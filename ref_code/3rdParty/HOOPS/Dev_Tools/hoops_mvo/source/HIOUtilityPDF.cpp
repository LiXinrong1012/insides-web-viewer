//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hoops_mvo/source/HIOUtilityPDF.cpp,v 1.72 2011-01-25 18:24:21 reuben Exp $
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "HIOUtilityPDF.h"
#include "HUtility.h"
#include "HBaseView.h"
#include "varray.h"
#include "HUtilityLocaleString.h"
#include "vlist.h"
#include "vhash.h"
#include "HBhvBehaviorManager.h"
#include "HBaseModel.h"
#include "HBhvAnimation.h"
#include "HBhvTimeline.h"


#include <vector>
#include <map>
#include <set>

#ifndef _WIN32_WCE
#include <sys/stat.h>

#include "ezpdf.h"

using namespace ezpdf;
using namespace std;

/*! HPDFPoster is a utility class used to help HIOUtilityPDF create 3d pdf files.
*/
class MVO_API HPDFPoster
{
public:
	/*! Constructs an HPDFPoster object. */
	HPDFPoster(){
		left = right = bottom = top = length = width = height = 0;
		data = (unsigned char*)0;
	}

	~HPDFPoster(){
		if(data)
			delete [] data;
	}
	/*! The image bounding in inches.*/
	float left, right, bottom, top;

	/*! The image width and height in pixels. */
	int width, height;
	/*! The uncompressed length of the image. */
	int length;
	/*! The uncompressed image data. */
	unsigned char * data;
};

/*! HPDFU3d is a utility class used to help HIOUtilityPDF create 3d pdf files.
*/
class MVO_API HPDFStream
{
public:
	/*! Constructs an HPDFU3d object. */
	HPDFStream(){
		length = 0;
		data = (unsigned char*)0;
	}

	~HPDFStream(){
		delete [] data;
	}
	/*! The length of the uncompressed data. */
	int length;
	/*! The u3d data. */
	unsigned char * data;

};

static void GetPosterStream(HPDFPoster*, HOutputHandlerOptions*, float const sizes[]);
static void Get3DStream(HPDFStream*, char const *, HPDFOptions*);

HPDFOptions::HPDFOptions() {
	m_pNativeFileName = 0;
	m_embeddedFiles = 0;
	m_pPRCAsmModelFile = 0;
	m_AnimationData = 0;
	Reset();
}

HPDFOptions::~HPDFOptions() {
	delete m_pNativeFileName;
	delete m_embeddedFiles;
	delete m_AnimationData;
}


char const * HPDFOptions::GetType() const
{
	return "HPDFOptions";
}

bool HPDFOptions::PopulateOptions(){
	Reset();
	return true;
}

void HPDFOptions::Reset() {
	m_bActivateOnPageOpen = false;
	m_fAnnotLeft = 0.5;
	m_fAnnotRight = -0.5;
	m_fAnnotBottom = 2;
	m_fAnnotTop = -0.5;
	m_fTextX = 0.5 ;
	m_fTextY = 2;
	m_filename = (wchar_t*)0;
	m_U3dOptions.ExportAnnotations(false);
	m_U3dOptions.ExportLines(false);
	m_b2dOutput = true;
	m_bNativeOutput = false;
	m_bAVIOutput = false;	
	m_OutputType = H_PDF_OUTPUT_2D;
	delete m_embeddedFiles;
	m_embeddedFiles = new std::map<int, std::basic_string<__wchar_t> >;
}

HFileOutputResult HIOUtilityPDF::FileOutputByKey(const wchar_t * FileName, HC_KEY key, HOutputHandlerOptions * options)
{
	HPDFOptions auto_options;
	HPDFOptions * pdf_options = (HPDFOptions *)options;
	if( strcmp(pdf_options->GetType(), "HPDFOptions") != 0 ){
		pdf_options = &auto_options;
		pdf_options->Init(options);
	}
	if(pdf_options->PopulateOptions() == false){
		return OutputOK; /* We hit cancel or something. */
	}

	SetStartingOutput();

	HFileOutputResult retval = OutputFail;
	switch(pdf_options->OutputType()){
		case H_PDF_OUTPUT_PORTFOLIO:{
			ReportOutputInformation("Exporting PDF Portfolio");
			retval = FileOutputByKeyPortfolio(FileName, key, pdf_options);
		}break;

		case H_PDF_OUTPUT_3D:{
			ReportOutputInformation("Exporting 3D PDF");
			if(HDB::GetHIOManager()->GetOutputHandler("PRC"))
				retval = FileOutputByKey3D(FileName, "PRC", key, pdf_options);
			else if(HDB::GetHIOManager()->GetOutputHandler("U3D"))
				retval = FileOutputByKey3D(FileName, "U3D", key, pdf_options);
			else
				retval = OutputFail;
		}break;

		case H_PDF_OUTPUT_2D:
		default:
			ReportOutputInformation("Exporting 2D PDF");
			retval = FileOutputByKey2D(FileName, key, pdf_options);
	}

	SetFinishedOutput();

	return retval;	
}

static Dict *
embedded_file_name_dict (Dict * fspec, wstring const &filepath)
{
	wchar_t const *filename = wcsrchr (filepath.c_str (), L'/');
	if (!filename)
		filename = wcsrchr (filepath.c_str (), L'\\');
	if (!filename)
		filename = filepath.c_str ();
	else
		++filename;

	fspec->insert ("Type", Name ("Filespec"));
	fspec->insert ("Desc", String (H_ASCII_TEXT(filename)));
	fspec->insert ("F", String (H_ASCII_TEXT(filename)));
	fspec->insert ("UF", WString (filename));

	Dict *ef = fspec->newDict ("EF");
	Dict *embedded_file = ef->newDict ("F");

	embedded_file->insert ("Type", Name ("EmbeddedFile"));
#ifdef _MSC_VER
	ifstream in (filepath.c_str (), std::ios::in | std::ios::binary);
#else
	ifstream in ((char const*)H_UTF8(filepath.c_str()).encodedText(), std::ios::in | std::ios::binary);
#endif
	if (!in)
	{
		wcerr << "Wasn't able to open input pdf " << filepath << endl;
		exit (1);
	}
#if 1
	filters::zlib zlib;
	char buffer[EZPDF_BUFFER_SIZE];
	in.read (buffer, EZPDF_BUFFER_SIZE);
	while (in.gcount () > 0){
		zlib.write(buffer, in.gcount ());
		in.read (buffer, EZPDF_BUFFER_SIZE);
	}
	zlib.read (buffer, EZPDF_BUFFER_SIZE);
	while (zlib.gcount () > 0){
		embedded_file->appendStream (buffer, zlib.gcount ());
		zlib.read (buffer, EZPDF_BUFFER_SIZE);
	}

	embedded_file->insert ("Length", embedded_file->streamSize ());
	Array * filters = embedded_file->newArray("Filter");
	filters->insert(Name(zlib.name()));
#else
	char buffer[EZPDF_BUFFER_SIZE];
	in.read (buffer, EZPDF_BUFFER_SIZE);
	while (in.gcount () > 0){
		embedded_file->appendStream (buffer, in.gcount ());
		in.read (buffer, EZPDF_BUFFER_SIZE);
	}

	embedded_file->insert ("Length", embedded_file->streamSize ());
	Array * filters = embedded_file->newArray("Filter");
#endif
	return fspec;
}

static void
BuildPage1 (Dict * page1)
{
	page1->insert ("Type", Name("Page"));

	Dict *contents = page1->newDict ("Contents");
	char strm[] = { "" };
	contents->appendStream (strm, strlen (strm));
	contents->insert ("Length", (int) strlen (strm));

	Dict *resources = page1->newDict ("Resources");
	Name tmp[] = { "PDF", "Text", "ImageA", "ImageB", "ImageC"};
	Array * resource_array = resources->newArray();
	resource_array->insert (tmp, tmp + 5);
	resources->insert ("ProcSet", resource_array);

	float media_box_data[] = { 0, 0, 300, 300 };
	Array * media_box = page1->newArray(media_box_data, media_box_data + 4);
	page1->insert ("MediaBox", media_box);

}

static
void BuildPages(Dict * pages)
{
	Dict *page = pages->newDict ();
	page->insert ("Parent", pages);
	BuildPage1 (page);

	Array * page_array = page->newArray();
	page_array->insert (page);
	pages->insert ("Kids", page_array);
	pages->insert ("Count", page_array->size ());
	pages->insert ("Type", Name("Pages"));
}


static
void BuildCollection(Dict * col, vector<basic_string<__wchar_t> > const & files)
{
	Dict *col_sort = col->newDict ("Sort");
	col_sort->insert ("Type", Name("CollectionSort"));
	Array * sorts = col_sort->newArray();
	for(unsigned int i = 0; i < files.size(); ++i){
		basic_string<__wchar_t> tmp = files[i];
		string utf8((char const*)H_UTF8(tmp.c_str()).encodedText());
		sorts->insert (String (utf8));
	}
	col_sort->insert ("S", sorts);

	col->insert ("Type", Name("Collection"));
	basic_string<__wchar_t> tmp = files[0];
	string utf8((char const*)H_UTF8(tmp.c_str()).encodedText());
	col->insert ("D", String (utf8));
	col->insert ("View", Name("T"));
}


static void
EmbedFiles(Dict * name_tree, vector<basic_string<__wchar_t> > const & files)
{
	set<basic_string<__wchar_t> > sorted_names;
	for(unsigned int i = 0; i < files.size(); ++i)
		sorted_names.insert(files[i]);

	Dict *embedded_names = name_tree->newDict ("EmbeddedFiles");
	Array * what_names = embedded_names->newArray();
	set<basic_string<__wchar_t> >::const_iterator iter = sorted_names.begin();
	set<basic_string<__wchar_t> >::const_iterator const end = sorted_names.end();
	while(iter != end)
	{
		basic_string<__wchar_t> tmp = *iter;
		H_UTF8 utf8(tmp.c_str());
		what_names->insert (String ((char const*)utf8.encodedText()));
		what_names->insert (embedded_file_name_dict (name_tree->newDict(), *iter));
		++iter;
	}
	embedded_names->insert ("Names", what_names);
}


static void
BuildPortfolio (const wchar_t * FileName, vector<basic_string<__wchar_t> > const & files)
{
	File pdf (FileName);

	Dict *catalog = pdf.newDict ("Root");
	BuildPages(catalog->newDict ("Pages"));
	BuildCollection(catalog->newDict ("Collection"), files);
	EmbedFiles(catalog->newDict ("Names"), files);
	catalog->insert ("Type", Name("Catalog"));

	Dict *info = pdf.newDict ("Info");
	info->insert ("Producer", String ("pdf++"));
	pdf.close();
}



/* When we finally fix the HInputOptions and HOutputOptions interface, this should be removed. */
typedef	struct AVIExportInfo {

	int starttick;		//!< Starttick for animation.
	int endtick;		//!< Endtick for animation.
	int resolution;		//!< The number of frames per second.
} AVIExportInfo;	//!< AVIExportInformation  Typedef for AVIExportInfo


static
bool WriteAviForPDF(HBaseView * m_pHView, wchar_t const * filename)
{
	bool retval = true;
	HBhvBehaviorManager *pBehaviorManager = m_pHView->GetModel()->GetBhvBehaviorManager();
	vlist_t * alist = pBehaviorManager->GetAnimationList();
	if(vlist_count(alist) > 0){

		HOutputHandler * aviio = HDB::GetHIOManager()->GetOutputHandler("avi");

		if(aviio){
			AVIExportInfo aviinfo;
			HBhvAnimation * animation = (HBhvAnimation *)vlist_peek_first(alist);

			aviinfo.starttick = animation->GetFirstTick();
			aviinfo.endtick = animation->GetLastTick();
			aviinfo.resolution = 33;

			HOutputHandlerOptions options;
			options.ExtendedData((void*)&aviinfo);
			options.View(m_pHView);
			options.WindowWidth(640);
			options.WindowHeight(480);

			if(aviio->FileOutputByKey(filename, m_pHView->GetModelKey(), &options) != OutputOK){
				retval = false;
			}
		}
		else return false;
	}
	else {
		m_pHView->FitWorld();
		m_pHView->ForceUpdate();
		m_pHView->SetSuppressUpdate(true);
		HCamera oldcamera;
		m_pHView->GetCamera(&oldcamera);
		bool oldsmooth = m_pHView->GetSmoothTransition();
		pBehaviorManager->SetCurrentTick(0);
 		m_pHView->SetSmoothTransition(false);
		m_pHView->SetViewMode(HViewFront);
		HBhvUtility::MakeCameraKeyframe(m_pHView,100, true);
		m_pHView->SetViewMode(HViewBack);
		HBhvUtility::MakeCameraKeyframe(m_pHView,100, true);
		m_pHView->SetViewMode(HViewIsoBackRightTop);
		HBhvUtility::MakeCameraKeyframe(m_pHView,100, true);		
		m_pHView->SetSuppressUpdate(false);
		m_pHView->SetCamera(oldcamera);
 		
		retval = WriteAviForPDF(m_pHView, filename);
		m_pHView->SetCamera(oldcamera);
		m_pHView->SetSmoothTransition(oldsmooth);	
		pBehaviorManager->DeleteAllAnimations();
 	}
	return retval;
}


HFileOutputResult HIOUtilityPDF::FileOutputByKeyPortfolio(const wchar_t * FileName, HC_KEY key, HPDFOptions * options) 
{
	if(!FileName) return OutputBadFileName;
	if(key == INVALID_KEY) return OutputFail;
	if(!options) return OutputFail;
	if( !options->m_pHBaseView )
		return OutputFail;

	SetStartingOutput();

	vector<basic_string<__wchar_t> > filevec;

	basic_string<__wchar_t> pdf2d;
	bool valid_2dpdf = false;

	if(options->Output2d()){
		ReportOutputProgress("Generating 2d pdf");
		pdf2d = FileName;
		pdf2d.resize(pdf2d.length() -4);
		pdf2d.append(L"2d.pdf");
		HFileOutputResult res = OutputFail;
		res = FileOutputByKey2D(pdf2d.c_str(), key, options);
		if(res == OutputOK){
			filevec.push_back(pdf2d);
			valid_2dpdf = true;
		}
	}
	
	basic_string<__wchar_t> pdf3d;
	basic_string<__wchar_t> pdf_prc;
	bool valid_3dpdf = false;
	
	if(options->Output3d()){
		if(options->came_from_adobe()){

			pdf_prc = options->NativeFileName();
 			HInputHandlerOptions prcoptions;
			prcoptions.m_pPRCAsmModelFile = options->m_pPRCAsmModelFile;
			prcoptions.m_bPRCCreatePRCFileOnly = true;
			HInputHandler * prchandler = HDB::GetHIOManager()->GetInputHandler("PRC");
  			prchandler->FileInputByKey(pdf_prc.c_str(),options->m_pHBaseView->GetModelKey(), &prcoptions);
 
 			wchar_t const * const dot = wcsrchr(pdf_prc.c_str(), L'.');
			if(dot){
				pdf_prc.resize(static_cast<int>(dot - pdf_prc.c_str()));
				pdf_prc.append(L"_prc.pdf");
				
				FILE * test = wfopen(pdf_prc.c_str(), L"rb");
				if(test){
					fclose(test);
					filevec.push_back(pdf_prc);
				}
			}
		}
		else {
			ReportOutputProgress("Generating 3d pdf");
			pdf3d = FileName;
			pdf3d.resize(pdf3d.length() -4);
			pdf3d.append(L"3d.pdf");
			HFileOutputResult res = OutputFail;
			if(HDB::GetHIOManager()->GetOutputHandler("PRC"))
				res = FileOutputByKey3D(pdf3d.c_str(), "PRC", key, options);
			else if(HDB::GetHIOManager()->GetOutputHandler("U3D"))
				res = FileOutputByKey3D(pdf3d.c_str(), "U3D", key, options);
			if(res == OutputOK){
				filevec.push_back(pdf3d);
				valid_3dpdf = true;
			}
		}
	}

	if(options->OutputNative() && (options->NativeFileName().length() > 0)){
		filevec.push_back(options->NativeFileName());
	}

#ifdef _MSC_VER	
	basic_string<__wchar_t> pdfavi;
	bool valid_avi = false;
	if(options->OutputAVI()){
		pdfavi = FileName;
		pdfavi.resize(pdfavi.length() -4);
		pdfavi.append(L".avi");
		ReportOutputProgress("Recording model video");
		if(WriteAviForPDF(options->View(), pdfavi.c_str())){
			filevec.push_back(pdfavi);
			valid_avi = true;
		}
	}
#endif
	
	map<int, basic_string<__wchar_t> > const * filemap = options->EmbeddedFiles();
	map<int, basic_string<__wchar_t> >::const_iterator iter = filemap->begin();
	map<int, basic_string<__wchar_t> >::const_iterator const end = filemap->end();
	while(iter != end){
		filevec.push_back(iter->second);
		++iter;
	}

	ReportOutputProgress("Assembling PDF Portfolio");
	BuildPortfolio(FileName, filevec);
	
	ReportOutputProgress("Cleaning up");

	if(valid_2dpdf)
		wremove(pdf2d.c_str());

	if(valid_3dpdf)
		wremove(pdf3d.c_str());

#ifdef _MSC_VER
	if(valid_avi)
		wremove(pdfavi.c_str());
#endif
	
	return OutputOK;
}

HFileOutputResult HIOUtilityPDF::FileOutputByKey2D(const wchar_t * FileName, HC_KEY key, HOutputHandlerOptions * options) 
{
	char DriverPath[MVO_SEGMENT_PATHNAME_BUFFER];

	if(!FileName) return OutputBadFileName;
	if(key == INVALID_KEY) return OutputFail;
	if(!options) return OutputFail;
	if( !options->m_pHBaseView )
	    return OutputFail;
	
	if(options->WindowWidth() <= 0 || options->WindowHeight() <= 0){
		options->WindowWidth(8.5f);
		options->WindowHeight(11);
	}

	/* append FileName to "?driver/pdf/", enclose it in 
	 * single quotes to maintain case and to protect special characters 
	 * from interpretation as segment delimeters */
	//sprintf(DriverPath, "%s\'%s\'", "?driver/pdf/", (char*)H_UTF8(FileName).encodedText());	
	sprintf(DriverPath, "%s\'%s\'", "?driver/pdf/", H_ASCII_TEXT(FileName));	
	// now we print the file!!!
	HFileOutputResult retval = HUtility::TwoPassPrint(DriverPath, options);
	HC_Delete_Segment(DriverPath);

	return retval;
}

#define PDF_INCHES(x) (72*(x))
#define PDF_POINTS(x) (x)

#define SLICES_PER_SECOND 20.0f
#define RESIZETHRESHOLD 1000
static void GenerateJavascriptAnimationData(HPDFOptions * pdf_options)
{
 	HBaseView *view = pdf_options->m_pHBaseView;
	if (!view->GetModel()->GetBhvBehaviorManager()->GetAnimationList()->count)
		return;

	unsigned int animationTotal = 4096;
 	char *animationData = new char[animationTotal];
	strcpy(animationData,"var animationData = \"");
	
	HBhvBehaviorManager *pBehaviorManager = view->GetModel()->GetBhvBehaviorManager();
	int i=0;
 	pBehaviorManager->ScheduleAllAnimations(true);

	float lasttick = pBehaviorManager->GetLastTick();

	float tps = pBehaviorManager->GetTicksPerSecond();
	float endtime = lasttick / tps;
	 
	int numslices = endtime  * (float)SLICES_PER_SECOND;
	float slen = endtime / numslices;

	vlist_s *alist = pBehaviorManager->GetAnimationList();

	int animationcount = 0;

	HC_KEY animkeylist[256];
 	HC_KEY *animitemkeys[256];
 	HBhvAnimation *animationlist[256];
	float **animmatrices[256];
 
	vhash_s *ihash = new_vhash(10,malloc,free);

	START_LIST_ITERATION(HBhvAnimation,alist);	 
	if (strcmp(temp->GetInterpolator()->GetType(),"QuatRot") == 0 || 
		strcmp(temp->GetInterpolator()->GetType(),"Pos") == 0 || strcmp(temp->GetInterpolator()->GetType(),"Scale") == 0 ||
		strcmp(temp->GetInterpolator()->GetType(),"Color") == 0 || strcmp(temp->GetInterpolator()->GetType(),"SegSwitch") == 0)
	{
		HBhvTargetObject *target = temp->GetTarget();
		HC_KEY key = target->GetTargetKey();
		key = HC_KShow_Original_Key(key);
		void *dummy;
		if (vhash_lookup_item(ihash, (void *)key , (void **)&dummy) != VHASH_STATUS_SUCCESS || 
			strcmp(temp->GetInterpolator()->GetType(),"Color") == 0)
		{
			animkeylist[animationcount] = key;
			animmatrices[animationcount] = new float*[numslices];
			animitemkeys[animationcount] = new HC_KEY[numslices];
			animationlist[animationcount] = temp;
			float **matrixlist = animmatrices[animationcount];
			for (int j=0;j<numslices;j++)
				matrixlist[j] = new float[16];
			if (strcmp(temp->GetInterpolator()->GetType(),"Color") != 0)
				vhash_insert_item(ihash, (void *)key  , (void *)dummy);
			animationcount++;
		}
	}
 	END_LIST_ITERATION(alist);

						
	for (i=0;i<numslices;i++)
	{
		pBehaviorManager->SetCurrentTick((slen * i)*tps);				
 		pBehaviorManager->ExecuteAnimations(pBehaviorManager->GetCurrentTick(), 0);

		for (int j=0;j<animationcount;j++)
		{
 			float *cmatrix = animmatrices[j][i];

			HC_Open_Segment_By_Key(animkeylist[j]);
			if (animationlist[j]->GetTarget()->GetCameraType()!=NoCamera)
			{
				HPoint pos,tar,up;
				float fieldx, fieldy;
				HC_Show_Camera_Position(&pos.x, &pos.y, &pos.z);
				HC_Show_Camera_Target(&tar.x, &tar.y, &tar.z);
				HC_Show_Camera_Up_Vector(&up.x, &up.y, &up.z);
				HC_Show_Camera_Field(&fieldx, &fieldy);
				cmatrix[0] = pos.x; cmatrix[1] = pos.y; cmatrix[2] = pos.z;
				cmatrix[3] = tar.x; cmatrix[4] = tar.y; cmatrix[5] = tar.z;
				cmatrix[6] = up.x; cmatrix[7] = up.y; cmatrix[8] = up.z;
				cmatrix[9] = fieldx; cmatrix[10] = fieldy;
			}
			else
			{
				if (strcmp(animationlist[j]->GetInterpolator()->GetType(),"SegSwitch") == 0)
				{
					HKeyframe *kframe;
					int inter;
					animationlist[j]->GetInterpolator((slen * i)*tps,inter,&kframe);
					if (kframe->m_type == HANIString)
					{
							HKeyframeString *kframeString = (HKeyframeString *)kframe;
							char *target = kframeString->GetTarget();
							animitemkeys[j][i] = HC_KCreate_Segment(target);						
					}
				}
				else if (strcmp(animationlist[j]->GetInterpolator()->GetType(),"Color") == 0)
				{
					float c[3];
					char dummy[MVO_BUFFER_SIZE];
					char options[MVO_BUFFER_SIZE];
					HC_Show_Net_Explicit_Color("faces", "diffuse", c, dummy, options);
					cmatrix[0] = c[0];
					cmatrix[1] = c[1];
					cmatrix[2] = c[2];
				}
				else
				{
					if (HC_Show_Existence("modelling matrix"))
						HC_Show_Modelling_Matrix(cmatrix);
					else
						HC_Compute_Identity_Matrix(cmatrix);
				}
			}
			HC_Close_Segment();		
		}
	}

	char text[4096];
	sprintf(text,"%d,",animationcount);
	strcat(animationData,text);
	for (int j=0;j<animationcount;j++)
	{
		bool isCamera = false;
		if (animationlist[j]->GetTarget()->GetCameraType()!=NoCamera)
		{
			isCamera = true;
			sprintf(text,"1,");
			strcat(animationData,text);
		}
		else
		{
			if (strcmp(animationlist[j]->GetInterpolator()->GetType(),"Color") == 0)
				sprintf(text,"2,");
			else if (strcmp(animationlist[j]->GetInterpolator()->GetType(),"SegSwitch") == 0)
				sprintf(text,"3,");
			else 
				sprintf(text,"0,");
			strcat(animationData,text);
		}
		sprintf(text,"0.0,%f,%d,%p,0,",endtime,numslices,animkeylist[j]);
		strcat(animationData,text);
		for (int i=0;i<numslices;i++)
		{
			if (strlen(animationData) + RESIZETHRESHOLD > animationTotal)
			{
				char *temp = new char[animationTotal + 4096];
				memset(temp,0,animationTotal+4096);
				strcpy(temp,animationData);
				delete [] animationData;
				animationData = temp;
				animationTotal+=4096;
			}
			if (strcmp(animationlist[j]->GetInterpolator()->GetType(),"SegSwitch") == 0)
			{
				sprintf(text,"%p,",animitemkeys[j][i]);					
				strcat(animationData, text);
			}
			else
			{
				sprintf(text,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,",animmatrices[j][i][0], 
					animmatrices[j][i][1],animmatrices[j][i][2],animmatrices[j][i][3],animmatrices[j][i][4],animmatrices[j][i][5],
					animmatrices[j][i][6],animmatrices[j][i][7],animmatrices[j][i][8],animmatrices[j][i][9],animmatrices[j][i][10],
					animmatrices[j][i][11],animmatrices[j][i][12],animmatrices[j][i][13],animmatrices[j][i][14],animmatrices[j][i][15]);
				strcat(animationData, text);
 			}
			delete [] animmatrices[j][i];
		}
		delete [] animitemkeys[j];
		delete [] animmatrices[j];
	}
	delete_vhash(ihash);

 	strcat(animationData,"\";\n");
	
	pdf_options->m_AnimationData = animationData;
}





static
void Get3DStream(HPDFStream * strm, char const * type, HPDFOptions * pdf_options)
{
	HOutputHandler * handler = HDB::GetHIOManager()->GetOutputHandler(type);

	handler->FileOutputByKey("HIOUtilityPDFtmp", pdf_options->m_pHBaseView->GetModelKey(), pdf_options);
	
	GenerateJavascriptAnimationData(pdf_options);


	FILE * f = fopen("HIOUtilityPDFtmp", "rb");
	if(f){
		fseek(f, 0, SEEK_END);
		strm->length = ftell(f);
		fseek(f, 0, SEEK_SET);
		strm->data = new unsigned char[strm->length];
		if(strm->data){
			fread(strm->data, strm->length, 1, f);
		}
		fclose(f);
	}
	remove("HIOUtilityPDFtmp");
}


static void
DoGraphics (HPDFOptions * options, Dict * contents)
{
	Graphics g;
	g.BeginText(PDF_INCHES(options->m_fTextX), PDF_INCHES(options->m_fTextY) - 22, "Courier", 18);
	H_UTF8 filepath8(options->filename());
	char const * filename = strrchr((char*)filepath8.encodedText(), '/') +1;
	if(filename == (void*)1){
		filename = strrchr((char*)filepath8.encodedText(), '\\') +1;
	}
	if(filename == (void*)1){
		filename = (char*)filepath8.encodedText();
	}
	g.InsertText(0, 0, (char const *)H_FORMAT_TEXT("Filename: %s", filename));
	char time_str[256];
	struct tm * localtm;
	time_t now;
	time(&now);
	localtm = gmtime(&now);
	strftime(time_str, sizeof(time_str), "%B %d, %Y", localtm);
	g.InsertText(0, -22, (char const *)H_FORMAT_TEXT("Date: %s", time_str));
	g.InsertText(0, -22, "Creator: HOOPS 3D Framework");
	g.EndText();
	contents->appendStream (g);
	contents->insert ("Length", (int) contents->streamSize ());
}

static void
BuildDefaultView (HPDFOptions * options, Dict * view)
{
	view->insert("Type", Name("3DView"));
	view->insert("XN", String("HOOPS Default View"));
	view->insert("IN", String("HOOPS Default View"));
	view->insert("MS", Name("M"));
	HCamera hcam;
	options->m_pHBaseView->GetCamera(&hcam);
	float matrix[16];
	HUtility::GetMatrixFromCamera(hcam.target, hcam.position, hcam.up_vector, 
			hcam.position, matrix);

	Array * camera = view->newArray();
	camera->insert(matrix[0]);
	camera->insert(matrix[1]);
	camera->insert(matrix[2]);

	camera->insert(matrix[4]);
	camera->insert(matrix[5]);
	camera->insert(matrix[6]);
	
	camera->insert(matrix[8]);
	camera->insert(matrix[9]);
	camera->insert(matrix[10]);

	camera->insert(matrix[12]);
	camera->insert(matrix[13]);
	camera->insert(matrix[14]);

	view->insert("C2W", camera);

	HVector const camtotar = hcam.target - hcam.position;
	double const len = HC_Compute_Vector_Length(&camtotar);
	view->insert("CO", len);

	Dict * lights = view->newDict("LS");
	lights->insert("Type", Name("3DLightingScheme"));
	lights->insert("Subtype", Name("CAD"));

	Dict * proj = view->newDict("P");
	proj->insert("Subtype", Name("P"));
	double fov = 2*atan(hcam.field_height/2.0/len);
	fov *= 180 / 3.14159;
	proj->insert("FOV", fov);
	proj->insert("N", 1);
	proj->insert("PS", Name("W"));
}

static
char const OnInstantiate[] = {
"console.println(\"==== Running JavaScript Embedded in 3d Annotation ====\");\n"
"\n"
"console.println(\"Animation Count: \" + scene.animations.count);\n"
"\n"
"/*Change this value to change the speed of the defaults camera transition*/\n"
"var gCameraStep			= 30;\n"
"var myTimer				= 0;\n"
"var myPrcTimer				= 0;\n"
"var i				= 0;\n"
"var curNode				= \"frame 0\";\n"
"\n"
"\n"
"\n"
"\n"
"function flipCardAnimation(){\n"
"	this.speed				= 0;\n"
"	this.cardsPerSecond		= 0;\n"
"	this.curCard			= 0;\n"
"	this.nextCard			= 0;\n"
"	this.endCard			= 0;\n"
"	this.oneFrame			= 0;\n"
"}\n"
"\n"
"\n"
"function startFlipCardAnimation(){\n"
"\n"
"	flipCardAnimation					= new flipCardAnimation();\n"
"	flipCardAnimation.speed				= 1;\n"
"	flipCardAnimation.cardsPerSecond	= 7.0;\n"
"	flipCardAnimation.curCard			= 0;\n"
"	flipCardAnimation.nextCard			= 0;\n"
"	flipCardAnimation.endCard			= 0;\n"
"	while(node = scene.nodes.getByName( \"frame \" + (flipCardAnimation.endCard +1) ))\n"
"		flipCardAnimation.endCard++;\n"
"	var nextFrame						= 0;\n"
"\n"
"	/*run the animation using a TimeEventHandler()*/\n"
"	myTimer			= new TimeEventHandler();\n"
"	myTimer.onEvent	= function(event){\n"
"\n"
"		flipCardAnimation.nextCard += flipCardAnimation.cardsPerSecond * (flipCardAnimation.speed * event.deltaTime);\n"
"		if(Math.floor(flipCardAnimation.nextCard) == flipCardAnimation.curCard)\n"
"			return;\n"
"		setVisibility( curNode, false );\n"
"		flipCardAnimation.curCard = Math.floor(flipCardAnimation.nextCard);\n"
"		if (flipCardAnimation.curCard > flipCardAnimation.endCard)\n"
"		{\n"
"			flipCardAnimation.curCard -= flipCardAnimation.endCard;\n"
"			flipCardAnimation.nextCard = flipCardAnimation.curCard;\n"
"		}\n"
"		\n"
"		curNode = \"frame \" + flipCardAnimation.curCard;\n"
"		setVisibility( curNode, true );\n"
"	}\n"
"   runtime.addEventHandler(myTimer);\n"
"	console.println( \"==== Started Flip Card Animation ====\");\n"
"}\n"
"\n"
"\n"
"function startAnimation(){\n"
"\n"
"	firstAnimation			= scene.animations.getByIndex(0);\n"
"	firstAnimation.speed	= 3;\n"
"	firstAnimation.oneFrame	= 1 / firstAnimation.framesPerSecond;\n"
"\n"
"	/*run the animation using a TimeEventHandler()*/\n"
"	myTimer			= new TimeEventHandler();\n"
"	myTimer.onEvent	= function(event){\n"
"\n"
"		firstAnimation.currentTime += firstAnimation.oneFrame * (firstAnimation.speed * event.deltaTime);\n"
"		if (firstAnimation.currentTime > firstAnimation.endTime)\n"
"	{\n"
"			firstAnimation.currentTime = firstAnimation.startTime;\n"
"		}\n"
"		}\n"
"   runtime.addEventHandler(myTimer);\n"
"	console.println( \"==== Started Animation ====\");\n"
"}\n"
"\n"
"function stopAnimation(){\n"
"	runtime.removeEventHandler(myTimer);\n"
"	myTimer = 0;\n"
"	console.println( \"==== Stopped Animation ====\");\n"
"}\n"
" \n"
" \n"
"\n"
"\n"
"function setLightScheme( lightSchemeName ){\n"
"    scene.lightScheme = lightSchemeName;\n"
"}\n"
"\n"
"function setRenderMode( renderModeName ){\n"
"    scene.renderMode = renderModeName;\n"
"}\n"
"\n"
"\n"
"var CONST_MATRIX = 0;\n"
"var CONST_CAMERA = 1;\n"
"var CONST_COLOR = 2;\n"
"var CONST_SEGSWITCH = 3;\n"
" \n"
"HJSCameraType = function HJSCameraType() {\n"
"    this.position = new Vector3();\n"
"    this.target = new Vector3();\n"
"    this.up = new Vector3();\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"HJSColorType = function HJSColorType() {\n"
"    this.r = 0.0;\n"
"    this.g = 0.0;\n"
"    this.b = 0.0;\n"
"}\n"
"\n"
"HJSSegSwitchType = function HJSSegSwitchType() {\n"
"    this.name = \"empty\";\n"
"    this.targetindex = 0;\n"
" }\n"
"\n"
"function HJSAnimationType(animtype,starttime, endtime,keyframes)\n"
"{\n"
"    HJSAnimationType.prototype.m_type = 0;\n"
"    HJSAnimationType.prototype.m_starttime = 0.0;\n"
"    HJSAnimationType.prototype.m_endtime = 0.0;\n"
"    HJSAnimationType.prototype.m_target = \"0\";\n"
"    HJSAnimationType.prototype.m_targetindex = -1;\n"
"    HJSAnimationType.prototype.m_bHasExplicitTimes = 0;\n"
"    HJSAnimationType.prototype.m_keyframes = new Array();\n"
"    HJSAnimationType.prototype.m_camerakeyframes = new Array();\n"
"    HJSAnimationType.prototype.m_colorkeyframes = new Array();\n"
"    HJSAnimationType.prototype.m_segswitchkeyframes = new Array();\n"
"    HJSAnimationType.prototype.m_keyframeTime = new Array();\n"
"    \n"
"    HJSAnimationType.prototype.m_bIsActive = 0;\n"
"    \n"
"    \n"
"}\n"
"    \n"
"    \n"
"var HJSAnimationArray = new Array();\n"
"\n"
"var lastSegSwitchIndex;\n"
"\n"
"function HJSResetSegSwitchAnimation() {\n"
"\n"
"    for (i = 0; i < HJSAnimationArray.length; i++) {\n"
"        if (HJSAnimationArray[i].m_type == 3) {\n"
"            for (j = 0; j < HJSAnimationArray[i].m_segswitchkeyframes.length; j++) {\n"
"                setVisibility(scene.nodes.getByIndex(HJSAnimationArray[i].m_segswitchkeyframes[j].targetindex).name, false);\n"
"            }\n"
"            setVisibility(scene.nodes.getByIndex(HJSAnimationArray[i].m_segswitchkeyframes[0].targetindex).name, true);\n"
"        }\n"
"    }\n"
"    lastSegSwitchIndex = 0;\n"
"}\n"
"            \n"
"\n"
"function HJSDecipherAnimationData() {\n"
"    var p = 0;\n"
"    console.println(\"Decipher\");\n"
"\n"
"    var animarray = animationData.split(\",\");\n"
"    var numberOfAnimations = parseInt(animarray[p++]);\n"
"\n"
"    HJSAnimationArray = new Array(numberOfAnimations);\n"
"    for (i = 0; i < numberOfAnimations; i++) \n"
"    {\n"
"\n"
"        HJSAnimationArray[i] = new HJSAnimationType;\n"
"        HJSAnimationArray[i].m_type = parseInt(animarray[p++]);\n"
"    \n"
"        HJSAnimationArray[i].m_starttime = parseFloat(animarray[p++]);\n"
"        HJSAnimationArray[i].m_endtime = parseFloat(animarray[p++]);\n"
"\n"
"        var numkeyframes = parseInt(animarray[p++]);\n"
"        HJSAnimationArray[i].m_target = animarray[p++];\n"
"        HJSAnimationArray[i].m_bHasExplicitTimes = parseInt(animarray[p++]);\n"
"\n"
"        if (HJSAnimationArray[i].m_type == CONST_MATRIX)\n"
"            HJSAnimationArray[i].m_keyframes = new Array(numkeyframes);\n"
"        else if (HJSAnimationArray[i].m_type == CONST_CAMERA)\n"
"            HJSAnimationArray[i].m_camerakeyframes = new Array(numkeyframes);\n"
"        else if (HJSAnimationArray[i].m_type == CONST_COLOR)\n"
"            HJSAnimationArray[i].m_colorkeyframes = new Array(numkeyframes);\n"
"        else if (HJSAnimationArray[i].m_type == CONST_COLOR)\n"
"            HJSAnimationArray[i].m_segswitchkeyframes = new Array(numkeyframes);\n"
"\n"
"\n"
"        var ncbase = 0;\n"
"         for (j = 0; j < numkeyframes; j++) {\n"
"             if (HJSAnimationArray[i].m_type == CONST_MATRIX)\n"
"                 HJSAnimationArray[i].m_keyframes[j] = new Matrix4x4();\n"
"             else if (HJSAnimationArray[i].m_type == CONST_CAMERA)\n"
"                 HJSAnimationArray[i].m_camerakeyframes[j] = new HJSCameraType();\n"
"             else if (HJSAnimationArray[i].m_type == CONST_COLOR)\n"
"                 HJSAnimationArray[i].m_colorkeyframes[j] = new HJSColorType();\n"
"             else if (HJSAnimationArray[i].m_type == CONST_SEGSWITCH)\n"
"                 HJSAnimationArray[i].m_segswitchkeyframes[j] = new HJSSegSwitchType();\n"
"                 \n"
"                \n"
"            var slicetime = (HJSAnimationArray[i].m_endtime - HJSAnimationArray[i].m_starttime)/numkeyframes;\n"
"           \n"
"            if (HJSAnimationArray[i].m_bHasExplicitTimes == 0)\n"
"                HJSAnimationArray[i].m_keyframeTime[j] = j * slicetime  + HJSAnimationArray[i].m_starttime;\n"
"             else\n"
"                 HJSAnimationArray[i].m_keyframeTime[j] = parseFloat(animarray[p++]);\n"
"\n"
"             if (HJSAnimationArray[i].m_type != CONST_SEGSWITCH) {\n"
"                 var tm = new Array();\n"
"                 for (k = 0; k < 16; k++) {\n"
"                     tm[k] = parseFloat(animarray[p++]);\n"
"\n"
"\n"
"                 }\n"
"\n"
"                 if (HJSAnimationArray[i].m_type == CONST_MATRIX) {\n"
"                     HJSAnimationArray[i].m_keyframes[j].set(tm[0], tm[1], tm[2], tm[3], tm[4], tm[5], tm[6], tm[7], tm[8], tm[9], tm[10], tm[11],\n"
"                 tm[12], tm[13], tm[14], tm[15]);\n"
"                 }\n"
"                 else if (HJSAnimationArray[i].m_type == CONST_CAMERA) {\n"
"                     HJSAnimationArray[i].m_camerakeyframes[j].position.set(tm[0], tm[1], tm[2]);\n"
"                     HJSAnimationArray[i].m_camerakeyframes[j].target.set(tm[3], tm[4], tm[5]);\n"
"                     HJSAnimationArray[i].m_camerakeyframes[j].up.set(tm[6], tm[7], tm[8]);\n"
"                 }\n"
"                 else if (HJSAnimationArray[i].m_type == CONST_COLOR) {\n"
"                     HJSAnimationArray[i].m_colorkeyframes[j].r = tm[0];\n"
"                     HJSAnimationArray[i].m_colorkeyframes[j].g = tm[1];\n"
"                     HJSAnimationArray[i].m_colorkeyframes[j].b = tm[2];\n"
"                 }\n"
"             }\n"
"             else {\n"
"                 HJSAnimationArray[i].m_segswitchkeyframes[j].name = animarray[p++];\n"
"\n"
"\n"
"                 var origname;\n"
"                            for (k = ncbase; k < scene.nodes.count; k++) {\n"
"                             var pos = scene.nodes.getByIndex(k).name.search(HJSAnimationArray[i].m_segswitchkeyframes[j].name);\n"
"                             if (pos >= 0) {\n"
"                                 ncbase = k;\n"
"                                 origname = scene.nodes.getByIndex(k).name;\n"
"                                 HJSAnimationArray[i].m_segswitchkeyframes[j].targetindex = k;\n"
"//                                 setVisibility(scene.nodes.getByIndex(k).name, false);\n"
"                                 break;\n"
"                             }\n"
"                         }\n"
"                //         if (k >= scene.nodes.count) {\n"
" //\n"
"//\n"
"  //                                            console.println(\"ff\");\n"
"    //                                            console.println(j);\n"
"      //                                                console.println(origname);                                \n"
"        //                                    console.println( HJSAnimationArray[i].m_segswitchkeyframes[j].name);\n"
"          //                                console.println( HJSAnimationArray[i].m_segswitchkeyframes[j].targetindex);\n"
"            //             }\n"
"             }\n"
"            \n"
"            \n"
"        }\n"
"\n"
"    }\n"
"\n"
"\n"
"    console.println(\"Decipher done\");\n"
"        \n"
"}\n"
"\n"
"\n"
"function HJSAssociateTarget() {\n"
"    for (i = 0; i < HJSAnimationArray.length; i++) {\n"
"        for (j = 0; j < scene.nodes.count; j++) {\n"
"            var pos = scene.nodes.getByIndex(j).name.search(HJSAnimationArray[i].m_target);\n"
"            if (pos >= 0) {\n"
"                HJSAnimationArray[i].m_targetindex = j;\n"
"                break;\n"
"            }\n"
"        }\n"
"    }\n"
"}\n"
"\n"
"var FirstTime = 1;\n"
"\n"
"function HJSPrcEvent(event) {\n"
"\n"
"    if (FirstTime == 1) {\n"
"        StartTime = event.time;\n"
"        FirstTime = 0;\n"
"    }\n"
"    var elapsedTime = event.time - StartTime;\n"
" \n"
"    for (i = 0; i < HJSAnimationArray.length; i++) {\n"
"      \n"
"        if (HJSAnimationArray[i].m_bIsActive == 1)\n"
"        {\n"
"            for (j = HJSAnimationArray[i].m_keyframeTime.length - 1; j > 0; j--) {               \n"
"                if (HJSAnimationArray[i].m_keyframeTime[j] <= elapsedTime) {\n"
"                    \n"
"                    if (HJSAnimationArray[i].m_type == 1) {\n"
"                        var currentCamera = scene.cameras.getByIndex(0);\n"
"                        currentCamera.position.set(HJSAnimationArray[i].m_camerakeyframes[j].position);\n"
"                        var up2 = new Vector3();\n"
"                        up2.set(0, 0, 0);\n"
"                        up2.addInPlace(HJSAnimationArray[i].m_camerakeyframes[j].up);\n"
"                        up2.addInPlace(HJSAnimationArray[i].m_camerakeyframes[j].position);\n"
"\n"
"                        currentCamera.up.set(up2);\n"
"                        currentCamera.targetPosition.set(HJSAnimationArray[i].m_camerakeyframes[j].target);\n"
"\n"
"                    }\n"
"                    else if (HJSAnimationArray[i].m_type == 0) {\n"
"                        scene.nodes.getByIndex(HJSAnimationArray[i].m_targetindex).transform.set(HJSAnimationArray[i].m_keyframes[j]);\n"
"                    }\n"
"                    else if (HJSAnimationArray[i].m_type == 2) {\n"
"                        var currentchild = scene.nodes.getByIndex(HJSAnimationArray[i].m_targetindex).firstChild;\n"
"                        while (true) {\n"
"                            currentchild.material.diffuseColor.set(HJSAnimationArray[i].m_colorkeyframes[j].r, HJSAnimationArray[i].m_colorkeyframes[j].g,\n"
"                            HJSAnimationArray[i].m_colorkeyframes[j].b);\n"
"                            currentchild.material.specularColor.set(HJSAnimationArray[i].m_colorkeyframes[j].r, HJSAnimationArray[i].m_colorkeyframes[j].g,\n"
"                            HJSAnimationArray[i].m_colorkeyframes[j].b);\n"
"                            currentchild.material.ambientColor.set(HJSAnimationArray[i].m_colorkeyframes[j].r, HJSAnimationArray[i].m_colorkeyframes[j].g,\n"
"                            HJSAnimationArray[i].m_colorkeyframes[j].b);\n"
"\n"
"                            currentchild = currentchild.nextSibling;\n"
"                            if (!currentchild)\n"
"                                break;\n"
"                        }\n"
"\n"
"\n"
"\n"
"                    }\n"
"                    else {\n"
"                        idx = HJSAnimationArray[i].m_segswitchkeyframes[j].targetindex;\n"
"                        if (lastSegSwitchIndex != -1 && lastSegSwitchIndex != idx) {\n"
"                            setVisibility(scene.nodes.getByIndex(lastSegSwitchIndex).name, false);\n"
"                        }\n"
"\n"
"                        setVisibility(scene.nodes.getByIndex(idx).name, true);\n"
"                        lastSegSwitchIndex = idx;\n"
"                    }\n"
"\n"
"\n"
"                    break;\n"
"                }\n"
"                \n"
"                \n"
"            }\n"
"         }\n"
"     }\n"
"     \n"
"    var done = 0;\n"
"    for (i = 0; i < HJSAnimationArray.length; i++) {\n"
"        l = HJSAnimationArray[i].m_keyframeTime.length - 1;\n"
"        if (HJSAnimationArray[i].m_keyframeTime[l] < elapsedTime)\n"
"            done++;\n"
"    }\n"
"\n"
"\n"
"    if (done == HJSAnimationArray.length) {\n"
"         HJSStopAnimation();\n"
"         HJSStartAnimation();\n"
"     }\n"
"             \n"
"}\n"
"\n"
"function HJSActivateAnimation(i)\n"
"{\n"
"    HJSAnimationArray[i].m_bIsActive = 1;\n"
"}\n"
"function HJSActivateAllAnimations()\n"
"{\n"
"    for (i=0;i<HJSAnimationArray.length;i++)\n"
"        HJSAnimationArray[i].m_bIsActive = 1;\n"
"}\n"
"    \n"
"function HJSStartAnimation() {\n"
"\n"
"    FirstTime = 1;\n"
"    /*run the animation using a TimeEventHandler()*/\n"
"    myPrcTimer = new TimeEventHandler();\n"
"    myPrcTimer.onEvent = HJSPrcEvent;\n"
"\n"
"    runtime.addEventHandler(myPrcTimer);\n"
"    console.println(\"==== Started PRC Animation ====\");\n"
"}\n"
"\n"
"\n"
"\n"
"function HJSStopAnimation() {\n"
"    runtime.removeEventHandler(myPrcTimer);\n"
"    myPrcTimer = 0;\n"
"    console.println(\"==== Stopped Animation ====\");\n"
"}\n"
"\n"
"\n"
"var firsttime = 0;\n"
"\n"
"function toggleAnimation(){\n"
"\n"
"    var matrix = new Matrix4x4();\n"
"\n"
"    if (firsttime == 0) {\n"
"        HJSDecipherAnimationData();\n"
"        HJSAssociateTarget();\n"
"        HJSActivateAllAnimations();\n"
"        firsttime = 1;\n"
"        HJSResetSegSwitchAnimation();\n"
"    }\n"
" \n"
"	if(myPrcTimer == 0){\n"
"		HJSStartAnimation();\n"
"	} else {\n"
"		HJSStopAnimation();\n"
"	}\n"
"	}\n"
"\n"
"function toggleFlipCardAnimation(){\n"
"	if(myTimer == 0){\n"
"		startFlipCardAnimation();\n"
"	} else {\n"
"		stopAnimation();\n"
"		}\n"
"	}\n"
"\n"
"function alignDefaultCamera(name)\n"
"{\n"
"\n"
"	var currentCamera = scene.cameras.getByIndex(0);\n"
"	var factor = 1.7320508075688772935274463415059;   /*sqr(3)*/\n"
"	var box = scene.computeBoundingBox();\n"
"	var r = (box.max.subtract(box.min)).length/(currentCamera.projectionType==currentCamera.TYPE_ORTHOGRAPHIC ? factor : Math.tan(currentCamera.fov));\n"
"\n"
"	var targetPosition = new Vector3();\n"
"	var position = new Vector3();\n"
"	var up = new Vector3();\n"
"	var viewPlaneSize = 1;\n"
"	var far = -1;\n"
"	var near = -1;\n"
"	var binding = currentCamera.BINDING_MIN ;\n"
"	var projectionType = currentCamera.projectionType ;\n"
"	var fov = currentCamera.fov;\n"
"					\n"
"	if ( name == \"Left\")\n"
"	{\n"
"		var vX = new Vector3();\n"
"		vX.set(r,0,0);\n"
"		targetPosition = box.center;\n"
"		position = box.center.subtract(vX);\n"
"		viewPlaneSize = r*factor;\n"
"		up.set(0,0,1);\n"
"		up.addInPlace(position);\n"
"	}\n"
"	else if ( name == \"Top\")\n"
"	{\n"
"		var vZ = new Vector3();\n"
"		vZ.set(0,0,r);\n"
"		targetPosition = box.center;\n"
"		position = box.center.add(vZ);\n"
"		viewPlaneSize = r*factor;\n"
"		up.set(0,1,0);\n"
"		up.addInPlace(position);\n"
"	}\n"
"	else if ( name == \"Front\")\n"
"	{\n"
"		var vY = new Vector3();\n"
"		vY.set(0,r,0);\n"
"		targetPosition = box.center;\n"
"		position = box.center.subtract(vY);\n"
"		viewPlaneSize = r*factor;\n"
"		up.set(0,0,1);\n"
"		up.addInPlace(position);\n"
"	}\n"
"	else if ( name == \"Right\")\n"
"	{\n"
"		var vX = new Vector3();\n"
"		vX.set(r,0,0);\n"
"		targetPosition = box.center;\n"
"		position = box.center.add(vX);\n"
"		viewPlaneSize = r*factor;\n"
"		up.set(0,0,1);\n"
"		up.addInPlace(position);\n"
"	}\n"
"	else if ( name == \"Bottom\")\n"
"	{\n"
"		var vZ = new Vector3();\n"
"		vZ.set(0,0,r);\n"
"		targetPosition = box.center;\n"
"		position = box.center.subtract(vZ);\n"
"		viewPlaneSize = r*factor;\n"
"		up.set(0,1,0);\n"
"		up.addInPlace(position);\n"
"	}\n"
"	else if ( name == \"Back\")\n"
"	{\n"
"		var vY = new Vector3();\n"
"		vY.set(0,r,0);\n"
"		targetPosition = box.center;\n"
"		position = box.center.add(vY);\n"
"		viewPlaneSize = r*factor;\n"
"		up.set(0,0,1);\n"
"		up.addInPlace(position);\n"
"	}\n"
"	else if ( name == \"Iso\")\n"
"	{\n"
"		var V = new Vector3();\n"
"		V.set(1,1,1);\n"
"		V.normalize();\n"
"		V.scaleInPlace(r);\n"
"		targetPosition = box.center;\n"
"		position = box.center.add(V);\n"
"		up.set(0,1,0);\n"
"		up.addInPlace(position);\n"
"		viewPlaneSize = r*factor;\n"
"	}\n"
"	else if ( name == \"Fit all\")\n"
"	{\n"
"		targetVector = currentCamera.position.subtract(currentCamera.targetPosition);\n"
"		targetVector.normalize();\n"
"		targetVector.scaleInPlace(r);\n"
"		targetPosition = box.center;\n"
"		position = new Vector3();\n"
"		position = box.center.add(targetVector);\n"
"		up = new Vector3();\n"
"		up = currentCamera.up.subtract(currentCamera.position);\n"
"		up.normalize();\n"
"		up.addInPlace(position);\n"
"		viewPlaneSize = r*factor;\n"
"	}\n"
"   else{\n"
"       return;\n"
"	}\n"
"\n"
"   var currentCamera = scene.cameras.getByIndex(0);\n"
"	currentCamera.position.set(position);\n"
"	currentCamera.up.set(up);\n"
"	currentCamera.targetPosition.set(targetPosition);\n"
"}\n"
"\n"
"function showNode( node, visible )\n"
"		{\n"
"        node.visible = visible;\n"
"        node = node.firstChild;\n"
"        while (node)\n"
"			{\n"
"                showNode(node,visible);\n"
"                node = node.nextSibling;\n"
"			}\n"
"		}\n"
"   \n"
"function setVisibility ( name, vis )\n"
"		{\n"
"	if(node = scene.nodes.getByName(name)){\n"
"		showNode( node, vis );\n"
"	    return;\n"
"			}\n"
"	console.println( \"==== Node Not Found: \" + name + \" ====\" );\n"
"		}\n"
"\n"
"function selectNode( name )\n"
"{\n"
"	if(node = scene.nodes.getByName(name)){\n"
"	    console.println( \"==== Selecting Node: \" + node.name + \" ====\" );\n"
"	    scene.selectedNode = node;\n"
"	    return;\n"
"	}\n"
"	console.println( \"==== Node Not Found: \" + name + \" ====\" );\n"
"}\n"
};


static void
Build3DD (HC_KEY key, HPDFOptions * options, char const * _3d_type, Dict * _3dd)
{
	_3dd->insert ("Type", Name("3D"));
	_3dd->insert ("Subtype", Name(_3d_type));

	Array * filter = _3dd->newArray();
	_3dd->insert ("Filter", filter);

	HPDFStream strm;
	Get3DStream(&strm, _3d_type, options);
	if(!strm.data){
		throw false;
	}

	filters::zlib zlib;
	zlib.write(strm.data, strm.length);
	char buf[1000];
	zlib.read(buf, 1000);
	while(zlib.gcount() > 0){
		_3dd->appendStream(buf, zlib.gcount());
		zlib.read(buf, 1000);
	}
	filter->insert(Name(zlib.name()));

	_3dd->insert ("Length", _3dd->streamSize());

	Array * VA = _3dd->newArray();
	_3dd->insert ("VA", VA);
	Dict * hoops_view = _3dd->newDict();
	VA->insert(hoops_view);
	BuildDefaultView (options, hoops_view);

	Dict * init = _3dd->newDict("OnInstantiate");

	char *istream;
	
	if (options->m_AnimationData)
	{
		istream = new char[strlen(OnInstantiate)+strlen(options->m_AnimationData) + 2];
		strcpy(istream,options->m_AnimationData);
		strcpy(&istream[strlen(options->m_AnimationData)], OnInstantiate);
		init->appendStream(istream, strlen(OnInstantiate) + strlen(options->m_AnimationData));
		init->insert("Length",  strlen(OnInstantiate) + strlen(options->m_AnimationData));

	}
	else
	{
		istream = new char[strlen(OnInstantiate)+2];
		strcpy(istream, OnInstantiate);
		init->appendStream(istream, strlen(OnInstantiate));
		init->insert("Length",  strlen(OnInstantiate));
	}
	delete [] istream;
}

static void
BuildPosterImage(HPDFOptions * options, float const sizes[], Dict * pimage)
{
	pimage->insert("Type", Name("XObject"));
	pimage->insert("Subtype", Name("Image"));
	pimage->insert("BitsPerComponent", 8);
	pimage->insert("ColorSpace", Name("DeviceRGB"));

	HPDFPoster poster;
	GetPosterStream(&poster, options, sizes);
	if(!poster.data){
		throw false;
	}

	pimage->insert("Width", poster.width);
	pimage->insert("Height", poster.height);

	filters::zlib zlib;
	zlib.write(poster.data, poster.length);
	char buf[1000];
	zlib.read(buf, 1000);
	while(zlib.gcount() > 0){
		pimage->appendStream(buf, zlib.gcount());
		zlib.read(buf, 1000);
	}
	pimage->insert ("Length", pimage->streamSize());

	Array * filter = pimage->newArray();
	pimage->insert ("Filter", filter);
	filter->insert(Name(zlib.name()));

#endif
}

static void
BuildAP (HPDFOptions * options, float const sizes[], Dict * ap)
{
	Dict * n = ap->newDict("N");
	n->insert("Type", Name("XObject"));
	n->insert("Subtype", Name("Form"));
	n->insert("FormType", 1);
	H_FORMAT_TEXT content("q %f 0 0 %f 0 0 cm /PosterImage Do Q", sizes[2] - sizes[0], sizes[3] - sizes[1]);
	n->appendStream(content, strlen(content));
	n->insert("Length", n->streamSize());

	float bbox_data[] = {0, 0, sizes[2] - sizes[0], sizes[3] - sizes[1]};
	Array * bbox = n->newArray(bbox_data, bbox_data +4);
	n->insert("BBox", bbox);

	Dict * resources = n->newDict("Resources");
	Array * procset = resources->newArray();
	procset->insert(Name("PDF"));
	procset->insert(Name("ImageC"));

	Dict * xobj = resources->newDict("XObject");
	Dict * pimage = xobj->newDict("PosterImage");
	BuildPosterImage (options, sizes, pimage);
}

static void
Build3DA (Dict * _3da)
{
	_3da->insert ("DIS", Name ("I"));
	_3da->insert ("AIS", Name ("L")); // <---  This is important for ANIMATION !!!!!
	_3da->insert ("A", Name ("PV"));
}

static void
BuildAnnot (HC_KEY key, char const * _3d_type, HPDFOptions * options, Dict * note, Dict * page, bool cae = false)
{
	note->insert ("Type", Name ("Annot"));
	note->insert ("Subtype", Name ("3D"));
	note->insert ("3DV", String("HOOPS Default View"));
	note->insert ("P", page);

	float sizes[] = { 
		PDF_INCHES(options->AnnotLeft()),
		PDF_INCHES(options->AnnotBottom()),
		PDF_INCHES(options->PaperWidth()) + PDF_INCHES(options->AnnotRight()),
		PDF_INCHES(options->PaperHeight()) + PDF_INCHES(options->AnnotTop()),
	};

	if(cae){
		sizes[2] -= PDF_INCHES(1.5);
		Dict * contents = 0;
		if(page->get<Dict *>("Contents", contents)){
			float colors[][3] = {
				{0,0,1},   {0, 0.333333f, 1},   {0, 0.666667f, 1},
				{0,1,1},   {0, 1,  0.666667f},  {0, 1, 0.333333f},
				{0,1,0},   {0.333333f, 1, 0},   {0.666667f, 1, 0},
				{1,1,0},   {1, 0.666667f, 0},   {1, 0.333333f, 0},
				{1,0,0},{1,1,1}
			};
			int bot = sizes[1] + PDF_INCHES(1.5);
			int top = sizes[3] - PDF_INCHES(1);
			int left = sizes[2] + PDF_INCHES(0.1);
			int right = left + PDF_INCHES(0.5);
			Graphics g;
			g.StrokeColor(0, 0, 0);
			for(int i = 0; i < 12; ++i){
				int mb = (top - bot) * (i/12.0) + bot;
				int mt = (top - bot) * ((i+1)/12.0) + bot;
				g.FillColor(colors[i][0], colors[i][1], colors[i][2]);
				g.PenPosition(left, mb);
				g.MovePen(left, mt);
				g.MovePen(right, mt);
				g.MovePen(right, mb);
				g.CloseFillAndStrokeEO();
				g.FillColor(0, 0, 0);
				g.BeginText(right +PDF_INCHES(0.1), (mb + mt) / 2.0 - 5, "Courier", 10);
				g.InsertText(0, 0, (char*)H_FORMAT_TEXT("%.0f", 500 * i/11.0));
			}
			g.FillColor(0, 0, 0);
			g.BeginText(left, top +PDF_INCHES(0.2), "Courier", 14);
			g.InsertText(0, 0, "Sample Data");
			contents->appendStream(g);
			contents->insert ("Length", (int) contents->streamSize ());
		}
	}

	Array *media_box = note->newArray (sizes, sizes + 4);
	note->insert ("Rect", media_box);

	Dict * _3dd = note->newDict("3DD");
	Build3DD (key, options, _3d_type, _3dd);

	Dict * AP = note->newDict("AP");
	BuildAP (options, sizes, AP);

	Dict * _3da = note->newDict("3DA");
	Build3DA (_3da);
}

static Dict *
BuildLinkAnnot(Dict * page, int x, int y, char const * align, float font_size, char const * text, char const * JavaScript)
{
	Dict * link = page->newDict();
	Dict * contents = 0;
	page->get<Dict*>("Contents", contents);

	link->insert("Type", Name("Annot"));
	link->insert("Subtype", Name("Link"));

	Array *link_rect = link->newArray ("Rect");
	float x1, x2, y1, y2;
	if(strchr(align, '>')){
		x1 = x - (int)((strlen(text) + 1) * font_size / 1.61803399);
		x2 = x;
	}
	else{
		x1 = x;
		x2 = x + (int)((strlen(text) + 1) * font_size / 1.61803399);
	}
	if(strchr(align, '^')){
		y1 = y - (font_size);
		y2 = y;
	}
	else {
		y1 = y;
		y2 = y + (font_size);
	}
	link_rect->insert(x1);
	link_rect->insert(y1);
	link_rect->insert(x2);
	link_rect->insert(y2);

	Dict * action = link->newDict("A");
	action->insert("Type", Name("Action"));
	action->insert("S", Name("JavaScript"));

	action->insert("JS", String(JavaScript));

	Graphics g;
	
	g.FillColor(0, 0, 1);
	g.BeginText(x1, y1, "Courier", font_size);
	g.InsertText(font_size / (2.0 * 1.61803399), 0, text);
	g.EndText();

	contents->appendStream (g);
	contents->insert ("Length", (int) contents->streamSize ());

	Dict * border = link->newDict("Border");
	border->insert("Type", Name("Border"));
	border->insert("W", 0); 

	return link;
}

static void
BuildPage1 (HC_KEY key, char const * _3d_type, HPDFOptions * options, Dict * page, Dict const *resources, bool cae = false)
{
	float media_box_data[] = { 0, 0, PDF_INCHES(options->PaperWidth()), PDF_INCHES(options->PaperHeight()) };
	Array *media_box = resources->newArray (media_box_data, media_box_data + 4);
	page->insert ("Type", Name ("Page"))->insert (Name ("Resources"),
		resources)->
		insert ("MediaBox", media_box);

	Dict * contents = page->newDict ("Contents");
	DoGraphics (options, contents);

	Dict *_3d_annot = page->newDict ();
	Array *annots = page->newArray ();
	annots->insert (_3d_annot);

	BuildAnnot (key, _3d_type, options, _3d_annot, page, cae);

	page->insert ("Annots", annots);

/* ANIMATION
 * The following JavaScript is getting the 'context3D' object from the first 3D annotation on the first page.  This
 * 'context3D' object allows access to the methods defined in the OnInstantiate script attached to the 3D annotation.
 * The OnInstantiate JavaScript is defined in script.cpp.  Note that context3D.toggleAnimation() calls toggleAnimation
 * in script.cpp (the 3D annotation's OnInstantiate script).
 */
	double const font_size = 18;
	double const left_margin = PDF_INCHES(0.5);
	double const top_margin = PDF_INCHES(options->m_fTextY);

	char const * animation_script = 0;
	HC_Open_Segment_By_Key(options->m_pHBaseView->GetModelKey());{
		if(HC_Show_Existence("user options = flip card animation")){
			animation_script = "var MyAnnote = this.getAnnots3D(0)[0];"
								"context3D = MyAnnote.context3D;"
								"context3D.toggleFlipCardAnimation();";
		}
		else {
			animation_script = "var MyAnnote = this.getAnnots3D(0)[0];"
								"context3D = MyAnnote.context3D;"
								"context3D.toggleAnimation();";
		}
	}HC_Close_Segment();

	double my_top_offset = 1 * 22;
	annots->insert(BuildLinkAnnot(page,
			PDF_INCHES(options->PaperWidth()) - left_margin,
			top_margin - my_top_offset,
			"v>",
			font_size,
			"Animate Model",
			animation_script
		));

	my_top_offset = 2 * 22;
	annots->insert(BuildLinkAnnot(page,
			PDF_INCHES(options->PaperWidth()) - left_margin,
			top_margin - my_top_offset,
			"v>",
			font_size,
			"Set ISO Camera",
			"var MyAnnote = this.getAnnots3D(0)[0];"
			"context3D =  MyAnnote.context3D;"
			"context3D.alignDefaultCamera( \"Iso\" );"
		));
}

static void
BuildPages (HC_KEY key, char const * _3d_type, HPDFOptions * options, Dict * pages, Dict const *resources, bool cae = false)
{
	Array *page_array = pages->newArray ();

	Dict *page = pages->newDict ();
	page_array->insert (page);
	page->insert ("Parent", pages);
	BuildPage1 (key, _3d_type, options, page, resources, cae);

	pages->insert ("Kids", page_array);
	pages->insert ("Count", page_array->size ());
	pages->insert ("Type", Name ("Pages"));
}


static void
SetupOneFont (Dict * resources, Name const &font_name)
{
	Dict *doc_font = resources->newDict ();
	doc_font->insert (Name ("Type"), Name ("Font"));
	doc_font->insert (Name ("Subtype"), Name ("TrueType"));
	doc_font->insert (Name ("BaseFont"), font_name);

	Dict *fonts = 0;
	if (resources->get < Dict * >(Name ("Font"), fonts))
	{
		fonts->insert (font_name, doc_font);
	}
}

static void
SetupFonts (Dict * resources)
{
	/* These are two of the build in fonts.  See the chapter on text in the PDF
	* specification for the rest of the 13 built in fonts.  */
	SetupOneFont (resources, Name ("Helvetica"));
	SetupOneFont (resources, Name ("Times-Roman"));
	SetupOneFont (resources, Name ("Courier"));
}

static void
BuildResources (Dict * resources)
{
	Name tmp[] = { "PDF", "Text", "ImageA", "ImageB", "ImageC" };
	Array *resource_array = resources->newArray ();
	resource_array->insert (tmp, tmp + 5);
	resources->insert ("ProcSet", resource_array);

	resources->newDict (Name ("Font"));
	SetupFonts (resources);
}

static char const document_script[] = {
"var waitingFor3DActivated = true;"

"function Initialize(){"
"	console.println(\"Checking if 3D Annotation is activate...\");"
"	if(waitingFor3DActivated){"
"		var a3d = getAnnots3D(0)[0];"
"		if(a3d.activated){"
"			waitingFor3DActivated = false;"
"			console.println(\"...3D Annotation is active.\");"
"			app.clearInterval(timeout);"
"			context3D = a3d.context3D;"
"			context3D.setLightScheme(\"cad\");"
"			context3D.setRenderMode(\"tranparent\");"
"		}"
"		if(timeout.count >= 60){/*seconds*/"
"			console.println(\"Giving up on 3D Annotation...\");"
"			app.clearInterval(timeout);"
"		}"
"	}"
"	timeout.count++;"
"}"

"timeout = app.setInterval(\"Initialize()\", 1000);"
"timeout.count = 0;"
};

static void
BuildNames(Dict * names)
{
	Dict * JavaScript = names->newDict("JavaScript");

	Array * name_tree = JavaScript->newArray();
	JavaScript->insert("Names", name_tree);

	Dict * js = names->newDict();
	js->insert("S", Name("JavaScript"));
	js->insert("Type", Name("Action"));

	Dict * dljs = js->newDict("JS");
	dljs->appendStream(document_script, sizeof(document_script));
	dljs->insert("Length", dljs->streamSize());

	name_tree->insert(String("Document JavaScript"));
	name_tree->insert(js);
}


static bool
output_3d_pdf (wchar_t const *pdf_filename, HC_KEY key, char const * _3d_type, HPDFOptions * options, bool cae = false)
{
	options->filename(pdf_filename);
	try {
		File pdf (pdf_filename);

		Dict * resources = pdf.newDict ();
		BuildResources (resources);

		Dict * catalog = pdf.newDict ("Root");

		Dict * names = catalog->newDict ("Names");
		BuildNames(names);

		BuildPages (key, _3d_type, options, catalog->newDict ("Pages"), resources, cae);
		catalog->insert ("Type", Name ("Catalog"));

		Dict * info = pdf.newDict ("Info");
		info->insert ("Producer", WString ("HOOPS 3D Application Framework"));

		pdf.close();
	}
	catch(...){
		return false;
	}
	return true;
}


HFileOutputResult HIOUtilityPDF::FileOutputByKey3D(const wchar_t * FileName,
												   char const * _3d_type,
												   HC_KEY key,
												   HOutputHandlerOptions * options) 
{
	bool cae = false;
	HC_Open_Segment_By_Key(options->m_pHBaseView->GetModelKey());{
		cae = 0 != HC_Show_Existence("user options = cae model");
	}HC_Close_Segment();

	if(output_3d_pdf(FileName, key, _3d_type, (HPDFOptions*)options, cae))
		return OutputOK;
	return OutputFail;
}

static
void GetPosterStream(HPDFPoster * poster,
									HOutputHandlerOptions *options,
									float const sizes[]){
	HPDFOptions * pdf_options = (HPDFOptions*)options;
	VCharArray driver_options(MVO_BUFFER_SIZE);
	HCamera camera, orig_camera;

	float SubscreenXmin = -1.0f;
	float SubscreenXmax = 1.0f;
	float SubscreenYmin = -1.0f;
	float SubscreenYmax = 1.0f;

	float window_ar = (sizes[2] - sizes[0])/(sizes[3] - sizes[1]);
	float page_ar = (sizes[2] - sizes[0])/(sizes[3] - sizes[1]);

	if (options->m_bUseSubscreen){
		if( window_ar > page_ar ){
			SubscreenYmin = -page_ar/window_ar;
			SubscreenYmax = page_ar/window_ar;
		} else {
			SubscreenXmin = -window_ar/page_ar;
			SubscreenXmax = window_ar/page_ar;
		}
	}
	
	/* this is the poster size in pixels */
	poster->width = (sizes[2] - sizes[0]);
	poster->height = (sizes[3] - sizes[1]);

	poster->length = poster->width * poster->height * 3;
	poster->data = new unsigned char[poster->length];
	HBestImageDriver dvrseg(pdf_options->View()->GetDriverType());
	if(poster->data){
		HC_KEY image_key;

		AxisMode axis_save = options->m_pHBaseView->GetAxisMode();
		options->m_pHBaseView->SetAxisMode(AxisOff);
		H_FORMAT_TEXT tmpseg("/driver/null/%d", HDB::GetUniqueID());
		HC_Open_Segment(tmpseg);{
			image_key = HC_KInsert_Image(0,0,0, "rgb",
				poster->width, poster->height, (void*)poster->data);
		}HC_Close_Segment();

		HC_Open_Segment(dvrseg);{
			HCLOCALE(sprintf (driver_options, "subscreen = (%f, %f, %f, %f)",  SubscreenXmin, SubscreenXmax, SubscreenYmin, SubscreenYmax));
			//HC_Set_Driver_Options (driver_options);
			sprintf(driver_options, 
				"isolated,"
				"no border,"
				"use window id = (image key = %s%p)",
				H_EXTRA_POINTER_FORMAT,
				(void*)image_key);
			HC_Set_Driver_Options(driver_options);
			HC_QSet_Window_Frame(".", "off");
			HC_Set_Rendering_Options("hsra=szb");
			/*	We modify the scene camera to fit the page since the scene is
				is included further down.  This means we have to save the original
				camera and restore it when we're done. */
			options->m_pHBaseView->GetCamera( &orig_camera );
			camera = orig_camera;

			// this code is needed if the aspect ratio of the
			// window changes. 
			HC_Open_Segment_By_Key(options->m_pHBaseView->GetViewKey());{
				float pixel_ratio, camera_ratio;
				HPoint test;
				test.Set(1,-1,0);
				HC_Compute_Coordinates(".", "local window", &test,"local pixels", &test);
				//set the aspect ratio of the print to be the same as the current view
				pixel_ratio = test.x/test.y;
				camera_ratio = camera.field_width/camera.field_height;
				if (pixel_ratio > camera_ratio)
					camera.field_width *= pixel_ratio/camera_ratio;
				else camera.field_height *= camera_ratio/pixel_ratio;			
			}HC_Close_Segment();

			options->m_pHBaseView->SetCamera( camera );
			HC_Include_Segment_By_Key(options->m_pHBaseView->GetSceneKey());
		}HC_Close_Segment();


		HC_Update_One_Display(dvrseg);
		float x,y,z; char format[16];
		HC_Show_Image(image_key, &x, &y, &z, format,
			&poster->width, &poster->height, (void*)poster->data);
		HC_Delete_Segment(dvrseg);
		HC_Delete_Segment(tmpseg);
		options->m_pHBaseView->SetAxisMode(axis_save);

		poster->left = 0;
		poster->right = options->m_Paper_Width + pdf_options->m_fAnnotRight - pdf_options->m_fAnnotLeft;
		poster->bottom = 0;
		poster->top = options->m_Paper_Height + pdf_options->m_fAnnotTop - pdf_options->m_fAnnotBottom;
	}
	options->m_pHBaseView->SetCamera( orig_camera );
}

//
// Copyright (c) 2005 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/hoops_dwf/source/HIOUtilityDwfExport.cpp,v 1.25 2010-11-19 00:39:06 trask Exp $
//

#pragma warning( disable : 4290 )

//[-- DWF toolkit includes
#include "dwf/Toolkit.h"
#include "dwf/package/Constants.h"
#include "dwf/package/Manifest.h"
#include "dwf/package/GlobalSection.h"
#include "dwf/package/reader/PackageReader.h"
#include "dwfcore/File.h"
#include "dwfcore/Exception.h"
#include "dwfcore/MIME.h"
#include "dwf/package/EModelSection.h" 
#include "dwf/package/EPlotSection.h"
#include "dwf/package/writer/DWF6PackageWriter.h"
#include "dwf/publisher/impl/DWFPackagePublisher.h"
//---]


#include "HIOUtilityDwfExport.h"

// standard includes
#include <math.h>

#define vlist_node_t hio_dwf_vlist_node_t 
#define vlist_t  hio_dwf_vlist_t
#define vlist_node_s hio_dwf_vlist_node_s 
#define vlist_s  hio_dwf_vlist_s
#define	vmalloc_t hio_dwf_vmalloc_t
#define	vfree_t hio_dwf_vfree_t
#define VList hio_dwf_VList
#define VStringHash hio_dwf_VStringHash
#define VHash hio_dwf_VHash
#undef VLIST_H
#undef VHASH_H
#define V_PREFIX HIO_DWF_
#undef START_LIST_ITERATION
#undef VLIST_COMPILE_TIME_ASSERT
// hoops_utils includes
#include "vhash.h"
#include "tempfile_utils.h"
#include "vlist.cpp"
#include "vhash.cpp"


// MVO includes
#include "HW3DStream.h"
#include "HUtilityTextParser.h"
#include "HIOUtilityHOOPS.h"
#include "HIOManager.h"
#include "HBaseView.h"
#include "HUtilityLocaleString.h"
#include "HW3DStreamInternal.h"




using namespace std;
using namespace DWFCore;
using namespace DWFToolkit;

#define wide_char(x)      L ## x

static void set_initial_view( DWFGraphicResource* pW3D, const HCamera* pCamera)
{
	// define the camera properties in the graphic resource
	DWFProperty oModelProp( L"", L"" );
	wchar_t zValues[64];
	float anValues[3];

	// projection
	oModelProp.setName( DWFPackagePublisher::kz_PropName_CameraProjection );
	oModelProp.setValue( (pCamera->projection[0] == 'p' ? L"1" : L"0") );
	pW3D->addProperty( &oModelProp, false );

	// position
	anValues[0] = pCamera->position.x; 
	anValues[1] = pCamera->position.y; 
	anValues[2] = pCamera->position.z; 
	_DWFCORE_SWPRINTF( zValues, 64, L"%.7G %.7G %.7G\0", anValues[0], anValues[1], anValues[2] );

	oModelProp.setName( DWFPackagePublisher::kz_PropName_CameraPosition );
	oModelProp.setValue( DWFString::RepairDecimalSeparators(zValues) );
	pW3D->addProperty( &oModelProp, false );

	// target
	anValues[0] = pCamera->target.x; 
	anValues[1] = pCamera->target.y; 
	anValues[2] = pCamera->target.z; 
	_DWFCORE_SWPRINTF( zValues, 64, L"%.7G %.7G %.7G\0", anValues[0], anValues[1], anValues[2] );

	oModelProp.setName( DWFPackagePublisher::kz_PropName_CameraTarget );
	oModelProp.setValue( DWFString::RepairDecimalSeparators(zValues) );
	pW3D->addProperty( &oModelProp, false );

	// up vector
	anValues[0] = pCamera->up_vector.x; 
	anValues[1] = pCamera->up_vector.y; 
	anValues[2] = pCamera->up_vector.z; 
	_DWFCORE_SWPRINTF( zValues, 64, L"%.7G %.7G %.7G\0", anValues[0], anValues[1], anValues[2] );

	oModelProp.setName( DWFPackagePublisher::kz_PropName_CameraUpVector );
	oModelProp.setValue( DWFString::RepairDecimalSeparators(zValues) );
	pW3D->addProperty( &oModelProp, false );

	// field
	anValues[0] = pCamera->field_width; 
	anValues[1] = pCamera->field_height; 
	anValues[2] = 0.0; 
	_DWFCORE_SWPRINTF( zValues, 64, L"%.7G %.7G\0", anValues[0], anValues[1]);

	oModelProp.setName( DWFPackagePublisher::kz_PropName_CameraField );
	oModelProp.setValue( DWFString::RepairDecimalSeparators(zValues) );
	pW3D->addProperty( &oModelProp, false );
}

static bool generate_unique_name(char * retNewName)
{
	time_t ltime;
	time( &ltime );
	sprintf(retNewName, "HOOPS_DWF_IO-%ld", ltime);
	return true;
}

static delimiter_t first_image_part[] = {"\x21-\x7E", false, "=|,|", true, false};
static delimiter_t second_image_part[] = {"\x21-\x7E", false, ",", true, false};

static void get_image_name(HC_KEY key, char *name)
{
	float dummy;
	int dummy2;
	char text[MVO_BUFFER_SIZE];
	HC_Show_Image_Size(key, &dummy, &dummy, &dummy, text, &dummy2, &dummy2 );

	HUtilityTextParser tp;    
	tp.InsertBuffer(text, strlen(text));

	char leftside[MVO_BUFFER_SIZE];
	char rightside[MVO_BUFFER_SIZE];
	while (1)
	{    
		int dlum;
		bool res = tp.ParseBuffer(leftside, (int &)dlum, first_image_part, 1);
		if (!res)
			break;
		if (tp.GetEndDelimiter() == '=')
			res = tp.ParseBuffer(rightside, (int &)dlum, second_image_part, 1);

		if (strcmp(leftside, "name") == 0)
		{
			strcpy(name, rightside);
		}
	}
}

static bool externalize_images(HC_KEY model_key, DWFEModelSection* pModelSection)
{
	HC_Open_Segment_By_Key(model_key);
		HC_Begin_Contents_Search("...", "images");
		HC_KEY image_key;
		while (HUtility::FindContents(image_key))
		{
			char image_name[MVO_BUFFER_SIZE];
			strcpy(image_name,"");
			get_image_name(image_key, image_name);
			if (streq(image_name,""))
				generate_unique_name(image_name);

			// export these to jpeg files
			wchar_t temp_tex_file[TEMPFILE_UTILS_BUFFER_SIZE];
			GenerateTempFileName(temp_tex_file, L"jpg");

			HOutputHandler *jpg_writer = HDB::GetHIOManager()->GetOutputHandler("jpg");
			HOutputHandlerOptions options;
			HFileOutputResult result = OutputFail;

			if(!jpg_writer)
				break;

			result = jpg_writer->FileOutputFromImageKey(H_ASCII_TEXT(temp_tex_file), 
															image_key, 0 );

			if( result != OutputOK )
				break;

			// create a DWF image resource and add it to EModelSection
			DWFImageResource* pImage = 
				DWFCORE_ALLOC_OBJECT( DWFImageResource( image_name,
				DWFXML::kzRole_Texture,
				DWFMIME::kzMIMEType_JPG) );

			// extras for the image
			// here we note the image has 24 bpp (color depth)
			pImage->configureImage( 24 );

			DWFFile oImageFilename( temp_tex_file );
			DWFStreamFileDescriptor* pImageFile = DWFCORE_ALLOC_OBJECT( DWFStreamFileDescriptor(oImageFilename, L"rb") );
			DWFFileInputStream* pImageFilestream = DWFCORE_ALLOC_OBJECT( DWFFileInputStream );

			pImageFile->open();
			pImageFilestream->attach( pImageFile, true );

			pImage->setInputStream( pImageFilestream );

			// drop the resource into the global section
			pModelSection->addResource(pImage, true, true, true, NULL);
		}
		HC_End_Contents_Search();
	HC_Close_Segment();		

	return true;
}

#define THUMBNAIL_WIDTH		200
#define THUMBNAIL_HEIGHT	200
static bool generate_thumbnail(HBaseView* pBaseView, DWFImageResource*& ret_pThumbnail)
{
	// NOTE: Generating thumbnail resource on a USB drive seems to be failing for some reason. It throws 
	// an exception at pThumbnailFile->open. I couldn't find any reason why it should be doing that.
	// As a workaround, I have placed a try...catch block to trap the exception - Sumit K (19-Jan-08)

	DWFStreamFileDescriptor * pThumbnailFile = 0;
	DWFFileInputStream* pThumbnailFilestream = 0;
	try
	{	
		ret_pThumbnail = 0;

		// export the scene to a small jpeg
		wchar_t temp_tex_file[MVO_BUFFER_SIZE];
		GenerateTempFileName(temp_tex_file, L"jpg");

		HOutputHandler *jpg_writer = HDB::GetHIOManager()->GetOutputHandler("jpg");
		HOutputHandlerOptions options;
		options.m_Window_Width = THUMBNAIL_WIDTH;
		options.m_Window_Height = THUMBNAIL_HEIGHT;
		options.m_Image_Dpi = 1;
		HFileOutputResult result = OutputFail;

		if(!jpg_writer)
			return false;

		result = pBaseView->FileOutput(temp_tex_file, jpg_writer, &options);

		if( result != OutputOK )
			return false;
	
		ret_pThumbnail = DWFCORE_ALLOC_OBJECT( DWFImageResource( L"HOOPS 3D Partviewer Model - Thumbnail",
										DWFXML::kzRole_Thumbnail, DWFMIME::kzMIMEType_JPG) );
		
		if (ret_pThumbnail == NULL)
			return false;

		double anTransform2[4][4] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		double anExtents2[4] = { 0, 0, THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT };

		ret_pThumbnail->configureGraphic( (const double*)anTransform2, (const double*)anExtents2 );
		ret_pThumbnail->configureImage( 24 );
		
		DWFString oDWFFilename(temp_tex_file);
		DWFFile oThumbnailFilename( oDWFFilename );
		pThumbnailFile = DWFCORE_ALLOC_OBJECT(DWFStreamFileDescriptor (oThumbnailFilename, L"rb") );
		
		if (pThumbnailFile == NULL)
		{
			DWFCORE_FREE_OBJECT( ret_pThumbnail );
			return false;
		}

		pThumbnailFilestream = DWFCORE_ALLOC_OBJECT(DWFFileInputStream);

		if (pThumbnailFilestream == NULL)
		{
			DWFCORE_FREE_OBJECT( ret_pThumbnail );
			DWFCORE_FREE_OBJECT( pThumbnailFile );
			return false;
		}

		// following line throws an exception on USB drives. Ref. to the note at the start of this function.
		pThumbnailFile->open();
		pThumbnailFilestream->attach( pThumbnailFile, true );

		ret_pThumbnail->setInputStream( pThumbnailFilestream );
	}
	catch(DWFIOException)
	{
		if( ret_pThumbnail )
		{
			DWFCORE_FREE_OBJECT( ret_pThumbnail );
			ret_pThumbnail = 0;
		}
		if ( pThumbnailFile )
			DWFCORE_FREE_OBJECT( pThumbnailFile );

		if (pThumbnailFilestream )
			DWFCORE_FREE_OBJECT( pThumbnailFilestream );

		return false;
	}
	return true;
}



HFileOutputResult HIOUtilityDwfExport::FileOutputByKey(const wchar_t * FileName, HC_KEY key, 
													   HOutputHandlerOptions * options)
{
	bool has_initial_camera = false;
	HW3DCamera hw3d_init_camera;
	
	SetStartingOutput();

	if( options )
	{
		// check to see if 2D format is required to be exported
		// if yes, relay this to HIOUtilityWhip2D
		if(!options->m_b3dOutput)
		{
			HIOUtilityWhip2D dwf_2d_exporter;
			return dwf_2d_exporter.FileOutputByKey(FileName, key, options);
		}

		if( options->m_pHBaseView )
		{
			HCamera mvo_init_camera;
			options->m_pHBaseView->GetCamera(&mvo_init_camera);

			hw3d_init_camera.position.x = mvo_init_camera.position.x;
			hw3d_init_camera.position.y = mvo_init_camera.position.y;
			hw3d_init_camera.position.z = mvo_init_camera.position.z;

			hw3d_init_camera.target.x = mvo_init_camera.target.x;
			hw3d_init_camera.target.y = mvo_init_camera.target.y;
			hw3d_init_camera.target.z = mvo_init_camera.target.z;

			hw3d_init_camera.up_vector.x = mvo_init_camera.up_vector.x;
			hw3d_init_camera.up_vector.y = mvo_init_camera.up_vector.y;
			hw3d_init_camera.up_vector.z = mvo_init_camera.up_vector.z;

			hw3d_init_camera.field_width = mvo_init_camera.field_width;
			hw3d_init_camera.field_height = mvo_init_camera.field_height;

			strcpy(hw3d_init_camera.projection, mvo_init_camera.projection);

			has_initial_camera = true;
		}
	}

	DWFFile oDWF( FileName );

	DWFSource oSource( L"", "HOOPS 3D Partviewer", L"" );
	DWFUnits oUnits(DWFUnits::eMeters);

	DWFString modelName(options->m_pDWFModelName);
	DWFEModelSection* pModelSection = DWFCORE_ALLOC_OBJECT( DWFEModelSection
										(modelName, L"123", 1, oSource, &oUnits) );

	// xref the images first
	// find out images and export them a jpegs
	externalize_images(key, pModelSection);

	// let's create the w3d file now using W3D_HOOPS module
	wchar_t temp_filename[TEMPFILE_UTILS_BUFFER_SIZE]; 
	GenerateTempFileName(temp_filename, L"w3d");

	// create an object definition resource
	DWFObjectDefinitionResource* pObjDefRes = 
		DWFCORE_ALLOC_OBJECT( DWFObjectDefinitionResource(DWFXML::kzElement_ObjectDefinition,DWFXML::kzRole_ObjectDefinition) );


	HW3D_Write_W3D_File(H_ASCII_TEXT(temp_filename), key, pObjDefRes, ((has_initial_camera)? &hw3d_init_camera:0));

	// define the resource - this must be allocated on the heap
	DWFGraphicResource* p3Dgfx = 
		DWFCORE_ALLOC_OBJECT( DWFGraphicResource(L"HOOPS 3D Model",  // title
		DWFXML::kzRole_Graphics3d,           // role
		DWFMIME::kzMIMEType_W3D,             // MIME type
		L"Tech Soft 3D",                // author
		L"Exported using HOOPS/3DF",        // description
		L"",                                 // creation time
		L"") );                              // modification time

	if(options && options->m_pHBaseView) 
	{
                // The initial camera is now directly exported into W3D stream, because the following 
                // is not working in DWF viewer - Rajesh B (02-May-06)
		// get the current camera which will be saved as the initial view
		//HCamera mvo_init_camera;
		//options->m_pHBaseView->GetCamera(&mvo_init_camera);
		//set_initial_view(p3Dgfx, &mvo_init_camera);

		// Add a thumbnail
		DWFImageResource* pThumbnail = 0;
		bool result_thumbnail = generate_thumbnail(options->m_pHBaseView, pThumbnail);
		if ((result_thumbnail == true) && pThumbnail)
			pModelSection->addResource( pThumbnail, true, true, true, p3Dgfx );
	}

	// bind the w3d file to the resource
	DWFFile oW3DFilename( temp_filename );
	DWFStreamFileDescriptor* pW3DFile = DWFCORE_ALLOC_OBJECT( DWFStreamFileDescriptor(oW3DFilename, L"rb") );
	DWFFileInputStream* pW3DFilestream = DWFCORE_ALLOC_OBJECT( DWFFileInputStream );

	// open the file and bind it to the stream
	pW3DFile->open();
	pW3DFilestream->attach( pW3DFile, true );

	// hand the stream off to the resource
	// NOTE: since we don't already know the filesize (in the application space - of course we can look on disk...)
	// leave the second parameter (nBytes) default as zero, this will tell the package writer
	// to use the number of bytes it processed through the stream as the size attribute in the descriptor.
	p3Dgfx->setInputStream( pW3DFilestream );

	// finally, drop the resource into the page
	pModelSection->addResource( p3Dgfx, true );
	pModelSection->addResource( pObjDefRes, true, true, true, p3Dgfx );

	DWF6PackageWriter oWriter( oDWF );
	oWriter.addSection( pModelSection );
	oWriter.write( L"Tech Soft 3D", L"HOOPS/3DF", L"12.x", 
		           L"Tech Soft 3D", L"12.x"  );

	//DWFCORE_FREE_OBJECT(pModelSection);

	SetFinishedOutput();

	return OutputOK;
}


static HFileOutputResult export_whip(const char * FileName, HC_KEY key, HOutputHandlerOptions * options) 
{
	char DriverPath[MVO_SEGMENT_PATHNAME_BUFFER];

	if(options->m_Window_Width <= 0 || options->m_Window_Height <= 0){
		options->m_Window_Width = 8.5;
		options->m_Window_Height = 11;
	}

	AxisMode axis_save;
	axis_save = options->m_pHBaseView->GetAxisMode();
	options->m_pHBaseView->SetAxisMode(AxisOff);

	/* append FileName to "?driver/whip2d/", enclose it in 
	* single quotes to maintain case and to protect special characters 
	* from interpretation as segment delimeters */
	sprintf(DriverPath, "%s\'%s\'", "?driver/whip2d/", FileName);	
	// now we print the file!!!
	HUtility::TwoPassPrint(DriverPath, options);
	HC_Delete_Segment(DriverPath);

	options->m_pHBaseView->SetAxisMode(axis_save);

	return OutputOK;
}

HFileOutputResult HIOUtilityWhip2D::FileOutputByKey(const wchar_t * FileName, HC_KEY key, HOutputHandlerOptions * options) 
{
	if(!FileName) 
		return OutputBadFileName;

	if(key == INVALID_KEY) 
		return OutputFail;

	if(!options)
		return OutputFail;

	if( !options->m_pHBaseView )
		return OutputFail;

	SetStartingOutput();

	// Configure Graphics
	double* anTransform = 0;
	double* anExtents = 0; 

	double paper_width =  options->m_Paper_Width <= 0 ? options->m_Window_Width : options->m_Paper_Width;
	double paper_height = options->m_Paper_Height <= 0 ? options->m_Window_Height : options->m_Paper_Height;
	double win_width = (options->m_Window_Width)*(options->m_Image_Dpi);
	double win_height = (options->m_Window_Height)*(options->m_Image_Dpi);

	double h_min[2], h_max[2];
	h_min[0] = h_min[1] = 0.0;
	double x_scale = h_max[0] = win_width;
	double y_scale = h_max[1] = win_height;
	double driver_scale = (x_scale > y_scale) ? x_scale : y_scale;

	h_min[0] = h_min[0]*LONG_MAX/driver_scale;
	h_min[1] = h_min[1]*LONG_MAX/driver_scale;
	h_max[0] = h_max[0]*LONG_MAX/driver_scale;
	h_max[1] = h_max[1]*LONG_MAX/driver_scale;

	double true_width = fabs(h_max[0] - h_min[0]);
	double true_height = fabs(h_max[1] - h_min[1]);
	double scale_x = paper_width/true_width;
	double scale_y = paper_height/true_height;
	double min_scale = (scale_x < scale_y) ? scale_x : scale_y;

	double paper_center[2] = {paper_width/2.0, paper_height/2.0};
	double dwf_center[2] = {true_width/2.0, true_height/2.0};
	double trans_X = paper_center[0] - (min_scale*dwf_center[0]);
	double trans_Y = paper_center[1] - (min_scale*dwf_center[1]);
	
	anTransform = new double[16];
	anTransform[0]  = min_scale; anTransform[1]  = 0.0      ; anTransform[2]  = 0.0; anTransform[3]  = 0;
	anTransform[4]  = 0.0      ; anTransform[5]  = min_scale; anTransform[6]  = 0.0; anTransform[7]  = 0;
	anTransform[8]  = 0.0      ; anTransform[9]  = 0.0      ; anTransform[10] = 1.0; anTransform[11] = 0;
	anTransform[12] = trans_X  ; anTransform[13] = trans_Y  ; anTransform[14] = 0.0; anTransform[15] = 1;

	anExtents = new double[4];
	anExtents[0] = h_min[0]*min_scale + trans_X;
	anExtents[1] = h_min[1]*min_scale + trans_Y;
	anExtents[2] = h_max[0]*min_scale + trans_X;
	anExtents[3] = h_max[1]*min_scale + trans_Y;


	double anPaperClip[4] = { 0, 0, paper_width, paper_height};
	DWFPaper oPaper( paper_width, paper_height, DWFPaper::eInches, 0x00ffffff, anPaperClip, true );

	DWFFile oDWF( FileName );
	DWFSource oSource( L"", "HOOPS 3D Part Viewer", L"" );

	DWFString modelName(options->m_pDWFModelName);
	DWFEPlotSection* pPage = DWFCORE_ALLOC_OBJECT( DWFEPlotSection(modelName, L"123", 1, oSource, 0x00ff00ff, &oPaper) );

	// let's create the w3d file now using W3D_HOOPS module
	wchar_t temp_filename[TEMPFILE_UTILS_BUFFER_SIZE]; 
	GenerateTempFileName(temp_filename, L"w2d");

	HFileOutputResult export_result = export_whip(H_ASCII_TEXT(temp_filename), key, options);
	if(  export_result != OutputOK )
		return export_result;

	// define the resource - this must be allocated on the heap
	DWFGraphicResource* p2Dgfx = 
		DWFCORE_ALLOC_OBJECT( DWFGraphicResource(L"HOOPS 3D Model",  // title
		DWFXML::kzRole_Graphics2d,           // role
		DWFMIME::kzMIMEType_W2D,             // MIME type
		L"Tech Soft 3D",                // author
		L"Exported using HOOPS/3DF",        // description
		L"",                                 // creation time
		L"") );                              // modification time


	p2Dgfx->configureGraphic((const double*)anTransform, (const double*)anExtents);

	H_SAFE_DELETE_ARRAY(anTransform);
	H_SAFE_DELETE_ARRAY(anExtents);

	if(options && options->m_pHBaseView) 
	{
		// get the current camera which will be saved as the initial view
		HCamera mvo_init_camera;
		options->m_pHBaseView->GetCamera(&mvo_init_camera);

		set_initial_view(p2Dgfx, &mvo_init_camera);

		// Add a thumbnail
		DWFImageResource* pThumbnail = 0;
		generate_thumbnail(options->m_pHBaseView, pThumbnail);
		if (pThumbnail)
			pPage->addResource( pThumbnail, true, true, true, p2Dgfx );
	}

	// bind the w3d file to the resource
	DWFFile oW2DFilename( temp_filename );
	DWFStreamFileDescriptor* pW2DFile = DWFCORE_ALLOC_OBJECT( DWFStreamFileDescriptor(oW2DFilename, L"rb") );
	DWFFileInputStream* pW2DFilestream = DWFCORE_ALLOC_OBJECT( DWFFileInputStream );

	// open the file and bind it to the stream
	pW2DFile->open();
	pW2DFilestream->attach( pW2DFile, true );

	// hand the stream off to the resource
	// NOTE: since we don't already know the filesize (in the application space - of course we can look on disk...)
	// leave the second parameter (nBytes) default as zero, this will tell the package writer
	// to use the number of bytes it processed through the stream as the size attribute in the descriptor.
	p2Dgfx->setInputStream( pW2DFilestream );

	// finally, drop the resource into the page
	pPage->addResource( p2Dgfx, true );

	DWF6PackageWriter oWriter( oDWF );
	oWriter.addSection( pPage );
	oWriter.write( L"Tech Soft 3D", L"HOOPS/3DF", L"12.x", 
		L"Tech Soft 3D", L"12.x"  );

	//DWFCORE_FREE_OBJECT(pModelSection);
	SetFinishedOutput();

	return OutputOK;

}

#ifdef HIO_DWF_EXPORT
void * CreateInput(HIOManager *manager)
{
	return NULL;
};

void * CreateOutput(HIOManager *manager)
{
	HIOUtilityDwfExport *handler = new HIOUtilityDwfExport();
	manager->RegisterOutputHandler("dwf",handler);
	return handler;
};

void Free(HIOUtilityDwfExport *handler)
{ 
	if(handler) 
		delete handler; 
};

#endif

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
// $Header: /files/homes/master/cvs/hoops_master/hio_skp/source/HSKPHelper.cpp,v 1.47 2010-09-27 12:27:52 mustafa Exp $
//



#include "HIOUtilitySKP.h"
#include "HSKPHelper.h"
#include "HUtility.h"
#include "HBaseView.h"

#include <tchar.h>
#include <string>
using std::string;
#include "math.h"

#define TWO_PI                  6.283185307179586476925286766559


static bool check_file_exist(const char* dir, const char* file)
{
    char full_filepath[_MAX_PATH];
    sprintf(full_filepath, "%s%s", dir, file);
    FILE* fp;
    fp = fopen(full_filepath,"r");
    if(fp!=NULL)
    {
        fclose(fp);
        return true;
    }
    else
    {
        return false;
    }
}

void convertToCharArray(_bstr_t &name, char temp_array[])
{
	BSTR str = name.Detach();
	size_t origsize = wcslen(str) + 1;
	size_t convertedChars = 0;
	wcstombs_s(&convertedChars, temp_array, origsize, str, _TRUNCATE);
	SysFreeString(str);

}

void convertToCharArray(BSTR &str, char temp_array[])
{
	size_t origsize = wcslen(str) + 1;
	size_t convertedChars = 0;
	wcstombs_s(&convertedChars, temp_array, origsize, str, _TRUNCATE);
}

void convertToCharArray(VARIANT &value, char temp_array[])
{
	char str[MVO_BUFFER_SIZE] = "";
	if(value.vt == VT_BSTR)
		sprintf(str, "%S", value.bstrVal);
	else if(value.vt == VT_I4)
		sprintf(str, "%i", value.intVal);
	else if(value.vt == VT_R8)
		sprintf(str, "%f", value.dblVal);
	
	strcpy(temp_array, str);
}


void HSKPImporter::getSegName(CComPtr<ISkpDrawingElement> pDrawable, char seg_name[])
{
	CComPtr<ISkpLayer> pLayer;
	pDrawable->get_Layer(&pLayer);
	BSTR layerName;
	pLayer->get_Name(&layerName);
	convertToCharArray(layerName,seg_name);
	conditionStringForSegName(seg_name);
	SysFreeString(layerName);
}

//void HSKPImporter::getSegName(CComPtr<ISkpEdge> pDrawable, char seg_name[])
//{
//	CComPtr<ISkpLayer> pLayer;
//	pDrawable->get_Layer(&pLayer);
//	BSTR layerName;
//	pLayer->get_Name(&layerName);
//	convertToCharArray(layerName,seg_name);
//	conditionStringForSegName(seg_name);
//}

void getRGBcolor(OLE_COLOR oleCol, double &r, double &g, double &b)
{
	BYTE R = ((BYTE)(oleCol));
	BYTE G = ((BYTE)(((WORD)(oleCol)) >> 8));
	BYTE B = ((BYTE)((oleCol)>>16));

	 r = (double)R;
	 g = (double)G;
	 b = (double)B;

	 r = r/255;
	 g = g/255;
	 b = b/255;
}



struct ATTRS
{
	const char* attr_name;
};

//Supported all UserDefined Attributes by RpReports for components
static ATTRS RpReportsAttributes[] =
{
	"Title",
	"Beshreibung",
	"Kosten",
	"Einwohnerzahl",
	"Größenklasse",
	"Abwasserreinigungsverfahren",
	"Volumen",
	"Grundfläche",
	"Oberfläche",
	"Durchmesser",
	"Gesamtkosten",
};

static ATTRS defaultAttributes[] =
{
	"UID",
	"ID",
	"NAME",
	"DESCRIPTION",
};

#define size(array)	sizeof(array)/sizeof(array[0])
#define nAttrs_RpReports		size(RpReportsAttributes)
#define nAttrs_default			size(defaultAttributes)


void setUserOption(CComPtr<ISkpAttributeProvider> pAttrprovider)
{
	if( pAttrprovider != 0)
	{
		CComPtr<ISkpAttributes> pAttrs;
		pAttrprovider->get_Attributes(&pAttrs);
		long count = 0;
		pAttrs->get_Count(&count);

		for(int i = 0; i < count; i++)
		{
			CComPtr<ISkpAttribute> pAttr;
			pAttrs->get_Item(i, &pAttr);
			CComPtr<ISkpAttributeDictionary> pAttrDic;
			pAttr->QueryInterface(IID_ISkpAttributeDictionary, (void **) &pAttrDic);
			if(pAttrDic != 0)
			{
				VARIANT value;
				char user_option[MVO_BUFFER_SIZE] = "\0";
			
				for(int i = 1; i < nAttrs_default; i++)//Import Other than UID, as UID will be imported by default
				{
					HRESULT res = pAttrDic->get_Item(bstr_t(defaultAttributes[i].attr_name), &value);
					if(res == S_OK)
					{					
						char str[MVO_BUFFER_SIZE];
						if(value.vt == VT_BSTR)
							sprintf(str, "%s=%S", defaultAttributes[i].attr_name, value.bstrVal);
						else if(value.vt == VT_I4)
							sprintf(str, "%s=%i", defaultAttributes[i].attr_name, value.intVal);
						else if(value.vt == VT_R8)
							sprintf(str, "%s=%f", defaultAttributes[i].attr_name, value.dblVal);
						strcat(user_option, str);
						strcat(user_option, ";");	
					}
				}
				
				HC_Set_User_Options(user_option);
			}
		}
	}
}

void setEntityUID(CComPtr<ISkpAttributeProvider> pAttrprovider)
{
	if( pAttrprovider != 0)
	{
		CComPtr<ISkpAttributes> pAttrs;
		pAttrprovider->get_Attributes(&pAttrs);
		long count = 0;
		pAttrs->get_Count(&count);

		for(int i = 0; i < count; i++)
		{
			CComPtr<ISkpAttribute> pAttr;
			pAttrs->get_Item(i, &pAttr);
			CComPtr<ISkpAttributeDictionary> pAttrDic;
			pAttr->QueryInterface(IID_ISkpAttributeDictionary, (void **) &pAttrDic);
			if(pAttrDic != 0)
			{
				VARIANT value;
				char user_option[MVO_BUFFER_SIZE] = "\0";
			
				HRESULT res = pAttrDic->get_Item(bstr_t(defaultAttributes[0].attr_name), &value);//Only Import UID
				
				if(res == S_OK)
				{					
					char str[MVO_BUFFER_SIZE];
					if(value.vt == VT_BSTR)
						sprintf(str, "%s=%S", defaultAttributes[i].attr_name, value.bstrVal);
					else if(value.vt == VT_I4)
						sprintf(str, "%s=%i", defaultAttributes[i].attr_name, value.intVal);
					else if(value.vt == VT_R8)
						sprintf(str, "%s=%f", defaultAttributes[i].attr_name, value.dblVal);
					strcat(user_option, str);
					strcat(user_option, ";");	
				}
				
				HC_Set_User_Options(user_option);
			}
		}
	}
}

void HSKPImporter::setTotalEntities(CComPtr<ISkpDocument> pDoc)
{
	CComPtr<ISkpEntityProvider> pEntProvider;
	pDoc->QueryInterface(IID_ISkpEntityProvider, (void **) &pEntProvider);
	CComPtr<ISkpEntities> pEntities;
	pEntProvider->get_Entities(&pEntities);
	pEntities->get_Count(&m_totalEntities); 
	
}

void HSKPImporter::WriteOptionsProvider(const char* title, CComPtr<ISkpNamedValues> pNVs)
{
    if(pNVs == NULL) 
    {
        return;
    }

    long count;
	HRESULT hr;

    hr = pNVs->get_Count(&count);

    if (count>0)
    {
        for(long i=0; i<count; i++)
        {
			CComPtr<ISkpNamedValue> pNV;
            hr = pNVs->get_Item(i, &pNV);
            BSTR bName; 
            VARIANT vValue;
            VariantInit(&vValue);

            hr = pNV->get_Name(&bName);
            hr = pNV->get_Value(&vValue);

			char val[4096];
			convertToCharArray(vValue, val);

			char Property[4096];
			convertToCharArray(bName,Property);

			if((strcmp( Property,"DisplayColorByLayer")) == 0)
			{
				convertToCharArray(vValue, val);
				if(strcmp(val, "1") == 0)
					m_bIsColorByLayer = true;
			}
			//set default front and back color for face

			double r,g,b;
			if((strcmp(Property ,"FaceBackColor")) == 0)
			{
				double back_color =atof(val);
				getRGBcolor(back_color, r, g, b);
				HC_Set_Color_By_Value( "back", "rgb", r, g, b );
			}
			if((strcmp(Property ,"FaceFrontColor")) == 0)
			{
				double front_color =atof(val);
				getRGBcolor(front_color, r, g, b);
				HC_Set_Color_By_Value( "front", "rgb", r, g, b );
			}

            SysFreeString(bName);
            VariantClear(&vValue);
        }
    }
}

void HSKPImporter::setDefaultOptions(CComPtr<ISkpDocument> pDoc)
{
	HRESULT hr;

	CComPtr<ISkpOptionsManager> pOptManager;
	hr = pDoc->get_OptionsManager(&pOptManager);

	long count;
	hr = pOptManager->get_Count(&count);

	if (count>0)
	{
		VARIANT vNum;
		::VariantInit(&vNum);
		vNum.vt = VT_I4;
		for(long i=0; i<count; i++)
		{
			CComPtr<ISkpOptionsProvider> pProvider;

			vNum.lVal = i;
			hr = pOptManager->get_Item(vNum, &pProvider);

			// write the option provider
			CComPtr<ISkpNamedValues> pNamedOptions;
			hr = pProvider->QueryInterface(IID_ISkpNamedValues, (void**)&pNamedOptions);

			BSTR bProviderName;
			hr = pProvider->get_Name(&bProviderName);
			_bstr_t szProviderName(bProviderName, true);

			WriteOptionsProvider((const char*)szProviderName, pNamedOptions);

			SysFreeString(bProviderName);
		}
	}
}

HSKPImporter::HSKPImporter(CComPtr<ISkpTextureWriter> textureWriter)
{
	m_bIsColorByLayer = false;
	m_bIsPartofComponentOrGroup = false;
	m_bSkpFitworld = false;
	m_pReader = HDB::GetHIOManager()->GetInputHandler("jpg");
	m_pTextureWriter = NULL;
	strcpy(m_ctexture_path, "Nothing");
	m_pTextureWriter = textureWriter;
	ignoreOffEntities = false;
	m_bImportMetadata = false;
	m_bIsCompTex = false;
	m_bIsGroupTex = false;
}

HSKPImporter::~HSKPImporter()
{	
	m_pTextureWriter.Release();
}


CComPtr<ISkpDocument> HSKPImporter::getSKPDatabase(const char * FileName, CComPtr<ISkpApplication> pApp)
{
  	CComPtr<ISkpFileReader> pFileReader;
	pApp->QueryInterface(IID_ISkpFileReader, (void **) &pFileReader);
	CComPtr<ISkpDocument> pDoc;
	pFileReader->OpenFile(_bstr_t(FileName), &pDoc);

	return pDoc;
}

void HSKPImporter::setTextureDirectory()
{
	char dir[MVO_BUFFER_SIZE];
	GetTempPath(MVO_BUFFER_SIZE,dir);
	char* outDir = dir;
	strcat(outDir,"SkpTextures");
	CreateDirectory(outDir, NULL);
	deleteDirectory(outDir);
	strcpy(m_cTextureDirectory, outDir);
}


BOOL HSKPImporter::deleteDirectory(const TCHAR* sPath)
{
	HANDLE hFind;    // file handle
	WIN32_FIND_DATA FindFileData;

	TCHAR DirPath[MAX_PATH];
	TCHAR FileName[MAX_PATH];

	_tcscpy(DirPath,sPath);
	_tcscat(DirPath,"\\*");    // searching all files
	_tcscpy(FileName,sPath);
	_tcscat(FileName,"\\");

	// find the first file
	hFind = FindFirstFile(DirPath,&FindFileData);
	if(hFind == INVALID_HANDLE_VALUE) return FALSE;
	_tcscpy(DirPath,FileName);

	bool bSearch = true;
	while(bSearch) {    // until we find an entry
		if(FindNextFile(hFind,&FindFileData)) {
			if(isDots(FindFileData.cFileName)) continue;
			_tcscat(FileName,FindFileData.cFileName);
			if((FindFileData.dwFileAttributes &
				FILE_ATTRIBUTE_DIRECTORY)) {

					// we have found a directory, recurse
					if(!deleteDirectory(FileName)) {
						FindClose(hFind);
						return FALSE;    // directory couldn't be deleted
					}
					// remove the empty directory
					RemoveDirectory(FileName);
					_tcscpy(FileName,DirPath);
			}
			else {
				//if(FindFileData.dwFileAttributes &
				//	FILE_ATTRIBUTE_READONLY)
				//	// change read-only file mode
				//	_chmod(FileName, _S_IWRITE);
					if(!DeleteFile(FileName)) {    // delete the file
					FindClose(hFind);
					return FALSE;
				}
				_tcscpy(FileName,DirPath);
			}
		}
		else {
			// no more files there
			if(GetLastError() == ERROR_NO_MORE_FILES)
				bSearch = false;
			else {
				// some error occurred; close the handle and return FALSE
				FindClose(hFind);
				return FALSE;
			}

		}

	}
	FindClose(hFind);                  // close the file handle

	return true;     // remove the empty directory

}
BOOL HSKPImporter::isDots(const TCHAR* str)
{
	if(_tcscmp(str,".") && _tcscmp(str,"..")) return FALSE;
	return TRUE;
}

void HSKPImporter::importSKPPages(CComPtr<ISkpDocument> pDoc,HInputHandlerOptions * InputHandlerOptions)
{
	CComPtr<ISkpPages> pages;
	pDoc->get_Pages(&pages);
	long pages_count = 0;
	pages->get_Count(&pages_count);
	if (pages_count && InputHandlerOptions)
	{
		if(InputHandlerOptions->m_pHBaseView)
		{
			CComPtr<ISkpPage> page;
			HRESULT success = pages->get_SelectedPage(&page);

			if(!page)
				return;

			CComPtr<ISkpCamera> camera;
			page->get_Camera(&camera);

			CComPtr<ISkpPoint3d>  eye;
			camera->get_Eye(&eye);

			CComPtr<ISkpPoint3d>  skp_target;
			camera->get_Target(&skp_target);

			CComPtr<ISkpVector3d> skp_up;
			camera->get_Up(&skp_up);

			CComPtr<ISkpVector3d> skp_dir;
			camera->get_Direction(&skp_dir);

			CComPtr<ISkpPoint3d>  skp_center;
			camera->get_Center(&skp_center);

			double tempX, tempY, tempZ;
			
			HPoint eye_position;
			eye->Get(&tempX, &tempY, &tempZ);
			eye_position.Set(tempX, tempY, tempZ);

			HPoint target;
			skp_target->Get(&tempX, &tempY, &tempZ);
			target.Set(tempX, tempY, tempZ);

			HPoint up_vector;
			skp_up->Get(&tempX, &tempY, &tempZ);
			up_vector.Set(tempX, tempY, tempZ);

			HPoint center;
			skp_center->Get(&tempX, &tempY, &tempZ);
			center.Set(tempX, tempY, tempZ);

			HPoint dir_vector;
			skp_dir->Get(&tempX, &tempY, &tempZ);
			dir_vector.Set(tempX, tempY, tempZ);

			HPoint line_vector;
			skp_center->Get(&tempX, &tempY, &tempZ);
			line_vector.Set(tempX - eye_position.x, tempY - eye_position.y, tempZ-eye_position.z);

			double  FieldOfView =0;
			camera->get_FieldOfView(&FieldOfView);
			double  height = 0;
			camera->get_Height(&height);
			
			HPoint  normalized_dir_vec,normalized_line_vec;
			HC_Compute_Normalized_Vector(&dir_vector,&normalized_dir_vec);
			HC_Compute_Normalized_Vector(&line_vector,&normalized_line_vec);
			
			double angle_view=HUtility::ComputeAngleBetweenVector(&normalized_dir_vec,&normalized_line_vec);
				
			double view_height=abs(HC_Compute_Vector_Length(&line_vector)*tan((angle_view*TWO_PI)/360.0));

			//Not sure if following is right way to calculate width but since there is lack of data following is the approximation
			double view_width=(FieldOfView/height)*view_height;
			
			HC_Open_Segment_By_Key(InputHandlerOptions->m_pHBaseView->GetSceneKey());
				HC_Set_Camera(&eye_position,&target,&up_vector,view_width,view_height,"perspective");
			HC_Close_Segment();

			//This is for smoke tests
			HC_Open_Segment_By_Key(InputHandlerOptions->m_pHBaseView->GetViewKey());
				HC_Set_Camera(&eye_position,&target,&up_vector,view_width,view_height,"perspective");
			HC_Close_Segment();

			InputHandlerOptions->m_pHBaseView->HasInitialView(true);
		}
	}
	else
	{
		//Default initial view is not supported for the files not haveing scenes/pages due to lack of data to calculate
		//view width and so instead I am calling fitWorld// Mustafa Bohari[29-SEP-08]
		m_bSkpFitworld = true;
	}
}

void  HSKPImporter::fitToScene(HInputHandlerOptions * options)
{
	if(m_bSkpFitworld == true && options->m_pHBaseView != 0)
		options->m_pHBaseView->FitWorld();
}

void HSKPImporter::importSKPEdgesInComponent(CComPtr<ISkpEntityProvider> pEntProvider)
{
	CComPtr<ISkpEdges> pEdges;
	pEntProvider->get_Edges(&pEdges);

	long edge_count = 0;
	pEdges->get_Count(&edge_count);

	for(int i = 0; i<edge_count; i++)
	{
		CComPtr<ISkpEdge> pEdge;
		pEdges->get_Item(i, &pEdge);
		CComPtr<ISkpDrawingElement> pDrawable;
		pEdge->QueryInterface(IID_ISkpDrawingElement, (void **)&pDrawable);

		BOOL isEdgevisible;
		pDrawable->get_IsVisible(&isEdgevisible);
		BOOL isSoft;
		pEdge->get_IsSoft(&isSoft);


		if(ignoreOffEntities == true)
		{
			if(isEdgevisible == FALSE || isSoft == TRUE )
				continue;//forget the import of this entity
		}

		CComPtr<ISkpLayer> pLayer;
		pDrawable->get_Layer(&pLayer);

		char layer_name[4096];
		getSegName(pDrawable, layer_name);

		bool isLayerSegOpened = false;
		BOOL isLayerVisible;
		pLayer->get_IsVisible(&isLayerVisible);

		if(strcmp(layer_name, "Layer0") != 0 && isLayerVisible == 0 )
		{
			if(ignoreOffEntities == true)
				continue;
			else
			{
				HC_Open_Segment("invisible layer");
				HC_Set_Visibility("everything = off");
				isLayerSegOpened = true;
			}
		}
		{
			CComPtr<ISkpPoint3d> startPoint;
			pEdge->get_StartPoint(&startPoint);

			CComPtr<ISkpPoint3d> endPoint;
			pEdge->get_EndPoint(&endPoint);

			bool isLineSegOpened = false;
			
			if(isEdgevisible == FALSE || isSoft == TRUE )
			{
				HC_Open_Segment("invisible edge");
				HC_Set_Visibility("everything = off");
				isLineSegOpened = true;
			}
			{
				HPoint hStartPoint, hEndpoint;
				double tempX, tempY, tempZ;

				startPoint->Get(&tempX, &tempY, &tempZ); 
				hStartPoint.Set(tempX, tempY, tempZ);

				endPoint->Get(&tempX, &tempY, &tempZ); 
				hEndpoint.Set(tempX, tempY, tempZ);

				HC_Insert_Line(hStartPoint.x, hStartPoint.y, hStartPoint.z, 
					hEndpoint.x, hEndpoint.y, hEndpoint.z);

				CComPtr<ISkpAttributeProvider> attProv;
				pEdge->QueryInterface(IID_ISkpAttributeProvider, (void **)&attProv);
				setEntityUID(attProv);
				if(m_bImportMetadata)
				{
					setUserOption(attProv);
				}
			}

			if(isLineSegOpened)
				HC_Close_Segment();//close line segment
		}
		if(isLayerSegOpened)
			HC_Close_Segment();//close layer segment
	}
}

void HSKPImporter::importEdges(char* geometrySeg_name, CComPtr<ISkpEdges> pEdges, int i, int edgesIncurve_count)
{
	HC_Open_Segment(geometrySeg_name);
	{
		for(int j = 0; j< edgesIncurve_count; j++)
		{
			
			CComPtr<ISkpEdge> pEdge;
			HRESULT	hr =  pEdges->get_Item(i + j, &pEdge);

			if (hr != S_OK)
				continue;

			CComPtr<ISkpDrawingElement> pDrawable;
			pEdge->QueryInterface(IID_ISkpDrawingElement, (void **)&pDrawable);

			BOOL is_Visible = 0;
			pDrawable->get_IsVisible(&is_Visible);

			BOOL is_Soft = 0;
			pEdge->get_IsSoft(&is_Soft);

			if(is_Visible == 0 )
			{
				HC_Set_Visibility("everything = off");
			}

			HPoint hStart, hEnd;
			double tempX, tempY, tempZ;

			CComPtr<ISkpPoint3d> startPoint;
			pEdge->get_StartPoint(&startPoint);
			startPoint->Get(&tempX, &tempY, &tempZ);
			hStart.Set(tempX, tempY, tempZ);

			CComPtr<ISkpPoint3d> endPoint;
			pEdge->get_EndPoint(&endPoint);
			endPoint->Get(&tempX, &tempY, &tempZ);
			hEnd.Set(tempX, tempY, tempZ);

			HC_Insert_Line(hStart.x, hStart.y, hStart.z, 
				hEnd.x, hEnd.y, hEnd.z);

			CComPtr<ISkpAttributeProvider> attProv;
			pEdge->QueryInterface(IID_ISkpAttributeProvider, (void **)&attProv);
			setEntityUID(attProv);
			if(m_bImportMetadata)
			{
				setUserOption(attProv);
			}
		}
	}
	HC_Close_Segment();//close geometry segment
}

void HSKPImporter::importSKPEdges(CComPtr<ISkpEntityProvider> pEntProvider)
{
	char geometrySeg_name[MVO_BUFFER_SIZE] ;
	char entity_name[100] = "";
	double prev_x,prev_y,prev_z;
	prev_x=prev_y=prev_z=0.0;
	int freehand_counter = 0;
	long prev_key=INVALID_KEY;

	CComPtr<ISkpEdges> pEdges;
	pEntProvider->get_Edges(&pEdges);
	long edge_count;
	pEdges->get_Count(&edge_count);
	for(int i = 0; i<edge_count; i++)
	{
		//Update progress bar
		m_pInputhandler->ReportInputPercentProgress(m_pInputhandler->GetInputPercentProgress() + 
												0.67*(1.0f/(float)m_totalEntities));
		
	
		CComPtr<ISkpEdge> pEdge;
		pEdges->get_Item(i, &pEdge);

		CComPtr<ISkpDrawingElement> pDrawable;
		pEdge->QueryInterface(IID_ISkpDrawingElement, (void **)&pDrawable);

		BOOL is_Visible = 0;
		pDrawable->get_IsVisible(&is_Visible);

		BOOL is_Soft = 0;
		pEdge->get_IsSoft(&is_Soft);

		BOOL is_LayerVisible = 0;
		CComPtr<ISkpLayer> pLayer;
		pDrawable->get_Layer(&pLayer);
		pLayer->get_IsVisible(&is_LayerVisible);

	    if(ignoreOffEntities == true)
		{
			if(is_Visible == FALSE || is_LayerVisible == FALSE)
				continue;//forget the import of this entity
		}

		CComPtr<ISkpCurve> pCurve;
		HRESULT isNotFreeHand = pEdge->get_Curve(&pCurve);

		if(isNotFreeHand == S_OK)
		{
		
			//Open segment with layer name
			char layer_name[4096];
			getSegName(pDrawable, layer_name);
			
			HC_Open_Segment(layer_name);
			{
				if(is_LayerVisible == 0 )
				{
					HC_Set_Visibility("everything = off");
				}
				
				CComPtr<ISkpEdges> pEdgesinCurve ; 
				HRESULT isValidCurve = pCurve->get_Edges(&pEdgesinCurve);
				long edgesIncurve_count = 0;

				//Deduce the type of entity like circle/arc/polygon etc and oprn the segment
				if(isValidCurve == S_OK)
				{
					pEdgesinCurve->get_Count(&edgesIncurve_count);
					//i = i + (edgesIncurve_count - 1);

					CComPtr<ISkpArcCurve> pArcCurve;
					pCurve->QueryInterface(IID_ISkpArcCurve, (void **) &pArcCurve);
					
					// get_IsFullCircle seems to be deprecated with SKP8(latest) api 
					//hence removed its usage. Mustafa B(27-Sep-10)
					BOOL isFullCircle = true;
					//pArcCurve->get_IsFullCircle(&isFullCircle);
		
					if(pCurve && isFullCircle && edgesIncurve_count == 24)
					{
						CComPtr<ISkpEdges> pCurveEdges ; 
						HRESULT result = pCurve->get_Edges(&pCurveEdges);
						if(result == S_OK)
						{
							strcpy(entity_name, "circle");
						}
					}
					else
					{
						if(edgesIncurve_count == 12)
						{
							strcpy(entity_name, "arc");
						}
						else if(edgesIncurve_count == 6)
						{
							strcpy(entity_name, "polygon");
						}
						else 
						{
							strcpy(entity_name, "curve");
						}
					}
				}
				else
				{
					strcpy(entity_name, "edge");
					edgesIncurve_count = 1;
				}
				
				CComPtr<ISkpEntity> pEntity;
				pEdge->QueryInterface(IID_ISkpEntity, (void **) &pEntity);
				long EntId = 0;
				pEntity->get_Id(&EntId);
				sprintf(geometrySeg_name, "%s_%d", entity_name, EntId);

				importEdges(geometrySeg_name, pEdges, i, edgesIncurve_count);
				i = i + (edgesIncurve_count - 1);
										
			}
			HC_Close_Segment();//close layer segment
		}
		else//Freehand curves
		{
			CComPtr<ISkpPoint3d> startPoint;
			pEdge->get_StartPoint(&startPoint);
			CComPtr<ISkpPoint3d> endPoint;
			pEdge->get_EndPoint(&endPoint);

			char layer_name[4096] ;
			getSegName(pDrawable, layer_name);

			HC_Open_Segment(layer_name);
			{
				if(is_LayerVisible == 0 )
				{
					HC_Set_Visibility("everything = off");
				}
				
				CComPtr<ISkpEntity> pEntity;
				pEdge->QueryInterface(IID_ISkpEntity, (void **)&pEntity);
				long pEntID;
				pEntity->get_Id(&pEntID);
				sprintf(geometrySeg_name, "freeHand_curves_%d", pEntID);
				
				bool isFreeHandsegOpened = false;
				double startX, startY, startZ;
				startPoint->Get(&startX, &startY, &startZ);

				if ((prev_x==startX)&&(prev_y==startY)&&(prev_z==startZ)&& freehand_counter != 0)
				{
					HC_Open_Segment_By_Key(prev_key);
					isFreeHandsegOpened = true;
				}
				else
				{
					freehand_counter++;
					prev_key=HC_KOpen_Segment(geometrySeg_name);
					isFreeHandsegOpened = true;
				}

				endPoint->Get(&prev_x, &prev_y, &prev_z);

				if(is_Visible == 0 )
				{
					HC_Set_Visibility("everything = off");
				}
				HC_Insert_Line(startX, startY, startZ, 
					prev_x, prev_y, prev_z);

				CComPtr<ISkpAttributeProvider> attProv;
				pEdge->QueryInterface(IID_ISkpAttributeProvider, (void **)&attProv);
				setEntityUID(attProv);
				if(m_bImportMetadata)
				{
					setUserOption(attProv);
				}

				if(isFreeHandsegOpened)
					HC_Close_Segment();//close free hand segment
			}
			HC_Close_Segment();//close layer segment
		}
		
	}

}


double HSKPImporter::round(double x)
{
	double n;
	if (fabs(modf(x, &n)) >= 0.5) {
		if (x >= 0) return (ceil(x));
		else return (floor(x));
	}
	else {
		if (x >= 0) return (floor(x));
		else return (ceil(x));
	}
}

void HSKPImporter::importSKPImage(CComPtr<ISkpEntityProvider> pEntProvider, bool fromCompOrGroup)
{
	bool isTextureWritten = true;

	CComPtr<ISkpImages> pImages;
	pEntProvider->get_Images(&pImages);

	long image_count = 0;
	pImages->get_Count(&image_count);

	for( int i = 0; i<image_count; i++)
	{
		//Update progress bar
		if(!fromCompOrGroup)
		{
			m_pInputhandler->ReportInputPercentProgress(m_pInputhandler->GetInputPercentProgress() + 
													0.67*(1.0f/(float)m_totalEntities));
		}

		CComPtr<ISkpImage> pImage;
		HRESULT hr = pImages->get_Item(i, &pImage);

		CComPtr<ISkpDrawingElement> pDrawable;
		pImage->QueryInterface(IID_ISkpDrawingElement, (void **)&pDrawable);

		BOOL is_Visible = 0;
		pDrawable->get_IsVisible(&is_Visible);

		if(ignoreOffEntities == true && is_Visible == 0)
			continue;//forget the import of this entity

		BOOL is_LayerVisible = 0;
		CComPtr<ISkpLayer> pLayer;
		pDrawable->get_Layer(&pLayer);

		pLayer->get_IsVisible(&is_LayerVisible);

		char filename_out[MVO_BUFFER_SIZE];
		char dir_out[MVO_BUFFER_SIZE];
		
		char layer_name[4096];
		getSegName(pDrawable, layer_name);
		
		//Open layer segment and set visibility governed by following conditions
		bool isLayerSegOpened = false;
		if(ignoreOffEntities == true && is_LayerVisible == 0)
		{
			if(m_bIsPartofComponentOrGroup == false )
				continue;
			else if(m_bIsPartofComponentOrGroup == true && strcmp(layer_name, "Layer0") != 0)
				continue;
		}
		else if(ignoreOffEntities == true && is_LayerVisible != 0)
		{
			if(m_bIsPartofComponentOrGroup == false)
			{
				HC_Open_Segment(layer_name);
				isLayerSegOpened = true;
			}
		}
		else if(ignoreOffEntities == false && is_LayerVisible == 0)
		{
			if(m_bIsPartofComponentOrGroup == false)
			{
				HC_Open_Segment(layer_name);
				HC_Set_Visibility("everything = off");
				isLayerSegOpened = true;
			}
			else if( m_bIsPartofComponentOrGroup == true && strcmp(layer_name, "Layer0") == 0)
			{
				HC_Open_Segment(layer_name);
				isLayerSegOpened = true;
			}
			else if ( m_bIsPartofComponentOrGroup == true && strcmp(layer_name, "Layer0") != 0)
			{
				HC_Open_Segment("invisible layer");
				HC_Set_Visibility("everything = off");	
				isLayerSegOpened = true;
			}
		}
		else if(ignoreOffEntities == false && is_LayerVisible != 0)
		{
			if(m_bIsPartofComponentOrGroup == false)
			{
				HC_Open_Segment(layer_name);
				isLayerSegOpened = true;
			}
		}

		{
			//import color of layer if valid
			double r, g, b;
			if(m_bIsColorByLayer == true)
			{
				// if the face is part of the component and if its on layer0 
				//then we have to apply color of its components layer if colorBylayer is set to on
				if(strcmp(layer_name, "Layer0") == 0 && m_bIsPartofComponentOrGroup == true)
					getRGBcolor(m_rCompOrGroupLayerColor, r, g, b); 
				else
				{
					CComPtr<ISkpMaterial> pLayerMat;
					pLayer->get_Material(&pLayerMat);
					OLE_COLOR layer_color;
					pLayerMat->get_Color(&layer_color);
					getRGBcolor(layer_color, r, g, b); 
					//pLayerMat.Release();
				}
				HC_Set_Color_By_Value( "faces", "rgb", r, g, b );

			}

			BSTR fileName;
			pImage->get_Path(&fileName);
			char texture_name[MVO_BUFFER_SIZE];
			convertToCharArray(fileName, texture_name);
			SysFreeString(fileName);
			
			HUtility::FindFileNameAndDirectory(texture_name,  dir_out,  filename_out);
			//conditionStringForSegName(filename_out);
					

			char file_out[MVO_BUFFER_SIZE];
			HC_Parse_String(filename_out, ".", 0,file_out);

			TCHAR fname[MVO_BUFFER_SIZE];
			sprintf(fname,"%s\\%s.png",m_cTextureDirectory,file_out);
			_bstr_t bName = fname;
			TCHAR file_onlyname[MVO_BUFFER_SIZE];
			sprintf(file_onlyname,"%s.png", file_out);
			//file_onlyname.Format(_T("%s.png"),file_out);

			bool isFileExist = check_file_exist(fname,"");

			if (!isFileExist)
			{
				HRESULT front_result;
				long image_handel;
				m_pTextureWriter->LoadImageA(pImage, &image_handel);
				if (image_handel>0)
				{
					try{
					front_result = m_pTextureWriter->WriteTextureFileFromHandle(image_handel,bName);
					}
					catch(...)
					{
						isTextureWritten = false;
					}
					if(front_result == S_OK)
					{
						HC_KEY this_style = HC_KOpen_Segment("/include library/SKPTextures");
						HC_Close_Segment();//?
						m_rInputOptions.m_pImageName=file_onlyname;
						HFileInputResult result = m_pReader->FileInputToImageKey(fname, &m_rImageKey, this_style, &m_rInputOptions);
						if(result == InputOK)
						{
							char texture_def[MVO_BUFFER_SIZE];
							sprintf (texture_def," source = %s",file_onlyname);
							HC_Define_Texture(file_onlyname,texture_def);
						}
					}

				}
			}

			char seg_name[MVO_BUFFER_SIZE];
			sprintf(seg_name,"Image_%s_%d",file_out,i);

			double 	Width = 0;
			pImage->get_Width(&Width);
			double 	Height = 0;
			pImage->get_Height(&Height);
			double 	ZRotation = 0;
			pImage->get_ZRotation(&ZRotation);
			ZRotation = ZRotation*(180/3.14);

			CComPtr<ISkpVector3d> vector3dPtr;
			pImage->get_Normal(&vector3dPtr);
			CComPtr<ISkpPoint3d> Origin;
			pImage->get_Origin(&Origin);

			HPoint Origin_hoops;
			double tempX, tempY, tempZ;
			Origin->Get(&tempX, &tempY, &tempZ);
			Origin_hoops.Set(tempX, tempY, tempZ);

			HPoint xaxis(1.0f,0.0f,0.0f),yaxis(0.0f,1.0f,0.0f),zaxis(0.0f,0.0f,1.0f);
			HPoint Nxaxis(-1.0f,0.0f,0.0f),Nyaxis(0.0f,-1.0f,0.0f),Nzaxis(0.0f,0.0f,-1.0f);

			HPoint model_plan;
			vector3dPtr->Get(&tempX, &tempY, &tempZ);
			model_plan.Set(round(tempX), round(tempY), round(tempZ));
			HPoint Image_shell[4];

			if (model_plan.operator ==(xaxis))
			{
				Image_shell[0].Set(0.0,0.0,0.0);
				Image_shell[1].Set(0.0,Width,0.0);
				Image_shell[2].Set(0.0,Width,Height);
				Image_shell[3].Set(0.0,0.0,Height);

			} 
			else if (model_plan.operator ==(yaxis))
			{
				Image_shell[0].Set(0.0,0.0,0.0);
				Image_shell[1].Set(-Width,0.0,0.0);
				Image_shell[2].Set(-Width,0.0,Height);
				Image_shell[3].Set(0.0,0.0,Height);

			}
			else if (model_plan.operator ==(zaxis))
			{
				Image_shell[0].Set(0.0,0.0,0.0);
				Image_shell[1].Set(Width,0.0,0.0);
				Image_shell[2].Set(Width,Height,0.0);
				Image_shell[3].Set(0.0,Height,0.0);

			}
			else if (model_plan.operator ==(Nxaxis))
			{
				Image_shell[0].Set(0.0,0.0,0.0);
				Image_shell[1].Set(0.0,-Width,0.0);
				Image_shell[2].Set(0.0,-Width,Height);
				Image_shell[3].Set(0.0,0.0,Height);

			} 
			else if (model_plan.operator ==(Nyaxis))
			{
				Image_shell[0].Set(0.0,0.0,0.0);
				Image_shell[1].Set(Width,0.0,0.0);
				Image_shell[2].Set(Width,0.0,Height);
				Image_shell[3].Set(0.0,0.0,Height);

			}
			else if (model_plan.operator ==(Nzaxis))
			{
				Image_shell[0].Set(0.0,0.0,0.0);
				Image_shell[1].Set(-Width,0.0,0.0);
				Image_shell[2].Set(-Width,Height,0.0);
				Image_shell[3].Set(0.0,Height,0.0);

			}

			if(Image_shell)
			{
				bool isImageSegOpened = false;
				if(m_bIsPartofComponentOrGroup == false)
				{
					HC_Open_Segment(seg_name);
					isImageSegOpened = true;
				}
				{
					if(is_Visible == 0)
					{
						if(m_bIsPartofComponentOrGroup == true)
						{
							HC_Open_Segment("invisible image");
							isImageSegOpened = true;
						}

						HC_Set_Visibility("everything=off");
					}

					transformPointsFromRotationTranslate(&ZRotation,&model_plan,Image_shell,&Origin_hoops);
					//HC_Translate_Object(Origin_hoops.x,Origin_hoops.y,Origin_hoops.z);
					int flist[5]={4,0,1,2,3};
					HC_KEY shell_key = HC_KInsert_Shell(4, Image_shell, 5, flist);
					float hpoint_fTexCords[]={0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f};
					HC_MSet_Vertex_Parameters(shell_key, 0, 4, 2, hpoint_fTexCords); 

					CComPtr<ISkpAttributeProvider> attProv;
					pImage->QueryInterface(IID_ISkpAttributeProvider, (void **)&attProv);
					setEntityUID(attProv);
					if(m_bImportMetadata)
					{
						setUserOption(attProv);
					}

					if(isTextureWritten)
					{
						sprintf(m_ccolor_opts, "faces = %s", file_onlyname);
						HC_Set_Color(m_ccolor_opts);
					}
				}
				if(isImageSegOpened)
					HC_Close_Segment();//Close Image segment
			}
		}
		if(isLayerSegOpened)
			HC_Close_Segment();//Close layer segment

	}

}


void HSKPImporter::transformPointsFromRotationTranslate(double *angle,HPoint* axis, HPoint* points,HPoint* origin)
{
	float rotation_translation_matrix[4][4];
	HPoint out_points[4];
	
	HC_Compute_Offaxis_Rotation(axis->x,axis->y,axis->z,*angle,&rotation_translation_matrix[0][0]);
	HC_Compute_Transformed_Points(4,points,&rotation_translation_matrix[0][0],out_points);
	HC_Compute_Translation_Matrix(origin->x,origin->y,origin->z,&rotation_translation_matrix[0][0]);
	HC_Compute_Transformed_Points(4,out_points,&rotation_translation_matrix[0][0],points);

}


void HSKPImporter::defineTexture(char * filename_out, long texture_handle)
{
	char texture_def[MVO_BUFFER_SIZE];
	char texture_name_back[MVO_BUFFER_SIZE];
	
	sprintf(texture_name_back,"back_%s",filename_out);
	strcpy(texture_def,"");
	sprintf(texture_def,"source = %s, parameter offset=3",filename_out);
	bool already_there = false;

	//if it is already there in scene
	pair<set<long>::iterator, bool> ret;
	ret = m_setBackTextureHandles.insert(texture_handle);

	
	if(ret.second == true)
		HC_Define_Local_Texture(texture_name_back,texture_def);
	
}


void HSKPImporter::importSKPFaces(CComPtr<ISkpEntityProvider> pEntProvider, bool fromCompOrGroup)
{
	CComPtr<ISkpFaces> pFaces;
	pEntProvider->get_Faces(&pFaces);
	long face_count = 0;
	pFaces->get_Count(&face_count);
	char backface_transmission[MVO_BUFFER_SIZE];
	char frontface_transmission[MVO_BUFFER_SIZE];
	double front_r,front_g,front_b;
	double back_r,back_g,back_b;
	bool isTextureWritten = true;

	for( int i = 0; i<face_count; i++)
	{
		//Update progress bar
		if(!fromCompOrGroup)
		{
			m_pInputhandler->ReportInputPercentProgress(m_pInputhandler->GetInputPercentProgress() + 
													0.67*(1.0f/(float)m_totalEntities));
		}
		
		CComPtr<ISkpFace> pFace;
		pFaces->get_Item(i, &pFace);

		//Find out if the face has texture applied on it

		CComPtr<ISkpMaterial> pFrontMat;
		BOOL isFrontTex = FALSE;

		HRESULT isFrontMat = pFace->get_FrontMaterial(&pFrontMat);
		if(isFrontMat == S_OK && pFrontMat)
		{
			pFrontMat->get_IsTexture(&isFrontTex);
		}

		CComPtr<ISkpMaterial> pBackMat;
		BOOL isBackTex = FALSE;
		HRESULT isBackMat = pFace->get_BackMaterial(&pBackMat);
		if(isBackMat == S_OK && pBackMat)
		{
			pBackMat->get_IsTexture(&isBackTex);
		}
		

		CComPtr<ISkpDrawingElement> pDrawable;
		pFace->QueryInterface(IID_ISkpDrawingElement, (void **)&pDrawable);

		BOOL is_visible = 0;
		pDrawable->get_IsVisible(&is_visible);

		if(ignoreOffEntities == true && is_visible == 0)
			continue;//forget the import of this entity

		strcpy(backface_transmission,"");
		strcpy(frontface_transmission,"");
		front_r=front_g=front_b=0.0;
		back_r=back_g=back_b=0.0;
		
		BOOL is_LayerVisible = 0;
		CComPtr<ISkpLayer> pLayer;
		pDrawable->get_Layer(&pLayer);

		pLayer->get_IsVisible(&is_LayerVisible);

		char layer_name[4096];
		getSegName(pDrawable, layer_name);


		/*if(stricmp(layer_name, "Layer0") == 0)
				int h = 0;*/
		
		//Open layer segment and set visibility governed by following conditions
		bool isLayerSegOpened = false;
		if(ignoreOffEntities == true && is_LayerVisible == 0)
		{
			if(m_bIsPartofComponentOrGroup == false )
				continue;
			else if(m_bIsPartofComponentOrGroup == true && strcmp(layer_name, "Layer0") != 0)
				continue;
		}
		else if(ignoreOffEntities == true && is_LayerVisible != 0)
		{
			if(m_bIsPartofComponentOrGroup == false)
			{
				HC_Open_Segment(layer_name);
				isLayerSegOpened = true;
			}
		}
		else if(ignoreOffEntities == false && is_LayerVisible == 0)
		{
			if(m_bIsPartofComponentOrGroup == false)
			{
				HC_Open_Segment(layer_name);
				HC_Set_Visibility("everything = off");
				isLayerSegOpened = true;
			}
			else if( m_bIsPartofComponentOrGroup == true && strcmp(layer_name, "Layer0") == 0)
			{
				HC_Open_Segment(layer_name);
				isLayerSegOpened = true;
			}
			else if ( m_bIsPartofComponentOrGroup == true && strcmp(layer_name, "Layer0") != 0)
			{
				HC_Open_Segment("invisible layer");
				HC_Set_Visibility("everything = off");	
				isLayerSegOpened = true;
			}
		}
		else if(ignoreOffEntities == false && is_LayerVisible != 0)
		{
			if(m_bIsPartofComponentOrGroup == false)
			{
				HC_Open_Segment(layer_name);
				isLayerSegOpened = true;
			}
		}

		{
			//import color of layer if valid
			double r, g, b;
			if(m_bIsColorByLayer == true)
			{
				// if the face is part of the component and if its on layer0 
				//then we have to apply color of its components layer if colorBylayer is set to on:Mustafa Bohari
				if(strcmp(layer_name, "Layer0") == 0 && m_bIsPartofComponentOrGroup == true)
					getRGBcolor(m_rCompOrGroupLayerColor, r, g, b); 
				else
				{
					CComPtr<ISkpMaterial> pLayerMat;
					pLayer->get_Material(&pLayerMat);
					OLE_COLOR layer_color;
					pLayerMat->get_Color(&layer_color);
					getRGBcolor(layer_color, r, g, b); 
				}
				HC_Set_Color_By_Value( "faces", "rgb", r, g, b );

			}

			char seg_name[4096];
			CComPtr<ISkpEntity> pEntity;
			pFace->QueryInterface(IID_ISkpEntity, (void **) &pEntity);
			long EntId = 0;
			pEntity->get_Id(&EntId);
			sprintf(seg_name, "face_%d", EntId);
			
			bool isFaceSegOpened = false;
			if(m_bIsPartofComponentOrGroup == false)
			{
				HC_Open_Segment(seg_name);//Geometry segment
				isFaceSegOpened = true;
			}
			{
				long handle;
				m_pTextureWriter->LoadFace(pFace, true, &handle);
                CComPtr<ISkpCorrectPerspective> perspective;
				m_pTextureWriter->QueryInterface(IID_ISkpCorrectPerspective, (void **)&perspective);
                
                CComPtr<ISkpUVHelper> uvHelper;
                pFace->GetUVHelper(PolygonMeshUVQFront, PolygonMeshUVQBack, perspective, &uvHelper);

                CComPtr<ISkpPolygonMesh> pPolyMesh;
				pFace->CreateMeshWithUVHelper(PolygonMeshUVQFront|
                    PolygonMeshUVQBack|PolygonMeshNormals, uvHelper, &pPolyMesh);

				long num_points = 0;
				pPolyMesh->get_NumPoints(&num_points);
				HPoint* hpoints = new HPoint[num_points];
				HPoint* hpoint_normals  = new HPoint[num_points];
				float* hpoint_TexCords  = new float[num_points*6];
				
				for(int j =1; j <= num_points; j++)
				{
					CComPtr<ISkpPoint3d> point;
					pPolyMesh->get_Point(j, &point);
					double tempX, tempY, tempZ;
					point->Get(&tempX, &tempY, &tempZ);
					hpoints[(j-1)].Set(tempX, tempY, tempZ);

					//point->Get((double *)&hpoints[(j-1)].x, (double *)&hpoints[(j-1)].y, (double *)&hpoints[(j-1)].z );
					

					CComPtr<ISkpVector3d> pNormal;
					HRESULT result = pPolyMesh->get_VertexNormal(j,&pNormal);
					pNormal->Get(&tempX, &tempY, &tempZ);
					hpoint_normals[(j-1)].Set(tempX, tempY, tempZ);
					//pNormal->Get((double *)&hpoint_normals[(j-1)].x, (double *)&hpoint_normals[(j-1)].y, (double *)&hpoint_normals[(j-1)].z );

					if(isFrontTex || isBackTex /*|| m_bIsCompTex || m_bIsGroupTex*/)
					{
						//Get Texture coordinates
						CComPtr<ISkpPoint3d> pFrontUV;
						HRESULT result_FrontUVPoint = pPolyMesh->get_FrontUVPoint(j, &pFrontUV);

						CComPtr<ISkpPoint3d> pBackUV;
						HRESULT result_BackUVPoint = pPolyMesh->get_BackUVPoint(j, &pBackUV);

						//prepare combined array having front and back texture coordinates
						//pFrontUV->Get((double *)&hpoint_TexCords[6*(j-1)], (double *)&hpoint_TexCords[6*(j-1)+1], (double *)&hpoint_TexCords[6*(j-1)+2] );
						pFrontUV->Get(&tempX, &tempY, &tempZ);
						hpoint_TexCords[6*(j-1)+0] = (float)tempX;
						hpoint_TexCords[6*(j-1)+1] = (float)tempY;
						hpoint_TexCords[6*(j-1)+2] = (float)tempZ;

						pBackUV->Get(&tempX, &tempY, &tempZ);
						hpoint_TexCords[6*(j-1)+3] = (float)tempX;
						hpoint_TexCords[6*(j-1)+4] = (float)tempY;
						hpoint_TexCords[6*(j-1)+5] = (float)tempZ;

						//pBackUV->Get((double *)&hpoint_TexCords[6*(j-1)+3], (double *)&hpoint_TexCords[6*(j-1)+4], (double *)&hpoint_TexCords[6*(j-1)+5] );
					}

				}
				//Get coneectivity of faces
				long num_poly = 0;
				pPolyMesh->get_NumPolygons(&num_poly);
				int* flist = new int[(num_poly*4)];
				for (int i = 1; i<=num_poly; i++)
				{
					flist[4*(i-1)] = 3;
					for (int j =1; j <= 3; j++)
					{
						long val;
						pPolyMesh->GetPolygonPointIndex(i, j, &val);
						flist[4*(i-1)+j] = (int)((abs(val))-1);
					}
				}
				if(is_visible == 0)
				{
					if(m_bIsPartofComponentOrGroup == true)
					{
						HC_Open_Segment("invisible face");
						isFaceSegOpened = true;
					}

					HC_Set_Visibility("everything=off");
				}
				HC_KEY shell_key = HC_KInsert_Shell(num_points, hpoints, (num_poly*4), flist);
				HC_MSet_Vertex_Normals(shell_key, 0, num_points, hpoint_normals);
							
				if(isFrontTex || isBackTex /*|| m_bIsCompTex || m_bIsGroupTex*/)
				{
					HC_MSet_Vertex_Parameters(shell_key, 0, num_points, 6, hpoint_TexCords); 
				}

				if(pFrontMat || pBackMat)
				{
					HC_Open_Geometry(shell_key);
					{
						applyMaterialOnFace(pFace);
					}
					HC_Close_Geometry();
				}

				CComPtr<ISkpAttributeProvider> attProv;
				pFace->QueryInterface(IID_ISkpAttributeProvider, (void **)&attProv);
				setEntityUID(attProv);
				if(m_bImportMetadata)
				{
					setUserOption(attProv);
				}
								
				H_SAFE_DELETE_ARRAY(flist);
				H_SAFE_DELETE_ARRAY(hpoints);
				H_SAFE_DELETE_ARRAY(hpoint_normals);
				H_SAFE_DELETE_ARRAY(hpoint_TexCords); 
			}
			if(isFaceSegOpened)
				HC_Close_Segment();//close face segment
		}
		if(isLayerSegOpened)
			HC_Close_Segment();//close layer segment
		
	}

}

void HSKPImporter::setModelKey(HC_KEY key)
{
	m_model_key=key;
}


void HSKPImporter::importSKPGroups(CComPtr<ISkpEntityProvider> pEntProvider, bool fromCompOrGroup)
{
	m_bIsGroupTex = false;
	CComPtr<ISkpGroups> pGroups;
	pEntProvider->get_Groups(&pGroups);
	long group_count = 0;
	pGroups->get_Count(&group_count);
	for (int group_counter = 0; group_counter < group_count; group_counter++)
	{
		//Update progress bar
		if(!fromCompOrGroup)
		{
			m_pInputhandler->ReportInputPercentProgress(m_pInputhandler->GetInputPercentProgress() + 
													0.67*(1.0f/(float)m_totalEntities));
		}

		CComPtr<ISkpGroup> pGroup;
		pGroups->get_Item(group_counter, &pGroup);

		
		CComPtr<ISkpDrawingElement> pDrawable;
		pGroup->QueryInterface(IID_ISkpDrawingElement, (void **)&pDrawable);

		BOOL is_visible = 0;
		pDrawable->get_IsVisible(&is_visible);

		if(ignoreOffEntities == true && is_visible == 0)
			continue;//forget the import of this entity

		//Open Segment with layer of the group
		char layer_name[4096];
		getSegName(pDrawable, layer_name);
		
		BOOL is_LayerVisible = 0;
		CComPtr<ISkpLayer> pLayer;
		pDrawable->get_Layer(&pLayer);

		pLayer->get_IsVisible(&is_LayerVisible);


		bool isLayerSegOpened = false;
		if(is_LayerVisible == 0)
		{
			if(ignoreOffEntities == true)
				continue;
			else
			{
				HC_Open_Segment(layer_name);
				HC_Set_Visibility("everything = off");
				isLayerSegOpened = true;
			}
		}
		else
		{
			HC_Open_Segment(layer_name);
			isLayerSegOpened = true;
		}
		{
			char group_segname[MVO_BUFFER_SIZE];
			char groupName[MVO_BUFFER_SIZE];
			BSTR str;
			pGroup->get_Name(&str);
			convertToCharArray(str, groupName);
			SysFreeString(str);

			CComPtr<ISkpEntity> pEntity;
			pGroup->QueryInterface(IID_ISkpEntity, (void **) &pEntity);
			long EntId = 0;
			pEntity->get_Id(&EntId);

			if (strcmp(groupName, "") == 0)
				sprintf(group_segname, "group_%d", EntId);
			else
			{
				conditionStringForSegName(groupName);
				sprintf(group_segname, "%s_%d", groupName,EntId);
			}

			HC_Open_Segment(group_segname);//Open group segment
			{
				if(is_visible == 0)
					HC_Set_Visibility("everything = off");

				//import color applied to component
				CComPtr<ISkpMaterial> pGroupMat;
				pDrawable->get_Material(&pGroupMat);
				if(pGroupMat)
				{
					char pGroupMat_transmission[MVO_BUFFER_SIZE];

					BOOL bIsTexture = 0;
					pGroupMat->get_IsTexture(&bIsTexture);

					BOOL bUses_Alfa = 0;
					pGroupMat->get_UsesAlpha(&bUses_Alfa);
					double pGroupAlpha = 1.0;
					pGroupMat->get_Alpha(&pGroupAlpha);

					if(bIsTexture)
					{
						m_bIsGroupTex = true;
						m_cFaceSide = "faces";

						char filename_out[MVO_BUFFER_SIZE];
						char dir_out[MVO_BUFFER_SIZE];
						//int result =  getSKPTexture(pFrontMat);


						//ToDo: Move this code to getSKPTexture()
						CComPtr<ISkpTextureWriter2> pTextureWrite2;
						m_pTextureWriter->QueryInterface(IID_ISkpTextureWriter2, (void **) &pTextureWrite2);

						long texture_handle;
						pTextureWrite2->LoadGroup(pGroup, &texture_handle);

						if (texture_handle>0)
						{
							CComPtr<ISkpTexture> pTexture;
							pGroupMat->get_Texture(&pTexture);
							BSTR fileName;
							pTexture->get_Filename(&fileName);
							char texture_name[MVO_BUFFER_SIZE];
							convertToCharArray(fileName, texture_name);
							SysFreeString(fileName);

							HUtility::FindFileNameAndDirectory(texture_name,  dir_out,  filename_out);
							//conditionStringForSegName(filename_out);
							

							sprintf(m_ctexture_path,"%s\\%s", m_cTextureDirectory,filename_out);
							bool isFileExist = check_file_exist(m_ctexture_path,"");
							if (!isFileExist)
							{
								HRESULT front_result=	pTextureWrite2->WriteTextureFileFromHandle(texture_handle,(_bstr_t)(m_ctexture_path));
								if(front_result == S_OK)
								{
									HC_KEY this_style = HC_KOpen_Segment("/include library/SKPTextures");
									HC_Close_Segment();
									m_rInputOptions.m_pImageName=filename_out;
									HFileInputResult result = m_pReader->FileInputToImageKey(m_ctexture_path, &m_rImageKey, this_style, &m_rInputOptions);
								}
							}

							//Applying parameterization source = natural uv is workaround for now
							//until we found a way to import texture coordinates correctly when texture is applied 
							//to group or component : Mustafa Bohari
							char texDef[MVO_BUFFER_SIZE];
							sprintf(texDef, "source = %s, parameterization source = natural uv", filename_out);
							HC_Define_Local_Texture("groupTex", texDef);
							sprintf(m_ccolor_opts, "%s = %s", m_cFaceSide, "groupTex");
							HC_Set_Color(m_ccolor_opts);

							if (bUses_Alfa)
							{
								sprintf(pGroupMat_transmission, "faces=(transmission = r=%f g=%f b=%f)",(1.0-pGroupAlpha),(1.0-pGroupAlpha),(1.0-pGroupAlpha));
								HC_Set_Color(pGroupMat_transmission);
							}
							
						}	
					}
					else
					{
						OLE_COLOR group_color;
						pGroupMat->get_Color(&group_color);
						double r, g, b;
						getRGBcolor(group_color, r, g, b); 
						HC_Set_Color_By_Value( "faces", "rgb", r, g, b );

						if (bUses_Alfa)
						{
							sprintf(pGroupMat_transmission, "faces=(transmission = r=%f g=%f b=%f)",(1.0-pGroupAlpha),(1.0-pGroupAlpha),(1.0-pGroupAlpha));
							HC_Set_Color(pGroupMat_transmission);
						}
						
					}
				}

				//Apply trnasform if any

				CComPtr<ISkpTransform> pTrans ;
				HRESULT isTransform = pGroup->get_Transform(&pTrans);
				if(isTransform == S_OK)
				{
					double trans_matrix[16];
					pTrans->GetData(trans_matrix);
					float hTransMatrix[16];
					for(int i =0; i< 16; i++)
						hTransMatrix[i] = (float) trans_matrix[i];

					HC_Set_Modelling_Matrix(hTransMatrix);

				}

				m_bIsPartofComponentOrGroup = true;
				pLayer->get_Color(&m_rCompOrGroupLayerColor);
				
				CComPtr<ISkpEntityProvider> pEntProvider;
				pGroup->QueryInterface(IID_ISkpEntityProvider, (void **) &pEntProvider);

				importSKPImage(pEntProvider, true);
				importSKPEdgesInComponent(pEntProvider);
				importSKPFaces(pEntProvider, true);
				importSKPGroups(pEntProvider, true);
				importSKPComponents(pEntProvider, true);

				//HC_Optimize_Segment_Tree (".", "merge shells = on, reorganize = (color = on)");


				CComPtr<ISkpAttributeProvider> attProv;
				pGroup->QueryInterface(IID_ISkpAttributeProvider, (void **)&attProv);
				setEntityUID(attProv);
				if(m_bImportMetadata)
				{
					setUserOption(attProv);
				}

				m_bIsPartofComponentOrGroup = false;
			}
			HC_Close_Segment();//close group segment
		}
		if(isLayerSegOpened)
			HC_Close_Segment();//Close layer segment
	}
}

void HSKPImporter::conditionStringForSegName(char* zString)
{
	
	int i = 0;
	int j = 0;

	bool isSpecialChar = false;
	while (zString[j] != 0)
	{
		switch(zString[j])
		{
			case ',':
			case '\'':
			case '\"':
			case '/':
			case '*':
			case '~':
			case '|':
			case '!':
			case '=':
			case ')':
			case '(':
			case '`':
			case '@':
			case '?':
				
				isSpecialChar = true;
				break;
		}

		if(isSpecialChar)
			break; // if there is only one special character, that's enough
		j++;
	}

	if(isSpecialChar)
	{
		i = 0;
		j = 0;
		char pIn[1024] = "";
		pIn[i++] = '`';
		while (zString[j] != 0)
		{	
			pIn[i++] = zString[j];	
			j++;
		}
		pIn[i++] = '`';
		strcpy(zString, pIn);
	}
	//else do nothing
	
}

void HSKPImporter::importSKPComponents(CComPtr<ISkpEntityProvider> pEntProvider, bool fromCompOrGroup)
{
	m_bIsCompTex = false;
	bool isTextureWritten = true;
	CComPtr<ISkpComponentInstances> pInstances;
	pEntProvider->get_ComponentInstances(&pInstances);
	long instances_count = 0;
	pInstances->get_Count(&instances_count);
	for(int instance_counter =0; instance_counter<instances_count; instance_counter++)
	{
		//Update progress bar
		if(!fromCompOrGroup)
		{
			m_pInputhandler->ReportInputPercentProgress(m_pInputhandler->GetInputPercentProgress() + 
													0.67*(1.0f/(float)m_totalEntities));
		}

		CComPtr<ISkpComponentInstance> pInstance;
		pInstances->get_Item(instance_counter, &pInstance);

		CComPtr<ISkpDrawingElement> pDrawable;
		pInstance->QueryInterface(IID_ISkpDrawingElement, (void **)&pDrawable);

		BOOL is_visible = 0;
		pDrawable->get_IsVisible(&is_visible);

		BOOL is_LayerVisible = 0;
		CComPtr<ISkpLayer> pLayer;
		pDrawable->get_Layer(&pLayer);

		pLayer->get_IsVisible(&is_LayerVisible);

		if(ignoreOffEntities == true && is_visible == 0)
			continue;//forget the import of this entity
		
		CComPtr<ISkpComponentDefinition> pCompDef;
		pInstance->get_ComponentDefinition(&pCompDef);
		
		BSTR compIns_name;
		pCompDef->get_Name(&compIns_name);
		char seg_name[4096] ;
		convertToCharArray(compIns_name, seg_name);
		SysFreeString(compIns_name);

		//import component defs in include library
		
		HC_Open_Segment("/include library/component definitions");
		char seg_path[4096];
		conditionStringForSegName(seg_name);	
		sprintf(seg_path, "/include library/component definitions/%s", seg_name);

		char segname [4096];
		HC_Begin_Segment_Search("*");
		int seg_count = 0;
		while(HC_Find_Segment(segname))
		{
			int isEqual = (_stricmp (segname, 	seg_path));

			if(isEqual == 0)
			{
				seg_count++;
				break;
			}
		}
		
		//import color applied to component
		CComPtr<ISkpMaterial> pCompMat;
		pDrawable->get_Material(&pCompMat);
		BOOL IsCompTexture = 0;
		if(pCompMat)
		{
			pCompMat->get_IsTexture(&IsCompTexture);
			if(IsCompTexture)
			{ 
				m_bIsCompTex = true;
			}
		}

		if(seg_count == 0)
		{
			HC_Open_Segment(seg_name);
				m_bIsPartofComponentOrGroup = true;
				pLayer->get_Color(&m_rCompOrGroupLayerColor);

				CComPtr<ISkpEntityProvider> pEntProvider;
				pCompDef->QueryInterface(IID_ISkpEntityProvider, (void **) &pEntProvider);

				importSKPImage(pEntProvider, true);
				importSKPEdgesInComponent(pEntProvider);
				importSKPFaces(pEntProvider, true);
				importSKPGroups(pEntProvider, true);
				importSKPComponents(pEntProvider, true);

			   // HC_Optimize_Segment_Tree (".", "merge shells = on");//, reorganize = (color = on)"

			m_bIsPartofComponentOrGroup = false;

			HC_Close_Segment();
		}

		HC_End_Segment_Search ();

		HC_Close_Segment();

		//import component instances
		char component_segname[4096];
		CComPtr<ISkpEntity> pEntity;
		pInstance->QueryInterface(IID_ISkpEntity, (void **) &pEntity);
		long EntId = 0;
		pEntity->get_Id(&EntId);

		if(stricmp(seg_name,""))
		{
			sprintf(component_segname, "%s_%d", seg_name, EntId);
		}
		else
		{
			sprintf(component_segname, "Component_%d", EntId);
		}


		//Open Segment with layer of the component
		char layer_name[4096];
		getSegName(pDrawable, layer_name);
		bool isLayerSegOpened = false;
		if(is_LayerVisible == 0)
		{
			if(ignoreOffEntities == true)
				continue;
			else
			{
				HC_Open_Segment(layer_name);
				HC_Set_Visibility("everything = off");
				isLayerSegOpened = true;
			}
		}
		else
		{
			HC_Open_Segment(layer_name);
			isLayerSegOpened = true;
		}
		{
			HC_Open_Segment(component_segname);//open component segment
			{
				if(is_visible == 0)
					HC_Set_Visibility("everything = off");

				//CComPtr<ISkpOptionsProvider> pOpProvider = pCompDef;
				CComPtr<ISkpAttributeProvider> pAttrprovider;
				pInstance->QueryInterface(IID_ISkpAttributeProvider, (void **) &pAttrprovider);
				if( pAttrprovider != 0 && m_bImportMetadata)
				{
					CComPtr<ISkpAttributes> pAttrs;
					pAttrprovider->get_Attributes(&pAttrs);
					long count = 0;
					pAttrs->get_Count(&count);

					for(int i = 0; i < count; i++)
					{
						CComPtr<ISkpAttribute> pAttr;
						pAttrs->get_Item(i, &pAttr);
						CComPtr<ISkpAttributeDictionary> pAttrDic;
						pAttr->QueryInterface(IID_ISkpAttributeDictionary, (void **)&pAttrDic);

						VARIANT value;
						char user_option[MVO_BUFFER_SIZE] = "\0";
						for(int i = 0; i < nAttrs_RpReports; i++)
						{
							HRESULT res = pAttrDic->get_Item(_bstr_t(RpReportsAttributes[i].attr_name), &value);

							if(res == S_OK)
							{					
								char str[MVO_BUFFER_SIZE];
								if(value.vt == VT_BSTR)
									sprintf(str, "%s=%S", RpReportsAttributes[i].attr_name, value.bstrVal);
								else if(value.vt == VT_I4)
									sprintf(str, "%s=%i", RpReportsAttributes[i].attr_name, value.intVal);
								else if(value.vt == VT_R8)
									sprintf(str, "%s=%f", RpReportsAttributes[i].attr_name, value.dblVal);
								strcat(user_option, str);
								strcat(user_option, ";");	
							}
						}
						HC_Set_User_Options(user_option);
					}
				}

				//import color applied to component
			
				if(pCompMat)
				{
					char pCompMat_transmission[MVO_BUFFER_SIZE];

					BOOL bUses_Alfa = 0;
					pCompMat->get_UsesAlpha(&bUses_Alfa);
					double pCompAlpha = 1.0;
					pCompMat->get_Alpha(&pCompAlpha);

					if(IsCompTexture)
					{
						m_cFaceSide = "faces";

						char filename_out[MVO_BUFFER_SIZE];
						char dir_out[MVO_BUFFER_SIZE];
						//int result =  getSKPTexture(pFrontMat);

						//ToDo: Move this code to getSKPTexture()

						long texture_handle;
						m_pTextureWriter->LoadComponentInstance(pInstance, &texture_handle);
						if (texture_handle>0)
						{
							CComPtr<ISkpTexture> pTexture;
							pCompMat->get_Texture(&pTexture);
							BSTR fileName;
							pTexture->get_Filename(&fileName);
							char texture_name[MVO_BUFFER_SIZE];
							convertToCharArray(fileName, texture_name);
							SysFreeString(fileName);

							HUtility::FindFileNameAndDirectory(texture_name,  dir_out,  filename_out);
							//conditionStringForSegName(filename_out);
									

							sprintf(m_ctexture_path,"%s\\%s", m_cTextureDirectory,filename_out);
							bool isFileExist = check_file_exist(m_ctexture_path,"");
							if (!isFileExist)
							{
								isTextureWritten = true;
								HRESULT front_result;
								try{
								front_result =	m_pTextureWriter->WriteTextureFileFromHandle(texture_handle,(_bstr_t)(m_ctexture_path));
								}
								catch(...)
								{
									isTextureWritten = false;
								}
								if(front_result == S_OK)
								{
									HC_KEY this_style = HC_KOpen_Segment("/include library/SKPTextures");
									HC_Close_Segment();
									m_rInputOptions.m_pImageName=filename_out;
									HFileInputResult result = m_pReader->FileInputToImageKey(m_ctexture_path, &m_rImageKey, this_style, &m_rInputOptions);
								}
							}

							if(isTextureWritten)
							{
								char texDef[MVO_BUFFER_SIZE];
								
								//Applying parameterization source = natural uv is workaround for now
								//until we found a way to import texture coordinates correctly when texture is applied 
								//to group or component : Mustafa Bohari
								sprintf(texDef, "source = %s, parameterization source = natural uv", filename_out);
								HC_Define_Local_Texture("compTex", texDef);
								sprintf(m_ccolor_opts, "%s = %s", m_cFaceSide, "compTex");

								HC_Set_Color(m_ccolor_opts);
							}

							if (bUses_Alfa)
							{
								sprintf(pCompMat_transmission, "faces=(transmission = r=%f g=%f b=%f)",(1.0-pCompAlpha),(1.0-pCompAlpha),(1.0-pCompAlpha));
								HC_Set_Color(pCompMat_transmission);
							}
							
						}	
					}
					else
					{
						OLE_COLOR comp_color;
						pCompMat->get_Color(&comp_color);
						double r, g, b;
						getRGBcolor(comp_color, r, g, b); 
						HC_Set_Color_By_Value( "faces", "rgb", r, g, b );

						if (bUses_Alfa)
						{
							sprintf(pCompMat_transmission, "faces=(transmission = r=%f g=%f b=%f)",(1.0-pCompAlpha),(1.0-pCompAlpha),(1.0-pCompAlpha));
							HC_Set_Color(pCompMat_transmission);
						}
						
					}
				}

				CComPtr<ISkpTransform> pTrans ;
				HRESULT isTransform = pInstance->get_Transform(&pTrans);
				if(isTransform == S_OK)
				{
					double trans_matrix[16];
					pTrans->GetData(trans_matrix);
					float hTransMatrix[16];
					for(int i =0; i< 16; i++)
						hTransMatrix[i] = (float) trans_matrix[i];

					HC_Set_Modelling_Matrix(hTransMatrix);
				}

				sprintf(seg_path, "/include library/component definitions/%s", seg_name);
				HC_Include_Segment(seg_path);

				CComPtr<ISkpAttributeProvider> attProv;
				pInstance->QueryInterface(IID_ISkpAttributeProvider, (void **)&attProv);
				setEntityUID(attProv);
				if(m_bImportMetadata)
				{
					setUserOption(attProv);
				}

			}
			HC_Close_Segment();//component segment
		}
		if(isLayerSegOpened)
			HC_Close_Segment();//layer segment
		
	}
}

void HSKPImporter::importSKPText(CComPtr<ISkpEntityProvider> pEntProvider)
{
	CComPtr<ISkpTexts> pTexts;
	pEntProvider->get_Texts(&pTexts);
	long text_count = 0;
	pTexts->get_Count(&text_count);
	for(int i = 0; i < text_count; i++)
	{
		CComPtr<ISkpText> pText;
		pTexts->get_Item(i, &pText);
		BSTR text_string;
		pText->get_Text(&text_string);
		BOOL val;
		HRESULT HR = pText->get_DisplayLeader(&val);
		CComPtr<ISkpFont> pFont;
		HR = pText->get_DrawingFont(&pFont);
	/*	BSTR font_face;
		pFont->get_FontFace(&font_face);*/
		double pLeaderStartPoint, pLeaderEndPoint, pExtensionEndPoint, pTextOffsetPoint;
		CComPtr<ISkpPoint3d> pLeaderStartPoint1, pLeaderEndPoint1, pExtensionEndPoint1, pTextOffsetPoint1;

		/*SkpTextJustification * just;
		SkpTextAlignment *   	 align;*/
		pText->_GetLeaderPoints(NULL, &pLeaderStartPoint, &pLeaderEndPoint, &pExtensionEndPoint, &pTextOffsetPoint
			, 0, 0);
		pText->LeaderPoints(NULL, &pLeaderStartPoint1, &pLeaderEndPoint1, &pExtensionEndPoint1, &pTextOffsetPoint1
			, 0, 0);
		char skp_text[MVO_BUFFER_SIZE];
		convertToCharArray(text_string, skp_text);
		HC_Insert_Text(0, 0, 0, skp_text);
		SysFreeString(text_string);
	}

}

void HSKPImporter::applyMaterialOnFace(CComPtr<ISkpFace> pFace)
{
	bool isTextureWritten = true;
	char backface_transmission[MVO_BUFFER_SIZE] = "";
	char frontface_transmission[MVO_BUFFER_SIZE] = "";

	double front_r,front_g,front_b;
	double back_r,back_g,back_b;
	front_r=front_g=front_b=0.0;
	back_r=back_g=back_b=0.0;

	// get material of entity
	if(m_bIsColorByLayer == false)
	{
		CComPtr<ISkpMaterial> pFrontMat;
		HRESULT if_exist = pFace->get_FrontMaterial(&pFrontMat);
		CComPtr<ISkpMaterial> pBackMat;
		pFace->get_BackMaterial(&pBackMat);

		if(pFrontMat)
		{	
			double pFrontAlpha = 1.0;
			BOOL bUses_Alfa = 0;
			pFrontMat->get_UsesAlpha(&bUses_Alfa);
			if (bUses_Alfa)
			{
				pFrontMat->get_Alpha(&pFrontAlpha);
			}

			if (!pBackMat&&(pFrontAlpha<1.0))
			{
				m_cFaceSide="faces";
			} 
			else
			{
				m_cFaceSide = "front";
			}

			BOOL bIs_Texture = 0;
			pFrontMat->get_IsTexture(&bIs_Texture);
			if(bIs_Texture)
			{
				char filename_out[MVO_BUFFER_SIZE];
				long texture_handle;

				m_pTextureWriter->LoadFace(pFace, TRUE, &texture_handle);
				if (texture_handle>0)
				{
					CComPtr<ISkpTexture> pTexture;
					pFrontMat->get_Texture(&pTexture);

					// Get the texture added in hoops scene
					isTextureWritten = AddtextureInScene(pTexture, texture_handle, filename_out);

					if(isTextureWritten)
					{
						sprintf(m_ccolor_opts, "%s = %s", m_cFaceSide, filename_out);
						HC_Set_Color(m_ccolor_opts);
					}

					if (bUses_Alfa)
					{
						sprintf(frontface_transmission, "%s=(transmission = r=%f g=%f b=%f)",m_cFaceSide,(1.0-pFrontAlpha),(1.0-pFrontAlpha),(1.0-pFrontAlpha));
						HC_Set_Color(frontface_transmission);
					}
					
				}
	
			}
			else
			{
				OLE_COLOR front_color;
				pFrontMat->get_Color(&front_color);
				getRGBcolor(front_color, front_r, front_g, front_b);
				HC_Set_Color_By_Value( m_cFaceSide, "rgb",front_r, front_g, front_b );
				if (bUses_Alfa)
				{
					sprintf(frontface_transmission, "%s=(transmission = r=%f g=%f b=%f)",m_cFaceSide,(1.0-pFrontAlpha),(1.0-pFrontAlpha),(1.0-pFrontAlpha));
					HC_Set_Color(frontface_transmission);
				}
				
			}
		}

		//HC_Set_Rendering_Options("transparency =(sty)
		if(pBackMat)
		{
			double pBackAlpha=1.0;
			BOOL bUses_Alfa = 0;
			pBackMat->get_UsesAlpha(&bUses_Alfa);

			if (bUses_Alfa)
			{
				pBackMat->get_Alpha(&pBackAlpha);
			}

			if (!pFrontMat&&(pBackAlpha<1.0))
			{
				m_cFaceSide="faces";
			} 
			else
			{
				m_cFaceSide = "back";
			}

			BOOL bIs_Texture = 0;
			pBackMat->get_IsTexture(&bIs_Texture);
			if(bIs_Texture)
			{					
				char filename_out[MVO_BUFFER_SIZE];
				long texture_handle;
				m_pTextureWriter->LoadFace(pFace, FALSE, &texture_handle);
				if (texture_handle>0)
				{
					CComPtr<ISkpTexture> pTexture;
					pBackMat->get_Texture(&pTexture);

					// Get the texture added in hoops scene
					isTextureWritten = AddtextureInScene(pTexture, texture_handle, filename_out);

					// Define texture for back face, 
					HC_Open_Segment_By_Key(m_model_key);
					defineTexture(filename_out, texture_handle);
					HC_Close_Segment();

					if(isTextureWritten)
					{
						char texture_file_name[MVO_BUFFER_SIZE];
						sprintf(texture_file_name,"back_%s",filename_out);
						sprintf(m_ccolor_opts, "%s = %s", m_cFaceSide, texture_file_name);
						HC_Set_Color(m_ccolor_opts);
					}
					if (bUses_Alfa)
					{
						sprintf(backface_transmission, "%s=(transmission = r=%f g=%f b=%f)",m_cFaceSide ,(1.0-pBackAlpha),(1.0-pBackAlpha),(1.0-pBackAlpha));
						HC_Set_Color(backface_transmission);
					}
										
				}	
			}
			else 
			{					
				OLE_COLOR back_color;
				pBackMat->get_Color(&back_color);
				getRGBcolor(back_color, back_r, back_g, back_b); 
				HC_Set_Color_By_Value( m_cFaceSide , "rgb", back_r, back_g, back_b );
				if (bUses_Alfa)
				{
					sprintf(backface_transmission, "%s=(transmission = r=%f g=%f b=%f)",m_cFaceSide ,(1.0-pBackAlpha),(1.0-pBackAlpha),(1.0-pBackAlpha));
					HC_Set_Color(backface_transmission);
				}
			}
		}
	}
}

bool HSKPImporter::AddtextureInScene(CComPtr<ISkpTexture> pTexture, long texture_handle, char * filename_out)
{
	char dir_out[MVO_BUFFER_SIZE];
	bool isTextureWritten = true;

	pair<set<long>::iterator, bool> ret;
	ret = m_setTextureHandles.insert(texture_handle);

	BSTR fileName;
	pTexture->get_Filename(&fileName);

	char texture_name[MVO_BUFFER_SIZE];
	convertToCharArray(fileName,texture_name);
	SysFreeString(fileName);

	HUtility::FindFileNameAndDirectory(texture_name,  dir_out,  texture_name);

	/* 
	There is a problem observed while writing a texture whose
	file name starts with 'untitled'. I am trying to eliminate writing
	and setting the texture related to 'untitled' texture file: Vijay Nerella (23-07-08)

	TODO - Replace name 'Untitled' with 'Unknown' - Ashish.S. 29/10/2009.
	*/
	bool isfile_untitled = false;
	if (!strnicmp(texture_name,"untitled",8))
	{
		isfile_untitled=true;
		isTextureWritten = false;
	}

	sprintf(filename_out,"%d_%s", texture_handle, texture_name);
	sprintf(m_ctexture_path,"%s\\%s", m_cTextureDirectory,filename_out);
	bool isFileExist = check_file_exist(m_ctexture_path,"");


	//if ((isFileExist==false)&&(isfile_untitled==false))
	if(ret.second == true && isfile_untitled == false )
	{
		isTextureWritten = true;
		HRESULT front_result;
		try{
			front_result =	m_pTextureWriter->WriteTextureFileFromHandle(texture_handle,(_bstr_t)(m_ctexture_path));
		}
		catch(...)
		{
			isTextureWritten = false;
		}
		if(front_result == S_OK)
		{
			HC_KEY this_style = HC_KOpen_Segment("/include library/SKPTextures");
			HC_Close_Segment();
			m_rInputOptions.m_pImageName=filename_out;
			HFileInputResult result = m_pReader->FileInputToImageKey(m_ctexture_path, &m_rImageKey, this_style, &m_rInputOptions);
		}
	}

	return isTextureWritten;
}

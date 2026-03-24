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
// $Header: /files/homes/master/cvs/hoops_master/hio_skp/source/HIOUtilitySKP.cpp,v 1.25 2010-07-30 09:38:23 mustafa Exp $
//


#include "HIOUtilitySKP.h"
#include "HSKPHelper.h"

//Hoops includes
#include "HUtilityLocaleString.h"
#include "hutility.h"


typedef HRESULT (*SkpAppFunc)(ISkpApplication** ppApplication) ;

HFileInputResult HIOUtilitySKP::FileInputByKey(const wchar_t * FileName, HC_KEY key, HInputHandlerOptions * options)
{
	return FileInputByKey(H_ASCII_TEXT(FileName), key, options); 
}

HFileInputResult HIOUtilitySKP::FileInputByKey(const unsigned short * FileName, HC_KEY key, HInputHandlerOptions * options)
{
	H_UTF16 utf16;
	utf16.encodedText((utf16_char*)FileName);
	return FileInputByKey(H_ASCII_TEXT(H_WCS(utf16).encodedText()), key, options);
}


HFileInputResult HIOUtilitySKP::FileInputByKey(const char * FileName, HC_KEY key, HInputHandlerOptions * options)
{
	HFileInputResult ret = InputOK;
	if(!FileName) return InputBadFileName;
	if(!key) return InputFail;

	//starting of progress bar
	SetStartingInput();

	CComPtr<ISkpTextureWriter> pTextureWriter;
	m_pApp->CreateTextureWriter(&pTextureWriter);
	m_bImporter = new HSKPImporter(pTextureWriter);

	m_bImporter->setInputHandler(this); 
		
	//Create directory to save skp textures
	m_bImporter->setTextureDirectory();

	BSTR version;
	m_pApp->get_Version(&version);
	SysFreeString(version);

	if(options)
	{
		m_bImporter->set_ignoreOffEntities(options->m_bIgnoreOffEntities);
		m_bImporter->set_importMetadata(options->m_bImportMetadata);
	}
	
  	HC_Open_Segment_By_Key(key);
	{
		int fileNameSize = strlen(FileName) + 1;
		char* dir = new char[fileNameSize];
		//char* skpFileName = new char [fileNameSize];
		char skpFileName[1024];
		HUtility::FindFileNameAndDirectory(FileName, dir, skpFileName);
		m_bImporter->conditionStringForSegName(skpFileName);
		
		HC_Open_Segment(skpFileName);
		{
			(m_bImporter->getInputHandler())->ReportInputPercentProgress(0.10);
			(m_bImporter->getInputHandler())->ReportInputInformation("Loading of SKP database started");
			CComPtr<ISkpDocument> pDoc = m_bImporter->getSKPDatabase(FileName,m_pApp);
			if(pDoc)
			{
				(m_bImporter->getInputHandler())->ReportInputInformation("Loading of SKP database finished");

				//Although time required to load the skp database varies for files, I have 
				//roughly estimated that this takes 1/3 of total time and hence passing
				//0.25 as argument to the following call : Mustafa Bohari[17-03-09]
				(m_bImporter->getInputHandler())->ReportInputPercentProgress(0.33);

				m_bImporter->setTotalEntities(pDoc);

				//Top level Hoops setting
				HC_Set_Handedness("right");
				HC_Set_Heuristics("culling = off");
				HC_Set_Color("lines = black");


				m_bImporter->setModelKey(key);
				m_bImporter->setDefaultOptions(pDoc);
				m_bImporter->importSKPPages(pDoc,options);
				(m_bImporter->getInputHandler())->ReportInputInformation("Reading of entities started");
				{
					CComPtr<ISkpEntityProvider> pEntProvider;
					pDoc->QueryInterface(IID_ISkpEntityProvider, (void **) &pEntProvider);

					m_bImporter->importSKPImage(pEntProvider, false);
					m_bImporter->importSKPEdges(pEntProvider);
					m_bImporter->importSKPFaces(pEntProvider, false);
					m_bImporter->importSKPComponents(pEntProvider, false);
					m_bImporter->importSKPGroups(pEntProvider, false);
					if(options->m_bOptimizeSegmentTree)
					{
						HC_Optimize_Segment_Tree(".","collapse matrices = on, merge shells = on, instance shells = on, process includes = on, preserve user options = merge, reorganize = (color = on)" );
							
					}
					
				}

				(m_bImporter->getInputHandler())->ReportInputInformation("Reading of entities finished");


				m_bImporter->fitToScene(options);

				// ISkpViewProvider interfaces is not supported by the SkpDocument and SkpApplication classes
				//And we require ISkpViewProvider object to get the text position 
				//So texts are not supported:Mustafa Bohari[11-APR-2008]

				//m_bImporter->importSKPText(m_bImporter->m_pDoc);//Not supported due to problem in getting text position
			}
			else
				ret = InputFail;
		}
		HC_Close_Segment();

		H_SAFE_DELETE_ARRAY(dir);
	//	H_SAFE_DELETE_ARRAY(skpFileName);

	}
	//HC_Write_Metafile(".","D:\\skp.hmf", "");
	HC_Close_Segment();

	if(m_bImporter)
		delete m_bImporter;

	SetFinishedInput();

	return ret;
}


void  HIOUtilitySKP::InitSKP()
{
	m_rHModule = LoadLibrary("SketchUpReader.dll");

	assert(m_rHModule);
    
	SkpAppFunc lpAppFunc = (SkpAppFunc)GetProcAddress(m_rHModule, "GetSketchUpSkpApplication");
	
    assert(lpAppFunc);

	(*lpAppFunc)(&m_pApp);

	assert(m_pApp);
}

void  HIOUtilitySKP::ShutdownSKP()
{
	if(m_rHModule)
		FreeLibrary(m_rHModule);
}


#ifdef HIO_SKP
void * CreateInput(HIOManager *manager)
{
	HIOUtilitySKP *handler  = new HIOUtilitySKP();
	manager->RegisterInputHandler("skp",handler);
	manager->RegisterConnector("skp",CreateConnector,(HIO_FREE_CONNECTOR_FUNCTION) FreeConnector);
	
	handler->InitSKP();

	return handler;

};

void * CreateOutput(HIOManager *manager)
{
	return NULL;
};


void * CreateConnector(void *unused)
{
	UNREFERENCED(unused);
	return new HIOConnector();
};


void Free(HIOUtilitySKP *handler)
{ 
	if(handler) 
	{
		handler->m_pApp.Release();
		handler->ShutdownSKP();
		delete handler;
		handler = NULL;
	}
	
};


void FreeConnector(HIOConnector *connector)
{
	if(connector)
		delete connector;
};

#endif

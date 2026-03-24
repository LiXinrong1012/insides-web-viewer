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
// $Header: /files/homes/master/cvs/hoops_master/hio_dgndirect_v2/source/HIOUtilityDGN.cpp,v 1.26 2010-08-23 13:14:26 mustafa Exp $
//

#include <stdio.h>

#include "hc.h"
#include "HIOUtilityDGN.h"
#include "HDGNHelper.h"

#include "OdaCommon.h"
#include "ExDgnServices.h"
#include "ExDgnHostAppServices.h"
#include "DgDatabase.h"
#include "DynamicLinker.h"

#include "RxInit.h"
#include "RxObjectImpl.h"
#include "RxDynamicModule.h"


#include "HUtilityLocaleString.h"

#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a


#ifndef _TOOLKIT_IN_DLL_
	ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDgnModule);
	ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(DgModelerModule);
	ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDgn7IOModuleImpl);  //this library allows to read V7 files
	ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDwgModule);//For reading ACAD Xdata
	ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDwgDbModuleImpl);//For reading ACAD Xdata


	ODRX_BEGIN_STATIC_MODULE_MAP()
		 ODRX_DEFINE_STATIC_APPMODULE(L"TG_Db", OdDgnModule)
		 ODRX_DEFINE_STATIC_APPMODULE(L"TG_ModelerGeometry", DgModelerModule)
		 ODRX_DEFINE_STATIC_APPLICATION(L"TG_Dgn7IO", OdDgn7IOModuleImpl)
		 ODRX_DEFINE_STATIC_APPLICATION(L"TD_Db.dll", OdDwgModule)
		 ODRX_DEFINE_STATIC_APPLICATION(L"TG_DwgDb", OdDwgDbModuleImpl)
	ODRX_END_STATIC_MODULE_MAP()
#endif



HFileInputResult HIOUtilityDGN::FileInputByKey(const wchar_t * FileName, HC_KEY key, HInputHandlerOptions * options)
{
	 HFileInputResult result = FileInputByKey(H_ASCII_TEXT(FileName), key, options); 
	 return result;
}

HFileInputResult HIOUtilityDGN::FileInputByKey(const unsigned short * FileName, HC_KEY key, HInputHandlerOptions * options)
{
	H_UTF16 utf16;
	utf16.encodedText((utf16_char*)FileName);
	return FileInputByKey(H_ASCII_TEXT(H_WCS(utf16).encodedText()), key, options);
}

HFileInputResult HIOUtilityDGN::FileInputByKey(const char * FileName, HC_KEY key, HInputHandlerOptions * options)
{
	HDGNImporter dgn_importer;
	dgn_importer.setInputHandler(this);

	//starting of progress bar
	SetStartingInput();
	HFileInputResult result = dgn_importer.FileInputByKey( FileName, key, options );
	if(options->m_bOptimizeSegmentTree)
	{
		HC_Optimize_Segment_Tree_By_Key( key, "collapse matrices = on, merge shells = on, instance shells = on, process includes = on, preserve user options = merge, reorganize = (color = on)" );
	}

	//completion of progress bar
	SetFinishedInput();


	return result;
}

void  HIOUtilityDGN::InitDGNDirect()
{

#ifndef _TOOLKIT_IN_DLL_
  ODRX_INIT_STATIC_MODULE_MAP();
#endif
  
    // Initialize Runtime Extension environment
    odrxInitialize( &g_HIO_OdExDgnSystemServices );

    // Initialize DGNdirect
    odrxDynamicLinker()->loadModule(L"TG_Db", false);
	odrxDynamicLinker()->loadModule(L"TD_Db.dll", false);

	OdRxModulePtr pModule = ::odrxDynamicLinker()->loadModule("TG_ModelerGeometry");

    OdRxClassPtr pService( odrxServiceDictionary()->getAt(OD_T("OdDgModelerGeometryCreator")) );

	if (!pModule.isNull() && !pService.isNull())
      OdDgModelerGeometryCreatorPtr pCreator = pService->create();
}

void  HIOUtilityDGN::ShutdownDGNDirect()
{
	odrxUninitialize();
}


#ifdef HIO_DGN
void * CreateInput(HIOManager *manager)
{
	HIOUtilityDGN *handler  = new HIOUtilityDGN();
	manager->RegisterInputHandler("dgn",handler);
	manager->RegisterConnector("dgn",CreateConnector,(HIO_FREE_CONNECTOR_FUNCTION) FreeConnector);
	
	handler->InitDGNDirect();

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


void Free(HIOUtilityDGN *handler)
{ 
	if(handler) 
	{
		handler->ShutdownDGNDirect();
		delete handler;
	}

};


void FreeConnector(HIOConnector *connector)
{
	if(connector)
		delete connector;
};

#endif

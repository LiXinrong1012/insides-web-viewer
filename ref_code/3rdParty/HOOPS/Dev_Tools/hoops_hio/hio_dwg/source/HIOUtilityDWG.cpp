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
// $Header: /files/homes/master/cvs/hoops_master/hio_dwg/source/HIOUtilityDWG.cpp,v 1.42 2010-10-13 09:57:17 ashish Exp $
//


// standard includes
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <string.h>
//#include <time.h>

// RealDWG includes
#include "acgi.h"
#include "acestext.h"
#include "acdbxref.h"
#include "afxwin.h"
#include "adesk.h"

#include "dbapserv.h"
#include "dbacis.h"
#include "dbmstyle.h"
#include "dbsymtb.h"
#include "dbents.h"
#include "dbelipse.h"
#include "dbspline.h"
#include "dblead.h"
#include "dbray.h"
#include "dbxline.h"
#include "dbmline.h"
#include "dbbody.h"
#include "dbregion.h"
#include "dbsol3d.h"
#include "rxregsvc.h"

// Hoops Include
#include "HIOUtilityDWG.h"
#include "hc.h"
#include "HDWGHelper.h"
#include "HUtilityLocaleString.h"

//Follwing global variable is used as there is no better way to pass the value of global_scale_factor of 
//master file to its xrefs for BStream importer//Mustafa Bohari 31-Aug-09
extern double global_GlobalScaleFactor = 1;

static const wchar_t acIsmObjDbxFile[] = L"acIsmObj18.dbx";

DWGException::DWGException(const char* msg)
{
	m_message = (char*)malloc(strlen(msg)+1);
	strcpy(m_message, "");
	strcat(m_message, msg);
}

DWGException::~DWGException()
{
	if(m_message)
	{
		free(m_message);
		m_message = NULL;
	}
}

class DumpDwgHostApp : public AcDbHostApplicationServices
{
public:
	~DumpDwgHostApp(){;};
	Acad::ErrorStatus findFile(ACHAR* pcFullPathOut, int nBufferLength,
		const ACHAR* pcFilename, AcDbDatabase* pDb = NULL,
		AcDbHostApplicationServices::FindFileHint hint = kDefault)
	{
		wchar_t pExtension[5];
		switch (hint)
		{
		case kCompiledShapeFile:
			wcscpy(pExtension, L".shx");
			break;
		case kTrueTypeFontFile:
			wcscpy(pExtension, L".ttf");
			break;
		case kPatternFile:
			wcscpy(pExtension, L".pat");
			break;
		case kARXApplication:
			wcscpy(pExtension, L".dbx");
			break;
		case kFontMapFile:
			wcscpy(pExtension, L".fmp");
			break;
		case kXRefDrawing:
			wcscpy(pExtension, L".dwg");
			break;
		case kFontFile:                // Fall through.  These could have
		case kEmbeddedImageFile:       // various extensions
		default:
			pExtension[0] = L'\0';
			break;
		}
		wchar_t* filePart;
		DWORD result = 0;

		result = SearchPath(NULL, pcFilename, pExtension, nBufferLength, 
			pcFullPathOut, &filePart);
	
		if (result && result < (DWORD)nBufferLength)
			return Acad::eOk;
		else
			return Acad::eFileNotFound;
	}
    // These two functions return the full path to the root folder where roamable/local 
    // customizable files were installed. Note that the user may have reconfigured 
    // the location of some the customizable files using the Options Dialog 
    // therefore these functions should not be used to locate customizable files. 
    // To locate customizable files either use the findFile function or the 
    // appropriate system variable for the given file type. 
    //
	Acad::ErrorStatus getRoamableRootFolder(const char*& folder)
	{
		// Return the Install directory for customizable files
		Acad::ErrorStatus ret = Acad::eOk;
		static char buf[MAX_PATH] = "\0"; //MDI SAFE
		if (buf[0]==0)
			if (GetModuleFileNameA(NULL, buf, MAX_PATH) != 0)
				ret = Acad::eRegistryAccessError;
		folder = buf;
		return ret;
	}

	Acad::ErrorStatus DumpDwgHostApp::getLocalRootFolder(const char*& folder)
	{
		// Return the Install directory for customizable files
		Acad::ErrorStatus ret = Acad::eOk;
		static char buf[MAX_PATH] = "\0"; //MDI SAFE
		if (buf[0]==0)
			if (GetModuleFileNameA(NULL, buf, MAX_PATH) != 0)
				ret = Acad::eRegistryAccessError;
		folder = buf;
		return ret;
	}

    //URL related services
    Adesk::Boolean isURL(const char* pszURL) const
	{
		return FALSE;/*PathIsURLA(pszURL);*/
	}

    Adesk::Boolean isRemoteFile(const char* pszLocalFile, char* pszURL) const
	{
		/*    CString value;
		if (m_localToUrl.Lookup(pszLocalFile,value))
		{
		strcpy(pszURL,value);
		return TRUE;
		}
		*/
		return FALSE;
	}
    //Acad::ErrorStatus  getRemoteFile(const char* pszURL, char* pszLocalFile, Adesk::Boolean bIgnoreCache) const;

    // make sure you implement getAlternateFontName. In case your findFile implementation
    // fails to find a font you should return a font name here that is guaranteed to exist.
    virtual ACHAR * getAlternateFontName() const
    {
        return L"txt.shx"; //findFile will be called again with this name
    }

	virtual void fatalError(const ACHAR * format,...)
	{
		throw new DWGException(H_ASCII_TEXT(format));
	}

	// This method is very important. When your application is supposed to load dbx files, implement this method
	// and set return value as ODBXHOSTAPPREGROOT in ObjDbx.msm. This will make sure that the execution finds 
	// required dbx files. (In case there are custom entities, and you have dbx files from object enablers) 
	// ASHISH.S. 13/10/2010. Issue 12960, ADN query - 1262303.
	//virtual const ACHAR * getRegistryProductRootKey()
	//{
	//	return L"SOFTWARE\\YOUR_COMPANY\\YOUR_PRODUCT\\VERSION"; // as in registry path.
	//}

};

DumpDwgHostApp gDumpDwgHostApp;



HFileInputResult HIOUtilityDWG::FileInputByKey(const char * FileName, HC_KEY key, HInputHandlerOptions * options)
{
	return FileInputByKey((wchar_t const*)H_WCS(FileName).encodedText(), key, options); 
}

HFileInputResult HIOUtilityDWG::FileInputByKey(const unsigned short * FileName, HC_KEY key, HInputHandlerOptions * options)
{
	H_UTF16 utf16;
	utf16.encodedText((utf16_char*)FileName);
	return FileInputByKey((wchar_t const*)H_WCS(utf16).encodedText(), key, options);
}



HFileInputResult HIOUtilityDWG::FileInputByKey(const wchar_t * FileName, HC_KEY key, HInputHandlerOptions * options)
{
	if(!FileName) return InputBadFileName;
	if(!key) return InputFail;

	SetStartingInput(FileName);

	// delegated to a separate class
	bool result;
	if( options && options->m_bInputViaHSF)
	{
		HDWG_BStreamImporter importer(this, false);
		result = importer.importDWGFile(FileName, key, options);
		char bstream_opt_str[] = "collapse matrices = on, merge shells = on, instance shells = on, process includes = on, preserve user options=merge, reorganize = (color = on)";
		HC_Optimize_Segment_Tree_By_Key(key, bstream_opt_str );
	}
	else
	{
		HDWG_3dgsImporter importer(this);
		result = importer.importDWGFile(FileName, key, options);
		HC_Optimize_Segment_Tree_By_Key(key, "instance shells, preserve user options=merge");

	}

	SetFinishedInput();


	//Reset Global scale factor to 1 again
	global_GlobalScaleFactor = 1;

	if(result) 
		return InputOK;
	else
		return InputFail;
}

HFileInputResult HIOUtilityDWG::DatabaseInputByKey(AcDbDatabase* pAcDbDatabase, 
												    HC_KEY key, HInputHandlerOptions * options)
{
	if(!pAcDbDatabase) return InputFail;
	if(!key) return InputFail;

	// delegated to a separate class
	bool result;
	if( options && options->m_bInputViaHSF)
	{
		HDWG_BStreamImporter importer(this, false);
		result = importer.importDWGDatabase(pAcDbDatabase, key, options);
	}
	else
	{
		HDWG_3dgsImporter importer(this);
		result = importer.importDWGDatabase(pAcDbDatabase, key, options);
	}

	if(result) 
		return InputOK;
	else
		return InputFail;
}

bool HIOUtilityDWG::InitRealDWG()
{
	acdbSetHostApplicationServices(&gDumpDwgHostApp);

	long lcid = 0x00000409;  // English
	acdbValidateSetup(lcid);

	// Load the ISM dll
	acrxLoadModule(acIsmObjDbxFile, 1);


	// Load dbx files for custom entities
	// fix for issue 11818
	wchar_t searchpath[256] = L"";

#if WIN64
	GetEnvironmentVariable(L"REALDWG_SDK_DIR_X64", searchpath, 256);
#else
	GetEnvironmentVariable(L"REALDWG_SDK_DIR", searchpath, 256);
#endif

	wcscat(searchpath, L"\\*.dbx");

	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(searchpath, &findFileData);

	if(hFind  != INVALID_HANDLE_VALUE) 
	{
		bool success;
		while(FindNextFile(hFind, &findFileData)) 
		{ 
			success = acrxLoadModule(findFileData.cFileName, 1);
		}
	}

	FindClose(hFind);

	return true;
}

bool HIOUtilityDWG::ShutDownRealDWG()
{
	if (acdbIsModelerStarted())
		acdbModelerEnd(); 

	// Unload the ISM dll
	acrxUnloadModule(acIsmObjDbxFile);

	wchar_t searchpath[256] = L"";

#if WIN64
	GetEnvironmentVariable(L"REALDWG_SDK_DIR_X64", searchpath, 256);
#else
	GetEnvironmentVariable(L"REALDWG_SDK_DIR", searchpath, 256);
#endif

	wcscat(searchpath, L"\\*.dbx");

	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(searchpath, &findFileData);

	if(hFind  != INVALID_HANDLE_VALUE) 
	{
		bool success;
		while(FindNextFile(hFind, &findFileData)) 
		{ 
			success = acrxUnloadModule(findFileData.cFileName);
		}
	}

	FindClose(hFind);

	acdbCleanUp();

	return true;
}


HIOConnectorDWG::~HIOConnectorDWG()
{
	if(m_pAcDbDatabase)
	{
		acdbReleaseHostDwg(m_pAcDbDatabase);
		m_pAcDbDatabase = 0;
	}
}


#ifdef HIO_DWG
void * CreateInput(HIOManager *manager)
{
	HIOUtilityDWG *handler = new HIOUtilityDWG();
	manager->RegisterInputHandler("dwg",handler);
	manager->RegisterInputHandler("dxf",handler);

	manager->RegisterConnector("dwg",CreateConnector,(HIO_FREE_CONNECTOR_FUNCTION) FreeConnector);
	manager->RegisterConnector("dxf",CreateConnector,(HIO_FREE_CONNECTOR_FUNCTION) FreeConnector);
#ifndef HIO_DWG_BYPASS_INIT_REALDWG
	handler->InitRealDWG();
#endif

	return handler;
};

void * CreateOutput(HIOManager *manager)
{
	return NULL;
};

void * CreateConnector(void * unused)
{
	UNREFERENCED(unused);
	return new HIOConnectorDWG();
};

void Free(HIOUtilityDWG *handler)
{ 
	if(handler) 
	{
#ifndef HIO_DWG_BYPASS_INIT_REALDWG
		handler->ShutDownRealDWG();
#endif
		delete handler; 
	}
};

void FreeConnector(HIOConnectorDWG *connector)
{
	if(connector)
		delete connector;
};

#endif
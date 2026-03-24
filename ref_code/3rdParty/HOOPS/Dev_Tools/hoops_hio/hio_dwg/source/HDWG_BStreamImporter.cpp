//
// (C) Copyright 1995-1996,1998-2004 by Autodesk, Inc.
//
//    This program is copyrighted by Autodesk, Inc. and is  licensed
//    to you under the following conditions.  You may not distribute
//    or  publish the source code of this program in any form.   You
//    may  incorporate this code in object form in derivative  works
//    provided  such  derivative  works  are  (i.) are  designed and 
//    intended  to  work  solely  with  Autodesk, Inc. products, and 
//    (ii.)  contain  Autodesk's  copyright  notice  "(C)  Copyright  
//    1995-1996 by Autodesk, Inc."
//
//    AUTODESK  PROVIDES THIS PROGRAM "AS IS" AND WITH  ALL  FAULTS.
//    AUTODESK  SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF  MER-
//    CHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK,  INC.
//    DOES  NOT  WARRANT THAT THE OPERATION OF THE PROGRAM  WILL  BE
//    UNINTERRUPTED OR ERROR FREE.

// HDWGHelper.CPP

#include "HDWGHelper.h"
#include "HBaseView.h"

// RealDWG Toolkit includes
#include "acdb.h"
#include "adesk.h"
#include "acgi.h"
#include "acestext.h"
#include "acgiutil.h"
#include "acgimaterial.h"
#include "acutmem.h"
#include "achapi.h"

#include "dbmain.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "dbents.h"
#include "dbelipse.h"
#include "dbspline.h"
#include "dbhatch.h"
#include "dblead.h"
#include "dbray.h"
#include "dbxline.h"
#include "dbmline.h"
#include "dbbody.h"
#include "dbimage.h"
#include "dbregion.h"
#include "dbsol3d.h"
#include "dbfcf.h"
#include "dbproxy.h"
#include "dbapserv.h"
#include "dbmstyle.h"
#include "dbmaterial.h"
#include "dbspfilt.h" 
#include "dbdict.h"
#include "dbgroup.h"
#include "dblayout.h"
#include "dbobjptr.h"

#include "gelnsg3d.h"
#include "rxobject.h"
#include "rxregsvc.h" 

// HOOPS includes
#include "hc.h"
#include "HTools.h"

// Standard includes
//#include <assert.h>
//#include <math.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <sys/stat.h>
//#include <time.h>
#include <ctime>
//#include <wchar.h>
//#include <direct.h>

// HOOPS/MVO includes
#include "HDB.h"
#include "HUtilityLocaleString.h"
#include "HUtilityGeometryCreation.h"
#include "HIOUtilityDWG.h"
#include "vhash.h"

// NOTE: REALDWG SDK FILE achapi.h REQUIRES 'UINT' WHICH SEEMS TO BE NON-STANDARD C/C++ DATATYPE AND IS 
// DEFINED IN windef.h. I COULDN'T INCLUDE THAT FILE DIRECTLY HERE BECAUSE OF WEIRD COMPILER ERRORS. INCLUDING
// windows.h SOLVES THE PROBLEM, BUT MAKES THIS CODE WINDOWS-ONLY. THAT SHOULD BE FINE - IF REALDWG ITSELF DOESN'T
// SUPPORT ANYTHING ELSE. Pavan T. (22nd Oct 07)
#ifdef WIN32
#include <windows.h>//Without this AcDbTable will not work.
#include "dbtable.h"
#endif


extern double global_GlobalScaleFactor;

//#include <shlwapi.h>
//#include <atlstr.h>



// NOTE ON NORMALS AND LIGHTING PROBLEM.  Bob has told me that our normal
// generation code does not honor the polygon handedness when it returns a
// normal and that it always returns a right handed normal which is the
// opposite to what we need.  We could enhance it but I think it would be
// easiest if you simply inverted the normals that you are currently receiving.
// This would be done by simply multiplying all the floats within the normals
// array by -1 - Gavin (via. email)

//define HIODWG_TESSELLATE_CIRCLE_ELLIPSE_SURFS: It is found that in HOOPS circular and elliptical surfaces
// (discs or filled pies) are tessellated on the fly and do not get pushed into display lists. This causes a huge
// performance overhead. Define the following if you want them to tessellate before inserting into HOOPS. In that 
// case they get inserted as shells
#define HIODWG_TESSELLATE_CIRCLE_ELLIPSE_SURFS

//define HIODWG_FORCE_XREF_GENERATION: Normally the DWG xrefs will not be imported if there is an hsf of same 
// name in the same directory. Provided these hsfs have later timestamp than their counter DWGs and are not of 0 size.
// But, you can force regeneration of these hsfs regardless by defining HIODWG_FORCE_XREF_GENERATION
// NOTE: THIS MODE IS CURRENTLY UNABLE TO RESOLVE CYCLIC XREFS IN DWGS AND WILL HANG IN SUCH CASE.
//#define HIODWG_FORCE_XREF_GENERATION


//define HIODWG_IMPORT_USE_HSF_XREFS will not resolve DWG xrefs using RealDWG, but will export each xref'ed
// DWG file as a separate xref'ed HSF. The master DWG will be exported as master HSF.
// LIMITATIONS: ASSUMES ALL THE DWG XREFS ARE IN THE SAME DIRECTORY AS MASTER XREF
#define HIODWG_IMPORT_USE_HSF_XREFS

// export the HSF object to a file

struct _stat HDWG_BStreamImporter::m_MasterHsfFileTime;

static bool check_file_exist(const wchar_t* dir, const wchar_t* file)
{
	wchar_t full_filepath[_MAX_PATH];
	wcscpy(full_filepath, dir);
	wcscat(full_filepath, file);

	FILE* fp;
	fp = wfopen(full_filepath,	L"r");
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

// returns the segment key of the block table record segment which contains/should contain
// this entity. The segment will be created if it doesn't exist
TK_Open_Segment* HDWG_BStreamImporter::GetBlockTableRecordSegmentForEntity(AcDbEntity *pEnt)
{
	//HC_KEY ret_segment_key = INVALID_KEY;
	AcDbBlockTableRecord *pBlockTableRecord = 0;
	AcDbObjectId ent_block_id = pEnt->blockId();
	bool isNew = false;
	return GetBlockTableRecordSegmentFromId(ent_block_id, isNew);
}
// returns the segment key of the block table record segment which contains/should contain
// this entity. The segment will be created if it doesn't exist
//static HC_KEY GetBlockTableRecordSegmentFromId(const AcDbObjectId& blockTableRecordID, bool& isNew)
TK_Open_Segment* HDWG_BStreamImporter::GetBlockTableRecordSegmentFromId(const AcDbObjectId& blockTableRecordID, bool& isNew)
{
	TK_Open_Segment	*ret_segment_handler = NULL;

	AcDbBlockTableRecord *pBlockTableRecord = 0;
	Acad::ErrorStatus es = acdbOpenObject(pBlockTableRecord, blockTableRecordID, AcDb::kForRead);

	// For optimization
	m_iterator_segmap = m_Segments_map.find (pBlockTableRecord);
	if(m_iterator_segmap != m_Segments_map.end()) 
	{
		pBlockTableRecord->close();
		ret_segment_handler = new TK_Open_Segment;
		STREAM_Open_Segment(ret_segment_handler, H_ASCII_TEXT(m_iterator_segmap->second));
		STREAM_Close_Segment();
		return ret_segment_handler;
	}
	//

	if (pBlockTableRecord)
	{
		wchar_t segment_name[MVO_BUFFER_SIZE] = L"";
		wchar_t *blockName;
		wchar_t bName[MVO_BUFFER_SIZE];

		pBlockTableRecord->getName(blockName);
		wcscpy(bName, blockName);
		condition_string_for_segment_name(bName);
		acdbFree(blockName);

		if((wcsicmp(L"Model_Space", (bName)) == 0) && (m_listDWGLayouts) && !m_bAmIXref)
		{
			wchar_t temp[MVO_BUFFER_SIZE];
			swprintf(temp, MVO_BUFFER_SIZE, L"btable_%p_%ls", pBlockTableRecord, (bName));
			swprintf(segment_name, MVO_BUFFER_SIZE, L"/include library/other block table records/model space/%ls", (temp));
		}
		else 
		{
			//if(wcsstr(bName ,L"Paper_Space"))
			if(pBlockTableRecord->isLayout())
			{
				//<<
				// this code piece is just to get the layout name of this paper_space.
				// We are creating layouts in Import_Layout() with proper layout names.
				// Now if the Layout has it's own geometry, they will come here and get the
				// owner's (Layout's) proper name and not just "Paper_Space". This will make
				// sure that the entity will come inside the segment created with Layout name.
				// this might be achieved by storing m_CurrentLayoutName as in 3DGS importer
				// but I am using this code instead. ASHISH.S. 15/05/09
				AcDbObjectId OwnerlayoutID = pBlockTableRecord->getLayoutId();
				AcDbLayout * OwnerLayout = 0;
				Acad::ErrorStatus es = acdbOpenObject(OwnerLayout, OwnerlayoutID, AcDb::kForRead);

				if(OwnerLayout)
				{
					wchar_t NewName[MVO_BUFFER_SIZE];
					wchar_t *layName;
					OwnerLayout->getLayoutName(layName);
					wcscpy(NewName, layName);
					acdbFree(layName);
					condition_string_for_segment_name(NewName);
					//>>
					swprintf(segment_name, MVO_BUFFER_SIZE, L"btable_%p_%ls", pBlockTableRecord, (NewName));
					OwnerLayout->close(); 
				}
				else 
					swprintf(segment_name, MVO_BUFFER_SIZE, L"btable_%p_%ls", pBlockTableRecord, (bName));
			}
			else
			{
				// You will find the execution visiting this place more often than any of above statements.
				swprintf(segment_name, MVO_BUFFER_SIZE, L"btable_%p_%ls", pBlockTableRecord, (bName));
			}		
		}

		vhash_status_t vhash_status;
		void* seg_hanlder_alreay_present = false;
		//vhash_lookup_string_key_item(m_vhash_SegName_IsPresentFlag, segment_name, (void**)&ret_segment_handler);
		vhash_status = vhash_lookup_string_key_item(m_vhash_SegName_IsPresentFlag, H_ASCII_TEXT(segment_name), (void**)&seg_hanlder_alreay_present);
		//H_ASSERT(vhash_status != VHASH_STATUS_FAILED);

		/*ret_segment_handler = new TK_Open_Segment;
		ret_segment_handler->SetSegment(H_ASCII_TEXT(segment_name));*/

		ret_segment_handler = new TK_Open_Segment;
		STREAM_Open_Segment(ret_segment_handler, H_ASCII_TEXT(segment_name));
		STREAM_Close_Segment();

		if(seg_hanlder_alreay_present == 0)
		{
			isNew = true;
			seg_hanlder_alreay_present = (void*)true;
			vhash_insert_string_key_item(m_vhash_SegName_IsPresentFlag, H_ASCII_TEXT(segment_name), (void*)seg_hanlder_alreay_present);
		}

		pBlockTableRecord->close();

		// For optimization
		char * seg_name = new char[MVO_BUFFER_SIZE];
		strcpy(seg_name,H_ASCII_TEXT(segment_name));
		m_Segments_map.insert(std::pair<void * , const char *>(pBlockTableRecord,seg_name));
	}

	return ret_segment_handler;
}

HDWG_BStreamImporter::HDWG_BStreamImporter(HIOUtilityDWG* pDWGInputHandler, bool is_xref) : HDWGImporter(pDWGInputHandler)
{
	m_pBStreamtk = new BStreamFileToolkit;
	//	m_pBStreamtk->SetLogFile("C:/temp/bstream_log.txt");
	//	m_pBStreamtk->SetLogging(true);
	m_pBStreamBuffer = new char[MVO_BUFFER_SIZE];
	m_nBStreamBuffSize = MVO_BUFFER_SIZE;
	m_nBStreamBuffCount = 0;
	m_pHSFFile = 0;
	m_vhash_StyleSegName_IsPresentFlag = 0;
	m_vhash_SegName_IsPresentFlag = 0;

	bConnectivityCompression = FALSE;
	bImageCompression = FALSE;
	bVertexCompression = FALSE;
	bNormalCompression = FALSE;
	m_VertexCompressionBits = 36;
	m_NormalCompressionBits = 24;
	m_ImageCompressionValue = 75;

	m_bMergeEntityShells = true;
	m_mtImportStart = 0;
	m_pFileName=0;
	m_bAmIXref = is_xref;
	m_bScratchSegOpen = false;
	m_pXref_hsf_path = 0;
	m_bShellWithFaceColor = false;
}

HDWG_BStreamImporter::~HDWG_BStreamImporter()
{
	delete []m_pBStreamBuffer;
	free(m_pFileName);
	delete m_pBStreamtk;
	free(m_pXref_hsf_path);

	// Free map for optimization
	for( std::map<void *,const char *>::iterator ii= m_Segments_map.begin(); ii!=m_Segments_map.end(); ++ii)
	{
		delete [] (*ii).second;
	}
};

class HSFNoticer : public HIONoticeCallback, public HIOPercentNoticeCallback {
public:
	HSFNoticer(HInputHandler * DWGInputHandler) {m_pDWGInputHandler =DWGInputHandler;};
	void Notice(char const * msg) {;};
	void Notice(wchar_t const * msg) {;};
	void Notice(float percent) {m_pDWGInputHandler->ReportInputPercentProgress(percent);};
	HInputHandler * m_pDWGInputHandler;
};

class HSFInfoNoticer : public HIONoticeCallback {
public:
	HSFInfoNoticer(HInputHandler * DWGInputHandler) {m_pDWGInputHandler =DWGInputHandler;};
	void Notice(char const * msg) {m_pDWGInputHandler->ReportInputInformation(msg);};
	void Notice(wchar_t const * msg) {m_pDWGInputHandler->ReportInputInformation(msg);};
	HInputHandler * m_pDWGInputHandler;
};
static bool get_text_alignment(AcDbText* pAcDbText, int* alignment_index)
{
	AcDb::TextVertMode vert_mode = pAcDbText->verticalMode();
	AcDb::TextHorzMode hort_mode = pAcDbText->horizontalMode();

	switch(hort_mode)
	{
	case AcDb::kTextAlign:
	case AcDb::kTextFit:
	case AcDb::kTextLeft:
		{
			switch(vert_mode)
			{
			case AcDb::kTextBase:
			case AcDb::kTextBottom:
				*alignment_index=TKO_Text_Alignment_Lower_Left;
				break;
			case AcDb::kTextTop:
				*alignment_index=TKO_Text_Alignment_Upper_Left;
				break;
			case AcDb::kTextVertMid:
			default:
				*alignment_index=TKO_Text_Alignment_Middle_Left;
				break;
			}
		}
		break;
	case AcDb::kTextRight:
		{
			switch(vert_mode)
			{
			case AcDb::kTextBase:
			case AcDb::kTextBottom:
				*alignment_index=TKO_Text_Alignment_Lower_Right;
				break;
			case AcDb::kTextTop:
				*alignment_index=TKO_Text_Alignment_Upper_Right;
				break;
			case AcDb::kTextVertMid:
				*alignment_index=TKO_Text_Alignment_Middle_Right;
				break;
			}
		}
		break;
	case AcDb::kTextCenter:
	case AcDb::kTextMid:
		{
			switch(vert_mode)
			{
			case AcDb::kTextBase:
			case AcDb::kTextBottom:
				*alignment_index=TKO_Text_Alignment_Lower_Center;
				break;
			case AcDb::kTextTop:
				*alignment_index=TKO_Text_Alignment_Upper_Center;
				break;
			case AcDb::kTextVertMid:
				*alignment_index=TKO_Text_Alignment_Middle_Center;
				break;
			}
		}

		break;
	default:
		*alignment_index=TKO_Text_Alignment_Middle_Center;
		break;
	}

	return true;
}

static bool get_Mtext_alignment(AcDbMText::AttachmentPoint eMattachpoint, int* alignment_index)
{
	//Only 9 cases exists for Mtext & are handled here, if 10th case exists in future then it should handled. The default option in switch
	// statement "**" doesnt have any meaning.
	switch(eMattachpoint)
	{
	case AcDbMText::kBottomCenter:		
	case AcDbMText::kTopCenter:		
	case AcDbMText::kMiddleCenter:
		*alignment_index=TKO_Text_Alignment_Lower_Center;
		break;
	case AcDbMText::kBottomLeft:		
	case AcDbMText::kTopLeft:		
	case AcDbMText::kMiddleLeft:
		*alignment_index=TKO_Text_Alignment_Lower_Left;
		break;
	case AcDbMText::kBottomRight:		
	case AcDbMText::kTopRight:		
	case AcDbMText::kMiddleRight:
		*alignment_index=TKO_Text_Alignment_Lower_Center;
		break;	
	default:
		*alignment_index=TKO_Text_Alignment_Middle_Center;
		break;
	}	
	return true;
}

static bool HasWritePermission(wchar_t const * dataPath)
{

	///////////////////////previous code/////////////////////////////
	/*	wchar_t* tmpPath = new wchar_t[wcslen(dataPath) + 1];
	wcscpy(tmpPath, dataPath);

	if(!PathIsDirectoryW(tmpPath))
	PathRemoveFileSpecW(tmpPath);

	UINT tmpVal = GetTempFileNameW((tmpPath),L"Temp",0x00,tmpPath);

	if(tmpVal)
	{
	try
	{
	DeleteFileW(tmpPath);
	}
	catch(...)
	{
	// user has write permission, but not delete. 
	}
	}
	delete [] tmpPath;
	return (tmpVal ? TRUE : FALSE);  */
	/////////////////////////////////////////////////////////////////////////
	/////////workaround to remove windows-specific calls ...need to look in..////////////////////////
	FILE *fp;
	if(dataPath)
	{
		fp = wfopen(dataPath,L"w+");
	}

	if(fp != NULL)
	{
		fclose(fp);
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	////////////////////////////////////////////////////////////////////////////


}
bool HDWG_BStreamImporter::importDWGFile(const wchar_t * FileName, HC_KEY modelKey, HInputHandlerOptions * pInputOptions)
{
	bool result = true;

	m_pFileName = h_dwg_wcsdup(FileName);

	//--Begin Progress Msg
	{
		wchar_t input_progress_msg[MVO_BUFFER_SIZE];
		if(m_bAmIXref)
			swprintf(input_progress_msg,MVO_BUFFER_SIZE, L"DWG Import Progress: Importing XRef %ls ...", FileName);
		else
			swprintf(input_progress_msg,MVO_BUFFER_SIZE, L"DWG Import Progress: Importing %ls ...", FileName);
		m_pDWGInputHandler->ReportInputProgress(input_progress_msg);
	}
	//--End Progress Msg


	wchar_t file_ext[_MAX_EXT] = {L""};
	HUtility::FindFileNameExtension(FileName, file_ext);
	if(wcslen(file_ext) == 0 || (!wcsieq(file_ext,L"dwg") && !wcsieq(file_ext,L"dxf")))
	{
		//-- Begin Information Report
		wchar_t err_msg[MVO_BUFFER_SIZE];
		swprintf(err_msg,MVO_BUFFER_SIZE, L"DWG Import Error: Unsupported file extension %ls", file_ext);
		m_pDWGInputHandler->ReportInputInformation(err_msg);
		return false;
		//-- End Information Report
	}

	TK_Status hdwg_status; 

	// construct a full filename but .hsf instead of .dwg
	wchar_t hsf_file[_MAX_PATH];
	size_t len = wcslen(FileName) - wcslen(L".dwg");
	wcsncpy(hsf_file, FileName, len);
	hsf_file[len] = L'\0';
	wcscat(hsf_file, L".hsf");

	bool do_import = true;
	if( pInputOptions && !pInputOptions->m_bForceReimport )
	{
		// check if hsf file already exists and is of a later date than DWG
		struct _stat dwg_fstat;
		struct _stat hsf_fstat;
		int stat_result = _wstat( FileName, &dwg_fstat );
		H_ASSERT( stat_result == 0);
		if( stat_result == 0)
		{
			stat_result = _wstat( hsf_file, &hsf_fstat );
			if( stat_result == 0 )
			{
				if( (difftime(hsf_fstat.st_mtime, dwg_fstat.st_mtime) > 0.0) &&
					(hsf_fstat.st_size > 0))
					do_import = false;
			}
		}
	}

	if(do_import)
	{
		m_vhash_SegName_IsPresentFlag = new_vhash(1,malloc,free);
		m_vhash_StyleSegName_IsPresentFlag = new_vhash(1,malloc,free);
		if(!m_bAmIXref)
		{
			int has_write_permission = HasWritePermission(hsf_file);
			if(has_write_permission == 0)
			{
				////// We need to create the hsf in the temp folder ...
				//DWORD dwBufSize=512;
				//DWORD dwRetVal;
				//wchar_t lpPathBuffer[512];
				//dwRetVal = GetTempPath(dwBufSize,lpPathBuffer);
				//wchar_t temp_path[_MAX_PATH];				
				//wcscpy(temp_path,(lpPathBuffer));
				//wcscat(temp_path,L"DWG_Export\\");

				////////////////////////////////////////////////////////////////////
				///replacement for above commented code which was windows specific.......
				char * pPath;
				pPath = getenv ("TEMP");
				size_t origsize = strlen(pPath) + 1;
				wchar_t tempPathName[MVO_BUFFER_SIZE];
				mbstowcs_s(0, tempPathName, origsize, pPath, _TRUNCATE);
				wchar_t temp_path[_MAX_PATH];				
				wcscpy(temp_path,tempPathName);
				wcscat(temp_path,L"/DWG_Export/");
				//////////////////////////////////////////////////////////////////////////

				if(!m_pXref_hsf_path)
					m_pXref_hsf_path = h_dwg_wcsdup(temp_path);
				else
					wcscpy(m_pXref_hsf_path,temp_path);
				_wmkdir(temp_path);
			}
		}

		if(m_pXref_hsf_path)
		{
			wchar_t hsf_file_name[_MAX_PATH];
			wchar_t unused_dir[_MAX_DIR];
			HUtility::FindFileNameAndDirectory((hsf_file), unused_dir, hsf_file_name);
			wcscpy(hsf_file, m_pXref_hsf_path);
			wcscat(hsf_file,hsf_file_name);
		}

		m_pHSFFile = wfopen(hsf_file, L"wb");
		H_ASSERT(m_pHSFFile);

		if(!m_bAmIXref)
		{
			int stat_result = _wstat( hsf_file, &m_MasterHsfFileTime );
		}

		if( !m_pHSFFile )
		{
			wchar_t err_msg[MVO_BUFFER_SIZE];
			swprintf(err_msg,MVO_BUFFER_SIZE, L"DWG Import Error: Failed to open %ls file for writing", hsf_file);
			m_pDWGInputHandler->ReportInputInformation(err_msg);
			return false;
		}

		m_mtImportStart = time(NULL);

		// tell the toolkit where to begin writing data; the size of the 'utility' buffer
		// can be anything; for this example, we use a 4k buffer
		m_pBStreamtk->PrepareBuffer(m_pBStreamBuffer, m_nBStreamBuffSize);
		m_pBStreamtk->SetAsciiMode(false);

		long flags = 0;

		if (!GetNormalCompression())
			flags |= TK_Full_Resolution_Normals;
		if (!GetVertexCompression())
			flags |= TK_Full_Resolution_Vertices;

		if (GetConnectivityCompression())
			flags |= TK_Connectivity_Compression;

		m_pBStreamtk->SetWriteFlags(flags);
		m_pBStreamtk->SetNumNormalBits(GetNormalCompressionBits());
		m_pBStreamtk->SetNumVertexBits(GetVertexCompressionBits());
		m_pBStreamtk->SetJpegQuality(GetImageCompressionValue());


		BBaseOpcodeHandler	*handler = 0;

		// create a TK_Header object and export it's associated HSF objects,
		// which include the TKE_Comment and TKE_File_Info objects
		// TK_Header automatically formats the TKE_Comment to contain file version 
		// information.  
		handler = new TK_Header();
		hdwg_status = WriteObject(handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete handler;

		// NOTE: Define the following preprocessor if you want the file to be compressed. 
		handler = new TK_Compression(TKE_Start_Compression);
		hdwg_status = WriteObject(handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		delete handler;
		////////////////////////- bstream

	}

	//--Begin Progress Msg
	{
		m_pDWGInputHandler->ReportInputProgress("DWG Import Progress: Loading database");
	}
	//--End Progress Msg

	AcDbDatabase *pDb = new AcDbDatabase(Adesk::kFalse);
	H_ASSERT(pDb != NULL);

	// Read the drawing  or dxf file.
	Acad::ErrorStatus acad_err;
	try
	{
		if(wcsieq(file_ext, L"dwg")) 
			acad_err = pDb->readDwgFile((FileName), _SH_DENYNO);
		else
			acad_err = pDb->dxfIn((FileName));
	}
	catch(DWGException* ex)
	{
		m_pDWGInputHandler->ReportInputInformation("DWG Read Error:");
		m_pDWGInputHandler->ReportInputInformation(ex->what());
		acad_err = Acad::eCantOpenFile;
		delete ex;
	}

	if( acad_err != Acad::eOk)
	{
		//-- Begin Information Report
		m_pDWGInputHandler->ReportInputInformation("DWG Import Error: Failed to load AcDbDatabase");
		//-- End Information Report

		delete pDb;
		fclose(m_pHSFFile);
		return false;
	}

	if(do_import)
	{
		result = importDWGDatabase(pDb, modelKey, pInputOptions);

		///////////////////////////
		BBaseOpcodeHandler* handler = new TK_Compression(TKE_Stop_Compression);
		hdwg_status = WriteObject(handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		delete handler;

		// export a TKE_termination object
		handler = new TK_Terminator(TKE_Termination);
		hdwg_status = WriteObject(handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete handler;

		// ask the toolkit how much of the final buffer is filled
		m_nBStreamBuffCount = m_pBStreamtk->CurrentBufferLength();

		// write out the final buffer
		fwrite(m_pBStreamBuffer, sizeof (char), m_nBStreamBuffCount, m_pHSFFile);

		// close the file
		fclose(m_pHSFFile);

		// Just to cleanup the vhash - this much code is required
		if(m_vhash_SegName_IsPresentFlag)
		{
			delete_vhash(m_vhash_SegName_IsPresentFlag);
			m_vhash_SegName_IsPresentFlag=0;
		} 

		// Just to cleanup the vhash - this much code is required
		if(m_vhash_StyleSegName_IsPresentFlag)
		{
			delete_vhash(m_vhash_StyleSegName_IsPresentFlag);
			m_vhash_StyleSegName_IsPresentFlag=0;
		} 
	}

#ifdef HIODWG_IMPORT_USE_HSF_XREFS
	// resolve the xrefs and import each of them
	importXRefs(pDb, modelKey, pInputOptions);
#endif

	// NOTE: This is equivalent to 	delete pDb; in a non-AutoCAD-based host environment
	//if(!m_pConnectivityInfo)
	acdbReleaseHostDwg(pDb);

	if(do_import)
	{
		wchar_t temp[MVO_BUFFER_SIZE];
		wchar_t scene_data[MVO_BUFFER_SIZE];
		wcscpy(scene_data, FileName);
		wcscat(scene_data, L"\n");
		if(m_nLine_count>0)
		{
			swprintf(temp,MVO_BUFFER_SIZE, L"\tProcessed  %i LINES\n", m_nLine_count);
			wcscat(scene_data, temp);
		}
		if(m_nPoint_count>0)
		{
			swprintf(temp,MVO_BUFFER_SIZE, L"\tProcessed  %i POINTS\n", m_nPoint_count);
			wcscat(scene_data, temp);
		}
		if(m_nCircle_count>0)
		{
			swprintf(temp,MVO_BUFFER_SIZE, L"\tProcessed  %i CIRCLES\n", m_nCircle_count);
			wcscat(scene_data, temp);
		}
		if(m_nArc_count>0)
		{
			swprintf(temp,MVO_BUFFER_SIZE, L"\tProcessed  %i ARCS\n", m_nArc_count);
			wcscat(scene_data, temp);
		}
		if(m_nSolid_count>0)
		{
			swprintf(temp,MVO_BUFFER_SIZE, L"\tProcessed  %i SOLIDS\n", m_nSolid_count);
			wcscat(scene_data, temp);
		}
		if(m_nSolid3D_count>0)
		{
			swprintf(temp,MVO_BUFFER_SIZE, L"\tProcessed  %i 3D SOLIDS\n", m_nSolid3D_count);
			wcscat(scene_data, temp);
		}
		if(m_nPloyLine_count>0)
		{
			swprintf(temp,MVO_BUFFER_SIZE, L"\tProcessed  %i POLYLINES\n", m_nPloyLine_count);
			wcscat(scene_data, temp);;
		}

		m_pDWGInputHandler->ReportInputProgress(scene_data);
	}


	if( !m_bAmIXref )
	{
		//--Begin Progress Msg
		{
			m_pDWGInputHandler->ReportInputProgress("DWG Import Progress: Creating Scene graph");
		}
		//--End Progress Msg

		HInputHandler *hsf_reader = HDB::GetHIOManager()->GetInputHandler(("hsf"));

		HSFNoticer * noticer = new HSFNoticer(m_pDWGInputHandler);
		HSFInfoNoticer * info_noticer = new HSFInfoNoticer(m_pDWGInputHandler);
		hsf_reader->SetInputProgressNoticeCallback(noticer);
		hsf_reader->SetInputInformationNoticeCallback(info_noticer);
		hsf_reader->SetInputPercentProgressNoticeCallback(noticer);

		HFileInputResult hsf_write_result = hsf_reader->FileInputByKey(hsf_file, modelKey, pInputOptions);

		hsf_reader->SetInputProgressNoticeCallback(0);
		hsf_reader->SetInputInformationNoticeCallback(0);
		hsf_reader->SetInputPercentProgressNoticeCallback(0);

		delete noticer;
		delete info_noticer;


		if( hsf_write_result != InputOK)
		{
			char err_msg[MVO_BUFFER_SIZE];
			sprintf(err_msg, "DWG Import Error: Failed to open %s file for loading", hsf_file);
			m_pDWGInputHandler->ReportInputInformation(err_msg);
			result = false;
		}
	}

	return result;
}

bool HDWG_BStreamImporter::importXRefs(AcDbDatabase* pHostDb, HC_KEY modelKey, HInputHandlerOptions * pInputOptions)
{
	AcDbXrefGraph xref_graph;
	Acad::ErrorStatus acad_err = acdbGetHostDwgXrefGraph(pHostDb, xref_graph, Adesk::kTrue);
	if( acad_err != Acad::eOk )
		return false;

	int num_xrefs = xref_graph.numNodes();
	if(num_xrefs < 2)
		return true;

	const ACHAR* root_filename = 0;
	acad_err = pHostDb->getFilename(root_filename);
	if( !root_filename )
		return false;

	wchar_t dir_name[_MAX_DIR];
	HUtility::FindFileNameAndDirectory((root_filename), dir_name, 0);

	int i;
	for(i = 1; i < num_xrefs; i++)
	{
		AcDbXrefGraphNode* xref_node = xref_graph.xrefNode(i);
		if( xref_node == NULL )
			continue;

		AcDbObjectId blrId = xref_node->btrId();
		AcDbBlockTableRecord *tblRecord = 0;
		Acad::ErrorStatus es = acdbOpenObject(tblRecord, blrId, AcDb::kForRead);

		if(!tblRecord)
			continue;
		///// if the master itself is an xref, then we don't load overlay xrefs of that master
		bool is_overlay = tblRecord->isFromOverlayReference();
		if( m_bAmIXref && is_overlay )
		{
			tblRecord->close();
			continue;
		}

		const ACHAR* blrFullPath;
		tblRecord->pathName(blrFullPath);
		tblRecord->close();

		wchar_t orig_pathName[_MAX_DIR];
		wchar_t final_dwg_filepath[_MAX_PATH];
		bool file_exist = false;

		wcscpy(orig_pathName, blrFullPath);
		do {

			// try the file as is
			file_exist = check_file_exist(orig_pathName, L"");
			if(file_exist)
			{
				wcscpy(final_dwg_filepath,orig_pathName);
				break;
			}

			if(orig_pathName[0] == '.')
			{
				if(orig_pathName[1] == '.') //..
				{
					wcscpy(final_dwg_filepath,dir_name);
					wcscat(final_dwg_filepath,orig_pathName);
					file_exist = check_file_exist(final_dwg_filepath, L"");
					if( file_exist )
						break;
				}
				else  //.
				{
					wchar_t blrFullPath_no_dot[_MAX_PATH];
					wchar_t blrFullPath_with_dot[_MAX_PATH];
					wcscpy( blrFullPath_with_dot, orig_pathName);
					wcscpy(blrFullPath_no_dot, L"");
					wcsncat(blrFullPath_no_dot, &(blrFullPath_with_dot[2]), wcslen(blrFullPath_with_dot)-2);
					wcscpy(final_dwg_filepath, dir_name);
					wcscat(final_dwg_filepath, blrFullPath_no_dot);
					file_exist = check_file_exist(final_dwg_filepath, L"");
					if( file_exist )
						break;
				}
			}

			// not there yet?
			const ACHAR* xref_name = xref_node->name();
			swprintf(final_dwg_filepath, _MAX_PATH, L".\\%ls.dwg", (xref_name));
			file_exist = check_file_exist(final_dwg_filepath, L"");
			if( file_exist ) 
				break;

			// use master's directory
			swprintf(final_dwg_filepath, _MAX_PATH, L"%ls%ls.dwg", dir_name, (xref_name));
			file_exist = check_file_exist(final_dwg_filepath, L"");
			if( file_exist ) 
				break;

			break;
		} while(1);

		if(file_exist)
		{
			// dwg file exists, now let's check if an hsf with more recent timestamp exists

			wchar_t hsf_file[_MAX_PATH];
			size_t len = wcslen(final_dwg_filepath) - wcslen(L".dwg");
			wcsncpy(hsf_file, final_dwg_filepath, len);
			hsf_file[len] = L'\0';
			wcscat(hsf_file, L".hsf");
			bool do_import = true;
			if(pInputOptions->m_bForceReimport)
			{
				struct _stat hsf_fstat;
				int stat_result = _wstat( hsf_file, &hsf_fstat );
				if (stat_result == 0)
				{
					// also check if this HSF is already being imported in this session.
					// we have recorded the start time of this session, compare current files fstat with that.-SumitK[100809]
					int diff = m_MasterHsfFileTime.st_mtime - hsf_fstat.st_mtime;
					if(difftime(hsf_fstat.st_mtime, m_MasterHsfFileTime.st_mtime) > 0.00 && (hsf_fstat.st_size > 0))
					{
						//we have already imported this file in this session and no need to go further.
						// just read the stream file from the location and bail out.-SumitK[100809]
						do_import = false;	
					}
				}
			}
			else
			{
				struct _stat dwg_fstat;
				struct _stat hsf_fstat;
				int stat_result = _wstat( final_dwg_filepath, &dwg_fstat );
				H_ASSERT( stat_result == 0);
				if( stat_result == 0)
				{
					stat_result = _wstat( hsf_file, &hsf_fstat );
					if( stat_result == 0 )
					{
						if( (difftime(hsf_fstat.st_mtime, dwg_fstat.st_mtime) > 0.0) && (hsf_fstat.st_size > 0))
						{
							do_import = false;
						}
					}
				}
			}
			// Code ends
			if( do_import )
			{
				HDWG_BStreamImporter importer(m_pDWGInputHandler, true);
				importer.m_listDWGLayouts = m_listDWGLayouts;
				if(m_pXref_hsf_path)
				{
					importer.m_pXref_hsf_path = h_dwg_wcsdup(m_pXref_hsf_path);
				}
				importer.importDWGFile(final_dwg_filepath, modelKey, pInputOptions);
			}
		}
		else
		{
			//-- Begin Information Report
			wchar_t err_msg[MVO_BUFFER_SIZE];
			swprintf(err_msg, MVO_BUFFER_SIZE, L"DWG Import Error: Unable to locate XRef file - %ls ", orig_pathName);
			m_pDWGInputHandler->ReportInputInformation(err_msg);
			//-- End Information Report
		}
		m_pDWGInputHandler->ReportInputPercentProgress(i/(float)num_xrefs);
	}

	return true;
}


void HDWG_BStreamImporter::update_layout_list(AcDbDatabase* pAcDbDatabase)
{
	m_listDWGLayouts = new_vlist(malloc, free);

	AcDbDictionary* pDict = NULL;
	if(pAcDbDatabase->getLayoutDictionary( pDict, AcDb::kForRead ) == Acad::eOk)
	{
		AcDbDictionaryIterator* dItr = NULL;
		dItr = pDict->newIterator();
		while (!dItr->done())
		{
			AcDbObject* pLayObj=NULL;
			if (dItr->getObject(pLayObj, AcDb::kForRead) == Acad::eOk)
			{
				AcDbLayout *layout = 0;
				layout = AcDbLayout::cast(pLayObj);
				ACHAR* layoutName;
				layout->getLayoutName(layoutName);
				if(wcsicmp(L"Model", layoutName))//Include only Paper_Sapce layout to import
				{
					vlist_add_after_cursor(m_listDWGLayouts, layoutName);
				}
				pLayObj->close();
			}
			dItr->next();
		}
		delete dItr;
		pDict->close();
	}
}


bool HDWG_BStreamImporter::importDWGDatabase(AcDbDatabase* pAcDbDatabase, HC_KEY modelKey, HInputHandlerOptions * pInputOptions)
{
	m_modelKey = modelKey;
	HPoint max_lim;
	HPoint min_lim;


	bool result = false;

	if( pInputOptions )
	{
		m_pInputOptions = pInputOptions; 

		if( pInputOptions->m_pConnector )
			m_pConnectivityInfo = (HIOConnectorDWG*) pInputOptions->m_pConnector;

		m_pDWGTextureDirectory = (wchar_t*) pInputOptions->m_pExtendedData;
		m_Deviation = pInputOptions->m_Deviation;
		m_bImportXData = pInputOptions->m_bImportMetadata;
		m_listRegAppNames = pInputOptions->m_listRegAppNames;
		m_listEntityType=pInputOptions->m_listEntityType;
		m_bImportWireframeForBrep = pInputOptions->m_bImportWireframeForBrep;
		m_numIsolines = pInputOptions->m_numIsolines;
		m_listDWGLayouts = pInputOptions->m_listDWGLayouts;
		m_bAttachDWGHandles = pInputOptions->m_bAttachDWGHandles;
		m_bImportAllLayouts = pInputOptions->m_bImportAllLayouts;
		m_bIgnoreOffEntity = pInputOptions->m_bIgnoreOffEntities;
		m_bDWGInsertMeshesAsShells = pInputOptions->m_bDWGInsertMeshesAsShells;
		m_bDisableDWGDrawOrder =  pInputOptions->m_bDisableDWGDrawOrder;
	}

	//HC_Open_Segment_By_Key(m_modelKey);

	if(m_pConnectivityInfo)
		m_pConnectivityInfo->SetDatabase(pAcDbDatabase);

	// only Global scale factor of master file is required
	if(m_bAmIXref == false)
	{
		global_GlobalScaleFactor = pAcDbDatabase->ltscale();
	}
	m_dGlobalScaleFactor = global_GlobalScaleFactor ;

	acdbHostApplicationServices()->setWorkingDatabase(pAcDbDatabase);

	// COMMENTING THIS OUT. SINCE I AM NOW REVERSING THE NORMALS BEFORE INSERTING
	// AND THAT TURNS OUT TO MAKE HANDEDNESS LEFT AND NOT RIGHT.
	//// I have noticed that DWG files are right-handed. So, set it
	//// ALERT: There is no documentation in stream toolkit on how to set handedness, it's not intuitive
	//// I just rev. engg. it using partviewer.
	//TK_Heuristics* heuristic_handler = new TK_Heuristics;
	//heuristic_handler->SetMask( TKO_Heuristic_Polygon_Handedness );
	//heuristic_handler->SetValue( 4 );
	//heuristic_handler->SetExtras(TKO_Heuristic_Polygon_Handedness);
	//TK_Status hdwg_status = WriteObject(heuristic_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	//H_ASSERT(hdwg_status == TK_Normal);
	//delete heuristic_handler;

#ifndef HIODWG_IMPORT_USE_HSF_XREFS
	acdbResolveCurrentXRefs(pAcDbDatabase);
#endif

	if(!m_bAmIXref)
	{
		//Units information as User_Option
		AcDb::UnitsValue units = pAcDbDatabase->insunits();
		char units_option[MVO_BUFFER_SIZE];
		strcpy(units_option, "dwg_unit=");
		switch(units)
		{
		case AcDb::kUnitsUndefined:
			strcat(units_option, "Undefined Units");
			break;
		case AcDb::kUnitsInches:
			strcat(units_option, "Inches");
			break;
		case AcDb::kUnitsFeet:
			strcat(units_option, "Feet");
			break;
		case AcDb::kUnitsMiles:
			strcat(units_option, "Miles");
			break;
		case AcDb::kUnitsMillimeters:
			strcat(units_option, "Millimeters");
			break;
		case AcDb::kUnitsCentimeters:
			strcat(units_option, "Centimeters");
			break;
		case AcDb::kUnitsMeters:
			strcat(units_option, "Meters");
			break;
		case AcDb::kUnitsKilometers:
			strcat(units_option, "Kilometers");
			break;
		case AcDb::kUnitsMicroinches:
			strcat(units_option, "Microinches");
			break;
		case AcDb::kUnitsMils:
			strcat(units_option, "Mils");
			break;
		case AcDb::kUnitsYards:
			strcat(units_option, "Yards");
			break;
		case AcDb::kUnitsAngstroms:
			strcat(units_option, "Angstrom");
			break;
		case AcDb::kUnitsNanometers:
			strcat(units_option, "Nanometers");
			break;
		case AcDb::kUnitsMicrons:
			strcat(units_option, "Microns");
			break;
		case AcDb::kUnitsDecimeters:
			strcat(units_option, "Decimeters");
			break;
		case AcDb::kUnitsDekameters:
			strcat(units_option, "Dekameters");
			break;
		case AcDb::kUnitsHectometers:
			strcat(units_option, "Hectometers");
			break;
		case AcDb::kUnitsGigameters:
			strcat(units_option, "Gigameters");
			break;
		case AcDb::kUnitsAstronomical:
			strcat(units_option, "Astronomical");
			break;
		case AcDb::kUnitsLightYears:
			strcat(units_option, "Light Years");
			break;
		case AcDb::kUnitsParsecs:
			strcat(units_option, "Parsecs");
			break;
		default:
			strcat(units_option, "Undefined Units");
		}
		// Bounding box info
		max_lim.Set(pAcDbDatabase->extmax().x, pAcDbDatabase->extmax().y, pAcDbDatabase->extmax().z);
		min_lim.Set(pAcDbDatabase->extmin().x, pAcDbDatabase->extmin().y, pAcDbDatabase->extmin().z);
		char extents[MVO_BUFFER_SIZE];
		sprintf(extents,"Extents_min =%lf %lf %lf, Extents_max =%lf %lf %lf",min_lim.x, min_lim.y, min_lim.z, max_lim.x, max_lim.y, max_lim.z);

		//HC_Open_Segment("info");
		char seg_name[MVO_BUFFER_SIZE];
		sprintf(seg_name, "info");
		TK_Open_Segment* open_seg_handler = new TK_Open_Segment;
		open_seg_handler->SetSegment(seg_name);
		TK_Status hdwg_status = WriteObject(open_seg_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete open_seg_handler;

		TK_Unicode_Options* user_options;
		//HC_Set_User_Options(units_option);
		user_options= new TK_Unicode_Options;
		user_options->SetOptions((unsigned short const*)H_UTF16(units_option).encodedText());
		hdwg_status = WriteObject(user_options, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete user_options;

		//HC_Set_User_Options(extents);
		user_options= new TK_Unicode_Options;
		user_options->SetOptions((unsigned short const*)H_UTF16(extents).encodedText());
		hdwg_status = WriteObject(user_options, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete user_options;

		//HC_Close_Segment();
		TK_Close_Segment* close_seg_handler = new TK_Close_Segment;
		hdwg_status = WriteObject(close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete close_seg_handler;
	}


	//importAcDbDatabase(pAcDbDatabase);
	//VC: Set this database values only once
	Adesk::UInt16 db_color_idx = pAcDbDatabase->cecolor().colorIndex(); 
	Adesk::UInt32 RGBM_byte = AcCmEntityColor::lookUpRGB(db_color_idx);
	float r,g,b;
	r = (float) GetRValueFromRGBM(RGBM_byte)/255.0f;
	g = (float) GetGValueFromRGBM(RGBM_byte)/255.0f;
	b = (float) GetBValueFromRGBM(RGBM_byte)/255.0f;

	//HC_Set_Color_By_Value ("geometry","RGB", r, g, b);

	TK_Status hdwg_status; 
	TK_Color_RGB *rgb_color_handler;
	rgb_color_handler = new TK_Color_RGB();
	rgb_color_handler->SetGeometry (TKO_Geo_Geom_Colors);
	rgb_color_handler->SetRGB(r, g, b);
	hdwg_status = WriteObject(rgb_color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete rgb_color_handler;

	// TODO: make sure how to get LWDEFAULT
	AcDb::LineWeight db_line_weight = H_LWDEFAULT; //pDatabase->celweight();
	float h_line_size = 0;
	h_line_size = db_line_weight * H_MM_TO_POINTS/100.0f;
	//HC_Set_Line_Weight(h_line_size);

	//set the marker defaults using PDMODE and PDSIZE database settings.
	if(!m_bAmIXref)
	{
		Adesk::Int16 db_pdmode = pAcDbDatabase->pdmode();
		double db_pdsize = pAcDbDatabase->pdsize();
		set_marker_settings(db_pdmode,db_pdsize );
	}

	TK_Size	*size_handler;
	size_handler= new TK_Size(TKE_Line_Weight);
	size_handler->SetSize(h_line_size); 
	hdwg_status = WriteObject(size_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete size_handler;

	TK_Unicode_Options user_options_handler;
	wchar_t file_data[MVO_BUFFER_SIZE];
	condition_string_for_user_options(m_pFileName);
	swprintf(file_data, MVO_BUFFER_SIZE, L"FileName=%ls",m_pFileName);
	user_options_handler.Reset();
	user_options_handler.SetOptions((unsigned short const*)H_UTF16(file_data).encodedText());
	hdwg_status = WriteObject(&user_options_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);

	if(m_bImportXData)
	{
		importLBGEData();
	}

	if(m_bImportAllLayouts && !m_listDWGLayouts) // and if the user is not providing the list already.
	{
		update_layout_list(pAcDbDatabase);
	}
	//VC: DWG Layout import support. If layouts are not provided, import MODEL_SPACE by default
	if(m_listDWGLayouts && !m_bAmIXref )
	{
		import_layout(pAcDbDatabase);
	}

	AcDbBlockTable *p;                                               
	if (pAcDbDatabase->getBlockTable(p, AcDb::kForRead) == Acad::eOk) 
	{  
		AcDbBlockTableIterator *pIter;
		AcDbBlockTableRecord *pRecord = 0;
		AcDbBlockTableRecord *pModelSpaceRecord = 0;
		p->newIterator(pIter);

		while (!pIter->done())
		{
			if (pIter->getRecord(pRecord, AcDb::kForRead) == Acad::eOk)
			{
				wchar_t *pName;
				if (pRecord && (pRecord->getName(pName) == Acad::eOk))
				{
					if (!(wcsicmp(L"*MODEL_SPACE", pName)))
					{
						if(!m_listDWGLayouts || m_bAmIXref)
						{
							importBlockTableRecord(pRecord);
							// Set initial View
							if(!m_bAmIXref)
								set_initial_view_for_model_space(pAcDbDatabase);
						}
						else
						{
							TK_Open_Segment* open_seg_handler = NULL;
							TK_Close_Segment *close_seg_handler = NULL;

							wchar_t model_space_seg_name[MVO_BUFFER_SIZE];
							swprintf(model_space_seg_name, MVO_BUFFER_SIZE, L"btable_%p_%ls", pRecord, (pName));
							condition_string_for_segment_name(model_space_seg_name);
							wchar_t ms_seg_name[MVO_BUFFER_SIZE]={L""};
							wcscpy(ms_seg_name,H_UNICODE_TEXT(ms_seg_name));
							swprintf(ms_seg_name,MVO_BUFFER_SIZE, L"/include library/other block table records/model space/%s", model_space_seg_name);
							vhash_status_t vhash_status;
							void* model_space_seg_present = false;
							vhash_status = vhash_lookup_string_key_item(m_vhash_SegName_IsPresentFlag, H_ASCII_TEXT(ms_seg_name), (void**)&model_space_seg_present);

							if(model_space_seg_present)
							{
								//Open Segment of "MS Include"
								char seg_name1[24];
								sprintf(seg_name1, "Model_Space");
								open_seg_handler = new TK_Open_Segment;
								open_seg_handler->SetSegment(seg_name1);
								hdwg_status = WriteObject(open_seg_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
								H_ASSERT(hdwg_status == TK_Normal);
								delete open_seg_handler;

								//HC_Include_Segment_By_Key(model_space_key);
								TK_Referenced_Segment	*referenced_segment_handler=NULL;
								referenced_segment_handler = new TK_Referenced_Segment(TKE_Include_Segment);
								referenced_segment_handler->SetSegment(H_ASCII_TEXT(ms_seg_name));
								hdwg_status = WriteObject(referenced_segment_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
								H_ASSERT(hdwg_status == TK_Normal);
								delete referenced_segment_handler;

								// Set Bounding box info
								//HC_Open_Segment("Bounding_Box");
								sprintf(seg_name1, "Bounding_Box");
								open_seg_handler = new TK_Open_Segment;
								open_seg_handler->SetSegment(seg_name1);
								hdwg_status = WriteObject(open_seg_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
								H_ASSERT(hdwg_status == TK_Normal);
								delete open_seg_handler;


								char extents[MVO_BUFFER_SIZE];
								sprintf(extents,"Extents_min =%lf %lf %lf, Extents_max =%lf %lf %lf",min_lim.x, min_lim.y, min_lim.z, max_lim.x, max_lim.y, max_lim.z);

								TK_User_Options* user_options;
								//HC_Set_User_Options(extents);
								user_options= new TK_User_Options;
								user_options->SetOptions(extents);
								hdwg_status = WriteObject(user_options, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
								H_ASSERT(hdwg_status == TK_Normal);
								delete user_options;

								//Close Bounding Box Segment
								close_seg_handler = new TK_Close_Segment;
								hdwg_status = WriteObject(close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
								H_ASSERT(hdwg_status == TK_Normal);
								delete close_seg_handler;

								// If the user wants a specific layout ON by sending list, model_space should remain OFF.
								// This is to make sure that previous applications (prior to m_bImportAllLayouts) would work as they were. 
								if(! m_bImportAllLayouts)
								{
									//HC_Set_Visibility("off");
									TK_Visibility	*vis_handler = new TK_Visibility();
									vis_handler->SetGeometry(TKO_Geo_All_Visibles);
									vis_handler->SetValue(0);
									hdwg_status = WriteObject(vis_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
									H_ASSERT(hdwg_status == TK_Normal);
									delete vis_handler;

									//HC_Set_Heuristics("exclude bounding");
									TK_Heuristics* heuristic_handler = new TK_Heuristics;
									heuristic_handler->SetMask( TKO_Heuristic_Exclude_Bounding );
									heuristic_handler->SetValue( TKO_Heuristic_Exclude_Bounding );
									TK_Status hdwg_status = WriteObject(heuristic_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
									H_ASSERT(hdwg_status == TK_Normal);
									delete heuristic_handler;
								}
								else
								{
									// Set initial View
									set_initial_view_for_model_space(pAcDbDatabase);
								}

								// Set unicode option for layout name it hepls in finding layouts while
								// setting visibility
								TK_Unicode_Options* unicode_options;
								//HC_Set_User_Options("layout = model");
								unicode_options = new TK_Unicode_Options;
								unicode_options->SetOptions((unsigned short const*)H_UTF16("layout = model").encodedText());
								hdwg_status = WriteObject(unicode_options, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
								H_ASSERT(hdwg_status == TK_Normal);
								delete unicode_options;

								//Close Model Space Segment
								close_seg_handler = new TK_Close_Segment;
								hdwg_status = WriteObject(close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
								H_ASSERT(hdwg_status == TK_Normal);
								delete close_seg_handler;
							}

						}
					}
					acdbFree(pName);
				}
				pRecord->close();
			}
			pIter->step();
		}
		delete pIter;

		p->close();		

	}

	//Refer Eventum Issue : 8316 and 8296
	//if( m_bIs3D )
	//{
	//	// Switch of the text if this is a 3D DWG
	//	// There could a better way to do this, may be as an input option? - Rajesh B (18-Dec-07)
	//	TK_Visibility	*vis_handler = new TK_Visibility();
	//	vis_handler->SetGeometry(TKO_Geo_text);
	//	vis_handler->SetValue(0);
	//	TK_Status hdwg_status = WriteObject(vis_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	//	H_ASSERT(hdwg_status == TK_Normal);
	//	delete vis_handler;
	//}

	result = true;

	//HC_Close_Segment();

	return result;
}
void HDWG_BStreamImporter::import_layout(AcDbDatabase* pAcDbDatabase)
{
	wchar_t model_space_seg_name[MVO_BUFFER_SIZE];
	wchar_t paper_space_seg_name[MVO_BUFFER_SIZE];
	AcDbBlockTable *p;                                               
	if (pAcDbDatabase->getBlockTable(p, AcDb::kForRead) == Acad::eOk) 
	{  
		AcDbBlockTableIterator *pIter;
		AcDbBlockTableRecord *pRecord = 0;
		AcDbBlockTableRecord *pModelSpaceRecord = 0;
		p->newIterator(pIter);

		while (!pIter->done())
		{
			if (pIter->getRecord(pRecord, AcDb::kForRead) == Acad::eOk)
			{
				wchar_t *pName;
				if (pRecord && (pRecord->getName(pName) == Acad::eOk))
				{
					if (!wcsicmp(L"*MODEL_SPACE", pName))
					{
						importBlockTableRecord(pRecord);
						swprintf(model_space_seg_name, MVO_BUFFER_SIZE, L"btable_%p_%ls", pRecord, (pName));
					}
					acdbFree(pName);
				}
				pRecord->close();
			}
			pIter->step();
		}
		delete pIter;
		p->close();		
	}

	//<< Hide the model space segment in include library
	STREAM_Open_Segment("/include library/other block table records/model space");

	//HC_Set_Visibility("off");
	TK_Visibility	*vis_handler = new TK_Visibility();
	vis_handler->SetGeometry(TKO_Geo_All_Visibles);
	vis_handler->SetValue(0);
	TK_Status hdwg_status = WriteObject(vis_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete vis_handler;

	///////close model space
	STREAM_Close_Segment();
	//>> Hide the model space segment in include library


	AcDbDictionary* pDict = NULL;
	AcDbLayoutManager *pLayMan;
	Acad::ErrorStatus mEs;
	pLayMan = (AcDbLayoutManager *)acdbHostApplicationServices()->layoutManager();

	if(pAcDbDatabase->getLayoutDictionary( pDict, AcDb::kForRead ) == Acad::eOk)
	{
		AcDbDictionaryIterator* dItr = NULL;
		dItr = pDict->newIterator();
		bool isFirstLayout = true;

		while (!dItr->done())
		{
			// Set this Layout as current -  for 11137
			mEs = pLayMan->setCurrentLayoutId(dItr->objectId());

			AcDbObject* pLayObj=NULL;
			if (dItr->getObject(pLayObj, AcDb::kForRead) == Acad::eOk)
			{
				AcDbLayout *layout = 0;
				layout = AcDbLayout::cast(pLayObj);
				ACHAR* layoutName;
				layout->getLayoutName(layoutName);

				vlist_reset_cursor(m_listDWGLayouts);
				wchar_t * layout_name = 0;
				while((layout_name = (wchar_t*) vlist_peek_cursor(m_listDWGLayouts)))
				{
					if (wcscmp(layoutName, (layout_name)) == 0)
					{
						m_bCleanVpList = true;
						AcDbObjectId layoutId = layout->getBlockTableRecordId();
						AcDbBlockTableRecord *pRecordLay = 0;
						if(acdbOpenObject(pRecordLay, layoutId, AcDb::kForRead) == Acad::eOk)
						{
							importBlockTableRecord(pRecordLay);//Import Paper_Space layout

							/*
							wchar_t * Layout_Name;								
							wchar_t pLayName[MVO_BUFFER_SIZE];

							pRecordLay->getName(Layout_Name);
							wcscpy(pLayName, Layout_Name);
							condition_string_for_segment_name(pLayName);
							acdbFree(Layout_Name);
							//swprintf(paper_space_seg_name,MVO_BUFFER_SIZE,L"btable_%p_%ls", pRecordLay, layout_name);
							*/

							swprintf(paper_space_seg_name,MVO_BUFFER_SIZE,L"btable_%p_%ls", pRecordLay, layoutName);
							condition_string_for_segment_name(paper_space_seg_name);
							pRecordLay->close();

							//char ms_seg_name[MVO_BUFFER_SIZE];
							condition_string_for_segment_name(model_space_seg_name);
							//sprintf(ms_seg_name, "/include library/other block table records/model space/%s", H_ASCII_TEXT(model_space_seg_name));
							wchar_t ms_seg_name[MVO_BUFFER_SIZE]={L""};
							wcscpy(ms_seg_name,H_UNICODE_TEXT(ms_seg_name));
							swprintf(ms_seg_name,MVO_BUFFER_SIZE, L"/include library/other block table records/model space/%s", model_space_seg_name);
							vhash_status_t vhash_status;
							void* model_space_seg_present = false;
							vhash_status = vhash_lookup_string_key_item(m_vhash_SegName_IsPresentFlag, H_ASCII_TEXT(ms_seg_name), (void**)&model_space_seg_present);

							if(model_space_seg_present)
							{
								TK_Open_Segment* open_seg_handler = NULL;
								TK_Close_Segment *close_seg_handler = NULL;
								TK_Status hdwg_status = TK_Error;

								vhash_status_t vhash_status;
								void* paper_space_seg_present = false;
								vhash_status = vhash_lookup_string_key_item(m_vhash_SegName_IsPresentFlag, H_ASCII_TEXT(paper_space_seg_name), (void**)&paper_space_seg_present);
								if(paper_space_seg_present)
								{
									STREAM_Open_Segment(H_ASCII_TEXT(paper_space_seg_name)); // Open Paper Space Segment
									{

										//Set some option, so that it will not get optimized 
										wchar_t temp[MVO_BUFFER_SIZE];
										condition_string_for_user_options(layoutName);
										swprintf(temp, MVO_BUFFER_SIZE, L"Layout=%ls",layoutName);

										TK_Unicode_Options* unicode_options;
										unicode_options = new TK_Unicode_Options;
										unicode_options->SetOptions((unsigned short const*)H_UTF16(temp).encodedText());
										hdwg_status = WriteObject(unicode_options, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
										H_ASSERT(hdwg_status == TK_Normal);
										delete unicode_options;


										if(!isFirstLayout || m_bImportAllLayouts)
										{
											//HC_Set_Visibility("off");
											TK_Visibility	*vis_handler = new TK_Visibility();
											vis_handler->SetGeometry(TKO_Geo_All_Visibles);
											vis_handler->SetValue(0);
											hdwg_status = WriteObject(vis_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
											H_ASSERT(hdwg_status == TK_Normal);
											delete vis_handler;

											//HC_Set_Heuristics("exclude bounding");
											TK_Heuristics* heuristic_handler = new TK_Heuristics;
											heuristic_handler->SetMask( TKO_Heuristic_Exclude_Bounding );
											heuristic_handler->SetValue( TKO_Heuristic_Exclude_Bounding );
											TK_Status hdwg_status = WriteObject(heuristic_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
											H_ASSERT(hdwg_status == TK_Normal);
											delete heuristic_handler;

											//HC_Set_Rendering_Options("attribute lock = visibility");
											TK_Rendering_Options * rendering_handler = new TK_Rendering_Options;
											rendering_handler->SetMask(TKO_Rendo_Attribute_Lock);
											rendering_handler->SetValue(TKO_Rendo_Attribute_Lock);
											rendering_handler->SetLockMask(TKO_Lock_Visibility);
											rendering_handler->SetLockValue(TKO_Lock_Visibility);
											rendering_handler->SetVisibilityLockMask(TKO_Geo_All_Visibles);
											rendering_handler->SetVisibilityLockValue(TKO_Geo_All_Visibles);
											hdwg_status = WriteObject(rendering_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
											H_ASSERT(hdwg_status == TK_Normal);
											delete rendering_handler;
										}
										else
										{
											isFirstLayout = false;
										}
										AcDbObjectId paper_space_vp_id = 0;
										paper_space_vp_id = pAcDbDatabase->paperSpaceVportId();

										for (int i = 0; i < (int)m_VpIdCount.size(); i++)
										{
											AcDbObjectId viewPortId = m_VpIdCount.at(i);
											if(paper_space_vp_id != viewPortId ) //To ignore top level viewport
												//if(size && (i != ignore_id) )
											{
												char vp_seg_name[1024];
												sprintf(vp_seg_name, "view_port_%p",viewPortId);
												//open segment here for each viewport in layout.
												//HC_Open_Segment(vp_seg_name);
												STREAM_Open_Segment(vp_seg_name);
												{

													HPoint ClipPoint[32];
													float *matrix = new float[16];
													AcCmEntityColor* entityColor = new AcCmEntityColor();
													int no_ClipPoint = 0;
													bool is_On;
													get_layout_data(viewPortId,pAcDbDatabase,ClipPoint,matrix,&no_ClipPoint,entityColor, &is_On);
													double r = entityColor->red()/255;
													double g = entityColor->green()/255;
													double b = entityColor->blue()/255;

													if(is_On)
													{												
														STREAM_Open_Segment("MS Include"); //Open Segment of "MS Include"
														{
															//HC_Set_Heuristics("exclude bounding");
															TK_Heuristics* heuristic_handler = new TK_Heuristics;
															heuristic_handler->SetMask( TKO_Heuristic_Exclude_Bounding );
															heuristic_handler->SetValue( TKO_Heuristic_Exclude_Bounding );
															TK_Status hdwg_status = WriteObject(heuristic_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
															H_ASSERT(hdwg_status == TK_Normal);
															delete heuristic_handler;

															//Include the Model_Space in paper_space
															//HC_Include_Segment_By_Key(model_space_key);
															TK_Referenced_Segment	*referenced_segment_handler=NULL;
															referenced_segment_handler = new TK_Referenced_Segment(TKE_Include_Segment);
															referenced_segment_handler->SetSegment(H_ASCII_TEXT(ms_seg_name));
															hdwg_status = WriteObject(referenced_segment_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
															H_ASSERT(hdwg_status == TK_Normal);
															delete referenced_segment_handler;

															//HC_Set_Modelling_Matrix(matrix);
															TK_Matrix	*matrix_handler;
															matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
															matrix_handler->SetMatrix(matrix);
															hdwg_status = WriteObject(matrix_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
															H_ASSERT(hdwg_status == TK_Normal);
															delete matrix_handler;

															//Set Clipping
															//HC_Set_Polygonal_Clip_Region(4,(HC_POINT*)(&rectClipPoint),"world");
															TK_Clip_Region* clip = new TK_Clip_Region;
															clip->SetPoints(no_ClipPoint, (float*)ClipPoint);
															clip->SetOptions(1);	//// Set the option to 1(world):Its default value is 0(window)
															hdwg_status = clip->Write(*m_pBStreamtk);
															H_ASSERT(hdwg_status == TK_Normal);
															delete clip;
														}
														STREAM_Close_Segment();//Close MS Include Segment
													}

													STREAM_Open_Segment("Clip Boundary");//HC_Open_Segment("clip_boundary");
													{
														HPoint* clip_region_point = new HPoint[no_ClipPoint+1];
														for(int i = 0; i < no_ClipPoint; i++)
														{
															clip_region_point[i] = ClipPoint[i];
														}

														clip_region_point[no_ClipPoint] = clip_region_point[0];

														TK_Polypoint	*line_handler;
														line_handler= new TK_Polypoint(TKE_Polyline);
														line_handler->SetPoints((no_ClipPoint+1), (float*)clip_region_point);
														hdwg_status = WriteObject(line_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
														H_ASSERT(hdwg_status == TK_Normal);
														delete line_handler;

														delete []clip_region_point;

														// query color and set on this segment
														float r,g,b;
														Adesk::UInt32 RGBM_byte = AcCmEntityColor::lookUpRGB(entityColor->colorIndex());
														r = (float) GetRValueFromRGBM(RGBM_byte)/255.0f;
														g = (float) GetGValueFromRGBM(RGBM_byte)/255.0f;
														b = (float) GetBValueFromRGBM(RGBM_byte)/255.0f;

														TK_Color_RGB  *color_handler = new TK_Color_RGB();
														color_handler->SetRGB(r,g, b);
														color_handler->SetGeometry (TKO_Geo_Geom_Colors);
														hdwg_status = WriteObject(color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
														H_ASSERT(hdwg_status == TK_Normal);
														delete color_handler;
													}
													STREAM_Close_Segment(); //close Clip Boundary
													delete []matrix;

												}
												STREAM_Close_Segment();//Close Viewport Segment
											}				
										}
										// For Bounding box
										AcGePoint2d min_Lim;
										AcGePoint2d max_Lim;
										layout->getLimits(min_Lim, max_Lim);

										// Set Bounding box info
										STREAM_Open_Segment("Bounding_Box");
										{
											char extents[MVO_BUFFER_SIZE];
											sprintf(extents,"Extents_min =%lf %lf 0.0, Extents_max =%lf %lf 0.0",min_Lim.x, min_Lim.y, max_Lim.x, max_Lim.y);

											TK_User_Options* user_options;
											//HC_Set_User_Options(extents);
											user_options= new TK_User_Options;
											user_options->SetOptions(extents);
											hdwg_status = WriteObject(user_options, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
											H_ASSERT(hdwg_status == TK_Normal);
											delete user_options;
										}
										STREAM_Close_Segment();//Close Bounding Box Segment
									}
									STREAM_Close_Segment();//Close Paper_Space Segment
								}
							}                            
						}
					}
					vlist_advance_cursor(m_listDWGLayouts);
				}
			}
			dItr->next();
			pLayObj->close();
		}
		delete dItr;
		pDict->close();
	}
}
void HDWG_BStreamImporter::set_initial_view_for_model_space(AcDbDatabase* pAcDbDatabase)
{
	if(!m_pInputOptions)
		return;

	if(!(m_pInputOptions->m_pHBaseView))
		return;

	AcDbViewportTable * pViewportTable;
	pAcDbDatabase->getViewportTable(pViewportTable, AcDb::kForRead);

	AcDbViewportTableIterator* pIterator;

	if ( pViewportTable->newIterator(pIterator) != Acad::eOk )
	{
		//L"\nCouldn't create ViewportTable iterator..."
		pViewportTable->close ();
		return;
	}

	AcDbViewportTableRecord *pCurrRecord = NULL;

	for ( pIterator->start (); !pIterator->done (); pIterator->step () )
	{
		AcDbViewportTableRecord* pRecord;

		if (pIterator->getRecord(pRecord, AcDb::kForRead) != Acad::eOk )
		{
			//"\nCouldn't open ViewportTableRecord...."
			continue;
		}

		// if there are more than one viewports in model space we will consider
		// only the active one.
		ACHAR * name;
		pRecord->getName(name);
		if(wcsicmp(name, L"*Active") != 0)
		{
			acdbFree(name);
			continue;
		}
		acdbFree(name);

		HCamera camera;
		GetCameraForInitialView(camera, pRecord);

		int Camera_projection = TKO_Camera_Orthographic;
		if(pRecord->perspectiveEnabled())
			Camera_projection = TKO_Camera_Perspective;
		else
			Camera_projection = TKO_Camera_Orthographic;

		char SceneSegName[MVO_BUFFER_SIZE];
		HC_Show_Segment(m_pInputOptions->m_pHBaseView->GetSceneKey(), SceneSegName);

		TK_Status hdwg_status;

		// Now add a TKE_View opcode which defines this camera.  It 
		// needs to be named "default" in order for HOOPS to honor it 
		TK_Camera * tk_camera = new TK_Camera(TKE_View);
		tk_camera->SetPosition(camera.position.x, camera.position.y, camera.position.z);
		tk_camera->SetTarget(camera.target.x, camera.target.y, camera.target.z);
		tk_camera->SetUpVector(camera.up_vector.x, camera.up_vector.y, camera.up_vector.z);
		tk_camera->SetField(camera.field_width, camera.field_height);
		tk_camera->SetProjection(Camera_projection);
		tk_camera->SetView("default");
		hdwg_status = WriteObject(tk_camera,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete tk_camera;

		SetRenderMode(m_pInputOptions, pRecord);

		m_pInputOptions->m_pHBaseView->HasInitialView(true);

		pRecord->close();
	}

	delete pIterator;
	pViewportTable->close();
}

void HDWG_BStreamImporter::importBlockTableRecord(AcDbBlockTableRecord* pRecord)
{
	//<< this is to handle draw order set on the entities.
	HDrawOrderHandler DrawOrderhandler(pRecord);
	DrawOrderhandler.Open();
	//>>

	AcDbBlockTableRecordIterator *pRecordIter;
	if (pRecord->newIterator(pRecordIter) == Acad::eOk)
	{
		AcDbEntity *pEnt;
		while (!pRecordIter->done())
		{
			if (pRecordIter->getEntity(pEnt, AcDb::kForRead) == Acad::eOk)
			{
				if(!CheckForInvalidExtents(pEnt))
                {
                    pEnt->close();
                    pRecordIter->step();
                    continue;
                }
				if(m_bIgnoreOffEntity)
				{
					// This entire scope of ignoring off entity can be moved inside importAcDbEntity,
					// where we are checking layer visibility to make the containing segment visble\invisble. ASHISH 14/09/2010
					AcDbLayerTableRecord *pLayerTableRecord = 0;
					AcDbObjectId ent_layer_id = pEnt->layerId();
					Acad::ErrorStatus es = acdbOpenObject(pLayerTableRecord, ent_layer_id, AcDb::kForRead);
					bool isEntvisible = true;
					if (pLayerTableRecord)
					{
						get_entity_visibility(pEnt, pLayerTableRecord, isEntvisible);
						pLayerTableRecord->close();
					}
					// if m_bIgnoreOffEntities is true and entity is not effectively visible then 
					//we are not intrested in importing the entity : Mustafa B
					if( isEntvisible == false )
					{
						pEnt->close();
						pRecordIter->step();
						continue;
					}
				}

				TK_Open_Segment* parent_seg_handler = NULL;
				parent_seg_handler = GetBlockTableRecordSegmentForEntity(pEnt);
				importAcDbEntity(pEnt,parent_seg_handler);

				// Draw order settings starts
				// Look for draw order if not asked to ignore them. 
				if(m_bIs2DEntity == true && !m_bDisableDWGDrawOrder)
				{
					DrawOrderhandler.CheckDrawOrderAndSetVisibility(pEnt, parent_seg_handler, this);
				}
				pEnt->close();
				if(parent_seg_handler)
				{
					delete parent_seg_handler;
				}
			}
			pRecordIter->step();
		}                            
		delete pRecordIter;
	}
	DrawOrderhandler.Close();
}


/////////////////////
void HDWG_BStreamImporter::get_entity_material_style(AcDbEntity* pEnt, const AcDbLayerTableRecord *pLayerTableRecord, TK_Open_Segment*& style_seg_handler)
{
	TK_Status hdwg_status; 
	style_seg_handler = NULL;
	bool is_by_block = false;
	AcDbDatabase* pDatabase = acdbHostApplicationServices()->workingDatabase();
	AcDbObjectId mat_id = pEnt->materialId();
	ACHAR* temp_mat_name = pEnt->material();
	wchar_t mat_name[MVO_BUFFER_SIZE];

	// if material is by block, just return
	if( mat_id == pDatabase->byBlockMaterial())
		return;
	else if( mat_id == pDatabase->byLayerMaterial())
	{
		if (pLayerTableRecord)
		{
			mat_id = pLayerTableRecord->materialId();
		}
	}

	if(mat_id.isNull())
		return;

	// I am going to ignore the global material for now
	// It doesn't seem to override the color of solids
	if(mat_id == pDatabase->globalMaterial())
		return;

	wcscpy(mat_name, temp_mat_name);
	condition_string_for_segment_name(mat_name);
	acutDelString(temp_mat_name);

	// I am taking mapper directly from entity as it was observed that
	// earlier method of getting mapper in importAcDbMaterial() shows only kBox type of mapping for all materials.
	// Getting mapping from entity gives correct mappings like kBox, kCylinder etc.
	// Also, adding the mapping ID in seg name, so that it will create separate textures for separate mapping
	// styles. Observed the error while working on 12157. ASHISH.S. 20/04/2010.
	AcGiMapper pMapper;
	pEnt->getMaterialMapper(pMapper);

	AcDbMaterial* p_mat = 0;
	acdbOpenObject(p_mat, mat_id, AcDb::kForRead);

	if(p_mat)
	{
		wchar_t mat_seg_name[MVO_BUFFER_SIZE];
		swprintf(mat_seg_name, MVO_BUFFER_SIZE, L"material_%p_%ls_%d", p_mat, (mat_name), pMapper.projection());

		// get the model segment name. we want to create the pathname for our material library
		char model_seg[MVO_SEGMENT_PATHNAME_BUFFER], mat_lib_seg[MVO_SEGMENT_PATHNAME_BUFFER];
		HC_Show_Segment(m_modelKey, (model_seg));
		sprintf(mat_lib_seg, "%s/%s", model_seg, HDWG_MATERIALS_LIBRARY_SEGMENT);

		STREAM_Open_Segment(mat_lib_seg);
		{

			// set the visibility off. This could have been done once at the start
			// but we create it here only when it is needed.
			//HC_Set_Visibility("off");
			TK_Visibility	*vis_handler = new TK_Visibility();
			vis_handler->SetGeometry(TKO_Geo_All_Visibles);
			vis_handler->SetValue(0);
			hdwg_status = WriteObject(vis_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete vis_handler;

			// get from our records if this material has been previously imported. Import only if it has *not* been.
			void* is_material_imported = 0;
			vhash_lookup_string_key_item(m_vhash_StyleSegName_IsPresentFlag, H_ASCII_TEXT(mat_seg_name), (void**)&is_material_imported);
			if( !is_material_imported )
			{
				style_seg_handler = new TK_Open_Segment;
				style_seg_handler->SetSegment(H_ASCII_TEXT(mat_seg_name));
				hdwg_status = WriteObject(style_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);

				importAcDbMaterial(p_mat, pMapper);

				STREAM_Close_Segment();

				// note down that this material has been imported.
				is_material_imported = (void*)true;
				vhash_insert_string_key_item(m_vhash_StyleSegName_IsPresentFlag, H_ASCII_TEXT(mat_seg_name), is_material_imported);
			}
			else 
			{
				style_seg_handler = new TK_Open_Segment;
				style_seg_handler->SetSegment(H_ASCII_TEXT(mat_seg_name));
			}

		}	
		STREAM_Close_Segment();

		p_mat->close();
	}
}

static float read_float (char const *cp, char const * * newcpp) {
	auto        char const      *cps;
	register    double          result = 0.0;
	auto        bool            negate = false;

	while (*cp == ' ') ++cp;

	if (*cp == '+' || *cp == '-') {
		if (*cp++ == '-')
			negate = true;
	}

	cps = cp;
	while ('0' <= *cp && *cp <= '9')
		result = result * 10.0 + (double)((int)*cp++ - '0');

	if (cp == cps && *cp != '.')    // no leading digits, fail if not '.'
		return 0.0;

	if (*cp == '.') {
		register        double          multiplier = 1.0;

		++cp;
		while ('0' <= *cp && *cp <= '9') {
			multiplier *= 0.1;
			result += multiplier * (double)((int)*cp++ - '0');
		}

		if (cp == cps + 1)          // bare '.'?
			return 0.0;
	}

	if (negate)
		result = -result;

	if (*cp == 'e' || *cp == 'E') {
		register        int             exp = 0;

		++cp;
		negate = false;

		while (*cp == ' ') ++cp;

		if (*cp == '+' || *cp == '-') {
			if (*cp++ == '-')
				negate = true;
		}

		cps = cp;
		while ('0' <= *cp && *cp <= '9')
			exp = exp * 10 + ((int)*cp++ - '0');

		if (cp == cps)              // no exponent digits
			return 0.0;

		if (exp != 0) {
			register    double          mantissa = negate ? 0.1 : 10.0;

			do {
				while ((exp & 1) == 0) {
					mantissa *= mantissa;
					exp >>= 1;
				}
				result *= mantissa;
			} while (--exp > 0);
		}
	}

	if (newcpp != 0)             // if caller wants to know where we left off...
		*newcpp = cp;

	return (float)result;
}


// used by image & size/weight settings
static char const * generic_units[] = {
	"oru", "sru", "wru", "points", "pixels",
	"%", "", "wsu"	    // 
};

static char const * himage_formats[] = {
	"mapped 8", "mapped 16", "rgb", "rgba", "bgra", "depth"
};

static int const TK_Image_Bytes_Per_Pixel[] = {
	1, 2, 3, 4, 4, 4
};

bool fill_image_handler(HC_KEY image_key, TK_Image& image_handler)
{
	auto        char            fmt[128];
	auto        char *          cp;

	unsigned char im_options;
	unsigned char im_format;
	unsigned char im_compression = TKO_Compression_None;
	float im_position[3];
	int   im_size[2];

	HC_Show_Image_Size (image_key, &im_position[0], &im_position[1], &im_position[2],
		fmt, &im_size[0], &im_size[1]);

	image_handler.SetSize(im_size);
	image_handler.SetPosition(im_position);

	float			im_explicit_size[2];
	unsigned char	im_explicit_units[2];
	im_explicit_units[0] = im_explicit_units[1] = TKO_Generic_Size_Pixels;
	if ((cp = strchr (fmt, ',')) != 0) {
		*cp++ = '\0';
		while (cp != 0) {
			auto	char *		start = cp;

			if ((cp = strchr (start, ',')) != 0)
				*cp++ = '\0';

			switch (*start) {
case 'n': {
	start += 5;    // strlen ("name=");
	image_handler.SetName(start);
		  }   break;

case 's': {
	auto    int             ii;

	start += 5;    // strlen ("size=");

	if (*start != '(') {
		im_explicit_size[0] = im_explicit_size[1] = read_float (start, (char const **)&start);
		while (*start == ' ') ++start;
		if ((cp = strchr (start, ',')) != 0)
			*cp++ = '\0';
		for (ii=0; ii<countof(generic_units); ++ii) {
			if (streq (start, generic_units[ii])) {
				im_explicit_units[0] = im_explicit_units[1] = (unsigned char)ii;
				break;
			}
		}
		if (im_explicit_units[0] == TKO_Generic_Size_Unspecified)
			return false;
	}
	else {
		start++;    // '('
		im_explicit_size[0] = read_float (start, (char const **)&start);
		while (*start == ' ') ++start;
		if ((cp = strchr (start, ',')) == 0)
			return false;
		*cp++ = '\0';	// overwrite ','
		for (ii=0; ii<countof(generic_units); ++ii) {
			if (streq (start, generic_units[ii])) {
				im_explicit_units[0] = (unsigned char)ii;
				break;
			}
		}
		if (im_explicit_units[0] == TKO_Generic_Size_Unspecified)
			return false;

		start = cp;
		im_explicit_size[1] = read_float (start, (char const **)&start);
		while (*start == ' ') ++start;
		if ((cp = strchr (start, ')')) == 0)
			return false;
		*cp++ = '\0';	// overwrite ')'
		for (ii=0; ii<countof(generic_units); ++ii) {
			if (streq (start, generic_units[ii])) {
				im_explicit_units[1] = (unsigned char)ii;
				break;
			}
		}
		if (im_explicit_units[0] == TKO_Generic_Size_Unspecified)
			return false;
		start = cp;
	}

	im_options |= TKO_Image_Explicit_Size;
		  }   break;

default: {
	return false;
		 }   
			}
		}
	}

	auto        int             i;
	for (i = 0; i < countof(himage_formats); ++i) {
		if (streq (fmt, himage_formats[i])) {
			im_format = (unsigned char)i;
			break;
		}
	}
	if (i == countof(himage_formats))
		return false;


	im_options |= TKO_Image_Local_Texture;

	// TODO: Compression is causing a crash in stream toolkit, so let's hold it off for a bit - Rajesh B (06-Dec-07)
	im_compression = TKO_Compression_None;
	//	if ((im_format == TKO_Image_RGB || im_format == TKO_Image_RGBA || im_format == TKO_Image_BGRA) &&
	//		im_size[0] > 64 && im_size[1] > 64 /*&& tk.GetJpegQuality() > 0*/)
	//		im_compression = TKO_Compression_JPEG;
	//	else if (im_format == TKO_Image_Mapped)
	//		im_compression = TKO_Compression_RLE;


	// allocate space
	image_handler.SetBytes (im_size[0] * im_size[1] * TK_Image_Bytes_Per_Pixel[(int)im_format]);
	if (!image_handler.GetBytes())
		return false;

	HC_Show_Image (image_key, &im_position[0], &im_position[1], &im_position[2],
		fmt, &im_size[0], &im_size[1], image_handler.GetBytes());

	image_handler.SetNeedsTag (true);
	image_handler.SetFormat(im_format);
	image_handler.SetOptions(im_options);
	image_handler.SetCompression(im_compression);

	return true;
}

void HDWG_BStreamImporter::importAcDbMaterial(AcDbMaterial *pAcDbMaterial, AcGiMapper pMapper)
{
	TK_Status hdwg_status; 
	AcGiMaterialColor color;
	AcGiMaterialMap	  mat_map;
	AcCmEntityColor cm_color;
	Adesk::UInt32 RGBM_byte;
	float r,g,b;
	AcGiMaterialTraits::ChannelFlags channel_flags = pAcDbMaterial->channelFlags();

	pAcDbMaterial->ambient(color);
	cm_color = color.color();
	if( !cm_color.isByBlock())
	{
		// if it is by block, let's not set any color, let the color be it's parents
		RGBM_byte = AcCmEntityColor::lookUpRGB(cm_color.colorIndex());
		r = (float) GetRValueFromRGBM(RGBM_byte)/255.0f;
		g = (float) GetGValueFromRGBM(RGBM_byte)/255.0f;
		b = (float) GetBValueFromRGBM(RGBM_byte)/255.0f;

		TK_Color_RGB  *ambient_color_handler = new TK_Color_RGB();
		ambient_color_handler->SetGeometry(TKO_Geo_Ambient);
		ambient_color_handler->SetRGB(r,g, b);
		hdwg_status = WriteObject(ambient_color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete ambient_color_handler;
	}

	pAcDbMaterial->diffuse(color, mat_map);
	cm_color = color.color();
	if( !cm_color.isByBlock())
	{
		// if it is by block, let's not set any color, let the color be it's parents
		RGBM_byte = AcCmEntityColor::lookUpRGB(cm_color.colorIndex());
		r = (float) GetRValueFromRGBM(RGBM_byte)/255.0f;
		g = (float) GetGValueFromRGBM(RGBM_byte)/255.0f;
		b = (float) GetBValueFromRGBM(RGBM_byte)/255.0f;

		TK_Color_RGB				*rgb_color_handler;
		rgb_color_handler = new TK_Color_RGB();
		rgb_color_handler->SetGeometry (TKO_Geo_Face);
		rgb_color_handler->SetRGB(r, g, b);
		hdwg_status = WriteObject(rgb_color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete rgb_color_handler;

		if( (channel_flags & AcGiMaterialTraits::kUseDiffuse) == AcGiMaterialTraits::kUseDiffuse )
		{
			AcGiMaterialMap::Source src = mat_map.source();
			const AcGiMaterialTexture* pAcGiTexture = mat_map.texture();

			// TODO: support kScene & kProcedural textures
			if( pAcGiTexture && (src == AcGiMaterialMap::kFile)
				&& (pAcGiTexture->isA() == AcGiImageFileTexture::desc()) )
			{
				AcGiImageFileTexture* pAcGiImageFileTexture = (AcGiImageFileTexture*) pAcGiTexture;
				const ACHAR * p_tex_filename = pAcGiImageFileTexture->sourceFileName();
				wchar_t texture_file[MVO_BUFFER_SIZE], file_ext[MVO_BUFFER_SIZE];

				bool if_file_exist = hio_dwg_check_file_exist(p_tex_filename); // For issue 12157. p_tex_filename has full direcory path.

				if(m_pDWGTextureDirectory && if_file_exist == false)
					swprintf(texture_file, MVO_BUFFER_SIZE, L"%ls\\%ls", m_pDWGTextureDirectory, (p_tex_filename));
				else
					swprintf(texture_file, MVO_BUFFER_SIZE, L"%ls", (p_tex_filename));

				HUtility::FindFileNameExtension(texture_file, file_ext);

				// convert this file to a texture
				wchar_t imageName[MVO_BUFFER_SIZE];
				swprintf(imageName, MVO_BUFFER_SIZE, L"%ls_%p", (p_tex_filename), pAcGiImageFileTexture);
				char imageFormat[MVO_BUFFER_SIZE];
				strcpy(imageFormat, "rgba");

				HInputHandler *reader = HDB::GetHIOManager()->GetInputHandler(file_ext);
				if(reader)
				{
					// create the image in the model segment for the time being. We will delete it anyway.
					HC_KEY image_key;
					HInputHandlerOptions options;
					char * ascii_image_name = strdup(H_ASCII_TEXT(imageName));
					options.m_pImageName = ascii_image_name;
					options.m_pImageFormat = imageFormat;
					HFileInputResult result = InputFail;

					result = reader->FileInputToImageKey((texture_file), &image_key, m_modelKey, &options );
					//free(ascii_image_name);

					if(result == InputOK)
					{
						// query the image details from HOOPS
						TK_Image* image_handler = new TK_Image();
						fill_image_handler(image_key, *image_handler);
						hdwg_status = WriteObject(image_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
						H_ASSERT(hdwg_status == TK_Normal);
						delete image_handler;

						//AcGiMapper mapper = mat_map.mapper();
						AcGiMapper::Projection map_mode = pMapper.projection();
						char param_source[MVO_BUFFER_SIZE];
						char texture_def[MVO_BUFFER_SIZE];
						char color_opts[MVO_BUFFER_SIZE];

						TK_Texture					*texture_handler;
						texture_handler = new TK_Texture;
						texture_handler->SetFlags(0);
						texture_handler->SetName(H_ASCII_TEXT(imageName));
						texture_handler->SetImage(H_ASCII_TEXT(imageName));

						texture_handler->SetFlags( texture_handler->GetFlags() | TKO_Texture_Param_Source );
						if( map_mode == AcGiMapper::kPlanar || map_mode == AcGiMapper::kBox)
						{
							strcpy(param_source, "natural");
							texture_handler->SetParameterSource(TKO_Texture_Param_Source_Natural_UV);
						}
						/*else if( map_mode == AcGiMapper::kBox)
						{
						strcpy(param_source, "surface normal");
						texture_handler->SetParameterSource(TKO_Texture_Param_Source_Surface_Normal);
						}*/
						else if( map_mode == AcGiMapper::kCylinder)
						{
							strcpy(param_source, "cylinder");
							texture_handler->SetParameterSource(TKO_Texture_Param_Source_Cylinder_Map);
						}
						else if( map_mode == AcGiMapper::kSphere)
						{
							strcpy(param_source, "sphere");
							texture_handler->SetParameterSource(TKO_Texture_Param_Source_Sphere_Map);
						}
						else
						{
							strcpy(param_source, "uv");
							texture_handler->SetParameterSource(TKO_Texture_Param_Source_UV);
						}

						sprintf(texture_def,"source = %s, parameterization source = %s",
							imageName, param_source);
						// TODO: add more texture definition parameters

						//HC_Define_Local_texture(imageName, texture_def); 
						hdwg_status = WriteObject(texture_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
						H_ASSERT(hdwg_status == TK_Normal);
						delete texture_handler;

						sprintf (color_opts, "faces = %s", imageName);
						//HC_Set_Color(color_opts);

						TK_Color *color_handler;
						color_handler = new TK_Color;
						color_handler->SetGeometry( TKO_Geo_Face );
						color_handler->SetChannels( 1 << TKO_Channel_Diffuse ); //xxx
						color_handler->SetDiffuseName( H_ASCII_TEXT(imageName)  );
						hdwg_status = WriteObject(color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
						H_ASSERT(hdwg_status == TK_Normal);
						delete color_handler;

						// we don't need the image, we have serialized it now
						HC_Delete_By_Key(image_key);
					}
					else
					{
						wchar_t error_msg[MVO_BUFFER_SIZE];
						swprintf(error_msg, MVO_BUFFER_SIZE, L"Failed to load texture image file - %ls.\n"
							L"You may need to set the location of the DWG textures\n"
							L"via the File page of the options dialog.", 
							(p_tex_filename));
						m_pDWGInputHandler->ReportInputInformation(error_msg);
					}
				}
				else
				{
					wchar_t error_msg[MVO_BUFFER_SIZE];
					swprintf(error_msg, MVO_BUFFER_SIZE, L"Failed to load texture image file - %ls.\n"
						L"Could not find any input handler which supports reading of %ls files.", 
						(p_tex_filename), file_ext);
					m_pDWGInputHandler->ReportInputInformation(error_msg);
				}

			}
		}
	}

	// TODO: The specular color seems to be returned as black when it shouldn't have.
	// this needs to be investigated.
	//double dwg_gloss;
	//pAcDbMaterial->specular(color, mat_map, dwg_gloss);
	//cm_color = color.color();
	//if( !cm_color.isByBlock())
	//{
	//	// if it is by block, let's not set any color, let the color be it's parents
	//	RGBM_byte = AcCmEntityColor::lookUpRGB(cm_color.colorIndex());
	//	r = (float) GetRValueFromRGBM(RGBM_byte)/255.0f;
	//	g = (float) GetGValueFromRGBM(RGBM_byte)/255.0f;
	//	b = (float) GetBValueFromRGBM(RGBM_byte)/255.0f;
	//	sprintf(h_color_def, "faces = specular = (R = %f G = %f B = %f)", r, g, b);
	//	HC_Set_Color(h_color_def);

	//	// TODO: texture, gloss
	//}

}
void HDWG_BStreamImporter::importLBGEData()
{
	AcDbDatabase* pDatabase = acdbHostApplicationServices()->workingDatabase();


	TK_Close_Segment *close_seg_handler = NULL;
	TK_Open_Segment	*open_seg_handler = NULL;
	TK_Unicode_Options	*user_options_handler = NULL;
	TK_Status hdwg_status;

	//HC_Open_Segment("DWG_ENTITY_NAMES");
	open_seg_handler= new TK_Open_Segment;
	open_seg_handler->SetSegment("DWG_ENTITY_NAMES");
	hdwg_status = WriteObject(open_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete open_seg_handler;

	//////////////AcDbEntities////////////
	//HC_Open_Segment("ENTITY_tYPES");
	open_seg_handler= new TK_Open_Segment;
	open_seg_handler->SetSegment("ENTITY_tYPES");
	hdwg_status = WriteObject(open_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete open_seg_handler;

	for (int i = 0; i < 58; i++) 
	{
		size_t len = wcslen((EntityList[i].pName));
		wchar_t *ent_name = h_dwg_wcsdup(EntityList[i].pName);

		wchar_t *ent_name1 = h_dwg_wcsdup(ent_name+4);

		size_t buff_size = sizeof(wchar_t) * (len+10);
		wchar_t *ent_option = (wchar_t*)malloc(buff_size);//maximum 999 number of entities
		swprintf(ent_option, buff_size, L"%i=%ls", i, ent_name1);

		condition_string_for_user_options(ent_option);
		//HC_Set_User_Options(ent_option);
		user_options_handler= new TK_Unicode_Options;
		user_options_handler->SetOptions((unsigned short const*)H_UTF16(ent_option).encodedText());
		hdwg_status = WriteObject(user_options_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete user_options_handler;

		entity_record.insert(std::map<int, wchar_t*>::value_type(i, ent_name1));
		free(ent_option);
		free(ent_name);
	}
	//HC_Close_Segment();//ENTITY_tYPES
	close_seg_handler = new TK_Close_Segment;
	hdwg_status = WriteObject(close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete close_seg_handler;
	//////////////AcDbEntities////////////

	/////// AcDbBlockTable////////////
	//HC_Open_Segment("BLOCK_tABLE");
	open_seg_handler= new TK_Open_Segment;
	open_seg_handler->SetSegment("BLOCK_tABLE");
	hdwg_status = WriteObject(open_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete open_seg_handler;

	AcDbBlockTable* pBlockTable;
	if(pDatabase->getBlockTable(pBlockTable, AcDb::kForRead) == Acad::eOk)
	{
		AcDbBlockTableIterator *pTIter=0;
		AcDbBlockTableRecord *pTRecord=0;
		pBlockTable->newIterator(pTIter);
		int blk_counter = 0;
		for(pTIter->start(); !pTIter->done(); pTIter->step())
		{
			if (pTIter->getRecord(pTRecord, AcDb::kForRead) == Acad::eOk)
			{
				wchar_t *pName1;
				if (pTRecord->getName(pName1) == Acad::eOk)
				{
					if(wcsicmp(pName1, L"*"))
					{
						wchar_t blk_def_name[MVO_BUFFER_SIZE];
						swprintf(blk_def_name, MVO_BUFFER_SIZE, L"%i=%ls", blk_counter, (pName1));
						condition_string_for_user_options(blk_def_name);
						//HC_Set_User_Options(blk_def_name);
						user_options_handler= new TK_Unicode_Options;
						user_options_handler->SetOptions((unsigned short const*)H_UTF16(blk_def_name).encodedText());
						hdwg_status = WriteObject(user_options_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
						H_ASSERT(hdwg_status == TK_Normal);
						delete user_options_handler;

						size_t blk_len = wcslen((pName1));
						wchar_t* blk_name = h_dwg_wcsdup(pName1);
						block_ref_record.insert(std::map<int, wchar_t*>::value_type(blk_counter, blk_name));
						blk_counter++;
					}
					acdbFree(pName1);
				}
			}
			pTRecord->close();
		}
		delete pTIter;
	}
	pBlockTable->close();

	//HC_Close_Segment();//BLOCK_tABLE
	close_seg_handler = new TK_Close_Segment;
	hdwg_status = WriteObject(close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete close_seg_handler;
	/////////AcDbBlockTable////////////

	//HC_Close_Segment();//DWG_ENTITY_NAMES
	close_seg_handler = new TK_Close_Segment;
	hdwg_status = WriteObject(close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete close_seg_handler;


	/////////AcDbLayers///////////////////
	//HC_Open_Segment("LAYER_NAMES");
	open_seg_handler= new TK_Open_Segment;
	open_seg_handler->SetSegment("LAYER_NAMES");
	hdwg_status = WriteObject(open_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete open_seg_handler;

	AcDbLayerTable *pLayerTable;
	AcDbLayerTableIterator *pLayTblIter;
	AcDbLayerTableRecord *pLayTblRecord;
	int lay_counter = 0;

	Acad::ErrorStatus err5 = pDatabase->getLayerTable(pLayerTable, AcDb::kForRead);
	pLayerTable->newIterator(pLayTblIter);

	while (!pLayTblIter->done())
	{
		if (pLayTblIter->getRecord(pLayTblRecord, AcDb::kForRead) == Acad::eOk)
		{
			wchar_t *pName;
			if (pLayTblRecord->getName(pName) == Acad::eOk)
			{
				wchar_t *lay_name; 
				lay_name = h_dwg_wcsdup(pName);
				layer_record.insert(std::map<int, wchar_t*>::value_type(lay_counter, lay_name));

				condition_string_for_user_options(lay_name);
				size_t buff_size = sizeof(wchar_t) * (wcslen(lay_name) +12);
				wchar_t *lay_option = (wchar_t*)malloc(buff_size);//maximum 9999 number of layers
				swprintf(lay_option, buff_size, L"%i=%ls", lay_counter, lay_name);

				//HC_Set_User_Options(lay_option);
				user_options_handler= new TK_Unicode_Options;
				user_options_handler->SetOptions((unsigned short const*)H_UTF16(lay_option).encodedText());
				hdwg_status = WriteObject(user_options_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
				H_ASSERT(hdwg_status == TK_Normal);
				delete user_options_handler;

				lay_counter++;
				acdbFree(pName);
				free(lay_option);
			}
			pLayTblRecord->close();
		}
		pLayTblIter->step();
	}
	delete pLayTblIter;
	pLayerTable->close();
	//HC_Close_Segment();//LAYER_NAMES
	close_seg_handler = new TK_Close_Segment;
	hdwg_status = WriteObject(close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete close_seg_handler;
	/////////AcDbLayers///////////////////

	////////Group Names//////////////////////
	AcDbDictionary* pGroupDict;
	Acad::ErrorStatus err = pDatabase->getGroupDictionary(pGroupDict, AcDb::kForRead);
	if( err == Acad::eOk )
	{
		//HC_Open_Segment("GROUP_NAMES");
		open_seg_handler= new TK_Open_Segment;
		open_seg_handler->SetSegment("GROUP_NAMES");
		hdwg_status = WriteObject(open_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete open_seg_handler;

		AcDbDictionaryIterator *pDictIter; 
		AcDbObject *pObj;
		pDictIter = pGroupDict->newIterator();
		int grp_counter = 0;
		while(!pDictIter->done())
		{
			if (pDictIter->getObject(pObj, AcDb::kForRead) == Acad::eOk)
			{
				ACHAR * grpName;
				AcDbGroup* grp;
				grp = AcDbGroup::cast(pObj);
				Acad::ErrorStatus  err = grp->getName(grpName);
				wchar_t *grp_name; 
				grp_name = h_dwg_wcsdup(grpName);
				group_record.insert(std::map<int, wchar_t*>::value_type(grp_counter, grp_name));

				size_t buff_size = sizeof(wchar_t) * (wcslen(grp_name) +10);
				wchar_t *grp_option = (wchar_t*)malloc(buff_size);//maximum 9999 number of groups
				swprintf(grp_option, buff_size, L"%i=%ls", grp_counter, grp_name);
				condition_string_for_user_options(grp_option);
				//HC_Set_User_Options(grp_option);
				user_options_handler= new TK_Unicode_Options;
				user_options_handler->SetOptions((unsigned short const*)H_UTF16(grp_option).encodedText());
				hdwg_status = WriteObject(user_options_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
				H_ASSERT(hdwg_status == TK_Normal);
				delete user_options_handler;

				grp_counter++;
				pObj->close();
				free(grp_option);
				acdbFree(grpName);
			}
			pDictIter->next();
		}
		delete pDictIter;
		//HC_Close_Segment();//GROUP_NAMES
		close_seg_handler = new TK_Close_Segment;
		hdwg_status = WriteObject(close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete close_seg_handler;
	}
	pGroupDict->close();
	//////////Group Names////////////////////
}


void HDWG_BStreamImporter::importAcDbEntity(AcDbEntity *pEnt, TK_Open_Segment *open_seg_handler, bool for_blk_ref)
{

	m_bAmIsolidHatch = false;
	const wchar_t *p = pEnt->isA()->name();
	int i = -1;

	bool draw_shaded = true;

	// if a list of entity types is provided to us, then import only those types.
	if(m_listEntityType)
	{
		bool import_entity = false;
		wchar_t * entity_name = 0;

		vlist_reset_cursor(m_listEntityType);
		while((entity_name = (wchar_t*) vlist_peek_cursor(m_listEntityType))) 
		{
			if (wcscmp(p, (entity_name)) == 0)
			{
				import_entity = true;
				break;
			}
			vlist_advance_cursor(m_listEntityType);
		}

		if(!import_entity)
			return;
	}	

	for (i = 0; i < nEntNames; i++)
	{
		if (wcscmp(p, EntityList[i].pName) == 0)
			break;
	}	

	if (i == 0 )
	{ 
		importAcDbBlockReference((AcDbBlockReference*)pEnt, open_seg_handler);
		return;
	}
	if (i == 1)
	{ 
		importAcDbMInsertBlock((AcDbMInsertBlock*)pEnt,open_seg_handler);
		return;
	}
	else if( i >= 2 && i <= 12 )
	{
		// We have a solid (like thing), this is a 3D DWG then. I feel that there should 
		// be a better way than this to determine if the file is a 3D DWG - Rajesh B (18-Dec-07)
		m_bIs3D = true;
		m_bIs2DEntity = false;

		draw_shaded = true;
		if( m_bImportWireframeForBrep )
			m_bDrawWireframe = true;
		else
			m_bDrawWireframe = false;

		switch(i)
		{
		case 3://3D Solid
			{
				AcDb3dSolid* p3dSolid = (AcDb3dSolid*)pEnt;

				if(p3dSolid)
				{
					double solid_area;
					p3dSolid->getArea(solid_area);
					// Though not confirmed from ADN until now if the area is NAN then concerned 3dSolid is invalid
					// but I assume that it is logical to not import these as these does not have any geometrical representation
					//Also this avoids the crash in files where such entities are present . Mustafa Bohari, 20-AUG-09
					if(_isnan(solid_area))
					{
						return;
					}

				}
				m_nSolid3D_count++;
			}
			break;

		case 4://Body
		case 8://Solid
			m_nSolid_count++;
			break;
		case 5://face
		case 7://Shape
		case 9://face
		case 10://PloyFaceMesh
		case 11://PolygonMesh
		case 12://ExtrudeSurface.
			m_nShell_count++;
			break;
		}
	}
	else if( i >= 13 && i <= 56 )
	{
		m_bIs2DEntity = true;
		draw_shaded = false;
		m_bDrawWireframe = true;

		switch(i)
		{
		case 22://Line
		case 26://XLine
			m_nLine_count++;
			break;

		case 18://Arc
			m_nArc_count++;
			break;

		case 19://Circle
			m_nCircle_count++;
			break;

		case 23://PolyLine
		case 16://2D PolyLine
		case 17://3D PolyLine
			m_nPloyLine_count++;
			break;

		case 27://Vertex
		case 28://2D vertex
		case 29://3D polyLine Vertex
		case 31://Point
		case 32://PolyFaceMeshVertex
		case 33://PolygonMeshVertex
			m_nPoint_count++;
			break;

		case 13://MText
		case 14://Text
			m_nText_count++;
			break;

		}
	}
	else if( i >= 13 && i <= 57)
	{
		m_bIs2DEntity = true;

		draw_shaded = false;
		m_bDrawWireframe = true;
	}
	else if(i == 57 || i == 60 )
	{
		m_bIs2DEntity = false;
		draw_shaded = true;
		m_bDrawWireframe = true;

	}
	else if( i == 59 )
	{
		// things we don't want to import
		return;
	}
	else if(i > 60)
	{
		m_bIs2DEntity = false;
		draw_shaded = false;
		m_bDrawWireframe = true;
	}

	double deviation_backup = 0.0;
	if( i == 13 )//Default Deviation for AcDbHatch
	{
		if(((AcDbHatch*)pEnt)->isSolidFill() == Adesk::kTrue)
		{
			m_bAmIsolidHatch = true;
			draw_shaded = true;
		}
		deviation_backup = HDWGImporter::get_deviation();
		HDWGImporter::set_deviation(0.1);
	}

	importAcDbEntity(pEnt, draw_shaded, open_seg_handler, for_blk_ref);
	if( i == 13 )//Reset back Deviation
	{
		HDWGImporter::set_deviation(deviation_backup);
	}
}

void HDWG_BStreamImporter::attachDWGHandle(AcDbEntity *pEnt)
{
	TK_Unicode_Options	*user_options_handler = NULL;
	TK_Status hdwg_status;

	///// AcDbEntity Handle for Persistency //////
	AcDbObjectId id = pEnt->objectId();
	if(!id.isNull())
	{
		AcDbHandle handle = id.handle();
		if(!handle.isNull())
		{
			wchar_t my_buf[MVO_BUFFER_SIZE];
			int int_handle = handle;
			swprintf(my_buf, MVO_BUFFER_SIZE, L"Handle=%X", int_handle);
			user_options_handler= new TK_Unicode_Options;
			user_options_handler->SetOptions((unsigned short const*)H_UTF16(my_buf).encodedText());
			hdwg_status = WriteObject(user_options_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete user_options_handler;
		}
	}
	///// AcDbEntity Handle for Persistency ENDS //////
}

void HDWG_BStreamImporter::importXdata(AcDbEntity *pEnt)
{
	resbuf *pBuf;
	if(m_listRegAppNames)
	{
		wchar_t * reg_appname;
		vlist_reset_cursor(m_listRegAppNames);

		while((reg_appname = (wchar_t*) vlist_peek_cursor(m_listRegAppNames))) 
		{
			pBuf = pEnt->xData((reg_appname));
			importXdata(pBuf);
			vlist_advance_cursor(m_listRegAppNames);
		}
	}
	else
	{
		pBuf = pEnt->xData(NULL);
		importXdata(pBuf);
	}



	//////////////////////////////////////////////

	TK_Unicode_Options	*user_options_handler = NULL;
	TK_Status hdwg_status;

	/////////// Entity Info for Model Browser
	if(!pEnt)
		return;
	//Layer
	ACHAR * lay_name = pEnt->layer();
	size_t size = wcslen((lay_name));
	wchar_t *layer_name = h_dwg_wcsdup(lay_name);
	condition_string_for_user_options(layer_name);
	std::map<int, wchar_t*>::iterator layer_iterator;
	for(layer_iterator = layer_record.begin(); layer_iterator != layer_record.end(); layer_iterator++)
	{
		wchar_t * aa = layer_iterator->second;
		if( wcsicmp(aa, layer_name) == 0)
		{
			wchar_t layer_user_opt[20];
			swprintf(layer_user_opt, 20, L"%s=%i", "1",layer_iterator->first);//1 For layer
			//HC_Set_User_Options(layer_user_opt);
			user_options_handler= new TK_Unicode_Options;
			user_options_handler->SetOptions((unsigned short const*)H_UTF16(layer_user_opt).encodedText());
			hdwg_status = WriteObject(user_options_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete user_options_handler;

			break;
		}
	}
	free(layer_name);
	acdbFree(lay_name);

	//EntityName
	const ACHAR *ent_type = pEnt->isA()->name();
	size_t ent_size = wcslen((ent_type));
	wchar_t *entity_name = h_dwg_wcsdup(ent_type);
	condition_string_for_user_options(entity_name);
	std::map<int, wchar_t*>::iterator entity_iterator;
	for(entity_iterator = entity_record.begin(); entity_iterator != entity_record.end(); entity_iterator++)
	{
		wchar_t * aa = entity_iterator->second;
		if( wcsicmp(aa, entity_name+4) == 0)
		{
			wchar_t entity_user_opt[9];
			swprintf(entity_user_opt, 9, L"%s=%i", "3", entity_iterator->first);//3 For Entity name
			//HC_Set_User_Options(entity_user_opt);
			user_options_handler= new TK_Unicode_Options;
			user_options_handler->SetOptions((unsigned short const*)H_UTF16(entity_user_opt).encodedText());
			hdwg_status = WriteObject(user_options_handler,  m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete user_options_handler;

			break;
		}
	}
	free(entity_name);
	//acdbFree(ent_type);

	//GroupNames
	// ALL OBJECTS IN A GROUP HAVE PERSISTANCE REACTORS
	AcDbVoidPtrArray *pReactors  = NULL;
	pReactors = pEnt->reactors();
	if( pReactors != NULL && pReactors->length() > 0)
	{
		for( int i=0; i<pReactors->length(); i++)
		{
			void* pSomething = NULL;
			pSomething = pReactors->at(i);

			// CHECK IF THIS IS PERSISTANT REACTOR
			if (acdbIsPersistentReactor(pSomething) == Adesk::kTrue )
			{
				AcDbObjectId persObjId;
				persObjId = acdbPersistentReactorObjectId(pSomething);

				AcDbObject* pPersReacObj = NULL;
				if ( acdbOpenObject(pPersReacObj, persObjId, AcDb::kForRead) == Acad::eOk )
				{
					AcDbGroup* pGroupObj = AcDbGroup::cast(pPersReacObj);
					if (pGroupObj != NULL)
					{
						if ( pGroupObj->has(pEnt) == Adesk::kTrue)
						{
							ACHAR* grpName;
							Acad::ErrorStatus  err = pGroupObj->getName(grpName);
							size_t grp_size = wcslen((grpName));
							wchar_t *grp_name = h_dwg_wcsdup(grpName);
							condition_string_for_user_options(grp_name);

							std::map<int, wchar_t*>::iterator group_iterator;
							for(group_iterator = group_record.begin(); group_iterator != group_record.end(); group_iterator++)
							{
								wchar_t* aa = group_iterator->second;
								if( wcsicmp(aa, grp_name) == 0)
								{
									wchar_t grp_user_opt[9];
									swprintf(grp_user_opt, 9, L"%s=%i", "2",group_iterator->first);//2 For Group Name
									//HC_Set_User_Options(grp_user_opt);
									user_options_handler= new TK_Unicode_Options;
									user_options_handler->SetOptions((unsigned short const*)H_UTF16(grp_user_opt).encodedText());
									hdwg_status = WriteObject(user_options_handler,  m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
									H_ASSERT(hdwg_status == TK_Normal);
									delete user_options_handler;

									break;
								}
							}
							free(grp_name);
							acdbFree(grpName);
						}
					}
					pPersReacObj->close();
				}
			}
		}
	}//End of GROUP


	///// Block Reference Index
	if(m_BlockRefIndex >= 0)
	{
		char blk_user_opt[9];
		sprintf(blk_user_opt, "%s=%i", "4",m_BlockRefIndex);//4 For BlockRef Names
		//HC_Set_User_Options(blk_user_opt);
		user_options_handler= new TK_Unicode_Options;
		user_options_handler->SetOptions((unsigned short const*)H_UTF16(blk_user_opt).encodedText());
		hdwg_status = WriteObject(user_options_handler,  m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete user_options_handler;

	}
	///////////// End of BlockRef
	//////////////////////////////////

}

void HDWG_BStreamImporter::importXdata(resbuf *pBuf)
{
	TK_Unicode_Options    user_options_handler;
	TK_Status hdwg_status = TK_Normal;
	wchar_t x_data_lhs[MVO_BUFFER_SIZE];
	wchar_t x_data_rhs[MVO_BUFFER_SIZE];

	if (pBuf)
	{
		VHash<short, unsigned int> xdata_type_vs_count;

		resbuf *p = pBuf;
		while (p) 
		{
			x_data_lhs[0] = L'\0';
			x_data_rhs[0] = L'\0';

			// construct the lhs
			unsigned int type_count = 0, dummy;
			vhash_status_t v_stat = xdata_type_vs_count.LookupItem(p->restype, &type_count);
			type_count++;
			xdata_type_vs_count.ReplaceItem(p->restype, type_count, &dummy);
			swprintf(x_data_lhs, MVO_BUFFER_SIZE, L"%hd_%u=", p->restype, type_count);

			switch (p->restype)
			{
				// type - real
			case AcDb::kDxfXdReal:
			case AcDb::kDxfXdDist:
			case AcDb::kDxfXdScale:
				{
					swprintf(x_data_rhs, MVO_BUFFER_SIZE, L"%g", p->resval.rreal);
				}
				break;

				// type - rpoint[3]
			case AcDb::kDxfXdXCoord:
			case AcDb::kDxfXdWorldXCoord:
			case AcDb::kDxfXdWorldXDisp:
			case AcDb::kDxfXdWorldXDir:
				{
					swprintf(x_data_rhs, MVO_BUFFER_SIZE, L"(%g,%g,%g)", p->resval.rpoint[0],
						p->resval.rpoint[1],
						p->resval.rpoint[2]);
				}
				break;

				// type - rint
			case AcDb::kDxfXdInteger16:
				{
					swprintf(x_data_rhs, MVO_BUFFER_SIZE, L"%d", p->resval.rint);
				}
				break;

				// type - ACHAR *
			case AcDb::kDxfXdAsciiString:
			case AcDb::kDxfRegAppName:
			case AcDb::kDxfXdControlString:
			case AcDb::kDxfXdLayerName:
				{
					swprintf(x_data_rhs, MVO_BUFFER_SIZE, L"%ls", (p->resval.rstring));
				}
				break;

				// type - long rlname[2]
			case AcDb::kDxfXdHandle:
				{
					swprintf(x_data_rhs, MVO_BUFFER_SIZE, L"%x %x %ls", p->resval.rlname[0], 
						p->resval.rlname[1],(p->resval.rstring));
				}
				break;


				// type - long rlong
			case AcDb::kDxfXdInteger32:
				{
					swprintf(x_data_rhs, MVO_BUFFER_SIZE, L"%ld", p->resval.rlong);
				}
				break;

			default:
				{
					if(p->restype)
						swprintf(x_data_rhs, MVO_BUFFER_SIZE, L"?");
				}
				break;
			}
			//case AcDb::kDxfXdSoftRefHandle:
			//case AcDb::kDxfXdHardRefHandle:
			//case AcDb::kDxfXdSoftOwnHandle:
			//case AcDb::kDxfXdHardOwnHandle:
			//    break;
			//
			//case AcDb::kDxfXdBinaryChunk:
			//{
			//HC_Set_User_Options("BinaryChunk: ");

			////_print(L"\t\t\tBinaryChunk:"));
			//{
			//    int i;
			//    for (i = 0; i < p->resval.rbinary.clen; i++)
			//    {
			//        if (i % 16 == 0)
			//            //_print(L"\n\t\t\t    "));
			//        char x_data[MVO_BUFFER_SIZE];
			//        sprintf(x_data, "%02x ", (BYTE)p->resval.rbinary.buf[i]);
			//        HC_Set_User_Options(x_data);

			//        //_print(L"%02x "), (BYTE)p->resval.rbinary.buf[i]);
			//    }
			//    //_print(L"\n"));
			//}
			//}
			//break;

			if( !wcseq(x_data_rhs, L""))
			{
				condition_string_for_user_options(x_data_rhs);
				wcscat(x_data_lhs, x_data_rhs);

				user_options_handler.Reset();
				user_options_handler.SetOptions((unsigned short const*)H_UTF16(x_data_lhs).encodedText());
				hdwg_status = WriteObject(&user_options_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
				H_ASSERT(hdwg_status == TK_Normal);
			}
			p = p->rbnext;
		}
		acutRelRb(pBuf);
	}
}

#ifndef HDWG_NO_HYPERLINKS_IMPORT
// Import the hyperlinks for a particular entity. Hyperlinks are attached to an entity and are not a separate entity.
// Our strtergy is to get these hyperlinks and store it as user options for that segment.
void HDWG_BStreamImporter::import_hyperlinks(AcDbEntity *pEnt)
{

	AcDbObjectId pEntId;

	TK_Status hdwg_status;

	// Get Object id.
	//acdbGetObjectId(pEntId, pEnt);
	pEntId = pEnt->objectId();

	if(!pEntId.isValid())
		return;

	// Open object for write.
	acdbOpenObject(pEnt, pEntId, AcDb::kForRead);

	if(!pEnt)
		return;

	// The hyperlink collection object is created inside
	// of getHyperlinkCollection below. 
	// It is our responsibility to delete it.
	AcDbHyperlinkCollection * pcHCL = NULL;

	// Get the hyperlink collection associated with the entity.
	ACRX_PE_PTR(pEnt, AcDbEntityHyperlinkPE)->getHyperlinkCollection(pEnt, pcHCL, false, true);

	// If a hyperlink exists already, say so.
	if (pcHCL->count() != 0)
	{
		AcDbHyperlink * pcHO;

		// Iterate through collection and print existing hyperlinks.
		wchar_t hyperlink_data[MVO_BUFFER_SIZE];
		int i = 0;
		for (i = 0; i < pcHCL->count(); i++)
		{
			// Get point to current hyperlink object.
			pcHO = pcHCL->item(i); 
			TK_Unicode_Options	*user_options_handler;

			//acutPrintf("Hyperlink name: %s", pcHO->name());
			swprintf(hyperlink_data, MVO_BUFFER_SIZE, L"Hyperlink name: %ls", (pcHO->name()));
			//HC_Set_User_Options(hyperlink_data);

			user_options_handler= new TK_Unicode_Options;
			user_options_handler->SetOptions((unsigned short const*)H_UTF16(hyperlink_data).encodedText());
			hdwg_status = WriteObject(user_options_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete user_options_handler;

			//acutPrintf("\nHyperlink location: %s", pcHO->subLocation());
			swprintf(hyperlink_data, MVO_BUFFER_SIZE, L"Hyperlink location: %ls", (pcHO->subLocation()));
			//HC_Set_User_Options(hyperlink_data);

			user_options_handler= new TK_Unicode_Options;
			user_options_handler->SetOptions((unsigned short const*)H_UTF16(hyperlink_data).encodedText());
			hdwg_status = WriteObject(user_options_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete user_options_handler;


			//acutPrintf("\nHyperlink description: %s", pcHO->description());
			swprintf(hyperlink_data, MVO_BUFFER_SIZE, L"Hyperlink description: %ls", (pcHO->description()));
			//HC_Set_User_Options(hyperlink_data);

			user_options_handler= new TK_Unicode_Options;
			user_options_handler->SetOptions((unsigned short const*)H_UTF16(hyperlink_data).encodedText());
			hdwg_status = WriteObject(user_options_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete user_options_handler;
		}
	}

	// Delete the collection. The collection will delete all its
	// contained hyperlink objects.
	delete pcHCL;

	// Close the object.
	pEnt->close();

}
#endif// HDWG_NO_HYPERLINKS_IMPORT

void HDWG_BStreamImporter::importAcDbEntity(AcDbEntity *pEnt, const bool& draw_shaded, 
											TK_Open_Segment *parent_seg, bool for_blk_ref)
{
	if(pEnt->isA() == AcDb3dSolid::desc())
	{
		AcDb3dSolid* sol = (AcDb3dSolid*)pEnt;

		if(sol)
		{
			Adesk::Boolean isnull = sol->isNull();
			if(isnull == Adesk::kTrue)
				return;
		}
	}

	TK_Status hdwg_status; 
	if( !draw_shaded && !m_bDrawWireframe)
		// what to draw?
		return;

	float r, g, b;
	int alpha;
	bool is_color_by_block;
	bool is_alpha_by_block;
	bool is_visible;
	TK_Open_Segment	*style_seg_handler = NULL;

	// OPTIMIZATION TIP:
	// We could potentially merge these three functions below into one and save
	// time by not requiring open and close layer table and it's records again and again

	// Using above old tip, Get Layer table record and pass it to all those methods
	// who need it. Closed after checking all properties. It should save opening closing time of the
	// record. ASHISH.S. 20/04/2010.
	AcDbLayerTableRecord *pLayerTableRecord = 0;
	AcDbObjectId ent_layer_id = pEnt->layerId();
	Acad::ErrorStatus es = acdbOpenObject(pLayerTableRecord, ent_layer_id, AcDb::kForRead);

	bool set_color = get_entity_rgb(pEnt, pLayerTableRecord, r, g, b, is_color_by_block, for_blk_ref);
	get_entity_transparency(pEnt, pLayerTableRecord, alpha, is_alpha_by_block);
	get_entity_visibility(pEnt, pLayerTableRecord, is_visible);
	get_entity_material_style(pEnt, pLayerTableRecord, style_seg_handler);

	AcDbObjectId line_type_id = pEnt->linetypeId();

	TK_Open_Segment* parent_clone = new TK_Open_Segment;
	if(parent_seg == NULL)
	{
		// we are organizing entities under their block table record. 
		// Fetch the block table record segment for this entity
		//HC_KEY blck_table_rec_seg_key = GetBlockTableRecordSegmentForEntity(pEnt);
		//HC_Open_Segment_By_Key(blck_table_rec_seg_key);
		TK_Open_Segment	*blck_table_rec_seg = GetBlockTableRecordSegmentForEntity(pEnt) ; 
		parent_clone->SetSegment(blck_table_rec_seg->GetSegment());
		delete blck_table_rec_seg;
	}
	else
	{
		//HC_Open_Segment_By_Key(parent_seg);
		//TK_Open_Segment	parent_clone;
		parent_clone->SetSegment(parent_seg->GetSegment());
	}

	hdwg_status = WriteObject(parent_clone,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete parent_clone;

	// Open a new segment for this entity. 
	// Though this is not optimal, we are going to optimize the tree in the end.
	char entity_segment_name[MVO_BUFFER_SIZE];
	sprintf(entity_segment_name, "entity_%p", pEnt);

	//HC_Open_Segment(entity_segment_name);
	STREAM_Open_Segment(entity_segment_name);

	if(style_seg_handler != NULL)
	{
		// get the model segment name. we want to create the pathname for our material library
		char model_seg[MVO_SEGMENT_PATHNAME_BUFFER], style_segment_name[MVO_SEGMENT_PATHNAME_BUFFER];
		HC_Show_Segment(m_modelKey, model_seg);

		sprintf(style_segment_name, "%s/%s/%s", model_seg, HDWG_MATERIALS_LIBRARY_SEGMENT, style_seg_handler->GetSegment());
		TK_Referenced_Segment *referenced_segment_handler;
		referenced_segment_handler = new TK_Referenced_Segment(TKE_Style_Segment);
		referenced_segment_handler->SetSegment(style_segment_name);
		hdwg_status = WriteObject(referenced_segment_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete referenced_segment_handler;
	}

	if( !is_color_by_block && set_color)
	{
		if(style_seg_handler != NULL)
		{
			//HC_Set_Color_By_Value ("edges=markers=lines=text","RGB", r, g, b);
			TK_Color_RGB	*rgb_color_handler;
			rgb_color_handler = new TK_Color_RGB();
			rgb_color_handler->SetGeometry (TKO_Geo_Edge|TKO_Geo_Line|TKO_Geo_Marker|TKO_Geo_Text);
			rgb_color_handler->SetRGB(r, g, b);
			hdwg_status = WriteObject(rgb_color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete rgb_color_handler;
		}
		else
		{
			//HC_Set_Color_By_Value ("geometry","RGB", r, g, b);
			TK_Color_RGB	*rgb_color_handler;
			rgb_color_handler = new TK_Color_RGB();
			rgb_color_handler->SetGeometry (TKO_Geo_Geom_Colors);
			rgb_color_handler->SetRGB(r, g, b);
			hdwg_status = WriteObject(rgb_color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete rgb_color_handler;
		}
	}

	if( (!is_alpha_by_block) && (alpha != 255) )
	{
		char htrans_options[MVO_BUFFER_SIZE];
		float halpha = alpha/255.0f;
		sprintf(htrans_options, "geometry=(transmission=(r=%f g=%f b=%f))", halpha, halpha, halpha);
		//HC_Set_Color(htrans_options);

		TK_Color  color_handler;
		color_handler.SetGeometry(TKO_Geo_Geom_Colors);
		color_handler.SetTransmission(halpha, halpha, halpha);
		hdwg_status = WriteObject(&color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
	}

	if(line_type_id != AcDbObjectId::kNull)
	{
		bool is_weight_by_block;
		float h_line_wt;
		get_entity_line_weight (pEnt, pLayerTableRecord, h_line_wt, is_weight_by_block);
		if( !is_weight_by_block )
		{
			//HC_Set_Line_Weight(h_line_wt);
			TK_Size						*size_handler;
			size_handler= new TK_Size(TKE_Line_Weight);
			size_handler->SetSize(h_line_wt); 
			hdwg_status = WriteObject(size_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete size_handler;
		}
	}
	import_entity_linetype(pEnt, pLayerTableRecord);
	if( !is_visible )
	{
		//HC_Set_Visibility("off");
		TK_Visibility	*vis_handler = new TK_Visibility();
		vis_handler->SetGeometry (TKO_Geo_All_Visibles);
		vis_handler->SetValue(0);
		hdwg_status = WriteObject(vis_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete vis_handler;
	}
	if(m_bAmIsolidHatch)
	{
		//HC_Set_Visibility("face=on,edge=off");
		TK_Visibility	*vis_handler = new TK_Visibility();
		vis_handler->SetGeometry (TKO_Geo_Face);
		vis_handler->SetValue(1);
		hdwg_status = WriteObject(vis_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete vis_handler;

		TK_Visibility	*vis_handler1 = new TK_Visibility();
		vis_handler1->SetGeometry (TKO_Geo_Edge);
		vis_handler1->SetValue(0);
		hdwg_status = WriteObject(vis_handler1,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete vis_handler1;
	}

	// Close layer table record
	if (pLayerTableRecord)
		pLayerTableRecord->close();

	if (pEnt->isA() == AcDbCircle::desc()) 
		importAcDbCircle((AcDbCircle*)pEnt);
	else if (pEnt->isA() == AcDbMText::desc()) 
		importAcDbMText((AcDbMText*)pEnt);
	else if (pEnt->isKindOf(AcDbDimension::desc())) 
		importAcDbDimension((AcDbDimension*)pEnt);
	else if (pEnt->isKindOf(AcDbPoint::desc())) 
		importAcDbPoint((AcDbPoint*)pEnt);
	else if (pEnt->isKindOf(AcDbLine::desc()))
		importAcDbLine((AcDbLine*)pEnt);
	else if (pEnt->isKindOf(AcDbXline::desc()))
		importAcDbXline((AcDbXline*)pEnt);
	else if (pEnt->isKindOf(AcDbRay::desc()))
		importAcDbRay((AcDbRay*)pEnt);
	else if (pEnt->isKindOf(AcDbViewport::desc()))
		importAcDbViewport((AcDbViewport*)pEnt);
	else if (pEnt->isKindOf(AcDbRasterImage::desc()))
		importAcDbRasterImage((AcDbRasterImage*)pEnt);
	else if (pEnt->isKindOf(AcDbMLeader::desc()))
		importAcDbMLeader((AcDbMLeader*)pEnt);
#ifdef WIN32
	else if (pEnt->isKindOf(AcDbTable::desc()))
		importAcDbTable((AcDbTable*)pEnt);
#endif
	else
	{
		HAcGiWorldDraw hacgi_world_draw(this, pEnt);

		bool optimize_segment = (draw_shaded && m_bMergeEntityShells 
			&& (pEnt->isA() != AcDbBlockReference::desc()));

		if ( draw_shaded == true )
		{
			if( optimize_segment )
			{
				// in this mode, we insert shells in a temporary HOOPS segment
				// the then merge/optimize them before dumping it in HSF
				HC_Open_Segment(HIODWG_SCRATCH_SEGMENT);
				m_bScratchSegOpen = true;
			}

			// import shaded
			hacgi_world_draw.setRegenType(kAcGiHideOrShadeCommand);
			if(pEnt->worldDraw(&hacgi_world_draw)== Adesk::kFalse)
			{
				/////The AcGiViewportDraw class is a container class that provides the ability to generate different 
				////geometry for different viewports. During entity regeneration, an entity's viewportDraw() method 
				/////is only called if the entity's worldDraw() method returns Adesk::kFalse. ---- Sumitk 18 mar 09.
				HAcGiViewportDraw hacgi_VP_draw(this, pEnt);
				pEnt->viewportDraw(&hacgi_VP_draw);				
			}			
		}

		if( m_bDrawWireframe == true )                                                                                                    
		{
			// import wireframe
			hacgi_world_draw.setRegenType(kAcGiStandardDisplay );
			if(pEnt->worldDraw(&hacgi_world_draw)== Adesk::kFalse)
			{
				/////The AcGiViewportDraw class is a container class that provides the ability to generate different 
				////geometry for different viewports. During entity regeneration, an entity's viewportDraw() method 
				/////is only called if the entity's worldDraw() method returns Adesk::kFalse. ---- Sumitk 18 mar 09.
				HAcGiViewportDraw hacgi_VP_draw(this, pEnt);
				pEnt->viewportDraw(&hacgi_VP_draw);				
			}
		}

		if( optimize_segment )
		{
			if(m_bShellWithFaceColor)//DWG Shell is with individual Face Colors set
			{
				HC_Optimize_Segment_Tree(".", "merge shells=on");

				//Get Shell Key
				char type[64];
				HC_KEY shell_key = INVALID_KEY;
				HC_KEY	new_key;
				HC_Begin_Contents_Search(".", "shells");
				while(HC_Find_Contents (type, &new_key)) 
				{
					if( streq( type, "shell" )) 
					{
						shell_key = new_key;
						break;
					}
				}
				HC_End_Contents_Search ();

				if(shell_key != INVALID_KEY)
				{
					HShellWrapper* shell = new HShellWrapper(shell_key);

					//Get Face Count
					float* face_color = 0;
					int faceCount = 0;
					int ii = 0;
					if(shell->m_flen)
					{
						while( ii < shell->m_flen)
						{
							faceCount++;
							ii = ii + shell->m_Flist[ii] + 1;
						}
					}

					//Get Face colors
					int face_list_length;
					int nPoints;

					// check how colors are set.
					int by_face = 0;
					int by_vertex = 0;

					HC_Show_Shell_Size( shell_key, &nPoints, &face_list_length );

					// make a quick test if it has cours on face or on shells.
					HC_Open_Geometry( shell_key );
					{
						HC_Open_Face(0);
						by_face = HC_Show_Existence("color");
						HC_Close_Face();

						HC_Open_Vertex(0);
						by_vertex = HC_Show_Existence("color");
						HC_Close_Vertex();
					}
					HC_Close_Geometry();

					float * face_colors = 0;
					float * vertex_colors = 0;

					// set colors either on face or vertex based on previous findings.
					if(by_face)
					{
						face_colors = new float[faceCount*3];
						HC_MShow_Face_Colors_By_Value(shell_key, 0, faceCount, face_colors);
					}
					if(by_vertex)
					{
						vertex_colors = new float[nPoints*3];
						HC_MShow_Vertex_Colors_By_Value(shell_key, "face", 0, nPoints, vertex_colors);
					}

					// Add this information in shell handler
					TK_Shell shell_handler;
					shell_handler.SetPoints(shell->m_plen, (float*)shell->m_Points);
					shell_handler.set_flist(shell->m_flen, shell->m_Flist);
					if(face_colors)
					{
						shell_handler.SetFaceColors((float*)face_color);
						delete[] face_colors;
					}
					if(vertex_colors)
					{
						shell_handler.SetVertexColors(vertex_colors);
						delete[] vertex_colors;
					}
					if(shell->m_VNormals)
					{
						shell_handler.SetVertexNormals((float*)shell->m_VNormals);
					}
					TK_Status hdwg_status = WriteObject(&shell_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
					H_ASSERT(hdwg_status == TK_Normal);
					delete shell;
				}//End of INVALID_KEY check
			}
			else
			{
				// geth the optimized shell points
				HShell	total_info;
				HShell	max_info;
				HUtility::Segment_Shell_Allocate (&total_info, &max_info, true);
				HUtility::Recursive_Merge_Shells (&total_info, &max_info, true, true);//Doesn't honor face colors while merging

				TK_Shell shell_handler;
				shell_handler.SetPoints(total_info.point_list_len, (float*)total_info.point_list);
				shell_handler.set_flist(total_info.face_list_len, total_info.face_list);
				if(total_info.normal_list)
				{
					// Reversing the normals here
					// Refer to: "NOTE ON NORMALS AND LIGHTING PROBLEM" - in this file
					for(int i = 0; i < total_info.point_list_len; i++ )
					{
						total_info.normal_list[i].x = - total_info.normal_list[i].x;
						total_info.normal_list[i].y = - total_info.normal_list[i].y;
						total_info.normal_list[i].z = - total_info.normal_list[i].z;
					}
					shell_handler.SetVertexNormals((float*)total_info.normal_list);
				}
				TK_Status hdwg_status = WriteObject(&shell_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
				H_ASSERT(hdwg_status == TK_Normal);
			}

			HC_Flush_Segment(".");
			HC_Close_Segment();
			m_bScratchSegOpen = false;
			m_bShellWithFaceColor = false;
		}

	}

	if( m_bImportXData )
	{
#ifndef HDWG_NO_HYPERLINKS_IMPORT			
		import_hyperlinks(pEnt);
#endif //HDWG_NO_HYPERLINKS_IMPORT
		importXdata(pEnt);
	}

	if(m_bAttachDWGHandles)
	{
		attachDWGHandle(pEnt);
	}

	//HC_Close_Segment();
	STREAM_Close_Segment(); //entity_segment_name

	//HC_Close_Segment();
	STREAM_Close_Segment(); //blck_table_rec_seg_key / parent_seg

	H_SAFE_DELETE(style_seg_handler);
}


void HDWG_BStreamImporter::importAcDbMTextFragment(AcDbMTextFragment* pAcDbMTextFragment, AcDbMText* pOrigAcDbMText)
{
	TK_Status hdwg_status; 
	HC_KEY text_key = INVALID_KEY;
	static int frag_no = 1;

	float h_pos[3], h_dir[3], h_norm[3];

	h_pos[0] = (float) pAcDbMTextFragment->location.x;
	h_pos[1] = (float) pAcDbMTextFragment->location.y;
	h_pos[2] = (float) pAcDbMTextFragment->location.z;

	h_dir[0] = (float) pAcDbMTextFragment->direction.x;
	h_dir[1] = (float) pAcDbMTextFragment->direction.y;
	h_dir[2] = (float) pAcDbMTextFragment->direction.z;

	h_norm[0] = (float) pAcDbMTextFragment->normal.x;
	h_norm[1] = (float) pAcDbMTextFragment->normal.y;
	h_norm[2] = (float) pAcDbMTextFragment->normal.z;


	// open a segment for this entity. We don't think this is really optimal,
	// rather we should open the segment based on color. But let's see
	char segment_name[MVO_BUFFER_SIZE];
	sprintf(segment_name, "mtext_frag_%d", frag_no++);

	//HC_Open_Segment(segment_name);
	TK_Open_Segment	 *open_seg_handler = NULL;
	open_seg_handler= new TK_Open_Segment;
	open_seg_handler->SetSegment(segment_name);
	hdwg_status = WriteObject(open_seg_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete open_seg_handler;

	{
		TK_Text_Font *text_font_handler;
		text_font_handler= new TK_Text_Font();
		text_font_handler->SetMask(0);

		// NOTE: This is somewhat ObjectARX oddity. The fragment can have color viz.
		// BY_BLOCK, BY_LAYER etc., but then it is not even an AcDbEntity
		// I fail to understand why getting a color of entity has to be so complicated.
		// Rajesh B (27-Jun-06)
		AcCmEntityColor color = pAcDbMTextFragment->color;
		//Adesk::UInt16 color_idx = pAcDbMTextFragment->colorIndex();
		if( color.isByLayer() )
		{
			// import the color of pOrigAcDbMText's layer
			Adesk::UInt16 color_idx = ((AcDbEntity*)pOrigAcDbMText)->colorIndex();
			AcCmColor cm_color = ((AcDbEntity*)pOrigAcDbMText)->color();

			// color is BYLAYER
			if(color_idx == 256 )
			{
				AcDbLayerTableRecord *pLayerTableRecord = 0;
				AcDbObjectId ent_layer_id = ((AcDbEntity*)pOrigAcDbMText)->layerId();

				Acad::ErrorStatus es = acdbOpenObject(pLayerTableRecord, ent_layer_id, AcDb::kForRead);
				if (pLayerTableRecord)
				{
					cm_color = pLayerTableRecord->color();
					color_idx = cm_color.colorIndex();
					pLayerTableRecord->close();
				}
			}
			Adesk::UInt32 RGBM_byte = AcCmEntityColor::lookUpRGB(color_idx);
			float r,g,b;
			r = (float) GetRValueFromRGBM(RGBM_byte)/255.0f;
			g = (float) GetGValueFromRGBM(RGBM_byte)/255.0f;
			b = (float) GetBValueFromRGBM(RGBM_byte)/255.0f;
			//HC_Set_Color_By_Value ("text","RGB", r, g, b);

			TK_Color_RGB				*rgb_color_handler;
			rgb_color_handler = new TK_Color_RGB();
			rgb_color_handler->SetGeometry (TKO_Geo_Text);
			rgb_color_handler->SetRGB(r, g, b);
			hdwg_status = WriteObject(rgb_color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete rgb_color_handler;
		}
		else if (color.isByBlock())
		{
			// do nothing. inherit parent's attributes
		}
		else
		{
			// if it is by block, let's not set any color, let the color be it's parents
			//Adesk::UInt16 color_idx = color.trueColor();

			Adesk::UInt32 RGBM_byte = AcCmEntityColor::lookUpRGB(color.colorIndex());
			float r,g,b;
			r = (float) GetRValueFromRGBM(RGBM_byte)/255.0f;
			g = (float) GetGValueFromRGBM(RGBM_byte)/255.0f;
			b = (float) GetBValueFromRGBM(RGBM_byte)/255.0f;
			//HC_Set_Color_By_Value ("text","RGB", r, g, b);

			TK_Color_RGB				*rgb_color_handler;
			rgb_color_handler = new TK_Color_RGB();
			rgb_color_handler->SetGeometry (TKO_Geo_Text);
			rgb_color_handler->SetRGB(r, g, b);
			hdwg_status = WriteObject(rgb_color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete rgb_color_handler;
		}	


		//*****************************************************************		
		AcDbMText::AttachmentPoint eattachpoint = pOrigAcDbMText->attachment();	
		int alignment_index;
		alignment_index = TKO_Text_Alignment_Insertion_Left; // ADN query 1256676, Eventum issue 11785 
		// After fragmentation each fragment resides at bottom left. << ASHISH.S. 11/02/2010
		/*if( (((AcDbEntity*)pOrigAcDbMText)->isKindOf(AcDbMText::desc())) )
		get_Mtext_alignment(eattachpoint,&alignment_index);			REMOVE */
		//*****************************************************************

		// We observed (in AutoCAD) that after exploding the Mtext, the text fragments always are Left Justified.
		// Also, the AcDbMtextFragment struct does not have any member for alignment/justification, 
		// hence it seems that we can safely assume it is left(hori) center(vert). Sumit K (25/04/2008)

		//text_key = import_text(h_pos, h_dir, h_norm, pAcDbMTextFragment->text, TKO_Text_Alignment_Middle_Left);

		// Transforms are handled generically (for planes other than XY) in this function. 
		//Beta << ASHISH.S. 17/08/2009.
		text_key = apply_transforms_and_insert_text(h_pos, h_dir, h_norm, pAcDbMTextFragment->text, alignment_index);

		//char h_name[MVO_BUFFER_SIZE];
		ACHAR * p_fname = 0;
		if(pAcDbMTextFragment->font && (wcscmp(pAcDbMTextFragment->font, L"") != 0))
			p_fname = pAcDbMTextFragment->font;
		else if(pAcDbMTextFragment->fontname && (wcscmp(pAcDbMTextFragment->fontname, L"") != 0))
			p_fname = pAcDbMTextFragment->fontname;
		else if(pAcDbMTextFragment->bigfont && (wcscmp(pAcDbMTextFragment->bigfont, L"") != 0))
			p_fname = pAcDbMTextFragment->bigfont;
		if( p_fname )
		{
			text_font_handler->SetMask(text_font_handler->GetMask() | TKO_Font_Names);
			text_font_handler->SetValue(text_font_handler->GetValue() | TKO_Font_Names);
			//sprintf(h_name, "name = %s", H_ASCII_tEXT(p_fname));
			//HC_Set_text_Font(h_name);
			text_font_handler->SetNames (H_ASCII_TEXT(p_fname));
		}

		if(pAcDbMTextFragment->widthFactor != 1.0f)
		{
			//char h_wscale[MVO_BUFFER_SIZE];
			//sprintf(h_wscale, "width scale = %f", (float)pAcDbMTextFragment->widthFactor);
			//HC_Set_text_Font(h_wscale);
			text_font_handler->SetMask(text_font_handler->GetMask() | TKO_Font_Width_Scale);
			text_font_handler->SetValue(text_font_handler->GetValue() | TKO_Font_Width_Scale);
			text_font_handler->SetWidthScale ((float)pAcDbMTextFragment->widthFactor);
		}

		if(pAcDbMTextFragment->bold)
		{
			//HC_Set_text_Font("bold=on");
			text_font_handler->SetMask (text_font_handler->GetMask() | TKO_Font_Bold );
			text_font_handler->SetValue(text_font_handler->GetValue() | TKO_Font_Bold);
		}
		if(pAcDbMTextFragment->italic)
		{
			//HC_Set_text_Font("italic=on");
			text_font_handler->SetMask(text_font_handler->GetMask() | TKO_Font_Italic);
			text_font_handler->SetValue(text_font_handler->GetValue() | TKO_Font_Italic);
		}

		//char h_size[MVO_BUFFER_SIZE];
		//sprintf(h_size, "size = %f oru", (float)pAcDbMTextFragment->capsHeight);
		//HC_Set_text_Font(h_size);
		text_font_handler->SetMask(text_font_handler->GetMask() | TKO_Font_Size);
		text_font_handler->SetValue(text_font_handler->GetValue() | TKO_Font_Size);
		text_font_handler->SetSizeUnits(TKO_Font_Size_Object);
		text_font_handler->SetSize ((float)pAcDbMTextFragment->capsHeight);

		hdwg_status = WriteObject(text_font_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete text_font_handler;

		// TODO: convert following attributes
		//AcGePoint2d extents;
		//double obliqueAngle;
		//double trackingFactor;
		////  stack flags
		//unsigned stackTop:1;
		//unsigned stackBottom:1;
		////  underline/overline data
		//unsigned underlined:1;
		//unsigned overlined:1;
		//AcGePoint3d underPoints[2];
		//AcGePoint3d overPoints[2];
	}
	//HC_Close_Segment();
	TK_Close_Segment			*close_seg_handler ; 
	close_seg_handler = new TK_Close_Segment;
	hdwg_status = WriteObject(close_seg_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete close_seg_handler;

	//if(m_pConnectivityInfo)
	//m_pConnectivityInfo->AddConnection(text_key, (void*) pOrigAcDbMText);
}

void HDWG_BStreamImporter::importAcDbCircle(AcDbCircle *pAcDbCircle)
{
	TK_Status hdwg_status; 
	HC_KEY circle_key = INVALID_KEY;
	double radius = pAcDbCircle->radius();
	AcGePoint3d center = pAcDbCircle->center();
	double thickness = pAcDbCircle->thickness();
	AcGeVector3d normal = pAcDbCircle->normal();

	float h_center1[3];
	h_center1[0] = (float)center.x;
	h_center1[1] = (float)center.y;
	h_center1[2] = (float)center.z;

	if (thickness == 0)
	{
		if( !m_bDrawWireframe )
			return;

		AcGeVector3d Wx(1, 0, 0);
		AcGeVector3d Wy(0, 1, 0);
		AcGeVector3d Wz(0, 0, 1);
		AcGeVector3d Ax,Ay,Az;

		if ((fabs (normal.x) < 1.0f/64.0f) && (fabs (normal.y) < 1.0f/64.0f))
			Ax = Wy.crossProduct(normal);
		else
			Ax = Wz.crossProduct(normal);

		Ax.normalize();

		Ay = normal.crossProduct(Ax);
		Ay.normalize();

		Az = normal;

		double cos_X_alpha = Wx.dotProduct(Ax);
		double cos_X_beta  = Wy.dotProduct(Ax);
		double cos_X_theta = Wz.dotProduct(Ax);

		float h_major[3];
		h_major[0] = (float) (center.x + radius*cos_X_alpha);
		h_major[1] = (float) (center.y + radius*cos_X_beta);
		h_major[2] = (float) (center.z + radius*cos_X_theta);

		double cos_Y_alpha = Wx.dotProduct(Ay);
		double cos_Y_beta  = Wy.dotProduct(Ay);
		double cos_Y_theta = Wz.dotProduct(Ay);

		float h_minor[3];
		h_minor[0] = (float) (center.x + radius*cos_Y_alpha);
		h_minor[1] = (float) (center.y + radius*cos_Y_beta);
		h_minor[2] = (float) (center.z + radius*cos_Y_theta);

		//circle_key = HC_KInsert_Elliptical_Arc (h_center1, h_major, h_minor, 0.0f, 1.0f);
		TK_Ellipse					*ellipse_handler;
		ellipse_handler = new TK_Ellipse(TKE_Elliptical_Arc); 
		ellipse_handler-> SetCenter(h_center1[0], h_center1[1], h_center1[2]);
		ellipse_handler-> SetMajor (h_major);
		ellipse_handler-> SetMinor (h_minor);
		ellipse_handler->SetLimits(0.0f, 1.0f);
		hdwg_status = WriteObject(ellipse_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete ellipse_handler;
	}
	else 
	{
		m_bIs2DEntity = false;
		float h_center2[3];
		h_center2[0] = (float)(center.x+(thickness*normal.x));
		h_center2[1] = (float)(center.y+(thickness*normal.y));
		h_center2[2] = (float)(center.z+(thickness*normal.z));
		// Insert_Circle_By_Radius would have been much easier to use, but it inserts
		// a circular disc, which is not what we want here.
		// circle_key = HC_KInsert_Cylinder (h_center1,h_center2, (float)radius,"none" );

		float cyl_axis[]={h_center1[0], h_center1[1], h_center1[2], h_center2[0], h_center2[1], h_center2[2]};
		TK_Cylinder	*cylinder_handler;
		cylinder_handler = new TK_Cylinder();
		cylinder_handler->SetAxis (cyl_axis);
		cylinder_handler->SetRadius ((float)radius);
		cylinder_handler->SetCaps (0);
		hdwg_status = WriteObject(cylinder_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete cylinder_handler;
	}

	//if(m_pConnectivityInfo)
	//m_pConnectivityInfo->AddConnection(circle_key, (void*)pAcDbCircle);
}

static char const * marker_symbols[] = {
	"o",            "(.)",  "(+)",  "(x)",  "(())", "@",
	".",    "+",    "x",            "*",
	"[]",           "[.]",          "[x]",          "[*]",
	"<>",           "<.>",  "<+>",                  "<*>",
	"/\\",  "^/\\", "/.\\",                         "/*\\",     "^/*\\",
	"\\/",  "v\\/", "\\./",                         "\\*/",     "v\\*/",
	"|>",   ">|>",  "|.>",                          "|*>",      ">|*>",
	"<|",   "<<|",  "<.|",                          "<*|",      "<<*|",

	"#",    "++",   "/ \\", "/_\\",
	"|",    "/",    "\\",   "/__\\",    "/_^_\\",
	"y",    "z",
};
void HDWG_BStreamImporter::set_marker_settings(const Adesk::Int16 db_pdmode,const double db_pdsize )
{
	if( db_pdmode == 1)
	{
		// fix for 10511
		TK_Size	*size_handler;
		TK_Status hdwg_status;
		size_handler= new TK_Size(TKE_Marker_Size);
		size_handler->SetSize(0.0); 
		hdwg_status = WriteObject(size_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete size_handler;
		return;
	}
	// Before getting into this, please read AutoCAD docs on PDMODE, PDSIZE and POINT commands. Some excerpts below
	// The PDMODE and PDSIZE system variables control the appearance of point objects. 
	// PDMODE values 0, 2, 3, and 4 specify a figure to draw through the point. 
	// A value of 1 specifies that nothing is displayed.
	// TODO: Support Thickness
	// TODO: Support transformable markers - markers which remain in the plane they were inserted/3D markers
	int n_glyphs = countof(GlyphTable);
	int i_glyph = 0;
	for(i_glyph = 0; i_glyph < n_glyphs; i_glyph++ )
	{
		if( GlyphTable[i_glyph].iSymbolPDMODE == db_pdmode )
			break;
	}

	if( i_glyph >= n_glyphs )
	{
		// This PDMODE is not found and may not be supported
		// We will let HOOPS fallback to whatever default symbol it wants to
		H_ASSERT(0);
		return;
	}

	HIODWG_GLYPH pGlyph = GlyphTable[i_glyph];
	TK_Status hdwg_status;

	TK_Named *named_handler= new TK_Named(TKE_Marker_Symbol);
	if( pGlyph.pSymbolDefinition )
	{
		// this is not a standard HOOPS marker, we may have to define this as glyph
		TK_Glyph_Definition * glyph_def = new TK_Glyph_Definition();
		//HC_Define_Glyph( pGlyph.pSymbolName, pGlyph.nSybolDefinitionSize,pGlyph.pSymbolDefinition);
		glyph_def->SetDefinition(pGlyph.nSybolDefinitionSize,pGlyph.pSymbolDefinition);
		glyph_def->SetName(pGlyph.pSymbolName);
		hdwg_status = glyph_def->Write(*m_pBStreamtk);
		H_ASSERT(hdwg_status == TK_Normal);
		delete glyph_def;

		named_handler->SetName(pGlyph.pSymbolName); 
	}
	else
	{
		//HC_Set_Marker_Symbol(pGlyph.pSymbolName);
		named_handler->SetIndex(pGlyph.opcode_index); 
	}

	WriteObject(named_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	delete named_handler;
	// AutoCAD ref: PDSIZE controls the size of the point figures, except for PDMODE values 0 and 1. 
	// A setting of 0 generates the point at 5 percent of the drawing area height. 
	// A positive PDSIZE value specifies an absolute size for the point figures. 
	// A negative value is interpreted as a percentage of the viewport size. 
	// The size of all points is recalculated when the drawing is regenerated.
	// HOOPS ref: The default "1.0" marker size equals 3.0 percent of the height of the display screen or 
	// virtual display screen. More precisely, it describes a 3.0 percent circle into which any marker symbol (except ".") will be made as large as possible and still fit into it. 
	// So if, for example, you wanted a 3 pixel x 3 pixel box, you would need a circle of diameter 3*sqrt(2).
	float marker_size = 0.0;
	TK_Size	*size_handler;
	size_handler= new TK_Size(TKE_Marker_Size);
	if(db_pdmode == 0.0)
	{
		// for this mode, I found that whatever behaviour HOOPS has for 0 setting is same has AutoCAD
		// i.e. the marker size is constant regardless of everything else and probably 1 pixel.
		//HC_Set_Marker_Size(0);
		size_handler->SetSize(marker_size); 
	}
	else if( db_pdsize == 0.0 )
	{
		//HC_Set_Marker_Size( fabs(5.0/3.0) );
		marker_size = fabs(5.0/3.0);
		size_handler->SetSize(marker_size); 
	}
	else if( db_pdsize < 0.0 )
	{
		//HC_Set_Marker_Size( fabs(db_pdsize/3.0) );
		marker_size = fabs(db_pdsize/3.0);
		size_handler->SetSize(marker_size); 
	}
	else if( db_pdsize > 0.0 )
	{
		//HC_Set_Variable_Marker_Size(marker_size);
		size_handler->SetSize(db_pdsize,TKO_Generic_Size_Object); 
	}
	hdwg_status = WriteObject(size_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete size_handler;
}

void HDWG_BStreamImporter::importAcDbPoint(AcDbPoint *pAcDbPoint)
{
	// TODO: support point thickness
	TK_Status hdwg_status;
	AcGePoint3d pos = pAcDbPoint->position();
	AcGeVector3d normal = pAcDbPoint->normal();
	float  normal_vect[3];
	normal_vect[0] = (float)normal.x;
	normal_vect[1] = (float)normal.y;
	normal_vect[2] = (float)normal.z;

	//marker_key = HC_KInsert_Marker(pos.x, pos.y, pos.z);
	TK_Point* point_handler = new TK_Point(TKE_Marker);
	point_handler->SetPoint(pos.x, pos.y, pos.z);
	hdwg_status = WriteObject(point_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	delete point_handler;

	//HC_Set_Geometry_Options(marker_key,geo_option);
	TK_Geometry_Options *options_handler = new TK_Geometry_Options() ; 
	options_handler->SetMask(TKO_Geometry_Options_Orientation);
	options_handler->SetOrientation(3,normal_vect);
	hdwg_status = WriteObject(options_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	delete options_handler;

	//HC_Set_Visibility("markers=on");
	TK_Visibility	*vis_handler = new TK_Visibility();
	vis_handler->SetGeometry(TKO_Geo_Marker);
	vis_handler->SetValue(TKO_Geo_Marker);
	hdwg_status = WriteObject(vis_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete vis_handler;
}
void HDWG_BStreamImporter::importAcDbMInsertBlock(AcDbMInsertBlock *pAcDbMInsertBlock,TK_Open_Segment * open_seg_handler)
{
	int cols = (int)pAcDbMInsertBlock->columns();
	int rows = (int)pAcDbMInsertBlock->rows();
	double colSpac = pAcDbMInsertBlock->columnSpacing();
	double rowSpac = pAcDbMInsertBlock->rowSpacing();

	//HC_Open_Segment_By_Key(blck_table_rec_seg_key);   
	TK_Open_Segment* btr_seg_clone = new TK_Open_Segment;
	btr_seg_clone->SetSegment(open_seg_handler->GetSegment());
	TK_Status	hdwg_status = WriteObject(btr_seg_clone,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete btr_seg_clone;

	for(int i=0; i < cols; i++)
	{
		for( int j=0; j < rows; j++)
		{
			char seg_name[MVO_BUFFER_SIZE];
			TK_Status hdwg_status;
			sprintf(seg_name, "AcDbMInsertBlock_%p_%d_%d", pAcDbMInsertBlock, i,j);
			TK_Open_Segment	*parent_seg_handler = new TK_Open_Segment;
			parent_seg_handler->SetSegment(seg_name);
			hdwg_status = WriteObject(parent_seg_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			importAcDbBlockReference(pAcDbMInsertBlock, parent_seg_handler, i, j);

			TK_Close_Segment close_seg_handler ; 
			hdwg_status = WriteObject(&close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete parent_seg_handler;
		}
	}

	TK_Close_Segment close_seg_handler ; 
	hdwg_status = WriteObject(&close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);

}
void HDWG_BStreamImporter::importAcDbBlockReference(AcDbBlockReference *pAcDbBlockReference, TK_Open_Segment* parent_seg,
													int mib_col, int mib_row)
{

	// btr = Block Table Record
	AcDbObjectId btr_id = pAcDbBlockReference->blockTableRecord();
	if(btr_id.isValid() == false)
		return;

	TK_Status hdwg_status; 
	//HC_Open_Segment("/include library/other block table records");
	STREAM_Open_Segment("/include library/other block table records");

	TK_Open_Segment	*include_seg_handler = NULL;

	bool btr_not_loaded = false;
	include_seg_handler = GetBlockTableRecordSegmentFromId(btr_id, btr_not_loaded);

	if(m_bImportXData)
	{
		//ACHAR* lay = pAcDbBlockReference->layer();
		wchar_t *bName;			
		AcDbBlockTableRecord *pBlockTableRecord = 0;
		Acad::ErrorStatus es = acdbOpenObject(pBlockTableRecord, btr_id, AcDb::kForRead);
		if (pBlockTableRecord)
		{
			pBlockTableRecord->getName(bName);
			pBlockTableRecord->close();
		}

		std::map<int, wchar_t*>::iterator itr;
		for(itr = block_ref_record.begin(); itr != block_ref_record.end(); itr++)
		{
			if( wcsicmp(itr->second, (bName)) == 0)
			{
				m_BlockRefIndex = itr->first;
				break;
			}
		}
		acdbFree(bName);
	}

	bool include_blockref_as_xrefd_hsf = false;
	AcDbBlockTableRecord *pRecord = 0;
	acdbOpenObject(pRecord, btr_id, AcDb::kForRead);

	if( pRecord )
	{
		bool is_overlay_xref = pRecord->isFromOverlayReference();
		////// we don't want to import an overlay xref if this DWG file itself is xref'ed into another
		if( !(m_bAmIXref && is_overlay_xref) )
		{
#ifdef HIODWG_IMPORT_USE_HSF_XREFS
			include_blockref_as_xrefd_hsf = pRecord->isFromExternalReference();
#endif
			if( include_blockref_as_xrefd_hsf )
			{
				ACHAR* btr_path = 0;
				Acad::ErrorStatus acad_err = pRecord->pathName(btr_path);
				if( acad_err == Acad::eOk && btr_path )
				{
					TK_Open_Segment open_seg_hndlr;
					open_seg_hndlr.SetSegment(include_seg_handler->GetSegment());
					hdwg_status = WriteObject(&open_seg_hndlr, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
					H_ASSERT(hdwg_status == TK_Normal);

					wchar_t hsf_path[_MAX_PATH];
					wchar_t unused_dir[_MAX_DIR];
					//strcpy(hsf_path, H_ASCII_tEXT(btr_path));
					HUtility::FindFileNameAndDirectory((btr_path), unused_dir, hsf_path);

					wchar_t *path = hsf_path;
					wchar_t *end;
					for(end=path; *end; )
						end++;
					path = end;
					*--path = L'f'; *--path = L's'; *--path = L'h';

					// Get the Xref's hsf included in this segment.
					TK_External_Reference_Unicode hsf_xref;
					wchar_t xref_filepath[_MAX_PATH];
					swprintf(xref_filepath, _MAX_PATH, L"%ls%ls", unused_dir, hsf_path);
					hsf_xref.SetString(xref_filepath);
					hdwg_status = WriteObject(&hsf_xref, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
					H_ASSERT(hdwg_status == TK_Normal);

					TK_Close_Segment close_seg_handler ; 
					hdwg_status = WriteObject(&close_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
					H_ASSERT(hdwg_status == TK_Normal);
				}
			}
			else
			{
				// if the block table record is not loaded, load it before including it
				if (btr_not_loaded == true)
				{
					AcDbBlockTableRecordIterator *pRecordIter;

					//<< this is to handle draw order set on the entities.
					HDrawOrderHandler DrawOrderhandler(pRecord);
					DrawOrderhandler.Open();
					//>>
					if (pRecord->newIterator(pRecordIter) == Acad::eOk)
					{
						AcDbEntity *pBlockRefEnt;
						while (!pRecordIter->done())
						{
							if (pRecordIter->getEntity(pBlockRefEnt, AcDb::kForRead) == Acad::eOk)
							{
								importAcDbEntity(pBlockRefEnt, include_seg_handler, true);

								// Draw order settings starts
								// Look for draw order if not asked to ignore them. 
								if(m_bIs2DEntity == true && !m_bDisableDWGDrawOrder)
								{
									DrawOrderhandler.CheckDrawOrderAndSetVisibility(pBlockRefEnt, include_seg_handler, this);
								}
								pBlockRefEnt->close();
							}
							pRecordIter->step();
						}                            
						delete pRecordIter;
					}
					DrawOrderhandler.Close();
				}
			}
		}
		pRecord->close();
	}

	TK_Close_Segment			*close_seg_handler ; 
	close_seg_handler = new TK_Close_Segment;
	hdwg_status = WriteObject(close_seg_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete close_seg_handler;

	m_BlockRefIndex = -1;



	// we are organizing entities under their block table record. 
	// Fetch the block table record segment for this entity
	//	HC_KEY blck_table_rec_seg_key;
	TK_Open_Segment	 *blck_table_rec_seg = NULL;
	if(parent_seg == NULL)
		blck_table_rec_seg = GetBlockTableRecordSegmentForEntity(pAcDbBlockReference);
	else
		blck_table_rec_seg = parent_seg;

	//HC_Open_Segment_By_Key(blck_table_rec_seg_key);   
	TK_Open_Segment* btr_seg_clone = new TK_Open_Segment;
	btr_seg_clone->SetSegment(blck_table_rec_seg->GetSegment());
	hdwg_status = WriteObject(btr_seg_clone,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete btr_seg_clone;

	//-------------------------------------------------------
	// The code below is to get the attributes for an entity. Attributes are located inside BlockReferences. 
	// Our logic is if there is any BlockRefernce we store it under Include Library and then include it in
	// model segment. So now when we get a BlockReference we do the same and iterate the next record. 
	// Again if we get the same BlockRefernce instead of scanning it all
	// we know that the same BlockTableRecord exists and we just include it. But here at the second instance the 
	// attributes could be different. So we are separating the process scanning of BlockTableRefernce and querying 
	// of attributes. Further, we are including attributes directly under model segment because if we follow the usual way of 
	// including it under include library then they never get included in model Segment. 
	// This seems little confusing and defies our understanding of BlockReference.
	// Pavan Totala (19-Apr-07)
	AcDbObjectIterator* pIter = pAcDbBlockReference->attributeIterator();
	while (!pIter->done())
	{
		AcDbObjectId objId = pIter->objectId();
		AcDbAttribute *pAtt;
		if (pAcDbBlockReference->openAttribute(pAtt, objId, AcDb::kForRead) == Acad::eOk)
		{
			Adesk::Boolean isInvisible = pAtt->isInvisible();
			if(isInvisible == Adesk::kFalse)
				importAcDbEntity(pAtt, blck_table_rec_seg);
			pAtt->close();
		}
		pIter->step();
	}
	delete pIter;
	//-------------------------------------------------------

	// create a segment for the block reference
	char block_ref_seg_name[MVO_BUFFER_SIZE];
	sprintf(block_ref_seg_name, "block_ref_%p", pAcDbBlockReference);

	//HC_Open_Segment(block_ref_seg_name);
	STREAM_Open_Segment(block_ref_seg_name);

	// Get Layer table record, closed at the end of this method
	AcDbLayerTableRecord *pLayerTableRecord = 0;
	AcDbObjectId ent_layer_id = pAcDbBlockReference->layerId();
	Acad::ErrorStatus es = acdbOpenObject(pLayerTableRecord, ent_layer_id, AcDb::kForRead);

	// To set Visibility. //ASHISH.S. 07/04/2009
	// The XRef which is going to be included under this segment is affected by the 
	// Freeze/thaw status of this pAcDbBlockReference's layer.
	// for now if the layer of this pAcDbBlockReference is frozen, the attached Xref on this layer will be invisible.

	// Breif description of how AutoCAD behaves for XRef layers.
	// If Xref is attached on a 'layer FOO of Master', the following attributes get inherited by the XRef layers as described below.
	// visibility - 0th layer of XRef get visibility status from FOO. Other layers of XRef follows their original visibility status.
	// color - 0th layer of XRef get color status from FOO. Other layers of XRef follows their original color.
	// Freeze/ Thaw - All layers of XRef follows this attribute from FOO. That means if FOO is frozen the XRef layers and entities are invisible.
	// It is bit tricky to impose the visibility and color attribute of FOO on the XRef layers as per above rules.
	// Hence for now only Freeze/ Thaw is implemented here.
	// Refer issues 10129, 10147(ADN Query).
	// get_entity_visibility checks for both entity's own and its layers visibility/thaw-frozen status.
	// Also
	// Check for visibility of the blockref itself (for issue 10917)
	bool is_visible = true;
	get_entity_visibility(pAcDbBlockReference, pLayerTableRecord, is_visible);
	if(!is_visible)
	{
		//HC_Set_Visibility("off");
		TK_Visibility * vis_handler = new TK_Visibility();
		vis_handler->SetGeometry(TKO_Geo_All_Visibles);
		vis_handler->SetValue(0);
		TK_Status hdwg_status = WriteObject(vis_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete vis_handler;

		//HC_Set_Heuristics("exclude bounding");
		TK_Heuristics * heuristic_handler = new TK_Heuristics;
		heuristic_handler->SetMask( TKO_Heuristic_Exclude_Bounding );
		heuristic_handler->SetValue( TKO_Heuristic_Exclude_Bounding );
		hdwg_status = WriteObject(heuristic_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete heuristic_handler;

		//HC_Set_Rendering_Options("attribute lock = visibility");
		TK_Rendering_Options * rendering_handler = new TK_Rendering_Options;
		rendering_handler->SetMask(TKO_Rendo_Attribute_Lock);
		rendering_handler->SetValue(TKO_Rendo_Attribute_Lock);
		rendering_handler->SetLockMask(TKO_Lock_Visibility);
		rendering_handler->SetLockValue(TKO_Lock_Visibility);
		rendering_handler->SetVisibilityLockMask(TKO_Geo_All_Visibles);
		rendering_handler->SetVisibilityLockValue(TKO_Geo_All_Visibles);
		hdwg_status = WriteObject(rendering_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete rendering_handler;
	}
	//

	// include the referenced block table record here

	//////We found some BLOCKS in dwg drawings which were either empty(ex.CPM) (not having any geometry/Entity) or having
	////// entities we don't want to import(ex.	RM_SDB).This check will make sure we never include such segments whiCh never 
	///// get loaded due empty blockTableRecords..SumitK()11/06/2008

	//HC_Include_Segment_By_Key(btr_seg_key);
	char include_seg_name[MVO_BUFFER_SIZE];
	char full_path_seg_name[MVO_BUFFER_SIZE];
	strcpy(include_seg_name, include_seg_handler->GetSegment()); 
	condition_string_for_segment_name(include_seg_name);
	sprintf(full_path_seg_name, "/include library/other block table records/%s", include_seg_name);
	TK_Referenced_Segment	*referenced_segment_handler;
	referenced_segment_handler = new TK_Referenced_Segment(TKE_Include_Segment);
	referenced_segment_handler->SetSegment(full_path_seg_name);
	hdwg_status = WriteObject(referenced_segment_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete referenced_segment_handler;

	//insert the clipping polygon here 
	insertClip(pAcDbBlockReference, m_pBStreamtk);

	// let's set the default attributes (color, line wt etc.) which will act 
	// as attributes for entities which have them BYBLOCK.
	float r, g, b;
	bool is_color_by_block;
	get_entity_rgb(pAcDbBlockReference, pLayerTableRecord, r, g, b, is_color_by_block);
	if(!is_color_by_block)
	{
		//HC_Set_Color_By_Value ("geometry","RGB", r, g, b);
		TK_Color_RGB				*rgb_color_handler;
		rgb_color_handler = new TK_Color_RGB();
		rgb_color_handler->SetGeometry (TKO_Geo_Geom_Colors);
		rgb_color_handler->SetRGB(r, g, b);
		hdwg_status = WriteObject(rgb_color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete rgb_color_handler;
	}

	int alpha = 255;
	bool is_alpha_by_block;
	get_entity_transparency(pAcDbBlockReference, pLayerTableRecord, alpha, is_alpha_by_block );

	if( (!is_alpha_by_block) && (alpha != 255) )
	{
		char htrans_options[MVO_BUFFER_SIZE];
		float halpha = alpha/255.0f;
		sprintf(htrans_options, "geometry=(transmission=(r=%f g=%f b=%f))", halpha, halpha, halpha);
		//HC_Set_Color(htrans_options);
		TK_Color color_handler;
		color_handler.SetGeometry(TKO_Geo_Geom_Colors);
		color_handler.SetTransmission(halpha, halpha, halpha);
		hdwg_status = WriteObject(&color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
	}

	bool is_weight_by_block;
	float h_line_wt;
	get_entity_line_weight (pAcDbBlockReference, pLayerTableRecord, h_line_wt, is_weight_by_block);
	if( !is_weight_by_block )
	{
		//HC_Set_Line_Weight(h_line_wt);
		TK_Size						*size_handler;
		size_handler= new TK_Size(TKE_Line_Weight);
		size_handler->SetSize(h_line_wt); 
		hdwg_status = WriteObject(size_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete size_handler;
	}
	import_entity_linetype(pAcDbBlockReference, pLayerTableRecord);

	AcGeMatrix3d trans_matrix;
	trans_matrix = pAcDbBlockReference->blockTransform();
	if(trans_matrix != AcGeMatrix3d::kIdentity || mib_row || mib_col)
	{
		trans_matrix.transposeIt();
		float h_trans_matrix[4][4];
		for (int i =0; i<4; i++)
			for(int j =0; j<4; j++)
				h_trans_matrix[i][j] = (float) trans_matrix(i,j);

		/////VijayC: Individual block level scaling and rotation
		if(mib_row || mib_col)
		{
			double col_spec = ((AcDbMInsertBlock *)(pAcDbBlockReference))->columnSpacing();
			double row_spec = ((AcDbMInsertBlock *)(pAcDbBlockReference))->rowSpacing();
			HPoint trs_pt(mib_col * col_spec, mib_row * row_spec);
			float r_mat[16];
			double rot_angle = pAcDbBlockReference->rotation();
			AcGeScale3d scl_fact = pAcDbBlockReference->scaleFactors();
			rot_angle = rot_angle*180.0/HDWG_PI;
			HC_Compute_Rotation_Matrix(0.0, 0.0, rot_angle, r_mat);
			HC_Compute_Transformed_Points(1, (void*)&trs_pt, r_mat, (void*)&trs_pt);
			float trans_mat[16];
			HC_Compute_Translation_Matrix(trs_pt.x, trs_pt.y, trs_pt.z, trans_mat);
			if(scl_fact.sx) h_trans_matrix[0][0] /= scl_fact.sx;
			if(scl_fact.sy) h_trans_matrix[1][1] /= scl_fact.sy;
			if(scl_fact.sz) h_trans_matrix[2][2] /= scl_fact.sz;
			//HC_Compute_Matrix_Product((float*)h_trans_matrix,(float*)r_mat ,(float*)h_trans_matrix);
			HC_Compute_Matrix_Product((float*) h_trans_matrix,(float*) trans_mat,(float*)h_trans_matrix);
			if(scl_fact.sx) h_trans_matrix[0][0] *= scl_fact.sx;
			if(scl_fact.sy) h_trans_matrix[1][1] *= scl_fact.sy;
			if(scl_fact.sz) h_trans_matrix[2][2] *= scl_fact.sz;
		}
		TK_Matrix	*matrix_handler;
		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix((float*)h_trans_matrix);
		hdwg_status = WriteObject(matrix_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete matrix_handler;
	}

	// We are trying to apply scale to the geometry but its doesnt see to work properly.
	// apply the modeling matrix (if not identity)
	//	AcGeScale3d blck_ref_scale = pBlockRef->scaleFactors();
	//	if( blck_ref_scale != AcGeScale3d::kIdentity )
	//		HC_Scale_Object(blck_ref_scale[0], blck_ref_scale[1], blck_ref_scale[2]);

	delete include_seg_handler;
	if(parent_seg == NULL)
		delete blck_table_rec_seg;

	//HC_Close_Segment();
	STREAM_Close_Segment();

	//HC_Close_Segment();
	STREAM_Close_Segment();

	// Close layer table record
	if (pLayerTableRecord)
		pLayerTableRecord->close();
}
Adesk::Boolean HDWG_BStreamImporter::import_circle(const AcGePoint3d& pt1,
												   const AcGePoint3d& pt2,
												   const AcGePoint3d& pt3,
												   AcDbEntity* pDatabaseEntity
												   ) const
{
	if( !m_bDrawWireframe )
		return Adesk::kFalse;

	HPoint h_point1;
	HPoint h_point2;
	HPoint h_point3;

	h_point1.x  = (float)pt1.x;
	h_point1.y	= (float)pt1.y;
	h_point1.z	= (float)pt1.z;

	h_point2.x  = (float)pt2.x;
	h_point2.y	= (float)pt2.y;
	h_point2.z	= (float)pt2.z;

	h_point3.x  = (float)pt3.x;
	h_point3.y	= (float)pt3.y;
	h_point3.z	= (float)pt3.z;

	//bstream_CreateWireframeCircleWithEllipse(h_point1, h_point2, h_point3);

	const HPoint &x1 = h_point1;
	const HPoint &x2 = h_point2;
	const HPoint &x3 = h_point3;

	TK_Status hdwg_status; 

	// Using three points lying on the circumference of a circle we find the center of the circle
	//	and then we compute the major and minor axes such that they are the same length

	double A[2][2], InvA[2][2] ;
	HVector v1(x2.x - x1.x, x2.y - x1.y, x2.z - x1.z), v2(x3.x - x1.x, x3.y - x1.y, x3.z - x1.z) ;

	double v1LenSquared = HC_Compute_Vector_Length(&v1), v2LenSquared = HC_Compute_Vector_Length(&v2) ;
	v1LenSquared *= v1LenSquared ; v2LenSquared *= v2LenSquared ;

	double v1_Dot_v2 = HC_Compute_Dot_Product(&v1, &v2) ;

	A[0][0] = 2.0*v1LenSquared ; A[0][1] = 2.0*v1_Dot_v2 ;
	A[1][0] = 2.0*v1_Dot_v2 ;    A[1][1] = 2.0*v2LenSquared ;

	double invDetA = 1.0 / (A[0][0]*A[1][1]-A[0][1]*A[1][0]) ;

	InvA[0][0] = invDetA*(A[1][1]) ;  InvA[0][1] = invDetA*(-A[0][1]) ;
	InvA[1][0] = invDetA*(-A[1][0]) ; InvA[1][1] = invDetA*(A[0][0]) ;

	double alpha = InvA[0][0]*(v1LenSquared) + InvA[0][1]*(v2LenSquared),
		beta  = InvA[1][0]*(v1LenSquared) + InvA[1][1]*(v2LenSquared) ;

	HPoint center(x1.x + alpha*v1.x + beta*v2.x, x1.y + alpha*v1.y + beta*v2.y, x1.z + alpha*v1.z + beta*v2.z) ;

	HPoint major, minor ;
	major = HPoint(x1) ;
	HVector v3 = major - center, planeNormal, v4 ;
	double radiusSquared = HC_Compute_Vector_Length(&v3) ;
	radiusSquared *= radiusSquared ;

	HC_Compute_Cross_Product(&v1, &v2, &planeNormal) ;
	HC_Compute_Cross_Product(&planeNormal, &v3, &v4) ;

	double v4LenSquared = HC_Compute_Vector_Length(&v4) ;
	v4LenSquared *= v4LenSquared ;

	double delta = sqrt(radiusSquared / v4LenSquared) ;
	minor = HPoint(center.x + delta * v4.x, center.y + delta * v4.y, center.z + delta * v4.z) ;

	float h_major[3];
	h_major[0] = (float) (major.x);
	h_major[1] = (float) (major.y);
	h_major[2] = (float) (major.z);

	float h_minor[3];
	h_minor[0] = (float) (minor.x);
	h_minor[1] = (float) (minor.y);
	h_minor[2] = (float) (minor.z);

	//ret_geom_key = HC_KInsert_Elliptical_Arc(&center, &major, &minor, 0.0, 1.0) ;
	TK_Ellipse					*ellipse_handler;
	ellipse_handler = new TK_Ellipse(TKE_Elliptical_Arc); 
	ellipse_handler-> SetCenter(center.x, center.y, center.z);
	ellipse_handler-> SetMajor (h_major);
	ellipse_handler-> SetMinor (h_minor);
	ellipse_handler->SetLimits(0.0, 1.0);
	hdwg_status = WriteObject(ellipse_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete ellipse_handler;

	//if(m_pConnectivityInfo)
	//m_pConnectivityInfo->AddConnection(circle_key, pDatabaseEntity);

	return Adesk::kFalse;
}



Adesk::Boolean HDWG_BStreamImporter::import_circular_arc(const AcGePoint3d& center,
														 const double radius,
														 const AcGeVector3d& normal,
														 const AcGeVector3d& startVector,
														 const double sweepAngle,
														 const AcGiArcType arcType,
														 AcDbEntity* pDatabaseEntity
														 ) const
{
	if( !m_bDrawWireframe )
		return Adesk::kFalse;

	AcGeVector3d Wx(1, 0, 0);
	AcGeVector3d Wy(0, 1, 0);
	AcGeVector3d Wz(0, 0, 1);

	AcGeVector3d Ax,Ay,Az;

	Ax = startVector;
	Ax.normalize();

	Ay = normal.crossProduct(startVector);
	Ay.normalize();

	Az = normal;
	Az.normalize();

	double cos_X_alpha = Wx.dotProduct(Ax);
	double cos_X_beta  = Wy.dotProduct(Ax);
	double cos_X_theta = Wz.dotProduct(Ax);

	float h_major[3];
	h_major[0] = (float) (center.x + radius*cos_X_alpha);
	h_major[1] = (float) (center.y + radius*cos_X_beta);
	h_major[2] = (float) (center.z + radius*cos_X_theta);


	double cos_Y_alpha = Wx.dotProduct(Ay);
	double cos_Y_beta  = Wy.dotProduct(Ay);
	double cos_Y_theta = Wz.dotProduct(Ay);

	float h_minor[3];
	h_minor[0] = (float) (center.x + radius*cos_Y_alpha);
	h_minor[1] = (float) (center.y + radius*cos_Y_beta);
	h_minor[2] = (float) (center.z + radius*cos_Y_theta);

	float h_center[3];
	h_center[0] = (float)center.x;
	h_center[1] = (float)center.y;
	h_center[2] = (float)center.z;


	float h_start_angle = 0.0f;
	float h_end_angle = ((float)sweepAngle/(2.0f*HDWG_F_PI));


	TK_Status hdwg_status; 
	TK_Ellipse					*ellipse_handler;
	ellipse_handler = new TK_Ellipse(TKE_Elliptical_Arc); 
	ellipse_handler-> SetCenter(h_center[0], h_center[1], h_center[2]);
	ellipse_handler-> SetMajor (h_major);
	ellipse_handler-> SetMinor (h_minor);
	ellipse_handler->SetLimits(h_start_angle, h_end_angle);
	hdwg_status = WriteObject(ellipse_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete ellipse_handler;

	//HC_KEY arc_key = HC_KInsert_Elliptical_Arc (h_center,h_major,h_minor, h_start_angle,h_end_angle);
	//if(m_pConnectivityInfo)
	//m_pConnectivityInfo->AddConnection(arc_key, (void*) pDatabaseEntity);

	return Adesk::kFalse;
}


Adesk::Boolean HDWG_BStreamImporter::import_circular_arc(const AcGePoint3d& start,
														 const AcGePoint3d& point,
														 const AcGePoint3d& end,
														 const AcGiArcType arcType,
														 AcDbEntity* pDatabaseEntity
														 ) const
{
	if( !m_bDrawWireframe )
		return Adesk::kFalse;

	float h_point1[3];
	float h_point2[3];
	float h_point3[3];

	h_point1[0] = (float)start.x;
	h_point1[1]	= (float)start.y;
	h_point1[2]	= (float)start.z;

	h_point2[0] = (float)point.x;
	h_point2[1]	= (float)point.y;
	h_point2[2]	= (float)point.z;

	h_point3[0] = (float)end.x;
	h_point3[1]	= (float)end.y;
	h_point3[2]	= (float)end.z;		

	TK_Status hdwg_status; 
	TK_Circle					*circle_handler;
	circle_handler = new TK_Circle( TKE_Circular_Arc );
	circle_handler->SetStart( h_point1[0], h_point1[1], h_point1[2] );
	circle_handler->SetMiddle( h_point2[0], h_point2[1], h_point2[2] );
	circle_handler->SetEnd( h_point3[0], h_point3[1], h_point3[2]);
	hdwg_status = WriteObject(circle_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete circle_handler;

	//HC_KEY arc_key = HC_KInsert_Circular_Arc (h_point1,h_point2,h_point3);
	//if(m_pConnectivityInfo)
	//m_pConnectivityInfo->AddConnection(arc_key, (void*) pDatabaseEntity);

	return Adesk::kFalse;

}

Adesk::Boolean HDWG_BStreamImporter::import_polyline(	const Adesk::UInt32 nbPoints,
													 const AcGePoint3d* pVertexList,
													 const AcGeVector3d* pNormal,
													 Adesk::LongPtr lBaseSubEntMarker,
													 AcDbEntity* pDatabaseEntity) const
{
	if( !m_bDrawWireframe )
		return Adesk::kFalse;

	TK_Status hdwg_status; 

	if( nbPoints < 2 )
		return Adesk::kFalse;
	else if (nbPoints == 2)
	{
		if( pVertexList[0] != pVertexList[1] )
		{
			TK_Line	*line_handler;
			line_handler= new TK_Line();
			line_handler->SetPoints(pVertexList[0].x, pVertexList[0].y, pVertexList[0].z, 
				pVertexList[1].x, pVertexList[1].y, pVertexList[1].z);
			hdwg_status = WriteObject(line_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			delete line_handler;
		}
		else
		{
			//the Hatch pattern AR-SAND is a collection of lines with co-incident start and end point.
			//so,if points 0 and 1 in pVertexList are same we are inserting a marker (".") at that point - SumitK(10/06/08)

			//HC_Set_Marker_Symbol(marker_symbol);
			TK_Named *named_handler= new TK_Named(TKE_Marker_Symbol);
			int i = 0;
			for (i = 0; i < countof(marker_symbols); ++i)
			{
				if (streq (".", marker_symbols[i])) 
				{
					named_handler->SetIndex(i); 
					break;
				}
			}
			hdwg_status = WriteObject(named_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			delete named_handler;
			//HC_Insert_Marker(pVertexList[0].x, pVertexList[0].y, pVertexList[0].z);
			TK_Point* point_handler = new TK_Point(TKE_Marker);
			point_handler->SetPoint(pVertexList[0].x, pVertexList[0].y, pVertexList[0].z);
			hdwg_status = WriteObject(point_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			delete point_handler;
		}
	}
	else
	{
		float * h_points = new float[nbPoints*3];
		for (unsigned int i = 0; i < nbPoints; i++) 
		{
			h_points[i*3]		= (float)(pVertexList[i]).x;
			h_points[i*3 + 1]	= (float)(pVertexList[i]).y;
			h_points[i*3 + 2]	= (float)(pVertexList[i]).z;
		}

		TK_Polypoint	*line_handler;
		line_handler= new TK_Polypoint(TKE_Polyline);
		line_handler->SetPoints(nbPoints, h_points);
		hdwg_status = WriteObject(line_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);

		delete line_handler;
		delete[] h_points;
	}
	if (pDatabaseEntity->isKindOf(AcDb2dPolyline::desc()))
	{
		double polyline_thickness = 0.00;
		polyline_thickness = ((AcDb2dPolyline*)pDatabaseEntity)->thickness();

		if(polyline_thickness != 0.00)
		{
			HPoint h_line_norm;
			HPoint * polyline_pts = new HPoint[nbPoints];
			for(unsigned int i=0 ; i < nbPoints ; i++)
			{
				polyline_pts[i].x = pVertexList[i].x;
				polyline_pts[i].y = pVertexList[i].y; 
				polyline_pts[i].z = pVertexList[i].z; 
			}
			if( polyline_thickness < 0.0 )
			{
				h_line_norm.x = -pNormal->x;
				h_line_norm.y = -pNormal->y;
				h_line_norm.z = -pNormal->z;
			}
			else
			{
				h_line_norm.x = pNormal->x;
				h_line_norm.y = pNormal->y;
				h_line_norm.z = pNormal->z;
			}
			// extrude the profile

			extrude_profile_along_line(nbPoints, polyline_pts, &h_line_norm, polyline_thickness);
			delete []polyline_pts;
		}
	}

	return Adesk::kFalse;
}

Adesk::Boolean HDWG_BStreamImporter::import_polygon(const Adesk::UInt32 nbPoints,
													const AcGePoint3d* pVertexList,
													AcDbEntity* pDatabaseEntity
													) const
{
	float * h_points = new float[nbPoints*3];
	for (unsigned int i = 0; i < nbPoints; i++) 
	{
		h_points[i*3]	= (float)(pVertexList[i]).x;
		h_points[i*3+1]	= (float)(pVertexList[i]).y;
		h_points[i*3+2]	= (float)(pVertexList[i]).z;
	}

	TK_Status hdwg_status; 
	TK_Polypoint				*line_handler;
	line_handler= new TK_Polypoint(TKE_Polygon);
	line_handler->SetPoints(nbPoints, h_points);
	hdwg_status = WriteObject(line_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete line_handler;

	//HC_KEY key = HC_KInsert_Polygon (nbPoints, h_points);
	//if(m_pConnectivityInfo)
	//m_pConnectivityInfo->AddConnection(key, (void*) pDatabaseEntity);

	delete[] h_points;

	return Adesk::kFalse;
}
void HDWG_BStreamImporter::importAcDbLine(AcDbLine *pAcDbLine)
{
	AcGePoint3d start_point = pAcDbLine->startPoint();
	AcGePoint3d end_point = pAcDbLine->endPoint();
	double line_thickness = pAcDbLine->thickness();
	TK_Status hdwg_status;

	if(line_thickness != 0.00)
	{
		//Even if line has thickness its a planar entity and hence we need
		//to set the draworder to it - Mustafa Bohari 10-SEP-09
		//m_bIs2DEntity = false;
		HPoint * line_pts = new HPoint[2];
		line_pts[0].x = start_point.x;
		line_pts[0].y = start_point.y;
		line_pts[0].z = start_point.z;
		line_pts[1].x = end_point.x;
		line_pts[1].y = end_point.y;
		line_pts[1].z = end_point.z;

		AcGeVector3d acge_norm = pAcDbLine->normal();
		HPoint h_line_norm;
		if( line_thickness < 0.0 )
		{
			h_line_norm.x = -acge_norm.x;
			h_line_norm.y = -acge_norm.y;
			h_line_norm.z = -acge_norm.z;
		}
		else
		{
			h_line_norm.x = acge_norm.x;
			h_line_norm.y = acge_norm.y;
			h_line_norm.z = acge_norm.z;
		}
		// extrude the profile

		extrude_profile_along_line(2, line_pts, &h_line_norm, line_thickness);

		delete []line_pts;
	}
	else 
	{
		//HC_Insert_Line(start_point.x,start_point.y,start_point.z,end_point.x,end_point.y,end_point.z);
		TK_Line		*l_line_handler;
		l_line_handler = new TK_Line;
		l_line_handler->SetPoints((float)start_point.x,(float)start_point.y,(float)start_point.z, (float)end_point.x,(float)end_point.y,(float)end_point.z);
		hdwg_status = WriteObject(l_line_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete l_line_handler;
	}
}

void HDWG_BStreamImporter::importAcDbRay(AcDbRay* pRay)
{
	AcGePoint3d basepoint = pRay->basePoint();

	AcGeVector3d unitDir = pRay->unitDir();
	if(!(unitDir.isZeroLength()) )
	{
		TK_Status hdwg_status;
		TK_Line		*l_line_handler;
		l_line_handler = new TK_Line(TKE_Infinite_Ray);
		l_line_handler->SetPoints((float)basepoint.x,(float)basepoint.y,(float)basepoint.z, (float)(basepoint.x+unitDir.x),(float)(basepoint.y+unitDir.y),(float)(basepoint.z+unitDir.z));
		hdwg_status = WriteObject(l_line_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete l_line_handler;
	}
}

void HDWG_BStreamImporter::importAcDbXline(AcDbXline* pXline)
{
	AcGePoint3d basepoint = pXline->basePoint();

	AcGeVector3d unitDir = pXline->unitDir();
	if(!(unitDir.isZeroLength()) )
	{
		TK_Status hdwg_status;
		TK_Line		*l_line_handler;
		l_line_handler = new TK_Line(TKE_Infinite_Line);
		l_line_handler->SetPoints((float)basepoint.x,(float)basepoint.y,(float)basepoint.z, (float)(basepoint.x+unitDir.x),(float)(basepoint.y+unitDir.y),(float)(basepoint.z+unitDir.z));
		hdwg_status = WriteObject(l_line_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete l_line_handler;
	}
}
void HDWG_BStreamImporter::importAcDbViewport(AcDbViewport* pViewport)
{
	AcDbObjectId viewPortId = pViewport->objectId();

	if(m_bCleanVpList)
	{
		m_VpIdCount.clear();
		m_bCleanVpList = false;
	}

	if(!viewPortId.isNull())
	{
		m_VpIdCount.push_back(viewPortId);
	}
}

void HDWG_BStreamImporter::importAcDbRasterImage(AcDbRasterImage* pEnt)
{
	AcDbObjectId ImageID = pEnt->imageDefId();
	AcDbRasterImageDef * ImageDef = 0;
	acdbOpenObject(ImageDef, ImageID,  AcDb::kForRead);

	if(!ImageDef)
	{
		const wchar_t *p = pEnt->isA()->name();
		if(wcscmp(p, L"AcDbWipeout") == 0)
		{
			InsertMaskRegion(pEnt);
		}
		return;
	}

	char FilePath[MVO_BUFFER_SIZE]= "";
	char newimageName[MVO_BUFFER_SIZE] = "";

	int image_pesent = GetImageFileName(ImageDef, FilePath, newimageName);

	if(!image_pesent)
	{
		HAcGiWorldDraw hacgi_world_draw(this, pEnt);
		hacgi_world_draw.setRegenType(kAcGiHideOrShadeCommand);
		if(pEnt->worldDraw(&hacgi_world_draw)== Adesk::kFalse)
		{
			HAcGiViewportDraw hacgi_VP_draw(this, pEnt);
			pEnt->viewportDraw(&hacgi_VP_draw);				
		}

		return;
	}

	char imageFormat[MVO_BUFFER_SIZE];
	strcpy(imageFormat, "rgb");

	HC_KEY image_seg = HC_KCreate_Segment("/include library/DWG images");

	bool image_already_exists = false;
	//<< search whether this image has already been defined
	HC_KEY temp_image_key;
	char type[128];
	HC_Open_Segment_By_Key(image_seg);
	HC_Begin_Contents_Search(".", " images");
	while(HC_Find_Contents (type, &temp_image_key))
	{
		char temp_image_name[1024];
		HC_Show_Image_Name(temp_image_key, temp_image_name);
		if(stricmp(temp_image_name, newimageName) == 0)
		{
			image_already_exists = true;
			break;
		}
	}
	HC_End_Contents_Search ();
	HC_Close_Segment();
	//>> search whether this image has already been defined

	HC_KEY image_key;
	TK_Status hdwg_status;

	if(image_already_exists == false)
	{
		HInputHandler *image_reader = HDB::GetHIOManager()->GetInputHandler(H_ASCII_TEXT(ImageDef->fileType()));
		H_ASSERT(image_reader);

		HInputHandlerOptions options;
		options.m_pImageName = newimageName;
		options.m_pImageFormat = imageFormat;
		HFileInputResult result = InputFail;
		if(image_pesent)
		{
			result = image_reader->FileInputToImageKey(H_ASCII_TEXT(FilePath),
				&image_key, image_seg, &options );
		}

		H_ASSERT(result == InputOK );

	}
	else
		image_key = temp_image_key;

	char style_segment_name[1024];
	sprintf(style_segment_name, "/include library/Style Segment/%s", newimageName);

	if(image_already_exists == false)
	{
		STREAM_Open_Segment(style_segment_name);
		// query the image details from HOOPS
		TK_Image* image_handler = new TK_Image();
		fill_image_handler(image_key, *image_handler);
		hdwg_status = WriteObject(image_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete image_handler;

		TK_Texture	*texture_handler;
		texture_handler = new TK_Texture;
		texture_handler->SetFlags(0);
		texture_handler->SetName(H_ASCII_TEXT(newimageName));
		texture_handler->SetImage(H_ASCII_TEXT(newimageName));
		texture_handler->SetFlags( texture_handler->GetFlags() | TKO_Texture_Param_Source );	
		texture_handler->SetParameterSource(TKO_Texture_Param_Source_UV);

		//HC_Define_Local_texture(imageName, texture_def); 
		hdwg_status = WriteObject(texture_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete texture_handler;

		STREAM_Close_Segment();
	}
	ImageDef->close();

	TK_Color *color_handler;
	color_handler = new TK_Color;
	color_handler->SetGeometry( TKO_Geo_Face );
	color_handler->SetChannels( 1 << TKO_Channel_Diffuse ); 
	color_handler->SetDiffuseName( H_ASCII_TEXT(newimageName)  );
	hdwg_status = WriteObject(color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete color_handler;

	TK_Referenced_Segment *referenced_segment_handler;
	referenced_segment_handler = new TK_Referenced_Segment(TKE_Style_Segment);
	//referenced_segment_handler = new TK_Referenced_Segment(TKE_Include_Segment);
	referenced_segment_handler->SetSegment(style_segment_name);
	hdwg_status = WriteObject(referenced_segment_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete referenced_segment_handler;	

	// we don't need the image, we have serialized it now
	//HC_Delete_By_Key(image_key);

	// set visibility of images off
	STREAM_Set_Visibility(TKO_Geo_Image, false);

	// Insert clip region
	InsertClipRegion(pEnt,m_pBStreamtk);


	HPoint mesh_points[4];
	HPoint vcor[4];
	int index[6] = {5,0,1,2,3,0};

	Get_Image_Rectangle_For_Shell(pEnt, mesh_points);

	vcor[0].x = 0.0;    vcor[0].y = 0.0;    vcor[0].z = 0.0;
	vcor[1].x = 1.0;    vcor[1].y = 0.0;    vcor[1].z = 0.0;
	vcor[2].x = 1.0;    vcor[2].y = 1.0;    vcor[2].z = 0.0;
	vcor[3].x = 0.0;    vcor[3].y = 1.0;    vcor[3].z = 0.0;

	TK_Shell shell_handler;
	shell_handler.SetPoints(4, (float*)mesh_points);
	shell_handler.set_flist(6, index);
	shell_handler.SetVertexParameters((float*)vcor,3);
	hdwg_status = WriteObject(&shell_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);

}
#ifdef WIN32
void HDWG_BStreamImporter::importAcDbTable(AcDbTable* pAcDbTable)
{
	char parent_name[MVO_BUFFER_SIZE];
	sprintf(parent_name,"AcDbTable_%p",pAcDbTable);
	//table_key = HC_KOpen_Segment(parent_name);
	TK_Open_Segment				*open_seg_handler = NULL;
	TK_Status hdwg_status;
	open_seg_handler= new TK_Open_Segment;
	open_seg_handler->SetSegment(parent_name);
	hdwg_status = WriteObject(open_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);

	Acad::ErrorStatus err;
	AcDbVoidPtrArray table_element;
	err = pAcDbTable->explode(table_element);


	for(int i=0 ; i<table_element.length(); i++)
	{
		AcRxObject* this_element = (AcRxObject*)table_element[i];
		if( this_element->isKindOf(AcDbEntity::desc()) )
		{
			importAcDbEntity((AcDbEntity*) this_element,open_seg_handler);
		}
		delete this_element;
	}

	//HC_Close_Segment();
	TK_Close_Segment			*close_seg_handler ; 
	close_seg_handler = new TK_Close_Segment;
	hdwg_status = WriteObject(close_seg_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete open_seg_handler;
	delete close_seg_handler;
}
#endif

void HDWG_BStreamImporter::importAcDbMLeader(AcDbMLeader* pAcDbMLeader)
{
	char parent_name[MVO_BUFFER_SIZE];
	sprintf(parent_name,"AcDbMLeader_%p",pAcDbMLeader);
	TK_Open_Segment * open_seg_handler = new TK_Open_Segment;
	STREAM_Open_Segment(open_seg_handler, parent_name);

	Acad::ErrorStatus err;
	AcDbVoidPtrArray leader_element;
	err = pAcDbMLeader->explode(leader_element);
	for(int i=0;i<leader_element.length();i++)
	{
		AcRxObject* this_element = (AcRxObject*)leader_element[i];
		if( this_element->isKindOf(AcDbEntity::desc()))
			importAcDbEntity((AcDbEntity*) this_element, open_seg_handler);
		delete this_element;
	}
	STREAM_Close_Segment();
}

static inline float* HPoints_2_floats(const int& n_points, const HPoint* hpoints_array)
{
	float* floats_array = new float[n_points*3];
	for(int k = 0; k < n_points; k++)
	{
		floats_array[3*k]   = hpoints_array[k].x;
		floats_array[3*k+1] = hpoints_array[k].y;
		floats_array[3*k+2] = hpoints_array[k].z;
	}
	return floats_array;
}

void HDWG_BStreamImporter::extrude_profile_along_line(const int& nProfilePoints, 
													  const HPoint* pStartProfilePoints,
													  HPoint* pDirection, const int& nExtrudeLength) const
{
	// normalize direction
	HPoint p_unit_dir;
	HC_Compute_Normalized_Vector(pDirection, &p_unit_dir);

	// generate end profile points
	// duplicate the points for flat shading effect
	int total_points = 4*nProfilePoints;
	HPoint* shell_points = new HPoint[total_points];
	double dx = nExtrudeLength*p_unit_dir.x;
	double dy = nExtrudeLength*p_unit_dir.y;
	double dz = nExtrudeLength*p_unit_dir.z;
	for( int i = 0; i < nProfilePoints; i++ )
	{
		shell_points[4*i]   = pStartProfilePoints[i];
		shell_points[4*i+1] = pStartProfilePoints[i];

		shell_points[4*i+2].x = pStartProfilePoints[i].x + dx;
		shell_points[4*i+2].y = pStartProfilePoints[i].y + dy;
		shell_points[4*i+2].z = pStartProfilePoints[i].z + dz;

		shell_points[4*i+3] = shell_points[4*i+2];
	}

	int n_quads = nProfilePoints;
	int face_indices_length = 5*n_quads;
	int* face_indices = new int[face_indices_length];
	bool is_even = true;
	for( int j = 0; j < n_quads; j++ )
	{
		face_indices[5*j] = 4;

		if( is_even )
		{
			face_indices[5*j+1] = j*4+0;
			face_indices[5*j+2] = j*4+4;
			face_indices[5*j+3] = j*4+6;
			face_indices[5*j+4] = j*4+2;
		}
		else
		{
			face_indices[5*j+1] = j*4+1;
			face_indices[5*j+2] = j*4+5;
			face_indices[5*j+3] = j*4+7;
			face_indices[5*j+4] = j*4+3;
		}
		is_even = !is_even;
	}

	face_indices[face_indices_length-2] = 3;
	face_indices[face_indices_length-3] = 1;

	TK_Shell *shell_handler;
	shell_handler = new TK_Shell;
	shell_handler->SetPoints(total_points, (float*) shell_points);
	shell_handler->set_flist(face_indices_length, face_indices);
	TK_Status hdwg_status = WriteObject(shell_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
	H_ASSERT(hdwg_status == TK_Normal);
	delete shell_handler;

	H_SAFE_DELETE_ARRAY(face_indices);
	H_SAFE_DELETE_ARRAY(shell_points);

	// If you don't want the flat-shading effect by duplicating the points, this is probably
	// a more optimal solution - insert the shell as tristrips. You can use following as replacement.
#if 0
	// normalize direction
	HPoint p_unit_dir;
	HC_Compute_Normalized_Vector(pDirection, &p_unit_dir);

	// generate end profile points
	int total_points = 2*nProfilePoints;
	HPoint* shell_points = new HPoint[total_points];
	double dx = nExtrudeLength*p_unit_dir.x;
	double dy = nExtrudeLength*p_unit_dir.y;
	double dz = nExtrudeLength*p_unit_dir.z;
	for( int i = 0; i < nProfilePoints; i++ )
	{
		shell_points[2*i] = pStartProfilePoints[i];

		shell_points[2*i+1].x = pStartProfilePoints[i].x + dx;
		shell_points[2*i+1].y = pStartProfilePoints[i].y + dy;
		shell_points[2*i+1].z = pStartProfilePoints[i].z + dz;
	}

	int face_indices_length = 0;
	int* face_indices = new int[total_points+1];
	face_indices[0] = total_points;
	for( int j = 0; j < total_points; j++ )
		face_indices[j+1] = j;

	HC_KEY shell_key = HC_KInsert_Shell_By_tristrips ( total_points, shell_points,
		total_points+1, face_indices, 0, 0);

	H_SAFE_DELETE_ARRAY(face_indices);
	H_SAFE_DELETE_ARRAY(shell_points);

	return shell_key;
#endif

}


Adesk::Boolean HDWG_BStreamImporter::import_pline(const AcDbPolyline& lwBuf,
												  Adesk::UInt32 fromIndex,
												  Adesk::UInt32 numSegs,
												  AcDbEntity* pDatabaseEntity
												  ) const
{	
	if( !m_bDrawWireframe )
		return Adesk::kFalse;

	TK_Status hdwg_status; 
	// these are not yet supported by RealDWG toolkit
	if( fromIndex != 0 || numSegs != 0)
		return Adesk::kFalse;

	unsigned int n_verts = lwBuf.numVerts();
	if(n_verts < 1)
		return Adesk::kFalse;

	if( (lwBuf.isOnlyLines() == Adesk::kTrue) && (lwBuf.hasWidth() == Adesk::kFalse))
	{
		HPoint * polyline_pts = 0;
		if(lwBuf.isClosed())
			polyline_pts = new HPoint[n_verts+1];
		else
			polyline_pts = new HPoint[n_verts];

		for( unsigned int i = 0; i < n_verts; i++ )
		{
			AcGePoint3d i_pt;
			lwBuf.getPointAt(i, i_pt);
			polyline_pts[i].x = i_pt.x;
			polyline_pts[i].y = i_pt.y;
			polyline_pts[i].z = i_pt.z;
		}

		if(lwBuf.isClosed())
			polyline_pts[n_verts] = polyline_pts[0];

		HC_KEY key = NULL;
		// if you find a AcDbPolyline which is closed and should rather appear filled in HOOPS.
		// then you could try inserting a polygon
		//key = HC_KInsert_Polygon(n_verts, polyline_pts);
		double line_thickness = lwBuf.thickness();
		if( line_thickness == 0.0 )
		{
			int n_vert_count = n_verts;
			if(lwBuf.isClosed())
				n_vert_count++;

			TK_Polypoint *line_handler= new TK_Polypoint(TKE_Polyline);
			line_handler->SetPoints(n_vert_count, (float*)polyline_pts);
			hdwg_status = WriteObject(line_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete line_handler;
		}
		else
		{
			AcGeVector3d acge_norm = lwBuf.normal();
			HPoint h_line_norm;
			if( line_thickness < 0.0 )
			{
				h_line_norm.x = -acge_norm.x;
				h_line_norm.y = -acge_norm.y;
				h_line_norm.z = -acge_norm.z;
			}
			else
			{
				h_line_norm.x = acge_norm.x;
				h_line_norm.y = acge_norm.y;
				h_line_norm.z = acge_norm.z;
			}
			// extrude the profile
			if(lwBuf.isClosed())
				extrude_profile_along_line(n_verts+1, polyline_pts, &h_line_norm, line_thickness);
			else
				extrude_profile_along_line(n_verts, polyline_pts, &h_line_norm, line_thickness);
		}
		H_SAFE_DELETE_ARRAY(polyline_pts);
	}
	else
	{
		for( unsigned int i = 0; i < n_verts; i++ )
		{
			// opening a new segment for each element
			// because each of them may have a different line/marker thickness
			// The Optimize_Segment_tree will take care of this anyway
			//HC_Open_Segment("");

			TK_Open_Segment				*open_seg_handler = NULL;
			open_seg_handler= new TK_Open_Segment;
			open_seg_handler->SetSegment("");
			hdwg_status = WriteObject(open_seg_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete open_seg_handler;

			HC_KEY key = INVALID_KEY;
			// check the type of segment at ith vertex

			AcDbPolyline::SegType seg_type = lwBuf.segType(i);

			if( seg_type == AcDbPolyline::kLine )
			{
				AcGeLineSeg3d line_seg;
				lwBuf.getLineSegAt(i, line_seg);

				AcGePoint3d start_point = line_seg.startPoint();
				AcGePoint3d end_point = line_seg.endPoint();		

				//key = HC_KInsert_Line ((float)start_point.x,(float)start_point.y,(float)start_point.z,
				//(float)end_point.x,(float)end_point.y,(float)end_point.z);
				TK_Line		*l_line_handler;
				l_line_handler = new TK_Line;
				l_line_handler->SetPoints((float)start_point.x,(float)start_point.y,(float)start_point.z, (float)end_point.x,(float)end_point.y,(float)end_point.z);
				hdwg_status = WriteObject(l_line_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
				H_ASSERT(hdwg_status == TK_Normal);
				delete l_line_handler;
			}
			else if( seg_type == AcDbPolyline::kArc )
			{
				AcGeCircArc3d arc_seg;
				lwBuf.getArcSegAt(i, arc_seg);

				AcGePoint3d start_point = arc_seg.startPoint();
				AcGePoint3d end_point = arc_seg.endPoint();	
				AcGePoint3d center_point = arc_seg.center(); 

				double start_ang = arc_seg.startAng();
				double end_ang = arc_seg.endAng(); 

				AcGeVector3d normal = arc_seg.normal();
				AcGeVector3d ref_vec = arc_seg.refVec();
				AcGeVector3d y_vec = normal.crossProduct(ref_vec);

				double radius = arc_seg.radius();

				AcGeVector3d Wx(1, 0, 0);
				AcGeVector3d Wy(0, 1, 0);
				AcGeVector3d Wz(0, 0, 1);
				AcGeVector3d Ax,Ay,Az;
				Ax = ref_vec;
				Ay = y_vec;
				Az = normal;

				double cos_X_alpha = Wx.dotProduct(Ax);
				double cos_X_beta  = Wy.dotProduct(Ax);
				double cos_X_theta = Wz.dotProduct(Ax);

				float h_major[3];
				h_major[0] = (float) (center_point.x + radius*cos_X_alpha);
				h_major[1] = (float) (center_point.y + radius*cos_X_beta);
				h_major[2] = (float) (center_point.z + radius*cos_X_theta);


				double cos_Y_alpha = Wx.dotProduct(Ay);
				double cos_Y_beta  = Wy.dotProduct(Ay);
				double cos_Y_theta = Wz.dotProduct(Ay);

				float h_minor[3];
				h_minor[0] = (float) (center_point.x + radius*cos_Y_alpha);
				h_minor[1] = (float) (center_point.y + radius*cos_Y_beta);
				h_minor[2] = (float) (center_point.z + radius*cos_Y_theta);

				float h_center[3];
				h_center[0] = (float)center_point.x;
				h_center[1] = (float)center_point.y;
				h_center[2] = (float)center_point.z;


				float h_start_angle = (float)start_ang/(2.0f*HDWG_F_PI);
				float h_end_angle = (float)end_ang/(2.0f*HDWG_F_PI);

				if((start_ang == 0.0) && (end_ang == HDWG_PI) && (n_verts ==2))
				{
#ifdef HIODWG_tESSELLATE_CIRCLE_ELLIPSE_SURFS
					HC_Open_Segment(HIODWG_SCRATCH_SEGMENT);
					HC_KEY key = HC_KInsert_Ellipse(h_center, h_major, h_minor);
					HC_KEY shell_key = HC_Generate_Shell_From_Geometry(key, "");

					int nPointCount(0), nFaceListLength(0);
					float* pOriginalPoints = 0;
					int* pFaceList = 0;
					HC_Show_Shell_Size( shell_key, &nPointCount, &nFaceListLength );
					HC_Show_Geometry_Pointer( shell_key, "points", &pOriginalPoints);
					HC_Show_Geometry_Pointer( shell_key, "face list", &pFaceList );

					TK_Shell shell_handler;
					shell_handler.SetPoints(nPointCount, (float*)pOriginalPoints);
					shell_handler.set_flist(nFaceListLength, pFaceList);
					TK_Status hdwg_status = WriteObject(&shell_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
					H_ASSERT(hdwg_status == TK_Normal);

					HC_Flush_Segment(".");

					HC_Close_Segment();
#else
					//key = HC_KInsert_Ellipse (h_center,h_major,h_minor);
					TK_Ellipse	ellipse_handler(TKE_Ellipse); 
					ellipse_handler.SetCenter(h_center[0], h_center[1], h_center[2]);
					ellipse_handler.SetMajor (h_major);
					ellipse_handler.SetMinor (h_minor);
					hdwg_status = WriteObject(&ellipse_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
					H_ASSERT(hdwg_status == TK_Normal);
#endif
				}
				else 
				{
					//key = HC_KInsert_Elliptical_Arc (h_center,h_major,h_minor, h_start_angle,h_end_angle);
					TK_Ellipse	ellipse_handler(TKE_Elliptical_Arc); 
					ellipse_handler.SetCenter(h_center[0], h_center[1], h_center[2]);
					ellipse_handler.SetMajor (h_major);
					ellipse_handler.SetMinor (h_minor);
					ellipse_handler.SetLimits(h_start_angle, h_end_angle);
					hdwg_status = WriteObject(&ellipse_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
					H_ASSERT(hdwg_status == TK_Normal);
				}


			}
			else if( seg_type == AcDbPolyline::kPoint )
			{
				AcGePoint3d point3D;
				lwBuf.getPointAt(i,point3D);

				float h_point[3];

				h_point[0]  = (float)point3D.x;
				h_point[1]	= (float)point3D.y;
				h_point[2]	= (float)point3D.z;

				//key = HC_KInsert_Marker (h_point[0], h_point[1], h_point[2]);
				TK_Point	*point_handler;
				point_handler = new TK_Point(TKE_Marker);
				point_handler->SetPoint(h_point[0], h_point[1], h_point[2]);
				hdwg_status = WriteObject(point_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
				H_ASSERT(hdwg_status == TK_Normal);
				delete point_handler;
			}


			// Set the line weight.
			// TODO: Handle different start and end weights
			double start_width = 0.0;
			double end_width = 0.0;
			lwBuf.getWidthsAt(i, start_width, end_width);
			if((start_width == end_width) && (start_width != 0.0))
			{
				////start_width = start_width * (H_MM_TO_POINTS/100.0);
				////HC_Set_Line_Weight(start_width);
				//char element_size[MVO_BUFFER_SIZE];
				//sprintf(element_size,"%g wsu", start_width);

				//HC_Set_Variable_Edge_Weight(element_size);
				//HC_Set_Variable_Line_Weight(element_size);
				//HC_Set_Variable_Marker_Size(element_size);

				TK_Size	*size_handler;
				size_handler= new TK_Size(TKE_Edge_Weight);
				size_handler->SetSize(start_width,TKO_Generic_Size_World); 
				hdwg_status = WriteObject(size_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
				H_ASSERT(hdwg_status == TK_Normal);
				delete size_handler;

				size_handler= new TK_Size(TKE_Line_Weight);
				size_handler->SetSize(start_width,TKO_Generic_Size_World); 
				hdwg_status = WriteObject(size_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
				H_ASSERT(hdwg_status == TK_Normal);
				delete size_handler;

				size_handler= new TK_Size(TKE_Marker_Size);
				size_handler->SetSize(start_width,TKO_Generic_Size_World); 
				hdwg_status = WriteObject(size_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
				H_ASSERT(hdwg_status == TK_Normal);
				delete size_handler;
			}


			//if(m_pConnectivityInfo)
			//m_pConnectivityInfo->AddConnection(key, (void*) pDatabaseEntity);

			//HC_Close_Segment();
			TK_Close_Segment			*close_seg_handler ; 
			close_seg_handler = new TK_Close_Segment;
			hdwg_status = WriteObject(close_seg_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);
			delete close_seg_handler;

		}
	}

	return Adesk::kFalse;
}



Adesk::Boolean HDWG_BStreamImporter::import_mesh  (const Adesk::UInt32 rows,
												   const Adesk::UInt32 columns,
												   const AcGePoint3d* pVertexList,
												   const AcGiEdgeData* pEdgeData,
												   const AcGiFaceData* pFaceData,
												   const AcGiVertexData* pVertexData,
												   const bool bAutoGenerateNormals,
												   AcDbEntity* pDatabaseEntity
												   ) const
{
	unsigned int nbVertex = rows*columns;
	TK_Status hdwg_status; 
	float * h_points = new float[nbVertex*3];
	float *h_normals = 0;

	for (unsigned int i = 0; i < (nbVertex); i++) 
	{
		h_points[i*3]		= (float)(pVertexList[i]).x;
		h_points[i*3 + 1]	= (float)(pVertexList[i]).y;
		h_points[i*3 + 2]	= (float)(pVertexList[i]).z;
	}

	if(!bAutoGenerateNormals && pVertexData)
	{
		// let's grab some normal data too. For now, do only vertex normals
		AcGeVector3d * acge_vtx_normals = pVertexData->normals();

		// TODO: Use the orientation flag to determine the handedness
		h_normals = new float[nbVertex*3];
		for(unsigned int i = 0; i < nbVertex; i++)
		{
			h_normals[i*3]		= (float)(acge_vtx_normals[i]).x;
			h_normals[i*3 + 1]	= (float)(acge_vtx_normals[i]).y;
			h_normals[i*3 + 2]	= (float)(acge_vtx_normals[i]).z;
		}
	}

	if(!m_bDWGInsertMeshesAsShells)
	{
		TK_Mesh mesh_handler;
		mesh_handler.SetPoints(nbVertex, h_points);
		mesh_handler.SetRows(rows);
		mesh_handler.SetColumns(columns);
		if(h_normals)
			mesh_handler.SetVertexNormals(h_normals);
		hdwg_status = WriteObject(&mesh_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
	}
	else // convert the mesh in shell in case m_bDWGInsertMeshesAsShells variable is true
	{
		HC_KEY key = HC_KInsert_Mesh (rows, columns,h_points);
		if(h_normals)
			HC_MSet_Vertex_Normals(key, 0, nbVertex, h_normals);

		HC_KEY shell_key = HC_Generate_Shell_From_Geometry(key, "");
		// delete the mesh.
		HC_Delete_By_Key(key);

		int n_points, n_face_list_indices;
		HC_Show_Shell_Size(shell_key, &n_points, &n_face_list_indices);
		HPoint * face_points = new HPoint[n_points];
		int * index_list = new int[n_face_list_indices];
		HC_Show_Shell(shell_key, &n_points, face_points, &n_face_list_indices, index_list);
		// delete this shell which might not be optimized
		HC_Delete_By_Key(shell_key);

		// optimize the shell
		int n_opt_points, n_opt_face_list_indices;
		HPoint * opt_face_points = new HPoint[n_points];
		int * opt_index_list = new int[n_face_list_indices];

		HC_Compute_Optimized_Shell(n_points, face_points, 0, n_face_list_indices, index_list,
			"tolerance = 0.0001 oru",
			&n_opt_points, opt_face_points, &n_opt_face_list_indices, opt_index_list, 0, 0);

		// Insert Optimized shell

		TK_Shell *shell_handler;
		shell_handler = new TK_Shell;
		shell_handler->SetPoints(n_opt_points, (float*)opt_face_points);
		shell_handler->set_flist(n_opt_face_list_indices, opt_index_list);
		hdwg_status = WriteObject(shell_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete shell_handler;

		// delete allocated memories.
		delete [] face_points;
		delete [] index_list;
		delete [] opt_face_points;
		delete [] opt_index_list;
	}

	delete[] h_points;
	if(h_normals)
		delete[] h_normals;

	return Adesk::kFalse;
}

Adesk::Boolean HDWG_BStreamImporter::import_shell(const Adesk::UInt32 nbVertex,
												  const AcGePoint3d* pVertexList,
												  const Adesk::UInt32 faceListSize,
												  const Adesk::Int32* pFaceList,
												  const AcGiEdgeData* pEdgeData,
												  const AcGiFaceData* pFaceData ,
												  const AcGiVertexData* pVertexData,
												  const struct resbuf* pResBuf,
												  const bool bAutoGenerateNormals,
												  AcDbEntity* pDatabaseEntity
												  ) const

{
	//Face Count
	int faceCount = 0;
	unsigned int ii = 0;
	if(faceListSize)
	{
		while( ii < faceListSize)
		{
			faceCount++;
			ii = ii + pFaceList[ii] + 1;
		}
	}

	//Color per face
	float* rgb_colors = 0;
	if(pFaceData && faceCount)
	{
		short* colors = pFaceData->colors();
		if(colors)
		{
			rgb_colors = new float[faceCount*3];
			int counter = 0;
			for(int i = 0; i < faceCount; i++)
			{
				Adesk::UInt32 RGBM_byte = AcCmEntityColor::lookUpRGB(colors[i]);
				rgb_colors[counter] = (float) GetRValueFromRGBM(RGBM_byte)/255.0f;
				rgb_colors[counter+1] = (float) GetGValueFromRGBM(RGBM_byte)/255.0f;
				rgb_colors[counter+2] = (float) GetBValueFromRGBM(RGBM_byte)/255.0f;
				counter+=3;
			}
		}
	}


	float * h_points = new float[nbVertex*3];
	float *h_normals = 0;

	for (unsigned int i = 0; i < nbVertex; i++) 
	{
		h_points[i*3]		= (float)(pVertexList[i]).x;
		h_points[i*3 + 1]	= (float)(pVertexList[i]).y;
		h_points[i*3 + 2]	= (float)(pVertexList[i]).z;
	}

	// Check for color per vertex
	float * vertex_rgb_colors = 0;
	AcCmEntityColor * vertex_colors = 0;
	if(pVertexData && nbVertex)
	{
		vertex_colors = pVertexData->trueColors();
		if(vertex_colors)
		{
			vertex_rgb_colors = new float[nbVertex*3];
			Adesk::UInt8 r,g,b;

			for (unsigned int i = 0; i < nbVertex; i++) 
			{
				r = vertex_colors[i].red();
				g = vertex_colors[i].green();
				b = vertex_colors[i].blue();

				vertex_rgb_colors[i*3]		= (float) r/ 255.0;
				vertex_rgb_colors[i*3 + 1]	= (float) g/ 255.0;
				vertex_rgb_colors[i*3 + 2]	= (float) b/ 255.0;
			}
		}
	}

	int * h_facelist = new int[faceListSize];
	for (unsigned int k = 0; k < faceListSize; k++)
	{
		h_facelist[k] = (*pFaceList);
		++pFaceList;
	}

	if(!bAutoGenerateNormals && pVertexData)
	{
		// let's grab some normal data too. For now, do only vertex normals
		AcGeVector3d * acge_vtx_normals = pVertexData->normals();

		if(acge_vtx_normals)
		{
			// TODO: Use the orientation flag to determine the handedness
			h_normals = new float[nbVertex*3];
			for(unsigned int i = 0; i < nbVertex; i++)
			{
				h_normals[i*3]		= (float)(acge_vtx_normals[i]).x;
				h_normals[i*3 + 1]	= (float)(acge_vtx_normals[i]).y;
				h_normals[i*3 + 2]	= (float)(acge_vtx_normals[i]).z;
			}
		}
	}

	TK_Status hdwg_status; 
	if(!m_bScratchSegOpen) // This also takes care of m_bMergeEntityShells in ImportAcDbEntity
	{
		TK_Shell *shell_handler;
		shell_handler = new TK_Shell;
		shell_handler->SetPoints(nbVertex, h_points);
		shell_handler->set_flist(faceListSize, h_facelist);
		if(rgb_colors)
		{
			shell_handler->SetFaceColors(rgb_colors);
			delete[] rgb_colors;
		}
		if(vertex_colors)
		{
			shell_handler->SetVertexColors(vertex_rgb_colors);
		}
		if(h_normals)
			shell_handler->SetVertexNormals(h_normals);
		hdwg_status = WriteObject(shell_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete shell_handler;
	}
	else
	{
		/*if(!m_bScratchSegOpen) 
		HC_Open_Segment(HIODWG_SCRATCH_SEGMENT);*/ //REMOVE LATER

		HC_KEY shell_key = HC_KInsert_Shell (nbVertex, h_points, faceListSize,h_facelist);
		if(rgb_colors)
		{
			HC_MSet_Face_Colors_By_Value(shell_key, "faces", 0, "rgb", faceCount, rgb_colors);
			m_bShellWithFaceColor = true;
			delete[] rgb_colors;
		}
		if(vertex_colors)
		{
			HC_MSet_Vertex_Colors_By_Value(shell_key, "faces",  0, "rgb", nbVertex, vertex_rgb_colors);
			m_bShellWithFaceColor = true;
			delete[] vertex_rgb_colors;
		}
		if(h_normals)
			HC_MSet_Vertex_Normals(shell_key, 0, nbVertex, h_normals);
		/*if(!m_bScratchSegOpen)
		HC_Close_Segment();*/ //REMOVE LATER
	}

	delete[] h_points;
	delete[] h_facelist;
	if(h_normals)
		delete[] h_normals;


	return Adesk::kFalse;
}

Adesk::Boolean HDWG_BStreamImporter::import_text  (const AcGePoint3d& position,
												   const AcGeVector3d& normal,
												   const AcGeVector3d& direction,
												   const double height,
												   const double width,
												   const double oblique,
												   const ACHAR* pMsg,
												   AcDbEntity* pDatabaseEntity
												   ) const
{	

	//// #9535 : we are getting pMsg as a empty string from world draw, these strings are having very weird values of position 
	//// which further locks the camera operation.we are not going to import such empty text strings - Sumitk[12/10/2008]
	if(wcscmp(pMsg,L"") == 0)
	{
		return Adesk::kFalse;
	}

	//<< This check is to identify if the string is empty
	// Provided as a fix for issue - 10427.
	// some files may have empty strings, autoCAD ignores them while FitToScreen, 
	// but hoops doesn't. This makes FitToScreen in hoops look different than AutoCAD.
	// By ignoring the empty (with all spaces too) strings we can fix this.
	int i = 0;
	bool is_empty = false;
	while(pMsg[i])
	{
		if(pMsg[i] == L' ')
			is_empty = true;
		else
		{
			is_empty = false;
			break;
		}
		i++;
	}

	if(is_empty)
		return Adesk::kFalse;
	//>>

	float h_text_dir[3];
	h_text_dir[0]  = (float)direction.x;
	h_text_dir[1]  = (float)direction.y;
	h_text_dir[2]  = (float)direction.z;

	float h_normal[3];
	h_normal[0]  = (float)normal.x;
	h_normal[1]	 = (float)normal.y;
	h_normal[2]	 = (float)normal.z;

	float h_point1[3];
	h_point1[0] = (float)position.x;
	h_point1[1]	= (float)position.y;
	h_point1[2]	= (float)position.z;

	int alignment_index;
	double dtext_width=1.0;
	alignment_index = TKO_Text_Alignment_Middle_Center;
	AcDbText * pAcDbText=(AcDbText*)pDatabaseEntity;
	if( pDatabaseEntity && (pDatabaseEntity->isKindOf(AcDbText::desc())) )
	{
		get_text_alignment(pAcDbText,&alignment_index);
		dtext_width=pAcDbText->widthFactor();
	}

	HC_KEY key ;
	//import_text(h_point1, h_text_dir, h_normal, pMsg,alignment_index);

	// Transforms are handled generically (for planes other than XY) in this function. 
	// Beta << ASHISH.S. 17/08/2009.
	key = apply_transforms_and_insert_text(h_point1, h_text_dir, h_normal, pMsg,alignment_index);

	return Adesk::kFalse;
}

Adesk::Boolean HDWG_BStreamImporter::import_text(	const AcGePoint3d& position,
												 const AcGeVector3d& normal,
												 const AcGeVector3d& direction,
												 const ACHAR* pMsg,
												 const Adesk::LongPtr length,
												 const Adesk::Boolean raw,
												 const AcGiTextStyle &pTextStyle,
												 AcDbEntity* pDatabaseEntity
												 ) const
{
	//// #9535 : we are getting pMsg as a empty string from world draw, these strings are having very weird values of position 
	//// which further locks the camera operation.we are not going to import such empty text strings - Sumitk[12/10/2008]
	if(wcscmp(pMsg,L"") == 0)
	{
		return Adesk::kFalse;
	}

	//<< This check is to identify if the string is empty
	// Provided as a fix for issue - 10427.
	// some files may have empty strings, autoCAD ignores them while FitToScreen, 
	// but hoops doesn't. This makes FitToScreen in hoops look different than AutoCAD.
	// By ignoring the empty (with all spaces too) strings we can fix this.
	int i = 0;
	bool is_empty = false;
	while(pMsg[i])
	{
		if(pMsg[i] == L' ')
			is_empty = true;
		else
		{
			is_empty = false;
			break;
		}
		i++;
	}

	if(is_empty)
		return Adesk::kFalse;
	//>>

	// We are waiting for ADN's response on this one on how to get the font name - Pavan T. (20-Mar-06)
	TK_Status hdwg_status; 
	float h_text_dir[3];
	h_text_dir[0]  = (float)direction.x;
	h_text_dir[1]  = (float)direction.y;
	h_text_dir[2]  = (float)direction.z;

	float h_normal[3];
	h_normal[0]  = (float)normal.x;
	h_normal[1]	 = (float)normal.y;
	h_normal[2]	 = (float)normal.z;

	Adesk::Boolean bold = Adesk::kFalse;
	Adesk::Boolean italic = Adesk::kFalse;
	wchar_t *pTypeface = 0;
	int charset, pitch_family;
	float text_size;
	const wchar_t *pStyleName = 0;

	const wchar_t *pFileName = pTextStyle.fileName();
	wchar_t font_ext[24] = L"";
	if(pFileName) // pFileName is null, below function crashes.
		HUtility::FindFileNameExtension(pFileName, font_ext, 24);
	if(wcscmp(font_ext, L"shx") == 0)
		((HDWG_BStreamImporter*)this)->m_bIsSHXFont = true;

	Acad::ErrorStatus es = pTextStyle.font(pTypeface, bold, italic, charset, pitch_family);

	text_size = pTextStyle.textSize();

	// HACK ALERT: This adjustment seems to make the text appear in almost same size in HOOPS as in DWG
	// Until we know for sure how to access DWG font info - Pavan Totala (04-Apr-06)
	if(text_size > 0.220000)
		text_size=text_size-0.0700000;

	pStyleName = pTextStyle.styleName();
	//HC_Open_Segment("");
	STREAM_Open_Segment("");
	{
		wchar_t * pHText = 0;
		if( length != -1 )
		{
			pHText = new wchar_t[length+10];
			wcsncpy(pHText, pMsg, length);
			pHText[length] = L'\0';
		}
		else
		{
			size_t len = wcslen(pMsg);
			pHText = new wchar_t[len+1];
			wcsncpy(pHText, pMsg, len);
			pHText[len] = L'\0';
		}

		// About the text insertion. This is the information from AutoDesk RealDWG guide.

		// If vertical mode is AcDb::kTextBase and horizontal mode is either AcDb::kTextLeft, 
		// AcDb::kTextAlign, or AcDb::kTextFit, then the position point (DXF group code 10) 
		// is the insertion point for the text object and, for AcDb::kTextLeft, the alignment point 
		// is automatically calculated based on the other parameters in the text object.
		// For all other vertical and horizontal mode combinations, the alignment point is used as the 
		// insertion point of the text and the position point is automatically calculated based on the other 
		// parameters in the text object.

		float h_point1[3];
		h_point1[0] = (float)position.x;
		h_point1[1]	= (float)position.y;
		h_point1[2]	= (float)position.z;

		int alignment_index = TKO_Text_Alignment_Lower_Left;
		double dtext_width=1.0;	
		// we can only set the insertion point correct, if we have access to AcDbText interface
		if( pDatabaseEntity && (pDatabaseEntity->isKindOf(AcDbText::desc())) )
		{
			AcDbText* pAcDbText = (AcDbText*)pDatabaseEntity;
			AcDb::TextVertMode vert_mode = pAcDbText->verticalMode();
			AcDb::TextHorzMode hort_mode = pAcDbText->horizontalMode();

			if( !( (vert_mode == AcDb::kTextBase) && 
				( (hort_mode == AcDb::kTextLeft) || (hort_mode == AcDb::kTextAlign) || (hort_mode == AcDb::kTextFit) )
				)
				)
			{
				AcGePoint3d align = pAcDbText->alignmentPoint();
				h_point1[0]  = (float)align.x;
				h_point1[1]	 = (float)align.y;
				h_point1[2]	 = (float)align.z;
			}
			get_text_alignment(pAcDbText,&alignment_index);
			dtext_width=pAcDbText->widthFactor();
		}

		//import_text(h_point1, h_text_dir, h_normal, pHText,alignment_index);

		// Transforms are handled generically (for planes other than XY) in this function. 
		//Beta << ASHISH.S. 17/08/2009.
		apply_transforms_and_insert_text(h_point1, h_text_dir, h_normal, pHText,alignment_index);

		//if(m_pConnectivityInfo)
		//m_pConnectivityInfo->AddConnection(key, (void*) pDatabaseEntity);

		/*char txt_opts[4096];
		if(pTypeface && wcscmp(pTypeface,L"")))
		sprintf(txt_opts, "name = %s", H_ASCII_tEXT(pTypeface));
		else if(pStyleName && (wcscmp(pStyleName,L""))))
		sprintf(txt_opts, "name = %s", H_ASCII_tEXT(pStyleName));
		else
		sprintf(txt_opts, "name = system default");*/
		//HC_Set_text_Font(txt_opts);
		TK_Text_Font				*text_font_handler;
		text_font_handler= new TK_Text_Font();
		text_font_handler->SetMask(0);

		if(dtext_width != 1.0f)
		{
			//char h_wscale[MVO_BUFFER_SIZE];
			//sprintf(h_wscale, "width scale = %f", (float)pAcDbMTextFragment->widthFactor);
			//HC_Set_text_Font(h_wscale);
			text_font_handler->SetMask(text_font_handler->GetMask() | TKO_Font_Width_Scale);
			text_font_handler->SetValue(text_font_handler->GetValue() | TKO_Font_Width_Scale);
			text_font_handler->SetWidthScale ((float)dtext_width);
		}

		//text_font_handler->SetMask(TKO_Font_Names);
		text_font_handler->SetMask(text_font_handler->GetMask() | TKO_Font_Names);
		text_font_handler->SetValue(text_font_handler->GetValue() | TKO_Font_Names);

		if(((HDWG_BStreamImporter*)this)->m_bIsSHXFont)
		{
			wchar_t font_name[24] = L"";
			unsigned int  i = 0;
			wchar_t dot[2] = L".";
			wchar_t str[2] = L"";
			unsigned int len = wcslen(pFileName);
			while(i <= (len - 1))
			{
				str[0] = pFileName[i];
				if(wcscmp(str, dot) == 0)
					break;
				font_name[i] = pFileName[i];
				i++;
			}
			text_font_handler->SetNames (H_ASCII_TEXT(font_name));

			//HC_Set_Text_Font("preference=(smaller = vector, larger = default, cutoff = 0.1 sru)");
			TK_Text_Font text_font_handler;
			text_font_handler.SetMask(TKO_Font_Preference);
			text_font_handler.SetValue(TKO_Font_Preference);
			text_font_handler.SetPreferences(TKO_Font_Preference_Exterior, TKO_Font_Preference_Default);
			text_font_handler.SetPreferenceCutoff(0.1f);
			text_font_handler.SetPreferenceCutoffUnits(TKO_Font_Size_Screen);
			hdwg_status = WriteObject(&text_font_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
			H_ASSERT(hdwg_status == TK_Normal);

		}
		else if(pTypeface && wcscmp(pTypeface,L""))
			text_font_handler->SetNames (H_ASCII_TEXT(pTypeface));
		else if(pStyleName && (wcscmp(pStyleName,L"")))
			text_font_handler->SetNames (H_ASCII_TEXT(pStyleName));
		else
			text_font_handler->SetNames ("system default");

		if(text_size > 0)
		{
			//sprintf(txt_opts, "size = %f oru", text_size);
			//HC_Set_text_Font(txt_opts);
			text_font_handler->SetMask(text_font_handler->GetMask() | TKO_Font_Size);
			text_font_handler->SetValue(text_font_handler->GetValue() | TKO_Font_Size);
			text_font_handler->SetSizeUnits(TKO_Font_Size_Object);
			text_font_handler->SetSize (text_size);
		}
		if( bold == Adesk::kTrue )
		{
			//HC_Set_text_Font("bold");
			text_font_handler->SetMask (text_font_handler->GetMask() | TKO_Font_Bold );
			text_font_handler->SetValue(text_font_handler->GetValue() | TKO_Font_Bold);
		}
		if( italic == Adesk::kTrue)
		{
			//HC_Set_text_Font("italic");
			text_font_handler->SetMask(text_font_handler->GetMask() |TKO_Font_Italic);
			text_font_handler->SetValue(text_font_handler->GetValue() | TKO_Font_Italic);
		}

		text_font_handler->SetMask(text_font_handler->GetMask() | TKO_Font_Transforms );
		text_font_handler->SetValue(text_font_handler->GetValue() | TKO_Font_Transforms);
		text_font_handler->SetTransforms(TKO_Font_Transform_Full);

		hdwg_status = WriteObject(text_font_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete text_font_handler;

		H_SAFE_DELETE_ARRAY(pHText);
	}
	//HC_Close_Segment();
	STREAM_Close_Segment();

	//	if(pTypeface)
	//		delete pTypeface;

	// reset m_bIsSHXFont to false
	((HDWG_BStreamImporter*)this)->m_bIsSHXFont = false;

	return Adesk::kFalse;
}

HC_KEY HDWG_BStreamImporter::apply_transforms_and_insert_text(float my_center[], float my_path1[], float my_norm1[], wchar_t const * text, const int alignment_index ) const
{
	//<< This check is to identify if the string is empty
	// Provided as a fix for issue - 10427.
	// some files may have empty strings, autoCAD ignores them while FitToScreen, 
	// but hoops doesn't. This makes FitToScreen in hoops look different than AutoCAD.
	// By ignoring the empty (with all spaces too) strings we can fix this.
	int i = 0;
	bool is_empty = false;
	while(text[i])
	{
		if(text[i] == L' ')
			is_empty = true;
		else
		{
			is_empty = false;
			break;
		}
		i++;
	}

	if(is_empty)
		return 0;
	//>>

	static float h_matrix_trans[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
	GetModelingMatrixForText(my_center, my_path1, my_norm1, h_matrix_trans);

	// Check for special chars like degree, diameter symbols, and replace
	// with equivalent ascii values.
	wchar_t* local_text = new wchar_t[wcslen(text)+1];
	swprintf(local_text,L"%s",text);
	if(wcsstr(local_text,L"%%"))
		condition_string_for_special_characters(local_text);

	TK_Status hdwg_status; 
	HC_KEY text_key = INVALID_KEY;
	//HC_Open_Segment("");
	STREAM_Open_Segment("");
	{
		/*HC_Set_text_Font("transforms");
		HC_Rotate_Object(xrot, yrot, zrot);
		HC_translate_Object(my_center[0], my_center[1], my_center[2]);
		HC_Set_text_Alignment("**");*/

		TK_Text_Font text_font_handler1;
		text_font_handler1.SetMask(TKO_Font_Transforms );
		text_font_handler1.SetValue(TKO_Font_Transforms);
		text_font_handler1.SetTransforms(TKO_Font_Transform_Full);
		hdwg_status = WriteObject(&text_font_handler1,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);

		//HC_Set_Text_Font("preference=(smaller = vector, larger = default, cutoff = 0.02 oru)");
		TK_Text_Font text_font_handler;
		text_font_handler.SetMask(TKO_Font_Preference);
		text_font_handler.SetValue(TKO_Font_Preference);
		text_font_handler.SetPreferences(TKO_Font_Preference_Exterior, TKO_Font_Preference_Default);
		if(m_bIsSHXFont == true)
			text_font_handler.SetPreferenceCutoff(0.1f);
		else
			text_font_handler.SetPreferenceCutoff(0.04f);

		text_font_handler.SetPreferenceCutoffUnits(TKO_Font_Size_Screen);
		hdwg_status = WriteObject(&text_font_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);


		// Set the result matrix.
		TK_Matrix					*matrix_handler;
		matrix_handler = new TK_Matrix(TKE_Modelling_Matrix);
		matrix_handler->SetMatrix(h_matrix_trans);
		hdwg_status = WriteObject(matrix_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete matrix_handler;

		// what if this is a real UNICODE text?
		//text_key = HC_KInsert_text(0,0,0, H_ASCII_tEXT(text));
		TK_Text		*text_handler;
		text_handler= new TK_Text(TKE_Text_With_Encoding);
		text_handler->SetString((unsigned short const*)H_UTF16(local_text).encodedText());
		text_handler->SetPosition(0, 0, 0);
		hdwg_status = WriteObject(text_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete text_handler;

		TK_Enumerated	*enumerated_handler;
		enumerated_handler= new TK_Enumerated(TKE_Text_Alignment);
		enumerated_handler->SetIndex(alignment_index); 
		WriteObject(enumerated_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		delete enumerated_handler;

	}
	//HC_Close_Segment();
	STREAM_Close_Segment();

	H_SAFE_DELETE_ARRAY(local_text);
	return text_key;
}
void HDWG_BStreamImporter::importAcDbDimension(AcDbDimension* pAcDbDimension)
{
	// get the block table record which contains the entities this dimension displays
	AcDbObjectId blockId = pAcDbDimension->dimBlockId();
	AcDbBlockTableRecord *pRecord = 0;
	acdbOpenObject(pRecord, blockId, AcDb::kForRead);
	if(pRecord)
	{
		AcDbBlockTableRecordIterator *pRecordIter;
		if (pRecord->newIterator(pRecordIter) == Acad::eOk)
		{
			AcDbEntity *pEnt;
			while (!pRecordIter->done())
			{
				if (pRecordIter->getEntity(pEnt, AcDb::kForRead) == Acad::eOk)
				{
					// NOTE: Do not import AcDbPoint from dimension objects. The problem is
					// these points in dimensions don't seem to follow PDMODE and PDSIZE settings
					// and I couldn't figure out what determines their shape and size.
					// Since we were ignoring points anyway, I think it should be just fine - Rajesh B (05-Jun-08)
					if (pEnt->isA() != AcDbPoint::desc())
						importAcDbEntity(pEnt);
					pEnt->close();
				}
				pRecordIter->step();
			}                            
			delete pRecordIter;
		}
		pRecord->close();
	}
}
void HDWG_BStreamImporter::import_entity_linetype(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord)
{
	AcDbDatabase* pDatabase = acdbHostApplicationServices()->workingDatabase();
	H_ASSERT(pDatabase);

	AcDbObjectId line_type_id = pEnt->linetypeId();

	// If the line type is by block, then just ignore it.
	// Because we know that in that case it is going to be inherited
	if(line_type_id == pDatabase->byBlockLinetype())
		return;

	if( line_type_id == pDatabase->byLayerLinetype())
	{
		if (pLayerTableRecord)
		{
			line_type_id = pLayerTableRecord->linetypeObjectId();
		}
	}

	double linetype_scale = pEnt->linetypeScale() * m_dGlobalScaleFactor;

	if(line_type_id != pDatabase->continuousLinetype())
		import_entity_linetype(line_type_id, linetype_scale);

}

void HDWG_BStreamImporter::import_entity_linetype(const AcDbObjectId& pLinetypeId, double linetype_scale)
{
	AcDbLinetypeTableRecord  *pLineTypeTableRecord = 0;
	Acad::ErrorStatus es = acdbOpenObject(pLineTypeTableRecord, pLinetypeId, AcDb::kForRead);
	if( es == Acad::eOk && pLineTypeTableRecord)
	{
		int count = pLineTypeTableRecord->numDashes();
		if( count <= 0 )
		{
			// nothing to import?
			pLineTypeTableRecord->close();
			return;
		}

		char linestyle[MVO_BUFFER_SIZE];
		strcpy(linestyle,"");
		for (int i=0; i < count; i++)
		{
			double dash_length=pLineTypeTableRecord->dashLengthAt(i)* linetype_scale;

			if(dash_length == 0.0)
				dash_length = 1.0;

			if (dash_length > 0.0)
			{
				if (dash_length == 1)
				{
					//If length of the dash is one then we insert it as one pixel as this prevents 
					//dot to become line if zoomed in which matches behavior of AutoCAD : Mustafa Bohari
					sprintf(linestyle,"%s1 pixel dash,",linestyle);
				}
				else
				{
					sprintf(linestyle,"%s%lf oru dash,",linestyle,dash_length);
				}
			}
			else
			{
				sprintf(linestyle,"%s%lf oru blank,",linestyle,abs(dash_length));
			}

		}

		const ACHAR* line_type_name = 0;
		pLineTypeTableRecord->getName(line_type_name);
		size_t len=strlen(linestyle);
		TK_Status hdwg_status;
		linestyle[len-1]='\0';

		//HC_Define_Line_Style(H_ASCII_tEXT(line_type_name), linestyle);
		TK_Line_Style *line_style_handler;
		line_style_handler = new TK_Line_Style();
		line_style_handler->SetName((char *)line_type_name);
		line_style_handler->SetDefinition(linestyle);
		hdwg_status = WriteObject(line_style_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete line_style_handler;

		//HC_Set_Line_Pattern(H_ASCII_tEXT(line_type_name));
		TK_Named  *named_handler;
		named_handler= new TK_Named(TKE_Line_Pattern);
		named_handler->SetName((char*)line_type_name);
		WriteObject(named_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		delete named_handler;
		pLineTypeTableRecord->close();
	} 
}

void HDWG_BStreamImporter::InsertMaskRegion(AcDbRasterImage* pEnt)
{
	if(pEnt->isClipped())
	{
		int length;
		AcGePoint3dArray vertices;
		pEnt->getVertices(vertices);

		length = vertices.length();
		HPoint * MaskRegionPts = new HPoint[length];

		for ( int i=0; i<length; i++ )
		{
			MaskRegionPts[i].Set(vertices.at(i).x, vertices.at(i).y, vertices.at(i).z);
		}

		// Insert polygon as mask.
		// Ideal solution will be to insert same color polygon as the color of background.
		// For now adding white pilygon

		TK_Status hdwg_status; 
		// set color
		float clr[3] = {1.0, 1.0, 1.0};
		TK_Color	*color_handler;
		color_handler = new TK_Color();
		color_handler->SetGeometry (TKO_Geo_Edge|TKO_Geo_Face);
		color_handler->SetDiffuse(clr);
		//color_handler->SetTransmission(0.0, 1.0, 0.0);
		hdwg_status = WriteObject(color_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete color_handler;

		// set visibility
		TK_Visibility	*vis_handler = new TK_Visibility();
		vis_handler->SetGeometry(TKO_Geo_Edge|TKO_Geo_Face);
		vis_handler->SetValue(1);
		hdwg_status = WriteObject(vis_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete vis_handler;


		TK_Polypoint * line_handler;
		line_handler= new TK_Polypoint(TKE_Polygon);
		line_handler->SetPoints(length, (float *)MaskRegionPts);
		hdwg_status = WriteObject(line_handler,m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete line_handler;

		TK_Heuristics* heuristic_handler = new TK_Heuristics;
		heuristic_handler->SetMask( TKO_Heuristic_Concave_Polygons);
		heuristic_handler->SetValue(TKO_Heuristic_Concave_Polygons);
		hdwg_status = WriteObject(heuristic_handler, m_pBStreamtk, m_pHSFFile, m_pBStreamBuffer, m_nBStreamBuffSize);
		H_ASSERT(hdwg_status == TK_Normal);
		delete heuristic_handler;
	}
}


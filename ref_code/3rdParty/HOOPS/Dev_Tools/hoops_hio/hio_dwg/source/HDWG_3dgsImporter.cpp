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

#include <ctype.h>
// HDWGHelper.CPP
#include "hcd.h"
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

#include "dbacis.h"
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
#include "dbgroup.h"
#include "dbdict.h"
#include "dblayout.h"
#include "dbspfilt.h" 
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
//#include <time.h>
//#include <ctime>
//#include <wchar.h>

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

//returns the segment key of the block table record segment which contains/should contain
// this entity. The segment will be created if it doesn't exist
//static HC_KEY GetBlockTableRecordSegmentFromId(const AcDbObjectId& blockTableRecordID, bool& isNew, const wchar_t* lay_name)
//{
//	HC_KEY ret_segment_key = INVALID_KEY;
//
//	AcDbBlockTableRecord *pBlockTableRecord = 0;
//	Acad::ErrorStatus es = acdbOpenObject(pBlockTableRecord, blockTableRecordID, AcDb::kForRead);
//	if (pBlockTableRecord)
//	{
//		char segment_name[MVO_BUFFER_SIZE];
//		wchar_t *blockName;
//		wchar_t bName[MVO_BUFFER_SIZE];
//
//		pBlockTableRecord->getName(blockName);
//		wcscpy(bName, blockName);
//		condition_string_for_segment_name(bName);
//		acdbFree(blockName);
//
//		if((wcsicmp(L" Model_Space", (bName)) == 0) && (lay_name))
//		{
//			wchar_t temp[MVO_BUFFER_SIZE];
//			swprintf(temp, MVO_BUFFER_SIZE, L"btable_%p_%ls", pBlockTableRecord, (bName));
//			sprintf(segment_name, "/include library/other block table records/model space/%s", H_ASCII_TEXT(temp));
//		}
//		else
//		{
//			if(lay_name)
//			{
//				wchar_t LName[MVO_BUFFER_SIZE];
//				wcscpy(LName, lay_name);
//				condition_string_for_segment_name(LName);
//
//				sprintf(segment_name, "btable_%p_%s", pBlockTableRecord, H_ASCII_TEXT(LName));
//			}
//			else
//			{
//				sprintf(segment_name, "btable_%p_%s", pBlockTableRecord, H_ASCII_TEXT(bName));
//			}
//		}
//
//		int count = 0;
//		HC_Begin_Segment_Search(segment_name);
//			HC_Show_Segment_Count(&count);
//		HC_End_Segment_Search();
//
//		if( count == 0 )
//			isNew = true;
//
//		ret_segment_key = HC_KOpen_Segment(segment_name);
//		HC_Close_Segment();
//
//		pBlockTableRecord->close();
//	}
//
//	return ret_segment_key;
//}
HC_KEY HDWG_3dgsImporter::GetBlockTableRecordSegmentFromId(const AcDbObjectId& blockTableRecordID, bool& isNew)
{
	HC_KEY ret_segment_key = INVALID_KEY;

	AcDbBlockTableRecord *pBlockTableRecord = 0;
	Acad::ErrorStatus es = acdbOpenObject(pBlockTableRecord, blockTableRecordID, AcDb::kForRead);

	// For performance
	m_keymap_ieterator = m_Segments_map.find (pBlockTableRecord);
	if(m_keymap_ieterator != m_Segments_map.end()) 
	{
		pBlockTableRecord->close();
		return m_keymap_ieterator->second;
	}
	//
	if (pBlockTableRecord)
	{
		wchar_t segment_name[MVO_BUFFER_SIZE];
		wchar_t *blockName;
		wchar_t bName[MVO_BUFFER_SIZE];

		pBlockTableRecord->getName(blockName);
		wcscpy(bName, blockName);
		condition_string_for_segment_name(bName);
		acdbFree(blockName);

		if((wcsicmp(L"Model_Space", (bName)) == 0) && m_listDWGLayouts)
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
					// Must be some blockref with "Paper_Space" string in it's name.In case somebody is crash testing. 
					swprintf(segment_name, MVO_BUFFER_SIZE, L"btable_%p_%ls", pBlockTableRecord, (bName));

			}
			else
			{
				// You will find the execution visiting this place more often than any of above statements.
				swprintf(segment_name, MVO_BUFFER_SIZE, L"btable_%p_%ls", pBlockTableRecord, (bName));
			}		
		}

		int count = 0;
		HC_Begin_Segment_Search(H_ASCII_TEXT(segment_name));
		HC_Show_Segment_Count(&count);
		HC_End_Segment_Search();

		if( count == 0 )
			isNew = true;

		ret_segment_key = HC_KOpen_Segment(H_ASCII_TEXT(segment_name));
		HC_Close_Segment();

		// Insert key in map
		m_Segments_map.insert(std::pair<void * , HC_KEY>(pBlockTableRecord,ret_segment_key));

		pBlockTableRecord->close();
	}

	return ret_segment_key;
}

// returns the segment key of the block table record segment which contains/should contain
// this entity. The segment will be created if it doesn't exist
HC_KEY HDWG_3dgsImporter::GetBlockTableRecordSegmentForEntity(AcDbEntity *pEnt)
{
	HC_KEY ret_segment_key = INVALID_KEY;
	AcDbBlockTableRecord *pBlockTableRecord = 0;
	AcDbObjectId ent_block_id = pEnt->blockId();
	bool isNew = false;
	return GetBlockTableRecordSegmentFromId(ent_block_id, isNew);
}

bool HDWG_3dgsImporter::importDWGFile(const wchar_t * FileName, HC_KEY modelKey, HInputHandlerOptions * pInputOptions)
{
	bool result = false;
	if(m_fileName!=NULL)
		free(const_cast<wchar_t*>(m_fileName));
	m_fileName = h_dwg_wcsdup(FileName);

	wchar_t drive[_MAX_DRIVE] = L"";
	wchar_t dir[_MAX_DIR] = L"";
	wchar_t fname[_MAX_FNAME] = L"";
	wchar_t ext[_MAX_EXT] = L"";

	_wsplitpath((FileName), drive, dir, fname, ext);

	if (wcsicmp(ext, L".dwg") && wcsicmp(ext, L".dxf"))
		// File must have .dwg or .dxf extension
		return false;


	AcDbDatabase *pDb = new AcDbDatabase(Adesk::kFalse);
	if (pDb == NULL)
		return false;

	Acad::ErrorStatus acad_err;
	// Read the drawing  or dxf file.
	try
	{
		if(wcsicmp(ext, L".dwg"))
		{
			acad_err = pDb->dxfIn((FileName));
		}
		else
		{
			acad_err = pDb->readDwgFile((FileName), _SH_DENYNO);
		}
	}
	catch(DWGException* ex)
	{
		m_pDWGInputHandler->ReportInputInformation("DWG Read Error:");
		m_pDWGInputHandler->ReportInputInformation(ex->what());
		acad_err = Acad::eCantOpenFile;
		delete ex;
	}

	if (acad_err != Acad::eOk)
	{
		m_pDWGInputHandler->ReportInputInformation("DWG Import Error: Failed to load AcDbDatabase");
		delete pDb;
		return false;
	}

	result = importDWGDatabase(pDb, modelKey, pInputOptions);


	// NOTE: This is equivalent to 	delete pDb; in a non-AutoCAD-based host environment
	if(!m_pConnectivityInfo)
		acdbReleaseHostDwg(pDb);

	return result;
}

void HDWG_3dgsImporter::update_layout_list(AcDbDatabase* pAcDbDatabase)
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

void HDWG_3dgsImporter::GetNoOfEntitiesForProgressBar(AcDbDatabase* pAcDbDatabase)
{
	m_nTotalEntities = 0; // initialize
	m_nCurrentEntityCount = 0; // initialize counter
	// Get Layout list and count all the entities.
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
				// TODO: Right now I am counting entities in all layouts, but when user specifically wants only model space 
				// or any spcial layout, we should count entities only in those layouts.
				// The m_listDWGLayouts can be used for that. ASHISH 14/09/2010.
				AcDbObjectId layoutId = layout->getBlockTableRecordId();
				AcDbBlockTableRecord *pRecord = 0;
				if(acdbOpenObject(pRecord, layoutId, AcDb::kForRead) == Acad::eOk)
				{
					//count Layout Entities
					AcDbBlockTableRecordIterator *pRecordIter;
					if (pRecord->newIterator(pRecordIter) == Acad::eOk)
					{
						while (!pRecordIter->done())
						{
							m_nTotalEntities++;
							pRecordIter->step();
						}                            
						delete pRecordIter;
					} 
					pRecord->close();
				}
				pLayObj->close();
			}
			dItr->next();
		}
		delete dItr;
		pDict->close();
	}
}

bool HDWG_3dgsImporter::importDWGDatabase(AcDbDatabase* pAcDbDatabase, HC_KEY modelKey, HInputHandlerOptions * pInputOptions)
{
	m_modelKey = modelKey;

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
		m_bDisableDWGDrawOrder = pInputOptions->m_bDisableDWGDrawOrder;
	}


	HC_Open_Segment_By_Key(m_modelKey);

	// I have noticed that DWG files are right-handed. So, set it
	HC_Set_Heuristics("polygon handedness = right");

	if(m_pConnectivityInfo)
		m_pConnectivityInfo->SetDatabase(pAcDbDatabase);

	m_dGlobalScaleFactor = pAcDbDatabase->ltscale();

	acdbHostApplicationServices()->setWorkingDatabase(pAcDbDatabase);
	acdbResolveCurrentXRefs(pAcDbDatabase);

	acdbAcisSetDeleteBulletins(Adesk::kTrue);

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
	HC_Open_Segment("info");
	HC_Set_User_Options(units_option);
	HC_Close_Segment();

	//VC: Set this database values only once
	Adesk::UInt16 db_color_idx = pAcDbDatabase->cecolor().colorIndex(); 
	Adesk::UInt32 RGBM_byte = AcCmEntityColor::lookUpRGB(db_color_idx);
	float r,g,b;
	r = (float) GetRValueFromRGBM(RGBM_byte)/255.0f;
	g = (float) GetGValueFromRGBM(RGBM_byte)/255.0f;
	b = (float) GetBValueFromRGBM(RGBM_byte)/255.0f;

	HC_Set_Color_By_Value ("geometry","RGB", r, g, b);

	// TODO: make sure how to get LWDEFAULT
	AcDb::LineWeight db_line_weight = H_LWDEFAULT;
	float h_line_size = 0;
	h_line_size = db_line_weight * H_MM_TO_POINTS/100.0f;
	HC_Set_Line_Weight(h_line_size);

	//set the marker defaults using PDMODE and PDSIZE database settings.
	Adesk::Int16 db_pdmode = pAcDbDatabase->pdmode();
	double db_pdsize = pAcDbDatabase->pdsize();
	set_marker_settings(db_pdmode,db_pdsize );

	HPoint max_lim(pAcDbDatabase->extmax().x, pAcDbDatabase->extmax().y, pAcDbDatabase->extmax().z);
	HPoint min_lim(pAcDbDatabase->extmin().x, pAcDbDatabase->extmin().y, pAcDbDatabase->extmin().z);

	HC_Open_Segment("info");
	char extents[MVO_BUFFER_SIZE];
	sprintf(extents,"Extents_min =%lf %lf %lf, Extents_max =%lf %lf %lf",min_lim.x, min_lim.y, min_lim.z, max_lim.x, max_lim.y, max_lim.z);
	HC_Set_User_Options(extents); 
	HC_Close_Segment();

	// For loading progress bar
	GetNoOfEntitiesForProgressBar(pAcDbDatabase);

	if(m_bImportXData)
	{
		importLBGEData();
	}

	if(m_bImportAllLayouts) // and if the user is providing the list already, this list will be filled again with all layouts.
	{
		update_layout_list(pAcDbDatabase);
	}

	//VC: DWG Layout import support. If layouts are not provided, import MODEL_SPACE by default
	if(m_listDWGLayouts)
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
						if(!m_listDWGLayouts)
						{
							importBlockTableRecord(pRecord);
							// Set initial View
							set_initial_view_for_model_space(pAcDbDatabase);
						}
						else
						{
							HC_Open_Segment("/include library/other block table records/model space");
							HC_Set_Visibility("off");
							char	*type = NULL;
							HC_KEY	model_space_key=0;									
							type = new char [MVO_BUFFER_SIZE];
							HC_Begin_Contents_Search(".", " segment"); 
							while(HC_Find_Contents (type, &model_space_key)) 
							{
								char seg_name[1024];
								HC_Show_Segment(model_space_key, seg_name);
								if((strstr(seg_name,"model_space"))) //btable_FEO3335_model_spac
								{
									break;
								}
							}
							HC_End_Contents_Search ();
							HC_Close_Segment();//Close model_space

							if(model_space_key)
							{
								HC_Open_Segment("Model_Space");
								HC_Include_Segment_By_Key(model_space_key);
								// Set Bounding box info
								HC_Open_Segment("Bounding_Box");
								char extents[MVO_BUFFER_SIZE];
								sprintf(extents,"Extents_min =%lf %lf %lf, Extents_max =%lf %lf %lf",min_lim.x, min_lim.y, min_lim.z, max_lim.x, max_lim.y, max_lim.z);
								HC_Set_User_Options(extents); 
								HC_Close_Segment();

								// If the user wants a specific layout ON by sending list, model_space should remain OFF.
								// This is to make sure that previous applications (prior to m_bImportAllLayouts) would work as they were. 
								if(! m_bImportAllLayouts)
								{
									HC_Set_Visibility("off");
									HC_Set_Heuristics("exclude bounding");
								}
								else
								{
									// Set initial View
									set_initial_view_for_model_space(pAcDbDatabase);
								}
								// Set unicode option for layout name it hepls in finding layouts while
								// setting visibility
								HC_Set_Unicode_Options((unsigned short const*)H_UTF16("layout = model").encodedText());
								HC_Close_Segment();	/////MS Include
							}

							delete [] type;
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
	result = true; 

	//Refer Eventum Issue : 8316 and 8296
	//if( m_bIs3D )
	//{
	//	// Switch of the text if this is a 3D DWG
	//	// There could a better way to do this, may be as an input option? - Rajesh B (18-Dec-07)
	//	HC_Set_Visibility("text=off");
	//}

	//if(!m_bImportXData && !m_listDWGLayouts)//in importXData, Optimize_Segment_Tree disturbs the Entity, Layer and GroupNames
	{
		char optimize_options[256];
		strcpy(optimize_options, "reorganize = (color = on), discard user data = off, process includes, preserve user options=merge");

		// Issue 11705 - m_bDWGInsertMeshesAsShells if true merges all shells with above filters on.
		// It can affect the shell selection as it will merge the shells within above merging constraints.
		if(m_bDWGInsertMeshesAsShells)
			strcat(optimize_options, ", merge shells");

		if(m_pConnectivityInfo)
		{
			strcat(optimize_options, ",generate mapping = on");
			m_pConnectivityInfo->OptimizeTree(".",optimize_options);
		}
		else
		{
			strcat(optimize_options, ",no generate mapping");
			HC_Optimize_Segment_Tree(".", optimize_options);
		}
	}

	HC_Close_Segment();

	return result;
}
void HDWG_3dgsImporter::import_layout(AcDbDatabase *pAcDbDatabase)
{
	AcDbBlockTable *p;                                               
	AcDbBlockTableRecord * model_spaceRecord = 0; // For unique model_space search- fix for 10556.
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
						m_CurrentLayoutName = pName;
						importBlockTableRecord(pRecord);
						m_CurrentLayoutName = 0;

						model_spaceRecord = pRecord;
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

	// get the model space segment key and set it's visibility off
	char type[256];
	HC_KEY	model_space_key=0;									
	HC_Open_Segment("/include library/other block table records/model space");
	{
		HC_Set_Visibility("off");
		char seg_name[1024];
		sprintf(seg_name, "btable_%p_model_space", model_spaceRecord);
		ConverToLower(seg_name);
		model_space_key = HC_KOpen_Segment(seg_name);
		HC_Close_Segment();	
	}
	HC_Close_Segment();//Close model_space

	// import layouts.
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
						AcDbBlockTableRecord *pRecord = 0;
						if(acdbOpenObject(pRecord, layoutId, AcDb::kForRead) == Acad::eOk)
						{
							m_CurrentLayoutName = layoutName;
							importBlockTableRecord(pRecord);//Import Layout Entities
							m_CurrentLayoutName = 0;
							pRecord->close();

							HC_Open_Segment_By_Key(m_modelKey);
							{
								HC_KEY	paper_space_key;
								HC_Begin_Contents_Search(".", " segment"); 
								while(HC_Find_Contents (type, &paper_space_key)) 
								{
									char seg_name[1024];
									HC_Show_Segment(paper_space_key, seg_name);
									//if((strstr(seg_name,"sheet page")))

									char lay_lower[MVO_BUFFER_SIZE];

									// Using mere H_ASCII_TEXT would not solve the conditioning problem as layoutName may
									// contain special characters. Also it may have Unicode chars
									// Using this piece to condition layoutName.
									wchar_t conditioned_LayOut_Name[MVO_BUFFER_SIZE];
									wcscpy(conditioned_LayOut_Name, layoutName);
									condition_string_for_segment_name(conditioned_LayOut_Name);

									sprintf(lay_lower, "btable_%p_%s",pRecord, H_ASCII_TEXT(conditioned_LayOut_Name));
									ConverToLower(lay_lower);

									if((strstr(seg_name, lay_lower)))//This is current layout segment
									{
										HC_Open_Segment_By_Key(paper_space_key);
										{
											//Set some option, so that it will not get optimized 
											wchar_t temp[MVO_BUFFER_SIZE];
											condition_string_for_user_options(layoutName);
											swprintf(temp, MVO_BUFFER_SIZE, L"Layout=%ls",layoutName);

											HC_Set_Unicode_Options((unsigned short const*)H_UTF16(temp).encodedText());

											if(!isFirstLayout || m_bImportAllLayouts)
											{
												HC_Set_Visibility("off");
												HC_Set_Heuristics("exclude bounding");
												HC_Set_Rendering_Options("Attribute Lock = visibility");
											}
											else
											{
												isFirstLayout = false;
											}

											// add viewports in the Layout segment.
											AcDbObjectId paper_space_vp_id = 0;
											paper_space_vp_id = pAcDbDatabase->paperSpaceVportId();

											for (int i = 0; i < (int)m_VpIdCount.size(); i++)
											{	
												AcDbObjectId viewPortId = m_VpIdCount.at(i);
												if(paper_space_vp_id != viewPortId )//To ignore top level viewport
												{
													char vp_seg_name[1024];
													sprintf(vp_seg_name, "view_port_%p",viewPortId);
													//open segment here for each viewport in layout.
													HC_Open_Segment(vp_seg_name);
													{
														int no_ClipPoint = 0;
														HPoint ClipPoint[32];
														float *matrix = new float[16];
														AcCmEntityColor* entityColor = new AcCmEntityColor();
														bool is_On;
														get_layout_data(viewPortId,pAcDbDatabase,ClipPoint,matrix,&no_ClipPoint,entityColor, &is_On);

														// By using setting this layout as current and checking isOn for viewports
														// issue 11137 gets fixed.
														if(model_space_key && is_On)
														{
															HC_Open_Segment("MS Include");
															HC_Set_Heuristics("exclude bounding");
															HC_Include_Segment_By_Key(model_space_key);
															HC_Set_Modelling_Matrix(matrix);
															HC_Set_Polygonal_Clip_Region(no_ClipPoint,ClipPoint,"world");
															HC_Close_Segment();	/////MS Include
														}
														HC_Open_Segment("clip_boundary");
														{
															HPoint* clip_region_point = new HPoint[no_ClipPoint+1];
															for(int i = 0; i < no_ClipPoint; i++)
															{
																clip_region_point[i] = ClipPoint[i];
															}

															clip_region_point[no_ClipPoint] = clip_region_point[0];
															HC_Insert_Polyline((no_ClipPoint+1),clip_region_point);

															// query color and set on this segment
															float r,g,b;
															Adesk::UInt32 RGBM_byte = AcCmEntityColor::lookUpRGB(entityColor->colorIndex());
															r = (float) GetRValueFromRGBM(RGBM_byte)/255.0f;
															g = (float) GetGValueFromRGBM(RGBM_byte)/255.0f;
															b = (float) GetBValueFromRGBM(RGBM_byte)/255.0f;

															HC_Set_Color_By_Value("geometry", "RGB",r,g,b);

															delete []clip_region_point;
														}
														HC_Close_Segment();
														delete []matrix;						
														delete entityColor;
													}
													HC_Close_Segment();//vp_seg...
												}
											}

											// For Bounding box
											AcGePoint2d min_Lim;
											AcGePoint2d max_Lim;
											layout->getLimits(min_Lim, max_Lim);
											// Bounding Box segment
											HC_Open_Segment("Bounding_Box");
											{
												char extents[MVO_BUFFER_SIZE];
												sprintf(extents,"Extents_min =%lf %lf 0.0, Extents_max =%lf %lf 0.0",min_Lim.x, min_Lim.y, max_Lim.x, max_Lim.y);

												HC_Set_User_Options(extents);
											}
											HC_Close_Segment();
										}
										HC_Close_Segment();//paper_seg....
										break;//Found the required layout_segment and included Model_space
									}
								}
								HC_End_Contents_Search ();
							}
							HC_Close_Segment();//modelKey	
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

void HDWG_3dgsImporter::set_initial_view_for_model_space(AcDbDatabase* pAcDbDatabase)
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

		// Set proper camera from this record
		HCamera camera;
		GetCameraForInitialView(camera, pRecord);

		// Ask hoops to do the required work for using this data
		HC_Open_Segment(".");

		HC_Open_Segment_By_Key(m_pInputOptions->m_pHBaseView->GetSceneKey());
		HC_Set_Camera(&camera.position, &camera.target, &camera.up_vector, camera.field_width, camera.field_height, camera.projection);
		HC_Close_Segment();

		m_pInputOptions->m_pHBaseView->HasInitialView(true);

		SetRenderMode(m_pInputOptions, pRecord);

		HC_Close_Segment();

		pRecord->close();
	}

	delete pIterator;
	pViewportTable->close();
}

void HDWG_3dgsImporter::importBlockTableRecord(AcDbBlockTableRecord* pRecord)
{
	// this is to handle draw order set on the entities.
	HDrawOrderHandler DrawOrderhandler(pRecord);
	DrawOrderhandler.Open();

	float progress = 0.0;
	int progress_notification_count = 0;

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

				HC_KEY blck_table_rec_seg_key = INVALID_KEY;
				blck_table_rec_seg_key = GetBlockTableRecordSegmentForEntity(pEnt);
				importAcDbEntity(pEnt,blck_table_rec_seg_key);

				// Set draw order settings
				if(m_bIs2DEntity == true && !m_bDisableDWGDrawOrder)
				{
					DrawOrderhandler.CheckDrawOrderAndSetVisibility(pEnt,blck_table_rec_seg_key, this);
				}
				pEnt->close();
				m_nCurrentEntityCount++;

				// Progress bar
				progress_notification_count++;
				if(progress_notification_count == 10) // Increase progress_notification_count if you want less frequent notification
				{
					progress = 1.0 * (float)m_nCurrentEntityCount/(float)m_nTotalEntities;
					// This posts the current percent progress should be between 0.0 and 1.0
					m_pDWGInputHandler->ReportInputPercentProgress(progress);
					progress_notification_count = 0;
				}
			}
			pRecordIter->step();
		}                            
		delete pRecordIter;
	} 

	DrawOrderhandler.Close();
}
/////////////////////
void HDWG_3dgsImporter::get_entity_material_style(AcDbEntity* pEnt, const AcDbLayerTableRecord *pLayerTableRecord, HC_KEY& style_key)
{
	style_key = INVALID_KEY;
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

		HC_Open_Segment_By_Key(m_modelKey);
		HC_Open_Segment(HDWG_MATERIALS_LIBRARY_SEGMENT);

		// set the visibility off. This could have been done once at the start
		// but we create it here only when it is needed.
		HC_Set_Visibility("off");

		int count = 0;
		HC_Begin_Segment_Search(H_ASCII_TEXT(mat_seg_name));
		HC_Show_Segment_Count(&count);
		HC_End_Segment_Search();

		style_key = HC_KOpen_Segment(H_ASCII_TEXT(mat_seg_name));
		if( count <= 0 )
			importAcDbMaterial(p_mat, pMapper);
		HC_Close_Segment();

		HC_Close_Segment();
		HC_Close_Segment();

		p_mat->close();
	}
}
static bool get_text_alignment(AcDbText* pAcDbText, char * retAlignment)
{

	AcDb::TextVertMode vert_mode = pAcDbText->verticalMode();
	AcDb::TextHorzMode hort_mode = pAcDbText->horizontalMode();

	switch(hort_mode)
	{
	case AcDb::kTextAlign:
	case AcDb::kTextFit:
	case AcDb::kTextLeft:
		strcpy(retAlignment, "<");
		break;
	case AcDb::kTextRight:
		strcpy(retAlignment, ">");
		break;
	case AcDb::kTextCenter:
	case AcDb::kTextMid:
	default:
		strcpy(retAlignment, "*");
		break;
	}

	switch(vert_mode)
	{
	case AcDb::kTextBase:
	case AcDb::kTextBottom:
		strcat(retAlignment, "v");
		break;
	case AcDb::kTextTop:
		strcat(retAlignment, "^");
		break;
	case AcDb::kTextVertMid:
	default:
		strcat(retAlignment, "*");
		break;
	}
	return true;
}

static bool get_Mtext_alignment(AcDbMText::AttachmentPoint eMattachpoint, char * retAlignment)
{
	//Only 9 cases exists for Mtext & are handled here, if 10th case exists in future then it should handled. The default option in switch
	// statement "**" doesnt have any meaning.
	switch(eMattachpoint)
	{
	case AcDbMText::kBottomCenter:		
	case AcDbMText::kTopCenter:		
	case AcDbMText::kMiddleCenter:
		strcpy(retAlignment, "v*");
		break;
	case AcDbMText::kBottomLeft:		
	case AcDbMText::kTopLeft:		
	case AcDbMText::kMiddleLeft:
		strcpy(retAlignment, "v<");
		break;
	case AcDbMText::kBottomRight:		
	case AcDbMText::kTopRight:		
	case AcDbMText::kMiddleRight:
		strcpy(retAlignment, "v>");
		break;	
	default: 
		strcpy(retAlignment, "**");
		break;
	}	
	return true;
}


void HDWG_3dgsImporter::importAcDbMaterial(AcDbMaterial *pAcDbMaterial, AcGiMapper pMapper)
{
	AcGiMaterialColor color;
	AcGiMaterialMap	  mat_map;
	AcCmEntityColor cm_color;
	Adesk::UInt32 RGBM_byte;
	float r,g,b;
	char h_color_def[MVO_BUFFER_SIZE];
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
		sprintf(h_color_def, "ambient = (R = %f G = %f B = %f)", r, g, b);

		HC_Set_Color(h_color_def);
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
		HC_Set_Color_By_Value ("faces","RGB", r, g, b);

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
				char imageFormat[64];
				swprintf(imageName, MVO_BUFFER_SIZE, L"%ls_%p", (p_tex_filename), pAcGiImageFileTexture);				
				strcpy(imageFormat, "rgba");

				HInputHandler *reader = HDB::GetHIOManager()->GetInputHandler(file_ext);
				if(reader)
				{
					// get the currently open segment
					HC_KEY this_style = HC_KOpen_Segment(".");
					HC_Close_Segment();

					HC_KEY image_key;
					HInputHandlerOptions options;
					char * imageNameAscii = strdup(H_ASCII_TEXT(imageName));
					options.m_pImageName = imageNameAscii;
					options.m_pImageFormat = imageFormat;
					HFileInputResult result = InputFail;

					result = reader->FileInputToImageKey((texture_file), 
						&image_key, this_style, &options );					

					if(result == InputOK)
					{
						//AcGiMapper mapper = mat_map.mapper();
						AcGiMapper::Projection map_mode = pMapper.projection();
						char param_source[MVO_BUFFER_SIZE];
						char texture_def[MVO_BUFFER_SIZE];
						char color_opts[MVO_BUFFER_SIZE];

						if( map_mode == AcGiMapper::kPlanar || map_mode == AcGiMapper::kBox)
							strcpy(param_source, "natural");
						/*else if( map_mode == AcGiMapper::kBox)
						strcpy(param_source, "surface normal");*/
						else if( map_mode == AcGiMapper::kCylinder)
							strcpy(param_source, "cylinder");
						else if( map_mode == AcGiMapper::kSphere)
							strcpy(param_source, "sphere");
						else
							strcpy(param_source, "uv");

						sprintf(texture_def,"source = %s, parameterization source = %s",
							imageNameAscii, param_source);
						// TODO: add more texture definition parameters

						HC_Define_Local_Texture(imageNameAscii, texture_def); 

						sprintf (color_opts, "faces = %s", imageNameAscii);
						HC_Set_Color(color_opts);
					}
					else
					{
						wchar_t error_msg[MVO_BUFFER_SIZE];
						swprintf(error_msg, MVO_BUFFER_SIZE, L"Failed to load texture image file - %ls.\n"
							L"You may need to set the location of the DWG textures\n"
							L"via the File page of the options dialog.", 
							(p_tex_filename));
						HDB::ReportError(H_ASCII_TEXT(error_msg), 1);
					}

					//free(imageNameAscii);
				}
				else
				{
					wchar_t error_msg[MVO_BUFFER_SIZE];
					swprintf(error_msg, MVO_BUFFER_SIZE, L"Failed to load texture image file - %ls.\n"
						L"Could not find any input handler which supports reading of %ls files.", 
						(p_tex_filename), file_ext);
					HDB::ReportError(H_ASCII_TEXT(error_msg), 1);
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


void HDWG_3dgsImporter::importLBGEData()
{
	AcDbBlockTableRecord *pRecord = 0;
	AcDbBlockTableRecord *pModelSpaceRecord = 0;

	AcDbDatabase* pDatabase = acdbHostApplicationServices()->workingDatabase();

	if(m_fileName)
	{
		size_t len = wcslen(m_fileName);
		size_t buff_size = sizeof(wchar_t)*(len+20);
		wchar_t *file_name = (wchar_t*)malloc(buff_size);
		swprintf(file_name, buff_size, L"FileName=%ls",m_fileName);
		HC_Set_Unicode_Options((unsigned short const*)H_UTF16(file_name).encodedText());
		free(file_name);
		file_name = 0;
	}

	HC_Open_Segment_By_Key(m_modelKey);

	HC_Open_Segment("DWG_ENTITY_NAMES");


	//////////////AcDbEntities////////////
	HC_Open_Segment("ENTITY_tYPES");
	for (int i = 0; i < 58; i++) 
	{
		wchar_t *ent_name = h_dwg_wcsdup(EntityList[i].pName);
		wchar_t *ent_name1 = h_dwg_wcsdup(ent_name+4);

		size_t len = wcslen(ent_name1);
		size_t buff_size = sizeof(wchar_t) * (len+10);
		wchar_t *ent_option = (wchar_t*)malloc(buff_size); //maximum 999 number of entities
		swprintf(ent_option, buff_size, L"%i=%ls", i, ent_name1);
		condition_string_for_user_options(ent_option);
		HC_Set_Unicode_Options((unsigned short const*)H_UTF16(ent_option).encodedText());
		entity_record.insert(std::map<int, wchar_t*>::value_type(i, ent_name1));
		free(ent_option);
		free(ent_name);
	}
	HC_Close_Segment();//ENTITY_tYPES
	//////////////AcDbEntities////////////

	/////// AcDbBlockTable////////////
	HC_Open_Segment("BLOCK_tABLE");

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
						swprintf(blk_def_name,MVO_BUFFER_SIZE, L"%i=%ls", blk_counter, (pName1));
						condition_string_for_user_options(blk_def_name);
						HC_Set_Unicode_Options((unsigned short const *)H_UTF16(blk_def_name).encodedText());

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

	HC_Close_Segment();//BLOCK_tABLE
	///////AcDbBlockTable////////////

	HC_Close_Segment();//DWG_ENTITY_NAMES


	/////////AcDbLayers///////////////////
	HC_Open_Segment("LAYER_NAMES");

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
				wchar_t *lay_name = h_dwg_wcsdup(pName);
				layer_record.insert(std::map<int, wchar_t*>::value_type(lay_counter, lay_name));
				condition_string_for_user_options(lay_name);
				size_t len = wcslen(lay_name);
				size_t buff_size = sizeof(wchar_t) * (len+10);
				wchar_t *lay_option = (wchar_t*)malloc(buff_size);//maximum 9999 number of layers
				swprintf(lay_option,buff_size, L"%i=%ls", lay_counter, lay_name);
				HC_Set_Unicode_Options((unsigned short const*)H_UTF16(lay_option).encodedText());
				lay_counter++;
				acdbFree(pName);
				free(lay_option);
			}
			pLayTblRecord->close();
		}
		pLayTblIter->step();
	}
	delete pLayTblIter;
	HC_Close_Segment();//LAYER_NAMES
	/////////AcDbLayers///////////////////

	////////Group Names//////////////////////
	AcDbDictionary* pGroupDict;
	Acad::ErrorStatus err = pDatabase->getGroupDictionary(pGroupDict, AcDb::kForRead);
	if( err == Acad::eOk )
	{
		HC_Open_Segment("GROUP_NAMES");
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
				wchar_t * grp_name = h_dwg_wcsdup(grpName);
				group_record.insert(std::map<int, wchar_t*>::value_type(grp_counter, grp_name));

				size_t len = wcslen(grpName);
				size_t buff_size = sizeof(wchar_t) * (len+10);
				wchar_t *grp_option = (wchar_t*)malloc(buff_size);//maximum 9999 number of groups
				swprintf(grp_option,buff_size, L"%i=%ls", grp_counter, grp_name);
				condition_string_for_user_options(grp_option);
				HC_Set_Unicode_Options((unsigned short const*)H_UTF16(grp_option).encodedText());
				grp_counter++;
				pObj->close();
				free(grp_option);
				acdbFree(grpName);
			}
			pDictIter->next();
		}
		delete pDictIter;
		HC_Close_Segment();//GROUP_NAMES
	}
	pGroupDict->close();
	//////////Group Names////////////////////

	HC_Close_Segment();//m_modelKey
}


void HDWG_3dgsImporter::importAcDbEntity(AcDbEntity *pEnt, HC_KEY parent_seg, bool for_blk_ref)
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
		importAcDbBlockReference((AcDbBlockReference*)pEnt, parent_seg);
		return;
	}
	else if (i == 1)
	{
		importAcDbMInsertBlock((AcDbMInsertBlock*)pEnt, parent_seg);
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
			}
		}
	}
	else if( i >= 13 && i <= 57)
	{
		m_bIs2DEntity = true;

		draw_shaded = false;
		m_bDrawWireframe = true;
	}
	else if( i == 57 || i == 60 )
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
	else if( i > 60 )
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
		}
		deviation_backup = HDWGImporter::get_deviation();
		HDWGImporter::set_deviation(0.1);
	}
	importAcDbEntity(pEnt, draw_shaded, parent_seg, for_blk_ref);
	if( i == 13 )//Reset back Deviation
	{
		HDWGImporter::set_deviation(deviation_backup);
	}
}

void HDWG_3dgsImporter::attachDWGHandle(AcDbEntity *pEnt)
{
	///// AcDbEntity Handle for Persistency //////
	AcDbObjectId id = pEnt->objectId();
	if( !id.isNull())
	{
		AcDbHandle handle = id.handle();
		if(!handle.isNull())
		{
			wchar_t my_buf[MVO_BUFFER_SIZE];
			int int_handle = handle;
			swprintf(my_buf,MVO_BUFFER_SIZE, L"Handle=%X", int_handle);
			HC_Set_Unicode_Options((unsigned short const*)H_UTF16(my_buf).encodedText());
		}
	}
	///// AcDbEntity Handle for Persistency ENDS //////
}

void HDWG_3dgsImporter::importXdata(AcDbEntity *pEnt)
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

	/////////// Entity Info for Model Browser
	if(!pEnt)
		return;
	//Layer
	ACHAR * lay_name = pEnt->layer();
	wchar_t *layer_name = h_dwg_wcsdup(lay_name);
	condition_string_for_user_options(layer_name);
	std::map<int, wchar_t*>::iterator layer_iterator;
	for(layer_iterator = layer_record.begin(); layer_iterator != layer_record.end(); layer_iterator++)
	{
		wchar_t* aa = layer_iterator->second;
		if( wcsicmp(aa, layer_name) == 0)
		{
			wchar_t layer_user_opt[9];
			swprintf(layer_user_opt,9, L"%s=%i", "1",layer_iterator->first);//1 For layer
			HC_Set_Unicode_Options((unsigned short const*)H_UTF16(layer_user_opt).encodedText());
			break;
		}
	}
	free(layer_name);
	acdbFree(lay_name);

	//EntityName
	const ACHAR *ent_type = pEnt->isA()->name();
	wchar_t *entity_name = h_dwg_wcsdup(ent_type);
	condition_string_for_user_options(entity_name);
	std::map<int, wchar_t*>::iterator entity_iterator;
	for(entity_iterator = entity_record.begin(); entity_iterator != entity_record.end(); entity_iterator++)
	{
		wchar_t* aa = entity_iterator->second;
		if( wcsicmp(aa, entity_name+4) == 0)
		{
			wchar_t entity_user_opt[20];
			swprintf(entity_user_opt, 20, L"%s=%i", "3", entity_iterator->first);//2 For Entity name
			HC_Set_Unicode_Options((unsigned short const*)H_UTF16(entity_user_opt).encodedText());
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
							wchar_t *grp_name = h_dwg_wcsdup((grpName));
							condition_string_for_user_options(grp_name);

							std::map<int, wchar_t*>::iterator group_iterator;
							for(group_iterator = group_record.begin(); group_iterator != group_record.end(); group_iterator++)
							{
								wchar_t* aa = group_iterator->second;
								if( wcsicmp(aa, grp_name) == 0)
								{
									wchar_t grp_user_opt[20];
									swprintf(grp_user_opt,20, L"%s=%i", "2",group_iterator->first);//3 For Group Name
									HC_Set_Unicode_Options((unsigned short const*)H_UTF16(grp_user_opt).encodedText());
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
		HC_Set_User_Options(blk_user_opt);

	}
	///////////// End of BlockRef

}


void HDWG_3dgsImporter::importXdata(resbuf *pBuf)
{
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
			swprintf(x_data_lhs,MVO_BUFFER_SIZE, L"%hd_%u=", p->restype, type_count);

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
						p->resval.rlname[1],
						(p->resval.rstring));
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
			//	int i;
			//	for (i = 0; i < p->resval.rbinary.clen; i++)
			//	{
			//		if (i % 16 == 0)
			//			//_print(L"\n\t\t\t    "));
			//		char x_data[MVO_BUFFER_SIZE];
			//		sprintf(x_data, "%02x ", (BYTE)p->resval.rbinary.buf[i]);
			//		HC_Set_User_Options(x_data);

			//		//_print(L"%02x "), (BYTE)p->resval.rbinary.buf[i]);
			//	}
			//	//_print(L"\n"));
			//}
			//}
			//                break;

			if( !wcseq(x_data_rhs, L""))
			{
				condition_string_for_user_options(x_data_rhs);
				wcscat(x_data_lhs, x_data_rhs);
				HC_Set_Unicode_Options((unsigned short const*)H_UTF16(x_data_lhs).encodedText());
			}
			p = p->rbnext;
		}
		acutRelRb(pBuf);
	}
}

#ifndef HDWG_NO_HYPERLINKS_IMPORT
// Import the hyperlinks for a particular entity. Hyperlinks are attached to an entity and are not a separate entity.
// Our strtergy is to get these hyperlinks and store it as user options for that segment.
void HDWG_3dgsImporter::import_hyperlinks(AcDbEntity *pEnt)
{

	AcDbObjectId pEntId;

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
	AcDbEntityHyperlinkPE* pAcDbEntityHyperlinkPE = ACRX_PE_PTR(pEnt, AcDbEntityHyperlinkPE);
	if(pAcDbEntityHyperlinkPE == 0)
	{
		char error_msg[MVO_BUFFER_SIZE];
		sprintf(error_msg, "Failed to query hyperlinks associated with entities.\n"
			"It is possible that the application is unable to locate achapi**.dbx\n"
			"Hyperlinks associated with the entities will be ignored");
		HDB::ReportError(error_msg, 1);
		return;
	}

	pAcDbEntityHyperlinkPE->getHyperlinkCollection(pEnt, pcHCL, false, true);

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

			swprintf(hyperlink_data,MVO_BUFFER_SIZE, L"Hyperlink name = %ls", (pcHO->name()));
			HC_Set_Unicode_Options((unsigned short const*)H_UTF16(hyperlink_data).encodedText());

			swprintf(hyperlink_data,MVO_BUFFER_SIZE, L"Hyperlink location = %ls", (pcHO->subLocation()));
			HC_Set_Unicode_Options((unsigned short const*)H_UTF16(hyperlink_data).encodedText());

			swprintf(hyperlink_data,MVO_BUFFER_SIZE, L"Hyperlink description = %ls", (pcHO->description()));
			HC_Set_Unicode_Options((unsigned short const*)H_UTF16(hyperlink_data).encodedText());
		}
	}

	// Delete the collection. The collection will delete all its
	// contained hyperlink objects.
	delete pcHCL;

	// Close the object.
	pEnt->close();

}
#endif// HDWG_NO_HYPERLINKS_IMPORT

void HDWG_3dgsImporter::importAcDbEntity(AcDbEntity *pEnt, const bool& draw_shaded, 
										 HC_KEY parent_seg, bool for_blk_ref)
{

	if( !draw_shaded && !m_bDrawWireframe)
		// what to draw?
		return;

	float r, g, b;
	int alpha;
	bool is_color_by_block;
	bool is_alpha_by_block;
	bool is_visible;
	HC_KEY style_key = INVALID_KEY;

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
	get_entity_material_style(pEnt, pLayerTableRecord, style_key);

	AcDbObjectId line_type_id = pEnt->linetypeId();

	if(parent_seg == INVALID_KEY)
	{
		// we are organizing entities under their block table record. 
		// Fetch the block table record segment for this entity
		bool import_layout = false;
		if(m_listDWGLayouts)
			import_layout = true;

		HC_KEY blck_table_rec_seg_key = GetBlockTableRecordSegmentForEntity(pEnt);

		HC_Open_Segment_By_Key(blck_table_rec_seg_key);
	}
	else
		HC_Open_Segment_By_Key(parent_seg);

	// Open a new segment for this entity. 
	// Though this is not optimal, we are going to optimize the tree in the end.
	char entity_segment_name[MVO_BUFFER_SIZE];
	sprintf(entity_segment_name, "entity_%p", pEnt);

	HC_KEY entity_seg_key = HC_KOpen_Segment(entity_segment_name);

	if(style_key != INVALID_KEY)
		HC_Style_Segment_By_Key(style_key);

	if( !is_color_by_block && set_color)
	{
		if(style_key != INVALID_KEY)
			HC_Set_Color_By_Value ("edges=markers=lines=text","RGB", r, g, b);
		else
			HC_Set_Color_By_Value ("geometry","RGB", r, g, b);
	}

	if( (!is_alpha_by_block) && (alpha != 255) )
	{
		char htrans_options[MVO_BUFFER_SIZE];
		float halpha = alpha/255.0f;
		sprintf(htrans_options, "geometry=(transmission=(r=%f g=%f b=%f))", halpha, halpha, halpha);
		HC_Set_Color(htrans_options);
	}

	if(line_type_id != AcDbObjectId::kNull)
	{
		bool is_weight_by_block;
		float h_line_wt;
		get_entity_line_weight (pEnt, pLayerTableRecord, h_line_wt, is_weight_by_block);
		if( !is_weight_by_block )
			HC_Set_Line_Weight(h_line_wt);
	}

	import_entity_linetype(pEnt, pLayerTableRecord);

	if(m_bAmIsolidHatch)
	{
		HC_Set_Visibility("face=on,edge=off");
	}
	if( !is_visible )
		HC_Set_Visibility("off");

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

		if ( draw_shaded == true )
		{
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

	HC_Begin_Contents_Search("...", "geometry");
	int n_geoms = 0;
	HC_Show_Contents_Count(&n_geoms);
	HC_End_Contents_Search();

	if( n_geoms > 0 )
	{
		// NOTE: Optimizing on per entity basis. We have found that for too large models, the memory
		// consumed is so much that we don't get chance to optimize in the end - Rajesh B (11-Dec-07)
		if(m_pConnectivityInfo)
			m_pConnectivityInfo->OptimizeTree(".", "merge shells = on, reorganize = (color = on), generate mapping = on, discard user data = off, process includes, collapse matrices, preserve user options=on");
		else
			HC_Optimize_Segment_Tree(".", "merge shells = on, reorganize = (color = on), no generate mapping, discard user data = off, process includes, collapse matrices, preserve user options=on");
	}

	HC_Close_Segment();	// entity_seg_key

	//if( n_geoms < 1 )
	//	HC_Delete_By_Key(entity_seg_key);

	HC_Close_Segment(); //blck_table_rec_seg_key / parent_seg
}


void HDWG_3dgsImporter::importAcDbMTextFragment(AcDbMTextFragment* pAcDbMTextFragment, AcDbMText* pOrigAcDbMText)
{
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

	HC_Open_Segment(segment_name);
	{

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
			HC_Set_Color_By_Value ("text","RGB", r, g, b);
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
			HC_Set_Color_By_Value ("text","RGB", r, g, b);
		}

		//*****************************************************************		
		AcDbMText::AttachmentPoint eattachpoint = pOrigAcDbMText->attachment();	
		char  h_mtext_alignment[16];
		strcpy(h_mtext_alignment, ".<");	// ADN query 1256676, Eventum issue 11785 
		// After fragmentation each fragment resides at bottom left. << ASHISH.S. 11/02/2010
		//get_Mtext_alignment(eattachpoint,h_mtext_alignment);	REMOVE		
		//*****************************************************************

		// We observed (in AutoCAD) that after exploding the Mtext, the text fragments always are Left Justified.
		// Also, the AcDbMtextFragment struct does not have any member for alignment/justification, hence it seems that we can safely assume it is left(hori) center(vert).
		// Sumit K (25/04/2008).
		//text_key = import_text(h_pos, h_dir, h_norm, pAcDbMTextFragment->text,"<*");

		// Transforms are handled generically (for planes other than XY) in this function. 
		//Beta << ASHISH.S. 17/08/2009.
		text_key = apply_transforms_and_insert_text(h_pos, h_dir, h_norm, pAcDbMTextFragment->text,h_mtext_alignment);



		char h_name[MVO_BUFFER_SIZE];
		ACHAR * p_fname = 0;
		if(pAcDbMTextFragment->font && (wcscmp(pAcDbMTextFragment->font, L"") != 0))
			p_fname = pAcDbMTextFragment->font;
		else if(pAcDbMTextFragment->fontname && (wcscmp(pAcDbMTextFragment->fontname, L"") != 0))
			p_fname = pAcDbMTextFragment->fontname;
		else if(pAcDbMTextFragment->bigfont && (wcscmp(pAcDbMTextFragment->bigfont, L"") != 0))
			p_fname = pAcDbMTextFragment->bigfont;
		if( p_fname )
		{
			sprintf(h_name, "name = %s", H_ASCII_TEXT(p_fname));
			HC_Set_Text_Font(h_name);
		}

		if(pAcDbMTextFragment->widthFactor != 1.0f)
		{
			char h_wscale[MVO_BUFFER_SIZE];
			sprintf(h_wscale, "width scale = %f", (float)pAcDbMTextFragment->widthFactor);
			HC_Set_Text_Font(h_wscale);
		}

		if(pAcDbMTextFragment->bold)
			HC_Set_Text_Font("bold=on");
		if(pAcDbMTextFragment->italic)
			HC_Set_Text_Font("italic=on");

		char h_size[MVO_BUFFER_SIZE];
		sprintf(h_size, "size = %f oru", (float)pAcDbMTextFragment->capsHeight);
		HC_Set_Text_Font(h_size);


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
	HC_Close_Segment();

	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(text_key, (void*) pOrigAcDbMText);
}

void HDWG_3dgsImporter::importAcDbCircle(AcDbCircle *pAcDbCircle)
{
	HC_KEY circle_key = INVALID_KEY;
	double radius = pAcDbCircle->radius();
	AcGePoint3d center = pAcDbCircle->center();
	double thickness = pAcDbCircle->thickness();
	AcGeVector3d normal = pAcDbCircle->normal();

	double h_center1[3];
	h_center1[0] = (double)center.x;
	h_center1[1] = (double)center.y;
	h_center1[2] = (double)center.z;

	if (thickness == 0.0)
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

		double h_major[3];
		h_major[0] = (float) (center.x + radius*cos_X_alpha);
		h_major[1] = (float) (center.y + radius*cos_X_beta);
		h_major[2] = (float) (center.z + radius*cos_X_theta);

		double cos_Y_alpha = Wx.dotProduct(Ay);
		double cos_Y_beta  = Wy.dotProduct(Ay);
		double cos_Y_theta = Wz.dotProduct(Ay);

		double h_minor[3];
		h_minor[0] = (float) (center.x + radius*cos_Y_alpha);
		h_minor[1] = (float) (center.y + radius*cos_Y_beta);
		h_minor[2] = (float) (center.z + radius*cos_Y_theta);

		circle_key = HC_DKInsert_Elliptical_Arc (h_center1, h_major, h_minor, 0.0f, 1.0f);
	}
	else 
	{
		m_bIs2DEntity = false;
		double h_center2[3];
		h_center2[0] = (double)(center.x+(thickness*normal.x));
		h_center2[1] = (double)(center.y+(thickness*normal.y));
		h_center2[2] = (double)(center.z+(thickness*normal.z));
		// Insert_Circle_By_Radius would have been much easier to use, but it inserts
		// a circular disc, which is not what we want here.
		circle_key = HC_DKInsert_Cylinder (h_center1,h_center2, radius,"none" );
	}

	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(circle_key, (void*)pAcDbCircle);
}
void HDWG_3dgsImporter::set_marker_settings(const Adesk::Int16 db_pdmode,const double db_pdsize )
{
	if( db_pdmode == 1)
	{
		// fix for 10511
		HC_Set_Marker_Size(0);
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

	if( pGlyph.pSymbolDefinition ){
		// this is not a standard HOOPS marker, we may have to define this as glyph
		HC_Define_Glyph( pGlyph.pSymbolName, pGlyph.nSybolDefinitionSize, pGlyph.pSymbolDefinition);
	}

	HC_Set_Marker_Symbol(pGlyph.pSymbolName);

	// AutoCAD ref: PDSIZE controls the size of the point figures, except for PDMODE values 0 and 1. 
	// A setting of 0 generates the point at 5 percent of the drawing area height. 
	// A positive PDSIZE value specifies an absolute size for the point figures. 
	// A negative value is interpreted as a percentage of the viewport size. 
	// The size of all points is recalculated when the drawing is regenerated.
	// HOOPS ref: The default "1.0" marker size equals 3.0 percent of the height of the display screen or 
	// virtual display screen. More precisely, it describes a 3.0 percent circle into which any marker symbol (except ".") will be made as large as possible and still fit into it. 
	// So if, for example, you wanted a 3 pixel x 3 pixel box, you would need a circle of diameter 3*sqrt(2).

	if(db_pdmode == 0.0)
		// for this mode, I found that whatever behaviour HOOPS has for 0 setting is same has AutoCAD
		// i.e. the marker size is constant regardless of everything else and probably 1 pixel.
		HC_Set_Marker_Size(0);
	else if( db_pdsize == 0.0 )
		HC_Set_Marker_Size( fabs(5.0/3.0));
	else if( db_pdsize < 0.0 )
		HC_Set_Marker_Size( fabs(db_pdsize/3.0));
	else if( db_pdsize > 0.0 )
	{
		char marker_size[1024];
		sprintf(marker_size, "%g oru", db_pdsize);
		HC_Set_Variable_Marker_Size(marker_size);
	}
}



void HDWG_3dgsImporter::importAcDbPoint(AcDbPoint *pAcDbPoint)
{
	HC_KEY marker_key = INVALID_KEY;
	char geo_option[MVO_BUFFER_SIZE];
	// TODO: support point thickness
	AcGePoint3d pos = pAcDbPoint->position();
	AcGeVector3d normal = pAcDbPoint->normal();
	float n1 = normal.x;
	float n2 = normal.y;
	float n3 = normal.z;
	sprintf(geo_option, "orientation=(%f,%f,%f)",n1,n2,n3);
	marker_key = HC_KInsert_Marker(pos.x, pos.y, pos.z);
	HC_Set_Geometry_Options(marker_key,geo_option);
	HC_Set_Visibility("markers=on");

	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(marker_key, (void*)pAcDbPoint);
}
void HDWG_3dgsImporter::importAcDbMInsertBlock(AcDbMInsertBlock *pAcDbMInsertBlock, HC_KEY parent_seg)
{
	int cols = (int)pAcDbMInsertBlock->columns();
	int rows = (int)pAcDbMInsertBlock->rows();
	double colSpac = pAcDbMInsertBlock->columnSpacing();
	double rowSpac = pAcDbMInsertBlock->rowSpacing();

	HC_Open_Segment_By_Key(parent_seg);
	HC_KEY block_element;
	for(int i=0; i < cols; i++)
	{
		for( int j=0; j < rows; j++)
		{
			char seg_name[MVO_BUFFER_SIZE];
			sprintf(seg_name, "AcDbMInsertBlock_%p_%d_%d", pAcDbMInsertBlock, i,j);
			block_element = HC_KOpen_Segment(seg_name);
			importAcDbBlockReference(pAcDbMInsertBlock, block_element, i, j);
			HC_Close_Segment();
		}
	}
	HC_Close_Segment();

	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(block_element, (void*)pAcDbMInsertBlock);
}

void HDWG_3dgsImporter::importAcDbBlockReference(AcDbBlockReference *pAcDbBlockReference, HC_KEY parent_seg, int mib_col, int mib_row)
{
	// btr = Block Table Record
	AcDbObjectId btr_id = pAcDbBlockReference->blockTableRecord();
	if(btr_id.isValid() == false)
		return;

	HC_Open_Segment("/include library/other block table records");

	bool btr_not_loaded = false;
	bool import_layout = false;
	if(m_listDWGLayouts)
		import_layout = true;
	HC_KEY btr_seg_key = GetBlockTableRecordSegmentFromId(btr_id, btr_not_loaded);

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

	// if the block table record is not loaded, load it before including it
	if (btr_not_loaded == true)
	{
		AcDbBlockTableRecord *pRecord = 0;
		acdbOpenObject(pRecord, btr_id, AcDb::kForRead);

		// this is to handle draw order set on the entities.
		HDrawOrderHandler DrawOrderhandler(pRecord, true);
		DrawOrderhandler.Open();

		if(pRecord)
		{
			AcDbBlockTableRecordIterator *pRecordIter;
			if (pRecord->newIterator(pRecordIter) == Acad::eOk)
			{
				char entity_segment_name[MVO_BUFFER_SIZE]="";
				char user_option_debug[MVO_BUFFER_SIZE]="";
				AcDbEntity *pBlockRefEnt;
				while (!pRecordIter->done())
				{
					if (pRecordIter->getEntity(pBlockRefEnt, AcDb::kForRead) == Acad::eOk)
					{
						importAcDbEntity(pBlockRefEnt, btr_seg_key, true);

						// Draw order settings starts
						if(m_bIs2DEntity == true && !m_bDisableDWGDrawOrder)
						{
							DrawOrderhandler.CheckDrawOrderAndSetVisibility(pBlockRefEnt, btr_seg_key, this);
						}
						pBlockRefEnt->close();
					}
					pRecordIter->step();
				}                            
				delete pRecordIter;
			}
		}
		pRecord->close();
		DrawOrderhandler.Close();
	}
	HC_Close_Segment();
	m_BlockRefIndex = -1;



	// we are organizing entities under their block table record. 
	// Fetch the block table record segment for this entity
	HC_KEY blck_table_rec_seg_key;
	if(parent_seg == INVALID_KEY)
	{
		bool import_layout = false;
		if(m_listDWGLayouts)
			import_layout = true;
		blck_table_rec_seg_key = GetBlockTableRecordSegmentForEntity(pAcDbBlockReference);
	}
	else
		blck_table_rec_seg_key = parent_seg;

	HC_Open_Segment_By_Key(blck_table_rec_seg_key);  

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
				importAcDbEntity(pAtt, blck_table_rec_seg_key);
			pAtt->close();
		}
		pIter->step();
	}
	delete pIter;
	//-------------------------------------------------------

	// create a segment for the block reference
	char block_ref_seg_name[MVO_BUFFER_SIZE];
	sprintf(block_ref_seg_name, "block_ref_%p", pAcDbBlockReference);

	HC_Open_Segment(block_ref_seg_name);

	//insert the clipping polygon here	
	insertClip(pAcDbBlockReference);

	// include the referenced block table record here
	HC_Include_Segment_By_Key(btr_seg_key);

	// Get Layer table record, closed at the end of this method
	AcDbLayerTableRecord *pLayerTableRecord = 0;
	AcDbObjectId ent_layer_id = pAcDbBlockReference->layerId();
	Acad::ErrorStatus es = acdbOpenObject(pLayerTableRecord, ent_layer_id, AcDb::kForRead);

	// let's set the default attributes (color, line wt etc.) which will act 
	// as attributes for entities which have them BYBLOCK.
	float r, g, b;
	bool is_color_by_block;
	get_entity_rgb(pAcDbBlockReference, pLayerTableRecord, r, g, b, is_color_by_block);
	if(!is_color_by_block)
		HC_Set_Color_By_Value ("geometry","RGB", r, g, b);

	int alpha = 255;
	bool is_alpha_by_block;
	get_entity_transparency(pAcDbBlockReference, pLayerTableRecord, alpha, is_alpha_by_block );

	if( (!is_alpha_by_block) && (alpha != 255) )
	{
		char htrans_options[MVO_BUFFER_SIZE];
		float halpha = alpha/255.0f;
		sprintf(htrans_options, "geometry=(transmission=(r=%f g=%f b=%f))", halpha, halpha, halpha);
		HC_Set_Color(htrans_options);
	}

	bool is_weight_by_block;
	float h_line_wt;
	get_entity_line_weight (pAcDbBlockReference, pLayerTableRecord, h_line_wt, is_weight_by_block);
	if( !is_weight_by_block )
		HC_Set_Line_Weight(h_line_wt);

	import_entity_linetype(pAcDbBlockReference, pLayerTableRecord);

	// Freeze status of the block's layer
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
		HC_Set_Visibility("off");
		HC_Set_Heuristics("exclude bounding");
		HC_Set_Rendering_Options("attribute lock = visibility");
	}
	// Freeze Check Ends

	AcGeMatrix3d trans_matrix;
	trans_matrix = pAcDbBlockReference->blockTransform();
	if(trans_matrix != AcGeMatrix3d::kIdentity || mib_row || mib_col )
	{
		trans_matrix.transposeIt();
		float h_trans_matrix[4][4];
		for (int i =0; i<4; i++)
			for(int j =0; j<4; j++)
				h_trans_matrix[i][j] = (float) trans_matrix(i,j);

		//HC_Compute_Matrix_Product((float*)rot_matrix,(float*)h_trans_matrix,(float*)h_trans_matrix);
		HC_Set_Modelling_Matrix((float*)h_trans_matrix);

		//////////VijayC: Individual block level scaling and rotation
		if(mib_row || mib_col)
		{
			double col_spec = ((AcDbMInsertBlock *)(pAcDbBlockReference))->columnSpacing();
			double row_spec = ((AcDbMInsertBlock *)(pAcDbBlockReference))->rowSpacing();
			HPoint trs_pt(mib_col * col_spec, mib_row * row_spec);
			float r_mat[16];
			double rot_angle = pAcDbBlockReference->rotation();
			rot_angle = rot_angle*180.0/HDWG_PI;
			HC_Compute_Rotation_Matrix(0.0, 0.0, rot_angle, r_mat);
			HC_Compute_Transformed_Points(1, (void*)&trs_pt, r_mat, (void*)&trs_pt);
			HC_Translate_Object(trs_pt.x, trs_pt.y, trs_pt.z);
		}
	}

	// We are trying to apply scale to the geometry but its doesnt see to work properly.
	// apply the modeling matrix (if not identity)
	//	AcGeScale3d blck_ref_scale = pBlockRef->scaleFactors();
	//	if( blck_ref_scale != AcGeScale3d::kIdentity )
	//		HC_Scale_Object(blck_ref_scale[0], blck_ref_scale[1], blck_ref_scale[2]);


	HC_Close_Segment();
	HC_Close_Segment();

	// Close layer table record
	if (pLayerTableRecord)
		pLayerTableRecord->close();
}

Adesk::Boolean HDWG_3dgsImporter::import_circle(const AcGePoint3d& pt1,
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

	// HACK: 
	// Can't use Insert_Circle because it inserts a disc
	// Can't use Insert_Circular_Arc because it won't complete the circle
	// Cant' use Insert_Elliptical_Arc because it needs major and minor axes intersection points
	// requiring unnecessary computation
	// for now I am inserting two circular arcs as a workaround
	// Pavan T (28-Feb-06)
	//HC_Insert_Circular_Arc(h_point1, h_point2, h_point3);
	//HC_Insert_Circular_Arc(h_point2, h_point3, h_point1);
	// Finally there is something...
	HC_KEY circle_key = HUtilityGeometryCreation::CreateWireframeCircleWithEllipse(h_point1, h_point2, h_point3);

	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(circle_key, pDatabaseEntity);

	return Adesk::kFalse;
}


Adesk::Boolean HDWG_3dgsImporter::import_circular_arc(const AcGePoint3d& center,
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

	HC_KEY arc_key = HC_KInsert_Elliptical_Arc (h_center,h_major,h_minor, h_start_angle,h_end_angle);
	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(arc_key, (void*) pDatabaseEntity);

	return Adesk::kFalse;
}


Adesk::Boolean HDWG_3dgsImporter::import_circular_arc(const AcGePoint3d& start,
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

	HC_KEY arc_key = HC_KInsert_Circular_Arc (h_point1,h_point2,h_point3);
	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(arc_key, (void*) pDatabaseEntity);

	return Adesk::kFalse;

}

Adesk::Boolean HDWG_3dgsImporter::import_polyline(	const Adesk::UInt32 nbPoints,
												  const AcGePoint3d* pVertexList,
												  const AcGeVector3d* pNormal,
												  Adesk::LongPtr lBaseSubEntMarker,
												  AcDbEntity* pDatabaseEntity) const
{
	if( !m_bDrawWireframe )
		return Adesk::kFalse;

	HC_KEY key = INVALID_KEY;

	if( nbPoints < 2 )
		return Adesk::kFalse;
	else if (nbPoints == 2)
	{
		if( pVertexList[0] != pVertexList[1] )
		{
			key = HC_KInsert_Line(pVertexList[0].x, pVertexList[0].y, pVertexList[0].z, 
				pVertexList[1].x, pVertexList[1].y, pVertexList[1].z);
		}
		else
		{
			//the Hatch pattern AR-SAND is a collection of lines with co-incident start and end point.
			//so,if points 0 and 1 in pVertexList are same we are inserting a marker (".") at that point - SumitK(10/06/08)
			HC_Set_Marker_Symbol(".");
			HC_Insert_Marker(pVertexList[0].x, pVertexList[0].y, pVertexList[0].z);
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

		key = HC_KInsert_Polyline (nbPoints, h_points);	

		delete[] h_points;
	}
	if (pDatabaseEntity->isKindOf(AcDb2dPolyline::desc()))
	{
		double polyline_thickness = 0.00;
		polyline_thickness = ((AcDb2dPolyline*)pDatabaseEntity)->thickness();

		if(polyline_thickness != 0.00)
		{
			HC_KEY key = NULL;
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

			key = extrude_profile_along_line(nbPoints, polyline_pts, &h_line_norm, polyline_thickness);

			if(m_pConnectivityInfo)
				m_pConnectivityInfo->AddConnection(key, (void*) pDatabaseEntity);
			delete []polyline_pts;
		}
	}

	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(key, (void*) pDatabaseEntity);

	return Adesk::kFalse;
}

Adesk::Boolean HDWG_3dgsImporter::import_polygon(const Adesk::UInt32 nbPoints,
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

	HC_KEY key = HC_KInsert_Polygon (nbPoints, h_points);
	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(key, (void*) pDatabaseEntity);

	delete[] h_points;

	return Adesk::kFalse;
}

HC_KEY HDWG_3dgsImporter::extrude_profile_along_line(const int& nProfilePoints, 
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

	HC_KEY shell_key = HC_KInsert_Shell( total_points, shell_points,
		face_indices_length, face_indices);

	H_SAFE_DELETE_ARRAY(face_indices);
	H_SAFE_DELETE_ARRAY(shell_points);

	return shell_key;

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
void HDWG_3dgsImporter::importAcDbLine(AcDbLine *pAcDbLine)
{
	AcGePoint3d start_point = pAcDbLine->startPoint();
	AcGePoint3d end_point = pAcDbLine->endPoint();
	double line_thickness = pAcDbLine->thickness();

	if(line_thickness != 0.00)
	{
		//Even if line has thickness its a planar entity and hence we need
		//to set the draworder to it - Mustafa Bohari 10-SEP-09
		//m_bIs2DEntity = false;
		HC_KEY key = NULL;
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

		key = extrude_profile_along_line(2, line_pts, &h_line_norm, line_thickness);

		if(m_pConnectivityInfo)
			m_pConnectivityInfo->AddConnection(key, (void*) pAcDbLine);
		delete []line_pts;
	}
	else 
		HC_Insert_Line(start_point.x,start_point.y,start_point.z,end_point.x,end_point.y,end_point.z);

}

void HDWG_3dgsImporter::importAcDbRay(AcDbRay* pRay)
{
	AcGePoint3d basepoint = pRay->basePoint();

	AcGeVector3d unitDir = pRay->unitDir();
	if(!(unitDir.isZeroLength()) )
		HC_Insert_Infinite_Ray(basepoint.x, basepoint.y, basepoint.z, (basepoint.x+unitDir.x), (basepoint.y+(unitDir.y)), (basepoint.z+unitDir.z));
}


void HDWG_3dgsImporter::importAcDbXline(AcDbXline* pXline)
{
	AcGePoint3d basepoint = pXline->basePoint();

	AcGeVector3d unitDir = pXline->unitDir();
	if(!(unitDir.isZeroLength()) )
		HC_Insert_Infinite_Line(basepoint.x, basepoint.y, basepoint.z, (basepoint.x+unitDir.x), (basepoint.y+unitDir.y), (basepoint.z+unitDir.z));
}
void HDWG_3dgsImporter::importAcDbViewport(AcDbViewport* pViewport)
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

void HDWG_3dgsImporter::importAcDbRasterImage(AcDbRasterImage* pEnt)
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


	if(image_already_exists == false)
	{
		HInputHandler *image_reader = HDB::GetHIOManager()->GetInputHandler(H_ASCII_TEXT(ImageDef->fileType()));
		H_ASSERT(image_reader);

		HC_KEY image_key;
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

		char tex_opts[MVO_BUFFER_SIZE];
		sprintf(tex_opts, "source=%s", newimageName);
		HC_Define_Texture(newimageName, tex_opts);
	}

	ImageDef->close();

	char color_cmd[MVO_BUFFER_SIZE];
	sprintf(color_cmd, "faces=%s", newimageName);
	HC_Set_Color(color_cmd);

	InsertClipRegion(pEnt);


	HPoint mesh_points[4];
	HPoint vcor[4];
	int index[6] = {5,0,1,2,3,0};

	Get_Image_Rectangle_For_Shell(pEnt, mesh_points);

	vcor[0].x = 0.0;    vcor[0].y = 0.0;    vcor[0].z = 0.0;
	vcor[1].x = 1.0;    vcor[1].y = 0.0;    vcor[1].z = 0.0;
	vcor[2].x = 1.0;    vcor[2].y = 1.0;    vcor[2].z = 0.0;
	vcor[3].x = 0.0;    vcor[3].y = 1.0;    vcor[3].z = 0.0;

	HC_KEY mesh_key = HC_KInsert_Shell(4, mesh_points, 6, index);
	HC_MSet_Vertex_Parameters(mesh_key, 0, 4, 3, (float *)vcor);
}
#ifdef WIN32
void HDWG_3dgsImporter::importAcDbTable(AcDbTable* pAcDbTable)
{
	char parent_name[MVO_BUFFER_SIZE];
	sprintf(parent_name,"AcDbTable_%p",pAcDbTable);
	HC_KEY table_key;
	table_key = HC_KOpen_Segment(parent_name);

	Acad::ErrorStatus err;
	AcDbVoidPtrArray table_element;
	err = pAcDbTable->explode(table_element);
	for(int i=0;i<table_element.length();i++)
	{
		AcRxObject* this_element = (AcRxObject*)table_element[i];
		if( this_element->isKindOf(AcDbEntity::desc()) )
			importAcDbEntity((AcDbEntity*) this_element,table_key);
		delete this_element;
	}
	HC_Close_Segment();
}
#endif 

void HDWG_3dgsImporter::importAcDbMLeader(AcDbMLeader* pAcDbMLeader)
{
	char parent_name[MVO_BUFFER_SIZE];
	sprintf(parent_name,"AcDbMLeader_%p",pAcDbMLeader);
	HC_KEY leader_key;
	leader_key = HC_KOpen_Segment(parent_name);

	Acad::ErrorStatus err;
	AcDbVoidPtrArray leader_element;
	err = pAcDbMLeader->explode(leader_element);
	for(int i=0;i<leader_element.length();i++)
	{
		AcRxObject* this_element = (AcRxObject*)leader_element[i];
		if( this_element->isKindOf(AcDbEntity::desc()) )
			importAcDbEntity((AcDbEntity*) this_element,leader_key);
		delete this_element;
	}
	HC_Close_Segment();
}

Adesk::Boolean HDWG_3dgsImporter::import_pline(const AcDbPolyline& lwBuf,
											   Adesk::UInt32 fromIndex,
											   Adesk::UInt32 numSegs,
											   AcDbEntity* pDatabaseEntity
											   ) const
{	
	if( !m_bDrawWireframe )
		return Adesk::kFalse;

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
			if(lwBuf.isClosed())
				key = HC_KInsert_Polyline(n_verts+1, polyline_pts);
			else
				key = HC_KInsert_Polyline(n_verts, polyline_pts);
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
				key = extrude_profile_along_line(n_verts+1, polyline_pts, &h_line_norm, line_thickness);
			else
				key = extrude_profile_along_line(n_verts, polyline_pts, &h_line_norm, line_thickness);
		}
		if(m_pConnectivityInfo)
			m_pConnectivityInfo->AddConnection(key, (void*) pDatabaseEntity);

		delete[] polyline_pts;
	}
	else
	{
		for( unsigned int i = 0; i < n_verts; i++ )
		{
			// opening a new segment for each element
			// because each of them may have a different line/marker thickness
			// The Optimize_Segment_tree will take care of this anyway
			HC_Open_Segment("");

			HC_KEY key = INVALID_KEY;
			// check the type of segment at ith vertex

			AcDbPolyline::SegType seg_type = lwBuf.segType(i);

			if( seg_type == AcDbPolyline::kLine )
			{
				AcGeLineSeg3d line_seg;
				lwBuf.getLineSegAt(i, line_seg);

				AcGePoint3d start_point = line_seg.startPoint();
				AcGePoint3d end_point = line_seg.endPoint();		

				key = HC_KInsert_Line ((float)start_point.x,(float)start_point.y,(float)start_point.z,
					(float)end_point.x,(float)end_point.y,(float)end_point.z);
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

				double h_major[3];
				h_major[0] = (float) (center_point.x + radius*cos_X_alpha);
				h_major[1] = (float) (center_point.y + radius*cos_X_beta);
				h_major[2] = (float) (center_point.z + radius*cos_X_theta);


				double cos_Y_alpha = Wx.dotProduct(Ay);
				double cos_Y_beta  = Wy.dotProduct(Ay);
				double cos_Y_theta = Wz.dotProduct(Ay);

				double h_minor[3];
				h_minor[0] = (float) (center_point.x + radius*cos_Y_alpha);
				h_minor[1] = (float) (center_point.y + radius*cos_Y_beta);
				h_minor[2] = (float) (center_point.z + radius*cos_Y_theta);

				double h_center[3];
				h_center[0] = (float)center_point.x;
				h_center[1] = (float)center_point.y;
				h_center[2] = (float)center_point.z;


				double h_start_angle = (double)start_ang/(2.0f*HDWG_F_PI);
				double h_end_angle = (double)end_ang/(2.0f*HDWG_F_PI);

				if((start_ang == 0.0) && (end_ang == HDWG_PI) && (n_verts ==2))
				{
					key = HC_DKInsert_Ellipse (h_center,h_major,h_minor);
#ifdef HIODWG_tESSELLATE_CIRCLE_ELLIPSE_SURFS
					HC_KEY shell_key = HC_Generate_Shell_From_Geometry(key, "");
					HC_Delete_By_Key(key);
					key = shell_key;
#endif // HIODWG_tESSELLATE_CIRCLE_ELLIPSE_SURFS
				}
				else{

					if(memcmp(h_center, h_major, 3 * sizeof(double)) && memcmp(h_center, h_minor, 3 * sizeof(double))){
						key = HC_DKInsert_Elliptical_Arc (h_center,h_major,h_minor, h_start_angle,h_end_angle);
					} else {
						HC_Open_Segment("");{
							h_center[0] = h_center[1] = h_center[2] = 0;
							h_major[0] = (double) (radius*cos_X_alpha);
							h_major[1] = (double) (radius*cos_X_beta);
							h_major[2] = (double) (radius*cos_X_theta);
							h_minor[0] = (double) (radius*cos_Y_alpha);
							h_minor[1] = (double) (radius*cos_Y_beta);
							h_minor[2] = (double) (radius*cos_Y_theta);
							HC_Translate_Object(center_point.x, center_point.y, center_point.z);
							key = HC_DKInsert_Elliptical_Arc (h_center,h_major,h_minor, h_start_angle,h_end_angle);
						}HC_Close_Segment();
					}
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

				key = HC_KInsert_Marker (h_point[0], h_point[1], h_point[2]);

			}


			// Set the line weight.
			// TODO: Handle different start and end weights
			double start_width = 0.0;
			double end_width = 0.0;
			lwBuf.getWidthsAt(i, start_width, end_width);
			if((start_width == end_width) && (start_width != 0.0))
			{
				//start_width = start_width * (H_MM_TO_POINTS/100.0);
				//HC_Set_Line_Weight(start_width);
				char element_size[MVO_BUFFER_SIZE];
				sprintf(element_size,"%g wsu", start_width);
				HC_Set_Variable_Edge_Weight(element_size);
				HC_Set_Variable_Line_Weight(element_size);
				HC_Set_Variable_Marker_Size(element_size);
			}


			if(m_pConnectivityInfo)
				m_pConnectivityInfo->AddConnection(key, (void*) pDatabaseEntity);

			HC_Close_Segment();
		}
	}

	return Adesk::kFalse;
}



Adesk::Boolean HDWG_3dgsImporter::import_mesh  (const Adesk::UInt32 rows,
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
	HPoint * h_points = new HPoint[nbVertex*3];
	HVector * h_normals = 0;

	for (unsigned int i = 0; i < nbVertex; i++) 
	{
		h_points[i].x	= (float)(pVertexList[i]).x;
		h_points[i].y	= (float)(pVertexList[i]).y;
		h_points[i].z	= (float)(pVertexList[i]).z;
	}

	if(!bAutoGenerateNormals && pVertexData)
	{
		// let's grab some normal data too. For now, do only vertex normals
		AcGeVector3d * acge_vtx_normals = pVertexData->normals();

		// TODO: Use the orientation flag to determine the handedness
		h_normals = new HVector[nbVertex*3];
		for(unsigned int i = 0; i < nbVertex; i++)
		{
			h_normals[i].x	= (float)(acge_vtx_normals[i]).x;
			h_normals[i].y	= (float)(acge_vtx_normals[i]).y;
			h_normals[i].z	= (float)(acge_vtx_normals[i]).z;
		}
	}

	HC_KEY shell_key;
	HC_KEY key = HC_KInsert_Mesh (rows, columns,h_points);
	if(h_normals)
		HC_MSet_Vertex_Normals(key, 0, nbVertex, h_normals);

	if(m_bDWGInsertMeshesAsShells) // convert the mesh in shell in case this variable is true
	{
		shell_key = HC_Generate_Shell_From_Geometry(key, "");
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
		shell_key = HC_KInsert_Shell(n_opt_points, opt_face_points, n_opt_face_list_indices, opt_index_list);

		// delete allocated memories.
		delete [] face_points;
		delete [] index_list;
		delete [] opt_face_points;
		delete [] opt_index_list;
	}

	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(shell_key, (void*) pDatabaseEntity);

	delete[] h_points;
	if(h_normals)
		delete[] h_normals;

	return Adesk::kFalse;
}

Adesk::Boolean HDWG_3dgsImporter::import_shell(const Adesk::UInt32 nbVertex,
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

	HC_KEY key = HC_KInsert_Shell (nbVertex, h_points, faceListSize,h_facelist);
	if(rgb_colors)
	{
		HC_MSet_Face_Colors_By_Value(key, "faces", 0, "rgb", faceCount, rgb_colors);
		delete[] rgb_colors;
	}
	if(vertex_colors)
	{
		HC_MSet_Vertex_Colors_By_Value(key, "faces",  0, "rgb", nbVertex, vertex_rgb_colors);
		delete[] vertex_rgb_colors;
	}

	if(h_normals)
		HC_MSet_Vertex_Normals(key, 0, nbVertex, h_normals);

	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(key, (void*) pDatabaseEntity);

	delete[] h_points;
	delete[] h_facelist;
	if(h_normals)
		delete[] h_normals;

	return Adesk::kFalse;
}

Adesk::Boolean HDWG_3dgsImporter::import_text  (const AcGePoint3d& position,
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

	char  h_text_alignment[16];
	double dtext_width=1.0;
	strcpy(h_text_alignment, "**");
	AcDbText * pAcDbText=(AcDbText*)pDatabaseEntity;
	if( pDatabaseEntity && (pDatabaseEntity->isKindOf(AcDbText::desc())) )
	{
		get_text_alignment(pAcDbText,h_text_alignment);
		dtext_width=pAcDbText->widthFactor();
	}

	HC_KEY key;
	char chWidth_Factor[100];
	sprintf(chWidth_Factor,"width scale=%f",dtext_width);
	HC_Set_Text_Font(chWidth_Factor);
	//key = import_text(h_point1, h_text_dir, h_normal, pMsg,h_text_alignment);

	// Transforms are handled generically (for planes other than XY) in this function. 
	//Beta << ASHISH.S. 17/08/2009.
	key = apply_transforms_and_insert_text(h_point1, h_text_dir, h_normal, pMsg, h_text_alignment);

	if(m_pConnectivityInfo)
		m_pConnectivityInfo->AddConnection(key, (void*) pDatabaseEntity);

	return Adesk::kFalse;
}

Adesk::Boolean HDWG_3dgsImporter::import_text(	const AcGePoint3d& position,
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
		((HDWG_3dgsImporter*)this)->m_bIsSHXFont = true;

	Acad::ErrorStatus es = pTextStyle.font(pTypeface, bold, italic, charset, pitch_family);

	text_size = pTextStyle.textSize();

	// HACK ALERT: This adjustment seems to make the text appear in almost same size in HOOPS as in DWG
	// Until we know for sure how to access DWG font info - Pavan Totala (04-Apr-06)
	if(text_size > 0.220000)
		text_size=text_size-0.0700000;

	pStyleName = pTextStyle.styleName();
	HC_Open_Segment("");
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

		char  h_text_alignment[16];
		strcpy(h_text_alignment, "<*v");
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
			get_text_alignment(pAcDbText, h_text_alignment);
			dtext_width=pAcDbText->widthFactor();

		}
		char chWidth_Factor[100];
		sprintf(chWidth_Factor,"width scale=%f",dtext_width);
		HC_Set_Text_Font(chWidth_Factor);

		HC_KEY key;

		//key = import_text(h_point1, h_text_dir, h_normal, pHText,h_text_alignment);

		// Transforms are handled generically (for planes other than XY) in this function. 
		//Beta << ASHISH.S. 17/08/2009.
		key = apply_transforms_and_insert_text(h_point1, h_text_dir, h_normal, pHText,h_text_alignment);

		if(m_pConnectivityInfo)
			m_pConnectivityInfo->AddConnection(key, (void*) pDatabaseEntity);

		char txt_opts[MVO_BUFFER_SIZE];

		if(m_bIsSHXFont)
		{
			wchar_t font_name[24] = L"";
			unsigned int i = 0;
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
			sprintf(txt_opts, "name = %s", H_ASCII_TEXT(font_name));

		}
		else if(pTypeface && wcscmp(pTypeface,L""))
			sprintf(txt_opts, "name = %s", H_ASCII_TEXT(pTypeface));
		else if(pStyleName && (wcscmp(pStyleName,L"")))
			sprintf(txt_opts, "name = %s", H_ASCII_TEXT(pStyleName));
		else
			sprintf(txt_opts, "name = system default");

		HC_Set_Text_Font(txt_opts);

		if(text_size > 0)
		{
			sprintf(txt_opts, "size = %f oru", text_size);
			HC_Set_Text_Font(txt_opts);
		}
		if( bold == Adesk::kTrue )
			HC_Set_Text_Font("bold");
		if( italic == Adesk::kTrue)
			HC_Set_Text_Font("italic");

		H_SAFE_DELETE_ARRAY(pHText);
	}
	HC_Close_Segment();

	//	if(pTypeface)
	//		delete pTypeface;

	// reset m_bIsSHXFont to false
	((HDWG_3dgsImporter*)this)->m_bIsSHXFont = false;

	return Adesk::kFalse;
}

HC_KEY HDWG_3dgsImporter::import_text(float my_center[], float my_path1[], float my_norm1[], wchar_t const * text, const char* alignment) const
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

	HC_KEY text_key = INVALID_KEY;

	float xrot = 0, yrot=0, zrot=0;
	float my_path[3], my_norm[3];

	HC_Compute_Normalized_Vector(my_path1, my_path);
	HC_Compute_Normalized_Vector(my_norm1, my_norm);

	xrot = asin(my_norm[1]);
	if(my_norm[2] < 0) xrot *= -1;
	xrot *= 180.0f/HDWG_F_PI;

	yrot = acos(my_norm[2]);
	if(my_norm[0] < 0) yrot *= -1;
	yrot *= 180.0f/HDWG_F_PI;

	zrot = acos(my_path[0]);
	if(my_path[1] < 0) zrot *= -1;
	zrot *= 180.0f/HDWG_F_PI;

	HC_Open_Segment("");
	{
		HC_Set_Text_Font("transforms");
		HC_Rotate_Object(xrot, yrot, zrot);
		HC_Translate_Object(my_center[0], my_center[1], my_center[2]);
		HC_Set_Text_Alignment(alignment);

		//HC_Set_Text_Font("outline = on");
		// what if this is a real UNICODE text?
		text_key = HC_KInsert_Text_With_Encoding(0,0,0, "wcs", (char const*)text);

	}
	HC_Close_Segment();

	return text_key;
}

HC_KEY HDWG_3dgsImporter::apply_transforms_and_insert_text(float my_center[], float my_path1[], float my_norm1[], wchar_t const * text, const char* alignment) const
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

	HC_KEY text_key = INVALID_KEY;
	HC_Open_Segment("");
	{
		HC_Set_Text_Font("transforms");

		// workaround for issue 10640
		if(m_bIsSHXFont == false)
			HC_Set_Text_Font("preference=(smaller = exterior, larger = default, cutoff = 0.04 sru)");
		else
			HC_Set_Text_Font("preference=(smaller = exterior, larger = default, cutoff = 0.1 sru)");

		HC_Set_Modelling_Matrix(h_matrix_trans);    
		HC_Set_Text_Alignment(alignment);
		//HC_Set_Text_Font("outline = on");
		// what if this is a real UNICODE text?

		text_key = HC_KInsert_Text_With_Encoding(0,0,0, "wcs", (char const*)local_text);      
	}
	HC_Close_Segment();

	H_SAFE_DELETE_ARRAY(local_text);
	return text_key;
}

void HDWG_3dgsImporter::importAcDbDimension(AcDbDimension* pAcDbDimension)
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
void HDWG_3dgsImporter::import_entity_linetype(AcDbEntity *pEnt, const AcDbLayerTableRecord *pLayerTableRecord)
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

void HDWG_3dgsImporter::import_entity_linetype(const AcDbObjectId& pLinetypeId, double linetype_scale)
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
			double dash_length = pLineTypeTableRecord->dashLengthAt(i)* linetype_scale;

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
		const wchar_t * line_type_name = 0;
		pLineTypeTableRecord->getName(line_type_name);
		size_t len=strlen(linestyle);
		linestyle[len-1]='\0';
		HC_Define_Line_Style(H_ASCII_TEXT(line_type_name), linestyle);
		HC_Set_Line_Pattern(H_ASCII_TEXT(line_type_name));
		pLineTypeTableRecord->close();
	} 
}

void HDWG_3dgsImporter::InsertMaskRegion(AcDbRasterImage* pEnt)
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
		HC_Set_Color("white");
		HC_Set_Visibility("faces = on");
		HC_Insert_Polygon(length, MaskRegionPts);
		HC_Set_Heuristics("concave polygons = on");

	}
}

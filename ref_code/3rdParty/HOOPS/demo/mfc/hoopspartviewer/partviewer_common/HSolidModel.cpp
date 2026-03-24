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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSolidModel.cpp,v 1.165 2010-06-30 21:45:01 chad Exp $
//

#include "stdafx.h"
#include <afxtempl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "hc.h"
#include "HStream.h"
#include "HOpcodeShell.h"
#include "HSUtility.h"
#include "HSInclude.h"
#include "HSolidModel.h"
#include "HTools.h"
#include "CSolidHoopsApp.h"
#include "CMultiModelDlg.h"
#include "HUtilityXMLParser.h"
#include "HIOManager.h"
#include "HUtilityLocaleString.h"
#include "HEventManager.h"
#include "vhash.h"

#ifndef HOOPS_ONLY
#include "CBinaryFileToolkit.h"
#endif // HOOPS_ONLY

#ifdef GRANITE
#include "KUtils.h"
#endif // GRANITE

#ifdef INTEROP
#include "InterOpFileIO.h"
#endif // INTEROP

#ifdef ACIS
#include "entity_mgr_factory.hxx"
#include "asm_api.hxx"
#include "asm_assembly.hxx"
#endif // ACIS

extern CSolidHoopsApp theApp;

HSolidModel::HSolidModel() 
#ifdef ACIS
			: m_modelList(ASM_NO_HOLD)
#endif // ACIS
{
#ifndef HOOPS_ONLY
	m_mi = 0;
#endif // HOOPS_ONLY

#ifdef PARASOLID
	PK_PARTITION_create_empty(&m_partition);
#endif // PARASOLID

	m_bSolidModel = false;
	m_bSolidData = false;
	m_bPlainSolidModel = false;
	SetBRepGeometry(false);
	m_MultiSelectManager = new MultiSelectManager();

	m_model_handedness = HandednessNotSet;
	m_TopologyManager = new BREP_Topology;
	m_pPMIConnector = new HIOConnector;
	m_pConnector = new HIOConnector;
	//m_coord_sys_handedness = HandednessRight;

#ifdef GRANITE
	m_componentList = KComponentList::create();
#endif // GRANITE

#ifdef ACIS
	mhash_CompHandle_2_EEList = 0;
	curr_hs = &model_hs;
	SetHistoryStream();
#endif // ACIS

#ifdef INTEROP
	iop_fio = new InterOpFileIO(this);
#endif // INTEROP

}

HSolidModel::~HSolidModel()
{
	// Model cleanup : delete all the entities from the 
	// partition associated with this model
	DeleteAllEntities();
	delete m_MultiSelectManager;

	delete m_TopologyManager;
	delete m_pConnector;
	delete m_pPMIConnector;
	
#ifdef INTEROP
	delete iop_fio;
#endif // INTEROP
}

//======================================================================
//	Function :		HSolidModel::DeleteAllEntities
//	Description :	Deletes all the entities in the current model from the 
//					modeller and associated HOOPS geometry
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void HSolidModel::DeleteAllEntities()
{
#ifndef HOOPS_ONLY
	H_SAFE_DELETE(m_mi);
#endif // HOOPS_ONLY

#ifdef PARASOLID
	int n_bodies;
	PK_BODY_t	*bodies;
	PK_PARTITION_ask_bodies(m_partition, &n_bodies, &bodies);
	for(int i = 0; i < n_bodies; i++)
		DeleteParasolidEntity( bodies[i] );

	if (n_bodies > 0)
		PK_MEMORY_free(bodies);
#endif // PARASOLID

#ifdef ACIS
	HA_Delete_Entity_Geometry(m_entityList);

	SetHistoryStream();

	DELTA_STATE *ds;
	outcome o = api_note_state(ds);
	CHECK_OUTCOME(o);

	o = api_del_entity_list(m_entityList);
	CHECK_OUTCOME(o);

	o = api_note_state(ds);
	CHECK_OUTCOME(o);

	m_entityList.clear();

	if(mhash_CompHandle_2_EEList)
	{
		vlist_s *temp_list = new_vlist(malloc,free);
		vhash_to_vlist(mhash_CompHandle_2_EEList, temp_list, malloc);
		vhash_pair_t * handle_list_pair;
		while(handle_list_pair = (vhash_pair_t *) vlist_remove_first(temp_list)) 
		{
			EE_LIST *model_refs = (EE_LIST *)handle_list_pair->item;
			if(model_refs)
				api_del_entity(model_refs);
		}

		delete_vhash(mhash_CompHandle_2_EEList);
		delete_vlist(temp_list);
		mhash_CompHandle_2_EEList = 0;
	}
#endif // ACIS

#ifdef GRANITE
	m_componentList->clear();
#endif // GRANITE


}

#ifdef ACIS
EE_LIST* HSolidModel::GetEEListForComponent(component_handle* comp_handle)
{
	EE_LIST* ret_eelist = 0;
	if( !mhash_CompHandle_2_EEList )
		mhash_CompHandle_2_EEList = new_vhash(512, malloc, free);

	if( VHASH_STATUS_SUCCESS != vhash_lookup_item(mhash_CompHandle_2_EEList, 
												  comp_handle, (void**) &ret_eelist) )
	{
		// create a EE_LIST of ASM_MODEL_REFs
		outcome o;

		asm_model* root_model = 0;
		entity_handle_list model_refs;
		o = asmi_component_get_root_model(comp_handle, root_model);
		o = asmi_component_get_path(comp_handle, root_model, model_refs);

		ret_eelist = ACIS_NEW EE_LIST();
		ret_eelist->set_ownership(false);
		ret_eelist->init();
		model_refs.init();
		for (entity_handle* ent_handle = model_refs.first(); 
			ent_handle != NULL; ent_handle = model_refs.next())
		{
			ENTITY* ent = ent_handle->entity_ptr();
			ret_eelist->add(ent);
		}

		vhash_insert_item(mhash_CompHandle_2_EEList, (void*) comp_handle, (void*)ret_eelist);
	}

	return ret_eelist;
}
#endif	// ACIS

#ifdef PARASOLID
void HSolidModel::DeleteParasolidEntity( PK_ENTITY_t entity)
{
	HP_Delete_Entity_Geometry(1, &entity);
	PK_ENTITY_delete(1, &entity);
}
#endif // PARASOLID


#ifdef ACIS
void HSolidModel::SetHistoryStream ( HISTORY_STREAM * new_hs ) {
	outcome o;
	if (new_hs && new_hs != curr_hs) {
		o = api_set_default_history(new_hs);
		CHECK_OUTCOME(o);
		curr_hs = new_hs;
	}
	else {
		o = api_set_default_history(curr_hs);
		CHECK_OUTCOME(o);
	}
}

void HSolidModel::DeleteAcisEntity( ENTITY* entity)
{
	ENTITY_LIST elist;
	elist.add(entity);
	HA_Delete_Entity_Geometry(elist);
	// delete the ACIS body
	api_del_entity(entity);
	m_entityList.remove(entity);
}
void HSolidModel::AddAcisEntity( ENTITY* entity)
{
	m_entityList.add(entity);
}
void HSolidModel::RemoveAcisEntity( ENTITY* entity)
{
	m_entityList.remove(entity);
}
#endif // ACIS

#ifdef GRANITE
void HSolidModel::DeleteGraniteEntity( KObj_ptr entity )
{
	HG_Delete_Entity_Geometry(entity);

	//	// remove the entity from granite session
	//	RemoveGraniteEntity(entity);
}
void HSolidModel::AddGraniteEntity( KObj_ptr entity)
{
	assert(0);
	//	m_entityList->append(entity);
}
void HSolidModel::RemoveGraniteEntity( KObj_ptr entity)
{
	assert(0);
	//	// TODO_IMPLEMENT - DELETE ENTITY FROM GRANITE
	//	int n_ele = m_componentList->getarraysize();
	//	for( int i_ele = 0; i_ele < n_ele; i_ele++ )
	//	{
	//		if( m_componentList->get(i_ele) == entity )
	//		{
	//			m_componentList->removerange(i_ele, i_ele+1);
	//			break;
	//		}
	//	}
}
#endif // GRANITE

#ifdef ACIS
logical HSolidModel::HA_Read_Asat_File(const char* fname, asm_model_list& model_list)
{
	FILE * fp = NULL;
	ENTITY* entity = 0;
	outcome oc;
	logical res = TRUE;

	fp = fopen(fname, "r");
	res = (fp != NULL);

	if (res)
	{
		entity_mgr_factory* pEntity_Mgr_Factory;
		outcome o = asmi_get_entity_mgr_factory(pEntity_Mgr_Factory);
		check_outcome(o);

		// Retrieve a list of all models from file
		asm_restore_options ropts;
		ropts.set_entity_mgr_factory( pEntity_Mgr_Factory );
		oc =  asmi_restore_model_list(fp, TRUE, model_list, &ropts);
		res = oc.ok();
	}

	if (fp)
		fclose(fp);

	return res;
}

#endif // ACIS

void HSolidModel::MultiModelSelectionCallback(char const * in_container, int in_num_configs, char const ** in_configs, 
		int & out_config_selection)
{
	CMultiModelDlg mm_dlg(0, in_container, in_num_configs, in_configs);
	mm_dlg.DoModal();

	out_config_selection = mm_dlg.GetConfigSelection();	
}


// our application-specific read function
HFileInputResult HSolidModel::Read(wchar_t const * FileName, HBaseView * view) 
{   
	// This process is going to take sometime, convey that to the user
	CWaitCursor show_hourglass_cursor_through_this_function;

	HFileInputResult success = InputOK;
	wchar_t extension[64];
	wchar_t const * ext = wcsrchr(FileName, L'.');

	if(!ext)
		return InputBadFileName;

	++ext; //move one past the dot;

	// in case we have a Pro/E file which ends with a number, e.g., *.prt.1 or *.xas.1
	bool good_filename = true;
	wchar_t *filename_copy = 0;
	if ( good_filename && ext[0] >= L'0' && ext[0] <= L'9' ) { 
		if (filename_copy == 0) {
			int original_filename_len = (int)wcslen(FileName);
			filename_copy = new wchar_t [original_filename_len + 1];
			swprintf(filename_copy, original_filename_len, L"%ls", FileName);
			filename_copy[original_filename_len] = '\0';
		}
		wchar_t *bad_ext = wcsrchr(filename_copy, L'.');
		bad_ext[0] = '\0';
		ext = wcsrchr(filename_copy, L'.');
		if (!ext)
			good_filename = false;
		else
			ext++;
	}

	if (ext)
		swprintf(extension, 64, L"%ls", ext);

	if (filename_copy)
		delete [] filename_copy;

	if (!good_filename)
		return InputBadFileName;

#ifdef PARASOLID
	// read the file into the model object's model segment
	HP_Set_Hash_Level(0);
#endif // PARASOLID

	HC_Open_Segment_By_Key(m_ModelKey);	
	// we should maybe read ach file into it's own subsegment of the main model segment 
	// however I am keeping with reading it into the modelkey directly so that reading
	// and writing out a file doesn't result in nesting occuring.  Gavin
#ifdef INTEROP
	if (wcsieq(extension, L"catpart") || wcsieq(extension, L"catproduct") || wcsieq(extension, L"cgr") ||
		wcsieq(extension, L"model")   || wcsieq(extension, L"session")    || wcsieq(extension, L"exp") ||
		wcsieq(extension, L"prt")     || wcsieq(extension, L"xpr")        ||
		wcsieq(extension, L"asm")     || wcsieq(extension, L"xas")        ||
		wcsieq(extension, L"igs")     || wcsieq(extension, L"iges")       ||
		wcsieq(extension, L"stp")     || wcsieq(extension, L"step")       ||
		wcsieq(extension, L"vda")     ||
		wcsieq(extension, L"sldprt")  || wcsieq(extension, L"sldasm")	  ||
		wcsieq(extension, L"ipt")	  || wcsieq(extension, L"iam")
#ifdef ACIS
		|| wcsieq(extension, L"x_t") || wcsieq(extension, L"x_b")
#endif // ACIS
#ifdef PARASOLID
		|| wcsieq(extension, L"sat") || wcsieq(extension, L"sab")
#endif // PARASOLID
		) {
			m_bSolidModel = true;
			m_bSolidData = true;
			SetBRepGeometry(true);
			SetModelHandedness(HandednessSetLeft);
#ifdef ACIS
		DELTA_STATE *ds;
		outcome o = api_note_state(ds);
		CHECK_OUTCOME(o);
#endif // ACIS
		success = iop_fio->Import(FileName, extension, (HSolidView *)view);
#ifdef ACIS
		o = api_note_state(ds);
		CHECK_OUTCOME(o);

		SetHistoryStream();
		o = api_note_state(ds);
		CHECK_OUTCOME(o);
#endif // ACIS
	}
#if 0
	else if (!wcsnicmp(extension, L"tsf", wcslen(L"tsf"))) {
		PartInstance *pinst = new PartInstance();
		pinst->is_asm = true;
		SetEntHash(new VHash<ENTITY *, PartInstance *>());
		HStreamFileToolkit tk;
		tk.SetOpcodeHandler(TKE_Comment, new TK_ASMComment(this, pinst));
		tk.SetPrewalkHandler(new TK_ASMComment(this, pinst));
		tk.SetPostwalkHandler(new TK_ASMUser_Data(this, pinst));

		HC_Open_Segment_By_Key(GetModelKey());
			HTK_Read_Stream_File(FileName, &tk);
		HC_Close_Segment();

		SetPartHash(new VStringHash<PartInstance *>());
		GetPartHash()->InsertItem("root", pinst); 

		m_bSolidModel = true;
		m_bSolidData = true;
	}
#endif
#endif // INTEROP
#ifdef PARASOLID
#ifdef INTEROP
	else
#endif // INTEROP
		if  (wcsieq(extension, L"xmt_txt") || wcsieq(extension, L"x_t") || wcsieq(extension, L"x_b") ) 
		{
			m_bSolidModel = true;
			m_bSolidData = true;
			SetBRepGeometry(true);
			SetModelHandedness(HandednessSetLeft);

			PK_PART_receive_o_t options;
			PK_ERROR_code_t		result;

			PK_PART_receive_o_m(options);

			if (CAppSettings::bBinaryX_TFiles || wcsieq(extension, L"x_b") )
				options.transmit_format = PK_transmit_format_neutral_c;
			else
				options.transmit_format = PK_transmit_format_text_c;

			result = HP_Read_Xmt_File(FileName, GetPartition(), 0, 0, &options);	// read an XMT file
			if( result == PK_ERROR_schema_access_error )
			{
				TCHAR str[MVO_BUFFER_SIZE];
				_stprintf(str, _T("Could not find schema files at specified path:  %s\nUse the 'Tools-Options' dialog to set them correctly or define P_SCHEMA environment variable."), CAppSettings::SchemaPath);
				AfxMessageBox( str,	MB_ICONINFORMATION | MB_OK );	
			}
			else if( result != PK_ERROR_no_errors )
				AfxMessageBox( _T("Failed to read Parasolid file. HP_Read_Xmt_File returned an error"),	MB_ICONINFORMATION | MB_OK );	

			if (result < 0) 
				success = InputFail;
		} 
#endif // PARASOLID
#ifdef ACIS
#ifdef INTEROP
		else
#endif // INTEROP
			if  (!wcsnicmp(extension, L"sat", wcslen(L"sat")))
			{  
				ENTITY_LIST elist;
				ENTITY* entity;

				m_bSolidModel = true;
				m_bSolidData = true;
				SetBRepGeometry(true);
				SetModelHandedness(HandednessSetLeft);

				logical read_sat_result = HA_Read_Sat_File(H_ASCII_TEXT(FileName), elist);	// read an SAT file
				if( read_sat_result == FALSE )
				{
					AfxMessageBox(_T("Failed to read SAT file. The file may be corrupt or from later version of ACIS."));
					success = InputFail;
				}

				elist.init();						// set next() function to return first element in "list"
				while (entity = elist.next())
				{
					m_entityList.add(entity);
				}
			} 
			else if( !wcsnicmp(extension, L"asat", wcslen(L"asat")) )
			{  
				m_bSolidModel = true;
				m_bSolidData = true;
				SetBRepGeometry(true);
				SetModelHandedness(HandednessSetLeft);

				logical read_asat_result = HA_Read_Asat_File(H_ASCII_TEXT(FileName), m_modelList);
				if( read_asat_result == FALSE )
				{
					AfxMessageBox(_T("Failed to read ASAT file. The file may be corrupt or from later version of ACIS."));
					success = InputFail;
				}
				else
				{
					// render the entities
					m_modelList.init();
					asm_model* this_model = m_modelList.next();
					while (this_model)
					{
						MODEL_BEGIN(this_model)
							HA_Render_Model(this_model, "entity");
							//this_model->get_top_level_entities(m_entityList, TRUE);
							//HA_Render_Entities(m_entityList);
						MODEL_END(ASM_NO_CHANGE)

						this_model = m_modelList.next();
					}
				}

			} 

#endif // ACIS
#ifdef GRANITE

			if(		wcsstr(extension, L"prt")
				||  wcsstr(extension, L"asm") 
				||	wcsstr(extension, L"igs")
				||  wcsstr(extension, L"iges")
				||  wcsstr(extension, L"sat")
				||	wcsstr(extension, L"stp") 
				||  wcsstr(extension, L"step")
				||	wcsstr(extension, L"vda") 
				||	wcsstr(extension, L"g") 
				||	wcsstr(extension, L"x_t")
				||  wcsstr(extension, L"xmt_txt")
				||  wcsstr(extension, L"x_b"))
			{  
				m_bSolidModel = true;
				m_bSolidData = true;
				SetBRepGeometry(true);

				HG_Read_File(H_ASCII_TEXT(FileName), m_componentList);	// read a Granite file
				if(		wcsstr(extension, L"igs")
					||  wcsstr(extension, L"iges")
					||	wcsstr(extension, L"stp")
					||  wcsstr(extension, L"step")
					||	wcsstr(extension, L"vda")
					||	wcsstr(extension, L"g")
					)
					SetModelHandedness(HandednessSetNone);
				else
					SetModelHandedness(HandednessSetLeft);

				// We use instancing in HG bridge. This causes sharing of segments accross 
				// the files. To avoid that...  - Rajesh B
				CleanIncludes();

			} 
#endif // GRANITE
#ifdef HOOPS_ONLY
			if(	wcsieq(extension, L"") )
			{
				AfxMessageBox(_T("Failed to read file. Unrecognized file extension."));
			}
#endif // HOOPS_ONLY			
			else
			{
				// we don't know what extensions the base class is capable of handling
				// let it try and read the file whatever the extension might be

#ifndef HOOPS_ONLY				
				if (wcsieq(extension, _T(KERN_STREAM_FILE)))
					m_bSolidModel = true;
				else
#endif
					m_bSolidModel = false;
			
				SetBRepGeometry(false);
				if (wcsieq(extension, L"dwg") || wcsieq(extension, L"dxf")|| wcsieq(extension, L"dgn"))
				{
					HInputHandlerOptions options;
					wchar_t * p_dwg_textures_dir = 0;
					if(CAppSettings::DWGTextureDirectory.IsEmpty() == FALSE)
					{
						 H_WCS wcs(CAppSettings::DWGTextureDirectory);
						 p_dwg_textures_dir = wcsdup(wcs.encodedText());
					}
					options.m_pHBaseView = view;
					options.m_pExtendedData = (void*) p_dwg_textures_dir;
					options.m_bInputViaHSF = CAppSettings::bImportDWGviaBstream;
					options.m_Deviation = atof(H_ASCII_TEXT(CAppSettings::DWGDeviation));
					options.m_bImportMetadata = CAppSettings::bImportDWGXData;
					options.m_bImportAllLayouts = CAppSettings::bImportAllLayouts;

					//For DGN
					options.m_bIgnoreOffEntities = CAppSettings::bIgnoreInvisibleEntities;
					options.m_coneFactor = atof(H_ASCII_TEXT(CAppSettings::DGNFactorForCone));
					options.m_factorForSmartSolids = atof(H_ASCII_TEXT(CAppSettings::DGNFactorForSmartSolids ));

					success = HBaseModel::Read(FileName, 0, true, &options);

					if(p_dwg_textures_dir)
						free(p_dwg_textures_dir);
				}
				else
				{					
 					HInputHandlerOptions opt;
					// PRC options
					opt.m_pPRCPMIConnector = m_pPMIConnector;
					opt.m_pPRCTopologyManager = m_TopologyManager;
					opt.m_bPRCMergeFaces = !CAppSettings::bPrcFaceEdgeVertexSelectability;
					opt.m_pPRCMultiModelSelectionCallback = MultiModelSelectionCallback;

					// Other options
					opt.m_pConnector = m_pConnector;
					opt.m_tk = GetStreamFileTK();
					opt.m_pHBaseView = view;
					opt.m_bImportMetadata = CAppSettings::bImportDWGXData;;
  					success = HBaseModel::Read(FileName, view, true, &opt);
					m_pPRCAsmModelFile = opt.m_pPRCAsmModelFile;
					HObjectManager::FileLoadHObjectCheck(GetModelKey());
					if (opt.m_bPRCWrongVersion)
					{
								MessageBox(0, H_TEXT(L"PRC Import requires functionality that is not available in your version of Acrobat.\nPlease update to the latest version of Acrobat to view this file."), _T("ERROR!"), MB_OK);
								success = InputOK;
					}

				}
			}
			// update the polygon handedness for this model
			UpdateModelHandedness();

#ifdef PARASOLID
				if ( m_bSolidModel && m_bSolidData )
				{
					HC_Set_Rendering_Options("cut geometry options = (level = segment tree)");
				}
#endif // PARASOLID

			HC_Close_Segment();
#if 0
			if( m_bSolidModel )
				GenerateLODsForBodies();
#endif
			return success;
}

HFileOutputResult HSolidModel::WriteWithOptions(const wchar_t * FileName, HBaseView * pHView, HOutputHandlerOptions * options )
{
	int version = options->Version();
	int width  = options->WindowWidth();
	int height = options->WindowHeight();

	// This process is going to take sometime, convey that to the user
	CWaitCursor show_hourglass_cursor_through_this_function;
	HFileOutputResult result = OutputOK;

	wchar_t extension[MVO_BUFFER_SIZE];
	if(!FileName || wcslen(FileName) > MVO_BUFFER_SIZE) 
	{
		AfxMessageBox(_T("Failed to write file. Empty filename or filename too long."));
		return OutputBadFileName;
	}
	HUtility::FindFileNameExtension(FileName, extension);


#ifdef PARASOLID
	if  (wcsieq(extension, L"xmt_txt") || wcsieq(extension, L"x_t")) 
	{
		if (!m_bSolidModel)
			result = OutputFail;
		else
		{

			int						n_bodies;
			PK_BODY_t				*bodies;
			PK_PART_transmit_o_t	options;
			PK_ERROR_code_t			PK_result;

			/*	if (strncmp(extension,"xmt_txt",7)==0 || strncmp(extension,"x_t",3)==0)
			{
			char VersionFileName[MVO_BUFFER_SIZE];

			strcpy(VersionFileName,FileName);
			char num[MVO_BUFFER_SIZE];
			if (strncmp(extension,"xmt_txt",7)==0)
			strcpy(num,&extension[7]);
			else
			strcpy(num,&extension[3]);

			VersionFileName[strlen(VersionFileName)-strlen(num)]=0;

			*/	

			PK_PART_transmit_o_m(options);
			options.transmit_version=version;

			if (CAppSettings::bBinaryX_TFiles)
				options.transmit_format = PK_transmit_format_neutral_c;
			else
				options.transmit_format = PK_transmit_format_text_c;

			PK_PARTITION_ask_bodies(m_partition, &n_bodies, &bodies);
			PK_ASSEMBLY_t *assemblies;
			int n_assemblies;
			PK_PARTITION_ask_assemblies(m_partition, &n_assemblies, &assemblies);
			PK_PART_t *parts = new PK_PART_t[n_assemblies+n_bodies];
			int n_parts = 0;
			int i;
			for (i=0;i<n_bodies;i++)
			{
				int numref;
				PK_PART_ask_ref_instances(bodies[i],&numref,0);
				if (!numref)
					parts[n_parts++] = bodies[i];
			}

			for (i=0;i<n_assemblies;i++)
			{
				int numref;
				PK_PART_ask_ref_instances(assemblies[i],&numref,0);
				if (!numref)
					parts[n_parts++] = assemblies[i];
			}

			PK_PARTITION_set_current(m_partition);

			PK_result = HP_Write_Xmt_File((FileName), n_parts, parts, &options);	// write an XMT file

			if (PK_result < 0) result = OutputFail;

			if (n_bodies > 0)
				PK_MEMORY_free(bodies);
			if (n_assemblies > 0)
				PK_MEMORY_free(assemblies);
			delete parts;

		}
	}
#endif // PARASOLID

#ifdef ACIS
	if (wcsieq(extension, L"sat"))
	{
		// we get the version in int form and HA api wants in float
		// for eg. for ACIS 6.0 we get version num as 60, so divide
		// by 10.0 before passing it on the HA api - Rajesh B (9-Mar-01)
		version = CAppSettings::ModelerExportFileVer;
		if (m_entityList.iteration_count() > 0)
			HA_Write_Sat_File_2(H_ASCII_TEXT(FileName), m_entityList, (float) version/10.0f);
	}
#endif // ACIS

#ifdef GRANITE
	// ProE files tend to have strange extensions like crap.prt.1 or junk.asm.1
	// here is workaround that stuff - Rajesh B (11-Oct-01)
	if(strstr("1234567890", extension) )
	{
		extension[0]='\0';
		HC_Parse_String(FileName,".",-2,extension);
	}
	if(	streq(extension,"prt") )
	{  
		assert( m_componentList->get(0) );
		assert( m_componentList->get(0)->GetModel() );
		HG_Write_File(FileName, m_componentList->get(0)->GetModel() );
	}
	else if(	streq(extension,"asm") 
		/*||	streq(extension,"igs") || streq(extension,"iges")
		||	streq(extension,"stp") || streq(extension,"step")
		||	streq(extension,"vda")*/ )
	{
		assert( m_componentList->get(0) );
		if( m_componentList->get(0)->GetAssembly() )
			HG_Export_Assembly(FileName, m_componentList->get(0)->GetAssembly() );
		else
			HG_Export_Part(FileName, m_componentList->get(0));
	}

#endif // GRANITE
#ifdef HOOPS_ONLY
	if(	wcsieq(extension, L"") )
	{
		AfxMessageBox(_T("Failed to write file. Unrecognized file extension."));
	}
#endif // HOOPS_ONLY
	else
	{
		result = HBaseModel::WriteWithOptions( FileName, pHView, options);
	}
	UNREFERENCED(version);
	UNREFERENCED(width);
	UNREFERENCED(height);

	return result;
}

// our application-specific write function
bool HSolidModel::Write(const wchar_t * FileName, HBaseView * m_pHView, int version, int width, int height) 
{ 
	bool success = true;

	HOutputHandlerOptions options;
	options.m_pHBaseView = m_pHView;
	options.m_Image_Dpi = CAppSettings::DPI;
	options.m_Window_Width = width;
	options.m_Window_Height = height;
	options.m_bConserveMemory = CAppSettings::bConserveMemory;
	options.m_Version = version;

	if(!HBaseModel::WriteWithOptions( FileName, m_pHView, &options))
		success = false;

	return success;
}


//======================================================================
//	Function :		HSolidModel::UpdateModelHandedness
//	Description :	Sees if any polygon handedness is set on the model
//					key and updates the member variable. There are four
//					possible values
//					1. HandednessSetLeft - explicitly set polygon left handeness
//					2. HandednessSetRight - explicitly set polygon right handeness
//					3. HandednessSetNone - explicitly set no polygon handeness
//					4. HandednessNotSet - polygon handedness attribute not set
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void HSolidModel::UpdateModelHandedness()
{
	// see if handedness attribute was defined in the model,
	// if yes set our member variable
	// what is the polygon handedness for this model
	HC_Open_Segment_By_Key(GetModelKey());
	if (HC_Show_Existence("heuristics"))
	{
		unsigned int token_num = 0;
		char heuristics[MVO_BUFFER_SIZE], token[MVO_BUFFER_SIZE];
		HC_Show_Heuristics(heuristics);
		while(HC_Parse_String(heuristics,",",token_num++,token))
		{
			if (strstr(token,"polygon handedness"))
			{
				HC_Parse_String(token,"=",token_num++,token);
				if (strstr(token,"left") )
					m_model_handedness = HandednessSetLeft;
				else if (strstr(token,"right") )
					m_model_handedness = HandednessSetRight;
				else
					m_model_handedness = HandednessSetNone;
			}
		}
	}
	else
		m_model_handedness = HandednessNotSet;
	HC_Close_Segment();
}

//======================================================================
//	Function :		HSolidModel::SetModelHandedness
//	Description :	Sets the given modelhandedness on to the model key
//					This handedness get hardcoded in hmf/hsf files when
//					you save it.
//	Return :void	-	
//	Parameters :
//			ModelHandedness handedness	-	
//	Note :
//======================================================================
void HSolidModel::SetModelHandedness(ModelHandedness handedness)
{
	m_model_handedness = handedness; 

	HC_Open_Segment_By_Key(GetModelKey());

	if( m_model_handedness == HandednessSetLeft )
		HC_Set_Heuristics("polygon handedness = left");
	else if( m_model_handedness == HandednessSetRight )
		HC_Set_Heuristics("polygon handedness = Right");
	else if( m_model_handedness == HandednessSetNone )
		HC_Set_Heuristics("no polygon handedness");

	HC_Close_Segment();

}



//======================================================================
//	Function :		HSolidModel::SetBRepGeometry
//	Description :	Override the base class function to add setting of
//				user value on the segment. This helps in HNet, when we
//				emit this segment the peers understand our rendermode
//				setting better.
//	Return :void	-	
//	Parameters :
//			bool brep	-	
//	Note :
//======================================================================
void HSolidModel::SetBRepGeometry(bool brep)
{
	if (brep)
	{
		HC_KEY key = GetModelKey();
		HC_Open_Segment_By_Key(key);
		HC_Set_User_Value(1L);
		HC_Close_Segment();
	}

	HBaseModel::SetBRepGeometry(brep);
}

//======================================================================
//	Author :Rajesh B			Created : 9/19/2001 6:43:53 PM
//======================================================================
//	Function :		HSolidModel::UpdateModelGeometryType
//	Description :	Reads if any user value is set on the modelkey and 
//					sets the geometry type of the model accordingly
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
long HSolidModel::UpdateModelGeometryType()
{
	HC_Open_Segment_By_Key(GetModelKey());
	HC_POINTER_SIZED_INT value = 0L;
	if (HC_Show_Existence("user value"))
	{
		HC_Show_User_Value(&value);
		if (value == 1L)
			SetBRepGeometry(true);
		if (value == 2L)
			SetFEAGeometry(true);
		if (value == 3L)
			SetVectorGeometry(true);
	}
	else
	{
		SetBRepGeometry(false);
		SetFEAGeometry(false);
		SetVectorGeometry(false);
	}
	HC_Close_Segment();

	return value;
}


//======================================================================
//	Author :Rajesh B			Created : 11/1/2001 12:12:26 PM
//======================================================================
//	Function :		HSolidModel::GenerateLODsForBodies
//	Description :	Finds out each body in the current model and generates
//					LODS. The HUtility::Generate_LODs will recurse all the 
//					shells in the segment, merge them and generate LODs 
//					for this merged shell.
//	Return :void	-	
//	Parameters :
//	Note :
//======================================================================
void HSolidModel::GenerateLODsForBodies()
{
#ifndef HOOPS_ONLY

	int nb = 0;
	HC_KEY	keys[40000];

#ifdef PARASOLID
	PK_BODY_t* bodies;
	PK_ERROR_t err = PK_PARTITION_ask_bodies(m_partition, &nb, &bodies);
	assert(err == PK_ERROR_no_errors);
#endif //PARASOLID

#ifdef ACIS
	nb = m_entityList.iteration_count();
#endif // ACIS

#ifdef GRANITE
	KBodyList_ptr bodies = KBodyList::create();
	KGetSolidBodiesFromComponents( m_componentList, bodies );
	nb = bodies->getarraysize();
#endif // GRANITE

	for (int ib = 0; ib < nb; ib++)
	{
		// get the segment corresponding to this body
		int count = 0;

#ifdef PARASOLID
		count = HP_Compute_Geometry_Keys(bodies[ib], 1, keys, "bodies");
#endif //PARASOLID
#ifdef ACIS
		count = HA_Compute_Geometry_Keys(m_entityList[ib], 1, keys, "bodies");
#endif // ACIS
#ifdef GRANITE
		count = HG_Compute_Geometry_Keys(KObj::cast(bodies->get(ib)), 1, keys, "bodies");
#endif // GRANITE

		if( count == 1 )
		{
			char key_type[MVO_BUFFER_SIZE];
			HC_Show_Key_Type(keys[0], key_type);
			if (streq(key_type, "segment")) 
			{
				HC_Open_Segment_By_Key( keys[0] );
				//	HUtility::Generate_LODs( bool do_recurse , bool delete_orig_shells, bool insert_null_lods, 
				//							int n_lod_levels, float reduction_ratio );
				HUtility::Generate_LODs(true, false, true, 2, 0.20f);
				HC_Close_Segment();
			}
		}
	}

#ifdef PARASOLID
	if( nb > 0 )
		PK_MEMORY_free(bodies);
#endif //PARASOLID

#endif // HOOPS_ONLY
}

#ifndef HOOPS_ONLY

void TK_ModelStructure_XML::MakeType(HUtilityXMLGenerator *xmlgen, char *tname, char *imagename, bool selectable) 
{
	HUtilityXMLTag xmlt;
	xmlt.SetTagname("Type");
	xmlt.AddProperty("Name", tname, true);
	xmlt.AddProperty("Image", imagename, true);
	xmlt.AddPropertyInt("Selectable", (int)selectable);
	xmlt.SetOpen(false);
	xmlgen->AddTag(&xmlt);
}

void TK_ModelStructure_XML::MakeEntity(HUtilityXMLGenerator *xmlgen, HUtilityXMLTag *xmlt, char *name, char *type,int tagid, bool keepopen) 
{
	xmlt->SetTagname("Object");
	xmlt->AddProperty("Name", name, true);
	xmlt->AddProperty("Type", type, true);
	xmlt->AddPropertyInt("Identifier", tagid);
	xmlt->SetOpen(keepopen);
	xmlgen->AddTag(xmlt);
}



void HSolidModel::SetupModelStructureWriteFromHSF(HStreamFileToolkit *mytool)
{
	mytool->SetPostwalkHandler (new TK_ModelStructure_XML (this, mytool));
	mytool->SetOpcodeHandler (TKE_XML, new TK_ModelStructure_XML (this, mytool));
}

#ifdef GRANITE

int	TK_ModelStructure_XML::GetTagID(KERN_ENTITY entity) 
{
	HC_KEY key;
	int index = -1;
	if (HG_Compute_Geometry_Keys(entity, 1, &key,"bodies,faces,edges"))
		m_pStreamFileToolkit->KeyToIndex(key, index);
	else 
		return -1;
	return index;
}

void	TK_ModelStructure_XML::WriteEntity(HUtilityXMLGenerator *xmlgen, KERN_ENTITY entity) 
{    
	char temptext[4096];
	if (entity)
	{

		KERN_CLASS_TYPEDEF eclass = entity->giveRtti();
		if (eclass == KERN_BODY_TYPE)
		{			
			HUtilityXMLTag xmlt;

			sprintf(temptext,"%d", entity);
			MakeEntity(xmlgen,&xmlt, temptext, "Body",GetTagID(entity), true);
			KBody_ptr body = KBody::cast(entity);
			assert(body);
			KFaceList_ptr faces = body->GetFaceList();
			int numfaces = faces->getarraysize();

			for (int facenum=0;facenum<numfaces;facenum++)
				WriteEntity(xmlgen, KObj::cast(faces->get(facenum)));
			xmlgen->CloseTag(&xmlt);
		}	 
		else if (eclass == KERN_FACE_TYPE)
		{

			HUtilityXMLTag xmlt;
			sprintf(temptext,"%d", entity);
			MakeEntity(xmlgen,&xmlt, temptext, "Face",GetTagID(entity), true);
			KFace_ptr face = KFace::cast(entity);
			assert(face);

			KEdgeList_ptr edges = KFaceGetEdges(face);
			int numedges = edges->getarraysize();

			for (int edgenum=0; edgenum < numedges; edgenum++)
				WriteEntity(xmlgen, KObj::cast(edges->get(edgenum)));
			xmlgen->CloseTag(&xmlt);
		}
		else if (eclass == KERN_EDGE_TYPE)
		{

			HUtilityXMLTag xmlt;
			sprintf(temptext,"%d", entity);
			MakeEntity(xmlgen,&xmlt, temptext, "Edge",GetTagID(entity), false);
		}
	}

}

#endif // GRANITE

#ifdef ACIS

int	TK_ModelStructure_XML::GetTagID(ENTITY *entity) 
{
	HC_KEY key;
	int index = -1;
	if (HA_Compute_Geometry_Keys(entity, 1, &key))
		m_pStreamFileToolkit->KeyToIndex(key, index);
	else 
		return -1;
	return index;
}

void	TK_ModelStructure_XML::WriteEntity(HUtilityXMLGenerator *xmlgen, ENTITY *entity) 
{    
	outcome o;
	int eclass;
	char temptext[4096];
	if (entity)
	{

		eclass = entity->identity();
		if (eclass == BODY_TYPE)
		{			
			HUtilityXMLTag xmlt;

			sprintf(temptext,"%d", entity);
			MakeEntity(xmlgen,&xmlt, temptext, "Body",GetTagID(entity), true);
			int numshells = 0;
			ENTITY_LIST shells;
			o = api_get_shells( entity, shells);
			numshells = shells.iteration_count();
			CHECK_OUTCOME(o);			
			for (int shellnum=0;shellnum<numshells;shellnum++)
				WriteEntity(xmlgen, shells[shellnum]);
			xmlgen->CloseTag(&xmlt);
		}
		else if (eclass == SHELL_TYPE)
		{

			HUtilityXMLTag xmlt;
			sprintf(temptext,"%d", entity);
			MakeEntity(xmlgen,&xmlt, temptext, "Shell",GetTagID(entity), true);
			int numfaces;
			ENTITY_LIST faces;
			o = api_get_faces( entity, faces);
			numfaces = faces.iteration_count();
			CHECK_OUTCOME(o);
			for (int facenum=0;facenum<numfaces;facenum++)
				WriteEntity(xmlgen, faces[facenum]);
			xmlgen->CloseTag(&xmlt);
		}
		else if (eclass == FACE_TYPE)
		{

			HUtilityXMLTag xmlt;
			sprintf(temptext,"%d", entity);
			MakeEntity(xmlgen,&xmlt, temptext, "Face",GetTagID(entity), true);
			int numedges = 0;
			ENTITY_LIST edges;
			o = api_get_edges ( entity, edges );
			numedges = edges.iteration_count();
			CHECK_OUTCOME(o);

			for (int edgenum=0; edgenum < numedges; edgenum++)
				WriteEntity(xmlgen, edges[edgenum]);
			xmlgen->CloseTag(&xmlt);
		}
		else if (eclass == EDGE_TYPE)
		{

			HUtilityXMLTag xmlt;
			sprintf(temptext,"%d", entity);
			MakeEntity(xmlgen,&xmlt, temptext, "Edge",GetTagID(entity), true);
			int numvertices = 0;
			ENTITY_LIST vertices;
			o = api_get_vertices( entity, vertices );
			CHECK_OUTCOME(o);

			for( int vertexnum = 0; vertexnum < 2; vertexnum++ )
			{
				if( vertices[vertexnum] )			
					WriteEntity(xmlgen, vertices[vertexnum]);
			}
			xmlgen->CloseTag(&xmlt);
		}
		else if (eclass == VERTEX_TYPE)
		{

			HUtilityXMLTag xmlt;
			sprintf(temptext,"%d", temptext);
			MakeEntity(xmlgen,&xmlt, temptext, "Vertex",GetTagID(entity), false);
		}
	}

}

#endif // ACIS

#ifdef PARASOLID

int	TK_ModelStructure_XML::GetTagID(PK_ENTITY_t entity, char *type) 
{
	HC_KEY key;
	int index = -1;
	if (HP_Compute_Geometry_Keys(entity, 1, &key,type))
		m_pStreamFileToolkit->KeyToIndex(key, index);
	else 
		return -1;
	return index;
}

void	TK_ModelStructure_XML::WriteEntity(HUtilityXMLGenerator *xmlgen, PK_ENTITY_t entity) 
{    
	char temptext[4096];
	if (entity)
	{
		PK_CLASS_t eclass;
		if (entity)
			PK_ENTITY_ask_class(entity, &eclass);
		else 
			eclass = 0;

		if (eclass == PK_CLASS_body)
		{			
			HUtilityXMLTag xmlt;

			sprintf(temptext,"%d", entity);
			MakeEntity(xmlgen,&xmlt, temptext, "Body",GetTagID(entity, "bodies"), true);

			int numshells;
			PK_SHELL_t *shells;
			PK_BODY_ask_shells(entity,&numshells,&shells);

			for (int shellnum=0;shellnum<numshells;shellnum++)
				WriteEntity(xmlgen, shells[shellnum]);
			PK_MEMORY_free(shells);

			xmlgen->CloseTag(&xmlt);
		}
		else if (eclass == PK_CLASS_shell)
		{

			HUtilityXMLTag xmlt;
			sprintf(temptext,"%d", entity);
			MakeEntity(xmlgen,&xmlt, temptext, "Shell",GetTagID(entity, "bodies"), true);
			int numfaces;
			PK_FACE_t *faces;
			PK_LOGICAL_t *orientation;
			PK_SHELL_ask_oriented_faces(entity,&numfaces,&faces,&orientation);
			for (int facenum=0;facenum<numfaces;facenum++)
				WriteEntity(xmlgen, faces[facenum]);
			PK_MEMORY_free(faces);
			PK_MEMORY_free(orientation);
			xmlgen->CloseTag(&xmlt);
		}
		else if (eclass == PK_CLASS_face)
		{

			HUtilityXMLTag xmlt;
			sprintf(temptext,"%d", entity);
			MakeEntity(xmlgen,&xmlt, temptext, "Face",GetTagID(entity, "faces"), true);
			int numedges;
			PK_EDGE_t *edges;
			PK_FACE_ask_edges(entity,&numedges,&edges);

			for (int edgenum=0;edgenum<numedges;edgenum++)
				WriteEntity(xmlgen, edges[edgenum]);
			PK_MEMORY_free(edges);
			xmlgen->CloseTag(&xmlt);
		}
		else if (eclass == PK_CLASS_edge)
		{

			HUtilityXMLTag xmlt;
			sprintf(temptext,"%d", entity);
			MakeEntity(xmlgen,&xmlt, temptext, "Edge",GetTagID(entity, "edges"), true);
			PK_VERTEX_t vertices[2];
			PK_EDGE_ask_vertices(entity,vertices);

			for (int vertexnum=0;vertexnum<2;vertexnum++)
			{
				if (vertices[vertexnum]!=PK_ENTITY_null)
					WriteEntity(xmlgen, vertices[vertexnum]);
			}
			xmlgen->CloseTag(&xmlt);
		}
		else if (eclass == PK_CLASS_vertex)
		{

			HUtilityXMLTag xmlt;
			sprintf(temptext,"%d", temptext);
			MakeEntity(xmlgen,&xmlt, temptext, "Vertex",GetTagID(entity, "edges"), false);
		}
	}

}

#endif // PARASOLID




TK_Status	TK_ModelStructure_XML::Interpret(BStreamFileToolkit &tk, ID_Key key, int variant) 
{
	HUtilityXMLGenerator xmlgen;
	xmlgen.Reset();

	HUtilityXMLTag xmlt_modelstructure;
	xmlt_modelstructure.SetTagname("ModelStructure");
	xmlt_modelstructure.SetOpen(true);
	xmlgen.AddTag(&xmlt_modelstructure);

	MakeType(&xmlgen, "Assembly", "assembly.png",true);
	MakeType(&xmlgen, "Body", "body.png", true);
	MakeType(&xmlgen, "Shell", "shell.png", true);
	MakeType(&xmlgen, "Face", "face.png", true);
	MakeType(&xmlgen, "Edge", "edge.png", true);
	MakeType(&xmlgen, "Vertex", "vertex.png", false);

	HUtilityXMLTag xmlt_hierachy;
	xmlt_hierachy.SetTagname("Hierachy");
	xmlt_hierachy.SetOpen(true);
	xmlgen.AddTag(&xmlt_hierachy);

#ifdef PARASOLID

	PK_BODY_t * bodies;
	int numbodies;
	PK_ERROR_t err = PK_PARTITION_ask_bodies(((HSolidModel *)m_pModel)->GetPartition(),&numbodies,&bodies);
	assert(err == PK_ERROR_no_errors);

	for (int bodynum=0;bodynum<numbodies;bodynum++)
	{
		WriteEntity(&xmlgen, bodies[bodynum]);
	}
#endif // PARASOLID

#ifdef GRANITE
	HSolidModel * model = (HSolidModel *)(m_pModel);
	KComponentList_ptr components = model->GetComponentList();
	KBodyList_ptr bodies = KBodyList::create();
	KGetSolidBodiesFromComponents( components, bodies );
	int numbodies = bodies->getarraysize();	
	for (int bodynum=0;bodynum<numbodies;bodynum++)
	{
		WriteEntity(&xmlgen, KObj::cast(bodies->get(bodynum)));
	}
#endif // GRANITE

#ifdef ACIS
	int numbodies = 0;
	ENTITY_LIST bodies = ((HSolidModel *)m_pModel)->GetEntityList();
	bodies.init();
	int totalnumfaces=0;
	ENTITY *ent=0;
	while((ent = bodies.next())!=0) 
	{
		WriteEntity(&xmlgen, ent);
	}
#endif // ACIS

	xmlgen.CloseTag(&xmlt_hierachy);

	xmlgen.CloseTag(&xmlt_modelstructure);


	//	m_pModel->GetBhvBehaviorManager()->Serialize(&xmlgen);
	char *temp = new char [xmlgen.GetBufferSize()];
	memcpy(temp, xmlgen.GetBuffer(), xmlgen.GetBufferSize());
	SetXML (xmlgen.GetBufferSize(), temp);
	delete [] temp;
	return TK_Normal;
}

TK_Status   TK_ModelStructure_XML::Execute (BStreamFileToolkit & tk) 
{
	//	char *tempbuf = new char[GetSize() + 1];
	//	memcpy(tempbuf, GetXML(), GetSize());
	//	tempbuf[GetSize()] = 0;
	//	HBhvBehaviorManager::ProcessXMLData(m_pModel, tempbuf);
	//	delete [] tempbuf;
	return TK_Normal;
}

#endif // HOOPS_ONLY

#ifdef ACIS
asm_model* HSolidModel::get_asm_model(void)
{
	asm_model* owning_model = NULL;
	m_entityList.init();
	ENTITY* pEntity = m_entityList.next();
	while ( NULL == owning_model && pEntity != NULL )
	{
		if (pEntity && is_ASM_ASSEMBLY(pEntity))
		{
			ASM_ASSEMBLY* pasm_assembly = (ASM_ASSEMBLY*)pEntity;
			//			owning_model = sg_asm_assembly_get_owning_model(pasm_assembly);
			// owning_model = pasm_assembly->get_owning_model();
			api_asm_assembly_get_owning_model(pasm_assembly, owning_model);
		}
		pEntity = m_entityList.next();
	}

	return owning_model;
}

#endif // ACIS

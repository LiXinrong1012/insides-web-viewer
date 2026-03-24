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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSolidModel.h,v 1.49 2010-06-30 21:45:01 chad Exp $
//

// HSolidModel.h : interface of the HParaModel class, derived from HBaseModel
// Adds application-specific data and members for each model

#ifndef _HSOLIDMODEL_H
#define _HSOLIDMODEL_H

#include "HDB.h"
#include "HBaseModel.h"
#include "HTools.h"
#include "CAppSettings.h"
#include "HStream.h"
#include "HSInclude.h"
#include "HSUtility.h"
#ifdef ACIS
#include "ha_bridge.h"
#include "asm_model_list.hxx"
class asm_model;
class EE_LIST;
class component_handle;
class HISTORY_STREAM;
#endif // ACIS

#ifdef INTEROP
class InterOpFileIO;
#endif // INTEROP

class CModellerInfo;
class HUtilityXMLGenerator;
class HUtilityXMLTag;
class HIOConnector;


class HSolidModel : public HBaseModel
{
private:
#ifdef ACIS
	ENTITY_LIST m_entityList;		// list of entities (bodies) in this model
	asm_model_list m_modelList;		// list of the top-level ACIS models in ASAT file

	// stores a hash map of component_handle* vs. EE_LIST (which is the list of ASM_MODEL_REFs 
	// for the component.
	struct vhash_s *mhash_CompHandle_2_EEList;

	HISTORY_STREAM model_hs;		// default HISTORY_STREAM for this model
	HISTORY_STREAM *curr_hs;		// pointer to the current HISTORY_STREAM
#endif // ACIS
#ifdef INTEROP
	InterOpFileIO *iop_fio;
#endif // INTEROP

	ModelHandedness m_model_handedness;


public:
	HSolidModel();
	~HSolidModel();
	HFileInputResult Read(wchar_t const * FileName, HBaseView * view=0);
	HFileInputResult Read(const char * FileName, HBaseView * view=0){
		return Read((wchar_t*)H_WCS(FileName).encodedText(), view);
	}

	MultiSelectManager *GetMultiSelectManager() { return m_MultiSelectManager; }
	HFileOutputResult WriteWithOptions(wchar_t const * FileName, HBaseView * pHView=0, HOutputHandlerOptions * options = 0);
	HFileOutputResult WriteWithOptions(const char * FileName, HBaseView * pHView=0, HOutputHandlerOptions * options = 0){
		return WriteWithOptions((wchar_t*)H_WCS(FileName).encodedText(), pHView, options);
	}

	bool Write(const wchar_t * FileName, HBaseView * pHView, int version, int width = 0, int height = 0);
	bool Write(const char * FileName, HBaseView * pHView, int version, int width = 0, int height = 0){
		return Write((wchar_t*)H_WCS(FileName).encodedText(), pHView, version, width, height);
	}

#ifndef HOOPS_ONLY
	KERN_ENTITY Compute_Selected_Instance();
#endif // HOOPS_ONLY


#ifdef ACIS
	HISTORY_STREAM * GetHistoryStream () { return curr_hs; }
	void SetHistoryStream ( HISTORY_STREAM * new_hs = 0 );
	
	void DeleteAcisEntity( ENTITY* entity);
	void AddAcisEntity( ENTITY* entity);
	void RemoveAcisEntity( ENTITY* entity);

	ENTITY_LIST& GetEntityList() { return m_entityList; }
	asm_model_list& GetModelList() { return m_modelList; }

	EE_LIST* GetEEListForComponent(component_handle* comp_handle);

	logical HA_Read_Asat_File(const char* fname, asm_model_list& model_list);
	asm_model* HSolidModel::get_asm_model(void);
#endif // ACIS


#ifdef INTEROP
	InterOpFileIO * GetInterOpFileIOHandler () { return iop_fio; }
#endif // INTEROP

	void DeleteAllEntities();


#ifndef HOOPS_ONLY
	CModellerInfo *m_mi;
#endif // HOOPS_ONLY
	bool	m_bSolidModel;
	bool	m_bSolidData;
	bool	m_bPlainSolidModel;
	MultiSelectManager *m_MultiSelectManager;
	ModelHandedness GetModelHandedness() { return m_model_handedness; }
	void SetModelHandedness(ModelHandedness handedness);
	void UpdateModelHandedness();
	static void MultiModelSelectionCallback(char const * in_container, int in_num_configs, char const ** in_configs, int & out_config_selection);

	virtual void SetBRepGeometry(bool brep);
	long UpdateModelGeometryType();
#ifndef HOOPS_ONLY
	void SetupModelStructureWriteFromHSF(HStreamFileToolkit *mytool);
#endif

	BREP_Topology *m_TopologyManager;
	HIOConnector  *m_pPMIConnector;
	HIOConnector  *m_pConnector;
	void *m_pPRCAsmModelFile;
protected:
	void GenerateLODsForBodies();

};


#ifndef HOOPS_ONLY


//! The TK_Bhv_XML subclasses writes and reads behaviour related XML data
class TK_ModelStructure_XML : public TK_XML
{

public:

	/*!
	Constructs a TK_Bhv_XML Object
	\param model Pointer to HBaseModel object
 	*/
	TK_ModelStructure_XML(HBaseModel * model, HStreamFileToolkit*toolkit) : TK_XML() 
	{ 
		m_pModel = model;
		m_pStreamFileToolkit = toolkit;
	}

	/*! customized for this class to extract information from MVO 'behavior' data structures */
 	TK_Status	Interpret(BStreamFileToolkit &tk, ID_Key key, int variant) alter;
	/*! customized for this class to populate MVO 'behavior' data structures with information */
	TK_Status   Execute (BStreamFileToolkit & tk) alter;
#ifdef ACIS
	void	WriteEntity(HUtilityXMLGenerator *xmlgen, ENTITY *entity); 
	int	GetTagID(ENTITY *entity);
#endif


	void MakeType(HUtilityXMLGenerator *xmlgen, char *tname, char *imagename, bool selectable);
	void MakeEntity(HUtilityXMLGenerator *xmlgen, HUtilityXMLTag *xmlt, char *name, char *type,int tagid, bool keepopen);

	

private:
	HBaseModel *	m_pModel;	
	HStreamFileToolkit * m_pStreamFileToolkit;
};


#endif	// ACIS

#endif // _HSOLIDMODEL_H





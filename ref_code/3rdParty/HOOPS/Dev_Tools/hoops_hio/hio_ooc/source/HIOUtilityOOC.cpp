/*
 * Copyright (c) 2009 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: HIOUtilityOOC.cpp,v 1.13 2009-10-14 23:02:48 chad Exp $
 */

#include "HIOUtilityOOC.h"

#include "PointCloud.h"

#include "BStream.h"

#include "HBaseView.h"

class PointCloudInstance {
public:
	PointCloudInstance () {
		m_point_cloud = 0;
		m_update_timer = 0;
	};

	~PointCloudInstance () {
		if (m_update_timer) {
			HDB::GetHTManager()->UnRegisterClient(m_update_timer);
			delete m_update_timer;
		}

		delete m_point_cloud;
	};

	PointCloud *	m_point_cloud;
	HTClient *		m_update_timer;
};

HIOUtilityOOC::HIOUtilityOOC () {}

HIOUtilityOOC::~HIOUtilityOOC () {}

HFileInputResult HIOUtilityOOC::FileInputByKey ( wchar_t const * filename, HC_KEY key, HInputHandlerOptions * options ) {	
	PointCloud *pc = new PointCloud(filename);

	HC_Open_Segment_By_Key(key);
		PointCloudStatus status = pc->Load();
	HC_Close_Segment();

	if (pc->GetLoadType() == LOAD_TYPE_IMMEDIATE)
		delete pc;
	else {
		PointCloudInstance *pci = new PointCloudInstance();
		
		pci->m_point_cloud = pc;
		pc->SetExternalUpdateData(options->m_pHBaseView);

		pci->m_update_timer = new HTClient(1.0f, HTCS_PeriodicSkip, HIOUtilityOOC::UpdateCheck, pc);
		HDB::GetHTManager()->RegisterClient(pci->m_update_timer);

		options->m_pHBaseView->SetSignalNotify(HSignalDelete, FreePointCloudData, pci);
	}
	
	if (status != LOAD_SUCCESS)
		return InputFail;
	else
		return InputOK;
}

void HIOUtilityOOC::RegisterInputHandlerTypes () {
	HIORegisterInputType("ooc", this);
}

bool HIOUtilityOOC::FreePointCloudData ( int signal, void * signal_data, void * user_data ) {
	PointCloudInstance *pci = reinterpret_cast<PointCloudInstance *>(user_data);

	delete pci;

	return true;
}

bool HIOUtilityOOC::UpdateCheck ( float request_time, float actual_time, void * user_data ) {
	PointCloud *pc = reinterpret_cast<PointCloud *>(user_data);

	if (pc->IsUpdateNeeded())
		HBaseView::StaticForceUpdateRequest(pc->GetExternalUpdateData());

	return true;
}

#ifdef HIO_OOC_IMPORT
void * CreateInput ( HIOManager * manager ) {
	HIOUtilityOOC *handler = new HIOUtilityOOC();
	manager->RegisterInputHandler("ooc", handler);

	manager->RegisterConnector("ooc", CreateConnector, (HIO_FREE_CONNECTOR_FUNCTION)FreeConnector);
	return handler;
};

void * CreateOutput ( HIOManager * manager ) {
	return NULL;
};


void * CreateConnector ( void * unused ) {
	UNREFERENCED(unused);
	return new HIOConnector();
};


void Free ( HIOUtilityOOC * handler ) { 
	if (handler) 
		delete handler; 
};


void FreeConnector ( HIOConnector * connector ) {
	if (connector)
		delete connector;
};
#endif

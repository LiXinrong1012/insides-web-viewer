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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSOpObjectTranslate.cpp,v 1.16 2007-10-16 18:59:57 stage Exp $
//


#include "StdAfx.h"
#include "HSInclude.h"

#include "HBaseView.h"
#include "HSOpObjectTranslate.h"
#include "HSSelectionSet.h"
#include "HSolidModel.h"

#include "hc.h"

#include <assert.h>

#ifdef PARASOLID
#include "parasolid_kernel.h"
#include "kernel_interface.h"
#include "hp_bridge.h"
#endif // PARASOLID

/*
#ifdef ACIS
// Required to use HA_Compute_Entity_Pointer
#include "ha_bridge.h"
// Required to use vector class
#include "kernel/kernutil/vector/vector.hxx"
// Required to use transf class
#include "kernel/kernutil/vector/transf.hxx"
// Required to use outcome class
#include "kernel/kernapi/api/api.hxx"
// Required to use constant  BODY_TYPE
#include "kernel/kerndata/top/body.hxx"
// Required to call api_transform_entity
//#include "kernel/acis.hxx"
//#include "kernel/kernapi/api/api.hxx"
#include "kernel/kernapi/api/kernapi.hxx"
#endif // ACIS
*/

/////////////////////////////////////////////////////////////////////////////
// HSOpObjectTranslate

// App-specific translate operator for translating selected geometric kernel bodies
// Mouse down and motion use base class methods 
// Mouse up calls base class method and also update geometric kernel with the
// new position of each object


HSOpObjectTranslate::HSOpObjectTranslate(HBaseView* view, int DoRepeat,int DoCapture) : HOpObjectTranslate(view, DoRepeat, DoCapture)
{
	HSSelectionSet* selection = (HSSelectionSet*) (m_pView->GetSelection());
	
	int size = selection->GetSize();

	// loop through the selection list turning on spriting for each segment
	for (int n = 0; n < size; n++)
	{
		HC_KEY	key, segkey;
		char	type[MVO_BUFFER_SIZE];

		key = selection->GetAt(n);
		HC_Show_Key_Type(key, type);
		if (streq(type, "segment"))
			segkey = key;
		else
			segkey = HC_KShow_Owner_By_Key(key);

		HC_Open_Segment_By_Key(segkey);
			HC_Set_Heuristics("quick moves = spriting");
		HC_Close_Segment();
	}
	// now update the scene so that the sprite backbuffer is created
	m_pView->Update();
}


HSOpObjectTranslate::~HSOpObjectTranslate()
{
	HSSelectionSet* selection = (HSSelectionSet*) (m_pView->GetSelection());
	
	int size = selection->GetSize();

		// loop through each body id in the selection list, translating each one
	for (int n = 0; n < size; n++)
	{
		HC_KEY	key, segkey;
		char	type[MVO_BUFFER_SIZE];

		key = selection->GetAt(n);
		HC_Show_Key_Type(key, type);
		if (streq(type, "segment"))
			segkey = key;
		else
			segkey = HC_KShow_Owner_By_Key(key);

		HC_Open_Segment_By_Key(segkey);
			HC_UnSet_One_Heuristic("quick moves");
		HC_Close_Segment();
	}
}


// Mouse has come up; update each object's position in geometric kernel database
int HSOpObjectTranslate::OnLButtonUp(HEventInfo &ev)
{
	if (((HSolidModel *)(m_pView->GetModel()))->m_bSolidModel == true)
	{
		HSSelectionSet* selection = (HSSelectionSet*) (m_pView->GetSelection());

		int size = selection->GetSolidListSize();

		// loop through each body id in the selection list, translating each one
		for (int n = 0; n < size; n++)
		{
		#ifdef PARASOLID
			int				n_replaces;
			PK_BODY_t		body;
			PK_ERROR_code_t	error_code;
			PK_TRANSF_sf_t	transfMatrix;
			PK_TRANSF_t		transf;
			body = selection->GetAtSolidEntity(n);

			transfMatrix.matrix[0][0] = 1.0;
			transfMatrix.matrix[0][1] = 0.0;
			transfMatrix.matrix[0][2] = 0.0;
			transfMatrix.matrix[0][3] = m_ptNew.x - m_ptFirst.x;

			transfMatrix.matrix[1][0] = 0.0;
			transfMatrix.matrix[1][1] = 1.0;
			transfMatrix.matrix[1][2] = 0.0;
			transfMatrix.matrix[1][3] = m_ptNew.y - m_ptFirst.y;

			transfMatrix.matrix[2][0] = 0.0;
			transfMatrix.matrix[2][1] = 0.0;
			transfMatrix.matrix[2][2] = 1.0;
			transfMatrix.matrix[2][3] = m_ptNew.z - m_ptFirst.z;

			transfMatrix.matrix[3][0] = 0.0;
			transfMatrix.matrix[3][1] = 0.0;	
			transfMatrix.matrix[3][2] = 0.0;
			transfMatrix.matrix[3][3] = 1.0;

			error_code = PK_TRANSF_create(&transfMatrix, &transf);
			error_code = PK_BODY_transform(body, transf, 0.0, &n_replaces, 0, 0);
		#endif // PARASOLID

		#ifdef ACIS
			BODY*			body;
			SPAvector		translate_vector;
			SPAtransf		delta_transf;
			outcome			o;

			body = (BODY*)selection->GetAtSolidEntity(n);
			translate_vector.set_x(m_ptNew.x - m_ptFirst.x);
			translate_vector.set_y(m_ptNew.y - m_ptFirst.y);
			translate_vector.set_z(m_ptNew.z - m_ptFirst.z);

			delta_transf = translate_transf(translate_vector);
			o = api_transform_entity(body, delta_transf);
			assert(o.ok());
		#endif // ACIS
		}
	}

	// call base class method to actually move the object in the HOOPS database
	// and see the visual result of the translated geometry
	return HOpObjectTranslate::OnLButtonUp(ev);
}





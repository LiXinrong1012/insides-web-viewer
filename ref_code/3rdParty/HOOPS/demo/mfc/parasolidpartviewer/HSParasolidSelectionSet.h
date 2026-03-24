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
// $Header: /files/homes/master/cvs/hoops_master/parasolidpartviewer/HSParasolidSelectionSet.h,v 1.14 2009-08-21 18:15:31 chad Exp $
//

// HPSelectionSet.h : interface of the HPSelectionSet class, derived from HSelectionSet
// adds app-specific overlooading of selection functions to support PK_face, PK_body and
// PK_egde level selection/highlighting

#ifndef _HSPARASOLIDSELECTIONSET_H
#define _HSPARASOLIDSELECTIONSET_H

 
#include "parasolid_kernel.h"
#include "kernel_interface.h"

#include "HSSelectionSet.h"


class HSParasolidSelectionSet :  public HSSelectionSet 
{

 
public:
	HSParasolidSelectionSet(HBaseView* view);
 
	// overloaded virtuals
	virtual void Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message);
	virtual void DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message);
	virtual bool IsSelected(HC_KEY key, int num_include_keys, const HC_KEY * include_keys) const;

	void Select(HC_KEY key, const char* segpath, HC_KEY include_key, HC_KEY includer_key, bool emit_message = true);	
	void Select(PK_ENTITY_t entity, bool emit_message = true);

    void DeSelect(HC_KEY key, bool emit_message = true);	
	void DeSelectEntity(PK_ENTITY_t entity, bool emit_message = true);

     bool IsSelected(HC_KEY key); 	
 	// selection level support
	void RefreshSolidSelection();
 	
};

#endif







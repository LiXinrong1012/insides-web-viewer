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
// $Header: /files/homes/master/cvs/hoops_master/shared/solidviewer_common/HSPlainSelectionSet.h,v 1.13 2007-10-16 23:19:24 stage Exp $
//

// HPSelectionSet.h : interface of the HPSelectionSet class, derived from HSelectionSet
// adds app-specific overlooading of selection functions to support PK_face, PK_body and
// PK_egde level selection/highlighting

#ifndef _HSPLAINSELECTIONSET_H
#define _HSPLAINSELECTIONSET_H

#ifdef PARASOLID 
#include "parasolid_kernel.h"
#include "kernel_interface.h"
#endif // PARASOLID

#include "HSSelectionSet.h"


class HSPlainSelectionSet :  public HSSelectionSet 
{

 
public:
	HSPlainSelectionSet(HBaseView* view);
 
	// overloaded functions which handle instancing
	virtual void Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message);
	virtual void DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message);
	virtual bool IsSelected(HC_KEY key, int num_include_keys, HC_KEY * include_keys);

	// modeler entity select functions
	virtual void Select(long entity, bool emit_message = true);
	virtual void DeSelectEntity(long entity, bool emit_message = true);

	// deprecated old select functions
 	virtual void Select(HC_KEY key, const char* segpath, HC_KEY include_key, HC_KEY includer_key, bool emit_message = true);
	virtual void DeSelect(HC_KEY key, bool emit_message = true);
	virtual bool IsSelected(HC_KEY key); 	

	virtual void RefreshSolidSelection();
};

#endif






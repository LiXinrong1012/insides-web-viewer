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
// $Header: /files/homes/master/cvs/hoops_master/hoopspartviewer/HMySelectionSet.h,v 1.6 2007-08-16 19:57:02 nathan Exp $
//

// HMySelectionSet.h : interface of the HSelectionSet class
// manages list of selected (highlighted) items for view

#ifndef _HMYSELECTIONSET_H 
#define _HMYSELECTIONSET_H

#include <afxtempl.h>
#include "HSSelectionSet.h"

class HMySelectionSet : public HSSelectionSet
{
	

public:

	HMySelectionSet(HBaseView* view, bool bReferenceSelection = false);

	// Following members are overloaded to handle the 'segment' and 'entity' levels
	virtual void Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = true);
	virtual void DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = true);
    virtual bool IsSelected(HC_KEY key, int num_include_keys, HC_KEY * include_keys) const;

	void Select(HC_KEY key, const char* segpath, HC_KEY include_key, HC_KEY includer_key, bool emit_message=true);
	void DeSelect(HC_KEY key, bool emit_message = true);
    virtual bool IsSelected(HC_KEY key);


	void DeSelectAll();
	virtual void RefreshSolidSelection();

private:

};

#endif

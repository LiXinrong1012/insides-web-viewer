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
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/PreSelectionSet.h,v 1.6 2006-08-07 20:38:58 stage Exp $
//

// PreSelectionSet.h : interface of the HSelectionSet class
// manages list of selected (highlighted) items for view

#ifndef _HMYSELECTIONSET_H 
#define _HMYSELECTIONSET_H

#include "HSelectionSet.h"
#include "precore/ISelectionSupplier.h"

#include <QWeakPointer>

class PreHQWidget;

using namespace INSIDES;


class PreSelectionSet : public HSelectionSet ,public INSIDES::ISelectionSupplier
{
public:

	PreSelectionSet(HBaseView* view,PreHQWidget* hqWidget);
	~PreSelectionSet();

	// Following members are overloaded to handle the 'segment' and 'entity' levels
	virtual void Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = true);
	virtual void Select(HSelectionItem * new_sel, bool emit_message = false);
	virtual void DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = true);
	virtual bool IsSelected(HC_KEY key, int num_include_keys, HC_KEY * include_keys);

	virtual void Select(HC_KEY key, const char* segpath, HC_KEY include_key, HC_KEY includer_key, bool emit_message = false);
	virtual void DeSelect(HC_KEY key, bool emit_message = false);

	virtual void SelectSubentity(HC_KEY key, int num_include_keys, HC_KEY * include_keys, 
		int count, const int * faces=0, const int * vertex1=0, const int * vertex2=0, bool emit_message=false);

	void MySelect(HC_KEY key, int num_include_keys,HC_KEY* include_keys,bool emit_messsage=true);


	void updateProjectSelection();

protected:
	virtual void ss_onSetSelection_protected(const BaseItemSelection& );
	virtual void ss_onSetSelectionNodes_protected(const SelectionNodeElem& selection);
	virtual void ss_onSetSelectionElements_protected(const SelectionNodeElem& selection);


private:

	PreHQWidget*  m_HQWidget;

	BaseItem* getRelatedBaseItem(HC_KEY key);

	void updateSelectionEntity();
	void updateSelectionNodeElem();

};

#endif

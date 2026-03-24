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
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/HMySelectionSet.h,v 1.5 2006-08-07 20:38:46 stage Exp $
//

// HMySelectionSet.h : interface of the HSelectionSet class
// manages list of selected (highlighted) items for view

#ifndef _HMYSELECTIONSET_H 
#define _HMYSELECTIONSET_H

#include "HSelectionSet.h"
class CDataLoader; 

//! The MyHSelectionSet class manages a list of selected items.
/*!
	HMySelectionSet is derived from HSelectionSet to handle key based selection with persistent identifiers
*/

class HMySelectionSet : public HSelectionSet
{
	

public:
	/*! Constructor
		\param view Pointer to HBaseView object
 	    \param dataloader Pointer to dataloader object
 	*/
	HMySelectionSet(HBaseView* view, CDataLoader *dataloader);
	/*!  Selects an item by first trying to map the key to a persistent identifier
		\param key The key of the item to add.
		\param num_include_keys The number of include keys in the path upto the driver key
		\param include_keys An array of include keys
	    \param emit_message  Indicates that a message should be sent to the emit_message_function, which (if implemented)
 						   would typically use the HOOPS/Net 'Send' function to dispatch the message to clients	
	*/

 	virtual void Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = true);

	/*!  Calls the base class Select method
		\param key The key of the item to add.
		\param num_include_keys The number of include keys in the path upto the driver key
		\param include_keys An array of include keys
	    \param emit_message  Indicates that a message should be sent to the emit_message_function, which (if implemented)
 						   would typically use the HOOPS/Net 'Send' function to dispatch the message to clients	

	*/
	
	virtual void SelectDirect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = true);

	/*!  Sets the model structure filter used to filter selections
		\param filter Model Structure Filter to use for selections
	*/
 	void SetModelStructureFilter(char *filter) {strcpy(m_ModelStructureFilter, filter); }
 
private:

    CDataLoader *m_pDataLoader;
    char	m_ModelStructureFilter[256];
	
//	SelectLevel m_HoopsSelectLevel;

};

#endif

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
// $Header: /files/homes/master/cvs/hoops_master/shared/partviewer_common/HSUtility.cpp,v 1.21 2008-11-26 21:21:41 guido Exp $
//

// Utility Functions used for the application

#include "stdafx.h"
#include "HSInclude.h"

#include "HTools.h"
#include "HBaseOperator.h"
#include "HBaseView.h"
#include "HSUtility.h"
#include "HUtilityLocaleString.h"
#include "HUtility.h"
#include "HSelectionSet.h"
#include "vlist.h"
#include "vhash.h"
#include "hc.h"


#include <stdio.h>
#include <math.h>
#include <assert.h>
 
#ifdef ACIS
#ifdef IS_X11
// Required to resolve unresolved symbol in ACIS library libgihusk.sl
// *FIX this is a bug in Acis which should be fixed by release 5.3
#include "Xm/XmP.h"
Widget toplevel=0;
#endif // IS_X11
#endif // ACIS


#ifdef ACIS
//inline void check(outcome& o)
extern void check(outcome& o);
#if 0
{
	int error_number;
	if(!o.ok())
	{
//		__asm int 3;
		char error_string[MVO_BUFFER_SIZE];
		error_number = o.error_number();
		strcpy(error_string, find_err_mess(error_number));
		assert(0);
	}
}
#endif 

// calls the appropriate boolean function based on the target and tools
// and rerenders the resulting bodies
void	acis_boolean(unsigned long operation, BODY* target, 
							  unsigned long number_of_tools, BODY **tools)
{
	outcome o;
	unsigned long i;

	assert(target);
	assert(tools);
	assert(number_of_tools > 0);

	switch(operation)
	{
	case HA_OPERATION_SUBTRACT:
		for (i = 0; i < number_of_tools; i++)
		{
			o = api_subtract(tools[i], target);
			assert(o.ok());
		}
		break;
	case HA_OPERATION_UNITE:
		for (i = 0; i < number_of_tools; i++)
		{
			o = api_unite(tools[i], target);
			assert(o.ok());
		}
		break;
	case HA_OPERATION_INTERSECT:
		for (i = 0; i < number_of_tools; i++)
		{
			o = api_intersect(tools[i], target);
			assert(o.ok());
		}
		break;
	default:
		assert(0);
		break;
	}
	HA_Render_Entity(target);
}

#endif // ACIS




void QualifiedKey::Select(HBaseView *view)
{
	HSelectionSet *sel = view->GetSelection();
	sel->Select(m_Key, m_IncludeListLength, m_IncludeList);
}
MultiSelectItem::MultiSelectItem(HC_KEY key)
{
	m_Key.SetKey(key);
	m_AssociatedKeyList = new_vlist(malloc, free);
	m_AssociatedSelectItemList = new_vlist(malloc, free);
}
MultiSelectItem::~MultiSelectItem()
{
	START_LIST_ITERATION(QualifiedKey, m_AssociatedKeyList);
 			delete temp;
	END_LIST_ITERATION(m_AssociatedKeyList);
	delete_vlist(m_AssociatedKeyList);
	START_LIST_ITERATION(QualifiedKey, m_AssociatedSelectItemList);
 			delete temp;
	END_LIST_ITERATION(m_AssociatedSelectItemList);
	delete_vlist(m_AssociatedSelectItemList);
}


void MultiSelectItem::AddAssociatedKey(HC_KEY key, int length, HC_KEY *include_list)
{
	QualifiedKey *qk = new QualifiedKey(key, length, include_list);
	vlist_add_last(m_AssociatedKeyList, qk);
}
void MultiSelectItem::AddAssociatedSelectItem(HC_KEY key, int length, HC_KEY *include_list)
{
	QualifiedKey *qk = new QualifiedKey(key, length, include_list);
	vlist_add_last(m_AssociatedSelectItemList, qk);
}
void MultiSelectItem::MultiSelect(MultiSelectManager *mm, HBaseView *view)
{
	START_LIST_ITERATION(QualifiedKey, m_AssociatedKeyList);
 			temp->Select(view);
	END_LIST_ITERATION(m_AssociatedKeyList);
	START_LIST_ITERATION(QualifiedKey, m_AssociatedSelectItemList);
			mm->MultiSelect(temp->GetKey(), view);
 	END_LIST_ITERATION(m_AssociatedSelectItemList);
}



MultiSelectManager::MultiSelectManager()
{
	m_SelectItemHash = new_vhash(10,malloc,free);
	m_SelectItemList = new_vlist(malloc,free);
	m_bHasItems = false;
}
MultiSelectManager::~MultiSelectManager()
{
	START_LIST_ITERATION(MultiSelectItem, m_SelectItemList);
 			delete temp;
	END_LIST_ITERATION(m_SelectItemList);
	delete_vlist(m_SelectItemList);
	delete_vhash(m_SelectItemHash);
	
}



MultiSelectItem * MultiSelectManager::CreateMultiSelectItem(HC_KEY key)
{
	MultiSelectItem *item = new MultiSelectItem(key);
	vhash_insert_item(m_SelectItemHash, (void *)key  , (void *)item);	
	vlist_add_last(m_SelectItemList, item);
	m_bHasItems = true;
	return item;
}
MultiSelectItem * MultiSelectManager::GetMultiSelectItem(HC_KEY key)
{

	MultiSelectItem *item;
	int res = vhash_lookup_item(m_SelectItemHash, (void *)key ,  (void **)&item);
	if (!(res == VHASH_STATUS_SUCCESS))
		return 0;
	return item;
}

HC_KEY  MultiSelectManager::MultiSelect(HC_KEY key, HBaseView *view)
{
	int i;
	if (!m_bHasItems)
		return key;
	HC_KEY oldkey = key;
	for (i=0;i<5;i++)
	{		
		MultiSelectItem *item = GetMultiSelectItem(key);
		if (item)
		{
			item->MultiSelect(this, view);
			break;
		}
		key = HC_KShow_Owner_By_Key(key);
	}
	if (i==5)
		return oldkey;
	else
		return key;

}


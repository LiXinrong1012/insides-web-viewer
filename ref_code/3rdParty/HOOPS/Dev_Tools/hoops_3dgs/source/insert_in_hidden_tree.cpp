/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.81 2009-10-23 23:14:48 trask Exp $
 */


#include "hoops.h"
#include "driver.h"
#include "hidden.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HD_Insert_In_Hidden_Tree (
	_hoops_CASS alter				*item) {
#ifndef DISABLE_SORTING_HSR
	Net_Rendition const &		nr = item->_hoops_ASHSA->_hoops_APHGA;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

#	ifdef HOOPS_DEBUG_BUILD
	if (dc->_hoops_HCAGH)
		_hoops_SGSPR (HEC_INFO, HES_HOOPS_IS_CONFUSED, "Hidden geometry recollected ... not good.");
#	endif

	if (dc->_hoops_RIAGH == null) {
		dc->_hoops_SASS[dc->_hoops_IASS]++;
		item->next = (_hoops_CASS alter *)dc->_hoops_HASS[dc->_hoops_IASS];
		dc->_hoops_HASS[dc->_hoops_IASS] = item;
		if (dc->_hoops_RAI != dc->_hoops_GIAGH) {
			if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT)
				dc->_hoops_SHAGH |= HD_Geometry_To_Action_Mask (dc->_hoops_RAI);
			dc->_hoops_GIAGH = dc->_hoops_RAI;
		}
	}
	else {
		_hoops_PSGSH alter *info = (_hoops_PSGSH alter *)dc->_hoops_RIAGH->_hoops_ASHSA->_hoops_GPHSA;
		info->count++;
		item->next = info->root;
		info->root = item;
	}
#endif
}


GLOBAL_FUNCTION void HD_Start_Priority_Inclusion (
	Net_Rendition const &		nr,
	long						priority) {
#ifndef _hoops_IRSSH
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_CASS alter *				item;
	_hoops_PSGSH alter *		info;
	_hoops_SRHSA alter *		_hoops_ASHSA;

	ALLOC (item, _hoops_CASS);
	ZERO_STRUCT (item, _hoops_CASS);
	ALLOC (_hoops_ASHSA, _hoops_SRHSA); 
	ZERO_STRUCT (_hoops_ASHSA, _hoops_SRHSA); 
	item->_hoops_ASHSA = _hoops_ASHSA;
	item->values = priority;
	_hoops_ASHSA->type = _hoops_SSGSH;
	_hoops_ASHSA->_hoops_APHGA = nr;

	ALLOC (info, _hoops_PSGSH);
	ZERO_STRUCT (info, _hoops_PSGSH);
	info->_hoops_HRSSA = (_hoops_CASS alter *)dc->_hoops_RIAGH; /* (_hoops_ICIC _hoops_HIIC) */
	_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA alter*)info;

	HD_Insert_In_Hidden_Tree (item);

	dc->_hoops_RIAGH = item;
#endif
}

GLOBAL_FUNCTION void HD_Finish_Priority_Inclusion (
	Net_Rendition const &		nr) {
#ifndef _hoops_IRSSH
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_PSGSH alter *		info;

	if (dc->_hoops_RIAGH == null) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Inclusion imbalance");
		return;
	}

	info = (_hoops_PSGSH alter *)dc->_hoops_RIAGH->_hoops_ASHSA->_hoops_GPHSA;
	dc->_hoops_RIAGH = info->_hoops_HRSSA;
#endif
}

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
 * $Id: obf_tmp.txt 1.49 2010-10-06 19:16:28 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"


local void _hoops_RCPRGR (
	Display_Context alter	*dc,
	Attribute const			*_hoops_ASGPR) {

	do {
		if (_hoops_ASGPR->type > (Type)_hoops_IAAA (HK_STYLE, HK_DRIVER_OPTIONS))
			break;
#ifndef DISABLE_STYLE_SEGMENT
		else if (_hoops_ASGPR->type == HK_STYLE) {
			Attribute const	*_hoops_ACPRGR;

			_hoops_ACPRGR = ((Style const *)_hoops_ASGPR)->_hoops_IGRPR->_hoops_IPPGR;
			if (_hoops_ACPRGR != null)
				_hoops_RCPRGR (dc, _hoops_ACPRGR);
		}
#endif
		else if (_hoops_ASGPR->type == HK_DRIVER_OPTIONS) {
			HD_Record_Driver_Options (dc, _hoops_ASGPR);
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
}


local void _hoops_PCPRGR (
	Display_Context alter	*dc,
	_hoops_CRCP const			*_hoops_SRCP) {
	Attribute const			*_hoops_ASGPR = null;

	_hoops_PCCAR {
		if (_hoops_SRCP->type == _hoops_IRCP)
			_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;
		else if (_hoops_SRCP->type == _hoops_AGRPR || _hoops_SRCP->type == _hoops_PIRIR)
			_hoops_ASGPR = null;
		else
			_hoops_ASGPR = null;	// ?

		if (_hoops_ASGPR != null) {
			do if (_hoops_ASGPR->type == HK_DRIVER_OPTIONS ||
				   _hoops_ASGPR->type == HK_STYLE) goto _hoops_PCPPR;
			_hoops_RGGA ((_hoops_ASGPR = _hoops_ASGPR->next) == null);
		}
		if (_hoops_SRCP == HOOPS_WORLD->root) break;
		_hoops_SRCP = _hoops_SRCP->owner;
	}
	_hoops_PCPPR:;

	if (_hoops_SRCP != HOOPS_WORLD->root) _hoops_PCPRGR (dc, _hoops_SRCP->owner);

	_hoops_RCPRGR (dc, _hoops_ASGPR);
}


GLOBAL_FUNCTION void HD_Upwind_Driver_Options (
	Display_Context alter	*dc) {
	bool					_hoops_HCPRGR = BIT(dc->flags, _hoops_CPPHP);

	dc->flags |= _hoops_CPPHP;
	_hoops_PCPRGR (dc, dc->_hoops_AAHSR);
	if (!_hoops_HCPRGR)
		dc->flags &= ~_hoops_CPPHP;

	/* _hoops_CHASA, _hoops_RPP _hoops_HAHH */
	if (!dc->options._hoops_RASSP)
		dc->options._hoops_AASSP = false;
	if (!dc->options._hoops_AASSP)
		dc->options._hoops_PASSP = false;
	if (dc->_hoops_PGCC._hoops_CHHSR == _hoops_SHHSR)
		dc->options._hoops_SRRRR = false;
	if (dc->options._hoops_HRSSP)
		dc->options.border = true;
}

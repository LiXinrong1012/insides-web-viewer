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
 * $Id: obf_tmp.txt 1.48 2010-10-06 19:15:59 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


HC_INTERFACE void HC_CDECL HC_Define_Callback_Name (
	char const *			name,
	_hoops_IRPCR			address) 
{
	_hoops_PAPPR context("Define_Callback_Name");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Define_Callback_Name () */\n");
	);

	_hoops_HCHIR *		cname;
	_hoops_HCHIR **	_hoops_ASRGR;
	_hoops_HCRPR				_hoops_CRPCR;

	HI_Canonize_Chars (name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_CALLBACK, HES_NULL_INPUT, "Callback name is blank or null");
		return;
	}

	_hoops_RPPPR();
	_hoops_ASRGR = HI_Look_Up_Callback_Name (context, _hoops_CRPCR.text, _hoops_CRPCR.length);

	if (*_hoops_ASRGR != null) {
		HE_WARNING (HEC_CALLBACK, HES_REDEFINING_NAME, Sprintf_N (null, "Re-defining '%n'", &_hoops_CRPCR));
		HI_Generic_Delete (context,(_hoops_HPAH *)(*_hoops_ASRGR));
		_hoops_ASRGR = HI_Look_Up_Callback_Name (context, _hoops_CRPCR.text, _hoops_CRPCR.length);
	}

	ZALLOC (cname, _hoops_HCHIR);
	cname->_hoops_HIHI = 1;
	cname->type = _hoops_PCHIR;
	cname->owner = HOOPS_WORLD;

	cname->backlink = _hoops_ASRGR;
	if ((cname->next = *_hoops_ASRGR) != null)
		(*_hoops_ASRGR)->backlink = &cname->next;
	*_hoops_ASRGR = cname;

	cname->address = address;
	cname->name.text = _hoops_CRPCR.text;
	cname->name.length = _hoops_CRPCR.length;
	_hoops_IRRPR();
#endif
}

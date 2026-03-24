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
 * $Id: obf_tmp.txt 1.42 2010-10-06 19:15:59 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"


/* _hoops_CAAPA _hoops_PIHA _hoops_SHH _hoops_SRSR _hoops_IRIGR-_hoops_RGAR _hoops_IH _hoops_RH _hoops_IHPHR _hoops_IIGR _hoops_RH _hoops_GASR */
/* _hoops_CAAPA _hoops_PIHA _hoops_SHH _hoops_GSSC _hoops_AGIR */

GLOBAL_FUNCTION _hoops_PIIIR * HI_Define_Nice_Option (
	_hoops_GCIIR *		_hoops_SPHHR,
	long					id,
	const _hoops_HCRPR *			name,
	int						_hoops_RCIIR,
	int						_hoops_RHSAA,
	bool					_hoops_GHSAA,
	_hoops_GCIIR *		_hoops_CIIIR) {
	int						_hoops_ACIPP;
	_hoops_PIIIR *			type;
	_hoops_PIIIR **			_hoops_CCHPP;

	_hoops_PCIPP (*name, _hoops_ACIPP);
	_hoops_CCHPP = &_hoops_SPHHR->table[_hoops_ACIPP & (_hoops_SPHHR->size - 1)];

	ALLOC (type, _hoops_PIIIR);
	if ((type->next = *_hoops_CCHPP) != null)
		type->next->backlink = &type->next;
	*_hoops_CCHPP = type;
	type->backlink = _hoops_CCHPP;
	type->type = _hoops_AIIIR;
	type->owner = (_hoops_HPAH *)HOOPS_WORLD;
	type->_hoops_HIHI = 1;					/* _hoops_GAR _hoops_IRS _hoops_SHIR */
	type->_hoops_RRHH = _hoops_IIIIR;	/* _hoops_GAR _hoops_IRS _hoops_SHIR */

	type->id = id;
	type->name.length = name->length;
	type->name.text = name->text;
	type->_hoops_RCIIR = _hoops_RCIIR;
	type->_hoops_RHSAA = _hoops_RHSAA;
	type->_hoops_GHSAA = _hoops_GHSAA;

	type->_hoops_CIIIR = _hoops_CIIIR;

	++_hoops_SPHHR->count;

	return type;
}

GLOBAL_FUNCTION _hoops_RPSAP * HI_Define_Nice_KOption (
	_hoops_GCIIR *		_hoops_SPHHR,
	long					id,
	const KName *			name,
	int						_hoops_RCIIR,
	int						_hoops_RHSAA,
	bool					_hoops_GHSAA,
	_hoops_GCIIR *		_hoops_CIIIR) {
	_hoops_RPSAP *			type = null;
#ifndef DISABLE_UNICODE_OPTIONS
	int						_hoops_ACIPP;
	_hoops_RPSAP **			_hoops_CCHPP;

	_hoops_HCIPP (*name, _hoops_ACIPP);
	_hoops_CCHPP = (_hoops_RPSAP **)&_hoops_SPHHR->table[_hoops_ACIPP & (_hoops_SPHHR->size - 1)];

	ALLOC (type, _hoops_RPSAP);
	if ((type->next = *_hoops_CCHPP) != null)
		type->next->backlink = &type->next;
	*_hoops_CCHPP = type;
	type->backlink = _hoops_CCHPP;
	type->type = _hoops_AIIIR;
	type->owner = (_hoops_HPAH *)HOOPS_WORLD;
	type->_hoops_HIHI = 1;					/* _hoops_GAR _hoops_IRS _hoops_SHIR */
	type->_hoops_RRHH = _hoops_IIIIR;	/* _hoops_GAR _hoops_IRS _hoops_SHIR */

	type->id = id;
	type->_hoops_SIHSA.length = name->length;
	type->_hoops_SIHSA._hoops_IPPPP = name->_hoops_IPPPP;
	type->_hoops_RCIIR = _hoops_RCIIR;
	type->_hoops_RHSAA = _hoops_RHSAA;
	type->_hoops_GHSAA = _hoops_GHSAA;

	type->_hoops_CIIIR = _hoops_CIIIR;

	++_hoops_SPHHR->count;
#endif

	return type;
}

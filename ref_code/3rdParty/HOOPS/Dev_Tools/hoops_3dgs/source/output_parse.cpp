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
 * $Id: obf_tmp.txt 1.64 2010-10-06 19:16:14 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "path.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_APGCC {
	_hoops_CICIH		action;
	_hoops_CRCP *				newowner;
	_hoops_RSAPR *			_hoops_PPGCC;
	Key						_hoops_ACHPA;
	void *					info;
};


local void _hoops_HPGCC (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_CAGSA,
	void *					info) {
	_hoops_APGCC *	pass = (_hoops_APGCC *)info;
	Key						_hoops_ACHPA;
	Subsegment *			_hoops_AIGSA = null;

	if (pass->_hoops_PPGCC == null) {
		/* _hoops_RHGCA "_hoops_PGGPR" _hoops_CCA _hoops_IRS ^, ., _hoops_PAR / (_hoops_RH _hoops_SRRPR) */

		Subsegment	*_hoops_SSGPR;
		_hoops_CRCP				*_hoops_SRCP = pass->newowner;

		_hoops_SSGPR = _hoops_SRCP->owner->_hoops_RGRPR;

		if (_hoops_SSGPR != (Subsegment *)_hoops_SRCP) {
			do _hoops_AIGSA = _hoops_SSGPR;
			_hoops_RGGA ((_hoops_SSGPR = _hoops_SSGPR->next) == (Subsegment *)_hoops_SRCP);
		}

		_hoops_ACHPA = (*pass->action)(_hoops_RIGC, _hoops_CAGSA, _hoops_SRCP->owner, _hoops_SRCP->backlink,
								 _hoops_AIGSA, &_hoops_SRCP->name, true, pass->info);
	}
	else {
		Subsegment	**_hoops_ASRGR = &pass->newowner->_hoops_RGRPR;
		Subsegment	*x = null;
		_hoops_HCRPR			*_hoops_IPGCC;
		bool		_hoops_PIGSA = false;

		if (pass->_hoops_PPGCC->type == _hoops_PRPPR)
			_hoops_IPGCC = &_hoops_CAGSA->name;
		else
			_hoops_IPGCC = &pass->_hoops_PPGCC->_hoops_AGPPR;

		if (_hoops_IPGCC->length == 0) { /* _hoops_PSP-_hoops_RSIRR _hoops_CAGH */
			_hoops_RGGA ((x = *_hoops_ASRGR) == null) {
				if (x->type == _hoops_IRCP) break;
				_hoops_AIGSA = x;
				_hoops_ASRGR = &x->next;
			}
		}
		else {
			if (HI_Fast_Lookup_Available(pass->newowner, false)) {
				LOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
				_hoops_AIGSA = HI_Find_Fast_Lookup_Predecessor (pass->newowner, false, null, _hoops_IPGCC->text);
				UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);

				if (_hoops_AIGSA != null) {
					_hoops_ASRGR = &_hoops_AIGSA->next;

					x = *_hoops_ASRGR;

					if (x != null &&
						x->type == _hoops_IRCP &&
						!BIT (x->_hoops_RRHH, _hoops_HGAGR) &&
						HI_Compare_Names(&((_hoops_CRCP *)x)->name, _hoops_IPGCC) == 0) {
						
						_hoops_PIGSA = true;
					}
				}
			}
			
			if (_hoops_AIGSA == null) {
				int	_hoops_SCASA=0;

				_hoops_RGGA ((x = *_hoops_ASRGR) == null) {
					int				cmp;

					if (x->type == _hoops_IRCP &&
						!BIT (x->_hoops_RRHH, _hoops_HGAGR) &&
						(cmp = HI_Compare_Names(&((_hoops_CRCP *)x)->name, _hoops_IPGCC)) >= 0) {
						if (cmp == 0) _hoops_PIGSA = true;
						break;
					}

					_hoops_SCASA++;
					_hoops_AIGSA = x;
					_hoops_ASRGR = &x->next;
				}
							
				if (_hoops_SCASA > 128 && !BIT (HOOPS_WORLD->_hoops_IRARR, _hoops_IGPSA)) {
					LOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
					HI_Create_Fast_Lookup (pass->newowner, false);
					UNLOCK_MUTEX (HOOPS_WORLD->_hoops_RSASA);
				}
			}


			if (!_hoops_PIGSA && x != null &&
				BIT (pass->newowner->_hoops_PHSI, _hoops_GGPSA)) {
				Subsegment	*_hoops_CPGCC = _hoops_AIGSA;

				/* _hoops_CACH _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_SPGCC */

				_hoops_RGGA ((x = x->next) == null) {
					if (x->type == _hoops_IRCP &&
						!BIT (x->_hoops_RRHH, _hoops_HGAGR) &&
						_hoops_RAHSR (((_hoops_CRCP *)x)->name, *_hoops_IPGCC)) {
						/* _hoops_GSGI _hoops_SCH! */
						_hoops_ASRGR = x->backlink;
						_hoops_AIGSA = _hoops_CPGCC;
						break;
					}
					_hoops_CPGCC = x;
				}
			}
		}

		if (pass->_hoops_PPGCC->type == _hoops_PRPPR)
			_hoops_ACHPA = (*pass->action)(_hoops_RIGC, _hoops_CAGSA, pass->newowner,
									 _hoops_ASRGR, _hoops_AIGSA, null, _hoops_PIGSA, pass->info);
		else {
			_hoops_IPGCC = &pass->_hoops_PPGCC->_hoops_AGPPR;

			if (_hoops_RAHSR (_hoops_CAGSA->name, *_hoops_IPGCC))
				_hoops_ACHPA = (*pass->action)(_hoops_RIGC, _hoops_CAGSA, pass->newowner,
										 _hoops_ASRGR, _hoops_AIGSA, null, _hoops_PIGSA, pass->info);
			else
				_hoops_ACHPA = (*pass->action)(_hoops_RIGC, _hoops_CAGSA, pass->newowner,
										 _hoops_ASRGR, _hoops_AIGSA, _hoops_IPGCC, _hoops_PIGSA, pass->info);
		}
	}

	/* _hoops_ASRC _hoops_SIC _hoops_RPP _hoops_SPR, 0 _hoops_RPP _hoops_PIRC, -1 _hoops_RPP _hoops_AHPH */
	if (_hoops_ACHPA != 0) pass->_hoops_ACHPA = (pass->_hoops_ACHPA == 0) ? _hoops_ACHPA : -1;
}

local void _hoops_GHGCC (
	char const		*_hoops_GICII,
	char const		*_hoops_HICIH,
	char const		*_hoops_IICIH,
	_hoops_RSAPR	*path) {
	char			buf[MAX_ERRMSG];

	HE_ERROR2 (HEC_SYNTAX, HES_SEGMENT,

		Sprintf_SS (buf, "Can't put '%s' into '%s' -", _hoops_HICIH, _hoops_IICIH),
		_hoops_GICII);

	if (path != null) HI_Free_Path (path);
}

struct _hoops_RHGCC	{
	struct _hoops_RHGCC	*prev;
	_hoops_RSAPR	*_hoops_CIPPR;
};	

GLOBAL_FUNCTION Key HI_Output_Parse (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_HICIH,
	char const *			_hoops_IICIH,
	_hoops_CICIH		action,
	void *					info) {
	_hoops_RSAPR *			_hoops_CIPPR;
	_hoops_RSAPR *			_hoops_AHGCC,*_hoops_PHGCC,*_hoops_PPGCC = null;
	_hoops_CRCP *				_hoops_SRCP = null;
	bool					_hoops_ACGSA = false;
	_hoops_APGCC	pass;
	struct _hoops_RHGCC *		_hoops_RCSHR=null,*_hoops_HHGCC;

	if ((_hoops_CIPPR = HI_Parse_Path (_hoops_RIGC, _hoops_IICIH, _hoops_RPPSA|_hoops_AIPPR)) == null) {
		/* _hoops_RIHH (_hoops_AIAH _hoops_CRPPR) - _hoops_AHCI _hoops_RSIRR */
		return _hoops_SHSSR;
	}

	_hoops_AHGCC = _hoops_CIPPR;

	_hoops_PCCAR {
		local	const char		_hoops_IHGCC[] =
				"The only wildcard allowed in output name is a '*' at the end";

		do switch (_hoops_PHGCC = _hoops_CIPPR->next, _hoops_CIPPR->type) {
			default:	{
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected token type");
				return _hoops_SHSSR;
			}	/* _hoops_IHSA; */

			case _hoops_SGPPR:
			case _hoops_PGPPR:
			case _hoops_HGPPR:
			case _hoops_IGPPR:
			case _hoops_CGPPR: {
				_hoops_GHGCC (
			"A <, >, {, }, or , was found during expansion of the output name",
					_hoops_HICIH, _hoops_IICIH, _hoops_AHGCC);
				return _hoops_SHSSR;
			}	/* _hoops_IHSA; */

			case _hoops_HSAPR:
			case _hoops_PGRHH:
			case _hoops_SSAPR: {
				_hoops_GHGCC (_hoops_IHGCC, _hoops_HICIH, _hoops_IICIH, _hoops_AHGCC);
				return _hoops_SHSSR;
			}	/* _hoops_IHSA; */

			case _hoops_CSAPR: {
				if (_hoops_SRCP == null) _hoops_SRCP = HOOPS_WORLD->root;
				_hoops_ACGSA = false;
			}	break;

			case _hoops_ISAPR: {
				_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;
				_hoops_ACGSA = true;
			}	break;

			case _hoops_HRPPR: {
				if (_hoops_PPGCC != null) {
					Subsegment	*x;

					if (_hoops_PPGCC->type == _hoops_PRPPR) {
						_hoops_GHGCC (_hoops_IHGCC, _hoops_HICIH, _hoops_IICIH, _hoops_AHGCC);
						return _hoops_SHSSR;
					}

					if (_hoops_SRCP == null)
						_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

					if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) x = null;
					else if ((x = _hoops_SRCP->_hoops_RGRPR) != null) do {
						if (x->type >= _hoops_IRCP) {
							if (x->type == _hoops_IRCP) {
								if (!BIT (x->_hoops_RRHH, _hoops_HGAGR) &&
									_hoops_RAHSR (((_hoops_CRCP *)x)->name,
												 _hoops_PPGCC->_hoops_AGPPR)) {
									_hoops_SRCP = (_hoops_CRCP *)x;
									break;
								}
							}
							else if (!BIT (_hoops_SRCP->_hoops_PHSI,
										   _hoops_GGPSA)) {
								x = null;
								break;
							}
						}
					} while ((x = x->next) != null);

					if (x == null) {
						_hoops_GHGCC (Sprintf_PN (null,
								   "Containing segment '%p/%n' does not exist",
								   _hoops_SRCP, &_hoops_PPGCC->_hoops_AGPPR),
								   _hoops_HICIH, _hoops_IICIH, _hoops_AHGCC);
						return _hoops_SHSSR;
					}

					_hoops_PPGCC = null;
				}

				_hoops_SRCP = (_hoops_CRCP *)_hoops_SISIR (_hoops_RIGC, _hoops_CIPPR->key, _hoops_SRCP);
				_hoops_ACGSA = true;
				_hoops_PPGCC = null;
			}	break;

			case _hoops_RGPPR: {
				if (_hoops_PHGCC != null) {
					ALLOC (_hoops_HHGCC, struct _hoops_RHGCC);
					_hoops_HHGCC->prev = _hoops_RCSHR;
					_hoops_HHGCC->_hoops_CIPPR = _hoops_PHGCC;
					_hoops_RCSHR = _hoops_HHGCC;
				}
				_hoops_PHGCC = _hoops_CIPPR->expansion;
			}	break;

			case _hoops_GRPPR:
			case _hoops_RRPPR: {
			}	break;

			case _hoops_GGPPR:
			case _hoops_ARPPR:
			case _hoops_PRPPR: {
				if (_hoops_SRCP == null)
					_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;

				if (_hoops_PPGCC != null) {
					Subsegment	*x;

					if (_hoops_PPGCC->type == _hoops_PRPPR) {
						_hoops_GHGCC (_hoops_IHGCC, _hoops_HICIH, _hoops_IICIH, _hoops_AHGCC);
						return _hoops_SHSSR;
					}

					if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) x = null;
					else if ((x = _hoops_SRCP->_hoops_RGRPR) != null) do {
						if (x->type >= _hoops_IRCP) {
							if (x->type == _hoops_IRCP) {
								if (!BIT (x->_hoops_RRHH, _hoops_HGAGR) &&
									_hoops_RAHSR (((_hoops_CRCP *)x)->name,
												 _hoops_PPGCC->_hoops_AGPPR)) {
									_hoops_SRCP = (_hoops_CRCP *)x;
									break;
								}
							}
							else if (!BIT (_hoops_SRCP->_hoops_PHSI,
										   _hoops_GGPSA)) {
								x = null;
								break;
							}
						}
					} while ((x = x->next) != null);

					if (x == null) {
						_hoops_GHGCC (Sprintf_PN (null,
								   "Containing segment '%p/%n' does not exist",
								   _hoops_SRCP, &_hoops_PPGCC->_hoops_AGPPR),
								   _hoops_HICIH, _hoops_IICIH, _hoops_AHGCC);
						return _hoops_SHSSR;
					}
				}

				if (_hoops_CIPPR->type == _hoops_GGPPR) {
					_hoops_SRCP = _hoops_SRCP->owner;
					_hoops_ACGSA = false;
					_hoops_PPGCC = null;
				}
				else {
					if (_hoops_ACGSA) {
						_hoops_GHGCC ("Output spec can't contain compound names",
									_hoops_HICIH, _hoops_IICIH, _hoops_AHGCC);
						return _hoops_SHSSR;
					}

					_hoops_ACGSA = true;
					_hoops_PPGCC = _hoops_CIPPR;
				}
			}	break;
		} while ((_hoops_CIPPR = _hoops_PHGCC) != null);

		if ((_hoops_HHGCC = _hoops_RCSHR) == null)
			break;

		_hoops_CIPPR = _hoops_RCSHR->_hoops_CIPPR;
		_hoops_RCSHR = _hoops_RCSHR->prev;
		FREE (_hoops_HHGCC, struct _hoops_RHGCC);
	}

	pass.action = action;
	pass.newowner = _hoops_SRCP;
	pass._hoops_PPGCC = _hoops_PPGCC;
	pass._hoops_ACHPA = 0;
	pass.info = info;

	/* _hoops_PIP: _hoops_CHGCC _hoops_SHGCC _hoops_HGISR _hoops_IH _hoops_RH _hoops_GIGCC */
	HI_For_Each (_hoops_RIGC, _hoops_HICIH, true, _hoops_HPGCC, (void *)&pass);

	HI_Free_Path (_hoops_AHGCC);

	return pass._hoops_ACHPA;
}

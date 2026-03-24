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
 * $Id: obf_tmp.txt 1.55 2010-11-08 23:46:50 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "adt.h"


GLOBAL_FUNCTION void HI_Propagate_Maybes (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_ACHR				what)
{
	_hoops_ICIIR(_hoops_RIGC);

	if (_hoops_SRCP != null) do {
		if (!HOOPS_WORLD->_hoops_AGHGI &&
			BIT (what & ~_hoops_SRCP->_hoops_RCGC, _hoops_AHASA) && _hoops_SRCP->owner->type == _hoops_IRCP && !ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR | _hoops_SHSIR)) {
			_hoops_CRCP *		owner = _hoops_SRCP->owner;
			Subsegment *	_hoops_AIGSA;

			//_hoops_HPPSA (_hoops_IPPSA->_hoops_HHSIR);			// _hoops_SHR _hoops_GIAA _hoops_IRS _hoops_IHSIR?
			HI_Create_Fast_Lookup (owner, true);
			HI_Remove_Fast_Lookup_Item (owner, true, (Subsegment *)_hoops_SRCP);
			_hoops_SRCP->_hoops_RCGC |= what;
			HI_Add_Fast_Lookup_Item (owner, true, (Subsegment *)_hoops_SRCP);

			_hoops_AIGSA = HI_Find_Fast_Lookup_Predecessor (owner, true, (Subsegment *)_hoops_SRCP, null);
			//_hoops_SPPSA (_hoops_IPPSA->_hoops_HHSIR);

			_hoops_CIGPR (_hoops_RIGC, _hoops_SRCP);
			if (_hoops_AIGSA != null) {
				if ((_hoops_SRCP->next = _hoops_AIGSA->next) != null)
					_hoops_SRCP->next->backlink = &_hoops_SRCP->next;
				_hoops_SRCP->backlink = &_hoops_AIGSA->next;
				_hoops_AIGSA->next = (Subsegment *)_hoops_SRCP;
			}
			else {
				if ((_hoops_SRCP->next = owner->_hoops_RGRPR) != null)
					_hoops_SRCP->next->backlink = &_hoops_SRCP->next;
				_hoops_SRCP->backlink = &owner->_hoops_RGRPR;
				owner->_hoops_RGRPR = (Subsegment *)_hoops_SRCP;
			}

			_hoops_SRCP->_hoops_RRHH |= _hoops_PASIR;
			owner->_hoops_PHSI |= _hoops_GGPSA;
		}
		else
			_hoops_SRCP->_hoops_RCGC |= what;

		Xref const *		_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR();
		if (_hoops_AHICA != null) do {
			if (_hoops_AHICA->type == _hoops_AGRPR) {
				if (!BIT (_hoops_AHICA->owner->_hoops_RRHH, _hoops_HIRIR) &&
					!ALLBITS (_hoops_AHICA->owner->_hoops_RCGC, what)) {
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_AHICA->owner, what);
				}
			}
#ifndef DISABLE_STYLE_SEGMENT
			else {

				/* _hoops_PAGA: _hoops_PIRGS _hoops_RHAP _hoops_ASHHP */

				_hoops_ACHR	_hoops_CAPRA = what & (
					_hoops_ASPCR | _hoops_HPRRA |
					_hoops_PPHGP |
					_hoops_HPHGP |
					_hoops_RPHGP |
					_hoops_APHGP |
					_hoops_IPHGP |
					_hoops_PSPCR |
					_hoops_ASRRA |
					_hoops_AHHGP | _hoops_CPHGP);

				if (!ALLBITS (_hoops_AHICA->owner->_hoops_RCGC, _hoops_CAPRA))
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_AHICA->owner, _hoops_CAPRA);
			}
#endif
		} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

		_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_SRCP);

		if (_hoops_APAPA != null) {
			_hoops_APAPA->ResetCursor();
			_hoops_PHIP *	_hoops_RRA;
			while((_hoops_RRA = _hoops_APAPA->PeekCursor()) != null) {
				if (!BIT (_hoops_RRA->owner->_hoops_RRHH, _hoops_HIRIR) &&
					!ALLBITS (_hoops_RRA->owner->_hoops_RCGC, what)) {
						HI_Propagate_Maybes (_hoops_RIGC, _hoops_RRA->owner, what);
				}
				_hoops_APAPA->AdvanceCursor();
			}
		}

		_hoops_SRCP = _hoops_SRCP->owner;
	} while (_hoops_SRCP->type != _hoops_PRAIR && _hoops_SRCP->type != _hoops_PIRIR &&
			 (what &= ~_hoops_SRCP->_hoops_RCGC) != 0);
}

GLOBAL_FUNCTION void HI_Propagate_Maybes_Across_Styles (
	_hoops_CRCP				*_hoops_SRCP,
	_hoops_ACHR			what) {
	Xref					*_hoops_AHICA;

	_hoops_SRCP->_hoops_RCGC |= what;

#ifndef DISABLE_STYLE_SEGMENT
	if ((_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR()) != null) do {
		if (_hoops_AHICA->type == HK_STYLE) {
			if (!ALLBITS (_hoops_AHICA->owner->_hoops_RCGC, what)) {
				HI_Propagate_Maybes_Across_Styles (_hoops_AHICA->owner, what);
			}
		}
	} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
#endif
}

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
 * $Id: obf_tmp.txt 1.85 2010-10-27 19:47:46 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "please.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hc_standalone_proto.h"
#include "hpserror.h"
#include "adt.h"


local void _hoops_HRRPH (
	_hoops_GGAGR *		_hoops_GHRI) 
{

	/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_IRRPH _hoops_GSGR _hoops_CIIA (_hoops_PAR _hoops_CRRPH _hoops_IRS _hoops_CCAH _hoops_SRRPH
	 * _hoops_GSGR) _hoops_HGCR _hoops_RH _hoops_GARPH _hoops_GGR _hoops_CAPRH...
	 */
	if (_hoops_GHRI->_hoops_RCSHR._hoops_SPIAP != 0 &&
		(_hoops_GHRI->_hoops_CPCR._hoops_SPIAP == 0 ||
		 (_hoops_GHRI->_hoops_RCSHR._hoops_GHIAP != 0 &&
		  (_hoops_GHRI->_hoops_CPCR._hoops_GHIAP == 0 ||
		   _hoops_GHRI->_hoops_RCSHR._hoops_SRPIR->owner !=
		   _hoops_GHRI->_hoops_CPCR._hoops_SRPIR->owner)))) {
		/* _hoops_ASAC _hoops_IASI _hoops_RHGS _hoops_CIIA, _hoops_RPP _hoops_GII, _hoops_PPR _hoops_CIH _hoops_RH _hoops_PPGS */
		if (_hoops_GHRI->_hoops_HRPIR.length > 0) {
			if ((_hoops_GHRI->_hoops_ARPIR == null ||
				 !_hoops_RARPH (_hoops_GHRI->_hoops_HRPIR,
								_hoops_GHRI->_hoops_ARPIR->string)) &&
				HOOPS_WORLD->_hoops_PRGHP > 0) {
				_hoops_RRPIR	*sl;
				ALLOC (sl, _hoops_RRPIR);
				if ((sl->prev = _hoops_GHRI->_hoops_ARPIR) != null)
					sl->prev->next = sl;
				sl->next = null;
				_hoops_GHRI->_hoops_ARPIR = sl;
				HI_Copy_KName (&_hoops_GHRI->_hoops_HRPIR, &sl->string);

				if (_hoops_GHRI->_hoops_HHIAP < HOOPS_WORLD->_hoops_PRGHP)
					++_hoops_GHRI->_hoops_HHIAP;
				else {
					sl = _hoops_GHRI->_hoops_ARPIR;
					_hoops_RGGA (sl->prev == null) sl = sl->prev;
					sl->next->prev = null;
					_hoops_PRPIR (sl->string);
					FREE (sl, _hoops_RRPIR);
				}
			}
			_hoops_PRPIR (_hoops_GHRI->_hoops_HRPIR);
			_hoops_GHRI->_hoops_HRPIR.length = 0;
			_hoops_GHRI->_hoops_RHIAP = 0;
		}
	}
}


GLOBAL_FUNCTION void HI_Update_Events (
	_hoops_AIGPR *	_hoops_RIGC) 
{
#ifndef DISABLE_EVENTS
	_hoops_GGAGR *					_hoops_GHRI;

	UNREFERENCED(_hoops_RIGC);

	/* _hoops_ARAS _hoops_RHIR & _hoops_CRGS _hoops_RH _hoops_PCSHA _hoops_IS _hoops_HHPR & _hoops_HHSP _hoops_CGSI _hoops_GAR
	   _hoops_IRPR. _hoops_CGP _hoops_RH _hoops_PCSHA _hoops_PAH'_hoops_RA _hoops_HHPR, _hoops_PSCR _hoops_HPGGR _hoops_SCH _hoops_GAR
	   _hoops_HAR _hoops_SISPR _hoops_HGPP _hoops_IRS _hoops_SISS.
	 */
	_hoops_CSPPR();

	HOOPS_WORLD->_hoops_AARPH = false;

	if ((_hoops_GHRI = HOOPS_WORLD->_hoops_CISHA) != null)
	do if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_PARPH)) {
		if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA)) {
			if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR))
				_hoops_GHRI->_hoops_CGPIR &= ~_hoops_PARPH;
			else  /* _hoops_HAR _hoops_HHPHA - _hoops_HPPR _hoops_GICS _hoops_GGR _hoops_IRS _hoops_IGRH */
				HOOPS_WORLD->_hoops_AARPH = true;
		}
		else {
			_hoops_GGAGR *	_hoops_HARPH;

			/* _hoops_AA _hoops_CIPH _hoops_PGAP _hoops_GCA _hoops_HCHAR _hoops_HPGR _hoops_GIPR _hoops_RH _hoops_CISI
			 * _hoops_PPR _hoops_RH _hoops_RCAPR...
			 */
			if (_hoops_GHRI->_hoops_RCSHR._hoops_SPIAP != 0)
				_hoops_HRRPH (_hoops_GHRI);

			/* _hoops_HA _hoops_IPS _hoops_RCAPR _hoops_HSAGA _hoops_IS _hoops_CISI _hoops_HSAGA... */

			_hoops_HARPH = _hoops_GHRI->_hoops_CPCR.target;
			if ((_hoops_GHRI->_hoops_CPCR.target = _hoops_GHRI->_hoops_RCSHR.target) != null)
				if (_hoops_GHRI->_hoops_CPCR.target != _hoops_GHRI)
					_hoops_PRRH (_hoops_GHRI->_hoops_CPCR.target);

			if (_hoops_GHRI->_hoops_CPCR._hoops_SRPIR != null)
				_hoops_HPRH (_hoops_GHRI->_hoops_CPCR._hoops_SRPIR);
			if ((_hoops_GHRI->_hoops_CPCR._hoops_SRPIR = _hoops_GHRI->_hoops_RCSHR._hoops_SRPIR) != null)
				_hoops_PRRH (_hoops_GHRI->_hoops_CPCR._hoops_SRPIR);

			_hoops_GHRI->_hoops_CPCR._hoops_GPIAP = _hoops_GHRI->_hoops_RCSHR._hoops_GPIAP;
			_hoops_GHRI->_hoops_CPCR._hoops_RPIAP = _hoops_GHRI->_hoops_RCSHR._hoops_RPIAP;
			_hoops_GHRI->_hoops_CPCR._hoops_APIAP = _hoops_GHRI->_hoops_RCSHR._hoops_APIAP;
			_hoops_GHRI->_hoops_CPCR._hoops_PPIAP = _hoops_GHRI->_hoops_RCSHR._hoops_PPIAP;
			_hoops_GHRI->_hoops_CPCR._hoops_HPIAP = _hoops_GHRI->_hoops_RCSHR._hoops_HPIAP;
			_hoops_GHRI->_hoops_CPCR._hoops_IPIAP = _hoops_GHRI->_hoops_RCSHR._hoops_IPIAP;
			_hoops_GHRI->_hoops_CPCR._hoops_SPIAP = _hoops_GHRI->_hoops_RCSHR._hoops_SPIAP;
			_hoops_GHRI->_hoops_CPCR._hoops_GHIAP = _hoops_GHRI->_hoops_RCSHR._hoops_GHIAP;

			if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_IARPH)) {
				_hoops_GHRI->_hoops_CPCR._hoops_CPIAP = _hoops_GHRI->_hoops_RCSHR._hoops_CPIAP;

				if (_hoops_GHRI->_hoops_RCSHR._hoops_IRPIR == null) {
					if (_hoops_GHRI->_hoops_CPCR._hoops_IRPIR != null) {
						FREE_ARRAY (_hoops_GHRI->_hoops_CPCR._hoops_IRPIR, _hoops_CRPIR + 1, int);
						_hoops_GHRI->_hoops_CPCR._hoops_IRPIR = null;
					}
				}
				else {
					int *	in;
					int *	_hoops_PAGR;

					if ((_hoops_PAGR = _hoops_GHRI->_hoops_CPCR._hoops_IRPIR) == null) {
						ALLOC_ARRAY (_hoops_PAGR, _hoops_CRPIR + 1, int);
						_hoops_GHRI->_hoops_CPCR._hoops_IRPIR = _hoops_PAGR;
					}

					in = _hoops_GHRI->_hoops_RCSHR._hoops_IRPIR;
					int tmp = _hoops_CRPIR + 1;
					do {
						*_hoops_PAGR++ = *in++;
					} _hoops_RGGA (--tmp == 0);
				}
			}


			/* _hoops_CRGS _hoops_RH _hoops_PCSHA(_hoops_GRI) _hoops_AHCA _hoops_CGSI... */

			if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_CARPH)) {
				_hoops_APSHA				_hoops_AGPCA;

				if (_hoops_GHRI->_hoops_CPCR.target != null &&
					BIT (_hoops_GHRI->_hoops_CPCR.target->_hoops_RRHH, _hoops_HGAGR)) {
					_hoops_GHRI->_hoops_CPCR._hoops_HPIAP = 0;
					_hoops_GHRI->_hoops_CPCR._hoops_IPIAP = 0;
					if (_hoops_GHRI->_hoops_CPCR.target != _hoops_GHRI)
						_hoops_HPRH (_hoops_GHRI->_hoops_CPCR.target);
					if (_hoops_HARPH == _hoops_GHRI) 
						_hoops_HARPH = null;
					_hoops_GHRI->_hoops_CPCR.target = null;
				}

				_hoops_AGPCA = _hoops_GHRI->_hoops_CHIAP;

				if (_hoops_GHRI->_hoops_CPCR.target != null &&
					_hoops_GHRI->_hoops_CPCR._hoops_HPIAP > 0) {

					_hoops_AGPCA |= _hoops_SARPH;
				}

				if (_hoops_AGPCA != _hoops_GHRI->_hoops_SHIAP ||
					_hoops_HARPH != _hoops_GHRI->_hoops_CPCR.target) {
					_hoops_APSHA		_hoops_CCCIR;
					bool				_hoops_GPRPH = false;

					if ((!_hoops_GHRI->_hoops_SHIAP && _hoops_AGPCA) ||
						_hoops_HARPH != _hoops_GHRI->_hoops_CPCR.target) {

						_hoops_GHRI->_hoops_GIIAP.action = 0;

						if (_hoops_GHRI->_hoops_CPCR.target == _hoops_GHRI &&
							BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_RPRPH)) {
							if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_APRPH, null))
								_hoops_GHRI->_hoops_CGPIR &= ~_hoops_RPRPH;
						}

						if ((_hoops_GHRI->_hoops_CPCR.target != _hoops_GHRI ||
							 !BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_RPRPH)) &&
							_hoops_GHRI->_hoops_CPCR.target != null &&
							BIT (_hoops_GHRI->_hoops_CPCR.target->_hoops_CGPIR, _hoops_PPRPH)) {
							if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI->_hoops_CPCR.target, _hoops_HPRPH, null)) {
								HE_WARNING (HEC_EVENT_HANDLER, HES_DELETED_CURSOR,
										Sprintf_P (null, "The '%p' device does not have a cursor", _hoops_GHRI->_hoops_CPCR.target->owner));
								_hoops_GHRI->_hoops_CPCR.target->_hoops_CGPIR &= ~_hoops_PPRPH;
							}
						}
					}
					if ((_hoops_GHRI->_hoops_SHIAP && !_hoops_AGPCA) ||
						_hoops_HARPH != _hoops_GHRI->_hoops_CPCR.target) {
						if (_hoops_HARPH == _hoops_GHRI &&
							BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_RPRPH))
							_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_IPRPH, null);
						else if (_hoops_HARPH != null &&
								 BIT (_hoops_HARPH->_hoops_CGPIR, _hoops_PPRPH))
							_hoops_HISAA (_hoops_RIGC, _hoops_HARPH, _hoops_CPRPH, null);
					}

					if (_hoops_AGPCA &&
						_hoops_GHRI->_hoops_CPCR.target != null &&
						_hoops_GHRI->_hoops_CPCR.target != _hoops_GHRI &&
						BIT (_hoops_GHRI->_hoops_CPCR.target->_hoops_CGPIR, _hoops_PPRPH))

						_hoops_AGPCA |= _hoops_SPSHA | _hoops_IPSHA;

					_hoops_CCCIR = _hoops_AGPCA ^ _hoops_GHRI->_hoops_SHIAP;

					if (BIT (_hoops_CCCIR, _hoops_CPSHA))
						if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI,
							BIT (_hoops_AGPCA, _hoops_CPSHA) ? _hoops_SPRPH :
													   _hoops_GHRPH, null))
							_hoops_GPRPH = true;

					if (BIT (_hoops_CCCIR, _hoops_HPSHA))
						if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI,
							BIT (_hoops_AGPCA, _hoops_HPSHA) ? _hoops_RHRPH :
														 _hoops_AHRPH, null))
							_hoops_GPRPH = true;

					if (BIT (_hoops_CCCIR, _hoops_SPSHA))
						if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI,
							BIT (_hoops_AGPCA, _hoops_SPSHA) ? _hoops_PHRPH :
															 _hoops_HHRPH, null))
							_hoops_GPRPH = true;

					if (BIT (_hoops_CCCIR, _hoops_IPSHA))
						if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI,
							BIT (_hoops_AGPCA, _hoops_IPSHA) ? _hoops_IHRPH :
															   _hoops_CHRPH, null))
							_hoops_GPRPH = true;

					if (_hoops_GPRPH) {
						HE_ERROR2 (HEC_EVENT_HANDLER, HES_DELETED_LOCATOR,
							"Cannot enable selection/location events -",
								Sprintf_P (null, "'%p' doesn't have a locater attached", _hoops_GHRI->owner));

						_hoops_GHRI->_hoops_CGPIR &= ~_hoops_CARPH;
					}
					else {
						_hoops_GHRI->_hoops_SHIAP = _hoops_AGPCA;

						/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HHACR _hoops_CPHP _hoops_ARGPR,
						   _hoops_SHH _hoops_RCRR _hoops_IS _hoops_IIS _hoops_SCH _hoops_RHIR */

						if (BIT (_hoops_CCCIR, _hoops_GHRI->_hoops_GIIAP.action))
							_hoops_GHRI->_hoops_GIIAP.action = false;
					}
				}
			}

			if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SHRPH)) {
				if (_hoops_GHRI->_hoops_CPCR._hoops_SRPIR != null &&
					BIT (_hoops_GHRI->_hoops_CPCR._hoops_SRPIR->_hoops_RRHH, _hoops_HGAGR)) {
					_hoops_GHRI->_hoops_CPCR._hoops_GHIAP = 0;
					_hoops_HPRH (_hoops_GHRI->_hoops_CPCR._hoops_SRPIR);
					_hoops_GHRI->_hoops_CPCR._hoops_SRPIR = null;
				}

				if (_hoops_GHRI->_hoops_CPCR._hoops_SPIAP > 0 ||
					_hoops_GHRI->_hoops_CPCR._hoops_CPIAP > 0) {
					if (!_hoops_GHRI->_hoops_IHIAP) {

						if (_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_GIRPH, null))
							_hoops_GHRI->_hoops_IHIAP = true;
						else {
							HE_ERROR2 (HEC_EVENT_HANDLER, HES_DELETED_KEYBOARD,
								"Cannot enable string/button events -",
									Sprintf_P (null, "'%p' doesn't have a keyboard attached", _hoops_GHRI->owner));

							_hoops_GHRI->_hoops_CGPIR &= ~_hoops_SHRPH;
						}
					}
					else if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_IARPH)) {
						if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_RIRPH, null))
							_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
										"Can't modify string/button events");
					}
				}
				else {
					if (_hoops_GHRI->_hoops_IHIAP) {
						_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_AIRPH, null);
						_hoops_GHRI->_hoops_IHIAP = false;
					}
				}
			}

			if (_hoops_GHRI->_hoops_SHIAP ||
					_hoops_GHRI->_hoops_IHIAP)
				_hoops_GHRI->_hoops_CGPIR |= _hoops_PIRPH;
			else
				_hoops_GHRI->_hoops_CGPIR &= ~_hoops_PIRPH;

			_hoops_GHRI->_hoops_CGPIR &= ~(_hoops_PARPH|_hoops_IARPH);

			if (_hoops_HARPH != null && _hoops_HARPH != _hoops_GHRI)
				_hoops_HPRH (_hoops_HARPH);
		}
	}
	_hoops_RGGA ((_hoops_GHRI = _hoops_GHRI->_hoops_CISHA) == null);

	_hoops_IRRPR();
#endif
}



local char const *_hoops_HIRPH (
	Type			type) {

	switch (type) {
		case _hoops_CRIIR:		return "button";
		case _hoops_AAIIR:		return "location";
		case _hoops_SAIIR:	return "selection";
		case _hoops_GIIIR:		return "special";
		case _hoops_PHIIR:		return "wakeup";
		case _hoops_RHIIR:		return "string";
		default:					return "internal error - bad trouble";
	}
}


GLOBAL_FUNCTION _hoops_HISHA * HI_Current_Event (
	_hoops_AIGPR *	_hoops_RIGC,
	Type					type) 
{

	if (_hoops_RIGC->_hoops_PISHA == null) {
		HE_ERROR (HEC_EVENT_HANDLER, HES_INVALID_INPUT, "There is no current event");
		return null;
	}

	if (_hoops_RIGC->_hoops_PISHA->type != type) {
		HE_ERROR (HEC_EVENT_HANDLER, HES_INVALID_TYPE,
				Sprintf_SS (null, "The current event is a '%s' event, not a '%s' event",
				  _hoops_HIRPH (_hoops_RIGC->_hoops_PISHA->type), _hoops_HIRPH (type)));
		return null;
	}

	return _hoops_RIGC->_hoops_PISHA;
}

local bool _hoops_IIRPH (
	Selection_Event				*_hoops_GPIIR) {
	_hoops_CRCP						*_hoops_SRCP;
	_hoops_RISAP				*_hoops_HACAH;

	/* _hoops_IRS _hoops_GHSHA _hoops_PGRRR _hoops_SIAS _hoops_SHH _hoops_CIRPH _hoops_IH _hoops_GRRRA _hoops_PPCIP */

	if (BIT (_hoops_GPIIR->_hoops_APIIR->item->_hoops_RRHH, _hoops_HGAGR))
		return false;


	if (_hoops_GPIIR->_hoops_APIIR->item->type == _hoops_IRCP)
		_hoops_SRCP = (_hoops_CRCP *)_hoops_GPIIR->_hoops_APIIR->item;
	else
		_hoops_SRCP = (_hoops_CRCP *)_hoops_GPIIR->_hoops_APIIR->item->owner;


	if ((_hoops_HACAH = _hoops_GPIIR->_hoops_APIIR->_hoops_SISAP) != null) do {
		_hoops_CRCP				*_hoops_SIRPH;

		if (BIT (_hoops_HACAH->include->_hoops_RRHH, _hoops_HGAGR)) {
			return false;		/* _hoops_CRAA _hoops_PPRGA */
		}

		_hoops_SIRPH = (_hoops_CRCP alter *)_hoops_HACAH->include->_hoops_IGRPR;

		if (_hoops_SRCP != _hoops_SIRPH) do {
			if (_hoops_SRCP->owner->type == _hoops_PRAIR)
				return false; /* _hoops_SR _hoops_GGHP _hoops_CISS _hoops_GSPCA */
		} while ((_hoops_SRCP = _hoops_SRCP->owner) != _hoops_SIRPH);

		_hoops_SRCP = _hoops_HACAH->include->owner;
	} while ((_hoops_HACAH = _hoops_HACAH->prev) != null);


	if (_hoops_GPIIR->target != null && _hoops_SRCP != _hoops_GPIIR->target->owner) do {
		if (_hoops_SRCP->owner->type == _hoops_PRAIR)
			return false; /* _hoops_SR _hoops_GGHP _hoops_CISS _hoops_GSPCA */
	} while ((_hoops_SRCP = _hoops_SRCP->owner) != _hoops_GPIIR->target->owner);


	return true;
}

local bool _hoops_GCRPH (
	_hoops_PAIIR				*_hoops_HAIIR) {

	if (BIT (_hoops_HAIIR->source->_hoops_RRHH, _hoops_HGAGR))
		return false;

	if (_hoops_HAIIR->source->_hoops_CPCR._hoops_IPIAP > 0 &&
		_hoops_HAIIR->source->_hoops_CPCR.target != null &&
		BIT (_hoops_HAIIR->source->_hoops_CPCR.target->_hoops_RRHH, _hoops_HGAGR))
		return false;

	return true;
}

local bool _hoops_RCRPH (
	_hoops_SRIIR			*be) {

	if (BIT (be->source->_hoops_RRHH, _hoops_HGAGR))
		return false;

	return true;
}

local bool _hoops_ACRPH (
	_hoops_AHIIR			*_hoops_GPIIR) {

	if (BIT (_hoops_GPIIR->source->_hoops_RRHH, _hoops_HGAGR))
		return false;

	return true;
}


local void HC_CDECL HI_Show_Event (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					type,
	int						_hoops_SCPRA) 
{
	if (_hoops_RIGC->_hoops_PISHA == null)
		HI_Return_Chars (type, _hoops_SCPRA, "none", 4);

	else switch (_hoops_RIGC->_hoops_PISHA->type) {
		case _hoops_SAIIR: {
			if (_hoops_IIRPH ((Selection_Event *) _hoops_RIGC->_hoops_PISHA))
				HI_Return_Chars (type, _hoops_SCPRA, "selection", 9);
			else
				HI_Return_Chars (type, _hoops_SCPRA, "none", 4);
		}	break;

		case _hoops_AAIIR: {
			if (_hoops_GCRPH ((_hoops_PAIIR *) _hoops_RIGC->_hoops_PISHA))
				HI_Return_Chars (type, _hoops_SCPRA, "location", 8);
			else
				HI_Return_Chars (type, _hoops_SCPRA, "none", 4);
		}	break;

		case _hoops_RHIIR: {
			if (_hoops_ACRPH ((_hoops_AHIIR *) _hoops_RIGC->_hoops_PISHA))
				HI_Return_Chars (type, _hoops_SCPRA, "string", 6);
			else
				HI_Return_Chars (type, _hoops_SCPRA, "none", 4);
		}	break;

		case _hoops_CRIIR: {
			if (_hoops_RCRPH ((_hoops_SRIIR *) _hoops_RIGC->_hoops_PISHA))
				HI_Return_Chars (type, _hoops_SCPRA, "button", 6);
			else
				HI_Return_Chars (type, _hoops_SCPRA, "none", 4);
		}	break;


		case _hoops_PHIIR: {
			HI_Return_Chars (type, _hoops_SCPRA, "wakeup", 6);
		}	break;

		case _hoops_GIIIR: {
			HI_Return_Chars (type, _hoops_SCPRA, "special", 7);
		}	break;


		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized event type");
		}	break;
	}
}


HC_INTERFACE void HC_CDECL HC_Show_Event (
	char *	type) 
{
	_hoops_PAPPR context("Show_Event");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Event (string_buffer);*/\n");
	);

	HI_Show_Event (context, type, -1);
}




GLOBAL_FUNCTION bool HI_Dequeue_Event (
	_hoops_AIGPR *	_hoops_RIGC) 
{
	_hoops_HISHA *					event;

	if ((event = _hoops_RIGC->_hoops_PISHA) != null) {
		_hoops_RIGC->_hoops_PISHA = null;
		_hoops_HPRH (event);
	}

	_hoops_RGGA ((event = _hoops_RIGC->_hoops_PAARH) == null) {
		_hoops_CIGPR (_hoops_RIGC,event);

		if (event == _hoops_RIGC->_hoops_PCRPH) {
			_hoops_HPRH (event);
			_hoops_RIGC->_hoops_PCRPH = null;
		}

		switch (event->type) {
			case _hoops_PHIIR: {
				_hoops_HHIIR *		_hoops_IHIIR = (_hoops_HHIIR *)event;
				_hoops_HRIIR		*_hoops_CHIIR = _hoops_IHIIR->_hoops_CHIIR;

				--_hoops_IHIIR->_hoops_CHIIR->_hoops_HHSAP;

				if (_hoops_CHIIR->_hoops_AHSAP > 0) {
					_hoops_RIGC->_hoops_PISHA = event;
					return true;
				}
			}	break;

			case _hoops_CRIIR: {
				_hoops_SRIIR *		be = (_hoops_SRIIR *)event;
				_hoops_GGAGR	*source = be->source;

				if (!BIT (source->_hoops_CGPIR, _hoops_SGPIR) &&
					source->_hoops_CPCR._hoops_IRPIR != null) {
					int				index;

					index = _hoops_HCRPH(be->button);

					if (index == 0	||
						source->_hoops_CPCR._hoops_IRPIR[index] > 0) {
						_hoops_RIGC->_hoops_PISHA = event;
						return true;
					}
				}
			}	break;

			case _hoops_RHIIR: {
				_hoops_AHIIR *		_hoops_GPIIR = (_hoops_AHIIR *)event;
				_hoops_GGAGR	*source = _hoops_GPIIR->source;

				if (!BIT (source->_hoops_CGPIR, _hoops_SGPIR) &&
					source->_hoops_CPCR._hoops_SPIAP > 0) {
					_hoops_RIGC->_hoops_PISHA = event;
					return true;
				}
			}	break;

			case _hoops_GIIIR: {
				_hoops_RIGC->_hoops_PISHA = event;
				return true;
			}	/*_hoops_IHSA;*/

			case _hoops_AAIIR: {
				_hoops_PAIIR *	_hoops_HAIIR = (_hoops_PAIIR *)event;
				_hoops_GGAGR *				source = _hoops_HAIIR->source;

				if (!BIT (source->_hoops_CGPIR, _hoops_SGPIR) &&
					BIT(source->_hoops_CHIAP, _hoops_HAIIR->action)) {
					_hoops_RIGC->_hoops_PISHA = event;
					return true;
				}
			}	break;

			case _hoops_SAIIR: {
				Selection_Event *	_hoops_GPIIR = (Selection_Event *)event;
				_hoops_GGAGR *				source = _hoops_GPIIR->source;
				_hoops_GGAGR *				target = _hoops_GPIIR->target;

				/* ("_hoops_HCGP" _hoops_HRGR _hoops_IRAP _hoops_RAS _hoops_IRS _hoops_ICRPH) */
				if (target != null &&
					(BIT (target->_hoops_CGPIR, _hoops_SGPIR) ||
					 (source != null &&
					  (BIT (source->_hoops_CGPIR, _hoops_SGPIR) ||
					   source->_hoops_CPCR._hoops_HPIAP == 0)))) 
					{}
				else {
					_hoops_RPIIR				*si;

					si = _hoops_GPIIR->_hoops_APIIR;
					/* _hoops_RPP _hoops_PRRPA _hoops_IGCI _hoops_PGHPR, _hoops_HPPR _hoops_IH _hoops_IRS _hoops_IPPAR _hoops_IGCI */
					if (BIT (si->item->_hoops_RRHH, _hoops_HGAGR)) do {
						_hoops_RPIIR				*victim;

						victim = si;
						si = si->next;
						HI_Free_Selection_Item (victim);
					} while (si != null && BIT (si->item->_hoops_RRHH, _hoops_HGAGR));

					if ((_hoops_GPIIR->_hoops_APIIR = si) != null) {
						_hoops_RIGC->_hoops_PISHA = event;
						return true;
					}
				}
			}	break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized event type");
			}	break;
		}
		_hoops_HPRH (event);
	}

	return false;
}




GLOBAL_FUNCTION int HI_Take_A_Poll (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR const *			_hoops_GHRI,
	_hoops_GSPGR					now,
	bool					_hoops_CCRPH) {
#ifndef DISABLE_EVENTS
	int						_hoops_SCRPH = 0;

	HI_Check_Wakeups (_hoops_RIGC, now);

	if (HOOPS_WORLD->_hoops_PGGHP != nullroutine) {
		PUSHNAME(_hoops_RIGC);
		_hoops_AASAH(_hoops_RIGC, "Defined Event Checker (callback)");
			PUSHNAME(_hoops_RIGC);
			_hoops_AASAH(_hoops_RIGC, "Event Checker routine");
				(*HOOPS_WORLD->_hoops_PGGHP)();
			POPNAME(_hoops_RIGC);
		POPNAME(_hoops_RIGC);
	}

	if (_hoops_GHRI != null) {
		/*
		 * ("_hoops_GSRPH _hoops_SPHGR" _hoops_RPGP _hoops_HRGR _hoops_IRS _hoops_APSR _hoops_AGSIP _hoops_IH _hoops_IGH _hoops_SCH
		 *	*_hoops_CGH* _hoops_SHH _hoops_RSRPH!)
		 */

		do {
			
			if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA) && !BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR) &&
			   !BIT (_hoops_GHRI->owner->_hoops_PHSI, _hoops_GCHGP)) {

				int	_hoops_ASRPH = 0;

				if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_PIRPH)) {

					++_hoops_ASRPH;

					if (_hoops_GHRI->_hoops_SHIAP) {
						_hoops_CSPPR();
						_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_PSRPH, null);
						_hoops_IRRPR();
					}

					if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR) && 
						_hoops_GHRI->_hoops_IHIAP) {
						_hoops_CSPPR();
						_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_HSRPH, null);
						_hoops_IRRPR();
					}

				}
				else if (ALLBITS (_hoops_GHRI->_hoops_CGPIR, _hoops_RCSHA|_hoops_ISRPH)) {

					++_hoops_ASRPH;

					if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_CSRPH)) {
						_hoops_CSPPR();
						if(!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_SSRPH, null))
							((_hoops_GGAGR alter *)_hoops_GHRI)->_hoops_CGPIR &= ~_hoops_ISRPH;
						_hoops_IRRPR();
					}
				}

				if (!BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR))
					_hoops_SCRPH += _hoops_ASRPH;
			}

			if (_hoops_CCRPH)
				break;

		} while ((_hoops_GHRI = _hoops_GHRI->_hoops_CISHA) != null);

		return _hoops_SCRPH;
	}
	else
#endif
		return -1;	/* _hoops_HAS._hoops_IAS. _hoops_PSP _hoops_RPPRH _hoops_GGAPH, _hoops_HIS _hoops_SR _hoops_SARS'_hoops_RA _hoops_RPR _hoops_RH _hoops_RGAPH _hoops_SPSIR */
}


HC_INTERFACE void HC_CDECL HC_Flush_All_Events (void) 
{
	_hoops_PAPPR context("Flush_All_Events");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_Flush_All_Events ();\n");
	);


	_hoops_GSPGR	now = HI_What_Time ();

	HI_Check_Wakeups (context, now);

	if (HOOPS_WORLD->_hoops_PGGHP != nullroutine) {
		PUSHNAME(context);
		HI_Set_Name("Defined Event Checker (callback)");
			PUSHNAME(context);
			HI_Set_Name("Event Checker routine");
				(*HOOPS_WORLD->_hoops_PGGHP)();
			POPNAME(context);
		POPNAME(context);
	}


	_hoops_GGAGR *	_hoops_GHRI;
	if ((_hoops_GHRI = HOOPS_WORLD->_hoops_CISHA) != null) {
		do {
			
			if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA) &&
			   !BIT (_hoops_GHRI->owner->_hoops_PHSI, _hoops_GCHGP)) {

				/* _hoops_HPPR _hoops_IS _hoops_CHRI _hoops_GGSR _hoops_RH _hoops_HISAR-_hoops_PAPA _hoops_AGAPH/_hoops_PGRRR _hoops_PGAPH */
				_hoops_CSPPR();
				_hoops_HISAA (context, _hoops_GHRI, _hoops_HGAPH, null);
				_hoops_IRRPR();
			}

		} while ((_hoops_GHRI = _hoops_GHRI->_hoops_CISHA) != null);
	}

	while (HI_Dequeue_Event (context)) {}
#endif
}




GLOBAL_FUNCTION void HI_Check_Wakeups (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GSPGR					now) 
{
	_hoops_HRIIR *	_hoops_CHIIR;
	_hoops_HRIIR *	next;

	LOCK_MUTEX (HOOPS_WORLD->_hoops_IGAPH);

	if ((_hoops_CHIIR = HOOPS_WORLD->_hoops_CGAPH) != null) do {
		next = _hoops_CHIIR->next;
		if (_hoops_CHIIR->_hoops_RHSAP <= now || _hoops_CHIIR->_hoops_AHSAP == 0)
			HI_Queue_Wakeup_Event (_hoops_RIGC, _hoops_CHIIR);
	} while ((_hoops_CHIIR = next) != null);

	UNLOCK_MUTEX (HOOPS_WORLD->_hoops_IGAPH);
}



GLOBAL_FUNCTION int HI_Check_For_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR const *			_hoops_GHRI) 
{
#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
	return 0;
#else

	if (HOOPS_WORLD->_hoops_AARPH) 
		HI_Update_Events (_hoops_RIGC);

	if (HOOPS_WORLD->_hoops_CISHA == null) 
		return 0;
	else {
		_hoops_HISHA *		_hoops_SGAPH = null;
		_hoops_HISHA *		current;
		_hoops_HISHA *		event = null;
		_hoops_HISHA **	_hoops_ASRGR = &_hoops_SGAPH;
		int			count = 0;
		_hoops_GSPGR		now = HI_What_Time ();

		HI_Check_Wakeups (_hoops_RIGC, now);

		if (_hoops_RIGC->_hoops_PAARH == null) {

			bool _hoops_CCRPH = true;

			if (!_hoops_GHRI) {
				_hoops_GHRI = HOOPS_WORLD->_hoops_CISHA;
				_hoops_CCRPH = false;
			}

			HI_Take_A_Poll (_hoops_RIGC, _hoops_GHRI, now, _hoops_CCRPH);
		}

		current = _hoops_RIGC->_hoops_PISHA;
		_hoops_RIGC->_hoops_PISHA = null;

		/* _hoops_AGGHA _hoops_CPS _hoops_APIP _hoops_PSAP _hoops_RH _hoops_PGRRR _hoops_GSSHR... */

		while (HI_Dequeue_Event (_hoops_RIGC)) {
			++count;
			event = _hoops_RIGC->_hoops_PISHA;
			_hoops_RIGC->_hoops_PISHA = null;
			if ((event->next = *_hoops_ASRGR) != null)
				(*_hoops_ASRGR)->backlink = &event->next;
			*_hoops_ASRGR = event;
			event->backlink = _hoops_ASRGR;
			_hoops_ASRGR = &event->next;
		}

		/* ... _hoops_PSCR _hoops_PPSI _hoops_CAPR _hoops_ISSC _hoops_GPP. (_hoops_HGI _hoops_SPAHR _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_GRAPH!) */
		_hoops_RIGC->_hoops_PISHA = current;
		if ((_hoops_RIGC->_hoops_PAARH = _hoops_SGAPH) != null)
			_hoops_RIGC->_hoops_PAARH->backlink = &_hoops_RIGC->_hoops_PAARH;
		if ((_hoops_RIGC->_hoops_PCRPH = event) != null)
			_hoops_PRRH (event);

		return count;
	}
#endif
}


HC_INTERFACE int HC_CDECL HC_Check_For_Events (void) 
{
	_hoops_PAPPR context("Check_For_Events");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
	return 0;
#else

	CODE_GENERATION (
		HI_Dump_Code ("HC_Check_For_Events ();\n");
	);

	return HI_Check_For_Events (context, null);
#endif
}


GLOBAL_FUNCTION void HI_Requeue_Event (
	_hoops_AIGPR *	_hoops_RIGC) 
{
#ifndef DISABLE_EVENTS
	_hoops_HISHA *	event;
	if ((event = _hoops_RIGC->_hoops_PISHA) == null) {
		HE_WARNING (HEC_EVENT_HANDLER, HES_INVALID_INPUT, "There is no current event (was it already requeued?)");
		return;
	}

	if ((event->next = _hoops_RIGC->_hoops_PAARH) != null)
		_hoops_RIGC->_hoops_PAARH->backlink = &event->next;
	else {
		_hoops_RIGC->_hoops_PCRPH = event;
		_hoops_PRRH (event);
	}

	_hoops_RIGC->_hoops_PAARH = event;
	event->backlink = &_hoops_RIGC->_hoops_PAARH;
	_hoops_RIGC->_hoops_PISHA = null;
#endif
}



HC_INTERFACE void HC_CDECL HC_Requeue_Event (void) 
{
	_hoops_PAPPR context("Requeue_Event");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	CODE_GENERATION (
		HI_Dump_Code ("HC_Requeue_Event ();\n");
	);

	HI_Requeue_Event (context); 
#endif
}


GLOBAL_FUNCTION void HI_Await_Event (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					type,
	int						_hoops_SCPRA) 
{

#ifdef DISABLE_EVENTS
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(type);
	UNREFERENCED(_hoops_SCPRA);
#else
	
	/*
	 * _hoops_GHAP _hoops_RRAPH _hoops_HAGC _hoops_HHH _hoops_CSCS _hoops_ARAPH _hoops_ARI ...
	 * _hoops_PRAPH _hoops_GRS _hoops_ASRC _hoops_RPP _hoops_AAPA _hoops_PAPA _hoops_HRAPH _hoops_SGS _hoops_IRS _hoops_PCHC _hoops_PHI _hoops_IIGR
	 * "_hoops_PSPA" _hoops_HS _hoops_IRAPH (_hoops_CRAPH _hoops_APII _hoops_HPP _hoops_SRAPH _hoops_IIGR _hoops_SICAR _hoops_GGR _hoops_GHARR) _hoops_PAR
	 * _hoops_RPP _hoops_RH _hoops_HPARH (_hoops_IHPR) _hoops_RIGR _hoops_HRGR _hoops_PIGS - _hoops_SCH _hoops_PAH _hoops_PAHH _hoops_GACC _hoops_SHH
	 * _hoops_IRSGR _hoops_HPP _hoops_PCCP _hoops_PGRRR _hoops_RIP _hoops_SGS _hoops_GHAP _hoops_SIPGR'_hoops_RA _hoops_GAPR _hoops_GAAPH ....
	 */

	if (HOOPS_WORLD->_hoops_CISHA == null) 
		return;

	if (HOOPS_WORLD->_hoops_AARPH) 
		HI_Update_Events (_hoops_RIGC);

	/* _hoops_PS _hoops_GHCA _hoops_AIAH _hoops_HS _hoops_PCCP _hoops_PGRRR _hoops_CGRHP _hoops_GH _hoops_RPP _hoops_SR _hoops_SSAS _hoops_PCCP _hoops_PAAP _hoops_AIRI */
	/* _hoops_CRCI */
	if (_hoops_RIGC->_hoops_PISHA != null) {
		_hoops_HPRH (_hoops_RIGC->_hoops_PISHA);
		_hoops_RIGC->_hoops_PISHA = null;
	}

	while (_hoops_RIGC->_hoops_PISHA == null && 
			!HI_Dequeue_Event(_hoops_RIGC)) {
		
		if (HOOPS_WORLD->_hoops_RAAPH) 
			HI_Do_Update (_hoops_RIGC, -1.0, true);
	
		_hoops_GGAGR *	_hoops_GHRI = HOOPS_WORLD->_hoops_CISHA;
		
		int _hoops_SCRPH = 0;

		do {

			/* ("_hoops_GSRPH _hoops_SPHGR" _hoops_RPGP _hoops_HRGR _hoops_IRS _hoops_APSR _hoops_AGSIP _hoops_IH _hoops_IGH _hoops_SCH
			 *	*_hoops_CGH* _hoops_SHH _hoops_RSRPH!)
			 */

			if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA) &&
				ANYBIT (_hoops_GHRI->_hoops_CGPIR, _hoops_PIRPH|_hoops_ISRPH) &&
				!BIT (_hoops_GHRI->owner->_hoops_PHSI, _hoops_GCHGP)) {
			
				_hoops_GSPGR now = HI_What_Time ();

				_hoops_SCRPH += HI_Take_A_Poll (_hoops_RIGC, _hoops_GHRI, now, true);

				HI_Check_Wakeups (_hoops_RIGC, now);

				if (HI_Dequeue_Event (_hoops_RIGC))
					break;
			}

		} while ((_hoops_GHRI = _hoops_GHRI->_hoops_CISHA) != null);

		if (_hoops_SCRPH == 0 ||
			_hoops_RIGC->_hoops_PISHA != null)
			break;

		/* _hoops_AAAPH _hoops_IH _hoops_PAAPH */
		HI_Sleep (_hoops_HIAPR);
	}


	if (_hoops_RIGC->_hoops_PISHA == null)
		HI_Return_Chars (type, _hoops_SCPRA, "none", 4);
	else switch (_hoops_RIGC->_hoops_PISHA->type) {
		case _hoops_SAIIR: {
			HI_Return_Chars (type, _hoops_SCPRA, "selection", 9);
		}	break;

		case _hoops_AAIIR: {
			HI_Return_Chars (type, _hoops_SCPRA, "location", 8);
		}	break;

		case _hoops_PHIIR: {
			HI_Return_Chars (type, _hoops_SCPRA, "wakeup", 6);
		}	break;

		case _hoops_GIIIR: {
			HI_Return_Chars (type, _hoops_SCPRA, "special", 7);
		}	break;

		case _hoops_RHIIR: {
			HI_Return_Chars (type, _hoops_SCPRA, "string", 6);
		}	break;

		case _hoops_CRIIR: {
			HI_Return_Chars (type, _hoops_SCPRA, "button", 6);
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized event type");
		}	break;
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Await_Event (
	char *	type) 
{
	_hoops_PAPPR context("Await_Event");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Await_Event (string_buffer);\n");
	);

	HI_Await_Event (context, type, -1);
}



GLOBAL_FUNCTION void HI_Pause_Errors (
	int						category,
	int						specific,
	int						severity,
	int						msgc,
	char const * const *	msgv,
	int						_hoops_HRSAH,
	char const * const *	_hoops_PRSAH) {

#ifndef DISABLE_EVENTS
	UNREFERENCED (_hoops_PRSAH);

	if (_hoops_HRSAH == 2) {/* _hoops_HAAPH + _hoops_IHPP/_hoops_GCAR/_hoops_IAAPH == _hoops_IPIHR _hoops_SCH. _hoops_RCASA! */}
	else {
		_hoops_RGIIR *		save = HOOPS_WORLD->_hoops_RASAH;

		_hoops_AIGPR *_hoops_RIGC;
		_hoops_IIRIR (_hoops_RIGC);

		/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_CAAPH -- _hoops_CR _hoops_SR _hoops_CHR _hoops_AHCA _hoops_IS _hoops_AASA _hoops_RH _hoops_RIHH
		 * _hoops_HARPR _hoops_HII _hoops_GIAA _hoops_PCCP _hoops_RIHH _hoops_HARPR, _hoops_SR _hoops_PIHA _hoops_HASIR _hoops_RH _hoops_PGCR
		 * _hoops_IHH "_hoops_PCPH" _hoops_RPPCR _hoops_SAAPH _hoops_GH _hoops_HPP _hoops_GPAPH (_hoops_IH _hoops_CGRSR
		 * _hoops_RHIR _hoops_IPSP-_hoops_PAPR _hoops_RIHH _hoops_IASAH), _hoops_PPR _hoops_PHIH _hoops_CAPR _hoops_CGPR _hoops_SR _hoops_CHR
		 * _hoops_RHIR _hoops_CCA _hoops_RH _hoops_RIHRR _hoops_SPHS
		 */
		char const *	top = _hoops_RIGC->_hoops_RCSPP;
		POPNAME(_hoops_RIGC);
		char const *	next = _hoops_RIGC->_hoops_RCSPP;
		POPNAME(_hoops_RIGC);

		/* _hoops_PHIH _hoops_GIGR _hoops_HARPR _hoops_HIGR _hoops_PPR _hoops_RHRRH _hoops_SCH _hoops_GICS */
		HOOPS_WORLD->_hoops_RASAH = HOOPS_WORLD->_hoops_RPAPH;
		HI_Generate_Error (null, category, specific, severity, msgc, (char const **)msgv);
		HOOPS_WORLD->_hoops_RASAH = save;

		PUSHNAME(_hoops_RIGC);
		HI_Set_Name(next);
		PUSHNAME(_hoops_RIGC);
		HI_Set_Name(top);
	}
#endif
}



local void HI_Show_Location_Source (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					path,
	int						_hoops_APAPH,
	char *					display,
	int						_hoops_PPAPH,
	char *					action,
	int						_hoops_HPAPH,
	int *					status) 
{

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	_hoops_PAIIR *	_hoops_HAIIR;
	char				buf[MAX_ERRMSG];
	char *				_hoops_IPAPH;
	_hoops_GGAGR *				driver;

	if ((_hoops_HAIIR = (_hoops_PAIIR *)HI_Current_Event (_hoops_RIGC, _hoops_AAIIR)) == null) 
		return;

	if (BIT (_hoops_HAIIR->source->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_LOCATION, HES_DELETED_LOCATOR,
			"Can't 'Show' - the 'locater' has been deleted");
		return;
	}

	driver = _hoops_HAIIR->source;
	_hoops_IPAPH = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%p", (void *)driver->owner);
	HI_Return_Chars (path, _hoops_APAPH, buf, (int)(_hoops_IPAPH - buf));

	if (driver->_hoops_CPCR._hoops_IPIAP > 0 && driver->_hoops_CPCR.target != null) {
		if (BIT (driver->_hoops_CPCR.target->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_LOCATION, HES_DELETED_DISPLAY,
				"Can't 'Show' - the 'display' has been deleted");
			return;
		}

		_hoops_IPAPH = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%p",
			(void *)driver->_hoops_CPCR.target->owner);
		HI_Return_Chars (display, _hoops_PPAPH, buf, (int)(_hoops_IPAPH - buf));
	}
	else {
		HI_Return_Chars (display, _hoops_PPAPH, "", 0);
	}

	HI_Show_Locater_Action (_hoops_HAIIR->action, action, _hoops_HPAPH);
	*status = (int)_hoops_HAIIR->status;
#endif
}


local void HI_Show_Selection_Source (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					locater,
	int						_hoops_CPAPH,
	char *					picture,
	int						_hoops_SPAPH,
	char *					action,
	int						_hoops_HPAPH,
	int *					status)
{

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else

	Selection_Event *		_hoops_GPIIR;
	char					buf[_hoops_GHAPH];
	char *					_hoops_IPAPH;

	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (_hoops_RIGC, _hoops_SAIIR)) == null) 
		return;

	if (_hoops_GPIIR->source == null) 
		HI_Return_Chars (locater, _hoops_CPAPH, null, 0);
	else {
		if (BIT (_hoops_GPIIR->source->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_SELECTION, HES_DELETED_LOCATOR, "Can't 'Show' - the 'locater' has been deleted");
			return;
		}

		_hoops_IPAPH = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%p", (void *)_hoops_GPIIR->source->owner);
		HI_Return_Chars (locater, _hoops_CPAPH, buf, (int)(_hoops_IPAPH - buf));
	}

	if (_hoops_GPIIR->target == null)
		HI_Return_Chars (picture, _hoops_SPAPH, null, 0);
	else {
		if (BIT (_hoops_GPIIR->target->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_SELECTION, HES_DELETED_DISPLAY, "Can't 'Show' - the 'display' has been deleted");
			return;
		}

		_hoops_IPAPH = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%p", (void *)_hoops_GPIIR->target->owner);
		HI_Return_Chars (picture, _hoops_SPAPH, buf, (int)(_hoops_IPAPH - buf));
	}

	HI_Show_Locater_Action (_hoops_GPIIR->_hoops_APIIR->_hoops_GCSAP, action, _hoops_HPAPH);
	if (status)
		*status = (int)_hoops_GPIIR->status;
#endif
}


HC_INTERFACE void HC_CDECL HC_Pause (void) 
{
	_hoops_PAPPR context("Pause");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	CODE_GENERATION (
		HI_Dump_Code ("HC_Pause ();\n");
	);

	/* _hoops_SIPR _hoops_RH _hoops_SPSIR _hoops_SPIP _hoops_ARPP _hoops_ISCCP _hoops_RH _hoops_RIHH _hoops_SSHRH... */
	HI_Update_Actor_List (context);

	HOOPS_WORLD->_hoops_RPAPH = HOOPS_WORLD->_hoops_RASAH;
	HOOPS_WORLD->_hoops_RASAH = null;

	_hoops_RPPPR();
	HI_Define_Error_Handler (context, HI_Pause_Errors);
	_hoops_IRRPR();

	_hoops_CSPPR();
	HI_Enable_Location_Events (context, "?Locater", "?Picture", _hoops_HPSHA);
	HI_Enable_Button_Events (context, "?Keyboard", "anything");
	_hoops_IRRPR();

	_hoops_PCCAR {
		char	_hoops_RHAPH[20];
		char	path[100];	/* (_hoops_HAH _hoops_RISA _hoops_ASSP'_hoops_RA _hoops_RPSHR) */
		int		status;

		_hoops_RHAPH[0] = ' ';	/* _hoops_GGR _hoops_AGIR _hoops_RH _hoops_IAAPH _hoops_ISHS */
		HI_Await_Event (context, _hoops_RHAPH, _hoops_GGAPR(_hoops_RHAPH)-1);

		if (_hoops_RHAPH[0] == ' ') break;		/* _hoops_PSP _hoops_SPSIR? _hoops_AHAPH... */

		if (context->_hoops_PISHA == null)	{	/* _hoops_PSP _hoops_PGRRR -- _hoops_PCSHA _hoops_ISAHA? */
			HI_Exit_Program();
		}

		if (BIT(context->_hoops_PISHA->_hoops_RRHH, _hoops_IHSAP)) 
			{}
		else if (_hoops_RHAPH[0] == 'l') {
			HI_Show_Location_Source (context, path, _hoops_GGAPR(path)-1, path, _hoops_GGAPR(path)-1, _hoops_RHAPH, _hoops_GGAPR(_hoops_RHAPH)-1, &status);
			if (_hoops_RHAPH[0] == 'v') 
				break;
		}
		else if (_hoops_RHAPH[0] == 's' && _hoops_RHAPH[1] == 'e') {
			HI_Show_Selection_Source (context, path, _hoops_GGAPR(path)-1, path, _hoops_GGAPR(path)-1, _hoops_RHAPH, _hoops_GGAPR(_hoops_RHAPH)-1, &status);
			if (_hoops_RHAPH[0] == 'v')
				break;
		}
		else
			break;
	}

	if (context->_hoops_PISHA != null) {
		context->_hoops_PISHA->_hoops_RRHH |= _hoops_IHSAP;

		/* _hoops_HPGGR _hoops_GII _hoops_IHIA _hoops_PGRRR _hoops_GAR _hoops_AIPH _hoops_IH _hoops_HPIH _hoops_PHAPH */
		if (context->_hoops_PISHA->type == _hoops_AAIIR) {
			_hoops_PAIIR		*loc = (_hoops_PAIIR *)context->_hoops_PISHA;
			if (loc->_hoops_CAIIR != null)
				loc->_hoops_CAIIR->_hoops_RRHH |= _hoops_IHSAP;
		}
		else if (context->_hoops_PISHA->type == _hoops_CRIIR) {
			_hoops_SRIIR *_hoops_GRCPA = (_hoops_SRIIR *)context->_hoops_PISHA;
			if (_hoops_GRCPA->_hoops_RAIIR != null)
				_hoops_GRCPA->_hoops_RAIIR->_hoops_RRHH |= _hoops_IHSAP;
		}

		HI_Requeue_Event (context);
	}

	_hoops_CSPPR();
	HI_Disable_Button_Events (context, "?Keyboard", "anything");
	HI_Disable_Location_Events (context, "?Locater", "?Picture", _hoops_HPSHA);
	_hoops_IRRPR();

	_hoops_RPPPR();
	HI_UnDefine_Error_Handler (context, HI_Pause_Errors);
	_hoops_IRRPR();

	HOOPS_WORLD->_hoops_RASAH = HOOPS_WORLD->_hoops_RPAPH;
	HOOPS_WORLD->_hoops_RPAPH = null;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Time (
	float *	current_time) 
{
	_hoops_PAPPR context("Show_Time");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Time () */\n");
	);

	*current_time = (float)(HI_What_Time()) * (1.0f / (float)_hoops_HSPGR);
}


#ifndef DISABLE_EVENTS

local bool _hoops_HHAPH (
	char const				*_hoops_ACPGR,
	_hoops_APSHA		*_hoops_IHAPH) {
	char const				*_hoops_CHAPH = _hoops_ACPGR;

	*_hoops_IHAPH = false;
	while (*_hoops_ACPGR) switch (*_hoops_ACPGR++) {
		case 'O':
		case 'o': {
			*_hoops_IHAPH |= _hoops_SPSHA;
		}	break;

		case 'V':
		case 'v': {
			*_hoops_IHAPH |= _hoops_HPSHA;
		}	break;

		case '*': {
			*_hoops_IHAPH |= _hoops_IPSHA;
		}	break;

		case '^': {
			*_hoops_IHAPH |= _hoops_CPSHA;
		}	break;

		case ' ':
		case '\t': {
			/* _hoops_PSRCA */
		}	break;

		default: {
			HE_ERROR (HEC_LOCATION, HES_INVALID_INPUT,
					  Sprintf_S (null,
								 "Error in location action specification '%s'",
								 _hoops_CHAPH));
			return false;
		}	_hoops_HHHI;
	}

	return true;
}
#endif

GLOBAL_FUNCTION void HI_Enable_Location_Events (
	_hoops_AIGPR *	_hoops_RIGC,	
	char const *			_hoops_SHAPH,
	char const *			_hoops_GIAPH,
	_hoops_APSHA			_hoops_IHAPH) 
{
#ifdef DISABLE_EVENTS
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(_hoops_SHAPH);
	UNREFERENCED(_hoops_GIAPH);
	UNREFERENCED(action);
#else
	_hoops_RSIIR(_hoops_RIGC);

	_hoops_GGAGR *	locater;
	if ((locater = HI_Force_Find_Driver (_hoops_RIGC, _hoops_SHAPH)) != null) {

		while (*_hoops_GIAPH == ' ' || *_hoops_GIAPH == '\t') 
			++_hoops_GIAPH;

		_hoops_GGAGR *	target;
		if (*_hoops_GIAPH == '\0') 
			target = null;
		else if ((target = HI_Force_Find_Driver (_hoops_RIGC, _hoops_GIAPH)) != null) {

			if (locater->_hoops_RCSHR.target != null && locater->_hoops_RCSHR.target != target) {
				char	buf[MAX_ERRMSG];
				HE_ERROR2 (HEC_LOCATION, HES_TARGET_LOCATOR_CONNECTED,
						Sprintf_PP (null, "Locater '%p' is already connected to target '%p' -",
					locater->owner, locater->_hoops_RCSHR.target->owner),
					Sprintf_P (buf, "Can't also connect it to target '%p'", target->owner));
				locater = null;
				target = null;
			}
		}

		if (target != null) {
			if (locater->_hoops_RCSHR.target == null) {
				locater->_hoops_RCSHR.target = target;
				if (target != locater)
					_hoops_PRRH (target);
				target->_hoops_CGPIR |= _hoops_PARPH;
				HOOPS_WORLD->_hoops_AARPH = true;
			}
			++locater->_hoops_RCSHR._hoops_IPIAP;
		}

		if (locater != null) {
			if (BIT (_hoops_IHAPH, _hoops_CPSHA))				
				++locater->_hoops_RCSHR._hoops_GPIAP;
			if (BIT (_hoops_IHAPH, _hoops_HPSHA))				
				++locater->_hoops_RCSHR._hoops_RPIAP;
			if (BIT (_hoops_IHAPH, _hoops_SPSHA))			
				++locater->_hoops_RCSHR._hoops_APIAP;
			if (BIT (_hoops_IHAPH, _hoops_IPSHA))		
				++locater->_hoops_RCSHR._hoops_PPIAP;

			locater->_hoops_CHIAP |= _hoops_IHAPH;
			locater->_hoops_CGPIR |= _hoops_PARPH;
			HOOPS_WORLD->_hoops_AARPH = true;
		}
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Enable_Location_Events (
	char const *		_hoops_SHAPH,
	char const *		_hoops_GIAPH,
	char const *		action) 
{
	_hoops_PAPPR context("Enable_Location_Events");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Enable_Location_Events (%S, %S, ", _hoops_SHAPH, _hoops_GIAPH));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", action));
	);

	_hoops_APSHA		_hoops_IHAPH;
	if (!_hoops_HHAPH (action, &_hoops_IHAPH))
		return;

	_hoops_CSPPR();
	HI_Enable_Location_Events (context,	_hoops_SHAPH, _hoops_GIAPH, _hoops_IHAPH); 
	_hoops_IRRPR();
#endif
}


#ifndef DISABLE_EVENTS
local void _hoops_RIAPH (
	_hoops_GGAGR *			locater,
	char const *	type) {

	_hoops_PHPGR (HEC_LOCATION, HES_LOCATION_EVENT_NOT_ENABLED,
			Sprintf_SP (null, "Cannot disable '%s' events on '%p' -", type, locater->owner), "They are already fully disabled");
}
#endif


GLOBAL_FUNCTION void HI_Disable_Location_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_SHAPH,
	char const *			_hoops_GIAPH,
	_hoops_APSHA			_hoops_IHAPH) 
{
#ifdef DISABLE_EVENTS
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(_hoops_SHAPH);
	UNREFERENCED(_hoops_GIAPH);
	UNREFERENCED(action);
#else

	_hoops_RSIIR(_hoops_RIGC);

	_hoops_GGAGR *	locater;
	if ((locater = HI_Force_Find_Driver (_hoops_RIGC, _hoops_SHAPH)) != null) {

		_hoops_GGAGR *	target;

		while (*_hoops_GIAPH == ' ' || *_hoops_GIAPH == '\t') 
			++_hoops_GIAPH;

		if (*_hoops_GIAPH == '\0') 
			target = null;
		else {

			if ((target = HI_Force_Find_Driver (_hoops_RIGC, _hoops_GIAPH)) != null) {

				if (locater->_hoops_RCSHR.target != target) {
					_hoops_PHPGR (HEC_LOCATION, HES_TARGET_LOCATOR_NOT_CONNECTED,
						Sprintf_PP (null, "Locater '%p' is not connected to target '%p' -",
						locater->owner, locater->_hoops_RCSHR.target->owner), "Can't disable");
				}
				else if (--locater->_hoops_RCSHR._hoops_IPIAP == 0 &&
					locater->_hoops_RCSHR._hoops_HPIAP == 0) {
						target->_hoops_CGPIR |= _hoops_PARPH;
						HOOPS_WORLD->_hoops_AARPH = true;
						if (target != locater) 
							_hoops_HPRH (target);
						locater->_hoops_RCSHR.target = null;
				}
			}
			else 
				locater = null;
		}

		if (locater != null) {

			if (BIT (_hoops_IHAPH, _hoops_CPSHA))
				if (locater->_hoops_RCSHR._hoops_GPIAP == 0) _hoops_RIAPH (locater, "^");
				else if (--locater->_hoops_RCSHR._hoops_GPIAP == 0)
					locater->_hoops_CHIAP &= ~_hoops_CPSHA;

			if (BIT (_hoops_IHAPH, _hoops_HPSHA))
				if (locater->_hoops_RCSHR._hoops_RPIAP == 0) _hoops_RIAPH (locater, "v");
				else if (--locater->_hoops_RCSHR._hoops_RPIAP <= 0)
					locater->_hoops_CHIAP &= ~_hoops_HPSHA;

			if (BIT (_hoops_IHAPH, _hoops_SPSHA))
				if (locater->_hoops_RCSHR._hoops_APIAP == 0) _hoops_RIAPH (locater, "O");
				else if (--locater->_hoops_RCSHR._hoops_APIAP <= 0)
					locater->_hoops_CHIAP &= ~_hoops_SPSHA;

			if (BIT (_hoops_IHAPH, _hoops_IPSHA))
				if (locater->_hoops_RCSHR._hoops_PPIAP == 0) _hoops_RIAPH (locater, "*");
				else if (--locater->_hoops_RCSHR._hoops_PPIAP <= 0)
					locater->_hoops_CHIAP &= ~_hoops_IPSHA;

			locater->_hoops_CGPIR |= _hoops_PARPH;
			HOOPS_WORLD->_hoops_AARPH = true;
		}
	}
#endif
}

HC_INTERFACE void HC_CDECL HC_Disable_Location_Events (
	char const *		_hoops_SHAPH,
	char const *		_hoops_GIAPH,
	char const *		action) 
{
	_hoops_PAPPR context("Disable_Location_Events");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Disable_Location_Events (%S, %S, ", _hoops_SHAPH, _hoops_GIAPH));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", action));
	);

	_hoops_APSHA	_hoops_IHAPH;
	if (!_hoops_HHAPH (action, &_hoops_IHAPH)) 
		return;

	_hoops_CSPPR();
	HI_Disable_Location_Events (context, _hoops_SHAPH, _hoops_GIAPH, _hoops_IHAPH);
	_hoops_IRRPR();
#endif
}



GLOBAL_FUNCTION void HI_Queue_Location_Event (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR *					source,
	float					x,
	float					y,
	int						status,
	_hoops_APSHA			action) 
{
#ifndef DISABLE_EVENTS
	_hoops_GGAGR *					target = source->_hoops_CPCR.target;
	_hoops_APSHA			_hoops_AIAPH = source->_hoops_GIIAP.action;
	_hoops_PAIIR *		_hoops_PIAPH = null;

	if (source->_hoops_GIIAP.action == action &&
		source->_hoops_GIIAP.status == status &&
		source->_hoops_GIIAP.x == x &&
		source->_hoops_GIIAP.y == y) 
		return; /* _hoops_IPIHR _hoops_SCH */

	source->_hoops_GIIAP.action = action;
	source->_hoops_GIIAP.status = status;
	source->_hoops_GIIAP.x = x;
	source->_hoops_GIIAP.y = y;

	if (action == _hoops_IPSHA && 
		(_hoops_AIAPH == _hoops_HIAPH ||
		BIT (_hoops_CPSHA|_hoops_SPSHA, _hoops_AIAPH)))
		action = _hoops_HPSHA;
	else if (action == _hoops_SPSHA && 
			(_hoops_AIAPH == _hoops_HIAPH ||
			BIT (_hoops_HPSHA|_hoops_IPSHA, _hoops_AIAPH)))
			action = _hoops_CPSHA;

	if (target != null && BIT(target->_hoops_CGPIR, _hoops_PPRPH) &&
		!(target == source && BIT(target->_hoops_CGPIR, _hoops_RPRPH))) {

		_hoops_PAIIR				_hoops_IIAPH;
		_hoops_IIAPH.x = (float)x;
		_hoops_IIAPH.y = (float)y;
		_hoops_IIAPH.status = status;
		_hoops_IIAPH.action = action;
		_hoops_CSPPR();
		_hoops_HISAA (_hoops_RIGC, target, _hoops_CIAPH, &_hoops_IIAPH);
		_hoops_IRRPR();
	}

	if (action == _hoops_HPSHA)
		action |= _hoops_IPSHA;
	else if (action == _hoops_CPSHA)
		action |= _hoops_SPSHA;

	if (BIT (source->_hoops_CHIAP, action)) {
		_hoops_PAIIR				*_hoops_HAIIR;

		ZALLOC (_hoops_HAIIR, _hoops_PAIIR);
		_hoops_HAIIR->owner = HOOPS_WORLD;
		_hoops_HAIIR->_hoops_HIHI = 1;
		_hoops_HAIIR->type = _hoops_AAIIR;
		_hoops_HAIIR->_hoops_PHSHA = HI_What_Time();

		if (_hoops_RIGC->_hoops_PCRPH == null) {
			_hoops_RIGC->_hoops_PAARH = (_hoops_HISHA *)_hoops_HAIIR;
			_hoops_HAIIR->backlink = &_hoops_RIGC->_hoops_PAARH;
		}
		else {
			_hoops_RIGC->_hoops_PCRPH->next = (_hoops_HISHA *)_hoops_HAIIR;
			_hoops_HAIIR->backlink = &_hoops_RIGC->_hoops_PCRPH->next;
			_hoops_HPRH (_hoops_RIGC->_hoops_PCRPH);
		}
		_hoops_RIGC->_hoops_PCRPH = (_hoops_HISHA *)_hoops_HAIIR;
		_hoops_PRRH (_hoops_HAIIR);

		_hoops_HAIIR->x = (float)x;
		_hoops_HAIIR->y = (float)y;
		_hoops_HAIIR->status = status;
		_hoops_HAIIR->source = source;
		_hoops_PRRH (source);
		_hoops_HAIIR->action = action;

		_hoops_PIAPH = _hoops_HAIIR;
		_hoops_HAIIR->_hoops_CAIIR = null;
	}

	if (target != null && source->_hoops_CPCR._hoops_HPIAP > 0) {

		Selection_Event *	_hoops_GPIIR;

		ZALLOC (_hoops_GPIIR, Selection_Event);
		_hoops_GPIIR->owner = HOOPS_WORLD;
		_hoops_GPIIR->_hoops_HIHI = 1;
		_hoops_GPIIR->type = _hoops_SAIIR;
		_hoops_GPIIR->_hoops_PHSHA = HI_What_Time();
		_hoops_GPIIR->flags = false;
		_hoops_GPIIR->_hoops_IHSHA.left = (float)x;
		_hoops_GPIIR->_hoops_IHSHA.right = (float)x;
		_hoops_GPIIR->_hoops_IHSHA.bottom = (float)y;
		_hoops_GPIIR->_hoops_IHSHA.top = (float)y;
		_hoops_GPIIR->_hoops_IHSHA.hither = -MAX_FLOAT;
		_hoops_GPIIR->_hoops_IHSHA.yon = MAX_FLOAT;
		_hoops_GPIIR->_hoops_CHSHA = action;
		_hoops_GPIIR->status = status;
		_hoops_GPIIR->source = source;
		_hoops_PRRH (source);
		_hoops_GPIIR->target = target;
		_hoops_PRRH (target);

		_hoops_CSPPR();
		bool _hoops_GISHA = _hoops_HISAA (_hoops_RIGC, target, _hoops_RISHA, _hoops_GPIIR);
		_hoops_IRRPR();

		if (!_hoops_GISHA ||
			_hoops_GPIIR->_hoops_APIIR == null) _hoops_HPRH (_hoops_GPIIR);
		else {
			if (_hoops_RIGC->_hoops_PCRPH == null) {
				_hoops_GPIIR->backlink = &_hoops_RIGC->_hoops_PAARH;
				_hoops_RIGC->_hoops_PAARH = (_hoops_HISHA *)_hoops_GPIIR;
			}
			else {
				_hoops_RIGC->_hoops_PCRPH->next = (_hoops_HISHA *)_hoops_GPIIR;
				_hoops_GPIIR->backlink = &_hoops_RIGC->_hoops_PCRPH->next;
				_hoops_HPRH (_hoops_RIGC->_hoops_PCRPH);
			}

			_hoops_RIGC->_hoops_PCRPH = (_hoops_HISHA *)_hoops_GPIIR;
			_hoops_PRRH (_hoops_GPIIR);

			/* _hoops_RPP _hoops_SR _hoops_SAHR _hoops_IIAC _hoops_IRS _hoops_SIAPH _hoops_HAH, _hoops_GCAPH _hoops_RGR _hoops_CCA _hoops_SCH */
			if (_hoops_PIAPH != null) {
				_hoops_PIAPH->_hoops_CAIIR = _hoops_GPIIR;
				_hoops_PRRH (_hoops_GPIIR);
			}
		}
	}
#endif
}


/* _hoops_RH _hoops_HSPR _hoops_CGH _hoops_SHH _hoops_GGR _hoops_IRS _hoops_GIAH _hoops_RGHR, _hoops_HIH _hoops_ISCP _hoops_RCAPH _hoops_ACAPH
 * _hoops_CHR _hoops_GHHS _hoops_GGR _hoops_RH _hoops_PPRRR.
 */

HC_INTERFACE void HC_CDECL HC_Queue_Location_Event (
	char const *			_hoops_PCAPH,
	char const *			_hoops_SASHA,
	double					x,
	double					y,
	char const *			_hoops_RPSHA,
	int						status) 
{
	_hoops_PAPPR context("Queue_Location_Event");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Queue_Location_Event (%S, %S, ", _hoops_PCAPH, _hoops_SASHA));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_S (null, "%S, ", _hoops_RPSHA));
		HI_Dump_Code (Sprintf_D (null, "%d);\n", status));
	);

	_hoops_GGAGR *					source;
	_hoops_APSHA			action;
	_hoops_GGAGR *					target;
	_hoops_PAIIR *		_hoops_HAIIR;

	// _hoops_ASIGA _hoops_CSPIP _hoops_HCAPH

	if ((source = HI_Force_Find_Driver (context, _hoops_PCAPH)) == null) 
		return;
	if ((target = HI_Force_Find_Driver (context, _hoops_SASHA)) == null) 
		return;
	if ((action = HI_Decipher_Action (_hoops_RPSHA)) == 0) 
		return;

	if (x < -1.0001f || x > 1.0001f || y < -1.0001f || y > 1.0001f) {
		HE_ERROR (HEC_LOCATION, HES_OUT_OF_RANGE, "Location x or y is not in the range of -1 to +1");
		return;
	}

	if (target != source->_hoops_CPCR.target) {
		HE_WARNING (HEC_LOCATION, HES_INVALID_TARGET,
				Sprintf_PP (null, "'%p' is not the location target for '%p'", target->owner, source->owner));
		/* _hoops_PSP _hoops_ASRC ? */
	}

	if (HOOPS_WORLD->_hoops_AARPH) 
		HI_Update_Events (context);

	if (!BIT (source->_hoops_CHIAP, action)) {
		HE_WARNING (HEC_LOCATION, HES_LOCATION_EVENT_NOT_ENABLED,
				Sprintf_SP (null, "'%s' location events are not currently enabled on '%p'", _hoops_RPSHA, source->owner));
		return;
	}

	ZALLOC (_hoops_HAIIR, _hoops_PAIIR);
	_hoops_HAIIR->owner = HOOPS_WORLD;
	_hoops_HAIIR->_hoops_HIHI = 1;
	_hoops_HAIIR->type = _hoops_AAIIR;
	_hoops_HAIIR->_hoops_PHSHA = HI_What_Time();

	if (context->_hoops_PCRPH == null) {
		context->_hoops_PAARH = (_hoops_HISHA *)_hoops_HAIIR;
		_hoops_HAIIR->backlink = &context->_hoops_PAARH;
	}
	else {
		context->_hoops_PCRPH->next = (_hoops_HISHA *)_hoops_HAIIR;
		_hoops_HAIIR->backlink = &context->_hoops_PCRPH->next;
		_hoops_HPRH (context->_hoops_PCRPH);
	}
	context->_hoops_PCRPH = (_hoops_HISHA *)_hoops_HAIIR;
	_hoops_PRRH (_hoops_HAIIR);
	_hoops_HAIIR->_hoops_CAIIR = null;

	_hoops_HAIIR->x = (float)x;
	_hoops_HAIIR->y = (float)y;
	_hoops_HAIIR->status = status;
	_hoops_HAIIR->source = source;
	_hoops_PRRH (source);
	_hoops_HAIIR->action = action;
#endif
}


#ifdef DISABLE_EVENTS
#	ifdef DISABLE_COMPUTE
#		define	_hoops_ICAPH
#	endif
#endif

GLOBAL_FUNCTION _hoops_APSHA HI_Decipher_Action (
	char const				*_hoops_CCAPH) {
#ifndef _hoops_ICAPH
	char const				*_hoops_RPSHA = _hoops_CCAPH;
	_hoops_APSHA		action;

	action = 0;
	while (*_hoops_RPSHA == ' ') ++_hoops_RPSHA;
	if (*_hoops_RPSHA != '\0') {
		switch (*_hoops_RPSHA++) {
			case '^':			action = _hoops_CPSHA;			break;
			case 'V': case 'v': action = _hoops_HPSHA;		break;
			case '*':			action = _hoops_IPSHA; break;
			case 'O': case 'o': action = _hoops_SPSHA;	break;
		}
		while (*_hoops_RPSHA == ' ') ++_hoops_RPSHA;
	}

	if (action == 0 || *_hoops_RPSHA != '\0') {
		HE_ERROR2 (HEC_LOCATION, HES_INVALID_ACTION_NAME,
				Sprintf_S (null, "'%s' is not a valid action name -",
								_hoops_CCAPH),
				   "Must be one of ^, v, *, or O");
		return 0;
	}

	return action;
#else
	return 0;
#endif
}

local void HI_Show_Location (
	_hoops_AIGPR *	_hoops_RIGC,
	float *					x,
	float *					y) 
{
	_hoops_PAIIR *	_hoops_HAIIR;

	if ((_hoops_HAIIR = (_hoops_PAIIR *)HI_Current_Event (_hoops_RIGC, _hoops_AAIIR)) == null) {
		*x = 0.0f;
		*y = 0.0f;
		return;
	}

	*x = _hoops_HAIIR->x;
	*y = _hoops_HAIIR->y;
}

HC_INTERFACE void HC_CDECL HC_Get_Location (
	float *		x,
	float *		y) 
{
	_hoops_PAPPR context("Get_Location");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_Get_Location (&ff, &ff);\n");
	);

	_hoops_CSPPR();
	HI_Enable_Location_Events (context, "?Locater", "?Picture", _hoops_HPSHA|_hoops_IPSHA|_hoops_CPSHA);
	_hoops_IRRPR();

	char	_hoops_RHAPH[20];
	do {
		_hoops_RHAPH[0] = 'l';	/* _hoops_GGR _hoops_AGIR _hoops_RH _hoops_IAAPH _hoops_ISHS */
		HI_Await_Event (context, _hoops_RHAPH, _hoops_GGAPR(_hoops_RHAPH));

		if (_hoops_RHAPH[0] == 'n')	/* _hoops_PIRC */
			HI_Exit_Program();

	} _hoops_RGGA (_hoops_RHAPH[0] == 'l');

	_hoops_CSPPR();
	HI_Disable_Location_Events (context, "?Locater", "?Picture", _hoops_HPSHA|_hoops_IPSHA|_hoops_CPSHA);
	_hoops_IRRPR();

	HI_Show_Location (context, x, y);

#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Location (
	float *			x,
	float *			y) 
{	
	_hoops_PAPPR context("Show_Location");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Location () */\n");
	);

	HI_Show_Location (context, x, y);
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Location_Source (
	char *			path,
	char *			display,
	char *			action,
	int *			status) 
{
	_hoops_PAPPR context("Show_Location_Source");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Location_Source () */\n");
	);

	HI_Show_Location_Source (context, path, -1, display, -1, action, -1, status);
}






GLOBAL_FUNCTION void HI_Show_Locater_Action (
	_hoops_APSHA				_hoops_IHAPH,
	char					*type,
	int						_hoops_SCPRA) {

	if (_hoops_IHAPH == _hoops_CPSHA)
		HI_Return_Chars (type, _hoops_SCPRA, "^", 1);
	else if (_hoops_IHAPH == _hoops_HPSHA)
		HI_Return_Chars (type, _hoops_SCPRA, "v", 1);
	else if (_hoops_IHAPH == _hoops_SPSHA)
		HI_Return_Chars (type, _hoops_SCPRA, "O", 1);
	else if (_hoops_IHAPH == _hoops_IPSHA)
		HI_Return_Chars (type, _hoops_SCPRA, "*", 1);
}







#ifndef DISABLE_EVENTS

#define _hoops_SCAPH (-9999)


local int number (char *	p) 
{
  int				first, _hoops_IAGRA;

  switch (*p++) {
	case '0':		first = 0; break;
	case '1':		first = 1; break;
	case '2':		first = 2; break;
	case '3':		first = 3; break;
	case '4':		first = 4; break;
	case '5':		first = 5; break;
	case '6':		first = 6; break;
	case '7':		first = 7; break;
	case '8':		first = 8; break;
	case '9':		first = 9; break;
	default:		return _hoops_SCAPH;
 }

 if (*p == '\0') return first;

					  switch (*p) {
		case '0':		_hoops_IAGRA = 0; break;
		case '1':		_hoops_IAGRA = 1; break;
		case '2':		_hoops_IAGRA = 2; break;
		case '3':		_hoops_IAGRA = 3; break;
		case '4':		_hoops_IAGRA = 4; break;
		case '5':		_hoops_IAGRA = 5; break;
		case '6':		_hoops_IAGRA = 6; break;
		case '7':		_hoops_IAGRA = 7; break;
		case '8':		_hoops_IAGRA = 8; break;
		case '9':		_hoops_IAGRA = 9; break;
		default:		return _hoops_SCAPH;
					  }

	 return first*10 + _hoops_IAGRA;
}


local int _hoops_GSAPH (
	char const		*_hoops_SSACR,
	char const		*_hoops_HRHRA,
	char const		*_hoops_IRHRA,
	int				*_hoops_AHSAP,
	int				total);


local int _hoops_RSAPH (
	char const *	_hoops_CSHPP,
	int *			_hoops_AHSAP,
	int				_hoops_SSPCR) 
{
	char const *	p = _hoops_CSHPP;
	bool			_hoops_ASAPH = false;
	int				total = 0;

	_hoops_RGGA (*p == '\0') {
	 if (*p == ' ') 
		 ++p;
	 else if (*p == ',') {
		 if (!_hoops_ASAPH)
			 return _hoops_GSAPH ("too many commas", p, _hoops_CSHPP, _hoops_AHSAP, total);

		 _hoops_ASAPH = false;
		 ++p;
	 }
	 else {
		 char	buf[20];
		 char *	_hoops_ASAPR = buf,
			 count = 0;
		 int		start = _hoops_SCAPH,
			 end = _hoops_SCAPH,
			 _hoops_PSAPH;

		 if (_hoops_ASAPH)
			 return _hoops_GSAPH ("missing comma", p, _hoops_CSHPP, _hoops_AHSAP, total);

		 do *_hoops_ASAPR++ = _hoops_SHPCR (*p), ++p, ++count;
		 _hoops_RGGA (*p == '\0' || *p == ',' || count == _hoops_GGAPR(buf)-1);
		 *_hoops_ASAPR = '\0';

		 if (count == 1) {
			 /* _hoops_HSAPH _hoops_RGAR! */
			 start = (Button)(0xFF & p[-1]);
			 if ((start < _hoops_ISAPH || start > _hoops_CSAPH) &&
				 (start < _hoops_SSAPH || start > _hoops_GGPPH))
				 start = _hoops_SCAPH;
		 }
		 else if (count == 5 && _hoops_AGGR ("comma", buf)) start = ',';
		 else if (count == 5 && _hoops_AGGR ("space", buf)) start = ' ';
		 else if (count == 6 && _hoops_AGGR ("rubout", buf)) start = RUBOUT_KEY;
		 else if (count == 10 && _hoops_AGGR ("left arrow", buf))
			 start = _hoops_HCRPH(LEFT_ARROW_KEY);
		 else if (count == 11 && _hoops_AGGR ("right arrow", buf))
			 start = _hoops_HCRPH(RIGHT_ARROW_KEY);
		 else if (count == 8 && _hoops_AGGR ("up arrow", buf))
			 start = _hoops_HCRPH(UP_ARROW_KEY);
		 else if (count == 10 && _hoops_AGGR ("down arrow", buf))
			 start = _hoops_HCRPH(DOWN_ARROW_KEY);
		 else if (count == 5 && _hoops_AGGR ("arrow", buf)) {
			 start = _hoops_HCRPH(_hoops_RGPPH);
			 end = _hoops_HCRPH(_hoops_AGPPH);
		 }
		 else if (count == 8 && _hoops_AGGR ("function", buf)) {
			 start = _hoops_HCRPH(FIRST_FUNCTION_KEY);
			 end = _hoops_HCRPH(_hoops_PGPPH);
		 }
		 else if (count == 7 && _hoops_AGGR ("control", buf)) {
			 start = _hoops_HCRPH(_hoops_HGPPH);
			 end = _hoops_HCRPH(_hoops_IGPPH);
		 }
		 else if (count == 6 && _hoops_AGGR ("keypad", buf)) {
			 start = _hoops_HCRPH(FIRST_KEYPAD_KEY);
			 end = _hoops_HCRPH(_hoops_CGPPH);
		 }
		 else if (count == 8 && _hoops_AGGR ("printing", buf)) {
			 start = _hoops_HCRPH(_hoops_ISAPH);
			 end = _hoops_HCRPH(_hoops_CSAPH);
		 }
		 else if (count == 4 && _hoops_AGGR ("misc", buf)) {
			 start = _hoops_HCRPH(_hoops_SGPPH);
			 end = _hoops_HCRPH(_hoops_GRPPH);
		 }
		 else if (count == 6 && _hoops_AGGR ("number", buf)) {
			 start = (Button)'0';
			 end = (Button)'9';
		 }
		 else if (count == 6 && _hoops_AGGR ("letter", buf)) {
			 start = (Button)'A';
			 end = (Button)'Z';
		 }
		 else if (count == 8 && _hoops_AGGR ("anything", buf)) {
			 start = _hoops_RRPPH;
			 end = _hoops_CRPIR;
		 }
		 else if (count == 10 && _hoops_AGGR ("everything", buf)) {
			 start = _hoops_RRPPH;
			 end = _hoops_CRPIR;
		 }
		 else if (count == 6 && _hoops_AGGR ("escape", buf)) {
			 start = 27;		/* _hoops_PGPCR */
		 }
		 else if (count == 9 && _hoops_GPPSA ("control ", 8, buf)) {
			 /* _hoops_HSAPH _hoops_RGAR!! */
			 int				_hoops_ARPPH;

			 _hoops_ARPPH = _hoops_IRGCR(buf[8]);

			 if ('a' <= _hoops_ARPPH && _hoops_ARPPH <= 'z')
				 start = _hoops_ARPPH & 0x1F;		/* _hoops_PISH _hoops_PSAP _hoops_RGSHA */
			 else switch (_hoops_ARPPH) {
					case '@':	case '[':	case '\\':
					case ']':	case '^':	case '_':
					case '|':
					start = _hoops_ARPPH & 0x1F;	break;

					default:
					start = _hoops_SCAPH;		break;
						 }
					 }
					 else if ((count == 2 || count == 3) && buf[0] == 'f') {
						 start = _hoops_HCRPH(FIRST_FUNCTION_KEY) + number (&buf[1]);
						 if (start < _hoops_HCRPH(FIRST_FUNCTION_KEY) ||
							 start > _hoops_HCRPH(_hoops_PGPPH))
							 start = _hoops_SCAPH;
					 }
					 else if ((count == 3 || count == 4) &&
						 buf[0] == 'k' && buf[1] == 'p') {
							 start = _hoops_HCRPH(FIRST_KEYPAD_KEY) + number (&buf[2]);
							 if (start < _hoops_HCRPH(FIRST_KEYPAD_KEY) ||
								 start > _hoops_HCRPH(_hoops_CGPPH))
								 start = _hoops_SCAPH;
					 }

					 if (start == _hoops_SCAPH)
						 return _hoops_GSAPH ("Unexpected character or button name found",
						 p-count, _hoops_CSHPP, _hoops_AHSAP, total);

					 if (end == _hoops_SCAPH) 
						 end = start;

_hoops_PRPPH:;

	 _hoops_PSAPH = start;
	 do if ((_hoops_AHSAP[start] += _hoops_SSPCR) < 0) {
		 do _hoops_AHSAP[start] -= _hoops_SSPCR;
		 _hoops_RGGA (--start < _hoops_PSAPH);

		 return _hoops_GSAPH ("Button is fully disabled or was never enabled",
			 p - count, _hoops_CSHPP, _hoops_AHSAP, total);
	 }
	 _hoops_RGGA (++start > end);

	 total += (end - _hoops_PSAPH + 1) * _hoops_SSPCR;

	 /* _hoops_IPCIP _hoops_IS _hoops_AA _hoops_IRS _hoops_CIAGR _hoops_RRI */
	 if (_hoops_PSAPH == _hoops_ISAPH && end == _hoops_CSAPH) {
		 start = _hoops_SSAPH;
		 end = _hoops_GGPPH;
		 goto _hoops_PRPPH;
	 }
	 else if (_hoops_PSAPH == (Button)'A' && end == (Button)'Z') {
		 start = (Button)'a';
		 end = (Button)'z';
		 goto _hoops_PRPPH;
	 }

		 _hoops_ASAPH = true;
	 }
	}

	if (!_hoops_ASAPH) {
		if (total == 0) {
			HE_ERROR (HEC_BUTTON, HES_INVALID_INPUT, "No buttons were specified");
			return 0;
		}
		else
			return _hoops_GSAPH ("trailing comma found", p, _hoops_CSHPP, _hoops_AHSAP, total);
	}

	return total;
}


local int _hoops_GSAPH (
	char const *	_hoops_SSACR,
	char const *	_hoops_HRHRA,
	char const *	_hoops_IRHRA,
	int *			_hoops_AHSAP,
	int				total) {

	HE_ERROR2 (HEC_BUTTON, HES_INVALID_INPUT,
		Sprintf_S (null, "Error in button specification '%s' -", _hoops_IRHRA), _hoops_SSACR);

	if (total != 0) {	/* _hoops_PAISR _hoops_RH _hoops_SAIP */
		_hoops_HCRPR			in;
		_hoops_HCRPR			_hoops_PAGR;

		while (_hoops_HRHRA[-1] == ' ') 
			--_hoops_HRHRA;
		if (_hoops_HRHRA[-1] == ',') 
			--_hoops_HRHRA;

		in.text = (char *)_hoops_IRHRA;		/* _hoops_HIIC _hoops_IS _hoops_SRCH _hoops_IHH _hoops_HRPPH */
		in.length = _hoops_HRHRA - _hoops_IRHRA + 1;

		HI_Copy_Name (&in, &_hoops_PAGR);		/* _hoops_IPS _hoops_HIS _hoops_SR _hoops_PAH _hoops_GHHR _hoops_SCH */

		_hoops_PAGR.text[_hoops_PAGR.length - 1] = '\0';
		(void)_hoops_RSAPH (_hoops_PAGR.text, _hoops_AHSAP, _hoops_PAGR.length-1);	/* _hoops_PAISR _hoops_RH _hoops_AGRP */
		_hoops_RGAIR (_hoops_PAGR);
	}
	return 0;
}
#endif

GLOBAL_FUNCTION void HI_Enable_Button_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_IRPPH,
	char const *			_hoops_CRPPH) 
{
#ifdef DISABLE_EVENTS
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(_hoops_IRPPH);
	UNREFERENCED(_hoops_CRPPH);
#else

	_hoops_RSIIR(_hoops_RIGC);

	_hoops_GGAGR *	keyboard;
	if ((keyboard = HI_Force_Find_Driver (_hoops_RIGC, _hoops_IRPPH)) != null) {

		int *	_hoops_AHSAP;

		if ((_hoops_AHSAP = keyboard->_hoops_RCSHR._hoops_IRPIR) != null)
			keyboard->_hoops_RCSHR._hoops_CPIAP += _hoops_RSAPH (_hoops_CRPPH, _hoops_AHSAP, 1);
		else {
			int				tmp;

			ALLOC_ARRAY (_hoops_AHSAP, _hoops_CRPIR + 1, int);
			tmp = _hoops_CRPIR + 1;
			do *_hoops_AHSAP++ = 0;
			_hoops_RGGA (--tmp == 0);
			_hoops_AHSAP -= _hoops_CRPIR + 1;

			keyboard->_hoops_RCSHR._hoops_CPIAP += _hoops_RSAPH (_hoops_CRPPH, _hoops_AHSAP, 1);

			if (keyboard->_hoops_RCSHR._hoops_CPIAP > 0) {
				keyboard->_hoops_RCSHR._hoops_IRPIR = _hoops_AHSAP;
			}
			else {
				FREE_ARRAY (_hoops_AHSAP, _hoops_CRPIR + 1, int);
			}
		}
		keyboard->_hoops_CGPIR |= _hoops_PARPH|_hoops_IARPH;
		HOOPS_WORLD->_hoops_AARPH = true;
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Enable_Button_Events (
	char const *	_hoops_IRPPH,
	char const *	_hoops_CRPPH) 
{
	_hoops_PAPPR context("Enable_Button_Events");

#ifdef DISABLE_EVENTS
		_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Enable_Button_Events (%S, %S);\n",
		_hoops_IRPPH, _hoops_CRPPH));
	);

	_hoops_CSPPR();
	HI_Enable_Button_Events (context, _hoops_IRPPH, _hoops_CRPPH);
	_hoops_IRRPR();
#endif
}

GLOBAL_FUNCTION void HI_Disable_Button_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_IRPPH,
	char const *			_hoops_CRPPH) 
{
#ifdef DISABLE_EVENTS
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(_hoops_IRPPH);
	UNREFERENCED(_hoops_CRPPH;
#else

	_hoops_RSIIR(_hoops_RIGC);

	_hoops_GGAGR *	keyboard;
	if ((keyboard = HI_Force_Find_Driver (_hoops_RIGC, _hoops_IRPPH)) != null) {

		int *	_hoops_AHSAP;

		if ((_hoops_AHSAP = keyboard->_hoops_RCSHR._hoops_IRPIR) == null) {
			HE_ERROR2 (HEC_BUTTON, HES_BUTTON_EVENT_NOT_ENABLED,
				Sprintf_SP (null, "Cannot disable '%s' button events in '%p' -", 
				_hoops_CRPPH, keyboard->owner), "No buttons at all are enabled");
			return;
		}
		else {
			keyboard->_hoops_RCSHR._hoops_CPIAP += _hoops_RSAPH (_hoops_CRPPH, _hoops_AHSAP, -1);

			if (keyboard->_hoops_RCSHR._hoops_CPIAP == 0) {
				FREE_ARRAY (_hoops_AHSAP, _hoops_CRPIR + 1, int);
				keyboard->_hoops_RCSHR._hoops_IRPIR = null;
			}
		}
		keyboard->_hoops_CGPIR |= _hoops_PARPH|_hoops_IARPH;
		HOOPS_WORLD->_hoops_AARPH = true;
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Disable_Button_Events (
	char const *	_hoops_IRPPH,
	char const *	_hoops_CRPPH) 
{
	_hoops_PAPPR context("Disable_Button_Events");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Disable_Button_Events (%S, %S);\n",
		_hoops_IRPPH, _hoops_CRPPH));
	);

	_hoops_CSPPR();
	HI_Disable_Button_Events (context, _hoops_IRPPH, _hoops_CRPPH); 
	_hoops_IRRPR();
#endif
}



local void HI_Show_Button (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					name,
	int						_hoops_SRPPH) 
{	

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	_hoops_SRIIR *	be;

	if ((be = (_hoops_SRIIR *)HI_Current_Event (_hoops_RIGC, _hoops_CRIIR)) == null) 
		return;

	switch (be->button) {
		case ',': {
			HI_Return_Chars (name, _hoops_SRPPH, "comma", 5);
		}	break;

		case ' ': {
			HI_Return_Chars (name, _hoops_SRPPH, "space", 5);
		}	break;

		case UP_ARROW_KEY: {
			HI_Return_Chars (name, _hoops_SRPPH, "up arrow", 8);
		}	break;

		case DOWN_ARROW_KEY: {
			HI_Return_Chars (name, _hoops_SRPPH, "down arrow", 10);
		}	break;

		case LEFT_ARROW_KEY: {
			HI_Return_Chars (name, _hoops_SRPPH, "left arrow", 10);
		}	break;

		case RIGHT_ARROW_KEY: {
			HI_Return_Chars (name, _hoops_SRPPH, "right arrow", 11);
		}	break;

		case INSERT_KEY: {
			HI_Return_Chars (name, _hoops_SRPPH, "insert", 6);
		}	break;

		case HOME_KEY: {
			HI_Return_Chars (name, _hoops_SRPPH, "home", 4);
		}	break;

		case PAGE_UP_KEY: {
			HI_Return_Chars (name, _hoops_SRPPH, "page up", 7);
		}	break;

		case PAGE_DOWN_KEY: {
			HI_Return_Chars (name, _hoops_SRPPH, "page down", 9);
		}	break;

		case END_KEY: {
			HI_Return_Chars (name, _hoops_SRPPH, "end", 3);
		}	break;

		case _hoops_GAPPH: {
			HI_Return_Chars (name, _hoops_SRPPH, "help", 4);
		}	break;

		case RUBOUT_KEY: {
			HI_Return_Chars (name, _hoops_SRPPH, "rubout", 6);
		}	break;

		default: {
			local const char	_hoops_RAPPH[] = "0123456789";
			char	buf[20];
			char	*_hoops_ASAPR = buf;

			if (_hoops_HGPPH <= be->button &&
				be->button <= _hoops_IGPPH) {
					static	char	control[] = "@abcdefghijklmnopqrstuvwxyz[\\]^_";

					*_hoops_ASAPR++ = 'c'; *_hoops_ASAPR++ = 'o'; *_hoops_ASAPR++ = 'n'; *_hoops_ASAPR++ = 't';
					*_hoops_ASAPR++ = 'r'; *_hoops_ASAPR++ = 'o'; *_hoops_ASAPR++ = 'l'; *_hoops_ASAPR++ = ' ';
					*_hoops_ASAPR++ = control[be->button - _hoops_HGPPH];
			}
			else if (FIRST_FUNCTION_KEY <= be->button &&
				be->button <= _hoops_PGPPH) {
					int		tmp = be->button - FIRST_FUNCTION_KEY;

					*_hoops_ASAPR++ = 'f';
					if (tmp > 9) {
						*_hoops_ASAPR++ = _hoops_RAPPH[tmp/10];
						tmp %= 10;
					}
					*_hoops_ASAPR++ = _hoops_RAPPH[tmp];
			}
			else if (FIRST_KEYPAD_KEY <= be->button &&
				be->button <= _hoops_CGPPH) {
					int		tmp = be->button - FIRST_KEYPAD_KEY;

					*_hoops_ASAPR++ = 'k';
					*_hoops_ASAPR++ = 'p';
					if (tmp > 9) {
						*_hoops_ASAPR++ = _hoops_RAPPH[tmp/10];
						tmp %= 10;
					}
					*_hoops_ASAPR++ = _hoops_RAPPH[tmp];
			}
			else if ((_hoops_ISAPH <= be->button &&
				be->button <= _hoops_CSAPH) ||
				(_hoops_SSAPH <= be->button &&
				be->button <= _hoops_GGPPH)) {
					*_hoops_ASAPR++ = (char)be->button;
			}
			else if (ANYBIT (be->button, 0xFF00)) {
				*_hoops_ASAPR++ = (be->button & 0xFF00) >> 8;
				*_hoops_ASAPR++ = be->button & 0x00FF;
			}
			else {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Bad button value");
				return;
			}

			HI_Return_Chars (name, _hoops_SRPPH, buf, (int)(_hoops_ASAPR - buf));
		}	break;
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Button (
	char *		name) 
{
	_hoops_PAPPR context("Show_Button");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Button () */\n");
	);

	HI_Show_Button (context, name, -1);
}


local void HI_Show_Button_Source (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					path,
	int						_hoops_APAPH,
	char *					name,
	int						_hoops_SRPPH,
	int *					status) 
{

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	_hoops_SRIIR *be;
	char			buf[MAX_ERRMSG];
	char			*_hoops_IPAPH;

	if ((be = (_hoops_SRIIR *)HI_Current_Event (_hoops_RIGC, _hoops_CRIIR)) == null) 
		return;

	if (BIT (be->source->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_BUTTON, HES_DELETED_KEYBOARD, "Can't 'Show' - the 'keyboard' has been deleted");
		return;
	}

	_hoops_IPAPH = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%p", (void *)be->source->owner);
	HI_Return_Chars (path, _hoops_APAPH, buf, (int)(_hoops_IPAPH - buf));
	PUSHNAME(_hoops_RIGC);
	HI_Show_Button (_hoops_RIGC, name, _hoops_SRPPH);
	POPNAME(_hoops_RIGC);
	*status = (int)be->status;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Button_Source (
	char *		path,
	char *		name,
	int *		status) 
{
	_hoops_PAPPR context("Show_Button_Source");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Button_Source () */\n");
	);

	HI_Show_Button_Source (context, path, -1, name, -1, status);
}



#ifndef DISABLE_EVENTS


local Button _hoops_AAPPH (
							  char const		*name) {
								  char			buf[20];
								  char			*_hoops_ASAPR = buf;
								  char			*_hoops_PSAPR = buf+_hoops_GGAPR(buf)-1;
								  int				count;
								  int				button;
								  char			_hoops_PAPPH;

								  while (*name == ' ') ++name;

								  if (*name != '\0') {
									  _hoops_PAPPH = *name;
									  do *_hoops_ASAPR++ = _hoops_SHPCR (*name);
									  _hoops_RGGA (*++name == '\0' || _hoops_ASAPR == _hoops_PSAPR);
									  while (_hoops_ASAPR[-1] == ' ') --_hoops_ASAPR;
									  while (*name == ' ') ++name;
								  }
								  else
									  _hoops_PAPPH = '\0';

								  *_hoops_ASAPR = '\0';
								  count = _hoops_ASAPR - buf;

								  if (*name != '\0') return _hoops_SCAPH;
								  else if (count == 1) {
									  if (buf[0] == ' ' || buf[0] == ',') return _hoops_SCAPH;

									  /* _hoops_HSAPH _hoops_RGAR! */
									  button = (Button)0xFF & (Button)_hoops_PAPPH;
									  if ((_hoops_ISAPH > button || button > _hoops_CSAPH) &&
										  (_hoops_SSAPH > button || button > _hoops_GGPPH))
										  return _hoops_SCAPH;

									  return button;
								  }
								  else if (count == 5 && _hoops_AGGR ("comma", buf)) return ',';
								  else if (count == 5 && _hoops_AGGR ("space", buf)) return ' ';
								  else if (count == 6 && _hoops_AGGR ("rubout", buf)) return RUBOUT_KEY;
								  else if (count == 10 && _hoops_AGGR ("left arrow", buf)) return LEFT_ARROW_KEY;
								  else if (count == 11 && _hoops_AGGR ("right arrow", buf)) return RIGHT_ARROW_KEY;
								  else if (count == 8 && _hoops_AGGR ("up arrow", buf)) return UP_ARROW_KEY;
								  else if (count == 10 && _hoops_AGGR ("down arrow", buf)) return DOWN_ARROW_KEY;
								  else if (count == 9 && _hoops_GPPSA ("control ", 8, buf)) {
									  /* _hoops_HSAPH _hoops_RGAR!! */

									  if (buf[8] == '@')
										  button = _hoops_HGPPH;
									  else
										  button = (buf[8] - 'a' + 1) + _hoops_HGPPH;

									  if (button < _hoops_HGPPH || button > _hoops_IGPPH)
										  return _hoops_SCAPH;

									  return button;
								  }
								  else if ((count == 2 || count == 3) && buf[0] == 'f') {
									  button = FIRST_FUNCTION_KEY + number (&buf[1]);

									  if (button < FIRST_FUNCTION_KEY || button > _hoops_PGPPH)
										  return _hoops_SCAPH;

									  return button;
								  }
								  else if ((count == 3 || count == 4) &&
									  buf[0] == 'k' && buf[1] == 'p') {
										  button = FIRST_KEYPAD_KEY + number (&buf[2]);

										  if (button < FIRST_KEYPAD_KEY || button > _hoops_CGPPH)
											  return _hoops_SCAPH;

										  return button;
								  }
								  else return _hoops_SCAPH;
}
#endif


HC_INTERFACE void HC_CDECL HC_Queue_Button_Event (
	char const *	_hoops_HAPPH,
	char const *	_hoops_IAPPH,
	int				status) 
{
	_hoops_PAPPR context("Queue_Button_Event");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Queue_Button_Event (%S, %S, ", _hoops_HAPPH, _hoops_IAPPH));
		HI_Dump_Code (Sprintf_D (null, "%d);\n", status));
	);

	Button			button;
	_hoops_SRIIR *	be;
	_hoops_GGAGR *			keyboard;

	// _hoops_ASIGA _hoops_CSPIP _hoops_HCAPH

	if ((keyboard = HI_Force_Find_Driver (context, _hoops_HAPPH)) == null) 
		return;

	button = _hoops_AAPPH (_hoops_IAPPH);

	if (button == _hoops_SCAPH) {
		HE_ERROR (HEC_BUTTON, HES_INVALID_INPUT,
			Sprintf_S (null,"'%s' is not a recognized simple button name", _hoops_IAPPH));
		return;
	}

	if (HOOPS_WORLD->_hoops_AARPH) 
		HI_Update_Events (context);

	if (keyboard->_hoops_CPCR._hoops_IRPIR == null ||
		keyboard->_hoops_CPCR._hoops_IRPIR[_hoops_HCRPH(button)] <= 0) {
			HE_WARNING (HEC_BUTTON, HES_BUTTON_EVENT_NOT_ENABLED,
				Sprintf_SP (null, "Button '%s' is not enabled on '%p'", _hoops_IAPPH, keyboard->owner));
			return;
	}

	ZALLOC (be, _hoops_SRIIR);
	be->next = null;
	be->owner = HOOPS_WORLD;
	be->_hoops_HIHI = 1;
	be->type = _hoops_CRIIR;
	be->_hoops_PHSHA = HI_What_Time();

	be->button = button;
	be->source = keyboard;
	be->status = status;
	_hoops_PRRH (keyboard);

	if (context->_hoops_PCRPH == null) {
		context->_hoops_PAARH = (_hoops_HISHA *)be;
		be->backlink = &context->_hoops_PAARH;
	}
	else {
		context->_hoops_PCRPH->next = (_hoops_HISHA *)be;
		be->backlink = &context->_hoops_PCRPH->next;
		_hoops_HPRH (context->_hoops_PCRPH);
	}

	context->_hoops_PCRPH = (_hoops_HISHA *)be;
	_hoops_PRRH (be);

	be->_hoops_RAIIR = null;
#endif
}


 local void HI_Get_Button (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					name,
	int						_hoops_SRPPH) 
{

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	_hoops_CSPPR();
	HI_Enable_Button_Events (_hoops_RIGC, "?Keyboard", "anything");
	_hoops_IRRPR();

	char	_hoops_RHAPH[20];
	do {
		_hoops_RHAPH[0] = 'b';	/* _hoops_GGR _hoops_AGIR _hoops_RH _hoops_IAAPH _hoops_ISHS */
		HI_Await_Event (_hoops_RIGC, _hoops_RHAPH, _hoops_GGAPR(_hoops_RHAPH));
		if (_hoops_RHAPH[0] == 'n')		/* _hoops_PIRC */
			HI_Exit_Program();
	} _hoops_RGGA (_hoops_RHAPH[0] == 'b');

	_hoops_CSPPR();
	HI_Disable_Button_Events (_hoops_RIGC, "?Keyboard", "anything");
	_hoops_IRRPR();

	HI_Show_Button (_hoops_RIGC, name, _hoops_SRPPH);
#endif
}


HC_INTERFACE void HC_CDECL HC_Get_Button (
	char *	name) 
{
	_hoops_PAPPR context("Get_Button");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Get_Button (string_buffer);\n");
	);

	HI_Get_Button (context, name, -1);
}



GLOBAL_FUNCTION void HI_Enable_Selection_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_SHAPH,
	char const *			_hoops_GIAPH) 
{
#ifdef DISABLE_EVENTS
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(_hoops_SHAPH);
	UNREFERENCED(_hoops_GIAPH);
#else
	_hoops_RSIIR(_hoops_RIGC);

	_hoops_GGAGR *	locater;
	_hoops_GGAGR *	target;

	if ((locater = HI_Force_Find_Driver (_hoops_RIGC, _hoops_SHAPH)) == null) 
		return;

	if ((target = HI_Force_Find_Driver (_hoops_RIGC, _hoops_GIAPH)) == null) 
		return;

	if (locater->_hoops_RCSHR.target != null && locater->_hoops_RCSHR.target != target) {
		char	buf[MAX_ERRMSG];

		HE_ERROR2 (HEC_SELECTION, HES_TARGET_LOCATOR_CONNECTED,
			Sprintf_PP (null, "Locater '%p' is already connected to target '%p' -", locater->owner, locater->_hoops_RCSHR.target->owner),
			Sprintf_P (buf, "Can't also connect it to target '%p'", target->owner));
		return;
	}

	if (locater->_hoops_RCSHR.target == null) {
		target->_hoops_CGPIR |= _hoops_PARPH;
		HOOPS_WORLD->_hoops_AARPH = true;
		locater->_hoops_RCSHR.target = target;
		if (target != locater)
			_hoops_PRRH (target);
	}
	++locater->_hoops_RCSHR._hoops_HPIAP;
	locater->_hoops_CGPIR |= _hoops_PARPH;
	HOOPS_WORLD->_hoops_AARPH = true;
#endif
}



HC_INTERFACE void HC_CDECL HC_Enable_Selection_Events (
	char const *	_hoops_SHAPH,
	char const *	_hoops_GIAPH) 
{
	_hoops_PAPPR context("Enable_Selection_Events");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Enable_Selection_Events (%S, %S);\n", _hoops_SHAPH, _hoops_GIAPH));
	);

	_hoops_CSPPR();
	HI_Enable_Selection_Events (context, _hoops_SHAPH, _hoops_GIAPH); 
	_hoops_IRRPR();
#endif
}



GLOBAL_FUNCTION void HI_Disable_Selection_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_SHAPH,
	char const *			_hoops_GIAPH) 
{

#ifdef DISABLE_EVENTS
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(_hoops_SHAPH);
	UNREFERENCED(_hoops_GIAPH);
#else
	_hoops_RSIIR(_hoops_RIGC);

	_hoops_GGAGR *	locater;
	_hoops_GGAGR *	target;

	if ((locater = HI_Force_Find_Driver (_hoops_RIGC, _hoops_SHAPH)) == null) 
		return;
	if ((target = HI_Force_Find_Driver (_hoops_RIGC, _hoops_GIAPH)) == null) 
		return;

	if (locater->_hoops_RCSHR.target != target) {
		_hoops_PHPGR (HEC_SELECTION, HES_TARGET_LOCATOR_NOT_CONNECTED,
			Sprintf_PP (null,"Locater '%p' is not connected to target '%p' -", 
			locater->owner, locater->_hoops_RCSHR.target->owner), "Can't disable");
	}
	else if (--locater->_hoops_RCSHR._hoops_HPIAP == 0 &&
		locater->_hoops_RCSHR._hoops_IPIAP == 0) {
			target->_hoops_CGPIR |= _hoops_PARPH;
			HOOPS_WORLD->_hoops_AARPH = true;
			if (target != locater) _hoops_HPRH (target);
			locater->_hoops_RCSHR.target = null;
	}
	locater->_hoops_CGPIR |= _hoops_PARPH;
	HOOPS_WORLD->_hoops_AARPH = true;
#endif
}



HC_INTERFACE void HC_CDECL HC_Disable_Selection_Events (
	char const *		_hoops_SHAPH,
	char const *		_hoops_GIAPH) 
{
	_hoops_PAPPR context("Disable_Selection_Events");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Disable_Selection_Events (%S, %S);\n", _hoops_SHAPH, _hoops_GIAPH));
	);

	_hoops_CSPPR();
	HI_Disable_Selection_Events (context, _hoops_SHAPH, _hoops_GIAPH); 
	_hoops_IRRPR();
#endif
}



local void HI_Show_Selection (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					name,
	int						_hoops_SRPPH) 
{

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (_hoops_RIGC, _hoops_SAIIR)) == null)
		return;

	if (BIT (_hoops_GPIIR->_hoops_APIIR->item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SELECTION, HES_DELETED_ITEM, "Can't 'Show' - the item has been deleted");
		return;
	}

	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_GPIIR->_hoops_APIIR->item;
	while (_hoops_SRCP->type != _hoops_IRCP)
		_hoops_SRCP = (_hoops_CRCP *)_hoops_SRCP->owner;

	if (_hoops_SRCP->name.length > 0)
		HI_Return_Sprintf1 (name, _hoops_SRPPH, "%N", &_hoops_SRCP->name);
	else {
		char	buf[_hoops_GHAPH];
		Key	key = _hoops_SRCP->key;
		char * _hoops_IPAPH = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%k", (void *)&key);
		HI_Return_Chars (name, _hoops_SRPPH, buf, (int)(_hoops_IPAPH - buf));
	}
#endif
}



local void HI_Get_Selection (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					name,
	int						_hoops_SRPPH) 
{
#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	_hoops_CSPPR();
	HI_Enable_Selection_Events (_hoops_RIGC, "?Locater", "?Picture");
	_hoops_IRRPR();

	char	_hoops_RHAPH[20];
	do {
		_hoops_RHAPH[1] = 'e';	/* _hoops_GGR _hoops_AGIR _hoops_RH _hoops_IAAPH _hoops_ISHS */
		HI_Await_Event (_hoops_RIGC, _hoops_RHAPH, _hoops_GGAPR(_hoops_RHAPH));

		if (_hoops_RHAPH[0] == 'n')		/* _hoops_PIRC */
			HI_Exit_Program();

	} _hoops_RGGA (_hoops_RHAPH[1] == 'e');

	_hoops_CSPPR();
	HI_Disable_Selection_Events (_hoops_RIGC, "?Locater", "?Picture");
	_hoops_IRRPR();

	HI_Show_Selection (_hoops_RIGC, name, _hoops_SRPPH);

#endif
}


HC_INTERFACE void HC_CDECL HC_Get_Selection (
	char *		name) 
{
	_hoops_PAPPR context("Get_Selection");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Get_Selection (string_buffer);\n");
	);

	HI_Get_Selection (context, name, -1);
}



#ifndef DISABLE_EVENTS

local	const char		_hoops_CAPPH[] = "Key does not refer to a valid segment or to valid geometry";

struct _hoops_SAPPH {
	_hoops_CRCP *			segment;
	int					count;
};

local void _hoops_GPPPH (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_CRCP *					_hoops_SRCP,
	void *						info) {
	_hoops_SAPPH *	pt = (_hoops_SAPPH *)info;

	UNREFERENCED(_hoops_RIGC);

	pt->segment = _hoops_SRCP;
	pt->count++;
}


local _hoops_HPAH * _hoops_RPPPH (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			pathname,
	Key						key) {
	_hoops_HPAH *				_hoops_CISIR = null;

	if (key < 0)
		_hoops_CISIR = (_hoops_HPAH *)_hoops_RCSSR (_hoops_RIGC, key);
	else {
		/* _hoops_SIAS _hoops_SHH _hoops_HCIAA _hoops_APPPH, _hoops_HIH _hoops_RH _hoops_PCIRA (_hoops_ICCIA) _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_RH _hoops_IGS _hoops_CAGH */
		_hoops_SAPPH			pt;

		if (pathname[0] == '\0')	/* _hoops_HIH _hoops_RPP _hoops_PIRC _hoops_RAGA, _hoops_SR _hoops_RGAR _hoops_HS _hoops_RH _hoops_IGS _hoops_CAGH _hoops_IS _hoops_HPPR */
			pathname = ".";

		pt.count = 0;
		HI_For_Each (_hoops_RIGC, pathname, false, _hoops_GPPPH, (void *)&pt);

		if (pt.count == 1)
			_hoops_CISIR = _hoops_SISIR (_hoops_RIGC, key, pt.segment);
	}

	if (_hoops_CISIR == null)
		HE_ERROR (HEC_SELECTION, HES_INVALID_KEY, _hoops_CAPPH);

	return _hoops_CISIR;
}



#ifdef _hoops_PPPPH

local _hoops_HPAH * _hoops_HPPPH (
	char const		*pathname,
	Key			key,
	int				offset1,
	int				offset2,
	int				offset3) {
	_hoops_HPAH		*_hoops_CISIR = null;

	if ((_hoops_CISIR = _hoops_RPPPH (pathname, key)) == null)	/* _hoops_RIHH _hoops_AIAH _hoops_GIR */
		return null;


	if (!((_hoops_AHRIR <= _hoops_CISIR->type &&
							 _hoops_CISIR->type <= _hoops_PHRIR &&
		   !BIT(_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR)) ||
		  (_hoops_CISIR->type == _hoops_IRCP &&
		   !BIT(_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR)))) {
		HE_ERROR (HEC_SELECTION, HES_INVALID_KEY, _hoops_CAPPH);
		return null;
	}

	switch (_hoops_CISIR->type) {
		case _hoops_IRCP: {
			if (!ANYBIT (_hoops_CISIR->_hoops_SSGPR.segment._hoops_PHSI,
						 _hoops_SHSIR|_hoops_GISIR)) {
				HE_ERROR (HEC_SELECTION, HES_SEGMENT,
						Sprintf_P (null,
						"Can't directly select non-windowed segment '%p'",
						(_hoops_CRCP *)_hoops_CISIR));
				return null;
			}
			if (offset1 != -1 || offset2 != -1 || offset3 != -1) {
				HE_ERROR (HEC_SELECTION, HES_WINDOW,
						"Window segment specified; offsets not all -1");
				return null;
			}
		}	break;

		case _hoops_PIIP: {
			if ((!(offset1 == 0 && offset2 == 1) &&
				 !(offset2 == 0 && offset1 == 1)) ||
				offset3 != 0) {
				HE_ERROR (HEC_SELECTION, HES_POLYLINE,
						"Offsets not valid for specified line");
				return null;
			}
		}	break;

		case _hoops_PCIP: {
			if (!(offset1 == 0 && offset2 == 0 && offset3 == 0)) {
				HE_ERROR (HEC_SELECTION, HES_MARKER,
						"Offsets not all zero for specified marker");
				return null;
			}
		}	break;

		case _hoops_HGCP: {
			if (offset3 != 0 || offset1 < 0 || offset2 < 0 ||
				offset1 >= _hoops_CISIR->geometry.image.height ||
				offset2 >= _hoops_CISIR->geometry.image.width) {
				HE_ERROR (HEC_SELECTION, HES_IMAGE,
						"Offsets not valid for specified image");
				return null;
			}
		}	break;

		case _hoops_IIIP: {
			if (offset3 != 0 ||
				offset1 < 0 || offset2 < 0 ||
				offset1 >= Abs(_hoops_CISIR->geometry.polyline.count) ||
				offset2 >= Abs(_hoops_CISIR->geometry.polyline.count) ||
				!(offset1 == offset2 + 1 ||
				  offset2 == offset1 + 1 ||
				  (offset1 == 0 &&
				   offset2 == Abs(_hoops_CISIR->geometry.polyline.count) - 1) ||
				  (offset2 == 0 &&
				   offset1 == Abs(_hoops_CISIR->geometry.polyline.count) - 1))) {
				HE_ERROR (HEC_SELECTION, HES_POLYLINE,
						"Offsets not valid for specified polyline");
				return null;
			}
		}	break;

		case _hoops_RCIP: {
			if (offset3 != 0 ||
				offset1 < 0 || offset2 < 0 ||
				offset1 >= _hoops_CISIR->geometry.polygon.count ||
				offset2 >= _hoops_CISIR->geometry.polygon.count ||
				!(offset1 == offset2 + 1 ||
				  offset2 == offset1 + 1 ||
				  (offset1 == 0 &&
				   offset2 == _hoops_CISIR->geometry.polygon.count - 1) ||
				  (offset2 == 0 &&
				   offset1 == _hoops_CISIR->geometry.polygon.count - 1))) {
				HE_ERROR (HEC_SELECTION, HES_POLYGON,
						"Offsets not valid for specified polygon");
				return null;
			}
		}	break;

		case HK_STRING_CURSOR: {
			if (!(offset1 == 0 && offset2 == 0 && offset3 == 0)) {
				HE_ERROR (HEC_SELECTION, HES_STRING_CURSOR,
						"Offsets not all zero for specified cursor");
				return null;
			}
		}	break;

		case _hoops_AGCP: {
			if (offset3 != 0 || offset1 != 0 ||
				offset2 < 0 || offset2 >= _hoops_CISIR->geometry.text.count) {
				HE_ERROR (HEC_SELECTION, HES_TEXT,
						"Offsets not valid for specified text");
				return null;
			}
		}	break;

		case _hoops_ICIP: {
/* _hoops_GGCH _hoops_SS */
			switch (_hoops_CISIR->geometry.light._hoops_PRR) {
				case _hoops_H:
				case _hoops_C:
				case _hoops_I: {
					HE_ERROR (HEC_SELECTION, HES_LIGHT,
							"Invalid light type specified");
					return null;
				}	/* _hoops_IHSA; */

				case _hoops_S: {
					if (offset3 != 0 ||
						offset1 < 0 || offset2 < 0 ||
						offset1 >= _hoops_CISIR->geometry.light.l.area.count ||
						offset2 >= _hoops_CISIR->geometry.light.l.area.count ||
						!(offset1 == offset2 + 1 ||
						  offset2 == offset1 + 1 ||
						  (offset1 == 0 &&
						   offset2 == _hoops_CISIR->geometry.light.l.area.count - 1) ||
						  (offset2 == 0 &&
						   offset1 == _hoops_CISIR->geometry.light.l.area.count - 1))) {
						HE_ERROR (HEC_SELECTION, HES_LIGHT,
								"Offsets not valid for specified area light");
						return null;
					}
				}
			}
		}	break;

		case _hoops_SGCP:
		case _hoops_RIIP:
		case _hoops_GRCP:
		case _hoops_RRCP:
		case _hoops_CGCP:
		case _hoops_GIIP: {
			if (offset1 < 1 || offset1 > 3 ||
				offset2 < 1 || offset2 > 3 ||
				offset1 == offset2 ||
				offset3 != 0) {

				HE_ERROR (HEC_SELECTION, HES_INVALID_OFFSET,
						"Offsets not valid for specified item");
				return null;
			}
		}	break;

		case _hoops_ASIP:
		case _hoops_CSIP:
		case _hoops_GGCP:
		case _hoops_GSIP:
		case _hoops_SCIP: {
			return _hoops_CISIR; /* _hoops_SAHR _hoops_IIS _hoops_SCH _hoops_PHHR _hoops_RHIR _hoops_IH _hoops_HA */
		}		/*_hoops_IHSA;*/

		/* _hoops_AGIR _hoops_IPPPH: */

		default: {
			HE_ERROR (HEC_SELECTION, HES_INVALID_INPUT,
					_hoops_CAPPH);
			return null;
		}		/* _hoops_IHSA; */
	}
	return _hoops_CISIR;
}

#endif



local _hoops_PGRPR *_hoops_CPPPH (
	_hoops_AIGPR *	_hoops_RIGC,
	const char *			_hoops_SPPPH, 
	int						_hoops_GHPPH, 
	const char *			_hoops_RHPPH, 
	int						_hoops_AHPPH,
	const char *			_hoops_PHPPH, 
	int						_hoops_HHPPH)
{
	_hoops_CRCP *from, *to;
	_hoops_PGRPR *include;
	Subsegment *_hoops_GIPIA;
	char save;
	int i;
	char *_hoops_IHPPH = (char alter *)_hoops_SPPPH;
	char *includee = (char alter *)_hoops_RHPPH;
	char *inc = (char alter *)_hoops_PHPPH;

	/* _hoops_HGCR _hoops_IRS _hoops_CRS _hoops_IS _hoops_RH "_hoops_HII" _hoops_CAGH */
	save = _hoops_IHPPH[_hoops_GHPPH];
	_hoops_IHPPH[_hoops_GHPPH] = '\0';

	from = HI_One_Segment_Search(_hoops_RIGC, _hoops_IHPPH , true);

	if (from == null) {
		HE_ERROR (HEC_SELECTION, HES_INVALID_PATH_TOKEN,
			Sprintf_S (null, "invalid segment in selection path: %S", _hoops_IHPPH));
		return null;
	}
	_hoops_IHPPH[_hoops_GHPPH] = save;

	/* _hoops_HGCR _hoops_IRS _hoops_CRS _hoops_IS _hoops_RH "_hoops_IS" _hoops_CAGH */
	save = includee[_hoops_AHPPH];
	includee[_hoops_AHPPH] = '\0';

	to = HI_One_Segment_Search(_hoops_RIGC, includee, true);
	if (to == null) {
		HE_ERROR (HEC_SELECTION, HES_INVALID_PATH_TOKEN,
			Sprintf_S (null, "invalid segment in selection path: %S", includee));
		return null;
	}
	includee[_hoops_AHPPH] = save;

	/* _hoops_SRPA "_hoops_IS" _hoops_GH _hoops_PHPA _hoops_GGR _hoops_RH _hoops_CHPPH _hoops_GAR _hoops_CHIA _hoops_HPP _hoops_RH _hoops_PHI _hoops_IIGR '<'
	 * _hoops_HPS _hoops_GGR _hoops_RH _hoops_GCIS _hoops_AAS */
	if (*inc != '<') {
		save = inc[_hoops_HHPPH];
		inc[_hoops_HHPPH] = '\0';
		HE_ERROR (HEC_SELECTION, HES_INVALID_PATH_TOKEN,
			Sprintf_S (null, "Malformed selection path: %S does not look like an include", inc));
		inc[_hoops_HHPPH] = save;
		return null;
	}
	for (i = 1 ; (inc[i] == '<') && (to->owner != null) ; i++)
		to = to->owner;
	if (inc[i] == '<') {
		save = inc[_hoops_HHPPH];
		inc[_hoops_HHPPH] = '\0';
		HE_ERROR (HEC_SELECTION, HES_INVALID_PATH_TOKEN,
			Sprintf_S (null, "Specified ancestry in selection path runs past root segment: %S", inc));
		inc[_hoops_HHPPH] = save;
		return null;
	}
	
	/* _hoops_HA _hoops_GIPHR _hoops_RH _hoops_CAGH _hoops_IH _hoops_IRS _hoops_PIS _hoops_GCIS */
	_hoops_GIPIA = from->_hoops_RGRPR;
	while (_hoops_GIPIA != null) {
		if (_hoops_GIPIA->type == _hoops_AGRPR) {
			if (_hoops_SSIGP (_hoops_GIPIA) == to)
				break; /* _hoops_GSGI _hoops_SCH! */
		}
		_hoops_GIPIA = _hoops_GIPIA->next;
	}
	include = (_hoops_PGRPR *)_hoops_GIPIA;
	if (include == null) {
		HE_ERROR (HEC_SELECTION, HES_INVALID_PATH_TOKEN,
			"impossible selection path specified");
		return null;
	}
	return include;

} 


local _hoops_RISAP *_hoops_SHPPH  (
	_hoops_AIGPR * _hoops_RIGC,
	const char *pathname)
{
	const char *_hoops_GIPPH, *_hoops_RIPPH;
	const char *_hoops_AIPPH, *_hoops_PIPPH;
	const char *_hoops_HIPPH, *_hoops_IIPPH;
	_hoops_RISAP *_hoops_CIPPH = null, *tail = null, *temp;
	_hoops_PGRPR *include;

	if (pathname == null)
		return null; /* _hoops_IRAP _hoops_ICCIA */

	_hoops_AIPPH = pathname;
	while (*_hoops_AIPPH == ' ' && *_hoops_AIPPH != '\0') 
		_hoops_AIPPH++;
	_hoops_PIPPH = strchr (_hoops_AIPPH, '<');
	if (_hoops_PIPPH == null)
		return null; /* _hoops_ICCIA _hoops_CSAP _hoops_PCCP _hoops_IPPSR _hoops_CRAA _hoops_CCA _hoops_PSP _hoops_CRRPR */


	for (;;) {
		_hoops_HIPPH = _hoops_PIPPH;
		while (*_hoops_HIPPH == ' ' && *_hoops_HIPPH != '\0') 
			_hoops_HIPPH++;
		_hoops_IIPPH = _hoops_HIPPH;
		while (*_hoops_IIPPH != ' ' && *_hoops_IIPPH != '\0') 
			_hoops_IIPPH++;

		if (_hoops_HIPPH == _hoops_IIPPH)
			break; /* _hoops_PSP _hoops_RRI _hoops_CRRPR _hoops_IS _hoops_HPPP */

		_hoops_GIPPH = _hoops_IIPPH;
		while (*_hoops_GIPPH == ' ' && *_hoops_GIPPH != '\0') 
			_hoops_GIPPH++;
		_hoops_RIPPH = strchr (_hoops_GIPPH, '<');
		if (_hoops_RIPPH == null)
			_hoops_RIPPH = _hoops_GIPPH + strlen (_hoops_GIPPH);
		
		include = _hoops_CPPPH (_hoops_RIGC,
				_hoops_GIPPH, _hoops_RIPPH - _hoops_GIPPH, 
				_hoops_AIPPH, _hoops_PIPPH - _hoops_AIPPH, 
				_hoops_HIPPH, _hoops_IIPPH - _hoops_HIPPH);
		if (include == null)
			break; /* _hoops_RIHH _hoops_GGR _hoops_PHSPR _hoops_GCIS -- _hoops_SAHR _hoops_ASRC _hoops_PCPA _hoops_SR _hoops_HS _hoops_HIS _hoops_SGIP */

		ALLOC (temp, _hoops_RISAP);
		if (tail == null) {
			_hoops_CIPPH = temp;
		}
		else {
			tail->prev = temp;
		}
		tail = temp;
		temp->prev = null;
		temp->include = include;
		_hoops_PRRH (include);
		_hoops_AIPPH = _hoops_GIPPH;
		_hoops_PIPPH = _hoops_RIPPH;
	}
	return _hoops_CIPPH;
} 
#endif


GLOBAL_FUNCTION void HI_Queue_Selection_Event (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_PCAPH,
	char const *			_hoops_SASHA,
	char const *			_hoops_RPSHA,
	int						status,
	char const *			pathname,
	Key						_hoops_HSICA,
	int						offset1,
	int						offset2,
	int						offset3,
	double					xw,
	double					yw,
	double					_hoops_RCSAP,
	double					xc,
	double					yc,
	double					zc,
	_hoops_AISIA *	_hoops_GSHIR) 
{
	_hoops_GGAGR *					source;
	_hoops_GGAGR *					target;
	_hoops_APSHA			action;
	Selection_Event *		_hoops_GPIIR;
	_hoops_RPIIR *		si;
	_hoops_HPAH *				item;

	_hoops_RSIIR(_hoops_RIGC);

	while (*_hoops_SASHA == ' ') ++_hoops_SASHA;
	if (*_hoops_SASHA == '\0') target = null;
	else {
		if ((target = HI_Force_Find_Driver (_hoops_RIGC, _hoops_SASHA)) == null) 
			return;
	}

	{	char const		*_hoops_RPPA = _hoops_PCAPH;

		while (*_hoops_RPPA == ' ') ++_hoops_RPPA;

		if (*_hoops_RPPA == '\0') source = null;
		else {
			if ((source = HI_Force_Find_Driver (_hoops_RIGC, _hoops_PCAPH)) == null) 
				return;

			if (HOOPS_WORLD->_hoops_AARPH) 
				HI_Update_Events (_hoops_RIGC);

			if (target == null) {
				HE_ERROR (HEC_SELECTION, HES_LOCATOR_WITHOUT_DISPLAY,
						"'Locater' given without a 'display'");
				return;
			}
			else if (source->_hoops_CPCR._hoops_HPIAP <= 0 ||
				target != source->_hoops_CPCR.target) {
				HE_ERROR (HEC_SELECTION, HES_SELECTION_EVENT_NOT_ENABLED,
						Sprintf_PP (null,"Selection events not enabled from locater '%p' to display '%p'",
							source->owner, target->owner));
				return;
			}
		}
	}

	if ((action = HI_Decipher_Action (_hoops_RPSHA)) == 0) 
		return;


#ifdef _hoops_PPPPH
	if (xw < -1.0001f || xw > 1.0001f || yw < -1.0001f || yw > 1.0001f) {
		HE_ERROR (HEC_SELECTION, HES_WINDOW,
				"Window x or y is not in the range of -1 to +1");
		return;
	}

	if ((item = _hoops_HPPPH (pathname, _hoops_HSICA, offset1, offset2, offset3)) == null) return;
#else
	item = _hoops_RPPPH (_hoops_RIGC, pathname, _hoops_HSICA);
#endif

	ZALLOC (_hoops_GPIIR, Selection_Event);
	_hoops_GPIIR->owner = HOOPS_WORLD;
	_hoops_GPIIR->_hoops_HIHI = 1;
	_hoops_GPIIR->type = _hoops_SAIIR;
	_hoops_GPIIR->_hoops_PHSHA = HI_What_Time();
	_hoops_GPIIR->_hoops_IHSHA.left = MAX_FLOAT;		/* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA */
	_hoops_GPIIR->_hoops_IHSHA.right = MAX_FLOAT;		/* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA */
	_hoops_GPIIR->_hoops_IHSHA.bottom = MAX_FLOAT;		/* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA */
	_hoops_GPIIR->_hoops_IHSHA.top = MAX_FLOAT;			/* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA */
	_hoops_GPIIR->_hoops_IHSHA.hither = MAX_FLOAT;		/* _hoops_HHHGH */
	_hoops_GPIIR->_hoops_IHSHA.yon = MAX_FLOAT;			/* _hoops_HHHGH */
	_hoops_GPIIR->_hoops_CHSHA = action;
	if ((_hoops_GPIIR->source = source) != null)
		_hoops_PRRH (source);
	if ((_hoops_GPIIR->target = target) != null)
		_hoops_PRRH (target);
	_hoops_GPIIR->status = status;

	ZALLOC (si, _hoops_RPIIR);
	_hoops_GPIIR->_hoops_APIIR = si;
	si->xw = (float)xw;
	si->yw = (float)yw;
	si->_hoops_RCSAP = (float)_hoops_RCSAP;
	si->xc = (float)xc;
	si->yc = (float)yc;
	si->zc = (float)zc;
	si->_hoops_GCSAP = action;
	si->item = item;
	_hoops_PRRH (si->item);
	if (item->_hoops_CPGPR < _hoops_SHSSR)
		si->_hoops_CISAP = item->key;
	else
		si->_hoops_CISAP = _hoops_AIRIR(item);
	si->_hoops_HSICA = _hoops_HSICA;
	si->_hoops_SISAP = _hoops_SHPPH (_hoops_RIGC, pathname);
	si->offset1 = offset1;
	si->offset2 = offset2;
	si->offset3 = offset3;
	si->_hoops_HCSAP = -999.0f;	/* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA */

	if (_hoops_GSHIR) {	
		if (_hoops_RIGC->_hoops_SIPPH != null) 
			FREE(_hoops_RIGC->_hoops_SIPPH, _hoops_AISIA);
		_hoops_RIGC->_hoops_SIPPH = _hoops_GSHIR;
	}

	if (_hoops_RIGC->_hoops_PCRPH == null) {
		_hoops_GPIIR->backlink = &_hoops_RIGC->_hoops_PAARH;
		_hoops_RIGC->_hoops_PAARH = (_hoops_HISHA *)_hoops_GPIIR;
	}
	else {
		_hoops_RIGC->_hoops_PCRPH->next = (_hoops_HISHA *)_hoops_GPIIR;
		_hoops_GPIIR->backlink = &_hoops_RIGC->_hoops_PCRPH->next;
		_hoops_HPRH (_hoops_RIGC->_hoops_PCRPH);
	}

	_hoops_RIGC->_hoops_PCRPH = (_hoops_HISHA *)_hoops_GPIIR;
	_hoops_PRRH (_hoops_GPIIR);

}


HC_INTERFACE void HC_CDECL HC_Queue_Selection_Event (
	char const				*_hoops_PCAPH,
	char const				*_hoops_SASHA,
	char const				*_hoops_RPSHA,
	int						status,
	char const				*pathname,
	Key						_hoops_HSICA,
	int						offset1,
	int						offset2,
	int						offset3,
	double					xw,
	double					yw,
	double					_hoops_RCSAP,
	double					xc,
	double					yc,
	double					zc)
{
	_hoops_PAPPR context("Queue_Selection_Event");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Queue_Selection_Event (%S, %S, ", _hoops_PCAPH, _hoops_SASHA));
		HI_Dump_Code (Sprintf_S (null, "%S, ", _hoops_RPSHA));
		HI_Dump_Code (Sprintf_D (null, "%d, ", status));
		HI_Dump_Code (Sprintf_S (null, "%S, ", pathname));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D), ", _hoops_HSICA));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", offset1, offset2));
		HI_Dump_Code (Sprintf_D (null, "%d, ", offset3));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", xw, yw));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", _hoops_RCSAP, xc));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", yc, zc));
	);

	_hoops_CSPPR();
	HI_Queue_Selection_Event(context, _hoops_PCAPH, _hoops_SASHA, 
		_hoops_RPSHA, status, pathname, _hoops_HSICA, offset1, offset2, offset3, xw, yw, _hoops_RCSAP, xc, yc, zc,0);
	_hoops_IRRPR();
#endif
}

GLOBAL_FUNCTION void HI_Queue_Related_Selection (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			pathname,
	Key						_hoops_HSICA,
	int						offset1,
	int						offset2,
	int						offset3,
	double					xw,
	double					yw,
	double					_hoops_RCSAP,
	double					xc,
	double					yc,
	double					zc) 
{

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	_hoops_RPIIR *	si;
	_hoops_RPIIR *	_hoops_GCPPH;
	Selection_Event *	_hoops_GPIIR;
	_hoops_HPAH *			item;

	if (_hoops_RIGC->_hoops_PCRPH != null)
		_hoops_GPIIR = (Selection_Event *)_hoops_RIGC->_hoops_PCRPH;
	else if (_hoops_RIGC->_hoops_PISHA != null)
		_hoops_GPIIR = (Selection_Event *)_hoops_RIGC->_hoops_PISHA;
	else {
		HE_ERROR (HEC_SELECTION, HES_INVALID_RELATED_EVENT, "Can't be 'related' - no pending events");
		return;
	}

	if (_hoops_GPIIR->type != _hoops_SAIIR) {
		HE_ERROR (HEC_SELECTION, HES_INVALID_RELATED_EVENT, "Can't be 'related' - previous event is not 'selection'");
		return;
	}

#ifdef _hoops_PPPPH
	if (xw < -1.0001f || xw > 1.0001f || yw < -1.0001f || yw > 1.0001f) {
		HE_ERROR (HEC_SELECTION, HES_WINDOW, "Window x or y is not in the range of -1 to +1");
		return;
	}
	if ((item = _hoops_HPPPH (pathname, _hoops_HSICA, offset1, offset2, offset3)) == null)
		return;
#else
	if ((item = _hoops_RPPPH (_hoops_RIGC, pathname, _hoops_HSICA)) == null)
		return;
#endif

	if ((si = _hoops_GPIIR->_hoops_APIIR) == null) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Selection of 0 items");
		return;
	}

	_hoops_RGGA (si->next == null) si = si->next;
	_hoops_GCPPH = si;

	ZALLOC (si, _hoops_RPIIR);
	if (_hoops_GCPPH == null)
		_hoops_GPIIR->_hoops_APIIR = si;
	else
		_hoops_GCPPH->next = si;

	si->next = null;
	si->xw = (float)xw;
	si->yw = (float)yw;
	si->_hoops_RCSAP = (float)_hoops_RCSAP;
	si->xc = (float)xc;
	si->yc = (float)yc;
	si->zc = (float)zc;
	si->_hoops_GCSAP = _hoops_GCPPH->_hoops_GCSAP;		/* _hoops_PAIHR: _hoops_SR _hoops_SARS'_hoops_RA _hoops_HAGIP */
	si->item = item;
	_hoops_PRRH (si->item);
	si->_hoops_HSICA = _hoops_HSICA;
	si->_hoops_SISAP = si->_hoops_SISAP = _hoops_SHPPH (_hoops_RIGC, pathname);
	si->offset1 = offset1;
	si->offset2 = offset2;
	si->offset3 = offset3;
	si->_hoops_HCSAP = -999.0f;	/* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA */
	si->_hoops_ACSAP = null;
#endif
}



HC_INTERFACE void HC_CDECL HC_Queue_Related_Selection (
	char const *		pathname,
	Key					_hoops_HSICA,
	int					offset1,
	int					offset2,
	int					offset3,
	double				xw,
	double				yw,
	double				_hoops_RCSAP,
	double				xc,
	double				yc,
	double				zc) 
{
	_hoops_PAPPR context("Queue_Related_Selection");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Queue_Related_Selection (%S, ",pathname));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D), ", _hoops_HSICA));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", offset1, offset2));
		HI_Dump_Code (Sprintf_D (null, "%d, ", offset3));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", xw, yw));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", _hoops_RCSAP, xc));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", yc, zc));
	);


	HI_Queue_Related_Selection (
		context, pathname, _hoops_HSICA,
		offset1, offset2, offset3,
		xw, yw, _hoops_RCSAP,
		xc, yc, zc); 

#endif
}



HC_INTERFACE bool HC_CDECL HC_Find_Related_Selection (void) 
{
	_hoops_PAPPR context("Find_Related_Selection");

	CODE_GENERATION (
		HI_Dump_Code ("(void)HC_Find_Related_Selection ();\n");
	);

	Selection_Event *	_hoops_GPIIR;
	_hoops_RPIIR *	si;

	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null)
		return false;

	si = _hoops_GPIIR->_hoops_APIIR;

	if (si->next == null) {
		context->_hoops_PISHA = null;
		_hoops_HPRH (_hoops_GPIIR);
		return false;
	}
	else {
		_hoops_GPIIR->_hoops_APIIR = si->next;
		HI_Free_Selection_Item (si);
		return true;
	}
}





HC_INTERFACE void HC_CDECL HC_Show_Selection (
	char *		name) 
{
	_hoops_PAPPR context("Show_Selection");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection () */\n");
	);

	HI_Show_Selection (context, name, -1);
}


local void HI_Show_Selection_Pathname (
	_hoops_AIGPR *	_hoops_RIGC,
	char alter *			name,
	int						_hoops_SRPPH) 
{

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (_hoops_RIGC, _hoops_SAIIR)) == null) 
		return;

	if (BIT (_hoops_GPIIR->_hoops_APIIR->item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SELECTION, HES_DELETED_ITEM, "Can't 'Show' - the item has been deleted");
		return;
	}

	_hoops_CRCP const *			_hoops_SRCP;
	char					buf[10*_hoops_GHAPH];
	char alter *			_hoops_ASAPR;
	char const *			_hoops_PSAPR = buf + _hoops_GGAPR(buf);
	_hoops_RISAP const *	_hoops_HACAH;

	if (_hoops_GPIIR->_hoops_APIIR->item->type == _hoops_IRCP)
		_hoops_SRCP = (_hoops_CRCP const *)_hoops_GPIIR->_hoops_APIIR->item;
	else
		_hoops_SRCP = (_hoops_CRCP const *)_hoops_GPIIR->_hoops_APIIR->item->owner;

	_hoops_ASAPR = HI_Sprintf1 (buf, _hoops_PSAPR, "%p", (void *)_hoops_SRCP);

	if ((_hoops_HACAH = _hoops_GPIIR->_hoops_APIIR->_hoops_SISAP) != null) do {
		if (BIT (_hoops_HACAH->include->_hoops_RRHH, _hoops_HGAGR)) break; /*_hoops_IIP _hoops_IRIPR*/

		if (_hoops_HACAH->include->type == _hoops_AGRPR) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " <", null);

			if (!BIT (HOOPS_WORLD->system_flags, _hoops_SSCPP)) {
				_hoops_CRCP const *		_hoops_SIRPH = _hoops_HACAH->include->_hoops_IGRPR;

				while (_hoops_SRCP != _hoops_SIRPH) {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "<", null);
					if ((_hoops_SRCP = _hoops_SRCP->owner) == null) break;
				}
			}

			_hoops_SRCP = _hoops_HACAH->include->owner;
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %p", _hoops_SRCP);
		}
		else {	// _hoops_PIHA _hoops_SHH _hoops_IRS _hoops_CGRPR
			Key		_hoops_RCPPH = _hoops_AIRIR(_hoops_HACAH->include);

			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " < %k", &_hoops_RCPPH);

			_hoops_SRCP = _hoops_HACAH->include->owner;

			if (_hoops_HACAH->prev == null || _hoops_HACAH->prev->include->type == _hoops_AGRPR)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ":%p", _hoops_SRCP);
		}
	} while ((_hoops_HACAH = _hoops_HACAH->prev) !=	null);

	HI_Return_Chars (name, _hoops_SRPPH, buf, (int)(_hoops_ASAPR - buf));
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Selection_Pathname (
	char alter *			name) 
{
	_hoops_PAPPR context("Show_Selection_Pathname");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Pathname () */\n");
	);

	HI_Show_Selection_Pathname (context, name, -1);
}


HC_INTERFACE void HC_CDECL HC_Show_Selection_Item (
	Key *			key,
	int *			offset1,
	int *			offset2) 
{
	_hoops_PAPPR context("Show_Selection_Item");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Item () */\n");
	);

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null)
		return;

	_hoops_RPIIR *	si = _hoops_GPIIR->_hoops_APIIR;

	if (BIT (si->item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SELECTION, HES_DELETED_ITEM, "Can't 'Show' - the item has been deleted");
		return;
	}

	if (key)
		*key = si->_hoops_HSICA;
	if (offset1)
		*offset1 = si->offset1;
	if (offset2)
		*offset2 = si->offset2;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Selection_Source_Elem (
 	int *			offset1,
	int *			offset2,
	int *			offset3,
	Point alter *	_hoops_PAGR) 
{
	_hoops_PAPPR context("Show_Selection_Source_Element");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Source_Element () */\n");
	);

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null)
		return;

	_hoops_RPIIR *	si = _hoops_GPIIR->_hoops_APIIR;

	if (BIT (si->item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SELECTION, HES_DELETED_ITEM, "Can't 'Show' - the item has been deleted");
		return;
	}

 
	if (offset1)
		*offset1 = si->offset1;
	if (offset2)
		*offset2 = si->offset2;
	if (offset3)
		*offset3 = si->offset3;
	if (_hoops_PAGR && context->_hoops_SIPPH)
		*_hoops_PAGR = context->_hoops_SIPPH->hit_location;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Selection_Element (
	Key *			key,
	int *			offset1,
	int *			offset2,
	int *			offset3) 
{
	_hoops_PAPPR context("Show_Selection_Element");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Element () */\n");
	);

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null)
		return;

	_hoops_RPIIR *	si = _hoops_GPIIR->_hoops_APIIR;

	if (BIT (si->item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SELECTION, HES_DELETED_ITEM, "Can't 'Show' - the item has been deleted");
		return;
	}

	if (key)
		*key = si->_hoops_HSICA;
	if (offset1)
		*offset1 = si->offset1;
	if (offset2)
		*offset2 = si->offset2;
	if (offset3)
		*offset3 = si->offset3;
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Selection_Original_Key (
	Key *			key) 
{
	_hoops_PAPPR context("Show_Selection_Element");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Element () */\n");
	);

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null)
		return;

	_hoops_RPIIR *	si = _hoops_GPIIR->_hoops_APIIR;

	if (BIT (si->item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SELECTION, HES_DELETED_ITEM, "Can't 'Show' - the item has been deleted");
		return;
	}

	if (key)
		*key = si->_hoops_CISAP;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Selection_Elements (
	Key *			key,
	int *			count,
	int *			offset1,
	int *			offset2,
	int *			offset3) 
{
	_hoops_PAPPR context("Show_Selection_Elements");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Element () */\n");
	);

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null)
		return;

	_hoops_RPIIR *	si = _hoops_GPIIR->_hoops_APIIR;

	if (BIT (si->item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SELECTION, HES_DELETED_ITEM, "Can't 'Show' - the item has been deleted");
		return;
	}

	if (key)
		*key = si->_hoops_HSICA;

	if (count)
		*count = 0;

	_hoops_AISAP *	_hoops_ACSAP;

	if ((_hoops_ACSAP = si->_hoops_ACSAP) != null) do {
		if (count)
			++*count;
		if (offset1 != null)
			*offset1++ = _hoops_ACSAP->_hoops_PISAP[0];
		if (offset2 != null)
			*offset2++ = _hoops_ACSAP->_hoops_PISAP[1];
		if (offset3 != null)
			*offset3++ = _hoops_ACSAP->_hoops_PISAP[2];
	} while ((_hoops_ACSAP = _hoops_ACSAP->next) != null);
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Selection_Elements_Coun (
	Key *				key,
	int *				count) 
{
	_hoops_PAPPR context("Show_Selection_Element_Count");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Element () */\n");
	);

	*count=0;

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null)
		return;

	_hoops_RPIIR *	si = _hoops_GPIIR->_hoops_APIIR;

	if (BIT (si->item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SELECTION, HES_DELETED_ITEM, "Can't 'Show' - the item has been deleted");
		return;
	}

	if (key)
		*key = si->_hoops_HSICA;

	if (count) {
		*count = 0;
		_hoops_AISAP *	_hoops_ACSAP;
		if ((_hoops_ACSAP = si->_hoops_ACSAP) != null) {
			do {
				++*count;
			} while ((_hoops_ACSAP = _hoops_ACSAP->next) != null);
		}
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Selection_Location (
	float *				xw,
	float *				yw,
	float *				xc,
	float *				yc,
	float *				zc) 
{
	_hoops_PAPPR context("Show_Selection_Location");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Location () */\n");
	);

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null) 
		return;

	_hoops_RPIIR *	si = _hoops_GPIIR->_hoops_APIIR;

	if (xw)
		*xw = si->xw;
	if (yw)
		*yw = si->yw;
	if (xc)
		*xc = si->xc;
	if (yc)
		*yc = si->yc;
	if (zc)
		*zc = si->zc;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Selection_Position (
	float *			xw,
	float *			yw,
	float *			_hoops_RCSAP,
	float *			xc,
	float *			yc,
	float *			zc) 
{
	_hoops_PAPPR context("Show_Selection_Position");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Position () */\n");
	);

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null) 
		return;

	_hoops_RPIIR *	si = _hoops_GPIIR->_hoops_APIIR;

	if (xw)
		*xw = si->xw;
	if (yw)
		*yw = si->yw;
	if (_hoops_RCSAP)
		*_hoops_RCSAP = si->_hoops_RCSAP;
	if (xc)
		*xc = si->xc;
	if (yc)
		*yc = si->yc;
	if (zc)
		*zc = si->zc;
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Selection_Source (
	char *		locater,
	char *		picture,
	char *		action,
	int *		status) 
{
	_hoops_PAPPR context("Show_Selection_Source");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Source () */\n");
	);

	HI_Show_Selection_Source (context, locater, -1, picture, -1, action, -1, status);
}


/* _hoops_CCAH _hoops_SICAR */
HC_INTERFACE void HC_CDECL HC_Show_Selection_Keys (
	int *				count,
	Key *				_hoops_ACPPH) 
{
	_hoops_PAPPR context("Show_Selection_Keys");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Keys () */\n");
	);

	if (!count || !_hoops_ACPPH) {
		HE_ERROR (HEC_SELECTION, HES_NULL_INPUT, "HC_Show_Selection_Keys cannot accept null input");
		return;
	}

	*count = 0;			/* _hoops_SHIR _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_RIHH */

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null)
		return;

	if (BIT (_hoops_GPIIR->_hoops_APIIR->item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SELECTION, HES_DELETED_ITEM, "Can't 'Show' - the item has been deleted");
		return;
	}

	_hoops_CRCP *		_hoops_SRCP;
	Key *			keys = _hoops_ACPPH;
	_hoops_RISAP *	_hoops_HACAH;

	
	if (_hoops_GPIIR->_hoops_APIIR->item->type == _hoops_IRCP)
		_hoops_SRCP = (_hoops_CRCP *)_hoops_GPIIR->_hoops_APIIR->item;
	else {
		*keys++ = _hoops_GPIIR->_hoops_APIIR->_hoops_HSICA;
		_hoops_SRCP = (_hoops_CRCP *)_hoops_GPIIR->_hoops_APIIR->item->owner;
	}

	if ((_hoops_HACAH = _hoops_GPIIR->_hoops_APIIR->_hoops_SISAP) != null)  {
		while (_hoops_HACAH->include->type == _hoops_AHIP) {
			*keys++ = _hoops_HACAH->include->key;	/* _hoops_RH _hoops_CGRPR */
			_hoops_SRCP = _hoops_HACAH->include->owner;
			if ((_hoops_HACAH = _hoops_HACAH->prev) == null)
				break;
		}
		if (_hoops_HACAH != null) do {
			_hoops_CRCP *		_hoops_SIRPH;

			if (BIT (_hoops_HACAH->include->_hoops_RRHH, _hoops_HGAGR)) return;	/* _hoops_CRAA _hoops_PPRGA */

			_hoops_SIRPH = (_hoops_CRCP alter *)_hoops_HACAH->include->_hoops_IGRPR;

			if (_hoops_SRCP != _hoops_SIRPH) do {
				if (_hoops_SRCP->owner->type == _hoops_PRAIR) return; /* _hoops_SR _hoops_GGHP _hoops_CISS _hoops_GSPCA */

				*keys++ = _hoops_SRCP->key;		/* _hoops_GH _hoops_IS _hoops_RH _hoops_PGPAA _hoops_CAGH */
			} while ((_hoops_SRCP = _hoops_SRCP->owner) != _hoops_SIRPH);

			*keys++ = _hoops_SRCP->key;			/* _hoops_RH _hoops_SPR _hoops_PGPAA */
			*keys++ = _hoops_HACAH->include->key;	/* _hoops_RH _hoops_GCIS _hoops_ACAS */

			_hoops_SRCP = _hoops_HACAH->include->owner;
		} while ((_hoops_HACAH = _hoops_HACAH->prev) != null);
	}


	if (_hoops_GPIIR->target != null && _hoops_SRCP != _hoops_GPIIR->target->owner) do {
		if (_hoops_SRCP->owner->type == _hoops_PRAIR) return; /* _hoops_SR _hoops_GGHP _hoops_CISS _hoops_GSPCA */

		*keys++ = _hoops_SRCP->key;
	} while ((_hoops_SRCP = _hoops_SRCP->owner) != _hoops_GPIIR->target->owner);

	*keys++ = _hoops_SRCP->key;				/* _hoops_PPR _hoops_HA _hoops_RH _hoops_RHPP _hoops_CAGH... */

	_hoops_SRCP = _hoops_SRCP->owner;					/* _hoops_PPR _hoops_GH _hoops_RHIR _hoops_RH _hoops_SRRPR */
	while (_hoops_SRCP->type != _hoops_PRAIR) {
		*keys++ = _hoops_SRCP->key;
		_hoops_SRCP = _hoops_SRCP->owner;
	}

	*count = keys - _hoops_ACPPH;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Selection_Original_Keys (
	int *				count,
	Key *				_hoops_ACPPH) 
{
	_hoops_PAPPR context("Show_Selection_Original_Keys");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Original_Keys () */\n");
	);

	if (!_hoops_ACPPH) {
		HE_ERROR (HEC_SELECTION, HES_NULL_INPUT, "HC_Show_Selection_Original_Keys cannot accept null input");
		return;
	}

	if(count)
		*count = 0;			/* _hoops_SHIR _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_RIHH */

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null)
		return;

	if (BIT (_hoops_GPIIR->_hoops_APIIR->item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SELECTION, HES_DELETED_ITEM, "Can't 'Show' - the item has been deleted");
		return;
	}

	_hoops_CRCP *			_hoops_SRCP;
	Key *				keys = _hoops_ACPPH;
	_hoops_RISAP *		_hoops_HACAH;

	if (_hoops_GPIIR->_hoops_APIIR->item->type == _hoops_IRCP)
		_hoops_SRCP = (_hoops_CRCP *)_hoops_GPIIR->_hoops_APIIR->item;
	else {
		*keys++ = _hoops_GPIIR->_hoops_APIIR->_hoops_HSICA;//_hoops_PCPPH(_hoops_HCPPH->_hoops_ICPPH->_hoops_IGCI);
		_hoops_SRCP = (_hoops_CRCP *)_hoops_GPIIR->_hoops_APIIR->item->owner;
	}

	if ((_hoops_HACAH = _hoops_GPIIR->_hoops_APIIR->_hoops_SISAP) != null)  {
		while (_hoops_HACAH->include->type == _hoops_AHIP) {
			*keys++ = _hoops_AIRIR(_hoops_HACAH->include);	/* _hoops_RH _hoops_CGRPR */
			_hoops_SRCP = _hoops_HACAH->include->owner;
			if ((_hoops_HACAH = _hoops_HACAH->prev) == null)
				break;
		}
		if (_hoops_HACAH != null) do {
			_hoops_CRCP *		_hoops_SIRPH;

			if (BIT (_hoops_HACAH->include->_hoops_RRHH, _hoops_HGAGR)) return;	/* _hoops_CRAA _hoops_PPRGA */

			_hoops_SIRPH = (_hoops_CRCP alter *)_hoops_HACAH->include->_hoops_IGRPR;

			if (_hoops_SRCP != _hoops_SIRPH) do {
				if (_hoops_SRCP->owner->type == _hoops_PRAIR) return; /* _hoops_SR _hoops_GGHP _hoops_CISS _hoops_GSPCA */

				*keys++ = _hoops_AIRIR(_hoops_SRCP);		/* _hoops_GH _hoops_IS _hoops_RH _hoops_PGPAA _hoops_CAGH */
			} while ((_hoops_SRCP = _hoops_SRCP->owner) != _hoops_SIRPH);

			*keys++ = _hoops_AIRIR(_hoops_SRCP);			/* _hoops_RH _hoops_SPR _hoops_PGPAA */
			*keys++ = _hoops_AIRIR(_hoops_HACAH->include);	/* _hoops_RH _hoops_GCIS _hoops_ACAS */

			_hoops_SRCP = _hoops_HACAH->include->owner;
		} while ((_hoops_HACAH = _hoops_HACAH->prev) != null);
	}


	if (_hoops_GPIIR->target != null && _hoops_SRCP != _hoops_GPIIR->target->owner) do {
		if (_hoops_SRCP->owner->type == _hoops_PRAIR) return; /* _hoops_SR _hoops_GGHP _hoops_CISS _hoops_GSPCA */

		*keys++ = _hoops_AIRIR(_hoops_SRCP);
	} while ((_hoops_SRCP = _hoops_SRCP->owner) != _hoops_GPIIR->target->owner);

	*keys++ = _hoops_AIRIR(_hoops_SRCP);				/* _hoops_PPR _hoops_HA _hoops_RH _hoops_RHPP _hoops_CAGH... */

	_hoops_SRCP = _hoops_SRCP->owner;					/* _hoops_PPR _hoops_GH _hoops_RHIR _hoops_RH _hoops_SRRPR */
	while (_hoops_SRCP->type != _hoops_PRAIR) {
		*keys++ = _hoops_AIRIR(_hoops_SRCP);
		_hoops_SRCP = _hoops_SRCP->owner;
	}

	if(count)
		*count = keys - _hoops_ACPPH;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Selection_Keys_Count (
	int *				count) 
{
	_hoops_PAPPR context("Show_Selection_Keys_Count");

#ifdef DISABLE_SELECTION
	_hoops_IRPPR ("Selection");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Selection_Keys_Count () */\n");
	);

	if (!count) {
		HE_ERROR (HEC_SELECTION, HES_NULL_INPUT,
				"HC_Show_Selection_Keys_Count cannot accept null input");
		return;
	}

	*count = 0;			/* _hoops_SHIR _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_HHGS */

	Selection_Event *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (Selection_Event *)HI_Current_Event (context, _hoops_SAIIR)) == null) 
		return;

	if (BIT (_hoops_GPIIR->_hoops_APIIR->item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SELECTION, HES_DELETED_ITEM, "Can't 'Show' - the item has been deleted");
		return;
	}
	
	_hoops_CRCP *			_hoops_SRCP;
	_hoops_RISAP *		_hoops_HACAH;
	int					keys = 0;

	if (_hoops_GPIIR->_hoops_APIIR->item->type == _hoops_IRCP)
		_hoops_SRCP = (_hoops_CRCP *)_hoops_GPIIR->_hoops_APIIR->item;
	else {
		++keys;
		_hoops_SRCP = (_hoops_CRCP *)_hoops_GPIIR->_hoops_APIIR->item->owner;
	}

	if ((_hoops_HACAH = _hoops_GPIIR->_hoops_APIIR->_hoops_SISAP) != null) {
		while (_hoops_HACAH->include->type == _hoops_AHIP) {
			++keys;	/* _hoops_RH _hoops_CGRPR */
			_hoops_SRCP = _hoops_HACAH->include->owner;
			if ((_hoops_HACAH = _hoops_HACAH->prev) == null)
				break;
		}
		if (_hoops_HACAH != null) do {
			_hoops_CRCP				*_hoops_SIRPH;

			if (BIT (_hoops_HACAH->include->_hoops_RRHH, _hoops_HGAGR))
				return;	/* _hoops_CRAA _hoops_PPRGA */

			_hoops_SIRPH = (_hoops_CRCP alter *)_hoops_HACAH->include->_hoops_IGRPR;

			if (_hoops_SRCP != _hoops_SIRPH) do {
				if (_hoops_SRCP->owner->type == _hoops_PRAIR) 
					return; /* _hoops_SR _hoops_GGHP _hoops_CISS _hoops_GSPCA */

				++keys;		/* _hoops_GH _hoops_IS _hoops_RH _hoops_PGPAA _hoops_CAGH */
			} while ((_hoops_SRCP = _hoops_SRCP->owner) != _hoops_SIRPH);

			keys += 2;		 /* _hoops_RH _hoops_SPR _hoops_PGPAA, & _hoops_RH _hoops_GCIS _hoops_ACAS */

			_hoops_SRCP = _hoops_HACAH->include->owner;
		} while ((_hoops_HACAH = _hoops_HACAH->prev) != null);
	}


	if (_hoops_GPIIR->target != null && _hoops_SRCP != _hoops_GPIIR->target->owner) do {
		if (_hoops_SRCP->owner->type == _hoops_PRAIR) 
			return; /* _hoops_SR _hoops_GGHP _hoops_CISS _hoops_GSPCA */

		++keys;			/* _hoops_GH _hoops_IS _hoops_RH _hoops_RHPP */
	} while ((_hoops_SRCP = _hoops_SRCP->owner) != _hoops_GPIIR->target->owner);

	++keys;								/* _hoops_PPR _hoops_HA _hoops_RH _hoops_RHPP _hoops_CAGH... */

	_hoops_SRCP = _hoops_SRCP->owner;					/* _hoops_PPR _hoops_GH _hoops_RHIR _hoops_RH _hoops_SRRPR */
	while (_hoops_SRCP->type != _hoops_PRAIR) {
		++keys;
		_hoops_SRCP = _hoops_SRCP->owner;
	}

	*count = keys;
#endif
}




HC_INTERFACE void HC_CDECL HC_Enable_String_Events (
	char const *		_hoops_IRPPH,
	Key					_hoops_CCPPH) 
{
	_hoops_PAPPR context("Enable_String_Events");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Enable_String_Events (%S, ",
		_hoops_IRPPH));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D));\n", _hoops_CCPPH));
	);

	// _hoops_ASIGA _hoops_CSPIP _hoops_HCAPH

	_hoops_GGAGR *		keyboard;
	if ((keyboard = HI_Force_Find_Driver (context, _hoops_IRPPH)) == null) 
		return;

	if (_hoops_CCPPH == 0) 
		++keyboard->_hoops_RCSHR._hoops_SPIAP;
	else {

		_hoops_PIGPR *	cursor = (_hoops_PIGPR *)_hoops_RCSSR (context, _hoops_CCPPH);

		if (cursor == null || cursor->type != HK_STRING_CURSOR || BIT (cursor->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_STRING_EVENT, HES_INVALID_STRING_CURSOR, "Provided key does not refer to a valid String Cursor");
			return;
		}

		if (keyboard->_hoops_RCSHR._hoops_SRPIR != null && keyboard->_hoops_RCSHR._hoops_SRPIR != cursor) {
			HE_ERROR2 (HEC_STRING_EVENT, HES_CURSOR_ALREADY_PRESENT,
				Sprintf_P (null,"Keyboard '%p' already has a (different) string cursor attached -", keyboard->owner), 
				"Only one at a time is allowed");
			return;
		}

		++keyboard->_hoops_RCSHR._hoops_SPIAP;
		++keyboard->_hoops_RCSHR._hoops_GHIAP;

		if (keyboard->_hoops_RCSHR._hoops_SRPIR == null) {
			keyboard->_hoops_RCSHR._hoops_SRPIR = cursor;
			++cursor->_hoops_HIHI;
		}
	}

	keyboard->_hoops_CGPIR |= _hoops_PARPH;
	HOOPS_WORLD->_hoops_AARPH = true;
#endif
}


HC_INTERFACE void HC_CDECL HC_Disable_String_Events (
	char const *		_hoops_IRPPH,
	Key					_hoops_CCPPH) 
{
	_hoops_PAPPR context("Disable_String_Events");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Disable_String_Events (%S, ", _hoops_IRPPH));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D));\n", _hoops_CCPPH));
	);

	// _hoops_ASIGA _hoops_CSPIP _hoops_HCAPH

	_hoops_GGAGR *		keyboard;
	if ((keyboard = HI_Force_Find_Driver (context, _hoops_IRPPH)) == null) 
		return;

	if (_hoops_CCPPH != 0) {
		_hoops_PIGPR *	cursor = (_hoops_PIGPR *)_hoops_RCSSR (context, _hoops_CCPPH);

		if (cursor == null || cursor->type != HK_STRING_CURSOR || BIT (cursor->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_STRING_EVENT, HES_INVALID_KEY, "Provided key does not refer to a valid String Cursor");
			return;
		}

		if (keyboard->_hoops_RCSHR._hoops_SRPIR == null) {
			HE_WARNING (HEC_STRING_EVENT, HES_STRING_CURSOR_DISABLED,
				Sprintf_P (null, "The string cursor on keyboard '%p' is already fully disabled", keyboard->owner));
		}
		else if (keyboard->_hoops_RCSHR._hoops_SRPIR != cursor) {
			_hoops_PHPGR (HEC_STRING_EVENT, HES_STRING_CURSOR_MISMATCH,
				Sprintf_P (null, "Keyboard '%p' has a string cursor attached -", keyboard->owner),
				"It does not match the one that was specified");
		}
		else if (--keyboard->_hoops_RCSHR._hoops_GHIAP == 0) {
			keyboard->_hoops_RCSHR._hoops_SRPIR = null;
			_hoops_HPRH (cursor);
			if (keyboard->_hoops_PHIAP) {
				_hoops_PRPIR(keyboard->_hoops_PHIAP->string);
				FREE(keyboard->_hoops_PHIAP, _hoops_RRPIR);
				keyboard->_hoops_PHIAP = null;
			}
		}
	}

	if (keyboard->_hoops_RCSHR._hoops_SPIAP == 0) {
		_hoops_PHPGR (HEC_STRING_EVENT, HES_STRING_CURSOR_DISABLED,
			Sprintf_P (null, "Cannot disable string events on '%p' -", keyboard->owner),
			"They are already fully disabled");
	}
	else {
		--keyboard->_hoops_RCSHR._hoops_SPIAP;
		keyboard->_hoops_CGPIR |= _hoops_PARPH;
		HOOPS_WORLD->_hoops_AARPH = true;
	}
#endif
}




local void HI_Show_String (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					name,
	int						_hoops_SRPPH) 
{
#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	_hoops_AHIIR *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (_hoops_AHIIR *)HI_Current_Event (_hoops_RIGC, _hoops_RHIIR)) == null)
		return;

	HI_Return_Kars (name, _hoops_SRPPH, _hoops_GPIIR->string._hoops_IPPPP, _hoops_GPIIR->string.length, _hoops_GPIIR->encoding);
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_String (
	char *		name) 
{
	_hoops_PAPPR context("Show_String");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_String () */\n");
	);

	HI_Show_String (context, name, -1);
}


local void HI_Show_String_Source (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					path,
	int						_hoops_APAPH,
	Key *					cursor) 
{

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	_hoops_AHIIR *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (_hoops_AHIIR *)HI_Current_Event (_hoops_RIGC, _hoops_RHIIR)) == null) 
		return;

	if (BIT (_hoops_GPIIR->source->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_EVENT_HANDLER, HES_DELETED_KEYBOARD, "Can't 'Show' - the 'keyboard' has been deleted");
		return;
	}

	char			buf[MAX_ERRMSG];
	char *	_hoops_IPAPH = HI_Sprintf1 (buf, buf+_hoops_GGAPR(buf), "%p", (void *)_hoops_GPIIR->source->owner);
	HI_Return_Chars (path, _hoops_APAPH, buf, (int)(_hoops_IPAPH - buf));

	if (_hoops_GPIIR->source->_hoops_CPCR._hoops_SRPIR == null)
		*cursor = 0;
	else
		*cursor = _hoops_GPIIR->source->_hoops_CPCR._hoops_SRPIR->key;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_String_Source (
	char *		path,
	Key *		cursor) 
{
	_hoops_PAPPR context("Show_String_Source");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_String_Source () */\n");
	);

	HI_Show_String_Source (context, path, -1, cursor);
}



local void HI_Show_String_With_Encoding (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					encoding,
	int						_hoops_SCPPH,
	void *					name,
	int						_hoops_SRPPH) 
{

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	_hoops_AHIIR *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (_hoops_AHIIR *)HI_Current_Event (_hoops_RIGC, _hoops_RHIIR)) == null) 
		return;

	HI_Return_Kars ((char*)name, _hoops_SRPPH, _hoops_GPIIR->string._hoops_IPPPP, _hoops_GPIIR->string.length, _hoops_GPIIR->encoding);
	HI_Show_Encoding_Type (encoding, _hoops_SCPPH, _hoops_GPIIR->encoding);
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_String_With_Encoding (
	char *		encoding,
	void *		name) 
{
	_hoops_PAPPR context("Show_String_With_Encoding");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_String_With_Encoding () */\n");
	);

	HI_Show_String_With_Encoding (context, encoding, -1, name, -1);
}


HC_INTERFACE void HC_CDECL HC_Show_String_Count (
	int *		count) 
{
	_hoops_PAPPR context("Show_String_Count");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_String_Count () */\n");
	);

	_hoops_AHIIR *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (_hoops_AHIIR *)HI_Current_Event (context, _hoops_RHIIR)) == null) 
		return;

	*count = _hoops_GPIIR->string.length;			
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_String_Length (
	int *		length) 
{
	_hoops_PAPPR context("Show_String_Length");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_String_Length () */\n");
	);

	_hoops_AHIIR *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (_hoops_AHIIR *)HI_Current_Event (context, _hoops_RHIIR)) == null) 
		return;

	/* _hoops_CGIC _hoops_PHI _hoops_IIGR _hoops_GCSRR _hoops_RGHP */

	switch (_hoops_GPIIR->encoding) {
		case _hoops_SSAIP:
			*length = _hoops_GPIIR->string.length;		
		break;

		case _hoops_GSPPH:{
			H_UTF16 _hoops_RSPPH;
			_hoops_RSPPH.encodedText((utf16_char const*)_hoops_GPIIR->string._hoops_IPPPP);
			H_UTF8 _hoops_ASPPH(_hoops_RSPPH);
			utf8_char const * _hoops_PSPPH = _hoops_ASPPH.encodedText();
			while(*_hoops_PSPPH != 0) ++_hoops_PSPPH;
			*length = _hoops_PSPPH - _hoops_ASPPH.encodedText();
		} break;

		case _hoops_HSPPH:{
			H_UTF16 _hoops_RSPPH;
			_hoops_RSPPH.encodedText((utf16_char const*)_hoops_GPIIR->string._hoops_IPPPP);
			H_UTF32 _hoops_ISPPH(_hoops_RSPPH);
			utf32_char const * _hoops_PSPPH = _hoops_ISPPH.encodedText();
			while(*_hoops_PSPPH != 0) ++_hoops_PSPPH;
			*length = (int)(sizeof(utf32_char) * (_hoops_PSPPH - _hoops_ISPPH.encodedText()));
		} break;

		case _hoops_CSPPH:
		case _hoops_SSPPH:{
			H_UTF16 _hoops_RSPPH;
			_hoops_RSPPH.encodedText((utf16_char const*)_hoops_GPIIR->string._hoops_IPPPP);
			H_WCS _hoops_GGHPH(_hoops_RSPPH);
			wchar_t const * _hoops_PSPPH = _hoops_GGHPH.encodedText();
			while(*_hoops_PSPPH != L'\0') ++_hoops_PSPPH;
			*length = (int)(sizeof(wchar_t) * (_hoops_PSPPH - _hoops_GGHPH.encodedText()));
		} break;

		case _hoops_RGHPH:
		case _hoops_AGHPH:
		case _hoops_SACSR:		*length = 2 * _hoops_GPIIR->string.length; break;

		default: {		/* _hoops_AA _hoops_SCH _hoops_RH _hoops_ACIPR _hoops_PPRRR */
			Karacter		*_hoops_IHSCP = _hoops_GPIIR->string._hoops_IPPPP;
			int				count = _hoops_GPIIR->string.length;

			*length = 0;
			while (count-- > 0) {
				if ((*_hoops_IHSCP++ & 0xFF00) != 0)
					*length += 2;
				else
					(*length)++;
			}
		}	break;
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Queue_String_Event (
	char const *	_hoops_HAPPH,
	char const *	string,
	Key				cursor_key) 
{
	_hoops_PAPPR context("Queue_String_Event");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Queue_String_Event (%S, %S, ", _hoops_HAPPH, string));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D));\n", cursor_key));
	);

	// _hoops_ASIGA _hoops_CSPIP _hoops_HCAPH

	_hoops_GGAGR *	source;
	if ((source = HI_Force_Find_Driver (context, _hoops_HAPPH)) == null) 
		return;

	if (HOOPS_WORLD->_hoops_AARPH) 
		HI_Update_Events (context);

	if (source->_hoops_CPCR._hoops_SPIAP <= 0) {
		HE_WARNING (HEC_EVENT_HANDLER, HES_STRING_EVENT_NOT_ENABLED,
			Sprintf_P (null, "String events are not enabled on '%p'", source->owner));
		return;
	}

	if (cursor_key != 0l) {
		_hoops_PIGPR *	cursor = (_hoops_PIGPR *)_hoops_RCSSR (context, cursor_key);
		if (cursor == null || cursor->type != HK_STRING_CURSOR || BIT (cursor->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_EVENT_HANDLER, HES_INVALID_KEY, "The provided key does not refer to a valid String Cursor");
			return;
		}

		if (cursor != source->_hoops_CPCR._hoops_SRPIR) {
			HE_ERROR (HEC_EVENT_HANDLER, HES_STRING_EVENT_NOT_ENABLED, "The specified string cursor has not had string events enabled");
			return;
		}
	}


	_hoops_AHIIR *	_hoops_GPIIR;
	ZALLOC (_hoops_GPIIR, _hoops_AHIIR);
	_hoops_GPIIR->owner = HOOPS_WORLD;
	_hoops_GPIIR->_hoops_HIHI = 1;
	_hoops_GPIIR->type = _hoops_RHIIR;
	_hoops_GPIIR->_hoops_PHSHA = HI_What_Time();
	_hoops_GPIIR->encoding = HOOPS_WORLD->encoding;

	_hoops_GPIIR->source = source;
	_hoops_PRRH (source);

	HI_Convert_Char_To_KName (string, &_hoops_GPIIR->string, HOOPS_WORLD->encoding);

	if (context->_hoops_PCRPH == null) {
		context->_hoops_PAARH = (_hoops_HISHA *)_hoops_GPIIR;
		_hoops_GPIIR->backlink = &context->_hoops_PAARH;
	}
	else {
		context->_hoops_PCRPH->next = (_hoops_HISHA *)_hoops_GPIIR;
		_hoops_GPIIR->backlink = &context->_hoops_PCRPH->next;
		_hoops_HPRH (context->_hoops_PCRPH);
	}

	context->_hoops_PCRPH = (_hoops_HISHA *)_hoops_GPIIR;
	_hoops_PRRH (_hoops_GPIIR);

	if (_hoops_GPIIR->string.length > 0) {
		if ((source->_hoops_ARPIR == null ||
			!_hoops_RARPH (_hoops_GPIIR->string, source->_hoops_ARPIR->string) != 0) &&
			HOOPS_WORLD->_hoops_PRGHP > 0) {

			_hoops_RRPIR	*	sl;
			ZALLOC (sl, _hoops_RRPIR);
			if ((sl->prev = source->_hoops_ARPIR) != null)
				sl->prev->next = sl;
			sl->next = null;
			source->_hoops_ARPIR = sl;

			HI_Copy_KName (&_hoops_GPIIR->string, &sl->string);

			if (source->_hoops_HHIAP < HOOPS_WORLD->_hoops_PRGHP)
				++source->_hoops_HHIAP;
			else {
				sl = source->_hoops_ARPIR;
				_hoops_RGGA (sl->prev == null) sl = sl->prev;
				sl->next->prev = null;
				_hoops_PRPIR (sl->string);
				FREE (sl, _hoops_RRPIR);
			}
		}
	}
#endif
}



local void HI_Get_String_With_Encoding (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_PGHPH,
	char const *			encoding,
	void *					string,
	int						_hoops_HGHPH) 
{
#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	char	_hoops_RHAPH[20];

	PUSHNAME(_hoops_RIGC);
	HC_Open_Segment (_hoops_PGHPH);
	Key	_hoops_IGHPH = HC_Insert_Text_With_Encoding (0.0, 0.0, 0.0, encoding, "\0\0");
	Key	_hoops_CGHPH = HC_Insert_String_Cursor (_hoops_IGHPH, 0, 0);
	HC_Enable_String_Events ("?Keyboard", _hoops_CGHPH);
	do {
		_hoops_RHAPH[1] = 't';		/* _hoops_GGR _hoops_AGIR _hoops_RH _hoops_IAAPH _hoops_ISHS */
		HI_Await_Event (_hoops_RIGC, _hoops_RHAPH, _hoops_GGAPR(_hoops_RHAPH));
		if (_hoops_RHAPH[0] == 'n') /* _hoops_PIRC */
			HI_Exit_Program();
	} _hoops_RGGA (_hoops_RHAPH[1] == 't');
	HC_Disable_String_Events ("?Keyboard", _hoops_CGHPH);
	HC_Delete_By_Key (_hoops_IGHPH);  /* (_hoops_SGHPH _hoops_HASRH _hoops_HAH) */
	HC_Close_Segment ();

	char	_hoops_HCIS[30];
	HI_Show_String_With_Encoding (_hoops_RIGC, _hoops_HCIS, sizeof(_hoops_HCIS), string, _hoops_HGHPH);
	POPNAME(_hoops_RIGC);
#endif
}


HC_INTERFACE void HC_CDECL HC_Get_String_With_Encoding (
	char const *	_hoops_PGHPH,
	char const *	encoding,
	void *			string) 
{
	_hoops_PAPPR context("Get_String_With_Encoding");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Get_String_With_Encoding (%S, %S, string_buffer);\n",_hoops_PGHPH, encoding));
	);

	HI_Get_String_With_Encoding (context, _hoops_PGHPH, encoding, string, -1);
}



local void HI_Get_String (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_PGHPH,
	char *					string,
	int						_hoops_HGHPH) 
{

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	char			_hoops_RHAPH[20];
	Key			_hoops_IGHPH, _hoops_CGHPH;

	PUSHNAME(_hoops_RIGC);
	HC_Open_Segment (_hoops_PGHPH);
	_hoops_IGHPH = HC_Insert_Text (0.0, 0.0, 0.0, "");
	_hoops_CGHPH = HC_Insert_String_Cursor (_hoops_IGHPH, 0, 0);
	HC_Enable_String_Events ("?Keyboard", _hoops_CGHPH);
	do {
		_hoops_RHAPH[1] = 't';		/* _hoops_GGR _hoops_AGIR _hoops_RH _hoops_IAAPH _hoops_ISHS */
		HI_Await_Event (_hoops_RIGC, _hoops_RHAPH, _hoops_GGAPR(_hoops_RHAPH));

		if (_hoops_RHAPH[0] == 'n') /* _hoops_PIRC */
			HI_Exit_Program();
	} _hoops_RGGA (_hoops_RHAPH[1] == 't');
	HC_Disable_String_Events ("?Keyboard", _hoops_CGHPH);
	HC_Delete_By_Key (_hoops_IGHPH);  /* (_hoops_SGHPH _hoops_HASRH _hoops_HAH) */
	HC_Close_Segment ();
	HI_Show_String (_hoops_RIGC, string, _hoops_HGHPH);
	POPNAME(_hoops_RIGC);
#endif
}


HC_INTERFACE void HC_CDECL HC_Get_String (
	char const *	_hoops_PGHPH,
	char *			string) 
{
	_hoops_PAPPR context("Get_String");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Get_String (%S, string_buffer);\n",_hoops_PGHPH));
	);

	HI_Get_String (context, _hoops_PGHPH, string, -1);
}



#ifndef DISABLE_EVENTS

local void _hoops_GRHPH (
				 _hoops_AIGPR *	_hoops_RIGC,
				 _hoops_GGAGR *				driver,
				 int						offset,
				 int						ndelete,
				 int						_hoops_RRHPH,
				 Karacter *				_hoops_IPPPP,
				 int						cursor,
				 _hoops_IHGRP			encoding) {

					 UNREFERENCED (encoding);

					 if (driver->_hoops_CPCR._hoops_SRPIR != null) {
						 _hoops_HACC			*owner;

						 owner = (_hoops_HACC *)driver->_hoops_CPCR._hoops_SRPIR->owner;

						 if (_hoops_RRHPH > 0) {
							 HI_Edit_Text (_hoops_RIGC, owner, 0, offset, 0, ndelete, _hoops_RRHPH, _hoops_IPPPP);
						 }
						 else if (ndelete > 0) {
							 HI_Edit_Text (_hoops_RIGC, owner, 0, offset, 0, ndelete, 0, null);
						 }

						 PUSHNAME(_hoops_RIGC);
						 HC_Move_String_Cursor (_hoops_AIRIR (driver->_hoops_CPCR._hoops_SRPIR),
							 0, cursor);
						 POPNAME(_hoops_RIGC);
					 }

					 if (ndelete > 0 || _hoops_RRHPH > 0) {
						 int				count;

						 count = driver->_hoops_HRPIR.length - ndelete + _hoops_RRHPH;

						 if (count == 0) {
							 _hoops_PRPIR (driver->_hoops_HRPIR);

							 driver->_hoops_HRPIR.length = 0;
							 driver->_hoops_HRPIR._hoops_IPPPP = null;
						 }
						 else {
							 Karacter		*in, *_hoops_PAGR;
							 int				_hoops_ARHPH;

							 _hoops_ARHPH = count;
							 ALLOC_ARRAY (_hoops_PAGR, count+1, Karacter);
							 count = _hoops_ARHPH;
							 in = driver->_hoops_HRPIR._hoops_IPPPP;

							 if (offset > 0) {
								 count -= offset;
								 do *_hoops_PAGR++ = *in++;
								 _hoops_RGGA (--offset == 0);
							 }

							 in += ndelete;

							 if (_hoops_RRHPH > 0) {
								 count -= _hoops_RRHPH;
								 do *_hoops_PAGR++ = *_hoops_IPPPP++;
								 _hoops_RGGA (--_hoops_RRHPH == 0);
							 }

							 if (count > 0) {
								 do *_hoops_PAGR++ = *in++;
								 _hoops_RGGA (--count == 0);
							 }
							 *_hoops_PAGR = 0;

							 _hoops_PRPIR (driver->_hoops_HRPIR);

							 driver->_hoops_HRPIR.length = _hoops_ARHPH;
							 driver->_hoops_HRPIR._hoops_IPPPP = _hoops_PAGR - _hoops_ARHPH;
						 }
					 }
					 driver->_hoops_RHIAP = cursor;
}
#endif

GLOBAL_FUNCTION void HI_Edit_Karacters (
										_hoops_AIGPR *	_hoops_RIGC,
										_hoops_GGAGR *				source,
										Button					key,
										_hoops_IHGRP			_hoops_PRHPH) {
#ifndef DISABLE_EVENTS
											_hoops_IHGRP			_hoops_HRHPH = (_hoops_IHGRP)0;
											_hoops_RRPIR *			sl;

											if (source->_hoops_CPCR._hoops_SRPIR != null) {
												_hoops_PIGPR		*cursor = source->_hoops_CPCR._hoops_SRPIR;
												_hoops_HACC			*text = (_hoops_HACC *)cursor->owner;

												_hoops_HRHPH = text->encoding;

												if (BIT (cursor->_hoops_RRHH, _hoops_HGAGR)) {
													/* (_hoops_PIP: _hoops_RPP _hoops_RH _hoops_HCGR _hoops_HRGR _hoops_IRHPH, _hoops_RH _hoops_HASRH _hoops_GRS _hoops_SHH _hoops_HAH) */
													HE_WARNING (HEC_STRING_EVENT, HES_CURSOR_DELETED,
														"String cursor was ndeleted while string events were enabled");

													_hoops_HPRH (source->_hoops_CPCR._hoops_SRPIR);
													source->_hoops_CPCR._hoops_SRPIR = null;
													source->_hoops_CPCR._hoops_SPIAP -= source->_hoops_CPCR._hoops_GHIAP;
													source->_hoops_CPCR._hoops_GHIAP = 0;

													if (source->_hoops_CPCR._hoops_SPIAP == 0) { /* _hoops_SR'_hoops_ASAR _hoops_CRHPH */
														/* _hoops_CRGS _hoops_GSPCR _hoops_SHS _hoops_IS _hoops_RRS _hoops_SRHPH _hoops_HPGR _hoops_IHHH */
														source->_hoops_CGPIR |= _hoops_PARPH;
														HOOPS_WORLD->_hoops_AARPH = true;
														return;
													}
												}
												else {
													KName				_hoops_GAHPH;
													_hoops_GAHPH.length = text->count;
													_hoops_GAHPH._hoops_IPPPP = text->karacters;

													/* _hoops_IRHH _hoops_RAHPH _hoops_RCRR _hoops_RHPP _hoops_PPR _hoops_HCGR/_hoops_HASRH _hoops_CHR _hoops_GGR _hoops_CAPRH... */
													if (!_hoops_RARPH (source->_hoops_HRPIR, _hoops_GAHPH)) {
														_hoops_PRPIR (source->_hoops_HRPIR);

														HI_Copy_KName (&_hoops_GAHPH, &source->_hoops_HRPIR);
													}
													source->_hoops_RHIAP = cursor->column;
													{
														int		row = cursor->row;
														while (row > 0)
															source->_hoops_RHIAP += text->_hoops_ICI[--row] + 1;
													}
												}
											}

											switch (key) {
		case _hoops_AAHPH ('M'): {
			_hoops_AHIIR			*_hoops_GPIIR;

			if (source->_hoops_HIIAP != 0)
				_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 1, 0,
				null, source->_hoops_RHIAP, _hoops_HRHPH);
			source->_hoops_PIIAP = source->_hoops_HIIAP = 0;

			ZALLOC (_hoops_GPIIR, _hoops_AHIIR);
			_hoops_GPIIR->owner = HOOPS_WORLD;
			_hoops_GPIIR->_hoops_HIHI = 1;
			_hoops_GPIIR->type = _hoops_RHIIR;
			_hoops_GPIIR->_hoops_PHSHA = HI_What_Time();
			_hoops_GPIIR->encoding = _hoops_HRHPH;
			_hoops_GPIIR->source = source;
			_hoops_PRRH (source);

			if (_hoops_RIGC->_hoops_PCRPH == null) {
				_hoops_RIGC->_hoops_PAARH = (_hoops_HISHA *)_hoops_GPIIR;
				_hoops_GPIIR->backlink = &_hoops_RIGC->_hoops_PAARH;
			}
			else {
				_hoops_RIGC->_hoops_PCRPH->next = (_hoops_HISHA *)_hoops_GPIIR;
				_hoops_GPIIR->backlink = &_hoops_RIGC->_hoops_PCRPH->next;
				_hoops_HPRH (_hoops_RIGC->_hoops_PCRPH);
			}

			_hoops_RIGC->_hoops_PCRPH = (_hoops_HISHA *)_hoops_GPIIR;
			_hoops_PRRH (_hoops_GPIIR);

			HI_Copy_KName (&source->_hoops_HRPIR, &_hoops_GPIIR->string);

			if (source->_hoops_HRPIR.length > 0) {
				if ((source->_hoops_ARPIR == null ||
					!_hoops_RARPH (source->_hoops_HRPIR,
					source->_hoops_ARPIR->string)) &&
					HOOPS_WORLD->_hoops_PRGHP > 0) {
						ALLOC (sl, _hoops_RRPIR);
						if ((sl->prev = source->_hoops_ARPIR) != null)
							sl->prev->next = sl;
						sl->next = null;
						source->_hoops_ARPIR = sl;
						sl->string.length = source->_hoops_HRPIR.length;
						sl->string._hoops_IPPPP = source->_hoops_HRPIR._hoops_IPPPP;

						if (source->_hoops_HHIAP < HOOPS_WORLD->_hoops_PRGHP)
							++source->_hoops_HHIAP;
						else {
							sl = source->_hoops_ARPIR;
							_hoops_RGGA (sl->prev == null) sl = sl->prev;
							sl->next->prev = null;
							_hoops_PRPIR (sl->string);
							FREE (sl, _hoops_RRPIR);
						}
				}
				else
					_hoops_PRPIR (source->_hoops_HRPIR);

				source->_hoops_HRPIR.length = 0;
				source->_hoops_HRPIR._hoops_IPPPP = null;
				source->_hoops_RHIAP = 0;
			}
			source->_hoops_AHIAP = null;

			if (source->_hoops_PHIAP) {
				_hoops_PRPIR(source->_hoops_PHIAP->string);
				FREE(source->_hoops_PHIAP, _hoops_RRPIR);
				source->_hoops_PHIAP = null;
			}
							}	break;

		case UP_ARROW_KEY: {
			if (source->_hoops_HIIAP != 0)
				_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 1, 0,
				null, source->_hoops_RHIAP, _hoops_HRHPH);
			source->_hoops_PIIAP = source->_hoops_HIIAP = 0;

			if (source->_hoops_ARPIR != null) {
				if (source->_hoops_AHIAP == null) {
					if (!_hoops_RARPH (source->_hoops_HRPIR, source->_hoops_ARPIR->string)) {
						ZALLOC (source->_hoops_PHIAP, _hoops_RRPIR);
						HI_Copy_KName(&source->_hoops_HRPIR, &source->_hoops_PHIAP->string);
					}
					sl = source->_hoops_ARPIR;
				}
				else
					sl = source->_hoops_AHIAP->prev;

				if (sl != null) {
					_hoops_GRHPH (_hoops_RIGC, source, 0, source->_hoops_HRPIR.length,
						sl->string.length, sl->string._hoops_IPPPP, sl->string.length,
						_hoops_HRHPH);
					source->_hoops_AHIAP = sl;
				}
			}
						   }	break;

		case DOWN_ARROW_KEY: {
			if (source->_hoops_HIIAP != 0)
				_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 1, 0,
				null, source->_hoops_RHIAP, _hoops_HRHPH);
			source->_hoops_PIIAP = source->_hoops_HIIAP = 0;

			if (source->_hoops_ARPIR != null) {
				if (source->_hoops_AHIAP != null) {
					sl = source->_hoops_AHIAP->next;

					if (sl == null) {
						if (source->_hoops_PHIAP) {
							_hoops_GRHPH(_hoops_RIGC, source, 0, source->_hoops_HRPIR.length, 
								source->_hoops_PHIAP->string.length, 
								source->_hoops_PHIAP->string._hoops_IPPPP, 
								source->_hoops_PHIAP->string.length, 
								_hoops_HRHPH);
							_hoops_PRPIR(source->_hoops_PHIAP->string);
							FREE(source->_hoops_PHIAP, _hoops_RRPIR);
							source->_hoops_PHIAP = null;
						}
					}
					else {
						sl = source->_hoops_AHIAP->next;
						_hoops_GRHPH (_hoops_RIGC, source, 0, source->_hoops_HRPIR.length,
							sl->string.length, sl->string._hoops_IPPPP, sl->string.length,
							_hoops_HRHPH);
					}
					source->_hoops_AHIAP = sl;
				}
			}
							 }	break;

		case LEFT_ARROW_KEY: {
			if (source->_hoops_HIIAP != 0)
				_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 1, 0,
				null, source->_hoops_RHIAP, _hoops_HRHPH);
			source->_hoops_PIIAP = source->_hoops_HIIAP = 0;

			if (source->_hoops_RHIAP > 0)
				_hoops_GRHPH (_hoops_RIGC, source, 0, 0, 0, null, source->_hoops_RHIAP - 1,
				_hoops_HRHPH);
							 }	break;

		case RIGHT_ARROW_KEY: {
			if (source->_hoops_HIIAP != 0)
				_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 1, 0,
				null, source->_hoops_RHIAP, _hoops_HRHPH);
			source->_hoops_PIIAP = source->_hoops_HIIAP = 0;

			if (source->_hoops_RHIAP < source->_hoops_HRPIR.length)
				_hoops_GRHPH (_hoops_RIGC, source, 0, 0, 0, null, source->_hoops_RHIAP + 1,
				_hoops_HRHPH);
							  }	break;

		case _hoops_AAHPH('U'): {
			if (source->_hoops_HIIAP != 0)
				_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 1, 0,
				null, source->_hoops_RHIAP, _hoops_HRHPH);
			source->_hoops_PIIAP = source->_hoops_HIIAP = 0;

			/* _hoops_PAHPH _hoops_ISSC _hoops_IS _hoops_RH _hoops_RSGI _hoops_IIGR _hoops_RH _hoops_III */
			if (source->_hoops_RHIAP > 0)
				_hoops_GRHPH (_hoops_RIGC, source, 0, source->_hoops_RHIAP, 0, null, 0,
				_hoops_HRHPH);
						   }	break;

		case RUBOUT_KEY:
		case _hoops_AAHPH('H'): {
			if (source->_hoops_HIIAP != 0)
				_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 1, 0,
				null, source->_hoops_RHIAP, _hoops_HRHPH);

			else if (source->_hoops_RHIAP > 0)
				_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP - 1, 1, 0, null,
				source->_hoops_RHIAP - 1,
				_hoops_HRHPH);

			source->_hoops_PIIAP = source->_hoops_HIIAP = 0;
						   }	break;

		default: {
			if (_hoops_HRHPH == _hoops_SSAIP) {	/* 8 _hoops_IGRH _hoops_RGAR */
				if ((_hoops_ISAPH <= key &&
					key <= _hoops_CSAPH) ||
					(_hoops_SSAPH <= key &&
					key <= _hoops_GGPPH)) {
						Karacter		k;

						/* _hoops_SICR _hoops_RGR _hoops_HAHPH _hoops_IS _hoops_IRS _hoops_IAHPH */
						k = (Karacter)key;
						/* _hoops_SGS _hoops_CSAP _hoops_CAHPH (_hoops_RHGRH _hoops_HAR _hoops_CPPPR _hoops_SAHPH _hoops_CPHR) */

						_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 0, 1, &k,
							source->_hoops_RHIAP + 1,
							_hoops_HRHPH);
				}
			}
			else if (_hoops_HCRPH(key) == 0) {	/* _hoops_PPPSR _hoops_CIIA _hoops_IIGR 16b_hoops_SCH _hoops_GSPR */
				Karacter		k = (Karacter)key;

				if (_hoops_PRHPH != _hoops_HRHPH)
					HI_Convert_Karacters_Encoding (1, &k, &k, _hoops_PRHPH, _hoops_HRHPH);

				_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 0, 1, &k,
					source->_hoops_RHIAP + 1,
					_hoops_HRHPH);
			}
			else {
				Karacter		_hoops_GPHPH;

				if ('0' <= key && key <= '9') {
					source->_hoops_PIIAP = (source->_hoops_PIIAP << 4)
						| (key - '0');
					++source->_hoops_HIIAP;
				}
				else if ('A' <= key && key <= 'F') {
					source->_hoops_PIIAP = (source->_hoops_PIIAP << 4)
						| (key - 'A' + 10);
					++source->_hoops_HIIAP;
				}
				else if ('a' <= key && key <= 'f') {
					source->_hoops_PIIAP = (source->_hoops_PIIAP << 4)
						| (key - 'a' + 10);
					++source->_hoops_HIIAP;
				}
				else {
					if (source->_hoops_HIIAP != 0)
						_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 1, 0,
						null, source->_hoops_RHIAP, _hoops_HRHPH);
					if (key == ' ') {
						if (_hoops_HRHPH == _hoops_RPHPH ||
							_hoops_HRHPH == _hoops_APHPH)
							_hoops_GPHPH = 0x8140;
						else
							_hoops_GPHPH = 0x20;

						_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 0, 1,
							&_hoops_GPHPH, source->_hoops_RHIAP+1, _hoops_HRHPH);
					}
					source->_hoops_PIIAP = source->_hoops_HIIAP = 0;
				}

				if ((_hoops_GPHPH = (Karacter)source->_hoops_HIIAP) != 0) {
					_hoops_GPHPH |= _hoops_GPHPH << 8;
					if (_hoops_GPHPH == 0x0101)
						_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 0, 1,
						&_hoops_GPHPH, source->_hoops_RHIAP, _hoops_HRHPH);
					else
						_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 1, 1,
						&_hoops_GPHPH, source->_hoops_RHIAP, _hoops_HRHPH);

					if (source->_hoops_HIIAP == 4) {
						_hoops_GRHPH (_hoops_RIGC, source, source->_hoops_RHIAP, 1, 1,
							&source->_hoops_PIIAP,
							source->_hoops_RHIAP + 1,
							_hoops_HRHPH);
						source->_hoops_PIIAP = source->_hoops_HIIAP = 0;
					}
				}
			}
				 }	break;
											}
#endif
}



GLOBAL_FUNCTION void HI_Queue_Keyboard_Event (
	_hoops_GGAGR *				source,
	Button					button,
	int						status) {

		HI_Queue_Keyboard_Event_W_Enc (source, button, status,
			_hoops_SSAIP);
}

GLOBAL_FUNCTION void HI_Queue_Keyboard_Event_W_Enc (
	_hoops_GGAGR *					source,
	Button					button,
	int						status,
	_hoops_IHGRP			encoding) {
#ifndef DISABLE_EVENTS
	int						index;
	_hoops_SRIIR			*be = null;

	_hoops_AIGPR *		_hoops_RIGC;
	_hoops_IIRIR (_hoops_RIGC);

	index = _hoops_HCRPH(button);

	if (index == 0	||
		source->_hoops_CPCR._hoops_IRPIR != null &&
		source->_hoops_CPCR._hoops_IRPIR[index] > 0) {
			ZALLOC (be, _hoops_SRIIR);
			be->owner = HOOPS_WORLD;
			be->_hoops_HIHI = 1;
			be->type = _hoops_CRIIR;
			be->_hoops_PHSHA = HI_What_Time();

			be->button = button;
			be->source = source;
			be->status = status;
			_hoops_PRRH (source);


			if (_hoops_RIGC->_hoops_PCRPH == null) {
				_hoops_RIGC->_hoops_PAARH = (_hoops_HISHA *)be;
				be->backlink = &_hoops_RIGC->_hoops_PAARH;
			}
			else {
				_hoops_RIGC->_hoops_PCRPH->next = (_hoops_HISHA *)be;
				be->backlink = &_hoops_RIGC->_hoops_PCRPH->next;
				_hoops_HPRH (_hoops_RIGC->_hoops_PCRPH);
			}

			_hoops_RIGC->_hoops_PCRPH = (_hoops_HISHA *)be;
			_hoops_PRRH (be);

			be->_hoops_RAIIR = null;
	}

	if (source->_hoops_CPCR._hoops_SPIAP > 0) {
		HI_Edit_Karacters (_hoops_RIGC, source, button, encoding);

		if (_hoops_RIGC->_hoops_PCRPH != (_hoops_HISHA *)be) {
			/* _hoops_PIHA _hoops_HS _hoops_PRHI _hoops_IRS _hoops_GAIIR _hoops_HII _hoops_RH _hoops_IHCGP */

			/* _hoops_RPP _hoops_SR _hoops_SAHR _hoops_IIAC _hoops_IRS _hoops_PPHPH _hoops_HAH, _hoops_GCAPH _hoops_RGR _hoops_CCA _hoops_SCH */
			if (be != null) {
				be->_hoops_RAIIR = (_hoops_AHIIR *) _hoops_RIGC->_hoops_PCRPH;
				_hoops_PRRH (be->_hoops_RAIIR);
			}
		}
	}
#endif
}



GLOBAL_FUNCTION void HC_CDECL HI_Enable_Wakeup_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	float					_hoops_PHSAP) 
{
#ifdef DISABLE_EVENTS
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(_hoops_HPHPH);
#else
	UNREFERENCED(_hoops_RIGC);

	_hoops_GSPGR	_hoops_SPAPR;
	if ((_hoops_SPAPR = (_hoops_GSPGR)(_hoops_PHSAP * (float)_hoops_HSPGR)) == (_hoops_GSPGR)0) {
		HE_ERROR2 (HEC_EVENT_HANDLER, HES_INVALID_INTERVAL,"Requested wakeup interval is too small -",
			Sprintf_D (null, "We can only resolve 1/%dth of a second", int (_hoops_HSPGR)));
		return;
	}

	bool _hoops_IPHPH = true;

	LOCK_MUTEX (HOOPS_WORLD->_hoops_IGAPH);

	_hoops_HRIIR *	_hoops_CHIIR;
	_hoops_HRIIR **	_hoops_ASRGR;

	if ((_hoops_CHIIR = HOOPS_WORLD->_hoops_CGAPH) != null) {
		float	_hoops_CPHPH =   0.99999f * _hoops_PHSAP;
		float	_hoops_SPHPH = 1.00001f * _hoops_PHSAP;

		do if (_hoops_CPHPH < _hoops_CHIIR->_hoops_PHSAP && _hoops_CHIIR->_hoops_PHSAP < _hoops_SPHPH) {
			++_hoops_CHIIR->_hoops_AHSAP;
			_hoops_IPHPH = false;
			break;
		} _hoops_RGGA ((_hoops_CHIIR = _hoops_CHIIR->next) == null);
	}

	if (_hoops_IPHPH) {
		ZALLOC (_hoops_CHIIR, _hoops_HRIIR);
		_hoops_CHIIR->_hoops_HIHI = 1;
		_hoops_CHIIR->type = _hoops_PRIIR;
		_hoops_CHIIR->owner = HOOPS_WORLD;
		_hoops_CHIIR->_hoops_PHSAP = _hoops_PHSAP;
		_hoops_CHIIR->_hoops_AHSAP = 1;
		_hoops_CHIIR->_hoops_SPAPR = _hoops_SPAPR;
		_hoops_CHIIR->_hoops_RHSAP = _hoops_SPAPR + HI_What_Time ();

		_hoops_ASRGR = &HOOPS_WORLD->_hoops_CGAPH;
		_hoops_PCCAR {
			_hoops_HRIIR *	_hoops_GHHPH;

			if ((_hoops_GHHPH = *_hoops_ASRGR) == null) {
				_hoops_CHIIR->next = null;
				break;
			}

			if (_hoops_GHHPH->_hoops_RHSAP > _hoops_CHIIR->_hoops_RHSAP) {
				_hoops_CHIIR->next = _hoops_GHHPH;
				_hoops_GHHPH->backlink = &_hoops_CHIIR->next;
				break;
			}

			_hoops_ASRGR = &_hoops_GHHPH->next;
		}
		*_hoops_ASRGR = _hoops_CHIIR;
		_hoops_CHIIR->backlink = _hoops_ASRGR;
	}

	UNLOCK_MUTEX (HOOPS_WORLD->_hoops_IGAPH);

#endif
}


HC_INTERFACE void HC_CDECL HC_Enable_Wakeup_Events (
	double			_hoops_HPHPH) 
{
	_hoops_PAPPR context("Enable_Wakeup_Events");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Enable_Wakeup_Events (%F);\n", _hoops_HPHPH));
	);

	float	_hoops_PHSAP = (float)_hoops_HPHPH;

	if (_hoops_PHSAP <= 0.0f) {
		HE_ERROR (HEC_EVENT_HANDLER, HES_INVALID_INTERVAL, "Requested wakeup interval is zero or negative");
		return;
	}

	HI_Enable_Wakeup_Events (context, _hoops_PHSAP);

#endif
}


GLOBAL_FUNCTION bool HI_Disable_Wakeup_Events (
	_hoops_AIGPR *	_hoops_RIGC,
	float					_hoops_PHSAP) 
{
#ifdef DISABLE_EVENTS
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(_hoops_PHSAP);
	return false;
#else
	bool result = false;

	LOCK_MUTEX (HOOPS_WORLD->_hoops_IGAPH);

	_hoops_HRIIR *	_hoops_CHIIR;
	if ((_hoops_CHIIR = HOOPS_WORLD->_hoops_CGAPH) != null) {
		float	_hoops_CPHPH =   0.99999f * _hoops_PHSAP;
		float	_hoops_SPHPH = 1.00001f * _hoops_PHSAP;

		do if (_hoops_CPHPH < _hoops_CHIIR->_hoops_PHSAP && _hoops_CHIIR->_hoops_PHSAP < _hoops_SPHPH) {
			if (--_hoops_CHIIR->_hoops_AHSAP == 0)
				HI_Generic_Delete (_hoops_RIGC, (_hoops_HPAH *)_hoops_CHIIR);
			result = true;
			break;
		} _hoops_RGGA ((_hoops_CHIIR = _hoops_CHIIR->next) == null);
	}

	UNLOCK_MUTEX (HOOPS_WORLD->_hoops_IGAPH);

	return result;
#endif
}



HC_INTERFACE void HC_CDECL HC_Disable_Wakeup_Events (
	double		_hoops_HPHPH) 
{
	_hoops_PAPPR context("Disable_Wakeup_Events");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Disable_Wakeup_Events (%F);\n", _hoops_HPHPH));
	);

	float	_hoops_PHSAP = (float)_hoops_HPHPH;
	
	if (_hoops_PHSAP <= 0.0f) {
		HE_ERROR (HEC_EVENT_HANDLER, HES_INVALID_INTERVAL, "Requested wakeup interval is zero or negative");
		return;
	}

	if (!HI_Disable_Wakeup_Events (context, _hoops_PHSAP))
		HE_ERROR (HEC_EVENT_HANDLER, HES_WAKEUP_NOT_ENABLED, "Specified wakeup is fully disabled or was not found at all");

#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Wakeup (
	float *		_hoops_PHSAP) 
{
	_hoops_PAPPR context("Show_Wakeup");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Wakeup () */\n");
	);

	_hoops_HHIIR *	_hoops_RHHPH;
	if ((_hoops_RHHPH = (_hoops_HHIIR *)HI_Current_Event (context, _hoops_PHIIR)) == null) 
		return;

	*_hoops_PHSAP = _hoops_RHHPH->_hoops_CHIIR->_hoops_PHSAP;
#endif
}




HC_INTERFACE void HC_CDECL HC_Get_Wakeup (
	double			_hoops_AHHPH) 
{
	_hoops_PAPPR context("Get_Wakeup");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Get_Wakeup (%F);\n", _hoops_AHHPH));
	);

	if (_hoops_AHHPH > 0.0f) {

		float	_hoops_PHSAP = (float)_hoops_AHHPH;
		char	_hoops_RHAPH[20];

		HI_Enable_Wakeup_Events (context, _hoops_PHSAP);

		do {
			_hoops_RHAPH[0] = 'w';		/* _hoops_GGR _hoops_AGIR _hoops_RH _hoops_IAAPH _hoops_ISHS */
			HI_Await_Event (context, _hoops_RHAPH, _hoops_GGAPR(_hoops_RHAPH));

			if (_hoops_RHAPH[0] == 'n') /* _hoops_PIRC */
				HI_Exit_Program();
		} _hoops_RGGA (_hoops_RHAPH[0] == 'w');

		HI_Disable_Wakeup_Events (context, _hoops_PHSAP);
	}
#endif
}



#define _hoops_PHHPH	2

GLOBAL_FUNCTION void HI_Queue_Wakeup_Event (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HRIIR *				_hoops_CHIIR) 
{
#ifndef DISABLE_EVENTS
	_hoops_HHIIR *	_hoops_IHIIR;
	_hoops_HRIIR **		_hoops_ASRGR;
	_hoops_HRIIR *		_hoops_GHHPH;
	_hoops_GSPGR			now;

	if (_hoops_CHIIR->_hoops_AHSAP == 0) {
		/* _hoops_HHHPH (_hoops_HHAPA,_hoops_IHHPH); ... */
		_hoops_CIGPR (_hoops_RIGC,_hoops_CHIIR);
		_hoops_HPRH (_hoops_CHIIR);
		return;
	}

	LOCK_MUTEX (HOOPS_WORLD->_hoops_IGAPH);

	if (_hoops_CHIIR->_hoops_HHSAP < _hoops_PHHPH) {
		ZALLOC (_hoops_IHIIR, _hoops_HHIIR);
		_hoops_IHIIR->owner = HOOPS_WORLD;
		_hoops_IHIIR->_hoops_HIHI = 1;
		_hoops_IHIIR->type = _hoops_PHIIR;
		_hoops_IHIIR->_hoops_PHSHA = HI_What_Time();

		if (_hoops_RIGC->_hoops_PCRPH == null) {
			_hoops_RIGC->_hoops_PAARH = (_hoops_HISHA *)_hoops_IHIIR;
			_hoops_IHIIR->backlink = &_hoops_RIGC->_hoops_PAARH;
		}
		else {
			_hoops_RIGC->_hoops_PCRPH->next = (_hoops_HISHA *)_hoops_IHIIR;
			_hoops_IHIIR->backlink = &_hoops_RIGC->_hoops_PCRPH->next;
			_hoops_HPRH (_hoops_RIGC->_hoops_PCRPH);
		}

		_hoops_RIGC->_hoops_PCRPH = (_hoops_HISHA *)_hoops_IHIIR;
		_hoops_PRRH (_hoops_IHIIR);

		_hoops_IHIIR->_hoops_CHIIR = _hoops_CHIIR;
		_hoops_PRRH (_hoops_CHIIR);
	}

	now = HI_What_Time ();
	do _hoops_CHIIR->_hoops_RHSAP += _hoops_CHIIR->_hoops_SPAPR;
	_hoops_RGGA (_hoops_CHIIR->_hoops_RHSAP > now);

	/* _hoops_ASAR-_hoops_GSRGR _hoops_RH _hoops_IHHPH */

	_hoops_CIGPR (_hoops_RIGC,_hoops_CHIIR);
	_hoops_ASRGR = &HOOPS_WORLD->_hoops_CGAPH;
	_hoops_RGGA ((_hoops_GHHPH = *_hoops_ASRGR) == null ||
		   _hoops_GHHPH->_hoops_RHSAP >= _hoops_CHIIR->_hoops_RHSAP)
		_hoops_ASRGR = &_hoops_GHHPH->next;
	if ((_hoops_CHIIR->next = *_hoops_ASRGR) != null)
		(*_hoops_ASRGR)->backlink = &_hoops_CHIIR->next;
	*_hoops_ASRGR = _hoops_CHIIR;
	_hoops_CHIIR->backlink = _hoops_ASRGR;

	UNLOCK_MUTEX (HOOPS_WORLD->_hoops_IGAPH);
#endif
}


GLOBAL_FUNCTION void HI_Queue_Wakeup_Event (
	_hoops_AIGPR *	_hoops_RIGC,
	float					_hoops_PHSAP) 
{
#ifdef DISABLE_EVENTS
	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (_hoops_PHSAP);
#else

	if (HOOPS_WORLD->_hoops_AARPH) 
		HI_Update_Events (_hoops_RIGC);

	LOCK_MUTEX (HOOPS_WORLD->_hoops_IGAPH);

	bool			_hoops_CHHPH = true;

	_hoops_HHIIR *	_hoops_IHIIR;
	_hoops_HRIIR *		_hoops_CHIIR;

	_hoops_CHIIR = HOOPS_WORLD->_hoops_CGAPH;
	_hoops_PCCAR {
		if (_hoops_CHIIR == null) {
			HE_WARNING (HEC_EVENT_HANDLER, HES_WAKEUP_NOT_ENABLED, "Specified wakeup is not currently enabled");
			_hoops_CHHPH = false;
			break;
		}
		if (_hoops_CHIIR->_hoops_PHSAP == _hoops_PHSAP) 
			break;
		_hoops_CHIIR = _hoops_CHIIR->next;
	}

	if (_hoops_CHHPH) {

		ZALLOC (_hoops_IHIIR, _hoops_HHIIR);
		_hoops_IHIIR->owner = HOOPS_WORLD;
		_hoops_IHIIR->_hoops_HIHI = 1;
		_hoops_IHIIR->type = _hoops_PHIIR;
		_hoops_IHIIR->_hoops_PHSHA = HI_What_Time();

		if (_hoops_RIGC->_hoops_PCRPH == null) {
			_hoops_RIGC->_hoops_PAARH = (_hoops_HISHA *)_hoops_IHIIR;
			_hoops_IHIIR->backlink = &_hoops_RIGC->_hoops_PAARH;
		}
		else {
			_hoops_RIGC->_hoops_PCRPH->next = (_hoops_HISHA *)_hoops_IHIIR;
			_hoops_IHIIR->backlink = &_hoops_RIGC->_hoops_PCRPH->next;
			_hoops_HPRH (_hoops_RIGC->_hoops_PCRPH);
		}

		_hoops_RIGC->_hoops_PCRPH = (_hoops_HISHA *)_hoops_IHIIR;
		_hoops_PRRH (_hoops_IHIIR);

		_hoops_IHIIR->_hoops_CHIIR = _hoops_CHIIR;
		_hoops_PRRH (_hoops_CHIIR);
	}

	UNLOCK_MUTEX (HOOPS_WORLD->_hoops_IGAPH);
#endif
}

HC_INTERFACE void HC_CDECL HC_Queue_Wakeup_Event (
	double		_hoops_HPHPH) 
{
	_hoops_PAPPR context("Queue_Wakeup_Event");

#ifdef DISABLE_EVENTS
	_hoops_IRPPR ("Events");
#else

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Queue_Wakeup_Event (%F);\n", _hoops_HPHPH));
	);

	float	_hoops_PHSAP = (float)_hoops_HPHPH;
	
	if (_hoops_PHSAP <= 0.0f) {
		HE_ERROR (HEC_EVENT_HANDLER, HES_INVALID_INTERVAL, "Specified wakeup interval is zero or negative");
		return;
	}

	HI_Queue_Wakeup_Event (context, _hoops_PHSAP);
#endif
}

GLOBAL_FUNCTION void HI_Queue_Special_Event (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			type,
	char const *			value) 
{
	if (!_hoops_RIGC)
		_hoops_IIRIR (_hoops_RIGC);

	_hoops_RIIIR *	_hoops_GPIIR;
	ZALLOC (_hoops_GPIIR, _hoops_RIIIR);
	_hoops_GPIIR->owner = HOOPS_WORLD;
	_hoops_GPIIR->_hoops_HIHI = 1;
	_hoops_GPIIR->type = _hoops_GIIIR;
	_hoops_GPIIR->_hoops_PHSHA = HI_What_Time ();
	HI_Copy_Chars_To_Name (type, &_hoops_GPIIR->name);
	HI_Copy_Chars_To_Name (value, &_hoops_GPIIR->value);

	if (_hoops_RIGC->_hoops_PCRPH == null) {
		_hoops_RIGC->_hoops_PAARH = (_hoops_HISHA *)_hoops_GPIIR;
		_hoops_GPIIR->backlink = &_hoops_RIGC->_hoops_PAARH;
	}
	else {
		_hoops_RIGC->_hoops_PCRPH->next = (_hoops_HISHA *)_hoops_GPIIR;
		_hoops_GPIIR->backlink = &_hoops_RIGC->_hoops_PCRPH->next;
		_hoops_HPRH (_hoops_RIGC->_hoops_PCRPH);
	}
	_hoops_RIGC->_hoops_PCRPH = (_hoops_HISHA *)_hoops_GPIIR;
	_hoops_PRRH (_hoops_GPIIR);
}



HC_INTERFACE void HC_CDECL HC_Queue_Special_Event (
	char const *		type,
	char const *		value) 
{
	_hoops_PAPPR context("Queue_Special_Event");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Queue_Special_Event (%S, %S);\n", type, value));
	);

	HI_Queue_Special_Event (context, type, value);
}



HC_INTERFACE void HC_CDECL HC_Show_Special_Event (
	char *		type,
	char *		value) 
{
	_hoops_PAPPR context("Show_Special_Event");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Special_Event () */\n");
	);

	_hoops_RIIIR *	_hoops_GPIIR;
	if ((_hoops_GPIIR = (_hoops_RIIIR *)HI_Current_Event (context, _hoops_GIIIR)) == null)
		return;

	HI_Return_Chars (type, -1, _hoops_GPIIR->name.text, _hoops_GPIIR->name.length);
	HI_Return_Chars (value, -1, _hoops_GPIIR->value.text, _hoops_GPIIR->value.length);
}


GLOBAL_FUNCTION char * HI_Build_Special_Event_String (
	char alter *		string,
	char const *		brand,
	_hoops_CRCP const *		_hoops_GHRI,
	POINTER_SIZED_INT	window,
	int					_hoops_SHHPH) 
{
	char				_hoops_GIHPH[32];

	Sprintf_P (string, "%p", _hoops_GHRI);
	_hoops_HPRPR (", ", string);
	_hoops_HPRPR (brand, string);
	Sprintf_LD (_hoops_GIHPH, " Window = %D", window);
	_hoops_HPRPR (_hoops_GIHPH, string);
	if (_hoops_SHHPH > 0) {
		_hoops_HPRPR (", ", string);
		_hoops_HPRPR (brand, string);
		Sprintf_D (_hoops_GIHPH, " Event Type = %d", _hoops_SHHPH);
		_hoops_HPRPR (_hoops_GIHPH, string);
	}
	return (string);
}


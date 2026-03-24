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
 * $Id: obf_tmp.txt 1.316 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

struct _hoops_RCSGA {
	_hoops_RCSGA *		next;
	_hoops_SSGI			color;
	_hoops_ACSGA		list;
	_hoops_PCSGA	findex;
	_hoops_APCA	normal;
	_hoops_HCSGA	_hoops_ICSGA;
};


GLOBAL_FUNCTION _hoops_HIR * HI_New_Diffuse_Channel (
	_hoops_RCR *					texture) {
	_hoops_HIR *		_hoops_PGC;

	ZALLOC (_hoops_PGC, _hoops_HIR);
	_hoops_PGC->texture = texture;
	_hoops_PRRH (texture);
	return _hoops_PGC;
}


local _hoops_HIR * _hoops_CCSGA (
	_hoops_HIR const *	in) {
	_hoops_HIR *		_hoops_PGC;

	ALLOC (_hoops_PGC, _hoops_HIR);
	*_hoops_PGC = *in;
	_hoops_PRRH (_hoops_PGC->texture);
	HI_Copy_Name (&in->name, &_hoops_PGC->name);
	_hoops_PGC->next = null;
	return _hoops_PGC;
}


GLOBAL_FUNCTION _hoops_HIR * HI_Copy_Diffuse_Channel_List (
	_hoops_HIR const *	list) {
	_hoops_HIR *		_hoops_PGC;
	_hoops_HIR *		_hoops_IRRS = null;
	_hoops_HIR **		_hoops_ASRGR = &_hoops_IRRS;

	while (list) {
		_hoops_PGC = _hoops_CCSGA (list);
		*_hoops_ASRGR = _hoops_PGC;
		_hoops_ASRGR = &_hoops_PGC->next;
		list = list->next;
	}
	return _hoops_IRRS;
}

#if 0
struct _hoops_HIR {
	_hoops_HIR *		next;
	_hoops_RCR *					texture;
	_hoops_HCRPR						name;
	float						_hoops_IRIR;
	int							_hoops_HGA;
	Material_Channel_Flags		flags;
};

local int _hoops_SCSGA (
	_hoops_RCR const *		texture) {
	_hoops_AAPIR const *	nl;
	int					value;

	if (texture == null)
		return 0;

	value = texture->flags;

	if ((nl = texture->_hoops_PAPIR) != null) do {
		value += nl->key;
		nl = nl->next;
	} while (nl != null);

	return value;
}

while (_hoops_GSSGA != null) {
	value += _hoops_SCSGA (_hoops_GSSGA->texture);
	value += (int)(_hoops_GSSGA->_hoops_HGA * _hoops_GSSGA->_hoops_IRIR);
	value += _hoops_GSSGA->flags;

	_hoops_GSSGA = _hoops_RSSGA->next;
}
#endif

GLOBAL_FUNCTION bool HI_Diffuse_Channels_Match (
	_hoops_HIR const *	_hoops_ASSGA,
	_hoops_HIR const *	_hoops_RSSGA,
	Integer32						_hoops_PSSGA) 
{

	while (_hoops_RSSGA != null) {
		while (_hoops_ASSGA && _hoops_ASSGA->_hoops_HGA < _hoops_RSSGA->_hoops_HGA)
			_hoops_ASSGA = _hoops_ASSGA->next;

		if (_hoops_ASSGA == null ||
			_hoops_ASSGA->_hoops_HGA != _hoops_RSSGA->_hoops_HGA)
			return false;

		if (_hoops_ASSGA->flags != _hoops_RSSGA->flags)
			return false;

		if (_hoops_ASSGA->_hoops_IRIR != _hoops_RSSGA->_hoops_IRIR)
			return false;

		if (_hoops_ASSGA->texture->_hoops_PSSGA != _hoops_PSSGA)
			return false;


		if (!_hoops_RAHSR(_hoops_ASSGA->texture->name, _hoops_RSSGA->texture->name))
			return false;

		_hoops_RSSGA = _hoops_RSSGA->next;
	}

	return true;
}

GLOBAL_FUNCTION _hoops_HIR * HI_Mix_Diffuse_Channels (
	_hoops_HIR const *	_hoops_HSSGA,
	_hoops_HIR const *	_hoops_ISSGA) {
	_hoops_HIR *			_hoops_CSSGA = null;
	_hoops_HIR **			_hoops_ASRGR = &_hoops_CSSGA;
	_hoops_HIR *			_hoops_PGC = null;
	_hoops_HIR const *	_hoops_SSSGA = _hoops_HSSGA;
	_hoops_HIR const *	_hoops_IRRS = _hoops_ISSGA;
	bool done = false;

	while ((_hoops_IRRS || _hoops_SSSGA) && !done) {
		if (_hoops_IRRS) {
			if (_hoops_SSSGA) {
				if (_hoops_IRRS->_hoops_HGA <= _hoops_SSSGA->_hoops_HGA) {
					/* _hoops_GGR _hoops_RH _hoops_AGIR _hoops_IIGR _hoops_IRS _hoops_GGGRA, _hoops_GIPR _hoops_CHR _hoops_RGGRA _hoops_PPR _hoops_RH _hoops_CRPS
					 * _hoops_AGGRA (_hoops_HCCPR _hoops_RGCI _hoops_RSIRR _hoops_HRGR _hoops_RH _hoops_GRH _hoops_HPAP _hoops_PGGRA, "*")*/
					if (_hoops_IRRS->_hoops_HGA == _hoops_SSSGA->_hoops_HGA) {
						if (_hoops_AGGR (_hoops_IRRS->texture->name.text, "*")) {
							_hoops_PGC = _hoops_CCSGA (_hoops_SSSGA);
						}
						else {
							_hoops_PGC = _hoops_CCSGA (_hoops_IRRS);
							/* _hoops_HGGRA _hoops_AGSR _hoops_IS _hoops_IGGRA _hoops_GAR _hoops_PHRI _hoops_RH _hoops_SCGR _hoops_RCAP _hoops_SGGA
							 * _hoops_IS _hoops_HCR _hoops_RCHAR _hoops_GRIP.  _hoops_HSRR _hoops_RH _hoops_GCGC _hoops_IIGR _hoops_CGGRA, _hoops_RGR _hoops_AGSR
							 * _hoops_SGS _hoops_SR _hoops_SAHR _hoops_HCHGA _hoops_GGSR _hoops_RSIH (_hoops_HCCPR _hoops_RH _hoops_CGHI _hoops_RCAP _hoops_CSAP "*") */
							if (BIT (_hoops_IRRS->flags, _hoops_SGGRA))
								done = true;
						}
						_hoops_SSSGA = _hoops_SSSGA->next; /* _hoops_GCHGA _hoops_GIPR */
						_hoops_IRRS = _hoops_IRRS->next;
					}
					else {
						_hoops_PGC = _hoops_CCSGA (_hoops_IRRS);
						if (BIT (_hoops_IRRS->flags, _hoops_SGGRA))
							done = true;
						_hoops_IRRS = _hoops_IRRS->next; /* _hoops_GCHGA _hoops_CRPS _hoops_RGAR */
					}
				}
				else {
					_hoops_PGC = _hoops_CCSGA (_hoops_SSSGA);
					_hoops_SSSGA = _hoops_SSSGA->next;  /* _hoops_GCHGA _hoops_GRGRA _hoops_RGAR */
				}
				*_hoops_ASRGR = _hoops_PGC;
				_hoops_ASRGR = &_hoops_PGC->next;
			}
			else {
				*_hoops_ASRGR = HI_Copy_Diffuse_Channel_List (_hoops_IRRS);
				break;
			}
		}
		else {
			*_hoops_ASRGR = HI_Copy_Diffuse_Channel_List (_hoops_SSSGA);
			break;
		}
	}
	return _hoops_CSSGA;
}

GLOBAL_FUNCTION void HI_Free_Diffuse_Channel_List (
	_hoops_HIR alter *	_hoops_PGC) {

	while (_hoops_PGC) {
		_hoops_HIR *	victim = _hoops_PGC;

		_hoops_PGC = _hoops_PGC->next;
		_hoops_RGAIR (victim->name);
		_hoops_HPRH (victim->texture);
		FREE (victim, _hoops_HIR);
	}
}

GLOBAL_FUNCTION bool HI_Unset_Color(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_SSGI *					color) 
{
	/* _hoops_RRGRA */
	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(item);
	UNREFERENCED(color);
	return false;
}

GLOBAL_FUNCTION void HI_Copy_Named_Material (
	Named_Material const *		in,
	Named_Material *			_hoops_PAGR) 
{
	_hoops_ARGRA	_hoops_PRGRA = _hoops_PAGR->_hoops_PRGRA = in->_hoops_PRGRA;

	_hoops_PAGR->_hoops_HRGRA=in->_hoops_HRGRA;
	_hoops_PAGR->_hoops_SCA = HI_Copy_Diffuse_Channel_List (in->_hoops_SCA);
	_hoops_PAGR->_hoops_CSHR = in->_hoops_CSHR;
	HI_Copy_Name (&in->_hoops_IRGRA, &_hoops_PAGR->_hoops_IRGRA);

	for (int i=0; i<_hoops_CRGRA; i++) {
		HI_Copy_Name (&in->name[i], &_hoops_PAGR->name[i]);
		if (BIT (_hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i]))
			_hoops_PAGR->color[i] = in->color[i];
		_hoops_PAGR->flags[i] = in->flags[i];
	}
	for (int i=0; i<_hoops_GAGRA; i++)
		if ((_hoops_PAGR->texture[i] = in->texture[i]) != null)
			_hoops_PRRH(_hoops_PAGR->texture[i]);

	if (BIT (_hoops_PRGRA, M_TRANSMISSION))
		_hoops_PAGR->_hoops_IRIR = in->_hoops_IRIR;

	if (BIT (_hoops_PRGRA, _hoops_RAGRA))
		_hoops_PAGR->gloss = in->gloss;

	if (BIT (_hoops_PRGRA, _hoops_AAGRA))
		_hoops_PAGR->_hoops_PAGRA = in->_hoops_PAGRA;
}

local bool _hoops_HAGRA (
	_hoops_RCR const *		first,
	_hoops_RCR const *		_hoops_IAGRA) {
	_hoops_AAPIR const *	_hoops_CAGRA;
	_hoops_AAPIR const *	_hoops_SAGRA;

	if (first == null && _hoops_IAGRA == null)
		return true;
	if (first == null || _hoops_IAGRA == null)
		return false;

	if (first->flags != TF_UNEVALUATED || _hoops_IAGRA->flags != TF_UNEVALUATED)
		return false;

	_hoops_CAGRA = first->_hoops_PAPIR;
	_hoops_SAGRA = _hoops_IAGRA->_hoops_PAPIR;
	while (_hoops_CAGRA != null && _hoops_SAGRA != null) {
		if (_hoops_CAGRA->key != _hoops_SAGRA->key || !_hoops_RAHSR (_hoops_CAGRA->name, _hoops_SAGRA->name))
			return false;

		_hoops_CAGRA = _hoops_CAGRA->next;
		_hoops_SAGRA = _hoops_SAGRA->next;
	}

	if (_hoops_CAGRA != null || _hoops_SAGRA != null)	/* _hoops_HIGR _hoops_SPCC _hoops_GPGRA */
		return false;

	return true;
}
local bool _hoops_RPGRA (
	_hoops_HIR const *	first,
	_hoops_HIR const *	_hoops_IAGRA) {

	while (first && _hoops_IAGRA) {
		if (first->_hoops_HGA != _hoops_IAGRA->_hoops_HGA ||
			first->flags != _hoops_IAGRA->flags ||
			first->_hoops_IRIR != _hoops_IAGRA->_hoops_IRIR ||
			!_hoops_HAGRA (first->texture, _hoops_IAGRA->texture))
			return false;
		first = first->next;
		_hoops_IAGRA = _hoops_IAGRA->next;
	}
	if (first || _hoops_IAGRA)
		return false;
	return true;
}

GLOBAL_FUNCTION bool HI_Named_Materials_Equal (
	Named_Material const *	first,
	Named_Material const *	_hoops_IAGRA) {
	_hoops_ARGRA		_hoops_PRGRA;
	int							i;

	if ((_hoops_PRGRA = first->_hoops_PRGRA) != _hoops_IAGRA->_hoops_PRGRA)
		return false;
	if (first->_hoops_HRGRA != _hoops_IAGRA->_hoops_HRGRA)
		return false;

	if (!_hoops_RPGRA (first->_hoops_SCA, _hoops_IAGRA->_hoops_SCA))
		return false;
	if (first->_hoops_CSHR != _hoops_IAGRA->_hoops_CSHR)
		return false;

	for (i=0; i<_hoops_CRGRA; i++) {
		if (BIT (_hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i]) &&
			first->color[i] != _hoops_IAGRA->color[i])
			return false;
	}

	for (i=0; i<_hoops_GAGRA; i++)
		if (BIT (_hoops_PRGRA, HOOPS_READ_ONLY._hoops_APGRA[i]) &&
			!_hoops_HAGRA (first->texture[i], _hoops_IAGRA->texture[i]))
			return false;

	if (BIT (_hoops_PRGRA, M_TRANSMISSION))
		if (first->_hoops_IRIR != _hoops_IAGRA->_hoops_IRIR)
			return false;

	if (BIT (_hoops_PRGRA, _hoops_RAGRA))
		if (first->gloss != _hoops_IAGRA->gloss)
			return false;

	if (BIT (_hoops_PRGRA, _hoops_AAGRA))
		if (first->_hoops_PAGRA != _hoops_IAGRA->_hoops_PAGRA)
			return false;

	return true;
}

local bool _hoops_PPGRA (
	_hoops_HCSGA alter *	_hoops_HPGRA,
	_hoops_HCSGA const *	_hoops_IPGRA,
	_hoops_ARGRA		_hoops_PCGS) 
{
	bool					_hoops_CCCIR = false;
	Named_Material const *	_hoops_CPGRA = &_hoops_IPGRA->_hoops_ISHIR;
	Named_Material alter *	_hoops_SPGRA = &_hoops_HPGRA->_hoops_ISHIR;
	bool					_hoops_GHGRA = false;

	if (_hoops_IPGRA->_hoops_ISHIR._hoops_SCA && !BIT (_hoops_PCGS, M_DIFFUSE)) {
		if (_hoops_HPGRA->_hoops_ISHIR._hoops_SCA) {
			_hoops_HIR *_hoops_CSSGA =
				HI_Mix_Diffuse_Channels (
					_hoops_HPGRA->_hoops_ISHIR._hoops_SCA,
					_hoops_IPGRA->_hoops_ISHIR._hoops_SCA);
			HI_Free_Diffuse_Channel_List (_hoops_HPGRA->_hoops_ISHIR._hoops_SCA);
			_hoops_HPGRA->_hoops_ISHIR._hoops_SCA = _hoops_CSSGA;
		}
		else
			_hoops_HPGRA->_hoops_ISHIR._hoops_SCA = HI_Copy_Diffuse_Channel_List (_hoops_IPGRA->_hoops_ISHIR._hoops_SCA);
		_hoops_SPGRA->_hoops_HRGRA &= ~M_DIFFUSE;
		_hoops_GHGRA = true;
	}
	else if (BIT(_hoops_IPGRA->_hoops_ISHIR._hoops_PRGRA, _hoops_RHGRA) && !BIT (_hoops_PCGS, M_DIFFUSE) &&
			 _hoops_HPGRA->_hoops_ISHIR._hoops_SCA) {
		HI_Free_Diffuse_Channel_List (_hoops_HPGRA->_hoops_ISHIR._hoops_SCA);
		_hoops_HPGRA->_hoops_ISHIR._hoops_SCA = null;
	}
	else if (_hoops_HPGRA->_hoops_ISHIR._hoops_SCA)
		_hoops_GHGRA = true;

	if (BIT (_hoops_CPGRA->_hoops_PRGRA, M_DIFFUSE) && !BIT (_hoops_PCGS, M_DIFFUSE)) {
		_hoops_SPGRA->_hoops_CSHR = _hoops_CPGRA->_hoops_CSHR;
		_hoops_RGAIR (_hoops_SPGRA->_hoops_IRGRA);
		HI_Copy_Name (&_hoops_CPGRA->_hoops_IRGRA, &_hoops_SPGRA->_hoops_IRGRA);
		_hoops_SPGRA->_hoops_HRGRA &= ~M_DIFFUSE;
	}
	for (int i=0; i<_hoops_CRGRA; i++) {
		if (BIT (_hoops_CPGRA->_hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i]) &&
			!BIT (_hoops_PCGS, HOOPS_READ_ONLY._hoops_AHGRA[i])) {
			_hoops_SPGRA->color[i] = _hoops_CPGRA->color[i];
			_hoops_RGAIR (_hoops_SPGRA->name[i]);
			HI_Copy_Name (&_hoops_CPGRA->name[i], &_hoops_SPGRA->name[i]);
			_hoops_CCCIR = true;
			_hoops_SPGRA->_hoops_HRGRA &= ~HOOPS_READ_ONLY._hoops_SRGRA[i];
			if (!BIT (_hoops_CPGRA->_hoops_PRGRA, HOOPS_READ_ONLY._hoops_APGRA[i])) {
				/* _hoops_IH _hoops_HAIR _hoops_GRIP _hoops_RII _hoops_HSAR _hoops_SPI, _hoops_HAIR _hoops_PPR _hoops_HH _hoops_CHR _hoops_PGIA _hoops_HGIA */
				if (_hoops_SPGRA->texture[i] != null)
					_hoops_HPRH (_hoops_SPGRA->texture[i]);
				_hoops_SPGRA->texture[i]=null;
				_hoops_SPGRA->_hoops_PRGRA &= ~HOOPS_READ_ONLY._hoops_SRGRA[i];
			}
		}
		_hoops_SPGRA->flags[i] = _hoops_CPGRA->flags[i];
	}

	for (int i=0; i<_hoops_GAGRA; i++) {
		if (BIT (_hoops_CPGRA->_hoops_PRGRA, HOOPS_READ_ONLY._hoops_APGRA[i]) &&
			!BIT (_hoops_PCGS, HOOPS_READ_ONLY._hoops_AHGRA[i])) {
			if (_hoops_SPGRA->texture[i] != null)
				_hoops_HPRH (_hoops_SPGRA->texture[i]);
			if ((_hoops_SPGRA->texture[i] = _hoops_CPGRA->texture[i]) != null) {
				_hoops_GHGRA = true;
				_hoops_PRRH (_hoops_SPGRA->texture[i]);
			}
			_hoops_CCCIR = true;
			_hoops_SPGRA->_hoops_HRGRA &= ~HOOPS_READ_ONLY._hoops_SRGRA[i];
			if (i<_hoops_CRGRA &&
				!BIT(_hoops_CPGRA->_hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i])) {
				_hoops_RGAIR (_hoops_SPGRA->name[i]);
				_hoops_SPGRA->_hoops_PRGRA &= ~HOOPS_READ_ONLY._hoops_SRGRA[i];
			}
		}
		else {
			if (_hoops_SPGRA->texture[i] != null)
				_hoops_GHGRA = true;
		}
	}

	if (BIT (_hoops_CPGRA->_hoops_PRGRA, M_TRANSMISSION) && !BIT (_hoops_PCGS, M_TRANSMISSION)) {
		_hoops_SPGRA->_hoops_IRIR = _hoops_CPGRA->_hoops_IRIR;
		_hoops_CCCIR = true;
	}

	if (BIT (_hoops_CPGRA->_hoops_PRGRA, _hoops_RAGRA) && !BIT (_hoops_PCGS, _hoops_RAGRA)) {
		_hoops_SPGRA->gloss = _hoops_CPGRA->gloss;
		_hoops_CCCIR = true;
	}

	if (BIT (_hoops_CPGRA->_hoops_PRGRA, _hoops_AAGRA) && !BIT (_hoops_PCGS, _hoops_AAGRA)) {
		_hoops_SPGRA->_hoops_PAGRA = _hoops_CPGRA->_hoops_PAGRA;
		_hoops_CCCIR = true;
	}

	/* _hoops_CCPHR _hoops_IGPC, _hoops_PSP _hoops_RSIRR _hoops_HHPA */
	_hoops_RGAIR (_hoops_HPGRA->name);
	if (!ANYBIT (_hoops_SPGRA->_hoops_PRGRA, ~_hoops_CPGRA->_hoops_PRGRA)) {
		/* _hoops_CCGC _hoops_RASA, _hoops_SGH _hoops_CCAH _hoops_RSIRR */
		HI_Copy_Name (&_hoops_IPGRA->name, &_hoops_HPGRA->name);
	}

	_hoops_SPGRA->_hoops_PRGRA |= _hoops_CPGRA->_hoops_PRGRA;
	/* _hoops_PHGRA _hoops_RH _hoops_HHGRA'_hoops_GRI _hoops_IHGRA _hoops_IIGR _hoops_PCPA _hoops_PSHA _hoops_CGH _hoops_SHH _hoops_SCSI, _hoops_HIH _hoops_RGAR
	 * _hoops_IH _hoops_RH _hoops_IGPC _hoops_SCH _hoops_CGISR _hoops_AHCA */
	_hoops_SPGRA->_hoops_HRGRA |= _hoops_CPGRA->_hoops_HRGRA;

	if (_hoops_GHGRA)
		_hoops_SPGRA->_hoops_PRGRA |= _hoops_CHGRA;
	else
		_hoops_SPGRA->_hoops_PRGRA &= ~_hoops_CHGRA;

	return	_hoops_CCCIR;
}

GLOBAL_FUNCTION void HI_Free_Colors (_hoops_ACSGA alter *list)
{
	while (list != null) {
		_hoops_ACSGA alter *	tmp = (_hoops_ACSGA alter *)list;

		list = list->next;
		switch (tmp->type) {
			case _hoops_SHGRA: {
				_hoops_PCSGA *	find = (_hoops_PCSGA*)tmp;
				FREE (find, _hoops_PCSGA);
			}	break;

			case _hoops_PPCA: {
				_hoops_APCA *	_hoops_IRPA = (_hoops_APCA *)tmp;
				_hoops_RGAIR (_hoops_IRPA->name);
				FREE (_hoops_IRPA, _hoops_APCA);
			}	break;

			case _hoops_GIGRA: {
				_hoops_HCSGA *	_hoops_RIGRA = (_hoops_HCSGA *)tmp;
				HI_Free_Material_Names (&_hoops_RIGRA->_hoops_ISHIR, 1);
				_hoops_RGAIR (_hoops_RIGRA->name);
				FREE (_hoops_RIGRA, _hoops_HCSGA);
			}	break;
		}
	}
}

GLOBAL_FUNCTION _hoops_ACSGA * HI_Copy_Colors (
	_hoops_ACSGA const *		_hoops_AIGRA,
	_hoops_RHAH const *		_hoops_SPRAR,
	_hoops_PIGRA const *	locks) {
	_hoops_ACSGA *			first = null;
	_hoops_ACSGA **			_hoops_ASRGR = &first;

	if (_hoops_AIGRA != null) do {
		Color_Object		_hoops_GHA = _hoops_AIGRA->_hoops_GHA;
		_hoops_ACSGA *		_hoops_AARGA = null;

		switch (_hoops_AIGRA->type) {
			case _hoops_SHGRA: {
				_hoops_PCSGA const *	_hoops_HIGRA = (_hoops_PCSGA const *)_hoops_AIGRA;

				if (_hoops_SPRAR == null || (int)_hoops_HIGRA->value > _hoops_SPRAR->length) {
					if (locks != null && locks->color != 0) {
						for (int i=0; i<_hoops_IIGRA; i++)
							if (ALLBITS(locks->_hoops_HAA[i], _hoops_CIGRA))
								_hoops_GHA &= ~(1 << i);
					}

					if (_hoops_GHA != 0) {
						_hoops_PCSGA *		findex;

						/* _hoops_RGAR _hoops_HS _hoops_RH _hoops_SIGRA _hoops_IS _hoops_RIH _hoops_IGIAR */
						ZALLOC (findex, _hoops_PCSGA);
						findex->value = _hoops_HIGRA->value;

						_hoops_AARGA = findex;
					}
				}
				else {
					Named_Material const *	_hoops_SPGRA = (Named_Material const *)&_hoops_SPRAR->_hoops_HAA[(int)_hoops_HIGRA->value];

					if (locks != null && locks->color != 0) {
						for (int i=0; i<_hoops_IIGRA; i++) {
							_hoops_ARGRA		_hoops_PRGRA = _hoops_SPGRA->_hoops_PRGRA;
							_hoops_ARGRA		textures = _hoops_PRGRA & ~_hoops_CIGRA;

							_hoops_PRGRA &= _hoops_CIGRA;
							_hoops_PRGRA |= textures >> 8;

							if (ALLBITS(locks->_hoops_HAA[i], _hoops_PRGRA))
								_hoops_GHA &= ~(1 << i);
						}
					}

					if (_hoops_GHA != 0) {
						/* _hoops_GCGRA _hoops_CCA _hoops_RCGRA _hoops_ARCR _hoops_RARP */
						_hoops_HCSGA *		_hoops_ICSGA;

						ZALLOC (_hoops_ICSGA, _hoops_HCSGA);
						HI_Copy_Named_Material (_hoops_SPGRA, &_hoops_ICSGA->_hoops_ISHIR);
						_hoops_AARGA = _hoops_ICSGA;
					}
				}
			}	break;

			default:
			case _hoops_PPCA: {
				if (locks != null && locks->color != 0) {
					for (int i=0; i<_hoops_IIGRA; i++)
						if (BIT(locks->_hoops_HAA[i], M_DIFFUSE))
							_hoops_GHA &= ~(1 << i);
				}

				if (_hoops_GHA != 0) {
					_hoops_APCA const *	_hoops_ACGRA = (_hoops_APCA const *)_hoops_AIGRA;
					_hoops_APCA *			normal;

					ZALLOC (normal, _hoops_APCA);
					normal->rgb = _hoops_ACGRA->rgb;
					HI_Copy_Name (&_hoops_ACGRA->name, &normal->name);

					_hoops_AARGA = normal;
				}
			}	break;

			case _hoops_GIGRA: {
				_hoops_HCSGA const *	_hoops_PCGRA = (_hoops_HCSGA const *)_hoops_AIGRA;

				if (locks != null && locks->color != 0) {
					for (int i=0; i<_hoops_IIGRA; i++) {
						_hoops_ARGRA		_hoops_PRGRA = _hoops_PCGRA->_hoops_ISHIR._hoops_PRGRA;
						_hoops_ARGRA		textures = _hoops_PRGRA & ~_hoops_CIGRA;

						_hoops_PRGRA &= _hoops_CIGRA;
						_hoops_PRGRA |= textures >> 8;

						if (ALLBITS(locks->_hoops_HAA[i], _hoops_PRGRA))
							_hoops_GHA &= ~(1 << i);
					}
				}

				if (_hoops_GHA != 0) {
					_hoops_HCSGA *			_hoops_ICSGA;

					ZALLOC (_hoops_ICSGA, _hoops_HCSGA);
					HI_Copy_Named_Material (&_hoops_PCGRA->_hoops_ISHIR, &_hoops_ICSGA->_hoops_ISHIR);
					HI_Copy_Name (&_hoops_PCGRA->name, &_hoops_ICSGA->name);
					_hoops_AARGA = (_hoops_ACSGA *)_hoops_ICSGA;
				}
			}	break;
		}

		if (_hoops_AARGA != null) {
			*_hoops_ASRGR = _hoops_AARGA;
			_hoops_ASRGR = &_hoops_AARGA->next;

			_hoops_AARGA->type = _hoops_AIGRA->type;
			_hoops_AARGA->_hoops_GHA = _hoops_GHA;
		}
	} while ((_hoops_AIGRA = _hoops_AIGRA->next) != null);

	*_hoops_ASRGR = null;
	return first;
}


GLOBAL_FUNCTION void HI_Merge_Colors (
	_hoops_SSGI alter *			original,
	_hoops_ACSGA const *		_hoops_AARGA,
	_hoops_PIGRA const *	locks,
	_hoops_RHAH const *		_hoops_SPRAR) {
	_hoops_ACSGA *			_hoops_AIGRA;
	_hoops_ACSGA *			_hoops_HCGRA;
	_hoops_ACSGA *			tmp = null;

	/* _hoops_IH _hoops_GRR _hoops_HAIR _hoops_GGR _hoops_CCAH _hoops_HIGR
	**	_hoops_AGSGR _hoops_PSAP _hoops_CARA _hoops_SIH _hoops_ICGRA _hoops_RHGS _hoops_HIGR _hoops_RPP _hoops_CCGRA
	**	_hoops_RPP _hoops_APRS _hoops_PIS _hoops_HAIR	_hoops_HASC _hoops_GGR _hoops_GII _hoops_CCAH _hoops_SIH
	**	_hoops_SHS	_hoops_SSS _hoops_RHPA _hoops_IS _hoops_SGH _hoops_PAR _hoops_CCPP _hoops_CCAH
	**	_hoops_GGCH _hoops_AGSAR & _hoops_HGAS _hoops_IAR
	*/

	if (_hoops_AARGA != null) do {
		Color_Object			_hoops_SCGRA = _hoops_AARGA->_hoops_GHA;

		// _hoops_SRS _hoops_HHSP _hoops_GII _hoops_AGSAR _hoops_SGS _hoops_CHR _hoops_CCGC _hoops_PCPAR
		switch (_hoops_AARGA->type) {
			case _hoops_PPCA: {
				if (locks != null && locks->color != 0) {
					for (int i=0; i<_hoops_IIGRA; i++)
						if (BIT(locks->_hoops_HAA[i], M_DIFFUSE))
							_hoops_SCGRA &= ~(1 << i);
				}
			}	break;

			case _hoops_SHGRA: {
				_hoops_PCSGA const *	_hoops_GSGRA = (_hoops_PCSGA const *)_hoops_AARGA;

				if (_hoops_SPRAR == null || (int)_hoops_GSGRA->value > _hoops_SPRAR->length) {
					if (locks != null && locks->color != 0) {
						for (int i=0; i<_hoops_IIGRA; i++)
							if (ALLBITS(locks->_hoops_HAA[i], _hoops_CIGRA))
								_hoops_SCGRA &= ~(1 << i);
					}
				}
				else {
					Named_Material const *	_hoops_CPGRA = (Named_Material const *)&_hoops_SPRAR->_hoops_HAA[(int)_hoops_GSGRA->value];

					if (locks != null && locks->color != 0) {
						for (int i=0; i<_hoops_IIGRA; i++) {
							_hoops_ARGRA		_hoops_PRGRA = _hoops_CPGRA->_hoops_PRGRA;
							_hoops_ARGRA		textures = _hoops_PRGRA & ~_hoops_CIGRA;

							_hoops_PRGRA &= _hoops_CIGRA;
							_hoops_PRGRA |= textures >> 8;

							if (ALLBITS(locks->_hoops_HAA[i], _hoops_PRGRA))
								_hoops_SCGRA &= ~(1 << i);
						}
					}
				}
			}	break;

			case _hoops_GIGRA: {
				_hoops_HCSGA const *	_hoops_RSGRA = (_hoops_HCSGA const *)_hoops_AARGA;

				if (locks != null && locks->color != 0) {
					for (int i=0; i<_hoops_IIGRA; i++) {
						_hoops_ARGRA		_hoops_PRGRA = _hoops_RSGRA->_hoops_ISHIR._hoops_PRGRA;
						_hoops_ARGRA		textures = _hoops_PRGRA & ~_hoops_CIGRA;

						_hoops_PRGRA &= _hoops_CIGRA;
						_hoops_PRGRA |= textures >> 8;

						if (ALLBITS(locks->_hoops_HAA[i], _hoops_PRGRA))
							_hoops_SCGRA &= ~(1 << i);
					}
				}
			}	break;
		}

		if (_hoops_SCGRA != 0) do {
			Color_Object			_hoops_GHA, _hoops_ASGRA, used;
			_hoops_ARGRA		_hoops_PCGS = 0;

			_hoops_GHA = _hoops_SCGRA;	// _hoops_HPCAR _hoops_HCR (_hoops_GSSR _hoops_AGIR _hoops_SIHH _hoops_SGHS)

			if (locks != null && locks->color != Color_NONE) {
				int	_hoops_PSGRA = -1;

				// _hoops_SSS _hoops_SRS _hoops_CARA _hoops_HSGRA (_hoops_ISGRA, _hoops_CSGRA)
				for (int i=0; i<_hoops_SSGRA; i++) {
					if (BIT (_hoops_SCGRA, 1 << i)) {
						_hoops_PSGRA = i;
						break;
					}
				}
				// _hoops_PPR _hoops_GII _hoops_GGRRA _hoops_IHIA _hoops_CCA _hoops_SCH
				_hoops_PCGS = locks->_hoops_HAA[_hoops_PSGRA];

				// _hoops_SR'_hoops_GCPP _hoops_RGHH _hoops_RGR _hoops_CARA
				_hoops_GHA = 1 << _hoops_PSGRA;
				// _hoops_PPR _hoops_GII _hoops_SGS _hoops_AAHS _hoops_RH _hoops_PSHR _hoops_PPRRR
				for (int i=_hoops_PSGRA+1; i<_hoops_SSGRA; i++) {
					if (BIT (_hoops_SCGRA, 1 << i) && locks->_hoops_HAA[i] == _hoops_PCGS) {
						_hoops_GHA |= 1 << i;
					}
				}
			}

			_hoops_ASGRA = _hoops_GHA;

			used = _hoops_IHGPR;
			_hoops_HCGRA = null;

			if ((_hoops_AIGRA = original->colors) != null) do {
				// _hoops_GSRS _hoops_HCR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_RGRRA _hoops_IIGR _hoops_CIPSR *_hoops_ASSA* _hoops_RH _hoops_PPS
				_hoops_PCSGA const *	_hoops_AGRRA = (_hoops_PCSGA const *)_hoops_AIGRA;
				_hoops_APCA const *	old_normal = (_hoops_APCA const *)_hoops_AIGRA;
				_hoops_HCSGA const *	_hoops_PGRRA = (_hoops_HCSGA const *)_hoops_AIGRA;
				_hoops_PCSGA const *	new_findex = (_hoops_PCSGA const *)_hoops_AARGA;
				_hoops_APCA const *	new_normal = (_hoops_APCA const *)_hoops_AARGA;
				_hoops_HCSGA const *	new_general = (_hoops_HCSGA const *)_hoops_AARGA;

				/* _hoops_RPP _hoops_HSH _hoops_CHR _hoops_RH _hoops_PSHR, _hoops_SAHR _hoops_HASC _hoops_RH _hoops_CCAH _hoops_AGSAR _hoops_GGR */
				if (_hoops_AARGA->type == _hoops_AIGRA->type &&
					((_hoops_AARGA->type == _hoops_SHGRA &&
					  new_findex->value == _hoops_AGRRA->value) ||
					 (_hoops_AARGA->type == _hoops_PPCA &&
					  new_normal->name.length == 0 &&
					  new_normal->rgb == old_normal->rgb) ||
					 (_hoops_AARGA->type == _hoops_GIGRA &&
					  (new_general->name.length == 0 ||
					   _hoops_RAHSR (new_general->name, _hoops_PGRRA->name)) &&
					  HI_Named_Materials_Equal (&new_general->_hoops_ISHIR,
												&_hoops_PGRRA->_hoops_ISHIR)))) {
					/* _hoops_IRS _hoops_PSSP!! _hoops_PIP, _hoops_HGRRA, _hoops_SGS _hoops_AGSAR _hoops_IHIA _hoops_CCA
					 * _hoops_RH _hoops_CCAH _hoops_RGSR _hoops_SIAS _hoops_SHH _hoops_HSGRA _hoops_IGRRA _hoops_GGR _hoops_RH _hoops_HIGR,
					 * _hoops_HIS _hoops_RIIA _hoops_IIGR _hoops_GHGA _hoops_PA _hoops_ARI, _hoops_SR _hoops_SAHR _hoops_PCSA
					 * _hoops_RGR _hoops_SPR, _hoops_PPR _hoops_RAS _hoops_HCHAR _hoops_HPGR _hoops_CPS _hoops_SHS, _hoops_SR
					 * _hoops_PAH _hoops_HASC _hoops_GGR _hoops_GII _hoops_AGSAR _hoops_HAR _hoops_IAII _hoops_GIR */

					_hoops_HCGRA = _hoops_AIGRA;
					_hoops_GHA &= ~_hoops_AIGRA->_hoops_GHA;
				}
				else if (ANYBIT (_hoops_AIGRA->_hoops_GHA, _hoops_GHA)) {
					/* _hoops_RGR _hoops_SAGGR _hoops_CGRRA, _hoops_GAR _hoops_SGRRA _hoops_HHS _hoops_GHPP _hoops_GGR _hoops_HRHAR
					 * _hoops_CRGR _hoops_GRRRA _hoops_AIRP:
					 *		  _hoops_AGSAR _hoops_GGR _hoops_PPCAR - _hoops_HASC _hoops_IIGR _hoops_AIRC
					 *		  _hoops_RHGS _hoops_HIH _hoops_HAR _hoops_CCAH - _hoops_RHGS _hoops_AIRC
					 *		  _hoops_CCAH _hoops_HIH _hoops_HAR _hoops_RHGS - _hoops_CCAH _hoops_AIRC
					 *
					 *		  _hoops_IH _hoops_RRRRA:
					 *				_hoops_RHGS == _hoops_III=_hoops_HSP = _hoops_ARRRA _hoops_PRRRA
					 *				_hoops_CCAH == _hoops_HSP=_hoops_GPIA = _hoops_RRH _hoops_HRRRA
					 *				_hoops_ACPP:
					 *						_hoops_HSP = _hoops_ARRRA _hoops_RRH _hoops_HRRRA
					 *						_hoops_III = _hoops_ARRRA _hoops_PRRRA
					 *						_hoops_GPIA = _hoops_RRH _hoops_HRRRA
					 */
					_hoops_ACSGA const *		_hoops_IRRRA = _hoops_AARGA;
					Color_Object			_hoops_CRRRA = _hoops_AIGRA->_hoops_GHA;
					_hoops_HCSGA			_hoops_SRRRA;

					/** "_hoops_AGSAR _hoops_GGR _hoops_PPCAR" -- _hoops_CGIC _hoops_GARRA _hoops_GPRR & _hoops_RARRA **/
					switch (_hoops_AARGA->type) {
						case _hoops_PPCA: {
							_hoops_APCA const *		new_normal = (_hoops_APCA const *)_hoops_AARGA;

							if (_hoops_AIGRA->type != _hoops_GIGRA) {
								_hoops_APCA *	normal;

								/* _hoops_GAGPR _hoops_SGH _hoops_CCAH _hoops_RGSR */

								ZALLOC (normal, _hoops_APCA);
								normal->rgb = new_normal->rgb;
								HI_Copy_Name (&new_normal->name, &normal->name);
								normal->type = _hoops_PPCA;

								tmp = normal;
							}
							else {
								_hoops_HCSGA *			_hoops_ICSGA;

								/* _hoops_HASC _hoops_GAR _hoops_CCAH _hoops_SPI _hoops_IAPR _hoops_RHGS _hoops_RGSR */

								ZALLOC (_hoops_ICSGA, _hoops_HCSGA);
								HI_Copy_Named_Material (&((_hoops_HCSGA *)_hoops_AIGRA)->_hoops_ISHIR,
															&_hoops_ICSGA->_hoops_ISHIR);
								/* _hoops_PSP "_hoops_APSR" _hoops_RSIRR _hoops_RAS _hoops_AARRA */
								_hoops_ICSGA->name.length = 0;
								_hoops_ICSGA->name.text = null;
								_hoops_ICSGA->_hoops_ISHIR._hoops_CSHR = new_normal->rgb;
								if (_hoops_ICSGA->_hoops_ISHIR._hoops_SCA) {
									HI_Free_Diffuse_Channel_List (_hoops_ICSGA->_hoops_ISHIR._hoops_SCA);
									_hoops_ICSGA->_hoops_ISHIR._hoops_SCA = null;
								}
								_hoops_RGAIR (_hoops_ICSGA->_hoops_ISHIR._hoops_IRGRA);
								HI_Copy_Name (&new_normal->name, &_hoops_ICSGA->_hoops_ISHIR._hoops_IRGRA);
								_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA |= M_DIFFUSE;
								_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA &= ~_hoops_RHGRA;
								_hoops_ICSGA->_hoops_ISHIR._hoops_HRGRA |= M_DIFFUSE;
								_hoops_ICSGA->type = _hoops_GIGRA;

								tmp = _hoops_ICSGA;
							}
						}	break;

						case _hoops_SHGRA: {
							_hoops_PCSGA const *	new_findex = (_hoops_PCSGA const *)_hoops_AARGA;

							if (_hoops_SPRAR == null || (int)new_findex->value > _hoops_SPRAR->length) {
								_hoops_PCSGA *		findex;

								/* _hoops_SAHR _hoops_SGH _hoops_CCAH _hoops_RGSR */
								ZALLOC (findex, _hoops_PCSGA);
								findex->value = new_findex->value;
								findex->type = _hoops_SHGRA;

								tmp = (_hoops_ACSGA *)findex;
								break;
							}
							else {
								/* _hoops_IRAA _hoops_RH _hoops_ARCR _hoops_RARP _hoops_PPR _hoops_CAHAR _hoops_SR _hoops_RIAGR _hoops_IRS _hoops_RHAR _hoops_HAIR _hoops_GGR _hoops_RH _hoops_SRS _hoops_HGHC */
								HI_Copy_Named_Material (&_hoops_SPRAR->_hoops_HAA[(int)new_findex->value],
														&_hoops_SRRRA._hoops_ISHIR);
								_hoops_SRRRA.type = _hoops_GIGRA;
								_hoops_SRRRA._hoops_GHA = _hoops_AARGA->_hoops_GHA;
								_hoops_IRRRA = (_hoops_ACSGA const *)&_hoops_SRRRA;
								/* _hoops_HSSC _hoops_RHIR _hoops_IS _hoops_RHAR _hoops_PHSPR _hoops_IIGR _hoops_RH _hoops_ARCR _hoops_RARP */
							}
						}	_hoops_HHHI;

						case _hoops_GIGRA: {
							_hoops_HCSGA const *	new_general = (_hoops_HCSGA const *)_hoops_IRRRA;
							_hoops_HCSGA *			_hoops_ICSGA;

							ZALLOC (_hoops_ICSGA, _hoops_HCSGA);
							_hoops_ICSGA->type = _hoops_GIGRA;

							switch (_hoops_AIGRA->type) {
								case _hoops_SHGRA: {
									/* _hoops_SAHR _hoops_SGH _hoops_CCAH _hoops_SPR */
									HI_Copy_Named_Material (&new_general->_hoops_ISHIR,
															&_hoops_ICSGA->_hoops_ISHIR);
									if (_hoops_IRRRA == _hoops_AARGA)
										HI_Copy_Name (&new_general->name, &_hoops_ICSGA->name);
								}	break;

								case _hoops_PPCA: {
									/* _hoops_SGH _hoops_CCAH _hoops_SPR, _hoops_GRHP _hoops_RHGS _hoops_GAR _hoops_SPI _hoops_RPP
									 * _hoops_CCAH _hoops_ASSP'_hoops_RA _hoops_HS _hoops_SPR
									 */
									HI_Copy_Named_Material (&new_general->_hoops_ISHIR,
																&_hoops_ICSGA->_hoops_ISHIR);
									if (ANYBIT (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA, M_DIFFUSE)) {
										if (_hoops_IRRRA == _hoops_AARGA)
											HI_Copy_Name (&new_general->name, &_hoops_ICSGA->name);
									}
									else {
										_hoops_APCA const *	old_normal = (_hoops_APCA const *)_hoops_AIGRA;

										_hoops_ICSGA->_hoops_ISHIR._hoops_CSHR = old_normal->rgb;
										HI_Copy_Name (&old_normal->name, &_hoops_ICSGA->_hoops_ISHIR._hoops_IRGRA);
										_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA |= M_DIFFUSE|_hoops_RHGRA;
										if (!ANYBIT (new_general->_hoops_ISHIR._hoops_PRGRA, M_DIFFUSE|_hoops_RHGRA))
											_hoops_ICSGA->_hoops_ISHIR._hoops_HRGRA |= M_DIFFUSE;
									}
								}	break;

								case _hoops_GIGRA: {
									/* _hoops_HASC _hoops_CCAH _hoops_CIAA _hoops_IPS _hoops_IIGR _hoops_RHGS */
									HI_Copy_Named_Material (&((_hoops_HCSGA const *)_hoops_AIGRA)->_hoops_ISHIR,
																&_hoops_ICSGA->_hoops_ISHIR);
									if (_hoops_IRRRA == _hoops_AARGA)
										HI_Copy_Name (&new_general->name, &_hoops_ICSGA->name);
									_hoops_PPGRA (_hoops_ICSGA, new_general, _hoops_PCGS);
								}	break;
							}

							if (_hoops_IRRRA != _hoops_AARGA)
								HI_Free_Material_Names (&_hoops_SRRRA._hoops_ISHIR, 1);

							tmp = (_hoops_ACSGA *)_hoops_ICSGA;
						}	break;
					}

					original->_hoops_CCCIR |= _hoops_GHA;
					original->_hoops_GHA |= _hoops_GHA;


					tmp->next = _hoops_AIGRA->next;
					_hoops_AIGRA->next = tmp;

					tmp->_hoops_GHA = _hoops_AIGRA->_hoops_GHA & _hoops_GHA;

					/** "_hoops_RHGS _hoops_HIH _hoops_HAR _hoops_CCAH" -- _hoops_RHGS _hoops_HIGR _hoops_IGCI **/
					_hoops_AIGRA->_hoops_GHA &= ~_hoops_GHA;

					/* _hoops_GCHGA */
					_hoops_AIGRA = tmp;


					/** "_hoops_CCAH _hoops_HIH _hoops_HAR _hoops_RHGS" _hoops_GIR _hoops_GAR _hoops_SHIR (_hoops_PARRA) _hoops_AGIR **/
					_hoops_GHA &= ~_hoops_CRRRA;
					used |= _hoops_CRRRA;
				}
				else {
					/* _hoops_IRHH _hoops_RCRR _hoops_GII _hoops_AGSAR _hoops_AIAH _hoops_AGCA _hoops_CHR _hoops_RHSI _hoops_HII
					 * _hoops_SPHR _hoops_HAIR _hoops_AIRP */
					_hoops_AIGRA->_hoops_GHA &= ~used;
				}
			} while ((_hoops_AIGRA = _hoops_AIGRA->next) != null);

			if (_hoops_GHA != Color_NONE) {
				if (_hoops_HCGRA != null) {
					/* _hoops_GAGPR _hoops_HASC _hoops_CRGR _hoops_RH _hoops_HGHC _hoops_SR _hoops_HARRA _hoops_IARRA */
					_hoops_HCGRA->_hoops_GHA |= _hoops_GHA;
				}
				else {
					/* _hoops_RRP _hoops_IRS _hoops_SHSC _hoops_CCAH _hoops_CARRA */
					switch (_hoops_AARGA->type) {
						case _hoops_PPCA: {
							_hoops_APCA const *	new_normal = (_hoops_APCA const *)_hoops_AARGA;
							_hoops_APCA *			normal;

							ZALLOC (normal, _hoops_APCA);
							normal->rgb = new_normal->rgb;
							HI_Copy_Name (&new_normal->name, &normal->name);

							tmp = normal;
						}	break;

						case _hoops_SHGRA: {
							_hoops_PCSGA const *	new_findex = (_hoops_PCSGA const *)_hoops_AARGA;

							if (_hoops_SPRAR == null || (int)new_findex->value > _hoops_SPRAR->length) {
								_hoops_PCSGA *		findex;

								/* _hoops_PAH _hoops_RGAR _hoops_SGH _hoops_RH _hoops_SIGRA */
								ZALLOC (findex, _hoops_PCSGA);
								findex->value = new_findex->value;

								tmp = findex;
							}
							else {
								_hoops_HCSGA *		_hoops_ICSGA;

								/* _hoops_SGH _hoops_RH _hoops_ARCR _hoops_RARP */
								ZALLOC (_hoops_ICSGA, _hoops_HCSGA);
								HI_Copy_Named_Material (&_hoops_SPRAR->_hoops_HAA[(int)new_findex->value],
															&_hoops_ICSGA->_hoops_ISHIR);
								tmp = _hoops_ICSGA;
							}
						}	break;

						case _hoops_GIGRA: {
							_hoops_HCSGA const *	new_general = (_hoops_HCSGA const *)_hoops_AARGA;
							_hoops_HCSGA *			_hoops_ICSGA;

							ZALLOC (_hoops_ICSGA, _hoops_HCSGA);
							HI_Copy_Named_Material (&new_general->_hoops_ISHIR, &_hoops_ICSGA->_hoops_ISHIR);
							HI_Copy_Name (&new_general->name, &_hoops_ICSGA->name);

							tmp = _hoops_ICSGA;
						}	break;
					}
					tmp->next = original->colors;
					original->colors = tmp;

					tmp->type = _hoops_AARGA->type;
					tmp->_hoops_GHA = _hoops_GHA;
				}

				original->_hoops_GHA |= _hoops_GHA;
				original->_hoops_CCCIR |= _hoops_GHA;
			}

			_hoops_SCGRA &= ~_hoops_ASGRA;
		} while (_hoops_SCGRA != 0);
	} while ((_hoops_AARGA = _hoops_AARGA->next) != null);

	/* _hoops_HASIR _hoops_GII _hoops_RHPA _hoops_HIGR _hoops_IAGH */

	_hoops_ACSGA ** _hoops_SARRA = &original->colors;
	do {
		tmp = *_hoops_SARRA;
		if (tmp->_hoops_GHA == Color_NONE) {
			*_hoops_SARRA = tmp->next;
			tmp->next = null;
			HI_Free_Colors (tmp);
		}
		else
			_hoops_SARRA = &tmp->next;
	} while (*_hoops_SARRA != null);
}

local Attribute * _hoops_GPRRA (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH alter *			item,
	Attribute const *			_hoops_CPACR,
	Attribute alter *			_hoops_SPACR)
{
	_hoops_SSGI const *				_hoops_RPRRA = (_hoops_SSGI const *)_hoops_CPACR;
	_hoops_SSGI alter *				_hoops_APRRA = (_hoops_SSGI alter *)_hoops_SPACR;
	
	if (_hoops_RPRRA != null) {

		_hoops_ACSGA * _hoops_PPRRA = _hoops_APRRA->colors;

		_hoops_APRRA->colors = HI_Copy_Colors (_hoops_RPRRA->colors, null);
		_hoops_APRRA->_hoops_RRHH = _hoops_RPRRA->_hoops_RRHH;
		_hoops_APRRA->_hoops_GHA = _hoops_RPRRA->_hoops_GHA;
		_hoops_APRRA->_hoops_CCCIR = _hoops_RPRRA->_hoops_CCCIR;

		HI_Merge_Colors (_hoops_APRRA, _hoops_PPRRA, null, null);

		HI_Free_Colors (_hoops_PPRRA);

		if (_hoops_APRRA->_hoops_CCCIR == Color_NONE)
			return null; /* _hoops_PSP _hoops_AGRP! */
	}

	_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
	while(_hoops_SRCP != null && _hoops_SRCP->type != _hoops_IRCP)
		_hoops_SRCP = _hoops_SRCP->owner;

	if (_hoops_SRCP != null) {

		if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPRRA))
			HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_HPRRA);

		if (item->type >= _hoops_AHRIR && item->type <= _hoops_PHRIR)
			HI_Invalidate_Segment_Display_Lists (_hoops_RIGC, _hoops_SRCP, -2, (Geometry *)item, 0);
	}

	return	_hoops_APRRA;
}

GLOBAL_FUNCTION bool HI_Set_Color(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_SSGI *					color) 
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_COLOR, _hoops_GPRRA, color);
}


GLOBAL_FUNCTION bool HI_Set_Color(
	_hoops_AIGPR *	_hoops_RIGC, 
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR,
	_hoops_SSGI *					color)
{
	_hoops_ICIIR(_hoops_RIGC);

	ASSERT (_hoops_GCRIR == _hoops_SCRIR || 
			_hoops_GCRIR == _hoops_ICRIR || 
			_hoops_GCRIR == _hoops_GSRIR || 
			_hoops_GCRIR == _hoops_CCRIR);

	ASSERT(color->colors != null);

#ifdef _hoops_GCGHR
	_hoops_IRPPR ("Geometry Color Attributes");
#else

	_hoops_ACSGA const *	colors = color->colors;

	do {

		_hoops_PCSGA const *	_hoops_CPRRA = null;

		_hoops_ACGHR	index = 0.0f;
		RGB					rgb;

		switch (colors->type) {
			case _hoops_SHGRA: {
				_hoops_CPRRA = (_hoops_PCSGA const *)colors;
				index = _hoops_CPRRA->value;
				rgb = _hoops_GPSR::_hoops_RPSR;
			}	break;

			case _hoops_PPCA: {
				_hoops_APCA const * _hoops_SPRRA = (_hoops_APCA const *)colors;
				index = 0.0f;
				rgb = _hoops_SPRRA->rgb;
			}	break;

			case _hoops_GIGRA: {
				_hoops_HCSGA const * _hoops_GHRRA = (_hoops_HCSGA const *)colors;
				index = 0.0f;
				rgb = _hoops_GHRRA->_hoops_ISHIR._hoops_CSHR;

				if ((ANYBIT (_hoops_GHRRA->_hoops_ISHIR._hoops_PRGRA, ~(M_DIFFUSE|_hoops_RHGRA)) ||
					 _hoops_GHRRA->_hoops_ISHIR._hoops_SCA != null))
					HE_ERROR (HEC_COLOR, HES_NO_DIFFUSE_COLOR_COMPONENT,
					   "Only the diffuse color may be set within a mesh or shell.");
			}	break;

			default: ASSERT(0); break;
		}


		/* _hoops_RHRRA: _hoops_CGH _hoops_CPSA _hoops_CIH _hoops_CCGC "_hoops_AHRRA" _hoops_SIRGR */

		if (_hoops_GCRIR == _hoops_SCRIR) {

			if (_hoops_IPRI->type == _hoops_CSIP) {
				PolyCylinder alter *		_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;
				_hoops_AGHIR *	_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;

				if (ANYBIT (colors->_hoops_GHA, ~(Color_EDGE|Color_FACE)))
					HE_WARNING (HEC_COLOR, HES_CANNOT_SET_ATTRIBUTE,
						"Only a 'face', or 'edge' color may be set within a polycylinder vertex");

				if (_hoops_CPRRA != null) {

					_hoops_ACGHR *	_hoops_PHRRA;
					_hoops_ACGHR *	_hoops_HHRRA;

					if (BIT (colors->_hoops_GHA, Color_EDGE)) {
						if (_hoops_PGHIR == null)
							_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_IHRRA);
						else if (_hoops_PGHIR->_hoops_HGHIR == null) {
							if (BIT (colors->_hoops_GHA, Color_FRONT) && _hoops_PGHIR->_hoops_IGHIR != null)
								_hoops_PGHIR->_hoops_HGHIR = _hoops_PGHIR->_hoops_IGHIR;
							else
								_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_IHRRA);
						}
						else if (_hoops_PGHIR->_hoops_HGHIR == _hoops_PGHIR->_hoops_IGHIR &&
								 !BIT (colors->_hoops_GHA, Color_FRONT)) {
							/* _hoops_IHSA _hoops_HSSRR */
							_hoops_PGHIR->_hoops_HGHIR = (_hoops_ACGHR *)
								HI_Clone_Anything (_hoops_PGHIR->_hoops_HGHIR, _hoops_HSPIR->point_count * (long)sizeof(_hoops_ACGHR));
						}
						_hoops_PHRRA = &_hoops_PGHIR->_hoops_HGHIR[offset];
					}
					else
						_hoops_PHRRA = null;

					if (BIT (colors->_hoops_GHA, Color_FRONT)) {
						if (_hoops_PGHIR == null)
							_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_CHRRA);
						else if (_hoops_PGHIR->_hoops_IGHIR == null) {
							if (BIT (colors->_hoops_GHA, Color_EDGE) && _hoops_PGHIR->_hoops_HGHIR != null)
								_hoops_PGHIR->_hoops_IGHIR = _hoops_PGHIR->_hoops_HGHIR;
							else
								_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_CHRRA);
						}
						else if (_hoops_PGHIR->_hoops_IGHIR == _hoops_PGHIR->_hoops_HGHIR &&
								 !BIT (colors->_hoops_GHA, Color_EDGE)) {
							/* _hoops_IHSA _hoops_HSSRR */
							_hoops_PGHIR->_hoops_IGHIR = (_hoops_ACGHR *)
								HI_Clone_Anything (_hoops_PGHIR->_hoops_IGHIR, _hoops_HSPIR->point_count * (long)sizeof(_hoops_ACGHR));
						}
						_hoops_HHRRA = &_hoops_PGHIR->_hoops_IGHIR[offset];
					}
					else
						_hoops_HHRRA = null;

					_hoops_CGHIR *	flags = &_hoops_PGHIR->flags[offset];

					if ((_hoops_PHRRA == null ||
						 BIT (*flags, _hoops_IHRRA) && *_hoops_PHRRA == index) &&
						(_hoops_HHRRA == null ||
						 BIT (*flags, _hoops_CHRRA) && *_hoops_HHRRA == index))
						goto _hoops_PRSPR; /* _hoops_IRAHR */

					if (_hoops_PHRRA != null) {
						if (!BIT (*flags, _hoops_IHRRA)) {
							*flags |= _hoops_IHRRA;
							++_hoops_PGHIR->_hoops_CCHPR;
						}

						if (BIT (*flags, _hoops_SHRRA)) {
							*flags &= ~_hoops_SHRRA;
							--_hoops_PGHIR->_hoops_SCHPR;
							_hoops_PGHIR->ecolors[offset] = _hoops_GPSR::_hoops_RPSR;
						}

						*_hoops_PHRRA = index;
					}

					if (_hoops_HHRRA != null) {
						if (!BIT (*flags, _hoops_CHRRA)) {
							*flags |= _hoops_CHRRA;
							++_hoops_PGHIR->_hoops_SIRHR;
						}

						if (BIT (*flags, _hoops_GIRRA)) {
							*flags &= ~_hoops_GIRRA;
							--_hoops_PGHIR->_hoops_RCRHR;
							_hoops_PGHIR->fcolors[offset] = _hoops_GPSR::_hoops_RPSR;
						}

						*_hoops_HHRRA = index;
					}
				}
				else /* _hoops_CSSGR _hoops_HPP _hoops_PIRA */ {
					RGB *	_hoops_RIRRA;
					RGB *	_hoops_AIRRA;

					if (BIT (colors->_hoops_GHA, Color_EDGE)) {
						if (_hoops_PGHIR == null)
							_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_SHRRA);
						else if (_hoops_PGHIR->ecolors == null) {
							if (BIT (colors->_hoops_GHA, Color_FRONT) && _hoops_PGHIR->fcolors != null)
								_hoops_PGHIR->ecolors = _hoops_PGHIR->fcolors;
							else
								_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_SHRRA);
						}
						else if (_hoops_PGHIR->ecolors == _hoops_PGHIR->fcolors &&
								 !BIT (colors->_hoops_GHA, Color_FRONT)) {
							/* _hoops_IHSA _hoops_HSSRR */
							_hoops_PGHIR->ecolors = (RGB *)HI_Clone_Anything (_hoops_PGHIR->ecolors, _hoops_HSPIR->point_count * (long)sizeof(RGB));
						}
						_hoops_RIRRA = &_hoops_PGHIR->ecolors[offset];
					}
					else
						_hoops_RIRRA = null;

					if (BIT (colors->_hoops_GHA, Color_FRONT)) {
						if (_hoops_PGHIR == null)
							_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_GIRRA);
						else if (_hoops_PGHIR->fcolors == null) {
							if (BIT (colors->_hoops_GHA, Color_EDGE) && _hoops_PGHIR->ecolors != null)
								_hoops_PGHIR->fcolors = _hoops_PGHIR->ecolors;
							else
								_hoops_PGHIR = HI_Initialize_PCA_Vertex_Attributes (_hoops_HSPIR, _hoops_GIRRA);
						}
						else if (_hoops_PGHIR->fcolors == _hoops_PGHIR->ecolors &&
								 !BIT (colors->_hoops_GHA, Color_EDGE)) {
							/* _hoops_IHSA _hoops_HSSRR */
							_hoops_PGHIR->fcolors = (RGB *) HI_Clone_Anything (_hoops_PGHIR->fcolors, _hoops_HSPIR->point_count * (long)sizeof(RGB));
						}
						_hoops_AIRRA = &_hoops_PGHIR->fcolors[offset];
					}
					else
						_hoops_AIRRA = null;


					_hoops_CGHIR *	flags = &_hoops_PGHIR->flags[offset];

					if ((_hoops_RIRRA == null ||
						 BIT (*flags, _hoops_SHRRA) && *_hoops_RIRRA == rgb) &&
						(_hoops_AIRRA == null ||
						 BIT (*flags, _hoops_GIRRA) && *_hoops_AIRRA == rgb))
						goto _hoops_PRSPR; /* _hoops_IRAHR */

					if (_hoops_RIRRA != null) {
						if (!BIT (*flags, _hoops_SHRRA)) {
							*flags |= _hoops_SHRRA;
							++_hoops_PGHIR->_hoops_SCHPR;
						}

						if (BIT (*flags, _hoops_IHRRA)) {
							*flags &= ~_hoops_IHRRA;
							--_hoops_PGHIR->_hoops_CCHPR;
							_hoops_PGHIR->_hoops_HGHIR[offset] = 0.0f;
						}

						*_hoops_RIRRA = rgb;
					}

					if (_hoops_AIRRA != null) {
						if (!BIT (*flags, _hoops_GIRRA)) {
							*flags |= _hoops_GIRRA;
							++_hoops_PGHIR->_hoops_RCRHR;
						}

						if (BIT (*flags, _hoops_CHRRA)) {
							*flags &= ~_hoops_CHRRA;
							--_hoops_PGHIR->_hoops_SIRHR;
							_hoops_PGHIR->_hoops_IGHIR[offset] = 0.0f;
						}

						*_hoops_AIRRA = rgb;
					}
				}
			}
			else {

				if (ANYBIT (colors->_hoops_GHA, ~(Color_MARKER|Color_VERTEX|Color_EDGE|Color_FACE)))
					HE_WARNING (HEC_COLOR, HES_CANNOT_SET_ATTRIBUTE,
								"Only a 'marker'/'vertex', 'edge', or 'face' color may be set within a vertex");

				Local_Vertex_Attributes * _hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
				int _hoops_PIRRA = _hoops_SPRI->_hoops_HIRRA;

				/* _hoops_APSH _hoops_PII _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_HAIR _hoops_GPP _hoops_SAHR _hoops_SPR _hoops_GPHA, _hoops_HIS
					_hoops_SR'_hoops_GCPP _hoops_PAHH _hoops_RRP _hoops_IRS _hoops_IIRRA->_hoops_SGI _hoops_CRPR */

				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
					ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					for (int i = 0; i < _hoops_IPRI->point_count; i++)
						_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
				}

				if (_hoops_CPRRA != null) {
					_hoops_ACGHR *	_hoops_CIRRA = null;
					_hoops_ACGHR *	_hoops_PHRRA = null;
					_hoops_ACGHR *	_hoops_HHRRA = null;

					if (BIT (colors->_hoops_GHA, Color_VERTEX)) {
						if (_hoops_SPRI->_hoops_HAHIR == null) {
							if (BIT (colors->_hoops_GHA, Color_EDGE) && _hoops_SPRI->_hoops_HGHIR != null)
								_hoops_SPRI->_hoops_HAHIR = _hoops_SPRI->_hoops_HGHIR;
							else if (BIT (colors->_hoops_GHA, Color_FRONT) && _hoops_SPRI->_hoops_IGHIR != null)
								_hoops_SPRI->_hoops_HAHIR = _hoops_SPRI->_hoops_IGHIR;
							else
								HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_SIRRA, 0);
						}
						else {
							/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
							if (_hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_HGHIR &&
								_hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_IGHIR &&
								ANYBIT (colors->_hoops_GHA, Color_EDGE|Color_FRONT) &&
								!ALLBITS (colors->_hoops_GHA, Color_EDGE|Color_FRONT)) {
								/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
								if (!BIT (colors->_hoops_GHA, Color_EDGE)) {
									_hoops_SPRI->_hoops_HGHIR = (_hoops_ACGHR *)
										HI_Clone_Anything (_hoops_SPRI->_hoops_HGHIR, _hoops_IPRI->point_count * (long)sizeof(_hoops_ACGHR));
								}
								else /* _hoops_RPP (!_hoops_IRRC (_hoops_GCRRA->_hoops_HAIR._hoops_AGSAR, _hoops_RCRRA)) */ {
									_hoops_SPRI->_hoops_IGHIR = (_hoops_ACGHR *)
										HI_Clone_Anything (_hoops_SPRI->_hoops_IGHIR,
											(_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) *(long)sizeof(_hoops_ACGHR));
								}
							}
							else if (_hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_HGHIR &&
										!BIT (colors->_hoops_GHA, Color_EDGE) ||
									 _hoops_SPRI->_hoops_HAHIR == _hoops_SPRI->_hoops_IGHIR &&
										!BIT (colors->_hoops_GHA, Color_FRONT)) {
								/* _hoops_IHSA _hoops_HSSRR */
								_hoops_SPRI->_hoops_HAHIR = (_hoops_ACGHR *)
									HI_Clone_Anything (_hoops_SPRI->_hoops_HAHIR, _hoops_IPRI->point_count * (long)sizeof(_hoops_ACGHR));
							}
						}
						_hoops_CIRRA = &_hoops_SPRI->_hoops_HAHIR[offset];
					}

					if (BIT (colors->_hoops_GHA, Color_EDGE)) {
						if (_hoops_SPRI->_hoops_HGHIR == null) {
							if (BIT (colors->_hoops_GHA, Color_VERTEX) && _hoops_SPRI->_hoops_HAHIR != null)
								_hoops_SPRI->_hoops_HGHIR = _hoops_SPRI->_hoops_HAHIR;
							else if (BIT (colors->_hoops_GHA, Color_FRONT) && _hoops_SPRI->_hoops_IGHIR != null)
								_hoops_SPRI->_hoops_HGHIR = _hoops_SPRI->_hoops_IGHIR;
							else
								HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_RPHPR, 0);
						}
						else {
							/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
							if (_hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_HAHIR &&
								_hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_IGHIR &&
								ANYBIT (colors->_hoops_GHA, Color_VERTEX|Color_FRONT) &&
								!ALLBITS (colors->_hoops_GHA, Color_VERTEX|Color_FRONT)) {
								/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
								if (!BIT (colors->_hoops_GHA, Color_VERTEX)) {
									_hoops_SPRI->_hoops_HAHIR = (_hoops_ACGHR *)
										HI_Clone_Anything (_hoops_SPRI->_hoops_HAHIR, _hoops_IPRI->point_count * (long)sizeof(_hoops_ACGHR));
								}
								else /* _hoops_RPP (!_hoops_IRRC (_hoops_GCRRA->_hoops_HAIR._hoops_AGSAR, _hoops_RCRRA)) */ {
									_hoops_SPRI->_hoops_IGHIR = (_hoops_ACGHR *)
										HI_Clone_Anything (_hoops_SPRI->_hoops_IGHIR,
											(_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) * (long)sizeof(_hoops_ACGHR));
								}
							}
							else if (_hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_HAHIR &&
										!BIT (colors->_hoops_GHA, Color_VERTEX) ||
									 _hoops_SPRI->_hoops_HGHIR == _hoops_SPRI->_hoops_IGHIR &&
										!BIT (colors->_hoops_GHA, Color_FRONT)) {
								/* _hoops_IHSA _hoops_HSSRR */
								_hoops_SPRI->_hoops_HGHIR = (_hoops_ACGHR *)
									HI_Clone_Anything (_hoops_SPRI->_hoops_HGHIR, _hoops_IPRI->point_count * (long)sizeof(_hoops_ACGHR));
							}
						}
						_hoops_PHRRA = &_hoops_SPRI->_hoops_HGHIR[offset];
					}

					if (BIT (colors->_hoops_GHA, Color_FRONT)) {
						if (_hoops_SPRI->_hoops_IGHIR == null) {
							if (BIT (colors->_hoops_GHA, Color_EDGE) && _hoops_SPRI->_hoops_HGHIR != null)
								_hoops_SPRI->_hoops_IGHIR = _hoops_SPRI->_hoops_HGHIR;
							else if (BIT (colors->_hoops_GHA, Color_VERTEX) && _hoops_SPRI->_hoops_HAHIR != null)
								_hoops_SPRI->_hoops_IGHIR = _hoops_SPRI->_hoops_HAHIR;
							else
								HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_HARHR, 0);
						}
						else {
							/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
							if (_hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HAHIR &&
								_hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HGHIR &&
								ANYBIT (colors->_hoops_GHA, Color_VERTEX|Color_EDGE) &&
								!ALLBITS (colors->_hoops_GHA, Color_VERTEX|Color_EDGE)) {
								/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
								if (!BIT (colors->_hoops_GHA, Color_VERTEX)) {
									_hoops_SPRI->_hoops_HAHIR = (_hoops_ACGHR *)
										HI_Clone_Anything (_hoops_SPRI->_hoops_HAHIR, _hoops_IPRI->point_count * (long)sizeof(_hoops_ACGHR));
								}
								else /* _hoops_RPP (!_hoops_IRRC (_hoops_GCRRA->_hoops_HAIR._hoops_AGSAR, _hoops_ACRRA)) */ {
									_hoops_SPRI->_hoops_HGHIR = (_hoops_ACGHR *)
										HI_Clone_Anything (_hoops_SPRI->_hoops_HGHIR, _hoops_IPRI->point_count * (long)sizeof(_hoops_ACGHR));
								}
							}
							else if (_hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HAHIR &&
										!BIT (colors->_hoops_GHA, Color_VERTEX) ||
									 _hoops_SPRI->_hoops_IGHIR == _hoops_SPRI->_hoops_HGHIR &&
										!BIT (colors->_hoops_GHA, Color_EDGE)) {
								/* _hoops_IHSA _hoops_HSSRR */
								_hoops_SPRI->_hoops_IGHIR = (_hoops_ACGHR *)
									HI_Clone_Anything (_hoops_SPRI->_hoops_IGHIR,
										(_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) * (long)sizeof(_hoops_ACGHR));
							}
						}
						_hoops_HHRRA = &_hoops_SPRI->_hoops_IGHIR[offset];
					}


					Local_Vertex_Flags *	flags = _hoops_SPRI->_hoops_CHHPR(offset);

					if ((_hoops_CIRRA == null ||
						 BIT (*flags, _hoops_SIRRA) && *_hoops_CIRRA == index) &&
						(_hoops_PHRRA == null ||
						 BIT (*flags, _hoops_RPHPR) && *_hoops_PHRRA == index) &&
						(_hoops_HHRRA == null ||
						 BIT (*flags, _hoops_HARHR) && *_hoops_HHRRA == index))
						goto _hoops_PRSPR; /* _hoops_IRAHR */

					if (_hoops_CIRRA != null) {
						if (!BIT (*flags, _hoops_SIRRA)) {
							*flags |= _hoops_SIRRA;
							++_hoops_SPRI->_hoops_PCRRA;
						}
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;

						if (BIT (*flags, _hoops_HCRRA)) {
							*flags &= ~_hoops_HCRRA;
							--_hoops_SPRI->_hoops_ICRRA;
							_hoops_SPRI->_hoops_PAHIR[offset] = _hoops_GPSR::_hoops_RPSR;
							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
						}
						if (BIT (*flags, _hoops_CCRRA)) {
							*flags &= ~_hoops_CCRRA;
							--_hoops_SPRI->_hoops_HIRRA;
							_hoops_SPRI->_hoops_IAHIR[offset] = _hoops_CAHSR::_hoops_SAHSR;
							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_CCRRA;
						}

						*_hoops_CIRRA = index;
					}

					if (_hoops_PHRRA != null) {
						if (!BIT (*flags, _hoops_RPHPR)) {
							*flags |= _hoops_RPHPR;
							++_hoops_SPRI->_hoops_CCHPR;
						}
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;

						if (BIT (*flags, _hoops_PPHPR)) {
							*flags &= ~_hoops_PPHPR;
							--_hoops_SPRI->_hoops_SCHPR;
							_hoops_SPRI->ecolors[offset] = _hoops_GPSR::_hoops_RPSR;
							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
						}

						*_hoops_PHRRA = index;
					}

					if (_hoops_HHRRA != null) {
						if (!BIT (*flags, _hoops_HARHR)) {
							*flags |= _hoops_HARHR;
							++_hoops_SPRI->_hoops_SIRHR;
						}
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;

						if (BIT (*flags, _hoops_AARHR)) {
							*flags &= ~_hoops_AARHR;
							--_hoops_SPRI->_hoops_RCRHR;
							_hoops_SPRI->fcolors[offset] = _hoops_GPSR::_hoops_RPSR;
							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
						}

						*_hoops_HHRRA = index;
						_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
					}

					if (_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
						_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
						FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
						_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
						_hoops_SPRI->flags = 0;
					}
				}
				else /* _hoops_CSSGR _hoops_HPP _hoops_PIRA */ {
					RGB *	_hoops_GSRRA = null;
					RGB *	_hoops_RIRRA = null;
					RGB *	_hoops_AIRRA = null;

					if (BIT (colors->_hoops_GHA, Color_VERTEX)) {
						if (_hoops_SPRI->_hoops_PAHIR == null) {
							if (BIT (colors->_hoops_GHA, Color_EDGE) && _hoops_SPRI->ecolors != null)
								_hoops_SPRI->_hoops_PAHIR = _hoops_SPRI->ecolors;
							else if (BIT (colors->_hoops_GHA, Color_FRONT) && _hoops_SPRI->fcolors != null)
								_hoops_SPRI->_hoops_PAHIR = _hoops_SPRI->fcolors;
							else
								HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_HCRRA, 0);
						}
						else {
							/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
							if (_hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->ecolors &&
								_hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->fcolors &&
								ANYBIT (colors->_hoops_GHA, Color_EDGE|Color_FRONT) &&
								!ALLBITS (colors->_hoops_GHA, Color_EDGE|Color_FRONT)) {
								/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
								if (!BIT (colors->_hoops_GHA, Color_EDGE)) {
									_hoops_SPRI->ecolors = (RGB *)
										HI_Clone_Anything (_hoops_SPRI->ecolors, _hoops_IPRI->point_count * (long)sizeof(RGB));
								}
								else /* _hoops_RPP (!_hoops_IRRC (_hoops_GCRRA->_hoops_HAIR._hoops_AGSAR, _hoops_RCRRA)) */ {
									_hoops_SPRI->fcolors = (RGB *)
										HI_Clone_Anything (_hoops_SPRI->fcolors,
											(_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) * (long)sizeof(RGB));
								}
							}
							else if (_hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->ecolors &&
										!BIT (colors->_hoops_GHA, Color_EDGE) ||
									 _hoops_SPRI->_hoops_PAHIR == _hoops_SPRI->fcolors &&
										!BIT (colors->_hoops_GHA, Color_FRONT)) {
								/* _hoops_IHSA _hoops_HSSRR */
								_hoops_SPRI->_hoops_PAHIR = (RGB *)
									HI_Clone_Anything (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count * (long)sizeof(RGB));
							}
						}
						_hoops_GSRRA = &_hoops_SPRI->_hoops_PAHIR[offset];
					}

					if (BIT (colors->_hoops_GHA, Color_EDGE)) {
						if (_hoops_SPRI->ecolors == null) {
							if (BIT (colors->_hoops_GHA, Color_VERTEX) && _hoops_SPRI->_hoops_PAHIR != null)
								_hoops_SPRI->ecolors = _hoops_SPRI->_hoops_PAHIR;
							else if (BIT (colors->_hoops_GHA, Color_FRONT) && _hoops_SPRI->fcolors != null)
								_hoops_SPRI->ecolors = _hoops_SPRI->fcolors;
							else
								HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_PPHPR, 0);
						}
						else {
							/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
							if (_hoops_SPRI->ecolors == _hoops_SPRI->_hoops_PAHIR &&
								_hoops_SPRI->ecolors == _hoops_SPRI->fcolors &&
								ANYBIT (colors->_hoops_GHA, Color_VERTEX|Color_FRONT) &&
								!ALLBITS (colors->_hoops_GHA, Color_VERTEX|Color_FRONT)) {
								/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
								if (!BIT (colors->_hoops_GHA, Color_VERTEX)) {
									_hoops_SPRI->_hoops_PAHIR = (RGB *)
										HI_Clone_Anything (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count * (long)sizeof(RGB));
								}
								else /* _hoops_RPP (!_hoops_IRRC (_hoops_GCRRA->_hoops_HAIR._hoops_AGSAR, _hoops_RCRRA)) */ {
									_hoops_SPRI->fcolors = (RGB *)
										HI_Clone_Anything (_hoops_SPRI->fcolors,
														   (_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) *(long)sizeof(RGB));
								}
							}
							else if (_hoops_SPRI->ecolors == _hoops_SPRI->_hoops_PAHIR &&
										!BIT (colors->_hoops_GHA, Color_VERTEX) ||
									 _hoops_SPRI->ecolors == _hoops_SPRI->fcolors &&
										!BIT (colors->_hoops_GHA, Color_FRONT)) {
								/* _hoops_IHSA _hoops_HSSRR */
								_hoops_SPRI->ecolors = (RGB *)HI_Clone_Anything (_hoops_SPRI->ecolors, _hoops_IPRI->point_count *(long)sizeof(RGB));
							}
						}
						_hoops_RIRRA = &_hoops_SPRI->ecolors[offset];
					}

					if (BIT (colors->_hoops_GHA, Color_FRONT)) {
						if (_hoops_SPRI->fcolors == null) {
							if (BIT (colors->_hoops_GHA, Color_EDGE) && _hoops_SPRI->ecolors != null)
								_hoops_SPRI->fcolors = _hoops_SPRI->ecolors;
							else if (BIT (colors->_hoops_GHA, Color_VERTEX) && _hoops_SPRI->_hoops_PAHIR != null)
								_hoops_SPRI->fcolors = _hoops_SPRI->_hoops_PAHIR;
							else
								HI_Initialize_Vertex_Attributes (_hoops_IPRI, _hoops_AARHR, 0);
						}
						else {
							/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCSP _hoops_HIH _hoops_ASAI _hoops_RGSR _hoops_IRS _hoops_GCSP _hoops_ARIP, _hoops_IPS */
							if (_hoops_SPRI->fcolors == _hoops_SPRI->_hoops_PAHIR &&
								_hoops_SPRI->fcolors == _hoops_SPRI->ecolors &&
								ANYBIT (colors->_hoops_GHA, Color_VERTEX|Color_EDGE) &&
								!ALLBITS (colors->_hoops_GHA, Color_VERTEX|Color_EDGE)) {
								/* 3-_hoops_PPRRR _hoops_HSSRR, _hoops_SPR _hoops_IIGR _hoops_RH _hoops_HIASR _hoops_GHHS _hoops_RAAP _hoops_GGSR */
								if (!BIT (colors->_hoops_GHA, Color_VERTEX)) {
									_hoops_SPRI->_hoops_PAHIR = (RGB *)HI_Clone_Anything (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count * (long)sizeof(RGB));
								}
								else /* _hoops_RPP (!_hoops_IRRC (_hoops_GCRRA->_hoops_HAIR._hoops_AGSAR, _hoops_ACRRA)) */ {
									_hoops_SPRI->ecolors = (RGB *)HI_Clone_Anything (_hoops_SPRI->ecolors, _hoops_IPRI->point_count * (long)sizeof(RGB));
								}
							}
							else if (_hoops_SPRI->fcolors == _hoops_SPRI->_hoops_PAHIR &&
										!BIT (colors->_hoops_GHA, Color_VERTEX) ||
									 _hoops_SPRI->fcolors == _hoops_SPRI->ecolors &&
										!BIT (colors->_hoops_GHA, Color_EDGE)) {
								/* _hoops_IHSA _hoops_HSSRR */
								_hoops_SPRI->fcolors = (RGB *)HI_Clone_Anything (_hoops_SPRI->fcolors,(_hoops_IPRI->point_count + _hoops_IPRI->_hoops_GCRHR) * (long)sizeof(RGB));
							}
						}
						_hoops_AIRRA = &_hoops_SPRI->fcolors[offset];
					}


					Local_Vertex_Flags *	flags = _hoops_SPRI->_hoops_CHHPR(offset);

					if ((_hoops_GSRRA == null ||
						 BIT (*flags, _hoops_HCRRA) && *_hoops_GSRRA == rgb) &&
						(_hoops_RIRRA == null ||
						 BIT (*flags, _hoops_PPHPR) && *_hoops_RIRRA == rgb) &&
						(_hoops_AIRRA == null ||
						 BIT (*flags, _hoops_AARHR) && *_hoops_AIRRA == rgb))
						goto _hoops_PRSPR; /* _hoops_IRAHR */

					if (_hoops_GSRRA != null) {
						if (!BIT (*flags, _hoops_HCRRA)) {
							*flags |= _hoops_HCRRA;
							++_hoops_SPRI->_hoops_ICRRA;
						}
						_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;

						if (BIT (*flags, _hoops_SIRRA)) {
							*flags &= ~_hoops_SIRRA;
							--_hoops_SPRI->_hoops_PCRRA;
							_hoops_SPRI->_hoops_HAHIR[offset] = 0.0f;
							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
						}
						if (BIT (*flags, _hoops_CCRRA)) {
							*flags &= ~_hoops_CCRRA;
							--_hoops_SPRI->_hoops_HIRRA;
							_hoops_SPRI->_hoops_IAHIR[offset] = _hoops_CAHSR::_hoops_SAHSR;
							_hoops_IPRI->_hoops_AGRHR &= ~_hoops_CCRRA;
						}

						*_hoops_GSRRA = rgb;
					}

					if (_hoops_RIRRA != null) {
						if (!BIT (*flags, _hoops_PPHPR)) {
							*flags |= _hoops_PPHPR;
							++_hoops_SPRI->_hoops_SCHPR;
						}
						_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;

						if (BIT (*flags, _hoops_RPHPR)) {
							*flags &= ~_hoops_RPHPR;
							--_hoops_SPRI->_hoops_CCHPR;
							_hoops_SPRI->_hoops_HGHIR[offset] = 0.0f;
							_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
						}

						*_hoops_RIRRA = rgb;
					}

					if (_hoops_AIRRA != null) {
						if (!BIT (*flags, _hoops_AARHR)) {
							*flags |= _hoops_AARHR;
							++_hoops_SPRI->_hoops_RCRHR;
						}
						_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;

						if (BIT (*flags, _hoops_HARHR)) {
							*flags &= ~_hoops_HARHR;
							--_hoops_SPRI->_hoops_SIRHR;
							_hoops_SPRI->_hoops_IGHIR[offset] = 0.0f;
							_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
							_hoops_IPRI->polyhedron_flags &= ~_hoops_SCRRA;
						}

						*_hoops_AIRRA = rgb;
					}

					if (_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
						_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
						FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
						_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
						_hoops_SPRI->flags = 0;
					}
				}

				if (_hoops_IPRI->owner != null) {
					if (_hoops_PIRRA != 0) {
						if (_hoops_SPRI->_hoops_HIRRA == 0)
							HI_Less_Transparencies (_hoops_RIGC, _hoops_IPRI->owner, 1);
					}
					else {
						if (_hoops_SPRI->_hoops_HIRRA != 0)
							HI_More_Transparencies (_hoops_RIGC, _hoops_IPRI->owner, 1);
					}
				}
			}

			HI_Invalidate_Display_Lists(_hoops_RIGC, _hoops_IPRI);
			/* _hoops_RRRPR _hoops_PAH _hoops_SHH _hoops_IRAP _hoops_IH _hoops_SPIGA */
			if (_hoops_IPRI->owner != null) {
				/* _hoops_AGCR _hoops_CHR _hoops_IHRI _hoops_RPP _hoops_CPSA _hoops_IRS _hoops_RSRRA */
				if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_IPRI->owner, _hoops_ASRRA);
			}

			_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_GPSIR | _hoops_AHSGA | _hoops_RPSIR);
		}
		else if (_hoops_GCRIR == _hoops_ICRIR) {

			if (ANYBIT (colors->_hoops_GHA, ~Color_FACE))
				HE_WARNING (HEC_COLOR, HES_FACE, "Only 'face' color may be set within a face");

			Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				/* _hoops_SR _hoops_CHR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_HAIR _hoops_GPP _hoops_IRS _hoops_RSRA _hoops_HSP, _hoops_HIH _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_HSP _hoops_RIP _hoops_CRPR _hoops_HPP _hoops_HA, _hoops_SR _hoops_RRP _hoops_SPR! */
				ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				for (int i = 0; i < _hoops_IPRI->face_count; i++)
					_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
			}

			if (_hoops_CPRRA != null) {

				if (_hoops_CPRI->findices == null)
					HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_COLOR_BY_FINDEX);

				_hoops_GIIPR * flags = _hoops_CPRI->_hoops_CHHPR(offset);
				_hoops_ACGHR *	findex = &_hoops_CPRI->findices[offset];

				if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_FINDEX) && *findex == index)
					goto _hoops_PRSPR; /* _hoops_IRAHR */

				if (!BIT (*flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
					*flags |= LFA_EXPLICIT_COLOR_BY_FINDEX;
					++_hoops_CPRI->_hoops_PSRRA;
				}

				if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_VALUE)) {
					*flags &= ~LFA_EXPLICIT_COLOR_BY_VALUE;
					--_hoops_CPRI->_hoops_HSRRA;
					_hoops_CPRI->colors[offset] = _hoops_GPSR::_hoops_RPSR;
				}

				*findex = index;
				*flags |= _hoops_IGAHR;
			}
			else {
				/* _hoops_CSSGR _hoops_HPP _hoops_PIRA */ 

				if (_hoops_CPRI->colors == null)
					HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_COLOR_BY_VALUE);

				_hoops_GIIPR * flags = _hoops_CPRI->_hoops_CHHPR(offset);
				RGB * color = &_hoops_CPRI->colors[offset];

				if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_VALUE) && *color == rgb)
					goto _hoops_PRSPR; /* _hoops_IRAHR */

				if (!BIT (*flags, LFA_EXPLICIT_COLOR_BY_VALUE)) {
					*flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
					++_hoops_CPRI->_hoops_HSRRA;
				}

				if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
					*flags &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
					--_hoops_CPRI->_hoops_PSRRA;
					_hoops_CPRI->findices[offset] = 0.0f;
				}

				*color = rgb;
				*flags |= _hoops_IGAHR;
			}
			

			/* _hoops_RRRPR _hoops_PAH _hoops_SHH _hoops_IRAP _hoops_IH _hoops_SPIGA */
			if (_hoops_IPRI->owner) {
				HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, _hoops_IPRI->owner, -2, _hoops_IPRI, 0);
				if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_IPRI->owner, _hoops_ASRRA);
			}

			_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

			_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR | _hoops_SIGPR | _hoops_RPSIR);
		}
		else if (_hoops_GCRIR == _hoops_GSRIR) {

			
			_hoops_GIIPR			_hoops_ISRRA = 0;

			if (ANYBIT (colors->_hoops_GHA, ~Color_FACE))
				HE_WARNING (HEC_COLOR, HES_REGION, "Only 'face' color may be set within a region");

			Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
			int const *				regions = _hoops_CPRI->regions;

			if (regions == null && offset != 0)
				goto _hoops_PRSPR;	/* _hoops_RSSI _hoops_HCR _hoops_GGR _hoops_SHIR _hoops_ISPH, _hoops_IAGC _hoops_HRGR _hoops_HAR */

			if (regions != null) {
				/* _hoops_SR _hoops_CHR _hoops_AHCA _hoops_IS _hoops_ARP _hoops_IRS _hoops_HPRC _hoops_GPP _hoops_HAR _hoops_HCR
					_hoops_IIGR _hoops_RH _hoops_RSSI, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IRS _hoops_HSP _hoops_SGI _hoops_CRPR
					_hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HS _hoops_SPR */
				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
					ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
					for (int i = 0; i < _hoops_IPRI->face_count; i++)
						_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
				}
			}

			if (_hoops_CPRRA != null) {

				if (_hoops_CPRI->findices == null)
					HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_COLOR_BY_FINDEX);

				for (int i=0; i<_hoops_IPRI->face_count; i++) {
					if (regions == null || regions[i] == offset) {

						_hoops_GIIPR *	flags	 = _hoops_CPRI->_hoops_CHHPR(i);
						_hoops_ACGHR *	findex = &_hoops_CPRI->findices[i];

						if (!BIT (*flags, LFA_EXPLICIT_COLOR_BY_FINDEX) || *findex != index) {
							if (!BIT (*flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
								*flags |= LFA_EXPLICIT_COLOR_BY_FINDEX;
								++_hoops_CPRI->_hoops_PSRRA;
							}
							_hoops_ISRRA |= LFA_EXPLICIT_COLOR_BY_FINDEX;

							if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_VALUE)) {
								*flags &= ~LFA_EXPLICIT_COLOR_BY_VALUE;
								--_hoops_CPRI->_hoops_HSRRA;
								_hoops_CPRI->colors[i] = _hoops_GPSR::_hoops_RPSR;
								_hoops_ISRRA |= LFA_EXPLICIT_COLOR_BY_VALUE;
							}

							*findex = index;
						}
					}
				}
			}
			else /* _hoops_CSSGR _hoops_HPP _hoops_PIRA */ {
				if (_hoops_CPRI->colors == null)
					HI_Initialize_Face_Attributes (_hoops_IPRI, LFA_EXPLICIT_COLOR_BY_VALUE);

				for (int i=0; i<_hoops_IPRI->face_count; i++) {
					if (regions == null || regions[i] == offset) {
						_hoops_GIIPR * flags = _hoops_CPRI->_hoops_CHHPR(i);
						RGB *	color = &_hoops_CPRI->colors[i];

						if (!BIT (*flags, LFA_EXPLICIT_COLOR_BY_VALUE) || *color != rgb) {
							if (!BIT (*flags, LFA_EXPLICIT_COLOR_BY_VALUE)) {
								*flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
								++_hoops_CPRI->_hoops_HSRRA;
							}
							_hoops_ISRRA |= LFA_EXPLICIT_COLOR_BY_VALUE;

							if (BIT (*flags, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
								*flags &= ~LFA_EXPLICIT_COLOR_BY_FINDEX;
								--_hoops_CPRI->_hoops_PSRRA;
								_hoops_CPRI->findices[i] = 0.0f;
								_hoops_ISRRA |= LFA_EXPLICIT_COLOR_BY_FINDEX;
							}

							*color = rgb;

							*flags |= _hoops_IGAHR;
						}
					}
				}
			}

			/* _hoops_RRRPR _hoops_PAH _hoops_SHH _hoops_IRAP _hoops_IH _hoops_SPIGA */
			if (_hoops_IPRI->owner) {
				HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, _hoops_IPRI->owner, -2, _hoops_IPRI, 0);
				if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_IPRI->owner, _hoops_ASRRA);
			}

			if (_hoops_IPRI->tristrips != null) {
				if (!BIT (HOOPS_WORLD->system_flags, _hoops_CSRRA))
					_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;
				else {
					Tristrip *	ts = _hoops_IPRI->tristrips;

					do if (ts->face_attributes.region == offset) {
						ts->face_attributes.flags &= ~_hoops_IACHR;

						if (_hoops_CPRRA != null) {
							ts->face_attributes.findex = index;
							ts->face_attributes.flags |= LFA_EXPLICIT_COLOR_BY_FINDEX;
						}
						else {
							ts->face_attributes.color = rgb;
							ts->face_attributes.flags |= LFA_EXPLICIT_COLOR_BY_VALUE;
						}

						ts->_hoops_CPGPR |= _hoops_GPSIR;
					} while ((ts = ts->next) != null);
				}
			}

			_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR | _hoops_SIGPR | _hoops_RPSIR);
		}
		else if (_hoops_GCRIR == _hoops_CCRIR) {

			if (colors->_hoops_GHA != Color_EDGE)
				HE_WARNING (HEC_COLOR, HES_EDGE, "Only 'edge' color may be set within a edge");

			_hoops_RPGHR *	lea = &_hoops_IPRI->_hoops_IHHPR;

			if (_hoops_CPRRA != null) {
				if (lea->findices == null)
					HI_Initialize_Edge_Attributes (_hoops_IPRI, _hoops_RPGI);

				_hoops_GHHPR *	flags = &lea->flags[offset];
				_hoops_ACGHR *	findex = &lea->findices[offset];

				if (BIT (*flags, _hoops_RPGI) && *findex == index)
					goto _hoops_PRSPR; /* _hoops_IRAHR */

				if (!BIT (*flags, _hoops_RPGI)) {
					*flags |= _hoops_RPGI;
					++lea->_hoops_PSRRA;
				}
				_hoops_IPRI->_hoops_RSHPR &= ~_hoops_RPGI;

				if (BIT (*flags, _hoops_SSRRA)) {
					*flags &= ~_hoops_SSRRA;
					--lea->_hoops_HSRRA;
					lea->colors[offset] = _hoops_GPSR::_hoops_RPSR;
					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_SSRRA;
				}

				*findex = index;
			}
			else /* _hoops_CSSGR _hoops_HPP _hoops_PIRA */ {
				if (lea->colors == null)
					HI_Initialize_Edge_Attributes (_hoops_IPRI, _hoops_SSRRA);

				_hoops_GHHPR *	flags = &lea->flags[offset];
				RGB *				color = &lea->colors[offset];

				if (BIT (*flags, _hoops_SSRRA) && *color == rgb)
					goto _hoops_PRSPR; /* _hoops_IRAHR */

				if (!BIT (*flags, _hoops_SSRRA)) {
					*flags |= _hoops_SSRRA;
					++lea->_hoops_HSRRA;
				}
				_hoops_IPRI->_hoops_RSHPR &= ~_hoops_SSRRA;

				if (BIT (*flags, _hoops_RPGI)) {
					*flags &= ~_hoops_RPGI;
					--lea->_hoops_PSRRA;
					lea->findices[offset] = 0.0f;
					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_RPGI;
				}

				*color = rgb;
			}

			/* _hoops_RRRPR _hoops_PAH _hoops_SHH _hoops_IRAP _hoops_IH _hoops_SPIGA */
			if (_hoops_IPRI->owner) {
				HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, _hoops_IPRI->owner, -2, _hoops_IPRI, 0);
				if (!BIT (_hoops_IPRI->owner->_hoops_RCGC, _hoops_ASRRA))
					HI_Propagate_Maybes (_hoops_RIGC, _hoops_IPRI->owner, _hoops_ASRRA);
			}

			_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_GGARA | _hoops_RPSIR);
		}

	} while ((colors = colors->next) != null);

#endif
_hoops_PRSPR:
	return false;
}


local Color_Object _hoops_RGARA (
	char const		*_hoops_RPPA,
	char const		*_hoops_SSRPR)
{
	Color_Object _hoops_AGARA;

	switch (*_hoops_RPPA) {
		case 'c': {				/* _hoops_AACC _hoops_ISHA(_hoops_GRI)/_hoops_HSP(_hoops_GRI) */
			if (_hoops_SSRPR - _hoops_RPPA < 8)
				return Color_NONE;

			++_hoops_RPPA;

			if (*_hoops_RPPA++ != 'u' ||
				*_hoops_RPPA++ != 't' ||
				*_hoops_RPPA++ != ' ')
				return Color_NONE;

			if (*_hoops_RPPA == 'e') {
				if (*_hoops_RPPA++ != 'e' ||
					*_hoops_RPPA++ != 'd' ||
					*_hoops_RPPA++ != 'g' ||
					*_hoops_RPPA++ != 'e')
					return Color_NONE;

				if (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == 's') ++_hoops_RPPA;

				if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
					_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
						_hoops_RPPA += 2;
						if (*_hoops_RPPA++ != 'o' ||
							*_hoops_RPPA++ != 'n' ||
							*_hoops_RPPA++ != 't' ||
							*_hoops_RPPA++ != 'r' ||
							*_hoops_RPPA++ != 'a' ||
							*_hoops_RPPA++ != 's' ||
							*_hoops_RPPA++ != 't')
							return Color_NONE;
						else
							_hoops_AGARA = _hoops_PGARA;
				}
				else
					_hoops_AGARA = Color_CUT_EDGE;
			}
			else if (*_hoops_RPPA == 'f') {
				if (*_hoops_RPPA++ != 'f' ||
					*_hoops_RPPA++ != 'a' ||
					*_hoops_RPPA++ != 'c' ||
					*_hoops_RPPA++ != 'e')
					return Color_NONE;

				if (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == 's') ++_hoops_RPPA;

				if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
					_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
						_hoops_RPPA += 2;
						if (*_hoops_RPPA++ != 'o' ||
							*_hoops_RPPA++ != 'n' ||
							*_hoops_RPPA++ != 't' ||
							*_hoops_RPPA++ != 'r' ||
							*_hoops_RPPA++ != 'a' ||
							*_hoops_RPPA++ != 's' ||
							*_hoops_RPPA++ != 't')
							return Color_NONE;
						else
							_hoops_AGARA = _hoops_HGARA;
				}
				else
					_hoops_AGARA = Color_CUT_FACE;
			}
			else if (*_hoops_RPPA == 'g') {
				if (*_hoops_RPPA++ != 'g' ||
					*_hoops_RPPA++ != 'e' ||
					*_hoops_RPPA++ != 'o' ||
					*_hoops_RPPA++ != 'm' ||
					*_hoops_RPPA++ != 'e' ||
					*_hoops_RPPA++ != 't' ||
					*_hoops_RPPA++ != 'r' ||
					*_hoops_RPPA++ != 'y')
					return Color_NONE;

				if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
					_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
						_hoops_RPPA += 2;
						if (*_hoops_RPPA++ != 'o' ||
							*_hoops_RPPA++ != 'n' ||
							*_hoops_RPPA++ != 't' ||
							*_hoops_RPPA++ != 'r' ||
							*_hoops_RPPA++ != 'a' ||
							*_hoops_RPPA++ != 's' ||
							*_hoops_RPPA++ != 't')
							return Color_NONE;
						else
							_hoops_AGARA = _hoops_IGARA;
				}
				else
					_hoops_AGARA = Color_CUT_GEOMETRY;
			}
			else
				return Color_NONE;
				  }		break;

		case 'e': {				/* _hoops_ISHA(_hoops_GRI) */
			if (_hoops_SSRPR - _hoops_RPPA < 4)
				return Color_NONE;

			++_hoops_RPPA;

			if (*_hoops_RPPA++ != 'd' ||
				*_hoops_RPPA++ != 'g' ||
				*_hoops_RPPA++ != 'e')
				return Color_NONE;

			if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
				_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
					_hoops_RPPA += 2;
					if (*_hoops_RPPA++ != 'o' ||
						*_hoops_RPPA++ != 'n' ||
						*_hoops_RPPA++ != 't' ||
						*_hoops_RPPA++ != 'r' ||
						*_hoops_RPPA++ != 'a' ||
						*_hoops_RPPA++ != 's' ||
						*_hoops_RPPA++ != 't')
						return Color_NONE;

					_hoops_AGARA = Color_EDGE_CONTRAST;
			}
			else {
				if (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == 's') ++_hoops_RPPA;

				_hoops_AGARA = Color_EDGE;
			}
				  }		break;

		case 'p': {				/* _hoops_ISII(_hoops_GRI), _hoops_HSSP _hoops_CGARA */
			if (_hoops_SSRPR - _hoops_RPPA < 8)
				return Color_NONE;

			++_hoops_RPPA;

			if (*_hoops_RPPA++ != 'o' ||
				*_hoops_RPPA++ != 'l' ||
				*_hoops_RPPA++ != 'y')
				return Color_NONE;

			if (*_hoops_RPPA == 'l') {
				if (*_hoops_RPPA++ != 'l' ||
					*_hoops_RPPA++ != 'i' ||
					*_hoops_RPPA++ != 'n' ||
					*_hoops_RPPA++ != 'e')
					return Color_NONE;

				if (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == 's') ++_hoops_RPPA;

				_hoops_AGARA = Color_LINE;
			}
			else {
				if (_hoops_SSRPR - _hoops_RPPA < 12 ||
					*_hoops_RPPA++ != 'g' ||
					*_hoops_RPPA++ != 'o' ||
					*_hoops_RPPA++ != 'n' ||
					*_hoops_RPPA++ != ' ' ||
					*_hoops_RPPA++ != 'c' ||
					*_hoops_RPPA++ != 'o' ||
					*_hoops_RPPA++ != 'n' ||
					*_hoops_RPPA++ != 't' ||
					*_hoops_RPPA++ != 'r' ||
					*_hoops_RPPA++ != 'a' ||
					*_hoops_RPPA++ != 's' ||
					*_hoops_RPPA++ != 't')
					return Color_NONE;

				_hoops_AGARA = Color_FACE_CONTRAST;
			}
				  }		break;

		case 's': {				/* _hoops_IHGP _hoops_CHIR */
			if (_hoops_SSRPR - _hoops_RPPA < 17)
				return Color_NONE;

			++_hoops_RPPA;
			if (*_hoops_RPPA++ != 'i' ||
				*_hoops_RPPA++ != 'm' ||
				*_hoops_RPPA++ != 'p' ||
				*_hoops_RPPA++ != 'l' ||
				*_hoops_RPPA++ != 'e' ||
				*_hoops_RPPA++ != ' ' ||
				*_hoops_RPPA++ != 'r' ||
				*_hoops_RPPA++ != 'e' ||
				*_hoops_RPPA++ != 'f' ||
				*_hoops_RPPA++ != 'l' ||
				*_hoops_RPPA++ != 'e' ||
				*_hoops_RPPA++ != 'c' ||
				*_hoops_RPPA++ != 't' ||
				*_hoops_RPPA++ != 'i' ||
				*_hoops_RPPA++ != 'o' ||
				*_hoops_RPPA++ != 'n')
				return Color_NONE;
			_hoops_AGARA = _hoops_SGARA;
				  }		break;

		case 't': {				/* _hoops_HCGR */
			if (_hoops_SSRPR - _hoops_RPPA < 4)
				return Color_NONE;

			++_hoops_RPPA;

			if (*_hoops_RPPA++ != 'e' ||
				*_hoops_RPPA++ != 'x' ||
				*_hoops_RPPA++ != 't')
				return Color_NONE;

			if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
				_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
					_hoops_RPPA += 2;
					if (*_hoops_RPPA++ != 'o' ||
						*_hoops_RPPA++ != 'n' ||
						*_hoops_RPPA++ != 't' ||
						*_hoops_RPPA++ != 'r' ||
						*_hoops_RPPA++ != 'a' ||
						*_hoops_RPPA++ != 's' ||
						*_hoops_RPPA++ != 't')
						return Color_NONE;

					_hoops_AGARA = Color_TEXT_CONTRAST;
			}
			else
				_hoops_AGARA = Color_TEXT;
				  }	break;

		case 'b': {				/* _hoops_ISSC [_hoops_HSP] */
			if (_hoops_SSRPR - _hoops_RPPA < 4)
				return Color_NONE;

			++_hoops_RPPA;

			if (*_hoops_RPPA++ != 'a' ||
				*_hoops_RPPA++ != 'c' ||
				*_hoops_RPPA++ != 'k')
				return Color_NONE;

			if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
				_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
					_hoops_RPPA += 2;
					if (*_hoops_RPPA++ != 'o' ||
						*_hoops_RPPA++ != 'n' ||
						*_hoops_RPPA++ != 't' ||
						*_hoops_RPPA++ != 'r' ||
						*_hoops_RPPA++ != 'a' ||
						*_hoops_RPPA++ != 's' ||
						*_hoops_RPPA++ != 't')
						return Color_NONE;
					else
						_hoops_AGARA = _hoops_GRARA;
			}
			else
				_hoops_AGARA = Color_BACK;
				  }	break;

		case 'f': {				/* _hoops_HSP(_hoops_GRI), _hoops_HSP _hoops_CGARA, _hoops_RIPS [_hoops_HSP] */
			if (_hoops_SSRPR - _hoops_RPPA < 4)
				return Color_NONE;

			++_hoops_RPPA;

			if (_hoops_RPPA[0] == 'r' &&
				_hoops_RPPA[1] == 'o' &&
				_hoops_RPPA[2] == 'n' &&
				_hoops_RPPA[3] == 't') {
					_hoops_RPPA += 4;

					if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
						_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
							_hoops_RPPA += 2;
							if (*_hoops_RPPA++ != 'o' ||
								*_hoops_RPPA++ != 'n' ||
								*_hoops_RPPA++ != 't' ||
								*_hoops_RPPA++ != 'r' ||
								*_hoops_RPPA++ != 'a' ||
								*_hoops_RPPA++ != 's' ||
								*_hoops_RPPA++ != 't')
								return Color_NONE;

							_hoops_AGARA = _hoops_RRARA;
					}
					else
						_hoops_AGARA = Color_FRONT;
			}
			else {
				if (*_hoops_RPPA++ != 'a' ||
					*_hoops_RPPA++ != 'c' ||
					*_hoops_RPPA++ != 'e')
					return Color_NONE;

				if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
					_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
						_hoops_RPPA += 2;
						if (*_hoops_RPPA++ != 'o' ||
							*_hoops_RPPA++ != 'n' ||
							*_hoops_RPPA++ != 't' ||
							*_hoops_RPPA++ != 'r' ||
							*_hoops_RPPA++ != 'a' ||
							*_hoops_RPPA++ != 's' ||
							*_hoops_RPPA++ != 't')
							return Color_NONE;

						_hoops_AGARA = Color_FACE_CONTRAST;
				}
				else {
					if (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == 's') ++_hoops_RPPA;
					_hoops_AGARA = Color_FACE;
				}
			}
				  }	break;

		case 'm': {				/* _hoops_GPIA(_hoops_GRI) [_hoops_RGAR] */
			if (_hoops_SSRPR - _hoops_RPPA < 6)
				return Color_NONE;

			++_hoops_RPPA;

			if (*_hoops_RPPA++ != 'a' ||
				*_hoops_RPPA++ != 'r' ||
				*_hoops_RPPA++ != 'k' ||
				*_hoops_RPPA++ != 'e' ||
				*_hoops_RPPA++ != 'r')
				return Color_NONE;

			if (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == 's') ++_hoops_RPPA;

			if (_hoops_SSRPR - _hoops_RPPA >= 5 && _hoops_RPPA[0] == ' ' &&
				_hoops_RPPA[1] == 'o' && _hoops_RPPA[2] == 'n' &&
				_hoops_RPPA[3] == 'l' && _hoops_RPPA[4] == 'y') {
					_hoops_RPPA += 5;
					_hoops_AGARA = Color_MARKER;
			}
			else if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
				_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
					_hoops_RPPA += 2;
					if (*_hoops_RPPA++ != 'o' ||
						*_hoops_RPPA++ != 'n' ||
						*_hoops_RPPA++ != 't' ||
						*_hoops_RPPA++ != 'r' ||
						*_hoops_RPPA++ != 'a' ||
						*_hoops_RPPA++ != 's' ||
						*_hoops_RPPA++ != 't')
						return Color_NONE;

					_hoops_AGARA = Color_MARKER_CONTRAST;
			}
			else
				_hoops_AGARA = Color_MARKER | Color_VERTEX;
				  }	break;

		case 'v': {				/* _hoops_GPHA, _hoops_GIHA */
			if (_hoops_SSRPR - _hoops_RPPA < 6)
				return Color_NONE;

			++_hoops_RPPA;

			if (*_hoops_RPPA++ != 'e' ||
				*_hoops_RPPA++ != 'r' ||
				*_hoops_RPPA++ != 't')
				return Color_NONE;

			if (_hoops_RPPA[0] == 'e' && _hoops_RPPA[1] == 'x') {
				_hoops_RPPA += 2;
				if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
					_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
						_hoops_RPPA += 2;
						if (*_hoops_RPPA++ != 'o' ||
							*_hoops_RPPA++ != 'n' ||
							*_hoops_RPPA++ != 't' ||
							*_hoops_RPPA++ != 'r' ||
							*_hoops_RPPA++ != 'a' ||
							*_hoops_RPPA++ != 's' ||
							*_hoops_RPPA++ != 't')
							return Color_NONE;

						_hoops_AGARA = Color_VERTEX_CONTRAST;
				}
				else
					_hoops_AGARA = Color_VERTEX;
			}
			else if (_hoops_SSRPR - _hoops_RPPA >= 4 &&
				_hoops_RPPA[0] == 'i' && _hoops_RPPA[1] == 'c' &&
				_hoops_RPPA[2] == 'e' && _hoops_RPPA[3] == 's') {
					_hoops_RPPA += 4;

					_hoops_AGARA = Color_VERTEX;
			}
			else return Color_NONE;
				  }	break;

		case 'w': {				/* _hoops_RPPS(_hoops_GRI), _hoops_RPPS _hoops_CGARA */
			if (_hoops_SSRPR - _hoops_RPPA < 6)
				return Color_NONE;

			++_hoops_RPPA;

			if (*_hoops_RPPA++ != 'i' ||
				*_hoops_RPPA++ != 'n' ||
				*_hoops_RPPA++ != 'd' ||
				*_hoops_RPPA++ != 'o' ||
				*_hoops_RPPA++ != 'w')
				return Color_NONE;

			if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
				_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
					_hoops_RPPA += 2;
					if (*_hoops_RPPA++ != 'o' ||
						*_hoops_RPPA++ != 'n' ||
						*_hoops_RPPA++ != 't' ||
						*_hoops_RPPA++ != 'r' ||
						*_hoops_RPPA++ != 'a' ||
						*_hoops_RPPA++ != 's' ||
						*_hoops_RPPA++ != 't')
						return Color_NONE;

					_hoops_AGARA = Color_WINDOW_CONTRAST;
			}
			else {
				if (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == 's') ++_hoops_RPPA;

				_hoops_AGARA = Color_WINDOW;
			}
				  }	break;

		case 'a': {				/* _hoops_AASR, _hoops_AASR _hoops_GH, _hoops_ARARA, _hoops_AASR _hoops_RRR */
			if (_hoops_SSRPR - _hoops_RPPA < 7)
				return Color_NONE;

			++_hoops_RPPA;

			if (*_hoops_RPPA++ != 'm' ||
				*_hoops_RPPA++ != 'b' ||
				*_hoops_RPPA++ != 'i' ||
				*_hoops_RPPA++ != 'e' ||
				*_hoops_RPPA++ != 'n' ||
				*_hoops_RPPA++ != 't')
				return Color_NONE;

			if (_hoops_SSRPR - _hoops_RPPA >= 2 &&
				_hoops_RPPA[0] == ' ') {
					if (_hoops_RPPA[1] == 'u') { //_hoops_AASR _hoops_GH
						_hoops_RPPA += 2;
						if (*_hoops_RPPA++ != 'p')
							return Color_NONE;
						_hoops_AGARA = _hoops_PRARA;
					}
					else if (_hoops_RPPA[1] == 'd') { //_hoops_AASR _hoops_ISHP
						_hoops_RPPA += 2;
						if (*_hoops_RPPA++ != 'o' ||
							*_hoops_RPPA++ != 'w' ||
							*_hoops_RPPA++ != 'n')
							return Color_NONE;
						_hoops_AGARA = _hoops_HRARA;
					}
					else if (_hoops_RPPA[1] == 'l') {
						_hoops_RPPA += 2;
						if (*_hoops_RPPA++ != 'i' ||
							*_hoops_RPPA++ != 'g' ||
							*_hoops_RPPA++ != 'h' ||
							*_hoops_RPPA++ != 't')
							return Color_NONE;

						if (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == 's')
							++_hoops_RPPA;
						else if (_hoops_SSRPR - _hoops_RPPA >= 3 &&
							_hoops_RPPA[0] == 'i' &&
							_hoops_RPPA[1] == 'n' &&
							_hoops_RPPA[2] == 'g')
							_hoops_RPPA += 3;
						_hoops_AGARA = _hoops_IRARA;
					}
					else
						return Color_NONE;
			}
			else
				_hoops_AGARA = _hoops_IRARA;
				  }	break;

		case 'l': {				/* _hoops_III(_hoops_GRI), _hoops_RRR(_hoops_GRI), _hoops_RCA, _hoops_III _hoops_CGARA */
			if (_hoops_SSRPR - _hoops_RPPA < 4)
				return Color_NONE;

			++_hoops_RPPA;

			if (*_hoops_RPPA++ != 'i')
				return Color_NONE;

			if (_hoops_RPPA[0] == 'n' && _hoops_RPPA[1] == 'e') {
				_hoops_RPPA += 2;
				if (_hoops_SSRPR - _hoops_RPPA >= 9 &&
					_hoops_RPPA[0] == ' ' && _hoops_RPPA[1] == 'c') {
						_hoops_RPPA += 2;
						if (*_hoops_RPPA++ != 'o' ||
							*_hoops_RPPA++ != 'n' ||
							*_hoops_RPPA++ != 't' ||
							*_hoops_RPPA++ != 'r' ||
							*_hoops_RPPA++ != 'a' ||
							*_hoops_RPPA++ != 's' ||
							*_hoops_RPPA++ != 't')
							return Color_NONE;

						_hoops_AGARA = Color_LINE_CONTRAST;
				}
				else {
					if (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == 's') ++_hoops_RPPA;
					_hoops_AGARA = Color_LINE;
				}
			}
			else if (_hoops_SSRPR - _hoops_RPPA >= 3 &&
				_hoops_RPPA[0] == 'g' && _hoops_RPPA[1] == 'h' && _hoops_RPPA[2] == 't') {
					_hoops_RPPA += 3;
					if (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == 's')
						++_hoops_RPPA;
					else if (_hoops_SSRPR - _hoops_RPPA >= 3 &&
						_hoops_RPPA[0] == 'i' && _hoops_RPPA[1] == 'n' && _hoops_RPPA[2] == 'g')
						_hoops_RPPA += 3;

					_hoops_AGARA = Color_LIGHTING;
			}
			else return Color_NONE;
				  }		break;

		default: {
			return Color_NONE;
				 }		/*_hoops_IHSA;*/
	}

	while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') ++_hoops_RPPA;

	if (_hoops_RPPA != _hoops_SSRPR)
		return Color_NONE;

	return _hoops_AGARA;
}

local void _hoops_CRARA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH const *		item,
	_hoops_SSGI *					color)
{

	if (BIT(color->_hoops_GHA, _hoops_SRARA)) {
		Color_Object	_hoops_GAARA = Color_NONE;

		_hoops_IPRRA		_hoops_GCRIR = HI_Anything_To_Open_Type(_hoops_RIGC, item);

		switch (_hoops_GCRIR) {
			case _hoops_GSRIR:
			case _hoops_ICRIR:
				_hoops_GAARA = Color_FACE;
				break;

			case _hoops_CCRIR:
				_hoops_GAARA = Color_EDGE;
				break;

			case _hoops_HCRIR:
				if (item->type == _hoops_AHIP) {
					_hoops_GAARA = Color_GEOMETRY;
					break;
				}
				_hoops_HHHI;

			case _hoops_SCRIR: {
				if (item->type == _hoops_CIRIR) {
					_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)item;

					item = (_hoops_HPAH const *)_hoops_ASIIR->info.geometry._hoops_IGRPR;
				}

				if (item->type != _hoops_CSIP)
					_hoops_GAARA = (Color_FACE|Color_EDGE|Color_VERTEX);
				else
					_hoops_GAARA = (Color_FACE|Color_EDGE);
			} break;

			case _hoops_RCRIR:
			default:
				_hoops_GAARA = Color_GEOMETRY;
				break;
		}

		_hoops_ACSGA *	colors = color->colors;
		color->colors = null;
		color->_hoops_GHA = 0;
		color->_hoops_CCCIR = 0;

		_hoops_ACSGA *	next;

		do {
			next = colors->next;
			colors->next = null;

			if (BIT(colors->_hoops_GHA, _hoops_SRARA)) {
				colors->_hoops_GHA &= ~_hoops_SRARA;
				colors->_hoops_GHA |= _hoops_GAARA;
			}

			if (color->colors == null) {
				color->colors = colors;
				color->_hoops_GHA |= colors->_hoops_GHA;
				color->_hoops_CCCIR |= colors->_hoops_GHA;
			}
			else {
				HI_Merge_Colors (color, colors, null, null);
				HI_Free_Colors (colors);
			}

		} while ((colors = next) != null);
	}
}

GLOBAL_FUNCTION bool HI_Decipher_Color_Target (
	_hoops_AIGPR *		_hoops_RIGC,
	char const **				_hoops_RAARA,
	char const *				_hoops_SSRPR,
	bool						_hoops_AAARA,
	Color_Object *				_hoops_PAARA,
	Color_Object				_hoops_GAARA)
{
	UNREFERENCED (_hoops_RIGC);

	char const *				_hoops_RPPA = *_hoops_RAARA;
	char const *				_hoops_HRCAR;

	*_hoops_PAARA = Color_NONE;

	do {
		
		while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ') 
			++_hoops_RPPA;

		_hoops_HRCAR = _hoops_RPPA;

		if (_hoops_AAARA)
			_hoops_RGGA (_hoops_RPPA == _hoops_SSRPR || *_hoops_RPPA == '=' || *_hoops_RPPA == ',') 
				++_hoops_RPPA;
		else
			_hoops_RGGA (_hoops_RPPA == _hoops_SSRPR || *_hoops_RPPA == '=') 
				++_hoops_RPPA;

		if (_hoops_RPPA == _hoops_HRCAR) break;

		if (_hoops_HRCAR[0] == 'g' && _hoops_RPPA - _hoops_HRCAR >= 8 &&
			_hoops_HRCAR[1] == 'e' &&
			_hoops_HRCAR[2] == 'o' &&
			_hoops_HRCAR[3] == 'm' &&
			_hoops_HRCAR[4] == 'e' &&
			_hoops_HRCAR[5] == 't' &&
			_hoops_HRCAR[6] == 'r' &&
			_hoops_HRCAR[7] == 'y') {
			_hoops_HRCAR += 8;
			while (_hoops_HRCAR < _hoops_RPPA && *_hoops_HRCAR == ' ') 
				++_hoops_HRCAR;
			if (_hoops_HRCAR != _hoops_RPPA) 
				break;

			*_hoops_PAARA |= _hoops_GAARA;
		}
		else if (_hoops_HRCAR[0] == 'e' &&
			_hoops_RPPA - _hoops_HRCAR >= 10 &&
			_hoops_HRCAR[1] == 'v' &&
			_hoops_HRCAR[2] == 'e' &&
			_hoops_HRCAR[3] == 'r' &&
			_hoops_HRCAR[4] == 'y' &&
			_hoops_HRCAR[5] == 't' &&
			_hoops_HRCAR[6] == 'h' &&
			_hoops_HRCAR[7] == 'i' &&
			_hoops_HRCAR[8] == 'n' &&
			_hoops_HRCAR[9] == 'g') {
			_hoops_HRCAR += 10;
			while (_hoops_HRCAR < _hoops_RPPA && *_hoops_HRCAR == ' ') 
				++_hoops_HRCAR;
			if (_hoops_HRCAR != _hoops_RPPA)
				break;

			*_hoops_PAARA |= Color_EVERYTHING;
		}
		else if (_hoops_HRCAR[0] == 'p' &&
			_hoops_RPPA - _hoops_HRCAR >= 7 &&
			_hoops_HRCAR[1] == 'o' &&
			_hoops_HRCAR[2] == 'l' &&
			_hoops_HRCAR[3] == 'y' &&
			_hoops_HRCAR[4] == 'g' &&
			_hoops_HRCAR[5] == 'o' &&
			_hoops_HRCAR[6] == 'n' &&
			(_hoops_RPPA - _hoops_HRCAR < 16 ||
			 _hoops_HRCAR[7] != ' ' ||
			 _hoops_HRCAR[8] != 'c' ||
			 _hoops_HRCAR[9] != 'o' ||
			 _hoops_HRCAR[10] != 'n' ||
			 _hoops_HRCAR[11] != 't' ||
			 _hoops_HRCAR[12] != 'r' ||
			 _hoops_HRCAR[13] != 'a' ||
			 _hoops_HRCAR[14] != 's' ||
			 _hoops_HRCAR[15] != 't')) {
			_hoops_HRCAR += 7;
			if (_hoops_HRCAR < _hoops_RPPA && *_hoops_HRCAR == 's') 
				++_hoops_HRCAR;
			while (_hoops_HRCAR < _hoops_RPPA && *_hoops_HRCAR == ' ') 
				++_hoops_HRCAR;
			if (_hoops_HRCAR != _hoops_RPPA) 
				break;

			*_hoops_PAARA |= Color_POLYGON;
		}
		else if (_hoops_HRCAR[0] == 'f' &&
			_hoops_RPPA - _hoops_HRCAR >= 4 &&
			_hoops_HRCAR[1] == 'a' &&
			_hoops_HRCAR[2] == 'c' &&
			_hoops_HRCAR[3] == 'e' &&
			(_hoops_RPPA - _hoops_HRCAR < 13 ||
			 _hoops_HRCAR[4] != ' ' ||
			 _hoops_HRCAR[5] != 'c' ||
			 _hoops_HRCAR[6] != 'o' ||
			 _hoops_HRCAR[7] != 'n' ||
			 _hoops_HRCAR[8] != 't' ||
			 _hoops_HRCAR[9] != 'r' ||
			 _hoops_HRCAR[10] != 'a' ||
			 _hoops_HRCAR[11] != 's' ||
			 _hoops_HRCAR[12] != 't')) {
			_hoops_HRCAR += 4;
			if (_hoops_HRCAR < _hoops_RPPA && *_hoops_HRCAR == 's') 
				++_hoops_HRCAR;
			while (_hoops_HRCAR < _hoops_RPPA && *_hoops_HRCAR == ' ') 
				++_hoops_HRCAR;
			if (_hoops_HRCAR != _hoops_RPPA) 
				break;

			*_hoops_PAARA |= Color_FACE;
		}
		else {
			Color_Object tmp;

			if ((tmp = _hoops_RGARA (_hoops_HRCAR, _hoops_RPPA)) == 0) 
				break;
			*_hoops_PAARA |= tmp;
		}

		*_hoops_RAARA = _hoops_RPPA;
	} while (++_hoops_RPPA < _hoops_SSRPR);

	if (*_hoops_PAARA == Color_NONE) {
		*_hoops_PAARA = _hoops_GAARA;
		return false;
	}

	return true;
}

local void _hoops_HAARA (
	_hoops_HCRPR const *	name,
	char const *	_hoops_RPPA) {

	if (_hoops_RPPA - name->text >= MAX_ERRMSG - 30)
		HE_ERROR (HEC_COLOR, HES_SYNTAX_ERROR, Sprintf_N (null, "Can't parse color list '%n'", name));
	else {
		char	buf[MAX_ERRMSG];
		char	_hoops_IAARA[MAX_ERRMSG];
		char *	_hoops_CAARA = _hoops_IAARA;

		if (_hoops_RPPA > name->text) {
			do {
				*_hoops_CAARA++ = '-';
			} while (--_hoops_RPPA != name->text);
		}

		*_hoops_CAARA++ = '\0';

		HE_ERROR2 (HEC_COLOR, HES_SYNTAX_ERROR,
				   Sprintf_N (null, "Can't parse color list '%n'", name),
				   Sprintf_S (buf, "Error was near ---------%s^", _hoops_IAARA));
	}
}

local void _hoops_SAARA (
	double					findex)
{
	char					buf[MAX_ERRMSG];
	float					max = (float)_hoops_GPARA + 0.5f,min = -0.5f;
	float					_hoops_HHRRA = (float)findex;

	HE_ERROR2 (HEC_COLOR, HES_OUT_OF_RANGE_COLOR_INDEX,
			   Sprintf_F (null, "Color index %f is out of range -", _hoops_HHRRA),
			   Sprintf_FF (buf, "must be between %f and %f", min, max));
}


local void _hoops_RPARA (
	int			index)
{
	char	buf[MAX_ERRMSG];
	local	const long	max = _hoops_GPARA;

	HE_ERROR2 (HEC_COLOR, HES_OUT_OF_RANGE_COLOR_INDEX,
			   Sprintf_D (null, "Color index %d is out of range -", index),
			   Sprintf_LD (buf, "must be between zero and %D", max));
}


GLOBAL_FUNCTION bool HI_Check_Texture_Syntax (char const *_hoops_APARA) {
	char const *ptr;
	char _hoops_PPARA = 0;
	char c;

	ptr = _hoops_APARA;
	c = ptr[0];
	if (ptr[0] == '*' && ptr[1] == '\0')
		return true;
	else if (c == '"' || c == '\'' || c == '`') {
		_hoops_PPARA = c;
		ptr++;
		for (;;) {
			if (*ptr == '\0')
				return false; /* _hoops_PSP _hoops_PIS _hoops_HPARA */
			if (*ptr == _hoops_PPARA) {
				if (ptr[1] == '\0') /* _hoops_SSAS _hoops_RH _hoops_HPARA _hoops_RCPS _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_GSGR? */
					return true;
				else if (*(++ptr) != _hoops_PPARA) /* _hoops_IPARA _hoops_CPARA _hoops_CHR _hoops_GPRS */
					return false;
			}
			ptr++;
		}
	}
	else {
		for (;;) {
			switch (*ptr) {
				case '\n': case '\'':  case '"':  case '`':
				case '/': case '?': case '*': case '^': case ',':
				case '{': case '}': case '<': case '>': case '!': case '(':
				case ')': case '=': case '@':
				case ';': case '|':
					return false;
				case '\0':
					return true;
			default:
				ptr++;
			}
		}
	}
}

local _hoops_SSGI * _hoops_SPARA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCRPR const &			what,
	char const *			_hoops_GHARA,
	RGB const * 			rgb,
	char const *			_hoops_RHARA,
	char const *			_hoops_AHARA)
{
	_hoops_SSGI *					_hoops_APRRA = null;

	if (_hoops_RHARA && _hoops_RHARA[0] == '\0')
		_hoops_RHARA = null;

	if (_hoops_AHARA && _hoops_AHARA[0] == '\0')
		_hoops_AHARA = null;

	if (_hoops_RHARA && !HI_Check_Texture_Syntax (_hoops_RHARA)) {
		HE_ERROR (HEC_COLOR, HES_SYNTAX_ERROR,
			Sprintf_S (null, "Syntax error in texture name of explicit color: '%s'", _hoops_RHARA));
		return null;
	}

	/* _hoops_CAHA _hoops_GGSR _hoops_PCPA _hoops_IAIA _hoops_IIGR _hoops_CPAP _hoops_IS _hoops_GHAA _hoops_RH _hoops_HAIR _hoops_IS */

	Color_Object	_hoops_GHA;

	char const *	_hoops_RPPA = what.text;

	if (what.length == 0 ||
		!HI_Decipher_Color_Target (_hoops_RIGC, &_hoops_RPPA, _hoops_RPPA + what.length, true, &_hoops_GHA, _hoops_SRARA) ||
		_hoops_RPPA != what.text + what.length) {
		_hoops_HAARA (&what, _hoops_RPPA);
		return null;
	}
		
	/* _hoops_HAR _hoops_ICIC _hoops_IS _hoops_ASRC _hoops_RAS _hoops_RGR _hoops_PPSR (_hoops_HPGR _hoops_CHGC _hoops_HAR _hoops_SIHH _hoops_PHARA _hoops_GH */

	_hoops_HCRPR	_hoops_HHARA;

	if (_hoops_AHARA) {
		/* _hoops_IH _hoops_HA _hoops_IIH'_hoops_GRI _hoops_RGAR _hoops_SPR _hoops_HCSP _hoops_APP, _hoops_HIH _hoops_SR _hoops_GHCA _hoops_RRP _hoops_IS _hoops_PHHR _hoops_IS _hoops_IRS _hoops_AAP _hoops_SCAH
		 * _hoops_RPP _hoops_SR _hoops_GGCR _hoops_RRI _hoops_ICRSR _hoops_GGR _hoops_RH _hoops_SACS. */
		_hoops_SRHSR		_hoops_IHARA = _hoops_GRRCR ("ignore color");
		HI_Canonize_Chars (_hoops_AHARA, &_hoops_HHARA);
		if (_hoops_RAHSR (_hoops_IHARA, _hoops_HHARA))
			rgb = null;
		else
			HE_ERROR (HEC_COLOR, HES_SYNTAX_ERROR,
					   Sprintf_N (null, "Can't parse options list for explicit color '%n'", &_hoops_HHARA));
		_hoops_RGAIR (_hoops_HHARA);
	}


	_hoops_ARGRA		_hoops_CHARA = 0;
	Option_Value *			channel;

	Option_Value *	_hoops_SHARA = HI_Decipher_Color_Channel (_hoops_RIGC, _hoops_GHARA, 0);

	if ((channel = _hoops_SHARA) != null) {
		_hoops_CHARA = channel->type->id;
		if (channel->next)
			HE_ERROR (HEC_COLOR, HES_SYNTAX_ERROR,
				Sprintf_N (null, "Explicit color settings must be set one channel at a time", &_hoops_HHARA));
	}
	else
		_hoops_CHARA = M_DIFFUSE|_hoops_RHGRA;

	_hoops_HIR *	_hoops_PGC = null;
	int						_hoops_GIARA = -1;

	if (BIT (_hoops_CHARA, _hoops_RHGRA)) {
		ZALLOC (_hoops_PGC, _hoops_HIR);
		if (channel->_hoops_AIPCR > 0) {
			_hoops_PGC->_hoops_HGA = channel->value._hoops_RIARA[0];
			/* _hoops_RPP _hoops_AIARA _hoops_IRS _hoops_SASI _hoops_RCAP, _hoops_RGAR _hoops_ARP _hoops_RH _hoops_HH, _hoops_HAR _hoops_RH _hoops_HAIR */
			_hoops_CHARA &= ~M_DIFFUSE;
		}
		else
			_hoops_PGC->flags |= _hoops_SGGRA;
	}
	else if (BIT (_hoops_CHARA, _hoops_PIARA))
		_hoops_GIARA = _hoops_HIA;
	else if (BIT (_hoops_CHARA, _hoops_HIARA))
		_hoops_GIARA = _hoops_ACA;
	else if (BIT (_hoops_CHARA, _hoops_IIARA))
		_hoops_GIARA = _hoops_PCA;
	else if (BIT (_hoops_CHARA, _hoops_CIARA))
		_hoops_GIARA = _hoops_HCA;
	else if (BIT (_hoops_CHARA, _hoops_SIARA))
		_hoops_GIARA = _hoops_IIA;
	else if (BIT (_hoops_CHARA, _hoops_GCARA))
		_hoops_GIARA = _hoops_RIA;

	if (_hoops_SHARA != null)
		HI_Free_Option_List (_hoops_RIGC, _hoops_SHARA);

	if (!_hoops_RHARA && !rgb) {
		HE_WARNING (HEC_COLOR, HES_NULL_INPUT, "Explicit color is all blank");
	}
	else { 

		ZALLOC(_hoops_APRRA, _hoops_SSGI);
		_hoops_APRRA->_hoops_GHA = _hoops_APRRA->_hoops_CCCIR = _hoops_GHA;

		if (!_hoops_RHARA && _hoops_CHARA == (M_DIFFUSE|_hoops_RHGRA)) {

			_hoops_APCA * normal;
			ZALLOC (normal, _hoops_APCA);

			normal->rgb = *rgb;
			normal->type = _hoops_PPCA;
			normal->_hoops_GHA = _hoops_GHA;
			_hoops_APRRA->colors = normal;
		}
		else {

			_hoops_HCSGA *	_hoops_ICSGA;
			ZALLOC (_hoops_ICSGA, _hoops_HCSGA);

			_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA = M_DIFFUSE;
			_hoops_ICSGA->type = _hoops_GIGRA;
			_hoops_ICSGA->_hoops_GHA = _hoops_GHA;
			_hoops_APRRA->colors = _hoops_ICSGA;

			if (_hoops_RHARA) {
				_hoops_HCRPR texture_name;
				HI_Canonize_Chars_Quoted (_hoops_RHARA, &texture_name, false);

				_hoops_RCR *	texture = HI_Clone_Texture (0); /* _hoops_RSSAR _hoops_IRS _hoops_CCAH _hoops_HH _hoops_HII _hoops_SI */
				texture->flags |= TF_UNEVALUATED;

				/* _hoops_SRPS _hoops_RCARA _hoops_IIGR *_hoops_ACARA, _hoops_HIS _hoops_PSP _hoops_PCARA _hoops_SPHR _hoops_GPP */
				ZALLOC(texture->_hoops_PAPIR, _hoops_AAPIR);
				texture->_hoops_PAPIR->name = texture_name;
				_hoops_HCARA(texture->_hoops_PAPIR->name, texture->_hoops_PAPIR->key);

				HI_Copy_Chars_To_Name (texture_name.text, &texture->name);
				if (rgb) {
					if (_hoops_PGC)
						_hoops_PGC->flags |= _hoops_PRA;
					else
						_hoops_ICSGA->_hoops_ISHIR.flags[_hoops_GIARA] |= _hoops_PRA;
					texture->_hoops_SCR |= _hoops_ICARA;
					texture->_hoops_HPIR._hoops_IPIR = *rgb;
				}
				if (!_hoops_PGC) {
					_hoops_ICSGA->_hoops_ISHIR.flags[_hoops_GIARA] |= _hoops_CCARA;
					_hoops_ICSGA->_hoops_ISHIR.texture[_hoops_GIARA] = texture;
				}
				else {
					_hoops_PGC->flags |= _hoops_CCARA;
					_hoops_PGC->texture = texture;
					/* _hoops_RIH _hoops_SAII _hoops_IIGR _hoops_RH _hoops_SCARA _hoops_HRPR */
					_hoops_ICSGA->_hoops_ISHIR._hoops_SCA = _hoops_PGC;
					_hoops_PGC = null;
				}
				/* _hoops_RPP _hoops_SR _hoops_HS _hoops_GIPR _hoops_HAIR _hoops_PPR _hoops_HH _hoops_SIH, _hoops_RGR _hoops_GSARA _hoops_HRGR _hoops_RSARA _hoops_IS _hoops_GCGRA _hoops_RH _hoops_RSIR _hoops_RCAP,
				 * _hoops_HIS _hoops_ARP _hoops_RH _hoops_IGRH _hoops_IS _hoops_HGPR _hoops_HAIR _hoops_PPR _hoops_HH _hoops_GAR "_hoops_SCSI" */
				if (ANYBIT (_hoops_CHARA, _hoops_ASARA) && ANYBIT (_hoops_CHARA, _hoops_PSARA))
					_hoops_ICSGA->_hoops_ISHIR._hoops_HRGRA = (_hoops_CHARA & _hoops_ASARA);
				_hoops_CHARA &= ~_hoops_ASARA;
			}
			else {
				if (BIT(_hoops_CHARA, M_DIFFUSE))
					_hoops_ICSGA->_hoops_ISHIR._hoops_CSHR = *rgb;
				else if (_hoops_GIARA >= 0)
					_hoops_ICSGA->_hoops_ISHIR.color[_hoops_GIARA] = *rgb;
				else if (BIT(_hoops_CHARA, _hoops_RAGRA))
					_hoops_ICSGA->_hoops_ISHIR.gloss = rgb->red;

				if (BIT(_hoops_CHARA, M_TRANSMISSION)) {
					_hoops_PACHR	_hoops_HACHR;
					HI_RGB_To_HLS(rgb, &_hoops_HACHR);
					_hoops_ICSGA->_hoops_ISHIR._hoops_IRIR = 1.0f - _hoops_HACHR._hoops_HSPHR;
				}
			}
			_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA = _hoops_CHARA;

			if (_hoops_RHARA)
				_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA |= _hoops_CHGRA;
		}
	}

	/* _hoops_SR _hoops_SPIP _hoops_SPR, _hoops_HIH _hoops_SCH _hoops_IIP _hoops_GGHP _hoops_IGI */
	if (_hoops_PGC)
		FREE (_hoops_PGC, _hoops_HIR);

	return _hoops_APRRA;
}


local _hoops_SSGI * _hoops_HSARA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCRPR const &			name)
{
	_hoops_SSGI *					_hoops_APRRA = null;

	_hoops_RCSGA *				_hoops_ISARA = null;
	_hoops_RCSGA *				_hoops_CSARA = null;
	_hoops_RCSGA **				_hoops_SSARA = &_hoops_ISARA;
	bool					error = false;

	char const *	_hoops_RPPA = name.text;
	char const *	_hoops_SSRPR = _hoops_RPPA + name.length;
	while (_hoops_RPPA < _hoops_SSRPR && *_hoops_RPPA == ' ')
		++_hoops_RPPA;

	if (_hoops_RPPA == _hoops_SSRPR) {
		HE_WARNING (HEC_COLOR, HES_NULL_INPUT,"Color list is all blank");
		error = true;
	}
	else do {
		Named_Material	_hoops_GGPRA;
		int				_hoops_RGPRA;
		int				length;
		bool			_hoops_AGPRA;
		char			_hoops_PPARA;

		ZALLOC (_hoops_CSARA, _hoops_RCSGA);
		_hoops_CSARA->findex.type = _hoops_SHGRA;
		_hoops_CSARA->normal.type = _hoops_PPCA;
		_hoops_CSARA->_hoops_ICSGA.type = _hoops_GIGRA;

		ZERO_STRUCT (&_hoops_GGPRA, Named_Material);
		*_hoops_SSARA = _hoops_CSARA;
		_hoops_SSARA = &_hoops_CSARA->next;
		_hoops_CSARA->list.type = _hoops_GIGRA;		// _hoops_CCGR _hoops_SR _hoops_PRPS _hoops_IAII
		_hoops_CSARA->color.colors = &_hoops_CSARA->_hoops_ICSGA;	//

		char const *	_hoops_PGPRA = _hoops_RPPA;

		/*
		** _hoops_HGI _hoops_GRS _hoops_IRHH _hoops_IRS _hoops_GAAA _hoops_GGR _hoops_RH _hoops_AGIR _hoops_CAS _hoops_AICRR _hoops_RHAP
		** _hoops_IRS _hoops_HGPRA("_hoops_PRRRA") _hoops_HRII _hoops_HSAR "_hoops_RSSI=_hoops_PRRRA", _hoops_CR _hoops_GPGA
		** _hoops_CRSIR _hoops_PCPA _hoops_HRGR _hoops_IPIH _hoops_IGS (_hoops_CAGH, _hoops_GPHA...) "_hoops_PRRRA" _hoops_AGSR
		** _hoops_CPHP _hoops_HAGH.
		*/

		if (!HI_Decipher_Color_Target (_hoops_RIGC, &_hoops_PGPRA, _hoops_SSRPR, false, &_hoops_CSARA->list._hoops_GHA, _hoops_SRARA)) {
			_hoops_RPPA = _hoops_PGPRA;
		}
		else {
			_hoops_RPPA = _hoops_PGPRA;
			if (_hoops_RPPA == _hoops_SSRPR || *_hoops_RPPA++ != '=') {
				_hoops_HAARA (&name, _hoops_RPPA);
				error = true;
				break;
			}
		}

		_hoops_CSARA->color._hoops_GHA = _hoops_CSARA->color._hoops_CCCIR = _hoops_CSARA->list._hoops_GHA;

		/* _hoops_CGP _hoops_SR _hoops_HS "_hoops_RSSI = (_hoops_SPI=_hoops_PRRRA, _hoops_IGPRA=5.0), _hoops_APGR=_hoops_HRRRA"
		** _hoops_RGR _hoops_RRGR _hoops_CGPRA _hoops_IS _hoops_SRSIR _hoops_RH _hoops_ARIP _hoops_IPPAR _hoops_IS "_hoops_RSSI".
		** _hoops_GPGP _hoops_RGR _hoops_AGIR (_hoops_SPI...)
		*/
		_hoops_RGGA (_hoops_RPPA == _hoops_SSRPR || *_hoops_RPPA != ' ')
			++_hoops_RPPA;

		_hoops_CSARA->_hoops_ICSGA.name.text = (char *)_hoops_RPPA;
		_hoops_RGPRA = 0;
		_hoops_AGPRA = false;
		_hoops_PPARA = 0;
		_hoops_RGGA (_hoops_RPPA == _hoops_SSRPR || (_hoops_RGPRA == 0 && !_hoops_PPARA && *_hoops_RPPA == ',')) {
			if (*_hoops_RPPA == '(') ++_hoops_RGPRA;
			else if (*_hoops_RPPA == ')') --_hoops_RGPRA;
			else if (*_hoops_RPPA == ',') _hoops_AGPRA=true;
			else if (*_hoops_RPPA == '\'' || *_hoops_RPPA == '"' || *_hoops_RPPA == '`') {
				if (!_hoops_PPARA)
					_hoops_PPARA = *_hoops_RPPA;
				else if (*_hoops_RPPA == _hoops_PPARA)
					_hoops_PPARA = 0;
			}
			++_hoops_RPPA;
		}
		if (_hoops_RGPRA != 0) {
			_hoops_HAARA (&name, _hoops_PGPRA);
			error = true;
			break;
		}

		if ((length = _hoops_RPPA - _hoops_CSARA->_hoops_ICSGA.name.text) > 0) {
			do {
				if (_hoops_CSARA->_hoops_ICSGA.name.text[length - 1] != ' ')
					break;
			} _hoops_RGGA (--length == 0);
		}

		if ((_hoops_CSARA->_hoops_ICSGA.name.length = length) == 0) {
			_hoops_HAARA (&name, _hoops_RPPA);
			error = true;
			break;
		}

#ifndef DISABLE_COLOR_MAPS
		/* _hoops_AIHH _hoops_RPP _hoops_RGR _hoops_HAIR _hoops_HRGR _hoops_IRS _hoops_HAIR _hoops_ARCR _hoops_CIHA
		*/
		if (_hoops_CSARA->_hoops_ICSGA.name.text[0] == '#') {
			_hoops_PGPRA = _hoops_CSARA->_hoops_ICSGA.name.text;
			_hoops_PGPRA++;
			if (HI_Scan_Float (_hoops_RIGC, &_hoops_PGPRA, _hoops_PGPRA+_hoops_CSARA->_hoops_ICSGA.name.length-1, &_hoops_CSARA->findex.value)) {
				/*_hoops_ASIGA _hoops_ASRHR*/
				_hoops_CSARA->findex.value = 0.0f;
			}
			if (_hoops_CSARA->findex.value < -0.5f ||
				_hoops_CSARA->findex.value > (float)_hoops_GPARA + 0.5f) {
				_hoops_SAARA (_hoops_CSARA->findex.value);
				error = true;
			}

			if (error)
				break;

			/* _hoops_IIAC _hoops_SCH -- _hoops_IRS _hoops_HAIR _hoops_HPP _hoops_CIHA */
			_hoops_CSARA->_hoops_ICSGA.name.length = 0;

			_hoops_CSARA->list.type = _hoops_SHGRA;
			_hoops_CSARA->findex._hoops_GHA = _hoops_CSARA->list._hoops_GHA;
			_hoops_CSARA->color.colors = &_hoops_CSARA->findex;
		}
		else
#endif
		{	/* _hoops_HGI _hoops_HAIR _hoops_HRGR _hoops_HAR _hoops_IRS _hoops_HGIR _hoops_CIHA ("#3") */

			ZERO_STRUCT(&_hoops_GGPRA, Named_Material);

			/* _hoops_SGPRA _hoops_IH _hoops_PSHA.	_hoops_HGI _hoops_CRRPR:
			**			- _hoops_GRPRA _hoops_GRR _hoops_RCAP (_hoops_SPI, _hoops_IGPRA, _hoops_AHI.)
			**			- _hoops_RRPRA _hoops_CGGRA _hoops_GAHIR (_hoops_ARPRA _hoops_HRRRA)
			**			- _hoops_IGISR _hoops_GGR _hoops_IGRH _hoops_PAIP _hoops_PRPRA _hoops_PGAP _hoops_HRPRA _hoops_AAPR _hoops_GSGI.
			**	_hoops_HHIGR _hoops_IGISR _hoops_GGR _hoops_IRPRA _hoops_CCA _hoops_RH _hoops_ACPP.
			*/
			if (!HI_Evaluate_Color (_hoops_RIGC, &_hoops_CSARA->_hoops_ICSGA.name, &_hoops_GGPRA, 0, true)) {
				/* (_hoops_RIHH _hoops_AIAH _hoops_CRPPR) */
				HI_Free_Material_Names (&_hoops_GGPRA, 1);
				error = true;
				break;
			}

			/* _hoops_HGI _hoops_RRGR _hoops_IHCI _hoops_RH _hoops_APIR/_hoops_HH _hoops_IPPHR _hoops_SGS _hoops_CSAP
			** _hoops_CRPRA _hoops_GGSR _hoops_CRGR _hoops_SRPRA _hoops_IAPR _hoops_IS _hoops_RH _hoops_GCRRA _hoops_HRPR.
			*/
			if (_hoops_GGPRA._hoops_PRGRA == (M_DIFFUSE | _hoops_RHGRA) &&
				!_hoops_GGPRA._hoops_SCA) {		/* _hoops_IRHH _hoops_SCH _hoops_IHGP */

				_hoops_CSARA->_hoops_ICSGA.name.length = 0;

				_hoops_CSARA->list.type = _hoops_PPCA;
				_hoops_CSARA->normal._hoops_GHA = _hoops_CSARA->list._hoops_GHA;
				_hoops_CSARA->color.colors = &_hoops_CSARA->normal;
				HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, &_hoops_CSARA->normal.rgb);
				HI_Copy_Name (&_hoops_GGPRA._hoops_IRGRA, &_hoops_CSARA->normal.name);
			}
			else  {
				_hoops_CSARA->_hoops_ICSGA._hoops_GHA = _hoops_CSARA->list._hoops_GHA;
				_hoops_CSARA->color.colors = &_hoops_CSARA->_hoops_ICSGA;

				_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR._hoops_PRGRA = _hoops_GGPRA._hoops_PRGRA;
				_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR._hoops_HRGRA = _hoops_GGPRA._hoops_HRGRA;

				if (ANYBIT (_hoops_GGPRA._hoops_PRGRA, _hoops_ASARA)) {
					if (BIT (_hoops_GGPRA._hoops_PRGRA, M_DIFFUSE)) {
						HI_Copy_Name (&_hoops_GGPRA._hoops_IRGRA, &_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR._hoops_IRGRA);
						HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA._hoops_CSHR, &_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR._hoops_CSHR);
					}
					for (int i=0; i<_hoops_CRGRA; i++) {
						HI_Copy_Name (&_hoops_GGPRA.name[i], &_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR.name[i]);
						if (BIT (_hoops_GGPRA._hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i]))
							HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_GGPRA.color[i], &_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR.color[i]);
					}
				}
				/* _hoops_GAPRA _hoops_GRSS _hoops_RH _hoops_SGSS _hoops_RPR _hoops_GPP _hoops_IRPRA.
				** _hoops_PS _hoops_CHR _hoops_HGIPR _hoops_RGR _hoops_HH _hoops_CRS _hoops_SAII _hoops_IAPR _hoops_IS _hoops_GCRRA
				*/
				if (ANYBIT (_hoops_GGPRA._hoops_PRGRA, _hoops_PSARA)) {
					_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR._hoops_SCA = _hoops_GGPRA._hoops_SCA;
					_hoops_GGPRA._hoops_SCA = null;
					if (_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR._hoops_SCA)
						_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR._hoops_PRGRA |= _hoops_CHGRA;
					for (int i=0; i<_hoops_GAGRA; i++) {
						_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR.texture[i] = _hoops_GGPRA.texture[i];
						_hoops_GGPRA.texture[i] = null;
						if (_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR.texture[i])
							_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR._hoops_PRGRA |= _hoops_CHGRA;
					}
				}

				if (BIT (_hoops_GGPRA._hoops_PRGRA, M_TRANSMISSION))
					_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR._hoops_IRIR = _hoops_GGPRA._hoops_IRIR;

				if (BIT (_hoops_GGPRA._hoops_PRGRA, _hoops_RAGRA))
					_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR.gloss = _hoops_GGPRA.gloss;

				if (BIT (_hoops_GGPRA._hoops_PRGRA, _hoops_AAGRA))
					_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR._hoops_PAGRA = _hoops_GGPRA._hoops_PAGRA;
			}

			HI_Free_Material_Names (&_hoops_GGPRA, 1);
		}

	/* _hoops_HGI _hoops_HRGR _hoops_RH _hoops_HGSI _hoops_HAPR _hoops_SGS _hoops_RAPRA _hoops_RHIR _hoops_RH _hoops_RRCIR _hoops_HIGR _hoops_IIGR "_hoops_APGR = _hoops_HRRRA, _hoops_SPPR = _hoops_PRRRA, ..." */
	} while (++_hoops_RPPA < _hoops_SSRPR);

	_hoops_ACSGA ** _hoops_ASRGR = null;

	if (!error) {
		ZALLOC (_hoops_APRRA, _hoops_SSGI);
		_hoops_ASRGR = &_hoops_APRRA->colors;
	}

	if ((_hoops_CSARA = _hoops_ISARA) != null) do {

		_hoops_ISARA = _hoops_CSARA->next;

		if (_hoops_APRRA != null && 
			_hoops_CSARA->list._hoops_GHA != Color_NONE) {
			*_hoops_ASRGR = HI_Copy_Colors (_hoops_CSARA->color.colors, null);
			_hoops_APRRA->_hoops_GHA |= _hoops_CSARA->color._hoops_GHA;
			_hoops_APRRA->_hoops_CCCIR |= _hoops_CSARA->color._hoops_GHA;
			_hoops_ASRGR = &(*_hoops_ASRGR)->next;
		}

		switch (_hoops_CSARA->list.type) {
			case _hoops_SHGRA: {
			}	break;

			case _hoops_PPCA: {
				/*_hoops_ASIGA _hoops_AICRR _hoops_RIAGR _hoops_IAPGR _hoops_RGR _hoops_GGSR _hoops_HIH _hoops_SCH _hoops_CSAP _hoops_AAPRA _hoops_HIS... */
				_hoops_RGAIR (_hoops_CSARA->normal.name);
			}	break;

			case _hoops_GIGRA: {
				HI_Free_Material_Names (&_hoops_CSARA->_hoops_ICSGA._hoops_ISHIR, 1);
				/* _hoops_PCARA (_hoops_GCRRA->_hoops_RHAR._hoops_RSIRR); */
			}	break;
		}

		FREE (_hoops_CSARA, struct _hoops_RCSGA);

	} while ((_hoops_CSARA = _hoops_ISARA) != null);

	return _hoops_APRRA;
}

local _hoops_SSGI * _hoops_PAPRA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCRPR const &			what, 
	char const *			style,
	float					a,
	float					b,
	float					c)
{
	_hoops_SSGI *			_hoops_APRRA = null;
	Color_Object	_hoops_GHA;
	RGB				rgb;
	char const *	_hoops_RPPA = what.text;

	if (what.length == 0 ||
		!HI_Decipher_Color_Target (_hoops_RIGC, &_hoops_RPPA, _hoops_RPPA + what.length, true, &_hoops_GHA, _hoops_SRARA) ||
		_hoops_RPPA != what.text + what.length) {
		_hoops_HAARA (&what, _hoops_RPPA);
	}
	else {

		bool	error = false;

		while (*style == ' ')
			++style;

		if ((style[0] == 'r' || style[0] == 'R') &&
			(style[1] == 'g' || style[1] == 'G') &&
			(style[2] == 'b' || style[2] == 'B')) {

			if (!(0.0f <= a && a <= 1.0f && 0.0f <= b && b <= 1.0f && 0.0f <= c && c <= 1.0f)) {
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_RGB, "RGB value not in the range 0..1");
				error = true;
			}

			rgb.red = a;
			rgb.green = b;
			rgb.blue = c;
		}
		else if ((style[1] == 'l' || style[1] == 'L') &&
			(style[0] == 'h' || style[0] == 'H') &&		 /* (_hoops_GGSR _hoops_IIGR _hoops_AGR _hoops_GPP _hoops_AHAR) */
			(style[2] == 's' || style[2] == 'S')) {
			
			if (!(-1e5f <= a && a <= 1e5f)) {
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_HUE, "Hue has unreasonable magnitude");
				error = true;
			}

			if (!(0.0f <= b && b <= 1.0f)) {
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_LIGHTNESS, "Lightness is not in the range 0..1");
				error = true;
			}

			if (c < 0.0f) {
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_SATURATION, "Saturation is negative");
				error = true;
			}

			if ((b < 0.5f && c > 2.0f*b) || (b >= 0.5f && c > 2.0f - 2.0f*b)) {
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_SATURATION, "Too much saturation, given the lightness (try HSV)");
				error = true;
			}

			_hoops_PACHR	_hoops_HACHR;
			_hoops_HACHR._hoops_SCPHR = a;
			_hoops_HACHR._hoops_HSPHR = b;
			_hoops_HACHR._hoops_ISPHR = c;

			if (!error) 
				HI_HLS_To_RGB (&_hoops_HACHR, &rgb);
		}
		else if ((style[1] == 's' || style[1] == 'S') &&
			(style[0] == 'h' || style[0] == 'H') &&		 /* (_hoops_GGSR _hoops_IIGR _hoops_AGR _hoops_GPP _hoops_AHAR) */
			(style[2] == 'v' || style[2] == 'V')) {
			
			if (!(-1e5f <= a && a <= 1e5f)) {
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_HUE, "Hue has unreasonable magnitude");
				error = true;
			}

			if (!(0.0f <= c && c <= 1.0f)) {
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_LIGHTNESS,  "'Value' (lightness) is not in the range 0..1");
				error = true;
			}

			if (!(0.0f <= b && b <= c)) {
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_SATURATION, "Saturation is not in the range 0..'Value'");
				error = true;
			}

			_hoops_PACHR	_hoops_HACHR;
			_hoops_HACHR._hoops_SCPHR = a;
			_hoops_HACHR._hoops_ISPHR = b;
			_hoops_HACHR._hoops_HSPHR = c - 0.5f * b;

			if (!error) 
				HI_HLS_To_RGB (&_hoops_HACHR, &rgb);
		}
		else if ((style[0] == 'h' || style[0] == 'H') &&
			(style[1] == 'i' || style[1] == 'I') &&
			(style[2] == 'c' || style[2] == 'C')) {
				
			if (!(-1e5f <= a && a <= 1e5f)) {
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_HUE, "Hue has unreasonable magnitude");
				error = true;
			}

			if (!(0.0f <= c && c <= 1.0f)) {
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_LIGHTNESS, "Intensity (lightness) is not in the range 0..1");
				error = true;
			}

			if (!(0.0f <= b && b <= 1.0f)) {
				HE_ERROR (HEC_COLOR, HES_OUT_OF_RANGE_CHROMACITY, "Chromaticity (saturation) is not in the range 0..1");
				error = true;
			}

			_hoops_PACHR	_hoops_HACHR;
			_hoops_HACHR._hoops_SCPHR = a;
			_hoops_HACHR._hoops_HSPHR = b;
			if (_hoops_HACHR._hoops_HSPHR < 0.5f)
				_hoops_HACHR._hoops_ISPHR = c * 2.0f * _hoops_HACHR._hoops_HSPHR;
			else
				_hoops_HACHR._hoops_ISPHR = c * 2.0f * (1.0f - _hoops_HACHR._hoops_HSPHR);

			if (!error)
				HI_HLS_To_RGB (&_hoops_HACHR, &rgb);
		}
		else {
			HE_ERROR2 (HEC_COLOR, HES_INVALID_COLOR_SPACE,
				Sprintf_S (null, "Color system '%s' not recognized -", style), "Should be HLS, HIC, HSV, or RGB");
			error = true;
		}

		if (!error) {
			ZALLOC (_hoops_APRRA, _hoops_SSGI);

			_hoops_APCA * normal;
			ZALLOC (normal, _hoops_APCA);

			normal->rgb = rgb;
			normal->type = _hoops_PPCA;
			_hoops_APRRA->_hoops_GHA = _hoops_APRRA->_hoops_CCCIR = normal->_hoops_GHA = _hoops_GHA;
			_hoops_APRRA->colors = normal;
		}
	
	}

	return _hoops_APRRA;
}



local _hoops_SSGI * _hoops_HAPRA(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCRPR const &			what, 
	float					index)
{
	_hoops_SSGI *			_hoops_APRRA = null;
	char const *	_hoops_RPPA = what.text;
	Color_Object 	_hoops_GHA;

	if (what.length == 0 ||
		!HI_Decipher_Color_Target (_hoops_RIGC, &_hoops_RPPA, _hoops_RPPA + what.length, true, &_hoops_GHA, _hoops_SRARA) ||
		_hoops_RPPA != what.text + what.length) {
		_hoops_HAARA (&what, _hoops_RPPA);
	}
	else {
		ZALLOC (_hoops_APRRA, _hoops_SSGI);

		_hoops_PCSGA * findex;
		ZALLOC (findex, _hoops_PCSGA);

		findex->value = index;
		findex->type = _hoops_SHGRA;
		_hoops_APRRA->_hoops_GHA = _hoops_APRRA->_hoops_CCCIR = findex->_hoops_GHA = _hoops_GHA;
		_hoops_APRRA->colors = findex;
	}

	return _hoops_APRRA;
}


HC_INTERFACE void HC_CDECL HC_Set_Explicit_Color (
	char const *	type,
	char const *	channel,
	Point const *	rgb,
	char const *	texture,
	char const *	options)
{
	_hoops_PAPPR context("Set_Explicit_Color");

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT rgb;\n");
	++HOOPS_WORLD->_hoops_ISPPR;
	if (rgb) {
		HI_Dump_Code (Sprintf_F (null, "rgb.x = %f;", rgb->x));
		HI_Dump_Code (Sprintf_F (null, "rgb.y = %f;", rgb->y));
		HI_Dump_Code (Sprintf_F (null, "rgb.z = %f;", rgb->z));
	}
	HI_Dump_Code (Sprintf_SS (null, "\nHC_Set_Explicit_Color (%S, %S,", type, channel));
	if (rgb)
		HI_Dump_Code ("&rgb,");
	else
		HI_Dump_Code ("NULL,");
	if (texture && texture[0] != '\0')
		HI_Dump_Code (Sprintf_S (null, "%S,", texture));
	else
		HI_Dump_Code ("NULL,");
	if (options && options[0] != '\0')
		HI_Dump_Code (Sprintf_S (null, "%S", options));
	else
		HI_Dump_Code ("NULL");
	HI_Dump_Code (");\n}");
	--HOOPS_WORLD->_hoops_ISPPR;
	);


	_hoops_HCRPR	what;
	HI_Canonize_Chars (type, &what);

	bool	used = false;
	_hoops_SSGI * _hoops_APRRA = _hoops_SPARA(context, what, channel, (RGB *)rgb, texture, options);

	if (_hoops_APRRA != null) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_IAPRA)) != null) {

			_hoops_CRARA (context, target, _hoops_APRRA);

			if (target->type == _hoops_CIRIR) {
				_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
				used = HI_Set_Color(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR, _hoops_APRRA);
			}
			else 
				used = HI_Set_Color(context, target, _hoops_APRRA);

			_hoops_IRRPR();
		}

		if (!used) {
			HI_Free_Colors (_hoops_APRRA->colors);
			FREE (_hoops_APRRA, _hoops_SSGI);
		}	
	}

	_hoops_RGAIR(what);
}



HC_INTERFACE void HC_CDECL HC_Set_Color (
	char const *	cname)
{
	_hoops_PAPPR context("Set_Color");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Color (%S);\n", cname));
	);

	_hoops_HCRPR	name;
	HI_Canonize_Chars_Quoted (cname, &name, true);

	bool	used = false;
	_hoops_SSGI *	_hoops_APRRA = _hoops_HSARA(context, name);

	if (_hoops_APRRA != null) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_IAPRA)) != null) {

			_hoops_CRARA (context, target, _hoops_APRRA);
		
			if (target->type == _hoops_CIRIR) {
				_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
				used = HI_Set_Color(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR, _hoops_APRRA);
			}
			else 
				used = HI_Set_Color(context, target, _hoops_APRRA);

			_hoops_IRRPR();
		}

		if (!used) {
			HI_Free_Colors (_hoops_APRRA->colors);
			FREE (_hoops_APRRA, _hoops_SSGI);
		}
	}

	_hoops_RGAIR(name);
}


HC_INTERFACE void HC_CDECL HC_Set_Color_By_Index (
	char const *	_hoops_CAPRA,
	int				index)
{
	_hoops_PAPPR context("Set_Color_By_Index");

#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SD (null, "HC_Set_Color_By_Index (%S, %d);\n", _hoops_CAPRA, index));
	);

	if (index < 0 || (long)index > (long)_hoops_GPARA) {
		_hoops_RPARA (index);
		return;
	}

	_hoops_HCRPR	what;
	HI_Canonize_Chars (_hoops_CAPRA, &what);

	bool	used = false;
	_hoops_SSGI * _hoops_APRRA = _hoops_HAPRA(context, what, (float)index);

	if (_hoops_APRRA != null) {
		
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_IAPRA)) != null) {

			_hoops_CRARA (context, target, _hoops_APRRA);

			if (target->type == _hoops_CIRIR) {
				_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
				used = HI_Set_Color(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR, _hoops_APRRA);
			}
			else 
				used = HI_Set_Color(context, target, _hoops_APRRA);

			_hoops_IRRPR();
		}

		if (!used) {
			HI_Free_Colors (_hoops_APRRA->colors);
			FREE (_hoops_APRRA, _hoops_SSGI);
		}
	}

	_hoops_RGAIR (what);
#endif
}


HC_INTERFACE void HC_CDECL HC_Set_Color_By_FIndex (
	char const *	_hoops_CAPRA,
	double			findex)
{
	_hoops_PAPPR context("Set_Color_By_FIndex");

#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code (_hoops_SAPRA (null, "HC_Set_Color_By_FIndex (%S, %F);\n", _hoops_CAPRA, findex));
	);

	if (findex < -0.5f || findex >= (float)_hoops_GPARA + 0.5f) {
		_hoops_SAARA (findex);
		return;
	}

	_hoops_HCRPR	what;
	HI_Canonize_Chars (_hoops_CAPRA, &what);


	bool	used = false;
	_hoops_SSGI * _hoops_APRRA = _hoops_HAPRA(context, what, findex);

	if (_hoops_APRRA != null) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_IAPRA)) != null) {

			_hoops_CRARA (context, target, _hoops_APRRA);

			if (target->type == _hoops_CIRIR) {
				_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
				used = HI_Set_Color(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR, _hoops_APRRA);
			}
			else 
				used = HI_Set_Color(context, target, _hoops_APRRA);

			_hoops_IRRPR();
		}

		if (!used) {
			HI_Free_Colors (_hoops_APRRA->colors);
			FREE (_hoops_APRRA, _hoops_SSGI);
		}	
	}

	_hoops_RGAIR (what);
#endif
}



HC_INTERFACE void HC_CDECL HC_Set_Color_By_Value (
	char const *	_hoops_CAPRA,
	char const *	style,
	double			a,
	double			b,
	double			c)
{
	_hoops_PAPPR context("Set_Color_By_Value");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Set_Color_By_Value (%S, %S, ", _hoops_CAPRA, style));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", a, b));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", c));
	);


	_hoops_HCRPR	what;
	HI_Canonize_Chars (_hoops_CAPRA, &what);

	bool	used = false;
	_hoops_SSGI * _hoops_APRRA = _hoops_PAPRA(context, what, style, (float)a, (float)b, (float)c);

	if (_hoops_APRRA != null) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_IAPRA)) != null) {

			_hoops_CRARA (context, target, _hoops_APRRA);

			if (target->type == _hoops_CIRIR) {
				_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
				used = HI_Set_Color(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR, _hoops_APRRA);
			}
			else 
				used = HI_Set_Color(context, target, _hoops_APRRA);

			_hoops_IRRPR();
		}

		if (!used) {
			HI_Free_Colors (_hoops_APRRA->colors);
			FREE (_hoops_APRRA, _hoops_SSGI);
		}
	}

	_hoops_RGAIR (what);
}


GLOBAL_FUNCTION void HI_Unset_Color(
	_hoops_AIGPR *	_hoops_RIGC,
	Polyhedron *			_hoops_IPRI,
	int						offset,
	_hoops_IPRRA				_hoops_GCRIR)
{
	_hoops_ICIIR(_hoops_RIGC);
	ASSERT(_hoops_GCRIR == _hoops_SCRIR || _hoops_GCRIR == _hoops_CCRIR || _hoops_GCRIR == _hoops_ICRIR || _hoops_GCRIR == _hoops_GSRIR);

	switch (_hoops_GCRIR) {

#ifndef _hoops_GCGHR
		case _hoops_SCRIR: {
			if (_hoops_IPRI->type == _hoops_CSIP) {
				PolyCylinder alter *		_hoops_HSPIR = (PolyCylinder *)_hoops_IPRI;
				_hoops_CGHIR *			flags;

				_hoops_AGHIR *	_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;

				if ((flags = _hoops_PGHIR->flags) == null ||
					!ANYBIT (flags[offset], _hoops_GPPRA|_hoops_RPPRA)) {
					HE_ERROR (HEC_VERTEX, HES_COLOR, "No color set on this vertex");
					return;
				}

				if (BIT (flags[offset], _hoops_SHRRA)) {
					if (--_hoops_PGHIR->_hoops_SCHPR == 0) {
						if (_hoops_PGHIR->ecolors != _hoops_PGHIR->fcolors)
							FREE_ARRAY (_hoops_PGHIR->ecolors, _hoops_HSPIR->point_count, RGB);
						_hoops_PGHIR->ecolors = null;
					}
					else
						_hoops_PGHIR->ecolors[offset] = _hoops_GPSR::_hoops_RPSR;
				}
				else if (BIT (flags[offset], _hoops_IHRRA)) {
					if (--_hoops_PGHIR->_hoops_CCHPR == 0) {
						if (_hoops_PGHIR->_hoops_HGHIR != _hoops_PGHIR->_hoops_IGHIR)
							FREE_ARRAY (_hoops_PGHIR->_hoops_HGHIR, _hoops_HSPIR->point_count, _hoops_ACGHR);
						_hoops_PGHIR->_hoops_HGHIR = null;
					}
					else
						_hoops_PGHIR->_hoops_HGHIR[offset] = 0.0f;
				}

				if (BIT (flags[offset], _hoops_GIRRA)) {
					if (--_hoops_PGHIR->_hoops_RCRHR == 0) {
						if (_hoops_PGHIR->fcolors != _hoops_PGHIR->ecolors)
							FREE_ARRAY (_hoops_PGHIR->fcolors, _hoops_HSPIR->point_count, RGB);
						_hoops_PGHIR->fcolors = null;
					}
					else
						_hoops_PGHIR->fcolors[offset] = _hoops_GPSR::_hoops_RPSR;
				}
				else if (BIT (flags[offset], _hoops_CHRRA)) {
					if (--_hoops_PGHIR->_hoops_SIRHR == 0) {
						if (_hoops_PGHIR->_hoops_IGHIR != _hoops_PGHIR->_hoops_HGHIR)
							FREE_ARRAY (_hoops_PGHIR->_hoops_IGHIR, _hoops_HSPIR->point_count, _hoops_ACGHR);
						_hoops_PGHIR->_hoops_IGHIR = null;
					}
					else
						_hoops_PGHIR->_hoops_IGHIR[offset] = 0.0f;
				}

				flags[offset] &= ~(_hoops_GPPRA|_hoops_RPPRA);

				if (_hoops_PGHIR->_hoops_RCRHR == 0 &&
					_hoops_PGHIR->_hoops_SIRHR == 0 &&
					_hoops_PGHIR->_hoops_SCHPR == 0 &&
					_hoops_PGHIR->_hoops_CCHPR == 0) {
					/* _hoops_HCR _hoops_PPRGA! */
					FREE_ARRAY (_hoops_PGHIR->flags, _hoops_HSPIR->point_count, _hoops_CGHIR);
					FREE (_hoops_PGHIR, _hoops_AGHIR);
					_hoops_HSPIR->_hoops_RGHIR = null;
				}
			}
			else {
				Local_Vertex_Attributes *	_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;
				int	_hoops_PIRRA = _hoops_SPRI->_hoops_HIRRA;
				Local_Vertex_Flags * flags = _hoops_SPRI->_hoops_CHHPR(offset);

				if (!ANYBIT (*flags, _hoops_APPRA|_hoops_PPPRA|_hoops_HPPRA)) {
					HE_ERROR (HEC_VERTEX, HES_COLOR, "No color set on this vertex");
					return;
				}

				if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR)) {
					/* _hoops_SR _hoops_HS _hoops_SAHR _hoops_IPPRA _hoops_IRS _hoops_RHPC _hoops_GPP _hoops_IRS _hoops_RSRA _hoops_GPHA.  _hoops_CGP _hoops_RIAGR _hoops_RPII _hoops_GRP _hoops_RH
					_hoops_GHRHR _hoops_RIP, _hoops_SR _hoops_PAH'_hoops_RA _hoops_CPRIR _hoops_PPR _hoops_SR _hoops_HS _hoops_IS _hoops_CCPP _hoops_RH _hoops_IIRRA->_hoops_SGI _hoops_CRPR (_hoops_PPR _hoops_HSPC _hoops_SCH _hoops_IS _hoops_RH _hoops_GHRHR _hoops_RIP)*/
					ZALLOC_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					for (int i = 0; i < _hoops_IPRI->point_count; i++)
						_hoops_IPRI->local_vertex_attributes.flags[i] = _hoops_IPRI->local_vertex_attributes._hoops_SGRHR;
					_hoops_IPRI->polyhedron_flags |= _hoops_CGRHR;
					flags = _hoops_SPRI->_hoops_CHHPR(offset);
				}

				if (BIT (*flags, _hoops_HCRRA)) {
					if (--_hoops_SPRI->_hoops_ICRRA == 0) {
						if (_hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->ecolors && _hoops_SPRI->_hoops_PAHIR != _hoops_SPRI->fcolors)
							FREE_ARRAY (_hoops_SPRI->_hoops_PAHIR, _hoops_IPRI->point_count, RGB);
						_hoops_SPRI->_hoops_PAHIR = null;
					}
					else
						_hoops_SPRI->_hoops_PAHIR[offset] = _hoops_GPSR::_hoops_RPSR;

					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_HCRRA;
				}
				else if (BIT (*flags, _hoops_SIRRA)) {
					if (--_hoops_SPRI->_hoops_PCRRA == 0) {
						if (_hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_HGHIR && _hoops_SPRI->_hoops_HAHIR != _hoops_SPRI->_hoops_IGHIR)
							FREE_ARRAY (_hoops_SPRI->_hoops_HAHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
						_hoops_SPRI->_hoops_HAHIR = null;
					}
					else
						_hoops_SPRI->_hoops_HAHIR[offset] = 0.0f;

					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_SIRRA;
				}
				else if (BIT (*flags, _hoops_CCRRA)) {
					if (--_hoops_SPRI->_hoops_HIRRA == 0) {
						FREE_ARRAY (_hoops_SPRI->_hoops_IAHIR, _hoops_IPRI->point_count, RGBAS32);
						_hoops_SPRI->_hoops_IAHIR = null;
					}
					else
						_hoops_SPRI->_hoops_IAHIR[offset] = _hoops_CAHSR::_hoops_SAHSR;

					_hoops_IPRI->_hoops_AGRHR &= ~_hoops_CCRRA;
				}

				if (BIT (*flags, _hoops_PPHPR)) {
					if (--_hoops_SPRI->_hoops_SCHPR == 0) {
						if (_hoops_SPRI->ecolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->ecolors != _hoops_SPRI->fcolors)
							FREE_ARRAY (_hoops_SPRI->ecolors, _hoops_IPRI->point_count, RGB);
						_hoops_SPRI->ecolors = null;
					}
					else
						_hoops_SPRI->ecolors[offset] = _hoops_GPSR::_hoops_RPSR;

					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_HPHPR;
				}
				else if (BIT(*flags, _hoops_RPHPR)) {
					if (--_hoops_SPRI->_hoops_CCHPR == 0) {
						if (_hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_HGHIR != _hoops_SPRI->_hoops_IGHIR)
							FREE_ARRAY (_hoops_SPRI->_hoops_HGHIR, _hoops_IPRI->point_count, _hoops_ACGHR);
						_hoops_SPRI->_hoops_HGHIR = null;
					}
					else
						_hoops_SPRI->_hoops_HGHIR[offset] = 0.0f;

					_hoops_IPRI->_hoops_RSHPR &= ~_hoops_APHPR;
				}

				if (BIT (*flags, _hoops_AARHR)) {
					if (--_hoops_SPRI->_hoops_RCRHR == 0) {
						if (_hoops_SPRI->fcolors != _hoops_SPRI->_hoops_PAHIR && _hoops_SPRI->fcolors != _hoops_SPRI->ecolors)
							FREE_ARRAY (_hoops_SPRI->fcolors, _hoops_IPRI->point_count +
														_hoops_IPRI->_hoops_GCRHR, RGB);
						_hoops_SPRI->fcolors = null;
					}
					else
						_hoops_SPRI->fcolors[offset] = _hoops_GPSR::_hoops_RPSR;

					_hoops_IPRI->_hoops_ACRHR &= ~_hoops_PARHR;
				}
				else if (BIT (*flags, _hoops_HARHR)) {
					if (--_hoops_SPRI->_hoops_SIRHR == 0) {
						if (_hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HAHIR && _hoops_SPRI->_hoops_IGHIR != _hoops_SPRI->_hoops_HGHIR)
							FREE_ARRAY (_hoops_SPRI->_hoops_IGHIR, _hoops_IPRI->point_count +
														_hoops_IPRI->_hoops_GCRHR, _hoops_ACGHR);
						_hoops_SPRI->_hoops_IGHIR = null;
					}
					else
						_hoops_SPRI->_hoops_IGHIR[offset] = 0.0f;

					_hoops_IPRI->_hoops_ACRHR &= ~_hoops_IARHR;
				}

				*flags &= ~_hoops_CPPRA;

				if (_hoops_SPRI->lvf_uniform(_hoops_IPRI->point_count)) {
					_hoops_SPRI->_hoops_SGRHR = _hoops_SPRI->flags[0];
					FREE_ARRAY(_hoops_IPRI->local_vertex_attributes.flags, _hoops_IPRI->point_count, Local_Vertex_Flags);
					_hoops_IPRI->polyhedron_flags &= ~_hoops_CGRHR;
					_hoops_SPRI->flags = 0;
				}

				if (_hoops_IPRI->owner != null) {
					if (_hoops_PIRRA != 0) {
						if (_hoops_SPRI->_hoops_HIRRA == 0)
							HI_Less_Transparencies (_hoops_RIGC, _hoops_IPRI->owner, 1);
					}
					else {
						if (_hoops_SPRI->_hoops_HIRRA != 0)
							HI_More_Transparencies (_hoops_RIGC, _hoops_IPRI->owner, 1);
					}
				}
			}

			_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_GGARA|_hoops_RPSIR);
		}	break;

		case _hoops_CCRIR: {
			_hoops_GHHPR *		flags;
			_hoops_RPGHR *	lea = &_hoops_IPRI->_hoops_IHHPR;

			if ((flags = lea->flags) == null ||
				!ANYBIT (flags[offset], _hoops_SSRRA|_hoops_RPGI)) {
				HE_ERROR (HEC_EDGE, HES_COLOR, "No color set on this edge");
				return;
			}

			if (BIT (flags[offset], _hoops_RPGI)) {
				if (--lea->_hoops_PSRRA == 0) {
					FREE_ARRAY (lea->findices, _hoops_IPRI->_hoops_SPHA, _hoops_ACGHR);
					lea->findices = null;
				}
				else
					lea->findices[offset] = 0.0f;

				_hoops_IPRI->_hoops_RSHPR &= ~_hoops_RPGI;
			}
			else {
				if (--lea->_hoops_HSRRA == 0) {
					FREE_ARRAY (lea->colors, _hoops_IPRI->_hoops_SPHA, RGB);
					lea->colors = null;
				}
				else
					lea->colors[offset] = _hoops_GPSR::_hoops_RPSR;

				_hoops_IPRI->_hoops_RSHPR &= ~_hoops_SSRRA;
			}

			flags[offset] &= ~(_hoops_RPGI|_hoops_SSRRA);

			_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_GGARA|_hoops_RPSIR);
		}	break;

		case _hoops_ICRIR: {
			Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
			_hoops_GIIPR *		flags = _hoops_CPRI->flags;

			if (flags != null &&
				!ANYBIT (flags[offset], LFA_EXPLICIT_COLOR_BY_VALUE|LFA_EXPLICIT_COLOR_BY_FINDEX) ||
				flags == null && !ANYBIT (_hoops_CPRI->_hoops_SGRHR, LFA_EXPLICIT_COLOR_BY_VALUE|LFA_EXPLICIT_COLOR_BY_FINDEX)) {
				HE_ERROR (HEC_FACE, HES_COLOR, "No color set on this face");
				return;
			}

			/* _hoops_SR _hoops_CHR _hoops_AHCA _hoops_IS _hoops_IPPRA _hoops_IRS _hoops_HAIR _hoops_GPP _hoops_HAR _hoops_HCR
				_hoops_IIGR _hoops_RH _hoops_RSSI, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IRS _hoops_HSP _hoops_SGI _hoops_CRPR
				_hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HS _hoops_SPR */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				for (int i = 0; i < _hoops_IPRI->face_count; i++)
					_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
			}

			if (BIT (*_hoops_CPRI->_hoops_CHHPR(offset), LFA_EXPLICIT_COLOR_BY_FINDEX)) {
				if (--_hoops_CPRI->_hoops_PSRRA == 0) {
					FREE_ARRAY (_hoops_CPRI->findices, _hoops_IPRI->face_count, _hoops_ACGHR);
					_hoops_CPRI->findices = null;
				}
				else
					_hoops_CPRI->findices[offset] = 0.0f;
			}
			else {
				if (--_hoops_CPRI->_hoops_HSRRA == 0) {
					FREE_ARRAY (_hoops_CPRI->colors, _hoops_IPRI->face_count, RGB);
					_hoops_CPRI->colors = null;
				}
				else
					_hoops_CPRI->colors[offset] = _hoops_GPSR::_hoops_RPSR;
			}

			*_hoops_CPRI->_hoops_CHHPR(offset) &= ~(LFA_EXPLICIT_COLOR_BY_FINDEX|LFA_EXPLICIT_COLOR_BY_VALUE);
			*_hoops_CPRI->_hoops_CHHPR(offset) |= _hoops_IGAHR;

			_hoops_IPRI->polyhedron_flags |= _hoops_CCRHR;

			_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
		}	break;

		case _hoops_GSRIR: {
			int						_hoops_ISRRA = 0;
			Local_Face_Attributes *	_hoops_CPRI = &_hoops_IPRI->local_face_attributes;
			int const *				regions	 = _hoops_CPRI->regions;

			if (regions == null && offset != 0) {
				HE_ERROR (HEC_REGION, HES_COLOR, "No colors set in this region");
				return;
			}

			/* _hoops_SR _hoops_CHR _hoops_AHCA _hoops_IS _hoops_IPPRA _hoops_IRS _hoops_HAIR _hoops_GPP _hoops_HAR _hoops_HCR
				_hoops_IIGR _hoops_RH _hoops_RSSI, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IRS _hoops_HSP _hoops_SGI _hoops_CRPR
				_hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HS _hoops_SPR */
			if (!BIT(_hoops_IPRI->polyhedron_flags, _hoops_APRHR)) {
				ZALLOC_ARRAY(_hoops_IPRI->local_face_attributes.flags, _hoops_IPRI->face_count, _hoops_GIIPR);
				for (int i = 0; i < _hoops_IPRI->face_count; i++)
					_hoops_IPRI->local_face_attributes.flags[i] = _hoops_IPRI->local_face_attributes._hoops_SGRHR;
				_hoops_IPRI->polyhedron_flags |= _hoops_APRHR;
			}

			for (int i=0; i<_hoops_IPRI->face_count; i++) {
				if (regions == null || regions[i] == offset) {
					if (BIT (*_hoops_CPRI->_hoops_CHHPR(i), LFA_EXPLICIT_COLOR_BY_FINDEX)) {
						if (--_hoops_CPRI->_hoops_PSRRA == 0) {
							FREE_ARRAY (_hoops_CPRI->findices, _hoops_IPRI->face_count, _hoops_ACGHR);
							_hoops_CPRI->findices = null;
						}
						else
							_hoops_CPRI->findices[i] = 0.0f;

						_hoops_ISRRA |= LFA_EXPLICIT_COLOR_BY_FINDEX;
					}
					else if (BIT (*_hoops_CPRI->_hoops_CHHPR(i), LFA_EXPLICIT_COLOR_BY_VALUE)) {
						if (--_hoops_CPRI->_hoops_HSRRA == 0) {
							FREE_ARRAY (_hoops_CPRI->colors, _hoops_IPRI->face_count, RGB);
							_hoops_CPRI->colors = null;
						}
						else
							_hoops_CPRI->colors[i] = _hoops_GPSR::_hoops_RPSR;

						_hoops_ISRRA |= LFA_EXPLICIT_COLOR_BY_VALUE;
					}

					*_hoops_CPRI->_hoops_CHHPR(i) &= ~(LFA_EXPLICIT_COLOR_BY_FINDEX|LFA_EXPLICIT_COLOR_BY_VALUE);
				}
			}

			if (_hoops_ISRRA != 0) {
				if (_hoops_IPRI->tristrips != null) {
					Tristrip *		ts = _hoops_IPRI->tristrips;

					do if (ts->face_attributes.region == offset) {
						ts->face_attributes.flags &= ~_hoops_IACHR;
						ts->_hoops_CPGPR |= _hoops_GPSIR;
					} while ((ts = ts->next) != null);
				}

				_hoops_SASIR (_hoops_RIGC, _hoops_IPRI, _hoops_IHSSR|_hoops_SIGPR|_hoops_RPSIR);
			}
			else
				HE_ERROR (HEC_REGION, HES_COLOR, "No colors set in this region");
		}	break;
#endif
	}

}

HC_INTERFACE void HC_CDECL HC_UnSet_Color (void)
{
	_hoops_PAPPR context("UnSet_Color");

#ifdef DISABLE_UNSET
	_hoops_IRPPR ("UnSet");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Color ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IAPRA|_hoops_GSIIR)) != null) {
		if (target->type == _hoops_CIRIR) {
			_hoops_SIRIR * _hoops_ASIIR = (_hoops_SIRIR *)target;
			HI_Unset_Color(context, _hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR, _hoops_ASIIR->info._hoops_IPRI.offset, _hoops_ASIIR->_hoops_GCRIR);
		}
		else 
			HI_UnSet_Attribute (context, target, HK_COLOR);

		_hoops_IRRPR();
	}

#endif
}



#ifndef DISABLE_SHOW

// _hoops_HSRS _hoops_RH _hoops_RSIRR _hoops_IHIA _hoops_CCA _hoops_IRS *_hoops_RSRA* _hoops_IGRH
local char *_hoops_SPPRA (
	Color_Object type) {

	switch (type) {
		case Color_FRONT:				return (char *)"front";
		case Color_BACK:				return (char *)"back";
		case Color_EDGE:				return (char *)"edge";
		case Color_LINE:				return (char *)"line";
		case Color_VERTEX:				return (char *)"vertex";
		case Color_MARKER:				return (char *)"marker only";
		case Color_TEXT:				return (char *)"text";
		case Color_CUT_FACE:			return (char *)"cut face";
		case Color_CUT_EDGE:			return (char *)"cut edge";
		case Color_WINDOW:				return (char *)"window";
		case _hoops_SGARA:   return (char *)"simple reflection";
		case _hoops_RRARA:		return (char *)"front contrast";
		case _hoops_GRARA:		return (char *)"back contrast";
		case Color_EDGE_CONTRAST:		return (char *)"edge contrast";
		case Color_LINE_CONTRAST:		return (char *)"line contrast";
		case Color_VERTEX_CONTRAST:		return (char *)"vertex contrast";
		case Color_MARKER_CONTRAST:		return (char *)"marker contrast";
		case Color_TEXT_CONTRAST:		return (char *)"text contrast";
		case _hoops_HGARA:	return (char *)"cut face contrast";
		case _hoops_PGARA:	return (char *)"cut edge contrast";
		case Color_WINDOW_CONTRAST:		return (char *)"window contrast";
		case Color_LIGHTING:			return (char *)"lighting";
		case _hoops_PRARA:			return (char *)"ambient up";
		case _hoops_HRARA:		return (char *)"ambient down";

		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Can't choose color name");
			return (char *)"oops";
		}
	}
}


local char *_hoops_GHPRA (
	char			*_hoops_RHPRA,
	char			*_hoops_PSAPR,
	Color_Object _hoops_GHA,
	char const		*_hoops_AHPRA) {
	char			*_hoops_ASAPR = _hoops_RHPRA;
	Color_Object next;

	/* _hoops_HPCAR _hoops_SGS _hoops_RH _hoops_IIPR _hoops_SRHR _hoops_SSCP _hoops_RAPR _hoops_RSIAR -- _hoops_GA'_hoops_RA _hoops_ISPR _hoops_PHPRA */

	if (ALLBITS (_hoops_GHA, Color_EVERYTHING)) {
		return	HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"everything");
	}

	// _hoops_SRS _hoops_HPPP _hoops_GII _hoops_GSIPR-_hoops_IGRH _hoops_HHPRA
	if (ALLBITS (_hoops_GHA, Color_GEOMETRY)) {
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"geometry");
		_hoops_GHA &= ~Color_GEOMETRY;
	}
	if (ALLBITS (_hoops_GHA, Color_POLYGON)) {
		if (_hoops_ASAPR != _hoops_RHPRA) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)_hoops_AHPRA);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"polygon");
		_hoops_GHA &= ~Color_POLYGON;
	}
	if (ALLBITS (_hoops_GHA, Color_FACE)) {
		if (_hoops_ASAPR != _hoops_RHPRA) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)_hoops_AHPRA);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"face");
		_hoops_GHA &= ~Color_FACE;
	}
	if (ALLBITS (_hoops_GHA, Color_MARKER|Color_VERTEX)) {
		if (_hoops_ASAPR != _hoops_RHPRA) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)_hoops_AHPRA);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"marker");
		_hoops_GHA &= ~(Color_MARKER|Color_VERTEX);
	}
	if (ALLBITS (_hoops_GHA, Color_FACE_CONTRAST)) {
		if (_hoops_ASAPR != _hoops_RHPRA) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)_hoops_AHPRA);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"face contrast");
		_hoops_GHA &= ~Color_FACE_CONTRAST;
	}
	if (ALLBITS (_hoops_GHA, Color_CUT_GEOMETRY)) {
		if (_hoops_ASAPR != _hoops_RHPRA) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)_hoops_AHPRA);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"cut geometry");
		_hoops_GHA &= ~Color_CUT_GEOMETRY;
	}
	if (ALLBITS (_hoops_GHA, _hoops_IGARA)) {
		if (_hoops_ASAPR != _hoops_RHPRA) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)_hoops_AHPRA);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"cut geometry contrast");
		_hoops_GHA &= ~_hoops_IGARA;
	}
	if (ALLBITS (_hoops_GHA, _hoops_IRARA)) {
		if (_hoops_ASAPR != _hoops_RHPRA) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)_hoops_AHPRA);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)"ambient");
		_hoops_GHA &= ~_hoops_IRARA;
	}

	while (_hoops_GHA != Color_NONE) {
		if (_hoops_ASAPR != _hoops_RHPRA) _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)_hoops_AHPRA);
		next = _hoops_RIII (_hoops_GHA);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)_hoops_SPPRA (next));
		_hoops_GHA &= ~next;
	}

	return _hoops_ASAPR;
}


local void _hoops_IHPRA (
	Color_Object			_hoops_GHA,
	_hoops_CRCP				*_hoops_SRCP) {
	char					buf[128];
	char					*_hoops_RPPA;

	_hoops_RPPA = _hoops_GHPRA (buf, buf+_hoops_GGAPR(buf), _hoops_GHA, ",");
	*_hoops_RPPA = '\0';
	HE_ERROR (HEC_COLOR, HES_COLOR_WAS_SET_BY_INDEX,
			  Sprintf_SP (null, "%s color in '%p' was set \"by index\"",
						  buf, _hoops_SRCP));
}


local void _hoops_CHPRA (
	Color_Object			_hoops_GHA,
	_hoops_CRCP						*_hoops_SRCP) {
	char					buf[128];
	char					*_hoops_RPPA;

	_hoops_RPPA = _hoops_GHPRA (buf, buf+_hoops_GGAPR(buf), _hoops_GHA, ",");
	*_hoops_RPPA = '\0';
	HE_ERROR (HEC_COLOR, HES_COLOR_WAS_NOT_SET_BY_INDEX,
			  Sprintf_SP (null, "%s color in '%p' was not set \"by index\"",
						  buf, _hoops_SRCP));
}

#endif

#ifdef DISABLE_SHOW
#	ifdef DISABLE_METAFILE
#		define	_hoops_SHPRA
#	endif
#endif


GLOBAL_FUNCTION char * HI_Show_Material (
	char alter *				_hoops_ASAPR,
	char const *				_hoops_PSAPR,
	Named_Material const *		_hoops_ISHIR,
	Option_Value const *		option,
	bool						_hoops_GIPRA) {
#ifndef _hoops_SHPRA
	_hoops_ARGRA			_hoops_PRGRA = _hoops_ISHIR->_hoops_PRGRA;
	const char *				_hoops_RIPRA[] = {
		"specular=", "mirror=", "transmission=", "emission="};
	int							i;
	_hoops_ARGRA			mask, _hoops_AIPRA;
	bool						_hoops_PIPRA;

	if (_hoops_PRGRA == 0) {
		*_hoops_ASAPR++ = '*';
		return _hoops_ASAPR;
	}

	for (i=0; i<_hoops_CRGRA; i++) {
		if (BIT(_hoops_PRGRA, HOOPS_READ_ONLY._hoops_APGRA[i])) {
			if (_hoops_ISHIR->texture[i] == null ||
				BIT(_hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i])) {

				_hoops_PRGRA &= ~HOOPS_READ_ONLY._hoops_APGRA[i];
			}
		}
	}

	_hoops_PRGRA &= ~_hoops_CHGRA;
	_hoops_GIPRA = _hoops_GIPRA && (option == null) && (_hoops_RIII (_hoops_PRGRA) != _hoops_PRGRA);

	if (_hoops_GIPRA) {
		*_hoops_ASAPR++ = '(';
		if (_hoops_ASAPR == _hoops_PSAPR)
			return null;
	}

	/* _hoops_GRAS _hoops_RH _hoops_HIPRA _hoops_IIGR _hoops_PCPA _hoops_HRGR _hoops_HGRC _hoops_CCA _hoops_PCPA _hoops_HRGR _hoops_GPRI */
	if (option == null)
		_hoops_AIPRA = ~0; /* _hoops_CRGH _hoops_CPS _hoops_HHPA */
	else
		_hoops_AIPRA = option->type->id;
	mask = (_hoops_AIPRA & _hoops_ISHIR->_hoops_PRGRA);

	/* _hoops_RGHH _hoops_RH _hoops_SPI _hoops_GRIP */
	if (ANYBIT (mask, M_DIFFUSE|_hoops_RHGRA)) {
		_hoops_HIR const *_hoops_PGC = _hoops_ISHIR->_hoops_SCA;
		Material_Channel_Flags _hoops_IIPRA; /* _hoops_ICHHR _hoops_IHGC _hoops_IIGR _hoops_RH _hoops_CGHI _hoops_SPI _hoops_GRIP' _hoops_SGI */
		bool _hoops_CIPRA = (
			ALLBITS (mask, M_DIFFUSE|_hoops_RHGRA) &&
			!BIT (_hoops_ISHIR->_hoops_HRGRA, M_DIFFUSE)
		);
		bool _hoops_SIPRA = false;

		/* _hoops_IIPR _hoops_RCAP _hoops_RPPCR (_hoops_IAS._hoops_ISHI. "_hoops_SPI=" _hoops_PAR "_hoops_SPI _hoops_HH=") _hoops_RPP
		   _hoops_IRS) _hoops_IIH _hoops_CHR _hoops_GII _hoops_GRAA-_hoops_SPI _hoops_GRIP
		   _hoops_RCSR) _hoops_SR _hoops_HS _hoops_GPGR _hoops_SPI _hoops_GRIP _hoops_SGS _hoops_RRP _hoops_IS _hoops_SHH _hoops_GCPRA _hoops_GIAH
		   _hoops_GSGGR) _hoops_RH _hoops_AIRC _hoops_GPRI _hoops_CHR _hoops_IHIC _hoops_HSAR _hoops_PCPA _hoops_CSAP _hoops_HGRC, _hoops_PPR _hoops_SSIA _hoops_AAPR _hoops_HAR _hoops_RGIRR _hoops_SCSI */
		if (ANYBIT(mask, ~(M_DIFFUSE|_hoops_RHGRA)) ||
			(_hoops_CIPRA && ALLBITS (mask, M_DIFFUSE|_hoops_RHGRA)))
			_hoops_SIPRA = true; /* _hoops_AGIR _hoops_IRS,_hoops_RCSR */
		else if (!BIT (_hoops_ISHIR->_hoops_HRGRA, M_DIFFUSE) &&
			((_hoops_AIPRA & (M_DIFFUSE|_hoops_RHGRA) & (~_hoops_ISHIR->_hoops_PRGRA)) != 0))
			_hoops_SIPRA = true; /* _hoops_AGIR _hoops_GSGGR */

		if (_hoops_CIPRA || !_hoops_PGC || !BIT(mask,_hoops_RHGRA)) {
			if (_hoops_SIPRA) {
				if (_hoops_CIPRA)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "diffuse color=", null);
				else
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "diffuse=", null);
			}

			if (_hoops_ISHIR->_hoops_IRGRA.length != 0)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", (void *)&_hoops_ISHIR->_hoops_IRGRA);
			else {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "R=%f ", (void *)&_hoops_ISHIR->_hoops_CSHR.red);
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "G=%f ", (void *)&_hoops_ISHIR->_hoops_CSHR.green);
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "B=%f", (void *)&_hoops_ISHIR->_hoops_CSHR.blue);
			}
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",", null);
		}

		i = 0;
		if (_hoops_PGC && BIT (mask, _hoops_RHGRA)) {
			if (BIT (_hoops_ISHIR->_hoops_HRGRA, M_DIFFUSE)) {
				if (_hoops_SIPRA)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "diffuse=", null);
				if (_hoops_PGC->next || BIT (_hoops_PGC->flags, _hoops_CCARA))
					_hoops_PIPRA = true;
				else
					_hoops_PIPRA = false;

				if (_hoops_PIPRA)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "(", null);

				do {
					/* _hoops_GSRGR _hoops_RCPRA _hoops_CAS _hoops_IRPR */
					if (i < _hoops_PGC->_hoops_HGA) {
						do {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "*,", null);
							i++;
						} while (i < _hoops_PGC->_hoops_HGA);
					}

					if (BIT (_hoops_PGC->flags, _hoops_PRA)) {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "R=%f ", (void *)&_hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.red);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "G=%f ", (void *)&_hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.green);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "B=%f ", (void *)&_hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.blue);
					}
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", (void *)&_hoops_PGC->texture->name);
					if (_hoops_PGC->next)
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",", null);
					_hoops_IIPRA = _hoops_PGC->flags;
					i++;
				} while ((_hoops_PGC = _hoops_PGC->next) != null);
				if (BIT (_hoops_IIPRA, _hoops_CCARA) && !BIT(_hoops_IIPRA, _hoops_SGGRA))
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",*", null);
				if (_hoops_PIPRA)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ")", null);
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",", null);
			}
			else if (BIT (mask, _hoops_RHGRA)) {
				if (_hoops_SIPRA)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "diffuse texture=", null);
				_hoops_PIPRA = false;
				if (_hoops_ISHIR->_hoops_SCA)
					_hoops_PIPRA = true;
				if (_hoops_PIPRA)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "(", null);
				do {
					/* _hoops_GSRGR _hoops_RCPRA _hoops_CAS _hoops_IRPR */
					if (i < _hoops_PGC->_hoops_HGA) {
						do {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "*,", null);
							i++;
						} while (i < _hoops_PGC->_hoops_HGA);
					}
					if (BIT (_hoops_PGC->flags, _hoops_PRA)) {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "R=%f ", (void *)&_hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.red);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "G=%f ", (void *)&_hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.green);
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "B=%f ", (void *)&_hoops_PGC->texture->_hoops_HPIR._hoops_IPIR.blue);
					}
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", (void *)&_hoops_PGC->texture->name);
					if (_hoops_PGC->next)
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",", null);
					_hoops_IIPRA = _hoops_PGC->flags;
					i++;
				} while ((_hoops_PGC = _hoops_PGC->next) != null);
				if (BIT (_hoops_IIPRA, _hoops_CCARA) && !BIT(_hoops_IIPRA, _hoops_SGGRA))
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",*", null);
				if (_hoops_PIPRA)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ")", null);
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ",", null);
			}
		}
	}

	/* _hoops_HA _hoops_RGHH _hoops_RH _hoops_ACSP (_hoops_GRAA-_hoops_SPI) _hoops_IIGR _hoops_RH _hoops_GRIP */
	for (i=0; i<_hoops_CRGRA; i++) {
		if (BIT (mask, HOOPS_READ_ONLY._hoops_SRGRA[i]) ||
			(BIT (mask, HOOPS_READ_ONLY._hoops_APGRA[i]) &&
				_hoops_ISHIR->texture[i] != null)) {
			if (option == null)
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, _hoops_RIPRA[i], null);
			if (!BIT(_hoops_PRGRA, HOOPS_READ_ONLY._hoops_APGRA[i])) {
				if (_hoops_ISHIR->name[i].length != 0)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%n,", (void *)&_hoops_ISHIR->name[i]);
				else {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "R=%f ", (void *)&_hoops_ISHIR->color[i].red);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "G=%f ", (void *)&_hoops_ISHIR->color[i].green);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "B=%f,", (void *)&_hoops_ISHIR->color[i].blue);
				}
			}
			else {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%n,", (void *)&_hoops_ISHIR->texture[i]->name);
			}
			if (_hoops_ASAPR == null)
				return null;
		}
	}
	if (BIT (mask, _hoops_GCARA)) {
		if (option == null)
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "environment=", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn,", (void *)&_hoops_ISHIR->texture[_hoops_RIA]->name);
		if (_hoops_ASAPR == null)
			return null;
	}
	if (BIT (mask, _hoops_SIARA)) {
		if (option == null)
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "bump=", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn,", (void *)&_hoops_ISHIR->texture[_hoops_IIA]->name);
		if (_hoops_ASAPR == null)
			return null;
	}
	if (BIT (mask, _hoops_RAGRA)) {
		if (option == null)
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "gloss=", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", (void *)&_hoops_ISHIR->gloss);
	}

	if (BIT (mask, _hoops_AAGRA)) {
		if (option == null)
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "index=", null);
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%f,", (void *)&_hoops_ISHIR->_hoops_PAGRA);
	}

	if (_hoops_ASAPR != null) {
		--_hoops_ASAPR;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */
		if (_hoops_GIPRA)
			*_hoops_ASAPR++ = ')';
	}

	return _hoops_ASAPR;
#else
	return null;
#endif
}


GLOBAL_FUNCTION void HI_Show_Color (
	_hoops_SSGI *			color,
	char *			_hoops_ACPRA,
	int				_hoops_PCPRA)
{
	char *			cname = _hoops_ACPRA;
	_hoops_ACSGA *	list;

	list = color->colors;
	do {
		int				length;
		char			buf[4096];
		char *			_hoops_ASAPR = buf;
		char *			_hoops_PSAPR = buf+_hoops_GGAPR(buf);

		if (cname > _hoops_ACPRA)
			*_hoops_ASAPR++ = ',';

		_hoops_ASAPR = _hoops_GHPRA (_hoops_ASAPR, _hoops_PSAPR, list->_hoops_GHA, "=");
		*_hoops_ASAPR++ = '=';

		switch (list->type) {
			case _hoops_SHGRA: {
				_hoops_PCSGA const *	findex = (_hoops_PCSGA const *)list;

				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "#%f", (void *)&findex->value);
			}	break;

			case _hoops_PPCA: {
				_hoops_APCA const *	normal = (_hoops_APCA const *)list;

				if (normal->name.length > 0)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%n", (void *)&normal->name);
				else {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "R=%f ", (void *)&normal->rgb.red);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "G=%f ", (void *)&normal->rgb.green);
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "B=%f", (void *)&normal->rgb.blue);
				}
			}	break;

			case _hoops_GIGRA: {			// _hoops_RAPC _hoops_GGR _hoops_AGIR _hoops_SR _hoops_HHGC _hoops_IS _hoops_HCPRA _hoops_HGIHR
				_hoops_HCSGA alter *		_hoops_ICSGA = (_hoops_HCSGA alter *)list;

				if (_hoops_ICSGA->name.length > 0)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%n", (void *)&_hoops_ICSGA->name);
				else if (ANYBIT (list->_hoops_GHA, Color_FACE | Color_EDGE | Color_VERTEX |
												Color_CUT_FACE | Color_CUT_EDGE |
												Color_LINE | Color_MARKER | Color_TEXT))
					_hoops_ASAPR = HI_Show_Material (_hoops_ASAPR, _hoops_PSAPR, &_hoops_ICSGA->_hoops_ISHIR, null, true);
				else {
					/* _hoops_SPI _hoops_HRGR _hoops_RH _hoops_RGAR _hoops_ICPRA _hoops_PIRA _hoops_RPP _hoops_HAR
					 * _hoops_HSP/_hoops_ISHA/_hoops_GPIA
					 */
					_hoops_ARGRA	save = _hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA;
					if (!BIT (save, M_DIFFUSE))
						continue;
					_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA = M_DIFFUSE;	// _hoops_HAR _hoops_CPSA _hoops_ICIC
					_hoops_ASAPR = HI_Show_Material (_hoops_ASAPR, _hoops_PSAPR, &_hoops_ICSGA->_hoops_ISHIR, null, true);
					_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA = save;
				}
			}	break;
		}

		if (_hoops_ASAPR == null) {
			if (_hoops_PCPRA > 0)
				HE_ERROR (HEC_COLOR, HES_BUFFER_OVERFLOW, "Show color exceeded given output buffer size.");
			else
				HE_ERROR (HEC_INTERNAL_ERROR, HES_BUFFER_OVERFLOW, "Internal buffer overrun.");
			return;
		}

		length = (int)(_hoops_ASAPR - buf);
		HI_Return_Chars (cname, _hoops_PCPRA, buf, length);
		if (_hoops_PCPRA > 0)
			if ((_hoops_PCPRA -= length) < 0)
				return;
		cname += length;
	} while ((list = list->next) != null);
}

#ifndef DISABLE_SHOW


local void _hoops_CCPRA (
	_hoops_SSGI const *			color,
	char alter *			type,
	int						_hoops_SCPRA,
	char alter *			style,
	int						_hoops_GSPRA,
	float alter *			a,
	float alter *			b,
	float alter *			c) {
	_hoops_ACSGA const *		list;
	RGB const *				first;
	char					buf[300];
	char					*_hoops_ASAPR = buf,
							*_hoops_PSAPR = buf+_hoops_GGAPR(buf);
	char					buf1[128], buf2[128];

	list = color->colors;

	switch (list->type) {
		case _hoops_SHGRA: {
			_hoops_IHPRA (list->_hoops_GHA, color->owner);
			return;
		}	_hoops_HHHI;

		default:
		case _hoops_PPCA: {
			_hoops_APCA const *		normal = (_hoops_APCA const *)list;

			first = &normal->rgb;
		}	break;

		case _hoops_GIGRA: {
			_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

			first = &_hoops_ICSGA->_hoops_ISHIR._hoops_CSHR;
		}	break;
	}

	_hoops_ASAPR = _hoops_GHPRA (_hoops_ASAPR, _hoops_PSAPR, list->_hoops_GHA, ",");

/* _hoops_RSPRA: _hoops_HIISR _hoops_CCA _hoops_IGPC */

	while ((list = list->next) != null) {
		if (list->type == _hoops_SHGRA) {
			_hoops_IHPRA (list->_hoops_GHA, color->owner);
			return;
		}

		_hoops_APCA const *		normal = (_hoops_APCA const *)list;
		_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

		if (list->type == _hoops_PPCA && normal->rgb != *first ||
			list->type == _hoops_GIGRA && _hoops_ICSGA->_hoops_ISHIR._hoops_CSHR != *first) {
			char *			_hoops_RPPA;

			_hoops_RPPA = _hoops_GHPRA (buf1, buf1+_hoops_GGAPR(buf1),
							 list->_hoops_GHA, ",");
			*_hoops_RPPA = '\0';
			_hoops_RPPA = _hoops_GHPRA (buf2, buf2+_hoops_GGAPR(buf2),
							 color->colors->_hoops_GHA, ",");
			*_hoops_RPPA = '\0';
			HE_ERROR2 (HEC_COLOR, HES_COLOR_COMPONENTS_MISMATCH,
					   "Can't show the colors \"by value\" -",
					   Sprintf_SS (null,
						   "The value for %s differs from the value for %s",
						   buf1, buf2));
			return;
		}

		*_hoops_ASAPR++ = ',';
		_hoops_ASAPR = _hoops_GHPRA (_hoops_ASAPR, _hoops_PSAPR, list->_hoops_GHA, ",");
	}

	HI_Return_Chars (type, _hoops_SCPRA, buf, (int)(_hoops_ASAPR - buf));
	HI_Return_Chars (style, _hoops_GSPRA, "rgb", 3);

	*a = first->red;
	*b = first->green;
	*c = first->blue;
}


local void _hoops_ASPRA (
	_hoops_SSGI const *			color,
	char alter *			type,
	int						_hoops_SCPRA,
	int alter *				index) {
	_hoops_ACSGA const *		list;
	char					buf[300];
	char					*_hoops_ASAPR = buf,
							*_hoops_PSAPR = buf+_hoops_GGAPR(buf);
	char					buf1[128], buf2[128];

	list = color->colors;
	if (list->type != _hoops_SHGRA) {
		_hoops_CHPRA (list->_hoops_GHA, color->owner);
		return;
	}

	_hoops_ASAPR = _hoops_GHPRA (_hoops_ASAPR, _hoops_PSAPR, list->_hoops_GHA, ",");

	/* _hoops_GPGP _hoops_HAGIR, _hoops_RPP (_hoops_HIGR->_hoops_SPS != _hoops_IRAP) _hoops_SR _hoops_PIHA _hoops_HS _hoops_PSPRA _hoops_HSPRA _hoops_PAR
	** _hoops_PSPI, _hoops_PPR _hoops_HIS _hoops_GRS _hoops_SHR _hoops_CAHP _hoops_HHH _hoops_GHIS _hoops_IIGR _hoops_RIHH.	 _hoops_HSRR _hoops_HA,
	** _hoops_SGH _hoops_PCCP _hoops_HHHA _hoops_HAPR _hoops_IS _hoops_ISPR _hoops_HCR _hoops_AIRP (_hoops_SCH _hoops_CGH _hoops_RIHH & _hoops_ASRC
	** _hoops_RH _hoops_SRS _hoops_GHIR _hoops_RHIR).
	*/

	_hoops_PCSGA const *	first = (_hoops_PCSGA const *)list;

	while ((list = list->next) != null) {
		if (list->type != _hoops_SHGRA) {
			_hoops_CHPRA (list->_hoops_GHA, color->owner);
			return;
		}

		_hoops_PCSGA const *	findex = (_hoops_PCSGA const *)list;

		if (findex->value != first->value) {
			char			*_hoops_RPPA;

			_hoops_RPPA = _hoops_GHPRA (buf1, buf1+_hoops_GGAPR(buf1), list->_hoops_GHA, ",");
			*_hoops_RPPA = '\0';
			_hoops_RPPA = _hoops_GHPRA (buf2, buf2+_hoops_GGAPR(buf2), first->_hoops_GHA, ",");
			*_hoops_RPPA = '\0';
			HE_ERROR2 (HEC_COLOR, HES_COLOR_COMPONENTS_MISMATCH,
					   "Can't show the colors \"by index\" -",
					   Sprintf_SS (null, "The index for %s differs from the value for %s",buf1, buf2));
			return;
		}

		*_hoops_ASAPR++ = ',';
		_hoops_ASAPR = _hoops_GHPRA (_hoops_ASAPR, _hoops_PSAPR, list->_hoops_GHA, ",");
	}

	HI_Return_Chars (type, _hoops_SCPRA, buf, (int)(_hoops_ASAPR - buf));

	*index = (int)(first->value + 0.5f); /* _hoops_GIRR _hoops_SCH _hoops_PSAP */
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_Color (
	char *			cname)
{
	_hoops_PAPPR context("Show_Color");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Color () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ISPRA)) != null) {

		_hoops_SSGI *	color;
		if ((color = (_hoops_SSGI *)HI_Find_Attribute (context, target, HK_COLOR)) != null) {
			HI_Show_Color (color, cname, -1);
			_hoops_HPRH (color);
		}
		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Color_By_Index (
	char *			type,
	int *			index)
{
	_hoops_PAPPR context("Show_Color_By_Index");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Color_By_Index () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ISPRA)) != null) {

		_hoops_SSGI *		color;
		if ((color = (_hoops_SSGI *)HI_Find_Attribute (context, target, HK_COLOR)) != null) {
			_hoops_ASPRA (color, type, -1, index);
			_hoops_HPRH (color);
		}
		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Color_By_Value (
	char *			type,
	char *			style,
	float *			a,
	float *			b,
	float *			c)
{
	_hoops_PAPPR context("Show_Color_By_Value");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Color_By_Value () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ISPRA)) != null) {

		_hoops_SSGI *		color;
		if ((color = (_hoops_SSGI *)HI_Find_Attribute (context, target, HK_COLOR)) != null) {
			_hoops_CCPRA (color, type, -1, style, -1, a, b, c);
			_hoops_HPRH (color);
		}
		_hoops_IRRPR();
	}
#endif
}



#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Color (
	int				count,
	Key const *		keys,
	char *			cname)
{
	_hoops_PAPPR context("PShow_Net_Color");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Color () */\n");
	);

	_hoops_SSGI *		color;
	if ((color = (_hoops_SSGI *) HI_Find_Attribute_And_Lock(context, _hoops_ISPRA, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Color (color, cname, -1);
		_hoops_HPRH (color);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(cname, -1, "", 0);
#endif
}


#endif



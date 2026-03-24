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
 * $Id: obf_tmp.txt 1.144 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"


struct _hoops_AAAPI {
	_hoops_CRCP *			newowner;
	Subsegment **		_hoops_ASRGR;
	Key					_hoops_ACHPA;
	_hoops_CCPCA			condition;
};



GLOBAL_FUNCTION bool HI_Would_Be_Include_Loop (
	_hoops_CRCP *			owner,
	_hoops_CRCP *			_hoops_HCPIH) {

	do {
		Xref *			_hoops_AHICA;

		if (owner == _hoops_HCPIH)
			return true;

		if ((_hoops_AHICA = owner->_hoops_SGRPR()) != null) {
			do if (_hoops_AHICA->type == _hoops_AGRPR && !BIT (_hoops_AHICA->owner->_hoops_RRHH, _hoops_HIRIR)) {
				if (HI_Would_Be_Include_Loop (_hoops_AHICA->owner, _hoops_HCPIH))
					return true;
			} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
		}
		owner = owner->owner;
	} while (owner->type != _hoops_PRAIR);

	return false;
}



local void _hoops_PAAPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				ref,
	void *					info) 
{
	_hoops_PGRPR *				include;
	_hoops_AAAPI *		pt = (_hoops_AAAPI *)info;
	_hoops_CRCP *				_hoops_SRCP;
	_hoops_ACHR				_hoops_HAAPI;

	_hoops_SRCP = pt->newowner;

	/* _hoops_SSCP _hoops_SCH _hoops_AIAH _hoops_RPII _hoops_PGPAA? */
	if (ref->_hoops_HIHI < 20) {						/* _hoops_ISPR _hoops_ICHRR _hoops_HSIGP _hoops_HIGR! */
		Xref *			_hoops_AHICA;

		if ((_hoops_AHICA = ref->_hoops_SGRPR()) != null)
		do if (_hoops_AHICA->owner == _hoops_SRCP &&
			   _hoops_AHICA->type == _hoops_AGRPR &&
			   ((_hoops_PGRPR *)_hoops_AHICA)->condition.count == pt->condition.count &&
			   EQUAL_MEMORY (((_hoops_PGRPR *)_hoops_AHICA)->condition._hoops_ASACA, pt->condition.count*sizeof(int),
							  pt->condition._hoops_ASACA)) {
#if 0
			if (pt->condition.count == 0) {
				HE_WARNING (HEC_INCLUDE, HES_ALREADY_INCLUDED,
					Sprintf_PP (null, "Can't include '%p' in '%p' - already is",ref, _hoops_SRCP));
			}
			else {
				char			buffer[512];
				char			condition[256];

				HI_Show_Conditional (&pt->condition, condition, -1);
				Sprintf_S (buffer, "with condition '%s' - already is", condition);
				_hoops_PHPGR (HEC_INCLUDE, HES_ALREADY_INCLUDED, 
					Sprintf_PP (null, "Can't include '%p' in '%p'", ref, _hoops_SRCP), buffer);
			}
#endif

			pt->_hoops_ACHPA = (pt->_hoops_ACHPA == 0) ? _hoops_AHICA->key : -1;
			return;
		} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);
	}
	else {									/* _hoops_AA _hoops_SCH _hoops_RH _hoops_ACIPR _hoops_PPRRR */
		if ((include = (_hoops_PGRPR *)*pt->_hoops_ASRGR) != null)
		do {
			if (include->type != _hoops_AGRPR) {
				if (BIT (include->owner->_hoops_PHSI, _hoops_GGPSA))
					continue;	/* _hoops_ARARH, _hoops_GAAP _hoops_CRRPR _hoops_RAS _hoops_CHAPA, _hoops_GRHP _hoops_HCHAR */
				else
					break;
			}

			_hoops_CRCP const *		_hoops_SIRPH = include->_hoops_IGRPR;

			if (_hoops_SIRPH == ref &&
				include->condition.count == pt->condition.count &&
				EQUAL_MEMORY (include->condition._hoops_ASACA, pt->condition.count*sizeof(int),
							  pt->condition._hoops_ASACA)) {
#if 0
				if (pt->condition.count == 0)
					HE_WARNING (HEC_INCLUDE, HES_ALREADY_INCLUDED,
								Sprintf_PP (null, "Can't include '%p' in '%p' - already is", ref, _hoops_SRCP));
				else {
					char		buffer[512];
					char		condition[256];

					HI_Show_Conditional (&pt->condition, condition, -1);
					Sprintf_S (buffer, "with condition '%s' - already is", condition);
					_hoops_PHPGR (HEC_INCLUDE, HES_ALREADY_INCLUDED,
								Sprintf_PP (null, "Can't include '%p' in '%p'", ref, _hoops_SRCP), buffer);
				}
#endif

				pt->_hoops_ACHPA = (pt->_hoops_ACHPA == 0) ? include->key : -1;
				return;
			}
		} while ((include = (_hoops_PGRPR *)include->next) != null);
	}

	if (HI_Would_Be_Include_Loop (_hoops_SRCP, ref)) {
		HE_ERROR2 (HEC_INCLUDE, HES_INFINITE_LOOP,
					Sprintf_PP (null, "Can't include '%p' into '%p' -", ref, _hoops_SRCP),
				   "An infinite loop of subsegments would be created");
		return;
	}

	ZALLOC (include, _hoops_PGRPR);
	include->_hoops_RRHH = _hoops_HPAPA;
	include->type = _hoops_AGRPR;
	include->_hoops_HIHI = 1;
	include->owner = _hoops_SRCP;
	include->key = _hoops_AIRIR (include);

	include->priority = HOOPS_WORLD->_hoops_IPAPA++;

	/* _hoops_GHIS _hoops_HPP _hoops_RSIRR?? */

	if ((include->next = *pt->_hoops_ASRGR) != null)
		(*pt->_hoops_ASRGR)->backlink = &include->next;

	*pt->_hoops_ASRGR = (Subsegment *)include;
	include->backlink = pt->_hoops_ASRGR;

	include->_hoops_IGRPR = ref;
	_hoops_PRRH (ref);
	_hoops_SPAPA(_hoops_RIGC, include, ref);

	HI_Copy_Conditional (&pt->condition, &include->condition);


	_hoops_HAAPI = ref->_hoops_RCGC | _hoops_SPHGP;
	if (BIT (ref->_hoops_PHSI, _hoops_SHSIR)) 
		_hoops_HAAPI |= T_WINDOWS;

	/* _hoops_RPP _hoops_RH _hoops_PGPAA _hoops_CAGH _hoops_SSCP _hoops_IRS _hoops_SARA _hoops_SR _hoops_PIHA _hoops_IIS _hoops_RH _hoops_IAAPI _hoops_ACPA */
	if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_PSPCR) &&
		!BIT (_hoops_HAAPI, _hoops_PSPCR) &&
		BIT (ref->owner->_hoops_RCGC, _hoops_PSPCR)) {
		Attribute const		*_hoops_HPHCR;

		if ((_hoops_HPHCR = ref->_hoops_IPPGR) != null) do {
			if (_hoops_HPHCR->type >= HK_CAMERA) {
				if (_hoops_HPHCR->type == HK_CAMERA)
					_hoops_HAAPI |= _hoops_PSPCR;
				break;
			}
		} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
	}

	if (include->condition.count > 0)
		_hoops_HAAPI |= _hoops_CPHGP;

	_hoops_HAAPI &= ~_hoops_SRCP->_hoops_RCGC;
	if (_hoops_HAAPI != (_hoops_ACHR)0)
		HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_HAAPI);

	include->_hoops_CPGPR = _hoops_HCHPA;
	include->_hoops_SPGPR = 0;

	if (BIT (ref->_hoops_PHSI, _hoops_SHSIR)) {
		HI_Bring_To_Front (_hoops_RIGC, (_hoops_HPAH *)include);
	}

	pt->_hoops_ACHPA = (pt->_hoops_ACHPA == 0) ? include->key : -1;

	if (!ANYBIT (ref->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR)) {
		if (ref->_hoops_AAGSA() > 0)
			HI_More_Light (_hoops_RIGC, _hoops_SRCP, ref->_hoops_AAGSA());

		if (ref->_hoops_PAGSA() > 0)
			HI_More_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, ref->_hoops_PAGSA());

		if (ref->_hoops_SHGSA() > 0)
			HI_More_Shadows (_hoops_RIGC, _hoops_SRCP, ref->_hoops_SHGSA());

		if (!ANYBIT (ref->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA)) {
			if (ref->_hoops_IGCCA > 0)
				HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, ref->_hoops_IGCCA);
		}
	}

	if (ref->bounding != null)
		HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, ref->bounding, ref);
	else {
		Bounding	bounding;
		Bounding	_hoops_HSRIR;

		HI_Figure_Segment_Bounding (ref, bounding, _hoops_HSRIR);
		if (!bounding._hoops_HICAR())
			HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, bounding, ref);
	}

	if (BIT (ref->_hoops_RCGC, T_FACES))
		_hoops_SASIR (_hoops_RIGC, include, _hoops_GCGSA|
									 _hoops_CSCCA|
									 _hoops_PISSR|
									 _hoops_RPSIR|
									 _hoops_SSCCA);
	else if (ANYBIT (ref->_hoops_RCGC, _hoops_HAHGP) ||
			 BIT (ref->_hoops_PHSI, _hoops_SHSIR))
		_hoops_SASIR (_hoops_RIGC, include, _hoops_RCGSA|
									 _hoops_PISSR|
									 _hoops_RPSIR|
									 _hoops_SSCCA);
	else
		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_CCHPA);
}


local Key _hoops_CAAPI (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	char const *			condition) {
	Subsegment *			_hoops_GHHPH;
	_hoops_AAAPI		_hoops_HASAR;

	if ((_hoops_RIGC->open_list == null || _hoops_RIGC->open_list->_hoops_GCRIR != _hoops_RCRIR) &&
		!HI_Find_Our_Open (_hoops_RIGC))
		return 0;

	_hoops_HASAR.newowner = _hoops_RIGC->open_list->info.segment._hoops_IGRPR;
	_hoops_HASAR._hoops_ACHPA = 0;

	_hoops_HASAR.condition._hoops_ASACA = null;
	_hoops_HASAR.condition.count = 0;
	if (condition != null) {
		if (!HI_Parse_Condition (_hoops_RIGC, condition, &_hoops_HASAR.condition)) {
			HE_ERROR2 (HEC_INCLUDE, HES_CONDITIONAL, "Unable to process the conditional expression:", Sprintf_S (null, "'%s'", condition));
			return 0;
		}
	}

	if ((_hoops_GHHPH = _hoops_RIGC->open_list->info.segment._hoops_IGRPR->_hoops_RGRPR) == null) {
		_hoops_HASAR._hoops_ASRGR = &_hoops_RIGC->open_list->info.segment._hoops_IGRPR->_hoops_RGRPR;
	}
	else _hoops_PCCAR {
		if (_hoops_GHHPH->type >= _hoops_AGRPR ||
			BIT (_hoops_GHHPH->_hoops_RRHH, _hoops_PASIR)) {
			/* _hoops_ARPP _hoops_RGR _hoops_SPR */
			_hoops_HASAR._hoops_ASRGR = _hoops_GHHPH->backlink;
			break;
		}
		else if (_hoops_GHHPH->next == null) {
			/* _hoops_RAS _hoops_RGR _hoops_SPR */
			_hoops_HASAR._hoops_ASRGR = &_hoops_GHHPH->next;
			break;
		}
		_hoops_GHHPH = _hoops_GHHPH->next;
	}

	HI_For_Each (_hoops_RIGC, name, true, _hoops_PAAPI, (void *)&_hoops_HASAR);

	HI_Free_Conditional (&_hoops_HASAR.condition);
	return _hoops_HASAR._hoops_ACHPA;
}

local Key _hoops_SAAPI (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	char const *			condition,
	_hoops_CRCP *				_hoops_SRCP) {
	Subsegment *			_hoops_GHHPH;
	_hoops_CRCP *				ref = (_hoops_CRCP *)_hoops_RCSSR (_hoops_RIGC, key);
	_hoops_AAAPI		_hoops_HASAR;

	if (ref == null || ref->type != _hoops_IRCP || BIT(ref->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_INCLUDE, HES_INVALID_KEY, "Provided key does not refer to a valid segment");
		return _hoops_SHSSR;
	}

	if (_hoops_SRCP == null) {
		if ((_hoops_RIGC->open_list == null || _hoops_RIGC->open_list->_hoops_GCRIR != _hoops_RCRIR) &&
			!HI_Find_Our_Open (_hoops_RIGC))
			return 0;
		_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_IGRPR;
	}

	_hoops_HASAR.newowner = _hoops_SRCP;
	_hoops_HASAR._hoops_ACHPA = 0;

	_hoops_HASAR.condition._hoops_ASACA = null;
	_hoops_HASAR.condition.count = 0;
	if (condition != null) {
		if (!HI_Parse_Condition (_hoops_RIGC, condition, &_hoops_HASAR.condition)) {
			HE_ERROR2 (HEC_INCLUDE, HES_CONDITIONAL, "Unable to process the conditional expression:",Sprintf_S (null, "'%s'", condition));
			return 0;
		}
	}

	if ((_hoops_GHHPH = _hoops_SRCP->_hoops_RGRPR) == null) {
		_hoops_HASAR._hoops_ASRGR = &_hoops_SRCP->_hoops_RGRPR;
	}
	else _hoops_PCCAR {
		if (_hoops_GHHPH->type >= _hoops_AGRPR ||
			BIT (_hoops_GHHPH->_hoops_RRHH, _hoops_PASIR)) {
			/* _hoops_ARPP _hoops_RGR _hoops_SPR */
			_hoops_HASAR._hoops_ASRGR = _hoops_GHHPH->backlink;
			break;
		}
		else if (_hoops_GHHPH->next == null) {
			/* _hoops_RAS _hoops_RGR _hoops_SPR */
			_hoops_HASAR._hoops_ASRGR = &_hoops_GHHPH->next;
			break;
		}
		_hoops_GHHPH = _hoops_GHHPH->next;
	}

	_hoops_PAAPI (_hoops_RIGC, ref, (void *)&_hoops_HASAR);

	HI_Free_Conditional (&_hoops_HASAR.condition);
	return _hoops_HASAR._hoops_ACHPA;
}

GLOBAL_FUNCTION _hoops_PGRPR * HI_Create_Include (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				ref,
	_hoops_CRCP *				newowner,
	_hoops_CCPCA *			condition) {
	_hoops_AAAPI		_hoops_HASAR;
	Subsegment *			_hoops_GHHPH;

	_hoops_HASAR.newowner = newowner;
	_hoops_HASAR._hoops_ACHPA = 0;

	if (condition != null) {
		_hoops_HASAR.condition._hoops_ASACA = null;
		_hoops_HASAR.condition.count = 0;
	}
	else {
		_hoops_HASAR.condition._hoops_ASACA = condition->_hoops_ASACA;
		_hoops_HASAR.condition.count = condition->count;
	}

	if ((_hoops_GHHPH = newowner->_hoops_RGRPR) == null) {
		_hoops_HASAR._hoops_ASRGR = &newowner->_hoops_RGRPR;
	}
	else _hoops_PCCAR {
		if (_hoops_GHHPH->type >= _hoops_AGRPR ||
			BIT (_hoops_GHHPH->_hoops_RRHH, _hoops_PASIR)) {
			/* _hoops_ARPP _hoops_RGR _hoops_SPR */
			_hoops_HASAR._hoops_ASRGR = _hoops_GHHPH->backlink;
			break;
		}
		else if (_hoops_GHHPH->next == null) {
			/* _hoops_RAS _hoops_RGR _hoops_SPR */
			_hoops_HASAR._hoops_ASRGR = &_hoops_GHHPH->next;
			break;
		}
		_hoops_GHHPH = _hoops_GHHPH->next;
	}

	_hoops_PAAPI (_hoops_RIGC, ref, (void *)&_hoops_HASAR);

	if (_hoops_HASAR._hoops_ACHPA == 0)	/* _hoops_RIHH _hoops_GSPCA */
		return null;

	return (_hoops_PGRPR *)*_hoops_HASAR._hoops_ASRGR;
}


HC_INTERFACE Key HC_CDECL HC_Include_Segment (
	char const *			name)
{
	_hoops_PAPPR context("Include_Segment");

	_hoops_RPPPR();
	Key	key = _hoops_CAAPI (context, name, null);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "DEFINE (HC_Include_Segment (%S), ", name));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", key));
	);

	if (key == -1) {
		HE_WARNING(HEC_INCLUDE, HES_BAD_RETURN_KEY, "Can't return the key - more than one segment was included");
		return _hoops_SHSSR;
	}
	if (key == 0)		/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return key;
}


HC_INTERFACE Key HC_CDECL HC_Include_Segment_By_Key (
	Key						key)
{
	_hoops_PAPPR context("Include_Segment_By_Key");

	_hoops_RPPPR();
	Key	_hoops_ACHPA = _hoops_SAAPI (context, key, null, null);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Include_Segment_By_Key (LOOKUP (%D)), ", key));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	if (_hoops_ACHPA == 0)	/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return _hoops_ACHPA;
}

HC_INTERFACE Key HC_CDECL HC_Include_Segment_Key_By_Key (
	Key						key,
	Key						includer_key)
{
	_hoops_PAPPR context("Include_Segment_Key_By_Key");

	Key _hoops_ACHPA = 0;
	_hoops_RPPPR();

	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (context, includer_key);

	if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP || BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR))
		HE_ERROR (HEC_GLYPH, HES_INVALID_KEY, "Provided key does not refer to a valid segment");
	else
		_hoops_ACHPA = _hoops_SAAPI (context, key, null, _hoops_SRCP);

	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Include_Segment_Key_By_Key (LOOKUP (%D)), ", key));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D)), ", includer_key));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	if (_hoops_ACHPA == 0)	/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return _hoops_SHSSR;

	return _hoops_ACHPA;
}


HC_INTERFACE Key HC_CDECL HC_Conditional_Include (
	char const *			name,
	char const *			condition)
{
	_hoops_PAPPR context("Conditional_Include");

	_hoops_RPPPR();
	Key	key = _hoops_CAAPI (context, name, condition);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "DEFINE (HC_Conditional_Include (%S, %S), ", name, condition));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", key));
	);

	if (key == -1) {
		HE_WARNING(HEC_INCLUDE, HES_BAD_RETURN_KEY, "Can't return the key - more than one segment was included");
		return _hoops_SHSSR;
	}
	if (key == 0)		/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return key;
}


HC_INTERFACE Key HC_CDECL HC_Conditional_Include_By_Key (
	Key						key,
	char const *			condition)
{
	_hoops_PAPPR context("Conditional_Include_By_Key");

	_hoops_RPPPR();
	Key	_hoops_ACHPA = _hoops_SAAPI (context, key, condition, null);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Conditional_Include_By_Key (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_S	 (null, "%S), ", condition));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	if (_hoops_ACHPA == 0)	/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return _hoops_ACHPA;
}

HC_INTERFACE Key HC_CDECL HC_Conditional_Include_Key_By_Ke (
	Key						key,
	char const *			condition,
	Key						includer_key)
{
	_hoops_PAPPR context("Conditional_Include_By_Key");

	_hoops_RPPPR();

	Key			_hoops_ACHPA = _hoops_SHSSR;
	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (context, includer_key);

	if (_hoops_SRCP == null || _hoops_SRCP->type != _hoops_IRCP || BIT(_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GLYPH, HES_INVALID_KEY,"Provided key does not refer to a valid segment");
	}
	else
		_hoops_ACHPA = _hoops_SAAPI (context, key, condition, null);

	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Conditional_Include_Key_By_Key (LOOKUP (%D)), ", key));
		HI_Dump_Code (Sprintf_S	 (null, "%S, ", condition));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D)), ", includer_key));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	if (_hoops_ACHPA == 0)	/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return _hoops_ACHPA;
}

local bool _hoops_GPAPI (
	_hoops_CRCP const *			_hoops_SHGCR,
	_hoops_SIHIR const *		test) {		/* _hoops_GHCA _hoops_SHH _hoops_CPAP */

	if (BIT (test->_hoops_RRHH, _hoops_HGAGR))
		return false;

	if (test->type == _hoops_IRCP) {
		_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)test;
		Geometry const *	geometry;

		if (_hoops_SRCP == _hoops_SHGCR)
			return true;

		if ((geometry = _hoops_SRCP->geometry) != null) do {
			if (geometry->type == _hoops_AHIP) {
				_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)geometry;

				if (_hoops_GPAPI (_hoops_SHGCR, (_hoops_SIHIR const *)_hoops_RRA->_hoops_IHIP[0]))
					return true;
			}
		} while ((geometry = geometry->next) != null);
	}
	else if (test->type == _hoops_AHIP) {
		_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)test;

		return _hoops_GPAPI (_hoops_SHGCR, (_hoops_SIHIR const *)_hoops_RRA->_hoops_IHIP[0]);
	}

	return false;
}

local void _hoops_RAGSA (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_CRCP alter *				_hoops_SRCP,
	Geometry const *			geom,
	int							_hoops_RGPGR = ~0) {

	switch (geom->type) {
		case _hoops_ICIP: {
			if (BIT (_hoops_RGPGR, _hoops_AGPGR (_hoops_ICIP)))
				HI_More_Light (_hoops_RIGC, _hoops_SRCP, 1);
		}	break;

		case _hoops_HGPGR: {
			if (BIT (_hoops_RGPGR, _hoops_AGPGR (_hoops_HGPGR)))
				HI_More_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, 1);
		}	break;

		case _hoops_AHIP: {
			_hoops_PHIP const *		_hoops_RRA = (_hoops_PHIP const *)geom;

			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP const *		_hoops_HGRPR = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

				HI_More_Light (_hoops_RIGC, _hoops_SRCP, _hoops_HGRPR->_hoops_AAGSA());
				HI_More_Cutting_Planes (_hoops_RIGC, _hoops_SRCP, _hoops_HGRPR->_hoops_PAGSA());
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++) {
					_hoops_RAGSA (_hoops_RIGC, _hoops_SRCP, (Geometry const *)_hoops_RRA->_hoops_IHIP[i], _hoops_RRA->_hoops_RGPGR);
				}
			}
		}	break;
	}
}

GLOBAL_FUNCTION void HOOPS::_hoops_CIHIR (_hoops_AIGPR * _hoops_RIGC, _hoops_PHIP * _hoops_RRA, _hoops_SIHIR const * _hoops_SIIS, bool _hoops_CPAPP) 
{
	UNREFERENCED(_hoops_RIGC);
	_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_SIIS);
	ASSERT(_hoops_CPAPP || _hoops_APAPA != null);
	ASSERT(!BIT(_hoops_RRA->_hoops_RRHH, _hoops_IIHIR));
	if (_hoops_APAPA != null) {
		_hoops_APAPA->Remove(_hoops_RRA);
		if (_hoops_APAPA->Count() == 0) {
			_hoops_PGRCA(_hoops_SIIS)->_hoops_RRHH &= ~_hoops_IRPGI;
			HOOPS_WORLD->_hoops_PPAPA->Remove(_hoops_SIIS);
			delete _hoops_APAPA;
		}
	}
}


GLOBAL_FUNCTION void HOOPS::_hoops_ISRSA (_hoops_AIGPR * _hoops_RIGC, _hoops_PHIP * _hoops_RRA) {
#ifdef _hoops_HPAPP
	_hoops_ICIIR(_hoops_RIGC);
#else
	UNREFERENCED(_hoops_RIGC);
#endif
	ASSERT(_hoops_RRA->_hoops_HHIP > 0);
	ASSERT(!BIT(_hoops_RRA->owner->_hoops_RRHH, _hoops_HIRIR));
	ASSERT(!BIT(_hoops_RRA->_hoops_RRHH, _hoops_IIHIR));

	for (int i=0; i< _hoops_RRA->_hoops_HHIP; ++i) {

		_hoops_SIHIR const * _hoops_SIIS = _hoops_RRA->_hoops_IHIP[i];
#if 0
		if (_hoops_SIIS->type == _hoops_IRCP) {
			_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)_hoops_SIIS;
			if (_hoops_SRCP->name.text && strstr(_hoops_SRCP->name.text, "6592")) {
				_hoops_SRCP=_hoops_SRCP;
			}
		}
#endif

		_hoops_PGRCA(_hoops_SIIS)->_hoops_RRHH |= _hoops_IRPGI;

		_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_SIIS);

		if (_hoops_APAPA == null) {
			_hoops_APAPA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_RPAPA)(HOOPS_WORLD->memory_pool);
			HOOPS_WORLD->_hoops_PPAPA->InsertItem(_hoops_SIIS, _hoops_APAPA);
		}

		ASSERT(!_hoops_APAPA->ItemExists(_hoops_RRA));
		_hoops_APAPA->AddFirst(_hoops_RRA);
	}

}

local void _hoops_RPAPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				ref,		/* _hoops_GHCA _hoops_SHH _hoops_CPAP */
	void *					info) {
	_hoops_PHIP *	_hoops_RRA;
	_hoops_AAAPI *		pt = (_hoops_AAAPI *)info;
	_hoops_CRCP *				_hoops_SRCP = pt->newowner;

	if (ref == _hoops_SRCP) {
		HE_WARNING (HEC_REFERENCE, HES_ALREADY_INCLUDED, Sprintf_P (null, "Can't reference '%p' from itself", _hoops_SRCP));
		pt->_hoops_ACHPA = -1;
		return;
	}

	if (_hoops_GPAPI (_hoops_SRCP, (_hoops_SIHIR const *)ref)) {
		if (ref->type == _hoops_IRCP)
			HE_ERROR2 (HEC_REFERENCE, HES_INFINITE_LOOP,
					Sprintf_PP (null,"Can't reference '%p' into '%p' -", ref, _hoops_SRCP),
					   "An infinite loop of references would be created");
		else
			HE_ERROR2 (HEC_REFERENCE, HES_INFINITE_LOOP,
					HI_Sprintf4 (null, null, "Can't reference '%D' into '%p' -",
						0,0, (void *)ref->key, (void *)_hoops_SRCP),
						"An infinite loop of references would be created");
		return;
	}

	ZALLOC (_hoops_RRA, _hoops_PHIP);
	_hoops_RRA->type = _hoops_AHIP;
	_hoops_RRA->owner = _hoops_SRCP;
	_hoops_RRA->_hoops_CPGPR = _hoops_HCHPA;
	_hoops_RRA->_hoops_RGPGR = ~0;
	HI_Copy_Conditional (&pt->condition, &_hoops_RRA->condition);

	ALLOC_ARRAY (_hoops_RRA->_hoops_IHIP, 1, _hoops_SIHIR const *);
	_hoops_RRA->_hoops_HHIP = 1;
	_hoops_RRA->_hoops_IHIP[0] = (_hoops_SIHIR const *)ref;
	_hoops_PRRH (ref);

	HI_Insert_Geometry (_hoops_RIGC, (_hoops_HPAH alter *)pt->newowner, (Geometry *) _hoops_RRA,
						false,	/* _hoops_HAR _hoops_PRGI _hoops_CPIC _hoops_IS _hoops_HPPR _hoops_IH _hoops_RH 2D _hoops_AGIR */
						_hoops_IHSSR);

	_hoops_ISRSA(_hoops_RIGC, _hoops_RRA);

	_hoops_RAGSA (_hoops_RIGC, _hoops_SRCP, _hoops_RRA);

	if (_hoops_RRA->condition.count > 0)
		HI_Propagate_Maybes (_hoops_RIGC, _hoops_RRA->owner, _hoops_CPHGP);

	pt->_hoops_ACHPA = (pt->_hoops_ACHPA == 0) ? _hoops_RRA->key : -1;
}

GLOBAL_FUNCTION _hoops_PHIP * HI_Create_Reference (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				ref,
	_hoops_CRCP *				newowner,
	_hoops_CCPCA *			condition) {


	UNREFERENCED(condition);

	_hoops_AAAPI		_hoops_HASAR;
	ZERO_STRUCT(&_hoops_HASAR, _hoops_AAAPI);
	_hoops_HASAR.newowner = newowner;

	_hoops_RPAPI (_hoops_RIGC, ref, (void *)&_hoops_HASAR);

	if (_hoops_HASAR._hoops_ACHPA == 0)	/* _hoops_RIHH _hoops_GSPCA */
		return null;

	return (_hoops_PHIP *)_hoops_RCSSR (_hoops_RIGC, _hoops_HASAR._hoops_ACHPA);
}


local Key _hoops_APAPI (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_PPAPI,
	_hoops_CRCP *				_hoops_HPAPI,
	_hoops_CRCP *				_hoops_IPAPI,
	char const *			condition) {

	if (_hoops_IPAPI == null) {
		if ((_hoops_RIGC->open_list == null || _hoops_RIGC->open_list->_hoops_GCRIR != _hoops_RCRIR) &&
			!HI_Find_Our_Open (_hoops_RIGC))
			return 0;
		_hoops_IPAPI = _hoops_RIGC->open_list->info.segment._hoops_IGRPR;
	}

	_hoops_AAAPI		_hoops_HASAR;
	ZERO_STRUCT(&_hoops_HASAR, _hoops_AAAPI);
	_hoops_HASAR.newowner = _hoops_IPAPI;

	if (condition != null) {
		if (!HI_Parse_Condition (_hoops_RIGC,condition, &_hoops_HASAR.condition)) {
			HE_ERROR2 (HEC_REFERENCE, HES_CONDITIONAL,"Unable to process the conditional expression:",Sprintf_S (null, "'%s'", condition));
			return 0;
		}
	}

	if (_hoops_PPAPI != null)
		HI_For_Each (_hoops_RIGC, _hoops_PPAPI, true, _hoops_RPAPI, (void *)&_hoops_HASAR);
	else
		_hoops_RPAPI (_hoops_RIGC, _hoops_HPAPI, (void *)&_hoops_HASAR);

	HI_Free_Conditional (&_hoops_HASAR.condition);
	return _hoops_HASAR._hoops_ACHPA;
}



HC_INTERFACE Key HC_CDECL HC_Reference_Geometry (
	char const *			name)
{
	_hoops_PAPPR context("Reference_Geometry");

	_hoops_RPPPR();
	Key	key = _hoops_APAPI (context, name, null, null, null);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "DEFINE (HC_Reference_Geometry (%S), ", name));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", key));
	);

	if (key == -1) {
		HE_WARNING (HEC_REFERENCE, HES_BAD_RETURN_KEY, "Can't return the key - more than one segment was included");
		return _hoops_SHSSR;
	}
	if (key == 0)		/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return key;
}


HC_INTERFACE Key HC_CDECL HC_Reference_Geometry_By_Key (
	Key						key) {
	Key						_hoops_ACHPA;
	_hoops_PAPPR context("Reference_Geometry_By_Key");

	_hoops_RPPPR();
	int						offset;
	_hoops_CRCP *				_hoops_HPAPI = (_hoops_CRCP *)_hoops_SISIR (context, key, &offset);

	if (_hoops_HPAPI == null || BIT(_hoops_HPAPI->_hoops_RRHH, _hoops_HGAGR) ||
		(_hoops_HPAPI->type != _hoops_IRCP && (_hoops_HPAPI->type < _hoops_AHRIR || _hoops_HPAPI->type > _hoops_PHRIR))) {
			HE_ERROR (HEC_REFERENCE, HES_INVALID_KEY, "Provided key does not refer to a valid segment or geometry");
			_hoops_IRRPR();
			return _hoops_SHSSR;
	}
	if (BIT (_hoops_HPAPI->_hoops_RRHH, _hoops_CHRIR)) {		// _hoops_SRSIR _hoops_PPR _hoops_GASIR _hoops_GPP _hoops_RH _hoops_CCAH _hoops_RASIR
		if (_hoops_HPAPI->type == _hoops_HIIP)
			_hoops_HPAPI = (_hoops_CRCP *)HI_Isolate_Line_From_Multiline (context, (_hoops_SHRIR *)_hoops_HPAPI, offset);
		else if (_hoops_HPAPI->type == _hoops_PIRS)
			_hoops_HPAPI = (_hoops_CRCP *)HI_Isolate_Marker_From_Multimarker (context, (_hoops_GRPGR *)_hoops_HPAPI, offset);
	}

	_hoops_ACHPA = _hoops_APAPI (context, null, _hoops_HPAPI, null, null);

	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Reference_Geometry_By_Key (LOOKUP (%D)), ", key));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	if (_hoops_ACHPA == 0)	/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return _hoops_ACHPA;
}



HC_INTERFACE Key HC_CDECL HC_Reference_Geometry_Key_By_Ke (
	Key						target_segment,
	Key						reference_key) {
	_hoops_PAPPR context("Reference_Geometry_Key_By_Key");

	_hoops_RPPPR();
	int						offset;
	_hoops_CRCP *				_hoops_HPAPI = (_hoops_CRCP *)_hoops_SISIR (context, reference_key, &offset);

	if (_hoops_HPAPI == null || BIT(_hoops_HPAPI->_hoops_RRHH, _hoops_HGAGR) ||
		(_hoops_HPAPI->type != _hoops_IRCP && (_hoops_HPAPI->type < _hoops_AHRIR || _hoops_HPAPI->type > _hoops_PHRIR))) {
			HE_ERROR (HEC_REFERENCE, HES_INVALID_KEY, "Provided reference key does not refer to a valid segment or geometry");
			_hoops_IRRPR();
			return _hoops_SHSSR;
	}

	_hoops_CRCP *	_hoops_IPAPI = (_hoops_CRCP *)_hoops_RCSSR (context, target_segment);
	if (_hoops_IPAPI == null || _hoops_IPAPI->type != _hoops_IRCP || BIT(_hoops_IPAPI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_REFERENCE, HES_INVALID_KEY, "Provided target segment key does not refer to a valid segment");
		_hoops_IRRPR();
		return _hoops_SHSSR;
	}
	if (BIT (_hoops_HPAPI->_hoops_RRHH, _hoops_CHRIR)) {		// _hoops_SRSIR _hoops_PPR _hoops_GASIR _hoops_GPP _hoops_RH _hoops_CCAH _hoops_RASIR
		if (_hoops_HPAPI->type == _hoops_HIIP)
			_hoops_HPAPI = (_hoops_CRCP *)HI_Isolate_Line_From_Multiline (context, (_hoops_SHRIR *)_hoops_HPAPI, offset);
		else if (_hoops_HPAPI->type == _hoops_PIRS)
			_hoops_HPAPI = (_hoops_CRCP *)HI_Isolate_Marker_From_Multimarker (context, (_hoops_GRPGR *)_hoops_HPAPI, offset);
	}

	Key _hoops_ACHPA = _hoops_APAPI (context, null, _hoops_HPAPI, _hoops_IPAPI, null);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Reference_Geometry_Key_By_Key (LOOKUP (%D),", target_segment));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D)),", reference_key));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	if (_hoops_ACHPA == 0)	/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return _hoops_ACHPA;
}



HC_INTERFACE Key HC_CDECL HC_Conditional_Reference (
	char const *			name,
	char const *			condition)
{
	_hoops_PAPPR context("Conditional_Reference");

	_hoops_RPPPR();
	Key	key = _hoops_APAPI (context, name, null, null, null);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "DEFINE (HC_Conditional_Reference (%S, %S), ", name, condition));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", key));
	);

	if (key == -1) {
		HE_WARNING(HEC_REFERENCE, HES_BAD_RETURN_KEY, "Can't return the key - more than one segment was included");
		return _hoops_SHSSR;
	}
	if (key == 0)		/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return key;
}



HC_INTERFACE Key HC_CDECL HC_Conditional_Reference_By_Key (
	Key						key,
	char const *			condition)
{
	_hoops_PAPPR context("Conditional_Reference_By_Key");

	_hoops_RPPPR();
	int						offset;
	_hoops_CRCP *				_hoops_HPAPI = (_hoops_CRCP *)_hoops_SISIR (context, key, &offset);

	if (_hoops_HPAPI == null || BIT(_hoops_HPAPI->_hoops_RRHH, _hoops_HGAGR) ||
		(_hoops_HPAPI->type != _hoops_IRCP && (_hoops_HPAPI->type < _hoops_AHRIR || _hoops_HPAPI->type > _hoops_PHRIR))) {
			HE_ERROR (HEC_REFERENCE, HES_INVALID_KEY, "Provided key does not refer to a valid segment or geometry");
			_hoops_IRRPR();
			return _hoops_SHSSR;
	}
	if (BIT (_hoops_HPAPI->_hoops_RRHH, _hoops_CHRIR)) {		// _hoops_SRSIR _hoops_PPR _hoops_GASIR _hoops_GPP _hoops_RH _hoops_CCAH _hoops_RASIR
		if (_hoops_HPAPI->type == _hoops_HIIP)
			_hoops_HPAPI = (_hoops_CRCP *)HI_Isolate_Line_From_Multiline (context, (_hoops_SHRIR *)_hoops_HPAPI, offset);
		else if (_hoops_HPAPI->type == _hoops_PIRS)
			_hoops_HPAPI = (_hoops_CRCP *)HI_Isolate_Marker_From_Multimarker (context, (_hoops_GRPGR *)_hoops_HPAPI, offset);
	}

	Key	_hoops_ACHPA = _hoops_APAPI (context, null, _hoops_HPAPI, null, null);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Conditional_Reference_By_Key (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_S	 (null, "%S), ", condition));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	if (_hoops_ACHPA == 0)	/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return _hoops_ACHPA;
}



HC_INTERFACE Key HC_CDECL HC_Show_Include_Segment (
	Key					key,
	char *				includee)
{
	_hoops_PAPPR context("Show_Include_Segment");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Include_Segment () */\n");
	);

	Key	result = _hoops_SHSSR;

	_hoops_CSPPR();

	_hoops_PGRPR const *	include = (_hoops_PGRPR *)_hoops_RCSSR (context, key);

	if (include == null || include->type != _hoops_AGRPR || BIT (include->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_INCLUDE, HES_INVALID_KEY, "Provided key does not refer to a valid inclusion");
	}
	else {
		_hoops_CRCP const *	_hoops_SRCP = (_hoops_CRCP const *) (include->_hoops_IGRPR);
		if (includee != null)
			HI_Return_Sprintf1 (includee, -1, "%p", (void *)_hoops_SRCP);
		result = _hoops_SRCP->key;
	}

	_hoops_IRRPR();
	return result;
#endif
}




HC_INTERFACE void HC_CDECL HC_Show_Conditional_Include (
	Key					key,
	char *				includee,
	char *				condition)
{
	_hoops_PAPPR context("Show_Conditional_Include");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Conditional_Include_Segment () */\n");
	);

	_hoops_CSPPR();

	_hoops_PGRPR const *		include = (_hoops_PGRPR *)_hoops_RCSSR (context, key);

	if (include == null || include->type != _hoops_AGRPR || BIT (include->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_INCLUDE, HES_INVALID_KEY, "Provided key does not refer to a valid inclusion");
	}
	else {
		_hoops_CRCP const *	_hoops_SRCP = (_hoops_CRCP const *) (include->_hoops_IGRPR);
		HI_Return_Sprintf1 (includee, -1, "%p", (void *)_hoops_SRCP);
		HI_Show_Conditional (&include->condition, condition, -1);
	}

	_hoops_IRRPR();
#endif
}




/****************************************************************************************************/



static const int        _hoops_CPAPI[32] = {
        1, 2, 29, 3, 30, 15, 25, 4, 31, 23, 21, 16, 26, 18, 5, 9,
        32, 28, 14, 24, 22, 20, 17, 8, 27, 13, 19, 7, 12, 6, 11, 10
};
static const int        _hoops_SPAPI = 0x077CB531UL;

static int _hoops_GHAPI (int v)
{
	v *= _hoops_SPAPI;
	return _hoops_CPAPI[(v >> 27) & 0x1F];
}



HC_INTERFACE void HC_CDECL HC_Show_Reference_Geometry_Filt (
	Key				key,
	char *			filter)
{
	_hoops_PAPPR context("Show_Reference_Geometry_Filter");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Reference_Geometry_Filter () */\n");
	);

	_hoops_CSPPR();

	_hoops_PHIP	*	_hoops_RRA = (_hoops_PHIP *)_hoops_RCSSR (context, key);

	if (_hoops_RRA == null || _hoops_RRA->type != _hoops_AHIP || BIT (_hoops_RRA->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_INCLUDE, HES_INVALID_KEY, "Provided key does not refer to a valid reference");
	}

	if (_hoops_RRA->_hoops_RGPGR == ~0) {
		HI_Return_Chars (filter, -1, "geometry", 8);
	}
	else {
		char buf[4096];
		char * p = buf;
		int count = 0;
		bool _hoops_RHAPI = false;
		int mask = _hoops_RRA->_hoops_RGPGR;

		while (mask != 0) {
			int bit = _hoops_RIII(mask);
			mask &= ~bit;
			count++;
		}

		mask = _hoops_RRA->_hoops_RGPGR;

		if (count > 16) {
			p = HI_Copy_Chars ("geometry,", p);
			_hoops_RHAPI = true;
			mask = ~mask;
		}
		else {
			p = HI_Copy_Chars ("no geometry,", p);
		}

		while (mask != 0) {
			int bit = _hoops_RIII(mask);

			mask &= ~bit;

			if (_hoops_RHAPI)
				p = HI_Copy_Chars ("no ", p);

			switch (_hoops_GHAPI(bit)-1) {
				case _hoops_IIAGR(_hoops_HGPGR): {
					p = HI_Copy_Chars ("cutting plane,", p);
				} break;

				case _hoops_IIAGR(_hoops_ICIP): {
					p = HI_Copy_Chars ("light,", p);
				} break;

				case _hoops_IIAGR(_hoops_SCIP): {
					p = HI_Copy_Chars ("shell,", p);
				} break;

				case _hoops_IIAGR(_hoops_GGCP): {
					p = HI_Copy_Chars ("grid,", p);
				} break;

				case _hoops_IIAGR(_hoops_GSIP): {
					p = HI_Copy_Chars ("mesh,", p);
				} break;

				case _hoops_IIAGR(_hoops_PRCP): {
					p = HI_Copy_Chars ("nurbs surface,", p);
				} break;

				case _hoops_IIAGR(_hoops_ASIP): {
					p = HI_Copy_Chars ("cylinder,", p);
				} break;

				case _hoops_IIAGR(_hoops_CSIP): {
					p = HI_Copy_Chars ("polycylinder,", p);
				} break;

				case _hoops_IIAGR(_hoops_HSIP): {
					p = HI_Copy_Chars ("sphere,", p);
				} break;

				case _hoops_IIAGR(_hoops_RCIP): {
					p = HI_Copy_Chars ("polygon,", p);
				} break;

				case _hoops_IIAGR(_hoops_SGCP): {
					p = HI_Copy_Chars ("circle,", p);
				} break;

				case _hoops_IIAGR(_hoops_GRCP): {
					p = HI_Copy_Chars ("circular chord,", p);
				} break;

				case _hoops_IIAGR(_hoops_RRCP): {
					p = HI_Copy_Chars ("circular wedge,", p);
				} break;

				case _hoops_IIAGR(_hoops_CGCP): {
					p = HI_Copy_Chars ("ellipse,", p);
				} break;

				case _hoops_IIAGR(_hoops_PIIP): {
					p = HI_Copy_Chars ("line,", p);
				} break;

				case _hoops_IIAGR(_hoops_IIIP): {
					p = HI_Copy_Chars ("polyline,", p);
				} break;

				case _hoops_IIAGR(_hoops_CHIP): {
					p = HI_Copy_Chars ("nurbs curve,", p);
				} break;

				case _hoops_IIAGR(_hoops_RIIP): {
					p = HI_Copy_Chars ("circular arc,", p);
				} break;

				case _hoops_IIAGR(_hoops_GIIP): {
					p = HI_Copy_Chars ("elliptical arc,", p);
				} break;

				case _hoops_IIAGR(_hoops_SIIP): {
					p = HI_Copy_Chars ("infinite line,", p);
				} break;

				case _hoops_IIAGR(_hoops_HGCP): {
					p = HI_Copy_Chars ("image,", p);
				} break;

				case _hoops_IIAGR(_hoops_PCIP): {
					p = HI_Copy_Chars ("marker,", p);
				} break;

				case _hoops_IIAGR(_hoops_AGCP): {
					p = HI_Copy_Chars ("text,", p);
				} break;

				case _hoops_IIAGR(HK_STRING_CURSOR): {
					p = HI_Copy_Chars ("string cursor,", p);
				} break;

				case _hoops_IIAGR(_hoops_AHIP): {
					p = HI_Copy_Chars ("reference,", p);
				} break;

				default: break; // _hoops_GHCA _hoops_HS _hoops_AHAPI _hoops_SIH _hoops_SGS _hoops_CHR _hoops_HAR _hoops_APIP
			}
		}
		p--;	/* _hoops_HASIR _hoops_CGHI ',' */
		HI_Return_Chars (filter, -1, buf, (int)(p - buf));
	}

	_hoops_IRRPR();

#endif
}





HC_INTERFACE Key HC_CDECL HC_Show_Reference_Geometry (
	Key					key)
{
	_hoops_PAPPR context("Show_Reference_Geometry");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return _hoops_SHSSR;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Reference_Geometry () */\n");
	);

	_hoops_CSPPR();

	_hoops_PHIP	*_hoops_RRA = (_hoops_PHIP *)_hoops_RCSSR (context, key);

	if (_hoops_RRA == null || _hoops_RRA->type != _hoops_AHIP || BIT (_hoops_RRA->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_INCLUDE, HES_INVALID_KEY, "Provided key does not refer to a valid reference");
		return _hoops_SHSSR;
	}

	Key _hoops_IAPSA;

	if (_hoops_RRA->_hoops_IHIP[0]->key < 0)
		_hoops_IAPSA = _hoops_RRA->_hoops_IHIP[0]->key;
	else
		_hoops_IAPSA = _hoops_AIRIR(_hoops_RRA->_hoops_IHIP[0]);

	_hoops_IRRPR();

	return	_hoops_IAPSA;
#endif
}



HC_INTERFACE Key HC_CDECL HC_Show_Conditional_Reference (
	Key				key,
	char *			condition)
{
	_hoops_PAPPR context("Show_Conditional_Reference");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Conditional_Reference () */\n");
	);

	_hoops_CSPPR();

	_hoops_PHIP	*	_hoops_RRA = (_hoops_PHIP *)_hoops_RCSSR (context, key);

	Key result = _hoops_SHSSR;;

	if (_hoops_RRA == null || _hoops_RRA->type != _hoops_AHIP || BIT (_hoops_RRA->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_INCLUDE, HES_INVALID_KEY, "Provided key does not refer to a valid reference");
	}
	else {
		HI_Show_Conditional (&_hoops_RRA->condition, condition, -1);
		result = _hoops_RRA->_hoops_IHIP[0]->key;
	}

	_hoops_IRRPR();

	return result;
#endif
}





HC_INTERFACE void HC_CDECL HC_Show_Reference_Keys (
	Key							key,
	int alter *					count,
	Key alter *					keys) 
{
	_hoops_PAPPR context("Show_Reference_Keys");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Reference_Keys () */\n");
	);

	_hoops_CSPPR();

	_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP *)_hoops_RCSSR (context, key);

	if (_hoops_RRA == null || _hoops_RRA->type != _hoops_AHIP || BIT (_hoops_RRA->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_INCLUDE, HES_INVALID_KEY, "Provided key does not refer to a valid reference");
	}
	else {

		if (count)
			*count = _hoops_RRA->_hoops_HHIP;

		for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++)
			keys[i] = _hoops_AIRIR(_hoops_RRA->_hoops_IHIP[i]);
	}

	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Reference_Keys_Count (
	Key							key,
	int alter *					count) 
{
	_hoops_PAPPR context("Show_Reference_Keys_Count");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Reference_Keys_Count () */\n");
	);

	_hoops_CSPPR();
	_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP *)_hoops_RCSSR (context, key);

	if (_hoops_RRA == null || _hoops_RRA->type != _hoops_AHIP || BIT (_hoops_RRA->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_INCLUDE, HES_INVALID_KEY, "Provided key does not refer to a valid reference");
	}
	else
		*count = _hoops_RRA->_hoops_HHIP;

	_hoops_IRRPR();
#endif
}


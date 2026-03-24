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
 * $Id: obf_tmp.txt 1.90 2010-11-09 06:47:15 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


#ifndef DISABLE_STYLE_SEGMENT

struct _hoops_SSGGGR {
	Attribute **	_hoops_ASRGR;
	Key				_hoops_ACHPA;
	_hoops_CCPCA		condition;
	_hoops_CRCP *		_hoops_IPAPI;
	_hoops_HCRPR *			_hoops_SGAIR;
	Integer32		_hoops_PCSCA;
};


#ifndef DISABLE_STYLE_SEGMENT

/* _hoops_IRS _hoops_IAHA _hoops_SSCP _hoops_SAHR _hoops_RPII _hoops_SPIP _hoops_PAR _hoops_SSCP _hoops_SAHR _hoops_PCIAH _hoops_HHH _hoops_AIRC. */

/* _hoops_CGH _hoops_ISPR _hoops_IH _hoops_AIRC _hoops_RSGS _hoops_GGR _hoops_PSHR-_hoops_PAPA _hoops_PCIAA */

local void _hoops_GGRGGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	bool *					_hoops_PPIHA,
	Attribute *				_hoops_ASGPR) {
	/* _hoops_HPCAR _hoops_HCR (_hoops_RGRGGR) _hoops_AIRC _hoops_RCPS _hoops_RAS _hoops_HCR _hoops_PCIAA */

	while (_hoops_ASGPR->type <= HK_STYLE) {
		if (_hoops_ASGPR->type == HK_STYLE &&
			!BIT (_hoops_ASGPR->_hoops_RRHH, _hoops_HGAGR)) {
		
			Style *		style = (Style *)_hoops_ASGPR;

			if (style->_hoops_IGRPR && !BIT (style->_hoops_IGRPR->_hoops_RRHH, _hoops_HGAGR) &&
				style->_hoops_IGRPR->_hoops_IPPGR != null)
				_hoops_GGRGGR (_hoops_RIGC, _hoops_SRCP, _hoops_PPIHA, style->_hoops_IGRPR->_hoops_IPPGR);
		}

		if ((_hoops_ASGPR = _hoops_ASGPR->next) == null) 
			return;
	}

	do if (!BIT (_hoops_ASGPR->_hoops_RRHH, _hoops_HGAGR)) {
		char			type = _hoops_ASGPR->type;

		/* _hoops_AGSIP: _hoops_AIRC _hoops_PGAP _hoops_PAH _hoops_HASC _hoops_HHSA _hoops_IRS _hoops_AIIAP _hoops_SGHHR */

		switch (type) {
			case HK_COLOR: {
				_hoops_SSGI *			color = (_hoops_SSGI *)_hoops_ASGPR;
				int				_hoops_AGRGGR = _hoops_SRCP->_hoops_IGCCA;

				/* _hoops_IRHH _hoops_SCH _hoops_IHSH _hoops_PII _hoops_HCR _hoops_PSHA _hoops_ARI _hoops_HS _hoops_HGAS */
				color->_hoops_CCCIR = color->_hoops_GHA;
				HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, null, _hoops_ASGPR);

				/* "_hoops_CPRAA" _hoops_IRS _hoops_HAIR _hoops_CCA _hoops_IHSP _hoops_CHH _hoops_HAHA _hoops_RH _hoops_RPR, _hoops_HIS _hoops_PPSI _hoops_SCH _hoops_ISSC */
				if (_hoops_AGRGGR != _hoops_SRCP->_hoops_IGCCA)
				HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_AGRGGR - _hoops_SRCP->_hoops_IGCCA);
			}	break;

			case HK_RENDERING_OPTIONS:
			case HK_SELECTABILITY:
			case HK_VISIBILITY:
			case HK_DRIVER_OPTIONS:
			case HK_HEURISTICS:
			case HK_MODELLING_MATRIX:
			case HK_TEXT_FONT: {
				HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, null, _hoops_ASGPR);
			}	break;

			default: {
				if (!_hoops_PPIHA [(int)type]) {
					HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, type, null, _hoops_ASGPR);
					_hoops_PPIHA [(int)type] = true;
				}
			}	break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
}
#endif


GLOBAL_FUNCTION void HI_Redraw_Style (
	_hoops_AIGPR *	_hoops_RIGC,
	Style *					style) {
#ifndef DISABLE_STYLE_SEGMENT
	bool		_hoops_PPIHA [_hoops_CRCCA+1];
	Attribute	*_hoops_ASGPR;

	ZERO_ARRAY(_hoops_PPIHA, _hoops_CRCCA+1, bool);

	if ((_hoops_ASGPR = style->owner->_hoops_IPPGR) != null) do {
		if (!BIT (_hoops_ASGPR->_hoops_RRHH, _hoops_HGAGR))
			_hoops_PPIHA [(int)_hoops_ASGPR->type] = true;
		}
	_hoops_RGGA ((_hoops_ASGPR = _hoops_ASGPR->next) == null);

	if (style->_hoops_IGRPR && style->_hoops_IGRPR->_hoops_IPPGR)
		_hoops_GGRGGR (_hoops_RIGC, style->owner, _hoops_PPIHA, style->_hoops_IGRPR->_hoops_IPPGR);
#endif
}

GLOBAL_FUNCTION void HI_Delete_Style_Attributes (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	Style *					style) {
	
	if (style->_hoops_IGRPR) {
		int					_hoops_AGRGGR = _hoops_SRCP->_hoops_IGCCA;
		Attribute *			_hoops_HPHCR;
		if ((_hoops_HPHCR = style->_hoops_IGRPR->_hoops_IPPGR) != null) do {
			if (_hoops_HPHCR->type == HK_STYLE)
				HI_Delete_Style_Attributes (_hoops_RIGC, _hoops_SRCP, (Style *)_hoops_HPHCR);
			else
				HI_Redraw_Attribute (_hoops_RIGC, _hoops_SRCP, _hoops_HPHCR->type, _hoops_HPHCR, null);
		} _hoops_RGGA ((_hoops_HPHCR = _hoops_HPHCR->next) == null);

		/* "_hoops_PISSA" _hoops_IRS _hoops_HAIR _hoops_CCA _hoops_IHSP _hoops_CHH _hoops_HAHA _hoops_RH _hoops_RPR, _hoops_HIS _hoops_PPSI _hoops_SCH _hoops_ISSC */
		if (_hoops_AGRGGR != _hoops_SRCP->_hoops_IGCCA)
			HI_More_Transparencies (_hoops_RIGC, _hoops_SRCP, _hoops_AGRGGR - _hoops_SRCP->_hoops_IGCCA);
	}
}

local bool _hoops_PGRGGR (
	Xref *			_hoops_AHICA,
	_hoops_CRCP *		_hoops_HCPIH) {

	do if (_hoops_AHICA->type == HK_STYLE &&
		   !BIT (_hoops_AHICA->_hoops_RRHH, _hoops_HGAGR)) {
		_hoops_CRCP *	owner = _hoops_AHICA->owner;

		if (owner == _hoops_HCPIH) 
			return true;

		if (owner->_hoops_SGRPR() != null)
			if (_hoops_PGRGGR (owner->_hoops_SGRPR(), _hoops_HCPIH)) return true;
	} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

	return false;
}


local void _hoops_HGRGGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				ref,
	void *					info) {
	
	_hoops_SSGGGR *		pt = (_hoops_SSGGGR *)info;
	Attribute **			_hoops_ASRGR = pt->_hoops_ASRGR;
	_hoops_CRCP *				owner = pt->_hoops_IPAPI;
	ASSERT(owner);

	if (ref && BIT (ref->_hoops_PHSI, _hoops_PRSIR)) {
		HI_Not_When_Streamed (ref, "use it as a style");
		return;
	}

	Style *					style;
	
	/* _hoops_SSCP _hoops_SCH _hoops_AIAH _hoops_RPII _hoops_IGRGGR? */
	if ((style = (Style *)*_hoops_ASRGR) != null) do {

		if (style->type > HK_STYLE)
			break;
		else 
		if (style->type == HK_STYLE &&
			!BIT (style->_hoops_RRHH, _hoops_HGAGR) &&
			((ref && style->_hoops_IGRPR == ref) || 
			 (ref == null && style->_hoops_IGRPR == null && 
				style->_hoops_PCSCA == pt->_hoops_PCSCA &&
				_hoops_RAHSR(style->_hoops_SGAIR, *pt->_hoops_SGAIR))) &&
			style->condition.count == pt->condition.count &&
			EQUAL_MEMORY (style->condition._hoops_ASACA, style->condition.count*sizeof(int), pt->condition._hoops_ASACA)) {

			if (ref != null) {

				if (style->condition.count == 0) {
					//_hoops_GASA: _hoops_PHHS _hoops_SSPC _hoops_APHS _hoops_IAHA _hoops_RPGAR
					//_hoops_GHCC (_hoops_CGRGGR, _hoops_SGRGGR,
					//	_hoops_GRRGGR (_hoops_IRAP, "_hoops_HAIC'_hoops_RA _hoops_IAHA '%_hoops_CCAHR' _hoops_PII '%_hoops_CCAHR' - _hoops_AIAH _hoops_HRGR", _hoops_IAHA->_hoops_RRRPR, _hoops_PAGGR));
				}
				else {
					char			buffer[4096];
					char			condition[4096];

					HI_Show_Conditional (&style->condition, condition, -1);
					Sprintf_S (buffer, "with condition '%s' - already is", condition);
					_hoops_PHPGR (HEC_STYLE, HES_ALREADY_STYLED,
						Sprintf_PP (null, "Can't style '%p' like '%p'",style->owner, ref),buffer);
				}
			}
			else {

				if (style->condition.count == 0) {
					//_hoops_GASA: _hoops_PHHS _hoops_SSPC _hoops_APHS _hoops_IAHA _hoops_RPGAR
					//_hoops_GHCC (_hoops_CGRGGR, _hoops_SGRGGR,
					//	_hoops_RRRGGR (_hoops_IRAP, "_hoops_HAIC'_hoops_RA _hoops_IAHA '%_hoops_CCAHR' _hoops_CCA _hoops_ACGIP _hoops_IAHA '%_hoops_ACHP' - _hoops_AIAH _hoops_HRGR", _hoops_IAHA->_hoops_RRRPR, _hoops_SGPSH->_hoops_ARRGGR));
				}
				else {
					char			buffer[4096];
					char			condition[4096];

					HI_Show_Conditional (&style->condition, condition, -1);
					Sprintf_S (buffer, "with condition '%s' - already is", condition);
					_hoops_PHPGR (HEC_STYLE, HES_ALREADY_STYLED,
						Sprintf_PN (null, "Can't style '%p' with named style '%n'",style->owner, pt->_hoops_SGAIR),buffer);
				}
			}

			pt->_hoops_ACHPA = (pt->_hoops_ACHPA == 0) ? style->key : -1;
			return;
		}

		_hoops_ASRGR = &style->next;	/* _hoops_CCAH _hoops_SPR _hoops_GRS _hoops_PHHR _hoops_RAS _hoops_ARI (_hoops_PAR _hoops_SPHR) */
	} while ((style = (Style *)style->next) != null);

	if (ref != null) {

		if (owner == ref ||
			(owner->_hoops_SGRPR() != null &&
			 _hoops_PGRGGR (owner->_hoops_SGRPR(), ref))) {
			HE_ERROR2 (HEC_STYLE, HES_INFINITE_LOOP,
					Sprintf_PP (null, "Can't style '%p' like '%p' -", owner, ref),
					   "An infinite loop of Styles would be created");
			return;
		}
	}

	ZALLOC (style, Style);
	style->type = HK_STYLE;
	style->_hoops_HIHI = 1;
	style->owner = owner;
	style->_hoops_CPGPR = _hoops_HCHPA;
	style->key = _hoops_AIRIR (style);

	if ((style->next = *_hoops_ASRGR) != null)
		(*_hoops_ASRGR)->backlink = &style->next;

	*_hoops_ASRGR = (Attribute *)style;
	style->backlink = _hoops_ASRGR;

	if (pt->condition.count > 0)
		HI_Copy_Conditional (&pt->condition, &style->condition);

	if (pt->_hoops_SGAIR) {

		/*_hoops_SRAI _hoops_RSIRR*/
		style->_hoops_SGAIR.text = pt->_hoops_SGAIR->text;
		style->_hoops_SGAIR.length = pt->_hoops_SGAIR->length;
		pt->_hoops_SGAIR->text = null;
		pt->_hoops_SGAIR->length = 0;

		style->_hoops_PCSCA =  pt->_hoops_PCSCA;
	}
	else {

		style->_hoops_IGRPR = ref;
		_hoops_PRRH (ref);
		_hoops_ACSCA(_hoops_RIGC, style, ref);

		_hoops_ACHR	_hoops_HAAPI = ref->_hoops_RCGC & (
			_hoops_HPRRA|_hoops_RPHGP|_hoops_APHGP|
			_hoops_ASPCR|_hoops_PSPCR|_hoops_AHHGP|_hoops_CPHGP);

		if (style->condition.count > 0)
			_hoops_HAAPI |= _hoops_CPHGP;

		_hoops_HAAPI &= ~style->owner->_hoops_RCGC;

		if (_hoops_HAAPI != 0)
			HI_Propagate_Maybes (_hoops_RIGC, style->owner, _hoops_HAAPI);

		if (!ANYBIT (ref->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR|_hoops_GIGSA|_hoops_RIGSA))
			if (ref->_hoops_IGCCA > 0)
				HI_More_Transparencies (_hoops_RIGC, owner, ref->_hoops_IGCCA);

		if (style->_hoops_IGRPR->_hoops_IPPGR != null)
			HI_Redraw_Style (_hoops_RIGC, style);
	}

	pt->_hoops_ACHPA = (pt->_hoops_ACHPA == 0) ? style->key : -1;
}



local Key _hoops_PRRGGR (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			style_name,
	_hoops_CRCP *				_hoops_IASSI,
	_hoops_HCRPR *					_hoops_SGAIR,
	_hoops_CRCP *				_hoops_IPAPI,
	char const *			condition) {

	if (_hoops_IPAPI == null) {
		if ((_hoops_RIGC->open_list == null || _hoops_RIGC->open_list->_hoops_GCRIR != _hoops_RCRIR) && 
			!HI_Find_Our_Open (_hoops_RIGC))
			return 0;
		_hoops_IPAPI = _hoops_RIGC->open_list->info.segment._hoops_IGRPR;
	}

	_hoops_SSGGGR			_hoops_HASAR;
	ZERO_STRUCT(&_hoops_HASAR, _hoops_SSGGGR); 
	_hoops_HASAR._hoops_IPAPI = _hoops_IPAPI;

	if (_hoops_SGAIR) {
		_hoops_HASAR._hoops_SGAIR = _hoops_SGAIR;
		_hoops_HCARA(*_hoops_SGAIR, _hoops_HASAR._hoops_PCSCA);
	}

	if (condition != null) {
		if (!HI_Parse_Condition (_hoops_RIGC, condition, &_hoops_HASAR.condition)) {
			HE_ERROR2 (HEC_STYLE, HES_CONDITIONAL, "Unable to process the conditional expression:", Sprintf_S (null, "'%s'", condition));
			return 0;
		}
	}

	Attribute *				_hoops_GHHPH;
	if ((_hoops_GHHPH = _hoops_IPAPI->_hoops_IPPGR) == null) {
		_hoops_HASAR._hoops_ASRGR = &_hoops_IPAPI->_hoops_IPPGR;

		if (style_name)
			HI_For_Each (_hoops_RIGC, style_name, true, _hoops_HGRGGR, (void *)&_hoops_HASAR);
		else
			_hoops_HGRGGR (_hoops_RIGC, _hoops_IASSI, (void *)&_hoops_HASAR);
	}
	else _hoops_PCCAR {
		if (_hoops_GHHPH->type >= HK_STYLE) {
			/* _hoops_ARPP _hoops_RGR _hoops_SPR */
			_hoops_HASAR._hoops_ASRGR = _hoops_GHHPH->backlink;

			if (style_name)
				HI_For_Each (_hoops_RIGC, style_name, true, _hoops_HGRGGR, (void *)&_hoops_HASAR);
			else
				_hoops_HGRGGR (_hoops_RIGC, _hoops_IASSI, (void *)&_hoops_HASAR);
			break;
		}
		else if (_hoops_GHHPH->next == null) {
			/* _hoops_RAS _hoops_RGR _hoops_SPR */
			_hoops_HASAR._hoops_ASRGR = &_hoops_GHHPH->next;

			if (style_name)
				HI_For_Each (_hoops_RIGC, style_name, true, _hoops_HGRGGR, (void *)&_hoops_HASAR);
			else
				_hoops_HGRGGR (_hoops_RIGC, _hoops_IASSI, (void *)&_hoops_HASAR);
			break;
		}
		_hoops_GHHPH = _hoops_GHHPH->next;
	}

	HI_Free_Conditional (&_hoops_HASAR.condition);

	return _hoops_HASAR._hoops_ACHPA;
}
#endif


HC_INTERFACE Key HC_CDECL HC_Named_Style_Segment (
	char const *		style_name) 
{
	_hoops_PAPPR context("Named_Style_Segment");

#ifdef DISABLE_STYLE_SEGMENT
	_hoops_IRPPR ("Style_Segment");
#else

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (style_name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_STYLE, HES_NULL_INPUT, "Named style name is blank or null");
		return _hoops_SHSSR;
	}

	_hoops_RPPPR();
	Key	key = _hoops_PRRGGR (context, null, null, &_hoops_CRPCR, null, null);
	_hoops_IRRPR();

	_hoops_RGAIR(_hoops_CRPCR);

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "DEFINE (HC_Named_Style_Segment (%S), ", style_name));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", key));
	);

	if (key == -1) {
		HE_WARNING (HEC_STYLE, HES_BAD_RETURN_KEY,
			"Can't return the key - more than one segment was styled");
		return _hoops_SHSSR;
	}
	if (key == 0)		/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

#endif
	return key;
}


HC_INTERFACE Key HC_CDECL HC_Named_Style_Segment_By_Key (
	Key				target_segment,
	char const *	style_name) 
{
	_hoops_PAPPR context("Named_Style_Segment_By_Key");

#ifdef DISABLE_STYLE_SEGMENT
	_hoops_IRPPR ("Style_Segment");
	return	_hoops_SHSSR;
#else

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (style_name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_STYLE, HES_NULL_INPUT, "Named style name is blank or null");
		return _hoops_SHSSR;
	}

	_hoops_RPPPR();

	_hoops_CRCP *	_hoops_IPAPI = (_hoops_CRCP *)_hoops_RCSSR (context, target_segment);
	if (_hoops_IPAPI == null || _hoops_IPAPI->type != _hoops_IRCP || BIT(_hoops_IPAPI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_STYLE, HES_INVALID_KEY, "Provided target segment key does not refer to a valid segment");
		_hoops_IRRPR();
		return _hoops_SHSSR;
	}

	Key	key = _hoops_PRRGGR (context, null, null, &_hoops_CRPCR, _hoops_IPAPI, null);
	_hoops_IRRPR();

	_hoops_RGAIR(_hoops_CRPCR);

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Named_Style_Segment_By_Key (LOOKUP (%D),",target_segment));
		HI_Dump_Code (Sprintf_S (null, "%S), ", style_name));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", key));
	);

	if (key == -1) {
		HE_WARNING (HEC_STYLE, HES_BAD_RETURN_KEY, "Can't return the key - more than one segment was styled");
		return _hoops_SHSSR;
	}
	if (key == 0)		/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return key;
#endif	
}


HC_INTERFACE Key HC_CDECL HC_Style_Segment (
	char const *	name) 
{
	_hoops_PAPPR context("Style_Segment");

#ifdef DISABLE_STYLE_SEGMENT
	_hoops_IRPPR ("Style_Segment");
#else

	_hoops_RPPPR();
	Key	key = _hoops_PRRGGR (context, name, null, null, null, null);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "DEFINE (HC_Style_Segment (%S), ", name));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", key));
	);

	if (key == -1) {
		HE_WARNING (HEC_STYLE, HES_BAD_RETURN_KEY, "Can't return the key - more than one segment was styled");
		return _hoops_SHSSR;
	}
	if (key == 0)		/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

#endif
	return key;
}

HC_INTERFACE Key HC_CDECL HC_Style_Segment_By_Key (
	Key			key) 
{
	_hoops_PAPPR context("Style_Segment_By_Key");

#ifdef DISABLE_STYLE_SEGMENT
	_hoops_IRPPR ("Style_Segment");
	return	_hoops_SHSSR;
#else

	_hoops_RPPPR();
	_hoops_CRCP *	_hoops_IASSI = (_hoops_CRCP *)_hoops_RCSSR (context, key);
	if (_hoops_IASSI == null || _hoops_IASSI->type != _hoops_IRCP || BIT(_hoops_IASSI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_STYLE, HES_INVALID_KEY, "Provided key does not refer to a valid segment");
		_hoops_IRRPR();
		return _hoops_SHSSR;
	}

	Key	_hoops_ACHPA = _hoops_PRRGGR (context, null, _hoops_IASSI, null, null, null);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Style_Segment_By_Key (LOOKUP (%D)), ", key));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	if (_hoops_ACHPA == 0)	/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return _hoops_ACHPA;
#endif	
}


HC_INTERFACE Key HC_CDECL HC_Style_Segment_Key_By_Key (
	Key			target_segment,
	Key			style_segment) 
{
	_hoops_PAPPR context("Style_Segment_Key_By_Key");

#ifdef DISABLE_STYLE_SEGMENT
	_hoops_IRPPR ("Style_Segment");
	return	_hoops_SHSSR;
#else

	_hoops_RPPPR();
	_hoops_CRCP *	_hoops_IASSI = (_hoops_CRCP *)_hoops_RCSSR (context, style_segment);
	if (_hoops_IASSI == null || _hoops_IASSI->type != _hoops_IRCP || BIT(_hoops_IASSI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_STYLE, HES_INVALID_KEY, "Provided style segment key does not refer to a valid segment");
		_hoops_IRRPR();
		return _hoops_SHSSR;
	}

	_hoops_CRCP *	_hoops_IPAPI = (_hoops_CRCP *)_hoops_RCSSR (context, target_segment);
	if (_hoops_IPAPI == null || _hoops_IPAPI->type != _hoops_IRCP || BIT(_hoops_IPAPI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_STYLE, HES_INVALID_KEY, "Provided target segment key does not refer to a valid segment");
		_hoops_IRRPR();
		return _hoops_SHSSR;
	}

	Key	_hoops_ACHPA = _hoops_PRRGGR (context, null, _hoops_IASSI, null, _hoops_IPAPI, null);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Style_Segment_Key_By_Key (LOOKUP (%D), ", target_segment));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D)), ", style_segment));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	if (_hoops_ACHPA == 0)	/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

	return _hoops_ACHPA;
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Named_Style_Segment (Key style_key, char * style_name)
{
	_hoops_PAPPR context("Show_Named_Style_Segment");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_STYLE_SEGMENT
	_hoops_IRPPR ("Style_Segment");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Named_Style_Segment () */\n");
	);

	_hoops_CSPPR();

	Style *	style = (Style *)_hoops_RCSSR (context, style_key);

	if (style == null || style->type != HK_STYLE || BIT (style->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_STYLE, HES_INVALID_KEY, "Provided key does not refer to a valid style");
		goto _hoops_PRSPR;
	}

	if (style->_hoops_IGRPR != null) {
		HE_ERROR (HEC_STYLE, HES_INVALID_KEY, "Provided key does not refer to a named style");
		goto _hoops_PRSPR;
	}

	HI_Return_Sprintf1 (style_name, -1, "%n", (void *)&style->_hoops_SGAIR);

_hoops_PRSPR:
	_hoops_IRRPR();
#endif
#endif

}


HC_INTERFACE Key HC_CDECL HC_Conditional_Style (
	char const *	name,
	char const *	condition) 
{
	_hoops_PAPPR context("Conditional_Style");

#ifdef DISABLE_STYLE_SEGMENT
	_hoops_IRPPR ("Style_Segment");
#else

	_hoops_RPPPR();
	Key	key = _hoops_PRRGGR (context, name, null, null, null, condition);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "DEFINE (HC_Conditional_Style (%S, %S), ", name, condition));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", key));
	);

	if (key == -1) {
		HE_WARNING (HEC_STYLE, HES_BAD_RETURN_KEY, "Can't return the key - more than one segment was styled");
		return _hoops_SHSSR;
	}
	if (key == 0)		/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

#endif
	return key;
}

HC_INTERFACE Key HC_CDECL HC_Conditional_Style_By_Key (
	Key				key,
	char const *	condition) 
{
	_hoops_PAPPR context("Conditional_Style_By_Key");

#ifdef DISABLE_STYLE_SEGMENT
	_hoops_IRPPR ("Style_Segment");
#else

	_hoops_RPPPR();
	_hoops_CRCP *	_hoops_IASSI = (_hoops_CRCP *)_hoops_RCSSR (context, key);
	if (_hoops_IASSI == null || _hoops_IASSI->type != _hoops_IRCP || BIT(_hoops_IASSI->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_STYLE, HES_INVALID_KEY, "Provided key does not refer to a valid segment");
		_hoops_IRRPR();
		return _hoops_SHSSR;
	}
	Key	_hoops_ACHPA = _hoops_PRRGGR (context, null, _hoops_IASSI, null, null, condition);
	_hoops_IRRPR();

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Conditional_Style_By_Key (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_S	 (null, "%S), ", condition));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_ACHPA));
	);

	if (_hoops_ACHPA == 0)	/* _hoops_PIRC -- _hoops_RIHH _hoops_AIAH _hoops_RAGA */
		return	_hoops_SHSSR;

#endif
	return _hoops_ACHPA;
}


HC_INTERFACE Key HC_CDECL HC_Show_Style_Segment (
	Key			key,
	char *		pathname) 
{
	_hoops_PAPPR context("Show_Style_Segment");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
	return _hoops_SHSSR;
#else
#ifdef DISABLE_STYLE_SEGMENT
	_hoops_IRPPR ("Style_Segment");
	return _hoops_SHSSR;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Style_Segment () */\n");
	);

	_hoops_CSPPR();

	Key _hoops_IAPSA = _hoops_SHSSR;

	Style *	style = (Style *)_hoops_RCSSR (context, key);

	if (style == null || style->type != HK_STYLE || BIT (style->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_STYLE, HES_INVALID_KEY, "Provided key does not refer to a valid style");
		goto _hoops_PRSPR;
	}

	if (style->_hoops_IGRPR == null) {
		HE_ERROR (HEC_STYLE, HES_INVALID_KEY, "Provided key refers to a named style");
		goto _hoops_PRSPR;
	}

	_hoops_IAPSA = style->_hoops_IGRPR->key;

	if (pathname != null)
		HI_Return_Sprintf1 (pathname, -1, "%p", (void *)style->_hoops_IGRPR);

_hoops_PRSPR:
	_hoops_IRRPR();

	return _hoops_IAPSA;
#endif
#endif
}




HC_INTERFACE void HC_CDECL HC_Show_Conditional_Style (
	Key			key,
	char *		pathname,
	char *		condition) 
{
	_hoops_PAPPR context("Show_Conditional_Style");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_STYLE_SEGMENT
	_hoops_IRPPR ("Style_Segment");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Conditional_Style () */\n");
	);

	_hoops_CSPPR();

	Style *	style = (Style *)_hoops_RCSSR (context, key);

	if (style == null || style->type != HK_STYLE || BIT (style->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_STYLE, HES_INVALID_KEY, "Provided key does not refer to a valid style");
		goto _hoops_PRSPR;
	}

	if (style->_hoops_IGRPR == null) {
		HE_ERROR (HEC_STYLE, HES_INVALID_KEY, "Provided key refers to a named style");
		goto _hoops_PRSPR;
	}

	if (pathname)
		HI_Return_Sprintf1 (pathname, -1, "%p", (void *)style->_hoops_IGRPR);

	if (condition)
		HI_Show_Conditional (&style->condition, condition, -1);

_hoops_PRSPR:
	_hoops_IRRPR();

#endif
#endif
}




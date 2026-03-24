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
 * $Id: obf_tmp.txt 1.52 2010-10-06 19:15:59 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "path.h"
#include "searchh.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



local char *_hoops_CCAPR (
	char const		*in,
	char alter		*_hoops_PAGR,
	int				len) {

	_hoops_RGGA (--len < 0) 
		*_hoops_PAGR++ = *in++;
	return _hoops_PAGR;
}


local char *_hoops_SCAPR (void) {
	HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, "Return string won't fit in provided space; truncated");
	return null;
}


local char * _hoops_GSAPR (
	_hoops_RSAPR	*pt,
	char			*_hoops_ASAPR,
	char			*_hoops_PSAPR) {

	do switch (pt->type) {
		case _hoops_HSAPR: {
			if (_hoops_PSAPR - _hoops_ASAPR < 3) return _hoops_SCAPR();
			_hoops_ASAPR = _hoops_CCAPR ("...", _hoops_ASAPR, 3);
		}	break;

		case _hoops_ISAPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = '.';
		}	break;

		case _hoops_CSAPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = '/';
		}	break;

		case _hoops_SSAPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = '%';
		}	break;

		case _hoops_GGPPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = '^';
		}	break;

		case _hoops_RGPPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = '?';
			if (_hoops_PSAPR - _hoops_ASAPR < pt->_hoops_AGPPR.length) return _hoops_SCAPR();
			_hoops_ASAPR = _hoops_CCAPR (pt->_hoops_AGPPR.text, _hoops_ASAPR, pt->_hoops_AGPPR.length);
		}	break;

		case _hoops_PGPPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = '{';
		}	break;

		case _hoops_HGPPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = '}';
		}	break;

		case _hoops_IGPPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = '>';
		}	break;

		case _hoops_CGPPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = '<';
		}	break;

		case _hoops_SGPPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = ',';
		}	break;

		case _hoops_GRPPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = '(';
		}	break;

		case _hoops_RRPPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = ')';
		}	break;

		case _hoops_ARPPR: {
			if (_hoops_PSAPR - _hoops_ASAPR < pt->_hoops_AGPPR.length) return _hoops_SCAPR();
			_hoops_ASAPR = _hoops_CCAPR (pt->_hoops_AGPPR.text, _hoops_ASAPR, pt->_hoops_AGPPR.length);
		}	break;

		case _hoops_PRPPR: {
			if (_hoops_ASAPR == _hoops_PSAPR) return _hoops_SCAPR ();
			*_hoops_ASAPR++ = '*';
		}	break;

		case _hoops_HRPPR: {
			if (_hoops_PSAPR - _hoops_ASAPR < 9) return _hoops_SCAPR();
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%k", (void *)&pt->key);
		}	break;

		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Undefined path token type");
			return null;
		}	/* _hoops_IHSA; */
	}
	_hoops_RGGA ((pt = pt->next) == null);

	return _hoops_ASAPR;
}



GLOBAL_FUNCTION void HI_Show_Alias (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			alias,
	char *					_hoops_ASAPR,
	int						length) 
{

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else

	if (*alias != '?') {
		HE_ERROR (HEC_ALIAS, HES_BEGINS_WITH_QUESTION_MARK, "Alias name must begin with a ?");
		return;
	}

	_hoops_RSAPR	*pt;
	if ((pt = HI_Parse_Path (_hoops_RIGC,  alias, false)) == null) {
		/* _hoops_RIHH - _hoops_AHCI _hoops_RSIRR (_hoops_AIAH _hoops_CRPPR) */
		return;
	}

	if (pt->next != null || pt->type != _hoops_RGPPR) {
		HE_ERROR (HEC_ALIAS, HES_INVALID_INPUT, Sprintf_S (null, "'%s' is not a legal alias name", alias));
		HI_Free_Path (pt);
		return;
	}
	
	_hoops_SRPPR **	_hoops_GAPPR = HI_Look_Up_Alias (_hoops_RIGC, pt->_hoops_AGPPR.text, pt->_hoops_AGPPR.length);
	HI_Free_Path (pt);
	if (*_hoops_GAPPR == null) {
		HE_ERROR (HEC_ALIAS, HES_INVALID_INPUT, "Alias not defined");
		return;
	}

	char *	_hoops_PSAPR;

	if (length == -1) 
		_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR - 1;
	else 
		_hoops_PSAPR = _hoops_ASAPR + length;

	_hoops_ASAPR = _hoops_GSAPR ((*_hoops_GAPPR)->_hoops_AAPPR, _hoops_ASAPR, _hoops_PSAPR);

	if (length == -1) *_hoops_ASAPR = '\0';
	else {
		if (_hoops_ASAPR != null && _hoops_ASAPR != _hoops_PSAPR) {
			do *_hoops_ASAPR++ = ' ';
			_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR);
		}
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Alias (
	char const *	alias,
	char *			expansion) 
{
	_hoops_PAPPR context("Show_Alias");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Alias () */\n");
	);

	HI_Show_Alias (context, alias, expansion, -1);
}




HC_INTERFACE void HC_CDECL HC_Define_Alias (
	char const *	iname,
	char const *	definition) 
{
	_hoops_PAPPR context("Define_Alias");

	/* _hoops_ASC _hoops_PGCR _hoops_APGR _hoops_ARPP _hoops_HAPPR _hoops_GPP _hoops_AHAR, _hoops_IAPPR?*/
	bool	_hoops_CAPPR = !BIT (HOOPS_WORLD->_hoops_SAPPR, _hoops_GPPPR);
	HOOPS_WORLD->_hoops_SAPPR |= _hoops_GPPPR;

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Define_Alias (%S, %S);\n", iname, definition));
	);

	_hoops_RPPPR();

	_hoops_RSAPR *	name;
	_hoops_SRPPR ** 		_hoops_GAPPR;
	_hoops_RSAPR *	path;
	_hoops_SRPPR *			alias;

	if ((name = HI_Parse_Path (context, iname, false)) == null) {
		/* _hoops_RIHH - _hoops_AHCI _hoops_RSIRR (_hoops_AIAH _hoops_CRPPR) */
		goto _hoops_APPPR;
	}

	if (name->next != null || name->type != _hoops_RGPPR) {
		HE_ERROR (HEC_ALIAS, HES_INVALID_INPUT, Sprintf_S (null, "'%s' is not a legal alias name", iname));
		HI_Free_Path (name);
		goto _hoops_APPPR;
	}

	
	_hoops_GAPPR = HI_Look_Up_Alias (context, name->_hoops_AGPPR.text, name->_hoops_AGPPR.length);
	if (*_hoops_GAPPR != null) {
		/* _hoops_SR _hoops_HS _hoops_SPR, _hoops_HIH _hoops_SR _hoops_PPPPR'_hoops_RA _hoops_HPPPR _hoops_RPP _hoops_RGR _hoops_AASA _hoops_IS _hoops_IPPPR
		 * _hoops_PHPP _hoops_IS _hoops_SHH _hoops_RH _hoops_CPPPR _hoops_SRS _hoops_AHAP _hoops_GGR _hoops_RH _hoops_SPPPR (_hoops_PSP _hoops_GHPPR
		 * _hoops_IH _hoops_RHPPR _hoops_PCCP _hoops_AHPPR _hoops_PHPPR _hoops_RPP _hoops_RGR _hoops_PCPH _hoops_HHPPR _hoops_SCH!).
		 * _hoops_SAGAR, _hoops_SR _hoops_GRS _hoops_HSCI _hoops_GII _hoops_CAGH _hoops_SGS _hoops_CSAP _hoops_IHPPR _hoops_SPIP
		 * _hoops_IH _hoops_SGS _hoops_CIH _hoops_PHPPR.
		 */
		if (_hoops_CAPPR) {

			_hoops_CRCP *		_hoops_SRCP;

			if ((_hoops_SRCP = HI_One_Segment_Search (context, iname, true)) != null) {
				/* _hoops_CHPPR _hoops_SHPPR _hoops_HRGR _hoops_PAHH _hoops_ICIC _hoops_ARI, _hoops_CR _hoops_SR _hoops_SAHR
				 * _hoops_SPIP _hoops_RGR, _hoops_HIH _hoops_RH _hoops_IHH _hoops_HCGC _hoops_GA'_hoops_RA _hoops_GIPPR
				 */
				HI_Delete_Segment (context, _hoops_SRCP, null);
			}
		}
		else {
			HE_WARNING (HEC_ALIAS, HES_REDEFINING_NAME,
					Sprintf_N (null,"Re-defining existing alias '?%n'", &name->_hoops_AGPPR));
		}

		HI_Generic_Delete (context,(_hoops_HPAH *)*_hoops_GAPPR);

		/* (_hoops_SAHR _hoops_GGR _hoops_AGIR _hoops_CPHP _hoops_RIPPR...) */
		_hoops_GAPPR = HI_Look_Up_Alias (context, name->_hoops_AGPPR.text, name->_hoops_AGPPR.length);
	}

	if ((path = HI_Parse_Path (context, definition, _hoops_AIPPR|QUALIFIERS)) == null) {
		/* _hoops_RIHH - _hoops_AHCI _hoops_CRAA (_hoops_AIAH _hoops_CRPPR) */
		HI_Free_Path (name);
		goto _hoops_APPPR;
	}

	/* _hoops_SCH _hoops_CHH _hoops_SHH _hoops_AGAPR _hoops_IS _hoops_PIPPR _hoops_ISPR _hoops_RH _hoops_CRAA _hoops_HAH, _hoops_HIH _hoops_HIPPR... */

	ZALLOC (alias, _hoops_SRPPR);
	alias->_hoops_HIHI = 1;
	alias->type = _hoops_IIPPR;
	alias->owner = HOOPS_WORLD;
	alias->_hoops_AAPPR = path;
	if ((alias->next = *_hoops_GAPPR) != null) (*_hoops_GAPPR)->backlink = &alias->next;
	*_hoops_GAPPR = alias;
	alias->backlink = _hoops_GAPPR;
	alias->_hoops_AAPPR = path;

	/* _hoops_SRAI _hoops_RH _hoops_RSIRR */
	alias->name.text = name->_hoops_AGPPR.text;
	alias->name.length = name->_hoops_AGPPR.length;
	FREE (name, _hoops_RSAPR);

	{	_hoops_RSAPR	*_hoops_CIPPR = path;
		int				_hoops_SIPPR = 0;

		do switch (_hoops_CIPPR->type) {
			case _hoops_GRPPR:	++_hoops_SIPPR;		break;
			case _hoops_RRPPR:	--_hoops_SIPPR;		break;

			case _hoops_PGPPR:
			case _hoops_HGPPR:
			case _hoops_IGPPR:
			case _hoops_CGPPR:
			case _hoops_SGPPR: {
				if (_hoops_SIPPR == 0) {
					/* _hoops_RSPH _hoops_HHH _hoops_GCPPR _hoops_CGS _hoops_IS _hoops_GHSGR _hoops_RCPPR */

					_hoops_RGGA (_hoops_CIPPR->next == null) _hoops_CIPPR = _hoops_CIPPR->next;

					ALLOC (_hoops_CIPPR->next, _hoops_RSAPR);
					_hoops_CIPPR->next->type = _hoops_RRPPR;
					_hoops_CIPPR->next->next = null;

					ALLOC (_hoops_CIPPR, _hoops_RSAPR);
					_hoops_CIPPR->type = _hoops_GRPPR;
					_hoops_CIPPR->next = alias->_hoops_AAPPR;
					alias->_hoops_AAPPR = _hoops_CIPPR;
					alias->_hoops_RRHH |= _hoops_ACPPR;
					goto _hoops_PCPPR;
				}
			}	break;
		}
		_hoops_RGGA ((_hoops_CIPPR = _hoops_CIPPR->next) == null);
		_hoops_PCPPR:;
	}


_hoops_APPPR:
	_hoops_IRRPR();

	if (_hoops_CAPPR) {
		/* _hoops_HCPPR _hoops_RH _hoops_ICPPR _hoops_HII _hoops_CCPPR */
		PUSHNAME(context);
		HI_Set_Name ("Hoops Startup (internal)");
		HOOPS_WORLD->_hoops_SAPPR &= ~_hoops_GPPPR;
		HI_Interpret_Environment (context, true);
		POPNAME(context);
	}
}


HC_INTERFACE void HC_CDECL HC_UnDefine_Alias (
	char const *	iname) 
{
	_hoops_PAPPR context("UnDefine_Alias");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnDefine_Alias (%S);\n", iname));
	);

	_hoops_RSAPR *	name;

	if ((name = HI_Parse_Path (context, iname, false)) == null) {
		/* _hoops_RIHH - _hoops_AHCI _hoops_RSIRR (_hoops_AIAH _hoops_CRPPR) */
		return;
	}

	if (name->next != null || name->type != _hoops_RGPPR) {
		HE_ERROR (HEC_ALIAS, HES_INVALID_INPUT, Sprintf_S (null, "'%s' is not a legal alias name", iname));
		HI_Free_Path (name);
		return;
	}

	_hoops_RPPPR();
	_hoops_SRPPR *	alias = *HI_Look_Up_Alias (context, name->_hoops_AGPPR.text, name->_hoops_AGPPR.length);

	if (alias == null) {
		HE_WARNING (HEC_ALIAS, HES_INVALID_INPUT,
				Sprintf_N (null, "Alias '%n' not currently defined - can't UnDefine", &name->_hoops_AGPPR));
	}
	else
		HI_Generic_Delete (context,(_hoops_HPAH *)alias);

	_hoops_IRRPR();

	HI_Free_Path (name);
}


GLOBAL_FUNCTION _hoops_SRPPR ** HI_Look_Up_Alias (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	int						length) {
	int						_hoops_SCPPR;
	char const *			_hoops_RPPA;
	char const *			_hoops_GSPPR;
	_hoops_SRPPR **				_hoops_GAPPR,
							*al;
	int						_hoops_GCAH = 0;
	
	if ((_hoops_GAPPR = _hoops_RSPPR(_hoops_RIGC, _hoops_ASPPR)) == null) {
		ZALLOC_ARRAY (_hoops_GAPPR, _hoops_PSPPR, _hoops_SRPPR *);
		_hoops_RSPPR(_hoops_RIGC, _hoops_ASPPR) = _hoops_GAPPR;
	}

	_hoops_RPPA = name;
	_hoops_SCPPR = length;
	do _hoops_GCAH += (int)*_hoops_RPPA++;
	_hoops_RGGA (--_hoops_SCPPR == 0);

	/*** _hoops_PGCR'_hoops_GRI _hoops_HSPPR _hoops_RGAR! ***/
	_hoops_GAPPR += _hoops_GCAH & (_hoops_PSPPR - 1);

	while ((al = *_hoops_GAPPR) != null) {
		if (al->name.length == length) {
			_hoops_SCPPR = length;
			_hoops_RPPA = name;
			_hoops_GSPPR = al->name.text;
			while (*_hoops_RPPA++ == *_hoops_GSPPR++)
				if (--_hoops_SCPPR == 0)
					return _hoops_GAPPR;
		}

		_hoops_GAPPR = &al->next;
	}

	return _hoops_GAPPR;
}




HC_INTERFACE void HC_CDECL HC_Begin_Alias_Search (void) 
{
	_hoops_PAPPR context("Begin_Alias_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Alias_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_CSPPR();

	_hoops_SRPPR **	_hoops_GAPPR = _hoops_RSPPR(context, _hoops_ASPPR);
	if (_hoops_GAPPR == null) {
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Alias hash table missing");
		return;
	}

	_hoops_SSPPR *	_hoops_GGHPR;
	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = context->_hoops_RGHPR;
	context->_hoops_RGHPR = _hoops_GGHPR;

	int count = _hoops_PSPPR;
	do {
		_hoops_SRPPR *	alias;
		if ((alias = *_hoops_GAPPR) != null) do {
			_hoops_AGHPR *	node;
			ZALLOC (node, _hoops_AGHPR);
			node->next = _hoops_GGHPR->list;
			_hoops_GGHPR->list = node;
			node->item = (_hoops_HPAH *)alias;
			_hoops_PRRH (alias);
			++_hoops_GGHPR->count;
		} while ((alias = alias->next) != null);
		++_hoops_GAPPR;
	}
	_hoops_RGGA (--count == 0);

	_hoops_IRRPR();
#endif
}


GLOBAL_FUNCTION bool HI_Find_Alias (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					alias,
	int						length) 
{

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else

	if (_hoops_RIGC->_hoops_RGHPR == null) {
		HE_ERROR (HEC_ALIAS, HES_INACTIVE_SEARCH, "No alias search is active");
		return false;
	}

	_hoops_AGHPR	*	list;

	while ((list = _hoops_RIGC->_hoops_RGHPR->list) != null) {
		_hoops_SRPPR *		item = (_hoops_SRPPR *)list->item;

		_hoops_RIGC->_hoops_RGHPR->list = list->next;
		FREE (list, _hoops_AGHPR);

/* _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_PGHPR */
		if (!BIT (item->_hoops_RRHH, _hoops_HGAGR)) {
			HI_Return_Sprintf1 (alias, length, "?%n", (void *)&item->name);
			_hoops_HPRH (item);
			return true;
		}
		else
			_hoops_HPRH (item);
	}

#endif
	return false;
}


HC_INTERFACE bool HC_CDECL HC_Find_Alias (
	char *	alias) 
{
	_hoops_PAPPR context("Find_Alias");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Alias () */\n");
	);

	return HI_Find_Alias (context, alias, -1);
}


HC_INTERFACE void HC_CDECL HC_Show_Alias_Count (
	int						*count) 
{
	_hoops_PAPPR context("Show_Alias_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Alias_Count () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_RGHPR;
	if (_hoops_GGHPR == null) {
		*count = 0;
		HE_ERROR (HEC_ALIAS, HES_INACTIVE_SEARCH, "No alias search is active");
	}
	else 
		*count = _hoops_GGHPR->count;
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Alias_Search (void) 
{
	_hoops_PAPPR context("End_Alias_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Alias_Search () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_RGHPR;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_ALIAS, HES_END_WITHOUT_BEGIN_SEARCH, "End without Begin");
		return;
	}

	HI_Free_Search_List (context, _hoops_GGHPR->list);

	context->_hoops_RGHPR = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
}




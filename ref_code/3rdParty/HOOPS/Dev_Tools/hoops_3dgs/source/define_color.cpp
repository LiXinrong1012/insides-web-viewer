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
 * $Id: obf_tmp.txt 1.79 2010-10-06 19:15:59 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "searchh.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_COLOR_NAMES

local void HC_CDECL _hoops_SPHPP (
	char const      *ref,
	int             _hoops_SCPPR,
	_hoops_HCRPR         *_hoops_PAGR) {

	if (_hoops_SCPPR == 0) {
		_hoops_PAGR->length = 0;
		_hoops_PAGR->text = null;
	}
	else {
		char            *_hoops_AHSCA;

		ALLOC_ARRAY (_hoops_AHSCA, _hoops_SCPPR+1, char);
		_hoops_PAGR->length = _hoops_SCPPR;
		_hoops_PAGR->text = _hoops_AHSCA;

		do *_hoops_AHSCA++ = *ref++;
		_hoops_RGGA (--_hoops_SCPPR == 0);
		*_hoops_AHSCA = '\0';
	}
}


local bool _hoops_GHHPP (
	_hoops_HCRPR			*name) {

	if (!(_hoops_RHHPP (*name->text) >= _hoops_RHHPP ('a') &&
		  _hoops_RHHPP (*name->text) <= _hoops_RHHPP ('z') ||
		  _hoops_RHHPP (*name->text) >= _hoops_RHHPP ('A') &&
		  _hoops_RHHPP (*name->text) <= _hoops_RHHPP ('Z'))
#ifdef _MSC_VER
#	pragma warning(disable: 4310)	// _hoops_HIIC _hoops_AHHPP _hoops_SRSR _hoops_PIRA
#endif
			&& !(_hoops_IRGCR(*name->text) >= 0XC0 /* _hoops_PHHPP, _hoops_SRS _hoops_HHHPP-1 _hoops_IHHPP */ &&
				 *name->text != (char)0XD7 /* _hoops_IACH */ &&
				 *name->text != (char)0XF7 /* _hoops_RIPI-_hoops_HPP */)


												   ) {
		HE_ERROR (HEC_COLOR, HES_INVALID_INPUT,
				Sprintf_N (null, "Name-to-be-defined '%n' does not begin with a letter",
			name));
		_hoops_RGAIR (*name);
		return false;
	}
	return true;
}


local void _hoops_CHHPP (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_SCHIR *				_hoops_SHHPP,
	_hoops_HCRPR *					name,
	int						degree) {
	_hoops_RSHIR *			_hoops_ICHIR,
							**_hoops_ASRGR;

	_hoops_ASRGR = HI_Look_Up_Color (_hoops_RIGC, name->text, name->length);
	if (*_hoops_ASRGR != null) {
		if ((*_hoops_ASRGR)->_hoops_AAPPR == _hoops_SHHPP) {
			/* _hoops_ASRHR: _hoops_ARSSR _hoops_RH _hoops_PSHR _hoops_RSIRR _hoops_RRPC _hoops_GGR _hoops_RH _hoops_PSHR _hoops_IAGC */
			_hoops_RGAIR (*name);
			return;
		}
		else {
			HE_WARNING (HEC_COLOR, HES_REDEFINING_NAME,
					Sprintf_N (null, "Re-defining '%n'", name));
			HI_Generic_Delete (_hoops_RIGC,(_hoops_HPAH *)(*_hoops_ASRGR)->_hoops_AAPPR);
		}

		_hoops_ASRGR = HI_Look_Up_Color (_hoops_RIGC, name->text, name->length);
	}

	ALLOC (_hoops_ICHIR, _hoops_RSHIR);
	_hoops_ICHIR->next = _hoops_SHHPP->_hoops_HSHIR;
	_hoops_SHHPP->_hoops_HSHIR = _hoops_ICHIR;
	_hoops_ICHIR->degree = degree;
	_hoops_ICHIR->_hoops_AAPPR = _hoops_SHHPP;
	_hoops_ICHIR->name.length = name->length;
	_hoops_ICHIR->name.text = name->text;
	*_hoops_ASRGR = _hoops_ICHIR;
	_hoops_ICHIR->_hoops_SSCAP = null;
	_hoops_ICHIR->_hoops_GGSAP = _hoops_ASRGR;
}


local bool _hoops_GIHPP (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_SCHIR *				_hoops_SHHPP,
	char const *			innames,
	int						degree) {
	_hoops_HCRPR					name, _hoops_HGPIR;
	int						start, end;

	HI_Canonize_Chars_Quoted (innames, &_hoops_HGPIR, false);

	if (_hoops_HGPIR.length == 0) 
		return true;

	end = 0;
	_hoops_PCCAR {
		while (end < _hoops_HGPIR.length && _hoops_HGPIR.text[end] == ' ') end++;
		start = end;
		while (end < _hoops_HGPIR.length && _hoops_HGPIR.text[end] != ',') end++;
		if (end > start) {
			_hoops_SPHPP (_hoops_HGPIR.text + start, end - start, &name);
			if (!_hoops_GHHPP (&name)) {
				_hoops_RGAIR (name);
				_hoops_RGAIR (_hoops_HGPIR);
				return false;
			}
			_hoops_CHHPP (_hoops_RIGC, _hoops_SHHPP, &name, degree);
			if (end == _hoops_HGPIR.length)
				break;
			end++;
		}
	}
	_hoops_RGAIR (_hoops_HGPIR);
	return true;
}
#endif


HC_INTERFACE void HC_CDECL HC_Define_Color_Name (
	char const *		_hoops_SHGCR,
	char const *		first,
	char const *		_hoops_IAGRA,
	char const *		definition) 
{
	_hoops_PAPPR context("Define_Color_Name");

#ifdef DISABLE_COLOR_NAMES
	_hoops_IRPPR ("Color Names");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Define_Color_Name (%S, %S, ", _hoops_SHGCR, first));
		HI_Dump_Code (Sprintf_SS (null, "%S, %S);\n", _hoops_IAGRA, definition));
	);

	Named_Material		_hoops_ISHIR;
	_hoops_SCHIR *			_hoops_SHHPP;
	_hoops_HCRPR				_hoops_CRPCR;
	bool				_hoops_RIHPP;

	HI_Canonize_Chars_Quoted (definition, &_hoops_CRPCR, false);

	ZERO_STRUCT (&_hoops_ISHIR, Named_Material);
	if (!HI_Evaluate_Color (context, &_hoops_CRPCR, &_hoops_ISHIR, 0, true)) {
		_hoops_RGAIR (_hoops_CRPCR);
		return;
	}
	_hoops_ISHIR._hoops_PRGRA &= ~_hoops_PSARA;

	/* (_hoops_HCR _hoops_GPRS) */

	ZALLOC (_hoops_SHHPP, _hoops_SCHIR);
	_hoops_SHHPP->_hoops_HIHI = 1;
	_hoops_SHHPP->type = _hoops_CCHIR;
	_hoops_SHHPP->owner = HOOPS_WORLD;
	_hoops_SHHPP->backlink = &_hoops_RSPPR(context, _hoops_AIHPP);
	if ((_hoops_SHHPP->next = _hoops_RSPPR(context, _hoops_AIHPP)) != null)
		_hoops_RSPPR(context, _hoops_AIHPP)->backlink = &_hoops_SHHPP->next;
	_hoops_RSPPR(context, _hoops_AIHPP) = _hoops_SHHPP;
	HI_Copy_Named_Material (&_hoops_ISHIR, &_hoops_SHHPP->_hoops_ISHIR);
	HI_Free_Material_Names (&_hoops_ISHIR, 1);
	/* _hoops_SRAI _hoops_PIHPP */
	_hoops_RSAI (&_hoops_CRPCR, _hoops_HCRPR, &_hoops_SHHPP->definition);

	_hoops_RPPPR();
	_hoops_RIHPP = !_hoops_GIHPP (context, _hoops_SHHPP, _hoops_SHGCR, _hoops_RGGPP) ||
			  !_hoops_GIHPP (context, _hoops_SHHPP, first, _hoops_AGGPP) ||
			  !_hoops_GIHPP (context, _hoops_SHHPP, _hoops_IAGRA, _hoops_PGGPP);
	_hoops_IRRPR();

	if (_hoops_RIHPP || _hoops_SHHPP->_hoops_HSHIR == null) {
		if (_hoops_SHHPP->_hoops_HSHIR == null)
			HE_WARNING (HEC_COLOR, HES_NULL_INPUT, "No names - at all - specified.");

		_hoops_RPPPR();
		HI_Generic_Delete (context,(_hoops_HPAH *)_hoops_SHHPP);
		_hoops_IRRPR();
	}

	HI_Flush_Color_Material_Lookup(&_hoops_RSPPR(context, _hoops_HIHPP));
#endif
}




struct _hoops_IIHPP {
	struct _hoops_IIHPP		*next;
	_hoops_SCHIR		*_hoops_GSHIR;
};



GLOBAL_FUNCTION void HI_UnDefine_Color_Name (
	_hoops_AIGPR *_hoops_RIGC,
	char const *		innames) {
	_hoops_HCRPR				_hoops_HGPIR;
	char *				_hoops_RPPA,*_hoops_CIHPP,*_hoops_SIHPP;
	_hoops_RSHIR *		_hoops_GCHPP;

	HI_Canonize_Chars_Quoted (innames, &_hoops_HGPIR, false);

	_hoops_CIHPP = _hoops_RPPA = _hoops_HGPIR.text;
	_hoops_SIHPP = _hoops_CIHPP + _hoops_HGPIR.length;

	do if (*_hoops_RPPA++ == ',') break;
	_hoops_RGGA (_hoops_RPPA == _hoops_SIHPP);

	_hoops_RPPPR();
	if (_hoops_RPPA == _hoops_SIHPP) {
		/* _hoops_RGAR _hoops_SPR _hoops_RSIRR _hoops_IS _hoops_RCHPP */
		if ((_hoops_GCHPP = *HI_Look_Up_Color (_hoops_RIGC, _hoops_CIHPP, _hoops_HGPIR.length)) == null) {
			HE_WARNING (HEC_COLOR, HES_INVALID_INPUT,
					Sprintf_N (null,
						"Color name not found in '%n'", &_hoops_HGPIR));
		}
		else {
			HI_Generic_Delete (_hoops_RIGC,(_hoops_HPAH *)_hoops_GCHPP->_hoops_AAPPR);
			HI_Flush_Color_Material_Lookup(&_hoops_RSPPR(_hoops_RIGC, _hoops_HIHPP));
		}
	}
	else {
		/* _hoops_ACIPR _hoops_AGIR: _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_IS _hoops_SHH _hoops_ACHPP */

		/* _hoops_RPP _hoops_PGCR _hoops_RPPCR _hoops_IH _hoops_RH _hoops_PSHR _hoops_AHAP _hoops_CHR _hoops_CHIA, _hoops_SGS'_hoops_GRI _hoops_GPRS -
		 * _hoops_HIS _hoops_SR _hoops_PAH'_hoops_RA _hoops_AA _hoops_HSCI _hoops_CCGR _hoops_RAS _hoops_SPAAR _hoops_HRGR _hoops_CPHR */

		struct _hoops_IIHPP			*_hoops_PCHPP = null, *_hoops_HCHPP;
		--_hoops_RPPA;

		_hoops_PCCAR {
			int				_hoops_ICHPP = _hoops_RPPA - _hoops_CIHPP;

			if (_hoops_ICHPP > 0 && _hoops_RPPA[-1] == ' ') --_hoops_ICHPP;

			if (_hoops_ICHPP == 0) {
				HE_WARNING (HEC_COLOR, HES_NULL_INPUT,
						"The color name is blank");
			}
			else if ((_hoops_GCHPP = *HI_Look_Up_Color (_hoops_RIGC, _hoops_CIHPP, _hoops_ICHPP)) == null) {
				HE_WARNING (HEC_COLOR, HES_INVALID_INPUT,
						Sprintf_N (null,
							"Color name not found in '%n'", &_hoops_HGPIR));
			}
			else {
				if ((_hoops_HCHPP = _hoops_PCHPP) != null) do {
					if (_hoops_HCHPP->_hoops_GSHIR == _hoops_GCHPP->_hoops_AAPPR) break;
				}
				_hoops_RGGA ((_hoops_HCHPP = _hoops_HCHPP->next) == null);

				if (_hoops_HCHPP == null) {	/* _hoops_HAR _hoops_AIAH _hoops_GPP _hoops_HIGR */
					ALLOC (_hoops_HCHPP, struct _hoops_IIHPP);
					_hoops_HCHPP->_hoops_GSHIR = _hoops_GCHPP->_hoops_AAPPR;
					_hoops_HCHPP->next = _hoops_PCHPP;
					_hoops_PCHPP = _hoops_HCHPP;
				}
			}

			if (++_hoops_RPPA > _hoops_SIHPP) break;

			if (*_hoops_RPPA == ' ') ++_hoops_RPPA;
			_hoops_CIHPP = _hoops_RPPA;
			while (_hoops_RPPA < _hoops_SIHPP && *_hoops_RPPA != ',') ++_hoops_RPPA;
		}

		if (_hoops_PCHPP != null) {
			
			HI_Flush_Color_Material_Lookup(&_hoops_RSPPR(_hoops_RIGC, _hoops_HIHPP));

			_hoops_RGGA ((_hoops_HCHPP = _hoops_PCHPP) == null) {
				_hoops_PCHPP = _hoops_HCHPP->next;
				HI_Generic_Delete (_hoops_RIGC,(_hoops_HPAH *)_hoops_HCHPP->_hoops_GSHIR);
				FREE (_hoops_HCHPP, struct _hoops_IIHPP);
			}
		}
	}
	_hoops_IRRPR();

	_hoops_RGAIR (_hoops_HGPIR);
}


HC_INTERFACE void HC_CDECL HC_UnDefine_Color_Name (
	char const *		innames) 
{
	_hoops_PAPPR context("UnDefine_Color_Name");

#ifdef DISABLE_COLOR_NAMES
	_hoops_IRPPR ("Color Names");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnDefine_Color_Name (%S);\n", innames));
	);
	
	HI_UnDefine_Color_Name (context, innames);
#endif
}





GLOBAL_FUNCTION _hoops_RSHIR ** HI_Look_Up_Color (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	int						length) {
	int						_hoops_SCPPR;
	char const *			_hoops_RPPA;
	char const *			_hoops_GSPPR;
	_hoops_RSHIR **			_hoops_CCHPP, *_hoops_ASHIR;
	int						_hoops_GCAH = 0;
	int						id;
	
	id = _hoops_RIGC->_hoops_IAPCR;

	if (length == 0) {
		HE_ERROR (HEC_COLOR, HES_NULL_INPUT,
				"Color name is blank or null");
		return null;
	}

	if ((_hoops_CCHPP = _hoops_RSPPR(_hoops_RIGC, _hoops_SCHPP)) == null) {
		ZALLOC_ARRAY (_hoops_CCHPP, _hoops_GSHPP, _hoops_RSHIR *);
		_hoops_RSPPR(_hoops_RIGC, _hoops_SCHPP) = _hoops_CCHPP;
	}

	_hoops_RPPA = name;
	_hoops_SCPPR = length;
	do _hoops_GCAH += (int)*_hoops_RPPA++;
	_hoops_RGGA (--_hoops_SCPPR == 0);

	/*** _hoops_PGCR'_hoops_GRI _hoops_HSPPR _hoops_RGAR! ***/
	_hoops_CCHPP += _hoops_GCAH & (_hoops_GSHPP - 1);

	_hoops_RGGA ((_hoops_ASHIR = *_hoops_CCHPP) == null) {
		if (_hoops_ASHIR->name.length == length) {
			_hoops_SCPPR = length;
			_hoops_RPPA = name;
			_hoops_GSPPR = _hoops_ASHIR->name.text;
			while (*_hoops_RPPA++ == *_hoops_GSPPR++) if (--_hoops_SCPPR == 0) return _hoops_CCHPP;
		}

		_hoops_CCHPP = &_hoops_ASHIR->_hoops_SSCAP;
	}

	return _hoops_CCHPP;
}




GLOBAL_FUNCTION void HI_Show_Color_Name (
	char const *	string,
	char *			_hoops_AAPPR,
	int				len) 
{
	_hoops_PAPPR context("Show_Color_Name");

#ifdef DISABLE_COLOR_NAMES
	_hoops_IRPPR ("Color Names");
#else

	_hoops_RSHIR	*	_hoops_RSHPP;
	_hoops_HCRPR			name;

	HI_Canonize_Chars_Quoted (string, &name, false);

	_hoops_CSPPR();
	_hoops_RSHPP = *HI_Look_Up_Color (context, name.text, name.length);
	_hoops_IRRPR();

	if (_hoops_RSHPP == null) {
		HE_ERROR (HEC_COLOR, HES_NULL_INPUT, "No definition for color");
	}
	else {
		HI_Return_Sprintf1 (_hoops_AAPPR, len, "%n", (void *)&_hoops_RSHPP->_hoops_AAPPR->definition);
	}
	_hoops_RGAIR(name);
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Color_Name (
	char const		*string,
	char			*_hoops_AAPPR) {

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Color_Name () */\n");
	);

	HI_Show_Color_Name (string, _hoops_AAPPR, -1);
}



HC_INTERFACE void HC_CDECL HC_Begin_Color_Name_Search (void) 
{
	_hoops_PAPPR context("Begin_Color_Name_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Color_Name_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_SSPPR *		_hoops_GGHPR;
	_hoops_SCHIR *			_hoops_ASHPP;
	_hoops_AGHPR *		node;

	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = context->_hoops_PSHPP;
	context->_hoops_PSHPP = _hoops_GGHPR;

	_hoops_CSPPR();

	_hoops_ASHPP = _hoops_RSPPR(context, _hoops_AIHPP);
	if (_hoops_ASHPP != null) do {
		ZALLOC (node, _hoops_AGHPR);
		node->next = _hoops_GGHPR->list;
		_hoops_GGHPR->list = node;
		node->item = (_hoops_HPAH *)_hoops_ASHPP;
		_hoops_PRRH (_hoops_ASHPP);
		++_hoops_GGHPR->count;
	} while ((_hoops_ASHPP = _hoops_ASHPP->next) != null);

	_hoops_IRRPR();
#endif
}


GLOBAL_FUNCTION bool HI_Find_Color_Name (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					_hoops_ASAPR,
	int						_hoops_HSHPP,
	char *					_hoops_HCHPR,
	int						_hoops_ISHPP,
	char *					_hoops_CSHPP,
	int						_hoops_SSHPP) 
{
	
#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else

	_hoops_AGHPR	*	list;
	int				_hoops_GGIPP = 0, _hoops_RGIPP = 0, _hoops_AGIPP = 0;
	char			*_hoops_PSAPR, *_hoops_PGIPP, *_hoops_RASGR;

	if (_hoops_RIGC->_hoops_PSHPP == null) {
		HE_ERROR (HEC_COLOR, HES_INACTIVE_SEARCH, "No color search is active");
		return false;
	}
	if (_hoops_HSHPP == -1) _hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR - 1;
		else _hoops_PSAPR = _hoops_ASAPR + _hoops_HSHPP;
	if (_hoops_ISHPP == -1) _hoops_PGIPP = _hoops_HCHPR + HOOPS_WORLD->_hoops_RAPPR - 1;
		else _hoops_PGIPP = _hoops_HCHPR + _hoops_ISHPP;
	if (_hoops_SSHPP == -1) _hoops_RASGR = _hoops_CSHPP + HOOPS_WORLD->_hoops_RAPPR - 1;
		else _hoops_RASGR = _hoops_CSHPP + _hoops_SSHPP;

	if ((list = _hoops_RIGC->_hoops_PSHPP->list) != null) {
		_hoops_SCHIR	*item = (_hoops_SCHIR *)list->item;
		_hoops_RSHIR	*color;

		_hoops_RIGC->_hoops_PSHPP->list = list->next;
		FREE (list, _hoops_AGHPR);
		while (BIT (item->_hoops_RRHH, _hoops_HGAGR)) {
			_hoops_HPRH (item);
			if ((list = _hoops_RIGC->_hoops_PSHPP->list) == null)
				return false;
			item = (_hoops_SCHIR *)list->item;
			_hoops_RIGC->_hoops_PSHPP->list = list->next;
			FREE (list, _hoops_AGHPR);
		}

		if ((color = item->_hoops_HSHIR) != null) do {
			switch (color->degree) {
				case (_hoops_RGGPP):
					if (_hoops_GGIPP == 0) {
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%qn", (void *)&color->name);
						_hoops_GGIPP = 1;
					}
					else if (_hoops_GGIPP == 1)
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, ", %qn", (void *)&color->name);

					if (_hoops_ASAPR == null) {
						HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW,
								  "Base color(s) will not fit in provided buffer - truncated");
						_hoops_ASAPR = _hoops_PSAPR;
						_hoops_GGIPP = -1;
					}
					break;
				case (_hoops_AGGPP):
					if (_hoops_RGIPP == 0) {
						_hoops_HCHPR = HI_Sprintf1 (_hoops_HCHPR, _hoops_PGIPP, "%qn", (void *)&color->name);
						_hoops_RGIPP = 1;
					}
					else if (_hoops_RGIPP == 1)
						_hoops_HCHPR = HI_Sprintf1 (_hoops_HCHPR, _hoops_PGIPP, ", %qn", (void *)&color->name);

					if (_hoops_HCHPR == null) {
						HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW,
								  "First Degree color(s) will not fit in provided buffer - truncated");
						_hoops_HCHPR = _hoops_PGIPP;
						_hoops_RGIPP = -1;
					}
					break;
				case (_hoops_PGGPP):
					if (_hoops_AGIPP == 0) {
						_hoops_CSHPP = HI_Sprintf1 (_hoops_CSHPP, _hoops_RASGR, "%qn", (void *)&color->name);
						_hoops_AGIPP = 1;
					}
					else if (_hoops_AGIPP == 1)
						_hoops_CSHPP = HI_Sprintf1 (_hoops_CSHPP, _hoops_RASGR, ", %qn", (void *)&color->name);

					if (_hoops_CSHPP == null) {
						HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW,
								  "Second Degree color(s) will not fit in provided buffer - truncated");
						_hoops_CSHPP = _hoops_RASGR;
						_hoops_AGIPP = -1;
					}
					break;
				default:
					_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Bad degree");
					break;
			}
		} while ((color = color->next) != null);

		if (_hoops_GGIPP != -1) {
			if (_hoops_HSHPP == -1) *_hoops_ASAPR = '\0';
			else if (_hoops_ASAPR != _hoops_PSAPR) {
				do *_hoops_ASAPR++ = ' ';
				_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR);
			}
		}
		if (_hoops_RGIPP != -1) {
			if (_hoops_ISHPP == -1) *_hoops_HCHPR = '\0';
			else if (_hoops_HCHPR != _hoops_PGIPP) {
				do *_hoops_HCHPR++ = ' ';
				_hoops_RGGA (_hoops_HCHPR == _hoops_PGIPP);
			}
		}
		if (_hoops_AGIPP != -1) {
			if (_hoops_SSHPP == -1) *_hoops_CSHPP = '\0';
			else if (_hoops_CSHPP != _hoops_RASGR) {
				do *_hoops_CSHPP++ = ' ';
				_hoops_RGGA (_hoops_CSHPP == _hoops_RASGR);
			}
		}

		_hoops_HPRH (item);
		return true;
	}

#endif
	return false;
}


HC_INTERFACE bool HC_CDECL HC_Find_Color_Name (
	char *		color,
	char *		_hoops_HGIPP,
	char *		_hoops_IGIPP) 
{
	_hoops_PAPPR context("Find_Color_Name");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Color_Name () */\n");
	);

	return HI_Find_Color_Name (context, color, -1, _hoops_HGIPP, -1, _hoops_IGIPP, -1);
}


HC_INTERFACE void HC_CDECL HC_Show_Color_Name_Count (
	int *			count) 
{
	_hoops_PAPPR context("Show_Color_Name_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Color_Name_Count () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_PSHPP;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_COLOR, HES_INACTIVE_SEARCH, "No color search is active");
		*count = 0;
	}
	else *count = _hoops_GGHPR->count;
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Color_Name_Search (void) 
{
	_hoops_PAPPR context("End_Color_Name_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Color_Name_Search () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_PSHPP;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_COLOR, HES_END_WITHOUT_BEGIN_SEARCH, "End without matching Begin");
		return;
	}

	HI_Free_Search_List (context, _hoops_GGHPR->list);

	context->_hoops_PSHPP = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
}



GLOBAL_FUNCTION void HI_UnDefine_Colors (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			string) {
#ifndef DISABLE_COLOR_NAMES
	_hoops_HCRPR					name;
	int						i = 0;
	char *					_hoops_ASAPR;

	if (*string == '\0') 
		return;

	int len = _hoops_SSGR (string) + 1;

	ALLOC_ARRAY (_hoops_ASAPR, len, char);
	name.text = null;
	name.length = 0;

	while (HI_Parse_String (string, ",", i++, _hoops_ASAPR, -1)) {

		HI_Canonize_Chars_Quoted (_hoops_ASAPR, &name, false);
		if (*HI_Look_Up_Color (_hoops_RIGC, name.text, name.length) != null) 
			HI_UnDefine_Color_Name (_hoops_RIGC, _hoops_ASAPR);

		if (name.text)
			FREE_ARRAY (name.text, name.length+1, char);
		name.text = null;
	}

	FREE_ARRAY (_hoops_ASAPR, len, char);
#endif
}




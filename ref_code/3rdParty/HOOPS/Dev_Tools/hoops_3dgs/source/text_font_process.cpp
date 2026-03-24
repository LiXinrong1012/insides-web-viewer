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
 * $Id: obf_tmp.txt 1.177 2011-01-08 00:54:14 jason Exp $
 */


#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "patterns.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


#ifndef DISABLE_DEFINED_FONTS
local	const char _hoops_SHHHC[] = "Can't locate builtin font";
local	const char _hoops_ISIGGR[] = "Unexpected problem 'marking font'";
#endif

GLOBAL_FUNCTION void HD_Find_One_Font (
	Display_Context const *_hoops_CSIGGR) {
	Display_Context alter *dc = (Display_Context alter *)_hoops_CSIGGR;
#ifndef DISABLE_DEFINED_FONTS
	_hoops_PGIIR const		*font;
	local		_hoops_SRHSR				_hoops_PSHGGR = _hoops_GRRCR ("Enfield");

	if (dc->_hoops_ASAGH)
		return;

	/* _hoops_SSIGGR */
	HD_Record_Font_With_Encoding (dc, _hoops_PSHGGR.text, null, _hoops_SACSR, 0.0f, 1.5f);
	if ((font = *HI_Look_Up_Font (dc->_hoops_RIGC, _hoops_PSHGGR.text, _hoops_PSHGGR.length)) == null)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_SHHHC);
	if (!HD_Mark_Font_As_Defined (dc, _hoops_PSHGGR.text, font))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_ISIGGR);
	if (!HD_Mark_Font_As_Generic (dc, _hoops_PSHGGR.text, GFN_STROKED))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_ISIGGR);
	if (!HD_Mark_Font_As_Transformable (dc, _hoops_PSHGGR.text,		_hoops_IAGGH))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_ISIGGR);

#endif
	dc->_hoops_ASAGH = true;
}

GLOBAL_FUNCTION void HD_Find_Basic_Fonts (
	Display_Context const *_hoops_CSIGGR) {
	Display_Context alter *dc = (Display_Context alter *)_hoops_CSIGGR;
#ifndef _hoops_HRSSH
	_hoops_PGIIR const		*font;
	local		_hoops_SRHSR				_hoops_GGCGGR = _hoops_GRRCR ("Newfield");
	local		_hoops_SRHSR				_hoops_ISHGGR = _hoops_GRRCR ("Brooktondale");
	local		_hoops_SRHSR				_hoops_CRIGGR = _hoops_GRRCR ("Kuma");
#endif

	if (dc->_hoops_PSAGH)
		return;

	if (!dc->_hoops_ASAGH) HD_Find_One_Font(dc);

#ifndef _hoops_HRSSH
	/* _hoops_RGCGGR */
	HD_Record_Font_With_Encoding (dc, _hoops_GGCGGR.text, null, _hoops_SSAIP, 0.0f, 1.5f);
	if ((font = *HI_Look_Up_Font (dc->_hoops_RIGC, _hoops_GGCGGR.text, _hoops_GGCGGR.length)) == null)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_SHHHC);
	if (!HD_Mark_Font_As_Defined (dc, _hoops_GGCGGR.text, font))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_ISIGGR);
	if (!HD_Mark_Font_As_Transformable (dc, _hoops_GGCGGR.text, _hoops_IAGGH))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_ISIGGR);

	/* _hoops_AGCGGR */
	HD_Record_Font_With_Encoding (dc, _hoops_ISHGGR.text, null, _hoops_SSAIP, 0.0f, 1.5f);
	if ((font = *HI_Look_Up_Font (dc->_hoops_RIGC, _hoops_ISHGGR.text, _hoops_ISHGGR.length)) == null)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_SHHHC);
	if (!HD_Mark_Font_As_Defined (dc, _hoops_ISHGGR.text, font))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_ISIGGR);
	if (!HD_Mark_Font_As_Transformable (dc, _hoops_ISHGGR.text, _hoops_IAGGH))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_ISIGGR);

	/* _hoops_PGCGGR */
	HD_Record_Font_With_Encoding (dc, _hoops_CRIGGR.text, null, _hoops_APHPH, 0.0f, 1.5f);

	if ((font = *HI_Look_Up_Font (dc->_hoops_RIGC, _hoops_CRIGGR.text, _hoops_CRIGGR.length)) == null)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_SHHHC);
	if (!HD_Mark_Font_As_Generic (dc, _hoops_CRIGGR.text, GFN_STROKED))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_ISIGGR);
	if (!HD_Mark_Font_As_Defined (dc, _hoops_CRIGGR.text, font))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_ISIGGR);

	if (!HD_Mark_Font_As_Transformable (dc, _hoops_CRIGGR.text, _hoops_IAGGH))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, _hoops_ISIGGR);
#endif

	(*dc->_hoops_ACPGR->_hoops_CACSR)(dc);

	dc->_hoops_PSAGH = true;
}

GLOBAL_FUNCTION void HD_Find_All_Fonts (
	Display_Context const *_hoops_CSIGGR) {

	Display_Context alter *dc = (Display_Context alter *)_hoops_CSIGGR;

	if (dc->_hoops_HSAGH)
		return;

	if (!dc->_hoops_ASAGH) HD_Find_One_Font(dc);

	if (!dc->_hoops_PSAGH) HD_Find_Basic_Fonts(dc);

#ifdef FREETYPE
	HD_Find_Freetype_Fonts (dc);
#endif

	(*dc->_hoops_ACPGR->find_all_fonts)(dc);

	dc->_hoops_HSAGH = true;
}





GLOBAL_FUNCTION void HD_Find_Font_Height (
	Display_Context const		*dc,
	Font_Instance const			*_hoops_SIHIH) {
	Font_Instance alter			* alter *_hoops_ASRGR;
	Font_Instance alter			*instance;

	instance = (Font_Instance alter *)_hoops_SIHIH;

	/* _hoops_HAGIP _hoops_IH _hoops_RH _hoops_APPS - _hoops_SSHAR _hoops_CGH _hoops_ISPR _hoops_SGS _hoops_SCH _hoops_SAGGR _hoops_PIISR _hoops_GGR */
	if (!HD_Load_Font (dc, instance)) {
		instance->_hoops_IGGGH = instance->_hoops_ISISR = _hoops_IARGI; /* _hoops_ICCAR _hoops_PRAR */
		instance->_hoops_ISISR = (float)_hoops_IARGI;
	}

	/* _hoops_ASAR-_hoops_GHIS _hoops_RH _hoops_CPCI */
	if (instance->_hoops_SSSSP != null) {
		/* (_hoops_RH _hoops_HIIC _hoops_HRGR _hoops_ICIC) */
		_hoops_ASRGR = (Font_Instance alter * alter *)&instance->family->_hoops_ICSSP;
		while (*_hoops_ASRGR != instance)
			_hoops_ASRGR = &(*_hoops_ASRGR)->_hoops_SSSSP;
		*_hoops_ASRGR = instance->_hoops_SSSSP;

		while (*_hoops_ASRGR != null && (*_hoops_ASRGR)->_hoops_ISISR <= instance->_hoops_ISISR)
			_hoops_ASRGR = &(*_hoops_ASRGR)->_hoops_SSSSP;
		instance->_hoops_SSSSP = *_hoops_ASRGR;
		*_hoops_ASRGR = instance;
	}

	if (instance->_hoops_GGGGH != null &&
		instance->_hoops_IRGGH != GFN_NONE) {
		/* (_hoops_RH _hoops_HIIC _hoops_HRGR _hoops_ICIC) */
		_hoops_ASRGR = (Font_Instance alter * alter *)&dc->_hoops_RRHGH[instance->_hoops_IRGGH];
		while (*_hoops_ASRGR != instance)
			_hoops_ASRGR = &(*_hoops_ASRGR)->_hoops_GGGGH;
		*_hoops_ASRGR = instance->_hoops_GGGGH;

		while (*_hoops_ASRGR != null && (*_hoops_ASRGR)->_hoops_ISISR <= instance->_hoops_ISISR)
			_hoops_ASRGR = &(*_hoops_ASRGR)->_hoops_GGGGH;
		instance->_hoops_GGGGH = *_hoops_ASRGR;
		*_hoops_ASRGR = instance;
	}
}



GLOBAL_FUNCTION unsigned short HD_Standard_Map_Char_Index(
	Font_Instance const	*		instance,
	Karacter					_hoops_IPCSR) {

	UNREFERENCED(instance);
	return _hoops_IPCSR;
}

GLOBAL_FUNCTION bool HD_Standard_Name_Font(
	Net_Rendition const &		nr,
	_hoops_IGPIR const *			_hoops_RRCSP,
	_hoops_IGPIR alter *			_hoops_ARCSP) {

	UNREFERENCED(nr);
	UNREFERENCED(_hoops_RRCSP);
	UNREFERENCED(_hoops_ARCSP);

	return false;
}



local bool HD_Freetype_Name_Font(
	Net_Rendition const &		nr,
	_hoops_IGPIR const *			_hoops_RRCSP,
	_hoops_IGPIR alter *			_hoops_ARCSP) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	char						specific[1024];
	char alter *				_hoops_ASAPR = specific;
	char alter *				_hoops_PSAPR = specific + _hoops_GGAPR (specific);

	_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", _hoops_RRCSP->specified.text);

	if (_hoops_HRCIR->_hoops_ASRIP)
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s", "BOLD");

	if (_hoops_HRCIR->_hoops_PSRIP)
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " %s", "ITALIC");
	*_hoops_ASAPR = '\0';

	ZERO_STRUCT(_hoops_ARCSP, _hoops_IGPIR);

	HI_Copy_Chars_To_Name(specific, &_hoops_ARCSP->specified);

	return true;
}

GLOBAL_FUNCTION bool HD_Standard_Will_Use_Stencil(
	Net_Rendition const &		nr,
	Font_Instance const *		specific) {

	if (specific->family->_hoops_RRCSR == _hoops_ARCSR)
		return false;

	if (nr->_hoops_SISI->transform == FT_FULL)
		return true;

	return false;
}

GLOBAL_FUNCTION void HD_Standard_Size_Font(
	Net_Rendition const &		nr,
	Font_Instance alter *		instance) {
	float						_hoops_HGCGGR, height;

	UNREFERENCED(nr);

	if (instance->family->_hoops_RRCSR == _hoops_ARCSR) {
		instance->_hoops_RACSR = instance->_hoops_ISISR;
		instance->_hoops_GCHSA = 1.0f;
		instance->_hoops_RRGGH = false;
		return;
	}


	instance->_hoops_RRGGH = (*instance->_hoops_GGSSP)(nr, instance);

	if (nr->_hoops_SISI->transform == FT_FULL) {
		_hoops_SGCC		_hoops_HSGA = nr->transform_rendition->_hoops_IPH;

		if (instance->_hoops_RRGGH) {
			_hoops_HGCGGR = height = (int)instance->_hoops_ISISR;

			if (_hoops_HSGA->data._hoops_CPH != 0.0f) {
				height *= _hoops_HSGA->data._hoops_CPH;
			}
			else {
				float			_hoops_PIIH, _hoops_HIIH, _hoops_SHGIP, _hoops_IGCGGR;

				_hoops_PIIH = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->data.elements[0][0]);
				_hoops_HIIH = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->data.elements[1][0]);
				_hoops_SHGIP = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->data.elements[2][0]);

				_hoops_IGCGGR = _hoops_IAAA(_hoops_IAAA(_hoops_PIIH, _hoops_HIIH), _hoops_SHGIP);

				height *= _hoops_IGCGGR;
			}

			if (nr->_hoops_SISI->_hoops_GHGRP != GSU_ORU)
				height /= nr->transform_rendition->_hoops_SPH->_hoops_SSPA*0.5f;

			height = (int)HI_Get_Stencil_Cache_Height ((int)height, true);
		}
		else {
			/* _hoops_IPIH _hoops_RGAR _hoops_CGCGGR _hoops_RHAP _hoops_GRAA _hoops_APSP _hoops_AHGGR */

			_hoops_HGCGGR = height = (float)instance->_hoops_ISISR;

			if (height < 24.0f)
				height = 24.0f;

			if (height > 256.0f)
				height = 256.0f;
		}
	}
	else
		_hoops_HGCGGR = height = instance->_hoops_ISISR;

	((Font_Instance alter *)instance)->_hoops_RACSR = height;
	if (height > 0)
		((Font_Instance alter *)instance)->_hoops_GCHSA = (float)_hoops_HGCGGR/(float)height;
	else
		((Font_Instance alter *)instance)->_hoops_GCHSA = 1.0f;
}


local	_hoops_SRHSR		_hoops_SGCGGR = _hoops_GRRCR ("Newfield");

local Font_Instance const *_hoops_GRCGGR (
	Display_Context alter	*dc,
	_hoops_HCRPR const				*name,
	_hoops_IHGRP			encoding,
	Integer32				max,
	Integer32				min,
	Integer32				pixels,
	float					_hoops_PHGIP,
	bool					_hoops_RRCGGR);


local Font_Instance const *_hoops_ARCGGR (
	Display_Context alter	*dc,
	_hoops_HCRPR const				*name,
	_hoops_IHGRP			encoding,
	Integer32				max,
	Integer32				min,
	Integer32				pixels,
	float					_hoops_PHGIP,
	bool					_hoops_RRCGGR) {
	_hoops_PGIIR const				*font;

	/* _hoops_PIRC _hoops_GSGI -- _hoops_CACH _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_IRS _hoops_PAPR _hoops_HRCSR _hoops_SR _hoops_PAH _hoops_ACAPA */

	if ((font = *HI_Look_Up_Font (dc->_hoops_RIGC, name->text, name->length)) != null &&
		 HI_Encoding_Is_Compatible (encoding, font->encoding)) {
		char			buf[MAX_ERRMSG];

		/* _hoops_CAHP _hoops_IRS _hoops_PCRIP _hoops_IS _hoops_PSSP _hoops_RH _hoops_PAPR _hoops_HRCSR */
		Sprintf_N (buf, "%n", name);
		HD_Record_Font_With_Encoding (dc, buf, null, font->encoding, 0.0f, 1.5f);

		if (!HD_Mark_Font_As_Defined (dc, buf, font) ||
			!HD_Mark_Font_As_Transformable (dc, buf, _hoops_HAGGH)) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Unexpected error accessing defined font");
			return null;
		}
		else {
			/* _hoops_SGH _hoops_RH _hoops_CCAH _hoops_PCRIP */
			return _hoops_GRCGGR (dc, name, encoding,
									max, min, pixels, _hoops_PHGIP, _hoops_RRCGGR);
		}
	}
	else
		return null;	/* _hoops_PIRC _hoops_RPGHH */
}

local Font_Instance const *_hoops_GRCGGR (
	Display_Context alter	*dc,
	_hoops_HCRPR const				*name,
	_hoops_IHGRP			encoding,
	Integer32				max,
	Integer32				min,
	Integer32				pixels,
	float					_hoops_PHGIP,
	bool					_hoops_RRCGGR) {
	_hoops_SHSSP const			*_hoops_GSIGGR=0;
	_hoops_SHSSP const			*next;
	int						length;
	bool					_hoops_PRCGGR = false;
	int						_hoops_ARAHR = 0;
	char const				*_hoops_RPPA = name->text;
	int						count = name->length;


	_hoops_RGGA (--count < 0) _hoops_ARAHR += _hoops_SHPCR (*_hoops_RPPA), _hoops_RPPA++;

	next = dc->_hoops_GRHGH[_hoops_ARAHR & (_hoops_HHRSP - 1)];

	length = name->length;

	_hoops_PCCAR {
		if ((_hoops_GSIGGR = next) == null) {
			if (!_hoops_PRCGGR) {
				_hoops_AAPIR	*_hoops_IRHGH = dc->_hoops_IRHGH;

				while (_hoops_IRHGH != null) {
					if (_hoops_IGGPA(_hoops_IRHGH->name.text, name->text))
						break;
					_hoops_IRHGH = _hoops_IRHGH->next;
				}

				if (_hoops_IRHGH)
					/* _hoops_GA'_hoops_RA _hoops_HPPR _hoops_GICS */;
				else if ((*dc->_hoops_ACPGR->_hoops_AACSR) (dc, name->text)) {
					next = dc->_hoops_GRHGH[_hoops_ARAHR & (_hoops_HHRSP - 1)];
				}
				else if (HD_Find_One_Freetype_Font (dc, name->text)) {
					next = dc->_hoops_GRHGH[_hoops_ARAHR & (_hoops_HHRSP - 1)];
				}
				else {
					ZALLOC (_hoops_IRHGH, _hoops_AAPIR);
					_hoops_IRHGH->next = dc->_hoops_IRHGH;
					dc->_hoops_IRHGH = _hoops_IRHGH;
					HI_Copy_Name (name, &_hoops_IRHGH->name);
				}

				_hoops_PRCGGR = true;
			}
			if ((_hoops_GSIGGR = next) == null)
				return _hoops_ARCGGR (dc, name, encoding,
										 max, min, pixels, _hoops_PHGIP, _hoops_RRCGGR);
		}

		next = _hoops_GSIGGR->_hoops_SSCAP;
		if (_hoops_GSIGGR->name.length == length) {
			char const		*a = name->text,
							*b = _hoops_GSIGGR->name.text;

			while (_hoops_SHPCR(*a) == _hoops_SHPCR(*b)) {
				++a, ++b;
				if (*b == '\0') {
					if (_hoops_GSIGGR->type == _hoops_GISSP &&
						((_hoops_RCSSP const*)_hoops_GSIGGR)->font != null &&
						BIT (((_hoops_RCSSP const*)_hoops_GSIGGR)->font->_hoops_RRHH, _hoops_HGAGR)) {
						/* _hoops_PAPR _hoops_HRCSR _hoops_SSCP _hoops_RPII _hoops_ACHPP, _hoops_SR _hoops_PIHA _hoops_APRI
						 * _hoops_RGCI _hoops_SGCRP "_hoops_PCRIP" _hoops_PPR _hoops_GIPHR _hoops_HHH _hoops_RRI
						 */
						HD_Free_Defined_Font_Family (dc, (_hoops_RCSSP alter *)_hoops_GSIGGR);
						break;
					}
					else if ((_hoops_GSIGGR->type == _hoops_RISSP &&
							  HI_Encoding_Is_Compatible (encoding,
												((Font_Instance const*)_hoops_GSIGGR)->encoding)) ||
							 (_hoops_GSIGGR->type == _hoops_GISSP &&
							  HI_Encoding_Is_Compatible (encoding,
										((_hoops_RCSSP const*)_hoops_GSIGGR)->_hoops_ICSSP->encoding)))
						goto _hoops_PCPPR;	/* _hoops_GGHP _hoops_IRS _hoops_GHACA _hoops_PSSP */
					else
						break;
				}
			}
		}
	}
	_hoops_PCPPR:;

	if (_hoops_GSIGGR->type == _hoops_RISSP) {
		Font_Instance const* instance = (Font_Instance const *)_hoops_GSIGGR;

		if (_hoops_PHGIP == 0.0f)	/* _hoops_HII _hoops_HRCGGR - "_hoops_PA" */
			return (Font_Instance const *)_hoops_GSIGGR;

		if (pixels < 2 && instance->family->_hoops_RRCSR != _hoops_ARCSR &&
				instance->family->_hoops_RRCSR != _hoops_SISSP)
				return null;

		if (instance->_hoops_ISISR < 0)
			HD_Find_Font_Height (dc, (Font_Instance const *)_hoops_GSIGGR);

		if (_hoops_RRCGGR) {
			if (!instance->_hoops_PRGGH &&
				min <= instance->_hoops_IGGGH &&
				max >= instance->_hoops_IGGGH)
				return instance;
		}
		else {
			if (!instance->_hoops_PRGGH &&
				min <= instance->_hoops_ISISR &&
				max >= instance->_hoops_ISISR)
				return instance;
		}

		return null;
	}
	else {
		/* _hoops_IRCGGR _hoops_RSSA _hoops_HPGR _hoops_IRS _hoops_CRCGGR */
		_hoops_RCSSP const *		family = (_hoops_RCSSP const *)_hoops_GSIGGR;
		Font_Instance const	*	specific = family->_hoops_ICSSP;

		if (_hoops_PHGIP == 0.0f) {	/* _hoops_HII _hoops_HRCGGR - "_hoops_PA" */
			do if (!specific->_hoops_PRGGH)
				break;
			while ((specific = specific->_hoops_SSSSP) != null);

			return specific;	/* _hoops_PSCR _hoops_RH _hoops_SRS _hoops_RIRIA */
		}
		else if (!family->_hoops_PCSSP) {
			Font_Instance const	*_hoops_ACCAA = null;
			Integer32			err,
												_hoops_SRCGGR = _hoops_IICIA;

			if (pixels < 2 && family->_hoops_RRCSR != _hoops_ARCSR &&
				family->_hoops_RRCSR != _hoops_SISSP)
				return null;

			while (specific->_hoops_ISISR < 0) {
				HD_Find_Font_Height (dc, specific);
				specific = family->_hoops_ICSSP; /* _hoops_HSPP _hoops_IAPR */
			}

			if (_hoops_RRCGGR) {
				do {
					if (specific->_hoops_IGGGH > max) break;
					else if (specific->_hoops_IGGGH >= min) {
						if ((err = (int)specific->_hoops_IGGGH - pixels) < 0) err = -err;
						if (err <= _hoops_SRCGGR && !specific->_hoops_PRGGH) {
							if ((_hoops_SRCGGR = err) == 0) return specific;/* _hoops_HRGR _hoops_RRHP */
							_hoops_ACCAA = specific;
						}
					}
				} while ((specific = specific->_hoops_SSSSP) != null);
			}
			else {
				do {
					if (specific->_hoops_ISISR > max) break;
					else if (specific->_hoops_ISISR >= min) {
						if ((err = (int)specific->_hoops_ISISR - pixels) < 0) err = -err;
						if (err <= _hoops_SRCGGR && !specific->_hoops_PRGGH) {
							if ((_hoops_SRCGGR = err) == 0) return specific;/* _hoops_HRGR _hoops_RRHP */
							_hoops_ACCAA = specific;
						}
					}
				} while ((specific = specific->_hoops_SSSSP) != null);
			}
			return _hoops_ACCAA;
		}
		else { /* _hoops_IHSH _hoops_IH _hoops_RRHP _hoops_SPASR _hoops_RGAR */
			if (pixels < 2 && family->_hoops_RRCSR != _hoops_ARCSR &&
					family->_hoops_RRCSR != _hoops_SISSP)
					return null;

			while (specific->_hoops_ISISR < 0) {
				HD_Find_Font_Height (dc, specific);
				specific = family->_hoops_ICSSP; /* _hoops_HSPP _hoops_IAPR */
			}

			if (_hoops_RRCGGR) {
				do {
					if (specific->_hoops_IGGGH == _hoops_PHGIP) { /* _hoops_GGHP _hoops_RH _hoops_RPHR _hoops_SPR */
						if (specific->_hoops_PRGGH) return null; /* _hoops_ICCAR _hoops_GACGGR! */
						return specific;
					}
				} while ((specific = specific->_hoops_SSSSP) != null);
			}
			else {
				do {
					if (specific->_hoops_ISISR == _hoops_PHGIP) {
						if (specific->_hoops_PRGGH) return null; /* _hoops_ICCAR _hoops_GACGGR! */
						return specific;
					}
				} while ((specific = specific->_hoops_SSSSP) != null);
			}

			return family->_hoops_ICSSP; /* _hoops_ASRC _hoops_RH '0' _hoops_HAGAR */
		}
	}
}


local Font_Instance const * _hoops_RACGGR (
	Display_Context const *	dc,
	_hoops_CSSGP		name,
	_hoops_IHGRP			encoding,
	Integer32				max,
	Integer32				min,
	Integer32				pixels,
	float					_hoops_PHGIP,
	bool					_hoops_RRCGGR) {
	Font_Instance const *	specific;

	if (name == GFN_STROKED && !dc->_hoops_ASAGH)
		HD_Find_One_Font(dc);

	if (name != GFN_STROKED && !dc->_hoops_PSAGH)
		HD_Find_Basic_Fonts(dc);

	if ((specific = dc->_hoops_RRHGH[name]) == null)
		return null;

	if (_hoops_PHGIP == 0.0f) {		/* _hoops_HII _hoops_HRCGGR */
		do if (!specific->_hoops_PRGGH && HI_Encoding_Is_Compatible (encoding, specific->encoding))
			break;
		while ((specific = specific->_hoops_GGGGH) != null);
		return specific;
	}
	else if (!specific->family->_hoops_PCSSP) {
		Font_Instance const	*_hoops_ACCAA = null;
		Integer32			err,
												_hoops_SRCGGR = _hoops_IICIA;

		if (pixels < 2 && specific->family->_hoops_RRCSR != _hoops_ARCSR)
			return null;

		while (specific->_hoops_ISISR < 0) {
			HD_Find_Font_Height (dc, specific);
			specific = dc->_hoops_RRHGH[name]; /* _hoops_HSPP _hoops_IAPR */
		}

		if (_hoops_RRCGGR) {
			do {
				if (specific->_hoops_IGGGH > max) break;
				else if (specific->_hoops_IGGGH >= min) {
					if ((err = (int)specific->_hoops_IGGGH - pixels) < 0) err = -err;
					if (err <= _hoops_SRCGGR && !specific->_hoops_PRGGH &&
						HI_Encoding_Is_Compatible (encoding, specific->encoding)==_hoops_RCIGI) {
						if ((_hoops_SRCGGR = err) == 0) return specific;/* _hoops_HRGR _hoops_RRHP */
						_hoops_ACCAA = specific;
					}
				}
			} while ((specific = specific->_hoops_GGGGH) != null);

			specific = dc->_hoops_RRHGH[name];
			do {
				if (specific->_hoops_IGGGH > max) break;
				else if (specific->_hoops_IGGGH >= min) {
					if ((err = (int)specific->_hoops_IGGGH - pixels) < 0) err = -err;
					if (err <= _hoops_SRCGGR && !specific->_hoops_PRGGH &&
						HI_Encoding_Is_Compatible (encoding, specific->encoding)) {
						if ((_hoops_SRCGGR = err) == 0) return specific;/* _hoops_HRGR _hoops_RRHP */
						_hoops_ACCAA = specific;
					}
				}
			} while ((specific = specific->_hoops_GGGGH) != null);
		}
		else {
			do {
				if (specific->_hoops_ISISR > max) break;
				else if (specific->_hoops_ISISR >= min) {
					if ((err = (int)specific->_hoops_ISISR - pixels) < 0) err = -err;
					if (err <= _hoops_SRCGGR && !specific->_hoops_PRGGH &&
						HI_Encoding_Is_Compatible (encoding, specific->encoding)==_hoops_RCIGI) {

						if ((_hoops_SRCGGR = err) == 0) return specific;/* _hoops_HRGR _hoops_RRHP */
						_hoops_ACCAA = specific;
					}
				}
			} while ((specific = specific->_hoops_GGGGH) != null);

			specific = dc->_hoops_RRHGH[name];
			do {
				if (specific->_hoops_ISISR > max) break;
				else if (specific->_hoops_ISISR >= min) {
					if ((err = (int)specific->_hoops_ISISR - pixels) < 0) err = -err;
					if (err <= _hoops_SRCGGR && !specific->_hoops_PRGGH &&
						HI_Encoding_Is_Compatible (encoding, specific->encoding)) {

						if ((_hoops_SRCGGR = err) == 0) return specific;/* _hoops_HRGR _hoops_RRHP */
						_hoops_ACCAA = specific;
					}
				}
			} while ((specific = specific->_hoops_GGGGH) != null);
		}
		return _hoops_ACCAA;
	}
	else { /* _hoops_IHSH _hoops_IH _hoops_RRHP _hoops_SPASR _hoops_RGAR */
		if (pixels < 2 && specific->family->_hoops_RRCSR != _hoops_ARCSR)
			return null;

		while (specific->_hoops_ISISR < 0) {
			HD_Find_Font_Height (dc, specific);
			specific = dc->_hoops_RRHGH[name]; /* _hoops_HSPP _hoops_IAPR */
		}

		if (_hoops_RRCGGR) {
			do if (specific->_hoops_IGGGH == _hoops_PHGIP &&
				   HI_Encoding_Is_Compatible (encoding, specific->encoding)==_hoops_RCIGI) {
				/* _hoops_GGHP _hoops_RH _hoops_RPHR _hoops_SPR */
				if (specific->_hoops_PRGGH) return null; /* _hoops_ICCAR _hoops_GACGGR! */
				return specific;
			} while ((specific = specific->_hoops_GGGGH) != null);

			specific = dc->_hoops_RRHGH[name];
			do if (specific->_hoops_IGGGH == _hoops_PHGIP &&
				   HI_Encoding_Is_Compatible (encoding, specific->encoding)) {
				/* _hoops_GGHP _hoops_RH _hoops_RPHR _hoops_SPR */
				if (specific->_hoops_PRGGH) return null; /* _hoops_ICCAR _hoops_GACGGR! */
				return specific;
			} while ((specific = specific->_hoops_GGGGH) != null);
		}
		else {
			do if ( ( (specific->_hoops_GCHSA != 1.0) ? specific->_hoops_RACSR : specific->_hoops_ISISR) == _hoops_PHGIP &&
				   HI_Encoding_Is_Compatible (encoding, specific->encoding)==_hoops_RCIGI) {
				/* _hoops_GGHP _hoops_RH _hoops_RPHR _hoops_SPR */
				if (specific->_hoops_PRGGH) return null; /* _hoops_ICCAR _hoops_GACGGR! */
				return specific;
			} while ((specific = specific->_hoops_GGGGH) != null);

			specific = dc->_hoops_RRHGH[name];
			do if ( ( (specific->_hoops_GCHSA != 1.0) ? specific->_hoops_RACSR : specific->_hoops_ISISR) == _hoops_PHGIP &&
				   HI_Encoding_Is_Compatible (encoding, specific->encoding)) {
				/* _hoops_GGHP _hoops_RH _hoops_RPHR _hoops_SPR */
				if (specific->_hoops_PRGGH) return null; /* _hoops_ICCAR _hoops_GACGGR! */
				return specific;
			} while ((specific = specific->_hoops_GGGGH) != null);
		}

		/* _hoops_ASRC _hoops_RH '0' _hoops_HAGAR */
		specific = dc->_hoops_RRHGH[name];
		do if (HI_Encoding_Is_Compatible (encoding, specific->encoding)==_hoops_RCIGI)
			return specific;
		while ((specific = specific->_hoops_GGGGH) != null);

		specific = dc->_hoops_RRHGH[name];
		do if (HI_Encoding_Is_Compatible (encoding, specific->encoding))
			return specific;
		while ((specific = specific->_hoops_GGGGH) != null);

		/* _hoops_AACGGR'_hoops_RA _hoops_SSS _hoops_PA, _hoops_HIH _hoops_SR _hoops_PIHA _hoops_ASRC _hoops_IRS _hoops_PSSP _hoops_IH "_hoops_RRIC"
		 * _hoops_RPP _hoops_HHPPC _hoops_GHAGI-_hoops_HHHPP-1 */
#ifndef DISABLE_DEFINED_FONTS
		if (name == GFN_STROKED &&
				HI_Encoding_Is_Compatible (encoding,
					dc->_hoops_RRHGH[GFN_STROKED]->family->_hoops_ICSSP->encoding))
			return dc->_hoops_RRHGH[GFN_STROKED]->family->_hoops_ICSSP;
		else
#endif
			return null;
	}
}

local void _hoops_PACGGR(Font_Instance alter* specific, Display_Context* _hoops_SAARH) {
		Font_Instance alter	*_hoops_GGHCS = (Font_Instance alter *)specific;
		Display_Context alter		*dc = (Display_Context alter *)_hoops_SAARH;

		switch (specific->family->_hoops_RRCSR) {
#ifndef DISABLE_DEFINED_FONTS
			case _hoops_ARCSR:
				_hoops_GGHCS->load_font = HD_Load_Defined_Font;
				_hoops_GGHCS->unload_font = HD_Unload_Defined_Font;
				_hoops_GGHCS->measure_char = HD_Measure_Defined_Char;
				_hoops_GGHCS->_hoops_SRCSR = HD_Draw_Defined_Font;
				_hoops_GGHCS->_hoops_SSCSP = HD_Standard_Size_Font;
				_hoops_GGHCS->_hoops_GGSSP = HD_Standard_Will_Use_Stencil;
				break;
#endif
			case _hoops_CISSP:
				_hoops_GGHCS->load_font = dc->_hoops_ACPGR->load_font;
				_hoops_GGHCS->unload_font = dc->_hoops_ACPGR->unload_font;
				_hoops_GGHCS->measure_char = dc->_hoops_ACPGR->measure_char;
				_hoops_GGHCS->_hoops_SRCSR = dc->_hoops_ACPGR->_hoops_SRCSR;
				_hoops_GGHCS->map_font_char_index = dc->_hoops_ACPGR->map_font_char_index;
				_hoops_GGHCS->_hoops_SSCSP = dc->_hoops_ACPGR->_hoops_SSCSP;
				_hoops_GGHCS->_hoops_RGSSP = dc->_hoops_ACPGR->_hoops_RGSSP;
				_hoops_GGHCS->_hoops_GGSSP = dc->_hoops_ACPGR->_hoops_GGSSP;
				break;
#ifdef FREETYPE
			case _hoops_SISSP:
				_hoops_GGHCS->load_font = HD_Load_Freetype_Font;
				_hoops_GGHCS->unload_font = HD_Unload_Freetype_Font;
				_hoops_GGHCS->measure_char = HD_Measure_Freetype_Char;
				_hoops_GGHCS->_hoops_SRCSR = HD_Draw_Freetype_Font;
				_hoops_GGHCS->map_font_char_index = HD_Map_Freetype_Char_Index;
				_hoops_GGHCS->_hoops_RGSSP = HD_Make_Freetype_Stencil;
				_hoops_GGHCS->_hoops_SSCSP = HD_Standard_Size_Font;
				_hoops_GGHCS->_hoops_GGSSP = HD_Freetype_Will_Use_Stencil;
				break;
#endif
		}
}


#define _hoops_HACGGR		0x01
#define _hoops_IACGGR		0x02
#define _hoops_CACGGR			0x04
#define _hoops_SACGGR			0x08
#define _hoops_GPCGGR			0x10

GLOBAL_FUNCTION void HD_Choose_Font (
	Net_Rendition const &		nr,
	_hoops_IGPIR const *			_hoops_AHHIH,
	_hoops_IHGRP				encoding,
	bool						_hoops_AARHP) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	_hoops_IGCSR alter &		_hoops_IRRIP = (_hoops_IGCSR alter &)_hoops_HRCIR;
	float						size,
								_hoops_ACPAP;
	Integer32					pixels,
								max_height,
								min_height;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	Font_Instance const *		specific;
	bool						_hoops_PRPSP = false;
	bool						_hoops_RRCGGR = false;
	bool						_hoops_RPCGGR = true;
	int							index=0;

	UNREFERENCED(_hoops_AARHP);

	if (_hoops_HRCIR->font != null && !_hoops_HRCIR->font->_hoops_PRGGH &&
		HI_Encoding_Is_Compatible (encoding, _hoops_HRCIR->font->encoding)) {
		((Font_Instance alter *)_hoops_HRCIR->font)->_hoops_RACSR = _hoops_HRCIR->font->_hoops_ISISR;
		return; /* _hoops_IIP _hoops_IRIPR */
	}

	if (!dc->_hoops_ASAGH)
		HD_Find_One_Font(dc);

	/* _hoops_PPRII _hoops_HIGSC _hoops_RSIRR, _hoops_IGIR, _hoops_IGIR _hoops_AAHP, _hoops_PPR _hoops_AHGGR. _hoops_SCIAR
		_hoops_RSIRR, _hoops_PIHA _hoops_HIGSC _hoops_APCGGR, _hoops_RH _hoops_PPCGGR, _hoops_PPR _hoops_RH _hoops_HPCGGR. */

	/* _hoops_SICR _hoops_IGIR _hoops_PPR _hoops_IGIR _hoops_AAHP _hoops_IS _hoops_RIHRR _hoops_ASPA */
	size = 1.0f;
	switch (_hoops_HRCIR->_hoops_GHGRP) {
		case _hoops_SPSC: {
			_hoops_SGCC			_hoops_HSGA = nr->transform_rendition->_hoops_IPH;

			if (_hoops_HSGA->data._hoops_CPH != 0.0f)
				size = _hoops_HSGA->data._hoops_CPH;
			else {
				float	tmp;

				size = ((Vector const *)&_hoops_HSGA->data.elements[0][0])->length();
				if ((tmp = ((Vector const *)&_hoops_HSGA->data.elements[1][0])->length()) > size)
					size = tmp;
				if ((tmp = ((Vector const *)&_hoops_HSGA->data.elements[2][0])->length()) > size)
					size = tmp;
			}
		}	_hoops_HHHI;

		case GSU_ORU: {
			_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
			_hoops_HHRA const *				_hoops_SPH = nr->transform_rendition->_hoops_SPH;
			float						width, height;

			width  = (float)(_hoops_SGRA->extent.right - _hoops_SGRA->extent.left + 1 - _hoops_SGRA->_hoops_RRAIP.left - _hoops_SGRA->_hoops_RRAIP.right);
			height = (float)(_hoops_SGRA->extent.top - _hoops_SGRA->extent.bottom + 1 - _hoops_SGRA->_hoops_RRAIP.bottom - _hoops_SGRA->_hoops_RRAIP.top);

			// _hoops_CGH _hoops_SHPR _hoops_CCIR _hoops_SHH _hoops_HGGA _hoops_GGR?
			//_hoops_IPCGGR _hoops_RCIC &	_hoops_CPCGGR = _hoops_SCII->_hoops_RICC->_hoops_GSCHA;
			//_hoops_IGAA *= 0.5f * (_hoops_CPCGGR._hoops_RPHR - _hoops_CPCGGR._hoops_RAAP);
			//_hoops_APPS *= 0.5f * (_hoops_CPCGGR._hoops_SCIA - _hoops_CPCGGR._hoops_PRPC);

			if (_hoops_SPH->projection == _hoops_SSIH ||
				_hoops_SPH->_hoops_CSIH >= _hoops_SGRA->_hoops_CSIH)
				size *= _hoops_HRCIR->_hoops_PHP * height / _hoops_SPH->_hoops_SSPA;
			else
				size *= _hoops_HRCIR->_hoops_PHP * width / _hoops_SPH->_hoops_ISPA;
		}	break;

		case GSU_SRU: {
			size = _hoops_HRCIR->_hoops_PHP * (float)dc->current._hoops_PRPSR.y;
		}	break;

		case GSU_WRU: {
			_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;

			size = _hoops_HRCIR->_hoops_PHP *
				   (float)(_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom + 1);
			if (size <= 0.0f)
				size = 1.0f;
		}	break;

		case GSU_POINTS: {
			size = _hoops_HRCIR->_hoops_PHP *					/* _hoops_RSSA */
				   (float)(1.0/72 *					/* _hoops_IPIHH _hoops_RIR _hoops_PPSR */
						 2.54 *						/* _hoops_SAPSR _hoops_RIR _hoops_CPIHH */
						 1.0001) *					/* (_hoops_GIRR _hoops_GH _hoops_IRS _hoops_RSCA) */
				   dc->current._hoops_HAP.y;	/* _hoops_ASPA _hoops_RIR _hoops_SPIHH */

			if (!BIT(dc->flags, _hoops_CSHSR))
				size *= HOOPS_WORLD->_hoops_IRGHP;

			_hoops_RRCGGR = true;
		}	break;

		case GSU_PIXELS: {
			size = _hoops_HRCIR->_hoops_PHP;
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "'size units' ?");
			size = 10.0f;
		}	break;
	}
	if (_hoops_HRCIR->transform == FT_FULL && _hoops_HRCIR->_hoops_GHGRP != GSU_ORU && _hoops_HRCIR->_hoops_GHGRP != _hoops_SPSC) {
		_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
		_hoops_HHRA const *				_hoops_SPH = nr->transform_rendition->_hoops_SPH;

		if (_hoops_SPH->_hoops_CSIH < _hoops_SGRA->_hoops_CSIH) {
			if (_hoops_SPH->_hoops_CSIH > 1.0f && _hoops_SGRA->_hoops_CSIH >= 1.0f)
				size /= _hoops_SPH->_hoops_CSIH;
		}
		else {
			if (_hoops_SPH->_hoops_CSIH < 1.0f && _hoops_SGRA->_hoops_CSIH <= 1.0f)
				size *= _hoops_SPH->_hoops_CSIH;
		}
	}

	_hoops_ACPAP = 1.0f;
	switch (_hoops_HRCIR->_hoops_SSPAP) {
		case _hoops_SPSC: {
			_hoops_SGCC			_hoops_HSGA = nr->transform_rendition->_hoops_IPH;

			if (_hoops_HSGA->data._hoops_CPH != 0.0f)
				_hoops_ACPAP = _hoops_HSGA->data._hoops_CPH;
			else {
				float	tmp;

				_hoops_ACPAP = ((Vector const *)&_hoops_HSGA->data.elements[0][0])->length();
				if ((tmp = ((Vector const *)&_hoops_HSGA->data.elements[1][0])->length()) > _hoops_ACPAP)
					_hoops_ACPAP = tmp;
				if ((tmp = ((Vector const *)&_hoops_HSGA->data.elements[2][0])->length()) > _hoops_ACPAP)
					_hoops_ACPAP = tmp;
			}
		}	_hoops_HHHI;

		case GSU_ORU: {
			_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
			_hoops_HHRA const *				_hoops_SPH = nr->transform_rendition->_hoops_SPH;

			_hoops_ACPAP *= _hoops_HRCIR->_hoops_ACPAP *
					(float)(_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom + 1) /
					_hoops_SPH->_hoops_SSPA;
		}	break;

		case GSU_SRU: {
			_hoops_ACPAP = _hoops_HRCIR->_hoops_ACPAP * (float)dc->current._hoops_PRPSR.y;
		}	break;

		case GSU_WRU: {
			_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;

			_hoops_ACPAP = _hoops_HRCIR->_hoops_ACPAP *
					(float)(_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom + 1);
		}	break;

		case GSU_POINTS: {
			_hoops_ACPAP = _hoops_HRCIR->_hoops_ACPAP *		/* _hoops_RSSA */
				   (float)(1.0/72 *					/* _hoops_IPIHH _hoops_RIR _hoops_PPSR */
						 2.54) *					/* _hoops_SAPSR _hoops_RIR _hoops_CPIHH */
				   dc->current._hoops_HAP.y;	/* _hoops_ASPA _hoops_RIR _hoops_SPIHH */

			if (!BIT(dc->flags, _hoops_CSHSR))
				size *= HOOPS_WORLD->_hoops_IRGHP;

		}	break;

		case GSU_PIXELS: {
			_hoops_ACPAP = _hoops_HRCIR->_hoops_ACPAP;
		}	break;

		case GSU_PERCENT: {
			_hoops_ACPAP = _hoops_HRCIR->_hoops_ACPAP * size * 0.01f;
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "'size tolerance units' ?");
			_hoops_ACPAP = 0.0f;
		}	break;
	}

#	define		_hoops_SPCGGR		0.5f

	pixels = (Integer32)(size + _hoops_SPCGGR);				/* (_hoops_GIRR _hoops_GHCGGR) */
	max_height = (Integer32)(size + 0.99f + _hoops_SPCGGR);	  /* (_hoops_GIRR _hoops_GH) */
	min_height = (Integer32)(size - _hoops_ACPAP - _hoops_SPCGGR); /* (_hoops_GIRR _hoops_ISHP) */

_hoops_RHCGGR:

	specific = null;

	if (_hoops_AHHIH != null) {
		/* _hoops_HPPR _hoops_IS _hoops_SSS _hoops_IRS _hoops_HPHR _hoops_HAGAR */
		_hoops_IGPIR const	*	name = _hoops_AHHIH;
		bool				_hoops_AHCGGR;
		bool				_hoops_PHCGGR;
		float				_hoops_RAHCR;
		bool				_hoops_HARSS;
		int					tmp;

		/* _hoops_CCGR _hoops_RHPP _hoops_PAH _hoops_HHCI-_hoops_IHIS _hoops_HCGR _hoops_PCAAA, _hoops_HHSA _hoops_IIPGA _hoops_IS _hoops_RRIC */

		_hoops_AHCGGR = _hoops_HRCIR->transform == FT_FULL;

		/* _hoops_HHHR _hoops_IGAA _hoops_CCPA _hoops_HGAP _hoops_GRRRI _hoops_HCGR */
		if (_hoops_HRCIR->width_scale < 0.0f)
			_hoops_AHCGGR = true;

		_hoops_PHCGGR = BIT(nr->transform_rendition->heuristics, _hoops_HRIRP) &&
							  BIT(dc->_hoops_PGCC.flags, _hoops_APPGH);

		_hoops_RAHCR = _hoops_HRCIR->rotation;
		tmp = (int)(_hoops_RAHCR / 90.0f + 0.5f);
		_hoops_HARSS = (Abs (_hoops_RAHCR - tmp * 90.0f) <= 0.25f);

		if ((size > 16384) && (_hoops_HRCIR->transform != FT_FULL)) {
			/* _hoops_IH _hoops_HHCGGR _hoops_HCGR _hoops_HSSC _hoops_ISSC _hoops_IS _hoops_RRIC */
			specific = _hoops_RACGGR (dc, GFN_STROKED, encoding,
				max_height, min_height,
				pixels, size, _hoops_RRCGGR);
		}
		else do {
			index++;
			if (_hoops_HRCIR->fallback_index < index) {
				switch (name->_hoops_SSSGP) {
					case GFN_STROKED: {
						specific = _hoops_RACGGR (dc, name->_hoops_SSSGP, encoding,
												   max_height, min_height,
												   pixels, size, _hoops_RRCGGR);
					}	break;

					case GFN_SANS_SERIF:
					case GFN_TYPEWRITER:
					case GFN_ROMAN:
					case _hoops_GIIGI:
					case _hoops_RIIGI:
					case _hoops_AIIGI:
					case GFN_SYSTEM_DEFAULT: {
						specific = _hoops_RACGGR (dc, name->_hoops_SSSGP, encoding,
												   max_height, min_height,
												   pixels, size, _hoops_RRCGGR);
					}	break;

					case GFN_SPECIFIED: {
						_hoops_IGPIR const	*_hoops_IHCGGR = name;
						_hoops_IGPIR alter	_hoops_CHCGGR;

						if (_hoops_HRCIR->_hoops_ISPAP[0] == _hoops_ASPAP &&
							dc->_hoops_ACPGR->_hoops_CSCSP (nr, name, &_hoops_CHCGGR)) {
								_hoops_IHCGGR = &_hoops_CHCGGR;
						}

						specific = _hoops_GRCGGR (dc, &_hoops_IHCGGR->specified, encoding,
													max_height, min_height,
													pixels, size, _hoops_RRCGGR);

						if (0 && !specific &&
							(_hoops_HRCIR->_hoops_ISPAP[0] == _hoops_RSPAP ||
								_hoops_HRCIR->_hoops_ISPAP[0] == _hoops_PSPAP)) {

								if (_hoops_IHCGGR == &_hoops_CHCGGR)
									_hoops_RGAIR(_hoops_CHCGGR.specified);

								if (HD_Freetype_Name_Font (nr, name, &_hoops_CHCGGR)) {
									_hoops_IHCGGR = &_hoops_CHCGGR;

									specific = _hoops_GRCGGR (dc, &_hoops_IHCGGR->specified, encoding,
										max_height, min_height,
										pixels, size, _hoops_RRCGGR);
								}
						}

						if (_hoops_IHCGGR == &_hoops_CHCGGR)
							_hoops_RGAIR(_hoops_CHCGGR.specified);
					}	break;
				}

				/* _hoops_RIARC _hoops_PPGRR _hoops_AHSGH */
				if (specific != null &&  _hoops_HRCIR->_hoops_ISPAP[0] != _hoops_RSPAP) {
					if (_hoops_HRCIR->_hoops_ISPAP[0] == _hoops_ASPAP &&
						specific->family->_hoops_RRCSR != _hoops_CISSP)
						specific = null;
					else if (_hoops_HRCIR->_hoops_ISPAP[0] == _hoops_PSPAP &&
						specific->family->_hoops_RRCSR != _hoops_SISSP)
						specific = null;
					else if (_hoops_HRCIR->_hoops_ISPAP[0] == _hoops_HSPAP &&
						specific->family->_hoops_RRCSR != _hoops_ARCSR)
						specific = null;
				}

				/* _hoops_SR _hoops_GHCA _hoops_RRP _hoops_IS _hoops_HSGR _hoops_RGR _hoops_SPR _hoops_PPR _hoops_SSS _hoops_HPIH _hoops_HRCSR */
				if (specific != null &&
					specific->family->_hoops_RRCSR == _hoops_CISSP) {
					/* _hoops_SR _hoops_SPGA'_hoops_RA _hoops_GRP _hoops_RGR _hoops_IHH _hoops_HPCS _hoops_PIH _hoops_HA */
					int _hoops_SHCGGR = 0;

					if (_hoops_PHCGGR)
						_hoops_SHCGGR |= _hoops_GPCGGR;

					if (_hoops_AHCGGR && !ANYBIT (specific->_hoops_CAGGH, _hoops_AAGGH|_hoops_PAGGH))
						_hoops_SHCGGR |= _hoops_HACGGR;

					if ((!ANYBIT (specific->_hoops_CAGGH, _hoops_GPCSR|_hoops_SRGGH) &&
						 _hoops_RAHCR != 0.0f) ||
						(BIT (specific->_hoops_CAGGH, _hoops_SRGGH) && !_hoops_HARSS))
						_hoops_SHCGGR |= _hoops_IACGGR;

					if (!BIT (specific->_hoops_CAGGH, _hoops_RAGGH) && _hoops_HRCIR->_hoops_IPGRP != 0.0f)
						_hoops_SHCGGR |= _hoops_CACGGR;

					if (!BIT (specific->_hoops_CAGGH, _hoops_GAGGH) && _hoops_HRCIR->width_scale != 1.0f)
						_hoops_SHCGGR |= _hoops_SACGGR;

					if (_hoops_SHCGGR) {
						specific = null;
					}
				}
			}
		} while (specific == null && (name = name->next) != null);
	}

	if (!HOOPS_WORLD->_hoops_RAGHP) {
		if (!specific && !dc->_hoops_HSAGH) {
			/* _hoops_HPPR _hoops_GICS _hoops_CCA _hoops_HCR _hoops_HRCSR _hoops_GAAPH */
			HD_Find_All_Fonts (dc);
			index=0;
			goto _hoops_RHCGGR;
		}
	}

	if (!specific && _hoops_RPCGGR &&
		dc->options._hoops_SAPIR != null) {

		_hoops_AHHIH = dc->options._hoops_SAPIR;

		_hoops_RPCGGR=false;
		goto _hoops_RHCGGR;
	}

	if (!specific) {		/* _hoops_SGH _hoops_RH _hoops_RRIC _hoops_HRCSR */
		specific = _hoops_RACGGR (dc, GFN_STROKED, encoding,
								   max_height, min_height,
								   pixels, size, _hoops_RRCGGR);

		if (specific != null)
			_hoops_PRPSP = true;
	}

	if (specific && specific->_hoops_ISISR == 0.0f && size != 0) {
		float			_hoops_IGGGH, _hoops_ISISR;

		/* _hoops_GICGGR _hoops_PPR _hoops_PRHPA _hoops_GGRRR: _hoops_RIPHR _hoops_IRS _hoops_CCAH _hoops_HAGAR */

		/* _hoops_RH '0' _hoops_HAGAR'_hoops_GRI '_hoops_GCISC' _hoops_HRGR _hoops_IGRC _hoops_RH _hoops_GCISC/_hoops_PSSSP *_hoops_AHHSR* */
		if (_hoops_RRCGGR) {
			_hoops_IGGGH = size;
			_hoops_ISISR = _hoops_IGGGH / specific->_hoops_IGGGH;
		}
		else {
			_hoops_ISISR = size;
			_hoops_IGGGH = _hoops_ISISR * specific->_hoops_IGGGH;
		}

		specific = HD_Record_Scaleable_Instance (dc, specific, _hoops_ISISR, _hoops_IGGGH);
	}

	/* _hoops_CISA _hoops_GGR _hoops_ISCP _hoops_ASRC _hoops_PIRA */
	_hoops_IRRIP->font = specific;
	_hoops_IRRIP->fallback_index = index;
	_hoops_IRRIP->_hoops_PRPSP = _hoops_PRPSP;

	if (specific) {
		Font_Instance alter	*_hoops_GGHCS = (Font_Instance alter *)specific;
		_hoops_PACGGR(_hoops_GGHCS, dc);
		(*_hoops_GGHCS->_hoops_SSCSP)(nr, _hoops_GGHCS);
	}
}



#define _hoops_RICGGR(x)	(float)_hoops_IRGCR(x)


GLOBAL_FUNCTION void * HD_Load_Defined_Font (
	Display_Context const *dc,
	char const *name,
	Font_Instance alter *instance) {
#ifdef DISABLE_DEFINED_FONTS
	_hoops_IRPPR ("Defined Fonts");
	return 0;
#else
	_hoops_PGIIR alter * font = (_hoops_PGIIR alter *)instance->family->font;

	UNREFERENCED (dc);
	UNREFERENCED (name);
	UNREFERENCED (instance);

	/* _hoops_GAR _hoops_RIRA _hoops_GAR _hoops_PA, _hoops_PPR _hoops_HSGS */
	return font;
#endif
}

GLOBAL_FUNCTION void HD_Unload_Defined_Font (
	Display_Context const *dc,
	Font_Instance alter *instance) {
#ifdef DISABLE_DEFINED_FONTS
	_hoops_IRPPR ("Defined Fonts");
#else

	UNREFERENCED (dc);
	UNREFERENCED (instance);
#endif
}

GLOBAL_FUNCTION bool HD_Unload_Oldest_Font (
	Display_Context alter	*dc,
	int		_hoops_GSHIH) {

	Font_Instance alter * instance = (Font_Instance alter *)dc->_hoops_HRHGH[_hoops_GSHIH];
	Font_Instance alter ** _hoops_ASRGR= (Font_Instance alter **)&dc->_hoops_HRHGH[_hoops_GSHIH];

	if (!instance)
		return false;

	while (instance->next) {
		_hoops_ASRGR = (Font_Instance alter **)&instance->next;
		instance = (Font_Instance alter *)instance->next;
	}

	(*instance->unload_font)(dc, instance);

	if (instance->_hoops_RGPIP) {
		FREE_ARRAY (instance->_hoops_RGPIP, _hoops_HGGGH, _hoops_SCSSP);
	}
	instance->_hoops_RGPIP=0;
	instance->_hoops_GAASR = 0;
	instance->_hoops_CGCSR = false;
	instance->next = null;

	dc->_hoops_PRHGH[_hoops_GSHIH]--;
	*_hoops_ASRGR = null;

	return true;
}


GLOBAL_FUNCTION bool HD_Load_Font (
	Display_Context const		*_hoops_CSIGGR,
	Font_Instance const			*_hoops_SIHIH) {
	char const					*_hoops_AICGGR;
	Font_Instance alter			*instance;
	Display_Context alter		*dc = (Display_Context alter *)_hoops_CSIGGR;
	int							_hoops_GSHIH=_hoops_SIHIH->family->_hoops_RRCSR;
	unsigned int				_hoops_PICGGR=0;

	instance = (Font_Instance alter *)_hoops_SIHIH;

	if (instance->_hoops_CGCSR) {
		Font_Instance alter * _hoops_HICGGR = (Font_Instance alter *)dc->_hoops_HRHGH[_hoops_GSHIH];
		Font_Instance alter ** _hoops_ASRGR= (Font_Instance alter **)&dc->_hoops_HRHGH[_hoops_GSHIH];

		/* _hoops_IHIS _hoops_HAGAR _hoops_IS _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_CISI _hoops_HIGR */
		while (instance != _hoops_HICGGR) {
			_hoops_ASRGR = (Font_Instance alter **)&_hoops_HICGGR->next;
			_hoops_HICGGR = (Font_Instance alter *)_hoops_HICGGR->next;
		}

		if (instance != dc->_hoops_HRHGH[_hoops_GSHIH]) {
			/*_hoops_HSRPA _hoops_GGSR _hoops_PPR _hoops_IHIS _hoops_IS _hoops_RH _hoops_HARS _hoops_IIGR _hoops_RH _hoops_HIGR*/
			*_hoops_ASRGR=(Font_Instance alter *)instance->next;
			instance->next=dc->_hoops_HRHGH[_hoops_GSHIH];
			dc->_hoops_HRHGH[_hoops_GSHIH]=instance;
		}

		return true;
	}

	if (instance->_hoops_PRGGH) return false;	/* _hoops_IHGSR _hoops_SHS _hoops_AIAH _hoops_IICGGR _hoops_SCH */

	if (instance->name.length != 0)
		_hoops_AICGGR = instance->name.text;
	else {
		_hoops_AICGGR = instance->family->name.text;

		/* _hoops_ISPR _hoops_IH _hoops_PHPPR */
		if (instance->family->_hoops_ICSSP) {
			if (instance->family->_hoops_ICSSP->_hoops_SAGGH.length != 0)
				_hoops_AICGGR = instance->family->_hoops_ICSSP->_hoops_SAGGH.text;
		}
	}

	if (!instance->_hoops_RGPIP)
		ALLOC_ARRAY_CACHED(instance->_hoops_RGPIP, _hoops_HGGGH, _hoops_SCSSP);

	/*_hoops_SCAC _hoops_GAS _hoops_PIH*/
	ZERO_ARRAY(instance->_hoops_RGPIP, _hoops_HGGGH, _hoops_SCSSP);

#define _hoops_CICGGR 128
#define _hoops_SICGGR 128
#define _hoops_GCCGGR 128

	_hoops_PACGGR(instance, dc);
	switch (_hoops_GSHIH) {
#ifndef DISABLE_DEFINED_FONTS
		case _hoops_ARCSR:
			_hoops_PICGGR = _hoops_CICGGR;
			break;
#endif
		case _hoops_CISSP:
			_hoops_PICGGR = _hoops_SICGGR;
			break;
#ifdef FREETYPE
		case _hoops_SISSP:
			_hoops_PICGGR = _hoops_GCCGGR;
			break;
#endif
	}

	while (dc->_hoops_PRHGH[_hoops_GSHIH] >= _hoops_PICGGR)
		HD_Unload_Oldest_Font (dc, _hoops_GSHIH);

	_hoops_PCCAR {

		if (!instance->_hoops_CGCSR) {
			instance->_hoops_GAASR = (*instance->load_font)(dc, _hoops_AICGGR, instance);

			/* _hoops_GGHP _hoops_SCH _hoops_PGGGH */
			if (instance->_hoops_GAASR) {
				if (instance->_hoops_ISISR < 0.0f || instance->_hoops_IGGGH < 0.0f) {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Driver load_font failed to return Aheight or vspace");
					(*instance->unload_font)(dc, instance);
					if (instance->_hoops_RGPIP) {
						FREE_ARRAY (instance->_hoops_RGPIP, _hoops_HGGGH, _hoops_SCSSP);
					}
					instance->_hoops_RGPIP = 0;
					instance->_hoops_GAASR = 0;
					instance->_hoops_CGCSR = false;
					instance->_hoops_PRGGH = true;
					instance->next = null;
					return false;
				}
				else {
					instance->_hoops_CGCSR = true;
					break;
				}
			}
		}

		/* _hoops_CSISS _hoops_RRI _hoops_PPR _hoops_RRI _hoops_CCGR _hoops_HCR _hoops_CHR _hoops_PPRGA */
		if (!HD_Unload_Oldest_Font (dc, _hoops_GSHIH)) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, Sprintf_SD (null,
				"Unable to load font '%s', size %d", _hoops_AICGGR, (int)instance->_hoops_IGGGH));

			if (instance->_hoops_RGPIP) {
				FREE_ARRAY (instance->_hoops_RGPIP, _hoops_HGGGH, _hoops_SCSSP);
			}
			instance->_hoops_RGPIP = 0;
			instance->_hoops_CGCSR = false;
			instance->_hoops_PRGGH = true;
			instance->next = null;
			return false;
		}
	}

	/* _hoops_GGCR _hoops_IS _hoops_RH _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_CISI _hoops_HIGR */
	instance->next=dc->_hoops_HRHGH[_hoops_GSHIH];
	dc->_hoops_HRHGH[_hoops_GSHIH]=instance;
	dc->_hoops_PRHGH[_hoops_GSHIH]++;

	return true;
}


/* _hoops_RH _hoops_HSPR _hoops_HRGR _hoops_IH _hoops_RH _hoops_RCCGGR _hoops_SGH _hoops_IIGR _hoops_RH _hoops_ACCGGR _hoops_RHPP */
GLOBAL_FUNCTION void HD_Force_Font_Load (
	Net_Rendition const &		nr) {
	Display_Context alter *		dc = (Display_Context alter*)nr->_hoops_SRA;
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	char const *				_hoops_AICGGR;
	Font_Instance alter *		instance = (Font_Instance alter *)_hoops_HRCIR->font;
	int							_hoops_RRCSR = instance->family->_hoops_RRCSR;

	if (instance->name.length != 0)
		_hoops_AICGGR = instance->name.text;
	else
		_hoops_AICGGR = instance->family->name.text;

	if (!instance->_hoops_RGPIP)
		ALLOC_ARRAY (instance->_hoops_RGPIP, _hoops_HGGGH, _hoops_SCSSP);

	/*_hoops_SCAC _hoops_GAS _hoops_PIH*/
	ZERO_ARRAY(instance->_hoops_RGPIP, _hoops_HGGGH, _hoops_SCSSP);

	instance->load_font = dc->_hoops_ACPGR->load_font;
	instance->unload_font = dc->_hoops_ACPGR->unload_font;
	instance->measure_char= dc->_hoops_ACPGR->measure_char;

	instance->_hoops_GAASR = (*dc->_hoops_ACPGR->load_font) (dc, _hoops_AICGGR, instance);

	/* _hoops_GGCR _hoops_IS _hoops_RH _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_CISI _hoops_HIGR */
	instance->next = dc->_hoops_HRHGH[_hoops_RRCSR];
	dc->_hoops_HRHGH[_hoops_RRCSR] = instance;
	++dc->_hoops_PRHGH[_hoops_RRCSR];
}


GLOBAL_FUNCTION void HD_Unload_All_Fonts (
	Display_Context alter *		dc) {

	while (HD_Unload_Oldest_Font (dc, _hoops_ARCSR));

	while (HD_Unload_Oldest_Font (dc, _hoops_CISSP));

	while (HD_Unload_Oldest_Font (dc, _hoops_SISSP));
}




#define _hoops_RICGGR(x)	(float)_hoops_IRGCR(x)
#define _hoops_CARSS 1024

/*_hoops_PCCGGR _hoops_HCCGGR _hoops_RGGCI _hoops_GRAPR _hoops_ICCGGR _hoops_ICRHR _hoops_CCCGGR*/
/*_hoops_PCCGGR _hoops_RCAAA _hoops_RGGCI _hoops_ISHIP _hoops_SCCGGR _hoops_ISCC _hoops_CCCGGR*/

GLOBAL_FUNCTION bool HD_Measure_Characters (
	Net_Rendition const &		nr,
	int							count,
	Karacter const *			_hoops_AARPS,
	_hoops_IHGRP const			_hoops_GSCGGR,
	float *						_hoops_GGGS) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	Display_Context const *		dc = nr->_hoops_SRA;
	bool						_hoops_PSHIH = false;
	Karacter const *			_hoops_IHSCP;
	Karacter *					_hoops_GPRSS = 0;
	Karacter					_hoops_SARSS[_hoops_CARSS];
	_hoops_IHGRP				encoding = _hoops_GSCGGR;
	Font_Instance const *		instance;
	int							n = 0;

	*_hoops_GGGS = 0.0f;

	if (!_hoops_HRCIR->font->_hoops_CGCSR)
		HD_Load_Font (dc, _hoops_HRCIR->font);

	if (encoding != _hoops_HRCIR->font->encoding &&
		HI_Encoding_Is_Compatible(encoding, _hoops_HRCIR->font->encoding) == _hoops_ACIGI) {
		/*_hoops_CGH _hoops_RGAR _hoops_SHH _hoops_CPRSS _hoops_PAR _hoops_SPRSS */

		if (count > _hoops_CARSS) {
			ALLOC_ARRAY(_hoops_GPRSS, count, Karacter);
			_hoops_IHSCP = _hoops_GPRSS;
		}
		else
			_hoops_IHSCP = _hoops_SARSS;

		HI_Convert_Karacters_Encoding (count, _hoops_AARPS, (Karacter*) _hoops_IHSCP, encoding, _hoops_HRCIR->font->encoding);
	}
	else
		_hoops_IHSCP = _hoops_AARPS;

	encoding = _hoops_HRCIR->font->encoding;

	n = 0;
	instance = _hoops_HRCIR->font;

	while (n < count) {
		Karacter _hoops_CSAIP;
		_hoops_SCSSP *_hoops_RGPIP;
		float _hoops_RSCGGR = 0.0f;

		if (encoding == _hoops_SSAIP)
			_hoops_CSAIP = _hoops_IHSCP[n]&0x00FF;
		else
			_hoops_CSAIP = _hoops_IHSCP[n];

		_hoops_RGPIP = &instance->_hoops_RGPIP[_hoops_GGPIP(_hoops_CSAIP)];

		/* _hoops_HRGR _hoops_IGAA _hoops_PIAH? */
		if (_hoops_RGPIP->valid <= 0 ||
			_hoops_RGPIP->_hoops_CSAIP != _hoops_CSAIP ||
			_hoops_RGPIP->_hoops_HSSSP != instance->_hoops_RACSR ||
			(_hoops_RGPIP->_hoops_ASRIP == 1) != _hoops_HRCIR->_hoops_ASRIP) {

			bool _hoops_CPCSR = false;
			void * _hoops_SPCSR = 0;
			float _hoops_RAPPI = 0.0f;

			_hoops_RGPIP->_hoops_HSSSP = instance->_hoops_RACSR;

			(*instance->measure_char)(nr, instance, _hoops_CSAIP, &_hoops_RAPPI, &_hoops_CPCSR, &_hoops_SPCSR);

			_hoops_RGPIP->valid = 1;
			_hoops_RGPIP->_hoops_CSAIP = _hoops_CSAIP;
			_hoops_RGPIP->_hoops_ASSSP = _hoops_RAPPI;
			_hoops_RGPIP->_hoops_RSSSP = 0;
			_hoops_RGPIP->_hoops_CSSSP = 0;
			_hoops_RGPIP->data = _hoops_SPCSR;
			_hoops_RGPIP->_hoops_ASRIP = _hoops_HRCIR->_hoops_ASRIP;

			if (_hoops_CPCSR) {
				/* _hoops_ARCPC _hoops_RAIGR _hoops_ASCGGR _hoops_CGHGH _hoops_HSRRH _hoops_GISIP _hoops_SCCGGR */
				Font_Instance const *	_hoops_RSSSP = null;
				Karacter				_hoops_CIHIH = 0;

				if ((_hoops_RSSSP = HD_Find_Fill_In_Font (nr, _hoops_HRCIR->font, _hoops_IHSCP[n], &_hoops_CIHIH)) != null) {
					Net_Rendition			_hoops_AHRSS = nr;
					_hoops_IGCSR alter &	_hoops_PSCGGR = _hoops_AHRSS.Modify()->_hoops_SISI.Modify();

					_hoops_PSCGGR->font = _hoops_RSSSP;
					_hoops_AHRSS->_hoops_SISI = _hoops_PSCGGR;

					HD_Measure_Characters (_hoops_AHRSS, 1, &_hoops_CIHIH, _hoops_RSSSP->encoding, &_hoops_RAPPI);

					_hoops_RGPIP->_hoops_ASSSP = _hoops_RAPPI;
					_hoops_RGPIP->_hoops_RSSSP = _hoops_RSSSP;
					_hoops_RGPIP->_hoops_CSSSP = _hoops_CIHIH;
				}
				else {
					/*_hoops_SIGP _hoops_RGR _hoops_PIHA _hoops_SHH _hoops_GIR _hoops_PAR _hoops_IIP _hoops_IHPS*/
				}
			}
		}

		_hoops_RSCGGR = _hoops_RGPIP->_hoops_ASSSP;

		if (_hoops_RGPIP->_hoops_RSSSP)
			_hoops_PSHIH = true;

		if (_hoops_RGPIP->_hoops_RSSSP)
			*_hoops_GGGS += _hoops_RSCGGR * _hoops_RGPIP->_hoops_RSSSP->_hoops_GCHSA;
		else {
			float _hoops_HSCGGR = _hoops_RSCGGR;

			*_hoops_GGGS += _hoops_HSCGGR * instance->_hoops_GCHSA;
		}

		n++;
	}

	if (_hoops_GPRSS)
		FREE_ARRAY(_hoops_GPRSS, count, Karacter);

	return _hoops_PSHIH;
}


GLOBAL_FUNCTION bool HD_Measure_Defined_Char (
	Net_Rendition const & nr,
	Font_Instance const *instance,
	unsigned short _hoops_IPCSR,
	float alter *_hoops_GGGS,
	bool alter *_hoops_CPCSR,
	void ** _hoops_SPCSR) {
#ifdef DISABLE_DEFINED_FONTS
		_hoops_IRPPR ("Defined Fonts");
#else
	_hoops_PGIIR const		*font = instance->family->font;
	int n = 0;
	float _hoops_PRPHA;
	char const		*tmp;
	Karacter _hoops_CSAIP;

	UNREFERENCED (nr);

	*_hoops_GGGS = 0.0f;
	*_hoops_SPCSR = 0;


	if (font->encoding == _hoops_SSAIP)
		_hoops_CSAIP = _hoops_IPCSR&0x00FF;
	else
		_hoops_CSAIP = _hoops_IPCSR;

	if (font->_hoops_HGIIR != null) {
		(*((_hoops_CAHAP)font->_hoops_HGIIR->address)) (font->name.text, font->data, _hoops_CSAIP, &tmp);
	}
	else if (font->encoding == _hoops_SSAIP) {
		tmp = font->_hoops_CGIIR[_hoops_CSAIP];
	}
	else {
		/* _hoops_PSHPR _hoops_GIPHR */
		char const * const *	low;
		char const * const *	high;
		char const * const *	_hoops_SPGIR;
		int						index = _hoops_CSAIP;

		tmp = null;				/* _hoops_GGR _hoops_AGIR _hoops_PIRC _hoops_GSGI */
		low = &font->_hoops_CGIIR[0];
		high = low + font->_hoops_IGIIR -1;

		if (index <= _hoops_SPHAP(*high) &&
				index>= _hoops_SPHAP(*low)) {
			_hoops_SPGIR = low + (high - low)/2;

			while (high >= low) {
				int _hoops_AGPIP = _hoops_SPHAP (*_hoops_SPGIR);

				if (_hoops_AGPIP == index)	 {
					tmp = *_hoops_SPGIR;
					break;
				}
				else if (_hoops_AGPIP > index)
					high = _hoops_SPGIR - 1;
				else
					low = _hoops_SPGIR + 1;
				_hoops_SPGIR = low + (high - low)/2;
			}
		}
	}

	/*_hoops_ASRC _hoops_RH _hoops_RHSAR _hoops_HIIA _hoops_GH _hoops_PIH _hoops_IH _hoops_SRS _hoops_GAS _hoops_RGAR*/
	/*_hoops_RGR _hoops_CGH _hoops_SHH _hoops_RHSI _hoops_CGPR _hoops_RII _hoops_PSCH _hoops_CHR _hoops_HGAS _hoops_IS _hoops_PSISC*/
	/* _hoops_RGAR _hoops_SPR _hoops_GAS _hoops_GAAP*/
	if (n == 0)
		*_hoops_SPCSR = (void *)tmp;

	if (tmp != null) {
		++tmp;
		if (font->encoding != _hoops_SSAIP) ++tmp;

		_hoops_PRPHA = (_hoops_RICGGR (*tmp) + _hoops_RICGGR (font->data[3])) / _hoops_RICGGR (font->data[1]);
		_hoops_PRPHA *= font->_hoops_CSIH;

		*_hoops_GGGS += instance->_hoops_RACSR * _hoops_PRPHA;

		*_hoops_CPCSR = false;
	}
	else {
		*_hoops_CPCSR = true;
	}

#endif
	return true;
}


GLOBAL_FUNCTION Font_Instance const * HD_Find_Fill_In_Font (
	Net_Rendition const &		in_nr,
	Font_Instance const *		_hoops_HIHIH,
	Karacter					_hoops_ISCGGR,
	Karacter alter *			_hoops_RHRSS) {
	Net_Rendition				nr = in_nr;
	_hoops_IGCSR const &		_hoops_HRCIR = in_nr->_hoops_SISI;
	_hoops_IGPIR					_hoops_RCPPI;
	Font_Instance const	*		_hoops_CSCGGR = 0;
	float						_hoops_RAPPI;

	_hoops_RAPPI = 0.0f;

	if (!_hoops_HRCIR->_hoops_PRPSP) {
		/* _hoops_HPPR _hoops_RHPP _hoops_IIPGA _hoops_GSPIP */
		_hoops_IGCSR alter &	_hoops_SSCGGR = nr.Modify()->_hoops_SISI.Modify();
		// _hoops_PAH'_hoops_RA _hoops_SGH _hoops_PRGSI() _hoops_PGGA _hoops_GGSGGR _hoops_PIHA _hoops_HAR _hoops_SHH _hoops_HIAP
		_hoops_SSCGGR->font = null;

		HD_Choose_Font (nr, _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR, _hoops_HIHIH->encoding, true);

		_hoops_CSCGGR = _hoops_SSCGGR->font;

		if (_hoops_CSCGGR && _hoops_CSCGGR->family == _hoops_HIHIH->family) _hoops_CSCGGR=0;

		if (_hoops_CSCGGR) {
			if (!_hoops_CSCGGR->_hoops_CGCSR)
				HD_Load_Font (nr->_hoops_SRA, _hoops_CSCGGR);

			/* _hoops_PAAP _hoops_RH _hoops_SCGR _hoops_HRCSR _hoops_HPHS */
			{
				Font_Instance alter* _hoops_GGHCS = (Font_Instance alter*)_hoops_CSCGGR;

				(*_hoops_GGHCS->_hoops_SSCSP)(nr, _hoops_GGHCS);
			}

			if (HI_Encoding_Is_Compatible(_hoops_HIHIH->encoding, _hoops_CSCGGR->encoding) == _hoops_ACIGI) {
				HI_Convert_Karacters_Encoding(1, &_hoops_ISCGGR, _hoops_RHRSS, _hoops_HIHIH->encoding, _hoops_CSCGGR->encoding);
			}
			else
				*_hoops_RHRSS = _hoops_ISCGGR;

			if (HD_Measure_Characters (nr, 1, _hoops_RHRSS, _hoops_CSCGGR->encoding, &_hoops_RAPPI)) _hoops_CSCGGR=0;
		}
	}

	/* _hoops_HHSA _hoops_IRS _hoops_AHCRR -- _hoops_IRHS _hoops_IPHR _hoops_ASIGA*/
	if (!_hoops_CSCGGR) {
		_hoops_RCPPI.specified.length = 0;
		_hoops_RCPPI.next = null;
		_hoops_RCPPI._hoops_SSSGP = GFN_STROKED;

		_hoops_IGCSR alter &	_hoops_SSCGGR = nr.Modify()->_hoops_SISI.Modify();
		_hoops_SSCGGR->transform = FT_NONE;
		_hoops_SSCGGR->_hoops_PHP = (float)_hoops_HRCIR->font->_hoops_ISISR;
		_hoops_SSCGGR->_hoops_GHGRP = GSU_PIXELS;
		_hoops_SSCGGR->_hoops_ACPAP = 0.0f;
		_hoops_SSCGGR->_hoops_SSPAP = GSU_PERCENT;
		_hoops_SSCGGR->_hoops_SRRIP();

		HD_Choose_Font (nr, &_hoops_RCPPI, _hoops_SACSR, true);

		_hoops_CSCGGR = _hoops_SSCGGR->font;

		if (_hoops_CSCGGR) {
			if (!_hoops_CSCGGR->_hoops_CGCSR)
				HD_Load_Font (nr->_hoops_SRA, _hoops_CSCGGR);

			/* _hoops_PAAP _hoops_RH _hoops_SCGR _hoops_HRCSR _hoops_HPHS */
			{
				Font_Instance alter* _hoops_GGHCS = (Font_Instance alter*)_hoops_CSCGGR;

				(*_hoops_GGHCS->_hoops_SSCSP)(nr, _hoops_GGHCS);
			}


			if (_hoops_CSCGGR->family == _hoops_HIHIH->family) {
				/*_hoops_SGPIP _hoops_GRPIP*/
				*_hoops_RHRSS = 0x0000;
			}
			else {
				if (HI_Encoding_Is_Compatible(_hoops_HIHIH->encoding, _hoops_CSCGGR->encoding) == _hoops_ACIGI) {
					HI_Convert_Karacters_Encoding(1, &_hoops_ISCGGR, _hoops_RHRSS, _hoops_HIHIH->encoding, _hoops_CSCGGR->encoding);
				}
				else
					*_hoops_RHRSS = _hoops_ISCGGR;

				if (HD_Measure_Characters (nr, 1, _hoops_RHRSS, _hoops_CSCGGR->encoding, &_hoops_RAPPI)) {
					/*_hoops_SGPIP _hoops_GRPIP*/
					*_hoops_RHRSS = 0x0000;
				}
			}
		}

		_hoops_RGAIR (_hoops_RCPPI.specified);
	}

	return _hoops_CSCGGR;
}



GLOBAL_FUNCTION void HD_Record_Font (
	Display_Context const		*dc,
	char const				*_hoops_HSHIH,
	char const				*_hoops_ISHIH,
	float					_hoops_ISISR,
	float					_hoops_IGGGH) {

	HD_Record_Font_With_Encoding (dc, _hoops_HSHIH, _hoops_ISHIH,
								  _hoops_SSAIP, _hoops_ISISR, _hoops_IGGGH);
}


local _hoops_SHSSP alter * _hoops_RGSGGR (
	Display_Context const	*dc,
	char const					*string,
	_hoops_SHSSP alter			* alter * alter *_hoops_PGPAS,
	_hoops_HCRPR alter				*name) {
	_hoops_SHSSP alter			*_hoops_GSIGGR;

	{	char const		*_hoops_RPPA = string;
		int				_hoops_ARAHR = 0;
		local			const char		sans_serif[] = "sans serif",
										typewriter[] = "typewriter",
										roman[] = "roman",
										stroked[] = "stroked";

		do _hoops_ARAHR += _hoops_SHPCR (*_hoops_RPPA);
		_hoops_RGGA (*++_hoops_RPPA == '\0');

		name->length = _hoops_RPPA - string;
		name->text = (char alter *)string;

		if ((_hoops_ARAHR == 's'+'a'+'n'+'s'+' '+'s'+'e'+'r'+'i'+'f' &&
			 _hoops_IGGPA (string, sans_serif)) ||
			(_hoops_ARAHR == 't'+'y'+'p'+'e'+'w'+'r'+'i'+'t'+'e'+'r' &&
			 _hoops_IGGPA (string, typewriter)) ||
			(_hoops_ARAHR == 'r'+'o'+'m'+'a'+'n' &&
			 _hoops_IGGPA (string, roman)) ||
			(_hoops_ARAHR == 's'+'t'+'r'+'o'+'k'+'e'+'d' &&
			 _hoops_IGGPA (string, stroked))) {
#			ifdef _hoops_CGSPR
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "The requested font name is reserved");
#			endif
			name->length = 0;
			return null;
		}

		/* (_hoops_RH _hoops_HIIC _hoops_HRGR _hoops_ICIC) */
		*_hoops_PGPAS = (_hoops_SHSSP alter * alter *)&dc->_hoops_GRHGH[_hoops_ARAHR & (_hoops_HHRSP - 1)];

		if ((_hoops_GSIGGR = **_hoops_PGPAS) == null)
			return null;
	}

	do {
		if (_hoops_GSIGGR->name.length == name->length) {
			char const		*a = string;
			char const		*b = _hoops_GSIGGR->name.text;

			while (_hoops_SHPCR(*a) == _hoops_SHPCR(*b)) {
				++a, ++b;
				if (*b == '\0') return _hoops_GSIGGR;	/* _hoops_GGHP _hoops_IRS _hoops_PSSP */
			}
		}
		*_hoops_PGPAS = &_hoops_GSIGGR->_hoops_SSCAP;
	} while ((_hoops_GSIGGR = _hoops_GSIGGR->_hoops_SSCAP) != null);

	return null;
}


local _hoops_SHSSP alter *_hoops_AGSGGR (
	Display_Context const	*dc,
	char const					*name) {
	_hoops_SHSSP alter			* alter *_hoops_PGSGGR;
	_hoops_HCRPR						_hoops_HGSGGR;

	if (*name == '\0') {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Null name passed to Mark_Font");
		return null;
	}

	return _hoops_RGSGGR (dc, name, &_hoops_PGSGGR, &_hoops_HGSGGR);
}

//#_hoops_PPIP _hoops_IGSGGR
#ifdef _hoops_CGSGGR
#include <stdio.h>
static FILE *_hoops_SGSGGR=NULL;
#endif

GLOBAL_FUNCTION void HD_Record_Font_With_Encoding (
	Display_Context const	*dc,
	char const				*_hoops_HSHIH,
	char const				*_hoops_ISHIH,
	_hoops_IHGRP			encoding,
	float					_hoops_ISISR,
	float					_hoops_IGGGH) {
	_hoops_HCRPR					_hoops_GRSGGR;
	_hoops_HCRPR					family_name;
	_hoops_RCSSP alter		*family;
	Font_Instance alter		*instance;
	Font_Instance alter		* alter *_hoops_RRSGGR;
	_hoops_SHSSP alter			* alter *_hoops_ARSGGR;
	_hoops_SHSSP alter			* alter *_hoops_PRSGGR=0;

	if (_hoops_HSHIH == null)
		_hoops_HSHIH = "";	 /* _hoops_PSRCA */
	if (_hoops_ISHIH == null)
		_hoops_ISHIH = ""; /* _hoops_PSRCA */

#ifdef _hoops_CGSGGR
	if (_hoops_SGSGGR == NULL)
		_hoops_SGSGGR = fopen("dfile.txt", "w+");
	fprintf(_hoops_SGSGGR,"%s %s\n", _hoops_HSHIH, _hoops_ISHIH);
	fflush(_hoops_SGSGGR);
#endif

	if (*_hoops_HSHIH == '\0') { /* _hoops_SHH _hoops_AGAPR, _hoops_SGH _hoops_RH _hoops_SASI _hoops_RSIRR */
		if (*_hoops_ISHIH == '\0') {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "At least one of the two names must be given!");
			return;
		}
		_hoops_HSHIH = _hoops_ISHIH;
		_hoops_ISHIH = "";
	}

	if (_hoops_ISISR < -1.0f) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "'Aheight' is less than -1");
		return;
	}
	else if (_hoops_ISISR == -1.0f) {
		if (*_hoops_ISHIH == '\0') {
			_hoops_IISCP (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"If the font size determination is deferred until later (Aheight=-1),",
								"a 'specific_name' must be given.");
			return;
		}
		if (_hoops_IGGGH != -1.0f) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "If 'Aheight' is equal to -1, 'vspace' should be too");
			return;
		}
	}
	else if (_hoops_ISISR == 0.0f) {
		if (*_hoops_ISHIH != '\0') {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "A scaleable font (Aheight=0) should not have a 'specific' name");
			return;
		}
	}
	else /* _hoops_HRSGGR > 0 */ {
		if (_hoops_IGGGH < _hoops_ISISR) {
#			ifdef _hoops_CGSPR
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Vspace must be >= Aheight");
#			endif
			return;
		}
	}

	family = (_hoops_RCSSP alter *)_hoops_RGSGGR (dc, _hoops_HSHIH,
											   &_hoops_ARSGGR, &family_name);
	if (family_name.length == 0)
		return; /* '_hoops_SSS' _hoops_RIAGR _hoops_PCCP _hoops_RIHH */

	if (*_hoops_ISHIH == '\0')
		_hoops_GRSGGR.length = 0;
	else {
		_hoops_SHSSP const		*_hoops_PPIHA;

		if ((_hoops_PPIHA = _hoops_RGSGGR (dc, _hoops_ISHIH,
										&_hoops_PRSGGR, &_hoops_GRSGGR)) != null) {
			/* _hoops_GHCA _hoops_SAHR _hoops_SHH _hoops_IRS _hoops_SSRS */

			switch (_hoops_PPIHA->type) {
				case _hoops_RISSP: {
					Font_Instance const * instance = (Font_Instance const *)_hoops_PPIHA;
					if (instance->_hoops_ISISR == _hoops_ISISR &&
						instance->_hoops_ISISR == _hoops_IGGGH &&
						instance->encoding == encoding)
						return;
				}	break;

				case _hoops_GISSP: {
					Font_Instance const	*_hoops_IRSGGR;

					if ((_hoops_IRSGGR = ((_hoops_RCSSP const *)_hoops_PPIHA)->_hoops_ICSSP) != null) do {
						if (_hoops_IRSGGR->_hoops_ISISR == _hoops_ISISR &&
							_hoops_IRSGGR->_hoops_ISISR == _hoops_IGGGH &&
							_hoops_IRSGGR->encoding == encoding)
							return;
					} while ((_hoops_IRSGGR = _hoops_IRSGGR->_hoops_SSSSP) != null);
				}	break;
			}

			/* _hoops_HAR _hoops_RH _hoops_PSHR _hoops_SPR _hoops_SR _hoops_GGHP _hoops_ARPP */

#			ifdef _hoops_CGSPR
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   Sprintf_S (null,
								   "Specific name '%s' has already been used",
								   _hoops_ISHIH));
#			endif
			return;
		}
		if (_hoops_GRSGGR.length == 0) return; /* '_hoops_SSS' _hoops_RIAGR _hoops_PCCP _hoops_RIHH */

		if (_hoops_ARSGGR == _hoops_PRSGGR && /* (_hoops_HHCI _hoops_PSCR _hoops_HIAC _hoops_PCR) */
			_hoops_IGGPA (family_name.text, _hoops_GRSGGR.text)) {
			/* _hoops_SHH _hoops_AGAPR - _hoops_RH _hoops_PSHR _hoops_RSIRR _hoops_CSAP _hoops_CGI _hoops_GGR _hoops_IH _hoops_GIPR */
			_hoops_GRSGGR.length = 0;
		}
	}

	if (family != null) {
		if (family->type != _hoops_GISSP) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "That family name was previously used as a 'specific' name");
			return;
		}

		if (family->_hoops_PCSSP) {
			if (_hoops_ISISR == 0.0f) {
#				ifdef _hoops_CGSPR
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									   "Scaleable (Aheight=0) font already declared");
#				endif
			}
			else
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "Can't add a different font to a scaleable font family");
			return;
		}

		if (_hoops_ISISR == 0.0f) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Can't add a Aheight=0 font to an existing font family");
			return;
		}

		if ((family->_hoops_HCSSP || _hoops_GRSGGR.length == 0) &&
			(_hoops_ISISR == -1.0f || family->_hoops_ICSSP->_hoops_ISISR == -1.0f)) {
			_hoops_IISCP (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"If 'Aheight=-1' is in use, then each member of",
								"a font family must have its own name");
			return;
		}

		if (_hoops_ISISR != -1.0f) {
			Font_Instance const		*_hoops_CRSGGR;

			if ((_hoops_CRSGGR = family->_hoops_ICSSP) != null) {
				do if (_hoops_ISISR <= _hoops_CRSGGR->_hoops_ISISR) {
					if (_hoops_ISISR == _hoops_CRSGGR->_hoops_ISISR) {
#						ifdef _hoops_CGSPR
							_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
										   "That size already occurs in that font family");
#						endif
						return;
					}
					break;
				} while ((_hoops_CRSGGR = _hoops_CRSGGR->_hoops_SSSSP) != null);
			}
		}
	}
	else {		/* '_hoops_PCRIP' _hoops_RSAS'_hoops_RA _hoops_IIH */
		ZALLOC (family, _hoops_RCSSP);

		family->next = (_hoops_RCSSP alter *)dc->_hoops_SGHGH; /*_hoops_ICIC _hoops_HIIC*/
		((Display_Context alter *)dc)->_hoops_SGHGH = family;

		HI_Copy_Name (&family_name, &family->name);
		family->_hoops_SSCAP = *_hoops_ARSGGR;
		*_hoops_ARSGGR = (_hoops_SHSSP alter *)family; /* _hoops_ICIC _hoops_HIIC */

		family->_hoops_PCSSP = (_hoops_ISISR == 0.0f);
	}

	ZALLOC (instance, Font_Instance);
	instance->type = _hoops_RISSP;

	if (_hoops_GRSGGR.length == 0)
		family->_hoops_HCSSP = true;
	else {
		/* _hoops_PPSI _hoops_SCH _hoops_GGR */
		HI_Copy_Name (&_hoops_GRSGGR, &instance->name);
		instance->_hoops_SSCAP = *_hoops_PRSGGR;
		*_hoops_PRSGGR = (_hoops_SHSSP alter *)instance; /* _hoops_ICIC _hoops_HIIC*/
	}

	/* (_hoops_RH _hoops_HIIC _hoops_HRGR _hoops_ICIC) */
	_hoops_RRSGGR = (Font_Instance alter * alter *)&family->_hoops_ICSSP;
	while (*_hoops_RRSGGR != null) {
		if (_hoops_ISISR < (*_hoops_RRSGGR)->_hoops_ISISR)
			break;
		_hoops_RRSGGR = &(*_hoops_RRSGGR)->_hoops_SSSSP;
	}
	instance->_hoops_SSSSP = *_hoops_RRSGGR;
	*_hoops_RRSGGR = instance;
	instance->family = family;
	instance->_hoops_ISISR = _hoops_ISISR;
	instance->_hoops_IGGGH = _hoops_IGGGH;
	instance->encoding = encoding;
	instance->_hoops_GRGGH = 1.0f;
	instance->_hoops_GCHSA = 1.0f;
	instance->_hoops_RACSR = _hoops_ISISR;
}


local void _hoops_SRSGGR (
	Display_Context const	*dc,
	Font_Instance alter		*_hoops_GASGGR,
	_hoops_CSSGP		_hoops_SSSGP) {
	Font_Instance alter		* alter *_hoops_ASRGR;

	if (_hoops_GASGGR->_hoops_IRGGH != GFN_NONE) {
		if (_hoops_GASGGR->_hoops_IRGGH != _hoops_SSSGP)
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Font already marked as a different kind of 'generic'");
		else
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Font is already marked once as 'generic'");
		return;
	}

	/* (_hoops_RH _hoops_HIIC _hoops_HRGR _hoops_ICIC) */
	_hoops_ASRGR = (Font_Instance alter * alter *)&dc->_hoops_RRHGH[_hoops_SSSGP];

	if (*_hoops_ASRGR != null) {
		if ((*_hoops_ASRGR)->family->_hoops_PCSSP || _hoops_GASGGR->family->_hoops_PCSSP) do {
			if (_hoops_GASGGR->encoding <= (*_hoops_ASRGR)->encoding) {
				if (_hoops_GASGGR->encoding == (*_hoops_ASRGR)->encoding) {
					_hoops_IISCP (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
										"For a given generic font class & encoding, if a font is scaleable",
										"it must be the sole occupant of the class");
					return;
				}
				break;
			}
			_hoops_ASRGR = &(*_hoops_ASRGR)->_hoops_GGGGH;
		} while (*_hoops_ASRGR != null);

		if (*_hoops_ASRGR != null && _hoops_GASGGR->_hoops_ISISR != -1.0f) do {
			if (_hoops_GASGGR->_hoops_ISISR <= (*_hoops_ASRGR)->_hoops_ISISR) {
				if (_hoops_GASGGR->_hoops_ISISR == (*_hoops_ASRGR)->_hoops_ISISR) {
					if (_hoops_GASGGR->encoding <= (*_hoops_ASRGR)->encoding) {
						if (_hoops_GASGGR->encoding == (*_hoops_ASRGR)->encoding) {
							if (_hoops_GASGGR == *_hoops_ASRGR)
								_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Tried to mark the same thing as generic twice");
							else
								_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Another font of the same size is already in that generic name class");
							return;
						}
						break;
					}
				}
				break;
			}
			_hoops_ASRGR = &(*_hoops_ASRGR)->_hoops_GGGGH;
		} while (*_hoops_ASRGR != null);
	}

	_hoops_GASGGR->_hoops_GGGGH = *_hoops_ASRGR;
	_hoops_GASGGR->_hoops_IRGGH = _hoops_SSSGP;
	*_hoops_ASRGR = _hoops_GASGGR;
}


GLOBAL_FUNCTION bool HD_Mark_Font_As_Generic (
	Display_Context const	*dc,
	char const					*name,
	_hoops_CSSGP		_hoops_IRGGH) {
	_hoops_SHSSP alter			*_hoops_GSIGGR;

	switch (_hoops_IRGGH) {
		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Illegal 'generic name' value");
			return false;
		}		/*_hoops_IHSA;*/

		case GFN_SANS_SERIF:
		case GFN_TYPEWRITER:
		case GFN_ROMAN:
		case _hoops_GIIGI:
		case _hoops_RIIGI:
		case _hoops_AIIGI:
		case GFN_STROKED: break;
	}

	if ((_hoops_GSIGGR = _hoops_AGSGGR (dc, name)) == null)
		return false;

	if (_hoops_GSIGGR->type == _hoops_RISSP)
		_hoops_SRSGGR (dc, (Font_Instance alter *)_hoops_GSIGGR, _hoops_IRGGH);
	else {
		Font_Instance alter	*instance;

		instance = (Font_Instance alter *)((_hoops_RCSSP const *)_hoops_GSIGGR)->_hoops_ICSSP;

		do _hoops_SRSGGR (dc, instance, _hoops_IRGGH);
		while (instance->_hoops_ISISR != 0.0f && (instance = instance->_hoops_SSSSP) != null);
	}

	return true;
}


GLOBAL_FUNCTION bool HD_Mark_Font_As_System_Default (
	Display_Context const		*dc,
	char const						*name,
	float							_hoops_ISISR) {

	UNREFERENCED(_hoops_ISISR);

	if (dc->_hoops_RRHGH[GFN_SYSTEM_DEFAULT] != null) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
			"A font is already marked as 'system default'");
		return false;
	}

	return HD_Mark_Font_As_Generic (dc, name, GFN_SYSTEM_DEFAULT);
}


GLOBAL_FUNCTION bool HD_Mark_Font_As_Transformable (
	Display_Context const	*dc,
	char const					*name,
	int							_hoops_CAGGH) {
	_hoops_SHSSP alter			*_hoops_GSIGGR;

	if ((_hoops_GSIGGR = _hoops_AGSGGR (dc, name)) == null)
		return false;

	if (_hoops_GSIGGR->type == _hoops_RISSP)
		((Font_Instance alter *)_hoops_GSIGGR)->_hoops_CAGGH = _hoops_CAGGH;
	else {
		Font_Instance alter	*instance;

		instance = (Font_Instance alter *)((_hoops_RCSSP const *)_hoops_GSIGGR)->_hoops_ICSSP;

		do instance->_hoops_CAGGH = _hoops_CAGGH;
		while ((instance = instance->_hoops_SSSSP) != null);
	}

	return true;
}


GLOBAL_FUNCTION bool HD_Mark_Font_As_Aliased (
	Display_Context const		 *dc,
	char const						*name,
	char const						*_hoops_ASHIH,
	long							index) {
	_hoops_SHSSP alter			*_hoops_GSIGGR;
	_hoops_HCRPR						_hoops_RASGGR;


	if ((_hoops_GSIGGR = _hoops_AGSGGR (dc, name)) == null)
		return false;

	_hoops_RASGGR.length = _hoops_SSGR (_hoops_ASHIH);
	_hoops_RASGGR.text = (alter char *)_hoops_ASHIH;

	if (_hoops_GSIGGR->type == _hoops_RISSP) {
		/*_hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_AASGGR*/
		_hoops_RGAIR(((Font_Instance alter *)_hoops_GSIGGR)->_hoops_SAGGH);
		HI_Copy_Name (&_hoops_RASGGR, &(((Font_Instance alter *)_hoops_GSIGGR)->_hoops_SAGGH));
		((Font_Instance alter *)_hoops_GSIGGR)->_hoops_SSPAR = index;
	}
	else {
		Font_Instance alter	*instance;

		instance = (Font_Instance alter *)((_hoops_RCSSP const *)_hoops_GSIGGR)->_hoops_ICSSP;

		do {
				/*_hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_AASGGR*/
				_hoops_RGAIR(instance->_hoops_SAGGH);
				HI_Copy_Name (&_hoops_RASGGR, &(instance->_hoops_SAGGH));
				instance->_hoops_SSPAR = index;
		} while ((instance = instance->_hoops_SSSSP) != null);
	}

	return true;
}


GLOBAL_FUNCTION Font_Instance const * HD_Record_Scaleable_Instance (
	Display_Context const	*dc,
	Font_Instance const		*specific,
	float						_hoops_ISISR,
	float						_hoops_IGGGH) {
	Font_Instance alter		*instance;
	Font_Instance alter		* alter *_hoops_ASRGR;

	/* _hoops_GICGGR _hoops_PPR _hoops_PRHPA _hoops_GGRRR: _hoops_RIPHR _hoops_IRS _hoops_CCAH _hoops_HAGAR */

	ZALLOC (instance, Font_Instance);

	instance->type = _hoops_RISSP;
	instance->family = specific->family;
	instance->_hoops_AGGGH = specific;
	instance->_hoops_ISISR = _hoops_ISISR;
	instance->_hoops_IGGGH = _hoops_IGGGH;
	instance->_hoops_IRGGH = specific->family->_hoops_ICSSP->_hoops_IRGGH;
	instance->encoding = specific->encoding;
	instance->_hoops_CAGGH = specific->_hoops_CAGGH;
	instance->_hoops_SSPAR= specific->_hoops_SSPAR;
	instance->_hoops_GRGGH = 1.0f;
	instance->_hoops_GCHSA = 1.0f;
	instance->_hoops_RACSR = _hoops_ISISR;

	_hoops_ASRGR = (Font_Instance alter * alter *)&specific->family->_hoops_ICSSP; /* _hoops_ICIC _hoops_HIIC */
	while (*_hoops_ASRGR != null && (*_hoops_ASRGR)->_hoops_ISISR <= instance->_hoops_ISISR)
		_hoops_ASRGR = &(*_hoops_ASRGR)->_hoops_SSSSP;

	instance->_hoops_SSSSP = *_hoops_ASRGR;
	*_hoops_ASRGR = instance;

	if (instance->_hoops_IRGGH == GFN_NONE)
		instance->_hoops_GGGGH = null;
	else {
		/* (_hoops_RH _hoops_HIIC _hoops_HRGR _hoops_ICIC) */
		_hoops_ASRGR = (Font_Instance alter * alter *)&dc->_hoops_RRHGH[instance->_hoops_IRGGH];
		while (*_hoops_ASRGR != null && (*_hoops_ASRGR)->_hoops_ISISR <= instance->_hoops_ISISR)
			_hoops_ASRGR = &(*_hoops_ASRGR)->_hoops_GGGGH;

		instance->_hoops_GGGGH = *_hoops_ASRGR;
		*_hoops_ASRGR = instance;
	}

	return instance;
}


GLOBAL_FUNCTION bool HD_Mark_Font_As_Defined (
	Display_Context const	*dc,
	char const				*name,
	_hoops_PGIIR const				*font) {
	_hoops_SHSSP alter			*_hoops_GSIGGR;

	if ((_hoops_GSIGGR = _hoops_AGSGGR (dc, name)) == null)
		return false;

	if (_hoops_GSIGGR->type == _hoops_RISSP) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Can't mark an instance as 'built-in'");
		return false;
	}

	((_hoops_RCSSP alter *)_hoops_GSIGGR)->_hoops_RRCSR = _hoops_ARCSR;
	((_hoops_RCSSP alter *)_hoops_GSIGGR)->font = font;
	if (font != null)
		_hoops_PRRH (font);

	return true;
}

GLOBAL_FUNCTION bool HD_Mark_Font_As_Freetype (
	Display_Context const	*dc,
	char const					*name) {
#ifdef FREETYPE
	_hoops_SHSSP alter			*_hoops_GSIGGR;

	if ((_hoops_GSIGGR = _hoops_AGSGGR (dc, name)) == null)
		return false;

	if (_hoops_GSIGGR->type == _hoops_RISSP) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Can't mark an instance as 'Freetype'");
		return false;
	}

	((_hoops_RCSSP alter *)_hoops_GSIGGR)->_hoops_RRCSR = _hoops_SISSP;
	return true;
#else
	UNREFERENCED(dc);
	UNREFERENCED(name);
	return false;
#endif
}


GLOBAL_FUNCTION void HD_Free_Fonts (
	Display_Context alter	*dc) {
	_hoops_RCSSP alter		*family;
	_hoops_RCSSP alter		*_hoops_PASGGR;

	HD_Unload_All_Fonts(dc);

	if ((family = (_hoops_RCSSP alter *)dc->_hoops_SGHGH) != null) do {
		Font_Instance alter	*instance;

		if (family->font != null)
			_hoops_HPRH (family->font);

		if ((instance = (Font_Instance alter *)family->_hoops_ICSSP) != null) {
			Font_Instance alter	*_hoops_HASGGR;

			do {
				_hoops_RGAIR (instance->name);
				_hoops_RGAIR (instance->_hoops_SAGGH);

				_hoops_HASGGR = (Font_Instance alter *)instance->_hoops_SSSSP;

				if (instance->_hoops_RGPIP) {
					FREE_ARRAY (instance->_hoops_RGPIP, _hoops_HGGGH, _hoops_SCSSP);
				}

				FREE (instance, Font_Instance);
			} while ((instance = _hoops_HASGGR) != null);
		}

		_hoops_RGAIR (family->name);
		_hoops_PASGGR = family->next;
		FREE (family, _hoops_RCSSP);
	} while ((family = _hoops_PASGGR) != null);

	dc->_hoops_SGHGH = null;
}

GLOBAL_FUNCTION void HD_Free_Defined_Font_Family (
	Display_Context alter	*dc,
	_hoops_RCSSP alter		*family) {
	_hoops_RCSSP alter		* alter *_hoops_ASRGR;
	_hoops_SHSSP alter			* alter *_hoops_SIGCC;

	_hoops_ASRGR = (_hoops_RCSSP alter * alter *)&dc->_hoops_SGHGH;/* _hoops_ICIC _hoops_HIIC. */

	if (family->font != null)	/* _hoops_CGH _hoops_SHR _hoops_SHH _hoops_IHPR */
		_hoops_HPRH (family->font);

	/* _hoops_SCAC _hoops_GII _hoops_SASI _hoops_SPGIA */
	{	Font_Instance alter		*instance;

		/* _hoops_ICIC _hoops_HIIC */
		if ((instance = (Font_Instance alter *)family->_hoops_ICSSP) != null) {
			Font_Instance alter	*_hoops_HASGGR;

			do {
				_hoops_RGAIR (instance->name);
				_hoops_RGAIR (instance->_hoops_SAGGH);

				_hoops_HASGGR = instance->_hoops_SSSSP;

				if (instance->_hoops_RGPIP) {
					FREE_ARRAY (instance->_hoops_RGPIP, _hoops_HGGGH, _hoops_SCSSP);
				}

				FREE (instance, Font_Instance);
			} while ((instance = _hoops_HASGGR) != null);
		}
	}

	/* _hoops_HASIR _hoops_HII _hoops_SCAH _hoops_GASR */
	{	char const		*_hoops_RPPA = family->name.text;
		int				count = family->name.length;
		int				_hoops_ARAHR = 0;

		do _hoops_ARAHR += _hoops_SHPCR (*_hoops_RPPA++);
		_hoops_RGGA (--count <= 0);

		/* (_hoops_RH _hoops_HIIC _hoops_HRGR _hoops_ICIC) */
		_hoops_SIGCC = (_hoops_SHSSP alter * alter *)&dc->_hoops_GRHGH[_hoops_ARAHR & (_hoops_HHRSP - 1)];
	}

	_hoops_PCCAR {
		if (*_hoops_SIGCC == null) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Driver font table is corrupted");
			break;
		}

		if (*_hoops_SIGCC == (_hoops_SHSSP const *)family) {
			*_hoops_SIGCC = family->_hoops_SSCAP;
			break;
		}
		/* _hoops_ICIC _hoops_HIIC */
		_hoops_SIGCC = &(*_hoops_SIGCC)->_hoops_SSCAP;
	}

	/* _hoops_HASIR _hoops_HII _hoops_PCRIP _hoops_HIGR */
	_hoops_PCCAR {
		if (*_hoops_ASRGR == null) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Driver font list is corrupted");
			break;
		}

		if (*_hoops_ASRGR == family) {
			*_hoops_ASRGR = family->next;
			break;
		}
		/* _hoops_ICIC _hoops_HIIC */
		_hoops_ASRGR = &(*_hoops_ASRGR)->next;
	}


	_hoops_RGAIR (family->name);
	FREE (family, _hoops_RCSSP);
}







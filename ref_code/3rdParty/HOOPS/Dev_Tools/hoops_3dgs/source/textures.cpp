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
 * $Id: obf_tmp.txt 1.220 2010-12-07 20:40:17 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "searchh.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_TEXTURING

#define _hoops_PHSGGR		-1

local const _hoops_IGRCR _hoops_HHSGGR[] = {
	{HK_PS_UNSPECIFIED,			_hoops_GRRCR ("unknown"),		_hoops_RRRCR, 0, false},
	{HK_PS_U,					_hoops_GRRCR ("u"),				_hoops_RRRCR, 0, false},
	{HK_PS_UV,					_hoops_GRRCR ("uv"),			_hoops_RRRCR, 0, false},
	{HK_PS_UVW,					_hoops_GRRCR ("uvw"),			_hoops_RRRCR, 0, false},
	{HK_PS_OBJECT,				_hoops_GRRCR ("object"),		_hoops_RRRCR, 0, false},
	{HK_PS_WORLD,				_hoops_GRRCR ("world"),			_hoops_RRRCR, 0, false},
	{HK_PS_SURFACE_NORMAL,		_hoops_GRRCR ("normal"),		_hoops_RRRCR, 0, false},
	{HK_PS_REFLECTION_VECTOR,	_hoops_GRRCR ("reflection"),	_hoops_RRRCR, 0, false},
	{_hoops_HSR, _hoops_GRRCR ("physical reflection"),	_hoops_RRRCR, 0, false},
	{HK_PS_NATURAL_UV,			_hoops_GRRCR ("natural"),		_hoops_RRRCR, 0, false},
	{HK_PS_LOCAL_PIXELS,		_hoops_GRRCR ("local pixels"),	_hoops_RRRCR, 0, false},
	{HK_PS_OUTER_PIXELS,		_hoops_GRRCR ("outer pixels"),	_hoops_RRRCR, 0, false},
	{HK_PS_LOCAL_WINDOW,		_hoops_GRRCR ("local window"),	_hoops_RRRCR, 0, false},
	{HK_PS_OUTER_WINDOW,		_hoops_GRRCR ("outer window"),	_hoops_RRRCR, 0, false},
	{HK_PS_SPHERE,				_hoops_GRRCR ("sphere"),		_hoops_RRRCR, 0, false},
	{HK_PS_CYLINDER,			_hoops_GRRCR ("cylinder"),		_hoops_RRRCR, 0, false},

	/* _hoops_IRACC */
	{HK_PS_SURFACE_NORMAL,		_hoops_GRRCR ("surface normal"),_hoops_RRRCR, 0, false},
	{HK_PS_REFLECTION_VECTOR,	_hoops_GRRCR ("reflection normal"),_hoops_RRRCR, 0, false},
	{HK_PS_REFLECTION_VECTOR,	_hoops_GRRCR ("reflection vector"),_hoops_RRRCR, 0, false},
	{HK_PS_NATURAL_UV,			_hoops_GRRCR ("natural uv"),_hoops_RRRCR, 0, false},
	{HK_PS_SPHERE,				_hoops_GRRCR ("sphere map"),_hoops_RRRCR, 0, false},
	{HK_PS_CYLINDER,			_hoops_GRRCR ("cylinder map"),_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_IHSGGR = {
	_hoops_GGAPR (_hoops_HHSGGR),				_hoops_HHSGGR,
};

local const _hoops_IGRCR _hoops_CHSGGR[] = {
	{_hoops_HCGRP,			_hoops_GRRCR ("unknown"),		_hoops_RRRCR, 0, false},
	{_hoops_ICGRP,			_hoops_GRRCR ("rectilinear"),	_hoops_RRRCR, 0, false},
	{_hoops_ICGRP,			_hoops_GRRCR ("rectangular"),	_hoops_RRRCR, 0, false},
	{_hoops_CCGRP,			_hoops_GRRCR ("spherical"),		_hoops_RRRCR, 0, false},
	{_hoops_SCGRP,		_hoops_GRRCR ("hemispherical"), _hoops_RRRCR, 0, false},
	{_hoops_SCGRP,		_hoops_GRRCR ("hemispheres"),	_hoops_RRRCR, 0, false},
	{_hoops_GSGRP,			_hoops_GRRCR ("cubic faces"),	_hoops_RRRCR, 0, false},
	{_hoops_GSGRP,			_hoops_GRRCR ("cubic"),			_hoops_RRRCR, 0, false},
	{_hoops_GSGRP,			_hoops_GRRCR ("cube"),			_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_SHSGGR = {
	_hoops_GGAPR (_hoops_CHSGGR),			_hoops_CHSGGR,
};

local const _hoops_IGRCR _hoops_GISGGR[] = {
	{_hoops_SGA,				_hoops_GRRCR ("drop"),			_hoops_RRRCR, 0, false},
	{_hoops_ASCC,				_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{_hoops_ASCC,				_hoops_GRRCR ("no"),			_hoops_RRRCR, 0, false},
	{_hoops_ASCC,				_hoops_GRRCR ("clamp"),			_hoops_RRRCR, 0, false},
	{_hoops_ASGRP,				_hoops_GRRCR ("repeat"),		_hoops_RRRCR, 0, false},
	{_hoops_ASGRP,				_hoops_GRRCR ("on"),			_hoops_RRRCR, 0, false},
	{_hoops_PSGRP,				_hoops_GRRCR ("mirror"),		_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_RISGGR = {
	_hoops_GGAPR (_hoops_GISGGR),					_hoops_GISGGR,
};

local const _hoops_IGRCR _hoops_GAHRS[] = {
	{_hoops_HSCC,			_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{_hoops_HSCC,			_hoops_GRRCR ("no"),			_hoops_RRRCR, 0, false},
	{_hoops_HSGRP,		_hoops_GRRCR ("bilinear"),		_hoops_RRRCR, 0, false},
	{_hoops_HSGRP,		_hoops_GRRCR ("on"),			_hoops_RRRCR, 0, false},
	{_hoops_SSGRP,		_hoops_GRRCR ("gaussian"),		_hoops_RRRCR, 0, false},
	{_hoops_GGRRP,		_hoops_GRRCR ("stochastic"),	_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_AISGGR = {
	_hoops_GGAPR (_hoops_GAHRS),			_hoops_GAHRS,
};

local const _hoops_IGRCR _hoops_PISGGR[] = {
	{_hoops_HSCC,		_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{_hoops_HSCC,		_hoops_GRRCR ("no"),			_hoops_RRRCR, 0, false},
	{_hoops_AARH,		_hoops_GRRCR ("mipmap"),		_hoops_RRRCR, 0, false},
	{_hoops_AARH,		_hoops_GRRCR ("on"),			_hoops_RRRCR, 0, false},
	{_hoops_PARH,	_hoops_GRRCR ("anisotropic"),	_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_HISGGR = {
	_hoops_GGAPR (_hoops_PISGGR),				_hoops_PISGGR,
};

local const _hoops_IGRCR _hoops_IISGGR[] = {
	{_hoops_AGRRP,		_hoops_GRRCR ("off"),			_hoops_RRRCR, 0, false},
	{_hoops_AGRRP,		_hoops_GRRCR ("no"),			_hoops_RRRCR, 0, false},
	{_hoops_PGRRP,		_hoops_GRRCR ("red"),			_hoops_RRRCR, 0, false},
	{_hoops_HGRRP,		_hoops_GRRCR ("green"),			_hoops_RRRCR, 0, false},
	{_hoops_IGRRP,		_hoops_GRRCR ("blue"),			_hoops_RRRCR, 0, false},
	{_hoops_CGRRP,		_hoops_GRRCR ("alpha"),			_hoops_RRRCR, 0, false},
	{_hoops_SGRRP,		_hoops_GRRCR ("zero"),			_hoops_RRRCR, 0, false},
	{_hoops_GRRRP,		_hoops_GRRCR ("one"),			_hoops_RRRCR, 0, false},
	{_hoops_RRRRP, _hoops_GRRCR ("luminance"),		_hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_CISGGR = {
	_hoops_GGAPR (_hoops_IISGGR),			_hoops_IISGGR,
};

local const _hoops_IGRCR _hoops_SISGGR[] = {
	{_hoops_GARRP,					_hoops_GRRCR ("source"),				_hoops_PRRCR, -9999, false},
	{_hoops_IRRRP,			_hoops_GRRCR ("parameter offset"),		_hoops_APRCA, 1, true},
	{_hoops_HRRRP,			_hoops_GRRCR ("parameterization source"), _hoops_GHAGA, 1, false, &_hoops_IHSGGR},
	{_hoops_HRRRP,			_hoops_GRRCR ("parameter source"),		_hoops_GHAGA, 1, false, &_hoops_IHSGGR},
	{_hoops_APRRP,			_hoops_GRRCR ("layout"),				_hoops_GHAGA, 1, true, &_hoops_SHSGGR},
	{_hoops_CRRRP,				_hoops_GRRCR ("transform"),				_hoops_PRRCR, 1, true},
	{_hoops_SRRRP,					_hoops_GRRCR ("tiling"),				_hoops_GHAGA, -1, true, &_hoops_RISGGR},
	{_hoops_RARRP,	_hoops_GRRCR ("interpolation filter"),	_hoops_GHAGA, -1, true, &_hoops_AISGGR},
	{_hoops_AARRP,		_hoops_GRRCR ("decimation filter"),		_hoops_GHAGA, -1, true, &_hoops_HISGGR},
	{_hoops_PARRP,		_hoops_GRRCR ("red channel mapping"),	_hoops_GHAGA, 1, true, &_hoops_CISGGR},
	{_hoops_HARRP,		_hoops_GRRCR ("green channel mapping"),	_hoops_GHAGA, 1, true, &_hoops_CISGGR},
	{_hoops_IARRP,		_hoops_GRRCR ("blue channel mapping"),	_hoops_GHAGA, 1, true, &_hoops_CISGGR},
	{_hoops_CARRP,		_hoops_GRRCR ("alpha channel mapping"),	_hoops_GHAGA, 1, true, &_hoops_CISGGR},
	{_hoops_SARRP,			_hoops_GRRCR ("value scale"),			_hoops_SPPCR, 2, true},
	{_hoops_GPRRP,				_hoops_GRRCR ("caching"),				_hoops_RRRCR,  0, true},
	{_hoops_HPRRP,				_hoops_GRRCR ("down sample"),			_hoops_RRRCR,  0, true},
	{_hoops_HPRRP,				_hoops_GRRCR ("down sampling"),			_hoops_RRRCR,  0, true},
	{_hoops_HPRRP,				_hoops_GRRCR ("downsample"),			_hoops_RRRCR,  0, true},
	{_hoops_HPRRP,				_hoops_GRRCR ("downsampling"),			_hoops_RRRCR,  0, true},
	{_hoops_HPRRP,				_hoops_GRRCR ("down-sample"),			_hoops_RRRCR,  0, true},
	{_hoops_HPRRP,				_hoops_GRRCR ("down-sampling"),			_hoops_RRRCR,  0, true},
	{_hoops_PPRRP,				_hoops_GRRCR ("modulate"),				_hoops_RRRCR,  0, true},
	{_hoops_IPRRP,					_hoops_GRRCR ("decal"),					_hoops_RRRCR,  0, true},
	{_hoops_CPRRP,		_hoops_GRRCR ("source callback"),		_hoops_PRRCR,  1, true},
	{_hoops_PHRRP,	_hoops_GRRCR ("source callback data"),	_hoops_PRRCR,  1, true},
	{_hoops_IPGH,		_hoops_GRRCR ("transform override"),	_hoops_RRRCR,  0, true},
	{_hoops_RHRRP,					_hoops_GRRCR ("camera"),				_hoops_PRRCR, 1, true},
	{_hoops_PHSGGR,			_hoops_GRRCR ("stage"),					_hoops_PRRCR, 1, true},
	{_hoops_ASR,	_hoops_GRRCR ("multitexture"),			_hoops_RRRCR,  0, true},
	{_hoops_AHRRP,		_hoops_GRRCR ("source dimensions"),		_hoops_APRCA, -3, true},
};

GLOBAL_FUNCTION void HI_Init_Texture_Options() {

	_hoops_HIACR (_hoops_CPRGI, _hoops_SISGGR);
}

local bool _hoops_ACCCA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP	const *			_hoops_SRCP,
	_hoops_RCR *				texture,
	char const *			definition,
	Option_Value *			option_list) {
	Option_Value *			option;
	_hoops_ARRRP			_hoops_GCSGGR = (_hoops_ARRRP) 0;
	_hoops_HCHIR *			_hoops_HGIIR = null;

	UNREFERENCED(_hoops_SRCP);

	HI_Init_Texture_Options();

	if (definition &&
		!HI_Parse_Options (_hoops_RIGC, definition, _hoops_CIACR (_hoops_CPRGI),
						   &option_list, _hoops_SIACR))
						   return false;

	if ((option = option_list) != null) do {
		if (option->type->id > 0) {
			//_hoops_HHHR _hoops_RGGHR _hoops_IRHC _hoops_SGS _hoops_RH _hoops_HCSP _hoops_HRGR _hoops_HAR _hoops_RCCP _hoops_IS _hoops_SHH _hoops_SSPP
			//_hoops_RRAI _hoops_IS _hoops_RH _hoops_ARGR _hoops_HH _hoops_SGI _hoops_PAIP (_hoops_IAS._hoops_ISHI. _hoops_RCSGGR)
			_hoops_GCSGGR |= (_hoops_ARRRP) option->type->id;

			if (option->_hoops_GCACR)
				texture->flags &= (int)~option->type->id;
			else
				texture->flags |= (int)option->type->id;
		}

		switch (option->type->id) {
			case _hoops_HRRRP:  {
				texture->_hoops_PSR = (Param_Source)option->value.option_list->type->id;
			}	break;

			case _hoops_IRRRP:  {
				if (option->_hoops_GCACR)
					texture->_hoops_RSCP = 0;
				else {
					texture->_hoops_RSCP = option->value._hoops_RIARA[0];

					if (texture->_hoops_RSCP < 0) {
						HE_WARNING (HEC_TEXTURE, HES_OUT_OF_RANGE_VALUE_SCALE,
								"Parameter offset must be larger than zero.");
						texture->_hoops_RSCP = 0;
					}
				}
			}	break;

			case _hoops_APRRP:	 {
				texture->_hoops_GAARP = (_hoops_PCGRP)option->value.option_list->type->id;
			}	break;

			case _hoops_CRRRP:	{
				if (option->_hoops_GCACR) {
					texture->_hoops_IRARP = null;
				}
				else {
					_hoops_HCRPR	name;

					HI_Canonize_Chars_Quoted (option->value._name[0].text, &name, false);
					texture->_hoops_IRARP = HI_One_Segment_Search(_hoops_RIGC, name.text, true);
					if (texture->_hoops_IRARP == null) {
						HE_WARNING (HEC_TEXTURE, HES_INVALID_TRANSFORM_SEGMENT,
								Sprintf_N (null, "Transform segment '%n' does not exist",
								&option->value._name[0]));
					}
					_hoops_RGAIR (name);
				}
				/* _hoops_SGI _hoops_HAR _hoops_IGI _hoops_IH _hoops_HIHP, _hoops_RGAR _hoops_ACSGGR _hoops_CRS */
				texture->flags &= (int)~_hoops_CRRRP;
			}	break;

			case _hoops_RHRRP:	{
				if (option->_hoops_GCACR) {
					texture->_hoops_SRARP = null;
				}
				else {
					_hoops_HCRPR	name;

					HI_Canonize_Chars_Quoted (option->value._name[0].text, &name, false);
					texture->_hoops_SRARP = HI_One_Segment_Search(_hoops_RIGC, name.text, true);
					if (texture->_hoops_SRARP == null) {
						HE_WARNING (HEC_TEXTURE, HES_INVALID_TRANSFORM_SEGMENT,
								Sprintf_N (null, "Camera segment '%n' does not exist",
								&option->value._name[0]));
					}
					_hoops_RGAIR (name);
				}
				/* _hoops_SGI _hoops_HAR _hoops_IGI _hoops_IH _hoops_SARA, _hoops_RGAR _hoops_PCSGGR _hoops_CRS */
				texture->flags &= (int)~_hoops_RHRRP;
			}	break;

			case _hoops_SRRRP:	 {
				if (option->_hoops_GCACR)
					texture->_hoops_CGA = _hoops_ASCC;
				else if (option->_hoops_AIPCR == 0)
					texture->_hoops_CGA = _hoops_ASGRP;
				else
					texture->_hoops_CGA = (_hoops_RSGRP)option->value.option_list->type->id;

				/* _hoops_ARP _hoops_RPP _hoops_PA _hoops_HRGR _hoops_HHHA */
				texture->flags |= _hoops_SRRRP;
			}	break;

			case _hoops_GARRP:	 {
				_hoops_HCRPR			*name = &option->value._name[0];
				int				count = option->_hoops_AIPCR;

				/* _hoops_GGAS _hoops_RPP _hoops_GHGPR _hoops_CHIA */
				if (texture->_hoops_PAPIR) {
					_hoops_AAPIR	*next, *_hoops_PAPIR = texture->_hoops_PAPIR;

					while (_hoops_PAPIR != null) {
						next = _hoops_PAPIR->next;
						_hoops_RGAIR(_hoops_PAPIR->name);
						FREE (_hoops_PAPIR, _hoops_AAPIR);
						_hoops_PAPIR = next;
					}
				}

				if (count == 1 && name->text[0] == '@') {
					int				_hoops_RAPPH = 0;
					Key				_hoops_HCSGGR = 0;
					char const *	cursor = name->text;
					Image *			image;

					++cursor;  //_hoops_HSGR '@'
					while (*cursor == ' ') ++cursor;	//_hoops_ICSGGR _hoops_CCSGGR _hoops_CCSGGR
					if (name->length >= 3 && cursor[0] == '0' && cursor[1] == 'x')
						cursor+=2;	//_hoops_HHH _hoops_SASPP _hoops_PCIAI 0x _hoops_CGPR _hoops_SCSGGR-_hoops_SSRSS %_hoops_CCAHR

					_hoops_PCCAR {
						int				inc;

						switch (*cursor++) {
							case '0':			inc = 0x0;		break;
							case '1':			inc = 0x1;		break;
							case '2':			inc = 0x2;		break;
							case '3':			inc = 0x3;		break;
							case '4':			inc = 0x4;		break;
							case '5':			inc = 0x5;		break;
							case '6':			inc = 0x6;		break;
							case '7':			inc = 0x7;		break;
							case '8':			inc = 0x8;		break;
							case '9':			inc = 0x9;		break;
							case 'A': case 'a': inc = 0xA;		break;
							case 'B': case 'b': inc = 0xB;		break;
							case 'C': case 'c': inc = 0xC;		break;
							case 'D': case 'd': inc = 0xD;		break;
							case 'E': case 'e': inc = 0xE;		break;
							case 'F': case 'f': inc = 0xF;		break;
							default:			inc = -1;		break;
						}

						if (inc < 0) break;

						_hoops_HCSGGR <<= 4;
						_hoops_HCSGGR += inc;
						++_hoops_RAPPH;
					}

					--cursor;

					if (!_hoops_RAPPH) {
						HE_ERROR (HEC_SYNTAX, HES_AT_SIGN_MISSING_FROM_KEY,
								Sprintf_S (null,
								  "Missing image key after '@' in '%s'", definition));
						break;
					}

					image = (Image *)_hoops_RCSSR(_hoops_RIGC, _hoops_HCSGGR);
					if (image && image->type == _hoops_HGCP && !BIT(image->_hoops_RRHH, _hoops_HGAGR)) {
						_hoops_PRRH(image);
						texture->image = image;
					}
				}

				_hoops_AAPIR	**_hoops_ASRGR = &texture->_hoops_PAPIR;

				while (count--) {
					_hoops_AAPIR	*_hoops_SPIPI;

					ZALLOC (_hoops_SPIPI, _hoops_AAPIR);
					HI_Copy_Name (name, &_hoops_SPIPI->name);

					*_hoops_ASRGR = _hoops_SPIPI;
					_hoops_ASRGR = &_hoops_SPIPI->next;

					name++;
				}
			}	break;

			case _hoops_RARRP:  {
				texture->flags |= _hoops_RARRP;

				if (option->_hoops_GCACR)
					texture->_hoops_PSCC = _hoops_HSCC;
				else if (option->_hoops_AIPCR == 0)
					texture->_hoops_PSCC = _hoops_HSGRP;
				else
					texture->_hoops_PSCC =
						(_hoops_PPCRR)option->value.option_list->type->id;
			}	break;

			case _hoops_AARRP:	{
				if (option->_hoops_GCACR)
					texture->_hoops_RARH = _hoops_HSCC;
				else if (option->_hoops_AIPCR == 0)
					texture->_hoops_RARH = _hoops_AARH;
				else
					texture->_hoops_RARH = (_hoops_PPCRR)option->value.option_list->type->id;
			}	break;

			case _hoops_PARRP:  {
				if (option->_hoops_GCACR)
					texture->_hoops_HPIR._hoops_RSRRP = _hoops_AGRRP;
				else
					texture->_hoops_HPIR._hoops_RSRRP = (_hoops_RGRRP)option->value.option_list->type->id;
			}	break;

			case _hoops_HARRP:	 {
				if (option->_hoops_GCACR)
					texture->_hoops_HPIR._hoops_ASRRP = _hoops_AGRRP;
				else
					texture->_hoops_HPIR._hoops_ASRRP = (_hoops_RGRRP)option->value.option_list->type->id;
			}	break;

			case _hoops_IARRP:	{
				if (option->_hoops_GCACR)
					texture->_hoops_HPIR._hoops_PSRRP = _hoops_AGRRP;
				else
					texture->_hoops_HPIR._hoops_PSRRP = (_hoops_RGRRP)option->value.option_list->type->id;
			}	break;

			case _hoops_CARRP:	 {
				if (option->_hoops_GCACR)
					texture->_hoops_HPIR._hoops_HSRRP = _hoops_AGRRP;
				else
					texture->_hoops_HPIR._hoops_HSRRP = (_hoops_RGRRP)option->value.option_list->type->id;
			}	break;

			case _hoops_SARRP:  {
				if (option->_hoops_GCACR) {
					texture->_hoops_HPIR._hoops_IIRH = 0.0f;
					texture->_hoops_HPIR._hoops_CIRH = 1.0f;
				}
				else {
					texture->_hoops_HPIR._hoops_IIRH = option->value._hoops_PIPCR[0];
					texture->_hoops_HPIR._hoops_CIRH = option->value._hoops_PIPCR[1];

					if (texture->_hoops_HPIR._hoops_IIRH < 0.0f) {
						HE_WARNING (HEC_TEXTURE, HES_OUT_OF_RANGE_VALUE_SCALE,
								"Texture value scale min must be larger than zero.");
						texture->_hoops_HPIR._hoops_IIRH = 0.0f;
					}
				}
			}	break;

			case _hoops_GPRRP:
				texture->flags |= _hoops_GPRRP;
				if (option->_hoops_GCACR)
					texture->_hoops_SCR |= _hoops_IHRRP;
				break;

			case _hoops_HPRRP:
				texture->flags |= _hoops_HPRRP;
				if (option->_hoops_GCACR)
					texture->_hoops_SCR |= _hoops_RCRH;
				else
					texture->_hoops_SCR &= ~_hoops_RCRH;
				break;

			case _hoops_PPRRP:
				texture->flags |= _hoops_PPRRP;
				if (!option->_hoops_GCACR)
					texture->_hoops_SCR |= _hoops_IGA;
				break;

			case _hoops_IPRRP:
				texture->flags |= _hoops_IPRRP;
				if (!option->_hoops_GCACR)
					texture->_hoops_SCR |= _hoops_PGA;
				break;

			case _hoops_CPRRP: {
 				if (_hoops_HGIIR != null)
					_hoops_HPRH (_hoops_HGIIR);

				if ((_hoops_HGIIR = *HI_Look_Up_Callback_Name (_hoops_RIGC,
									option->value._name[0].text,
									option->value._name[0].length)) == null) {
					HE_ERROR2 (HEC_TEXT, HES_CALLBACK,
							Sprintf_N (null, "'%n' is not a recognized routine name -", &option->value._name[0]),
							   "Define_Callback_Name needs to be called first");

					HI_Free_Option_List (_hoops_RIGC, option_list);
					return false;
				}
				texture->flags |= _hoops_CPRRP;
				if (!option->_hoops_GCACR)
					texture->_hoops_SCR |= _hoops_CHRRP;
				_hoops_PRRH(_hoops_HGIIR);
			}	break;

			case _hoops_PHRRP: {

				_hoops_HCRPR *		name = option->value._name;
				POINTER_SIZED_INT	value;

				texture->_hoops_HRARP = 0;

				if (option->_hoops_GCACR == false) {
					char *		_hoops_RPPA = name->text;
					if (HI_Scan_Ptr (_hoops_RIGC, (char const **)&_hoops_RPPA, _hoops_RPPA+name->length, &value) == null) {
						texture->_hoops_HRARP = (void *)value;
					}
					else
						HE_ERROR (HEC_HOOPS_SYSTEM, HES_BAD_VALUE,
							Sprintf_N (null, "source callback data '%n' is not valid", name));
				}

				texture->flags |= _hoops_PHRRP;

			}	break;

			case _hoops_IPGH:
				texture->flags |= _hoops_IPGH;
				if (option->_hoops_GCACR)
					texture->_hoops_SCR |= _hoops_IPGH;
			break;

			case _hoops_PHSGGR:
				//_hoops_AA _hoops_ISAP (_hoops_IH _hoops_HA)
			break;

			case _hoops_ASR:
				//_hoops_AA _hoops_ISAP
			break;

			case _hoops_AHRRP: {
				int				count = option->_hoops_AIPCR;

				ASSERT (count <= 3);  //_hoops_IAII _hoops_GSSGGR _hoops_HRGR _hoops_AGIA _hoops_IS _hoops_HPPPR _hoops_PPR _hoops_HCHGA
				texture->_hoops_ICR[0] =
					texture->_hoops_ICR[1] =
					texture->_hoops_ICR[2] = 1;
				for (int i = 0; i < count; i++) {
					texture->_hoops_ICR[i] = option->value._hoops_RIARA[i];
				}
			}  break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Define Texture option lookup");
				HI_Free_Option_List (_hoops_RIGC, option_list);
				return false;
			}			/* _hoops_IHSA; */
		}
	} while ((option = option->next) != null);

	texture->_hoops_HGIIR = _hoops_HGIIR;

	if (definition)
		HI_Free_Option_List (_hoops_RIGC, option_list);

	return true;
}

local void _hoops_RSSGGR (_hoops_RCR alter * texture)
{
	/* _hoops_HCIC _hoops_RH _hoops_CAGH _hoops_IHGS _hoops_ASSGGR _hoops_IS _hoops_HGGC _hoops_HPHR? */
	if (!BIT (texture->_hoops_IRARP->_hoops_RRHH, _hoops_HGAGR)) {
		/* _hoops_HCIC _hoops_IIH _hoops_PCCP _hoops_RHGS _hoops_PIAH _hoops_RSGA _hoops_SGS _hoops_SSCP _hoops_RPII _hoops_PGHPR? */
		if (texture->_hoops_GAGH != null &&
			BIT (texture->_hoops_GAGH->_hoops_RRHH, _hoops_HGAGR)) {
			/* _hoops_IPCP _hoops_PIAH _hoops_HH _hoops_RSGA _hoops_SSCP _hoops_RPII _hoops_PGHPR */
			_hoops_HPRH (texture->_hoops_GAGH);
			texture->_hoops_GAGH = null;
		}
		/* _hoops_HHCS _hoops_IS _hoops_SSS _hoops_IRS _hoops_RSGA _hoops_GGR _hoops_RH _hoops_IAHA-_hoops_CAGH */
		if (texture->_hoops_GAGH == null) {
			Attribute const *	_hoops_HPHCR;

			if ((_hoops_HPHCR = texture->_hoops_IRARP->_hoops_IPPGR) != null) do {
				if (_hoops_HPHCR->type == HK_TEXTURE_MATRIX &&
					ANYBIT (((_hoops_GAAIR const *)_hoops_HPHCR)->matrix._hoops_RAGR, _hoops_CICH)) {
					/* _hoops_CCCAR _hoops_PCCP _hoops_CISI, _hoops_GRAA-_hoops_SRGH _hoops_HH _hoops_RSGA! */
					texture->_hoops_GAGH = (_hoops_GAAIR alter *)_hoops_HPHCR;
					_hoops_PRRH (_hoops_HPHCR);
					break;
				}
			} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
		}
	}
	else {
		/* _hoops_IAHA _hoops_CAGH _hoops_SSCP _hoops_RPII _hoops_PSSGGR */
		if (texture->_hoops_GAGH != null) {
			/* _hoops_IPCP _hoops_IAHA _hoops_CAGH _hoops_CSAP _hoops_PGHPR, _hoops_RSGA _hoops_PIHA _hoops_SHH _hoops_GACC */
			_hoops_HPRH (texture->_hoops_GAGH);
			texture->_hoops_GAGH = null;
		}

		HE_WARNING (HEC_TEXTURE, HES_INVALID_TRANSFORM_SEGMENT,
				Sprintf_N (null, "Texture '%n' transform segment no longer exists.",
				&texture->name));

		/* _hoops_RGAR _hoops_HPPPR _hoops_ARR */
		texture->_hoops_IRARP = null;
	}

	if (texture->_hoops_GAGH != null &&
		texture->_hoops_GAGH->matrix._hoops_APRA == null) {
		HI_Validate_Matrix_Adjoint(&texture->_hoops_GAGH->matrix);
	}
}

local void _hoops_HSSGGR (_hoops_RCR alter * texture)
{
	/* _hoops_HCIC _hoops_RH _hoops_CAGH _hoops_IHGS _hoops_ASSGGR _hoops_IS _hoops_HGGC _hoops_HPHR? */
	if (!BIT (texture->_hoops_SRARP->_hoops_RRHH, _hoops_HGAGR)) {
		/* _hoops_HCIC _hoops_IIH _hoops_PCCP _hoops_RHGS _hoops_PIAH _hoops_SARA _hoops_SGS _hoops_SSCP _hoops_RPII _hoops_PGHPR? */
		if (texture->_hoops_RRIIR != null &&
			BIT (texture->_hoops_RRIIR->_hoops_RRHH, _hoops_HGAGR)) {
			/* _hoops_IPCP _hoops_PIAH _hoops_HH _hoops_RSGA _hoops_SSCP _hoops_RPII _hoops_PGHPR */
			_hoops_HPRH (texture->_hoops_RRIIR);
			texture->_hoops_RRIIR = null;
		}
		/* _hoops_HHCS _hoops_IS _hoops_SSS _hoops_IRS _hoops_RSGA _hoops_GGR _hoops_RH _hoops_IAHA-_hoops_CAGH */
		if (texture->_hoops_RRIIR == null) {
			Attribute const *	_hoops_HPHCR;

			if ((_hoops_HPHCR = texture->_hoops_SRARP->_hoops_IPPGR) != null) do {
				if (_hoops_HPHCR->type == HK_CAMERA) {
					/* _hoops_CCCAR _hoops_PCCP _hoops_CISI _hoops_SARA! */
					texture->_hoops_RRIIR = (_hoops_HHRA alter *)_hoops_HPHCR;
					_hoops_PRRH (_hoops_HPHCR);
					break;
				}
			} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
		}
	}
	else {
		/* _hoops_IAHA _hoops_CAGH _hoops_SSCP _hoops_RPII _hoops_PSSGGR */
		if (texture->_hoops_RRIIR != null) {
			/* _hoops_IPCP _hoops_IAHA _hoops_CAGH _hoops_CSAP _hoops_PGHPR, _hoops_SARA _hoops_PIHA _hoops_SHH _hoops_GACC */
			_hoops_HPRH (texture->_hoops_RRIIR);
			texture->_hoops_RRIIR = null;
		}

		HE_WARNING (HEC_TEXTURE, HES_INVALID_TRANSFORM_SEGMENT,
				Sprintf_N (null, "Texture '%n' camera segment no longer exists.",
				&texture->name));

		/* _hoops_RGAR _hoops_HPPPR _hoops_ARR */
		texture->_hoops_SRARP = null;
	}
}


GLOBAL_FUNCTION _hoops_RCR * HI_Clone_Texture (
	_hoops_RCR const *		texture) {
	_hoops_RCR *			_hoops_ISSGGR;

	ALLOC (_hoops_ISSGGR, _hoops_RCR);

	if (!texture) {
		ZERO_STRUCT (_hoops_ISSGGR, _hoops_RCR);

		/* _hoops_CISA _hoops_GGR _hoops_GRAA-_hoops_AHHR _hoops_HSSHH */
		_hoops_ISSGGR->_hoops_HIHI = 1;
		_hoops_ISSGGR->type = _hoops_GRIIR;
		_hoops_ISSGGR->_hoops_PSCC = _hoops_HSGRP;
		_hoops_ISSGGR->_hoops_HPIR._hoops_IIRH = 0.0f;
		_hoops_ISSGGR->_hoops_HPIR._hoops_CIRH = 1.0f;
		_hoops_ISSGGR->_hoops_HPIR._hoops_SIRH = 1.0f;
		_hoops_ISSGGR->_hoops_SCR |= _hoops_RCRH;
		_hoops_ISSGGR->_hoops_ICR [0] =
			_hoops_ISSGGR->_hoops_ICR [1] =
			_hoops_ISSGGR->_hoops_ICR [2] = 1;

		return _hoops_ISSGGR;
	}

	_hoops_RSAI (texture, _hoops_RCR, _hoops_ISSGGR);

	_hoops_ISSGGR->_hoops_HIHI = 1;
	_hoops_ISSGGR->_hoops_RHGH = null;

	if (texture->name.length > 0)
		HI_Copy_Name (&texture->name, &_hoops_ISSGGR->name);

	if (texture->_hoops_PAPIR != null) {
		_hoops_AAPIR *			_hoops_PAPIR = texture->_hoops_PAPIR;
		_hoops_AAPIR **		_hoops_ASRGR = &_hoops_ISSGGR->_hoops_PAPIR;

		while (_hoops_PAPIR != null) {
			_hoops_AAPIR *		_hoops_SPIPI;

			ZALLOC (_hoops_SPIPI, _hoops_AAPIR);
			HI_Copy_Name (&_hoops_PAPIR->name, &_hoops_SPIPI->name);

			_hoops_SPIPI->key = _hoops_PAPIR->key;

			*_hoops_ASRGR = _hoops_SPIPI;
			_hoops_ASRGR = &_hoops_SPIPI->next;
			_hoops_PAPIR = _hoops_PAPIR->next;
		}
	}

	if (_hoops_ISSGGR->image != null)
		_hoops_PRRH (_hoops_ISSGGR->image);

	if (_hoops_ISSGGR->_hoops_HGIIR != null)
		_hoops_PRRH (_hoops_ISSGGR->_hoops_HGIIR);

	if (_hoops_ISSGGR->_hoops_GAGH != null) {
		/*_hoops_IPS _hoops_RH _hoops_HIHP _hoops_IHAH _hoops_HIS _hoops_SR _hoops_PAH _hoops_GRPHA _hoops_SCH*/
		_hoops_GAAIR *	_hoops_AISHC;

		ALLOC (_hoops_AISHC, _hoops_GAAIR);
		_hoops_RSAI(_hoops_ISSGGR->_hoops_GAGH, _hoops_GAAIR, _hoops_AISHC);
		_hoops_AISHC->matrix._hoops_APRA.retain();
		_hoops_AISHC->_hoops_HIHI = 1;
		_hoops_ISSGGR->_hoops_GAGH=_hoops_AISHC;
	}

	if (_hoops_ISSGGR->_hoops_RRIIR != null) {
		_hoops_PRRH (_hoops_ISSGGR->_hoops_RRIIR);
	}

	if (texture->_hoops_RSR != null) {
		//_hoops_AA _hoops_IRS _hoops_ACAHP _hoops_IPS.
		_hoops_AGSA *s;

		ZALLOC (s, _hoops_AGSA);
		_hoops_RSAI (texture->_hoops_RSR, _hoops_AGSA, s);
		HI_Copy_Name (&texture->_hoops_RSR->shader_source, &s->shader_source);
		_hoops_ISSGGR->_hoops_RSR = s;
	}

	/* _hoops_RH _hoops_GRRSA _hoops_HRGR _hoops_HAR _hoops_CHHA */
	_hoops_ISSGGR->flags &= (int)~_hoops_RPRRP;

	return _hoops_ISSGGR;
}

#ifdef _hoops_SHRIP
local unsigned char _hoops_PASHH[] = {128, 128, 128, 128, 128, 128, 128, 128,
										128, 128, 128, 128, 128, 128, 128, 128};
#else
local unsigned char _hoops_PASHH[] = {255, 255, 255, 255,	 0,	  0,  0, 255,
										0,	 0,	  0, 255,  255, 255, 255, 255};
#endif


GLOBAL_FUNCTION void HI_Validate_Texture_Fallback_Image ()
{
	HI_Create_Image (&HOOPS_WORLD->_hoops_CIHGI,
				 null,
				 2, 2,
				 Image_RGBA32, 0,
				 _hoops_HGPGI,
				 (unsigned char *)_hoops_PASHH);
}


GLOBAL_FUNCTION _hoops_RCR * HI_Activate_Texture(
	_hoops_RCR const *			texture,
	_hoops_CPAIR const *	_hoops_CICSR,
	bool					_hoops_PHIPP,
	Integer32				_hoops_PSSGA) 
{

	_hoops_RCR * _hoops_ISSGGR = 0;

	if (texture->image != null || texture->_hoops_HGIIR != null || BIT (texture->_hoops_SCR, _hoops_GSR)) {
		/* _hoops_RGR _hoops_HRGR _hoops_RH _hoops_AIRA _hoops_HH */
		if (texture->_hoops_IRARP != null)
			_hoops_RSSGGR((_hoops_RCR *)texture); /* _hoops_HIIC _hoops_SGGR _hoops_RCIC-_hoops_PPIA */

		if (texture->_hoops_SRARP != null)
			_hoops_HSSGGR((_hoops_RCR *)texture); /* _hoops_HIIC _hoops_SGGR _hoops_RCIC-_hoops_PPIA */

		_hoops_ISSGGR = HI_Clone_Texture(texture);
		_hoops_ISSGGR->flags |= _hoops_GHRRP;
		_hoops_ISSGGR->_hoops_PSSGA = _hoops_PSSGA;

		if (texture->image && BIT(_hoops_ISSGGR->image->flags, _hoops_SHCC))
			_hoops_ISSGGR->flags |= _hoops_IAPS;

		HOOPS_WORLD->_hoops_PCRGH++;
	}
	else {
		Integer32		key;
		int				i;

		if (!_hoops_CICSR)
			return 0;

		if ((key = texture->_hoops_PAPIR->key) == 0)
			return 0;

		for (i=0; i<_hoops_CICSR->count; i++) {
			if (key == _hoops_CICSR->keys[i]) {
				_hoops_RCR *	_hoops_CSSGGR = _hoops_CICSR->textures[i];

				if (_hoops_RAHSR (texture->_hoops_PAPIR->name, _hoops_CSSGGR->name)) {
					if (_hoops_CSSGGR->image || texture->_hoops_HGIIR) {
						_hoops_ISSGGR =  HI_Activate_Texture (_hoops_CSSGGR, 0, _hoops_PHIPP);
					}
					else {
						/* _hoops_GSGI _hoops_SCH _hoops_HA _hoops_CCIH _hoops_SCH _hoops_GH */
						if (!BIT(texture->flags, TF_UNEVALUATED) &&
							_hoops_CICSR->count - i >= 1 &&
							(texture->_hoops_PAPIR->key == texture->key &&
								_hoops_RAHSR (texture->_hoops_PAPIR->name, texture->name))) {

							_hoops_CPAIR _hoops_SSSGGR;

							_hoops_SSSGGR.count = _hoops_CICSR->count - i - 1;
							_hoops_SSSGGR.keys = &_hoops_CICSR->keys[i+1];
							_hoops_SSSGGR.textures = &_hoops_CICSR->textures[i+1];

							_hoops_ISSGGR = HI_Activate_Texture (_hoops_CSSGGR, &_hoops_SSSGGR, _hoops_PHIPP);
						}
						else {
							if (_hoops_CSSGGR != texture)
								_hoops_ISSGGR = HI_Activate_Texture (_hoops_CSSGGR, _hoops_CICSR, _hoops_PHIPP);
						}
					}

					/* _hoops_PHIS _hoops_ISSC _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_HH */
					if (!_hoops_ISSGGR)
						break;

					if (ANYBIT(_hoops_CSSGGR->flags, _hoops_CSGH|_hoops_AIA)) {
						_hoops_AAPIR *	_hoops_GGGRGR = _hoops_CSSGGR->_hoops_PAPIR;
						_hoops_AAPIR *	name = _hoops_CSSGGR->_hoops_PAPIR;
						int _hoops_ARIIR;

						ASSERT (!ALLBITS (_hoops_CSSGGR->flags, _hoops_CSGH|_hoops_AIA)); //_hoops_PGIA _hoops_HGIA

						if (BIT(_hoops_CSSGGR->flags, _hoops_AIA)) {
							_hoops_ISSGGR->flags |= _hoops_AIA;
							_hoops_ARIIR = 6;
						}
						else {
							_hoops_ISSGGR->flags |= _hoops_CSGH;
							_hoops_ARIIR = _hoops_CSSGGR->_hoops_ICR[2];
							_hoops_AIGA (_hoops_CSSGGR->_hoops_ICR, 3, int, _hoops_ISSGGR->_hoops_ICR);
						}

						ALLOC_ARRAY(_hoops_ISSGGR->_hoops_PRAH, _hoops_ARIIR, _hoops_RCR*);

						/* _hoops_HSGR _hoops_RH _hoops_SRS _hoops_SPR */
						_hoops_ISSGGR->_hoops_PRAH[0] = _hoops_ISSGGR;
						name = name->next;

						for (int ii=1; ii<_hoops_ARIIR; ii++) {
							_hoops_CSSGGR->_hoops_PAPIR = name;

							_hoops_ISSGGR->_hoops_PRAH[ii] = HI_Activate_Texture (_hoops_CSSGGR, _hoops_CICSR, _hoops_PHIPP);

							name = name->next;
						}

						_hoops_CSSGGR->_hoops_PAPIR = _hoops_GGGRGR;
					}

					_hoops_ISSGGR->flags |= _hoops_GHRRP;
					_hoops_ISSGGR->_hoops_PSSGA = _hoops_PSSGA;


					/* _hoops_CGPR _hoops_SR'_hoops_ASAR _hoops_CPHR _hoops_RGGRGR, _hoops_CCSAH _hoops_CGH _hoops_SHH _hoops_RH _hoops_AIRA, _hoops_PPR _hoops_RSIRR _hoops_CGH _hoops_SHH _hoops_RH _hoops_RIIS */
					if (!_hoops_ISSGGR->_hoops_PAPIR) {
						/*_hoops_SHARC (&_hoops_AGGRGR->_hoops_RSIRR, _hoops_RCSSA, &_hoops_AGGRGR->_hoops_PGGRGR);*/
						ZALLOC (_hoops_ISSGGR->_hoops_PAPIR, _hoops_AAPIR);
						HI_Copy_Name (&_hoops_ISSGGR->name, &_hoops_ISSGGR->_hoops_PAPIR->name);
					}
					_hoops_RGAIR (_hoops_ISSGGR->name);
					HI_Copy_Name (&texture->name, &_hoops_ISSGGR->name);

					/* _hoops_GA'_hoops_RA _hoops_GGCR _hoops_GII _hoops_AIRC _hoops_HII _hoops_IRS _hoops_HGHC _hoops_GCRSS _hoops_HH */
					if (BIT(texture->flags, TF_UNEVALUATED))
						return _hoops_ISSGGR;

					/* _hoops_GHAA _hoops_RH _hoops_IAHA _hoops_CAGH _hoops_RSGA _hoops_RPP _hoops_GII */
					if (texture->_hoops_IRARP) {
						_hoops_RSSGGR ((_hoops_RCR *)texture); /* _hoops_HIIC _hoops_SGGR _hoops_RCIC-_hoops_PPIA */

						if (texture->_hoops_GAGH) {
							if (_hoops_ISSGGR->_hoops_GAGH) {
								_hoops_GAAIR * _hoops_AISHC;

								ALLOC (_hoops_AISHC, _hoops_GAAIR);
								_hoops_RSAI (_hoops_ISSGGR->_hoops_GAGH, _hoops_GAAIR, _hoops_AISHC);
								_hoops_AISHC->matrix._hoops_APRA.retain();
								HI_Multiply_Matrices (
										&_hoops_ISSGGR->_hoops_GAGH->matrix,
										&texture->_hoops_GAGH->matrix,
										&_hoops_AISHC->matrix);
								_hoops_HPRH (_hoops_ISSGGR->_hoops_GAGH);
								_hoops_ISSGGR->_hoops_GAGH = _hoops_AISHC;
								HI_Validate_Matrix_Adjoint (&_hoops_ISSGGR->_hoops_GAGH->matrix);
							}
							else {
								/*_hoops_IPS _hoops_RH _hoops_HIHP _hoops_IHAH _hoops_HIS _hoops_SR _hoops_PAH _hoops_GRPHA _hoops_SCH*/
								_hoops_GAAIR * _hoops_AISHC;

								ALLOC (_hoops_AISHC, _hoops_GAAIR);
								_hoops_RSAI (texture->_hoops_GAGH, _hoops_GAAIR, _hoops_AISHC);
								_hoops_AISHC->matrix._hoops_APRA.retain();
								_hoops_AISHC->_hoops_HIHI = 1;
								/* _hoops_RRRPR ? */
								_hoops_ISSGGR->_hoops_GAGH=_hoops_AISHC;
							}
						}
					}

					/* _hoops_GHAA _hoops_RH _hoops_IAHA _hoops_CAGH _hoops_SARA _hoops_RPP _hoops_GII */
					if (texture->_hoops_SRARP) {
						_hoops_HSSGGR ((_hoops_RCR *)texture); /* _hoops_HIIC _hoops_SGGR _hoops_RCIC-_hoops_PPIA */
						if (_hoops_ISSGGR->_hoops_RRIIR != null)
							_hoops_HPRH (_hoops_ISSGGR->_hoops_RRIIR);
						if ((_hoops_ISSGGR->_hoops_RRIIR = texture->_hoops_RRIIR) != null)
							_hoops_PRRH (_hoops_ISSGGR->_hoops_RRIIR);
					}

					/* _hoops_PCCP _hoops_HHHA _hoops_SSRA _hoops_PSIAA _hoops_PCCP _hoops_CHHA _hoops_SPR*/
					if (BIT(texture->flags, _hoops_SRRRP)) {
						_hoops_ISSGGR->flags |= _hoops_SRRRP;
						_hoops_ISSGGR->_hoops_CGA = texture->_hoops_CGA;
					}
					else
						_hoops_ISSGGR->_hoops_CGA = texture->_hoops_CGA;

					/* _hoops_RIIPS _hoops_HGGRGR */
					if (BIT(texture->flags, _hoops_HPRRP)) {
						if (BIT(texture->_hoops_SCR, _hoops_RCRH))
							_hoops_ISSGGR->_hoops_SCR |= _hoops_RCRH;
						else
							_hoops_ISSGGR->_hoops_SCR &= ~_hoops_RCRH;

						_hoops_ISSGGR->flags |= _hoops_HPRRP;
					}

					if (BIT(texture->flags, _hoops_GPRRP)) {
						if (BIT(texture->_hoops_SCR, _hoops_IHRRP))
							_hoops_ISSGGR->_hoops_SCR |= _hoops_IHRRP;
						else
							_hoops_ISSGGR->_hoops_SCR &= ~_hoops_IHRRP;

						_hoops_ISSGGR->flags |= _hoops_GPRRP;
					}

					if (BIT(texture->flags, _hoops_PPRRP)) {
						if (BIT(texture->_hoops_SCR, _hoops_IGA))
							_hoops_ISSGGR->_hoops_SCR |= _hoops_IGA;
						else
							_hoops_ISSGGR->_hoops_SCR &= ~_hoops_IGA;

						_hoops_ISSGGR->flags |= _hoops_PPRRP;
					}

					if (BIT(texture->flags, _hoops_IPRRP)) {
						if (BIT(texture->_hoops_SCR, _hoops_PGA))
							_hoops_ISSGGR->_hoops_SCR |= _hoops_PGA;
						else
							_hoops_ISSGGR->_hoops_SCR &= ~_hoops_PGA;

						_hoops_ISSGGR->flags |= _hoops_IPRRP;
					}
					if (BIT(texture->flags, _hoops_CPRRP)) {
						if (BIT(texture->_hoops_SCR, _hoops_CHRRP))
							_hoops_ISSGGR->_hoops_SCR |= _hoops_CHRRP;
						else
							_hoops_ISSGGR->_hoops_SCR &= ~_hoops_CHRRP;

						_hoops_ISSGGR->flags |= _hoops_CPRRP;
					}

					if (BIT(texture->flags, _hoops_IPGH)) {
						if (BIT(texture->_hoops_SCR, _hoops_IPGH))
							_hoops_ISSGGR->_hoops_SCR |= _hoops_IPGH;
						else
							_hoops_ISSGGR->_hoops_SCR &= ~_hoops_IPGH;

						_hoops_ISSGGR->flags |= _hoops_IPGH;
					}

					/* _hoops_HPPR _hoops_IS _hoops_SHH _hoops_AHGCI */
					if (ANYBIT (texture->flags,
								_hoops_HRRRP|
								_hoops_IRRRP|
								_hoops_APRRP|
								_hoops_RARRP|
								_hoops_AARRP|
								_hoops_SARRP|
								_hoops_HIRH)) {

						/* _hoops_RARHR _hoops_HHHA _hoops_HRP */
						if (BIT(texture->flags, _hoops_HRRRP)) {
							_hoops_ISSGGR->flags |= _hoops_HRRRP;
							_hoops_ISSGGR->_hoops_PSR = texture->_hoops_PSR;
						}
						if (BIT(texture->flags, _hoops_IRRRP)) {
							_hoops_ISSGGR->flags |= _hoops_IRRRP;
							_hoops_ISSGGR->_hoops_RSCP = texture->_hoops_RSCP;
						}
						if (BIT(texture->flags, _hoops_APRRP)) {
							_hoops_ISSGGR->flags |= _hoops_APRRP;
							_hoops_ISSGGR->_hoops_GAARP = texture->_hoops_GAARP;
						}
						if (BIT(texture->flags, _hoops_RARRP)) {
							_hoops_ISSGGR->flags |= _hoops_RARRP;
							_hoops_ISSGGR->_hoops_PSCC = texture->_hoops_PSCC;
						}
						if (BIT(texture->flags, _hoops_AARRP)) {
							_hoops_ISSGGR->flags |= _hoops_AARRP;
							_hoops_ISSGGR->_hoops_RARH = texture->_hoops_RARH;
						}
						if (BIT(texture->flags, _hoops_SARRP)) {
							_hoops_ISSGGR->flags |= _hoops_SARRP;
							_hoops_ISSGGR->_hoops_HPIR._hoops_IIRH = texture->_hoops_HPIR._hoops_IIRH;
							_hoops_ISSGGR->_hoops_HPIR._hoops_CIRH = texture->_hoops_HPIR._hoops_CIRH;
						}
						if (BIT(texture->flags, _hoops_HIRH)) {
							if (BIT(texture->flags, _hoops_PARRP)) {
								_hoops_ISSGGR->flags |= _hoops_PARRP|_hoops_HIRH;
								_hoops_ISSGGR->_hoops_HPIR._hoops_RSRRP = texture->_hoops_HPIR._hoops_RSRRP;
							}
							if (BIT(texture->flags, _hoops_HARRP)) {
								_hoops_ISSGGR->flags |= _hoops_HARRP|_hoops_HIRH;
								_hoops_ISSGGR->_hoops_HPIR._hoops_ASRRP = texture->_hoops_HPIR._hoops_ASRRP;
							}
							if (BIT(texture->flags, _hoops_IARRP)) {
								_hoops_ISSGGR->flags |= _hoops_IARRP|_hoops_HIRH;
								_hoops_ISSGGR->_hoops_HPIR._hoops_PSRRP = texture->_hoops_HPIR._hoops_PSRRP;
							}
							if (BIT(texture->flags, _hoops_CARRP)) {
								_hoops_ISSGGR->flags |= _hoops_CARRP|_hoops_HIRH;
								_hoops_ISSGGR->_hoops_HPIR._hoops_HSRRP = texture->_hoops_HPIR._hoops_HSRRP;
							}
						}
					}

					return _hoops_ISSGGR;
				}
			}
		}

		/* _hoops_CIPHC _hoops_IS _hoops_SSS _hoops_RH _hoops_HH */
		if (_hoops_PHIPP) {
			_hoops_ISSGGR = HI_Clone_Texture (0);
			_hoops_ISSGGR->flags |= _hoops_RARRP;
			_hoops_ISSGGR->flags |= _hoops_SPRRP;
			_hoops_ISSGGR->flags |= _hoops_GHRRP;
			_hoops_ISSGGR->_hoops_PSSGA = _hoops_PSSGA;

			_hoops_ISSGGR->_hoops_PSCC = _hoops_HSCC;
			if (!HOOPS_WORLD->_hoops_CIHGI)
				HI_Validate_Texture_Fallback_Image ();
			_hoops_ISSGGR->image = HOOPS_WORLD->_hoops_CIHGI;
			_hoops_PRRH(_hoops_ISSGGR->image);

			HOOPS_WORLD->_hoops_HCRGH++;
		}
	}

	return _hoops_ISSGGR;
}

local Attribute * _hoops_IGGRGR(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR)
{
	_hoops_CPAIR const *	_hoops_CRGIH = (_hoops_CPAIR const *)_hoops_CPACR;
	_hoops_CPAIR alter *	_hoops_SRGIH = (_hoops_CPAIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	ASSERT (_hoops_SRGIH->count == 1);

	_hoops_RCR *	texture = _hoops_SRGIH->textures[0];

	if (_hoops_CRGIH) {
		for (int i=0; i<_hoops_CRGIH->count; i++) {
			if (_hoops_CRGIH->keys[i] == texture->key) {
				if (!_hoops_RAHSR (texture->name, _hoops_CRGIH->textures[i]->name))
					continue;

				if (BIT (texture->flags, _hoops_RPRRP) &&
					!BIT (_hoops_CRGIH->textures[i]->flags, _hoops_RPRRP))
					return null; // _hoops_GRHP _hoops_RHGS _hoops_APRIP

				if (BIT (_hoops_CRGIH->textures[i]->flags, _hoops_RPRRP) ||
					(!texture->image && _hoops_CRGIH->textures[i]->image &&
					 _hoops_RAHSR(texture->_hoops_PAPIR->name, _hoops_CRGIH->textures[i]->name))) {

					_hoops_RCR *	_hoops_CGGRGR = (_hoops_RCR alter *)_hoops_CRGIH->textures[i];

					/* _hoops_GRH _hoops_AGIR _hoops_IH _hoops_SGGRGR _hoops_ISCP _hoops_HAII _hoops_HCGP _hoops_CSCR */
					/* _hoops_RGR _hoops_CRHPR _hoops_GPACI _hoops_IPHR: _hoops_HH._hoops_GGSGS */
					if (!BIT (texture->flags, _hoops_RPRRP) &&
						_hoops_RAHSR (texture->_hoops_PAPIR->name, _hoops_CGGRGR->name)) {

						/* _hoops_IPS _hoops_PPR _hoops_HASC _hoops_HHHA _hoops_HRP*/
						texture->image = _hoops_CGGRGR->image;
						texture->image->texture = 0;
						_hoops_CGGRGR->image = 0;

						/* _hoops_PCCP _hoops_HHHA _hoops_SSRA _hoops_PSIAA _hoops_PCCP _hoops_CHHA _hoops_SPR*/
						if (BIT(_hoops_CGGRGR->flags, _hoops_SRRRP) &&
							!BIT(texture->flags, _hoops_SRRRP)) {
							texture->flags |= _hoops_SRRRP;
							texture->_hoops_CGA = _hoops_CGGRGR->_hoops_CGA;
						}

						if (BIT(_hoops_CGGRGR->flags, _hoops_GPRRP) &&
							!BIT(texture->flags, _hoops_GPRRP)) {
							texture->flags |= _hoops_GPRRP;
							if (BIT(_hoops_CGGRGR->_hoops_SCR, _hoops_IHRRP))
								texture->_hoops_SCR |= _hoops_IHRRP;
							else
								texture->_hoops_SCR &= ~_hoops_IHRRP;
						}

						if (BIT(_hoops_CGGRGR->flags, _hoops_HPRRP) &&
							!BIT(texture->flags, _hoops_HPRRP)) {
							texture->flags |= _hoops_HPRRP;
							if (BIT(_hoops_CGGRGR->_hoops_SCR, _hoops_RCRH))
								texture->_hoops_SCR |= _hoops_RCRH;
							else
								texture->_hoops_SCR &= ~_hoops_RCRH;
						}

						if (BIT(_hoops_CGGRGR->flags, _hoops_PPRRP) &&
							!BIT(texture->flags, _hoops_PPRRP)) {
							texture->flags |= _hoops_PPRRP;
							if (BIT(_hoops_CGGRGR->_hoops_SCR, _hoops_IGA))
								texture->_hoops_SCR |= _hoops_IGA;
							else
								texture->_hoops_SCR &= ~_hoops_IGA;
						}

						if (BIT(_hoops_CGGRGR->flags, _hoops_IPRRP) &&
							!BIT(texture->flags, _hoops_IPRRP)) {
							texture->flags |= _hoops_IPRRP;
							if (BIT(_hoops_CGGRGR->_hoops_SCR, _hoops_PGA))
								texture->_hoops_SCR |= _hoops_PGA;
							else
								texture->_hoops_SCR &= ~_hoops_PGA;
						}
						if (BIT(_hoops_CGGRGR->flags, _hoops_CPRRP) &&
							!BIT(texture->flags, _hoops_CPRRP)) {
							texture->flags |= _hoops_CPRRP;
							if (BIT(_hoops_CGGRGR->_hoops_SCR, _hoops_CHRRP))
								texture->_hoops_SCR |= _hoops_CHRRP;
							else
								texture->_hoops_SCR &= ~_hoops_CHRRP;
						}

						if (BIT(_hoops_CGGRGR->flags, _hoops_IPGH) &&
							!BIT(texture->flags, _hoops_IPGH)) {
							texture->flags |= _hoops_IPGH;
							if (BIT(_hoops_CGGRGR->_hoops_SCR, _hoops_IPGH))
								texture->_hoops_SCR |= _hoops_IPGH;
							else
								texture->_hoops_SCR &= ~_hoops_IPGH;
						}

						/* _hoops_HPPR _hoops_IS _hoops_SHH _hoops_AHGCI */
						if (ANYBIT (_hoops_CGGRGR->flags,
									_hoops_HRRRP|
									_hoops_IRRRP|
									_hoops_RARRP|
									_hoops_AARRP|
									_hoops_SARRP|
									_hoops_HIRH)) {

							/* _hoops_GRGRGR _hoops_HHHA _hoops_HRP */
							if (BIT(_hoops_CGGRGR->flags, _hoops_HRRRP) &&
								!BIT(texture->flags, _hoops_HRRRP)) {
								texture->flags |= _hoops_HRRRP;
								texture->_hoops_PSR = _hoops_CGGRGR->_hoops_PSR;
							}
							if (BIT(_hoops_CGGRGR->flags, _hoops_IRRRP) &&
								!BIT(texture->flags, _hoops_IRRRP)) {
								texture->flags |= _hoops_IRRRP;
								texture->_hoops_RSCP = _hoops_CGGRGR->_hoops_RSCP;
							}
							if (BIT(_hoops_CGGRGR->flags, _hoops_RARRP) &&
								!BIT(texture->flags, _hoops_RARRP)) {
								texture->flags |= _hoops_RARRP;
								texture->_hoops_PSCC = _hoops_CGGRGR->_hoops_PSCC;
							}
							if (BIT(_hoops_CGGRGR->flags, _hoops_AARRP) &&
								!BIT(texture->flags, _hoops_AARRP)) {
								texture->flags |= _hoops_AARRP;
								texture->_hoops_RARH = _hoops_CGGRGR->_hoops_RARH;
							}
							if (BIT(_hoops_CGGRGR->flags, _hoops_SARRP) &&
								!BIT(texture->flags, _hoops_SARRP)) {
								texture->flags |= _hoops_SARRP;
								texture->_hoops_HPIR._hoops_IIRH = _hoops_CGGRGR->_hoops_HPIR._hoops_IIRH;
								texture->_hoops_HPIR._hoops_CIRH = _hoops_CGGRGR->_hoops_HPIR._hoops_CIRH;
							}
							if (BIT(_hoops_CGGRGR->flags, _hoops_HIRH)) {
								if (BIT(_hoops_CGGRGR->flags, _hoops_PARRP) &&
									!BIT(texture->flags, _hoops_PARRP)) {
									texture->flags |= _hoops_PARRP|_hoops_HIRH;
									texture->_hoops_HPIR._hoops_RSRRP = _hoops_CGGRGR->_hoops_HPIR._hoops_RSRRP;
								}
								if (BIT(_hoops_CGGRGR->flags, _hoops_HARRP) &&
									!BIT(texture->flags, _hoops_HARRP)) {
									texture->flags |= _hoops_HARRP|_hoops_HIRH;
									texture->_hoops_HPIR._hoops_ASRRP = _hoops_CGGRGR->_hoops_HPIR._hoops_ASRRP;
								}
								if (BIT(_hoops_CGGRGR->flags, _hoops_IARRP) &&
									!BIT(texture->flags, _hoops_IARRP)) {
									texture->flags |= _hoops_IARRP|_hoops_HIRH;
									texture->_hoops_HPIR._hoops_PSRRP = _hoops_CGGRGR->_hoops_HPIR._hoops_PSRRP;
								}
								if (BIT(_hoops_CGGRGR->flags, _hoops_CARRP) &&
									!BIT(texture->flags, _hoops_CARRP)) {
									texture->flags |= _hoops_CARRP|_hoops_HIRH;
									texture->_hoops_HPIR._hoops_HSRRP = _hoops_CGGRGR->_hoops_HPIR._hoops_HSRRP;
								}
							}
						}
					}
					else
						HE_WARNING (HEC_IMAGE, HES_REDEFINING_NAME,
							Sprintf_N (null, "Re-defining image name '%n'", &texture->name));
				}
				else
					HE_WARNING (HEC_TEXTURE, HES_REDEFINING_NAME,
						Sprintf_N (null, "Re-defining texture '%n'", &texture->name));

				/*_hoops_SGPHP _hoops_RH _hoops_HIS _hoops_ISCP _hoops_CCGCS _hoops_CRPR _hoops_ASSP'_hoops_RA _hoops_HGCR _hoops_IRGR*/
				_hoops_CRGIH->textures[i]->owner = 0;
				_hoops_HPRH(_hoops_CRGIH->textures[i]);

				// _hoops_GCGRA
				_hoops_PGRCA(_hoops_CRGIH)->textures[i] = texture;
				_hoops_PGRCA(_hoops_CRGIH)->keys[i] = texture->key;

				FREE_ARRAY (_hoops_SRGIH->textures, 1, _hoops_RCR*);
				FREE_ARRAY (_hoops_SRGIH->keys, 1, Integer32);

				/* _hoops_SRAI _hoops_RHGS _hoops_CCGCS _hoops_PPR _hoops_IIIAA _hoops_CGPHS */
				_hoops_SRGIH->textures = _hoops_CRGIH->textures;
				_hoops_SRGIH->keys = _hoops_CRGIH->keys;
				_hoops_SRGIH->count = _hoops_CRGIH->count;

				_hoops_PGRCA(_hoops_CRGIH)->textures = 0;
				_hoops_PGRCA(_hoops_CRGIH)->keys = 0;
				_hoops_PGRCA(_hoops_CRGIH)->count = 0;

				return _hoops_SRGIH;
			}
		}

		if (_hoops_CRGIH->count > 0) {
			int	count = _hoops_CRGIH->count+1;

			_hoops_RCR **	textures;
			ZALLOC_ARRAY(textures, count, _hoops_RCR*);

			Integer32 *	keys;
			ALLOC_ARRAY(keys, count, Integer32);

			_hoops_AIGA(_hoops_SRGIH->textures, 1, _hoops_RCR*, textures);
			_hoops_AIGA(_hoops_SRGIH->keys, 1, Integer32, keys);
			FREE_ARRAY(_hoops_SRGIH->textures, 1, _hoops_RCR*);
			FREE_ARRAY(_hoops_SRGIH->keys, 1, Integer32);

			// _hoops_RGR _hoops_HRGR _hoops_HIGIP
			_hoops_AIGA(_hoops_CRGIH->keys, _hoops_CRGIH->count, Integer32, &keys[1]);
			_hoops_AIGA(_hoops_CRGIH->textures, _hoops_CRGIH->count, _hoops_RCR*, &textures[1]);
			FREE_ARRAY(_hoops_CRGIH->textures, _hoops_CRGIH->count, _hoops_RCR*);
			FREE_ARRAY(_hoops_CRGIH->keys, _hoops_CRGIH->count, Integer32);
			_hoops_PGRCA(_hoops_CRGIH)->textures = null;
			_hoops_PGRCA(_hoops_CRGIH)->keys = null;
			_hoops_PGRCA(_hoops_CRGIH)->count = 0;

			_hoops_SRGIH->textures = textures;
			_hoops_SRGIH->keys = keys;
			_hoops_SRGIH->count = count;
		}
	}

	return _hoops_SRGIH;
}

GLOBAL_FUNCTION void HI_Record_Texture_Definition (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_RCR *				texture)
{

	_hoops_CPAIR *	_hoops_RRGRGR;
	ZALLOC (_hoops_RRGRGR, _hoops_CPAIR);
	_hoops_RRGRGR->count = 1;
	ZALLOC_ARRAY(_hoops_RRGRGR->textures, 1, _hoops_RCR*);
	ALLOC_ARRAY(_hoops_RRGRGR->keys, 1, Integer32);

	_hoops_RRGRGR->textures[0] = texture;
	_hoops_RRGRGR->keys[0] = texture->key;

	if (!HI_Set_Attribute (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, _hoops_IPAIR, _hoops_IGGRGR, _hoops_RRGRGR)) {
		FREE_ARRAY(_hoops_RRGRGR->textures, 1, _hoops_RCR*);
		FREE_ARRAY(_hoops_RRGRGR->keys, 1, Integer32);
		FREE (_hoops_RRGRGR, _hoops_CPAIR);
	}
}



local void _hoops_ARGRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_HCRPR const &			_hoops_CRPCR)
{
	_hoops_ICIIR(_hoops_RIGC);
#ifndef DISABLE_TEXTURING

	_hoops_RCR * texture = HI_Look_Up_Texture (_hoops_RIGC, _hoops_SRCP, &_hoops_CRPCR);

	if (!texture) {
		HE_WARNING (HEC_TEXTURE, HES_BAD_DEFINITION,
				Sprintf_N (null, "Texture '%n' not currently "
					"defined - can't UnDefine", &_hoops_CRPCR));
	}
	else {
		/* _hoops_HSPAA _hoops_RH _hoops_HH _hoops_IS _hoops_RH _hoops_PRGRGR */
		if (!texture->image) {
			_hoops_HPRH (texture);
		}
		else {
			/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_CHHA _hoops_HH _hoops_PSCR _hoops_SR _hoops_HIAP _hoops_SCH _hoops_IS _hoops_SHIR */
			/* _hoops_GRP _hoops_IRS _hoops_SHIR _hoops_HH _hoops_IS _hoops_HGCR _hoops_RH _hoops_AAP */
			_hoops_RCR *	_hoops_ISSGGR = HI_Clone_Texture (null);

			if (texture->_hoops_GAGH != null)
				_hoops_HPRH (texture->_hoops_GAGH);
			if (texture->_hoops_RRIIR != null)
				_hoops_HPRH (texture->_hoops_RRIIR);

			texture->_hoops_IRARP = _hoops_ISSGGR->_hoops_IRARP;
			if ((texture->_hoops_GAGH = _hoops_ISSGGR->_hoops_GAGH) != null)
				_hoops_PRRH (texture->_hoops_GAGH);
			texture->_hoops_SRARP = _hoops_ISSGGR->_hoops_SRARP;
			if ((texture->_hoops_RRIIR = _hoops_ISSGGR->_hoops_RRIIR) != null)
				_hoops_PRRH (texture->_hoops_RRIIR);
			texture->flags = _hoops_ISSGGR->flags;
			texture->_hoops_SCR = _hoops_ISSGGR->_hoops_SCR;
			texture->_hoops_PSR = _hoops_ISSGGR->_hoops_PSR;
			texture->_hoops_GAARP = _hoops_ISSGGR->_hoops_GAARP;
			texture->_hoops_CGA = _hoops_ISSGGR->_hoops_CGA;
			texture->_hoops_PSCC = _hoops_ISSGGR->_hoops_PSCC;
			texture->_hoops_RARH = _hoops_ISSGGR->_hoops_RARH;
			texture->_hoops_HPIR = _hoops_ISSGGR->_hoops_HPIR;

			texture->flags |= _hoops_RPRRP;
			if (texture->_hoops_PSR == HK_PS_UNSPECIFIED)
				texture->_hoops_PSR = HK_PS_UV;

			_hoops_HPRH (_hoops_ISSGGR);
		}
	}
#endif
}


local _hoops_RCR * _hoops_HRGRGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	Image *					image,
	_hoops_HCRPR const &			name,
	char const *			definition,
	Option_Value *			option_list,
	bool					_hoops_IRGRGR)
{
	/* _hoops_GISA _hoops_IRS _hoops_CCAH _hoops_HH _hoops_IPPHR */
	_hoops_RCR *	texture = HI_Clone_Texture(0);

	if (_hoops_SRCP)
		texture->owner = (_hoops_HPAH *)_hoops_SRCP;

	/* _hoops_PHIR _hoops_GGR _hoops_RH _hoops_HH _hoops_IPPHR _hoops_CCA _hoops_SHIR _hoops_HSH*/
	HI_Copy_Name (&name, &texture->name);

	if (!_hoops_ACCCA (_hoops_RIGC, _hoops_SRCP, texture, definition, option_list)) {
		HI_Au_Revoir((_hoops_HPAH*)texture);
		return 0;
	}

	if (_hoops_IRGRGR) {
		if (texture->_hoops_PSR == HK_PS_UNSPECIFIED)
			texture->_hoops_PSR = HK_PS_WORLD;
	}
	else {
		//_hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_IRS _hoops_ASRH _hoops_ARCR
		if (texture->_hoops_ICR[0] == 1 &&
			texture->_hoops_ICR[1] == 1 &&
			texture->_hoops_ICR[2] == 1) {
			_hoops_AAPIR const *ptr = texture->_hoops_PAPIR;
			int count = 0;
			while (ptr != null) {
				count++;
				ptr = ptr->next;
			}
			if (count == 6)
				texture->flags |= _hoops_AIA;
		}
		else if (texture->_hoops_ICR[2] > 1)
			texture->flags |= _hoops_CSGH;

		if (image) {
			_hoops_PRRH(image);
			_hoops_PRRH(texture);
			image->texture = texture;
			texture->image = image;
			texture->flags |= _hoops_RPRRP;
			if (texture->_hoops_PSR == HK_PS_UNSPECIFIED)
				texture->_hoops_PSR = HK_PS_UV;
		}
		else if ((!texture->_hoops_PAPIR || texture->_hoops_PAPIR->name.length == 0) && !texture->_hoops_HGIIR) {
			HE_WARNING (HEC_TEXTURE, HES_IMAGE_MISSING, Sprintf_N (null, "Texture '%n' has no source ", &texture->name));
			HI_Au_Revoir((_hoops_HPAH*)texture);
			return 0;
		}
	}

	if (_hoops_IRGRGR) {
		_hoops_RCR *	_hoops_CGGRGR = HI_Look_Up_Texture(_hoops_RIGC, _hoops_SRCP, &texture->name);
		if (_hoops_CGGRGR)
			_hoops_ARGRGR (_hoops_RIGC, _hoops_SRCP, texture->name);
	}
	else if (_hoops_SRCP && (image || texture->_hoops_PAPIR && _hoops_RAHSR(texture->_hoops_PAPIR->name, texture->name))) {
		_hoops_RCR *	_hoops_ISSGGR = texture;

		texture = HI_Look_Up_Texture(_hoops_RIGC, _hoops_SRCP, &_hoops_ISSGGR->name);

		if (texture) {
			if (image) {
				if (texture->image) {
					texture->image->texture = null;
					_hoops_HPRH(texture->image);
				}

				texture->_hoops_HPIR._hoops_SIRH = _hoops_ISSGGR->_hoops_HPIR._hoops_SIRH;
				texture->_hoops_HPIR._hoops_IPIR = _hoops_ISSGGR->_hoops_HPIR._hoops_IPIR;

				if (!texture->_hoops_IRARP)
					texture->_hoops_IRARP = _hoops_ISSGGR->_hoops_IRARP;

				texture->_hoops_GAGH = null;

				if (!texture->_hoops_SRARP)
					texture->_hoops_SRARP = _hoops_ISSGGR->_hoops_SRARP;

				texture->_hoops_RRIIR = null;

				if (!BIT(texture->flags, _hoops_HPRRP)) {
					if (BIT(_hoops_ISSGGR->_hoops_SCR, _hoops_RCRH))
						texture->_hoops_SCR |= _hoops_RCRH;
					else
						texture->_hoops_SCR &= ~_hoops_RCRH;
				}

				if (!BIT(texture->flags, _hoops_GPRRP)) {
					if (BIT(_hoops_ISSGGR->_hoops_SCR, _hoops_IHRRP))
						texture->_hoops_SCR |= _hoops_IHRRP;
					else
						texture->_hoops_SCR &= ~_hoops_IHRRP;
				}

				if (!BIT(texture->flags, _hoops_PPRRP)) {
					if (BIT(_hoops_ISSGGR->_hoops_SCR, _hoops_IGA))
						texture->_hoops_SCR |= _hoops_IGA;
					else
						texture->_hoops_SCR &= ~_hoops_IGA;
				}

				if (!BIT(texture->flags, _hoops_IPRRP)) {
					if (BIT(_hoops_ISSGGR->_hoops_SCR, _hoops_PGA))
						texture->_hoops_SCR |= _hoops_PGA;
					else
						texture->_hoops_SCR &= ~_hoops_PGA;
				}
				if (!BIT(texture->flags, _hoops_CPRRP)) {
					if (BIT(_hoops_ISSGGR->_hoops_SCR, _hoops_CHRRP))
						texture->_hoops_SCR |= _hoops_CHRRP;
					else
						texture->_hoops_SCR &= ~_hoops_CHRRP;
				}

				if (!BIT(texture->flags, _hoops_SARRP)) {
					texture->_hoops_HPIR._hoops_IIRH = _hoops_ISSGGR->_hoops_HPIR._hoops_IIRH;
					texture->_hoops_HPIR._hoops_CIRH = _hoops_ISSGGR->_hoops_HPIR._hoops_CIRH;
				}

				if (!BIT(texture->flags, _hoops_HRRRP))
					texture->_hoops_PSR = _hoops_ISSGGR->_hoops_PSR;

				if (!BIT(texture->flags, _hoops_IRRRP))
					texture->_hoops_RSCP = _hoops_ISSGGR->_hoops_RSCP;

				if (!BIT(texture->flags, _hoops_APRRP))
					texture->_hoops_GAARP = _hoops_ISSGGR->_hoops_GAARP;

				if (!BIT(texture->flags, _hoops_SRRRP))
					texture->_hoops_CGA = _hoops_ISSGGR->_hoops_CGA;

				if (!BIT(texture->flags, _hoops_RARRP))
					texture->_hoops_PSCC = _hoops_ISSGGR->_hoops_PSCC;

				if (!BIT(texture->flags, _hoops_AARRP))
					texture->_hoops_RARH = _hoops_ISSGGR->_hoops_RARH;

				if (!BIT(texture->flags, _hoops_PARRP))
					texture->_hoops_HPIR._hoops_RSRRP = _hoops_ISSGGR->_hoops_HPIR._hoops_RSRRP;

				if (!BIT(texture->flags, _hoops_HARRP))
					texture->_hoops_HPIR._hoops_ASRRP = _hoops_ISSGGR->_hoops_HPIR._hoops_ASRRP;

				if (!BIT(texture->flags, _hoops_IARRP))
					texture->_hoops_HPIR._hoops_PSRRP = _hoops_ISSGGR->_hoops_HPIR._hoops_PSRRP;

				if (!BIT(texture->flags, _hoops_CARRP))
					texture->_hoops_HPIR._hoops_HSRRP = _hoops_ISSGGR->_hoops_HPIR._hoops_HSRRP;

				texture->flags |= _hoops_ISSGGR->flags;

				/* _hoops_SRAI _hoops_CCAH _hoops_CSCR */
				image->texture = texture;
				_hoops_ISSGGR->image=null;
				texture->image = image;
				texture->flags |= _hoops_RPRRP;
			}
			else {
				/* _hoops_IPS _hoops_CCAH _hoops_HH _hoops_AAP _hoops_IS _hoops_RHGS _hoops_HH*/
				if (texture->_hoops_GAGH != null)
					_hoops_HPRH (texture->_hoops_GAGH);
				if (texture->_hoops_RRIIR != null)
					_hoops_HPRH (texture->_hoops_RRIIR);

				texture->_hoops_IRARP = _hoops_ISSGGR->_hoops_IRARP;
				if ((texture->_hoops_GAGH = _hoops_ISSGGR->_hoops_GAGH) != null)
					_hoops_PRRH(texture->_hoops_GAGH);
				texture->_hoops_SRARP = _hoops_ISSGGR->_hoops_SRARP;
				if ((texture->_hoops_RRIIR = _hoops_ISSGGR->_hoops_RRIIR) != null)
					_hoops_PRRH(texture->_hoops_RRIIR);
				texture->flags = _hoops_ISSGGR->flags;
				texture->_hoops_SCR = _hoops_ISSGGR->_hoops_SCR;
				texture->_hoops_PSR = _hoops_ISSGGR->_hoops_PSR;
				texture->_hoops_RSCP = _hoops_ISSGGR->_hoops_RSCP;
				texture->_hoops_GAARP = _hoops_ISSGGR->_hoops_GAARP;
				texture->_hoops_CGA = _hoops_ISSGGR->_hoops_CGA;
				texture->_hoops_PSCC = _hoops_ISSGGR->_hoops_PSCC;
				texture->_hoops_RARH = _hoops_ISSGGR->_hoops_RARH;
				texture->_hoops_HPIR = _hoops_ISSGGR->_hoops_HPIR;
			}

			HI_Au_Revoir ((_hoops_HPAH*)_hoops_ISSGGR);
			return 0;
		}

		texture = _hoops_ISSGGR;
	}

	_hoops_HCARA(texture->name,texture->key);
	if (texture->_hoops_PAPIR) {
		_hoops_AAPIR *_hoops_AAGPC = texture->_hoops_PAPIR;

		while (_hoops_AAGPC) {
			_hoops_HCARA(_hoops_AAGPC->name, _hoops_AAGPC->key);
			_hoops_AAGPC = _hoops_AAGPC->next;
		}
	}

	return texture;
}
#endif

HC_INTERFACE void HC_CDECL HC_Define_Texture (
	char const *	name,
	char const *	definition)
{
	_hoops_PAPPR context("Define_Texture");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Define_Texture (%S, %S);\n", name, definition));
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars_Quoted (name, &_hoops_CRPCR, false);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_TEXTURE, HES_NULL_INPUT, "Texture name is blank or null");
		return;
	}

	_hoops_RPPPR();

	_hoops_CRCP const *	_hoops_SRCP = _hoops_RSPPR(context, _hoops_RPGHP);

	_hoops_RCR *	texture = _hoops_HRGRGR (context, _hoops_SRCP, 0, _hoops_CRPCR, definition, null, false);

	if (texture)
		HI_Record_Texture_Definition (context, (_hoops_CRCP *)_hoops_SRCP, texture);

	_hoops_IRRPR();

	_hoops_RGAIR(_hoops_CRPCR);

#endif
}


HC_INTERFACE void HC_CDECL HC_Define_Local_Texture (
	char const *		name,
	char const *		definition)
{
	_hoops_PAPPR context("Define_Local_Texture");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Define_Local_Texture (%S, %S);\n", name, definition));
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars_Quoted (name, &_hoops_CRPCR, false);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_TEXTURE, HES_NULL_INPUT, "Texture name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RHRPP)) != null) {
		_hoops_RCR * texture = _hoops_HRGRGR (context, (_hoops_CRCP *)target, 0, _hoops_CRPCR, definition, null, false);

		if (texture)
			HI_Record_Texture_Definition (context, (_hoops_CRCP *)target, texture);

		_hoops_IRRPR();
	}

	_hoops_RGAIR(_hoops_CRPCR);
#endif
}


HC_INTERFACE void HC_CDECL HC_Define_Shader (
	char const *		name,
	char const *		options,
	char const *		shader_source)
{
	_hoops_PAPPR context("Define_Shader");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Define_Shader(%S, %S,", name, options));
		HI_Dump_Code (Sprintf_S (null, "%s);\n", shader_source));
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars_Quoted (name, &_hoops_CRPCR, false);
	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_TEXTURE, HES_NULL_INPUT, "Shader name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RHRPP)) != null) {
		_hoops_RCR * texture = _hoops_HRGRGR (context, (_hoops_CRCP *)target, 0, _hoops_CRPCR, options, null, true);

		if (texture)
			HI_Record_Texture_Definition (context, (_hoops_CRCP *)target, texture);

		if (texture) {
			texture->_hoops_SCR |= _hoops_GSR;
			ZALLOC (texture->_hoops_RSR, _hoops_AGSA);
			texture->_hoops_RSR->id = _hoops_CIAGP (&HOOPS_WORLD->global_id);
			char const *ptr;
			float _hoops_CRGRGR = 0;
			ptr = shader_source;
			do {
				ptr = HI_First_Substring_In_String ("version", ptr);
				if (ptr != null) {
					ptr += 7;
					HI_Scan_Float (context, &ptr, null, &_hoops_CRGRGR);
				}
			} while (ptr && _hoops_CRGRGR < 19);
			if (_hoops_CRGRGR < 19) {
				HE_ERROR (HEC_TEXTURE, HES_VERSION_MISMATCH, "Shader source must contain the string '//version 19'");
			}
			HI_Copy_Chars_To_Name (shader_source, &texture->_hoops_RSR->shader_source);
		}
		_hoops_IRRPR();
	}

	_hoops_RGAIR(_hoops_CRPCR);
#endif
}



GLOBAL_FUNCTION void HI_Define_Implicit_Texture (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	Image *					image,
	Option_Value *			option_list)
{
#ifndef DISABLE_TEXTURING
	_hoops_RCR *	texture = _hoops_HRGRGR (_hoops_RIGC, _hoops_SRCP, image, image->name, null, option_list, false);

	if (texture)
		HI_Record_Texture_Definition (_hoops_RIGC, (_hoops_CRCP *)_hoops_SRCP, texture);
#endif
}


GLOBAL_FUNCTION _hoops_RCR * HI_Define_Shadow_Texture(
	_hoops_AIGPR *	_hoops_RIGC,
	Image *					image)
{
#ifndef DISABLE_TEXTURING
	_hoops_RCR * texture = _hoops_HRGRGR (_hoops_RIGC, 0, image, image->name, null, null, false);

	if (texture) {
		texture->_hoops_CGA = _hoops_ASCC;
		texture->_hoops_SCR = _hoops_ICARA;
		texture->flags |= _hoops_IAPS;
	}

	return texture;
#else
	return null;
#endif
}

GLOBAL_FUNCTION void HI_UnDefine_Texture (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_RCR *				texture) {
	_hoops_CPAIR *			_hoops_CICSR;
	int						i;
	bool					_hoops_SRGRGR = true;

	if (!texture->owner)
		return;

	_hoops_CICSR = (_hoops_CPAIR*) HI_Find_Attribute (_hoops_RIGC, (_hoops_HPAH *)texture->owner, -_hoops_IPAIR);

	if (!_hoops_CICSR)
		return;

	if (BIT(texture->flags, _hoops_GHRRP))
		_hoops_SRGRGR = false;

	for (i=0; i<_hoops_CICSR->count; i++) {
		if (texture == _hoops_CICSR->textures[i]) {
			if (_hoops_CICSR->count == 1) {
				FREE_ARRAY (_hoops_CICSR->textures, 1, _hoops_RCR *);
				FREE_ARRAY (_hoops_CICSR->keys, 1, Integer32);
				_hoops_CICSR->textures=0;
				_hoops_CICSR->keys = 0;
				_hoops_CICSR->count = 0;
			}
			else {
				_hoops_RCR** _hoops_HPRIP;
				Integer32* new_keys;
				int _hoops_RGCCA;

				_hoops_RGCCA = _hoops_CICSR->count-1;

				ALLOC_ARRAY (_hoops_HPRIP, _hoops_RGCCA, _hoops_RCR *);
				ALLOC_ARRAY (new_keys, _hoops_RGCCA, Integer32);

				if (i > 0) {
					_hoops_AIGA (_hoops_CICSR->textures, i, _hoops_RCR *, _hoops_HPRIP);
					_hoops_AIGA (_hoops_CICSR->keys, i, Integer32, new_keys);
				}

				if (i < _hoops_RGCCA) {
					_hoops_AIGA (&_hoops_CICSR->textures[i+1], _hoops_RGCCA-i, _hoops_RCR *, &_hoops_HPRIP[i]);
					_hoops_AIGA (&_hoops_CICSR->keys[i+1], _hoops_RGCCA-i, Integer32, &new_keys[i]);
				}

				FREE_ARRAY (_hoops_CICSR->textures, _hoops_CICSR->count, _hoops_RCR*);
				FREE_ARRAY (_hoops_CICSR->keys, _hoops_CICSR->count, Integer32);

				_hoops_CICSR->textures = _hoops_HPRIP;
				_hoops_CICSR->keys = new_keys;
				_hoops_CICSR->count  =_hoops_RGCCA;
			}
			_hoops_HPRH (texture);
			break;
		}
	}

	if (_hoops_SRGRGR) {
		_hoops_CICSR->_hoops_CPGPR |= _hoops_AHSGA;
		HI_Redraw_Attribute(_hoops_RIGC, _hoops_CICSR->owner, _hoops_IPAIR, null, null);
	}

	_hoops_HPRH (_hoops_CICSR);
}





local bool _hoops_CGCGI(float *matrix) {
	float _hoops_SGCGI[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
	int i;

	if (matrix == null)
		return true;

	for (i = 0; i < 16; i++)
		if (_hoops_SGCGI[i] != matrix[i])
			return false;
	return true;
}

GLOBAL_FUNCTION bool HI_Show_Texture (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_RCR *				texture,
	char *					definition,
	int						_hoops_ISCIH,
	char *					shader_source,
	int						_hoops_CSCIH,
	bool					_hoops_SSCIH,
	char const *			opt) {
#ifndef DISABLE_TEXTURING
	char					buf[2000];
	bool					_hoops_GAGRGR = false;
	char *					ps = buf;
	char *					pe = buf+_hoops_GGAPR(buf) -1;
	_hoops_ARRRP			flags=~0;

	UNREFERENCED (shader_source);
	UNREFERENCED (_hoops_CSCIH);

	if (opt) {
		Option_Value *		option;
		_hoops_HIACR (_hoops_CPRGI, _hoops_SISGGR);
		if (!HI_Parse_Options (_hoops_RIGC, opt, _hoops_CIACR (_hoops_CPRGI),
							   &option, _hoops_CGPCR|_hoops_PAPCA))
							   return false;
		if (option == null)
			return false;
		flags = option->type->id;
		HI_Free_Option_List (_hoops_RIGC, option);
	}
	else {
		if (shader_source != null &&
			texture->_hoops_RSR->shader_source.length != 0) {
			const char *end;
			char *ptr;
			if (_hoops_CSCIH <= 0)
				end = shader_source + HOOPS_WORLD->_hoops_RAPPR;
			else
				end = shader_source + _hoops_CSCIH;
			ptr = HI_Sprintf1 (shader_source, end, "%s", (void *)texture->_hoops_RSR->shader_source.text);
			*ptr = '\0';
		}
	}
	if (BIT (texture->_hoops_SCR, _hoops_GSR)) {
		//_hoops_SR'_hoops_ASAR _hoops_PCCSI _hoops_IRS _hoops_CI, _hoops_HAR _hoops_IRS _hoops_HH.  _hoops_PCHC _hoops_AIRC _hoops_CHR _hoops_HAR _hoops_ARGPR
		flags &= ~(_hoops_GARRP|_hoops_APRRP|_hoops_SRRRP|_hoops_RARRP|
			_hoops_GPRRP|_hoops_HPRRP|_hoops_IPRRP|_hoops_CPRRP|_hoops_PHRRP|
			_hoops_PARRP|_hoops_HARRP|_hoops_IARRP|_hoops_CARRP);


		if (BIT(flags, _hoops_ASR)) {
			//_hoops_PGRAC _hoops_ASSP'_hoops_RA _hoops_HS _hoops_GII _hoops_CICC _hoops_SGI, _hoops_HIS _hoops_SCH _hoops_HRGR _hoops_SHR _hoops_GHSAR _hoops_IS _hoops_SHH "_hoops_ARP"
			//_hoops_HAS._hoops_IAS. _hoops_SHR _hoops_PGI "_hoops_GPP" _hoops_PAR "_hoops_PSAP", _hoops_IIP, "_hoops_GA'_hoops_RA _hoops_PICP"
			_hoops_GAGRGR = true;
			if (BIT(texture->flags, _hoops_ASR)) {
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "multitexture,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "on,", null);
			}
			else {
				if (opt)
					ps = HI_Sprintf1 (ps, pe, "off,", null);
			}
		}
	}

	if (BIT(flags, _hoops_GARRP)) {
		if (texture->image != null) {
			/* _hoops_CHHA _hoops_HCGP */
			if (_hoops_SSCIH && texture->image->name.length != 0) {
				_hoops_GAGRGR = true;
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "source=", null);
				ps = HI_Sprintf1 (ps, pe, "%qn,", (void *)&texture->image->name);
				if (ps == null)
					return false;
			}
		}
		else if (texture->_hoops_PAPIR->name.length > 0) {
			/* _hoops_HHHA _hoops_HCGP */
			_hoops_GAGRGR = true;

			if (ANYBIT(texture->flags, _hoops_AIA|_hoops_CSGH)) {
				_hoops_AAPIR *name = texture->_hoops_PAPIR;

				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "source=(", null);

				while (name) {
					if (name->next != null)
						ps = HI_Sprintf1 (ps, pe, "%qn,", (void *)&name->name);
					else
						ps = HI_Sprintf1 (ps, pe, "%qn", (void *)&name->name);
					name = name->next;
				}

				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "),", null);
			}
			else {
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "source=", null);
				ps = HI_Sprintf1 (ps, pe, "%qn,", (void *)&texture->_hoops_PAPIR->name);
			}
			if (ps == null)
				return false;
		}
	}

	if (BIT(flags, _hoops_AHRRP)) {
		if (opt) {
			ps = HI_Sprintf1 (ps, pe, "%d,", &texture->_hoops_ICR[0]);
			ps = HI_Sprintf1 (ps, pe, "%d,", &texture->_hoops_ICR[1]);
			ps = HI_Sprintf1 (ps, pe, "%d,", &texture->_hoops_ICR[2]);
		}
		else if (texture->_hoops_ICR[0] != 1 ||
			texture->_hoops_ICR[1] != 1 ||
			texture->_hoops_ICR[2] != 1) {	
			ps = HI_Sprintf1 (ps, pe, "source dimensions=(%d,", &texture->_hoops_ICR[0]);
			ps = HI_Sprintf1 (ps, pe, "%d,", &texture->_hoops_ICR[1]);
			ps = HI_Sprintf1 (ps, pe, "%d),", &texture->_hoops_ICR[2]);
		}
	}

	if (BIT(flags, _hoops_IRRRP)) {
		if (BIT(texture->flags, _hoops_IRRRP)) {
			_hoops_GAGRGR = true;
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, "parameter offset=", null);
			ps = HI_Sprintf1 (ps, pe, "%d,", &texture->_hoops_RSCP);
		}
	}

	if (BIT(flags, _hoops_HRRRP)) {
		if (BIT(texture->flags, _hoops_HRRRP)) {
			_hoops_GAGRGR = true;
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, "parameterization source=", null);
			switch (texture->_hoops_PSR) {
				case HK_PS_UNSPECIFIED: {
					ps = HI_Sprintf1 (ps, pe, "unknown,", null);
				}	break;
				case HK_PS_U: {
					ps = HI_Sprintf1 (ps, pe, "u,", null);
				}	break;
				case HK_PS_UV: {
					ps = HI_Sprintf1 (ps, pe, "uv,", null);
				}	break;
				case HK_PS_UVW: {
					ps = HI_Sprintf1 (ps, pe, "uvw,", null);
				}	break;
				case HK_PS_OBJECT: {
					ps = HI_Sprintf1 (ps, pe, "object,", null);
				}	break;
				case HK_PS_WORLD: {
					ps = HI_Sprintf1 (ps, pe, "world,", null);
				}	break;
				case HK_PS_SURFACE_NORMAL: {
					ps = HI_Sprintf1 (ps, pe, "surface normal,", null);
				}	break;
				case HK_PS_REFLECTION_VECTOR: {
					ps = HI_Sprintf1 (ps, pe, "reflection vector,", null);
				}	break;
				case _hoops_HSR: {
					ps = HI_Sprintf1 (ps, pe, "physical reflection,", null);
				}	break;
				case HK_PS_NATURAL_UV: {
					ps = HI_Sprintf1 (ps, pe, "natural uv,", null);
				}	break;
				case HK_PS_LOCAL_PIXELS: {
					ps = HI_Sprintf1 (ps, pe, "local pixels,", null);
				}	break;
				case HK_PS_OUTER_PIXELS: {
					ps = HI_Sprintf1 (ps, pe, "outer pixels,", null);
				}	break;
				case HK_PS_LOCAL_WINDOW: {
					ps = HI_Sprintf1 (ps, pe, "local window,", null);
				}	break;
				case HK_PS_OUTER_WINDOW: {
					ps = HI_Sprintf1 (ps, pe, "outer window,", null);
				}	break;
				case HK_PS_SPHERE: {
					ps = HI_Sprintf1 (ps, pe, "sphere map,", null);
				}	break;
				case HK_PS_CYLINDER: {
					ps = HI_Sprintf1 (ps, pe, "cylinder map,", null);
				}	break;
				default: {
					_hoops_SPCI(HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Bogus surface parameterization source.");
				}
			}
		}
	}

	if (BIT(flags, _hoops_APRRP)) {
		if (BIT(texture->flags, _hoops_APRRP)) {
			_hoops_GAGRGR = true;
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, "layout=", null);
			switch (texture->_hoops_GAARP) {
				case _hoops_HCGRP: {
					ps = HI_Sprintf1 (ps, pe, "unknown,", null);
				}	break;
				case _hoops_ICGRP: {
					ps = HI_Sprintf1 (ps, pe, "rectilinear,", null);
				}	break;
				case _hoops_CCGRP: {
					ps = HI_Sprintf1 (ps, pe, "spherical,", null);
				}	break;
				case _hoops_SCGRP: {
					ps = HI_Sprintf1 (ps, pe, "hemispherical,", null);
				}	break;
				case _hoops_GSGRP: {
					ps = HI_Sprintf1 (ps, pe, "cubic faces,", null);
				}	break;
				default: {
					_hoops_SPCI(HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Bogus surface parameterization function.");
				}
			}
		}
	}

	if (BIT(flags, _hoops_CRRRP)) {
		if (BIT(texture->flags, _hoops_GHRRP) && texture->_hoops_GAGH) {
			float *		_hoops_RICIR = (float *)texture->_hoops_GAGH->matrix.elements;

			if (!_hoops_CGCGI(_hoops_RICIR)) {
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "transform=(", null);

				for (int i=0; i<4; ++i) {
					ps = HI_Sprintf1 (ps, pe, "(", null);
					ps = HI_Sprintf1 (ps, pe, "%f ", (void *)&_hoops_RICIR[0]);
					ps = HI_Sprintf1 (ps, pe, "%f ", (void *)&_hoops_RICIR[1]);
					ps = HI_Sprintf1 (ps, pe, "%f ", (void *)&_hoops_RICIR[2]);
					ps = HI_Sprintf1 (ps, pe, "%f", (void *)&_hoops_RICIR[3]);
					ps = HI_Sprintf1 (ps, pe, ")", null);

					_hoops_RICIR += 4;
				}

				if (!opt)
					ps = HI_Sprintf1 (ps, pe, ")", null);

				ps = HI_Sprintf1 (ps, pe, ",", null);
			}
		}
		else if (texture->_hoops_IRARP) {
			_hoops_CRCP const *		_hoops_IASSI = texture->_hoops_IRARP;
			_hoops_CRCP const *		_hoops_CACIA = (_hoops_CRCP const *)texture->owner;

			_hoops_GAGRGR = true;
			if (_hoops_IASSI->name.length != 0 && _hoops_CACIA != HOOPS_WORLD->root) {
				_hoops_CRCP const *		_hoops_RAGRGR = _hoops_CACIA;
				_hoops_CRCP const *		_hoops_AAGRGR = null;
				char				_hoops_PAGRGR[MAX_ERRMSG];
				char *				segname = _hoops_PAGRGR;
				int					_hoops_ICRH = 0;

				if (*HI_Look_Up_Alias (_hoops_RIGC, "include library", 15) != null)
					_hoops_AAGRGR = HI_One_Segment_Search (_hoops_RIGC, "?Include Library", false);
				else
					_hoops_AAGRGR = HI_One_Segment_Search (_hoops_RIGC, "/Include Library", false);

				while (_hoops_RAGRGR != null) {
					if (_hoops_RAGRGR == HOOPS_WORLD->root) {
						_hoops_RAGRGR = null;
						break;
					}
					else if (_hoops_RAGRGR == _hoops_AAGRGR)
						break;
					else {
						Attribute const *	_hoops_HPHCR;

						if ((_hoops_HPHCR = _hoops_RAGRGR->_hoops_IPPGR) != null) do {
							if (_hoops_HPHCR->type == HK_DRIVER)
								goto _hoops_HAGRGR;
							else if (_hoops_HPHCR->type > HK_DRIVER)
								break;
						} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

						_hoops_RAGRGR = _hoops_RAGRGR->owner;
					}
				}
			  _hoops_HAGRGR:

				Sprintf_P (segname, "%p",  _hoops_IASSI);

				if (_hoops_RAGRGR != null) {
					char					_hoops_IAGRGR[MAX_ERRMSG];
					char					root[MAX_ERRMSG];
					char *					current = _hoops_IAGRGR;
					int						length = 0;

					Sprintf_P (current, "%p/", _hoops_CACIA);
					Sprintf_P (root,    "%p/", _hoops_RAGRGR);

					length = _hoops_SSGR (root);
					if (_hoops_GPPSA (current, length, root) &&
						_hoops_GPPSA (segname, length, root)) {
						char *					_hoops_RPPA;

						segname += length;
						current += length;

						while ((_hoops_RPPA = _hoops_HCGGI('/',current)) != null) {
							length = _hoops_RPPA - current + 1;		/* _hoops_GCIS _hoops_RH '/' */
							if (_hoops_GPPSA (segname, length, current)) {
								segname += length;
								current += length;
							}
							else
								break;
						}

						if (*current) {
							_hoops_RPPA = current;
							while ((_hoops_RPPA = _hoops_HCGGI('/',_hoops_RPPA)) != null) {
								++_hoops_ICRH;
								++_hoops_RPPA;		/* _hoops_SAS _hoops_RAS _hoops_RGR _hoops_SPR */
							}
						}
					}
				}

				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "transform='", null);
				while (_hoops_ICRH-- > 0) {
					ps = HI_Sprintf1 (ps, pe, "../", null);
				}
				ps = HI_Sprintf1 (ps, pe, "%s", segname);
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "'", null);
				ps = HI_Sprintf1 (ps, pe, ",", null);
			}
			else {
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "transform='", null);
				ps = HI_Sprintf1 (ps, pe, "%p", _hoops_IASSI);
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "'", null);
				ps = HI_Sprintf1 (ps, pe, ",", null);
			}
		}
	}

	if (BIT(flags, _hoops_RHRRP)) {
		if (texture->_hoops_SRARP) {
			_hoops_CRCP const *		_hoops_IASSI = texture->_hoops_SRARP;
			_hoops_CRCP const *		_hoops_CACIA = (_hoops_CRCP const *)texture->owner;

			_hoops_GAGRGR = true;
			if (_hoops_IASSI->name.length != 0 && _hoops_CACIA != HOOPS_WORLD->root) {
				_hoops_CRCP const *		_hoops_RAGRGR = _hoops_CACIA;
				_hoops_CRCP const *		_hoops_AAGRGR = null;
				char				_hoops_PAGRGR[MAX_ERRMSG];
				char *				segname = _hoops_PAGRGR;
				int					_hoops_ICRH = 0;

				if (*HI_Look_Up_Alias (_hoops_RIGC, "include library", 15) != null)
					_hoops_AAGRGR = HI_One_Segment_Search (_hoops_RIGC, "?Include Library", false);
				else
					_hoops_AAGRGR = HI_One_Segment_Search (_hoops_RIGC, "/Include Library", false);

				while (_hoops_RAGRGR != null) {
					if (_hoops_RAGRGR == HOOPS_WORLD->root) {
						_hoops_RAGRGR = null;
						break;
					}
					else if (_hoops_RAGRGR == _hoops_AAGRGR)
						break;
					else {
						Attribute const *	_hoops_HPHCR;

						if ((_hoops_HPHCR = _hoops_RAGRGR->_hoops_IPPGR) != null) do {
							if (_hoops_HPHCR->type == HK_DRIVER)
								goto _hoops_CAGRGR;
							else if (_hoops_HPHCR->type > HK_DRIVER)
								break;
						} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

						_hoops_RAGRGR = _hoops_RAGRGR->owner;
					}
				}
			  _hoops_CAGRGR:

				Sprintf_P (segname, "%p",  _hoops_IASSI);

				if (_hoops_RAGRGR != null) {
					char					_hoops_IAGRGR[MAX_ERRMSG];
					char					root[MAX_ERRMSG];
					char *					current = _hoops_IAGRGR;
					int						length = 0;

					Sprintf_P (current, "%p/", _hoops_CACIA);
					Sprintf_P (root,    "%p/", _hoops_RAGRGR);

					length = _hoops_SSGR (root);
					if (_hoops_GPPSA (current, length, root) &&
						_hoops_GPPSA (segname, length, root)) {
						char *					_hoops_RPPA;

						segname += length;
						current += length;

						while ((_hoops_RPPA = _hoops_HCGGI('/',current)) != null) {
							length = _hoops_RPPA - current + 1;		/* _hoops_GCIS _hoops_RH '/' */
							if (_hoops_GPPSA (segname, length, current)) {
								segname += length;
								current += length;
							}
							else
								break;
						}

						if (*current) {
							_hoops_RPPA = current;
							while ((_hoops_RPPA = _hoops_HCGGI('/',_hoops_RPPA)) != null) {
								++_hoops_ICRH;
								++_hoops_RPPA;		/* _hoops_SAS _hoops_RAS _hoops_RGR _hoops_SPR */
							}
						}
					}
				}

				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "camera='", null);
				while (_hoops_ICRH-- > 0) {
					ps = HI_Sprintf1 (ps, pe, "../", null);
				}
				ps = HI_Sprintf1 (ps, pe, "%s", segname);
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "'", null);
				ps = HI_Sprintf1 (ps, pe, ",", null);
			}
			else {
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "camera='", null);
				ps = HI_Sprintf1 (ps, pe, "%p", _hoops_IASSI);
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "'", null);
				ps = HI_Sprintf1 (ps, pe, ",", null);
			}
		}
	}

	if (BIT(flags, _hoops_SRRRP)) {
		if (BIT(texture->flags, _hoops_SRRRP)) {
			_hoops_GAGRGR = true;
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, "tiling=", null);
			switch (texture->_hoops_CGA) {
				case _hoops_ASCC: {
					ps = HI_Sprintf1 (ps, pe, "clamp,", null);
				}	break;
				case _hoops_ASGRP: {
					ps = HI_Sprintf1 (ps, pe, "repeat,", null);
				}	break;
				case _hoops_PSGRP: {
					ps = HI_Sprintf1 (ps, pe, "mirror,", null);
				}	break;
				case _hoops_SGA: {
					ps = HI_Sprintf1 (ps, pe, "drop,", null);
				}	break;
				default: {
					_hoops_SPCI(HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Bogus tiling style.");
				}
			}
		}
	}

	if (BIT(flags, _hoops_RARRP)) {
		if (BIT(texture->flags, _hoops_RARRP)) {
			_hoops_GAGRGR = true;
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, "interpolation filter=", null);
			switch (texture->_hoops_PSCC) {
				case _hoops_HSCC: {
					ps = HI_Sprintf1 (ps, pe, "off,", null);
				}	break;
				case _hoops_HSGRP: {
					ps = HI_Sprintf1 (ps, pe, "bilinear,", null);
				}	break;
				case _hoops_ISGRP: {
					ps = HI_Sprintf1 (ps, pe, "trilinear,", null);
				}	break;
				case _hoops_SSGRP: {
					ps = HI_Sprintf1 (ps, pe, "gaussian,", null);
				}	break;
				case _hoops_GGRRP: {
					ps = HI_Sprintf1 (ps, pe, "stochastic,", null);
				}	break;
				case _hoops_AARH:
				case _hoops_CSGRP:
				default: {
					_hoops_SPCI(HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Bogus interpolation filter.");
				}
			}
		}
	}

	if (BIT(flags, _hoops_AARRP)) {
		if (BIT(texture->flags, _hoops_AARRP)) {
			_hoops_GAGRGR = true;
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, "decimation filter=", null);
			switch (texture->_hoops_RARH) {
				case _hoops_HSCC: {
					ps = HI_Sprintf1 (ps, pe, "off,", null);
				}	break;
				case _hoops_AARH: {
					ps = HI_Sprintf1 (ps, pe, "mipmap,", null);
				}	break;
				case _hoops_PARH: {
					ps = HI_Sprintf1 (ps, pe, "anisotropic,", null);
				}	break;
				case _hoops_CSGRP: {
					_hoops_SPCI(HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Bogus interpolation filter.");
				}	break;
				case _hoops_HSGRP:
				case _hoops_ISGRP:
				case _hoops_SSGRP:
				case _hoops_GGRRP:
				default: {
					_hoops_SPCI(HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Bogus decimation filter.");
				}
			}
		}
	}

	if (BIT(flags, _hoops_PARRP)) {
		if (BIT(texture->flags, _hoops_PARRP)) {
			_hoops_GAGRGR = true;
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, "red channel mapping=", null);
			switch (texture->_hoops_HPIR._hoops_RSRRP) {
				case _hoops_PGRRP: {
					ps = HI_Sprintf1 (ps, pe, "red,", null);
				}	break;
				case _hoops_HGRRP: {
					ps = HI_Sprintf1 (ps, pe, "green,", null);
				}	break;
				case _hoops_IGRRP: {
					ps = HI_Sprintf1 (ps, pe, "blue,", null);
				}	break;
				case _hoops_CGRRP: {
					ps = HI_Sprintf1 (ps, pe, "alpha,", null);
				}	break;
				case _hoops_SGRRP: {
					ps = HI_Sprintf1 (ps, pe, "zero,", null);
				}	break;
				case _hoops_GRRRP: {
					ps = HI_Sprintf1 (ps, pe, "one,", null);
				}	break;
				case _hoops_RRRRP: {
					ps = HI_Sprintf1 (ps, pe, "luminance,", null);
				}	break;
				case _hoops_AGRRP: {
					ps = HI_Sprintf1 (ps, pe, "off,", null);
				}	break;
				default: {
					_hoops_SPCI(HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Bogus red channel mapping.");
				}
			}
		}
	}

	if (BIT(flags, _hoops_HARRP)) {
		if (BIT(texture->flags, _hoops_HARRP)) {
			_hoops_GAGRGR = true;
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, "green channel mapping=", null);
			switch (texture->_hoops_HPIR._hoops_ASRRP) {
				case _hoops_PGRRP: {
					ps = HI_Sprintf1 (ps, pe, "red,", null);
				}	break;
				case _hoops_HGRRP: {
					ps = HI_Sprintf1 (ps, pe, "green,", null);
				}	break;
				case _hoops_IGRRP: {
					ps = HI_Sprintf1 (ps, pe, "blue,", null);
				}	break;
				case _hoops_CGRRP: {
					ps = HI_Sprintf1 (ps, pe, "alpha,", null);
				}	break;
				case _hoops_SGRRP: {
					ps = HI_Sprintf1 (ps, pe, "zero,", null);
				}	break;
				case _hoops_GRRRP: {
					ps = HI_Sprintf1 (ps, pe, "one,", null);
				}	break;
				case _hoops_RRRRP: {
					ps = HI_Sprintf1 (ps, pe, "luminance,", null);
				}	break;
				case _hoops_AGRRP: {
					ps = HI_Sprintf1 (ps, pe, "off,", null);
				}	break;
				default: {
					_hoops_SPCI(HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Bogus green channel mapping.");
				}
			}
		}
	}

	if (BIT(flags, _hoops_IARRP)) {
		if (BIT(texture->flags, _hoops_IARRP)) {
			_hoops_GAGRGR = true;
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, "blue channel mapping=", null);
			switch (texture->_hoops_HPIR._hoops_PSRRP) {
				case _hoops_PGRRP: {
					ps = HI_Sprintf1 (ps, pe, "red,", null);
				}	break;
				case _hoops_HGRRP: {
					ps = HI_Sprintf1 (ps, pe, "green,", null);
				}	break;
				case _hoops_IGRRP: {
					ps = HI_Sprintf1 (ps, pe, "blue,", null);
				}	break;
				case _hoops_CGRRP: {
					ps = HI_Sprintf1 (ps, pe, "alpha,", null);
				}	break;
				case _hoops_SGRRP: {
					ps = HI_Sprintf1 (ps, pe, "zero,", null);
				}	break;
				case _hoops_GRRRP: {
					ps = HI_Sprintf1 (ps, pe, "one,", null);
				}	break;
				case _hoops_RRRRP: {
					ps = HI_Sprintf1 (ps, pe, "luminance,", null);
				}	break;
				case _hoops_AGRRP: {
					ps = HI_Sprintf1 (ps, pe, "off,", null);
				}	break;
				default: {
					_hoops_SPCI(HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Bogus blue channel mapping.");
				}
			}
		}
	}

	if (BIT(flags, _hoops_CARRP)) {
		if (BIT(texture->flags, _hoops_CARRP)) {
			_hoops_GAGRGR = true;
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, "alpha channel mapping=", null);
			switch (texture->_hoops_HPIR._hoops_HSRRP) {
				case _hoops_PGRRP: {
					ps = HI_Sprintf1 (ps, pe, "red,", null);
				}	break;
				case _hoops_HGRRP: {
					ps = HI_Sprintf1 (ps, pe, "green,", null);
				}	break;
				case _hoops_IGRRP: {
					ps = HI_Sprintf1 (ps, pe, "blue,", null);
				}	break;
				case _hoops_CGRRP: {
					ps = HI_Sprintf1 (ps, pe, "alpha,", null);
				}	break;
				case _hoops_SGRRP: {
					ps = HI_Sprintf1 (ps, pe, "zero,", null);
				}	break;
				case _hoops_GRRRP: {
					ps = HI_Sprintf1 (ps, pe, "one,", null);
				}	break;
				case _hoops_RRRRP: {
					ps = HI_Sprintf1 (ps, pe, "luminance,", null);
				}	break;
				case _hoops_AGRRP: {
					ps = HI_Sprintf1 (ps, pe, "off,", null);
				}	break;
				default: {
					_hoops_SPCI(HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Bogus blue channel mapping.");
				}
			}
		}
	}

	if (BIT(flags, _hoops_SARRP)) {
		if (BIT(texture->flags, _hoops_SARRP)) {
			_hoops_GAGRGR = true;
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, "value scale=(", null);
			ps = HI_Sprintf1 (ps, pe, "%f,", &texture->_hoops_HPIR._hoops_IIRH);
			ps = HI_Sprintf1 (ps, pe, "%f", &texture->_hoops_HPIR._hoops_CIRH);
			if (!opt)
				ps = HI_Sprintf1 (ps, pe, ")", null);
			ps = HI_Sprintf1 (ps, pe, ",", null);
		}
	}

	if (BIT(flags, _hoops_GPRRP)) {
		if (BIT(texture->flags, _hoops_GPRRP)) {
			_hoops_GAGRGR = true;
			if (BIT(texture->_hoops_SCR, _hoops_IHRRP))
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "no caching,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "off,", null);
			else
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "caching,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "on,", null);
		}
	}

	if (BIT(flags, _hoops_HPRRP)) {
		if (BIT(texture->flags, _hoops_HPRRP)) {
			_hoops_GAGRGR = true;
			if (BIT(texture->_hoops_SCR, _hoops_RCRH))
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "no down sample,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "off,", null);
			else
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "down sample,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "on,", null);
		}
	}

	if (BIT(flags, _hoops_PPRRP)) {
		if (BIT(texture->flags, _hoops_PPRRP)) {
			_hoops_GAGRGR = true;
			if (!BIT(texture->_hoops_SCR, _hoops_IGA))
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "no modulate,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "off,", null);
			else
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "modulate,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "on,", null);
		}
	}

	if (BIT(flags, _hoops_IPRRP)) {
		if (BIT(texture->flags, _hoops_IPRRP)) {
			_hoops_GAGRGR = true;
			if (!BIT(texture->_hoops_SCR, _hoops_PGA))
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "no decal,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "off,", null);
			else
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "decal,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "on,", null);
		}
	}

	if (BIT(flags, _hoops_CPRRP)) {
		if (BIT(texture->flags, _hoops_CPRRP)) {
			_hoops_GAGRGR = true;
			if (!BIT(texture->_hoops_SCR, _hoops_CHRRP))
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "no source callback,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "off,", null);
			else
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "source callback=%n,", (void*)&texture->_hoops_HGIIR->name);
				else
					ps = HI_Sprintf1 (ps, pe, "%n,", (void*)&texture->_hoops_HGIIR->name);
		}
	}

	if (BIT(flags, _hoops_IPGH)) {
		if (BIT(texture->flags, _hoops_IPGH)) {
			_hoops_GAGRGR = true;
			if (BIT(texture->_hoops_SCR, _hoops_IPGH))
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "no transform override,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "off,", null);
			else
				if (!opt)
					ps = HI_Sprintf1 (ps, pe, "transform override,", null);
				else
					ps = HI_Sprintf1 (ps, pe, "on,", null);
		}
	}

	if (ps != null) {
		if (ps != buf) {
			/* _hoops_SIPR _hoops_IASH _hoops_IIGR _hoops_GRCIR _hoops_RRCIR */
			ps--;
		}
		if (_hoops_ISCIH != 0)
			HI_Return_Chars (definition, _hoops_ISCIH, buf, (int)(ps - buf));
	}
	return _hoops_GAGRGR;
#else
	return false;
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Texture (
	char const *	name,
	char *			definition)
{
	_hoops_PAPPR context("Show_Texture");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Texture () */\n");
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars_Quoted (name, &_hoops_CRPCR, false);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_TEXTURE, HES_NULL_INPUT, "Texture name is blank or null");
		return;
	}

	_hoops_CSPPR();

	_hoops_RCR * texture = HI_Look_Up_Texture (context, _hoops_RSPPR(context, _hoops_RPGHP), &_hoops_CRPCR);

	if (!texture) {
		HE_ERROR (HEC_TEXTURE, HES_DEFINITION_NOT_FOUND,
			Sprintf_N (null, "Texture '%n' not found", &_hoops_CRPCR));
	}
	else
		HI_Show_Texture (context, texture, definition, -1, null, 0, true, 0);

	_hoops_IRRPR();

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Local_Texture (
	char const *	name,
	char *			definition)
{
	_hoops_PAPPR context("Show_Local_Texture");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Local_Texture () */\n");
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars_Quoted (name, &_hoops_CRPCR, false);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_TEXTURE, HES_NULL_INPUT, "Texture name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SSRPP)) != null) {

		_hoops_RCR * texture = HI_Look_Up_Texture (context, (_hoops_CRCP *)target, &_hoops_CRPCR);

		if (!texture) {
			HE_ERROR (HEC_TEXTURE, HES_DEFINITION_NOT_FOUND, 
				Sprintf_N (null, "Texture '%n' not found", &_hoops_CRPCR));
		}
		else {
			HI_Show_Texture (context, texture, definition, -1, null, 0, true, 0);
		}

		_hoops_IRRPR();
	}

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Shader (
	char const *	name,
	char *			definition,
	char *			shader_source)
{
	_hoops_PAPPR context("Show_Shader");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Shader () */\n");
	);

	int _hoops_ISCIH = -1;
	int _hoops_SAGRGR = -1;
	if (definition == null)
		_hoops_ISCIH = 0;
	if (shader_source == null)
		_hoops_SAGRGR = 0;

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars_Quoted (name, &_hoops_CRPCR, false);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_TEXTURE, HES_NULL_INPUT, "Texture name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SSRPP)) != null) {

		_hoops_RCR * texture = HI_Look_Up_Texture (context, (_hoops_CRCP *)target, &_hoops_CRPCR);

		if (!texture) {
			HE_ERROR (HEC_TEXTURE, HES_DEFINITION_NOT_FOUND, 
				Sprintf_N (null, "Shader '%n' not found", &_hoops_CRPCR));
		}
		else {
			HI_Show_Texture (context, texture, definition, _hoops_ISCIH, shader_source, _hoops_SAGRGR, true, 0);
		}
		_hoops_IRRPR();
	}

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}

local void _hoops_GPGRGR(
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	char *					output,
	int						_hoops_ICHPP,
	char *					shader_source,
	int						_hoops_RPGRGR,
	Key *					out_image,
	_hoops_CPAIR *			_hoops_CICSR,
	char const *			opt) {

	_hoops_RCR *				txr;
	_hoops_RCR *				_hoops_APGRGR;

	_hoops_APGRGR = HI_Clone_Texture (0);
	ZALLOC(_hoops_APGRGR->_hoops_PAPIR, _hoops_AAPIR);
	HI_Canonize_Chars_Quoted (name, &_hoops_APGRGR->_hoops_PAPIR->name, false);
	_hoops_HCARA(_hoops_APGRGR->_hoops_PAPIR->name,_hoops_APGRGR->_hoops_PAPIR->key);
	_hoops_APGRGR->flags |= TF_UNEVALUATED;

	txr = HI_Activate_Texture(_hoops_APGRGR, _hoops_CICSR, false);

	if (!txr) {
		if (out_image)
			*out_image=_hoops_SHSSR;

		HE_WARNING (HEC_TEXTURE, HES_MISSING,"Unable to evaluate texture in this context.");
	}
	else {
		if (out_image)
			*out_image=txr->image->key;

		if (output) {
			if (!HI_Show_Texture (_hoops_RIGC, txr, output, _hoops_ICHPP, shader_source, _hoops_RPGRGR, true, opt)) {
				/* _hoops_PPGRGR? */
			}
		}
		_hoops_HPRH (txr);
	}

	_hoops_HPRH (_hoops_APGRGR);
}


HC_INTERFACE void HC_CDECL HC_PShow_Net_Texture (
	int				count,
	Key const *		keys,
	char const *	name,
	char *			output,
	Key *			out_image)
{
	_hoops_PAPPR context("PShow_Net_Texture");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* PShow_Net_Texture () */\n");
	);

	_hoops_CPAIR *	_hoops_CICSR;
	if ((_hoops_CICSR = (_hoops_CPAIR *) HI_Find_Attribute_And_Lock(context, _hoops_SSRPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_GPGRGR(context, name, output, -1, null, 0, out_image, _hoops_CICSR, 0);
		_hoops_HPRH (_hoops_CICSR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(output,-1, "", 0);

#endif
}


HC_INTERFACE void HC_CDECL HC_PShow_Net_Shader (
	int				count,
	Key const *		keys,
	char const *	name,
	char *			output,
	char *			shader_source)
{
	_hoops_PAPPR context("PShow_Net_Shader");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* PShow_Net_Shader() */\n");
	);

	_hoops_CPAIR *	_hoops_CICSR;
	if ((_hoops_CICSR = (_hoops_CPAIR *) HI_Find_Attribute_And_Lock(context, _hoops_SSRPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_GPGRGR(context, name, output, -1, shader_source, -1, null, _hoops_CICSR, 0);
		_hoops_HPRH (_hoops_CICSR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(output,-1, "", 0);

#endif
}


HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Texture (
	int				count,
	Key const *		keys,
	char const *	name,
	char const *	opt,
	char *			output)
{
	_hoops_PAPPR context("PShow_One_Net_Texture");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* PShow_One_Net_Texture () */\n");
	);

	_hoops_CPAIR *	_hoops_CICSR;
	if ((_hoops_CICSR = (_hoops_CPAIR *) HI_Find_Attribute_And_Lock(context, _hoops_SSRPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_GPGRGR(context, name, output, -1, null, 0, null, _hoops_CICSR, opt);
		_hoops_HPRH (_hoops_CICSR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(output,-1, "", 0);

#endif
}

HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Shader_Option (
	int					count,
	Key const *			keys,
	char const *		name,
	char const *		opt,
	char *				output)
{
	_hoops_PAPPR context("PShow_One_Net_Shader_Option");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* PShow_One_Net_Shader_Option() */\n");
	);

	_hoops_CPAIR *	_hoops_CICSR;
	if ((_hoops_CICSR = (_hoops_CPAIR *) HI_Find_Attribute_And_Lock(context, _hoops_SSRPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_GPGRGR(context, name, output, -1, null, 0, null, _hoops_CICSR, opt);
		_hoops_HPRH (_hoops_CICSR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(output,-1, "", 0);

#endif
}


GLOBAL_FUNCTION void HI_Flush_Textures(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CPAIR *			_hoops_SAHCA,
	bool					_hoops_AHCIH)
{
	bool	_hoops_PAHCA = _hoops_AHCIH;
	bool	_hoops_AACRS = false;
	bool	_hoops_AAHCA = false;

	for (int i = 0; i < _hoops_SAHCA->count; i++) {
		_hoops_AAHCA = BIT (_hoops_SAHCA->textures[i]->_hoops_SCR, _hoops_GSR);
		if (_hoops_AAHCA != _hoops_PAHCA) {
			_hoops_AACRS = true;
			break;
		}
	}

	if (_hoops_AACRS) {
		for (int i = 0; i < _hoops_SAHCA->count; i++) {
			_hoops_AAHCA = BIT (_hoops_SAHCA->textures[i]->_hoops_SCR, _hoops_GSR);
			if (_hoops_AAHCA == _hoops_PAHCA) {
				_hoops_ARGRGR (_hoops_RIGC, _hoops_SAHCA->owner, _hoops_SAHCA->textures[i]->name);
			}
		}
	}
	else
		HI_Generic_Delete (_hoops_RIGC, (_hoops_HPAH *)_hoops_SAHCA);
}


HC_INTERFACE void HC_CDECL HC_UnDefine_Texture (
	char const *	iname)
{
	_hoops_PAPPR context("UnDefine_Texture");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnDefine_Texture (%S);\n", iname));
	);

	_hoops_HCRPR					_hoops_CRPCR;
	HI_Canonize_Chars_Quoted (iname, &_hoops_CRPCR, false);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_TEXTURE, HES_NULL_INPUT, "Texture name is blank or null");
		return;
	}

	_hoops_RPPPR();
	_hoops_ARGRGR (context, _hoops_RSPPR(context, _hoops_RPGHP), _hoops_CRPCR);
	_hoops_IRRPR();

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}


HC_INTERFACE void HC_CDECL HC_UnDefine_Local_Texture (
	char const *	iname)
{
	_hoops_PAPPR context("UnDefine_Local_Texture");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnDefine_Local_Texture (%S);\n", iname));
	);

	_hoops_HCRPR					_hoops_CRPCR;
	HI_Canonize_Chars_Quoted (iname, &_hoops_CRPCR, false);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_TEXTURE, HES_NULL_INPUT, "Texture name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RHRPP|_hoops_GSIIR)) != null) {
		_hoops_ARGRGR (context, (_hoops_CRCP const *)target, _hoops_CRPCR);
		_hoops_IRRPR();
	}

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}


HC_INTERFACE void HC_CDECL HC_UnDefine_Shader (
	char const *		iname)
{
	_hoops_PAPPR context("UnDefine_Shader");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnDefine_Shader (%S);\n", iname));
	);

	_hoops_HCRPR					_hoops_CRPCR;
	HI_Canonize_Chars_Quoted (iname, &_hoops_CRPCR, false);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_TEXTURE, HES_NULL_INPUT, "Shader name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RHRPP|_hoops_GSIIR)) != null) {
		_hoops_ARGRGR (context, (_hoops_CRCP const *)target, _hoops_CRPCR);
		_hoops_IRRPR();
	}

	_hoops_RGAIR (_hoops_CRPCR);
#endif
}



#ifndef DISABLE_SEARCH
#ifndef DISABLE_TEXTURING
local void _hoops_HPGRGR(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	bool					_hoops_IRGRGR) {
	_hoops_SSPPR *			_hoops_GGHPR;
	_hoops_AGHPR *			node;

	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	if (_hoops_IRGRGR) {
		_hoops_GGHPR->prev = _hoops_RIGC->_hoops_CHPGI;
		_hoops_RIGC->_hoops_CHPGI = _hoops_GGHPR;
	}
	else {
		_hoops_GGHPR->prev = _hoops_RIGC->_hoops_IHPGI;
		_hoops_RIGC->_hoops_IHPGI = _hoops_GGHPR;
	}

	_hoops_CPAIR * _hoops_CICSR = (_hoops_CPAIR*) HI_Find_Attribute (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, -_hoops_IPAIR);

	if (_hoops_CICSR) {
		for (int i=0; i<_hoops_CICSR->count; i++) {
			if (BIT (_hoops_CICSR->textures[i]->_hoops_SCR, _hoops_GSR) == _hoops_IRGRGR) {
				ALLOC (node, _hoops_AGHPR);
				node->next = _hoops_GGHPR->list;
				_hoops_GGHPR->list = node;
				node->item = (_hoops_HPAH *)_hoops_CICSR->textures[i];
				node->_hoops_AGRI = false;
				_hoops_PRRH(_hoops_CICSR->textures[i]);
				++_hoops_GGHPR->count;
			}
		}

		_hoops_HPRH(_hoops_CICSR);
	}
}
#endif
#endif

HC_INTERFACE void HC_CDECL HC_Begin_Texture_Search (void)
{
	_hoops_PAPPR context("Begin_Texture_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Texture_Search () */\n");
	++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_CSPPR();
	_hoops_HPGRGR(context, _hoops_RSPPR(context, _hoops_RPGHP), false);
	_hoops_IRRPR();
#endif
#endif
}

HC_INTERFACE void HC_CDECL HC_Begin_Local_Texture_Search (void)
{
	_hoops_PAPPR context("Begin_Local_Texture_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Local_Texture_Search () */\n");
	++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_CSPPR();

	_hoops_CRCP * _hoops_SRCP;

	if (context->open_list != null && context->open_list->_hoops_GCRIR == _hoops_RCRIR ||
		HI_Find_Our_Open (context)) {

		if (context->open_list->_hoops_GCRIR == _hoops_RCRIR)
			_hoops_SRCP = context->open_list->info.segment._hoops_IGRPR;
		else {
			HE_ERROR (HEC_TEXTURE, HES_NO_OPEN_SEGMENT, "Local Textures require open segment");
			goto _hoops_PRSPR;
		}
	}
	else {
		HE_ERROR (HEC_TEXTURE, HES_NO_OPEN_SEGMENT, "Local Textures require open segment, none can be found");
		goto _hoops_PRSPR;
	}

	_hoops_HPGRGR(context, _hoops_SRCP, false);

_hoops_PRSPR:
	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Begin_Shader_Search (void)
{
	_hoops_PAPPR context("Begin_Shader_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Shader_Search () */\n");
	++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_CSPPR();

	_hoops_CRCP * _hoops_SRCP;

	if (context->open_list != null && context->open_list->_hoops_GCRIR == _hoops_RCRIR ||
		HI_Find_Our_Open (context)) {

		if (context->open_list->_hoops_GCRIR == _hoops_RCRIR)
			_hoops_SRCP = context->open_list->info.segment._hoops_IGRPR;
		else {
			HE_ERROR (HEC_TEXTURE, HES_NO_OPEN_SEGMENT, "Shaders require open segment");
			goto _hoops_PRSPR;
		}
	}
	else {
		HE_ERROR (HEC_TEXTURE, HES_NO_OPEN_SEGMENT, "Shader require open segment, none can be found");
		goto _hoops_PRSPR;
	}

	_hoops_HPGRGR(context, _hoops_SRCP, true);

_hoops_PRSPR:
	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE bool HC_CDECL HC_Find_Texture (
	char alter *	_hoops_IAGIH)
{
	_hoops_PAPPR context("Find_Texture");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Texture () */\n");
	);

	_hoops_AGHPR	*list;

	if (context->_hoops_IHPGI == null) {
		HE_ERROR (HEC_TEXTURE, HES_INACTIVE_SEARCH,"No texture search is active");
		return false;
	}

	if ((list = context->_hoops_IHPGI->list) != null) do {
		_hoops_RCR		*item = (_hoops_RCR *)list->item;

		context->_hoops_IHPGI->list = list->next;
		FREE (list, _hoops_AGHPR);
		list = context->_hoops_IHPGI->list;

		/* _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_PGHPR */
		if (!BIT (item->_hoops_RRHH, _hoops_HGAGR)) {
			HI_Return_Sprintf1 (_hoops_IAGIH, -1, "%qn", (void *)&item->name);
			_hoops_HPRH (item);
			return true;
		}
		else _hoops_HPRH (item);
	}
	_hoops_RGGA (list == null);
#endif
#endif

	return false;
}

HC_INTERFACE bool HC_CDECL HC_Find_Shader (
	char alter *	_hoops_IAGIH)
{
	_hoops_PAPPR context("Find_Shader");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Shader () */\n");
	);

	_hoops_AGHPR	*			list;

	if (context->_hoops_CHPGI == null) {
		HE_ERROR (HEC_TEXTURE, HES_INACTIVE_SEARCH, "No shader search is active");
		return false;
	}

	if ((list = context->_hoops_CHPGI->list) != null) do {
		_hoops_RCR *			item = (_hoops_RCR *)list->item;

		context->_hoops_CHPGI->list = list->next;
		FREE (list, _hoops_AGHPR);
		list = context->_hoops_CHPGI->list;

		/* _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_PGHPR */
		if (!BIT (item->_hoops_RRHH, _hoops_HGAGR)) {
			HI_Return_Sprintf1 (_hoops_IAGIH, -1, "%qn", (void *)&item->name);
			_hoops_HPRH (item);
			return true;
		}
		else _hoops_HPRH (item);
	} while (list != null);
#endif
#endif

	return false;
}



HC_INTERFACE void HC_CDECL HC_Show_Texture_Count (
	int *					count)
{
	_hoops_PAPPR context("Show_Texture_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
	*count = 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Texture_Count () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_IHPGI;

	if (_hoops_GGHPR == null) {
		*count = 0;
		HE_ERROR (HEC_TEXTURE, HES_INACTIVE_SEARCH, "No texture search is active");
	}
	else
		*count = _hoops_GGHPR->count;
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Texture_Search (void)
{
	_hoops_PAPPR context("End_Texture_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Texure_Search () */\n");
	);


	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_IHPGI;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_TEXTURE, HES_END_WITHOUT_BEGIN_SEARCH, "End without Begin");
		return;
	}

	HI_Free_Search_List (context, _hoops_GGHPR->list);

	context->_hoops_IHPGI = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Shader_Search (void)
{
	_hoops_PAPPR context("End_Shader_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
	HI_Dump_Code ("/* HC_End_Shader_Search () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_CHPGI;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_TEXTURE, HES_END_WITHOUT_BEGIN_SEARCH, "End without Begin");
		return;
	}

	HI_Free_Search_List (context, _hoops_GGHPR->list);

	context->_hoops_CHPGI = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
#endif
}




GLOBAL_FUNCTION _hoops_RCR * HI_Look_Up_Texture (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_HCRPR const *			name)
{
#ifndef DISABLE_TEXTURING
	_hoops_RSIIR(_hoops_RIGC);

	_hoops_CPAIR *	_hoops_CICSR = (_hoops_CPAIR*) HI_Find_Attribute(_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, -_hoops_IPAIR);

	if (!_hoops_CICSR)
		return null;

	Integer32	key;
	_hoops_HCARA(*name, key);

	if (key) {
		for (int i=0; i<_hoops_CICSR->count; i++) {
			if (key == _hoops_CICSR->keys[i]) {
				_hoops_RCR *	texture = _hoops_CICSR->textures[i];

				if (_hoops_RAHSR(*name, texture->name)) {
					_hoops_HPRH(_hoops_CICSR);
					return texture;
				}
			}
		}
	}

	_hoops_HPRH(_hoops_CICSR);
#endif
	return null;
}















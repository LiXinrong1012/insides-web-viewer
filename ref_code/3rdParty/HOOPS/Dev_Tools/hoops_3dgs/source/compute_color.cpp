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
 * $Id: obf_tmp.txt 1.66 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



GLOBAL_FUNCTION void HI_RGB_To_HLS (
	RGB const	*rgb,
	_hoops_PACHR			*_hoops_HACHR) {
	float			_hoops_ARAHR, _hoops_RCSAA;

	if (rgb->green < rgb->red) {
		if (rgb->blue < rgb->green) {
			_hoops_RCSAA = rgb->red - rgb->blue;
			if (_hoops_RCSAA < 0.0001f) goto _hoops_ACSAA;
			_hoops_ARAHR = rgb->red + rgb->blue;
			_hoops_HACHR->_hoops_SCPHR = _hoops_ISSSR ((_hoops_ARAHR - 2.0f*rgb->green) / _hoops_RCSAA) / 3.0f;
		}
		else if (rgb->red < rgb->blue) {
			_hoops_RCSAA = rgb->blue - rgb->green;
			if (_hoops_RCSAA < 0.0001f) goto _hoops_ACSAA;
			_hoops_ARAHR = rgb->blue + rgb->green;
			_hoops_HACHR->_hoops_SCPHR = _hoops_ISSSR ((_hoops_ARAHR - 2.0f*rgb->red) / _hoops_RCSAA) / 3.0f + 240.0f;
		}
		else {
			_hoops_RCSAA = rgb->red - rgb->green;
			if (_hoops_RCSAA < 0.0001f) goto _hoops_ACSAA;
			_hoops_ARAHR = rgb->red + rgb->green;
			_hoops_HACHR->_hoops_SCPHR = _hoops_ISSSR ((2.0f*rgb->blue - _hoops_ARAHR) / _hoops_RCSAA) / 3.0f + 300.0f;
		}
	}
	else {
		if (rgb->blue < rgb->red) {
			_hoops_RCSAA = rgb->green - rgb->blue;
			if (_hoops_RCSAA < 0.0001f) goto _hoops_ACSAA;
			_hoops_ARAHR = rgb->green + rgb->blue;
			_hoops_HACHR->_hoops_SCPHR = _hoops_ISSSR ((2.0f*rgb->red - _hoops_ARAHR) / _hoops_RCSAA) / 3.0f + 60.0f;
		}
		else if (rgb->blue < rgb->green) {
			_hoops_RCSAA = rgb->green - rgb->red;
			if (_hoops_RCSAA < 0.0001f) goto _hoops_ACSAA;
			_hoops_ARAHR = rgb->green + rgb->red;
			_hoops_HACHR->_hoops_SCPHR = _hoops_ISSSR ((_hoops_ARAHR - 2.0f*rgb->blue) / _hoops_RCSAA) / 3.0f + 120.0f;
		}
		else {
			_hoops_RCSAA = rgb->blue - rgb->red;
			if (_hoops_RCSAA < 0.0001f) goto _hoops_ACSAA;
			_hoops_ARAHR = rgb->blue + rgb->red;
			_hoops_HACHR->_hoops_SCPHR = _hoops_ISSSR ((2.0f*rgb->green - _hoops_ARAHR) / _hoops_RCSAA) / 3.0f + 180.0f;
		}
	}

/*
	_hoops_RPP (_hoops_RRAS >= 1.0f)
		_hoops_PCSAA->_hoops_HCSAA = _hoops_ICSAA / (2.0f - _hoops_RRAS);
	_hoops_SHS
		_hoops_PCSAA->_hoops_HCSAA = _hoops_ICSAA / _hoops_RRAS;
*/
	_hoops_HACHR->_hoops_ISPHR = _hoops_RCSAA;

	_hoops_HACHR->_hoops_HSPHR = _hoops_ARAHR * 0.5f;

	if (_hoops_HACHR->_hoops_SCPHR < 0.0f)
		_hoops_HACHR->_hoops_SCPHR += 360.0f;
	else if (_hoops_HACHR->_hoops_SCPHR >= 360.0f)
		_hoops_HACHR->_hoops_SCPHR -= 360.0f;

	return;		/* _hoops_RSGR _hoops_IIGR _hoops_GSSR _hoops_AGIR */

	_hoops_ACSAA:;		/* _hoops_CCSAA _hoops_AGIR */
	_hoops_HACHR->_hoops_ISPHR = 0.0f;
	_hoops_HACHR->_hoops_HSPHR = rgb->red;	/* "_hoops_PRRRA" _hoops_HRGR _hoops_SCSAA */
	_hoops_HACHR->_hoops_SCPHR = 0.0f;
}





/*
 * _hoops_GHAP _hoops_GRS _hoops_HPCAR _hoops_SGS:
 *					_hoops_GGHR _hoops_HRGR "_hoops_HAR _hoops_HICAA"
 *					0.0 <= _hoops_GSSAA <=	  1.0
 *					0.0 <= _hoops_GRI <=	  1.0
 *
 *		_hoops_HAIR			_hoops_RSSAA _hoops_RCSA
 *
 *		_hoops_PRRRA				  0
 *		_hoops_ASSAA			120
 *		_hoops_HRRRA			240
 */


GLOBAL_FUNCTION void HI_HLS_To_RGB (
	_hoops_PACHR const	*_hoops_HACHR,
	RGB			*_hoops_PSSAA) 
{
	RGB temp;
	RGB *rgb;

	if (_hoops_HACHR == (_hoops_PACHR const *)_hoops_PSSAA)
		rgb = &temp;
	else
		rgb = _hoops_PSSAA;

	if (_hoops_HACHR->_hoops_ISPHR < 0.0001f)
		rgb->red = rgb->green = rgb->blue = _hoops_HACHR->_hoops_HSPHR;
	else {
		float			_hoops_RCSAA;
		float			_hoops_SCPHR = _hoops_HACHR->_hoops_SCPHR;

/*
		_hoops_RPP (_hoops_PCSAA->_hoops_HSSAA <= 0.5f)
			_hoops_ICSAA = _hoops_PCSAA->_hoops_HSSAA * _hoops_PCSAA->_hoops_HCSAA;
		_hoops_SHS
			_hoops_ICSAA = (1.0f - _hoops_PCSAA->_hoops_HSSAA) * _hoops_PCSAA->_hoops_HCSAA;
*/
		_hoops_RCSAA = 0.5f * _hoops_HACHR->_hoops_ISPHR;

#		define	func(x)			COS ((x) * 3.0f)

		if (_hoops_SCPHR < -1e5f || _hoops_SCPHR > 1e5f) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								"Color hue is unreasonable");
			/* _hoops_ASRC _hoops_ISSAA */
			rgb->red   = 1.0f;
			rgb->green = 0.0f;
			rgb->blue  = 1.0f;
			goto done;
		}

		while (_hoops_SCPHR >= 360.0f) _hoops_SCPHR -= 360.0f;
		while (_hoops_SCPHR < 0.0f) _hoops_SCPHR += 360.0f;

		switch ((int)(_hoops_SCPHR * 1.0f/60.0f)) {
			case 0:		{
				rgb->red = _hoops_HACHR->_hoops_HSPHR + _hoops_RCSAA;
				rgb->green = _hoops_HACHR->_hoops_HSPHR - _hoops_RCSAA * func (_hoops_SCPHR);
				rgb->blue = _hoops_HACHR->_hoops_HSPHR - _hoops_RCSAA;
			}	break;
			case 1:		{
				rgb->red = _hoops_HACHR->_hoops_HSPHR + _hoops_RCSAA * func (_hoops_SCPHR - 60.0f);
				rgb->green = _hoops_HACHR->_hoops_HSPHR + _hoops_RCSAA;
				rgb->blue = _hoops_HACHR->_hoops_HSPHR - _hoops_RCSAA;
			}	break;
			case 2:		{
				rgb->green = _hoops_HACHR->_hoops_HSPHR + _hoops_RCSAA;
				rgb->blue = _hoops_HACHR->_hoops_HSPHR - _hoops_RCSAA * func (_hoops_SCPHR - 120.0f);
				rgb->red = _hoops_HACHR->_hoops_HSPHR - _hoops_RCSAA;
			}	break;
			case 3:		{
				rgb->green = _hoops_HACHR->_hoops_HSPHR + _hoops_RCSAA * func (_hoops_SCPHR - 180.0f);
				rgb->blue = _hoops_HACHR->_hoops_HSPHR + _hoops_RCSAA;
				rgb->red = _hoops_HACHR->_hoops_HSPHR - _hoops_RCSAA;
			}	break;
			case 4:		{
				rgb->blue = _hoops_HACHR->_hoops_HSPHR + _hoops_RCSAA;
				rgb->red = _hoops_HACHR->_hoops_HSPHR - _hoops_RCSAA * func (_hoops_SCPHR - 240.0f);
				rgb->green = _hoops_HACHR->_hoops_HSPHR - _hoops_RCSAA;
			}	break;
			case 5:		{
				rgb->blue = _hoops_HACHR->_hoops_HSPHR + _hoops_RCSAA * func (_hoops_SCPHR - 300.0f);
				rgb->red = _hoops_HACHR->_hoops_HSPHR + _hoops_RCSAA;
				rgb->green = _hoops_HACHR->_hoops_HSPHR - _hoops_RCSAA;
			}	break;
		}

		if (rgb->red < 0.0f) rgb->red = 0.0f;
		if (rgb->green < 0.0f) rgb->green = 0.0f;
		if (rgb->blue < 0.0f) rgb->blue = 0.0f;
		if (rgb->red > 1.0f) rgb->red = 1.0f;
		if (rgb->green > 1.0f) rgb->green = 1.0f;
		if (rgb->blue > 1.0f) rgb->blue = 1.0f;
	}
  done:
	if (rgb != _hoops_PSSAA)
		*_hoops_PSSAA = *rgb;
}



HC_INTERFACE bool HC_CDECL HC_Compute_Color (
	char const *				color,
	char const *				type,
	RGB *						value) 
{
	_hoops_PAPPR context("Compute_Color");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Color () */\n");
	);

	_hoops_HCRPR						name;
	Named_Material				_hoops_ISHIR;

	HI_Canonize_Chars (color, &name);

	ZERO_STRUCT(&_hoops_ISHIR, Named_Material);
	_hoops_CSPPR();
	if (!HI_Evaluate_Color (context, &name, &_hoops_ISHIR, 0, false) ||
		_hoops_ISHIR._hoops_PRGRA != (M_DIFFUSE|_hoops_RHGRA)) {
		_hoops_IRRPR();
		HI_Free_Diffuse_Channel_List (_hoops_ISHIR._hoops_SCA);
		_hoops_ISHIR._hoops_SCA = null;
		HI_Free_Material_Names (&_hoops_ISHIR, 1);
		_hoops_RGAIR (name);
		return false;
	}
	_hoops_IRRPR();
	/* _hoops_SR _hoops_GA'_hoops_RA _hoops_SGH _hoops_RH _hoops_IHSR _hoops_RPPCR, _hoops_HIS _hoops_SHH _hoops_RCRR _hoops_IS _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_CAPR */
	HI_Free_Material_Names (&_hoops_ISHIR, 1);

	/* _hoops_IPIH _hoops_HRS _hoops_RGAR _hoops_SPI _hoops_IHSR */
	if (!BIT (_hoops_ISHIR._hoops_PRGRA, M_DIFFUSE)) {
		HE_ERROR (HEC_COMPUTE, HES_NO_DIFFUSE_COLOR_COMPONENT, "Color has no diffuse component");
		_hoops_RGAIR (name);
		return false;
	}
	_hoops_RGAIR (name);

	while (*type == ' '	 ||	 *type == '\t')	 type++;

	if (*type == '\0') {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_COLOR_SPACE, "No output color space specified");
		return false;
	}

	_hoops_PACHR const *					_hoops_HACHR = (_hoops_PACHR const *)&_hoops_ISHIR._hoops_CSHR;

	if (type[0] == 'h'	||	type[0] == 'H') {
		if ((type[2] == 's' || type[2] == 'S') &&
			(type[1] == 'l' || type[1] == 'L' ||
			 type[1] == 'i' || type[1] == 'I')) {
			value->red = _hoops_HACHR->_hoops_SCPHR;
			value->green = _hoops_HACHR->_hoops_HSPHR;
			value->blue = _hoops_HACHR->_hoops_ISPHR;
		}
		else if ((type[1] == 's' || type[1] == 'S') &&
				 (type[2] == 'v' || type[2] == 'V')) {
			value->red = _hoops_HACHR->_hoops_SCPHR;
			value->green = _hoops_HACHR->_hoops_ISPHR;
			value->blue = _hoops_HACHR->_hoops_HSPHR + 0.5f * _hoops_HACHR->_hoops_ISPHR;
		}
		else if ((type[1] == 'i' || type[1] == 'I') &&
				 (type[2] == 'c' || type[2] == 'C')) {
			value->red = _hoops_HACHR->_hoops_SCPHR;
			value->green = _hoops_HACHR->_hoops_HSPHR;
			if (_hoops_HACHR->_hoops_HSPHR < 0.001f || _hoops_HACHR->_hoops_HSPHR > 0.999f)
				value->blue = 0.0f;
			else
				if (_hoops_HACHR->_hoops_HSPHR <= 0.5f)
					value->blue = _hoops_HACHR->_hoops_ISPHR / (2.0f * _hoops_HACHR->_hoops_HSPHR);
				else
					value->blue = _hoops_HACHR->_hoops_ISPHR / (2.0f - 2.0f * _hoops_HACHR->_hoops_HSPHR);
		}
		else {
			HE_ERROR (HEC_COMPUTE, HES_INVALID_COLOR_SPACE,
					  Sprintf_S (null, "Output color space '%s' not recognized", type));
			return false;
		}
	}
	else if ((type[0] == 'r' || type[0] == 'R') &&
			 (type[1] == 'g' || type[1] == 'G') &&
			 (type[2] == 'b' || type[2] == 'B')) {
		RGB						rgb;

		HI_HLS_To_RGB (_hoops_HACHR, &rgb);
		*value = rgb;
	}
	else {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_COLOR_SPACE,
				  Sprintf_S (null, "Output color space '%s' not recognized", type));
		return false;
	}

	return true;
#endif
}


HC_INTERFACE bool HC_CDECL HC_Compute_Color_By_Value (
	char const *	_hoops_CSSAA,
	RGB const *		in,
	char const *	_hoops_SSSAA,
	RGB *			_hoops_PAGR) 
{
	_hoops_PAPPR context("Compute_Color_By_Value");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Color_By_Value () */\n");
	);

	_hoops_PACHR			_hoops_HACHR;
	RGB			rgb;
	float		tmp;

	while (*_hoops_CSSAA == ' ' || *_hoops_CSSAA == '\t')
		_hoops_CSSAA++;
	while (*_hoops_SSSAA == ' ' || *_hoops_SSSAA == '\t')
		_hoops_SSSAA++;

	if (*_hoops_CSSAA == '\0') {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_COLOR_SPACE, "No input color space specified");
		return false;
	}
	if (*_hoops_SSSAA == '\0') {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_COLOR_SPACE, "No output color space specified");
		return false;
	}

	if (_hoops_CSSAA[0] == 'h' || _hoops_CSSAA[0] == 'H') {
		_hoops_HACHR._hoops_SCPHR = in->red;
		_hoops_HACHR._hoops_HSPHR = in->green;
		_hoops_HACHR._hoops_ISPHR = in->blue;

		if (_hoops_HACHR._hoops_SCPHR > 1e5f || _hoops_HACHR._hoops_SCPHR < -1e5f) {
			return false;
		}

		while (_hoops_HACHR._hoops_SCPHR >= 360.0f)
			_hoops_HACHR._hoops_SCPHR -= 360.0f;
		while (_hoops_HACHR._hoops_SCPHR < 0.0f)
			_hoops_HACHR._hoops_SCPHR += 360.0f;

		if ((_hoops_CSSAA[1] == 'l' || _hoops_CSSAA[1] == 'L' ||
			 _hoops_CSSAA[1] == 'i' || _hoops_CSSAA[1] == 'I') &&
			 _hoops_CSSAA[2] == 's' || _hoops_CSSAA[2] == 'S') {
			if (_hoops_HACHR._hoops_HSPHR > 1.0f || _hoops_HACHR._hoops_HSPHR < 0.0f) {
				return false;
			}
		}
		else if ((_hoops_CSSAA[1] == 'i' || _hoops_CSSAA[1] == 'I') &&
				 (_hoops_CSSAA[2] == 'c' || _hoops_CSSAA[2] == 'C')) {
			if (_hoops_HACHR._hoops_ISPHR > 1.0f || _hoops_HACHR._hoops_ISPHR < 0.0f) {
				return false;
			}

			if (_hoops_HACHR._hoops_HSPHR > 1.0f || _hoops_HACHR._hoops_HSPHR < 0.0f) {
				return false;
			}

			if (_hoops_HACHR._hoops_HSPHR <= 0.5f)
				_hoops_HACHR._hoops_ISPHR *= 2.0f*_hoops_HACHR._hoops_HSPHR;
			else
				_hoops_HACHR._hoops_ISPHR *= (2.0f - 2.0f*_hoops_HACHR._hoops_HSPHR);
		}
		else if ((_hoops_CSSAA[1] == 's' || _hoops_CSSAA[1] == 'S') &&
				 (_hoops_CSSAA[2] == 'v' || _hoops_CSSAA[2] == 'V')) {
			if (_hoops_HACHR._hoops_ISPHR > 1.0f || _hoops_HACHR._hoops_ISPHR < 0.0f) {
				return false;
			}

			if (_hoops_HACHR._hoops_HSPHR > _hoops_HACHR._hoops_ISPHR || _hoops_HACHR._hoops_HSPHR < 0.0f) {
				return false;
			}

			/* _hoops_PAGA: _hoops_CSCHR _hoops_CICHR _hoops_IIGR _hoops_GGGPA _hoops_PPR _hoops_RGGPA */
			tmp = _hoops_HACHR._hoops_HSPHR;
			_hoops_HACHR._hoops_HSPHR = _hoops_HACHR._hoops_ISPHR;
			_hoops_HACHR._hoops_ISPHR = tmp;

			_hoops_HACHR._hoops_HSPHR -= 0.5f * _hoops_HACHR._hoops_ISPHR;
		}
		else {
			HE_ERROR (HEC_COMPUTE, HES_INVALID_COLOR_SPACE,
					  Sprintf_S (null, "Input color space '%s' not recognized",_hoops_CSSAA));
			return false;
		}
	}
	else if ((_hoops_CSSAA[0] == 'r' || _hoops_CSSAA[0] == 'R') &&
			 (_hoops_CSSAA[1] == 'g' || _hoops_CSSAA[1] == 'G') &&
			 (_hoops_CSSAA[2] == 'b' || _hoops_CSSAA[2] == 'B')) {

		rgb = *in;

		if (rgb.red < 0.0f || rgb.red > 1.0f) {
			return false;
		}
		if (rgb.green < 0.0f || rgb.green > 1.0f) {
			return false;
		}
		if (rgb.blue < 0.0f || rgb.blue > 1.0f) {
			return false;
		}

		/* _hoops_ICHRR-_hoops_AACC _hoops_RPP _hoops_AGGPA == _hoops_PGGPA == "_hoops_HGGPA" */
		if (_hoops_IGGPA("rgb", _hoops_SSSAA)) {
			*_hoops_PAGR = *in;
			return true;
		}

		HI_RGB_To_HLS (&rgb, &_hoops_HACHR);
	}
	else {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_COLOR_SPACE, Sprintf_S (null, "Input color space '%s' not recognized", _hoops_CSSAA));
		return false;
	}

	if (_hoops_SSSAA[0] == 'h' || _hoops_SSSAA[0] == 'H') {
		if ((_hoops_SSSAA[2] == 's' || _hoops_SSSAA[2] == 'S') &&
			(_hoops_SSSAA[1] == 'l' || _hoops_SSSAA[1] == 'L' ||
			 _hoops_SSSAA[1] == 'i' || _hoops_SSSAA[1] == 'I')) {
			_hoops_PAGR->red = _hoops_HACHR._hoops_SCPHR;
			_hoops_PAGR->green = _hoops_HACHR._hoops_HSPHR;
			_hoops_PAGR->blue = _hoops_HACHR._hoops_ISPHR;
		}
		else if ((_hoops_SSSAA[1] == 's' || _hoops_SSSAA[1] == 'S') &&
				 (_hoops_SSSAA[2] == 'v' || _hoops_SSSAA[2] == 'V')) {
			_hoops_PAGR->red = _hoops_HACHR._hoops_SCPHR;
			_hoops_PAGR->green = _hoops_HACHR._hoops_ISPHR;
			_hoops_PAGR->blue = _hoops_HACHR._hoops_HSPHR + 0.5f * _hoops_HACHR._hoops_ISPHR;
		}
		else if ((_hoops_SSSAA[1] == 'i' || _hoops_SSSAA[1] == 'I') &&
				 (_hoops_SSSAA[2] == 'c' || _hoops_SSSAA[2] == 'C')) {
			_hoops_PAGR->red = _hoops_HACHR._hoops_SCPHR;
			_hoops_PAGR->green = _hoops_HACHR._hoops_HSPHR;
			if (_hoops_HACHR._hoops_HSPHR < 0.001f  ||  _hoops_HACHR._hoops_HSPHR > 0.999f)
				_hoops_PAGR->blue = 0.0f;
			else
				if (_hoops_HACHR._hoops_HSPHR <= 0.5f)
					_hoops_PAGR->blue = _hoops_HACHR._hoops_ISPHR / (2.0f * _hoops_HACHR._hoops_HSPHR);
				else
					_hoops_PAGR->blue = _hoops_HACHR._hoops_ISPHR / (2.0f	 -	2.0f * _hoops_HACHR._hoops_HSPHR);
		}
		else
			HE_ERROR (HEC_COMPUTE, HES_INVALID_COLOR_SPACE,
					  Sprintf_S (null, "Output color space '%s' not recognized", _hoops_SSSAA));
	}
	else if ((_hoops_SSSAA[0] == 'r' || _hoops_SSSAA[0] == 'R') &&
			 (_hoops_SSSAA[1] == 'g' || _hoops_SSSAA[1] == 'G') &&
			 (_hoops_SSSAA[2] == 'b' || _hoops_SSSAA[2] == 'B')) {
		HI_HLS_To_RGB (&_hoops_HACHR, &rgb);
		*_hoops_PAGR = rgb;
	}
	else {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_COLOR_SPACE,
				  Sprintf_S (null, "Output color space '%s' not recognized", _hoops_SSSAA));
		return false;
	}

	return true;
#endif
}

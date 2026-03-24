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
 * $Id: obf_tmp.txt 1.56 2010-10-06 19:16:43 jason Exp $
 */



#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"


/* _hoops_HISI: _hoops_HPSRS -> _hoops_ICCGI */
GLOBAL_FUNCTION void HI_Return_Kars (
	char					*_hoops_PAGR,
	int						_hoops_ICHPP,
	Karacter const			*in,
	int						_hoops_GSCIH,
	_hoops_IHGRP		encoding) {
	local const char			_hoops_SSACR[] =
						"Return string won't fit in provided space; truncated";


	if (_hoops_ICHPP == -1) { /* _hoops_IHRPR _hoops_GSGR _hoops_ASRC */
		_hoops_ICHPP = HOOPS_WORLD->_hoops_RAPPR;

		switch (encoding) {
			case _hoops_SSAIP: {
				if (_hoops_GSCIH > _hoops_ICHPP - 1) {
					HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
							_hoops_SSACR);
					_hoops_GSCIH = _hoops_ICHPP - 1;
				}

				if (_hoops_GSCIH > 0) do {
					*_hoops_PAGR++ = (char)*in++; /* _hoops_SICR _hoops_IAHPH _hoops_IS _hoops_GSPR */
				} _hoops_RGGA (--_hoops_GSCIH == 0);

				*_hoops_PAGR = '\0';
			}	break;

			case _hoops_RGHPH: {
				if (_hoops_GSCIH*2 > _hoops_ICHPP - 1) {
					HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
							_hoops_SSACR);
					_hoops_GSCIH = (_hoops_ICHPP - 1)/2;
				}

				if (_hoops_GSCIH > 0) do {
					*_hoops_PAGR++ = (char)((*in >> 8) & 0x00FF);
					*_hoops_PAGR++ = (char)(*in & 0x00FF); /* _hoops_SICR _hoops_IAHPH _hoops_IS 2 _hoops_GSPR */
					++in;
				} _hoops_RGGA (--_hoops_GSCIH == 0);

				*_hoops_PAGR++ = '\0';
				*_hoops_PAGR = '\0';
			} break;

			case _hoops_GSPPH:{

				H_UTF16 _hoops_RSPPH;
				_hoops_RSPPH.encodedText( (utf16_char const*)in );
				H_UTF8 _hoops_ASPPH(_hoops_RSPPH);
				
				_hoops_GSCIH = (int)_hoops_ASPPH.length();

				if ((int)(_hoops_GSCIH*sizeof(utf8_char)) > _hoops_ICHPP - 1) {
					HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
							_hoops_SSACR);
					_hoops_GSCIH = (_hoops_ICHPP - 1)/sizeof(utf8_char);
				}

				utf8_char const * _hoops_PSPPH = _hoops_ASPPH.encodedText();
				if (_hoops_GSCIH > 0) do {
					*_hoops_PAGR++ = (char)*_hoops_PSPPH++;
				} _hoops_RGGA (--_hoops_GSCIH == 0);

				*_hoops_PAGR = '\0';
			} break;

			case _hoops_HSPPH:{

				H_UTF16 _hoops_RSPPH;
				_hoops_RSPPH.encodedText( (utf16_char const*)in );
				H_UTF32 _hoops_ISPPH(_hoops_RSPPH);

				_hoops_GSCIH = (int)_hoops_ISPPH.length();
				
				if ((int)(_hoops_GSCIH*sizeof(utf32_char)) > _hoops_ICHPP - 1) {
					HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
							_hoops_SSACR);
					_hoops_GSCIH = (_hoops_ICHPP - 1)/sizeof(utf32_char);
				}

				H_UTF32::iterator _hoops_IPSRS = _hoops_ISPPH.begin();
				int * _hoops_RGIGS = (int*)_hoops_PAGR;
				if (_hoops_GSCIH > 0) do {
					*_hoops_RGIGS++ = *_hoops_IPSRS++;
				} _hoops_RGGA (--_hoops_GSCIH == 0);

				*_hoops_RGIGS = 0;
			} break;

			case _hoops_CSPPH:
			case _hoops_SSPPH:{

				H_UTF16 _hoops_RSPPH;
				_hoops_RSPPH.encodedText( (utf16_char const*)in );
				H_WCS _hoops_GGHPH(_hoops_RSPPH);
				
				_hoops_GSCIH = (int)_hoops_GGHPH.length();
				
				if ((int)(_hoops_GSCIH*sizeof(wchar_t)) > _hoops_ICHPP - 1) {
					HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
							_hoops_SSACR);
					_hoops_GSCIH = (_hoops_ICHPP - 1)/sizeof(wchar_t);
				}

				wchar_t const * _hoops_PSPPH = _hoops_GGHPH.encodedText();
				wchar_t * _hoops_CPSRS = (wchar_t*)_hoops_PAGR;
				if (_hoops_GSCIH > 0) do {
					*_hoops_CPSRS++ = (wchar_t)*_hoops_PSPPH++;
				} _hoops_RGGA (--_hoops_GSCIH == 0);

				*_hoops_CPSRS = L'\0';
			} break;

			case _hoops_AGHPH:
			case _hoops_SACSR: {
				unsigned short	*_hoops_AGRIH = (unsigned short *)_hoops_PAGR;

				if (_hoops_GSCIH*2 > _hoops_ICHPP - 1) {
					HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR);
					_hoops_GSCIH = (_hoops_ICHPP - 1)/2;
				}

				if (_hoops_GSCIH > 0) do {
					*_hoops_AGRIH++ = (unsigned short)*in++;
				} _hoops_RGGA (--_hoops_GSCIH == 0);

				*_hoops_AGRIH = 0x0000;
			} break;

			case _hoops_HIIGI:
			case _hoops_RPHPH:
			case _hoops_APHPH: {
				if (_hoops_GSCIH > 0) do {
					if (((Integer32)*in & 0x0000FF00L) == 0) {
						if (--_hoops_ICHPP < 1) {
							HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR);
							break;
						}
						*_hoops_PAGR++ = (char)*in;				/* _hoops_RSRA _hoops_RAPSR _hoops_PIRA */
					}
					else {
						if ((_hoops_ICHPP -= 2) < 1) {
							HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
									_hoops_SSACR);
							break;
						}
						/* _hoops_SICR _hoops_IAHPH _hoops_IS 2 _hoops_GSPR */
						*_hoops_PAGR++ = (char)((*in >> 8) & 0x00FF);
						*_hoops_PAGR++ = (char)(*in & 0x00FF);
					}
					++in;
				} _hoops_RGGA (--_hoops_GSCIH == 0);
				*_hoops_PAGR = '\0';
			}	break;
		}
	}
	else {		/* _hoops_RGPCR & _hoops_AGPCR _hoops_GSGR _hoops_ASRC */
		switch (encoding) {
			case _hoops_SSAIP: {
				if (_hoops_GSCIH > _hoops_ICHPP) {
					HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
							_hoops_SSACR);
					_hoops_GSCIH = _hoops_ICHPP;
				}

				_hoops_ICHPP -= _hoops_GSCIH;		/* (_hoops_PHI _hoops_IIGR _hoops_ARRCC _hoops_RGHP) */

				if (_hoops_GSCIH > 0) do {
					*_hoops_PAGR++ = (char)*in++; /* _hoops_SICR _hoops_IAHPH _hoops_IS _hoops_GSPR */
				} _hoops_RGGA (--_hoops_GSCIH == 0);

				if (_hoops_ICHPP > 0) do {
					*_hoops_PAGR++ = ' ';
				} _hoops_RGGA (--_hoops_ICHPP == 0);
			}

			case _hoops_RGHPH: {
				if (_hoops_GSCIH*2 > _hoops_ICHPP) {
					HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
							_hoops_SSACR);
					_hoops_GSCIH = _hoops_ICHPP/2;
				}

				_hoops_ICHPP /= 2;			/* _hoops_PHI _hoops_IIGR _hoops_HPSRS _hoops_APSR */
				_hoops_ICHPP -= _hoops_GSCIH;		/* (_hoops_PHI _hoops_IIGR _hoops_ARRCC _hoops_RGHP) */

				if (_hoops_GSCIH > 0) do {
					*_hoops_PAGR++ = (char)((*in >> 8) & 0x00FF);
					*_hoops_PAGR++ = (char)(*in & 0x00FF); /* _hoops_SICR _hoops_IAHPH _hoops_IS 2 _hoops_GSPR */
					++in;
				} _hoops_RGGA (--_hoops_GSCIH == 0);

				if (_hoops_ICHPP > 0) do {
					*_hoops_PAGR++ = ' ';
					*_hoops_PAGR++ = '\0';
				} _hoops_RGGA (--_hoops_ICHPP == 0);
			}	break;

			case _hoops_GSPPH:
			case _hoops_AGHPH:
			case _hoops_HSPPH:
			case _hoops_SSPPH:
			case _hoops_CSPPH:
			case _hoops_SACSR: {
				unsigned short	*_hoops_AGRIH = (unsigned short *)_hoops_PAGR;

				if (_hoops_GSCIH*2 > _hoops_ICHPP) {
					HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
							_hoops_SSACR);
					_hoops_GSCIH = _hoops_ICHPP/2;
				}

				_hoops_ICHPP /= 2;			/* _hoops_PHI _hoops_IIGR _hoops_HPSRS _hoops_APSR */
				_hoops_ICHPP -= _hoops_GSCIH;		/* (_hoops_PHI _hoops_IIGR _hoops_ARRCC _hoops_RGHP) */

				if (_hoops_GSCIH > 0) do {
					*_hoops_AGRIH++ = (unsigned short)*in++;
				} _hoops_RGGA (--_hoops_GSCIH == 0);

				if (_hoops_ICHPP > 0) do {
					*_hoops_AGRIH++ = (unsigned short)' ';
				} _hoops_RGGA (--_hoops_ICHPP == 0);
			}	break;

			case _hoops_HIIGI:
			case _hoops_RPHPH:
			case _hoops_APHPH: {
				if (_hoops_GSCIH > 0) do {
					if (((Integer32)*in & 0x0000FF00L) == 0) {
						if (--_hoops_ICHPP < 0) {
							HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
									_hoops_SSACR);
							break;
						}
						*_hoops_PAGR++ = (char)*in;				/* _hoops_RSRA _hoops_RAPSR _hoops_PIRA */
					}
					else {
						if ((_hoops_ICHPP -= 2) < 0) {
							HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
									_hoops_SSACR);
							_hoops_ICHPP += 2;
							break;
						}
						/* _hoops_SICR _hoops_IAHPH _hoops_IS 2 _hoops_GSPR */
						*_hoops_PAGR++ = (char)((*in >> 8) & 0x00FF);
						*_hoops_PAGR++ = (char)(*in & 0x00FF);
					}
					++in;
				} _hoops_RGGA (--_hoops_GSCIH == 0);

				if (_hoops_ICHPP > 0) do {
					*_hoops_PAGR++ = ' ';
				} _hoops_RGGA (--_hoops_ICHPP <= 0);
			}	break;
		}
	}
}


/* _hoops_CPAGI: _hoops_HPSRS -> _hoops_HPSRS */
GLOBAL_FUNCTION void HI_Return_Karacters (
	Karacter				*_hoops_PAGR,
	int						_hoops_ICHPP,
	Karacter const		*in,
	int						_hoops_GSCIH) {
	local const char			_hoops_SSACR[] =
						"Return string won't fit in provided space; truncated";


	if (_hoops_ICHPP == -1) { /* _hoops_IHRPR _hoops_GSGR _hoops_ASRC */
		_hoops_ICHPP = HOOPS_WORLD->_hoops_RAPPR;

		if (_hoops_GSCIH > _hoops_ICHPP - 1) {
			HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR);
			_hoops_GSCIH = _hoops_ICHPP - 1;
		}

		if (_hoops_GSCIH > 0) do {
			*_hoops_PAGR++ = *in++;
		} _hoops_RGGA (--_hoops_GSCIH == 0);

		*_hoops_PAGR = 0x0000;
	}
	else {		/* _hoops_RGPCR & _hoops_AGPCR _hoops_GSGR _hoops_ASRC */
		if (_hoops_GSCIH > _hoops_ICHPP) {
			HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
					_hoops_SSACR);
			_hoops_GSCIH = _hoops_ICHPP;
		}

		_hoops_ICHPP -= _hoops_GSCIH;		/* (_hoops_PHI _hoops_IIGR _hoops_ARRCC _hoops_RGHP) */

		if (_hoops_GSCIH > 0) do {
			*_hoops_PAGR++ = *in++;
		} _hoops_RGGA (--_hoops_GSCIH == 0);

		if (_hoops_ICHPP > 0) do {
			*_hoops_PAGR++ = (Karacter)' ';
		} _hoops_RGGA (--_hoops_ICHPP == 0);
	}
}



GLOBAL_FUNCTION void HI_Return_Chars (
	char			*_hoops_PAGR,
	int				_hoops_ICHPP,
	char const		*in,
	int				_hoops_GSCIH) {
	local const char			_hoops_SSACR[] =
						"Return string won't fit in provided space; truncated";

	if (_hoops_ICHPP == -1) { /* _hoops_IHRPR _hoops_GSGR _hoops_ASRC */
		_hoops_ICHPP = HOOPS_WORLD->_hoops_RAPPR;

		if (_hoops_GSCIH > _hoops_ICHPP - 1) {
			HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
					_hoops_SSACR);
			_hoops_GSCIH = _hoops_ICHPP - 1;
		}

		if (_hoops_GSCIH > 0)
			do *_hoops_PAGR++ = *in++;
			_hoops_RGGA (--_hoops_GSCIH == 0);

		*_hoops_PAGR = '\0';
	}
	else {		/* _hoops_RGPCR & _hoops_AGPCR _hoops_GSGR _hoops_ASRC */
		if (_hoops_GSCIH > _hoops_ICHPP) {
			HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
					_hoops_SSACR);
			_hoops_GSCIH = _hoops_ICHPP;
		}

		_hoops_ICHPP -= _hoops_GSCIH;		/* (_hoops_PHI _hoops_IIGR _hoops_ARRCC _hoops_RGHP) */

		if (_hoops_GSCIH > 0)
			do *_hoops_PAGR++ = *in++;
			_hoops_RGGA (--_hoops_GSCIH == 0);

		if (_hoops_ICHPP > 0) {
			*_hoops_PAGR++ = '\0';
			--_hoops_ICHPP;
		}

		if (_hoops_ICHPP > 0)
			do *_hoops_PAGR++ = ' ';
			_hoops_RGGA (--_hoops_ICHPP == 0);
	}
}




GLOBAL_FUNCTION void HI_Return_Sprintf1 (
	char			*_hoops_ASAPR,
	int				length,
	char const		*spec,
	void const		*item) {
	char			*_hoops_PSAPR;

	if (length == -1) {
		_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR - 1;
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, spec, item);
		if (_hoops_ASAPR != null) *_hoops_ASAPR = '\0';
	}
	else {
		_hoops_PSAPR = _hoops_ASAPR + length;
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, spec, item);
		if (_hoops_ASAPR != null && _hoops_ASAPR != _hoops_PSAPR) {
			do *_hoops_ASAPR++ = ' ';
			_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR);
		}
	}
	if (_hoops_ASAPR == null) HE_WARNING (HEC_MEMORY, HES_BUFFER_OVERFLOW,
						"Return string won't fit in provide space;	Truncated");
}




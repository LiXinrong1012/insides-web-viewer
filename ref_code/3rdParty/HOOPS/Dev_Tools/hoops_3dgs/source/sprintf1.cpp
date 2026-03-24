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
 * $Id: obf_tmp.txt 1.76 2010-08-06 19:08:20 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hpserror.h"

#define _hoops_IAIHS(x)		('0' + (char)(x))


local bool _hoops_CAIHS (
	char			*string) {

	if (*string != '\0') do {
		if ('a' <= *string && *string <= 'z') {}
		else if ('0' <= *string && *string <= '9') {}

		else switch (*string) {
			case ' ':
				if (string[1] == ' ')
					return true;

			case '#':	 case '+':	  case '-':
			case '$':	 case '_':	  case '.':
				break;

			default:			
				return true;
		}
	} _hoops_RGGA (*++string == '\0');

	return	false;
}


/* _hoops_CGIC _hoops_RPP _hoops_IRS _hoops_RSIRR _hoops_SSCP _hoops_GII _hoops_GRH _hoops_HPS _hoops_PAR _hoops_GHGPR _hoops_HGS _hoops_SGS _hoops_CHH _hoops_SHH 
 * _hoops_CISS _hoops_RPP _hoops_SR _hoops_SARS'_hoops_RA _hoops_GGCR _hoops_CPARA.  (_hoops_SAIHS _hoops_HII _hoops_CPRAA _hoops_CPARA _hoops_IS _hoops_AIAH _hoops_RSIGI _hoops_RHIPP, _hoops_PHRI */
local bool _hoops_GPIHS (
	_hoops_HCRPR			*name,
	bool			_hoops_RPIHS,
	bool			_hoops_APIHS) {
	char			*string = name->text;
	int				count = name->length;
	char			_hoops_PPARA = 0;

	if (count == 0) 
		return false;

	do {
		if ('a' <= *string && *string <= 'z') {}
		else if ('0' <= *string && *string <= '9') {}
		else switch (*string) {
			case ' ': {
				if (string[1] == ' ' && !_hoops_PPARA)
					return true;
			}	break;
			
			case '#':	 case '+':	  case '-':
			case '$':	 case '_':	  case '.': {
			}	break;

			case '\'': case '"': case '`': {
				if (_hoops_PPARA) {
					if (*string == _hoops_PPARA)
						if (string[1] == _hoops_PPARA) {
							/* _hoops_SRIII _hoops_RH _hoops_CISI _hoops_HPARA _hoops_IAHA _hoops_RIRPR _hoops_GAR _hoops_PCCP _hoops_PGPCR 
							 * _hoops_ICPPR _hoops_IS _hoops_SHH _hoops_PPIHS _hoops_GAR _hoops_IRS _hoops_RSRA _hoops_HAGAR. (_hoops_IAS._hoops_ISHI.
							 * "_hoops_HPIHS'_hoops_GRI _hoops_GSSP" _hoops_PAH _hoops_GACC _hoops_SHH _hoops_AIHCR _hoops_GAR '_hoops_HPIHS''_hoops_GRI _hoops_GSSP') */
							++string;
							--count;
						}
						else
							_hoops_PPARA = 0;
				}
				else
					_hoops_PPARA = *string;
			}	break;

			/* _hoops_HPS _hoops_SGS _hoops_CHR _hoops_PHRH _hoops_GGR _hoops_CRAA _hoops_RPPCR, _hoops_HIH _hoops_HAR _hoops_GGGGR */
			case ':': {
				if (_hoops_RPIHS)
					break;
			}	_hoops_HHHI;
			default: {
				/* _hoops_AHGHS _hoops_IPIHS _hoops_HIRCC _hoops_AAGPH, _hoops_PGAP _hoops_RRP _hoops_CPIHS _hoops_HPP _hoops_CPARA _hoops_PPR
				 * _hoops_CGH _hoops_PRGPR _hoops_SHH _hoops_GHSAR "_hoops_GRH" */
				if (!_hoops_PPARA) {
					if ('A' <= *string && *string <= 'Z') {
						if (!_hoops_APIHS)
							return true;
					}
					else
						return true;
				}
			}
		}

		++string;
	} _hoops_RGGA (--count == 0);

	if (_hoops_PPARA)
		return true; /* _hoops_PARRA _hoops_CPARA (_hoops_IAS._hoops_ISHI. _hoops_HPIHS'_hoops_GRI _hoops_GSSP) */

	if (_hoops_RPIHS && *name->text == '.') {	/* _hoops_GAAP _hoops_IRS _hoops_GRH _hoops_RSIRR _hoops_SGS _hoops_PIHA _hoops_HS _hoops_RPII _hoops_CGIGI _hoops_IS _hoops_HGCR _hoops_GGR _hoops_ARI */
		switch (name->length) {
			case 1: {
				return true;	/* _hoops_PIHA _hoops_SHH ".", _hoops_RAARH _hoops_SPIP _hoops_CPHP _hoops_PII: "'.'" */
			}	_hoops_HHHI;
			case 2: {
				if (_hoops_AGGR (name->text, ".."))
					return true;
			}	break;
			case 3: {
				if (_hoops_AGGR (name->text, "..."))
					return true;
			}	break;
			case 4: {
				if (_hoops_AGGR (name->text, "...."))
					return true;
			}	break;
		}
	}

	return	false;
}

/*_hoops_SPIHS _hoops_HRGR _hoops_CSRHA _hoops_RGR _hoops_SPR _hoops_RPP _hoops_RH _hoops_ASCSC _hoops_HRGR _hoops_GPP*/
/*_hoops_IPHIA _hoops_HASIR _hoops_GGR 2005 -_hoops_GHIHS*/
//#_hoops_IHS _hoops_HIHPH
//# _hoops_RHIHS _hoops_SGGC("", _hoops_PSAP)
//#_hoops_SHIIR

GLOBAL_FUNCTION char alter * HI_Sprintf1 (
	char alter		*_hoops_ASAPR,
	char const		*_hoops_PSAPR,
	char const		*spec,
	void const		*ptr) {
	local const char			_hoops_AHIHS[] = "0123456789ABCDEF";
	long			tmp;

	if (_hoops_ASAPR == null)
		return null;	/* (_hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_PGHC _hoops_RIHH) */

	_hoops_RGGA (*spec == '\0') {
		if (_hoops_ASAPR == _hoops_PSAPR)
			return null;   /* _hoops_HPCAR _hoops_HPGR _hoops_CHGC 1 _hoops_GAS _hoops_ICPAA */

		if (*spec != '%')
			*_hoops_ASAPR++ = *spec++;
		else switch (spec += 2, spec[-1]) {
			case '.':
			case 'F':
			case 'f': {
				float			f;
				float			_hoops_PHIHS = 0.0f;
				float			scale;
				int				_hoops_GRASR = 0;
				int				_hoops_HHIHS;
				bool		_hoops_AHIPI = (spec[-1] == '.');

				if (_hoops_AHIPI) {
					_hoops_PHIHS = 0.1f;
					if (spec[0] != '0') {
						_hoops_HHIHS = (int)(spec[0] - '0');
						do _hoops_PHIHS *= 0.1f;
						_hoops_RGGA (--_hoops_HHIHS <= 0);
					}
					spec += 2;
				}

				if (spec[-1] == 'f')
					f = *(float *)ptr;
				else
					f = (float)(*(double *)ptr); /* _hoops_IHIHS _hoops_IHIHS! */

				/* _hoops_SRGAI _hoops_IRS _hoops_AIIC _hoops_CHIHS, _hoops_AHPA _hoops_IIGR 6 _hoops_IHRSP */

#				define	_hoops_SHIHS			6
#				define	_hoops_GIIHS			1e6f

				if (_hoops_PSAPR - _hoops_ASAPR < 3+_hoops_SHIHS+4)
					return null;

				/* _hoops_CISRP _hoops_SCH _hoops_PPR _hoops_ISPR _hoops_RH _hoops_HRASR */
				if (f >= 0.0f) {
					if (f < 1.0f/MAX_FLOAT)
						f = 0.0f;
					else if (f > MAX_FLOAT)
						f = MAX_FLOAT;
				}
				else {
					if (f > -1.0f/MAX_FLOAT)
						f = 0.0f;
					else {
						if (f < -MAX_FLOAT)
							f = -MAX_FLOAT;
						*_hoops_ASAPR++ = '-';	/* _hoops_AA _hoops_RH _hoops_HRASR */
						f = -f;
					}
				}

				if (f > 0.0f) {
					if (f >= _hoops_GIIHS) {
						do ++_hoops_GRASR;
						_hoops_RGGA ((f *= 0.1f) < 10.0f);
					}
					else if (0.01f > f && f > 0.0f && !_hoops_AHIPI) {
						do --_hoops_GRASR;
						_hoops_RGGA ((f *= 10.0f) >= 1.0f);
					}

					scale = _hoops_GIIHS/10.0f;

					while (scale > f) scale *= 0.1f;

					if (_hoops_PHIHS == 0.0f)
						_hoops_PHIHS = (scale >= _hoops_GIIHS) ? 0.1f : scale*(10.0f/_hoops_GIIHS);

					f += _hoops_PHIHS*0.5f;		/* _hoops_GIRR _hoops_GH */
					if (!(scale*10.0f > f))
						scale *= 10.0f; /* _hoops_CCIH _hoops_RPP _hoops_RIIHS */
				}
				else {
					scale = 0.1f;
				}

				if (scale < 0.99f /* 1 */)
					*_hoops_ASAPR++ = '0';
				else do {
					_hoops_HHIHS = (int)(f / scale);
					*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_HHIHS);
					f -= (float)_hoops_HHIHS * scale;
				}
				_hoops_RGGA ((scale *= 0.1f) < 0.99f /* 1 */);

				if (f > _hoops_PHIHS || _hoops_AHIPI) {
					*_hoops_ASAPR++ = '.';
					scale = 0.1f;

					_hoops_PCCAR {
						_hoops_HHIHS = (int)(f / scale);
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_HHIHS);
						f -= _hoops_HHIHS * scale;
						scale *= 0.1f;
						if (f <= _hoops_PHIHS && (!_hoops_AHIPI || scale <= _hoops_PHIHS))
							break;
					}
				}

				if (_hoops_GRASR != 0) {
					*_hoops_ASAPR++ = 'e';
					if (_hoops_GRASR > 0)
						*_hoops_ASAPR++ = '+';
					else {
						*_hoops_ASAPR++ = '-';
						_hoops_GRASR = -_hoops_GRASR;
					}
					if (_hoops_GRASR >= 10) {
						_hoops_HHIHS = _hoops_GRASR / 10;
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_HHIHS);
						_hoops_GRASR -= _hoops_HHIHS*10;
					}
					*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_GRASR);
				}
			}	break;

			case 'd': {
				int		_hoops_AIIHS = *(int *)ptr;

				/* _hoops_SRGAI _hoops_IRS _hoops_AHIPP _hoops_CHIHS */

				if (sizeof(int) != sizeof(short)) {
					tmp = _hoops_AIIHS/1000000000;

					if (_hoops_ASAPR+11 > _hoops_PSAPR || tmp > 9 || tmp < -9)
						*_hoops_ASAPR++ = '?';
					else {
						if (_hoops_AIIHS < 0) {
							*_hoops_ASAPR++ = '-';
							_hoops_AIIHS = -_hoops_AIIHS;
							tmp = -tmp;
						}

						/* _hoops_RGR _hoops_HRGR _hoops_CHPCR! */
						if (_hoops_AIIHS > 999999999)
							*_hoops_ASAPR++ = _hoops_IAIHS(tmp);
						if (_hoops_AIIHS > 99999999)
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS/100000000 %10);
						if (_hoops_AIIHS > 9999999)
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS/10000000 % 10);
						if (_hoops_AIIHS > 999999)
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS/1000000 % 10);
						if (_hoops_AIIHS > 99999)
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS/100000 % 10);
						if (_hoops_AIIHS > 9999)
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS/10000 % 10);
						if (_hoops_AIIHS > 999)
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS/1000 % 10);
						if (_hoops_AIIHS > 99)
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS/100 % 10);
						if (_hoops_AIIHS > 9)
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS/10 % 10);
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS % 10);
					}
				}
				else /* _hoops_RPP (_hoops_GGHSP(_hoops_SCSH) == _hoops_GGHSP(_hoops_ICHRR)) */ {
					tmp = _hoops_AIIHS/10000;

					if (_hoops_ASAPR+6 > _hoops_PSAPR || tmp > 9 || tmp < -9)
						*_hoops_ASAPR++ = '?';
					else {
						if (_hoops_AIIHS < 0) {
							*_hoops_ASAPR++ = '-';
							_hoops_AIIHS = -_hoops_AIIHS;
							tmp = -tmp;
						}

						/* _hoops_RGR _hoops_HRGR _hoops_CHPCR! */
						if (_hoops_AIIHS > 9999)
							*_hoops_ASAPR++ = _hoops_IAIHS(tmp);
						if (_hoops_AIIHS > 999)
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS/1000 % 10);
						if (_hoops_AIIHS > 99)
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS/100 % 10);
						if (_hoops_AIIHS > 9)
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS/10 % 10);
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_AIIHS % 10);
					}
				}
			}	break;


			case 'D': {
				long			_hoops_PIIHS = *(long *)ptr;

				/* _hoops_SRGAI _hoops_IRS _hoops_RGRRR _hoops_AHIPP _hoops_CHIHS */


				if (_hoops_PSAPR - _hoops_ASAPR < (sizeof(unsigned long) == 8 ? 20 : 11))
					*_hoops_ASAPR++ = '?';
				else {
					bool _hoops_HIIHS = false;

					if (_hoops_PIIHS < 0) {
						*_hoops_ASAPR++ = '-';
						_hoops_PIIHS = -_hoops_PIIHS;
					}

					if (sizeof(unsigned long) == 8) {
						/* _hoops_IIIHS _hoops_CIIHS (_hoops_SHH _hoops_RHRIR _hoops_HAR _hoops_IS _hoops_PCHRA _hoops_GII
						 * _hoops_GRASP _hoops_A _hoops_SGS _hoops_SIAS _hoops_HAR _hoops_SHH _hoops_RPRI _hoops_GPP
						 * _hoops_RII _hoops_IACAR.)
						 */

						/* _hoops_RAH _hoops_RH _hoops_CASH _hoops_ARIP _hoops_SRS. */
						_hoops_PIIHS = _hoops_PIIHS/1000000000L;
						if (_hoops_PIIHS != 0) {
							_hoops_HIIHS = true;
							if (_hoops_PIIHS > 999999999L)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000000000L % 10);
							if (_hoops_PIIHS > 99999999L)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100000000L % 10);
							if (_hoops_PIIHS > 9999999L)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10000000L % 10);
							if (_hoops_PIIHS > 999999L)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000000L % 10);
							if (_hoops_PIIHS > 99999L)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100000L % 10);
							if (_hoops_PIIHS > 9999L)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10000L % 10);
							if (_hoops_PIIHS > 999L)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000L % 10);
							if (_hoops_PIIHS > 99L)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100L % 10);
							if (_hoops_PIIHS > 9L)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10L % 10);
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS % 10);
						}

						/* _hoops_SSAP, _hoops_PPR _hoops_RAHIP _hoops_CRGR _hoops_GHGA _hoops_HISAR _hoops_ARIP. */
						_hoops_PIIHS = *(long *)ptr;
						if (_hoops_PIIHS < 0)
							_hoops_PIIHS = -_hoops_PIIHS; /* _hoops_GAR _hoops_ARRS */
						_hoops_PIIHS %= 1000000000L;
					}

					/* _hoops_RGR _hoops_HRGR _hoops_CHPCR! */
					if (sizeof(unsigned long) != 8)
						if (_hoops_HIIHS || _hoops_PIIHS > 999999999L)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000000000L % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 99999999L)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100000000L % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 9999999L)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10000000L % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 999999L)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000000L % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 99999L)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100000L % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 9999L)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10000L % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 999L)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000L % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 99L)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100L % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 9L)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10L % 10);
					*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS % 10);
				}
			}	break;

			case 'P': {
				unsigned POINTER_SIZED_INT		_hoops_PIIHS = *(unsigned POINTER_SIZED_INT *)ptr;

				/* _hoops_SRGAI _hoops_PCCP _hoops_APPC _hoops_RGRRR _hoops_AHIPP _hoops_CHIHS */


				if (_hoops_PSAPR - _hoops_ASAPR < (sizeof(unsigned POINTER_SIZED_INT) == 8 ? 20 : 11))
					*_hoops_ASAPR++ = '?';
				else {
					bool _hoops_HIIHS = false;

					if (sizeof(unsigned POINTER_SIZED_INT) == 8) {
						/* _hoops_IIIHS _hoops_CIIHS (_hoops_SHH _hoops_RHRIR _hoops_HAR _hoops_IS _hoops_PCHRA _hoops_GII
						 * _hoops_GRASP _hoops_A _hoops_SGS _hoops_SIAS _hoops_HAR _hoops_SHH _hoops_RPRI _hoops_GPP
						 * _hoops_RII _hoops_IACAR.)
						 */

						/* _hoops_RAH _hoops_RH _hoops_CASH _hoops_ARIP _hoops_SRS. */
						_hoops_PIIHS = _hoops_PIIHS/1000000000UL;
						if (_hoops_PIIHS != 0) {
							_hoops_HIIHS = true;
							if (_hoops_PIIHS > 999999999UL)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000000000UL % 10);
							if (_hoops_PIIHS > 99999999UL)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100000000UL % 10);
							if (_hoops_PIIHS > 9999999UL)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10000000UL % 10);
							if (_hoops_PIIHS > 999999UL)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000000UL % 10);
							if (_hoops_PIIHS > 99999UL)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100000UL % 10);
							if (_hoops_PIIHS > 9999UL)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10000UL % 10);
							if (_hoops_PIIHS > 999UL)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000UL % 10);
							if (_hoops_PIIHS > 99UL)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100UL % 10);
							if (_hoops_PIIHS > 9UL)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10UL % 10);
							*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS % 10);
						}

						/* _hoops_SSAP, _hoops_PPR _hoops_RAHIP _hoops_CRGR _hoops_GHGA _hoops_HISAR _hoops_ARIP. */
						_hoops_PIIHS = *(unsigned POINTER_SIZED_INT *)ptr;
						_hoops_PIIHS %= 1000000000UL;
					}

					/* _hoops_RGR _hoops_HRGR _hoops_CHPCR! */
					if (sizeof(unsigned POINTER_SIZED_INT) != 8)
						if (_hoops_HIIHS || _hoops_PIIHS > 999999999UL)
								*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000000000UL % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 99999999UL)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100000000UL % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 9999999UL)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10000000UL % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 999999UL)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000000UL % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 99999UL)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100000UL % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 9999UL)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10000UL % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 999UL)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/1000UL % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 99UL)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/100UL % 10);
					if (_hoops_HIIHS || _hoops_PIIHS > 9UL)
						*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS/10UL % 10);
					*_hoops_ASAPR++ = _hoops_IAIHS(_hoops_PIIHS % 10);
				}
			}	break;

			case 'x': {
				int		_hoops_AIIHS = *(int *)ptr;

				/* _hoops_SRGAI _hoops_IRS _hoops_ACCAI _hoops_CHIHS (4 _hoops_SIIHS _hoops_RGAR) */

				*_hoops_ASAPR++ = '0';
				*_hoops_ASAPR++ = 'x';
				*_hoops_ASAPR++ = _hoops_AHIHS[(_hoops_AIIHS>>12) & 0xF];
				*_hoops_ASAPR++ = _hoops_AHIHS[(_hoops_AIIHS>> 8) & 0xF];
				*_hoops_ASAPR++ = _hoops_AHIHS[(_hoops_AIIHS>> 4) & 0xF];
				*_hoops_ASAPR++ = _hoops_AHIHS[(_hoops_AIIHS	  ) & 0xF];
			}	break;

			case 'o': {
				int		_hoops_AIIHS = *(int *)ptr;

				/* _hoops_SRGAI _hoops_IRS _hoops_CHSRS _hoops_CHIHS (2 _hoops_GCSRR _hoops_RGAR) */

				*_hoops_ASAPR++ = '0';
				*_hoops_ASAPR++ = _hoops_AHIHS[(_hoops_AIIHS>>15) & 01];
				*_hoops_ASAPR++ = _hoops_AHIHS[(_hoops_AIIHS>>12) & 07];
				*_hoops_ASAPR++ = _hoops_AHIHS[(_hoops_AIIHS>> 9) & 07];
				*_hoops_ASAPR++ = _hoops_AHIHS[(_hoops_AIIHS>> 6) & 07];
				*_hoops_ASAPR++ = _hoops_AHIHS[(_hoops_AIIHS>> 3) & 07];
				*_hoops_ASAPR++ = _hoops_AHIHS[(_hoops_AIIHS	  ) & 07];
			}	break;

			case 's': {
				/* _hoops_SRGAI _hoops_IRS _hoops_GSSR _hoops_IHRPR _hoops_AHHR-_hoops_CCGAI _hoops_GSGR */

				if (ptr != null) {
					char			*_hoops_GARIP = (char *)ptr;

					_hoops_RGGA (*_hoops_GARIP == '\0') {
						if (_hoops_ASAPR == _hoops_PSAPR)
							return null;
						*_hoops_ASAPR++ = *_hoops_GARIP++;
					}
				}
			}	break;

			case 'S': {
				/* _hoops_SRGAI _hoops_IRS _hoops_CGIGI _hoops_IHRPR _hoops_AHHR-_hoops_CCGAI _hoops_GSGR */

				if (ptr != null) {
					char			*_hoops_GARIP = (char *)ptr;

					*_hoops_ASAPR++ = '"';

					_hoops_RGGA (*_hoops_GARIP == '\0') {
						if (_hoops_ASAPR == _hoops_PSAPR)
							return null;
						if (*_hoops_GARIP == '"' || *_hoops_GARIP == '\\') {
							*_hoops_ASAPR++ = '\\';
							if (_hoops_ASAPR == _hoops_PSAPR)
								return null;
						}
						*_hoops_ASAPR++ = *_hoops_GARIP++;
					}

					*_hoops_ASAPR++ = '"';
				}
			}	break;

			case 'n': {
				/* _hoops_SRGAI _hoops_IRS _hoops_AGAH "_hoops_RSIRR" */
				_hoops_HCRPR _hoops_CPSGI;
				HI_Decode_User_Option(*(_hoops_HCRPR *)ptr, _hoops_CPSGI);

				if (_hoops_CPSGI.length > 0) {
					char			*_hoops_GARIP = _hoops_CPSGI.text;
					int				len = _hoops_CPSGI.length;

					if (len > _hoops_PSAPR - _hoops_ASAPR)
						return null;

					do *_hoops_ASAPR++ = *_hoops_GARIP++;
					_hoops_RGGA (--len == 0);
				}
				_hoops_RGAIR(_hoops_CPSGI);
			}	break;

			case 'N': {
				/* _hoops_SRGAI _hoops_IRS _hoops_AGAH "_hoops_RSIRR", _hoops_GAAP _hoops_CGIGI, _hoops_GCIHS _hoops_GRH */
				/* _hoops_CIGII _hoops_IGI _hoops_IH _hoops_CAGH _hoops_RPPCR */
				_hoops_HCRPR _hoops_CPSGI;
				HI_Decode_User_Option(*(_hoops_HCRPR *)ptr, _hoops_CPSGI);

				if (_hoops_CPSGI.length > 0) {
					char			*_hoops_GARIP = _hoops_CPSGI.text;
					int				len = _hoops_CPSGI.length;
					bool		_hoops_AGRI;

					if (len > _hoops_PSAPR - _hoops_ASAPR)
						return null;	/* _hoops_ICSI _hoops_ISPR */

					_hoops_AGRI = _hoops_GPIHS (&_hoops_CPSGI, true, false);

					if (_hoops_AGRI)
						*_hoops_ASAPR++ = '`';
					do {
						if (*_hoops_GARIP == '`' && _hoops_AGRI) {
							if (_hoops_ASAPR == _hoops_PSAPR)
								return null;
							*_hoops_ASAPR++ = '`';
						}
						if (_hoops_ASAPR == _hoops_PSAPR)
							return null;
						*_hoops_ASAPR++ = *_hoops_GARIP++;
					} _hoops_RGGA (--len == 0);

					if (_hoops_AGRI) {
						if (_hoops_ASAPR == _hoops_PSAPR)
							return null;
						*_hoops_ASAPR++ = '`';
					}
				}

				_hoops_RGAIR(_hoops_CPSGI);
			}	break;

			case 'X':
			case 'k': {
				POINTER_SIZED_INT  key = (POINTER_SIZED_INT)*(Key *)ptr;

				if (sizeof(Key) != sizeof(void *))
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									   "Bad Key/long assumption");

				if (_hoops_PSAPR - _hoops_ASAPR < (sizeof(Key) == 8 ? 17 : 9)) {
					return null;
				}
				else {
					bool _hoops_HIIHS = false;

					if (spec[-1] == 'k')
						*_hoops_ASAPR++ = '@';

					if (sizeof(Key) == 8) {
						/* _hoops_IIIHS _hoops_CIIHS (_hoops_SHH _hoops_RHRIR _hoops_HAR _hoops_IS _hoops_PCHRA _hoops_GII
						 * _hoops_GRASP _hoops_A _hoops_SGS _hoops_SIAS _hoops_HAR _hoops_SHH _hoops_RPRI _hoops_GPP
						 * _hoops_RII _hoops_IACAR.)
						 */

						/* _hoops_RAH _hoops_RH _hoops_CASH _hoops_ARIP _hoops_SRS. (_hoops_PARRH _hoops_RRPC _hoops_IS _hoops_SRCH _hoops_RCIHS _hoops_GCHH) */
						key >>= 16;
						key >>= 16;
						if (key != 0)
							_hoops_HIIHS = true;
						if (key & 0xF0000000)
							*_hoops_ASAPR++ = _hoops_AHIHS[(key>>28) & 0xF];
						if (key & 0xFF000000)
							*_hoops_ASAPR++ = _hoops_AHIHS[(key>>24) & 0xF];
						if (key & 0xFFF00000)
							*_hoops_ASAPR++ = _hoops_AHIHS[(key>>20) & 0xF];
						if (key & 0xFFFF0000)
							*_hoops_ASAPR++ = _hoops_AHIHS[(key>>16) & 0xF];
						if (key & 0xFFFFF000)
							*_hoops_ASAPR++ = _hoops_AHIHS[(key>>12) & 0xF];
						if (key & 0xFFFFFF00)
							*_hoops_ASAPR++ = _hoops_AHIHS[(key>> 8) & 0xF];
						if (key & 0xFFFFFFF0)
							*_hoops_ASAPR++ = _hoops_AHIHS[(key>> 4) & 0xF];
						if (key != 0)
							*_hoops_ASAPR++ = _hoops_AHIHS[(key	) & 0xF];

						/* _hoops_SSAP, _hoops_PPR _hoops_RAHIP _hoops_CRGR _hoops_GHGA _hoops_HISAR _hoops_ARIP. */
						key = (POINTER_SIZED_INT)*(Key *)ptr;
					}

					if (_hoops_HIIHS || (key & 0xF0000000))
						*_hoops_ASAPR++ = _hoops_AHIHS[(key>>28) & 0xF];
					if (_hoops_HIIHS || (key & 0xFF000000))
						*_hoops_ASAPR++ = _hoops_AHIHS[(key>>24) & 0xF];
					if (_hoops_HIIHS || (key & 0xFFF00000))
						*_hoops_ASAPR++ = _hoops_AHIHS[(key>>20) & 0xF];
					if (_hoops_HIIHS || (key & 0xFFFF0000))
						*_hoops_ASAPR++ = _hoops_AHIHS[(key>>16) & 0xF];
					if (_hoops_HIIHS || (key & 0xFFFFF000))
						*_hoops_ASAPR++ = _hoops_AHIHS[(key>>12) & 0xF];
					if (_hoops_HIIHS || (key & 0xFFFFFF00))
						*_hoops_ASAPR++ = _hoops_AHIHS[(key>> 8) & 0xF];
					if (_hoops_HIIHS || (key & 0xFFFFFFF0))
						*_hoops_ASAPR++ = _hoops_AHIHS[(key>> 4) & 0xF];
					*_hoops_ASAPR++ = _hoops_AHIHS[key & 0xF];
				}
			}	break;

			case 'q': {
				switch (*spec++) {
					case 's': {
						/* _hoops_SRGAI _hoops_IRS _hoops_IHRPR _hoops_AHHR-_hoops_CCGAI _hoops_GSGR, _hoops_GAAP _hoops_CGIGI */

						if (ptr != null) {
							char			*_hoops_GARIP = (char *)ptr;
							bool		_hoops_AGRI;

							_hoops_AGRI = _hoops_CAIHS (_hoops_GARIP);

							if (_hoops_AGRI)
								*_hoops_ASAPR++ = '`';
							_hoops_RGGA (*_hoops_GARIP == '\0') {
								if (*_hoops_GARIP == '`' && _hoops_AGRI) {
									if (_hoops_ASAPR == _hoops_PSAPR)
										return null;
									*_hoops_ASAPR++ = '`';
								}
								if (_hoops_ASAPR == _hoops_PSAPR)
									return null;
								*_hoops_ASAPR++ = *_hoops_GARIP++;
							}
							if (_hoops_AGRI) {
								if (_hoops_ASAPR == _hoops_PSAPR)
									return null;
								*_hoops_ASAPR++ = '`';
							}
						}
					}	break;

					case 'n': {
						/* _hoops_SRGAI _hoops_IRS _hoops_AGAH "_hoops_RSIRR", _hoops_GAAP _hoops_CGIGI */
						_hoops_HCRPR _hoops_CPSGI;
						HI_Decode_User_Option(*(_hoops_HCRPR *)ptr, _hoops_CPSGI);

						if (_hoops_CPSGI.length > 0) {
							char			*_hoops_GARIP = _hoops_CPSGI.text;
							int				len = _hoops_CPSGI.length;
							bool		_hoops_AGRI;

							if (len > _hoops_PSAPR - _hoops_ASAPR)
								return null;	/* _hoops_ICSI _hoops_ISPR */

							_hoops_AGRI = _hoops_GPIHS (&_hoops_CPSGI, false, false);

							if (_hoops_AGRI)
								*_hoops_ASAPR++ = '`';
							do {
								if (*_hoops_GARIP == '`' && _hoops_AGRI) {
									if (_hoops_ASAPR == _hoops_PSAPR)
										return null;
									*_hoops_ASAPR++ = '`';
								}
								if (_hoops_ASAPR == _hoops_PSAPR)
									return null;
								*_hoops_ASAPR++ = *_hoops_GARIP++;
							} _hoops_RGGA (--len == 0);

							if (_hoops_AGRI) {
								if (_hoops_ASAPR == _hoops_PSAPR)
									return null;
								*_hoops_ASAPR++ = '`';
							}
						}
						_hoops_RGAIR(_hoops_CPSGI);
					}	break;
				}
			}	break;

			case 'Q': {	// _hoops_AARHA?
				switch (*spec++) {
					case 'n': {
						/* _hoops_SRGAI _hoops_IRS _hoops_AGAH "_hoops_RSIRR", _hoops_GAAP _hoops_CGIGI */
						_hoops_HCRPR _hoops_CPSGI;
						HI_Decode_User_Option(*(_hoops_HCRPR *)ptr, _hoops_CPSGI);

						if (_hoops_CPSGI.length > 0) {
							char			*_hoops_GARIP = _hoops_CPSGI.text;
							int				len = _hoops_CPSGI.length;
							bool		_hoops_AGRI;

							if (len > _hoops_PSAPR - _hoops_ASAPR)
								return null;	/* _hoops_ICSI _hoops_ISPR */

							_hoops_AGRI = _hoops_GPIHS (&_hoops_CPSGI, false, true);

							if (_hoops_AGRI)
								*_hoops_ASAPR++ = '`';
							do {
								if (*_hoops_GARIP == '`' && _hoops_AGRI) {
									if (_hoops_ASAPR == _hoops_PSAPR)
										return null;
									*_hoops_ASAPR++ = '`';
								}
								if (_hoops_ASAPR == _hoops_PSAPR)
									return null;
								*_hoops_ASAPR++ = *_hoops_GARIP++;
							} _hoops_RGGA (--len == 0);

							if (_hoops_AGRI) {
								if (_hoops_ASAPR == _hoops_PSAPR)
									return null;
								*_hoops_ASAPR++ = '`';
							}
						}
						_hoops_RGAIR(_hoops_CPSGI);
					}	break;
				}
			}	break;

			case 'p': {
				/* _hoops_SRGAI _hoops_IRS _hoops_CRAA _hoops_SGS _hoops_RPPCR _hoops_IRS _hoops_CAGH */

				_hoops_CRCP				*prev = (_hoops_CRCP *)ptr;

				if (BIT (prev->_hoops_PHSI, _hoops_PRSIR)) {
					while (prev->owner->type == _hoops_IRCP &&
									BIT (prev->owner->_hoops_PHSI, _hoops_PRSIR))
						prev = prev->owner;

					ptr = (void *)prev;
				}

				if (prev->owner->type == _hoops_PRAIR) {		/* _hoops_HPGR _hoops_RH _hoops_SRRPR! */
					if (_hoops_ASAPR == _hoops_PSAPR)
						return null;
					*_hoops_ASAPR++ = '/';
					break;
				}

				while (prev->owner->type == _hoops_IRCP)
					prev = prev->owner;

				if (prev->owner->type == _hoops_PIRIR) {
					prev = prev->owner;
					if (_hoops_ASAPR == _hoops_PSAPR)
						return null;
					*_hoops_ASAPR++ = '/';
				}

				do {
					_hoops_CRCP				*_hoops_SRCP = (_hoops_CRCP *)ptr;

					_hoops_RGGA (_hoops_SRCP->owner == prev) _hoops_SRCP = _hoops_SRCP->owner;

					if (_hoops_ASAPR == _hoops_PSAPR)
						return null;
					*_hoops_ASAPR++ = '/';

					if (_hoops_SRCP->name.length == 0) {
						POINTER_SIZED_INT	key = _hoops_SRCP->key;

						/* _hoops_SRGAI _hoops_IRS _hoops_ACCAI _hoops_CHIHS (8 _hoops_PAR 16 _hoops_SIIHS _hoops_RGAR) */

						if (_hoops_PSAPR - _hoops_ASAPR < (sizeof(POINTER_SIZED_INT) == 8 ? 17 : 9)) {
							return null;
						}
						else {
							bool _hoops_ACIHS = false;
							if (sizeof(Key) != sizeof(void *))
								_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
												   "Bad Key/long assumption");

							*_hoops_ASAPR++ = '@';

							if (sizeof(Key) == 8) {
								/* _hoops_IIIHS _hoops_CIIHS (_hoops_SHH _hoops_RHRIR _hoops_HAR _hoops_IS _hoops_PCHRA _hoops_GII
								 * _hoops_GRASP _hoops_A _hoops_SGS _hoops_SIAS _hoops_HAR _hoops_SHH _hoops_RPRI _hoops_GPP
								 * _hoops_RII _hoops_IACAR.)
								 */

								/* _hoops_RAH _hoops_RH _hoops_CASH _hoops_ARIP _hoops_SRS. (_hoops_PARRH _hoops_RRPC _hoops_IS _hoops_SRCH _hoops_RCIHS _hoops_GCHH) */
								key >>= 16;
								key >>= 16;
								if (key != 0)
									_hoops_ACIHS = true;
								if (key & 0xF0000000)
									*_hoops_ASAPR++ = _hoops_AHIHS[(key>>28) & 0xF];
								if (key & 0xFF000000)
									*_hoops_ASAPR++ = _hoops_AHIHS[(key>>24) & 0xF];
								if (key & 0xFFF00000)
									*_hoops_ASAPR++ = _hoops_AHIHS[(key>>20) & 0xF];
								if (key & 0xFFFF0000)
									*_hoops_ASAPR++ = _hoops_AHIHS[(key>>16) & 0xF];
								if (key & 0xFFFFF000)
									*_hoops_ASAPR++ = _hoops_AHIHS[(key>>12) & 0xF];
								if (key & 0xFFFFFF00)
									*_hoops_ASAPR++ = _hoops_AHIHS[(key>> 8) & 0xF];
								if (key & 0xFFFFFFF0)
									*_hoops_ASAPR++ = _hoops_AHIHS[(key>> 4) & 0xF];
								if (key != 0)
									*_hoops_ASAPR++ = _hoops_AHIHS[(key	) & 0xF];

								/* _hoops_SSAP, _hoops_PPR _hoops_RAHIP _hoops_CRGR _hoops_GHGA _hoops_HISAR _hoops_ARIP. */
								key = (POINTER_SIZED_INT) _hoops_SRCP->key;
							}

							if (_hoops_ACIHS || (key & 0xF0000000))
								*_hoops_ASAPR++ = _hoops_AHIHS[(key>>28) & 0xF];
							if (_hoops_ACIHS || (key & 0xFF000000))
								*_hoops_ASAPR++ = _hoops_AHIHS[(key>>24) & 0xF];
							if (_hoops_ACIHS || (key & 0xFFF00000))
								*_hoops_ASAPR++ = _hoops_AHIHS[(key>>20) & 0xF];
							if (_hoops_ACIHS || (key & 0xFFFF0000))
								*_hoops_ASAPR++ = _hoops_AHIHS[(key>>16) & 0xF];
							if (_hoops_ACIHS || (key & 0xFFFFF000))
								*_hoops_ASAPR++ = _hoops_AHIHS[(key>>12) & 0xF];
							if (_hoops_ACIHS || (key & 0xFFFFFF00))
								*_hoops_ASAPR++ = _hoops_AHIHS[(key>> 8) & 0xF];
							if (_hoops_ACIHS || (key & 0xFFFFFFF0))
								*_hoops_ASAPR++ = _hoops_AHIHS[(key>> 4) & 0xF];
							*_hoops_ASAPR++ = _hoops_AHIHS[key & 0xF];
						}
					}
					else {
						char			*_hoops_GARIP = _hoops_SRCP->name.text;
						int				len = _hoops_SRCP->name.length;
						bool		_hoops_AGRI;

						if (len > _hoops_PSAPR - _hoops_ASAPR)
							return null;		/* _hoops_ICSI _hoops_ISPR */

						_hoops_AGRI = _hoops_GPIHS (&_hoops_SRCP->name, true, false);

						if (_hoops_AGRI)
							*_hoops_ASAPR++ = '`';
						do {
							if (*_hoops_GARIP == '`' && _hoops_AGRI) {
								if (_hoops_ASAPR == _hoops_PSAPR)
									return null;
								*_hoops_ASAPR++ = '`';
							}
							if (_hoops_ASAPR == _hoops_PSAPR)
								return null;
							*_hoops_ASAPR++ = *_hoops_GARIP++;
						} _hoops_RGGA (--len == 0);

						if (_hoops_AGRI) {
							if (_hoops_ASAPR == _hoops_PSAPR)
								return null;
							*_hoops_ASAPR++ = '`';
						}
					}
					prev = _hoops_SRCP;
				}
				_hoops_RGGA (prev == (_hoops_CRCP *)ptr);
			}	break;

			case '%': {
				if (_hoops_ASAPR == _hoops_PSAPR)
					return null;
				*_hoops_ASAPR++ = '%';
			}	break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "Bad argument to Sprintf1");
				return null;
			}	/*_hoops_IHSA;*/
		}
	}

	return _hoops_ASAPR;
}



GLOBAL_FUNCTION char * HI_Sprintf4 (
	_hoops_AIGPR *	_hoops_RIGC,
	char *					buf,
	char const *			spec,
	int						_hoops_CPIPP,
	int						_hoops_SPIPP,
	void const *			_hoops_AIPPA,
	void const *			_hoops_PIPPA) {
	void const *			_hoops_PCIHS = _hoops_AIPPA;
	int						_hoops_AIIHS = _hoops_CPIPP;
	char					format[8];

	/* _hoops_SGH _hoops_IPHR _hoops_CRPR _hoops_HRII _hoops_HSAR '_hoops_GHHPI' _hoops_SSPP _hoops_GGR _hoops_AGIR _hoops_RH _hoops_CIIA
	 * _hoops_SGRRA '_hoops_GHHPI'.*/

	char					_hoops_RHSPR[_hoops_CGHHP];
	char *					_hoops_ASAPR = _hoops_RHSPR;
	char *					_hoops_PSAPR = &_hoops_RHSPR[_hoops_CGHHP-1];
	char *					_hoops_HCIHS;
	
	if (buf == null) {
		if (_hoops_RIGC == null)
			_hoops_IIRIR (_hoops_RIGC);
		_hoops_ASAPR = _hoops_RIGC->_hoops_RIPGI;
		_hoops_PSAPR = _hoops_ASAPR + _hoops_CGHHP - 1;
	}

	format[0] = '%';

	do if (*spec != '%') *_hoops_ASAPR++ = *spec++;
	else switch (*++spec) {
		case '%': {
			*_hoops_ASAPR++ = *spec++;
		}	break;


		case 'd':
		case 'x':
		case 'o': {
			format[1] = *spec++;
			format[2] = '\0';

			if ((_hoops_HCIHS = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, format, &_hoops_AIIHS)) != null)
				_hoops_ASAPR = _hoops_HCIHS;
			else
				*_hoops_ASAPR++ = '?';

			_hoops_AIIHS = _hoops_SPIPP;
		}	break;

		case 'D':
		case 'P':
		case 'X':
		case 'F':
		case 'f':
		case 's':
		case 'S':
		case 'n':
		case 'k':
		case 'p': {
			format[1] = *spec++;
			format[2] = '\0';

			if ((_hoops_HCIHS = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, format, _hoops_PCIHS)) != null)
				_hoops_ASAPR = _hoops_HCIHS;
			else
				*_hoops_ASAPR++ = '?';

			_hoops_PCIHS = _hoops_PIPPA;
		}	break;

		case 'q': {
			format[1] = *spec++;		/* _hoops_ARHHI */
			format[2] = *spec++;		/* _hoops_GRI|_hoops_ACHP */
			format[3] = '\0';

			if ((_hoops_HCIHS = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, format, _hoops_PCIHS)) != null)
				_hoops_ASAPR = _hoops_HCIHS;
			else
				*_hoops_ASAPR++ = '?';

			_hoops_PCIHS = _hoops_PIPPA;
		}	break;

		case '.': {
			format[1] = *spec++;		/* . */
			format[2] = *spec++;		/* # */
			format[3] = *spec++;		/* _hoops_RCHP */
			format[4] = '\0';

			if ((_hoops_HCIHS = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, format, _hoops_PCIHS)) != null)
				_hoops_ASAPR = _hoops_HCIHS;
			else
				*_hoops_ASAPR++ = '?';

			_hoops_PCIHS = _hoops_PIPPA;
		}	break;


		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Bad argument to Sprintf4");
			return null;
		}		/*_hoops_IHSA;*/
	}
	_hoops_RGGA (*spec == '\0' || _hoops_ASAPR == _hoops_PSAPR);

	*_hoops_ASAPR++ = '\0';

	if (buf == null)
		return _hoops_RIGC->_hoops_RIPGI;
	else {
		/* _hoops_IPS _hoops_GCHRR _hoops_IS _hoops_HPHR _hoops_IIPR (_hoops_RGR _hoops_IHIGR _hoops_PSCA _hoops_IS _hoops_RSSAI) */

		spec = _hoops_RHSPR;
		_hoops_ASAPR = buf;
		do {} _hoops_RGGA ((*_hoops_ASAPR++ = *spec++) == '\0');

		return buf;
	}
}

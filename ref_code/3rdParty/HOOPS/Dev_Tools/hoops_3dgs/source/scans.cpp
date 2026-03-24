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
 * $Id: obf_tmp.txt 1.46 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "hi_proto.h"


#ifdef _hoops_RCRCC
#include <stdio.h>
static FILE * f=NULL;
#endif

GLOBAL_FUNCTION char const * HI_Scan_Name (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA,	/* _hoops_ASPR _hoops_IS _hoops_ASPR _hoops_IS _hoops_GSGR (_hoops_SRSS) */
	char const *			_hoops_SSRPR,	/* _hoops_ASPR _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_GSGR (_hoops_IRIGR) */
	_hoops_HCRPR *					name)	/* _hoops_ASPR _hoops_IS _hoops_GHPP (_hoops_PHPH) */
{ 
	char const		*_hoops_RPPA = *_hoops_RAARA;
	char			*_hoops_PCRCC;
	int				length = 0;
	char const		*_hoops_HCRCC;
	char const		*_hoops_ICRCC;
	local		char const		_hoops_AIHGC[] =
		"Illegal character found, or expected name/string not found";
	
	/* _hoops_IGHHH: _hoops_IPRCC _hoops_RHIPP _hoops_GHCA _hoops_SHH _hoops_PGI 0-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS
	 * _hoops_SHH _hoops_IRAP) _hoops_PAR _hoops_SPCC-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS _hoops_SHH _hoops_GRAA-_hoops_IRAP). _hoops_SPRCC
	 * _hoops_IH _hoops_GHRCC _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_IPHR _hoops_GGSR _hoops_GPRS _hoops_GGR _hoops_PGI _hoops_AGIR; _hoops_PCGC _hoops_IH
	 * _hoops_PACAR _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_RRP _hoops_IS _hoops_SRS _hoops_ISPR _hoops_IH _hoops_CCRCC _hoops_IHGS _hoops_GRAA-_hoops_IRAP.
	 */

#ifdef _hoops_RCRCC
	if (f == NULL)
		f = fopen("scan.txt", "w+");

	if (_hoops_SSRPR) {	
		int i;
		for (i=0; i<(_hoops_SSRPR - *_hoops_RAARA);i++)
			fprintf(f, "%c", *_hoops_RAARA[i]); 
		fprintf(f, "\n"); 
	}
	else
		fprintf(f, "%s\n", *_hoops_RAARA); 
#endif

	if (_hoops_SSRPR != null && _hoops_RPPA >= _hoops_SSRPR) return _hoops_AIHGC;

	while (*_hoops_RPPA == ' ') if (++_hoops_RPPA == _hoops_SSRPR) return _hoops_AIHGC;

	_hoops_HCRCC = _hoops_RPPA;

	/* ('%' _hoops_HRGR _hoops_HAR _hoops_IRS _hoops_HAIHH _hoops_RGAR _hoops_IH _hoops_RH _hoops_SSCPR _hoops_IIGR
	 *	_hoops_RH '_hoops_IGIR _hoops_AAHP' _hoops_HCGR _hoops_HRCSR _hoops_HCSP.)
	 */

	_hoops_RGGA (_hoops_RPPA == _hoops_SSRPR) switch (*_hoops_RPPA++) {
		default: {
			++length;
		}	break;

		case ',':
		case '(':
		case ')': case '\0': case '\n': case '=': { /* _hoops_RHRCC! */
		}		goto _hoops_PCPPR;


		case '"': case '`': case '\'': {
			char	_hoops_AHRCC = _hoops_RPPA[-1];

			_hoops_PCCAR {
				if (_hoops_RPPA == _hoops_SSRPR || *_hoops_RPPA == '\0') return "Unbalanced quote marks";

				if (*_hoops_RPPA++ != _hoops_AHRCC) ++length;
				else if (_hoops_RPPA != _hoops_SSRPR && *_hoops_RPPA == _hoops_AHRCC) ++length, ++_hoops_RPPA;
				else break;
			}
		}	break;
	}
	_hoops_RPPA++;		/* _hoops_CR _hoops_SR _hoops_PHRCC _hoops_HPP _hoops_HHRCC _hoops_RH _hoops_RSGR, _hoops_SPSRS _hoops_RH --_hoops_GSIPH _hoops_CAPP */

  _hoops_PCPPR:;

	/* _hoops_GASA: _hoops_RH _hoops_HSPR _hoops_PGCR _hoops_APGR _hoops_RSRHR _hoops_CHRCC _hoops_AHGSR _hoops_SGS _hoops_CHR _hoops_ICIC _hoops_IS _hoops_SSPC */
	_hoops_ICRCC = --_hoops_RPPA;
	while (length > 0 && *--_hoops_RPPA == ' ') --length;

	if (length == 0) {	/* _hoops_PIHA _hoops_HS _hoops_RPII _hoops_CGIGI _hoops_IRAP _hoops_GSGR */
		name->length = 0;
		name->text = null;
	}
	else {
		POOL_ALLOC_ARRAY (_hoops_PCRCC, length+1, char, _hoops_RIGC->memory_pool);
		name->length = length;
		name->text = _hoops_PCRCC;

		_hoops_RPPA = _hoops_HCRCC;

		do switch (_hoops_IRGCR(*_hoops_RPPA)) {

			default: {
				*_hoops_PCRCC++ = _hoops_SHPCR (*_hoops_RPPA), ++_hoops_RPPA;
			}	break;

			case '"': case '`': case '\'': {
				char	_hoops_AHRCC = *_hoops_RPPA++;

				_hoops_PCCAR {
					if (*_hoops_RPPA == _hoops_AHRCC) {
						if (*++_hoops_RPPA == _hoops_AHRCC) {
							/* _hoops_SRIII _hoops_RH _hoops_CISI _hoops_HPARA _hoops_IAHA _hoops_RIRPR _hoops_GAR _hoops_PCCP _hoops_PGPCR
							 * _hoops_ICPPR.  _hoops_PHGP "_hoops_CCGPH'_hoops_GRI _hoops_HH" _hoops_PAH _hoops_GACC _hoops_SHH _hoops_AIHCR
							 * _hoops_GAR '_hoops_CCGPH''_hoops_GRI _hoops_HH' */
							*_hoops_PCRCC++ = *_hoops_RPPA++;
							--length;
						}
						else break;
					}
					else {
						*_hoops_PCRCC++ = *_hoops_RPPA++;
						--length;
					}
				}
				++length;		/* (_hoops_GGSP _hoops_IHH --_hoops_SPCC _hoops_HPGR _hoops_RH _hoops_PRPC) */
			}	break;

			case ',':
			case '(':
			case ')': case '\0': case '\n': case '=': { /* _hoops_RHRCC! */
				_hoops_RGAIR (*name);
				return "Illegal character found - try more quote marks?";
			}	/*_hoops_IHSA;*/
		}
		_hoops_RGGA (--length <= 0);
		*_hoops_PCRCC = '\0';
	}

	*_hoops_RAARA = _hoops_ICRCC;
	return null;
}


GLOBAL_FUNCTION char const * HI_Scan_String (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA,	/* _hoops_ASPR _hoops_IS _hoops_ASPR _hoops_IS _hoops_GSGR (_hoops_SRSS) */
	char const *			_hoops_SSRPR,	/* _hoops_ASPR _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_GSGR (_hoops_IRIGR) */
	_hoops_HCRPR *					name)	/* _hoops_ASPR _hoops_IS _hoops_GHPP (_hoops_PHPH) */
{ 
	char const		*_hoops_RPPA = *_hoops_RAARA;
	char			*_hoops_PCRCC;
	int				length;

	/* _hoops_IGHHH: _hoops_IPRCC _hoops_RHIPP _hoops_GHCA _hoops_SHH _hoops_PGI 0-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS
	 * _hoops_SHH _hoops_IRAP) _hoops_PAR _hoops_SPCC-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS _hoops_SHH _hoops_GRAA-_hoops_IRAP). _hoops_SPRCC
	 * _hoops_IH _hoops_GHRCC _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_IPHR _hoops_GGSR _hoops_GPRS _hoops_GGR _hoops_PGI _hoops_AGIR; _hoops_PCGC _hoops_IH
	 * _hoops_PACAR _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_RRP _hoops_IS _hoops_SRS _hoops_ISPR _hoops_IH _hoops_CCRCC _hoops_IHGS _hoops_GRAA-_hoops_IRAP.
	 */

	_hoops_RGGA (_hoops_RPPA == _hoops_SSRPR || *_hoops_RPPA == '\0' || *_hoops_RPPA == ',' || *_hoops_RPPA == ')') ++_hoops_RPPA;

	if ((length = _hoops_RPPA - *_hoops_RAARA) == 0) {
		name->length = 0;
		name->text = null;
	}
	else {
		POOL_ALLOC_ARRAY (_hoops_PCRCC, length+1, char, _hoops_RIGC->memory_pool);
		name->length = length;
		name->text = _hoops_PCRCC;

		_hoops_RPPA = *_hoops_RAARA;

		do *_hoops_PCRCC++ = *_hoops_RPPA++;
		_hoops_RGGA (--length == 0);
		*_hoops_PCRCC = '\0';

		*_hoops_RAARA = _hoops_RPPA;
	}
	return null;
}



GLOBAL_FUNCTION char const * HI_Scan_Key (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA,	/* _hoops_ASPR _hoops_IS _hoops_ASPR _hoops_IS _hoops_GSGR (_hoops_SRSS) */
	char const *			_hoops_SSRPR,	/* _hoops_ASPR _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_GSGR (_hoops_IRIGR) */
	Key *					resultp)/* _hoops_ASPR _hoops_IS _hoops_GHPP (_hoops_PHPH) */
{
	UNREFERENCED(_hoops_RIGC);

	char const		*_hoops_RPPA = *_hoops_RAARA;
	Key			result = 0, _hoops_GHSRS;
	bool		_hoops_RHSRS = false;
	local		char const		_hoops_AIHGC[] = "Expected integer not found",
		_hoops_AHSRS[] = "Bad octal digit (8 or 9!)",
		_hoops_PHSRS[] = "Bad hex constant";

	/* _hoops_IGHHH: _hoops_IPRCC _hoops_RHIPP _hoops_GHCA _hoops_SHH _hoops_PGI 0-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS
	* _hoops_SHH _hoops_IRAP) _hoops_PAR _hoops_SPCC-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS _hoops_SHH _hoops_GRAA-_hoops_IRAP). _hoops_SPRCC
	* _hoops_IH _hoops_GHRCC _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_IPHR _hoops_GGSR _hoops_GPRS _hoops_GGR _hoops_PGI _hoops_AGIR; _hoops_PCGC _hoops_IH
	* _hoops_PACAR _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_RRP _hoops_IS _hoops_SRS _hoops_ISPR _hoops_IH _hoops_CCRCC _hoops_IHGS _hoops_GRAA-_hoops_IRAP.
	*/

	if (_hoops_SSRPR != null && _hoops_RPPA >= _hoops_SSRPR) return _hoops_AIHGC;

	while (*_hoops_RPPA == ' ') if (++_hoops_RPPA == _hoops_SSRPR) return _hoops_AIHGC;

	if (*_hoops_RPPA == '+' || *_hoops_RPPA == '-') {
		if (*_hoops_RPPA++ == '-') _hoops_RHSRS = true;
		if (_hoops_RPPA == _hoops_SSRPR) return _hoops_AIHGC;
	}

	if (*_hoops_RPPA != '0') {			/* _hoops_AHIPP */
		_hoops_GHSRS = 0;

		_hoops_PCCAR {
			switch (*_hoops_RPPA) {
			case '0':										break;
			case '1':		_hoops_GHSRS += 1;				break;
			case '2':		_hoops_GHSRS += 2;				break;
			case '3':		_hoops_GHSRS += 3;				break;
			case '4':		_hoops_GHSRS += 4;				break;
			case '5':		_hoops_GHSRS += 5;				break;
			case '6':		_hoops_GHSRS += 6;				break;
			case '7':		_hoops_GHSRS += 7;				break;
			case '8':		_hoops_GHSRS += 8;				break;
			case '9':		_hoops_GHSRS += 9;				break;
			default:		goto _hoops_HHSRS;
			}

			result = _hoops_GHSRS;
			if (++_hoops_RPPA == _hoops_SSRPR) break;
			_hoops_GHSRS *= 10;
		}

_hoops_HHSRS:;

		if (result == 0) return _hoops_AIHGC;
	}
	else if (++_hoops_RPPA == _hoops_SSRPR) {		/* _hoops_HHGPR _hoops_AHHR (_hoops_GRH _hoops_AGIR) */
	}
	else if (*_hoops_RPPA == 'x' || *_hoops_RPPA == 'X') {		/* _hoops_ACCAI */
		++_hoops_RPPA;
		_hoops_GHSRS = 0;

		_hoops_PCCAR {
			switch (*_hoops_RPPA) {
			case '0':										break;
			case '1':				_hoops_GHSRS += 1;		break;
			case '2':				_hoops_GHSRS += 2;		break;
			case '3':				_hoops_GHSRS += 3;		break;
			case '4':				_hoops_GHSRS += 4;		break;
			case '5':				_hoops_GHSRS += 5;		break;
			case '6':				_hoops_GHSRS += 6;		break;
			case '7':				_hoops_GHSRS += 7;		break;
			case '8':				_hoops_GHSRS += 8;		break;
			case '9':				_hoops_GHSRS += 9;		break;
			case 'a': case 'A':		_hoops_GHSRS += 10;		break;
			case 'b': case 'B':		_hoops_GHSRS += 11;		break;
			case 'c': case 'C':		_hoops_GHSRS += 12;		break;
			case 'd': case 'D':		_hoops_GHSRS += 13;		break;
			case 'e': case 'E':		_hoops_GHSRS += 14;		break;
			case 'f': case 'F':		_hoops_GHSRS += 15;		break;
			default:				goto _hoops_IHSRS;
			}

			result = _hoops_GHSRS;
			if (++_hoops_RPPA == _hoops_SSRPR) break;
			_hoops_GHSRS *= 16;
		}

_hoops_IHSRS:;

		if (*(_hoops_RPPA-1) == 'x' || *(_hoops_RPPA-1) == 'X') return _hoops_PHSRS;
	}
	else {						/* _hoops_CHSRS */
		_hoops_GHSRS = 0;

		_hoops_PCCAR {
			switch (*_hoops_RPPA) {
			case '0':										break;
			case '1':				_hoops_GHSRS += 1;		break;
			case '2':				_hoops_GHSRS += 2;		break;
			case '3':				_hoops_GHSRS += 3;		break;
			case '4':				_hoops_GHSRS += 4;		break;
			case '5':				_hoops_GHSRS += 5;		break;
			case '6':				_hoops_GHSRS += 6;		break;
			case '7':				_hoops_GHSRS += 7;		break;
			case '8': case '9':		return _hoops_AHSRS;
			default:				goto _hoops_SHSRS;
			}

			result = _hoops_GHSRS;
			if (++_hoops_RPPA == _hoops_SSRPR) break;
			_hoops_GHSRS *= 8;
		}

_hoops_SHSRS:;
	}

	if (_hoops_RHSRS)
		*resultp = -result; /* (_hoops_PIP: _hoops_GPGH'_hoops_RA _hoops_SSRR _hoops_IS _hoops_PGSAH _hoops_GPP _hoops_GISRS) */
	else
		*resultp = result;

	while (_hoops_RPPA != _hoops_SSRPR && *_hoops_RPPA == ' ') ++_hoops_RPPA;

	*_hoops_RAARA = _hoops_RPPA;
	return null;
}




GLOBAL_FUNCTION char const * HI_Scan_Long (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA,	/* _hoops_ASPR _hoops_IS _hoops_ASPR _hoops_IS _hoops_GSGR (_hoops_SRSS) */
	char const *			_hoops_SSRPR,	/* _hoops_ASPR _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_GSGR (_hoops_IRIGR) */
	long *					resultp)/* _hoops_ASPR _hoops_IS _hoops_GHPP (_hoops_PHPH) */
{
	UNREFERENCED(_hoops_RIGC);

	char const		*_hoops_RPPA = *_hoops_RAARA;
	long			result = 0,
								_hoops_GHSRS;
	bool		_hoops_RHSRS = false;
	local		char const		_hoops_AIHGC[] = "Expected integer not found",
								_hoops_AHSRS[] = "Bad octal digit (8 or 9!)",
								_hoops_PHSRS[] = "Bad hex constant";

	/* _hoops_IGHHH: _hoops_IPRCC _hoops_RHIPP _hoops_GHCA _hoops_SHH _hoops_PGI 0-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS
	 * _hoops_SHH _hoops_IRAP) _hoops_PAR _hoops_SPCC-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS _hoops_SHH _hoops_GRAA-_hoops_IRAP). _hoops_SPRCC
	 * _hoops_IH _hoops_GHRCC _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_IPHR _hoops_GGSR _hoops_GPRS _hoops_GGR _hoops_PGI _hoops_AGIR; _hoops_PCGC _hoops_IH
	 * _hoops_PACAR _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_RRP _hoops_IS _hoops_SRS _hoops_ISPR _hoops_IH _hoops_CCRCC _hoops_IHGS _hoops_GRAA-_hoops_IRAP.
	 */

	if (_hoops_SSRPR != null && _hoops_RPPA >= _hoops_SSRPR) return _hoops_AIHGC;

	while (*_hoops_RPPA == ' ') if (++_hoops_RPPA == _hoops_SSRPR) return _hoops_AIHGC;

	if (*_hoops_RPPA == '+' || *_hoops_RPPA == '-') {
		if (*_hoops_RPPA++ == '-') _hoops_RHSRS = true;
		if (_hoops_RPPA == _hoops_SSRPR) return _hoops_AIHGC;
	}

	if (*_hoops_RPPA != '0') {			/* _hoops_AHIPP */
		_hoops_GHSRS = 0;

		_hoops_PCCAR {
			switch (*_hoops_RPPA) {
				case '0':										break;
				case '1':		_hoops_GHSRS += 1;				break;
				case '2':		_hoops_GHSRS += 2;				break;
				case '3':		_hoops_GHSRS += 3;				break;
				case '4':		_hoops_GHSRS += 4;				break;
				case '5':		_hoops_GHSRS += 5;				break;
				case '6':		_hoops_GHSRS += 6;				break;
				case '7':		_hoops_GHSRS += 7;				break;
				case '8':		_hoops_GHSRS += 8;				break;
				case '9':		_hoops_GHSRS += 9;				break;
				default:		goto _hoops_HHSRS;
			}

			result = _hoops_GHSRS;
			if (++_hoops_RPPA == _hoops_SSRPR) break;
			_hoops_GHSRS *= 10;
		}

		_hoops_HHSRS:;

		if (result == 0) return _hoops_AIHGC;
	}
	else if (++_hoops_RPPA == _hoops_SSRPR) {		/* _hoops_HHGPR _hoops_AHHR (_hoops_GRH _hoops_AGIR) */
	}
	else if (*_hoops_RPPA == 'x' || *_hoops_RPPA == 'X') {		/* _hoops_ACCAI */
		++_hoops_RPPA;
		_hoops_GHSRS = 0;

		_hoops_PCCAR {
			switch (*_hoops_RPPA) {
				case '0':										break;
				case '1':				_hoops_GHSRS += 1;		break;
				case '2':				_hoops_GHSRS += 2;		break;
				case '3':				_hoops_GHSRS += 3;		break;
				case '4':				_hoops_GHSRS += 4;		break;
				case '5':				_hoops_GHSRS += 5;		break;
				case '6':				_hoops_GHSRS += 6;		break;
				case '7':				_hoops_GHSRS += 7;		break;
				case '8':				_hoops_GHSRS += 8;		break;
				case '9':				_hoops_GHSRS += 9;		break;
				case 'a': case 'A':		_hoops_GHSRS += 10;		break;
				case 'b': case 'B':		_hoops_GHSRS += 11;		break;
				case 'c': case 'C':		_hoops_GHSRS += 12;		break;
				case 'd': case 'D':		_hoops_GHSRS += 13;		break;
				case 'e': case 'E':		_hoops_GHSRS += 14;		break;
				case 'f': case 'F':		_hoops_GHSRS += 15;		break;
				default:				goto _hoops_IHSRS;
			}

			result = _hoops_GHSRS;
			if (++_hoops_RPPA == _hoops_SSRPR) break;
			_hoops_GHSRS *= 16;
		}

		_hoops_IHSRS:;

		if (*(_hoops_RPPA-1) == 'x' || *(_hoops_RPPA-1) == 'X') return _hoops_PHSRS;
	}
	else {						/* _hoops_CHSRS */
		_hoops_GHSRS = 0;

		_hoops_PCCAR {
			switch (*_hoops_RPPA) {
				case '0':										break;
				case '1':				_hoops_GHSRS += 1;		break;
				case '2':				_hoops_GHSRS += 2;		break;
				case '3':				_hoops_GHSRS += 3;		break;
				case '4':				_hoops_GHSRS += 4;		break;
				case '5':				_hoops_GHSRS += 5;		break;
				case '6':				_hoops_GHSRS += 6;		break;
				case '7':				_hoops_GHSRS += 7;		break;
				case '8': case '9':		return _hoops_AHSRS;
				default:				goto _hoops_SHSRS;
			}

			result = _hoops_GHSRS;
			if (++_hoops_RPPA == _hoops_SSRPR) break;
			_hoops_GHSRS *= 8;
		}

		_hoops_SHSRS:;
	}

	if (_hoops_RHSRS)
		*resultp = -result; /* (_hoops_PIP: _hoops_GPGH'_hoops_RA _hoops_SSRR _hoops_IS _hoops_PGSAH _hoops_GPP _hoops_GISRS) */
	else
		*resultp = result;

	while (_hoops_RPPA != _hoops_SSRPR && *_hoops_RPPA == ' ') ++_hoops_RPPA;

	*_hoops_RAARA = _hoops_RPPA;
	return null;
}



GLOBAL_FUNCTION char const * HI_Scan_Ptr (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA,	/* _hoops_ASPR _hoops_IS _hoops_ASPR _hoops_IS _hoops_GSGR (_hoops_SRSS) */
	char const *			_hoops_SSRPR,	/* _hoops_ASPR _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_GSGR (_hoops_IRIGR) */
	POINTER_SIZED_INT *		resultp)/* _hoops_ASPR _hoops_IS _hoops_GHPP (_hoops_PHPH) */
{
	UNREFERENCED(_hoops_RIGC);

	char const		*_hoops_RPPA = *_hoops_RAARA;
	POINTER_SIZED_INT result = 0,
								_hoops_GHSRS;
	bool		_hoops_RHSRS = false;
	local		char const		_hoops_AIHGC[] = "Expected integer not found",
								_hoops_AHSRS[] = "Bad octal digit (8 or 9!)",
								_hoops_PHSRS[] = "Bad hex constant";

	/* _hoops_IGHHH: _hoops_IPRCC _hoops_RHIPP _hoops_GHCA _hoops_SHH _hoops_PGI 0-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS
	 * _hoops_SHH _hoops_IRAP) _hoops_PAR _hoops_SPCC-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS _hoops_SHH _hoops_GRAA-_hoops_IRAP). _hoops_SPRCC
	 * _hoops_IH _hoops_GHRCC _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_IPHR _hoops_GGSR _hoops_GPRS _hoops_GGR _hoops_PGI _hoops_AGIR; _hoops_PCGC _hoops_IH
	 * _hoops_PACAR _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_RRP _hoops_IS _hoops_SRS _hoops_ISPR _hoops_IH _hoops_CCRCC _hoops_IHGS _hoops_GRAA-_hoops_IRAP.
	 */

	if (_hoops_SSRPR != null && _hoops_RPPA >= _hoops_SSRPR) return _hoops_AIHGC;

	while (*_hoops_RPPA == ' ') if (++_hoops_RPPA == _hoops_SSRPR) return _hoops_AIHGC;

	if (*_hoops_RPPA == '+' || *_hoops_RPPA == '-') {
		if (*_hoops_RPPA++ == '-') _hoops_RHSRS = true;
		if (_hoops_RPPA == _hoops_SSRPR) return _hoops_AIHGC;
	}

	if (*_hoops_RPPA != '0') {			/* _hoops_AHIPP */
		_hoops_GHSRS = 0;

		_hoops_PCCAR {
			switch (*_hoops_RPPA) {
				case '0':										break;
				case '1':		_hoops_GHSRS += 1;				break;
				case '2':		_hoops_GHSRS += 2;				break;
				case '3':		_hoops_GHSRS += 3;				break;
				case '4':		_hoops_GHSRS += 4;				break;
				case '5':		_hoops_GHSRS += 5;				break;
				case '6':		_hoops_GHSRS += 6;				break;
				case '7':		_hoops_GHSRS += 7;				break;
				case '8':		_hoops_GHSRS += 8;				break;
				case '9':		_hoops_GHSRS += 9;				break;
				default:		goto _hoops_HHSRS;
			}

			result = _hoops_GHSRS;
			if (++_hoops_RPPA == _hoops_SSRPR) break;
			_hoops_GHSRS *= 10;
		}

		_hoops_HHSRS:;

		if (result == 0) return _hoops_AIHGC;
	}
	else if (++_hoops_RPPA == _hoops_SSRPR) {		/* _hoops_HHGPR _hoops_AHHR (_hoops_GRH _hoops_AGIR) */
	}
	else if (*_hoops_RPPA == 'x' || *_hoops_RPPA == 'X') {		/* _hoops_ACCAI */
		++_hoops_RPPA;
		_hoops_GHSRS = 0;

		_hoops_PCCAR {
			switch (*_hoops_RPPA) {
				case '0':										break;
				case '1':				_hoops_GHSRS += 1;		break;
				case '2':				_hoops_GHSRS += 2;		break;
				case '3':				_hoops_GHSRS += 3;		break;
				case '4':				_hoops_GHSRS += 4;		break;
				case '5':				_hoops_GHSRS += 5;		break;
				case '6':				_hoops_GHSRS += 6;		break;
				case '7':				_hoops_GHSRS += 7;		break;
				case '8':				_hoops_GHSRS += 8;		break;
				case '9':				_hoops_GHSRS += 9;		break;
				case 'a': case 'A':		_hoops_GHSRS += 10;		break;
				case 'b': case 'B':		_hoops_GHSRS += 11;		break;
				case 'c': case 'C':		_hoops_GHSRS += 12;		break;
				case 'd': case 'D':		_hoops_GHSRS += 13;		break;
				case 'e': case 'E':		_hoops_GHSRS += 14;		break;
				case 'f': case 'F':		_hoops_GHSRS += 15;		break;
				default:				goto _hoops_IHSRS;
			}

			result = _hoops_GHSRS;
			if (++_hoops_RPPA == _hoops_SSRPR) break;
			_hoops_GHSRS *= 16;
		}

		_hoops_IHSRS:;

		if (*(_hoops_RPPA-1) == 'x' || *(_hoops_RPPA-1) == 'X') return _hoops_PHSRS;
	}
	else {						/* _hoops_CHSRS */
		_hoops_GHSRS = 0;

		_hoops_PCCAR {
			switch (*_hoops_RPPA) {
				case '0':										break;
				case '1':				_hoops_GHSRS += 1;		break;
				case '2':				_hoops_GHSRS += 2;		break;
				case '3':				_hoops_GHSRS += 3;		break;
				case '4':				_hoops_GHSRS += 4;		break;
				case '5':				_hoops_GHSRS += 5;		break;
				case '6':				_hoops_GHSRS += 6;		break;
				case '7':				_hoops_GHSRS += 7;		break;
				case '8': case '9':		return _hoops_AHSRS;
				default:				goto _hoops_SHSRS;
			}

			result = _hoops_GHSRS;
			if (++_hoops_RPPA == _hoops_SSRPR) break;
			_hoops_GHSRS *= 8;
		}

		_hoops_SHSRS:;
	}

	if (_hoops_RHSRS)
		*resultp = -result; /* (_hoops_PIP: _hoops_GPGH'_hoops_RA _hoops_SSRR _hoops_IS _hoops_PGSAH _hoops_GPP _hoops_GISRS) */
	else
		*resultp = result;

	while (_hoops_RPPA != _hoops_SSRPR && *_hoops_RPPA == ' ') ++_hoops_RPPA;

	*_hoops_RAARA = _hoops_RPPA;
	return null;
}


GLOBAL_FUNCTION char const * HI_Scan_Integer (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA,	/* _hoops_ASPR _hoops_IS _hoops_ASPR _hoops_IS _hoops_GSGR (_hoops_SRSS) */
	char const *			_hoops_SSRPR,	/* _hoops_ASPR _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_GSGR (_hoops_IRIGR) */
	int *					resultp)/* _hoops_ASPR _hoops_IS _hoops_GHPP (_hoops_PHPH) */
{
	UNREFERENCED(_hoops_RIGC);

	local char const		overflow[] = "Integer too large";

	if (sizeof(long) == sizeof(int))
		return HI_Scan_Long (_hoops_RIGC, _hoops_RAARA, _hoops_SSRPR, (long *)resultp);
	else {
		long			_hoops_PIHGS;
		char const		*_hoops_SSACR;

		if ((_hoops_SSACR = HI_Scan_Long (_hoops_RIGC, _hoops_RAARA, _hoops_SSRPR, &_hoops_PIHGS)) != null) 
			return _hoops_SSACR;

		*resultp = (int)_hoops_PIHGS;

		if ((long)*resultp != _hoops_PIHGS) 
			return overflow;

		return null;
	}
}


GLOBAL_FUNCTION char const * HI_Scan_Float (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA,	/* _hoops_ASPR _hoops_IS _hoops_ASPR _hoops_IS _hoops_GSGR (_hoops_SRSS) */
	char const *			_hoops_SSRPR,	/* _hoops_ASPR _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_GSGR (_hoops_IRIGR) */
	float *					resultp)/* _hoops_ASPR _hoops_IS _hoops_GHPP (_hoops_PHPH) */
{
	UNREFERENCED(_hoops_RIGC);

	char const		*_hoops_RPPA = *_hoops_RAARA;
	char const		*_hoops_HRCAR;
	float			result = 0.0f;
	int				_hoops_RISRS;
	bool		_hoops_RHSRS = false;
	local		char const		_hoops_AIHGC[] = "Expected floating-point number not found",
								overflow[]	= "Floating-point number too big (overflow)",
								_hoops_AISRS[] = "Floating-point number too small (underflow)",
								_hoops_PISRS[] = "Floating-point number syntax error";
	/* _hoops_HISRS._hoops_GSGGR _hoops_IISRS _hoops_GPP _hoops_RH _hoops_RIHH _hoops_GCPPI */
	ASSERT(overflow[26] == 'b' && _hoops_AISRS[26] == 's');

	/* _hoops_IGHHH: _hoops_IPRCC _hoops_RHIPP _hoops_GHCA _hoops_SHH _hoops_PGI 0-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS
	 * _hoops_SHH _hoops_IRAP) _hoops_PAR _hoops_SPCC-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS _hoops_SHH _hoops_GRAA-_hoops_IRAP). _hoops_SPRCC
	 * _hoops_IH _hoops_GHRCC _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_IPHR _hoops_GGSR _hoops_GPRS _hoops_GGR _hoops_PGI _hoops_AGIR; _hoops_PCGC _hoops_IH
	 * _hoops_PACAR _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_RRP _hoops_IS _hoops_SRS _hoops_ISPR _hoops_IH _hoops_CCRCC _hoops_IHGS _hoops_GRAA-_hoops_IRAP.
	 */

	if (_hoops_SSRPR != null && _hoops_RPPA >= _hoops_SSRPR) return _hoops_AIHGC;
	while (*_hoops_RPPA == ' ') if (++_hoops_RPPA == _hoops_SSRPR) return _hoops_AIHGC;

	if (*_hoops_RPPA == '+' || *_hoops_RPPA == '-') {
		if (*_hoops_RPPA++ == '-') _hoops_RHSRS = true;
		if (_hoops_RPPA == _hoops_SSRPR) return _hoops_AIHGC;
	}

	_hoops_HRCAR = _hoops_RPPA;
	_hoops_RISRS = 0;
	while (_hoops_RPPA != _hoops_SSRPR) {
		switch (*_hoops_RPPA++) {
			default: {
				--_hoops_RPPA;
				if (_hoops_RPPA == _hoops_HRCAR && *_hoops_RPPA != '.') return _hoops_AIHGC;
				goto _hoops_CISRS;
			}	/* _hoops_IHSA; */

			case '0':	result = result * 10.0f;		break;
			case '1':	result = result * 10.0f + 1.0f; break;
			case '2':	result = result * 10.0f + 2.0f; break;
			case '3':	result = result * 10.0f + 3.0f; break;
			case '4':	result = result * 10.0f + 4.0f; break;
			case '5':	result = result * 10.0f + 5.0f; break;
			case '6':	result = result * 10.0f + 6.0f; break;
			case '7':	result = result * 10.0f + 7.0f; break;
			case '8':	result = result * 10.0f + 8.0f; break;
			case '9':	result = result * 10.0f + 9.0f; break;
		}

		if (++_hoops_RISRS > _hoops_RARGI) return overflow;
	}
	_hoops_CISRS:;


	if (_hoops_RPPA != _hoops_SSRPR && *_hoops_RPPA == '.') {
		float			_hoops_SPGCR = 1.0f;

		++_hoops_RPPA;
		if (result == 0.0f) {
			while (_hoops_RPPA != _hoops_SSRPR && '0' == *_hoops_RPPA) {
				_hoops_SPGCR *= 0.1f;
				if (--_hoops_RISRS < -_hoops_RARGI) {
					//_hoops_ASRC _hoops_SIHGS;
					goto _hoops_SISRS;
				}
				++_hoops_RPPA;
			}
		}

		while (_hoops_RPPA != _hoops_SSRPR) {
			_hoops_SPGCR *= 0.1f;

			switch (*_hoops_RPPA++) {
				default: {
					/* _hoops_GASA: _hoops_GCSRS _hoops_IRS _hoops_CHRCC _hoops_ASRHR _hoops_SGS _hoops_HRGR _hoops_ICIC _hoops_IS _hoops_SSPC */
					--_hoops_RPPA;
					if (_hoops_RPPA == _hoops_HRCAR + 1) return _hoops_AIHGC;
					goto _hoops_SISRS;
				}		/* _hoops_IHSA; */

				case '0':										break;
				case '1':		result += _hoops_SPGCR;			break;
				case '2':		result += _hoops_SPGCR * 2.0f;	break;
				case '3':		result += _hoops_SPGCR * 3.0f;	break;
				case '4':		result += _hoops_SPGCR * 4.0f;	break;
				case '5':		result += _hoops_SPGCR * 5.0f;	break;
				case '6':		result += _hoops_SPGCR * 6.0f;	break;
				case '7':		result += _hoops_SPGCR * 7.0f;	break;
				case '8':		result += _hoops_SPGCR * 8.0f;	break;
				case '9':		result += _hoops_SPGCR * 9.0f;	break;
			}
		}
		_hoops_SISRS:;
	}

	if (_hoops_RHSRS) result = -result;

	/* _hoops_GASA: _hoops_GCSRS _hoops_IRS _hoops_CHRCC _hoops_ASRHR _hoops_SGS _hoops_HRGR _hoops_ICIC _hoops_IS _hoops_SSPC */
	if (_hoops_RPPA != _hoops_SSRPR && (*_hoops_RPPA == 'e' || *_hoops_RPPA == 'E')) {
		int				_hoops_GRASR = 0;

		++_hoops_RPPA;
		_hoops_RHSRS = false;

		while (_hoops_RPPA != _hoops_SSRPR && *_hoops_RPPA == ' ') ++_hoops_RPPA;

		if (_hoops_RPPA != _hoops_SSRPR && (*_hoops_RPPA == '+' || *_hoops_RPPA == '-')) {
			if (*_hoops_RPPA++ == '-') _hoops_RHSRS = true;
		}

		_hoops_HRCAR = _hoops_RPPA;
		while (_hoops_RPPA != _hoops_SSRPR) {
			switch (*_hoops_RPPA++) {
				default: {
					--_hoops_RPPA;
					if (_hoops_RPPA == _hoops_HRCAR) return _hoops_PISRS;
					goto _hoops_RCSRS;
				}		/* _hoops_IHSA; */

				case '0':		_hoops_GRASR = _hoops_GRASR * 10;				break;
				case '1':		_hoops_GRASR = _hoops_GRASR * 10 + 1;			break;
				case '2':		_hoops_GRASR = _hoops_GRASR * 10 + 2;			break;
				case '3':		_hoops_GRASR = _hoops_GRASR * 10 + 3;			break;
				case '4':		_hoops_GRASR = _hoops_GRASR * 10 + 4;			break;
				case '5':		_hoops_GRASR = _hoops_GRASR * 10 + 5;			break;
				case '6':		_hoops_GRASR = _hoops_GRASR * 10 + 6;			break;
				case '7':		_hoops_GRASR = _hoops_GRASR * 10 + 7;			break;
				case '8':		_hoops_GRASR = _hoops_GRASR * 10 + 8;			break;
				case '9':		_hoops_GRASR = _hoops_GRASR * 10 + 9;			break;
			}
			if (_hoops_GRASR >= 1000) return _hoops_RHSRS ? _hoops_AISRS : overflow;
		}
		_hoops_RCSRS:;

		if (_hoops_GRASR != 0) {
			float	_hoops_ACSRS;
			if (_hoops_RHSRS) {
				if (_hoops_RISRS - _hoops_GRASR < -_hoops_RARGI) {
					//_hoops_ASRC _hoops_SIHGS;
					result = 0.0f;
					_hoops_GRASR = 0;
				}
				_hoops_ACSRS = 0.1f;
			}
			else {
				if (_hoops_RISRS + _hoops_GRASR > _hoops_RARGI) return overflow;
				_hoops_ACSRS = 10.0f;
			}
			while (_hoops_GRASR > 0) {
				while ((_hoops_GRASR & 1) == 0) {
					_hoops_GRASR /= 2;
					_hoops_ACSRS *= _hoops_ACSRS;
				}
				_hoops_GRASR -= 1;
				result *= _hoops_ACSRS;
			}
		}
	}

	/* _hoops_GCSRS _hoops_IRS _hoops_CHRCC _hoops_ASRHR _hoops_SGS _hoops_HRGR _hoops_ICIC _hoops_IS _hoops_SSPC */
	*resultp = result;

	while (_hoops_RPPA != _hoops_SSRPR && *_hoops_RPPA == ' ') ++_hoops_RPPA;

	*_hoops_RAARA = _hoops_RPPA;
	return null;
}



GLOBAL_FUNCTION char const * HI_Scan_Boolean (
	_hoops_AIGPR *	_hoops_RIGC,
	char const **			_hoops_RAARA,	/* _hoops_ASPR _hoops_IS _hoops_ASPR _hoops_IS _hoops_GSGR (_hoops_SRSS) */
	char const *			_hoops_SSRPR,	/* _hoops_ASPR _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_GSGR (_hoops_IRIGR) */
	bool *					resultp)/* _hoops_ASPR _hoops_IS _hoops_GHPP (_hoops_PHPH) */
{
	UNREFERENCED(_hoops_RIGC);

	char const		*_hoops_RPPA = *_hoops_RAARA;
	local char const _hoops_PCSRS[] =
		"Expected bool value (On/Off/True/False/1/0/Yes/No) not found";

	/* _hoops_IGHHH: _hoops_IPRCC _hoops_RHIPP _hoops_GHCA _hoops_SHH _hoops_PGI 0-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS
	 * _hoops_SHH _hoops_IRAP) _hoops_PAR _hoops_SPCC-_hoops_CCGAI (_hoops_CCRCC _hoops_GRS _hoops_SHH _hoops_GRAA-_hoops_IRAP). _hoops_SPRCC
	 * _hoops_IH _hoops_GHRCC _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_IPHR _hoops_GGSR _hoops_GPRS _hoops_GGR _hoops_PGI _hoops_AGIR; _hoops_PCGC _hoops_IH
	 * _hoops_PACAR _hoops_IS _hoops_CCRCC _hoops_GRS _hoops_RRP _hoops_IS _hoops_SRS _hoops_ISPR _hoops_IH _hoops_CCRCC _hoops_IHGS _hoops_GRAA-_hoops_IRAP.
	 */

	if (_hoops_SSRPR != null && _hoops_RPPA >= _hoops_SSRPR) return _hoops_PCSRS;
	while (*_hoops_RPPA == ' ') if (++_hoops_RPPA == _hoops_SSRPR) return _hoops_PCSRS;

	switch (*_hoops_RPPA++) {
		case 'T': case 't': {
			if ((_hoops_SSRPR == null || _hoops_RPPA+2 < _hoops_SSRPR) &&
				(_hoops_RPPA[0] == 'r' || _hoops_RPPA[0] == 'R') &&
				(_hoops_RPPA[1] == 'u' || _hoops_RPPA[1] == 'U') &&
				(_hoops_RPPA[2] == 'e' || _hoops_RPPA[2] == 'E')) _hoops_RPPA += 3;

			*resultp = true;
		}	break;

		case 'F': case 'f': {
			if ((_hoops_SSRPR == null || _hoops_RPPA+3 < _hoops_SSRPR) &&
				(_hoops_RPPA[0] == 'a' || _hoops_RPPA[0] == 'A') &&
				(_hoops_RPPA[1] == 'l' || _hoops_RPPA[1] == 'L') &&
				(_hoops_RPPA[2] == 's' || _hoops_RPPA[2] == 'S') &&
				(_hoops_RPPA[3] == 'e' || _hoops_RPPA[3] == 'E')) _hoops_RPPA += 4;

			*resultp = false;
		}	break;

		case 'Y': case 'y': {
			if ((_hoops_SSRPR == null || _hoops_RPPA+1 < _hoops_SSRPR) &&
				(_hoops_RPPA[0] == 'e' || _hoops_RPPA[0] == 'E') &&
				(_hoops_RPPA[1] == 's' || _hoops_RPPA[1] == 'S')) _hoops_RPPA += 2;

			*resultp = true;
		}	break;

		case 'N': case 'n': {
			if ((_hoops_SSRPR == null || _hoops_RPPA < _hoops_SSRPR) &&
				(_hoops_RPPA[0] == 'o' || _hoops_RPPA[0] == 'O')) _hoops_RPPA += 1;

			*resultp = false;
		}	break;

		case '1': {
			*resultp = true;
		}	break;

		case '0': {
			*resultp = false;
		}	break;

		case 'O': case 'o': {
			if (_hoops_RPPA == _hoops_SSRPR) return _hoops_PCSRS;

			if (*_hoops_RPPA == 'n' || *_hoops_RPPA == 'N') {
				++_hoops_RPPA;
				*resultp = true;
			}
			else if ((_hoops_SSRPR == null || _hoops_RPPA+1 < _hoops_SSRPR) &&
					 (_hoops_RPPA[0] == 'f' || _hoops_RPPA[0] == 'F') &&
					 (_hoops_RPPA[1] == 'f' || _hoops_RPPA[1] == 'F')) {
				_hoops_RPPA += 2;
				*resultp = false;
			}
			else
				return _hoops_PCSRS;
		}	break;

		default: {
			return _hoops_PCSRS;
		}		/*_hoops_IHSA;*/
	}

	while (_hoops_RPPA != _hoops_SSRPR && *_hoops_RPPA == ' ') ++_hoops_RPPA;

	*_hoops_RAARA = _hoops_RPPA;
	return null;
}


#include "database.h"

local const _hoops_IGRCR _hoops_AHSIA[] = {
	{GSU_ORU,			_hoops_GRRCR ("oru"),			_hoops_RRRCR, 0, false},
	{GSU_SRU,			_hoops_GRRCR ("sru"),			_hoops_RRRCR, 0, false},
	{GSU_WRU,			_hoops_GRRCR ("wru"),			_hoops_RRRCR, 0, false},
	{_hoops_SPSC,			_hoops_GRRCR ("wsu"),			_hoops_RRRCR, 0, false},
	{_hoops_SPSC,			_hoops_GRRCR ("world"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pixels"),		_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pixel"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("pxl"),			_hoops_RRRCR, 0, false},
	{GSU_PIXELS,		_hoops_GRRCR ("px"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("points"),		_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("point"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("pts"),			_hoops_RRRCR, 0, false},
	{GSU_POINTS,		_hoops_GRRCR ("pt"),			_hoops_RRRCR, 0, false},
};


GLOBAL_FUNCTION char const *HI_Scan_Generic_Size (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HCAIR *			value,
	char const *			options,
	char const *			type) 
{
	char const *			_hoops_SSACR = null;
	char const *			_hoops_RPPA;
	_hoops_HCRPR					name;

	while (*options == ' ') 
		++options;

	if ((_hoops_SSACR = HI_Scan_Float (_hoops_RIGC, &options, null, &value->value)) != null)
		return Sprintf_SS (null, "Can't scan '%s' - %s", type, _hoops_SSACR);

	_hoops_RPPA = options;
	if ((_hoops_SSACR = HI_Scan_Name (_hoops_RIGC, &options, null, &name)) != null)
		return Sprintf_SS (null, "Can't scan '%s' - %s", type, _hoops_SSACR);

	while (*options == ' ') ++options;
	if (*options != '\0') {
		_hoops_SSACR = Sprintf_SS (null, "'%s' is not a reasonable units specifier for '%s'", _hoops_RPPA, type);
	}
	else {
		int i;
		for (i=0; i<_hoops_GGAPR(_hoops_AHSIA); ++i) {
			if (_hoops_RAHSR (*(_hoops_HCRPR *)&_hoops_AHSIA[i].name, name))
				break;
		}

		if (i == _hoops_GGAPR(_hoops_AHSIA)) {
			_hoops_SSACR = Sprintf_NS (null, "'%n' is not a reasonable units specifier for '%s'", &name, type);
		}
		else
			value->_hoops_HHP = (_hoops_GIGRP)_hoops_AHSIA[i].id;
	}

	_hoops_RGAIR (name);

	return _hoops_SSACR;
}


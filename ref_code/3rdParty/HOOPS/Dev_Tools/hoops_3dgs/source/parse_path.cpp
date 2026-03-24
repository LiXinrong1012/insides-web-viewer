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
 * $Id: obf_tmp.txt 1.60 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "path.h"
#include "adt.h"
#include "hi_proto.h"
#include "hpserror.h"


#ifdef _hoops_RCRCC
static FILE * f=NULL;
#endif

local char const * _hoops_ACRCC (
	char const		**_hoops_RAARA,	/* _hoops_ASPR _hoops_IS _hoops_ASPR _hoops_IS _hoops_GSGR (_hoops_SRSS) */
	char const		*_hoops_SSRPR,	/* _hoops_ASPR _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_GSGR (_hoops_IRIGR) */
	_hoops_HCRPR			*name) { /* _hoops_ASPR _hoops_IS _hoops_GHPP (_hoops_PHPH) */
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
			for (i=0; i<(_hoops_SSRPR - *_hoops_RAARA); i++)
				fprintf(f, "%c", *_hoops_RAARA[i]);
			fprintf(f, "\n");
		}
		else
			fprintf(f, "%s\n", *_hoops_RAARA);
#endif

		if (_hoops_SSRPR != null && _hoops_RPPA >= _hoops_SSRPR)
			return _hoops_AIHGC;

		while (*_hoops_RPPA == ' ') if (++_hoops_RPPA == _hoops_SSRPR)
			return _hoops_AIHGC;

		_hoops_HCRCC = _hoops_RPPA;

		/* ('%' _hoops_HRGR _hoops_HAR _hoops_IRS _hoops_HAIHH _hoops_RGAR _hoops_IH _hoops_RH _hoops_SSCPR _hoops_IIGR
		*	_hoops_RH '_hoops_IGIR _hoops_AAHP' _hoops_HCGR _hoops_HRCSR _hoops_HCSP.)
		*/

		_hoops_RGGA (_hoops_RPPA == _hoops_SSRPR) switch (*_hoops_RPPA++) {
			default: {
				++length;
			}	break;

			case '/': case '?': case '*': case '^': case ',':
			case '{': case '}': case '<': case '>': case '!': case '(':
			case ')': case '\0': case '\n': case '=': case '@': { /* _hoops_RHRCC! */
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
		_hoops_RPPA++;		/* _hoops_CR _hoops_SR _hoops_PHRCC _hoops_HPP _hoops_HHRCC _hoops_RH _hoops_RSGR, _hoops_SHI _hoops_RH --_hoops_GSIPH _hoops_CAPP */

_hoops_PCPPR:;

		/* _hoops_GASA: _hoops_RH _hoops_HSPR _hoops_PGCR _hoops_APGR _hoops_RSRHR _hoops_CHRCC _hoops_AHGSR _hoops_SGS _hoops_CHR _hoops_ICIC _hoops_IS _hoops_SSPC */
		_hoops_ICRCC = --_hoops_RPPA;
		while (length > 0 && *--_hoops_RPPA == ' ') --length;

		if (length == 0) {	/* _hoops_PIHA _hoops_HS _hoops_RPII _hoops_CGIGI _hoops_IRAP _hoops_GSGR */
			name->length = 0;
			name->text = null;
		}
		else {
			ALLOC_ARRAY (_hoops_PCRCC, length+1, char);
			name->length = length;
			name->text = _hoops_PCRCC;

			_hoops_RPPA = _hoops_HCRCC;

			do switch (_hoops_IRGCR(*_hoops_RPPA)) {
				case 0337/*_hoops_SHRCC-_hoops_GIRCC*/:		case 0340/*_hoops_IRS`*/:
				case 0341/*_hoops_IRS'*/:		case 0342/*_hoops_IRS^*/:
				case 0343/*_hoops_IRS~*/:		case 0344/*_hoops_IRS"*/:
				case 0345/*_hoops_IRS.*/:		case 0346/*_hoops_RIRCC*/:
				case 0347/*_hoops_GSGGR,*/:		case 0350/*_hoops_IAS`*/:
				case 0351/*_hoops_IAS'*/:		case 0352/*_hoops_IAS^*/:
				case 0353/*_hoops_IAS"*/:		case 0354/*_hoops_HAS`*/:
				case 0355/*_hoops_HAS'*/:		case 0356/*_hoops_HAS^*/:
				case 0357/*_hoops_HAS"*/:		case 0360/*_hoops_AIRCC*/:
				case 0361/*_hoops_ACHP~*/:		case 0362/*_hoops_GCSR`*/:
				case 0363/*_hoops_GCSR'*/:		case 0364/*_hoops_GCSR^*/:
				case 0365/*_hoops_GCSR~*/:		case 0366/*_hoops_GCSR"*/:
				case 0370/*_hoops_GCSR/ */:		case 0371/*_hoops_IARGR`*/:
				case 0372/*_hoops_IARGR'*/:		case 0373/*_hoops_IARGR^*/:
				case 0374/*_hoops_IARGR"*/:		case 0375/*_hoops_HAPC'*/:
				case 0376/*_hoops_PIRCC*/:		case 0377/*_hoops_HAPC"*/:

				case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
				case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
				case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
				case 's': case 't': case 'u': case 'v': case 'w': case 'x':
				case 'y': case 'z': case '$': case '_': case '-': case '+':
				case '#': case ' ': case '0': case '1': case '2': case '3':
				case '4': case '5': case '6': case '7': case '8': case '9':
				case ':': case '&': case '.': case '%': case '[': case ']':
				case '\\': {
					*_hoops_PCRCC++ = *_hoops_RPPA++;
				}	break;

				case 0300/*_hoops_RAIGR`*/:		case 0301/*_hoops_RAIGR'*/:
				case 0302/*_hoops_RAIGR^*/:		case 0303/*_hoops_RAIGR~*/:
				case 0304/*_hoops_RAIGR"*/:		case 0305/*_hoops_RAIGR.*/:
				case 0306/*_hoops_PAAIA*/:		case 0307/*_hoops_IHRPR,*/:
				case 0310/*_hoops_HRAIA`*/:		case 0311/*_hoops_HRAIA'*/:
				case 0312/*_hoops_HRAIA^*/:		case 0313/*_hoops_HRAIA"*/:
				case 0314/*_hoops_GHAP`*/:		case 0315/*_hoops_GHAP'*/:
				case 0316/*_hoops_GHAP^*/:		case 0317/*_hoops_GHAP"*/:
				case 0320/*_hoops_HIRCC-_hoops_AIRCC*/:		case 0321/*_hoops_PGGIR~*/:
				case 0322/*_hoops_RGGIR`*/:		case 0323/*_hoops_RGGIR'*/:
				case 0324/*_hoops_RGGIR^*/:		case 0325/*_hoops_RGGIR~*/:
				case 0326/*_hoops_RGGIR"*/:		case 0330/*_hoops_RGGIR/ */:
				case 0331/*_hoops_GRGGR`*/:		case 0332/*_hoops_GRGGR'*/:
				case 0333/*_hoops_GRGGR^*/:		case 0334/*_hoops_GRGGR"*/:
				case 0335/*_hoops_GHCR'*/:		case 0336/*_hoops_HIRCC-_hoops_PIRCC*/:

				case 'A': case 'B': case 'C': case 'D':
				case 'E': case 'F': case 'G': case 'H': case 'I': case 'J':
				case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
				case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V':
				case 'W': case 'X': case 'Y': case 'Z': {
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

				default: {
					_hoops_RGAIR (*name);
					return "Illegal character found - try more quote marks?";
				}	_hoops_HHHI;
			} _hoops_RGGA (--length <= 0);
			*_hoops_PCRCC = '\0';
		}

		*_hoops_RAARA = _hoops_ICRCC;
		return null;
}


/* _hoops_PIP: _hoops_RHAP _hoops_HAR _hoops_PPPCR "_hoops_RAIGR(_hoops_IHAC, ,_hoops_IHRPR)_hoops_APCAR" _hoops_CIAH */

#define _hoops_SCRCC		4		/* _hoops_RAS _hoops_AAGPH, *, % */
#define _hoops_GSRCC	3		/* _hoops_RAS _hoops_GHAAI '/' */
#define _hoops_RSRCC			2		/* _hoops_RAS _hoops_GHAAI '.' _hoops_PAR _hoops_PCCP _hoops_PHPPR _hoops_RSIRR */
#define _hoops_ASRCC	1		/* _hoops_RAS _hoops_GARAI '/' */
#define _hoops_PSRCC		0		/* _hoops_RAS _hoops_PA _hoops_SHS */


struct _hoops_RIASA {
	_hoops_RIASA *		prev;
	_hoops_RSAPR *	_hoops_CIPPR;
};


local char const * _hoops_HSRCC (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_AAPHP *		_hoops_GGRHH,
	_hoops_RSAPR *			_hoops_CIPPR,
	_hoops_RIASA *				_hoops_RCSHR,
	int						state,
	int						flags,
	int						depth) {

	/* _hoops_PSSP _hoops_SGHC _hoops_GIAA _hoops_RH _hoops_RAGA _hoops_CAGH */

	_hoops_PCCAR {	/* _hoops_GAR _hoops_RGRRR _hoops_GAR _hoops_SR _hoops_HS _hoops_GRPSA (_hoops_CACH _hoops_PRPC _hoops_IIGR _hoops_HAPR) */
		switch (_hoops_CIPPR->type) {
			case _hoops_ISAPR: {
				if (depth >= 0)
					return "'.' may only be used at start of the specification";

				if (!BIT (flags, _hoops_RPPSA)) depth = 9999; /* _hoops_HPCAR _hoops_SCH'_hoops_GRI _hoops_RIRA */
				else {
					_hoops_CRCP *			_hoops_SRCP;

					if (_hoops_RIGC->open_list == null ||
						_hoops_RIGC->open_list->_hoops_GCRIR != _hoops_RCRIR ||
						BIT (_hoops_RIGC->open_list->_hoops_RRHH, _hoops_APAPP))
							return "'.' referred to, but no segment is open";

					depth = -1;
					_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;
					do ++depth, _hoops_SRCP = _hoops_SRCP->owner;
					_hoops_RGGA (_hoops_SRCP->type != _hoops_IRCP);
				}

				state = _hoops_RSRCC;
			}	break;

			case _hoops_RGPPR: {
				_hoops_SRPPR const *	alias;
				char const *	result;

				if (state == _hoops_RSRCC || state == _hoops_SCRCC)
					return "Missing separator (near '?')";

				if (!BIT (flags, _hoops_RPPSA)) 
					return null;	 /* _hoops_RCRP _hoops_GH (_hoops_AGHPA _hoops_SPHR) */

				if ((alias = *HI_Look_Up_Alias(_hoops_RIGC, _hoops_CIPPR->_hoops_AGPPR.text, _hoops_CIPPR->_hoops_AGPPR.length)) == null)
					return Sprintf_N (null, "'?%n' is not currently defined", &_hoops_CIPPR->_hoops_AGPPR);

				if (_hoops_GGRHH->LookupItem(alias) == VHASH_STATUS_SUCCESS)
					return Sprintf_N (null,"Alias '?%n' currently has a recursive definition - can't expand", &_hoops_CIPPR->_hoops_AGPPR);

				_hoops_CIPPR->expansion = alias->_hoops_AAPPR;

				_hoops_GGRHH->InsertItem(alias);

				if (_hoops_CIPPR->next == null) {
					result = _hoops_HSRCC (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR->expansion, _hoops_RCSHR, state, flags, depth);
				}
				else {
					_hoops_RIASA _hoops_ISRCC;

					_hoops_ISRCC.prev = _hoops_RCSHR;
					_hoops_ISRCC._hoops_CIPPR = _hoops_CIPPR->next;

					result = _hoops_HSRCC (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR->expansion, &_hoops_ISRCC, state, flags, depth);
				}

				_hoops_GGRHH->RemoveItem(alias);

				return result;
			}	/*_hoops_IHSA;*/

			case _hoops_CSAPR: {
				if (depth < 0) {
					depth = 0;
					state = _hoops_GSRCC;
				}
				else if (state == _hoops_GSRCC || state == _hoops_ASRCC)
					return "Too many /'s";
				else
					state = _hoops_ASRCC;
			}	break;

			case _hoops_HRPPR: {
				if (state == _hoops_RSRCC || state == _hoops_SCRCC)
					return "Missing separator (near '@')";

				/* _hoops_IIS _hoops_CIS _hoops_HIISR _hoops_CCA _hoops_IRSPR */

				depth = 9999;	/* _hoops_IRHH _hoops_SCH _hoops_IHSH _hoops_IHRI */
				state = _hoops_RSRCC;
			}	break;

			case _hoops_GGPPR: {
				if (state == _hoops_RSRCC)
					return "Missing separator (near '^')";

				if (depth < 0) {
					if (!BIT (flags, _hoops_RPPSA))
						depth = 9999; /* _hoops_HPCAR _hoops_SCH'_hoops_GRI _hoops_RIRA */
					else {
						if (_hoops_RIGC->open_list == null ||
							_hoops_RIGC->open_list->_hoops_GCRIR != _hoops_RCRIR ||
							BIT (_hoops_RIGC->open_list->_hoops_RRHH, _hoops_APAPP))
								return "'^' referred to, but no segment is open";

						depth = -1;
						_hoops_CRCP *	_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;
						do {
							++depth, _hoops_SRCP = _hoops_SRCP->owner;
						} _hoops_RGGA (_hoops_SRCP->type != _hoops_IRCP);
					}
				}

				if (--depth < 0)
					return "Too many ^'s - fell off the top";

				state = _hoops_PSRCC;
			}	break;

			case _hoops_SGPPR: {
				int				_hoops_SIPPR = 0;
				_hoops_RSAPR	*_hoops_IGRHH = _hoops_CIPPR;

				if (!BIT (flags, _hoops_AIPPR))
					return "Alternatives (i.e., commas) not allowed in this context";

				/* _hoops_SSS _hoops_PIS _hoops_RPHR _hoops_RGGR, _hoops_RPP _hoops_GII */

				_hoops_PCCAR {
					if ((_hoops_CIPPR = _hoops_CIPPR->next) == null) {
						/* _hoops_SR _hoops_CHR _hoops_HPGR _hoops_CGRHH _hoops_PAPA, _hoops_PPR _hoops_IHGRH _hoops_IHCS
						 * _hoops_PSAP _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIGR _hoops_SIHH _hoops_IRS _hoops_PIS ')'.
						 */

						/* _hoops_HSPP _hoops_IAPR */

						depth = -1;
						state = _hoops_PSRCC;
						_hoops_CIPPR = _hoops_IGRHH;
						break;
					}

					if (_hoops_CIPPR->type == _hoops_GRPPR)
						++_hoops_SIPPR;
					else if (_hoops_CIPPR->type == _hoops_RRPPR)
						if (--_hoops_SIPPR < 0)
							break;
				}
			}	break;

			case _hoops_RRPPR: {
			}	break;

			case _hoops_GRPPR: {
				_hoops_PCCAR {
					int				_hoops_SIPPR = 0;
					char const *	_hoops_ACSR;

					_hoops_CIPPR = _hoops_CIPPR->next;
					if ((_hoops_ACSR = _hoops_HSRCC (_hoops_RIGC, _hoops_GGRHH, _hoops_CIPPR, _hoops_RCSHR, state, flags, depth)) != null)
						return _hoops_ACSR;

					_hoops_RGGA (_hoops_CIPPR->type == _hoops_SGPPR && _hoops_SIPPR == 0) {
						if (_hoops_CIPPR->type == _hoops_GRPPR)
							++_hoops_SIPPR;
						else if (_hoops_CIPPR->type == _hoops_RRPPR)
							if (--_hoops_SIPPR < 0)
								return null;

						_hoops_CIPPR = _hoops_CIPPR->next;
					}
				}
			}	/*_hoops_IHSA;*/

			case _hoops_PRPPR:
			case _hoops_ARPPR:
			case _hoops_SSAPR:
			case _hoops_HSAPR:
			case _hoops_PGRHH: {
				if (state == _hoops_RSRCC) switch (_hoops_CIPPR->type) {
					case _hoops_PRPPR:			return "Missing separator (near '*')";
					case _hoops_SSAPR:			return "Missing separator (near '%')";
					case _hoops_HSAPR:			return "Missing separator (near '...')";
					case _hoops_PGRHH:	return "Missing separator (near '....')";
					case _hoops_ARPPR:			return Sprintf_N (null, "Missing separator (near '%n')", &_hoops_CIPPR->_hoops_AGPPR);
				}

				if (depth < 0) {
					if (!BIT (flags, _hoops_RPPSA)) depth = 9999; /* _hoops_HPCAR _hoops_SCH'_hoops_GRI _hoops_RIRA */
					else {
						_hoops_CRCP *	_hoops_SRCP;

						if (_hoops_RIGC->open_list == null ||
							_hoops_RIGC->open_list->_hoops_GCRIR != _hoops_RCRIR ||
							BIT (_hoops_RIGC->open_list->_hoops_RRHH, _hoops_APAPP))
							return "Specification did not start with root ('/'), and no segment is open";

						depth = -1;
						_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_PCRIR;
						do {
							++depth, _hoops_SRCP = _hoops_SRCP->owner;
						} _hoops_RGGA (_hoops_SRCP->type != _hoops_IRCP);
					}
				}

				if (_hoops_CIPPR->type != _hoops_ARPPR && !BIT (flags, _hoops_AIPPR))
					return "Wildcards not allowed in this context";

				if (state == _hoops_ASRCC &&
					_hoops_CIPPR->type != _hoops_HSAPR && _hoops_CIPPR->type != _hoops_PGRHH)
					++depth;

				state = (_hoops_CIPPR->type == _hoops_HSAPR || _hoops_CIPPR->type == _hoops_PGRHH) ? _hoops_PSRCC : _hoops_SCRCC;
			}	break;

			case _hoops_PGPPR:
			case _hoops_HGPPR:
			case _hoops_IGPPR:
			case _hoops_CGPPR:
			case _hoops_CSRCC: {
				if (state == _hoops_ASRCC)
					return "Trailing '/' with no name following";

				if (depth < 0)
					return "Completely blank or void specification";

				/* _hoops_HSPP _hoops_IAPR */

				depth = -1;
				state = _hoops_PSRCC;
			}	break;

			default: {
				_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Somethin' bad during 'check_path'");
				return null;
			}	/* _hoops_IHSA; */
		}

		if ((_hoops_CIPPR = _hoops_CIPPR->next) == null) {
			if (_hoops_RCSHR == null)
				break;
			if (state == _hoops_GSRCC)
				state = _hoops_PSRCC;
			_hoops_CIPPR = _hoops_RCSHR->_hoops_CIPPR;
			_hoops_RCSHR = _hoops_RCSHR->prev;
		}
	}

	/* _hoops_SGPSA _hoops_GGSR _hoops_IIGR _hoops_GRPSA - _hoops_PIHA _hoops_SHH _hoops_IIH! */

	if (state == _hoops_ASRCC)
		return "Trailing '/' with no name following";

	if (depth < 0)
		return "Completely blank or void specification";

	return null;
}


GLOBAL_FUNCTION _hoops_RSAPR * HI_Parse_Path (
	_hoops_AIGPR *		_hoops_RIGC,
	char const *				_hoops_RCCIH,
	int							flags) 
{
	char const *				spec = _hoops_RCCIH;
	_hoops_RSAPR					_hoops_GGHPR;
	_hoops_RSAPR *				pt = &_hoops_GGHPR;
	int							_hoops_SIPPR = 0;

	/*** _hoops_IGIPR _hoops_IRAP-_hoops_CCGAI _hoops_GSGR! ***/

	_hoops_GGHPR.next = null;

	_hoops_RGGA (*spec == '\0') switch (*spec++) {
		case ' ': {
		}	break;

		case '/': {
			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_CSAPR;
		}	break;

		case '^': {
			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_GGPPR;
		}	break;

		case '*': {
			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_PRPPR;
			_hoops_GGHPR.next->_hoops_GARHH = true;
		}	break;

		case '%': {
			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_SSAPR;
			_hoops_GGHPR.next->_hoops_GARHH = true;
		}	break;

		case '@': {
			bool		_hoops_SSRCC = true;

			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_HRPPR;
			pt->key = 0;
			while (*spec == ' ') ++spec;

			_hoops_PCCAR {
				int				inc;

				switch (*spec++) {
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

				pt->key <<= 4;
				pt->key += inc;
				_hoops_SSRCC = false;
			}

			--spec;

			if (_hoops_SSRCC) {
				HE_ERROR (HEC_SYNTAX, HES_AT_SIGN_MISSING_FROM_KEY,
						Sprintf_S (null, "Missing segment key after '@' in '%s'", _hoops_RCCIH));
				pt->next = null;
				HI_Free_Path (_hoops_GGHPR.next);
				return null;
			}
		}	break;

		case ',': {
			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_SGPPR;
			_hoops_GGHPR.next->_hoops_GARHH = true;
		}	break;

		case '>': {
			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_IGPPR;
			pt->level = 1;
			if (!BIT (HOOPS_WORLD->system_flags, _hoops_SSCPP) &&
				*spec == '>') do
				++pt->level;
			_hoops_RGGA (*++spec != '>');
		}	break;

		case '<': {
			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_CGPPR;
			pt->level = 1;
			if (!BIT (HOOPS_WORLD->system_flags, _hoops_SSCPP) &&
				*spec == '<') do
				++pt->level;
			_hoops_RGGA (*++spec != '<');
		}	break;

		case '}': {
			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_HGPPR;
			pt->level = 1;
			if (!BIT (HOOPS_WORLD->system_flags, _hoops_SSCPP) &&
				*spec == '}') do
				++pt->level;
			_hoops_RGGA (*++spec != '}');
		}	break;

		case '{': {
			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_PGPPR;
			pt->level = 1;
			if (!BIT (HOOPS_WORLD->system_flags, _hoops_SSCPP) &&
				*spec == '{') do
				++pt->level;
			_hoops_RGGA (*++spec != '{');
		}	break;
/*
*		_hoops_AGIR '!': {
*			_hoops_RPIPC (_hoops_SGPSH->_hoops_SPS, _hoops_GGACC);
*			_hoops_SGPSH = _hoops_SGPSH->_hoops_SPS;
*			_hoops_SGPSH->_hoops_GPRR = _hoops_RGACC;
*		}	_hoops_IHSA;
*/
		case '(': {
			++_hoops_SIPPR;
			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_GRPPR;
		}	break;

		case ')': {
			if (--_hoops_SIPPR < 0) {
				HE_ERROR (HEC_SYNTAX, HES_BAD_PARENTHESES,
						Sprintf_S (null, "Unbalanced parentheses in '%s'", _hoops_RCCIH));

				pt->next = null;
				HI_Free_Path (_hoops_GGHPR.next);
				return null;
			}

			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_RRPPR;
		}	break;

		default: {
			char const *	_hoops_AGACC;
			char const *	_hoops_CIIAC;
			char const		first = *--spec;

			ZALLOC (pt->next, _hoops_RSAPR);
			pt = pt->next;
			pt->type = _hoops_ARPPR;

			if (*spec == '?') {
				pt->type = _hoops_RGPPR;
				do {} while (*++spec == ' ');
			}

			_hoops_AGACC = spec;
			if ((_hoops_CIIAC = _hoops_ACRCC (&_hoops_AGACC, null, &pt->_hoops_AGPPR)) != null) {
				HE_ERROR2 (HEC_SYNTAX, HES_PARSE_STRING,
						Sprintf_S (null, "Error parsing '%s'", _hoops_RCCIH), _hoops_CIIAC);
				pt->next = null;
				pt->_hoops_AGPPR.length = 0;
				HI_Free_Path (_hoops_GGHPR.next);
				return null;
			}

			if (pt->_hoops_AGPPR.length == 0) {
				char	buf[2];
				buf[0] = *spec;
				buf[1] = '\0';
				HE_ERROR (HEC_SYNTAX, HES_BAD_CHARACTER,
						Sprintf_SS (null, "Unexpected character '%s' found in segment name '%s'", buf, _hoops_RCCIH));
				pt->next = null;
				HI_Free_Path (_hoops_GGHPR.next);
				return null;
			}

			/* _hoops_ISPR _hoops_IH _hoops_GRH _hoops_ARAR */
			if (pt->type == _hoops_ARPPR && first == '.') {
				switch (pt->_hoops_AGPPR.length) {
					case 1: {
						pt->type = _hoops_ISAPR;
					}	break;
					case 2: {
						if (_hoops_AGGR (pt->_hoops_AGPPR.text, ".."))
							pt->type = _hoops_GGPPR;
					}	break;
					case 3: {
						if (_hoops_AGGR (pt->_hoops_AGPPR.text, "..."))
							pt->type = _hoops_HSAPR;
					}	break;
					case 4: {
						if (_hoops_AGGR (pt->_hoops_AGPPR.text, "...."))
							pt->type = _hoops_PGRHH;
					}	break;
				}

				if (pt->type != _hoops_ARPPR)
					_hoops_RGAIR (pt->_hoops_AGPPR);
			}


			spec = _hoops_AGACC;
		}	break;
	}

	pt->next = null;

	if (_hoops_GGHPR.next == null) {
		HE_ERROR (HEC_SYNTAX, HES_NULL_INPUT, "Blank or null segment specification");
		return null;
	}

	if (_hoops_SIPPR != 0) {
		HE_ERROR (HEC_SYNTAX, HES_BAD_PARENTHESES, Sprintf_S (null, "Unbalanced parentheses in '%s'", _hoops_RCCIH));
		HI_Free_Path (_hoops_GGHPR.next);
		return null;
	}

	_hoops_AAPHP *	_hoops_GGRHH = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_AAPHP)(_hoops_RIGC->memory_pool, _hoops_PAPHP);

	char const *		_hoops_PGACC = _hoops_HSRCC(_hoops_RIGC, _hoops_GGRHH, _hoops_GGHPR.next, null, _hoops_PSRCC, flags, -1);

	delete _hoops_GGRHH;

	if (_hoops_PGACC != null) {
		char	buf[MAX_ERRMSG];
		HE_ERROR2 (HEC_SYNTAX, HES_SYNTAX_ERROR, 
			Sprintf_S (buf, "Syntax error during expansion of '%s' -", _hoops_RCCIH), _hoops_PGACC);
		HI_Free_Path (_hoops_GGHPR.next);
		return null;
	}


	return _hoops_GGHPR.next;
}

GLOBAL_FUNCTION void HI_Free_Path (
	_hoops_RSAPR   *_hoops_CIPPR) {

	_hoops_RGGA (_hoops_CIPPR == null) {
		_hoops_RSAPR   *next = _hoops_CIPPR->next;

		if (_hoops_CIPPR->type == _hoops_ARPPR || _hoops_CIPPR->type == _hoops_RGPPR)
			_hoops_RGAIR (_hoops_CIPPR->_hoops_AGPPR);

		FREE (_hoops_CIPPR, _hoops_RSAPR);
		_hoops_CIPPR = next;
	}
}





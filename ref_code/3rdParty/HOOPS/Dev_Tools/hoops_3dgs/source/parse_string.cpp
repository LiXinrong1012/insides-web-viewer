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
 * $Id: obf_tmp.txt 1.32 2010-07-29 22:01:32 jason Exp $
 */

#include "hoops.h"
#include "hc_proto.h"
#include "hi_proto.h"


#define		_hoops_HGACC		1
#define		_hoops_IGACC   -1
struct _hoops_CGACC {
	bool _hoops_SGACC, _hoops_GRACC, _hoops_RRACC, _hoops_CARGA;
	int		_hoops_ARACC;
};


local bool _hoops_PRACC (
	char const				c,
	char const				*_hoops_ICSIH,
	struct _hoops_CGACC		*status,
	int						direction) {

	switch (c) {
		case '(': {
			if (status->_hoops_CARGA && status->_hoops_ARACC == 0) break;
			status->_hoops_ARACC += direction;
			if (status->_hoops_ARACC < 0) status->_hoops_ARACC = 0;
			if (status->_hoops_ARACC == 0) status->_hoops_CARGA = false;
			else status->_hoops_CARGA = true;
		}	break;

		case ')': {
			if (status->_hoops_CARGA && status->_hoops_ARACC == 0) break;
			status->_hoops_ARACC -= direction;
			if (status->_hoops_ARACC < 0) status->_hoops_ARACC = 0;
			if (status->_hoops_ARACC == 0) status->_hoops_CARGA = false;
			else status->_hoops_CARGA = true;
		}	break;

		case '"': {
			if (status->_hoops_CARGA && !status->_hoops_SGACC) break;
			status->_hoops_CARGA = (status->_hoops_SGACC = !status->_hoops_SGACC);
		}	break;

		case '`': {
			if (status->_hoops_CARGA && !status->_hoops_RRACC) break;
			status->_hoops_CARGA = (status->_hoops_RRACC = !status->_hoops_RRACC);
		}	break;

		case '\'': {
			if (status->_hoops_CARGA && !status->_hoops_GRACC) break;
			status->_hoops_CARGA = (status->_hoops_GRACC = !status->_hoops_GRACC);
		}	break;

		default: {
			if (c == *_hoops_ICSIH && !status->_hoops_CARGA) return true;
		}	break;
	}
	return false;
}


GLOBAL_FUNCTION bool HI_Parse_String (
	char const *		string,
	char const *		_hoops_ICSIH,
	int					offset,
	char *				_hoops_CIPPR,
	int					_hoops_CCSIH) {
	char const *		start,
						*end;
	struct _hoops_CGACC	status;

	status._hoops_SGACC = false;
	status._hoops_RRACC = false;
	status._hoops_GRACC = false;
	status._hoops_CARGA = false;
	status._hoops_ARACC  = 0;

	if (offset >= 0) {
		if (offset > 0) {
			_hoops_PCCAR {
				if (*string == '\0') return false;
				if (_hoops_PRACC (*string++, _hoops_ICSIH, &status, _hoops_HGACC))
					if (--offset == 0) break;
			}
		}

		start = string;
		_hoops_RGGA (*string == '\0' ||
			   _hoops_PRACC (*string, _hoops_ICSIH, &status, _hoops_HGACC)) ++string;
		end = string;
	}
	else {
		++offset;		/* _hoops_IRHH _hoops_SCH _hoops_AHHR-_hoops_IIHA */

		start = string;
		do {} _hoops_RGGA (*string++ == '\0');
		end = --string;

		/* _hoops_HSPP _hoops_RSSA _hoops_IS _hoops_RH _hoops_RSGI _hoops_IIGR _hoops_RH _hoops_SHSC _hoops_AHAP _hoops_ARI;
		 * _hoops_GSGR _hoops_PPR _hoops_RSGR _hoops_PPSR _hoops_SPR _hoops_PSAP _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_SHSC _hoops_GSGR.
		 */

		if (offset < 0) {
			_hoops_PCCAR {
				if (string == start) return false;
				if (_hoops_PRACC (*--string, _hoops_ICSIH, &status, _hoops_IGACC))
					if (++offset == 0) break;
			}
			end = string;
		}

		/* _hoops_GSGR _hoops_PPR _hoops_RSGR _hoops_PPSR _hoops_SPR _hoops_PSAP _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HPHR _hoops_AAS,
		 * _hoops_HSPP _hoops_HGGC _hoops_RSSA _hoops_HPGR _hoops_RH _hoops_RSGI _hoops_IIGR _hoops_RH _hoops_SHSC _hoops_AHAP.
		 */

		_hoops_RGGA (string == start) {
			if (_hoops_PRACC (*--string, _hoops_ICSIH, &status, _hoops_IGACC)) {
				start = string + 1;
				break;
			}
		}
	}

	while (start < end && *start == ' ') ++start;
	while (start < end && *(end-1) == ' ') --end;

	HI_Return_Chars (_hoops_CIPPR, _hoops_CCSIH, start, (int)(end - start));
	return true;
}

HC_INTERFACE bool HC_CDECL HC_Parse_String (
	char const *	string,
	char const *	_hoops_ICSIH,
	int				offset,
	char *			_hoops_CIPPR) 
{
	_hoops_PAPPR context("Parse_String");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Parse_String () */\n");
	);

	return HI_Parse_String (string,_hoops_ICSIH,offset,_hoops_CIPPR,-1);
}




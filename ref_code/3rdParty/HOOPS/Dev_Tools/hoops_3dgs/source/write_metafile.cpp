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
 * $Id: obf_tmp.txt 1.419 2010-12-06 22:05:40 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "metafile.h"
#include "patterns.h"
#include "filedata.h"
#include "please.h"
#include "adt.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_METAFILE

#define _hoops_CISAGR 80
#define _hoops_SISAGR 10
#define _hoops_GCSAGR 6

#define _hoops_RCSAGR					0
#define _hoops_ACSAGR					1
#define _hoops_PCSAGR					2

/* _hoops_CACH _hoops_CHGRP._hoops_GSGGR */
extern char const *_hoops_GHIHH[];

/* _hoops_SR _hoops_SGH _hoops_RGR _hoops_GGR _hoops_AGIR _hoops_RH _hoops_IPSP _hoops_SHPH _hoops_RH _hoops_HRSAR _hoops_RGSR */
#define _hoops_HCSAGR	32768

// _hoops_RRSRR _hoops_IH _hoops_PRCA _hoops_ICSAGR _hoops_SGHC _hoops_IGI _hoops_GGR _hoops_GPAC
#define	_hoops_CCSAGR					_hoops_HCIGP(4)		// _hoops_CAGH _hoops_HRGR _hoops_RH _hoops_SCSAGR _hoops_IIGR _hoops_IRS _hoops_PSHS _hoops_CAGH
#define	_hoops_GSSAGR					_hoops_HCIGP(5)		// _hoops_CAGH _hoops_SSCP _hoops_AIAH _hoops_RPII _hoops_AGCA _hoops_GPP _hoops_RH _hoops_ICSAGR _hoops_SIHPA



/* _hoops_RRGC _hoops_IIGR _hoops_CAGH _hoops_PHSSI _hoops_IH _hoops_CSCHR _hoops_CAGH _hoops_HARSI */
struct root {
	_hoops_CRCP const *		segment;
	struct root *		next;
};

struct _hoops_RSSAGR {
	_hoops_AIGPR *	_hoops_RIGC;
	Metafile *				_hoops_PHCIH;
	_hoops_CAGGI *		unnamed;
	struct root *			_hoops_ASSAGR;
	_hoops_IRIPH *				_hoops_GRHRI;
	_hoops_AAPHP *		_hoops_GGRHH;
};


local void _hoops_PSSAGR (
	_hoops_RSSAGR *	info,
	_hoops_CRCP const *		_hoops_SRCP) {
	struct root *		node;

	ALLOC (node, struct root);
	node->next = info->_hoops_ASSAGR;
	info->_hoops_ASSAGR = node;
	node->segment = _hoops_SRCP;
}

local void _hoops_HSSAGR (
	_hoops_RSSAGR *	info) {
	struct root *		node;

	if ((node = info->_hoops_ASSAGR) == null) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Reference chain missing");
		return;
	}

	info->_hoops_ASSAGR = node->next;
	FREE (node, struct root);
}


//	 _hoops_IISH _hoops_RH _hoops_SRGR _hoops_IIGR _hoops_RH _hoops_SCGR _hoops_RGHR _hoops_SRHR _hoops_IS _hoops_IHIAH -- _hoops_GHCA _hoops_SHH _hoops_IRIHH

//	 _hoops_CGP _hoops_GII _hoops_PCPH _hoops_GGR _hoops_RGR _hoops_RPHRA _hoops_HRS _hoops_RCPP, _hoops_IRS _hoops_GGHGI _hoops_SCRII
//	 _hoops_RIHH _hoops_SSCP _hoops_HHIAGR _hoops_PPR _hoops_IRS _hoops_GPSRR _hoops_SSCP _hoops_AIAH _hoops_RPII _hoops_CRPPR.

local bool _hoops_ISSAGR (
	_hoops_IRIPH	*_hoops_GHIPH) {
	int				_hoops_SHGGR;
	_hoops_HCRPR			_hoops_CCCIH, _hoops_SCCIH;
	int				_hoops_HCIS;

	_hoops_SCCIH.length = 0;
	_hoops_SHGGR = _hoops_GHIPH->_hoops_ASAPR - &_hoops_GHIPH->buffer[_hoops_GHIPH->_hoops_RAIPH][0];
	if (_hoops_SHGGR == 0)
		return true;
	if (!_hoops_GHIPH->_hoops_IPIPH) {
		if (!HI_Synch_File_Buffer (_hoops_GHIPH->_hoops_CRIPH, &_hoops_HCIS, &_hoops_CCCIH, &_hoops_SCCIH)) {
			if (_hoops_SCCIH.length != 0) _hoops_GHIPH->_hoops_CAIPH = 2;
			HI_Report_File_Error_With_Names (_hoops_GHIPH, &_hoops_CCCIH, &_hoops_SCCIH);
			return false;
		}
		_hoops_GHIPH->_hoops_IPIPH = false;
	}
	_hoops_SCCIH.length = 0;
	if (!HI_Write_File_Buffer (_hoops_GHIPH->_hoops_CRIPH,
			&_hoops_GHIPH->buffer[_hoops_GHIPH->_hoops_RAIPH][0], _hoops_SHGGR, &_hoops_CCCIH, &_hoops_SCCIH)) {
		if (_hoops_SCCIH.length != 0) _hoops_GHIPH->_hoops_CAIPH = 2;
		HI_Report_File_Error_With_Names (_hoops_GHIPH, &_hoops_CCCIH, &_hoops_SCCIH);
		return false;
	}
	_hoops_GHIPH->_hoops_RAIPH = 1 - _hoops_GHIPH->_hoops_RAIPH;
	_hoops_GHIPH->_hoops_ASAPR = &_hoops_GHIPH->buffer[_hoops_GHIPH->_hoops_RAIPH][0];
	_hoops_GHIPH->_hoops_PSAPR = &_hoops_GHIPH->buffer[_hoops_GHIPH->_hoops_RAIPH][_hoops_PRIPH];
	return true;
}


//	_hoops_CSSAGR _hoops_IAPR _hoops_IH _hoops_IRS _hoops_CCAH _hoops_III

local bool _hoops_SSSAGR (
	_hoops_IRIPH	*_hoops_GHIPH) {
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
	int				_hoops_SAIPH = _hoops_GHIPH->_hoops_SAIPH,
								_hoops_GGGPGR;

	if (_hoops_GHIPH->_hoops_CPIPH)
		return true;

	if (_hoops_SAIPH > _hoops_GHIPH->_hoops_GPIPH - 40) /* _hoops_ARRPA _hoops_ISPR */
		_hoops_SAIPH = _hoops_GHIPH->_hoops_GPIPH - 40;

	if (_hoops_SAIPH <= 0)
		return true;	/* _hoops_IAGRS */

	_hoops_GHIPH->_hoops_RPIPH += _hoops_SAIPH;
	_hoops_GGGPGR = _hoops_SAIPH / 8;
	_hoops_SAIPH -= _hoops_GGGPGR * 8;
	if (_hoops_GHIPH->_hoops_PSAPR - _hoops_ASAPR < _hoops_GGGPGR + _hoops_SAIPH) {
		if (!_hoops_ISSAGR (_hoops_GHIPH))
			return false;
		_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
	} while (--_hoops_GGGPGR >= 0) *_hoops_ASAPR++ = '\t';
	while (--_hoops_SAIPH >= 0) *_hoops_ASAPR++ = ' ';

	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
	return true;
}


/*
 *	_hoops_CRIHH _hoops_PCCP _hoops_CIIA _hoops_SRHR _hoops_IS _hoops_RH _hoops_RGHR _hoops_SRHR.	_hoops_CGP "_hoops_GGR _hoops_GSGR"
 *	_hoops_PSCR _hoops_III _hoops_PGSAH _hoops_SAHR _hoops_HIRGR _hoops_IRS _hoops_RGGPGR.  _hoops_HHPC, _hoops_III _hoops_PGSAH
 *	_hoops_HIRGR _hoops_RH _hoops_SPS _hoops_III _hoops_IS _hoops_SHH _hoops_AGGPGR _hoops_IAPR _hoops_HAHGS->_hoops_AGGRS.
 */

#define _hoops_PGGPGR(_hoops_IGIGGR, _hoops_RPPA, _hoops_SSRPR) do {				\
		_hoops_IGIGGR->_hoops_RPPA = _hoops_RPPA;							\
		if (!_hoops_ISSAGR (_hoops_IGIGGR)) return false;	\
		_hoops_RPPA = _hoops_IGIGGR->_hoops_RPPA;							\
		_hoops_SSRPR = _hoops_IGIGGR->_hoops_SSRPR;							\
	}	while (0)

#define _hoops_HGGPGR(_hoops_IGIGGR, _hoops_RPPA, _hoops_SSRPR, c)		do {	\
		if (_hoops_RPPA == _hoops_SSRPR) _hoops_PGGPGR (_hoops_IGIGGR, _hoops_RPPA, _hoops_SSRPR);	\
		*_hoops_RPPA++ = c;								\
		++_hoops_IGIGGR->_hoops_RPIPH;					\
	}	while (0)

#define _hoops_IGGPGR(_hoops_IGIGGR, _hoops_RPPA, _hoops_SSRPR) do {				\
		_hoops_HGGPGR (_hoops_IGIGGR, _hoops_RPPA, _hoops_SSRPR, '\n');			\
		_hoops_IGIGGR->_hoops_RPIPH = 0;					\
		++_hoops_IGIGGR->_hoops_APIPH;						\
		if (_hoops_IGIGGR->_hoops_CPIPH) {				\
			_hoops_HGGPGR (_hoops_IGIGGR, _hoops_RPPA, _hoops_SSRPR, ';'); 	\
			_hoops_HGGPGR (_hoops_IGIGGR, _hoops_RPPA, _hoops_SSRPR, ';');		\
			_hoops_HGGPGR (_hoops_IGIGGR, _hoops_RPPA, _hoops_SSRPR, ' ');		\
		} \
	}	while (0)

local bool _hoops_CGGPGR (
	_hoops_IRIPH		*_hoops_GHIPH,
	int				_hoops_SGGPGR,
	char			next) {
	local const char			_hoops_GRGPGR[] = "01234567";
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR,
								*_hoops_PSAPR = _hoops_GHIPH->_hoops_PSAPR;

	if (_hoops_GHIPH->_hoops_RPIPH+4 >= _hoops_GHIPH->_hoops_GPIPH)
		_hoops_IGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR);

	_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, '\\');
	if (_hoops_RHHPP (next) >= '0' && _hoops_RHHPP (next) <= '7') {
		_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, _hoops_GRGPGR[_hoops_SGGPGR/0100 % 010]);
		_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, _hoops_GRGPGR[_hoops_SGGPGR/010 % 010]);
	}
	else {
		if (_hoops_SGGPGR > 077)
			_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, _hoops_GRGPGR[_hoops_SGGPGR/0100 % 010]);
		if (_hoops_SGGPGR > 07)
			_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, _hoops_GRGPGR[_hoops_SGGPGR/010 % 010]);
	}
	_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, _hoops_GRGPGR[_hoops_SGGPGR % 010]);

	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
	return true;
}


/* _hoops_AHPA _hoops_GAS _hoops_IHSA _hoops_SGGGH _hoops_SGS _hoops_SR _hoops_ACRR (_hoops_RRGPGR) */
#define _hoops_ARGPGR		80

local bool _hoops_PRGPGR (
	_hoops_IRIPH		*_hoops_GHIPH,
	char			*_hoops_HRGPGR) {
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
	char			*_hoops_PSAPR = _hoops_GHIPH->_hoops_PSAPR;
	char			_hoops_HPRS[_hoops_ARGPGR];
	char			*_hoops_IRGPGR;
	int				_hoops_HAHC;

	if (_hoops_ASAPR != _hoops_HRGPGR) {
		/* _hoops_SRCH _hoops_IRS _hoops_GRCIR _hoops_RPGR */
		if (_hoops_ASAPR[-1] == ' ') --_hoops_ASAPR;

		/* _hoops_SRCH _hoops_IRS _hoops_CPGHR '(' _hoops_GPP _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_III */
		if (_hoops_HRGPGR > &_hoops_GHIPH->buffer[_hoops_GHIPH->_hoops_RAIPH][0] &&
			_hoops_HRGPGR[-1] == '(')
			--_hoops_HRGPGR;
	}

	if (_hoops_ASAPR == _hoops_HRGPGR) {
		_hoops_HAHC = 0;
		_hoops_IRGPGR = _hoops_HPRS;
	}
	else {
		/* _hoops_ASAC _hoops_RH _hoops_ARIP _hoops_RAS _hoops_RH _hoops_CGHI-_hoops_RIRA-_hoops_IHSA,
		 * _hoops_PPR _hoops_ACASA.
		 */
		_hoops_HAHC = _hoops_ASAPR - _hoops_HRGPGR;
		_hoops_IRGPGR = &_hoops_HPRS[_hoops_HAHC];
		do *--_hoops_IRGPGR = *--_hoops_ASAPR;
		_hoops_RGGA (_hoops_ASAPR == _hoops_HRGPGR);
	}

	_hoops_IGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR);
	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
	if (!_hoops_SSSAGR (_hoops_GHIPH))
		return false;
	_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
	_hoops_GHIPH->_hoops_RPIPH += _hoops_HAHC;
	_hoops_RGGA (--_hoops_HAHC < 0) *_hoops_ASAPR++ = *_hoops_IRGPGR++;
	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
	return true;
}


local bool _hoops_CRGPGR (
	_hoops_IRIPH		*_hoops_GHIPH,
	char const		*_hoops_SRGPGR) {
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR,
								*_hoops_PSAPR = _hoops_GHIPH->_hoops_PSAPR;
	int				_hoops_SGGPGR;

	_hoops_PCCAR {
		if (_hoops_GHIPH->user_data == _hoops_RCSAGR) _hoops_PCCAR {
			_hoops_SGGPGR = _hoops_IRGCR (*_hoops_SRGPGR++);

			if (_hoops_SGGPGR == '\0') {
				_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
				return true;
			}

			if (_hoops_GHIPH->_hoops_RPIPH >= _hoops_GHIPH->_hoops_GPIPH)
				_hoops_IGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR);

			if (_hoops_RHHPP (_hoops_SGGPGR) >= 32 && _hoops_RHHPP (_hoops_SGGPGR) <= 126) {
				_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, _hoops_SGGPGR);

				if (_hoops_SGGPGR == '"') {
					if (*_hoops_SRGPGR == '\0') {
						_hoops_GHIPH->user_data = _hoops_PCSAGR;
						_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
						return true;
					}
					else {
						_hoops_GHIPH->user_data = _hoops_ACSAGR;
						break; /* _hoops_HAPR _hoops_ISHP _hoops_IS _hoops_RH '_hoops_GSSR' _hoops_HARPR */
					}
				}
				else if (_hoops_SGGPGR == '\\') {
					if (_hoops_GHIPH->_hoops_RPIPH >= _hoops_GHIPH->_hoops_GPIPH - 1)
						_hoops_IGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR);
					_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, '\\');
				}
			}
			else {
				_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
				if (!_hoops_CGGPGR (_hoops_GHIPH, _hoops_SGGPGR, *_hoops_SRGPGR))
					return false;
				_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
				_hoops_PSAPR = _hoops_GHIPH->_hoops_PSAPR;
			}
		}
		else {
			char			*_hoops_HRGPGR;

			if (_hoops_GHIPH->user_data == _hoops_PCSAGR &&
				*_hoops_SRGPGR != ')' && *_hoops_SRGPGR != '\n') {
				if (_hoops_GHIPH->_hoops_RPIPH >= _hoops_GHIPH->_hoops_GPIPH) {
					_hoops_IGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR);
					_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
					if (!_hoops_SSSAGR (_hoops_GHIPH))
						return false;
					_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
					_hoops_PSAPR = _hoops_GHIPH->_hoops_PSAPR;
				}
				else {
					_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, ' ');
				}
			}

#			define		_hoops_GAGPGR()		do {			\
					if (_hoops_PSAPR - _hoops_ASAPR < _hoops_ARGPGR)	\
						_hoops_PGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR);		\
					_hoops_HRGPGR = _hoops_ASAPR;				\
				}		while (0)

			_hoops_GAGPGR();

			_hoops_PCCAR {
				if ((_hoops_SGGPGR = _hoops_IRGCR (*_hoops_SRGPGR)) == '\0') {
					_hoops_GHIPH->user_data = _hoops_PCSAGR;
					_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
					return true;
				}

				++_hoops_SRGPGR;

				if (_hoops_GHIPH->_hoops_RPIPH >= _hoops_GHIPH->_hoops_GPIPH) {
					_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
					if (!_hoops_PRGPGR (_hoops_GHIPH, _hoops_HRGPGR))
						return false;

					/* _hoops_RAGPGR _hoops_GH _hoops_IHH _hoops_RPGR, _hoops_RPP _hoops_SR _hoops_HS _hoops_SGGGH _hoops_RAS _hoops_ARGAR*/
					if (_hoops_SGGPGR == ' ' &&
						_hoops_GHIPH->_hoops_ASAPR != _hoops_GHIPH->buffer[_hoops_GHIPH->_hoops_RAIPH] &&
						(_hoops_GHIPH->_hoops_ASAPR[-1] == ' ' || _hoops_GHIPH->_hoops_ASAPR[-1] == '\t')) {
						if ((_hoops_SGGPGR = _hoops_IRGCR (*_hoops_SRGPGR)) == '\0') {
							_hoops_GHIPH->user_data = _hoops_ACSAGR;
							return true;
						}
						++_hoops_SRGPGR;
					}

					_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
					_hoops_PSAPR = _hoops_GHIPH->_hoops_PSAPR;
					_hoops_GAGPGR ();
				}

				*_hoops_ASAPR++ = (char)_hoops_SGGPGR;
				++_hoops_GHIPH->_hoops_RPIPH;

				switch (_hoops_SGGPGR) {
					case '(': {
						++_hoops_GHIPH->_hoops_SAIPH;

						if (*_hoops_SRGPGR == '\0') {
							_hoops_GHIPH->user_data = _hoops_ACSAGR;
							_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
							return true;
						}

						_hoops_GAGPGR ();
					}	break;

					case ')': {
						--_hoops_GHIPH->_hoops_SAIPH;

						if (*_hoops_SRGPGR == '\0') {
							_hoops_GHIPH->user_data = _hoops_PCSAGR;
							_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
							return true;
						}

						_hoops_GAGPGR ();
					}	break;

					case '"': {
						_hoops_GHIPH->user_data = _hoops_RCSAGR;
						goto _hoops_PCPPR;	/* _hoops_HAPR _hoops_ISSC _hoops_IS '_hoops_GGR _hoops_GSGR' _hoops_AGIR */
					}	/* _hoops_IHSA; */

					case ' ': {
						_hoops_GAGPGR ();
					}	break;

					case '\n': {
						--_hoops_ASAPR;	/* _hoops_HIS _hoops_SR _hoops_PAH _hoops_SGH _hoops_RH _hoops_AAGPGR _hoops_RIGR */
						_hoops_IGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR);
						_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
						if (!_hoops_SSSAGR (_hoops_GHIPH))
							return false;

						if (*_hoops_SRGPGR == '\0') {
							_hoops_GHIPH->user_data = _hoops_ACSAGR;
							return true;
						}

						_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
						_hoops_PSAPR = _hoops_GHIPH->_hoops_PSAPR;
						_hoops_GAGPGR ();
					}	break;
				}
			}
			_hoops_PCPPR:;
		}
	}
}


local bool _hoops_PAGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	char const		*_hoops_SRGPGR,
		long count) {
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR,
								*_hoops_PSAPR = _hoops_GHIPH->_hoops_PSAPR;
	int				_hoops_SGGPGR;

	_hoops_PCCAR {
		_hoops_SGGPGR = _hoops_IRGCR (*_hoops_SRGPGR); _hoops_SRGPGR++;

		if (count == -1) {
			if (_hoops_SGGPGR == '\0') {
				_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
				return true;
			}
		}
		else {
			if (count-- == 0) {
				_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
				return true;
			}
		}

		if (_hoops_GHIPH->_hoops_RPIPH >= _hoops_GHIPH->_hoops_GPIPH)
			_hoops_IGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR);

		if (_hoops_SGGPGR == '"' || _hoops_SGGPGR == '\\') {
			_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, '\\');
			if (_hoops_GHIPH->_hoops_RPIPH >= _hoops_GHIPH->_hoops_GPIPH)
				_hoops_IGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR);
			_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, _hoops_SGGPGR);
		}
		else if (_hoops_RHHPP (_hoops_SGGPGR) >= 32 && _hoops_RHHPP (_hoops_SGGPGR) <= 126) {
			_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, _hoops_SGGPGR);
		}
		else {
			_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
			if (!_hoops_CGGPGR (_hoops_GHIPH, _hoops_SGGPGR, *_hoops_SRGPGR))
				return false;
			_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
			_hoops_PSAPR = _hoops_GHIPH->_hoops_PSAPR;
		}
	}
}


/*
 *	_hoops_HAGPGR _hoops_IAGPGR _hoops_CPRAA _hoops_CPARA (") _hoops_AARI _hoops_RH _hoops_CIIA _hoops_SRHR.
 */
local bool _hoops_CAGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	char const		*_hoops_SRGPGR) {

	return (_hoops_CRGPGR (_hoops_GHIPH, "\"") &&
			_hoops_PAGPGR (_hoops_GHIPH, _hoops_SRGPGR, -1) &&
			_hoops_CRGPGR (_hoops_GHIPH, "\""));
}

/*
 * _hoops_HAGPGR _hoops_IAGPGR _hoops_CPRAA _hoops_CPARA (") _hoops_AARI _hoops_RH _hoops_CIIA _hoops_SRHR.
 */
local bool _hoops_SAGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	char const		*_hoops_SRGPGR,
	long			count) {

	return (_hoops_CRGPGR (_hoops_GHIPH, "\"") &&
			_hoops_PAGPGR (_hoops_GHIPH, _hoops_SRGPGR, count) &&
			_hoops_CRGPGR (_hoops_GHIPH, "\""));
}


/*
 *	_hoops_HAGPGR _hoops_GPGPGR () _hoops_IS _hoops_GGCR _hoops_RPGPGR _hoops_PIH _hoops_IS _hoops_RH _hoops_IIPR _hoops_SRHR
 */
local bool _hoops_APGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	char const		*format,
	void const		*data) {
	char			buf[MAX_ERRMSG];
	char			*_hoops_ASAPR = buf,
								*_hoops_PSAPR = buf+_hoops_GGAPR(buf)-1;

	_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, format, data);

	if (_hoops_ASAPR == null) {
		_hoops_GHIPH->message = "Error formatting metafile data";
		HI_Report_File_Error (_hoops_GHIPH);
		(void)_hoops_ISSAGR (_hoops_GHIPH);
		return false;
	}

	*_hoops_ASAPR++ = '\0';
	if (_hoops_GHIPH->_hoops_PSAPR - _hoops_GHIPH->_hoops_ASAPR < _hoops_ASAPR - buf && !_hoops_ISSAGR (_hoops_GHIPH))
		return false;

	if (format[0] == '%' && format[1] == 'p') {
		/*** _hoops_RCASA _hoops_IS _hoops_AGRP @'_hoops_GRI _hoops_IS _hoops_RRI _hoops_PPGPGR #'_hoops_GRI _hoops_GGR _hoops_CRAA _hoops_RPPCR ***/
		if (*(_hoops_ASAPR = buf) != '\0') do {
			if (*_hoops_ASAPR == '@')
				*_hoops_ASAPR = '#';
		} while (*++_hoops_ASAPR != '\0');
	}

	if (_hoops_GHIPH->user_data != _hoops_RCSAGR)
		return _hoops_CRGPGR (_hoops_GHIPH, buf);
	else
		return _hoops_PAGPGR (_hoops_GHIPH, buf, -1);
}


local bool _hoops_HPGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	_hoops_HCRPR const	*_hoops_IPGPGR) {
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR,
								*_hoops_PSAPR = _hoops_GHIPH->_hoops_PSAPR;
	char const		*_hoops_SRGPGR;
	int				length;
	int				_hoops_SGGPGR;
	_hoops_HCRPR			_hoops_CPSGI;

	HI_Decode_User_Option(*_hoops_IPGPGR, _hoops_CPSGI);
	_hoops_SRGPGR = _hoops_CPSGI.text;
	length = _hoops_CPSGI.length;

	/* _hoops_PII _hoops_CCHRC-_hoops_GGR-_hoops_GSGR, _hoops_AHSAR _hoops_RH _hoops_GSGR _hoops_HRGR _hoops_SGAAH _hoops_HRII _hoops_HSAR
	 * _hoops_AHHR-_hoops_CCGAI.
	 */

	_hoops_RGGA (--length < 0) {
		_hoops_SGGPGR = _hoops_IRGCR (*_hoops_SRGPGR++);

		if (_hoops_GHIPH->_hoops_RPIPH >= _hoops_GHIPH->_hoops_GPIPH)
			_hoops_IGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR);

		if (_hoops_SGGPGR == '"' || _hoops_SGGPGR == '\\') {
			_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, '\\');
			if (_hoops_GHIPH->_hoops_RPIPH >= _hoops_GHIPH->_hoops_GPIPH)
				_hoops_IGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR);
			_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, _hoops_SGGPGR);
		}
		else if (_hoops_RHHPP (_hoops_SGGPGR) >= 32 && _hoops_RHHPP (_hoops_SGGPGR) <= 126) {
			_hoops_HGGPGR (_hoops_GHIPH, _hoops_ASAPR, _hoops_PSAPR, _hoops_SGGPGR);
		}
		else {
			_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
			if (!_hoops_CGGPGR (_hoops_GHIPH, _hoops_SGGPGR,
				(char) ((length == 0) ? '\0' : *_hoops_SRGPGR))) {
				_hoops_RGAIR(_hoops_CPSGI);
				return false;
			}
			_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
			_hoops_PSAPR = _hoops_GHIPH->_hoops_PSAPR;
		}
	}
	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
	_hoops_RGAIR(_hoops_CPSGI);
	return true;
}

local int _hoops_CPGPGR(_hoops_PGGSA::Pair * a, _hoops_PGGSA::Pair * b, void const * const data)
{
	if (a->Key() < b->Key()) {
		return -1;
	}
	else if (a->Key() > b->Key()) {
		return 1;
	}
	else if (a->Item() < b->Item()) {
		return -1;
	}
	else if (a->Item() > b->Item()) {
		return 1;
	}
	return 0;
	UNREFERENCED(data);
}


local int _hoops_SPGPGR(_hoops_GISCA::Pair * a, _hoops_GISCA::Pair * b, void const * const data)
{
	if (a->Key() < b->Key()) {
		return -1;
	}
	else if (a->Key() > b->Key()) {
		return 1;
	}
	return 0;
	UNREFERENCED(data);
}

local bool _hoops_GHGPGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	_hoops_HPPIR const *	_hoops_AHHRGR) {
	_hoops_HPPIR const *	user_options;
	Option_Value *			_hoops_CSCIR;

	if (_hoops_AHHRGR->_hoops_IGGSA)
		user_options = HI_Distill_User_Options(_hoops_RIGC, _hoops_AHHRGR, _hoops_ACIAP);
	else
		user_options = _hoops_AHHRGR;

	_hoops_CSCIR = user_options->option_list;
	if (_hoops_CSCIR != null) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "(User_Options \""))
			goto FAILED;

		_hoops_PCCAR {
			int				_hoops_RHSAA;

			if (_hoops_CSCIR->type->_hoops_RCIIR != _hoops_HRSAP)
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "Unexpected option type");
			else if (_hoops_CSCIR->_hoops_GCACR) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "no ")	 ||
					!_hoops_HPGPGR (_hoops_GHIPH, &_hoops_CSCIR->type->name))
					goto FAILED;
			}
			else if ((_hoops_RHSAA = _hoops_CSCIR->_hoops_AIPCR) == 0) {
				if (!_hoops_HPGPGR (_hoops_GHIPH, &_hoops_CSCIR->type->name))
					goto FAILED;
			}
			else if (_hoops_RHSAA == 1) {
				if (!_hoops_HPGPGR (_hoops_GHIPH, &_hoops_CSCIR->type->name))
					goto FAILED;
				if (!_hoops_CRGPGR (_hoops_GHIPH, "="))
					goto FAILED;
				if (!_hoops_HPGPGR (_hoops_GHIPH, &_hoops_CSCIR->value._name[0]))
					goto FAILED;
			}
			else {
				int		_hoops_RHGPGR = 0;

				if (!_hoops_HPGPGR (_hoops_GHIPH, &_hoops_CSCIR->type->name))
					goto FAILED;
				if (!_hoops_CRGPGR (_hoops_GHIPH, "=("))
					goto FAILED;

				do {
					if (_hoops_RHGPGR > 0) if (!_hoops_CRGPGR (_hoops_GHIPH, ","))
						goto FAILED;
					if (!_hoops_HPGPGR (_hoops_GHIPH, &_hoops_CSCIR->value._name[_hoops_RHGPGR]))
						goto FAILED;
				} _hoops_RGGA (++_hoops_RHGPGR == _hoops_RHSAA);

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					goto FAILED;
			}

			if ((_hoops_CSCIR = _hoops_CSCIR->next) == null) break;

			/* _hoops_GGCR ',' _hoops_GAPA _hoops_APSAR */
			if (!_hoops_CRGPGR (_hoops_GHIPH, ","))
				goto FAILED;
		}

		if (!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
			goto FAILED;
	}

	_hoops_CSCIR = user_options->_hoops_APICA;
	if (_hoops_CSCIR != null) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "(Unicode_Options \""))
			goto FAILED;

		_hoops_PCCAR {
			_hoops_RPSAP *_hoops_HCGCC = (_hoops_RPSAP *)_hoops_CSCIR->type;
			int				_hoops_RHSAA;
			char			scratch[4096];
			char			*_hoops_ASAPR = scratch;

			if (_hoops_HCGCC->_hoops_RCIIR != _hoops_CRSAP)
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "Unexpected option type");
			else if (_hoops_CSCIR->_hoops_GCACR) {
				*_hoops_ASAPR++ = '\0';	*_hoops_ASAPR++ = 'n';
				*_hoops_ASAPR++ = '\0';	*_hoops_ASAPR++ = 'o';
				*_hoops_ASAPR++ = '\0';	*_hoops_ASAPR++ = ' ';
				HI_Return_Kars (_hoops_ASAPR, -1, _hoops_HCGCC->_hoops_SIHSA._hoops_IPPPP,
								_hoops_HCGCC->_hoops_SIHSA.length, _hoops_RGHPH);
				if (!_hoops_PAGPGR (_hoops_GHIPH, scratch,
											     2*_hoops_HCGCC->_hoops_SIHSA.length + 6))
					goto FAILED;
			}
			else if ((_hoops_RHSAA = _hoops_CSCIR->_hoops_AIPCR) == 0) {
				HI_Return_Kars (_hoops_ASAPR, -1, _hoops_HCGCC->_hoops_SIHSA._hoops_IPPPP,
								_hoops_HCGCC->_hoops_SIHSA.length, _hoops_RGHPH);
				if (!_hoops_PAGPGR (_hoops_GHIPH, scratch,
											   2*_hoops_HCGCC->_hoops_SIHSA.length))
					goto FAILED;
			}
			else if (_hoops_RHSAA == 1) {
				HI_Return_Kars (_hoops_ASAPR, -1, _hoops_HCGCC->_hoops_SIHSA._hoops_IPPPP,
								_hoops_HCGCC->_hoops_SIHSA.length, _hoops_RGHPH);
				_hoops_ASAPR += 2*_hoops_HCGCC->_hoops_SIHSA.length;
				*_hoops_ASAPR++ = '\0';	*_hoops_ASAPR++ = '=';

				KName _hoops_CPSGI;
				HI_Decode_Unicode_User_Option(_hoops_CSCIR->value._hoops_HGSAP[0], _hoops_CPSGI);
				HI_Return_Kars (_hoops_ASAPR, -1, _hoops_CPSGI._hoops_IPPPP, _hoops_CPSGI.length, _hoops_RGHPH);
				_hoops_ASAPR += 2*_hoops_CPSGI.length;
				_hoops_PRPIR(_hoops_CPSGI);

				if (!_hoops_PAGPGR (_hoops_GHIPH, scratch, _hoops_ASAPR-scratch))
					goto FAILED;
			}
			else {
				int		_hoops_RHGPGR = 0;

				HI_Return_Kars (_hoops_ASAPR, -1, _hoops_HCGCC->_hoops_SIHSA._hoops_IPPPP,
								_hoops_HCGCC->_hoops_SIHSA.length, _hoops_RGHPH);
				_hoops_ASAPR += 2*_hoops_HCGCC->_hoops_SIHSA.length;
				*_hoops_ASAPR++ = '\0';	*_hoops_ASAPR++ = '=';
				*_hoops_ASAPR++ = '\0';	*_hoops_ASAPR++ = '(';

				do {
					if (_hoops_RHGPGR > 0) {
						*_hoops_ASAPR++ = '\0';	*_hoops_ASAPR++ = ',';
					}

					KName _hoops_CPSGI;
					HI_Decode_Unicode_User_Option(_hoops_CSCIR->value._hoops_HGSAP[_hoops_RHGPGR], _hoops_CPSGI);
					HI_Return_Kars (_hoops_ASAPR, -1, _hoops_CPSGI._hoops_IPPPP, _hoops_CPSGI.length, _hoops_RGHPH);
					_hoops_ASAPR += 2*_hoops_CPSGI.length;
					_hoops_PRPIR(_hoops_CPSGI);
				} _hoops_RGGA (++_hoops_RHGPGR == _hoops_RHSAA);

				*_hoops_ASAPR++ = '\0';	*_hoops_ASAPR++ = ')';

				if (!_hoops_PAGPGR (_hoops_GHIPH, scratch,
										   _hoops_ASAPR-scratch))
					goto FAILED;
			}

			if ((_hoops_CSCIR = _hoops_CSCIR->next) == null) break;

			/* _hoops_GGCR ',' _hoops_GAPA _hoops_APSAR */
			scratch[0] = '\0';	scratch[1] = ',';
			if (!_hoops_PAGPGR (_hoops_GHIPH, scratch, 2))
				goto FAILED;
		}

		if (!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
			goto FAILED;
	}

	if (user_options->_hoops_AGGSA) {
		_hoops_PGGSA::PairList * _hoops_ARIRI = user_options->_hoops_AGGSA->GetPairList();
		_hoops_ARIRI->Sort(_hoops_CPGPGR);
		_hoops_PGGSA::Pair * p;
		while ((p = _hoops_ARIRI->PeekCursor()) != 0) {
			long key = p->Key();
			void * item = p->Item();
			if (
				!_hoops_CRGPGR (_hoops_GHIPH, "(User_Index ") ||
				!_hoops_APGPGR (_hoops_GHIPH, "%D ", (void*)&key) ||
				!_hoops_APGPGR (_hoops_GHIPH, "0x%X", (void*)&item) ||
				!_hoops_CRGPGR (_hoops_GHIPH, ")\n")) {
					delete _hoops_ARIRI;
					goto FAILED;
				}
			_hoops_ARIRI->AdvanceCursor();
		}
		delete _hoops_ARIRI;
	}

	if (user_options->_hoops_HGGSA) {
		_hoops_GISCA::PairList * _hoops_ARIRI = user_options->_hoops_HGGSA->GetPairList();
		_hoops_ARIRI->Sort(_hoops_SPGPGR);
		_hoops_GISCA::Pair * p;
		while ((p = _hoops_ARIRI->PeekCursor()) != 0) {
			POINTER_SIZED_INT key = p->Key();
			_hoops_IHSCA * _hoops_CRHRGR = p->Item();

			if (!_hoops_CRGPGR (_hoops_GHIPH, "(User_Data") ||
				!_hoops_APGPGR (_hoops_GHIPH, "0x%X", (void*)&key) ||
				!_hoops_APGPGR (_hoops_GHIPH, "%D", (void*)&_hoops_CRHRGR->data_length)) {
				delete _hoops_ARIRI;
				goto FAILED;
			}

			const char * data = (const char *)_hoops_CRHRGR->data;
			int i;

			for (i=0; i<_hoops_CRHRGR->data_length; i++) {
				POINTER_SIZED_INT value = POINTER_SIZED_INT(0xff & data[i]);
				if (!_hoops_APGPGR (_hoops_GHIPH, "0x%X", (void*)&value)) {
					delete _hoops_ARIRI;
					goto FAILED;
				}
			}

			if (!_hoops_CRGPGR (_hoops_GHIPH, ")\n")) {
				delete _hoops_ARIRI;
				goto FAILED;
			}

			_hoops_ARIRI->AdvanceCursor();
		}
		delete _hoops_ARIRI;
	}


	if (user_options != _hoops_AHHRGR)
		_hoops_HPRH(user_options);

	return true;

FAILED:

	if (user_options != _hoops_AHHRGR)
		_hoops_HPRH(user_options);

	return false;
}


local bool _hoops_AHGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	Point const	*p) {

	return (_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&p->x) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&p->y) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&p->z));
}
local bool _hoops_PHGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	Vector const	*p) {

	return (_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&p->x) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&p->y) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&p->z));
}
local bool _hoops_HHGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	_hoops_ARPA const	*p) {

	return (_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&p->a) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&p->b) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&p->c) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&p->d));
}


local bool _hoops_IHGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	Point const	*p) {

	return (_hoops_CRGPGR (_hoops_GHIPH, "(") &&
			_hoops_AHGPGR (_hoops_GHIPH, p) &&
			_hoops_CRGPGR (_hoops_GHIPH, ")"));
}
local bool _hoops_CHGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	Vector const	*p) {

	return (_hoops_CRGPGR (_hoops_GHIPH, "(") &&
			_hoops_PHGPGR (_hoops_GHIPH, p) &&
			_hoops_CRGPGR (_hoops_GHIPH, ")"));
}

/*
 *	 _hoops_IISH _hoops_IRS _hoops_RSGA _hoops_GAGHR
 */
local bool _hoops_SHGPGR (
	_hoops_IRIPH *		_hoops_GHIPH,
	float const *	f) {

	return (_hoops_CRGPGR (_hoops_GHIPH, "(") &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&f[0]) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&f[1]) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&f[2]) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&f[3]) &&
			_hoops_CRGPGR (_hoops_GHIPH, ")"));
}


/*
 *	_hoops_AHGHR _hoops_IRS _hoops_HAIR _hoops_GPRR, _hoops_GIHII _hoops_RH _hoops_IRPR _hoops_HCGR _hoops_RSIRR
 */
local char *_hoops_SPPRA (
	Color_Object type) {

	switch (type) {
		case Color_FRONT:				return (char *)"Front";
		case Color_BACK:				return (char *)"Back";
		case Color_EDGE:				return (char *)"Edge";
		case Color_LINE:				return (char *)"Line";
		case Color_VERTEX:				return (char *)"Vertex";
		case Color_MARKER:				return (char *)"Marker Only";
		case Color_TEXT:				return (char *)"Text";
		case Color_CUT_FACE:			return (char *)"Cut Face";
		case Color_CUT_EDGE:			return (char *)"Cut Edge";
		case Color_WINDOW:				return (char *)"Window";
		case _hoops_SGARA:	return (char *)"Simple Reflection";
		case _hoops_RRARA:		return (char *)"Front Contrast";
		case _hoops_GRARA:		return (char *)"Back Contrast";
		case Color_EDGE_CONTRAST:		return (char *)"Edge Contrast";
		case Color_LINE_CONTRAST:		return (char *)"Line Contrast";
		case Color_VERTEX_CONTRAST:		return (char *)"Vertex Contrast";
		case Color_MARKER_CONTRAST:		return (char *)"Marker Contrast";
		case Color_TEXT_CONTRAST:		return (char *)"Text Contrast";
		case _hoops_HGARA:	return (char *)"Cut Face Contrast";
		case _hoops_PGARA:	return (char *)"Cut Edge Contrast";
		case Color_WINDOW_CONTRAST:		return (char *)"Window Contrast";
		case Color_LIGHTING:			return (char *)"Lighting";
		case _hoops_PRARA:			return (char *)"Ambient Up";
		case _hoops_HRARA:		return (char *)"Ambient Down";

		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Can't choose color name");
			return (char *)"oops";
		}
	}
}


local bool _hoops_GIGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	Color_Object _hoops_GHA,
	char const		*_hoops_AHPRA) {
	bool		_hoops_RIGPGR = false;
	Color_Object next;

	if (ALLBITS (_hoops_GHA, Color_EVERYTHING)) {
		return _hoops_CRGPGR (_hoops_GHIPH, "Everything");
	}

	if (ALLBITS (_hoops_GHA, Color_GEOMETRY)) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "Geometry"))
			return false;
		_hoops_GHA &= ~Color_GEOMETRY;
		_hoops_RIGPGR = true;
	}

	if (ALLBITS (_hoops_GHA, Color_POLYGON)) {
		if (_hoops_RIGPGR  &&
			!_hoops_CRGPGR (_hoops_GHIPH, _hoops_AHPRA))
			return false;

		if (!_hoops_CRGPGR (_hoops_GHIPH, "Polygon"))
			return false;
		_hoops_GHA &= ~Color_POLYGON;
		_hoops_RIGPGR = true;
	}

	if (ALLBITS (_hoops_GHA, Color_FACE)) {
		if (_hoops_RIGPGR  &&
			!_hoops_CRGPGR (_hoops_GHIPH, _hoops_AHPRA))
			return false;

		if (!_hoops_CRGPGR (_hoops_GHIPH, "Face"))
			return false;
		_hoops_GHA &= ~Color_FACE;
		_hoops_RIGPGR = true;
	}

	if (ALLBITS (_hoops_GHA, Color_MARKER|Color_VERTEX)) {
		if (_hoops_RIGPGR  &&
			!_hoops_CRGPGR (_hoops_GHIPH, _hoops_AHPRA))
			return false;

		if (!_hoops_CRGPGR (_hoops_GHIPH, "Marker"))
			return false;
		_hoops_GHA &= ~(Color_MARKER|Color_VERTEX);
		_hoops_RIGPGR = true;
	}

	if (ALLBITS (_hoops_GHA, Color_FACE_CONTRAST)) {
		if (_hoops_RIGPGR  &&
			!_hoops_CRGPGR (_hoops_GHIPH, _hoops_AHPRA))
			return false;

		if (!_hoops_CRGPGR (_hoops_GHIPH, "Face Contrast"))
			return false;
		_hoops_GHA &= ~Color_FACE_CONTRAST;
		_hoops_RIGPGR = true;
	}

	if (ALLBITS (_hoops_GHA, Color_CUT_GEOMETRY)) {
		if (_hoops_RIGPGR  &&
			!_hoops_CRGPGR (_hoops_GHIPH, _hoops_AHPRA))
			return false;

		if (!_hoops_CRGPGR (_hoops_GHIPH, "Cut Geometry"))
			return false;
		_hoops_GHA &= ~Color_CUT_GEOMETRY;
		_hoops_RIGPGR = true;
	}

	if (ALLBITS (_hoops_GHA, _hoops_IGARA)) {
		if (_hoops_RIGPGR  &&
			!_hoops_CRGPGR (_hoops_GHIPH, _hoops_AHPRA))
			return false;

		if (!_hoops_CRGPGR (_hoops_GHIPH, "Cut Geometry CONTRAST"))
			return false;
		_hoops_GHA &= ~_hoops_IGARA;
		_hoops_RIGPGR = true;
	}

	if (ALLBITS (_hoops_GHA, _hoops_IRARA)) {
		if (_hoops_RIGPGR  &&
			!_hoops_CRGPGR (_hoops_GHIPH, _hoops_AHPRA))
			return false;

		if (!_hoops_CRGPGR (_hoops_GHIPH, "Ambient"))
			return false;
		_hoops_GHA &= ~_hoops_IRARA;
		_hoops_RIGPGR = true;
	}

	while (_hoops_GHA != 0) {
		if (_hoops_RIGPGR && !_hoops_CRGPGR (_hoops_GHIPH, _hoops_AHPRA))
			return false;

		next = _hoops_RIII(_hoops_GHA);

		if (!_hoops_CRGPGR (_hoops_GHIPH, _hoops_SPPRA (next)))
			return false;

		_hoops_GHA &= ~next;
		_hoops_RIGPGR = true;
	}

	return true;
}



local bool _hoops_AIGPGR (
	_hoops_IRIPH *				_hoops_GHIPH,
	Named_Material const *	_hoops_ISHIR) {

#define _hoops_PIGPGR 4096
	char buffer[_hoops_PIGPGR];
	char * _hoops_ASAPR;

	if ((_hoops_ASAPR = HI_Show_Material (buffer, buffer+_hoops_PIGPGR, _hoops_ISHIR, null, true)) == null)
		return false;

	*_hoops_ASAPR='\0';

	if (!_hoops_PAGPGR (_hoops_GHIPH, buffer, -1))
		return false;

	return true;
}



local bool _hoops_HIGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	Attribute	*_hoops_ASGPR,
	bool		_hoops_IIGPGR) {
	_hoops_SSGI		*color = (_hoops_SSGI *)_hoops_ASGPR;
	_hoops_ACSGA	*list;
	bool		_hoops_CIGPGR = false,
								_hoops_SIGPGR = false,
								_hoops_GCGPGR = false;

	list = color->colors;
	do {
		if (list->type == _hoops_SHGRA) {
			_hoops_GCGPGR = true;
		}
		else if (!_hoops_IIGPGR ||
				 list->type == _hoops_PPCA &&
				  ((_hoops_APCA const *)list)->name.length == 0 ||
				list->type == _hoops_GIGRA &&
				  ((_hoops_HCSGA const *)list)->name.length == 0) {
			_hoops_SIGPGR = true;
		}
		else {
			/* _hoops_IGHS _hoops_HAIR _hoops_RPPCR, _hoops_HAR _hoops_HSH */
			if (_hoops_CIGPGR) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, ", "))
					return false;
			}
			else {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Color \""))
					return false;
			}

			if (!_hoops_GIGPGR (_hoops_GHIPH, list->_hoops_GHA, "="))
				return false;

			if (!_hoops_CRGPGR (_hoops_GHIPH, "="))
				return false;

			if (list->type == _hoops_PPCA) {
				_hoops_APCA const *		normal = (_hoops_APCA const *)list;

				if (!_hoops_APGPGR (_hoops_GHIPH, "%n", (void *)&normal->name))
					return false;
			}
			else {
				_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

				if (!_hoops_APGPGR (_hoops_GHIPH, "%n", (void *)&_hoops_ICSGA->name))
					return false;
			}

			_hoops_CIGPGR = true;
		} /* _hoops_SHS, _hoops_IGHS _hoops_HAIR _hoops_RPPCR, _hoops_HAR _hoops_HSH */
	} while ((list = list->next) != null);

	if (_hoops_CIGPGR && !_hoops_CRGPGR (_hoops_GHIPH, "\")"))
		return false;


	/****		_hoops_RGR _hoops_RHAP _hoops_HAR _hoops_HASC _hoops_PSHA _hoops_IIGR _hoops_PSHR _hoops_PIRA _hoops_PGAP			*****
	*****		_hoops_AAPR _hoops_ARP _hoops_GAR _hoops_HAGH _hoops_RPPCR								****/

	if (_hoops_GCGPGR || _hoops_SIGPGR) {
		list = color->colors;
		do if (list->type == _hoops_SHGRA) {
			_hoops_PCSGA const *		findex = (_hoops_PCSGA const *)list;

			if ((float)(int)findex->value == findex->value) {
				int				_hoops_RCGPGR = (int)findex->value;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Color_By_Index \""))
					return false;

				if (!_hoops_GIGPGR (_hoops_GHIPH, list->_hoops_GHA, ","))
					return false;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "\"") ||
					!_hoops_APGPGR (_hoops_GHIPH, "%d)", (void *)&_hoops_RCGPGR))
					return false;

				if (list->next != null && !_hoops_CRGPGR (_hoops_GHIPH, "\n"))
					return false;
			}
			else {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Color_By_FIndex \""))
					return false;

				if (!_hoops_GIGPGR (_hoops_GHIPH, list->_hoops_GHA, ","))
					return false;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "\"") ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)&findex->value))
					return false;

				if (list->next != null && !_hoops_CRGPGR (_hoops_GHIPH, "\n"))
					return false;
			}
		}
		else if (list->type == _hoops_PPCA &&
				 (!_hoops_IIGPGR ||
				  ((_hoops_APCA const *)list)->name.length == 0)) {
			_hoops_APCA const *		normal = (_hoops_APCA const *)list;

			/* _hoops_CSSGR _hoops_HPP _hoops_PIRA _hoops_PAH _hoops_RGHH _hoops_RGR _hoops_AGIR */
			if (!_hoops_CRGPGR (_hoops_GHIPH, "(Color_By_Value \""))
				return false;

			if (!_hoops_GIGPGR (_hoops_GHIPH, list->_hoops_GHA, ","))
				return false;

			if (!_hoops_CRGPGR (_hoops_GHIPH, "\" \"RGB\"") ||
				!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&normal->rgb.red) ||
				!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&normal->rgb.green) ||
				!_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)&normal->rgb.blue))
				return false;
		}
		else if (list->type == _hoops_GIGRA &&
				 (!_hoops_IIGPGR ||
				  ((_hoops_HCSGA const *)list)->name.length == 0)) {
			_hoops_HCSGA const *		_hoops_ICSGA = (_hoops_HCSGA const *)list;

			if (_hoops_ICSGA->_hoops_ISHIR._hoops_PRGRA == M_DIFFUSE) {
				/* _hoops_CSSGR _hoops_HPP _hoops_PIRA _hoops_PAH _hoops_RGHH _hoops_RGR _hoops_AGIR */
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Color_By_Value \""))
					return false;

				if (!_hoops_GIGPGR (_hoops_GHIPH, list->_hoops_GHA, ","))
					return false;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "\" \"RGB\"") ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_ICSGA->_hoops_ISHIR._hoops_CSHR.red) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_ICSGA->_hoops_ISHIR._hoops_CSHR.green) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)&_hoops_ICSGA->_hoops_ISHIR._hoops_CSHR.blue))
					return false;
			}
			else {		/* _hoops_RRI _hoops_HSAR _hoops_ACGPGR _hoops_PAH _hoops_RGHH */
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Color \""))
					return false;
				if (!_hoops_GIGPGR (_hoops_GHIPH, list->_hoops_GHA, "="))
					return false;
				if (!_hoops_CRGPGR (_hoops_GHIPH, "="))
					return false;
				if (_hoops_ICSGA->name.length > 0) {
					if (!_hoops_APGPGR (_hoops_GHIPH, "%n", (void *)&_hoops_ICSGA->name))
						return false;
				}
				else if (!_hoops_AIGPGR (_hoops_GHIPH, &_hoops_ICSGA->_hoops_ISHIR))
					return false;
				if (!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
					return false;
			}

			if (list->next != null && !_hoops_CRGPGR (_hoops_GHIPH, "\n"))
				return false;
		} while ((list = list->next) != null);
	}

	return true;
}


/*
 *	_hoops_IISH _hoops_RH _hoops_HCGR _hoops_RSHCR _hoops_IS _hoops_IRS _hoops_RPPS _hoops_PAR _hoops_HSSP _hoops_HSGP _hoops_CRGR _hoops_RH _hoops_IIPR
 *	_hoops_SRHR
 */
local bool _hoops_PCGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	short			value) {
	char const		*p;

	switch (value) {
		case FP_WINDOW_CROSSHATCH:
		case FP_CROSSHATCH:				p = "#";		break;
		case FP_WINDOW_VERTICAL_BARS:
		case FP_VERTICAL_BARS:			p = "|";		break;
		case FP_WINDOW_HORIZONTAL_BARS:
		case FP_HORIZONTAL_BARS:		p = "=";		break;
		case FP_WINDOW_SLANT_RIGHT:
		case FP_SLANT_RIGHT:			p = "/";		break;
		case FP_WINDOW_SLANT_LEFT:
		case FP_SLANT_LEFT:				p = "\\";		break;
		case FP_WINDOW_DIAMONDS:
		case FP_DIAMONDS:				p = "<>";		break;
		case FP_WINDOW_SQUARE_DOTS:
		case FP_SQUARE_DOTS:			p = ":";		break;
		case FP_WINDOW_CHECKERBOARD:
		case FP_CHECKERBOARD:			p = "[]";		break;

		case FP_SOLID:					p = "solid";	break;

		case FP_WINDOW_TRANSPARENT:		p = "clear";	break;

		case FP_WINDOW_GRADIENT_N:		p = "N";		break;
		case FP_WINDOW_GRADIENT_NE:		p = "NE";		break;
		case FP_WINDOW_GRADIENT_E:		p = "E";		break;
		case FP_WINDOW_GRADIENT_SE:		p = "SE";		break;
		case FP_WINDOW_GRADIENT_S:		p = "S";		break;
		case FP_WINDOW_GRADIENT_SW:		p = "SW";		break;
		case FP_WINDOW_GRADIENT_W:		p = "W";		break;
		case FP_WINDOW_GRADIENT_NW:		p = "NW";		break;

		case FP_BLEND:					p = "blend";	break;


		case FP_WINDOW_TRANS_NO_ZCLEAR:	p = "invisible"; break;


		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected area pattern");
			p = "solid";
		}	break;
	}
	return _hoops_CAGPGR (_hoops_GHIPH, p);
}


/* _hoops_CHPPR _hoops_PCPH _hoops_IH _hoops_IRGAA _hoops_SGS _hoops_IRAA _hoops_SPR _hoops_PPSR */
local bool _hoops_HCGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	char const		*_hoops_CSRPR,
	Point const	*point) {

	return (_hoops_CRGPGR (_hoops_GHIPH, "(") &&
			_hoops_CRGPGR (_hoops_GHIPH, _hoops_CSRPR) &&
			_hoops_AHGPGR (_hoops_GHIPH, point) &&
			_hoops_CRGPGR (_hoops_GHIPH, ")"));
}


/* _hoops_IRS _hoops_HIGR _hoops_IIGR "_hoops_RACIR", _hoops_III _hoops_PRGS _hoops_PPR _hoops_ICGPGR _hoops_AGAPR */
local bool _hoops_CCGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	int				count,
	Point const	*points) {

	if (count == 0) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "()"))
			return false;
	}
	else {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
			return false;

		do {
			if (!_hoops_CRGPGR (_hoops_GHIPH, "(") ||
				!_hoops_AHGPGR (_hoops_GHIPH, points++) ||
				!_hoops_CRGPGR (_hoops_GHIPH, ")"))
				return false;
		} _hoops_RGGA (--count == 0);

		if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
			return false;
	}

	return true;
}
local bool _hoops_SCGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	int				count,
	_hoops_ARPA const	*planes) {

	if (count == 0) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "()"))
			return false;
	}
	else {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
			return false;

		do {
			if (!_hoops_CRGPGR (_hoops_GHIPH, "(") ||
				!_hoops_HHGPGR (_hoops_GHIPH, planes++) ||
				!_hoops_CRGPGR (_hoops_GHIPH, ")"))
				return false;
		} _hoops_RGGA (--count == 0);

		if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
			return false;
	}

	return true;
}


/* _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_AGRIR, _hoops_III _hoops_PRGS _hoops_PPR _hoops_ICGPGR _hoops_AGAPR */
local bool _hoops_GSGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	int				count,
	int const		*_hoops_RGIGS) {

	if (count == 0) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "()"))
			return false;
	}
	else {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
			return false;

		while (--count != 0)
			if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)_hoops_RGIGS++))
				return false;

		if (!_hoops_APGPGR (_hoops_GHIPH, "%d)", (void *)_hoops_RGIGS))
			return false;
	}

	return true;
}

/* _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_PHRP, _hoops_III _hoops_PRGS _hoops_PPR _hoops_ICGPGR _hoops_AGAPR */
local bool _hoops_RSGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	int				count,
	float const		*_hoops_RRIGS) {

	if (count == 0) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "()"))
			return false;
	}
	else {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
			return false;

		while (--count != 0)
			if (!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)_hoops_RRIGS++))
				return false;

		if (!_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)_hoops_RRIGS))
			return false;
	}

	return true;
}

/* _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_PHRP, _hoops_III _hoops_PRGS _hoops_PPR _hoops_ICGPGR _hoops_AGAPR, */
local bool _hoops_ASGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	char const		*name,
	int				count,
	float const		*_hoops_RRIGS) {

	if (count == 0) {
		return false;
	}
	else {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "(") ||
			!_hoops_CRGPGR (_hoops_GHIPH, name) ||
			!_hoops_CRGPGR (_hoops_GHIPH, " ("))
			return false;

		_hoops_RGGA (--count == 0)
			if (!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)_hoops_RRIGS++))
				return false;

		if (!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)_hoops_RRIGS) ||
			!_hoops_CRGPGR (_hoops_GHIPH, "))\n"))
			return false;
	}

	return true;
}


/* _hoops_CHPPR _hoops_PCPH _hoops_IH _hoops_RHASR _hoops_SGS _hoops_IRAA _hoops_SPR _hoops_HIGR _hoops_IIGR _hoops_RSSA */
local bool _hoops_PSGPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	char const		*_hoops_CSRPR,
	int				count,
	Point const	*points) {

	return (_hoops_CRGPGR (_hoops_GHIPH, "(") &&
			_hoops_CRGPGR (_hoops_GHIPH, _hoops_CSRPR) &&
			_hoops_CCGPGR (_hoops_GHIPH, count, points) &&
			_hoops_CRGPGR (_hoops_GHIPH, ")"));
}


local bool _hoops_HSGPGR (
	_hoops_RSSAGR *		info,
	Image *					image,
	char *					scratch) {
	_hoops_IRIPH *				_hoops_GHIPH = info->_hoops_GRHRI;
	char					format[1024];

	if (!_hoops_CRGPGR (_hoops_GHIPH, "(Compressed_Image") ||
		!_hoops_AHGPGR (_hoops_GHIPH, &image->_hoops_CSAI) ||
		!_hoops_CRGPGR (_hoops_GHIPH, "\""))
		return false;

	/* _hoops_CSCS _hoops_RPCC _hoops_PPR _hoops_CCCIP _hoops_RSIRR _hoops_PPR/_hoops_PAR _hoops_IGIR */
	PUSHNAME(info->_hoops_RIGC);
	HC_Show_Image_Size (_hoops_AIRIR (image), null, null, null, format, null, null);
	POPNAME(info->_hoops_RIGC);
	if (!_hoops_PAGPGR	 (_hoops_GHIPH, format, -1))
		return false;

	if (image->texture != 0) {
		int	_hoops_ISGPGR;
		bool _hoops_GAGRGR;

		_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;

		HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
		_hoops_GAGRGR = HI_Show_Texture (info->_hoops_RIGC, image->texture, scratch, -1, null, 0, false, 0);
		HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

		if (image->owner == (_hoops_CRCP*)image->texture->owner &&
			!_hoops_PAGPGR (_hoops_GHIPH, ",local", -1))
			return false;

		if (_hoops_GAGRGR && (
			!_hoops_PAGPGR (_hoops_GHIPH, ",texture options=(", -1) ||
			!_hoops_PAGPGR (_hoops_GHIPH, scratch, -1) ||
			!_hoops_PAGPGR (_hoops_GHIPH, ")", -1)))
			return false;
	}

	if (!_hoops_CRGPGR (_hoops_GHIPH, "\""))
		return false;

	/* _hoops_SRGGR _hoops_CSCR _hoops_PIH _hoops_HII _hoops_RH _hoops_CGRH _hoops_RPP _hoops_SIGR */
	if (ALLBITS (image->flags, _hoops_GRRH|_hoops_APAH)) {
		_hoops_GACR *		dl = image->_hoops_GAHA;
		_hoops_GGAGR *			_hoops_CSHHP = (_hoops_GGAGR *)dl->_hoops_GHRI;

		_hoops_HISAA (info->_hoops_RIGC, _hoops_CSHHP, _hoops_ASGPI, dl->list);
	}

	if (!_hoops_APGPGR (_hoops_GHIPH, "%d ", (void *)&image->width))
		return false;
	if (!_hoops_APGPGR (_hoops_GHIPH, "%d ", (void *)&image->height))
		return false;
	if (!_hoops_APGPGR (_hoops_GHIPH, "%d ", (void *)&image->_hoops_IARH))
		return false;

	if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
		return false;

	unsigned char *ptr = (unsigned char *)image->_hoops_PHGH;
	int _hoops_HAGR;
	for (int i = 0; i < image->_hoops_IARH; i++) {
		_hoops_HAGR = *ptr++;
		if (!_hoops_APGPGR (_hoops_GHIPH, "%d ", (void *)&_hoops_HAGR))
			return false;
	}

	if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
		return false;
	if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
		return false;

	return true;
}


local bool _hoops_CSGPGR (
	_hoops_RSSAGR *		info,
	Image *					image,
	char *					scratch) {
	_hoops_IRIPH *				_hoops_GHIPH = info->_hoops_GRHRI;
	void const * const *	rasters = image->rasters;
	int						row;
	int						column;
	int						index;
	char					format[1024];

	if (info->_hoops_GGRHH->LookupItem(image) == VHASH_STATUS_SUCCESS)
		return true;

	info->_hoops_GGRHH->InsertItem(image);

	if (BIT (image->flags, _hoops_SSGH))
		return _hoops_HSGPGR (info, image, scratch);

	if (!_hoops_CRGPGR (_hoops_GHIPH, "(Image") ||
		!_hoops_AHGPGR (_hoops_GHIPH, &image->_hoops_CSAI) ||
		!_hoops_CRGPGR (_hoops_GHIPH, "\""))
		return false;

	/* _hoops_CSCS _hoops_RPCC _hoops_PPR _hoops_CCCIP _hoops_RSIRR _hoops_PPR/_hoops_PAR _hoops_IGIR */
	PUSHNAME(info->_hoops_RIGC);
	HC_Show_Image_Size (_hoops_AIRIR (image), null, null, null, format, null, null);
	POPNAME(info->_hoops_RIGC);
	if (!_hoops_PAGPGR	 (_hoops_GHIPH, format, -1))
		return false;

	if (image->texture != 0) {
		int				_hoops_ISGPGR;
		bool		_hoops_GAGRGR;

		_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;

		HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
		_hoops_GAGRGR = HI_Show_Texture (info->_hoops_RIGC, image->texture, scratch, -1, null, 0, false, 0);
		HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

		if (image->owner == (_hoops_CRCP*)image->texture->owner &&
			!_hoops_PAGPGR (_hoops_GHIPH, ",local", -1))
			return false;

		if (_hoops_GAGRGR && (
			!_hoops_PAGPGR (_hoops_GHIPH, ",texture options=(", -1) ||
			!_hoops_PAGPGR (_hoops_GHIPH, scratch, -1) ||
			!_hoops_PAGPGR (_hoops_GHIPH, ")", -1)))
			return false;
	}

	if (!_hoops_CRGPGR (_hoops_GHIPH, "\" ("))
		return false;

	/* _hoops_SRGGR _hoops_CSCR _hoops_PIH _hoops_HII _hoops_RH _hoops_CGRH _hoops_RPP _hoops_SIGR */
	if (ALLBITS (image->flags, _hoops_GRRH|_hoops_APAH)) {
		_hoops_GACR *		dl = image->_hoops_GAHA;
		_hoops_GGAGR *			_hoops_CSHHP = (_hoops_GGAGR *)dl->_hoops_GHRI;

		_hoops_HISAA (info->_hoops_RIGC, _hoops_CSHHP, _hoops_ASGPI, dl->list);
	}

	switch (image->format) {
#ifndef DISABLE_NON_RGB_IMAGES
		case _hoops_PCCRH: {
			float *_hoops_GAAC;

			if ((row = image->height) > 0) do {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
					return false;
				_hoops_GAAC = (float *)*rasters++;

				if ((column = image->width) > 0) do {
					if (!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)_hoops_GAAC))
						return false;
					_hoops_GAAC++;
				} _hoops_RGGA (--column == 0);

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			} _hoops_RGGA (--row == 0);
		}   break;

		case Image_MAPPED_16: {
			unsigned short	*_hoops_GAAC;

			if ((row = image->height) > 0) do {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
					return false;
				_hoops_GAAC = (unsigned short *)*rasters++;

				if ((column = image->width) > 0) do {
					/* _hoops_CAAA _hoops_ICHRR _hoops_IS _hoops_SCSH */
					index = *_hoops_GAAC++;
					if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&index))
						return false;
				} _hoops_RGGA (--column == 0);

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			} _hoops_RGGA (--row == 0);
		}	break;
#endif

		case Image_MAPPED_8:
		case _hoops_AHGH: {
			unsigned char	*_hoops_GAAC;

			if ((row = image->height) > 0) do {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
					return false;
				_hoops_GAAC = (unsigned char *)*rasters++;

				if ((column = image->width) > 0) do {
					/* _hoops_CAAA _hoops_GSPR _hoops_IS _hoops_SCSH */
					index = _hoops_IRGCR(*_hoops_GAAC);
					if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&index))
						return false;
					++_hoops_GAAC;
				} _hoops_RGGA (--column == 0);

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			} _hoops_RGGA (--row == 0);
		}	break;

		case _hoops_HHGH:
		case _hoops_CSGSP:
		case Image_RGBA32:
		case _hoops_HRSRH: {
			int 		i,j;

			for (i=0; i< image->height; i++) {
				unsigned char   *_hoops_IGRPI = (unsigned char*)image->rasters[i];

				if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
					return false;

				for (j=0; j< image->width; j++) {
					_hoops_AIGH	pixel;
					int		value;

					if (image->format == _hoops_CSGSP) {
						RGBAS32 *_hoops_AGRPI = (RGBAS32*)&_hoops_IGRPI[j];
						pixel.r = _hoops_AGRPI->r;
						pixel.g = _hoops_AGRPI->g;
						pixel.b = _hoops_AGRPI->b;
						pixel.a = _hoops_AGRPI->a;
						_hoops_IGRPI+=4;
					}
					else if (image->format == Image_RGBA32) {
						pixel.r = *_hoops_IGRPI++;
						pixel.g = *_hoops_IGRPI++;
						pixel.b = *_hoops_IGRPI++;
						pixel.a = *_hoops_IGRPI++;
					}
					else if (image->format == _hoops_HRSRH) {
						pixel.a = *_hoops_IGRPI++;
						pixel.r = *_hoops_IGRPI++;
						pixel.g = *_hoops_IGRPI++;
						pixel.b = *_hoops_IGRPI++;
					}
					else {
						/*_hoops_CSCR->_hoops_RPCC == _hoops_SGRPI*/
						pixel.r = *_hoops_IGRPI++;
						pixel.g = *_hoops_IGRPI++;
						pixel.b = *_hoops_IGRPI++;
						pixel.a = _hoops_GPGCR;
					}

					if (image->_hoops_ISRRP == _hoops_HHGH) {
						value = pixel.r;
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&value))
							return false;
						value = pixel.g;
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&value))
							return false;
						value = pixel.b;
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&value))
							return false;
					}
					else if (image->_hoops_ISRRP == _hoops_HRSRH) {
						value = pixel.a;
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&value))
							return false;
						value = pixel.r;
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&value))
							return false;
						value = pixel.g;
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&value))
							return false;
						value = pixel.b;
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&value))
							return false;
					}
					else if (image->_hoops_ISRRP == Image_RGBA32) {
						value = pixel.r;
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&value))
							return false;
						value = pixel.g;
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&value))
							return false;
						value = pixel.b;
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&value))
							return false;
						value = pixel.a;
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&value))
							return false;
					}
				}

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}
		}	break;

		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				   "Unexpected image format");
	}

	if (!_hoops_CRGPGR (_hoops_GHIPH, "))"))
		return false;
	return true;
}


local bool _hoops_SSGPGR (
	_hoops_IRIPH		*_hoops_GHIPH,
	_hoops_AIHPR			*_hoops_PIHPR) {
	Point		*points = _hoops_PIHPR->points;
	int				_hoops_SIHPR;

	if (!_hoops_CRGPGR (_hoops_GHIPH, "(Mesh ("))
		return false;

	_hoops_SIHPR = _hoops_PIHPR->rows;
	if (_hoops_SIHPR != 0) _hoops_PCCAR {
		if (!_hoops_CCGPGR (_hoops_GHIPH, _hoops_PIHPR->columns, points))
			return false;
		if (--_hoops_SIHPR == 0) break;
		if (!_hoops_CRGPGR (_hoops_GHIPH, "\n")) break;
		points += _hoops_PIHPR->columns;
	}
	if (!_hoops_CRGPGR (_hoops_GHIPH, "))"))
		return false;

	return true;
}


local void _hoops_GGRPGR (
	_hoops_CRCP alter *			_hoops_SRCP,
	bool					set) {

	if (_hoops_SRCP != HOOPS_WORLD->root) do {
		if (set) {
			if (BIT (_hoops_SRCP->_hoops_RRHH, _hoops_CCSAGR))
				break;
			_hoops_SRCP->_hoops_RRHH |= _hoops_CCSAGR;
		}
		else {
			if (!BIT (_hoops_SRCP->_hoops_RRHH, _hoops_CCSAGR))
				break;
			_hoops_SRCP->_hoops_RRHH &= ~_hoops_CCSAGR;
		}
	} while ((_hoops_SRCP = _hoops_SRCP->owner) != HOOPS_WORLD->root);
}

local void _hoops_RGRPGR (
	_hoops_CRCP alter *			_hoops_SRCP,
	bool					set,
	bool					_hoops_AGRPGR = false) {
	Subsegment alter *		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;

	if (_hoops_AGRPGR)
		_hoops_GGRPGR (_hoops_SRCP, set);

	if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_RGRPGR (_hoops_SSIGP(_hoops_GIPIA), set, _hoops_AGRPGR || (_hoops_GIPIA->type == _hoops_AGRPR));
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
}


struct _hoops_PGRPGR {
	_hoops_PGRPGR *		next;
	_hoops_CRCP const *		segment;
	int					_hoops_APACP;
};

local _hoops_PGRPGR * _hoops_HGRPGR (
	_hoops_CRCP const *		_hoops_SRCP,
	_hoops_CRCP const *		_hoops_IGRPGR = null,
	_hoops_CRCP const *		_hoops_CGRPGR = null) {
	_hoops_PGRPGR *		_hoops_CIPPH = null;
	int					_hoops_HRPGC = 0;

	_hoops_PCCAR {
		_hoops_PGRPGR *		_hoops_RAASA;

		if (_hoops_SRCP == _hoops_IGRPGR)
			_hoops_HRPGC |= 0x01;
		else if (_hoops_SRCP == _hoops_CGRPGR)
			_hoops_HRPGC |= 0x02;

		ALLOC (_hoops_RAASA, _hoops_PGRPGR);
		_hoops_RAASA->segment = _hoops_SRCP;
		_hoops_RAASA->_hoops_APACP = _hoops_HRPGC;
		_hoops_RAASA->next = _hoops_CIPPH;
		_hoops_CIPPH = _hoops_RAASA;
		if (_hoops_SRCP == HOOPS_WORLD->root)
			break;
		_hoops_SRCP = _hoops_SRCP->owner;
		if (_hoops_SRCP == HOOPS_WORLD->root && _hoops_IGRPGR != HOOPS_WORLD->root)
			break;
	}

	return _hoops_CIPPH;
}

local int depth (_hoops_CRCP const * _hoops_SRCP) {
	int		count = 0;

	if (_hoops_SRCP != HOOPS_WORLD->root) do
		++count;
	while ((_hoops_SRCP = _hoops_SRCP->owner) != HOOPS_WORLD->root);

	return count;
}

local bool _hoops_SGRPGR (
	_hoops_RSSAGR *	info,
	_hoops_CRCP const *		segment) {
	_hoops_IRIPH *			_hoops_GHIPH = info->_hoops_GRHRI;
	Key					tmp = _hoops_AIRIR (segment);
	char				string[MAX_ERRMSG];

	Sprintf_X (string, "XXX Temporary #%X", tmp);
	if (!_hoops_CRGPGR (_hoops_GHIPH, string))
		return false;

	if (!BIT (segment->_hoops_RRHH, _hoops_GSSAGR)) {
		info->unnamed->Push(segment, depth (segment));
		((_hoops_CRCP alter *)segment)->_hoops_RRHH |= _hoops_GSSAGR;
	}

	return true;
}

local bool _hoops_GRRPGR (
	_hoops_RSSAGR *		info,
	_hoops_CRCP const *			segment,
	_hoops_CRCP const *			_hoops_RRRPGR) {
	_hoops_IRIPH *				_hoops_GHIPH = info->_hoops_GRHRI;
	_hoops_PGRPGR *			_hoops_ARRPGR = null;
	_hoops_PGRPGR *			_hoops_PRRPGR = null;
	_hoops_PGRPGR *			victim;
	bool					_hoops_HRRPGR = false;

	if (_hoops_RRRPGR != null) {
		_hoops_CRCP const *		root = info->_hoops_ASSAGR->segment;
		_hoops_CRCP const *		_hoops_AAGRGR = null;

		if (*HI_Look_Up_Alias (info->_hoops_RIGC, "include library", 15) != null)
			_hoops_AAGRGR = HI_One_Segment_Search (info->_hoops_RIGC, "?Include Library", false);
		else
			_hoops_AAGRGR = HI_One_Segment_Search (info->_hoops_RIGC, "/Include Library", false);

		_hoops_ARRPGR = _hoops_HGRPGR (segment, root, _hoops_AAGRGR);
		_hoops_PRRPGR = _hoops_HGRPGR (_hoops_RRRPGR, root, _hoops_AAGRGR);

		if ((_hoops_ARRPGR->_hoops_APACP & _hoops_PRRPGR->_hoops_APACP) != 0) {
			while (_hoops_PRRPGR != null && _hoops_ARRPGR->next != null &&	// _hoops_IRRPGR _hoops_PAH _hoops_RHPA, _hoops_CRRPGR _hoops_PAH'_hoops_RA
				   _hoops_ARRPGR->segment == _hoops_PRRPGR->segment) {
				victim = _hoops_ARRPGR;
				_hoops_ARRPGR = victim->next;
				FREE (victim, _hoops_PGRPGR);

				victim = _hoops_PRRPGR;
				_hoops_PRRPGR = victim->next;
				FREE (victim, _hoops_PGRPGR);
			}
			_hoops_HRRPGR = true;
		}
		else {
			while ((victim = _hoops_PRRPGR) != null) {
				_hoops_PRRPGR = victim->next;
				FREE (victim, _hoops_PGRPGR);
			}
		}
	}
	else {
		_hoops_ARRPGR = _hoops_HGRPGR (segment);
	}

	if (_hoops_PRRPGR != null) {
		// _hoops_GGCR "../" _hoops_IH _hoops_GRR _hoops_RARP
		while ((victim = _hoops_PRRPGR) != null) {
			if (!_hoops_CRGPGR (_hoops_GHIPH, "../"))
				return false;

			_hoops_PRRPGR = victim->next;
			FREE (victim, _hoops_PGRPGR);
		}
	}

	while ((victim = _hoops_ARRPGR) != null) {
		segment = victim->segment;

		if (!_hoops_HRRPGR) {
			if (!_hoops_CRGPGR (_hoops_GHIPH, "/"))
				return false;
		}
		_hoops_HRRPGR = false;	// _hoops_HHSA _hoops_HAIAH _hoops_IH _hoops_GRR _hoops_HHRPA _hoops_CAGH

		if (segment->name.length > 0) {
			if (!_hoops_APGPGR (_hoops_GHIPH, "%N", (void *)&segment->name))
				return false;
		}
		else {
			if (!_hoops_SGRPGR (info, segment))
				return false;
		}

		_hoops_ARRPGR = victim->next;
		FREE (victim, _hoops_PGRPGR);
	}

	return true;
}

local bool _hoops_SRRPGR (
	_hoops_IRIPH *		_hoops_GHIPH,
	_hoops_HCRPR const *	name,
	int				style) {
	char const *	p;

	if (!_hoops_CRGPGR (_hoops_GHIPH, "\""))
		return false;

	switch (style & LCAP_START_MASK) {
		case LCAP_BUTT	:		p = "";			break;
		case LCAP_SQUARE:		p = "[";		break;
		case LCAP_ROUND:		p = "(";		break;
		case LCAP_TRIANGLE:		p = "<";		break;

		default:				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
												   "Unexpected line/edge pattern");
								return false;	_hoops_HHHI;
	}
	if (!_hoops_PAGPGR (_hoops_GHIPH, p, -1))
		return false;

	if (style & LCAP_END_MASK) {
		switch (style & LCAP_END_MASK) {
			case LCAP_END_BUTT	:		p = "|";		break;
			case LCAP_END_SQUARE:		p = "[";		break;
			case LCAP_END_ROUND:		p = "(";		break;
			case LCAP_END_TRIANGLE:		p = "<";		break;

			default:				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
													   "Unexpected line/edge pattern");
									return false;	_hoops_HHHI;
		}
		if (!_hoops_PAGPGR (_hoops_GHIPH, p, -1))
			return false;
	}

	if (!_hoops_PAGPGR (_hoops_GHIPH, name->text, -1))
		return false;

	switch (style & LJOIN_MASK) {
		case LJOIN_MITER:		p = "";			break;
		case LJOIN_BEVEL:		p = "|";		break;
		case LJOIN_ROUND:		p = ")";		break;

		default:				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
												   "Unexpected line/edge pattern");
								return false;	_hoops_HHHI;
	}
	if (!_hoops_PAGPGR (_hoops_GHIPH, p, -1))
		return false;

	switch (style & LPAT_MASK) {
		case LPAT_BUTT:			p = "";			break;
		case LPAT_ROUND:		p = "@";		break;
		case LPAT_SQUARE:		p = "#";		break;
		case LPAT_TRIANGLE:		p = "^";		break;

		default:				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
												   "Unexpected line/edge pattern");
								return false;	_hoops_HHHI;
	}
	if (!_hoops_PAGPGR (_hoops_GHIPH, p, -1))
		return false;

	return _hoops_CRGPGR (_hoops_GHIPH, "\"");
}


local bool _hoops_GARPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	char const		*type,
	RGB			*rgb) {

	return (_hoops_APGPGR (_hoops_GHIPH, "(Color_By_Value %S", type) &&
			_hoops_APGPGR (_hoops_GHIPH, "\"rgb\" %f", (void *)&rgb->red) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&rgb->green) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)&rgb->blue));
}

local bool _hoops_RARPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	RGBAS32		*color) {
	RGBA		_hoops_PIHR = *color;

	return (_hoops_APGPGR (_hoops_GHIPH, "(Color_By_Value \"vertex\" \"rgba\" %f", (void *)&_hoops_PIHR.red) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_PIHR.green) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_PIHR.blue) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)&_hoops_PIHR.alpha));
}


local bool _hoops_AARPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	Vector const	*normal) {

	return (_hoops_APGPGR (_hoops_GHIPH, "(Normal %f", (void *)&normal->x) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&normal->y) &&
			_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)&normal->z));
}

local bool _hoops_PARPGR (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_RSSH const		*param,
	Integer32			param_width) {
	int		i;

	if (!_hoops_CRGPGR (_hoops_GHIPH, "(Parameter ("))
		return false;

	for (i=0; i<param_width; i++)
		if (!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&param[i]))
			return false;

	if (!_hoops_CRGPGR (_hoops_GHIPH, "))"))
		return false;

	return true;
}


local void _hoops_HARPGR (
	Polyhedron	*_hoops_IPRI,
	int				offset,
	int				*_hoops_IARPGR,
	int				*_hoops_CARPGR) {

	if (_hoops_IPRI->type == _hoops_GSIP) {
		_hoops_AIHPR *					_hoops_PIHPR = (_hoops_AIHPR *)_hoops_IPRI;

		*_hoops_IARPGR = offset / 3;
		switch (offset % 3) {
			case 0:		*_hoops_CARPGR = *_hoops_IARPGR + 1;						break;
			case 1:		*_hoops_CARPGR = *_hoops_IARPGR + _hoops_PIHPR->columns;			break;
			case 2:		*_hoops_CARPGR = *_hoops_IARPGR + _hoops_PIHPR->columns - 1;		break;
		}
	}
	else /* _hoops_HGCPR */ {
		Shell *					_hoops_SPHPR = (Shell *)_hoops_IPRI;
		_hoops_RHHPR		**_hoops_PPGPA,
								*edge;
		int						upper,
								lower,
								_hoops_ISPI;

		/* _hoops_AA _hoops_IRS _hoops_PSHPR _hoops_GIPHR */
		/* _hoops_ARARH */
		_hoops_PPGPA = _hoops_SPHPR->_hoops_HHHPR;
		lower = 0;
		upper = _hoops_SPHPR->point_count;
		edge = _hoops_SPHPR->_hoops_GRCPR + offset;

		_hoops_RGGA ((_hoops_ISPI = lower + (upper - lower)/2) == lower) {
			if (_hoops_PPGPA[_hoops_ISPI] > edge)
				upper = _hoops_ISPI;
			else
				lower = _hoops_ISPI;
		}

		*_hoops_IARPGR = _hoops_ISPI;
		*_hoops_CARPGR = edge->_hoops_GIHPR;
	}
}


local bool _hoops_SARPGR(
	_hoops_IRIPH	*_hoops_GHIPH,
	UV_Trim		*node,
	bool		_hoops_GPRPGR) {
	if (node->next != null)
		_hoops_SARPGR (_hoops_GHIPH, node->next, _hoops_GPRPGR);

	switch (node->type) {
		case _hoops_PARIR: {
			UV_Trim_Poly *_hoops_HARIR = (UV_Trim_Poly *) node;
			int i;

			if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(Trim_Poly"))
				return false;
			if (!_hoops_GPRPGR) {
				if (node->flags & _hoops_RSSSI) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "\"keep\""))
						return false;
				}
				else {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "\"remove\""))
						return false;
				}
			}
			if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
				return false;

			for (i = 0; i < _hoops_HARIR->count; i++) {
				if (!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_HARIR->points[i].u) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_HARIR->points[i].v))
					return false;
			}
			if (!_hoops_CRGPGR (_hoops_GHIPH, "))"))
				return false;
		}	break;

		case _hoops_IARIR: {
			UV_Trim_Curve *curve = (UV_Trim_Curve *) node;
			int i, knot_count;
			float start_u, end_u;

			if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(Trim_Curve"))
				return false;
			if (!_hoops_GPRPGR) {
				if (node->flags & _hoops_RSSSI) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "\"keep\""))
						return false;
				}
				else {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "\"remove\""))
						return false;
				}
			}
			if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&curve->degree) ||
				!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&curve->control_point_count))
				return false;

			start_u = 0;
			end_u = 1;
			if (!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&start_u) ||
				!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&end_u))
				return false;

			if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
				return false;
			for (i = 0; i < curve->control_point_count; i++) {
				if (!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&curve->control_points[i].u) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&curve->control_points[i].v))
					return false;
			}
			if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
				return false;

			if (curve->knots != null) {
				knot_count = curve->control_point_count + curve->degree + 1;
				if (!_hoops_ASGPGR (_hoops_GHIPH, "Knots", knot_count, curve->knots))
					return false;
			}
			if (curve->weights != null) {
				if (!_hoops_ASGPGR (_hoops_GHIPH, "Weights", curve->control_point_count, curve->weights))
					return false;
			}
			if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
				return false;
		}	break;

		case _hoops_CARIR: {
			UV_Trim_Collection *_hoops_SARIR = (UV_Trim_Collection *)node;

			if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(Trim_Collection"))
				return false;
			if (!_hoops_GPRPGR) {
				if (_hoops_SARIR->flags & _hoops_RSSSI) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "\"keep\""))
						return false;
				}
				else {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "\"remove\""))
						return false;
				}
			}
			else {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						"Unexpected trim type on NURBS Surface during file write: collection in collection");
			}
			if (_hoops_SARIR->_hoops_GPRIR != null) {
				if (!_hoops_SARPGR (_hoops_GHIPH, _hoops_SARIR->_hoops_GPRIR, true))
					return false;
			}
			if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
				return false;
		}	break;

		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"Unexpected trim type on NURBS Surface during file write");
			break;
	}

	return true;
}



local bool _hoops_RPRPGR (_hoops_PGAIR const *_hoops_HGAIR)
{
	int i;

	if (_hoops_HGAIR == null)
		return true;
	for (i = 0; i < _hoops_IGAIR; i++) {
		if (_hoops_HGAIR->data[i] != null)
			return false;
	}
	return true;
}


/* _hoops_CPCHR _hoops_IGCPR */
local bool _hoops_GRSIR (
		Geometry *g,
		_hoops_RSSAGR *info, char *s);
local bool _hoops_APRPGR (
		Attribute *a, _hoops_CRCP const *_hoops_SRCP,
		_hoops_RSSAGR *info, char *s);


local bool _hoops_PPRPGR (
	_hoops_HPAH *thing,
	_hoops_RSSAGR	*info,
	char *scratch)
{
	_hoops_IRIPH		*_hoops_GHIPH = info->_hoops_GRHRI;
	Geometry			*list;
	int					i;
	_hoops_PGAIR *_hoops_HGAIR = null;

	switch (thing->type) {
		case _hoops_SCIP:
		case _hoops_GSIP:
			_hoops_HGAIR = ((Polyhedron *)thing)->_hoops_HGAIR;
			break;
		case _hoops_IRCP:
			_hoops_HGAIR = ((_hoops_CRCP *)thing)->_hoops_SSRIR();
			break;
		default:
			HE_ERROR (HEC_INTERNAL_ERROR, HES_MOST_RECENT_OPEN,
					"unrecognized LOD owner");
	}

	if (_hoops_RPRPGR(_hoops_HGAIR))
		return true;

	for (i = 1; i <= _hoops_IGAIR; i++) {
		list = _hoops_HGAIR->data[i-1];
		if (list != null) {
			if (!_hoops_APGPGR (_hoops_GHIPH, "\n(LOD %d", (void *)&i) ||
				!_hoops_GRSIR (list, info, scratch) ||
				!_hoops_CRGPGR (_hoops_GHIPH, ")"))
				return false;
		}
	}
	return true;
}




local bool _hoops_HPRPGR (
	Polyhedron *			_hoops_IPRI,
	_hoops_RSSAGR *	info) {
	_hoops_IRIPH *			_hoops_GHIPH = info->_hoops_GRHRI;

	if (_hoops_IPRI->local_face_attributes.regions != null) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(Regions") ||
			!_hoops_GSGPGR (_hoops_GHIPH, _hoops_IPRI->face_count,
									_hoops_IPRI->local_face_attributes.regions) ||
			!_hoops_CRGPGR (_hoops_GHIPH, ")"))
			return false;
	}

	if (BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) && _hoops_IPRI->local_vertex_attributes.flags != null ||
		!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) && _hoops_IPRI->local_vertex_attributes._hoops_SGRHR != 0) {
		Local_Vertex_Attributes		*_hoops_SPRI;
		int								vertex = 0;
		Local_Vertex_Flags			mask;
		char							buffer[128];
		char							*_hoops_ASAPR;

		_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		_hoops_RGGA (vertex == _hoops_IPRI->point_count) {
			if (ANYBIT (*_hoops_SPRI->_hoops_CHHPR(vertex),
						_hoops_CIICA|
						_hoops_CPPRA|
						LVA_EXPLICIT_NORMAL|
						_hoops_ASAPA)) {
				if (!_hoops_APGPGR (_hoops_GHIPH, "\n(Vertex %d", (void *)&vertex))
					return false;

				/* _hoops_HAIR _hoops_PHSPR _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_SIRAR _hoops_IS _hoops_IRHH _hoops_IPRPGR _hoops_IIPR */

				mask = *_hoops_SPRI->_hoops_CHHPR(vertex) & _hoops_ARSII;
				while (mask != 0) {
					RGB					*color;

					_hoops_ASAPR = buffer;
					*_hoops_ASAPR = '\0';
					color = null;

					if (mask == _hoops_ARSII &&
						_hoops_SPRI->fcolors[vertex] == _hoops_SPRI->ecolors[vertex] &&
						_hoops_SPRI->fcolors[vertex] == _hoops_SPRI->_hoops_PAHIR[vertex]) {
						/* _hoops_HCR _hoops_HRSP _hoops_RH _hoops_PSHR! */
						color = &_hoops_SPRI->fcolors[vertex];
						_hoops_ASAPR = HI_Copy_Chars ("geometry", _hoops_ASAPR);
						mask = false;
					}
					else switch (_hoops_RIII (mask)) {		/* _hoops_ARAR _hoops_RRIPR! */
						case _hoops_HCRRA: {
							color = &_hoops_SPRI->_hoops_PAHIR[vertex];
							_hoops_ASAPR = HI_Copy_Chars ("marker", _hoops_ASAPR);
							mask &= ~_hoops_HCRRA;
						}	 _hoops_HHHI;

						case _hoops_PPHPR: {
							if (BIT (mask, _hoops_PPHPR) &&
								(color == null ||
								 color->red	  == _hoops_SPRI->ecolors[vertex].red	&&
								 color->green == _hoops_SPRI->ecolors[vertex].green &&
								 color->blue  == _hoops_SPRI->ecolors[vertex].blue)) {
								if (color != null)
									_hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);

								color = &_hoops_SPRI->ecolors[vertex];
								_hoops_ASAPR = HI_Copy_Chars ("edge", _hoops_ASAPR);
								mask &= ~_hoops_PPHPR;
							}
						}		_hoops_HHHI;

						case _hoops_AARHR: {
							if (BIT (mask, _hoops_AARHR) &&
								(color == null ||
								 color->red	  == _hoops_SPRI->fcolors[vertex].red	&&
								 color->green == _hoops_SPRI->fcolors[vertex].green &&
								 color->blue  == _hoops_SPRI->fcolors[vertex].blue)) {
								if (color != null)
									_hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);

								color = &_hoops_SPRI->fcolors[vertex];
								_hoops_ASAPR = HI_Copy_Chars ("face", _hoops_ASAPR);
								mask &= ~_hoops_AARHR;
							}
						}		_hoops_HHHI;
					}
					*_hoops_ASAPR = '\0';

					if (!_hoops_GARPGR (_hoops_GHIPH, buffer, color))
						return false;
				}

				if (BIT (*_hoops_SPRI->_hoops_CHHPR(vertex), _hoops_CCRRA)) {
					if (!_hoops_RARPGR (_hoops_GHIPH, &_hoops_SPRI->_hoops_IAHIR[vertex]))
						return false;
				}

				mask = *_hoops_SPRI->_hoops_CHHPR(vertex) & _hoops_GGSII;
				while (mask != 0) {
					_hoops_ACGHR	findex;

					_hoops_ASAPR = buffer;
					*_hoops_ASAPR = '\0';
					findex = -1.0f;

					if (mask == _hoops_GGSII &&
						_hoops_SPRI->_hoops_IGHIR[vertex] == _hoops_SPRI->_hoops_HGHIR[vertex] &&
						_hoops_SPRI->_hoops_IGHIR[vertex] == _hoops_SPRI->_hoops_HAHIR[vertex]) {
						/* _hoops_HCR _hoops_HRSP _hoops_RH _hoops_PSHR! */
						findex = _hoops_SPRI->_hoops_IGHIR[vertex];
						_hoops_ASAPR = HI_Copy_Chars ("geometry", _hoops_ASAPR);
						mask = false;
					}
					else switch (_hoops_RIII (mask)) {		/* _hoops_ARAR _hoops_RRIPR! */
						case _hoops_SIRRA: {
							findex = _hoops_SPRI->_hoops_HAHIR[vertex];
							_hoops_ASAPR = HI_Copy_Chars ("marker", _hoops_ASAPR);
							mask &= ~_hoops_SIRRA;
						}	 _hoops_HHHI;

						case _hoops_RPHPR: {
							if (BIT (mask, _hoops_RPHPR) &&
								(findex == -1 ||
								 findex == _hoops_SPRI->_hoops_HGHIR[vertex])) {
								if (findex != -1) _hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);

								findex = _hoops_SPRI->_hoops_HGHIR[vertex];
								_hoops_ASAPR = HI_Copy_Chars ("edge", _hoops_ASAPR);
								mask &= ~_hoops_RPHPR;
							}
						}		_hoops_HHHI;

						case _hoops_HARHR: {
							if (BIT (mask, _hoops_HARHR) &&
								(findex == -1 ||
								 findex == _hoops_SPRI->_hoops_IGHIR[vertex])) {
								if (findex != -1) _hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);

								findex = _hoops_SPRI->_hoops_IGHIR[vertex];
								_hoops_ASAPR = HI_Copy_Chars ("face", _hoops_ASAPR);
								mask &= ~_hoops_HARHR;
							}
						}		_hoops_HHHI;
					}
					*_hoops_ASAPR = '\0';

					if (!_hoops_APGPGR (_hoops_GHIPH, "(Color_By_Findex %S", (void *)buffer) ||
						!_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)&findex))
						return false;
				}


				if (BIT (*_hoops_SPRI->_hoops_CHHPR(vertex), _hoops_PHIAA)) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Visibility \"markers\")"))
						return false;
				}
				else if (BIT (*_hoops_SPRI->_hoops_CHHPR(vertex), _hoops_HHIAA)) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Visibility \"no markers\")"))
						return false;
				}

				if (BIT (*_hoops_SPRI->_hoops_CHHPR(vertex), _hoops_SIICA)) {
					_hoops_RPHIR *sl = HI_LVA_Symbol_Lookup(_hoops_IPRI, _hoops_SPRI->_hoops_SAHIR[vertex]);
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Marker_Symbol \"") ||
						!_hoops_CRGPGR (_hoops_GHIPH, sl->name.text) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
						return false;
				}

				if (BIT (*_hoops_SPRI->_hoops_CHHPR(vertex), _hoops_GCICA))
					if (!_hoops_APGPGR (_hoops_GHIPH, "(Marker_Size %f)",
										 (void *)&_hoops_SPRI->_hoops_CAHIR[vertex]))
						return false;

				if (BIT (*_hoops_SPRI->_hoops_CHHPR(vertex), LVA_EXPLICIT_NORMAL))
					if (!_hoops_AARPGR (_hoops_GHIPH, &_hoops_SPRI->normals[vertex]))
						return false;

				if (BIT (*_hoops_SPRI->_hoops_CHHPR(vertex), _hoops_ASAPA))
					if (!_hoops_PARPGR (_hoops_GHIPH, &_hoops_SPRI->params[vertex*_hoops_SPRI->param_width], _hoops_SPRI->param_width))
						return false;

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}

			++vertex;
		}
	}

	if (_hoops_IPRI->_hoops_IHHPR.flags != null) {
		_hoops_RPGHR		*lea;
		int								edge = 0;

		lea = &_hoops_IPRI->_hoops_IHHPR;

		_hoops_RGGA (edge == _hoops_IPRI->_hoops_SPHA) {
			if (ANYBIT (lea->flags[edge],
						_hoops_APGI|
						_hoops_AHIAA|
						_hoops_SSRRA|
						_hoops_RPGI|
						_hoops_GPGI|
						_hoops_SCICA)) {
				int				_hoops_ISPI, _hoops_CSPI;

				_hoops_HARPGR (_hoops_IPRI, edge, &_hoops_ISPI, &_hoops_CSPI);

				if (!_hoops_APGPGR (_hoops_GHIPH, "\n(Edge %d", (void *)&_hoops_ISPI) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&_hoops_CSPI))
					return false;

				if (BIT (lea->flags[edge], _hoops_APGI)) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Visibility \"edges\")"))
						return false;
				}
				else if (BIT (lea->flags[edge], _hoops_AHIAA)) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Visibility \"no edges\")"))
						return false;
				}

				if (BIT (lea->flags[edge], _hoops_SSRRA)) {
					if (!_hoops_GARPGR (_hoops_GHIPH, "edge", &lea->colors[edge]))
						return false;
				}
				else if (BIT (lea->flags[edge], _hoops_RPGI))
					if (!_hoops_APGPGR (_hoops_GHIPH, "(Color_By_Findex \"edge\" %f)",
										 (void *)&lea->findices[edge]))
						return false;

				if (BIT (lea->flags[edge], _hoops_SCICA))
					if (!_hoops_APGPGR (_hoops_GHIPH, "(Edge_Weight %f)",
										 (void *)&lea->weights[edge]))
						return false;

				if (BIT (lea->flags[edge], _hoops_GPGI)) {
					_hoops_HHHIR *_hoops_IHHIR = HI_LEA_Pattern_Lookup(_hoops_IPRI, lea->_hoops_AHHIR[edge]);
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Edge_Pattern \"") ||
						!_hoops_CRGPGR (_hoops_GHIPH, _hoops_IHHIR->name.text) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
						return false;
				}

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}

			++edge;
		}
	}

	if (_hoops_IPRI->local_face_attributes._hoops_CHHPR() != null) {
		Local_Face_Attributes		*_hoops_CPRI;
		int								face = 0;

		_hoops_CPRI = &_hoops_IPRI->local_face_attributes;

		_hoops_RGGA (face == _hoops_IPRI->face_count) {
			if (ANYBIT (*(_hoops_CPRI->_hoops_CHHPR(face)),
						_hoops_IAGI|
						_hoops_HSIPR|
						LFA_EXPLICIT_COLOR_BY_VALUE|
						LFA_EXPLICIT_COLOR_BY_FINDEX|
						_hoops_HAGI|
						LFA_EXPLICIT_NORMAL)) {
				if (!_hoops_APGPGR (_hoops_GHIPH, "\n(Face %d", (void *)&face))
					return false;

				if (BIT (*(_hoops_CPRI->_hoops_CHHPR(face)), _hoops_IAGI)) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Visibility \"faces\")"))
						return false;
				}
				else if (BIT(*(_hoops_CPRI->_hoops_CHHPR(face)), _hoops_HSIPR)) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Visibility \"no faces\")"))
						return false;
				}

				if (BIT (*(_hoops_CPRI->_hoops_CHHPR(face)), LFA_EXPLICIT_COLOR_BY_VALUE)) {
					if (!_hoops_GARPGR (_hoops_GHIPH, "face", &_hoops_CPRI->colors[face]))
						return false;
				}
				else if (BIT (*(_hoops_CPRI->_hoops_CHHPR(face)), LFA_EXPLICIT_COLOR_BY_FINDEX))
					if (!_hoops_APGPGR (_hoops_GHIPH, "(Color_By_Findex \"face\" %f)",
										 (void *)&_hoops_CPRI->findices[face]))
						return false;

				if (BIT (*(_hoops_CPRI->_hoops_CHHPR(face)), _hoops_HAGI)) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Face_Pattern \"") ||
						!_hoops_PCGPGR (_hoops_GHIPH,
											 (short)_hoops_IRGCR (_hoops_CPRI->_hoops_AHHIR[face])) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
						return false;
				}

				if (BIT (*(_hoops_CPRI->_hoops_CHHPR(face)), LFA_EXPLICIT_NORMAL))
					if (!_hoops_AARPGR (_hoops_GHIPH, (Vector *)&_hoops_CPRI->normals[face]))
						return false;

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}

			++face;
		}
	}

	return true;
} /* _hoops_RSGR _hoops_API "_hoops_GGI _hoops_CPHAR _hoops_AIRC()" */


local bool _hoops_CPRPGR (
	PolyCylinder *				_hoops_HSPIR,
	_hoops_RSSAGR *			info)
{
	_hoops_IRIPH *					_hoops_GHIPH = info->_hoops_GRHRI;
	_hoops_AGHIR *	_hoops_PGHIR;

	if ((_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR) != null) {
		int								vertex = 0;
		_hoops_CGHIR				mask;
		char							buffer[128];
		char							*_hoops_ASAPR;

		_hoops_RGGA (vertex == _hoops_HSPIR->point_count) {
			if (ANYBIT (_hoops_PGHIR->flags[vertex], _hoops_CHSGP)) {
				if (!_hoops_APGPGR (_hoops_GHIPH, "\n(Vertex %d", (void *)&vertex))
					return false;

				/* _hoops_HAIR _hoops_PHSPR _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_SIRAR _hoops_IS _hoops_IRHH _hoops_IPRPGR _hoops_IIPR */

				mask = _hoops_PGHIR->flags[vertex] & _hoops_HHSGP;
				while (mask != 0) {
					RGB					*color;

					_hoops_ASAPR = buffer;
					*_hoops_ASAPR = '\0';
					color = null;

					if (mask == _hoops_HHSGP &&
						_hoops_PGHIR->fcolors[vertex].red ==
						_hoops_PGHIR->ecolors[vertex].red &&

						_hoops_PGHIR->fcolors[vertex].green ==
						_hoops_PGHIR->ecolors[vertex].green &&

						_hoops_PGHIR->fcolors[vertex].blue ==
						_hoops_PGHIR->ecolors[vertex].blue) {
						/* _hoops_GIPR _hoops_RH _hoops_PSHR! */
						color = &_hoops_PGHIR->fcolors[vertex];
						_hoops_ASAPR = HI_Copy_Chars ("geometry", _hoops_ASAPR);
						mask = false;
					}
					else switch (_hoops_RIII (mask)) {		/* _hoops_ARAR _hoops_RRIPR! */
						case _hoops_SHRRA: {
							color = &_hoops_PGHIR->ecolors[vertex];
							_hoops_ASAPR = HI_Copy_Chars ("edge", _hoops_ASAPR);
							mask &= ~_hoops_SHRRA;
						}		_hoops_HHHI;

						case _hoops_GIRRA: {
							if (BIT (mask, _hoops_GIRRA) &&
								(color == null ||
								 color->red	  == _hoops_PGHIR->fcolors[vertex].red	&&
								 color->green == _hoops_PGHIR->fcolors[vertex].green &&
								 color->blue  == _hoops_PGHIR->fcolors[vertex].blue)) {
								if (color != null)
									_hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);

								color = &_hoops_PGHIR->fcolors[vertex];
								_hoops_ASAPR = HI_Copy_Chars ("face", _hoops_ASAPR);
								mask &= ~_hoops_GIRRA;
							}
						}		_hoops_HHHI;
					}
					*_hoops_ASAPR = '\0';

					if (!_hoops_GARPGR (_hoops_GHIPH, buffer, color))
						return false;
				}

				mask = _hoops_PGHIR->flags[vertex] & _hoops_IHSGP;
				while (mask != 0) {
					_hoops_ACGHR	findex;

					_hoops_ASAPR = buffer;
					*_hoops_ASAPR = '\0';
					findex = -1.0f;

					if (mask == _hoops_IHSGP &&
						_hoops_PGHIR->_hoops_IGHIR[vertex] == _hoops_PGHIR->_hoops_HGHIR[vertex]) {
						/* _hoops_GIPR _hoops_RH _hoops_PSHR! */
						findex = _hoops_PGHIR->_hoops_IGHIR[vertex];
						_hoops_ASAPR = HI_Copy_Chars ("geometry", _hoops_ASAPR);
						mask = false;
					}
					else switch (_hoops_RIII (mask)) {		/* _hoops_ARAR _hoops_RRIPR! */
						case _hoops_IHRRA: {
							findex = _hoops_PGHIR->_hoops_HGHIR[vertex];
							_hoops_ASAPR = HI_Copy_Chars ("edge", _hoops_ASAPR);
							mask &= ~_hoops_IHRRA;
						}	 _hoops_HHHI;

						case _hoops_CHRRA: {
							if (BIT (mask, _hoops_CHRRA) &&
								(findex == -1 ||
								 findex == _hoops_PGHIR->_hoops_IGHIR[vertex])) {
								if (findex != -1) _hoops_ASAPR = HI_Copy_Chars (",", _hoops_ASAPR);

								findex = _hoops_PGHIR->_hoops_IGHIR[vertex];
								_hoops_ASAPR = HI_Copy_Chars ("face", _hoops_ASAPR);
								mask &= ~_hoops_CHRRA;
							}
						}		_hoops_HHHI;
					}
					*_hoops_ASAPR = '\0';

					if (!_hoops_APGPGR (_hoops_GHIPH, "(Color_By_Findex %S", (void *)buffer) ||
						!_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)&findex))
						return false;
				}

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}

			++vertex;
		}
	}

	if (BIT (_hoops_HSPIR->flags, _hoops_RSICA)) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(Face 0") ||
			!_hoops_AARPGR (_hoops_GHIPH, &_hoops_HSPIR->_hoops_ACCSA[0]) ||
			!_hoops_CRGPGR (_hoops_GHIPH, ")"))
			return false;
	}
	if (BIT (_hoops_HSPIR->flags, _hoops_ASICA)) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(Face 1") ||
			!_hoops_AARPGR (_hoops_GHIPH, &_hoops_HSPIR->_hoops_ACCSA[1]) ||
			!_hoops_CRGPGR (_hoops_GHIPH, ")"))
			return false;
	}

	return true;
} /* _hoops_RSGR _hoops_API "_hoops_GGI _hoops_RSRRA _hoops_AIRC()" */


local bool _hoops_SPRPGR (
	_hoops_IRIPH *	_hoops_GHIPH,
	Light *		light) {

	if (BIT(light->flags, _hoops_RISGP)) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "\"camera relative\""))
			return false;
	}
	return true;
}



/* _hoops_CPCHR */
local bool _hoops_GHRPGR (
	_hoops_CRCP *			_hoops_SRCP,
	_hoops_RSSAGR *	info,
	bool				_hoops_GPRIC,
	char *				scratch);


local bool _hoops_RHRPGR (
	_hoops_CRCP const *		segment) {

	if (BIT (segment->_hoops_RRHH, _hoops_CCSAGR))
		return true;

	if (segment->_hoops_SGRPR() != null)
		return true;

	return false;
}

/*
 *	_hoops_CGP "_hoops_CAGH" _hoops_SSCP _hoops_HAR _hoops_RPII _hoops_PHPH _hoops_GGSR _hoops_GAPR, _hoops_GGI _hoops_SCH _hoops_IS _hoops_RH _hoops_SCRII
 */
local bool _hoops_AHRPGR (
	_hoops_CRCP const		*segment,
	_hoops_CRCP const		*_hoops_HRSSA,
	bool				_hoops_PHRPGR,
	_hoops_RSSAGR		*info,
	bool				_hoops_GPRIC,
	char					*scratch) {
	_hoops_IRIPH			*_hoops_GHIPH = info->_hoops_GRHRI;

	if (info->_hoops_GGRHH->LookupItem(segment) == VHASH_STATUS_SUCCESS)
		return true;

	if (segment->key > _hoops_SHSSR) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "(Renumber"))
			return false;
	}
	if (segment->priority != 0) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "(Priority"))
			return false;
	}


	if (!_hoops_CRGPGR (_hoops_GHIPH, "(Segment \""))
		return false;

	if (_hoops_PHRPGR) {
		if (segment->name.length != 0 || !_hoops_RHRPGR(segment)) {
			if (!_hoops_APGPGR (_hoops_GHIPH, "%N", (void *)&segment->name))
				return false;
		}
		else if (!_hoops_SGRPGR (info, segment))
			return false;
	}
	else
		if (!_hoops_GRRPGR (info, segment, _hoops_HRSSA))
			return false;

	if (!_hoops_CRGPGR (_hoops_GHIPH, "\" (") ||
		!_hoops_GHRPGR ((_hoops_CRCP *)segment, info, _hoops_GPRIC, scratch) ||
		!_hoops_CRGPGR (_hoops_GHIPH, "))"))
		return false;


	if (segment->priority != 0) {
		if (!_hoops_APGPGR (_hoops_GHIPH, "%d)", (void *)&segment->priority))
			return false;
	}
	if (segment->key > _hoops_SHSSR) {
		if (!_hoops_APGPGR (_hoops_GHIPH, "%D", (void *)&segment->key) ||
			!_hoops_CRGPGR (_hoops_GHIPH,  HI_Has_Local_Key (segment->owner, segment->key)
									? "\"L\")" : "\"G\")"))
			return false;
	}

	return true;
}

local bool _hoops_GRSIR (
	Geometry *			geometry,
	_hoops_RSSAGR *	info,
	char *					scratch) {
	_hoops_IRIPH	*_hoops_GHIPH = info->_hoops_GRHRI;
	bool		_hoops_RAIHR = false;
	int				type;
	Metafile		*_hoops_PHCIH = info->_hoops_PHCIH;

	do {
		bool		_hoops_HHRPGR = false;

		if ((_hoops_GHIPH->_hoops_RPIPH > _hoops_GHIPH->_hoops_SAIPH ||
			 _hoops_GHIPH->_hoops_ASAPR != _hoops_GHIPH->buffer[_hoops_GHIPH->_hoops_RAIPH] &&
			 _hoops_GHIPH->_hoops_ASAPR[-1] == ')') &&
			!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
			return false;

		type = geometry->type;

		/* _hoops_HS _hoops_SR _hoops_AIS _hoops_GPP _hoops_RRIPR _hoops_IGCGA? */
		if (!_hoops_RAIHR && BIT (geometry->_hoops_RRHH, _hoops_PASIR)) {
			if (!_hoops_CRGPGR (_hoops_GHIPH, "(Front ("))
				return false;
			_hoops_RAIHR = true;
		}

		/* _hoops_AA _hoops_SR _hoops_RRP _hoops_IS _hoops_PICII _hoops_PA _hoops_IS _hoops_RH _hoops_CPAP? */
		if (geometry->_hoops_IPPGR != null) {
			if (!_hoops_CRGPGR (_hoops_GHIPH, "(Geometry"))
				return false;
			_hoops_HHRPGR = true;
		}
		else if (geometry->type == _hoops_SCIP || geometry->type == _hoops_GSIP) {
			Local_Vertex_Attributes		*_hoops_SPRI;
			_hoops_RPGHR		*lea;
			Local_Face_Attributes		*_hoops_CPRI;
			Polyhedron					*phon;

			phon = (Polyhedron *)geometry;
			_hoops_SPRI = &phon->local_vertex_attributes;
			lea = &phon->_hoops_IHHPR;
			_hoops_CPRI = &phon->local_face_attributes;

			if (_hoops_SPRI->_hoops_CPIAA != 0				||
				_hoops_SPRI->_hoops_SIIPR != 0				||
				_hoops_SPRI->_hoops_ICRRA != 0		||
				_hoops_SPRI->_hoops_PCRRA != 0		||
				_hoops_SPRI->_hoops_HIRRA != 0			||
				_hoops_SPRI->_hoops_SCHPR != 0		||
				_hoops_SPRI->_hoops_CCHPR != 0		||
				_hoops_SPRI->_hoops_RCRHR != 0		||
				_hoops_SPRI->_hoops_SIRHR != 0		||
				_hoops_SPRI->_hoops_AHIIC != 0					||
				_hoops_SPRI->explicit_normal_count != 0					||
				_hoops_SPRI->_hoops_RSAPA != 0				||

				lea->_hoops_CPIAA != 0				||
				lea->_hoops_SIIPR != 0				||
				lea->_hoops_HSRRA != 0			||
				lea->_hoops_PSRRA != 0		||
				lea->_hoops_SRAPA != 0				||
				lea->_hoops_CCHHC != 0					||

				_hoops_CPRI->_hoops_CPIAA != 0				||
				_hoops_CPRI->_hoops_SIIPR != 0				||
				_hoops_CPRI->_hoops_HSRRA != 0			||
				_hoops_CPRI->_hoops_PSRRA != 0		||
				_hoops_CPRI->_hoops_SRAPA != 0				||
				_hoops_CPRI->explicit_normal_count != 0					||

				phon->local_face_attributes.regions != null	||
				!_hoops_RPRPGR(phon->_hoops_HGAIR)) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Geometry"))
					return false;
				_hoops_HHRPGR = true;
			}
		}
		else if (geometry->type == _hoops_PRCP) {
			if (((_hoops_APPGR *)geometry)->_hoops_GPRIR != null) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Geometry"))
					return false;
				_hoops_HHRPGR = true;
			}
		}
		else if (geometry->type == _hoops_CSIP) {
			PolyCylinder *		_hoops_HSPIR = (PolyCylinder *)geometry;
			_hoops_AGHIR *	_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;

			if (_hoops_PGHIR != null &&
				(_hoops_PGHIR->_hoops_RCRHR != 0		||
				 _hoops_PGHIR->_hoops_SIRHR != 0		||
				 _hoops_PGHIR->_hoops_SCHPR != 0		||
				 _hoops_PGHIR->_hoops_CCHPR != 0) ||
				ANYBIT (_hoops_HSPIR->flags, _hoops_PHSGP)) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Geometry"))
					return false;
				_hoops_HHRPGR = true;
			}
		}
		else if (geometry->type == _hoops_AGCP) {
			if (((_hoops_HACC *)geometry)->region != null ||
				((_hoops_HACC *)geometry)->_hoops_PIHIR != null) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Geometry"))
					return false;
				_hoops_HHRPGR = true;
			}
		}
		else if (geometry->type == _hoops_SGCP) {
			if (BIT (geometry->_hoops_RRHH, _hoops_HGGGA)) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Geometry"))
					return false;
				_hoops_HHRPGR = true;
			}
		}
		else if (geometry->type == _hoops_RIIP ||
				 geometry->type == _hoops_GRCP ||
				 geometry->type == _hoops_RRCP) {
			if (BIT (geometry->_hoops_RRHH, _hoops_HGGGA)) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Geometry"))
					return false;
				_hoops_HHRPGR = true;
			}
		}
		else if (geometry->type == _hoops_IIIP) {
			if (((Polyline *)geometry)->orientation) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Geometry"))
					return false;
				_hoops_HHRPGR = true;
			}
		}
		else if (geometry->type == _hoops_PCIP) {
			if (((Marker *)geometry)->orientation) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Geometry"))
					return false;
				_hoops_HHRPGR = true;
			}
		}

		/* _hoops_HRGR _hoops_SCH _hoops_APPPH? */
		if (geometry->owner != null && geometry->key > _hoops_SHSSR) {
			if (!_hoops_CRGPGR (_hoops_GHIPH, "(Renumber"))
				return false;
		}

		/* _hoops_RH _hoops_CPAP _hoops_ACAS */
		switch (type) {
			case _hoops_SGCP: {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Circle"))
					return false;

				if (BIT (geometry->_hoops_RRHH, _hoops_SHHI)) {
					_hoops_AIHI const *	c = (_hoops_AIHI const *)geometry;
					Point				tmp;

					tmp.z = 0.0f;

					tmp.x = c->center.x + c->radius;
					tmp.y = c->center.y;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;

					tmp.x = c->center.x;
					tmp.y = c->center.y + c->radius;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;

					tmp.x = c->center.x - c->radius;
					tmp.y = c->center.y;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;
				}
				else {
					_hoops_PHPIR const *	c = (_hoops_PHPIR const *)geometry;

					if (!_hoops_IHGPGR (_hoops_GHIPH, &c->start) ||
						!_hoops_IHGPGR (_hoops_GHIPH, &c->_hoops_GGSSR) ||
						!_hoops_IHGPGR (_hoops_GHIPH, &c->end))
						return false;
				}

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case _hoops_RIIP: {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Circular_Arc"))
					return false;

				if (BIT (geometry->_hoops_RRHH, _hoops_RGGGA)) {
					_hoops_SSSSR const *	a = (_hoops_SSSSR const *)geometry;

					if (!_hoops_IHGPGR (_hoops_GHIPH, &a->points[0]) ||
						!_hoops_IHGPGR (_hoops_GHIPH, &a->points[1]) ||
						!_hoops_IHGPGR (_hoops_GHIPH, &a->points[2]))
						return false;
				}
				else if (BIT (geometry->_hoops_RRHH, _hoops_SHHI)) {
					Circular_Arc_Lite const *	a = (Circular_Arc_Lite const *)geometry;
					Point						tmp;
					float						_hoops_GGHCR, _hoops_AGHCR;

					tmp.z = 0.0f;

					_hoops_RICH (a->arc_start * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					tmp.x = a->center.x + _hoops_AGHCR * a->radius;
					tmp.y = a->center.y + _hoops_GGHCR * a->radius;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;

					_hoops_RICH (0.5f * (a->arc_start + a->_hoops_PHHI) * 360.0f,
								_hoops_GGHCR, _hoops_AGHCR);
					tmp.x = a->center.x + _hoops_AGHCR * a->radius;
					tmp.y = a->center.y + _hoops_GGHCR * a->radius;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;

					_hoops_RICH (a->_hoops_PHHI * 360.0f,
								_hoops_GGHCR, _hoops_AGHCR);
					tmp.x = a->center.x + _hoops_AGHCR * a->radius;
					tmp.y = a->center.y + _hoops_GGHCR * a->radius;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;
				}
				else {
					Circular_Arc const *	a = (Circular_Arc const *)geometry;

					if (!_hoops_IHGPGR (_hoops_GHIPH, &a->start) ||
						!_hoops_IHGPGR (_hoops_GHIPH, &a->_hoops_GGSSR) ||
						!_hoops_IHGPGR (_hoops_GHIPH, &a->end))
						return false;
				}

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}  break;

			case _hoops_GRCP: {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Circular_Chord"))
					return false;

				if (BIT (geometry->_hoops_RRHH, _hoops_SHHI)) {
					Circular_Arc_Lite const *	a = (Circular_Arc_Lite const *)geometry;
					Point						tmp;
					float						_hoops_GGHCR, _hoops_AGHCR;

					tmp.z = 0.0f;

					_hoops_RICH (a->arc_start * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					tmp.x = a->center.x + _hoops_AGHCR * a->radius;
					tmp.y = a->center.y + _hoops_GGHCR * a->radius;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;

					_hoops_RICH (0.5f * (a->arc_start + a->_hoops_PHHI) * 360.0f,
								_hoops_GGHCR, _hoops_AGHCR);
					tmp.x = a->center.x + _hoops_AGHCR * a->radius;
					tmp.y = a->center.y + _hoops_GGHCR * a->radius;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;

					_hoops_RICH (a->_hoops_PHHI * 360.0f,
								_hoops_GGHCR, _hoops_AGHCR);
					tmp.x = a->center.x + _hoops_AGHCR * a->radius;
					tmp.y = a->center.y + _hoops_GGHCR * a->radius;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;
				}
				else {
					Circular_Arc const *	a = (Circular_Arc const *)geometry;

					if (!_hoops_IHGPGR (_hoops_GHIPH, &a->start) ||
						!_hoops_IHGPGR (_hoops_GHIPH, &a->_hoops_GGSSR) ||
						!_hoops_IHGPGR (_hoops_GHIPH, &a->end))
						return false;
				}

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}  break;

			case _hoops_RRCP: {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Circular_Wedge"))
					return false;

				if (BIT (geometry->_hoops_RRHH, _hoops_SHHI)) {
					Circular_Arc_Lite const *	a = (Circular_Arc_Lite const *)geometry;
					Point						tmp;
					float						_hoops_GGHCR, _hoops_AGHCR;

					tmp.z = 0.0f;

					_hoops_RICH (a->arc_start * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					tmp.x = a->center.x + _hoops_AGHCR * a->radius;
					tmp.y = a->center.y + _hoops_GGHCR * a->radius;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;

					_hoops_RICH (0.5f * (a->arc_start + a->_hoops_PHHI) * 360.0f,
								_hoops_GGHCR, _hoops_AGHCR);
					tmp.x = a->center.x + _hoops_AGHCR * a->radius;
					tmp.y = a->center.y + _hoops_GGHCR * a->radius;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;

					_hoops_RICH (a->_hoops_PHHI * 360.0f,
								_hoops_GGHCR, _hoops_AGHCR);
					tmp.x = a->center.x + _hoops_AGHCR * a->radius;
					tmp.y = a->center.y + _hoops_GGHCR * a->radius;
					if (!_hoops_IHGPGR (_hoops_GHIPH, &tmp))
						return false;
				}
				else {
					Circular_Arc const *	a = (Circular_Arc const *)geometry;

					if (!_hoops_IHGPGR (_hoops_GHIPH, &a->start) ||
						!_hoops_IHGPGR (_hoops_GHIPH, &a->_hoops_GGSSR) ||
						!_hoops_IHGPGR (_hoops_GHIPH, &a->end))
						return false;
				}

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}  break;

			case _hoops_HGPGR: {
				_hoops_HHPIR const *		_hoops_RPPA = (_hoops_HHPIR const *)geometry;

				if (_hoops_RPPA->count == 1) {
					if (!_hoops_APGPGR (_hoops_GHIPH, "(Cutting_Plane %f", (void *)&_hoops_RPPA->planes->a) ||
						!_hoops_APGPGR (_hoops_GHIPH, " %f", (void *)&_hoops_RPPA->planes->b) ||
						!_hoops_APGPGR (_hoops_GHIPH, " %f", (void *)&_hoops_RPPA->planes->c) ||
						!_hoops_APGPGR (_hoops_GHIPH, " %f)", (void *)&_hoops_RPPA->planes->d))
						return false;
				}
				else {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Cutting_Section") ||
						!_hoops_SCGPGR (_hoops_GHIPH, _hoops_RPPA->count, _hoops_RPPA->planes) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}
			}	break;

			case _hoops_ICIP: {
				Light				*light = (Light *)geometry;

				switch (light->_hoops_PRR) {
					case _hoops_H: {
						_hoops_HIPIR const *	dl = (_hoops_HIPIR const *)light;

						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Distant_Light") ||
							!_hoops_AHGPGR (_hoops_GHIPH, (Point const *)&dl->original) ||
							!_hoops_SPRPGR (_hoops_GHIPH, light) ||
							!_hoops_CRGPGR (_hoops_GHIPH, ")"))
							return false;
					}	break;

					case _hoops_C: {
						_hoops_AIPIR const *		pl = (_hoops_AIPIR const *)light;

						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Local_Light") ||
							!_hoops_AHGPGR (_hoops_GHIPH, &pl->position) ||
							!_hoops_SPRPGR (_hoops_GHIPH, light) ||
							!_hoops_CRGPGR (_hoops_GHIPH, ")"))
							return false;
					}	break;

					case _hoops_I: {
						Point			position, target;
						char			options[256];

						PUSHNAME(info->_hoops_RIGC);
						HC_Show_Spot_Light (_hoops_AIRIR (light),
											&position, &target, options);
						POPNAME(info->_hoops_RIGC);

						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Spot_Light") ||
							!_hoops_IHGPGR (_hoops_GHIPH, &position) ||
							!_hoops_IHGPGR (_hoops_GHIPH, &target) ||
							!_hoops_CAGPGR (_hoops_GHIPH, options) ||
							!_hoops_CRGPGR (_hoops_GHIPH, ")"))
							return false;
					}	break;

					case _hoops_S: {
						_hoops_SHPIR const *		al = (_hoops_SHPIR const *)light;

						int				count;
						char			list[256];

						PUSHNAME(info->_hoops_RIGC);
						HC_Show_Area_Light_Count (_hoops_AIRIR(light),
												  &count, list);
						POPNAME(info->_hoops_RIGC);

						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Area_Light") ||
							!_hoops_CCGPGR (_hoops_GHIPH, al->count, al->points) ||
							!_hoops_CAGPGR (_hoops_GHIPH, list) ||
							!_hoops_CRGPGR (_hoops_GHIPH, ")"))
							return false;
					}	break;
				}
			}	break;

			case _hoops_CGCP: {
				Ellipse const *				ellipse = (Ellipse *)geometry;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Ellipse") ||
					!_hoops_IHGPGR (_hoops_GHIPH, &ellipse->center) ||
					!_hoops_IHGPGR (_hoops_GHIPH, &ellipse->major) ||
					!_hoops_IHGPGR (_hoops_GHIPH, &ellipse->minor) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case _hoops_GIIP: {
				Elliptical_Arc const *		_hoops_ACAIP = (Elliptical_Arc *)geometry;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Elliptical_Arc") ||
					!_hoops_IHGPGR (_hoops_GHIPH, &_hoops_ACAIP->center) ||
					!_hoops_IHGPGR (_hoops_GHIPH, &_hoops_ACAIP->major) ||
					!_hoops_IHGPGR (_hoops_GHIPH, &_hoops_ACAIP->minor) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_ACAIP->arc_start) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)&_hoops_ACAIP->_hoops_PHHI))
					return false;
			}	break;

			case _hoops_ASIP: {
				Cylinder const *			_hoops_CPSSA = (Cylinder const *)geometry;
				char const *				_hoops_ACGH = "";

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Cylinder") ||
					!_hoops_IHGPGR (_hoops_GHIPH, &_hoops_CPSSA->axis[0]) ||
					!_hoops_IHGPGR (_hoops_GHIPH, &_hoops_CPSSA->axis[1]) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_CPSSA->radius))
					return false;

				switch (_hoops_CPSSA->flags) {
					case _hoops_ASCSA:	   _hoops_ACGH = "none";	break;
					case _hoops_IHHIA:   _hoops_ACGH = "first";	break;
					case _hoops_SHHIA:  _hoops_ACGH = "second"; break;
					case _hoops_PSCSA:	   _hoops_ACGH = "both";	break;
				}
				if (!_hoops_CAGPGR (_hoops_GHIPH, _hoops_ACGH) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case _hoops_GGCP: {
				Grid	  *grid = (Grid *)geometry;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Grid"))
					return false;
				if (grid->_hoops_APIAA == _hoops_SPARP) {
					if (!_hoops_CAGPGR (_hoops_GHIPH, "Radial"))
						return false;
				}
				else {
					if (!_hoops_CAGPGR (_hoops_GHIPH, "Quadrilateral"))
						return false;
				}

				if (!_hoops_IHGPGR (_hoops_GHIPH, &grid->origin) ||
					!_hoops_IHGPGR (_hoops_GHIPH, &grid->ref1) ||
					!_hoops_IHGPGR (_hoops_GHIPH, &grid->ref2) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&grid->count1) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&grid->count2) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case _hoops_PIIP: {
				Point const *		pl = ((Line const *)geometry)->points;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Line") ||
					!_hoops_AHGPGR (_hoops_GHIPH, &pl[0]) ||
					!_hoops_AHGPGR (_hoops_GHIPH, &pl[1]) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case _hoops_HIIP: {
				Point const *		pl = ((_hoops_SHRIR const *)geometry)->points;
				int const *			mapping = ((_hoops_SHRIR const *)geometry)->mapping;
				int					count = -((_hoops_SHRIR const *)geometry)->count / 2;
				_hoops_CRCP const *		_hoops_SRCP = geometry->owner;

				if (_hoops_SRCP->type != _hoops_IRCP)
					_hoops_SRCP = null;

				while (count-- > 0) {
					Key				_hoops_CPCAS = HOOPS_WORLD->_hoops_GCHCA.table[*mapping++ & ~_hoops_RIRIR].key;

					if (_hoops_SRCP != null && _hoops_CPCAS > _hoops_SHSSR) {
						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Renumber"))
							return false;
					}

					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Line") ||
						!_hoops_AHGPGR (_hoops_GHIPH, &pl[0]) ||
						!_hoops_AHGPGR (_hoops_GHIPH, &pl[1]) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;

					if (_hoops_SRCP != null && _hoops_CPCAS > _hoops_SHSSR) {
						if (!_hoops_APGPGR (_hoops_GHIPH, "%D", (void *)&_hoops_CPCAS) ||
							!_hoops_CRGPGR (_hoops_GHIPH, HI_Has_Local_Key (_hoops_SRCP, _hoops_CPCAS) ? "\"L\")" : "\"G\")"))
							 return false;
					}

					pl += 2;
				}
			}	break;

			case _hoops_PCIP: {
				if (!_hoops_HCGPGR (_hoops_GHIPH, "Marker",
									&((Marker const *)geometry)->_hoops_CSAI))
					return false;

				if (((Marker const *)geometry)->orientation) {
					char options[128];
					HI_Show_Geometry_Options(geometry, options, -1);
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Geometry_Options") ||
						!_hoops_CAGPGR (_hoops_GHIPH, options) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}
			}	break;

			case _hoops_PIRS: {
				Point const *		pl = ((_hoops_GRPGR const *)geometry)->points;
				int const *			mapping = ((_hoops_GRPGR const *)geometry)->mapping;
				int					count = ((_hoops_GRPGR const *)geometry)->count;
				_hoops_CRCP const *		_hoops_SRCP = geometry->owner;

				if (_hoops_SRCP->type != _hoops_IRCP)
					_hoops_SRCP = null;

				while (count-- > 0) {
					Key				_hoops_PPCAS = HOOPS_WORLD->_hoops_GCHCA.table[*mapping++ & ~_hoops_RIRIR].key;

					if (_hoops_SRCP != null && _hoops_PPCAS > _hoops_SHSSR) {
						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Renumber"))
							return false;
					}

					if (!_hoops_HCGPGR (_hoops_GHIPH, "Marker", pl++))
							return false;

					if (_hoops_SRCP != null && _hoops_PPCAS > _hoops_SHSSR) {
						if (!_hoops_APGPGR (_hoops_GHIPH, "%D", (void *)&_hoops_PPCAS) ||
							!_hoops_CRGPGR (_hoops_GHIPH, HI_Has_Local_Key (_hoops_SRCP, _hoops_PPCAS) ? "\"L\")" : "\"G\")"))
							 return false;
					}
				}
			}	break;

			case _hoops_GSIP: {
				if (!_hoops_SSGPGR (_hoops_GHIPH, (_hoops_AIHPR *)geometry))
					return false;
			}	break;

			case _hoops_IIIP: {
				Polyline const *		polyline = (Polyline const *)geometry;

				if (polyline->count < 0) {
					if (!_hoops_PSGPGR (_hoops_GHIPH, "Polyline_Segments",
						Abs(polyline->count),
						polyline->points))
						return false;
				}
				else {
					if (!_hoops_PSGPGR (_hoops_GHIPH, "Polyline",
						polyline->count,
						polyline->points))
						return false;
				}

				if (polyline->orientation) {
					char options[128];
					HI_Show_Geometry_Options(geometry, options, -1);
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Geometry_Options") ||
						!_hoops_CAGPGR (_hoops_GHIPH, options) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}
			}	break;

			case _hoops_SIIP: {
				Point const *		pl = ((Polyline const *)geometry)->points;

				if (BIT (geometry->_hoops_RRHH, _hoops_IHHCA)) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Infinite_Ray") ||
						!_hoops_AHGPGR (_hoops_GHIPH, &pl[0]) ||
						!_hoops_AHGPGR (_hoops_GHIPH, &pl[1]) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}
				else {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Infinite_Line") ||
						!_hoops_AHGPGR (_hoops_GHIPH, &pl[0]) ||
						!_hoops_AHGPGR (_hoops_GHIPH, &pl[1]) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}
			}	break;

			case _hoops_CSIP: {
				PolyCylinder *			_hoops_HSPIR = (PolyCylinder *)geometry;
				char const *			_hoops_ACGH = "";

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(PolyCylinder ") ||
					!_hoops_CCGPGR (_hoops_GHIPH, _hoops_HSPIR->point_count, _hoops_HSPIR->points) ||
					!_hoops_RSGPGR (_hoops_GHIPH, _hoops_HSPIR->_hoops_ISPIR, _hoops_HSPIR->radii))
					return false;

				switch (_hoops_HSPIR->flags & _hoops_PPSSA) {
					case _hoops_ASCSA:	   _hoops_ACGH = "none";	break;
					case _hoops_IHHIA:   _hoops_ACGH = "first";	break;
					case _hoops_SHHIA:  _hoops_ACGH = "second"; break;
					case _hoops_PSCSA:	   _hoops_ACGH = "both";	break;
				}
				if (!_hoops_CAGPGR (_hoops_GHIPH, _hoops_ACGH) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case _hoops_HSIP: {
				Sphere const *		sphere = (Sphere const *)geometry;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Sphere") ||
					!_hoops_IHGPGR (_hoops_GHIPH, &sphere->data.center) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&sphere->data.radius))
					return false;

				if (sphere->_hoops_CSPIR) {
					if (!_hoops_CHGPGR (_hoops_GHIPH, &sphere->_hoops_CSPIR[0]) ||
						!_hoops_CHGPGR (_hoops_GHIPH, &sphere->_hoops_CSPIR[1]))
						return false;
				}
				else {
					if (!_hoops_CHGPGR (_hoops_GHIPH, &_hoops_IRGA::_hoops_RCPCR) ||
						!_hoops_CHGPGR (_hoops_GHIPH, &_hoops_IRGA::X_Axis))
						return false;
				}
				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case _hoops_CHIP: {
#ifndef _hoops_CCPIR
				_hoops_PIRGR *_hoops_SCPIR = (_hoops_PIRGR *)geometry;
				int knot_count = _hoops_SCPIR->control_point_count + _hoops_SCPIR->degree + 1;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(NURBS_Curve") ||
					!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&_hoops_SCPIR->degree) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&_hoops_SCPIR->control_point_count) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_SCPIR->start_u) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_SCPIR->end_u))
					return false;

				if (!_hoops_CCGPGR (_hoops_GHIPH, _hoops_SCPIR->control_point_count,
											  _hoops_SCPIR->control_points))
					return false;
				if (!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
					return false;

				if (_hoops_SCPIR->knots != null) {
					if (!_hoops_ASGPGR (_hoops_GHIPH, "Knots", knot_count, _hoops_SCPIR->knots))
						return false;
				}
				if (_hoops_SCPIR->weights != null) {
					if (!_hoops_ASGPGR (_hoops_GHIPH, "Weights", _hoops_SCPIR->control_point_count,
											_hoops_SCPIR->weights))
						return false;
				}
				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
#endif
			}	break;

			case _hoops_PRCP: {
#ifndef _hoops_GSPIR
				_hoops_APPGR *surface = (_hoops_APPGR *)geometry;
				int _hoops_RSPIR = surface->n_u_vertices + surface->u_degree + 1;
				int _hoops_ASPIR = surface->n_v_vertices + surface->v_degree + 1;
				int control_point_count = surface->n_u_vertices * surface->n_v_vertices;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(NURBS_Surface") ||
					!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&surface->u_degree) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&surface->v_degree) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&surface->n_u_vertices) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&surface->n_v_vertices))
					return false;

				if (!_hoops_CCGPGR (_hoops_GHIPH, control_point_count,
											  surface->control_points))
					return false;
				if (!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
					return false;
				if (surface->u_knots != null) {
					if (!_hoops_ASGPGR (_hoops_GHIPH, "u_Knots", _hoops_RSPIR, surface->u_knots))
						return false;
				}
				if (surface->v_knots != null) {
					if (!_hoops_ASGPGR (_hoops_GHIPH, "v_Knots", _hoops_ASPIR, surface->v_knots))
						return false;
				}
				if (surface->weights != null) {
					if (!_hoops_ASGPGR (_hoops_GHIPH, "Weights", control_point_count,
											surface->weights))
						return false;
				}
				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
#endif
			}	break;

			case _hoops_RCIP: {
				Polygon const *		polygon = (Polygon const *)geometry;

				if (!_hoops_PSGPGR (_hoops_GHIPH, "Polygon",
											   polygon->count,
											   polygon->points))
					return false;
			}	break;

			case _hoops_HGCP: {
				if (!_hoops_CSGPGR (info, (Image *)geometry, scratch))
					return false;
			}	break;

			case _hoops_SCIP: {
				Shell		*_hoops_SPHPR = (Shell *)geometry;
				int				_hoops_IGIAP = _hoops_PHCIH->_hoops_IGIAP;

				if (_hoops_IGIAP == _hoops_AGIAP) {
					if (_hoops_SPHPR->face_list == null && _hoops_SPHPR->tristrips != null)
						_hoops_IGIAP = _hoops_HGIAP;
					else
						_hoops_IGIAP = _hoops_PGIAP;
				}

				if (_hoops_IGIAP == _hoops_HGIAP) {
					int _hoops_IHRPGR, _hoops_CHRPGR;
					int *_hoops_SHRPGR = null, *_hoops_GIRPGR = null;

					HC_Show_Shell_By_Tristrips_Size (_hoops_SPHPR->key,
											null, &_hoops_IHRPGR, &_hoops_CHRPGR);
					if (_hoops_IHRPGR != 0)
						ALLOC_ARRAY (_hoops_SHRPGR, _hoops_IHRPGR, int);
					if (_hoops_CHRPGR != 0)
						ALLOC_ARRAY (_hoops_GIRPGR, _hoops_CHRPGR, int);
					HC_Show_Shell_By_Tristrips (_hoops_SPHPR->key,
											null, null,
											&_hoops_IHRPGR, _hoops_SHRPGR,
											&_hoops_CHRPGR, _hoops_GIRPGR);

					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Shell_By_Tristrips") ||
						!_hoops_CCGPGR (_hoops_GHIPH, _hoops_SPHPR->point_count, _hoops_SPHPR->points) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\n") ||
						!_hoops_GSGPGR (_hoops_GHIPH, _hoops_IHRPGR, _hoops_SHRPGR) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\n") ||
						!_hoops_GSGPGR (_hoops_GHIPH, _hoops_CHRPGR, _hoops_GIRPGR) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;

					if (_hoops_SHRPGR)
						FREE_ARRAY (_hoops_SHRPGR, _hoops_IHRPGR, int);
					if (_hoops_GIRPGR)
						FREE_ARRAY (_hoops_GIRPGR, _hoops_CHRPGR, int);
				}
				else {
					if (_hoops_SPHPR->face_list == null && _hoops_SPHPR->tristrips != null)
						HI_Face_List_From_Tristrips (info->_hoops_RIGC, _hoops_SPHPR);

					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Shell") ||
						!_hoops_CCGPGR (_hoops_GHIPH, _hoops_SPHPR->point_count, _hoops_SPHPR->points) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\n") ||
						!_hoops_GSGPGR (_hoops_GHIPH, _hoops_SPHPR->face_list_length, _hoops_SPHPR->face_list) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}
			}	break;

			case _hoops_AGCP: {
				_hoops_HACC			*text = (_hoops_HACC *)geometry;
				Karacter		*_hoops_IHSCP = text->karacters;
				char			*_hoops_ASAPR = scratch;
				int				count = text->count;
				int				length;

				PUSHNAME(info->_hoops_RIGC);
				HC_Show_Text_Length (_hoops_AIRIR(text), &length);
				POPNAME(info->_hoops_RIGC);

				if (length >= _hoops_HCSAGR - 1) {
					_hoops_GHIPH->message = "Text primitive is longer than the internal buffer - truncated";
					HI_Report_File_Error (_hoops_GHIPH);

					count = _hoops_HCSAGR - 1;
				}

				if (text->encoding == _hoops_SACSR)
					HI_Return_Kars (_hoops_ASAPR, -1, _hoops_IHSCP, count, _hoops_RGHPH);
				else
					HI_Return_Kars (_hoops_ASAPR, -1, _hoops_IHSCP, count, text->encoding);

				if (text->encoding == _hoops_SSAIP) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Text"))
						return false;
				}
				else {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Text_With_Encoding"))
							return false;
				}

				if (!_hoops_AHGPGR (_hoops_GHIPH, &text->_hoops_CSAI))
					return false;

				if (text->encoding != _hoops_SSAIP) {
					char	buf[100];

					HI_Show_Encoding_Type (buf, -1, text->encoding);

					if (!_hoops_CAGPGR (_hoops_GHIPH, buf))
						return false;
				}

				if (text->encoding == _hoops_SACSR || text->encoding == _hoops_RGHPH) {
					if (!_hoops_SAGPGR (_hoops_GHIPH, scratch, 2*count))
						return false;
				}
				else if (text->encoding == _hoops_GSPPH) {
					H_UTF8 _hoops_ASPPH;
					_hoops_ASPPH.encodedText((utf8_char const*) scratch);
					if (!_hoops_CAGPGR (_hoops_GHIPH, (char const*)_hoops_ASPPH.encodedText()))
						return false;
				}
				else if (text->encoding == _hoops_AGHPH) {
					H_UTF16 _hoops_RSPPH;
					_hoops_RSPPH.encodedText((utf16_char const*) scratch);
					H_UTF8 _hoops_ASPPH(_hoops_RSPPH);
					if (!_hoops_CAGPGR (_hoops_GHIPH, (char const*)_hoops_ASPPH.encodedText()))
						return false;
				}
				else if (text->encoding == _hoops_HSPPH) {
					H_UTF32 _hoops_ISPPH;
					_hoops_ISPPH.encodedText((utf32_char const*) scratch);
					H_UTF8 _hoops_ASPPH(_hoops_ISPPH);
					if (!_hoops_CAGPGR (_hoops_GHIPH, (char const*)_hoops_ASPPH.encodedText()))
						return false;
				}
				else if (text->encoding == _hoops_SSPPH || text->encoding == _hoops_CSPPH) {
					H_WCS _hoops_GGHPH;
					_hoops_GGHPH.encodedText((wchar_t const*) scratch);
					H_UTF8 _hoops_ASPPH(_hoops_GGHPH);
					if (!_hoops_CAGPGR (_hoops_GHIPH, (char const*)_hoops_ASPPH.encodedText()))
						return false;
				}
				else {
					if (!_hoops_CAGPGR (_hoops_GHIPH, scratch))
						return false;
				}

				if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case _hoops_AHIP: {
				_hoops_GHIPH->message =
				"Internal error -  Geometry references not supported in metafiles.";
				HI_Report_File_Error (_hoops_GHIPH);
			}	break;

			default: {
				char	*_hoops_ASAPR;

				if ((_hoops_ASAPR = HI_Sprintf1 (scratch, scratch + _hoops_HCSAGR - 1,
									   "Internal Error: Unknown Geometry:%d",
									   (void *)&type)) != null) {
					if (_hoops_ASAPR != scratch + _hoops_HCSAGR - 1)
						*_hoops_ASAPR = '\0';
					_hoops_GHIPH->message = scratch;
					HI_Report_File_Error (_hoops_GHIPH);
				}
			}	break;
		}

		/* _hoops_RGHH _hoops_RCCGS */
		if (geometry->key > _hoops_SHSSR) {
			_hoops_CRCP *		_hoops_SRCP = geometry->owner;

			if (_hoops_SRCP != null &&
				_hoops_SRCP->type == _hoops_IRCP) {
				if (!_hoops_APGPGR (_hoops_GHIPH, "%D", (void *)&geometry->key) ||
					!_hoops_CRGPGR (_hoops_GHIPH, HI_Has_Local_Key (_hoops_SRCP, geometry->key) ? "\"L\")" : "\"G\")"))
					 return false;
			}
		}

		if (_hoops_HHRPGR) {
			/* _hoops_RIRPGR _hoops_CPAP _hoops_PAPA _hoops_AIRC */
			if (geometry->_hoops_IPPGR != null)
				_hoops_APRPGR (geometry->_hoops_IPPGR, null, info, scratch);


			/* _hoops_CPAP-_hoops_SASI _hoops_AIRC */
			if (geometry->type == _hoops_SCIP || geometry->type == _hoops_GSIP) {
				Polyhedron					*phon;

				phon = (Polyhedron *)geometry;

				if (!_hoops_HPRPGR (phon, info))
					return false;

				if (!BIT (_hoops_PHCIH->value, _hoops_IIHAP)) {
					if (!_hoops_PPRPGR ((_hoops_HPAH *)phon, info, scratch))
						return false;
				}
			}
#ifndef _hoops_GSPIR
			else if (geometry->type == _hoops_PRCP) {
				_hoops_APPGR *_hoops_SCPIR = (_hoops_APPGR *)geometry;

				if (!_hoops_SARPGR (_hoops_GHIPH, _hoops_SCPIR->_hoops_GPRIR, false))
					return false;
			}
#endif
			else if (geometry->type == _hoops_CSIP) {
				PolyCylinder *	_hoops_HSPIR = (PolyCylinder *)geometry;

				if (!_hoops_CPRPGR (_hoops_HSPIR, info))
					return false;
			}
			else if (geometry->type == _hoops_AGCP) {
				_hoops_HACC *			text = (_hoops_HACC *)geometry;

				if (text->region != null) {
					char			options[256];

					if (!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
						return false;
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Text_Region "))
						return false;
					if (!_hoops_CCGPGR (_hoops_GHIPH, text->region->count,
												  text->region->points))
						return false;

					HI_Show_Text_Region_Options (text->region, options);

					if (!_hoops_CAGPGR (_hoops_GHIPH, options) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}


				if (text->_hoops_PIHIR != null) {
					int i;

					PUSHNAME(info->_hoops_RIGC);
					for (i=0; i<text->count; i++) {
						_hoops_HIHIR *_hoops_RGHGGR = &text->_hoops_PIHIR[i];

						if (_hoops_RGHGGR->_hoops_HAICA != 0) {
							if (!_hoops_APGPGR (_hoops_GHIPH, "\n(Character_Attribute %d", (void *)&i))
								return false;

							HC_MShow_Character_Attributes(_hoops_AIRIR(geometry), i, 1, scratch);

							if (!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
								!_hoops_CRGPGR (_hoops_GHIPH, ")"))
								return false;
						}
					}
					POPNAME(info->_hoops_RIGC);
				}
			}
			else if (geometry->type == _hoops_SGCP ||
					 geometry->type == _hoops_RIIP ||
					 geometry->type == _hoops_GRCP ||
					 geometry->type == _hoops_RRCP) {
				if (!_hoops_HCGPGR (_hoops_GHIPH, "Center",
									&((_hoops_PHPIR const *)geometry)->center))
					return false;
			}

			/* _hoops_GGGR _hoops_RGR _hoops_CPAP */
			if (!_hoops_CRGPGR (_hoops_GHIPH, ")"))
				return false;
		}
	} while ((geometry = geometry->next) != null);

	/* _hoops_RPP _hoops_SR _hoops_GHACI _hoops_RRIPR _hoops_CIPH, _hoops_GGGR _hoops_RH _hoops_AIRPGR */
	if (_hoops_RAIHR) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "))"))
			return false;
	}
	return true;
} /* _hoops_RSGR _hoops_API _hoops_PIRPGR */


local bool _hoops_APRPGR (
	Attribute *				_hoops_ASGPR,
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_RSSAGR *		info,
	char *					scratch)
{
	_hoops_IRIPH *				_hoops_GHIPH = info->_hoops_GRHRI;
	Metafile *				_hoops_PHCIH = info->_hoops_PHCIH;
	int						_hoops_ISGPGR;
	char const *			p;
	int						type;

	do {
		if ((_hoops_GHIPH->_hoops_RPIPH > _hoops_GHIPH->_hoops_SAIPH ||
			 _hoops_GHIPH->_hoops_ASAPR != _hoops_GHIPH->buffer[_hoops_GHIPH->_hoops_RAIPH] &&
			 _hoops_GHIPH->_hoops_ASAPR[-1] == ')') &&
			!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
			return false;

		switch (_hoops_ASGPR->type) {
			case HK_COLOR: {
				if (!_hoops_HIGPGR (_hoops_GHIPH, _hoops_ASGPR, BIT (_hoops_PHCIH->value, _hoops_RIHAP)))
					return false;
			}	break;

			case _hoops_GRAIR: {
				if (((_hoops_RRAIR const *)_hoops_ASGPR)->flag)
					p = "on";
				else
					p = "off";
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Streaming_Mode \"") ||
					!_hoops_CRGPGR (_hoops_GHIPH, p) ||
					!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
					return false;
			}	break;

			case HK_STYLE: {
				Style		*style = (Style *)_hoops_ASGPR;

				if (BIT (_hoops_PHCIH->value, _hoops_CHHAP) &&
					style->_hoops_IGRPR != null &&
					info->_hoops_GGRHH->LookupItem(style->_hoops_IGRPR) != VHASH_STATUS_SUCCESS) {
					if (!_hoops_AHRPGR (style->_hoops_IGRPR, _hoops_SRCP, false, info, false, scratch) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
						return false;
				}

				if (style->key > _hoops_SHSSR && _hoops_SRCP != null) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Renumber"))
						return false;
				}

				if (style->_hoops_IGRPR) {
					if (style->condition.count == 0) {
						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Style_Segment \"") ||
							!_hoops_GRRPGR (info, style->_hoops_IGRPR, _hoops_SRCP) ||
							!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
							return false;
					}
					else {
						char			condition[2048];

						HI_Show_Conditional (&style->condition, condition, -1);
						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Conditional_Style \"") ||
							!_hoops_GRRPGR (info, style->_hoops_IGRPR, _hoops_SRCP) ||
							!_hoops_CRGPGR (_hoops_GHIPH, "\" \"") ||
							!_hoops_CRGPGR (_hoops_GHIPH, condition) ||
							!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
							return false;
					}
				}
				else {
					if (style->condition.count == 0) {
						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Named_Style \"") ||
							!_hoops_APGPGR (_hoops_GHIPH, "%n", (void *)&style->_hoops_SGAIR) ||
							!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
							return false;
					}
					else {
						char			condition[2048];

						HI_Show_Conditional (&style->condition, condition, -1);
						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Conditional_Named_Style \"") ||
							!_hoops_APGPGR (_hoops_GHIPH, "%n", (void *)&style->_hoops_SGAIR) ||
							!_hoops_CRGPGR (_hoops_GHIPH, "\" \"") ||
							!_hoops_CRGPGR (_hoops_GHIPH, condition) ||
							!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
							return false;
					}
				}

				if (style->key > _hoops_SHSSR && _hoops_SRCP != null) {
					if (!_hoops_APGPGR (_hoops_GHIPH, "%D", (void *)&style->key) ||
						!_hoops_CRGPGR (_hoops_GHIPH, HI_Has_Local_Key (_hoops_SRCP, style->key) ? "\"L\")" : "\"G\")"))
						return false;
				}
			}	break;

			case HK_CAMERA: {
				_hoops_HHRA *_hoops_SPH = (_hoops_HHRA *)_hoops_ASGPR;
				bool _hoops_SACRP = _hoops_GHIPH->_hoops_CPIPH;

				if (BIT (_hoops_PHCIH->value, _hoops_CIHAP)) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, ";;"))
						return false;
					_hoops_GHIPH->_hoops_CPIPH = true;
				}
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Camera") ||
					!_hoops_IHGPGR (_hoops_GHIPH, &_hoops_SPH->position) ||
					!_hoops_IHGPGR (_hoops_GHIPH, &_hoops_SPH->target) ||
					!_hoops_CHGPGR (_hoops_GHIPH, &_hoops_SPH->up_vector) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f",
									 (void *)&_hoops_SPH->_hoops_ISPA) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f \"",
									 (void *)&_hoops_SPH->_hoops_SSPA))
					return false;

				if (_hoops_SPH->_hoops_HHCH != 0.0f ||
					_hoops_SPH->_hoops_IHCH != 0.0f) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "Oblique "))
						return false;
				}
				switch (_hoops_SPH->projection) {
					default:
						_hoops_GHIPH->message =
						"Internal error -  Unknown camera projection";
						HI_Report_File_Error (_hoops_GHIPH);
						_hoops_HHHI;

					case _hoops_GHH:
						p = "Perspective";
						break;
					case _hoops_CPPCR:
						p = "Orthographic";
						break;
					case _hoops_SSIH:
						p = "Stretched";
						break;
				}
				if (!_hoops_CRGPGR (_hoops_GHIPH, p))
					return false;
				if (_hoops_SPH->_hoops_HHCH != 0.0f ||
					_hoops_SPH->_hoops_IHCH != 0.0f) {
					if (_hoops_SPH->_hoops_IHCH == 0.0f) {
						if (!_hoops_APGPGR (_hoops_GHIPH, "=%f",
									(void *)&_hoops_SPH->_hoops_HHCH))
							return false;
					}
					else {
						if (!_hoops_APGPGR (_hoops_GHIPH, "=(%f,",
									(void *)&_hoops_SPH->_hoops_HHCH) ||
							!_hoops_APGPGR (_hoops_GHIPH, "%f)",
									(void *)&_hoops_SPH->_hoops_IHCH))
							return false;
					}
				}
				if (!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
					return false;

				if (_hoops_SPH->_hoops_SIPCR != &HOOPS_WORLD->_hoops_GCPCR) {
					if ((_hoops_GHIPH->_hoops_RPIPH > _hoops_GHIPH->_hoops_SAIPH ||
						 _hoops_GHIPH->_hoops_ASAPR != _hoops_GHIPH->buffer[_hoops_GHIPH->_hoops_RAIPH] &&
						 _hoops_GHIPH->_hoops_ASAPR[-1] == ')') &&
						!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
						return false;
					if (BIT (_hoops_PHCIH->value, _hoops_CIHAP))
						if (!_hoops_CRGPGR (_hoops_GHIPH, ";;"))
							return false;

					if (!_hoops_APGPGR (_hoops_GHIPH, "(Camera_Near_Limit %f)",
										 (void *)_hoops_SPH->_hoops_SIPCR))
						return false;
				}

				_hoops_GHIPH->_hoops_CPIPH = _hoops_SACRP;
			}	break;

			case HK_CLIP_REGION: {
				_hoops_IRAIR const *		_hoops_CRAIR = (_hoops_IRAIR const *)_hoops_ASGPR;

				if (BIT (_hoops_CRAIR->flags, _hoops_SPAGA)) {
					if (BIT(_hoops_CRAIR->flags, _hoops_RHIH))
						p = "world,type=mask";
					else
						p = "world,type=clip";
				}
				else {
					if (BIT(_hoops_CRAIR->flags, _hoops_RHIH))
						p = "window,type=mask";
					else
						p = "window,type=clip";
				}

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Clip_Region") ||
					!_hoops_GSGPGR (_hoops_GHIPH, 1, &_hoops_CRAIR->count) ||
					!_hoops_CCGPGR (_hoops_GHIPH, _hoops_CRAIR->count,
												_hoops_CRAIR->points) ||
					!_hoops_CRGPGR (_hoops_GHIPH, "\"") ||
					!_hoops_CRGPGR (_hoops_GHIPH, p) ||
					!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
					return false;
			}	break;

			case HK_HANDEDNESS: {
				if (((_hoops_ARAIR const *)_hoops_ASGPR)->which == _hoops_RAACA)
					p = "right";
				else
					p = "left";

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Handedness \"") ||
					!_hoops_CRGPGR (_hoops_GHIPH, p) ||
					!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
					return false;
			}	break;

			case HK_SELECTABILITY: {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Selectability"))
					return false;

				_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
				HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
				HI_Show_Selectability ((_hoops_ASAIR *)_hoops_ASGPR, scratch, -1);
				HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

				if (!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case HK_VISIBILITY: {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Visibility"))
					return false;

				_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
				HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
				HI_Show_Visibility ((_hoops_RSAIR *)_hoops_ASGPR, scratch, -1);
				HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

				if (!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case HK_WINDOW: {
				Window *				window = (Window *)_hoops_ASGPR;

				if (!_hoops_APGPGR (_hoops_GHIPH, "(Window %f", (void *)&window->_hoops_RCHS.left) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&window->_hoops_RCHS.right) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&window->_hoops_RCHS.bottom) ||
					!_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)&window->_hoops_RCHS.top))
					return false;
			}	break;

			case HK_WINDOW_FRAME: {
				_hoops_GSAIR const *	_hoops_IGGCH = (_hoops_GSAIR const *)_hoops_ASGPR;

				if (BIT(_hoops_IGGCH->flags, _hoops_PIARP))
					if (BIT(_hoops_IGGCH->flags, _hoops_CIARP))
						if (BIT(_hoops_IGGCH->flags, _hoops_HIARP))
							p = "single, inset, decorative";
						else
							p = "single, decorative";
					else
						if (BIT(_hoops_IGGCH->flags, _hoops_HIARP))
							p = "single, inset";
						else
							p = "single";
				else if (BIT(_hoops_IGGCH->flags, _hoops_AIARP))
					if (BIT(_hoops_IGGCH->flags, _hoops_CIARP))
						if (BIT(_hoops_IGGCH->flags, _hoops_HIARP))
							p = "on, inset, decorative";
						else
							p ="on, decorative";
					else
						if (BIT(_hoops_IGGCH->flags, _hoops_HIARP))
							p = "on, inset";
						else
							p ="on";
				else
					if (BIT(_hoops_IGGCH->flags, _hoops_IIARP))
						p = "off";
					else
					if (BIT(_hoops_IGGCH->flags, _hoops_HIARP))
						p = "off, inset";
					else
						p = "off, no inset";

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Window_Frame \"") ||
					!_hoops_CRGPGR (_hoops_GHIPH, p) ||
					!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
					return false;
			}	break;

			case HK_COLOR_MAP: {
#ifndef DISABLE_COLOR_MAPS
				_hoops_RHAH			*_hoops_CSIR = (_hoops_RHAH *)_hoops_ASGPR;
				int					i = _hoops_CSIR->length;
/* _hoops_RSPRA: _hoops_IGPC */
				Named_Material	   *_hoops_ISHIR = _hoops_CSIR->_hoops_HAA;

				while (i-- != 0) {
					if (_hoops_ISHIR->_hoops_PRGRA != M_DIFFUSE) break;
					++_hoops_ISHIR;
				}

				_hoops_ISHIR = _hoops_CSIR->_hoops_HAA;

				if (i < 0) {	/* _hoops_SPI _hoops_RGAR -- _hoops_HSH _hoops_IHRI */
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Color_Map_By_Value \"RGB\" ("))
					  return false;

					i = _hoops_CSIR->length;
					while (i-- != 0) {
						if (!_hoops_APGPGR (_hoops_GHIPH, "(%f", (void *)&_hoops_ISHIR->_hoops_CSHR.red) ||
							!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_ISHIR->_hoops_CSHR.green) ||
							!_hoops_APGPGR (_hoops_GHIPH, "%f)", (void *)&_hoops_ISHIR->_hoops_CSHR.blue))
							return false;
						++_hoops_ISHIR;
					}
					if (!_hoops_CRGPGR (_hoops_GHIPH, "))"))
						return false;
				}
				else {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Color_Map \""))
						return false;

					i = _hoops_CSIR->length;
					while (i-- != 0) {
						if (!_hoops_AIGPGR (_hoops_GHIPH, _hoops_ISHIR))
							return false;
						++_hoops_ISHIR;
						if (i > 0)
							if (!_hoops_CRGPGR (_hoops_GHIPH, ","))
								return false;
					}
					if (!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
						return false;
				}
#endif
			}	break;

			case _hoops_CPPIR: {
				_hoops_SPPIR const *		conditions = (_hoops_SPPIR const *)_hoops_ASGPR;
				_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
				HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;

				if (conditions->count > 0) {
					HI_Show_Conditions (conditions, scratch, -1);

					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Conditions") ||
						!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")\n"))
						return false;
				}

				if (conditions->_hoops_ACPGR != null) {
					_hoops_PCACA const *	action = conditions->_hoops_ACPGR;

					do {
						char const *			action_type = null;
						char					options[128];

						switch (action->type) {
							case _hoops_CRPCA:	action_type = "prune segment";		break;
						}

						HI_Show_One_Conditional_Action (info->_hoops_RIGC, conditions, action_type,
														options, scratch);


						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Conditional_Action"))
							return false;

						if (options[0] == '\0') {
							if (!_hoops_CAGPGR (_hoops_GHIPH, action_type))
								return false;
						}
						else {
							char				_hoops_HIRPGR[256];

							Sprintf_SS (_hoops_HIRPGR, "%s=(%s)", action_type, options);
							if (!_hoops_CAGPGR (_hoops_GHIPH, _hoops_HIRPGR))
								return false;
						}

						if (!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
							!_hoops_CRGPGR (_hoops_GHIPH, ")\n"))
							return false;
					} while ((action = action->next) != null);
				}

				HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;
			}	break;

			case HK_DRIVER_OPTIONS: {
				_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
				HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
				HI_Show_Driver_Options ((_hoops_GAPIR *)_hoops_ASGPR, scratch, -1);
				HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

				_hoops_GHIPH->_hoops_CPIPH = true;
				if (!_hoops_CRGPGR (_hoops_GHIPH, ";; (Driver_Options") ||
					!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
				_hoops_GHIPH->_hoops_CPIPH = false;
				if (!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
					return false;
			}	break;

			case HK_LINE_PATTERN: {
				_hoops_PSAIR const *	_hoops_HSAIR = (_hoops_PSAIR const *)_hoops_ASGPR;
				if (_hoops_HSAIR->mask == 0) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Line_Pattern ") ||
						!_hoops_SRRPGR (_hoops_GHIPH, &_hoops_HSAIR->line_style, _hoops_HSAIR->value) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}
				else {
					_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
					HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
					HI_Show_Line_Pattern_Explicit (info->_hoops_RIGC, (_hoops_PSAIR *)_hoops_ASGPR, scratch, -1);
					HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Line_Pattern_Explicit ") ||
						!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}
			}	break;

			case HK_EDGE_PATTERN: {
				_hoops_ISAIR const *	_hoops_CSAIR = (_hoops_ISAIR const *)_hoops_ASGPR;
				if (_hoops_CSAIR->mask == 0) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Edge_Pattern ") ||
						!_hoops_SRRPGR (_hoops_GHIPH, &_hoops_CSAIR->line_style, _hoops_CSAIR->value) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}
				else {
					_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
					HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
					HI_Show_Edge_Pattern_Explicit (info->_hoops_RIGC, (_hoops_ISAIR *)_hoops_ASGPR, scratch, -1);
					HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Edge_Pattern_Explicit ") ||
						!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}
			}	break;

			case HK_FACE_PATTERN: {
				_hoops_IHCAP const *		fp = (_hoops_IHCAP const *)_hoops_ASGPR;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Face_Pattern") ||
					!_hoops_PCGPGR (_hoops_GHIPH, fp->value) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case HK_WINDOW_PATTERN: {
				_hoops_CHCAP const *		_hoops_GARIP = (_hoops_CHCAP const *)_hoops_ASGPR;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Window_Pattern") ||
					!_hoops_PCGPGR (_hoops_GHIPH, _hoops_GARIP->value) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case HK_HEURISTICS: {
				_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
				HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
				HI_Show_Heuristics ((_hoops_GHAIR *)_hoops_ASGPR, scratch, -1);
				HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Heuristics") ||
					!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case HK_RENDERING_OPTIONS: {
				_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
				HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
				HI_Show_Rendering_Options ((_hoops_RHAIR *)_hoops_ASGPR, scratch, -1);
				HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Rendering_Options") ||
					!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case HK_TEXT_FONT: {
				_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
				HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
				HI_Show_Text_Font ((_hoops_AGPIR *)_hoops_ASGPR, scratch, -1);
				HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Text_Font") ||
					!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;
			}	break;

			case HK_CALLBACK: {
#ifndef DISABLE_CALLBACKS
				_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
				HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
				HI_Show_Callback ((_hoops_GCHIR *)_hoops_ASGPR, scratch, -1, 0);
				HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Callback") ||
					!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
					return false;

#endif
			}	break;

			case HK_LINE_WEIGHT: {
				_hoops_GHCAP const *		_hoops_CGRIP = (_hoops_GHCAP const *)_hoops_ASGPR;

				if (_hoops_CGRIP->data._hoops_HHP == _hoops_SHGRP) {
					if (!_hoops_APGPGR (_hoops_GHIPH, "(Line_Weight %f)", (void *)&_hoops_CGRIP->data.value))
						return false;
				}
				else {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Variable_Line_Weight \"") ||
						!_hoops_APGPGR (_hoops_GHIPH, "%f ", (void *)&_hoops_CGRIP->data.value) ||
						!_hoops_CRGPGR (_hoops_GHIPH, _hoops_GHIHH[(int)_hoops_CGRIP->data._hoops_HHP]) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
						return false;
				}
			}	break;

			case HK_EDGE_WEIGHT: {
				_hoops_RHCAP const *		_hoops_PSGIP = (_hoops_RHCAP const *)_hoops_ASGPR;

				if (_hoops_PSGIP->data._hoops_HHP == _hoops_SHGRP) {
					if (!_hoops_APGPGR (_hoops_GHIPH, "(Edge_Weight %f)", (void *)&_hoops_PSGIP->data.value))
					return false;
				}
				else {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Variable_Edge_Weight \"") ||
						!_hoops_APGPGR (_hoops_GHIPH, "%f ", (void *)&_hoops_PSGIP->data.value) ||
						!_hoops_CRGPGR (_hoops_GHIPH, _hoops_GHIHH[(int)_hoops_PSGIP->data._hoops_HHP]) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
						return false;
				}
			}	break;

			case HK_MARKER_SIZE: {
				_hoops_AHCAP const *		_hoops_IRPP = (_hoops_AHCAP const *)_hoops_ASGPR;

				if (_hoops_IRPP->data._hoops_HHP == _hoops_SHGRP) {
					if (!_hoops_APGPGR (_hoops_GHIPH, "(Marker_Size %f)", (void *)&_hoops_IRPP->data.value))
					return false;
				}
				else {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Variable_Marker_Size \"") ||
						!_hoops_APGPGR (_hoops_GHIPH, "%f ", (void *)&_hoops_IRPP->data.value) ||
						!_hoops_CRGPGR (_hoops_GHIPH, _hoops_GHIHH[(int)_hoops_IRPP->data._hoops_HHP]) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
						return false;
				}
			}	break;

			case HK_TEXT_SPACING: {
				_hoops_PHCAP const * _hoops_RSHHC = (_hoops_PHCAP const *)_hoops_ASGPR;

				if (!_hoops_APGPGR (_hoops_GHIPH, "(Text_Spacing %f)", (void *)&_hoops_RSHHC->data.value))
					return false;
			}	break;

			case HK_MARKER_SYMBOL: {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Marker_Symbol \"") ||
					!_hoops_CRGPGR (_hoops_GHIPH, ((_hoops_GICAP const *)_hoops_ASGPR)->name.text) ||
					!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
					return false;
			}	break;

			case HK_MODELLING_MATRIX: {
				float const *	_hoops_RICIR = &((_hoops_ISGI const *)_hoops_ASGPR)->matrix.elements[0][0];
				int				i;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Modelling_Matrix ("))
					return false;

				for (i=0; i<4; ++i) {
					if (!_hoops_CRGPGR (_hoops_GHIPH, "("))
						return false;
					if (!_hoops_AHGPGR (_hoops_GHIPH, (Point *)_hoops_RICIR))
						return false;
					_hoops_RICIR += 4;
					if (i != 3) {
						if (!_hoops_CRGPGR (_hoops_GHIPH, "0)"))
							return false;
					}
					else {
						if (!_hoops_CRGPGR (_hoops_GHIPH, "1)))"))
							return false;
					}
				}
			}	break;

			case HK_TEXTURE_MATRIX: {
#ifndef DISABLE_TEXTURING
				float const *	_hoops_RICIR = &((_hoops_GAAIR const *)_hoops_ASGPR)->matrix.elements[0][0];
				int				i;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Texture_Matrix ("))
					return false;

				for (i=0; i<4; ++i) {
					if (!_hoops_SHGPGR(_hoops_GHIPH, _hoops_RICIR))
						return false;
					_hoops_RICIR += 4;
				}
				if (!_hoops_CRGPGR (_hoops_GHIPH, "))"))
					return false;
#endif
		   }   break;

			case _hoops_RAAIR: {
				_hoops_AAAIR const *		_hoops_AAGIH = (_hoops_AAAIR const *)_hoops_ASGPR;

				for (int i=0; i<_hoops_AAGIH->count; ++i) {
					_hoops_GASC const &		glyph = _hoops_AAGIH->glyphs[i];

					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Glyph_Definition \"") ||
						!_hoops_HPGPGR (_hoops_GHIPH, &glyph->name) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\" ("))
						return false;

					for (unsigned int n=0; n<glyph->length; ++n) {
						int c = glyph->data[n];
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d ", (void *)&c))
							return false;
					}

					if (!_hoops_CRGPGR (_hoops_GHIPH, "))\n"))
						return false;
				}
			}	break;

			case _hoops_RPAIR: {
				_hoops_APAIR const *	_hoops_IIRPGR = (_hoops_APAIR const *)_hoops_ASGPR;
				int i;

				for (i=0; i<_hoops_IIRPGR->count; i++) {
					Line_Style const &	_hoops_ACCI = _hoops_IIRPGR->_hoops_HPAIR[i];

					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Line_Style_Definition \"") ||
						!_hoops_HPGPGR (_hoops_GHIPH, &_hoops_ACCI->name) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\" \"") ||
						!_hoops_HPGPGR (_hoops_GHIPH, &_hoops_ACCI->definition) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\")\n"))
						return false;
				}
			}	break;

			case _hoops_HAAIR: {
				_hoops_IAAIR const *		_hoops_CIRPGR = (_hoops_IAAIR const *)_hoops_ASGPR;

				for (int i=0; i<_hoops_CIRPGR->count; ++i) {
					_hoops_GPAIR const &		_hoops_SGAIR = _hoops_CIRPGR->_hoops_SAAIR[i];

					if (BIT (_hoops_PHCIH->value, _hoops_CHHAP) &&
						_hoops_SGAIR->segment != null &&
						info->_hoops_GGRHH->LookupItem(_hoops_SGAIR->segment) != VHASH_STATUS_SUCCESS) {
						if (!_hoops_AHRPGR (_hoops_SGAIR->segment, _hoops_SRCP, false, info, false, scratch) ||
							!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
							return false;
					}

					if (!_hoops_CRGPGR (_hoops_GHIPH, "(Named_Style_Definition \"") ||
						!_hoops_HPGPGR (_hoops_GHIPH, &_hoops_SGAIR->name) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\" \"") ||
						!_hoops_GRRPGR (info, _hoops_SGAIR->segment, _hoops_SRCP) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\")\n"))
						return false;
				}
			}	break;

			case _hoops_IPAIR: {
#ifndef DISABLE_TEXTURING
				_hoops_CPAIR const *	_hoops_CICSR = (_hoops_CPAIR const *)_hoops_ASGPR;
				_hoops_RCR		*texture;
				int				i;
				bool		_hoops_SIRPGR = false;

				_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
				if (_hoops_CICSR->count > 0) {
					/* _hoops_RGAR _hoops_RRP _hoops_IRS _hoops_SPCS _hoops_IGS _hoops_RPP _hoops_SR _hoops_CHR _hoops_GPP _hoops_RH _hoops_CGRHH _hoops_CAGH (_hoops_GPP _hoops_CIGS _hoops_SRRPR) */
					if (info->_hoops_ASSAGR != null &&
						info->_hoops_ASSAGR->next == null &&
						info->_hoops_ASSAGR->segment == _hoops_SRCP) {
						for (i=0; i<_hoops_CICSR->count; i++) {
							texture = _hoops_CICSR->textures[i];

							if (!BIT (texture->flags,_hoops_RPRRP)) {
								if (!_hoops_CRGPGR (_hoops_GHIPH, "(Segment \".\" (\n"))
									return false;
								_hoops_SIRPGR = true;
								break;
							}
						}
					}
				}

				for (i=0; i<_hoops_CICSR->count; i++) {
					texture = _hoops_CICSR->textures[i];

					if (!BIT (texture->flags, _hoops_RPRRP)) {
						if (texture->_hoops_IRARP != null &&
							BIT (_hoops_PHCIH->value, _hoops_CHHAP) &&
							info->_hoops_GGRHH->LookupItem(texture->_hoops_IRARP) != VHASH_STATUS_SUCCESS) {
							if (!_hoops_AHRPGR (texture->_hoops_IRARP, _hoops_SRCP, false, info, true, scratch) ||
								!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
								return false;
						}
						if (texture->_hoops_SRARP != null &&
							BIT (_hoops_PHCIH->value, _hoops_CHHAP) &&
							info->_hoops_GGRHH->LookupItem(texture->_hoops_SRARP) != VHASH_STATUS_SUCCESS) {
							if (!_hoops_AHRPGR (texture->_hoops_SRARP, _hoops_SRCP, false, info, true, scratch) ||
								!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
								return false;
						}


						if (BIT (texture->_hoops_SCR, _hoops_GSR)) {
							char *_hoops_GCRPGR;
							bool status;

							if (!_hoops_CRGPGR (_hoops_GHIPH, "(Shader") ||
								!_hoops_CAGPGR (_hoops_GHIPH, _hoops_PRIGI (null, "%qn", &texture->name)))
								return false;

							HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
							ALLOC_ARRAY_CACHED (_hoops_GCRPGR, _hoops_HCSAGR, char);
							HI_Show_Texture (info->_hoops_RIGC, texture, scratch, -1, _hoops_GCRPGR, -1, true, 0);
							HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

							status = (_hoops_CAGPGR (_hoops_GHIPH, scratch) &&
										_hoops_CRGPGR (_hoops_GHIPH, "\n") &&
										_hoops_CAGPGR (_hoops_GHIPH, _hoops_GCRPGR) &&
										_hoops_CRGPGR (_hoops_GHIPH, ")\n"));
							FREE_ARRAY (_hoops_GCRPGR, _hoops_HCSAGR, char);
							if (!status)
								return false;
						}
						else {
							if (!_hoops_CRGPGR (_hoops_GHIPH, "(Texture") ||
								!_hoops_CAGPGR (_hoops_GHIPH, _hoops_PRIGI (null, "%qn", &texture->name)))
								return false;

							HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
							HI_Show_Texture (info->_hoops_RIGC, texture, scratch, -1, null, 0, true, 0);
							HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

							if (!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
								!_hoops_CRGPGR (_hoops_GHIPH, ")\n"))
								return false;
						}
					}
				}

				if (_hoops_SIRPGR)
					if (!_hoops_CRGPGR (_hoops_GHIPH, "))\n"))
						return false;
#endif
			}	break;

			case HK_TEXT_ALIGNMENT: {
				_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;
				HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
				HI_Show_Text_Alignment ((_hoops_SHCAP *)_hoops_ASGPR, scratch, -1);
				HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Text_Alignment \"") ||
					!_hoops_CRGPGR (_hoops_GHIPH, scratch) ||
					!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
						return false;
			}	break;

			case HK_TEXT_PATH: {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Text_Path") ||
					!_hoops_AHGPGR (_hoops_GHIPH, (Point *)&((_hoops_RGPIR const *)_hoops_ASGPR)->value) ||
					!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
			}	break;

			case HK_USER_OPTIONS: {
				if (!_hoops_GHGPGR (info->_hoops_RIGC, _hoops_GHIPH, (_hoops_HPPIR *)_hoops_ASGPR))
						return false;
			}	break;

			case HK_USER_VALUE: {
				if (!_hoops_APGPGR (_hoops_GHIPH, "(User_Value 0x%X)",(void *)&((_hoops_RHPIR const *)_hoops_ASGPR)->data))
					return false;
			}	break;

			case HK_DRIVER: {
			}	break;

			default: {
				char			*_hoops_ASAPR;

				type = _hoops_ASGPR->type;

				if ((_hoops_ASAPR = HI_Sprintf1 (scratch, scratch + _hoops_HCSAGR - 2, "Internal Error: Unknown Attribute #%d",(void *)&type)) != null) {
					*_hoops_ASAPR = '\0';
					_hoops_GHIPH->message = scratch;
					HI_Report_File_Error (_hoops_GHIPH);
				}
			}	break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	return true;
}




/*
 *	_hoops_IISH _hoops_GGSR _hoops_RH _hoops_SRGR _hoops_IIGR _hoops_RH _hoops_CAGH '_hoops_PHHIP'
 */
local bool _hoops_GHRPGR (
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_RSSAGR *		info,
	bool					_hoops_GPRIC,
	char *					scratch)
{
	_hoops_IRIPH			*_hoops_GHIPH = info->_hoops_GRHRI;
	Metafile			*_hoops_PHCIH = info->_hoops_PHCIH;
	int					type;

	if (_hoops_GPRIC)
		_hoops_PSSAGR (info, _hoops_SRCP);

  top:;

	info->_hoops_GGRHH->InsertItem(_hoops_SRCP);

	if (_hoops_SRCP->_hoops_IPPGR != null)
		_hoops_APRPGR (_hoops_SRCP->_hoops_IPPGR, _hoops_SRCP, info, scratch);

	/* _hoops_IPSP-_hoops_CHIA _hoops_IASC _hoops_HRGR _hoops_RCRPGR _hoops_PII _hoops_PCCP _hoops_IGRI... */
	if (_hoops_SRCP->bounding != null &&
		BIT (_hoops_SRCP->bounding->flags, _hoops_CCIIR)) {
		if (_hoops_GHIPH->_hoops_RPIPH > _hoops_GHIPH->_hoops_SAIPH &&
			!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
			return false;

		if (BIT (_hoops_SRCP->bounding->flags, _hoops_HAPGP)) {
			if (!_hoops_CRGPGR (_hoops_GHIPH, "(Bounding_Cuboid") ||
				!_hoops_IHGPGR (_hoops_GHIPH, &_hoops_SRCP->bounding->cuboid.min) ||
				!_hoops_IHGPGR (_hoops_GHIPH, &_hoops_SRCP->bounding->cuboid.max) ||
				!_hoops_CRGPGR (_hoops_GHIPH, ")"))
				return false;
		}
		else {
			if (!_hoops_CRGPGR (_hoops_GHIPH, "(Bounding_Sphere") ||
				!_hoops_IHGPGR (_hoops_GHIPH, &_hoops_SRCP->bounding->sphere.center) ||
				!_hoops_APGPGR (_hoops_GHIPH, "%f", (void *)&_hoops_SRCP->bounding->sphere.radius) ||
				!_hoops_CRGPGR (_hoops_GHIPH, ")"))
				return false;
		}
	}

	if (_hoops_SRCP->geometry != null)
		_hoops_GRSIR (_hoops_SRCP->geometry, info, scratch);

	if (_hoops_SRCP->_hoops_RGRPR != null) {
		Subsegment	*_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR;
		bool		_hoops_RAIHR = false;

		do {
			if ((_hoops_GHIPH->_hoops_RPIPH > _hoops_GHIPH->_hoops_SAIPH ||
				 _hoops_GHIPH->_hoops_ASAPR != _hoops_GHIPH->buffer[_hoops_GHIPH->_hoops_RAIPH] &&
				 _hoops_GHIPH->_hoops_ASAPR[-1] == ')') &&
				!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
				return false;

			type = _hoops_SSGPR->type;

			if (!_hoops_RAIHR && BIT (_hoops_SSGPR->_hoops_RRHH, _hoops_PASIR) && _hoops_SSGPR->priority != 0) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "(Front ("))
					return false;
				_hoops_RAIHR = true;
			}

			switch (type) {
				case _hoops_AGRPR: {
					_hoops_PGRPR *		include = (_hoops_PGRPR *)_hoops_SSGPR;
					_hoops_CRCP *		_hoops_RIHHH = (_hoops_CRCP alter *)include->_hoops_IGRPR;

					if (BIT (_hoops_PHCIH->value, _hoops_CHHAP) &&
						info->_hoops_GGRHH->LookupItem(_hoops_RIHHH) != VHASH_STATUS_SUCCESS) {
						if (!_hoops_AHRPGR (_hoops_RIHHH, _hoops_SRCP, false, info, true, scratch) ||
							!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
							return false;
					}

					/* _hoops_HS _hoops_IS _hoops_SHH _hoops_RCRR _hoops_RH _hoops_ACRPGR _hoops_HRGR _hoops_RAS _hoops_RH _hoops_PCRPGR */
					if (include->key > _hoops_SHSSR) {
						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Renumber"))
							return false;
					}
					if (include->priority != 0 && !BIT(include->_hoops_RRHH, _hoops_HPAPA)) {
						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Priority"))
							return false;
					}

					if (include->condition.count == 0) {
						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Include_Segment \"") ||
							!_hoops_GRRPGR (info, include->_hoops_IGRPR, _hoops_SRCP) ||
							!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
							return false;
					}
					else {
						char			condition[2048];

						HI_Show_Conditional (&include->condition, condition, -1);
						if (!_hoops_CRGPGR (_hoops_GHIPH, "(Conditional_Include \"") ||
							!_hoops_GRRPGR (info, include->_hoops_IGRPR, _hoops_SRCP) ||
							!_hoops_CRGPGR (_hoops_GHIPH, "\" \"") ||
							!_hoops_CRGPGR (_hoops_GHIPH, condition) ||
							!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
							return false;
					}

					if (include->priority != 0 && !BIT(include->_hoops_RRHH, _hoops_HPAPA)) {
						if (!_hoops_APGPGR (_hoops_GHIPH, "%d)",
											 (void *)&include->priority))
							return false;
					}
					if (include->key > _hoops_SHSSR) {
						if (!_hoops_APGPGR (_hoops_GHIPH, "%D", (void *)&include->key) ||
							!_hoops_CRGPGR (_hoops_GHIPH, HI_Has_Local_Key (_hoops_SRCP, include->key) ? "\"L\")" : "\"G\")"))
							return false;
					}
				}	break;

				case _hoops_IRCP: {
					if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {
						_hoops_SRCP = (_hoops_CRCP *)_hoops_SSGPR;
						goto top;
					}

					if (!_hoops_AHRPGR ((_hoops_CRCP *)_hoops_SSGPR, _hoops_SRCP, true,
									 info, false, scratch))
						return false;
				}	break;

				default: {
					char	*_hoops_ASAPR;
					if ((_hoops_ASAPR = HI_Sprintf1 (scratch, scratch + _hoops_HCSAGR - 1,
										   "Internal Error: Unknown Subsegment:%d",
										   (void *)&type)) != null) {
						if (_hoops_ASAPR != scratch + _hoops_HCSAGR - 1)
							*_hoops_ASAPR = '\0';
						_hoops_GHIPH->message = scratch;
						HI_Report_File_Error (_hoops_GHIPH);
					}
				}	break;
			}
		} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);

		if (_hoops_RAIHR) {
			 if (!_hoops_CRGPGR (_hoops_GHIPH, "))"))
				 return false;
		}
	}

	if (_hoops_SRCP->_hoops_SSRIR() != null) {
		if (!BIT (_hoops_PHCIH->value, _hoops_IIHAP)) {
			if (!_hoops_PPRPGR ((_hoops_HPAH *)_hoops_SRCP, info, scratch))
				return false;
		}
	}

	if (_hoops_GPRIC)
		_hoops_HSSAGR (info);

	return true;
}


local bool _hoops_HCRPGR (
	_hoops_IRIPH	*_hoops_GHIPH,
	_hoops_SIRIR	*_hoops_ICRPGR) {

	/* _hoops_GHHA _hoops_RHIR _hoops_PPR _hoops_AA _hoops_RPAC _hoops_ARIPR _hoops_SRS */
	if (_hoops_ICRPGR->next != null)
		if (!_hoops_HCRPGR (_hoops_GHIPH, _hoops_ICRPGR->next))
			return false;

	switch (_hoops_ICRPGR->_hoops_GCRIR) {
		case _hoops_RCRIR: {
			if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(Segment_Is_Open \"") ||
				!_hoops_APGPGR (_hoops_GHIPH, "%p", (void *)_hoops_ICRPGR->info.segment._hoops_PCRIR) ||
				!_hoops_CRGPGR (_hoops_GHIPH, "\")"))
				return false;
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Metafiling of Open geom/face/edge/vertex: Not written yet!");
		}	break;
	}

	return true;
}


local bool _hoops_CCRPGR (
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_IRIPH *				_hoops_GHIPH,
	int						_hoops_SCRPGR,
	int						_hoops_GSRPGR,
	_hoops_RSSAGR	*		info,
	char *					scratch)
{
	int						_hoops_RSRPGR;
	bool					_hoops_ASRPGR = true;
	_hoops_CRCP const *			_hoops_PSRPGR;

	UNREFERENCED(_hoops_GSRPGR);
	UNREFERENCED(scratch);
	UNREFERENCED(info);
	UNREFERENCED(_hoops_SRCP);
	UNREFERENCED(_hoops_ASRPGR);
	UNREFERENCED(_hoops_PSRPGR);

	if (_hoops_SCRPGR == 0)
		return true;

	_hoops_RSRPGR = HOOPS_WORLD->_hoops_RAPPR;

#ifndef DISABLE_TEXTURING

	_hoops_PSRPGR = _hoops_RSPPR(info->_hoops_RIGC, _hoops_RPGHP);

	_hoops_PCCAR {
		if (_hoops_PSRPGR == _hoops_SRCP) {
			_hoops_ASRPGR = false;
			break;
		}

		if (_hoops_PSRPGR == HOOPS_WORLD->root) break;
		_hoops_PSRPGR = _hoops_PSRPGR->owner;
	}


	if (BIT (_hoops_SCRPGR, _hoops_ICHAP) && _hoops_ASRPGR) {

		_hoops_CPAIR *	_hoops_CICSR = (_hoops_CPAIR*)HI_Find_Attribute(info->_hoops_RIGC, (_hoops_HPAH *)_hoops_RSPPR(info->_hoops_RIGC, _hoops_RPGHP),-_hoops_IPAIR);

		if (_hoops_CICSR) {
			bool	_hoops_HSRPGR = false;
			int		_hoops_ISGPGR = HOOPS_WORLD->_hoops_RAPPR;

			for (int i=0; i<_hoops_CICSR->count; i++) {

				_hoops_RCR *	texture=_hoops_CICSR->textures[i];

				if (texture->image &&
					!BIT (texture->image->_hoops_RRHH, _hoops_HGAGR) &&
					info->_hoops_GGRHH->LookupItem(texture->image) != VHASH_STATUS_SUCCESS) {

					/* _hoops_RRP _hoops_IRS _hoops_HGHC _hoops_IS _hoops_PPSI _hoops_SCH... */
					if (!_hoops_HSRPGR) {
						if (!_hoops_CRGPGR (_hoops_GHIPH,
						  "\n(Segment \"/\" (\n"))
							return false;
						_hoops_HSRPGR = true;
					}

					if (!_hoops_CSGPGR (info, texture->image,scratch))
						return false;
				}
			}

			for (int i=0; i<_hoops_CICSR->count; i++) {

				_hoops_RCR *	texture=_hoops_CICSR->textures[i];

				if (!BIT (texture->flags,_hoops_RPRRP)) {
					if (!_hoops_HSRPGR) {
						if (!_hoops_CRGPGR (_hoops_GHIPH,
						  "\n(Segment \"/\" ("))
							return false;
						_hoops_HSRPGR = true;
					}

					if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(Texture \"") ||
						!_hoops_HPGPGR (_hoops_GHIPH, &texture->name) ||
						!_hoops_CRGPGR (_hoops_GHIPH, "\""))
						return false;

					HOOPS_WORLD->_hoops_RAPPR = _hoops_HCSAGR;
					HI_Show_Texture (info->_hoops_RIGC, texture, scratch, -1, null, 0, true, 0);
					HOOPS_WORLD->_hoops_RAPPR = _hoops_ISGPGR;

					if (!_hoops_CAGPGR (_hoops_GHIPH, scratch) ||
						!_hoops_CRGPGR (_hoops_GHIPH, ")"))
						return false;
				}
			}

			if (_hoops_HSRPGR) {
				if (!_hoops_CRGPGR (_hoops_GHIPH, "))"))
					return false;
			}

			_hoops_HPRH(_hoops_CICSR);
		}
	}
#endif

	return true;
}



/*
 *	_hoops_IISH _hoops_PHPPR _hoops_PPR _hoops_HAIR _hoops_PAIGR _hoops_PPR _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH
 *	_hoops_IS _hoops_RH _hoops_SCRII
 */
local bool _hoops_ISRPGR (
	_hoops_CRCP *			_hoops_SRCP,
	_hoops_IRIPH *			_hoops_GHIPH,
	int					_hoops_SCRPGR,
	int					_hoops_GSRPGR,
	_hoops_RSSAGR *	info,
	char *				scratch) {
	int					_hoops_RSRPGR;
	int					id;

	id = info->_hoops_RIGC->_hoops_IAPCR;

	UNREFERENCED(scratch);
	UNREFERENCED(info);
	UNREFERENCED(_hoops_GSRPGR);
	UNREFERENCED(_hoops_SRCP);

	if (_hoops_SCRPGR == 0)
		return true;

	_hoops_RSRPGR = HOOPS_WORLD->_hoops_RAPPR;

#ifndef DISABLE_SEARCH
	if (BIT (_hoops_SCRPGR, _hoops_RCHAP)) {
		char	name[4096], expansion [4096];

		PUSHNAME(info->_hoops_RIGC);
		HC_Begin_Alias_Search ();
		HOOPS_WORLD->_hoops_RAPPR = _hoops_GGAPR (name);
		while (HI_Find_Alias (info->_hoops_RIGC, name, -1)) {
			HOOPS_WORLD->_hoops_RAPPR = _hoops_GGAPR (expansion);
			HI_Show_Alias (info->_hoops_RIGC, name, expansion, -1);
			POPNAME(info->_hoops_RIGC);
			if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(Alias") ||
				!_hoops_CAGPGR (_hoops_GHIPH, name) ||
				!_hoops_CAGPGR (_hoops_GHIPH, expansion) ||
				!_hoops_CRGPGR (_hoops_GHIPH, ")")) {
				HOOPS_WORLD->_hoops_RAPPR = _hoops_RSRPGR;
				return false;
			}
			PUSHNAME(info->_hoops_RIGC);
		}
		HC_End_Alias_Search ();
		POPNAME(info->_hoops_RIGC);
	}

	if (BIT (_hoops_SCRPGR, _hoops_ACHAP)) {
		char	name[128], _hoops_GHP[128], _hoops_CSRPGR[128], _hoops_AAPPR[4096], _hoops_SSRPGR[128];

		HC_Begin_Color_Name_Search ();
		HOOPS_WORLD->_hoops_RAPPR =
				_hoops_AHIA (_hoops_GGAPR (name), _hoops_AHIA (_hoops_GGAPR (_hoops_GHP), _hoops_GGAPR (_hoops_CSRPGR)));
		while (HI_Find_Color_Name (info->_hoops_RIGC, name, -1, _hoops_GHP, -1, _hoops_CSRPGR, -1)) {
			(void)HC_Parse_String (name, ",", 0, _hoops_SSRPGR);
			HOOPS_WORLD->_hoops_RAPPR = _hoops_GGAPR (_hoops_AAPPR);
			HI_Show_Color_Name (_hoops_SSRPGR, _hoops_AAPPR, -1);
			POPNAME(info->_hoops_RIGC);
			if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(Color_Name") ||
				!_hoops_CAGPGR (_hoops_GHIPH, name) ||
				!_hoops_CAGPGR (_hoops_GHIPH, _hoops_GHP) ||
				!_hoops_CAGPGR (_hoops_GHIPH, _hoops_CSRPGR) ||
				!_hoops_CAGPGR (_hoops_GHIPH, _hoops_AAPPR) ||
				!_hoops_CRGPGR (_hoops_GHIPH, ")")) {
				HOOPS_WORLD->_hoops_RAPPR = _hoops_RSRPGR;
				return false;
			}
			PUSHNAME(info->_hoops_RIGC);
		}
		HC_End_Color_Name_Search ();
		POPNAME(info->_hoops_RIGC);
	}
#endif

	HOOPS_WORLD->_hoops_RAPPR = _hoops_RSRPGR;

	if (BIT (_hoops_SCRPGR, _hoops_PCHAP)) {
		if (info->_hoops_RIGC->open_list != null)
			if (!_hoops_HCRPGR (_hoops_GHIPH, info->_hoops_RIGC->open_list))
				return false;
	}

	if (BIT (_hoops_SCRPGR, _hoops_HCHAP)) {
		_hoops_PGIIR			*font,
						**_hoops_GPPIR;
		int				count;

		_hoops_GPPIR = _hoops_RSPPR(info->_hoops_RIGC, _hoops_SPPGI);
		if (_hoops_GPPIR == null) {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Font hash table missing");
			return false;
		}

		count = _hoops_GPRGI;
		do {
			if ((font = *_hoops_GPPIR) != null) do if (!font->_hoops_IAHAP) {
				char			_hoops_SSHGGR[64];
				int				_hoops_GGAPGR;
				char const		*data;

				/* _hoops_HSRPR "_hoops_HRCSR" */
				if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(Font \"") ||
					!_hoops_HPGPGR (_hoops_GHIPH, &font->name) ||
					!_hoops_CRGPGR (_hoops_GHIPH, "\" \""))
					return false;

				if (font->encoding != _hoops_SSAIP) {
					HI_Show_Encoding_Type (_hoops_SSHGGR, -1, font->encoding);
					if (!_hoops_APGPGR (_hoops_GHIPH, "encoding=%s", (void *)_hoops_SSHGGR))
						return false;
				}
				if (font->encoding != _hoops_SSAIP &&
					font->_hoops_HGIIR != null &&
					!_hoops_CRGPGR (_hoops_GHIPH, ", "))
					return false;
				if (font->_hoops_HGIIR != null &&
					!_hoops_APGPGR (_hoops_GHIPH, "lookup=%n",
									 (void *)&font->_hoops_HGIIR->name))
					return false;
				if (!_hoops_CRGPGR (_hoops_GHIPH, "\" ("))
					return false;

				data = font->data;
				_hoops_GGAPGR = font->data_length;

				do {
					int				index;

					/* _hoops_CAAA _hoops_GSPR _hoops_IS _hoops_SCSH */
					index = _hoops_SAAIP (*data);
					if (!_hoops_APGPGR (_hoops_GHIPH, "%d", (void *)&index))
						return false;
					++data;
				} while (--_hoops_GGAPGR > 0);

				if (!_hoops_CRGPGR (_hoops_GHIPH, "))"))
					return false;
			} while ((font = font->next) != null);
			++_hoops_GPPIR;
		} while (--count > 0);
	}

	return true;
}


/*
 *	 _hoops_CIAPI _hoops_RH _hoops_RGHR _hoops_GRSSR _hoops_HPP '_hoops_HAHGS'.
 */
local bool _hoops_HCCGS (
	_hoops_IRIPH	*_hoops_GHIPH,
	bool		_hoops_CGIAP) {
	_hoops_HCRPR			_hoops_CCCIH, _hoops_SCCIH;

	_hoops_GHIPH->_hoops_ASAPR = &_hoops_GHIPH->buffer[0][0];
	_hoops_GHIPH->_hoops_PSAPR = &_hoops_GHIPH->buffer[0][_hoops_PRIPH];
	_hoops_GHIPH->_hoops_RAIPH = 0;
	_hoops_GHIPH->_hoops_SAIPH = 0;
	_hoops_GHIPH->_hoops_RPIPH = 0;
	_hoops_GHIPH->_hoops_GPIPH = 79;
	_hoops_GHIPH->_hoops_APIPH = 0;
	_hoops_GHIPH->_hoops_CAIPH = 1;
	_hoops_GHIPH->_hoops_IPIPH = true;
	_hoops_GHIPH->_hoops_CPIPH = false;
	_hoops_GHIPH->_hoops_SAPPR = 0;
	_hoops_CCCIH.length = 0;
	_hoops_SCCIH.length = 0;
	if (!HI_Open_File (&_hoops_GHIPH->filename, FILE_For_Writing,
					   &_hoops_GHIPH->_hoops_CRIPH, _hoops_CGIAP, &_hoops_CCCIH, &_hoops_SCCIH)) {
		if (_hoops_SCCIH.length != 0) _hoops_GHIPH->_hoops_CAIPH = 2;
		HI_Report_File_Error_With_Names (_hoops_GHIPH, &_hoops_CCCIH, &_hoops_SCCIH);
		return false;
	}
	else return true;
}



local bool _hoops_RGAPGR (
	_hoops_RSSAGR *	info,
	_hoops_CRCP const *		root) {
	_hoops_IRIPH *			_hoops_GHIPH = info->_hoops_GRHRI;
	_hoops_CRCP const *		segment;

	_hoops_GHIPH->_hoops_SAIPH = 0;	/* _hoops_SAHR _hoops_IS _hoops_SHH _hoops_RCRR */
	if (_hoops_GHIPH->_hoops_RPIPH > _hoops_GHIPH->_hoops_SAIPH &&
		!_hoops_CRGPGR (_hoops_GHIPH, "\n"))
		return false;

	_hoops_PSSAGR (info, root);
	while (info->unnamed->Pop(&segment)) {
		if (!_hoops_CRGPGR (_hoops_GHIPH, "(Rename_Segment \""))
			return false;
		if (!_hoops_GRRPGR (info, segment, root))
			return false;
		if (!_hoops_CRGPGR (_hoops_GHIPH, "\" \"\")\n"))
			return false;
	}
	_hoops_HSSAGR (info);

	return true;
}

local bool _hoops_AGAPGR (
	_hoops_IRIPH			*_hoops_GHIPH) {
	local		const float				_hoops_PGAPGR = _hoops_PRCCR;
	char					buffer[MAX_ERRMSG];
	char					version[MAX_ERRMSG];

	if (!_hoops_CRGPGR (_hoops_GHIPH,
					  Sprintf_F (null, ";; HMF V%.2f TEXT", _hoops_PGAPGR)))
		return false;

	/* _hoops_CGH _hoops_HPSI _hoops_CCA "_hoops_IPPSA->_hoops_HGAPGR", _hoops_HIH _hoops_GRHP _hoops_CGSI
	 * _hoops_IHGP _hoops_HPP _hoops_HPIAA _hoops_IGAPGR _hoops_HRGR _hoops_AHSC _hoops_RAPR _hoops_IH _hoops_PA _hoops_SR _hoops_CHR
	 * _hoops_PGAIP _hoops_IS _hoops_HGCR _hoops_ARI
	 */

	_hoops_GHIPH->_hoops_CPIPH = true;

	if (!_hoops_CRGPGR (_hoops_GHIPH, "\n(") ||
		!_hoops_CRGPGR (_hoops_GHIPH, HK_PLATFORM) ||
		!_hoops_CRGPGR (_hoops_GHIPH, ") "))
		return false;

	HI_HOOPS_Version (version, -1);
	Sprintf_S (buffer, "HOOPS %s", version);
	if (!_hoops_CRGPGR (_hoops_GHIPH, buffer))
		return false;

	_hoops_GHIPH->_hoops_CPIPH = false;

	return true;
}

local void _hoops_CGAPGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	Metafile *				_hoops_PHCIH) 
{
	_hoops_RSSAGR			info;
	_hoops_IRIPH				_hoops_GRHRI;
	_hoops_IRIPH *				_hoops_GHIPH = &_hoops_GRHRI;
	_hoops_HCRPR					_hoops_CCCIH, _hoops_SCCIH;
	int						_hoops_HCIS;
	char					scratch[_hoops_HCSAGR];
	_hoops_HCRPR *					_hoops_PSHAP;

	info._hoops_RIGC = _hoops_RIGC;
	info._hoops_PHCIH = _hoops_PHCIH;
	info.unnamed = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_CAGGI)(_hoops_RIGC->memory_pool);
	info._hoops_ASSAGR = null;
	info._hoops_GRHRI = &_hoops_GRHRI;
	info._hoops_GGRHH = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_AAPHP)(_hoops_RIGC->memory_pool, _hoops_PAPHP);

	_hoops_GHIPH->_hoops_PPIPH = true;
	_hoops_GHIPH->user_data = _hoops_ACSAGR;

	if (BIT (_hoops_PHCIH->value, _hoops_PHHAP))
		_hoops_PSHAP = &_hoops_PHCIH->_hoops_PSHAP;
	else if (HOOPS_WORLD->_hoops_HAGHP != null)
		_hoops_PSHAP = &HOOPS_WORLD->_hoops_HAGHP->name;
	else
		_hoops_PSHAP = null;

	if (!HI_Get_Filename (_hoops_SRCP, _hoops_PHCIH, _hoops_GHIPH, _hoops_PSHAP))
		return;

	if (!_hoops_HCCGS (_hoops_GHIPH, _hoops_PHCIH->_hoops_CGIAP)) {
		_hoops_RGAIR (_hoops_GHIPH->filename);
		return;
	}

	_hoops_PHCIH->_hoops_CGIAP = false;

	/* _hoops_RH "_hoops_RPP" _hoops_GRS _hoops_RRS _hoops_RPP _hoops_GII _hoops_IIGR _hoops_RH _hoops_SCSHR _hoops_ISHS! */

	_hoops_RGRPGR (_hoops_SRCP, true);

	if (_hoops_AGAPGR (_hoops_GHIPH) &&
		(!BIT (_hoops_PHCIH->value, _hoops_GIHAP) ||
		 _hoops_ISRPGR (_hoops_SRCP, _hoops_GHIPH, _hoops_PHCIH->_hoops_HPCI & _hoops_PHCIH->_hoops_SCHAP,
						_hoops_PHCIH->value, &info, scratch)) &&
		_hoops_GHRPGR (_hoops_SRCP, &info, true, scratch) &&
		(!BIT (_hoops_PHCIH->value, _hoops_GIHAP) ||
		 _hoops_CCRPGR (_hoops_SRCP, _hoops_GHIPH, _hoops_PHCIH->_hoops_HPCI & _hoops_PHCIH->_hoops_SCHAP,
			 _hoops_PHCIH->value, &info, scratch)) &&
		_hoops_RGAPGR (&info, _hoops_SRCP) &&
		_hoops_CRGPGR (_hoops_GHIPH, "\n") && _hoops_ISSAGR (_hoops_GHIPH)) {
		/* _hoops_HCR _hoops_IHRI _hoops_HIS _hoops_SGIP */

		if (!HI_Synch_File_Buffer (_hoops_GHIPH->_hoops_CRIPH, &_hoops_HCIS, &_hoops_CCCIH, &_hoops_SCCIH))
			HI_Report_File_Error_With_Names (_hoops_GHIPH, &_hoops_CCCIH, &_hoops_SCCIH);
	}

	_hoops_RGRPGR (_hoops_SRCP, false);

	while (info._hoops_ASSAGR != null)	/* _hoops_GGAS _hoops_GPP _hoops_HPCS */
		_hoops_HSSAGR (&info);

	if (!HI_Close_File (_hoops_GHIPH->_hoops_CRIPH, &_hoops_CCCIH, &_hoops_SCCIH))
		HI_Report_File_Error_With_Names (_hoops_GHIPH, &_hoops_CCCIH, &_hoops_SCCIH);

	_hoops_RGAIR (_hoops_GHIPH->filename);

	delete info._hoops_GGRHH;
	delete info.unnamed;
}
#endif

HC_INTERFACE void HC_CDECL HC_Write_Metafile (
	char const *		segname,
	char const *		file,
	char const *		options)
{
	_hoops_PAPPR context("Write_Metafile");

#ifdef DISABLE_METAFILE
	_hoops_IRPPR ("Metafile");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Write_Metafile (%S, %S, ", segname, file));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", options));
	);

	_hoops_CRCP *			_hoops_SRCP;
	Metafile			_hoops_APHCR;
	char				_hoops_SGAPGR[MAX_ERRMSG];

	_hoops_CSPPR();

	if ((_hoops_SRCP = HI_One_Segment_Search (context, segname, true)) == null) {
		_hoops_IRRPR();
		return;
	}

	/* _hoops_HGCR _hoops_IRS _hoops_SPCS _hoops_SCRII _hoops_IGRI */
	ZERO_STRUCT (&_hoops_APHCR, Metafile);

	_hoops_APHCR.mask = _hoops_RHHAP;
	_hoops_APHCR.value = _hoops_RHHAP;
	_hoops_APHCR._hoops_ASHAP = ~0U;

	_hoops_APHCR._hoops_RGIAP = _hoops_CSHAP;
	_hoops_APHCR._hoops_CGIAP = true;

	/* _hoops_CGIC _hoops_GII _hoops_AAP */
	HI_Decipher_Metafile_Options (context, options, &_hoops_APHCR);

	while (*file == ' ') ++file;
	if (*file != '\0') {
		_hoops_RRIGI (_hoops_SGAPGR, "name=%qs", file);
		HI_Decipher_Metafile_Options (context, _hoops_SGAPGR, &_hoops_APHCR);
	}

	PUSHNAME(context);
	_hoops_AASAH (context, "Metafile writing (internal)");
	_hoops_CGAPGR (context, _hoops_SRCP, &_hoops_APHCR);
	POPNAME(context);

	_hoops_IRRPR();

	_hoops_RGAIR (_hoops_APHCR.name);
	_hoops_RGAIR (_hoops_APHCR._hoops_PSHAP);
	_hoops_RGAIR (_hoops_APHCR.comment);
	_hoops_RGAIR (_hoops_APHCR._hoops_HSHAP);
#endif
}



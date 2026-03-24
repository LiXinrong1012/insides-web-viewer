/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.124 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "metafile.h"
#include "filedata.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "phedron.h"
#include "path.h"
#include "adt.h"
#include "hpserror.h"

#ifndef DISABLE_METAFILE

local const _hoops_IGRCR _hoops_PRHGS[] = {
	{_hoops_RCHAP,		_hoops_GRRCR ("alias"), _hoops_RRRCR, 0, true},
	{_hoops_ACHAP,	_hoops_GRRCR ("color name"), _hoops_RRRCR, 0, true},
	{_hoops_PCHAP,		_hoops_GRRCR ("open item"), _hoops_RRRCR, 0, true},
	{_hoops_HCHAP,			_hoops_GRRCR ("font"), _hoops_RRRCR, 0, true},
	{_hoops_ICHAP,		_hoops_GRRCR ("texture"), _hoops_RRRCR, 0, true},

	{_hoops_RCHAP,		_hoops_GRRCR ("aliases"), _hoops_RRRCR, 0, true},
	{_hoops_ACHAP,	_hoops_GRRCR ("color names"), _hoops_RRRCR, 0, true},
	{_hoops_PCHAP,		_hoops_GRRCR ("open items"), _hoops_RRRCR, 0, true},
	{_hoops_HCHAP,			_hoops_GRRCR ("fonts"), _hoops_RRRCR, 0, true},
	{_hoops_ICHAP,		_hoops_GRRCR ("textures"), _hoops_RRRCR, 0, true},
};

local const _hoops_HPAGA _hoops_HRHGS = {
	_hoops_GGAPR (_hoops_PRHGS),
	_hoops_PRHGS,
};

local const _hoops_IGRCR _hoops_IRHGS[] = {
	{_hoops_SSHAP,		_hoops_GRRCR ("off"), _hoops_RRRCR, 0, false},
	{_hoops_SSHAP,		_hoops_GRRCR ("no"), _hoops_RRRCR, 0, false},
	{_hoops_SSHAP,		_hoops_GRRCR ("false"), _hoops_RRRCR, 0, false},
	{_hoops_GGIAP,		_hoops_GRRCR ("on"), _hoops_RRRCR, 0, false},
	{_hoops_GGIAP,		_hoops_GRRCR ("yes"), _hoops_RRRCR, 0, false},
	{_hoops_GGIAP,		_hoops_GRRCR ("true"), _hoops_RRRCR, 0, false},
	{_hoops_CSHAP,			_hoops_GRRCR ("automatic"), _hoops_RRRCR, 0, false},
	{_hoops_CSHAP,			_hoops_GRRCR ("default"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_CRHGS = {
	_hoops_GGAPR (_hoops_IRHGS),
	_hoops_IRHGS,
};


local const _hoops_IGRCR _hoops_SRHGS[] = {
	{_hoops_AGIAP,				_hoops_GRRCR ("default"), _hoops_RRRCR, 0, false},
	{_hoops_AGIAP,				_hoops_GRRCR ("auto"), _hoops_RRRCR, 0, false},
	{_hoops_HGIAP,				_hoops_GRRCR ("all"), _hoops_RRRCR, 0, false},
	{_hoops_HGIAP,				_hoops_GRRCR ("on"), _hoops_RRRCR, 0, false},
	{_hoops_HGIAP,				_hoops_GRRCR ("force"), _hoops_RRRCR, 0, false},
	{_hoops_PGIAP,			_hoops_GRRCR ("none"), _hoops_RRRCR, 0, false},
	{_hoops_PGIAP,			_hoops_GRRCR ("off"), _hoops_RRRCR, 0, false},
	{_hoops_PGIAP,			_hoops_GRRCR ("suppress"), _hoops_RRRCR, 0, false},
};

local const _hoops_HPAGA _hoops_GAHGS = {
	_hoops_GGAPR (_hoops_SRHGS),
	_hoops_SRHGS,
};


local const _hoops_IGRCR _hoops_RAHGS[] = {
	{_hoops_GHHAP,					_hoops_GRRCR ("read"), _hoops_RRRCR, 0, true},
	{_hoops_RHHAP,				_hoops_GRRCR ("write"), _hoops_RRRCR, 0, true},
	{_hoops_AHHAP,					_hoops_GRRCR ("name"), _hoops_PRRCR, 1, true},
	{_hoops_PHHAP,			_hoops_GRRCR ("directory"), _hoops_PRRCR, 1, true},
	{_hoops_HHHAP,				_hoops_GRRCR ("comment"), _hoops_PRRCR, 1, true},
	{_hoops_IHHAP ,		_hoops_GRRCR ("original name"), _hoops_PRRCR, 1, true},
	{_hoops_CHHAP,_hoops_GRRCR ("follow cross-reference"), _hoops_RRRCR, 0, true},
	{_hoops_SHHAP,			_hoops_GRRCR ("overwrite"), _hoops_RRRCR, 0, true},
	{_hoops_RIHAP,		_hoops_GRRCR ("use color name"), _hoops_RRRCR, 0, true},

	{_hoops_GIHAP,			_hoops_GRRCR ("save state"), _hoops_GHAGA,
	-999, true, &_hoops_HRHGS},
	{_hoops_AIHAP,		_hoops_GRRCR ("restore state"), _hoops_GHAGA,
	-999, true, &_hoops_HRHGS},

	{_hoops_PIHAP,		_hoops_GRRCR ("filename extension"), _hoops_GHAGA,
	-1, true, &_hoops_CRHGS},

	{_hoops_HHHAP,				_hoops_GRRCR ("comments"), _hoops_PRRCR, 1, true},
	{_hoops_CHHAP,_hoops_GRRCR ("follow cross-references"), _hoops_RRRCR, 0, true},
	{_hoops_RIHAP,		_hoops_GRRCR ("use color names"), _hoops_RRRCR, 0, true},
	{_hoops_IIHAP,			_hoops_GRRCR ("suppress lod"), _hoops_RRRCR, 0, true},
	{_hoops_HIHAP,		_hoops_GRRCR ("tristrips"), _hoops_GHAGA, 
	-1, true, &_hoops_GAHGS},
	{_hoops_CIHAP,		_hoops_GRRCR ("suppress camera"), _hoops_RRRCR, 0, true},
	{_hoops_SIHAP,		_hoops_GRRCR ("relative path"), _hoops_APRCA, 1, true},
	{_hoops_SIHAP,		_hoops_GRRCR ("relative paths"), _hoops_APRCA, 1, true},
	{_hoops_SIHAP,		_hoops_GRRCR ("relative path limit"), _hoops_APRCA, 1, true},
	{_hoops_GCHAP ,		_hoops_GRRCR ("prepend root"), _hoops_PRRCR, 1, true},
};


GLOBAL_FUNCTION void HI_Decipher_Metafile_Options (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			list,
	Metafile *				_hoops_APHCR) 
{

	if (_hoops_CIACR (_hoops_IPRGI)->table == null)
		_hoops_HIACR (_hoops_IPRGI, _hoops_RAHGS);

	Option_Value *option_list;
	Option_Value *option;

	if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_IPRGI), &option_list, _hoops_SIACR)) 
		return;

	if ((option = option_list) != null) do {
		int	mask = (int)option->type->id;

		_hoops_APHCR->mask |= mask;
		if (option->_hoops_GCACR) {
			_hoops_APHCR->value &= ~mask;

			if (mask == _hoops_PIHAP)
				_hoops_APHCR->_hoops_RGIAP = _hoops_SSHAP;
			if (mask == _hoops_HIHAP)
				_hoops_APHCR->_hoops_IGIAP = _hoops_PGIAP;
			if (mask == _hoops_SIHAP)
				_hoops_APHCR->_hoops_ASHAP = ~0U;
			if (mask == _hoops_GCHAP)
				_hoops_RGAIR (_hoops_APHCR->_hoops_ISHAP);
		}
		else {
			_hoops_APHCR->value |= mask;
			switch (mask) {
				case _hoops_AHHAP: {
					_hoops_RGAIR (_hoops_APHCR->name);		/* _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_PGHC _hoops_AASA */
					HI_Copy_Name (option->value._name, &_hoops_APHCR->name);
				}	break;

				case _hoops_PHHAP: {
					_hoops_RGAIR (_hoops_APHCR->_hoops_PSHAP);
					HI_Copy_Name (option->value._name, &_hoops_APHCR->_hoops_PSHAP);
				}	break;

				case _hoops_HHHAP: {
					_hoops_RGAIR (_hoops_APHCR->comment);
					HI_Copy_Name (option->value._name, &_hoops_APHCR->comment);
				}	break;

				case _hoops_IHHAP: {
					_hoops_RGAIR (_hoops_APHCR->_hoops_HSHAP);
					HI_Copy_Name (option->value._name, &_hoops_APHCR->_hoops_HSHAP);
				}	break;

				case _hoops_GCHAP: {
					_hoops_RGAIR (_hoops_APHCR->_hoops_ISHAP);	
					if (option->value._name->text[option->value._name->length-1] == '/') {
						_hoops_APHCR->_hoops_ISHAP.length=option->value._name->length-1;
						ALLOC_ARRAY(_hoops_APHCR->_hoops_ISHAP.text, _hoops_APHCR->_hoops_ISHAP.length, char);
						_hoops_AIGA(option->value._name->text, _hoops_APHCR->_hoops_ISHAP.length, char, _hoops_APHCR->_hoops_ISHAP.text);
						_hoops_APHCR->_hoops_ISHAP.text[_hoops_APHCR->_hoops_ISHAP.length]='\0';
					}
					else
						HI_Copy_Name (option->value._name, &_hoops_APHCR->_hoops_ISHAP);

				}	break;

				case _hoops_GIHAP: {
					Option_Value			*_hoops_AHSAA;

					if ((_hoops_AHSAA = option->value.option_list) == null) {
						_hoops_APHCR->_hoops_HPCI = _hoops_CCHAP;
						_hoops_APHCR->_hoops_SCHAP = _hoops_CCHAP;
						_hoops_APHCR->value |= mask;
					}
					else do {
						int				_hoops_PHSAA;

						_hoops_PHSAA = (int)_hoops_AHSAA->type->id;
						_hoops_APHCR->_hoops_HPCI |= _hoops_PHSAA;

						if (_hoops_AHSAA->_hoops_GCACR)
							_hoops_APHCR->_hoops_SCHAP &= ~_hoops_PHSAA;
						else
							_hoops_APHCR->_hoops_SCHAP |= _hoops_PHSAA;
					} _hoops_RGGA ((_hoops_AHSAA = _hoops_AHSAA->next) == null);
				}	break;

				case _hoops_AIHAP: {
					Option_Value			*_hoops_AHSAA;

					if ((_hoops_AHSAA = option->value.option_list) == null) {
						_hoops_APHCR->_hoops_GSHAP = _hoops_CCHAP;
						_hoops_APHCR->_hoops_RSHAP = _hoops_CCHAP;
						_hoops_APHCR->value |= mask;
					}
					else do {
						int				_hoops_PHSAA;

						_hoops_PHSAA = (int)_hoops_AHSAA->type->id;
						_hoops_APHCR->_hoops_GSHAP |= _hoops_PHSAA;

						if (_hoops_AHSAA->_hoops_GCACR)
							_hoops_APHCR->_hoops_RSHAP &= ~_hoops_PHSAA;
						else
							_hoops_APHCR->_hoops_RSHAP |= _hoops_PHSAA;
					} _hoops_RGGA ((_hoops_AHSAA = _hoops_AHSAA->next) == null);
				}	break;

				case _hoops_PIHAP: {
					Option_Value			*_hoops_AHSAA;

					if ((_hoops_AHSAA = option->value.option_list) == null)
						_hoops_APHCR->_hoops_RGIAP = _hoops_GGIAP;
					else
						_hoops_APHCR->_hoops_RGIAP = (int)_hoops_AHSAA->type->id;
				}	break;

				case _hoops_HIHAP: {
					Option_Value			*_hoops_AHSAA;

					if ((_hoops_AHSAA = option->value.option_list) == null)
						_hoops_APHCR->_hoops_IGIAP = _hoops_HGIAP;
					else
						_hoops_APHCR->_hoops_IGIAP = (int)_hoops_AHSAA->type->id;
				}	break;

				case _hoops_SIHAP: {
					_hoops_APHCR->_hoops_ASHAP = option->value._hoops_RIARA[0];
				}	break;
			}
		}
	}
	_hoops_RGGA ((option = option->next) == null);

	HI_Free_Option_List (_hoops_RIGC, option_list);

}



/*
 *	_hoops_AAHGS, _hoops_RH _hoops_SICAR _hoops_GGR _hoops_RGR _hoops_RPHRA _hoops_ACRR _hoops_SGS _hoops_PAHGS ()
 *	_hoops_SSCP _hoops_RPII _hoops_PIGS _hoops_SRS.
 */

/*
 *	_hoops_CGP _hoops_PHPRA _hoops_HRGR _hoops_HPGR _hoops_RSGR _hoops_IIGR _hoops_SRHR _hoops_HAHGS, _hoops_HGCR _hoops_HPIH _hoops_SRHR.  _hoops_HPSHR _hoops_RIHH,
 *	_hoops_RH _hoops_RIHH _hoops_GPSRR _hoops_HRGR _hoops_GGR _hoops_HAHGS->_hoops_GPSRR _hoops_PPR _hoops_ASRC _hoops_RCPP,
 *	_hoops_SHS _hoops_ASRC _hoops_IHPR;
 */
#define _hoops_IAHGS(_hoops_GHIPH, _hoops_ASAPR) ((_hoops_ASAPR) != _hoops_GHIPH->_hoops_PSAPR || \
	(_hoops_GHIPH->_hoops_ASAPR = (_hoops_ASAPR), (_hoops_CAHGS (_hoops_GHIPH) ? ((_hoops_ASAPR) = _hoops_GHIPH->_hoops_ASAPR, true) : false)))

/*
 *	_hoops_CGP _hoops_HA _hoops_HPGR _hoops_RSGR _hoops_IIGR _hoops_SRHR _hoops_HAHGS, _hoops_HGCR _hoops_HPIH _hoops_SRHR.	_hoops_HPSHR _hoops_RIHH,
 *	_hoops_RH _hoops_RIHH _hoops_GPSRR _hoops_HRGR _hoops_GGR _hoops_HAHGS->_hoops_GPSRR _hoops_PPR _hoops_ASRC _hoops_RCPP,
 *	_hoops_SHS _hoops_ASRC _hoops_IHPR;
 */
#define _hoops_SAHGS(_hoops_GHIPH) (_hoops_GHIPH->_hoops_ASAPR != _hoops_GHIPH->_hoops_PSAPR || _hoops_CAHGS (_hoops_GHIPH))


local const		char	overflow[] = "Overflow in output buffer";


local void swap_buffers (
	_hoops_IRIPH *	_hoops_GHIPH) 
{
#ifndef DISABLE_METAFILE
	char			*_hoops_GPHGS;
	bool		_hoops_RPHGS;

	_hoops_GPHGS = _hoops_GHIPH->_hoops_AAIPH;
	_hoops_GHIPH->_hoops_AAIPH = _hoops_GHIPH->_hoops_ASAPR;
	_hoops_GHIPH->_hoops_ASAPR = _hoops_GPHGS;

	_hoops_GPHGS = _hoops_GHIPH->_hoops_PAIPH;
	_hoops_GHIPH->_hoops_PAIPH = _hoops_GHIPH->_hoops_PSAPR;
	_hoops_GHIPH->_hoops_PSAPR = _hoops_GPHGS;

	_hoops_RPHGS = _hoops_GHIPH->_hoops_IAIPH;
	_hoops_GHIPH->_hoops_IAIPH = _hoops_GHIPH->_hoops_HAIPH;
	_hoops_GHIPH->_hoops_HAIPH = _hoops_RPHGS;

	_hoops_GHIPH->_hoops_RAIPH = 1 - _hoops_GHIPH->_hoops_RAIPH;
#endif
}


/*
 *	_hoops_PHIR _hoops_IRS _hoops_CCAH _hoops_RGHR _hoops_SRHR.	_hoops_ICIA _hoops_GPS _hoops_CCGR _hoops_RH _hoops_SRHR _hoops_HRGR _hoops_IHIR.
 *	_hoops_HCGAR _hoops_RCPP _hoops_GPP _hoops_RSGR _hoops_IIGR _hoops_RGHR _hoops_PAR _hoops_IRS _hoops_RGHR _hoops_RIHH.
 */
local bool _hoops_APHGS (
	_hoops_IRIPH	*_hoops_GHIPH) {
#ifndef DISABLE_METAFILE
	int				_hoops_GSHHH;
	_hoops_HCRPR			_hoops_CCCIH, _hoops_SCCIH;
	char			*_hoops_ASAPR;

	_hoops_HGGIH(_hoops_CCCIH);
	_hoops_HGGIH(_hoops_SCCIH);

	if (_hoops_GHIPH->_hoops_HAIPH) return false;
	_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR = &_hoops_GHIPH->buffer[_hoops_GHIPH->_hoops_RAIPH][0];

	if (!HI_Read_File_Buffer (_hoops_GHIPH->_hoops_CRIPH, _hoops_ASAPR, &_hoops_GSHHH, _hoops_PRIPH,
		&_hoops_CCCIH, &_hoops_SCCIH)) {
		_hoops_GHIPH->_hoops_HHGHP = true;
		HI_Report_File_Error_With_Names (_hoops_GHIPH, &_hoops_CCCIH, &_hoops_SCCIH);
		return false;
	}
	if (_hoops_GSHHH != -1) { /* _hoops_CGP _hoops_RH _hoops_SRHR _hoops_HRGR _hoops_APIP */
		_hoops_GHIPH->_hoops_PSAPR = _hoops_ASAPR + _hoops_GSHHH;
		if (_hoops_GSHHH == 0) {
			_hoops_GHIPH->_hoops_HAIPH = true;
			return false;
		}
	}
	return true;
#else
	return false;
#endif
}


local bool _hoops_CAHGS (
	_hoops_IRIPH	*_hoops_GHIPH) {
#ifndef DISABLE_METAFILE
	int				_hoops_GSHHH;
	_hoops_HCRPR			_hoops_CCCIH, _hoops_SCCIH;

	if (_hoops_GHIPH->_hoops_HAIPH) return false;

	swap_buffers (_hoops_GHIPH);
	if (!HI_Synch_File_Buffer (_hoops_GHIPH->_hoops_CRIPH, &_hoops_GSHHH, &_hoops_CCCIH, &_hoops_SCCIH)) {
		_hoops_GHIPH->_hoops_HHGHP = true;
		HI_Report_File_Error_With_Names (_hoops_GHIPH, &_hoops_CCCIH, &_hoops_SCCIH);
		return false;
	}

	if (_hoops_GSHHH != -1) {
		_hoops_GHIPH->_hoops_PSAPR = _hoops_GHIPH->_hoops_ASAPR + _hoops_GSHHH;
		if (_hoops_GSHHH == 0) {
			_hoops_GHIPH->_hoops_HAIPH = true;
			return false;
		}
	}
	swap_buffers (_hoops_GHIPH);

	if (!_hoops_APHGS (_hoops_GHIPH) && !_hoops_GHIPH->_hoops_HAIPH) return false;
	swap_buffers (_hoops_GHIPH);
	return !_hoops_GHIPH->_hoops_HAIPH;
#else
	return false;
#endif
}


#ifndef DISABLE_METAFILE
/*
 *	_hoops_RAIGR _hoops_PPHGS _hoops_PAR _hoops_HPHGS _hoops_CSAP _hoops_SAHR _hoops_IRIGR. _hoops_SGR _hoops_PPHGS-_hoops_HPHGS _hoops_PAR _hoops_HPHGS-_hoops_PPHGS _hoops_GAR _hoops_SPR _hoops_CCAH _hoops_III.
 *	_hoops_HCGAR _hoops_RCPP _hoops_GPP _hoops_RGHR _hoops_RIHH _hoops_PAR _hoops_IPHGS
 */
local bool _hoops_CPHGS (
	_hoops_IRIPH	*_hoops_GHIPH) {
	char			_hoops_SPHGS;
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;

	if (_hoops_ASAPR < _hoops_GHIPH->_hoops_PSAPR && *_hoops_ASAPR == '\r')
		_hoops_SPHGS = '\n';
	else if (_hoops_ASAPR < _hoops_GHIPH->_hoops_PSAPR && *_hoops_ASAPR == '\n')
		_hoops_SPHGS = '\r';
	else {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "No new line ?");
		_hoops_SPHGS = '\r';
	}

	++_hoops_ASAPR;
	++_hoops_GHIPH->_hoops_APIPH;
	if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) 
		return false;
	if (*_hoops_ASAPR == _hoops_SPHGS) 
		++_hoops_ASAPR;
	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
	return true;
}


/*
 *	_hoops_APSH _hoops_IAISR _hoops_IS _hoops_CACH _hoops_RPP _hoops_RH _hoops_SPS _hoops_GAS _hoops_HRGR '_hoops_GSGGR', _hoops_SIHH _hoops_ARS _hoops_SCH.	
 *	_hoops_GCAAA _hoops_RCPP _hoops_RPP _hoops_PSP _hoops_PSSP _hoops_PAR _hoops_RPP _hoops_IIH _hoops_CSAP _hoops_IRS _hoops_RGHR _hoops_RIHH
 */

local bool _hoops_GHHGS (
	_hoops_IRIPH	*_hoops_GHIPH,
	char			c) 
{
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;

	if (_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR) &&
		*_hoops_ASAPR == c)
		return true;

	return false;
}


/*
 *	_hoops_GCAAA _hoops_IHPR _hoops_RPP _hoops_RH _hoops_SPS _hoops_GAS _hoops_IRIGR _hoops_HRGR '_hoops_GSGGR'.	_hoops_GCAAA _hoops_RCPP
 *	_hoops_IAII _hoops_PAR _hoops_RPP _hoops_IIH _hoops_CSAP _hoops_IRS _hoops_RGHR _hoops_RIHH
 */
local bool _hoops_RHHGS (
	_hoops_IRIPH *				_hoops_GHIPH,
	char					c) 
{
	char *	_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;

	if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) {
		if (_hoops_SPIPH (_hoops_GHIPH)) {
			char	_hoops_APHHA[MAX_ERRMSG];
			char	_hoops_AHHGS[2];

			_hoops_AHHGS[0] = c;
			_hoops_AHHGS[1] = '\0';

			_hoops_GHIPH->message = Sprintf_S (_hoops_APHHA, "Unexpected end of file while looking for '%s'",_hoops_AHHGS);
			HI_Report_File_Error (_hoops_GHIPH);
		}
		return false;
	}
	if (*_hoops_ASAPR != c) {
		char			_hoops_PHHGS[MAX_ERRMSG],
								*_hoops_HHHGS = _hoops_PHHGS,
								*_hoops_IHHGS = _hoops_PHHGS+_hoops_GGAPR(_hoops_PHHGS)-1;
		int				_hoops_HACAH = *_hoops_ASAPR;

		*_hoops_HHHGS++ = '\'';
		*_hoops_HHHGS++ = *_hoops_ASAPR;
		_hoops_HHHGS = HI_Sprintf1 (_hoops_HHHGS, _hoops_IHHGS, "' (%d decimal) was found when '", &_hoops_HACAH);

		if (_hoops_HHHGS != null) {
			*_hoops_HHHGS++ = c;
			_hoops_HHHGS = HI_Sprintf1 (_hoops_HHHGS, _hoops_IHHGS, "' was expected", null);
		}
		if (_hoops_HHHGS != null && _hoops_HHHGS != _hoops_IHHGS) *_hoops_HHHGS = '\0';
		_hoops_GHIPH->message = _hoops_PHHGS;
		HI_Report_File_Error (_hoops_GHIPH);
		return false;
	}
	_hoops_GHIPH->_hoops_ASAPR = ++_hoops_ASAPR;
	return true;
}


/*
 *	_hoops_RRIHH _hoops_HPS _hoops_CCGR '_hoops_GSGGR' _hoops_HRGR _hoops_GSGI.  _hoops_GCAAA _hoops_IHPR _hoops_RPP _hoops_IIH _hoops_CSAP _hoops_PSP
 *	_hoops_RGHR _hoops_RIHH _hoops_PAR _hoops_HPGR _hoops_RSGR _hoops_IIGR _hoops_RGHR
 */
local bool _hoops_CHHGS (
	_hoops_IRIPH	*_hoops_GHIPH,
	char			c) {
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;

	do {
		if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) return false;
		if (*_hoops_ASAPR ==	'\r' || *_hoops_ASAPR == '\n') {
			_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
			if (!_hoops_CPHGS (_hoops_GHIPH)) return false;
			_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
		}
	}
	_hoops_RGGA (*_hoops_ASAPR++ == c);
	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
	return true;
}
#endif

local bool _hoops_SHHGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	Key *					l) 
{
#ifndef DISABLE_METAFILE
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
	char			_hoops_GIHGS[40];
	char			*_hoops_AHSCA = _hoops_GIHGS;
	char			*_hoops_CHHHC = _hoops_GIHGS+_hoops_GGAPR(_hoops_GIHGS)-1;

	_hoops_PCCAR {
		if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) {
			if (_hoops_SPIPH (_hoops_GHIPH)) {
				_hoops_GHIPH->message = "Unexpected end of file while reading an integer";
				HI_Report_File_Error (_hoops_GHIPH);
			}
			return false;
		}

		if (*_hoops_ASAPR == ' ' || *_hoops_ASAPR == ')' || *_hoops_ASAPR == ']' ||
			*_hoops_ASAPR == '\r' || *_hoops_ASAPR == '\n' || *_hoops_ASAPR == '\t') break;

		if (_hoops_CHHHC != _hoops_AHSCA + 1) *_hoops_AHSCA++ = *_hoops_ASAPR++;
		else {
			_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
			_hoops_GHIPH->message = overflow;
			HI_Report_File_Error (_hoops_GHIPH);
			return false;
		}
	}
	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
	*_hoops_AHSCA = '\0';
	_hoops_CHHHC = _hoops_AHSCA;
	_hoops_AHSCA = _hoops_GIHGS;
	if (HI_Scan_Key (_hoops_RIGC, (char const **)&_hoops_AHSCA, _hoops_CHHHC, l) == null &&
		_hoops_AHSCA == _hoops_CHHHC) return true;
	_hoops_GHIPH->message = Sprintf_S (null,"Syntax error: '%s' is not a legal integer", _hoops_GIHGS);
	HI_Report_File_Error (_hoops_GHIPH);
#endif
	return false;
}



local bool _hoops_RIHGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	long *					l) 
{
#ifndef DISABLE_METAFILE
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
	char			_hoops_GIHGS[40];
	char			*_hoops_AHSCA = _hoops_GIHGS;
	char			*_hoops_CHHHC = _hoops_GIHGS+_hoops_GGAPR(_hoops_GIHGS)-1;

	_hoops_PCCAR {
		if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) {
			if (_hoops_SPIPH (_hoops_GHIPH)) {
				_hoops_GHIPH->message = "Unexpected end of file while reading an integer";
				HI_Report_File_Error (_hoops_GHIPH);
			}
			return false;
		}

		if (*_hoops_ASAPR == ' ' || *_hoops_ASAPR == ')' || *_hoops_ASAPR == ']' ||
			*_hoops_ASAPR == '\r' || *_hoops_ASAPR == '\n' || *_hoops_ASAPR == '\t') break;

		if (_hoops_CHHHC != _hoops_AHSCA + 1) *_hoops_AHSCA++ = *_hoops_ASAPR++;
		else {
			_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
			_hoops_GHIPH->message = overflow;
			HI_Report_File_Error (_hoops_GHIPH);
			return false;
		}
	}
	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
	*_hoops_AHSCA = '\0';
	_hoops_CHHHC = _hoops_AHSCA;
	_hoops_AHSCA = _hoops_GIHGS;
	if (HI_Scan_Long (_hoops_RIGC, (char const **)&_hoops_AHSCA, _hoops_CHHHC, l) == null &&
		_hoops_AHSCA == _hoops_CHHHC) return true;
	_hoops_GHIPH->message = Sprintf_S (null,"Syntax error: '%s' is not a legal integer", _hoops_GIHGS);
	HI_Report_File_Error (_hoops_GHIPH);
#endif
	return false;
}


local bool _hoops_AIHGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	int *					i) 
{
#ifndef DISABLE_METAFILE

	if (sizeof(long) == sizeof(int)) 
		return _hoops_RIHGS (_hoops_RIGC, _hoops_GHIPH, (long *)i);
	else {
		long			_hoops_PIHGS;

		if (!_hoops_RIHGS (_hoops_RIGC, _hoops_GHIPH, &_hoops_PIHGS)) return false;

		*i = (int)_hoops_PIHGS;

		if ((long)*i != _hoops_PIHGS) {
			_hoops_GHIPH->message = "Integer too large";
			HI_Report_File_Error (_hoops_GHIPH);
			return false;
		}
		return true;
	}
#else
	return false;
#endif
}


local bool _hoops_HIHGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	float *					f) 
{
#ifndef DISABLE_METAFILE
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
	char			_hoops_GIHGS[40];
	char			*_hoops_AHSCA = _hoops_GIHGS;
	char			*_hoops_CHHHC = _hoops_GIHGS+_hoops_GGAPR(_hoops_GIHGS)-1;

	_hoops_PCCAR {
		if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) {
			if (_hoops_SPIPH (_hoops_GHIPH)) {
				_hoops_GHIPH->message = "Unexpected end of file while reading a float";
				HI_Report_File_Error (_hoops_GHIPH);
			}
			return false;
		}

		if (*_hoops_ASAPR == ')' || *_hoops_ASAPR == ' ' ||
			*_hoops_ASAPR == '\r' || *_hoops_ASAPR == '\n' || *_hoops_ASAPR == '\t') break;

		if (_hoops_AHSCA != _hoops_CHHHC) *_hoops_AHSCA++ = *_hoops_ASAPR++;
		else {
			_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
			_hoops_GHIPH->message = overflow;
			HI_Report_File_Error (_hoops_GHIPH);
			return false;
		}
	}
	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
	if (_hoops_AHSCA == _hoops_CHHHC) {
		_hoops_GHIPH->message = overflow;
		HI_Report_File_Error (_hoops_GHIPH);
		return false;
	}
	else {
		float tmp;
		char const *_hoops_IIHGS;

		*_hoops_AHSCA = '\0';
		_hoops_CHHHC = _hoops_AHSCA;
		_hoops_AHSCA = _hoops_GIHGS;
		_hoops_IIHGS = HI_Scan_Float (_hoops_RIGC, (char const **)&_hoops_AHSCA, _hoops_CHHHC, &tmp);
		if (_hoops_IIHGS == null) {
			*f = (float)tmp;
			return true;
		}
		if (!BIT(_hoops_GHIPH->_hoops_SAPPR, _hoops_HRIPH)) {
			_hoops_GHIPH->message = Sprintf_SS (null, "Syntax error: '%s' - '%s'", _hoops_GIHGS, _hoops_IIHGS);
			HI_Report_File_Error (_hoops_GHIPH);
			_hoops_GHIPH->_hoops_SAPPR |= _hoops_HRIPH;
		}
		if (_hoops_IIHGS[26] == 'b' /* "_hoops_CIHGS-_hoops_PPSR _hoops_PHI _hoops_HAH _hoops_AHSC (_hoops_PGSAH)" */ ||
			_hoops_IIHGS[26] == 's' /* "_hoops_CIHGS-_hoops_PPSR _hoops_PHI _hoops_HAH _hoops_RISA (_hoops_SIHGS)" */) {
			*f = 0;
			return true;
		}
		else
			return false;
	}
#else
	return false;
#endif
}



/*
 *	_hoops_CPPP _hoops_ISGR _hoops_HCR _hoops_GC, _hoops_ICSRA, _hoops_PPHGS _hoops_PAR _hoops_HPHGS _hoops_HPS, _hoops_RPCPR _hoops_APGR.
 *	_hoops_HCGAR _hoops_RCPP _hoops_GPP _hoops_IRS _hoops_RGHR _hoops_RIHH _hoops_HIH _hoops_IHPR _hoops_GPP _hoops_RSGR _hoops_IIGR _hoops_RGHR _hoops_PAR _hoops_CGPR
 *	_hoops_IRS _hoops_GRAA _hoops_PGS _hoops_GC _hoops_HPS _hoops_HRGR _hoops_IRIGR
 */
local bool _hoops_GCHGS (
	_hoops_IRIPH	*_hoops_GHIPH) {
#ifndef DISABLE_METAFILE
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
	bool		_hoops_RCHGS = false;

	_hoops_PCCAR {
		if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) return _hoops_SPIPH (_hoops_GHIPH);
		if (*_hoops_ASAPR == ' ' || *_hoops_ASAPR == '\t') ++_hoops_ASAPR;
		else if (*_hoops_ASAPR == ';') {
			++_hoops_ASAPR;
			_hoops_RCHGS = true;
		}
		else if (*_hoops_ASAPR ==	'\r' || *_hoops_ASAPR == '\n') {
			_hoops_RCHGS = false;
			_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
			if (!_hoops_CPHGS (_hoops_GHIPH)) return _hoops_SPIPH (_hoops_GHIPH);
			_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
		}
		else {
			if (_hoops_RCHGS) ++_hoops_ASAPR;
			else break;
		}
	}
	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
	return true;
#else
	return false;
#endif
}

local bool _hoops_ACHGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	Point *					c) 
{
#ifndef DISABLE_METAFILE

	return
		_hoops_RHHGS (_hoops_GHIPH, '(') &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &c->x) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &c->y) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &c->z) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_RHHGS (_hoops_GHIPH, ')');
#else
	return false;
#endif
}

local bool _hoops_GGGII (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	_hoops_ARPA *					c) 
{
#ifndef DISABLE_METAFILE

	return
		_hoops_RHHGS (_hoops_GHIPH, '(') &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &c->a) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &c->b) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &c->c) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &c->d) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_RHHGS (_hoops_GHIPH, ')');
#else
	return false;
#endif
}


#ifndef DISABLE_METAFILE


/* _hoops_RHHSR _hoops_RSSA/_hoops_AGRIR/_hoops_ICCGI/_hoops_PHRP _hoops_CRPR _hoops_RRGR _hoops_GGR _hoops_RGAS */
local int _hoops_PCHGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS) {
	Point				*points;
	int						_hoops_CAHI,
										_hoops_ICHGS;
	int						delta;
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;

	if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) return false;

	if (!_hoops_RHHGS (_hoops_GHIPH, '('))
		return false;
	if (!_hoops_GCHGS (_hoops_GHIPH)) 
		return false;

	_hoops_CAHI = _hoops_HCHGS->_hoops_SAIII;
	_hoops_ICHGS = _hoops_HCHGS->_hoops_GPIII;
	points = _hoops_HCHGS->_hoops_RPIII + _hoops_ICHGS;

	_hoops_RGGA (*_hoops_GHIPH->_hoops_ASAPR == ')') {
		if (++_hoops_ICHGS > _hoops_CAHI) {
			int				_hoops_CCHGS = _hoops_CAHI;
			Point		*_hoops_RRSAA = _hoops_HCHGS->_hoops_RPIII;

			_hoops_CAHI *= 2;
			ALLOC_ARRAY_CACHED (points, _hoops_CAHI, Point);
			_hoops_HCHGS->_hoops_RPIII = points;
			_hoops_HCHGS->_hoops_SAIII = _hoops_CAHI;

			_hoops_AIGA (_hoops_RRSAA, (long)_hoops_CCHGS, Point, points);
			points += _hoops_ICHGS - 1;

			if (_hoops_RRSAA != &_hoops_HCHGS->_hoops_CAIII[0])
				FREE_ARRAY (_hoops_RRSAA, _hoops_CCHGS, Point);
		}

		if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, points)) return -1;
		++points;

		if (!_hoops_GCHGS (_hoops_GHIPH)) return -1;
	}
	++_hoops_GHIPH->_hoops_ASAPR;

	delta = _hoops_ICHGS - _hoops_HCHGS->_hoops_GPIII;
	_hoops_HCHGS->_hoops_GPIII = _hoops_ICHGS;
	return delta;
}

local int _hoops_SCHGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS) {
	_hoops_ARPA				*planes;
	int						_hoops_GSHGS,
										_hoops_RSHGS;
	int						delta;
	char			*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;

	if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) return false;

	if (!_hoops_RHHGS (_hoops_GHIPH, '('))
		return false;
	if (!_hoops_GCHGS (_hoops_GHIPH)) 
		return false;

	_hoops_GSHGS = _hoops_HCHGS->_hoops_PIIII;
	_hoops_RSHGS = _hoops_HCHGS->_hoops_HIIII;
	planes = _hoops_HCHGS->_hoops_IIIII + _hoops_RSHGS;

	_hoops_RGGA (*_hoops_GHIPH->_hoops_ASAPR == ')') {
		if (++_hoops_RSHGS > _hoops_GSHGS) {
			int				_hoops_ASHGS = _hoops_GSHGS;
			_hoops_ARPA		*_hoops_RRSAA = _hoops_HCHGS->_hoops_IIIII;

			_hoops_GSHGS *= 2;
			ALLOC_ARRAY (planes, _hoops_GSHGS, _hoops_ARPA);
			_hoops_HCHGS->_hoops_IIIII = planes;
			_hoops_HCHGS->_hoops_PIIII = _hoops_GSHGS;

			_hoops_AIGA (_hoops_RRSAA, (long)_hoops_ASHGS, _hoops_ARPA, planes);
			planes += _hoops_RSHGS - 1;

			if (_hoops_RRSAA != &_hoops_HCHGS->_hoops_AIIII[0])
				FREE_ARRAY (_hoops_RRSAA, _hoops_ASHGS, _hoops_ARPA);
		}

		if (!_hoops_GGGII (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, planes)) return -1;
		++planes;

		if (!_hoops_GCHGS (_hoops_GHIPH)) return -1;
	}
	++_hoops_GHIPH->_hoops_ASAPR;

	delta = _hoops_RSHGS - _hoops_HCHGS->_hoops_HIIII;
	_hoops_HCHGS->_hoops_HIIII = _hoops_RSHGS;
	return delta;
}


/* _hoops_HRS _hoops_PHI _hoops_IIGR _hoops_HPS _hoops_IRIGR, _hoops_PAR _hoops_HHHR _hoops_GPP _hoops_RIHH */
local int _hoops_PSHGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS,
	int						which) {
	char					*_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
	int						*_hoops_HSHGS, *_hoops_ISHGS;
	int						**_hoops_CSHGS;
	int						_hoops_SSHGS, _hoops_GGIGS;
	int						*_hoops_RGIGS;
	int						*_hoops_AGIGS;

	switch (which) {
		case 0:
			_hoops_HSHGS = &_hoops_HCHGS->_hoops_HPIII;	 
			_hoops_ISHGS = &_hoops_HCHGS->_hoops_PPIII;
			_hoops_CSHGS = &_hoops_HCHGS->_hoops_IPIII;
			_hoops_AGIGS = _hoops_HCHGS->_hoops_APIII;
			break;
		case 1:
			_hoops_HSHGS = &_hoops_HCHGS->_hoops_GHIII;	 
			_hoops_ISHGS = &_hoops_HCHGS->_hoops_SPIII;
			_hoops_CSHGS = &_hoops_HCHGS->_hoops_RHIII;
			_hoops_AGIGS = _hoops_HCHGS->_hoops_CPIII;
			break;
		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected array id");
			return -1;
	}
	_hoops_SSHGS = *_hoops_HSHGS = 0;	
	_hoops_GGIGS = *_hoops_ISHGS;
	_hoops_RGIGS = *_hoops_CSHGS;

	if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) 
		return -1;

	if (!_hoops_RHHGS (_hoops_GHIPH, '(') ||
		!_hoops_GCHGS (_hoops_GHIPH)) 
			return -1;

	_hoops_RGGA (*_hoops_GHIPH->_hoops_ASAPR == ')') {
		if (_hoops_SSHGS >= _hoops_GGIGS) {
			int				_hoops_PGIGS = _hoops_GGIGS;
			int				*_hoops_RRSAA = _hoops_RGIGS;

			_hoops_GGIGS *= 2;
			ALLOC_ARRAY_CACHED (_hoops_RGIGS, _hoops_GGIGS, int);

			_hoops_AIGA (_hoops_RRSAA, (long)_hoops_PGIGS, int, _hoops_RGIGS);

			if (_hoops_RRSAA != _hoops_AGIGS)
				FREE_ARRAY (_hoops_RRSAA, _hoops_PGIGS, int);
		}

		if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, _hoops_RGIGS + _hoops_SSHGS)) 
			return -1;

		if (!_hoops_GCHGS (_hoops_GHIPH)) 
			return -1;

		_hoops_SSHGS++;
	}
	++_hoops_GHIPH->_hoops_ASAPR;

	*_hoops_HSHGS = _hoops_SSHGS;
	*_hoops_ISHGS = _hoops_GGIGS;
	*_hoops_CSHGS = _hoops_RGIGS;
	return _hoops_SSHGS;
}


local int _hoops_HGIGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS) {
	char					*_hoops_SHGGR;
	int						_hoops_IGIGS,
										_hoops_CGIGS;
	int						delta;

	if (!_hoops_RHHGS (_hoops_GHIPH, '(') ||
		!_hoops_GCHGS (_hoops_GHIPH)) return false;

	_hoops_IGIGS = _hoops_HCHGS->_hoops_PHIII;
	_hoops_CGIGS = _hoops_HCHGS->_hoops_HHIII;
	_hoops_SHGGR = _hoops_HCHGS->_hoops_IHIII + _hoops_CGIGS;

	_hoops_RGGA (*_hoops_GHIPH->_hoops_ASAPR == ')') {
		if (++_hoops_CGIGS > _hoops_IGIGS) {
			int				_hoops_SGIGS = _hoops_IGIGS;
			char			*_hoops_RRSAA = _hoops_HCHGS->_hoops_IHIII;

			_hoops_IGIGS *= 2;
			ALLOC_ARRAY (_hoops_SHGGR, _hoops_IGIGS, char);
			_hoops_HCHGS->_hoops_IHIII = _hoops_SHGGR;
			_hoops_HCHGS->_hoops_PHIII = _hoops_IGIGS;

			_hoops_AIGA (_hoops_RRSAA, (long)_hoops_SGIGS, char, _hoops_SHGGR);
			_hoops_SHGGR += _hoops_CGIGS - 1;

			if (_hoops_RRSAA != &_hoops_HCHGS->_hoops_AHIII[0])
				FREE_ARRAY (_hoops_RRSAA, _hoops_SGIGS, char);
		}

		if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &delta)) 
			return -1;
		*_hoops_SHGGR++ = delta & 0xFF;

		if (!_hoops_GCHGS (_hoops_GHIPH)) 
			return -1;
	}
	++_hoops_GHIPH->_hoops_ASAPR;

	delta = _hoops_CGIGS - _hoops_HCHGS->_hoops_HHIII;
	_hoops_HCHGS->_hoops_HHIII = _hoops_CGIGS;
	return delta;
}


local int _hoops_GRIGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS) {
	float					*_hoops_RRIGS;
	int						_hoops_ARIGS,
										_hoops_PRIGS;
	int						delta;

	if (!_hoops_RHHGS (_hoops_GHIPH, '(') ||
		!_hoops_GCHGS (_hoops_GHIPH)) return false;

	_hoops_ARIGS = _hoops_HCHGS->_hoops_SHIII;
	_hoops_PRIGS = _hoops_HCHGS->_hoops_GIIII;
	_hoops_RRIGS = _hoops_HCHGS->_hoops_RIIII + _hoops_PRIGS;

	_hoops_RGGA (*_hoops_GHIPH->_hoops_ASAPR == ')') {
		if (++_hoops_PRIGS > _hoops_ARIGS) {
			int				_hoops_HRIGS = _hoops_ARIGS;
			float			*_hoops_RRSAA = _hoops_HCHGS->_hoops_RIIII;

			_hoops_ARIGS *= 2;
			ALLOC_ARRAY (_hoops_RRIGS, _hoops_ARIGS, float);
			_hoops_HCHGS->_hoops_RIIII = _hoops_RRIGS;
			_hoops_HCHGS->_hoops_SHIII = _hoops_ARIGS;

			_hoops_AIGA (_hoops_RRSAA, (long)_hoops_HRIGS, float, _hoops_RRIGS);
			_hoops_RRIGS += _hoops_PRIGS - 1;

			if (_hoops_RRSAA != &_hoops_HCHGS->_hoops_CHIII[0])
				FREE_ARRAY (_hoops_RRSAA, _hoops_HRIGS, float);
		}

		if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, _hoops_RRIGS)) return -1;
		++_hoops_RRIGS;

		if (!_hoops_GCHGS (_hoops_GHIPH)) return -1;
	}
	++_hoops_GHIPH->_hoops_ASAPR;

	delta = _hoops_PRIGS - _hoops_HCHGS->_hoops_GIIII;
	_hoops_HCHGS->_hoops_GIIII = _hoops_PRIGS;
	return delta;
}
#endif


local bool _hoops_IRIGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS,
	int						which) {
#ifndef DISABLE_METAFILE

	if (which != 0) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected number of arrays");
		return false;
	}
	_hoops_HCHGS->_hoops_GPIII = 0;
	return (_hoops_PCHGS (_hoops_GHIPH, _hoops_HCHGS) >= 0);
#else
	return false;
#endif
}

local bool _hoops_CRIGS (
	_hoops_IRIPH *				_hoops_GHIPH,
	_hoops_GAIII *	_hoops_HCHGS,
	int						which) 
{
#ifndef DISABLE_METAFILE

	if (which != 0) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected number of arrays");
		return false;
	}
	_hoops_HCHGS->_hoops_HIIII = 0;
	return (_hoops_SCHGS (_hoops_GHIPH, _hoops_HCHGS) >= 0);
#else
	return false;
#endif
}


local bool _hoops_SRIGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS,
	int						which) {
#ifndef DISABLE_METAFILE

	return (_hoops_PSHGS (_hoops_GHIPH, _hoops_HCHGS, which) >= 0);
#else
	return false;
#endif
}


local bool _hoops_GAIGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS,
	int						which) {
#ifndef DISABLE_METAFILE

	if (which != 0) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected number of arrays");
		return false;
	}
	_hoops_HCHGS->_hoops_HHIII = 0;
	return (_hoops_HGIGS (_hoops_GHIPH, _hoops_HCHGS) >= 0);
#else
	return false;
#endif
}


local bool _hoops_RAIGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS,
	int						which) {
#ifndef DISABLE_METAFILE

	if (which != 0) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected number of arrays");
		return false;
	}
	_hoops_HCHGS->_hoops_GIIII = 0;
	return (_hoops_GRIGS (_hoops_GHIPH, _hoops_HCHGS) >= 0);
#else
	return false;
#endif
}


#ifndef DISABLE_METAFILE
/* _hoops_AAIGS
 * _hoops_HGCR _hoops_IRS _hoops_AAS _hoops_IIGR _hoops_GH _hoops_IS 128 _hoops_ISIAR _hoops_PAIGS _hoops_HPS.
 * _hoops_HHIGR _hoops_HRGR _hoops_CRICR _hoops_IS _hoops_HAIGS _hoops_IAIGS _hoops_CAIGS, _hoops_AHSAR _hoops_SGS _hoops_SCH _hoops_RHAP _hoops_HAR _hoops_CRCR
 * _hoops_CPARA ("), _hoops_PPR _hoops_RHAP _hoops_HAR _hoops_GCGH _hoops_GII _hoops_PGPCR _hoops_SAIGS _hoops_PAR _hoops_GRH
 * _hoops_GPIGS */
local bool _hoops_RPIGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	char				*name) {
	int i;

	for (i = 0; i < 128; i++) 
	{
		if (_hoops_GHIPH->_hoops_ASAPR == _hoops_GHIPH->_hoops_PSAPR) {
			if (!_hoops_CAHGS (_hoops_GHIPH))
				return false;
		}
		if ((*_hoops_GHIPH->_hoops_ASAPR >= 'a') && (*_hoops_GHIPH->_hoops_ASAPR <= 'z'))
			*name++ = *_hoops_GHIPH->_hoops_ASAPR++;
		else if ((*_hoops_GHIPH->_hoops_ASAPR >= 'A') &&	(*_hoops_GHIPH->_hoops_ASAPR <= 'Z'))
			*name++ = _hoops_SHPCR(*_hoops_GHIPH->_hoops_ASAPR++);
		else if (*_hoops_GHIPH->_hoops_ASAPR == '_')
			*name++ = *_hoops_GHIPH->_hoops_ASAPR++;
		else 
			break;
	}
	*name = '\0';
	if ((i == 0) || (i == 128))
		return false;
	else
		return true;
} /* _hoops_RSGR _hoops_API _hoops_AAIGS */
#endif


/* 
 * _hoops_GAGIP _hoops_IH _hoops_RH _hoops_AHAR _hoops_IIGR _hoops_GPS _hoops_GGR _hoops_IRCPH' _hoops_RIRCP _hoops_AAAPR, _hoops_HIH
 * _hoops_GHCA _hoops_SHH _hoops_PASI _hoops_PSIGA.	_hoops_HHIGR _hoops_SAGGR _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_PHRP _hoops_GGR _hoops_RH _hoops_HSPR
 * _hoops_RPCC (_hoops_AAS (_hoops_APIGS _hoops_PPIGS _hoops_HPIGS _hoops_IPIGS ...)) _hoops_CAS _hoops_RH _hoops_AAS _hoops_HRGR _hoops_IGI _hoops_IS _hoops_PIAAR
 * _hoops_RH _hoops_PHRP.
 */
local bool _hoops_CPIGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS,
	int						which) {
#ifndef DISABLE_METAFILE

	if (which != 0) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected number of arrays");
		return false;
	}

	_hoops_HCHGS->_hoops_GIIII = 0;
	if (!_hoops_GCHGS (_hoops_GHIPH)) 
		return false;
	/* _hoops_RIARR, _hoops_HIH _hoops_GA'_hoops_RA _hoops_RHRRH _hoops_RIHH, _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_SPIGS _hoops_RGGR */
	if (*_hoops_GHIPH->_hoops_ASAPR == '(')
		_hoops_GHIPH->_hoops_ASAPR++;
	else
		return false;
	if (!_hoops_GCHGS (_hoops_GHIPH))
		return false;
	if (!_hoops_RPIGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII))
		return false;
	if (!_hoops_GCHGS (_hoops_GHIPH))
		return false;
	if (_hoops_GRIGS (_hoops_GHIPH, _hoops_HCHGS) < 0)
		return false;
	if (!_hoops_GCHGS (_hoops_GHIPH))
		return false;
	if (!_hoops_RHHGS (_hoops_GHIPH, ')')) 
		return false;

	return true;
#else
	return false;
#endif
} /* _hoops_RSGR _hoops_API _hoops_GHIGS */


local bool _hoops_RHIGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS,
	int						which) {
#ifndef DISABLE_METAFILE
	int						_hoops_AHIGS;
	bool				_hoops_PHIGS = false;

	if (which != 0) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected number of arrays");
		return false;
	}

	_hoops_HCHGS->_hoops_GPIII = 0;

	if (!_hoops_RHHGS (_hoops_GHIPH, '(') ||
		!_hoops_GCHGS (_hoops_GHIPH) ||
		(_hoops_HCHGS->_hoops_GCIII = _hoops_PCHGS (_hoops_GHIPH, _hoops_HCHGS)) < 0 ||
		!_hoops_GCHGS (_hoops_GHIPH)) return false;

	_hoops_RGGA (*_hoops_GHIPH->_hoops_ASAPR == ')') {
		if ((_hoops_AHIGS = _hoops_PCHGS (_hoops_GHIPH, _hoops_HCHGS)) < 0)
			return false;

		if (_hoops_AHIGS != _hoops_HCHGS->_hoops_GCIII && !_hoops_PHIGS) {
			char	buf[MAX_ERRMSG];

			_hoops_GHIPH->message = Sprintf_DD (buf,
				"First row of mesh had %d points but current row has %d",
				_hoops_HCHGS->_hoops_GCIII, _hoops_AHIGS);

			HI_Report_File_Error (_hoops_GHIPH);
			_hoops_PHIGS = true;
		}

		if (!_hoops_GCHGS (_hoops_GHIPH)) return false;
	}
	++_hoops_GHIPH->_hoops_ASAPR;

	if (_hoops_HCHGS->_hoops_GCIII == 0)
		_hoops_HCHGS->_hoops_SIIII = 0;
	else
		_hoops_HCHGS->_hoops_SIIII = _hoops_HCHGS->_hoops_GPIII / _hoops_HCHGS->_hoops_GCIII;

	return true;
#else
	return false;
#endif
}


#ifndef DISABLE_METAFILE
local bool _hoops_HHIGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	float					c[4]) 
{
	return
		_hoops_RHHGS (_hoops_GHIPH, '(') &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &c[0]) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &c[1]) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &c[2]) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &c[3]) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_RHHGS (_hoops_GHIPH, ')');
}
#endif


local bool _hoops_IHIGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	float alter *			matp) 
{
#ifndef DISABLE_METAFILE
	_hoops_RPRA alter		*mat = (_hoops_RPRA alter *)matp;

	return
		_hoops_RHHGS (_hoops_GHIPH, '(') &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HHIGS (_hoops_RIGC, _hoops_GHIPH, &mat[0][0]) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HHIGS (_hoops_RIGC, _hoops_GHIPH, &mat[1][0]) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HHIGS (_hoops_RIGC, _hoops_GHIPH, &mat[2][0]) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_HHIGS (_hoops_RIGC, _hoops_GHIPH, &mat[3][0]) &&
		_hoops_GCHGS (_hoops_GHIPH) &&
		_hoops_RHHGS (_hoops_GHIPH, ')');
#else
	return false;
#endif
}


#ifndef DISABLE_METAFILE
local void *_hoops_CHIGS (
	void			*_hoops_SHIGS,
	int				_hoops_GIIGS,
	int				_hoops_CICSA,
	int				_hoops_RCRGA,
	int				bpp) {
	unsigned char	*_hoops_RIIGS;

	ALLOC_ARRAY (_hoops_RIIGS, _hoops_RCRGA * bpp, unsigned char);

	COPY_MEMORY (_hoops_SHIGS, (long)_hoops_GIIGS * bpp, (void *)_hoops_RIIGS);

	FREE_ARRAY (_hoops_SHIGS, _hoops_CICSA * bpp, unsigned char);

	return (void *)_hoops_RIIGS;
}


local void **_hoops_AIIGS (
	void			**_hoops_GCGCC,
	int				_hoops_GIIGS,
	int				_hoops_CICSA,
	int				_hoops_RCRGA) {
	void			**_hoops_PIIGS;

	ALLOC_ARRAY (_hoops_PIIGS, _hoops_RCRGA, void *);
	_hoops_AIGA(_hoops_GCGCC, _hoops_GIIGS, void *, _hoops_PIIGS);
	FREE_ARRAY (_hoops_GCGCC, _hoops_CICSA, void *);
	return _hoops_PIIGS;
}


local void _hoops_HIIGS (
	void			**table,
	int				height,
	int				width,
	int				_hoops_IIIGS,
	int				bpp) {
	int				count = _hoops_IIIGS;

	_hoops_RGGA (--count < 0) {
		void			*_hoops_GAAC = *table++;
		FREE_ARRAY (_hoops_GAAC, width * bpp, unsigned char);
	}
	table -= _hoops_IIIGS;
	FREE_ARRAY (table, height, void *);
}
#endif


local bool _hoops_CIIGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	char *					_hoops_SIIGS,
	int *					_hoops_GCIGS,
	int *					_hoops_RCIGS,
	void ***				_hoops_ACIGS) 
{
#ifndef DISABLE_METAFILE
	void **			_hoops_PCIGS;
	void **			_hoops_HCIGS;
	void **			_hoops_ICIGS;
#	define		_hoops_CCIGS		128		/* "128" _hoops_HRGR _hoops_SCSAA */
#	define		_hoops_SCIGS	_hoops_CCIGS
	int				width = _hoops_CCIGS;
	int				height = _hoops_SCIGS;
	int				i;
	float			f;
	Image_Format	format;
	int				bpp;

	/* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RH _hoops_HPHR _hoops_IGAA _hoops_CCGR _hoops_RAS _hoops_RH _hoops_SRS _hoops_GAGHR;
	* _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RH _hoops_HPHR _hoops_APPS _hoops_CCGR _hoops_RH _hoops_CPPPR _hoops_RSGR. _hoops_CGP _hoops_PA
	* _hoops_IAGA _hoops_RHPH, _hoops_CPS _hoops_SSCP _hoops_IS _hoops_SHH _hoops_HGGPR.
	*/

	if (_hoops_SIIGS == null)
		format = Image_MAPPED_16;		/* _hoops_AIR _hoops_CRPR */
	else
		if ((format = HI_Determine_Image_Format (_hoops_RIGC, _hoops_SIIGS, null)) == _hoops_CAHPA)
			return false;

	/* _hoops_HGCR _hoops_HGSI _hoops_SPIGS (*/
	if (!_hoops_RHHGS (_hoops_GHIPH, '(')) return false;

	/* _hoops_HGCR _hoops_RH _hoops_SRS _hoops_PPSCP (_hoops_SPCC _hoops_RHGC) */

	if (!_hoops_GCHGS (_hoops_GHIPH) ||
		!_hoops_RHHGS (_hoops_GHIPH, '(') ||
		!_hoops_GCHGS (_hoops_GHIPH)) return false;

	switch (format) {
#ifndef DISABLE_NON_RGB_IMAGES
		case _hoops_PCCRH: {
			float	*_hoops_GAAC;
			float	*_hoops_GSIGS,
								*_hoops_RSIGS;

			bpp = 4;
			ALLOC_ARRAY (_hoops_GAAC, _hoops_CCIGS, float);
			width = _hoops_CCIGS;
			_hoops_RSIGS = _hoops_GAAC;
			_hoops_GSIGS = _hoops_GAAC + _hoops_CCIGS;

			_hoops_PCCAR {
				if (!_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &f) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, float);
					return false;
				}

				*_hoops_GAAC++ = (float)f;

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (_hoops_GAAC == _hoops_GSIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_RSIGS = (float *)_hoops_CHIGS (
						_hoops_RSIGS, width, width, 2*width, bpp);
					_hoops_GAAC = _hoops_RSIGS + width;
					_hoops_GSIGS = _hoops_GAAC + width;
					width += width;
				}
			}

			if (_hoops_GAAC != _hoops_GSIGS) { /* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_ASIGS = width;
				width = _hoops_GAAC - _hoops_RSIGS;
				_hoops_RSIGS = (float *)_hoops_CHIGS (
						_hoops_RSIGS, width, _hoops_ASIGS, width, bpp);
			}
			/* "_hoops_IGAA" _hoops_HRGR _hoops_HA _hoops_RH _hoops_HPHR _hoops_IGAA */

			/* _hoops_IRHH _hoops_PCCP _hoops_CIGS _hoops_AHGC */
			ALLOC_ARRAY (_hoops_PCIGS, _hoops_SCIGS, void *);
			height = _hoops_SCIGS;
			_hoops_ICIGS = _hoops_PCIGS;
			_hoops_HCIGS = _hoops_PCIGS + _hoops_SCIGS;

			/* _hoops_IRAA _hoops_RH _hoops_SPR _hoops_SR _hoops_AIAH _hoops_HS */
			*_hoops_PCIGS++ = (_hoops_GARSR *)_hoops_RSIGS;

			_hoops_PCCAR {
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {		/* _hoops_CSCR _hoops_HCR _hoops_CPHR */
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR++ != '(') {		/* _hoops_HAR _hoops_IRS _hoops_CCAH _hoops_PPSCP?? */
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					_hoops_GHIPH->message =
						"Expected ')' to end the image or '(' to begin a raster";
					HI_Report_File_Error (_hoops_GHIPH);
					return false;
				}

				/* _hoops_HGCR _hoops_IRS _hoops_SHSC _hoops_CCAH _hoops_PPSCP */
				if (_hoops_PCIGS == _hoops_HCIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
														height, height, 2*height);
					_hoops_PCIGS = _hoops_ICIGS + height;
					_hoops_HCIGS = _hoops_PCIGS + height;
					height += height;
				}
				ALLOC_ARRAY (_hoops_GAAC, width, float);
				_hoops_GSIGS = _hoops_GAAC + width;
				*_hoops_PCIGS++ = (void *)_hoops_GAAC;

				/* _hoops_IRIGR _hoops_SCH _hoops_GGR */
				do {
					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &f)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					*_hoops_GAAC++ = (float)f;
				}
				_hoops_RGGA (_hoops_GAAC == _hoops_GSIGS);

				/* _hoops_HPIRA _hoops_SCH _hoops_PSAP */
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_RHHGS (_hoops_GHIPH, ')')) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}
			}

			if (_hoops_PCIGS != _hoops_HCIGS) {/* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_PSIGS = height;
				height = _hoops_PCIGS - _hoops_ICIGS;
				_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
															 height, _hoops_PSIGS,
															 height);
			}

			*_hoops_ACIGS = _hoops_ICIGS;
		} 	break;

		case Image_MAPPED_16: {
			_hoops_GARSR	*_hoops_GAAC;
			_hoops_GARSR	*_hoops_GSIGS,
										*_hoops_RSIGS;

			bpp = 2;
			ALLOC_ARRAY (_hoops_GAAC, _hoops_CCIGS, _hoops_GARSR);
			width = _hoops_CCIGS;
			_hoops_RSIGS = _hoops_GAAC;
			_hoops_GSIGS = _hoops_GAAC + _hoops_CCIGS;

			_hoops_PCCAR {
				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_GARSR);
					return false;
				}

				*_hoops_GAAC++ = (_hoops_GARSR)i;

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (_hoops_GAAC == _hoops_GSIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_RSIGS = (_hoops_GARSR *)_hoops_CHIGS (
						_hoops_RSIGS, width, width, 2*width, bpp);
					_hoops_GAAC = _hoops_RSIGS + width;
					_hoops_GSIGS = _hoops_GAAC + width;
					width += width;
				}
			}

			if (_hoops_GAAC != _hoops_GSIGS) { /* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_ASIGS = width;
				width = _hoops_GAAC - _hoops_RSIGS;
				_hoops_RSIGS = (_hoops_GARSR *)_hoops_CHIGS (
						_hoops_RSIGS, width, _hoops_ASIGS, width, bpp);
			}
			/* "_hoops_IGAA" _hoops_HRGR _hoops_HA _hoops_RH _hoops_HPHR _hoops_IGAA */

			/* _hoops_IRHH _hoops_PCCP _hoops_CIGS _hoops_AHGC */
			ALLOC_ARRAY (_hoops_PCIGS, _hoops_SCIGS, void *);
			height = _hoops_SCIGS;
			_hoops_ICIGS = _hoops_PCIGS;
			_hoops_HCIGS = _hoops_PCIGS + _hoops_SCIGS;

			/* _hoops_IRAA _hoops_RH _hoops_SPR _hoops_SR _hoops_AIAH _hoops_HS */
			*_hoops_PCIGS++ = (_hoops_GARSR *)_hoops_RSIGS;

			_hoops_PCCAR {
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {		/* _hoops_CSCR _hoops_HCR _hoops_CPHR */
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR++ != '(') {		/* _hoops_HAR _hoops_IRS _hoops_CCAH _hoops_PPSCP?? */
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					_hoops_GHIPH->message =
						"Expected ')' to end the image or '(' to begin a raster";
					HI_Report_File_Error (_hoops_GHIPH);
					return false;
				}

				/* _hoops_HGCR _hoops_IRS _hoops_SHSC _hoops_CCAH _hoops_PPSCP */
				if (_hoops_PCIGS == _hoops_HCIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
														height, height, 2*height);
					_hoops_PCIGS = _hoops_ICIGS + height;
					_hoops_HCIGS = _hoops_PCIGS + height;
					height += height;
				}
				ALLOC_ARRAY (_hoops_GAAC, width, _hoops_GARSR);
				_hoops_GSIGS = _hoops_GAAC + width;
				*_hoops_PCIGS++ = (void *)_hoops_GAAC;

				/* _hoops_IRIGR _hoops_SCH _hoops_GGR */
				do {
					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					*_hoops_GAAC++ = (_hoops_GARSR)i;
				}
				_hoops_RGGA (_hoops_GAAC == _hoops_GSIGS);

				/* _hoops_HPIRA _hoops_SCH _hoops_PSAP */
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_RHHGS (_hoops_GHIPH, ')')) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}
			}

			if (_hoops_PCIGS != _hoops_HCIGS) {/* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_PSIGS = height;
				height = _hoops_PCIGS - _hoops_ICIGS;
				_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
															 height, _hoops_PSIGS,
															 height);
			}

			*_hoops_ACIGS = _hoops_ICIGS;
		}	break;
#endif

		case _hoops_AHGH:
		case Image_MAPPED_8: {
			unsigned char	*_hoops_GAAC;
			unsigned char	*_hoops_GSIGS,
										*_hoops_RSIGS;

			bpp = 1;
			ALLOC_ARRAY (_hoops_GAAC, _hoops_CCIGS, unsigned char);
			width = _hoops_CCIGS;
			_hoops_RSIGS = _hoops_GAAC;
			_hoops_GSIGS = _hoops_GAAC + _hoops_CCIGS;

			_hoops_PCCAR {
				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, unsigned char);
					return false;
				}

				*_hoops_GAAC++ = (unsigned char)i;

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (_hoops_GAAC == _hoops_GSIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_RSIGS = (unsigned char *)_hoops_CHIGS (
						_hoops_RSIGS, width, width, 2*width, bpp);
					_hoops_GAAC = _hoops_RSIGS + width;
					_hoops_GSIGS = _hoops_GAAC + width;
					width += width;
				}
			}

			if (_hoops_GAAC != _hoops_GSIGS) { /* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_ASIGS = width;
				width = _hoops_GAAC - _hoops_RSIGS;
				_hoops_RSIGS = (unsigned char *)_hoops_CHIGS (
					_hoops_RSIGS, width, _hoops_ASIGS, width, bpp);
			}
			/* "_hoops_IGAA" _hoops_HRGR _hoops_HA _hoops_RH _hoops_HPHR _hoops_IGAA */

			/* _hoops_IRHH _hoops_PCCP _hoops_CIGS _hoops_AHGC */
			ALLOC_ARRAY (_hoops_PCIGS, _hoops_SCIGS, void *);
			height = _hoops_SCIGS;
			_hoops_ICIGS = _hoops_PCIGS;
			_hoops_HCIGS = _hoops_PCIGS + _hoops_SCIGS;

			/* _hoops_IRAA _hoops_RH _hoops_SPR _hoops_SR _hoops_AIAH _hoops_HS */
			*_hoops_PCIGS++ = (unsigned char *)_hoops_RSIGS;

			_hoops_PCCAR {
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {		/* _hoops_CSCR _hoops_HCR _hoops_CPHR */
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR++ != '(') {		/* _hoops_HAR _hoops_IRS _hoops_CCAH _hoops_PPSCP?? */
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					_hoops_GHIPH->message =
						"Expected ')' to end the image or '(' to begin a raster";
					HI_Report_File_Error (_hoops_GHIPH);
					return false;
				}

				/* _hoops_HGCR _hoops_IRS _hoops_SHSC _hoops_CCAH _hoops_PPSCP */
				if (_hoops_PCIGS == _hoops_HCIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
														height, height, 2*height);
					_hoops_PCIGS = _hoops_ICIGS + height;
					_hoops_HCIGS = _hoops_PCIGS + height;
					height += height;
				}
				ALLOC_ARRAY (_hoops_GAAC, width, unsigned char);
				_hoops_GSIGS = _hoops_GAAC + width;
				*_hoops_PCIGS++ = (void *)_hoops_GAAC;

				/* _hoops_IRIGR _hoops_SCH _hoops_GGR */
				do {
					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					*_hoops_GAAC++ = (unsigned char)i;
				}
				_hoops_RGGA (_hoops_GAAC == _hoops_GSIGS);

				/* _hoops_HPIRA _hoops_SCH _hoops_PSAP */
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_RHHGS (_hoops_GHIPH, ')')) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}
			}

			if (_hoops_PCIGS != _hoops_HCIGS) {/* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_PSIGS = height;
				height = _hoops_PCIGS - _hoops_ICIGS;
				_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
															 height, _hoops_PSIGS,
															 height);
			}

			*_hoops_ACIGS = _hoops_ICIGS;
		}	break;

		case _hoops_HHGH: {
			_hoops_SHGH		*_hoops_GAAC;
			_hoops_SHGH		*_hoops_GSIGS,
										*_hoops_RSIGS;

			bpp = 3;
			ALLOC_ARRAY (_hoops_GAAC, _hoops_CCIGS, _hoops_SHGH);
			width = _hoops_CCIGS;
			_hoops_RSIGS = _hoops_GAAC;
			_hoops_GSIGS = _hoops_GAAC + _hoops_CCIGS;

			_hoops_PCCAR {
				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_SHGH);
					return false;
				}
				_hoops_GAAC->r = (unsigned char)i;

				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_SHGH);
					return false;
				}
				_hoops_GAAC->g = (unsigned char)i;

				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_SHGH);
					return false;
				}
				_hoops_GAAC->b = (unsigned char)i;

				++_hoops_GAAC;

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (_hoops_GAAC == _hoops_GSIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_RSIGS = (_hoops_SHGH *)_hoops_CHIGS (
						_hoops_RSIGS, width, width, 2*width, bpp);
					_hoops_GAAC = _hoops_RSIGS + width;
					_hoops_GSIGS = _hoops_GAAC + width;
					width += width;
				}
			}

			if (_hoops_GAAC != _hoops_GSIGS) { /* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_ASIGS = width;
				width = _hoops_GAAC - _hoops_RSIGS;
				_hoops_RSIGS = (_hoops_SHGH *)_hoops_CHIGS (
						_hoops_RSIGS, width, _hoops_ASIGS, width, bpp);
			}
			/* "_hoops_IGAA" _hoops_HRGR _hoops_HA _hoops_RH _hoops_HPHR _hoops_IGAA */

			/* _hoops_IRHH _hoops_PCCP _hoops_CIGS _hoops_AHGC */
			ALLOC_ARRAY (_hoops_PCIGS, _hoops_SCIGS, void *);
			height = _hoops_SCIGS;
			_hoops_ICIGS = _hoops_PCIGS;
			_hoops_HCIGS = _hoops_PCIGS + _hoops_SCIGS;

			/* _hoops_IRAA _hoops_RH _hoops_SPR _hoops_SR _hoops_AIAH _hoops_HS */
			*_hoops_PCIGS++ = (_hoops_SHGH *)_hoops_RSIGS;

			_hoops_PCCAR {
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {		/* _hoops_CSCR _hoops_HCR _hoops_CPHR */
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR++ != '(') {		/* _hoops_HAR _hoops_IRS _hoops_CCAH _hoops_PPSCP?? */
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					_hoops_GHIPH->message =
						"Expected ')' to end the image or '(' to begin a raster";
					HI_Report_File_Error (_hoops_GHIPH);
					return false;
				}

				/* _hoops_HGCR _hoops_IRS _hoops_SHSC _hoops_CCAH _hoops_PPSCP */
				if (_hoops_PCIGS == _hoops_HCIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
														height, height, 2*height);
					_hoops_PCIGS = _hoops_ICIGS + height;
					_hoops_HCIGS = _hoops_PCIGS + height;
					height += height;
				}
				ALLOC_ARRAY (_hoops_GAAC, width, _hoops_SHGH);
				_hoops_GSIGS = _hoops_GAAC + width;
				*_hoops_PCIGS++ = (void *)_hoops_GAAC;

				/* _hoops_IRIGR _hoops_SCH _hoops_GGR */
				do {
					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					_hoops_GAAC->r = (unsigned char)i;

					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					_hoops_GAAC->g = (unsigned char)i;

					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					_hoops_GAAC->b = (unsigned char)i;

				}
				_hoops_RGGA (++_hoops_GAAC == _hoops_GSIGS);

				/* _hoops_HPIRA _hoops_SCH _hoops_PSAP */
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_RHHGS (_hoops_GHIPH, ')')) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}
			}

			if (_hoops_PCIGS != _hoops_HCIGS) {/* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_PSIGS = height;
				height = _hoops_PCIGS - _hoops_ICIGS;
				_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
															 height, _hoops_PSIGS,
															 height);
			}

			*_hoops_ACIGS = _hoops_ICIGS;
		}	break;

#ifndef DISABLE_NON_RGB_IMAGES
		case _hoops_HRSRH: {
			_hoops_IRSRH		*_hoops_GAAC;
			_hoops_IRSRH		*_hoops_GSIGS,
										*_hoops_RSIGS;

			bpp = 4;
			ALLOC_ARRAY (_hoops_GAAC, _hoops_CCIGS, _hoops_IRSRH);
			width = _hoops_CCIGS;
			_hoops_RSIGS = _hoops_GAAC;
			_hoops_GSIGS = _hoops_GAAC + _hoops_CCIGS;

			_hoops_PCCAR {
				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_IRSRH);
					return false;
				}
				_hoops_GAAC->a = (unsigned char)i;

				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_IRSRH);
					return false;
				}
				_hoops_GAAC->r = (unsigned char)i;

				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_IRSRH);
					return false;
				}
				_hoops_GAAC->g = (unsigned char)i;

				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_IRSRH);
					return false;
				}
				_hoops_GAAC->b = (unsigned char)i;

				++_hoops_GAAC;

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (_hoops_GAAC == _hoops_GSIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_RSIGS = (_hoops_IRSRH *)_hoops_CHIGS (
						_hoops_RSIGS, width, width, 2*width, bpp);
					_hoops_GAAC = _hoops_RSIGS + width;
					_hoops_GSIGS = _hoops_GAAC + width;
					width += width;
				}
			}

			if (_hoops_GAAC != _hoops_GSIGS) { /* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_ASIGS = width;
				width = _hoops_GAAC - _hoops_RSIGS;
				_hoops_RSIGS = (_hoops_IRSRH *)_hoops_CHIGS (
						_hoops_RSIGS, width, _hoops_ASIGS, width, bpp);
			}
			/* "_hoops_IGAA" _hoops_HRGR _hoops_HA _hoops_RH _hoops_HPHR _hoops_IGAA */

			/* _hoops_IRHH _hoops_PCCP _hoops_CIGS _hoops_AHGC */
			ALLOC_ARRAY (_hoops_PCIGS, _hoops_SCIGS, void *);
			height = _hoops_SCIGS;
			_hoops_ICIGS = _hoops_PCIGS;
			_hoops_HCIGS = _hoops_PCIGS + _hoops_SCIGS;

			/* _hoops_IRAA _hoops_RH _hoops_SPR _hoops_SR _hoops_AIAH _hoops_HS */
			*_hoops_PCIGS++ = (_hoops_IRSRH *)_hoops_RSIGS;

			_hoops_PCCAR {
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {		/* _hoops_CSCR _hoops_HCR _hoops_CPHR */
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR++ != '(') {		/* _hoops_HAR _hoops_IRS _hoops_CCAH _hoops_PPSCP?? */
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					_hoops_GHIPH->message =
						"Expected ')' to end the image or '(' to begin a raster";
					HI_Report_File_Error (_hoops_GHIPH);
					return false;
				}

				/* _hoops_HGCR _hoops_IRS _hoops_SHSC _hoops_CCAH _hoops_PPSCP */
				if (_hoops_PCIGS == _hoops_HCIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
														height, height, 2*height);
					_hoops_PCIGS = _hoops_ICIGS + height;
					_hoops_HCIGS = _hoops_PCIGS + height;
					height += height;
				}
				ALLOC_ARRAY (_hoops_GAAC, width, _hoops_IRSRH);
				_hoops_GSIGS = _hoops_GAAC + width;
				*_hoops_PCIGS++ = (void *)_hoops_GAAC;

				/* _hoops_IRIGR _hoops_SCH _hoops_GGR */
				do {
					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					_hoops_GAAC->a = (unsigned char)i;

					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					_hoops_GAAC->r = (unsigned char)i;

					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					_hoops_GAAC->g = (unsigned char)i;

					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					_hoops_GAAC->b = (unsigned char)i;

				}
				_hoops_RGGA (++_hoops_GAAC == _hoops_GSIGS);

				/* _hoops_HPIRA _hoops_SCH _hoops_PSAP */
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_RHHGS (_hoops_GHIPH, ')')) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}
			}

			if (_hoops_PCIGS != _hoops_HCIGS) {/* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_PSIGS = height;
				height = _hoops_PCIGS - _hoops_ICIGS;
				_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
															 height, _hoops_PSIGS,
															 height);
			}

			*_hoops_ACIGS = _hoops_ICIGS;
		}	break;
#endif

		case Image_RGBA32: {
			_hoops_AIGH		*_hoops_GAAC;
			_hoops_AIGH		*_hoops_GSIGS,
										*_hoops_RSIGS;

			bpp = 4;
			ALLOC_ARRAY (_hoops_GAAC, _hoops_CCIGS, _hoops_AIGH);
			width = _hoops_CCIGS;
			_hoops_RSIGS = _hoops_GAAC;
			_hoops_GSIGS = _hoops_GAAC + _hoops_CCIGS;

			_hoops_PCCAR {

				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_AIGH);
					return false;
				}
				_hoops_GAAC->r = (unsigned char)i;

				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_AIGH);
					return false;
				}
				_hoops_GAAC->g = (unsigned char)i;

				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_AIGH);
					return false;
				}
				_hoops_GAAC->b = (unsigned char)i;

				if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i) ||
					!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					FREE_ARRAY (_hoops_RSIGS, width, _hoops_AIGH);
					return false;
				}
				_hoops_GAAC->a = (unsigned char)i;

				++_hoops_GAAC;

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (_hoops_GAAC == _hoops_GSIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_RSIGS = (_hoops_AIGH *)_hoops_CHIGS (
						_hoops_RSIGS, width, width, 2*width, bpp);
					_hoops_GAAC = _hoops_RSIGS + width;
					_hoops_GSIGS = _hoops_GAAC + width;
					width += width;
				}
			}

			if (_hoops_GAAC != _hoops_GSIGS) { /* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_ASIGS = width;
				width = _hoops_GAAC - _hoops_RSIGS;
				_hoops_RSIGS = (_hoops_AIGH *)_hoops_CHIGS (
						_hoops_RSIGS, width, _hoops_ASIGS, width, bpp);
			}
			/* "_hoops_IGAA" _hoops_HRGR _hoops_HA _hoops_RH _hoops_HPHR _hoops_IGAA */

			/* _hoops_IRHH _hoops_PCCP _hoops_CIGS _hoops_AHGC */
			ALLOC_ARRAY (_hoops_PCIGS, _hoops_SCIGS, void *);
			height = _hoops_SCIGS;
			_hoops_ICIGS = _hoops_PCIGS;
			_hoops_HCIGS = _hoops_PCIGS + _hoops_SCIGS;

			/* _hoops_IRAA _hoops_RH _hoops_SPR _hoops_SR _hoops_AIAH _hoops_HS */
			*_hoops_PCIGS++ = (_hoops_AIGH *)_hoops_RSIGS;

			_hoops_PCCAR {
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_SAHGS (_hoops_GHIPH)) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR == ')') {		/* _hoops_CSCR _hoops_HCR _hoops_CPHR */
					++_hoops_GHIPH->_hoops_ASAPR;
					break;
				}

				if (*_hoops_GHIPH->_hoops_ASAPR++ != '(') {		/* _hoops_HAR _hoops_IRS _hoops_CCAH _hoops_PPSCP?? */
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					_hoops_GHIPH->message =
						"Expected ')' to end the image or '(' to begin a raster";
					HI_Report_File_Error (_hoops_GHIPH);
					return false;
				}

				/* _hoops_HGCR _hoops_IRS _hoops_SHSC _hoops_CCAH _hoops_PPSCP */
				if (_hoops_PCIGS == _hoops_HCIGS) {
					/* _hoops_SIPHA _hoops_PPR _hoops_IPS _hoops_IAPR */
					_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
														height, height, 2*height);
					_hoops_PCIGS = _hoops_ICIGS + height;
					_hoops_HCIGS = _hoops_PCIGS + height;
					height += height;
				}
				ALLOC_ARRAY (_hoops_GAAC, width, _hoops_AIGH);
				_hoops_GSIGS = _hoops_GAAC + width;
				*_hoops_PCIGS++ = (void *)_hoops_GAAC;

				/* _hoops_IRIGR _hoops_SCH _hoops_GGR */
				do {

					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					_hoops_GAAC->r = (unsigned char)i;

					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					_hoops_GAAC->g = (unsigned char)i;

					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					_hoops_GAAC->b = (unsigned char)i;

					if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &i)) {
						_hoops_HIIGS (_hoops_ICIGS,
										  height, width,
										  _hoops_PCIGS - _hoops_ICIGS, bpp);
						return false;
					}
					_hoops_GAAC->a = (unsigned char)i;
				}
				_hoops_RGGA (++_hoops_GAAC == _hoops_GSIGS);

				/* _hoops_HPIRA _hoops_SCH _hoops_PSAP */
				if (!_hoops_GCHGS (_hoops_GHIPH) || !_hoops_RHHGS (_hoops_GHIPH, ')')) {
					_hoops_HIIGS (_hoops_ICIGS,
									  height, width,
									  _hoops_PCIGS - _hoops_ICIGS, bpp);
					return false;
				}
			}

			if (_hoops_PCIGS != _hoops_HCIGS) {/* _hoops_RPP _hoops_RII _hoops_HSAR _hoops_IRS _hoops_RRHP _hoops_PSSP */
				int				_hoops_PSIGS = height;
				height = _hoops_PCIGS - _hoops_ICIGS;
				_hoops_ICIGS = _hoops_AIIGS (_hoops_ICIGS,
															 height, _hoops_PSIGS,
															 height);
			}

			*_hoops_ACIGS = _hoops_ICIGS;
		}	break;

		default:
			_hoops_GHIPH->message = "Unexpected image format";
			HI_Report_File_Error (_hoops_GHIPH);
			return false; /* _hoops_RIHH */
	}

	*_hoops_GCIGS = width;
	*_hoops_RCIGS = height;
	return true;
#else
	return false;
#endif
}

#ifndef DISABLE_METAFILE

local const char _hoops_HSIGS[] =
	"Unexpected end of file while reading a character string";

#endif

local void _hoops_ISIGS (
	char alter * alter &	sp,
	int alter &				length) {
	char const *			_hoops_CSIGS = sp;
	int						_hoops_SSIGS = length;

	if (length < _hoops_CRIII)
		length *= 2;
	else
		length += _hoops_CRIII;

	ALLOC_ARRAY (sp, length, char);
	_hoops_AIGA (_hoops_CSIGS, _hoops_SSIGS, char, sp);
	FREE_ARRAY (_hoops_CSIGS, _hoops_SSIGS, char);
}

local bool _hoops_GGCGS (
	_hoops_IRIPH *				_hoops_GHIPH,
	char alter * alter &	_hoops_RGCGS,
	int alter &				length) {
	char alter *			sp = _hoops_RGCGS;
	char const *			_hoops_AGCGS = sp + length;
#ifndef DISABLE_METAFILE
	char *					_hoops_ASAPR;
	int						_hoops_PGCGS = 0;

	if (!_hoops_RHHGS (_hoops_GHIPH, '"')) return false;
	_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
	_hoops_PCCAR {
		if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) return false;

		if (_hoops_PGCGS && '0' <= *_hoops_ASAPR && *_hoops_ASAPR <= '7') {
			sp--;
			*sp = (*sp * 010)  +  (*_hoops_ASAPR++ - '0');
			sp++;
			if (++_hoops_PGCGS == 3)
				_hoops_PGCGS = 0;
		}
		else if (*_hoops_ASAPR == '\\') {
			++_hoops_ASAPR;
			if (!_hoops_IAHGS (_hoops_GHIPH, _hoops_ASAPR)) {
				if (_hoops_SPIPH (_hoops_GHIPH)) {
					_hoops_GHIPH->message = _hoops_HSIGS;
					HI_Report_File_Error (_hoops_GHIPH);
				}
				return false;
			}

			if (sp == _hoops_AGCGS) {
				int _hoops_SSIGS = length;
				_hoops_ISIGS (_hoops_RGCGS, length);
				sp = _hoops_RGCGS + _hoops_SSIGS;
				_hoops_AGCGS = _hoops_RGCGS + length;
			}

			if (*_hoops_ASAPR == '\n' || *_hoops_ASAPR == '\r') {
				_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
				if (!_hoops_CPHGS (_hoops_GHIPH)) {
					if (_hoops_SPIPH (_hoops_GHIPH)) {
						_hoops_GHIPH->message = _hoops_HSIGS;
						HI_Report_File_Error (_hoops_GHIPH);
					}
					return false;
				}
				_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
			}

			if ('0' <= *_hoops_ASAPR && *_hoops_ASAPR <= '7') {
				*sp++ = (*_hoops_ASAPR++ - '0');
				_hoops_PGCGS = 1;
			}
			else {
				if (*_hoops_ASAPR == 'n')
					*sp++ = '\n';
				else
					*sp++ = *_hoops_ASAPR;
				++_hoops_ASAPR;
				_hoops_PGCGS = 0;
			}
		}
		else if (*_hoops_ASAPR == '\n' || *_hoops_ASAPR == '\r') {
			_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
			if (!_hoops_CPHGS (_hoops_GHIPH)) {
				if (_hoops_SPIPH (_hoops_GHIPH)) {
					_hoops_GHIPH->message = _hoops_HSIGS;
					HI_Report_File_Error (_hoops_GHIPH);
				}
				return false;
			}
			_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
			_hoops_PGCGS = 0;
		}
		else if (*_hoops_ASAPR == '"') {
			++_hoops_ASAPR;
			break;
		}
		else {
			if (sp == _hoops_AGCGS) {
				int _hoops_SSIGS = length;
				_hoops_ISIGS (_hoops_RGCGS, length);
				sp = _hoops_RGCGS + _hoops_SSIGS;
				_hoops_AGCGS = _hoops_RGCGS + length;
			}

			*sp++ = *_hoops_ASAPR++;
			_hoops_PGCGS = 0;
		}
	}

	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;

	if (sp == _hoops_AGCGS) {
		int _hoops_SSIGS = length;
		_hoops_ISIGS (_hoops_RGCGS, length);
		sp = _hoops_RGCGS + _hoops_SSIGS;
		_hoops_AGCGS = _hoops_RGCGS + length;
	}
	*sp++ = '\0';
	if (sp == _hoops_AGCGS) {
		int _hoops_SSIGS = length;
		_hoops_ISIGS (_hoops_RGCGS, length);
		sp = _hoops_RGCGS + _hoops_SSIGS;
		_hoops_AGCGS = _hoops_RGCGS + length;
	}
	*sp = '\0';

	return true;
#else
	return false;
#endif
}



local bool _hoops_HGCGS (
	_hoops_IRIPH *				_hoops_GHIPH,
	char alter * alter &	sp,
	int alter &				length) 
{
	_hoops_GCHGS (_hoops_GHIPH);
	if (_hoops_GHHGS(_hoops_GHIPH, '"')) {
		return _hoops_GGCGS(_hoops_GHIPH, sp, length);
	}
	else
		sp[0] = '\0';	
	return true;
}


local const char _hoops_IGCGS[] = "Latest metafile version is assumed";


local int _hoops_CGCGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH	*			_hoops_GHIPH) {
#ifndef DISABLE_METAFILE
	float			_hoops_SGCGS;
	char			tmp;

	/* _hoops_PPIP _hoops_IRS "_hoops_ICIC" _hoops_CSPP _hoops_IIGR _hoops_GRCGS */
#	define		_hoops_RRCGS(x)		(tmp = (x), _hoops_SHPCR(tmp))

	if (!_hoops_SAHGS (_hoops_GHIPH)) return 0;

	if (*_hoops_GHIPH->_hoops_ASAPR != ';') {
		_hoops_GHIPH->message = "Expected \";;\" when reading metafile version";
		_hoops_GHIPH->_hoops_RGHGA = _hoops_IGCGS;
		_hoops_GHIPH->_hoops_CAIPH = 2;
		HI_Report_File_Error (_hoops_GHIPH);
		return 1;
	}

	++_hoops_GHIPH->_hoops_ASAPR;

	if (!_hoops_SAHGS (_hoops_GHIPH)) return 0;

	if (*_hoops_GHIPH->_hoops_ASAPR++ != ';') {
		_hoops_GHIPH->message = "Expected \";;\" but only found one ';'";
		_hoops_GHIPH->_hoops_RGHGA = _hoops_IGCGS;
		_hoops_GHIPH->_hoops_CAIPH = 2;
		HI_Report_File_Error (_hoops_GHIPH);
		return 1;
	}

	if (!_hoops_GCHGS (_hoops_GHIPH)) return 0;

	if (!(_hoops_SAHGS (_hoops_GHIPH) && _hoops_RRCGS (*_hoops_GHIPH->_hoops_ASAPR++) == 'h' &&
		 _hoops_SAHGS (_hoops_GHIPH) && _hoops_RRCGS (*_hoops_GHIPH->_hoops_ASAPR++) == 'm' &&
		 _hoops_SAHGS (_hoops_GHIPH) && _hoops_RRCGS (*_hoops_GHIPH->_hoops_ASAPR++) == 'f')) {
		_hoops_GHIPH->message =
	  "Could not read metafile version - expected the keyword \"HMF\"";
		_hoops_GHIPH->_hoops_RGHGA = _hoops_IGCGS;
		_hoops_GHIPH->_hoops_CAIPH = 2;
		HI_Report_File_Error (_hoops_GHIPH);
		return 1;
	}

	if (!_hoops_GCHGS (_hoops_GHIPH)) return 0;

	if (!(_hoops_SAHGS (_hoops_GHIPH) && _hoops_RRCGS (*_hoops_GHIPH->_hoops_ASAPR++) == 'v')) {
		_hoops_GHIPH->message =
				"Expected a 'V' when reading metafile version";
				_hoops_GHIPH->_hoops_RGHGA = _hoops_IGCGS;
				_hoops_GHIPH->_hoops_CAIPH = 2;
		HI_Report_File_Error (_hoops_GHIPH);
		return 1;
	}

	if (!_hoops_GCHGS (_hoops_GHIPH)) return 0;

	if (!_hoops_HIHGS (_hoops_RIGC, _hoops_GHIPH, &_hoops_SGCGS)) {
		if (_hoops_GHIPH->_hoops_HHGHP) return 1;

		_hoops_GHIPH->message = "Error reading metafile version number";
		_hoops_GHIPH->_hoops_RGHGA = _hoops_IGCGS;
		_hoops_GHIPH->_hoops_CAIPH = 2;
		HI_Report_File_Error (_hoops_GHIPH);
		if (!_hoops_CHHGS (_hoops_GHIPH, '(')) return 0;
		_hoops_SGCGS = _hoops_PRCCR;
	}

	/* _hoops_CACH _hoops_RPP _hoops_RH _hoops_RGHR _hoops_HRGR _hoops_CPAC _hoops_HSAR _hoops_SR _hoops_CHR */
	/* _hoops_IPCP '0.00001' _hoops_HRGR _hoops_IS _hoops_CRHR _hoops_SIRCP _hoops_HHGS */
	if (_hoops_SGCGS > _hoops_PRCCR + 0.00001f) {
		char			buf[MAX_ERRMSG];

		if ((int)_hoops_SGCGS != (int)_hoops_PRCCR) {
			HE_ERROR2 (HEC_METAFILE, HES_VERSION_MISMATCH,
					Sprintf_N (null,
							 "Version mismatch (major) in reading file '%n' -",
								 &_hoops_GHIPH->filename),
					  Sprintf_D (buf,
			 "This Hoops does not know how to read a version '%d.xx' metafile",
								 (int)_hoops_SGCGS));
			return 0;
		}
		else {
			local		const float		_hoops_GCPGI = _hoops_PRCCR;

			_hoops_ARGIP (HEC_METAFILE, HES_VERSION_MISMATCH,
					Sprintf_N (null,
							 "Version mismatch (minor) in reading file '%n' -",
									&_hoops_GHIPH->filename),
						Sprintf_FF (buf,
		 "'new' metafile (MF ver %.2f) being read by an 'old' Hoops (MF ver %.2f) -",
									_hoops_SGCGS, _hoops_GCPGI),
			  "May trip over unrecognized new data types, if any are present");
		}
	}

	if (!_hoops_GCHGS (_hoops_GHIPH)) return 0;

	if (!(_hoops_SAHGS (_hoops_GHIPH) && _hoops_RRCGS (*_hoops_GHIPH->_hoops_ASAPR++) == 't' &&
		 _hoops_SAHGS (_hoops_GHIPH) && _hoops_RRCGS (*_hoops_GHIPH->_hoops_ASAPR++) == 'e' &&
		 _hoops_SAHGS (_hoops_GHIPH) && _hoops_RRCGS (*_hoops_GHIPH->_hoops_ASAPR++) == 'x' &&
		 _hoops_SAHGS (_hoops_GHIPH) && _hoops_RRCGS (*_hoops_GHIPH->_hoops_ASAPR++) == 't')) {
		_hoops_GHIPH->message = "Unknown metafile type -- \"TEXT\" is assumed";
		HI_Report_File_Error (_hoops_GHIPH);
		return 1;
	}

	return (int)(_hoops_SGCGS * 100.0f + 0.1f);
#else
	return 0;
#endif
}



GLOBAL_FUNCTION void HI_Report_File_Error (
	_hoops_IRIPH	*_hoops_GHIPH) {
#ifndef DISABLE_METAFILE
		char			buf[1000], *_hoops_ASAPR = buf;
		char			*_hoops_PSAPR = buf+_hoops_GGAPR(buf);

		if (_hoops_GHIPH->_hoops_CAIPH == 0) {
			_hoops_GHIPH->_hoops_CAIPH = 1;
			return;
		}
		if (_hoops_GHIPH->_hoops_PPIPH)
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "Error writing file '%n'", (void *)&_hoops_GHIPH->filename);
		else _hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR,
			"Error reading file '%n'", (void *)&_hoops_GHIPH->filename);
		if (_hoops_ASAPR != null)
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, " at line %d", (void *)&_hoops_GHIPH->_hoops_APIPH);
		if (_hoops_ASAPR != null && _hoops_ASAPR != _hoops_PSAPR) *_hoops_ASAPR = '\0';
		switch (_hoops_GHIPH->_hoops_CAIPH) {
		case 1:
			HE_ERROR2 (HEC_FILE_IO, HES_ERROR_WRITING_FILE,
				buf, _hoops_GHIPH->message);
			break;
		case 2:
			HE_ERROR3 (HEC_FILE_IO, HES_ERROR_WRITING_FILE,
				buf, _hoops_GHIPH->message, _hoops_GHIPH->_hoops_RGHGA);
			break;
		default:
		case 0:
			HE_ERROR (HEC_FILE_IO, HES_ERROR_WRITING_FILE,
				buf);
			break;
		}
		_hoops_GHIPH->_hoops_CAIPH = 1;
#endif
}


GLOBAL_FUNCTION void HI_Report_File_Error_With_Names (
	_hoops_IRIPH	*_hoops_GHIPH,
	_hoops_HCRPR			*_hoops_CCCIH,
	_hoops_HCRPR			*_hoops_SCCIH) 
{
#ifndef DISABLE_METAFILE

	if (_hoops_GHIPH->_hoops_CAIPH >= 2)
		_hoops_GHIPH->_hoops_RGHGA = _hoops_SCCIH->text;
	if (_hoops_GHIPH->_hoops_CAIPH >= 1)
		_hoops_GHIPH->message = _hoops_CCCIH->text;

	HI_Report_File_Error (_hoops_GHIPH);

	_hoops_GHIPH->message = null;
	_hoops_GHIPH->_hoops_RGHGA = null;

	_hoops_RGAIR (*_hoops_SCCIH);
	_hoops_RGAIR (*_hoops_CCCIH);
#endif
}




local bool _hoops_SHHHC (
	_hoops_IRIPH *		_hoops_GHIPH,
	char const *	_hoops_RPPA) 
{
	char			temp[MAX_ERRMSG];

	_hoops_GHIPH->message = Sprintf_S (temp, "\"%s\" is not a known metafile command", _hoops_RPPA);
	HI_Report_File_Error (_hoops_GHIPH);
	return false;
}



/* _hoops_ARCGS
 * _hoops_RGR _hoops_API _hoops_HSSIA _hoops_PPGS _hoops_IH _hoops_PGAP _hoops_SCH _hoops_HRGR _hoops_RH 
 * _hoops_RCPH _hoops_API'_hoops_GRI _hoops_CSSAR _hoops_IS _hoops_CIH 
 */
local void _hoops_PRCGS (
	_hoops_IRIPH		  *_hoops_GHIPH,
	_hoops_GAIII  *_hoops_HCHGS,
	int					  *knot_count,
	float				  **knots,
	int					  *weight_count,
	float				  **weights) {
	int i;
	char const *t, *s;

	/* _hoops_SGHSA _hoops_PPR _hoops_HHRP _hoops_CHR _hoops_IRAP _hoops_HCCPR _hoops_GSGI _hoops_IS _hoops_SHH _hoops_IAII */
	*knots = *weights = null;
	*knot_count = *weight_count = 0;

	for (i = 0; i < 2; i++)
	{
		if (_hoops_CPIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
		{
			/* _hoops_HRCGS _hoops_RH _hoops_RPPCR.	_hoops_PSSRR _hoops_RH _hoops_RPPCR _hoops_ACSRR "_hoops_SGHSA" _hoops_PPR "_hoops_HHRP" */
			t = "knots";
			s = _hoops_HCHGS->_hoops_RCIII;
			if (_hoops_AGGR(t,s)) {
				*knot_count = _hoops_HCHGS->_hoops_GIIII;
				_hoops_APRGA(_hoops_HCHGS->_hoops_RIIII, *knot_count, float, *knots);
			}

			t = "weights";
			s = _hoops_HCHGS->_hoops_RCIII;
			if (_hoops_AGGR(t,s)) {
				*weight_count = _hoops_HCHGS->_hoops_GIIII;
				_hoops_APRGA(_hoops_HCHGS->_hoops_RIIII, *weight_count, float, *weights);
			}
		}
	}
} /* _hoops_RSGR _hoops_API _hoops_ARCGS */

/* _hoops_ARCGS
 * _hoops_RGR _hoops_API _hoops_HSSIA _hoops_PPGS _hoops_IH _hoops_PGAP _hoops_SCH _hoops_HRGR _hoops_RH 
 * _hoops_RCPH _hoops_API'_hoops_GRI _hoops_CSSAR _hoops_IS _hoops_CIH 
 */
local void _hoops_IRCGS (
	_hoops_IRIPH		  *_hoops_GHIPH,
	_hoops_GAIII  *_hoops_HCHGS,
	int					  *_hoops_RSPIR,
	float				  **u_knots,
	int					  *_hoops_ASPIR,
	float				  **v_knots,
	int					  *weight_count,
	float				  **weights) {
	bool _hoops_HPAHA;
	char const *t, *s;

	/* _hoops_SGHSA _hoops_PPR _hoops_HHRP _hoops_CHR _hoops_IRAP _hoops_HCCPR _hoops_GSGI _hoops_IS _hoops_SHH _hoops_IAII */
	*u_knots = *v_knots = *weights = null;
	*_hoops_RSPIR = *_hoops_ASPIR = *weight_count = 0;

	while (_hoops_CPIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
	{
		/* _hoops_HRCGS _hoops_RH _hoops_RPPCR.	_hoops_PSSRR _hoops_RH _hoops_RPPCR _hoops_ACSRR "_hoops_CRCGS", "_hoops_SRCGS" _hoops_PPR "_hoops_HHRP" */
		_hoops_HPAHA = true;
		t = "u_knots";
		s = _hoops_HCHGS->_hoops_RCIII;
		do if (*s++ != *t++) _hoops_HPAHA = false;
		_hoops_RGGA (*t == '\0');
		if (_hoops_HPAHA)
		{
			*_hoops_RSPIR = _hoops_HCHGS->_hoops_GIIII;
			_hoops_APRGA(_hoops_HCHGS->_hoops_RIIII, *_hoops_RSPIR, float, *u_knots);
		}

		_hoops_HPAHA = true;
		t = "v_knots";
		s = _hoops_HCHGS->_hoops_RCIII;
		do if (*s++ != *t++) _hoops_HPAHA = false;
		_hoops_RGGA (*t == '\0');
		if (_hoops_HPAHA)
		{
			*_hoops_ASPIR = _hoops_HCHGS->_hoops_GIIII;
			_hoops_APRGA(_hoops_HCHGS->_hoops_RIIII, *_hoops_ASPIR, float, *v_knots);
		}

		_hoops_HPAHA = true;
		t = "weights";
		s = _hoops_HCHGS->_hoops_RCIII;
		do if (*s++ != *t++) _hoops_HPAHA = false;
		_hoops_RGGA (*t == '\0');
		if (_hoops_HPAHA)
		{
			*weight_count = _hoops_HCHGS->_hoops_GIIII;
			_hoops_APRGA(_hoops_HCHGS->_hoops_RIIII, *weight_count, float, *weights);
		}
	}
} /* _hoops_RSGR _hoops_API _hoops_ARCGS */

#endif


/*
*	_hoops_GCAAA _hoops_IHPR _hoops_RPP _hoops_PHPPR _hoops_HRGR _hoops_AIAH _hoops_PAPR.  "_hoops_GACGS" _hoops_GAAAI
*	_hoops_RH _hoops_RACGS _hoops_AACGS _hoops_IIGR _hoops_RH _hoops_PHPPR _hoops_RSIRR
*/
local bool _hoops_PACGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	char *					alias,
	bool *					_hoops_HACGS) {
#ifndef DISABLE_METAFILE
		_hoops_RSAPR	*pt;
		_hoops_SRPPR				**_hoops_GAPPR;

		*_hoops_HACGS = true;

		if (*alias != '?') {
			_hoops_GHIPH->message = "Alias name must begin with a ?";
			HI_Report_File_Error (_hoops_GHIPH);
			*_hoops_HACGS = false;
			return false;
		}

		if ((pt = HI_Parse_Path (_hoops_RIGC, alias, false)) == null) {
			/* _hoops_RIHH - _hoops_AHCI _hoops_RSIRR (_hoops_AIAH _hoops_CRPPR) */
			_hoops_GHIPH->message = "Alias name syntax error";
			HI_Report_File_Error (_hoops_GHIPH);
			*_hoops_HACGS = false;
			return false;
		}

		if (pt->next != null || pt->type != _hoops_RGPPR) {
			_hoops_GHIPH->message =
				Sprintf_S (null, "'%s' is not a legal alias name", alias);
			HI_Report_File_Error (_hoops_GHIPH);
			HI_Free_Path (pt);
			*_hoops_HACGS = false;
			return false;
		}

		_hoops_GAPPR = HI_Look_Up_Alias (_hoops_RIGC, pt->_hoops_AGPPR.text, pt->_hoops_AGPPR.length);
		HI_Free_Path (pt);
		return (*_hoops_GAPPR != null);
#else
		return false;
#endif
}


local bool _hoops_IACGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_IRIPH *				_hoops_GHIPH,
	int						size,
	unsigned char alter *	_hoops_PAGR)
{
	int i, _hoops_HAGR;

	if (!_hoops_RHHGS (_hoops_GHIPH, '(')) 
		return false;
	for (i = 0 ; i < size ; i++) {
		if (!_hoops_GCHGS (_hoops_GHIPH))
			return false;
		if (!_hoops_AIHGS (_hoops_RIGC, _hoops_GHIPH, &_hoops_HAGR))
			return false;
		if (!_hoops_GCHGS (_hoops_GHIPH))
			return false;
		_hoops_PAGR[i] = (unsigned char)_hoops_HAGR;
	}
	if (!_hoops_RHHGS (_hoops_GHIPH, ')')) 
		return false;
	return true;
}



local bool _hoops_CACGS (
	_hoops_IRIPH *				_hoops_GHIPH,
	char const *			_hoops_CSRPR,
	_hoops_GAIII *	_hoops_HCHGS) {
#ifndef DISABLE_METAFILE

	switch (*_hoops_CSRPR) {
		case 'a': {
			if (_hoops_AGGR (_hoops_CSRPR, "alias")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII)) return false;

				if (BIT (_hoops_HCHGS->_hoops_PAIII, _hoops_RCHAP)) {
					bool		_hoops_HACGS;

					if (_hoops_PACGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, &_hoops_HACGS)) {
						PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
						HC_UnDefine_Alias (_hoops_HCHGS->_hoops_RCIII);
						POPNAME(_hoops_HCHGS->_hoops_RIGC);
					}

					if (_hoops_HACGS) {
						PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
						HC_Define_Alias (_hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_HCIII);
						POPNAME(_hoops_HCHGS->_hoops_RIGC);
					}
				}
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "append_modelling_matrix")) {
				if (!_hoops_IHIGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->a0[0][0]))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Append_Modelling_Matrix (&_hoops_HCHGS->a0[0][0]);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "area_light")) {
				if (!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Area_Light (_hoops_HCHGS->_hoops_GPIII, _hoops_HCHGS->_hoops_RPIII, _hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'b': {
			if (_hoops_AGGR (_hoops_CSRPR, "bounding_cuboid")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Bounding_Cuboid (&_hoops_HCHGS->_hoops_AGCII, &_hoops_HCHGS->_hoops_AIGCR);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "bounding_sphere")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Bounding_Sphere (&_hoops_HCHGS->_hoops_AGCII, _hoops_HCHGS->_hoops_AIPCP);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'c': {
			if (_hoops_AGGR (_hoops_CSRPR, "callback")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Callback (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "camera")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_PIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Camera (&_hoops_HCHGS->_hoops_AGCII, &_hoops_HCHGS->_hoops_AIGCR, (Vector const *)&_hoops_HCHGS->_hoops_PIGCR, _hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "camera_by_volume")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_CGHGR))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Camera_By_Volume (_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_CGHGR);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "camera_field")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Camera_Field (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "camera_near_limit")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Camera_Near_Limit (_hoops_HCHGS->_hoops_AIPCP);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "camera_position")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Camera_Position (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "camera_projection")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Camera_Projection (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "camera_target")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Camera_Target (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "camera_up_vector")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Camera_Up_Vector (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "center")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Circular_Center (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "character_attribute")) {
				if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				HC_MSet_Character_Attributes(_hoops_HCHGS->_hoops_HAIII, _hoops_HCHGS->_hoops_SSIII, 1, _hoops_HCHGS->_hoops_HCIII);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "circle")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_PIGCR))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Circle (&_hoops_HCHGS->_hoops_AGCII, &_hoops_HCHGS->_hoops_AIGCR, &_hoops_HCHGS->_hoops_PIGCR);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "circular_arc")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_PIGCR))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Circular_Arc (&_hoops_HCHGS->_hoops_AGCII, &_hoops_HCHGS->_hoops_AIGCR, &_hoops_HCHGS->_hoops_PIGCR);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "circular_chord")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_PIGCR))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Circular_Chord (&_hoops_HCHGS->_hoops_AGCII, &_hoops_HCHGS->_hoops_AIGCR, &_hoops_HCHGS->_hoops_PIGCR);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "circular_wedge")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_PIGCR))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Circular_Wedge (&_hoops_HCHGS->_hoops_AGCII, &_hoops_HCHGS->_hoops_AIGCR, &_hoops_HCHGS->_hoops_PIGCR);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "clip_region")) {
				if (!_hoops_SRIGS (_hoops_GHIPH, _hoops_HCHGS, 0) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
#if 0
				/* _hoops_CGPR _hoops_SR _hoops_RGHH _hoops_SIRAR _hoops_HSPH */
				HC_Set_Clip_Region (_hoops_HCHGS->_hoops_HPIII,
									_hoops_HCHGS->_hoops_IPIII,
									_hoops_HCHGS->_hoops_RPIII,
									_hoops_HCHGS->_hoops_HCIII);
#else
				/* _hoops_HIH _hoops_IH _hoops_HA, _hoops_RGAR 1 _hoops_HAPR, _hoops_ICGSI _hoops_SGCS... */
				HC_Set_Polygonal_Clip_Region (_hoops_HCHGS->_hoops_IPIII[0],
											_hoops_HCHGS->_hoops_RPIII,
											_hoops_HCHGS->_hoops_HCIII);
#endif
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "close")) {
				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Close_Segment ();
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "conditions")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Conditions (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "conditional_action")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Conditional_Action (_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "conditional_include")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Conditional_Include (_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "conditional_style")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Conditional_Style (_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "color")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Color (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "color_by_findex")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Color_By_FIndex (_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_AIPCP);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "color_by_index")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Color_By_Index (_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_SSIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "color_by_value")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				if (_hoops_IGGPA (_hoops_HCHGS->_hoops_HCIII, "rgba")) {
					if (!_hoops_GCHGS (_hoops_GHIPH) ||
						!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_CGHGR))
						return false;

					Key		key = _hoops_AIRIR (_hoops_HCHGS->_hoops_RIGC->open_list->info.geometry._hoops_IGRPR);
					int		offset = _hoops_HCHGS->_hoops_RIGC->open_list->info.geometry.offset;
					RGBA	_hoops_PIHR(_hoops_HCHGS->_hoops_AIPCP,_hoops_HCHGS->f1,_hoops_HCHGS->f2,_hoops_HCHGS->_hoops_CGHGR);

					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_MSet_Vertex_Colors_By_Value4 (key, "vertex", offset, "rgba", 1, &_hoops_PIHR);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
				else {
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_Set_Color_By_Value (_hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "color_map")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

#ifndef DISABLE_COLOR_MAPS
				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Color_Map (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
#endif
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "color_map_by_value")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
					return false;

#ifndef DISABLE_COLOR_MAPS
				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Color_Map_By_Value (_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_GPIII, (RGB const *)_hoops_HCHGS->_hoops_RPIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
#endif
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "color_name")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_ACIII, _hoops_HCHGS->_hoops_SCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_PCIII, _hoops_HCHGS->_hoops_GSIII)) return false;

				if (BIT (_hoops_HCHGS->_hoops_PAIII, _hoops_ACHAP)) {
					HI_UnDefine_Colors (_hoops_HCHGS->_hoops_RIGC, _hoops_HCHGS->_hoops_HCIII);
					HI_UnDefine_Colors (_hoops_HCHGS->_hoops_RIGC, _hoops_HCHGS->_hoops_RCIII);
					HI_UnDefine_Colors (_hoops_HCHGS->_hoops_RIGC, _hoops_HCHGS->_hoops_ACIII);
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_Define_Color_Name (_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_ACIII, _hoops_HCHGS->_hoops_PCIII);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "compressed_image")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH))
					return false;

				int size;
				if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->width) || 
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->height) || 
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &size) || 
					!_hoops_GCHGS (_hoops_GHIPH))
					return false;

				unsigned char *_hoops_SACGS;
				ALLOC_ARRAY (_hoops_SACGS, size, unsigned char);
				if (!_hoops_IACGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, size, _hoops_SACGS)) {
					FREE_ARRAY (_hoops_SACGS, size, unsigned char);
					return false;
				}
				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Compressed_Image(_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->width, _hoops_HCHGS->height, size, _hoops_SACGS);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
				FREE_ARRAY (_hoops_SACGS, size, unsigned char);
				_hoops_SACGS = null;
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "cutting_plane")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_CGHGR))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Cutting_Plane (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_CGHGR);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "cutting_section")) {
				if (!_hoops_CRIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Cutting_Section (_hoops_HCHGS->_hoops_HIIII, _hoops_HCHGS->_hoops_IIIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "cylinder")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII,
									_hoops_HCHGS->_hoops_CCIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Cylinder (&_hoops_HCHGS->_hoops_AGCII, &_hoops_HCHGS->_hoops_AIGCR, _hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->_hoops_RCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'd': {
			if (_hoops_AGGR (_hoops_CSRPR, "define_color")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_ACIII, _hoops_HCHGS->_hoops_SCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_PCIII, _hoops_HCHGS->_hoops_GSIII)) return false;

				if (BIT (_hoops_HCHGS->_hoops_PAIII, _hoops_ACHAP)) {
					HI_UnDefine_Colors (_hoops_HCHGS->_hoops_RIGC, _hoops_HCHGS->_hoops_HCIII);
					HI_UnDefine_Colors (_hoops_HCHGS->_hoops_RIGC, _hoops_HCHGS->_hoops_RCIII);
					HI_UnDefine_Colors (_hoops_HCHGS->_hoops_RIGC, _hoops_HCHGS->_hoops_ACIII);
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_Define_Color_Name (_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_ACIII, _hoops_HCHGS->_hoops_PCIII);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "distant_light")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_HGCGS(_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Distant_Light (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				if (_hoops_HCHGS->_hoops_RCIII[0] != '\0')
					HC_Set_Geometry_Options(_hoops_HCHGS->new_key, _hoops_HCHGS->_hoops_RCIII); /* _hoops_IAS._hoops_ISHI. "_hoops_SARA _hoops_CSCHR" */
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "dolly_camera")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Dolly_Camera (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "driver_options")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Driver_Options (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'e': {
			if (_hoops_AGGR (_hoops_CSRPR, "edge")) {
				if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->i1)) return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Open_Edge (_hoops_HCHGS->_hoops_SSIII, _hoops_HCHGS->i1);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);

				_hoops_GGIII	*_hoops_GPCGS;

				ALLOC (_hoops_GPCGS, _hoops_GGIII);
				_hoops_GPCGS->next = _hoops_HCHGS->_hoops_RAIII;
				_hoops_GPCGS->type = _hoops_SGIII;
				_hoops_HCHGS->_hoops_RAIII = _hoops_GPCGS;
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "edge_pattern")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Edge_Pattern (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "edge_pattern_explicit")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Edge_Pattern_Explicit (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "edge_weight")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Edge_Weight (_hoops_HCHGS->_hoops_AIPCP);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "ellipse")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_PIGCR))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Ellipse (&_hoops_HCHGS->_hoops_AGCII, &_hoops_HCHGS->_hoops_AIGCR, &_hoops_HCHGS->_hoops_PIGCR);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "elliptical_arc")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_PIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Elliptical_Arc (&_hoops_HCHGS->_hoops_AGCII, &_hoops_HCHGS->_hoops_AIGCR, &_hoops_HCHGS->_hoops_PIGCR, _hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'f': {
			if (_hoops_AGGR (_hoops_CSRPR, "face")) {
				if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII))
					return false;

				int			_hoops_AICIP = HOOPS_WORLD->system_flags;

				if (_hoops_HCHGS->version < 125)
					HOOPS_WORLD->system_flags |= _hoops_GGSPP;
				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Open_Face (_hoops_HCHGS->_hoops_SSIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
				HOOPS_WORLD->system_flags = _hoops_AICIP;

				_hoops_GGIII	*_hoops_GPCGS;

				ALLOC (_hoops_GPCGS, _hoops_GGIII);
				_hoops_GPCGS->next = _hoops_HCHGS->_hoops_RAIII;
				_hoops_GPCGS->type = _hoops_CGIII;
				_hoops_HCHGS->_hoops_RAIII = _hoops_GPCGS;
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "face_pattern")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Face_Pattern (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "font")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GAIGS (_hoops_GHIPH, _hoops_HCHGS, 0)) return false;

				if (BIT (_hoops_HCHGS->_hoops_PAIII, _hoops_HCHAP)) {
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_Define_Font (_hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_HHIII, _hoops_HCHGS->_hoops_IHIII);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "front")) {
				_hoops_GGIII	*_hoops_GPCGS;

				ALLOC (_hoops_GPCGS, _hoops_GGIII);
				_hoops_GPCGS->next = _hoops_HCHGS->_hoops_RAIII;
				_hoops_GPCGS->type = _hoops_PGIII;
				_hoops_HCHGS->_hoops_RAIII = _hoops_GPCGS;
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'g': {
			if (_hoops_AGGR (_hoops_CSRPR, "geometry")) {
				_hoops_GGIII	*_hoops_GPCGS;

				ALLOC (_hoops_GPCGS, _hoops_GGIII);
				_hoops_GPCGS->next = _hoops_HCHGS->_hoops_RAIII;
				_hoops_GPCGS->type = _hoops_IGIII;
				_hoops_HCHGS->_hoops_RAIII = _hoops_GPCGS;
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "geometry_options")) {
				if (!_hoops_GCHGS(_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Geometry_Options(_hoops_HCHGS->_hoops_HAIII, _hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "grid")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_PIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->i1))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Grid (_hoops_HCHGS->_hoops_HCIII, &_hoops_HCHGS->_hoops_AGCII, &_hoops_HCHGS->_hoops_AIGCR, &_hoops_HCHGS->_hoops_PIGCR, _hoops_HCHGS->_hoops_SSIII, _hoops_HCHGS->i1);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "glyph_definition")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_SRIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
					return false;

				char *		_hoops_RPCGS;
				ALLOC_ARRAY(_hoops_RPCGS, _hoops_HCHGS->_hoops_HPIII, char);

				for (int i=0;i<_hoops_HCHGS->_hoops_HPIII;i++)
					_hoops_RPCGS[i]=(char)_hoops_HCHGS->_hoops_IPIII[i];

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Define_Glyph(_hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_HPIII, _hoops_RPCGS);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);

				FREE_ARRAY(_hoops_RPCGS, _hoops_HCHGS->_hoops_HPIII, char);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'h': {
			if (_hoops_AGGR (_hoops_CSRPR, "handedness")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Handedness (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "heuristics")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Heuristics (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'i': {
			if (_hoops_AGGR (_hoops_CSRPR, "image")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_CIIGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, &_hoops_HCHGS->width, &_hoops_HCHGS->height, &_hoops_HCHGS->_hoops_PGCII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HI_Insert_Image_By_Row (_hoops_HCHGS->_hoops_RIGC, _hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->width, _hoops_HCHGS->height, _hoops_HCHGS->_hoops_PGCII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "include_segment")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				if (_hoops_HCHGS->_hoops_ISHAP.length == 0 ||
					_hoops_HCHGS->_hoops_HCIII[0] != '/') {
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					_hoops_HCHGS->new_key = HC_Include_Segment (_hoops_HCHGS->_hoops_HCIII);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
				else {
					int		required = _hoops_HCHGS->_hoops_ISHAP.length + _hoops_SSGR (_hoops_HCHGS->_hoops_HCIII) + 1;

					if (required > _hoops_HCHGS->_hoops_ASIII) {
						FREE_ARRAY (_hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII, char);
						while (required > _hoops_HCHGS->_hoops_ASIII && required < _hoops_CRIII)
							_hoops_HCHGS->_hoops_ASIII *= 2;
						while (required > _hoops_HCHGS->_hoops_ASIII)
							_hoops_HCHGS->_hoops_ASIII += _hoops_CRIII;
						ALLOC_ARRAY (_hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII, char);
					}
					_hoops_AAHR(_hoops_HCHGS->_hoops_ISHAP.text,_hoops_HCHGS->_hoops_ICIII);
					if (_hoops_HCHGS->_hoops_HCIII[1] != '\0')
					_hoops_HPRPR(_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_ICIII); 
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					_hoops_HCHGS->new_key = HC_Include_Segment (_hoops_HCHGS->_hoops_ICIII);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "ink")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Insert_Ink (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "infinite_line")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_CGHGR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SGHGR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_RGCII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Infinite_Line (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_CGHGR, _hoops_HCHGS->_hoops_SGHGR, _hoops_HCHGS->_hoops_RGCII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "infinite_ray")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_CGHGR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SGHGR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_RGCII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Infinite_Ray (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_CGHGR, _hoops_HCHGS->_hoops_SGHGR, _hoops_HCHGS->_hoops_RGCII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'l': {
			if (_hoops_AGGR (_hoops_CSRPR, "line")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_CGHGR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SGHGR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_RGCII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Line (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_CGHGR, _hoops_HCHGS->_hoops_SGHGR, _hoops_HCHGS->_hoops_RGCII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "line_pattern")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Line_Pattern (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "line_pattern_explicit")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Line_Pattern_Explicit (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "line_style_definition")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Define_Line_Style(_hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "line_weight")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Line_Weight (_hoops_HCHGS->_hoops_AIPCP);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "local_light")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_HGCGS(_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Local_Light (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				if (_hoops_HCHGS->_hoops_RCIII[0] != '\0')
					HC_Set_Geometry_Options(_hoops_HCHGS->new_key, _hoops_HCHGS->_hoops_RCIII); /* _hoops_IAS._hoops_ISHI. "_hoops_SARA _hoops_CSCHR" */
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "lod")) {
				if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Open_LOD (_hoops_HCHGS->_hoops_SSIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);

				_hoops_GGIII	*_hoops_GPCGS;

				ALLOC (_hoops_GPCGS, _hoops_GGIII);
				_hoops_GPCGS->next = _hoops_HCHGS->_hoops_RAIII;
				_hoops_GPCGS->type = _hoops_RRIII;
				_hoops_HCHGS->_hoops_RAIII = _hoops_GPCGS;
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'm': {
			if (_hoops_AGGR (_hoops_CSRPR, "marker")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Marker (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "marker_size")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Marker_Size (_hoops_HCHGS->_hoops_AIPCP);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "marker_symbol")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Marker_Symbol (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "mesh")) {
				if (!_hoops_RHIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Mesh (_hoops_HCHGS->_hoops_SIIII, _hoops_HCHGS->_hoops_GCIII, _hoops_HCHGS->_hoops_RPIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "metafile")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Read_Metafile ("", ".", _hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "modelling_matrix")) {
				if (!_hoops_IHIGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->a0[0][0]))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Modelling_Matrix (&_hoops_HCHGS->a0[0][0]);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "modify_color_map")) {
				if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

#ifndef DISABLE_COLOR_MAPS
				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Modify_Color_Map (_hoops_HCHGS->_hoops_SSIII, _hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
#endif
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "modify_color_map_by_value")) {
				if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
					return false;

#ifndef DISABLE_COLOR_MAPS
				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Modify_Color_Map_By_Value (_hoops_HCHGS->_hoops_SSIII, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_GPIII, (RGB const *)_hoops_HCHGS->_hoops_RPIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
#endif
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'n': {
			if (_hoops_AGGR (_hoops_CSRPR, "named_style")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII)) 
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Named_Style_Segment(_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "named_style_definition")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII)) 
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Define_Named_Style(_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_ICIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "normal")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Normal (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "nurbs_curve")) {
				float *knots = null, *weights = null;
				int _hoops_HGA, control_point_count;
				int knot_count, weight_count;

				if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII) ||			/* _hoops_AGR */
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->i1) ||			/* _hoops_CPSGP */
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||		/* _hoops_APCGS */
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||		/* _hoops_PPCGS */
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0)		/* _hoops_HPCGS */
				)
					return false;

				/* _hoops_RPP _hoops_IIH _hoops_CHR _hoops_HHRP _hoops_PPR _hoops_SGHSA, _hoops_IRIGR _hoops_CAPR */
				_hoops_PRCGS (_hoops_GHIPH, _hoops_HCHGS, &knot_count, &knots, &weight_count, &weights);

				_hoops_HGA = _hoops_HCHGS->_hoops_SSIII;
				control_point_count = _hoops_HCHGS->i1;
				if (knot_count > 0 && knot_count != (control_point_count + _hoops_HGA + 1)) {
						_hoops_GHIPH->message = "incorrect NURBS curve knot vector length";
					HI_Report_File_Error (_hoops_GHIPH);
					return false;
				}
				if (weight_count > 0 && weight_count != control_point_count) {
					_hoops_GHIPH->message = "incorrect NURBS curve weight vector length";
					HI_Report_File_Error (_hoops_GHIPH);
					return false;
				}

				/* (_hoops_IPCGS->_hoops_CPCGS) _hoops_CGH _hoops_SHR _hoops_SASPR _hoops_CPSGP */
				if (_hoops_HCHGS->_hoops_GPIII != control_point_count) {
					_hoops_GHIPH->message = "incorrect NURBS curve point count";
					HI_Report_File_Error (_hoops_GHIPH);
					return false;
				}

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_NURBS_Curve (_hoops_HGA, control_point_count, _hoops_HCHGS->_hoops_RPIII,
													  weights, knots, _hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);

				if (knots != null)
					FREE_ARRAY (knots, knot_count, float);
				if (weights != null)
					FREE_ARRAY (weights, weight_count, float);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "nurbs_surface")) {
				float *u_knots, *v_knots, *weights;
				int _hoops_RSPIR, _hoops_ASPIR, weight_count;

				u_knots = v_knots = weights = null;
				if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII) ||			/* _hoops_ISSCC */
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->i1) ||			/* _hoops_CSSCC */
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->i2) ||			/* _hoops_IGAA */
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SAPH) ||			/* _hoops_APPS */
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0)		/* _hoops_HPCGS */
				)
					return false;

				/* _hoops_RPP _hoops_IIH _hoops_CHR _hoops_HHRP _hoops_PPR _hoops_SGHSA, _hoops_IRIGR _hoops_CAPR */
				_hoops_IRCGS (_hoops_GHIPH, _hoops_HCHGS, 
											&_hoops_RSPIR, &u_knots, 
											&_hoops_ASPIR, &v_knots, 
											&weight_count, &weights);

				/* (_hoops_IPCGS->_hoops_CPCGS) _hoops_CGH _hoops_SHR _hoops_SASPR (_hoops_IPCGS->_hoops_PRAHA) */
				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_NURBS_Surface (_hoops_HCHGS->_hoops_SSIII, _hoops_HCHGS->i1, _hoops_HCHGS->i2, _hoops_HCHGS->_hoops_SAPH, 
														_hoops_HCHGS->_hoops_RPIII, weights, u_knots, v_knots);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);

				if (weights != null)
					FREE_ARRAY (weights, weight_count, float);
				if (u_knots != null)
					FREE_ARRAY (u_knots, _hoops_RSPIR, float);
				if (v_knots != null)
					FREE_ARRAY (v_knots, _hoops_ASPIR, float);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'o': {
			if (_hoops_AGGR (_hoops_CSRPR, "orbit_camera")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Orbit_Camera (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'p': {
			if (_hoops_AGGR (_hoops_CSRPR, "pan_camera")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Pan_Camera (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "parameter")) {
				if (!_hoops_RAIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Parameter (_hoops_HCHGS->_hoops_GIIII, _hoops_HCHGS->_hoops_RIIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "polycylinder")) {
				if (!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_RAIGS (_hoops_GHIPH, _hoops_HCHGS, 0) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_PolyCylinder (_hoops_HCHGS->_hoops_GPIII, _hoops_HCHGS->_hoops_RPIII,
														_hoops_HCHGS->_hoops_GIIII, _hoops_HCHGS->_hoops_RIIII,
														_hoops_HCHGS->_hoops_RCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "polygon")) {
				if (!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Polygon (_hoops_HCHGS->_hoops_GPIII, _hoops_HCHGS->_hoops_RPIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "polyline")) {
				if (!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
				return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Polyline (_hoops_HCHGS->_hoops_GPIII, _hoops_HCHGS->_hoops_RPIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "polyline_segments")) {
				if (!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Polyline (-_hoops_HCHGS->_hoops_GPIII, _hoops_HCHGS->_hoops_RPIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "priority")) {
				_hoops_GGIII	*_hoops_GPCGS;

				ALLOC (_hoops_GPCGS, _hoops_GGIII);
				_hoops_GPCGS->next = _hoops_HCHGS->_hoops_RAIII;
				_hoops_GPCGS->type = _hoops_PRIII;
				_hoops_HCHGS->_hoops_RAIII = _hoops_GPCGS;
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'r': {
			if (_hoops_AGGR (_hoops_CSRPR, "regions")) {
				if (!_hoops_SRIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_MSet_Face_Regions (_hoops_AIRIR (_hoops_HCHGS->_hoops_RIGC->open_list->info.geometry._hoops_IGRPR),
									  0, _hoops_HCHGS->_hoops_HPIII, _hoops_HCHGS->_hoops_IPIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "rename_segment")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				char * 		_hoops_PHGSA = _hoops_HCHGS->_hoops_RCIII;
				char * 		_hoops_HHGSA = _hoops_HCHGS->_hoops_HCIII;

				if (_hoops_HCHGS->_hoops_ISHAP.length > 0) {
					if (_hoops_PHGSA[0] == '/') {
							int		required = _hoops_HCHGS->_hoops_ISHAP.length + _hoops_SSGR (_hoops_HCHGS->_hoops_RCIII) + 1;

							if (required > _hoops_HCHGS->_hoops_SCIII) {
								FREE_ARRAY (_hoops_HCHGS->_hoops_ACIII, _hoops_HCHGS->_hoops_SCIII, char);
								while (required > _hoops_HCHGS->_hoops_SCIII && required < _hoops_CRIII)
									_hoops_HCHGS->_hoops_SCIII *= 2;
								while (required > _hoops_HCHGS->_hoops_SCIII)
									_hoops_HCHGS->_hoops_SCIII += _hoops_CRIII;
								ALLOC_ARRAY (_hoops_HCHGS->_hoops_ACIII, _hoops_HCHGS->_hoops_SCIII, char);
							}
						_hoops_AAHR(_hoops_HCHGS->_hoops_ISHAP.text,_hoops_HCHGS->_hoops_ACIII);
						if (_hoops_HCHGS->_hoops_RCIII[1] != '\0')
							_hoops_HPRPR(_hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_ACIII); 
						_hoops_PHGSA = _hoops_HCHGS->_hoops_ACIII;		
					}

					if (_hoops_HHGSA[0] == '/') {
							int		required = _hoops_HCHGS->_hoops_ISHAP.length + _hoops_SSGR (_hoops_HCHGS->_hoops_HCIII) + 1;

							if (required > _hoops_HCHGS->_hoops_ASIII) {
								FREE_ARRAY (_hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII, char);
								while (required > _hoops_HCHGS->_hoops_ASIII && required < _hoops_CRIII)
									_hoops_HCHGS->_hoops_ASIII *= 2;
								while (required > _hoops_HCHGS->_hoops_ASIII)
									_hoops_HCHGS->_hoops_ASIII += _hoops_CRIII;
								ALLOC_ARRAY (_hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII, char);
							}
						_hoops_AAHR(_hoops_HCHGS->_hoops_ISHAP.text, _hoops_HCHGS->_hoops_ICIII);
						if (_hoops_HCHGS->_hoops_HCIII[1] != '\0')
							_hoops_HPRPR(_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_ICIII); 
						_hoops_HHGSA = _hoops_HCHGS->_hoops_ICIII;
					}
				}

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Rename_Segment (_hoops_PHGSA, _hoops_HHGSA);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "rendering_options")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Rendering_Options (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "renumber")) {
				_hoops_GGIII	*_hoops_GPCGS;

				ALLOC (_hoops_GPCGS, _hoops_GGIII);
				_hoops_GPCGS->next = _hoops_HCHGS->_hoops_RAIII;
				_hoops_GPCGS->type = _hoops_HGIII;
				_hoops_HCHGS->_hoops_RAIII = _hoops_GPCGS;
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "restart_ink")) {
				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Restart_Ink ();
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "roll_camera")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Roll_Camera (_hoops_HCHGS->_hoops_AIPCP);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "rotate_object")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Rotate_Object (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "rotate_object_offaxis")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_CGHGR))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Rotate_Object_Offaxis (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_CGHGR);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 's': {
			if (_hoops_AGGR (_hoops_CSRPR, "scale_object")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Scale_Object (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "segment")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII)) return false;
					if (_hoops_HCHGS->_hoops_ISHAP.length == 0 ||
						_hoops_HCHGS->_hoops_HCIII[0] != '/') {
						PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
						_hoops_HCHGS->new_key = HC_Open_Segment (_hoops_HCHGS->_hoops_HCIII);
						POPNAME(_hoops_HCHGS->_hoops_RIGC);
					}
					else {
						int		required = _hoops_HCHGS->_hoops_ISHAP.length + _hoops_SSGR (_hoops_HCHGS->_hoops_HCIII) + 1;

						if (required > _hoops_HCHGS->_hoops_ASIII) {
							FREE_ARRAY (_hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII, char);
							while (required > _hoops_HCHGS->_hoops_ASIII && required < _hoops_CRIII)
								_hoops_HCHGS->_hoops_ASIII *= 2;
							while (required > _hoops_HCHGS->_hoops_ASIII)
								_hoops_HCHGS->_hoops_ASIII += _hoops_CRIII;
							ALLOC_ARRAY (_hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII, char);
						}
						_hoops_AAHR(_hoops_HCHGS->_hoops_ISHAP.text, _hoops_HCHGS->_hoops_ICIII);
						if (_hoops_HCHGS->_hoops_HCIII[1] != '\0')
						_hoops_HPRPR(_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_ICIII); 
						PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
						_hoops_HCHGS->new_key = HC_Open_Segment (_hoops_HCHGS->_hoops_ICIII);
						POPNAME(_hoops_HCHGS->_hoops_RIGC);
					}

				if (_hoops_HCHGS->new_key == _hoops_SHSSR)
					return false;

				_hoops_GGIII	*_hoops_GPCGS;

				ALLOC (_hoops_GPCGS, _hoops_GGIII);
				_hoops_GPCGS->next = _hoops_HCHGS->_hoops_RAIII;
				_hoops_GPCGS->type = _hoops_AGIII;
				_hoops_HCHGS->_hoops_RAIII = _hoops_GPCGS;
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "segment_is_open")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				if (BIT (_hoops_HCHGS->_hoops_PAIII, _hoops_PCHAP))
					HI_Canonize_Chars (_hoops_HCHGS->_hoops_HCIII, &_hoops_HCHGS->_hoops_IAIII);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "selectability")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Selectability (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "shader")) {
					if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII) ||
						!_hoops_GCHGS (_hoops_GHIPH) ||
						!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
						!_hoops_GCHGS (_hoops_GHIPH) ||
						!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII)) 
						return false;

					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_Define_Shader (_hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_ICIII);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "shell")) {
					if (!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0) ||
						!_hoops_GCHGS (_hoops_GHIPH) ||
						!_hoops_SRIGS (_hoops_GHIPH, _hoops_HCHGS, 0))
						return false;

					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					_hoops_HCHGS->new_key = HC_Insert_Shell (_hoops_HCHGS->_hoops_GPIII, _hoops_HCHGS->_hoops_RPIII, 
													_hoops_HCHGS->_hoops_HPIII, _hoops_HCHGS->_hoops_IPIII);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "shell_by_tristrips")) {
				if (!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_SRIGS (_hoops_GHIPH, _hoops_HCHGS, 0) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_SRIGS (_hoops_GHIPH, _hoops_HCHGS, 1))
					return false;

				int *		_hoops_SPCGS = null;

				if (_hoops_HCHGS->_hoops_GHIII)
					_hoops_SPCGS = _hoops_HCHGS->_hoops_RHIII;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Shell_By_Tristrips (_hoops_HCHGS->_hoops_GPIII, _hoops_HCHGS->_hoops_RPIII, 
															_hoops_HCHGS->_hoops_HPIII, _hoops_HCHGS->_hoops_IPIII,
															_hoops_HCHGS->_hoops_GHIII, _hoops_SPCGS);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "sphere")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_PIGCR))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Sphere (&_hoops_HCHGS->_hoops_AGCII, _hoops_HCHGS->_hoops_AIPCP, &_hoops_HCHGS->_hoops_AIGCR, &_hoops_HCHGS->_hoops_PIGCR);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "spot_light")) {
				if (!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_ACHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIGCR) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Spot_Light (&_hoops_HCHGS->_hoops_AGCII, &_hoops_HCHGS->_hoops_AIGCR, _hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "streaming_mode")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Streaming_Mode (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "style_segment")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				if (_hoops_HCHGS->_hoops_ISHAP.length == 0 ||
					_hoops_HCHGS->_hoops_HCIII[0] != '/') {
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_Style_Segment (_hoops_HCHGS->_hoops_HCIII);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
				else {
					int		required = _hoops_HCHGS->_hoops_ISHAP.length + _hoops_SSGR (_hoops_HCHGS->_hoops_HCIII) + 1;

					if (required > _hoops_HCHGS->_hoops_ASIII) {
						FREE_ARRAY (_hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII, char);
						while (required > _hoops_HCHGS->_hoops_ASIII && required < _hoops_CRIII)
							_hoops_HCHGS->_hoops_ASIII *= 2;
						while (required > _hoops_HCHGS->_hoops_ASIII)
							_hoops_HCHGS->_hoops_ASIII += _hoops_CRIII;
						ALLOC_ARRAY (_hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII, char);
					}
					_hoops_AAHR(_hoops_HCHGS->_hoops_ISHAP.text, _hoops_HCHGS->_hoops_ICIII);
					if (_hoops_HCHGS->_hoops_HCIII[1] != '\0')
					_hoops_HPRPR(_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_ICIII); 
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_Style_Segment (_hoops_HCHGS->_hoops_ICIII);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 't': {
			if (_hoops_AGGR (_hoops_CSRPR, "text")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				_hoops_HCHGS->new_key = HC_Insert_Text (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "text_alignment")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Text_Alignment (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "text_font")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Text_Font (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "text_path")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Text_Path (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "text_region")) {
				if (!_hoops_IRIGS (_hoops_GHIPH, _hoops_HCHGS, 0) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Text_Region (_hoops_HCHGS->_hoops_GPIII,
									_hoops_HCHGS->_hoops_RPIII,
									_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "text_size")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Text_Size (_hoops_HCHGS->_hoops_AIPCP);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "text_spacing")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Text_Spacing (_hoops_HCHGS->_hoops_AIPCP);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "text_with_encoding")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
#if !HOOPS_BIGENDIAN
				if (_hoops_AGGR (_hoops_HCHGS->_hoops_RCIII, "unicode")) {
						char *_hoops_RPPA = _hoops_HCHGS->_hoops_HCIII;
						char tmp;

						while (_hoops_RPPA[0] != '\0' || _hoops_RPPA[1] != '\0') {
								tmp = _hoops_RPPA[1];
								_hoops_RPPA[1] = _hoops_RPPA[0];
								_hoops_RPPA[0] = tmp;
								_hoops_RPPA += 2;
						}
				}
#endif
				if (_hoops_AGGR (_hoops_HCHGS->_hoops_RCIII, "utf8")) {
					H_UTF8 _hoops_ASPPH;
					_hoops_ASPPH.encodedText ((utf8_char const*)_hoops_HCHGS->_hoops_HCIII);
					_hoops_HCHGS->new_key = HC_Insert_Text_With_Encoding (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_RCIII, (void const*)_hoops_ASPPH.encodedText());
				}
				else if (_hoops_AGGR (_hoops_HCHGS->_hoops_RCIII, "utf16")) {
					H_UTF8 _hoops_ASPPH;
					_hoops_ASPPH.encodedText ((utf8_char const*)_hoops_HCHGS->_hoops_HCIII);
					H_UTF16 _hoops_RSPPH(_hoops_ASPPH);
					_hoops_HCHGS->new_key = HC_Insert_Text_With_Encoding (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_RCIII, (void const*)_hoops_RSPPH.encodedText());
				}
				else if (_hoops_AGGR (_hoops_HCHGS->_hoops_RCIII, "utf32")) {
					H_UTF8 _hoops_ASPPH;
					_hoops_ASPPH.encodedText ((utf8_char const*)_hoops_HCHGS->_hoops_HCIII);
					H_UTF32 _hoops_ISPPH(_hoops_ASPPH);
					_hoops_HCHGS->new_key = HC_Insert_Text_With_Encoding (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_RCIII, (void const*)_hoops_ISPPH.encodedText());
				}
				else if (_hoops_AGGR (_hoops_HCHGS->_hoops_RCIII, "wcs")) {
					H_UTF8 _hoops_ASPPH;
					_hoops_ASPPH.encodedText ((utf8_char const*)_hoops_HCHGS->_hoops_HCIII);
					H_WCS _hoops_GGHPH(_hoops_ASPPH);
					_hoops_HCHGS->new_key = HC_Insert_Text_With_Encoding (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_RCIII, (void const*)_hoops_GGHPH.encodedText());
				}
				else	// _hoops_CSPGA, _hoops_GHCGS, _hoops_RHCGS
					_hoops_HCHGS->new_key = HC_Insert_Text_With_Encoding (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_RCIII, (void const*)_hoops_HCHGS->_hoops_HCIII);

				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "texture")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII)) return false;

				if (_hoops_HCHGS->_hoops_RAIII->type == _hoops_AGIII) {
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_Define_Local_Texture (_hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_HCIII);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
				else if (BIT (_hoops_HCHGS->_hoops_PAIII, _hoops_ICHAP)) {
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_Define_Texture (_hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_HCIII);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "texture_matrix")) {
				if (!_hoops_IHIGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->a0[0][0]))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Texture_Matrix (&_hoops_HCHGS->a0[0][0]);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "translate_object")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Translate_Object (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "trim_poly")) {
				bool				_hoops_AHCGS = false;

				if (_hoops_HCHGS->_hoops_RAIII->type != _hoops_ARIII) {
					if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII)||
						!_hoops_GCHGS (_hoops_GHIPH))
						return false;
					if (_hoops_HCHGS->_hoops_HCIII[0] == 'k')
						_hoops_AHCGS = true;
				}
				if (!_hoops_RAIGS(_hoops_GHIPH, _hoops_HCHGS, 0) ||
					!_hoops_GCHGS (_hoops_GHIPH)) 
						return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Trim_NURBS_Surface_By_Poly (_hoops_HCHGS->_hoops_GIIII/2, _hoops_HCHGS->_hoops_RIIII);
				if (_hoops_AHCGS)
					HC_Set_Trim_Operation (0, "keep");
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "trim_collection")) {
				bool				_hoops_AHCGS = false;

				if (_hoops_HCHGS->_hoops_RAIII->type != _hoops_ARIII) {
					if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII) ||
						!_hoops_GCHGS (_hoops_GHIPH))
						return false;
					if (_hoops_HCHGS->_hoops_HCIII[0] == 'k')
						_hoops_AHCGS = true;
				}
				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Create_Trim_Collection();
				if (_hoops_AHCGS)
					HC_Set_Trim_Operation (0, "keep");
				HC_Open_Trim (0);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);

				_hoops_GGIII *	_hoops_GPCGS;

				ALLOC (_hoops_GPCGS, _hoops_GGIII);
				_hoops_GPCGS->next = _hoops_HCHGS->_hoops_RAIII;
				_hoops_GPCGS->type = _hoops_ARIII;
				_hoops_HCHGS->_hoops_RAIII = _hoops_GPCGS;
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "trim_curve")) {
				float *control_points = null, *knots = null, *weights = null;
				int control_point_count, knot_count, weight_count;
				float start_u, end_u;
				bool _hoops_AHCGS = false;

				if (_hoops_HCHGS->_hoops_RAIII->type != _hoops_ARIII) {
					if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII)||
						!_hoops_GCHGS (_hoops_GHIPH))
						return false;
					if (_hoops_HCHGS->_hoops_HCIII[0] == 'k')
						_hoops_AHCGS = true;
				}

				if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII) ||				/* _hoops_AGR */
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &control_point_count) ||	/* _hoops_CPSGP */
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &start_u) ||				/* _hoops_APCGS */
					!_hoops_GCHGS (_hoops_GHIPH) || 
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &end_u) ||				/* _hoops_PPCGS	*/
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_RAIGS(_hoops_GHIPH, _hoops_HCHGS, 0))			/* _hoops_RGSHA _hoops_RSSA (_hoops_IARGR,_hoops_HPPC) */
					return false;

				_hoops_APRGA(_hoops_HCHGS->_hoops_RIIII, 2*control_point_count, float, control_points);
				if (control_points == null)
					return false;
				if (!_hoops_GCHGS (_hoops_GHIPH)) 
					return false;

				/* _hoops_RPP _hoops_IIH _hoops_CHR _hoops_HHRP _hoops_PPR _hoops_SGHSA, _hoops_IRIGR _hoops_CAPR */
				_hoops_PRCGS (_hoops_GHIPH, _hoops_HCHGS, &knot_count, &knots, &weight_count, &weights);

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Trim_NURBS_Surface_By_Curve (
						_hoops_HCHGS->_hoops_SSIII, control_point_count, control_points, weights, knots, 0, 1);
				if (_hoops_AHCGS)
					HC_Set_Trim_Operation (0, "keep");
				POPNAME(_hoops_HCHGS->_hoops_RIGC);

				FREE_ARRAY (control_points, 2*control_point_count, float);
				if (knots != null)
					FREE_ARRAY (knots, knot_count, float);
				if (weights != null)
					FREE_ARRAY (weights, weight_count, float);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'u': {
			if (_hoops_AGGR (_hoops_CSRPR, "user_options")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_User_Options (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "user_value")) {
				if (!_hoops_RIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_GGCII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_User_Value (_hoops_HCHGS->_hoops_GGCII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "user_index")) {
				if (!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_RIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_GGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_RIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SARAA)) return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_User_Index (_hoops_HCHGS->_hoops_GGCII, (void *)(POINTER_SIZED_INT)_hoops_HCHGS->_hoops_SARAA);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "user_data")) {
				if (!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_RIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_GGCII) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_RIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SARAA)) return false;

				if (_hoops_HCHGS->_hoops_SARAA > 0) {
					int i;
					char * data = 0;

					ALLOC_ARRAY_CACHED(data, _hoops_HCHGS->_hoops_SARAA, char);

					for (i=0; i<_hoops_HCHGS->_hoops_SARAA; i++) {
						long v;
						if (!_hoops_GCHGS (_hoops_GHIPH) ||
							!_hoops_RIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &v))
							return false;
						data[i] = (char)(0xff & v);
					}
					
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_Set_User_Data (_hoops_HCHGS->_hoops_GGCII, data, _hoops_HCHGS->_hoops_SARAA);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);

					FREE_ARRAY(data, _hoops_HCHGS->_hoops_SARAA, char);
				}
				else {
					PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
					HC_Set_User_Data (_hoops_HCHGS->_hoops_GGCII, 0, 0);
					POPNAME(_hoops_HCHGS->_hoops_RIGC);
				}
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "unicode_options")) {
				Karacter		_hoops_AGRIH[_hoops_CRIII/2];
				Karacter		*_hoops_IHSCP = _hoops_AGRIH;
				char const		*_hoops_RPPA = _hoops_HCHGS->_hoops_HCIII;

				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				_hoops_PCCAR {
					*_hoops_IHSCP = (_hoops_IRGCR (_hoops_RPPA[0]) << 8) |
							_hoops_IRGCR (_hoops_RPPA[1]);
					if (*_hoops_IHSCP++ == 0)
						break;
					_hoops_RPPA += 2;
				}

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Unicode_Options (_hoops_AGRIH);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'v': {
			if (_hoops_AGGR (_hoops_CSRPR, "variable_edge_weight")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Variable_Edge_Weight (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "variable_line_weight")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Variable_Line_Weight (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "variable_marker_size")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Variable_Marker_Size (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "vertex")) {
				if (!_hoops_AIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_SSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Open_Vertex (_hoops_HCHGS->_hoops_SSIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);

				_hoops_GGIII	*_hoops_GPCGS;

				ALLOC (_hoops_GPCGS, _hoops_GGIII);
				_hoops_GPCGS->next = _hoops_HCHGS->_hoops_RAIII;
				_hoops_GPCGS->type = _hoops_GRIII;
				_hoops_HCHGS->_hoops_RAIII = _hoops_GPCGS;
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "visibility")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Visibility (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'w': {
			if (_hoops_AGGR (_hoops_CSRPR, "window")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f1) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->f2) ||
					!_hoops_GCHGS (_hoops_GHIPH) ||
					!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_CGHGR))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Window (_hoops_HCHGS->_hoops_AIPCP, _hoops_HCHGS->f1, _hoops_HCHGS->f2, _hoops_HCHGS->_hoops_CGHGR);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "window_frame")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Window_Frame (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else if (_hoops_AGGR (_hoops_CSRPR, "window_pattern")) {
				if (!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Set_Window_Pattern (_hoops_HCHGS->_hoops_HCIII);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		case 'z': {
			if (_hoops_AGGR (_hoops_CSRPR, "zoom_camera")) {
				if (!_hoops_HIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_HCHGS->_hoops_AIPCP))
					return false;

				PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
				HC_Zoom_Camera (_hoops_HCHGS->_hoops_AIPCP);
				POPNAME(_hoops_HCHGS->_hoops_RIGC);
			}
			else
				return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	break;

		default: {
			return _hoops_SHHHC (_hoops_GHIPH, _hoops_CSRPR);
		}	_hoops_HHHI;
	}

	return true;
#else
	return false;
#endif
}





/*
 * _hoops_RRPP _hoops_RH _hoops_CIIA _hoops_SRHR _hoops_GH _hoops_IS _hoops_RH _hoops_SPS _hoops_GC _hoops_GAS _hoops_PPR _hoops_PPSI _hoops_RH _hoops_GHPP
 * _hoops_GGR '_hoops_GSIPH'.
 */
local bool _hoops_PHCGS (
	_hoops_IRIPH	*_hoops_GHIPH,
	char			*outp,
	char			*_hoops_HHCGS) {
	char			*_hoops_ASAPR;
	char			c;
	local		const char		_hoops_IHCGS[] =
					"Unrecognizable command -- too long for buffer";

	_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
	_hoops_PCCAR {
		if (_hoops_ASAPR == _hoops_GHIPH->_hoops_PSAPR) {
			_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
			if (!_hoops_CAHGS (_hoops_GHIPH)) return false;
			_hoops_ASAPR = _hoops_GHIPH->_hoops_ASAPR;
		}

		if (outp == _hoops_HHCGS) {
			_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;
			_hoops_GHIPH->message = _hoops_IHCGS;
			HI_Report_File_Error (_hoops_GHIPH);
			return false;
		}

		c = _hoops_SHPCR (*_hoops_ASAPR);

		if ((_hoops_RHHPP('a') <= _hoops_RHHPP(c) && _hoops_RHHPP(c) <= _hoops_RHHPP('z')) ||
			(_hoops_RHHPP('0') <= _hoops_RHHPP(c) && _hoops_RHHPP(c) <= _hoops_RHHPP('9')) ||
			c == '_')
			*outp++ = (char)c, ++_hoops_ASAPR;
		else
			break;
	}

	_hoops_GHIPH->_hoops_ASAPR = _hoops_ASAPR;

	/* (_hoops_CIS _hoops_HRGR _hoops_SHHA _hoops_IS _hoops_ASSS _hoops_IHH _hoops_RSIAR _hoops_IH _hoops_RH \0) */
	*outp = '\0';

	return true;
}


/*
 * _hoops_IAIGH _hoops_PAPA _hoops_IIGR _hoops_HAIGS _hoops_CHCGS _hoops_RGISI () - _hoops_IRIGR _hoops_PPR _hoops_HPPP _hoops_SPR _hoops_APRAR
 * _hoops_SHCGS _hoops_IGCI.
 */
local bool _hoops_GICGS (
	_hoops_IRIPH			*_hoops_GHIPH,
	_hoops_GAIII	*_hoops_HCHGS,
	bool				_hoops_RICGS) {
	_hoops_GGIII		*_hoops_AICGS = _hoops_HCHGS->_hoops_RAIII;

#	define		_hoops_PICGS					50
	char					_hoops_HICGS[_hoops_PICGS + 1];
	char					*_hoops_CSRPR = _hoops_HICGS,
										*_hoops_IICGS = _hoops_HICGS+_hoops_PICGS;
	int						_hoops_CCS = 0;

	do {
		if (_hoops_SPIPH (_hoops_GHIPH)) {
			if (_hoops_CCS == 0) return true;

			_hoops_GHIPH->message = "Expected ')' not found before end of file";
			HI_Report_File_Error (_hoops_GHIPH);
			return false;
		}

		/* _hoops_HGCR _hoops_RH _hoops_SPIGS _hoops_RGGR _hoops_IIGR _hoops_RH _hoops_IRGAA */
		if (*_hoops_GHIPH->_hoops_ASAPR != '(') return true;

		/* _hoops_RPR _hoops_SCH, _hoops_PPR _hoops_HGCR _hoops_GII _hoops_IHH _hoops_ARRPH */
		do {
			++_hoops_GHIPH->_hoops_ASAPR;
			++_hoops_CCS;
			if (!_hoops_GCHGS (_hoops_GHIPH)) return false;
		} while (*_hoops_GHIPH->_hoops_ASAPR == '(' && !_hoops_SPIPH(_hoops_GHIPH));

		/* _hoops_ISPR _hoops_IH _hoops_RHPA "()" _hoops_AGIR */
		if (*_hoops_GHIPH->_hoops_ASAPR != ')') {
			/* _hoops_HGCR _hoops_RH _hoops_RSIRR _hoops_IIGR _hoops_RH _hoops_IRGAA, _hoops_PPPCR _hoops_SCH, _hoops_PPR _hoops_AA _hoops_SCH */
			_hoops_HCHGS->new_key = _hoops_SHSSR;

			if (!_hoops_PHCGS (_hoops_GHIPH, _hoops_CSRPR, _hoops_IICGS) ||
				!_hoops_GCHGS (_hoops_GHIPH) ||
				!_hoops_CACGS (_hoops_GHIPH, _hoops_CSRPR, _hoops_HCHGS) ||
				!_hoops_GCHGS (_hoops_GHIPH)) return false;

			if (_hoops_HCHGS->_hoops_RAIII != _hoops_AICGS) {
				/* _hoops_HHPPA - _hoops_CPHP _hoops_CCAH _hoops_HSAAI _hoops_GH */

				switch (_hoops_HCHGS->_hoops_RAIII->type) {
					case _hoops_GRIII: {
						/* _hoops_SAHR _hoops_GHHA - _hoops_CSIII _hoops_SSAS _hoops_RH _hoops_IPHR */
						if (!_hoops_GICGS (_hoops_GHIPH, _hoops_HCHGS, true))
							return false;
						PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
						HC_Close_Vertex ();
						POPNAME(_hoops_HCHGS->_hoops_RIGC);
					}	break;

					case _hoops_RRIII: {
						/* _hoops_SAHR _hoops_GHHA - _hoops_CSIII _hoops_SSAS _hoops_RH _hoops_IPHR */
						if (!_hoops_GICGS (_hoops_GHIPH, _hoops_HCHGS, true))
							return false;
						PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
						HC_Close_LOD ();
						POPNAME(_hoops_HCHGS->_hoops_RIGC);
					}	break;

					case _hoops_SGIII: {
						/* _hoops_SAHR _hoops_GHHA - _hoops_CSIII _hoops_SSAS _hoops_RH _hoops_IPHR */
						if (!_hoops_GICGS (_hoops_GHIPH, _hoops_HCHGS, true)) return false;
						PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
						HC_Close_Edge ();
						POPNAME(_hoops_HCHGS->_hoops_RIGC);
					}	break;

					case _hoops_CGIII: {
						/* _hoops_SAHR _hoops_GHHA - _hoops_CSIII _hoops_SSAS _hoops_RH _hoops_IPHR */
						if (!_hoops_GICGS (_hoops_GHIPH, _hoops_HCHGS, true)) return false;
						PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
						HC_Close_Face ();
						POPNAME(_hoops_HCHGS->_hoops_RIGC);
					}	break;

					case _hoops_PGIII: {
						/* _hoops_GHHA - _hoops_RH _hoops_PIGS _hoops_CICGS _hoops_GRS _hoops_AA _hoops_RH _hoops_IPHR */
						if (!_hoops_GICGS (_hoops_GHIPH, _hoops_HCHGS, true)) return false;
						/* (_hoops_ISCP '_hoops_SICGS' _hoops_HRGR _hoops_RH _hoops_SIC _hoops_IIGR _hoops_RH _hoops_CGHI _hoops_ASSA _hoops_IGCI) */
					}	break;

					case _hoops_AGIII: {
						Key			_hoops_GCCGS = _hoops_HCHGS->new_key;

						/* _hoops_GHHA - _hoops_CSIII _hoops_SSAS _hoops_RH _hoops_IPHR */
						if (!_hoops_GICGS (_hoops_GHIPH, _hoops_HCHGS, true)) return false;
						PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
						HC_Close_Segment ();
						POPNAME(_hoops_HCHGS->_hoops_RIGC);
						/* (_hoops_ISCP '_hoops_SICGS' _hoops_HRGR _hoops_RH _hoops_GIGR _hoops_SPR _hoops_HII _hoops_RH _hoops_CAGH) */
						_hoops_HCHGS->new_key = _hoops_GCCGS;
					}	break;

					case _hoops_ARIII: {
						/* _hoops_GHHA - _hoops_CSIII _hoops_SSAS _hoops_RH _hoops_IPHR */
						if (!_hoops_GICGS (_hoops_GHIPH, _hoops_HCHGS, true)) return false;
						PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
						HC_Close_Trim ();
						POPNAME(_hoops_HCHGS->_hoops_RIGC);
					}	break;

					case _hoops_IGIII: {
						Geometry *geom;
						Polyhedron *phon;

						/* _hoops_PIHA _hoops_AA _hoops_IRS _hoops_RSRA _hoops_IRGAA, _hoops_PSCR _hoops_SGH _hoops_RGCI _hoops_SIC */
						if (!_hoops_GICGS (_hoops_GHIPH, _hoops_HCHGS, false)) return false;
						if (_hoops_HCHGS->new_key != _hoops_SHSSR) {
							Key			_hoops_GCCGS = _hoops_HCHGS->new_key;

							_hoops_HCHGS->_hoops_HAIII = _hoops_HCHGS->new_key;

							PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
							HC_Open_Geometry (_hoops_GCCGS);
							POPNAME(_hoops_HCHGS->_hoops_RIGC);
							/* _hoops_HA _hoops_AA _hoops_RH _hoops_PSSPR */
							if (!_hoops_GICGS (_hoops_GHIPH, _hoops_HCHGS, true)) return false;

							geom = (Geometry *) _hoops_RCSSR (_hoops_HCHGS->_hoops_RIGC, _hoops_GCCGS);
							if (geom->type == _hoops_SCIP) {
								phon = (Polyhedron *)geom;
								if ((((Shell *)phon)->face_list == null && phon->tristrips != null) &&
									((phon->local_face_attributes.flags != null) || phon->local_face_attributes._hoops_SGRHR != 0)) {
									/* _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_RRCPR, _hoops_PPSAR, _hoops_HPP _hoops_CCGI, _hoops_PPR _hoops_SSCP _hoops_IRGH _hoops_HSP _hoops_AIRC
									* _hoops_CCIH _hoops_SCH _hoops_GH _hoops_HIS _hoops_SGS _hoops_IRS _hoops_CRHH _hoops_GSRHR _hoops_GRS _hoops_HAR _hoops_SPHR _hoops_SHH _hoops_IRSGR.
									* (_hoops_PS _hoops_PAH'_hoops_RA _hoops_SCRHR _hoops_CCGI, _hoops_CR _hoops_SR _hoops_HS _hoops_PSP _hoops_HSP _hoops_HIGR) */
									HI_Resort_Tristrips(phon, -1);
								}
							}

							PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
							HC_Close_Geometry ();
							POPNAME(_hoops_HCHGS->_hoops_RIGC);
							/* (_hoops_ISCP '_hoops_SICGS' _hoops_HRGR _hoops_RH _hoops_GIGR _hoops_SPR) */
							_hoops_HCHGS->new_key = _hoops_GCCGS;
							_hoops_HCHGS->_hoops_HAIII = _hoops_SHSSR;
						}
					}	break;

					case _hoops_HGIII: {
						/* _hoops_PIHA _hoops_AA _hoops_IRS _hoops_RSRA _hoops_IRGAA, _hoops_PSCR _hoops_SGH _hoops_RGCI _hoops_SIC */
						Key				_hoops_ACHPA;

						if (!_hoops_GICGS (_hoops_GHIPH, _hoops_HCHGS, false)) return false;

						/* _hoops_IRIGR _hoops_RCCGS _hoops_PIH _hoops_PRGI _hoops_RPP "_hoops_GSRGR" _hoops_SRSH */
						/* _hoops_RGAR _hoops_IPSP _hoops_CRGIA _hoops_CHR _hoops_GGR _hoops_GPACI _hoops_HIS _hoops_SSIA
						* <32 _hoops_IGRH _hoops_PPR _hoops_RGR _hoops_HRGR _hoops_IHRI _hoops_GPP _hoops_ACCGS
						*/
						if (!_hoops_SHHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &_hoops_ACHPA) ||
							!_hoops_GCHGS (_hoops_GHIPH) ||
							!_hoops_GGCGS (_hoops_GHIPH, _hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII))
							return false;

						if (_hoops_HCHGS->new_key != _hoops_SHSSR) {
							PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
							HC_Renumber_Key (_hoops_HCHGS->new_key, _hoops_ACHPA, _hoops_HCHGS->_hoops_RCIII);
							POPNAME(_hoops_HCHGS->_hoops_RIGC);
						}
					}	break;

					case _hoops_PRIII: {
						/* _hoops_PIHA _hoops_AA _hoops_IRS _hoops_RSRA _hoops_IRGAA, _hoops_PSCR _hoops_SGH _hoops_RGCI _hoops_SIC */
						long			priority;

						if (!_hoops_GICGS (_hoops_GHIPH, _hoops_HCHGS, false))
							return false;

						/* _hoops_IRIGR _hoops_GHCP _hoops_PIH _hoops_PRGI _hoops_RPP "_hoops_GSRGR" _hoops_SRSH */
						if (!_hoops_RIHGS (_hoops_HCHGS->_hoops_RIGC, _hoops_GHIPH, &priority))
							return false;

						if (_hoops_HCHGS->new_key != _hoops_SHSSR) {
							PUSHNAME(_hoops_HCHGS->_hoops_RIGC);
							HC_Set_Priority (_hoops_HCHGS->new_key, priority);
							POPNAME(_hoops_HCHGS->_hoops_RIGC);
						}
					}	break;
				}

				{	_hoops_GGIII	 *_hoops_RSGHR = _hoops_HCHGS->_hoops_RAIII;
					_hoops_HCHGS->_hoops_RAIII = _hoops_RSGHR->next;
					FREE (_hoops_RSGHR, _hoops_GGIII);
					if (_hoops_HCHGS->_hoops_RAIII != _hoops_AICGS)
						return true;/* _hoops_SR'_hoops_ASAR _hoops_PCCGS*/
				}
			}

			if (_hoops_AICGS->type == _hoops_PGIII && _hoops_HCHGS->new_key != _hoops_SHSSR) {
				HI_Bring_To_Front_By_Key (_hoops_HCHGS->_hoops_RIGC, _hoops_HCHGS->new_key);
			}
		}

		/* _hoops_HGCR _hoops_RH _hoops_CSGR _hoops_RGGR(_hoops_GRI) */
		if (!_hoops_GCHGS (_hoops_GHIPH)) return false;
		while (!_hoops_SPIPH (_hoops_GHIPH) && *_hoops_GHIPH->_hoops_ASAPR == ')') {
			if (--_hoops_CCS < 0) return true; /* _hoops_HHPPA, _hoops_HAR _hoops_CARS */
			++_hoops_GHIPH->_hoops_ASAPR;
			if (!_hoops_GCHGS (_hoops_GHIPH)) return false;
		}
	} while (_hoops_RICGS || _hoops_CCS > 0);

	return true;
}


/* _hoops_CIAPI _hoops_RH _hoops_RGHR _hoops_GRSSR _hoops_HPP '_hoops_HAHGS' */
local bool _hoops_HCCGS (
	_hoops_IRIPH	*_hoops_GHIPH,
	_hoops_HCRPR			*_hoops_CCCIH,
	_hoops_HCRPR			*_hoops_SCCIH) {

	_hoops_GHIPH->_hoops_ASAPR = &_hoops_GHIPH->buffer[0][0];
	_hoops_GHIPH->_hoops_PSAPR = &_hoops_GHIPH->buffer[0][_hoops_PRIPH];
	_hoops_GHIPH->_hoops_RAIPH = 0;
	_hoops_GHIPH->_hoops_HAIPH = false;
	_hoops_GHIPH->_hoops_AAIPH = null;
	_hoops_GHIPH->_hoops_PAIPH = null;
	_hoops_GHIPH->_hoops_IAIPH = false;
	_hoops_GHIPH->_hoops_APIPH = 1;
	_hoops_GHIPH->_hoops_HHGHP = false;
	_hoops_GHIPH->_hoops_CAIPH = 1;
	_hoops_GHIPH->_hoops_HPIPH = false;
	_hoops_GHIPH->_hoops_SAPPR = 0;
	if (!HI_Open_File (&_hoops_GHIPH->filename, FILE_For_Reading, &_hoops_GHIPH->_hoops_CRIPH,
				false, _hoops_CCCIH, _hoops_SCCIH)) {
		return false;
	}
	if (!_hoops_APHGS (_hoops_GHIPH)) 
		return false;
	swap_buffers (_hoops_GHIPH);
	return _hoops_CAHGS (_hoops_GHIPH);
}


/*
 * _hoops_SPRHI _hoops_CCHGR _hoops_IH _hoops_GPS _hoops_GPACI
 *
 * '_hoops_PHHIP' _hoops_HRGR _hoops_SIGR _hoops_ARI _hoops_HIS _hoops_SGS _hoops_RH _hoops_CAGH _hoops_RSIRR _hoops_PAH _hoops_SHH _hoops_IGI _hoops_GAR _hoops_RH
 * _hoops_SHIR _hoops_RGHR _hoops_RSIRR
 */
local void _hoops_ICCGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	Metafile *				_hoops_PHCIH) {
#ifndef DISABLE_METAFILE
	_hoops_IRIPH				_hoops_GHIPH;
	_hoops_HCRPR					_hoops_CCCIH, _hoops_SCCIH;
	bool					_hoops_CCCGS = true;
	_hoops_AAPIR *				_hoops_PSHAP;
	_hoops_AAPIR				_hoops_SCCGS;
	int						version;


	PUSHNAME(_hoops_RIGC);
	_hoops_AASAH (_hoops_RIGC, "Metafile reading (internal)");

	ZERO_STRUCT (&_hoops_GHIPH, _hoops_IRIPH);
	_hoops_HGGIH(_hoops_GHIPH.filename);

	/* _hoops_GSCGS(); */

	if (_hoops_SRCP->geometry != null || _hoops_SRCP->_hoops_RGRPR != null)
		_hoops_CCCGS = false;

	if (_hoops_CCCGS && _hoops_SRCP->_hoops_IPPGR != null) {
		Attribute	*_hoops_RSCGS = _hoops_SRCP->_hoops_IPPGR;

		do if (_hoops_RSCGS->type != HK_DRIVER &&
			  _hoops_RSCGS->type != HK_DRIVER_OPTIONS) {
			_hoops_CCCGS = false;
			break;
		} while ((_hoops_RSCGS = _hoops_RSCGS->next) != null);
	}

	if (BIT (_hoops_PHCIH->value, _hoops_PHHAP)) {
		_hoops_SCCGS.name.length = _hoops_PHCIH->_hoops_PSHAP.length;
		_hoops_SCCGS.name.text = _hoops_PHCIH->_hoops_PSHAP.text;
		_hoops_SCCGS.next = HOOPS_WORLD->_hoops_HAGHP;
		_hoops_PSHAP = &_hoops_SCCGS;
	}
	else if ((_hoops_PSHAP = HOOPS_WORLD->_hoops_HAGHP) == null) {
		/* _hoops_RRP _hoops_PCCP _hoops_RHPA _hoops_PIRA */
		_hoops_SCCGS.name.length = 0;
		_hoops_SCCGS.name.text = null;
		_hoops_SCCGS.next = null;
		_hoops_PSHAP = &_hoops_SCCGS;
	}

	_hoops_GHIPH._hoops_PPIPH = false;
	_hoops_CCCIH.length = _hoops_SCCIH.length = 0;
	_hoops_GHIPH.filename.length = 0;
	_hoops_PCCAR if (HI_Get_Filename (_hoops_SRCP, _hoops_PHCIH, &_hoops_GHIPH, &_hoops_PSHAP->name)) {
		if (_hoops_HCCGS (&_hoops_GHIPH, &_hoops_CCCIH, &_hoops_SCCIH)) {
			if ((version = _hoops_CGCGS (_hoops_RIGC, &_hoops_GHIPH)) > 0) {
				_hoops_GAIII	*_hoops_HCHGS;

				/* _hoops_IIPP '_hoops_IPCGS' _hoops_GPP _hoops_RH _hoops_SIHPA _hoops_HRII _hoops_HSAR _hoops_RH _hoops_RRGC
				* _hoops_PGGA _hoops_SCH _hoops_GHCA _hoops_PGSAH _hoops_RH _hoops_SPRS _hoops_GPP _hoops_RH _hoops_AAGIP'_hoops_GRI.
				*/
				ALLOC (_hoops_HCHGS, _hoops_GAIII);
				_hoops_HCHGS->_hoops_RIGC = _hoops_RIGC;
				_hoops_HCHGS->_hoops_GRHRI = &_hoops_GHIPH;
				_hoops_HCHGS->version = version;
				_hoops_HCHGS->_hoops_RAIII = &_hoops_HCHGS->_hoops_AAIII;
				_hoops_HCHGS->_hoops_AAIII.type = _hoops_RGIII;
				_hoops_HCHGS->_hoops_IAIII.length = 0;
				_hoops_HCHGS->_hoops_RPIII = &_hoops_HCHGS->_hoops_CAIII[0];
				_hoops_HCHGS->_hoops_SAIII = _hoops_GGAPR(_hoops_HCHGS->_hoops_CAIII);
				_hoops_HCHGS->_hoops_IPIII = &_hoops_HCHGS->_hoops_APIII[0];
				_hoops_HCHGS->_hoops_PPIII = _hoops_GGAPR(_hoops_HCHGS->_hoops_APIII);
				_hoops_HCHGS->_hoops_RHIII = &_hoops_HCHGS->_hoops_CPIII[0];
				_hoops_HCHGS->_hoops_SPIII = _hoops_GGAPR(_hoops_HCHGS->_hoops_CPIII);
				_hoops_HCHGS->_hoops_IHIII = &_hoops_HCHGS->_hoops_AHIII[0];
				_hoops_HCHGS->_hoops_PHIII = _hoops_GGAPR(_hoops_HCHGS->_hoops_AHIII);
				_hoops_HCHGS->_hoops_RIIII = &_hoops_HCHGS->_hoops_CHIII[0];
				_hoops_HCHGS->_hoops_SHIII = _hoops_GGAPR(_hoops_HCHGS->_hoops_CHIII);
				_hoops_HCHGS->_hoops_IIIII = &_hoops_HCHGS->_hoops_AIIII[0];
				_hoops_HCHGS->_hoops_PIIII = _hoops_GGAPR(_hoops_HCHGS->_hoops_AIIII);

				_hoops_HCHGS->_hoops_CCIII = _hoops_HCHGS->_hoops_SCIII = _hoops_HCHGS->_hoops_GSIII = _hoops_HRIII;
				_hoops_HCHGS->_hoops_RSIII = _hoops_HCHGS->_hoops_ASIII = _hoops_HRIII;
				ALLOC_ARRAY_CACHED (_hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII, char);
				ALLOC_ARRAY_CACHED (_hoops_HCHGS->_hoops_ACIII, _hoops_HCHGS->_hoops_SCIII, char);
				ALLOC_ARRAY_CACHED (_hoops_HCHGS->_hoops_PCIII, _hoops_HCHGS->_hoops_GSIII, char);
				ALLOC_ARRAY_CACHED (_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII, char);
				ALLOC_ARRAY_CACHED (_hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII, char);

				_hoops_HCHGS->_hoops_PAIII = _hoops_PHCIH->_hoops_GSHAP &
									_hoops_PHCIH->_hoops_RSHAP;

				if (_hoops_PHCIH->_hoops_ISHAP.length > 0)
					HI_Copy_Name(&_hoops_PHCIH->_hoops_ISHAP, &_hoops_HCHGS->_hoops_ISHAP);
				else {
					HI_Copy_Name(&_hoops_RSPPR(_hoops_HCHGS->_hoops_RIGC, _hoops_ISHAP), &_hoops_HCHGS->_hoops_ISHAP);
				}

				if (_hoops_GCHGS (&_hoops_GHIPH) &&
					_hoops_GICGS (&_hoops_GHIPH, _hoops_HCHGS, true)) {
					/* _hoops_ICPRH _hoops_PCCP _hoops_RIHH _hoops_RPP _hoops_HAR _hoops_HPGR _hoops_RH _hoops_RSGR */
					if (!_hoops_SPIPH (&_hoops_GHIPH)) {
						char			_hoops_AHHGS[2];
						_hoops_AHHGS[0] = *_hoops_GHIPH._hoops_ASAPR;
						_hoops_AHHGS[1] = '\0';
						_hoops_GHIPH.message = Sprintf_S (null,
								"'%s' found when expecting the end of file", _hoops_AHHGS);
						HI_Report_File_Error (&_hoops_GHIPH);
					}
					else if (_hoops_HCHGS->_hoops_RAIII->type != _hoops_RGIII) {
						char const		*type;

						/* _hoops_ICPRH _hoops_PCCP _hoops_RIHH _hoops_RPP _hoops_PA _hoops_HGGC _hoops_IGS. */

						switch (_hoops_HCHGS->_hoops_RAIII->type) {
							case _hoops_PGIII:		type = "Front";			break;
							case _hoops_HGIII:	type = "Renumber";		break;
							case _hoops_AGIII:	type = "Segment";		break;
							case _hoops_GRIII:	type = "Vertex";		break;
							case _hoops_RRIII:		type = "LOD";			break;
							case _hoops_SGIII:		type = "Edge";			break;
							case _hoops_IGIII:	type = "Geometry";		break;
							case _hoops_CGIII:		type = "Face";			break;
							case _hoops_ARIII:		type = "Trim";			break;
							default:			type = "?internal error"; break;
						}

						_hoops_GHIPH.message = Sprintf_S (null,
								"Expected ')' to close '%s' command", type);
						HI_Report_File_Error (&_hoops_GHIPH);
					}

					/* _hoops_CASI _hoops_GH */
					_hoops_RGGA (_hoops_HCHGS->_hoops_RAIII->type == _hoops_RGIII) {
						_hoops_GGIII		*_hoops_RSGHR;

						_hoops_RSGHR = _hoops_HCHGS->_hoops_RAIII;
						PUSHNAME(_hoops_RIGC);
						switch (_hoops_RSGHR->type) {
							case _hoops_AGIII:	HC_Close_Segment ();	break;
							case _hoops_GRIII:	HC_Close_Vertex ();		break;
							case _hoops_RRIII:		HC_Close_LOD ();		break;
							case _hoops_SGIII:		HC_Close_Edge ();		break;
							case _hoops_IGIII:	HC_Close_Geometry ();	break;
							case _hoops_CGIII:		HC_Close_Face ();		break;
							case _hoops_ARIII:		HC_Close_Trim ();		break;
						}
						POPNAME(_hoops_RIGC);
						_hoops_HCHGS->_hoops_RAIII = _hoops_RSGHR->next;
						FREE (_hoops_RSGHR, _hoops_GGIII);
					}

					/* _hoops_CIAPI _hoops_RH _hoops_CAGH _hoops_PSHS _hoops_GGR _hoops_RH '_hoops_ASCGS'
					* _hoops_SCRII _hoops_IRGAA
					*/
					/* _hoops_HGASR: _hoops_RGAR _hoops_SPR _hoops_PAPA _hoops_PSCGS */
					if (_hoops_HCHGS->_hoops_IAIII.length != 0) {
						PUSHNAME(_hoops_RIGC);
						HC_Open_Segment (_hoops_HCHGS->_hoops_IAIII.text);
						POPNAME(_hoops_RIGC);

						_hoops_RGAIR (_hoops_HCHGS->_hoops_IAIII);
						_hoops_HCHGS->_hoops_IAIII.length = 0;
					}
				}

				/* _hoops_SP _hoops_GH '_hoops_IPCGS' */
				_hoops_RGGA (_hoops_HCHGS->_hoops_RAIII->type == _hoops_RGIII) {
					_hoops_GGIII		*_hoops_RSGHR;

					_hoops_RSGHR = _hoops_HCHGS->_hoops_RAIII;
					_hoops_HCHGS->_hoops_RAIII = _hoops_RSGHR->next;
					FREE (_hoops_RSGHR, _hoops_GGIII);
				}

				_hoops_RGAIR (_hoops_HCHGS->_hoops_IAIII);
				_hoops_RGAIR (_hoops_HCHGS->_hoops_ISHAP);

				if (_hoops_HCHGS->_hoops_RPIII != &_hoops_HCHGS->_hoops_CAIII[0])
					FREE_ARRAY (_hoops_HCHGS->_hoops_RPIII, _hoops_HCHGS->_hoops_SAIII, Point);

				if (_hoops_HCHGS->_hoops_IPIII != &_hoops_HCHGS->_hoops_APIII[0])
					FREE_ARRAY (_hoops_HCHGS->_hoops_IPIII, _hoops_HCHGS->_hoops_PPIII, int);

				if (_hoops_HCHGS->_hoops_RHIII != &_hoops_HCHGS->_hoops_CPIII[0])
					FREE_ARRAY (_hoops_HCHGS->_hoops_RHIII, _hoops_HCHGS->_hoops_SPIII, int);

				if (_hoops_HCHGS->_hoops_IHIII != &_hoops_HCHGS->_hoops_AHIII[0])
					FREE_ARRAY (_hoops_HCHGS->_hoops_IHIII, _hoops_HCHGS->_hoops_PHIII, char);

				if (_hoops_HCHGS->_hoops_RIIII != &_hoops_HCHGS->_hoops_CHIII[0])
					FREE_ARRAY (_hoops_HCHGS->_hoops_RIIII, _hoops_HCHGS->_hoops_SHIII, float);

				if (_hoops_HCHGS->_hoops_IIIII != &_hoops_HCHGS->_hoops_AIIII[0])
					FREE_ARRAY (_hoops_HCHGS->_hoops_IIIII, _hoops_HCHGS->_hoops_PIIII, _hoops_ARPA);

				FREE_ARRAY (_hoops_HCHGS->_hoops_RCIII, _hoops_HCHGS->_hoops_CCIII, char);
				FREE_ARRAY (_hoops_HCHGS->_hoops_ACIII, _hoops_HCHGS->_hoops_SCIII, char);
				FREE_ARRAY (_hoops_HCHGS->_hoops_PCIII, _hoops_HCHGS->_hoops_GSIII, char);
				FREE_ARRAY (_hoops_HCHGS->_hoops_HCIII, _hoops_HCHGS->_hoops_RSIII, char);
				FREE_ARRAY (_hoops_HCHGS->_hoops_ICIII, _hoops_HCHGS->_hoops_ASIII, char);

				FREE (_hoops_HCHGS, _hoops_GAIII);
			}
			HI_Close_File (_hoops_GHIPH._hoops_CRIPH, &_hoops_CCCIH, &_hoops_SCCIH);
			break;
		}

		if ((_hoops_PSHAP = _hoops_PSHAP->next) == null) {
			/* _hoops_IHCS _hoops_PSAP _hoops_RSGR _hoops_IIGR _hoops_HIGR! */
			HI_Report_File_Error_With_Names (&_hoops_GHIPH, &_hoops_CCCIH, &_hoops_SCCIH);
			break;
		}
		else {
			/* _hoops_SR'_hoops_GCPP _hoops_SGH _hoops_RH _hoops_GPSRR _hoops_HII _hoops_RH _hoops_CGHI _hoops_HAPR, _hoops_RPP _hoops_SCH _hoops_HGGC _hoops_ISHS */
			_hoops_RGAIR (_hoops_CCCIH);
			_hoops_RGAIR (_hoops_SCCIH);
			_hoops_CCCIH.length = _hoops_SCCIH.length = 0;
			_hoops_RGAIR (_hoops_GHIPH.filename);
			_hoops_GHIPH.filename.length = 0;
		}
	}
	if (_hoops_GHIPH.message)
		HI_Report_File_Error (&_hoops_GHIPH);
	_hoops_RGAIR (_hoops_GHIPH.filename);

	/* _hoops_HSCGS(); */

	POPNAME(_hoops_RIGC);
#endif
}


HC_INTERFACE void HC_CDECL HC_Read_Metafile (
	char const *		file,
	char const *		segname,
	char const *		options)
{
	_hoops_PAPPR context("Read_Metafile");

#ifdef DISABLE_METAFILE
	_hoops_IRPPR ("Metafile");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Read_Metafile (%S, %S, ", file, segname));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", options));
	);

	_hoops_CSPPR();

	_hoops_CRCP *	_hoops_SRCP;
	if ((_hoops_SRCP = HI_Create_Segment (context, null, segname, true)) != null) {

		Metafile			_hoops_APHCR;
		/* _hoops_HGCR _hoops_IRS _hoops_SPCS _hoops_SCRII _hoops_IGRI */
		ZERO_STRUCT (&_hoops_APHCR, Metafile);
		_hoops_APHCR.mask = _hoops_GHHAP;
		_hoops_APHCR.value = _hoops_GHHAP;

		_hoops_APHCR._hoops_RGIAP = _hoops_CSHAP;

		/* _hoops_CGIC _hoops_GII _hoops_AAP */
		HI_Decipher_Metafile_Options (context, options, &_hoops_APHCR);

		if (_hoops_APHCR._hoops_HSHAP.text == null) {
			while (*file == ' ') 
				++file;
			if (*file != '\0') {
				char	_hoops_ISCGS[MAX_ERRMSG];
				_hoops_RRIGI (_hoops_ISCGS, "name=%qs", file);
				HI_Decipher_Metafile_Options (context, _hoops_ISCGS, &_hoops_APHCR);
			}

			HI_Open_Segment (context, _hoops_SRCP);
			_hoops_ICCGS (context, _hoops_SRCP, &_hoops_APHCR);
			HI_Close_Segment (context);
		}

		_hoops_RGAIR (_hoops_APHCR.name);
		_hoops_RGAIR (_hoops_APHCR._hoops_PSHAP);
		_hoops_RGAIR (_hoops_APHCR.comment);
		_hoops_RGAIR (_hoops_APHCR._hoops_HSHAP);
		_hoops_RGAIR (_hoops_APHCR._hoops_ISHAP);
	}

	_hoops_IRRPR();

#endif
}



#ifndef DISABLE_METAFILE

const POINTER_SIZED_INT _hoops_CSRSC = 8;


local void _hoops_CSCGS (
						_hoops_HCRPR const	*in,
						_hoops_HCRPR			*_hoops_PAGR) {
							_hoops_HCRPR			_hoops_SPIPI;
							int				i;
							char			*_hoops_CSHPP, *_hoops_AHSCA;

							if (in->length == 0) return;

							i = in->length + _hoops_PAGR->length;
							ALLOC_ARRAY (_hoops_AHSCA, i+1, char);
							_hoops_SPIPI.text = _hoops_AHSCA;
							_hoops_SPIPI.length = i;

							i = _hoops_PAGR->length;
							if (i != 0) {
								_hoops_CSHPP = _hoops_PAGR->text;
								do *_hoops_AHSCA++ = *_hoops_CSHPP++;
								_hoops_RGGA (--i == 0);
							}

							_hoops_RGAIR (*_hoops_PAGR);

							i = in->length;
							if (i != 0) {
								_hoops_CSHPP = in->text;
								do *_hoops_AHSCA++ = *_hoops_CSHPP++;
								_hoops_RGGA (--i == 0);
							}

							*_hoops_AHSCA = '\0';

							_hoops_PAGR->length = _hoops_SPIPI.length;
							_hoops_PAGR->text = _hoops_SPIPI.text;
}
#endif

/*
*	_hoops_HPSHR _hoops_RH _hoops_HARGR _hoops_IIGR _hoops_RH _hoops_SCRII _hoops_IGRI _hoops_PPR _hoops_RH _hoops_CAGH _hoops_RSIRR,
*	_hoops_HPSSA _hoops_IRS _hoops_RGHR _hoops_CRAA _hoops_GIIA _hoops_GGR '_hoops_HAHGS->_hoops_CAIAH'
*/
local _hoops_SRHSR	_hoops_SSCGS = _hoops_GRRCR (".hmf");

GLOBAL_FUNCTION bool HI_Get_Filename (
	_hoops_CRCP		*_hoops_SRCP,
	Metafile		*_hoops_PHCIH,
	_hoops_IRIPH	*_hoops_GHIPH,
	_hoops_HCRPR			*_hoops_HHCIH) {
#ifndef DISABLE_METAFILE
		_hoops_HCRPR			_hoops_PSHAP, file, _hoops_GPIHH;

		_hoops_HGGIH(_hoops_PSHAP);
		_hoops_HGGIH(file);
		_hoops_HGGIH(_hoops_GPIHH);
		_hoops_HGGIH(_hoops_GHIPH->filename);

		if (BIT (_hoops_PHCIH->value, _hoops_AHHAP)) {
			if (_hoops_PHCIH->name.text == null || _hoops_PHCIH->name.length == 0) {
				_hoops_GHIPH->message = "'name' option was provided but is blank";
				HI_Report_File_Error (_hoops_GHIPH);
				return false;
			}
			HI_Parse_Filename (&_hoops_PHCIH->name, &_hoops_PSHAP, &file, &_hoops_GPIHH);
		}
		else if (_hoops_SRCP->name.length > 0) {
			char	*_hoops_CSHPP, *_hoops_AHSCA;
			int		i;

			_hoops_CSHPP = _hoops_SRCP->name.text;
			i = _hoops_AHIA (_hoops_SRCP->name.length, _hoops_CSRSC);
			ALLOC_ARRAY (_hoops_AHSCA, i+1, char);
			file.text = _hoops_AHSCA;
			file.length = i;
			while (i-- != 0) *_hoops_AHSCA++ = *_hoops_CSHPP++;
			*_hoops_AHSCA = '\0';
		}
		else
			HI_Copy_Chars_To_Name ("hoops", &file);

		if (_hoops_PSHAP.length == 0 && _hoops_HHCIH != null && _hoops_HHCIH->length != 0) {
			HI_Copy_Name (_hoops_HHCIH, &_hoops_PSHAP);
			HI_Add_Path_Delimiter (&_hoops_PSHAP, &file);
		}

		/* _hoops_RPP _hoops_RH _hoops_SAIHH _hoops_HRGR _hoops_HAR "._hoops_GGSGS" , _hoops_GAAP _hoops_CIGAA "._hoops_GGSGS" _hoops_IS _hoops_RH _hoops_GHPP */
		if ((_hoops_GPIHH.length == 0 &&
			_hoops_PHCIH->_hoops_RGIAP != _hoops_SSHAP) ||
			(MULTIPLE_DOT_FILENAMES &&
			!_hoops_RAHSR (_hoops_GPIHH, _hoops_SSCGS) &&
			_hoops_PHCIH->_hoops_RGIAP == _hoops_GGIAP))
			_hoops_CSCGS ((_hoops_HCRPR const *)&_hoops_SSCGS, &_hoops_GPIHH);

		_hoops_CSCGS (&_hoops_PSHAP, &_hoops_GHIPH->filename);
		_hoops_CSCGS (&file, &_hoops_GHIPH->filename);
		_hoops_CSCGS (&_hoops_GPIHH, &_hoops_GHIPH->filename);

		_hoops_RGAIR (_hoops_PSHAP);
		_hoops_RGAIR (file);
		_hoops_RGAIR (_hoops_GPIHH);

		if (_hoops_GHIPH->_hoops_PPIPH && !BIT (_hoops_PHCIH->value, _hoops_SHHAP))
			HI_Make_Unique_Filename (&_hoops_GHIPH->filename);

		return true;
#else
		return false;
#endif
}



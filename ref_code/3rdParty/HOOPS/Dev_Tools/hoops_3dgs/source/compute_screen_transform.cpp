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
 * $Id: obf_tmp.txt 1.59 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "tandt.h"


GLOBAL_FUNCTION void HD_Compute_Screen_Transform (
	Net_Rendition const &		nr,
	Point alter *				scale,
	Point alter *				translate) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_HHRA const *				_hoops_SPH = _hoops_IHCR->_hoops_SPH;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	float						_hoops_PCHH = _hoops_IHCR->_hoops_PCHH;

	/* _hoops_IPHR _hoops_GGR _hoops_CSHCR _hoops_IIGR _hoops_SPCR _hoops_ASPA... */

	/* _hoops_PAGAR _hoops_RH _hoops_IGAA _hoops_CHH _hoops_SHH "_hoops_RPHR _hoops_ACCHA _hoops_RAAP _hoops_PCCHA _hoops_HCCHA". _hoops_SAGAR, _hoops_SR
	 * _hoops_ICHRA _hoops_SPR _hoops_HII _hoops_SGS _hoops_IS _hoops_ASSS _hoops_IRS _hoops_HHAA-_hoops_AIR _hoops_CCPCR _hoops_SIPIR _hoops_HCR
	 * _hoops_AARI _hoops_RH _hoops_RPPS. _hoops_ICCHA, _hoops_RPP _hoops_IRS _hoops_III _hoops_HRGR _hoops_HGRC _hoops_GPCPR _hoops_HPGR _hoops_RH
	 * _hoops_ISHA _hoops_IIGR _hoops_RH _hoops_RPPS, _hoops_SR _hoops_HSRS _hoops_IRS _hoops_IGAA _hoops_PPR _hoops_IRS _hoops_APPS _hoops_SGS _hoops_GRS _hoops_CCCHA
	 * _hoops_SCH _hoops_GGR _hoops_RH _hoops_SCCHA _hoops_IIGR _hoops_RH _hoops_SPGHR _hoops_ASPA. _hoops_AAPAR _hoops_SCH _hoops_PPPPR'_hoops_RA _hoops_PPGC
	 * _hoops_SHH _hoops_SACH _hoops_SGGR.
	 */

	/* _hoops_SPCR & _hoops_GHCR _hoops_CHR _hoops_IHGP _hoops_SIA */
	/* _hoops_SIHH _hoops_GSCHA:
	_hoops_CSRA->_hoops_SISR = 0.5f * (_hoops_RSCHA->_hoops_ASCHA._hoops_RPHR - _hoops_RSCHA->_hoops_ASCHA._hoops_RAAP);
	_hoops_CSRA->_hoops_HAPC = 0.5f * (_hoops_RSCHA->_hoops_ASCHA._hoops_SCIA	- _hoops_RSCHA->_hoops_ASCHA._hoops_PRPC);
	*/
	/* _hoops_CCA _hoops_SHPR _hoops_CCIR, _hoops_SAHR _hoops_PCCP _hoops_IHH _hoops_CRICR _hoops_SAAA */

	scale->x = 0.25f * (_hoops_SGRA->_hoops_CIIH.right - _hoops_SGRA->_hoops_CIIH.left) *
						(_hoops_IHCR->_hoops_HCIH.right - _hoops_IHCR->_hoops_HCIH.left);
	scale->y = 0.25f * (_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom) *
						(_hoops_IHCR->_hoops_HCIH.top - _hoops_IHCR->_hoops_HCIH.bottom);

	if (_hoops_SPH->projection != _hoops_SSIH) {
		float						_hoops_ISIH;

		_hoops_ISIH = _hoops_SGRA->_hoops_CSIH * (_hoops_IHCR->_hoops_HCIH.top - _hoops_IHCR->_hoops_HCIH.bottom) /
									 (_hoops_IHCR->_hoops_HCIH.right - _hoops_IHCR->_hoops_HCIH.left);
		if (_hoops_ISIH <= _hoops_SPH->_hoops_CSIH)
			scale->x *= _hoops_ISIH / _hoops_SPH->_hoops_CSIH;
		else
			scale->y *= _hoops_SPH->_hoops_CSIH / _hoops_ISIH;
	}
	if (BIT (_hoops_IHCR->flags, _hoops_PGCH)) scale->x = -scale->x;

	/* _hoops_SIHH _hoops_GSCHA:
	_hoops_PHCH->_hoops_SISR = 0.5f*(_hoops_AIIC)(_hoops_RSCHA->_hoops_ASCHA._hoops_RAAP + _hoops_RSCHA->_hoops_ASCHA._hoops_RPHR);
	_hoops_PHCH->_hoops_HAPC = 0.5f*(_hoops_AIIC)(_hoops_RSCHA->_hoops_ASCHA._hoops_PRPC + _hoops_RSCHA->_hoops_ASCHA._hoops_SCIA);
	*/
	translate->x = 0.5f*(0.5f*(_hoops_IHCR->_hoops_HCIH.left+_hoops_IHCR->_hoops_HCIH.right) - -1.0f) *
					(_hoops_SGRA->_hoops_CIIH.right - _hoops_SGRA->_hoops_CIIH.left) + _hoops_SGRA->_hoops_CIIH.left;
	translate->y = 0.5f*(0.5f*(_hoops_IHCR->_hoops_HCIH.bottom+_hoops_IHCR->_hoops_HCIH.top) - -1.0f) *
					(_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom) + _hoops_SGRA->_hoops_CIIH.bottom;


	/* _hoops_AHCR _hoops_HRGR _hoops_PSCHA */
	if (!BIT(_hoops_IHCR->flags, _hoops_PASP) && _hoops_PCHH == 0.0f)
		_hoops_PCHH = (float)_hoops_HSCHA;

	/*
		_hoops_ISCHA _hoops_CSCHA, _hoops_SARA-_hoops_IS-_hoops_HIHP _hoops_AAAA _hoops_GGSR _hoops_IRS _hoops_RSGA
		_hoops_HGPP _hoops_SGS _hoops_CGPR _hoops_SSH = -1, _hoops_SSCHA = 0, _hoops_PPR _hoops_CGPR _hoops_SSH = 0, _hoops_SSCHA = 1. (_hoops_GPGP
		_hoops_RHAR, _hoops_SSCHA=_hoops_SSH+1, _hoops_IS _hoops_HSPP. _hoops_GPIP _hoops_HRGR _hoops_HPGR -1, _hoops_SAAP _hoops_HRGR _hoops_HPGR 0.)

		_hoops_PGII _hoops_RGR _hoops_IGIPR _hoops_SGS _hoops_SR _hoops_HHGC _hoops_IS _hoops_ARCR _hoops_CIAA [0, _hoops_GGSHA],
		_hoops_PGAP _hoops_HRGR _hoops_RH _hoops_IRISR _hoops_SHCA _hoops_GC.  _hoops_PS _hoops_HSPP _hoops_SIA _hoops_CRGR
		[0, 1] _hoops_PSCR _hoops_CSRA _hoops_RH _hoops_ACPP. 3D _hoops_SPSIR _hoops_SGS _hoops_RGSHA
		_hoops_AGSHA _hoops_PGAP _hoops_ACRR _hoops_RII _hoops_SCAP (_hoops_HGPP _hoops_GAR [-1, 1])
		_hoops_PAH _hoops_IRHH _hoops_RH _hoops_IRPR _hoops_PGSHA _hoops_GGR _hoops_RH _hoops_HGSHA _hoops_CAPP.
	*/

	if (_hoops_SPH->projection != _hoops_GHH) {
		/* _hoops_HSRR _hoops_CIHP:

		   _hoops_AHGHR: _hoops_RH _hoops_RHC _hoops_HRGR _hoops_HPGR _hoops_SSH = -_hoops_IGSHA.

		   _hoops_PS _hoops_HHGC _hoops_IS _hoops_ARCR:
			   1.  _hoops_SSH = [_hoops_RHC, +_hoops_IGSHA] = [-_hoops_IGSHA, +_hoops_IGSHA]
		   _hoops_IS  2.  [0, 1]

		   _hoops_SAGAR, _hoops_SGS'_hoops_GRI _hoops_HAR _hoops_GHAR, _hoops_HIS _hoops_SR _hoops_HSRS
		   _hoops_IRS _hoops_CCIR _hoops_IIHA _hoops_GPP _hoops_RH _hoops_SARA-_hoops_IS-_hoops_SAAP _hoops_GIRA,
		   _hoops_HGPP _hoops_GAR
			   3.  _hoops_SSH = [-_hoops_CGSHA, _hoops_CGSHA]
		   _hoops_PPR _hoops_SR _hoops_PPIP _hoops_SSCHA = 1, _hoops_GAR _hoops_RPP _hoops_SR _hoops_RIAGR _hoops_RIPPR _hoops_RH
		   _hoops_RHC _hoops_HCR _hoops_RH _hoops_PPRRR _hoops_ISSC _hoops_IS -_hoops_IGSHA.

		   _hoops_SGSHA _hoops_SSCHA _hoops_PAPR _hoops_IS _hoops_SHH 1 _hoops_HPGR _hoops_HCR _hoops_AHPHA _hoops_IH _hoops_PCCP
		   _hoops_CIHP _hoops_PHCR, _hoops_RH _hoops_GRSHA _hoops_HRGR
		   _hoops_RRSHA _hoops_GPICR

		   _hoops_AGGA, _hoops_SCH'_hoops_GRI _hoops_IHGP _hoops_IS _hoops_ARCR (3) _hoops_CIAA (2) _hoops_GRP
			   8.  _hoops_SSH' = _hoops_GRI*_hoops_SSH + _hoops_RA

			   9.  0  = _hoops_GRI * -_hoops_CGSHA + _hoops_RA
			  10.  1  = _hoops_GRI * _hoops_CGSHA  + _hoops_RA
			  --------------------------------
			  11.  1  =					   2_hoops_RA

			  12.  _hoops_RA = 1 / 2
			  13.  _hoops_GRI = _hoops_RA / _hoops_CGSHA	_hoops_HII (12) _hoops_PPR (9)

			  1/_hoops_CPSP->_hoops_ARSHA _hoops_AHPP _hoops_IS _hoops_SHH _hoops_IRS _hoops_GHAR _hoops_PIRA _hoops_IH _hoops_CGSHA
		*/

		scale->z = 0.5f * _hoops_IHCR->_hoops_CHCR;
		translate->z = 0.5f;
	}
	else {
		/*		_hoops_HSRR _hoops_AIHP:

			_hoops_AHGHR: _hoops_RH _hoops_RHC _hoops_HRGR _hoops_HPGR _hoops_SSH = -1, _hoops_SAAP _hoops_HRGR _hoops_HPGR _hoops_SSH = 0

			_hoops_PS _hoops_HHGC _hoops_IS _hoops_ARCR
				1.		_hoops_SSH = (_hoops_RHC, +_hoops_IGSHA] = (-1, +_hoops_IGSHA]
			_hoops_IS	2.		[0, 1]

			(1) _hoops_PAH _hoops_SHH _hoops_AIHCR _hoops_GRP _hoops_PRSHA _hoops_GAR
				3.		_hoops_SSH = [-1 + _hoops_PRSHA, +_hoops_IGSHA]
			_hoops_PGGA _hoops_SR _hoops_HPCAR _hoops_SGS _hoops_HRSHA _hoops_CIHH _hoops_GRS _hoops_GPHCR
			"_hoops_PRSHA" _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_IRSHA _hoops_RHC _hoops_PPSR, _hoops_CRSHA
			_hoops_HRGPR _hoops_RH _hoops_CGRRA _hoops_GHCH-_hoops_HPP-_hoops_AHHR _hoops_GAR _hoops_SR _hoops_GHCH _hoops_HPP _hoops_SSCHA

			_hoops_PS _hoops_PIHA _hoops_GHCH _hoops_HPP _hoops_SSCHA, _hoops_CAS
				4.		_hoops_SSCHA -> _hoops_PRSHA	  _hoops_GAR   _hoops_SSH -> -1 + _hoops_PRSHA
			_hoops_PGGA
				4a. _hoops_SSCHA -> 0			  _hoops_GAR   _hoops_SSH -> -1
			_hoops_PPR 5.		_hoops_SSCHA -> +_hoops_IGSHA	  _hoops_GAR   _hoops_SSH -> +_hoops_IGSHA

			_hoops_AGGA, (5) _hoops_SRSHA _hoops_PGGA _hoops_SSCHA=_hoops_SSH+_hoops_IHRPR _hoops_GAR _hoops_SSIA _hoops_PHHR _hoops_IS _hoops_GASHA,
			_hoops_HIAGR _hoops_IIGR _hoops_RH _hoops_RAR _hoops_CHRA.  _hoops_CPIPR _hoops_SGS _hoops_SISR/(_hoops_SISR+_hoops_IHRPR) -> 1
			_hoops_GAR _hoops_SISR -> +_hoops_IGSHA.

			_hoops_IGHS (4) _hoops_PPR (5) _hoops_IS _hoops_GHCH (3) _hoops_HPP _hoops_SSCHA, _hoops_SR _hoops_HGCR
				6.		_hoops_SSH/_hoops_SSCHA = [(-1 + _hoops_PRSHA) / _hoops_PRSHA, +_hoops_IGSHA/+_hoops_IGSHA]
			_hoops_PGAP _hoops_HRGR
				7.		_hoops_SSH/_hoops_SSCHA = [1 - 1/_hoops_PRSHA, 1]

			_hoops_AGGA, _hoops_SCH'_hoops_GRI _hoops_IHGP _hoops_IS _hoops_ARCR (7) _hoops_CIAA (2) _hoops_GRP
				8.		_hoops_SSH' = _hoops_GRI*(_hoops_SSH/_hoops_SSCHA) + _hoops_RA

				9.		0  = _hoops_GRI * (1 - 1/_hoops_PRSHA) + _hoops_RA
			   10.		1  = _hoops_GRI * (1)			+ _hoops_RA
			   ----------------------------------
			   11.		1  = _hoops_GRI / _hoops_PRSHA

			   12.		_hoops_GRI = _hoops_PRSHA
			   13.		_hoops_RA = 1 - _hoops_GRI		 _hoops_HII (10), (12)
		*/

		scale->z = _hoops_IHCR->_hoops_CHCR;
		translate->z = 1.0f - scale->z;
	}

	/* _hoops_CSRA _hoops_GHPP _hoops_HII [0,1] _hoops_IS [0,_hoops_RASHA], _hoops_AASHA _hoops_IH _hoops_GII _hoops_CCIR
	 * _hoops_GGIRR _hoops_PASHA _hoops_GGR _hoops_CPSP->_hoops_HASHA[]
	 */
	{
		float			_hoops_IASHA, _hoops_CASHA;

		_hoops_IASHA = (_hoops_IHCR->_hoops_GSCH[1] - _hoops_IHCR->_hoops_GSCH[0]) * _hoops_PCHH;
		_hoops_CASHA = _hoops_IHCR->_hoops_GSCH[0] * _hoops_PCHH;

		scale->z *= _hoops_IASHA;
		translate->z *= _hoops_IASHA;
		translate->z += _hoops_CASHA;
	}
}

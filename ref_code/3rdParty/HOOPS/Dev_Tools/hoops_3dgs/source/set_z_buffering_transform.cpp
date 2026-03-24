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
 * $Id: obf_tmp.txt 1.48 2010-05-17 20:25:06 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "hd_proto.h"
#include "tandt.h"

GLOBAL_FUNCTION void HD_Set_Z_Buffering_Transform (
	Net_Rendition const &		nr,
	bool						_hoops_GGIIH,
	bool						_hoops_RGIIH,
	float						_hoops_PCHH) {
	Net_Rendition				_hoops_APS = nr;
	_hoops_HHCR alter &	_hoops_IHCR = _hoops_APS->transform_rendition; /* _hoops_ICIC? */
	_hoops_HRPA					_hoops_RHSPR;

	/* _hoops_IRHH _hoops_RCRR _hoops_SHIR _hoops_ARSHA _hoops_HRGR _hoops_ARP _hoops_RPP _hoops_SIGR */
	if (_hoops_IHCR->_hoops_CHCR == 0.0f) {
		_hoops_IHCR->_hoops_CHCR = Abs(_hoops_GIPHP);
		_hoops_IHCR->_hoops_RIPHP = 1.0f;
	}

	if (_hoops_PCHH == 0.0f) {
		if (_hoops_IHCR->_hoops_PCHH > 0.0f)
			_hoops_PCHH = _hoops_IHCR->_hoops_PCHH;
		else
			_hoops_PCHH = nr->_hoops_SRA->_hoops_PGCC._hoops_PASHP;
	}

	if (BIT(_hoops_IHCR->flags, _hoops_PASP) == _hoops_RGIIH &&
		_hoops_IHCR->_hoops_PCHH == _hoops_PCHH &&
		(!_hoops_GGIIH || _hoops_PGSC (_hoops_IHCR->_hoops_HGSC))) {
		if (BIT (_hoops_IHCR->flags, _hoops_HHGGA))
			HD_Set_DC_Cutting_Planes (nr);

		return; /* _hoops_RPAPR (_hoops_HHSH) */
	}


	/* _hoops_SHH _hoops_RHRIR _hoops_ARI: _hoops_RPP _hoops_SR _hoops_CRHPS, _hoops_SCH _hoops_HGGC _hoops_IRHS _hoops_RH _hoops_RHGS _hoops_RASHA, _hoops_PPR _hoops_PSCR _hoops_SRHPS _hoops_IRHS _hoops_RH _hoops_CCAH _hoops_SPR */
	if (BIT (_hoops_IHCR->flags, _hoops_PRAIP)) {
		/* _hoops_IPCP _hoops_SSH-_hoops_SRHR _hoops_PIH _hoops_GSH _hoops_RH _hoops_PPPPI _hoops_SHPR _hoops_HIHP, _hoops_HIS _hoops_AHCR
		 * _hoops_SHPH _hoops_HGAP _hoops_PCCP _hoops_PAISR-_hoops_PRHSA _hoops_IIGR _hoops_PCCP _hoops_AIAH-_hoops_SGGA _hoops_SHPR _hoops_HPPPI.
		 */
		HD_Undo_Screen (nr, &_hoops_RHSPR);
		if (_hoops_RGIIH == _hoops_GGIIH) {
			if (_hoops_RGIIH)
				_hoops_IHCR->flags |= _hoops_PASP;
			else
				_hoops_IHCR->flags &= ~_hoops_PASP;
		}
		_hoops_IHCR->_hoops_PCHH = _hoops_PCHH;
		HD_Redo_Screen (nr, &_hoops_RHSPR);
	}
	else {
		/* _hoops_IHPHR _hoops_HRGR _hoops_IHGP */
		if (_hoops_RGIIH == _hoops_GGIIH) {
			if (_hoops_RGIIH)
				_hoops_IHCR->flags |= _hoops_PASP;
			else
				_hoops_IHCR->flags &= ~_hoops_PASP;
		}
		_hoops_IHCR->_hoops_PCHH = _hoops_PCHH;
	}

	if (BIT (_hoops_IHCR->flags, _hoops_HHGGA))
		HD_Set_DC_Cutting_Planes (nr);

	if (_hoops_GGIIH && !_hoops_PGSC (_hoops_IHCR->_hoops_HGSC)) {
		switch (_hoops_IHCR->_hoops_HGSC) {
			case _hoops_CIPHP:
			case _hoops_PCPHP:	_hoops_IHCR->_hoops_HGSC = _hoops_ACPHP;	 break;

			case _hoops_RCPHP: _hoops_IHCR->_hoops_HGSC = _hoops_GCPHP; break;
		}
	}
}

static INLINE float f1(float const x)
{
	return 20.0f / x;
}

static INLINE float _hoops_CGHGR(float const x)
{
	return 64.0f / x;
}

static INLINE float f2(float const x, float const _hoops_GAHPS, float const _hoops_RAHPS)
{
	float const _hoops_AAHPS = _hoops_CGHGR(_hoops_RAHPS) - f1(_hoops_GAHPS);
	float const _hoops_PAHPS = _hoops_RAHPS - _hoops_GAHPS;
	float const _hoops_HAHPS = f1(_hoops_GAHPS);
	float const retval = _hoops_AAHPS / _hoops_PAHPS * (x - _hoops_GAHPS) + _hoops_HAHPS;
	return retval;
}

static INLINE float f(float const x)
{
	float retval = 0;
	float const _hoops_GAHPS = 2.5f;
	float const _hoops_RAHPS = 16.0f;

	if(x < _hoops_GAHPS){
		retval = f1(x);
	} else if(x < _hoops_RAHPS) {
		retval = f2(x, _hoops_GAHPS, _hoops_RAHPS);
	} else{
		retval = _hoops_CGHGR(x);
	}
	return retval;
}


GLOBAL_FUNCTION float HD_Compute_Displacement_Scale (
	Net_Rendition const &		nr,
	float						_hoops_HAIIH) {


	if(nr->transform_rendition->_hoops_SPH != null &&
		BIT(nr->transform_rendition->flags, _hoops_GPSHP) &&
		nr->transform_rendition->_hoops_CHCR > 0.95 ){

		 float _hoops_RGRA = 1.0;

	    if (nr->transform_rendition->_hoops_CHCR <= 5.0)
			_hoops_RGRA = nr->transform_rendition->_hoops_CHCR / 5.0;

		float width = nr->transform_rendition->_hoops_SPH->_hoops_ISPA;
		float height = nr->transform_rendition->_hoops_SPH->_hoops_SSPA;
		float _hoops_IAHPS = sqrt(width*width + height*height);

		float x = nr->transform_rendition->_hoops_SPH->_hoops_SRIR / _hoops_IAHPS;

		float _hoops_PIAGP = 40.0/( pow((x+0.35),1.35) )+1.0;
		//_hoops_AIIC _hoops_CAHPS = _hoops_RCHP(_hoops_SISR);

		//_hoops_AIIC	_hoops_CAHPS = 30.0/( _hoops_RARGC(_hoops_SISR+0.35,2.0) )+4.0;

		//_hoops_AIIC _hoops_CAHPS = (20.0/_hoops_RARGC(_hoops_SISR+0.35,1.35) ) +0.4;

		//_hoops_AIIC _hoops_CAHPS = _hoops_SCII->_hoops_RICC->_hoops_ARSHA / _hoops_SCII->_hoops_RICC->_hoops_SAHPS;
		// _hoops_AIIC _hoops_CAHPS = 1.0f;



		return (_hoops_HAIIH/8.0)*_hoops_PIAGP*_hoops_RGRA;
	}
	else
		return _hoops_HAIIH;

}





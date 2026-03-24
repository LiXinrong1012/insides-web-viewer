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
 * $Id: obf_tmp.txt 1.170 2010-08-06 17:32:04 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hidden.h"
#include "hd_proto.h"
#include "hi_proto.h"

#include "adt.h"


#ifndef _hoops_CRHSA

local bool _hoops_HAGAS (
	float			_hoops_IAGAS,
	float			_hoops_CAGAS,
	DC_Point alter		*_hoops_SAGAS,
	DC_Point alter		*_hoops_GPGAS,
	_hoops_CASS alter *_hoops_RPGAS,
	DC_Point alter		*_hoops_APPCP,
	DC_Point alter		*_hoops_HPPCP) {
	DC_Point alter		*_hoops_GGIAR = _hoops_SAGAS,
										*p1 = _hoops_GPGAS;
	_hoops_SRHSA alter	*_hoops_ASHSA = _hoops_RPGAS->_hoops_ASHSA;
	float			t,
								_hoops_HSHGA,
								_hoops_ISHGA,
								_hoops_APGAS,
								_hoops_PPGAS;
	DC_Point alter		*p2;


	/* _hoops_ASRC _hoops_IHPR _hoops_RPP _hoops_IRS "_hoops_ACAAA" _hoops_SGSSR _hoops_HICP */

	if (-0.1f < _hoops_CAGAS && _hoops_CAGAS < 0.1f) return false;

	t = _hoops_IAGAS / _hoops_CAGAS;

	if (t > 0.5f) {
		/* _hoops_RH "_hoops_HPGAS" _hoops_HRGR _hoops_IPGAS _hoops_PARAA _hoops_HSAR _hoops_CPGAS _hoops_GPP _hoops_RH _hoops_CPGAS->_hoops_PARAA _hoops_ISHA */
		t = 1.0f - t;

		_hoops_HSHGA = (p1->x - _hoops_GGIAR->x) * t;
		if (_hoops_HSHGA > 3.0f*_hoops_HSISA || _hoops_HSHGA < -3.0f*_hoops_HSISA) return true;

		_hoops_ISHGA = (p1->y - _hoops_GGIAR->y) * t;
		if (_hoops_ISHGA > 3.0f*_hoops_HSISA || _hoops_ISHGA < -3.0f*_hoops_HSISA) return true;

		if (p1 == &_hoops_ASHSA->points[_hoops_ASHSA->count-1])
			p2 = _hoops_ASHSA->points;
		else
			p2 = p1+1;
	}
	else {
		/* _hoops_IPGAS _hoops_CPGAS _hoops_HSAR _hoops_PARAA */

		_hoops_HSHGA = (p1->x - _hoops_GGIAR->x) * t;
		if (_hoops_HSHGA > 3.0f*_hoops_HSISA || _hoops_HSHGA < -3.0f*_hoops_HSISA) return true;

		_hoops_ISHGA = (p1->y - _hoops_GGIAR->y) * t;
		if (_hoops_ISHGA > 3.0f*_hoops_HSISA || _hoops_ISHGA < -3.0f*_hoops_HSISA) return true;

		p2 = p1;
		p1 = _hoops_GGIAR;
		if (_hoops_GGIAR-- == _hoops_ASHSA->points)
			_hoops_GGIAR = &_hoops_ASHSA->points[_hoops_ASHSA->count-1];
	}

	/* _hoops_RRI _hoops_SPGAS _hoops_RPGP: _hoops_PARAA _hoops_HRGR _hoops_GPP _hoops_RH _hoops_GHGAS->_hoops_RHGAS _hoops_III, _hoops_HRPAI.
	 * _hoops_AIHH _hoops_RPP _hoops_CPGAS _hoops_PPR _hoops_AARAA _hoops_CHR _hoops_GPP _hoops_RH _hoops_PSHR _hoops_PAR _hoops_PGCHR _hoops_AIRSP _hoops_IIGR _hoops_SGS _hoops_III.
	 */

	_hoops_APGAS = _hoops_HPPCP->x - _hoops_APPCP->x;
	_hoops_PPGAS = _hoops_HPPCP->y - _hoops_APPCP->y;
	if (Abs (_hoops_APGAS) > Abs (_hoops_PPGAS)) {
		float					_hoops_AHGAS,
										_hoops_PHGAS;

		/* _hoops_III _hoops_HRGR _hoops_RRI _hoops_IRGGA _hoops_HSAR _hoops_IRPHR */
		if (Abs (_hoops_APGAS) < 2.0f*_hoops_HSISA) return false;

		/* _hoops_GPICR _hoops_SAPGP _hoops_IS _hoops_HHGAS _hoops_HICA _hoops_HHGS */
		_hoops_AHGAS = _hoops_GGIAR->y;
		_hoops_AHGAS -= _hoops_APPCP->y + (_hoops_GGIAR->x - _hoops_APPCP->x)/_hoops_APGAS * _hoops_PPGAS;

		_hoops_PHGAS = p2->y;
		_hoops_PHGAS -= _hoops_APPCP->y + (p2->x - _hoops_APPCP->x)/_hoops_APGAS * _hoops_PPGAS;

		if (_hoops_AHGAS < -2.0f*_hoops_HSISA) {
			if (_hoops_PHGAS > 2.0f*_hoops_HSISA) return true;
		}
		else if (_hoops_AHGAS > 2.0f*_hoops_HSISA) {
			if (_hoops_PHGAS < -2.0f*_hoops_HSISA) return true;
		}
		else {
			/* _hoops_CPGAS _hoops_HRGR _hoops_GACC _hoops_GPP _hoops_RH _hoops_III - _hoops_RCRP _hoops_GH */
		}
	}
	else {
		float					_hoops_IHGAS,
										_hoops_CHGAS;

		/* _hoops_III _hoops_HRGR _hoops_CRGP _hoops_IRGGA _hoops_HSAR _hoops_IRPHR */
		if (Abs (_hoops_PPGAS) < 2.0f*_hoops_HSISA) return false;

		/* _hoops_GPICR _hoops_SAPGP _hoops_IS _hoops_HHGAS _hoops_HICA _hoops_HHGS */
		_hoops_IHGAS = _hoops_GGIAR->x;
		_hoops_IHGAS -= _hoops_APPCP->x + (_hoops_GGIAR->y - _hoops_APPCP->y)/_hoops_PPGAS * _hoops_APGAS;

		_hoops_CHGAS = p2->x;
		_hoops_CHGAS -= _hoops_APPCP->x + (p2->y - _hoops_APPCP->y)/_hoops_PPGAS * _hoops_APGAS;

		if (_hoops_IHGAS < -2.0f*_hoops_HSISA) {
			if (_hoops_CHGAS > 2.0f*_hoops_HSISA) return true;
		}
		else if (_hoops_IHGAS > 2.0f*_hoops_HSISA) {
			if (_hoops_CHGAS < -2.0f*_hoops_HSISA) return true;
		}
		else {
			/* _hoops_CPGAS _hoops_HRGR _hoops_GACC _hoops_GPP _hoops_RH _hoops_III - _hoops_RCRP _hoops_GH */
		}
	}

	return false;
}


local bool _hoops_SHGAS (
	_hoops_CASS alter *test,
	_hoops_CASS alter *_hoops_HARIR) {
	_hoops_SRHSA alter	*_hoops_GIGAS = test->_hoops_ASHSA;
	_hoops_SRHSA alter	*_hoops_RIGAS = _hoops_HARIR->_hoops_ASHSA;
	float			px,
								py;
	DC_Point alter		*_hoops_APPCP,
								*_hoops_HPPCP;
	bool		_hoops_AIGAS,
								_hoops_PIGAS;
	float			_hoops_HIGAS,
								_hoops_IIGAS,
								_hoops_CIGAS,
								_hoops_SIGAS;
	int				count;

	/* _hoops_IH _hoops_SPR _hoops_PPSR _hoops_GGR _hoops_CPGAS, _hoops_CACH _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_GIAA _hoops_PARAA */

	_hoops_APPCP = &_hoops_GIGAS->points[0];
	if (_hoops_GIGAS->count == 1) {
		_hoops_HPPCP = null;
		px = _hoops_APPCP->x;
		py = _hoops_APPCP->y;
	}
	else {
		_hoops_HPPCP = &_hoops_GIGAS->points[1];

		if (_hoops_GIGAS->count == 2) {
			px = (_hoops_APPCP->x + _hoops_HPPCP->x) * 0.5f;
			py = (_hoops_APPCP->y + _hoops_HPPCP->y) * 0.5f;
		}
		else {
			DC_Point const	*_hoops_IPPCP = &_hoops_GIGAS->points[2];

			px = (_hoops_APPCP->x + _hoops_HPPCP->x + _hoops_IPPCP->x) * (1.0f/3.0f);
			py = (_hoops_APPCP->y + _hoops_HPPCP->y + _hoops_IPPCP->y) * (1.0f/3.0f);
		}
	}

	/* _hoops_AIIHR _hoops_RPGP... */

	if (!(_hoops_RIGAS->xmin <= px && px <= _hoops_RIGAS->xmax &&
		_hoops_RIGAS->ymin <= py && py <= _hoops_RIGAS->ymax)) return false;


	/* _hoops_GCGAS _hoops_RPGP... */

	_hoops_HIGAS = px - 2.0f*_hoops_HSISA;
	_hoops_IIGAS = px + 2.0f*_hoops_HSISA;
	_hoops_CIGAS = py - 2.0f*_hoops_HSISA;
	_hoops_SIGAS = py + 2.0f*_hoops_HSISA;

	/* _hoops_IISPR _hoops_RGR _hoops_SAHR _hoops_IS _hoops_CACH _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_SPPR _hoops_IIGR _hoops_PARAA _hoops_GIPR _hoops_RGCPR _hoops_IS
	 * _hoops_RH _hoops_RAAP _hoops_PPR _hoops_RH _hoops_RPHR _hoops_IIGR _hoops_IRS _hoops_RISA _hoops_IASC _hoops_AHCRR _hoops_IIGR _hoops_RH _hoops_PPSR _hoops_GGR _hoops_CPGAS.
	 */

	_hoops_AIGAS = _hoops_PIGAS = false;

	_hoops_APPCP = _hoops_RIGAS->points;
	count = _hoops_RIGAS->count;

	while (count-- > 0) {
		float			_hoops_ISHGA, tmp;

		if (count == 0)
			_hoops_HPPCP = _hoops_RIGAS->points;
		else
			_hoops_HPPCP = _hoops_APPCP+1;

		if (_hoops_APPCP->y < _hoops_CIGAS) {
			/* _hoops_GHGAS _hoops_GHCSA _hoops_CAPP; _hoops_IHSH _hoops_IH _hoops_RHGAS _hoops_HRPAI _hoops_ARRS */
			_hoops_RGGA (_hoops_HPPCP->y > _hoops_CIGAS) {
				if (count-- == 0) return false;
				++_hoops_APPCP;
				if (count == 0)
					_hoops_HPPCP = _hoops_RIGAS->points;
				else
					_hoops_HPPCP = _hoops_APPCP+1;
			}
			if (_hoops_HPPCP->y - _hoops_APPCP->y < 2.0f*_hoops_HSISA) continue;
		}
		else if (_hoops_APPCP->y > _hoops_SIGAS) {
			/* _hoops_GHGAS _hoops_GHCSA _hoops_ARRS; _hoops_IHSH _hoops_IH _hoops_RHGAS _hoops_HRPAI _hoops_CAPP */
			_hoops_RGGA (_hoops_HPPCP->y < _hoops_SIGAS) {
				if (count-- == 0) return false;
				++_hoops_APPCP;
				if (count == 0)
					_hoops_HPPCP = _hoops_RIGAS->points;
				else
					_hoops_HPPCP = _hoops_APPCP+1;
			}
			if (_hoops_APPCP->y - _hoops_HPPCP->y < 2.0f*_hoops_HSISA) continue;
		}
		else {
			/* _hoops_GHGAS _hoops_RSIPR _hoops_GHCSA _hoops_ARRS _hoops_PAR _hoops_CAPP; _hoops_GII _hoops_GRAA-_hoops_IRGGA
			 * _hoops_RHGAS _hoops_HRGR _hoops_GPRS
			 */
			tmp = _hoops_APPCP->y - _hoops_HPPCP->y;
			if (-2.0f*_hoops_HSISA < tmp && tmp < 2.0f*_hoops_HSISA) continue;
		}

		if (_hoops_APPCP->x < _hoops_HIGAS) {
			if (_hoops_HPPCP->x < _hoops_HIGAS) {
				if (_hoops_PIGAS) return true;
				_hoops_AIGAS = true;
				goto _hoops_SCAIP;
			}
		}
		else if (_hoops_APPCP->x > _hoops_IIGAS) {
			if (_hoops_HPPCP->x > _hoops_IIGAS) {
				if (_hoops_AIGAS) return true;
				_hoops_PIGAS = true;
				goto _hoops_SCAIP;
			}
		}

		tmp = _hoops_APPCP->x * (py - _hoops_HPPCP->y) -
			  _hoops_HPPCP->x * (py - _hoops_APPCP->y);

		if ((_hoops_ISHGA = _hoops_APPCP->y - _hoops_HPPCP->y) > 0.0f) {
			if (tmp < _hoops_HIGAS*_hoops_ISHGA) {
				if (_hoops_PIGAS) return true;
				_hoops_AIGAS = true;
			}
			else if (tmp > _hoops_IIGAS*_hoops_ISHGA) {
				if (_hoops_AIGAS) return true;
				_hoops_PIGAS = true;
			}
		}
		else {
			if (tmp > _hoops_HIGAS*_hoops_ISHGA) {
				if (_hoops_PIGAS) return true;
				_hoops_AIGAS = true;
			}
			else if (tmp < _hoops_IIGAS*_hoops_ISHGA) {
				if (_hoops_AIGAS) return true;
				_hoops_PIGAS = true;
			}
		}

	  _hoops_SCAIP:
		++_hoops_APPCP;
	}

	return false;
}
#endif


local bool _hoops_RCGAS (
	_hoops_CASS alter *	_hoops_ARSAH,
	_hoops_CASS alter *	_hoops_HPGPR) {
#ifndef _hoops_CRHSA
	_hoops_SRHSA alter *	_hoops_ACGAS = _hoops_ARSAH->_hoops_ASHSA;
	_hoops_SRHSA alter *	_hoops_PCGAS	= _hoops_HPGPR->_hoops_ASHSA;
	DC_Point alter *		_hoops_APPCP,
								*_hoops_GGIAR,
								*_hoops_HPPCP,
								*p1;
	int				_hoops_HCGAS, pcount;
	bool		_hoops_ICGAS;
	float			_hoops_GSAHR=0.05f;

	_hoops_ICGAS = (_hoops_ACGAS->type == _hoops_AHHSA &&
					  _hoops_HRCSA (_hoops_PCGAS->type) ||
					  _hoops_PCGAS->type == _hoops_AHHSA &&
					  _hoops_HRCSA (_hoops_ACGAS->type));

	if (!_hoops_ICGAS)
		_hoops_GSAHR=0.0f;


	_hoops_APPCP = _hoops_ACGAS->points;
	_hoops_HCGAS = _hoops_ACGAS->count;

	while (_hoops_HCGAS-- > 0) {
		float			_hoops_APGAS, _hoops_PPGAS,
										_hoops_CCGAS, _hoops_SCGAS,
										_hoops_GSGAS, _hoops_RSGAS, _hoops_SSHGA,
										_hoops_ASGAS, _hoops_PSGAS;

		if (_hoops_HCGAS == 0)
			_hoops_HPPCP = _hoops_ACGAS->points;
		else
			_hoops_HPPCP = _hoops_APPCP+1;

		_hoops_APGAS = _hoops_HPPCP->x - _hoops_APPCP->x;
		_hoops_PPGAS = _hoops_HPPCP->y - _hoops_APPCP->y;

		/* _hoops_CACH _hoops_RPP _hoops_RH _hoops_PRISA _hoops_GHSSR _hoops_SHHP (_hoops_GGR _hoops_PHCR) */

		/* _hoops_HHGC '_hoops_SGPSH' _hoops_PPR '_hoops_HSGAS' _hoops_CAS _hoops_CPGAS-_hoops_PARAA'_hoops_GRI _hoops_III _hoops_CGSSR _hoops_HRGR _hoops_IGISH _hoops_HPP
		 * _hoops_GHGAS-_hoops_RHGAS'_hoops_GRI. _hoops_CGP 0<_hoops_SGPSH<1, _hoops_SGS'_hoops_GRI _hoops_PGCPR; _hoops_RPP 0<_hoops_HSGAS<1, _hoops_SGS'_hoops_GRI _hoops_IRS
		 * _hoops_HPHR _hoops_HPGAS.
		 */

		/* _hoops_GAIPA _hoops_CPPHR:

				   (_hoops_ISGAS - _hoops_CSGAS) _hoops_SSGAS + (_hoops_GGRAS - _hoops_RGRAS) _hoops_AGRAS
			 [_hoops_HSGAS = ---------------------------------,
							 _hoops_PGRAS _hoops_SSGAS - _hoops_HGRAS _hoops_AGRAS

										 (_hoops_ISGAS - _hoops_CSGAS) _hoops_HGRAS + (_hoops_GGRAS - _hoops_RGRAS) _hoops_PGRAS
								  _hoops_SGPSH =	 -------------------------------------]
												   _hoops_PGRAS _hoops_SSGAS - _hoops_HGRAS _hoops_AGRAS

		 */

		_hoops_GGIAR = _hoops_PCGAS->points;
		pcount = _hoops_PCGAS->count;

		while (pcount-- > 0) {
			if (pcount == 0)
				p1 = _hoops_PCGAS->points;
			else
				p1 = _hoops_GGIAR+1;

			_hoops_CCGAS = p1->x - _hoops_GGIAR->x;
			_hoops_SCGAS = p1->y - _hoops_GGIAR->y;


			_hoops_ASGAS = _hoops_GGIAR->x - _hoops_APPCP->x;
			_hoops_PSGAS = _hoops_GGIAR->y - _hoops_APPCP->y;

			if (_hoops_ICGAS) {
				/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_IGRAS _hoops_IRS _hoops_HSSP _hoops_ISHA _hoops_ACSRR _hoops_IRS _hoops_III _hoops_CAGH,
				 * _hoops_SGH _hoops_PCCP _hoops_IHH _hoops_RPGP: _hoops_IRHH _hoops_RH _hoops_III == _hoops_RH _hoops_ISHA _hoops_IRS
				 * _hoops_IRS _hoops_AGIR _hoops_IIGR _hoops_GHASP. _hoops_ICCHA, _hoops_RPP _hoops_IRS _hoops_III _hoops_APSH _hoops_PII _hoops_SCH'_hoops_GRI
				 * _hoops_IHGS _hoops_IGI _hoops_GAR _hoops_PCCP _hoops_CGRAS _hoops_HSSP _hoops_ISHA, _hoops_HHSA _hoops_SCH
				 * _hoops_IS _hoops_RPR _hoops_GAR _hoops_GHASP _hoops_RH _hoops_HSSP. _hoops_SGRAS _hoops_PCCP _hoops_ISHA
				 * == _hoops_PCCP _hoops_ISHA, _hoops_PGAP _hoops_SR _hoops_HCAGR _hoops_PSRCA.
				 */

				float			tmp;

				if (-_hoops_HSISA < _hoops_ASGAS && _hoops_ASGAS < _hoops_HSISA) {
					if (-_hoops_HSISA < _hoops_PSGAS && _hoops_PSGAS < _hoops_HSISA) {
						tmp = p1->x - _hoops_HPPCP->x;
						if (-_hoops_HSISA < tmp && tmp < _hoops_HSISA) {
							tmp = p1->y - _hoops_HPPCP->y;
							if (-_hoops_HSISA < tmp && tmp < _hoops_HSISA) {
								return true;
							}
						}
					}
				}

				tmp = p1->x - _hoops_APPCP->x;
				if (-_hoops_HSISA < tmp && tmp < _hoops_HSISA) {
					tmp = p1->y - _hoops_APPCP->y;
					if (-_hoops_HSISA < tmp && tmp < _hoops_HSISA) {
						tmp = _hoops_GGIAR->x - _hoops_HPPCP->x;
						if (-_hoops_HSISA < tmp && tmp < _hoops_HSISA) {
							tmp = _hoops_GGIAR->y - _hoops_HPPCP->y;
							if (-_hoops_HSISA < tmp && tmp < _hoops_HSISA) {
								return true;
							}
						}
					}
				}
			}


			/* _hoops_AGAR _hoops_RPGP _hoops_IH _hoops_SGSSR _hoops_GAPA _hoops_AGCR _hoops_PGCR _hoops_SPPR */
			/* (_hoops_CPHR _hoops_GRRAS) */

			if ((_hoops_SSHGA = _hoops_SCGAS*_hoops_APGAS - _hoops_CCGAS*_hoops_PPGAS) > _hoops_GSAHR) {
				_hoops_RSGAS = _hoops_ASGAS * _hoops_PPGAS - _hoops_PSGAS * _hoops_APGAS;

				if (0.0f < _hoops_RSGAS && _hoops_RSGAS < _hoops_SSHGA) {
					_hoops_GSGAS = _hoops_ASGAS * _hoops_SCGAS - _hoops_PSGAS * _hoops_CCGAS;
					if (0.0f < _hoops_GSGAS && _hoops_GSGAS < _hoops_SSHGA) {
						if (_hoops_HAGAS (_hoops_RSGAS, _hoops_SSHGA, _hoops_GGIAR, p1, _hoops_HPGPR, _hoops_APPCP, _hoops_HPPCP) &&
							_hoops_HAGAS (_hoops_GSGAS, _hoops_SSHGA, _hoops_APPCP, _hoops_HPPCP, _hoops_ARSAH, _hoops_GGIAR, p1))
							return true;
					}
				}
			}
			else if (_hoops_SSHGA < -_hoops_GSAHR) {
				_hoops_RSGAS = _hoops_ASGAS * _hoops_PPGAS - _hoops_PSGAS * _hoops_APGAS;

				if (0.0f > _hoops_RSGAS && _hoops_RSGAS > _hoops_SSHGA) {
					_hoops_GSGAS = _hoops_ASGAS * _hoops_SCGAS - _hoops_PSGAS * _hoops_CCGAS;
					if (0.0f > _hoops_GSGAS && _hoops_GSGAS > _hoops_SSHGA) {
						if (_hoops_HAGAS (_hoops_RSGAS, _hoops_SSHGA, _hoops_GGIAR, p1, _hoops_HPGPR, _hoops_APPCP, _hoops_HPPCP) &&
							_hoops_HAGAS (_hoops_GSGAS, _hoops_SSHGA, _hoops_APPCP, _hoops_HPPCP, _hoops_ARSAH, _hoops_GGIAR, p1))
							return true;
					}
				}
			}
			else {	/* _hoops_AIIA _hoops_GGAIA */
				_hoops_RSGAS = _hoops_ASGAS * _hoops_PPGAS - _hoops_PSGAS * _hoops_APGAS;

				if (-_hoops_GSAHR < _hoops_RSGAS && _hoops_RSGAS < _hoops_GSAHR) {	/* _hoops_PPR _hoops_SPR _hoops_PPSR _hoops_IIGR _hoops_HAICR _hoops_GPP _hoops_III _hoops_HRAIA */
					_hoops_SSHGA = _hoops_APGAS * _hoops_APGAS + _hoops_PPGAS * _hoops_PPGAS;

					if (_hoops_SSHGA > 0.01f) {						/* _hoops_HRAIA _hoops_RGRRR _hoops_RAPR _hoops_IS _hoops_SHAC */
						_hoops_RSGAS = _hoops_ASGAS * _hoops_APGAS + _hoops_PSGAS * _hoops_PPGAS;
						_hoops_GSGAS = (p1->x - _hoops_APPCP->x) * _hoops_APGAS + (p1->y - _hoops_APPCP->y) * _hoops_PPGAS;

						_hoops_RSGAS /= _hoops_SSHGA;	/* _hoops_PRISA _hoops_PHCR _hoops_IIGR _hoops_CPGAS _hoops_CIAA _hoops_HRAIA */
						_hoops_GSGAS /= _hoops_SSHGA;	/* _hoops_PRISA _hoops_PHCR _hoops_IIGR _hoops_PARAA _hoops_CIAA _hoops_HRAIA */

						/* _hoops_RPP _hoops_PGI _hoops_PPSR _hoops_IIGR _hoops_HAICR _hoops_GIAA _hoops_CAGH _hoops_HRAIA */
						if (-0.001f < _hoops_RSGAS && _hoops_RSGAS < 1.001f ||
							-0.001f < _hoops_GSGAS && _hoops_GSGAS < 1.001f)
							return true;
					}
				}
			}

			++_hoops_GGIAR;
		}

		++_hoops_APPCP;
	}

	if (_hoops_HRCSA (_hoops_PCGAS->type) && _hoops_SHGAS (_hoops_ARSAH, _hoops_HPGPR))
		return true;
	else if (_hoops_HRCSA (_hoops_ACGAS->type) && _hoops_SHGAS (_hoops_HPGPR, _hoops_ARSAH))
		return true;
	else
#endif
		return false;
}


#ifndef _hoops_CRHSA

local int _hoops_RRRAS (
	_hoops_CASS alter *_hoops_GGIAR,
	_hoops_CASS alter *p1) {
	_hoops_SRHSA alter	*_hoops_ARRAS = p1->_hoops_ASHSA;
	_hoops_SRHSA alter	*_hoops_PRRAS = _hoops_GGIAR->_hoops_ASHSA;
	float			a = _hoops_ARRAS->plane.a,
								b = _hoops_ARRAS->plane.b,
								c = _hoops_ARRAS->plane.c;

	/* _hoops_CACH _hoops_RPP _hoops_HCR _hoops_CPGAS'_hoops_GRI _hoops_RSSA _hoops_CHR _hoops_GPP _hoops_SPR _hoops_PPAP _hoops_PAR _hoops_RH _hoops_RII _hoops_IIGR _hoops_PARAA'_hoops_GRI _hoops_IPPA */
	/* _hoops_RPP _hoops_SSIA _hoops_CHR _hoops_ASRC -1 _hoops_RPP _hoops_GGR _hoops_ISSC, +1 _hoops_RPP _hoops_GGR _hoops_RIPS */
	/* _hoops_RPP _hoops_IRPAA, _hoops_ASRC 2 */
	/* _hoops_RPP _hoops_HAR _hoops_GPP _hoops_SPR _hoops_PPAP _hoops_PPR _hoops_HAR _hoops_IRPAA, _hoops_ASRC 0 */

	if (_hoops_ARRAS->type == _hoops_AHHSA ||				/* _hoops_ISHA-_hoops_APGR _hoops_HS _hoops_PSP _hoops_IPPA */
		_hoops_ARRAS->type == _hoops_RCHSA ||				/*	  ""   ""	  ""	  */
		_hoops_PRRAS->type == _hoops_PCHSA ||			/* _hoops_AGCR _hoops_HS _hoops_PSP "_hoops_RSSA" */
		_hoops_PRRAS->type == _hoops_PIHSA ||				/*	  ""   ""	  ""	  */
		_hoops_PRRAS->type == _hoops_PHHSA) {				/*	  ""   ""	  ""	  */

		return 0;								/* _hoops_SR _hoops_CCSHR _hoops_HRRAS */
	}
	else if (c == 0.0f) {						/* _hoops_IPPA _hoops_HRGR _hoops_ISHA _hoops_GPP */
		if (_hoops_PRRAS->type <= _hoops_ARRAS->type)
			return -1;							/* _hoops_PSCR _hoops_CPGAS _hoops_PAH _hoops_SHH _hoops_SRS */
		else
			return 1;							/* (_hoops_PAR _hoops_GAAP _hoops_PARAA?) */
	}
	else {
		float			_hoops_IPCSA,
										_hoops_CPCSA,
										_hoops_HPCSA;
		DC_Point alter		*start;
		int						count;
		float					_hoops_GSAHR = _hoops_HSISA;

		/* _hoops_AAHP _hoops_PIHA _hoops_PSSP _hoops_PAR _hoops_SHH _hoops_RRPAR _hoops_HSAR _hoops_GGR _hoops_ACGR-_hoops_CPR! */

		if (_hoops_ARRAS->plane.d > 0) {
			if (1.0e-6f * _hoops_ARRAS->plane.d > _hoops_GSAHR)
				_hoops_GSAHR = 1.0e-6f * _hoops_ARRAS->plane.d;
		}
		else {
			if (-1.0e-6f * _hoops_ARRAS->plane.d > _hoops_GSAHR)
				_hoops_GSAHR = -1.0e-6f * _hoops_ARRAS->plane.d;
		}

		_hoops_CPCSA = -_hoops_ARRAS->plane.d + _hoops_GSAHR;
		_hoops_IPCSA = -_hoops_ARRAS->plane.d - _hoops_GSAHR;

		/* 1) _hoops_SSS _hoops_IRS _hoops_PPSR _hoops_GHCSA _hoops_GPP _hoops_SPR _hoops_PPAP _hoops_PAR _hoops_RH _hoops_RII _hoops_IIGR _hoops_RGR _hoops_IPPA,
		 *	  _hoops_RPP _hoops_IIH _hoops_CHR _hoops_GII _hoops_HGPP.
		 */

#		define	ABC(p) (a*(p)->x + b*(p)->y + c*(p)->z)

		start = _hoops_PRRAS->points;
		count = _hoops_PRRAS->count;
 		while (count-- > 0) {
			_hoops_HPCSA = ABC (start);
			if (_hoops_HPCSA > _hoops_CPCSA) {
				/* _hoops_IHSH _hoops_IH _hoops_IRS _hoops_PPSR _hoops_GHCSA _hoops_GPP _hoops_RH _hoops_IRRAS _hoops_PPAP */
				while (count-- > 0) {
					++start;
					if (ABC (start) < _hoops_IPCSA)
						return 0;
				}

				return -1;
			}
			else if (_hoops_HPCSA < _hoops_IPCSA) {
				/* _hoops_IHSH _hoops_IH _hoops_IRS _hoops_PPSR _hoops_GHCSA _hoops_GPP _hoops_RH _hoops_RRPAR _hoops_PPAP */
				while (count-- > 0) {
					++start;
					if (ABC (start) > _hoops_CPCSA)
						return 0;
				}

				return 1;
			}

			/* _hoops_GGR _hoops_RH _hoops_IPPA; _hoops_PAH'_hoops_RA _hoops_CRGS */
			++start;
		}

		/* _hoops_PIHA _hoops_SHH _hoops_IRPAA */
		return 2;
	}
}
#endif


local int _hoops_CRRAS (
	_hoops_CASS alter *	_hoops_GGIAR,
	_hoops_CASS alter *	p1) 
{
#ifndef _hoops_CRHSA
	_hoops_SRHSA alter *	_hoops_PRRAS = _hoops_GGIAR->_hoops_ASHSA;
	_hoops_SRHSA alter *	_hoops_ARRAS	= p1->_hoops_ASHSA;
	int				_hoops_AGCII, _hoops_AIGCR;

	/* _hoops_ASRC -1 _hoops_RPP _hoops_CPGAS _hoops_PAH _hoops_SHH _hoops_CHCC _hoops_ARPP _hoops_PARAA
	 *		  +1 _hoops_RPP _hoops_PARAA _hoops_PAH _hoops_SHH _hoops_CHCC _hoops_ARPP _hoops_CPGAS
	 *		  0	 _hoops_RPP _hoops_PGI _hoops_PAH _hoops_SHH _hoops_CHCC _hoops_SRS
	 *		  2	 _hoops_RPP _hoops_RSIPR _hoops_PAH _hoops_SHH _hoops_CHCC _hoops_SRS
	 */

	/* _hoops_SRRAS _hoops_GASR _hoops_IH _hoops_RH _hoops_ASRC _hoops_PIRA:
	 *
	 *		   -1	   0	 1	 (_hoops_HRRRH)
	 *		  -----------------
	 *	   -1 |	 0	  -1	-1
	 *		  |
	 *		0 |	 1	   ?	-1
	 *		  |
	 *		1 |	 1	   1	 0
	 *		  |
	 *	  (_hoops_RSCAI)
	 *
	 * _hoops_IPCP -1/-1 _hoops_HRGR _hoops_HAR _hoops_GRGA _hoops_RPCSH _hoops_IH - _hoops_SR _hoops_HSGR _hoops_GGSR _hoops_RAS _hoops_RSCAI == -1.
	 *
	 * _hoops_IPCP +1'_hoops_GRI _hoops_CHR _hoops_GHGPR-_hoops_RAICR.
	 *
	 * _hoops_IPCP 0/0 _hoops_PIRA _hoops_GCA _hoops_HPPA _hoops_RPHR _hoops_HA.
	 *
	 */

	if (_hoops_PRRAS->type == _hoops_AHHSA && _hoops_ARRAS->type == _hoops_AHHSA)
		return 0;		/* (_hoops_IH _hoops_HA) */

	if ((_hoops_AGCII = _hoops_RRRAS (_hoops_GGIAR, p1)) < 0) return -1;

	if (_hoops_AGCII == 2) return 0;		/* _hoops_IRPAA */

	if ((_hoops_AIGCR = _hoops_RRRAS (p1, _hoops_GGIAR)) > 0) {
		if (_hoops_AIGCR == 2) return 0;	/* _hoops_IRPAA */

		return _hoops_AGCII - 1;
	}

	/* _hoops_HPPR _hoops_IS _hoops_SRCH _hoops_RCCAR +1/+2 ... */
	if (_hoops_IARHH (_hoops_PRRAS->type) && _hoops_IARHH (_hoops_ARRAS->type))
		if (!_hoops_RCGAS (_hoops_GGIAR, p1)) return 0;

	if (_hoops_AGCII != _hoops_AIGCR) return 1;	  /* _hoops_SHCAR, _hoops_RPP _hoops_SSIA'_hoops_ASAR _hoops_HAR _hoops_GIPR _hoops_GSHCR, _hoops_PSCR... */

	/* _hoops_SSIA _hoops_AHGS _hoops_IS _hoops_ARCRA... */

	return 2; /* _hoops_RCRP _hoops_GH _hoops_GPP _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RGR _hoops_IH _hoops_HA */
#else
	return 0;
#endif
}


/*
 * _hoops_AASCI _hoops_IS _hoops_RCRP _hoops_AAPI _hoops_IRS _hoops_GARAS _hoops_CHAA _hoops_HPIPR, _hoops_HIS _hoops_SGS _hoops_RII
 * _hoops_CGSI _hoops_IHGS _hoops_SASPR _hoops_SSIA _hoops_GRS _hoops_RCPS _hoops_GGSR _hoops_GHIPR _hoops_CGSI _hoops_PII _hoops_SPPR.
 */
GLOBAL_FUNCTION void HD_Painters_Bias_Z (
	_hoops_CASS alter *hidden,
	bool		_hoops_RARAS) {
#ifndef DISABLE_SORTING_HSR
	float					_hoops_CSSAH=0.0f;
	_hoops_SRHSA alter	*_hoops_ASHSA = hidden->_hoops_ASHSA;
	DC_Point alter		*pt = _hoops_ASHSA->points;
	int						count = _hoops_ASHSA->count;

	if (_hoops_HRCSA (_hoops_ASHSA->type))
		_hoops_CSSAH += _hoops_ASHSA->_hoops_APHGA->transform_rendition->_hoops_CHIH;

	_hoops_CSSAH += _hoops_ASHSA->_hoops_APHGA->transform_rendition->_hoops_SHIH;
	_hoops_CSSAH *= _hoops_ISSIR(_hoops_ASHSA->_hoops_APHGA->transform_rendition);

	if (_hoops_CSSAH == 0.0f)
		return;

	if (!_hoops_RARAS) 
		_hoops_CSSAH = -_hoops_CSSAH;

	_hoops_ASHSA->_hoops_RICR += _hoops_CSSAH;
	_hoops_ASHSA->_hoops_AICR += _hoops_CSSAH;
	_hoops_ASHSA->plane.d -= _hoops_ASHSA->plane.c * _hoops_CSSAH;

	while (count-- > 0) {
		pt->z += _hoops_CSSAH;
		++pt;
	}
#endif
}

GLOBAL_FUNCTION void HD_Remove_Hidden_Followers (
	_hoops_CASS alter *thing,
	_hoops_CASS alter *start) {
#ifndef _hoops_CRHSA

	_hoops_PCCAR {
		if (start->_hoops_HPISA == thing) {
			start->_hoops_HPISA = null;
			if (--thing->values == 0) return;
		}
		start = start->next;
	}
#endif
}

#ifndef _hoops_CRHSA


/*
 * _hoops_ICPSA _hoops_PII _hoops_IRS _hoops_AARAS _hoops_RSSAI _hoops_CASPC _hoops_HARS _hoops_PPR _hoops_RIRP _hoops_PPR
 * _hoops_RH _hoops_PARAS _hoops_GAPA _hoops_CAPR.
 *
 * _hoops_ICGP _hoops_SPR _hoops_IIGR _hoops_CAPR _hoops_APSAR _hoops_IS _hoops_AACC _hoops_HPP. _hoops_CGP _hoops_IIH _hoops_CHR _hoops_GII _hoops_SAIA/
 * _hoops_AIR _hoops_SIRGR/_hoops_HCGR _hoops_RHIPP, _hoops_SSIA _hoops_PAH'_hoops_RA _hoops_SHH _hoops_AACC, _hoops_HIS _hoops_SRS _hoops_HPPR _hoops_IS
 * _hoops_SRSHR _hoops_IRS _hoops_PGAGA _hoops_SGS'_hoops_GRI _hoops_AARGR _hoops_IS _hoops_AHCR (_hoops_PII _hoops_SPR _hoops_IIGR _hoops_CAPR) _hoops_HIS
 * _hoops_SSIA _hoops_PPPPR'_hoops_RA _hoops_RRP _hoops_IS _hoops_SHH _hoops_AACC.
 */
local _hoops_CASS alter *_hoops_HARAS (
	Display_Context const *		dc,
	_hoops_CASS alter *				head,
	_hoops_CASS alter *				tail) {
	_hoops_CASS alter *				test;
	_hoops_CASS alter *				_hoops_IARAS;
	_hoops_CASS alter *				_hoops_CARAS;


	_hoops_IARAS = head;
	_hoops_PCCAR {
		if (_hoops_GGRSH (_hoops_IARAS)) {
			float			z = _hoops_IARAS->_hoops_ASHSA->_hoops_RICR;
			_hoops_ARPA		plane;

			plane.a = 0.0f;
			plane.b = 0.0f;
			plane.c = 1.0f;
			plane.d = (float)(-z);

			test = head;
			_hoops_PCCAR {
				if (test->_hoops_ASHSA->_hoops_RICR < z && z < test->_hoops_ASHSA->_hoops_AICR) {
					if (HD_Cut_Hidden_By_Plane (dc, test, &plane, false)) { 
						if (test == tail) return head;
						test = test->next;		/* _hoops_HSGR _hoops_ISGR _hoops_CCAH _hoops_SPR */
					}
				}
				if (test == tail) break;
				test = test->next;
			}
		}
		if (_hoops_IARAS == tail) break;
		_hoops_IARAS = _hoops_IARAS->next;
	}

	_hoops_IARAS = head;
	_hoops_RGGA (_hoops_IARAS->_hoops_ASHSA->type != _hoops_AHHSA) { /* _hoops_CCGR _hoops_SSCP-_hoops_IRS-_hoops_IPPA */
		if (_hoops_IARAS == tail) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "A cycle made of edges");
			return null;
		}
		_hoops_IARAS = _hoops_IARAS->next;
	}

	_hoops_CARAS = _hoops_IARAS;

	_hoops_PCCAR {
		test = head;

		_hoops_PCCAR {
			if (test != _hoops_IARAS)
				if (HD_Cut_Hidden_By_Plane (dc, test, &_hoops_IARAS->_hoops_ASHSA->plane, false)) 
					return head;

			if (test == tail) break;

			test = test->next;
		}

		do {
			if (_hoops_IARAS == tail)
				_hoops_IARAS = head;
			else
				_hoops_IARAS = _hoops_IARAS->next;
		}
		_hoops_RGGA (_hoops_IARAS->_hoops_ASHSA->type != _hoops_AHHSA);

		if (_hoops_IARAS == _hoops_CARAS) {
#ifdef _hoops_CGSPR
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						"Internal error: An uncuttable hidden-surface cycle");
#endif
			return null;
		}
	}
}


local _hoops_CASS alter *_hoops_SARAS (
	Display_Context const *		dc,
	_hoops_CASS alter *				head,
	_hoops_CASS alter *				test) {
	_hoops_CASS alter *				_hoops_GPRAS;
	_hoops_CASS alter *				_hoops_GPGHP;
								

	/* _hoops_HARS _hoops_CGH _hoops_SRHIR _hoops_RPGP */

	/*
	 * _hoops_PS _hoops_AA _hoops_RGR _hoops_HPP _hoops_HGIPR _hoops_RH _hoops_SHSC _hoops_IIGR _hoops_RPGP'_hoops_GRI "_hoops_PIHA _hoops_SRHIR" _hoops_AASH
	 * _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_HARS.
	 */

	_hoops_GPRAS = test;
	_hoops_GPRAS->prev->next = _hoops_GPRAS->next;
	_hoops_GPRAS->next->prev = _hoops_GPRAS->prev;

	_hoops_GPRAS->next = _hoops_GPRAS->prev = _hoops_GPRAS;

	_hoops_RGGA ((_hoops_GPGHP = _hoops_GPRAS->_hoops_HPISA) == null) {
		/*
		 * _hoops_RPRAS _hoops_SGS _hoops_HCR _hoops_RH "-1"'_hoops_GRI _hoops_SGS _hoops_HHPPR "_hoops_CIGSH"'_hoops_GRI _hoops_IS _hoops_SHH
		 * _hoops_PIISR _hoops_GGR _hoops_AAPR _hoops_IRARH _hoops_CCCI _hoops_HPP _hoops_IRCC _hoops_RH _hoops_PIIA _hoops_AGIR.
		 */

		if ((_hoops_HRCSA (_hoops_GPGHP->_hoops_ASHSA->type) &&
			 _hoops_IARHH (_hoops_GPRAS->_hoops_ASHSA->type)) ||
			(_hoops_GPGHP->_hoops_ASHSA->type == _hoops_AHHSA &&
			 _hoops_HRCSA (_hoops_GPRAS->_hoops_ASHSA->type))) {
			if (_hoops_CRRAS (_hoops_GPRAS, _hoops_GPGHP) <= 0) { 
				_hoops_GPRAS->_hoops_HPISA = null;
				--_hoops_GPGHP->values;
				break;
			}
		}

		if (_hoops_GPGHP == head) {
			/*
			 * _hoops_APRAS - _hoops_SR'_hoops_RISP _hoops_PPRAS _hoops_PSAP _hoops_RH _hoops_RIPS -
			 * (_hoops_SR'_hoops_RISP _hoops_GGHP _hoops_CAIR _hoops_IRS _hoops_AARAS _hoops_RSSAI)
			 */

			/* _hoops_PPSI _hoops_PIPSH _hoops_GPP _hoops_RH _hoops_RIPS _hoops_PPR _hoops_PIPSH->_hoops_SPS _hoops_GPP _hoops_RH _hoops_ISSC */

			_hoops_GPRAS->prev->next = _hoops_GPGHP->next;
			_hoops_GPGHP->next->prev = _hoops_GPRAS->prev;
			_hoops_GPRAS->prev = _hoops_GPGHP;
			_hoops_GPGHP->next = _hoops_GPRAS;

			return _hoops_HARAS (dc, _hoops_GPGHP, test); 
		}

		/* _hoops_HPRAS _hoops_SCH _hoops_HII _hoops_RH _hoops_RHGS _hoops_HIGR */

		_hoops_GPGHP->prev->next = _hoops_GPGHP->next;
		_hoops_GPGHP->next->prev = _hoops_GPGHP->prev;

		/* _hoops_PPSI _hoops_SCH _hoops_GPP _hoops_RH _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_CCAH _hoops_HIGR */
		_hoops_GPGHP->next = _hoops_GPRAS;
		_hoops_GPGHP->prev = _hoops_GPRAS->prev;
		_hoops_GPRAS->prev->next = _hoops_GPGHP;
		_hoops_GPRAS->prev = _hoops_GPGHP;
		_hoops_GPRAS = _hoops_GPGHP;
	}

	/* _hoops_PPSI _hoops_RGR _hoops_AASH _hoops_GPP _hoops_RH _hoops_RIPS */
	head->prev->next = test->next;
	test->next->prev = head->prev;
	head->prev = test;
	test->next = head;

	/* _hoops_PCSA _hoops_CPCP _hoops_SIHC */
	head->_hoops_HPISA = test;
	++test->values;

#if 0	/* _hoops_RCSC _hoops_RHAP _hoops_RGR _hoops_HAPR _hoops_IIP _hoops_IGRC _hoops_SSS _hoops_PA ??? */

	/* _hoops_IRHH _hoops_RCRR _hoops_SGS _hoops_IPRAS _hoops_SIPGR'_hoops_RA _hoops_IHPPP _hoops_CRGR _hoops_CPRAS */

	test = _hoops_GPRAS;
	if (head->values != 0) {
		do if (test->_hoops_HPISA == head) {
#ifdef _hoops_CGSPR
				printf ("booga!\n");
#endif /* _hoops_SHRS */
			test->_hoops_HPISA = null;
			if (--head->values == 0) break;
		}
		_hoops_RGGA ((test = test->next) == head);
	}
#endif

	return _hoops_GPRAS;
}

local _hoops_CASS alter * _hoops_SPRAS (
	Display_Context const *		dc,
	_hoops_CASS alter *				head,
	_hoops_CASS alter * alter *		_hoops_GHRAS) {

	_hoops_SRHSA alter *		_hoops_RHRAS;
	_hoops_CASS alter *				_hoops_RCSHR = *_hoops_GHRAS;
	_hoops_CASS alter *				test;
	_hoops_SRHSA alter *		_hoops_GIGAS;

	if ((test = head) == null) {
		/* _hoops_GRH _hoops_AGIR - _hoops_IRS _hoops_AHRAS '_hoops_SCGR' _hoops_HIGR */
		/* _hoops_RCRP _hoops_SCH _hoops_RH _hoops_SRS (_hoops_PHRAS _hoops_SGGR) _hoops_RCAPR _hoops_AHAP _hoops_GSGI */
		test = head = _hoops_RCSHR;
		_hoops_RCSHR = head->next;
		head->next = head->prev = head;

		/* _hoops_HSPP _hoops_CASI _hoops_CGPR _hoops_HHRAS _hoops_PSAP _hoops_RCAPR _hoops_HIGR */
		head->_hoops_HPISA = null;
		head->values = 0;
	}

	_hoops_PCCAR {
		_hoops_CASS alter *_hoops_IHRAS;
		int _hoops_SIPI, result;
		float _hoops_CHRAS, _hoops_SHRAS;

		if ((test = test->next) == head) { /* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_HPGR _hoops_RH _hoops_RSGR */
			if ((test = _hoops_RCSHR) == null || test->_hoops_ASHSA->_hoops_AICR < head->_hoops_ASHSA->_hoops_RICR) break;

			/* _hoops_IRAA _hoops_SCH _hoops_PSAP _hoops_RH _hoops_RCAPR _hoops_HIGR _hoops_PPR _hoops_PPSI _hoops_SCH _hoops_ARPP _hoops_RH _hoops_HARS */
			_hoops_RCSHR = test->next;
			test->prev = head->prev;
			test->prev->next = test;
			test->next = head;
			head->prev = test;

			/* _hoops_HSPP _hoops_CASI _hoops_CGPR _hoops_HHRAS _hoops_PSAP _hoops_RCAPR _hoops_HIGR */
			test->_hoops_HPISA = null;
			test->values = 0;
		}

		/* _hoops_HHGC _hoops_IS _hoops_CACH _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_GPRS _hoops_IS _hoops_PGSA '_hoops_HARS' _hoops_ARPP '_hoops_RPGP'... */

		/* _hoops_IASC _hoops_AHCRR _hoops_ISPR */
		_hoops_GIGAS = test->_hoops_ASHSA;
		_hoops_RHRAS = head->_hoops_ASHSA;

		if (_hoops_GIGAS->_hoops_AICR < _hoops_RHRAS->_hoops_RICR) {/* _hoops_HCR _hoops_GPRS */}
		else if (_hoops_GIGAS->_hoops_AICR == _hoops_RHRAS->_hoops_RICR &&
				 (_hoops_RHRAS->_hoops_AICR > _hoops_GIGAS->_hoops_RICR || _hoops_RHRAS->type <= _hoops_GIGAS->type)) {/*_hoops_GPRS*/}
		else if (_hoops_RHRAS->xmax < _hoops_GIGAS->xmin) {/* _hoops_HCR _hoops_GPRS */}
		else if (_hoops_GIGAS->xmax < _hoops_RHRAS->xmin) {/* _hoops_HCR _hoops_GPRS */}
		else if (_hoops_RHRAS->ymax < _hoops_GIGAS->ymin) {/* _hoops_HCR _hoops_GPRS */}
		else if (_hoops_GIGAS->ymax < _hoops_RHRAS->ymin) {/* _hoops_HCR _hoops_GPRS */}
		else if (test->_hoops_HPISA == head) {/* _hoops_HCR _hoops_GPRS */}

		/* _hoops_RPP _hoops_RH _hoops_RSSA _hoops_IHSH _hoops_GPRS... */
		else {
			/*
			 * _hoops_PS _hoops_HS _hoops_IS _hoops_AA _hoops_HPHR _hoops_IPHR _hoops_GPP _hoops_RGR _hoops_SPR -- _hoops_RGR _hoops_HRGR _hoops_PCCP
			 * _hoops_IRPR _hoops_HRGS _hoops_IS _hoops_ISPR _hoops_IH _hoops_PCCP _hoops_PAAP _hoops_RCCS
			 * _hoops_PPR _hoops_HGCR _hoops_GGSR _hoops_IIGR _hoops_IRS _hoops_AGIIP-_hoops_CPPPR-_hoops_CPPPR-_hoops_RGRRR _hoops_HAPR.
			 */
			if (_hoops_GGPGR(_hoops_GIGAS->_hoops_APHGA))
				break;

			if ((_hoops_SIPI = _hoops_CRRAS (head, test)) <= 0) {
				if (_hoops_SIPI < 0 && test->_hoops_HPISA == null) {
					test->_hoops_HPISA = head; /* _hoops_RHAC _hoops_PIHA _hoops_PCSA _hoops_RGR... */
					++head->values;
				}

				/* _hoops_HCR _hoops_GPRS */
			}
			else if (_hoops_SIPI == 2) {		/* _hoops_AGSIP */
#ifndef _hoops_GPISI
				/* _hoops_PSHR _hoops_PCGC _hoops_GAR _hoops_ARRS, _hoops_RGAR _hoops_RRI _hoops_GIRAS (<=, >=) */

				if (_hoops_GIGAS->_hoops_AICR <= _hoops_RHRAS->_hoops_RICR) {/* _hoops_HCR _hoops_GPRS */}
				else if (_hoops_RHRAS->xmax <= _hoops_GIGAS->xmin) {/* _hoops_HCR _hoops_GPRS */}
				else if (_hoops_GIGAS->xmax <= _hoops_RHRAS->xmin) {/* _hoops_HCR _hoops_GPRS */}
				else if (_hoops_RHRAS->ymax <= _hoops_GIGAS->ymin) {/* _hoops_HCR _hoops_GPRS */}
				else if (_hoops_GIGAS->ymax <= _hoops_RHRAS->ymin) {/* _hoops_HCR _hoops_GPRS */}

				/* _hoops_HPPR _hoops_IS _hoops_AACC _hoops_RH "_hoops_HRHC" _hoops_AHAP _hoops_SRS */
				else if (0 && _hoops_GIGAS->xmax - _hoops_GIGAS->xmin + _hoops_GIGAS->ymax - _hoops_GIGAS->ymin <
						 _hoops_RHRAS->xmax - _hoops_RHRAS->xmin + _hoops_RHRAS->ymax - _hoops_RHRAS->ymin) {
					if ((result = HD_Cut_Hidden_By_Plane (dc, test, &_hoops_RHRAS->plane, true)) != 0) { 
						if (result != -1) {
							/* _hoops_CPCP _hoops_CGH _hoops_GACHR _hoops_RPGP -> _hoops_HARS -> _hoops_RPGP->_hoops_SPS */
							test->next->_hoops_HPISA = head;
							++head->values;
							if ((_hoops_IHRAS = _hoops_SARAS (dc, head, test)) == null) 
								break;	/* _hoops_SPGC! */

							test = head = _hoops_IHRAS;
						}
						else {
							_hoops_CHRAS = 0.5f * (_hoops_GIGAS->_hoops_AICR + _hoops_GIGAS->_hoops_RICR);
							_hoops_SHRAS = 0.5f * (_hoops_RHRAS->_hoops_AICR + _hoops_RHRAS->_hoops_RICR);

							if (_hoops_CHRAS < _hoops_SHRAS && test->_hoops_HPISA == null) {
								test->_hoops_HPISA = head; /* _hoops_RHAC _hoops_PIHA _hoops_PCSA _hoops_RGR... */
								++head->values;
							}
							else {
								/* '_hoops_HARS' _hoops_CGH _hoops_SHH _hoops_CPHR _hoops_RAS '_hoops_RPGP' */
								if ((_hoops_IHRAS = _hoops_SARAS (dc, head, test)) == null) break; /* _hoops_SPGC! */ 
								/* _hoops_HARS'_hoops_GRI _hoops_RPII _hoops_SRSS - _hoops_HSPP _hoops_HCHAR _hoops_GICS */
								test = head = _hoops_IHRAS;
							}
						}
					}
					else if ((result = HD_Cut_Hidden_By_Plane (dc, head, &_hoops_GIGAS->plane, true)) != 0) { 
						if (result != -1) {
							/* _hoops_CPCP _hoops_CGH _hoops_GACHR _hoops_HARS -> _hoops_RPGP -> _hoops_HARS->_hoops_SPS */
							_hoops_IHRAS = head->next;
							head->next = _hoops_IHRAS->next;
							_hoops_IHRAS->next->prev = head;

							_hoops_IHRAS->next = test->next;
							_hoops_IHRAS->next->prev = _hoops_IHRAS;
							_hoops_IHRAS->prev = test;
							test->next = _hoops_IHRAS;

							_hoops_IHRAS->_hoops_HPISA = test;
							++test->values;

							/* _hoops_HARS'_hoops_GRI _hoops_RPII _hoops_IIAC _hoops_HRHC - _hoops_HSPP _hoops_HCHAR _hoops_GICS */
							test = head;
						}
						else {
							_hoops_CHRAS = 0.5f * (_hoops_GIGAS->_hoops_AICR + _hoops_GIGAS->_hoops_RICR);
							_hoops_SHRAS = 0.5f * (_hoops_RHRAS->_hoops_AICR + _hoops_RHRAS->_hoops_RICR);

							if (_hoops_CHRAS < _hoops_SHRAS && test->_hoops_HPISA == null) {
								test->_hoops_HPISA = head; /* _hoops_RHAC _hoops_PIHA _hoops_PCSA _hoops_RGR... */
								++head->values;
							}
							else {
								/* '_hoops_HARS' _hoops_CGH _hoops_SHH _hoops_CPHR _hoops_RAS '_hoops_RPGP' */
								if ((_hoops_IHRAS = _hoops_SARAS (dc, head, test)) == null) break; /* _hoops_SPGC! */ 
								/* _hoops_HARS'_hoops_GRI _hoops_RPII _hoops_SRSS - _hoops_HSPP _hoops_HCHAR _hoops_GICS */
								test = head = _hoops_IHRAS;
							}
						}
					}
					else {
#ifdef _hoops_CGSPR
							printf ("Skew/intersecting polygon confusion 1 - can't cut!\7\n");
#endif /* _hoops_SHRS */
						break;	/* _hoops_HGCR _hoops_GGSR _hoops_IIGR _hoops_ARI */
					}
				}
				else {
					if ((result = HD_Cut_Hidden_By_Plane (dc, head, &_hoops_GIGAS->plane, true)) != 0) { 
						if (result != -1) {		
							/* _hoops_CPCP _hoops_CGH _hoops_GACHR _hoops_HARS -> _hoops_RPGP -> _hoops_HARS->_hoops_SPS */
							_hoops_IHRAS = head->next;
							head->next = _hoops_IHRAS->next;
							_hoops_IHRAS->next->prev = head;

							_hoops_IHRAS->next = test->next;
							_hoops_IHRAS->next->prev = _hoops_IHRAS;
							_hoops_IHRAS->prev = test;
							test->next = _hoops_IHRAS;

							_hoops_IHRAS->_hoops_HPISA = test;
							++test->values;

							/* _hoops_HARS'_hoops_GRI _hoops_RPII _hoops_IIAC _hoops_HRHC - _hoops_HSPP _hoops_HCHAR _hoops_GICS */
							test = head;
						}
						else {
							_hoops_CHRAS = 0.5f * (_hoops_GIGAS->_hoops_AICR + _hoops_GIGAS->_hoops_RICR);
							_hoops_SHRAS = 0.5f * (_hoops_RHRAS->_hoops_AICR + _hoops_RHRAS->_hoops_RICR);

							if (_hoops_CHRAS < _hoops_SHRAS && test->_hoops_HPISA == null) {
								test->_hoops_HPISA = head; /* _hoops_RHAC _hoops_PIHA _hoops_PCSA _hoops_RGR... */
								++head->values;
							}
							else {
								/* '_hoops_HARS' _hoops_CGH _hoops_SHH _hoops_CPHR _hoops_RAS '_hoops_RPGP' */
								if ((_hoops_IHRAS = _hoops_SARAS (dc, head, test)) == null) break; /* _hoops_SPGC! */ 
								/* _hoops_HARS'_hoops_GRI _hoops_RPII _hoops_SRSS - _hoops_HSPP _hoops_HCHAR _hoops_GICS */
								test = head = _hoops_IHRAS;
							}
						}
					}
					else if ((result = HD_Cut_Hidden_By_Plane (dc, test, &_hoops_RHRAS->plane, true)) != 0) { 
						if (result != -1) {		
							/* _hoops_CPCP _hoops_CGH _hoops_GACHR _hoops_RPGP -> _hoops_HARS -> _hoops_RPGP->_hoops_SPS */
							test->next->_hoops_HPISA = head;
							++head->values;
							if ((_hoops_IHRAS = _hoops_SARAS (dc, head, test)) == null) 
								break;	/* _hoops_SPGC! */

							test = head = _hoops_IHRAS;
						}
						else {
							_hoops_CHRAS = 0.5f * (_hoops_GIGAS->_hoops_AICR + _hoops_GIGAS->_hoops_RICR);
							_hoops_SHRAS = 0.5f * (_hoops_RHRAS->_hoops_AICR + _hoops_RHRAS->_hoops_RICR);

							if (_hoops_CHRAS < _hoops_SHRAS && test->_hoops_HPISA == null) {
								test->_hoops_HPISA = head; /* _hoops_RHAC _hoops_PIHA _hoops_PCSA _hoops_RGR... */
								++head->values;
							}
							else {
								/* '_hoops_HARS' _hoops_CGH _hoops_SHH _hoops_CPHR _hoops_RAS '_hoops_RPGP' */
								if ((_hoops_IHRAS = _hoops_SARAS (dc, head, test)) == null) break; /* _hoops_SPGC! */ 
								/* _hoops_HARS'_hoops_GRI _hoops_RPII _hoops_SRSS - _hoops_HSPP _hoops_HCHAR _hoops_GICS */
								test = head = _hoops_IHRAS;
							}
						}
					}
					else {
#ifdef _hoops_CGSPR
							printf ("Skew/intersecting polygon confusion 2 - can't cut!\7\n");
#endif /* _hoops_SHRS */
						break;	/* _hoops_HGCR _hoops_GGSR _hoops_IIGR _hoops_ARI */
					}
				}
#endif /* _hoops_CHS _hoops_RIRAS */
			}
			else {
				/* '_hoops_HARS' _hoops_CGH _hoops_SHH _hoops_CPHR _hoops_RAS '_hoops_RPGP' */

				if ((_hoops_IHRAS = _hoops_SARAS (dc, head, test)) == null) 
					break;		/* _hoops_SPGC! */

				/* _hoops_HARS'_hoops_GRI _hoops_RPII _hoops_SRSS - _hoops_HSPP _hoops_HCHAR _hoops_GICS */
				test = head = _hoops_IHRAS;
			}
		}
	}

	if (head->values != 0)
		HD_Remove_Hidden_Followers (head, head->next); 

	*_hoops_GHRAS = _hoops_RCSHR;

	return head;
}

#endif





#if 0
#include <stdio.h>
#define _hoops_AIRAS
#endif
#if 0
#include <stdio.h>
#define _hoops_PIRAS
static float _hoops_HIRAS;
static float _hoops_IIRAS;
#endif

#define _hoops_CIRAS			100		/* _hoops_CCSHP _hoops_APSAR */
#define _hoops_SIRAS			5		/* _hoops_ASPA */

#define _hoops_GCRAS	0.2f	/* _hoops_IS _hoops_SHH _hoops_GHGC _hoops_HCAS */

#ifndef _hoops_CRHSA
local void _hoops_RCRAS (
	Display_Context const *		dc,
	_hoops_CASS alter *				_hoops_RCSHR,
	Int_Rectangle alter	*		scope,
	int							count);
#endif

local void _hoops_ACRAS (
	Display_Context const *		dc,
	_hoops_CASS alter *				hidden,
	Int_Rectangle alter	*		scope,
	int							count,
	int							level,
	float						_hoops_PCRAS,
	float						_hoops_HCRAS);



/****************/
/* _hoops_RAPCI _hoops_ICRAS */
/****************/
#define _hoops_CCRAS(hidden, count, _hoops_SCRAS) { \
	_hoops_CASS alter *	_hoops_GSRAS; \
	_hoops_GSRAS = hidden; \
	count = 0; _hoops_SCRAS = 0; \
	do { \
	++count; \
	if (hidden->_hoops_ASHSA->_hoops_APHGA->_hoops_CPP->_hoops_PRH._hoops_HRH) ++_hoops_SCRAS; \
	}_hoops_RGGA ((hidden = hidden->next) == null); \
	hidden = _hoops_GSRAS; \
}

#define _hoops_RSRAS(hidden,_hoops_ASRAS,_hoops_PSRAS) { \
	_hoops_CASS alter *	_hoops_GSRAS; \
	_hoops_GSRAS = hidden; \
	do { \
		if (hidden->_hoops_ASHSA->_hoops_RICR < _hoops_ASRAS) _hoops_ASRAS = hidden->_hoops_ASHSA->_hoops_RICR; \
		if (hidden->_hoops_ASHSA->_hoops_AICR > _hoops_PSRAS) _hoops_PSRAS = hidden->_hoops_ASHSA->_hoops_AICR; \
	} _hoops_RGGA ((hidden = hidden->next) == null); \
	hidden = _hoops_GSRAS; \
}

#define _hoops_HSRAS(hidden, min, max, _hoops_GGSSR, _hoops_ISRAS, _hoops_AGH, _hoops_CSRAS) { \
	_hoops_CASS alter *	_hoops_GSRAS; \
	_hoops_GSRAS = hidden; \
	do { \
		if ((hidden)->_hoops_ASHSA->max < (_hoops_GGSSR)-1) { \
			++(_hoops_ISRAS); \
		} \
		else if ((hidden)->_hoops_ASHSA->min > (_hoops_GGSSR)+1) { \
			++(_hoops_AGH); \
		} \
		else { \
			++(_hoops_ISRAS); \
			++(_hoops_AGH); \
			++(_hoops_CSRAS); \
		} \
	} _hoops_RGGA ((hidden = hidden->next) == null); \
	hidden = _hoops_GSRAS; \
}



local _hoops_CASS alter * _hoops_SSRAS (
	Display_Context const *		dc,
	_hoops_CASS alter *				old_item) {
	_hoops_CASS alter *				new_item;
	_hoops_SRHSA alter *		_hoops_PAHSA;
	_hoops_SRHSA alter *		_hoops_RAHSA = old_item->_hoops_ASHSA;

	POOL_ALLOC (new_item, _hoops_CASS, dc->memory_pool);
	_hoops_PAHSA = _hoops_RAHSA;
	_hoops_CAHS(_hoops_PAHSA);
	new_item->_hoops_ASHSA = _hoops_PAHSA;
	new_item->flags = HF_NONE;

	new_item->_hoops_HPISA = null;
	new_item->prev = null;
	new_item->values = 0;

	return new_item;
}

#define _hoops_GGAAS(dc, hidden, min, max, _hoops_GGSSR, _hoops_RGAAS, _hoops_AGAAS) { \
	do { \
		if ((hidden)->_hoops_ASHSA->max < (_hoops_GGSSR)-1) { \
			*(_hoops_RGAAS) = (hidden); \
			(_hoops_RGAAS) = &(hidden)->next; \
		} \
		else if ((hidden)->_hoops_ASHSA->min > (_hoops_GGSSR)+1) { \
			*(_hoops_AGAAS) = (hidden); \
			(_hoops_AGAAS) = &(hidden)->next; \
		} \
		else { \
			*(_hoops_RGAAS) = (hidden); \
			(_hoops_RGAAS) = &(hidden)->next; \
			*(_hoops_AGAAS) = _hoops_SSRAS (dc, (hidden)); \
			(_hoops_AGAAS) = &(*(_hoops_AGAAS))->next; \
		} \
	} _hoops_RGGA ((hidden = hidden->next) == null); \
}

#define _hoops_PGAAS(total,_hoops_GPRPH)	(((total))<((_hoops_GPRPH)*2))


#if 0
#define _hoops_HGAAS
#endif
#ifndef _hoops_HGAAS
local int _hoops_IGAAS (
	Display_Context const *	dc,
	_hoops_CASS alter **			_hoops_CGAAS,
	Int_Rectangle alter	*	scope,
	int						count,
	float					_hoops_PCRAS,
	float					_hoops_HCRAS) {
	_hoops_CASS alter *			hidden = *_hoops_CGAAS;
	_hoops_CASS alter *			_hoops_HPRS = hidden;
	_hoops_CASS alter *			_hoops_SAISA = null;
	_hoops_CASS alter *			_hoops_HHAHR = null;
	_hoops_CASS alter **			_hoops_SGAAS = null;
	_hoops_CASS alter *			_hoops_GRAAS = null;
	_hoops_SRHSA alter *	_hoops_ASHSA = hidden->_hoops_ASHSA;
	bool					_hoops_RRAAS = true;
	float					_hoops_ARAAS, _hoops_PRAAS, _hoops_HRAAS;
	int						_hoops_IRAAS = 0;
	int						_hoops_CRAAS = 0;
	int						_hoops_SRAAS = 0;
	int						n = 0;

	UNREFERENCED(count);
	UNREFERENCED(_hoops_PCRAS);
	UNREFERENCED(_hoops_HCRAS);

#ifdef _hoops_AIRAS
	printf("count: %d %d %d %d %d\n", count, 
			scope->left, scope->right, scope->bottom, scope->top);
#endif


	/*_hoops_RRHP _hoops_GAAAS _hoops_IAPRR*/
	do {
		_hoops_ASHSA = hidden->_hoops_ASHSA;
		if (!_hoops_HRCSA(_hoops_ASHSA->type)) 
			continue;

		if (_hoops_ASHSA->xmin <= scope->left && 
			_hoops_ASHSA->xmax >= scope->right &&
			_hoops_ASHSA->ymin <= scope->bottom && 
			_hoops_ASHSA->ymax >= scope->top &&
			!_hoops_ASHSA->_hoops_APHGA->_hoops_CPP->_hoops_PRH._hoops_HRH) {

			if (_hoops_ASHSA->type == _hoops_IPHSA) {
				DC_Point			*_hoops_HSPI, *_hoops_ISPI, *_hoops_CSPI;
				float				alpha, beta;
				float				_hoops_RAAAS, _hoops_AAAAS;
				float				_hoops_PAAAS, _hoops_HAAAS;
				float				_hoops_IAAAS, _hoops_CAAAS;

				_hoops_CRAAS++;

				_hoops_HSPI = &_hoops_ASHSA->points[0];
				_hoops_ISPI = &_hoops_ASHSA->points[1];
				_hoops_CSPI = &_hoops_ASHSA->points[2];

				_hoops_AAAAS = (float)scope->bottom - _hoops_HSPI->y;
				_hoops_CAAAS = _hoops_CSPI->y - _hoops_HSPI->y;
				_hoops_HAAAS = _hoops_ISPI->y - _hoops_HSPI->y;

				_hoops_RAAAS = (float)scope->left - _hoops_HSPI->x;
				_hoops_IAAAS = _hoops_CSPI->x - _hoops_HSPI->x;
				_hoops_PAAAS = _hoops_ISPI->x - _hoops_HSPI->x;

				if (_hoops_PAAAS != 0.0f) {
					beta = (_hoops_CAAAS*_hoops_PAAAS - _hoops_IAAAS*_hoops_HAAAS);
					if (beta == 0.0f)
						continue;
					beta = (_hoops_AAAAS*_hoops_PAAAS - _hoops_RAAAS*_hoops_HAAAS) / beta;
					/* _hoops_GIRCC>1 _hoops_HRIRR _hoops_AIIR<0 _hoops_IS _hoops_HGCR (_hoops_AIIR+_hoops_GIRCC)<=1 */
					if (beta < 0.0f || beta > 1.0f)
						continue;
					alpha = (_hoops_RAAAS - beta * _hoops_IAAAS) / _hoops_PAAAS;
				}
				else if (_hoops_HAAAS != 0.0f && _hoops_IAAAS != 0.0f) {
					/* _hoops_RGR _hoops_AGIR _hoops_SAHR _hoops_HACAR _hoops_AIAA _hoops_SRRRH, _hoops_HIH _hoops_HRGR _hoops_RCGRA _hoops_IS _hoops_RH _hoops_ARRS. */
					beta = _hoops_RAAAS / _hoops_IAAAS;
					if (beta < 0.0f || beta > 1.0f)
						continue;
					alpha = (_hoops_AAAAS - beta * _hoops_CAAAS) / _hoops_HAAAS;
				}
				else
					continue;

				if (!(alpha > 0.0f && (alpha + beta) <= 1.0f))
					continue;


				_hoops_AAAAS = (float)scope->top - _hoops_HSPI->y;
				_hoops_CAAAS = _hoops_CSPI->y - _hoops_HSPI->y;
				_hoops_HAAAS = _hoops_ISPI->y - _hoops_HSPI->y;

				_hoops_RAAAS = (float)scope->left - _hoops_HSPI->x;
				_hoops_IAAAS = _hoops_CSPI->x - _hoops_HSPI->x;
				_hoops_PAAAS = _hoops_ISPI->x - _hoops_HSPI->x;

				if (_hoops_PAAAS != 0.0f) {
					beta = (_hoops_CAAAS*_hoops_PAAAS - _hoops_IAAAS*_hoops_HAAAS);
					if (beta == 0.0f)
						continue;
					beta = (_hoops_AAAAS*_hoops_PAAAS - _hoops_RAAAS*_hoops_HAAAS) / beta;
					/* _hoops_GIRCC>1 _hoops_HRIRR _hoops_AIIR<0 _hoops_IS _hoops_HGCR (_hoops_AIIR+_hoops_GIRCC)<=1 */
					if (beta < 0.0f || beta > 1.0f)
						continue;
					alpha = (_hoops_RAAAS - beta * _hoops_IAAAS) / _hoops_PAAAS;
				}
				else if (_hoops_HAAAS != 0.0f && _hoops_IAAAS != 0.0f) {
					/* _hoops_RGR _hoops_AGIR _hoops_SAHR _hoops_HACAR _hoops_AIAA _hoops_SRRRH, _hoops_HIH _hoops_HRGR _hoops_RCGRA _hoops_IS _hoops_RH _hoops_ARRS. */
					beta = _hoops_RAAAS / _hoops_IAAAS;
					if (beta < 0.0f || beta > 1.0f)
						continue;
					alpha = (_hoops_AAAAS - beta * _hoops_CAAAS) / _hoops_HAAAS;
				}
				else
					continue;

				if (!(alpha > 0.0f && (alpha + beta) <= 1.0f))
					continue;


				_hoops_AAAAS = (float)scope->bottom - _hoops_HSPI->y;
				_hoops_CAAAS = _hoops_CSPI->y - _hoops_HSPI->y;
				_hoops_HAAAS = _hoops_ISPI->y - _hoops_HSPI->y;

				_hoops_RAAAS = (float)scope->right - _hoops_HSPI->x;
				_hoops_IAAAS = _hoops_CSPI->x - _hoops_HSPI->x;
				_hoops_PAAAS = _hoops_ISPI->x - _hoops_HSPI->x;

				if (_hoops_PAAAS != 0.0f) {
					beta = (_hoops_CAAAS*_hoops_PAAAS - _hoops_IAAAS*_hoops_HAAAS);
					if (beta == 0.0f)
						continue;
					beta = (_hoops_AAAAS*_hoops_PAAAS - _hoops_RAAAS*_hoops_HAAAS) / beta;
					/* _hoops_GIRCC>1 _hoops_HRIRR _hoops_AIIR<0 _hoops_IS _hoops_HGCR (_hoops_AIIR+_hoops_GIRCC)<=1 */
					if (beta < 0.0f || beta > 1.0f)
						continue;
					alpha = (_hoops_RAAAS - beta * _hoops_IAAAS) / _hoops_PAAAS;
				}
				else if (_hoops_HAAAS != 0.0f && _hoops_IAAAS != 0.0f) {
					/* _hoops_RGR _hoops_AGIR _hoops_SAHR _hoops_HACAR _hoops_AIAA _hoops_SRRRH, _hoops_HIH _hoops_HRGR _hoops_RCGRA _hoops_IS _hoops_RH _hoops_ARRS. */
					beta = _hoops_RAAAS / _hoops_IAAAS;
					if (beta < 0.0f || beta > 1.0f)
						continue;
					alpha = (_hoops_AAAAS - beta * _hoops_CAAAS) / _hoops_HAAAS;
				}
				else
					continue;

				if (!(alpha > 0.0f && (alpha + beta) <= 1.0f))
					continue;


				_hoops_AAAAS = (float)scope->top - _hoops_HSPI->y;
				_hoops_CAAAS = _hoops_CSPI->y - _hoops_HSPI->y;
				_hoops_HAAAS = _hoops_ISPI->y - _hoops_HSPI->y;

				_hoops_RAAAS = (float)scope->right - _hoops_HSPI->x;
				_hoops_IAAAS = _hoops_CSPI->x - _hoops_HSPI->x;
				_hoops_PAAAS = _hoops_ISPI->x - _hoops_HSPI->x;

				if (_hoops_PAAAS != 0.0f) {
					beta = (_hoops_CAAAS*_hoops_PAAAS - _hoops_IAAAS*_hoops_HAAAS);
					if (beta == 0.0f)
						continue;
					beta = (_hoops_AAAAS*_hoops_PAAAS - _hoops_RAAAS*_hoops_HAAAS) / beta;
					/* _hoops_GIRCC>1 _hoops_HRIRR _hoops_AIIR<0 _hoops_IS _hoops_HGCR (_hoops_AIIR+_hoops_GIRCC)<=1 */
					if (beta < 0.0f || beta > 1.0f)
						continue;
					alpha = (_hoops_RAAAS - beta * _hoops_IAAAS) / _hoops_PAAAS;
				}
				else if (_hoops_HAAAS != 0.0f && _hoops_IAAAS != 0.0f) {
					/* _hoops_RGR _hoops_AGIR _hoops_SAHR _hoops_HACAR _hoops_AIAA _hoops_SRRRH, _hoops_HIH _hoops_HRGR _hoops_RCGRA _hoops_IS _hoops_RH _hoops_ARRS. */
					beta = _hoops_RAAAS / _hoops_IAAAS;
					if (beta < 0.0f || beta > 1.0f)
						continue;
					alpha = (_hoops_AAAAS - beta * _hoops_CAAAS) / _hoops_HAAAS;
				}
				else
					continue;

				if (!(alpha > 0.0f && (alpha + beta) <= 1.0f))
					continue;

				_hoops_GRAAS = hidden; 
			}
			else {
				_hoops_SRAAS++;
			}
		}
	} while ((hidden = hidden->next) != null); 

	if (_hoops_GRAAS) {
		hidden = _hoops_HPRS;
		_hoops_ASHSA = hidden->_hoops_ASHSA;
		_hoops_SAISA = null;
		_hoops_SGAAS = &_hoops_SAISA;

		_hoops_ARAAS = _hoops_GRAAS->_hoops_ASHSA->_hoops_AICR;

		_hoops_RRAAS = false;

		while (hidden) {
			_hoops_ASHSA = hidden->_hoops_ASHSA;
			if (_hoops_ASHSA->_hoops_RICR > _hoops_ARAAS) {
				if (_hoops_ASHSA->type == _hoops_IPHSA) _hoops_CRAAS--;
				_hoops_HPRS = hidden->next;
				hidden->next = null;
				HD_Free_Hidden_List(dc, hidden); 
				hidden = _hoops_HPRS;
				n++;
			}
			else {
				if (_hoops_ASHSA->type == _hoops_AHHSA)
					_hoops_RRAAS = true;

				*_hoops_SGAAS = hidden;
				_hoops_SGAAS = &hidden->next; 
				hidden = hidden->next;
			}
		}

		*_hoops_SGAAS = null;
		*_hoops_CGAAS = _hoops_SAISA;
	}

	hidden = *_hoops_CGAAS;
	_hoops_ASHSA = hidden->_hoops_ASHSA;
	_hoops_HPRS = *_hoops_CGAAS;

	/* _hoops_SCH _hoops_PHPP _hoops_SGS _hoops_RH _hoops_HGGS _hoops_PPR _hoops_III _hoops_IAPRR _hoops_CHR _hoops_HAR _hoops_GHGC _hoops_SCH _hoops_GGR _hoops_ICRP _hoops_ARAR */
	/* _hoops_IRS _hoops_IGRH _hoops_HHS _hoops_SHH _hoops_RRAI _hoops_IS _hoops_AGSGR _hoops_SCH _hoops_GPP _hoops_GAAP _hoops_IH _hoops_CGGPR _hoops_RGHR _hoops_IGIR */
	/* _hoops_SAAAS _hoops_PSP _hoops_IAPRR: 3842376  _hoops_PSP _hoops_HGGS _hoops_PAR _hoops_III: 2490171  _hoops_HCR _hoops_IAPRR: 809967 */
	/* _hoops_RH _hoops_RRGR _hoops_RHAP _hoops_AHGS _hoops_IS _hoops_IPHR _hoops_HIH _hoops_HRGR _hoops_GPAAS _hoops_RPAAS _hoops_PPR _hoops_HAR _hoops_SGS _hoops_CGRIR */
	if (1 || BIT(_hoops_ASHSA->_hoops_APHGA->_hoops_IRR->_hoops_GSSIR,_hoops_AGAAP)) {
#ifdef _hoops_AIRAS
		printf("removed: %d from: %d\n", n, count);
#endif
		return n;
	}

	_hoops_PRAAS = scope->right - scope->left + 1.0f;
	_hoops_HRAAS = scope->top - scope->bottom + 1.0f;
	_hoops_IRAAS = int (_hoops_PRAAS * _hoops_HRAAS);

	/* _hoops_III _hoops_IAPRR */
	if (_hoops_RRAAS) {
		float 	_hoops_APAAS = _hoops_PRAAS*0.6f;
		float 	_hoops_PPAAS = _hoops_HRAAS*0.6f;
		float 	_hoops_HPAAS = _hoops_APAAS*_hoops_APAAS+_hoops_PPAAS*_hoops_PPAAS;
		float 	_hoops_IPAAS = (scope->left + scope->right)/2.0f;
		float 	_hoops_CPAAS = (scope->bottom + scope->top)/2.0f;

#ifdef _hoops_AIRAS
	printf("line test: %f %f %f %d\n", _hoops_HPAAS, _hoops_IPAAS, _hoops_CPAAS, _hoops_IRAAS);
#endif
		do {
			hidden->values = _hoops_IRAAS;

			if (_hoops_ASHSA->type == _hoops_AHHSA) {
				DC_Point *_hoops_HSPI, *_hoops_ISPI;
				Point _hoops_RRASA, _hoops_HIHHA, _hoops_PIAIA;
				float	_hoops_SSHGA,dist,t;

				_hoops_HSPI = &_hoops_ASHSA->points[0];
				_hoops_ISPI = &_hoops_ASHSA->points[1];

				_hoops_RRASA.x = _hoops_HSPI->x-_hoops_IPAAS;
				_hoops_RRASA.y = _hoops_HSPI->y-_hoops_CPAAS;

				_hoops_HIHHA.x = _hoops_ISPI->x-_hoops_HSPI->x;
				_hoops_HIHHA.y = _hoops_ISPI->y-_hoops_HSPI->y;

				_hoops_SSHGA = _hoops_HIHHA.x*_hoops_HIHHA.x + _hoops_HIHHA.y*_hoops_HIHHA.y;

				if (_hoops_SSHGA > 0.00001f) 
					t = -(_hoops_RRASA.x*_hoops_HIHHA.x+_hoops_RRASA.y*_hoops_HIHHA.y)/_hoops_SSHGA;
				else
					t = 0;

				if (t > 1.0f) t=1.0f;
				if (t < 0.0f) t=0.0f;
				_hoops_PIAIA.x = _hoops_RRASA.x + t*_hoops_HIHHA.x;
				_hoops_PIAIA.y = _hoops_RRASA.y + t*_hoops_HIHHA.y;
				dist = _hoops_PIAIA.x*_hoops_PIAIA.x + _hoops_PIAIA.y*_hoops_PIAIA.y;

				if (dist > _hoops_HPAAS) {
					hidden->values = 0;
				}
			}
		} while ((hidden = hidden->next) != null); 

		hidden = _hoops_HPRS;
	}

	/*_hoops_HGGS _hoops_HPSRR _hoops_IAPRR*/
	if (_hoops_CRAAS > 0) {
		int x, y;

		_hoops_HHAHR = hidden;
		_hoops_HHAHR->prev = null;

		while ((hidden = hidden->next) != null) {
			if (!_hoops_RRAAS) 
				hidden->values = _hoops_IRAAS;

			hidden->prev=_hoops_HHAHR;
			_hoops_HHAHR=hidden;
		} 

		_hoops_HPRS = *_hoops_CGAAS;

		for (x=scope->left; x<=scope->right; x++) {
			for (y=scope->bottom; y<=scope->top; y++) {
#define _hoops_SPAAS 5
				_hoops_CASS *	_hoops_GHAAS[_hoops_SPAAS] = {0,0,0,0,0};
				float		_hoops_RHAAS[_hoops_SPAAS] = {MAX_FLOAT, MAX_FLOAT, MAX_FLOAT, MAX_FLOAT, MAX_FLOAT};
				float		_hoops_AHAAS[_hoops_SPAAS][2] = {{0.0f, 0.0f}, {-0.5f, -0.5f}, {0.5f, -0.5f}, {-0.5f, 0.5f}, {0.5f, 0.5f}}; 
				float		_hoops_PHAAS = 0.0f;
				int			i;

				hidden = _hoops_HHAHR;

				do {
					for (i=0; i<_hoops_SPAAS; i++) 
						if (_hoops_ASHSA->_hoops_RICR > _hoops_RHAAS[i]) break;

					if (_hoops_ASHSA->type == _hoops_IPHSA &&
						!_hoops_ASHSA->_hoops_APHGA->_hoops_CPP->_hoops_PRH._hoops_HRH) {
						DC_Point		*_hoops_HSPI, *_hoops_ISPI, *_hoops_CSPI;
						float			alpha, beta;
						float			_hoops_RAAAS, _hoops_AAAAS;
						float			_hoops_PAAAS, _hoops_HAAAS;
						float			_hoops_IAAAS, _hoops_CAAAS;
						float			z;

						_hoops_HSPI = &_hoops_ASHSA->points[0];
						_hoops_ISPI = &_hoops_ASHSA->points[1];
						_hoops_CSPI = &_hoops_ASHSA->points[2];

						for (i=0; i<_hoops_SPAAS; i++) {
							_hoops_AAAAS = y + _hoops_AHAAS[i][0] - _hoops_HSPI->y;
							_hoops_CAAAS = _hoops_CSPI->y - _hoops_HSPI->y;
							_hoops_HAAAS = _hoops_ISPI->y - _hoops_HSPI->y;

							_hoops_RAAAS = x - _hoops_AHAAS[i][1] - _hoops_HSPI->x;
							_hoops_IAAAS = _hoops_CSPI->x - _hoops_HSPI->x;
							_hoops_PAAAS = _hoops_ISPI->x - _hoops_HSPI->x;

							if (_hoops_PAAAS != 0.0f) {
								beta = (_hoops_CAAAS*_hoops_PAAAS - _hoops_IAAAS*_hoops_HAAAS);
								if (beta == 0.0f)
									continue;
								beta = (_hoops_AAAAS*_hoops_PAAAS - _hoops_RAAAS*_hoops_HAAAS) / beta;
								/* _hoops_GIRCC>1 _hoops_HRIRR _hoops_AIIR<0 _hoops_IS _hoops_HGCR (_hoops_AIIR+_hoops_GIRCC)<=1 */
								if (beta < 0.0f || beta > 1.0f)
									continue;
								alpha = (_hoops_RAAAS - beta * _hoops_IAAAS) / _hoops_PAAAS;
							}
							else if (_hoops_HAAAS != 0.0f && _hoops_IAAAS != 0.0f) {
								/* _hoops_RGR _hoops_AGIR _hoops_SAHR _hoops_HACAR _hoops_AIAA _hoops_SRRRH, _hoops_HIH _hoops_HRGR _hoops_RCGRA _hoops_IS _hoops_RH _hoops_ARRS. */
								beta = _hoops_RAAAS / _hoops_IAAAS;
								if (beta < 0.0f || beta > 1.0f)
									continue;
								alpha = (_hoops_AAAAS - beta * _hoops_CAAAS) / _hoops_HAAAS;
							}
							else
								continue;

							if (!(alpha > 0.0f && (alpha + beta) <= 1.0f))
								continue;

							z = (_hoops_ASHSA->plane.a * (float)x + _hoops_ASHSA->plane.b * (float)y + _hoops_ASHSA->plane.d) / -_hoops_ASHSA->plane.c;

							if (z < _hoops_RHAAS[i]) {
								_hoops_GHAAS[i] = hidden;
								_hoops_RHAAS[i] = z;
							}
						}
					}
				} while ((hidden = hidden->prev) != null); 

				hidden = _hoops_HHAHR;

				/* _hoops_IIRRC _hoops_RPP _hoops_IRS _hoops_HHAAS _hoops_AIR _hoops_HRGR _hoops_GSGI */
				for (i=0; i<_hoops_SPAAS; i++) {
					if (!_hoops_GHAAS[i]) goto _hoops_IHAAS;

					/* _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_CHAAS _hoops_AARI */
					_hoops_GHAAS[i]->values = _hoops_IRAAS+1;

					if (_hoops_RHAAS[i] > _hoops_PHAAS) 
						_hoops_PHAAS = _hoops_RHAAS[i];
				}

				/*_hoops_GGCR 10% _hoops_GAR _hoops_CCPCR _hoops_SIPIR*/
				/*
				_hoops_SHAAS += (_hoops_GIAAS-_hoops_RIAAS)*0.01f;
				*/

				do {
					_hoops_ASHSA = hidden->_hoops_ASHSA;
					if (_hoops_ASHSA->_hoops_RICR > _hoops_PHAAS) {
						hidden->values--;
#ifdef _hoops_AIRAS
						if (hidden->values == 0)
							printf("rayculling %f %f\n", _hoops_PHAAS, hidden->_hoops_RICR);
#endif
					}
				} while ((hidden = hidden->prev) != null); 
			}
		}
	}

_hoops_IHAAS:

	hidden = _hoops_HPRS;
	_hoops_SAISA = null;
	_hoops_SGAAS = &_hoops_SAISA;

	while (hidden) {
		if (hidden->values<=0) {
			_hoops_HPRS = hidden->next;
			hidden->next  =null;
			HD_Free_Hidden_List(dc, hidden); 
			hidden = _hoops_HPRS;
			n++;
		}
		else {
			*_hoops_SGAAS = hidden;
			_hoops_SGAAS = &hidden->next; 
			hidden->prev = null;
			hidden->values = 0;
			hidden = hidden->next;
		}
	}

	*_hoops_SGAAS = null;
	*_hoops_CGAAS = _hoops_SAISA;

#ifdef _hoops_AIRAS
	printf("removed: %d from: %d\n", n, count);
#endif

	return n;
}
#else
#define _hoops_IGAAS(dc,a,b,c,_hoops_RPSC,_hoops_CGSAA) 0
#endif

#ifndef _hoops_CRHSA

local void _hoops_ACRAS (
	Display_Context const *	dc,
	_hoops_CASS alter *			hidden,
	Int_Rectangle alter	*	scope,
	int						count,
	int						level,
	float					_hoops_PCRAS,
	float					_hoops_HCRAS) {
	_hoops_CASS alter			*_hoops_AIAAS, *_hoops_PIAAS, 
							**_hoops_RGAAS = &_hoops_AIAAS, 
							**_hoops_AGAAS = &_hoops_PIAAS;
	Int_Rectangle			_hoops_HCRRH;
	int						_hoops_CSRAS = 0, _hoops_ISRAS = 0, _hoops_AGH = 0;
	int						_hoops_GGSSR;


	/* _hoops_ISPR _hoops_PPR _hoops_SHSP _hoops_HHCI */
	if (_hoops_GGPGR(hidden->_hoops_ASHSA->_hoops_APHGA)) {
		HD_Free_Hidden_List (dc, hidden); 
		return;
	}

	if (count == 0) {
		return;
	}
	else if (count < _hoops_CIRAS) {
		count -= _hoops_IGAAS(dc, &hidden, scope, count, _hoops_PCRAS, _hoops_HCRAS); 
		_hoops_RCRAS (dc, hidden, scope, count); 
		return;
	}
	else if ((level & 0x1) && ((scope->right - scope->left) >= _hoops_SIRAS)) {
_hoops_HIAAS:
		_hoops_GGSSR = ((scope->right + scope->left) / 2);

		_hoops_HSRAS(hidden, xmin, xmax, _hoops_GGSSR, _hoops_ISRAS, _hoops_AGH, _hoops_CSRAS);

#if 0
#ifdef _hoops_AIRAS
printf("X lc mmm lrbt quadratize_and_draw %d %d %d %d %d %d %d %d %d\n", 
	level, count, 
	_hoops_ISRAS, _hoops_AGH, _hoops_CSRAS,
	scope->left, scope->right, scope->bottom, scope->top);
#endif
#endif

		if (_hoops_PGAAS(count, _hoops_CSRAS)) {
			count -= _hoops_IGAAS(dc, &hidden, scope, count, _hoops_PCRAS, _hoops_HCRAS); 
			_hoops_RCRAS (dc, hidden, scope, count); 
			return;
		}

		_hoops_GGAAS(dc, hidden, xmin, xmax, _hoops_GGSSR, _hoops_RGAAS, _hoops_AGAAS);

		*_hoops_RGAAS = null;
		*_hoops_AGAAS = null;

		_hoops_HCRRH.bottom = scope->bottom;
		_hoops_HCRRH.top = scope->top;

		if (_hoops_AIAAS) {
			_hoops_HCRRH.left = scope->left;
			_hoops_HCRRH.right = _hoops_GGSSR;
			_hoops_ACRAS (dc, _hoops_AIAAS, &_hoops_HCRRH, _hoops_ISRAS, level + 1, _hoops_PCRAS, _hoops_HCRAS);
		}

		if (_hoops_PIAAS) {
			_hoops_HCRRH.left = _hoops_GGSSR+1;
			_hoops_HCRRH.right = scope->right;
			_hoops_ACRAS (dc, _hoops_PIAAS, &_hoops_HCRRH, _hoops_AGH, level + 1, _hoops_PCRAS, _hoops_HCRAS);
		}
	}
	else if ((scope->top - scope->bottom) >= _hoops_SIRAS) {
		_hoops_GGSSR = ((scope->top + scope->bottom) / 2);

		_hoops_HSRAS(hidden, ymin, ymax, _hoops_GGSSR, _hoops_ISRAS, _hoops_AGH, _hoops_CSRAS);

#if 0
#ifdef _hoops_AIRAS
printf("Y lc mmm lrbt quadratize_and_draw %d %d %d %d %d %d %d %d %d\n", 
	level, count, 
	_hoops_ISRAS, _hoops_AGH, _hoops_CSRAS,
	scope->left, scope->right, scope->bottom, scope->top);
#endif
#endif

		if (_hoops_PGAAS(count, _hoops_CSRAS)) {
			count -= _hoops_IGAAS(dc, &hidden, scope, count, _hoops_PCRAS, _hoops_HCRAS); 
			_hoops_RCRAS (dc, hidden, scope, count); 
			return;
		}

		_hoops_GGAAS(dc, hidden, ymin, ymax, _hoops_GGSSR, _hoops_RGAAS, _hoops_AGAAS);

		*_hoops_RGAAS = null;
		*_hoops_AGAAS = null;

		_hoops_HCRRH.left = scope->left;
		_hoops_HCRRH.right = scope->right;

		if (_hoops_AIAAS) {
			_hoops_HCRRH.bottom = scope->bottom;
			_hoops_HCRRH.top = _hoops_GGSSR;
			_hoops_ACRAS (dc, _hoops_AIAAS, &_hoops_HCRRH, _hoops_ISRAS, level + 1, _hoops_PCRAS, _hoops_HCRAS);
		}

		if (_hoops_PIAAS) {
			_hoops_HCRRH.bottom = _hoops_GGSSR+1;
			_hoops_HCRRH.top = scope->top;
			_hoops_ACRAS (dc, _hoops_PIAAS, &_hoops_HCRRH, _hoops_AGH, level + 1, _hoops_PCRAS, _hoops_HCRAS);
		}
	}
	else if ((scope->right - scope->left) >= _hoops_SIRAS) {
		goto _hoops_HIAAS;
	}
	else {
		count -= _hoops_IGAAS(dc, &hidden, scope, count, _hoops_PCRAS, _hoops_HCRAS); 
		_hoops_RCRAS (dc, hidden, scope, count); 
		return;
	}	
}

#ifdef _hoops_AIRAS
static int _hoops_IIAAS=0;
#endif

local void _hoops_RCRAS (
	Display_Context const *		dc,
	_hoops_CASS alter *				_hoops_CIAAS,
	Int_Rectangle alter *		scope,
	int							count) {
	_hoops_CASS alter *				_hoops_RCSHR = _hoops_CIAAS;
	_hoops_CASS alter *				hidden;
	_hoops_CASS alter *				_hoops_IAISA;
	Net_Rendition				_hoops_ACRIP;
	Net_Rendition				_hoops_RHICP;
	_hoops_HHCR			_hoops_SIAAS;
	_hoops_HHCR			_hoops_GCAAS;
	_hoops_HHCR			_hoops_AHICP;


	if (count == 0) 
		return;

#ifdef _hoops_AIRAS
	_hoops_IIAAS+=count;
	printf("c lrbt full_sort_and_draw %d %d %d %d %d\n", count,
		scope->left, scope->right, scope->bottom, scope->top);
#endif

#ifdef _hoops_PIRAS
{
	_hoops_CASS alter *_hoops_HPRS;
	DC_Point		*_hoops_HSPI, *_hoops_ISPI, *_hoops_CSPI;
	static int first=1;

#define _hoops_RCAAS(z) ((z)-_hoops_HIRAS)

	hidden = _hoops_RCSHR;

	if (first) {
		float r,g,b;
		printf(";; HMF V1.24 TEXT\n(Visibility \"edges = off\")\n");
		r=1.0f;g=0.0f;b=0.0f;
		printf("(Segment \"red\" ((Color_By_Value \"Line,Face\" \"RGB\" %f %f %f)))\n", r,g,b);
		r=0.0f;g=1.0f;b=0.0f;
		printf("(Segment \"green\" ((Color_By_Value \"Line,Face\" \"RGB\" %f %f %f)))\n", r,g,b);
		r=0.0f;g=0.0f;b=1.0f;
		printf("(Segment \"blue\" ((Color_By_Value \"Line,Face\" \"RGB\" %f %f %f)))\n", r,g,b);
		first=0;
	}

	printf("(Segment \"blue\" (");
	printf("(Polyline ((%f %f %f) (%f %f %f) (%f %f %f) (%f %f %f) (%f %f %f)))))\n",
		(float)scope->left, (float)scope->bottom, 0.0f,
		(float)scope->left, (float)scope->top, 0.0f,
		(float)scope->right, (float)scope->top, 0.0f,
		(float)scope->right, (float)scope->bottom, 0.0f,
		(float)scope->left, (float)scope->bottom, 0.0f);

	while (hidden) {
		if (hidden->type == _hoops_IPHSA) {
			_hoops_HSPI = &hidden->points[0];
			_hoops_ISPI = &hidden->points[1];
			_hoops_CSPI = &hidden->points[2];

			printf("(Segment \"red\" (");
			printf("(Polygon ((%f %f %f) (%f %f %f) (%f %f %f)))))\n",
					_hoops_HSPI->x, _hoops_HSPI->y, _hoops_RCAAS(_hoops_HSPI->z),
					_hoops_ISPI->x, _hoops_ISPI->y, _hoops_RCAAS(_hoops_ISPI->z),
					_hoops_CSPI->x, _hoops_CSPI->y, _hoops_RCAAS(_hoops_CSPI->z));

		}
		else if (hidden->type == _hoops_AHHSA) {
			_hoops_HSPI = &hidden->points[0];
			_hoops_ISPI = &hidden->points[1];

			printf("(Segment \"green\" (");
			printf("(Polyline ((%f %f %f) (%f %f %f)))))\n",
					_hoops_HSPI->x, _hoops_HSPI->y, _hoops_RCAAS(_hoops_HSPI->z),
					_hoops_ISPI->x, _hoops_ISPI->y, _hoops_RCAAS(_hoops_ISPI->z));

		}

		hidden = hidden->next;
	}

	hidden = _hoops_HPRS;
}

#endif

	/* _hoops_SSS _hoops_RH _hoops_SPS _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_PGSA _hoops_SCH, _hoops_PPR _hoops_CIH _hoops_SCH. */
	_hoops_ACRIP = _hoops_RCSHR->_hoops_ASHSA->_hoops_APHGA;
	_hoops_SIAAS = _hoops_ACRIP->transform_rendition;
	_hoops_RHICP = _hoops_ACRIP;
	_hoops_AHICP = _hoops_RHICP.Modify()->transform_rendition.Modify();

	if (!BIT (_hoops_AHICP->heuristics, _hoops_HRIRP)) {
		bool		_hoops_CCCIR = false;

		if (scope->left > _hoops_AHICP->_hoops_AGAA.left) {
			_hoops_AHICP->_hoops_AGAA.left = scope->left;
			_hoops_CCCIR = true;
		}
		if (scope->right < _hoops_AHICP->_hoops_AGAA.right) {
			_hoops_AHICP->_hoops_AGAA.right = scope->right;
			_hoops_CCCIR = true;
		}
		if (scope->bottom > _hoops_AHICP->_hoops_AGAA.bottom) {
			_hoops_AHICP->_hoops_AGAA.bottom = scope->bottom;
			_hoops_CCCIR = true;
		}
		if (scope->top < _hoops_AHICP->_hoops_AGAA.top) {
			_hoops_AHICP->_hoops_AGAA.top = scope->top;
			_hoops_CCCIR = true;
		}

		if (_hoops_CCCIR)
			_hoops_AHICP->flags &= ~_hoops_AIHS;
	}

	_hoops_GCAAS = _hoops_SIAAS;
	hidden = null;

	_hoops_PCCAR {
		hidden = _hoops_SPRAS (dc, hidden, &_hoops_RCSHR); 
		
		_hoops_ACRIP = hidden->_hoops_ASHSA->_hoops_APHGA;
		_hoops_SIAAS = _hoops_ACRIP->transform_rendition;

		if (_hoops_ACRIP->_hoops_AHP != _hoops_RHICP->_hoops_AHP ||
			_hoops_ACRIP->_hoops_IHA != _hoops_RHICP->_hoops_IHA ||
			_hoops_ACRIP->_hoops_RHP != _hoops_RHICP->_hoops_RHP ||
			_hoops_ACRIP->_hoops_GSP != _hoops_RHICP->_hoops_GSP ||
			_hoops_ACRIP->_hoops_SISI != _hoops_RHICP->_hoops_SISI ||
			_hoops_ACRIP->_hoops_ASIR != _hoops_RHICP->_hoops_ASIR ||
			_hoops_ACRIP->_hoops_IRR != _hoops_RHICP->_hoops_IRR ||
			_hoops_SIAAS != _hoops_GCAAS) {

			_hoops_HHCR		_hoops_ACAAS = _hoops_AHICP; // _hoops_CRCC _hoops_SCH _hoops_IH _hoops_PCAAS _hoops_SAHR _hoops_CAPP

			_hoops_RHICP = _hoops_ACRIP;
			_hoops_RHICP.Modify()->transform_rendition = _hoops_AHICP; 

			if (_hoops_SIAAS != _hoops_GCAAS) {
				_hoops_AHICP = _hoops_SIAAS.Copy();
				if (!BIT (_hoops_AHICP->heuristics, _hoops_HRIRP)) {
					bool						_hoops_CCCIR = false;

					if (scope->left > _hoops_AHICP->_hoops_AGAA.left) {
						_hoops_AHICP->_hoops_AGAA.left = scope->left;
						_hoops_CCCIR = true;
					}
					if (scope->right < _hoops_AHICP->_hoops_AGAA.right) {
						_hoops_AHICP->_hoops_AGAA.right = scope->right;
						_hoops_CCCIR = true;
					}
					if (scope->bottom > _hoops_AHICP->_hoops_AGAA.bottom) {
						_hoops_AHICP->_hoops_AGAA.bottom = scope->bottom;
						_hoops_CCCIR = true;
					}
					if (scope->top < _hoops_AHICP->_hoops_AGAA.top) {
						_hoops_AHICP->_hoops_AGAA.top = scope->top;
						_hoops_CCCIR = true;
					}

					if (_hoops_CCCIR)
						_hoops_AHICP->flags &= ~_hoops_AIHS;
				}
				_hoops_RHICP->transform_rendition = _hoops_AHICP;

				_hoops_GCAAS = _hoops_SIAAS;
			}
		}



		if (_hoops_AHICP->_hoops_AGAA.left < _hoops_AHICP->_hoops_AGAA.right &&
			_hoops_AHICP->_hoops_AGAA.bottom < _hoops_AHICP->_hoops_AGAA.top) {

			hidden->_hoops_ASHSA->_hoops_APHGA = _hoops_RHICP;

			HD_Draw_Hidden_Item (hidden, false); 

			hidden->_hoops_ASHSA->_hoops_APHGA = _hoops_ACRIP;
		}

		/* _hoops_RHAPA _hoops_RGR _hoops_SPR _hoops_HII _hoops_RH _hoops_CISI _hoops_HIGR */
		_hoops_IAISA = hidden;
		hidden = hidden->next;

		if (_hoops_IAISA != hidden) {
			/* _hoops_RH _hoops_CISI _hoops_HIGR _hoops_HRGR _hoops_GRAA-_hoops_RHPA; _hoops_HCAAS _hoops_RH _hoops_CICRR */
			hidden->prev = _hoops_IAISA->prev;
			_hoops_IAISA->prev->next = hidden;
		}
		else {
			/* _hoops_RH _hoops_CISI _hoops_HIGR _hoops_HRGR _hoops_RHPA _hoops_HA */
			hidden = null;

			if (_hoops_RCSHR == null) {
				/* _hoops_RH _hoops_RCAPR _hoops_HIGR _hoops_HRGR _hoops_RHPA _hoops_HAH. */
				/* _hoops_PS'_hoops_ASAR _hoops_ICAAS _hoops_ARI. */
				_hoops_IAISA->next = null; 
				HD_Free_Hidden_List (dc, _hoops_IAISA); 
				break;
			}
		}

		_hoops_IAISA->next = null; 
		HD_Free_Hidden_List (dc, _hoops_IAISA); 

		if (_hoops_GGPGR(_hoops_RHICP)) {
			/* _hoops_CCAAS - _hoops_SHSP _hoops_HHCI */

			if (_hoops_RCSHR != null)
				HD_Free_Hidden_List (dc, _hoops_RCSHR); 

			if (hidden != null) {
				hidden->prev->next = null;	 /* _hoops_CPAII-_hoops_SCAAS _hoops_RH _hoops_HIGR */
				HD_Free_Hidden_List (dc, hidden); 
			}

			break;
		}
	}
	if (_hoops_RHICP->_hoops_SRA->_hoops_SPSIP)
		HD_Flush_Hidden_Item_Cache ((Display_Context alter *)_hoops_RHICP->_hoops_SRA);
}

#endif


GLOBAL_FUNCTION void HD_See_Whats_Hidden (
	Net_Rendition const &		nr) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
#ifndef DISABLE_SORTING_HSR
	_hoops_CASS alter *				_hoops_RCSHR = null;
	bool						_hoops_GSAAS = false;
	_hoops_SHCRP				_hoops_SRI;
	int							_hoops_PRCIP = 0;
	int							_hoops_RSAAS = -1;


	if (dc->_hoops_SRSIP[dc->_hoops_IASS] == null) {
		if (dc->_hoops_HASS[dc->_hoops_IASS] == null) 
			return;

		if (dc->_hoops_HASS[dc->_hoops_IASS]->_hoops_ASHSA->type != _hoops_SSGSH)
			_hoops_RCSHR = (_hoops_CASS *)dc->_hoops_HASS[dc->_hoops_IASS];
			
		if (_hoops_RCSHR) {
			if (ANYBIT (_hoops_RCSHR->_hoops_ASHSA->_hoops_APHGA->current,
					_hoops_GSSHP|_hoops_RSSHP)) {
				_hoops_GSAAS = true;
			}
			else {
				/* _hoops_HRGR _hoops_IIH _hoops_IRS _hoops_CGGC _hoops_IIGR _hoops_IHSP _hoops_SIHH _hoops_IRS _hoops_SSH-_hoops_SRHR? */
				_hoops_CASS const *		x = _hoops_RCSHR;

				do if (x->_hoops_ASHSA->_hoops_APHGA->_hoops_CPP->_hoops_PRH._hoops_HRH) {
					_hoops_GSAAS = true;
					break;
				} while ((x = x->next) != null);
			}

			if (_hoops_GSAAS) {
				_hoops_SRI = nr->_hoops_CPP->_hoops_PRH._hoops_SRI;
				if (_hoops_SRI == _hoops_PIII)
					_hoops_SRI = _hoops_HSSS;
			}
			else
				_hoops_SRI = nr->_hoops_IRR->_hoops_SRI;

			/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_HCH _hoops_ASAAS _hoops_SGH _hoops_CACPI _hoops_HAR _hoops_PSAAS _hoops_IH _hoops_CIPH _hoops_SGS _hoops_HSAAS _hoops_GGR */
			if (_hoops_SRI == _hoops_PIII)
				_hoops_SRI = _hoops_HSSS;

		}
		else
			_hoops_SRI = _hoops_GAI;

#		ifndef _hoops_CRHSA
			if (ANYBIT (_hoops_SRI, ~(_hoops_HSSS|_hoops_GAI))) {
				_hoops_CASS alter *	item;
				_hoops_SCASP		_hoops_ISAAS = 0;

#			ifndef _hoops_IRSSH
				_hoops_ISAAS |= TR_SORT_HIDDEN_BY_PRIORITY;
#			endif
#			ifndef _hoops_IRRHP
				_hoops_ISAAS |= _hoops_GSASP;
#			endif
				item = (_hoops_CASS alter *)dc->_hoops_HASS[dc->_hoops_IASS];
				if (item) do {
					if (!ANYBIT (item->_hoops_ASHSA->_hoops_APHGA->transform_rendition->flags, _hoops_ISAAS))
						HD_Painters_Bias_Z (item, true); 
				} while ((item = item->next) != null);
			}
#		endif

		HD_Linearize_Hidden_Tree (dc, (_hoops_CASS alter *)dc->_hoops_HASS[dc->_hoops_IASS], dc->_hoops_SASS[dc->_hoops_IASS],
								  _hoops_SRI, &_hoops_RCSHR, null);

		dc->_hoops_SASS[dc->_hoops_IASS] = 0;
		dc->_hoops_HASS[dc->_hoops_IASS] = null;

		_hoops_RSAAS = dc->_hoops_IASS;

		if (_hoops_RCSHR == null)
			return;		/* _hoops_ARHAR */
	}
	else {
		_hoops_RCSHR = dc->_hoops_SRSIP[dc->_hoops_IASS]->_hoops_SIGSH;
		_hoops_SRI = dc->_hoops_SRSIP[dc->_hoops_IASS]->_hoops_SRI;
		_hoops_GSAAS = dc->_hoops_SRSIP[dc->_hoops_IASS]->_hoops_GCGSH;

		dc->_hoops_SRSIP[dc->_hoops_IASS]->_hoops_SIGSH = null;
	}

	/* _hoops_GA'_hoops_RA _hoops_ASRC _hoops_SIHH _hoops_GGAS _hoops_RAS _hoops_RGR */
	dc->_hoops_HCAGH = true;


	if (_hoops_GSAAS) {
		_hoops_APARR	_hoops_RRCI;
		
		while (ANYBIT (dc->_hoops_IPCI->mode, _hoops_ISGGR|_hoops_HSGGR)) {
			_hoops_IGRS (dc);
			_hoops_PRCIP++;
		}
		_hoops_RRCI = _hoops_HGCGA (dc, "see hidden transparency", _hoops_RCSHR->_hoops_ASHSA->_hoops_APHGA);

#		ifndef DISABLE_RASTERIZER
#			ifndef _hoops_GCSIR
				if (ANYBIT (_hoops_RCSHR->_hoops_ASHSA->_hoops_APHGA->current,
							_hoops_RSSHP|_hoops_CISHP)) {
					_hoops_RRCI->draw_dc_polytriangle			= HD_Span_DC_Polytriangle;
					_hoops_RRCI->draw_dc_colorized_polytriangle	= HD_Span_DC_Colorized_Polytris;
					_hoops_RRCI->draw_dc_gouraud_polytriangle	= HD_Span_DC_Gouraud_Polytris;
					_hoops_RRCI->draw_dc_phong_polytriangle		= HD_Span_DC_Phong_Polytris;
					_hoops_RRCI->draw_dc_textured_polytriangle	= HD_Span_DC_Textured_Polytris;

					_hoops_RRCI->draw_dc_polyline				= HD_Span_DC_Polyline;
					_hoops_RRCI->draw_dc_colorized_polyline		= HD_Span_DC_Colorized_Polyline;
					_hoops_RRCI->draw_dc_gouraud_polyline		= HD_Span_DC_Gouraud_Polyline;
					_hoops_RRCI->draw_dc_phong_polyline			= HD_Span_DC_Phong_Polyline;
					_hoops_RRCI->draw_dc_textured_polyline		= HD_Span_DC_Textured_Polyline;

					_hoops_RRCI->_hoops_HPCGA			= HD_Image_To_RGB32_Rasters;

					if (_hoops_RCSHR->_hoops_ASHSA->_hoops_APHGA->_hoops_SAIR->_hoops_ASSIR != null &&
						_hoops_RCSHR->_hoops_ASHSA->_hoops_APHGA->_hoops_SAIR->_hoops_ASSIR->
										_hoops_PSSIR()->depth_buffer != null)
						_hoops_RRCI->draw_dc_rgb32_rasters		= HD_Buffer_DC_Raster_C32_Z16;
					else
						_hoops_RRCI->draw_dc_rgb32_rasters		= HD_Buffer_DC_Raster_C32_Z00;

					_hoops_RRCI->draw_dc_polydot				= HD_Std_DC_Polydot;
					_hoops_RRCI->draw_dc_colorized_polydot	= HD_Std_DC_Colorized_Polydot;
				}
#			endif

			_hoops_RRCI->_hoops_GCCGA		= HD_Rasterize_DC_Spans_C24_U;
			_hoops_RRCI->_hoops_ACCGA		= HD_Rasterize_DC_Spans_C24_G;
			_hoops_RRCI->_hoops_HCCGA		= HD_Rasterize_DC_Spans_C24_R;
#		endif
	}

	/*
	 * _hoops_PIPAH _hoops_HHCI-_hoops_PGSA _hoops_RPP _hoops_AHCR-_hoops_GHIS-_hoops_RGAR _hoops_PAR _hoops_CSGSH,
	 * _hoops_PAR _hoops_RPGH _hoops_RH _hoops_IHIR _hoops_GHCH-_hoops_PPR-_hoops_CSAAS,
	 * _hoops_GHAAI _hoops_CRGR _hoops_RH _hoops_IHIR _hoops_SSAAS'_hoops_GRI _hoops_GHIS.
	 */

#	ifndef _hoops_CRHSA
	if (ANYBIT (_hoops_SRI, ~(_hoops_HSSS|_hoops_GAI))) {
		Int_Rectangle					scope;

		if (BIT (_hoops_RCSHR->_hoops_ASHSA->_hoops_APHGA->transform_rendition->flags, _hoops_CGHIP)) {
			_hoops_HHCR			_hoops_IHCR;
			_hoops_CASS const *				x = _hoops_RCSHR;

			_hoops_IHCR = x->_hoops_ASHSA->_hoops_APHGA->transform_rendition;
			scope.left = _hoops_IHCR->_hoops_AGAA.left;
			scope.right = _hoops_IHCR->_hoops_AGAA.right;
			scope.bottom = _hoops_IHCR->_hoops_AGAA.bottom;
			scope.top = _hoops_IHCR->_hoops_AGAA.top;

			while ((x = x->next) != null) {
				_hoops_IHCR = x->_hoops_ASHSA->_hoops_APHGA->transform_rendition;
				if (scope.left > _hoops_IHCR->_hoops_AGAA.left)
					scope.left = _hoops_IHCR->_hoops_AGAA.left;
				if (scope.right < _hoops_IHCR->_hoops_AGAA.right)
					scope.right = _hoops_IHCR->_hoops_AGAA.right;
				if (scope.bottom > _hoops_IHCR->_hoops_AGAA.bottom)
					scope.bottom = _hoops_IHCR->_hoops_AGAA.bottom;
				if (scope.top < _hoops_IHCR->_hoops_AGAA.top)
					scope.top = _hoops_IHCR->_hoops_AGAA.top;
			};
		}
		else {
			_hoops_CGRA const &	_hoops_SGRA = _hoops_RCSHR->_hoops_ASHSA->_hoops_APHGA->_hoops_SAIR;

			scope.left = _hoops_SGRA->_hoops_PHRA.left;
			scope.right = _hoops_SGRA->_hoops_PHRA.right;
			scope.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
			scope.top = _hoops_SGRA->_hoops_PHRA.top;
		}

		if (BIT (_hoops_RCSHR->_hoops_ASHSA->_hoops_APHGA->_hoops_IRR->_hoops_GSSIR, 
					_hoops_SCRAP) ||
			BIT (_hoops_RCSHR->_hoops_ASHSA->_hoops_APHGA->transform_rendition->heuristics, _hoops_HRIRP)) {

			_hoops_RCRAS (dc, _hoops_RCSHR, &scope, -1); 
		}
		else {
			float		_hoops_PCRAS = (float)1.0e30;
			float		_hoops_HCRAS = -(float)1.0e30;
			int			count, _hoops_SCRAS;

			_hoops_CCRAS (_hoops_RCSHR, count, _hoops_SCRAS); 

#			ifdef _hoops_AIRAS
				_hoops_IIAAS=0;
				printf("get scope %d %d %d %d %d\n", count,
					scope.left, scope.right, scope.bottom, scope.top);
#			endif

			_hoops_RSRAS(_hoops_RCSHR, _hoops_PCRAS, _hoops_HCRAS);

			_hoops_ACRAS (dc, _hoops_RCSHR, &scope, count, 0, _hoops_PCRAS, _hoops_HCRAS); 

#			ifdef _hoops_AIRAS
				printf("full_sort_count %d \n", _hoops_IIAAS);
#			endif
		}

		_hoops_RCSHR = null;		// _hoops_HCR _hoops_IIGR _hoops_RH _hoops_IHIR _hoops_GPAC _hoops_CASI _hoops_GH _hoops_GPP _hoops_RCCS
	}
	else
#	endif
	{
		_hoops_RCSHR = HD_Draw_Hidden_Item (_hoops_RCSHR, true);  /* _hoops_CRRHP _hoops_RH _hoops_HIGR _hoops_GAR _hoops_SCH _hoops_IAGA */
	}

#	ifdef HOOPS_DEBUG_BUILD
	if (_hoops_RSAAS != -1 && dc->_hoops_IASS != _hoops_RSAAS)
		_hoops_SGSPR (HEC_INFO, HES_HOOPS_IS_CONFUSED, "alternate_mode changed ... not good.");
	if (dc->_hoops_HASS[dc->_hoops_IASS] != null) 
		_hoops_SGSPR (HEC_INFO, HES_HOOPS_IS_CONFUSED, "Hidden geometry recollected ... not good.");
#	endif

	if (_hoops_GSAAS) {
		_hoops_HGSGA (dc, "see hidden transparency");
		while (_hoops_PRCIP--) {
			_hoops_SGRS (dc);
		}
	}


	dc->_hoops_HCAGH = false;

	if (_hoops_RCSHR == null) {
		if (dc->_hoops_SRSIP[dc->_hoops_IASS] != null) {
			FREE (dc->_hoops_SRSIP[dc->_hoops_IASS], _hoops_CHAGH);
			dc->_hoops_SRSIP[dc->_hoops_IASS] = null;
		}
	}
	else {
		if (dc->_hoops_SRSIP[dc->_hoops_IASS] == null)
			ZALLOC (dc->_hoops_SRSIP[dc->_hoops_IASS], _hoops_CHAGH);

		dc->_hoops_SRSIP[dc->_hoops_IASS]->_hoops_SIGSH = _hoops_RCSHR;
		dc->_hoops_SRSIP[dc->_hoops_IASS]->_hoops_SRI = _hoops_SRI;
		dc->_hoops_SRSIP[dc->_hoops_IASS]->_hoops_GCGSH = _hoops_GSAAS;
	}

#endif
}

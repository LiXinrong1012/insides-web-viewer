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
 * $Id: obf_tmp.txt 1.100 2010-06-04 21:37:18 jason Exp $
 */

/*
 * _hoops_PAGA: _hoops_RH _hoops_HPPA _hoops_IPPA _hoops_RPGP _hoops_HRGR _hoops_CPPPR _hoops_CHPCR - _hoops_SCH _hoops_IRIAS _hoops_RH _hoops_AIRAI
 * _hoops_RSSA _hoops_HPGR _hoops_RH _hoops_CGHI _hoops_PPHIA. _hoops_CRIAS _hoops_SGGR, _hoops_PGAP _hoops_GHCA _hoops_HS _hoops_SRIAS,
 * _hoops_CHR _hoops_IIP _hoops_GPISC. _hoops_GAPAA _hoops_IPSIA _hoops_GHCA _hoops_SPHCP _hoops_SHH _hoops_ACIPR _hoops_IS "_hoops_PPSR _hoops_HPGR".
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "select.h"
#include "patterns.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_SELECTION

/*
 * _hoops_GAIAS _hoops_IS _hoops_CACH _hoops_RPP _hoops_IRS _hoops_CARA _hoops_GC _hoops_PPSR _hoops_HRGR _hoops_AACC _hoops_SGGR _hoops_HPP _hoops_HPPA _hoops_GHC.
 */
#define _hoops_RAIAS(_hoops_IHCR, p) \
	(!BIT (_hoops_IHCR->flags, _hoops_CSP) || \
		HD_Point_Within_Cutting_Planes (_hoops_IHCR, (p)->x, (p)->y, (p)->z))

/*
 * _hoops_AIHH _hoops_RPP _hoops_RH _hoops_SGSSR _hoops_PPSR _hoops_GGR _hoops_SHCA _hoops_HRGR _hoops_GGR _hoops_RH _hoops_GHSHA _hoops_CISAR.
 */
#define _hoops_AAIAS(sc, p) \
   ((p)->x >= (sc)->bounding.left && \
	(p)->x <= (sc)->bounding.right && \
	(p)->y >= (sc)->bounding.bottom && \
	(p)->y <= (sc)->bounding.top && \
	(p)->z >= (sc)->bounding.hither && \
	(p)->z <= (sc)->bounding.yon)


/*
 * _hoops_AHGHR _hoops_IRS _hoops_GHSHA _hoops_GGSC (_hoops_IH _hoops_RH _hoops_SHCA _hoops_GHSHA _hoops_PPSR, _hoops_HAS._hoops_IAS. _hoops_PAIAS),
 * _hoops_PGCR _hoops_SHCA _hoops_RSGR _hoops_RSSA _hoops_IIGR _hoops_IRS _hoops_RGCPR _hoops_III, _hoops_ASRC _hoops_RH _hoops_HAIAS _hoops_GIRA _hoops_HII
 * _hoops_PAIAS, _hoops_RH _hoops_PPSR _hoops_ACHAS _hoops_PPR _hoops_RGCI _hoops_RA _hoops_PIRA.
 */
local float _hoops_IAIAS (
	Net_Rendition const & nr,
	Point				const *_hoops_GGIAR,
	Point				const *p1,
	Point				alter *_hoops_SIAIA,
	float					alter *t) {
	_hoops_ACCCP	alter *sc = nr->_hoops_SRA->_hoops_APHHP;
	Point						_hoops_CAIAS,
												_hoops_HHPSH;
	float							tc,
												_hoops_HSHGA,
												_hoops_ISHGA,
												_hoops_HPCII = 0.0f;

	/*
	 * _hoops_ACGR _hoops_RH _hoops_HISGR _hoops_PPSR _hoops_IS _hoops_RH _hoops_HASRH _hoops_GPP _hoops_RH _hoops_PRISA _hoops_III ==
	 *
	 * _hoops_AHGHR _hoops_RH _hoops_PRISA _hoops_III _hoops_CGSSR:
	 *		_hoops_SISR = _hoops_CPGAS->_hoops_SISR + _hoops_IIHAS * _hoops_RA		   (_hoops_IIHAS = _hoops_PARAA->_hoops_SISR - _hoops_CPGAS->_hoops_SISR)
	 *		_hoops_HAPC = _hoops_CPGAS->_hoops_HAPC + _hoops_SIHAS * _hoops_RA		   (_hoops_SIHAS = _hoops_PARAA->_hoops_HAPC - _hoops_CPGAS->_hoops_HAPC)
	 *
	 * _hoops_AHGHR _hoops_RH _hoops_IHGP _hoops_GIRA _hoops_HII _hoops_IRS _hoops_III _hoops_IS _hoops_IRS _hoops_PPSR (_hoops_GCHAS, _hoops_RCHAS):
	 *		 2			 2			 2
	 *		_hoops_PCCIR  = (_hoops_SISR - _hoops_GCHAS)  + (_hoops_HAPC - _hoops_RCHAS)
	 *															  2
	 * _hoops_SPAA _hoops_RH _hoops_RA-_hoops_PIRA _hoops_HPGR _hoops_RH _hoops_HISGR _hoops_CCHRA - _hoops_RH _hoops_AASC _hoops_IIGR _hoops_PCCIR	- _hoops_HRGR,
	 * _hoops_RRPS _hoops_IS _hoops_GAIPA:
	 *			  _hoops_IIHAS * (_hoops_GCHAS - _hoops_CPGAS->_hoops_SISR) + _hoops_SIHAS * (_hoops_RCHAS - _hoops_CPGAS->_hoops_HAPC)
	 *		_hoops_ACHAS =  -------------------------------
	 *						   2	 2
	 *						 _hoops_IIHAS	 + _hoops_SIHAS
	 */

	_hoops_CAIAS = *_hoops_GGIAR;
	_hoops_HHPSH = *p1;
	_hoops_HSHGA = _hoops_HHPSH.x - _hoops_CAIAS.x;
	_hoops_ISHGA = _hoops_HHPSH.y - _hoops_CAIAS.y;

	tc = _hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA*_hoops_ISHGA;		/* _hoops_GRAS _hoops_PCHAS */
	if (tc < 0.000001f) {
		/* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_PPSR, _hoops_HAR _hoops_IRS _hoops_III! */
		_hoops_SIAIA->x = _hoops_CAIAS.x;
		_hoops_SIAIA->y = _hoops_CAIAS.y;
		_hoops_SIAIA->z = _hoops_CAIAS.z;
		tc = 0.0f;
	}
	else {
		tc = (_hoops_HSHGA * (sc->_hoops_AICAH.x - _hoops_CAIAS.x) +
			  _hoops_ISHGA * (sc->_hoops_AICAH.y - _hoops_CAIAS.y)) / tc;

		if (tc > _hoops_SHRSP) {	/* _hoops_HCHAS _hoops_ICCAR. _hoops_CACH _hoops_ICHAS _hoops_GGR _hoops_RHPP._hoops_GGHR */
			_hoops_HSHGA = -_hoops_HSHGA;
			_hoops_ISHGA = -_hoops_ISHGA;
			_hoops_HPCII = _hoops_CAIAS.x; _hoops_CAIAS.x = _hoops_HHPSH.x; _hoops_HHPSH.x = _hoops_HPCII;
			_hoops_HPCII = _hoops_CAIAS.y; _hoops_CAIAS.y = _hoops_HHPSH.y; _hoops_HHPSH.y = _hoops_HPCII;

			tc = (_hoops_HSHGA * (sc->_hoops_AICAH.x - _hoops_CAIAS.x) +
				  _hoops_ISHGA * (sc->_hoops_AICAH.y - _hoops_CAIAS.y)) / (_hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA*_hoops_ISHGA);
		}

		/* _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_HCHAR _hoops_GIAA _hoops_RH _hoops_III **_hoops_CAGH** ... */
		if (tc <= 0.0f) {
			tc = 0.0f;
			_hoops_SIAIA->x = _hoops_CAIAS.x;
			_hoops_SIAIA->y = _hoops_CAIAS.y;
			_hoops_SIAIA->z = _hoops_CAIAS.z;
		}
		else if (tc >= 1.0f) {
			tc = 1.0f;
			_hoops_SIAIA->x = _hoops_HHPSH.x;
			_hoops_SIAIA->y = _hoops_HHPSH.y;
			_hoops_SIAIA->z = _hoops_HHPSH.z;
		}
		else {
			_hoops_SIAIA->x = _hoops_CAIAS.x + _hoops_HSHGA * tc;
			_hoops_SIAIA->y = _hoops_CAIAS.y + _hoops_ISHGA * tc;
			_hoops_SIAIA->z = _hoops_CAIAS.z + (_hoops_HHPSH.z - _hoops_CAIAS.z) * tc;
		}
	}

	*t = tc;

	_hoops_HSHGA = (_hoops_SIAIA->x - sc->_hoops_AICAH.x) / sc->_hoops_HICAH.x;
	_hoops_ISHGA = (_hoops_SIAIA->y - sc->_hoops_AICAH.y) / sc->_hoops_HICAH.y;

	return	(_hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA);
}


/*
 * _hoops_AHGHR _hoops_IRS _hoops_CPSP (_hoops_IH _hoops_RH _hoops_HPPA _hoops_IPPA _hoops_SIHC), _hoops_SAIAS (_hoops_IH _hoops_RH _hoops_SHCA _hoops_GHSHA
 * _hoops_PPSR), _hoops_IRS _hoops_SHCA _hoops_GPIA, _hoops_RGCI _hoops_PSAP _hoops_ARP _hoops_PSPI, _hoops_PPR _hoops_PCPA _hoops_GPRR _hoops_IIGR
 * _hoops_GPIAS _hoops_CPAP (_hoops_HSP, _hoops_ISHA, _hoops_PPR _hoops_GPIA), _hoops_PRIA _hoops_RH _hoops_GHSHA
 * _hoops_HPHS _hoops_RPP _hoops_RH _hoops_SHCA _hoops_GPIA _hoops_HRGR _hoops_GIAA _hoops_RH _hoops_GHSHA _hoops_IPCAH.
 */
local void _hoops_RPIAS (
	Net_Rendition const &		nr,
	Point const *				p,
	int							_hoops_APIAS, /* _hoops_SHI _hoops_IH _hoops_CCAHR */
	int							_hoops_PPIAS,/* _hoops_SHI _hoops_IH _hoops_CCAHR */
	Grid const *				grid,
	_hoops_ACHR					_hoops_HPIAS) {
	_hoops_HHCR	const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ACCCP alter *	sc = nr->_hoops_SRA->_hoops_APHHP;
	float						_hoops_CIPAS,
								_hoops_IPIAS,
								_hoops_CPIAS,
								_hoops_HSHGA,
								_hoops_ISHGA;

	_hoops_IPIAS = 1.0f / sc->_hoops_HICAH.x;
	_hoops_CPIAS = 1.0f / sc->_hoops_HICAH.y;

	if ((_hoops_HSHGA = p->x - sc->_hoops_AICAH.x) < 0.0f)
		_hoops_HSHGA = -_hoops_HSHGA;
	if ((_hoops_ISHGA = p->y - sc->_hoops_AICAH.y) < 0.0f)
		_hoops_ISHGA = -_hoops_ISHGA;
	_hoops_HSHGA *= _hoops_IPIAS; _hoops_ISHGA *= _hoops_CPIAS;

	if ((_hoops_CIPAS =	_hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA) < (sc->_hoops_GICAH * 2.0f)
		&& (_hoops_RAIAS (_hoops_IHCR,p) && _hoops_AAIAS (sc, p)))
		HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
								_hoops_APIAS, _hoops_PPIAS, 0, p->z, _hoops_CIPAS, _hoops_HPIAS, null);
}


/*
 * _hoops_SPIAS _hoops_HSAR _hoops_GHIAS, _hoops_HA _hoops_SR _hoops_HS _hoops_PGCR _hoops_SHCA _hoops_SAIA.
 */
local void _hoops_RHIAS (
	Net_Rendition const &		nr,
	Point const *				_hoops_GGIAR,
	Point const *				p1,
	int							_hoops_APIAS,
	int							_hoops_PPIAS,
	int							_hoops_AHIAS,
	int							_hoops_PHIAS,
	Grid const *				grid,
	_hoops_ACHR					_hoops_HPIAS) {
	_hoops_HHCR	const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ACCCP alter *	sc = nr->_hoops_SRA->_hoops_APHHP;
	float						_hoops_CIPAS,
								_hoops_IPIAS,
								_hoops_CPIAS,
								_hoops_HSHGA,
								_hoops_ISHGA,
								_hoops_HHIAS,
								_hoops_IHIAS = 0.0f;
	bool						_hoops_CHIAS;
	int							off1 = 0,
								off2 = 0;

	_hoops_CHIAS = false;
	_hoops_HHIAS = sc->_hoops_GICAH * 2.0f;

	_hoops_IPIAS = 1.0f / sc->_hoops_HICAH.x;
	_hoops_CPIAS = 1.0f / sc->_hoops_HICAH.y;

	if ((_hoops_HSHGA = _hoops_GGIAR->x - sc->_hoops_AICAH.x) < 0.0f)
		_hoops_HSHGA = -_hoops_HSHGA;
	if ((_hoops_ISHGA = _hoops_GGIAR->y - sc->_hoops_AICAH.y) < 0.0f)
		_hoops_ISHGA = -_hoops_ISHGA;
	_hoops_HSHGA *= _hoops_IPIAS; _hoops_ISHGA *= _hoops_CPIAS;

	if (((_hoops_CIPAS =	 _hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA) < _hoops_HHIAS) &&
		_hoops_RAIAS (_hoops_IHCR,_hoops_GGIAR) && _hoops_AAIAS (sc, _hoops_GGIAR)) {
		off1 = _hoops_APIAS;
		off2 = _hoops_PPIAS;
		_hoops_HHIAS = _hoops_CIPAS;
		_hoops_IHIAS = _hoops_GGIAR->z;
		_hoops_CHIAS = true;
	}

	if ((_hoops_HSHGA = p1->x - sc->_hoops_AICAH.x) < 0.0f)
		_hoops_HSHGA = -_hoops_HSHGA;
	if ((_hoops_ISHGA = p1->y - sc->_hoops_AICAH.y) < 0.0f)
		_hoops_ISHGA = -_hoops_ISHGA;
	_hoops_HSHGA *= _hoops_IPIAS; _hoops_ISHGA *= _hoops_CPIAS;

	if (((_hoops_CIPAS =	 _hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA) < _hoops_HHIAS)
		&& _hoops_RAIAS (_hoops_IHCR,p1) && _hoops_AAIAS (sc, p1)) {
		off1 = _hoops_AHIAS;
		off2 = _hoops_PHIAS;
		_hoops_HHIAS = _hoops_CIPAS;
		_hoops_IHIAS = p1->z;
		_hoops_CHIAS = true;
	}

	if (_hoops_CHIAS) {
		HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
								off1, off2, 0, _hoops_IHIAS, _hoops_HHIAS, _hoops_HPIAS, null);
	}
}


/*
 * _hoops_SPIAS _hoops_HSAR _hoops_SHIAS, _hoops_HA _hoops_SR _hoops_HS _hoops_AIAA _hoops_SHCA _hoops_SAIA.
 */
local void _hoops_GIIAS (
	Net_Rendition const &		nr,
	Point const *				_hoops_GGIAR,
	Point const *				p1,
	Point const *				p2,
	Point const *				_hoops_IAPH,
	int							_hoops_APIAS,	 /* _hoops_SHI _hoops_IH _hoops_CPGAS */
	int							_hoops_PPIAS, /* _hoops_SHI _hoops_IH _hoops_CPGAS */
	int							_hoops_AHIAS,/* _hoops_SHI _hoops_IH _hoops_PARAA */
	int							_hoops_PHIAS,	 /* _hoops_SHI _hoops_IH _hoops_PARAA */
	Grid const *				grid,
	_hoops_ACHR					_hoops_HPIAS) {
	_hoops_HHCR	const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ACCCP alter *	sc = nr->_hoops_SRA->_hoops_APHHP;
	float						_hoops_CIPAS,
								_hoops_IPIAS,
								_hoops_CPIAS,
								_hoops_HSHGA,
								_hoops_ISHGA,
								_hoops_HHIAS;
	bool						_hoops_CHIAS;
	int							off1 = 0,
								off2 = 0;
	float						_hoops_IHIAS = 0.0f;

	_hoops_CHIAS = false;
	_hoops_HHIAS = sc->_hoops_GICAH * 2.0f;

	_hoops_IPIAS = 1.0f / sc->_hoops_HICAH.x;
	_hoops_CPIAS = 1.0f / sc->_hoops_HICAH.y;

	if ((_hoops_HSHGA = _hoops_GGIAR->x - sc->_hoops_AICAH.x) < 0.0f)
		_hoops_HSHGA = -_hoops_HSHGA;
	if ((_hoops_ISHGA = _hoops_GGIAR->y - sc->_hoops_AICAH.y) < 0.0f)
		_hoops_ISHGA = -_hoops_ISHGA;
	_hoops_HSHGA *= _hoops_IPIAS; _hoops_ISHGA *= _hoops_CPIAS;

	if (((_hoops_CIPAS =	 _hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA) < _hoops_HHIAS)
		&& (_hoops_RAIAS (_hoops_IHCR,_hoops_GGIAR) && _hoops_AAIAS (sc, _hoops_GGIAR))) {
		off1 = _hoops_APIAS;
		off2 = _hoops_AHIAS;
		_hoops_HHIAS = _hoops_CIPAS;
		_hoops_IHIAS = _hoops_GGIAR->z;
		_hoops_CHIAS = true;
	}

	if ((_hoops_HSHGA = p1->x - sc->_hoops_AICAH.x) < 0.0f)
		_hoops_HSHGA = -_hoops_HSHGA;
	if ((_hoops_ISHGA = p1->y - sc->_hoops_AICAH.y) < 0.0f)
		_hoops_ISHGA = -_hoops_ISHGA;
	_hoops_HSHGA *= _hoops_IPIAS; _hoops_ISHGA *= _hoops_CPIAS;

	if (((_hoops_CIPAS =	 _hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA) < _hoops_HHIAS)
		&& (_hoops_RAIAS (_hoops_IHCR,p1) && _hoops_AAIAS (sc, p1))) {
		off1 = _hoops_PPIAS;
		off2 = _hoops_AHIAS;
		_hoops_HHIAS = _hoops_CIPAS;
		_hoops_IHIAS = p1->z;
		_hoops_CHIAS = true;
	}

	if ((_hoops_HSHGA = p2->x - sc->_hoops_AICAH.x) < 0.0f)
		_hoops_HSHGA = -_hoops_HSHGA;
	if ((_hoops_ISHGA = p2->y - sc->_hoops_AICAH.y) < 0.0f)
		_hoops_ISHGA = -_hoops_ISHGA;
	_hoops_HSHGA *= _hoops_IPIAS; _hoops_ISHGA *= _hoops_CPIAS;

	if (((_hoops_CIPAS = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA) < _hoops_HHIAS)
		&& (_hoops_RAIAS (_hoops_IHCR,p2) && _hoops_AAIAS (sc, p2))) {
		off1 = _hoops_APIAS;
		off2 = _hoops_PHIAS;
		_hoops_HHIAS = _hoops_CIPAS;
		_hoops_IHIAS = p2->z;
		_hoops_CHIAS = true;
	}

	if ((_hoops_HSHGA = _hoops_IAPH->x - sc->_hoops_AICAH.x) < 0.0f)
		_hoops_HSHGA = -_hoops_HSHGA;
	if ((_hoops_ISHGA = _hoops_IAPH->y - sc->_hoops_AICAH.y) < 0.0f)
		_hoops_ISHGA = -_hoops_ISHGA;
	_hoops_HSHGA *= _hoops_IPIAS; _hoops_ISHGA *= _hoops_CPIAS;

	if (((_hoops_CIPAS =	 _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA) < _hoops_HHIAS)
		&& (_hoops_RAIAS (_hoops_IHCR,_hoops_IAPH) && _hoops_AAIAS (sc, _hoops_IAPH))) {
		off1 = _hoops_PPIAS;
		off2 = _hoops_PHIAS;
		_hoops_HHIAS = _hoops_CIPAS;
		_hoops_IHIAS = _hoops_IAPH->z;
		_hoops_CHIAS = true;
	}

	if (_hoops_CHIAS) {
		HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
								off1, off2, 0, _hoops_IHIAS, _hoops_HHIAS, _hoops_HPIAS, null);
	}
}


/*
 * _hoops_AHGHR _hoops_IRS _hoops_CPSP (_hoops_IH _hoops_RH _hoops_HPPA _hoops_IPPA _hoops_SIHC), _hoops_SAIAS (_hoops_IH _hoops_RH _hoops_SHCA _hoops_GHSHA
 * _hoops_PPSR _hoops_PPR _hoops_RH _hoops_CAPS _hoops_SIHC), _hoops_RH _hoops_HARGR _hoops_PSPAR _hoops_IIGR _hoops_PCCP _hoops_PGIS, _hoops_RGCI _hoops_SHI
 * _hoops_PSPI , _hoops_PPR _hoops_PCPA _hoops_GPRR _hoops_IIGR  _hoops_GPIAS _hoops_CPAP (_hoops_HSP, _hoops_PAR _hoops_ISHA),
 * _hoops_PRIA _hoops_RH _hoops_GHSHA
 * _hoops_HPHS _hoops_RPP _hoops_RH _hoops_SHCA _hoops_GPIA _hoops_HRGR _hoops_GIAA _hoops_RH _hoops_GHSHA _hoops_IPCAH.
 *
 * _hoops_PHAA _hoops_SSS _hoops_RH _hoops_RCSA _hoops_IIGR _hoops_RH _hoops_PGIS, _hoops_GHCH _hoops_SCH _hoops_CRGR 20 _hoops_ISPAA
 * _hoops_IS _hoops_CAHP _hoops_ARSCI _hoops_RSCA _hoops_RGCPR _hoops_APGR _hoops_GGR _hoops_CARA _hoops_GC.
 * _hoops_RIIAS _hoops_GRR _hoops_III _hoops_IS _hoops_SHCA, _hoops_SSS _hoops_RH _hoops_HAIAS _hoops_GIRA
 * _hoops_HII _hoops_RH _hoops_SHCA _hoops_GHSHA _hoops_PPSR.
 */
local void _hoops_AIIAS (
	Net_Rendition const &		nr,
	Vector const *				_hoops_GGHI,
	Vector const *				_hoops_RGHI,
	int							_hoops_PIIAS,
	int							_hoops_AHIAS,
	int							_hoops_PHIAS,
	Grid const *				grid,
	_hoops_ACHR					_hoops_HPIAS) {
	_hoops_HHCR	const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	_hoops_ACCCP alter *	sc = nr->_hoops_SRA->_hoops_APHHP;
	float						_hoops_HHIAS = 0.0f,
								_hoops_HISAP,
								_hoops_IHIAS = 0.0f,
								_hoops_RAHCR,
								_hoops_HIIAS,
								_hoops_GGHCR,
								_hoops_AGHCR,
								_hoops_RHAPH,
								_hoops_ARSR,
								increment,
								w,
								_hoops_IGHCP;
	Point						_hoops_SIAIA,
								lower,
								upper,
								temp;
	bool						_hoops_CHIAS;
	int							off1 = 0,
								off2 = 0,
								_hoops_HPCII = 0;

	_hoops_CHIAS = false;
	increment = 360.0f / grid->_hoops_IPIAA;

	/* 1/20 _hoops_IIGR _hoops_RH _hoops_GPISR */
	_hoops_IGHCP = increment * 0.05f;

	_hoops_HHIAS = sc->_hoops_GICAH * 2.0f;

	/*
	 * _hoops_IRHH _hoops_RCRR _hoops_SGS _hoops_SR _hoops_CHR _hoops_IIIAS _hoops_HII _hoops_IRS _hoops_HRHC _hoops_CIHA
	 */
	if (_hoops_AHIAS > _hoops_PHIAS) {
		_hoops_HPCII = _hoops_AHIAS;
		_hoops_AHIAS = _hoops_PHIAS;
		_hoops_PHIAS = _hoops_HPCII;
	}

	/* _hoops_IPCP _hoops_AASC _hoops_RCSA */
	_hoops_RAHCR = _hoops_AHIAS * increment;

	/* _hoops_IPCP _hoops_CIAS _hoops_RCSA */
	_hoops_HIIAS = _hoops_PHIAS * increment;

	/*
	 * _hoops_IPCP _hoops_CIIAS, _hoops_IS _hoops_CGIC _hoops_PGAP _hoops_RSGR _hoops_RH _hoops_GHSHA
	 * _hoops_HRGR _hoops_SCHIA _hoops_IS.
	 */
	_hoops_ARSR = _hoops_RAHCR + (_hoops_HIIAS - _hoops_RAHCR) * 0.5f;

	do {
		/* _hoops_SSS _hoops_RH _hoops_CARA _hoops_GC _hoops_RSSA _hoops_GPP _hoops_RH _hoops_PGIS */
		_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);

		lower.x = grid->origin.x +
				  _hoops_PIIAS * (_hoops_AGHCR * _hoops_GGHI->x + _hoops_GGHCR * _hoops_RGHI->x);
		lower.y = grid->origin.y +
				  _hoops_PIIAS * (_hoops_AGHCR * _hoops_GGHI->y + _hoops_GGHCR * _hoops_RGHI->y);
		lower.z = grid->origin.z +
				  _hoops_PIIAS * (_hoops_AGHCR * _hoops_GGHI->z + _hoops_GGHCR * _hoops_RGHI->z);

		_hoops_RAHCR += _hoops_IGHCP;
		_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);

		upper.x = grid->origin.x +
				  _hoops_PIIAS * (_hoops_AGHCR * _hoops_GGHI->x + _hoops_GGHCR * _hoops_RGHI->x);
		upper.y = grid->origin.y +
				  _hoops_PIIAS * (_hoops_AGHCR * _hoops_GGHI->y + _hoops_GGHCR * _hoops_RGHI->y);
		upper.z = grid->origin.z +
				  _hoops_PIIAS * (_hoops_AGHCR * _hoops_GGHI->z + _hoops_GGHCR * _hoops_RGHI->z);

		/* _hoops_HIHP _hoops_CAPR _hoops_IS _hoops_SHCA */
		if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
			temp.x = _hoops_HPRA (elements, lower);
			temp.y = _hoops_IPRA (elements, lower);
			temp.z = _hoops_CPRA (elements, lower);
			lower.x = temp.x;
			lower.y = temp.y;
			lower.z = temp.z;
		}
		else {
			w = _hoops_PHCP (elements, lower);
			if (w <= _hoops_IHCR->_hoops_CHCR) {
				lower.x = lower.y = lower.z = 1e6f;
			}
			else {
				temp.x = _hoops_HPRA (elements, lower) / w;
				temp.y = _hoops_IPRA (elements, lower) / w;
				temp.z = _hoops_CPRA (elements, lower) / w;
				lower.x = temp.x;
				lower.y = temp.y;
				lower.z = temp.z;
			}
		}

		if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
			temp.x = _hoops_HPRA (elements, upper);
			temp.y = _hoops_IPRA (elements, upper);
			temp.z = _hoops_CPRA (elements, upper);
			upper.x = temp.x;
			upper.y = temp.y;
			upper.z = temp.z;
		}
		else {
			w = _hoops_PHCP (elements, upper);
			if (w <= _hoops_IHCR->_hoops_CHCR) {
				upper.x = upper.y = upper.z = 1e6f;
			}
			else {
				temp.x = _hoops_HPRA (elements, upper) / w;
				temp.y = _hoops_IPRA (elements, upper) / w;
				temp.z = _hoops_CPRA (elements, upper) / w;
				upper.x = temp.x;
				upper.y = temp.y;
				upper.z = temp.z;
			}
		}

		/*
		 * _hoops_SSS _hoops_RH _hoops_SGSSR _hoops_PPSR, _hoops_HAIAS _hoops_GIRA,
		 * _hoops_SR _hoops_HS _hoops_PSP _hoops_SGH _hoops_IIGR _hoops_RH _hoops_RA _hoops_PIRA _hoops_CR _hoops_RH _hoops_RCSA _hoops_ICRRP
		 * _hoops_PGAP _hoops_RSGR _hoops_PPSR _hoops_SR _hoops_CHR _hoops_SCHIA _hoops_IS.
		 */
		_hoops_HISAP = _hoops_IAIAS (nr, &lower, &upper, &_hoops_SIAIA, &_hoops_RHAPH);

		if (_hoops_AAIAS (sc, &_hoops_SIAIA)) {
			if (_hoops_RAHCR > _hoops_ARSR) {
				if ((_hoops_RAIAS (_hoops_IHCR,&lower) ||
					 _hoops_RAIAS (_hoops_IHCR,&upper)) &&
					_hoops_HISAP < _hoops_HHIAS) {
					off1 = _hoops_PIIAS;
					off2 = _hoops_PHIAS;
					_hoops_CHIAS = true;
					_hoops_IHIAS = _hoops_SIAIA.z;
					_hoops_HHIAS = _hoops_HISAP;
				}
			}
			else {
				if ((_hoops_RAIAS (_hoops_IHCR,&lower) ||
					 _hoops_RAIAS (_hoops_IHCR,&upper)) &&
					_hoops_HISAP < _hoops_HHIAS) {
					off1 = _hoops_PIIAS;
					off2 = _hoops_AHIAS;
					_hoops_CHIAS = true;
					_hoops_IHIAS = _hoops_SIAIA.z;
					_hoops_HHIAS = _hoops_HISAP;
				}
			}
		}
	} while (_hoops_RAHCR < _hoops_HIIAS);

	if (_hoops_CHIAS)
		HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
								off1, off2, 0, _hoops_IHIAS, _hoops_HHIAS, _hoops_HPIAS, null);
}


/*
 * _hoops_SPIAS _hoops_CSPP _hoops_IIGR _hoops_SIIAS, _hoops_HA _hoops_RH _hoops_GHSHA _hoops_PPSR _hoops_HRGR
 * _hoops_ASSA _hoops_GHARP _hoops_CAPS _hoops_GCIAS.	 _hoops_PHAA _hoops_SSS _hoops_RH _hoops_GIRA _hoops_IIGR _hoops_RH
 * _hoops_PGCR _hoops_RGCPR _hoops_SPPR, _hoops_PSCR _hoops_SSS _hoops_RH _hoops_GIRA _hoops_IIGR _hoops_RH
 * _hoops_PGCR _hoops_RRRC _hoops_GAR _hoops_SR _hoops_SSAS _hoops_GGR _hoops_SIIAS.
 *
 * _hoops_IPCP _hoops_RCIAS... _hoops_CHR _hoops_RH _hoops_AIAA _hoops_GIHA _hoops_IIGR _hoops_RH _hoops_GCIAS.
 */
local void _hoops_ACIAS (
	Net_Rendition const &		nr,
	Vector const *				_hoops_GGHI,
	Vector const *				_hoops_RGHI,
	Point const *				_hoops_PCIAS,
	Point const *				_hoops_HCIAS,
	Point const *				_hoops_ICIAS,
	Point const *				_hoops_CCIAS,
	int							_hoops_APIAS,
	int							_hoops_PPIAS,
	int							_hoops_AHIAS,
	int							_hoops_PHIAS,
	Grid const *				grid,
	_hoops_ACHR					_hoops_HPIAS) {
	_hoops_HHCR	const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	_hoops_ACCCP alter *	sc = nr->_hoops_SRA->_hoops_APHHP;
	float						_hoops_HHIAS,
								_hoops_HISAP,
								_hoops_IHIAS = 0.0f,
								_hoops_RAHCR,
								_hoops_HIIAS,
								_hoops_GGHCR,
								_hoops_AGHCR,
								tc,
								_hoops_ARSR,
								increment,
								w,
								_hoops_IGHCP;
	Point						_hoops_SIAIA,
								_hoops_SCIAS,
								_hoops_GSIAS,
								_hoops_RSIAS,
								_hoops_ASIAS,
								temp;
	bool						_hoops_CHIAS;
	int							off1 = 0,
								off2 = 0,
								_hoops_HPCII = 0;

	_hoops_CHIAS = false;
	_hoops_HHIAS = MAX_FLOAT;

	/* _hoops_SRS _hoops_RPGP _hoops_RGCPR _hoops_SPPR */
	_hoops_HISAP = _hoops_IAIAS (nr, _hoops_PCIAS, _hoops_HCIAS,
							   &_hoops_SIAIA, &tc);

	if (_hoops_HPIAS == T_FACES || _hoops_AAIAS (sc, &_hoops_SIAIA)) {
		if (tc > 0.5) {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_HCIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_HISAP;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_PCIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_HISAP;
				_hoops_CHIAS = true;
			}
		}
		else {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_PCIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_HISAP;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_HCIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_HISAP;
				_hoops_CHIAS = true;
			}
		}
	}

	_hoops_HISAP = _hoops_IAIAS (nr, _hoops_ICIAS, _hoops_CCIAS,
							   &_hoops_SIAIA, &tc);

	if (_hoops_HPIAS == T_FACES || _hoops_AAIAS (sc, &_hoops_SIAIA)) {
		if (tc > 0.5) {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_CCIAS) && _hoops_HISAP < _hoops_HHIAS) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_HISAP;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_ICIAS) && _hoops_HISAP < _hoops_HHIAS) {
				off1 = _hoops_APIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_HISAP;
				_hoops_CHIAS = true;
			}
		}
		else {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_ICIAS) && _hoops_HISAP < _hoops_HHIAS) {
				off1 = _hoops_APIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_HISAP;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_CCIAS) && _hoops_HISAP < _hoops_HHIAS) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_HISAP;
				_hoops_CHIAS = true;
			}
		}
	}

	/* _hoops_HA _hoops_RH _hoops_RRRC */
	increment = 360.0f / grid->_hoops_IPIAA;

	if (_hoops_AHIAS > _hoops_PHIAS) {
		/* _hoops_GGSHR */
		_hoops_HPCII = _hoops_AHIAS;
		_hoops_AHIAS = _hoops_PHIAS;
		_hoops_PHIAS = _hoops_HPCII;
	}

	_hoops_IGHCP = increment * 0.05f;
	_hoops_RAHCR = _hoops_AHIAS * increment;
	_hoops_HIIAS = _hoops_PHIAS * increment;
	_hoops_ARSR = _hoops_RAHCR + (_hoops_HIIAS - _hoops_RAHCR) * 0.5f;

	do {
		_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);

		_hoops_SCIAS.x = grid->origin.x +
					   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI->x + _hoops_GGHCR * _hoops_RGHI->x);
		_hoops_SCIAS.y = grid->origin.y +
					   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI->y + _hoops_GGHCR * _hoops_RGHI->y);
		_hoops_SCIAS.z = grid->origin.z +
					   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI->z + _hoops_GGHCR * _hoops_RGHI->z);

		_hoops_GSIAS.x = grid->origin.x +
						_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI->x + _hoops_GGHCR * _hoops_RGHI->x);
		_hoops_GSIAS.y = grid->origin.y +
						_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI->y + _hoops_GGHCR * _hoops_RGHI->y);
		_hoops_GSIAS.z = grid->origin.z +
						_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI->z + _hoops_GGHCR * _hoops_RGHI->z);

		_hoops_RAHCR += _hoops_IGHCP;
		_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);

		_hoops_RSIAS.x = grid->origin.x +
					   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI->x + _hoops_GGHCR * _hoops_RGHI->x);
		_hoops_RSIAS.y = grid->origin.y +
					   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI->y + _hoops_GGHCR * _hoops_RGHI->y);
		_hoops_RSIAS.z = grid->origin.z +
					   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI->z + _hoops_GGHCR * _hoops_RGHI->z);

		_hoops_ASIAS.x = grid->origin.x +
						_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI->x + _hoops_GGHCR * _hoops_RGHI->x);
		_hoops_ASIAS.y = grid->origin.y +
						_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI->y + _hoops_GGHCR * _hoops_RGHI->y);
		_hoops_ASIAS.z = grid->origin.z +
						_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI->z + _hoops_GGHCR * _hoops_RGHI->z);

		if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
			temp.x = _hoops_HPRA (elements, _hoops_SCIAS);
			temp.y = _hoops_IPRA (elements, _hoops_SCIAS);
			temp.z = _hoops_CPRA (elements, _hoops_SCIAS);
			_hoops_SCIAS.x = temp.x;
			_hoops_SCIAS.y = temp.y;
			_hoops_SCIAS.z = temp.z;
		}
		else {
			w = _hoops_PHCP (elements, _hoops_SCIAS);
			if (w <= _hoops_IHCR->_hoops_CHCR) {
				_hoops_SCIAS.x = _hoops_SCIAS.y = _hoops_SCIAS.z = 1e6f;
			}
			else {
				temp.x = _hoops_HPRA (elements, _hoops_SCIAS) / w;
				temp.y = _hoops_IPRA (elements, _hoops_SCIAS) / w;
				temp.z = _hoops_CPRA (elements, _hoops_SCIAS) / w;
				_hoops_SCIAS.x = temp.x;
				_hoops_SCIAS.y = temp.y;
				_hoops_SCIAS.z = temp.z;
			}
		}

		if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
			temp.x = _hoops_HPRA (elements, _hoops_GSIAS);
			temp.y = _hoops_IPRA (elements, _hoops_GSIAS);
			temp.z = _hoops_CPRA (elements, _hoops_GSIAS);
			_hoops_GSIAS.x = temp.x;
			_hoops_GSIAS.y = temp.y;
			_hoops_GSIAS.z = temp.z;
		}
		else {
			w = _hoops_PHCP (elements, _hoops_GSIAS);
			if (w <= _hoops_IHCR->_hoops_CHCR) {
				_hoops_GSIAS.x = _hoops_GSIAS.y = _hoops_GSIAS.z = 1e6f;
			}
			else {
				temp.x = _hoops_HPRA (elements, _hoops_GSIAS) / w;
				temp.y = _hoops_IPRA (elements, _hoops_GSIAS) / w;
				temp.z = _hoops_CPRA (elements, _hoops_GSIAS) / w;
				_hoops_GSIAS.x = temp.x;
				_hoops_GSIAS.y = temp.y;
				_hoops_GSIAS.z = temp.z;
			}
		}

		if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
			temp.x = _hoops_HPRA (elements, _hoops_RSIAS);
			temp.y = _hoops_IPRA (elements, _hoops_RSIAS);
			temp.z = _hoops_CPRA (elements, _hoops_RSIAS);
			_hoops_RSIAS.x = temp.x;
			_hoops_RSIAS.y = temp.y;
			_hoops_RSIAS.z = temp.z;
		}
		else {
			w = _hoops_PHCP (elements, _hoops_RSIAS);
			if (w <= _hoops_IHCR->_hoops_CHCR) {
				_hoops_RSIAS.x = _hoops_RSIAS.y = _hoops_RSIAS.z = 1e6f;
			}
			else {
				temp.x = _hoops_HPRA (elements, _hoops_RSIAS) / w;
				temp.y = _hoops_IPRA (elements, _hoops_RSIAS) / w;
				temp.z = _hoops_CPRA (elements, _hoops_RSIAS) / w;
				_hoops_RSIAS.x = temp.x;
				_hoops_RSIAS.y = temp.y;
				_hoops_RSIAS.z = temp.z;
			}
		}

		if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
			temp.x = _hoops_HPRA (elements, _hoops_ASIAS);
			temp.y = _hoops_IPRA (elements, _hoops_ASIAS);
			temp.z = _hoops_CPRA (elements, _hoops_ASIAS);
			_hoops_ASIAS.x = temp.x;
			_hoops_ASIAS.y = temp.y;
			_hoops_ASIAS.z = temp.z;
		}
		else {
			w = _hoops_PHCP (elements, _hoops_ASIAS);
			if (w <= _hoops_IHCR->_hoops_CHCR) {
				_hoops_ASIAS.x = _hoops_ASIAS.y = _hoops_ASIAS.z = 1e6f;
			}
			else {
				temp.x = _hoops_HPRA (elements, _hoops_ASIAS) / w;
				temp.y = _hoops_IPRA (elements, _hoops_ASIAS) / w;
				temp.z = _hoops_CPRA (elements, _hoops_ASIAS) / w;
				_hoops_ASIAS.x = temp.x;
				_hoops_ASIAS.y = temp.y;
				_hoops_ASIAS.z = temp.z;
		   }
		}

		_hoops_HISAP = _hoops_IAIAS (nr, &_hoops_GSIAS, &_hoops_ASIAS, &_hoops_SIAIA, &tc);

		if (_hoops_HPIAS == T_FACES || _hoops_AAIAS (sc, &_hoops_SIAIA)) {
			if (_hoops_RAHCR > _hoops_ARSR) {
				if ((_hoops_RAIAS (_hoops_IHCR,&_hoops_GSIAS) ||
					 _hoops_RAIAS (_hoops_IHCR,&_hoops_ASIAS)) &&
					_hoops_HISAP < _hoops_HHIAS) {
					off1 = _hoops_PPIAS;
					off2 = _hoops_PHIAS;
					_hoops_CHIAS = true;
					_hoops_IHIAS = _hoops_SIAIA.z;
					_hoops_HHIAS = _hoops_HISAP;
				}
			}
			else {
				if ((_hoops_RAIAS (_hoops_IHCR,&_hoops_GSIAS) ||
						_hoops_RAIAS (_hoops_IHCR,&_hoops_ASIAS)) &&
						_hoops_HISAP < _hoops_HHIAS) {
					off1 = _hoops_PPIAS;
					off2 = _hoops_AHIAS;
					_hoops_CHIAS = true;
					_hoops_IHIAS = _hoops_SIAIA.z;
					_hoops_HHIAS = _hoops_HISAP;
				}
			}
		}

		_hoops_HISAP = _hoops_IAIAS (nr, &_hoops_SCIAS, &_hoops_RSIAS, &_hoops_SIAIA, &tc);

		if (_hoops_HPIAS == T_FACES || _hoops_AAIAS (sc, &_hoops_SIAIA)) {
			if (_hoops_RAHCR > _hoops_ARSR) {
				if ((_hoops_RAIAS (_hoops_IHCR,&_hoops_SCIAS) ||
					 _hoops_RAIAS (_hoops_IHCR,&_hoops_RSIAS)) &&
					_hoops_HISAP < _hoops_HHIAS) {
					off1 = _hoops_APIAS;
					off2 = _hoops_PHIAS;
					_hoops_CHIAS = true;
					_hoops_IHIAS = _hoops_SIAIA.z;
					_hoops_HHIAS = _hoops_HISAP;
				}
			}
			else {
				if ((_hoops_RAIAS (_hoops_IHCR,&_hoops_SCIAS) ||
					 _hoops_RAIAS (_hoops_IHCR,&_hoops_RSIAS)) &&
					_hoops_HISAP < _hoops_HHIAS) {
					off1 = _hoops_APIAS;
					off2 = _hoops_AHIAS;
					_hoops_CHIAS = true;
					_hoops_IHIAS = _hoops_SIAIA.z;
					_hoops_HHIAS = _hoops_HISAP;
				}
			}
		}
	} while (_hoops_RAHCR < _hoops_HIIAS);

	if (_hoops_CHIAS) {
		if (_hoops_HPIAS == T_FACES) {
			/*
			 * _hoops_RPP _hoops_RH _hoops_SHCA _hoops_GHSHA _hoops_HRGR _hoops_ASSA _hoops_IIGR _hoops_RH _hoops_GCIAS, _hoops_RH _hoops_SSH
			 * _hoops_PIRA _hoops_PSIAS _hoops_HRGR 0.0f.
			 */
			HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
									off1, off2, 0, _hoops_IHIAS, 0.0f, _hoops_HPIAS, null);
		}
		else if (_hoops_HHIAS < sc->_hoops_GICAH * 2.0f) {
			HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
									off1, off2, 0, _hoops_IHIAS, _hoops_HHIAS, _hoops_HPIAS, null);
		}
	}
}


/*
 * _hoops_AHGHR _hoops_IRS _hoops_CPSP (_hoops_IH _hoops_RH _hoops_HPPA _hoops_IPPA _hoops_SIHC), _hoops_SAIAS (_hoops_IH _hoops_RH _hoops_SHCA _hoops_GHSHA
 * _hoops_PPSR), _hoops_PGCR _hoops_SHCA _hoops_RSGR _hoops_RSSA _hoops_IIGR _hoops_PCCP _hoops_ISHA, _hoops_PAII _hoops_PSAP _hoops_ARP _hoops_PSPI, _hoops_PPR _hoops_PCPA _hoops_GPRR _hoops_IIGR
 * _hoops_GPIAS _hoops_CPAP (_hoops_HSP, _hoops_ISHA, _hoops_PAR _hoops_GPIA), _hoops_PRIA _hoops_RH _hoops_GHSHA
 * _hoops_HPHS _hoops_RPP _hoops_RH _hoops_SHCA _hoops_III _hoops_HRGR _hoops_GIAA _hoops_RH _hoops_GHSHA _hoops_IPCAH.
 */
local void _hoops_HSIAS (
	Net_Rendition const &		nr,
	Point const *				_hoops_GGIAR,
	Point const *				p1,
	int							_hoops_APIAS,	 /* _hoops_SHI _hoops_IH _hoops_CPGAS */
	int							_hoops_PPIAS, /* _hoops_SHI _hoops_IH _hoops_CPGAS */
	int							_hoops_AHIAS,/* _hoops_SHI _hoops_IH _hoops_PARAA */
	int							_hoops_PHIAS,	 /* _hoops_SHI _hoops_IH _hoops_PARAA */
	Grid const *				grid,
	_hoops_ACHR					_hoops_HPIAS) {
	_hoops_HHCR	const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ACCCP alter *	sc = nr->_hoops_SRA->_hoops_APHHP;
	float						_hoops_HISAP,
								tc;
	Point						_hoops_SIAIA;

	_hoops_HISAP = _hoops_IAIAS (nr, _hoops_GGIAR, p1, &_hoops_SIAIA, &tc);

	if (_hoops_HISAP < sc->_hoops_GICAH * 2.0f &&
		_hoops_AAIAS (sc, &_hoops_SIAIA)) {
		if (tc > 0.5f) {
			if (_hoops_RAIAS (_hoops_IHCR,p1))
				HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
										_hoops_AHIAS, _hoops_PHIAS, 0, _hoops_SIAIA.z, _hoops_HISAP, _hoops_HPIAS, null);
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_GGIAR))
				HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
										_hoops_APIAS, _hoops_APIAS, 0, _hoops_SIAIA.z, _hoops_HISAP, _hoops_HPIAS, null);
		}
		else {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_GGIAR))
				HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
										_hoops_APIAS, _hoops_PPIAS, 0, _hoops_SIAIA.z, _hoops_HISAP, _hoops_HPIAS, null);
			else if (_hoops_RAIAS (_hoops_IHCR, p1))
				HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
										_hoops_AHIAS, _hoops_AHIAS, 0, _hoops_SIAIA.z ,_hoops_HISAP, _hoops_HPIAS, null);
		}
	}
}


/*
 * _hoops_SPIAS _hoops_CSPP _hoops_IIGR _hoops_ISIAS, _hoops_HA _hoops_SR _hoops_HS _hoops_AIAA _hoops_SPPR.
 * _hoops_HGI _hoops_HRGR _hoops_IGI _hoops_RGAR _hoops_HPP _hoops_ISHA _hoops_GHSHA.
 */
local void _hoops_CSIAS (
	Net_Rendition const &		nr,
	Point const *				_hoops_SCIAS,
	Point const *				_hoops_GSIAS,
	Point const *				_hoops_RSIAS,
	Point const *				_hoops_ASIAS,
	int							_hoops_APIAS,
	int							_hoops_PPIAS,
	int							_hoops_AHIAS,
	int							_hoops_PHIAS,/* _hoops_SHI _hoops_IH _hoops_CCAHR */
	Grid const *				grid,
	_hoops_ACHR					_hoops_HPIAS) {
	_hoops_HHCR	const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ACCCP alter *	sc = nr->_hoops_SRA->_hoops_APHHP;
	int							off1 = 0,
								off2 = 0;
	bool						_hoops_CHIAS;
	float						_hoops_HHIAS,
								_hoops_IHIAS = 0.0f,
								tc,
								_hoops_CGSIR;
	Point						_hoops_SIAIA;

	_hoops_CHIAS = false;
	_hoops_HHIAS = sc->_hoops_GICAH * 2.0f;
	_hoops_CGSIR = _hoops_IAIAS (nr, _hoops_SCIAS, _hoops_GSIAS, &_hoops_SIAIA, &tc);

	if (_hoops_CGSIR < _hoops_HHIAS && _hoops_AAIAS (sc, &_hoops_SIAIA)) {
		if (tc > 0.5) {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_GSIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_SCIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
		}
		else {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_SCIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_GSIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
		}
	}

	_hoops_CGSIR =	_hoops_IAIAS (nr, _hoops_RSIAS, _hoops_ASIAS, &_hoops_SIAIA, &tc);

	if (_hoops_CGSIR < _hoops_HHIAS && _hoops_AAIAS (sc, &_hoops_SIAIA)) {
		if (tc > 0.5) {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_ASIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_RSIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
		}
		else {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_RSIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_ASIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
		}
	}

	_hoops_CGSIR =	_hoops_IAIAS (nr, _hoops_SCIAS, _hoops_RSIAS, &_hoops_SIAIA, &tc);

	if (_hoops_CGSIR < _hoops_HHIAS && _hoops_AAIAS (sc, &_hoops_SIAIA)) {
		if (tc > 0.5) {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_RSIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_SCIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
		}
		else {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_SCIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_RSIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
		}
	}

	_hoops_CGSIR =	_hoops_IAIAS (nr, _hoops_GSIAS, _hoops_ASIAS, &_hoops_SIAIA, &tc);

	if (_hoops_CGSIR < _hoops_HHIAS && _hoops_AAIAS (sc, &_hoops_SIAIA)) {
		if (tc > 0.5) {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_ASIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_GSIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
		}
		else {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_GSIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_AHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_ASIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_PHIAS;
				_hoops_IHIAS = _hoops_SIAIA.z;
				_hoops_HHIAS = _hoops_CGSIR;
				_hoops_CHIAS = true;
			}
		}
	}

	if (_hoops_CHIAS)
		HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
								off1, off2, 0, _hoops_IHIAS,_hoops_HHIAS, _hoops_HPIAS, null);
}

/*
 * _hoops_SPIAS _hoops_CSPP _hoops_IIGR _hoops_ISIAS, _hoops_HA _hoops_SR _hoops_HS _hoops_AIAA _hoops_SPPR _hoops_PPR _hoops_SR _hoops_CHR
 * _hoops_HHCPR _hoops_IGH _hoops_IRS _hoops_HSP _hoops_HRGR _hoops_GPIAS.  _hoops_IPCP _hoops_HSP _hoops_HRGR _hoops_PACIA
 * _hoops_HCCPR _hoops_HCR _hoops_IIGR _hoops_RH _hoops_AIAA _hoops_GIHA _hoops_CHR _hoops_AACC _hoops_SGGR _hoops_PAR _hoops_RH
 * _hoops_SHCA _hoops_GHSHA _hoops_PPSR _hoops_ACAS (_hoops_HA _hoops_RH _hoops_SGSSR _hoops_SSIAS) _hoops_HRGR
 * _hoops_HAR _hoops_GGR _hoops_RH _hoops_GHSHA _hoops_CISAR.
 */
local void _hoops_GGCAS (
	Net_Rendition const &		nr,
	Point const *				_hoops_SCIAS,
	Point const *				_hoops_GSIAS,
	Point const *				_hoops_RSIAS,
	Point const *				_hoops_ASIAS,
	int							_hoops_APIAS,
	int							_hoops_PPIAS,
	int							_hoops_AHIAS,
	int							_hoops_PHIAS,/* _hoops_SHI _hoops_IH _hoops_CCAHR */
	Grid const *				grid,
	_hoops_ACHR					_hoops_HPIAS) {
	_hoops_HHCR	const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_ACCCP alter *	sc = nr->_hoops_SRA->_hoops_APHHP;
	int							off1 = 0,
								off2 = 0;
	float						_hoops_HHIAS,
								tc,
								_hoops_CGSIR;
	Point						_hoops_SIAIA;
	float						_hoops_RCSAP;

	if (_hoops_AAIAS(sc, &sc->_hoops_AICAH)) {
		_hoops_HHIAS = _hoops_CGSIR = _hoops_IAIAS (nr, _hoops_SCIAS, _hoops_GSIAS, &_hoops_SIAIA, &tc);

		if (tc > 0.5) {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_GSIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_AHIAS;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_SCIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_AHIAS;
			}
		}
		else {
			if (_hoops_RAIAS (_hoops_IHCR, _hoops_SCIAS)) {
				off1 = _hoops_APIAS;
				off2 = _hoops_AHIAS;
			}
			else if (_hoops_RAIAS (_hoops_IHCR, _hoops_GSIAS)) {
				off1 = _hoops_PPIAS;
				off2 = _hoops_AHIAS;
			}
		}
		_hoops_RCSAP = _hoops_SIAIA.z;

		_hoops_CGSIR =	_hoops_IAIAS (nr, _hoops_RSIAS, _hoops_ASIAS, &_hoops_SIAIA, &tc);

		if (_hoops_CGSIR < _hoops_HHIAS) {
			if (tc > 0.5) {
				if (_hoops_RAIAS (_hoops_IHCR, _hoops_ASIAS)) {
					off1 = _hoops_PPIAS;
					off2 = _hoops_PHIAS;
				}
				else if (_hoops_RAIAS (_hoops_IHCR, _hoops_RSIAS)) {
					off1 = _hoops_APIAS;
					off2 = _hoops_PHIAS;
				}
			}
			else {
				if (_hoops_RAIAS (_hoops_IHCR, _hoops_RSIAS)) {
					off1 = _hoops_APIAS;
					off2 = _hoops_PHIAS;
				}
				else if (_hoops_RAIAS (_hoops_IHCR, _hoops_ASIAS)) {
					off1 = _hoops_PPIAS;
					off2 = _hoops_PHIAS;
				}
			}
			_hoops_RCSAP = _hoops_SIAIA.z;
		}

		_hoops_CGSIR =	_hoops_IAIAS (nr, _hoops_SCIAS, _hoops_RSIAS, &_hoops_SIAIA, &tc);

		if (_hoops_CGSIR < _hoops_HHIAS) {
			if (tc > 0.5) {
				if (_hoops_RAIAS (_hoops_IHCR, _hoops_RSIAS)) {
					off1 = _hoops_APIAS;
					off2 = _hoops_PHIAS;
				}
				else if (_hoops_RAIAS (_hoops_IHCR, _hoops_SCIAS)) {
					off1 = _hoops_APIAS;
					off2 = _hoops_AHIAS;
				}
			}
			else {
				if (_hoops_RAIAS (_hoops_IHCR, _hoops_SCIAS)) {
					off1 = _hoops_APIAS;
					off2 = _hoops_AHIAS;
				}
				else if (_hoops_RAIAS (_hoops_IHCR, _hoops_RSIAS)) {
					off1 = _hoops_APIAS;
					off2 = _hoops_PHIAS;
				}
			}
			_hoops_RCSAP = _hoops_SIAIA.z;
		}

		_hoops_CGSIR =	_hoops_IAIAS (nr, _hoops_GSIAS, _hoops_ASIAS, &_hoops_SIAIA, &tc);

		if (_hoops_CGSIR < _hoops_HHIAS) {
			if (tc > 0.5) {
				if (_hoops_RAIAS (_hoops_IHCR, _hoops_ASIAS)) {
					off1 = _hoops_PPIAS;
					off2 = _hoops_PHIAS;
				}
				else if (_hoops_RAIAS (_hoops_IHCR, _hoops_GSIAS)) {
					off1 = _hoops_PPIAS;
					off2 = _hoops_AHIAS;
				}
			}
			else {
				if (_hoops_RAIAS (_hoops_IHCR, _hoops_GSIAS)) {
					off1 = _hoops_PPIAS;
					off2 = _hoops_AHIAS;
				}
				else if (_hoops_RAIAS (_hoops_IHCR, _hoops_ASIAS)) {
					off1 = _hoops_PPIAS;
					off2 = _hoops_PHIAS;
				}
			}
			_hoops_RCSAP = _hoops_SIAIA.z;
		}

		HD_Elaborate_Selection (nr, (Geometry alter *)grid, grid->key, _hoops_AIRIR(grid),
								off1, off2, 0, _hoops_RCSAP, 0.0f, _hoops_HPIAS, null);
	}
}
#endif


GLOBAL_FUNCTION void HD_Select_Grid (
	Net_Rendition const &		nr,
	Grid const *				grid) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	Point						line[2];
	float						_hoops_SSHGA, t;
	Vector						_hoops_SIAIA, _hoops_GGHI, _hoops_RGHI = _hoops_IRGA::_hoops_CRGA, tmp;
	Point						_hoops_SCIAS = _hoops_HPCH::_hoops_IPCH,
								_hoops_GSIAS = _hoops_HPCH::_hoops_IPCH,
								_hoops_RSIAS = _hoops_HPCH::_hoops_IPCH,
								_hoops_ASIAS = _hoops_HPCH::_hoops_IPCH,
								temp;
	float						_hoops_ISPI = 0.0f, _hoops_CSPI = 0.0f;
	int							_hoops_APIAS, _hoops_PPIAS, _hoops_AHIAS, _hoops_PHIAS;
	float						w;
	float						a0, a1, a2, _hoops_SACIC, _hoops_IHHI, _hoops_CHHI;
	_hoops_RPRA const			*_hoops_CRIPA;


	/*
	 * _hoops_HGI _hoops_HRGR _hoops_CGRRA -- _hoops_SRS, _hoops_SICR _hoops_RH _hoops_GHSHA _hoops_AHC _hoops_CRGR _hoops_IRS _hoops_III,
	 * _hoops_PPR _hoops_HIHP _hoops_SCH _hoops_CRGR _hoops_CARA _hoops_GC.	_hoops_SPAA _hoops_GRAS _hoops_RH _hoops_SGSSR _hoops_IIGR
	 * _hoops_RH _hoops_CCAH _hoops_III _hoops_CCA _hoops_RH _hoops_CAPS _hoops_IPPA.  _hoops_IPCP _hoops_PPSR _hoops_HRGR _hoops_PSCR _hoops_ISAIA _hoops_CRGR
	 * _hoops_RH _hoops_GC _hoops_PAPR _hoops_HPP _hoops_RH _hoops_HARGR _hoops_PSPAR _hoops_IS _hoops_CGIC _hoops_RH _hoops_PGCR _hoops_SHI
	 * _hoops_HSH.	 _hoops_IPCP [_hoops_GH _hoops_IS] _hoops_AIAA _hoops_RSSA _hoops_GCPPR _hoops_RH _hoops_HPHR _hoops_RSSA _hoops_CHR _hoops_PSCR
	 * _hoops_CHIAR _hoops_IS _hoops_SHPR _hoops_GC, _hoops_PPR _hoops_RH _hoops_PHRHA _hoops_IIGR _hoops_AGCR _hoops_HRGR _hoops_HHRPR _hoops_GAR _hoops_RH
	 * _hoops_HPHR _hoops_SHI _hoops_HSH.
	 */

	_hoops_CRIPA = _hoops_IHCR->matrix->_hoops_PPRA()->data.elements;

	line[0].x = _hoops_CRIPA[0][0] * sc->_hoops_AICAH.x +
				_hoops_CRIPA[1][0] * sc->_hoops_AICAH.y +
				_hoops_CRIPA[2][0] * 0.0f +
				_hoops_CRIPA[3][0] * 1.0f;

	line[0].y = _hoops_CRIPA[0][1] * sc->_hoops_AICAH.x +
				_hoops_CRIPA[1][1] * sc->_hoops_AICAH.y +
				_hoops_CRIPA[2][1] * 0.0f +
				_hoops_CRIPA[3][1] * 1.0f;

	line[0].z = _hoops_CRIPA[0][2] * sc->_hoops_AICAH.x +
				_hoops_CRIPA[1][2] * sc->_hoops_AICAH.y +
				_hoops_CRIPA[2][2] * 0.0f +
				_hoops_CRIPA[3][2] * 1.0f;

	w		  = _hoops_CRIPA[0][3] * sc->_hoops_AICAH.x +
				_hoops_CRIPA[1][3] * sc->_hoops_AICAH.y +
				_hoops_CRIPA[2][3] * 0.0f +
				_hoops_CRIPA[3][3] * 1.0f;

	if (w != 1.0f) {
		if (w == 0.0f)
			return;
		w = 1.0f / w;

		line[0].x *= w;
		line[0].y *= w;
		line[0].z *= w;
	}

	line[1].x = _hoops_CRIPA[0][0] * sc->_hoops_AICAH.x +
				_hoops_CRIPA[1][0] * sc->_hoops_AICAH.y +
				_hoops_CRIPA[2][0] * 0.5f * _hoops_IHCR->_hoops_PCHH +
				_hoops_CRIPA[3][0] * 1.0f;

	line[1].y = _hoops_CRIPA[0][1] * sc->_hoops_AICAH.x +
				_hoops_CRIPA[1][1] * sc->_hoops_AICAH.y +
				_hoops_CRIPA[2][1] * 0.5f * _hoops_IHCR->_hoops_PCHH	+
				_hoops_CRIPA[3][1] * 1.0f;

	line[1].z = _hoops_CRIPA[0][2] * sc->_hoops_AICAH.x +
				_hoops_CRIPA[1][2] * sc->_hoops_AICAH.y +
				_hoops_CRIPA[2][2] * 0.5f * _hoops_IHCR->_hoops_PCHH	+
				_hoops_CRIPA[3][2] * 1.0f;

	w		  = _hoops_CRIPA[0][3] * sc->_hoops_AICAH.x +
				_hoops_CRIPA[1][3] * sc->_hoops_AICAH.y +
				_hoops_CRIPA[2][3] * 0.5f * _hoops_IHCR->_hoops_PCHH +
				_hoops_CRIPA[3][3] * 1.0f;

	if (w != 1.0f) {
		if (w == 0.0f)
			return;
		w = 1.0f / w;

		line[1].x *= w;
		line[1].y *= w;
		line[1].z *= w;
	}

	_hoops_SSHGA = grid->plane.a * (line[1].x - line[0].x)	 +
			grid->plane.b * (line[1].y - line[0].y)	 +
			grid->plane.c * (line[1].z - line[0].z);

	if (_hoops_SSHGA == 0.0f) {
		/* _hoops_PSP _hoops_PPPSR _hoops_RHHR -- _hoops_SPHR _hoops_GGCR _hoops_IPCAH _hoops_RPGP ? */
		return;
	}

	if (BIT (sc->options, _hoops_CRPAS)) {
		bool							_hoops_RCAI = false;

		_hoops_IGRS (dc);

		if (sc->_hoops_GPPAS) {
			void *							_hoops_CCHSP;

			_hoops_CCHSP = _hoops_AACGH (nr, true);
			_hoops_PPICP (nr, grid);
			_hoops_PACGH (nr, _hoops_CCHSP);

			if (_hoops_IACGH (nr, _hoops_CCHSP) == 0)
				_hoops_RCAI = true;
		}
		else {
			_hoops_HCSIR alter *	_hoops_ICSIR = null;

			if (nr->_hoops_SAIR->_hoops_ASSIR != null)
				_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
			if (_hoops_ICSIR == null) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Expected frame buffer not found");
				_hoops_RCAI = true;
				goto _hoops_SIPAS;
			}

			_hoops_ICSIR->input._hoops_PHHSP = 0;
			_hoops_PPICP (nr, grid);
			if (_hoops_ICSIR->input._hoops_PHHSP == 0)
				_hoops_RCAI = true;
		}

	  _hoops_SIPAS:
		_hoops_SGRS (dc);
		if (_hoops_RCAI)
			return;
	}

	t = grid->plane.d +
		grid->plane.a * line[0].x +
		grid->plane.b * line[0].y +
		grid->plane.c * line[0].z;
	t /= -_hoops_SSHGA;

	_hoops_SIAIA.x = line[0].x + t * (line[1].x - line[0].x);
	_hoops_SIAIA.y = line[0].y + t * (line[1].y - line[0].y);
	_hoops_SIAIA.z = line[0].z + t * (line[1].z - line[0].z);

	if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH &&
		(w = _hoops_PHCP (elements, _hoops_SIAIA)) < 0.0f)
		return;			/* _hoops_GHIPR _hoops_RHC */

	_hoops_GGHI.x = grid->ref1.x - grid->origin.x;
	_hoops_GGHI.y = grid->ref1.y - grid->origin.y;
	_hoops_GGHI.z = grid->ref1.z - grid->origin.z;

	switch (grid->_hoops_APIAA) {
		case _hoops_PPIAA: {
			_hoops_RGHI.x = grid->ref2.x - grid->origin.x;
			_hoops_RGHI.y = grid->ref2.y - grid->origin.y;
			_hoops_RGHI.z = grid->ref2.z - grid->origin.z;

			if (Abs(grid->plane.a) > Abs(grid->plane.b) &&
				Abs(grid->plane.a) > Abs(grid->plane.c)) {
				a0 = _hoops_SIAIA.y - grid->origin.y;
				a1 = _hoops_GGHI.y;
				a2 = _hoops_RGHI.y;
				_hoops_SACIC = _hoops_SIAIA.z - grid->origin.z;
				_hoops_IHHI = _hoops_GGHI.z;
				_hoops_CHHI = _hoops_RGHI.z;
			}
			else if (Abs(grid->plane.b) > Abs(grid->plane.c)) {
				a0 = _hoops_SIAIA.x - grid->origin.x;
				a1 = _hoops_GGHI.x;
				a2 = _hoops_RGHI.x;
				_hoops_SACIC = _hoops_SIAIA.z - grid->origin.z;
				_hoops_IHHI = _hoops_GGHI.z;
				_hoops_CHHI = _hoops_RGHI.z;
			}
			else {
				a0 = _hoops_SIAIA.x - grid->origin.x;
				a1 = _hoops_GGHI.x;
				a2 = _hoops_RGHI.x;
				_hoops_SACIC = _hoops_SIAIA.y - grid->origin.y;
				_hoops_IHHI = _hoops_GGHI.y;
				_hoops_CHHI = _hoops_RGHI.y;
			}

			_hoops_SSHGA = a1 * _hoops_CHHI - a2 * _hoops_IHHI;

			_hoops_ISPI = (a0 * _hoops_CHHI - a2 * _hoops_SACIC) / _hoops_SSHGA;
			_hoops_CSPI = (a1 * _hoops_SACIC - a0 * _hoops_IHHI) / _hoops_SSHGA;
		}	break;

		case _hoops_SPARP: {
			float			_hoops_RAHCR, _hoops_RGCAS, section;

			_hoops_RGHI.x = _hoops_GGHI.z * grid->plane.b - _hoops_GGHI.y * grid->plane.c;
			_hoops_RGHI.y = _hoops_GGHI.x * grid->plane.c - _hoops_GGHI.z * grid->plane.a;
			_hoops_RGHI.z = _hoops_GGHI.y * grid->plane.a - _hoops_GGHI.x * grid->plane.b;

			_hoops_RGCAS = _hoops_SGIHR (_hoops_GGHI.x * _hoops_GGHI.x +
						   _hoops_GGHI.y * _hoops_GGHI.y +
						   _hoops_GGHI.z * _hoops_GGHI.z);

			tmp.x = _hoops_SIAIA.x - grid->origin.x;
			tmp.y = _hoops_SIAIA.y - grid->origin.y;
			tmp.z = _hoops_SIAIA.z - grid->origin.z;

			_hoops_ISPI = _hoops_SGIHR (tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z) /
				 _hoops_RGCAS;

			(void)HI_Normalize (&tmp);
			(void)HI_Normalize (&_hoops_GGHI);

			_hoops_RAHCR = _hoops_ISSSR (_hoops_GGHI.x * tmp.x	+
							 _hoops_GGHI.y * tmp.y  +
							 _hoops_GGHI.z * tmp.z);

			section = 360.0f / grid->_hoops_IPIAA;

			if (_hoops_RGHI.x * tmp.x + _hoops_RGHI.y * tmp.y + _hoops_RGHI.z * tmp.z >= 0.0f)
				_hoops_CSPI = _hoops_RAHCR / section;
			else if (grid->count2 <= 0)
				_hoops_CSPI = -_hoops_RAHCR / section;
			else if ((360.0f - _hoops_RAHCR) - grid->count2 * section < _hoops_RAHCR)
				_hoops_CSPI = grid->_hoops_IPIAA - _hoops_RAHCR / section;
			else
				_hoops_CSPI = -_hoops_RAHCR / section;

			/* _hoops_PHIH _hoops_CRGGA (_hoops_SCGA _hoops_ARRS) */
			_hoops_GGHI.x = grid->ref1.x - grid->origin.x;
			_hoops_GGHI.y = grid->ref1.y - grid->origin.y;
			_hoops_GGHI.z = grid->ref1.z - grid->origin.z;
		}	break;
	}

	_hoops_APIAS = (int)_hoops_ISPI;
	if (_hoops_ISPI >= 0)
		_hoops_PPIAS = _hoops_APIAS + 1;
	else
		_hoops_PPIAS = _hoops_APIAS - 1;

	if (grid->count1 > 0) {
		if (_hoops_APIAS < 0)
			_hoops_APIAS = 0;
		else if (_hoops_APIAS > grid->count1)
			_hoops_APIAS = grid->count1;

		if (_hoops_PPIAS < 0)
			_hoops_PPIAS = 0;
		else if (_hoops_PPIAS > grid->count1)
			_hoops_PPIAS = grid->count1;
	}
	else if (grid->count1 < 0) {
		if (_hoops_APIAS < grid->count1)
			_hoops_APIAS = grid->count1;
		else if (_hoops_APIAS > -grid->count1)
			_hoops_APIAS = -grid->count1;

		if (_hoops_PPIAS < grid->count1)
			_hoops_PPIAS = grid->count1;
		else if (_hoops_PPIAS > -grid->count1)
			_hoops_PPIAS = -grid->count1;
	}

	_hoops_AHIAS = (int)_hoops_CSPI;
	if (_hoops_CSPI >= 0)
		_hoops_PHIAS = _hoops_AHIAS + 1;
	else
		_hoops_PHIAS = _hoops_AHIAS - 1;

	if (grid->count2 > 0) {
		if (_hoops_AHIAS < 0)
			_hoops_AHIAS = 0;
		else if (_hoops_AHIAS > grid->count2)
			_hoops_AHIAS = grid->count2;

		if (_hoops_PHIAS < 0)
			_hoops_PHIAS = 0;
		else if (_hoops_PHIAS > grid->count2)
			_hoops_PHIAS = grid->count2;
	}
	else if (grid->count2 < 0) {
		if (_hoops_AHIAS < grid->count2)
			_hoops_AHIAS = grid->count2;
		else if (_hoops_AHIAS > -grid->count2)
			_hoops_AHIAS = -grid->count2;

		if (_hoops_PHIAS < grid->count2)
			_hoops_PHIAS = grid->count2;
		else if (_hoops_PHIAS > -grid->count2)
			_hoops_PHIAS = -grid->count2;
	}

	switch (grid->_hoops_APIAA) {
		case _hoops_PPIAA: {
			_hoops_SCIAS.x = grid->origin.x + _hoops_APIAS * _hoops_GGHI.x +
						   _hoops_AHIAS * _hoops_RGHI.x;
			_hoops_SCIAS.y = grid->origin.y + _hoops_APIAS * _hoops_GGHI.y +
						   _hoops_AHIAS * _hoops_RGHI.y;
			_hoops_SCIAS.z = grid->origin.z + _hoops_APIAS * _hoops_GGHI.z +
						   _hoops_AHIAS * _hoops_RGHI.z;

			_hoops_GSIAS.x = grid->origin.x + _hoops_PPIAS * _hoops_GGHI.x +
							_hoops_AHIAS * _hoops_RGHI.x;
			_hoops_GSIAS.y = grid->origin.y + _hoops_PPIAS * _hoops_GGHI.y +
							_hoops_AHIAS * _hoops_RGHI.y;
			_hoops_GSIAS.z = grid->origin.z + _hoops_PPIAS * _hoops_GGHI.z +
							_hoops_AHIAS * _hoops_RGHI.z;

			_hoops_RSIAS.x = grid->origin.x + _hoops_APIAS * _hoops_GGHI.x +
						   _hoops_PHIAS * _hoops_RGHI.x;
			_hoops_RSIAS.y = grid->origin.y + _hoops_APIAS * _hoops_GGHI.y +
						   _hoops_PHIAS * _hoops_RGHI.y;
			_hoops_RSIAS.z = grid->origin.z + _hoops_APIAS * _hoops_GGHI.z +
						   _hoops_PHIAS * _hoops_RGHI.z;

			_hoops_ASIAS.x = grid->origin.x + _hoops_PPIAS * _hoops_GGHI.x +
							_hoops_PHIAS * _hoops_RGHI.x;
			_hoops_ASIAS.y = grid->origin.y + _hoops_PPIAS * _hoops_GGHI.y +
							_hoops_PHIAS * _hoops_RGHI.y;
			_hoops_ASIAS.z = grid->origin.z + _hoops_PPIAS * _hoops_GGHI.z +
							_hoops_PHIAS * _hoops_RGHI.z;
		}	break;

		case _hoops_SPARP: {
			float			_hoops_GGHCR, _hoops_AGHCR, _hoops_RAHCR, increment;

			increment = 360.0f / grid->_hoops_IPIAA;

			_hoops_RAHCR = _hoops_AHIAS * increment;
			_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);

			_hoops_SCIAS.x = grid->origin.x +
						   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI.x + _hoops_GGHCR * _hoops_RGHI.x);
			_hoops_SCIAS.y = grid->origin.y +
						   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI.y + _hoops_GGHCR * _hoops_RGHI.y);
			_hoops_SCIAS.z = grid->origin.z +
						   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI.z + _hoops_GGHCR * _hoops_RGHI.z);

			_hoops_GSIAS.x = grid->origin.x +
							_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI.x + _hoops_GGHCR * _hoops_RGHI.x);
			_hoops_GSIAS.y = grid->origin.y +
							_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI.y + _hoops_GGHCR * _hoops_RGHI.y);
			_hoops_GSIAS.z = grid->origin.z +
							_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI.z + _hoops_GGHCR * _hoops_RGHI.z);

			_hoops_RAHCR = _hoops_PHIAS * increment;
			_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);

			_hoops_RSIAS.x = grid->origin.x +
						   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI.x + _hoops_GGHCR * _hoops_RGHI.x);
			_hoops_RSIAS.y = grid->origin.y +
						   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI.y + _hoops_GGHCR * _hoops_RGHI.y);
			_hoops_RSIAS.z = grid->origin.z +
						   _hoops_APIAS * (_hoops_AGHCR * _hoops_GGHI.z + _hoops_GGHCR * _hoops_RGHI.z);

			_hoops_ASIAS.x = grid->origin.x +
							_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI.x + _hoops_GGHCR * _hoops_RGHI.x);
			_hoops_ASIAS.y = grid->origin.y +
							_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI.y + _hoops_GGHCR * _hoops_RGHI.y);
			_hoops_ASIAS.z = grid->origin.z +
							_hoops_PPIAS * (_hoops_AGHCR * _hoops_GGHI.z + _hoops_GGHCR * _hoops_RGHI.z);
		}	break;
	}

	if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
		temp.x = _hoops_HPRA (elements, _hoops_SCIAS);
		temp.y = _hoops_IPRA (elements, _hoops_SCIAS);
		temp.z = _hoops_CPRA (elements, _hoops_SCIAS);
		_hoops_SCIAS.x = temp.x;
		_hoops_SCIAS.y = temp.y;
		_hoops_SCIAS.z = temp.z;
	}
	else {
		w = _hoops_PHCP (elements, _hoops_SCIAS);
		if (w <= _hoops_IHCR->_hoops_CHCR) {
			_hoops_SCIAS.x = _hoops_SCIAS.y = _hoops_SCIAS.z = 1e5f;
		}
		else {
			temp.x = _hoops_HPRA (elements, _hoops_SCIAS) / w;
			temp.y = _hoops_IPRA (elements, _hoops_SCIAS) / w;
			temp.z = _hoops_CPRA (elements, _hoops_SCIAS) / w;
			_hoops_SCIAS.x = temp.x;
			_hoops_SCIAS.y = temp.y;
			_hoops_SCIAS.z = temp.z;
		}
	}

	if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
		temp.x = _hoops_HPRA (elements, _hoops_GSIAS);
		temp.y = _hoops_IPRA (elements, _hoops_GSIAS);
		temp.z = _hoops_CPRA (elements, _hoops_GSIAS);
		_hoops_GSIAS.x = temp.x;
		_hoops_GSIAS.y = temp.y;
		_hoops_GSIAS.z = temp.z;
	}
	else {
		w = _hoops_PHCP (elements, _hoops_GSIAS);
		if (w <= _hoops_IHCR->_hoops_CHCR) {
			_hoops_GSIAS.x = _hoops_GSIAS.y = _hoops_GSIAS.z = 1e5f;
		}
		else {
			temp.x = _hoops_HPRA (elements, _hoops_GSIAS) / w;
			temp.y = _hoops_IPRA (elements, _hoops_GSIAS) / w;
			temp.z = _hoops_CPRA (elements, _hoops_GSIAS) / w;
			_hoops_GSIAS.x = temp.x;
			_hoops_GSIAS.y = temp.y;
			_hoops_GSIAS.z = temp.z;
		}
	}

	if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
		temp.x = _hoops_HPRA (elements, _hoops_RSIAS);
		temp.y = _hoops_IPRA (elements, _hoops_RSIAS);
		temp.z = _hoops_CPRA (elements, _hoops_RSIAS);
		_hoops_RSIAS.x = temp.x;
		_hoops_RSIAS.y = temp.y;
		_hoops_RSIAS.z = temp.z;
	}
	else {
		w = _hoops_PHCP (elements, _hoops_RSIAS);
		if (w <= _hoops_IHCR->_hoops_CHCR) {
			_hoops_RSIAS.x = _hoops_RSIAS.y = _hoops_RSIAS.z = 1e5f;
		}
		else {
			temp.x = _hoops_HPRA (elements, _hoops_RSIAS) / w;
			temp.y = _hoops_IPRA (elements, _hoops_RSIAS) / w;
			temp.z = _hoops_CPRA (elements, _hoops_RSIAS) / w;
			_hoops_RSIAS.x = temp.x;
			_hoops_RSIAS.y = temp.y;
			_hoops_RSIAS.z = temp.z;
		}
	}

	if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
		temp.x = _hoops_HPRA (elements, _hoops_ASIAS);
		temp.y = _hoops_IPRA (elements, _hoops_ASIAS);
		temp.z = _hoops_CPRA (elements, _hoops_ASIAS);
		_hoops_ASIAS.x = temp.x;
		_hoops_ASIAS.y = temp.y;
		_hoops_ASIAS.z = temp.z;
	}
	else {
		w = _hoops_PHCP (elements, _hoops_ASIAS);
		if (w <= _hoops_IHCR->_hoops_CHCR) {
			_hoops_ASIAS.x = _hoops_ASIAS.y = _hoops_ASIAS.z = 1e5f;
		}
		else {
			temp.x = _hoops_HPRA (elements, _hoops_ASIAS) / w;
			temp.y = _hoops_IPRA (elements, _hoops_ASIAS) / w;
			temp.z = _hoops_CPRA (elements, _hoops_ASIAS) / w;
			_hoops_ASIAS.x = temp.x;
			_hoops_ASIAS.y = temp.y;
			_hoops_ASIAS.z = temp.z;
	   }
	}

	{
		_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
		_hoops_ACHR					_hoops_SGPPI = _hoops_RRGH->_hoops_AAICA & (nr->_hoops_RGP | _hoops_RRGH->_hoops_PHARP);

		if (_hoops_APIAS == _hoops_PPIAS) {
			if (_hoops_AHIAS == _hoops_PHIAS) {
				/*
				 * _hoops_HPAC = _hoops_AGCAS
				 * _hoops_PS _hoops_RPGP _hoops_RH _hoops_GHSHA _hoops_PPSR _hoops_CCA _hoops_RH _hoops_GPHA.
				 */
				if (BIT (_hoops_SGPPI, T_FACES)) {
					_hoops_RPIAS (nr, &_hoops_SCIAS, _hoops_APIAS, _hoops_AHIAS,
								grid, T_FACES);
				}
				else if (ANYBIT (_hoops_SGPPI, T_PERIMETER_EDGES|_hoops_CRHGP|T_GENERIC_EDGES)) {
					_hoops_RPIAS (nr, &_hoops_SCIAS, _hoops_APIAS, _hoops_AHIAS,
								grid, T_ANY_EDGE);
				}
				else /* _hoops_RPP (_hoops_IRRC (_hoops_PGCAS, _hoops_HGCAS)) */ {
					_hoops_RPIAS (nr, &_hoops_SCIAS, _hoops_APIAS, _hoops_AHIAS,
								grid, T_VERTICES);
				}
			}
			else {
				/* _hoops_HPAC = _hoops_IGCAS */
				if (BIT (_hoops_SGPPI, T_FACES)) {
					 if (grid->_hoops_APIAA == _hoops_SPARP)
						_hoops_AIIAS (nr, &_hoops_GGHI, &_hoops_RGHI, _hoops_APIAS,
								 _hoops_AHIAS, _hoops_PHIAS, grid, T_FACES);
					 else
						_hoops_HSIAS (nr, &_hoops_SCIAS, &_hoops_RSIAS,
								  _hoops_APIAS, _hoops_AHIAS, _hoops_APIAS, _hoops_PHIAS,
								  grid, T_FACES);
				}
				else if (ANYBIT (_hoops_SGPPI, T_PERIMETER_EDGES|_hoops_CRHGP|T_GENERIC_EDGES)) {
					 if (grid->_hoops_APIAA == _hoops_SPARP)
						_hoops_AIIAS (nr, &_hoops_GGHI, &_hoops_RGHI, _hoops_APIAS,
								 _hoops_AHIAS, _hoops_PHIAS, grid, T_ANY_EDGE);
					 else
						_hoops_HSIAS (nr, &_hoops_SCIAS, &_hoops_RSIAS,
								  _hoops_APIAS, _hoops_AHIAS, _hoops_APIAS, _hoops_PHIAS,
								  grid, T_ANY_EDGE);
				}
				else /* _hoops_RPP (_hoops_IRRC (_hoops_PGCAS, _hoops_HGCAS)) */ {
					 _hoops_RHIAS (nr, &_hoops_SCIAS, &_hoops_RSIAS, _hoops_APIAS,
						_hoops_AHIAS, _hoops_APIAS, _hoops_PHIAS, grid, T_VERTICES);
				}
			}
		}
		else if (_hoops_AHIAS == _hoops_PHIAS) {
			/*
			 * _hoops_HPAC = _hoops_IGCAS
			 * _hoops_CPGP _hoops_RH _hoops_CGCAS == _hoops_SGCAS, _hoops_SR _hoops_HS
			 * _hoops_IRS _hoops_RGCPR _hoops_III _hoops_PRGI _hoops_IH _hoops_IRS _hoops_GHARP _hoops_CAPS.
			 */

			if (BIT (_hoops_SGPPI, T_FACES)) {
				_hoops_HSIAS (nr, &_hoops_SCIAS, &_hoops_GSIAS, _hoops_APIAS,
						  _hoops_AHIAS, _hoops_PPIAS, _hoops_PHIAS, grid, T_FACES);
			}
			else if (ANYBIT (_hoops_SGPPI, T_PERIMETER_EDGES|_hoops_CRHGP|T_GENERIC_EDGES)) {
				_hoops_HSIAS (nr, &_hoops_SCIAS, &_hoops_GSIAS, _hoops_APIAS,
						  _hoops_AHIAS, _hoops_PPIAS, _hoops_PHIAS, grid, T_ANY_EDGE);
			}
			else /* _hoops_RPP (_hoops_IRRC (_hoops_PGCAS, _hoops_HGCAS)) */ {
				 _hoops_RHIAS (nr, &_hoops_SCIAS, &_hoops_GSIAS, _hoops_APIAS,
					 _hoops_AHIAS, _hoops_PPIAS, _hoops_PHIAS, grid, T_VERTICES);
			}
		}
		else {
			/* _hoops_HPAC = _hoops_GRCAS */
			if (BIT (_hoops_SGPPI, T_FACES)) {
				if (grid->_hoops_APIAA == _hoops_SPARP)
					_hoops_ACIAS (nr, &_hoops_GGHI, &_hoops_RGHI, &_hoops_SCIAS, &_hoops_GSIAS,
							   &_hoops_RSIAS, &_hoops_ASIAS, _hoops_APIAS, _hoops_PPIAS,
							   _hoops_AHIAS, _hoops_PHIAS, grid, T_FACES);
				else
					_hoops_GGCAS (nr, &_hoops_SCIAS, &_hoops_GSIAS, &_hoops_RSIAS,
								&_hoops_ASIAS, _hoops_APIAS, _hoops_PPIAS, _hoops_AHIAS, _hoops_PHIAS,
								grid, T_FACES);
			}
			else if (ANYBIT (_hoops_SGPPI, T_PERIMETER_EDGES|_hoops_CRHGP|T_GENERIC_EDGES)) {
				if (grid->_hoops_APIAA == _hoops_SPARP)
					_hoops_ACIAS (nr, &_hoops_GGHI, &_hoops_RGHI, &_hoops_SCIAS, &_hoops_GSIAS,
							   &_hoops_RSIAS, &_hoops_ASIAS, _hoops_APIAS, _hoops_PPIAS,
							   _hoops_AHIAS, _hoops_PHIAS, grid, T_ANY_EDGE);
				else
					_hoops_CSIAS (nr, &_hoops_SCIAS, &_hoops_GSIAS, &_hoops_RSIAS, &_hoops_ASIAS,
								_hoops_APIAS, _hoops_PPIAS, _hoops_AHIAS, _hoops_PHIAS,
								grid, T_ANY_EDGE);
			}
			else {
				 _hoops_GIIAS (nr, &_hoops_SCIAS, &_hoops_GSIAS, &_hoops_RSIAS, &_hoops_ASIAS,
								_hoops_APIAS, _hoops_PPIAS, _hoops_AHIAS, _hoops_PHIAS,
								grid, T_VERTICES);
			}
		}
	}
#endif
}

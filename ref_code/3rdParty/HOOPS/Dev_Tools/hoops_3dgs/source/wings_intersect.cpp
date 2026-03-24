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
 * $Id: obf_tmp.txt 1.54 2010-08-06 19:05:09 jason Exp $
 */

#include "hoops.h"
#include "topology.h"
#include "hi_proto.h"
#include "hpserror.h"


#ifdef _hoops_CGSPR
#include <stdio.h>
#endif

#ifndef DISABLE_POLY_SELECTION


/*
 * _hoops_CGP _hoops_IHPR, _hoops_PSCR _hoops_RH _hoops_CRHAS "_hoops_IRS" _hoops_HRGR _hoops_RRIPR _hoops_ARPP "_hoops_RCSR"
 */
local bool _hoops_SSCAGR (
	_hoops_GPCIH			*a,
	_hoops_GPCIH			*b) {

	return (a->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y < b->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y ||
			a->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y == b->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y &&
			(a->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x < b->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x ||
			 a->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x == b->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x &&
			 a->type < b->type));
}



/*
 * _hoops_GGSAGR _hoops_IS _hoops_AGR _hoops_RGSAGR.
 */
local void _hoops_AGSAGR (
	_hoops_GPCIH			**first,
	_hoops_GPCIH			**_hoops_SSAC) {

	if (first < _hoops_SSAC) {
		_hoops_GPCIH			**i = first - 1;
		_hoops_GPCIH			**j = _hoops_SSAC;

		for (;;) {
			while (_hoops_SSCAGR (*++i, *_hoops_SSAC) && i < j);
			while (_hoops_SSCAGR (*_hoops_SSAC, *--j) && i < j);
			if (i >= j) break;
			Swap (*i, *j);
		}

		Swap (*i, *_hoops_SSAC);

		_hoops_AGSAGR (first, i-1);
		_hoops_AGSAGR (i+1, _hoops_SSAC);
	}
}



GLOBAL_FUNCTION void HI_Free_Wings (
	int				count,
	_hoops_GPCIH			**_hoops_RPCIH) {

	_hoops_GPCIH			**_hoops_PGSAGR = _hoops_RPCIH;
	_hoops_GPCIH			**_hoops_AGCGS = _hoops_PGSAGR + count;

	_hoops_RGGA (_hoops_PGSAGR == _hoops_AGCGS) {
		FREE (*_hoops_PGSAGR, _hoops_GPCIH);
		_hoops_PGSAGR++;
	}
	FREE_ARRAY (_hoops_RPCIH, count, _hoops_GPCIH *);

}



GLOBAL_FUNCTION int HI_Create_Polyglin_Wings (
	int				count,
	Point		*points,
	bool		_hoops_SPGPA,
	int				owner,
	_hoops_GPCIH			***_hoops_RPCIH) {

	_hoops_GPCIH			*_hoops_HGSAGR;
	_hoops_GPCIH			*_hoops_IGSAGR = null;
	int				_hoops_CAPAS = 0;
	Point		*_hoops_SPGGA = points;
	Point		*_hoops_CGSAGR = points + count;
	_hoops_GPCIH			*_hoops_SGSAGR;
	_hoops_GPCIH			*_hoops_GRSAGR = null;
	float			_hoops_GSAHR = 1.0e-3f;

	_hoops_IGSAGR = null;

	/*
	 * _hoops_RRSAGR 1:
	 *
	 * _hoops_GISA _hoops_CSCS _hoops_RGSAGR
	 */
	do {
		/* _hoops_RPGH _hoops_IRS _hoops_CCAH _hoops_CRHAS */
		ALLOC (_hoops_HGSAGR, _hoops_GPCIH);
		_hoops_HGSAGR->next = _hoops_IGSAGR;
		_hoops_IGSAGR = _hoops_HGSAGR;
		++_hoops_CAPAS;

		if (_hoops_GRSAGR == null) _hoops_GRSAGR = _hoops_HGSAGR;

		_hoops_HGSAGR->owner = owner;
		if (_hoops_SPGPA)
			_hoops_HGSAGR->region = owner;
		else
			_hoops_HGSAGR->region = false;

		/*
		 * _hoops_ARP _hoops_RAAP _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_CRHAS _hoops_IS _hoops_ARSAGR _hoops_GPHA
		 */
		_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS] = points;

		/*
		 * _hoops_SPIC _hoops_RPHR _hoops_PPAP _hoops_ARHI _hoops_HPGP _hoops_GPP _hoops_RH _hoops_PSHR
		 * _hoops_IRGGA _hoops_GAR _hoops_RH _hoops_RAAP _hoops_PPAP
		 */
		do _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS] = points;
		_hoops_RGGA (++points == _hoops_CGSAGR ||
				Abs(points->y - _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y) > _hoops_GSAHR);

		/*
		 * _hoops_GGR _hoops_AGIR _hoops_SR _hoops_HS _hoops_ASPSR _hoops_RSSA, _hoops_IRHH _hoops_SCH _hoops_IRS _hoops_RSRA _hoops_PPSR
		 */
		if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x ==
			_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x)
			_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS];

		_hoops_HGSAGR->_hoops_HASHH = true;
		_hoops_HGSAGR->_hoops_SSAGS[_hoops_HRASA] = _hoops_HGSAGR->_hoops_SSAGS[_hoops_IGHAS] = 0.0f;
	} _hoops_RGGA (points == _hoops_CGSAGR);


	/*
	 * _hoops_AGGA _hoops_HS
	 *		 _hoops_RGSAGR (=_hoops_PRSAGR) ... _hoops_HRSAGR
	 */


	/*
	 * _hoops_RRSAGR 2:
	 *
	 * _hoops_RPACC _hoops_SRS _hoops_PPR _hoops_CGHI _hoops_RGSAGR _hoops_RPP _hoops_SSIA _hoops_CHR _hoops_GPP _hoops_RH _hoops_PSHR _hoops_IRGGA,
	 * _hoops_HIS _hoops_SGS
	 *
	 *	   _hoops_PRSAGR	_hoops_HRSAGR
	 *	  *------------**---------------*
	 *	  _hoops_GSSAA			   _hoops_HPARGR				_hoops_AHGPH
	 *	  _hoops_IPARGR
	 *
	 *	_hoops_RHCHR
	 *
	 *				_hoops_HRSAGR
	 *	  *--------------------------*
	 *	  _hoops_ISAII							 _hoops_AHGPH
	 *	  _hoops_CPARGR
	 *
	 *	_hoops_HIH _hoops_PSSSR _hoops_IH _hoops_AGIR _hoops_CAS _hoops_HCR _hoops_RSSA _hoops_IH _hoops_IRS _hoops_RSRA _hoops_PRCGH
	 */
	if (_hoops_HGSAGR == _hoops_GRSAGR) {
		Point *		left;
		Point *		right;

		/* _hoops_HACSS _hoops_RH _hoops_RSSA _hoops_HCHAR _hoops_IH _hoops_RH _hoops_IRSAGR */
		points = _hoops_SPGGA;
		left = right = points++;
		do {
			if (points->x < left->x)
				left = points;
			else if (points->x > right->x)
				right = points;
		} _hoops_RGGA (++points == _hoops_CGSAGR);

		/* _hoops_IRHH _hoops_IRS _hoops_IHGP _hoops_PRCGH */
		_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS] = left;
		_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS] = right;
	}
	else if (Abs(_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->y - _hoops_GRSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y) < _hoops_GSAHR) {
		/*
		 * _hoops_SIPR _hoops_IASH _hoops_IIGR _hoops_RH _hoops_PRSAGR, _hoops_HPP _hoops_SIIPS _hoops_RH
		 * _hoops_HRSAGR _hoops_IS _hoops_RH _hoops_RAAP _hoops_PPR _hoops_HCPCA _hoops_RH _hoops_PRSAGR
		 *
		 *				 _hoops_HRSAGR
		 *	  *-------------**---------------*
		 *	  _hoops_ISAII								 _hoops_AHGPH
		 *	  _hoops_CRSAGR
		 */

		if (!_hoops_SPGPA &&
			_hoops_GRSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x !=
			_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x) {
			/*
			 * _hoops_SRSAGR _hoops_CGAPC: _hoops_HHIGR _hoops_ASSP'_hoops_RA _hoops_IGRC _hoops_GGGR:
			 *
			 *	   _hoops_PRSAGR		_hoops_HRSAGR
			 *	  *------------*   *------------*
			 *	  _hoops_GSSAA			   _hoops_PCCIR   _hoops_ISAII			_hoops_AHGPH
			 *	  _hoops_IPARGR
			 *
			 * _hoops_SR _hoops_RRP _hoops_IS _hoops_PRIA _hoops_SGS _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_IASI _hoops_IRGGA _hoops_PPR
			 * _hoops_PRIA "_hoops_IGRIP" _hoops_PRGGR _hoops_GGR _hoops_RH _hoops_GARRA [_hoops_SRS] _hoops_CRHAS
			 */

			_hoops_GRSAGR->_hoops_HASHH = false;
			if (_hoops_GRSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x <
				_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x) {
				_hoops_GRSAGR->_hoops_SSAGS[_hoops_HRASA] = _hoops_GRSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x;
				_hoops_GRSAGR->_hoops_SSAGS[_hoops_IGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x;
			}
			else {
				_hoops_GRSAGR->_hoops_SSAGS[_hoops_HRASA] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x;
				_hoops_GRSAGR->_hoops_SSAGS[_hoops_IGHAS] = _hoops_GRSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x;
			}
		}
		else
			_hoops_SPGPA = true;

		_hoops_GRSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS];
		/*
		 * _hoops_GGR _hoops_AGIR _hoops_SR _hoops_HS _hoops_ASPSR _hoops_RSSA, _hoops_IRHH _hoops_SCH _hoops_IRS _hoops_RSRA _hoops_PPSR
		 */
		if (_hoops_GRSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x ==
			_hoops_GRSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x)
			_hoops_GRSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS] = _hoops_GRSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS];
		_hoops_IGSAGR = _hoops_IGSAGR->next;
		FREE (_hoops_HGSAGR, _hoops_GPCIH);
		_hoops_HGSAGR = _hoops_IGSAGR;
		--_hoops_CAPAS;
	}


	_hoops_SGSAGR = _hoops_GRSAGR->next;


	/*
	 * _hoops_RRSAGR 3:
	 *
	 * _hoops_RACIR _hoops_RH _hoops_GASAGR _hoops_PPR _hoops_RASAGR _hoops_CICRR _hoops_CIAH
	 */
	_hoops_HGSAGR = _hoops_IGSAGR;

	do {
		_hoops_GPCIH			*_hoops_AASAGR;

		/* _hoops_RH _hoops_SPS _hoops_CRHAS _hoops_GGR _hoops_RH _hoops_HIGR _hoops_GHCA _hoops_ARGAR _hoops_AARI _hoops_RPP _hoops_CAHC */
		if ((_hoops_AASAGR = _hoops_HGSAGR->next) == _hoops_SGSAGR) {
			bool		_hoops_HASHH;

			_hoops_HASHH = _hoops_SPGPA || !_hoops_GRSAGR->_hoops_HASHH || (_hoops_IGSAGR == _hoops_GRSAGR);

			_hoops_AASAGR = _hoops_IGSAGR;

			_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA]._hoops_HASHH = _hoops_HASHH;
			_hoops_AASAGR->_hoops_GRCPR[_hoops_IGHAS]._hoops_HASHH = _hoops_HASHH;
		}
		else {
			_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA]._hoops_HASHH = true;
			_hoops_AASAGR->_hoops_GRCPR[_hoops_IGHAS]._hoops_HASHH = true;
		}

		/* _hoops_AASA _hoops_SPS _hoops_CRHAS'_hoops_GRI _hoops_RPHR _hoops_RH "_hoops_SPS _hoops_RAAP" _hoops_IIGR _hoops_RGR _hoops_CRHAS */
		_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS] = _hoops_AASAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS];

		/* _hoops_AASA _hoops_RGR _hoops_CRHAS'_hoops_GRI _hoops_RAAP _hoops_RH "_hoops_SPS _hoops_RPHR" _hoops_IIGR _hoops_RH _hoops_SPS _hoops_CRHAS */
		_hoops_AASAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS];
	} while ((_hoops_HGSAGR = _hoops_HGSAGR->next) != _hoops_SGSAGR);



	/*
	 * _hoops_RRSAGR 4:
	 *
	 * _hoops_AIGAA _hoops_RGSAGR
	 */
	_hoops_HGSAGR = _hoops_IGSAGR;
	do {
		_hoops_HGSAGR->type = 0;
		if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS]->y > _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y)
			_hoops_HGSAGR->type |= _hoops_RIGRGR;
		if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS]->y > _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->y)
			_hoops_HGSAGR->type |= _hoops_AIGRGR;
	} while ((_hoops_HGSAGR = _hoops_HGSAGR->next) != _hoops_SGSAGR);

	if (_hoops_IGSAGR == _hoops_GRSAGR) _hoops_IGSAGR->type = _hoops_CGHAS;

	/*
	 * _hoops_RRSAGR 5:
	 *
	 * _hoops_HHHSI _hoops_RH _hoops_RGSAGR _hoops_AARI _hoops_HIS _hoops_SGS _hoops_RH _hoops_RAAP _hoops_HRGR _hoops_CPSA _hoops_RAAP
	 * _hoops_PPR _hoops_RH _hoops_RPHR _hoops_HRGR _hoops_CPSA _hoops_RPHR, _hoops_RPP _hoops_SCH _hoops_GPGH'_hoops_RA _hoops_SGS _hoops_PPRRR _hoops_AIAH.
	 */
	_hoops_HGSAGR = _hoops_IGSAGR;
	do {
		bool _hoops_PASAGR = false;

		if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x == _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x) {
			switch (_hoops_HGSAGR->type) {
			  case _hoops_CGHAS:
				if ((_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS]->x -
					 _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x) *
					(_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS]->y -
					 _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->y) >
					(_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS]->x -
					 _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x) *
					(_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS]->y -
					 _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y))
					_hoops_PASAGR = true;
				break;
			  case _hoops_HIGRGR:
				if ((_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS]->x -
					 _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x) *
					(_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS]->y -
					 _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->y) <
					(_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS]->x -
					 _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x) *
					(_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS]->y -
					 _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y))
					_hoops_PASAGR = true;
				break;
			  case _hoops_RIGRGR:
			  case _hoops_AIGRGR:
				if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS]->y >
					_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS]->y)
					_hoops_PASAGR = true;
				break;
			}
		}
		else if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x >
				 _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x)
			_hoops_PASAGR = true;

		if (_hoops_PASAGR) {
			/* _hoops_GGSHR _hoops_PHARGR _hoops_PPR _hoops_CHAII */
			Swap (_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS], _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]);
			Swap (_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS], _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS]);
			Swap (_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS]._hoops_HASHH,	_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA]._hoops_HASHH);
		}
	} while ((_hoops_HGSAGR = _hoops_HGSAGR->next) != _hoops_SGSAGR);


	/*
	 * _hoops_RRSAGR 6:
	 *
	 * _hoops_GAIGP _hoops_RGSAGR _hoops_HPP _hoops_AHGP _hoops_HASAGR _hoops_HAPC, _hoops_GRP _hoops_PHRSA _hoops_SHARGR.
	 * _hoops_RAP _hoops_GH _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_CRS _hoops_IS _hoops_RGSAGR, _hoops_HIS _hoops_SR _hoops_PAH _hoops_GHIS _hoops_AGAP, _hoops_HRII
	 * _hoops_HSAR _hoops_RH _hoops_HCCGR
	 */
	{
		_hoops_GPCIH			**_hoops_IASAGR;

		ALLOC_ARRAY_CACHED (_hoops_IASAGR, _hoops_CAPAS, _hoops_GPCIH *);
		*_hoops_RPCIH = _hoops_IASAGR;
		_hoops_HGSAGR = _hoops_IGSAGR;
		do *_hoops_IASAGR++ = _hoops_HGSAGR;
		while ((_hoops_HGSAGR = _hoops_HGSAGR->next) != null);
		_hoops_AGSAGR (*_hoops_RPCIH, *_hoops_RPCIH + _hoops_CAPAS - 1);

		/*
		 * _hoops_CASAGR,
		 * _hoops_HCGAR _hoops_RH _hoops_SASAGR
		 */
		return _hoops_CAPAS;
	}
}



typedef struct _hoops_IPPSH {
	struct _hoops_IPPSH		*next;

	Point			_hoops_ICAGA;		/* _hoops_RGAR "_hoops_HAPC" _hoops_HRGR _hoops_SAPIA */
	_hoops_APRGGR		*_hoops_GRCPR[2];
} _hoops_GPSAGR;


local void _hoops_HPAGR (
	_hoops_APRGGR	*edge,
	_hoops_GPSAGR		*_hoops_IPPSH) {

	_hoops_RGGA (edge == null) {
		_hoops_APRGGR	*victim = edge;

		edge = victim->next;
		FREE (victim, _hoops_APRGGR);
	}

	_hoops_RGGA (_hoops_IPPSH == null) {
		_hoops_GPSAGR		*victim = _hoops_IPPSH;

		_hoops_IPPSH = _hoops_IPPSH->next;
		FREE (victim, _hoops_GPSAGR);
	}
}


local void _hoops_RPSAGR (
	_hoops_GPSAGR		*_hoops_IPPSH,
	_hoops_GPSAGR		**_hoops_ASRGR) {

	_hoops_RGGA (*_hoops_ASRGR == null || _hoops_IPPSH->_hoops_ICAGA.y <= (*_hoops_ASRGR)->_hoops_ICAGA.y)
		_hoops_ASRGR = &(*_hoops_ASRGR)->next;

	_hoops_RGGA (*_hoops_ASRGR == null || _hoops_IPPSH->_hoops_ICAGA.y != (*_hoops_ASRGR)->_hoops_ICAGA.y) {
		if (_hoops_IPPSH->_hoops_GRCPR[_hoops_HRASA] == (*_hoops_ASRGR)->_hoops_GRCPR[_hoops_HRASA] &&
			_hoops_IPPSH->_hoops_GRCPR[_hoops_IGHAS] == (*_hoops_ASRGR)->_hoops_GRCPR[_hoops_IGHAS]) {
			FREE (_hoops_IPPSH, _hoops_GPSAGR);
			return;
		}
		_hoops_ASRGR = &(*_hoops_ASRGR)->next;
	}

	_hoops_IPPSH->next = *_hoops_ASRGR;
	*_hoops_ASRGR = _hoops_IPPSH;
}


local bool _hoops_APSAGR (
	_hoops_APRGGR	*left,
	_hoops_APRGGR	*_hoops_PPSAGR,
	float			_hoops_HPSAGR,
	_hoops_GPSAGR		**_hoops_SGIGA) {
	Point		_hoops_RSPSA;
	bool		_hoops_GAHHR;
	int				_hoops_IPSAGR;

	_hoops_GAHHR = (left->pt[_hoops_HGHAS]->x - left->pt[_hoops_PGHAS]->x) *
			   (_hoops_PPSAGR->pt[_hoops_HGHAS]->y - _hoops_PPSAGR->pt[_hoops_PGHAS]->y) >
			   (left->pt[_hoops_HGHAS]->y - left->pt[_hoops_PGHAS]->y) *
			   (_hoops_PPSAGR->pt[_hoops_HGHAS]->x - _hoops_PPSAGR->pt[_hoops_PGHAS]->x);

	if (_hoops_GAHHR)
		_hoops_IPSAGR = HI_Intersect_Line_Segments_2D (left->pt[_hoops_PGHAS], left->pt[_hoops_HGHAS],
													_hoops_PPSAGR->pt[_hoops_PGHAS], _hoops_PPSAGR->pt[_hoops_HGHAS],
													&_hoops_RSPSA);
	else
		_hoops_IPSAGR = HI_Intersect_Line_Segments_2D (_hoops_PPSAGR->pt[_hoops_PGHAS], _hoops_PPSAGR->pt[_hoops_HGHAS],
													left->pt[_hoops_PGHAS], left->pt[_hoops_HGHAS],
													&_hoops_RSPSA);

	if (_hoops_IPSAGR > 0 && _hoops_RSPSA.y >= _hoops_HPSAGR) {
		if (left->owner != _hoops_PPSAGR->owner && left->_hoops_HASHH && _hoops_PPSAGR->_hoops_HASHH)
			return true;

		if (_hoops_RSPSA.y == left->pt[_hoops_PGHAS]->y &&
			_hoops_RSPSA.y == _hoops_PPSAGR->pt[_hoops_PGHAS]->y) {

			/* "_hoops_ARCRA" _hoops_HPGR _hoops_PRPC, _hoops_GAAP _hoops_AIAH _hoops_GGR _hoops_GGSP _hoops_AGR */
			if ((left->pt[_hoops_HGHAS]->x - left->pt[_hoops_PGHAS]->x) *
				(_hoops_PPSAGR->pt[_hoops_HGHAS]->y - _hoops_PPSAGR->pt[_hoops_PGHAS]->y) <
				(left->pt[_hoops_HGHAS]->y - left->pt[_hoops_PGHAS]->y) *
				(_hoops_PPSAGR->pt[_hoops_HGHAS]->x - _hoops_PPSAGR->pt[_hoops_PGHAS]->x)) return false;
		}

		{
			_hoops_GPSAGR		*_hoops_SAIAR;

			ALLOC (_hoops_SAIAR, _hoops_GPSAGR);
			_hoops_SAIAR->_hoops_ICAGA = _hoops_RSPSA;
			if (_hoops_GAHHR) {
				_hoops_SAIAR->_hoops_GRCPR[_hoops_HRASA] = left;
				_hoops_SAIAR->_hoops_GRCPR[_hoops_IGHAS] = _hoops_PPSAGR;
			}
			else {
				_hoops_SAIAR->_hoops_GRCPR[_hoops_HRASA] = _hoops_PPSAGR;
				_hoops_SAIAR->_hoops_GRCPR[_hoops_IGHAS] = left;
			}
			_hoops_RPSAGR (_hoops_SAIAR, _hoops_SGIGA);

			return false;
		}
	}
	else if (_hoops_IPSAGR < 0) {	/* _hoops_SPRPA, _hoops_CACH _hoops_RPP _hoops_CGISH _hoops_RSSAI */
		Vector			l, p1, p2;
		float				t, _hoops_SSHGA;

		l.x = left->pt[_hoops_HGHAS]->x - left->pt[_hoops_PGHAS]->x;
		l.y = left->pt[_hoops_HGHAS]->y - left->pt[_hoops_PGHAS]->y;
		l.z = 0.0f;

		p1.x = _hoops_PPSAGR->pt[_hoops_PGHAS]->x - left->pt[_hoops_PGHAS]->x;
		p1.y = _hoops_PPSAGR->pt[_hoops_PGHAS]->y - left->pt[_hoops_PGHAS]->y;
		p1.z = 0.0f;

		p2.x = _hoops_PPSAGR->pt[_hoops_HGHAS]->x - left->pt[_hoops_PGHAS]->x;
		p2.y = _hoops_PPSAGR->pt[_hoops_HGHAS]->y - left->pt[_hoops_PGHAS]->y;
		p2.z = 0.0f;

		_hoops_SSHGA = l.x * l.x  +  l.y * l.y;

		/* _hoops_AGCR _hoops_HCGC _hoops_GPICR _hoops_HPIAA _hoops_RH _hoops_SGHC _hoops_CHR _hoops_RGCGA _hoops_GGR _hoops_RH _hoops_PSHR _hoops_HAGA */
		t = (p1.x * l.x + p1.y * l.y) / _hoops_SSHGA;
		if (t > 1.0f)
			return false;	/* _hoops_RPHR _hoops_III _hoops_PAIHH _hoops_GRHCP _hoops_RSGR _hoops_IIGR _hoops_RAAP _hoops_III */

		t = (p2.x * l.x + p2.y * l.y) / _hoops_SSHGA;
		if (t < 0.0f)
			return false;	/* _hoops_RPHR _hoops_III _hoops_HCPA _hoops_ARPP _hoops_HSPP _hoops_IIGR _hoops_RAAP _hoops_III */

		/* _hoops_PIHA _hoops_RSSAI, _hoops_CACH _hoops_RPP _hoops_SGS'_hoops_GRI _hoops_PSIGA */
		if (left->owner != _hoops_PPSAGR->owner && left->_hoops_HASHH && _hoops_PPSAGR->_hoops_HASHH)
			return true;
	}
	return false;
}

local bool _hoops_CPSAGR (
	_hoops_APRGGR	*edge,
	_hoops_GPCIH			*_hoops_RGHAS) {
	Point		*start;
	Point		*end;
	float			level;
	float			x;

	level = _hoops_RGHAS->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y;
	start = edge->pt[_hoops_PGHAS];
	end = edge->pt[_hoops_HGHAS];

	x = start->x  +	 (end->x - start->x) *
						(level - start->y) / (end->y - start->y);

	return	_hoops_RGHAS->_hoops_SSAGS[_hoops_HRASA] < x	 &&	 x < _hoops_RGHAS->_hoops_SSAGS[_hoops_IGHAS];
}
#endif



/* _hoops_HRS 1 _hoops_IH _hoops_RHHR, 0 _hoops_IH _hoops_CPHS, -1 _hoops_RPP _hoops_PAH'_hoops_RA _hoops_IPCA */

GLOBAL_FUNCTION int HI_Wings_Intersect (
	int				_hoops_PGSIH,
	_hoops_GPCIH			**_hoops_HGSIH,
	int				_hoops_IGSIH,
	_hoops_GPCIH			**_hoops_CGSIH) {
#ifndef DISABLE_POLY_SELECTION
	_hoops_APRGGR	*_hoops_GRCPR = null;
	_hoops_GPSAGR		*_hoops_SGIGA = null;
	float			_hoops_HPSAGR;
	_hoops_GPSAGR		*_hoops_SPSAGR;


	_hoops_PCCAR {
		_hoops_APRGGR	*_hoops_GHSAGR;
		_hoops_GPCIH			*_hoops_HGSAGR;

		/*
		 * _hoops_RHSAGR _hoops_ARSAGR _hoops_CRHAS _hoops_HII _hoops_ISPP _hoops_IIGR _hoops_PGI _hoops_AHSAGR _hoops_PAR _hoops_PHSAGR.
		 */
		if (_hoops_PGSIH == 0 || _hoops_IGSIH == 0) {
			_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
			return 0;
		}
		else {
			if (_hoops_SSCAGR (*_hoops_HGSIH, *_hoops_CGSIH)) {
				_hoops_HGSAGR = *_hoops_HGSIH++;
				--_hoops_PGSIH;
			}
			else {
				_hoops_HGSAGR = *_hoops_CGSIH++;
				--_hoops_IGSIH;
			}
		}


		/*
		 * _hoops_ISRPA _hoops_PHPA-_hoops_GHCP _hoops_ARRSH _hoops_ARPP _hoops_PRCA _hoops_RH _hoops_SCGR _hoops_CRHAS
		 */
		_hoops_SPSAGR = _hoops_SGIGA;
		_hoops_RGGA (_hoops_SGIGA == null ||
			   _hoops_SGIGA->_hoops_ICAGA.y > _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y) {
			_hoops_GPSAGR		*_hoops_SAIAR;

			_hoops_SAIAR = _hoops_SGIGA;
			_hoops_HPSAGR = _hoops_SAIAR->_hoops_ICAGA.y;

			for (_hoops_GHSAGR = _hoops_GRCPR;
						_hoops_GHSAGR != null;
								_hoops_GHSAGR = _hoops_GHSAGR->next) {
				if (_hoops_SAIAR->_hoops_GRCPR[_hoops_HRASA] == _hoops_GHSAGR) {
					if (_hoops_GHSAGR->next == null || _hoops_SAIAR->_hoops_GRCPR[_hoops_IGHAS] != _hoops_GHSAGR->next) {
						if (_hoops_SGIGA->next != null &&
							_hoops_SGIGA->next->_hoops_ICAGA.y == _hoops_SAIAR->_hoops_ICAGA.y &&
							_hoops_SGIGA->next != _hoops_SPSAGR) {
							/* _hoops_ARRSH _hoops_GHCA _hoops_SHH _hoops_GGSR _hoops_IIGR _hoops_AGR, _hoops_HPPR _hoops_RH _hoops_SPS _hoops_SPR */
							_hoops_GPSAGR	**_hoops_ASRGR;
							_hoops_SGIGA = _hoops_SGIGA->next;
							_hoops_ASRGR = &_hoops_SGIGA->next;
							while (*_hoops_ASRGR != null && (*_hoops_ASRGR)->_hoops_ICAGA.y == _hoops_SAIAR->_hoops_ICAGA.y)
								_hoops_ASRGR = &(*_hoops_ASRGR)->next;
							_hoops_SAIAR->next = *_hoops_ASRGR;
							*_hoops_ASRGR = _hoops_SAIAR;
							goto _hoops_HHSAGR;
						}

						/* _hoops_CISS _hoops_IHGC _hoops_IIGR _hoops_CPHP... */
						_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
						return -1;
					}

#ifdef _hoops_CGSPR
					printf ("Crossing at %f %f %f\n",
							 _hoops_SAIAR->_hoops_ICAGA.x,
							 _hoops_SAIAR->_hoops_ICAGA.y,
							 _hoops_SAIAR->_hoops_ICAGA.z);
#endif

					/* _hoops_IHSAGR _hoops_PHARGR _hoops_PPR _hoops_CHAII */
					_hoops_GHSAGR->next->prev = _hoops_GHSAGR->prev;
					if (_hoops_GHSAGR->prev != null)
						_hoops_GHSAGR->prev->next = _hoops_GHSAGR->next;
					else
						_hoops_GRCPR = _hoops_GHSAGR->next;
					_hoops_GHSAGR->prev = _hoops_GHSAGR->next;
					_hoops_GHSAGR->next = _hoops_GHSAGR->next->next;
					if (_hoops_GHSAGR->next != null)
						_hoops_GHSAGR->next->prev = _hoops_GHSAGR;
					_hoops_GHSAGR->prev->next = _hoops_GHSAGR;

					{
						int		_hoops_HIPGR = _hoops_GHSAGR->prev->region;

						_hoops_GHSAGR->prev->region ^= _hoops_GHSAGR->region;
						if (_hoops_GHSAGR->prev->prev != null)
							_hoops_GHSAGR->prev->region ^= _hoops_GHSAGR->prev->prev->region;
						_hoops_GHSAGR->region = _hoops_HIPGR;
					}

					if (_hoops_GHSAGR->prev->prev != null &&
						_hoops_APSAGR (_hoops_GHSAGR->prev, _hoops_GHSAGR->prev->prev,
									 _hoops_HPSAGR, &_hoops_SGIGA) ||
						_hoops_GHSAGR->next != null &&
						_hoops_APSAGR (_hoops_GHSAGR, _hoops_GHSAGR->next,
									 _hoops_HPSAGR, &_hoops_SGIGA)) {
						_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
						return 1;
					}

					break;		/* _hoops_RIARR _hoops_GIPHR */
				}
			}

			_hoops_SGIGA = _hoops_SGIGA->next;
			FREE (_hoops_SAIAR, _hoops_GPSAGR);
			_hoops_SPSAGR = _hoops_SGIGA;

			_hoops_HHSAGR:;
		}


		_hoops_HPSAGR = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y;

		switch (_hoops_HGSAGR->type) {
			case _hoops_CGHAS: {
				_hoops_APRGGR	*_hoops_GPGRH;
				_hoops_APRGGR	*_hoops_CHSAGR;

#ifdef _hoops_CGSPR
				if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x ==
						_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x)
					printf ("%d Valley at %f %f %f\n",
							_hoops_HGSAGR->owner,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->z);
				else
					printf ("%d Valley at [%f,%f] %f %f\n",
							_hoops_HGSAGR->owner,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->z);
#endif
				/*
				 * _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_ISHA _hoops_PSAI _hoops_HII _hoops_RH _hoops_CRHAS
				 */
				ALLOC (_hoops_GPGRH, _hoops_APRGGR);
				_hoops_GPGRH->region = _hoops_HGSAGR->region;
				_hoops_GPGRH->owner = _hoops_HGSAGR->owner;
				_hoops_GPGRH->_hoops_HASHH = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA]._hoops_HASHH;
				_hoops_GPGRH->pt[_hoops_PGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS];
				_hoops_GPGRH->pt[_hoops_HGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS];

				ALLOC (_hoops_CHSAGR, _hoops_APRGGR);
				_hoops_CHSAGR->region = 0;
				_hoops_CHSAGR->owner = _hoops_HGSAGR->owner;
				_hoops_CHSAGR->_hoops_HASHH = _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS]._hoops_HASHH;
				_hoops_CHSAGR->pt[_hoops_PGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS];
				_hoops_CHSAGR->pt[_hoops_HGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS];

				if (_hoops_GPGRH->pt[_hoops_PGHAS] != _hoops_CHSAGR->pt[_hoops_PGHAS])
					_hoops_APSAGR (_hoops_GPGRH, _hoops_CHSAGR, _hoops_HPSAGR, &_hoops_SGIGA);

				/*
				 * _hoops_CARR _hoops_RGR _hoops_CCAH _hoops_PSAI _hoops_CRGR _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_RRGP
				 */
				if ((_hoops_GHSAGR = _hoops_GRCPR) == null) {
					/*
					 * _hoops_ICSH _hoops_HRGR _hoops_IRAP -- _hoops_RGR _hoops_PSAI _hoops_RHCHR _hoops_RH _hoops_HIGR
					 */
					_hoops_GRCPR = _hoops_GPGRH;
					_hoops_GPGRH->prev = null;
					_hoops_GPGRH->next = _hoops_CHSAGR;
					_hoops_CHSAGR->prev = _hoops_GPGRH;
					_hoops_CHSAGR->next = null;
				}
				else {
					/*
					 * _hoops_CPRGS _hoops_IS _hoops_SSS _hoops_AGGPR _hoops_ACAGR _hoops_IH _hoops_CCAH _hoops_RAAP _hoops_ISHA
					 */

					do {
						if (_hoops_GPGRH->pt[_hoops_PGHAS]->y != _hoops_GHSAGR->pt[_hoops_PGHAS]->y &&
							((_hoops_GPGRH->pt[_hoops_PGHAS]->x - _hoops_GHSAGR->pt[_hoops_PGHAS]->x) *
							 (_hoops_GHSAGR->pt[_hoops_HGHAS]->y - _hoops_GHSAGR->pt[_hoops_PGHAS]->y) <
							 (_hoops_GPGRH->pt[_hoops_PGHAS]->y - _hoops_GHSAGR->pt[_hoops_PGHAS]->y) *
							 (_hoops_GHSAGR->pt[_hoops_HGHAS]->x - _hoops_GHSAGR->pt[_hoops_PGHAS]->x)) ||
							_hoops_GPGRH->pt[_hoops_PGHAS]->y == _hoops_GHSAGR->pt[_hoops_PGHAS]->y &&
							_hoops_GPGRH->pt[_hoops_PGHAS]->x < _hoops_GHSAGR->pt[_hoops_PGHAS]->x) {
							_hoops_GPGRH->prev = _hoops_GHSAGR->prev;
							_hoops_GPGRH->next = _hoops_GHSAGR;
							_hoops_GHSAGR->prev = _hoops_GPGRH;
							if (_hoops_GPGRH->prev != null)
								_hoops_GPGRH->prev->next = _hoops_GPGRH;
							if (_hoops_GRCPR == _hoops_GHSAGR) _hoops_GRCPR = _hoops_GPGRH;
							/* _hoops_SHSAGR = _hoops_GISAGR; */

							break;
						}
						else if (_hoops_GHSAGR->next == null) {
							_hoops_GPGRH->prev = _hoops_GHSAGR;
							_hoops_GPGRH->next = null;
							_hoops_GHSAGR->next = _hoops_GPGRH;
							_hoops_GHSAGR = _hoops_GPGRH;

							break;
						}
					} _hoops_RGGA ((_hoops_GHSAGR = _hoops_GHSAGR->next) == null);


					if (_hoops_GPGRH->prev != null &&
						_hoops_GPGRH->prev->region) {
						if (_hoops_GPGRH->prev->region != _hoops_HGSAGR->region) {
							FREE (_hoops_CHSAGR, _hoops_APRGGR); /* _hoops_HAR _hoops_GGR _hoops_SPPR _hoops_HIGR */
							_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
							return 1;
						}
						else {
							_hoops_GPGRH->region = 0;
							_hoops_CHSAGR->region = _hoops_HGSAGR->region;
						}
					}

					/*
					 * _hoops_CPRGS _hoops_IS _hoops_SSS _hoops_AGGPR _hoops_ACAGR _hoops_IH _hoops_CCAH _hoops_RPHR _hoops_ISHA
					 */

					if (_hoops_GPGRH->next == null ||
						_hoops_GPGRH->pt[_hoops_PGHAS] == _hoops_CHSAGR->pt[_hoops_PGHAS]) {
						_hoops_CHSAGR->prev = _hoops_GPGRH;
						_hoops_CHSAGR->next = _hoops_GPGRH->next;
						if (_hoops_GPGRH->next != null)
							_hoops_GPGRH->next->prev = _hoops_CHSAGR;
						_hoops_GPGRH->next = _hoops_CHSAGR;
					}
					else do {
						if (_hoops_CHSAGR->pt[_hoops_PGHAS]->y != _hoops_GHSAGR->pt[_hoops_PGHAS]->y &&
							((_hoops_CHSAGR->pt[_hoops_PGHAS]->x - _hoops_GHSAGR->pt[_hoops_PGHAS]->x) *
							 (_hoops_GHSAGR->pt[_hoops_HGHAS]->y - _hoops_GHSAGR->pt[_hoops_PGHAS]->y) <
							 (_hoops_CHSAGR->pt[_hoops_PGHAS]->y - _hoops_GHSAGR->pt[_hoops_PGHAS]->y) *
							 (_hoops_GHSAGR->pt[_hoops_HGHAS]->x - _hoops_GHSAGR->pt[_hoops_PGHAS]->x)) ||
							_hoops_CHSAGR->pt[_hoops_PGHAS]->y == _hoops_GHSAGR->pt[_hoops_PGHAS]->y &&
							_hoops_CHSAGR->pt[_hoops_PGHAS]->x < _hoops_GHSAGR->pt[_hoops_PGHAS]->x) {
							_hoops_CHSAGR->prev = _hoops_GHSAGR->prev;
							_hoops_CHSAGR->next = _hoops_GHSAGR;
							_hoops_GHSAGR->prev = _hoops_CHSAGR;
							_hoops_CHSAGR->prev->next = _hoops_CHSAGR;
							break;
						}
						else if (_hoops_GHSAGR->next == null) {
							_hoops_CHSAGR->next = null;
							_hoops_CHSAGR->prev = _hoops_GHSAGR;
							_hoops_GHSAGR->next = _hoops_CHSAGR;
							break;
						}
					} _hoops_RGGA ((_hoops_GHSAGR = _hoops_GHSAGR->next) == null);


					if (_hoops_GPGRH->next != _hoops_CHSAGR) {
						_hoops_GHSAGR = _hoops_GPGRH->next;
						do {
							if (_hoops_GHSAGR->_hoops_HASHH &&
								_hoops_GHSAGR->owner != _hoops_GPGRH->owner &&
								(_hoops_HGSAGR->_hoops_HASHH ||
								 !_hoops_CPSAGR (_hoops_GHSAGR, _hoops_HGSAGR))) {
								_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
								return 1;
							}

							_hoops_GHSAGR->region ^= _hoops_HGSAGR->region;
						} _hoops_RGGA ((_hoops_GHSAGR = _hoops_GHSAGR->next) == _hoops_CHSAGR);
						_hoops_CHSAGR->region = _hoops_CHSAGR->prev->region ^ _hoops_HGSAGR->region;

						if (_hoops_CHSAGR->prev->region &&
							_hoops_CHSAGR->prev->region != _hoops_HGSAGR->region) {
							_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
							return 1;
						}

						if (_hoops_GPGRH->prev != null &&
							_hoops_APSAGR (_hoops_GPGRH->prev, _hoops_GPGRH, _hoops_HPSAGR, &_hoops_SGIGA) ||
							_hoops_APSAGR (_hoops_GPGRH, _hoops_GPGRH->next, _hoops_HPSAGR, &_hoops_SGIGA) ||
							_hoops_APSAGR (_hoops_CHSAGR->prev, _hoops_CHSAGR, _hoops_HPSAGR, &_hoops_SGIGA) ||
							_hoops_CHSAGR->next != null &&
							_hoops_APSAGR (_hoops_CHSAGR, _hoops_CHSAGR->next, _hoops_HPSAGR, &_hoops_SGIGA)) {
							_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
							return 1;
						}
					}
					else {
						if (_hoops_GPGRH->prev != null &&
							_hoops_APSAGR (_hoops_GPGRH->prev, _hoops_GPGRH, _hoops_HPSAGR, &_hoops_SGIGA) ||
							_hoops_CHSAGR->next != null &&
							_hoops_APSAGR (_hoops_CHSAGR, _hoops_CHSAGR->next, _hoops_HPSAGR, &_hoops_SGIGA)) {
							_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
							return 1;
						}
					}
				}
			}	break;


			case _hoops_HIGRGR: {
				_hoops_APRGGR	*_hoops_RISAGR;
				_hoops_APRGGR	*_hoops_AISAGR;
				int		_hoops_PISAGR;

#ifdef _hoops_CGSPR
				if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x ==
						_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x)
					printf ("%d Peak at %f %f %f\n",
							_hoops_HGSAGR->owner,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->z);
				else
					printf ("%d Peak at [%f,%f] %f %f\n",
							_hoops_HGSAGR->owner,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->z);
#endif

				_hoops_RISAGR = _hoops_GRCPR;

				/* _hoops_CPRGS _hoops_IH _hoops_RAAP _hoops_ISHA */
				_hoops_RGGA (_hoops_RISAGR->pt[_hoops_HGHAS] == _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]) {
					if ((_hoops_RISAGR = _hoops_RISAGR->next) == null) {
						_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
						return -1;
					}
				}

				/* _hoops_GPASR _hoops_RH _hoops_RPHR _hoops_ISHA */
				_hoops_AISAGR = _hoops_RISAGR->next;
				_hoops_PCCAR {
					if (_hoops_AISAGR == null) {
						/* _hoops_CISS _hoops_IHGC _hoops_IIGR _hoops_CPHP... */
						_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
						return -1;
					}

					if (_hoops_AISAGR->pt[_hoops_HGHAS] == _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS])
						break;

					_hoops_AISAGR = _hoops_AISAGR->next;
				}

				/* _hoops_GHAA _hoops_SIISR */
				_hoops_PISAGR = _hoops_RISAGR->region ^ _hoops_AISAGR->region;

				_hoops_GHSAGR = _hoops_RISAGR->next;
				_hoops_RGGA (_hoops_GHSAGR == _hoops_AISAGR) {
					if (_hoops_GHSAGR->_hoops_HASHH &&
						_hoops_GHSAGR->owner != _hoops_AISAGR->owner &&
						(_hoops_HGSAGR->_hoops_HASHH ||
						 !_hoops_CPSAGR (_hoops_GHSAGR, _hoops_HGSAGR))) {
						_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
						return 1;
					}

					_hoops_GHSAGR->region ^= _hoops_PISAGR;

					_hoops_GHSAGR = _hoops_GHSAGR->next;
				}

				/* _hoops_ISPR _hoops_ARRSH */
				if (_hoops_RISAGR->prev != null &&
					_hoops_APSAGR (_hoops_RISAGR->prev, _hoops_RISAGR->next,
								 _hoops_HPSAGR, &_hoops_SGIGA) ||
					_hoops_AISAGR->next != null &&
					_hoops_APSAGR (_hoops_AISAGR->prev, _hoops_AISAGR->next,
								 _hoops_HPSAGR, &_hoops_SGIGA)) {
					_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
					return 1;
				}

				/* _hoops_HRCHR */
				if (_hoops_RISAGR->prev != null)
					_hoops_RISAGR->prev->next = _hoops_RISAGR->next;
				else
					_hoops_GRCPR = _hoops_RISAGR->next;
				/* _hoops_PIHA _hoops_SHH _hoops_IRS _hoops_SPS _hoops_ARI (_hoops_HPGR _hoops_CHGC "_hoops_HISAGR") */
				_hoops_RISAGR->next->prev = _hoops_RISAGR->prev;
				FREE (_hoops_RISAGR, _hoops_APRGGR);

				if (_hoops_AISAGR->next != null)
					_hoops_AISAGR->next->prev = _hoops_AISAGR->prev;
				if (_hoops_AISAGR->prev != null)
					_hoops_AISAGR->prev->next = _hoops_AISAGR->next;
				else
					_hoops_GRCPR = _hoops_AISAGR->next;
				FREE (_hoops_AISAGR, _hoops_APRGGR);
			}	break;


			case _hoops_RIGRGR:
			case _hoops_AIGRGR: {
				_hoops_APRGGR	*lower;
				_hoops_APRGGR	*upper;

#ifdef _hoops_CGSPR
				if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x ==
						_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x)
					printf ("%d Bend at %f %f %f\n",
							_hoops_HGSAGR->owner,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->z);
				else
					printf ("%d Bend at [%f,%f] %f %f\n",
							_hoops_HGSAGR->owner,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y,
							_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->z);
#endif
				/*
				 * _hoops_CPRGS _hoops_IS _hoops_SSS _hoops_PIS _hoops_ACAGR _hoops_IH _hoops_GSSC _hoops_ISHA
				 */
				if ((lower = _hoops_GRCPR) == null) {
					_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
					return -1;
				}
				_hoops_RGGA (lower->pt[_hoops_HGHAS] == _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS] ||
					   lower->pt[_hoops_HGHAS] == _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]) {
					if ((lower = lower->next) == null) {
						_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
						return -1;
					}
				}

				if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS] == _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]) {
					if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS]->y <
						_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS]->y) {
						lower->pt[_hoops_PGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS];
						lower->pt[_hoops_HGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS];
						lower->_hoops_HASHH = _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS]._hoops_HASHH;
					}
					else {
						lower->pt[_hoops_PGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS];
						lower->pt[_hoops_HGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS];
						lower->_hoops_HASHH = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA]._hoops_HASHH;
					}

					if (lower->prev != null &&
						_hoops_APSAGR (lower->prev, lower, _hoops_HPSAGR, &_hoops_SGIGA) ||
						lower->next != null &&
						_hoops_APSAGR (lower, lower->next, _hoops_HPSAGR, &_hoops_SGIGA)) {
						_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
						return 1;
					}
				}
				else {
					if (lower->pt[_hoops_HGHAS] == _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]) {
						lower->pt[_hoops_PGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS];
						lower->pt[_hoops_HGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS];
						lower->_hoops_HASHH = _hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS]._hoops_HASHH;

						if ((upper = lower->next) != null) {
							int		_hoops_GRGGH;

							_hoops_GRGGH = lower->region;
							if (lower->prev != null) _hoops_GRGGH ^= lower->prev->region;

							do if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->y != upper->pt[_hoops_PGHAS]->y &&
								((_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x - upper->pt[_hoops_PGHAS]->x) *
								 (upper->pt[_hoops_HGHAS]->y - upper->pt[_hoops_PGHAS]->y) <
								 (_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->y - upper->pt[_hoops_PGHAS]->y) *
								 (upper->pt[_hoops_HGHAS]->x - upper->pt[_hoops_PGHAS]->x)) ||
								_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->y == upper->pt[_hoops_PGHAS]->y &&
								_hoops_HGSAGR->_hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS]->x < upper->pt[_hoops_PGHAS]->x) {
								if (upper != lower->next) {
									if (lower->prev != null)
										lower->prev->next = lower->next;
									else
										_hoops_GRCPR = lower->next;
									lower->next->prev = lower->prev;

									lower->prev = upper->prev;
									lower->next = upper;
									upper->prev->next = lower;
									upper->prev = lower;
								}

								break;
							}
							else {
								if (upper->_hoops_HASHH &&
									upper->owner != lower->owner &&
									(_hoops_HGSAGR->_hoops_HASHH ||
									 !_hoops_CPSAGR (upper, _hoops_HGSAGR))) {
									_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
									return 1;
								}

								upper->region ^= _hoops_GRGGH;

								if (upper->next == null) {
									if (lower->prev != null)
										lower->prev->next = lower->next;
									else
										_hoops_GRCPR = lower->next;
									lower->next->prev = lower->prev;

									lower->prev = upper;
									lower->next = null;
									upper->next = lower;

									break;
								}
							} _hoops_RGGA ((upper = upper->next) == null);
						}
					}
					else {
						lower->pt[_hoops_PGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS];
						lower->pt[_hoops_HGHAS] = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS];
						lower->_hoops_HASHH = _hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA]._hoops_HASHH;

						if ((upper = lower->prev) != null) {
							int		_hoops_GRGGH;

							_hoops_GRGGH = lower->region;
							if (lower->next != null) _hoops_GRGGH ^= lower->next->region;

							do if (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y != upper->pt[_hoops_PGHAS]->y &&
								((_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x - upper->pt[_hoops_PGHAS]->x) *
								 (upper->pt[_hoops_HGHAS]->y - upper->pt[_hoops_PGHAS]->y) >
								 (_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y - upper->pt[_hoops_PGHAS]->y) *
								 (upper->pt[_hoops_HGHAS]->x - upper->pt[_hoops_PGHAS]->x)) ||
								_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->y == upper->pt[_hoops_PGHAS]->y &&
								_hoops_HGSAGR->_hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS]->x > upper->pt[_hoops_PGHAS]->x) {
								if (upper != lower->prev) {
									if (lower->next != null)
										lower->next->prev = lower->prev;
									lower->prev->next = lower->next;

									lower->prev = upper;
									lower->next = upper->next;
									upper->next->prev = lower;
									upper->next = lower;
								}

								break;
							}
							else {
								if (upper->_hoops_HASHH &&
									upper->owner != lower->owner &&
									(_hoops_HGSAGR->_hoops_HASHH ||
									 !_hoops_CPSAGR (upper, _hoops_HGSAGR))) {
									_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
									return 1;
								}

								upper->region ^= _hoops_GRGGH;

								if (upper->prev == null) {
									if (lower->next != null)
										lower->next->prev = lower->prev;
									lower->prev->next = lower->next;

									lower->prev = null;
									lower->next = upper;
									upper->prev = lower;
									_hoops_GRCPR = lower;

									break;
								}
							} _hoops_RGGA ((upper = upper->prev) == null);
						}
					}


					if (lower->prev != null &&
						_hoops_APSAGR (lower->prev, lower, _hoops_HPSAGR, &_hoops_SGIGA) ||
						lower->next != null &&
						_hoops_APSAGR (lower, lower->next, _hoops_HPSAGR, &_hoops_SGIGA)) {
						_hoops_HPAGR (_hoops_GRCPR, _hoops_SGIGA);
						return 1;
					}
				}
			}	break;
		  }
	}

	/*
	 * _hoops_ASAI _hoops_IISAGR
	 *
	 * _hoops_GGAS (_hoops_SPPR, _hoops_ARRSH);
	 * _hoops_ASRC 0;
	 */
#else
	return 0;
#endif
}

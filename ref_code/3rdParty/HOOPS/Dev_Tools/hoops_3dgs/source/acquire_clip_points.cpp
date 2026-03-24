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
 * $Id: obf_tmp.txt 1.77 2010-10-06 19:16:14 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



GLOBAL_FUNCTION int HD_Compute_Trimmed_Clip_Points (
	_hoops_HHCR const &		_hoops_IHCR,
	int								count,
	DC_Point const *				_hoops_CGCAR,
	float const *					_hoops_SGCAR,
	_hoops_GRCAR alter *				_hoops_RRCAR) {
	DC_Point const *				point;
	_hoops_GRCAR alter *				_hoops_ARCAR;
	float							a, b, c, d;
	DC_Point const *				end = _hoops_CGCAR + count;
	int								_hoops_PRCAR;
	float const *					ws;
	_hoops_IAPA const *		_hoops_HRCAR;
	_hoops_GPPA const *	_hoops_IRCAR;
	int								_hoops_CRCAR = 0;
	int								_hoops_SRCAR;
	bool							_hoops_GACAR;

	_hoops_GACAR = !_hoops_PGSC (_hoops_IHCR->_hoops_HGSC);

	_hoops_HRCAR = _hoops_IHCR->_hoops_RGH->_hoops_PHCA;

	do {
		_hoops_SRCAR = count;

		_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA;
		do {
			point = _hoops_CGCAR;
			ws = _hoops_SGCAR;
			_hoops_ARCAR = _hoops_RRCAR;
			a = _hoops_IRCAR->_hoops_SPPA.a;
			b = _hoops_IRCAR->_hoops_SPPA.b;
			c = _hoops_IRCAR->_hoops_SPPA.c;
			d = _hoops_IRCAR->_hoops_SPPA.d;
			_hoops_PRCAR = count;

			/* _hoops_RHCS _hoops_ACSRR _hoops_PCCP _hoops_IGGA _hoops_HPPA _hoops_IPPA */

			/* _hoops_PS _hoops_SGH "_hoops_RACAR" _hoops_HRII _hoops_HSAR 0.0 _hoops_IAPR _hoops_GPP _hoops_RH _hoops_RPHR-_hoops_AACAR _hoops_PPAP _hoops_IIGR _hoops_RH
			 * _hoops_RPGP _hoops_PACAR. _hoops_HGI _hoops_HACAR 1 _hoops_SAPS-_hoops_PPSR _hoops_GGCR _hoops_GPP _hoops_ICRP _hoops_IACAR.
			 *
			 * _hoops_IPCP "_hoops_CACAR" _hoops_RPR _hoops_HRGR _hoops_SACAR _hoops_CCA _hoops_GPCAR _hoops_IS
			 * *_hoops_RGR* _hoops_IPPA.
			 */

			if (_hoops_GACAR) {
				/* (_hoops_HCR _hoops_RH _hoops_RSSA _hoops_APGP _hoops_HS _hoops_AHCR == 0) */
				do {
					if (point->x * a + point->y * b + d > 0) {
						--_hoops_PRCAR;				/* _hoops_RPR _hoops_SCH */
						*_hoops_ARCAR |= _hoops_RPCAR;	/* _hoops_HPGGR _hoops_SCH */
					}
					++_hoops_ARCAR;
				} _hoops_RGGA (++point == end);
			}
			else {
				/* _hoops_HRSP-_hoops_APCAR _hoops_RPGP */

				if (a == 0.0f && b == 0.0f) {
					/* _hoops_SGGC _hoops_IH _hoops_HPPA _hoops_IPPA _hoops_AARGR _hoops_IS _hoops_AHCR -
					 * _hoops_IRS _hoops_PPCAR _hoops_AGIR?
					 */

					if (c > 0.0f) {
						d /= c;
						do {
							float		w = 1.0f;	/* _hoops_HPCAR _hoops_SCGA */

							if (BIT (*_hoops_ARCAR, _hoops_IPCAR))
								w = *ws;

							if (point->z + w*d > 0) {
								--_hoops_PRCAR;	  /* _hoops_RPR _hoops_SCH */
								*_hoops_ARCAR |= _hoops_RPCAR; /* _hoops_HPGGR _hoops_SCH */
							}
							++ws;
							++_hoops_ARCAR;
						} _hoops_RGGA (++point == end);
					}
					else if (c < 0.0f) {
						d /= c;
						do {
							float		w = 1.0f;	/* _hoops_HPCAR _hoops_SCGA */

							if (BIT (*_hoops_ARCAR, _hoops_IPCAR))
								w = *ws;

							if (point->z + w*d < 0) {
								--_hoops_PRCAR;	  /* _hoops_RPR _hoops_SCH */
								*_hoops_ARCAR |= _hoops_RPCAR; /* _hoops_HPGGR _hoops_SCH */
							}
							++ws;
							++_hoops_ARCAR;
						} _hoops_RGGA (++point == end);
					}
					else _hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Strange cut plane");
				}
				else {
					do {
						float		w = 1.0f;	/* _hoops_HPCAR _hoops_SCGA */

						if (BIT (*_hoops_ARCAR, _hoops_IPCAR))
							w = *ws;

						if (point->x*a + point->y*b + point->z*c + w*d > 0) {
							--_hoops_PRCAR;	  /* _hoops_RPR _hoops_SCH */
							*_hoops_ARCAR |= _hoops_RPCAR; /* _hoops_HPGGR _hoops_SCH */
						}
						++ws;
						++_hoops_ARCAR;
					} _hoops_RGGA (++point == end);
				}
			}

			if (_hoops_PRCAR < _hoops_SRCAR)
				_hoops_SRCAR = _hoops_PRCAR;
		} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);

		if (_hoops_SRCAR > _hoops_CRCAR)
			_hoops_CRCAR = _hoops_SRCAR;
	} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);
	
	return _hoops_CRCAR;
}



#define _hoops_CPCAR	50		/* _hoops_SPCAR _hoops_IIGR _hoops_RSSA _hoops_HAHH _hoops_IS
										 * _hoops_IRHH _hoops_SCH _hoops_GHCAR _hoops_IS _hoops_SRS
										 * _hoops_HIHP _hoops_PPR _hoops_ISPR _hoops_RH _hoops_IASC
										 * _hoops_AHCRR. */
local int _hoops_RHCAR (
	Net_Rendition const &		nr,
	_hoops_SASC const &		cuboid) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	
	DC_Point					_hoops_PAGR[8];
	float						ws[8];
	_hoops_GRCAR					_hoops_ARCAR[8];
	Point						in[8];
	int							_hoops_AHCAR;

	cuboid._hoops_GPSC(&in[0]);

	switch ((*HOOPS_WORLD->_hoops_PHCAR[_hoops_IHCR->_hoops_HGSC])
				(_hoops_IHCR, 8, in, &_hoops_IHCR->matrix->data.elements[0][0], &nr->_hoops_SAIR->_hoops_HHCAR, _hoops_PAGR, ws, _hoops_ARCAR)) {
		case 0: {
			int				_hoops_IHCAR;

			/* _hoops_PGII _hoops_CHR _hoops_SIPP. _hoops_GCRR _hoops_RCRR _hoops_SSIA'_hoops_ASAR _hoops_HCR _hoops_SIPP _hoops_GPP _hoops_RH _hoops_PSHR _hoops_PPAP */

			_hoops_IHCAR  = (int)_hoops_ARCAR[0];
			_hoops_IHCAR &= (int)_hoops_ARCAR[1];
			_hoops_IHCAR &= (int)_hoops_ARCAR[2];
			_hoops_IHCAR &= (int)_hoops_ARCAR[3];
			_hoops_IHCAR &= (int)_hoops_ARCAR[4];
			_hoops_IHCAR &= (int)_hoops_ARCAR[5];
			_hoops_IHCAR &= (int)_hoops_ARCAR[6];
			_hoops_IHCAR &= (int)_hoops_ARCAR[7];

			if (_hoops_IHCAR != 0)
				return 0; /* _hoops_CHCAR! */

			_hoops_AHCAR = 1; /* _hoops_SHCAR, "_hoops_GICAR" */
		}	break;

		case 8:	 _hoops_AHCAR = 8; /* (_hoops_HIS _hoops_SGIP) */		break;

		default: _hoops_AHCAR = 1; /* _hoops_SHCAR, "_hoops_GICAR" */ break;
	}

	/* _hoops_ICAGR _hoops_PAR _hoops_RRI _hoops_CSAP _hoops_GIAA. _hoops_RHCS _hoops_RH _hoops_HPPA _hoops_GHC, _hoops_RPP _hoops_GII. */
	if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
		int _hoops_RICAR = HD_Compute_Trimmed_Clip_Points (_hoops_IHCR, 8, _hoops_PAGR, ws, _hoops_ARCAR);
		if (_hoops_AHCAR > _hoops_RICAR) 
			_hoops_AHCAR = _hoops_RICAR;
	}

	return _hoops_AHCAR;
}


GLOBAL_FUNCTION int HD_Acquire_Clip_Points (
	Net_Rendition const &		nr,
	Bounding const &			_hoops_RCHS,
	int							count,
	Point const *				_hoops_AICAR,
	DC_Point alter *			_hoops_CGCAR,
	float alter *				ws,
	_hoops_GRCAR alter *			_hoops_RRCAR) {

	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	int _hoops_AHCAR = 1;		/* _hoops_SHCAR, _hoops_GICAR */

	if (count > _hoops_CPCAR && 
		!BIT (_hoops_IHCR->flags, _hoops_AIHS) &&
		 BIT (_hoops_IHCR->heuristics, _hoops_PICAR) &&
		!_hoops_RCHS._hoops_HICAR()) {

		_hoops_AHCAR = _hoops_RHCAR (nr, _hoops_RCHS->cuboid);

		if (_hoops_AHCAR == 0) 
			return 0; /* _hoops_IICAR */
	}

	int _hoops_CRCAR = (*HOOPS_WORLD->_hoops_PHCAR[_hoops_IHCR->_hoops_HGSC]) (
												 _hoops_IHCR,
												 count,
												 _hoops_AICAR,
												 &_hoops_IHCR->matrix->data.elements[0][0],
												 &nr->_hoops_SAIR->_hoops_HHCAR,
												 _hoops_CGCAR,
												 ws,
												 _hoops_RRCAR);

	/*
	 * _hoops_CGP _hoops_RH _hoops_RSSA _hoops_CHR _hoops_HCR _hoops_GIAA _hoops_RH _hoops_SHPR, _hoops_SR _hoops_ASRC _hoops_ICSI. _hoops_CGP _hoops_RH
	 * _hoops_RSSA _hoops_CHR _hoops_HCR _hoops_PSAP _hoops_RH _hoops_SHPR _hoops_SR _hoops_HCAGR _hoops_HSGR _hoops_GGSR _hoops_IIGR
	 * _hoops_CPS. _hoops_CGP _hoops_SSIA'_hoops_ASAR _hoops_HAR _hoops_HCR _hoops_PSAP _hoops_GGR _hoops_RH _hoops_PSHR _hoops_HAGA,
	 * _hoops_PHRI, _hoops_SR _hoops_RRP _hoops_IS _hoops_HHSA _hoops_RH _hoops_CICAR-_hoops_CIHH _hoops_SICAR _hoops_IS _hoops_SHH
	 * _hoops_PIGS. _hoops_HGI _hoops_HRGR _hoops_GCCAR _hoops_HPP _hoops_RCCAR _hoops_IRS 1, _hoops_SHCAR, _hoops_ACCAR _hoops_SGS
	 * _hoops_IIH _hoops_CSAP _hoops_IRS _hoops_PPSR _hoops_HAR _hoops_SACH.
	 */

	if (_hoops_CRCAR == 0) {
		_hoops_GRCAR const *	_hoops_ARCAR = _hoops_RRCAR;
		int					_hoops_IHCAR;
		int					remaining = count;

		_hoops_IHCAR = (int)*_hoops_RRCAR;
		++_hoops_ARCAR;
		--remaining;

		_hoops_PCCAR {
			if (remaining < 8) {
				switch (remaining) {
					case 7: _hoops_IHCAR &= (int)_hoops_ARCAR[6];		_hoops_HHHI;
					case 6: _hoops_IHCAR &= (int)_hoops_ARCAR[5];		_hoops_HHHI;
					case 5: _hoops_IHCAR &= (int)_hoops_ARCAR[4];		_hoops_HHHI;
					case 4: _hoops_IHCAR &= (int)_hoops_ARCAR[3];		_hoops_HHHI;
					case 3: _hoops_IHCAR &= (int)_hoops_ARCAR[2];		_hoops_HHHI;
					case 2: _hoops_IHCAR &= (int)_hoops_ARCAR[1];		_hoops_HHHI;
					case 1: _hoops_IHCAR &= (int)_hoops_ARCAR[0];		_hoops_HHHI;
					case 0:								break;
				}

				if (_hoops_IHCAR != 0) 
					return 0; /* _hoops_HCCAR! */

				break;	/* _hoops_ICCAR _hoops_PRAR */
			}

			_hoops_IHCAR &= (int)_hoops_ARCAR[0];
			_hoops_IHCAR &= (int)_hoops_ARCAR[1];
			_hoops_IHCAR &= (int)_hoops_ARCAR[2];
			_hoops_IHCAR &= (int)_hoops_ARCAR[3];
			if (_hoops_IHCAR == 0) 
				break;		/* _hoops_ICCAR _hoops_PRAR */
			_hoops_IHCAR &= (int)_hoops_ARCAR[4];
			_hoops_IHCAR &= (int)_hoops_ARCAR[5];
			_hoops_IHCAR &= (int)_hoops_ARCAR[6];
			_hoops_IHCAR &= (int)_hoops_ARCAR[7];
			if (_hoops_IHCAR == 0) 
				break;		/* _hoops_ICCAR _hoops_PRAR */

			remaining -= 8;
			_hoops_ARCAR += 8;
		}

		/* _hoops_CCCAR _hoops_IRS _hoops_SCCAR */

		_hoops_CRCAR = 1;		/* (_hoops_RSPH _hoops_RH _hoops_GSCAR _hoops_IIGR _hoops_SPR _hoops_GIAA) */
	}

	/* _hoops_ICAGR _hoops_PAR _hoops_RRI _hoops_CSAP _hoops_GIAA. _hoops_RHCS _hoops_RH _hoops_HPPA _hoops_GHC, _hoops_RPP _hoops_GII. */
	if (BIT (_hoops_IHCR->flags, _hoops_CSP) && _hoops_AHCAR != 8) {
		int _hoops_RICAR = HD_Compute_Trimmed_Clip_Points (_hoops_IHCR, count, _hoops_CGCAR, ws, _hoops_RRCAR);
		if (_hoops_CRCAR > _hoops_RICAR) 
			_hoops_CRCAR = _hoops_RICAR;
	}

	return _hoops_CRCAR;
}



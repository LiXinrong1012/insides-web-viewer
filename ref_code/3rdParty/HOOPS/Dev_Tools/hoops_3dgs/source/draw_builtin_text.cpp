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
 * $Id: obf_tmp.txt 1.147 2010-10-02 07:04:42 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


#ifndef DISABLE_DEFINED_FONTS

/* _hoops_AGCR _hoops_CGH _hoops_PSSP _hoops_RH _hoops_PAIGR _hoops_GGR _hoops_HRAIP */

#define _hoops_IRAIP		 0
#define _hoops_CRAIP		-1
#define _hoops_SRAIP	-2
#define _hoops_GAAIP		-3
#define _hoops_RAAIP	-4
#define _hoops_AAAIP		-5


#define _hoops_PAAIP		256

#define _hoops_HAAIP(p,_hoops_IAAIP,_hoops_CAAIP,_hoops_PRAA,_hoops_HRAA,x,y) do {		\
		int				_hoops_HAGR;							\
																		\
		_hoops_HAGR = _hoops_SAAIP (*p);	++p;							\
		x = (_hoops_HAGR - _hoops_IAAIP) * _hoops_PRAA;									\
		_hoops_HAGR = _hoops_SAAIP (*p);	++p;							\
		y = (_hoops_HAGR - _hoops_CAAIP) * _hoops_HRAA;									\
	} while (0)

#define _hoops_GPAIP(_hoops_RICGR,_hoops_AICGR,_hoops_IPGRP,_hoops_RPAIP,_hoops_APAIP) do {					\
		float			tx, ty;							\
																		\
		tx = _hoops_RICGR + _hoops_IPGRP * _hoops_AICGR; ty = _hoops_AICGR;								\
		_hoops_RPAIP = tx * _hoops_AGHCR - ty * _hoops_GGHCR;									\
		_hoops_APAIP = tx * _hoops_GGHCR   + ty * _hoops_AGHCR;								\
	} while (0)

#define _hoops_PPAIP(_hoops_RICGR,_hoops_AICGR,_hoops_HPAIP,_hoops_IPAIP,_hoops_IPGRP,_hoops_RPAIP,_hoops_APAIP) do {		\
		_hoops_GPAIP (_hoops_RICGR, _hoops_AICGR, _hoops_IPGRP, _hoops_RPAIP, _hoops_APAIP);					\
		_hoops_RPAIP += _hoops_HPAIP;	_hoops_APAIP += _hoops_IPAIP;									\
	} while (0)

#define _hoops_CPAIP(p,_hoops_HPAIP,_hoops_IPAIP,_hoops_SPAIP,_hoops_IAAIP,_hoops_CAAIP,_hoops_PRAA,_hoops_HRAA,_hoops_IPGRP,x,y,z) do {		\
		float			_hoops_GHAIP,							\
										_hoops_RHAIP;							\
		_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA,			\
						_hoops_GHAIP, _hoops_RHAIP);									\
		_hoops_PPAIP (_hoops_GHAIP, _hoops_RHAIP, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP, x, y);		\
		z = _hoops_SPAIP;														\
	} while (0)


GLOBAL_FUNCTION bool HI_Analyze_Arc (
	Point const			*start,
	Point const			*_hoops_GGSSR,
	Point const			*end,
	Point alter			*center,
	Point alter			*_hoops_GGHI,
	Point alter			*_hoops_RGHI,
	float alter				*_hoops_RAHCR) {
	float					dx1, _hoops_AHAIP, dx2, _hoops_PHAIP;
	float					_hoops_HHAIP;
	float					_hoops_IHAIP, _hoops_CHAIP;
	Vector				_hoops_ISPI, _hoops_CSPI, _hoops_SSPI;
	float					_hoops_GARCA, _hoops_RARCA, _hoops_SHAIP;
	float					_hoops_GIAIP, _hoops_RIAIP, _hoops_AIAIP;

	dx1 = start->x - _hoops_GGSSR->x;
	_hoops_AHAIP = start->y - _hoops_GGSSR->y;
	dx2 = end->x - _hoops_GGSSR->x;
	_hoops_PHAIP = end->y - _hoops_GGSSR->y;

	if ((_hoops_HHAIP = dx1*_hoops_PHAIP - dx2*_hoops_AHAIP) == 0)		/* _hoops_ARHAR */
		return false;

	_hoops_HHAIP = 0.5f / _hoops_HHAIP;			/* _hoops_SR _hoops_SGH _hoops_HHAA _hoops_RH _hoops_AGICR */
	_hoops_IHAIP = dx1*dx1 + _hoops_AHAIP*_hoops_AHAIP;
	_hoops_CHAIP = dx2*dx2 + _hoops_PHAIP*_hoops_PHAIP;

	/* _hoops_CPSA _hoops_PCCP _hoops_SHI _hoops_HII _hoops_IRGP */
	center->x = _hoops_HHAIP * (_hoops_IHAIP*_hoops_PHAIP - _hoops_CHAIP*_hoops_AHAIP);
	center->y = _hoops_HHAIP * (dx1*_hoops_CHAIP - dx2*_hoops_IHAIP);

	center->x += _hoops_GGSSR->x;
	center->y += _hoops_GGSSR->y;
	center->z = _hoops_GGSSR->z;

	_hoops_GGHI->x = start->x - center->x;
	_hoops_GGHI->y = start->y - center->y;
	_hoops_GGHI->z = 0.0f;

	_hoops_RGHI->x = -_hoops_GGHI->y;
	_hoops_RGHI->y =	 _hoops_GGHI->x;

	if (dx1 * _hoops_PHAIP - dx2 * _hoops_AHAIP > 0.0f) { /* _hoops_ISPR _hoops_RSSP */
		_hoops_RGHI->x = -_hoops_RGHI->x;
		_hoops_RGHI->y = -_hoops_RGHI->y;
	}

	_hoops_ISPI.x = start->x - center->x;
	_hoops_ISPI.y = start->y - center->y;
	_hoops_ISPI.z = 0.0f;
	(void)HI_Normalize (&_hoops_ISPI);

	_hoops_CSPI.x = _hoops_GGSSR->x - center->x;
	_hoops_CSPI.y = _hoops_GGSSR->y - center->y;
	_hoops_CSPI.z = 0.0f;
	(void)HI_Normalize (&_hoops_CSPI);

	_hoops_SSPI.x = end->x - center->x;
	_hoops_SSPI.y = end->y - center->y;
	_hoops_SSPI.z = 0.0f;
	(void)HI_Normalize (&_hoops_SSPI);

	_hoops_GARCA = _hoops_ISPI.x * _hoops_CSPI.x + _hoops_ISPI.y * _hoops_CSPI.y;
	_hoops_RARCA = _hoops_CSPI.x * _hoops_SSPI.x + _hoops_CSPI.y * _hoops_SSPI.y;
	_hoops_SHAIP = _hoops_ISPI.x * _hoops_SSPI.x + _hoops_ISPI.y * _hoops_SSPI.y;

	_hoops_GIAIP = _hoops_ISSSR(_hoops_GARCA);
	_hoops_RIAIP = _hoops_ISSSR(_hoops_RARCA);
	_hoops_AIAIP = _hoops_ISSSR(_hoops_SHAIP);

	if (Abs(_hoops_GIAIP + _hoops_RIAIP - _hoops_AIAIP) > 1.0f)	/* _hoops_PIAIP _hoops_IRS _hoops_CPSH _hoops_IIGR _hoops_RIHH */
		*_hoops_RAHCR = 360.0f - _hoops_AIAIP;
	else
		*_hoops_RAHCR = _hoops_AIAIP;

	return true;
}


local void _hoops_HIAIP (
	Net_Rendition const &	in_nr,
	Font_Instance const	*	specific,
	char const				*p,
	float					x,
	float					y,
	float					z,
	float					_hoops_PRAA,
	float					_hoops_HRAA,
	float					_hoops_IAAIP,
	float					_hoops_CAAIP,
	float					_hoops_IPGRP,
	float					_hoops_GGHCR,
	float					_hoops_AGHCR,
	bool					_hoops_IIAIP) {
	Net_Rendition			nr = in_nr;
	Point alter				*pl = null;
	Polyline alter			*polyline = null;
	Polygon alter			*polygon = null;
	float					_hoops_HPAIP = x,
							_hoops_IPAIP = y,
							_hoops_SPAIP = z;
	bool					_hoops_CIAIP = false;
	int						_hoops_SIAIP;

	UNREFERENCED (specific);

	_hoops_RGGA ((_hoops_SIAIP = _hoops_SAAIP (*p)) == _hoops_IRAIP) switch (_hoops_SIAIP) {
		case _hoops_CRAIP: {
			nr.Modify();

			Line_Rendition alter &		_hoops_HC = nr->_hoops_AHP;
			_hoops_CIGA alter &		_hoops_SIGA = _hoops_HC->_hoops_IHA;

			++p;
			if (_hoops_SIGA == null) {
				_hoops_SIGA = nr->_hoops_IHA;
				_hoops_SIGA.Modify();

				_hoops_SIGA->pattern = FP_SOLID;

				_hoops_SIGA->_hoops_CHA = _hoops_HC->_hoops_CHA;
				_hoops_SIGA->_hoops_GIA = _hoops_HC->_hoops_CHA;

				_hoops_SIGA->color = _hoops_HC->color;
				_hoops_SIGA->_hoops_RGIR = _hoops_HC->color;
			}

			nr->_hoops_IHA = _hoops_SIGA;
			nr->_hoops_RHP = _hoops_HC;

			_hoops_CIAIP = true;
			if (polygon != null) {
				pl = polygon->points;
			}
		}	break;
		case _hoops_GAAIP: {
			_hoops_CIAIP = false;
		}		_hoops_HHHI;		/* _hoops_RAIA _hoops_PSHR _hoops_RRGR _hoops_GAR "_hoops_GCAIP" _hoops_IS _hoops_CISA */
		case _hoops_SRAIP: {
			++p;
			if (polygon != null) {
				if ((polygon->count = pl - polygon->points) > 2)
					_hoops_RCAIP (nr, polygon);

				if (polygon->_hoops_HIHI == 1) {	/* _hoops_ASGGR _hoops_IS _hoops_RHGPA */
					pl = polygon->points;
				}
			}
		}	break;

		case _hoops_RAAIP: {
			Point				_hoops_GAPPA, _hoops_RAPPA;
			Point				center, radii;

			++p;
			if (_hoops_IIAIP &&
				(p[0] == p[2] || p[1] == p[3])) {
				HE_ERROR (HEC_ELLIPSE, HES_DEGENERATE_DEFINITION,
						"Ellipse definition is degenerate");
				p += 4;
				break;
			}

			_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA,
							_hoops_GAPPA.x, _hoops_GAPPA.y);
			_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA,
							_hoops_RAPPA.x, _hoops_RAPPA.y);

			center.x = (_hoops_GAPPA.x + _hoops_RAPPA.x) / 2;
			center.y = (_hoops_GAPPA.y + _hoops_RAPPA.y) / 2;
			center.z = _hoops_SPAIP;

			radii.x = Abs (_hoops_GAPPA.x - _hoops_RAPPA.x) / 2;
			radii.y = Abs (_hoops_GAPPA.y - _hoops_RAPPA.y) / 2;
			radii.z = 0.0f;

			if (!_hoops_CIAIP) {
				Elliptical_Arc alter		*_hoops_ACAIP;

				ZALLOC (_hoops_ACAIP, Elliptical_Arc);
				_hoops_ACAIP->type = _hoops_GIIP;
				_hoops_ACAIP->_hoops_CPGPR = _hoops_PHSSR;
				_hoops_ACAIP->_hoops_HIHI = 1;

				_hoops_PPAIP (center.x, center.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP,
								  _hoops_ACAIP->center.x, _hoops_ACAIP->center.y);
				_hoops_ACAIP->center.z = center.z;

				/* _hoops_CSGA _hoops_PGCR _hoops_HARGR _hoops_PSPAR */
				_hoops_GPAIP (radii.x, 0.0f, _hoops_IPGRP,
								  _hoops_ACAIP->_hoops_GGHI.x, _hoops_ACAIP->_hoops_GGHI.y);
				_hoops_ACAIP->_hoops_GGHI.z = 0.0f;

				_hoops_GPAIP (0, radii.y, _hoops_IPGRP,
								  _hoops_ACAIP->_hoops_RGHI.x, _hoops_ACAIP->_hoops_RGHI.y);
				_hoops_ACAIP->_hoops_RGHI.z = 0.0f;

				_hoops_ACAIP->major.x = _hoops_ACAIP->center.x + _hoops_ACAIP->_hoops_GGHI.x;
				_hoops_ACAIP->major.y = _hoops_ACAIP->center.y + _hoops_ACAIP->_hoops_GGHI.y;
				_hoops_ACAIP->major.z = _hoops_ACAIP->center.z + _hoops_ACAIP->_hoops_GGHI.z;

				_hoops_ACAIP->minor.x = _hoops_ACAIP->center.x + _hoops_ACAIP->_hoops_RGHI.x;
				_hoops_ACAIP->minor.y = _hoops_ACAIP->center.y + _hoops_ACAIP->_hoops_RGHI.y;
				_hoops_ACAIP->minor.z = _hoops_ACAIP->center.z + _hoops_ACAIP->_hoops_RGHI.z;

				_hoops_ACAIP->plane.a = 0.0f;
				_hoops_ACAIP->plane.b = 0.0f;
				_hoops_ACAIP->plane.c = 1.0f;
				_hoops_ACAIP->plane.d = -center.z;

				_hoops_ACAIP->arc_start = 0.0f;
				_hoops_ACAIP->_hoops_PHHI = 1.0f;

				_hoops_PPAGR (nr, _hoops_ACAIP);

				_hoops_HPRH (_hoops_ACAIP);
			}
			else {
				Ellipse alter		*_hoops_IHHIR;

				ZALLOC (_hoops_IHHIR, Ellipse);
				_hoops_IHHIR->type = _hoops_CGCP;
				_hoops_IHHIR->_hoops_CPGPR = _hoops_PHSSR;
				_hoops_IHHIR->_hoops_HIHI = 1;

				_hoops_PPAIP (center.x, center.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP,
								  _hoops_IHHIR->center.x, _hoops_IHHIR->center.y);
				_hoops_IHHIR->center.z = center.z;

				/* _hoops_CSGA _hoops_PGCR _hoops_HARGR _hoops_PSPAR */
				_hoops_GPAIP (radii.x, 0.0f, _hoops_IPGRP,
								  _hoops_IHHIR->_hoops_GGHI.x, _hoops_IHHIR->_hoops_GGHI.y);
				_hoops_IHHIR->_hoops_GGHI.z = 0.0f;

				_hoops_GPAIP (0.0f, radii.y, _hoops_IPGRP,
								  _hoops_IHHIR->_hoops_RGHI.x, _hoops_IHHIR->_hoops_RGHI.y);
				_hoops_IHHIR->_hoops_RGHI.z = 0.0f;

				_hoops_IHHIR->major.x = _hoops_IHHIR->center.x + _hoops_IHHIR->_hoops_GGHI.x;
				_hoops_IHHIR->major.y = _hoops_IHHIR->center.y + _hoops_IHHIR->_hoops_GGHI.y;
				_hoops_IHHIR->major.z = _hoops_IHHIR->center.z + _hoops_IHHIR->_hoops_GGHI.z;

				_hoops_IHHIR->minor.x = _hoops_IHHIR->center.x + _hoops_IHHIR->_hoops_RGHI.x;
				_hoops_IHHIR->minor.y = _hoops_IHHIR->center.y + _hoops_IHHIR->_hoops_RGHI.y;
				_hoops_IHHIR->minor.z = _hoops_IHHIR->center.z + _hoops_IHHIR->_hoops_RGHI.z;

				_hoops_IHHIR->plane.a = 0.0f;
				_hoops_IHHIR->plane.b = 0.0f;
				_hoops_IHHIR->plane.c = 1.0f;
				_hoops_IHHIR->plane.d = -center.z;

				_hoops_PCAIP (nr, _hoops_IHHIR);

				_hoops_HPRH (_hoops_IHHIR);
			}
		}	break;

		case _hoops_AAAIP: {
			Point		_hoops_GAPPA, _hoops_RAPPA, _hoops_CAPPA;
			Point		center, _hoops_GGHI, _hoops_RGHI;
			float			_hoops_RAHCR, _hoops_HCAIP, _hoops_ICAIP;
			int				ii;

			++p;
			_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA,
							_hoops_GAPPA.x, _hoops_GAPPA.y);
			_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA,
							_hoops_RAPPA.x, _hoops_RAPPA.y);
			_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA,
							_hoops_CAPPA.x, _hoops_CAPPA.y);
			_hoops_GAPPA.z = _hoops_RAPPA.z = _hoops_CAPPA.z = _hoops_SPAIP;

			if (!_hoops_CIAIP) {
				if (polyline != null && polyline->_hoops_HIHI == 1) {}
				else {
					if (polyline != null) _hoops_HPRH (polyline);

					ZALLOC (polyline, Polyline);
					polyline->_hoops_HIHI = 1;
					polyline->type = _hoops_IIIP;
					polyline->_hoops_CPGPR = _hoops_PHSSR;

					ALLOC_ARRAY (pl, _hoops_PAAIP, Point);
					polyline->points = pl;
					polyline->allocated = _hoops_PAAIP;
				}
				pl = polyline->points;
			}
			else {
				if (polygon != null && polygon->_hoops_HIHI == 1) {}
				else {
					if (polygon != null) _hoops_HPRH (polygon);

					ZALLOC (polygon, Polygon);
					polygon->_hoops_HIHI = 1;
					polygon->type = _hoops_RCIP;
					polygon->_hoops_CPGPR = _hoops_PHSSR;

					ALLOC_ARRAY (pl, _hoops_PAAIP, Point);
					polygon->points = pl;
					polygon->allocated = _hoops_PAAIP;
				}
				pl = polygon->points;
			}

			if (HI_Analyze_Arc (&_hoops_GAPPA, &_hoops_RAPPA, &_hoops_CAPPA,
							   &center, &_hoops_GGHI, &_hoops_RGHI, &_hoops_RAHCR)) {
				/* _hoops_HIHP _hoops_PHPHA _hoops_SIHC */
				_hoops_PPAIP (center.x, center.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP,
								  center.x, center.y);
				_hoops_GPAIP (_hoops_GGHI.x, _hoops_GGHI.y, _hoops_IPGRP,
								  _hoops_GGHI.x, _hoops_GGHI.y);
				_hoops_GPAIP (_hoops_RGHI.x, _hoops_RGHI.y, _hoops_IPGRP,
								  _hoops_RGHI.x, _hoops_RGHI.y);

				for (ii=0; ii<_hoops_RAHCR; ii+=5) {
					_hoops_RICH ((float)ii, _hoops_HCAIP, _hoops_ICAIP);
					pl->x = center.x + _hoops_ICAIP * _hoops_GGHI.x + _hoops_HCAIP * _hoops_RGHI.x;
					pl->y = center.y + _hoops_ICAIP * _hoops_GGHI.y + _hoops_HCAIP * _hoops_RGHI.y;
					pl->z = center.z;
					++pl;
				}
				_hoops_RICH (_hoops_RAHCR, _hoops_HCAIP, _hoops_ICAIP);
				pl->x = center.x + _hoops_ICAIP * _hoops_GGHI.x + _hoops_HCAIP * _hoops_RGHI.x;
				pl->y = center.y + _hoops_ICAIP * _hoops_GGHI.y + _hoops_HCAIP * _hoops_RGHI.y;
				pl->z = center.z;
				++pl;
			}
			else {		/* _hoops_GGR _hoops_IRS _hoops_III -- _hoops_SAHR _hoops_SGH _hoops_CAPR */
				_hoops_PPAIP (_hoops_GAPPA.x, _hoops_GAPPA.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP,
								  pl->x, pl->y);
				pl->z = _hoops_SPAIP;	++pl;

				_hoops_PPAIP (_hoops_RAPPA.x, _hoops_RAPPA.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP,
								  pl->x, pl->y);
				pl->z = _hoops_SPAIP;	++pl;

				_hoops_PPAIP (_hoops_CAPPA.x, _hoops_CAPPA.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP,
								  pl->x, pl->y);
				pl->z = _hoops_SPAIP;	++pl;
			}

			if (!_hoops_CIAIP && (polyline->count = pl - polyline->points) > 0)
				_hoops_CCAIP (nr, polyline);
		}	break;

		default: {
			++p;
			if (_hoops_SIAIP > _hoops_IRAIP) {
				if (!_hoops_CIAIP) {
					if (polyline != null && polyline->_hoops_HIHI == 1) {}
					else {
						if (polyline != null) _hoops_HPRH (polyline);

						ZALLOC (polyline, Polyline);
						polyline->_hoops_HIHI = 1;
						polyline->type = _hoops_IIIP;
						polyline->_hoops_CPGPR = _hoops_PHSSR;

						ALLOC_ARRAY_CACHED (pl, _hoops_PAAIP, Point);
						polyline->points = pl;
						polyline->allocated = _hoops_PAAIP;
					}
					pl = polyline->points;

					do {
						_hoops_CPAIP (p,
										_hoops_HPAIP, _hoops_IPAIP, _hoops_SPAIP,
										_hoops_IAAIP, _hoops_CAAIP,
										_hoops_PRAA, _hoops_HRAA, _hoops_IPGRP,
										pl->x, pl->y, pl->z);
						++pl;
					} _hoops_RGGA (--_hoops_SIAIP == 0);

					polyline->count = pl - polyline->points;
					_hoops_CCAIP (nr, polyline);
				}
				else {
					if (polygon != null && polygon->_hoops_HIHI == 1) {}
					else {
						if (polygon != null) _hoops_HPRH (polygon);

						ZALLOC (polygon, Polygon);
						polygon->_hoops_HIHI = 1;
						polygon->type = _hoops_RCIP;
						polygon->_hoops_CPGPR = _hoops_PHSSR;

						ALLOC_ARRAY (pl, _hoops_PAAIP, Point);
						polygon->points = pl;
						polygon->allocated = _hoops_PAAIP;
						pl = polygon->points;
					}

					do {
						_hoops_CPAIP (p,
										_hoops_HPAIP, _hoops_IPAIP, _hoops_SPAIP,
										_hoops_IAAIP, _hoops_CAAIP,
										_hoops_PRAA, _hoops_HRAA, _hoops_IPGRP,
										pl->x, pl->y, pl->z);
						++pl;
					} _hoops_RGGA (--_hoops_SIAIP == 0);
				}
			}
			else {
				HE_WARNING (HEC_TEXT, HES_INVALID_DEF_FONT_DRAW_CODE,
						"invalid defined_font draw code");
				continue;
			}
		}	break;
	}

	/* _hoops_GII _hoops_GGAS? */
	if (_hoops_CIAIP && polygon != null && (polygon->count = pl - polygon->points) > 2)
		_hoops_RCAIP (nr, polygon);

	if (polyline != null) _hoops_HPRH (polyline);
	if (polygon != null) _hoops_HPRH (polygon);
}

#endif

GLOBAL_FUNCTION void HD_Draw_Defined_Font (
	Net_Rendition const &	in_nr,
	Font_Instance const *	specific,
	Point const *			where,
	int						count,
	Karacter const *		string,
	Vector const *			scale) {
#ifndef DISABLE_DEFINED_FONTS
	Net_Rendition			nr = in_nr;
	_hoops_IGCSR const &	_hoops_HRCIR = nr->_hoops_SISI;
	Display_Context alter *	dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_PSIHP		_hoops_HSIHP = nr->_hoops_RSGC;
	float					x = where->x,
							y = where->y;
	_hoops_PGIIR const				*font;
	float					_hoops_PRAA,
							_hoops_HRAA;
	float					_hoops_SCAIP;
	float					_hoops_PRPHA;
	float					_hoops_IPGRP;
	float					_hoops_GGHCR,
							_hoops_AGHCR;
	int						height,
							width,
							spacing;
	int						_hoops_IAAIP = 0,
							_hoops_CAAIP = 0;
	bool					_hoops_IIAIP = false;
	DC_Point				_hoops_GSAIP[2];

	if (dc->_hoops_APHHP == null &&
		BIT(in_nr->_hoops_IRR->_hoops_CHP, _hoops_CRAAP) &&
		!BIT(in_nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
		_hoops_APARR			_hoops_RRCI;

		nr.Modify()->_hoops_IRR.Modify()->_hoops_CHP |= _hoops_SHP;

		/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_RSAIP */
		_hoops_RRCI = _hoops_HGCGA (dc, "transparent stroked text deferral", nr);

		_hoops_RRCI->draw_3d_polyline	= HD_Defer_Antialiased_3D_Polyline;
		_hoops_RRCI->draw_dc_polyline	= HD_Hide_DC_Polyline;
	}

	if (nr->_hoops_AHP != _hoops_HRCIR->_hoops_RGIHP) {
		if (_hoops_HRCIR->_hoops_RGIHP == null) {
			((_hoops_IGCSR alter &)_hoops_HRCIR)->_hoops_RGIHP = nr->_hoops_AHP;
			Line_Rendition alter &	_hoops_ASAIP = ((_hoops_IGCSR alter &)_hoops_HRCIR)->_hoops_RGIHP.Modify();

			_hoops_ASAIP->_hoops_CHA = _hoops_HRCIR->_hoops_CHA;

			_hoops_ASAIP->color = _hoops_HRCIR->color;

			HD_Replace_Line_Style(_hoops_ASAIP, nr->_hoops_GCSHP->_hoops_IHRIP);

			_hoops_ASAIP->style = LJOIN_ROUND|LCAP_ROUND;
			_hoops_ASAIP->weight = dc->_hoops_PGCC._hoops_IHHSR;
			_hoops_ASAIP->_hoops_IHA = null;
		}
		nr.Modify()->_hoops_AHP = _hoops_HRCIR->_hoops_RGIHP;
	}

	/* _hoops_SGH _hoops_IPSP-_hoops_PAPR _hoops_HCGR _hoops_RGISR/_hoops_CCAC _hoops_SICAR, _hoops_PSAIP _hoops_HHGPR _hoops_APGR
	 * _hoops_PPR _hoops_RSSI _hoops_RPP _hoops_ACHPP */
	if ((_hoops_HRCIR->transform == FT_FULL)) {
		if (_hoops_HSIHP->action.draw_dc_polyline != _hoops_HSIHP->action._hoops_SPCHP ||
			_hoops_HSIHP->action.draw_dc_face != _hoops_HSIHP->action._hoops_RHCHP ||
			_hoops_HSIHP->action.draw_3d_polyline != _hoops_HSIHP->action._hoops_GCCHP ||
			_hoops_HSIHP->action.draw_3d_polygon != _hoops_HSIHP->action._hoops_ACCHP) {

			_hoops_HSIHP = nr.Modify()->_hoops_RSGC.Modify();
			_hoops_HSIHP->action.draw_dc_polyline = _hoops_HSIHP->action._hoops_SPCHP;
			_hoops_HSIHP->action.draw_dc_face = _hoops_HSIHP->action._hoops_RHCHP;
			_hoops_HSIHP->action.draw_3d_polyline = _hoops_HSIHP->action._hoops_GCCHP;
			_hoops_HSIHP->action.draw_3d_polygon = _hoops_HSIHP->action._hoops_ACCHP;
		}
	}
	else {
		if (_hoops_HSIHP->action.draw_dc_polyline != _hoops_HSIHP->action._hoops_SPCHP ||
			_hoops_HSIHP->action.draw_dc_face != _hoops_HSIHP->action._hoops_RHCHP) {

			_hoops_HSIHP = nr.Modify()->_hoops_RSGC.Modify();
			_hoops_HSIHP->action.draw_dc_polyline = _hoops_HSIHP->action._hoops_SPCHP;
			_hoops_HSIHP->action.draw_dc_face = _hoops_HSIHP->action._hoops_RHCHP;
		}
	}

	font = specific->family->font;

	height	= _hoops_IRGCR (font->data[1]);
	width	= _hoops_IRGCR (font->data[2]);
	spacing = _hoops_IRGCR (font->data[3]);

	_hoops_PRPHA = specific->_hoops_ISISR / (float)height;
	_hoops_PRPHA *= font->_hoops_CSIH;

	_hoops_HRAA = specific->_hoops_ISISR;
	_hoops_HRAA *= scale->y / (float)height;

	_hoops_PRAA = (width + spacing) * _hoops_PRPHA * _hoops_HRCIR->width_scale;
	_hoops_PRAA *= scale->x / (float)(width + spacing);

	/* _hoops_CSGA _hoops_HSAIP _hoops_SRS */
	_hoops_RICH (_hoops_HRCIR->_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR);
	_hoops_IPGRP = _hoops_GGHCR / _hoops_AGHCR;

	/* _hoops_HA _hoops_HGCR _hoops_IHSPA & _hoops_HHSPA _hoops_IIGR _hoops_ICSA */
	_hoops_RICH (_hoops_HRCIR->rotation, _hoops_GGHCR, _hoops_AGHCR);

#if 0
	/* _hoops_IRHH _hoops_SCH _hoops_GIRR _hoops_PSAP _hoops_AGAPR */
	x += 0.5f * scale->x * _hoops_AGHCR - 0.5f * scale->y * _hoops_GGHCR;
	y += 0.5f * scale->x * _hoops_GGHCR + 0.5f * scale->y * _hoops_AGHCR;
#endif

	_hoops_SCAIP = scale->x * 0.5f * spacing * _hoops_PRPHA * _hoops_HRCIR->width_scale;
	x += _hoops_SCAIP * _hoops_AGHCR;
	y += _hoops_SCAIP * _hoops_GGHCR;

	_hoops_GSAIP[0].x = x;
	_hoops_GSAIP[0].y = y;
	_hoops_GSAIP[0].z = where->z;

	while (count--) {
		char const *p;
		int _hoops_ISAIP;
		Karacter _hoops_CSAIP;

		if (font->encoding == _hoops_SSAIP) 
			_hoops_CSAIP = *string&0x00FF;
		else
			_hoops_CSAIP = *string;

		string++;

		_hoops_ISAIP = _hoops_GGPIP(_hoops_CSAIP);

		if (specific->_hoops_RGPIP[_hoops_ISAIP].valid &&
			specific->_hoops_RGPIP[_hoops_ISAIP]._hoops_CSAIP == _hoops_CSAIP &&
			specific->_hoops_RGPIP[_hoops_ISAIP].data) {
			p = (const char*)specific->_hoops_RGPIP[_hoops_ISAIP].data;
		}
		else {
			if (font->_hoops_HGIIR != null) {
				(*((_hoops_CAHAP)font->_hoops_HGIIR->address)) (font->name.text, font->data, _hoops_CSAIP, &p);
				_hoops_IIAIP = true;
			}
			else if (font->encoding == _hoops_SSAIP) {
				p = font->_hoops_CGIIR[_hoops_CSAIP];
			} 
			else {				/* _hoops_PSHPR _hoops_GIPHR */
				char const * const *low;
				char const * const *high;
				char const * const *_hoops_SPGIR;
				int index = _hoops_CSAIP;

				p = null;				/* _hoops_GGR _hoops_AGIR _hoops_PIRC _hoops_GSGI */
				low = &font->_hoops_CGIIR[0];
				high = low + font->_hoops_IGIIR - 1;

				if (index <= _hoops_SPHAP(*high) &&
						index>= _hoops_SPHAP(*low)) {
					_hoops_SPGIR = low + (high - low)/2;

					while (high >= low) {
						int _hoops_AGPIP = _hoops_SPHAP (*_hoops_SPGIR);

						if (_hoops_AGPIP == index) {
							p = *_hoops_SPGIR;
							break;
						}
						else if (_hoops_AGPIP > index)
							high = _hoops_SPGIR - 1;
						else
							low = _hoops_SPGIR + 1;
						_hoops_SPGIR = low + (high - low)/2;
					}
				}
			}
		}

		if (p == null) {

			/* _hoops_AICP _hoops_PGPIP _hoops_ACPH*/
			if (font->encoding == _hoops_SSAIP) 
				width = _hoops_IRGCR (font->data[2]);
			else
				width = _hoops_IRGCR (font->data[3]);
			/* _hoops_HGPIP _hoops_IGPIP _hoops_CGPIP */
			/* _hoops_SIGP _hoops_SGPIP _hoops_GRPIP */
			p = "";						

		}
		else {
			/* _hoops_HGCR _hoops_ISGR 1 _hoops_PAR 2 _hoops_RAPSR _hoops_PIRA */
			++p;
			if (font->encoding != _hoops_SSAIP) ++p;

			width	 = p[0];							/* _hoops_HPHR */
			_hoops_IAAIP = p[1];
			_hoops_CAAIP = p[2];
			p+= 5;										/* _hoops_HSGR _hoops_RRPIP */
		}

		_hoops_SCAIP = scale->x * (width + spacing) * _hoops_PRPHA * _hoops_HRCIR->width_scale;

		if (_hoops_HRCIR->transform == FT_FULL) {			/* _hoops_CHIAR */
			/* _hoops_AASA _hoops_GGSR, _hoops_IS _hoops_HGCR _hoops_CIGGR _hoops_CPCPR _hoops_AHI */
			_hoops_HIAIP (nr, specific, p, x, y, where->z,
								   _hoops_PRAA, _hoops_HRAA, (float)_hoops_IAAIP, (float)_hoops_CAAIP,
								   _hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR, _hoops_IIAIP);
		}
		else if (specific->_hoops_ISISR >= 2.0f) {
			DC_Point			_hoops_ARPIP[_hoops_PAAIP];
			DC_Point alter	*pt = _hoops_ARPIP;
			int					_hoops_HPAIP = (int)x,
											_hoops_IPAIP = (int)y;
			float				_hoops_SPAIP = (float)where->z;
			bool			_hoops_CIAIP = false;
			int					_hoops_SIAIP;

			_hoops_RGGA ((_hoops_SIAIP = _hoops_SAAIP (*p)) == 0) switch (_hoops_SIAIP) {
				case _hoops_CRAIP: {
					nr.Modify();

					Line_Rendition alter &		_hoops_HC = nr->_hoops_AHP;
					_hoops_CIGA alter &		_hoops_SIGA = _hoops_HC->_hoops_IHA;

					++p;
					if (_hoops_SIGA == null) {
						_hoops_SIGA = nr->_hoops_IHA;
						_hoops_SIGA.Modify();

						_hoops_SIGA->pattern = FP_SOLID;

						_hoops_SIGA->_hoops_CHA = _hoops_HC->_hoops_CHA;
						_hoops_SIGA->_hoops_GIA = _hoops_HC->_hoops_CHA;

						_hoops_SIGA->color = _hoops_HC->color;
						_hoops_SIGA->_hoops_RGIR = _hoops_HC->color;
					}

					nr->_hoops_IHA = _hoops_SIGA;

					nr->_hoops_RHP = _hoops_HC;

					_hoops_CIAIP = true;
				}	break;
				case _hoops_GAAIP: {
					_hoops_CIAIP = false;
				}		_hoops_HHHI;		/* _hoops_RAIA _hoops_PSHR _hoops_RRGR _hoops_GAR "_hoops_GCAIP" _hoops_IS _hoops_CISA */
				case _hoops_SRAIP: {
					int		_hoops_PRPIP = pt - _hoops_ARPIP;

					++p;
					if (_hoops_PRPIP > 2)
						_hoops_HRPIP (nr, _hoops_PRPIP, _hoops_ARPIP);
					pt = _hoops_ARPIP;
				}	break;

				case _hoops_RAAIP: {
					Point				_hoops_GAPPA, _hoops_RAPPA;
					Point				center, radii;

					++p;
					if (_hoops_IIAIP &&
						(p[0] == p[2] || p[1] == p[3])) {
						HE_ERROR (HEC_ELLIPSE, HES_DEGENERATE_DEFINITION,
								"Ellipse definition is degenerate");
						p += 4;
						break;
					}

					_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA,
									_hoops_GAPPA.x, _hoops_GAPPA.y);
					_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA,
									_hoops_RAPPA.x, _hoops_RAPPA.y);

					center.x = (_hoops_GAPPA.x + _hoops_RAPPA.x) / 2;
					center.y = (_hoops_GAPPA.y + _hoops_RAPPA.y) / 2;
					center.z = (float)_hoops_SPAIP;

					radii.x = Abs (_hoops_GAPPA.x - _hoops_RAPPA.x) / 2 + 0.5f;
					radii.y = Abs (_hoops_GAPPA.y - _hoops_RAPPA.y) / 2 + 0.5f;
					radii.z = 0.0f;

					if (_hoops_IPGRP != 0.0f || _hoops_HRCIR->rotation != 0.0f ||
						_hoops_CIAIP && _hoops_HSIHP->action._hoops_RHCHP != nullroutine ||
						!_hoops_CIAIP && _hoops_HSIHP->action._hoops_SPCHP != nullroutine) {
						DC_Point			_hoops_IRPIP[100];
						DC_Point alter *	_hoops_CRPIP = _hoops_IRPIP;
						float				_hoops_HCAIP, _hoops_ICAIP;
						Vector				_hoops_IHHI, _hoops_CHHI;

						_hoops_PPAIP (center.x, center.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP, center.x, center.y);
						_hoops_GPAIP (radii.x, 0.0f, _hoops_IPGRP, _hoops_IHHI.x, _hoops_IHHI.y);
						_hoops_GPAIP (0.0f, radii.y, _hoops_IPGRP, _hoops_CHHI.x, _hoops_CHHI.y);

						for (int ii=0; ii<=72; ++ii) {
							_hoops_RICH ((float)(ii*5), _hoops_HCAIP, _hoops_ICAIP);
							_hoops_CRPIP->x = center.x + _hoops_ICAIP * _hoops_IHHI.x + _hoops_HCAIP * _hoops_CHHI.x;
							_hoops_CRPIP->y = center.y + _hoops_ICAIP * _hoops_IHHI.y + _hoops_HCAIP * _hoops_CHHI.y;
							_hoops_CRPIP->z = center.z;
							++_hoops_CRPIP;
						}

						if (_hoops_CIAIP)
							_hoops_HRPIP (nr, 72, _hoops_IRPIP);
						else
							_hoops_SRPIP (nr, 73, _hoops_IRPIP);
					}
					else {
						DC_Point		_hoops_GAPIP, _hoops_RAPIP;

						_hoops_GAPIP.x = _hoops_HPAIP + center.x;
						_hoops_GAPIP.y = _hoops_IPAIP + center.y;
						_hoops_GAPIP.z = center.z;

						_hoops_RAPIP.x = radii.x;
						_hoops_RAPIP.y = radii.y;
						_hoops_RAPIP.z = radii.z;

						if (_hoops_CIAIP)
							_hoops_AAPIP (nr, &_hoops_GAPIP, &_hoops_RAPIP);
						else
							_hoops_PAPIP (nr, &_hoops_GAPIP, &_hoops_RAPIP);
					}
				}	break;

				case _hoops_AAAIP: {
					Point		_hoops_GAPPA, _hoops_RAPPA, _hoops_CAPPA;
					Point		center, _hoops_GGHI, _hoops_RGHI;
					float			_hoops_RAHCR, _hoops_HCAIP, _hoops_ICAIP;
					int				ii;

					++p;
					_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA,
									_hoops_GAPPA.x, _hoops_GAPPA.y);
					_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA,
									_hoops_RAPPA.x, _hoops_RAPPA.y);
					_hoops_HAAIP (p, _hoops_IAAIP, _hoops_CAAIP, _hoops_PRAA, _hoops_HRAA,
									_hoops_CAPPA.x, _hoops_CAPPA.y);
					_hoops_GAPPA.z = _hoops_RAPPA.z = _hoops_CAPPA.z = (float)_hoops_SPAIP;

					if (HI_Analyze_Arc (&_hoops_GAPPA, &_hoops_RAPPA, &_hoops_CAPPA,
									   &center, &_hoops_GGHI, &_hoops_RGHI, &_hoops_RAHCR)) {
						/* _hoops_HIHP _hoops_PHPHA _hoops_SIHC */
						_hoops_PPAIP (center.x, center.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP,
										  center.x, center.y);
						_hoops_GPAIP (_hoops_GGHI.x, _hoops_GGHI.y, _hoops_IPGRP,
										  _hoops_GGHI.x, _hoops_GGHI.y);
						_hoops_GPAIP (_hoops_RGHI.x, _hoops_RGHI.y, _hoops_IPGRP,
										  _hoops_RGHI.x, _hoops_RGHI.y);

						for (ii=0; ii<_hoops_RAHCR; ii+=5) {
							_hoops_RICH ((float)ii, _hoops_HCAIP, _hoops_ICAIP);
							pt->x = center.x + _hoops_ICAIP * _hoops_GGHI.x + _hoops_HCAIP * _hoops_RGHI.x;
							pt->y = center.y + _hoops_ICAIP * _hoops_GGHI.y + _hoops_HCAIP * _hoops_RGHI.y;
							pt->z = center.z;
							++pt;
						}
						_hoops_RICH (_hoops_RAHCR, _hoops_HCAIP, _hoops_ICAIP);
						pt->x = center.x + _hoops_ICAIP * _hoops_GGHI.x + _hoops_HCAIP * _hoops_RGHI.x;
						pt->y = center.y + _hoops_ICAIP * _hoops_GGHI.y + _hoops_HCAIP * _hoops_RGHI.y;
						pt->z = center.z;
						++pt;
					}
					else {		/* _hoops_GGR _hoops_IRS _hoops_III -- _hoops_SAHR _hoops_SGH _hoops_CAPR */
						_hoops_PPAIP (_hoops_GAPPA.x, _hoops_GAPPA.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP,
										  pt->x, pt->y);
						pt->z = (float)_hoops_SPAIP;	++pt;

						_hoops_PPAIP (_hoops_RAPPA.x, _hoops_RAPPA.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP,
										  pt->x, pt->y);
						pt->z = (float)_hoops_SPAIP;	++pt;

						_hoops_PPAIP (_hoops_CAPPA.x, _hoops_CAPPA.y, _hoops_HPAIP, _hoops_IPAIP, _hoops_IPGRP,
										  pt->x, pt->y);
						pt->z = (float)_hoops_SPAIP;	++pt;
					}

					if (!_hoops_CIAIP) {
						int		_hoops_PRPIP = pt - _hoops_ARPIP;

						_hoops_SRPIP (nr, _hoops_PRPIP, _hoops_ARPIP);
						pt = _hoops_ARPIP;
					}
				}	break;

				default: {
					++p;
					if (_hoops_SIAIP > _hoops_IRAIP) {
						if (_hoops_SIAIP == 1) {		/* _hoops_SAHR _hoops_AA _hoops_IRS _hoops_PSCHR _hoops_HA */
							_hoops_CPAIP (p,
											_hoops_HPAIP, _hoops_IPAIP, (float)_hoops_SPAIP,
											_hoops_IAAIP, _hoops_CAAIP,
											_hoops_PRAA, _hoops_HRAA, _hoops_IPGRP,
											pt->x, pt->y, pt->z);
							_hoops_HAPIP (nr, pt);
						}
						else {
							do {
								_hoops_CPAIP (p,
												_hoops_HPAIP, _hoops_IPAIP, (float)_hoops_SPAIP,
												_hoops_IAAIP, _hoops_CAAIP,
												_hoops_PRAA, _hoops_HRAA, _hoops_IPGRP,
												pt->x, pt->y, pt->z);
								++pt;
							} _hoops_RGGA (--_hoops_SIAIP == 0);
							if (!_hoops_CIAIP) {
								int		_hoops_PRPIP = pt - _hoops_ARPIP;

								_hoops_SRPIP (nr, _hoops_PRPIP, _hoops_ARPIP);
								pt = _hoops_ARPIP;
							}
						}
					}
					else {
						HE_WARNING (HEC_TEXT, HES_INVALID_DEF_FONT_DRAW_CODE,
								"invalid defined_font draw code");
						continue;
					}
				}	break;
			}

			/* _hoops_GII _hoops_GGAS? (_hoops_RGAR _hoops_SSRR _hoops_RPP _hoops_SHRAA) */
			if (pt != _hoops_ARPIP) {
				int		_hoops_PRPIP = pt - _hoops_ARPIP;

				_hoops_HRPIP (nr, _hoops_PRPIP, _hoops_ARPIP);
			}
		}

		x += _hoops_SCAIP * _hoops_AGHCR;
		y += _hoops_SCAIP * _hoops_GGHCR;
	}

	if (specific->_hoops_ISISR < 2.0f && _hoops_HRCIR->transform != FT_FULL &&
		_hoops_HRCIR->_hoops_SGHAP != _hoops_HGHAP) {
		/* _hoops_HAH _hoops_RISA, _hoops_HIS "_hoops_IAPIP" _hoops_SCH */
		/* _hoops_PAISR _hoops_CGHI _hoops_GCHGA */
		x -= _hoops_SCAIP * _hoops_AGHCR;
		y -= _hoops_SCAIP * _hoops_GGHCR;

		if (Abs (x - _hoops_GSAIP[0].x) >= 1.0f ||
			Abs (y - _hoops_GSAIP[0].y) >= 1.0f) {
			_hoops_GSAIP[1].x = x;
			_hoops_GSAIP[1].y = y;
			_hoops_GSAIP[1].z = where->z;
			_hoops_SCGGA (nr, 2, _hoops_GSAIP);
		}
		else
			_hoops_HAPIP (nr, &_hoops_GSAIP[0]);
	}

	if (dc->_hoops_APHHP == null &&
		BIT(in_nr->_hoops_IRR->_hoops_CHP, _hoops_CRAAP) &&
		!BIT(in_nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
		_hoops_HGSGA (dc, "transparent stroked text deferral");
	}
#endif
}



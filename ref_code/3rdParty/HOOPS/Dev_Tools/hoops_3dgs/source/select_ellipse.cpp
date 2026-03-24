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
 * $Id: obf_tmp.txt 1.91 2010-05-17 22:45:19 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "select.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#define _hoops_HCSAH		512

GLOBAL_FUNCTION void HD_Select_Ellipse (
	Net_Rendition const &		nr,
	Ellipse const *				ellipse,
	bool						_hoops_CSHIH) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;
	_hoops_GHHI alter *			curve = (_hoops_GHHI alter *)ellipse;
	Geometry alter *			geometry = (Geometry alter *)ellipse;
	Point						_hoops_RCPAS[_hoops_HCSAH+4];
	Point *						points = _hoops_RCPAS;
	int							count;
	int							n;
	int							offset1,
											offset2;
	float						_hoops_RCSAP = 0;
	float						_hoops_HISAP = 0;
	bool						_hoops_PISAA = BIT (nr->transform_rendition->heuristics,
															_hoops_PAIRP);
	bool						_hoops_CIHIA = false;


	n = HD_Determine_Elliptical_Res (nr, curve);
	if (n == 0) return;
	if (n > _hoops_HCSAH)
		ALLOC_ARRAY (points, n+4, Point);

	count = HD_Generate_Elliptical_Points (nr, curve, n, points);

	sc->_hoops_HPPAS._hoops_APPAS = &sc->_hoops_HPPAS._hoops_ACSAP;
	sc->_hoops_HPPAS._hoops_PPPAS = 0;
	sc->_hoops_HPPAS._hoops_RPPAS = nr->_hoops_IRR->_hoops_CCIRP.polyline;
	sc->_hoops_HPPAS._hoops_PHGGH = -1;
	sc->_hoops_HPPAS._hoops_CHGGH = -1;
	sc->_hoops_HPPAS._hoops_CIHIA = false;

	if (_hoops_PISAA) {
		sc->_hoops_HPPAS._hoops_RAI = (Geometry const *)curve;
		sc->_hoops_HPPAS._hoops_HHGGH = sc->_hoops_GICAH;

		if (_hoops_CSHIH)
			HD_Std_3D_Ellipse (nr, ellipse);
		else {
			Elliptical_Arc	arc;

			//_hoops_SHARC (&_hoops_HCPI->_hoops_GGHR,		_hoops_ACPAS,	&_hoops_PGIS._hoops_GGHR);
			arc.type = _hoops_GIIP;
			_hoops_RSAI (&ellipse->center,	Point,	&arc.center);
			_hoops_RSAI (&ellipse->plane,	_hoops_ARPA,	&arc.plane);
			_hoops_RSAI (&ellipse->_hoops_GGHI,	Vector,	&arc._hoops_GGHI);
			_hoops_RSAI (&ellipse->_hoops_RGHI,	Vector,	&arc._hoops_RGHI);
			_hoops_RSAI (&ellipse->major,	Point,	&arc.major);
			_hoops_RSAI (&ellipse->minor,	Point,	&arc.minor);
			arc.arc_start = 0.0f;
			arc._hoops_PHHI = 1.0f;
			arc._hoops_RRHH = ellipse->_hoops_RRHH;

			HD_Std_3D_Elliptical_Arc (nr, &arc);
		}

		sc->_hoops_HPPAS._hoops_RAI = null;
		if (sc->_hoops_HPPAS._hoops_CHGGH != -1) {
			_hoops_CIHIA = true;
			_hoops_RCSAP = sc->_hoops_HPPAS._hoops_IHGGH;
			_hoops_HISAP = sc->_hoops_HPPAS._hoops_HHGGH;
		}
	}
	else if (HD_Select_Point_List (nr, geometry, count, points,
							  true, _hoops_CSHIH,
							  &offset1, &offset2, &_hoops_HISAP, &_hoops_RCSAP)) {
		_hoops_CIHIA = true;
	}

	if (_hoops_CIHIA) {
		_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
		_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
		float						_hoops_GIGCR, _hoops_RIGCR, d3;
		float						x, y, w,
									_hoops_HSHGA, _hoops_ISHGA;

		_hoops_GIGCR = _hoops_RIGCR = d3 = 0.0f;
		switch (ellipse->type) {
			case _hoops_SGCP:
			case _hoops_GRCP:
			case _hoops_RRCP: {
				Point		_hoops_HCIS[3];
				Point const	*start;
				Point const	*_hoops_GGSSR;
				Point const	*end;

				if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
					/* _hoops_AAAHH _hoops_APSAR _hoops_GA'_hoops_RA _hoops_ASH _hoops_HPHR _hoops_RSSA, _hoops_IRHH _hoops_HHH */
					_hoops_AIHI const *	c = (_hoops_AIHI const *)ellipse;
					float					_hoops_GGHCR, _hoops_AGHCR;
					float					_hoops_PCPAS, _hoops_HCPAS;

					if (ellipse->type != _hoops_SGCP) {
						Circular_Arc_Lite const *	a;
						a = (Circular_Arc_Lite const *)c;

						_hoops_PCPAS = a->arc_start;
						_hoops_HCPAS = a->_hoops_PHHI;
					}
					else {
						/* _hoops_SRII _hoops_GA'_hoops_RA _hoops_HS _hoops_PGIS _hoops_HSPP & _hoops_SPCC, _hoops_RSPH _hoops_SCH */
						_hoops_PCPAS = 0;
						_hoops_HCPAS = 0.5;
					}

					_hoops_RICH (_hoops_PCPAS * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					_hoops_HCIS[0].x = c->center.x + _hoops_AGHCR * c->radius;
					_hoops_HCIS[0].y = c->center.y + _hoops_GGHCR * c->radius;
					_hoops_HCIS[0].z = 0.0f;

					_hoops_RICH (0.5f * (_hoops_PCPAS + _hoops_HCPAS) * 360.0f,
							   _hoops_GGHCR, _hoops_AGHCR);
					_hoops_HCIS[1].x = c->center.x + _hoops_AGHCR * c->radius;
					_hoops_HCIS[1].y = c->center.y + _hoops_GGHCR * c->radius;
					_hoops_HCIS[1].z = 0.0f;

					_hoops_RICH (_hoops_HCPAS * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					_hoops_HCIS[2].x = c->center.x + _hoops_AGHCR * c->radius;
					_hoops_HCIS[2].y = c->center.y + _hoops_GGHCR * c->radius;
					_hoops_HCIS[2].z = 0.0f;


					start  = &_hoops_HCIS[0];
					_hoops_GGSSR = &_hoops_HCIS[1];
					end	   = &_hoops_HCIS[2];
				}
				else {
					_hoops_PHPIR alter *_hoops_HGSSR = (_hoops_PHPIR alter *)ellipse;

					start  = &_hoops_HGSSR->start;
					_hoops_GGSSR = &_hoops_HGSSR->_hoops_GGSSR;
					end	   = &_hoops_HGSSR->end;
				}

				if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
					x = _hoops_HPRA (elements, *start);
					y = _hoops_IPRA (elements, *start);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					_hoops_GIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;

					x = _hoops_HPRA (elements, *_hoops_GGSSR);
					y = _hoops_IPRA (elements, *_hoops_GGSSR);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					_hoops_RIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;

					x = _hoops_HPRA (elements, *end);
					y = _hoops_IPRA (elements, *end);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					d3 = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
				}
				else {
					w = _hoops_PHCP (elements, *start);
					if (w <= 0.0f)
						_hoops_GIGCR = MAX_FLOAT;
					else {
						x = _hoops_HPRA (elements, *start) / w;
						y = _hoops_IPRA (elements, *start) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						_hoops_GIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}

					w = _hoops_PHCP (elements, *_hoops_GGSSR);
					if (w <= 0.0f)
						_hoops_RIGCR = MAX_FLOAT;
					else {
						x = _hoops_HPRA (elements, *_hoops_GGSSR) / w;
						y = _hoops_IPRA (elements, *_hoops_GGSSR) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						_hoops_RIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}

					w = _hoops_PHCP (elements, *end);
					if (w <= 0.0f)
						d3 = MAX_FLOAT;
					else {
						x = _hoops_HPRA (elements, *end) / w;
						y = _hoops_IPRA (elements, *end) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						d3 = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}
				}
			}	break;

			case _hoops_CGCP: {
				if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
					x = _hoops_HPRA (elements, ellipse->center);
					y = _hoops_IPRA (elements, ellipse->center);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					_hoops_GIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;

					x = _hoops_HPRA (elements, ellipse->major);
					y = _hoops_IPRA (elements, ellipse->major);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					_hoops_RIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;

					x = _hoops_HPRA (elements, ellipse->minor);
					y = _hoops_IPRA (elements, ellipse->minor);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					d3 = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
				}
				else {
					w = _hoops_PHCP (elements, ellipse->center);
					if (w <= 0.0f)
						_hoops_GIGCR = MAX_FLOAT;
					else {
						x = _hoops_HPRA (elements, ellipse->center) / w;
						y = _hoops_IPRA (elements, ellipse->center) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						_hoops_GIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}

					w = _hoops_PHCP (elements, ellipse->major);
					if (w <= 0.0f)
						_hoops_RIGCR = MAX_FLOAT;
					else {
						x = _hoops_HPRA (elements, ellipse->major) / w;
						y = _hoops_IPRA (elements, ellipse->major) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						_hoops_RIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}

					w = _hoops_PHCP (elements, ellipse->minor);
					if (w <= 0.0f)
						d3 = MAX_FLOAT;
					else {
						x = _hoops_HPRA (elements, ellipse->minor) / w;
						y = _hoops_IPRA (elements, ellipse->minor) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						d3 = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}
				}
			}	break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "Unexpected type during select_ellipse");
			}	break;
		}

		if (_hoops_GIGCR < _hoops_RIGCR) {
			if (_hoops_RIGCR < d3) {
				offset1 = 1;
				offset2 = 2;
			}
			else if (_hoops_GIGCR < d3) {
				offset1 = 1;
				offset2 = 3;
			}
			else {
				offset1 = 3;
				offset2 = 1;
			}
		}
		else {
			if (_hoops_GIGCR < d3) {
				offset1 = 2;
				offset2 = 1;
			}
			else if (d3 < _hoops_RIGCR) {
				offset1 = 3;
				offset2 = 2;
			}
			else {
				offset1 = 2;
				offset2 = 3;
			}
		}


		if (_hoops_CSHIH && _hoops_HISAP == 0.0f)
			HD_Elaborate_Selection (nr, dc->_hoops_RAI,
									dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
									offset1, offset2, 0,
									_hoops_RCSAP, _hoops_HISAP, T_FACES, null);
		else
			HD_Elaborate_Selection (nr, dc->_hoops_RAI,
									dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
									offset1, offset2, 0,
									_hoops_RCSAP, _hoops_HISAP, T_ANY_EDGE, null);
	}


	if (n > _hoops_HCSAH)
		FREE_ARRAY (points, n+4, Point);

	while (sc->_hoops_HPPAS._hoops_ACSAP != null) {
		_hoops_AISAP *	victim = sc->_hoops_HPPAS._hoops_ACSAP;
		sc->_hoops_HPPAS._hoops_ACSAP = victim->next;
		FREE (victim, _hoops_AISAP);
	}
	sc->_hoops_HPPAS._hoops_ACSAP = null;
	sc->_hoops_HPPAS._hoops_APPAS = &dc->_hoops_APHHP->_hoops_HPPAS._hoops_ACSAP;
	sc->_hoops_HPPAS._hoops_PPPAS = 0;
#endif
}

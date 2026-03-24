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
 * $Id: obf_tmp.txt 1.88 2010-05-17 22:45:19 covey Exp $
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

GLOBAL_FUNCTION void HD_Select_Elliptical_Arc (
	Net_Rendition const &		nr,
	Elliptical_Arc const *		arc) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;
	_hoops_GHHI alter *			curve = (_hoops_GHHI alter *)arc;
	Geometry alter *			geometry = (Geometry alter *)arc;
	Point						_hoops_RCPAS[_hoops_HCSAH+4];
	Point *						points = _hoops_RCPAS;
	int							count;
	int							n = 0;
	int							offset1,
											offset2;
	float						_hoops_RCSAP = 0.0f;
	float						_hoops_HISAP = 0.0f;
	bool						_hoops_PISAA = BIT (nr->transform_rendition->heuristics,
															_hoops_PAIRP);
	bool						_hoops_CIHIA = false;

	sc->_hoops_HPPAS._hoops_APPAS = &sc->_hoops_HPPAS._hoops_ACSAP;
	sc->_hoops_HPPAS._hoops_PPPAS = 0;
	sc->_hoops_HPPAS._hoops_RPPAS = nr->_hoops_IRR->_hoops_CCIRP.polyline;
	sc->_hoops_HPPAS._hoops_PHGGH = -1;
	sc->_hoops_HPPAS._hoops_CHGGH = -1;
	sc->_hoops_HPPAS._hoops_CIHIA = false;

	if (arc->type == _hoops_RIIP &&
		BIT (curve->_hoops_RRHH, _hoops_RGGGA)) {
		_hoops_SSSSR const *	a = (_hoops_SSSSR const *)arc;

		if (_hoops_PISAA) {
			sc->_hoops_HPPAS._hoops_RAI = geometry;
			sc->_hoops_HPPAS._hoops_HHGGH = sc->_hoops_GICAH;

			HD_Std_3D_Elliptical_Arc (nr, arc);

			sc->_hoops_HPPAS._hoops_RAI = null;
			if ((offset1 = sc->_hoops_HPPAS._hoops_CHGGH) != -1) {
				offset2 = offset1 + 1;

				HD_Elaborate_Selection (nr, dc->_hoops_RAI,
										dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
										offset1, offset2, 0,
										sc->_hoops_HPPAS._hoops_IHGGH, sc->_hoops_HPPAS._hoops_HHGGH,
										T_LINES, sc->_hoops_HPPAS._hoops_ACSAP);
			}
		}
		else if (HD_Select_Point_List (nr, geometry, 3, a->points,
									  false, false,
									  &offset1, &offset2, &_hoops_HISAP, &_hoops_RCSAP)) {
			HD_Elaborate_Selection (nr, dc->_hoops_RAI,
									dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
									offset1, offset2, 0,
									_hoops_RCSAP, _hoops_HISAP, T_LINES, null);
		}
		goto _hoops_HPAGR;
	}

	n = HD_Determine_Elliptical_Res (nr, curve);
	if (n == 0) return;
	if (n > _hoops_HCSAH)
		ALLOC_ARRAY (points, n+4, Point);

	count = HD_Generate_Elliptical_Points (nr, curve, n, points);

	/* _hoops_SRS _hoops_AA _hoops_GHSHA _hoops_GAR _hoops_RPP _hoops_SCH _hoops_AAPR _hoops_IRS _hoops_ISII */
	if (_hoops_PISAA) {
		sc->_hoops_HPPAS._hoops_RAI = (Geometry const *)curve;
		sc->_hoops_HPPAS._hoops_HHGGH = sc->_hoops_GICAH;

		HD_Std_3D_Elliptical_Arc (nr, arc);

		sc->_hoops_HPPAS._hoops_RAI = null;
		_hoops_RCSAP = sc->_hoops_HPPAS._hoops_IHGGH;

		if (sc->_hoops_HPPAS._hoops_CHGGH != -1)
			_hoops_CIHIA = true;
	}
	else if (HD_Select_Point_List (nr, geometry, count, points,
								  false, false,
								  &offset1, &offset2, &_hoops_HISAP, &_hoops_RCSAP)) {
		_hoops_CIHIA = true;
	}

	if (_hoops_CIHIA) {
		_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
		float							_hoops_GIGCR, _hoops_RIGCR, d3;
		float							x, y, w,
												_hoops_HSHGA, _hoops_ISHGA;

		_hoops_GIGCR = _hoops_RIGCR = d3 = 0.0f;
		switch (arc->type) {
			case _hoops_RIIP: {
				Point		_hoops_HCIS[3];
				Point const	*start;
				Point const	*_hoops_GGSSR;
				Point const	*end;

				if (BIT (curve->_hoops_RRHH, _hoops_SHHI)) {
					/* _hoops_AAAHH _hoops_APSAR _hoops_GA'_hoops_RA _hoops_ASH _hoops_HPHR _hoops_RSSA, _hoops_IRHH _hoops_HHH */
					Circular_Arc_Lite const *	a = (Circular_Arc_Lite const *)arc;
					float					_hoops_GGHCR, _hoops_AGHCR;
					float					_hoops_PCPAS, _hoops_HCPAS;

					_hoops_PCPAS = a->arc_start;
					_hoops_HCPAS = a->_hoops_PHHI;

					_hoops_RICH (_hoops_PCPAS * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					_hoops_HCIS[0].x = a->center.x + _hoops_AGHCR * a->radius;
					_hoops_HCIS[0].y = a->center.y + _hoops_GGHCR * a->radius;
					_hoops_HCIS[0].z = 0.0f;

					_hoops_RICH (0.5f * (_hoops_PCPAS + _hoops_HCPAS) * 360.0f,
							   _hoops_GGHCR, _hoops_AGHCR);
					_hoops_HCIS[1].x = a->center.x + _hoops_AGHCR * a->radius;
					_hoops_HCIS[1].y = a->center.y + _hoops_GGHCR * a->radius;
					_hoops_HCIS[1].z = 0.0f;

					_hoops_RICH (_hoops_HCPAS * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
					_hoops_HCIS[2].x = a->center.x + _hoops_AGHCR * a->radius;
					_hoops_HCIS[2].y = a->center.y + _hoops_GGHCR * a->radius;
					_hoops_HCIS[2].z = 0.0f;


					start  = &_hoops_HCIS[0];
					_hoops_GGSSR = &_hoops_HCIS[1];
					end	   = &_hoops_HCIS[2];
				}
				else {
					Circular_Arc alter	*_hoops_ICPAS = (Circular_Arc alter *)arc;

					start  = &_hoops_ICPAS->start;
					_hoops_GGSSR = &_hoops_ICPAS->_hoops_GGSSR;
					end	   = &_hoops_ICPAS->end;
				}

				if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
					x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, *start);
					y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, *start);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					_hoops_GIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;

					x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, *_hoops_GGSSR);
					y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, *_hoops_GGSSR);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					_hoops_RIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;

					x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, *end);
					y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, *end);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					d3 = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
				}
				else {
					w = _hoops_PHCP (_hoops_IHCR->matrix->data.elements, *start);
					if (w <= 0.0f)
						_hoops_GIGCR = MAX_FLOAT;
					else {
						x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, *start) / w;
						y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, *start) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						_hoops_GIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}

					w = _hoops_PHCP (_hoops_IHCR->matrix->data.elements, *_hoops_GGSSR);
					if (w <= 0.0f)
						_hoops_RIGCR = MAX_FLOAT;
					else {
						x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, *_hoops_GGSSR) / w;
						y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, *_hoops_GGSSR) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						_hoops_RIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}

					w = _hoops_PHCP (_hoops_IHCR->matrix->data.elements, *end);
					if (w <= 0.0f)
						d3 = MAX_FLOAT;
					else {
						x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, *end) / w;
						y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, *end) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						d3 = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}
				}
			}	break;

			case _hoops_GIIP: {
				if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
					x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, arc->center);
					y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, arc->center);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					_hoops_GIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;

					x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, arc->major);
					y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, arc->major);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					_hoops_RIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;

					x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, arc->minor);
					y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, arc->minor);
					_hoops_HSHGA = sc->_hoops_AICAH.x - x;
					_hoops_ISHGA = sc->_hoops_AICAH.y - y;
					d3 = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
				}
				else {
					w = _hoops_PHCP (_hoops_IHCR->matrix->data.elements, arc->center);
					if (w <= 0.0f)
						_hoops_GIGCR = MAX_FLOAT;
					else {
						x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, arc->center) / w;
						y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, arc->center) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						_hoops_GIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}

					w = _hoops_PHCP (_hoops_IHCR->matrix->data.elements, arc->major);
					if (w <= 0.0f)
						_hoops_RIGCR = MAX_FLOAT;
					else {
						x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, arc->major) / w;
						y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, arc->major) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						_hoops_RIGCR = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}

					w = _hoops_PHCP (_hoops_IHCR->matrix->data.elements, arc->minor);
					if (w <= 0.0f)
						d3 = MAX_FLOAT;
					else {
						x = _hoops_HPRA (_hoops_IHCR->matrix->data.elements, arc->minor) / w;
						y = _hoops_IPRA (_hoops_IHCR->matrix->data.elements, arc->minor) / w;

						_hoops_HSHGA = sc->_hoops_AICAH.x - x;
						_hoops_ISHGA = sc->_hoops_AICAH.y - y;
						d3 = _hoops_HSHGA * _hoops_HSHGA + _hoops_ISHGA * _hoops_ISHGA;
					}
				}
			}	break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected type during select_elliptical_arc");
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


		HD_Elaborate_Selection (nr, dc->_hoops_RAI,
								dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
								offset1, offset2, 0,
								_hoops_RCSAP, _hoops_HISAP, T_LINES, null);
	}

  _hoops_HPAGR:
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

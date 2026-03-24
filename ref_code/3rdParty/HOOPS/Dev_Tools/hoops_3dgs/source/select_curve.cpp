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
 * $Id: obf_tmp.txt 1.40 2010-05-17 22:45:19 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "select.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_SELECTION

#if 0
	static const float _hoops_ASRHH[] = {
		0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	10, 11, 12, 13, 14, 15 };
	static const float _hoops_PSRHH[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
#endif

#define _hoops_IRGPA 2.0f


/*********************************************************************\
 *	_hoops_GIPAS
 *	_hoops_PGAA
 *	_hoops_HRS _hoops_RH _hoops_RRAA _hoops_IIGR _hoops_RH _hoops_GIRA _hoops_GAPA _hoops_PGCR _hoops_RSSA
\*********************************************************************/
local float _hoops_RIPAS (Point const *p1, Point const *p2) {
	float dist = 0;

	dist += (p1->x - p2->x) * (p1->x - p2->x);
	dist += (p1->y - p2->y) * (p1->y - p2->y);
	dist += (p1->z - p2->z) * (p1->z - p2->z);

	return dist; 
} /* _hoops_RSGR _hoops_API _hoops_GIPAS */


/*********************************************************************\
 *	_hoops_AIPAS
\*********************************************************************/
GLOBAL_FUNCTION void HD_Select_NURBS_Curve (
	Net_Rendition const &		nr,
	_hoops_PIRGR alter *			curve) {
#ifndef _hoops_CCPIR
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;
	bool						_hoops_PISAA = BIT (nr->transform_rendition->heuristics,
															_hoops_PAIRP);
	int i;
	int offset1, offset2;
	float _hoops_RCSAP;
	float _hoops_HISAP;
	int _hoops_PIPAS = -1;
	float dist, _hoops_HIPAS = MAX_FLOAT;

	if (!curve->control_point_count)
		return;

	if (curve->polyline.points == null) {
		Polyline polyline;
		HI_Generate_NURBS_Polyline (curve,
			&nr->_hoops_ARA->_hoops_APPI, 
			&nr->transform_rendition->matrix->data,
			&polyline, 0);
		if (polyline.points == null)
			return;
		curve->polyline.points = polyline.points;
		curve->polyline.allocated = polyline.allocated;
		curve->polyline.count = polyline.count;
	}

	sc->_hoops_HPPAS._hoops_APPAS = &sc->_hoops_HPPAS._hoops_ACSAP;
	sc->_hoops_HPPAS._hoops_PPPAS = 0;
	sc->_hoops_HPPAS._hoops_RPPAS = nr->_hoops_IRR->_hoops_CCIRP.polyline;
	sc->_hoops_HPPAS._hoops_PHGGH = -1;
	sc->_hoops_HPPAS._hoops_CHGGH = -1;
	sc->_hoops_HPPAS._hoops_CIHIA = false;
	/* _hoops_SRS _hoops_AA _hoops_GHSHA _hoops_GAR _hoops_RPP _hoops_SCH _hoops_AAPR _hoops_IRS _hoops_ISII */
	if (_hoops_PISAA) {
		sc->_hoops_HPPAS._hoops_RAI = (Geometry const *)curve;
		sc->_hoops_HPPAS._hoops_HHGGH = sc->_hoops_GICAH;

		HD_Std_3D_NURBS_Curve (nr, curve);

		sc->_hoops_HPPAS._hoops_RAI = null;
		if ((offset1 = sc->_hoops_HPPAS._hoops_CHGGH) != -1) {
			/* _hoops_SSS _hoops_RH _hoops_PHRHA _hoops_RGSHA _hoops_PPSR */
			for (i = 0; i < curve->control_point_count; i++) {
				dist = _hoops_RIPAS (
					&curve->polyline.points[offset1],
					&curve->control_points[i]);
				if (dist < _hoops_HIPAS) { 
					_hoops_HIPAS = dist; 
					_hoops_PIPAS = i;
				}
			}

			HD_Elaborate_Selection (nr, dc->_hoops_RAI,
									dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
									_hoops_PIPAS, -1, -1,
									sc->_hoops_HPPAS._hoops_IHGGH, sc->_hoops_HPPAS._hoops_HHGGH,
									T_LINES, sc->_hoops_HPPAS._hoops_ACSAP);
		}
	}
	else if (HD_Select_Point_List (nr, (Geometry const *)curve, 
					  curve->polyline.count, curve->polyline.points,
					  false, false,
					  &offset1, &offset2, &_hoops_HISAP, &_hoops_RCSAP)) {
		/* _hoops_SSS _hoops_RH _hoops_PHRHA _hoops_RGSHA _hoops_PPSR */
		for (i = 0; i < curve->control_point_count; i++)
		{
			dist = _hoops_RIPAS (
				&curve->polyline.points[offset1],
				&curve->control_points[i]);
			if (dist < _hoops_HIPAS) { 
				_hoops_HIPAS = dist; 
				_hoops_PIPAS = i;
			}
		}
		/* _hoops_HSPAA _hoops_RH _hoops_HPHS _hoops_PSAP _hoops_IS _hoops_SHH _hoops_IIPAS */
		HD_Elaborate_Selection (nr, dc->_hoops_RAI,
								dc->_hoops_RAI->key, _hoops_AIRIR(dc->_hoops_RAI),
								_hoops_PIPAS, -1, -1,
								_hoops_RCSAP, _hoops_HISAP, T_ANY_EDGE, null);
	}

	while (sc->_hoops_HPPAS._hoops_ACSAP != null) {
		_hoops_AISAP *	victim = sc->_hoops_HPPAS._hoops_ACSAP;
		sc->_hoops_HPPAS._hoops_ACSAP = victim->next;
		FREE (victim, _hoops_AISAP);
	}
	sc->_hoops_HPPAS._hoops_ACSAP = null;
	sc->_hoops_HPPAS._hoops_APPAS = &dc->_hoops_APHHP->_hoops_HPPAS._hoops_ACSAP;
	sc->_hoops_HPPAS._hoops_PPPAS = 0;
#endif
} /* _hoops_RSGR _hoops_API _hoops_AIPAS */

#endif

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
 * $Id: obf_tmp.txt 1.49 2009-11-07 01:16:35 covey Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "patterns.h"
#include "hd_proto.h"


GLOBAL_FUNCTION void HD_Std_DC_Polydot (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
#ifndef DISABLE_DRAW_3D
	DC_Point					pt[2];

	if (nr->transform_rendition->_hoops_HCHH != null) {
		Net_Rendition					_hoops_RHICP = nr.Copy();
		_hoops_HHCR alter &		_hoops_AHICP = _hoops_RHICP->transform_rendition.Modify();

		if (nr->transform_rendition->_hoops_HCHH->_hoops_AHGGA == null)
			HD_Validate_Clipping_Rendition (_hoops_AHICP, _hoops_AHICP->_hoops_HCHH);

		if (_hoops_AHICP->_hoops_HCHH->_hoops_AHGGA->count == 0)	// _hoops_ISAP _hoops_PAH _hoops_SHH _hoops_CHCC
			return;


		_hoops_AHICP->_hoops_HCHH = null;

		while (count-- > 0) {
			_hoops_ASHH const *		_hoops_CRAIR = nr->transform_rendition->_hoops_HCHH->_hoops_AHGGA;
			bool							draw = false;

			do {
				_hoops_GPPA const *	_hoops_GRCPR = _hoops_CRAIR->_hoops_GRCPR;

				draw = true;
				for (int i=0; i<_hoops_CRAIR->count; i++) {
					if (_hoops_GRCPR[i]._hoops_SPPA.a * points->x +
							_hoops_GRCPR[i]._hoops_SPPA.b * points->y +
								_hoops_GRCPR[i]._hoops_SPPA.d > 0.0f) {
						draw = false;
						break;
					}
				}
			} while (!draw && (_hoops_CRAIR = _hoops_CRAIR->next) != null);

			if (draw)
				_hoops_HAPIP (_hoops_RHICP, points);

			points++;
		}
	}
	else {
		while (count-- > 0) {
			pt[0].x = points->x;
			pt[0].y = points->y;
			pt[0].z = points->z;
			pt[1].x = points->x;
			pt[1].y = points->y;
			pt[1].z = points->z;

			_hoops_SCGGA (nr, 2, pt);

			points++;
		}
	}
#endif
}

GLOBAL_FUNCTION void HD_Std_DC_Colorized_Polydot (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				_hoops_IASGR,
	bool						single) {
#ifndef DISABLE_DRAW_3D

	if (nr->transform_rendition->_hoops_HCHH != null) {
		Net_Rendition					_hoops_RHICP = nr.Copy();
		_hoops_HHCR alter &		_hoops_AHICP = _hoops_RHICP->transform_rendition.Modify();

		if (nr->transform_rendition->_hoops_HCHH->_hoops_AHGGA == null)
			HD_Validate_Clipping_Rendition (_hoops_AHICP, _hoops_AHICP->_hoops_HCHH);

		if (_hoops_AHICP->_hoops_HCHH->_hoops_AHGGA->count == 0)	// _hoops_ISAP _hoops_PAH _hoops_SHH _hoops_CHCC
			return;


		_hoops_AHICP->_hoops_HCHH = null;

		DC_Point alter *				new_points = null;
		DC_Point alter *				_hoops_GSGGA = null;
		RGBAS32 alter *					_hoops_SIICS = null;
		RGBAS32 alter *					_hoops_GCICS = null;
		int								_hoops_RGCCA = 0;
		int								n = count;

		while (n-- > 0) {
			_hoops_ASHH const *		_hoops_CRAIR = nr->transform_rendition->_hoops_HCHH->_hoops_AHGGA;
			bool							draw = false;

			do {
				_hoops_GPPA const *	_hoops_GRCPR = _hoops_CRAIR->_hoops_GRCPR;

				draw = true;
				for (int i=0; i<_hoops_CRAIR->count; i++) {
					if (_hoops_GRCPR[i]._hoops_SPPA.a * points->x +
							_hoops_GRCPR[i]._hoops_SPPA.b * points->y +
								_hoops_GRCPR[i]._hoops_SPPA.d > 0.0f) {
						draw = false;
						break;
					}
				}
			} while (!draw && (_hoops_CRAIR = _hoops_CRAIR->next) != null);

			if (draw) {
				*_hoops_GSGGA++ = *points;

				if (!single)
					*_hoops_GCICS++ = *_hoops_IASGR;

				_hoops_RGCCA++;
			}

			points++;
			if (!single)
				_hoops_IASGR++;
		}

		if (!single)
			_hoops_RIGGA (_hoops_RHICP, _hoops_RGCCA, new_points, _hoops_SIICS, true);
		else
			_hoops_RIGGA (_hoops_RHICP, _hoops_RGCCA, new_points, _hoops_IASGR, true);

		FREE_ARRAY (new_points, count, DC_Point);
		if (!single)
			FREE_ARRAY (_hoops_SIICS, count, RGBAS32);
	}
	else {
		while (count-- > 0) {
			_hoops_SSGCP (nr, points, points, 0, _hoops_CSGSP, 0, (const void* const *)&_hoops_IASGR,
							   FP_SOLID, null, null);

			points++;
			if (!single)
				_hoops_IASGR++;
		}
	}
#endif
}


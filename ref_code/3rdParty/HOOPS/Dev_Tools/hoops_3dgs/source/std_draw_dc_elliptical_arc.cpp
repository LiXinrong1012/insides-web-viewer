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
 * $Id: obf_tmp.txt 1.41 2010-06-04 21:37:19 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"


#define _hoops_SAIGA	256

GLOBAL_FUNCTION void HD_Std_DC_Elliptical_Arc (
	Net_Rendition const &		in_nr,
	DC_Point const *			center,
	DC_Point const *			radius,
	float						start,
	float						end) {
	Net_Rendition				nr = in_nr;
	float						_hoops_SAGP;

	if ((_hoops_SAGP = _hoops_IAAA (radius->x, radius->y)) <= 1) {
		_hoops_HAPIP (nr, center);
	}
	else {
		DC_Point				pt[_hoops_SAIGA];
		DC_Point alter *		pp;
		DC_Point alter *		pe;
		float					_hoops_HGII;
		float					theta;
		float					delta;
		float					_hoops_GGHCR;
		float					_hoops_AGHCR;
		int						count;

		if (!BIT(nr->_hoops_AHP->flags, _hoops_HGRIP) &&
			BIT(nr->_hoops_AHP->line_style->flags, LSF_MIDDLE_GLYPH|LSF_JOIN))
			nr.Modify()->_hoops_AHP.Modify()->flags |= _hoops_HGRIP;

		if (end < start)
			end += 1.0f;

		_hoops_HGII = 4.0f * _hoops_SGIHR (_hoops_SAGP);
		if (_hoops_HGII >= _hoops_SAIGA)
				_hoops_HGII = _hoops_SAIGA - 1;
		count = (int)(_hoops_HGII * (end - start));

		pp = pt;
		pe = pp + count;

		theta = 360.0f * start;
		delta = 360.0f / _hoops_HGII;

		do {
			_hoops_RICH (theta, _hoops_GGHCR, _hoops_AGHCR);
			theta += delta;
			pp->x = center->x + radius->x * _hoops_AGHCR;
			pp->y = center->y + radius->y * _hoops_GGHCR;
			pp->z = center->z;
		} _hoops_RGGA (++pp >= pe);

		_hoops_RICH (360.0f * end, _hoops_GGHCR, _hoops_AGHCR);
		pp->x = center->x + radius->x * _hoops_AGHCR;
		pp->y = center->y + radius->y * _hoops_GGHCR;
		pp->z = center->z;

		_hoops_SCGGA (nr, pp - pt + 1, pt);
	}
}

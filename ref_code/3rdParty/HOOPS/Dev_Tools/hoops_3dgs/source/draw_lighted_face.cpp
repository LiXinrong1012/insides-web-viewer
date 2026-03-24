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
 * $Id: obf_tmp.txt 1.62 2009-10-23 23:02:06 trask Exp $
 */


#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "hd_proto.h"
#include "hi_proto.h"

GLOBAL_FUNCTION void HD_Draw_Lighted_Face (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			_hoops_GHPCP,
	Geometry const *			geometry) {

	if (count < 3) return;

	/*
	 *	_hoops_RPP _hoops_SR _hoops_HS _hoops_IRS _hoops_RRR _hoops_PSCR ...
	 */
	if (nr->_hoops_IHA->_hoops_AGP != null) {
		if (geometry->type == _hoops_RCIP) { /* _hoops_SHCAR, _hoops_HAR _hoops_IRS _hoops_PRHC _hoops_PAR _hoops_HCPI */
			if (!BIT (geometry->_hoops_RRHH, _hoops_ARHH))
				HI_Find_Polygon_Plane ((Polygon alter *)geometry);

			if (!BIT (geometry->_hoops_RRHH, _hoops_IASGP)) {
				_hoops_HRPIP (nr, count, _hoops_GHPCP);
				return;
			}
		}

		{
			RGBA			result;
			RGBAS32			color;
			unsigned char	_hoops_IRIR;

			if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH)
				_hoops_IRIR = (unsigned char) (255.99f * nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR);
			else
				_hoops_IRIR = _hoops_GPGCR;

			HD_Figure_Light (nr, geometry, &result);
			color = RGBAS32 (result, _hoops_IRIR);

			_hoops_IPHCP (nr, count, _hoops_GHPCP, &color);
		}
	}

	/*
	 *	_hoops_SHS _hoops_SR _hoops_HS _hoops_HCH _hoops_CPHCP _hoops_SPHCP....
	 */
	else {
		RGBA			result;
		RGBAS32			color;
		unsigned char	_hoops_IRIR;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH)
			_hoops_IRIR = (unsigned char) (255.99f * nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR);
		else
			_hoops_IRIR = _hoops_GPGCR;

		/* _hoops_GHHCP _hoops_CGH _hoops_GACHR _hoops_RHHCP */
		HD_Figure_Light (nr, geometry, &result);
		color = RGBAS32 (result, _hoops_IRIR);

		_hoops_IPHCP (nr, count, _hoops_GHPCP, &color);
	}
}



GLOBAL_FUNCTION void HD_Draw_Lighted_Polygon (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			_hoops_GHPCP,
	Geometry const *			geometry) {

	HD_Draw_Lighted_Face (nr, count, _hoops_GHPCP, geometry);

	/* _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_AHHCP _hoops_III _hoops_CCA _hoops_ISHA -- _hoops_CPHR _hoops_HPP _hoops_PHHCP _hoops_ARRS */

	_hoops_SRPIP (nr, count, _hoops_GHPCP);
}


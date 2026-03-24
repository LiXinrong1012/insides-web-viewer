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
 * $Id: obf_tmp.txt 1.39 2009-10-23 23:29:24 trask Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "hd_proto.h"


GLOBAL_FUNCTION void HD_Std_DC_Rectangle (
	Net_Rendition const & nr,
	int						left,
	int						right,
	int						bottom,
	int						top) {
	DC_Point				pt[4];

	pt[0].x = (float)left;	  pt[0].y = (float)bottom;
	pt[1].x = (float)left;	  pt[1].y = (float)top;
	pt[2].x = (float)right;	  pt[2].y = (float)top;
	pt[3].x = (float)right;	  pt[3].y = (float)bottom;

	/* _hoops_GPGP _hoops_HAGIR, _hoops_AHCR _hoops_HSH _hoops_GRS _hoops_IIP _hoops_SHH _hoops_SIGR _hoops_PGGA _hoops_CIPSI
	 * _hoops_CHR _hoops_RGAR _hoops_CHCC _hoops_GGR _hoops_GRAA-_hoops_CCSHP-_hoops_ISSGR _hoops_CCH. _hoops_GPGP _hoops_PAHSR, _hoops_SHH
	 * _hoops_AGAPR _hoops_PPR _hoops_RSPC _hoops_HHH _hoops_HSH.
	 */
	pt[0].z = pt[1].z = pt[2].z = pt[3].z = nr->transform_rendition->_hoops_PCHH;

	_hoops_RSGCP (nr, 4, pt);
}

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
 * $Id: obf_tmp.txt 1.39 2009-10-23 23:29:16 trask Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "hd_proto.h"


GLOBAL_FUNCTION void HD_Std_DC_Polygon (
	Net_Rendition const &	inr,
	int						count,
	DC_Point const *		points) {
#ifndef DISABLE_DRAW_3D
	Net_Rendition			nr = inr;

	_hoops_HRPIP (nr, count-1, points);

	/* _hoops_GHCA _hoops_HS _hoops_RPII _hoops_HGAS _hoops_HPP _hoops_GHAP._hoops_RPRAR. */
	if (nr->_hoops_AHP != nr->_hoops_RHP)
		nr.Modify()->_hoops_AHP = nr->_hoops_RHP;

	_hoops_SRPIP (nr, count, points);
#endif
}

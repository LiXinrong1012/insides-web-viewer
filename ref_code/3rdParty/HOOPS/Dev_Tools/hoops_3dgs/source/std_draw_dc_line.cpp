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
 * $Id: obf_tmp.txt 1.31 2009-10-23 23:29:08 trask Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "hd_proto.h"


GLOBAL_FUNCTION void HD_Std_DC_Phong_Polyline (
	Net_Rendition const & nr,
	int						count,
	DC_Point const *		points,
	RGBA const *			colors,
	_hoops_ARPA const *		planes) {

	HD_Span_DC_Phong_Polyline (nr, count, points, colors, planes);
}

GLOBAL_FUNCTION void HD_Std_DC_Textured_Polyline (
	Net_Rendition const & nr,
	int						count,
	DC_Point const *		points,
	RGBA const *			colors,
	_hoops_ARPA const *		planes,
	_hoops_RSSH const *	params,
	Integer32			param_width,
	_hoops_SSIC		param_flags) {

	HD_Span_DC_Textured_Polyline (nr, count, points, colors, planes, params, param_width, param_flags);
}

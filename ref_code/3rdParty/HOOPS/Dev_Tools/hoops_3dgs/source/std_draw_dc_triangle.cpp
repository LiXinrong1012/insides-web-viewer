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
 * $Id: obf_tmp.txt 1.30 2009-10-23 23:29:32 trask Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "patterns.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HD_Std_DC_Polytriangle (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points) {

#ifndef DISABLE_DRAW_3D
	
	HD_Span_DC_Polytriangle (nr, count, points);
#endif
}

GLOBAL_FUNCTION void HD_Std_DC_Colorized_Polytris (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*_hoops_HICGR,
	bool						single) {
#ifndef DISABLE_DRAW_3D

	HD_Span_DC_Colorized_Polytris (nr, count, points, _hoops_HICGR, single);
#endif
}

GLOBAL_FUNCTION void HD_Std_DC_Gouraud_Polytris (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors) {
#ifndef DISABLE_DRAW_3D

	HD_Span_DC_Gouraud_Polytris (nr, count, points, colors);
#endif
}


GLOBAL_FUNCTION void HD_Std_DC_Phong_Polytris (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBA const					*colors,
	_hoops_ARPA const					*planes) {

	HD_Std_DC_Textured_Polytris (nr, count, points, colors, planes, null, 0, 0);
}


GLOBAL_FUNCTION void HD_Std_DC_Textured_Polytris (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBA const					*colors,
	_hoops_ARPA const					*planes,
	_hoops_RSSH const				*params,
	Integer32					param_width,
	_hoops_SSIC				param_flags) {
#ifndef DISABLE_DRAW_3D

	HD_Span_DC_Textured_Polytris (nr, count,
			points, colors, planes,
			params, param_width, param_flags);
#endif
}




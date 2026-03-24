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
 * $Id: obf_tmp.txt 1.7 2010-11-04 21:25:03 trask Exp $
 */

#ifdef _hoops_GAACI
#undef _hoops_GAACI
#endif
#define _hoops_GAACI 0x0501

#include "windows_wrapper.h"	// _hoops_CGRI <_hoops_SPHGR._hoops_GGHR>, _hoops_PIHA _hoops_RCPS _hoops_SRS :(

#include "hoops.h"
#include "hd_proto.h"

#ifndef OSX_SYSTEM
#ifndef _hoops_ICGGC

#include "hoops.h"
#include "hd_proto.h"

/*
 * _hoops_APICR _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_MGL_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI, 
	int						request, 
	void *					request_info) 
{
	UNREFERENCED(request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "mgl");
}

#else /* _hoops_SSSPC _hoops_ARGAC */

#include "hoops.h"
#include "hd_proto.h"

#ifndef __cplusplus
#define c_class class
#endif

#define _hoops_HHAGC
//#_hoops_PPIP _hoops_HCCPC

//#_hoops_PPIP _hoops_ARGAC
//#_hoops_PPIP _hoops_GGGHC

#define OPENGL_DRIVER
#define DECLARE_OGL_PROTOTYPES
//#_hoops_PPIP _hoops_RGGHC
#include "GL/gl_mangle.h"
#include "GL/glu_mangle.h"
#include "GL/glx_mangle.h"

#if defined(_WIN32)
#include "ogl_wgl.cpp"
#else
#include "ogl_glx.cpp"
#endif

/* _hoops_IRGH _hoops_GCAII _hoops_PIH: */
/*
 *  _hoops_SCSA _hoops_GCAII _hoops_PIH _hoops_HRGR _hoops_CCGC _hoops_CHHH, _hoops_HIH _hoops_GGR _hoops_RGR _hoops_AGIR _hoops_RH
 *  _hoops_PIRA _hoops_HRGR _hoops_IRS _hoops_PCPH _hoops_GRGPR _hoops_PGAP _hoops_CGH _hoops_IIP _hoops_AGRP _hoops_ARR _hoops_SCH'_hoops_GRI
 *  _hoops_RPII _hoops_CPSIA. _hoops_PHGP _hoops_RGR _hoops_HRGR _hoops_HHSH _hoops_IRS _hoops_IRIGR-_hoops_RGAR!
 */

#if 0
#define DEBUG_PRINTS 1
#endif

#endif
#endif

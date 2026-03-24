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
 * $Id: obf_tmp.txt 2.1729 2011-01-27 08:35:53 heppe Exp $
 */


#ifndef HOOPS_DEFINED
# include "hoops.h"
#endif

#ifndef NUTCRACKER
#ifdef _MSC_VER
#define WGL_DRIVER // _hoops_GRHP _hoops_RAHRH _hoops_CIGGC _hoops_SCSAH
#endif
#endif

#if defined(GLX_DRIVER) || defined(WGL_DRIVER) || defined(AGL_DRIVER) || defined(COCOA_OGL_DRIVER)

#include "ogl.h"
#include "oglext.h"

#include "hc_proto.h"
#include "hi_proto.h"
#include "phdraw.h"


//_hoops_PH _hoops_SIA _hoops_ASSP'_hoops_RA _hoops_IPHR _hoops_PRRP _hoops_SIHH _hoops_AIRRR
#define _hoops_SIGGC

#ifdef _hoops_GCGGC
#include "HoopsShaderHooks.h"
_hoops_RCGGC* _hoops_ACGGC(_hoops_PCGGC _hoops_HCGGC);
#endif



static XBits	_hoops_RSPRH[] = {
	{"NONE",							XBIT_NONE},
	{"UNDRAW_OVERLAY_FRONT_AND_BACK",	XBIT_UNDRAW_OVERLAY_FRONT_AND_BACK},
	{"BAD_KTX",							XBIT_BAD_KTX},
	{"DOUBLE_BUFFER_SWAP_ONLY",			XBIT_DOUBLE_BUFFER_SWAP_ONLY},
	{"BAD_VERTEX_ARRAYS",				XBIT_BAD_VERTEX_ARRAYS},
	{"BAD_SCISSORING",					XBIT_BAD_SCISSORING},
	{"EYE_SPACE_DEPTH",					XBIT_EYE_SPACE_DEPTH},
	{"FORCE_DEFAULT_SOFTWARE",			XBIT_FORCE_DEFAULT_SOFTWARE},
	{"BAD_OVERLAY",						XBIT_BAD_OVERLAY},
	{"BAD_STENCIL",						XBIT_BAD_STENCIL},
	{"BAD_TRANSPARENT_POINT",			XBIT_BAD_TRANSPARENT_POINT},
	{"RESTORE_REGION_ZBUFFER_OFF",		XBIT_RESTORE_REGION_ZBUFFER_OFF},
	{"BAD_MULTILIGHT",					XBIT_BAD_MULTILIGHT},
	{"BAD_DISPLAY_LIST",				XBIT_BAD_DISPLAY_LIST},
	{"FORCE_OLD_CHOOSE_PIXEL_FORMAT",	XBIT_FORCE_OLD_CHOOSE_PIXEL_FORMAT},
	{"BAD_PIXEL_STORE",					XBIT_BAD_PIXEL_STORE},
	{"RASTERS_AS_VERTICES",				XBIT_RASTERS_AS_VERTICES},
	{"ALLOW_DRAWPIXEL_RESTORE",			XBIT_ALLOW_DRAWPIXEL_RESTORE},
	{"DOUBLE_BUFFER_COPY_ONLY",			XBIT_DOUBLE_BUFFER_COPY_ONLY},
	{"LIES_ABOUT_SWAP",					XBIT_LIES_ABOUT_SWAP},
	{"PIXEL_OPERATIONS_EXPENSIVE",		XBIT_PIXEL_OPERATIONS_EXPENSIVE},
	{"BAD_PHONG",						XBIT_BAD_PHONG},
	{"BAD_PATTERNED_LINES",				XBIT_BAD_PATTERNED_LINES},
	{"BAD_PBUFFER",						XBIT_BAD_PBUFFER},
	{"BAD_SPOTLIGHT_TEXTURE",			XBIT_BAD_SPOTLIGHT_TEXTURE},
	{"4142_WORKAROUND",					XBIT_4142_WORKAROUND},
	{"BAD_TWO_SIDED_LIGHTING",			XBIT_BAD_TWO_SIDED_LIGHTING},
	{"BAD_FLAT_VERTEX_ARRAYS",			XBIT_BAD_FLAT_VERTEX_ARRAYS},
	{"BAD_WGL_ARB_BUFFER",				XBIT_BAD_WGL_ARB_BUFFER},
	{"BAD_MSAA_WGL_ARB_BUFFER",			XBIT_BAD_MSAA_WGL_ARB_BUFFER},
	{"WGL_ARB_BUFFER_1024_LIMIT",		XBIT_WGL_ARB_BUFFER_1024_LIMIT},
	{"FLAT_TRISTRIP_MISMATCH",			XBIT_FLAT_TRISTRIP_MISMATCH},
	{"BAD_NONDL_VERTEX_ARRAYS",			XBIT_BAD_NONDL_VERTEX_ARRAYS},
	{"BAD_SINGLE_BUFFERING",            XBIT_BAD_SINGLE_BUFFERING},
	{"BAD_ACCUMULATION_BUFFER",         XBIT_BAD_ACCUMULATION_BUFFER},
	{"BAD_16BIT_ACCUMULATION_BUFFER",   XBIT_BAD_16BIT_ACCUMULATION_BUFFER},
	{"LINE_PATTERN_NEEDS_BLENDING",     XBIT_LINE_PATTERN_NEEDS_BLENDING},
	{"SLOW_MSAA_DEPTH_TEXTURE",			XBIT_SLOW_MSAA_DEPTH_TEXTURE},
	{"BAD_MSAA_ACCUMULATION_BUFFER",    XBIT_BAD_MSAA_ACCUMULATION_BUFFER},
	{"BAD_VERTEX_BUFFER_OBJECT",		XBIT_BAD_VERTEX_BUFFER_OBJECT},
	{"BAD_ELEMENT_BUFFER",				XBIT_BAD_ELEMENT_BUFFER},
	{"BAD_CUT_POINTS",					XBIT_BAD_CUT_POINTS},
	{"BAD_FRAGMENT_PROGRAM",			XBIT_BAD_FRAGMENT_PROGRAM},
	{"BAD_SEPARATE_SPECULAR",			XBIT_BAD_SEPARATE_SPECULAR},
	{"DELAYED_VERTEX_ARRAYS",			XBIT_DELAYED_VERTEX_ARRAYS},
	{"BAD_TEXTURE_RECTANGLE",			XBIT_BAD_TEXTURE_RECTANGLE},
	{"BAD_MULTIPLE_CLIP_PLANES",		XBIT_BAD_MULTIPLE_CLIP_PLANES},
	{"SLOW_PEELED_LINESMOOTH",			XBIT_SLOW_PEELED_LINESMOOTH},
	{"BAD_NON_POWER_OF_2_TEXTURES",		XBIT_BAD_NON_POWER_OF_2_TEXTURES},
	{"TEXTURE_SIZE_OFF_BY_ONE",			XBIT_TEXTURE_SIZE_OFF_BY_ONE},
	{"",0}
};

#ifdef _hoops_ICGGC
static const char * _hoops_CCGGC = "MGL_Software";
static const char * _hoops_SCGGC = "MGL_Software";
#else

#ifdef AGL_DRIVER
static const char * _hoops_CCGGC = "AGL_Software";
static const char * _hoops_SCGGC = "AGL_Hardware";
#endif

#ifdef COCOA_OGL_DRIVER
static const char * _hoops_CCGGC = "Cocoa_OGL_Software";
static const char * _hoops_SCGGC = "Cocoa_OGL_Hardware";
#endif

#ifdef WGL_DRIVER
static const char * _hoops_CCGGC = "WGL_Software";
static const char * _hoops_SCGGC = "WGL_Hardware";
#endif

#ifdef GLX_DRIVER
static const char * _hoops_CCGGC = "GLX_Software";
static const char * _hoops_SCGGC = "GLX_Hardware";
#endif

#endif


/* _hoops_RGR _hoops_GASR _hoops_CGH _hoops_SHH _hoops_SAHR 520 _hoops_GCSRR, _hoops_HIS _hoops_SCH _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_GSGS _hoops_IIGR _hoops_IRS _hoops_IGIR _hoops_RCSRR */
static const unsigned char _hoops_HRPH[65][8] = {
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	{0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	{0x0, 0x80, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0},
	{0x0, 0x80, 0x0, 0x0, 0x0, 0x88, 0x0, 0x0},
	{0x0, 0x88, 0x0, 0x0, 0x0, 0x88, 0x0, 0x0},
	{0x0, 0x88, 0x0, 0x20, 0x0, 0x88, 0x0, 0x0},
	{0x0, 0x88, 0x0, 0x20, 0x0, 0x88, 0x0, 0x2},
	{0x0, 0x88, 0x0, 0x20, 0x0, 0x88, 0x0, 0x22},
	{0x0, 0x88, 0x0, 0x22, 0x0, 0x88, 0x0, 0x22},
	{0x0, 0x88, 0x0, 0xa2, 0x0, 0x88, 0x0, 0x22},
	{0x0, 0x88, 0x0, 0xa2, 0x0, 0x88, 0x0, 0x2a},
	{0x0, 0x88, 0x0, 0xa2, 0x0, 0x88, 0x0, 0xaa},
	{0x0, 0x88, 0x0, 0xaa, 0x0, 0x88, 0x0, 0xaa},
	{0x0, 0xa8, 0x0, 0xaa, 0x0, 0x88, 0x0, 0xaa},
	{0x0, 0xa8, 0x0, 0xaa, 0x0, 0x8a, 0x0, 0xaa},
	{0x0, 0xa8, 0x0, 0xaa, 0x0, 0xaa, 0x0, 0xaa},
	{0x0, 0xaa, 0x0, 0xaa, 0x0, 0xaa, 0x0, 0xaa},
	{0x40, 0xaa, 0x0, 0xaa, 0x0, 0xaa, 0x0, 0xaa},
	{0x40, 0xaa, 0x0, 0xaa, 0x4, 0xaa, 0x0, 0xaa},
	{0x40, 0xaa, 0x0, 0xaa, 0x44, 0xaa, 0x0, 0xaa},
	{0x44, 0xaa, 0x0, 0xaa, 0x44, 0xaa, 0x0, 0xaa},
	{0x44, 0xaa, 0x10, 0xaa, 0x44, 0xaa, 0x0, 0xaa},
	{0x44, 0xaa, 0x10, 0xaa, 0x44, 0xaa, 0x1, 0xaa},
	{0x44, 0xaa, 0x10, 0xaa, 0x44, 0xaa, 0x11, 0xaa},
	{0x44, 0xaa, 0x11, 0xaa, 0x44, 0xaa, 0x11, 0xaa},
	{0x44, 0xaa, 0x51, 0xaa, 0x44, 0xaa, 0x11, 0xaa},
	{0x44, 0xaa, 0x51, 0xaa, 0x44, 0xaa, 0x15, 0xaa},
	{0x44, 0xaa, 0x51, 0xaa, 0x44, 0xaa, 0x55, 0xaa},
	{0x44, 0xaa, 0x55, 0xaa, 0x44, 0xaa, 0x55, 0xaa},
	{0x54, 0xaa, 0x55, 0xaa, 0x44, 0xaa, 0x55, 0xaa},
	{0x54, 0xaa, 0x55, 0xaa, 0x45, 0xaa, 0x55, 0xaa},
	{0x54, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa},
	{0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa},
	{0xd5, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa},
	{0xd5, 0xaa, 0x55, 0xaa, 0x5d, 0xaa, 0x55, 0xaa},
	{0xd5, 0xaa, 0x55, 0xaa, 0xdd, 0xaa, 0x55, 0xaa},
	{0xdd, 0xaa, 0x55, 0xaa, 0xdd, 0xaa, 0x55, 0xaa},
	{0xdd, 0xaa, 0x75, 0xaa, 0xdd, 0xaa, 0x55, 0xaa},
	{0xdd, 0xaa, 0x75, 0xaa, 0xdd, 0xaa, 0x57, 0xaa},
	{0xdd, 0xaa, 0x75, 0xaa, 0xdd, 0xaa, 0x77, 0xaa},
	{0xdd, 0xaa, 0x77, 0xaa, 0xdd, 0xaa, 0x77, 0xaa},
	{0xdd, 0xaa, 0xf7, 0xaa, 0xdd, 0xaa, 0x77, 0xaa},
	{0xdd, 0xaa, 0xf7, 0xaa, 0xdd, 0xaa, 0x7f, 0xaa},
	{0xdd, 0xaa, 0xf7, 0xaa, 0xdd, 0xaa, 0xff, 0xaa},
	{0xdd, 0xaa, 0xff, 0xaa, 0xdd, 0xaa, 0xff, 0xaa},
	{0xfd, 0xaa, 0xff, 0xaa, 0xdd, 0xaa, 0xff, 0xaa},
	{0xfd, 0xaa, 0xff, 0xaa, 0xdf, 0xaa, 0xff, 0xaa},
	{0xfd, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa},
	{0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa},
	{0xff, 0xea, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa},
	{0xff, 0xea, 0xff, 0xaa, 0xff, 0xae, 0xff, 0xaa},
	{0xff, 0xea, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xaa},
	{0xff, 0xee, 0xff, 0xaa, 0xff, 0xee, 0xff, 0xaa},
	{0xff, 0xee, 0xff, 0xba, 0xff, 0xee, 0xff, 0xaa},
	{0xff, 0xee, 0xff, 0xba, 0xff, 0xee, 0xff, 0xab},
	{0xff, 0xee, 0xff, 0xba, 0xff, 0xee, 0xff, 0xbb},
	{0xff, 0xee, 0xff, 0xbb, 0xff, 0xee, 0xff, 0xbb},
	{0xff, 0xee, 0xff, 0xfb, 0xff, 0xee, 0xff, 0xbb},
	{0xff, 0xee, 0xff, 0xfb, 0xff, 0xee, 0xff, 0xbf},
	{0xff, 0xee, 0xff, 0xfb, 0xff, 0xee, 0xff, 0xff},
	{0xff, 0xee, 0xff, 0xff, 0xff, 0xee, 0xff, 0xff},
	{0xff, 0xfe, 0xff, 0xff, 0xff, 0xee, 0xff, 0xff},
	{0xff, 0xfe, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff},
	{0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
	{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
};


static const GLenum _hoops_GSGGC[2] = {GL_TEXTURE0_ARB, GL_TEXTURE1_ARB};




#include "ogl_vbo_tristrip.cpp"


/*****************************************************************************
 *****************************************************************************
						_hoops_RGAIA _hoops_PPR _hoops_IHRRR _hoops_IIRCI
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_PGAA
 */
local void
_hoops_RSGGC (unsigned short const _hoops_ASGGC[16],
					 GLubyte alter _hoops_PSGGC[128]) {
	Integer32 row;
	int i, j;

	for (i = 0, j = 0; i < 16; i++, j += 4) {

		row = _hoops_ASGGC[i];
		row = (row << 16) | row;

		*(_hoops_PSGGC +j +64 +0) = (unsigned char)(row & 0xff);
		*(_hoops_PSGGC +j     +0) = (unsigned char)(row & 0xff);

		row >>= 8;
		*(_hoops_PSGGC +j +64 +1) = (unsigned char)(row & 0xff);
		*(_hoops_PSGGC +j     +1) = (unsigned char)(row & 0xff);

		row >>= 8;
		*(_hoops_PSGGC +j +64 +2) = (unsigned char)(row & 0xff);
		*(_hoops_PSGGC +j     +2) = (unsigned char)(row & 0xff);

		row >>= 8;
		*(_hoops_PSGGC +j +64 +3) = (unsigned char)(row & 0xff);
		*(_hoops_PSGGC +j     +3) = (unsigned char)(row & 0xff);
	}
}


/*
 * _hoops_PGAA
 */
local void
_hoops_HSGGC (Display_Context alter * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	int i;

	HD_Get_Bit_Patterns (dc, true);
	for (i = 1; i < _hoops_CRPH; i++)
		_hoops_RSGGC (dc->_hoops_GRPH[i], _hoops_CSRGR->_hoops_SRPH[i]);
}




local void _hoops_ISGGC(float *v)
{
	float len = (float)sqrt((v[0]*v[0]) + (v[1]*v[1]) + (v[2]*v[2]));

	if (len > 0) {
		v[0] /= len;
		v[1] /= len;
		v[2] /= len;
	}
}

local void _hoops_CSGGC(float *r, const float *n, const float *l)
{
	float _hoops_SSGGC;

	_hoops_SSGGC = 2.0f * (n[0]*l[0] + n[1]*l[1] + n[2]*l[2]);
	r[0] = (_hoops_SSGGC * n[0]) - l[0];
	r[1] = (_hoops_SSGGC * n[1]) - l[1];
	r[2] = (_hoops_SSGGC * n[2]) - l[2];
}

local float _hoops_GGRGC(float *_hoops_ISPI, float *_hoops_CSPI)
{
	return (_hoops_ISPI[0]*_hoops_CSPI[0] + _hoops_ISPI[1]*_hoops_CSPI[1] + _hoops_ISPI[2]*_hoops_CSPI[2]);
}

/* _hoops_RGR _hoops_HICRR _hoops_API _hoops_SRIPA _hoops_RGRGC, _hoops_PHAII. */
local void _hoops_AGRGC(int i, int x, int y, int _hoops_PGRGC, float *v)
{
	float s, t, sc, tc;
	s = (0.5f + x) / _hoops_PGRGC;
	t = (0.5f + y) / _hoops_PGRGC;
	sc = 2.0f*s - 1;
	tc = 2.0f*t - 1;

	switch (i)
	{
		case 0:
			v[0] = 1;
			v[1] = -tc;
			v[2] = -sc;
			break;
		case 1:
			v[0] = -1;
			v[1] = -tc;
			v[2] = sc;
			break;
		case 2:
			v[0] = sc;
			v[1] = 1;
			v[2] = tc;
			break;
		case 3:
			v[0] = sc;
			v[1] = -1;
			v[2] = -tc;
			break;
		case 4:
			v[0] = sc;
			v[1] = -tc;
			v[2] = 1;
			break;
		case 5:
			v[0] = -sc;
			v[1] = -tc;
			v[2] = -1;
			break;
	}
	_hoops_ISGGC(v);
}


#ifndef GL_TEXTURE_WRAP_R
#define GL_TEXTURE_WRAP_R 0x8072
#endif
/* _hoops_RGR _hoops_HICRR _hoops_API _hoops_SHII _hoops_HII _hoops_GCGAH _hoops_HGRGC _hoops_IGRGC */
local void _hoops_CGRGC(int _hoops_SGRGC,
						  Net_Rendition const & nr,
						  _hoops_PC const &_hoops_HC,
						  _hoops_HHA const & matr)
{
	AGLM(OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);)
	float vector[3];
	float _hoops_GRRGC[3];
	float _hoops_RRRGC[3];
	float _hoops_IIPCR[3] = { 0, 0, 1 };
	float _hoops_ARRGC[3];
	float _hoops_ARGCR, spec, _hoops_PRRGC, _hoops_HRRGC;
	int i, x, y, _hoops_IRRGC;
	float *pixels;
	_hoops_AS const *light;
	_hoops_HRPA _hoops_CRRGC;

	/* _hoops_IPS _hoops_RH _hoops_SARA _hoops_RIHCR _hoops_RSGA _hoops_HIS _hoops_SR _hoops_PAH _hoops_GRPHA _hoops_RH _hoops_SRRGC _hoops_IGPC */
	HI_Copy_43(&nr->transform_rendition->_hoops_SPH->_hoops_PRPA.elements[0][0],
				&_hoops_CRRGC.elements[0][0]);
	_hoops_CRRGC.elements[3][0] = 0;
	_hoops_CRRGC.elements[3][1] = 0;
	_hoops_CRRGC.elements[3][2] = 0;

	ALLOC_ARRAY(pixels, _hoops_SGRGC * _hoops_SGRGC * 3, float);

	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	_hoops_PRRGC = 4.0f * matr->gloss;
	for (i = 0; i < 6; i++) {
		memset(pixels, 0, 3 * _hoops_SGRGC * _hoops_SGRGC * sizeof(float));
		light = _hoops_HC->_hoops_CGR;
		while (light != null) {
			_hoops_ARRGC[0] = light->color.red;
			_hoops_ARRGC[1] = light->color.green;
			_hoops_ARRGC[2] = light->color.blue;
			_hoops_GRRGC[0] = _hoops_HPRA (_hoops_CRRGC.elements, light->direction);
			_hoops_GRRGC[1] = _hoops_IPRA (_hoops_CRRGC.elements, light->direction);
			_hoops_GRRGC[2] = -_hoops_CPRA (_hoops_CRRGC.elements, light->direction);
			_hoops_ISGGC(_hoops_GRRGC);
			for (y = 0; y < _hoops_SGRGC; y++) {
				for (x = 0; x < _hoops_SGRGC; x++) {
					_hoops_IRRGC = (y * _hoops_SGRGC + x) * 3;
					_hoops_AGRGC(i, x, y, _hoops_SGRGC, vector);
					_hoops_CSGGC(_hoops_RRRGC, vector, _hoops_GRRGC);
					spec = _hoops_GGRGC(_hoops_IIPCR,_hoops_RRRGC);
					_hoops_ARGCR = _hoops_GGRGC(vector,_hoops_GRRGC);
					if ((_hoops_ARGCR > 0) && (spec > 0)) {
						/* _hoops_RCGRA _hoops_IS _hoops_GARGC = _hoops_RARGC(_hoops_GARGC, _hoops_AARGC); */
						_hoops_HRRGC = (float)exp(_hoops_PRRGC * log(spec));
						pixels[_hoops_IRRGC]		+= _hoops_ARRGC[0] * _hoops_HRRGC;
						pixels[_hoops_IRRGC + 1] += _hoops_ARRGC[1] * _hoops_HRRGC;
						pixels[_hoops_IRRGC + 2] += _hoops_ARRGC[2] * _hoops_HRRGC;
					}
				}
			}
			light = light->next;
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB+i,
						0,
						GL_RGB8,
						_hoops_SGRGC,
						_hoops_SGRGC,
						0,
						GL_RGB,
						GL_FLOAT,
						pixels);
		_hoops_GPRH(_hoops_RPRH)++;
	}
	/* _hoops_CIH _hoops_GH _hoops_RH _hoops_AIR _hoops_SRHR */
	FREE_ARRAY(pixels, _hoops_SGRGC * _hoops_SGRGC * 3, float);

} /* _hoops_RSGR _hoops_API _hoops_PARGC */


#define CUBE_MAP_SIZE 32
local bool _hoops_HARGC(Net_Rendition const & nr,
				  _hoops_PC const & _hoops_HC,
				  _hoops_HHA const & matr)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
#if 1
	/*_hoops_ASIGA _hoops_RGHH _hoops_GISR _hoops_SS */
	_hoops_AS const *light;
#endif

	if (!_hoops_CSRGR->_hoops_IARGC)
		return false;

	if (nr->transform_rendition->_hoops_SPH == _hoops_CSRGR->_hoops_CSC._hoops_HAACP._hoops_CARGC &&
		_hoops_CSRGR->_hoops_IARRR == _hoops_HC->_hoops_CPA &&
		matr->gloss == _hoops_CSRGR->_hoops_CSC._hoops_HAACP.gloss) {
		if (_hoops_CSRGR->_hoops_SARGC == _hoops_GPRGC)
			return false;
		if (_hoops_CSRGR->_hoops_SARGC != _hoops_RPRGC) {
			_hoops_APRGC (_hoops_CSRGR, nr, _hoops_HC);
			_hoops_PPRGC(_hoops_CSRGR, 1);
			glEnable(GL_TEXTURE_CUBE_MAP_ARB);
			_hoops_PPRGC(_hoops_CSRGR, 0);
		}
		return true;
	}

	/* _hoops_CAH _hoops_ISPR
	 * _hoops_PS _hoops_PAH _hoops_RGHH _hoops_GII _hoops_PHI _hoops_IIGR _hoops_SS, _hoops_HIH _hoops_SSIA _hoops_PIHA _hoops_HCR _hoops_SHH _hoops_RSSR */
#if 1
	/*_hoops_ASIGA _hoops_RGHH _hoops_GISR _hoops_SS */
	light = _hoops_HC->_hoops_CGR;
	while (light != null) {
		if (light->_hoops_PRR != _hoops_H) {
			_hoops_CSRGR->_hoops_SARGC = _hoops_GPRGC;
			return false;
		}
		light = light->next;
	}
#endif

	_hoops_PPRGC(_hoops_CSRGR, 1);
	if (_hoops_CSRGR->_hoops_CSC._hoops_HAACP._hoops_HPRGC == _hoops_RSARR)
		OGL_ALLOC_TEXTURE(_hoops_CSRGR->_hoops_CSC._hoops_HAACP._hoops_HPRGC);
	_hoops_IPRGC (_hoops_CSRGR, 1, GL_TEXTURE_CUBE_MAP_ARB, _hoops_CSRGR->_hoops_CSC._hoops_HAACP._hoops_HPRGC);
	_hoops_CGRGC(CUBE_MAP_SIZE, nr, _hoops_HC, matr);
	glEnable(GL_TEXTURE_CUBE_MAP_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_ARB);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_ARB);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_ARB);
	_hoops_PPRGC(_hoops_CSRGR, 0);

	_hoops_CSRGR->_hoops_CSC._hoops_HAACP._hoops_CARGC = nr->transform_rendition->_hoops_SPH;
	_hoops_CSRGR->_hoops_CSC._hoops_HAACP.gloss = matr->gloss;

	/* _hoops_SR _hoops_SGH _hoops_HPRGR _hoops_PPIC _hoops_SS _hoops_IH _hoops_CPS _hoops_HIH _hoops_GHI */
	_hoops_APRGC (_hoops_CSRGR, nr, _hoops_HC);
	return true;
}


local void _hoops_CPRGC(OGLData alter * _hoops_CSRGR) {
	_hoops_PPRGC(_hoops_CSRGR, 1);
	glDisable(GL_TEXTURE_CUBE_MAP_ARB);
	_hoops_PPRGC(_hoops_CSRGR, 0);
}


local void _hoops_SPRGC(OGLData alter * _hoops_CSRGR) {
	_hoops_PPRGC(_hoops_CSRGR, 1);
	glEnable(GL_TEXTURE_CUBE_MAP_ARB);
	_hoops_PPRGC(_hoops_CSRGR, 0);
}


/*
 * _hoops_PGAA
 */
local void
_hoops_GHRGC (OGLData alter * _hoops_CSRGR) {
	if (_hoops_CSRGR->_hoops_SARGC != _hoops_RHRGC) {
		glDisable (GL_LIGHTING);
		ENSURE_MATERIAL_COLOR_OFF (_hoops_CSRGR);
		if (_hoops_CSRGR->_hoops_SARGC == _hoops_RPRGC)
			_hoops_CPRGC(_hoops_CSRGR);
		_hoops_CSRGR->_hoops_SARGC = _hoops_RHRGC;
	}
}


/*
 * _hoops_PGAA
 */
#ifndef _hoops_IACIR
# define _hoops_IACIR (1e10f)
#endif
local void
_hoops_AHRGC (OGLData alter * _hoops_CSRGR,
				Net_Rendition const & nr,
				_hoops_PC const & _hoops_HC) {
	int i;
	_hoops_GRGH const &	_hoops_RRGH = nr->_hoops_IRR;
	_hoops_AS const *	light;
	GLfloat _hoops_PHRGC[4];
	bool _hoops_HHRGC = false;
	GLfloat _hoops_HGSAI[4] = {0, 0, 0, 0};

	if (_hoops_CSRGR->_hoops_SARGC == _hoops_RPRGC)
		_hoops_CPRGC(_hoops_CSRGR);

	if (_hoops_HC == null) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Lighting requested, but there are no lights.");
		return;
	}

	/* _hoops_AGSGR _hoops_PSAP _hoops_SS _hoops_IHRGC _hoops_SR _hoops_AGRP _hoops_CAPR */
	glDisable (GL_LIGHTING);

	for (i = 0; i < _hoops_CSRGR->_hoops_CHRGC; i++) {
		if (i > _hoops_CSRGR->_hoops_SHRGC) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Turned off invalid light!");
			break;
		}
		glDisable (GL_LIGHT0 + i);
		if (_hoops_CSRGR->_hoops_GIRGC[i]) {
			if (_hoops_CSRGR->_hoops_RIRGC ||
				_hoops_CSRGR->_hoops_AIRGC) {
				/* _hoops_PHIH _hoops_RH _hoops_AISR-_hoops_IPPAR _hoops_HRP _hoops_IS _hoops_RH _hoops_HSSHH
				 * _hoops_GAR _hoops_HRARH _hoops_GGR _hoops_PIRGC _hoops_PHSAR _hoops_ACISR */
				_hoops_PHRGC[0] = 0; _hoops_PHRGC[1] = 0; _hoops_PHRGC[2] = -1;
				glLightfv (GL_LIGHT0 + i, GL_SPOT_DIRECTION, _hoops_PHRGC);
				_hoops_PHRGC[0] = 0; _hoops_PHRGC[1] = 0; _hoops_PHRGC[2] = 1; _hoops_PHRGC[3] = 0;
				glLightfv (GL_LIGHT0 + i, GL_POSITION, _hoops_PHRGC);
				glLightf (GL_LIGHT0 + i, GL_SPOT_EXPONENT, 0);
				glLightf (GL_LIGHT0 + i, GL_SPOT_CUTOFF, 180);
				_hoops_CSRGR->_hoops_GIRGC[i] = false;
			}
		}
	}

	/* _hoops_HGSR _hoops_RH _hoops_RCA _hoops_SARR _hoops_IH _hoops_HCR _hoops_SS */
	if (!_hoops_HIRGC (_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC, _hoops_RRGH->_hoops_HASR)) {

		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.red = _hoops_PHRGC[0] = _hoops_RRGH->_hoops_HASR.red;
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.green = _hoops_PHRGC[1] = _hoops_RRGH->_hoops_HASR.green;
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.blue = _hoops_PHRGC[2] = _hoops_RRGH->_hoops_HASR.blue;
		_hoops_PHRGC[3] = 1.0;	/* _hoops_AIIR _hoops_RCAP == _hoops_PPRGR */
		glLightModelfv (GL_LIGHT_MODEL_AMBIENT, _hoops_PHRGC);
	}


	ENSURE_LOCAL_VIEWER(_hoops_CSRGR, BIT (_hoops_RRGH->_hoops_PPH, Rendo_LOCAL_VIEWER));

	/*
	 * _hoops_SIIR _hoops_RH _hoops_GGSP _hoops_RCA _hoops_AHC _hoops_RSGA, _hoops_PGAP _hoops_IH _hoops_AGAH _hoops_SSCP _hoops_AIAH _hoops_RIAGR
	 * _hoops_HCR _hoops_PRGIA _hoops_HCIA _hoops_SGGA.	_hoops_PHGP _hoops_HCR _hoops_SR _hoops_RRP _hoops_HRGR _hoops_RH _hoops_HAPRR _hoops_IS _hoops_RHC _hoops_GC.
	 */
	if (!_hoops_CSRGR->_hoops_IICH) {
		glPushMatrix ();
		glLoadMatrixf (_hoops_CSRGR->_hoops_CIRGC);
	}

	/* _hoops_HGSR _hoops_GRR _hoops_RRR */
	i = 0;
	if ((light = _hoops_HC->_hoops_CGR) != null) {
		do {
			GLenum gl_light = GL_LIGHT0 + i;

			/* _hoops_HGSR _hoops_RRR _hoops_HAIR, _hoops_PIP _hoops_PSP _hoops_AASR _hoops_HAIR, _hoops_SGH _hoops_HRSAR _hoops_AASR _hoops_RGAR */
			_hoops_PHRGC[0] = light->_hoops_HASR.red;
			_hoops_PHRGC[1] = light->_hoops_HASR.green;
			_hoops_PHRGC[2] = light->_hoops_HASR.blue;
			_hoops_PHRGC[3] = 1.0;
			glLightfv (gl_light, GL_AMBIENT, _hoops_PHRGC);

			_hoops_PHRGC[0] = light->color.red;
			_hoops_PHRGC[1] = light->color.green;
			_hoops_PHRGC[2] = light->color.blue;
			_hoops_PHRGC[3] = 1.0;
			glLightfv (gl_light, GL_DIFFUSE, _hoops_PHRGC);

			if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA)) {
				glLightfv (gl_light, GL_SPECULAR, _hoops_HGSAI);
			}
			else
				glLightfv (gl_light, GL_SPECULAR, _hoops_PHRGC);

			/* _hoops_GISR _hoops_SS _hoops_SIRGC _hoops_SAHR _hoops_PII _hoops_PPSR _hoops_SS _hoops_HIH _hoops_CCA _hoops_IRS _hoops_HH _hoops_IS _hoops_ASAGI
			 * _hoops_CAPR _hoops_SIPP _hoops_RH _hoops_GCRGC */
			if (light->_hoops_PRR == _hoops_I) {
				if (_hoops_CSRGR->_hoops_RIRGC ||
					_hoops_CSRGR->_hoops_AIRGC) {
					_hoops_PHRGC[0] = light->position.x;
					_hoops_PHRGC[1] = light->position.y;
					_hoops_PHRGC[2] = light->position.z;
					_hoops_PHRGC[3] = 1.0f;
					glLightfv (gl_light, GL_POSITION, _hoops_PHRGC);
					glLightf (gl_light, GL_SPOT_EXPONENT, light->_hoops_CCSGP);
					glLightf (gl_light, GL_SPOT_CUTOFF, light->_hoops_HCSR);
					_hoops_PHRGC[0] = light->direction.x;
					_hoops_PHRGC[1] = light->direction.y;
					_hoops_PHRGC[2] = light->direction.z;
					_hoops_PHRGC[3] = 0.0f;
					glLightfv (gl_light, GL_SPOT_DIRECTION, _hoops_PHRGC);
					_hoops_CSRGR->_hoops_GIRGC[i] = true;
				}
				else {
					continue;
				}
			}
			else if (light->_hoops_PRR == _hoops_C) {

				_hoops_PHRGC[0] = light->position.x;
				_hoops_PHRGC[1] = light->position.y;
				_hoops_PHRGC[2] = light->position.z;
				_hoops_PHRGC[3] = 1.0f;
				glLightfv (gl_light, GL_POSITION, _hoops_PHRGC);
			}
			else if (_hoops_HHRGC) {
				/* _hoops_RCRGC _hoops_RSSR _hoops_RRR */
				_hoops_PHRGC[0] = light->direction.x * _hoops_IACIR;
				_hoops_PHRGC[1] = light->direction.y * _hoops_IACIR;
				_hoops_PHRGC[2] = light->direction.z * _hoops_IACIR;
				_hoops_PHRGC[3] = 1.0f;
				glLightfv (gl_light, GL_POSITION, _hoops_PHRGC);
			}
			else {
				/* _hoops_ACRGC _hoops_RSSR _hoops_RRR (_hoops_SSCHA = 0 _hoops_AGSR _hoops_HAGA _hoops_AAGA) */
				_hoops_PHRGC[0] = light->direction.x;
				_hoops_PHRGC[1] = light->direction.y;
				_hoops_PHRGC[2] = light->direction.z;
				_hoops_PHRGC[3] = 0.0f;
				glLightfv (gl_light, GL_POSITION, _hoops_PHRGC);
			}
			i++;
			if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_MULTILIGHT))
				_hoops_HHRGC = true;
			/* _hoops_HCAGR, _hoops_AAPA _hoops_PAPA _hoops_GRS _hoops_CRHR _hoops_RGR _hoops_HII _hoops_CCHCP _hoops_HPP _hoops_PCRGC _hoops_RGR _hoops_AGIR
			 * _hoops_PPR _hoops_GHGA _hoops_RH _hoops_RPIC _hoops_ACAS, _hoops_HIH _hoops_SCH _hoops_PAH _hoops_RCPS _hoops_GH _hoops_GGR _hoops_HHH _hoops_RAGII _hoops_ARAR _hoops_SGS _hoops_SR **_hoops_PIHA**
			 * _hoops_AA _hoops_RCA _hoops_GGR _hoops_GSIA */
			if (i >= _hoops_CSRGR->_hoops_SHRGC)
				break;
		} _hoops_RGGA ((light = light->next) == null);
	}

	_hoops_CSRGR->_hoops_CHRGC = i;

	if (!_hoops_CSRGR->_hoops_IICH) {
		glPopMatrix ();
	}

	/* _hoops_AGSGR _hoops_GPP _hoops_SS */
	for (i=0; i <_hoops_CSRGR->_hoops_CHRGC; i++)
		glEnable (GL_LIGHT0 + i);

	glEnable (GL_LIGHTING);
}



/*
 * _hoops_PGAA
 */
local void
_hoops_HCRGC (OGLData alter * _hoops_CSRGR,
				_hoops_AS const *light)
{
	int i;
	GLfloat _hoops_PHRGC[4];
	GLfloat _hoops_HGSAI[4] = {0, 0, 0, 0};

	/* _hoops_AGSGR _hoops_PSAP _hoops_SS _hoops_IHRGC _hoops_SR _hoops_AGRP _hoops_CAPR */
	glDisable (GL_LIGHTING);
	if (_hoops_CSRGR->_hoops_SARGC == _hoops_RPRGC)
		_hoops_CPRGC(_hoops_CSRGR);

	for (i = 0; i < _hoops_CSRGR->_hoops_CHRGC; i++)
		glDisable (GL_LIGHT0 + i);
	/*
	 * _hoops_SIIR _hoops_RH _hoops_GGSP _hoops_RCA _hoops_AHC _hoops_RSGA, _hoops_PGAP _hoops_IH _hoops_AGAH _hoops_SSCP _hoops_AIAH _hoops_RIAGR
	 * _hoops_HCR _hoops_PRGIA _hoops_HCIA _hoops_SGGA.	_hoops_PHGP _hoops_HCR _hoops_SR _hoops_RRP _hoops_HRGR _hoops_RH _hoops_HAPRR _hoops_IS _hoops_RHC _hoops_GC.
	 */
	if (!_hoops_CSRGR->_hoops_IICH) {
		glPushMatrix ();
		glLoadMatrixf (_hoops_CSRGR->_hoops_CIRGC);
	}
	_hoops_PHRGC[0] = light->position.x;
	_hoops_PHRGC[1] = light->position.y;
	_hoops_PHRGC[2] = light->position.z;
	_hoops_PHRGC[3] = 1.0f;
	glLightfv (GL_LIGHT0, GL_POSITION, _hoops_PHRGC);

	_hoops_PHRGC[0] = light->color.red;
	_hoops_PHRGC[1] = light->color.green;
	_hoops_PHRGC[2] = light->color.blue;
	_hoops_PHRGC[3] = 1;
	glLightfv (GL_LIGHT0, GL_DIFFUSE, _hoops_PHRGC);
	glLightfv (GL_LIGHT0, GL_SPECULAR, _hoops_PHRGC);

	if (!_hoops_CSRGR->_hoops_IICH) {
		glPopMatrix ();
	}
	glEnable (GL_LIGHT0);
	glEnable (GL_LIGHTING);
	_hoops_CSRGR->_hoops_CHRGC = 1;
	_hoops_CSRGR->_hoops_SARGC = _hoops_ICRGC;

	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.red =
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.green =
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.blue = 0;
	glLightModelfv (GL_LIGHT_MODEL_AMBIENT, _hoops_HGSAI);
}


/*
 * _hoops_IHRAH - _hoops_IAGP _hoops_RACGH
 */

local void * _hoops_GRSSP (
	Net_Rendition const &nr,
	bool				disable_write) {
	OGLData alter *			_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	GLuint					id;

	ENSURE_TRANSPARENCY(_hoops_CSRGR, false);

	if (disable_write) {
		glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		ENSURE_DEPTH_MASK(_hoops_CSRGR, GL_FALSE);
	}

	(*_hoops_CSRGR->glGenQueries) (1, &id);
	if (_hoops_CSRGR->glBeginQueryARB)
		(*_hoops_CSRGR->glBeginQueryARB) (GL_SAMPLES_PASSED_ARB, id);
	else
		(*_hoops_CSRGR->glBeginOcclusionQueryNV) (id);

	return (void *)(POINTER_SIZED_INT)id;
}

local void _hoops_RRSSP (
	Net_Rendition const &nr,
	void *					_hoops_HACGH) {
	OGLData alter *			_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	UNREFERENCED(_hoops_HACGH);

	if (_hoops_CSRGR->glEndQueryARB != null)
		(*_hoops_CSRGR->glEndQueryARB) (GL_SAMPLES_PASSED_ARB);
	else
		(*_hoops_CSRGR->glEndOcclusionQueryNV) ();

	glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	ENSURE_DEPTH_MASK(_hoops_CSRGR, GL_TRUE);

	_hoops_CSRGR->_hoops_CCRGC = true;
}

local int _hoops_CRGIP (
	Net_Rendition const &nr,
	void *					_hoops_HACGH) {
	OGLData alter *			_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	GLuint					id = (GLuint)(POINTER_SIZED_INT)_hoops_HACGH;
	GLuint					value=0;

	if (_hoops_CSRGR->_hoops_CCRGC) {
		glFlush();
		_hoops_CSRGR->_hoops_CCRGC = false;
	}

	_hoops_GPRH(_hoops_IHRGH)++;

	/* _hoops_SCRGC _hoops_PAPR _hoops_SCH _hoops_GAR _hoops_GSRGC _hoops_AGIRR _hoops_RSRGC _hoops_PAPR _hoops_SCH _hoops_GAR
	 * _hoops_ASRGC, _hoops_HIH _hoops_GAR _hoops_SGIP _hoops_GAR _hoops_GHAP _hoops_PAH _hoops_CRGS, _hoops_SCH _hoops_RHCI _hoops_IS _hoops_RH
	 * _hoops_PSHR _hoops_HSSSR _hoops_PIRA */
	ASSERT (GL_QUERY_RESULT_AVAILABLE_ARB == GL_PIXEL_COUNT_AVAILABLE_NV);
	while (1) {
		(*_hoops_CSRGR->glGetQueryObjectuiv) (id, GL_QUERY_RESULT_AVAILABLE_ARB, &value);
		if (value)
			break;
	}
	if (value)
		(*_hoops_CSRGR->glGetQueryObjectuiv) (id, GL_QUERY_RESULT_ARB, &value);
	else
		value = ~0U;

	(*_hoops_CSRGR->glDeleteQueries) (1, &id);

	return value;
}


local void _hoops_ARSSP (
	Net_Rendition const &nr,
	void *					_hoops_HACGH) {
	OGLData alter *			_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	GLuint					id = (GLuint)(POINTER_SIZED_INT)_hoops_HACGH;

	(*_hoops_CSRGR->glDeleteQueries) (1, &id);
}


#ifdef _hoops_PSRGC
local void fence (
	Net_Rendition const &nr)
{
	OGLData alter *			_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	POINTER_SIZED_INT		id;

	if (_hoops_CSRGR->_hoops_HSRGC != -1) {
		id = _hoops_CSRGR->_hoops_ISRGC[_hoops_CSRGR->_hoops_HSRGC];
		_hoops_CRGIP (nr, I2V(id));
	}
	_hoops_CSRGR->_hoops_HSRGC = !_hoops_CSRGR->_hoops_HSRGC;
	_hoops_CSRGR->_hoops_CSRGC = _hoops_SSRGC;
	id = V2I(_hoops_GRSSP (nr, 0));
	_hoops_RRSSP (nr, I2V(id));
	_hoops_CSRGR->_hoops_ISRGC[_hoops_CSRGR->_hoops_HSRGC];
}
#endif


/*
 * _hoops_PGAA
 */
local void
invalidate_cache (OGLData alter * _hoops_CSRGR)
{
	int i;

	_hoops_CSRGR->_hoops_HCAC = _hoops_CCC;
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_CSRGR->_hoops_IARRR = _hoops_CCC;
	_hoops_CSRGR->_hoops_ICAC = _hoops_CCC;
	_hoops_CSRGR->_hoops_SARRR = _hoops_CCC;
	_hoops_CSRGR->_hoops_RSHH = _hoops_CCC;
	_hoops_CSRGR->_hoops_GPRRR = _hoops_CCC;

	_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;
	_hoops_CSRGR->_hoops_CSC._hoops_GPIR = _hoops_CAHSR::_hoops_SAHSR;
	_hoops_CSRGR->_hoops_CSC._hoops_CRIA = _hoops_RSARR;
	_hoops_CSRGR->_hoops_CSC.line_style = null;
	_hoops_CSRGR->_hoops_CSC.line_weight = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_GGAGC = DRAW_MODE_NORMAL;
	_hoops_CSRGR->_hoops_CSC._hoops_RGAGC = false;

	_hoops_CSRGR->_hoops_AGAGC = _hoops_RSARR;

	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.red = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.green = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.blue = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.red = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.green = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.blue = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.alpha = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_SGC.red = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_SGC.green = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_SGC.blue = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IRC.red = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IRC.green = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IRC.blue = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_HGAGC = -1.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_IGAGC = _hoops_CSRGR->_hoops_CSC._hoops_ISHIR;
	_hoops_CSRGR->_hoops_CSC._hoops_CGAGC = _hoops_RSARR;

	for (i = 0; i < OGL_MAX_TEXTURE_UNITS; i++)
		_hoops_CSRGR->_hoops_CSC._hoops_SGAGC[i] = _hoops_RSARR;

	/*_hoops_GRAGC _hoops_ACGPA _hoops_HGAPR _hoops_RRAGC _hoops_IGPIP _hoops_AIIRI _hoops_ARAGC _hoops_RAIGR _hoops_HRPAH
	 * _hoops_GHAP'_hoops_RPRAR _hoops_PRAGC _hoops_IGPIP _hoops_HRAGC _hoops_RAIGR _hoops_IRAGC _hoops_GGHIP _hoops_CRAGC
	_hoops_HGPGA->_hoops_IHAH._hoops_SRAGC = _hoops_GAAGC;
	_hoops_HGPGA->_hoops_IHAH._hoops_RAHCP._hoops_RAAGC = _hoops_GAAGC;
	*/
	_hoops_CSRGR->_hoops_CSC._hoops_AAAGC = (Named_Material *) 0;

	_hoops_APSS(_hoops_CSRGR,0);
	_hoops_APSS(_hoops_CSRGR,1);
	(_hoops_CSRGR)->_hoops_CSC._hoops_PAAGC[0] = _hoops_RSARR;
	(_hoops_CSRGR)->_hoops_CSC._hoops_HAAGC[0] = _hoops_RSARR;
	(_hoops_CSRGR)->_hoops_CSC._hoops_IAAGC[0] = _hoops_RSARR;
	(_hoops_CSRGR)->_hoops_CSC._hoops_PAAGC[1] = _hoops_RSARR;
	(_hoops_CSRGR)->_hoops_CSC._hoops_HAAGC[1] = _hoops_RSARR;
	(_hoops_CSRGR)->_hoops_CSC._hoops_IAAGC[1] = _hoops_RSARR;
	_hoops_RCPRR(_hoops_CSRGR);
	_hoops_CAAGC(_hoops_CSRGR);

	/* _hoops_HRCI _hoops_RH _hoops_HIHP _hoops_IHAH _hoops_HPHS */
	_hoops_CSRGR->_hoops_CARGC = null;
	_hoops_CSRGR->_hoops_SAAGC = 0.0f;
	_hoops_CSRGR->_hoops_CSIH = 0;
	_hoops_CSRGR->_hoops_IIIH = -1;
	_hoops_CSRGR->_hoops_SIIH = -1;
	_hoops_CSRGR->_hoops_GPAGC = -1;
	_hoops_CSRGR->_hoops_RPAGC = -1;
	_hoops_CSRGR->_hoops_APAGC = _hoops_CCC;
	_hoops_CSRGR->_hoops_CSC._hoops_GSCH[0] = _hoops_CSRGR->_hoops_CSC._hoops_GSCH[1] = -1.0f;

	_hoops_CSRGR->_hoops_PPAGC = false;
	_hoops_CSRGR->_hoops_CSC._hoops_HPAGC = _hoops_RSARR;
	_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = false;
	_hoops_CSRGR->_hoops_CSC._hoops_CPAGC = _hoops_RSARR;
	_hoops_CSRGR->_hoops_CSC._hoops_SPAGC = _hoops_RSARR;
	_hoops_CSRGR->_hoops_CSC._hoops_GHAGC = _hoops_RSARR;
	_hoops_CSRGR->_hoops_CSC._hoops_AAIH = GL_FALSE;/*_hoops_HCR _hoops_SGH _hoops_HHSA _hoops_GGR _hoops_RH _hoops_IHPI*/
}



#define _hoops_RHAGC(x) \
	((strstr((char *) extensions, x) == 0) ? false : true)

#if defined(_hoops_PPCSH) || defined(IRIX_SYSTEM) || defined(AIX_SYSTEM) || defined(SOLARIS_SYSTEM) || defined(HPUX_SYSTEM)
#define _hoops_AHAGC
#endif

#if 0
#if defined(LINUX_SYSTEM)
#ifdef _LP64
#define _hoops_AHAGC
#endif
#endif
#endif

#if defined(NUTCRACKER)
#define _hoops_AHAGC
#endif

#ifdef _hoops_AHAGC
#  define GetProcAddress(_hoops_SCPGA) (void *)0
#elif defined(GLX_DRIVER)
#ifdef _hoops_PHAGC
typedef void (*GLfunction)();
extern GLfunction glXGetProcAddressARB (GLubyte *);
#endif
#if !defined(GLX_VERSION_1_4)
#  define GetProcAddress(_hoops_SCPGA) glXGetProcAddressARB((GLubyte *)_hoops_SCPGA)
#else
#  define GetProcAddress(_hoops_SCPGA) glXGetProcAddress((GLubyte *)_hoops_SCPGA)
#endif
#elif defined(WGL_DRIVER)
#  define GetProcAddress(_hoops_SCPGA) wglGetProcAddress(_hoops_SCPGA)
#elif defined(AGL_DRIVER)
#  define GetProcAddress(_hoops_SCPGA) MyAGLGetProcAddress(_hoops_SCPGA);
#elif defined(COCOA_OGL_DRIVER)
#  define GetProcAddress(_hoops_SCPGA) _hoops_CCPGA(_hoops_SCPGA);
#endif

local void _hoops_RHH (Display_Context alter *	dc);

#ifdef _hoops_HHAGC

local void _hoops_IHAGC(OGLData alter * _hoops_CSRGR)
{

#ifdef DEBUG_FBO
	fprintf(stderr,"common_cleanup_fbo\n");
#endif

	if (_hoops_CSRGR->_hoops_CHAGC) {
#ifdef DEBUG_FBO
		fprintf(stderr,"cleaning up fbo_color_tex\n");
#endif
		glDeleteTextures(1, &_hoops_CSRGR->_hoops_CHAGC);
	}

	if (_hoops_CSRGR->_hoops_SHAGC) {
#ifdef DEBUG_FBO
		fprintf(stderr,"cleaning up fbo_depth_stencil_rb\n");
#endif
		_hoops_CSRGR->_glDeleteRenderbuffersEXT(1, &_hoops_CSRGR->_hoops_SHAGC);
	}

	if (_hoops_CSRGR->_hoops_GIAGC) {
#ifdef DEBUG_FBO
		fprintf(stderr,"cleaning up fbo_depth_rb\n");
#endif
		_hoops_CSRGR->_glDeleteRenderbuffersEXT(1, &_hoops_CSRGR->_hoops_GIAGC);
	}

	if (_hoops_CSRGR->_hoops_RIAGC) {
#ifdef DEBUG_FBO
		fprintf(stderr,"cleaning up fbo_fb\n");
#endif
		_hoops_CSRGR->_hoops_AIAGC(1, &_hoops_CSRGR->_hoops_RIAGC);
	}

	_hoops_CSRGR->_hoops_CHAGC = 0;
	_hoops_CSRGR->_hoops_SHAGC = 0;
	_hoops_CSRGR->_hoops_GIAGC = 0;
	_hoops_CSRGR->_hoops_RIAGC = 0;
}

local bool _hoops_PIAGC(OGLData alter * _hoops_CSRGR)
{
	GLenum status;

#ifdef DEBUG_FBO
	fprintf(stderr,"common_make_fbo_current\n");
#endif

	_hoops_CSRGR->_hoops_HIAGC(GL_FRAMEBUFFER_EXT, _hoops_CSRGR->_hoops_RIAGC);

	status = _hoops_CSRGR->_hoops_IIAGC(GL_FRAMEBUFFER_EXT);

	switch (status) {
		case GL_FRAMEBUFFER_COMPLETE_EXT:
#ifdef DEBUG_FBO
			fprintf(stderr,"GL_FRAMEBUFFER_COMPLETE_EXT\n");
#endif
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
#ifdef DEBUG_FBO
			fprintf(stderr,"GL_FRAMEBUFFER_UNSUPPORTED_EXT\n");
#endif
			goto _hoops_CIAGC;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
#ifdef DEBUG_FBO
			fprintf(stderr,"GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT\n");
#endif
			goto _hoops_CIAGC;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
#ifdef DEBUG_FBO
			fprintf(stderr,"GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT\n");
#endif
			goto _hoops_CIAGC;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT:
#ifdef DEBUG_FBO
			fprintf(stderr,"GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT\n");
#endif
			goto _hoops_CIAGC;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
#ifdef DEBUG_FBO
			fprintf(stderr,"GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT\n");
#endif
			goto _hoops_CIAGC;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
#ifdef DEBUG_FBO
			fprintf(stderr,"GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT\n");
#endif
			goto _hoops_CIAGC;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
#ifdef DEBUG_FBO
			fprintf(stderr,"GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT\n");
#endif
			goto _hoops_CIAGC;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
#ifdef DEBUG_FBO
			fprintf(stderr,"GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT\n");
#endif
			goto _hoops_CIAGC;
			break;
		default:
#ifdef DEBUG_FBO
			fprintf(stderr,"UNKNOWN FBO ERROR %x\n", status);
#endif
			goto _hoops_CIAGC;
			break;
	}

	return true;

_hoops_CIAGC:

	return false;
}

local bool _hoops_SIAGC(OGLData alter * _hoops_CSRGR, bool _hoops_GCAGC)
{
	char const *extensions;

	extensions = (char const *) glGetString (GL_EXTENSIONS);

	if (!extensions)
		extensions = "";

	_hoops_CSRGR->_hoops_RCAGC = _hoops_RHAGC("GL_EXT_framebuffer_object");
	if (_hoops_CSRGR->_hoops_RCAGC) {

		_hoops_CSRGR->_glIsRenderbufferEXT = (glIsRenderbufferEXTProc) GetProcAddress ("glIsRenderbufferEXT");
		_hoops_CSRGR->_hoops_ACAGC = (glBindRenderbufferEXTProc) GetProcAddress("glBindRenderbufferEXT");
		_hoops_CSRGR->_glDeleteRenderbuffersEXT = (glDeleteRenderbuffersEXTProc) GetProcAddress("glDeleteRenderbuffersEXT");
		_hoops_CSRGR->_hoops_PCAGC = (glGenRenderbuffersEXTProc) GetProcAddress("glGenRenderbuffersEXT");
		_hoops_CSRGR->_hoops_HCAGC = (glRenderbufferStorageEXTProc) GetProcAddress("glRenderbufferStorageEXT");
		_hoops_CSRGR->glGetRenderbufferParameterivEXT = (glGetRenderbufferParameterivEXTProc) GetProcAddress("glGetRenderbufferParameterivEXT");

		_hoops_CSRGR->_hoops_ICAGC = (glIsFramebufferEXTProc) GetProcAddress("glIsFramebufferEXT");
		_hoops_CSRGR->_hoops_HIAGC = (glBindFramebufferEXTProc) GetProcAddress("glBindFramebufferEXT");
		_hoops_CSRGR->_hoops_AIAGC = (glDeleteFramebuffersEXTProc) GetProcAddress("glDeleteFramebuffersEXT");
		_hoops_CSRGR->_hoops_CCAGC = (glGenFramebuffersEXTProc) GetProcAddress("glGenFramebuffersEXT");
		_hoops_CSRGR->_hoops_IIAGC = (glCheckFramebufferStatusEXTProc) GetProcAddress("glCheckFramebufferStatusEXT");

		_hoops_CSRGR->_hoops_SCAGC = (glFramebufferTexture1DEXTProc) GetProcAddress("glFramebufferTexture1DEXT");
		_hoops_CSRGR->_hoops_GSAGC = (glFramebufferTexture2DEXTProc) GetProcAddress("glFramebufferTexture2DEXT");
		_hoops_CSRGR->_hoops_RSAGC = (glFramebufferTexture3DEXTProc) GetProcAddress("glFramebufferTexture3DEXT");

		_hoops_CSRGR->_hoops_ASAGC = (glFramebufferRenderbufferEXTProc) GetProcAddress("glFramebufferRenderbufferEXT");
		_hoops_CSRGR->glGetFramebufferAttachmentParameterivEXT = (glGetFramebufferAttachmentParameterivEXTProc) GetProcAddress("glGetFramebufferAttachmentParameterivEXT");
		_hoops_CSRGR->glGenerateMipmapEXT = (glGenerateMipmapEXTProc) GetProcAddress("glGenerateMipmapEXT");

		if (!_hoops_CSRGR->_glIsRenderbufferEXT ||
			!_hoops_CSRGR->_hoops_ACAGC ||
			!_hoops_CSRGR->_glDeleteRenderbuffersEXT ||
			!_hoops_CSRGR->_hoops_PCAGC ||
			!_hoops_CSRGR->_hoops_HCAGC ||
			!_hoops_CSRGR->glGetRenderbufferParameterivEXT ||
			!_hoops_CSRGR->_hoops_ICAGC ||
			!_hoops_CSRGR->_hoops_HIAGC ||
			!_hoops_CSRGR->_hoops_AIAGC ||
			!_hoops_CSRGR->_hoops_CCAGC ||
			!_hoops_CSRGR->_hoops_IIAGC ||
			!_hoops_CSRGR->_hoops_SCAGC ||
			!_hoops_CSRGR->_hoops_GSAGC ||
			!_hoops_CSRGR->_hoops_RSAGC ||
			!_hoops_CSRGR->_hoops_ASAGC ||
			!_hoops_CSRGR->glGetFramebufferAttachmentParameterivEXT ||
			!_hoops_CSRGR->glGenerateMipmapEXT)
			_hoops_CSRGR->_hoops_RCAGC = false;

	}

	if (!_hoops_GCAGC)
		return _hoops_CSRGR->_hoops_RCAGC;


	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &_hoops_CSRGR->_hoops_PSAGC);

	if (_hoops_CSRGR->_hoops_PSAGC < 1) {
		_hoops_CSRGR->_hoops_RCAGC = false;
	}

	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &_hoops_CSRGR->_hoops_HSAGC);

	if (_hoops_CSRGR->_hoops_HSAGC < 1) {
		_hoops_CSRGR->_hoops_RCAGC = false;
	}

	if (_hoops_CSRGR->_hoops_RCAGC) {

		_hoops_CSRGR->_hoops_ISAGC = _hoops_HSHGI(_hoops_IAAA(_hoops_CSRGR->_hoops_IHGRR->width, 8));
		_hoops_CSRGR->_hoops_CSAGC = _hoops_HSHGI(_hoops_IAAA(_hoops_CSRGR->_hoops_IHGRR->height, 8));

#ifdef DEBUG_FBO
		fprintf(stderr,"fbo_width: %d fbo_height: %d\n", _hoops_CSRGR->_hoops_ISAGC, _hoops_CSRGR->_hoops_CSAGC);
#endif

		if (_hoops_CSRGR->_hoops_ISAGC > _hoops_CSRGR->_hoops_HSAGC ||
			_hoops_CSRGR->_hoops_CSAGC > _hoops_CSRGR->_hoops_HSAGC) {
#ifdef DEBUG_FBO
		fprintf(stderr,"fbo_max_renderbuffer_size: %d exceded!!!\n", _hoops_CSRGR->_hoops_HSAGC);
#endif
			goto _hoops_CIAGC;
		}

		/* _hoops_HGSR _hoops_HAIR _hoops_HH */
		glGenTextures(1, &_hoops_CSRGR->_hoops_CHAGC);
		_hoops_IPRGC( _hoops_CSRGR, 0, GL_TEXTURE_2D, _hoops_CSRGR->_hoops_CHAGC);
		if (glIsTexture(_hoops_CSRGR->_hoops_CHAGC) == GL_FALSE) {
#ifdef DEBUG_FBO
			fprintf(stderr,"fbo_color_tex == GL_FALSE\n");
#endif
			goto _hoops_CIAGC;
		}
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,
			_hoops_CSRGR->_hoops_ISAGC,_hoops_CSRGR->_hoops_CSAGC,
			0,GL_RGBA,GL_UNSIGNED_BYTE,0);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		_hoops_CSRGR->_hoops_SSAGC = _hoops_RHAGC("GL_EXT_packed_depth_stencil");

		if (_hoops_CSRGR->_hoops_SSAGC) {
#ifdef DEBUG_FBO
			fprintf(stderr,"supports_EXT_packed_depth_stencil\n");
#endif
			/* _hoops_HSPC _hoops_HCH/_hoops_APSP _hoops_GGPGC */
			_hoops_CSRGR->_hoops_PCAGC(1, &_hoops_CSRGR->_hoops_SHAGC);
			_hoops_CSRGR->_hoops_ACAGC(GL_RENDERBUFFER_EXT, _hoops_CSRGR->_hoops_SHAGC);
			if (_hoops_CSRGR->_glIsRenderbufferEXT(_hoops_CSRGR->_hoops_SHAGC) == GL_FALSE) {
#ifdef DEBUG_FBO
				fprintf(stderr,"fbo_depth_stencil_rb == GL_FALSE\n");
#endif
				goto _hoops_CIAGC;
			}
			_hoops_CSRGR->_hoops_HCAGC(
				GL_RENDERBUFFER_EXT, GL_DEPTH24_STENCIL8_EXT,
				_hoops_CSRGR->_hoops_ISAGC, _hoops_CSRGR->_hoops_CSAGC);

			if (_hoops_CSRGR->_hoops_SHAGC == 0)
				_hoops_CSRGR->_hoops_SSAGC = false;
#ifdef DEBUG_FBO
			else
				fprintf(stderr,"we have fbo_depth_stencil_rb\n");
#endif
		}

		if (!_hoops_CSRGR->_hoops_SSAGC) {
			/* _hoops_HSPC _hoops_HCH _hoops_GGPGC */
			_hoops_CSRGR->_hoops_PCAGC(1, &_hoops_CSRGR->_hoops_GIAGC);
			_hoops_CSRGR->_hoops_ACAGC(GL_RENDERBUFFER_EXT, _hoops_CSRGR->_hoops_GIAGC);
			if (_hoops_CSRGR->_glIsRenderbufferEXT(_hoops_CSRGR->_hoops_GIAGC) == GL_FALSE) {
#ifdef DEBUG_FBO
				fprintf(stderr,"fbo_depth_rb == GL_FALSE\n");
#endif
				goto _hoops_CIAGC;
			}
			_hoops_CSRGR->_hoops_HCAGC(
				GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24,
				_hoops_CSRGR->_hoops_ISAGC, _hoops_CSRGR->_hoops_CSAGC);

#if 0
			/* _hoops_HSPC _hoops_APSP _hoops_GGPGC */
			_hoops_CSRGR->_hoops_PCAGC(1, &_hoops_CSRGR->_hoops_RGPGC);
			_hoops_CSRGR->_hoops_ACAGC(GL_RENDERBUFFER_EXT, _hoops_CSRGR->_hoops_RGPGC);
			if (_hoops_CSRGR->_glIsRenderbufferEXT(_hoops_CSRGR->_hoops_RGPGC) == GL_FALSE) {
#ifdef DEBUG_FBO
				fprintf(stderr,"fbo_stencil_rb == GL_FALSE\n");
#endif
				goto _hoops_CIAGC;
			}
			_hoops_CSRGR->_hoops_HCAGC(
				GL_RENDERBUFFER_EXT, GL_STENCIL_INDEX8_EXT,
				_hoops_CSRGR->_hoops_ISAGC, _hoops_CSRGR->_hoops_CSAGC);
#endif

		}

		_hoops_CSRGR->_hoops_CCAGC(1, &_hoops_CSRGR->_hoops_RIAGC);
		_hoops_CSRGR->_hoops_HIAGC(GL_FRAMEBUFFER_EXT, _hoops_CSRGR->_hoops_RIAGC);
		if (_hoops_CSRGR->_hoops_ICAGC(_hoops_CSRGR->_hoops_RIAGC) == GL_FALSE) {
#ifdef DEBUG_FBO
			fprintf(stderr,"fbo_fb == GL_FALSE\n");
#endif
			goto _hoops_CIAGC;
		}


		_hoops_CSRGR->_hoops_GSAGC(GL_FRAMEBUFFER_EXT,
			GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D,
			_hoops_CSRGR->_hoops_CHAGC, 0);

		if (_hoops_CSRGR->_hoops_SHAGC) {
			_hoops_CSRGR->_hoops_ASAGC(GL_FRAMEBUFFER_EXT,
				GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT,
				_hoops_CSRGR->_hoops_SHAGC);
			_hoops_CSRGR->_hoops_ASAGC(GL_FRAMEBUFFER_EXT,
				GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT,
				_hoops_CSRGR->_hoops_SHAGC);
		}

		if (_hoops_CSRGR->_hoops_GIAGC)
			_hoops_CSRGR->_hoops_ASAGC(GL_FRAMEBUFFER_EXT,
				GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT,
				_hoops_CSRGR->_hoops_GIAGC);

		if (_hoops_CSRGR->_hoops_RGPGC)
			_hoops_CSRGR->_hoops_ASAGC(GL_FRAMEBUFFER_EXT,
				GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT,
				_hoops_CSRGR->_hoops_RGPGC);

		if (!_hoops_PIAGC(_hoops_CSRGR))
			goto _hoops_CIAGC;

		return true;
	}


_hoops_CIAGC:

	_hoops_IHAGC(_hoops_CSRGR);

	HE_WARNING (HEC_OPENGL_DRIVER, HES_VISUAL_FOR_OPENGL_MISSING, "FBO setup failed");

	return false;
}

#endif

/* _hoops_PIP _hoops_SGS _hoops_RGR _hoops_AGPGC _hoops_HRGR _hoops_GGR _hoops_PIHRA _hoops_IS _hoops_RH _hoops_CSPP _hoops_SASI _hoops_GIGAA
 * _hoops_SGS _hoops_PAH _hoops_SHH _hoops_PGGGH _hoops_CCA _hoops_PGPGC _hoops_HGPGC.  _hoops_AIHH _hoops_IGPGC */
local void
_hoops_CGPGC (OGLData alter * _hoops_CSRGR)
{
	if (!_hoops_CSRGR->_hoops_PRARR->id.text)
		return;
	if (HI_CI_Wild_Equal_Strings("*radeon*", _hoops_CSRGR->_hoops_PRARR->id.text)) {
		if (_hoops_CSRGR->_hoops_SGPGC == 2) {
			if (_hoops_CSRGR->_hoops_GRPGC == 0) {
				if (_hoops_CSRGR->_hoops_RRPGC <= 5883)
					XBIT_APPEND (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_FRAGMENT_PROGRAM);
			}
		}
	}
}

/*
 * _hoops_PGAA
 * _hoops_IPCP _hoops_ACPH _hoops_GASR _hoops_CGH _hoops_SHH _hoops_SRSS _hoops_GGR _hoops_RGAR _hoops_PGCR _hoops_IIHP:
 *	 1. _hoops_HPGR _hoops_CISPP _hoops_GGR _hoops_SRAAH
 *	 2. _hoops_ARI, _hoops_RAS _hoops_SR _hoops_CAHA _hoops_GGSR _hoops_RH _hoops_CGCH _hoops_SARR _hoops_IIGR _hoops_PGPRH _hoops_SR _hoops_CHR _hoops_GACH _hoops_CCA
 */
local void
_hoops_ARPGC (OGLData alter * _hoops_CSRGR)
{
	char const *extensions;
	char const *version;
	Display_Context alter *	dc = (Display_Context alter *)_hoops_CSRGR->dc;
	_hoops_APARR alter &	_hoops_RRCI = (_hoops_APARR alter &) dc->_hoops_ACPGR;
	int _hoops_PRPGC = 0;
	int _hoops_HRPGC;

	version = (char const *) glGetString (GL_VERSION);

	if (!version)
		version = "1.1";

	_hoops_HRPGC = sscanf(version,"%d.%d.%d", &_hoops_CSRGR->_hoops_SGPGC, &_hoops_CSRGR->_hoops_GRPGC, &_hoops_CSRGR->_hoops_RRPGC);
	if (_hoops_HRPGC < 3)
		_hoops_CSRGR->_hoops_RRPGC = 0;
	_hoops_CGPGC (_hoops_CSRGR);

	if (_hoops_CSRGR->_hoops_SGPGC == 1 && _hoops_CSRGR->_hoops_GRPGC < 2)
		_hoops_CSRGR->_hoops_IRPGC = true;
	else
		_hoops_CSRGR->_hoops_IRPGC = false;

	if (!XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_SEPARATE_SPECULAR)) {
		if (_hoops_CSRGR->_hoops_SGPGC > 1 || (_hoops_CSRGR->_hoops_SGPGC == 1 && _hoops_CSRGR->_hoops_GRPGC >=2))
			_hoops_CSRGR->_hoops_CRPGC = true;
		else
			_hoops_CSRGR->_hoops_CRPGC = false;
	}
	else
		_hoops_CSRGR->_hoops_CRPGC = false;

	extensions = (char const *) glGetString (GL_EXTENSIONS);

	if (!extensions)
		extensions = "";

	_hoops_CSRGR->_hoops_SRPGC = _hoops_RHAGC("GL_ATI_meminfo");
	_hoops_CSRGR->_hoops_GAPGC = _hoops_RHAGC("GL_EXT_texture_filter_anisotropic");
	_hoops_CSRGR->_hoops_RAPGC = _hoops_RHAGC("GL_EXT_clip_volume_hint");
	_hoops_CSRGR->_hoops_AAPGC = _hoops_RHAGC("GL_ARB_texture_mirrored_repeat");
	_hoops_CSRGR->_hoops_PAPGC = _hoops_RHAGC("GL_EXT_bgra");
	_hoops_CSRGR->_hoops_HAPGC = 
		(_hoops_RHAGC("GL_ARB_texture_non_power_of_two") &&
		!XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_NON_POWER_OF_2_TEXTURES));

	_hoops_CSRGR->_hoops_IAPGC = _hoops_RHAGC("GL_NV_primitive_restart");
	_hoops_CSRGR->_hoops_CAPGC = _hoops_RHAGC ("GL_ARB_texture_border_clamp");

	//_hoops_GASA _hoops_PIP: _hoops_HAR _hoops_RCRR _hoops_RPP _hoops_CPHP _hoops_PII _hoops_RH _hoops_HSPR _hoops_HRGR _hoops_HAHH _hoops_PAR _hoops_HAR
	//_hoops_RPP (_hoops_HGPGA->_hoops_SAPGC) {
	//	_hoops_AIIC _hoops_HGPC[4] = {0.5, 0.5, 0.5, 0};
	//	_hoops_GPPGC (_hoops_RPPGC, _hoops_APPGC, _hoops_HGPC);
	//}

	_hoops_CSRGR->_hoops_PPPGC =
					(_hoops_RHAGC("GL_ARB_texture_rectangle") ||
					 _hoops_RHAGC("GL_EXT_texture_rectangle") ||
					 _hoops_RHAGC("GL_NV_texture_rectangle"));
	if (XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_SEPARATE_SPECULAR))
		_hoops_CSRGR->_hoops_PPPGC = false;

	_hoops_CSRGR->_hoops_HPPGC = _hoops_RHAGC("GL_ARB_point_parameters");
	if (!_hoops_CSRGR->_hoops_HPPGC)
		_hoops_CSRGR->_hoops_HPPGC = _hoops_RHAGC("GL_EXT_point_parameters");
	if (_hoops_CSRGR->_hoops_HPPGC) {
		_hoops_CSRGR->_hoops_IPPGC = (glPointParameterfARBProc) GetProcAddress ("glPointParameterfARB");
		if (!_hoops_CSRGR->_hoops_IPPGC)
			_hoops_CSRGR->_hoops_IPPGC = (glPointParameterfARBProc) GetProcAddress ("glPointParameterfEXT");
		_hoops_CSRGR->_hoops_CPPGC = (glPointParameterfvARBProc) GetProcAddress ("glPointParameterfvARB");
		if (!_hoops_CSRGR->_hoops_CPPGC)
			_hoops_CSRGR->_hoops_CPPGC = (glPointParameterfvARBProc) GetProcAddress ("glPointParameterfvEXT");
		if (!_hoops_CSRGR->_hoops_IPPGC || !_hoops_CSRGR->_hoops_CPPGC)
			_hoops_CSRGR->_hoops_HPPGC=false;
	}

	_hoops_CSRGR->_hoops_SPPGC = _hoops_RHAGC("GL_ARB_depth_texture");
	_hoops_CSRGR->_hoops_GHPGC = _hoops_RHAGC("GL_ARB_shadow");

	_hoops_CSRGR->_hoops_RHPGC = _hoops_RHAGC("GL_ARB_texture_compression");
	if (_hoops_CSRGR->_hoops_RHPGC) {
		_hoops_CSRGR->_hoops_AHPGC = _hoops_RHAGC("GL_EXT_texture_compression_s3tc");
		if (!_hoops_CSRGR->_hoops_AHPGC)
			_hoops_CSRGR->_hoops_AHPGC = _hoops_RHAGC("GL_S3_s3tc");
		_hoops_CSRGR->glCompressedTexImage2DARB = (glCompressedTexImage2DARBProc) GetProcAddress ("glCompressedTexImage2DARB");
		if (!_hoops_CSRGR->_hoops_AHPGC || !_hoops_CSRGR->glCompressedTexImage2DARB)
			_hoops_CSRGR->_hoops_RHPGC=false;
	}

	_hoops_CSRGR->_hoops_PHPGC= _hoops_RHAGC("GL_EXT_texture3D");
	if (_hoops_CSRGR->_hoops_PHPGC) {
		_hoops_CSRGR->glTexImage3D = (glTexImage3DProc) GetProcAddress ("glTexImage3D");
		_hoops_CSRGR->glTexSubImage3D = (glTexSubImage3DProc) GetProcAddress ("glTexSubImage3D");
		if (!_hoops_CSRGR->glTexImage3D || !_hoops_CSRGR->glTexSubImage3D)
			_hoops_CSRGR->_hoops_PHPGC=false;
	}

	_hoops_CSRGR->_hoops_HHPGC = _hoops_RHAGC("GL_NV_fence");
	if (_hoops_CSRGR->_hoops_HHPGC) {
		_hoops_CSRGR->glGenFencesNV = (glGenFencesNVProc) GetProcAddress ("glGenFencesNV");
		_hoops_CSRGR->glDeleteFencesNV = (glDeleteFencesNVProc) GetProcAddress ("glDeleteFencesNV");
		_hoops_CSRGR->glSetFenceNV = (glSetFenceNVProc) GetProcAddress ("glSetFenceNV");
		_hoops_CSRGR->glTestFenceNV = (glTestFenceNVProc) GetProcAddress ("glTestFenceNV");
		_hoops_CSRGR->glFinishFenceNV = (glFinishFenceNVProc) GetProcAddress ("glFinishFenceNV");
		_hoops_CSRGR->glIsFenceNV = (glIsFenceNVProc) GetProcAddress ("glIsFenceNV");
		_hoops_CSRGR->glGetFenceivNV = (glGetFenceivNVProc) GetProcAddress ("glGetFenceivNV");
		if (!_hoops_CSRGR->glGenFencesNV ||
			!_hoops_CSRGR->glDeleteFencesNV ||
			!_hoops_CSRGR->glSetFenceNV ||
			!_hoops_CSRGR->glTestFenceNV ||
			!_hoops_CSRGR->glFinishFenceNV ||
			!_hoops_CSRGR->glIsFenceNV ||
			!_hoops_CSRGR->glGetFenceivNV)
			_hoops_CSRGR->_hoops_HHPGC = false;
	}

#if 0
	_hoops_SIAGC(_hoops_CSRGR, false);
#endif
	_hoops_CSRGR->_hoops_IHPGC = !XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_VERTEX_BUFFER_OBJECT) &&
								_hoops_RHAGC("GL_ARB_vertex_buffer_object");
	if (_hoops_CSRGR->_hoops_IHPGC) {
		_hoops_CSRGR->_hoops_PSPGI = (glBindBufferARBProc) GetProcAddress ("glBindBufferARB");
		_hoops_CSRGR->_hoops_ISPGI = (glDeleteBuffersARBProc) GetProcAddress ("glDeleteBuffersARB");
		_hoops_CSRGR->_hoops_CHPGC = (glGenBuffersARBProc) GetProcAddress ("glGenBuffersARB");
		_hoops_CSRGR->_hoops_SHPGC = (glIsBufferARBProc) GetProcAddress ("glIsBufferARB");
		_hoops_CSRGR->_hoops_HSPGI = (glBufferDataARBProc) GetProcAddress ("glBufferDataARB");
		_hoops_CSRGR->_hoops_GIPGC = (glBufferSubDataARBProc) GetProcAddress ("glBufferSubDataARB");
		_hoops_CSRGR->_hoops_RIPGC = (glGetBufferSubDataARBProc) GetProcAddress ("glGetBufferSubDataARB");
		_hoops_CSRGR->_hoops_AIPGC = (glMapBufferARBProc) GetProcAddress ("glMapBufferARB");
		_hoops_CSRGR->_hoops_PIPGC = (glUnmapBufferARBProc) GetProcAddress ("glUnmapBufferARB");
		_hoops_CSRGR->_hoops_HIPGC = (glGetBufferParameterivARBProc) GetProcAddress ("glGetBufferParameterivARB");
		_hoops_CSRGR->_hoops_IIPGC = (glGetBufferPointervARBProc) GetProcAddress ("glGetBufferPointervARB");
		if (!_hoops_CSRGR->_hoops_PSPGI ||
			!_hoops_CSRGR->_hoops_ISPGI ||
			!_hoops_CSRGR->_hoops_CHPGC ||
			!_hoops_CSRGR->_hoops_SHPGC ||
			!_hoops_CSRGR->_hoops_HSPGI ||
			!_hoops_CSRGR->_hoops_GIPGC ||
			!_hoops_CSRGR->_hoops_RIPGC ||
			!_hoops_CSRGR->_hoops_AIPGC ||
			!_hoops_CSRGR->_hoops_PIPGC ||
			!_hoops_CSRGR->_hoops_HIPGC ||
			!_hoops_CSRGR->_hoops_IIPGC)
			_hoops_CSRGR->_hoops_IHPGC = false;
		HOOPS_WORLD->_hoops_PSPGI = (void*)_hoops_CSRGR->_hoops_PSPGI;
		HOOPS_WORLD->_hoops_HSPGI = (void*)_hoops_CSRGR->_hoops_HSPGI;
		HOOPS_WORLD->_hoops_ISPGI = (void*)_hoops_CSRGR->_hoops_ISPGI;
	}

	_hoops_CSRGR->glDrawRangeElementsEXT = (glDrawRangeElementsEXTProc) GetProcAddress ("glDrawRangeElementsEXT");
	if (!_hoops_CSRGR->glDrawRangeElementsEXT)
		_hoops_CSRGR->glDrawRangeElementsEXT = (glDrawRangeElementsEXTProc) GetProcAddress ("glDrawRangeElements");

	_hoops_CSRGR->glMultiDrawElementsEXT = (glMultiDrawElementsEXTProc) GetProcAddress ("glMultiDrawElementsEXT");
	if (!_hoops_CSRGR->glMultiDrawElementsEXT)
		_hoops_CSRGR->glMultiDrawElementsEXT = (glMultiDrawElementsEXTProc) GetProcAddress ("glMultiDrawElements");

	_hoops_CSRGR->glMultiDrawArraysEXT = (glMultiDrawArraysEXTProc) GetProcAddress ("glMultiDrawArraysEXT");
	if (!_hoops_CSRGR->glMultiDrawArraysEXT)
		_hoops_CSRGR->glMultiDrawArraysEXT = (glMultiDrawArraysEXTProc) GetProcAddress ("glMultiDrawArrays");


#if 0
	/* _hoops_GRS _hoops_RARI _hoops_RGR _hoops_CGPR _hoops_SR _hoops_HS _hoops_CIPGC */
	if (_hoops_CSRGR->_hoops_IAPGC) {
		_hoops_CSRGR->_hoops_SIPGC = (glPrimitiveRestartNVProc) GetProcAddress ("glPrimitiveRestartNV");
		_hoops_CSRGR->_hoops_GCPGC = (glPrimitiveRestartIndexNVProc) GetProcAddress ("glPrimitiveRestartIndexNV");
		if (!_hoops_CSRGR->_hoops_SIPGC || !_hoops_CSRGR->_hoops_GCPGC)
			_hoops_CSRGR->_hoops_IAPGC = false;
		else {
			glEnableClientState(GL_PRIMITIVE_RESTART_NV);
			_hoops_CSRGR->_hoops_GCPGC(_hoops_RCPGC);
			_hoops_CSRGR->_hoops_SIPGC();
		}
	}
#endif

	/* _hoops_RCPP _hoops_CCGR _hoops_GIPCR _hoops_IAII */
	_hoops_CSRGR->_hoops_ACPGC = false;
	if (!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_KTX) &&
		_hoops_RHAGC("GL_KTX_buffer_region")) {
		glKTXBufferRegionEnabledProc glKTXBufferRegionEnabled;

		_hoops_CSRGR->glNewKTXBufferRegion = (glNewKTXBufferRegionProc) GetProcAddress ("glNewKTXBufferRegion");
		_hoops_CSRGR->glDeleteKTXBufferRegion = (glDeleteKTXBufferRegionProc) GetProcAddress ("glDeleteKTXBufferRegion");
		_hoops_CSRGR->glReadKTXBufferRegion = (glReadKTXBufferRegionProc) GetProcAddress ("glReadKTXBufferRegion");
		_hoops_CSRGR->glDrawKTXBufferRegion = (glDrawKTXBufferRegionProc) GetProcAddress ("glDrawKTXBufferRegion");
		glKTXBufferRegionEnabled = (glKTXBufferRegionEnabledProc) GetProcAddress ("glKTXBufferRegionEnabled");

		if (!_hoops_CSRGR->glNewKTXBufferRegion) {
			_hoops_CSRGR->glNewKTXBufferRegion = (glNewKTXBufferRegionProc) GetProcAddress ("glNewBufferRegion");
			_hoops_CSRGR->glDeleteKTXBufferRegion = (glDeleteKTXBufferRegionProc) GetProcAddress ("glDeleteBufferRegion");
			_hoops_CSRGR->glReadKTXBufferRegion = (glReadKTXBufferRegionProc) GetProcAddress ("glReadBufferRegion");
			_hoops_CSRGR->glDrawKTXBufferRegion = (glDrawKTXBufferRegionProc) GetProcAddress ("glDrawBufferRegion");
			glKTXBufferRegionEnabled = (glKTXBufferRegionEnabledProc) GetProcAddress ("glBufferRegionEnabled");
		}

		if (_hoops_CSRGR->_hoops_AIPGA > 1)
			glKTXBufferRegionEnabled = false;

		if (_hoops_CSRGR->glNewKTXBufferRegion &&
			_hoops_CSRGR->glDeleteKTXBufferRegion &&
			_hoops_CSRGR->glReadKTXBufferRegion &&
			_hoops_CSRGR->glDrawKTXBufferRegion &&
			glKTXBufferRegionEnabled) {
			/* _hoops_PIRGC _hoops_RHPP _hoops_PAH _hoops_HGGC _hoops_PCPGC _hoops_ACSRR _hoops_HCPGC _hoops_RPP,
			 * _hoops_IH _hoops_PCAI, _hoops_HAR _hoops_RAPR _hoops_SRHSI _hoops_PPGS _hoops_HRGR _hoops_HHPA */
			if ((*glKTXBufferRegionEnabled)()) {
				_hoops_CSRGR->_hoops_ACPGC = true;
			}
		}
	}
	if (!_hoops_CSRGR->_hoops_ACPGC) {
		_hoops_CSRGR->glNewKTXBufferRegion=0;
		_hoops_CSRGR->glDeleteKTXBufferRegion=0;
		_hoops_CSRGR->glReadKTXBufferRegion=0;
		_hoops_CSRGR->glDrawKTXBufferRegion=0;
	}

	if (!XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_FRAGMENT_PROGRAM) &&
		(_hoops_RHAGC("GL_ARB_vertex_program") || _hoops_RHAGC("ARB_fragment_program"))) {

		_hoops_CSRGR->glGenProgramsARB = (glGenProgramsARBProc) GetProcAddress ("glGenProgramsARB");
		_hoops_CSRGR->glDeleteProgramsARB = (glDeleteProgramsARBProc) GetProcAddress ("glDeleteProgramsARB");
		_hoops_CSRGR->glProgramStringARB = (glProgramStringARBProc) GetProcAddress ("glProgramStringARB");
		_hoops_CSRGR->glBindProgramARB = (glBindProgramARBProc) GetProcAddress ("glBindProgramARB");
		_hoops_CSRGR->glProgramEnvParameter4fARB = (glProgramEnvParameter4fARBProc) GetProcAddress ("glProgramEnvParameter4fARB");

		if (_hoops_CSRGR->glGenProgramsARB &&
			_hoops_CSRGR->glDeleteProgramsARB &&
			_hoops_CSRGR->glProgramStringARB &&
			_hoops_CSRGR->glBindProgramARB &&
			_hoops_CSRGR->glProgramEnvParameter4fARB) {
			/* _hoops_PIP: _hoops_ICPGC _hoops_HRGR _hoops_HAHH _hoops_HIH _hoops_HAR _hoops_CHIS _hoops_IH _hoops_CCPGC _hoops_GCGH, _hoops_HIS
			   _hoops_HGPGA->_hoops_SCPGC _hoops_PAH _hoops_HGGC _hoops_SHH _hoops_IRAP */
			_hoops_CSRGR->_hoops_GSPGC = _hoops_RHAGC("GL_ARB_vertex_program");
			_hoops_CSRGR->_hoops_RSPGC = _hoops_RHAGC("GL_ARB_fragment_program");
			_hoops_CSRGR->_hoops_ASPGC = _hoops_RHAGC("GL_ARB_fragment_program_shadow");
		}
		else {
			_hoops_CSRGR->glGenProgramsARB=0;
			_hoops_CSRGR->glDeleteProgramsARB=0;
			_hoops_CSRGR->glProgramStringARB=0;
			_hoops_CSRGR->glBindProgramARB=0;
			_hoops_CSRGR->glProgramEnvParameter4fARB = 0;
		}
	}

	if (_hoops_CSRGR->_hoops_GSPGC && _hoops_RHAGC ("ARB_shader_objects")) {

		_hoops_CSRGR->glShaderSourceARB = (glShaderSourceARBProc) GetProcAddress ("glShaderSourceARB");
		_hoops_CSRGR->glCompileShaderARB = (glCompileShaderARBProc) GetProcAddress ("glCompileShaderARB");
		_hoops_CSRGR->glGetInfoLogARB = (glGetInfoLogARBProc) GetProcAddress ("glGetInfoLogARB");
		_hoops_CSRGR->glAttachObjectARB = (glAttachObjectARBProc) GetProcAddress ("glAttachObjectARB");
		_hoops_CSRGR->_hoops_PSPGC = (glDetachObjectARBProc) GetProcAddress ("glDetachObjectARB");
		_hoops_CSRGR->glDeleteShaderARB = (glDeleteShaderARBProc) GetProcAddress ("glDeleteShaderARB");
		_hoops_CSRGR->glLinkProgramARB = (glLinkProgramARBProc) GetProcAddress ("glLinkProgramARB");
		_hoops_CSRGR->glCreateShaderObjectARB = (glCreateShaderObjectARBProc) GetProcAddress ("glCreateShaderObjectARB");
		_hoops_CSRGR->glCreateProgramObjectARB = (glCreateProgramObjectARBProc) GetProcAddress ("glCreateProgramObjectARB");
		_hoops_CSRGR->glDeleteProgramARB = (glDeleteProgramARBProc) GetProcAddress ("glDeleteProgramARB");
		/* _hoops_IH _hoops_HHH _hoops_SCPC, _hoops_GCGAH'_hoops_GRI _hoops_SPSIR _hoops_ASRC _hoops_IRAP _hoops_RPP _hoops_RHAC _hoops_SGH
			"_hoops_HSPGC", _hoops_RIIA _hoops_IIGR "_hoops_ISPGC"  _hoops_PAR
			"_hoops_CSPGC" _hoops_RIIA _hoops_IIGR "_hoops_SSPGC" */
		if (!_hoops_CSRGR->glDeleteShaderARB)
			_hoops_CSRGR->glDeleteShaderARB = (glDeleteShaderARBProc) GetProcAddress ("glDeleteShader");
		if (!_hoops_CSRGR->glDeleteProgramARB)
			_hoops_CSRGR->glDeleteProgramARB = (glDeleteProgramARBProc) GetProcAddress ("glDeleteProgram");
		_hoops_CSRGR->glUseProgramObjectARB = (glUseProgramObjectARBProc) GetProcAddress ("glUseProgramObjectARB");
		_hoops_CSRGR->glGetObjectParameterfvARB = (glGetObjectParameterfvARBProc) GetProcAddress ("glGetObjectParameterfvARB");
		_hoops_CSRGR->glGetObjectParameterivARB = (glGetObjectParameterivARBProc) GetProcAddress ("glGetObjectParameterivARB");

		if (_hoops_CSRGR->glShaderSourceARB &&
			_hoops_CSRGR->glCompileShaderARB &&
			_hoops_CSRGR->glGetInfoLogARB &&
			_hoops_CSRGR->glAttachObjectARB &&
			_hoops_CSRGR->_hoops_PSPGC &&
			_hoops_CSRGR->glDeleteShaderARB &&
			_hoops_CSRGR->glLinkProgramARB &&
			_hoops_CSRGR->glCreateShaderObjectARB &&
			_hoops_CSRGR->glCreateProgramObjectARB &&
			_hoops_CSRGR->glDeleteProgramARB &&
			_hoops_CSRGR->glUseProgramObjectARB &&
			_hoops_CSRGR->glGetObjectParameterfvARB &&
			_hoops_CSRGR->glGetObjectParameterivARB) {
			_hoops_CSRGR->_hoops_GGHGC = true;
		}
		else {
			_hoops_CSRGR->glShaderSourceARB=0;
			_hoops_CSRGR->glCompileShaderARB=0;
			_hoops_CSRGR->glGetInfoLogARB=0;
			_hoops_CSRGR->glAttachObjectARB=0;
			_hoops_CSRGR->_hoops_PSPGC=0;
			_hoops_CSRGR->glDeleteShaderARB=0;
			_hoops_CSRGR->glLinkProgramARB=0;
			_hoops_CSRGR->glCreateShaderObjectARB=0;
			_hoops_CSRGR->glCreateProgramObjectARB=0;
			_hoops_CSRGR->glDeleteProgramARB=0;
			_hoops_CSRGR->glUseProgramObjectARB=0;
			_hoops_CSRGR->glGetObjectParameterfvARB = 0;
			_hoops_CSRGR->glGetObjectParameterivARB = 0;
		}
	}


#ifdef GL_VERSION_1_3
	_hoops_CSRGR->glActiveTextureARB = (glActiveTextureARBProc) GetProcAddress("glActiveTexture");
	_hoops_CSRGR->_hoops_RGHGC = (glActiveTextureARBProc) GetProcAddress("glClientActiveTexture");
	_hoops_CSRGR->glMultiTexCoord2fvARB = (glMultiTexCoord2fvARBProc) GetProcAddress("glMultiTexCoord2fv");
	_hoops_CSRGR->glMultiTexCoord3fvARB = (glMultiTexCoord2fvARBProc) GetProcAddress("glMultiTexCoord3fv");
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &_hoops_CSRGR->_hoops_AGHGC);
#else
	if (_hoops_RHAGC("GL_ARB_multitexture")) {
		_hoops_CSRGR->glActiveTextureARB = (glActiveTextureARBProc) GetProcAddress("glActiveTextureARB");
		_hoops_CSRGR->_hoops_RGHGC = (glActiveTextureARBProc) GetProcAddress("glClientActiveTextureARB");
		_hoops_CSRGR->glMultiTexCoord2fvARB = (glMultiTexCoord2fvARBProc) GetProcAddress("glMultiTexCoord2fvARB");
		_hoops_CSRGR->glMultiTexCoord3fvARB = (glMultiTexCoord3fvARBProc) GetProcAddress("glMultiTexCoord3fvARB");
		glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &_hoops_CSRGR->_hoops_AGHGC);
		if (_hoops_CSRGR->_hoops_AGHGC > OGL_MAX_TEXTURE_UNITS)
			_hoops_CSRGR->_hoops_AGHGC = OGL_MAX_TEXTURE_UNITS;
	}
	if (_hoops_RHAGC("GL_EXT_texture_env_combine")) {
		_hoops_CSRGR->_hoops_PGHGC = true;
	}

#endif
	if (_hoops_CSRGR->glActiveTextureARB && _hoops_CSRGR->_hoops_AGHGC >= 2 &&
		(_hoops_RHAGC("GL_EXT_texture_env_add") || _hoops_RHAGC("GL_ARB_texture_env_add")) &&
		(_hoops_RHAGC("GL_EXT_texture_cube_map") || _hoops_RHAGC("GL_ARB_texture_cube_map")) &&
		(!XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_PHONG))) {

		_hoops_CSRGR->_hoops_IARGC = true;
#ifdef WGL_DRIVER
		{ /* _hoops_RCSC _hoops_HAR _hoops_PCCP _hoops_HGHGC _hoops_IH _hoops_RH _hoops_AHCI _hoops_PGPRH ? */
			_hoops_RRPRH *_hoops_IRSRA = _hoops_ARPRH();
			if (_hoops_IRSRA->_hoops_SSRRI == _hoops_RGARI) _hoops_CSRGR->_hoops_IARGC = false;
		}
#endif
	}

	/* _hoops_IIRAR _hoops_RH _hoops_IGHGC _hoops_IAGP _hoops_RACGH _hoops_CGPR _hoops_SCH _hoops_HRGR _hoops_HHPA */
	if (_hoops_RHAGC("GL_ARB_occlusion_query")) {
		GLint	_hoops_RCHA;

		_hoops_CSRGR->glGetQueryivARB = (glGetQueryivARBProc) GetProcAddress("glGetQueryivARB");
		if (_hoops_CSRGR->glGetQueryivARB)
			(*_hoops_CSRGR->glGetQueryivARB) (GL_SAMPLES_PASSED_ARB, GL_QUERY_COUNTER_BITS_ARB, &_hoops_RCHA);
		else
			_hoops_RCHA = 0;

		if (_hoops_RCHA > 0) {
			_hoops_CSRGR->glGenQueries = (glGenQueriesARBProc) GetProcAddress("glGenQueriesARB");
			_hoops_CSRGR->glDeleteQueries = (glDeleteQueriesARBProc) GetProcAddress("glDeleteQueriesARB");
			_hoops_CSRGR->glBeginQueryARB = (glBeginQueryARBProc) GetProcAddress("glBeginQueryARB");
			_hoops_CSRGR->glEndQueryARB = (glEndQueryARBProc) GetProcAddress("glEndQueryARB");
			_hoops_CSRGR->glGetQueryObjectuiv = (glGetQueryObjectuivARBProc) GetProcAddress("glGetQueryObjectuivARB");
			if (_hoops_CSRGR->glGenQueries &&
				_hoops_CSRGR->glDeleteQueries &&
				_hoops_CSRGR->glBeginQueryARB &&
				_hoops_CSRGR->glEndQueryARB &&
				_hoops_CSRGR->glGetQueryObjectuiv) {
				_hoops_RRCI->_hoops_GRSSP = _hoops_GRSSP;
				_hoops_RRCI->_hoops_RRSSP = _hoops_RRSSP;
				_hoops_RRCI->_hoops_CRGIP = _hoops_CRGIP;
				_hoops_RRCI->_hoops_ARSSP = _hoops_ARSSP;
			}
		}
	}
	if (_hoops_RRCI->_hoops_GRSSP == null) {
		/* _hoops_HSSC _hoops_ISSC _hoops_IS _hoops_CGHGC _hoops_SGHGC _hoops_CGPR _hoops_SR _hoops_PAH'_hoops_RA _hoops_HGCR _hoops_IGHGC.  _hoops_PAGA _hoops_SGS _hoops_SR _hoops_SGH _hoops_RH _hoops_SCRGC _hoops_CHCPI _hoops_CAS
		    _hoops_RH _hoops_GRHGC _hoops_PPR _hoops_RRHGC _hoops_PSSP. */
		if (_hoops_RHAGC("GL_NV_occlusion_query")) {
			_hoops_CSRGR->glGenQueries = (glGenQueriesARBProc) GetProcAddress("glGenOcclusionQueriesNV");
			_hoops_CSRGR->glDeleteQueries = (glDeleteQueriesARBProc) GetProcAddress("glDeleteOcclusionQueriesNV");
			_hoops_CSRGR->glBeginOcclusionQueryNV = (glBeginOcclusionQueryNVProc) GetProcAddress("glBeginOcclusionQueryNV");
			_hoops_CSRGR->glEndOcclusionQueryNV = (glEndOcclusionQueryNVProc) GetProcAddress("glEndOcclusionQueryNV");
			_hoops_CSRGR->glGetQueryObjectuiv = (glGetQueryObjectuivARBProc) GetProcAddress("glGetOcclusionQueryuivNV");
			if (_hoops_CSRGR->glGenQueries &&
				_hoops_CSRGR->glDeleteQueries &&
				_hoops_CSRGR->glBeginOcclusionQueryNV &&
				_hoops_CSRGR->glEndOcclusionQueryNV &&
				_hoops_CSRGR->glGetQueryObjectuiv) {
				_hoops_RRCI->_hoops_GRSSP = _hoops_GRSSP;
				_hoops_RRCI->_hoops_RRSSP = _hoops_RRSSP;
				_hoops_RRCI->_hoops_CRGIP = _hoops_CRGIP;
				_hoops_RRCI->_hoops_ARSSP = _hoops_ARSSP;
			}
		}
	}

	if (BIT (_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_ARHGC) ||
			XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_VERTEX_ARRAYS)) {
		_hoops_CSRGR->_hoops_PRHGC = false;
	}
	else {
		_hoops_CSRGR->_hoops_PRHGC = true;
	}

	dc->_hoops_PGCC._hoops_AHAGH = 1;  //_hoops_SR _hoops_PAH _hoops_SHR _hoops_HPGR _hoops_CHGC _hoops_AA 1
	if (_hoops_CSRGR->_hoops_GSPGC &&
		_hoops_CSRGR->_hoops_RSPGC &&
		/*_hoops_HGPGA->_hoops_HRHGC &&*/  //<-_hoops_AHPP _hoops_SGS _hoops_IRHGC _hoops_APAC _hoops_PAH _hoops_AA _hoops_SCH _hoops_PRGI _hoops_PHRI _hoops_SSIA _hoops_IRISI _hoops_SSIA _hoops_PAH'_hoops_RA
		_hoops_CSRGR->_hoops_SPPGC &&
		_hoops_CSRGR->_hoops_GHPGC &&
		_hoops_CSRGR->_hoops_PPPGC) {
		_hoops_RRCI->_hoops_RHH = _hoops_RHH;
		if (!_hoops_CSRGR->_hoops_CRHGC &&
			_hoops_CSRGR->_hoops_AIPGA <= 1)
			dc->_hoops_PGCC._hoops_AHAGH = _hoops_APRRR;
	}

	dc->_hoops_PGCC.flags |= _hoops_PAGIP; /* <--- _hoops_PAH _hoops_SHH _hoops_SRHGC _hoops_CAPP */
	if (_hoops_CSRGR->_hoops_GGHGC &&
		!(_hoops_CSRGR->_hoops_AIPGA > 1 && XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_SLOW_MSAA_DEPTH_TEXTURE)))
		_hoops_CSRGR->_hoops_GAHGC = OGLR_DEPTH_TEXTURE_RECT;
	else if (_hoops_CSRGR->_hoops_ACPGC)
		_hoops_CSRGR->_hoops_GAHGC = OGLR_KTX_BUFFER_REGION;
	else if (_hoops_CSRGR->_hoops_RAHGC &&
		!(_hoops_CSRGR->_hoops_AIPGA > 1 && XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_MSAA_WGL_ARB_BUFFER)))
		/* _hoops_PAHA'_hoops_RA _hoops_IHPS _hoops_AHSAR _hoops_GPP _hoops_SPHGR */
		_hoops_CSRGR->_hoops_GAHGC = OGLR_WGL_ARB_BUFFER;
	else if (_hoops_CSRGR->_hoops_AAHGC && _hoops_CSRGR->_hoops_PAHGC)
		/* _hoops_PAHA'_hoops_RA _hoops_IHPS _hoops_AHSAR _hoops_GPP _hoops_SPHGR */
		_hoops_CSRGR->_hoops_GAHGC = OGLR_MAKE_CONTEXT_CURRENT;
	else if (XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_ALLOW_DRAWPIXEL_RESTORE))
		_hoops_CSRGR->_hoops_GAHGC = OGLR_DRAW_PIXELS;
	else
		dc->_hoops_PGCC.flags &= ~_hoops_PAGIP;

	/* _hoops_GGR _hoops_AGR _hoops_IIGR _hoops_RH _hoops_RHPP'_hoops_GRI _hoops_CIHCA... */
	if (!_hoops_CSRGR->_hoops_GSGRR)
			dc->_hoops_PGCC._hoops_IIPGH[_hoops_PRPGC++] = QMoves_Accumulation;
	dc->_hoops_PGCC._hoops_IIPGH[_hoops_PRPGC++] = QMoves_XOR;
	if (BIT(dc->_hoops_PGCC.flags, _hoops_PAGIP))
		dc->_hoops_PGCC._hoops_IIPGH[_hoops_PRPGC++] = QMoves_Spriting;

}/* _hoops_RSGR _hoops_API _hoops_HAHGC */


/*
 * _hoops_PGAA
 */
local void
_hoops_IAHGC (Display_Context alter * dc)
{
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	float _hoops_CAHGC[2];

#if 0
	GLint _hoops_RCHA[3];
	glGetIntegerv (GL_RED_BITS, _hoops_RCHA);
	glGetIntegerv (GL_BLUE_BITS, _hoops_RCHA + 1);
	glGetIntegerv (GL_GREEN_BITS, _hoops_RCHA + 2);
	_hoops_CSRGR->_hoops_SAHGC = _hoops_RCHA[0] + _hoops_RCHA[1] + _hoops_RCHA[2];
#endif
	dc->_hoops_PGCC._hoops_HHPGH =
		dc->_hoops_PGCC._hoops_AAPSR = 1L << 24;
	dc->_hoops_PGCC._hoops_APASR = 0;

	dc->flags |= _hoops_IIPIP;

	/* _hoops_GPHGC _hoops_AAPI, "_hoops_RPHGC" */
	glGetIntegerv (GL_STENCIL_BITS, &_hoops_CSRGR->_hoops_APHGC);
	_hoops_CSRGR->_hoops_PPHGC = _hoops_CSRGR->_hoops_APHGC > 0;

	_hoops_CSRGR->_hoops_GAGRR = false;

	glGetIntegerv (GL_DEPTH_BITS, &_hoops_CSRGR->_hoops_IGARR);

	if (_hoops_CSRGR->_hoops_IGARR > 24)
		_hoops_CSRGR->_hoops_IGARR = 24;

#ifdef NUTCRACKER
	_hoops_CSRGR->_hoops_CGARR = ((__int64)1UL << _hoops_CSRGR->_hoops_IGARR) - 1;
#else
	_hoops_CSRGR->_hoops_CGARR = (0x1 << _hoops_CSRGR->_hoops_IGARR) - 1;
#endif

	dc->flags |= _hoops_RAAGH;
	dc->_hoops_PGCC._hoops_HASHP = _hoops_CSRGR->_hoops_IGARR;
	dc->_hoops_PGCC._hoops_PASHP = (float) (_hoops_CSRGR->_hoops_CGARR);
	/* _hoops_IRHH _hoops_RCRR _hoops_SSH _hoops_SRHR _hoops_HCH _hoops_HRGR _hoops_GGR _hoops_CCIR _hoops_PPR _hoops_SRSHR _hoops_IRS _hoops_RIRA _hoops_AHPA */
	if (dc->_hoops_PGCC._hoops_HASHP > 0)
		dc->flags &= ~_hoops_AASHP;
	else
		dc->flags |= _hoops_AASHP;

	glGetIntegerv (GL_MAX_LIGHTS, &_hoops_CSRGR->_hoops_SHRGC);
	if (_hoops_CSRGR->_hoops_SHRGC < 8)
		_hoops_CSRGR->_hoops_SHRGC = 8;
	dc->_hoops_PGCC._hoops_HGCC = _hoops_CSRGR->_hoops_SHRGC;
	glGetIntegerv (GL_MAX_CLIP_PLANES, &_hoops_CSRGR->_hoops_GAH);
	if (XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_MULTIPLE_CLIP_PLANES))
		_hoops_CSRGR->_hoops_GAH = 1;

	/*_hoops_HGPGA->_hoops_ICCC = 0;*/
	dc->_hoops_PGCC._hoops_ACPGH = _hoops_CSRGR->_hoops_GAH;

	glGetIntegerv (GL_MAX_TEXTURE_SIZE, &_hoops_CSRGR->_hoops_HPHGC);
	if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_TEXTURE_SIZE_OFF_BY_ONE)) {
		_hoops_CSRGR->_hoops_HPHGC--;
	}
	dc->_hoops_PGCC._hoops_PCPGH = _hoops_CSRGR->_hoops_HPHGC;

	/* _hoops_IPHGC _hoops_CPHGC _hoops_HRS _hoops_RH _hoops_CGGPR _hoops_PPR _hoops_AHPA _hoops_SPHGC
	 * _hoops_APP _hoops_HPP _hoops_CGPR _hoops_GHHGC _hoops_HRGR _hoops_PPP.  _hoops_GHAP _hoops_SIPGR'_hoops_RA _hoops_GCRHA
	 * _hoops_GII _hoops_GPPRH _hoops_RHHGC _hoops_SGS _hoops_IIH _hoops_HRGR _hoops_IRS _hoops_AHPA _hoops_CGPR _hoops_GHHGC
	 * _hoops_HRGR _hoops_GRGR. */
	glGetFloatv(GL_LINE_WIDTH_RANGE, _hoops_CAHGC);
	_hoops_CSRGR->_hoops_AHHGC = (int) _hoops_CAHGC[1];

	if (_hoops_CSRGR->_hoops_PHHGC)
		dc->_hoops_PGCC.flags |= _hoops_CPPGH;
	else
		dc->_hoops_PGCC.flags &= ~_hoops_CPPGH;

	dc->_hoops_PGCC.flags |= _hoops_SPPGH;

	if (_hoops_CSRGR->_hoops_IARGC)
		dc->_hoops_PGCC.flags |= _hoops_RPPGH;
	else
		dc->_hoops_PGCC.flags &= ~_hoops_RPPGH;

	dc->_hoops_PGCC.flags |= _hoops_PSSHP;
	dc->_hoops_PGCC.flags |= _hoops_ASSHP;

	//_hoops_RGAR _hoops_HHHGC _hoops_PAR _hoops_IHHGC _hoops_PAH _hoops_GSIA _hoops_CHHGC _hoops_CPRAH _hoops_SHHGC
	if (_hoops_CSRGR->_hoops_PIGRR != DCT_IMAGE && !_hoops_CSRGR->_hoops_GSGRR)
		dc->_hoops_PGCC.flags |= _hoops_PHPGH;

#ifdef GLX_DRIVER
	dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;
#if 0
	{
		GLboolean _hoops_SASSR=GL_TRUE;
		glGetBooleanv (GL_DOUBLEBUFFER, &_hoops_SASSR);

		if (_hoops_SASSR)
			dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;
		else
			dc->_hoops_PGCC._hoops_CHHSR = _hoops_SHHSR;
	}
#endif
#endif

	if (dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA &&
		!dc->options._hoops_AHIIP) {

		dc->_hoops_PGCC._hoops_CHHSR = _hoops_ACPGA;
		_hoops_CSRGR->_hoops_GIHGC = true;
	}

}


/*****************************************************************************
 *****************************************************************************
							 _hoops_ACASI _hoops_ICSH _hoops_PCASI
 *****************************************************************************
 *****************************************************************************/


local void
_hoops_RIHGC (OGLData alter * _hoops_CSRGR,
				   Driver_Color const * color) {
#ifdef GLX_DRIVER
	bool _hoops_AIHGC = true;
	int index = 1;
	XColor _hoops_PIHGC;
	unsigned long error;

	_hoops_RGGA (index == _hoops_CSRGR->overlay._hoops_HIHGC) {
		if (_hoops_CSRGR->overlay.colors[index] == *color) {
			_hoops_AIHGC = false;
			break;
		}
		else {
			++index;
		}
	}

	/* _hoops_PIHA _hoops_PPIP _hoops_RH _hoops_HAIR - _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_IIH _hoops_AIAH */
	if (_hoops_AIHGC) {
		if (_hoops_CSRGR->overlay._hoops_HIHGC < _hoops_CSRGR->overlay._hoops_AHISI - 1)
			++_hoops_CSRGR->overlay._hoops_HIHGC;

		_hoops_PIHGC.red = color->_hoops_HRIR.r << 8 | color->_hoops_HRIR.r;
		_hoops_PIHGC.green = color->_hoops_HRIR.g << 8 | color->_hoops_HRIR.g;
		_hoops_PIHGC.blue = color->_hoops_HRIR.b << 8 | color->_hoops_HRIR.b;

		_hoops_PIHGC.flags = DoRed | DoGreen | DoBlue;
		_hoops_PIHGC.pixel = index;
		error = XStoreColor (_hoops_CSRGR->display, _hoops_CSRGR->overlay.colormap, &_hoops_PIHGC);
		_hoops_CSRGR->overlay.colors[index] = *color;
	}
#if defined (SOLARIS_SYSTEM) || defined (AIX_SYSTEM) || defined (_hoops_PPCSH)
	XInstallColormap (_hoops_CSRGR->display, _hoops_CSRGR->overlay.colormap);
#endif
	glIndexi (index);

	_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;		/* _hoops_SR _hoops_GA'_hoops_RA _hoops_HSSRR _hoops_IIHGC _hoops_SSCHA/_hoops_GSHC */
	UNREFERENCED(error);
#else
	UNREFERENCED(_hoops_CSRGR);
	UNREFERENCED(color);
#endif
}


/* _hoops_PGAA */
local void
_hoops_CIHGC (Display_Context const * dc)
{
#ifdef GLX_DRIVER
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	_hoops_CSRGR->_hoops_RIPGR = false;
	ENSURE_DRAW_MODE (_hoops_CSRGR, DRAW_MODE_OVERLAY);

	_hoops_RCPRR(_hoops_CSRGR);
	ENSURE_SCISSOR_SET (_hoops_CSRGR, 0, 0, _hoops_CSRGR->window_width+1, _hoops_CSRGR->window_height+1);

	_hoops_CAAGC(_hoops_CSRGR);
	ENSURE_VIEWPORT_SET(_hoops_CSRGR, 0, 0, _hoops_CSRGR->window_width, _hoops_CSRGR->window_height);

	/* _hoops_ARH _hoops_RH _hoops_HAIR _hoops_IS _hoops_RRH */
	glClearIndex ((float) _hoops_CSRGR->overlay._hoops_SIHGC);

	_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;
	glFlush ();
	glClear (GL_COLOR_BUFFER_BIT);		/* _hoops_HHAHP _hoops_IIGS _hoops_SCAC _hoops_PRCH */

	FORCE_DRAW_MODE (_hoops_CSRGR, DRAW_MODE_NORMAL);
	FORCE_SCISSOR_OFF (_hoops_CSRGR);
	_hoops_CAAGC(_hoops_CSRGR);

	_hoops_CSRGR->_hoops_HCAC = _hoops_CCC;
	_hoops_CSRGR->_hoops_ICAC = _hoops_CCC;
#else
	UNREFERENCED(dc);
#endif
}


local void
draw_overlay_list (Net_Rendition const & nr)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	HD_Alternate_Hidden_Root (dc, _hoops_IHPGR);
	if (!dc->_hoops_CHPGR &&
		!dc->_hoops_HASS[dc->_hoops_IASS] &&
		!dc->_hoops_GPSS[dc->_hoops_IASS] &&
		!dc->_hoops_RPSS[dc->_hoops_IASS])
		goto _hoops_HPAGR;

	switch (dc->_hoops_SHPGR) {
		case QMoves_Real_Overlay: {
			invalidate_cache (_hoops_CSRGR);
			if (_hoops_CSRGR->_hoops_GCHGC) {
				_hoops_CSRGR->_hoops_GCHGC = false;
				ENSURE_ZBUFFER_NOT_DISPLACED(_hoops_CSRGR,nr);
				glMatrixMode (GL_PROJECTION);
				glPopMatrix();
				glMatrixMode (GL_MODELVIEW);
				glPopMatrix();
			}
			FORCE_LIGHTS_OFF(_hoops_CSRGR);
#ifdef GLX_DRIVER
			_hoops_CSRGR->overlay._hoops_HIHGC = 1;
#	if defined(SOLARIS_SYSTEM)
			_hoops_CSRGR->overlay._hoops_HIHGC = SOLARIS_RESERVED_COLORS;
#	endif
#endif
			FORCE_DRAW_MODE (_hoops_CSRGR, DRAW_MODE_OVERLAY);
			HD_Standard_Draw_Overlay_List (nr);
			invalidate_cache (_hoops_CSRGR);
			if (_hoops_CSRGR->_hoops_GCHGC) {
				_hoops_CSRGR->_hoops_GCHGC = false;
				ENSURE_ZBUFFER_NOT_DISPLACED(_hoops_CSRGR,nr);
				glMatrixMode (GL_PROJECTION);
				glPopMatrix();
				glMatrixMode (GL_MODELVIEW);
				glPopMatrix();
			}
			FORCE_LIGHTS_OFF(_hoops_CSRGR);
			FORCE_DRAW_MODE (_hoops_CSRGR, DRAW_MODE_NORMAL);
		} break;

		case QMoves_Accumulation: {
			bool _hoops_RCHGC =
				XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_ACCUMULATION_BUFFER) ||
				(_hoops_CSRGR->_hoops_CRHGC && XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_16BIT_ACCUMULATION_BUFFER)) ||
				(_hoops_CSRGR->_hoops_AIPGA > 1 && XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_MSAA_ACCUMULATION_BUFFER)) ||
				dc->_hoops_RIGC->_hoops_HCPGR == 1;

			if (_hoops_RCHGC) {
				//_hoops_IRS _hoops_IAGIP-_hoops_IIHA _hoops_ACHGC _hoops_AAHRP _hoops_SRHR
				Int_Rectangle const * area = &nr->_hoops_SAIR->_hoops_SCIH;
				int w = area->right - area->left + 1;
				int h = area->top - area->bottom + 1;
				if (_hoops_CSRGR->_hoops_PCHGC &&
					(w != _hoops_CSRGR->_hoops_HCHGC ||
					 h != _hoops_CSRGR->_hoops_ICHGC)) {
					_hoops_ISPGR(dc->_hoops_SHCIP, _hoops_CSRGR->_hoops_PCHGC, _hoops_CSRGR->_hoops_CCHGC);
					_hoops_CSRGR->_hoops_PCHGC = null;
					_hoops_CSRGR->_hoops_CCHGC = null;
				}
				if (!_hoops_CSRGR->_hoops_PCHGC) {
					if (dc->_hoops_RIGC->_hoops_HCPGR != 1)
						create_region(nr, 0, (void **)&_hoops_CSRGR->_hoops_PCHGC, 0);
					else
						create_region(nr, 0, (void **)&_hoops_CSRGR->_hoops_PCHGC, (void **)&_hoops_CSRGR->_hoops_CCHGC);

					if (!_hoops_CSRGR->_hoops_PCHGC) {
						//_hoops_GASA _hoops_PIP: _hoops_GHAP _hoops_ACRR _hoops_RGR _hoops_AGIR _hoops_IS _hoops_SHH _hoops_SHRII _hoops_RAGII
						Display_Context alter *_hoops_HAPRH = (Display_Context alter *)dc;
						_hoops_HAPRH->_hoops_PGCC.flags |= _hoops_GIHSR;
						return;
					}
					_hoops_CSRGR->_hoops_HCHGC = w;
					_hoops_CSRGR->_hoops_ICHGC = h;
				}

				_hoops_HIPGR (nr, 0, _hoops_CSRGR->_hoops_PCHGC, _hoops_CSRGR->_hoops_CCHGC);

				if (BIT (_hoops_CSRGR->dc->options._hoops_IRARR, Debug_QMOVES_NO_ZDAMAGE)) {
					_hoops_HSIIP alter *si;

					if ((si = dc->_hoops_CHPGR) != null) do {
						si->nr.Modify()->transform_rendition.Modify();
						HD_Set_Z_Buffering_Transform (si->nr, false, false, 0.0f);
					} while ((si = si->next) != null);
				}
				else {
					glClear (GL_DEPTH_BUFFER_BIT);

					if (dc->_hoops_RIGC->_hoops_HCPGR != 1)
						dc->flags |= _hoops_ICPGR;
				}

			}
			else {
				//_hoops_IRS _hoops_HPHR _hoops_AAHRP _hoops_SRHR
				glClearAccum(0.0, 0.0, 0.0, 0.0);
				if (BIT (_hoops_CSRGR->dc->options._hoops_IRARR, Debug_QMOVES_NO_ZDAMAGE)) {
					_hoops_HSIIP alter *si;

					glClear (GL_ACCUM_BUFFER_BIT);
					if ((si = dc->_hoops_CHPGR) != null) do {
						si->nr.Modify()->transform_rendition.Modify();
						HD_Set_Z_Buffering_Transform (si->nr, false, false, 0.0f);
					} while ((si = si->next) != null);
				}
				else {
					glClear (GL_ACCUM_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
					dc->flags |= _hoops_ICPGR;
				}
				ENSURE_SCISSOR_OFF (_hoops_CSRGR);
				glAccum (GL_LOAD, 1.0f);

				if (_hoops_CSRGR->_hoops_PCHGC != null) {
					// _hoops_CICA _hoops_HII "_hoops_PAH'_hoops_RA _hoops_SGH" _hoops_IS "_hoops_PAH _hoops_SGH", _hoops_HIS _hoops_HASIR _hoops_GGPI
					_hoops_ISPGR(dc->_hoops_SHCIP, _hoops_CSRGR->_hoops_PCHGC, _hoops_CSRGR->_hoops_CCHGC);
					_hoops_CSRGR->_hoops_PCHGC = null;
					_hoops_CSRGR->_hoops_CCHGC = null;
				}

			}
			HD_Standard_Draw_Overlay_List (nr);
			DEBUG_FLUSH();
		} break;

		case QMoves_XOR: {
			glLogicOp (GL_XOR);
			glEnable (GL_COLOR_LOGIC_OP);
			_hoops_CSRGR->_hoops_CSC._hoops_SCHGC = true;
			_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;

			HD_Standard_Draw_Overlay_List (nr);

			glLogicOp (GL_SET);
			glDisable (GL_COLOR_LOGIC_OP);
			_hoops_CSRGR->_hoops_CSC._hoops_SCHGC = false;
		} break;

		case QMoves_Spriting: {
			/* _hoops_AA _hoops_ISAP.  _hoops_SCH'_hoops_GRI _hoops_GIR _hoops_GGR _hoops_CCPGR */
		} break;
	}

	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_CSRGR->_hoops_HCAC = _hoops_CCC;
	_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;
	_hoops_CSRGR->_hoops_RIPGR = true;
  _hoops_HPAGR:
	HD_Alternate_Hidden_Root (dc, _hoops_IHPGR);
}

local void
_hoops_SCPGR (Net_Rendition const & nr)
{
	Display_Context const *dc = nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	if (!_hoops_CSRGR->_hoops_RIPGR)
		return;

	switch (dc->_hoops_SHPGR) {
		case QMoves_Real_Overlay:
			_hoops_CIHGC (dc);
		break;

		case QMoves_Accumulation: {
			Int_Rectangle const *_hoops_GSHGC = &nr->_hoops_SAIR->_hoops_SCIH;
			if (dc->_hoops_RIGC->_hoops_HCPGR == 0 &&
				!BIT (_hoops_CSRGR->dc->options._hoops_IRARR, Debug_QMOVES_NO_ZDAMAGE)) {
				_hoops_CAAGR(nr,
					_hoops_GSHGC->left, _hoops_GSHGC->right,
					_hoops_GSHGC->bottom, _hoops_GSHGC->top);
			}
			ENSURE_SCISSOR_OFF (_hoops_CSRGR);
			glMatrixMode (GL_TEXTURE);
			glPushMatrix ();
			glLoadIdentity ();
			if (_hoops_CSRGR->_hoops_PCHGC)
				_hoops_PIPGR (nr, 0, _hoops_CSRGR->_hoops_PCHGC, _hoops_CSRGR->_hoops_CCHGC);
			else
				glAccum(GL_RETURN, 1.0);
			glPopMatrix ();
			glMatrixMode (GL_MODELVIEW);
			DEBUG_FLUSH();
		} break;

		case QMoves_XOR: {
			glLogicOp (GL_XOR);
			glEnable (GL_COLOR_LOGIC_OP);
			_hoops_CSRGR->_hoops_CSC._hoops_SCHGC = true;
			_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;
			if (_hoops_CSRGR->_hoops_SRRRR &&
				dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA) {
				/*_hoops_RSHGC (_hoops_HGPGA->_hoops_ASHGC->_hoops_PSHGC, _hoops_HSHGC)) { */
				glDrawBuffer (GL_FRONT);
				HD_Standard_UnDraw_Overlay_List (nr);
				glDrawBuffer (GL_BACK);
			}
			else
				HD_Standard_UnDraw_Overlay_List (nr);
			glLogicOp (GL_SET);
			glDisable (GL_COLOR_LOGIC_OP);
			_hoops_CSRGR->_hoops_CSC._hoops_SCHGC = false;
		} break;

		case QMoves_Spriting: {
			/* _hoops_AA _hoops_ISAP.  _hoops_SCH'_hoops_GRI _hoops_GIR _hoops_GGR _hoops_CCPGR */
		} break;
	}
	_hoops_CSRGR->_hoops_RIPGR = false;
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;
}


local void _hoops_ISHGC (Display_Context const * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	if (_hoops_CSRGR->_hoops_RIPGR && _hoops_CSRGR->_hoops_CSHGC)
		_hoops_CIHGC (dc);

	glDrawBuffer (GL_FRONT_AND_BACK);
	glClear (GL_COLOR_BUFFER_BIT);

	if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_SINGLE_BUFFERING))
		_hoops_CSRGR->_hoops_CSC._hoops_SSHGC = (_hoops_CSRGR->_hoops_SRRRR ? GL_BACK : GL_FRONT_AND_BACK);
	else _hoops_CSRGR->_hoops_CSC._hoops_SSHGC = (_hoops_CSRGR->_hoops_SRRRR ? GL_BACK : GL_FRONT);

	glDrawBuffer (_hoops_CSRGR->_hoops_CSC._hoops_SSHGC);
	glReadBuffer (_hoops_CSRGR->_hoops_CSC._hoops_SSHGC);

	glFlush ();
}

/*
 * _hoops_AHCR _hoops_SRHR _hoops_PGSI _hoops_PPR _hoops_RGCAH.
 */

/*
 * _hoops_SRAC
 */
local void
_hoops_CAAGR (Net_Rendition const & nr,
				int left, int right, int bottom, int top) {
	OGLData alter *_hoops_CSRGR = OGLNRD (nr);

 	_hoops_GGIGC (_hoops_CSRGR);
	ENSURE_SCISSOR_SET (_hoops_CSRGR, left, bottom, right - left + 1, top - bottom + 1);

	_hoops_RGIGC (_hoops_CSRGR, nr->transform_rendition->_hoops_RHPHP);

	/*_hoops_ACAC _hoops_PCAC _hoops_HPPA _hoops_IPPA _hoops_HIHP _hoops_CGPR _hoops_HIHP _hoops_SHPH*/
	_hoops_CSRGR->_hoops_HCAC = _hoops_CCC;
	_hoops_CSRGR->_hoops_ICAC = _hoops_CCC;

	/* _hoops_PSP _hoops_RRP _hoops_IS _hoops_AGSGR _hoops_GPP _hoops_AGIGC _hoops_IH _hoops_HSSGR... */
	ENSURE_DEPTH_MASK(_hoops_CSRGR, GL_TRUE);
	glClear (GL_DEPTH_BUFFER_BIT);
}


local void
_hoops_PGIGC (
		OGLData alter * _hoops_CSRGR,
		Net_Rendition	nr,
		int mode)
{
	float _hoops_RICR;
	float _hoops_AICR;

#if defined(IRIX_SYSTEM)
	/* _hoops_CPHP _hoops_AHCA _hoops_ISCP _hoops_RSAHH _hoops_IIGR _hoops_HSP _hoops_ISP _hoops_ASSP'_hoops_RA _hoops_HGIGC _hoops_CCA
		_hoops_GRCHH (_hoops_PAR _hoops_HPGR _hoops_CHGC _hoops_RH _hoops_IGIGC _hoops_SGS _hoops_SR _hoops_HS _hoops_GGR-_hoops_CGIGC) */
	if (mode == _hoops_SGIGC)
		mode = _hoops_GRIGC;
#endif
	if (nr && !BIT(nr->transform_rendition->flags, _hoops_PASP))
		mode = _hoops_RRIGC;

	/* _hoops_HGCR _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_RHGS _hoops_CCH */
	if (_hoops_CSRGR->_hoops_CSC._hoops_ARIGC != 0.0f) {
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode (GL_MODELVIEW);
		_hoops_CSRGR->_hoops_CSC._hoops_ARIGC = 0.0f;
	}
	else if (_hoops_CSRGR->_hoops_CSC._hoops_PRIGC == _hoops_RRIGC && mode != _hoops_RRIGC)
		glEnable (GL_DEPTH_TEST);

	/* _hoops_HGCR _hoops_CRGR _hoops_RH _hoops_CCAH _hoops_CCH */
	if (mode == _hoops_GRIGC || mode == _hoops_SGIGC) {

		_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
		float						_hoops_ARIGC = _hoops_IHCR->_hoops_SHIH;

		if (mode == _hoops_SGIGC)
			_hoops_ARIGC += _hoops_IHCR->_hoops_CHIH;

		if (_hoops_CSRGR->_hoops_CSC._hoops_HRIGC)
			_hoops_ARIGC += 1.0f;

		if (_hoops_ARIGC != 0.0f) {
			float _hoops_SRIR = _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			if (_hoops_CSRGR->_hoops_GCHGC)
				glTranslatef(0, 0, 1000.0 * _hoops_IHCR->_hoops_CHCR * _hoops_ARIGC);
			else
				glTranslatef(0, 0, -0.0001 * _hoops_SRIR * _hoops_ARIGC);
			glMatrixMode (GL_MODELVIEW);
		}
		if (!_hoops_CSRGR->_hoops_GCHGC) {
			_hoops_RICR = _hoops_IHCR->_hoops_GSCH[0];
			_hoops_AICR = _hoops_IHCR->_hoops_GSCH[1];
		}
		else {
			_hoops_RICR = 0;
			_hoops_AICR = 1;
		}
		_hoops_CSRGR->_hoops_CSC._hoops_ARIGC = _hoops_ARIGC;
	}
	else {
		/* _hoops_IRIGC _hoops_PAR _hoops_CRIGC */
		if (mode == _hoops_RRIGC) {
			if (_hoops_CSRGR->_hoops_CSC._hoops_PRIGC != _hoops_RRIGC)
				glDisable (GL_DEPTH_TEST);
			_hoops_RICR = _hoops_AICR = 0;
		}
		else {
			_hoops_RICR = 0;
			_hoops_AICR = 1;
		}
		_hoops_CSRGR->_hoops_CSC._hoops_ARIGC = 0;
	}

	if (_hoops_CSRGR->_hoops_CSC._hoops_GSCH[0] != _hoops_RICR ||
		_hoops_CSRGR->_hoops_CSC._hoops_GSCH[1] != _hoops_AICR) {
		glDepthRange(_hoops_RICR, _hoops_AICR);
		_hoops_CSRGR->_hoops_CSC._hoops_GSCH[0] = _hoops_RICR;
		_hoops_CSRGR->_hoops_CSC._hoops_GSCH[1] = _hoops_AICR;
	}

	_hoops_CSRGR->_hoops_CSC._hoops_PRIGC = mode;
}



/*_hoops_HGAPR _hoops_SRIGC _hoops_GAIGC _hoops_RAIGC _hoops_AAIGC _hoops_PAIGC _hoops_HAIGC*/
/*_hoops_IGPIP _hoops_ISCC _hoops_PAAAR _hoops_CARRI 3D _hoops_GCPAR _hoops_SHCA _hoops_IAIGC*/
struct concave_tri {
	/* _hoops_RIP _hoops_IH _hoops_ISRR _hoops_GHARR _hoops_IIGR _hoops_RSSA */
	bool _hoops_RPPH;
	bool _hoops_CAIGC;
	union
	{
		DC_Point const *dc;
		Point const *_hoops_GSPH;
	}
	points;
	int pattern;
	OGLData alter *_hoops_CSRGR;
	Driver_Color color;
	Driver_Color contrast_color;
	_hoops_ARCIH	_hoops_PSPH;
};


/*
 * _hoops_PGAA
 */
local void
_hoops_SAIGC (
				void *_hoops_PAPH,
				Integer32 _hoops_HAPH,
				Point const * p1, Point const * p2, Point const * _hoops_IAPH,
				Integer32 _hoops_ISPI, Integer32 _hoops_CSPI, Integer32 _hoops_SSPI,
				Intersection const * i1, Intersection const * i2, Intersection const * _hoops_SAPH)
{
	AGLM(OGLData alter *_hoops_CSRGR = ((struct concave_tri const *) _hoops_PAPH)->_hoops_CSRGR;)

	glBegin (GL_TRIANGLES);
		glVertex3fv ((GLfloat const *) p1);
		glVertex3fv ((GLfloat const *) p2);
		glVertex3fv ((GLfloat const *) _hoops_IAPH);
	glEnd ();

	UNREFERENCED(_hoops_PAPH);
	UNREFERENCED(_hoops_HAPH);
	UNREFERENCED(_hoops_ISPI);
	UNREFERENCED(_hoops_CSPI);
	UNREFERENCED(_hoops_SSPI);
	UNREFERENCED(i1);
	UNREFERENCED(i2);
	UNREFERENCED(_hoops_SAPH);
}


/*
 * _hoops_PGAA
 */
local void
callback_draw_triangle (
				void *_hoops_PAPH,
				Integer32 _hoops_HAPH,
				Point const * p1, Point const * p2, Point const * _hoops_IAPH,
				Integer32 _hoops_ISPI, Integer32 _hoops_CSPI, Integer32 _hoops_SSPI,
				Intersection const * i1, Intersection const * i2, Intersection const * _hoops_SAPH) {
	struct concave_tri const *_hoops_GPIGC = (struct concave_tri const *) _hoops_PAPH;
	int pattern = _hoops_GPIGC->pattern;
	OGLData alter *_hoops_CSRGR = _hoops_GPIGC->_hoops_CSRGR;
	Driver_Color const *color = &_hoops_GPIGC->color;
	Driver_Color const *contrast_color = &_hoops_GPIGC->contrast_color;

	glBegin (GL_TRIANGLES);
		glVertex3f (p1->x + 0.5f, p1->y + 0.5f, p1->z);
		glVertex3f (p2->x + 0.5f, p2->y + 0.5f, p2->z);
		glVertex3f (_hoops_IAPH->x + 0.5f, _hoops_IAPH->y + 0.5f, _hoops_IAPH->z);
	glEnd ();

	if (pattern != FP_SOLID) {
		glEnable (GL_POLYGON_STIPPLE);
		_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
		FORCE_COLOR (_hoops_CSRGR, contrast_color, false);
		ENSURE_FACE_PATTERN (_hoops_CSRGR, pattern);
		glBegin (GL_TRIANGLES);
			glVertex3f (p1->x + 0.5f, p1->y + 0.5f, p1->z);
			glVertex3f (p2->x + 0.5f, p2->y + 0.5f, p2->z);
			glVertex3f (_hoops_IAPH->x + 0.5f, _hoops_IAPH->y + 0.5f, _hoops_IAPH->z);
		glEnd ();
		glDisable (GL_POLYGON_STIPPLE);
		FORCE_COLOR (_hoops_CSRGR, color, false);
	}

	UNREFERENCED(_hoops_HAPH);
	UNREFERENCED(_hoops_ISPI);
	UNREFERENCED(_hoops_CSPI);
	UNREFERENCED(_hoops_SSPI);
	UNREFERENCED(i1);
	UNREFERENCED(i2);
	UNREFERENCED(_hoops_SAPH);
}

/*
 * _hoops_PGAA
 * _hoops_SIGP: _hoops_AISA _hoops_GHPH _hoops_HRGR _hoops_RHPH _hoops_IH _hoops_AHPH _hoops_ARAR
 * _hoops_PAGA: _hoops_RGR _hoops_CSAP _hoops_PHPH _hoops_CCA _hoops_RH _hoops_GHPH _hoops_SGS _hoops_HHPH _hoops_HRGR _hoops_IHPH _hoops_PPR _hoops_SGS
 * _hoops_SCH _hoops_HRGR _hoops_CHPH _hoops_IS _hoops_AA _hoops_AHPH _hoops_HAIR _hoops_SHPH _hoops_GIPH _hoops_GHGA _hoops_GPGR _hoops_RPIGC.	_hoops_HGI
 * _hoops_GHPH _hoops_GHCA _hoops_SHH _hoops_AIPH.  _hoops_PIPH _hoops_HIPH _hoops_IH _hoops_IIPH _hoops_CIPH!
 */
local void
draw_concave_face (Net_Rendition const & nr,
				   int count, struct concave_tri const * _hoops_SIPH) {
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	int _hoops_RPPH = _hoops_SIPH->_hoops_RPPH;
	Point alter *_hoops_GCPH;
	int alter *face_list;

	if (count == 0)
		return;

	/*
	 * _hoops_RAH _hoops_RH _hoops_HSP _hoops_HPP _hoops_RCPH _hoops_GGSR _hoops_IH _hoops_IRS _hoops_IHIR-_hoops_CSRA _hoops_HSSP
	 * _hoops_HHPH. _hoops_IPCP _hoops_ACPH _hoops_PCPH _hoops_PSCR _hoops_HCPH _hoops_RH
	 * _hoops_ICPH'_hoops_GRI _hoops_CCPH-_hoops_SCPH _hoops_PCPH.
	 */

	if (_hoops_RPPH) {
		_hoops_GCPH = (Point alter *)_hoops_SIPH->points.dc;

		/* _hoops_CSPH _hoops_RHAP _hoops_HAIR _hoops_ARI, _hoops_HIH _hoops_APSP _hoops_ASSP'_hoops_RA */
		if (!_hoops_SIPH->_hoops_CAIGC)
			_hoops_APIGC (_hoops_CSRGR, &_hoops_SIPH->color, nr);
	}
	else {
		_hoops_GCPH = (Point alter *)_hoops_SIPH->points._hoops_GSPH;
	}

	/* _hoops_GCRR _hoops_IRS _hoops_RSPH _hoops_HSP _hoops_HIGR */
	{
		int alter *_hoops_ASPH;
		int vertex;

		POOL_ALLOC_ARRAY_CACHED (_hoops_ASPH, count + 1, int, nr->_hoops_SRA->memory_pool);
		face_list = _hoops_ASPH;

		*_hoops_ASPH++ = count;
		vertex = 0;
		do
			*_hoops_ASPH++ = vertex;
		_hoops_RGGA (++vertex == count);
	}

	/*_hoops_SIGP: _hoops_GGI _hoops_IRS _hoops_IARI _hoops_PPR _hoops_SGH _hoops_SIRGR */
	/*
	 * _hoops_PAGA: _hoops_SCH _hoops_CHH _hoops_SHH _hoops_SPAC _hoops_RPP _hoops_SR _hoops_ACHGR _hoops_HCR _hoops_HIPH _hoops_CRGR _hoops_IRS _hoops_HIGR _hoops_PPR _hoops_IIAC _hoops_SPR _hoops_AASA _hoops_IS
	 * _hoops_PPIGC..._hoops_HIH _hoops_RGR _hoops_HRGR _hoops_HAR _hoops_IRS _hoops_PPCAR _hoops_AGIR _hoops_HIS _hoops_GA'_hoops_RA _hoops_HPIGC _hoops_GHIR _hoops_GPP _hoops_SCH..._hoops_GACC _hoops_IRHH
	 * _hoops_IGRI _hoops_SHPH _hoops_CRGR _hoops_AIRI _hoops_CPCI _hoops_GGR _hoops_IPIGC _hoops_PPR _hoops_SGH _hoops_CAPR _hoops_ARI...
	 */

	HI_Triangulate_Face_X (_hoops_GCPH, _hoops_RPPH ? &_hoops_IRGA::_hoops_IGHH : null, face_list,
						 face_list + count + 1, _hoops_SIPH->_hoops_PSPH,
						 (void alter *) _hoops_SIPH);

	FREE_ARRAY (face_list, count + 1, int);
}



/*
 * _hoops_PGAA
 */
local void
_hoops_CPIGC (OGLData alter * _hoops_CSRGR,
	_hoops_GPPA const *_hoops_RPPA) {

	GLdouble _hoops_SAPA[4];

	_hoops_CSRGR->_hoops_SPIGC = 0;

	do {
		_hoops_SAPA[0] = -_hoops_RPPA->_hoops_SPPA.a;
		_hoops_SAPA[1] = -_hoops_RPPA->_hoops_SPPA.b;
		_hoops_SAPA[2] = -_hoops_RPPA->_hoops_SPPA.c;
		_hoops_SAPA[3] = -_hoops_RPPA->_hoops_SPPA.d;
		if (_hoops_SAPA[3] == 0.0f)
		    _hoops_SAPA[3] = 1.0e-8f;
		glClipPlane (GL_CLIP_PLANE0+_hoops_CSRGR->_hoops_SPIGC, _hoops_SAPA);

		_hoops_CSRGR->_hoops_SPIGC++;
	} _hoops_RGGA ((_hoops_RPPA = _hoops_RPPA->next) == null);
}


/* _hoops_RAGA _hoops_IRS _hoops_HSPH _hoops_ISPH _hoops_PAPR _hoops_GGR _hoops_CSPH, _hoops_PGSA _hoops_SSPH _hoops_SHS */
local void _hoops_GGHH (Net_Rendition const &nr, _hoops_ASHH const *_hoops_PPGGA)
{
	OGLData *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	DC_Point const *pts = _hoops_PPGGA->points;
	int	count = _hoops_PPGGA->count;
	/* _hoops_RRP _hoops_IS _hoops_RGHH _hoops_AGHH _hoops_PGHH _hoops_ARI... */
	struct concave_tri _hoops_SIPH;
	DC_Point *buffer;
	int *face_list, *end;
	DC_Point _hoops_HGHH[4];
	int i;

	_hoops_HGHH[0].x = _hoops_IHCR->_hoops_AGAA.left - 2;
	_hoops_HGHH[0].y = _hoops_IHCR->_hoops_AGAA.bottom - 2;
	_hoops_HGHH[0].z = 0;
	_hoops_HGHH[1].x = _hoops_IHCR->_hoops_AGAA.left - 2;
	_hoops_HGHH[1].y = _hoops_IHCR->_hoops_AGAA.top + 2;
	_hoops_HGHH[1].z = 0;
	_hoops_HGHH[2].x = _hoops_IHCR->_hoops_AGAA.right + 2;
	_hoops_HGHH[2].y = _hoops_IHCR->_hoops_AGAA.top + 2;
	_hoops_HGHH[2].z = 0;
	_hoops_HGHH[3].x = _hoops_IHCR->_hoops_AGAA.right + 2;
	_hoops_HGHH[3].y = _hoops_IHCR->_hoops_AGAA.bottom - 2;
	_hoops_HGHH[3].z = 0;
	_hoops_SIPH.pattern = FP_SOLID;
	_hoops_SIPH._hoops_CSRGR = _hoops_CSRGR;
	_hoops_SIPH.color = _hoops_CAHSR::_hoops_SAHSR;
	_hoops_SIPH.contrast_color = _hoops_CAHSR::_hoops_SAHSR;
	_hoops_SIPH._hoops_PSPH = callback_draw_triangle;
	_hoops_SIPH._hoops_RPPH = true;
	_hoops_SIPH._hoops_CAIGC = true;

	ALLOC_ARRAY (buffer, count + 4, DC_Point);
	_hoops_AIGA (_hoops_HGHH, 4, DC_Point, buffer);
	_hoops_AIGA (pts, count, DC_Point, buffer+4);
	glStencilOp (GL_KEEP, GL_KEEP, GL_ZERO);

	ALLOC_ARRAY (face_list, count + 6, int);
	face_list[0] = 4;
	face_list[1] = 0;
	face_list[2] = 1;
	face_list[3] = 2;
	face_list[4] = 3;
	face_list[5] = -count;
	for (i = 0; i < count; i++) {
		face_list[i+6] = i+4;
	}
	_hoops_SIPH.points.dc = buffer;
	end = face_list + count + 6;
	HI_Triangulate_Face_X ((Point *)buffer, &_hoops_IRGA::_hoops_IGHH, face_list, end, callback_draw_triangle, &_hoops_SIPH);
	FREE_ARRAY (face_list, count + 6, int);
	FREE_ARRAY (buffer, count + 4, DC_Point);
}

/* _hoops_RAGA _hoops_IRS _hoops_HSPH _hoops_ISPH _hoops_PAPR _hoops_GGR _hoops_CSPH, _hoops_PGSA _hoops_RH _hoops_ISPH */
local void _hoops_CGHH (Net_Rendition const &nr, _hoops_ASHH const *_hoops_PPGGA)
{
	OGLData *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	DC_Point const *pts = _hoops_PPGGA->points;
	int	count = _hoops_PPGGA->count;
	/* _hoops_RRP _hoops_IS _hoops_RGHH _hoops_AGHH _hoops_PGHH _hoops_ARI... */
	struct concave_tri _hoops_SIPH;
	int *face_list, *end;
	int i;

	_hoops_SIPH.pattern = FP_SOLID;
	_hoops_SIPH._hoops_CSRGR = _hoops_CSRGR;
	_hoops_SIPH.color = _hoops_CAHSR::_hoops_SAHSR;
	_hoops_SIPH.contrast_color = _hoops_CAHSR::_hoops_SAHSR;
	_hoops_SIPH._hoops_PSPH = callback_draw_triangle;
	_hoops_SIPH._hoops_RPPH = true;
	_hoops_SIPH._hoops_CAIGC = true;

	glStencilOp (GL_KEEP,GL_KEEP, GL_ZERO);

	ALLOC_ARRAY (face_list, count+1, int);
	face_list[0] = count;
	for (i = 0; i < count; i++) {
		face_list[i+1] = i;
	}
	_hoops_SIPH.points.dc = pts;
	end = face_list + count + 1;
	HI_Triangulate_Face_X ((Point *)pts, &_hoops_IRGA::_hoops_IGHH, face_list, end, callback_draw_triangle, &_hoops_SIPH);
	FREE_ARRAY (face_list, count+1, int);
}



local void _hoops_GHIGC (OGLData alter * _hoops_CSRGR, Net_Rendition const & nr) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	bool						_hoops_RHIGC = _hoops_CSRGR->_hoops_CSC._hoops_APH;
	GLenum						_hoops_AHIGC = _hoops_CSRGR->_hoops_CSC._hoops_PHIGC;
	GLboolean					_hoops_CSHH, _hoops_ISHH;
	int 						_hoops_HHIGC;
	int 						_hoops_GGIH = 0, _hoops_AGIH = 0, _hoops_HGIH = 0;
	int 						_hoops_IHIGC = 0;
	bool						_hoops_CHIGC = false;

	_hoops_ASHH const *	_hoops_PPGGA = null;

	if (_hoops_IHCR->_hoops_HCHH)
		_hoops_PPGGA = _hoops_IHCR->_hoops_HCHH->_hoops_PSHH;

	if (_hoops_PPGGA == null) {
		if (_hoops_CSRGR->_hoops_SHIGC)
			return;
	}
	else {
		if (_hoops_PPGGA && _hoops_IHCR->_hoops_HCHH->_hoops_CPA == _hoops_CSRGR->_hoops_RSHH)
			return;
	}

	ENSURE_CULLING_OFF (_hoops_CSRGR);
	if (_hoops_CSRGR->_hoops_GIIGC) {
		glGetIntegerv (GL_STENCIL_FUNC, (GLint *)&_hoops_GGIH);
		glGetIntegerv (GL_STENCIL_VALUE_MASK, (GLint *)&_hoops_AGIH);
		glGetIntegerv (GL_STENCIL_REF, (GLint *)&_hoops_HGIH);
		glGetIntegerv (GL_STENCIL_PASS_DEPTH_PASS, (GLint *)&_hoops_IHIGC);
		_hoops_CHIGC = glIsEnabled (GL_FRAGMENT_PROGRAM_ARB) != 0;
		glDisable (GL_FRAGMENT_PROGRAM_ARB);
	}
	_hoops_ISHH = _hoops_CSRGR->_hoops_CSC._hoops_RAIH;
	_hoops_CSHH = _hoops_CSRGR->_hoops_CSC._hoops_AAIH;
	_hoops_HHIGC = _hoops_CSRGR->_hoops_CSC._hoops_PRIGC;
	_hoops_RPAP (_hoops_CSRGR, GL_FALSE);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, GL_FALSE);
	_hoops_RIIGC (_hoops_CSRGR);

	if (_hoops_PPGGA) {
		glStencilMask (0x80);
		glStencilFunc (GL_ALWAYS, 0x80, 0x80);
		glStencilOp (GL_KEEP, GL_KEEP, GL_REPLACE);

		/* _hoops_GCIH _hoops_APSP _hoops_SRHR _hoops_PSAP _hoops_CCA _hoops_RH _hoops_CASH _hoops_IGRH _hoops_ARP.
		   _hoops_HSRR _hoops_HSPH _hoops_PGHH, _hoops_SCAC _hoops_CPS _hoops_SIPP _hoops_GRR _hoops_ISPH.
		   _hoops_HSRR _hoops_PISH _hoops_PGHH, _hoops_SCAC _hoops_CPS _hoops_GIAA _hoops_GRR _hoops_ISPH. */

		ENSURE_STENCIL_ON (_hoops_CSRGR);

		glClearStencil(0x80);
		glClear (GL_STENCIL_BUFFER_BIT);

		if (_hoops_PPGGA) do {
			if (BIT (_hoops_PPGGA->flags, _hoops_RHIH))
				_hoops_CGHH (nr, _hoops_PPGGA);
			else
				_hoops_GGHH (nr, _hoops_PPGGA);
			DEBUG_FLUSH();
			_hoops_CSRGR->_hoops_SHIGC = false;
		} while ((_hoops_PPGGA = _hoops_PPGGA->next) != null);


		glStencilMask (0x00FF);
		if (_hoops_CSRGR->_hoops_GIIGC) {
			glStencilFunc (_hoops_GGIH, _hoops_HGIH, _hoops_AGIH);
			glStencilOp (GL_KEEP, GL_KEEP, _hoops_IHIGC);
			if (_hoops_CHIGC)
				glEnable (GL_FRAGMENT_PROGRAM_ARB);
		}
		else {
			glStencilFunc(GL_EQUAL, 0x80, 0x80);
			glStencilOp (GL_KEEP, GL_KEEP, GL_KEEP);
		}
	}

	_hoops_RPAP (_hoops_CSRGR, _hoops_ISHH);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, _hoops_CSHH);
	if (_hoops_CSRGR->_hoops_CSC._hoops_PRIGC == _hoops_GRIGC)
		_hoops_AIIGC (_hoops_CSRGR, nr);
	else if (_hoops_CSRGR->_hoops_CSC._hoops_PRIGC == _hoops_SGIGC)
		_hoops_PIIGC (_hoops_CSRGR, nr);
	if (_hoops_RHIGC)
		FORCE_CULLING (_hoops_CSRGR, _hoops_AHIGC);

	if (_hoops_IHCR->_hoops_HCHH)
		_hoops_CSRGR->_hoops_RSHH = _hoops_IHCR->_hoops_HCHH->_hoops_CPA;
	else
		_hoops_CSRGR->_hoops_SHIGC = true;
}


local void
_hoops_SAHH (OGLData alter * _hoops_CSRGR, Net_Rendition const & nr) {
	long						window_width = _hoops_CSRGR->window_width;
	long						window_height = _hoops_CSRGR->window_height;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Int_Rectangle const &		_hoops_GPHH = _hoops_IHCR->_hoops_AGAA;
	GLfloat						matrix[16];

	int _hoops_HIIGC = XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_SCISSORING);

	/*
	 * _hoops_IIIGC _hoops_HRGR 3D _hoops_HIH _hoops_CSPH _hoops_CIPH _hoops_HRGR _hoops_GGR _hoops_AIR _hoops_PCRR, _hoops_HIS _hoops_SR _hoops_HGSR _hoops_RH _hoops_ICIH _hoops_PPR _hoops_RSGA
	 * _hoops_HGPP _hoops_SGS _hoops_AIR _hoops_CPHH _hoops_CHR _hoops_IIS _hoops_RHIR _hoops_CIAH
	 */
	_hoops_CSRGR->_hoops_HCAC = _hoops_RARRR (_hoops_IHCR->_hoops_CPA);
	/* *_hoops_ACAC _hoops_PCAC _hoops_HPPA _hoops_IPPA _hoops_HIHP _hoops_CGPR _hoops_HIHP _hoops_SHPH _hoops_CIIGC
	 * _hoops_SIIGC _hoops_CAGRH _hoops_HIH _hoops_RRPS _hoops_IS _hoops_PIRGC _hoops_ACISR _hoops_RGR _hoops_GHCA _hoops_SHH _hoops_ARAH-_hoops_RRHAR.  _hoops_SGCH _hoops_CRGR
	 * _hoops_PCAC _hoops_HPPA _hoops_GHC _hoops_CRGP _hoops_AAGAI, _hoops_HIH _hoops_GCIGC _hoops_RCIGC.	 _hoops_ACIGC,
	 * _hoops_SR _hoops_CPCGP _hoops_RGAR _hoops_ARPP & _hoops_RAS _hoops_ASCA _hoops_IAPR _hoops_PCIGC _hoops_HIH _hoops_RPGGI _hoops_SGS
	 * _hoops_CSAP _hoops_HAR _hoops_CHIS. */
	_hoops_CSRGR->_hoops_ICAC = _hoops_CCC;

	ENSURE_FOG_OFF(_hoops_CSRGR, nr);
	ENSURE_CULLING_OFF (_hoops_CSRGR);
	_hoops_HCIGC (_hoops_CSRGR);

	if (_hoops_CSRGR->_hoops_CSC._hoops_SSHGC == GL_BACK)
		_hoops_RGIGC (_hoops_CSRGR, _hoops_IHCR->_hoops_RHPHP);

	if (_hoops_HIIGC) {
		/* _hoops_PCHC _hoops_CSSC _hoops_IIGR _hoops_CPAP _hoops_CHR _hoops_HAR _hoops_PRRP _hoops_ICIGC _hoops_HPP _hoops_HRRPI _hoops_CHPPR _hoops_ICCGR _hoops_PIRGC */
		ENSURE_VIEWPORT_SET(_hoops_CSRGR,
			_hoops_GPHH.left, _hoops_GPHH.bottom,
			_hoops_GPHH.right - _hoops_GPHH.left + 1, _hoops_GPHH.top - _hoops_GPHH.bottom + 1);
	}
	else {
		ENSURE_VIEWPORT_SET(_hoops_CSRGR, 0, 0, window_width, window_height);
	}

	if (0/*_hoops_IRRC (_hoops_CPSP->_hoops_SGI, _hoops_CCIGC)*/) {
		ENSURE_SCISSOR_OFF (_hoops_CSRGR);
		ENSURE_CLIP_VOLUME_HINT(_hoops_CSRGR, GL_FASTEST);
	}
	else {
		_hoops_GGIGC (_hoops_CSRGR);
		ENSURE_SCISSOR_SET (_hoops_CSRGR,_hoops_GPHH.left, _hoops_GPHH.bottom,
									_hoops_GPHH.right - _hoops_GPHH.left + 1,
									_hoops_GPHH.top - _hoops_GPHH.bottom + 1);
		ENSURE_CLIP_VOLUME_HINT(_hoops_CSRGR, GL_DONT_CARE);
	}

	if (!_hoops_CSRGR->_hoops_GCHGC) {
		_hoops_SCIGC (_hoops_CSRGR);
		ENSURE_ZBUFFER_NOT_DISPLACED(_hoops_CSRGR,nr);
		glMatrixMode (GL_PROJECTION);
		glPushMatrix();
		glMatrixMode (GL_MODELVIEW);
		glPushMatrix();
		_hoops_CSRGR->_hoops_CSC._hoops_GSCH[0] = _hoops_IACIR;  /* _hoops_HRCI */
	}

	if (window_width < 1)
		window_width = 1;
	if (window_height < 1)
		window_height = 1;

	if (!_hoops_CSRGR->_hoops_GCHGC ||
		window_width != _hoops_CSRGR->_hoops_GPAGC ||
		window_height != _hoops_CSRGR->_hoops_RPAGC ||
		_hoops_CSRGR->_hoops_GSGRR ||
		_hoops_CSRGR->_hoops_GSIGC != BIT(_hoops_IHCR->flags, _hoops_PASP)) {
		glLoadIdentity();		/* _hoops_GSGA */

		/* _hoops_GPGP _hoops_HIHH, _hoops_RH _hoops_PHCR _hoops_RSGA _hoops_HRGR _hoops_PCPA _hoops_APPP _hoops_CGSI _hoops_HII _hoops_RHC _hoops_PCRR _hoops_PPR
		 * _hoops_CHAAI _hoops_CAPR _hoops_CRGR _hoops_IRS -1.0 _hoops_IS 1.0 _hoops_ASRH.  _hoops_CPGP _hoops_AGAH _hoops_CHAAI _hoops_CGSI _hoops_CRGR _hoops_AIR
		 * _hoops_PCRR _hoops_AIAH _hoops_IH _hoops_CSPH _hoops_CIPH _hoops_PPR _hoops_HIHH _hoops_RGAR _hoops_IHIGR _hoops_IHHH _hoops_IS _hoops_SSSS
		 * _hoops_CGSI _hoops_GGR _hoops_CARA _hoops_GC _hoops_SR _hoops_PIHA _hoops_PAISR _hoops_RH _hoops_AGAH _hoops_AIR _hoops_PCRR _hoops_PPR
		 * _hoops_PPSI _hoops_CAPR _hoops_CRGR _hoops_IRS -1.0 _hoops_IS 1.0 _hoops_ASRH.  _hoops_ICAGR _hoops_PPRRR _hoops_IS _hoops_AA _hoops_RGR _hoops_HRGR _hoops_IS _hoops_CSRA _hoops_PPR
		 * _hoops_PHCH _hoops_AIH _hoops_RH _hoops_PHCR _hoops_RSGA.
		 */
		ENSURE_ZBUFFER_NOT_DISPLACED(_hoops_CSRGR,nr);
		glMatrixMode (GL_PROJECTION);
		matrix[0] = (GLfloat) (2.0 / window_width);
		matrix[1] = (GLfloat) 0;
		matrix[2] = (GLfloat) 0;
		matrix[3] = (GLfloat) 0;
		matrix[4] = (GLfloat) 0;
		matrix[5] = (GLfloat) (2.0 / window_height);
		matrix[6] = (GLfloat) 0;
		matrix[7] = (GLfloat) 0;
		matrix[8] = (GLfloat) 0;
		matrix[9] = (GLfloat) 0;
		matrix[10] = (GLfloat) (2.0 / _hoops_IHCR->_hoops_PCHH);
		matrix[11] = (GLfloat) 0;
		matrix[12] = (GLfloat) - 1;
		matrix[13] = (GLfloat) - 1;
		matrix[14] = (GLfloat) - 1;
		matrix[15] = (GLfloat) 1;
		if (_hoops_HIIGC) {
			matrix[0] = (GLfloat) (2.0 / (_hoops_GPHH.right - _hoops_GPHH.left + 1));
			matrix[5] = (GLfloat) (2.0 / (_hoops_GPHH.top - _hoops_GPHH.bottom + 1));
			matrix[12] = (GLfloat) - 1 - _hoops_GPHH.left * matrix[0];
			matrix[13] = (GLfloat) - 1 - _hoops_GPHH.bottom * matrix[5];
		}
		if ((_hoops_CSRGR->_hoops_CSC._hoops_GGAGC == DRAW_MODE_OVERLAY) || !BIT(_hoops_IHCR->flags, _hoops_PASP)) {
			matrix[14] = (GLfloat) 0;
			matrix[10] = (GLfloat) 1e-10;
		}
		glLoadMatrixf (matrix);
		glMatrixMode (GL_MODELVIEW);
		_hoops_CSRGR->_hoops_GSIGC = BIT(_hoops_IHCR->flags, _hoops_PASP);
	}
	/* _hoops_AGCR _hoops_PAH _hoops_PAHH _hoops_SHH _hoops_RIPPR _hoops_ASSA _hoops_RH _hoops_ARRS _hoops_RIS */
	_hoops_CSRGR->_hoops_GCHGC = true;
	_hoops_CSRGR->_hoops_GPAGC  = (int) window_width;
	_hoops_CSRGR->_hoops_RPAGC = (int) window_height;

	if (_hoops_IHCR->_hoops_HCHH != null) {
		ENSURE_STENCIL_ON (_hoops_CSRGR);
		if (_hoops_IHCR->_hoops_HCHH != null && _hoops_CSRGR->_hoops_RSHH != _hoops_IHCR->_hoops_HCHH->_hoops_CPA)
			_hoops_GHIGC (_hoops_CSRGR, nr);
	}
	else {
		if (!_hoops_CSRGR->_hoops_GIIGC)
			_hoops_RSIGC (_hoops_CSRGR);
		else {
			_hoops_GHIGC (_hoops_CSRGR, nr); //_hoops_SCAC _hoops_RH _hoops_APSP
			ENSURE_STENCIL_ON (_hoops_CSRGR);
		}
	}
}



/*
 * _hoops_PGAA
 */
local void
_hoops_ASIGC (float m[][4]) {
	if (m[0][0] * m[1][1] * m[2][2] +
		m[0][1] * m[1][2] * m[2][0] +
		m[0][2] * m[1][0] * m[2][1] -
		m[0][2] * m[1][1] * m[2][0] -
		m[0][1] * m[1][0] * m[2][2] -
		m[0][0] * m[1][2] * m[2][1] == 0.0f) {
		float max, _hoops_PSIGC;

#define _hoops_HSIGC(a, b) (Abs(a) > Abs(b) ? Abs(a) : Abs(b))

		max = Abs (m[0][0]);
		_hoops_PSIGC = _hoops_HSIGC (m[0][1], m[0][2]);
		if (max < _hoops_PSIGC)
			max = _hoops_PSIGC;
		_hoops_PSIGC = _hoops_HSIGC (m[1][0], m[1][1]);
		if (max < _hoops_PSIGC)
			max = _hoops_PSIGC;
		_hoops_PSIGC = _hoops_HSIGC (m[1][2], m[2][0]);
		if (max < _hoops_PSIGC)
			max = _hoops_PSIGC;
		_hoops_PSIGC = _hoops_HSIGC (m[2][1], m[2][2]);
		if (max < _hoops_PSIGC)
			max = _hoops_PSIGC;

#undef _hoops_HSIGC

		max *= 0.001f;

		m[0][0] += max;
		m[0][1] += max;
		m[0][2] += max;
		m[1][0] += max;
		m[1][1] += max;
		m[1][2] += max;
		m[2][0] += max;
		m[2][1] += max;
		m[2][2] += max;
	}
}


/*
 * _hoops_PGAA
 * _hoops_HSCP _hoops_SGS _hoops_ISCP _hoops_PIRGC _hoops_PIAP _hoops_SSCP _hoops_RH _hoops_GGSP _hoops_HRP _hoops_IH
 *	 _hoops_IRS) _hoops_PGCR _hoops_RPSA _hoops_RCA,
 *	 _hoops_RCSR) _hoops_ISIGC
 *	 _hoops_GSGGR) _hoops_CSIGC
 */
local void
_hoops_AGSP (OGLData alter * _hoops_CSRGR,
				_hoops_HHCR const & _hoops_IHCR,
				int flags)
{
	bool _hoops_SSIGC = false;
	bool _hoops_HGSP;
	int heuristics = _hoops_IHCR->heuristics;

	if (!BIT (_hoops_IHCR->matrix->data.flags, _hoops_HASA))
		HI_Validate_Matrix_NEG3X3((_hoops_HRPA alter *)&_hoops_IHCR->matrix->data);

	bool _hoops_IASA = BIT (_hoops_IHCR->matrix->data._hoops_RAGR, _hoops_CASA);

	if (_hoops_CSRGR->_hoops_GGCGC)
		_hoops_IASA = !_hoops_IASA;


	if (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI)) {
		/* "_hoops_PRP _hoops_ASGA" _hoops_HRGR _hoops_PCCP _hoops_CCGHA _hoops_HCSP _hoops_IS _hoops_GSRS
		 * _hoops_GSSR _hoops_RGAP _hoops_RH _hoops_PSHR _hoops_PPRRR _hoops_GAR _hoops_PIIHR _hoops_AGAH _hoops_IRSP.
		 * _hoops_HHIGR _hoops_IISA _hoops_HPGR _hoops_IRS _hoops_HSRAP _hoops_AIPP _hoops_PPR _hoops_HRGR _hoops_HAR _hoops_RIRA _hoops_IH _hoops_CCAH _hoops_RRGR.
		 */
		ENSURE_TWO_SIDED (_hoops_CSRGR, GL_FALSE);
		ENSURE_CULLING_OFF (_hoops_CSRGR);
		return;
	}
	else if (BIT (flags,_hoops_RGCGC)) {
		_hoops_HGSP = true;
		if (BIT (flags,_hoops_AGCGC))
			heuristics ^= _hoops_RSA;
	}
	else if (BIT (_hoops_IHCR->flags, _hoops_SPP)) {
		_hoops_HGSP = true;
		_hoops_SSIGC = true;
	}
	else {
		_hoops_HGSP = BIT (_hoops_IHCR->flags, _hoops_IGSP);
		if (!_hoops_HGSP &&
			ANYBIT (heuristics, _hoops_RSA))
			_hoops_SSIGC = true;
	}

	if (_hoops_IASA) {
		if (BIT (heuristics, _hoops_SASA)) {
			if (_hoops_SSIGC) {
				if (!BIT(_hoops_CSRGR->dc->options._hoops_IRARR,_hoops_SIAAH))
					ENSURE_TWO_SIDED (_hoops_CSRGR, GL_TRUE);
				ENSURE_FRONT_FACE (_hoops_CSRGR, GL_CW);
				if (_hoops_HGSP)
					_hoops_RHSA (_hoops_CSRGR, GL_BACK);
				else
					ENSURE_CULLING_OFF (_hoops_CSRGR);
			}
			else {
				ENSURE_TWO_SIDED (_hoops_CSRGR, GL_FALSE);
				ENSURE_FRONT_FACE (_hoops_CSRGR, GL_CW);
				if (_hoops_HGSP)
					_hoops_RHSA (_hoops_CSRGR, GL_BACK);
				else
					ENSURE_CULLING_OFF (_hoops_CSRGR);
			}
		}
		else if (BIT (heuristics, _hoops_GPSA)) {
			if (_hoops_SSIGC) {
				if (!BIT(_hoops_CSRGR->dc->options._hoops_IRARR,_hoops_SIAAH))
					ENSURE_TWO_SIDED (_hoops_CSRGR, GL_TRUE);
				ENSURE_FRONT_FACE (_hoops_CSRGR, GL_CCW);
				if (_hoops_HGSP)
					_hoops_RHSA (_hoops_CSRGR, GL_FRONT);
				else
					ENSURE_CULLING_OFF (_hoops_CSRGR);
			}
			else {
				ENSURE_TWO_SIDED (_hoops_CSRGR, GL_FALSE);
				ENSURE_FRONT_FACE (_hoops_CSRGR, GL_CW);
				if (_hoops_HGSP)
					_hoops_RHSA (_hoops_CSRGR, GL_FRONT);
				else
					ENSURE_CULLING_OFF (_hoops_CSRGR);
			}
		}
		else {					/* _hoops_RSSP _hoops_HAR _hoops_ARP */
			ENSURE_TWO_SIDED (_hoops_CSRGR, GL_FALSE);
			ENSURE_CULLING_OFF (_hoops_CSRGR);
		}
	}
	else {						/* _hoops_PGCGC */

		if (BIT (heuristics, _hoops_SASA)) {
			if (_hoops_SSIGC) {
				if (!BIT(_hoops_CSRGR->dc->options._hoops_IRARR,_hoops_SIAAH))
					ENSURE_TWO_SIDED (_hoops_CSRGR, GL_TRUE);
				ENSURE_FRONT_FACE (_hoops_CSRGR, GL_CCW);
				if (_hoops_HGSP)
					_hoops_RHSA (_hoops_CSRGR, GL_BACK);
				else
					ENSURE_CULLING_OFF (_hoops_CSRGR);
			}
			else {
				ENSURE_TWO_SIDED (_hoops_CSRGR, GL_FALSE);
				ENSURE_FRONT_FACE (_hoops_CSRGR, GL_CCW);
				if (_hoops_HGSP)
					_hoops_RHSA (_hoops_CSRGR, GL_BACK);
				else
					ENSURE_CULLING_OFF (_hoops_CSRGR);
			}
		}
		else if (BIT (heuristics, _hoops_GPSA)) {
			if (_hoops_SSIGC) {
				if (!BIT(_hoops_CSRGR->dc->options._hoops_IRARR,_hoops_SIAAH))
					ENSURE_TWO_SIDED (_hoops_CSRGR, GL_TRUE);
				ENSURE_FRONT_FACE (_hoops_CSRGR, GL_CW);
				if (_hoops_HGSP)
					_hoops_RHSA (_hoops_CSRGR, GL_FRONT);
				else
					ENSURE_CULLING_OFF (_hoops_CSRGR);
			}
			else {
				ENSURE_TWO_SIDED (_hoops_CSRGR, GL_FALSE);
				ENSURE_FRONT_FACE (_hoops_CSRGR, GL_CCW);
				if (_hoops_HGSP)
					_hoops_RHSA (_hoops_CSRGR, GL_FRONT);
				else
					ENSURE_CULLING_OFF (_hoops_CSRGR);
			}
		}
		else {					/* _hoops_RSSP _hoops_HAR _hoops_ARP */

			ENSURE_TWO_SIDED (_hoops_CSRGR, GL_FALSE);
			ENSURE_CULLING_OFF (_hoops_CSRGR);
		}
	}
}


/*
 * _hoops_PGAA
 */
local void
_hoops_HGCGC (OGLData alter * _hoops_CSRGR,
					   _hoops_GPPA const *_hoops_RPPA) {

	GLdouble _hoops_SAPA[4];

	_hoops_HCIGC (_hoops_CSRGR);
	_hoops_CSRGR->_hoops_SPIGC = 0;
	if (!_hoops_CSRGR->_hoops_IICH) {
		glPushMatrix ();
		glLoadMatrixf (_hoops_CSRGR->_hoops_CIRGC);
	}

	do {
		_hoops_SAPA[0] = -_hoops_RPPA->_hoops_SHPA.a;
		_hoops_SAPA[1] = -_hoops_RPPA->_hoops_SHPA.b;
		_hoops_SAPA[2] = -_hoops_RPPA->_hoops_SHPA.c;
		_hoops_SAPA[3] = -_hoops_RPPA->_hoops_SHPA.d;
		if (_hoops_SAPA[3] == 0.0f)
		    _hoops_SAPA[3] = 1.0e-8f;
		glClipPlane (GL_CLIP_PLANE0+_hoops_CSRGR->_hoops_SPIGC, _hoops_SAPA);

		_hoops_CSRGR->_hoops_SPIGC++;
	} _hoops_RGGA ((_hoops_RPPA = _hoops_RPPA->next) == null);

	if (!_hoops_CSRGR->_hoops_IICH) {
		glPopMatrix ();
	}
	_hoops_IGCGC (_hoops_CSRGR);
}


/*
 * _hoops_PGAA
 */
local void
_hoops_GIIH (
	OGLData alter *				_hoops_CSRGR,
	Net_Rendition const &		nr) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Display_Context const *		dc = nr->_hoops_SRA;
	bool 						_hoops_SARC;
	bool 						_hoops_CGCGC;
	float 						gl_projection_matrix[4][4];
	float 						_hoops_PIIH, _hoops_HIIH;
	long 						_hoops_IIIH;
	long 						_hoops_SIIH;
	bool 						_hoops_RIIH = false;
	Point						_hoops_PPCH = _hoops_HPCH::_hoops_IPCH, _hoops_CPCH = _hoops_HPCH::_hoops_IPCH;
	int 						_hoops_SCHH = _hoops_CSRGR->window_width;
	int 						_hoops_GSHH = _hoops_CSRGR->window_height;
	Int_Rectangle				extent;
	float						_hoops_ISIH;

	_hoops_CSRGR->_hoops_HCAC = _hoops_PARRR (_hoops_IHCR->_hoops_CPA);
	/* *_hoops_ACAC _hoops_PCAC _hoops_HPPA _hoops_IPPA _hoops_HIHP _hoops_CGPR _hoops_HIHP _hoops_SHPH _hoops_CIIGC
	 * _hoops_SIIGC _hoops_CAGRH _hoops_HIH _hoops_RRPS _hoops_IS _hoops_PIRGC _hoops_ACISR _hoops_RGR _hoops_GHCA _hoops_SHH _hoops_ARAH-_hoops_RRHAR.  _hoops_SGCH _hoops_CRGR
	 * _hoops_PCAC _hoops_HPPA _hoops_GHC _hoops_CRGP _hoops_AAGAI, _hoops_HIH _hoops_GCIGC _hoops_RCIGC.	 _hoops_ACIGC,
	 * _hoops_SR _hoops_CPCGP _hoops_RGAR _hoops_ARPP & _hoops_RAS _hoops_ASCA _hoops_IAPR _hoops_PCIGC _hoops_HIH _hoops_RPGGI _hoops_SGS
	 * _hoops_CSAP _hoops_HAR _hoops_CHIS. */
	_hoops_CSRGR->_hoops_ICAC = _hoops_CCC;
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;

	_hoops_RGIGC (_hoops_CSRGR, _hoops_IHCR->_hoops_RHPHP);

	_hoops_SGCGC (_hoops_CSRGR);

	_hoops_SARC = BIT (_hoops_IHCR->flags, _hoops_PRIR);
	_hoops_CGCGC = BIT (_hoops_IHCR->flags, _hoops_RCRIP);

	/*_hoops_GRCGC _hoops_RRCGC _hoops_HAPCA _hoops_ARCGC*/
	if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH)) {
		ENSURE_FOG_ON(_hoops_CSRGR, nr);
	}
	else {
		ENSURE_FOG_OFF(_hoops_CSRGR, nr);
	}

	if (0/*_hoops_IRRC (_hoops_CPSP->_hoops_SGI, _hoops_CCIGC)*/) {
		ENSURE_SCISSOR_OFF (_hoops_CSRGR);
		ENSURE_CLIP_VOLUME_HINT(_hoops_CSRGR, GL_FASTEST);
	}
	else {
		_hoops_GGIGC (_hoops_CSRGR);
		ENSURE_SCISSOR_SET (_hoops_CSRGR, _hoops_IHCR->_hoops_AGAA.left, _hoops_IHCR->_hoops_AGAA.bottom,
							_hoops_IHCR->_hoops_AGAA.right - _hoops_IHCR->_hoops_AGAA.left + 1,
							_hoops_IHCR->_hoops_AGAA.top - _hoops_IHCR->_hoops_AGAA.bottom + 1);
		ENSURE_CLIP_VOLUME_HINT(_hoops_CSRGR, GL_DONT_CARE);
	}

	if (_hoops_SCHH < 1)
		_hoops_SCHH = 1;
	if (_hoops_GSHH < 1)
		_hoops_GSHH = 1;

	if (_hoops_IHCR->_hoops_HCHH != null) {
		ENSURE_STENCIL_ON (_hoops_CSRGR);
		if (_hoops_CSRGR->_hoops_RSHH != _hoops_IHCR->_hoops_HCHH->_hoops_CPA) {
			Int_Rectangle const &	_hoops_GPHH = _hoops_IHCR->_hoops_AGAA;
			int						_hoops_HIIGC = XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_SCISSORING);
			long					window_width = _hoops_SCHH;
			long					window_height = _hoops_GSHH;

			if (_hoops_HIIGC) {
				/* _hoops_PCHC _hoops_CSSC _hoops_IIGR _hoops_CPAP _hoops_CHR _hoops_HAR _hoops_PRRP _hoops_ICIGC _hoops_HPP _hoops_HRRPI _hoops_CHPPR _hoops_ICCGR _hoops_PIRGC */
				ENSURE_VIEWPORT_SET(_hoops_CSRGR,
					_hoops_GPHH.left, _hoops_GPHH.bottom,
					_hoops_GPHH.right - _hoops_GPHH.left + 1, _hoops_GPHH.top - _hoops_GPHH.bottom + 1);
			}
			else {
				ENSURE_VIEWPORT_SET(_hoops_CSRGR, 0, 0, window_width, window_height);
			}

			/* _hoops_RRP _hoops_IRS _hoops_IRHP _hoops_CICA _hoops_IS _hoops_PRCGC _hoops_ARI... _hoops_PHPHA _hoops_HII _hoops_ARP _hoops_CSPH _hoops_HPPPI */
			if (!_hoops_CSRGR->_hoops_GCHGC) {
				ENSURE_ZBUFFER_NOT_DISPLACED(_hoops_CSRGR,nr);
				glMatrixMode (GL_PROJECTION);
				glPushMatrix();
				glMatrixMode (GL_MODELVIEW);
				glPushMatrix();
			}
			/* _hoops_SHR _hoops_APGP _hoops_HRCGC, _hoops_PSP _hoops_RRP _hoops_IH _hoops_IRCGC _hoops_RSAIP _hoops_ARI*/
			if (!_hoops_CSRGR->_hoops_GCHGC ||
				window_width != _hoops_CSRGR->_hoops_GPAGC ||
				window_height != _hoops_CSRGR->_hoops_RPAGC ||
				_hoops_CSRGR->_hoops_GSGRR) {
				GLfloat matrix[16];

				ENSURE_ZBUFFER_NOT_DISPLACED(_hoops_CSRGR,nr);
				glMatrixMode (GL_PROJECTION);
				matrix[0] = (GLfloat) (2.0 / window_width);
				matrix[1] = (GLfloat) 0;
				matrix[2] = (GLfloat) 0;
				matrix[3] = (GLfloat) 0;
				matrix[4] = (GLfloat) 0;
				matrix[5] = (GLfloat) (2.0 / window_height);
				matrix[6] = (GLfloat) 0;
				matrix[7] = (GLfloat) 0;
				matrix[8] = (GLfloat) 0;
				matrix[9] = (GLfloat) 0;
#if defined(IRIX_SYSTEM)
/* _hoops_CRCGC _hoops_SRCGC _hoops_PAH'_hoops_RA _hoops_RGHH _hoops_PCCHI _hoops_PHCR _hoops_HCIA _hoops_CCA _hoops_GRCHH _hoops_PIIHR _hoops_IS 6.5.13 */
				matrix[10] = (GLfloat) 1e-30;
#else
				matrix[10] = (GLfloat) 0;
#endif
				matrix[11] = (GLfloat) 0;
				matrix[12] = (GLfloat) - 1;
				matrix[13] = (GLfloat) - 1;
				matrix[14] = (GLfloat) 0;
				matrix[15] = (GLfloat) 1;
				if (_hoops_HIIGC) {
					matrix[0] = (GLfloat) (2.0 / (_hoops_GPHH.right - _hoops_GPHH.left + 1));
					matrix[5] = (GLfloat) (2.0 / (_hoops_GPHH.top - _hoops_GPHH.bottom + 1));
					matrix[12] = (GLfloat) - 1 - _hoops_GPHH.left * matrix[0];
					matrix[13] = (GLfloat) - 1 - _hoops_GPHH.bottom * matrix[5];
				}
				glLoadMatrixf (matrix);

				glMatrixMode (GL_MODELVIEW);
				glLoadIdentity();

			}
			_hoops_CSRGR->_hoops_GCHGC = true;
			_hoops_CSRGR->_hoops_GPAGC  = (int) window_width;
			_hoops_CSRGR->_hoops_RPAGC = (int) window_height;

			_hoops_GHIGC (_hoops_CSRGR, nr);
		}
	}
	else {
		if (!_hoops_CSRGR->_hoops_GIIGC)
			_hoops_RSIGC (_hoops_CSRGR);
		else {
			_hoops_GHIGC (_hoops_CSRGR, nr);  //_hoops_SCAC _hoops_RH _hoops_APSP
			ENSURE_STENCIL_ON (_hoops_CSRGR);
		}
	}

	if (_hoops_CSRGR->_hoops_GIIGC) {
		 if (!_hoops_IHCR->_hoops_HCHH ) {
			  int _hoops_IRIH;
			  glGetIntegerv(GL_STENCIL_WRITEMASK, (GLint*)(&_hoops_IRIH));

			  glStencilMask(0x0080);
			  glClearStencil(0x0080);
			  glClear(GL_STENCIL_BUFFER_BIT);

			  glStencilMask(_hoops_IRIH);
		 }
	 }

	if (_hoops_CSRGR->_hoops_GCHGC) {
		_hoops_CSRGR->_hoops_GCHGC = false;
		_hoops_SCIGC (_hoops_CSRGR);
		ENSURE_ZBUFFER_NOT_DISPLACED(_hoops_CSRGR,nr);
		glMatrixMode (GL_PROJECTION);
		glPopMatrix();
		glMatrixMode (GL_MODELVIEW);
		glPopMatrix();
		_hoops_CSRGR->_hoops_CSC._hoops_GSCH[0] = _hoops_IACIR;  /* _hoops_HRCI */
	}

	_hoops_IIIH = _hoops_SGRA->_hoops_CIIH.right - _hoops_SGRA->_hoops_CIIH.left;
	_hoops_SIIH = _hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom;

	extent.left = _hoops_SGRA->_hoops_CIIH.left +
				(int)(0.5f * (_hoops_IHCR->_hoops_HCIH.left - -1.0f) * _hoops_IIIH);
	extent.right = _hoops_SGRA->_hoops_CIIH.left +
				(int)(0.5f * (_hoops_IHCR->_hoops_HCIH.right - -1.0f) * _hoops_IIIH);
	extent.bottom = _hoops_SGRA->_hoops_CIIH.bottom +
				(int)(0.5f * (_hoops_IHCR->_hoops_HCIH.bottom - -1.0f) * _hoops_SIIH);
	extent.top = _hoops_SGRA->_hoops_CIIH.bottom +
				(int)(0.5f * (_hoops_IHCR->_hoops_HCIH.top - -1.0f) * _hoops_SIIH);

	_hoops_IIIH = extent.right - extent.left;
	_hoops_SIIH = extent.top - extent.bottom;


	if (_hoops_IIIH > dc->_hoops_PGCC._hoops_PRPSR.x ||
		_hoops_SIIH > dc->_hoops_PGCC._hoops_PRPSR.y)
			_hoops_RIIH = true;


	_hoops_ISIH = _hoops_SGRA->_hoops_CSIH * (_hoops_IHCR->_hoops_HCIH.top - _hoops_IHCR->_hoops_HCIH.bottom) /
								 (_hoops_IHCR->_hoops_HCIH.right - _hoops_IHCR->_hoops_HCIH.left);

	if (_hoops_IIIH != _hoops_CSRGR->_hoops_IIIH ||
		_hoops_SIIH != _hoops_CSRGR->_hoops_SIIH ||
		_hoops_IHCR->_hoops_SPH != _hoops_CSRGR->_hoops_CARGC ||
		_hoops_IHCR->_hoops_CHCR != _hoops_CSRGR->_hoops_SAAGC ||
		_hoops_ISIH != _hoops_CSRGR->_hoops_CSIH ||
		BIT (_hoops_IHCR->flags, _hoops_PGCH) != _hoops_CSRGR->_hoops_GACGC ||
		(_hoops_IHCR->_hoops_RHPHP == _hoops_HHPHP && _hoops_CSRGR->_hoops_CSC._hoops_CHHCR != _hoops_IHCR->_hoops_ACSRP ||
		 _hoops_IHCR->_hoops_RHPHP == _hoops_PHPHP && _hoops_CSRGR->_hoops_CSC._hoops_CHHCR != -_hoops_IHCR->_hoops_ACSRP)) {

		_hoops_CSRGR->_hoops_CSIH = _hoops_ISIH;
		_hoops_CSRGR->_hoops_GACGC = BIT (_hoops_IHCR->flags, _hoops_PGCH);

		/* _hoops_AA _hoops_RH _hoops_SIHP _hoops_PAR _hoops_AIHP _hoops_HAPRR _hoops_GGR _hoops_RHC _hoops_GC--_hoops_RACGC _hoops_AACGC! */
		ENSURE_ZBUFFER_NOT_DISPLACED(_hoops_CSRGR,nr);
		glMatrixMode (GL_PROJECTION);
		_hoops_PIIH = _hoops_HIIH = 1.0f;

		if (_hoops_IHCR->_hoops_SPH->projection != _hoops_SSIH) {
			if (_hoops_ISIH <= _hoops_IHCR->_hoops_SPH->_hoops_CSIH)
				_hoops_PIIH = _hoops_ISIH / _hoops_IHCR->_hoops_SPH->_hoops_CSIH;
			else
				_hoops_HIIH = _hoops_IHCR->_hoops_SPH->_hoops_CSIH / _hoops_ISIH;
		}

		if (BIT (_hoops_IHCR->flags, _hoops_PGCH))
			_hoops_PIIH = -_hoops_PIIH;

		/* _hoops_HIHH _hoops_RHAP _hoops_ASAI _hoops_RGHH _hoops_PACGC _hoops_APPR _hoops_HSAR _hoops_RH _hoops_RIHRR _hoops_SHPR...
		 * _hoops_SR _hoops_HS _hoops_IS _hoops_RSPH _hoops_AGAP _hoops_CAIR _hoops_CCA _hoops_IRS _hoops_CSRA _hoops_PPR _hoops_PHCH.
		 */
		if (_hoops_RIIH) {
			float _hoops_HACGC;	/* _hoops_IACGC _hoops_IIGR _hoops_IGAA */
			float _hoops_CACGC;

			_hoops_HACGC = 1.0f / _hoops_SCHH;
			_hoops_CACGC = 1.0f / _hoops_GSHH;

			_hoops_PPCH.x = _hoops_IIIH * _hoops_HACGC;
			_hoops_PPCH.y = _hoops_SIIH * _hoops_CACGC;

			_hoops_CPCH.x = (extent.right + extent.left) * _hoops_HACGC - 1.0f;
			_hoops_CPCH.y = (extent.top + extent.bottom) * _hoops_CACGC - 1.0f;
		}

		gl_projection_matrix[0][0] = 2.0f * _hoops_PIIH / _hoops_IHCR->_hoops_SPH->_hoops_ISPA;
		gl_projection_matrix[0][1] = 0.0f;
		gl_projection_matrix[0][2] = 0.0f;
		gl_projection_matrix[0][3] = 0.0f;

		gl_projection_matrix[1][0] = 0.0f;
		gl_projection_matrix[1][1] = 2.0f * _hoops_HIIH / _hoops_IHCR->_hoops_SPH->_hoops_SSPA;
		gl_projection_matrix[1][2] = 0.0f;
		gl_projection_matrix[1][3] = 0.0f;

		if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
			gl_projection_matrix[2][0] = 0.0f;
			gl_projection_matrix[2][1] = 0.0f;
			gl_projection_matrix[2][2] = -1.0f / _hoops_IHCR->_hoops_SPH->_hoops_SRIR;
			gl_projection_matrix[2][3] = -1.0f / _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

			gl_projection_matrix[3][0] = 0.0f;
			gl_projection_matrix[3][1] = 0.0f;
			gl_projection_matrix[3][2] = -2.0f * _hoops_IHCR->_hoops_CHCR;
			gl_projection_matrix[3][3] = 0.0f;


			if (_hoops_IHCR->_hoops_RHPHP != _hoops_AHPHP) {
				float			_hoops_CHHCR = 0.0f;
				float			_hoops_GGHCR, _hoops_AGHCR;

				switch (nr->transform_rendition->_hoops_RHPHP) {
					case _hoops_PHPHP:
						_hoops_CHHCR = -_hoops_IHCR->_hoops_ACSRP;
						break;
					case _hoops_HHPHP:
						_hoops_CHHCR =  _hoops_IHCR->_hoops_ACSRP;
						break;
				}
				_hoops_CSRGR->_hoops_CSC._hoops_CHHCR = _hoops_CHHCR;

				_hoops_RICH (_hoops_CHHCR, _hoops_GGHCR, _hoops_AGHCR);

				if (_hoops_AGHCR != 0.0f) {
					/* _hoops_HAR _hoops_RCRR _hoops_GPP _hoops_AGCR, _hoops_HIH _hoops_SCH'_hoops_GRI _hoops_GGR _hoops_RH _hoops_SACGC */
					float			_hoops_HIC = _hoops_GGHCR/_hoops_AGHCR;
					/*_hoops_SPRS		_hoops_AIIC			_hoops_GPCGC = 0.5f * _hoops_CPSP->_hoops_SARA->_hoops_ACPCR;*/

					gl_projection_matrix[2][0] = 2.0f * _hoops_HIC / _hoops_IHCR->_hoops_SPH->_hoops_SRIR;
					gl_projection_matrix[3][0] = 2.0f * _hoops_HIC;
				}
			}
			else
				_hoops_CSRGR->_hoops_CSC._hoops_CHHCR = 0.0f;
		}
		else {
			/* _hoops_ARCH _hoops_PPR _hoops_RPCGC */

			gl_projection_matrix[2][0] = 0.0f;
			gl_projection_matrix[2][1] = 0.0f;
			gl_projection_matrix[2][2] = -2.0f * _hoops_IHCR->_hoops_CHCR / (2*_hoops_IHCR->_hoops_SPH->_hoops_SRIR);
			gl_projection_matrix[2][3] = 0.0f;

			gl_projection_matrix[3][0] = 0.0f;
			gl_projection_matrix[3][1] = 0.0f;
			gl_projection_matrix[3][2] = 0.0f;
			gl_projection_matrix[3][3] = 1.0f;
		}

		/* _hoops_CPGP _hoops_RGR _hoops_CCIH _hoops_AGIR _hoops_HRGR _hoops_RAGII _hoops_GHAP _hoops_RHCA _hoops_SCH _hoops_HRGR _hoops_GIH _hoops_IS _hoops_AA _hoops_IRS _hoops_ISPR _hoops_ARI _hoops_HRII _hoops_HSAR
		 * _hoops_APCGC _hoops_AIAA _hoops_IHH _hoops_SRRRH _hoops_CRGR _hoops_RH _hoops_ARRS _hoops_RSGA _hoops_RRGR.
		 */
		if (_hoops_RIIH) {
			gl_projection_matrix[0][0] *= _hoops_PPCH.x;
			gl_projection_matrix[1][1] *= _hoops_PPCH.y;

			gl_projection_matrix[2][0] = gl_projection_matrix[2][3] * _hoops_CPCH.x;
			gl_projection_matrix[2][1] = gl_projection_matrix[2][3] * _hoops_CPCH.y;

			gl_projection_matrix[3][0] = gl_projection_matrix[3][3] * _hoops_CPCH.x;
			gl_projection_matrix[3][1] = gl_projection_matrix[3][3] * _hoops_CPCH.y;
		}

		glLoadMatrixf ((GLfloat const *) &gl_projection_matrix[0][0]);

		if ((_hoops_IHCR->_hoops_RHPHP != _hoops_AHPHP) && (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)) {
			float translate[4][4];
			float _hoops_CHCH[4][4];
			float _hoops_CGSIR = _hoops_IHCR->_hoops_PCSRP;
			float			_hoops_CHHCR = 0.0f;
			float			_hoops_GGHCR, _hoops_AGHCR;


			switch (nr->transform_rendition->_hoops_RHPHP) {
				case _hoops_PHPHP:
					_hoops_CHHCR = -_hoops_IHCR->_hoops_ACSRP;
					break;
				case _hoops_HHPHP:
					_hoops_CHHCR =  _hoops_IHCR->_hoops_ACSRP;
					break;
			}
			_hoops_CSRGR->_hoops_CSC._hoops_CHHCR = _hoops_CHHCR;

			_hoops_RICH (_hoops_CHHCR, _hoops_GGHCR, _hoops_AGHCR);

			if (_hoops_AGHCR != 0.0f) {
				/* _hoops_HAR _hoops_RCRR _hoops_GPP _hoops_AGCR, _hoops_HIH _hoops_SCH'_hoops_GRI _hoops_GGR _hoops_RH _hoops_SACGC */
				float			_hoops_HIC = _hoops_GGHCR/_hoops_AGHCR;
				/*_hoops_SPRS		_hoops_AIIC			_hoops_PPCGC = 1.0f; */
				/*_hoops_SPRS		_hoops_AIIC			_hoops_GPCGC = 0.5f * _hoops_CPSP->_hoops_SARA->_hoops_ACPCR;*/

				translate[0][0] = 1.0f;
				translate[0][1] = 0.0f;
				translate[0][2] = 0.0f;
				translate[0][3] = 0.0f;

				translate[1][0] = 0.0f;
				translate[1][1] = 1.0f;
				translate[1][2] = 0.0f;
				translate[1][3] = 0.0f;

				translate[2][0] = 0.0f;
				translate[2][1] = 0.0f;
				translate[2][2] = 1.0f;
				translate[2][3] = 0.0f;

				translate[3][0] = 0.0f;
				translate[3][1] = 0.0f;
				translate[3][2] = (float)(-_hoops_CGSIR - _hoops_IHCR->_hoops_SPH->_hoops_SRIR);
				translate[3][3] = 1.0f;

				_hoops_CHCH[0][0] = 1.0f;
				_hoops_CHCH[0][1] = 0.0f;
				_hoops_CHCH[0][2] = 0.0f;
				_hoops_CHCH[0][3] = 0.0f;

				_hoops_CHCH[1][0] = 0.0f;
				_hoops_CHCH[1][1] = 1.0f;
				_hoops_CHCH[1][2] = 0.0f;
				_hoops_CHCH[1][3] = 0.0f;

				_hoops_CHCH[2][0] = _hoops_HIC;
				_hoops_CHCH[2][1] = 0.0f;
				_hoops_CHCH[2][2] = 1.0f;
				_hoops_CHCH[2][3] = 0.0f;

				_hoops_CHCH[3][0] = 0.0f;
				_hoops_CHCH[3][1] = 0.0f;
				_hoops_CHCH[3][2] = 0.0f;
				_hoops_CHCH[3][3] = 1.0f;

				glMultMatrixf((GLfloat const *)&translate[0][0]);
				glMultMatrixf ((GLfloat const *)&_hoops_CHCH[0][0]);
				translate[3][2] = (float)(_hoops_CGSIR + _hoops_IHCR->_hoops_SPH->_hoops_SRIR);
				glMultMatrixf((GLfloat const *)&translate[0][0]);
			}

		}

		if (_hoops_IHCR->_hoops_SPH->_hoops_HHCH != 0.0f || _hoops_IHCR->_hoops_SPH->_hoops_IHCH != 0.0f) {
			float			_hoops_CHCH[4][4];
			float			_hoops_SHCH, _hoops_GICH;

			HI_Ident_44 (&_hoops_CHCH[0][0]);
			if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)
				_hoops_CHCH[3][2] += _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

			_hoops_RICH (_hoops_IHCR->_hoops_SPH->_hoops_HHCH, _hoops_SHCH, _hoops_GICH);
			if (_hoops_GICH != 0.0f) {
				/*
				 * _hoops_IPCP _hoops_HSPR _hoops_HRGR _hoops_APGP _hoops_IRS _hoops_SAICR _hoops_IIGR _hoops_IRS 4-_hoops_HPP-3 _hoops_HPP
				 *
				 *	  1		0	  0		0
				 *	  0		1	  0		0
				 *	  _hoops_PAICR 0	  1		0
				 *	  0		0	  0		1
				 *
				 * _hoops_GPICR _hoops_IIHA _hoops_GPP _hoops_PCPA _hoops_SR _hoops_ACPA _hoops_AHCA _hoops_RH _hoops_CIIA
				 */
				_hoops_CHCH[2][0] -= _hoops_SHCH/_hoops_GICH;
				_hoops_CHCH[3][0] -= _hoops_SHCH/_hoops_GICH * _hoops_CHCH[3][2];
			}

			_hoops_RICH (_hoops_IHCR->_hoops_SPH->_hoops_IHCH, _hoops_SHCH, _hoops_GICH);
			if (_hoops_GICH != 0.0f) {
				/*
				 * _hoops_RPICR _hoops_GAR _hoops_ARRS, _hoops_GRP
				 *
				 *	  1		0	  0		0
				 *	  0		1	  0		0
				 *	  0		_hoops_PAICR 1		0
				 *	  0		0	  0		1
				 */
				_hoops_CHCH[2][1] -= _hoops_SHCH/_hoops_GICH;
				_hoops_CHCH[3][1] -= _hoops_SHCH/_hoops_GICH * _hoops_CHCH[3][2];
			}
			if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)
				_hoops_CHCH[3][2] -= _hoops_IHCR->_hoops_SPH->_hoops_SRIR;

			glMultMatrixf ((GLfloat const *)&_hoops_CHCH[0][0]);
		}

		_hoops_CSRGR->_hoops_PPAGC = false;
		glMatrixMode (GL_MODELVIEW);
	}

	if (_hoops_IHCR->_hoops_SPH != _hoops_CSRGR->_hoops_CARGC ||
		_hoops_IHCR->_hoops_IPH->_hoops_CPA != _hoops_CSRGR->_hoops_APAGC) {
		_hoops_CSRGR->_hoops_APAGC = _hoops_IHCR->_hoops_IPH->_hoops_CPA;
		/*
		 * _hoops_HIHH _hoops_RSGA _hoops_HCPH _hoops_CHR _hoops_CPHR _hoops_GGR _hoops_RH _hoops_PIIA _hoops_AGR. _hoops_PS _hoops_HHGC _hoops_IS _hoops_AA
		 * _hoops_CARA _hoops_GC _hoops_SCAAI _hoops_SRS _hoops_PPR _hoops_PSCR _hoops_RH _hoops_GSSP _hoops_IS _hoops_RHC
		 * _hoops_GC _hoops_HAPRR.  _hoops_HGI _hoops_AGSR _hoops_SR _hoops_HGSR _hoops_RH _hoops_GSSP _hoops_IS _hoops_RHC _hoops_GC
		 * _hoops_RSGA _hoops_ARI _hoops_PPR _hoops_AA _hoops_RH _hoops_SICH _hoops_CIPH _hoops_CGHI.
		 */
		HI_Copy_43 (&_hoops_IHCR->_hoops_SPH->_hoops_PRPA.elements[0][0],
					_hoops_CSRGR->_hoops_CIRGC);

		/* _hoops_AA _hoops_RH _hoops_RSSP _hoops_AGRP _hoops_PPR _hoops_RH _hoops_SARA _hoops_HICH (0 _hoops_IS -5) */
		_hoops_CSRGR->_hoops_CIRGC[2] = -_hoops_CSRGR->_hoops_CIRGC[2];
		_hoops_CSRGR->_hoops_CIRGC[6] = -_hoops_CSRGR->_hoops_CIRGC[6];
		_hoops_CSRGR->_hoops_CIRGC[10] = -_hoops_CSRGR->_hoops_CIRGC[10];
		_hoops_CSRGR->_hoops_CIRGC[14] = -_hoops_CSRGR->_hoops_CIRGC[14];

		if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH)
			_hoops_CSRGR->_hoops_CIRGC[14] -= _hoops_IHCR->_hoops_SPH->_hoops_SRIR;


		_hoops_CSRGR->_hoops_IICH =
			!ANYBIT (_hoops_IHCR->_hoops_IPH->data._hoops_RAGR,
					 _hoops_CICH);

		if (!_hoops_CSRGR->_hoops_IICH) {
			HI_Matmul_44_by_44 (&_hoops_IHCR->_hoops_IPH->data.elements[0][0],
								_hoops_CSRGR->_hoops_CIRGC, &_hoops_CSRGR->_hoops_HPCGC[0][0]);
			/*
			 * _hoops_ARGH _hoops_IH _hoops_PCCHI _hoops_RSGA, _hoops_PGGA _hoops_IPCGC _hoops_RAIA _hoops_RH _hoops_AGICR
			 * _hoops_HRII _hoops_HSAR _hoops_RH _hoops_GGRA _hoops_GGR _hoops_RH _hoops_RCA _hoops_IISRR.
			 */
			if (_hoops_IHCR->_hoops_IPH->data._hoops_CPH == 0.0f &&
				(_hoops_CGCGC || _hoops_SARC)) {
				_hoops_ASIGC (_hoops_CSRGR->_hoops_HPCGC);
			}
			glLoadMatrixf (&_hoops_CSRGR->_hoops_HPCGC[0][0]);
		}
		else {
			/* _hoops_SGH _hoops_ICCH _hoops_RSGA _hoops_RIIA _hoops_IIGR _hoops_GSGA _hoops_PPR _hoops_SRCH _hoops_CCCH */
			glLoadMatrixf (_hoops_CSRGR->_hoops_CIRGC);
		}
		_hoops_CSRGR->_hoops_PPAGC = false;
	}

	_hoops_CSRGR->_hoops_IIIH = _hoops_IIIH;
	_hoops_CSRGR->_hoops_SIIH = _hoops_SIIH;
	_hoops_CSRGR->_hoops_CARGC = _hoops_IHCR->_hoops_SPH;
	_hoops_CSRGR->_hoops_SAAGC = _hoops_IHCR->_hoops_CHCR;

	if (_hoops_SARC) {
		if (_hoops_IHCR->_hoops_IPH->data._hoops_CPH != 1.0f)
			ENSURE_NORMALIZE_ON (_hoops_CSRGR);
		else
			_hoops_CPCGC (_hoops_CSRGR);
	}
	else {
		_hoops_CPCGC (_hoops_CSRGR);
	}
	if (_hoops_RIIH) {
		ENSURE_VIEWPORT_SET(_hoops_CSRGR, 0, 0, _hoops_SCHH, _hoops_GSHH);
	}
	else {
		ENSURE_VIEWPORT_SET(_hoops_CSRGR,
							extent.left, extent.bottom,
							extent.right - extent.left + 1,
							extent.top - extent.bottom + 1);
	}

	OGL_SET_HANDEDNESS (_hoops_CSRGR, _hoops_IHCR, 0);
}		/* _hoops_RSGR _hoops_API _hoops_SPCGC */


#if 0
/*
 * _hoops_PGAA (_hoops_CAPGR _hoops_HII _hoops_PIRGC)
 */
local void
_hoops_GHCGC (GLenum error_code) {
#if 0
	const char *_hoops_RHCGC;
	_hoops_RHCGC = gluErrorString (error_code);
	/* _hoops_HGGC _hoops_RRP _hoops_IS _hoops_AA _hoops_CPHP _hoops_CCA _hoops_RGR _hoops_GSGR */
#else
		UNREFERENCED(error_code);
#endif
}
#endif

/*
 * _hoops_PGAA
 */
local void
_hoops_AHCGC (OGLData alter * _hoops_CSRGR) {
	_hoops_CSRGR->_hoops_PHCGC._hoops_GIIH						= _hoops_GIIH;
	_hoops_CSRGR->_hoops_PHCGC._hoops_SAHH						= _hoops_SAHH;
	_hoops_CSRGR->_hoops_PHCGC._hoops_AHRGC						= _hoops_AHRGC;
	_hoops_CSRGR->_hoops_PHCGC._hoops_GHRGC					= _hoops_GHRGC;
	_hoops_CSRGR->_hoops_PHCGC._hoops_AGSP						= _hoops_AGSP;
	_hoops_CSRGR->_hoops_PHCGC.set_line_rendition					= set_line_rendition;
	_hoops_CSRGR->_hoops_PHCGC._hoops_HHCGC						= _hoops_HHCGC;
	_hoops_CSRGR->_hoops_PHCGC._hoops_IHCGC		= _hoops_IHCGC;
	_hoops_CSRGR->_hoops_PHCGC._hoops_RIHGC					= _hoops_RIHGC;
	_hoops_CSRGR->_hoops_PHCGC._hoops_PIGH						= _hoops_PIGH;
	_hoops_CSRGR->_hoops_PHCGC._hoops_GHAH		= _hoops_GHAH;


	_hoops_CSRGR->_hoops_ACPGR._hoops_GIIH						= _hoops_GIIH;
	_hoops_CSRGR->_hoops_ACPGR._hoops_SAHH						= _hoops_SAHH;
	_hoops_CSRGR->_hoops_ACPGR._hoops_AHRGC						= _hoops_AHRGC;
	_hoops_CSRGR->_hoops_ACPGR._hoops_GHRGC					= _hoops_GHRGC;
	_hoops_CSRGR->_hoops_ACPGR._hoops_AGSP						= _hoops_AGSP;
	_hoops_CSRGR->_hoops_ACPGR.set_line_rendition					= set_line_rendition;
	_hoops_CSRGR->_hoops_ACPGR._hoops_HHCGC						= _hoops_HHCGC;
	_hoops_CSRGR->_hoops_ACPGR._hoops_IHCGC		= _hoops_IHCGC;
	_hoops_CSRGR->_hoops_ACPGR._hoops_RIHGC					= _hoops_RIHGC;
	_hoops_CSRGR->_hoops_ACPGR._hoops_PIGH						= _hoops_PIGH;
	_hoops_CSRGR->_hoops_ACPGR._hoops_GHAH		= _hoops_GHAH;
}

/*
 *	_hoops_PGAA
 */
local void
_hoops_CHCGC (Display_Context alter * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	_hoops_CSRGR->dc = dc;

	_hoops_AHCGC(_hoops_CSRGR);

	invalidate_cache (_hoops_CSRGR);

	_hoops_CSRGR->_hoops_GSPGC = false;
	_hoops_CSRGR->_hoops_RSPGC = false;
	_hoops_CSRGR->_hoops_GGHGC = false;

	_hoops_CSRGR->_hoops_SHCGC = false;
	_hoops_CSRGR->_hoops_RAHGC = false;
	_hoops_CSRGR->_hoops_PAHGC = false;

	_hoops_CSRGR->_hoops_PHHGC = false;
	_hoops_CSRGR->_hoops_IARGC = false;
	_hoops_CSRGR->_hoops_ACPGC = false;
	_hoops_CSRGR->_hoops_SPIGC = 0;
	_hoops_CSRGR->_hoops_GICGC = false;
	_hoops_CSRGR->_hoops_CSHGC = false;
	_hoops_CSRGR->_hoops_GAHGC = 0;

	_hoops_CSRGR->_hoops_PHAI = OGL_POLYMARKER_BATCH_SIZE;

	_hoops_CSRGR->_hoops_CHRGC = 0;
	_hoops_CSRGR->_hoops_SARGC = _hoops_RHRGC;
	ZERO_ARRAY(_hoops_CSRGR->_hoops_GIRGC, 32, bool);
	if (_hoops_CSRGR->_hoops_PRARR)
		HI_Free_Driver_Config(_hoops_CSRGR->_hoops_PRARR);

	_hoops_RGAIR(dc->_hoops_PGCC._hoops_GSPGH);
	_hoops_RGAIR(dc->_hoops_PGCC._hoops_RSPGH);
	HI_Copy_Chars_To_Name("DEFAULT", &dc->_hoops_PGCC._hoops_GSPGH);
	HI_Copy_Chars_To_Name("*", &dc->_hoops_PGCC._hoops_RSPGH);
	dc->_hoops_PGCC._hoops_PRARR = _hoops_CSRGR->_hoops_PRARR = HI_Lookup_Driver_Config(dc->_hoops_RIGC, "opengl", "DEFAULT", "*", true, _hoops_RSPRH);

}



/*
 * _hoops_PGAA
 * _hoops_HIS _hoops_SGS _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IS _hoops_RICGC _hoops_AICGC' _hoops_CIGS _hoops_SHIR _hoops_HSH,
 * _hoops_PPSI _hoops_ISCP _hoops_HAII _hoops_HSSPR _hoops_HSH _hoops_CRGR _hoops_HCR _hoops_ICCI _hoops_PIAP
 */
local void
_hoops_PICGC (Display_Context alter * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	_hoops_IAHGC ((Display_Context alter *) dc);

	/* _hoops_PAIA */
	_hoops_HSGGC ((Display_Context alter *) dc);

	glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
	glClearStencil (0);
	_hoops_CSRGR->_hoops_CSC._hoops_GPIR._hoops_HRIR.r = 255;
	_hoops_CSRGR->_hoops_CSC._hoops_GPIR._hoops_HRIR.g = 255;
	_hoops_CSRGR->_hoops_CSC._hoops_GPIR._hoops_HRIR.b = 255;
	_hoops_CSRGR->_hoops_CSC._hoops_GPIR._hoops_HRIR.a = 255;
	glClearDepth (1.0f);

	/*_hoops_HCIC _hoops_RGR _hoops_SSRR _hoops_SGIPR? _hoops_HICGC (_hoops_IICGC);*/

	FORCE_SCISSOR_OFF (_hoops_CSRGR);
	_hoops_CICGC (_hoops_CSRGR);
	FORCE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);

	/* _hoops_IIAH _hoops_RGAR _hoops_RPP _hoops_RPSP _hoops_HRGR _hoops_GSHHR! */
	FORCE_BLEND_FUNC(_hoops_CSRGR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_hoops_SICGC(_hoops_CSRGR);
	_hoops_CIAP(_hoops_CSRGR, GL_TRUE);
	/* _hoops_RAS _hoops_GCCGC _hoops_RCCGC */
	_hoops_ACCGC (_hoops_CSRGR);

	_hoops_SGCGC (_hoops_CSRGR);
	_hoops_PCCGC(_hoops_CSRGR, GL_CCW);
	_hoops_HCCGC(_hoops_CSRGR, GL_FALSE);

	_hoops_CSRGR->_hoops_CSC._hoops_PRIGC = _hoops_RRIGC;
	FORCE_DEPTH_FUNCTION (_hoops_CSRGR, GL_LEQUAL);
	_hoops_AHPRR (_hoops_CSRGR, false);
	_hoops_CPPRR (_hoops_CSRGR, false);

	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

	FORCE_LIGHTS_OFF (_hoops_CSRGR);

	/* _hoops_AGSGR _hoops_GPP _hoops_IAPRR _hoops_IH _hoops_ISSC _hoops_RSSI */
	FORCE_CULLING (_hoops_CSRGR, GL_BACK);
	/* _hoops_HHSP _hoops_IAPRR, _hoops_HIH _hoops_PCSA _hoops_SGS _hoops_ISSC _hoops_RSSI _hoops_CHR _hoops_RH _hoops_SHIR */
	_hoops_ICCGC (_hoops_CSRGR);

	_hoops_CCCGC (_hoops_CSRGR, GL_FRONT_AND_BACK);
	_hoops_SCCGC (_hoops_CSRGR);

	glPixelStorei (GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	_hoops_CSRGR->_hoops_CSC._hoops_SCHGC = false;
	_hoops_CSRGR->_hoops_CSC._hoops_PSAH = _hoops_RSARR;
	_hoops_CSRGR->_hoops_CSC._hoops_GSCGC = _hoops_RSARR;
	_hoops_CSRGR->_hoops_CSC._hoops_HAACP._hoops_HPRGC = _hoops_RSARR;

#ifdef GLX_DRIVER
#ifdef SOLARIS_SYSTEM
	_hoops_CSRGR->overlay._hoops_HIHGC = SOLARIS_RESERVED_COLORS;
#else
	_hoops_CSRGR->overlay._hoops_HIHGC = 1; /* 0 _hoops_HRGR _hoops_SHR _hoops_RRH _hoops_PAR _hoops_HIS _hoops_HHH _hoops_SPR _hoops_RSCGC*/
#endif
#endif

	_hoops_ASCGC (_hoops_CSRGR, _hoops_AHPHP);
	_hoops_CSRGR->_hoops_CSC._hoops_CHHCR = 0.0f;
	_hoops_CSRGR->_hoops_CSC._hoops_SSHGC = GL_BACK;


#ifndef _hoops_SCIGI
	if (BIT (_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_PSAAH))
#endif
		/*_hoops_SHIR _hoops_SCAC _hoops_HRGR _hoops_PGS */
		glClearColor (0.0, 0.0, 0.0, 1.0);
	if (!BIT (_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_PSCGC))
		_hoops_ISHGC (dc);
	glClearColor (1.0, 1.0, 1.0, 1.0);

	/* _hoops_HSCGC _hoops_GIGR _hoops_ISCGC _hoops_CSAP _hoops_IS _hoops_SGH _hoops_RH _hoops_HSPR _hoops_IAPGR _hoops_GGSR _hoops_APGR
	 * _hoops_IS _hoops_IRHH _hoops_RH _hoops_HGPGA->_hoops_PPPHH _hoops_PSSP _hoops_AAPA-_hoops_PAPA.  _hoops_HHIGR _hoops_ASSP'_hoops_RA _hoops_IPHR, _hoops_PHRI.	_hoops_PIRGC'_hoops_GRI
	 * _hoops_GRRC _hoops_CHR _hoops_SCIPA _hoops_GRP _hoops_AGCR _hoops_HRPRA, _hoops_HIS _hoops_SR _hoops_RIIA _hoops_CSCGC _hoops_SGS
	 * _hoops_AGIS _hoops_SGHC _hoops_GRS _hoops_SHH _hoops_PSP _hoops_RPIP _hoops_HSAR 5 _hoops_ASPA.	_hoops_AHIPR _hoops_AHPP _hoops_IS _hoops_SHH _hoops_RAPR
	 * _hoops_SSCGC (_hoops_HGPGA->_hoops_PPPHH, _hoops_GGSGC, _hoops_RGSGC);
	 * _hoops_SSCGC (_hoops_HGPGA->_hoops_PPPHH, _hoops_AGSGC, 2); */

	/* _hoops_CACH _hoops_PGSGC _hoops_IH _hoops_AASA _hoops_IS _hoops_HGSGC */
	_hoops_CSRGR->_hoops_SCPIR = gluNewNurbsRenderer ();
#if 0
#ifdef WGL_DRIVER
	gluNurbsCallback (_hoops_CSRGR->_hoops_SCPIR, GLU_ERROR, (void (*)()) _hoops_GHCGC);
#else
	gluNurbsCallback (_hoops_CSRGR->_hoops_SCPIR, GLU_ERROR, (GLvoid (*)()) _hoops_GHCGC);
#endif
#endif
	gluNurbsProperty (_hoops_CSRGR->_hoops_SCPIR, GLU_SAMPLING_METHOD, GLU_PATH_LENGTH);
	gluNurbsProperty (_hoops_CSRGR->_hoops_SCPIR, GLU_SAMPLING_TOLERANCE, 5.0);
	gluNurbsProperty (_hoops_CSRGR->_hoops_SCPIR, GLU_AUTO_LOAD_MATRIX, GL_TRUE);

	/* _hoops_IGI _hoops_IH _hoops_ASCA _hoops_GCPA */
	_hoops_CSRGR->_hoops_IGSGC = gluNewQuadric();
	gluQuadricDrawStyle (_hoops_CSRGR->_hoops_IGSGC, GLU_FILL);
	_hoops_CSRGR->_hoops_CGSGC = gluNewQuadric();
	gluQuadricDrawStyle (_hoops_CSRGR->_hoops_CGSGC, GLU_LINE);
	/* _hoops_IGI _hoops_IH _hoops_ASCA _hoops_CRCIA */
	_hoops_CSRGR->_hoops_SGSGC = gluNewQuadric();
	gluQuadricDrawStyle (_hoops_CSRGR->_hoops_SGSGC, GLU_FILL);
	_hoops_CSRGR->_hoops_GRSGC = gluNewQuadric();
	gluQuadricDrawStyle (_hoops_CSRGR->_hoops_GRSGC, GLU_LINE);

	_hoops_ARPGC (_hoops_CSRGR);

	if (_hoops_CSRGR->_hoops_CRPGC)
		glLightModelf (GL_LIGHT_MODEL_COLOR_CONTROL_EXT,GL_SEPARATE_SPECULAR_COLOR_EXT);

	_hoops_IAHGC ((Display_Context alter *) dc);

	_hoops_CSRGR->_hoops_GCHGC = false;
	_hoops_CSRGR->_hoops_GSIGC = false;
	_hoops_CSRGR->_hoops_PPAGC = false;

	if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_DISPLAY_LIST) ||
		_hoops_CSRGR->_hoops_PIGRR == DCT_IMAGE) {
		((_hoops_GGAGR *) dc->_hoops_GHRI)->_hoops_CAIAP = _hoops_GRIAP;
	    _hoops_CSRGR->_hoops_RRSGC = false;
	}
	else {
		((_hoops_GGAGR *) dc->_hoops_GHRI)->_hoops_CAIAP = _hoops_RRIAP;
	    _hoops_CSRGR->_hoops_RRSGC = true;
	}

#ifdef _hoops_PSRGC
	//_hoops_RGAR _hoops_SSCP _hoops_PCCP _hoops_GIRRR _hoops_RPP _hoops_PPP _hoops_CCA _hoops_ARSGC
	_hoops_CSRGR->_hoops_CSRGC = _hoops_SSRGC;
	_hoops_CSRGR->_hoops_HSRGC = -1;
#endif

#ifndef WGL_DRIVER
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR || _hoops_CSRGR->_hoops_PIGRR == _hoops_CPSGR)
		((_hoops_GGAGR *) dc->_hoops_GHRI)->_hoops_CAIAP = _hoops_GRIAP;
#endif

#ifdef LINUX_SYSTEM
	((_hoops_GGAGR *) dc->_hoops_GHRI)->_hoops_CAIAP = _hoops_GRIAP;
#endif
}



/*
 * _hoops_PGAA
 */
local void
set_line_rendition (OGLData alter * _hoops_CSRGR,
					Net_Rendition const & nr,
					Line_Rendition const & _hoops_HC) {
	if (_hoops_CSRGR->_hoops_RPCI != _hoops_HC->_hoops_CPA) {
		int				weight;

		_hoops_CSRGR->_hoops_RPCI = _hoops_HC->_hoops_CPA;

		_hoops_APIGC (_hoops_CSRGR, &_hoops_HC->color, nr);

		if ((weight = _hoops_HC->weight) < 0)
			weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
		if (weight == 0)
			weight = 1;
		ENSURE_LINE_WEIGHT (_hoops_CSRGR, weight);

		ENSURE_LINE_PATTERN (_hoops_CSRGR, _hoops_HC->line_style);
		ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);
	}
}

local RGB const *_hoops_RPCA (_hoops_APCA const *color, int mask)
{
	do {
		ASSERT (color->type == _hoops_PPCA);
		if (BIT (color->_hoops_GHA, mask))
			return &color->rgb;
	} while ((color = (_hoops_APCA const *)color->next) != null);
	return null;
}



/*
 * _hoops_PGAA
 */
local void
_hoops_HHCGC (
	OGLData alter *				_hoops_CSRGR,
	Net_Rendition const &		nr,
	_hoops_HHA const &	matr,
	RGB const *					_hoops_PRSGC,
	RGB const *					_hoops_HRSGC)
{
	RGB const *					color;
	RGB alter *					_hoops_IRSGC;
	RGBA alter *				_hoops_CRSGC;
	GLfloat alter				_hoops_PHRGC[4];
	bool						_hoops_CRSPH;

	_hoops_CRSPH = BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI);

	_hoops_SRSGC (_hoops_CSRGR);

	if (matr == nr->_hoops_IHA->_hoops_CHA &&
		matr != nr->_hoops_IHA->_hoops_GIA &&
		ANYBIT (nr->transform_rendition->heuristics, _hoops_RSA)) {
		_hoops_HHA const &	_hoops_ISRAA = nr->_hoops_IHA->_hoops_CHA;
		_hoops_HHA const &	_hoops_SIPI = nr->_hoops_IHA->_hoops_GIA;

		/* _hoops_ISSC _hoops_HSP */
		if (_hoops_PRSGC)
		    color = _hoops_PRSGC;
		else
		    color = &_hoops_SIPI->_hoops_CSHR;

		if (!_hoops_HIRGC (_hoops_CSRGR->_hoops_CSC._hoops_IGAGC._hoops_PGAGC, *color)) {
			_hoops_CRSGC = &_hoops_CSRGR->_hoops_CSC._hoops_IGAGC._hoops_PGAGC;
			_hoops_CRSGC->red = _hoops_PHRGC[0] = color->red;
			_hoops_CRSGC->green = _hoops_PHRGC[1] = color->green;
			_hoops_CRSGC->blue = _hoops_PHRGC[2] = color->blue;
			_hoops_CRSGC->alpha = _hoops_PHRGC[3] = _hoops_SIPI->_hoops_IRIR;
			glMaterialfv (GL_BACK, GL_AMBIENT_AND_DIFFUSE, _hoops_PHRGC);
		}
		_hoops_CCCGC (_hoops_CSRGR, GL_BACK);
		FORCE_COLOR_4F(color->red, color->green, color->blue, _hoops_SIPI->_hoops_IRIR, _hoops_CRSPH);

		/* _hoops_RIPS _hoops_HSP */
		if (_hoops_PRSGC)
		    color = _hoops_PRSGC;
		else
		    color = &_hoops_ISRAA->_hoops_CSHR;

		if (_hoops_CRSPH) {
			_hoops_PHRGC[0] = _hoops_PHRGC[1] = _hoops_PHRGC[2] = color->_hoops_CPIR();
			color = (RGB *)_hoops_PHRGC;
		}

		if (!_hoops_HIRGC (_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC, *color)) {
			_hoops_CRSGC = &_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC;
			_hoops_CRSGC->red = _hoops_PHRGC[0] = color->red;
			_hoops_CRSGC->green = _hoops_PHRGC[1] = color->green;
			_hoops_CRSGC->blue = _hoops_PHRGC[2] = color->blue;
			_hoops_CRSGC->alpha = _hoops_PHRGC[3] = _hoops_ISRAA->_hoops_IRIR;
			glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, _hoops_PHRGC);
		}
		_hoops_CCCGC (_hoops_CSRGR, GL_FRONT);
		FORCE_COLOR_4F(color->red, color->green, color->blue, _hoops_ISRAA->_hoops_IRIR, _hoops_CRSPH);
	}
	else {
		_hoops_GASGC (_hoops_CSRGR, GL_FRONT_AND_BACK);

		if (_hoops_PRSGC)
		    color = _hoops_PRSGC;
		else
		    color = &matr->_hoops_CSHR;

		if (_hoops_CRSPH) {
			_hoops_PHRGC[0] = _hoops_PHRGC[1] = _hoops_PHRGC[2] = color->_hoops_CPIR();
			color = (RGB *)_hoops_PHRGC;
		}

		if (!_hoops_HIRGC (_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC, *color) ||
			_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.alpha != matr->_hoops_IRIR) {
			_hoops_CRSGC = &_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC;
			_hoops_CRSGC->red = _hoops_PHRGC[0] = color->red;
			_hoops_CRSGC->green = _hoops_PHRGC[1] = color->green;
			_hoops_CRSGC->blue = _hoops_PHRGC[2] = color->blue;
			_hoops_CRSGC->alpha = _hoops_PHRGC[3] = matr->_hoops_IRIR;
			glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, _hoops_PHRGC);

			/*
			 * _hoops_IIS _hoops_SACS _hoops_RASGC* _hoops_HCPH _hoops_HAHA _hoops_ISCP _hoops_SCGR _hoops_AASGC _hoops_AASR _hoops_PPR _hoops_SPI _hoops_PSHA
			 * _hoops_RGR _hoops_RHAP _hoops_HAR _hoops_AHGS _hoops_IS _hoops_IPHR _hoops_GGR _hoops_PSIS..._hoops_SCH _hoops_GHCA _hoops_SHH _hoops_APIP _hoops_RPP _hoops_RHAC _hoops_CHR _hoops_GRP
			 * _hoops_SRGS, _hoops_PHRI...
			 */
			FORCE_COLOR_4F(color->red, color->green, color->blue, matr->_hoops_IRIR, _hoops_CRSPH);
		}
/* _hoops_SGH _hoops_RGR _hoops_RIS _hoops_IS _hoops_SSS _hoops_GGSR _hoops_RPP _hoops_RH _hoops_HAIR _hoops_HRGR _hoops_IHGS _hoops_HGAS _hoops_GHIPR _hoops_RH _hoops_IHAH'_hoops_GRI _hoops_ISSC */
#if 0
		else {
			float _hoops_PIHR[4];
			glGetFloatv(GL_CURRENT_COLOR, _hoops_PIHR);
			if (_hoops_PIHR[0] != _hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.red ||
				_hoops_PIHR[1] != _hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.green ||
				_hoops_PIHR[2] != _hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.blue ||
				_hoops_PIHR[3] != _hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.alpha)
				_hoops_PIHR[0] = _hoops_PIHR[0];
		}
#endif
		_hoops_CSRGR->_hoops_CSC._hoops_IGAGC._hoops_PGAGC.red = _hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.red;
		_hoops_CSRGR->_hoops_CSC._hoops_IGAGC._hoops_PGAGC.green = _hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.green;
		_hoops_CSRGR->_hoops_CSC._hoops_IGAGC._hoops_PGAGC.blue = _hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.blue;
		_hoops_CSRGR->_hoops_CSC._hoops_IGAGC._hoops_PGAGC.alpha = _hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.alpha;
	}
	_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;

	if (_hoops_HRSGC)
	    color = _hoops_HRSGC;
	else
		color = &matr->color[_hoops_HIA];

	if (_hoops_CRSPH) {
		_hoops_PHRGC[0] = _hoops_PHRGC[1] = _hoops_PHRGC[2] = color->_hoops_CPIR();
		color = (RGB *)_hoops_PHRGC;
	}

	if (!_hoops_HIRGC (_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_SGC, *color)) {
		_hoops_IRSGC = &_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_SGC;
		_hoops_IRSGC->red = _hoops_PHRGC[0] = color->red;
		_hoops_IRSGC->green = _hoops_PHRGC[1] = color->green;
		_hoops_IRSGC->blue = _hoops_PHRGC[2] = color->blue;
		_hoops_PHRGC[3] = 1.0f;
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, _hoops_PHRGC);
	}

	if (!_hoops_HIRGC (_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IRC, matr->color[_hoops_HCA])) {
	    color = &matr->color[_hoops_HCA];
		if (_hoops_CRSPH) {
			_hoops_PHRGC[0] = _hoops_PHRGC[1] = _hoops_PHRGC[2] = color->_hoops_CPIR();
			color = (RGB *)_hoops_PHRGC;
		}
		_hoops_IRSGC = &_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IRC;
		_hoops_IRSGC->red = _hoops_PHRGC[0] = color->red;
		_hoops_IRSGC->green = _hoops_PHRGC[1] = color->green;
		_hoops_IRSGC->blue = _hoops_PHRGC[2] = color->blue;
		_hoops_PHRGC[3] = 1.0f;
		glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, _hoops_PHRGC);
	}
	 /*
	 * _hoops_HIHH _hoops_RAIA _hoops_RH _hoops_RSPHP-_hoops_AAGA _hoops_GGR _hoops_IHRHA _hoops_RH _hoops_GHI _hoops_CHIR,
	 * _hoops_PHGP _hoops_RH _hoops_IGPRA _hoops_PRSPA _hoops_IRHS _hoops_IRS _hoops_IGRH _hoops_IIGR _hoops_IHPHP.  4 _hoops_HRGR _hoops_RGAR _hoops_IRS _hoops_AHGC.
	 */
	if (_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_HGAGC != matr->gloss) {
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_HGAGC = matr->gloss;
		if (matr->gloss < 25)
			glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 4.0f * matr->gloss);
		else
			glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);
	}
}

/*
 * _hoops_PGAA
 */
local void
_hoops_IHCGC (
	OGLData alter *				_hoops_CSRGR,
	Net_Rendition const &		nr,
	_hoops_HHA const &	_hoops_RRGH) {
	RGB alter *					_hoops_IRSGC;
	RGBA alter *				_hoops_CRSGC;
	GLfloat alter				_hoops_PHRGC[4];
	RGB const *					color;

	color = &_hoops_RRGH->color[_hoops_HIA];
	if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI)) {
		_hoops_PHRGC[0] = _hoops_PHRGC[1] = _hoops_PHRGC[2] = color->_hoops_CPIR();
		color = (RGB *)_hoops_PHRGC;
	}
	_hoops_IRSGC = &_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_SGC;
	_hoops_IRSGC->red = _hoops_PHRGC[0] = color->red;
	_hoops_IRSGC->green = _hoops_PHRGC[1] = color->green;
	_hoops_IRSGC->blue = _hoops_PHRGC[2] = color->blue;
	_hoops_PHRGC[3] = 1.0f;
	glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, _hoops_PHRGC);

	_hoops_CRSGC = &_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_PGAGC;
	_hoops_CRSGC->red = _hoops_PHRGC[0] = 1.0f;
	_hoops_CRSGC->green = _hoops_PHRGC[1] = 1.0f;
	_hoops_CRSGC->blue = _hoops_PHRGC[2] = 1.0f;
	_hoops_CRSGC->alpha = _hoops_PHRGC[3] = _hoops_RRGH->_hoops_IRIR;
	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, _hoops_PHRGC);

	if (_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_HGAGC != _hoops_RRGH->gloss) {
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_HGAGC = _hoops_RRGH->gloss;
		if (_hoops_RRGH->gloss < 25)
			glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 4.0f * _hoops_RRGH->gloss);
		else
			glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);
	}

	_hoops_SRSGC (_hoops_CSRGR);
	FORCE_COLOR_4F(1.0, 1.0, 1.0, _hoops_RRGH->_hoops_IRIR, false);
	_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;
	UNREFERENCED(nr);
}



/*****************************************************************************
 *****************************************************************************
				_hoops_HRPAH _hoops_PASGC
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_PGAA
 */
local void
_hoops_HASGC (
	Net_Rendition const &	nr,
	GLint					width,
	int						_hoops_IASGC) {
	AGLM(OGLData alter *	_hoops_CSRGR = OGLD (nr->_hoops_SRA);)
	_hoops_AIGH *				_hoops_PAGR;
	char *					_hoops_IGHSI;
	int 					_hoops_CASGC;
	int 					column;
	_hoops_AIGH *				_hoops_PAAC;
	Named_Material *		_hoops_SASGC = (Named_Material *)
									nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->_hoops_HAA;
	int						_hoops_HHAH = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->length;
	_hoops_AHAH const &			_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;


	_hoops_CASGC = 4;
	ALLOC_ARRAY(_hoops_IGHSI, width * _hoops_CASGC, char);
	_hoops_PAAC = _hoops_PAGR = (_hoops_AIGH *) _hoops_IGHSI;

	if (BIT(_hoops_PHAH.options, _hoops_CHRH)) {
		*_hoops_PAAC++ = HD_Apply_Color_Effects (_hoops_SASGC[0]._hoops_CSHR, _hoops_PHAH);

		for (column = 0; column < width-1; column++) {
			int		index = column % _hoops_HHAH;

			*_hoops_PAAC++ = HD_Apply_Color_Effects (_hoops_SASGC[index]._hoops_CSHR, _hoops_PHAH);
		}
	}
	else {
		*_hoops_PAAC++ = _hoops_SASGC[0]._hoops_CSHR;

		for (column = 0; column < width-1; column++) {
			int		index = column % _hoops_HHAH;

			*_hoops_PAAC++ = _hoops_SASGC[index]._hoops_CSHR;
		}
	}

	glTexImage2D (GL_TEXTURE_2D, 0, _hoops_CASGC,
			  width, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)_hoops_PAGR);
	_hoops_GPRH(_hoops_RPRH)++;

	if (_hoops_IASGC) {
		gluBuild2DMipmaps (GL_TEXTURE_2D, _hoops_CASGC,
					   width,1, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)_hoops_PAGR);
	}

	FREE_ARRAY(_hoops_PAGR, width * _hoops_CASGC, char);
}


/*
 * _hoops_PGAA
 */
local GLint
_hoops_IPAH (GLint _hoops_CPAH) {
	GLint _hoops_SPAH;
	for (_hoops_SPAH = 64;	 _hoops_SPAH < _hoops_CPAH;  _hoops_SPAH = _hoops_SPAH << 1)
		;
	return _hoops_SPAH;
}

static const float _hoops_PAIRH[4][4] = {{1,0,0,0},{0,-1,0,0},{0,0,1,0},{0,1,0,1}};
static const float _hoops_AAIRH[4][4] =  {{0,0,1,0},{1,0,0,0},{0,1,0,0},{0,0,0,1}};
static const float _hoops_GPSGC[4][4] = {{-1,0,0,0},{0,-1,0,0},{0,0,1,0},{1,1,0,1}};
static const float _hoops_RPSGC[4][4] = {{0.5f,0,0,0},{0,0.5f,0,0},{0,0,1,0},{0,0,0,1}};



local void _hoops_APSGC(OGLData alter *_hoops_CSRGR)
{

	if (_hoops_CSRGR->_hoops_CSC._hoops_PSAH &&
		_hoops_CSRGR->_hoops_CSC._hoops_PSAH != _hoops_RSARR) {
		OGL_FREE_TEXTURE(_hoops_CSRGR->_hoops_CSC._hoops_PSAH);
	}
	_hoops_CSRGR->_hoops_CSC._hoops_PSAH = _hoops_RSARR;

	if (_hoops_CSRGR->_hoops_CSC._hoops_HAACP._hoops_HPRGC	 &&
		_hoops_CSRGR->_hoops_CSC._hoops_HAACP._hoops_HPRGC != _hoops_RSARR) {
		OGL_FREE_TEXTURE(_hoops_CSRGR->_hoops_CSC._hoops_HAACP._hoops_HPRGC);
	}
	_hoops_CSRGR->_hoops_CSC._hoops_HAACP._hoops_HPRGC=_hoops_RSARR;
}

local void _hoops_PPSGC(OGLData alter *_hoops_CSRGR)
{
	gluDeleteNurbsRenderer (_hoops_CSRGR->_hoops_SCPIR);
	_hoops_CSRGR->_hoops_SCPIR = null;
	gluDeleteQuadric (_hoops_CSRGR->_hoops_IGSGC);
	_hoops_CSRGR->_hoops_IGSGC = null;
	gluDeleteQuadric (_hoops_CSRGR->_hoops_CGSGC);
	_hoops_CSRGR->_hoops_CGSGC = null;
	gluDeleteQuadric (_hoops_CSRGR->_hoops_SGSGC);
	_hoops_CSRGR->_hoops_SGSGC = null;
	gluDeleteQuadric (_hoops_CSRGR->_hoops_GRSGC);
	_hoops_CSRGR->_hoops_GRSGC = null;
}


local void
_hoops_HPSGC(
		OGLData *_hoops_CSRGR)
{
	_hoops_IPSGC *pair;
	int i; 
	_hoops_AIGI *_hoops_PSCI[8];

	if (_hoops_CSRGR->_hoops_CIGI->_hoops_RCGI) {
		_hoops_PSCI[0] = _hoops_CSRGR->_hoops_CIGI->_hoops_RCGI;
		while ((pair = _hoops_PSCI[0]->RemoveFirst()) != null) {
			Tristrip alter *ts = (Tristrip alter *)pair->geo;
			ts->_hoops_CARI &= ~_hoops_SARI;
			delete pair;
		}
		delete _hoops_PSCI[0];
		_hoops_CSRGR->_hoops_CIGI->_hoops_RCGI = null;
	}

	_hoops_PSCI[0] = _hoops_CSRGR->_hoops_CIGI->_hoops_IIRI;
	_hoops_CSRGR->_hoops_CIGI->_hoops_IIRI = null;
	_hoops_PSCI[1] = _hoops_CSRGR->_hoops_CIGI->_hoops_CIRI;
	_hoops_CSRGR->_hoops_CIGI->_hoops_CIRI = null;
	_hoops_PSCI[2] = _hoops_CSRGR->_hoops_CIGI->_hoops_SIRI;
	_hoops_CSRGR->_hoops_CIGI->_hoops_SIRI = null;
	for (i = 0; i < 3; i++) {
		if (_hoops_PSCI[i]) {
			while ((pair = _hoops_PSCI[i]->RemoveFirst()) != null) {
				Polyedge alter *pe = (Polyedge alter *)pair->geo;
				pe->_hoops_CARI &= ~_hoops_SARI;
				delete pair;
			}
			delete _hoops_PSCI[i];
		}
	}

	_hoops_PSCI[0] = _hoops_CSRGR->_hoops_CIGI->_hoops_HRPI;
	_hoops_CSRGR->_hoops_CIGI->_hoops_HRPI = null;
	_hoops_PSCI[1] = _hoops_CSRGR->_hoops_CIGI->_hoops_IIII;
	_hoops_CSRGR->_hoops_CIGI->_hoops_IIII = null;
	for (i = 0; i < 2; i++) {
		if (_hoops_PSCI[i]) {
			while ((pair = _hoops_PSCI[i]->RemoveFirst()) != null)
				delete pair;
			delete _hoops_PSCI[i];
		}
	}

	/* _hoops_HSCI _hoops_RH _hoops_IARI */
	_hoops_CSRGR->_hoops_CIGI->nr.release();
	FREE (_hoops_CSRGR->_hoops_CIGI, OGL_Collector);
	_hoops_CSRGR->_hoops_CIGI = null;
	_hoops_CSRGR->_hoops_ISCI = 0;
}


local bool 
_hoops_CPSGC (
		_hoops_AGCI *_hoops_AGAGR, 
		void *_hoops_HHCAP)
{
	Display_Context const *dc = (Display_Context const *)_hoops_HHCAP;
	OGL_Display_List *odl = (OGL_Display_List *) _hoops_AGAGR;

	if (odl->type == OGL_DL_TEXTURE && odl->_hoops_PPAH) {
		/* _hoops_RPP _hoops_RH _hoops_CSRI _hoops_HRGR _hoops_IRS _hoops_CGRH _hoops_HH, _hoops_SRPS _hoops_RH _hoops_PIH _hoops_ARPP _hoops_PGAGR _hoops_SCH _hoops_SGGR */
		Image alter *image = (Image alter *)odl->_hoops_PPAH->owner;
		if (image &&
			BIT (image->flags, _hoops_GRRH)) {
			if (ALLBITS (image->flags, _hoops_GRRH|_hoops_APAH))
				_hoops_CGAGR (dc, odl);
			image->flags &= ~(_hoops_GRRH|_hoops_APAH);
		}
	}
	return true;
}


local void
_hoops_SPSGC(Display_Context const * dc)
{
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	int i;

	if (_hoops_CSRGR->_hoops_GHSGC)
		_hoops_ISPGR(dc->_hoops_SHCIP, _hoops_CSRGR->_hoops_GHSGC, 0);
	if (_hoops_CSRGR->_hoops_PCHGC)
		_hoops_ISPGR(dc->_hoops_SHCIP, _hoops_CSRGR->_hoops_PCHGC, _hoops_CSRGR->_hoops_CCHGC);

	_hoops_GHRGC (_hoops_CSRGR);

	if (_hoops_CSRGR->_hoops_RHSGC) {
		(*_hoops_CSRGR->glDeleteProgramsARB) (1, &_hoops_CSRGR->_hoops_RHSGC);
		(*_hoops_CSRGR->glDeleteProgramsARB) (1, &_hoops_CSRGR->_hoops_AHSGC);
		_hoops_CSRGR->_hoops_RHSGC = _hoops_CSRGR->_hoops_AHSGC = 0;
	}

	_hoops_APSGC(_hoops_CSRGR);
	_hoops_PPSGC(_hoops_CSRGR);

	if (_hoops_CSRGR->_hoops_CIGI)
		_hoops_HPSGC (_hoops_CSRGR);

	HD_Purge_Display_Lists(dc->_hoops_GHRI, _hoops_CPSGC, (void *)dc);

	if (dc->_hoops_GHRI->_hoops_RGAGR)
		_hoops_SSRGR((Display_Context alter *)dc);

	for (i = 0; i < _hoops_PHSGC+1; i++)
		if (_hoops_CSRGR->_hoops_HHSGC[i]) {
			_hoops_HPRH(_hoops_CSRGR->_hoops_HHSGC[i]);
			_hoops_CSRGR->_hoops_HHSGC[i] = null;
		}
	if (_hoops_CSRGR->_hoops_IHSGC) {
		FREE_ARRAY(_hoops_CSRGR->_hoops_IHSGC, _hoops_CHSGC, int);
		_hoops_CSRGR->_hoops_IHSGC = null;
	}
	if (_hoops_CSRGR->_hoops_SHSGC) {
		FREE_ARRAY(_hoops_CSRGR->_hoops_SHSGC, OGL_SCRATCH_SPACE_SIZE, Point);
		_hoops_CSRGR->_hoops_SHSGC = null;
	}
	if (_hoops_CSRGR->_hoops_GISGC) {
		FREE_ARRAY(_hoops_CSRGR->_hoops_GISGC, OGL_SCRATCH_SPACE_SIZE, Vector);
		_hoops_CSRGR->_hoops_GISGC = null;
	}
	if (_hoops_CSRGR->_hoops_RISGC) {
		FREE_ARRAY(_hoops_CSRGR->_hoops_RISGC, OGL_SCRATCH_SPACE_SIZE, RGB);
		_hoops_CSRGR->_hoops_RISGC = null;
	}
	if (_hoops_CSRGR->_hoops_AISGC) {
		FREE_ARRAY(_hoops_CSRGR->_hoops_AISGC,
					2*OGL_SCRATCH_SPACE_SIZE,
					float);
		_hoops_CSRGR->_hoops_AISGC = null;
	}
	if (_hoops_CSRGR->_hoops_IIHS) {
		FREE_ARRAY (_hoops_CSRGR->_hoops_IIHS, _hoops_CSRGR->_hoops_HIHS, Test);
		_hoops_CSRGR->_hoops_IIHS = null;
	}
	if (_hoops_CSRGR->_hoops_PISGC) {
		delete _hoops_CSRGR->_hoops_PISGC;
		_hoops_CSRGR->_hoops_PISGC = null;
	}

	for (i = 0; i < _hoops_HISGC; i++)
		if (_hoops_CSRGR->_hoops_IISGC[i])
			glDeleteTextures (1, &_hoops_CSRGR->_hoops_IISGC[i]);
	for (i = 0; i < _hoops_APRRR; i++)
		if (_hoops_CSRGR->_hoops_CISGC[i])
			glDeleteTextures (1, &_hoops_CSRGR->_hoops_CISGC[i]);

	if (_hoops_CSRGR->_hoops_SISGC) {
		(*_hoops_CSRGR->_hoops_PSPGC) (_hoops_CSRGR->_hoops_SISGC, _hoops_CSRGR->_hoops_GCSGC);
		(*_hoops_CSRGR->glDeleteShaderARB) (_hoops_CSRGR->_hoops_GCSGC);
		(*_hoops_CSRGR->glDeleteProgramARB) (_hoops_CSRGR->_hoops_SISGC);
		_hoops_CSRGR->_hoops_SISGC = 0;
		_hoops_CSRGR->_hoops_GCSGC = 0;
	}
}



local _hoops_HIGH _hoops_RCSGC (	
	OGLData alter *_hoops_CSRGR,
	Net_Rendition const & nr,
	_hoops_RCR alter *txr,
	OGL_Render_Pass _hoops_GCI, 
	int _hoops_CCGH,
	int _hoops_ICGH)

{
	_hoops_HIGH _hoops_IIGH=0;

	if (_hoops_CSRGR->_hoops_IRPGC &&
		(txr->_hoops_CGA == _hoops_ASCC || txr->_hoops_CGA == _hoops_SGA))
		_hoops_IIGH |= _hoops_AGSC;

	if (!_hoops_CSRGR->_hoops_HAPGC)
		_hoops_IIGH |= _hoops_GHRH;

	/* _hoops_RGAR _hoops_SGH _hoops_RIS _hoops_RRRH _hoops_PSP _hoops_RHRH _hoops_AHRH _hoops_PHRH */
	_hoops_IIGH |= _hoops_HHRH;

#if 0
	/* _hoops_RPGP _hoops_ICCGR _hoops_ACSGC */
	_hoops_CSRGR->_hoops_AAPGC=false;
#endif
	if (BIT(nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH) &&
		_hoops_GCI != _hoops_PCSGC)
		_hoops_IIGH |= _hoops_GIRH;

	if (txr->_hoops_CGA == _hoops_PSGRP &&
		!_hoops_CSRGR->_hoops_AAPGC)
		_hoops_IIGH |= _hoops_SIRRP;

	if (_hoops_GCI == _hoops_HCSGC)
		_hoops_IIGH |= _hoops_PPRH;
	else if (BIT(txr->_hoops_SCR, _hoops_IGA) && !BIT(txr->_hoops_SCR, _hoops_PGA))
	    _hoops_IIGH |= _hoops_PPRH;
	else if (txr->_hoops_CGA == _hoops_SGA)
	    _hoops_IIGH |= _hoops_PPRH;

	if (txr->_hoops_RARH == _hoops_AARH)
		_hoops_IIGH |= _hoops_RIRH;

	if (txr->_hoops_RARH == _hoops_PARH)
		_hoops_IIGH |= _hoops_AIRH;

	if (ANYBIT(txr->flags, _hoops_HIRH) ||
		txr->_hoops_HPIR._hoops_IIRH != 0.0f ||
		txr->_hoops_HPIR._hoops_CIRH != 1.0f ||
		txr->_hoops_HPIR._hoops_SIRH != 1.0f ||
		txr->_hoops_HPIR._hoops_IPIR.red != 0.0f ||
		txr->_hoops_HPIR._hoops_IPIR.green != 0.0f ||
		txr->_hoops_HPIR._hoops_IPIR.blue != 0.0f)
		_hoops_IIGH |= _hoops_GCRH;

	if (BIT(txr->_hoops_SCR, _hoops_RCRH) ||
	    _hoops_ICGH > _hoops_CSRGR->_hoops_HPHGC) {
		_hoops_ICGH=_hoops_CSRGR->_hoops_HPHGC;
	}

	HD_Activate_Texture_Image(nr, txr, _hoops_IIGH, _hoops_CCGH, _hoops_ICGH, _hoops_CCGH, _hoops_ICGH);

	return _hoops_IIGH;
}


local GLuint
_hoops_ICSGC (
	OGLData alter *_hoops_CSRGR,
	Net_Rendition const & nr,
	_hoops_RCR alter *txr,
	OGL_Render_Pass _hoops_GCI,
	int _hoops_GRRA)
{
	_hoops_GACR alter *dl=0;
	OGL_Display_List alter *odl=0;
	bool _hoops_RACR=false;
	GLuint list=0;
	int _hoops_ICGH = 512; //_hoops_PASGH _hoops_HCCPR "_hoops_PSP _hoops_SCPP" _hoops_HRGR _hoops_CHIA (_hoops_PGAP _hoops_SCH _hoops_HRGR _hoops_HPP _hoops_SHIR)
	int _hoops_CCGH = 4;
	_hoops_RCR alter *_hoops_CRAH;
	int format, _hoops_CCSGC, _hoops_GCPIR;
	int w, h, depth;

	if (!txr->_hoops_RHGH)
		_hoops_RCSGC (_hoops_CSRGR, nr, txr, _hoops_GCI, _hoops_CCGH, _hoops_ICGH);
	_hoops_RACR = _hoops_AACR(nr, &txr->_hoops_RHGH->_hoops_GAHA, &dl, &odl, OGL_DL_TEXTURE);
	list = odl->item.texture.id;
	_hoops_PPRGC(_hoops_CSRGR, _hoops_GRRA);
	_hoops_IPRGC(_hoops_CSRGR, _hoops_GRRA, GL_TEXTURE_3D, list);

	if (_hoops_RACR) {
		format = 0;
		_hoops_CCSGC = 0; 
		w = txr->_hoops_RHGH->width;
		h = txr->_hoops_RHGH->height;
		depth = txr->_hoops_ICR[2];
		switch (txr->_hoops_RHGH->format) {
			case _hoops_AHGH:
				format = GL_LUMINANCE;
				_hoops_CCSGC = 1;
				_hoops_GCPIR = 1;
				break;
			case _hoops_HHGH:
				format = GL_RGB;
				_hoops_CCSGC = GL_RGB8;
				_hoops_GCPIR = 3;
				break;
			case Image_RGBA32:
				format = GL_RGBA;
				_hoops_CCSGC = GL_RGBA8;
				_hoops_GCPIR = 4;
				break;
			default:
				HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
					"Internal error: Unhandled 3D texture type in opengl driver.");
		}
		(*_hoops_CSRGR->glTexImage3D)(GL_TEXTURE_3D, 0, _hoops_CCSGC, w, h, depth, 0, format, GL_UNSIGNED_BYTE, null);

		for (int i = 0; i < depth ; ++i) {
			_hoops_CRAH = txr->_hoops_PRAH[i * txr->_hoops_ICR[0] * txr->_hoops_ICR[1]];
			_hoops_RCSGC (_hoops_CSRGR, nr, _hoops_CRAH, _hoops_GCI, _hoops_CCGH, _hoops_ICGH);
			(*_hoops_CSRGR->glTexSubImage3D)(
				GL_TEXTURE_3D,
				0, 
				0, 0, i,
				w, h, 1, 
				format, GL_UNSIGNED_BYTE, (GLvoid *)_hoops_CRAH->_hoops_RHGH->_hoops_PHGH);
		}
	}

	//_hoops_CHR _hoops_IIH _hoops_APIP _hoops_ARHGP _hoops_IIGR 3d _hoops_AI _hoops_RII _hoops_HSAR _hoops_SPI?
	UNREFERENCED (_hoops_GCI);
	return list;
}


/*
 * _hoops_PGAA
 */
local GLuint
_hoops_PIGH (
	OGLData alter *_hoops_CSRGR,
	Net_Rendition const & nr,
	_hoops_RCR alter *txr,
	OGL_Render_Pass _hoops_GCI,
	int _hoops_GRRA)
{
	_hoops_GACR alter *dl=0;
	OGL_Display_List alter *odl=0;
	bool _hoops_RACR=false;
	GLuint list=0;
	int _hoops_ICGH = 512; //_hoops_PASGH _hoops_HCCPR "_hoops_PSP _hoops_SCPP" _hoops_HRGR _hoops_CHIA (_hoops_PGAP _hoops_SCH _hoops_HRGR _hoops_HPP _hoops_SHIR)
	int _hoops_CCGH = 4;
	GLuint _hoops_SCSGC = _hoops_CSRGR->_hoops_CSC._hoops_SGAGC[_hoops_GRRA];
	GLint format = 0, _hoops_CCSGC = 0;

	if (BIT(txr->flags, _hoops_CSGH)) {
		return _hoops_ICSGC (_hoops_CSRGR, nr, txr, _hoops_GCI, _hoops_GRRA);
	}

	if (txr->_hoops_RARH == _hoops_PARH &&
		_hoops_CSRGR->_hoops_GAPGC) {
		float _hoops_GSSGC;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &_hoops_GSSGC);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, _hoops_GSSGC);
	}

	//_hoops_RSSGC _hoops_PPR _hoops_APARI _hoops_CHR _hoops_GIR _hoops_GGR _hoops_AAPA _hoops_PAPA.  _hoops_CRCAI _hoops_HRGR _hoops_GIR _hoops_ARI
	if (BIT (txr->image->flags, _hoops_SSGH) &&
		txr->image->format != _hoops_GGRH &&
		txr->image->format != _hoops_RGRH &&
		txr->image->format != _hoops_AGRH) {

		//_hoops_RH _hoops_PGRH _hoops_HGRH _hoops_CHH _hoops_HS _hoops_IS _hoops_SHH _hoops_IRS _hoops_IGRH _hoops_HAGH _hoops_IH _hoops_CGRH-_hoops_RGAR _hoops_SGRH _hoops_AI
		ASSERT (!BIT (txr->image->flags, _hoops_GRRH));  

		//_hoops_SGRH _hoops_RRRH _hoops_PAH _hoops_RGAR _hoops_SHH _hoops_IGI _hoops_GAR-_hoops_HRGR, _hoops_HIS _hoops_RH _hoops_ASGH _hoops_ARRH _hoops_HGRH _hoops_ASSP'_hoops_RA _hoops_GHAA
		_hoops_RACR = _hoops_AACR(nr, &txr->image->_hoops_GAHA, &dl, &odl, OGL_DL_TEXTURE);

		if (!txr->_hoops_RHGH) {
			if (_hoops_CSRGR->_hoops_AHPGC) {
				txr->_hoops_RHGH = txr->image;
				_hoops_PRRH (txr->_hoops_RHGH);
			}
			else {
				HE_ERROR (HEC_TEXTURE, HES_UNSUPPORTED_DEVICE,
						"S3 texture decompression not supported on this hardware.");
				if (!HOOPS_WORLD->_hoops_CIHGI)
					HI_Validate_Texture_Fallback_Image ();
				txr->_hoops_RHGH = HOOPS_WORLD->_hoops_CIHGI;
				_hoops_PRRH (txr->_hoops_RHGH);
				goto _hoops_ASSGC;
			}
		}


		switch (txr->image->format) {
			case _hoops_IRRH: 
				format = GL_COMPRESSED_RGB_ARB;
				_hoops_CCSGC = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
				break;
			case _hoops_CRRH: 
				format = GL_COMPRESSED_RGBA_ARB;
				_hoops_CCSGC = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				break;
			case _hoops_SRRH: 
				format = GL_COMPRESSED_RGBA_ARB;
				_hoops_CCSGC = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;

			default:
				HE_ERROR (HEC_TEXTURE, HES_PROCEDURAL_ERROR,
						"Unexpected compressed texture format.");
				return 0;
		}
		if (_hoops_RACR) {
			OGL_ALLOC_TEXTURE(odl->item.texture.id);

			odl->_hoops_CARH = txr->image->_hoops_IARH;
			HOOPS_WORLD->_hoops_SARH += odl->_hoops_CARH;

			_hoops_IPRGC(_hoops_CSRGR, _hoops_GRRA, GL_TEXTURE_2D, odl->item.texture.id);
			(*_hoops_CSRGR->glCompressedTexImage2DARB)(GL_TEXTURE_2D, 0, _hoops_CCSGC, 
				txr->image->width, txr->image->height,
				0, txr->image->_hoops_IARH, 
				txr->image->_hoops_PHGH);
			_hoops_GPRH(_hoops_RPRH)++;
		}
		else
			_hoops_IPRGC(_hoops_CSRGR, _hoops_GRRA, GL_TEXTURE_2D, odl->item.texture.id);

		if (txr->_hoops_RARH == _hoops_PARH ||
			txr->_hoops_RARH == _hoops_AARH) {
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		}
		return odl->item.texture.id;
	}

			

	if (txr->_hoops_RHGH &&
		_hoops_GCI == _hoops_HCSGC &&
		!BIT(txr->_hoops_RHGH->flags, _hoops_PPRH)) {
		_hoops_HPRH(txr->_hoops_RHGH);
		txr->_hoops_RHGH=0;
	}

	if (txr->_hoops_RHGH &&
		(_hoops_GCI == _hoops_PCSGC ||
		 !BIT(txr->_hoops_RHGH->flags, _hoops_GIRH) &&
		 BIT(nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH))) {
		_hoops_HPRH(txr->_hoops_RHGH);
		txr->_hoops_RHGH=0;
	}

	if (!txr->_hoops_RHGH &&
		BIT (txr->image->flags, _hoops_GRRH)) {
		/* _hoops_RH _hoops_CSCR _hoops_HICP _hoops_GPP _hoops_RH _hoops_CGRH _hoops_RGAR, _hoops_HIS _hoops_SR _hoops_PAH'_hoops_RA _hoops_AGIRA _hoops_PPR _hoops_GRPHA _hoops_SCH */
		txr->_hoops_RHGH = txr->image;
		_hoops_PRRH (txr->_hoops_RHGH);
	}

_hoops_ASSGC:


	if (!txr->_hoops_RHGH)
		_hoops_RCSGC (_hoops_CSRGR, nr, txr, _hoops_GCI, _hoops_CCGH, _hoops_ICGH);

	if (txr->_hoops_RHGH == null)
		return 0;

	if (BIT (txr->_hoops_RHGH->flags, _hoops_GRRH)) {
		/* _hoops_IPCP _hoops_AIRI _hoops_HIGR **_hoops_ISCC** _hoops_RH _hoops_IAAI _hoops_IPS _hoops_IIGR _hoops_RH _hoops_CSCR _hoops_PIH.
		   _hoops_HGPP _hoops_RRRH _hoops_CHR _hoops_CSCC _hoops_IS _hoops_IRS _hoops_SASI _hoops_RHPP, _hoops_HIH _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_SSCC
		   _hoops_RH _hoops_GGSC _hoops_SR'_hoops_ASAR _hoops_IPIH _hoops_ASCA _hoops_CCA (_hoops_GGR _hoops_RGSC, _hoops_SCH _hoops_PAHH _hoops_GPGH'_hoops_RA).
		   _hoops_PSPC, _hoops_RH _hoops_ASGH _hoops_PSSGC _hoops_HGRH _hoops_ASSP'_hoops_RA _hoops_GHAA _hoops_ARI. */
		dl = txr->_hoops_RHGH->_hoops_GAHA;
		if (dl)
			odl = (OGL_Display_List alter *) dl->list;
		if (!odl) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				   "GPU copy of texture unexpectedly lost by opengl driver.");
			return 0;
		}
		_hoops_RACR = false;
	}
	else
		_hoops_RACR = _hoops_AACR(nr, &txr->_hoops_RHGH->_hoops_GAHA, &dl, &odl, OGL_DL_TEXTURE);

	if (_hoops_RACR && !txr->_hoops_RHGH->_hoops_PHGH) {
		_hoops_HPRH(txr->_hoops_RHGH);
		txr->_hoops_RHGH=0;
		goto _hoops_ASSGC;
	}

	if (_hoops_RACR) {
		OGL_ALLOC_TEXTURE(odl->item.texture.id);
		odl->_hoops_CARH = 
				txr->_hoops_RHGH->_hoops_GCPIR * 
				txr->_hoops_RHGH->width *
				txr->_hoops_RHGH->height;
		HOOPS_WORLD->_hoops_SARH += odl->_hoops_CARH;
	}

	switch (_hoops_GCI) {

		case _hoops_HSSGC:
		case _hoops_ISSGC:
			if (BIT(txr->_hoops_SCR, _hoops_IGA) &&!BIT(txr->_hoops_SCR, _hoops_PGA))
				HD_Set_Image_Alpha(txr->_hoops_RHGH, 255);
		case _hoops_CSSGC:
		case _hoops_SSSGC:
		case _hoops_GGGRC:
			list = odl->item.texture.id;
			break;

		case _hoops_HCSGC: {
			RGB const *_hoops_RAC = &(nr->_hoops_IHA->_hoops_CHA->color[_hoops_ACA]);
			unsigned char _hoops_RGGRC;
			int _hoops_AGGRC;
			float _hoops_PHCHR;
			_hoops_PHCHR = (_hoops_RAC->red + _hoops_RAC->green + _hoops_RAC->blue) / 3;
			if (_hoops_PHCHR < 0.0f) _hoops_PHCHR = 0.0f;
			if (_hoops_PHCHR > 1.0f) _hoops_PHCHR = 1.0f;
			_hoops_RGGRC = (unsigned char)(_hoops_PHCHR * 255.0f);
			_hoops_AGGRC = (int)(_hoops_PHCHR * (_hoops_PGGRC-1));

			if (!odl->item.texture._hoops_SRAGR)
				ZALLOC_ARRAY(odl->item.texture._hoops_SRAGR, _hoops_PGGRC, GLuint);
			if (!odl->item.texture._hoops_SRAGR[_hoops_AGGRC]) {
				OGL_ALLOC_TEXTURE(list);
				odl->item.texture._hoops_SRAGR[_hoops_AGGRC] = list;
				_hoops_RACR = true;

				if (!BIT (txr->_hoops_RHGH->flags, _hoops_GRRH))
					HD_Set_Image_Alpha(txr->_hoops_RHGH, _hoops_RGGRC);
			}
			else
				list = odl->item.texture._hoops_SRAGR[_hoops_AGGRC];
		} break;

		default:break;
	}

	if (_hoops_RACR) {
		int format = 0;

		_hoops_PPRGC(_hoops_CSRGR, _hoops_GRRA);
		_hoops_IPRGC(_hoops_CSRGR, _hoops_GRRA, GL_TEXTURE_2D, list);

		ASSERT (txr->_hoops_RHGH->width <= _hoops_CSRGR->_hoops_HPHGC + (BIT(txr->_hoops_RHGH->flags, _hoops_AGSC)?2:0));
		ASSERT (txr->_hoops_RHGH->height <= _hoops_CSRGR->_hoops_HPHGC + (BIT(txr->_hoops_RHGH->flags, _hoops_AGSC)?2:0));

		switch (txr->_hoops_RHGH->format) {
			case _hoops_AHGH:
				format = GL_LUMINANCE;
				if (txr->_hoops_CGA == _hoops_SGA) {
					if (BIT (txr->_hoops_RHGH->flags, _hoops_HAAH)) {
						if (_hoops_CSRGR->_hoops_AHPGC)
							_hoops_CCSGC = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
						else
							_hoops_CCSGC = 4;
					}
					else
						_hoops_CCSGC = 4;
				}
				else {
					if (BIT (txr->_hoops_RHGH->flags, _hoops_HAAH)) {
						if (_hoops_CSRGR->_hoops_AHPGC)
							_hoops_CCSGC = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
						else
							_hoops_CCSGC = 1;
					}
					else
						_hoops_CCSGC = 1;
				}
			break;
			case _hoops_HHGH:
				format = GL_RGB;
				if (txr->_hoops_CGA == _hoops_SGA) {
					if (BIT (txr->_hoops_RHGH->flags, _hoops_HAAH)) {
						if (_hoops_CSRGR->_hoops_AHPGC)
							_hoops_CCSGC = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
						else
							_hoops_CCSGC = 4;
					}
					else
						_hoops_CCSGC = 4;
				}
				else {
					if (BIT (txr->_hoops_RHGH->flags, _hoops_HAAH)) {
						if (_hoops_CSRGR->_hoops_AHPGC)
							_hoops_CCSGC = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
						else
							_hoops_CCSGC = 3;
					}
					else
						_hoops_CCSGC = 3;
				}
			break;
			case Image_RGBA32:
				format = GL_RGBA;
				if (BIT (txr->_hoops_RHGH->flags, _hoops_HAAH)) {
					if (_hoops_CSRGR->_hoops_AHPGC)
						_hoops_CCSGC = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
					else
						_hoops_CCSGC = 4;
				}
				else
					_hoops_CCSGC = 4;
			break;

			default:
				HE_ERROR (HEC_TEXTURE, HES_PROCEDURAL_ERROR, "Unexpected texture format in opengl driver.");
				return 0;
		}

		if (BIT(txr->_hoops_RHGH->flags, _hoops_AGSC)) {
			glTexImage2D (GL_TEXTURE_2D, 0, _hoops_CCSGC,
				  txr->_hoops_RHGH->width,
				  txr->_hoops_RHGH->height,
				  1, format, GL_UNSIGNED_BYTE,
				  (GLvoid *)txr->_hoops_RHGH->_hoops_PHGH);
			_hoops_GPRH(_hoops_RPRH)++;
			if (txr->_hoops_RARH == _hoops_PARH ||
				txr->_hoops_RARH == _hoops_AARH) {
				/* _hoops_RRP _hoops_HGGRC _hoops_CSCR _hoops_RSAIP _hoops_RSAIP _hoops_RSAIP*/
				_hoops_HIGH _hoops_IIGH = txr->_hoops_RHGH->flags;
				HD_Activate_Texture_Image(nr, txr, _hoops_ACRRP|(_hoops_IIGH&~_hoops_AGSC), _hoops_CCGH, _hoops_ICGH, _hoops_CCGH, _hoops_ICGH);
				gluBuild2DMipmaps (GL_TEXTURE_2D, _hoops_CCSGC,
					txr->_hoops_RHGH->width,
					txr->_hoops_RHGH->height,
					format, GL_UNSIGNED_BYTE,
					(GLvoid *)txr->_hoops_RHGH->_hoops_PHGH);
				/* _hoops_RSAIP _hoops_RSAIP _hoops_RSAIP */
				txr->_hoops_RHGH->flags &= ~_hoops_RCRRP;
			}
		}
		else {
			glTexImage2D (GL_TEXTURE_2D, 0, _hoops_CCSGC,
				txr->_hoops_RHGH->width,
				txr->_hoops_RHGH->height,
				0, format, GL_UNSIGNED_BYTE,
				(GLvoid *)txr->_hoops_RHGH->_hoops_PHGH);
			if (txr->_hoops_RARH == _hoops_PARH ||
					txr->_hoops_RARH == _hoops_AARH)
				gluBuild2DMipmaps (GL_TEXTURE_2D, _hoops_CCSGC,
					txr->_hoops_RHGH->width,
					txr->_hoops_RHGH->height,
					format, GL_UNSIGNED_BYTE,
					(GLvoid *)txr->_hoops_RHGH->_hoops_PHGH);
		}
		//_hoops_RHI _hoops_AI _hoops_RRP _hoops_IS _hoops_SHH _hoops_IGGRC _hoops_SPHR _hoops_IS _hoops_HHSA _hoops_AIIR _hoops_HIS _hoops_GA'_hoops_RA _hoops_APRI
		if (BIT (txr->_hoops_RHGH->flags, _hoops_GPAH) && 
			!BIT (_hoops_GCI, _hoops_HCSGC)) {
			Image *_hoops_CGGRC = txr->_hoops_RHGH;
			int _hoops_RPAH = (long)_hoops_CGGRC->row_bytes * (long)_hoops_CGGRC->height;

			ASSERT (!BIT (txr->_hoops_RHGH->flags, _hoops_GRRH));  //_hoops_PAHA'_hoops_RA _hoops_HGCR _hoops_ARI _hoops_RRPC _hoops_CCA _hoops_RH _hoops_PSHR _hoops_CSCR
			ASSERT (BIT (_hoops_CGGRC->flags, _hoops_HHRH));
			ASSERT (!BIT (_hoops_CGGRC->flags, _hoops_SSGH));
			FREE_ARRAY (_hoops_CGGRC->_hoops_PHGH, _hoops_RPAH, char);
			if (_hoops_CGGRC->rasters != null) {
				FREE_ARRAY (_hoops_CGGRC->rasters, _hoops_CGGRC->height, void *);
				_hoops_CGGRC->rasters = null;
			}
			_hoops_CGGRC->_hoops_PHGH = null;
			_hoops_CGGRC->flags |= (_hoops_GRRH|_hoops_APAH);
			odl->_hoops_PPAH->owner = (_hoops_HPAH *) txr->_hoops_RHGH;
		}
		HD_Clean_Texture_Image_Cache(nr, txr);
		_hoops_GPRH(_hoops_RPRH)++;

		if (_hoops_SCSGC != _hoops_RSARR)
			_hoops_IPRGC(_hoops_CSRGR, _hoops_GRRA, GL_TEXTURE_2D, _hoops_SCSGC);
	}

	return list;
}

/*
 * _hoops_PGAA
 */
local void
_hoops_SGGRC (Net_Rendition const & nr)
{
	AGLM(OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);)
	_hoops_AIGH *_hoops_PAGR;
	unsigned char * _hoops_IGHSI;
	int _hoops_CASGC;
 	_hoops_AIGH *_hoops_PAAC;
	RGB color = nr->_hoops_IHA->_hoops_CHA->_hoops_CSHR;
	int i;

	_hoops_CASGC = 4;
	ALLOC_ARRAY(_hoops_IGHSI, 4 * _hoops_CASGC, unsigned char);
	_hoops_PAAC = _hoops_PAGR = (_hoops_AIGH *) _hoops_IGHSI;

	for (i=0; i<4; i++) {
		_hoops_IGHSI[i*_hoops_CASGC] = (unsigned char)(255.99f * color.red);
		_hoops_IGHSI[i*_hoops_CASGC+1] = (unsigned char)(255.99f * color.green);
		_hoops_IGHSI[i*_hoops_CASGC+2] = (unsigned char)(255.99f * color.blue);
		_hoops_IGHSI[i*_hoops_CASGC+3] = (unsigned char)255;
	}

	glTexImage2D (GL_TEXTURE_2D, 0, _hoops_CASGC,
			  2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)_hoops_PAGR);
	_hoops_GPRH(_hoops_RPRH)++;

	FREE_ARRAY(_hoops_PAGR, 4 * _hoops_CASGC, unsigned char);
}



local bool
_hoops_GRGRC (OGLData alter * _hoops_CSRGR, Net_Rendition const & nr, int _hoops_GRRA) {
 	GLuint list;

	bool _hoops_RRGRC = true;


	if (_hoops_CSRGR->_hoops_CSC._hoops_GSCGC == _hoops_RSARR) {
		OGL_ALLOC_TEXTURE(list);
		if (!list) return false;
		_hoops_CSRGR->_hoops_CSC._hoops_GSCGC = list;
	}
	else {
		list = _hoops_CSRGR->_hoops_CSC._hoops_GSCGC;
	}

	if (_hoops_CSRGR->_hoops_CSC._hoops_SGAGC[_hoops_GRRA] != list) {
		_hoops_CSRGR->_hoops_CSC._hoops_SGAGC[_hoops_GRRA] = list;

/*		_hoops_RPP (!_hoops_AGGC (_hoops_ARGRC->_hoops_CPGGR, _hoops_PRGRC | _hoops_HRGRC) &&
				(_hoops_HGPGA->_hoops_IHAH._hoops_IRGRC == _hoops_ARGRC->_hoops_GCHR)) {
			_hoops_CRGRC = _hoops_RCPP;
			*/
		if (1) {
			_hoops_APSS(_hoops_CSRGR,_hoops_GRRA);
			_hoops_PPRGC(_hoops_CSRGR, _hoops_GRRA);
			_hoops_IPRGC(_hoops_CSRGR, _hoops_GRRA, GL_TEXTURE_2D, list);
		}
	}
	else {
		/*
		_hoops_RPP (!_hoops_AGGC (_hoops_ARGRC->_hoops_CPGGR, _hoops_PRGRC | _hoops_HRGRC) &&
				(_hoops_HGPGA->_hoops_IHAH._hoops_IRGRC == _hoops_ARGRC->_hoops_GCHR)) {
			_hoops_CRGRC = _hoops_RCPP;
		}
*/
	}

	if (_hoops_RRGRC) {
		_hoops_IPRGC(_hoops_CSRGR, _hoops_GRRA, GL_TEXTURE_2D, list);
		_hoops_SGGRC (nr);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	_hoops_SRGRC(_hoops_CSRGR, _hoops_GRRA);

	return true;
}



local bool
_hoops_GSAC (
	OGLData alter *_hoops_CSRGR,
	Net_Rendition const & nr,
	_hoops_RCR alter *txr,
	OGL_Render_Control_Flags _hoops_GAGRC,
	_hoops_ARGRA _hoops_GCI,
	GLuint id,
	int _hoops_GRRA) 
{
	GLenum _hoops_CAGRR;
	_hoops_GAAIR alter *tm = (_hoops_GAAIR alter *) nr->_hoops_IRR->_hoops_APGH;

	if (txr && BIT (txr->flags, _hoops_CSGH))
		_hoops_CAGRR = GL_TEXTURE_3D;
	else
		_hoops_CAGRR = GL_TEXTURE_2D;

	if (BIT(nr->_hoops_SRA->flags, _hoops_CHSI))
		return false;

	_hoops_PPRGC(_hoops_CSRGR, _hoops_GRRA);
	_hoops_IPRGC(_hoops_CSRGR, _hoops_GRRA, _hoops_CAGRR, id);

	/* _hoops_RGR _hoops_IGI _hoops_IS _hoops_SHH _hoops_RGAR _hoops_RPP
	   _hoops_IRRC (_hoops_SCII->_hoops_CCGIP->_hoops_RAGRC, _hoops_AAGRC))
	   _hoops_HIH _hoops_SR _hoops_GSGI _hoops_SGS _hoops_HHH _hoops_PAGRC _hoops_CHH _hoops_SHSP _hoops_SCH _hoops_GPP _hoops_PRGI _hoops_RPP _hoops_SR _hoops_HAGRC _hoops_SCH _hoops_HAR _hoops_IS. */
	ENSURE_TEXTURE_PERSPECTIVE_CORRECTION_ON(_hoops_CSRGR, _hoops_GRRA);

	if (_hoops_GCI == _hoops_HCSGC) {
		ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_CAGRR, GL_REPEAT, _hoops_GRRA);
		_hoops_SAIRH(_hoops_CSRGR, _hoops_CAGRR, GL_REPEAT, _hoops_GRRA);
		glTexParameteri(_hoops_CAGRR, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(_hoops_CAGRR, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else if (txr) {
		switch (txr->_hoops_CGA) {
			case _hoops_ASGRP:
				ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_CAGRR, GL_REPEAT, _hoops_GRRA);
				_hoops_SAIRH(_hoops_CSRGR, _hoops_CAGRR, GL_REPEAT, _hoops_GRRA);
			break;
			case _hoops_ASCC:
				/* _hoops_PAH'_hoops_RA _hoops_SGH _hoops_RGR _hoops_PGGA _hoops_IIGR _hoops_IAGRC _hoops_RGAP */
				/* _hoops_IRRC(_hoops_CAGRC->_hoops_ARRH->_hoops_SGI, _hoops_SAGRC) _hoops_RSAIP _hoops_RSAIP _hoops_RSAIP */
				if (_hoops_CSRGR->_hoops_IRPGC) {
					ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_CAGRR, GL_CLAMP, _hoops_GRRA);
					_hoops_SAIRH(_hoops_CSRGR, _hoops_CAGRR, GL_CLAMP, _hoops_GRRA);
				}
				else {
					ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_CAGRR, GL_CLAMP_TO_EDGE, _hoops_GRRA);
					_hoops_SAIRH(_hoops_CSRGR, _hoops_CAGRR, GL_CLAMP_TO_EDGE, _hoops_GRRA);
				}
			break;
			case _hoops_PSGRP:
				if (_hoops_CSRGR->_hoops_AAPGC) {
					ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_CAGRR, GL_MIRRORED_REPEAT_ARB, _hoops_GRRA);
					_hoops_SAIRH(_hoops_CSRGR, _hoops_CAGRR, GL_MIRRORED_REPEAT_ARB, _hoops_GRRA);
				}
				else {
					ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_CAGRR, GL_REPEAT, _hoops_GRRA);
					_hoops_SAIRH(_hoops_CSRGR, _hoops_CAGRR, GL_REPEAT, _hoops_GRRA);
				}
			break;
			case _hoops_SGA:
				if (!_hoops_CSRGR->_hoops_CAPGC) {
					ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_CAGRR, GL_CLAMP, _hoops_GRRA);
					_hoops_SAIRH(_hoops_CSRGR, _hoops_CAGRR, GL_CLAMP, _hoops_GRRA);
				}
				else {
					ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_CAGRR, GL_CLAMP_TO_BORDER_ARB, _hoops_GRRA);
					_hoops_SAIRH(_hoops_CSRGR, _hoops_CAGRR, GL_CLAMP_TO_BORDER_ARB, _hoops_GRRA);
				}
				_hoops_IPGP (_hoops_CSRGR, true);
			break;
		}

		/* _hoops_SR _hoops_CGH _hoops_IIP _hoops_CAH _hoops_PGGA _hoops_IIGR _hoops_PIGGH */
		if (txr->_hoops_PSCC == _hoops_HSCC) {
			glTexParameteri(_hoops_CAGRR, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			if (txr->_hoops_RARH == _hoops_AARH ||
				txr->_hoops_RARH == _hoops_PARH) {
				glTexParameteri(_hoops_CAGRR, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			}
			else {
				glTexParameteri(_hoops_CAGRR, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}
		}
		else {
			glTexParameteri(_hoops_CAGRR, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (txr->_hoops_RARH == _hoops_AARH ||
				txr->_hoops_RARH == _hoops_PARH) {
				glTexParameteri(_hoops_CAGRR, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			}
			else {
				glTexParameteri(_hoops_CAGRR, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
		}
		_hoops_SRGRC(_hoops_CSRGR, _hoops_GRRA);
	}

	/*
	 * _hoops_PHAA _hoops_RH _hoops_HRSAR _hoops_HH _hoops_RSGA _hoops_IPIH _hoops_ARP (_hoops_RPP _hoops_GII).
	 * _hoops_HAPI _hoops_SR _hoops_ARP _hoops_GH _hoops_PCCP _hoops_SRGH _hoops_RSGA _hoops_PPR _hoops_GACC _hoops_IHAA _hoops_RH _hoops_HH.
	 */
	glMatrixMode (GL_TEXTURE);
	if (txr && BIT(txr->flags, _hoops_CSGH))
		glLoadMatrixf (&_hoops_AAIRH[0][0]);
	else if (_hoops_GCI == _hoops_HCSGC &&
	    BIT(nr->transform_rendition->flags, _hoops_PGCH))
	    glLoadMatrixf (&_hoops_GPSGC[0][0]);
	else
		glLoadMatrixf (&_hoops_PAIRH[0][0]);


	if (!BIT (_hoops_GAGRC, _hoops_GPGRC)) {
	    if (txr->_hoops_GAGH) {
		    /* _hoops_SGPR _hoops_RGAR _hoops_IRS _hoops_HH-_hoops_IIHA _hoops_RSGA */
		    glMultMatrixf (&txr->_hoops_GAGH->matrix._hoops_APRA->data.elements[0][0]);
	    }
#ifdef _hoops_GCGGC
		// _hoops_RPGRC: _hoops_AH _hoops_RSAIP _hoops_IS _hoops_RRS _hoops_IRISR _hoops_HII _hoops_APGRC _hoops_RH _hoops_HH _hoops_HCIA _hoops_GGR _hoops_GSIPR-_hoops_GPCGP
		// _hoops_AIHH _hoops_PPGRC _hoops_RCSRR #10535
		else
#endif
	    if ((txr == null || !BIT(txr->flags, _hoops_IPGH)) &&
			ANYBIT (tm->matrix._hoops_RAGR, _hoops_CICH)) {
		    /* _hoops_SGPR _hoops_RGAR _hoops_IRS _hoops_CAGH-_hoops_IIHA _hoops_RSGA */
		    if (tm->matrix._hoops_APRA == null)
			    HI_Validate_Matrix_Adjoint ((_hoops_HRPA *)&tm->matrix);
		    glMultMatrixf (&tm->matrix._hoops_APRA->data.elements[0][0]);
	    }

	    if (txr->_hoops_RHGH->flags&_hoops_SIRRP) {
		    glMultMatrixf (&_hoops_RPSGC[0][0]);
	    }
	}
	glMatrixMode (GL_MODELVIEW);

	return true;
}


local bool pre_pass(
	Net_Rendition const &		nr,
	OGL_Render_Control *		rc,
	Tristrip const *			ts)
{
	Display_Context const *		dc = nr->_hoops_SRA;
	OGLData alter *				_hoops_CSRGR = OGLD (dc);
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HHA const &	matr = _hoops_SIGA->_hoops_CHA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Point const *				points = ts->points;
	Vector const *				normals = ts->_hoops_ICHA;
    _hoops_RSSH alter	*			params;
	int 						point_count = ts->point_count;
	int 						_hoops_AHCGR = 0;
	int							i;

	if (BIT(dc->flags, _hoops_CHSI) ||
		_hoops_CSRGR->_hoops_CSC._hoops_IPAGC)
		return false;

#ifdef _hoops_GCGGC
	_hoops_HPGRC _hoops_IPGRC;
	_hoops_RCGGC* _hoops_CPGRC = _hoops_ACGGC(dc->_hoops_RIGC->thread_id);
	_hoops_CSRGR->_hoops_SPGRC = false;
	if (_hoops_CPGRC) {
		// _hoops_GHGRC 473716 - _hoops_AIRI _hoops_CPCI _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_RHGRC.  _hoops_RHHP _hoops_ICSHR _hoops_GHC _hoops_AA _hoops_HS _hoops_SPR, _hoops_HIH _hoops_SSIA
		// _hoops_GA'_hoops_RA _hoops_HS _hoops_PCCP _hoops_RRRPR.  _hoops_GCIAR _hoops_SHS _hoops_SR _hoops_GHAA _hoops_ISCP _hoops_AIRRR _hoops_IS _hoops_SSCP _hoops_GIPR.  _hoops_PS _hoops_HHGC _hoops_IS _hoops_GHAA _hoops_AIRRR _hoops_IS
		// _hoops_AIRI _hoops_CPCI, _hoops_HIH _hoops_HAR _hoops_IS _hoops_SHHP _hoops_ICSHR _hoops_GHC.  _hoops_HGI _hoops_SPS _hoops_RPP _hoops_RPGP _hoops_RHAP _hoops_SGS.
		if (!ts->_hoops_GSCP || ts->_hoops_GSCP->owner) {

			if (rc->pass == 0 &&
				!BIT(dc->flags, _hoops_GPHHP) &&
				!BIT(dc->flags, _hoops_GIHCP)) {

				OGL_Display_List * dl = (ts && ts->_hoops_GAHA) ? (OGL_Display_List *)ts->_hoops_GAHA->list : NULL;
				_hoops_IPGRC._hoops_AHGRC((void*)&nr, (void*)dl, false);
				_hoops_CPGRC->InitShader(_hoops_IPGRC, dc->_hoops_RIGC->thread_id);

				_hoops_CSRGR->_hoops_CSC._hoops_HRIGC = true;
				_hoops_CSRGR->_hoops_CSC._hoops_GSCH[0] = _hoops_RSARR;
				_hoops_PIIGC(_hoops_CSRGR, nr);

				if (BIT (ts->_hoops_CARI, _hoops_HPCGP) && !_hoops_CSRGR->_hoops_GSGRR)
				{
					_hoops_CSRGR->_hoops_SPGRC = true;
					rc->params[rc->pass] = ts->_hoops_CCHA;
					rc->param_width[rc->pass] = ts->_hoops_GSHA;
				}
			}
		}
	}

	if (strncmp(_hoops_IPGRC._hoops_PHGRC, "swbg_", 5) == 0)
		return false;

	// _hoops_RPGRC: _hoops_HHGRC->_hoops_RIH > 0 _hoops_SIGH _hoops_RH _hoops_GCAC _hoops_IIGR _hoops_IHGRC _hoops_AI.  _hoops_IRISR _hoops_RRRS _hoops_AGAP _hoops_CCA _hoops_RH _hoops_PSHR _hoops_PPRGR _hoops_PIRA
	// _hoops_GAR _hoops_RH _hoops_HSSSH _hoops_HSP.  _hoops_PS _hoops_HHGC _hoops_CAPR _hoops_SHR _hoops_CHCC _hoops_AGPC _hoops_CIGC.  _hoops_RSCS _hoops_RH _hoops_RHGS _hoops_PIRA _hoops_HIS _hoops_SR _hoops_PAH _hoops_PHIH _hoops_SCH
	float _hoops_CHGRC = matr->_hoops_IRIR;
	if (rc->pass > 0)
		const_cast<_hoops_HHA&>(matr)->_hoops_IRIR = 1.0f;

#endif

	if (BIT(rc->flags[rc->pass], _hoops_SHGRC))
		_hoops_CSRGR->_hoops_CSC._hoops_HRIGC = true;

	if (_hoops_CSRGR->_hoops_RPCI != _hoops_SIGA->_hoops_CPA || rc->pass != 0) {
		if (_hoops_SIGA->_hoops_AGP != null &&
			BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES)) {
			RGB _hoops_CRIRH;

			_hoops_CRIRH.red = _hoops_CRIRH.green = _hoops_CRIRH.blue = 1.0f;
			if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA)) {
			    /* _hoops_CIS _hoops_PIHA _hoops_GHSGR _hoops_SGS _hoops_SSSC _hoops_CHR _hoops_RPHR _hoops_IH _hoops_RAHCP _hoops_RPIC */
			    if (!_hoops_HARGC(nr, _hoops_SIGA->_hoops_AGP, _hoops_SIGA->_hoops_CHA))
				    _hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
						"if phong shading is not possible, it should have"
						" been punted before the call to pre pass");
			}
			else
			    _hoops_GIGRC (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_AGP);
			if (rc->_hoops_GCI[rc->pass] != _hoops_RIGRC)
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, matr, &rc->_hoops_AIGRC[rc->pass], &rc->_hoops_PIGRC[rc->pass]);
		}
		else if (_hoops_SIGA->_hoops_CHA->_hoops_IRIR != 1.0f ||
			 rc->txr[rc->pass] != 0 ||
			 _hoops_SIGA->color != _hoops_SIGA->_hoops_RGIR) {

			_hoops_SCIGC (_hoops_CSRGR);
			if (rc->_hoops_GCI[rc->pass] != _hoops_RIGRC)
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, matr, &rc->_hoops_AIGRC[rc->pass], &rc->_hoops_PIGRC[rc->pass]);
		}
		else {
			_hoops_SCIGC (_hoops_CSRGR);
			_hoops_APIGC (_hoops_CSRGR, &_hoops_SIGA->color, nr);
		}
		if (rc->pass == 0)
			_hoops_CSRGR->_hoops_RPCI = _hoops_SIGA->_hoops_CPA;
		else
			_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	}

_hoops_HIGRC:

#ifdef _hoops_GCGGC
	// _hoops_IPRP _hoops_RH _hoops_RHGS _hoops_PPRGR _hoops_PIRA.
	if (rc->pass > 0)
		const_cast<_hoops_HHA&>(matr)->_hoops_IRIR = _hoops_CHGRC;

	if (!_hoops_IPGRC._hoops_IIGRC)
	{
#endif

	if (BIT(rc->flags[rc->pass], _hoops_CIGRC)) {
		if (_hoops_CSRGR->_hoops_CRPGC)
			glLightModelf (GL_LIGHT_MODEL_COLOR_CONTROL_EXT,GL_SINGLE_COLOR_EXT);

 		if ((rc->_hoops_GCI[rc->pass] == _hoops_PCSGC && rc->_hoops_SIGRC[rc->pass] == 1) || (_hoops_AHCGR != 0)) {
			if (rc->txr[rc->pass])
				_hoops_GSAC (_hoops_CSRGR, nr, rc->txr[rc->pass], rc->flags[rc->pass], rc->_hoops_GCI[rc->pass], rc->id[rc->pass], 0);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);     /*  _hoops_HGGRI _hoops_IRS _hoops_GCGRC _hoops_CAIH...*/
			glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_DOT3_RGB_EXT);

			glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_TEXTURE);           /* _hoops_GAPA _hoops_RH _hoops_PGGIR (_hoops_IIGR _hoops_PGGIR._hoops_ISAII) _hoops_PGAP _hoops_HRGR _hoops_GCSS _hoops_GGR _hoops_IRS _hoops_GSSR _hoops_ARCR _hoops_HH... */
			glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND0_RGB_EXT, GL_SRC_COLOR);

			glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_PRIMARY_COLOR_EXT); /* _hoops_CCA _hoops_RH _hoops_ISAII (_hoops_IIGR _hoops_PGGIR._hoops_ISAII) _hoops_PGAP _hoops_HRGR _hoops_GCSS _hoops_GGR _hoops_RH _hoops_GPHA'_hoops_GRI _hoops_SPI _hoops_HAIR. */
			glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, GL_SRC_COLOR);
		}
		else {
 			if (rc->_hoops_SIGRC[rc->pass] == 0 && rc->_hoops_GCI[rc->pass] == _hoops_PCSGC)
				_hoops_GRGRC (_hoops_CSRGR,nr, 1);
			else if (rc->txr[rc->pass])
				_hoops_GSAC (_hoops_CSRGR, nr, rc->txr[rc->pass], rc->flags[rc->pass], rc->_hoops_GCI[rc->pass], rc->id[rc->pass], 1);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);  /* _hoops_SSIAH... */
			glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);

			glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_PREVIOUS_EXT);
			glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND0_RGB_EXT, GL_SRC_COLOR);    /* _hoops_RH _hoops_HAIR _hoops_ACRGI _hoops_CGI _hoops_ISHP _hoops_HII _hoops_RH _hoops_PGHC _hoops_HPPCR (_hoops_HPPCR 0) _hoops_CCA... */

			glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_TEXTURE);
			glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, GL_SRC_COLOR);    /* _hoops_RH _hoops_HH _hoops_IH _hoops_RGR _hoops_HPPCR _hoops_CCA. */
 		}
	}
	else  if (rc->txr[rc->pass])
		_hoops_GSAC (_hoops_CSRGR, nr, rc->txr[rc->pass], rc->flags[rc->pass], rc->_hoops_GCI[rc->pass], rc->id[rc->pass], 0);

	switch (rc->_hoops_GCI[rc->pass]) {
		case _hoops_RCGRC: {
			if (BIT(rc->flags[rc->pass], _hoops_ACGRC)) {
				/* _hoops_RSPH _hoops_APIR _hoops_IS _hoops_PGS _hoops_IH _hoops_PCGRC */
				GLfloat alter _hoops_CRIRH[4] = { 1, 1, 1, 1 };
				GLfloat alter _hoops_HCGRC[4] = { 0, 0, 0, 1 };

				ENSURE_MATERIAL_COLOR_OFF (_hoops_CSRGR);
				_hoops_GASGC (_hoops_CSRGR, GL_FRONT_AND_BACK);
				glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, _hoops_CRIRH);
				glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, _hoops_HCGRC);
				_hoops_ICGRC(_hoops_CSRGR);
			}
			if (_hoops_SIGA->color != _hoops_SIGA->_hoops_RGIR &&
				_hoops_CSRGR->_hoops_SARGC == _hoops_RHRGC) {
				/*_hoops_RSPH _hoops_RRR _hoops_IH _hoops_GAACP _hoops_PGCR _hoops_RPSA _hoops_RCA */
				GLfloat _hoops_PHRGC[4];

				_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.red = _hoops_PHRGC[0] = 1.0f;
				_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.green = _hoops_PHRGC[1] = 1.0f;
				_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.blue = _hoops_PHRGC[2] = 1.0f;
				_hoops_PHRGC[3] = 1.0;	/* _hoops_AIIR _hoops_RCAP == _hoops_PPRGR */
				glLightModelfv (GL_LIGHT_MODEL_AMBIENT, _hoops_PHRGC);

				_hoops_PHRGC[0] = 0.0f;
				_hoops_PHRGC[1] = 0.0f;
				_hoops_PHRGC[2] = 0.0f;
				_hoops_PHRGC[3] = 1.0;
				glLightfv (GL_LIGHT0, GL_DIFFUSE, _hoops_PHRGC);

				/* _hoops_CCGRC _hoops_SCGRC 59** _hoops_APAC _hoops_HS _hoops_IRS _hoops_GSGRC _hoops_CAGRH _hoops_CCA 2-_hoops_RPSA _hoops_RCA _hoops_PPR _hoops_PSP
					_hoops_RIGII _hoops_HII _hoops_SPI _hoops_PAR _hoops_GHI */
				if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_4142_WORKAROUND))
					_hoops_PHRGC[0] = 0.01f;

				glLightfv (GL_LIGHT0, GL_SPECULAR, _hoops_PHRGC);
				glEnable (GL_LIGHT0);
				glEnable (GL_LIGHTING);
			}
		}	break;

		case _hoops_RIGRC: {
   			_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, _hoops_AHCGR);
			OGL_SET_TEXTURE_INDEXED_MATERIAL (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_CHA);
		} break;

		case _hoops_ISSGC:
		case _hoops_CSSGC:
		case _hoops_PCSGC: {
			if (rc->txr[rc->pass] && 
				BIT (rc->txr[rc->pass]->flags, _hoops_CSGH))
				_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_3D, _hoops_AHCGR);
			else
				_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, _hoops_AHCGR);
			if (rc->txr[rc->pass]) {
			    if (BIT (rc->txr[rc->pass]->_hoops_SCR, _hoops_IGA) ||
				    BIT (rc->flags[rc->pass], _hoops_ACGRC)) {
				    if (rc->_hoops_GCI[rc->pass] == _hoops_CSSGC) {
					    ENSURE_TEXTURE_ENV_MODE (_hoops_CSRGR, GL_DECAL, _hoops_AHCGR);
					    _hoops_ASGRC (_hoops_CSRGR);
					    ENSURE_BLEND_FUNC (_hoops_CSRGR, GL_ZERO, GL_SRC_COLOR);
				    }
				    else {
					    ENSURE_TEXTURE_ENV_MODE (_hoops_CSRGR, GL_MODULATE, _hoops_AHCGR);
					    _hoops_ASGRC (_hoops_CSRGR);
					    ENSURE_BLEND_FUNC (_hoops_CSRGR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				    }
			    }
			    else if (!BIT(rc->txr[rc->pass]->flags, _hoops_IAPS) ||
						  _hoops_CSRGR->_hoops_PSGRC) {
				    ENSURE_TEXTURE_ENV_MODE (_hoops_CSRGR, GL_MODULATE, _hoops_AHCGR);
			    }
			    else {
				    ENSURE_TEXTURE_ENV_MODE (_hoops_CSRGR, GL_MODULATE, _hoops_AHCGR);
				    _hoops_ASGRC (_hoops_CSRGR);
				    ENSURE_BLEND_FUNC (_hoops_CSRGR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			    }
			}
			if (BIT (rc->flags[rc->pass], _hoops_HSGRC)) {
 			    ENSURE_TEXTURE_GEN_MODE (_hoops_CSRGR, GL_OBJECT_LINEAR, _hoops_AHCGR);
			    _hoops_ISGRC (_hoops_CSRGR, _hoops_AHCGR);

				nr->transform_rendition->_hoops_IPH->_hoops_PPRA();
				float _hoops_CSGRC[4];
				_hoops_CSGRC[0] = _hoops_IHCR->_hoops_IPH->data._hoops_APRA->data.elements[0][0];
				_hoops_CSGRC[1] = _hoops_IHCR->_hoops_IPH->data._hoops_APRA->data.elements[0][1];
				_hoops_CSGRC[2] = _hoops_IHCR->_hoops_IPH->data._hoops_APRA->data.elements[0][2];
				_hoops_CSGRC[3] = _hoops_IHCR->_hoops_IPH->data.elements[3][0];

				float _hoops_SSGRC[4];
				_hoops_SSGRC[0] = _hoops_IHCR->_hoops_IPH->data._hoops_APRA->data.elements[1][0];
				_hoops_SSGRC[1] = _hoops_IHCR->_hoops_IPH->data._hoops_APRA->data.elements[1][1];
				_hoops_SSGRC[2] = _hoops_IHCR->_hoops_IPH->data._hoops_APRA->data.elements[1][2];
				_hoops_SSGRC[3] = _hoops_IHCR->_hoops_IPH->data.elements[3][1];

				glTexGenfv(GL_S, GL_OBJECT_PLANE, (float *) _hoops_CSGRC);
				glTexGenfv(GL_T, GL_OBJECT_PLANE, (float *) _hoops_SSGRC);

			}
		}	break;

		case _hoops_HCSGC: {
    		_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, 0);
			if (BIT (rc->flags[rc->pass], _hoops_GGRRC)) {
			    _hoops_ISGRC (_hoops_CSRGR, 0);
			    ENSURE_TEXTURE_GEN_MODE (_hoops_CSRGR, GL_SPHERE_MAP,0);

			}
			else if (rc->txr[rc->pass]->_hoops_PSR == _hoops_HSR) {
			    _hoops_HHRA const	*_hoops_SPH = nr->transform_rendition->_hoops_SPH;
				bool _hoops_RGRRC = true;

				ALLOC_ARRAY_CACHED(params, 2*point_count, _hoops_RSSH);
			    rc->params[rc->pass] = params;
			    rc->_hoops_RSIC[rc->pass] = 2*point_count;
			    rc->flags[rc->pass] |= _hoops_AGRRC;

				if (_hoops_RGRRC) {
					if (!normals) {
						_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
									"Environment mapping via physical reflection requires vertex normal in opengl driver");
					}

					nr->transform_rendition->_hoops_IPH->_hoops_PPRA();
					//? _hoops_PGRRC((_hoops_HGRRC *)&_hoops_SARA->_hoops_IGRRC);

					for (i=0; i<point_count; i++) {
						_hoops_SGCC const &	_hoops_CGRRC = nr->transform_rendition->_hoops_IPH;
						Vector						_hoops_SGRRC;
						_hoops_RSSH					param[3];
						float 						_hoops_GRRRC;
						float 						tmp;
						_hoops_ARPA 						_hoops_RRRRC, _hoops_ARRRC;
						Point 						_hoops_PRRRC;

						_hoops_PRRRC.x = _hoops_HPRA (_hoops_CGRRC->data.elements, points[i]);
						_hoops_PRRRC.y = _hoops_IPRA (_hoops_CGRRC->data.elements, points[i]);
						_hoops_PRRRC.z = _hoops_CPRA (_hoops_CGRRC->data.elements, points[i]);

						_hoops_SGRRC.x = _hoops_PRRRC.x - _hoops_SPH->position.x;
						_hoops_SGRRC.y = _hoops_PRRRC.y - _hoops_SPH->position.y;
						_hoops_SGRRC.z = _hoops_PRRRC.z - _hoops_SPH->position.z;

						QUICK_NORMALIZE (_hoops_SGRRC);

						_hoops_RRRRC.a = normals[i].x;
						_hoops_RRRRC.b = normals[i].y;
						_hoops_RRRRC.c = normals[i].z;
						_hoops_RRRRC.d = -(normals[i].x*points[i].x +
											normals[i].y*points[i].y +
											normals[i].z*points[i].z);

						_hoops_ARRRC.a = _hoops_HRRRC (_hoops_CGRRC->data._hoops_APRA->data.elements, _hoops_RRRRC);
						_hoops_ARRRC.b = _hoops_IRRRC (_hoops_CGRRC->data._hoops_APRA->data.elements, _hoops_RRRRC);
						_hoops_ARRRC.c = _hoops_CRRRC (_hoops_CGRRC->data._hoops_APRA->data.elements, _hoops_RRRRC);
						_hoops_ARRRC.d = _hoops_CRRRC (_hoops_CGRRC->data._hoops_APRA->data.elements, _hoops_RRRRC);

						QUICK_NORMALIZE (_hoops_ARRRC);

						_hoops_GRRRC = _hoops_SGRRC.x * _hoops_ARRRC.a +
							_hoops_SGRRC.y * _hoops_ARRRC.b +
							_hoops_SGRRC.z * _hoops_ARRRC.c;

						_hoops_GRRRC *= 2.0f;

						param[0] = _hoops_SGRRC.x - _hoops_GRRRC * _hoops_ARRRC.a;
						param[1] = _hoops_SGRRC.y - _hoops_GRRRC * _hoops_ARRRC.b;
						param[2] = _hoops_SGRRC.z - _hoops_GRRRC * _hoops_ARRRC.c;

						/*_hoops_SRRRC _hoops_GARRC*/
						tmp = 1.0f - param[2];
						tmp = _hoops_SGIHR (param[0] * param[0] + param[1] * param[1] + tmp * tmp);

						if (tmp < 0.000001f)
							tmp = 0.000001f;

						tmp = 0.5f / tmp;

						params[2*i+0] = param[0] * tmp + 0.5f;
						params[2*i+1] = param[1] * tmp + 0.5f;

#if 0
						if (params[2*i+0] != params[2*i+0] || params[2*i+1] != params[2*i+1])
							_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "NAN");
#endif
					}
				}
			}
			else if (!BIT (ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
			    _hoops_HHRA const	*_hoops_SPH = nr->transform_rendition->_hoops_SPH;
				bool _hoops_RGRRC = true;
			    _hoops_HRPA	    _hoops_CGRRC;

				ALLOC_ARRAY_CACHED(params, 2*point_count, _hoops_RSSH);
			    rc->params[rc->pass] = params;
			    rc->_hoops_RSIC[rc->pass] = 2*point_count;
			    rc->flags[rc->pass] |= _hoops_AGRRC;

				if (_hoops_RGRRC) {
					if (!normals) {
						_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
									"Environment mapping requires vertex normal in opengl driver");
					}

					HI_Multiply_Matrices(&nr->transform_rendition->_hoops_IPH->data,
										 &_hoops_SPH->_hoops_PRPA, &_hoops_CGRRC);

					HI_Validate_Matrix_Adjoint(&_hoops_CGRRC);

					for (i=0; i<point_count; i++) {
						Vector _hoops_SGRRC;
						_hoops_ARPA _hoops_RRRRC, _hoops_ARRRC;
						_hoops_RSSH param[3];
						Point _hoops_PRRRC;
						float _hoops_GRRRC;
						float tmp;

						_hoops_PRRRC.x = _hoops_HPRA (_hoops_CGRRC.elements, points[i]);
						_hoops_PRRRC.y = _hoops_IPRA (_hoops_CGRRC.elements, points[i]);
						_hoops_PRRRC.z = _hoops_CPRA (_hoops_CGRRC.elements, points[i]);

						_hoops_SGRRC.x = 0.0f;
						_hoops_SGRRC.y = 0.0f;
						_hoops_SGRRC.z = 1.0f;


						_hoops_RRRRC.a = normals[i].x;
						_hoops_RRRRC.b = normals[i].y;
						_hoops_RRRRC.c = normals[i].z;
						_hoops_RRRRC.d = -(normals[i].x*points[i].x +
											normals[i].y*points[i].y +
											normals[i].z*points[i].z);

						_hoops_ARRRC.a = _hoops_HRRRC (_hoops_CGRRC._hoops_APRA->data.elements, _hoops_RRRRC);
						_hoops_ARRRC.b = _hoops_IRRRC (_hoops_CGRRC._hoops_APRA->data.elements, _hoops_RRRRC);
						_hoops_ARRRC.c = _hoops_CRRRC (_hoops_CGRRC._hoops_APRA->data.elements, _hoops_RRRRC);

						QUICK_NORMALIZE (_hoops_ARRRC);

						_hoops_GRRRC = _hoops_SGRRC.x * _hoops_ARRRC.a +
							_hoops_SGRRC.y * _hoops_ARRRC.b +
							_hoops_SGRRC.z * _hoops_ARRRC.c;

						_hoops_GRRRC *= 2.0f;

						param[0] = _hoops_SGRRC.x - _hoops_GRRRC * _hoops_ARRRC.a;
						param[1] = _hoops_SGRRC.y - _hoops_GRRRC * _hoops_ARRRC.b;
						param[2] = _hoops_SGRRC.z - _hoops_GRRRC * _hoops_ARRRC.c;

						/*_hoops_SRRRC _hoops_GARRC*/
						tmp = 1.0f - param[2];
						tmp = _hoops_SGIHR (param[0] * param[0] + param[1] * param[1] + tmp * tmp);

						if (tmp < 0.000001f)
							tmp = 0.000001f;

						tmp = 0.5f / tmp;

						params[2*i+0] = param[0] * tmp + 0.5f;
						params[2*i+1] = param[1] * tmp + 0.5f;

#if 0
						if (params[2*i+0] != params[2*i+0] || params[2*i+1] != params[2*i+1])
							_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "NAN");
#endif
					}
				}
			}

			ENSURE_TEXTURE_ENV_MODE (_hoops_CSRGR, GL_DECAL, _hoops_AHCGR);
		    _hoops_ASGRC (_hoops_CSRGR);
		    ENSURE_BLEND_FUNC (_hoops_CSRGR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			if (rc->pass != 0) {
				RGB const *color = &rc->_hoops_AIGRC[rc->pass];
				float _hoops_RARRC;
				RGB const *_hoops_RAC = &(nr->_hoops_IHA->_hoops_CHA->color[_hoops_ACA]);

			    if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA))
				    _hoops_CPRGC(_hoops_CSRGR);
				_hoops_RARRC = (_hoops_RAC->red + _hoops_RAC->green + _hoops_RAC->blue) / 3;
				_hoops_GASGC (_hoops_CSRGR, GL_FRONT_AND_BACK);
				FORCE_COLOR_4F(color->red, color->green, color->blue, _hoops_RARRC, false);
			}
			_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, 0);
		} break;

		case _hoops_SSSGC:{
			_hoops_PC const &		_hoops_HC = nr->_hoops_IHA->_hoops_AGP;
			_hoops_AS const *		light;
			GLfloat _hoops_PHRGC[4];

			if (_hoops_CSRGR->_hoops_CRPGC)
				glLightModelf (GL_LIGHT_MODEL_COLOR_CONTROL_EXT,GL_SINGLE_COLOR_EXT);
			_hoops_AARRC (_hoops_CSRGR,0);
			ENSURE_TEXTURE_ENV_MODE(_hoops_CSRGR, GL_MODULATE,_hoops_AHCGR);
			_hoops_ASGRC(_hoops_CSRGR);
			ENSURE_BLEND_FUNC(_hoops_CSRGR, GL_SRC_ALPHA, GL_ONE);

			/*_hoops_PSP _hoops_AASR _hoops_PSP _hoops_RAHCP _hoops_PPR _hoops_PSP _hoops_SPI _hoops_HGSR _hoops_RH _hoops_GHI _hoops_HAIR _hoops_IH _hoops_HCR _hoops_SS*/
			glDisable (GL_LIGHTING);
			_hoops_PHRGC[0] = 0.0;
			_hoops_PHRGC[1] = 0.0;
			_hoops_PHRGC[2] = 0.0;
			_hoops_PHRGC[3] = 1.0;
			glLightModelfv (GL_LIGHT_MODEL_AMBIENT, _hoops_PHRGC);
			if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA))
				_hoops_CPRGC(_hoops_CSRGR);
			light = _hoops_HC->_hoops_CGR;
			for (i = 0; i < _hoops_CSRGR->_hoops_CHRGC; i++) {
				GLfloat _hoops_HGSAI[4] = {0, 0, 0, 0};
				_hoops_PHRGC[0] = light->color.red;
				_hoops_PHRGC[1] = light->color.green;
				_hoops_PHRGC[2] = light->color.blue;
				_hoops_PHRGC[3] = 1.0;
				glDisable (GL_LIGHT0 + i);
				glLightfv (GL_LIGHT0+i, GL_DIFFUSE, _hoops_HGSAI);
				glLightfv (GL_LIGHT0+i, GL_SPECULAR, _hoops_PHRGC);
				glEnable (GL_LIGHT0 + i);
				light = light->next;
			}
			glEnable (GL_LIGHTING);
			_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, 0);
		} break;

		case _hoops_GGGRC:{
			_hoops_AS const *light = rc->light[rc->pass];
			_hoops_HRPA tmp, total, _hoops_RHSPR;
			float _hoops_GGHCR, _hoops_AGHCR;
			float _hoops_PARRC[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };

			ALLOC_ARRAY(params, 2*point_count, _hoops_RSSH);
			rc->params[rc->pass] = params;
			rc->_hoops_RSIC[rc->pass] = 2*point_count;
			rc->flags[rc->pass] |= _hoops_AGRRC;

			HI_Copy_Matrix(&_hoops_IHCR->_hoops_IPH->data, &total);

			total.elements[3][0] -= (light->position.x+light->direction.x);
			total.elements[3][1] -= (light->position.y+light->direction.y);
			total.elements[3][2] -= (light->position.z+light->direction.z);
			total._hoops_RAGR = (_hoops_PRICR|_hoops_RRICR);
			total._hoops_CPH = _hoops_IHCR->_hoops_IPH->data._hoops_CPH;

			tmp._hoops_RAGR = 0;

			if (light->direction.x == 0.0 && light->direction.y == 0.0) {
				if (light->direction.z < 0.0) {
					HI_Compute_Rotation_Matrix (0.0, 180.0, 0.0, &tmp.elements[0][0]);
					tmp._hoops_RAGR |= _hoops_GRICR;
					tmp._hoops_CPH = 1;
					HI_Copy_Matrix (&total, &_hoops_RHSPR);
					HI_Multiply_Matrices (&_hoops_RHSPR, &tmp, &total);
				}
			}
			else {
				float _hoops_RAHCR = (float)HI_ACos(light->direction.z);
				HI_Compute_Offaxis_Rotation (-light->direction.y, light->direction.x, 0.0f, -_hoops_RAHCR, &tmp.elements[0][0]);
				tmp._hoops_RAGR |= (_hoops_GRICR|_hoops_RRICR);
				tmp._hoops_CPH = 1;
				HI_Copy_Matrix (&total, &_hoops_RHSPR);
				HI_Multiply_Matrices (&_hoops_RHSPR, &tmp, &total);
			}


			HI_SinCos(light->_hoops_HCSR, &_hoops_GGHCR, &_hoops_AGHCR);
			_hoops_AIGA(_hoops_PARRC, 16, float, &tmp.elements[0][0]);
			tmp.elements[0][0] = tmp.elements[1][1] = (_hoops_AGHCR/_hoops_GGHCR); /* 1/_hoops_HARRC _hoops_PPR _hoops_HGPC _hoops_GGCH*/
			tmp.elements[2][2] = tmp.elements[2][3] = 1.0f;
			tmp._hoops_RAGR |= (_hoops_CHCP|_hoops_HRICR);
			tmp._hoops_CPH = 0;

			HI_Copy_Matrix (&total, &_hoops_RHSPR);
			HI_Multiply_Matrices (&_hoops_RHSPR, &tmp, &total);

			total.elements[0][0] *= 0.5f;
			total.elements[1][0] *= 0.5f;
			total.elements[2][0] *= 0.5f;
			total.elements[3][0] *= 0.5f;
			total.elements[0][1] *= 0.5f;
			total.elements[1][1] *= 0.5f;
			total.elements[2][1] *= 0.5f;
			total.elements[3][1] *= 0.5f;

			for (i=0; i<point_count; i++) {
				float w = _hoops_PHCP (total.elements, points[i]);

				if (w > _hoops_IHCR->_hoops_CHCR) {
					params[2*i+0] = 0.5f + _hoops_HPRA (total.elements, points[i]) / w;
					params[2*i+1] = 0.5f + _hoops_IPRA (total.elements, points[i]) / w;
				}
				else {
					Vector _hoops_GIHI;

					_hoops_GIHI.x = 0.5f + _hoops_HPRA (_hoops_RHSPR.elements, points[i]) / w;
					_hoops_GIHI.y = 0.5f + _hoops_IPRA (_hoops_RHSPR.elements, points[i]) / w;
					_hoops_GIHI.z = 0.0f;

					HI_Normalize(&_hoops_GIHI);

					params[2*i+0] = 100 * _hoops_GIHI.x;
					params[2*i+1] = 100 * _hoops_GIHI.y;
				}
			}

			ENSURE_TEXTURE_ENV_MODE(_hoops_CSRGR, GL_MODULATE,_hoops_AHCGR);
			ENSURE_BLEND_FUNC(_hoops_CSRGR, GL_ONE, GL_ONE);
			_hoops_ASGRC(_hoops_CSRGR);
			_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, 0);
			_hoops_SCIGC (_hoops_CSRGR);
			_hoops_HCRGC(_hoops_CSRGR, light);
			ENSURE_TEXTURE_PERSPECTIVE_CORRECTION_ON(_hoops_CSRGR,_hoops_AHCGR);
			if (ANYBIT(
				nr->_hoops_IRR->_hoops_APGH->matrix._hoops_RAGR,
				_hoops_CICH)) {
				glMatrixMode (GL_TEXTURE);
				glPushMatrix();
				glLoadIdentity();
				glMatrixMode (GL_MODELVIEW);
			}
		} break;

		default:
			break;
	}

	/* _hoops_PH _hoops_SIA _hoops_SHR _hoops_SSCP _hoops_IRS _hoops_SPI _hoops_HH _hoops_HISS _hoops_IS _hoops_SCH, _hoops_HIS _hoops_PHHR _hoops_ISSC _hoops_IS _hoops_RH _hoops_HSPP */
	if (rc->_hoops_GCI[rc->pass] == _hoops_ISSGC && rc->_hoops_IARRC.length) {
		rc->pass++;
		_hoops_AHCGR = 1;
 		goto _hoops_HIGRC;
	}

	if (rc->_hoops_GCI[rc->pass] == _hoops_PCSGC) 	{
		if (rc->_hoops_SIGRC[rc->pass] == 1)
			rc->pass--;
		else {
			if (!_hoops_AHCGR) {
				_hoops_AHCGR = 1;
				goto _hoops_HIGRC;
			}
		}
	}

	if (BIT(rc->flags[rc->pass], _hoops_CARRC) || BIT(rc->flags[rc->pass], _hoops_AGCGC)) {
	    /* _hoops_RGSP _hoops_ISSC _hoops_RSSI _hoops_GGR _hoops_RIPS _hoops_RIH _hoops_PPR _hoops_RIPS _hoops_RSSI _hoops_GGR _hoops_ISSC _hoops_RIH */
	    unsigned int _hoops_SARRC;

		if (!BIT (_hoops_IHCR->matrix->data.flags, _hoops_HASA))
			HI_Validate_Matrix_NEG3X3((_hoops_HRPA alter *)&_hoops_IHCR->matrix->data);

		bool _hoops_IASA = BIT (_hoops_IHCR->matrix->data._hoops_RAGR, _hoops_CASA);

	    if (_hoops_IASA) {
			if (BIT (_hoops_IHCR->heuristics, _hoops_SASA))
				_hoops_SARRC = GL_CW;
			else
				_hoops_SARRC = GL_CCW;
	    }
	    else {
			if (BIT (_hoops_IHCR->heuristics, _hoops_SASA))
				_hoops_SARRC = GL_CCW;
			else
				_hoops_SARRC = GL_CW;
	    }
	    _hoops_RHSA(_hoops_CSRGR,GL_BACK);
	    if (BIT(rc->flags[rc->pass], _hoops_CARRC))
		/* _hoops_SAHR _hoops_RGSP _hoops_ISSC _hoops_RSSI, _hoops_APIR _hoops_HRGR _hoops_AIAH _hoops_ARP _hoops_HPP _hoops_PGSA _hoops_AGRHA */
			ENSURE_FRONT_FACE(_hoops_CSRGR, _hoops_SARRC);

	    if (BIT(rc->flags[rc->pass], _hoops_AGCGC))
		    _hoops_RHSA(_hoops_CSRGR,GL_FRONT);
	}

#ifdef _hoops_GCGGC
	}
	else
	{
		if (_hoops_CPGRC && !_hoops_CSRGR->_hoops_GSGRR)
			_hoops_CPGRC->_hoops_CHCRR(_hoops_IPGRC, dc->_hoops_RIGC->thread_id);
	}
#endif

	return true;

} /* _hoops_RSGR _hoops_API _hoops_GGRGR _hoops_RIH */


local bool _hoops_GPRRC (
	Net_Rendition const & nr,
	Integer32 _hoops_RPRRC,
	_hoops_SSIC _hoops_APRRC,
	OGL_Render_Control *rc)
{
	Display_Context const *dc = nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	int i;

	if (BIT(dc->flags, _hoops_CHSI) ||
		_hoops_CSRGR->_hoops_CSC._hoops_IPAGC)
		return false;

	_hoops_CSRGR->_hoops_CSC._hoops_HRIGC = false;

#ifdef _hoops_GCGGC
	if(!_hoops_CSRGR->_hoops_GSGRR)
	{
		_hoops_RCGGC* _hoops_CPGRC = _hoops_ACGGC(dc->_hoops_RIGC->thread_id);
		if (_hoops_CPGRC)
		{
			_hoops_HPGRC _hoops_IPGRC;
			_hoops_IPGRC._hoops_AHGRC((void*)&nr, NULL, false);
			_hoops_CPGRC->_hoops_PPRRC(_hoops_IPGRC, dc->_hoops_RIGC->thread_id);
			_hoops_CSRGR->_hoops_CSC._hoops_GSCH[0] = _hoops_RSARR;
			_hoops_PIIGC(_hoops_CSRGR, nr);

			if (_hoops_CSRGR->_hoops_SPGRC)
			{
				_hoops_HPRRC(_hoops_CSRGR,1,false);
				_hoops_IPRRC(_hoops_CSRGR,0);
			}
		}
	}
#endif

	UNREFERENCED(_hoops_RPRRC);
	UNREFERENCED(_hoops_APRRC);

	if (ANYBIT (rc->flags[rc->pass], _hoops_RGCGC|_hoops_AGCGC)) {
		OGL_SET_HANDEDNESS (_hoops_CSRGR, nr->transform_rendition, 0);
	}

	switch (rc->_hoops_GCI[rc->pass]) {
		case _hoops_RCGRC:
			if (nr->_hoops_IHA->color !=
				nr->_hoops_IHA->_hoops_RGIR &&
				_hoops_CSRGR->_hoops_SARGC == _hoops_RHRGC) {
				/*_hoops_HGPIP _hoops_CPRRC*/
				glDisable (GL_LIGHT0);
				glDisable (GL_LIGHTING);
			}
			break;

		case _hoops_RIGRC: {
			_hoops_AARRC (_hoops_CSRGR,0);
		} break;

		case _hoops_ISSGC:
		case _hoops_CSSGC:
		    ENSURE_BLEND_FUNC(_hoops_CSRGR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			if (_hoops_CSRGR->_hoops_HSAC)
				_hoops_SPRRC(_hoops_CSRGR);
			else
				_hoops_ACCGC(_hoops_CSRGR);

			if (BIT(rc->flags[rc->pass], _hoops_HSGRC)) {
			    _hoops_SRGRC(_hoops_CSRGR, 0);
			}
			_hoops_AARRC (_hoops_CSRGR,0);

			break;

		case _hoops_HCSGC:
			if (BIT(rc->flags[rc->pass], _hoops_GGRRC)) {
			    _hoops_SRGRC(_hoops_CSRGR, 0);
			}
			else {
				if (rc->params[rc->pass])
					FREE_ARRAY(rc->params[rc->pass], rc->_hoops_RSIC[rc->pass], _hoops_RSSH);
			}
			if (rc->pass > 0) {
				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA))
					_hoops_SPRGC(_hoops_CSRGR);
			}
			ENSURE_BLEND_FUNC(_hoops_CSRGR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			if (_hoops_CSRGR->_hoops_HSAC)
				_hoops_SPRRC(_hoops_CSRGR);
			else
				_hoops_ACCGC(_hoops_CSRGR);

			break;

		case _hoops_SSSGC: {
			_hoops_PC const &		_hoops_HC = nr->_hoops_IHA->_hoops_AGP;
			_hoops_AS const *		light;
			GLfloat _hoops_HGSAI[4] = {0, 0, 0, 0};
			GLfloat _hoops_PHRGC[4];

			if (_hoops_CSRGR->_hoops_CRPGC)
				glLightModelf (GL_LIGHT_MODEL_COLOR_CONTROL_EXT,GL_SEPARATE_SPECULAR_COLOR_EXT);
			ENSURE_BLEND_FUNC(_hoops_CSRGR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			if (_hoops_CSRGR->_hoops_HSAC)
				_hoops_SPRRC(_hoops_CSRGR);
			else
				_hoops_ACCGC(_hoops_CSRGR);

			glDisable (GL_LIGHTING);
			_hoops_PHRGC[0] = _hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.red;
			_hoops_PHRGC[1] = _hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.green;
			_hoops_PHRGC[2] = _hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.blue;
			_hoops_PHRGC[3] = 1.0;
			glLightModelfv (GL_LIGHT_MODEL_AMBIENT, _hoops_PHRGC);
			if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA))
				_hoops_SPRGC(_hoops_CSRGR);
			light = _hoops_HC->_hoops_CGR;
			for (i = 0; i < _hoops_CSRGR->_hoops_CHRGC; i++) {
				_hoops_PHRGC[0] = light->color.red;
				_hoops_PHRGC[1] = light->color.green;
				_hoops_PHRGC[2] = light->color.blue;
				_hoops_PHRGC[3] = 1.0;
				glDisable (GL_LIGHT0 + i);
				glLightfv (GL_LIGHT0+i, GL_DIFFUSE, _hoops_PHRGC);
				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA))
					glLightfv (GL_LIGHT0+i, GL_SPECULAR, _hoops_HGSAI);
				else
					glLightfv (GL_LIGHT0+i, GL_SPECULAR, _hoops_PHRGC);
				glEnable (GL_LIGHT0 + i);
				light = light->next;
			}
			glEnable (GL_LIGHTING);
		} break;

		case _hoops_GGGRC:{
			FREE_ARRAY(rc->params[rc->pass], rc->_hoops_RSIC[rc->pass], _hoops_RSSH);
			ENSURE_BLEND_FUNC(_hoops_CSRGR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			if (_hoops_CSRGR->_hoops_HSAC)
				_hoops_SPRRC (_hoops_CSRGR);
			else
				_hoops_ACCGC (_hoops_CSRGR);
			_hoops_GHRGC (_hoops_CSRGR);
			if (ANYBIT(
				nr->_hoops_IRR->_hoops_APGH->matrix._hoops_RAGR,
				_hoops_CICH)) {
				glMatrixMode (GL_TEXTURE);
				glPopMatrix();
				glMatrixMode (GL_MODELVIEW);
			}
		} break;
	}


	if (BIT(rc->flags[rc->pass], _hoops_CIGRC)) {

		if (_hoops_CSRGR->_hoops_CRPGC)
			glLightModelf (GL_LIGHT_MODEL_COLOR_CONTROL_EXT,GL_SEPARATE_SPECULAR_COLOR_EXT);

		if (rc->_hoops_GCI[rc->pass] != _hoops_PCSGC)
			rc->pass++;
		if (rc->_hoops_IARRC.length) {
			FREE_ARRAY(rc->_hoops_IARRC._hoops_GHRRC, rc->_hoops_IARRC.length, Vector);
			FREE_ARRAY(rc->_hoops_IARRC._hoops_RHRRC, rc->_hoops_IARRC.length, Vector);
			FREE_ARRAY(rc->_hoops_IARRC._hoops_AHRRC, rc->_hoops_IARRC.length, Vector);
			FREE_ARRAY(rc->_hoops_IARRC._hoops_PHRRC, rc->_hoops_IARRC.length, Point);
		}

		_hoops_HHRRC(_hoops_CSRGR,1);

		glMatrixMode(GL_TEXTURE);
  		glDisable(GL_TEXTURE_CUBE_MAP_ARB);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    	_hoops_AARRC (_hoops_CSRGR, 1);

		_hoops_HHRRC(_hoops_CSRGR,0);
 		glMatrixMode(GL_TEXTURE);
  		glDisable(GL_TEXTURE_CUBE_MAP_ARB);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    	_hoops_AARRC (_hoops_CSRGR, 0);
    	glMatrixMode (GL_MODELVIEW);
		_hoops_IHRRC(_hoops_CSRGR,0);
	}
	rc->pass++;
	if (rc->pass < rc->_hoops_CHRRC)
		return true;
	else
		return false;

} /* _hoops_RSGR _hoops_API _hoops_SHRRC */


local bool _hoops_GIRRC(
	Net_Rendition const & nr,
	_hoops_AS const *light,
	Tristrip *ts,
	Bounding &	_hoops_RIRRC)
{

	if (BIT(_hoops_RIRRC->flags, Bounding_EMPTY)) {

		if (BIT(_hoops_RIRRC->flags, _hoops_IAPGP))
			return false;

		if (ts == null || 
			ts->bounding._hoops_HICAR() ||
			ANYBIT (ts->bounding->flags, Bounding_EMPTY|_hoops_HGCIR|_hoops_IGCIR|Bounding_TRANSFORM_DEPENDENT) ||
			ts->_hoops_GSCP == null ||
			!(ts->_hoops_GSCP->type == _hoops_SCIP || ts->_hoops_GSCP->type == _hoops_GSIP)) {
			/* _hoops_SGH _hoops_AIRRC _hoops_GAR _hoops_IRS _hoops_GRH _hoops_PIRA _hoops_IS _hoops_IRHC _hoops_SGS _hoops_SSSC _hoops_CHR _hoops_HAR _hoops_RPHR _hoops_IH
			 * _hoops_ARPRR _hoops_IS _hoops_PIRRC _hoops_RH _hoops_RAGA _hoops_CPHAR.  _hoops_HIRRC, _hoops_IH _hoops_RCHAR _hoops_PCGRC,
			 * _hoops_SR _hoops_PAH _hoops_IIRRC _hoops_RSIH _hoops_SIHH _hoops_PRGI _hoops_IRCC */
			_hoops_RIRRC->flags |= _hoops_IAPGP;
			return false;
		}

		_hoops_HRPA const * _hoops_CIRRC = &nr->transform_rendition->_hoops_IPH->data;

		if (!ANYBIT (_hoops_CIRRC->_hoops_RAGR, _hoops_CICH)) {
			_hoops_RIRRC = ts->bounding;
		}
		else {

			Point pts[8];
			ts->bounding->cuboid._hoops_GPSC(&pts[0]);

			_hoops_RPRA const * elements = _hoops_CIRRC->elements;

			Point _hoops_SIRRC[8];

			for (int i = 0; i < 8; i++) {
				_hoops_SIRRC[i].x = _hoops_HPRA (elements, pts[i]);
				_hoops_SIRRC[i].y = _hoops_IPRA (elements, pts[i]);
				_hoops_SIRRC[i].z = _hoops_CPRA (elements, pts[i]);
			}

			_hoops_RIRRC = Bounding::Create(8, _hoops_SIRRC);
		}
	}

	Vector	_hoops_GCRRC = _hoops_RIRRC->sphere.center - light->position;
	float	_hoops_RCRRC = _hoops_GCRRC.length();

	/* _hoops_HRGR _hoops_AAHIA _hoops_RPHIA _hoops_HRGR _hoops_ASSA _hoops_IASC _hoops_CHHRR */
	if (_hoops_RCRRC < _hoops_RIRRC->sphere.radius)
		return false; 

	/* _hoops_RRR _hoops_HAGA _hoops_HRGR _hoops_SCGA, _hoops_HIH _hoops_SIIGC _hoops_HRGR _hoops_HAR */
	float	_hoops_SSRP =  _hoops_GCRRC._hoops_SSRP(light->direction) / _hoops_RCRRC;

	float	_hoops_ACRRC;
	if (_hoops_SSRP >= 1.0f)
		_hoops_ACRRC = 0;
	else if (_hoops_SSRP <= -1.0f)
		_hoops_ACRRC = 180;
	else
		_hoops_ACRRC = HI_ACos(_hoops_SSRP);

	float	_hoops_PCRRC = 90 - HI_ACos(_hoops_RIRRC->sphere.radius / _hoops_RCRRC);
	if (_hoops_PCRRC + light->_hoops_HCSR > _hoops_ACRRC)
		return false;
	else
		return true;
}


#ifndef _hoops_SIGGC
local void _hoops_HCRRC(Point *_hoops_ISPI,
                                Point *_hoops_CSPI,
                                Point *_hoops_SSPI,
                                float _hoops_ICRRC, float _hoops_CCRRC,
                                float _hoops_SCRRC, float _hoops_GSRRC,
                                float _hoops_RSRRC, float _hoops_ASRRC,
                                Vector *_hoops_AHRRC,
                                Vector *_hoops_GHRRC,
                                Vector *_hoops_RHRRC)
{
    /* _hoops_GISA _hoops_ISHA _hoops_PSPAR _hoops_HII _hoops_GPHA 1 _hoops_IS _hoops_PSPAR 2 _hoops_PPR 3.*/

	Point _hoops_PSRRC;
	Point _hoops_HSRRC;
	float _hoops_ISRRC;
	float _hoops_CSRRC;
	float _hoops_SSRRC;
	float _hoops_GGARC;
	float _hoops_RGARC;

	_hoops_PSRRC.x = _hoops_CSPI->x - _hoops_ISPI->x; 	_hoops_PSRRC.y = _hoops_CSPI->y - _hoops_ISPI->y; 	_hoops_PSRRC.z = _hoops_CSPI->z - _hoops_ISPI->z;
	_hoops_HSRRC.x = _hoops_SSPI->x - _hoops_ISPI->x; 	_hoops_HSRRC.y = _hoops_SSPI->y - _hoops_ISPI->y; 	_hoops_HSRRC.z = _hoops_SSPI->z - _hoops_ISPI->z;

    /* _hoops_GISA _hoops_ISHA _hoops_PSPAR _hoops_HII _hoops_RH _hoops_HH _hoops_PCRR _hoops_IIGR _hoops_GPHA 1 _hoops_IS _hoops_AAGA 2. */
     _hoops_ISRRC = _hoops_SCRRC - _hoops_ICRRC;
     _hoops_CSRRC = _hoops_GSRRC - _hoops_CCRRC;

    /* _hoops_GISA _hoops_ISHA _hoops_PSPAR _hoops_HII _hoops_RH _hoops_HH _hoops_PCRR _hoops_IIGR _hoops_GPHA 1 _hoops_IS _hoops_AAGA 3. */
    _hoops_SSRRC = _hoops_RSRRC - _hoops_ICRRC;
    _hoops_GGARC = _hoops_ASRRC - _hoops_CCRRC;

    _hoops_RGARC = _hoops_ISRRC * _hoops_GGARC -
                         _hoops_SSRRC * _hoops_CSRRC;

    if (_hoops_RGARC < 0.0001f && _hoops_RGARC > -0.0001f) {
        /* _hoops_PS'_hoops_ASAR _hoops_HAH _hoops_GGGR _hoops_IS _hoops_AHHR _hoops_PPR _hoops_SR'_hoops_ASAR _hoops_HPGR _hoops_AGARC _hoops_IIGR _hoops_IRS _hoops_GHCH-_hoops_HPP-_hoops_AHHR! */
        /* _hoops_RAP _hoops_RH _hoops_IACA _hoops_RSGA _hoops_IS _hoops_RH _hoops_SRGH _hoops_RSGA _hoops_PPR _hoops_AA _hoops_ISAP. */
		_hoops_AHRRC->x = 1.0f; _hoops_AHRRC->y = 0.0f; _hoops_AHRRC->z = 0.0f;
		_hoops_GHRRC->x = 0.0f; _hoops_GHRRC->y = 1.0f; _hoops_GHRRC->z = 0.0f;
		_hoops_RHRRC->x = 0.0f; _hoops_RHRRC->y = 0.0f; _hoops_RHRRC->z = 1.0f;
	}
    else {
        /* _hoops_PSIH _hoops_PPR _hoops_IHAH _hoops_RH _hoops_IACGC _hoops_PIRA */
        float _hoops_PGARC = 1.0f / _hoops_RGARC;

        Vector T;
        Vector _hoops_HPIHI;
        Vector _hoops_HCRHH;
		float _hoops_HGARC;
		Vector _hoops_IGARC, _hoops_CGARC, _hoops_SGARC;

		T.x = (_hoops_GGARC * _hoops_PSRRC.x - _hoops_CSRRC * _hoops_HSRRC.x) * _hoops_PGARC;
		T.y = (_hoops_GGARC * _hoops_PSRRC.y - _hoops_CSRRC * _hoops_HSRRC.y) * _hoops_PGARC;
		T.z = (_hoops_GGARC * _hoops_PSRRC.z - _hoops_CSRRC * _hoops_HSRRC.z) * _hoops_PGARC;

        _hoops_HPIHI.x = (-_hoops_SSRRC * _hoops_PSRRC.x + _hoops_ISRRC * _hoops_HSRRC.x) * _hoops_PGARC;
		_hoops_HPIHI.y = (-_hoops_SSRRC * _hoops_PSRRC.y + _hoops_ISRRC * _hoops_HSRRC.y) * _hoops_PGARC;
		_hoops_HPIHI.z = (-_hoops_SSRRC * _hoops_PSRRC.z + _hoops_ISRRC * _hoops_HSRRC.z) * _hoops_PGARC;

		HI_Compute_Cross_Product(&T,&_hoops_HPIHI,&_hoops_HCRHH);


        /* _hoops_PSIH _hoops_PPR _hoops_IHAH _hoops_RH _hoops_IACGC _hoops_PIRA */
        _hoops_HGARC = ((T.x * _hoops_HPIHI.y * _hoops_HCRHH.z - T.z * _hoops_HPIHI.y * _hoops_HCRHH.x) +
					(_hoops_HPIHI.x * _hoops_HCRHH.y * T.z - _hoops_HPIHI.z * _hoops_HCRHH.y * T.x) +
					(_hoops_HCRHH.x * T.y * _hoops_HPIHI.z - _hoops_HCRHH.z * T.y * _hoops_HPIHI.x));

		if (_hoops_HGARC != 0.0f)
			_hoops_HGARC /= 1.0f;

        /*
         _hoops_SGPR _hoops_RH _hoops_AH _hoops_SAAAR (_hoops_GRARC), (_hoops_IHAC) _hoops_RRARC, _hoops_PPR _hoops_PGGIR (_hoops_AGAR) _hoops_PSPAR
         _hoops_IS _hoops_CSGA _hoops_RH _hoops_AGICR _hoops_IIGR _hoops_RH _hoops_IACA _hoops_RSGA _hoops_SGS _hoops_SSIA _hoops_HCAAA.
         _hoops_IPCP _hoops_AGICR _hoops_IIGR _hoops_RH _hoops_IACA _hoops_RSGA _hoops_HRGR _hoops_PCPA _hoops_SR _hoops_HHGC _hoops_CR _hoops_SR _hoops_RRP _hoops_SGS
         _hoops_IS _hoops_HIHP _hoops_RH _hoops_RRR'_hoops_GRI _hoops_AAGA _hoops_CRGR _hoops_IACA-_hoops_GC.
        */


		HI_Compute_Cross_Product(&_hoops_HPIHI,&_hoops_HCRHH, &_hoops_IGARC);
        _hoops_AHRRC->x =   _hoops_IGARC.x * _hoops_HGARC;
		HI_Compute_Cross_Product(&_hoops_HCRHH,&T, &_hoops_CGARC);
        _hoops_AHRRC->y = -(_hoops_CGARC.x * _hoops_HGARC);
		HI_Compute_Cross_Product(&T,&_hoops_HPIHI, &_hoops_SGARC);
        _hoops_AHRRC->z =   _hoops_SGARC.x * _hoops_HGARC;
		HI_Normalize(_hoops_AHRRC);

        _hoops_GHRRC->x = -(_hoops_IGARC.y * _hoops_HGARC);
        _hoops_GHRRC->y =   _hoops_CGARC.y * _hoops_HGARC;
        _hoops_GHRRC->z = -(_hoops_SGARC.y * _hoops_HGARC);
		HI_Normalize(_hoops_GHRRC);

        _hoops_RHRRC->x =  _hoops_IGARC.z * _hoops_HGARC;
        _hoops_RHRRC->y = -(_hoops_CGARC.z * _hoops_HGARC);
        _hoops_RHRRC->z =   _hoops_SGARC.z * _hoops_HGARC;
		HI_Normalize(_hoops_RHRRC);

		_hoops_GHRRC->x*=-1.0f;
		_hoops_GHRRC->y*=-1.0f;
		_hoops_GHRRC->z*=-1.0f;
	/*
		_hoops_RPP (_hoops_ARARC->_hoops_SISR*(_hoops_GGRA)[0] +
				_hoops_ARARC->_hoops_HAPC*(_hoops_GGRA)[1] +
				_hoops_ARARC->_hoops_SSH*(_hoops_GGRA)[2] +
				(_hoops_GGRA)[3] * (-((_hoops_IIHHR)->_hoops_SISR * _hoops_ARARC->_hoops_SISR +
				  (_hoops_IIHHR)->_hoops_HAPC * (_hoops_ARARC)->_hoops_HAPC +
				  (_hoops_IIHHR)->_hoops_SSH * (_hoops_ARARC)->_hoops_SSH)) > 0.0f) {

			_hoops_ARARC->_hoops_SISR = - _hoops_ARARC->_hoops_SISR;
			_hoops_ARARC->_hoops_HAPC = - _hoops_ARARC->_hoops_HAPC;
			_hoops_ARARC->_hoops_SSH = - _hoops_ARARC->_hoops_SSH;
		}
		*/
    }
}
#endif


#ifndef _hoops_SIGGC
local void _hoops_PRARC(Vector* _hoops_HRARC , Vector *_hoops_IRARC)
{

    _hoops_IRARC->x = ((*_hoops_HRARC).x * 0.5f) + 0.5f;
    _hoops_IRARC->y = ((*_hoops_HRARC).y * 0.5f) + 0.5f;
    _hoops_IRARC->z = ((*_hoops_HRARC).z * 0.5f) + 0.5f;
}
#endif

#ifndef _hoops_SIGGC
local void _hoops_CRARC(Net_Rendition const & nr, Tristrip const * ts, Point *_hoops_SRARC,
								   Vector *_hoops_AHRRC, Vector *_hoops_GHRRC, Vector *_hoops_RHRRC)
{

	int i;
 	_hoops_AS const *_hoops_CGR = nr->_hoops_IHA->_hoops_AGP->_hoops_CGR;
	Vector _hoops_GAARC, _hoops_RAARC, _hoops_AAARC;

	_hoops_GAARC.x = _hoops_CGR->direction.x;
	_hoops_GAARC.y = _hoops_CGR->direction.y;
	_hoops_GAARC.z = _hoops_CGR->direction.z;


	for (i=0; i<ts->point_count; i++) {
		float _hoops_PAARC[16];
#if 0
		_hoops_GAARC.x = nr->transform_rendition->_hoops_SPH->position.x - ts->points[i].x;
		_hoops_GAARC.y = nr->transform_rendition->_hoops_SPH->position.y - ts->points[i].y;
		_hoops_GAARC.z = nr->transform_rendition->_hoops_SPH->position.z - ts->points[i].z;
#endif

		HI_Normalize(&_hoops_GAARC);


		_hoops_PAARC[0] = _hoops_AHRRC[i].x;
		_hoops_PAARC[4] = _hoops_GHRRC[i].x;
		_hoops_PAARC[8] = _hoops_RHRRC[i].x;
		_hoops_PAARC[12] = 0;
		_hoops_PAARC[1] = _hoops_AHRRC[i].y;
		_hoops_PAARC[5] = _hoops_GHRRC[i].y;
		_hoops_PAARC[9] = _hoops_RHRRC[i].y;
		_hoops_PAARC[13] = 0;
		_hoops_PAARC[2] = _hoops_AHRRC[i].z;
		_hoops_PAARC[6] = _hoops_GHRRC[i].z;
		_hoops_PAARC[10] = _hoops_RHRRC[i].z;
		_hoops_PAARC[14] = 0;
		_hoops_PAARC[3] = 0;
		_hoops_PAARC[7] = 0;
		_hoops_PAARC[11] = 0;
		_hoops_PAARC[15] = 1.0f;


		HI_Compute_Transformed_Points(1, (Point*)&_hoops_GAARC, _hoops_PAARC, (Point*)&_hoops_RAARC);


		_hoops_PRARC(&_hoops_RAARC, &_hoops_AAARC);

		_hoops_SRARC[i].x = _hoops_AAARC.x;
		_hoops_SRARC[i].y = _hoops_AAARC.y;
		_hoops_SRARC[i].z = _hoops_AAARC.z;

	}

}
#endif

#ifndef _hoops_SIGGC
local void _hoops_HAARC(Tristrip const * ts, Vector *_hoops_AHRRC, Vector *_hoops_GHRRC, Vector *_hoops_RHRRC, int param_width)
{
	int i;

	for (i=0;i<ts->point_count;i++)
	{
		_hoops_AHRRC[i].x = 0; _hoops_AHRRC[i].y = 0; _hoops_AHRRC[i].z = 0;
		_hoops_GHRRC[i].x = 0; _hoops_GHRRC[i].y = 0; _hoops_GHRRC[i].z = 0;
		_hoops_RHRRC[i].x = 0; _hoops_RHRRC[i].y = 0; _hoops_RHRRC[i].z = 0;
	}

	if (ts->point_count == 3)
	{
		_hoops_HCRRC(&ts->points[0], &ts->points[1], &ts->points[2],
			ts->_hoops_GSSH->_hoops_CCHA[0*param_width],ts->_hoops_GSSH->_hoops_CCHA[0*param_width+1],
			ts->_hoops_GSSH->_hoops_CCHA[1*param_width],ts->_hoops_GSSH->_hoops_CCHA[1*param_width+1],
			ts->_hoops_GSSH->_hoops_CCHA[2*param_width],ts->_hoops_GSSH->_hoops_CCHA[2*param_width+1],
			&_hoops_AHRRC[0], &_hoops_GHRRC[0], &_hoops_RHRRC[0]);
		_hoops_HCRRC(&ts->points[1], &ts->points[2], &ts->points[0],
			ts->_hoops_GSSH->_hoops_CCHA[1*param_width],ts->_hoops_GSSH->_hoops_CCHA[1*param_width+1],
			ts->_hoops_GSSH->_hoops_CCHA[2*param_width],ts->_hoops_GSSH->_hoops_CCHA[2*param_width+1],
			ts->_hoops_GSSH->_hoops_CCHA[0*param_width],ts->_hoops_GSSH->_hoops_CCHA[0*param_width+1],
			&_hoops_AHRRC[1], &_hoops_GHRRC[1], &_hoops_RHRRC[1]);
		_hoops_HCRRC(&ts->points[2], &ts->points[0], &ts->points[1],
			ts->_hoops_GSSH->_hoops_CCHA[2*param_width],ts->_hoops_GSSH->_hoops_CCHA[2*param_width+1],
			ts->_hoops_GSSH->_hoops_CCHA[0*param_width],ts->_hoops_GSSH->_hoops_CCHA[0*param_width+1],
			ts->_hoops_GSSH->_hoops_CCHA[1*param_width],ts->_hoops_GSSH->_hoops_CCHA[1*param_width+1],
			&_hoops_AHRRC[2], &_hoops_GHRRC[2], &_hoops_RHRRC[2]);
	}
	else if (ts && ts->_hoops_GSCP &&
			ts->_hoops_GSCP->type == _hoops_SCIP &&
			((Shell *)ts->_hoops_GSCP)->face_list)
	{
		int _hoops_IAARC;
		int *_hoops_PSRGA;
		int j=0;
		i = 0;
		_hoops_IAARC = ((Shell *)ts->_hoops_GSCP)->face_list_length;
		_hoops_PSRGA = ((Shell *)ts->_hoops_GSCP)->face_list;
 		while (1)
		{
			int _hoops_CAARC = _hoops_PSRGA[i++];
			for (j=0;j<_hoops_CAARC;j++)
			{
				int p1,p2 =0,_hoops_IAPH = 0;
				Vector t,b,n;
				p1 = _hoops_PSRGA[i];
				if (j<_hoops_CAARC-2)
				{
					p2 = _hoops_PSRGA[i+1];
					_hoops_IAPH = _hoops_PSRGA[i+2];
				}
				if (j==_hoops_CAARC-2)
				{
					p2 = _hoops_PSRGA[i+1];
					_hoops_IAPH = _hoops_PSRGA[i-j];
				}
				else if (j==_hoops_CAARC-1)
				{
					p2 = _hoops_PSRGA[i-j];
					_hoops_IAPH = _hoops_PSRGA[i-j+1];

				}
				_hoops_HCRRC(&ts->points[p1], &ts->points[p2], &ts->points[_hoops_IAPH],
					ts->_hoops_GSSH->_hoops_CCHA[p1*param_width],ts->_hoops_GSSH->_hoops_CCHA[p1*param_width+1],
					ts->_hoops_GSSH->_hoops_CCHA[p2*param_width],ts->_hoops_GSSH->_hoops_CCHA[p2*param_width+1],
					ts->_hoops_GSSH->_hoops_CCHA[_hoops_IAPH*param_width],ts->_hoops_GSSH->_hoops_CCHA[_hoops_IAPH*param_width+1],
					&t, &b, &n);
				_hoops_AHRRC[p1].x += t.x; _hoops_AHRRC[p1].y += t.y; _hoops_AHRRC[p1].z += t.z;
				_hoops_GHRRC[p1].x += b.x; _hoops_GHRRC[p1].y += b.y; _hoops_GHRRC[p1].z += b.z;
				_hoops_RHRRC[p1].x += n.x; _hoops_RHRRC[p1].y += n.y; _hoops_RHRRC[p1].z += n.z;
				i++;
			}
			if (i>=_hoops_IAARC)
				break;
		}
	}
	else
	{
		int j, _hoops_SAHAR;
		int _hoops_PHHA;
		int *lengths;
		int *_hoops_AIHA;
		int p1, p2, _hoops_IAPH;
		Vector t,b,n;
		_hoops_PHHA = ts->_hoops_PHHA;
		lengths = ts->lengths;
		_hoops_AIHA = ts->_hoops_AIHA;

		j=0;
		for (i=0; i<_hoops_PHHA; i++) {
			if (lengths[i] > 0) {
				/* _hoops_SCPH _hoops_CGGR */
				_hoops_SAHAR = j + lengths[i];
				p1 = _hoops_AIHA[j];
				j++;
				p2 = _hoops_AIHA[j];
				j++;
				while (1) {
					_hoops_IAPH = _hoops_AIHA[j];
					_hoops_HCRRC(&ts->points[p1], &ts->points[p2], &ts->points[_hoops_IAPH],
						ts->_hoops_GSSH->_hoops_CCHA[p1*param_width],ts->_hoops_GSSH->_hoops_CCHA[p1*param_width+1],
						ts->_hoops_GSSH->_hoops_CCHA[p2*param_width],ts->_hoops_GSSH->_hoops_CCHA[p2*param_width+1],
						ts->_hoops_GSSH->_hoops_CCHA[_hoops_IAPH*param_width],ts->_hoops_GSSH->_hoops_CCHA[_hoops_IAPH*param_width+1],
						&t, &b, &n);
					_hoops_AHRRC[p1].x += t.x; _hoops_AHRRC[p1].y += t.y; _hoops_AHRRC[p1].z += t.z;
					_hoops_GHRRC[p1].x += b.x; _hoops_GHRRC[p1].y += b.y; _hoops_GHRRC[p1].z += b.z;
					_hoops_RHRRC[p1].x += n.x; _hoops_RHRRC[p1].y += n.y; _hoops_RHRRC[p1].z += n.z;
					_hoops_AHRRC[p2].x += t.x; _hoops_AHRRC[p2].y += t.y; _hoops_AHRRC[p2].z += t.z;
					_hoops_GHRRC[p2].x += b.x; _hoops_GHRRC[p2].y += b.y; _hoops_GHRRC[p2].z += b.z;
					_hoops_RHRRC[p2].x += n.x; _hoops_RHRRC[p2].y += n.y; _hoops_RHRRC[p2].z += n.z;
					_hoops_AHRRC[_hoops_IAPH].x += t.x; _hoops_AHRRC[_hoops_IAPH].y += t.y; _hoops_AHRRC[_hoops_IAPH].z += t.z;
					_hoops_GHRRC[_hoops_IAPH].x += b.x; _hoops_GHRRC[_hoops_IAPH].y += b.y; _hoops_GHRRC[_hoops_IAPH].z += b.z;
					_hoops_RHRRC[_hoops_IAPH].x += n.x; _hoops_RHRRC[_hoops_IAPH].y += n.y; _hoops_RHRRC[_hoops_IAPH].z += n.z;
					p1 = p2;
					p2 = _hoops_IAPH;

					j++;
					if (j==_hoops_SAHAR) break;

					_hoops_IAPH = _hoops_AIHA[j];
					_hoops_HCRRC(&ts->points[_hoops_IAPH], &ts->points[p2], &ts->points[p1],
						ts->_hoops_GSSH->_hoops_CCHA[_hoops_IAPH*param_width],ts->_hoops_GSSH->_hoops_CCHA[_hoops_IAPH*param_width+1],
						ts->_hoops_GSSH->_hoops_CCHA[p2*param_width],ts->_hoops_GSSH->_hoops_CCHA[p2*param_width+1],
						ts->_hoops_GSSH->_hoops_CCHA[p1*param_width],ts->_hoops_GSSH->_hoops_CCHA[p1*param_width+1],
						&t, &b, &n);
					_hoops_AHRRC[p1].x += t.x; _hoops_AHRRC[p1].y += t.y; _hoops_AHRRC[p1].z += t.z;
					_hoops_GHRRC[p1].x += b.x; _hoops_GHRRC[p1].y += b.y; _hoops_GHRRC[p1].z += b.z;
					_hoops_RHRRC[p1].x += n.x; _hoops_RHRRC[p1].y += n.y; _hoops_RHRRC[p1].z += n.z;
					_hoops_AHRRC[p2].x += t.x; _hoops_AHRRC[p2].y += t.y; _hoops_AHRRC[p2].z += t.z;
					_hoops_GHRRC[p2].x += b.x; _hoops_GHRRC[p2].y += b.y; _hoops_GHRRC[p2].z += b.z;
					_hoops_RHRRC[p2].x += n.x; _hoops_RHRRC[p2].y += n.y; _hoops_RHRRC[p2].z += n.z;
					_hoops_AHRRC[_hoops_IAPH].x += t.x; _hoops_AHRRC[_hoops_IAPH].y += t.y; _hoops_AHRRC[_hoops_IAPH].z += t.z;
					_hoops_GHRRC[_hoops_IAPH].x += b.x; _hoops_GHRRC[_hoops_IAPH].y += b.y; _hoops_GHRRC[_hoops_IAPH].z += b.z;
					_hoops_RHRRC[_hoops_IAPH].x += n.x; _hoops_RHRRC[_hoops_IAPH].y += n.y; _hoops_RHRRC[_hoops_IAPH].z += n.z;


					p1 = p2;
					p2 = _hoops_IAPH;
					j++;
					if (j==_hoops_SAHAR) break;
				}
			}
		}
	}

#if 0
	for (i=0;i<ts->point_count;i++)
	{
		HI_Normalize(&_hoops_AHRRC[i]);
		HI_Normalize(&_hoops_GHRRC[i]);
		HI_Normalize(&_hoops_RHRRC[i]);
	}
#endif
}
#endif


/* _hoops_GII _hoops_CAH _hoops_HCGC _hoops_HS _hoops_IS _hoops_IHPS _hoops_ARPP _hoops_RGR _hoops_API _hoops_HRGR _hoops_PIGS (_hoops_IS _hoops_SRCH _hoops_PGGS _hoops_PAGIR) */
local void _hoops_SAARC (
	Net_Rendition const &		nr,
	OGL_Render_Control *		rc,
	Tristrip const *			ts) {
	OGLData alter *				_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HHA			matr = _hoops_SIGA->_hoops_CHA;
	_hoops_GRGH const &		_hoops_ACHI = nr->_hoops_IRR;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	bool						_hoops_GPARC = false;
	GLuint						id;
 	unsigned int				_hoops_IPHAP;
 	int							_hoops_RPARC = 0;
	bool						_hoops_APARC;
	int							i;
	_hoops_RSSH const *			params;
	Integer32					param_width;
	_hoops_SSIC				flags;
	_hoops_RRCC *		_hoops_GSSH = ts->_hoops_GSSH;

	if (_hoops_GSSH) {
		params = _hoops_GSSH->_hoops_CCHA;
		param_width = _hoops_GSSH->_hoops_GSHA;
		flags = _hoops_GSSH->_hoops_SCAI;
	}
	else {
		params = 0;
		param_width = 0;
		flags = 0;
	}
	

	rc->n = 0;
	rc->_hoops_IARRC.length = 0;
	if (ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA)) {
		if (matr != nr->_hoops_IHA->_hoops_GIA &&
			!BIT (_hoops_IHCR->flags, _hoops_IGSP)) {
			_hoops_RPARC = _hoops_CARRC;
		}
		else if (XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_TWO_SIDED_LIGHTING)) {
			_hoops_RPARC = _hoops_CARRC|_hoops_RGCGC;
		}
	}

_hoops_PPARC:
	_hoops_APARC = false;
	_hoops_IPHAP = rc->n;
#ifndef DISABLE_TEXTURING

	if (matr->_hoops_ARIR &&
		BIT (_hoops_ACHI->_hoops_CSA, _hoops_GSRC))
		_hoops_GPARC=true;

	/* _hoops_HPARC _hoops_AI */
	if (_hoops_SIGA->_hoops_AGP &&
		!_hoops_CSRGR->_hoops_AIRGC &&
		!_hoops_CSRGR->_hoops_RIRGC) {
		_hoops_PC const &		_hoops_HC = _hoops_SIGA->_hoops_AGP;
		_hoops_AS const *		light;
		_hoops_RCR alter *txr = null;
		int _hoops_IPARC;
		Bounding _hoops_RIRRC = Bounding::Create();

		light = _hoops_HC->_hoops_CGR;
		while (light != null) {
 			if (light->_hoops_PRR == _hoops_I &&
				!_hoops_GIRRC(nr, light, (Tristrip *)ts, _hoops_RIRRC)) {
	    			_hoops_APARC = true;

				_hoops_IPARC = (int)((light->_hoops_ACSR/light->_hoops_HCSR) * _hoops_PHSGC);
				if (_hoops_CSRGR->_hoops_HHSGC[_hoops_IPARC] != null) {
					txr = _hoops_CSRGR->_hoops_HHSGC[_hoops_IPARC];
				}
				else {
					txr = HI_Clone_Texture(0);
					txr->_hoops_CGA = _hoops_ASCC;
					txr->image = HI_Create_Spotlight_Image(128, light->_hoops_ACSR/light->_hoops_HCSR);
					_hoops_CSRGR->_hoops_HHSGC[_hoops_IPARC] = txr;
				}
				id = OGL_DEFINE_TEXTURE (_hoops_CSRGR, nr, txr, _hoops_GGGRC,0);

				if (rc->n == 0) {
					rc->id[rc->n] = 0;
					rc->txr[rc->n] = 0;
					rc->_hoops_GCI[rc->n] = _hoops_RCGRC;
					rc->params[rc->n] = null;
					rc->param_width[rc->n] = 0;
					rc->flags[rc->n] = _hoops_RPARC;
					rc->_hoops_AIGRC[rc->n] = matr->_hoops_CSHR;
					rc->_hoops_PIGRC[rc->n] = matr->color[_hoops_HIA];
					rc->n++;
					if (rc->n == OGL_MAX_PASSES)
						goto done;
				}

				if (id != _hoops_RSARR) {
					rc->id[rc->n] = id;
					rc->txr[rc->n] = txr;
					rc->_hoops_GCI[rc->n] = _hoops_GGGRC;
					rc->params[rc->n] = null; /* _hoops_IS _hoops_SHH _hoops_GGSRA _hoops_HPP _hoops_GGRGR _hoops_RIH */
					rc->param_width[rc->n] = 2;
					rc->flags[rc->n] = _hoops_RPARC;
					rc->light[rc->n] = light;
					rc->_hoops_AIGRC[rc->n] = _hoops_GPSR::_hoops_IAHHP;
					rc->_hoops_PIGRC[rc->n] = matr->color[_hoops_HIA];
					rc->n++;
					if (rc->n == OGL_MAX_PASSES)
						goto done;
				}
			}
			light = light->next;
		}
	}

	/* _hoops_HAIR _hoops_GGAR _hoops_AI */
	if (BIT (ts->_hoops_SRHA, _hoops_GGIA)) {
		rc->_hoops_GCI[rc->n] = _hoops_RIGRC;
		rc->params[rc->n] = null; /* _hoops_IS _hoops_SHH _hoops_GGSRA _hoops_HPP _hoops_GGRGR _hoops_RIH */
		rc->param_width[rc->n] = 2;
		rc->_hoops_RSCP[rc->n] = 0;
		rc->flags[rc->n] = _hoops_RPARC;
		rc->n++;
		if (rc->n == OGL_MAX_PASSES)
			goto done;
	}

	/* _hoops_GHSR _hoops_AI */
	if (BIT(ts->_hoops_SRHA,DL_TEXTURE_PREBOUND)) {
		/* _hoops_RH _hoops_CRHH _hoops_PISRA _hoops_IS _hoops_IHHH _hoops_CCA _hoops_SRCIA _hoops_PIAP _hoops_AIAH _hoops_ARP _hoops_HII _hoops_GIAA _hoops_IRS _hoops_CAPGR */
		rc->_hoops_GCI[rc->n] = _hoops_ISSGC;
		rc->params[rc->n] =  params;
		rc->param_width[rc->n] = param_width;
		rc->flags[rc->n] = _hoops_RPARC;
		rc->n++;
		if (rc->n == OGL_MAX_PASSES)
			goto done;
	}
	else if (_hoops_GPARC && matr->_hoops_SCA != null) {
		if (ts->_hoops_GSSH/*_hoops_IAGCI >= 2*/ || BIT (ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
			_hoops_HIR *_hoops_PGC = matr->_hoops_SCA;
			int _hoops_GCI;
			bool _hoops_CPARC = false;

			if (BIT (_hoops_PGC->texture->flags, _hoops_IAPS) || _hoops_PGC->texture->_hoops_CGA == _hoops_SGA) {
				if (BIT (_hoops_PGC->texture->_hoops_SCR, _hoops_PGA) || _hoops_PGC->_hoops_HGA>0)
					_hoops_CPARC = true;
			}

			do {
				if (_hoops_PGC == matr->_hoops_SCA)
					_hoops_GCI = _hoops_ISSGC;
				else
					_hoops_GCI = _hoops_CSSGC;

				if (BIT (_hoops_PGC->texture->_hoops_SCR, _hoops_GSR))
					id = _hoops_RSARR;
				else
					id = OGL_DEFINE_TEXTURE (_hoops_CSRGR, nr, _hoops_PGC->texture, _hoops_GCI, 0);

				if (_hoops_CPARC) {
					if (rc->n == 0) {
					rc->id[rc->n] = 0;
					rc->txr[rc->n] = 0;
					rc->_hoops_GCI[rc->n] = _hoops_RCGRC;
					rc->params[rc->n] = null;
					rc->param_width[rc->n] = 0;
					rc->flags[rc->n] = _hoops_RPARC;
					rc->_hoops_AIGRC[rc->n] = matr->_hoops_CSHR;
					rc->_hoops_PIGRC[rc->n] = matr->color[_hoops_HIA];
					rc->n++;
					}
					if (_hoops_CSRGR->_hoops_GSGRR) {
						//_hoops_HGASI _hoops_IH _hoops_IRS _hoops_ICCGR _hoops_ICCI _hoops_CAGRH _hoops_GRCCP _hoops_GAGS _hoops_RSSI _hoops_GGII _hoops_RRAR
						//_hoops_HII _hoops_SPARC _hoops_RSSI
						for (i = 0 ; i < (int)rc->n ; i++)
							rc->flags[i] |= _hoops_SHGRC;
					}
				}

				if (id != _hoops_RSARR)  {
					rc->id[rc->n] = id;
					rc->txr[rc->n] = (_hoops_RCR *)_hoops_PGC->texture;
					rc->_hoops_GCI[rc->n] = _hoops_GCI;
					
					if (_hoops_GSSH) {
						rc->params[rc->n] = _hoops_GSSH->_hoops_CCHA;
						rc->param_width[rc->n] = _hoops_GSSH->_hoops_GSHA;
						flags = _hoops_GSSH->_hoops_SCAI;
					}
					rc->flags[rc->n] = _hoops_RPARC; /* _hoops_CGH _hoops_RGR _hoops_IRIGR _hoops_SGI _hoops_HII _hoops_GHARC->_hoops_HGCI */
					
					if (BIT (flags, _hoops_HPPAR))
						rc->flags[rc->n] |= _hoops_RHARC;
					if (BIT (flags, _hoops_RSRSP))
						rc->flags[rc->n] |= _hoops_GPGRC;
					if (BIT (flags, _hoops_SSRSP) && BIT (flags, _hoops_PSRSP)) {
						rc->flags[rc->n] |= _hoops_HSGRC;
						rc->params[rc->n] = 0;
						rc->param_width[rc->n] = 0;
					}
					if (rc->txr[rc->n]->_hoops_RSCP+1>=rc->param_width[rc->n])
						rc->_hoops_RSCP[rc->n] = 0;
					else
						rc->_hoops_RSCP[rc->n] = rc->txr[rc->n]->_hoops_RSCP;

 					if (BIT (_hoops_PGC->flags, _hoops_PRA)) {

						if (BIT (_hoops_PGC->flags, _hoops_PPIR))
							rc->_hoops_AIGRC[rc->n] = matr->_hoops_CSHR;
						else
							rc->_hoops_AIGRC[rc->n] = rc->txr[rc->n]->_hoops_HPIR._hoops_IPIR;
					}
					else {
						if (_hoops_APARC)
							rc->flags[rc->n] |= _hoops_ACGRC;
						rc->_hoops_AIGRC[rc->n] = _hoops_GPSR::_hoops_IAHHP;
					}
					rc->_hoops_PIGRC[rc->n] = matr->color[_hoops_HIA];

					/* _hoops_RH _hoops_SRS _hoops_SPI _hoops_RCAP _hoops_PAH _hoops_HGCR _hoops_IRS _hoops_GHGPR _hoops_PGSR _hoops_GGR _hoops_HHH _hoops_RGHSH,
					   _hoops_IAS._hoops_ISHI. "_hoops_PRRRA _hoops_PSSAH" _hoops_GPP _hoops_SPI _hoops_HAIR _hoops_IIGR _hoops_HRRRA */
					if (_hoops_PGC == matr->_hoops_SCA &&
						BIT (_hoops_PGC->texture->_hoops_SCR, _hoops_IGA)) {
						rc->_hoops_AIGRC[rc->n].red	*= matr->_hoops_CSHR.red;
						rc->_hoops_AIGRC[rc->n].green *= matr->_hoops_CSHR.green;
						rc->_hoops_AIGRC[rc->n].blue	*= matr->_hoops_CSHR.blue;
					}

					_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
					rc->_hoops_AIGRC[rc->n].red	*= _hoops_RRA->image._hoops_HRA.red;
					rc->_hoops_AIGRC[rc->n].green *= _hoops_RRA->image._hoops_HRA.green;
					rc->_hoops_AIGRC[rc->n].blue	*= _hoops_RRA->image._hoops_HRA.blue;

					rc->n++;
					if (_hoops_GSSH)
						_hoops_GSSH = _hoops_GSSH->next;
					if (rc->n == OGL_MAX_PASSES)
						goto done;
				}
			} while ((_hoops_PGC = _hoops_PGC->next) != null);
			/* _hoops_HHH _hoops_ICCI _hoops_PAGRC _hoops_HS _hoops_PSP _hoops_AHARC _hoops_IHAHP, _hoops_HIS _hoops_GGR _hoops_AGR _hoops_IS _hoops_GHAA _hoops_AI
			 * _hoops_IS _hoops_GISR _hoops_SS, _hoops_SR _hoops_SGH _hoops_RH _hoops_SS _hoops_IS _hoops_IRHH _hoops_IRS _hoops_PHARC _hoops_CSRA _hoops_HIRA, _hoops_PPR _hoops_IRHH _hoops_RH _hoops_HH _hoops_ASAGI
			 * _hoops_PCPA _hoops_HRGR _hoops_GGR _hoops_RH _hoops_HCHSR _hoops_SRHR.	 _hoops_GPGP _hoops_IRS _hoops_PPRRR, _hoops_RGR _hoops_HRGR _hoops_GPCPR _hoops_PGCHR _hoops_IS _hoops_RH _hoops_ASGH _hoops_PPRRR _hoops_IIGR _hoops_GHGA _hoops_CGSI */
			if (rc->n != 1 &&
				rc->_hoops_GCI[1] == _hoops_GGGRC &&
				!_hoops_CSRGR->_hoops_AIRGC) {
				for (i = 0; i < (int)rc->n; i++)
					rc->flags[i] |= _hoops_ACGRC;
			}
		}
	}


#ifndef _hoops_SIGGC
	/* _hoops_HHARC _hoops_ARCR */
	if (_hoops_GPARC && matr->texture[_hoops_IIA] != null && 	!ANYBIT (_hoops_RPARC, _hoops_AGCGC) &&
		_hoops_CSRGR->glMultiTexCoord2fvARB && _hoops_CSRGR->_hoops_PGHGC && nr->_hoops_IHA->_hoops_AGP) {
		if (param_width >= 2) {
			id = OGL_DEFINE_TEXTURE (_hoops_CSRGR, nr, (_hoops_RCR *)matr->texture[_hoops_IIA], _hoops_PCSGC,1);
 			if (id != _hoops_RSARR) {
				rc->id[rc->n] = id;
				rc->txr[rc->n] = (_hoops_RCR *)matr->texture[_hoops_IIA];
				rc->_hoops_GCI[rc->n] = _hoops_PCSGC;
				rc->params[rc->n] = params;
				rc->param_width[rc->n] = param_width;
				rc->flags[rc->n] = _hoops_RPARC;
				if (BIT (flags, _hoops_HPPAR))
					rc->flags[rc->n] |= _hoops_RHARC;
				if (BIT (flags, _hoops_RSRSP))
					rc->flags[rc->n] |= _hoops_GPGRC;
				if (BIT (flags, _hoops_SSRSP) && BIT (flags, _hoops_PSRSP)) {
					rc->flags[rc->n] |= _hoops_HSGRC;
					rc->params[rc->n] = 0;
					rc->param_width[rc->n] = 0;
				}
				if (rc->txr[rc->n]->_hoops_RSCP+1>=rc->param_width[rc->n])
				    rc->_hoops_RSCP[rc->n] = 0;
				else
				    rc->_hoops_RSCP[rc->n] = rc->txr[rc->n]->_hoops_RSCP;
				if (_hoops_APARC)
				    rc->flags[rc->n] |= _hoops_ACGRC;

				rc->_hoops_IARRC.length = ts->point_count;
				ALLOC_ARRAY_CACHED(rc->_hoops_IARRC._hoops_GHRRC, ts->point_count, Vector);
				ALLOC_ARRAY_CACHED(rc->_hoops_IARRC._hoops_RHRRC, ts->point_count, Vector);
				ALLOC_ARRAY_CACHED(rc->_hoops_IARRC._hoops_AHRRC, ts->point_count, Vector);
				ALLOC_ARRAY_CACHED(rc->_hoops_IARRC._hoops_PHRRC, ts->point_count, Point);
				_hoops_HAARC(ts, rc->_hoops_IARRC._hoops_AHRRC, rc->_hoops_IARRC._hoops_GHRRC,
					rc->_hoops_IARRC._hoops_RHRRC, param_width);
				_hoops_CRARC(nr, ts, rc->_hoops_IARRC._hoops_PHRRC,
					rc->_hoops_IARRC._hoops_AHRRC, rc->_hoops_IARRC._hoops_GHRRC,
					rc->_hoops_IARRC._hoops_RHRRC);
				rc->_hoops_SIGRC[rc->n] = 1;
	 			if (rc->n > 0) {
					rc->_hoops_SIGRC[rc->n] = 1;
					rc->_hoops_SIGRC[rc->n-1] = 0;
					rc->flags[rc->n-1] |= _hoops_CIGRC;
				}
				else {
					rc->_hoops_SIGRC[rc->n] = 0;
				}
				rc->flags[rc->n] |= _hoops_CIGRC;
				rc->_hoops_AIGRC[rc->n] = matr->_hoops_CSHR;
				rc->_hoops_PIGRC[rc->n] = matr->color[_hoops_HIA];
				rc->n++;
				if (rc->n == OGL_MAX_PASSES)
					goto done;
			}
		}
	}
#endif

	/* _hoops_IHARC _hoops_ARCR */
	if (_hoops_GPARC && matr->texture[_hoops_RIA] != null && !BIT (ts->_hoops_CARI, _hoops_HPII)) {
		id = OGL_DEFINE_TEXTURE (_hoops_CSRGR, nr, (_hoops_RCR *)matr->texture[_hoops_RIA], _hoops_HCSGC,0);

		if (BIT (_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_CHARC) &&
			rc->n == 0) {
			/* _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_RH _hoops_RGAR _hoops_RIH _hoops_SR _hoops_GGCR _hoops_IRS _hoops_SHISR _hoops_SPI _hoops_RIH _hoops_SRS, _hoops_HIH _hoops_RGAR _hoops_RPP _hoops_SCH _hoops_HRGR **_hoops_CPSA** _hoops_SAPIA
			 * _hoops_SGS _hoops_PCCP _hoops_RHI _hoops_ARCR _hoops_IAPR _hoops_IRS _hoops_RRH _hoops_HH _hoops_PHPP _hoops_GPCPR _hoops_RH _hoops_PSHR _hoops_GAR _hoops_SAHR _hoops_PCCP _hoops_RHI _hoops_ARCR */
			rc->id[rc->n] = 0;
			rc->txr[rc->n] = 0;
			rc->_hoops_GCI[rc->n] = _hoops_RCGRC;
			rc->params[rc->n] = null;
			rc->param_width[rc->n] = 0;
			rc->flags[rc->n] = _hoops_RPARC;
			rc->_hoops_AIGRC[rc->n] = matr->_hoops_CSHR;
			rc->_hoops_PIGRC[rc->n] = matr->color[_hoops_HIA];
			rc->n++;
			if (rc->n == OGL_MAX_PASSES)
				goto done;
		}

		if (id != _hoops_RSARR) {
			rc->id[rc->n] = id;
			rc->txr[rc->n] = (_hoops_RCR *)matr->texture[_hoops_RIA];
			rc->_hoops_GCI[rc->n] = _hoops_HCSGC;

			if (rc->txr[rc->n]->_hoops_PSR != _hoops_HSR &&
			    nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH) {
			    rc->params[rc->n] = null; /* _hoops_IS _hoops_SHH _hoops_GGSRA _hoops_HPP _hoops_GGRGR _hoops_RIH */
			    rc->param_width[rc->n] = 0;
			    rc->flags[rc->n] |= _hoops_GGRRC;
			}
			else {
			    rc->params[rc->n] = null; /* _hoops_IS _hoops_SHH _hoops_GGSRA _hoops_HPP _hoops_GGRGR _hoops_RIH */
			    rc->param_width[rc->n] = 2;
			    rc->flags[rc->n] |= _hoops_AGRRC;
			}
			if (rc->n != 0)
				rc->_hoops_AIGRC[rc->n] = _hoops_GPSR::_hoops_IAHHP;
			else
				rc->_hoops_AIGRC[rc->n] = matr->_hoops_CSHR;
			rc->_hoops_PIGRC[rc->n] = matr->color[_hoops_HIA];
			rc->n++;
			if (rc->n == OGL_MAX_PASSES)
				goto done;
		}
	}

	/* _hoops_AHSR _hoops_HH */
	if (_hoops_GPARC && matr->texture[_hoops_HIA] != null && _hoops_SIGA->_hoops_AGP != null) {
		if (param_width >= 2) {
			id = OGL_DEFINE_TEXTURE (_hoops_CSRGR, nr, (_hoops_RCR *)matr->texture[_hoops_HIA], _hoops_SSSGC,0);

			if (id != _hoops_RSARR) {
				/* _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_RH _hoops_RGAR _hoops_RIH _hoops_SR _hoops_GGCR _hoops_IRS _hoops_SHISR _hoops_SPI _hoops_RIH _hoops_SRS*/
				if (rc->n == 0) {
					rc->id[rc->n] = 0;
					rc->txr[rc->n] = 0;
					rc->_hoops_GCI[rc->n] = _hoops_RCGRC;
					rc->params[rc->n] = null;
					rc->param_width[rc->n] = 0;
					rc->flags[rc->n] = _hoops_RPARC;
					rc->_hoops_AIGRC[rc->n] = matr->_hoops_CSHR;
					/* _hoops_PSP _hoops_RRP _hoops_IS _hoops_SHARC _hoops_CRGR _hoops_GHI _hoops_HAIR -- _hoops_SCH _hoops_CHH _hoops_SAHR _hoops_HGCR _hoops_CPAHA _hoops_HPP _hoops_RH _hoops_HAPR _hoops_CAPP */
					rc->n++;
					if (rc->n == OGL_MAX_PASSES)
						goto done;
				}
				for (i = 0; i < (int)rc->n; i++) {
					if (rc->_hoops_GCI[i] != _hoops_SSSGC) {
						rc->_hoops_PIGRC[i] = _hoops_GPSR::_hoops_RPSR;
					}
				}
				rc->id[rc->n] = id;
				rc->txr[rc->n] = (_hoops_RCR *)matr->texture[_hoops_HIA];
				rc->_hoops_GCI[rc->n] = _hoops_SSSGC;
				rc->params[rc->n] = params;
				rc->param_width[rc->n] = param_width;
				rc->flags[rc->n] = _hoops_RPARC;
				if (BIT (flags, _hoops_HPPAR))
				    rc->flags[rc->n] |= _hoops_RHARC;
				if (BIT (flags, _hoops_RSRSP))
				    rc->flags[rc->n] |= _hoops_GPGRC;
				rc->_hoops_AIGRC[rc->n] = _hoops_GPSR::_hoops_RPSR;
				if (BIT (rc->txr[rc->n]->_hoops_SCR, _hoops_ICARA))
					rc->_hoops_PIGRC[rc->n] = rc->txr[rc->n]->_hoops_HPIR._hoops_IPIR;
				else
					rc->_hoops_PIGRC[rc->n] = _hoops_GPSR::_hoops_IAHHP;
				rc->n++;
				if (rc->n == OGL_MAX_PASSES)
					goto done;
			}
		}
	}

#endif
	/* _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_ISAP _hoops_SHS, _hoops_SGH _hoops_IRS _hoops_SHISR _hoops_SPI _hoops_RIH */
	if (rc->n == _hoops_IPHAP) {
		rc->id[rc->n] = 0;
		rc->txr[rc->n] = 0;
		rc->_hoops_GCI[rc->n] = _hoops_RCGRC;
		rc->params[rc->n] = null;
		rc->param_width[rc->n] = 0;
		rc->flags[rc->n] = _hoops_RPARC;
		rc->_hoops_AIGRC[rc->n] = matr->_hoops_CSHR;
		rc->_hoops_PIGRC[rc->n] = matr->color[_hoops_HIA];
		rc->n++;
		if (rc->n == OGL_MAX_PASSES)
			goto done;
	}

	if (_hoops_RPARC == _hoops_CARRC) {
		matr = _hoops_SIGA->_hoops_GIA;
		/* _hoops_GIARC _hoops_RIPS _hoops_IS _hoops_ISSC */
 		_hoops_RPARC ^= (_hoops_CARRC|_hoops_AGCGC);
		_hoops_GSSH = ts->_hoops_GSSH; /* _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_ISSC _hoops_IS _hoops_RH _hoops_HSPP */
		goto _hoops_PPARC;
	}

done:
 	rc->pass = 0;
	rc->_hoops_CHRRC = rc->n;

	/* _hoops_RIARC _hoops_HIAH */
	if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI)) {
		RGB alter *rgb;

		for (i = 0; i < (int)rc->_hoops_CHRRC; i++) {
			rgb = &rc->_hoops_AIGRC[i];
			*rgb = RGB(rgb->_hoops_CPIR());
			rgb = &rc->_hoops_PIGRC[i];
			*rgb = RGB(rgb->_hoops_CPIR());
		}
	}

} /* _hoops_RSGR _hoops_API _hoops_AIARC */



/*
 * _hoops_PGAA
 */
local bool
_hoops_GHAH (OGLData alter * _hoops_CSRGR, Net_Rendition const & nr) {
	_hoops_CIGA const & _hoops_SIGA = nr->_hoops_IHA;
	GLuint list;
	_hoops_RHAH const *_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;
	int _hoops_HHAH = _hoops_CSIR->length;
	GLsizei width = _hoops_IPAH (4 * _hoops_HHAH);
	float _hoops_PIARC[4][4];
	int _hoops_GRRA = 0;
	bool _hoops_RRGRC = true;

	if (BIT(nr->_hoops_SRA->flags, _hoops_CHSI))
		return true;

	if (!_hoops_CSRGR->_hoops_CSC._hoops_RAIH && !_hoops_CSRGR->_hoops_GIIGC)
		return true;

	if (_hoops_CSRGR->_hoops_CSC._hoops_PSAH == _hoops_RSARR) {
		OGL_ALLOC_TEXTURE(list);
		if (!list) return false;
		_hoops_CSRGR->_hoops_CSC._hoops_PSAH = list;
	}
	else {
		list = _hoops_CSRGR->_hoops_CSC._hoops_PSAH;
	}

	if (_hoops_CSRGR->_hoops_CSC._hoops_SGAGC[_hoops_GRRA] != list) {
		_hoops_IPRGC(_hoops_CSRGR, _hoops_GRRA, GL_TEXTURE_2D, list);

		if (!ANYBIT (_hoops_CSIR->_hoops_CPGPR, _hoops_CASIR | _hoops_AHSGA) &&
				(_hoops_CSRGR->_hoops_CSC._hoops_AAAGC == _hoops_CSIR->_hoops_HAA)) {
			_hoops_RRGRC = false;
		}
	}
	else {
		if (!ANYBIT (_hoops_CSIR->_hoops_CPGPR, _hoops_CASIR | _hoops_AHSGA) &&
				(_hoops_CSRGR->_hoops_CSC._hoops_AAAGC == _hoops_CSIR->_hoops_HAA)) {
			_hoops_RRGRC = false;
		}
	}

	if (_hoops_RRGRC) {
		_hoops_CSRGR->_hoops_CSC._hoops_AAAGC = (Named_Material *) _hoops_CSIR->_hoops_HAA;

		_hoops_IPRGC(_hoops_CSRGR, _hoops_GRRA, GL_TEXTURE_2D, list);
		_hoops_HASGC (nr, width, false);
	}

	if (BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES) &&
		(_hoops_SIGA->_hoops_AGP != null))	 {
		ENSURE_TEXTURE_ENV_MODE(_hoops_CSRGR, GL_MODULATE, _hoops_GRRA);
	}
	else {
		ENSURE_TEXTURE_ENV_MODE(_hoops_CSRGR, GL_DECAL, _hoops_GRRA);
	}


	ENSURE_TEXTURE_PERSPECTIVE_CORRECTION_ON(_hoops_CSRGR, _hoops_GRRA);
	ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, GL_TEXTURE_2D, GL_REPEAT,0);
	_hoops_SAIRH(_hoops_CSRGR, GL_TEXTURE_2D, GL_REPEAT,0);


	if (!BIT (nr->_hoops_IRR->_hoops_CSA,_hoops_HIRC)) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	_hoops_SRGRC(_hoops_CSRGR,0);

	_hoops_PIARC[0][0] = 1.0f / (float)(width);
	_hoops_PIARC[0][1] = 0.0f;
	_hoops_PIARC[0][2] = 0.0f;
	_hoops_PIARC[0][3] = 0.0f;
	_hoops_PIARC[1][0] = 0.0f;
	_hoops_PIARC[1][1] = 1.0f;
	_hoops_PIARC[1][2] = 0.0f;
	_hoops_PIARC[1][3] = 0.0f;
	_hoops_PIARC[2][0] = 0.0f;
	_hoops_PIARC[2][1] = 0.0f;
	_hoops_PIARC[2][2] = 1.0f;
	_hoops_PIARC[2][3] = 0.0f;
	_hoops_PIARC[3][0] = 1.5f / (float)(width);		/* _hoops_RCSC _hoops_RHAP _hoops_RGR _hoops_PIRA _hoops_AHGS _hoops_IS _hoops_IPHR? */
	_hoops_PIARC[3][1] = 0.0f;
	_hoops_PIARC[3][2] = 0.0f;
	_hoops_PIARC[3][3] = 1.0f;

	glMatrixMode (GL_TEXTURE);
	glLoadMatrixf (&_hoops_PIARC[0][0]);
	glMatrixMode (GL_MODELVIEW);

	return true;
}

#ifndef DISABLE_MUTEX
#define OGL_DL_DELETE_TASK
#endif

#ifdef _hoops_GGHSH
//[10503] : _hoops_HIARC _hoops_AGCGR _hoops_GPP _hoops_RGHR _hoops_GGGR/_hoops_IIARC.
#undef OGL_DL_DELETE_TASK
#endif

#ifdef _hoops_SHRIP
#undef OGL_DL_DELETE_TASK
#endif

#ifndef WGL_DRIVER
#undef OGL_DL_DELETE_TASK
#endif

#ifdef OGL_DL_DELETE_TASK
#include "task_queue.h"

class OGL_DL_Delete_Task : public _hoops_GCARR {

public:

	OGL_DL_Delete_Task(Display_Context const * dc, _hoops_AGCI * _hoops_RGAGR) {

		_hoops_RCARR = _hoops_RGAGR;

		if (dc->_hoops_GHRI->_hoops_ACARR)
			dc->_hoops_GHRI->_hoops_ACARR->_hoops_PCARR(this);
		else
			_hoops_HCARR(false);
	};

	virtual ~OGL_DL_Delete_Task() {
		;
	};

	virtual _hoops_ICARR Type() {return _hoops_CIARC;}

	virtual void _hoops_HCARR(bool _hoops_SCARR) {

		UNREFERENCED(_hoops_SCARR);

		_hoops_RRPRH *_hoops_IRSRA = _hoops_ARPRH();
		OGL_Master_Context *_hoops_SIARC = _hoops_IRSRA->_hoops_HRACI;

		_hoops_CAAI (_hoops_SIARC->_hoops_GCARC);

		HDC _hoops_RCARC = wglGetCurrentDC ();
		HGLRC _hoops_ACARC = wglGetCurrentContext ();
		wglMakeCurrent (_hoops_SIARC->hDC, _hoops_SIARC->hGLRC);

		_hoops_AGCI * _hoops_AGAGR=null;

		while ((_hoops_AGAGR = _hoops_RCARR) != null) {
			_hoops_RCARR = _hoops_AGAGR->next;
			_hoops_SPSI (_hoops_AGAGR);
		}

		wglMakeCurrent (_hoops_RCARC, _hoops_ACARC);

		_hoops_APAI (_hoops_SIARC->_hoops_GCARC);

		delete this;
	};

private:
	_hoops_AGCI * _hoops_RCARR;
};

#endif



local void _hoops_SSRGR(Display_Context const * dc)
{

	_hoops_GGAGR alter * _hoops_GHRI = (_hoops_GGAGR alter *)dc->_hoops_GHRI;

	_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);
	_hoops_AGCI * _hoops_RGAGR = _hoops_GHRI->_hoops_RGAGR;
	_hoops_GHRI->_hoops_RGAGR = null;
	_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);

	if (_hoops_RGAGR != null) {

		_hoops_AGCI * _hoops_AGAGR = _hoops_RGAGR;

		OGLData alter *_hoops_CSRGR = OGLD (dc);
		bool _hoops_PCARC;

#ifdef OGL_DL_DELETE_TASK
		_hoops_PCARC = (_hoops_CSRGR->_hoops_GSGRR || BIT (dc->options._hoops_IRARR, _hoops_HCARC));
#else
		_hoops_PCARC = true;
		UNREFERENCED (_hoops_CSRGR);
#endif

		while (_hoops_AGAGR != null) {

			OGL_Display_List alter * odl = (OGL_Display_List alter *)_hoops_AGAGR;

			if (odl->type == OGL_DL_TEXTURE && odl->_hoops_PPAH) {
				/* _hoops_RPP _hoops_RH _hoops_CSRI _hoops_HRGR _hoops_IRS _hoops_CGRH _hoops_HH, _hoops_SRPS _hoops_RH _hoops_PIH _hoops_ARPP _hoops_PGAGR _hoops_SCH _hoops_SGGR */
				Image alter *image = (Image alter *)odl->_hoops_PPAH->owner;
				if (image &&
					BIT (image->flags, _hoops_GRRH)) {
					if (ALLBITS (image->flags, _hoops_GRRH|_hoops_APAH))
						_hoops_CGAGR (dc, odl);
					image->flags &= ~(_hoops_GRRH|_hoops_APAH);
				}
			}

			switch (odl->type) {
				case OGL_DL_SEGMENT_TREE: {
					if (odl->item._hoops_ACGI._hoops_ARRI)
						_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_ARRI->Count();
					if (odl->item._hoops_ACGI._hoops_AGAI)
						_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_AGAI->Count();
					if (odl->item._hoops_ACGI._hoops_GGAI)
						_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_GGAI->Count();
					if (odl->item._hoops_ACGI._hoops_RGAI)
						_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_RGAI->Count();
					if (odl->item._hoops_ACGI._hoops_CAPI)
						_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_CAPI->Count();
					if (odl->item._hoops_ACGI._hoops_RCII)
						_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_RCII->Count();
					if (odl->item._hoops_ACGI._hoops_ICARC)
						_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_ICARC->Count();
					if (odl->item._hoops_ACGI._hoops_GAAI)
						_hoops_RCCA(_hoops_SGAGR) += odl->item._hoops_ACGI._hoops_GAAI->Count();
				} break;

				case OGL_DL_GEOMETRY:
				case OGL_DL_GEOMETRY_VBO: {
					if (odl->item.geometry.id)
						_hoops_RCCA(_hoops_SGAGR)++;
				} break;

				default:
					_hoops_RCCA(_hoops_SGAGR)++;
			}


			if (_hoops_PCARC) {
				_hoops_AGCI * _hoops_RRAGR = _hoops_AGAGR->next;
				_hoops_SPSI (_hoops_AGAGR);
				_hoops_AGAGR = _hoops_RRAGR;
			}
			else
				_hoops_AGAGR = _hoops_AGAGR->next;

		}

#ifdef OGL_DL_DELETE_TASK
		if (_hoops_RGAGR &&
			!_hoops_PCARC) {
			glFlush();  // _hoops_PAHA'_hoops_RA _hoops_RRP _hoops_SCH _hoops_HIH _hoops_GRRI'_hoops_GRI _hoops_SGS _hoops_HGCR _hoops_PGHPR _hoops_CCARC _hoops_GAAP _hoops_SIGR
			NEW(OGL_DL_Delete_Task)(dc, _hoops_RGAGR);
		}
#endif
	}

}




/*
 * _hoops_PGAA
 */
void _hoops_SCARC (
		Net_Rendition const & nr,
		Tristrip const *ts)
{
	/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_AIRI _hoops_HIGR _hoops_RGAR, _hoops_SIHH _hoops_RH _hoops_PPPS _hoops_SIHC _hoops_GGR _hoops_AGR _hoops_IS _hoops_CAH */
	Tristrip alter *_hoops_RPIAR = (Tristrip alter *) ts;
	_hoops_GACR alter *dl;
	OGL_Display_List alter *odl=0;
	bool _hoops_RACR;

	_hoops_RACR = _hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &dl, &odl, OGL_DL_GEOMETRY_VBO);
	HD_Queue_Destroy_List (odl, true);
}


local bool _hoops_AACR(
	Net_Rendition const &		nr,
	_hoops_GACR alter **		_hoops_ASRGR,
	_hoops_GACR alter **		dl,
	OGL_Display_List alter **	odl,
	unsigned int				type)
{
	bool _hoops_RACR = HI_Get_Display_List(nr->_hoops_SRA->_hoops_GHRI, _hoops_ASRGR, dl);

	if ((*dl)->list == null) {
		ZALLOC(*odl, OGL_Display_List);
		AGLM((*odl)->_hoops_CSRGR = OGLD(nr->_hoops_SRA));
		(*dl)->list = (_hoops_AGCI*)*odl;
		(*dl)->_hoops_GGCI = -1;
		(*odl)->_hoops_GHRI = nr->_hoops_SRA->_hoops_GHRI;
		(*odl)->time_stamp = HOOPS_WORLD->_hoops_GPPI;
		(*odl)->_hoops_GPPI = HOOPS_WORLD->_hoops_GPPI;
		(*odl)->type = type;
		(*odl)->_hoops_PPAH = *dl;

		_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);
		(*odl)->next = HOOPS_WORLD->_hoops_GPAI;
		(*odl)->prev = &(HOOPS_WORLD->_hoops_GPAI);
		if (HOOPS_WORLD->_hoops_GPAI != null)
			HOOPS_WORLD->_hoops_GPAI->prev = &(*odl)->next;
		HOOPS_WORLD->_hoops_GPAI = *odl;
		_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);

		_hoops_RACR = true;
		if (type == OGL_DL_SEGMENT_TREE) {
			(*dl)->action_mask = _hoops_RSCI;
			if (BIT (nr->_hoops_SRA->flags, _hoops_IIGC))
				(*dl)->_hoops_PRRI |= _hoops_AASI;
		}
	}
	*odl = (OGL_Display_List*) (*dl)->list;

	return _hoops_RACR;
}


local void
_hoops_GSARC (OGL_Vertex_Buffer_Object alter *_hoops_SAAS)
{
	glBindBufferARBProc _hoops_PSPGI = (glBindBufferARBProc) HOOPS_WORLD->_hoops_PSPGI;
	glBufferDataARBProc _hoops_HSPGI = (glBufferDataARBProc)HOOPS_WORLD->_hoops_HSPGI;
	glDeleteBuffersARBProc _hoops_ISPGI = (glDeleteBuffersARBProc)HOOPS_WORLD->_hoops_ISPGI;

	if (_hoops_SAAS->_hoops_RSARC)
		FREE_ARRAY (_hoops_SAAS->_hoops_RSARC, _hoops_SAAS->_hoops_ASARC + 1, int);
	if (_hoops_SAAS->_hoops_PSARC)
		FREE_ARRAY (_hoops_SAAS->_hoops_PSARC, _hoops_SAAS->_hoops_HSARC, int);
	if (_hoops_SAAS->_hoops_ISARC)
		FREE_ARRAY (_hoops_SAAS->_hoops_ISARC, _hoops_SAAS->count, int);
	if (_hoops_SAAS->_hoops_CSARC)
		FREE_ARRAY (_hoops_SAAS->_hoops_CSARC, _hoops_SAAS->count, int);
	if (_hoops_SAAS->_hoops_SSARC)
		FREE_ARRAY (_hoops_SAAS->_hoops_SSARC, _hoops_SAAS->count, _hoops_CAIS);
	if (_hoops_SAAS->_hoops_GGPRC)
		FREE_ARRAY (_hoops_SAAS->_hoops_GGPRC, _hoops_SAAS->_hoops_RGPRC * _hoops_SAAS->_hoops_AGPRC, short);
	if (_hoops_SAAS->_hoops_PGPRC)
		FREE_ARRAY (_hoops_SAAS->_hoops_PGPRC, _hoops_SAAS->_hoops_HGPRC * _hoops_SAAS->_hoops_AGPRC, short);
	if (_hoops_SAAS->_hoops_IGPRC) {
		_hoops_PSPGI(GL_ARRAY_BUFFER_ARB, _hoops_SAAS->_hoops_IGPRC);
		_hoops_HSPGI (GL_ARRAY_BUFFER_ARB, 0, NULL, GL_STATIC_DRAW_ARB);
		_hoops_ISPGI (1, &_hoops_SAAS->_hoops_IGPRC);
		_hoops_SAAS->_hoops_IGPRC = 0;
	}
	if (_hoops_SAAS->_hoops_CGPRC) {
		_hoops_PSPGI(GL_ARRAY_BUFFER_ARB, _hoops_SAAS->_hoops_CGPRC);
		_hoops_HSPGI (GL_ARRAY_BUFFER_ARB, 0, NULL, GL_STATIC_DRAW_ARB);
		_hoops_ISPGI (1, &_hoops_SAAS->_hoops_CGPRC);
		_hoops_SAAS->_hoops_CGPRC = 0;
	}
	if (_hoops_SAAS->_hoops_SGPRC) {
		_hoops_PSPGI(GL_ARRAY_BUFFER_ARB, _hoops_SAAS->_hoops_SGPRC);
		_hoops_HSPGI (GL_ARRAY_BUFFER_ARB, 0, NULL, GL_STATIC_DRAW_ARB);
		_hoops_ISPGI (1, &_hoops_SAAS->_hoops_SGPRC);
		_hoops_SAAS->_hoops_SGPRC = 0;
	}
	if (_hoops_SAAS->_hoops_GRPRC) {
		_hoops_PSPGI(GL_ARRAY_BUFFER_ARB, _hoops_SAAS->_hoops_GRPRC);
		_hoops_HSPGI (GL_ARRAY_BUFFER_ARB, 0, NULL, GL_STATIC_DRAW_ARB);
		_hoops_ISPGI (1, &_hoops_SAAS->_hoops_GRPRC);
		_hoops_SAAS->_hoops_GRPRC = 0;
	}
	if (_hoops_SAAS->_hoops_RRPRC) {
		_hoops_PSPGI(GL_ELEMENT_BUFFER_ARB, _hoops_SAAS->_hoops_RRPRC);
		_hoops_HSPGI (GL_ELEMENT_BUFFER_ARB, 0, NULL, GL_STATIC_DRAW_ARB);
		_hoops_ISPGI (1, &_hoops_SAAS->_hoops_RRPRC);
		_hoops_SAAS->_hoops_RRPRC = 0;
	}
	if (_hoops_SAAS->_hoops_ARPRC) {
		_hoops_PSPGI(GL_ELEMENT_BUFFER_ARB, _hoops_SAAS->_hoops_ARPRC);
		_hoops_HSPGI (GL_ELEMENT_BUFFER_ARB, 0, NULL, GL_STATIC_DRAW_ARB);
		_hoops_ISPGI (1, &_hoops_SAAS->_hoops_ARPRC);
		_hoops_SAAS->_hoops_ARPRC = 0;
	}
	_hoops_PSPGI(GL_ARRAY_BUFFER_ARB, 0);
	_hoops_PSPGI(GL_ELEMENT_BUFFER_ARB, 0);

	FREE (_hoops_SAAS, OGL_Vertex_Buffer_Object);
}


local void
_hoops_PRPRC (OGL_Polymarker_Vertex_Buffer_Object alter *_hoops_SAAS)
{
	glBindBufferARBProc _hoops_PSPGI = (glBindBufferARBProc) HOOPS_WORLD->_hoops_PSPGI;
	glBufferDataARBProc _hoops_HSPGI = (glBufferDataARBProc) HOOPS_WORLD->_hoops_HSPGI;
	glDeleteBuffersARBProc _hoops_ISPGI = (glDeleteBuffersARBProc) HOOPS_WORLD->_hoops_ISPGI;

	if (_hoops_SAAS->_hoops_HRPRC) {
		_hoops_PSPGI(GL_ARRAY_BUFFER_ARB, _hoops_SAAS->_hoops_HRPRC);
		_hoops_HSPGI (GL_ARRAY_BUFFER_ARB, 0, NULL, GL_STATIC_DRAW_ARB);
		_hoops_ISPGI (1, &_hoops_SAAS->_hoops_HRPRC);
		_hoops_SAAS->_hoops_HRPRC = 0;
	}
	_hoops_PSPGI(GL_ARRAY_BUFFER_ARB, 0);
	_hoops_PSPGI(GL_ELEMENT_BUFFER_ARB, 0);
	HOOPS_WORLD->display_list_vram_usage -= _hoops_SAAS->_hoops_GPGC;
	FREE (_hoops_SAAS, OGL_Polymarker_Vertex_Buffer_Object);
}


local void
_hoops_IPGI (OGL_Display_List_List *list) {
	if (list) {
		OGL_Display_List *_hoops_IRAGR;
		while ((_hoops_IRAGR = list->RemoveFirst()) != null) {
			_hoops_SPSI (_hoops_IRAGR);
		}
		delete list;
	}
}


local void
_hoops_SPSI (_hoops_AGCI *_hoops_AGAGR)
{
	OGL_Display_List alter * odl = (OGL_Display_List alter *)_hoops_AGAGR;
	AGLM(OGLData *_hoops_CSRGR = odl->_hoops_CSRGR);
	AGLM(ASSERT(_hoops_CSRGR != null));
	int i;

	switch (odl->type) {
		case OGL_DL_TEXTURE: {
			if (odl->item.texture.id &&
				odl->item.texture.id != _hoops_RSARR)
				OGL_FREE_TEXTURE(odl->item.texture.id);

			if (odl->item.texture._hoops_SRAGR) {
				for (i=0; i<_hoops_PGGRC; i++)
					if (odl->item.texture._hoops_SRAGR[i] &&
						odl->item.texture._hoops_SRAGR[i] != _hoops_RSARR)
						OGL_FREE_TEXTURE(odl->item.texture._hoops_SRAGR[i]);
				FREE_ARRAY(odl->item.texture._hoops_SRAGR, _hoops_PGGRC, GLuint);
			}
			HOOPS_WORLD->_hoops_SARH -= odl->_hoops_CARH;
		}break;

		case OGL_DL_GEOMETRY: {
			if (odl->item.geometry.id &&
				odl->item.geometry.id != _hoops_RSARR)
				glDeleteLists (odl->item.geometry.id, 1);
			HOOPS_WORLD->display_list_vram_usage -= odl->_hoops_CARH;
		}break;

		case OGL_DL_GEOMETRY_VBO: {
			if (odl->item.geometry.id != 0 &&
				odl->item.geometry.id != _hoops_RSARR) {
				_hoops_GSARC ((OGL_Vertex_Buffer_Object *)odl->item.geometry.id);
				odl->item.geometry.id = _hoops_RSARR;
			}
			HOOPS_WORLD->display_list_vram_usage -= odl->_hoops_CARH;
		}break;

		case OGL_DL_POLYMARKER_VBO_LIST: {
			if (odl->item.geometry.id &&
				odl->item.geometry.id != _hoops_RSARR) {
				OGL_DL_VBO_List* list = (OGL_DL_VBO_List *)odl->item.geometry.id;
				OGL_Polymarker_Vertex_Buffer_Object *_hoops_SAAS;

				while ((_hoops_SAAS = list->RemoveFirst()) != null) {
					_hoops_PRPRC (_hoops_SAAS);
				}
				delete list;
			}
		}break;

		case OGL_DL_SEGMENT_POLYLINE: {
			Polyedge *pe;
			if ((pe = odl->item._hoops_RPPI.pe) != null) {
				if (_hoops_ISAI (pe) == 0) {
					/* _hoops_RPP _hoops_SR _hoops_SGIPR _hoops_HGCR _hoops_ARI _hoops_CCA _hoops_IRS _hoops_ACRI _hoops_SGS _hoops_ASSP'_hoops_RA _hoops_HS
					 * _hoops_IRPRC, _hoops_SR'_hoops_ASAR _hoops_GGR _hoops_SPGC */
					glDeleteLists (V2I(pe->_hoops_GAHA), 1);
					FREE (pe, Polyedge);
				}
			}
			HOOPS_WORLD->display_list_vram_usage -= odl->_hoops_CARH;
		}break;

		case OGL_DL_SEGMENT_POLYGON: {
			_hoops_IPGI (odl->item._hoops_ACII._hoops_PCII);
			_hoops_IPGI (odl->item._hoops_ACII._hoops_GHPI);
		} break;

		case OGL_DL_SEGMENT_TREE: {
			OGL_Display_List_List *list;
			_hoops_GRGGI *glist;
			Geometry *g;

			if ((list = odl->item._hoops_ACGI._hoops_ARRI) != null)
				_hoops_IPGI (list);
			if ((list = odl->item._hoops_ACGI._hoops_AGAI) != null)
				_hoops_IPGI (list);
			if ((list = odl->item._hoops_ACGI._hoops_GGAI) != null)
				_hoops_IPGI (list);
			if ((list = odl->item._hoops_ACGI._hoops_RGAI) != null)
				_hoops_IPGI (list);
			if ((list = odl->item._hoops_ACGI._hoops_CAPI) != null)
				_hoops_IPGI (list);
			if ((list = odl->item._hoops_ACGI._hoops_RCII) != null)
				_hoops_IPGI (list);
			if ((list = odl->item._hoops_ACGI._hoops_ICARC) != null)
				_hoops_IPGI (list);
			if ((list = odl->item._hoops_ACGI._hoops_GAAI) != null)
				_hoops_IPGI (list);
			glist = odl->item._hoops_ACGI._hoops_CRPRC;
			if (glist) {
				while ((g = glist->RemoveFirst()) != null) {
					_hoops_HPRH (g);
				}
				delete glist;
			}
			glist = odl->item._hoops_ACGI._hoops_SRPRC;
			if (glist) {
				while ((g = glist->RemoveFirst()) != null) {
					_hoops_HPRH (g);
				}
				delete glist;
			}
			odl->item._hoops_ACGI._hoops_ARRI = null;
			odl->item._hoops_ACGI._hoops_AGAI = null;
			odl->item._hoops_ACGI._hoops_GGAI = null;
			odl->item._hoops_ACGI._hoops_RGAI = null;
			odl->item._hoops_ACGI._hoops_CAPI = null;
			odl->item._hoops_ACGI._hoops_RCII = null;
			odl->item._hoops_ACGI._hoops_CRPRC = null;
			odl->item._hoops_ACGI._hoops_SRPRC = null;
			odl->item._hoops_ACGI._hoops_GAAI = null;
			odl->item._hoops_ACGI._hoops_RGP = 0;
			odl->item._hoops_ACGI.flags = 0;
		}break;

		case OGL_DL_GEOMETRY_LIST: {
			if (odl->item.geometry.id &&
				odl->item.geometry.id != _hoops_RSARR) {
					OGL_DL_ID_List* list = (OGL_DL_ID_List *)odl->item.geometry.id;


					while ( list->PeekFirst() != 0) {
						glDeleteLists (list->RemoveFirst(), 1);
					}
					delete list;
					HOOPS_WORLD->display_list_vram_usage -= odl->_hoops_CARH;
			}
		}break;

		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				   "unrecognized display list type in opengl driver.");
			break;
	}
	FREE(odl, OGL_Display_List);
}


/*****************************************************************************
 *****************************************************************************
								_hoops_GAPRC
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_SRAC
 */
local void
draw_dc_polydot (Net_Rendition const & nr, int count, DC_Point const * points) {
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_IAPA const		*_hoops_CAPA = null;
	DC_Point const				*_hoops_SPGGA = points;
	int								_hoops_HAHC = count;


	_hoops_RAPRC("draw_dc_polydot", true);

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
		HD_Clip_DC_Polydot (nr, count, points, 0, _hoops_RHGGA);
		return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;
		bool							_hoops_IAHC = false;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}

		if (_hoops_IAHC) {
			HD_Clip_DC_Polydot (nr, count, points, 0, _hoops_GPHC);
			return;
		}
	}

	_hoops_SCIGC (_hoops_CSRGR);
	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	_hoops_AIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
	_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));
	OGL_SET_LINE_RENDITION (_hoops_CSRGR, nr, nr->_hoops_AHP);
	ENSURE_LINE_SMOOTH(_hoops_CSRGR, false);

	_hoops_GPRH(_hoops_CCCA) += count;

	do {
		if (_hoops_CAPA != null) {
			_hoops_HCIGC (_hoops_CSRGR);
			_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			_hoops_IGCGC (_hoops_CSRGR);
		}
		points = _hoops_SPGGA;
		count = _hoops_HAHC;

		glBegin (GL_POINTS);
		while (count-- > 0) {
			glVertex3f (points->x + 0.5f, points->y + 0.5f, points->z);
			points++;
		}
		glEnd ();

		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);
}


/*
 * _hoops_SRAC
 */
local void
draw_dc_colorized_polydot (
	Net_Rendition const & nr,
	int						count,
	DC_Point const		*points,
	RGBAS32 const		*_hoops_IASGR,
	bool				single) {
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_IAPA const		*_hoops_CAPA = null;
	DC_Point const				*_hoops_SPGGA = points;
	int							_hoops_HAHC = count;
	bool						_hoops_CRSPH;

	_hoops_RAPRC("draw_dc_polydot", true);

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
		HD_Clip_DC_Polydot (nr, count, points, _hoops_IASGR, _hoops_RHGGA|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}

	_hoops_CRSPH = BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;
		bool							_hoops_IAHC = false;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}

		if (_hoops_IAHC) {
			HD_Clip_DC_Polydot (nr, count, points, _hoops_IASGR, _hoops_GPHC|(single?_hoops_RAIC:_hoops_PAIC));
			return;
		}
	}

	_hoops_SCIGC (_hoops_CSRGR);
	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	_hoops_AIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
	_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));
	OGL_SET_LINE_RENDITION (_hoops_CSRGR, nr, nr->_hoops_AHP);
	ENSURE_LINE_SMOOTH(_hoops_CSRGR, false);
	_hoops_AAPRC(_hoops_CSRGR, false);

	_hoops_GPRH(_hoops_CCCA) += count;

	do {
		RGBAS32				_hoops_ARSRI;

		if (_hoops_CAPA != null) {
			_hoops_HCIGC (_hoops_CSRGR);
			_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			_hoops_IGCGC (_hoops_CSRGR);
		}
		points = _hoops_SPGGA;
		count = _hoops_HAHC;

		glBegin (GL_POINTS);

		_hoops_ARSRI = *_hoops_IASGR;
		_hoops_PAPRC(_hoops_IASGR->r, _hoops_IASGR->g, _hoops_IASGR->b, _hoops_IASGR->a, _hoops_CRSPH);

		while (count-- > 0) {
			glVertex3f (points->x + 0.5f, points->y + 0.5f, points->z);
			points++;
			if (!single) {
				_hoops_IASGR++;
				if (count > 0 && _hoops_ARSRI != *_hoops_IASGR) {
					_hoops_ARSRI = *_hoops_IASGR;
					_hoops_PAPRC(_hoops_IASGR->r, _hoops_IASGR->g, _hoops_IASGR->b, _hoops_IASGR->a, _hoops_CRSPH);
				}
			}
		}
		glEnd ();

		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);

	_hoops_CSRGR->_hoops_RPCI=_hoops_RSARR;
	_hoops_ICGRC(_hoops_CSRGR);
}


/*
 * _hoops_SRAC
 */
local void
draw_dc_polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	Display_Context const *		dc = nr->_hoops_SRA;
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	OGLData alter *				_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	int							weight;
	_hoops_IAPA const	*	_hoops_CAPA = null;
	bool 						antialias;
	bool 						_hoops_HAPRC;

	_hoops_RAPRC("draw_dc_polyline", true);

	/*
	 * _hoops_IAPRC _hoops_PAR _hoops_SHRAR _hoops_APGR _hoops_IIGR _hoops_IGAA _hoops_SPR _hoops_PIHA _hoops_SHH _hoops_GIR _hoops_HPP _hoops_CAPRC...
	 * _hoops_HIS _hoops_RH _hoops_SAPRC _hoops_PCPH _hoops_SSCP _hoops_CPHP _hoops_IS _hoops_IPHR _hoops_CCA!
	 */
	if ((weight = _hoops_HC->weight) < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);

	if (BIT(nr->_hoops_AHP->flags, _hoops_SRPI) ||
		_hoops_GAPI(_hoops_CSRGR,_hoops_HC,weight) ||
		(BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)&&
			weight==1&&
			!BIT(dc->_hoops_PGCC.flags, _hoops_SPPGH))) {
	    HD_Std_DC_Polyline (nr, count, points);
	    return;
	}

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
	    HD_Clip_DC_Polyline (nr, count, points, 0,0,0,0,0,0,_hoops_RHGGA);
	    return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;
		bool							_hoops_IAHC = false;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}

		if (_hoops_IAHC) {
			HD_Clip_DC_Polyline (nr, count, points, 0,0,0,0,0,0,_hoops_GPHC);
			return;
		}
	}

	antialias = BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)&&
				weight==1&&BIT(dc->_hoops_PGCC.flags, _hoops_SPPGH);

	_hoops_HAPRC = (!BIT (nr->transform_rendition->flags, _hoops_CSP) ||
					  !XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_CUT_POINTS));

	_hoops_SCIGC (_hoops_CSRGR);
	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	_hoops_AIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH||antialias);
	_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));
	OGL_SET_LINE_RENDITION (_hoops_CSRGR, nr, _hoops_HC);
	ENSURE_LINE_SMOOTH(_hoops_CSRGR, antialias);

	if (count > 0) {
		DC_Point const	*_hoops_SPGGA = points;
		int					_hoops_HAHC = count;

		do {
			if (_hoops_CAPA != null) {
				_hoops_HCIGC (_hoops_CSRGR);
				_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				_hoops_IGCGC (_hoops_CSRGR);
			}
			points = _hoops_SPGGA;
			count = _hoops_HAHC;

			_hoops_GPRH(_hoops_HCCA) += count - 1;

			glBegin (GL_LINE_STRIP);
				while (count-- > 0) {
					glVertex3f (points->x + 0.5f, points->y + 0.5f, points->z);
					points++;
				}
			glEnd ();
			if (_hoops_HAPRC) {
				--points;
				_hoops_GPPRC (_hoops_CSRGR, 1);
				if (antialias)
					_hoops_AAPRC (_hoops_CSRGR, true);
				else
					_hoops_AAPRC (_hoops_CSRGR, false);
				glBegin (GL_POINTS);
					glVertex3f (points->x + 0.5f, points->y + 0.5f, points->z);
				glEnd ();
			}

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}
	else {
		DC_Point const	*_hoops_SPGGA = points;
		int					_hoops_HAHC;
		int					_hoops_RRC;

		_hoops_ICHC (count, _hoops_RRC, 2);
		_hoops_HAHC = count;

		do {
			if (_hoops_CAPA != null) {
				_hoops_HCIGC (_hoops_CSRGR);
				_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				_hoops_IGCGC (_hoops_CSRGR);
			}
			points = _hoops_SPGGA;
			count = _hoops_HAHC;

			_hoops_GPRH(_hoops_HCCA) += count;

			glBegin (GL_LINES);
				while (count-- > 0) {
					glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
					glVertex3f (points[1].x + 0.5f, points[01].y + 0.5f, points[1].z);
					points += _hoops_RRC;
				}
			glEnd ();

			if (_hoops_HAPRC) {
				points = _hoops_SPGGA;
				count = _hoops_HAHC;
				_hoops_GPPRC (_hoops_CSRGR, 1);
				if (antialias)
					_hoops_AAPRC (_hoops_CSRGR, true);
				else
					_hoops_AAPRC (_hoops_CSRGR, false);
				glBegin (GL_POINTS);
					while (count-- > 0) {
						glVertex3f (points[1].x + 0.5f, points[01].y + 0.5f, points[1].z);
						points += _hoops_RRC;
					}
				glEnd ();
			}
			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}
}


/*
 * _hoops_SRAC
 */
local void
draw_dc_gouraud_polyline (Net_Rendition const & nr,
						  int count,
						DC_Point const *points,
						RGBAS32 const *colors)
{
	Display_Context const *		dc = nr->_hoops_SRA;
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	int weight;
	_hoops_IAPA const		*_hoops_CAPA = null;
	bool antialias;
	bool _hoops_HAPRC;
	bool _hoops_CRSPH;

	_hoops_RAPRC("draw_dc_gouraud_polyline", true);

	/*
	 * _hoops_IAPRC _hoops_PAR _hoops_SHRAR _hoops_APGR _hoops_IIGR _hoops_IGAA _hoops_SPR _hoops_PIHA _hoops_SHH _hoops_GIR _hoops_HPP _hoops_CAPRC...
	 * _hoops_HIS _hoops_RH _hoops_SAPRC _hoops_PCPH _hoops_SSCP _hoops_CPHP _hoops_IS _hoops_IPHR _hoops_CCA!
	 */
	if ((weight = _hoops_HC->weight) < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);

	if (BIT(_hoops_HC->flags, _hoops_SRPI) ||
		_hoops_GAPI(_hoops_CSRGR,_hoops_HC,weight)) {
	    HD_Std_DC_Gouraud_Polyline (nr, count, points, colors);
	    return;
	}
	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
	    HD_Clip_DC_Polyline (nr, count, points, colors,0,0,0,0,0,_hoops_RHGGA|_hoops_AAIC);
	    return;
	}

	_hoops_CRSPH = BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;
		bool							_hoops_IAHC = false;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}

		if (_hoops_IAHC) {
			HD_Clip_DC_Polyline (nr, count, points, colors,0,0,0,0,0,_hoops_GPHC|_hoops_AAIC);
			return;
		}
	}

	antialias = BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)&&
				weight==1&&BIT(dc->_hoops_PGCC.flags, _hoops_SPPGH);
	_hoops_HAPRC = (!BIT (nr->transform_rendition->flags, _hoops_CSP) ||
					  !XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_CUT_POINTS));

	_hoops_SCIGC (_hoops_CSRGR);
	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	_hoops_AIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH||antialias);
	_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));
	OGL_SET_LINE_RENDITION (_hoops_CSRGR, nr, _hoops_HC);
	ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_SMOOTH);
	ENSURE_LINE_SMOOTH(_hoops_CSRGR, antialias);

	if (count > 0) {
		DC_Point const	*_hoops_SPGGA = points;
		RGBAS32 const	*_hoops_GHGGA = colors;
		int					_hoops_HAHC = count;

		do {
			if (_hoops_CAPA != null) {
				_hoops_HCIGC (_hoops_CSRGR);
				_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				_hoops_IGCGC (_hoops_CSRGR);
			}
			points = _hoops_SPGGA;
			colors = _hoops_GHGGA;
			count = _hoops_HAHC;

			_hoops_GPRH(_hoops_HCCA) += count - 1;

			glBegin (GL_LINE_STRIP);
				while (count-- > 0) {
					_hoops_PAPRC(colors[0].r, colors[0].g, colors[0].b, colors[0].a, _hoops_CRSPH);
					glVertex3f (points->x + 0.5f, points->y + 0.5f, points->z);
					points++;
					colors++;
				}
			glEnd ();
			if (_hoops_HAPRC) {
				--points;
				glBegin (GL_POINTS);
					glVertex3f (points->x + 0.5f, points->y + 0.5f, points->z);
				glEnd ();
			}
			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}
	else {
		DC_Point const	*_hoops_SPGGA = points;
		RGBAS32 const	*_hoops_GHGGA = colors;
		int					_hoops_HAHC;
		int		_hoops_RRC;

		_hoops_ICHC (count, _hoops_RRC, 2);
		_hoops_HAHC = count;

		do {
			if (_hoops_CAPA != null) {
				_hoops_HCIGC (_hoops_CSRGR);
				_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				_hoops_IGCGC (_hoops_CSRGR);
			}
			points = _hoops_SPGGA;
			colors = _hoops_GHGGA;
			count = _hoops_HAHC;

			_hoops_GPRH(_hoops_HCCA) += count;

			glBegin (GL_LINES);
				while (count-- > 0) {
					_hoops_PAPRC(colors[0].r, colors[0].g, colors[0].b, colors[0].a, _hoops_CRSPH);
					glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
					_hoops_PAPRC(colors[1].r, colors[1].g, colors[1].b, colors[0].a, _hoops_CRSPH);
					glVertex3f (points[1].x + 0.5f, points[1].y + 0.5f, points[1].z);
					points += _hoops_RRC;
					colors += _hoops_RRC;
				}
			glEnd ();
			if (_hoops_HAPRC) {
				points = _hoops_SPGGA;
				colors = _hoops_GHGGA;
				count = _hoops_HAHC;
				_hoops_GPPRC (_hoops_CSRGR, 1);
				if (antialias)
					_hoops_AAPRC (_hoops_CSRGR, true);
				else
					_hoops_AAPRC (_hoops_CSRGR, false);
				glBegin (GL_POINTS);
					while (count-- > 0) {
						_hoops_PAPRC(colors[1].r, colors[1].g, colors[1].b, colors[0].a, _hoops_CRSPH);
						glVertex3f (points[1].x + 0.5f, points[01].y + 0.5f, points[1].z);
						points += _hoops_RRC;
						colors += _hoops_RRC;
					}
				glEnd ();
			}

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}

	/* _hoops_CSPH _hoops_IRIC _hoops_PGRC _hoops_RPPRC _hoops_GH _hoops_SCGR _hoops_HAIR */
	_hoops_ICGRC(_hoops_CSRGR);
}


/*
 * _hoops_SRAC
 */
local void
draw_dc_colorized_polyline (
		Net_Rendition const & nr,
		int count,
		DC_Point const *points,
		RGBAS32 const *_hoops_GAHC,
		bool single)
{
#define _hoops_APPRC 2048
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	int weight;
	int _hoops_PGHS;
	int i;
	RGBAS32 buffer[_hoops_APPRC];
	RGBAS32 alter *colors = buffer;

	_hoops_RAPRC("draw_dc_colorized_polyline", true);

	if ((weight = _hoops_HC->weight) < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
	if (BIT(_hoops_HC->flags, _hoops_SRPI) ||
		_hoops_GAPI(_hoops_CSRGR,_hoops_HC,weight)) {
	    HD_Std_DC_Colorized_Polyline (nr, count, points, _hoops_GAHC, single);
	    return;
	}

	if (count < 0)
		_hoops_PGHS = -count/2;
	else
		_hoops_PGHS = count - 1;
	if (_hoops_PGHS*2 + 2> _hoops_APPRC)
		ALLOC_ARRAY (colors, _hoops_PGHS*2 + 2, RGBAS32);
	if (single) {
		for (i = 0; i < _hoops_PGHS; i++) {
			colors[i*2] = _hoops_GAHC[0];
			colors[i*2+1] = _hoops_GAHC[0];
		}
	}
	else {
		for (i = 0; i < _hoops_PGHS; i++) {
			colors[i*2] = _hoops_GAHC[i];
			colors[i*2+1] = _hoops_GAHC[i];
		}
	}
	draw_dc_gouraud_polyline (nr, count, points, colors);
	if (_hoops_PGHS*2 + 2> _hoops_APPRC)
		FREE_ARRAY (colors, _hoops_PGHS*2 + 2, RGBAS32);
}


/*
 * _hoops_SRAC
 */
local void
draw_dc_rectangle (Net_Rendition const & nr,
				   int left,
				   int right, int bottom, int top) {
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Int_Rectangle const &		_hoops_GPHH = _hoops_IHCR->_hoops_AGAA;

	_hoops_RAPRC("draw_dc_rectangle", true);

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC ||
	    _hoops_SIGA->pattern == FP_USER_DEFINED) {
	    HD_Std_DC_Rectangle (nr, left, right, bottom, top);
	    return;
	}

	_hoops_SCIGC (_hoops_CSRGR);

	if (_hoops_CSRGR->_hoops_RPCI != _hoops_SIGA->_hoops_CPA) {
		_hoops_CSRGR->_hoops_RPCI = _hoops_SIGA->_hoops_CPA;
		_hoops_PPPRC (_hoops_CSRGR, &_hoops_SIGA->color);
	}

	_hoops_RGIGC (_hoops_CSRGR, nr->transform_rendition->_hoops_RHPHP);
	_hoops_GGIGC (_hoops_CSRGR);

	ENSURE_SCISSOR_SET (_hoops_CSRGR, _hoops_GPHH.left, _hoops_GPHH.bottom,
						_hoops_GPHH.right - _hoops_GPHH.left + 1,
						_hoops_GPHH.top - _hoops_GPHH.bottom + 1);
	_hoops_CSRGR->_hoops_HCAC = _hoops_CCC;

	glClear (GL_COLOR_BUFFER_BIT);

	if (_hoops_SIGA->pattern != FP_SOLID) {
		_hoops_GIAC(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		_hoops_AIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
		ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
		_hoops_IPGP(_hoops_CSRGR, false);

		glEnable (GL_POLYGON_STIPPLE);
		_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
		FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->contrast_color, false);
		ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
		glRecti (left, bottom, right+1, top+1);
		glDisable (GL_POLYGON_STIPPLE);
	}
	_hoops_CSRGR->_hoops_CARGC = null;
}




/*
 * _hoops_SRAC
 */
local void
draw_dc_polytriangle (Net_Rendition const & nr,
					  int count,
				  DC_Point const * points) {
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	DC_Point const *_hoops_SPGGA = points;
	int _hoops_HAHC;
	_hoops_IAPA const		*_hoops_CAPA = null;

	_hoops_RAPRC("draw_dc_polytriangle", true);

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
	    HD_Clip_DC_Polytriangle (nr, count, points, 0,0,0,0,0,0, _hoops_RHGGA);
	    return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;
		bool							_hoops_IAHC = false;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}

		if (_hoops_IAHC) {
			HD_Clip_DC_Polytriangle (nr, count, points, 0,0,0,0,0,0,_hoops_GPHC);
			return;
		}
	}

	if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
	    HD_Span_DC_Polytriangle (nr, count, points);
	    return;
	}

	_hoops_SCIGC (_hoops_CSRGR);

	if (_hoops_CSRGR->_hoops_RPCI != _hoops_SIGA->_hoops_CPA) {
		_hoops_CSRGR->_hoops_RPCI = _hoops_SIGA->_hoops_CPA;
		_hoops_APIGC (_hoops_CSRGR, &_hoops_SIGA->color, nr);
		ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);
	}

	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	_hoops_PIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
	_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));

	if (count > 0) {
		_hoops_HAHC = count;
		do {
			if (_hoops_CAPA != null) {
				_hoops_HCIGC (_hoops_CSRGR);
				_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				_hoops_IGCGC (_hoops_CSRGR);
			}
			points = _hoops_SPGGA;
			count = _hoops_HAHC;

			_hoops_GPRH(_hoops_ACCA) += count;

			glBegin (GL_TRIANGLE_STRIP);
				while (count-- > 0) {
					glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
					points++;
				}
			glEnd ();

			if (_hoops_SIGA->pattern != FP_SOLID) {
				glEnable (GL_POLYGON_STIPPLE);
				_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
				FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->contrast_color, false);
				ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
				points = _hoops_SPGGA;
				count = _hoops_HAHC;
				glBegin (GL_TRIANGLE_STRIP);
					while (count-- > 0) {
						glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
						points++;
					}
				glEnd ();
				glDisable (GL_POLYGON_STIPPLE);
			}

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}
	else {
		int		_hoops_RRC;

		_hoops_ICHC (count, _hoops_RRC, 3);
		_hoops_HAHC = count;
		do {
			if (_hoops_CAPA != null) {
				_hoops_HCIGC (_hoops_CSRGR);
				_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				_hoops_IGCGC (_hoops_CSRGR);
			}
			points = _hoops_SPGGA;
			count = _hoops_HAHC;

			_hoops_GPRH(_hoops_ACCA) += count;

			glBegin (GL_TRIANGLES);
				while (count-- > 0) {
					glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
					glVertex3f (points[1].x + 0.5f, points[1].y + 0.5f, points[1].z);
					glVertex3f (points[2].x + 0.5f, points[2].y + 0.5f, points[2].z);
					points += _hoops_RRC;
				}
			glEnd ();

			if (_hoops_SIGA->pattern != FP_SOLID) {
				glEnable (GL_POLYGON_STIPPLE);
				_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
				FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->contrast_color, false);
				ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
				points = _hoops_SPGGA;
				count = _hoops_HAHC;
				glBegin (GL_TRIANGLES);
					while (count-- > 0) {
						glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
						glVertex3f (points[1].x + 0.5f, points[1].y + 0.5f, points[1].z);
						glVertex3f (points[2].x + 0.5f, points[2].y + 0.5f, points[2].z);
						points += _hoops_RRC;
					}
				glEnd ();
				glDisable (GL_POLYGON_STIPPLE);
			}

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}
}


/*
 * _hoops_SRAC
 */
local void
draw_dc_colorized_polytriangle (Net_Rendition const & nr,
								int count,
							DC_Point const * points,
							RGBAS32 const * colors,
							bool single) {
	Driver_Color _hoops_CPHHP;
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	DC_Point const * _hoops_SPGGA = points;
	int _hoops_HAHC;
	RGBAS32 const * _hoops_GHGGA = colors;
	int _hoops_RRC;
	_hoops_IAPA const		*_hoops_CAPA = null;

	_hoops_RAPRC("draw_dc_colorized_polytriangle", true);

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
	    HD_Clip_DC_Polytriangle (nr, count, points, colors,0,0,0,0,0, _hoops_RHGGA|_hoops_RAIC);
	    return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;
		bool							_hoops_IAHC = false;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}

		if (_hoops_IAHC) {
			HD_Clip_DC_Polytriangle (nr, count, points, colors,0,0,0,0,0, _hoops_GPHC|_hoops_RAIC);
			return;
		}
	}

	if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
	    HD_Span_DC_Colorized_Polytris (nr, count, points, colors, single);
	    return;
	}

	_hoops_SCIGC (_hoops_CSRGR);
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);


	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	_hoops_PIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
	_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));

	_hoops_ICHC (count, _hoops_RRC, 3);
	_hoops_HAHC = count;

	do {
		if (_hoops_CAPA != null) {
			_hoops_HCIGC (_hoops_CSRGR);
			_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			_hoops_IGCGC (_hoops_CSRGR);
		}
		points = _hoops_SPGGA;
		count = _hoops_HAHC;
		colors = _hoops_GHGGA;

		_hoops_GPRH(_hoops_ACCA) += count;

		glBegin (GL_TRIANGLES);
			while (count-- > 0) {
				_hoops_CPHHP = *colors;
				_hoops_APIGC (_hoops_CSRGR, &_hoops_CPHHP, nr);
				glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
				glVertex3f (points[1].x + 0.5f, points[1].y + 0.5f, points[1].z);
				glVertex3f (points[2].x + 0.5f, points[2].y + 0.5f, points[2].z);
				points += _hoops_RRC;
				if (!single)
					colors++;
			}
		glEnd ();

		if (_hoops_SIGA->pattern != FP_SOLID) {
			glEnable (GL_POLYGON_STIPPLE);
			_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
			FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->contrast_color, false);
			ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
			points = _hoops_SPGGA;
			count = _hoops_HAHC;

			_hoops_GPRH(_hoops_ACCA) += count;

			glBegin (GL_TRIANGLES);
				while (count-- > 0) {
					glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
					glVertex3f (points[1].x + 0.5f, points[1].y + 0.5f, points[1].z);
					glVertex3f (points[2].x + 0.5f, points[2].y + 0.5f, points[2].z);
					points += _hoops_RRC;
				}
			glEnd ();
			glDisable (GL_POLYGON_STIPPLE);
		}

		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);
}


/*
 * _hoops_SRAC
 */
local void
draw_dc_gouraud_polytriangle (Net_Rendition const & nr,
							  int count,
						  DC_Point const * points,
						  RGBAS32 const * colors)
{
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	DC_Point const *_hoops_SPGGA = points;
	int _hoops_HAHC;
	RGBAS32 const * _hoops_GHGGA = colors;
	_hoops_IAPA const		*_hoops_CAPA = null;
	bool _hoops_CRSPH;

	_hoops_CRSPH = BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI);

	_hoops_RAPRC("draw_dc_gouraud_polytriangle", true);

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
	    HD_Clip_DC_Polytriangle (nr, count, points, colors,0,0,0,0,0, _hoops_RHGGA|_hoops_AAIC);
	    return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;
		bool							_hoops_IAHC = false;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}

		if (_hoops_IAHC) {
			HD_Clip_DC_Polytriangle (nr, count, points, colors,0,0,0,0,0, _hoops_GPHC|_hoops_AAIC);
			return;
		}
	}

	if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
	    HD_Span_DC_Gouraud_Polytris (nr, count, points, colors);
	    return;
	}

	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;

	_hoops_SCIGC (_hoops_CSRGR);
	ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_SMOOTH);
	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	_hoops_PIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
	_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));

	if (count > 0) {
		_hoops_HAHC = count;
		do {
			if (_hoops_CAPA != null) {
				_hoops_HCIGC (_hoops_CSRGR);
				_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				_hoops_IGCGC (_hoops_CSRGR);
			}
			points = _hoops_SPGGA;
			count = _hoops_HAHC;
			colors = _hoops_GHGGA;

			_hoops_GPRH(_hoops_ACCA) += count;

			glBegin (GL_TRIANGLE_STRIP);
				while (count-- > 0) {
					_hoops_PAPRC (colors[0].r, colors[0].g, colors[0].b, colors[0].a, _hoops_CRSPH);
					glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
					points++;
					colors++;
				}
			glEnd ();

			if (_hoops_SIGA->pattern != FP_SOLID) {
				glEnable (GL_POLYGON_STIPPLE);
				_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
				FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->contrast_color, _hoops_CRSPH);
				ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
				points = _hoops_SPGGA;
				count = _hoops_HAHC;

				_hoops_GPRH(_hoops_ACCA) += count;

				glBegin (GL_TRIANGLE_STRIP);
					while (count-- > 0) {
						glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
						points++;
					}
				glEnd ();
				glDisable (GL_POLYGON_STIPPLE);
			}

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}
	else {
		int		_hoops_RRC;

		_hoops_ICHC (count, _hoops_RRC, 3);
		_hoops_HAHC = count;

		/* _hoops_GA'_hoops_RA _hoops_IAIC _hoops_RH _hoops_RPR _hoops_GGR _hoops_RGR _hoops_RPGP.  _hoops_PS _hoops_HS _hoops_IS _hoops_PGI _hoops_SHR _hoops_SGH _hoops_GPHA
		   _hoops_SIRGR _hoops_PAR _hoops_SHR _hoops_SGH _hoops_RPGH/_hoops_RSGR _hoops_GGR _hoops_AGR _hoops_HAR _hoops_IS _hoops_ARPR _hoops_HPPRC. */
		if (_hoops_CSRGR->_hoops_PRHGC) {
			_hoops_AIGH *_hoops_IPPRC;
			int i;

			ENSURE_COLOR_ARRAY_ON(_hoops_CSRGR);
			_hoops_CPPRC(_hoops_CSRGR);
			glVertexPointer(3, GL_FLOAT, 0, points);
			/* _hoops_RAPSR _hoops_SPPRC _hoops_HII _hoops_GHARR-_hoops_SASI _hoops_GCRSP _hoops_IS _hoops_PHIAH-_hoops_HIAGR _hoops_GCAGI */
			/* _hoops_IPCP _hoops_HSPR _hoops_RPGP _hoops_IGIPR _hoops_GHPRC _hoops_HRGR _hoops_GGHSP(_hoops_HGGPA).
			 * _hoops_CGP _hoops_SGS _hoops_SGIPR _hoops_SHPH, _hoops_RGR _hoops_RPGP _hoops_GHCA _hoops_RRP _hoops_IS _hoops_GACHR (_hoops_RPR*3) _hoops_PAR _hoops_AGIIP _hoops_PRGI (_hoops_RPR*4) */
			if (count > OGL_SCRATCH_SPACE_SIZE)
				ALLOC_ARRAY (_hoops_IPPRC, count*3, _hoops_AIGH);
			else {
				if (!_hoops_CSRGR->_hoops_RISGC)
					ALLOC_ARRAY(_hoops_CSRGR->_hoops_RISGC, OGL_SCRATCH_SPACE_SIZE, RGB);
				_hoops_IPPRC = (_hoops_AIGH *) _hoops_CSRGR->_hoops_RISGC;
			}
			if (_hoops_CRSPH) {
				unsigned char _hoops_HHGA;
				for (i = 0; i < count*3; i++) {
					_hoops_IPPRC[i] = colors[i];
					_hoops_HHGA = _hoops_IRASP (colors[i].r, colors[i].g, colors[i].b);
					_hoops_IPPRC[i].r = _hoops_HHGA;
					_hoops_IPPRC[i].g = _hoops_HHGA;
					_hoops_IPPRC[i].b = _hoops_HHGA;
				}
			}
			else {
				for (i = 0; i < count*3; i++)
					_hoops_IPPRC[i] = colors[i];
			}
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, _hoops_IPPRC);

			do {
				if (_hoops_CAPA != null) {
					_hoops_HCIGC (_hoops_CSRGR);
					_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
					_hoops_IGCGC (_hoops_CSRGR);
				}

				_hoops_GPRH(_hoops_ACCA) += count;
				glDrawArrays(GL_TRIANGLES,0,count*3);

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);

			if (_hoops_IPPRC != (_hoops_AIGH *) _hoops_CSRGR->_hoops_RISGC)
				FREE_ARRAY (_hoops_IPPRC, count*3, _hoops_AIGH);

			_hoops_RHPRC(_hoops_CSRGR);
			_hoops_AHPRC(_hoops_CSRGR);
		}
		else {
			do {
				if (_hoops_CAPA != null) {
					_hoops_HCIGC (_hoops_CSRGR);
					_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
					_hoops_IGCGC (_hoops_CSRGR);
				}
				points = _hoops_SPGGA;
				count = _hoops_HAHC;
				colors = _hoops_GHGGA;

				_hoops_GPRH(_hoops_ACCA) += count;

				glBegin (GL_TRIANGLES);
					while (count-- > 0) {
						_hoops_PAPRC(colors[0].r, colors[0].g, colors[0].b, colors[0].a, _hoops_CRSPH);
						glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
						_hoops_PAPRC(colors[1].r, colors[1].g, colors[1].b, colors[1].a, _hoops_CRSPH);
						glVertex3f (points[1].x + 0.5f, points[1].y + 0.5f, points[1].z);
						_hoops_PAPRC(colors[2].r, colors[2].g, colors[2].b, colors[2].a, _hoops_CRSPH);
						glVertex3f (points[2].x + 0.5f, points[2].y + 0.5f, points[2].z);
						points += _hoops_RRC;
						colors += _hoops_RRC;
					}
				glEnd ();

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);
		}

		do {
			if (_hoops_CAPA != null) {
				_hoops_HCIGC (_hoops_CSRGR);
				_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				_hoops_IGCGC (_hoops_CSRGR);
			}

			if (_hoops_SIGA->pattern != FP_SOLID) {
				glEnable (GL_POLYGON_STIPPLE);
				_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
				FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->contrast_color, _hoops_CRSPH);
				ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
				points = _hoops_SPGGA;
				count = _hoops_HAHC;
				_hoops_GPRH(_hoops_ACCA) += count;
				glBegin (GL_TRIANGLES);
					while (count-- > 0) {
						glVertex3f (points[0].x + 0.5f, points[0].y + 0.5f, points[0].z);
						glVertex3f (points[1].x + 0.5f, points[1].y + 0.5f, points[1].z);
						glVertex3f (points[2].x + 0.5f, points[2].y + 0.5f, points[2].z);
						points += _hoops_RRC;
					}
				glEnd ();
				glDisable (GL_POLYGON_STIPPLE);
			}

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}

	/* _hoops_CSPH _hoops_IRIC _hoops_PHPRC _hoops_RPPRC _hoops_GH _hoops_SCGR _hoops_HAIR */
	_hoops_ICGRC(_hoops_CSRGR);
}


local bool _hoops_HHPRC (
	Net_Rendition const & nr,
	bool alter *_hoops_IHPRC,
	bool alter *_hoops_CHPRC,
	bool alter *_hoops_SHPRC)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	int _hoops_RASP = 0;
	int _hoops_GPIAR = 0;
	int i, j;

	/* _hoops_SRS _hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_CPHP _hoops_SR _hoops_PAH _hoops_PRGI _hoops_RGHH _hoops_CCA _hoops_ICCI */
	if (_hoops_SIGA->_hoops_PGPH != null && _hoops_SIGA->_hoops_PGPH->stipple)
		_hoops_RASP = _hoops_SIGA->_hoops_PGPH->stipple;
	else if (_hoops_SIGA->_hoops_PGPH != null &&
			 _hoops_SIGA->_hoops_PGPH->height <= 32 && _hoops_SIGA->_hoops_PGPH->width <= 32 &&
			 _hoops_RIII(_hoops_SIGA->_hoops_PGPH->width) == _hoops_SIGA->_hoops_PGPH->width &&
			 _hoops_RIII(_hoops_SIGA->_hoops_PGPH->height) == _hoops_SIGA->_hoops_PGPH->height)
		_hoops_GPIAR = 1;
	else
		return false;

	/* _hoops_ARPR _hoops_RH _hoops_GIPRC _hoops_HSGP */
	if (_hoops_RASP) {
		*_hoops_IHPRC = true;
		*_hoops_CHPRC = false;
		*_hoops_SHPRC = true;
		if (_hoops_CSRGR->_hoops_AGAGC != -_hoops_RASP) {
			int _hoops_PHPSR;
			const unsigned char *pattern;

			_hoops_CSRGR->_hoops_AGAGC = -_hoops_RASP;
			_hoops_PHPSR = (int)(64 - _hoops_RASP);
			pattern = _hoops_HRPH[_hoops_PHPSR];
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x8 _hoops_IS 8x32 */
			for (i = 0; i < 8; i++) {
				_hoops_CSRGR->_hoops_RIPRC[i] = pattern[i];
				_hoops_CSRGR->_hoops_RIPRC[i] |= _hoops_CSRGR->_hoops_RIPRC[i] << 8;
				_hoops_CSRGR->_hoops_RIPRC[i] |= _hoops_CSRGR->_hoops_RIPRC[i] << 16;
			}
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x32 _hoops_IS 32x32 */
			_hoops_AIGA (_hoops_CSRGR->_hoops_RIPRC,  8, unsigned int, _hoops_CSRGR->_hoops_RIPRC+8);
			_hoops_AIGA (_hoops_CSRGR->_hoops_RIPRC, 16, unsigned int, _hoops_CSRGR->_hoops_RIPRC+16);
		}
	}
	else if (_hoops_GPIAR) {
		if (_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP == UPAT_NO_FACE)
			*_hoops_IHPRC = false;
		else
			*_hoops_IHPRC = true;
		if (_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP == UPAT_NO_CONTRAST)
			*_hoops_CHPRC = false;
		else
			*_hoops_CHPRC = true;
		*_hoops_SHPRC = false;

		if (_hoops_CSRGR->_hoops_AGAGC != _hoops_SIGA->_hoops_CPA) {
			_hoops_CSRGR->_hoops_AGAGC = _hoops_SIGA->_hoops_CPA;
			for (i = 0; i < _hoops_SIGA->_hoops_PGPH->height; i++) {
				int		index = _hoops_SIGA->_hoops_PGPH->height-1 - i;

				_hoops_CSRGR->_hoops_RIPRC[index] = 0;
				for (j = 0; j < _hoops_SIGA->_hoops_PGPH->width; j++) {
					if (_hoops_SIGA->_hoops_PGPH->pattern[i*_hoops_SIGA->_hoops_PGPH->width + j] == 0)
						_hoops_CSRGR->_hoops_RIPRC[index] |= 1 << (_hoops_SIGA->_hoops_PGPH->width-1 - j);
				}
				while (j<32) {
					_hoops_CSRGR->_hoops_RIPRC[index] |= _hoops_CSRGR->_hoops_RIPRC[index]<<j;
					j <<= 1;
				}
			}
			while (i<32) {
				_hoops_AIGA (_hoops_CSRGR->_hoops_RIPRC, i, unsigned int, _hoops_CSRGR->_hoops_RIPRC+i);
				i <<= 1;
			}
			if (_hoops_SIGA->_hoops_PGPH->_hoops_ACHHP != UPAT_NO_CONTRAST)
				for (i = 0; i < 32; i++)
					_hoops_CSRGR->_hoops_RIPRC[i] ^= ~0UL;
		}
	}
	return true;
}


/*
 * _hoops_SRAC
 */
local void
draw_dc_face (Net_Rendition const & nr,
			  int count, DC_Point const * points)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	DC_Point const *end = points + count;
	DC_Point const *_hoops_SPGGA = points;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	_hoops_IAPA const *_hoops_CAPA = null;
	bool _hoops_CHRRC[2] = { true, false };
	bool _hoops_RASP = false;
	bool	_hoops_IAHC = false;
	int i;

	_hoops_RAPRC("draw_dc_face", true);

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
		HD_Clip_DC_Face (nr, count, points, 0, _hoops_RHGGA);
		return;
	}
	if (_hoops_SIGA->pattern != FP_SOLID) {
		if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
			if (!_hoops_HHPRC (nr, &_hoops_CHRRC[0], &_hoops_CHRRC[1], &_hoops_RASP))
				_hoops_IAHC = true;
		}
		else
			_hoops_CHRRC[1] = true; /* _hoops_SR _hoops_RRP _hoops_IRS _hoops_HSP _hoops_CGARA _hoops_RIH */
	}

	if (!_hoops_IAHC && BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
	}
	if (_hoops_IAHC) {
		HD_Std_DC_Face (nr, count, points);
		return;
	}

	_hoops_SCIGC (_hoops_CSRGR);
	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	_hoops_PIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH && !_hoops_RASP);
	_hoops_IPGP(_hoops_CSRGR, BIT(_hoops_IHCR->flags, _hoops_CASP));

	_hoops_GPRH(_hoops_PHRGH) += count;

	for (i = 0; i < 2; i++) {
		if (!_hoops_CHRRC[i])
			continue;

		if (i == 0) {
			if (_hoops_CSRGR->_hoops_RPCI != _hoops_SIGA->_hoops_CPA) {
				_hoops_CSRGR->_hoops_RPCI = _hoops_SIGA->_hoops_CPA;
				_hoops_APIGC (_hoops_CSRGR, &_hoops_SIGA->color, nr);
				ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);
			}
			if (_hoops_SIGA->pattern != FP_SOLID && !_hoops_CHRRC[1]) {
				/* _hoops_RH _hoops_CGARA _hoops_RIH _hoops_HRGR _hoops_AGSI, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_GHAA _hoops_RH _hoops_GIPRC _hoops_ARI */
				ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
				glEnable (GL_POLYGON_STIPPLE);
			}
		}
		else {
			ASSERT (i == 1);
			_hoops_APIGC (_hoops_CSRGR, &_hoops_SIGA->contrast_color, nr);
			_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
			ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
			glEnable (GL_POLYGON_STIPPLE);
		}

		if (BIT (_hoops_IHCR->heuristics, _hoops_CGCS)) {
			struct concave_tri _hoops_SIPH;

			_hoops_SIPH.points.dc = points;
			_hoops_SIPH.pattern = _hoops_SIGA->pattern;
			_hoops_SIPH._hoops_CSRGR = _hoops_CSRGR;
			_hoops_SIPH.color = _hoops_SIGA->color;
			_hoops_SIPH.contrast_color = _hoops_SIGA->contrast_color;
			_hoops_SIPH._hoops_PSPH = callback_draw_triangle;
			_hoops_SIPH._hoops_RPPH = true;
			_hoops_SIPH._hoops_CAIGC = false;

			do {
				if (_hoops_CAPA != null) {
					_hoops_HCIGC (_hoops_CSRGR);
					_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
					_hoops_IGCGC (_hoops_CSRGR);
				}
				draw_concave_face (nr, count, &_hoops_SIPH);
				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);
		}
		else {
			/*_hoops_AIPRC*/
			do {
				if (_hoops_CAPA != null) {
					_hoops_HCIGC (_hoops_CSRGR);
					_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
					_hoops_IGCGC (_hoops_CSRGR);
				}
				points = _hoops_SPGGA;

				glBegin (GL_POLYGON);
				do {
					glVertex3f (points->x + 0.5f, points->y + 0.5f, points->z);
				} _hoops_RGGA (++points == end);
				glEnd ();

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);
		}
	}
	if (_hoops_SIGA->pattern != FP_SOLID)
		glDisable (GL_POLYGON_STIPPLE);
}


/*
 * _hoops_SRAC
 */
local void
draw_dc_colorized_face (Net_Rendition const & nr,
						int count,
						DC_Point const * points,
						RGBAS32 const * color) {
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	DC_Point const *end = points + count;
	DC_Point const *_hoops_SPGGA = points;
	int pattern = _hoops_SIGA->pattern;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	Driver_Color _hoops_CPHHP;
	_hoops_IAPA const		*_hoops_CAPA = null;
	bool _hoops_CRSPH;

	_hoops_RAPRC("draw_dc_colorized_face", true);

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
		HD_Clip_DC_Face (nr, count, points, color, _hoops_RHGGA);
		return;
	}
	if (pattern == FP_USER_DEFINED) {
		HD_Std_DC_Colorized_Face (nr, count, points, color);
		return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;
		bool							_hoops_IAHC = false;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}

		if (_hoops_IAHC) {
			HD_Std_DC_Colorized_Face (nr, count, points, color);
			return;
		}
	}

	_hoops_CRSPH = BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI);

	_hoops_SCIGC (_hoops_CSRGR);
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_CPHHP = *color;

	_hoops_APIGC (_hoops_CSRGR, &_hoops_CPHHP, nr);
	ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);


	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	_hoops_PIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
	_hoops_IPGP(_hoops_CSRGR, BIT(_hoops_IHCR->flags, _hoops_CASP));

	_hoops_GPRH(_hoops_PHRGH) += count;

	if (BIT (_hoops_IHCR->heuristics, _hoops_CGCS)) {
		struct concave_tri _hoops_SIPH;

		_hoops_SIPH.points.dc = points;
		_hoops_SIPH.pattern = pattern;
		_hoops_SIPH._hoops_CSRGR = _hoops_CSRGR;
		_hoops_SIPH.color = _hoops_CPHHP;
		_hoops_SIPH.contrast_color = _hoops_SIGA->contrast_color;
		_hoops_SIPH._hoops_PSPH = callback_draw_triangle;
		_hoops_SIPH._hoops_RPPH = true;
		_hoops_SIPH._hoops_CAIGC = false;

		do {
			if (_hoops_CAPA != null) {
				_hoops_HCIGC (_hoops_CSRGR);
				_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				_hoops_IGCGC (_hoops_CSRGR);
			}
			draw_concave_face (nr, count, &_hoops_SIPH);
			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}
	else {
		_hoops_IAPA const		*_hoops_PIPRC = _hoops_CAPA;

		do {
			if (_hoops_CAPA != null) {
				_hoops_HCIGC (_hoops_CSRGR);
				_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				_hoops_IGCGC (_hoops_CSRGR);
			}
			points = _hoops_SPGGA;

			glBegin (GL_POLYGON);
			do {
				glVertex3f (points->x + 0.5f, points->y + 0.5f, points->z);
			} _hoops_RGGA (++points == end);
			glEnd ();

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);

		if (pattern != FP_SOLID) {
			glEnable (GL_POLYGON_STIPPLE);
			_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
			FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->contrast_color, _hoops_CRSPH);
			ENSURE_FACE_PATTERN (_hoops_CSRGR, pattern);

			_hoops_CAPA = _hoops_PIPRC;
			do {
				if (_hoops_CAPA != null) {
					_hoops_HCIGC (_hoops_CSRGR);
					_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
					_hoops_IGCGC (_hoops_CSRGR);
				}
				points = _hoops_SPGGA;

				glBegin (GL_POLYGON);
				do {
					glVertex3f (points->x + 0.5f, points->y + 0.5f, points->z);
				} _hoops_RGGA (++points == end);
				glEnd ();

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);

			glDisable (GL_POLYGON_STIPPLE);
		}
	}
}


/*
 * _hoops_SRAC
 */
local void
draw_dc_rgb32_rasters (Net_Rendition const & nr,
					   DC_Point const * start,
					   DC_Point const * end,
					   int row_bytes,
					   RGBAS32 const * _hoops_GAAC) {
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	int _hoops_RAAC;
	int width = (int)end->x - (int)start->x + 1;
	GLsizei height = (GLsizei)start->y - (GLsizei)end->y + 1;
	int dx;
	float _hoops_AAAC;
	DC_Point _hoops_PAAC;
	RGBAS32 const *_hoops_HAAC;
	RGBAS32 const *_hoops_IAAC;
	_hoops_IAPA const		*_hoops_CAPA = null;
	RGBAS32 const * _hoops_HIPRC = _hoops_GAAC;
	bool _hoops_CRSPH;

	_hoops_RAPRC("draw_dc_rgb32_rasters", true);

	_hoops_CRSPH = BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI);

	ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);
	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, false);
	_hoops_AIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
	_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
		}
		else
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
	}


	if (0 == row_bytes)
		row_bytes = width * sizeof (RGBAS32);

	do {

		_hoops_GPRH(rasters) += width*height;

		if (_hoops_CAPA != null) {
			_hoops_HCIGC (_hoops_CSRGR);
			_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			_hoops_IGCGC (_hoops_CSRGR);
		}
		_hoops_GAAC = _hoops_HIPRC;
		_hoops_RAAC = (int)start->y;
		dx = (int)end->x - (int)start->x;

		if (XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_TRANSPARENT_POINT)) {
			if (dx > 0)
				_hoops_AAAC = (end->z - start->z) / (float)dx;
			else
				_hoops_AAAC = 0.0f;

			glBegin (GL_LINES);
			while (_hoops_RAAC >= (int)end->y) {
				_hoops_IAAC = _hoops_GAAC;
				_hoops_HAAC = _hoops_IAAC + dx;
				_hoops_PAAC.x = start->x + 0.5f;
				_hoops_PAAC.y = _hoops_RAAC + 0.5f;
				_hoops_PAAC.z = start->z;
				do {
					_hoops_PAPRC(_hoops_IAAC->r, _hoops_IAAC->g, _hoops_IAAC->b, _hoops_IAAC->a, _hoops_CRSPH);
					glVertex3fv ((GLfloat const *) &_hoops_PAAC);
					_hoops_PAAC.x++;
					glVertex3fv ((GLfloat const *) &_hoops_PAAC);
					_hoops_PAAC.z += _hoops_AAAC;
				} _hoops_RGGA (_hoops_IAAC++ == _hoops_HAAC);
				_hoops_GAAC = (RGBAS32 *) ((unsigned char *) _hoops_GAAC + row_bytes);
				_hoops_RAAC--;
			}
			glEnd ();
		}
		else if (dx == 0) {
			glBegin (GL_POINTS);
			while (_hoops_RAAC >= (int)end->y) {
				_hoops_PAPRC(_hoops_GAAC->r, _hoops_GAAC->g, _hoops_GAAC->b, _hoops_GAAC->a, _hoops_CRSPH);
				glVertex3f(start->x + 0.5f, _hoops_RAAC + 0.5f, start->z);

				_hoops_GAAC = (RGBAS32 *) ((unsigned char *) _hoops_GAAC + row_bytes);
				_hoops_RAAC--;
			}
			glEnd ();
		}
		else {
			_hoops_AAAC = (end->z - start->z) / (float)dx;

			glBegin (GL_POINTS);

			while (_hoops_RAAC >= (int)end->y) {
				_hoops_IAAC = _hoops_GAAC;
				_hoops_HAAC = _hoops_IAAC + dx;
				_hoops_PAAC.x = start->x + 0.5f;
				_hoops_PAAC.y = _hoops_RAAC + 0.5f;
				_hoops_PAAC.z = start->z;

				do {
					_hoops_PAPRC(_hoops_IAAC->r, _hoops_IAAC->g, _hoops_IAAC->b, _hoops_IAAC->a, _hoops_CRSPH);
					glVertex3fv ((GLfloat const *) &_hoops_PAAC);
					_hoops_PAAC.z += _hoops_AAAC;
					_hoops_PAAC.x++;
				} _hoops_RGGA (_hoops_IAAC++ == _hoops_HAAC);

				_hoops_GAAC = (RGBAS32 *) ((unsigned char *) _hoops_GAAC + row_bytes);
				_hoops_RAAC--;
			}

			glEnd ();
		}
		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);

	/* _hoops_AHRH _hoops_RPPRC _hoops_GH _hoops_SCGR _hoops_HAIR */
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_ICGRC(_hoops_CSRGR);
}



/*****************************************************************************
 *****************************************************************************
						3D_hoops_IIPRC
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_SRAC
 */
local void
draw_3d_image(
	Net_Rendition const &		nr,
	Image const *				image) {
	OGLData alter *				_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_ISHHP const &	_hoops_CSHHP = nr->_hoops_ASIR;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Point alter					points[4];
	float						_hoops_IACC, _hoops_CACC, _hoops_SACC, _hoops_GPCC, u, v;
	int							width, height;
	GLfloat alter				_hoops_PHRGC[4];
	_hoops_RCR alter *				txr = null;
	GLuint						id;
	_hoops_IAPA const *	_hoops_CAPA = null;

	_hoops_RAPRC("draw_3d_image", true);

	if ((image->format == Image_MAPPED_8 || image->format == Image_MAPPED_16) &&
		image->_hoops_RGARP >= _hoops_CSHHP->_hoops_PSIR->length) {
		HE_WARNING (HEC_IMAGE, HES_OUT_OF_RANGE_COLOR_MAP, Sprintf_DD (null,
			"Mapped image max of %d may exceed color map max of %d - not drawn",
			(int)image->_hoops_RGARP, (int)_hoops_CSHHP->_hoops_PSIR->length - 1));
		return;
	}

	if (!HD_Calc_Image_Position_And_Size(nr, image, &width, &height, &_hoops_IACC, &_hoops_CACC, &_hoops_SACC)) return;

	if (BIT(image->flags, _hoops_SHCC) || BIT(image->flags, _hoops_GICC) ||
		nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR != 1.0f ) {

	    HD_Std_3D_Image(nr, image);
	    return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;
		bool							_hoops_IAHC = false;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}

		if (_hoops_IAHC) {
			HD_Std_3D_Image(nr, image);
			return;
		}
	}

	txr = HI_Clone_Texture(0);
	txr->_hoops_SCR |= _hoops_RCRH;
	txr->_hoops_CGA = _hoops_ASCC;
	if (width < image->width>>1 || height < image->height>>1) {
		txr->_hoops_RARH = _hoops_AARH;
		txr->_hoops_PSCC = _hoops_HSCC;
	}
	else if (width == image->width && height == image->height)
		txr->_hoops_PSCC = _hoops_HSCC;

	txr->image = (Image alter*)image;
	_hoops_PRRH(txr->image);

	ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);
	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, false);
	_hoops_PIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
	_hoops_IPGP(_hoops_CSRGR, false);
	ENSURE_CULLING_OFF (_hoops_CSRGR);

	if (nr->_hoops_ARA->image._hoops_RSCC.red != 1.0f ||
		nr->_hoops_ARA->image._hoops_RSCC.green != 1.0f ||
		nr->_hoops_ARA->image._hoops_RSCC.blue != 1.0f) {

		_hoops_PHRGC[0] = nr->_hoops_ARA->image._hoops_RSCC.red;
		_hoops_PHRGC[1] = nr->_hoops_ARA->image._hoops_RSCC.green;
		_hoops_PHRGC[2] = nr->_hoops_ARA->image._hoops_RSCC.blue;
		_hoops_PHRGC[3] = 1.0f;

		if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI)) {
			float _hoops_PHCHR = _hoops_IRASP (_hoops_PHRGC[0], _hoops_PHRGC[1], _hoops_PHRGC[2]);
			_hoops_PHRGC[0] = _hoops_PHRGC[1] = _hoops_PHRGC[2] = _hoops_PHCHR;
		}
	}
	else {
		_hoops_PHRGC[0]=_hoops_PHRGC[1]=_hoops_PHRGC[2]=_hoops_PHRGC[3]=1.0f;
	}

	glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, _hoops_PHRGC);
	_hoops_CCCGC (_hoops_CSRGR, GL_FRONT);
	FORCE_COLOR_4F(_hoops_PHRGC[0], _hoops_PHRGC[1], _hoops_PHRGC[2], _hoops_PHRGC[3], false);

	if (BIT (image->flags, _hoops_GRRH)) {
		/* _hoops_IPCP _hoops_AIRI _hoops_HIGR **_hoops_ISCC** _hoops_RH _hoops_IAAI _hoops_IPS _hoops_IIGR _hoops_RH _hoops_CSCR _hoops_PIH.
		   _hoops_HGPP _hoops_RRRH _hoops_CHR _hoops_CSCC _hoops_IS _hoops_IRS _hoops_SASI _hoops_RHPP, _hoops_HIH _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_SSCC
		   _hoops_RH _hoops_GGSC _hoops_SR'_hoops_ASAR _hoops_IPIH _hoops_ASCA _hoops_CCA (_hoops_GGR _hoops_RGSC, _hoops_SCH _hoops_PAHH _hoops_GPGH'_hoops_RA).
		   _hoops_PSPC, _hoops_RH _hoops_ASGH _hoops_PSSGC _hoops_HGRH _hoops_ASSP'_hoops_RA _hoops_GHAA _hoops_ARI. */
		_hoops_GACR alter *dl;
		OGL_Display_List alter *odl = 0;

		dl = image->_hoops_GAHA;
		if (dl)
			odl = (OGL_Display_List alter *) dl->list;
		if (!odl) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
				   "GPU copy of image unexpectedly lost by opengl driver.");
			return;
		}
		id = odl->item.texture.id;
		_hoops_GSAC (_hoops_CSRGR, nr, null, _hoops_GPGRC, _hoops_HSSGC, id, 0);
		u = v = 1;
	}
	else {
		id = OGL_DEFINE_TEXTURE (_hoops_CSRGR, nr, txr, _hoops_HSSGC,0);
		_hoops_GSAC (_hoops_CSRGR, nr, txr, _hoops_GPGRC, _hoops_HSSGC, id,0);

		if (!BIT(txr->_hoops_RHGH->flags, _hoops_PCRH)) {
			u=1.0f;
			v=1.0f;
		}
		else {
			if (BIT(txr->_hoops_RHGH->flags, _hoops_AGSC)) {
				u = (float)image->width/(float)(txr->_hoops_RHGH->width -2);
				v = (float)image->height/(float)(txr->_hoops_RHGH->height -2);
			}
			else {
				u = (float)image->width/(float)(txr->_hoops_RHGH->width);
				v = (float)image->height/(float)(txr->_hoops_RHGH->height);
			}
		}
	}
	_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, 0);
	ENSURE_TEXTURE_ENV_MODE (_hoops_CSRGR, GL_MODULATE,0);

	if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC))
		_hoops_GPCC = _hoops_IGSC (_hoops_SACC, _hoops_IHCR);
	else
		_hoops_GPCC = 0.0f;

	points[0].x = ((int)(_hoops_IACC+ 0.5f - width  * 0.5f));
	points[0].y = ((int)(_hoops_CACC+ 0.5f - height * 0.5f));
	points[0].z = _hoops_GPCC;

	points[1].x = points[0].x ;
	points[1].y = points[0].y + height;
	points[1].z = _hoops_GPCC;

	points[2].x = points[0].x + width;
	points[2].y = points[0].y + height;
	points[2].z = _hoops_GPCC;

	points[3].x = points[0].x + width;
	points[3].y = points[0].y;
	points[3].z = _hoops_GPCC;

	do {
		if (_hoops_CAPA != null) {
			_hoops_HCIGC (_hoops_CSRGR);
			_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			_hoops_IGCGC (_hoops_CSRGR);
		}

		_hoops_GPRH(_hoops_ACCA) += 2;

		glBegin (GL_TRIANGLE_STRIP);
			glTexCoord2f (0.0f, 0.0f);
			glVertex3f (points[0].x , points[0].y , points[0].z);
			glTexCoord2f (0.0f, v);
			glVertex3f (points[1].x , points[1].y , points[1].z);
			glTexCoord2f (u, 0.0f);
			glVertex3f (points[3].x , points[3].y , points[3].z);
			glTexCoord2f (u, v);
			glVertex3f (points[2].x , points[2].y , points[2].z);
		glEnd ();

		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);

	_hoops_AARRC (_hoops_CSRGR,0);
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_ICGRC(_hoops_CSRGR);
	_hoops_HPRH(txr);
}

local bool
_hoops_CCIC(
				Net_Rendition const &		nr,
				int							count,
				DC_Point const *			points,
				_hoops_RSSH const *			params,
				Integer32					param_width)
{
	OGLData alter *					_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	Display_Context const *			dc = nr->_hoops_SRA;
	GLfloat alter					_hoops_PHRGC[4];
	_hoops_RCR alter *					txr = null;
	_hoops_HHA const &		matr = nr->_hoops_IHA->_hoops_CHA;
	GLuint							id;
	_hoops_IAPA const *		_hoops_CAPA = null;
	const int						_hoops_SCIC [6]	= {0, 1, 2, 3, 4, 5};
	const int						_hoops_GSIC [6]	= {0, 1, 2, 2, 1, 3};
	const int *						indices;
	int								i;
	int								_hoops_RSIC;
	_hoops_RSSH 						_hoops_PSIC[18];
	float							u, v;

	UNREFERENCED(dc);

	if (matr->_hoops_SCA == null ||
		matr->_hoops_SCA->next != null)
		return false;

	if (!BIT(matr->_hoops_SCA->texture->_hoops_SCR, _hoops_RCRH))
		return false;

	if (count==4)
		indices = _hoops_GSIC;
	else if (count == -6)
		indices = _hoops_SCIC;
	else
		return false;

	if (BIT (_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_CIPRC) &&
		BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GSRC) &&
		(matr->_hoops_SCA->texture->image->width > _hoops_CSRGR->_hoops_HPHGC ||
		matr->_hoops_SCA->texture->image->height > _hoops_CSRGR->_hoops_HPHGC)) {
		return false;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				return false;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				return false;
		}
	}

	txr = matr->_hoops_SCA->texture;
	_hoops_PRRH(txr);
	id = OGL_DEFINE_TEXTURE (_hoops_CSRGR, nr, txr, _hoops_HSSGC,0);

	if (id == 0) {
		_hoops_HPRH(txr);
		return false;
	}

	ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);
	_hoops_GIAC(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, false);
	_hoops_PIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
	_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));
	ENSURE_CULLING_OFF (_hoops_CSRGR);

	_hoops_PHRGC[3] = matr->_hoops_IRIR;
	if (BIT(matr->_hoops_SCA->flags, _hoops_PRA)
		|| BIT(matr->_hoops_SCA->flags, _hoops_PPIR)) {

		_hoops_PHRGC[0] = matr->_hoops_CSHR.red;
		_hoops_PHRGC[1] = matr->_hoops_CSHR.green;
		_hoops_PHRGC[2] = matr->_hoops_CSHR.blue;

		if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI)) {
			float _hoops_PHCHR = _hoops_IRASP (_hoops_PHRGC[0], _hoops_PHRGC[1], _hoops_PHRGC[2]);
			_hoops_PHRGC[0] = _hoops_PHRGC[1] = _hoops_PHRGC[2] = _hoops_PHCHR;
		}
	}
	else {
		_hoops_PHRGC[0]=_hoops_PHRGC[1]=_hoops_PHRGC[2]=1.0f;
	}

	_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
	_hoops_PHRGC[0] *= _hoops_RRA->image._hoops_HRA.red;
	_hoops_PHRGC[1] *= _hoops_RRA->image._hoops_HRA.green;
	_hoops_PHRGC[2] *= _hoops_RRA->image._hoops_HRA.blue;

	glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, _hoops_PHRGC);
	_hoops_CCCGC (_hoops_CSRGR, GL_FRONT);
	FORCE_COLOR_4F(_hoops_PHRGC[0], _hoops_PHRGC[1], _hoops_PHRGC[2], _hoops_PHRGC[3], false);


	_hoops_GSAC (_hoops_CSRGR, nr, txr, _hoops_GPGRC, _hoops_HSSGC, id,0);


	if (!BIT(txr->_hoops_RHGH->flags, _hoops_PCRH)) {
		u=1.0f;
		v=1.0f;
	}
	else {
		u = (float)matr->_hoops_SCA->texture->image->width/(float)txr->_hoops_RHGH->width;
		v = (float)matr->_hoops_SCA->texture->image->height/(float)txr->_hoops_RHGH->height;
	}
	_hoops_RSIC = (count>0 ? count : -count);

	for (i=0; i<_hoops_RSIC; ++i) {
		_hoops_PSIC[i*param_width] = params[i*param_width] * u;
		_hoops_PSIC[i*param_width +1] = params[i*param_width +1] * v;
	}

	_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, 0);
	ENSURE_TEXTURE_ENV_MODE (_hoops_CSRGR, GL_MODULATE, 0);

#ifdef _hoops_GCGGC
	bool _hoops_SIPRC = false;
	_hoops_HPGRC _hoops_IPGRC;
	if(!_hoops_CSRGR->_hoops_GSGRR)
	{
		_hoops_RCGGC* _hoops_CPGRC = _hoops_ACGGC(dc->_hoops_RIGC->thread_id);
		if (_hoops_CPGRC &&
			!BIT(dc->flags, _hoops_GPHHP) &&
			!BIT(dc->flags, _hoops_GIHCP)) {

				_hoops_IPGRC._hoops_AHGRC((void*)&nr, NULL, false);

				if (strncmp(_hoops_IPGRC._hoops_PHGRC, "swbg_", 5) == 0) {
					_hoops_CPGRC->InitShader(_hoops_IPGRC, dc->_hoops_RIGC->thread_id, (void*)&nr);
					_hoops_CPGRC->_hoops_CHCRR(_hoops_IPGRC, dc->_hoops_RIGC->thread_id);
					_hoops_CPGRC->_hoops_PPRRC(_hoops_IPGRC, dc->_hoops_RIGC->thread_id);
					_hoops_SIPRC = true;
				}
		}
	}

	if (!_hoops_SIPRC)
	{
#endif

	do {
		if (_hoops_CAPA != null) {
			_hoops_HCIGC (_hoops_CSRGR);
			_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			_hoops_IGCGC (_hoops_CSRGR);
		}

		_hoops_GPRH(_hoops_ACCA) += 2;

		float _hoops_GCPRC = _hoops_CSRGR->_hoops_GSGRR ? 100 : 0;

		glBegin (GL_TRIANGLES);
		for (i=0; i<6; ++i)
		{
			glTexCoord2fv (&_hoops_PSIC[indices[i]*param_width]);
			//_hoops_RCPRC (&_hoops_RSSA[_hoops_PSPI[_hoops_HAS]]._hoops_SISR);
			glVertex3f(points[indices[i]].x + 0.5f, points[indices[i]].y + 0.5f, points[indices[i]].z + _hoops_GCPRC);
		}
		glEnd ();

		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);

#ifdef _hoops_GCGGC
	}
#endif

	_hoops_AARRC (_hoops_CSRGR,0);
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_ICGRC(_hoops_CSRGR);
	_hoops_HPRH(txr);

	return true;
}

#ifndef DISABLE_TEXTURING
/*
 * _hoops_SRAC
 */
local void
draw_dc_textured_polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	_hoops_SSIC				param_flags) {
	OGLData alter *				_hoops_CSRGR = OGLNRD(nr);
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HHA const &	matr = _hoops_SIGA->_hoops_CHA;
	_hoops_GRGH const &		_hoops_ACHI = nr->_hoops_IRR;
	Net_Rendition				_hoops_CRAI;
	_hoops_HHCR			_hoops_GGCC;
	Tristrip alter				ts;
	float						_hoops_APCP;
	Point alter *				_hoops_RGCC;
	Vector alter *				normals;
	int *						lengths;
	int *						_hoops_AGCC;
	int							_hoops_RRC, used, i;

	_hoops_RAPRC("draw_dc_textured_polytriangle", true);

	if (BIT (param_flags, _hoops_IGASP)) {
		if (_hoops_CCIC(nr, count, points, params, param_width))
			return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP) &&
		nr->transform_rendition->_hoops_RGH != null) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;
		int									_hoops_CPGGA;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH)
			_hoops_CPGGA = _hoops_GGH->_hoops_CRH;
		else
			_hoops_CPGGA = _hoops_GGH->_hoops_PGH;

		if (_hoops_CPGGA > _hoops_CSRGR->_hoops_GAH) {
			HD_Clip_DC_Polytriangle (nr, count, points, 0, colors, planes,
									 params, param_width, param_flags, _hoops_GPHC|_hoops_AAIC);
			return;
		}
	}

	if (_hoops_SIGA->_hoops_AGP != null && _hoops_SIGA->_hoops_AGP->count > _hoops_CSRGR->_hoops_SHRGC ||
		(BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA) && !_hoops_CSRGR->_hoops_IARGC)) {
	    HD_Std_DC_Textured_Polytris (nr, count, points, colors, planes, params, param_width, param_flags);
	    return;
	}

	if (BIT (_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_CIPRC) &&
		matr->_hoops_ARIR &&
		BIT (_hoops_ACHI->_hoops_CSA, _hoops_GSRC) &&
		matr->_hoops_SCA != null &&
		BIT(matr->_hoops_SCA->texture->_hoops_SCR, _hoops_RCRH) &&
		(matr->_hoops_SCA->texture->image->width > _hoops_CSRGR->_hoops_HPHGC ||
		 matr->_hoops_SCA->texture->image->height > _hoops_CSRGR->_hoops_HPHGC)) {

	    HD_Std_DC_Textured_Polytris (nr, count, points, colors, planes, params, param_width, param_flags);
		return;
	}

	/* _hoops_RAHCP _hoops_CAH _hoops_ISPR */
	if (BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES) &&
		BIT (_hoops_ACHI->_hoops_CSA, _hoops_SSA) &&
		_hoops_SIGA->_hoops_AGP) {
		_hoops_AS const *light;

		light = _hoops_SIGA->_hoops_AGP->_hoops_CGR;
		while (light != null) {
			if (light->_hoops_PRR != _hoops_H) {
				HD_Std_DC_Textured_Polytris (nr, count, points, colors, planes, params, param_width, param_flags);
				return;
			}
			light = light->next;
		}
	}


	_hoops_CRAI = nr;
	_hoops_GGCC = _hoops_CRAI.Modify()->transform_rendition.Modify(1<<23);
	_hoops_GGCC->flags &= ~_hoops_IGSP;
	_hoops_GGCC->heuristics &= ~_hoops_RSA;

	if ((BIT (_hoops_GGCC->flags, _hoops_GRHH) &&
		 !BIT (_hoops_GGCC->flags, _hoops_PRIR))) {
		/* _hoops_HHSA _hoops_GSIA _hoops_RCA _hoops_GPP _hoops_HIS _hoops_SGS _hoops_SR _hoops_GA'_hoops_RA _hoops_HGCR _hoops_PGGS _hoops_PAGIR */
		_hoops_GGCC->flags |= _hoops_PRIR;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);

	/* _hoops_CCA "_hoops_PSP _hoops_CCSHP _hoops_AARAR", _hoops_SR _hoops_HPPR _hoops_IS _hoops_RHHR _hoops_RH _hoops_GRSIP _hoops_SSH _hoops_SIHGA.
	    _hoops_SR _hoops_ACPRC _hoops_IS _hoops_AA _hoops_HIS _hoops_GGR _hoops_RGR _hoops_API, _hoops_PHRI, _hoops_PGGA _hoops_SR _hoops_CHR _hoops_PSAR
		3d _hoops_CPAP _hoops_IS _hoops_CSPH _hoops_PPR _hoops_PSCR _hoops_ISSC _hoops_GICS. _hoops_IPCP _hoops_CGCHI: _hoops_AISI _hoops_ISSC _hoops_SAHR _hoops_IRS _hoops_IGRH. */
	if (!BIT (_hoops_GGCC->flags, _hoops_IRI)) {
		DC_Point alter * _hoops_PCPRC = (DC_Point alter *)points;
		DC_Point const * end;

		if (_hoops_RRC == 3)
			end = points + count * 3;
		else
			end = points + count + 2;
		while (_hoops_PCPRC < end) {
			_hoops_PCPRC->z += 10;
			_hoops_PCPRC++;
		}
		_hoops_GGCC->_hoops_GSCH[0] = 0;
		_hoops_GGCC->_hoops_GSCH[1] = 1;
	}

	if (_hoops_GGCC->_hoops_IPH->data._hoops_RAGR != _hoops_SGICR) {
		_hoops_GGCC->_hoops_IPH = _hoops_SGCC::Create (nr->_hoops_SRA);
	    HD_Redo_Screen (_hoops_CRAI, &((_hoops_HHRA alter *)_hoops_GGCC->_hoops_SPH)->_hoops_GRCC);
	}
	if (!BIT (nr->transform_rendition->flags, _hoops_IGCC))
		HD_Validate_World_To_Screen (_hoops_CRAI);
	_hoops_SGCC const &	_hoops_CGRRC = _hoops_CRAI->transform_rendition->_hoops_CGCC;
	_hoops_CGRRC->_hoops_PPRA();


	ALLOC_ARRAY_CACHED (_hoops_RGCC, count*3, Point);
	ALLOC_ARRAY_CACHED (normals, count*3, Vector);
	ALLOC_ARRAY_CACHED (_hoops_AGCC, count*3, int);
	ALLOC_ARRAY_CACHED (lengths, count, int);

	ZERO_STRUCT(&ts, Tristrip);
	ZALLOC(ts._hoops_GSSH, _hoops_RRCC);
	_hoops_ICAI(ts._hoops_GSSH);
	ts._hoops_PHHA = count;
	ts.total = count * 3;
	ts.point_count = count * 3;
	ts.face_count = count;
	ts._hoops_GSSH->_hoops_GSHA = param_width;
	ts._hoops_GSSH->_hoops_SCAI = param_flags & ~_hoops_ARCC;
	ts._hoops_SRHA = _hoops_SRHH | _hoops_GAHH | DL_TEMPORARY_DATA;
	ts._hoops_GSSH->_hoops_CCHA = (_hoops_RSSH alter *)params;
	if (planes)
		ts._hoops_ICHA = normals;
	ts._hoops_AIHA = _hoops_AGCC;
	ts.points = _hoops_RGCC;

	int length = count+2;

	_hoops_RPRA const *		_hoops_APRA = _hoops_CGRRC->data._hoops_APRA->data.elements;

	if (_hoops_RRC == 3) {
		ts.lengths = lengths;
		ts._hoops_RAHH |= _hoops_AAHH;
		ts._hoops_PHHA = count;
		ts.total = count * 3;
		ts.point_count = count * 3;
		used = 0;
		for (i = 0; i < count; i++) {
			lengths[i] = 3;
			_hoops_AGCC[used] = used;
			_hoops_AGCC[used+1] = used+1;
			_hoops_AGCC[used+2] = used+2;

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[used + 0]);
			_hoops_RGCC[used].x = _hoops_HPRA (_hoops_APRA, points[used + 0]) * _hoops_APCP;
			_hoops_RGCC[used].y = _hoops_IPRA (_hoops_APRA, points[used + 0]) * _hoops_APCP;
			_hoops_RGCC[used].z = _hoops_CPRA (_hoops_APRA, points[used + 0]) * _hoops_APCP;

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[used + 1]);
			_hoops_RGCC[used + 1].x = _hoops_HPRA (_hoops_APRA, points[used + 1]) * _hoops_APCP;
			_hoops_RGCC[used + 1].y = _hoops_IPRA (_hoops_APRA, points[used + 1]) * _hoops_APCP;
			_hoops_RGCC[used + 1].z = _hoops_CPRA (_hoops_APRA, points[used + 1]) * _hoops_APCP;

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[used + 2]);
			_hoops_RGCC[used + 2].x = _hoops_HPRA (_hoops_APRA, points[used + 2]) * _hoops_APCP;
			_hoops_RGCC[used + 2].y = _hoops_IPRA (_hoops_APRA, points[used + 2]) * _hoops_APCP;
			_hoops_RGCC[used + 2].z = _hoops_CPRA (_hoops_APRA, points[used + 2]) * _hoops_APCP;

			if (planes) {
				normals[used + 0].x = planes[used + 0].a;
				normals[used + 0].y = planes[used + 0].b;
				normals[used + 0].z = planes[used + 0].c;
				normals[used + 1].x = planes[used + 1].a;
				normals[used + 1].y = planes[used + 1].b;
				normals[used + 1].z = planes[used + 1].c;
				normals[used + 2].x = planes[used + 2].a;
				normals[used + 2].y = planes[used + 2].b;
				normals[used + 2].z = planes[used + 2].c;
			}

			used += 3;
		}
	}
	else {

		ts._hoops_PHHA = 1;
		ts.total = length;
		ts.point_count = length;
		ts.lengths = &length;
		for (i = 0; i < length; i++) {
			_hoops_AGCC[i] = i;

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[i]);
			_hoops_RGCC[i].x = _hoops_HPRA (_hoops_APRA, points[i]) * _hoops_APCP;
			_hoops_RGCC[i].y = _hoops_IPRA (_hoops_APRA, points[i]) * _hoops_APCP;
			_hoops_RGCC[i].z = _hoops_CPRA (_hoops_APRA, points[i]) * _hoops_APCP;

			if (planes) {
				normals[i + 0].x = planes[i].a;
				normals[i + 0].y = planes[i].b;
				normals[i + 0].z = planes[i].c;
			}
		}
	}

	_hoops_CSRGR->_hoops_HCPRC = true;
	draw_3d_tristrip (_hoops_CRAI, &ts);
	_hoops_CSRGR->_hoops_HCPRC = false;

	FREE_ARRAY (_hoops_RGCC, count*3, Point);
	FREE_ARRAY (normals, count*3, Vector);
	FREE_ARRAY (_hoops_AGCC, count*3, int);
	FREE_ARRAY (lengths, count, int);
	if (_hoops_ISAI (ts._hoops_GSSH) == 0)
		HI_Free_Texture_Parameters (ts._hoops_GSSH);

	if (ts._hoops_HSAI != 0)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"invalid tristrip reference count in opengl driver draw_dc_textured_polytriangle");
}
#endif


local void
_hoops_CSII (
		Net_Rendition const & nr,
		OGL_Display_List alter *odl)
{
	OGLData *_hoops_CSRGR = OGLD(nr->_hoops_SRA);
	Display_Context const * dc = nr->_hoops_SRA;

	/* _hoops_GCRR _hoops_IRS _hoops_RSPH _hoops_CRHH */
	Tristrip *_hoops_SSII;

	POOL_ZALLOC(_hoops_SSII,Tristrip, dc->memory_pool);
	POOL_ZALLOC(_hoops_SSII->_hoops_GAHA, _hoops_GACR, dc->memory_pool);
	POOL_ZALLOC(_hoops_SSII->_hoops_GSSH, _hoops_RRCC, dc->memory_pool);

	_hoops_ICAI(_hoops_SSII);
	_hoops_ICAI(_hoops_SSII->_hoops_GSSH);

	/* _hoops_RAP _hoops_GH _hoops_RH _hoops_CRHH _hoops_PPR _hoops_RGCI _hoops_AIRI _hoops_HIGR */
	_hoops_SSII->_hoops_GAHA->list = (_hoops_AGCI*)odl;
	odl->_hoops_PPAH = _hoops_SSII->_hoops_GAHA;
	_hoops_SSII->_hoops_GAHA->_hoops_GHRI = nr->_hoops_SRA->_hoops_GHRI;
	_hoops_SSII->_hoops_GAHA->_hoops_AGRI = odl->item.geometry._hoops_SRHA;
	_hoops_SSII->_hoops_GAHA->_hoops_PRRI = odl->item.geometry._hoops_CARI;
	_hoops_SSII->_hoops_GAHA->_hoops_GGCI = -1;
	_hoops_SSII->_hoops_GSAI = odl->item.geometry._hoops_GSAI;

	//_hoops_PGCI->_hoops_HGCI = _hoops_CSRI->_hoops_IGCI._hoops_CPAP._hoops_CGCI;
	_hoops_SSII->_hoops_SRHA = odl->item.geometry._hoops_SRHA;
	_hoops_SSII->_hoops_CARI = odl->item.geometry._hoops_CARI;
	_hoops_SSII->face_attributes.flags = odl->item.geometry._hoops_IRRI;
	_hoops_SSII->_hoops_SRHA |= DL_DO_NOT_RECOMPILE;
	_hoops_SSII->_hoops_GSSH->_hoops_SCAI = odl->item.geometry.param_flags[0];
	_hoops_SSII->total = odl->item.geometry._hoops_IGGI.total; 
	_hoops_SSII->_hoops_PHHA = odl->item.geometry._hoops_IGGI._hoops_PHHA; 
	_hoops_SSII->point_count = odl->item.geometry._hoops_IGGI.point_count;

		/* _hoops_CHPR _hoops_IS "_hoops_PGSA 3d _hoops_CRHH" */
	ASSERT(_hoops_SSII->_hoops_GAHA->list);	//_hoops_SR _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_ARI
	draw_3d_tristrip(nr, _hoops_SSII);
	ASSERT(_hoops_SSII->_hoops_GAHA->list);	//_hoops_SCH _hoops_HRGR _hoops_CHHH _hoops_IH _hoops_PRCI _hoops_IS _hoops_HRCI _hoops_IRCI

	/* _hoops_CRCI */

	FREE(_hoops_SSII->_hoops_GSSH, _hoops_RRCC);

	FREE(_hoops_SSII->_hoops_GAHA, _hoops_GACR);
	FREE(_hoops_SSII, Tristrip);
	odl->_hoops_PPAH = null;
	if (ANYBIT (odl->item.geometry._hoops_SRHA, DL_COLORS_BY_FINDEX|_hoops_GGIA|DL_VCOLORED_TRISTRIP)) {
		_hoops_ICGRC (_hoops_CSRGR);
		_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	}
}


local void _hoops_HARI (
		Net_Rendition const & nr,
		OGL_Display_List_List alter *_hoops_AACI,
		bool _hoops_PACI,
		bool _hoops_HACI)
{
	OGL_Display_List *odl;
	bool draw;

	_hoops_AACI->ResetCursor();
	while ((odl = _hoops_AACI->PeekCursor()) != null) {
		if (BIT (odl->item.geometry._hoops_IRRI, _hoops_IAGI))
			draw = _hoops_PACI;
		else
			draw = _hoops_HACI;
		if (draw)
			_hoops_CSII (nr, odl);
		_hoops_AACI->AdvanceCursor();
	}
}


local void
_hoops_SRCI (
		Net_Rendition const & nr,
		OGL_Display_List alter *odl)
{
	Display_Context const * dc = nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLD(nr->_hoops_SRA);
	Polyedge *_hoops_GACI;

	POOL_ZALLOC (_hoops_GACI, Polyedge, dc->memory_pool);
	POOL_ZALLOC (_hoops_GACI->_hoops_GAHA, _hoops_GACR, dc->memory_pool);

	/* _hoops_RAP _hoops_GH _hoops_RH _hoops_ACRI _hoops_PPR _hoops_RGCI _hoops_AIRI _hoops_HIGR */
	_hoops_GACI->_hoops_GAHA->list = (_hoops_AGCI*)odl;
	_hoops_GACI->_hoops_GAHA->list->_hoops_PPAH = _hoops_GACI->_hoops_GAHA;
	_hoops_GACI->_hoops_GAHA->_hoops_GHRI = nr->_hoops_SRA->_hoops_GHRI;
	_hoops_GACI->_hoops_GAHA->_hoops_AGRI = odl->item.geometry._hoops_SRHA;
	_hoops_GACI->_hoops_GAHA->_hoops_PRRI = odl->item.geometry._hoops_CARI;
	_hoops_GACI->_hoops_GAHA->_hoops_GGCI = -1;

	_hoops_GACI->_hoops_GSAI = odl->item.geometry._hoops_GSAI;
	_hoops_GACI->_hoops_SRHA = odl->item.geometry._hoops_SRHA;
	_hoops_GACI->_hoops_CARI = odl->item.geometry._hoops_CARI;
	_hoops_GACI->_hoops_PPGI.flags = odl->item.geometry._hoops_IRRI;
	_hoops_GACI->_hoops_SRHA |= DL_DO_NOT_RECOMPILE;
	_hoops_GACI->total = odl->item.geometry._hoops_IGGI.total;
	_hoops_GACI->point_count = odl->item.geometry._hoops_IGGI.point_count;
	_hoops_GACI->_hoops_PHHA = odl->item.geometry._hoops_IGGI._hoops_PHHA;

	ASSERT(_hoops_GACI->_hoops_GAHA->list);	//_hoops_SR _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_ARI _hoops_HCCPR _hoops_IIH'_hoops_GRI _hoops_CPHP _hoops_IS _hoops_GRCI
	/* _hoops_CHPR _hoops_IS "_hoops_PGSA 3d _hoops_ACRI" */
	draw_3d_polyedge(nr, _hoops_GACI);
	ASSERT(_hoops_GACI->_hoops_GAHA->list);	//_hoops_SCH _hoops_HRGR _hoops_CHHH _hoops_IH _hoops_PRCI _hoops_IS _hoops_HRCI _hoops_IRCI

	/* _hoops_CRCI */
	FREE (_hoops_GACI->_hoops_GAHA, _hoops_GACR);
	FREE (_hoops_GACI, Polyedge);
	odl->_hoops_PPAH = null;
	if (ANYBIT (odl->item.geometry._hoops_SRHA, DL_COLORS_BY_FINDEX|_hoops_GGIA|DL_VCOLORED_TRISTRIP)) {
		_hoops_ICGRC (_hoops_CSRGR);
		_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	}
}


local void _hoops_CGAI (
		Net_Rendition const & nr,
		OGL_Display_List alter *_hoops_CHGI,
		bool _hoops_PACI,
		bool _hoops_HACI)
{
	OGL_Display_List_List alter *_hoops_AACI = null;
	OGL_Display_List *odl;
	bool draw;
	int i;

	for (i = 0; i < 3; i++) {
		if (i == 0)
			_hoops_AACI = _hoops_CHGI->item._hoops_ACGI._hoops_RGAI;
		else if (i == 1)
			_hoops_AACI = _hoops_CHGI->item._hoops_ACGI._hoops_GGAI;
		else if (i == 2)
			_hoops_AACI = _hoops_CHGI->item._hoops_ACGI._hoops_AGAI;
		if (!_hoops_AACI)
			continue;
		_hoops_AACI->ResetCursor();
		while ((odl = _hoops_AACI->PeekCursor()) != null) {
			if (BIT (odl->item.geometry._hoops_IRRI, _hoops_APGI))
				draw = _hoops_PACI;
			else
				draw = _hoops_HACI;
			if (draw)
				_hoops_SRCI (nr, odl);
			_hoops_AACI->AdvanceCursor();
		}
	}
}


local void
_hoops_ICPRC (
		Net_Rendition const & inr,
		_hoops_ACHR type,
		OGL_Display_List_List alter *_hoops_AACI)
{
	OGLData *_hoops_CSRGR = OGLD(inr->_hoops_SRA);
	OGL_Display_List *odl;

	Net_Rendition nr = inr;
	if (type != T_VERTICES) {
		nr->_hoops_SCP = nr->_hoops_GSP;
	}

	/* _hoops_CACI _hoops_RHIR _hoops_RH _hoops_CCGI _hoops_HIGR _hoops_PPR _hoops_PGSA _hoops_HCR _hoops_IIGR _hoops_CAPR! */
	_hoops_AACI->ResetCursor();
	while ((odl = _hoops_AACI->PeekCursor()) != null) {
		/* _hoops_GCRR _hoops_IRS _hoops_RSPH _hoops_CRHH */
		Polymarker *_hoops_IRAI;

		ZALLOC (_hoops_IRAI, Polymarker);
		ZALLOC (_hoops_IRAI->_hoops_GAHA, _hoops_GACR);

		_hoops_ICAI (_hoops_IRAI);

		/* _hoops_RAP _hoops_GH _hoops_RH _hoops_CRHH _hoops_PPR _hoops_RGCI _hoops_AIRI _hoops_HIGR */
		_hoops_IRAI->_hoops_GAHA->list = (_hoops_AGCI*)odl;
		odl->_hoops_PPAH = _hoops_IRAI->_hoops_GAHA;
		_hoops_IRAI->_hoops_GAHA->_hoops_GHRI = nr->_hoops_SRA->_hoops_GHRI;
		_hoops_IRAI->_hoops_GAHA->_hoops_AGRI = odl->item.geometry._hoops_SRHA;
		_hoops_IRAI->_hoops_GAHA->_hoops_PRRI = odl->item.geometry._hoops_CARI;
		_hoops_IRAI->_hoops_GAHA->_hoops_GGCI = -1;

		_hoops_IRAI->_hoops_GSAI = odl->item.geometry._hoops_GSAI;
		_hoops_IRAI->_hoops_SRHA = odl->item.geometry._hoops_SRHA;
		_hoops_IRAI->_hoops_CARI = odl->item.geometry._hoops_CARI;
		_hoops_IRAI->_hoops_SACI.flags = odl->item.geometry._hoops_IRRI;
		_hoops_IRAI->_hoops_SRHA |= DL_DO_NOT_RECOMPILE;
		_hoops_IRAI->point_count = odl->item.geometry._hoops_IGGI.point_count;
		_hoops_IRAI->length = _hoops_IRAI->point_count;

		/* _hoops_CHPR _hoops_IS "_hoops_PGSA 3d _hoops_PAAI" */
		ASSERT (_hoops_IRAI->_hoops_GAHA->list);	//_hoops_SR _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_ARI
		draw_3d_polymarker (nr, _hoops_IRAI);
		ASSERT (_hoops_IRAI->_hoops_GAHA->list);	//_hoops_SCH _hoops_HRGR _hoops_CHHH _hoops_IH _hoops_PRCI _hoops_IS _hoops_HRCI _hoops_IRCI

		/* _hoops_CRCI */
		FREE (_hoops_IRAI->_hoops_GAHA, _hoops_GACR);
		FREE (_hoops_IRAI, Polymarker);
		odl->_hoops_PPAH = null;
		_hoops_AACI->AdvanceCursor();
		if (ANYBIT (odl->item.geometry._hoops_SRHA, DL_COLORS_BY_FINDEX|_hoops_GGIA|DL_VCOLORED_TRISTRIP)) {
			_hoops_ICGRC (_hoops_CSRGR);
			_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
		}
	}
}


local void _hoops_ICII (
		Net_Rendition const & nr,
		OGL_Display_List_List alter *_hoops_AACI,
		_hoops_ACHR _hoops_RGP)
{
	OGL_Display_List *odl;
	OGL_Display_List *_hoops_APCI;
	OGL_Display_List_List *list;

	if (BIT (_hoops_RGP, T_FACES)) {
		_hoops_AACI->ResetCursor();
		while ((odl = _hoops_AACI->PeekCursor()) != null) {
			if (odl->item._hoops_ACII._hoops_PCII) {
				list = odl->item._hoops_ACII._hoops_PCII;
				list->ResetCursor();
				while ((_hoops_APCI = list->PeekCursor()) != null) {
					list->AdvanceCursor();
					_hoops_CSII (nr, _hoops_APCI);
				}
			}
		_hoops_AACI->AdvanceCursor();
	}
	}
	if (BIT (_hoops_RGP, T_ANY_POLYGON_EDGE)) {
		_hoops_AACI->ResetCursor();
		while ((odl = _hoops_AACI->PeekCursor()) != null) {
			if (odl->item._hoops_ACII._hoops_GHPI) {
				list = odl->item._hoops_ACII._hoops_GHPI;
				list->ResetCursor();
				while ((_hoops_APCI = list->PeekCursor()) != null) {
					list->AdvanceCursor();
					_hoops_SRCI (nr, _hoops_APCI);
				}
			}
			_hoops_AACI->AdvanceCursor();
		}
	}
}


local bool _hoops_CPGI (
		_hoops_GRGH const &_hoops_RRGH)
{

	bool _hoops_SPGI = BIT (_hoops_RRGH->locks.color, Color_FRONT) &&
					 BIT (_hoops_RRGH->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE);
	if (_hoops_SPGI)
		return false;

	_hoops_GHGI _hoops_RHGI = _hoops_RRGH->_hoops_CSA & ~_hoops_AHGI;
	return ANYBIT (_hoops_RHGI, _hoops_PHGI);
}


local void
_hoops_PPCI (
		Net_Rendition const & nr,
		_hoops_GACR alter *dl)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLD (dc);
	OGL_Display_List *_hoops_CHGI = (OGL_Display_List *) dl->list;
	OGL_Display_List *odl;
	_hoops_ACHR _hoops_RGP = nr->_hoops_RGP;
	_hoops_ACHR _hoops_HPCI = dc->_hoops_IPCI->mask;
	bool _hoops_RIRI, _hoops_GIRI;

	_hoops_RIRI = BIT (_hoops_CHGI->item._hoops_ACGI.flags, OGL_SEGDL_HAS_EXPLICIT_VISIBLE);

	if (_hoops_CSRGR->_hoops_CIGI) {
		_hoops_HPSGC (_hoops_CSRGR);
		return;
	}

	if (_hoops_CHGI->type != OGL_DL_SEGMENT_TREE) {
		/* _hoops_IH _hoops_HA, _hoops_RGR _hoops_API _hoops_PAH _hoops_RGAR _hoops_RGHH _hoops_CAGH _hoops_PAPA _hoops_AIRI _hoops_CPCI */
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
			"Unknown display list type in dx9_driver::execute_display_list");
		return;
	}

	if (BIT (_hoops_RGP, T_FACES)) {
		if (BIT (dl->_hoops_PRRI, _hoops_GCRI)) {
			_hoops_RGP |= T_EDGES;
			dc->_hoops_IPCI->mask |= (_hoops_ASRI|_hoops_GHCI);
		}
		if (BIT (dl->_hoops_PRRI, _hoops_RCRI)) {
			_hoops_RGP |= T_EDGES;
			dc->_hoops_IPCI->mask |= (_hoops_RSRI);
		}
	}
	if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES)) {
		_hoops_RGP |= _hoops_GPA;
		if (_hoops_CPGI (nr->_hoops_IRR)) {
			_hoops_RGP &= ~(T_FACES);
			_hoops_RGP |= nr->_hoops_ARA->_hoops_CICP._hoops_RGP & (T_FACES);
		}
	}

	//_hoops_RH _hoops_HSPR _hoops_RIS _hoops_RHCI _hoops_HHH _hoops_AHCI _hoops_PHCI _hoops_CCA _hoops_HHCI _hoops_IHCI [#10623]
	if (dc->_hoops_IPCI->_hoops_CHCI != segment_render &&
		dc->_hoops_IPCI->_hoops_CHCI != HD_Standard_Render) {
		(*dc->_hoops_IPCI->_hoops_CHCI) (nr, (Geometry *)dl, dc->_hoops_IPCI->mask, true);
		return;
	}

	if (_hoops_CHGI->item._hoops_ACGI._hoops_ARRI) {
		_hoops_GIRI = BIT (_hoops_RGP, T_FACES);
		if (_hoops_GIRI || _hoops_RIRI) {
			_hoops_HARI (nr,
				_hoops_CHGI->item._hoops_ACGI._hoops_ARRI,
				_hoops_RIRI, _hoops_GIRI);
		}
	}
	if (_hoops_CHGI->item._hoops_ACGI._hoops_CRPRC) {
		_hoops_GRGGI *glist = _hoops_CHGI->item._hoops_ACGI._hoops_CRPRC;
		_hoops_ACHR mask = (_hoops_SHSI | _hoops_PGRI);
		Geometry *g;

		glist->ResetCursor ();
		for (;;) {
			g = glist->PeekCursor();
			if (!g)
				break;
			dc->_hoops_IPCI->_hoops_CHCI (nr, g, mask, true);
			glist->AdvanceCursor();
		}
	}
	if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
		if (_hoops_CHGI->item._hoops_ACGI._hoops_RCII)
			_hoops_ICII (nr, _hoops_CHGI->item._hoops_ACGI._hoops_RCII, _hoops_RGP);
	}

	if (_hoops_CHGI->item._hoops_ACGI._hoops_AGAI ||
		_hoops_CHGI->item._hoops_ACGI._hoops_GGAI ||
		_hoops_CHGI->item._hoops_ACGI._hoops_RGAI) {
		_hoops_GIRI = ANYBIT (_hoops_RGP, _hoops_PSRI);
		if (_hoops_GIRI || _hoops_RIRI)
			_hoops_CGAI (nr,
				_hoops_CHGI, _hoops_RIRI, _hoops_GIRI);
		if (_hoops_CHGI->item._hoops_ACGI._hoops_SRPRC) {
			_hoops_GRGGI *glist = _hoops_CHGI->item._hoops_ACGI._hoops_SRPRC;
			_hoops_ACHR mask = (_hoops_SHSI | _hoops_IGAI);
			Geometry *g;

			glist->ResetCursor ();
			for (;;) {
				g = glist->PeekCursor();
				if (!g)
					break;
				dc->_hoops_IPCI->_hoops_CHCI (nr, g, mask, true);
				glist->AdvanceCursor();
			}
		}
	}

	if (BIT (_hoops_RGP, T_LINES) &&
		_hoops_CHGI->item._hoops_ACGI._hoops_CAPI) {
		OGL_Display_List_List *_hoops_AACI = _hoops_CHGI->item._hoops_ACGI._hoops_CAPI;
		/* _hoops_CACI _hoops_RHIR _hoops_RH _hoops_HIGR _hoops_PPR _hoops_PGSA _hoops_HCR _hoops_IIGR _hoops_CAPR! */
		_hoops_AACI->ResetCursor();
		while ((odl = _hoops_AACI->PeekCursor()) != null) {
			ASSERT (odl->type == OGL_DL_SEGMENT_POLYLINE);

			Polyedge *pe = odl->item._hoops_RPPI.pe;
			really_draw_3d_polyedge (nr, nr->_hoops_AHP, pe, null);
			_hoops_AACI->AdvanceCursor();
		}
	}

	if (BIT (_hoops_RGP, T_MARKERS) &&
		_hoops_CHGI->item._hoops_ACGI._hoops_GAAI) {
		_hoops_ICPRC (nr, T_MARKERS, _hoops_CHGI->item._hoops_ACGI._hoops_GAAI);
	}

	if (BIT (_hoops_RGP, T_VERTICES) &&
		_hoops_CHGI->item._hoops_ACGI._hoops_ICARC) {
		_hoops_ICPRC (nr, T_VERTICES, _hoops_CHGI->item._hoops_ACGI._hoops_ICARC);
	}

	dc->_hoops_IPCI->mask = _hoops_HPCI;

} //_hoops_RSGR _hoops_API '_hoops_GRCI _hoops_AIRI _hoops_HIGR'


/*
 * _hoops_PGAA
 */
local bool
_hoops_RPRC (
	Net_Rendition const &		nr,
	Tristrip const *			ts,
	_hoops_GACR const *		dl,
	OGL_Display_List const *	odl)
{
	OGLData alter*				_hoops_CSRGR = OGLD (nr->_hoops_SRA); //_hoops_CIGII _hoops_RCIC, _hoops_AHSAR _hoops_IH _hoops_GGAR _hoops_HH _hoops_HGSR
	_hoops_GRGH const &		_hoops_ACHI = nr->_hoops_IRR;
	bool 						_hoops_GHRC, _hoops_RHRC, findices;
	bool 						_hoops_AHRC, _hoops_PHRC, _hoops_HHRC;
	bool 						_hoops_SPGI, _hoops_IHRC;
	unsigned int				_hoops_RHGI;
	bool						_hoops_SHRC;

	if (odl->type != OGL_DL_GEOMETRY && odl->type != OGL_DL_GEOMETRY_VBO) {
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
			"Unexpected display list type in ogl::check_tristrip_display_list_valid");
		return false;
	}

	if (dl && dl->_hoops_GSAI == DL_FLAG_INVALID)
		return false;

	/* _hoops_SGH ! _hoops_GPP _hoops_GIPR _hoops_AIRSP _hoops_IIGR _hoops_CGSSR _hoops_IS _hoops_RPGP _hoops_IH _hoops_SICHR, _hoops_HRII _hoops_HSAR _hoops_GSAHH, _hoops_CCPRC */
	_hoops_SHRC = BIT (odl->item.geometry._hoops_SRHA, DL_HAS_TRANSPARENCY);
	if (!BIT (nr->_hoops_PSGI, T_FACES) != !_hoops_SHRC) {
		if (!nr->_hoops_IRR->_hoops_GIRC)
			return false;
	}

	if (BIT (odl->item.geometry._hoops_CARI, _hoops_HPII))
		return true;  //_hoops_AAPI _hoops_HS _hoops_PSP _hoops_IRGH _hoops_GPHA _hoops_AIRC, _hoops_HIS _hoops_PIRC _hoops_IIGR _hoops_RH _hoops_RII _hoops_PCGC _hoops_GHAA

	if (BIT (odl->item.geometry._hoops_SRHA, _hoops_CAGI)) {
		if (odl->time_stamp <
			nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->time_stamp)
			return false;
	}

	if (nr->_hoops_IHA->_hoops_CHA->texture[_hoops_RIA] &&
		(nr->_hoops_IHA->_hoops_CHA->texture[_hoops_RIA]->_hoops_PSR == _hoops_HSR ||
		nr->transform_rendition->_hoops_SPH->projection != _hoops_GHH))
		return false;

	_hoops_RHGI = _hoops_ACHI->_hoops_CSA & ~_hoops_AHGI;
	_hoops_SPGI = BIT (_hoops_ACHI->locks.color, Color_FRONT) &&
		 BIT (_hoops_ACHI->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE);
	_hoops_RHRC = (!_hoops_SPGI && BIT (_hoops_RHGI, _hoops_PHGI));
	_hoops_GHRC = BIT (odl->item.geometry._hoops_SRHA, DL_INDEX_INTERPOLATION);
	findices = BIT (odl->item.geometry._hoops_SRHA, DL_COLORS_BY_FINDEX);
	_hoops_HHRC = BIT (odl->item.geometry._hoops_SRHA, DL_VCOLORED_TRISTRIP);

	if (findices && (_hoops_GHRC != _hoops_RHRC))
		return false;
	if (_hoops_HHRC) {
		_hoops_PHRC =(!_hoops_SPGI && BIT (_hoops_RHGI, _hoops_HIRC));
		_hoops_AHRC = BIT (odl->item.geometry._hoops_SRHA, DL_COLOR_INTERPOLATION);
		if (_hoops_AHRC != _hoops_PHRC)
			return false;
		_hoops_IHRC = BIT (odl->item.geometry._hoops_SRHA, _hoops_IIRC);
		if (_hoops_SPGI != _hoops_IHRC)
		return false;
	}

	if (BIT(odl->item.geometry._hoops_SRHA, _hoops_GGIA) &&
		!OGL_DEFINE_INTERPOLATION_TEXTURE (_hoops_CSRGR, nr))
		return false;

	if (ts) {
		int _hoops_CIRC, _hoops_SIRC, _hoops_GCRC;
		int added, _hoops_RCRC;
		_hoops_CIRC = _hoops_ACRC & ~(
			DL_COLOR_INTERPOLATION |
			DL_INDEX_INTERPOLATION |
			_hoops_SRHH);
		_hoops_SIRC = DL_TEXTURING;
		_hoops_GCRC = (
			_hoops_PCRC |
			_hoops_HCRC |
			_hoops_ICRC);

		if (odl->item.geometry.id == 0)
			return false;

		added = odl->item.geometry._hoops_SRHA & ~ts->_hoops_SRHA;
		_hoops_RCRC = ts->_hoops_SRHA & ~odl->item.geometry._hoops_SRHA;
		if ((_hoops_RCRC & _hoops_CIRC) != 0)
			return false;
		if ((added & _hoops_CIRC & ~_hoops_SIRC) != 0)
			return false;

		// _hoops_ISPR _hoops_SCRC
		added = odl->item.geometry._hoops_CARI & ~ts->_hoops_CARI;
		_hoops_RCRC = ts->_hoops_CARI & ~odl->item.geometry._hoops_CARI;
		if ((_hoops_RCRC & _hoops_GCRC) != 0)
			return false;
		if ((added & _hoops_GCRC) != 0)
			return false;

		if (ANYBIT ((odl->item.geometry._hoops_GSAI ^ ts->_hoops_GSAI), Rendo_TRISTRIP_MASK))
			return false;
		if (BIT (ts->_hoops_SRHA, DL_TEXTURING) &&
			ts->_hoops_GSSH &&
			odl->item.geometry.param_flags[0] != ts->_hoops_GSSH->_hoops_SCAI)
			return false;
	}
	else {
		unsigned int _hoops_GSAI = _hoops_ACHI->_hoops_CSA & Rendo_TRISTRIP_MASK;
		if (BIT (nr->_hoops_IRR->_hoops_CSA,
				 (_hoops_GSRC & ~_hoops_AHGI)) &&
			(nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR ||
			 nr->_hoops_IHA->_hoops_GIA->_hoops_ARIR)) {
			if (!BIT (odl->item.geometry._hoops_SRHA, DL_TEXTURING))
				return false;
		}
		if (ANYBIT ((odl->item.geometry._hoops_GSAI ^ _hoops_GSAI), Rendo_TRISTRIP_MASK))
			return false;
	}

	return true;
}

local bool
_hoops_GARC (
	Net_Rendition const &		nr,
	_hoops_GACR const *		dl,
	OGL_Display_List const *	odl)
{
	if (dl && !BIT (dl->_hoops_PRRI, _hoops_RPCGP))
		return true;
	if (dl && dl->_hoops_GSAI == DL_FLAG_INVALID)
		return false;

	_hoops_PARC const *_hoops_HARC = &(nr->_hoops_ARA->_hoops_APPI);
	if (!BIT (dl->_hoops_PRRI, _hoops_APCGP)) {
		if (odl->item._hoops_RPPI._hoops_PPPI != _hoops_HARC->_hoops_PPPI)
			return false;
		if (odl->item._hoops_RPPI._hoops_HPPI != _hoops_HARC->_hoops_HPPI)
			return false;
		if (odl->item._hoops_RPPI._hoops_IPPI != _hoops_HARC->_hoops_IPPI)
			return false;
		if (odl->item._hoops_RPPI._hoops_CPPI != _hoops_HARC->_hoops_CPPI)
			return false;
		if (odl->item._hoops_RPPI._hoops_SPPI != _hoops_HARC->_hoops_SPPI)
			return false;
	}
	return true;
}


/*
 * _hoops_PGAA
 */
local bool _hoops_APRC (
		Net_Rendition const &		nr,
		Polyedge const *			pe,
		_hoops_GACR const *		dl,
		OGL_Display_List const *	odl)
{
	OGLData const *				_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	bool 						_hoops_GHRC, _hoops_RHRC, findices;
	bool 						_hoops_AHRC, _hoops_PHRC, _hoops_HHRC;
	bool 						_hoops_SPGI, _hoops_IHRC;
	unsigned int				_hoops_RHGI;

	if (odl->type != OGL_DL_GEOMETRY) {
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
			"Unexpected display list type in check_polyedge_display_list_valid");
		return false;
	}
	if (!_hoops_CSRGR->_hoops_CSC._hoops_RAIH)
		return true;

	if (dl && dl->_hoops_GSAI == (unsigned int) DL_FLAG_INVALID)
		return false;

	/* _hoops_SGH ! _hoops_GPP _hoops_GIPR _hoops_AIRSP _hoops_IIGR _hoops_CGSSR _hoops_IS _hoops_RPGP _hoops_IH _hoops_SICHR, _hoops_HRII _hoops_HSAR _hoops_GSAHH, _hoops_CRGIR */
	if (!BIT (nr->_hoops_PSGI, T_EDGES) !=
		!BIT (odl->item.geometry._hoops_SRHA, DL_HAS_TRANSPARENCY))
		return false;

	if (BIT (odl->item.geometry._hoops_CARI, _hoops_HPII))
		return true;  //_hoops_AAPI _hoops_HS _hoops_PSP _hoops_IRGH _hoops_GPHA _hoops_AIRC, _hoops_HIS _hoops_PIRC _hoops_IIGR _hoops_RH _hoops_RII _hoops_PCGC _hoops_GHAA

	if (BIT (odl->item.geometry._hoops_SRHA, _hoops_CAGI)) {
		if (odl->time_stamp <
			nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR->time_stamp)
			return false;
	}

	_hoops_RHGI = _hoops_RRGH->_hoops_CSA & ~_hoops_AHGI;
	_hoops_SPGI = BIT (_hoops_RRGH->locks.color, Color_FRONT) &&
		 BIT (_hoops_RRGH->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE);
	_hoops_RHRC = (!_hoops_SPGI && BIT (_hoops_RHGI, _hoops_CSRC));
	_hoops_GHRC = BIT (odl->item.geometry._hoops_SRHA, DL_INDEX_INTERPOLATION);
	findices = BIT (odl->item.geometry._hoops_SRHA, DL_COLORS_BY_FINDEX);
	_hoops_HHRC = BIT (odl->item.geometry._hoops_SRHA, DL_VCOLORED_TRISTRIP);

	if (findices && (_hoops_GHRC != _hoops_RHRC))
		return false;
	if (_hoops_HHRC) {
		if (!BIT (odl->item.geometry._hoops_CARI, _hoops_RCRI)) {
			_hoops_PHRC =(!_hoops_SPGI && BIT (_hoops_RHGI, _hoops_SSRC));
			_hoops_AHRC = BIT (odl->item.geometry._hoops_SRHA, DL_COLOR_INTERPOLATION);
			if (_hoops_AHRC != _hoops_PHRC)
				return false;
		}
		_hoops_IHRC = BIT (odl->item.geometry._hoops_SRHA, _hoops_IIRC);
		if (_hoops_SPGI != _hoops_IHRC)
			return false;
	}

	if (pe) {
		int _hoops_CIRC, _hoops_SIRC, _hoops_GCRC;
		int added, _hoops_RCRC;
		_hoops_CIRC = _hoops_ACRC & ~(
			DL_COLOR_INTERPOLATION |
			DL_INDEX_INTERPOLATION |
			_hoops_SRHH);
		_hoops_SIRC = DL_TEXTURING;
		_hoops_GCRC = (
			_hoops_HCRC |
			_hoops_ICRC);  /* _hoops_PSP _hoops_GGAC _hoops_ARI*/

		// _hoops_ISPR _hoops_CCRC
		added = odl->item.geometry._hoops_SRHA & ~pe->_hoops_SRHA;
		_hoops_RCRC = pe->_hoops_SRHA & ~odl->item.geometry._hoops_SRHA;
		if ((_hoops_RCRC & _hoops_CIRC) != 0)
			return false;
		if ((added & _hoops_CIRC & ~_hoops_SIRC) != 0)
			return false;

		// _hoops_ISPR _hoops_SCRC
		added = odl->item.geometry._hoops_CARI & ~pe->_hoops_CARI;
		_hoops_RCRC = pe->_hoops_CARI & ~odl->item.geometry._hoops_CARI;
		if ((_hoops_RCRC & _hoops_GCRC) != 0)
			return false;
		if ((added & _hoops_GCRC) != 0)
			return false;

		if ((odl->item.geometry._hoops_GSAI & _hoops_RHII) !=
			(pe->_hoops_GSAI & _hoops_RHII))
			return false;
	}
	else {
		if (BIT (nr->_hoops_IRR->_hoops_CSA,
				 (_hoops_RGAC & ~_hoops_AHGI)) &&
			(nr->_hoops_RHP->_hoops_CHA->_hoops_ARIR)) {
			if (!BIT (odl->item.geometry._hoops_SRHA, DL_TEXTURING))
				return false;
		}
		if (!BIT (odl->item.geometry._hoops_CARI, _hoops_RCRI)) {
			if ((odl->item.geometry._hoops_GSAI & _hoops_RHII) !=
				(_hoops_RRGH->_hoops_CSA & _hoops_RHII))
				return false;
		}
	}

	return true;
}


/*
 * _hoops_PGAA
 */
local bool
_hoops_SPRC (
	Net_Rendition const &		nr,
	_hoops_ACHR					_hoops_HRAI,
	Polymarker const *			pm,
	_hoops_GACR const *		dl,
	OGL_Display_List const *	odl)
{
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *				_hoops_CSRGR = OGLD (dc);
	unsigned int				_hoops_RHGI;
	bool 						_hoops_SPGI, _hoops_IHRC;
	bool 						_hoops_GHRC, _hoops_RHRC, findices;
	int							color_type, _hoops_HSCII;

	if (_hoops_HRAI == T_VERTICES) {
		color_type = _hoops_PPA;
		_hoops_HSCII = Color_VERTEX;
	}
	else {
		color_type = _hoops_APA;
		_hoops_HSCII = Color_MARKER;
	}
		
	if (dl->_hoops_GSAI == DL_FLAG_INVALID)
		return false;

	if (odl->item.geometry.id == _hoops_RSARR)
		return false;

	if (!_hoops_CSRGR->_hoops_CSC._hoops_RAIH)
		return true;

	_hoops_RHGI = nr->_hoops_IRR->_hoops_CSA & ~_hoops_AHGI;
	_hoops_SPGI = BIT (nr->_hoops_IRR->locks.color, _hoops_HSCII) &&
		 BIT (nr->_hoops_IRR->locks._hoops_HAA[color_type], M_DIFFUSE);
	_hoops_RHRC = (!_hoops_SPGI && BIT (_hoops_RHGI, _hoops_PHRAP));
	_hoops_GHRC = BIT (odl->item.geometry._hoops_SRHA, DL_INDEX_INTERPOLATION);
	findices = BIT (odl->item.geometry._hoops_SRHA, DL_COLORS_BY_FINDEX);

	if (findices && (_hoops_GHRC != _hoops_RHRC))
		return false;

	_hoops_IHRC = BIT (odl->item.geometry._hoops_SRHA, _hoops_IIRC);
	if (_hoops_SPGI != _hoops_IHRC)
		return false;

	if (pm) {
		unsigned int added, _hoops_RCRC;
		unsigned int _hoops_CIRC = _hoops_ACRC & ~(
			DL_COLOR_INTERPOLATION |
			DL_INDEX_INTERPOLATION);
		unsigned int _hoops_SCPRC = DL_TEXTURING;

		// _hoops_ISPR _hoops_CCRC
		added = odl->item.geometry._hoops_SRHA & ~pm->_hoops_SRHA;
		_hoops_RCRC = pm->_hoops_SRHA & ~odl->item.geometry._hoops_SRHA;
		if ((_hoops_RCRC & _hoops_CIRC) != 0)
			return false;
		if ((added & _hoops_CIRC & ~_hoops_SCPRC) != 0)
			return false;

		//_hoops_GASA _hoops_PIP: _hoops_HRGR _hoops_CPHP _hoops_PII _hoops_RH _hoops_HSPR _hoops_HAHH _hoops_PAR _hoops_HAR?
		//_hoops_RPP ((_hoops_CSRI->_hoops_IGCI._hoops_CPAP._hoops_RSRC & _hoops_GSPRC) !=
		//	(_hoops_IRAS->_hoops_RSRC & _hoops_GSPRC))
		//	_hoops_ASRC _hoops_RCPP;

		if (odl->type == OGL_DL_POLYMARKER_VBO_LIST) {
			OGL_DL_VBO_List* list = (OGL_DL_VBO_List*)I2V(odl->item.geometry.id);
			OGL_Polymarker_Vertex_Buffer_Object* _hoops_SAAS = list->PeekFirst();
			_hoops_RSPRC _hoops_PPCP = _hoops_SAAS->_hoops_PPCP;
			bool _hoops_ASPRC = pm->_hoops_ICHA != null &&
								BIT (nr->_hoops_RGP, T_LIGHTS_FOR_MARKERS);
			if (_hoops_ASPRC && !_hoops_PPCP._hoops_HHCP())
				return false;
		}
	}
	return true;
}


local bool
_hoops_PHII (
		Net_Rendition const &nr,
		int weight)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLD(dc);
	Line_Rendition const &_hoops_GHP = nr->_hoops_RHP;
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;

	if (weight < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC)
		return true;
	if ((nr->_hoops_IRR->_hoops_SRI == _hoops_SICI || ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE))&&
			_hoops_GAPI(_hoops_CSRGR,_hoops_GHP,weight))
		return true;

	if (nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI &&
		_hoops_SIGA->pattern == FP_USER_DEFINED)
		return true;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				return true;
		}
		else {
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				return true;
		}
	}

	if (_hoops_SIGA->color != _hoops_SIGA->_hoops_RGIR &&
		(!BIT (nr->transform_rendition->flags, _hoops_GRHH) ||
			!BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES) ||
			!_hoops_SIGA->_hoops_AGP))
				return true;


	bool _hoops_HHII = false, _hoops_IHII = false;
	_hoops_HHII = (
		BIT (nr->_hoops_RGP, T_FACES) &&
		nr->_hoops_IHA->_hoops_CHA &&
		nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < 1.0f);
	if (BIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE)) {
		_hoops_IHII = (
			nr->_hoops_RHP->_hoops_CHA &&
			nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR < 1.0f);
	}
	if (_hoops_HHII || _hoops_IHII) {
		if (nr->_hoops_CPP->_hoops_PRH.style != _hoops_AIII &&
			nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI &&
			nr->_hoops_CPP->_hoops_PRH._hoops_SRI != _hoops_PIII)
			return true;
	}

	return false;
}


local bool
_hoops_IARC (
	Net_Rendition const &		nr,
	_hoops_GACR const *		dl,
	OGL_Display_List const *	odl)
{
	OGLData *_hoops_CSRGR = OGLD(nr->_hoops_SRA);
	_hoops_ACHR _hoops_CARC = nr->_hoops_RGP;
	OGL_Display_List_List *list;
	OGL_Display_List *_hoops_APCI;
	bool _hoops_SARC, _hoops_GPRC;
	bool _hoops_ASSRR = (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI) ||
				!ANYBIT (nr->transform_rendition->heuristics, _hoops_RSA));

	if (dl && dl->_hoops_GSAI == DL_FLAG_INVALID)
		return false;

	if (BIT (_hoops_CARC, T_FACES)) {
		if (odl->item._hoops_ACII._hoops_PCII) {
			list = odl->item._hoops_ACII._hoops_PCII;

			if (_hoops_ASSRR &&
				list->Count() &&
				BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES))
				return false;

			list->ResetCursor();
			while ((_hoops_APCI = list->PeekCursor()) != null) {
				list->AdvanceCursor();
				if (!_hoops_RPRC (nr, null, null, _hoops_APCI))
					return false;
				_hoops_SARC = BIT (_hoops_APCI->item.geometry._hoops_SRHA, DL_LIGHTING);
				_hoops_GPRC = BIT (nr->transform_rendition->flags, _hoops_GRHH) &&
					BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES);
				if (_hoops_SARC != _hoops_GPRC)
					return false;
			}
		}
	}
	if (BIT (_hoops_CARC, T_ANY_POLYGON_EDGE)) {
		if (odl->item._hoops_ACII._hoops_GHPI) {
			list = odl->item._hoops_ACII._hoops_GHPI;
			if (list->Count() > 0) {
				int weight;
				if ((weight = nr->_hoops_RHP->weight) < 0)
					weight = (int)(HD_Compute_Generic_Size (nr, nr->_hoops_RHP->_hoops_PHP, nr->_hoops_RHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
				if (_hoops_GAPI(_hoops_CSRGR,nr->_hoops_RHP,weight))
					return false;
			}
			list->ResetCursor();
			while ((_hoops_APCI = list->PeekCursor()) != null) {
				list->AdvanceCursor();
				if (!_hoops_APRC (nr, null, null, _hoops_APCI))
					return false;
			}
		}
	}

	if (!BIT (dl->_hoops_PRRI, _hoops_RPCGP))
		return true;

	if (!odl->item._hoops_ACII._hoops_GHPI &&
		!odl->item._hoops_ACII._hoops_PCII)
		return true;

	_hoops_PARC const *_hoops_HARC = &(nr->_hoops_ARA->_hoops_APPI);
	if (!BIT (dl->_hoops_PRRI, _hoops_APCGP)) {
		if (odl->item._hoops_ACII._hoops_PPPI != _hoops_HARC->_hoops_PPPI)
			return false;
		if (odl->item._hoops_ACII._hoops_HPPI != _hoops_HARC->_hoops_HPPI)
			return false;
		if (odl->item._hoops_ACII._hoops_IPPI != _hoops_HARC->_hoops_IPPI)
			return false;
		if (odl->item._hoops_ACII._hoops_CPPI != _hoops_HARC->_hoops_CPPI)
			return false;
		if (odl->item._hoops_ACII._hoops_SPPI != _hoops_HARC->_hoops_SPPI)
			return false;
	}

	return true;
}


static inline Color_Object _hoops_PSPRC (
		_hoops_GRGH const & _hoops_RRGH)
{
	Color_Object _hoops_PCGS = 0;
	if (_hoops_RRGH->locks.color) {
		for (int i = 0 ; i < _hoops_IIGRA ; i++) {
			_hoops_PCGS |= (_hoops_RRGH->locks._hoops_HAA[i] & 0x1) << i;
		}
	}
	return _hoops_PCGS;
}



/*
* _hoops_PGAA
*/
local bool
_hoops_GSCI (
		  Net_Rendition const &nr,
		  _hoops_GACR const *dl,
		  OGL_Display_List const *_hoops_CHGI,
		  int alter *_hoops_HSHI,
		  int alter *_hoops_IICI,
		  int alter *_hoops_CICI)

{
	OGL_Display_List_List *vlist = null;
	_hoops_ACHR _hoops_CARC, _hoops_PPRC;
	OGL_Display_List *odl;

	if (dl->_hoops_GSAI == DL_FLAG_INVALID)
		return false;

	_hoops_CARC = nr->_hoops_RGP;
	if (!BIT(nr->transform_rendition->flags,_hoops_GRHH))
		_hoops_CARC &= ~(T_LIGHTS_FOR_FACES | T_LIGHTS_FOR_EDGES | T_LIGHTS_FOR_MARKERS);
	if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES)) {
		_hoops_CARC |= _hoops_GPA;
		if (_hoops_CPGI(nr->_hoops_IRR)) {
			_hoops_CARC &= ~(T_FACES);
			_hoops_CARC |= nr->_hoops_ARA->_hoops_CICP._hoops_RGP & (T_FACES);
		}
	}
	if (_hoops_HSHI)
		*_hoops_HSHI = _hoops_CARC;

	_hoops_PPRC = _hoops_CHGI->item._hoops_ACGI._hoops_RGP;
	*_hoops_IICI = _hoops_CARC & ~_hoops_PPRC;
	*_hoops_CICI = _hoops_PPRC & ~_hoops_CARC;

	if (ALLBITS (nr->_hoops_IRR->_hoops_CSA, _hoops_HCSI))
		return false;

	if (BIT (dl->_hoops_PRRI, _hoops_RPCGP)) {
		bool _hoops_HSPRC = BIT (dl->_hoops_PRRI, _hoops_APCGP);
		bool _hoops_ISPRC = nr->_hoops_ARA->_hoops_APPI._hoops_SAR;
		if (_hoops_HSPRC != _hoops_ISPRC)
			return false;
	}

	if (_hoops_CHGI->item._hoops_ACGI._hoops_CSPRC != 0) {
		Color_Object _hoops_SSPRC = _hoops_PSPRC(nr->_hoops_IRR) ^ _hoops_CHGI->item._hoops_ACGI._hoops_CSPRC;
		if (ANYBIT (_hoops_SSPRC, _hoops_CHGI->item._hoops_ACGI._hoops_GGHRC))
			return false;
	}

	if (BIT (_hoops_CARC, T_FACES)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_ARRI;
		if (vlist && vlist->Count()) {
			if (BIT (nr->transform_rendition->flags, _hoops_GRHH) &&
				BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES)) {
				/* _hoops_ISGHR _hoops_HCIAR _hoops_PPR _hoops_AHHS, _hoops_ICCI _hoops_PAH'_hoops_RA _hoops_GSSR _hoops_IHAA _hoops_GGR _hoops_AIRI _hoops_CPCI */
				if (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI) ||
					!ANYBIT (nr->transform_rendition->heuristics, _hoops_RSA))
					return false;
				if (BIT (_hoops_CHGI->item._hoops_ACGI._hoops_RGP, T_FACES) &&
					!BIT (_hoops_CHGI->item._hoops_ACGI._hoops_RGP, T_LIGHTS_FOR_FACES))
					return false;
			}
			odl = vlist->PeekFirst();
			if (_hoops_HGRI (nr, odl->item.geometry._hoops_SRHA, BIT (nr->_hoops_PSGI, T_FACES)))
				return false;
		}
		if (vlist) {
			vlist->ResetCursor();
			while ((odl = vlist->PeekCursor()) != null) {
				if (!_hoops_RPRC (nr, null, dl, odl))
					return false;
				vlist->AdvanceCursor();
			}
		}
	}
	if (BIT (_hoops_CARC, T_LINES)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_CAPI;
		if (vlist) {
			vlist->ResetCursor();
			if (vlist->Count()) {
				float weight;
				weight = nr->_hoops_AHP->weight;
				if (weight < 0)
					weight = (int)(HD_Compute_Generic_Size (nr, nr->_hoops_AHP->_hoops_PHP, nr->_hoops_AHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);
				if (_hoops_HSRI (nr, nr->_hoops_AHP, null, weight))
					return false;
			}
			while ((odl = vlist->PeekCursor()) != null) {
				if (!_hoops_GARC (nr, dl, odl))
					return false;
				vlist->AdvanceCursor();
			}
		}
	}

	if (BIT (_hoops_CARC, T_ANY_EDGE)) {
		int i;
		for (i = 0; i < 2; i++) {
			if (i == 0)
				vlist = _hoops_CHGI->item._hoops_ACGI._hoops_GGAI;
			else if (i == 1)
				vlist = _hoops_CHGI->item._hoops_ACGI._hoops_AGAI;
			if (vlist && vlist->Count()) {
				float weight = nr->_hoops_RHP->weight;
				if (weight < 0)
					weight = (int)(HD_Compute_Generic_Size (nr, nr->_hoops_RHP->_hoops_PHP, nr->_hoops_RHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);
				if (_hoops_HSRI (nr, nr->_hoops_RHP, null, weight))
					return false;

				if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP))
					return false;
				vlist->ResetCursor();
				while ((odl = vlist->PeekCursor()) != null) {
					if (!_hoops_APRC (nr, null, dl, odl))
						return false;
					vlist->AdvanceCursor();
				}
			}
		}
	}

	if (BIT (_hoops_CARC, _hoops_GPA)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_RGAI;
		if (vlist && vlist->Count()) {
			if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP))
				return false;
			vlist->ResetCursor();
			while ((odl = vlist->PeekCursor()) != null) {
				if (!_hoops_APRC (nr, null, dl, odl))
					return false;
				vlist->AdvanceCursor();
			}
		}
	}

	if (BIT (_hoops_CARC, T_MARKERS)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_GAAI;
		if (vlist && vlist->Count()) {
			if (_hoops_SGAI (nr, nr->_hoops_GSP, null, null))
				return false;
			vlist->ResetCursor();
			while ((odl = vlist->PeekCursor()) != null) {
				if (!_hoops_SPRC (nr, T_MARKERS, null, dl, odl))
					return false;
				vlist->AdvanceCursor();
			}
		}
	}

	if (BIT (_hoops_CARC, T_VERTICES)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_ICARC;
		if (vlist && vlist->Count()) {
			if (_hoops_SGAI (nr, nr->_hoops_SCP, null, null))
				return false;
			vlist->ResetCursor();
			while ((odl = vlist->PeekCursor()) != null) {
				if (!_hoops_SPRC (nr, T_VERTICES, null, dl, odl))
					return false;
				vlist->AdvanceCursor();
			}
		}
	}

	if (ANYBIT (_hoops_CARC, T_FACES|T_ANY_POLYGON_EDGE)) {
		vlist = _hoops_CHGI->item._hoops_ACGI._hoops_RCII;

		if (vlist) {
			vlist->ResetCursor();
			while ((odl = vlist->PeekCursor()) != null) {
				if (!_hoops_IARC (nr, dl, odl))
					return false;
				vlist->AdvanceCursor();
			}
		}
	}

	return true;
}


/*
 * _hoops_SRAC
 */
local void
_hoops_AICI(
		Net_Rendition const &nr,
		_hoops_GACR **_hoops_PICI,
		unsigned Integer32 *_hoops_RGHRC,
		unsigned Integer32 *_hoops_HICI)
{
	_hoops_GACR *dl;
	OGL_Display_List *_hoops_CHGI;
	bool _hoops_RACR;
	int _hoops_IICI = 0, _hoops_CICI = 0;

	if (ANYBIT (nr->_hoops_RGP, T_EDGES|T_LINES)) {
		if (nr->_hoops_IRR->_hoops_SRI == _hoops_SICI &&
			BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI)) {
			Line_Style const &	_hoops_ACCI = nr->_hoops_ASIR->_hoops_GCCI.line_style;

			/* _hoops_PCCI _hoops_HII _hoops_HCCI _hoops_GGR _hoops_ICCI._hoops_GGHR */
			if (!BIT(_hoops_ACCI->flags, LSF_SOLID)) {
				if (!BIT(_hoops_ACCI->flags, LSF_BITS16) || /* _hoops_PSP _hoops_CCCI 16-_hoops_IGRH _hoops_SCCI */
					BIT(nr->_hoops_AHP->flags, _hoops_SRPI) ||
					ANYBIT(_hoops_ACCI->flags, LSF_COMPLEX_ANYBITS))
					*_hoops_RGHRC = (_hoops_IGAI|_hoops_IRPI);
			}
		}
	}

	_hoops_RACR = _hoops_AACR(nr, &(*_hoops_PICI), &dl, &_hoops_CHGI, OGL_DL_SEGMENT_TREE);
	if (!_hoops_RACR) {
		if (!_hoops_GSCI (nr, dl, _hoops_CHGI, null, &_hoops_IICI, &_hoops_CICI))
			*_hoops_RGHRC = _hoops_RSCI;
	}
	if (_hoops_HICI) {
		*_hoops_HICI = 0;
		if (BIT (_hoops_IICI, T_FACES))
			*_hoops_HICI |= _hoops_PGRI|_hoops_ACIP;
		if (ANYBIT (_hoops_IICI, _hoops_PSRI))
			*_hoops_HICI |= _hoops_IGAI;
		if (ANYBIT (_hoops_IICI, T_ANY_POLYGON_EDGE))
			*_hoops_HICI |= _hoops_ACIP;
		if (BIT (_hoops_IICI, T_LINES))
			*_hoops_HICI |= _hoops_IRPI;
		if (ANYBIT (_hoops_IICI, T_MARKERS|T_VERTICES))
			*_hoops_HICI |= _hoops_HCIP|_hoops_RGPI;
	}

	if (_hoops_RACR)
		*_hoops_RGHRC = _hoops_RSCI;
}



local Action_Mask
_hoops_CSCI (_hoops_GACR const *dl)
{
	OGL_Display_List const *odl = (OGL_Display_List const *)dl->list;
	Action_Mask mask;

	mask = dl->action_mask;
	if (odl->item._hoops_ACGI._hoops_ARRI)
		mask |= _hoops_PGRI;
	if (odl->item._hoops_ACGI._hoops_AGAI)
		mask |= _hoops_IGAI;
	if (odl->item._hoops_ACGI._hoops_GGAI)
		mask |= _hoops_PSIP;
	if (odl->item._hoops_ACGI._hoops_RGAI)
		mask |= (_hoops_SSCI | _hoops_IGAI);
	if (odl->item._hoops_ACGI._hoops_CAPI)
		mask |= _hoops_IRPI;
	if (odl->item._hoops_ACGI._hoops_RCII)
		mask |= _hoops_SIII;
	if (odl->item._hoops_ACGI._hoops_ICARC)
		mask |= _hoops_RGPI;
	if (odl->item._hoops_ACGI._hoops_GAAI)
		mask |= _hoops_HCIP;
	return mask;
}


/*
 * _hoops_SRAC
 */
local bool
_hoops_GGSI(
		Net_Rendition const &		nr,
		_hoops_GACR **				_hoops_PICI,
		unsigned Integer32 *		mask,
		bool						_hoops_IHGI)
{
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	OGLData *					_hoops_CSRGR = OGLD(dc);
	_hoops_GACR *				dl;
	OGL_Display_List *			_hoops_CHGI;
	bool 						_hoops_RACR;
	bool 						_hoops_ARSI;
	Action_Mask					_hoops_RGSI = 0;
	Action_Mask					_hoops_RRSI = 0;
	int							_hoops_HSHI, _hoops_IICI = 0, _hoops_CICI = 0;

	_hoops_AGHRC("begin_display_list");

	/* _hoops_RH _hoops_HSPR _hoops_ICHRR _hoops_PGHRC _hoops_AA _hoops_HAR _hoops_GHAA _hoops_RPP _hoops_SR _hoops_CHR _hoops_HHPS _hoops_IRS _hoops_ISII
	 * "_hoops_CPAP" _hoops_AIRI _hoops_HIGR */
	if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT) {
		if (BIT(nr->_hoops_ARA->_hoops_PRSI.options, _hoops_HRSI) ||
			BIT(dc->flags, _hoops_IRSI)) {
			*mask = _hoops_RAPI;
			return false;
		}
		if (ANYBIT (nr->current, _hoops_CRSI | _hoops_SRSI) &&
			(dc->_hoops_IPCI->_hoops_CHCI != segment_render)) {
			*mask = _hoops_RAPI;
			return false;
		}
	}

	_hoops_RACR = _hoops_AACR(nr, &(*_hoops_PICI), &dl, &_hoops_CHGI, OGL_DL_SEGMENT_TREE);
	if (_hoops_CSRGR->_hoops_CIGI)
		_hoops_HPSGC (_hoops_CSRGR);

	_hoops_HSHI = nr->_hoops_RGP;
	if (!BIT(nr->transform_rendition->flags,_hoops_GRHH))
		_hoops_HSHI &= ~(T_LIGHTS_FOR_FACES | T_LIGHTS_FOR_EDGES | T_LIGHTS_FOR_MARKERS);
	if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES)) {
		_hoops_HSHI |= _hoops_GPA;
		if (_hoops_CPGI(_hoops_RRGH)) {
			_hoops_HSHI &= ~(T_FACES);
			_hoops_HSHI |= nr->_hoops_ARA->_hoops_CICP._hoops_RGP & (T_FACES);
		}
	}

	Color_Object _hoops_PCGS = 0;
	if (_hoops_RRGH->locks.color) {
		for (int i = 0 ; i < _hoops_IIGRA ; i++) {
			_hoops_PCGS |= (_hoops_RRGH->locks._hoops_HAA[i] & 0x1) << i;
		}
	}

	if (!_hoops_RACR) {
		if (!_hoops_GSCI (nr, dl, _hoops_CHGI, &_hoops_HSHI, &_hoops_IICI, &_hoops_CICI)) {
			if (_hoops_CHGI->item._hoops_ACGI._hoops_ARRI ||
				_hoops_CHGI->item._hoops_ACGI._hoops_AGAI ||
				_hoops_CHGI->item._hoops_ACGI._hoops_GGAI ||
				_hoops_CHGI->item._hoops_ACGI._hoops_RGAI ||
				_hoops_CHGI->item._hoops_ACGI._hoops_CAPI ||
				_hoops_CHGI->item._hoops_ACGI._hoops_RCII ||
				_hoops_CHGI->item._hoops_ACGI._hoops_GAAI ||
				_hoops_CHGI->item._hoops_ACGI._hoops_ICARC ) {
				if (dl->_hoops_GASI) {
					//_hoops_HCGI'_hoops_GRI _hoops_HRCI _hoops_PAII _hoops_RASI, _hoops_HIH _hoops_HAR _hoops_GPHP _hoops_RPHP
					if (!BIT (dl->_hoops_PRRI, _hoops_AASI)) {
						*dl->_hoops_GASI->backlink = dl->_hoops_GASI->next;
						_hoops_HPRH (dl->_hoops_GASI); //_hoops_GRS _hoops_PASI _hoops_AASA _hoops_RHIR _hoops_IS _hoops_HASI
					}
				}
				*dl->backlink = dl->next;
				_hoops_HPRH (dl); //_hoops_GRS _hoops_PASI _hoops_AASA _hoops_RHIR _hoops_IS _hoops_HASI
				_hoops_RACR = _hoops_AACR(nr, &(*_hoops_PICI), &dl, &_hoops_CHGI, OGL_DL_SEGMENT_TREE);
				ASSERT (_hoops_RACR);
			}
			else {
				_hoops_CHGI->item._hoops_ACGI._hoops_RGP = 0;
				_hoops_RACR = true;
			}
		}
		else {
			/* _hoops_IASI _hoops_CASI _hoops_GH _hoops_IIGR _hoops_AIRI _hoops_HIGR _hoops_GPGA _hoops_GPP _hoops_PGAP _hoops_SASI _hoops_SIH (_hoops_RPP _hoops_GII) _hoops_AGRP */
			OGL_Display_List *_hoops_GPSI;
			OGL_Display_List_List *list;
			_hoops_GRGGI *glist;
			Geometry *g;

			if (dl->_hoops_GASI &&
				!BIT (dl->_hoops_PRRI, _hoops_AASI)) {
				/* _hoops_SR _hoops_HS _hoops_IRS _hoops_HCH _hoops_ICH _hoops_AIRI _hoops_HIGR _hoops_SGS _hoops_HRGR _hoops_IRS _hoops_RPSI _hoops_IIGR _hoops_RGR _hoops_HCGI,
				 * _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SCH _hoops_APSI _hoops_IHHH _hoops_IS _hoops_PPSI _hoops_PA _hoops_GPP _hoops_RH
				 * _hoops_SGSI _hoops_HIGR _hoops_IH _hoops_SCH _hoops_IS _hoops_HPSI _hoops_CCA */
				int _hoops_IPSI = 0, _hoops_CPSI = 0;
				if (!_hoops_GSCI (nr, dl->_hoops_GASI,
						(OGL_Display_List *)dl->_hoops_GASI->list, null, &_hoops_IPSI, &_hoops_CPSI)) {
					ASSERT (dl->_hoops_GASI->_hoops_GSAI != DL_FLAG_INVALID); //_hoops_PAHA'_hoops_RA _hoops_SHH _hoops_SSRR
					dl->action_mask |= dl->_hoops_GASI->action_mask;
				}
				_hoops_IICI |= _hoops_IPSI;
				_hoops_CICI |= _hoops_CPSI;
			}

			if (BIT (_hoops_CHGI->item._hoops_ACGI.flags, OGL_SEGDL_HAS_EXPLICIT_VISIBLE))
				_hoops_HSHI |= (T_EDGES|T_FACES|T_VERTICES);

			if (!BIT (_hoops_HSHI, T_FACES))
				_hoops_IICI &= ~T_LIGHTS_FOR_FACES;
			if (!ANYBIT (_hoops_HSHI, _hoops_PSRI)) 
				_hoops_IICI &= ~T_LIGHTS_FOR_EDGES;
			if (!BIT (_hoops_HSHI, T_VERTICES))
				_hoops_IICI &= ~T_LIGHTS_FOR_MARKERS;

			if (BIT (nr->_hoops_RGP, T_FACES) &&
				ANYBIT (_hoops_IICI, T_FACES|T_LIGHTS_FOR_FACES)) {
				list = _hoops_CHGI->item._hoops_ACGI._hoops_ARRI;
				if (list) {
					while ((_hoops_GPSI = list->RemoveFirst()) != null)
						HD_Queue_Destroy_List (_hoops_GPSI, true);
				}
				glist = _hoops_CHGI->item._hoops_ACGI._hoops_CRPRC;
				if (glist) {
					while ((g = glist->RemoveFirst()) != null)
						_hoops_HPRH (g);
					delete glist;
					_hoops_CHGI->item._hoops_ACGI._hoops_CRPRC = null;
				}
				dl->action_mask |= _hoops_PGRI;
				_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(T_FACES|T_LIGHTS_FOR_FACES);
			}
			/* _hoops_IH _hoops_SPPR, _hoops_RPP _hoops_GHSI (_hoops_HIH _hoops_HAR _hoops_HCR) _hoops_RHSI _hoops_PAR _hoops_PA _hoops_RRAI */
			if (ANYBIT (nr->_hoops_RGP, _hoops_PSRI) &&
				(ANYBIT (_hoops_CICI, _hoops_PSRI) ||
				 ANYBIT (_hoops_IICI, _hoops_PSRI|T_LIGHTS_FOR_EDGES))) {
				list = _hoops_CHGI->item._hoops_ACGI._hoops_AGAI;
				if (list) {
					while ((_hoops_GPSI = list->RemoveFirst()) != null)
						HD_Queue_Destroy_List (_hoops_GPSI, true);
				}
				list = _hoops_CHGI->item._hoops_ACGI._hoops_GGAI;
				if (list) {
					while ((_hoops_GPSI = list->RemoveFirst()) != null)
						HD_Queue_Destroy_List (_hoops_GPSI, true);
				}
				glist = _hoops_CHGI->item._hoops_ACGI._hoops_SRPRC;
				if (glist) {
					while ((g = glist->RemoveFirst()) != null)
						_hoops_HPRH (g);
					delete glist;
					_hoops_CHGI->item._hoops_ACGI._hoops_SRPRC = null;
				}
				dl->action_mask |= _hoops_IGAI;
				_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(_hoops_PSRI|T_LIGHTS_FOR_EDGES);
			}
			if (BIT (_hoops_HSHI, _hoops_GPA) &&
				ANYBIT (_hoops_IICI, _hoops_GPA)) {
				list = _hoops_CHGI->item._hoops_ACGI._hoops_RGAI;
				if (list) {
					while ((_hoops_GPSI = list->RemoveFirst()) != null)
						HD_Queue_Destroy_List (_hoops_GPSI, true);
				}
				dl->action_mask |= _hoops_RSRI;
				_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(_hoops_GPA);
			}
			if (BIT (nr->_hoops_RGP, T_LINES) &&
				ANYBIT (_hoops_IICI, T_LINES)) {
				list = _hoops_CHGI->item._hoops_ACGI._hoops_CAPI;
				if (list) {
					while ((_hoops_GPSI = list->RemoveFirst()) != null)
						HD_Queue_Destroy_List (_hoops_GPSI, true);
				}
				dl->action_mask |= _hoops_IRPI;
				_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(T_LINES);
			}
			if (BIT (nr->_hoops_RGP, T_VERTICES) &&
				ANYBIT (_hoops_IICI, T_VERTICES|T_LIGHTS_FOR_MARKERS)) {
				list = _hoops_CHGI->item._hoops_ACGI._hoops_ICARC;
				if (list) {
					while ((_hoops_GPSI = list->RemoveFirst()) != null)
						HD_Queue_Destroy_List (_hoops_GPSI, true);
				}
				glist = _hoops_CHGI->item._hoops_ACGI._hoops_HGHRC;
				if (glist) {
					while ((g = glist->RemoveFirst()) != null)
						_hoops_HPRH (g);
					delete glist;
					_hoops_CHGI->item._hoops_ACGI._hoops_HGHRC = null;
				}
				dl->action_mask |= _hoops_RGPI;
				_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(T_VERTICES|T_LIGHTS_FOR_MARKERS);
			}
			if (BIT (nr->_hoops_RGP, T_MARKERS) &&
				BIT (_hoops_IICI, T_MARKERS)) {
				list = _hoops_CHGI->item._hoops_ACGI._hoops_GAAI;
				if (list) {
					while ((_hoops_GPSI = list->RemoveFirst()) != null)
						HD_Queue_Destroy_List (_hoops_GPSI, true);
				}
				dl->action_mask |= _hoops_HCIP;
				_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~(T_MARKERS);
			}
		}
	}
	if (_hoops_RACR) {
		_hoops_RGSI = _hoops_RAPI;
		_hoops_CHGI->item._hoops_ACGI.flags = 0;
		if (dc->_hoops_AHSI != null && BIT (dc->_hoops_AHSI->segment->_hoops_PHSI, _hoops_HHSI))
			_hoops_CHGI->item._hoops_ACGI.flags |= OGL_SEGDL_HAS_EXPLICIT_VISIBLE;
	}
	if (BIT (_hoops_CHGI->item._hoops_ACGI.flags, OGL_SEGDL_HAS_EXPLICIT_VISIBLE))
		_hoops_HSHI |= (T_EDGES|T_FACES|T_VERTICES);

	if (BIT (dl->_hoops_PRRI, _hoops_IHSI)) {
		dl->_hoops_PRRI &= ~_hoops_IHSI;
		_hoops_RGSI = _hoops_RAPI;
	}
	if (BIT(dc->flags, _hoops_CHSI)) {
		_hoops_RGSI &= (_hoops_RSCI|_hoops_SHSI);
		dl->_hoops_PRRI |= _hoops_IHSI;
	}
	_hoops_RGSI |= dl->action_mask;

	if (dl->_hoops_GASI &&
		!BIT (dl->_hoops_PRRI, _hoops_AASI) &&
		nr->_hoops_CPP->_hoops_PRH.style != _hoops_AIII &&
		nr->_hoops_CPP->_hoops_PRH._hoops_SRI != _hoops_PIII) {
		/* _hoops_ISCP _hoops_RPSI _hoops_HRGR _hoops_GISI _hoops_HGCR _hoops_RISI, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_AISI _hoops_PISI _hoops_CPAP _hoops_ISHP
		 * _hoops_HISI _hoops_IHSP _hoops_IISI _hoops_HRGR _hoops_CISI */
		_hoops_RGSI |= _hoops_CSCI (dl->_hoops_GASI);
	}

	dl->_hoops_GSAI = 0;
	if (dc->_hoops_AHSI != null && BIT (dc->_hoops_AHSI->segment->_hoops_PHSI, _hoops_HHSI))
		_hoops_HSHI |= (T_EDGES|T_FACES|T_VERTICES);
	if (BIT (_hoops_HSHI, T_FACES) &&
		ANYBIT (dl->_hoops_PRRI, _hoops_GCRI|_hoops_RCRI))
		_hoops_HSHI |= T_EDGES;
	if (!BIT(nr->transform_rendition->flags,_hoops_GRHH))
		_hoops_HSHI &= ~(T_LIGHTS_FOR_FACES | T_LIGHTS_FOR_EDGES | T_LIGHTS_FOR_MARKERS);
	if (!BIT (_hoops_HSHI, T_FACES)) {
		_hoops_RGSI &= ~_hoops_PGRI;
		if (!ANYBIT (_hoops_HSHI, T_ANY_POLYGON_EDGE))
			_hoops_RGSI &= ~_hoops_ACIP;
	}
	else if (BIT (_hoops_IICI, T_FACES))
		_hoops_RGSI |= _hoops_PGRI;
	if (ANYBIT (_hoops_IICI, T_ANY_POLYGON_EDGE|T_FACES))
		_hoops_RGSI |= _hoops_ACIP;
	if (!ANYBIT (_hoops_HSHI, _hoops_PSRI)) {
		_hoops_RGSI &= ~(_hoops_ASRI|_hoops_GHCI);
	}
	else if (ANYBIT (_hoops_IICI, _hoops_PSRI))
		_hoops_RGSI |= _hoops_ASRI|_hoops_GHCI;
	if (!BIT (_hoops_HSHI, T_LINES)) {
		if (!BIT (_hoops_HSHI, T_TEXT) ||
			nr->_hoops_SISI->transform != FT_FULL)
			_hoops_RGSI &= ~_hoops_IRPI;
	}
	else if (BIT (_hoops_IICI, T_LINES))
		_hoops_RGSI |= _hoops_IRPI;
	if (!BIT (_hoops_HSHI, T_VERTICES)) {
		_hoops_HSHI &= ~T_LIGHTS_FOR_MARKERS;
		_hoops_RGSI &= ~_hoops_RGPI;
	}
	else if (BIT (_hoops_IICI, T_VERTICES))
		_hoops_RGSI |= _hoops_RGPI;
	if (!BIT (_hoops_HSHI, T_MARKERS)) {
		_hoops_RGSI &= ~_hoops_HCIP;
	}
	else if (BIT (_hoops_IICI, T_MARKERS))
		_hoops_RGSI |= _hoops_HCIP;

	_hoops_ARSI = (
				ANYBIT (nr->_hoops_RGP, T_INTERIOR_SILHOUETTE_EDGES | _hoops_GCSI) &&
				!BIT (nr->_hoops_RGP, T_GENERIC_EDGES));
	if (_hoops_ARSI) {
		_hoops_RGSI |= _hoops_RCSI|_hoops_ACSI;
	}
	else {
		_hoops_RGSI &= ~(_hoops_HCCSP); //_hoops_GASA: _hoops_HAR _hoops_RCRR _hoops_PCPA _hoops_IS _hoops_AA _hoops_AHCA _hoops_RGR _hoops_SPR
		_hoops_RGSI &= ~(_hoops_RCSI|_hoops_ACSI);
		if (!ANYBIT (_hoops_RGSI, _hoops_PCSI) &&
			!ALLBITS (_hoops_RRGH->_hoops_CSA, _hoops_HCSI))
			_hoops_RGSI &= ~(_hoops_SHSI);
	}
	if (!BIT (_hoops_RGSI, _hoops_CIIP) &&
		!nr->_hoops_ARA->_hoops_APPI._hoops_SAR) {
		_hoops_RGSI &= ~(_hoops_AIIP|_hoops_SHIP);
	}

	if (_hoops_CHGI->item._hoops_ACGI._hoops_ARRI &&
		_hoops_CHGI->item._hoops_ACGI._hoops_ARRI->Count() &&
		BIT (_hoops_RGSI, _hoops_PGRI)) {
		if (!ANYBIT (_hoops_IICI, _hoops_PGRI))
			_hoops_RRSI |= _hoops_PGRI;
	}
	if (_hoops_CHGI->item._hoops_ACGI._hoops_CAPI &&
		_hoops_CHGI->item._hoops_ACGI._hoops_CAPI->Count() &&
		BIT (_hoops_RGSI, _hoops_CIIP)) {
		/* _hoops_RHHR _hoops_CCA _hoops_ICSI _hoops_CCSI _hoops_SCSI _hoops_CCA _hoops_HCH _hoops_GSSI _hoops_HSCH _hoops_RSSI. */
		if (nr->_hoops_ARA->_hoops_APPI._hoops_SAR)
			_hoops_RRSI |= _hoops_CIIP;
		else
			_hoops_RRSI |= _hoops_IRPI;
	}
	if (_hoops_CHGI->item._hoops_ACGI._hoops_AGAI &&
		_hoops_CHGI->item._hoops_ACGI._hoops_AGAI->Count() &&
		ANYBIT (_hoops_RGSI, _hoops_ASRI|_hoops_GHCI)) {
		/* _hoops_RHHR _hoops_CCA _hoops_CH _hoops_PPR _hoops_HCH _hoops_GSSI _hoops_RSSI _hoops_CPIC _hoops_RRH->_hoops_CIGC. */
		_hoops_RRSI |= (_hoops_ASRI|_hoops_GHCI);
	}
	if (_hoops_CHGI->item._hoops_ACGI._hoops_RGAI &&
		_hoops_CHGI->item._hoops_ACGI._hoops_RGAI->Count()) {
		_hoops_RRSI |= _hoops_RSRI;
	}
	//_hoops_GA'_hoops_RA _hoops_ASSI _hoops_SAIA _hoops_PPR _hoops_PSSI, _hoops_CR _hoops_SSIA _hoops_RRP _hoops_IS _hoops_GCGH _hoops_IASI _hoops_HSSI
	//_hoops_RPP (_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_CSSI &&
	//	_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_CSSI->_hoops_SGR()) {
	//	_hoops_ASSI |= _hoops_SSSI;
	//}
	//_hoops_RPP (_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_GGGC &&
	//	_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_GGGC->_hoops_SGR()) {
	//	_hoops_ASSI |= _hoops_RGGC;
	//}
	if (_hoops_CHGI->item._hoops_ACGI._hoops_RCII &&
		_hoops_CHGI->item._hoops_ACGI._hoops_RCII->Count()) {
		if (!ANYBIT (_hoops_RGSI, _hoops_ASRI|_hoops_GCGI)) {
			_hoops_RRSI |= _hoops_ACIP;
			if (!nr->_hoops_ARA->_hoops_APPI._hoops_SAR)
				_hoops_RRSI |= _hoops_ARCP;
		}
	}

	if (!_hoops_RGSI && !_hoops_IHGI) {
		_hoops_PPCI (nr, dl);
	}

	if (_hoops_RGSI) {
		/* _hoops_RAP _hoops_GH _hoops_RH _hoops_ICCI _hoops_IARI _hoops_RRGC, _hoops_PPR _hoops_AISI _hoops_SCH _hoops_GPP */
		OGL_Collector *_hoops_ARGC;

		ASSERT (!_hoops_CHGI->item._hoops_ACGI._hoops_ARRI || !_hoops_CHGI->item._hoops_ACGI._hoops_ARRI->Count() || !ANYBIT (_hoops_RGSI&~_hoops_RRSI, _hoops_PGRI));
		ASSERT (!_hoops_CHGI->item._hoops_ACGI._hoops_AGAI || !_hoops_CHGI->item._hoops_ACGI._hoops_AGAI->Count() || !ANYBIT (_hoops_RGSI&~_hoops_RRSI, _hoops_ASRI|_hoops_GHCI));
		ASSERT (!_hoops_CHGI->item._hoops_ACGI._hoops_CAPI || !_hoops_CHGI->item._hoops_ACGI._hoops_CAPI->Count() || !ANYBIT (_hoops_RGSI&~_hoops_RRSI, _hoops_CIIP));
		//_hoops_SAIA _hoops_PPR _hoops_PSSI _hoops_RRP _hoops_IS _hoops_GCGH _hoops_IASI _hoops_HSSI
		//_hoops_AGHR (!_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_CSSI || !_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_CSSI->_hoops_SGR() || !_hoops_AGGC (_hoops_PGGC&~_hoops_ASSI, _hoops_SSSI));
		//_hoops_AGHR (!_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_GGGC || !_hoops_HCGI->_hoops_IGCI._hoops_ISSI._hoops_GGGC->_hoops_SGR() || !_hoops_AGGC (_hoops_PGGC&~_hoops_ASSI, _hoops_RGGC));

		POOL_ZALLOC (_hoops_ARGC, OGL_Collector, dc->memory_pool);
		_hoops_ARGC->next = _hoops_CSRGR->_hoops_CIGI;
		_hoops_ARGC->nr = nr;
		_hoops_ARGC->mask = _hoops_RGSI;
		_hoops_ARGC->_hoops_RRSI = _hoops_RRSI;
		_hoops_ARGC->_hoops_PRGC = _hoops_RGSI;
		_hoops_ARGC->_hoops_IHGI = _hoops_IHGI;
		_hoops_CSRGR->_hoops_CIGI = _hoops_ARGC;
		_hoops_RGSI |= (_hoops_HRGC | _hoops_IRGC);
		_hoops_CSRGR->_hoops_ISCI++;
		if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_DISPLAY_LIST) ||
			ALLBITS (nr->_hoops_IRR->_hoops_CSA, _hoops_HCSI))
			_hoops_ARGC->_hoops_SIGI = true;  /* _hoops_CRGC _hoops_SRGC _hoops_GAGC */
	}
	*mask = _hoops_RGSI;
	return true;
}




local void _hoops_CRHI (
		int shift,
		int count,
		int *_hoops_SRHI)
{
	int i;
	int *_hoops_GAHI;

	_hoops_GAHI = _hoops_SRHI;
	for (i = 1; i < count - 1; i++) {
		*_hoops_GAHI++ = 0 + shift;
		*_hoops_GAHI++ = i + shift;
		*_hoops_GAHI++ = i + shift + 1;
	}
}


local void
_hoops_RAHI (
		int shift,
		int count,
		int *_hoops_SRHI)
{
	int i;
	int *_hoops_GAHI;

	_hoops_GAHI = _hoops_SRHI;
	*_hoops_GAHI++ = 0 + shift;
	for (i = 1; i*2 <= count; i++) {
		*_hoops_GAHI++ = i + shift;
		if (i*2 == count)
			break;
		*_hoops_GAHI++ = (count - i) + shift;
	}
}


struct _hoops_AAHI {
	Memory_Pool *	memory_pool;
	Point *			_hoops_PAHI; //_hoops_IH _hoops_HAHI-_hoops_IAHI
	int *			indices;
	int				_hoops_CAHI;
	int				_hoops_SAHI;
	int				_hoops_GPHI;
};

local void _hoops_RPHI (
		void *_hoops_PAPH,
		Integer32 _hoops_HAPH,
		Point const * p1, Point const * p2, Point const * _hoops_IAPH,
		Integer32 _hoops_ISPI, Integer32 _hoops_CSPI, Integer32 _hoops_SSPI,
		Intersection const * i1, Intersection const * i2, Intersection const * _hoops_SAPH)
{
	_hoops_AAHI *_hoops_APHI = (_hoops_AAHI *)_hoops_PAPH;
	int _hoops_PPHI = 0;

	if (_hoops_ISPI < 0 && -_hoops_ISPI > _hoops_PPHI)
		_hoops_PPHI = -_hoops_ISPI;
	if (_hoops_CSPI < 0 && -_hoops_CSPI > _hoops_PPHI)
		_hoops_PPHI = -_hoops_CSPI;
	if (_hoops_SSPI < 0 && -_hoops_SSPI > _hoops_PPHI)
		_hoops_PPHI = -_hoops_SSPI;

	if (_hoops_PPHI > _hoops_APHI->_hoops_CAHI) {
		Point *_hoops_HPHI;
		POOL_ZALLOC_ARRAY (_hoops_HPHI, _hoops_PPHI, Point, _hoops_APHI->memory_pool);
		if (_hoops_APHI->_hoops_CAHI > 0) {
			_hoops_AIGA (_hoops_APHI->_hoops_PAHI, _hoops_APHI->_hoops_CAHI, Point, _hoops_HPHI);
			FREE_ARRAY (_hoops_APHI->_hoops_PAHI, _hoops_APHI->_hoops_CAHI, Point);
		}
		_hoops_APHI->_hoops_PAHI = _hoops_HPHI;
		_hoops_APHI->_hoops_CAHI = _hoops_PPHI;
	}
	if (_hoops_APHI->_hoops_GPHI + 3 > _hoops_APHI->_hoops_SAHI) {
		int *_hoops_IPHI;
		POOL_ZALLOC_ARRAY (_hoops_IPHI, _hoops_APHI->_hoops_SAHI + 12, int, _hoops_APHI->memory_pool);
		if (_hoops_APHI->_hoops_SAHI > 0) {
			if (_hoops_APHI->_hoops_GPHI)
				_hoops_AIGA (_hoops_APHI->indices, _hoops_APHI->_hoops_GPHI, int, _hoops_IPHI);
			FREE_ARRAY (_hoops_APHI->indices, _hoops_APHI->_hoops_SAHI, int);
		}
		_hoops_APHI->indices = _hoops_IPHI;
		_hoops_APHI->_hoops_SAHI += 12;
	}

	if (_hoops_ISPI < 0)
		_hoops_APHI->_hoops_PAHI[-_hoops_ISPI - 1] = *p1; //_hoops_SHARC
	_hoops_APHI->indices[_hoops_APHI->_hoops_GPHI] = _hoops_ISPI;
	_hoops_APHI->_hoops_GPHI++;
	if (_hoops_CSPI < 0)
		_hoops_APHI->_hoops_PAHI[-_hoops_CSPI - 1] = *p2; //_hoops_SHARC
	_hoops_APHI->indices[_hoops_APHI->_hoops_GPHI] = _hoops_CSPI;
	_hoops_APHI->_hoops_GPHI++;
	if (_hoops_SSPI < 0)
		_hoops_APHI->_hoops_PAHI[-_hoops_SSPI - 1] = *_hoops_IAPH; //_hoops_SHARC
	_hoops_APHI->indices[_hoops_APHI->_hoops_GPHI] = _hoops_SSPI;
	_hoops_APHI->_hoops_GPHI++;
	UNREFERENCED (i1);
	UNREFERENCED (i2);
	UNREFERENCED (_hoops_SAPH);
	UNREFERENCED (_hoops_HAPH);
}


local void
_hoops_CPHI (
		Polygon const *p,
		_hoops_AAHI *_hoops_APHI)
{
	int i;
	int *face_list;

	POOL_ALLOC_ARRAY_CACHED (face_list, p->count + 1, int, _hoops_APHI->memory_pool);
	face_list[0] = p->count;
	for (i = 0; i < p->count; i++)
		face_list[i+1] = i;
	HI_Triangulate_Face_X (p->points, (Vector *)&p->plane, face_list,
						 face_list + p->count + 1, _hoops_RPHI,
						 (void alter *) _hoops_APHI);
	FREE_ARRAY (face_list, p->count + 1, int);
}


local void
_hoops_SPHI (
		Polygon const *p,
		_hoops_AAHI const *_hoops_APHI,
		int shift,
		int *_hoops_SRHI)
{
	int i;
	int *_hoops_GAHI = _hoops_SRHI;

	for (i = 0; i < _hoops_APHI->_hoops_GPHI; i++) {
		if (_hoops_APHI->indices[i] < 0)
			*_hoops_GAHI++ = -_hoops_APHI->indices[i] - 1 + shift + p->count;
		else
			*_hoops_GAHI++ = _hoops_APHI->indices[i] + shift;
	}
}



local _hoops_GHHI alter *
_hoops_RHHI (_hoops_GHHI const *a, _hoops_HRPA const *mat)
{
	_hoops_GHHI alter *_hoops_AHHI = null;
	switch (a->type) {
		case _hoops_RIIP:
		case _hoops_GIIP:
		case _hoops_GRCP:
		case _hoops_RRCP: {
			Circular_Arc alter *_hoops_PAGR;
			ZALLOC (_hoops_PAGR, Circular_Arc);
			_hoops_AHHI = (_hoops_GHHI alter *)_hoops_PAGR;
			_hoops_PAGR->type = a->type;
			_hoops_PAGR->arc_start = a->arc_start;
			_hoops_PAGR->_hoops_PHHI = a->_hoops_PHHI;
		} _hoops_HHHI;

		case _hoops_SGCP:
		case _hoops_CGCP: {
			Ellipse *_hoops_PAGR;
			Vector _hoops_IHHI, _hoops_CHHI;
			Point pt;

			if (_hoops_AHHI == null) {
				ZALLOC (_hoops_PAGR, Ellipse);
				_hoops_PAGR->type = _hoops_CGCP;
			}
			else
				_hoops_PAGR = (Ellipse *)_hoops_AHHI;

			_hoops_RPRA const *		elements = mat->elements;

			if (BIT (a->_hoops_RRHH, _hoops_SHHI)) {
				Vector _hoops_GIHI;
				_hoops_ARPA _hoops_RIHI;
				_hoops_AIHI const *	c;
				c = (_hoops_AIHI const *)a;		/* _hoops_IHRI _hoops_IH _hoops_PIHI _hoops_HAH */

				pt.x = c->center.x;
				pt.y = c->center.x;
				pt.z = 0;
				_hoops_PAGR->center.x = _hoops_HPRA (elements, pt);
				_hoops_PAGR->center.y = _hoops_IPRA (elements, pt);
				_hoops_PAGR->center.z = _hoops_CPRA (elements, pt);

				pt.x += c->radius;
				_hoops_PAGR->_hoops_GGHI.x = _hoops_HPRA (elements, pt) - _hoops_PAGR->center.x;
				_hoops_PAGR->_hoops_GGHI.y = _hoops_IPRA (elements, pt) - _hoops_PAGR->center.y;
				_hoops_PAGR->_hoops_GGHI.z = _hoops_CPRA (elements, pt) - _hoops_PAGR->center.y;

				pt.x = c->center.x;
				pt.y += c->radius;
				_hoops_PAGR->_hoops_RGHI.x = _hoops_HPRA (elements, pt) - _hoops_PAGR->center.x;
				_hoops_PAGR->_hoops_RGHI.y = _hoops_IPRA (elements, pt) - _hoops_PAGR->center.y;
				_hoops_PAGR->_hoops_RGHI.z = _hoops_CPRA (elements, pt) - _hoops_PAGR->center.y;

				_hoops_RIHI.a = _hoops_RIHI.b = _hoops_RIHI.d = 0;
				_hoops_RIHI.c = -1;
				HI_Compute_Transformed_Planes (1, &_hoops_RIHI, mat, &_hoops_PAGR->plane);
			}
			else {
				_hoops_GSPI const *e;
				e = (_hoops_GSPI *)a;
				_hoops_PAGR->center.x = _hoops_HPRA (elements, e->center);
				_hoops_PAGR->center.y = _hoops_IPRA (elements, e->center);
				_hoops_PAGR->center.z = _hoops_CPRA (elements, e->center);
				HI_Compute_Transformed_Vectors (1, &e->_hoops_GGHI, (float *)elements, &_hoops_PAGR->_hoops_GGHI);
				HI_Compute_Transformed_Vectors (1, &e->_hoops_RGHI, (float *)elements, &_hoops_PAGR->_hoops_RGHI);
				HI_Compute_Transformed_Planes (1, &e->plane, mat, &_hoops_PAGR->plane);
			}
			_hoops_AHHI = (_hoops_GHHI alter *)_hoops_PAGR;
		} break;

		default: {
			HE_ERROR (HEC_ELLIPSE, HES_PROCEDURAL_ERROR,
					"Unexpected case in compute transformed arc");
		} break;

	}
	_hoops_AHHI->key = -1;
	_hoops_AHHI->_hoops_HIHI = 1;
	return _hoops_AHHI;
}


#define _hoops_IGHRC(_hoops_GGGI,_hoops_RGGI) (\
	((_hoops_GGGI->color==null) && (_hoops_RGGI->color==null)) || \
	(_hoops_GGGI->color && _hoops_RGGI->color && (_hoops_GGGI->color->_hoops_GHA == _hoops_RGGI->color->_hoops_GHA)) \
)

local void
_hoops_CGHRC (
		Net_Rendition const & nr,
		Action_Mask mask,
		OGL_Display_List_Bin alter *_hoops_RRHA,
		OGL_Display_List_Bin_List alter *_hoops_CIHI,
		OGL_Display_List_Bin_List alter *_hoops_IAPI,
		bool *_hoops_GCHI,
		bool *_hoops_RCHI)
{
	Display_Context const * dc = nr->_hoops_SRA;
	_hoops_IPSGC *pair;
	_hoops_IPSGC *_hoops_SHAI[16];
	int _hoops_RIAI = 0, _hoops_AIAI = 0;
	int pass;
	Tristrip *ts = null;
	Polyedge *pe = null;
	Type type;
	Geometry const *g;
	int i, ii, _hoops_CCPI;
	int *_hoops_HCHI;
	_hoops_AAHI *_hoops_APHI;
	VList<_hoops_AAHI *> _hoops_ICHI(dc->memory_pool);
	_hoops_CCHI *_hoops_SCHI = null;
	struct _hoops_GSHI alter *_hoops_RSHI;
	int _hoops_ASHI = 0;
	bool _hoops_SAR = nr->_hoops_ARA->_hoops_APPI._hoops_SAR;
	bool _hoops_PSHI = false;
	_hoops_HRPA const *matrix = null;
	RGB const *_hoops_GPCP = null;
	_hoops_ACHR _hoops_HSHI;

	if (BIT (nr->transform_rendition->flags, _hoops_GRHH))
		_hoops_ASHI = nr->_hoops_RGP & (T_LIGHTS_FOR_FACES|T_LIGHTS_FOR_EDGES);

	*_hoops_GCHI = false;
	_hoops_SHAI[0] = _hoops_RRHA->_hoops_CRHA->PeekFirst();
	_hoops_RIAI = 1;

	_hoops_HSHI = nr->_hoops_RGP;
	if (!BIT (mask, _hoops_GCGI))
		_hoops_HSHI &= ~T_FACES;
	if (!BIT (mask, _hoops_ASRI))
		_hoops_HSHI &= ~T_ANY_POLYGON_EDGE;
	if (!ANYBIT (_hoops_HSHI, T_FACES|T_ANY_POLYGON_EDGE))
		return;

	for (pass = 0; pass < _hoops_RIAI; pass++) {
		if (BIT(_hoops_HSHI, T_FACES)) {
			POOL_ZALLOC (ts, Tristrip, dc->memory_pool);
			_hoops_ICAI (ts);
			if (BIT (nr->transform_rendition->flags, _hoops_GRHH) && BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES))
				ts->_hoops_SRHA |= DL_LIGHTING;
		}
		if (ANYBIT(_hoops_HSHI, T_ANY_POLYGON_EDGE)) {
			POOL_ZALLOC (pe, Polyedge, dc->memory_pool);
			_hoops_ICAI (pe);
			if (BIT (nr->transform_rendition->flags, _hoops_GRHH) && BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES))
				pe->_hoops_SRHA |= DL_LIGHTING;
		}
		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		for (;;) {
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (!pair)
				break;
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
			if (!_hoops_IGHRC (pair, _hoops_SHAI[pass])) {
				if (pass == 0) {
					//_hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SR _hoops_RRP _hoops_IS _hoops_GGCR _hoops_IRS _hoops_CCAH _hoops_PCAI
					if (!_hoops_IGHRC (pair, _hoops_SHAI[_hoops_AIAI])) {
						for (i = 0; i < _hoops_RIAI; i++) {
							if (_hoops_IGHRC (pair, _hoops_SHAI[i])) {
								_hoops_AIAI = i;
								break;
							}
						}
						if (i == _hoops_RIAI) {
							_hoops_SHAI[_hoops_RIAI] = pair;
							_hoops_RIAI++;
						}
					}
				}
				continue;
			}
			g = (Geometry const *)pair->geo;
			for (;;) { // _hoops_IH _hoops_GRR _hoops_ISHI
				type = g->type;
				if (ts)
					ts->face_count++;
				switch (type) {
					case _hoops_RCIP: {
						Polygon const *ptr = (Polygon const *)g;
						ASSERT (ptr->type == _hoops_RCIP);
						if (!BIT (ptr->_hoops_RRHH, _hoops_ARHH))
							HI_Find_Polygon_Plane ((Polygon alter *) ptr);
						if (ts) {
							POOL_ZALLOC (_hoops_APHI, _hoops_AAHI, dc->memory_pool);
							_hoops_APHI->memory_pool = dc->memory_pool;
							_hoops_CPHI (ptr, _hoops_APHI);
							if (_hoops_APHI->_hoops_GPHI != 0) {
								ts->point_count += ptr->count + _hoops_APHI->_hoops_CAHI;
								ts->total += _hoops_APHI->_hoops_GPHI;
								ts->_hoops_PHHA += _hoops_APHI->_hoops_GPHI / 3;
								_hoops_ICHI.AddLast (_hoops_APHI);
							}
							else {
								FREE (_hoops_APHI, _hoops_AAHI);
								_hoops_ICHI.AddLast (null);
							}
						}
						if (pe) {
							pe->point_count += ptr->count;
							pe->total += ptr->count + 1;
							pe->_hoops_PHHA++;
						}
					} break;

					case _hoops_GRCP:
					case _hoops_RRCP:
					case _hoops_SGCP:
					case _hoops_CGCP: {
						*_hoops_GCHI = true;

						if (_hoops_PSHI)
							_hoops_CSHI (g, type);

						if (!_hoops_SAR) {
							_hoops_GHHI const *a = (_hoops_GHHI const *)g;
							float start, end;
							int _hoops_HGII;

							if (!_hoops_SCHI)
								_hoops_SCHI = POOL_NEW(dc->memory_pool, _hoops_CCHI)(dc->memory_pool);
							POOL_ALLOC (_hoops_RSHI, struct _hoops_GSHI, dc->memory_pool);
							_hoops_RSHI->type = a->type;
							_hoops_RSHI->_hoops_IGII = _hoops_CCAI (pair->color, Color_EDGE);
							_hoops_RSHI->_hoops_CGII = _hoops_CCAI (pair->color, Color_FRONT);

							if (pair->_hoops_CPAI)
								a = _hoops_RHHI (a, &pair->_hoops_CPAI->matrix);
							_hoops_HGII = HD_Determine_Elliptical_Res (nr, a);
							if (BIT (a->_hoops_RRHH, _hoops_SHHI)) {
								Circular_Arc_Lite const *arc;

								arc = (Circular_Arc_Lite const *)a;
								start = arc->arc_start;
								end = arc->_hoops_PHHI;
								_hoops_RSHI->plane.a = _hoops_RSHI->plane.b = _hoops_RSHI->plane.d = 0;
								_hoops_RSHI->plane.c = -1;
							}
							else {
								Elliptical_Arc const *arc;

								arc = (Elliptical_Arc const *)a;
								start = arc->arc_start;
								end = arc->_hoops_PHHI;
								if (end < start)
									end += 1.0f;
								_hoops_RSHI->plane = arc->plane;
							}
							_hoops_RSHI->_hoops_SGII = 10 + _hoops_HGII;
							POOL_ALLOC_ARRAY_CACHED (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point, dc->memory_pool);
							_hoops_RSHI->count = HD_Generate_Elliptical_Points (nr, a, _hoops_HGII, _hoops_RSHI->points);
							ASSERT (_hoops_RSHI->count <= _hoops_RSHI->_hoops_SGII);
							if (_hoops_RSHI->count >= 2) {
								_hoops_SCHI->AddLast(_hoops_RSHI);
								if (ts) {
									ts->point_count += _hoops_RSHI->count;
									//_hoops_GRII _hoops_RRII _hoops_CHR _hoops_ARII _hoops_AGHH, _hoops_HIS _hoops_SSIA _hoops_HS
									//_hoops_IS _hoops_SHH _hoops_HSHA _hoops_GAR _hoops_IRS _hoops_PRII, _hoops_HRII _hoops_HSAR _hoops_GAR _hoops_IRS _hoops_IRII
									if (a->type == _hoops_RRCP)
										ts->total += 3 * (_hoops_RSHI->count - 2);
									else
										ts->total += _hoops_RSHI->count;
									ts->_hoops_PHHA++;
								}
								if (pe) {
									pe->point_count += _hoops_RSHI->count;
									pe->total += _hoops_RSHI->count + 1;
									pe->_hoops_PHHA++;
								}
								if (_hoops_ASHI)
									_hoops_RSHI->plane = a->plane;
							}
							else {
								FREE_ARRAY (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point);
								FREE (_hoops_RSHI, struct _hoops_GSHI);
								_hoops_RSHI = null;
							}
							if (pair->_hoops_CPAI) {
								ASSERT (a != (_hoops_GHHI const *)g);
								_hoops_HPRH (a);
								a = null;
							}
						}
						else {
							_hoops_PSHI = true;
							_hoops_CSHI (g, type);
						}
					} break;
				}
				if (!g)
					break;
				if (pair->single)
					break;
				g = g->next;
				if (!g || g->type != type)
					break;
			}
		}
		*_hoops_RCHI = _hoops_PSHI;
		if (ts && ts->point_count == 0) {
			if (_hoops_ISAI (ts) == 0)
				HI_Free_Tristrip (ts);
			ts = null;
		}
		if (pe && pe->point_count == 0) {
			if (_hoops_ISAI (pe) == 0)
				HI_Free_Polyedge (pe);
			pe = null;
		}
		if (!ts && !pe)
			continue;

		if (ts) {
			OGL_Display_List_Bin *_hoops_CRII = null;
			POOL_ALLOC_ARRAY_CACHED (ts->lengths, ts->_hoops_PHHA, int, dc->memory_pool);
			POOL_ALLOC_ARRAY_CACHED (ts->_hoops_AIHA, ts->total, int, dc->memory_pool);
			POOL_ZALLOC_ARRAY_CACHED (ts->face_indices, ts->total, int, dc->memory_pool);
			ts->_hoops_RAHH |= _hoops_AAHH;
			POOL_ALLOC_ARRAY_ALIGNED_CACHED (ts->points, ts->point_count, Point, 16, dc->memory_pool);
			ts->_hoops_RAHH |= _hoops_AIPI;
			if (_hoops_CCAI (_hoops_SHAI[pass]->color, Color_FRONT) != null) {
				POOL_ALLOC_ARRAY_CACHED (ts->_hoops_PCHA, ts->point_count, RGB, dc->memory_pool);
				ts->_hoops_RAHH |= _hoops_PIPI;
			}
			if (BIT (_hoops_ASHI, T_LIGHTS_FOR_FACES)) {
				POOL_ALLOC_ARRAY_ALIGNED_CACHED (ts->_hoops_PRHH, ts->face_count, _hoops_ARPA, 16, dc->memory_pool);
				ts->_hoops_RAHH |= _hoops_RCPI;
			}
			ts->point_count = 0;
			ts->total = 0;
			ts->_hoops_PHHA = 0;

			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			_hoops_CCPI = 0;
			_hoops_HCHI = ts->face_indices;
			for (;;) {
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				if (!pair)
					break;
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				if (!_hoops_IGHRC (pair, _hoops_SHAI[pass]))
					continue;
				g = (Geometry const *)pair->geo;
				if (pair->_hoops_CPAI)
					matrix = &pair->_hoops_CPAI->matrix;
				else
					matrix = null;
				if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA], M_DIFFUSE))
					_hoops_GPCP = null;
				else
					_hoops_GPCP = _hoops_CCAI (pair->color, Color_FRONT);
				if (g->type == _hoops_RCIP) {
					for (;;) {
						Polygon const *ptr = (Polygon const *)g;
						if (matrix) {
							float _hoops_APCP;
							Point *_hoops_PCAP = ts->points + ts->point_count;
							for (ii = 0; ii < ptr->count; ii++) {
								_hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, ptr->points[ii]);
								_hoops_PCAP->x = _hoops_HPRA(matrix->elements, ptr->points[ii]) * _hoops_APCP;
								_hoops_PCAP->y = _hoops_IPRA(matrix->elements, ptr->points[ii]) * _hoops_APCP;
								_hoops_PCAP->z = _hoops_CPRA(matrix->elements, ptr->points[ii]) * _hoops_APCP;
								_hoops_PCAP++;
							}
						}
						else
							_hoops_AIGA (ptr->points, ptr->count, Point, &ts->points[ts->point_count]);
						if (_hoops_GPCP) {
							for (ii = 0; ii < ptr->count; ii++)
								_hoops_RSAI (_hoops_GPCP, RGB, ts->_hoops_PCHA + ts->point_count + ii);
						}
						_hoops_APHI = _hoops_ICHI.RemoveFirst ();
						if (_hoops_APHI) {
							_hoops_SPHI (ptr, _hoops_APHI, ts->point_count, &ts->_hoops_AIHA[ts->total]);
							if (_hoops_APHI->_hoops_CAHI) {
								if (matrix) {
									float _hoops_APCP;
									Point *_hoops_PCAP = &ts->points[ts->point_count] + ptr->count;
									for (ii = 0; ii < _hoops_APHI->_hoops_CAHI; ii++) {
										_hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, _hoops_APHI->_hoops_PAHI[ii]);
										_hoops_PCAP->x = _hoops_HPRA(matrix->elements, _hoops_APHI->_hoops_PAHI[ii]) * _hoops_APCP;
										_hoops_PCAP->y = _hoops_IPRA(matrix->elements, _hoops_APHI->_hoops_PAHI[ii]) * _hoops_APCP;
										_hoops_PCAP->z = _hoops_CPRA(matrix->elements, _hoops_APHI->_hoops_PAHI[ii]) * _hoops_APCP;
										_hoops_PCAP++;
									}
								}
								else
									_hoops_AIGA (_hoops_APHI->_hoops_PAHI, _hoops_APHI->_hoops_CAHI, Point, &ts->points[ts->point_count] + ptr->count);
							}
							ts->point_count += ptr->count + _hoops_APHI->_hoops_CAHI;
							for (i = 0; i < _hoops_APHI->_hoops_GPHI / 3; i++)
								ts->lengths[ts->_hoops_PHHA + i] = 3;
							ts->_hoops_PHHA += _hoops_APHI->_hoops_GPHI / 3;
							ts->total += _hoops_APHI->_hoops_GPHI;
							FREE_ARRAY (_hoops_APHI->indices, _hoops_APHI->_hoops_SAHI, int);
							if (_hoops_APHI->_hoops_PAHI)
								FREE_ARRAY (_hoops_APHI->_hoops_PAHI, _hoops_APHI->_hoops_CAHI, Point);
							FREE (_hoops_APHI, _hoops_AAHI);
						}
						while (_hoops_HCHI < ts->face_indices + ts->total)
							*_hoops_HCHI++ = _hoops_CCPI;
						if (ts->_hoops_PRHH) {
							if (BIT(nr->transform_rendition->heuristics, _hoops_SASA))
								ts->_hoops_PRHH[_hoops_CCPI] = -ptr->plane;
							else
								ts->_hoops_PRHH[_hoops_CCPI] = ptr->plane;
						}
						_hoops_CCPI++;
						if (pair->single)
							break;
						g = g->next;
						if (!g || g->type != _hoops_RCIP)
							break;
					}
				}
			}
			/* _hoops_CHPI, _hoops_SRII, _hoops_GAII _hoops_PPR _hoops_RRII _hoops_AAPR _hoops_RAII _hoops_PPR _hoops_AAII _hoops_CIAA _hoops_PAII _hoops_HAII _hoops_HIGR */
			if (_hoops_SCHI && !_hoops_PSHI) {
				_hoops_SCHI->ResetCursor();
				while ((_hoops_RSHI = _hoops_SCHI->PeekCursor()) != null) {
					_hoops_AIGA (_hoops_RSHI->points, _hoops_RSHI->count, Point, &ts->points[ts->point_count]);
					if (_hoops_RSHI->type == _hoops_RRCP) {
						_hoops_CRHI (ts->point_count, _hoops_RSHI->count, &ts->_hoops_AIHA[ts->total]);
						ts->lengths[ts->_hoops_PHHA] = 3 * (_hoops_RSHI->count - 2);
						ts->total += ts->lengths[ts->_hoops_PHHA];
					}
					else {
						_hoops_RAHI (ts->point_count, _hoops_RSHI->count, &ts->_hoops_AIHA[ts->total]);
						ts->total += _hoops_RSHI->count;
						ts->lengths[ts->_hoops_PHHA] = _hoops_RSHI->count;
					}
					if (ts->_hoops_PRHH) {
						if (BIT(nr->transform_rendition->heuristics, _hoops_SASA))
							ts->_hoops_PRHH[_hoops_CCPI] = -_hoops_RSHI->plane;
						else
							ts->_hoops_PRHH[_hoops_CCPI] = _hoops_RSHI->plane;
					}
					if (_hoops_RSHI->_hoops_CGII) {
						ASSERT (ts->_hoops_PCHA != null);  //_hoops_IAII _hoops_RGR _hoops_PAHA'_hoops_RA _hoops_HS _hoops_CGI _hoops_SGHRC
						for (ii = 0; ii < _hoops_RSHI->count; ii++)
							_hoops_RSAI (_hoops_RSHI->_hoops_CGII, RGB, ts->_hoops_PCHA + ts->point_count + ii);
					}
					ts->point_count += _hoops_RSHI->count;
					_hoops_CCPI++;
					ts->_hoops_PHHA++;
					_hoops_SCHI->AdvanceCursor();
				}
			}

			pair = POOL_NEW(dc->memory_pool, _hoops_IPSGC)(_hoops_RRHA->nr, ts, null, null);

			if (ts->_hoops_PCHA != null)
				ts->_hoops_SRHA |= DL_VCOLORED_TRISTRIP;
			if (BIT (nr->_hoops_PSGI, T_FACES))
				ts->_hoops_SRHA |= DL_HAS_TRANSPARENCY;
			ts->_hoops_CARI |= _hoops_HPII;

			POOL_ZALLOC (_hoops_CRII, OGL_Display_List_Bin, dc->memory_pool);
			_hoops_CRII->_hoops_CRHA = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
			_hoops_CRII->_hoops_CRHA->AddFirst(pair);
			_hoops_CRII->nr = _hoops_RRHA->nr;

			_hoops_CIHI->AddFirst (_hoops_CRII);
		}
		if (pe) {
			OGL_Display_List_Bin *_hoops_GRPI = null;
			pe->lengths_allocated = pe->_hoops_PHHA;
			pe->_hoops_IPII = pe->total;
			pe->_hoops_CPII = pe->total;
			POOL_ALLOC_ARRAY_CACHED (pe->lengths, pe->lengths_allocated, int, dc->memory_pool);
			POOL_ALLOC_ARRAY_CACHED (pe->_hoops_AIHA, pe->_hoops_IPII, int, dc->memory_pool);
			POOL_ALLOC_ARRAY_CACHED (pe->_hoops_SPII, pe->_hoops_CPII, int, dc->memory_pool);
			pe->_hoops_RAHH |= _hoops_AAHH;
			POOL_ALLOC_ARRAY_ALIGNED_CACHED (pe->points, pe->point_count, Point, 16, dc->memory_pool);
			pe->_hoops_RAHH |= _hoops_AIPI;
			pe->_hoops_SPHA = pe->_hoops_PHHA;
			if (BIT (_hoops_ASHI, T_LIGHTS_FOR_EDGES)) {
				POOL_ALLOC_ARRAY_CACHED (pe->_hoops_RSHA, pe->_hoops_SPHA, Vector, dc->memory_pool);
				pe->_hoops_RAHH |= _hoops_GHII;
			}
			if (_hoops_CCAI (_hoops_SHAI[pass]->color, Color_EDGE) != null) {
				POOL_ALLOC_ARRAY_CACHED (pe->_hoops_PCHA, pe->point_count, RGB, dc->memory_pool);
				pe->_hoops_RAHH |= _hoops_PIPI;
			}
			pe->point_count = 0;
			pe->total = 0;
			pe->_hoops_PHHA = 0;

			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			for (;;) {
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				if (!pair)
					break;
				_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
				if (!_hoops_IGHRC (pair, _hoops_SHAI[pass]))
					continue;
				g = (Geometry const *)pair->geo;
				if (g->type == _hoops_RCIP) {
					for (;;) {
						Polygon const *ptr = (Polygon const *)g;
						if (pair->_hoops_CPAI)
							matrix = &pair->_hoops_CPAI->matrix;
						else
							matrix = null;
						if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_SAA], M_DIFFUSE))
							_hoops_GPCP = null;
						else
							_hoops_GPCP = _hoops_CCAI (pair->color, Color_EDGE);
						if (matrix) {
							float _hoops_APCP;
							Point *_hoops_PCAP = pe->points + pe->point_count;
							for (ii = 0; ii < ptr->count; ii++) {
								_hoops_APCP = 1.0f / _hoops_PHCP (matrix->elements, ptr->points[ii]);
								_hoops_PCAP->x = _hoops_HPRA(matrix->elements, ptr->points[ii]) * _hoops_APCP;
								_hoops_PCAP->y = _hoops_IPRA(matrix->elements, ptr->points[ii]) * _hoops_APCP;
								_hoops_PCAP->z = _hoops_CPRA(matrix->elements, ptr->points[ii]) * _hoops_APCP;
								_hoops_PCAP++;
							}
						}
						else
							_hoops_AIGA (ptr->points, ptr->count, Point, &pe->points[pe->point_count]);
						if (_hoops_GPCP) {
							for (ii = 0; ii < ptr->count; ii++)
								_hoops_RSAI (_hoops_GPCP, RGB, pe->_hoops_PCHA + pe->point_count + ii);
						}
						for (i = 0; i < ptr->count; i++) {
							pe->_hoops_SPII[pe->total + i] = pe->_hoops_PHHA;
							pe->_hoops_AIHA[pe->total + i] = pe->point_count + i;
						}
						pe->_hoops_SPII[pe->total + i] = pe->_hoops_PHHA;
						pe->_hoops_AIHA[pe->total + i] = pe->point_count; //_hoops_GGGR _hoops_RH _hoops_HAPR
						if (pe->_hoops_RSHA)
							_hoops_RSAI (&ptr->plane, Vector, &pe->_hoops_RSHA[pe->_hoops_PHHA]);
						pe->lengths[pe->_hoops_PHHA] = ptr->count + 1;
						pe->point_count += ptr->count;
						pe->total += ptr->count + 1;
						pe->_hoops_PHHA++;
						if (pair->single)
							break;
						g = g->next;
						if (!g || g->type != _hoops_RCIP)
							break;
					}
				}
			}
			/* _hoops_CHPI, _hoops_SRII, _hoops_GAII _hoops_PPR _hoops_RRII _hoops_AAPR _hoops_RAII _hoops_PPR _hoops_AAII _hoops_CIAA _hoops_PAII _hoops_HAII _hoops_HIGR */
			if (_hoops_SCHI && !_hoops_PSHI) {
				_hoops_SCHI->ResetCursor();
				while ((_hoops_RSHI = _hoops_SCHI->PeekCursor()) != null) {
					_hoops_AIGA (_hoops_RSHI->points, _hoops_RSHI->count, Point, &pe->points[pe->point_count]);
					for (i = 0; i < _hoops_RSHI->count; i++) {
						pe->_hoops_SPII[pe->total + i] = pe->_hoops_PHHA;
						pe->_hoops_AIHA[pe->total + i] = pe->point_count + i;
					}
					pe->_hoops_SPII[pe->total + i] = pe->_hoops_PHHA;
					pe->_hoops_AIHA[pe->total + i] = pe->point_count; //_hoops_GGGR _hoops_RH _hoops_HAPR
					if (pe->_hoops_RSHA)
						_hoops_RSAI (&_hoops_RSHI->plane, Vector, &pe->_hoops_RSHA[pe->_hoops_PHHA]);
					pe->lengths[pe->_hoops_PHHA] = _hoops_RSHI->count + 1;
					if (_hoops_RSHI->_hoops_IGII) {
						ASSERT (pe->_hoops_PCHA != null);  //_hoops_IAII _hoops_RGR _hoops_PAHA'_hoops_RA _hoops_HS _hoops_CGI _hoops_SGHRC
						for (ii = 0; ii < _hoops_RSHI->count; ii++)
							_hoops_RSAI (_hoops_RSHI->_hoops_IGII, RGB, pe->_hoops_PCHA + pe->point_count + ii);
					}
					pe->point_count += _hoops_RSHI->count;
					pe->total += _hoops_RSHI->count + 1;
					pe->_hoops_PHHA++;
					_hoops_SCHI->AdvanceCursor();
				}
			}

			pair = POOL_NEW(dc->memory_pool, _hoops_IPSGC)(_hoops_RRHA->nr, pe, null, null);

			pe->_hoops_SPHA = pe->_hoops_PHHA;
			if (pe->_hoops_PCHA != null)
				pe->_hoops_SRHA |= DL_VCOLORED_TRISTRIP;
			pe->_hoops_CARI |= _hoops_HPII;
			if (BIT (nr->_hoops_PSGI, T_EDGES))
				pe->_hoops_SRHA |= DL_HAS_TRANSPARENCY;

			POOL_ZALLOC( _hoops_GRPI, OGL_Display_List_Bin, dc->memory_pool);
			_hoops_GRPI->_hoops_CRHA = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
			_hoops_GRPI->_hoops_CRHA->AddFirst(pair);
			_hoops_GRPI->nr = _hoops_RRHA->nr;

			_hoops_IAPI->AddFirst (_hoops_GRPI);
		}

		if (_hoops_SCHI) {
			while ((_hoops_RSHI = _hoops_SCHI->RemoveFirst()) != null) {
				FREE_ARRAY (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point);
				FREE (_hoops_RSHI, struct _hoops_GSHI);
			}
			delete _hoops_SCHI;
			_hoops_SCHI = null;
		}
		//_hoops_GGR _hoops_RH _hoops_GSSR _hoops_AGIR, _hoops_SR _hoops_PPPPR'_hoops_RA _hoops_RHHR _hoops_RH _hoops_GRHRC _hoops_HCPH _hoops_CAPP _hoops_PGGA
		//_hoops_SAII _hoops_GRS _hoops_HS _hoops_RPII _hoops_CGI _hoops_IS _hoops_RH _hoops_GPII
		if (ts) {
			if (_hoops_ISAI (ts) == 0)
				HI_Free_Tristrip (ts);
			ts = null;
		}
		if (pe) {
			if (_hoops_ISAI (pe) == 0)
				HI_Free_Polyedge (pe);
			pe = null;
		}
	}
}


local bool
_hoops_HSRI (
		Net_Rendition const &nr,
		Line_Rendition const &_hoops_GHP,
		Polyedge const *pe,
		int weight)
{
	Display_Context const *		dc = nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	_hoops_IAPA const *_hoops_CAPA = null;

	if (BIT (nr->_hoops_PSGI, T_EDGES) &&
		nr->_hoops_CPP->_hoops_PRH.style != _hoops_AIII &&
		nr->_hoops_CPP->_hoops_PRH._hoops_SRI != _hoops_PIII &&
		(!pe || !BIT (pe->_hoops_SRHA, DL_3D_TRANSPARENCY)))
		return true;

	if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)&&
		weight==1 &&
		!BIT(dc->_hoops_PGCC.flags, _hoops_SPPGH))
		return true;

	if (nr->transform_rendition->_hoops_HCHH &&
		!_hoops_CSRGR->_hoops_PPHGC)
		return true;

	if (pe && pe->_hoops_CCHA)
		return true;

	if (_hoops_GAPI (_hoops_CSRGR, _hoops_GHP, weight))
		return true;

	/* _hoops_RCA _hoops_CAH _hoops_HCGC */
	if (BIT (_hoops_IHCR->flags, _hoops_GRHH) && 
		BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES)) {

		if (!BIT (_hoops_IHCR->flags, _hoops_PRIR))
			return true;

		if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GCP) &&
			_hoops_GHP->_hoops_AGP) {
			_hoops_AS const *light;

			if (!_hoops_CSRGR->_hoops_IARGC)
				return true;
			light = _hoops_GHP->_hoops_AGP->_hoops_CGR;
			while (light != null) {
				if (light->_hoops_PRR != _hoops_H)
					return true;
				light = light->next;
			}
		}
	}

	if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = _hoops_IHCR->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				return true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				return true;
		}
	}
	return false;
}


local void
_hoops_HIII (
		Net_Rendition const & nr,
		_hoops_GACR alter *dl,
		bool _hoops_IHGI)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLD(dc);
	OGL_Display_List *_hoops_CHGI = (OGL_Display_List *)dl->list;
	bool _hoops_AHAI = true;

	if (_hoops_CSRGR->_hoops_CIGI->_hoops_IIII) {
		_hoops_IPSGC *pair;
		float weight;
		_hoops_AIGI *list;
		bool _hoops_GIGI = false;

		list = _hoops_CSRGR->_hoops_CIGI->_hoops_IIII;
		_hoops_CSRGR->_hoops_CIGI->_hoops_IIII = null;
		_hoops_AHAI = false;

		weight = nr->_hoops_RHP->weight;
		if (weight < 0)
			weight = (int)(HD_Compute_Generic_Size (nr, nr->_hoops_RHP->_hoops_PHP, nr->_hoops_RHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);

		//_hoops_CIP _hoops_HSSP _hoops_SPPR _hoops_PAH'_hoops_RA _hoops_PHHR _hoops_RHIR _hoops_RH _hoops_GSSR _hoops_ACRI _hoops_RRGR, _hoops_PGGA _hoops_SSIA _hoops_RRP
		//_hoops_IS _hoops_SHH _hoops_GRSHR _hoops_IS _hoops_HSP _hoops_RH _hoops_SARA, _hoops_PPR _hoops_PRGI _hoops_RPP _hoops_RSSP _hoops_HRGR _hoops_ARP, _hoops_IIH _hoops_HRGR _hoops_PSP
		//_hoops_RIPS/_hoops_ISSC _hoops_IPPA _hoops_IS _hoops_RHSHP _hoops_CAPR _hoops_IS.
		if (ALLBITS (nr->_hoops_RGP, T_EDGES|T_LIGHTS_FOR_EDGES) &&
			nr->_hoops_RHP->_hoops_AGP != null)
			_hoops_GIGI = true;

		if (_hoops_GIGI ||
			_hoops_PHII (nr, weight)) {
			if (!_hoops_IHGI) {
				Geometry const *g;
				list->ResetCursor();
				while ((pair = list->PeekCursor()) != null) {
					list->AdvanceCursor();
					g = (Geometry const *)pair->geo;
					_hoops_CSRGR->_hoops_AHPI = !pair->single;
					if (g->type == _hoops_RCIP)
						draw_3d_polygon (pair->nr, (Polygon const *)g);
					else
						draw_3d_ellipse (pair->nr, (Ellipse const *)g);
					_hoops_CSRGR->_hoops_AHPI = false;
				}
			}
			dl->action_mask |= _hoops_SIII;
		}
		else {
			OGL_Display_List_Bin *_hoops_RRHA = null;
			OGL_Display_List *_hoops_CRPI = null;
			Tristrip alter *ts;
			Polyedge alter *pe;
			OGL_Display_List_Bin_List *_hoops_CIHI = POOL_NEW(dc->memory_pool, OGL_Display_List_Bin_List)(dc->memory_pool);
			OGL_Display_List_Bin_List *_hoops_IAPI = POOL_NEW(dc->memory_pool, OGL_Display_List_Bin_List)(dc->memory_pool);
			OGL_Display_List_Bin *_hoops_CRII = null;
			OGL_Display_List_Bin *_hoops_GRPI = null;
			bool _hoops_GCII = false;
			bool _hoops_PSHI = false;
			Action_Mask mask = _hoops_RAPI;

			//_hoops_GASA: _hoops_HPGR _hoops_SPR _hoops_PPSR _hoops_SR _hoops_SIGR _hoops_IS _hoops_HASIR _hoops_RGR _hoops_RIS.  _hoops_AIHH _hoops_AGIR 11635
			if (!ANYBIT (_hoops_CHGI->item._hoops_ACGI.flags,
				OGL_DL_BLESSED_SEGMENT | OGL_DL_BLESSED_GEOMETRY))
				_hoops_GIGI = true;

			ZALLOC (_hoops_RRHA, OGL_Display_List_Bin);
			_hoops_RRHA->nr = _hoops_CSRGR->_hoops_CIGI->nr;
			_hoops_RRHA->_hoops_CRHA = list;

			if (_hoops_CHGI &&
				_hoops_CHGI->item._hoops_ACGI._hoops_RCII) {
				_hoops_CRPI = _hoops_CHGI->item._hoops_ACGI._hoops_RCII->PeekFirst();
				if (_hoops_CRPI) {
					if (_hoops_CRPI->item._hoops_ACII._hoops_PCII != null) {
						mask &= ~_hoops_GCGI;
						if (!_hoops_IHGI &&
							BIT (nr->_hoops_RGP, T_FACES))
							_hoops_ICII (nr, _hoops_CHGI->item._hoops_ACGI._hoops_RCII, T_FACES);
					}
					if (_hoops_CRPI->item._hoops_ACII._hoops_GHPI != null) {
						mask &= ~_hoops_ASRI;
						if (!_hoops_IHGI &&
							BIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE))
							_hoops_ICII (nr, _hoops_CHGI->item._hoops_ACGI._hoops_RCII, T_ANY_POLYGON_EDGE);
					}
				}
			}

			_hoops_CGHRC (_hoops_RRHA->nr, mask, _hoops_RRHA, _hoops_CIHI, _hoops_IAPI, &_hoops_GCII, &_hoops_PSHI);
			if (_hoops_GCII) {
				dl->_hoops_PRRI |= _hoops_RPCGP;
				if (nr->_hoops_ARA->_hoops_APPI._hoops_SAR)
					dl->_hoops_PRRI |= _hoops_APCGP;
				else
					dl->_hoops_PRRI &= ~_hoops_APCGP;
			}


			if (_hoops_CIHI->Count() &&
				BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES) &&
				!ANYBIT (nr->transform_rendition->heuristics, _hoops_RSA))
				_hoops_GIGI = true;
			if (ANYBIT (dl->action_mask, _hoops_ACIP|_hoops_ARCP))
				_hoops_GIGI = true;
			if (HOOPS_WORLD->display_list_vram_usage >= HOOPS_WORLD->_hoops_PHARR ||
				_hoops_CSRGR->_hoops_CIGI->_hoops_SIGI)
				_hoops_GIGI = true;

			if (!_hoops_GIGI) {
				if (!_hoops_CRPI) {
					ZALLOC (_hoops_CRPI, OGL_Display_List);
					AGLM(_hoops_CRPI->_hoops_CSRGR = OGLD(dc));
					_hoops_CRPI->type = OGL_DL_SEGMENT_POLYGON;
					_hoops_CRPI->_hoops_GHRI = dc->_hoops_GHRI;
					if (_hoops_GCII) {
						_hoops_CRPI->item._hoops_ACII._hoops_PPPI = nr->_hoops_ARA->_hoops_APPI._hoops_PPPI;
						_hoops_CRPI->item._hoops_ACII._hoops_HPPI = nr->_hoops_ARA->_hoops_APPI._hoops_HPPI;
						_hoops_CRPI->item._hoops_ACII._hoops_IPPI = nr->_hoops_ARA->_hoops_APPI._hoops_IPPI;
						_hoops_CRPI->item._hoops_ACII._hoops_CPPI = nr->_hoops_ARA->_hoops_APPI._hoops_CPPI;
						_hoops_CRPI->item._hoops_ACII._hoops_SPPI = nr->_hoops_ARA->_hoops_APPI._hoops_SPPI;
					}
				}
				_hoops_CIHI->ResetCursor();
				while ((_hoops_CRII = _hoops_CIHI->PeekCursor()) != null) {
					_hoops_CIHI->AdvanceCursor();
					if (_hoops_CRII->_hoops_CRHA->Count()) {
						_hoops_CRII->_hoops_CHGI = _hoops_CHGI;
						_hoops_RRRI (_hoops_CRII->nr, null, _hoops_CRII);
						if (!_hoops_CRPI->item._hoops_ACII._hoops_PCII)
							_hoops_CRPI->item._hoops_ACII._hoops_PCII = POOL_NEW(dc->memory_pool, OGL_Display_List_List)(dc->memory_pool);
						_hoops_CRPI->item._hoops_ACII._hoops_PCII->AddFirst (_hoops_CRII->odl);
						_hoops_AHAI = true;
					}
				}
				_hoops_IAPI->ResetCursor();
				while ((_hoops_GRPI = _hoops_IAPI->PeekCursor()) != null) {
					_hoops_IAPI->AdvanceCursor();
					if (_hoops_GRPI->_hoops_CRHA->Count()) {
						_hoops_GRPI->_hoops_CHGI = _hoops_CHGI;
						really_draw_3d_polyedge (_hoops_GRPI->nr, _hoops_GRPI->nr->_hoops_RHP, null, _hoops_GRPI);
						if (!_hoops_CRPI->item._hoops_ACII._hoops_GHPI)
							_hoops_CRPI->item._hoops_ACII._hoops_GHPI = POOL_NEW(dc->memory_pool, OGL_Display_List_List)(dc->memory_pool);
						_hoops_CRPI->item._hoops_ACII._hoops_GHPI->AddFirst (_hoops_GRPI->odl);
						_hoops_AHAI = true;
					}
				}
				if (_hoops_CRPI->item._hoops_ACII._hoops_PCII ||
					_hoops_CRPI->item._hoops_ACII._hoops_GHPI) {
					if (!_hoops_CHGI->item._hoops_ACGI._hoops_RCII)
						_hoops_CHGI->item._hoops_ACGI._hoops_RCII = POOL_NEW(dc->memory_pool, OGL_Display_List_List)(dc->memory_pool);
					if (_hoops_CRPI != _hoops_CHGI->item._hoops_ACGI._hoops_RCII->PeekFirst())
						_hoops_CHGI->item._hoops_ACGI._hoops_RCII->AddFirst(_hoops_CRPI);
				}
				else
					FREE (_hoops_CRPI, OGL_Display_List);
				_hoops_CRPI = null;
			}

			if (_hoops_GIGI) {

				_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
				_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;
				dc->_hoops_SPA->modelling_matrix = null;
				dc->_hoops_SPA->color = null;

				/* _hoops_PGSA _hoops_CCII _hoops_GGR _hoops_HGAI _hoops_CCH */
				if (!_hoops_IHGI) {
					_hoops_CIHI->ResetCursor();
					while ((_hoops_CRII = _hoops_CIHI->PeekCursor()) != null) {
						_hoops_CIHI->AdvanceCursor();
						_hoops_CRII->_hoops_CRHA->ResetCursor();
						while ((pair = _hoops_CRII->_hoops_CRHA->PeekCursor()) != null) {
							ts = (Tristrip *)pair->geo;
							ts->_hoops_SRHA |= _hoops_SRHH;
							_hoops_RRRI (_hoops_CRII->nr, ts, null);
							_hoops_CRII->_hoops_CRHA->AdvanceCursor();
						}
					}
					_hoops_IAPI->ResetCursor();
					while ((_hoops_GRPI = _hoops_IAPI->PeekCursor()) != null) {
						_hoops_IAPI->AdvanceCursor();
						_hoops_GRPI->_hoops_CRHA->ResetCursor();
						while ((pair = _hoops_GRPI->_hoops_CRHA->PeekCursor()) != null) {
							pe = (Polyedge *)pair->geo;
							pe->_hoops_SRHA |= _hoops_SRHH;
							really_draw_3d_polyedge (_hoops_GRPI->nr, _hoops_GRPI->nr->_hoops_RHP, pe, null);
							_hoops_GRPI->_hoops_CRHA->AdvanceCursor();
						}
					}
				}
				dl->action_mask |= _hoops_SIII;

				dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
				dc->_hoops_SPA->color = _hoops_GGRI;
			}
			if (_hoops_PSHI) {
				Geometry const *g;

				_hoops_RRHA->_hoops_CRHA->ResetCursor();
				while ((pair = _hoops_RRHA->_hoops_CRHA->PeekCursor()) != null) {
					_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
					g = (Geometry const *)pair->geo;
					if (g->type == _hoops_RCIP)
						continue;
					_hoops_CSRGR->_hoops_AHPI = !pair->single;
					dc->_hoops_RAI = g;
					draw_3d_ellipse (pair->nr, (Ellipse const *)g);
					_hoops_CSRGR->_hoops_AHPI = false;
				}
				if (dl)
					dl->action_mask |= _hoops_ARCP;
			}
			while ((_hoops_CRII = _hoops_CIHI->RemoveFirst()) != null) {
				while ((pair = _hoops_CRII->_hoops_CRHA->RemoveFirst()) != null)
					delete pair;
				delete _hoops_CRII->_hoops_CRHA;
				_hoops_CRII->nr = null;
				_hoops_CRII->odl = null;
				FREE (_hoops_CRII, OGL_Display_List_Bin);
			}
			delete _hoops_CIHI;
			while ((_hoops_GRPI = _hoops_IAPI->RemoveFirst()) != null) {
				while ((pair = _hoops_GRPI->_hoops_CRHA->RemoveFirst()) != null)
					delete pair;
				delete _hoops_GRPI->_hoops_CRHA;
				_hoops_GRPI->nr = null;
				_hoops_GRPI->odl = null;
				FREE (_hoops_GRPI, OGL_Display_List_Bin);
			}
			delete _hoops_IAPI;

			_hoops_RRHA->nr = null;
			FREE (_hoops_RRHA, OGL_Display_List_Bin);
			_hoops_RRHA = null;
		}

		/* _hoops_SP _hoops_GH _hoops_IARI _hoops_HIGR _hoops_PPR _hoops_AGPI _hoops_PGPI/_hoops_SCII _hoops_IGPI */
		while ((pair = list->RemoveFirst()) != null)
			delete pair;
		delete list;
		_hoops_CSRGR->_hoops_CIGI->_hoops_IIII = 0;
	}

	if (_hoops_AHAI) {
		_hoops_ACHR _hoops_RGP = nr->_hoops_RGP;

		if (_hoops_CHGI &&
			_hoops_CHGI->item._hoops_ACGI._hoops_RCII &&
			ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
				_hoops_ICII (nr, _hoops_CHGI->item._hoops_ACGI._hoops_RCII, _hoops_RGP);
		}
	}
}


local int
_hoops_GSII (Geometry const *_hoops_RSII, bool single)
{
	Geometry const *g = _hoops_RSII;
	int _hoops_ASII = 0;
	int _hoops_PSII = 0;
	int type;

		type = g->type;
		switch (type) {
			case _hoops_HIIP:
			case _hoops_IIIP:  {
				Polyline const *ptr;
				do {
					ptr = (Polyline const *)g;
					_hoops_ASII += Abs(ptr->count);
					_hoops_PSII++;
					if (single)
						break;
					g = g->next;
				} while (g && g->type == type);
			} break;

			case _hoops_PIIP: {
				do {
					_hoops_ASII += 2;
					_hoops_PSII++;
					if (single)
						break;
					g = g->next;
				} while (g && g->type == type);
			} break;

			case _hoops_GIIP:
			case _hoops_RIIP:
			case _hoops_CHIP:{
				do {
					_hoops_ASII += 256;
					_hoops_PSII++;
					if (single)
						break;
					g = g->next;
				} while (g && g->type == type);
			} break;

			default:
			break;
	}
	return 12 * _hoops_ASII + 12 * _hoops_PSII;
}


local int
_hoops_RRHRC (Tristrip const *ts)
{
	int size;

	size = 16 * ts->total;
	if (ts->_hoops_ICHA || ts->_hoops_PRHH)
		size += 12 * ts->total;

	if (BIT (ts->_hoops_SRHA, _hoops_GGIA))
		size += ts->total * 2 * sizeof(_hoops_RSSH);
	else if (ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_CCHA)
		size += ts->total * ts->_hoops_GSSH->_hoops_GSHA * sizeof(_hoops_RSSH);
	return size;
}

local int
_hoops_ARHRC (Polyedge const *pe)
{
	int size;

	size = 16 * pe->total;
	if (pe->_hoops_ICHA)
		size += 12 * pe->total;

	if (BIT (pe->_hoops_SRHA, _hoops_GGIA))
		size += pe->total * 2 * sizeof(_hoops_RSSH);
	else if (pe->_hoops_CCHA)
		size += pe->total * pe->_hoops_GSHA * sizeof(_hoops_RSSH);
	return size;
}

local int
_hoops_PSSH (Polymarker const *pm)
{
	int size;

	size = 16 * pm->length;
	if (pm->_hoops_ICHA)
		size += 12 * pm->length;

	return size;
}

local bool
_hoops_HGRI (
	Net_Rendition const &		nr,
	unsigned Integer32			_hoops_SRHA,
	bool 						_hoops_CISP)
{
	Display_Context const *		dc = nr->_hoops_SRA;
	OGLData alter *				_hoops_CSRGR = OGLD (dc);
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HHA const &	matr = _hoops_SIGA->_hoops_CHA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_GRGH const &		_hoops_ACHI = nr->_hoops_IRR;

	if (_hoops_CSRGR->_hoops_HCPRC)
		return false;

	if (_hoops_CISP &&
		nr->_hoops_CPP->_hoops_PRH.style != _hoops_AIII &&
		nr->_hoops_CPP->_hoops_PRH._hoops_SRI != _hoops_PIII &&
		!BIT (_hoops_SRHA, DL_3D_TRANSPARENCY)) {
		if (matr->_hoops_IRIR < 1.0f ||
			(matr->_hoops_SCA && matr->_hoops_SCA->_hoops_HGA == 0 && !BIT(matr->_hoops_SCA->texture->_hoops_SCR, _hoops_PGA)))
			return true;
	}
	else if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
		return true;
	}
	else if ((BIT (_hoops_IHCR->flags, _hoops_GRHH) &&
		 !BIT (_hoops_IHCR->flags, _hoops_PRIR))) {
		return true;
	}
	if (_hoops_SIGA->pattern == FP_USER_DEFINED) {
		if (_hoops_SIGA->_hoops_PGPH != null && _hoops_SIGA->_hoops_PGPH->stipple) {
		}
		else if (_hoops_SIGA->_hoops_PGPH == null ||
				 _hoops_SIGA->_hoops_PGPH->height > 32 || _hoops_SIGA->_hoops_PGPH->width > 32 ||
				 _hoops_RIII(_hoops_SIGA->_hoops_PGPH->width) != _hoops_SIGA->_hoops_PGPH->width ||
				 _hoops_RIII(_hoops_SIGA->_hoops_PGPH->height) != _hoops_SIGA->_hoops_PGPH->height)
			return true;
	}
	if (BIT (_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_CIPRC) &&
		BIT (_hoops_ACHI->_hoops_CSA, _hoops_GSRC) &&
		matr->_hoops_SCA != null &&
		BIT(matr->_hoops_SCA->texture->_hoops_SCR, _hoops_RCRH) &&
		(matr->_hoops_SCA->texture->image->width > _hoops_CSRGR->_hoops_HPHGC ||
		 matr->_hoops_SCA->texture->image->height > _hoops_CSRGR->_hoops_HPHGC)) {
		return true;
	}
	if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = _hoops_IHCR->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				return true;
		}
		else {
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				return true;
		}
	}
	if (BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES) &&
		_hoops_SIGA->_hoops_AGP) {
		_hoops_AS const *light;

		/* _hoops_RAHCP _hoops_CAH _hoops_ISPR */
		if (BIT (_hoops_ACHI->_hoops_CSA, _hoops_SSA)) {
			if (!_hoops_CSRGR->_hoops_IARGC)
				return true;

			light = _hoops_SIGA->_hoops_AGP->_hoops_CGR;
			while (light != null) {
				if (light->_hoops_PRR != _hoops_H)
					return true;
				light = light->next;
			}
		}
	}
	return false;
}


local void
_hoops_HHGI (
		Net_Rendition const &nr,
		_hoops_GACR alter *dl,
		bool _hoops_IHGI)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLD(dc);
	OGL_Display_List_Bin *_hoops_RRHA;
	_hoops_IPSGC *pair;
	Tristrip alter *ts;
	_hoops_AIGI *list;
	OGL_Display_List *_hoops_CHGI = (OGL_Display_List alter *)dl->list;
	const int _hoops_PRHRC = 0x7fff;
	bool _hoops_CISP;
	bool _hoops_GIGI = false;
	bool _hoops_AHAI = true;
	bool _hoops_PIGI = false;
	bool _hoops_HIGI = false;

	if (_hoops_CSRGR->_hoops_CIGI->_hoops_RCGI) {
		OGL_Display_List_Bin_List *_hoops_SHGI = POOL_NEW(dc->memory_pool, OGL_Display_List_Bin_List)(dc->memory_pool);
		int _hoops_GCI, _hoops_HRHRC = 0;

		list = _hoops_CSRGR->_hoops_CIGI->_hoops_RCGI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			list->AdvanceCursor();

			ts = (Tristrip *) pair->geo;

			if (BIT (ts->face_attributes.flags, _hoops_IAGI) &&
				_hoops_CHGI && BIT (_hoops_CHGI->item._hoops_ACGI._hoops_PCGI, T_FACES)) {
					_hoops_PIGI = true;
					continue; // _hoops_RH _hoops_HCGI _hoops_AIAH _hoops_ICGI _hoops_RH _hoops_HHHA _hoops_CCGI
			}

			/* _hoops_IRHRC _hoops_RHIR _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_CRHH _hoops_CRHRC, _hoops_PPR _hoops_CAHA _hoops_GGSR _hoops_PGAP _hoops_SCGI _hoops_IS _hoops_GGCR _hoops_SCH _hoops_IS */
			_hoops_SHGI->ResetCursor();
			while ((_hoops_RRHA = _hoops_SHGI->PeekCursor()) != null) {
				bool _hoops_APACP = true;
				_hoops_IPSGC *_hoops_SRHRC = _hoops_RRHA->_hoops_CRHA->PeekFirst();
				Tristrip const *_hoops_GAHRC = (Tristrip const *) _hoops_SRHRC->geo;

				if (_hoops_RRHA->point_count + ts->total > _hoops_PRHRC)
					_hoops_APACP = false;
				if ((_hoops_SRHRC->color != null) != (pair->color != null))
					_hoops_APACP = false;
				if ( (_hoops_GAHRC->_hoops_GSSH && ts->_hoops_GSSH && _hoops_GAHRC->_hoops_GSSH->_hoops_GSHA != ts->_hoops_GSSH->_hoops_GSHA) || 
					(_hoops_GAHRC->_hoops_PAGI != null) != (ts->_hoops_PAGI != null) ||
					(_hoops_GAHRC->_hoops_GSSH && (_hoops_GAHRC->_hoops_PCHA != null) != (ts->_hoops_PCHA != null)) )
					_hoops_APACP = false;
				if (ts->face_attributes.flags != _hoops_GAHRC->face_attributes.flags)
					_hoops_APACP = false;
				if (_hoops_APACP)
					break;
				_hoops_SHGI->AdvanceCursor();
			}

			if (!_hoops_RRHA) {
				/* _hoops_CSH _hoops_PIS _hoops_SCGI _hoops_GSGI, _hoops_HIS _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SPR, _hoops_PPR _hoops_GGCR _hoops_IS _hoops_RSGI */
				ZALLOC (_hoops_RRHA, OGL_Display_List_Bin);
				_hoops_RRHA->_hoops_AGRI = ts->_hoops_SRHA & ~_hoops_GAHH;
				_hoops_RRHA->_hoops_GSHA = ts->_hoops_GSSH ? ts->_hoops_GSSH->_hoops_GSHA : 0;
				_hoops_RRHA->id = 0;
				/*_hoops_IPRPI: _hoops_SCGI->_hoops_CRSRR = _hoops_RAHRC(_hoops_SCII, _hoops_AAHRC, _hoops_GARI, _hoops_PAHRC);*/
				_hoops_SHGI->AddFirst(_hoops_RRHA);
				_hoops_RRHA->_hoops_CRHA = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
				_hoops_RRHA->nr = nr;
			}

			/* _hoops_RGPA _hoops_RH _hoops_CRHH _hoops_CRGR _hoops_RH _hoops_SCGI , _hoops_PPR _hoops_ARP _hoops_GII _hoops_ASGI _hoops_PIH.
			* _hoops_SAII _hoops_IIGR _hoops_RH _hoops_RRGP _hoops_HRGR _hoops_HGGC _hoops_CCA _hoops_RH _hoops_SSIS _hoops_IH _hoops_HA, _hoops_PHRI */
			_hoops_RRHA->_hoops_CRHA->AddFirst(pair);

			/* _hoops_HGCR _hoops_CRHH'_hoops_GRI _hoops_SCPH _hoops_RPR */
			_hoops_RRHA->point_count += ts->total; //_hoops_PCCP _hoops_AAPA _hoops_ASCR
			_hoops_RRHA->_hoops_HGAC += ts->total - 2*ts->_hoops_PHHA;
			_hoops_GCI = _hoops_RRHRC (ts);
			_hoops_RRHA->_hoops_GPGC += _hoops_GCI;
			_hoops_HRHRC += _hoops_GCI;
		}
		_hoops_CISP = BIT (nr->_hoops_PSGI, T_FACES);

		if (BIT (dl->_hoops_AGRI, DL_INSUFFICIENT_VRAM) ||
			ANYBIT (dl->action_mask, _hoops_PGRI))
			_hoops_GIGI = true;

		if (BIT (nr->transform_rendition->flags, _hoops_GRHH) && BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES)) {
			if (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI) ||
				!ANYBIT (nr->transform_rendition->heuristics, _hoops_RSA))
				_hoops_GIGI = true;
		}

		if (nr->_hoops_IHA->_hoops_CHA->texture[_hoops_RIA] &&
			(nr->_hoops_IHA->_hoops_CHA->texture[_hoops_RIA]->_hoops_PSR == _hoops_HSR ||
			nr->transform_rendition->_hoops_SPH->projection != _hoops_GHH))
			_hoops_GIGI = true;

		if (HOOPS_WORLD->display_list_vram_usage + _hoops_HRHRC > HOOPS_WORLD->_hoops_PHARR)
			_hoops_GIGI = true;

		while ((_hoops_RRHA = _hoops_SHGI->RemoveFirst()) != null) {
			_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
			_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;
			bool _hoops_HAHRC = false;
			bool _hoops_IAHRC, _hoops_CAHRC;
			int pass;

			_hoops_RRHA->_hoops_CRHA->ResetCursor();
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			ts = (Tristrip *) pair->geo;
			if (pair->_hoops_CPAI)
				_hoops_HAHRC = BIT (pair->_hoops_CPAI->matrix._hoops_RAGR, _hoops_CASA);
			if (_hoops_HGRI(nr, ts->_hoops_SRHA, _hoops_CISP))
				_hoops_GIGI = true;

			if (!BIT (_hoops_CHGI->item._hoops_ACGI.flags, OGL_DL_BLESSED_SEGMENT))
				_hoops_GIGI = true;

			if (!_hoops_GIGI) {
				_hoops_RRHA->_hoops_CHGI = _hoops_CHGI;
				if (BIT (ts->_hoops_SRHA, _hoops_GGIA)) {
					_hoops_CRRI (nr, null, _hoops_RRHA);
				}
				else
					_hoops_RRRI (nr, null, _hoops_RRHA);
				if (_hoops_RRHA->_hoops_AGRI == DL_FLAG_INVALID) {
					_hoops_GIGI = true;
				}
				else {
					if (_hoops_RRHA->odl) {
						if (!_hoops_CHGI->item._hoops_ACGI._hoops_ARRI)
							_hoops_CHGI->item._hoops_ACGI._hoops_ARRI = POOL_NEW(dc->memory_pool, OGL_Display_List_List)(dc->memory_pool);
						_hoops_CHGI->item._hoops_ACGI._hoops_ARRI->AddFirst(_hoops_RRHA->odl);
						if (BIT (_hoops_RRHA->odl->item.geometry._hoops_IRRI, _hoops_IAGI))
							_hoops_HIGI = true;
						_hoops_AHAI = true;
					}
				}
			}

			if (_hoops_GIGI) {
				_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~T_LIGHTS_FOR_FACES;
				_hoops_CAHRC = false;
				for (pass = 0; pass < 2; pass++) {
					_hoops_RRHA->_hoops_CRHA->ResetCursor();
					pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
					ts = (Tristrip *) pair->geo;
					_hoops_IAHRC = ((pass == 0) ? _hoops_HAHRC : !_hoops_HAHRC);

					_hoops_SAHRC (_hoops_CSRGR, nr->transform_rendition, _hoops_IAHRC);
					if (!_hoops_IHGI) {
						for (;;) {
							int _hoops_AICIP;

							pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
							if (!pair)
								break;
							ts = (Tristrip *)pair->geo;
							_hoops_AICIP = ts->_hoops_SRHA;
							if (!BIT (_hoops_CHGI->item._hoops_ACGI.flags, OGL_DL_BLESSED_GEOMETRY))
								ts->_hoops_SRHA |= DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS;
							dc->_hoops_SPA->modelling_matrix = null;
							if (ts->_hoops_GSCP)
								dc->_hoops_RAI = (Geometry const *) ts->_hoops_GSCP;
							if (BIT (ts->_hoops_SRHA, _hoops_GGIA))
								_hoops_ARCI (pair->nr, ts);
							else
								draw_3d_tristrip (pair->nr, ts);
							ts->_hoops_SRHA = _hoops_AICIP;
							_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
						}
					}
					dl->action_mask |= _hoops_PGRI;
					if (!_hoops_CAHRC)
						break;
				}
				if (dc->_hoops_SSGC >= 0 &&
					_hoops_CHGI->item._hoops_ACGI.
					_hoops_CRPRC == null) {
						_hoops_GRGGI *glist = POOL_NEW(dc->memory_pool, _hoops_GRGGI)(dc->memory_pool);
						_hoops_RRHA->_hoops_CRHA->ResetCursor();
						for (;;) {
							pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
							if (!pair)
								break;
							ts = (Tristrip *)pair->geo;
							_hoops_PRRH (ts->_hoops_GSCP);
							glist->AddLast (ts->_hoops_GSCP);
							_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
						}
						_hoops_CHGI->item._hoops_ACGI._hoops_CRPRC = glist;
				}
			}

			delete _hoops_RRHA->_hoops_CRHA;
			dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
			dc->_hoops_SPA->color = _hoops_GGRI;
			_hoops_RRHA->nr.release();
			FREE (_hoops_RRHA, OGL_Display_List_Bin);
		}
		/* _hoops_RARI _hoops_RH _hoops_CIPH _hoops_SR _hoops_HPSH _hoops_IAPR _hoops_RH _hoops_SRS _hoops_GHIR _hoops_AARI */
		if (_hoops_CHGI &&
			BIT (_hoops_CHGI->item._hoops_ACGI._hoops_PCGI, T_FACES)) {
			if (_hoops_GIGI) {
				while ((pair = list->PeekCursor()) != null) {
					list->AdvanceCursor();
					ts = (Tristrip *) pair->geo;
					if (BIT (ts->face_attributes.flags, _hoops_IAGI)) {
						unsigned int _hoops_PARI = ts->_hoops_SRHA;
						ts->_hoops_SRHA |= _hoops_SRHH;
						if (!_hoops_IHGI) {
							if (BIT (ts->_hoops_SRHA, _hoops_GGIA))
								_hoops_CRRI (pair->nr, ts, null);
							else
								_hoops_RRRI (pair->nr, ts, null);
						}
						ts->_hoops_SRHA = _hoops_PARI;
					}
				}
			}
			else {
				_hoops_HARI (nr, _hoops_CHGI->item._hoops_ACGI._hoops_ARRI, true, false);
			}
		}
		if (_hoops_HIGI)
			_hoops_CHGI->item._hoops_ACGI._hoops_PCGI |= T_FACES;

		/* _hoops_SP _hoops_GH _hoops_IARI _hoops_HIGR _hoops_PPR _hoops_AGPI _hoops_PGPI/_hoops_HGPI _hoops_IGPI */
		while ((pair = list->RemoveFirst()) != null) {
			ts = (Tristrip alter *)pair->geo;
			ts->_hoops_CARI &= ~_hoops_SARI;

			//_hoops_RPP _hoops_ASGA _hoops_CHR _hoops_GPRI _hoops_PPR _hoops_RPRI _hoops_IS _hoops_APRI (_hoops_HAS._hoops_IAS. _hoops_HAR _hoops_HHHA), _hoops_PSCR _hoops_PPRI '_hoops_HPRI (_hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_PAAP)
			if (ts->_hoops_GSCP &&
				(ts->_hoops_GSCP->type == _hoops_SCIP || ts->_hoops_GSCP->type == _hoops_GSIP) && 
				!_hoops_GIGI) {
				Polyhedron const *_hoops_IPRI = (Polyhedron const *)ts->_hoops_GSCP;
				Local_Face_Attributes const *_hoops_CPRI = (Local_Face_Attributes const *) &_hoops_IPRI->local_face_attributes;
				Local_Vertex_Attributes const *_hoops_SPRI = (Local_Vertex_Attributes const *) &_hoops_IPRI->local_vertex_attributes;

				if ((_hoops_CPRI->normals != null && _hoops_CPRI->explicit_normal_count == 0) ||
					 (_hoops_SPRI->normals != null && _hoops_SPRI->explicit_normal_count == 0))
					HI_Queue_Flush_Derived_Normals (dc->_hoops_GHRI, (Polyhedron alter *)ts->_hoops_GSCP);
			}
			//_hoops_RHRI _hoops_AHRI, _hoops_PHRI, _hoops_CHR _hoops_SHR _hoops_HHRI _hoops_HPP _hoops_RH _hoops_CRHH, _hoops_HIS _hoops_SCH'_hoops_GRI _hoops_IHRI _hoops_IS _hoops_CHRI _hoops_CAPR _hoops_RPHR _hoops_SGGR _hoops_RPP _hoops_GPRI
			if (BIT (ts->_hoops_SRHA, _hoops_CAGI)) {
				ts->_hoops_SRHA &= ~_hoops_CAGI;
				if (ts->_hoops_PAGI && BIT (ts->_hoops_RAHH, _hoops_SHRI)) {
					FREE_ARRAY (ts->_hoops_PAGI, ts->face_count, RGB);
					ts->_hoops_PAGI = null;
					ts->_hoops_RAHH &= ~_hoops_SHRI;
				}
			}

			delete pair;
		}
		delete list;
		_hoops_CSRGR->_hoops_CIGI->_hoops_RCGI = null;

		delete _hoops_SHGI;
	}

	if (_hoops_CSRGR->_hoops_CIGI &&
		_hoops_CSRGR->_hoops_CIGI->_hoops_IHGI)
		_hoops_AHAI = false;

	if (_hoops_AHAI &&
		_hoops_CHGI->item._hoops_ACGI._hoops_ARRI) {
			bool _hoops_GIRI;
			if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES) &&
				_hoops_CPGI(nr->_hoops_IRR))
				_hoops_GIRI = BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_FACES);
			else
				_hoops_GIRI = BIT (nr->_hoops_RGP, T_FACES);

			bool _hoops_RIRI = BIT (_hoops_CHGI->item._hoops_ACGI._hoops_PCGI, T_FACES);
			if (_hoops_GIRI || _hoops_RIRI)
				_hoops_HARI (nr,
					_hoops_CHGI->item._hoops_ACGI._hoops_ARRI,
					_hoops_RIRI, _hoops_GIRI);
	}
} /* _hoops_RSGR _hoops_API '_hoops_RSGR _hoops_CRHH _hoops_AIRI _hoops_HIGR' */


local void
_hoops_PIRI (
		Net_Rendition const &nr,
		_hoops_GACR alter *dl,
		bool _hoops_IHGI)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLD(dc);
	OGL_Display_List_Bin *_hoops_RRHA;
	_hoops_IPSGC *pair;
	Polyedge alter *pe;
	_hoops_AIGI *list;
	OGL_Display_List *_hoops_CHGI = (OGL_Display_List alter *)dl->list;
	int weight;
	int stage = 0;
	int _hoops_AHAI = true;
	bool _hoops_GPHRC;
	bool _hoops_HIGI = false;
	bool _hoops_GIGI = false;

	if ((weight = nr->_hoops_RHP->weight) < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, nr->_hoops_RHP->_hoops_PHP, nr->_hoops_RHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
	if (weight == 0)
		weight = 1;

	if (_hoops_CSRGR->_hoops_CIGI->_hoops_IIRI ||
		_hoops_CSRGR->_hoops_CIGI->_hoops_CIRI ||
		_hoops_CSRGR->_hoops_CIGI->_hoops_SIRI) {

		OGL_Display_List_Bin_List *_hoops_HIRI = POOL_NEW(dc->memory_pool, OGL_Display_List_Bin_List)(dc->memory_pool);

		_hoops_AHAI = false;
		for (stage = 0; stage < 3; stage++) {
			if (stage == 0)
				list = _hoops_CSRGR->_hoops_CIGI->_hoops_SIRI;
			else if (stage == 1)
				list = _hoops_CSRGR->_hoops_CIGI->_hoops_CIRI;
			else if (stage == 2)
				list = _hoops_CSRGR->_hoops_CIGI->_hoops_IIRI;
			else
				break; // _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_SSRR

			if (!list)
				continue;
			list->ResetCursor();
			while ((pair = list->PeekCursor()) != null) {
				pe = (Polyedge *) pair->geo;
				if (list == _hoops_CSRGR->_hoops_CIGI->_hoops_CIRI)
					dl->_hoops_PRRI |= _hoops_GCRI;
				else if (list == _hoops_CSRGR->_hoops_CIGI->_hoops_SIRI)
					dl->_hoops_PRRI |= _hoops_RCRI;

				/* _hoops_IRHRC _hoops_RHIR _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_ACRI _hoops_CRHRC, _hoops_PPR _hoops_CAHA _hoops_GGSR _hoops_PGAP _hoops_SCGI _hoops_IS _hoops_GGCR _hoops_SCH _hoops_IS */
				_hoops_HIRI->ResetCursor();
				while ((_hoops_RRHA = _hoops_HIRI->PeekCursor()) != null) {
					Polyedge const *_hoops_GASI = (Polyedge const *)_hoops_RRHA->_hoops_CRHA->PeekFirst()->geo;
					const int _hoops_AAGI = (_hoops_GPGI|_hoops_RPGI|_hoops_APGI);
					bool _hoops_APACP = true;

					if ((_hoops_GASI->_hoops_ASHA != null) != (pe->_hoops_ASHA != null) ||
						(_hoops_GASI->_hoops_PCHA != null) != (pe->_hoops_PCHA != null))
						_hoops_APACP = false;
					if (!_hoops_HPGI (_hoops_GASI->_hoops_PPGI,
													pe->_hoops_PPGI,
													_hoops_AAGI))
						_hoops_APACP = false;
					if (_hoops_APACP)
						break;
					_hoops_HIRI->AdvanceCursor();
				}

				if (!_hoops_RRHA) {
					/* _hoops_CSH _hoops_PIS _hoops_SCGI _hoops_GSGI, _hoops_HIS _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_SPR, _hoops_PPR _hoops_GGCR _hoops_IS _hoops_RSGI */
					ZALLOC (_hoops_RRHA, OGL_Display_List_Bin);
					_hoops_RRHA->_hoops_AGRI = pe->_hoops_SRHA & ~_hoops_GAHH;
					_hoops_RRHA->id = 0;
					/*_hoops_IPRPI: _hoops_SCGI->_hoops_CRSRR = _hoops_RAHRC(_hoops_SCII, _hoops_AAHRC, _hoops_SAHA, _hoops_PAHRC);*/
					_hoops_HIRI->AddFirst(_hoops_RRHA);
					_hoops_RRHA->_hoops_CRHA = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
					_hoops_RRHA->nr = nr;
				}

				/* _hoops_RGPA _hoops_RH _hoops_ACRI _hoops_CRGR _hoops_RH _hoops_SCGI , _hoops_PPR _hoops_ARP _hoops_GII _hoops_ASGI _hoops_PIH */
				_hoops_RRHA->_hoops_CRHA->AddFirst(pair);

				/* _hoops_HGCR _hoops_ACRI'_hoops_GRI _hoops_CHCA _hoops_RPR */
				_hoops_RRHA->_hoops_HGAC += pe->total - pe->_hoops_PHHA;

				list->AdvanceCursor();
			}

			_hoops_GPHRC = BIT(dc->flags, _hoops_CHSI);

			if (_hoops_IHGI)
				dc->flags |= _hoops_CHSI;
			else
				dc->flags &= ~_hoops_CHSI;

			while ((_hoops_RRHA = _hoops_HIRI->RemoveFirst()) != null) {
				bool _hoops_RIGI = false;
				_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
				_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;

				_hoops_RRHA->_hoops_CRHA->ResetCursor();
				pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
				pe = (Polyedge *) pair->geo;
				if (pe->_hoops_ICHA || pe->_hoops_RSHA) {
					if (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI) ||
					   !ANYBIT (nr->transform_rendition->heuristics, _hoops_RSA)) {
						_hoops_GIGI = true;
					}
				}
				if (BIT (dl->_hoops_AGRI, DL_INSUFFICIENT_VRAM) ||
					_hoops_HSRI(_hoops_RRHA->nr, nr->_hoops_RHP, pe, weight))
					_hoops_GIGI = true;

				if (!BIT (_hoops_CHGI->item._hoops_ACGI.flags, OGL_DL_BLESSED_SEGMENT) &&
					!ALLBITS (_hoops_CHGI->item._hoops_ACGI.flags,
							OGL_DL_BLESSED_GEOMETRY|OGL_DL_SINGLE_INSTANCED))
					_hoops_GIGI = true;

				if (list == _hoops_CSRGR->_hoops_CIGI->_hoops_SIRI) {
					if (BIT (dl->action_mask, _hoops_RSRI))
						_hoops_GIGI = true;
				}
				else {
					if (ANYBIT (dl->action_mask, _hoops_ASRI|_hoops_GHCI))
						_hoops_GIGI = true;
				}

				/* _hoops_GA'_hoops_RA _hoops_IRHH _hoops_IRS _hoops_HCGI _hoops_RPP _hoops_RH _hoops_CCSHP _hoops_III _hoops_RPHRC _hoops_HRGR _hoops_SAHR _hoops_CPIC _hoops_IS _hoops_RIGHH _hoops_SCH */
				if (nr->_hoops_IRR->_hoops_SRI == _hoops_SICI &&
					BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI)) {
					Line_Style const &	_hoops_ACCI = nr->_hoops_ASIR->_hoops_GCCI.line_style;

					/* _hoops_PCCI _hoops_HII _hoops_HCCI _hoops_GGR _hoops_ICCI._hoops_GGHR */
					if (!BIT(_hoops_ACCI->flags, LSF_SOLID)) {
						if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_PATTERNED_LINES) ||
							!BIT(_hoops_ACCI->flags, LSF_BITS16) || /* _hoops_PSP _hoops_CCCI 16-_hoops_IGRH _hoops_SCCI */
							BIT(nr->_hoops_AHP->flags, _hoops_SRPI) ||
							ANYBIT(_hoops_ACCI->flags, LSF_COMPLEX_ANYBITS))
							_hoops_GIGI = true;
					}
				}

				if (!_hoops_GIGI) {
					if (pair->color != null &&
						BIT (pe->_hoops_SRHA, DL_HAS_TRANSPARENCY)) {
						_hoops_GIGI = true;
						_hoops_RIGI = true;
					}
					if (_hoops_CSRGR->_hoops_CIGI->_hoops_SIGI) {
						_hoops_GIGI = true;
						_hoops_RIGI = true;
					}
				}


				if (!_hoops_GIGI) {
					OGL_Display_List *odl;
					int _hoops_PRHA = 0;
					GLuint id;
					int _hoops_AICIP;

					ZALLOC(odl, OGL_Display_List);
					AGLM(odl->_hoops_CSRGR = OGLD(dc));
					odl->type = OGL_DL_GEOMETRY;
					odl->_hoops_GHRI = dc->_hoops_GHRI;
					odl->time_stamp = HOOPS_WORLD->_hoops_GPPI;
					id = glGenLists(1);
					glNewList (id, GL_COMPILE);
					_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = true;
					for (;;) {
						pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
						if (!pair)
							break;
						pe = (Polyedge *)pair->geo;
						/* _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS */
						if (pe->_hoops_GAHA && pe->_hoops_GAHA->list)
							HD_Queue_Destroy_List ((OGL_Display_List *)pe->_hoops_GAHA->list, true);
						odl->item.geometry._hoops_IGGI.point_count += pe->point_count;
						odl->item.geometry._hoops_IGGI._hoops_PHHA += pe->_hoops_PHHA;
						odl->item.geometry._hoops_IGGI.total += pe->total;
						odl->_hoops_CARH += _hoops_ARHRC (pe);
						/* _hoops_SR'_hoops_GHGP _hoops_SHH _hoops_GGR _hoops_SPGC _hoops_RPP _hoops_AHHA _hoops_HS _hoops_PGSGR _hoops_HGSGR
						   _hoops_IH _hoops_APHRC, _hoops_HIH _hoops_SGS _hoops_AGIR _hoops_HRGR _hoops_AGIA
						   _hoops_IS _hoops_SHH _hoops_GIR _hoops_GGR _hoops_RH _hoops_PIS _hoops_SCGI _hoops_SPAAR _hoops_RRGR _hoops_ARRS */
						_hoops_PRHA |= (
								pe->_hoops_GSHA >= 2 ||
								pe->_hoops_PCHA ||
								pe->_hoops_ICHA);
						dc->_hoops_SPA->modelling_matrix = pair->_hoops_CPAI;
						dc->_hoops_SPA->color = pair->color;
						_hoops_AICIP = pe->_hoops_SRHA;
						if (!BIT (_hoops_CHGI->item._hoops_ACGI.flags, OGL_DL_BLESSED_GEOMETRY))
							pe->_hoops_SRHA |= DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS;
						if (pe->_hoops_GSCP)
							dc->_hoops_RAI = (Geometry const *) pe->_hoops_GSCP;
						draw_3d_polyedge(nr, pe);
						pe->_hoops_SRHA = _hoops_AICIP;
						_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
					}
					_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = false;
					glEndList ();
					HOOPS_WORLD->display_list_vram_usage += odl->_hoops_CARH;
					odl->item.geometry.id = id;
					odl->item.geometry._hoops_GSAI = pe->_hoops_GSAI;
					odl->item.geometry._hoops_SRHA = pe->_hoops_SRHA;
					odl->item.geometry._hoops_CARI = pe->_hoops_CARI;
					odl->item.geometry._hoops_IRRI = pe->_hoops_PPGI.flags;
					if (_hoops_PRHA)
						odl->item.geometry._hoops_SRHA |= DL_FORCE_SMOOTH_SHADE_MODEL;

					/* _hoops_CSRI _hoops_HRGR _hoops_IRS _hoops_PPHRC _hoops_GPRR */
					if (list == _hoops_CSRGR->_hoops_CIGI->_hoops_CIRI) {
						if (_hoops_CHGI->item._hoops_ACGI._hoops_GGAI == null)
							_hoops_CHGI->item._hoops_ACGI._hoops_GGAI = POOL_NEW(dc->memory_pool, OGL_Display_List_List)(dc->memory_pool);
						_hoops_CHGI->item._hoops_ACGI._hoops_GGAI->AddFirst(odl);
					}
					else if (list == _hoops_CSRGR->_hoops_CIGI->_hoops_SIRI) {
						if (_hoops_CHGI->item._hoops_ACGI._hoops_RGAI == null)
							_hoops_CHGI->item._hoops_ACGI._hoops_RGAI = POOL_NEW(dc->memory_pool, OGL_Display_List_List)(dc->memory_pool);
						_hoops_CHGI->item._hoops_ACGI._hoops_RGAI->AddFirst(odl);
					}
					else {
						if (_hoops_CHGI->item._hoops_ACGI._hoops_AGAI == null)
							_hoops_CHGI->item._hoops_ACGI._hoops_AGAI = POOL_NEW(dc->memory_pool, OGL_Display_List_List)(dc->memory_pool);
						_hoops_CHGI->item._hoops_ACGI._hoops_AGAI->AddFirst(odl);
					}
					if (BIT (odl->item.geometry._hoops_IRRI, _hoops_APGI))
						_hoops_HIGI = true;
					_hoops_AHAI = true;
				}
				else {
					/* _hoops_PGSA _hoops_GGR _hoops_HGAI _hoops_CCH */
					_hoops_CHGI->item._hoops_ACGI._hoops_RGP &= ~T_LIGHTS_FOR_EDGES;
					if (!_hoops_IHGI) {
						for (;;) {
							pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
							if (!pair)
								break;
							pe = (Polyedge *)pair->geo;
							dc->_hoops_SPA->modelling_matrix = null;
							if (pe->_hoops_GSCP)
								dc->_hoops_RAI = (Geometry const *) pe->_hoops_GSCP;
							pe->_hoops_SRHA |= DL_SUPPRESS_SEGMENT_DISPLAY_LISTS;
							if (!_hoops_RIGI)
								pe->_hoops_SRHA |= _hoops_SRHH;
							draw_3d_polyedge(pair->nr, pe);
							_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
						}
					}
					if (list == _hoops_CSRGR->_hoops_CIGI->_hoops_SIRI) {
						dl->action_mask |= _hoops_RSRI;
					}
					else {
						dl->action_mask |= _hoops_IGAI;
						if (list == _hoops_CSRGR->_hoops_CIGI->_hoops_CIRI)
							dl->action_mask |= _hoops_PGRI;
					}
				    if (dc->_hoops_SSGC >= 0 &&
					    _hoops_CHGI->item._hoops_ACGI._hoops_SRPRC == null) {
					    _hoops_GRGGI *glist = POOL_NEW(dc->memory_pool, _hoops_GRGGI)(dc->memory_pool);
					    _hoops_RRHA->_hoops_CRHA->ResetCursor();
					    for (;;) {
						    pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
						    if (!pair)
							    break;
						    pe = (Polyedge *)pair->geo;
						    _hoops_PRRH (pe->_hoops_GSCP);
						    glist->AddLast (pe->_hoops_GSCP);
						    _hoops_RRHA->_hoops_CRHA->AdvanceCursor();
					    }
					    _hoops_CHGI->item._hoops_ACGI._hoops_SRPRC = glist;
				    }
				}
				delete _hoops_RRHA->_hoops_CRHA;
				dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
				dc->_hoops_SPA->color = _hoops_GGRI;
				_hoops_RRHA->nr.release();
				FREE (_hoops_RRHA, OGL_Display_List_Bin);
			}

			if (_hoops_GPHRC)
				dc->flags |= _hoops_CHSI;
			else
				dc->flags &= ~_hoops_CHSI;

			/* _hoops_RARI _hoops_RH _hoops_CIPH _hoops_SR _hoops_HPSH _hoops_IAPR _hoops_RH _hoops_SRS _hoops_GHIR _hoops_AARI */
			if (BIT (_hoops_CHGI->item._hoops_ACGI._hoops_PCGI, T_EDGES)) {
				if (_hoops_GIGI) {
					while ((pair = list->PeekCursor()) != null) {
						list->AdvanceCursor();
						pe = (Polyedge *) pair->geo;
						if (BIT (pe->_hoops_PPGI.flags, _hoops_APGI)) {
							unsigned int _hoops_PARI = pe->_hoops_SRHA;
							pe->_hoops_SRHA |= _hoops_SRHH;
							if (!_hoops_IHGI) {
								really_draw_3d_polyedge (pair->nr, pair->nr->_hoops_RHP, pe, null);
							}
							pe->_hoops_SRHA = _hoops_PARI;
						}
					}
				}
				else {
					_hoops_CGAI (nr, _hoops_CHGI, true, false);
				}
			}
			if (_hoops_HIGI)
				_hoops_CHGI->item._hoops_ACGI._hoops_PCGI |= T_EDGES;

			/* _hoops_SP _hoops_GH _hoops_IARI _hoops_HIGR _hoops_PPR _hoops_AGPI _hoops_PGPI/_hoops_PAGGR _hoops_IGPI */
			while ((pair = list->RemoveFirst()) != null) {
				pe = (Polyedge alter *)pair->geo;
				pe->_hoops_CARI &= ~_hoops_SARI;
				delete pair;
			}

			delete list;
		}
		_hoops_CSRGR->_hoops_CIGI->_hoops_IIRI = null;
		_hoops_CSRGR->_hoops_CIGI->_hoops_CIRI = null;
		_hoops_CSRGR->_hoops_CIGI->_hoops_SIRI = null;
		delete _hoops_HIRI;
	}


	if (_hoops_CSRGR->_hoops_CIGI &&
		_hoops_CSRGR->_hoops_CIGI->_hoops_IHGI)
		_hoops_AHAI = false;

	if (!_hoops_CHGI->item._hoops_ACGI._hoops_AGAI && !ANYBIT (dl->_hoops_PRRI, _hoops_GCRI|_hoops_RCRI))
		_hoops_AHAI = false;

	if (_hoops_AHAI) {
		bool _hoops_GIRI =
			(ANYBIT (nr->_hoops_RGP, _hoops_PSRI) ||
			ANYBIT (dl->_hoops_PRRI, _hoops_GCRI));
		bool _hoops_RIRI = BIT (_hoops_CHGI->item._hoops_ACGI._hoops_PCGI, T_EDGES);

		if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES) &&
			ANYBIT (dl->_hoops_PRRI, _hoops_RCRI))
			_hoops_GIRI = true;

		if (_hoops_GIRI || _hoops_RIRI)
			_hoops_CGAI (nr, _hoops_CHGI, _hoops_RIRI, _hoops_GIRI);
	}

} /* _hoops_RSGR _hoops_API '_hoops_RSGR _hoops_ACRI _hoops_AIRI _hoops_HIGR' */



/*
 * _hoops_PGAA
 */
local void
_hoops_HPHRC (
		Polyedge const *pe,
		int alter *_hoops_HPHA,
		int alter *_hoops_AAGR)
{
	int i = 0;
	int point_count = 0;
	int length = 0;

	/* _hoops_CGP _hoops_PPSR _hoops_RPR _hoops_HRGR 0, _hoops_HSPAR _hoops_GPHA _hoops_PSPI _hoops_HIGR _hoops_IS _hoops_CACH _hoops_RSH _hoops_AHPH _hoops_RSSA _hoops_IIH *_hoops_CGH* _hoops_SHH */
	if (pe->point_count == 0) {
		for (i = 0; i < pe->total; i++)
			if (point_count < pe->_hoops_AIHA[i])
				point_count = pe->_hoops_AIHA[i];
		point_count++;	/*_hoops_PIHA _hoops_HIHA _hoops_IH 0 _hoops_IIHA _hoops_CIHA*/
	}
	else
		point_count = pe->point_count;
	if (_hoops_HPHA)
		*_hoops_HPHA = point_count;

	/* _hoops_RH _hoops_ACRI'_hoops_GRI _hoops_CIHA _hoops_SRHR _hoops_SPCC */
	if (pe->lengths) {
		/* _hoops_HHHA _hoops_IHHA */
		for (i = 0; i < pe->_hoops_PHHA; i++)
			length += 2 * (pe->lengths[i]-1);
	}
	else {
		/* _hoops_CHHA _hoops_IHHA, _hoops_SHHA _hoops_SGS _hoops_HCR _hoops_GIHA _hoops_RIHA _hoops_GGR _hoops_SPR _hoops_CGGR */
		length += 2 * (pe->total - 1);
	}
	if (_hoops_AAGR)
		*_hoops_AAGR = length;
}



local void
_hoops_IPHRC (
		Net_Rendition const &nr,
		_hoops_IPSGC const *pair,
		bool _hoops_IHGI,
		Polyedge alter *pe,
		_hoops_HHRGR alter *_hoops_IHRGR,
		bool *_hoops_AHRGR,
		Action_Mask *_hoops_CPHRC)
{
	Geometry const *_hoops_RSII = (Geometry const *)pair->geo;
	Display_Context const * dc = nr->_hoops_SRA;
	bool single = pair->single;
	OGLData *_hoops_CSRGR = OGLD(nr->_hoops_SRA);
	bool _hoops_SAR = nr->_hoops_ARA->_hoops_APPI._hoops_SAR;
	int type;
	struct _hoops_CHRGR alter *_hoops_RSHI;
	bool _hoops_ARPI = false;
	Geometry const *g = _hoops_RSII;

	while (g) {
		type = g->type;
		if (type != _hoops_RSII->type)
			break;
		switch (type) {
			case _hoops_HIIP: {
				type = _hoops_IIIP;		// _hoops_HSII _hoops_SAHR _hoops_GAR _hoops_ISII
			} _hoops_HHHI;

			case _hoops_IIIP: {
				do {
					Polyline const *	ptr = (Polyline const *)g;

					pe->point_count += Abs(ptr->count);
					pe->total += Abs(ptr->count);
					if (ptr->count > 0)
						pe->_hoops_PHHA++;
					else
						pe->_hoops_PHHA += -(ptr->count)/2; //_hoops_SPHRC _hoops_APGR

					if (single)
						break;
					g = g->next;
				} while (g && g->type == type);
			} break;

			case _hoops_PIIP: {
				do {
					pe->point_count += 2;
					pe->total += 2;
					pe->_hoops_PHHA++;

					if (single)
						break;
					g = g->next;
				} while (g && g->type == type);
			} break;

			case _hoops_CHIP:{
				_hoops_ARPI = true;
				if (!_hoops_SAR) {
					Polyline alter _hoops_AIRGR;
					_hoops_PIRGR const *ptr;

					do {
						ptr = (_hoops_PIRGR const *)g;
						if (ptr->control_point_count) {
							ZERO_STRUCT (&_hoops_AIRGR, Polyline);
							HI_Generate_NURBS_Polyline (ptr,
								&nr->_hoops_ARA->_hoops_APPI,
								&nr->transform_rendition->matrix->data,
								&_hoops_AIRGR, 0);
							POOL_ALLOC (_hoops_RSHI, struct _hoops_CHRGR, dc->memory_pool);
							_hoops_RSHI->_hoops_SGII = _hoops_AIRGR.allocated;
							_hoops_RSHI->count = _hoops_AIRGR.count;
							_hoops_RSHI->points = _hoops_AIRGR.points;
							_hoops_IHRGR->AddLast(_hoops_RSHI);
							pe->point_count += _hoops_RSHI->count;
							pe->total += _hoops_RSHI->count;
							pe->_hoops_PHHA++;
						}
						if (single)
							break;
						g = g->next;
					} while (g && g->type == type);
				}
				else {
					*_hoops_CPHRC |= _hoops_SHIP;
					if (!_hoops_IHGI) {
						_hoops_CSRGR->_hoops_AHPI = !single;
						draw_3d_nurbs_curve (pair->nr, (_hoops_PIRGR const *) g);
						_hoops_CSRGR->_hoops_AHPI = false;
					}
					_hoops_CSHI (g, type);
				}
			} break;

			case _hoops_GIIP:
			case _hoops_RIIP: {
				_hoops_ARPI = true;
				if (!_hoops_SAR) {
					_hoops_GHHI const *ptr;
					float start, end;
					int _hoops_HGII;

					do {
						ptr = (_hoops_GHHI const *)g;
						POOL_ALLOC (_hoops_RSHI, struct _hoops_CHRGR, dc->memory_pool);
						_hoops_HGII = HD_Determine_Elliptical_Res (nr, ptr);
						if (BIT (ptr->_hoops_RRHH, _hoops_SHHI)) {
							Circular_Arc_Lite const *arc;

							arc = (Circular_Arc_Lite const *)ptr;
							start = arc->arc_start;
							end = arc->_hoops_PHHI;
						}
						else {
							Elliptical_Arc const *arc;

							arc = (Elliptical_Arc const *)ptr;
							start = arc->arc_start;
							end = arc->_hoops_PHHI;
							if (end < start)
								end += 1.0f;
						}
						_hoops_RSHI->_hoops_SGII = 10 + (int)((float)_hoops_HGII * Abs (end - start) + 0.5f);
						POOL_ALLOC_ARRAY_CACHED (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point, dc->memory_pool);
						_hoops_RSHI->count = HD_Generate_Elliptical_Points (nr, ptr, _hoops_HGII, _hoops_RSHI->points);
						ASSERT (_hoops_RSHI->count <= _hoops_RSHI->_hoops_SGII);
						if (_hoops_RSHI->count >= 2) {
							_hoops_IHRGR->AddLast(_hoops_RSHI);
							pe->point_count += _hoops_RSHI->count;
							pe->total += _hoops_RSHI->count;
							pe->_hoops_PHHA++;
						}
						else {
							FREE_ARRAY (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point);
							FREE (_hoops_RSHI, struct _hoops_CHRGR);
							_hoops_RSHI = null;
						}
						if (single)
							break;
						g = g->next;
					} while (g && g->type == type);
				}
				else {
					*_hoops_CPHRC |= _hoops_AIIP;
					if (!_hoops_IHGI) {
						do {
							_hoops_PPAGR (pair->nr, (Elliptical_Arc const *) g);
						g = g->next;
							if (single)
								break;
					} while (g && g->type == type);
				}
				else
					_hoops_CSHI (g, type);
				}
			} break;

			default:
				_hoops_CSHI (g, type);
		}
		if (single)
			break;
	}
	*_hoops_AHRGR = _hoops_ARPI;
}


local Polyedge alter *_hoops_GHHRC (
		Net_Rendition const &nr, 
		_hoops_IPSGC const *pair,
		bool *_hoops_RHHRC,
		Action_Mask *_hoops_CPHRC,
		bool _hoops_IHGI)
{
	Display_Context const * dc = nr->_hoops_SRA;
	Geometry const *_hoops_RSII = (Geometry const *)pair->geo;
	bool single = pair->single;
	Geometry const *g;
	Type type;
	_hoops_HHRGR alter *_hoops_IHRGR = null;
	struct _hoops_CHRGR alter *_hoops_RSHI;
	Polyedge alter *pe;
	int _hoops_GIRGR;
	int i, len;

	ZALLOC (pe, Polyedge);
	_hoops_CARSH (pe);  //_hoops_GPII _hoops_GRS _hoops_IRAA _hoops_SAII

	/* _hoops_SPIC _hoops_RH _hoops_HIGR _hoops_ARR _hoops_IS _hoops_GRAS _hoops_GHCS _hoops_PGRR */
	_hoops_IHRGR = POOL_NEW(dc->memory_pool, _hoops_HHRGR)(dc->memory_pool);
	_hoops_IPHRC (nr, pair, _hoops_IHGI,
		pe, _hoops_IHRGR, _hoops_RHHRC, _hoops_CPHRC);

	if (pe->point_count == 0) {
		HI_Free_Polyedge(pe);
		pe = null;
		goto _hoops_HPAGR;
	}
	ALLOC_ARRAY_CACHED (pe->lengths, pe->_hoops_PHHA, int);
	pe->lengths_allocated = pe->_hoops_PHHA;
	pe->_hoops_RAHH |= _hoops_AAHH;
	ALLOC_ARRAY_ALIGNED_CACHED (pe->points, pe->point_count, Point, 16);
	pe->_hoops_RAHH |= _hoops_AIPI;
	_hoops_GIRGR = pe->point_count;

	/* _hoops_HIAP _hoops_AGCR _hoops_HSH _hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH _hoops_RPRS _hoops_IIRGR _hoops_PPR _hoops_CIRGR _hoops_GAR
	 * _hoops_CRPR _hoops_PSPI.  _hoops_SSIA _hoops_CGH _hoops_RCPS _hoops_GGSR _hoops_IS _hoops_RH _hoops_PSHR _hoops_AHAP _hoops_GAR _hoops_ARPP */
	pe->_hoops_PHHA = pe->point_count = 0;
	g = _hoops_RSII;
	/* _hoops_SPIC _hoops_RH _hoops_HIGR _hoops_GICS _hoops_IS _hoops_IPS _hoops_CRGR _hoops_RH _hoops_RSSA _hoops_PPR _hoops_IIRGR _hoops_SIRGR */
	while (g) {
		type = g->type;
		if (type != _hoops_RSII->type)
			break;
		switch (type) {
			case _hoops_HIIP: {
				type = _hoops_IIIP;		// _hoops_HSII _hoops_SAHR _hoops_GAR _hoops_ISII
			} _hoops_HHHI;

			case _hoops_IIIP: {
				do {
					Polyline const *	ptr = (Polyline const *)g;

					_hoops_AIGA (ptr->points, Abs(ptr->count), Point, &pe->points[pe->point_count]);
					pe->point_count += Abs(ptr->count);
					if (ptr->count > 0) {
						pe->lengths[pe->_hoops_PHHA++] = ptr->count;
					}
					else {
						//_hoops_SPHRC _hoops_APGR
						len = -(ptr->count)/2;
						for (i = 0; i < len; i++)
							pe->lengths[pe->_hoops_PHHA++] = 2;
					}
					g = g->next;
					if (single)
						break;
				} while (g && g->type == type);
			} break;

			case _hoops_PIIP: {
				do {
					Line const *		ptr = (Line const *)g;

					_hoops_AIGA (ptr->points, 2, Point, &pe->points[pe->point_count]);
					pe->point_count += 2;
					pe->lengths[pe->_hoops_PHHA++] = 2;
					g = g->next;
					if (single)
						break;
				} while (g && g->type == type);
			} break;

			default:
				_hoops_CSHI (g, type);
		};
		/* _hoops_RRRC _hoops_PPR _hoops_GRRC _hoops_AAPR _hoops_RAII _hoops_PPR _hoops_AAII _hoops_CIAA _hoops_PAII _hoops_HAII _hoops_HIGR */
		if (_hoops_IHRGR) {
			while ((_hoops_RSHI = _hoops_IHRGR->RemoveFirst()) != null) {
				_hoops_AIGA (_hoops_RSHI->points, _hoops_RSHI->count, Point, &pe->points[pe->point_count]);
				pe->lengths[pe->_hoops_PHHA] = _hoops_RSHI->count;
				pe->point_count += _hoops_RSHI->count;
				pe->_hoops_PHHA++;
				FREE_ARRAY (_hoops_RSHI->points, _hoops_RSHI->_hoops_SGII, Point);
				FREE (_hoops_RSHI, struct _hoops_CHRGR);
			}
		}
		if (single)
			break;
	}
	ASSERT (pe->point_count == _hoops_GIRGR);
	if (!BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_RPA], M_DIFFUSE) && 	
		pair->color && 
		pe->point_count > 0) {
		RGB const *_hoops_GPCP;
		_hoops_GPCP = _hoops_CCAI (pair->color, Color_LINE);
		if (_hoops_GPCP) {
			ALLOC_ARRAY_CACHED (pe->_hoops_PCHA, pe->point_count, RGB);
			pe->_hoops_RAHH |= _hoops_PIPI;
			for (i = 0; i < pe->point_count; i++) {
				pe->_hoops_PCHA[i] = *_hoops_GPCP;
			}
		}
	}

  _hoops_HPAGR:
	delete _hoops_IHRGR;

	return pe;

} /*_hoops_RSGR _hoops_API '_hoops_APGR _hoops_IS _hoops_ACRI'*/


/*
 * _hoops_PGAA
 */
local void
_hoops_AHHRC (
		Net_Rendition const & nr,
		OGL_Display_List_Bin *_hoops_RRHA,
		bool *_hoops_RHHRC,
		Action_Mask *_hoops_PHHRC,
		bool _hoops_IHGI)
{
	Display_Context const * dc = nr->_hoops_SRA;
	Polyedge *pe;
	_hoops_AIGI *_hoops_RCRGR;
	int length, point_count;
	_hoops_IPSGC *pair = null;
	bool _hoops_ARPI;

	_hoops_RCRGR = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

	*_hoops_RHHRC = false;
	while ((pair = _hoops_RRHA->_hoops_CRHA->RemoveFirst()) != null) {

		pe = _hoops_GHHRC (nr, pair, &_hoops_ARPI, _hoops_PHHRC, _hoops_IHGI);

		if (_hoops_ARPI)
			*_hoops_RHHRC = true;

		if (pe) {
			_hoops_IPSGC *_hoops_ICRGR = POOL_NEW(dc->memory_pool, _hoops_IPSGC)(pair->nr, pe, pair->_hoops_CPAI, pair->color, pair->single);
			_hoops_RCRGR->AddFirst(_hoops_ICRGR);
			_hoops_HPHRC(pe, &point_count, &length);
			_hoops_RRHA->point_count += point_count;
			_hoops_RRHA->_hoops_HGAC += length;
		}

		delete pair;
	}
	delete _hoops_RRHA->_hoops_CRHA;
	_hoops_RRHA->_hoops_CRHA = _hoops_RCRGR;
}


/* _hoops_GCRR _hoops_IRS _hoops_RSPH _hoops_ACRI, _hoops_AISI _hoops_IRS _hoops_RAGA _hoops_CSRI _hoops_CRGR _hoops_SCH, _hoops_PPR _hoops_ASRC
 * _hoops_PCCP _hoops_CSRI _hoops_IIGR _hoops_GPRR _hoops_HHHRC _hoops_IS _hoops_ARGAR _hoops_SCH _hoops_GIRP _hoops_CCA
 * _hoops_HPHS _hoops_IS _hoops_CGIC _hoops_IGH _hoops_PAR _hoops_HAR _hoops_SCH _hoops_HRGR _hoops_HGGC _hoops_APIP */
local OGL_Display_List *_hoops_PRGAR (
		Net_Rendition const &nr,
		OGL_Display_List alter *odl,
		bool _hoops_ARPI)
{
	Polyedge *_hoops_GACI;
	OGL_Display_List *_hoops_CRPI;
	GLuint id;

	ZALLOC (_hoops_GACI, Polyedge);
	/* _hoops_RAP _hoops_GH _hoops_RH _hoops_ACRI _hoops_PPR _hoops_RGCI _hoops_AIRI _hoops_HIGR */
	id = odl->item.geometry.id;
	_hoops_GACI->_hoops_GAHA = (_hoops_GACR *)I2V(id);
	_hoops_GACI->_hoops_GSAI = odl->item.geometry._hoops_GSAI;
	_hoops_GACI->_hoops_SRHA = DL_DO_NOT_RECOMPILE | DL_LIGHTWEIGHT_DISPLAY_LIST;
	_hoops_GACI->total = odl->item.geometry._hoops_IGGI.total;
	_hoops_GACI->_hoops_PHHA = odl->item.geometry._hoops_IGGI._hoops_PHHA;
	_hoops_GACI->point_count = odl->item.geometry._hoops_IGGI.point_count;

	ZALLOC (_hoops_CRPI, OGL_Display_List);
	AGLM(_hoops_CRPI->_hoops_CSRGR = OGLD(nr->_hoops_SRA));
	_hoops_CRPI->type = OGL_DL_SEGMENT_POLYLINE;
	_hoops_CRPI->_hoops_GHRI = nr->_hoops_SRA->_hoops_GHRI;
	_hoops_CRPI->time_stamp = HOOPS_WORLD->_hoops_GPPI;
	_hoops_CRPI->_hoops_PPAH = odl->_hoops_PPAH;
	_hoops_CRPI->prev = odl->prev;
	_hoops_CRPI->next = odl->next;
	if (_hoops_CRPI->prev)
		*_hoops_CRPI->prev = _hoops_CRPI;
	if (_hoops_CRPI->next)
		_hoops_CRPI->next->prev = &_hoops_CRPI->next;
	odl->_hoops_PPAH = null;
	odl->prev = null;
	odl->next = null;
	_hoops_CRPI->item._hoops_RPPI.pe = _hoops_GACI;
	/*_hoops_SPR _hoops_IH _hoops_IHHRC->_hoops_IGCI._hoops_CHHRC, _hoops_PPR _hoops_SPR _hoops_IH _hoops_RGCI _hoops_CSRI*/
	_hoops_GACI->_hoops_HSAI = 1;
	if (_hoops_ARPI) {
		_hoops_CRPI->item._hoops_RPPI._hoops_PPPI = nr->_hoops_ARA->_hoops_APPI._hoops_PPPI;
		_hoops_CRPI->item._hoops_RPPI._hoops_HPPI = nr->_hoops_ARA->_hoops_APPI._hoops_HPPI;
		_hoops_CRPI->item._hoops_RPPI._hoops_IPPI = nr->_hoops_ARA->_hoops_APPI._hoops_IPPI;
		_hoops_CRPI->item._hoops_RPPI._hoops_CPPI = nr->_hoops_ARA->_hoops_APPI._hoops_CPPI;
		_hoops_CRPI->item._hoops_RPPI._hoops_SPPI = nr->_hoops_ARA->_hoops_APPI._hoops_SPPI;
	}
	return _hoops_CRPI;
}


//_hoops_HRS _hoops_IHPR _hoops_RPP _hoops_SR _hoops_RRAI _hoops_IRS _hoops_ARAI _hoops_IS _hoops_RH _hoops_HIGR
local bool
_hoops_SHHRC (
		OGL_DL_VBO_List* _hoops_GIHRC,
		Net_Rendition const &nr,
		_hoops_ACHR _hoops_HRAI,
		bool _hoops_RIHRC,
		Polymarker alter *_hoops_IRAI,
		int count,
		bool _hoops_IHGI,
		bool _hoops_GIGI)
{
	bool added = false;
	OGL_Polymarker_Vertex_Buffer_Object *_hoops_SAAS = null;

	if (_hoops_GIGI && _hoops_IHGI)
		return false;

	_hoops_IRAI->length = _hoops_IRAI->point_count = count;
	if (!_hoops_GIGI) {
		_hoops_AIHRC (&_hoops_SAAS, nr, _hoops_IRAI, _hoops_RIHRC, 0, count);
		if (_hoops_SAAS) {
			added = true;
			_hoops_GIHRC->AddLast (_hoops_SAAS);
		}
		else {
			_hoops_GIGI = true;
		}
	}
	if (_hoops_GIGI && !_hoops_IHGI) {
		Net_Rendition _hoops_CRAI = nr;
		_hoops_IRAI->_hoops_SRHA |= _hoops_SRHH;
		if (_hoops_HRAI != T_VERTICES)
			_hoops_CRAI.Modify()->_hoops_SCP = _hoops_CRAI->_hoops_GSP;
		draw_3d_polymarker (_hoops_CRAI, _hoops_IRAI);
	}

	return added;
}


local void
_hoops_RHAI (
		Net_Rendition const &nr,
		_hoops_GACR alter *dl,
		bool _hoops_IHGI)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLD(dc);
	bool _hoops_AHAI = true;
	OGL_Display_List *_hoops_CHGI = (OGL_Display_List *)dl->list;

	ASSERT (_hoops_CSRGR->_hoops_PHAI <= 1024);
	if (_hoops_CSRGR->_hoops_CIGI->_hoops_HHAI ||
		_hoops_CSRGR->_hoops_CIGI->_hoops_IHAI) {
		_hoops_AHAI = false;

		_hoops_AIGI *list = null;
		Color_Object _hoops_RAIH = 0;
		_hoops_ACHR _hoops_HRAI = 0;
		_hoops_IPSGC *pair;
		_hoops_IPSGC *_hoops_SHAI[16];
		int _hoops_RIAI = 0, _hoops_AIAI = 0;
		int pass;
		int i;
		Point _hoops_PIAI[1024];
		RGB _hoops_HIAI[1024];
		float _hoops_IIAI[1024];
		OGL_DL_VBO_List* _hoops_GIHRC = null;
		int stage = 0;
		bool _hoops_RIHRC = false; 
		OGL_Display_List *odl;
		bool _hoops_GIGI = false;
		OGL_Display_List_List *_hoops_SIAI = null;
		Polymarker const *pm;
		Polymarker alter *_hoops_IRAI = null;

		for (stage = 0; stage < 2; stage++) {
			int count = 0;
			int total = 0;
			int _hoops_RCAI = 0;
			bool _hoops_ACAI = false;
			unsigned int _hoops_PIHRC = 0;

			if (stage == 0) {
				list = _hoops_CSRGR->_hoops_CIGI->_hoops_IHAI;
				_hoops_GIGI = _hoops_SGAI (nr, nr->_hoops_GSP, null, null);
				_hoops_HRAI = T_MARKERS;
				_hoops_RAIH = Color_MARKER;
				if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_APA], M_DIFFUSE))
					_hoops_ACAI = true;
				if ((_hoops_SIAI = _hoops_CHGI->item._hoops_ACGI._hoops_GAAI) != null) {
					_hoops_AHAI = true;
					_hoops_SIAI->ResetCursor();
					while ((odl = _hoops_SIAI->PeekCursor()) != null) {
						_hoops_RCAI += odl->item.geometry._hoops_IGGI.total;
						_hoops_SIAI->AdvanceCursor();
					}					
				}
			}
			else if (stage == 1) {
				list = _hoops_CSRGR->_hoops_CIGI->_hoops_HHAI;
				_hoops_GIGI = _hoops_SGAI (nr, nr->_hoops_SCP, null, null);
				_hoops_HRAI = T_VERTICES;
				_hoops_RAIH = Color_VERTEX;
				if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_PPA], M_DIFFUSE))
					_hoops_ACAI = true;
				if ((_hoops_SIAI = _hoops_CHGI->item._hoops_ACGI._hoops_ICARC) != null) {
					_hoops_AHAI = true;
					_hoops_SIAI->ResetCursor();
					while ((odl = _hoops_SIAI->PeekCursor()) != null) {
						_hoops_RCAI += odl->item.geometry._hoops_IGGI.total;
						_hoops_SIAI->AdvanceCursor();
					}					
				}
			}
			else
				break; // _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_SSRR

			if (!list)
				continue;

			_hoops_SHAI[0] = list->PeekFirst();
			_hoops_RIAI = 1;
			for(pass = 0; pass < _hoops_RIAI; pass++) {
				total = 0;
				count = 0;
				if (!_hoops_GIGI)
					_hoops_GIHRC = POOL_NEW(dc->memory_pool, OGL_DL_VBO_List)(dc->memory_pool);
				list->ResetCursor();
				while ((pair = list->PeekCursor()) != null) {
					list->AdvanceCursor();
					if (!_hoops_IGHRC (pair, _hoops_SHAI[pass])) {
						if (pass == 0) {
							//_hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SR _hoops_RRP _hoops_IS _hoops_GGCR _hoops_IRS _hoops_CCAH _hoops_PCAI
							if (!_hoops_IGHRC (pair, _hoops_SHAI[_hoops_AIAI])) {
								for (i = 0; i < _hoops_RIAI; i++) {
									if (_hoops_IGHRC (pair, _hoops_SHAI[i])) {
										_hoops_AIAI = i;
										break;
									}
								}
								if (i == _hoops_RIAI) {
									_hoops_SHAI[_hoops_RIAI] = pair;
									_hoops_RIAI++;
								}
							}
						}
						continue;
					}
					if (pair->type == _hoops_IPSGC::_hoops_HCAI) {
						Point const *p;
						int vi;

						pm = (Polymarker const *)pair->geo;
						for (int i = _hoops_RCAI; i < pm->length ; i++) {
							if (_hoops_IRAI == null) {
								ZALLOC (_hoops_IRAI, Polymarker);
								_hoops_ICAI (_hoops_IRAI);
								_hoops_IRAI->points = _hoops_PIAI;
								if (pm->_hoops_HCHA)
									_hoops_IRAI->_hoops_HCHA = _hoops_IIAI;
								else {
									if (!_hoops_ACAI && _hoops_CCAI (_hoops_SHAI[pass]->color, _hoops_RAIH) != null)
										_hoops_IRAI->_hoops_PCHA = _hoops_HIAI;
									else if (pm->_hoops_PCHA)
										_hoops_IRAI->_hoops_PCHA = _hoops_HIAI;
								}
								_hoops_IRAI->_hoops_SRHA |= DL_TEMPORARY_DATA;
								_hoops_IRAI->_hoops_SRHA |= pm->_hoops_SRHA;
								_hoops_PIHRC |= pm->_hoops_SRHA;
								_hoops_IRAI->_hoops_CARI |= pm->_hoops_CARI;
								_hoops_IRAI->_hoops_GSAI |= pm->_hoops_GSAI;
							}
							if (pm->_hoops_AIHA) 
								vi = pm->_hoops_AIHA[i];
							else 
								vi = i;
							p = &pm->points[vi];
							if (pair->_hoops_CPAI) {
								float _hoops_APCP = 1.0f / _hoops_PHCP (pair->_hoops_CPAI->matrix.elements, *p);
								_hoops_IRAI->points[count].x = _hoops_HPRA (pair->_hoops_CPAI->matrix.elements, *p) * _hoops_APCP;
								_hoops_IRAI->points[count].y = _hoops_IPRA (pair->_hoops_CPAI->matrix.elements, *p) * _hoops_APCP;
								_hoops_IRAI->points[count].z = _hoops_CPRA (pair->_hoops_CPAI->matrix.elements, *p) * _hoops_APCP;
							}
							else
								_hoops_RSAI (p, Point, &_hoops_IRAI->points[count]);
							if (_hoops_IRAI->_hoops_PCHA) { /* _hoops_ASAI _hoops_PSAI->_hoops_HAIR, _hoops_GAR _hoops_RH _hoops_RGSR _hoops_GHCA _hoops_HAR _hoops_GHAA _hoops_IS _hoops_SAIA */
								if (pm->_hoops_PCHA) {
									_hoops_RSAI (&pm->_hoops_PCHA[vi], RGB, &_hoops_IRAI->_hoops_PCHA[count]);
								}
								else {
									RGB const *_hoops_GPCP = _hoops_CCAI (pair->color, _hoops_RAIH);
									_hoops_RSAI (_hoops_GPCP, RGB, &_hoops_IRAI->_hoops_PCHA[count]);
								}
							}
							else if (_hoops_IRAI->_hoops_HCHA)
								_hoops_IRAI->_hoops_HCHA[count] = pm->_hoops_HCHA[vi];
							count++;
							if (count == _hoops_CSRGR->_hoops_PHAI) {
								//_hoops_CHRI _hoops_IRS _hoops_SSAI
								if (!_hoops_SHHRC (_hoops_GIHRC, nr, _hoops_HRAI, _hoops_RIHRC, _hoops_IRAI, count, _hoops_IHGI, _hoops_GIGI)) {
									_hoops_GIGI = true;
								}
								else {
									_hoops_AHAI = true;
									total += count;
								}
								if (_hoops_IRAI->_hoops_HSAI > 1) {
									_hoops_ISAI (_hoops_IRAI);
									_hoops_IRAI = null;
								}
								count = 0;
							}
						}
						if (_hoops_RCAI >= pm->length)
							_hoops_RCAI -= pm->length;
						else
							_hoops_RCAI = 0;
					}
					else {
						Marker const *m = (Marker const *)pair->geo;
						for (;;) {
							if (_hoops_RCAI == 0) {
								if (_hoops_IRAI == null) {
									ZALLOC (_hoops_IRAI, Polymarker);
									_hoops_ICAI (_hoops_IRAI);
									_hoops_IRAI->_hoops_SRHA |= DL_TEMPORARY_DATA;
									_hoops_IRAI->_hoops_CARI = 0;
									_hoops_IRAI->_hoops_GSAI = 0;
									_hoops_IRAI->points = _hoops_PIAI;
									if (!_hoops_ACAI && _hoops_CCAI (_hoops_SHAI[pass]->color, _hoops_RAIH) != null)
										_hoops_IRAI->_hoops_PCHA = _hoops_HIAI;
								}
								if (pair->_hoops_CPAI) {
									float _hoops_APCP = 1.0f / _hoops_PHCP (pair->_hoops_CPAI->matrix.elements, m->_hoops_CSAI);
									_hoops_IRAI->points[count].x = _hoops_HPRA (pair->_hoops_CPAI->matrix.elements, m->_hoops_CSAI) * _hoops_APCP;
									_hoops_IRAI->points[count].y = _hoops_IPRA (pair->_hoops_CPAI->matrix.elements, m->_hoops_CSAI) * _hoops_APCP;
									_hoops_IRAI->points[count].z = _hoops_CPRA (pair->_hoops_CPAI->matrix.elements, m->_hoops_CSAI) * _hoops_APCP;
								}
								else
									_hoops_RSAI (&m->_hoops_CSAI, Point, &_hoops_IRAI->points[count]);
								if (_hoops_IRAI->_hoops_PCHA) {
									RGB const *_hoops_GPCP = _hoops_CCAI (pair->color, _hoops_RAIH);
									_hoops_RSAI (_hoops_GPCP, RGB, &_hoops_IRAI->_hoops_PCHA[count]);
								}
								count++;
								if (count == _hoops_CSRGR->_hoops_PHAI) {
									//_hoops_CHRI _hoops_IRS _hoops_SSAI
									if (!_hoops_SHHRC (_hoops_GIHRC, nr, _hoops_HRAI, _hoops_RIHRC, _hoops_IRAI, count, _hoops_IHGI, _hoops_GIGI)) {
										_hoops_GIGI = true;
									}
									else {
										_hoops_AHAI = true;
										total += count;
									}
									if (_hoops_IRAI->_hoops_HSAI > 1) {
										_hoops_ISAI (_hoops_IRAI);
										_hoops_IRAI = null;
									}
									count = 0;
								}
							}
							else
								--_hoops_RCAI;

							if (pair->single)
								break;
							m = (Marker const *)m->next;
							if (!m)
								break;
						}
					}
				}
				if (count) {
					//_hoops_CHRI _hoops_RH _hoops_GGPI
					if (!_hoops_SHHRC (_hoops_GIHRC, nr, _hoops_HRAI, _hoops_RIHRC, _hoops_IRAI, count, _hoops_IHGI, _hoops_GIGI)) {
						_hoops_GIGI = true;
					}
					else {
						_hoops_AHAI = true;
						total += count;
					}
				}
				if (_hoops_IRAI && 
					_hoops_ISAI (_hoops_IRAI) == 0) {
					HI_Free_Polymarker (_hoops_IRAI);
					_hoops_IRAI = null;
				}


				if (_hoops_GIGI) {
					if (stage == 0)
						dl->action_mask |= _hoops_HCIP;
					else
						dl->action_mask |= _hoops_RGPI;
				}
				
				if (total != 0) {
					ZALLOC (odl, OGL_Display_List);
					AGLM(odl->_hoops_CSRGR = OGLD(dc));
					odl->_hoops_GHRI = dc->_hoops_GHRI;
					odl->time_stamp = HOOPS_WORLD->_hoops_GPPI;
					odl->type = OGL_DL_POLYMARKER_VBO_LIST;
					odl->item.geometry.id = (POINTER_SIZED_INT)_hoops_GIHRC;
					odl->item.geometry._hoops_IGGI.total = total;
					odl->item.geometry._hoops_IGGI.point_count = total;
					odl->item.geometry._hoops_SRHA = _hoops_PIHRC;
					if (ANYBIT (nr->_hoops_IRR->locks.color, Color_VERTEX|Color_MARKER)) {
						bool _hoops_SPGI;
						if (_hoops_HRAI == T_VERTICES)
							_hoops_SPGI = (BIT (nr->_hoops_IRR->locks.color, Color_VERTEX) &&
											  BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_PPA], M_DIFFUSE));
						else
							_hoops_SPGI = (BIT (nr->_hoops_IRR->locks.color, Color_MARKER) &&
											  BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_APA], M_DIFFUSE));
						if (_hoops_SPGI)
							odl->item.geometry._hoops_SRHA = _hoops_IIRC;
					}
					if (stage == 0) {
						if (_hoops_CHGI->item._hoops_ACGI._hoops_GAAI == null)
							_hoops_CHGI->item._hoops_ACGI._hoops_GAAI = POOL_NEW(dc->memory_pool, OGL_Display_List_List)(dc->memory_pool);
						_hoops_CHGI->item._hoops_ACGI._hoops_GAAI->AddLast (odl);
					}
					else {
						if (_hoops_CHGI->item._hoops_ACGI._hoops_ICARC == null)
							_hoops_CHGI->item._hoops_ACGI._hoops_ICARC = POOL_NEW(dc->memory_pool, OGL_Display_List_List)(dc->memory_pool);
						_hoops_CHGI->item._hoops_ACGI._hoops_ICARC->AddLast (odl);
					}
					_hoops_AHAI = true;
				}
				else
					delete _hoops_GIHRC;
				_hoops_GIHRC = null;
			}

			/* _hoops_SP _hoops_GH _hoops_IARI _hoops_HIGR _hoops_PPR _hoops_AGPI _hoops_PGPI/_hoops_HGPI _hoops_IGPI */
			while ((pair = list->RemoveFirst()) != null)
				delete pair;
			delete list;
		}
		_hoops_CSRGR->_hoops_CIGI->_hoops_IHAI = null;
		_hoops_CSRGR->_hoops_CIGI->_hoops_HHAI = null;
	}
	if (_hoops_IHGI)
		_hoops_AHAI = false;

	if (_hoops_AHAI) {
		if (_hoops_CHGI->item._hoops_ACGI._hoops_GAAI &&
			BIT (nr->_hoops_RGP, T_MARKERS)) {
			_hoops_ICPRC (nr, T_MARKERS, _hoops_CHGI->item._hoops_ACGI._hoops_GAAI);
		}
		if (_hoops_CHGI->item._hoops_ACGI._hoops_ICARC &&
			BIT (nr->_hoops_RGP, T_VERTICES)) {
			_hoops_ICPRC (nr, T_VERTICES, _hoops_CHGI->item._hoops_ACGI._hoops_ICARC);
		}
	}
}


local void
_hoops_SGPI (
		Net_Rendition const &nr,
		_hoops_GACR alter *dl,
		bool _hoops_IHGI)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLD(dc);
	OGL_Display_List *_hoops_CHGI = (OGL_Display_List *)dl->list;
	OGL_Display_List_Bin *_hoops_RRHA = 0;
	_hoops_AIGI *list;
	bool _hoops_GIGI;
	bool _hoops_AHAI = true;

	if ((list = _hoops_CSRGR->_hoops_CIGI->_hoops_HRPI) != null) {
		_hoops_IPSGC *pair;
		float weight;
		bool _hoops_GPHRC = BIT(dc->flags, _hoops_CHSI);

		weight = nr->_hoops_AHP->weight;
		if (weight < 0)
			weight = (int)(HD_Compute_Generic_Size (nr, nr->_hoops_AHP->_hoops_PHP, nr->_hoops_AHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);

		if (_hoops_IHGI)
			dc->flags |= _hoops_CHSI;
		else
			dc->flags &= ~_hoops_CHSI;

		if (_hoops_HSRI (nr, nr->_hoops_AHP, null, weight)) {
			if (!_hoops_IHGI) {
				Geometry const *g;
				Type type;
				while ((pair = list->RemoveFirst()) != null) {
					g = (Geometry const *)pair->geo;
					_hoops_CSRGR->_hoops_AHPI = !pair->single;
					type = g->type;
					switch (type) {
						case _hoops_PIIP:
						case _hoops_HIIP:
						case _hoops_IIIP:
							draw_3d_polyline (pair->nr, (Polyline const *)g);
							break;
						case _hoops_CHIP:
							draw_3d_nurbs_curve (pair->nr, (_hoops_PIRGR const *)g);
							break;
						case _hoops_RIIP:
						case _hoops_GIIP:
							do {
								_hoops_PPAGR (pair->nr, (Elliptical_Arc const *) g);
								g = g->next;
								if (!_hoops_CSRGR->_hoops_AHPI)
									break;
							} while (g && g->type == type);
							break;
					}
					_hoops_CSRGR->_hoops_AHPI = false;
					delete pair;
				}
				dl->action_mask |= _hoops_IRPI;
			}
		}
		else {
			OGL_Display_List_Bin_List *_hoops_RRPI = POOL_NEW(dc->memory_pool, OGL_Display_List_Bin_List)(dc->memory_pool);

			_hoops_AHAI = false;
			_hoops_GIGI = BIT (dl->action_mask, _hoops_CIIP);
			if (!ANYBIT (_hoops_CHGI->item._hoops_ACGI.flags,
				OGL_DL_BLESSED_SEGMENT|OGL_DL_BLESSED_GEOMETRY))
				_hoops_GIGI = true;

			if (BIT (dl->action_mask, _hoops_CIIP))
				_hoops_GIGI = true;

			if (_hoops_CHGI &&
				_hoops_CHGI->item._hoops_ACGI._hoops_CAPI &&
				_hoops_CHGI->item._hoops_ACGI._hoops_CAPI->Count())
				_hoops_AHAI = true;

			/* _hoops_GA'_hoops_RA _hoops_IRHH _hoops_IRS _hoops_HCGI _hoops_RPP _hoops_RH _hoops_CCSHP _hoops_III _hoops_RPHRC _hoops_HRGR _hoops_SAHR _hoops_CPIC _hoops_IS _hoops_RIGHH _hoops_SCH */
			if (nr->_hoops_IRR->_hoops_SRI == _hoops_SICI &&
				BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI)) {
				Line_Style const &	_hoops_ACCI = nr->_hoops_ASIR->_hoops_GCCI.line_style;

				/* _hoops_PCCI _hoops_HII _hoops_HCCI _hoops_GGR _hoops_ICCI._hoops_GGHR */
				if (!BIT(_hoops_ACCI->flags, LSF_SOLID)) {
					if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_PATTERNED_LINES) ||
						!BIT(_hoops_ACCI->flags, LSF_BITS16) || /* _hoops_PSP _hoops_CCCI 16-_hoops_IGRH _hoops_SCCI */
						BIT(nr->_hoops_AHP->flags, _hoops_SRPI) ||
						ANYBIT(_hoops_ACCI->flags, LSF_COMPLEX_ANYBITS)) {
						_hoops_GIGI = true;
					}
				}
			}

			/* _hoops_HSGR _hoops_RH _hoops_ASGH _hoops_HIHRC, _hoops_PPR _hoops_IIHRC _hoops_CPS _hoops_CRGR _hoops_SPR _hoops_SCGI
			* _hoops_IAS._hoops_ISHI. _hoops_HII _hoops_AHHS:  _hoops_SCGI = _hoops_CIHRC (_hoops_SIHRC, _hoops_GCHRC); */
			ZALLOC (_hoops_RRHA, OGL_Display_List_Bin);
			_hoops_RRHA->_hoops_CRHA = _hoops_CSRGR->_hoops_CIGI->_hoops_HRPI;
			_hoops_CSRGR->_hoops_CIGI->_hoops_HRPI = null;
			_hoops_RRHA->nr = nr;
			_hoops_RRPI->AddFirst(_hoops_RRHA);

			_hoops_RRPI->ResetCursor();
			/* _hoops_RH _hoops_HSPR _hoops_HAPR _hoops_CGH _hoops_PSRC _hoops_GPCPR _hoops_ARR */
			while ((_hoops_RRHA = _hoops_RRPI->PeekCursor()) != null) {
				Polyedge *pe;
				OGL_Display_List *_hoops_CRPI, *odl;
				GLuint id;
				_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
				_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;
				bool _hoops_ARPI;
				Line_Rendition const &_hoops_HC = _hoops_RRHA->nr->_hoops_AHP;
				int weight;

				weight = _hoops_HC->weight;
				if (weight < 0)
					weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
				if (BIT(_hoops_HC->flags, _hoops_SRPI) ||
					_hoops_GAPI (_hoops_CSRGR, _hoops_HC, weight)) {
					while ((pair = _hoops_RRHA->_hoops_CRHA->RemoveFirst()) != null) {
						if (!_hoops_IHGI)
							segment_render (pair->nr, (Geometry *)pair->geo, _hoops_RAPI, pair->single);
						delete pair;
					}
					if (dl)
						dl->action_mask |= _hoops_IRPI;
				}
				else {
					//_hoops_RH _hoops_HSPR _hoops_AASA _hoops_GACC _hoops_SIHR _hoops_ASCA _hoops_RAR-_hoops_AAR _hoops_RRRC _hoops_GGR _hoops_HGAI _hoops_CCH
					//(_hoops_AIH _hoops_RCHRC)
					_hoops_AHHRC (_hoops_RRHA->nr, _hoops_RRHA, &_hoops_ARPI, &dl->action_mask, _hoops_IHGI);
					if (_hoops_ARPI) {
						dl->_hoops_PRRI |= _hoops_RPCGP;
						if (nr->_hoops_ARA->_hoops_APPI._hoops_SAR)
							dl->_hoops_PRRI |= _hoops_APCGP;
						else
							dl->_hoops_PRRI &= ~_hoops_APCGP;
					}
					if (_hoops_RRHA->_hoops_CRHA->Count() > 0) {
						Action_Mask _hoops_HPCI = dc->_hoops_IPCI->mask;
						_hoops_APARR alter &_hoops_RRCI = dc->_hoops_IPCI;

						_hoops_RRCI->mask |= _hoops_ASRI;
						if (!_hoops_GIGI) {
							ZALLOC(odl, OGL_Display_List);
							AGLM(odl->_hoops_CSRGR = OGLD(dc));
							odl->_hoops_GHRI = dc->_hoops_GHRI;
							odl->time_stamp = HOOPS_WORLD->_hoops_GPPI;
							odl->type = OGL_DL_GEOMETRY;
							id = glGenLists(1);
							glNewList (id, GL_COMPILE);
							_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = true;
							_hoops_RRHA->_hoops_CRHA->ResetCursor();
							for (;;) {
								pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
								if (!pair)
									break;
								pe = (Polyedge *)pair->geo;
								odl->item.geometry._hoops_IGGI.total += pe->total;
								odl->item.geometry._hoops_IGGI._hoops_PHHA += pe->_hoops_PHHA;
								odl->item.geometry._hoops_IGGI.point_count += pe->point_count;
								dc->_hoops_SPA->modelling_matrix = pair->_hoops_CPAI;
								dc->_hoops_SPA->color = pair->color;
								_hoops_CHGI->_hoops_CARH += _hoops_ARHRC (pe);
								draw_3d_polyedge(nr, pe);
								_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
							}
							dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
							dc->_hoops_SPA->color = _hoops_GGRI;
							_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = false;
							glEndList ();
							HOOPS_WORLD->display_list_vram_usage += _hoops_CHGI->_hoops_CARH;
							odl->type = OGL_DL_GEOMETRY;
							odl->item.geometry.id = id;

							/* _hoops_IPIH _hoops_ACHRC _hoops_GPRR, _hoops_HIH _hoops_RRP _hoops_IS _hoops_ARGAR _hoops_SGS _hoops_CRGR _hoops_PCHRC _hoops_GPRR */
							_hoops_CRPI = _hoops_PRGAR (nr, odl, _hoops_ARPI);
							ASSERT (odl->type == OGL_DL_GEOMETRY);
							ASSERT (_hoops_CRPI->type == OGL_DL_SEGMENT_POLYLINE);
							ASSERT (_hoops_CHGI->type == OGL_DL_SEGMENT_TREE);
							ASSERT (_hoops_CRPI->item._hoops_RPPI.pe != null);
							ASSERT (BIT (_hoops_CRPI->item._hoops_RPPI.pe->_hoops_SRHA, DL_LIGHTWEIGHT_DISPLAY_LIST));
							ASSERT (_hoops_CRPI->item._hoops_RPPI.pe->_hoops_GAHA != 0);
							FREE(odl, OGL_Display_List);
							if (_hoops_CHGI->item._hoops_ACGI._hoops_CAPI == null)
								_hoops_CHGI->item._hoops_ACGI._hoops_CAPI = POOL_NEW(dc->memory_pool, OGL_Display_List_List)(dc->memory_pool);
							_hoops_CHGI->item._hoops_ACGI._hoops_CAPI->AddLast(_hoops_CRPI);
							_hoops_AHAI = true;
						}
						else {
							_hoops_RRHA->_hoops_CRHA->ResetCursor();
							dc->_hoops_SPA->modelling_matrix = null;
							if (!_hoops_IHGI) {
								for (;;) {
									pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
									if (!pair)
										break;
									pe = (Polyedge *)pair->geo;
									pe->_hoops_SRHA |= _hoops_SRHH;
									really_draw_3d_polyedge (pair->nr, pair->nr->_hoops_AHP, pe, null);
									_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
								}
								_hoops_RRCI->mask = _hoops_HPCI;
							}
							dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
							dl->action_mask |= _hoops_IRPI;
						}
					}
				}
				while ((pair = _hoops_RRHA->_hoops_CRHA->RemoveFirst()) != null) {
					pe = (Polyedge *) pair->geo;
					ASSERT (pe->_hoops_GAHA == null);
					delete pair;
				}
				_hoops_RRHA->odl = null;
				if (_hoops_RRHA->_hoops_CRHA)
					delete _hoops_RRHA->_hoops_CRHA;
				_hoops_RRHA->nr.release();
				FREE (_hoops_RRHA, OGL_Display_List_Bin);
				_hoops_RRPI->AdvanceCursor();
			}
			delete _hoops_RRPI;
		}

		if (_hoops_GPHRC)
			dc->flags |= _hoops_CHSI;
		else
			dc->flags &= ~_hoops_CHSI;

		/* _hoops_SP _hoops_GH _hoops_IARI _hoops_CPCI (_hoops_RPP _hoops_SSIA _hoops_GSAHA'_hoops_RA _hoops_AIAH _hoops_HCHRC)*/
		if (_hoops_CSRGR->_hoops_CIGI->_hoops_HRPI) {
			_hoops_IPSGC *	pair;
			while ((pair = _hoops_CSRGR->_hoops_CIGI->_hoops_HRPI->RemoveFirst()) != null)
				delete pair;
			delete _hoops_CSRGR->_hoops_CIGI->_hoops_HRPI;
			_hoops_CSRGR->_hoops_CIGI->_hoops_HRPI = null;
		}
	}

	if (_hoops_CSRGR->_hoops_CIGI &&
		_hoops_CSRGR->_hoops_CIGI->_hoops_IHGI)
		_hoops_AHAI = false;

	if (_hoops_AHAI &&
		_hoops_CHGI->item._hoops_ACGI._hoops_CAPI &&
		BIT (nr->_hoops_RGP, T_LINES)) {
		OGL_Display_List *odl;
		OGL_Display_List_List *_hoops_AACI = _hoops_CHGI->item._hoops_ACGI._hoops_CAPI;
		Polyedge *pe;

		/* _hoops_CACI _hoops_RHIR _hoops_RH _hoops_HIGR _hoops_PPR _hoops_PGSA _hoops_HCR _hoops_IIGR _hoops_CAPR! */
		_hoops_AACI->ResetCursor();
		while ((odl = _hoops_AACI->PeekCursor()) != null) {
			ASSERT (odl->type == OGL_DL_SEGMENT_POLYLINE);
			pe = odl->item._hoops_RPPI.pe;
			really_draw_3d_polyedge (nr, nr->_hoops_AHP, pe, null);
			_hoops_AACI->AdvanceCursor();
		}
	}

} /* _hoops_RSGR _hoops_API '_hoops_RSGR _hoops_ISII _hoops_AIRI _hoops_HIGR' */



/* _hoops_RAGC _hoops_RH _hoops_HAHH _hoops_AAGC _hoops_IPI _hoops_PAGC _hoops_GPP _hoops_IRS _hoops_AIRI _hoops_HIGR
 * _hoops_IH _hoops_RH _hoops_AHAR _hoops_IIGR _hoops_HAGC _hoops_IRS _hoops_HSSI _hoops_IAGC */
local void _hoops_CAGC (
	Net_Rendition const & nr,
	OGL_Display_List *_hoops_CHGI)
{
	Display_Context const *dc = nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLD(dc);
	int delta = 0, _hoops_SAGC = 0, _hoops_ICHRC = 0;
	int _hoops_GPGC = 0;
	_hoops_AIGI *list;
	_hoops_IPSGC *pair;

	if (_hoops_CSRGR->_hoops_CIGI->_hoops_RCGI) {
		list = _hoops_CSRGR->_hoops_CIGI->_hoops_RCGI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Tristrip const *ts = (Tristrip const *) pair->geo;
			delta = _hoops_RRHRC (ts);
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
	}
	if (_hoops_CSRGR->_hoops_CIGI->_hoops_IIRI) {
		list = _hoops_CSRGR->_hoops_CIGI->_hoops_IIRI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Polyedge const *pe = (Polyedge const *) pair->geo;
			delta = _hoops_ARHRC (pe);
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
	}
	if (_hoops_CSRGR->_hoops_CIGI->_hoops_HHAI) {
		list = _hoops_CSRGR->_hoops_CIGI->_hoops_HHAI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Polymarker *pm = (Polymarker *)pair->geo;
			delta = _hoops_PSSH (pm);
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
	}

	if (_hoops_CSRGR->_hoops_CIGI->_hoops_CIRI) {
		list = _hoops_CSRGR->_hoops_CIGI->_hoops_CIRI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Polyedge const *pe = (Polyedge const *) pair->geo;
			delta = _hoops_ARHRC (pe);
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
	}
	if (_hoops_CSRGR->_hoops_CIGI->_hoops_SIRI) {
		list = _hoops_CSRGR->_hoops_CIGI->_hoops_SIRI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Polyedge const *pe = (Polyedge const *) pair->geo;
			delta = _hoops_ARHRC (pe);
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
	}
	if (_hoops_CSRGR->_hoops_CIGI->_hoops_HRPI) {
		list = _hoops_CSRGR->_hoops_CIGI->_hoops_HRPI;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Geometry *g = (Geometry *)pair->geo;
			delta = _hoops_GSII (g, pair->single);
			_hoops_GPGC += delta;
			list->AdvanceCursor();
		}
		_hoops_SAGC += list->Count();
	}
	if (_hoops_CSRGR->_hoops_CIGI->_hoops_IIII) {
		list = _hoops_CSRGR->_hoops_CIGI->_hoops_IIII;
		list->ResetCursor();
		while ((pair = list->PeekCursor()) != null) {
			Polygon *p = (Polygon *)pair->geo;
			if (p->type == _hoops_RCIP) {
				delta = 24 * p->count + 24;
			}
			else {
				//_hoops_GA'_hoops_RA _hoops_ACPA _hoops_GAPR _hoops_RSH _hoops_AHPH _hoops_RSSA _hoops_SCH'_hoops_GCPP _hoops_IRAA _hoops_IS _hoops_CCHRC _hoops_GIAA _hoops_GPSGA,
				//_hoops_SAHR _hoops_AHGC _hoops_GSPCA _hoops_AARI 100 _hoops_RIR _hoops_CHCA
				delta = 24 * 100;
			}
			_hoops_GPGC += delta;
			_hoops_ICHRC++;
			list->AdvanceCursor();
		}
		_hoops_SAGC += _hoops_ICHRC;
	}
	if (!_hoops_GPGC)
		return; 

	/* _hoops_PHGC _hoops_RIPI _hoops_HPP _hoops_AIPP (_hoops_SR _hoops_HHGC _hoops_IS _hoops_IHGC _hoops_RH _hoops_CHGC _hoops_SHGC _hoops_IPIH _hoops_CISI _hoops_AIRI _hoops_HIGR) */
	float _hoops_GIGC = (float)_hoops_GPGC / _hoops_SAGC;  
	if (HI_Push_Display_List (dc->_hoops_RIGC, _hoops_CHGI->_hoops_PPAH, _hoops_GIGC, _hoops_GPGC))
		_hoops_CHGI->item._hoops_ACGI.flags |= OGL_DL_BLESSED_SEGMENT;
}


/*
 * _hoops_SRAC
 */
local void
_hoops_AIGC(
		Net_Rendition const &nr,
		_hoops_GACR **_hoops_PICI,
		bool _hoops_IHGI)
{
	Display_Context const *dc = nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLD(dc);
	Integer32 _hoops_PIGC;
	OGL_Collector *_hoops_PRRC;
	_hoops_GACR alter *dl;
	OGL_Display_List *_hoops_CHGI;

	_hoops_RAPRC("end_display_list", false);

	if (_hoops_CSRGR->_hoops_CIGI != null) {

		if (_hoops_CSRGR->_hoops_CIGI->_hoops_SIGI)
			_hoops_GPRH(_hoops_HIGC)++;

		/* _hoops_SSPC _hoops_ASRC _hoops_RRGR _hoops_HII _hoops_SCHRC -- _hoops_SR _hoops_GA'_hoops_RA _hoops_PICP _hoops_RPP _hoops_CCAH _hoops_PAR _hoops_HAR */
		_hoops_AACR(nr, &(*_hoops_PICI), &dl, &_hoops_CHGI, OGL_DL_SEGMENT_TREE);

		if (!_hoops_IACI(dc)) {
			_hoops_ACHR _hoops_RGP = nr->_hoops_RGP;

			if (BIT (nr->_hoops_ARA->_hoops_CICP._hoops_RGP, T_EDGES)) {
				_hoops_RGP |= _hoops_GPA;
				if (_hoops_CPGI (nr->_hoops_IRR)) {
					_hoops_RGP &= ~(T_FACES);
					_hoops_RGP |= nr->_hoops_ARA->_hoops_CICP._hoops_RGP & (T_FACES);
				}
			}
			if (!BIT(nr->transform_rendition->flags,_hoops_GRHH))
				_hoops_RGP &= ~(T_LIGHTS_FOR_FACES | T_LIGHTS_FOR_EDGES | T_LIGHTS_FOR_MARKERS);
			if (!BIT (_hoops_RGP, T_FACES))
				_hoops_RGP &= ~T_LIGHTS_FOR_FACES;
			if (!BIT (_hoops_RGP, _hoops_PSRI))
				_hoops_RGP &= ~T_LIGHTS_FOR_EDGES;
			if (!BIT (_hoops_RGP, T_VERTICES))
				_hoops_RGP &= ~T_LIGHTS_FOR_MARKERS;

			_hoops_CHGI->item._hoops_ACGI._hoops_CSPRC = _hoops_PSPRC(nr->_hoops_IRR);
			_hoops_CHGI->item._hoops_ACGI._hoops_GGHRC |= _hoops_CSRGR->_hoops_CIGI->_hoops_GGHRC;
			_hoops_CHGI->item._hoops_ACGI._hoops_RGP |= _hoops_RGP;
			if (BIT(dc->flags, _hoops_IIGC)) {
				//_hoops_RPP _hoops_CPAP _hoops_HRGR _hoops_CIGC, _hoops_HSII _hoops_SCH _hoops_GAR _hoops_RPP _hoops_SCH _hoops_AAPR _hoops_HAR _hoops_SIGC _hoops_IH _hoops_RH
				//_hoops_GCGC _hoops_IIGR _hoops_IRS _hoops_HCH _hoops_ICH _hoops_AIRI _hoops_HIGR _hoops_HCGI
				_hoops_ACHR _hoops_RCGC = dc->_hoops_AHSI->segment->_hoops_RCGC;
				if (BIT (_hoops_RCGC, T_FACES) &&
					!BIT (nr->_hoops_PSGI, T_FACES))
					_hoops_RGP &= ~T_FACES;
				if (BIT (_hoops_RCGC, T_LINES) &&
					!BIT (nr->_hoops_PSGI, T_LINES))
					_hoops_RGP &= ~T_LINES;
				if (BIT (_hoops_RCGC, T_EDGES) &&
					!BIT (nr->_hoops_PSGI, T_EDGES))
					_hoops_RGP &= ~T_EDGES;
				//_hoops_SRSA _hoops_GASA _hoops_PIP: _hoops_PA _hoops_IS _hoops_AA _hoops_ARI _hoops_IH _hoops_ACGC?
				if (BIT (_hoops_RCGC, T_VERTICES) &&
					!BIT (nr->_hoops_PSGI, T_VERTICES))
					_hoops_RGP &= ~T_VERTICES;
				if (BIT (_hoops_RCGC, T_MARKERS) &&
					!BIT (nr->_hoops_PSGI, T_MARKERS))
					_hoops_RGP &= ~T_MARKERS;
				if (BIT (_hoops_RCGC, T_TEXT) &&
					!BIT (nr->_hoops_PSGI, T_TEXT))
					_hoops_RGP &= ~T_TEXT;

				//_hoops_RH _hoops_HSPR _hoops_PCGC _hoops_PSSP _hoops_HCGC _hoops_GGR _hoops_ICGC _hoops_SGS 
				//_hoops_ASSI _hoops_CPAP _hoops_SGS _hoops_HRGR _hoops_CCGC _hoops_RRH
				if (BIT (_hoops_RGP, T_FACES) && 
					nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR == 0 && 
					!nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR)
					_hoops_RGP &= ~T_FACES;
				if (BIT (_hoops_RGP, T_EDGES) && 
					nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR == 0 && 
					!nr->_hoops_RHP->_hoops_CHA->_hoops_ARIR)
					_hoops_RGP &= ~T_EDGES;
				if (BIT (_hoops_RGP, T_VERTICES) && 
					nr->_hoops_SCP->_hoops_CHA->_hoops_IRIR == 0 && 
					!nr->_hoops_SCP->_hoops_CHA->_hoops_ARIR)
					_hoops_RGP &= ~T_VERTICES;
			}
			if (BIT (_hoops_RGP, T_FACES)) {
				dl->action_mask &= ~_hoops_PGRI;
				if (_hoops_CSRGR->_hoops_CIGI->_hoops_CIRI)
					_hoops_RGP |= T_EDGES;
				if (_hoops_CSRGR->_hoops_CIGI->_hoops_SIRI)
					_hoops_RGP |= _hoops_GPA;
			}
			if (ANYBIT (_hoops_RGP, _hoops_PSRI))
				dl->action_mask &= ~_hoops_IGAI;
			if (BIT (_hoops_RGP, _hoops_GPA))
				dl->action_mask &= ~_hoops_RSRI;
			if (ANYBIT (_hoops_RGP, T_VERTICES))
				dl->action_mask &= ~_hoops_RGPI;
			if (ANYBIT (_hoops_RGP, T_MARKERS))
				dl->action_mask &= ~_hoops_HCIP;
			if (BIT (_hoops_RGP, T_LINES))
				dl->action_mask &= ~_hoops_IRPI;
			if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE))
				dl->action_mask &= ~(_hoops_ACIP|_hoops_ARCP);
		}
		if (_hoops_CSRGR->_hoops_CIGI->_hoops_SIGI) {
			if (ANYBIT (_hoops_CSRGR->_hoops_CIGI->_hoops_PRGC, _hoops_PGRI))
				dl->action_mask |= _hoops_PGRI;
			if (ANYBIT (_hoops_CSRGR->_hoops_CIGI->_hoops_PRGC, _hoops_ASRI|_hoops_GHCI))
				dl->action_mask |= _hoops_IGAI;
			if (BIT (_hoops_CSRGR->_hoops_CIGI->_hoops_PRGC, _hoops_RSRI))
				dl->action_mask |= _hoops_RSRI;
			if (BIT (_hoops_CSRGR->_hoops_CIGI->_hoops_PRGC, _hoops_RGPI))
				dl->action_mask |= _hoops_RGPI;
			if (BIT (_hoops_CSRGR->_hoops_CIGI->_hoops_PRGC, _hoops_HCIP))
				dl->action_mask |= _hoops_HCIP;
			if (ANYBIT (_hoops_CSRGR->_hoops_CIGI->_hoops_PRGC, _hoops_IRPI))
				dl->action_mask |= _hoops_IRPI;
			if (BIT (_hoops_CSRGR->_hoops_CIGI->_hoops_PRGC, _hoops_ACIP))
				dl->action_mask |= _hoops_ACIP;
		}

		dl->action_mask |= (_hoops_CSRGR->_hoops_CIGI->_hoops_PRGC ^ _hoops_CSRGR->_hoops_CIGI->mask);
		dl->action_mask |= dc->_hoops_SCGC;
		dl->action_mask |= dc->_hoops_GSGC;
		if (BIT (dc->_hoops_GSGC, _hoops_SHSI))
			dl->action_mask |= _hoops_PCSI;
		dl->action_mask |= nr->_hoops_RSGC->action_mask; /* _hoops_ASGC _hoops_ASSI _hoops_AIRI _hoops_CPCI */
		if (!_hoops_IACI(dc) &&
			!_hoops_CSRGR->_hoops_CIGI->_hoops_SIGI)
			dl->action_mask &= ~_hoops_CSRGR->_hoops_CIGI->_hoops_RRSI;

		/* _hoops_GSHRC _hoops_GH _hoops_HCR _hoops_RH _hoops_RSHRC _hoops_PIH, _hoops_HASC, _hoops_PGSA, _hoops_AHI. */
		_hoops_PIGC = _hoops_CSRGR->_hoops_ISCI;
		_hoops_CSRGR->_hoops_ISCI = 0;

		if (!BIT (_hoops_CHGI->item._hoops_ACGI.flags, OGL_DL_BLESSED_SEGMENT)) {
			if (_hoops_CSRGR->_hoops_CIGI->_hoops_ASHRC ||
				BIT(dc->flags, _hoops_IIGC)) {
				_hoops_CHGI->item._hoops_ACGI.flags |= OGL_DL_BLESSED_SEGMENT;
			}
			else {
				//_hoops_PSHRC _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_GAR _hoops_HSHRC (_hoops_RPP _hoops_IRPR) _hoops_PPR _hoops_CGPAA _hoops_SCH _hoops_CIAA _hoops_RH _hoops_GRRI _hoops_SIHPA
				_hoops_CAGC (nr, _hoops_CHGI);
			}
		}

		_hoops_HHGI (nr, dl, _hoops_IHGI);
		_hoops_PIRI (nr, dl, _hoops_IHGI);
		_hoops_RHAI (nr, dl, _hoops_IHGI); /* _hoops_AGRC _hoops_GIHA _hoops_PPR _hoops_SAIA */
		_hoops_SGPI (nr, dl, _hoops_IHGI); /* _hoops_AGRC _hoops_APGR, _hoops_GRRC _hoops_PPR _hoops_RRRC */
		_hoops_HIII (nr, dl, _hoops_IHGI);  /* _hoops_GSCA _hoops_HSSP _hoops_RSSI _hoops_PPR _hoops_HSSP _hoops_SPPR */

		/* _hoops_HSCI _hoops_RH _hoops_IARI */
		_hoops_PRRC = _hoops_CSRGR->_hoops_CIGI->next;
		_hoops_CSRGR->_hoops_CIGI->nr.release();
		FREE (_hoops_CSRGR->_hoops_CIGI, OGL_Collector);
		_hoops_CSRGR->_hoops_CIGI = _hoops_PRRC;
		_hoops_CSRGR->_hoops_ISCI = _hoops_PIGC - 1;
	}

} /* _hoops_RSGR _hoops_API '_hoops_RSGR _hoops_AIRI _hoops_CPCI' */



#define _hoops_ISHRC(_hoops_PPIGP, geom_type) \
	int _hoops_CPIGP = _hoops_IIAGR(geom_type); \
	if (_hoops_PPIGP->next == null) { \
		_hoops_PPIGP = null; \
		break; \
	} \
	if (_hoops_PPIGP->owner == null) { \
		do if ((_hoops_PPIGP = _hoops_PPIGP->next) == null) \
			break; \
		_hoops_RGGA (_hoops_PPIGP->type != geom_type); \
		break; \
	} \
	else for (;;) { \
		_hoops_CPIGP++; \
		if (_hoops_CPIGP > _hoops_RACP) { \
			_hoops_PPIGP = null; \
			break; \
		} \
		if (_hoops_PPIGP->owner->_hoops_GACP->_hoops_AACP (_hoops_CPIGP) != null) { \
			_hoops_PPIGP = _hoops_PPIGP->owner->_hoops_GACP->_hoops_AACP (_hoops_CPIGP); \
			break;\
		} \
	}


/*
* _hoops_PGAA
*/
local bool _hoops_RHIP (
	Action_Mask				mask,
	Geometry const *		g) {
	Type					type = g->type;

	if (type == _hoops_AHIP) {
		_hoops_PHIP const *		_hoops_RRA = (_hoops_PHIP const *)g;

		for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++)
			if (_hoops_RHIP (mask, (Geometry const *)_hoops_RRA->_hoops_IHIP[i]))
				return true;
		return false;
	}

	switch (type) {
		case _hoops_CHIP:
			return	BIT (mask, _hoops_SHIP);

		case _hoops_GIIP:
		case _hoops_RIIP:
			return	BIT (mask, _hoops_AIIP);

		case _hoops_PIIP:
		case _hoops_HIIP:
		case _hoops_IIIP:
			return	BIT (mask, _hoops_CIIP);

		case _hoops_SIIP:
			return	BIT (mask, _hoops_GCIP);

		case _hoops_RCIP:
			return	BIT (mask, _hoops_ACIP);

		case _hoops_PCIP:
			return	BIT (mask, _hoops_HCIP);

		case _hoops_ICIP:
			return	BIT (mask, _hoops_CCIP);

		case _hoops_SCIP:
		case _hoops_GSIP:
			return	BIT (mask, _hoops_RSIP);

		case _hoops_ASIP:
			return	BIT (mask, _hoops_PSIP);

		case _hoops_HSIP:
			return	BIT (mask, _hoops_ISIP);

		case _hoops_CSIP:
			return	BIT (mask, _hoops_SSIP);

		case _hoops_GGCP:
			return	BIT (mask, _hoops_RGCP);

		case _hoops_AGCP:
			return	BIT (mask, _hoops_PGCP);

		case _hoops_HGCP:
			return	BIT (mask, _hoops_IGCP);

		case _hoops_CGCP:
		case _hoops_SGCP:
		case _hoops_GRCP:
		case _hoops_RRCP:
			return	BIT (mask, _hoops_ARCP);

		case _hoops_PRCP:
			return	BIT (mask, _hoops_HRCP);

		case _hoops_IRCP: {
			_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *) g;
			Geometry const *	geo;

			if (_hoops_SRCP->_hoops_GACP) {
				for (int i = 0; i < _hoops_RACP; i++) {
					geo = _hoops_SRCP->_hoops_GACP->_hoops_AACP (i);
					if (geo && _hoops_RHIP (mask, geo))
						return true;
				}
			}
			else {
				geo = _hoops_SRCP->geometry;
				while (geo) {
					if (_hoops_RHIP (mask, geo))
						return true;
					geo = geo->next;
				}
			}
			return false;
		}

		default:
			return false;
	}
}


local bool
_hoops_HSHS (
		Net_Rendition const &nr,
		Geometry const *g,
		bool single)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	
	if (BIT (_hoops_CSRGR->_hoops_CIGI->_hoops_RRSI, _hoops_CIIP))
		return true;  //_hoops_ISII _hoops_HRGR _hoops_AIAH _hoops_GPP _hoops_RH _hoops_AIRI _hoops_HIGR.

	if (dc->_hoops_SPA->color != null && 
		_hoops_CCAI (dc->_hoops_SPA->color, Color_LINE))
		_hoops_CSRGR->_hoops_CIGI->_hoops_GGHRC |= Color_LINE;

	_hoops_IPSGC *pair = POOL_NEW(dc->memory_pool, _hoops_IPSGC)(nr, g, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color, single);

	if (!_hoops_CSRGR->_hoops_CIGI->_hoops_HRPI)
		_hoops_CSRGR->_hoops_CIGI->_hoops_HRPI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

	_hoops_CSRGR->_hoops_CIGI->_hoops_HRPI->AddFirst(pair);
	return true;
}


/*
 * _hoops_SRAC
 */
local Geometry const *
segment_render (
		Net_Rendition const & _hoops_GSAGR,
		Geometry const *_hoops_RSII,
		Action_Mask mask,
		bool _hoops_RSAGR)
{
	Display_Context alter *dc = _hoops_PGRCA(_hoops_GSAGR->_hoops_SRA);
	_hoops_ACHR _hoops_RGP;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	_hoops_CRCP const *start = _hoops_RSII->owner;
	Geometry const *g = _hoops_RSII;
	int _hoops_CSHRC = 0;
	bool _hoops_PSAGR = true;

	_hoops_RGP = _hoops_GSAGR->_hoops_RGP;

	if (dc->_hoops_SPA != dc->_hoops_ISAGR)
		_hoops_APSRR(dc, "resuming ref","", 0);

	do {
		Net_Rendition				nr = _hoops_GSAGR;
		bool						single = _hoops_RSAGR;

		if (dc->_hoops_SPA != dc->_hoops_ISAGR) {
			if ((g = dc->_hoops_SPA->geometry) == null) {
				g = dc->_hoops_SPA->_hoops_CSAGR;	// _hoops_IHIS _hoops_GPP _hoops_IS _hoops_GGAS
				_hoops_PSAGR = true;
			}
			nr = dc->_hoops_SPA->nr;
			single = dc->_hoops_SPA->single;
		}

		while (g) {
			_hoops_SSAGR(g);

			if (_hoops_PSAGR && _hoops_GGPGR(nr))
				return g;

			dc->_hoops_RAI = g;

			if (!BIT (nr->_hoops_RGPGR, _hoops_AGPGR(g->type))) {
				if (single)
					goto done;
				_hoops_PGPGR (g, g->type);
			}
			else switch (g->type) {
				case _hoops_PIIP:
				case _hoops_HIIP:
				case _hoops_IIIP:
					_hoops_CSHRC = _hoops_CIIP;
				case _hoops_CHIP:
					if (!_hoops_CSHRC)
						_hoops_CSHRC = _hoops_SHIP;
				case _hoops_GIIP:
				case _hoops_RIIP: {
					Type type = g->type;

					if (!_hoops_CSHRC)
						_hoops_CSHRC = _hoops_AIIP;

					if (BIT (_hoops_RGP, T_LINES)) {
						if (!single &&
							ANYBIT (mask, _hoops_IRPI)) {
							if (nr->_hoops_IRR->_hoops_GAHA == Display_List_GEOMETRY &&
								!_hoops_CSRGR->_hoops_ISCI) {

								bool _hoops_CRRS = (start != null);
								if (nr->_hoops_IRR->_hoops_SRI == _hoops_SICI &&
									BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI)) {
									Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
									int weight = _hoops_HC->weight;
									if (weight < 0)
										weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
									_hoops_CRRS = !_hoops_GAPI (_hoops_CSRGR, _hoops_HC, weight);
								}

								if (_hoops_CRRS) {
									Action_Mask			_hoops_SSHRC;
									_hoops_GPAGR	_hoops_RPAGR;
									_hoops_HICS		path;

									ASSERT(start != null);

									if (dc->_hoops_AHSI != null)
										path = dc->_hoops_AHSI->path;

									{
										_hoops_SPAGR				_hoops_GHAGR (start->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
										_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (start, path);

										if ((_hoops_RPAGR = _hoops_CSC->_hoops_PHAGR()) == null) {
											_hoops_RPAGR = _hoops_GPAGR::Create(dc->memory_pool);
											_hoops_CSC->_hoops_HHAGR (_hoops_RPAGR);
										}
									}

									_hoops_GGSI (_hoops_GSAGR, &_hoops_RPAGR->_hoops_GAHA, &_hoops_SSHRC, BIT(dc->flags, _hoops_CHSI));
									if (_hoops_CSRGR->_hoops_CIGI)
										_hoops_CSRGR->_hoops_CIGI->_hoops_ASHRC = true;
									_hoops_SSHRC &= _hoops_IRPI;
									if (_hoops_SSHRC)
										segment_render (_hoops_GSAGR, _hoops_RSII, _hoops_SSHRC, _hoops_RSAGR);
									if (_hoops_CSRGR->_hoops_ISCI)
										_hoops_AIGC (_hoops_GSAGR, &_hoops_RPAGR->_hoops_GAHA, BIT(dc->flags, _hoops_CHSI));
									mask &= ~_hoops_IRPI;
								}
							}
						}
						if (BIT (mask, _hoops_CSHRC)) {
							if (!_hoops_CSRGR->_hoops_ISCI ||
								!_hoops_HSHS (nr, g, single))
							{
								_hoops_CSRGR->_hoops_AHPI = !single;
								switch (type) {
									case _hoops_PIIP:
									case _hoops_HIIP:
									case _hoops_IIIP:
										draw_3d_polyline (nr, (Polyline const *)g);
									break;
									case _hoops_CHIP:
										draw_3d_nurbs_curve (nr, (_hoops_PIRGR const *)g);
									break;
									case _hoops_RIIP:
									case _hoops_GIIP:
										do {
											_hoops_PPAGR (nr, (Elliptical_Arc const *) g);
											g = g->next;
											if (!_hoops_CSRGR->_hoops_AHPI)
												break;
										} while (g && g->type == type);
									break;
								}
								_hoops_CSRGR->_hoops_AHPI = false;
							}
						}
					}
					_hoops_CSHRC = 0; //_hoops_HIAP _hoops_IH _hoops_RH _hoops_SPS _hoops_CPAP _hoops_GPRR
					if (single)
						goto done;
					_hoops_CSHI (g, type);
				} break;

				case _hoops_SIIP:
					if (_hoops_CSRGR->_hoops_CIGI)
						_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_GCIP;
					if (BIT (mask, _hoops_GCIP) && BIT (_hoops_RGP, T_LINES)) {
						do {
							dc->_hoops_RAI = g;
							_hoops_IGPGR (nr, (Polyline const *) g);
							if (single || (g = g->next) == null)
								goto done;
						} _hoops_RGGA (g->type != _hoops_SIIP);
					}
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_SIIP);
				break;

				case _hoops_RCIP: {
					if (ANYBIT (_hoops_RGP, T_ANY_POLYGON_EDGE | T_FACES) &&
						BIT (mask, _hoops_ACIP)) {
							if (_hoops_CSRGR->_hoops_CIGI) {
								if (_hoops_HSIS (nr, (Polygon const *)g, single))
									_hoops_CSHI (g, _hoops_RCIP);
								_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_ACIP;
							}
							_hoops_CSRGR->_hoops_AHPI = !single;
							dc->_hoops_RAI = g;
							_hoops_SGPGR (nr, (Polygon const *)g);
							_hoops_CSRGR->_hoops_AHPI = false;
						}
						if (single)
							goto done;
						_hoops_CSHI (g, _hoops_RCIP);
					}
				break;

				case _hoops_PCIP:
					if (BIT (mask, _hoops_HCIP) && BIT (_hoops_RGP, T_MARKERS)) {
						_hoops_CSRGR->_hoops_AHPI = !single;
						dc->_hoops_RAI = g;
						draw_3d_marker (nr, (Marker const *)g);
						_hoops_CSRGR->_hoops_AHPI = false;
					}
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_PCIP);
				break;

				case _hoops_PIRS:
					if (BIT (mask, _hoops_HCIP) && BIT (_hoops_RGP, T_MARKERS)) {
						do {
							dc->_hoops_RAI = g;
							HD_Std_3D_Multimarker (nr, (_hoops_GRPGR const *)g);
							if (single || (g = g->next) == null)
								goto done;
						} while (g->type == _hoops_PIRS);
					}
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_PIRS);
				break;
				/*
				 * _hoops_PS _hoops_PAH _hoops_SSPC _hoops_AGCR - _hoops_SSIA _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_SHH _hoops_CHCC
				 */
				case _hoops_HGPGR:
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_HGPGR);
				break;

				/*
				 * _hoops_IPCP _hoops_HSPR _hoops_IGCGA _hoops_CHR _hoops_HAH _hoops_RHRCP _hoops_IS _hoops_SHH _hoops_CHCC
				 * _hoops_ARI _hoops_GGR _hoops_RH _hoops_RHPP - _hoops_CAH _hoops_ISSC _hoops_IS _hoops_AAPA-_hoops_PAPA.
				 */
				case _hoops_ICIP:
					if (BIT (mask, _hoops_CCIP) && BIT (_hoops_RGP, T_ANY_LIGHTS)) {
						do {
							dc->_hoops_RAI = g;
							_hoops_RRPGR (nr, (Light const *) g);
							if (single || (g = g->next) == null)
								goto done;
						} _hoops_RGGA (g->type != _hoops_ICIP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_ICIP);
				break;

				case _hoops_GSIP: 
				case _hoops_SCIP: {
					Type type = g->type;
					if (_hoops_CSRGR->_hoops_CIGI) {
						_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_RSIP;
						if (!BIT (nr->_hoops_RGP, T_GENERIC_EDGES)) {
							if (BIT (nr->_hoops_RGP, T_INTERIOR_SILHOUETTE_EDGES))
								_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_RCSI;
							if (BIT (nr->_hoops_RGP, _hoops_GCSI))
								_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_ACSI;
						}
					}

					if (ANYBIT (mask, _hoops_RSIP|_hoops_PCSI)) {

						_hoops_CRCP *	_hoops_ARPGR;
						if ((_hoops_ARPGR = g->owner) != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(dc->_hoops_RIGC->thread_id);

						do {
							dc->_hoops_RAI = g;
							_hoops_HRPGR (nr, (Polyhedron const *) g);
							if (_hoops_IACI(dc)) {
								if (_hoops_ARPGR != null)
									_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
								return g;
							}

							if (single || (g = g->next) == null) {
								if (_hoops_ARPGR != null)
									_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
								goto done;
							}
						} _hoops_RGGA (g->type != type);

						if (_hoops_ARPGR != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, type);
				}	break;

				case _hoops_ASIP:
					if (_hoops_CSRGR->_hoops_CIGI)
						_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_PSIP;
					if (BIT (mask, _hoops_PSIP|_hoops_PCSI) &&
						ANYBIT (_hoops_RGP, T_FACES | T_ANY_SHELL_EDGE)) {
						do {
							dc->_hoops_RAI = g;
							_hoops_CRPGR (nr, (Cylinder const *) g);
							if (single || (g = g->next) == null)
								goto done;
						} _hoops_RGGA (g->type != _hoops_ASIP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_ASIP);
				break;

				case _hoops_CSIP:
					if (_hoops_CSRGR->_hoops_CIGI)
						_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_SSIP;
					if (BIT (mask, _hoops_SSIP|_hoops_PCSI) &&
						ANYBIT (_hoops_RGP, T_FACES | T_ANY_SHELL_EDGE)) {
						do {
							dc->_hoops_RAI = g;
							_hoops_GAPGR (nr, (PolyCylinder const *) g);
							if (single || (g = g->next) == null)
								goto done;
						} _hoops_RGGA (g->type != _hoops_CSIP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_CSIP);
				break;

				case _hoops_HSIP:
					if (_hoops_CSRGR->_hoops_CIGI)
						_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_ISIP;
					if (BIT (mask, _hoops_ISIP|_hoops_PCSI) &&
						ANYBIT (_hoops_RGP, T_FACES | T_ANY_SHELL_EDGE)) {

						do {
							dc->_hoops_RAI = g;
							_hoops_SRPGR (nr, (Sphere const *) g);
							if (single || (g = g->next) == null)
								goto done;
						} _hoops_RGGA (g->type != _hoops_HSIP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_HSIP);
				break;

				case _hoops_GGCP:
					/* _hoops_SR _hoops_RRP _hoops_IS _hoops_PCHIA _hoops_GGIRC'_hoops_GRI _hoops_GGR _hoops_SGHC _hoops_CCA _hoops_IPSIA _hoops_CCGR _hoops_SR _hoops_PAH _hoops_IRHH _hoops_CAPR _hoops_IPHR.
					 * _hoops_HGPP _hoops_SGHC _hoops_RGIRC _hoops_HAR _hoops_IS _hoops_HS _hoops_GSGS _hoops_RII _hoops_CPAP, _hoops_PHRI, _hoops_HIS _hoops_SCH _hoops_HRGR _hoops_PAHH
					 * _hoops_CPHP _hoops_IIGR _hoops_IRS _hoops_HISAR _hoops_GHCP */
					if (_hoops_CSRGR->_hoops_CIGI) {
						_hoops_CSRGR->_hoops_CIGI->_hoops_SIGI = true;
						_hoops_CSRGR->_hoops_CIGI->mask &= ~(_hoops_RGCP|_hoops_ACIP);
					}
					if (BIT (mask, _hoops_RGCP|_hoops_PCSI) &&
						ANYBIT (_hoops_RGP, T_FACES | T_ANY_GRID_EDGE | T_VERTICES)) {
						do {
							dc->_hoops_RAI = g;
							_hoops_RAPGR (nr, (Grid const *) g);
							if (single || (g = g->next) == null)
								goto done;
						} _hoops_RGGA (g->type != _hoops_GGCP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_GGCP);
				break;

				case _hoops_AGCP:
					if (_hoops_CSRGR->_hoops_CIGI)
						_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_PGCP;
					if (BIT (mask, _hoops_PGCP) && BIT (_hoops_RGP, T_TEXT)) {
						do {
							_hoops_HACC const *		text = (_hoops_HACC const *)g;

							dc->_hoops_RAI = g;
							if (text->count != 0 || text->_hoops_AAPGR != null)
								_hoops_PAPGR (nr, text);
							if (single || (g = g->next) == null)
								goto done;
						} _hoops_RGGA (g->type != _hoops_AGCP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_AGCP);
				break;

				case _hoops_HGCP:
					if (_hoops_CSRGR->_hoops_CIGI)
						_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_IGCP;
					if (BIT (mask, _hoops_IGCP) && BIT (_hoops_RGP, T_IMAGES)) {
						do {
							dc->_hoops_RAI = g;
							_hoops_HAPGR (nr, (Image const *) g);
							if (single || (g = g->next) == null)
								goto done;
						} _hoops_RGGA (g->type != _hoops_HGCP);
					}
					//_hoops_CGPGR
					if (single)
						goto done;
					_hoops_CSHI (g, _hoops_HGCP);
				break;

				case _hoops_GRCP:
				case _hoops_RRCP:
				case _hoops_CGCP:
				case _hoops_SGCP: {
					Type type = g->type;

					if (ANYBIT (_hoops_RGP, T_FACES | T_ANY_POLYGON_EDGE) &&
						BIT (mask, _hoops_ARCP)) {
						_hoops_CSRGR->_hoops_AHPI = !single;
						dc->_hoops_RAI = g;
						draw_3d_ellipse (nr, (Ellipse const *)g);
						_hoops_CSRGR->_hoops_AHPI = false;
					}
					if (single)
						goto done;
					//_hoops_CGPGR
					_hoops_CSHI (g, type);
				} break;

				case _hoops_PRCP:
					if (_hoops_CSRGR->_hoops_CIGI)
						_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_HRCP;
					if (BIT (mask, _hoops_HRCP|_hoops_PCSI) &&
						ANYBIT (_hoops_RGP, T_FACES|T_ANY_SHELL_EDGE)) {

						_hoops_CRCP *	_hoops_ARPGR;
						if ((_hoops_ARPGR = g->owner) != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(dc->_hoops_RIGC->thread_id);

						do {
							dc->_hoops_RAI = g;
							_hoops_RPPGR (nr, (_hoops_APPGR alter *) g);
							if (single || (g = g->next) == null) {
								if (_hoops_ARPGR != null)
									_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
								goto done;
							}
						} _hoops_RGGA (g->type != _hoops_PRCP);

						if (_hoops_ARPGR != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
					}

					if (single)
						goto done;
					//_hoops_CGPGR
					_hoops_CSHI (g, _hoops_PRCP);
				break;

				case _hoops_AHIP: {
					_hoops_PHIP const *	_hoops_RRA = (_hoops_PHIP const *)g;
					Geometry const *				_hoops_PPPGR = _hoops_RRA->next;

					if (dc->_hoops_SPA->_hoops_CSAGR != _hoops_RRA) {

						if (_hoops_RRA->condition.count == 0 ||
							 HI_Condition_Passed (nr->_hoops_ASIR->conditions.count,
												  nr->_hoops_ASIR->conditions._hoops_RCHA,
												  &_hoops_RRA->condition)) {

							bool _hoops_SIGI = false;

							if (_hoops_CSRGR->_hoops_CIGI &&
								_hoops_RRA->_hoops_IPPGR != null) {

								Attribute const *_hoops_HPPGR = _hoops_RRA->_hoops_IPPGR;
								_hoops_SSAGR(_hoops_HPPGR);

								_hoops_CSRGR->_hoops_CIGI->_hoops_CPPGR = true;

								do {
									_hoops_SSAGR(_hoops_HPPGR->next);
									ASSERT(_hoops_HPPGR->type <= _hoops_IAAA(HK_MODELLING_MATRIX,HK_USER_OPTIONS,HK_USER_VALUE,HK_COLOR));
									switch (_hoops_HPPGR->type) {
										case HK_MODELLING_MATRIX:
										case HK_USER_OPTIONS:
										case HK_USER_VALUE:
											break;
										case HK_COLOR: {
											_hoops_SSGI const *color = (_hoops_SSGI const *)_hoops_HPPGR;
											if (!HI_Color_Is_Simple (color, null))
												_hoops_SIGI = true;
										} break;
										default:
											_hoops_SIGI = true;
									}
								} while (!_hoops_SIGI && (_hoops_HPPGR = _hoops_HPPGR->next) != null);

								if (_hoops_SIGI)
									_hoops_CSRGR->_hoops_CIGI->_hoops_SIGI = _hoops_SIGI;
							}

							if (nr->_hoops_IRR->_hoops_GAHA != Display_List_SEGMENT ||
								(HD_Geometry_To_Action_Mask (g) & mask)) {
								if ((g = HD_Process_Geometry_Reference (nr, _hoops_RRA)) != null)
									goto _hoops_SPPGR;
							}
							nr = _hoops_GSAGR;
							single = _hoops_RSAGR;
							_hoops_PSAGR = false;
						}
					}
					else {
						if (nr->_hoops_IRR->_hoops_GAHA != Display_List_SEGMENT ||
							(HD_Geometry_To_Action_Mask (g) & mask)) {
							if ((g = HD_Process_Geometry_Reference (nr, _hoops_RRA)) != null)
								goto _hoops_SPPGR;
						}
						nr = _hoops_GSAGR;
						single = _hoops_RSAGR;
					}

					if (single || (g = _hoops_PPPGR) == null)
						goto done;
				}	  break;

				//_hoops_GASA _hoops_PIP:  _hoops_RGR _hoops_CSAP _hoops_IH _hoops_HHCI _hoops_IHCI (_hoops_CACH _hoops_AGIR 10623)
				case _hoops_HCIIR: {
					do {
						dc->_hoops_RAI = g;
						_hoops_PPCI (nr, (_hoops_GACR *)g);
						if (single || (g = g->next) == null)
							goto done;
					} _hoops_RGGA (g->type != _hoops_HCIIR);
				}	  break;

				/*
				 * _hoops_CPHP'_hoops_GRI _hoops_RHPH, _hoops_CSH _hoops_CGHA
				 */
				case _hoops_GHPGR: {
					_hoops_RHPGR *		_hoops_AHPGR = (_hoops_RHPGR *)g;
					_hoops_CRCP const *owner;

					owner = _hoops_AHPGR->owner;
					if (ANYBIT (_hoops_RGP, _hoops_AHPGR->which))
						_hoops_PHPGR (HEC_GL_DRIVER, HES_MEMORY_PURGED,
									 Sprintf_P (null, "Need to redraw all or some of '%p' -", owner),
									 "but memory has been purged from it");
					if (single || (g = g->next) == null)
						goto done;
				}	break;

				default:
					_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR,
											Sprintf_D (null, "Unknown type '%d' in render", g->type));
					goto done;
				_hoops_HHHI;
			}//_hoops_CICA

		}// _hoops_HPGP
  done:

	dc->_hoops_RAI = null;

	if (dc->_hoops_SPA != dc->_hoops_ISAGR) {
		dc->_hoops_SPA->geometry = null;
		//_hoops_AGIRC(_hoops_CSPH, "_hoops_CSPH->_hoops_PGIRC->_hoops_CPAP = _hoops_IRAP","", 0);
	}

  _hoops_SPPGR:;
	} while (dc->_hoops_SPA != dc->_hoops_ISAGR);

	return null;
} /* _hoops_RSGR _hoops_API '_hoops_CAGH _hoops_SRGS' */



/*
 * _hoops_SRAC
 */
local void
draw_3d_polyline (Net_Rendition const & nr,
				  Polyline const * polyline)
{
	Display_Context alter *dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	Point const *points;
	Point const *end;
	Polyline const *p = polyline;
	_hoops_IAPA const	*_hoops_CAPA = null;
	bool antialias = false;
	bool _hoops_CISP = false;
	bool _hoops_HAPRC = false;

	_hoops_RAPRC("draw_3d_polyline", true);

	if (_hoops_CSRGR->_hoops_ISCI) {
		if (dc->_hoops_RAI) {
			Type type = dc->_hoops_RAI->type;
			switch (type) {
				case _hoops_IIIP:
				case _hoops_HIIP:
				case _hoops_PIIP:
				case _hoops_GIIP:
				case _hoops_RIIP:
				case _hoops_CHIP: {
					_hoops_HSHS (nr, (Geometry const *)polyline, !_hoops_CSRGR->_hoops_AHPI);
					return;
				}
				default:
					//_hoops_AA _hoops_ISAP
					break;
			}
		}
		else {
			_hoops_HSHS (nr, (Geometry const *)polyline, !_hoops_CSRGR->_hoops_AHPI);
			return;
		}
		_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_CIIP;
	}

	if (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		int weight;
		bool _hoops_IAHC = false;

		weight = _hoops_HC->weight;
		if (weight < 0)
			weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);

		if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)&&
				weight==1&&!BIT(dc->_hoops_PGCC.flags, _hoops_SPPGH))
			_hoops_IAHC = true;
		else if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC)
			_hoops_IAHC = true;
		else if (BIT(_hoops_HC->flags, _hoops_SRPI) ||
				_hoops_GAPI (_hoops_CSRGR,_hoops_HC,weight))
			_hoops_IAHC = true;
		_hoops_CISP = (_hoops_HC->_hoops_CHA &&
						  _hoops_HC->_hoops_CHA->_hoops_IRIR < 1.0f);
		if (_hoops_CISP &&
			nr->_hoops_CPP->_hoops_PRH.style != _hoops_AIII &&
			nr->_hoops_CPP->_hoops_PRH._hoops_SRI != _hoops_PIII)
			_hoops_IAHC = true;

		if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
			_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;

			if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
				if (_hoops_GGH->_hoops_IRH == null)
					HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
				_hoops_CAPA = _hoops_GGH->_hoops_IRH;
				if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
					_hoops_IAHC = true;
			}
			else {
				_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
				if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
					_hoops_IAHC = true;
			}
		}

		if (_hoops_IAHC) {
			for (;;) {
				HD_Std_3D_Polyline (nr, p);
				if (!_hoops_CSRGR->_hoops_AHPI)
					break;
				p = (Polyline const *)p->next;
				if (p == null || p->type != polyline->type)
					break;
			}
			return;
		}

		antialias = BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) &&
					weight == 1 && BIT(dc->_hoops_PGCC.flags, _hoops_SPPGH);
		_hoops_HAPRC = (!BIT (nr->transform_rendition->flags, _hoops_CSP) ||
						  !XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_CUT_POINTS));

		_hoops_SCIGC (_hoops_CSRGR);

		_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;

		_hoops_GGGH(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		_hoops_AIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
		ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH||antialias);
		_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));
		OGL_SET_LINE_RENDITION (_hoops_CSRGR, nr, _hoops_HC);
		ENSURE_LINE_SMOOTH(_hoops_CSRGR, antialias);

	}
	for (;;) {
		if (polyline->type == _hoops_PIIP)
			_hoops_GPRH(_hoops_ICCA)++;
		else if (polyline->count <= 0)
			_hoops_GPRH(_hoops_ICCA) += -polyline->count / 2;
		else
			_hoops_GPRH(_hoops_ICCA) += polyline->count - 1;
		if (!_hoops_CSRGR->_hoops_AHPI)
			break;
		p = (Polyline const *)p->next;
		if (p == null || p->type != polyline->type)
			break;
	}

	do {
		if (_hoops_CAPA != null) {
			_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
		}
		/* _hoops_PPHHH _hoops_ISII _hoops_PAH _hoops_HS _hoops_GPRR _hoops_HGIRC, _hoops_IGIRC, _hoops_PAR _hoops_CGIRC */
		if (polyline->type == _hoops_PIIP) {
			Line const *	l = (Line const *)polyline;

			glBegin (GL_LINES);
			for (;;) {
				points = l->points;
				glVertex3fv ((GLfloat *) points++);
				glVertex3fv ((GLfloat *) points);
				if (!_hoops_CSRGR->_hoops_AHPI)
					break;
				l = (Line const *)l->next;
				if (l == null || l->type != _hoops_PIIP)
					break;
			}
			glEnd ();
			if (_hoops_HAPRC) {
				/* _hoops_SRCIA _hoops_APGR _hoops_RRS _hoops_SPR _hoops_AIR _hoops_ICHRR _hoops_IIGR _hoops_CAS _hoops_SR _hoops_HHGC _hoops_CAPR _hoops_IS, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS
				 * _hoops_HHSA _hoops_SGS _hoops_CGHI _hoops_AIR _hoops_IS _hoops_PGSA _hoops_CCA _hoops_IRS _hoops_SGIRC */
				_hoops_GPPRC (_hoops_CSRGR, 1);
				if (antialias)
					_hoops_AAPRC (_hoops_CSRGR, true);
				else
					_hoops_AAPRC (_hoops_CSRGR, false);

				l = (Line const *)polyline;

				glBegin (GL_POINTS);
				for (;;) {
					points = l->points;
					glVertex3fv ((GLfloat *) ++points);
					if (!_hoops_CSRGR->_hoops_AHPI)
						break;
					l = (Line const *)l->next;
					if (l == null || l->type != _hoops_PIIP)
						break;
				}
				glEnd ();
			}
		}
		else {
			bool	_hoops_GRIRC = false;
			Type	type = polyline->type;
			p = polyline;

			for (;;) {
				if (p->count > 1) {
					points = p->points;
					end = points + p->count;
					glBegin (GL_LINE_STRIP);
					do {
						glVertex3fv ((GLfloat *) points);
					} _hoops_RGGA (++points == end);
					glEnd ();
					if (_hoops_HAPRC) {
						--points;
						/* _hoops_SRCIA _hoops_APGR _hoops_RRS _hoops_SPR _hoops_AIR _hoops_ICHRR _hoops_IIGR _hoops_CAS _hoops_SR _hoops_HHGC _hoops_CAPR _hoops_IS, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS
						 * _hoops_HHSA _hoops_SGS _hoops_CGHI _hoops_AIR _hoops_IS _hoops_PGSA _hoops_CCA _hoops_IRS _hoops_SGIRC */
						_hoops_GPPRC (_hoops_CSRGR, 1);
						if (antialias)
							_hoops_AAPRC (_hoops_CSRGR, true);
						else
							_hoops_AAPRC (_hoops_CSRGR, false);
						glBegin (GL_POINTS);
							glVertex3fv ((GLfloat *) points);
						glEnd ();
					}
				}
				else if (p->count < -1)
					_hoops_GRIRC = true;
				if (!_hoops_CSRGR->_hoops_AHPI)
					break;
				p = (Polyline const *)p->next;
				if (p == null || p->type != type)
					break;
			}
			if (_hoops_GRIRC) {
				int length;
				p = polyline;
				glBegin (GL_LINES);
				for (;;) {
					if (p->count < -1) {
						points = p->points;
						length = -p->count;
						length &= ~0x1; //_hoops_ACASA _hoops_IS _hoops_PRGI
						end = points + length - 1;
						do {
							glVertex3fv ((GLfloat *) points++);
							glVertex3fv ((GLfloat *) points++);
						} while (points < end);
					}
					if (!_hoops_CSRGR->_hoops_AHPI)
						break;
					p = (Polyline const *)p->next;
					if (p == null || p->type != type)
						break;
				}
				glEnd ();
				if (_hoops_HAPRC) {
					_hoops_GPPRC (_hoops_CSRGR, 1);
					if (antialias)
						_hoops_AAPRC (_hoops_CSRGR, true);
					else
						_hoops_AAPRC (_hoops_CSRGR, false);
					glBegin (GL_POINTS);
					p = polyline;
					for (;;) {
						if (p->count < -1) {
							points = p->points;
							length = -p->count;
							length &= ~0x1; //_hoops_ACASA _hoops_IS _hoops_PRGI
							end = points + length - 1;
							do {
								glVertex3fv ((GLfloat *) &points[1]);
								points += 2;
							} while (points < end);
						}
						if (!_hoops_CSRGR->_hoops_AHPI)
							break;
						p = (Polyline const *)p->next;
						if (p == null || p->type != type)
							break;
					}
					glEnd ();
				}
			}
		}

		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);
}



local bool
_hoops_HSIS (
	Net_Rendition const &nr,
	Polygon const *p,
	bool single)
{
	Display_Context const *dc = nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	Type type = p->type;
	Action_Mask mask;
	_hoops_IPSGC *pair;

	UNREFERENCED(type);
	ASSERT (type == _hoops_RCIP);
	mask = _hoops_ACIP;

	if (_hoops_CSRGR->_hoops_CIGI->_hoops_SIGI)
		return false;

	if (dc->_hoops_RAI &&
		dc->_hoops_RAI->type != _hoops_RCIP)
		return false;

	/* _hoops_AAPI _hoops_PAH'_hoops_RA _hoops_HS _hoops_IRGH _hoops_ISHA _hoops_PAR _hoops_CPAP _hoops_AIRC, _hoops_HIS _hoops_IIH'_hoops_GRI _hoops_PSP
	   _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IH _hoops_IAHP _hoops_GGR _hoops_RH _hoops_ISIS
	_hoops_RPP (_hoops_SCII->_hoops_CSIS->_hoops_HSHR != _hoops_HGPGA->_hoops_SSIS->_hoops_SCII->_hoops_CSIS->_hoops_HSHR)
		_hoops_ASRC _hoops_RCPP;
	_hoops_RPP (_hoops_SCII->_hoops_GGCS->_hoops_HSHR != _hoops_HGPGA->_hoops_SSIS->_hoops_SCII->_hoops_GGCS->_hoops_HSHR)
		_hoops_ASRC _hoops_RCPP;
	*/

	if (!_hoops_CSRGR->_hoops_CIGI->_hoops_IIII)
		_hoops_CSRGR->_hoops_CIGI->_hoops_IIII = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

	if (dc->_hoops_SPA->color != null) {
		if (_hoops_CCAI (dc->_hoops_SPA->color, Color_EDGE) != null)
			_hoops_CSRGR->_hoops_CIGI->_hoops_GGHRC |= Color_EDGE;
		if (_hoops_CCAI (dc->_hoops_SPA->color, Color_FACE) != null)
			_hoops_CSRGR->_hoops_CIGI->_hoops_GGHRC |= Color_FACE;
	}
	pair = POOL_NEW(dc->memory_pool, _hoops_IPSGC)(nr, p, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color, single);

	_hoops_CSRGR->_hoops_CIGI->_hoops_IIII->AddFirst(pair);
	return true;
}


/* _hoops_SIHR _hoops_CHPI, _hoops_SRII, _hoops_GAII _hoops_PPR _hoops_RRII */
local void draw_3d_ellipse (
		Net_Rendition const &nr,
		Ellipse const *		 ellipse)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	Type type = ellipse->type;
	_hoops_IPSGC *pair;

	if (_hoops_CSRGR->_hoops_ISCI) {
		if (!_hoops_CSRGR->_hoops_CIGI->_hoops_IIII)
			_hoops_CSRGR->_hoops_CIGI->_hoops_IIII = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

		if (dc->_hoops_SPA->color != null) {
			if (_hoops_CCAI (dc->_hoops_SPA->color, Color_EDGE) != null)
				_hoops_CSRGR->_hoops_CIGI->_hoops_GGHRC |= Color_EDGE;
			if (_hoops_CCAI (dc->_hoops_SPA->color, Color_FACE) != null)
				_hoops_CSRGR->_hoops_CIGI->_hoops_GGHRC |= Color_FACE;
		}
		pair = POOL_NEW(dc->memory_pool, _hoops_IPSGC)(nr, ellipse, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color, !_hoops_CSRGR->_hoops_AHPI);

		_hoops_CSRGR->_hoops_CIGI->_hoops_IIII->AddFirst(pair);
		return;
	}

	for (;;) {
		switch (type) {
			case _hoops_CGCP:
			case _hoops_SGCP:
				HD_Std_3D_Ellipse (nr, ellipse);
				break;
			case _hoops_GRCP:
			case _hoops_RRCP:
				HD_Std_3D_Elliptical_Arc (nr, (Elliptical_Arc const *) ellipse);
				break;
		}
		if (!_hoops_CSRGR->_hoops_AHPI)
			break;
		ellipse = (Ellipse const *)ellipse->next;
		if (ellipse == null || ellipse->type != type)
			break;
	}
}

/*
 * _hoops_SRAC
 */
local void
draw_3d_polygon (Net_Rendition const & nr, Polygon const * polygon)
{
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	Line_Rendition const &_hoops_GHP = nr->_hoops_RHP;
	_hoops_HHCR const &_hoops_IHCR = nr->transform_rendition;
	_hoops_SCASP flags = _hoops_IHCR->flags;
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_ACHR _hoops_RGP = nr->_hoops_RGP;
	Point const *points = polygon->points;
	int count = polygon->count;
	Point const *end;
	bool _hoops_RASP = false;
	bool _hoops_IAHC = false;
	Polygon const *p;
	int _hoops_RRIRC = 0;
	bool _hoops_ARIRC = false;
	_hoops_IAPA const	*_hoops_CAPA = null;
	bool antialias = false;
	Point const *pts = points;
	Driver_Color _hoops_CPHHP;
	int weight = _hoops_GHP->weight;

	_hoops_RAPRC("draw_3d_polygon", true);

	if (weight < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP,1.0f, false, 0, true)+0.5f);
	_hoops_IAHC = _hoops_PHII(nr, _hoops_GHP->weight);

	if (_hoops_CSRGR->_hoops_ISCI) {
		if (!_hoops_IAHC && _hoops_HSIS (nr, polygon, !_hoops_CSRGR->_hoops_AHPI))
			return;
		_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_ACIP;
	}

	if (_hoops_IAHC) {
		p = polygon;
		for (;;) {
			HD_Std_3D_Polygon (nr, p);
			if (!_hoops_CSRGR->_hoops_AHPI)
				break;
			p = (Polygon const *)p->next;
			if (p == null || p->type != _hoops_RCIP)
				break;
		}
		return;
	}

	if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = _hoops_IHCR->_hoops_RGH;
		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH)
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
		else
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
	}

	if (nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI &&
		_hoops_SIGA->pattern == FP_USER_DEFINED)
		_hoops_RASP = true;

	_hoops_GGGH(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH && !_hoops_RASP);
	_hoops_IPGP(_hoops_CSRGR, BIT(_hoops_IHCR->flags, _hoops_CASP));
	if (!ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA)) {
		_hoops_RRIRC = _hoops_PRIRC;
		_hoops_HRIRC (_hoops_CSRGR, nr);
	}
	else if (BIT (_hoops_IHCR->heuristics,_hoops_SASA))
		_hoops_ARIRC = true;

	do {
		if (_hoops_CAPA != null) {
			_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
		}

		if (BIT (nr->_hoops_RGP, T_FACES)) {
			p = polygon;
			/* _hoops_IRHH _hoops_RCRR _hoops_ARP _hoops_APIR _hoops_SAGGR _hoops_RHHR */
			_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
			for (;;) {
				_hoops_GPRH(_hoops_GRCS)++;
				count = p->count;
				if (count != 0) {
					points = p->points;
					end = points + count;

					_hoops_PIIGC(_hoops_CSRGR, nr);
					ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));

					if (BIT (flags, _hoops_PRIR) &&
						_hoops_SIGA->_hoops_AGP != null &&
						BIT (_hoops_RGP, T_LIGHTS_FOR_FACES)) {

						/*_hoops_HAIGC _hoops_GCPAR _hoops_IRIRC _hoops_CRIRC*/
 						_hoops_GIGRC (_hoops_CSRGR, nr, 	_hoops_SIGA->_hoops_AGP);

						if (_hoops_CSRGR->_hoops_RPCI != _hoops_SIGA->_hoops_CPA) {
							_hoops_CSRGR->_hoops_RPCI = _hoops_SIGA->_hoops_CPA;
 							OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_CHA, 0, 0);
						}

						ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);

						if (!BIT (p->_hoops_RRHH, _hoops_ARHH))
							HI_Find_Polygon_Plane ((Polygon alter *) p);		/* _hoops_PRGIR _hoops_HIIC */

						if (_hoops_RRIRC == _hoops_PRIRC) {
							if (p->plane.a * _hoops_CSRGR->_hoops_SRIRC[0] +
								p->plane.b * _hoops_CSRGR->_hoops_SRIRC[1] +
								p->plane.c * _hoops_CSRGR->_hoops_SRIRC[2] +
								p->plane.d * _hoops_CSRGR->_hoops_SRIRC[3] > 0.0f)
								glNormal3f(-p->plane.a, -p->plane.b, -p->plane.c);
							else
								glNormal3fv ((GLfloat const *)&(p->plane));
						}
						else if (_hoops_ARIRC) {
							glNormal3f(-p->plane.a, -p->plane.b, -p->plane.c);
						}
						else {
							glNormal3fv ((GLfloat const *)&(p->plane));
						}

					}	/* _hoops_HIGGR _hoops_HAIGC _hoops_GCPAR _hoops_IRIRC _hoops_CRIRC */
					else if (BIT (flags, _hoops_GRHH) && BIT (_hoops_RGP, T_LIGHTS_FOR_FACES)) {
						/*_hoops_HAIGC _hoops_GCPAR _hoops_GAIRC _hoops_IRIRC _hoops_CRIRC*/
						_hoops_SCIGC (_hoops_CSRGR);

						if (!BIT (p->_hoops_RRHH, _hoops_ARHH))
							HI_Find_Polygon_Plane ((Polygon alter *) p);		/* _hoops_PRGIR _hoops_HIIC */

						if (!BIT (p->_hoops_RRHH, _hoops_IASGP))
							FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->color, false);
						else {
							RGBA result;

							HD_Figure_Light (nr, (Geometry const *) p, &result);
							*(RGBAS32 alter *) &_hoops_CPHHP = result;
							FORCE_COLOR (_hoops_CSRGR, &_hoops_CPHHP, false);
						}
					}	/*_hoops_HIGGR _hoops_HAIGC _hoops_GCPAR _hoops_GAIRC _hoops_IRIRC _hoops_CRIRC*/
					else {
						/* _hoops_HAIGC _hoops_GRAPR _hoops_CRIRC*/

						_hoops_RSAI(&_hoops_SIGA->color, Driver_Color, &_hoops_CPHHP);
						_hoops_CPHHP._hoops_HRIR.a = (unsigned char)(_hoops_SIGA->_hoops_CHA->_hoops_IRIR * (255.99));

						_hoops_SCIGC (_hoops_CSRGR);
						_hoops_APIGC (_hoops_CSRGR, &_hoops_CPHHP, nr);

					}	/* _hoops_HIGGR _hoops_CRIRC */

					if (_hoops_RASP) {
						int						s[32];
						int						i, j;
						unsigned char const *p = _hoops_SIGA->_hoops_PGPH->pattern;

						for (i=0; i<8; i++) {
							s[i] = 0;
							for (j=0; j<8; j++) {
								if (!(*p++))
									s[i] |= 1<<j;
							}

							s[i] |= s[i] <<	 8;
							s[i] |= s[i] << 16;
						}
						for (i=8; i<32; i++)
							s[i] = s[i%8];

						glEnable (GL_POLYGON_STIPPLE);
						glPolygonStipple ((GLubyte const *)s);
					}

					if (BIT (_hoops_IHCR->heuristics, _hoops_CGCS)) {
						struct concave_tri		_hoops_SIPH;

						/* _hoops_RAIRC: _hoops_PAH _hoops_RGR _hoops_SGIPR _hoops_IHPS? */
						_hoops_SIPH.points._hoops_GSPH = points;
						_hoops_SIPH._hoops_RPPH = false;
						_hoops_SIPH._hoops_CAIGC = false;
						_hoops_SIPH._hoops_CSRGR = _hoops_CSRGR;
						_hoops_SIPH._hoops_PSPH = _hoops_SAIGC;
						draw_concave_face (nr, count, (struct concave_tri const *)&_hoops_SIPH);

						if (!_hoops_RASP && _hoops_SIGA->pattern != FP_SOLID) {
							_hoops_SCIGC (_hoops_CSRGR);
							glEnable (GL_POLYGON_STIPPLE);
							FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->contrast_color, false);
							_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
							ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
							draw_concave_face (nr, count, (struct concave_tri const *)&_hoops_SIPH);
							glDisable (GL_POLYGON_STIPPLE);
						}
					}
					else {
						pts = points;
						glBegin (GL_POLYGON);
						do {
							glVertex3fv ((GLfloat const *) pts);
						} _hoops_RGGA (++pts == end);
						glEnd ();
						if (!_hoops_RASP && _hoops_SIGA->pattern != FP_SOLID) {
							pts = points;

							_hoops_SCIGC (_hoops_CSRGR);
							glEnable (GL_POLYGON_STIPPLE);
							FORCE_COLOR (_hoops_CSRGR, &_hoops_SIGA->contrast_color, false);
							_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
							ENSURE_FACE_PATTERN (_hoops_CSRGR, _hoops_SIGA->pattern);
							glBegin (GL_POLYGON);
							do {
								glVertex3fv ((GLfloat const *) pts);
							} _hoops_RGGA (++pts == end);
							glEnd ();
							glDisable (GL_POLYGON_STIPPLE);
						}
					}
				}
				if (_hoops_RASP)
					glDisable (GL_POLYGON_STIPPLE);
				if (!_hoops_CSRGR->_hoops_AHPI)
					break;
				p = (Polygon const *)p->next;
				if (p == null || p->type != _hoops_RCIP)
					break;
			}
			_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
		}			/* _hoops_HIGGR !_hoops_RHPPI */

		if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE)) {
			p = polygon;
			for (;;) {
				_hoops_GPRH(_hoops_GRCS)++;
				count = p->count;
				if (count != 0) {
					pts = points = p->points;
					end = points + count;

					/*
					 * _hoops_PAGA: _hoops_PS _hoops_RRP _hoops_IS _hoops_ISPR _hoops_RIPS _hoops_PPR _hoops_ISSC _hoops_HSP _hoops_IAPRR _hoops_ARI _hoops_PGGA _hoops_AAIRC _hoops_AA
					 * _hoops_HAR _hoops_AA _hoops_SCH _hoops_APCS, _hoops_HIS _hoops_IH _hoops_HA _hoops_SGH _hoops_AAPI _hoops_GGR _hoops_PAIRC _hoops_CCH _hoops_IH _hoops_RH
					 * _hoops_HHGPA..._hoops_RGR _hoops_GHCA _hoops_SHH _hoops_GCASI..._hoops_PPR _hoops_HA _hoops_RGR _hoops_AGSR _hoops_SGS _hoops_ISSC _hoops_CPGCA _hoops_SPPR _hoops_CHR
					 * _hoops_GACC _hoops_RHGCP..._hoops_HAIRC _hoops_IS _hoops_RRGSI _hoops_IS _hoops_CACH _hoops_RPP _hoops_RGR _hoops_HRGR _hoops_PCPA _hoops_AGAH _hoops_GSSS.
					 * _hoops_IIIGC _hoops_SSCP _hoops_RGR _hoops_ARPC _hoops_GACC, _hoops_HAIRC _hoops_IS _hoops_AACGC.	_hoops_RAH _hoops_RH _hoops_APSP _hoops_GHC _hoops_HAISR _hoops_IH _hoops_RPHGC.
					 * _hoops_CPIP _hoops_HIGR _hoops_RH _hoops_HSSP _hoops_HRII _hoops_HSAR _hoops_SIACP _hoops_RH _hoops_RSSA _hoops_RRPC?
					 */

					antialias = BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)&&
						weight==1&&BIT(dc->_hoops_PGCC.flags, _hoops_SPPGH);

					_hoops_SCIGC (_hoops_CSRGR);
					_hoops_AIIGC(_hoops_CSRGR, nr);
					ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
					ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH||antialias);
					_hoops_IPGP(_hoops_CSRGR, BIT(_hoops_IHCR->flags, _hoops_CASP));
					OGL_SET_LINE_RENDITION (_hoops_CSRGR, nr, _hoops_GHP);
					ENSURE_LINE_SMOOTH(_hoops_CSRGR, antialias);

					_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;

#define _hoops_IAIRC
#ifdef _hoops_IAIRC
					glBegin (GL_LINE_LOOP);
					do {
						glVertex3fv ((GLfloat const *) pts);
					} _hoops_RGGA (++pts == end);
					glEnd ();
#else
					/* _hoops_GHSGR _hoops_SGS _hoops_SPPR _hoops_CHR _hoops_CHCC */
					glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
					glBegin (GL_POLYGON);
					do {
						if (matrix)
							_hoops_CAIRC (matrix, pts[0]);
						else
							glVertex3fv ((GLfloat const *) pts);
					} _hoops_RGGA (++pts == end);
					glEnd ();
					glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
#endif
				}
				if (!_hoops_CSRGR->_hoops_AHPI)
					break;
				p = (Polygon const *)p->next;
				if (p == null || p->type != _hoops_RCIP)
					break;
			}
		}

		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);

} /* _hoops_RSGR _hoops_API _hoops_PSIS */


/*
 * _hoops_SRAC
 */
local void
draw_3d_nurbs_curve (Net_Rendition const & nr,
					 _hoops_PIRGR const * curve) {

	Display_Context const *		dc = nr->_hoops_SRA;
	int i;
	int knot_count;
	float *knots;
	Point *points, *end;
	Line_Rendition const &_hoops_HC = nr->_hoops_AHP;
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	int weight = _hoops_HC->weight;
	_hoops_IAPA const *_hoops_CAPA = null;
	bool antialias = false;
	bool _hoops_HAPRC = false;
	bool _hoops_IAHC = false;

	_hoops_RAPRC("draw_3d_nurbs_curve", true);

	if (curve->control_point_count == 0)
		return;

	if (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC)
			_hoops_IAHC = true;
		/* _hoops_PSP _hoops_SHRII _hoops_CASH _hoops_ASIPR */
		else if (curve->degree > 6)
			_hoops_IAHC = true;
		/* _hoops_PSP _hoops_IIPGR */
		if (BIT (nr->transform_rendition->heuristics, _hoops_HRIRP))
			_hoops_IAHC = true;
		/* _hoops_PSP _hoops_SAPPA */
		else if ((curve->start_u > 0) || (curve->end_u < 1))
			_hoops_IAHC = true;
		else {
			if (weight < 0)
				weight = (int)(HD_Compute_Generic_Size (nr, _hoops_HC->_hoops_PHP, _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
			if (BIT(_hoops_HC->flags, _hoops_SRPI) ||
				_hoops_GAPI (_hoops_CSRGR, _hoops_HC, weight) ||
				BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP))
				_hoops_IAHC = true;
		}

		if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
			_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;

			if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
				if (_hoops_GGH->_hoops_IRH == null)
					HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
				_hoops_CAPA = _hoops_GGH->_hoops_IRH;
				if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
					_hoops_IAHC = true;
			}
			else {
				_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
				if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
					_hoops_IAHC = true;
			}
		}
		antialias = BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) &&
						weight==1&&BIT(dc->_hoops_PGCC.flags, _hoops_SPPGH);
		_hoops_HAPRC = (!BIT (nr->transform_rendition->flags, _hoops_CSP) ||
						  !XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_CUT_POINTS));

	}


	for (;;) {

		if (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {

			if (!BIT (curve->_hoops_RRHH, _hoops_CHIAA) &&
				!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {

				// _hoops_PASC _hoops_RGR _hoops_IRHS _hoops_IS _hoops_SHH _hoops_SAIRC _hoops_IS _hoops_GPIRC
				Bounding				bounding = Bounding::Create(curve->control_point_count, curve->control_points);
				
				Int_Rectangle const &	_hoops_RPIRC = nr->transform_rendition->_hoops_AGAA;
				
				// _hoops_CGH _hoops_SHH _hoops_ISHA _hoops_SGCR?
				float					_hoops_HHCAP = 1;

				_hoops_PACIR		_hoops_APIRC = _hoops_RPIRC;
				_hoops_APIRC._hoops_IACHA(_hoops_HHCAP);

				Test result = HD_Transform_And_Test_Bounding (nr, &bounding, &_hoops_APIRC, &nr->transform_rendition->_hoops_AGAA, 0);
				
				if (result == Test_DISJOINT)
					goto _hoops_PPIRC;
			}

			if (_hoops_IAHC) {
				HD_Std_3D_NURBS_Curve (nr, curve);
				goto _hoops_PPIRC;
			}

		/* _hoops_SS _hoops_CHR _hoops_SHR _hoops_PSAP _hoops_IH 3d _hoops_GRRC _hoops_PPR _hoops_PGRC */
		_hoops_SCIGC (_hoops_CSRGR);

		_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
		_hoops_GGGH(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		_hoops_AIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
		ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH||antialias);
			_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));
		OGL_SET_LINE_RENDITION (_hoops_CSRGR, nr, _hoops_HC);
		ENSURE_LINE_SMOOTH(_hoops_CSRGR, antialias);
	}

	if (!nr->_hoops_ARA->_hoops_APPI._hoops_SAR) {
		/* _hoops_GRAS _hoops_SCH (_hoops_RPP _hoops_HAHH) */
		if (curve->polyline.points == null) {
			Polyline polyline;
			HI_Generate_NURBS_Polyline (
				curve,
				&nr->_hoops_ARA->_hoops_APPI,
				&nr->transform_rendition->matrix->data,
				&polyline,
				0
			);
			if (polyline.points == null)
					goto _hoops_PPIRC;


			_hoops_PIRGR alter *_hoops_IPPSI = (_hoops_PIRGR alter *)curve;
			_hoops_IPPSI->polyline.points = polyline.points;
			_hoops_IPPSI->polyline.allocated = polyline.allocated;
			_hoops_IPPSI->polyline.count = polyline.count;
		}
		/* _hoops_PGSA _hoops_SCH */
		do {
			if (_hoops_CAPA != null) {
				_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			}

			points = curve->polyline.points;
			end = curve->polyline.points + curve->polyline.count;

			_hoops_GPRH(_hoops_ICCA) += curve->polyline.count;

			glBegin (GL_LINE_STRIP);
			do {
				glVertex3fv ((GLfloat const *) points);
			} _hoops_RGGA (++points == end);
			glEnd ();
			--points;
			if (_hoops_HAPRC) {
				glBegin (GL_POINTS);
					glVertex3fv ((GLfloat *) points);
				glEnd ();
			}

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}
	else {
		Point _hoops_HPIRC(0,0,0);
#define _hoops_IPIRC
#ifdef _hoops_IPIRC
		float matrix[16];

		_hoops_HPIRC = curve->control_points[0];

		matrix[0]  = 1.0f;
		matrix[1]  = 0.0f;
		matrix[2]  = 0.0f;
		matrix[3]  = 0.0f;
		matrix[4]  = 0.0f;
		matrix[5]  = 1.0f;
		matrix[6]  = 0.0f;
		matrix[7]  = 0.0f;
		matrix[8]  = 0.0f;
		matrix[9]  = 0.0f;
		matrix[10] = 1.0f;
		matrix[11] = 0.0f;
		matrix[12] = _hoops_HPIRC.x;
		matrix[13] = _hoops_HPIRC.y;
		matrix[14] = _hoops_HPIRC.z;
		matrix[15] = 1.0f;

		glPushMatrix();
		glMultMatrixf (matrix);
#endif

		knot_count = curve->control_point_count + curve->degree + 1;
		if (curve->knots == null) {
			/* _hoops_CCPP _hoops_GHRHR _hoops_SGHSA */
			ALLOC_ARRAY (knots, knot_count, float);
			for (i = 0; i < knot_count; i++)
				knots[i] = (float) i;
		}
		else
			knots = curve->knots;

		if (curve->weights == null) {

			float *_hoops_CPIRC = &curve->control_points[0].x;
#ifdef _hoops_IPIRC
			ALLOC_ARRAY (_hoops_CPIRC, curve->control_point_count * 3, float);
			for (i = 0; i < curve->control_point_count; i++) {
				_hoops_CPIRC[i * 3 + 0] = (curve->control_points[i].x - _hoops_HPIRC.x);
				_hoops_CPIRC[i * 3 + 1] = (curve->control_points[i].y - _hoops_HPIRC.y);
				_hoops_CPIRC[i * 3 + 2] = (curve->control_points[i].z - _hoops_HPIRC.z);
			}
#endif

			do {
				if (_hoops_CAPA != null) {
					_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				}

				_hoops_GPRH(_hoops_HHRGH)++;

				gluBeginCurve (_hoops_CSRGR->_hoops_SCPIR);
				gluNurbsCurve (_hoops_CSRGR->_hoops_SCPIR,
							   knot_count,
							   knots,
							   3,
							   (GLfloat *) _hoops_CPIRC,
							   curve->degree + 1, GL_MAP1_VERTEX_3);
				gluEndCurve (_hoops_CSRGR->_hoops_SCPIR);

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);

#ifdef _hoops_IPIRC
			FREE_ARRAY	(_hoops_CPIRC, curve->control_point_count * 3, float);
#endif
		}
		else {
			float *_hoops_CPIRC;

			ALLOC_ARRAY (_hoops_CPIRC, curve->control_point_count * 4, float);
			for (i = 0; i < curve->control_point_count; i++) {
				_hoops_CPIRC[i * 4 + 0] = (curve->control_points[i].x - _hoops_HPIRC.x) * curve->weights[i];
				_hoops_CPIRC[i * 4 + 1] = (curve->control_points[i].y - _hoops_HPIRC.y) * curve->weights[i];
				_hoops_CPIRC[i * 4 + 2] = (curve->control_points[i].z - _hoops_HPIRC.z) * curve->weights[i];
				_hoops_CPIRC[i * 4 + 3] = curve->weights[i];
			}

			do {
				if (_hoops_CAPA != null) {
					_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				}

				_hoops_GPRH(_hoops_HHRGH)++;

				gluBeginCurve (_hoops_CSRGR->_hoops_SCPIR);
				gluNurbsCurve (_hoops_CSRGR->_hoops_SCPIR,
							   knot_count,
							   knots,
							   4,
							   _hoops_CPIRC,
							   curve->degree + 1, GL_MAP1_VERTEX_4);
				gluEndCurve (_hoops_CSRGR->_hoops_SCPIR);

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);
			FREE_ARRAY	(_hoops_CPIRC, curve->control_point_count * 4, float);
		}
		gluEndCurve (_hoops_CSRGR->_hoops_SCPIR);

#ifdef _hoops_IPIRC
		glPopMatrix();
#endif

		if (curve->knots == null)
			FREE_ARRAY (knots, knot_count, float);
	}
_hoops_PPIRC:
		if (!_hoops_CSRGR->_hoops_AHPI)
			break;
		curve = (_hoops_PIRGR const *)curve->next;
		if (!curve || curve->type != _hoops_CHIP)
			break;
	}

} /* _hoops_RSGR _hoops_API _hoops_PAAAH */



/*
 * _hoops_SRAC
 * _hoops_RGR _hoops_API _hoops_SAHR _hoops_SPIRC _hoops_GHIRC _hoops_HAHAR _hoops_SGS _hoops_HS _hoops_SAHR 2 _hoops_RSSA _hoops_GGR _hoops_CAPR,
 * _hoops_HIH _hoops_IAII _hoops_HHHH _hoops_CAPR _hoops_GPP _hoops_IS _hoops_RH _hoops_HPRGR _hoops_PCPH */
local void
draw_3d_polycylinder (
	Net_Rendition const &		inr,
	PolyCylinder const *		_hoops_HSPIR) {
	Net_Rendition				nr = inr;
	_hoops_HHCR			_hoops_AHICP;
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Line_Rendition const &		_hoops_GHP = nr->_hoops_RHP;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	int _hoops_RGP = nr->_hoops_RGP;
	int _hoops_CSA = _hoops_RRGH->_hoops_CSA;
	float matrix[16];
	int _hoops_HCGIR;
	Point const *p1, *p2;
	int first, _hoops_IAGRA;
	float _hoops_HIHHA, _hoops_PIAIA;
	_hoops_SSPIR const *_hoops_CSPIR;
	_hoops_IAPA const *_hoops_CAPA = null;
	bool _hoops_IAHC = false;
	bool	_hoops_HHAHR;
	int weight = 0;

	_hoops_RAPRC("draw_3d_polycylinder", true);

	if (_hoops_CSRGR->_hoops_ISCI > 0)
		_hoops_IAHC = true;

	if (_hoops_HSPIR->point_count != 2 ||
	    _hoops_HSPIR->_hoops_RGHIR != null) {
		_hoops_IAHC = true;
	}

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
		_hoops_IAHC = true;
	}

	if (nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR) {
		_hoops_IAHC = true;
	}

	if (_hoops_SIGA->pattern != FP_SOLID ||
		nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI &&
		_hoops_SIGA->_hoops_CHA->_hoops_IRIR < 1.0f) {
		_hoops_IAHC = true;
	}

	if (ANYBIT(_hoops_RGP,T_ANY_EDGE)) {
		weight = _hoops_GHP->weight;
		if (weight < 0)
			weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
		if (_hoops_GAPI(_hoops_CSRGR,_hoops_GHP,weight) ||
			BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
			_hoops_IAHC = true;
		}
	}

	if (ALLBITS(_hoops_RGP, T_LIGHTS_FOR_FACES | T_FACES) &&
		BIT (_hoops_RRGH->_hoops_CSA, _hoops_SSA &&
		!_hoops_CSRGR->_hoops_IARGC)) {
		_hoops_IAHC = true;
	}

	if (!_hoops_IAHC &&
		BIT (_hoops_IHCR->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = _hoops_IHCR->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
	}

	if (_hoops_IAHC) {
		/* _hoops_PSP _hoops_RHIRC _hoops_ARI.  _hoops_PS'_hoops_GCPP _hoops_HGGC _hoops_SHH _hoops_GGR 3d _hoops_CGPR _hoops_SCH _hoops_IISA _hoops_ISSC _hoops_ISHP
			_hoops_GAR _hoops_CCGI _hoops_PPR _hoops_AHHA */
		HD_Std_3D_PolyCylinder(nr, _hoops_HSPIR);
		return;
	}

	if (_hoops_RRA->_hoops_PRSI.options & _hoops_HRSI) {
		if (_hoops_RRA->_hoops_PRSI._hoops_IISRP >= 0)
			_hoops_HCGIR = _hoops_RRA->_hoops_GAICA.cylinder[_hoops_RRA->_hoops_PRSI._hoops_IISRP];
		else
			/* _hoops_AHPPR _hoops_GHSHA _hoops_IIGR _hoops_PRCCA _hoops_HARH _hoops_IPIH _hoops_AHIRC _hoops_GAR _hoops_PRCCA == _hoops_PSAP
			 * _hoops_IH _hoops_GCPA.  _hoops_RHRPA _hoops_CHGC, _hoops_SGS _hoops_HRGR, _hoops_CCGR _hoops_SR _hoops_RCPS _hoops_GH _hoops_CCA _hoops_IRS
			 * _hoops_IRGIR _hoops_RIIRA.  (_hoops_CISRP < 0) _hoops_AGSR _hoops_PHIRC _hoops_GRGR. */
			_hoops_HCGIR = _hoops_RRA->_hoops_GAICA.cylinder[0];
	}
	else {
		_hoops_HCGIR = _hoops_RRA->_hoops_GAICA.cylinder[0];
	}


   if (_hoops_HCGIR <= 0) {
		if (_hoops_HCGIR < 0)
			return;

		_hoops_RGP &= T_GENERIC_EDGES|T_INTERIOR_SILHOUETTE_EDGES|T_PERIMETER_EDGES|_hoops_CRHGP|_hoops_GCSI|T_FACES;
		if (_hoops_RGP) {
			_hoops_GGGH(_hoops_CSRGR, nr);
			_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
			if (BIT (_hoops_RGP, T_FACES)) {
				if (_hoops_SIGA->_hoops_CHA->_hoops_IRIR != 1.0f) {
					_hoops_SCIGC (_hoops_CSRGR);
					OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_CHA, 0, 0);
				}
				else {
					_hoops_SCIGC (_hoops_CSRGR);
					_hoops_APIGC (_hoops_CSRGR, &_hoops_SIGA->color, nr);
				}
			}
			else {
				if (_hoops_GHP->_hoops_CHA->_hoops_IRIR != 1.0f) {
					_hoops_SCIGC (_hoops_CSRGR);
					OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
				}
				else {
					_hoops_SCIGC (_hoops_CSRGR);
					_hoops_APIGC (_hoops_CSRGR, &_hoops_GHP->color, nr);
				}
				ENSURE_LINE_PATTERN (_hoops_CSRGR, _hoops_GHP->line_style);
				if ((weight = _hoops_GHP->weight) < 0)
					weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
			}
			if (weight == 0)
				weight = 1;
			ENSURE_LINE_WEIGHT (_hoops_CSRGR, weight);
			do {
				if (_hoops_CAPA != null) {
					_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				}

				glBegin (GL_LINES);
					glVertex3fv ((const float *)&_hoops_HSPIR->points[0]);
					glVertex3fv ((const float *)&_hoops_HSPIR->points[1]);
				glEnd();

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);
		}
		return;
	}

	if ((_hoops_RGP & (T_GENERIC_EDGES|T_INTERIOR_SILHOUETTE_EDGES)) ==
				T_INTERIOR_SILHOUETTE_EDGES) {
		HD_Std_3D_PolyCylinder (nr, _hoops_HSPIR);
		return;
	}

	/* _hoops_ASAI _hoops_ICIC _hoops_IS _hoops_ASRC _hoops_GRHCP _hoops_RGR _hoops_PPSR (_hoops_SGH "_hoops_HHIIA _hoops_GGAS" _hoops_RIIA) */

	_hoops_HHAHR = BIT (nr->_hoops_ARA->geometry_options, _hoops_RHGAP);
	p1 = &_hoops_HSPIR->points[0];
	p2 = &_hoops_HSPIR->points[1];
	_hoops_CSPIR = &_hoops_HSPIR->_hoops_CSPIR[0];
	if (_hoops_HSPIR->_hoops_ISPIR == 1)
		_hoops_HIHHA = _hoops_PIAIA = _hoops_HSPIR->radii[0];
	else {
		if (!_hoops_HHAHR) {
			_hoops_HIHHA = _hoops_HSPIR->radii[0];
			_hoops_PIAIA = _hoops_HSPIR->radii[1];
		}
		else {
			_hoops_HIHHA = _hoops_HSPIR->radii[1];
			_hoops_PIAIA = _hoops_HSPIR->radii[0];
		}
	}
	if (!_hoops_HHAHR) {
		first = _hoops_HSPIR->flags & _hoops_IHHIA;
		_hoops_IAGRA = _hoops_HSPIR->flags & _hoops_SHHIA;
	}
	else {
		first = _hoops_HSPIR->flags & _hoops_SHHIA;
		_hoops_IAGRA = _hoops_HSPIR->flags & _hoops_IHHIA;
	}

	if (BIT(_hoops_IHCR->heuristics, _hoops_SASA)) {
		/* _hoops_GIARC _hoops_RSSP */
		nr.Modify()->transform_rendition.Modify()->heuristics ^= _hoops_RSA;
	}

	/* _hoops_ARPR _hoops_IRS _hoops_RIHCR _hoops_RSGA _hoops_IH _hoops_RH _hoops_HHIRC _hoops_PPR _hoops_PCAS _hoops_SGS _hoops_GRS _hoops_SHH _hoops_IGI _hoops_IH _hoops_GIPR
	 * _hoops_RH _hoops_RSSI _hoops_PPR _hoops_SPPR _hoops_AGIR */
	matrix[0]  = _hoops_CSPIR->axis[0].x;
	matrix[1]  = _hoops_CSPIR->axis[0].y;
	matrix[2]  = _hoops_CSPIR->axis[0].z;
	matrix[3]  = 0.0f;
	matrix[4]  = _hoops_CSPIR->axis[1].x;
	matrix[5]  = _hoops_CSPIR->axis[1].y;
	matrix[6]  = _hoops_CSPIR->axis[1].z;
	matrix[7]  = 0.0f;
	matrix[8]  = p2->x - p1->x;
	matrix[9]  = p2->y - p1->y;
	matrix[10] = p2->z - p1->z;
	matrix[11] = 0.0f;
	matrix[12] = p1->x;
	matrix[13] = p1->y;
	matrix[14] = p1->z;
	matrix[15] = 1.0f;

	if (_hoops_RGP & T_FACES) {
		int _hoops_RASP = 0;

		_hoops_GGGH(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		_hoops_PIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
		if (_hoops_CSA & (_hoops_IIRAP|_hoops_SSA))
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_SMOOTH);
		else
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);

		if (_hoops_CSRGR->_hoops_RPCI != _hoops_SIGA->_hoops_CPA) {
			_hoops_CSRGR->_hoops_RPCI = _hoops_SIGA->_hoops_CPA;

			if (_hoops_SIGA->_hoops_AGP != null &&
				BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES)) {
				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA)) {
					if (!_hoops_HARGC(nr, _hoops_SIGA->_hoops_AGP, _hoops_SIGA->_hoops_CHA)) {
						HD_Std_3D_PolyCylinder(nr, _hoops_HSPIR);
						goto _hoops_HPAGR;
					}
				}
				else
					_hoops_GIGRC (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_AGP);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_CHA, 0, 0);
			}
			else if (_hoops_SIGA->_hoops_CHA->_hoops_IRIR != 1.0f) {
				_hoops_SCIGC (_hoops_CSRGR);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_CHA, 0, 0);
			}
			else {
				if (_hoops_SIGA->color == _hoops_SIGA->_hoops_RGIR) {
					_hoops_SCIGC (_hoops_CSRGR);
					_hoops_APIGC (_hoops_CSRGR, &_hoops_SIGA->color, nr);
				}
				else {
					/* _hoops_PIRGC _hoops_SSCP _hoops_GIAH _hoops_RIPS/_hoops_ISSC _hoops_APIR _hoops_HRPRA, _hoops_HIH _hoops_HAR
					 * _hoops_IH _hoops_PPPSR, _hoops_GAACP _hoops_PSHA */
					HD_Std_3D_PolyCylinder (nr, _hoops_HSPIR);
					goto _hoops_HPAGR;
				}
			}
		}
		if (BIT (_hoops_IHCR->flags, _hoops_PRIR))
			ENSURE_NORMALIZE_ON (_hoops_CSRGR);

		if (nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI &&
			_hoops_SIGA->_hoops_CHA->_hoops_IRIR < 1.0f) {
			unsigned int s[32];
			int i, _hoops_PHPSR;
			const unsigned char *pattern;

			_hoops_RASP = 64 - (int)(_hoops_SIGA->_hoops_CHA->_hoops_IRIR * 64);

			_hoops_PHPSR = (int)(64 - _hoops_RASP);
			pattern = _hoops_HRPH[_hoops_PHPSR];
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x8 _hoops_IS 8x32 */
			for (i = 0; i < 8; i++) {
				s[i] = pattern[i];
				s[i] |= s[i] << 8;
				s[i] |= s[i] << 16;
			}
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x32 _hoops_IS 32x32 */
			_hoops_AIGA(s,  8, unsigned int, s+8);
			_hoops_AIGA(s, 16, unsigned int, s+16);
			glEnable (GL_POLYGON_STIPPLE);
			glPolygonStipple ((GLubyte const *)s);
		}

		do {
			if (_hoops_CAPA != null) {
				_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			}

			_hoops_GPRH(_hoops_HHRGH)++;

			glPushMatrix();
				glMultMatrixf (matrix);
				/* _hoops_RGR _hoops_GPGH'_hoops_RA _hoops_PPGC _hoops_RPHR. _hoops_CGIGR _hoops_SR _hoops_CGH _hoops_SHH _hoops_IHIRC _hoops_RH _hoops_RGSSA _hoops_GPP _hoops_RH _hoops_ISSGR,
					_hoops_HAR _hoops_ISHP _hoops_RH _hoops_IRSS.  _hoops_GHAP _hoops_PAH'_hoops_RA _hoops_AHGS _hoops_IS _hoops_HGCR _hoops_RH _hoops_RCA _hoops_RPHR, _hoops_PHRI, _hoops_HIS _hoops_PGSA _hoops_SCH
					_hoops_ISHP _hoops_RH _hoops_IRGP _hoops_RIIA, _hoops_HIH _hoops_RGAR _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_IIGR _hoops_RH _hoops_PGCR _hoops_PCAS _hoops_GPRI
					_hoops_HIS _hoops_SGS _hoops_SCH _hoops_GRS _hoops_SHH _hoops_PGAIP _hoops_IS _hoops_SHH _hoops_CCSHP. */
				if ((_hoops_HSPIR->flags & (_hoops_IHHIA|_hoops_SHHIA)) &&
					!ANYBIT (_hoops_RGP, T_GENERIC_EDGES|T_INTERIOR_SILHOUETTE_EDGES)) {
					glBegin(GL_LINES);
						glVertex3f(0, 0, 0.01f);
						glVertex3f(0, 0, 0.99f);
					glEnd();
				}
				gluCylinder (_hoops_CSRGR->_hoops_IGSGC, _hoops_HIHHA, _hoops_PIAIA, 1, _hoops_HCGIR, 1);
				if (_hoops_HSPIR->flags & _hoops_PPSSA)
				{
					if (first && _hoops_HIHHA > 1e-10f) {
						glScalef (-1, 1, -1);
							gluDisk (_hoops_CSRGR->_hoops_IGSGC, 0, _hoops_HIHHA, _hoops_HCGIR, 1);
						glScalef (-1, 1, -1);
					}
					if (_hoops_IAGRA && _hoops_PIAIA > 1e-10f) {
						glPopMatrix();
						glPushMatrix();
						glTranslatef (
							p2->x - p1->x,
							p2->y - p1->y,
							p2->z - p1->z);
						glMultMatrixf (matrix);
						gluDisk (_hoops_CSRGR->_hoops_IGSGC, 0, _hoops_PIAIA, _hoops_HCGIR, 1);
					}
				}
			glPopMatrix();

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);

		if (_hoops_RASP)
			glDisable (GL_POLYGON_STIPPLE);
	}
	if (_hoops_RGP & T_ANY_SHELL_EDGE) {
		_hoops_GGGH(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		if (_hoops_CSA & (_hoops_HIRAP|_hoops_GCP))
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_SMOOTH);
		else
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);

		_hoops_AIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
		if (_hoops_CSRGR->_hoops_RPCI != _hoops_GHP->_hoops_CPA) {
			_hoops_CSRGR->_hoops_RPCI = _hoops_GHP->_hoops_CPA;

			if (_hoops_GHP->_hoops_AGP != null
				&& BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES)) {
				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GCP)) {
					if (!_hoops_HARGC(nr, _hoops_GHP->_hoops_AGP, _hoops_GHP->_hoops_CHA)) {
						HD_Std_3D_PolyCylinder(nr, _hoops_HSPIR);
						goto _hoops_HPAGR;
					}
				}
				else
					_hoops_GIGRC (_hoops_CSRGR, nr, _hoops_GHP->_hoops_AGP);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else if (_hoops_GHP->_hoops_CHA->_hoops_IRIR != 1.0f) {
				_hoops_SCIGC (_hoops_CSRGR);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else {
				_hoops_SCIGC (_hoops_CSRGR);
				_hoops_APIGC (_hoops_CSRGR, &_hoops_GHP->color, nr);
			}

			ENSURE_LINE_PATTERN (_hoops_CSRGR, _hoops_GHP->line_style);
			if ((weight = _hoops_GHP->weight) < 0)
				weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
			if (weight == 0)
				weight = 1;
			ENSURE_LINE_WEIGHT (_hoops_CSRGR, weight);
		}
		do {
			if (_hoops_CAPA != null) {
				_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			}

			_hoops_GPRH(_hoops_HHRGH)++;

			glPushMatrix();
				glMultMatrixf (matrix);
				if (_hoops_RGP & T_GENERIC_EDGES) {
					gluCylinder (_hoops_CSRGR->_hoops_CGSGC, _hoops_HIHHA, _hoops_PIAIA, 1, _hoops_HCGIR, 1);
				}
				else {
					gluQuadricDrawStyle (_hoops_CSRGR->_hoops_CGSGC, GLU_SILHOUETTE);
					glScalef (-1, 1, -1);
					gluDisk (_hoops_CSRGR->_hoops_CGSGC, 0, _hoops_HIHHA, _hoops_HCGIR, 1);
					glScalef (-1, 1, -1);
					glPopMatrix();
					glPushMatrix();
					glTranslatef (
						p2->x - p1->x,
						p2->y - p1->y,
						p2->z - p1->z);
					glMultMatrixf (matrix);
					gluDisk (_hoops_CSRGR->_hoops_CGSGC, 0, _hoops_PIAIA, _hoops_HCGIR, 1);
					gluQuadricDrawStyle (_hoops_CSRGR->_hoops_CGSGC, GLU_LINE);
				}
			glPopMatrix();

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}

  _hoops_HPAGR:;
} /* _hoops_CHIRC */


local void draw_3d_cylinder (
	Net_Rendition const &		nr,
	Cylinder const *			cylinder) {
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Line_Rendition const &		_hoops_GHP = nr->_hoops_RHP;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	OGLData alter *				_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	int 						_hoops_RGP = nr->_hoops_RGP;
	int 						_hoops_CSA = _hoops_RRGH->_hoops_CSA;
	float						matrix[16];
	int							_hoops_HCGIR;
	Point const					*p1, *p2;
	int							first, _hoops_IAGRA;
	_hoops_IAPA const	*	_hoops_CAPA = null;
	_hoops_IAPA const	*	_hoops_PIPRC = null;
	int							weight = 0;
	bool						_hoops_IAHC = false;

	_hoops_RAPRC("draw_3d_cylinder", true);

	if (_hoops_CSRGR->_hoops_ISCI > 0)
		_hoops_IAHC = true;
	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
		_hoops_IAHC = true;
	}
	else if (nr->_hoops_IHA->_hoops_CHA->_hoops_ARIR) {
		_hoops_IAHC = true;
	}
	else if (_hoops_SIGA->pattern != FP_SOLID ||
		nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI &&
		_hoops_SIGA->_hoops_CHA->_hoops_IRIR < 1.0f) {
		_hoops_IAHC = true;
	}
	else if (ANYBIT (_hoops_RGP,T_ANY_EDGE)) {
		weight = _hoops_GHP->weight;
		if (weight < 0)
			weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
		if (_hoops_GAPI (_hoops_CSRGR, _hoops_GHP, weight) ||
			BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
			_hoops_IAHC = true;
		}
	}

	if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = _hoops_IHCR->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		_hoops_PIPRC = _hoops_CAPA;
	}
	if (_hoops_IAHC) {
		/* _hoops_PSP _hoops_RHIRC _hoops_ARI.  _hoops_PS'_hoops_GCPP _hoops_HGGC _hoops_SHH _hoops_GGR 3d _hoops_CGPR _hoops_SCH _hoops_IISA _hoops_ISSC _hoops_ISHP
		    _hoops_GAR _hoops_CCGI _hoops_PPR _hoops_AHHA */
		HD_Std_3D_Cylinder(nr, cylinder);
		return;
	}

	if (_hoops_RRA->_hoops_PRSI.options & _hoops_HRSI) {
		if (_hoops_RRA->_hoops_PRSI._hoops_IISRP >= 0)
			_hoops_HCGIR = _hoops_RRA->_hoops_GAICA.cylinder[_hoops_RRA->_hoops_PRSI._hoops_IISRP];
		else
			/* _hoops_AHPPR _hoops_GHSHA _hoops_IIGR _hoops_PRCCA _hoops_HARH _hoops_IPIH _hoops_AHIRC _hoops_GAR _hoops_PRCCA == _hoops_PSAP
			 * _hoops_IH _hoops_GCPA.  _hoops_RHRPA _hoops_CHGC, _hoops_SGS _hoops_HRGR, _hoops_CCGR _hoops_SR _hoops_RCPS _hoops_GH _hoops_CCA _hoops_IRS
			 * _hoops_IRGIR _hoops_RIIRA.  (_hoops_CISRP < 0) _hoops_AGSR _hoops_PHIRC _hoops_GRGR. */
			_hoops_HCGIR = _hoops_RRA->_hoops_GAICA.cylinder[0];
	}
	else {
		_hoops_HCGIR = _hoops_RRA->_hoops_GAICA.cylinder[0];
	}


   if (_hoops_HCGIR <= 0) {
		if (_hoops_HCGIR < 0)
			return;

		_hoops_RGP &= T_GENERIC_EDGES|T_INTERIOR_SILHOUETTE_EDGES|T_PERIMETER_EDGES|_hoops_CRHGP;
		if (_hoops_RGP) {
			_hoops_GGGH(_hoops_CSRGR, nr);
			_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
			if (_hoops_GHP->_hoops_AGP != null
				&& BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES)) {
				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GCP)) {
					if (!_hoops_HARGC(nr, _hoops_GHP->_hoops_AGP, _hoops_GHP->_hoops_CHA)) {
						HD_Std_3D_Cylinder(nr, cylinder);
						return;
					}
				}
				else
					_hoops_GIGRC (_hoops_CSRGR, nr, _hoops_GHP->_hoops_AGP);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else if (_hoops_GHP->_hoops_CHA->_hoops_IRIR != 1.0f) {
				_hoops_SCIGC (_hoops_CSRGR);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else {
				_hoops_SCIGC (_hoops_CSRGR);
				_hoops_APIGC (_hoops_CSRGR, &_hoops_GHP->color, nr);
			}
			ENSURE_LINE_PATTERN (_hoops_CSRGR, _hoops_GHP->line_style);
			if ((weight = _hoops_GHP->weight) < 0)
				weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
			if (weight == 0)
				weight = 1;
			ENSURE_LINE_WEIGHT (_hoops_CSRGR, weight);
			do {
				if (_hoops_CAPA != null) {
					_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				}

				glBegin (GL_LINES);
					glVertex3fv ((const float *)&cylinder->axis[0]);
					glVertex3fv ((const float *)&cylinder->axis[1]);
				glEnd();

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);
		}
		return;
	}

	if ((_hoops_RGP & (T_GENERIC_EDGES|T_INTERIOR_SILHOUETTE_EDGES)) ==
				T_INTERIOR_SILHOUETTE_EDGES) {
		HD_Std_3D_Cylinder (nr, cylinder);
		return;
	}

	/* _hoops_ARPR _hoops_IRS _hoops_RIHCR _hoops_RSGA _hoops_IH _hoops_RH _hoops_HHIRC _hoops_PPR _hoops_PCAS _hoops_SGS _hoops_GRS _hoops_SHH _hoops_IGI _hoops_IH _hoops_GIPR
	 * _hoops_RH _hoops_RSSI _hoops_PPR _hoops_SPPR _hoops_AGIR */
	if (BIT (_hoops_IHCR->heuristics, _hoops_SASA)) {
		p1 = &cylinder->axis[1];
		p2 = &cylinder->axis[0];
		first = cylinder->flags & _hoops_SHHIA;
		_hoops_IAGRA = cylinder->flags & _hoops_IHHIA;
	}
	else {
		p1 = &cylinder->axis[0];
		p2 = &cylinder->axis[1];
		first = cylinder->flags & _hoops_IHHIA;
		_hoops_IAGRA = cylinder->flags & _hoops_SHHIA;
	}
	matrix[0] = cylinder->_hoops_CSPIR.axis[0].x;
	matrix[1] = cylinder->_hoops_CSPIR.axis[0].y;
	matrix[2] = cylinder->_hoops_CSPIR.axis[0].z;
	matrix[3] = 0.0f;
	matrix[4] = cylinder->_hoops_CSPIR.axis[1].x;
	matrix[5] = cylinder->_hoops_CSPIR.axis[1].y;
	matrix[6] = cylinder->_hoops_CSPIR.axis[1].z;
	matrix[7] = 0.0f;
	matrix[8] = p2->x - p1->x;
	matrix[9] = p2->y - p1->y;
	matrix[10] = p2->z - p1->z;
	matrix[11] = 0.0f;
	matrix[12] = p1->x;
	matrix[13] = p1->y;
	matrix[14] = p1->z;
	matrix[15] = 1.0f;

	if (_hoops_RGP & T_FACES) {
		int								_hoops_RASP = 0;

		_hoops_GGGH(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		_hoops_PIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
		if (_hoops_CSA & (_hoops_IIRAP|_hoops_SSA))
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_SMOOTH);
		else
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);

		if (_hoops_CSRGR->_hoops_RPCI != _hoops_SIGA->_hoops_CPA) {
			_hoops_CSRGR->_hoops_RPCI = _hoops_SIGA->_hoops_CPA;

			if (_hoops_SIGA->_hoops_AGP != null &&
				BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES)) {
				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA)) {
					if (!_hoops_HARGC(nr, _hoops_SIGA->_hoops_AGP, _hoops_SIGA->_hoops_CHA)) {
						HD_Std_3D_Cylinder(nr, cylinder);
						return;
					}
				}
				else
					_hoops_GIGRC (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_AGP);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_CHA, 0, 0);
			}
			else if (_hoops_SIGA->_hoops_CHA->_hoops_IRIR != 1.0f) {
				_hoops_SCIGC (_hoops_CSRGR);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_CHA, 0, 0);
			}
			else {
				if (_hoops_SIGA->color == _hoops_SIGA->_hoops_RGIR) {
					_hoops_SCIGC (_hoops_CSRGR);
					_hoops_APIGC (_hoops_CSRGR, &_hoops_SIGA->color, nr);
				}
				else {
					/* _hoops_PIRGC _hoops_SSCP _hoops_GIAH _hoops_RIPS/_hoops_ISSC _hoops_APIR _hoops_HRPRA, _hoops_HIH _hoops_HAR
					 * _hoops_IH _hoops_PPPSR, _hoops_GAACP _hoops_PSHA */
					HD_Std_3D_Cylinder (nr, cylinder);
					return;
				}
			}
		}
		if (BIT (_hoops_IHCR->flags, _hoops_PRIR))
			ENSURE_NORMALIZE_ON (_hoops_CSRGR);

		if (nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI &&
			_hoops_SIGA->_hoops_CHA->_hoops_IRIR < 1.0f) {
			unsigned int s[32];
			int i, _hoops_PHPSR;
			const unsigned char *pattern;

			_hoops_RASP = 64 - (int)(_hoops_SIGA->_hoops_CHA->_hoops_IRIR * 64);

			_hoops_PHPSR = (int)(64 - _hoops_RASP);
			pattern = _hoops_HRPH[_hoops_PHPSR];
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x8 _hoops_IS 8x32 */
			for (i = 0; i < 8; i++) {
				s[i] = pattern[i];
				s[i] |= s[i] << 8;
				s[i] |= s[i] << 16;
			}
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x32 _hoops_IS 32x32 */
			_hoops_AIGA(s,  8, unsigned int, s+8);
			_hoops_AIGA(s, 16, unsigned int, s+16);
			glEnable (GL_POLYGON_STIPPLE);
			glPolygonStipple ((GLubyte const *)s);
		}

		do {
			if (_hoops_CAPA != null) {
				_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			}

			_hoops_GPRH(_hoops_HHRGH)++;

			glPushMatrix();
				glMultMatrixf (matrix);
				gluCylinder (_hoops_CSRGR->_hoops_IGSGC, cylinder->radius, cylinder->radius, 1, _hoops_HCGIR, 1);
				if (cylinder->flags & _hoops_PPSSA)
				{
					if (first) {
						glScalef (-1, 1, -1);
						gluDisk (_hoops_CSRGR->_hoops_IGSGC, 0, cylinder->radius, _hoops_HCGIR, 1);
						glScalef (-1, 1, -1);
					}
					if (_hoops_IAGRA) {
						glPopMatrix();
						glPushMatrix();
						glTranslatef (
							p2->x - p1->x,
							p2->y - p1->y,
							p2->z - p1->z);
						glMultMatrixf (matrix);
						gluDisk (_hoops_CSRGR->_hoops_IGSGC, 0, cylinder->radius, _hoops_HCGIR, 1);
					}
				}
			glPopMatrix();

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);

		if (_hoops_RASP)
			glDisable (GL_POLYGON_STIPPLE);
	}
	if (_hoops_RGP & T_ANY_SHELL_EDGE) {
		_hoops_GGGH(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		if (_hoops_CSA & (_hoops_HIRAP|_hoops_GCP))
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_SMOOTH);
		else
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);

		_hoops_AIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
		if (_hoops_CSRGR->_hoops_RPCI != _hoops_GHP->_hoops_CPA) {
			_hoops_CSRGR->_hoops_RPCI = _hoops_GHP->_hoops_CPA;

			if (_hoops_GHP->_hoops_AGP != null
				&& BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES)) {
				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GCP)) {
					if (!_hoops_HARGC(nr, _hoops_GHP->_hoops_AGP, _hoops_GHP->_hoops_CHA)) {
						HD_Std_3D_Cylinder(nr, cylinder);
						return;
					}
				}
				else
					_hoops_GIGRC (_hoops_CSRGR, nr, _hoops_GHP->_hoops_AGP);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else if (_hoops_GHP->_hoops_CHA->_hoops_IRIR != 1.0f) {
				_hoops_SCIGC (_hoops_CSRGR);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else {
				_hoops_SCIGC (_hoops_CSRGR);
				_hoops_APIGC (_hoops_CSRGR, &_hoops_GHP->color, nr);
			}

			ENSURE_LINE_PATTERN (_hoops_CSRGR, _hoops_GHP->line_style);
			if ((weight = _hoops_GHP->weight) < 0)
				weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
			if (weight == 0)
				weight = 1;
			ENSURE_LINE_WEIGHT (_hoops_CSRGR, weight);
		}

		_hoops_CAPA = _hoops_PIPRC;
		do {
			if (_hoops_CAPA != null) {
				_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			}

			_hoops_GPRH(_hoops_HHRGH)++;

			glPushMatrix();
				glMultMatrixf (matrix);

				if (_hoops_RGP & T_GENERIC_EDGES) {
					gluCylinder (_hoops_CSRGR->_hoops_CGSGC, cylinder->radius, cylinder->radius, 1, _hoops_HCGIR, 1);
				}
				else {
					gluQuadricDrawStyle (_hoops_CSRGR->_hoops_CGSGC, GLU_SILHOUETTE);
					glScalef (-1, 1, -1);
					gluDisk (_hoops_CSRGR->_hoops_CGSGC, 0, cylinder->radius, _hoops_HCGIR, 1);
					glScalef (-1, 1, -1);
					glPopMatrix();
					glPushMatrix();
					glTranslatef (
						p2->x - p1->x,
						p2->y - p1->y,
						p2->z - p1->z);
					glMultMatrixf (matrix);
					gluDisk (_hoops_CSRGR->_hoops_CGSGC, 0, cylinder->radius, _hoops_HCGIR, 1);
					gluQuadricDrawStyle (_hoops_CSRGR->_hoops_CGSGC, GLU_LINE);
				}
			glPopMatrix();

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}
} /* _hoops_SHIRC */


local void draw_3d_sphere (
	Net_Rendition const &		nr,
	Sphere const *				sphere) {
	_hoops_CIGA const &		_hoops_SIGA = nr->_hoops_IHA;
	Line_Rendition const &		_hoops_GHP = nr->_hoops_RHP;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_GRA const &	_hoops_RRA = nr->_hoops_ARA;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	OGLData alter *				_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	int 						_hoops_RGP = nr->_hoops_RGP;
	int 						_hoops_CSA = _hoops_RRGH->_hoops_CSA;
	float						matrix[16];
	int							_hoops_GIIRC, _hoops_RIIRC;
	_hoops_IAPA const *	_hoops_CAPA = null;
	_hoops_IAPA const *	_hoops_PIPRC = null;
	int							weight = 0;
	bool						_hoops_IAHC = false;
	bool						_hoops_AIIRC;

	_hoops_RAPRC("draw_3d_sphere", true);

	if (_hoops_CSRGR->_hoops_ISCI > 0)
		_hoops_IAHC = true;
	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC)
		_hoops_IAHC = true;
	else if (_hoops_SIGA->pattern != FP_SOLID ||
		nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI &&
		_hoops_SIGA->_hoops_CHA->_hoops_IRIR < 1.0f)
		_hoops_IAHC = true;
	else if (ANYBIT (_hoops_RGP, _hoops_SRHGP)) {
		weight = _hoops_GHP->weight;
		if (weight < 0)
			weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
		if (_hoops_GAPI (_hoops_CSRGR, _hoops_GHP,weight) ||
			BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP))
			_hoops_IAHC = true;

	}

	if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = _hoops_IHCR->_hoops_RGH;
		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		_hoops_PIPRC = _hoops_CAPA;
	}
	if (_hoops_IAHC) {
		/* _hoops_PSP _hoops_RHIRC _hoops_ARI.  _hoops_PS'_hoops_GCPP _hoops_HGGC _hoops_SHH _hoops_GGR 3d _hoops_CGPR _hoops_SCH _hoops_IISA _hoops_ISSC _hoops_ISHP
			_hoops_GAR _hoops_CCGI _hoops_PPR _hoops_AHHA */
		HD_Std_3D_Sphere(nr, sphere);
		return;
	}

	if (sphere->data.radius == 0.0f) {
		_hoops_GIIRC = 0;
	}
	else if (_hoops_RRA->_hoops_PRSI.options & _hoops_HRSI) {
		if (_hoops_RRA->_hoops_PRSI._hoops_IISRP >= 0)
			_hoops_GIIRC = _hoops_RRA->_hoops_GAICA.sphere[_hoops_RRA->_hoops_PRSI._hoops_IISRP];
		else
			/* _hoops_AHPPR _hoops_GHSHA _hoops_IIGR _hoops_PRCCA _hoops_HARH _hoops_IPIH _hoops_AHIRC _hoops_GAR _hoops_PRCCA == _hoops_PSAP
			 * _hoops_IH _hoops_CRCIA.	 _hoops_RHRPA _hoops_CHGC, _hoops_SGS _hoops_HRGR, _hoops_CCGR _hoops_SR _hoops_RCPS _hoops_GH _hoops_CCA _hoops_IRS
			 * _hoops_IRGIR _hoops_RIIRA.  (_hoops_CISRP < 0) _hoops_AGSR _hoops_PHIRC _hoops_GRGR. */
			_hoops_GIIRC = _hoops_RRA->_hoops_GAICA.sphere[0];
	}
	else {
		_hoops_GIIRC = _hoops_RRA->_hoops_GAICA.sphere[0];
	}
	_hoops_RIIRC = _hoops_GIIRC/2;

	_hoops_AIIRC = (!BIT (nr->transform_rendition->flags, _hoops_CSP) ||
				  !XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_CUT_POINTS));

	if (_hoops_GIIRC <= 0) {
		if (_hoops_GIIRC < 0)
			return;

		_hoops_RGP &= _hoops_SRHGP;
		if (_hoops_RGP) {
			_hoops_GGGH(_hoops_CSRGR, nr);
			_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
			if (_hoops_GHP->_hoops_AGP != null
				&& BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES)) {
				_hoops_GIGRC (_hoops_CSRGR, nr, _hoops_GHP->_hoops_AGP);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
				if (sphere->_hoops_CSPIR)
					glNormal3fv ((const float *)&sphere->_hoops_CSPIR[1]);
				else
					glNormal3f(0, 1, 0);
			}
			else if (_hoops_GHP->_hoops_CHA->_hoops_IRIR != 1.0f) {
				_hoops_SCIGC (_hoops_CSRGR);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else {
				_hoops_SCIGC (_hoops_CSRGR);
				_hoops_APIGC (_hoops_CSRGR, &_hoops_GHP->color, nr);
			}

			do {
				if (_hoops_CAPA != null) {
					_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				}
				if (_hoops_AIIRC) {
					glBegin (GL_POINTS);
						glVertex3fv ((const float *)&sphere->data.center);
					glEnd();
				}

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);
		}
		return;
	}
	/* _hoops_RPP _hoops_SR _hoops_RRP _hoops_SAHP _hoops_PPR _hoops_SSIA _hoops_SPGA'_hoops_RA _hoops_AIAH _hoops_PIIRC _hoops_RRGI _hoops_RH _hoops_RII _hoops_RGSGR */
	if ((_hoops_RGP & _hoops_SRHGP) == T_INTERIOR_SILHOUETTE_EDGES) {
		HD_Std_3D_Sphere (nr, sphere);
		return;
	}

	if (sphere->_hoops_CSPIR) {
		matrix[0] = sphere->_hoops_CSPIR[0].x;
		matrix[1] = sphere->_hoops_CSPIR[0].y;
		matrix[2] = sphere->_hoops_CSPIR[0].z;
		matrix[4] = sphere->_hoops_CSPIR[2].x;
		matrix[5] = sphere->_hoops_CSPIR[2].y;
		matrix[6] = sphere->_hoops_CSPIR[2].z;
		if (BIT (_hoops_IHCR->heuristics, _hoops_SASA)) {
			matrix[8]  = sphere->_hoops_CSPIR[1].x;
			matrix[9]  = sphere->_hoops_CSPIR[1].y;
			matrix[10] = sphere->_hoops_CSPIR[1].z;
		}
		else {
			matrix[8]  = -sphere->_hoops_CSPIR[1].x;
			matrix[9]  = -sphere->_hoops_CSPIR[1].y;
			matrix[10] = -sphere->_hoops_CSPIR[1].z;
		}
	}
	else {
		matrix[0] = sphere->data.radius;
		matrix[1] = 0.0f;
		matrix[2] = 0.0f;
		matrix[4] = 0.0f;
		matrix[5] = 0.0f;
		matrix[6] = sphere->data.radius;
		matrix[8] = 0.0f;
		if (BIT (_hoops_IHCR->heuristics, _hoops_SASA))
			matrix[9] = sphere->data.radius;
		else
			matrix[9] = -sphere->data.radius;
		matrix[10] = 0.0f;
	}
	matrix[3] = 0.0f;
	matrix[7] = 0.0f;
	matrix[11] = 0.0f;
	matrix[12] = sphere->data.center.x;
	matrix[13] = sphere->data.center.y;
	matrix[14] = sphere->data.center.z;
	matrix[15] = 1.0f;

	if (_hoops_RGP & T_FACES) {
		int								_hoops_RASP = 0;

		_hoops_GGGH(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		_hoops_PIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
		if (_hoops_CSA & (_hoops_IIRAP|_hoops_SSA))
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_SMOOTH);
		else
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);

		if (_hoops_CSRGR->_hoops_RPCI != _hoops_SIGA->_hoops_CPA) {
			_hoops_CSRGR->_hoops_RPCI = _hoops_SIGA->_hoops_CPA;

			if (_hoops_SIGA->_hoops_AGP != null &&
				BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES)) {
				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA)) {
					if (!_hoops_HARGC(nr, _hoops_SIGA->_hoops_AGP, _hoops_SIGA->_hoops_CHA)) {
						HD_Std_3D_Sphere(nr, sphere);
						return;
					}
				}
				else
					_hoops_GIGRC (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_AGP);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_CHA, 0, 0);
			}
			else if (_hoops_SIGA->_hoops_CHA->_hoops_IRIR != 1.0f) {
				_hoops_SCIGC (_hoops_CSRGR);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_SIGA->_hoops_CHA, 0, 0);
			}
			else {
				if (_hoops_SIGA->color == _hoops_SIGA->_hoops_RGIR) {
					_hoops_SCIGC (_hoops_CSRGR);
					_hoops_APIGC (_hoops_CSRGR, &_hoops_SIGA->color, nr);
				}
				else {
					/* _hoops_PIRGC _hoops_SSCP _hoops_GIAH _hoops_RIPS/_hoops_ISSC _hoops_APIR _hoops_HRPRA, _hoops_HIH _hoops_HAR
					 * _hoops_IH _hoops_PPPSR, _hoops_GAACP _hoops_PSHA */
					HD_Std_3D_Sphere (nr, sphere);
					return;
				}
			}
		}
		if (BIT (_hoops_IHCR->flags, _hoops_PRIR))
			ENSURE_NORMALIZE_ON (_hoops_CSRGR);

		if (nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI &&
			_hoops_SIGA->_hoops_CHA->_hoops_IRIR < 1.0f) {
			unsigned int s[32];
			int i, _hoops_PHPSR;
			const unsigned char *pattern;

			_hoops_RASP = 64 - (int)(_hoops_SIGA->_hoops_CHA->_hoops_IRIR * 64);

			_hoops_PHPSR = (int)(64 - _hoops_RASP);
			pattern = _hoops_HRPH[_hoops_PHPSR];
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x8 _hoops_IS 8x32 */
			for (i = 0; i < 8; i++) {
				s[i] = pattern[i];
				s[i] |= s[i] << 8;
				s[i] |= s[i] << 16;
			}
			/* _hoops_IRCH _hoops_HSGP _hoops_HII 8x32 _hoops_IS 32x32 */
			_hoops_AIGA(s,  8, unsigned int, s+8);
			_hoops_AIGA(s, 16, unsigned int, s+16);
			glEnable (GL_POLYGON_STIPPLE);
			glPolygonStipple ((GLubyte const *)s);
		}

		do {
			if (_hoops_CAPA != null) {
				_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			}

			_hoops_GPRH(_hoops_HHRGH)++;

			glPushMatrix();
				glMultMatrixf (matrix);
				gluSphere (_hoops_CSRGR->_hoops_SGSGC, 1, _hoops_GIIRC, _hoops_RIIRC);
			glPopMatrix();

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);

		if (_hoops_RASP)
			glDisable (GL_POLYGON_STIPPLE);
	}

	if (_hoops_RGP & _hoops_SRHGP) {
		_hoops_GGGH(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		if (_hoops_CSA & (_hoops_HIRAP|_hoops_GCP))
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_SMOOTH);
		else
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);

		_hoops_AIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
		if (_hoops_CSRGR->_hoops_RPCI != _hoops_GHP->_hoops_CPA) {
			_hoops_CSRGR->_hoops_RPCI = _hoops_GHP->_hoops_CPA;

			if (_hoops_GHP->_hoops_AGP != null
				&& BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES)) {
				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GCP)) {
					if (!_hoops_HARGC(nr, _hoops_GHP->_hoops_AGP, _hoops_GHP->_hoops_CHA)) {
						HD_Std_3D_Sphere(nr, sphere);
						return;
					}
				}
				else
					_hoops_GIGRC (_hoops_CSRGR, nr, _hoops_GHP->_hoops_AGP);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else if (_hoops_GHP->_hoops_CHA->_hoops_IRIR != 1.0f) {
				_hoops_SCIGC (_hoops_CSRGR);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else {
				_hoops_SCIGC (_hoops_CSRGR);
				_hoops_APIGC (_hoops_CSRGR, &_hoops_GHP->color, nr);
			}

			ENSURE_LINE_PATTERN (_hoops_CSRGR, _hoops_GHP->line_style);
			if ((weight = _hoops_GHP->weight) < 0)
				weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
			if (weight == 0)
				weight = 1;
			ENSURE_LINE_WEIGHT (_hoops_CSRGR, weight);
		}

		_hoops_CAPA = _hoops_PIPRC;
		do {
			if (_hoops_CAPA != null) {
				_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			}

			_hoops_GPRH(_hoops_HHRGH)++;

			glPushMatrix();
				glMultMatrixf (matrix);
				gluSphere (_hoops_CSRGR->_hoops_GRSGC, 1, _hoops_GIIRC, _hoops_RIIRC);
			glPopMatrix();

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);
	}
}

/*
 * _hoops_PGAA
 */
local void
_hoops_CRRI (
		Net_Rendition const & nr,
		Tristrip const * ts,
		OGL_Display_List_Bin *_hoops_RRHA)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	int _hoops_RPRRC;
	bool	_hoops_IAHC = false;
	OGL_Display_List alter *odl=0;
	_hoops_GACR alter *dl=0;
	_hoops_CIGA const &_hoops_SIGA = nr->_hoops_IHA;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	Tristrip alter *_hoops_RPIAR = (Tristrip alter *) ts;
	bool _hoops_RACR = false;
	bool _hoops_HIIRC = false;
	unsigned int _hoops_IIIRC;

	_hoops_RAPRC("draw_indexed_tristrip", true);

	if (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
			_hoops_IAHC = true;
		}
		else if ((BIT (_hoops_IHCR->flags, _hoops_GRHH)
			 && !BIT (_hoops_IHCR->flags, _hoops_PRIR))) {
			/* || _hoops_IRRC (_hoops_SCII->_hoops_CCGIP->_hoops_CIIRC, _hoops_GRIPH)) */
			_hoops_IAHC = true;
		}
		else if ((BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_SSA) && !_hoops_CSRGR->_hoops_IARGC)) {
			_hoops_IAHC = true;
		}
		else if (!_hoops_IAHC) {
			_hoops_IAHC = !OGL_DEFINE_INTERPOLATION_TEXTURE (_hoops_CSRGR, nr);
			_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, 0);
		}

		if (_hoops_SIGA->pattern == FP_USER_DEFINED)
			if (!_hoops_SIGA->_hoops_PGPH || !_hoops_SIGA->_hoops_PGPH->stipple)
				_hoops_IAHC = true;

		if (_hoops_IAHC) {
			_hoops_AARRC (_hoops_CSRGR, 0);
			if (BIT(ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
				/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_AIRI _hoops_HIGR _hoops_RGAR, _hoops_SIHH _hoops_RH _hoops_PPPS _hoops_SIHC _hoops_GGR _hoops_AGR _hoops_IS _hoops_CAH */
				_hoops_GACR alter *_hoops_SIIRC;
				bool _hoops_GCIRC = false;

				ENSURE_LIST_BASE(_hoops_CSRGR, 0);
				_hoops_GCIRC = _hoops_AACR(nr, &_hoops_RPIAR->_hoops_GAHA, &_hoops_SIIRC, &odl, OGL_DL_GEOMETRY);
				HD_Queue_Destroy_List (odl, true);
			}
			else
				HD_Draw_Indexicated_3D_Tristrip (nr, ts);
			goto done;
		}
	}

	if (nr->_hoops_IRR->_hoops_GAHA)
		_hoops_HIIRC = true;

	if (_hoops_RRHA) {
		unsigned int j = 0;
		_hoops_IPSGC *pair = null;
		_hoops_RPRRC = 0;


		_hoops_RRHA->_hoops_CRHA->ResetCursor();
		for (j = 0; j < _hoops_RRHA->_hoops_CRHA->Count(); j++) {
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			_hoops_RPIAR = (Tristrip alter *) pair->geo;

			// _hoops_GPR _hoops_SGS _hoops_RGR _hoops_HRGR _hoops_PCCP _hoops_CGAS _hoops_CRHH
			_hoops_RPIAR->_hoops_SRHA |= (_hoops_GGIA | DL_INDEX_INTERPOLATION);
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
		}
		_hoops_RRRI (_hoops_RRHA->nr, ts, _hoops_RRHA);
	}
	else {
		_hoops_IIIRC = _hoops_RPIAR->_hoops_SRHA;
		_hoops_RPIAR->_hoops_SRHA |= _hoops_GGIA;
		if (nr->_hoops_IRR->_hoops_GAHA) {
			_hoops_RACR = HI_Get_Display_List(nr->_hoops_SRA->_hoops_GHRI, &_hoops_RPIAR->_hoops_GAHA, &dl);
			if (dl->list && !BIT (dl->_hoops_AGRI, DL_INSUFFICIENT_VRAM)) {
				int _hoops_RCIRC = (_hoops_RPIAR->_hoops_SRHA & DL_DO_NOT_RECOMPILE);
				_hoops_RPIAR->_hoops_SRHA |= DL_DO_NOT_RECOMPILE;
				draw_3d_tristrip (nr, ts);
				/* _hoops_PHIH _hoops_RH "_hoops_AA _hoops_HAR _hoops_HRSPR _hoops_IGRH */
				_hoops_RPIAR->_hoops_SRHA =
					(_hoops_RPIAR->_hoops_SRHA & ~DL_DO_NOT_RECOMPILE) | _hoops_RCIRC;
				/* _hoops_PGI _hoops_SR _hoops_PPHRH _hoops_ACIRC _hoops_RH _hoops_HIGR, _hoops_PAR _hoops_SR _hoops_HGGPR _hoops_SCH _hoops_PPR _hoops_GA'_hoops_RA
				 * _hoops_HS _hoops_RAPR _hoops_SIHC _hoops_IS _hoops_HRSPR.  _hoops_CGP _hoops_HAR _hoops_RAPR _hoops_SIHC, _hoops_SR'_hoops_GCPP _hoops_HGCR
				 * _hoops_PIGS _hoops_GICS _hoops_SPHR _hoops_CCA _hoops_HPHR _hoops_PIH. */
				if (dl->list ||
					BIT (_hoops_RPIAR->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
					if (!BIT (_hoops_RPIAR->_hoops_CARI, _hoops_SARI))
						_hoops_RPIAR->_hoops_SRHA = _hoops_IIIRC;
					_hoops_ICGRC (_hoops_CSRGR);
					goto done;
				}
			}
		}

		if (BIT (ts->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
			_hoops_SCARC (nr, ts);
			goto done;
		}

		if (ANYBIT(dc->flags, _hoops_GIHCP|_hoops_GPHHP)) {
			draw_3d_tristrip (nr, ts);
		}
		else {
			_hoops_RPIAR->_hoops_SRHA |= (_hoops_GGIA | DL_INDEX_INTERPOLATION);

			draw_3d_tristrip (nr, ts);
		}
	}
  done:
	_hoops_AARRC (_hoops_CSRGR, 0);

}/* _hoops_RSGR _hoops_API _hoops_PCIRC */

/*
 * _hoops_SRAC
 */
local void
_hoops_ARCI (
		Net_Rendition const & nr,
		Tristrip const * ts)
{
	_hoops_CRRI(nr, ts, null);
}/* _hoops_RSGR _hoops_API _hoops_HGIS */


/*
 * _hoops_PGAA
 */
local void
really_draw_3d_polyedge (
		Net_Rendition const & nr,
		Line_Rendition const & _hoops_GHP,
		Polyedge const * pe,
		OGL_Display_List_Bin *_hoops_RRHA)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	int _hoops_RRIRC = 0;
	int _hoops_HCGS, _hoops_HCIRC;
	int _hoops_SHPC;
	int _hoops_SAHAR;
	int i,j;
	int type = 0;
	_hoops_IAPA const *_hoops_CAPA = null;
	bool _hoops_ICIRC = false;
	bool _hoops_IAHC = false;
	bool antialias = false;
	bool _hoops_HAPRC = true;
	OGL_Display_List alter *odl=0;
	int weight;
	_hoops_GACR alter *dl;
	bool alter _hoops_RACR=false;
	Polyedge alter *_hoops_HPAS = (Polyedge alter *) pe;
	_hoops_HRPA const *matrix = null;
	RGB const *_hoops_GPCP = null;
	Vector _hoops_HIPCP, _hoops_IIPCP;
	bool _hoops_CCIRC = _hoops_CSRGR->_hoops_PRHGC;
	bool _hoops_CRRS;
	float _hoops_IRIR = _hoops_GHP->_hoops_CHA->_hoops_IRIR;

	_hoops_RAPRC("draw_3d_polyedge", true);

	if (_hoops_GHP == nr->_hoops_RHP)
		type = T_EDGES;
	else
		type = T_LINES;

	if (_hoops_RRHA) {
		_hoops_IPSGC *pair;
		OGL_Display_List *odl;
		int _hoops_PRHA = 0;
		GLuint id;
		int _hoops_AICIP;
		Polyedge alter *_hoops_CHPS = null;

		ZALLOC(odl, OGL_Display_List);
		AGLM(odl->_hoops_CSRGR = OGLD(dc));
		odl->_hoops_GHRI = dc->_hoops_GHRI;
		odl->time_stamp = HOOPS_WORLD->_hoops_GPPI;
		odl->type = OGL_DL_GEOMETRY;
		_hoops_RRHA->odl = odl;
		id = glGenLists(1);
		glNewList (id, GL_COMPILE);
		_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = true;

		_hoops_ISGI const *_hoops_CSGI = dc->_hoops_SPA->modelling_matrix;
		_hoops_SSGI const *_hoops_GGRI = dc->_hoops_SPA->color;
		for (;;) {
			pair = _hoops_RRHA->_hoops_CRHA->PeekCursor();
			if (!pair)
				break;
			_hoops_CHPS = (Polyedge *)pair->geo;
			/* _hoops_IGHS _hoops_CAGH _hoops_PAPA _hoops_CGHS, _hoops_HIS _hoops_HRCI _hoops_GII _hoops_CPAP _hoops_CGHS */
			if (_hoops_CHPS->_hoops_GAHA && _hoops_CHPS->_hoops_GAHA->list)
				HD_Queue_Destroy_List ((OGL_Display_List *)_hoops_CHPS->_hoops_GAHA->list, true);
			odl->item.geometry._hoops_IGGI.point_count += _hoops_CHPS->point_count;
			odl->item.geometry._hoops_IGGI._hoops_PHHA += _hoops_CHPS->_hoops_PHHA;
			odl->item.geometry._hoops_IGGI.total += _hoops_CHPS->total;
			odl->_hoops_CARH += _hoops_ARHRC (_hoops_CHPS);
			/* _hoops_SR'_hoops_GHGP _hoops_SHH _hoops_GGR _hoops_SPGC _hoops_RPP _hoops_AHHA _hoops_HS _hoops_PGSGR _hoops_HGSGR
			   _hoops_IH _hoops_APHRC, _hoops_HIH _hoops_SGS _hoops_AGIR _hoops_HRGR _hoops_AGIA
			   _hoops_IS _hoops_SHH _hoops_GIR _hoops_GGR _hoops_RH _hoops_PIS _hoops_SCGI _hoops_SPAAR _hoops_RRGR _hoops_ARRS */
			_hoops_PRHA |= (
					_hoops_CHPS->_hoops_GSHA >= 2 ||
					_hoops_CHPS->_hoops_PCHA ||
					_hoops_CHPS->_hoops_ICHA);
			dc->_hoops_SPA->modelling_matrix = pair->_hoops_CPAI;
			dc->_hoops_SPA->color = pair->color;
			_hoops_AICIP = _hoops_CHPS->_hoops_SRHA;
			if (!BIT (_hoops_RRHA->_hoops_CHGI->item._hoops_ACGI.flags, OGL_DL_BLESSED_GEOMETRY))
				_hoops_CHPS->_hoops_SRHA |= DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS;
			if (_hoops_CHPS->_hoops_GSCP)
				dc->_hoops_RAI = (Geometry const *) _hoops_CHPS->_hoops_GSCP;
			really_draw_3d_polyedge (nr, _hoops_GHP, _hoops_CHPS, null);		//_hoops_GHHA!!
			_hoops_CHPS->_hoops_SRHA = _hoops_AICIP;
			_hoops_RRHA->_hoops_CRHA->AdvanceCursor();
		}
		dc->_hoops_SPA->modelling_matrix = _hoops_CSGI;
		dc->_hoops_SPA->color = _hoops_GGRI;

		_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = false;
		glEndList ();
		HOOPS_WORLD->display_list_vram_usage += odl->_hoops_CARH;
		odl->item.geometry.id = id;
		odl->item.geometry._hoops_SRHA = _hoops_CHPS->_hoops_SRHA;
		odl->item.geometry._hoops_CARI = _hoops_CHPS->_hoops_CARI;
		odl->item.geometry._hoops_IRRI = _hoops_CHPS->_hoops_PPGI.flags;
		if (_hoops_PRHA)
			odl->item.geometry._hoops_SRHA |= DL_FORCE_SMOOTH_SHADE_MODEL;
		return;
	}

	Point const *points = pe->points;
	RGB const *_hoops_ASHA = pe->_hoops_ASHA;
	Vector const *_hoops_RSHA = pe->_hoops_RSHA;
	RGB const *_hoops_PCHA = pe->_hoops_PCHA;
	Vector const *_hoops_ICHA = pe->_hoops_ICHA;
	_hoops_RSSH const *_hoops_CCHA = pe->_hoops_CCHA;
	int *lengths = pe->lengths;
	int *_hoops_AIHA = pe->_hoops_AIHA;
	int *_hoops_SPII = pe->_hoops_SPII;
	int _hoops_PHHA = pe->_hoops_PHHA;

	if ((weight = _hoops_GHP->weight) < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
	if (weight == 0)
		weight = 1;

	if (_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		if (!_hoops_CSRGR->_hoops_CSC._hoops_SCIRC) {
			if (dc->_hoops_SPA->modelling_matrix)
				matrix = &dc->_hoops_SPA->modelling_matrix->matrix;
			if (BIT (nr->_hoops_IRR->locks._hoops_HAA[_hoops_SAA], M_DIFFUSE))
				_hoops_GPCP = null;
			else
				_hoops_GPCP = _hoops_CCAI (dc->_hoops_SPA->color, Color_EDGE);
		}
		_hoops_CCIRC = false;  /* _hoops_SR _hoops_PAH'_hoops_RA _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_GSIRC _hoops_ASSA _hoops_IIGR _hoops_IRS _hoops_GRRI _hoops_PAR _hoops_HCGI */
	}
	else {
		_hoops_IAHC = _hoops_HSRI (nr, _hoops_GHP, pe, weight);
		if (_hoops_IAHC) {
			if (BIT (pe->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
				/* _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_AIRI _hoops_HIGR _hoops_RGAR, _hoops_SIHH _hoops_RH _hoops_PPPS _hoops_SIHC _hoops_GGR _hoops_AGR _hoops_IS _hoops_CAH */
				if (BIT (pe->_hoops_SRHA, DL_LIGHTWEIGHT_DISPLAY_LIST)) {
					/* _hoops_AIRI _hoops_HIGR _hoops_HRGR _hoops_RGAR _hoops_IRS _hoops_HRCGP */
					glDeleteLists (V2I(pe->_hoops_GAHA), 1);
					_hoops_HPAS->_hoops_GAHA = 0;
				}
				else {
					ENSURE_LIST_BASE(_hoops_CSRGR, 0);
					_hoops_RACR = _hoops_AACR(nr, &_hoops_HPAS->_hoops_GAHA, &dl, &odl, OGL_DL_GEOMETRY);
					HD_Queue_Destroy_List (odl, true);
				}
			}
			else {
				if (_hoops_CSRGR->_hoops_ISCI)
					_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_ASRI;
				if (_hoops_GHP->_hoops_CPA != nr->_hoops_RHP->_hoops_CPA) {
					Net_Rendition _hoops_CRAI = nr;
					_hoops_CRAI.Modify();
					_hoops_CRAI->_hoops_RHP = _hoops_GHP;
					HD_Std_3D_Polyedge (_hoops_CRAI, pe);
				}
				else
					HD_Std_3D_Polyedge (nr, pe);
			}
			return;
		}

		if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
			if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH)
				_hoops_CAPA = _hoops_IHCR->_hoops_RGH->_hoops_IRH;
			else
				_hoops_CAPA = _hoops_IHCR->_hoops_RGH->_hoops_PHCA;
		}

		if (_hoops_CSRGR->_hoops_ISCI > 0 && type == T_EDGES) {
			bool _hoops_HIRS = false;

			if (ANYBIT (pe->_hoops_SRHA, DL_DO_NOT_DEFER|DL_SUPPRESS_SEGMENT_DISPLAY_LISTS))
				_hoops_HIRS = true;

			if (!_hoops_HIRS) {
				_hoops_IPSGC *pair;

				_hoops_AIGI *list = null;
				bool _hoops_IIRS = (dc->_hoops_SPA->color &&
					BIT (dc->_hoops_SPA->color->_hoops_GHA, Color_EDGE));

				if (pe->_hoops_AIHA == null)
					return;

				ASSERT (_hoops_GHP == nr->_hoops_RHP); /* _hoops_APGR _hoops_PPR _hoops_PGRC _hoops_HS _hoops_PAII _hoops_HAII _hoops_HGAGA _hoops_AGPGC */

				if (!pe->_hoops_PCHA &&
					!pe->_hoops_ASHA &&
					!_hoops_IIRS &&
					nr->_hoops_RHP->_hoops_CPA != _hoops_CSRGR->_hoops_CIGI->nr->_hoops_RHP->_hoops_CPA) {
					if (BIT (pe->_hoops_CARI, _hoops_RCRI))
						_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_RSRI;
					else
						_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_ASRI;
				}

				if (dc->_hoops_RAI &&
					(dc->_hoops_RAI->type == _hoops_CSIP ||
					dc->_hoops_RAI->type == _hoops_ASIP)) {
						if (!_hoops_CSRGR->_hoops_CIGI->_hoops_CIRI)
							_hoops_CSRGR->_hoops_CIGI->_hoops_CIRI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
						list = _hoops_CSRGR->_hoops_CIGI->_hoops_CIRI;
				}
				else {
					if (BIT (pe->_hoops_CARI, _hoops_RCRI)) {
						if (BIT (_hoops_CSRGR->_hoops_CIGI->_hoops_RRSI, _hoops_RSRI))
							return;  //_hoops_CIRS _hoops_SIRS _hoops_IS _hoops_CRHR _hoops_GCRS _hoops_RCRS _hoops_CPAP
						if (!_hoops_CSRGR->_hoops_CIGI->_hoops_SIRI)
							_hoops_CSRGR->_hoops_CIGI->_hoops_SIRI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
						list = _hoops_CSRGR->_hoops_CIGI->_hoops_SIRI;
					}
					else {
						if (BIT (_hoops_CSRGR->_hoops_CIGI->_hoops_RRSI, _hoops_ASRI))
							return;  //_hoops_CIRS _hoops_SIRS _hoops_IS _hoops_CRHR _hoops_GCRS _hoops_RCRS _hoops_CPAP
						if (!_hoops_CSRGR->_hoops_CIGI->_hoops_IIRI)
							_hoops_CSRGR->_hoops_CIGI->_hoops_IIRI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
						list = _hoops_CSRGR->_hoops_CIGI->_hoops_IIRI;
					}
				}

				if (BIT(pe->_hoops_SRHA, DL_TEMPORARY_DATA))
					HD_Isolate_Polyedge_Data (dc, pe);

				Polyedge alter *_hoops_CHPS = (Polyedge alter *) pe;
				_hoops_CHPS->_hoops_CARI |= _hoops_SARI;

				if (dc->_hoops_SPA->color != null && 
					_hoops_CCAI (dc->_hoops_SPA->color, Color_EDGE))
					_hoops_CSRGR->_hoops_CIGI->_hoops_GGHRC |= Color_EDGE;
				pair = POOL_NEW(dc->memory_pool, _hoops_IPSGC)(nr, pe, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color);

				list->AddFirst(pair);
				return;
			}
			matrix = null;
			_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_ASRI;
		}

		/* _hoops_HHIGR _hoops_HRGR _hoops_HAR _hoops_ICIC _hoops_IS _hoops_CAH _hoops_GRHCP _hoops_RGR _hoops_PPSR */
		_hoops_GGGH(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		_hoops_AIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));

		if ((pe->_hoops_ICHA || pe->_hoops_RSHA) &&
			BIT (_hoops_IHCR->flags, _hoops_GRHH) && 
			BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES)) {
			if (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI) ||
			   !ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA)) {
				_hoops_RRIRC = _hoops_PRIRC;
				_hoops_HRIRC (_hoops_CSRGR, nr);
			}
		}

		antialias = weight == 1 &&
			BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)&&
			BIT(nr->_hoops_SRA->_hoops_PGCC.flags, _hoops_SPPGH);
		_hoops_HAPRC = (!BIT (nr->transform_rendition->flags, _hoops_CSP) ||
						  !XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_CUT_POINTS));

		if (_hoops_CSRGR->_hoops_RPCI != _hoops_GHP->_hoops_CPA) {
			bool _hoops_RSIRC = false;

			_hoops_CSRGR->_hoops_RPCI = _hoops_GHP->_hoops_CPA;
			if (_hoops_GHP->_hoops_AGP != null) {
				if (BIT (pe->_hoops_CARI, _hoops_RCRI)) {
					if (nr->_hoops_ARA->_hoops_ACP._hoops_PCP)
						_hoops_RSIRC = true;
				}
				else if (type == T_EDGES) {
					if (BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES))
						_hoops_RSIRC = true;
				}
			}

			if (_hoops_RSIRC) {
				if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_GCP)) {
				    if (!_hoops_HARGC(nr, _hoops_GHP->_hoops_AGP, _hoops_GHP->_hoops_CHA)) {
						/* _hoops_SCH _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_SSRR _hoops_IS _hoops_HGCR _hoops_ARI -- _hoops_CAH _hoops_HCGC _hoops_CHR _hoops_HPGR _hoops_HSPP _hoops_IIGR _hoops_API */
						HD_Std_3D_Polyedge (nr, pe);
						return;
					}
				}
				else
				    _hoops_GIGRC (_hoops_CSRGR, nr, _hoops_GHP->_hoops_AGP);
				if (BIT (pe->_hoops_SRHA, _hoops_GGIA))
					OGL_SET_TEXTURE_INDEXED_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA);
				else
					OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else if (_hoops_IRIR < 1.0f) {
				_hoops_SCIGC (_hoops_CSRGR);
				if (BIT (pe->_hoops_SRHA, _hoops_GGIA))
					OGL_SET_TEXTURE_INDEXED_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA);
				else
					OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else {
				_hoops_SCIGC (_hoops_CSRGR);
				_hoops_APIGC (_hoops_CSRGR, &_hoops_GHP->color, nr);
			}

			ENSURE_LINE_PATTERN (_hoops_CSRGR, _hoops_GHP->line_style);
			ENSURE_LINE_WEIGHT (_hoops_CSRGR, weight);
		}

		ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH||antialias);
		_hoops_IPGP(_hoops_CSRGR, BIT(_hoops_IHCR->flags, _hoops_CASP));
		ENSURE_LINE_SMOOTH(_hoops_CSRGR, antialias);

#if 0
		if (pe->_hoops_GPPPI) {
			/* _hoops_SR _hoops_PAH _hoops_ARP _hoops_RH _hoops_HAIR _hoops_ARR _hoops_PPR _hoops_PSCR _hoops_HPRAR _hoops_CRGR _hoops_RH _hoops_ARACP _hoops_ARAR */
			if (_hoops_PCHA != null) {
				/* _hoops_SGH _hoops_CIHA _hoops_IIGR _hoops_SRS _hoops_PPSR */
				glColor3fv ((float const *) &_hoops_PCHA[_hoops_AIHA[0]]);
				_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;
				_hoops_PCHA = null;
			}
			else if (_hoops_ASHA != null) {
				/* _hoops_SGH _hoops_CIHA _hoops_IIGR _hoops_SRS _hoops_HSP (_hoops_IHIA _hoops_CCA _hoops_GIAP _hoops_PPSR) */
				glColor3fv ((float const *) &_hoops_ASHA[_hoops_SPII[1]]);
				_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;
				_hoops_ASHA = null;
			}
		}
#endif
		if (_hoops_PCHA || _hoops_ICHA || _hoops_CCHA ||
			ANYBIT (pe->_hoops_SRHA, DL_FORCE_SMOOTH_SHADE_MODEL|_hoops_GGIA))
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_SMOOTH);
		else
			ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);

		if (BIT(pe->_hoops_SRHA, _hoops_GGIA)) {
			_hoops_IAHC = !OGL_DEFINE_INTERPOLATION_TEXTURE (_hoops_CSRGR, nr);
			_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, 0);

			//_hoops_PPIP _hoops_GGAR _hoops_HH _hoops_HCGC _hoops_HSP _hoops_RCA _hoops_HPRC, _hoops_HAR _hoops_ISHA _hoops_RRR _hoops_HPRC, 
			//_hoops_HIS _hoops_SAHR _hoops_GRPHA _hoops_SCH _hoops_ISSC _hoops_RPP _hoops_SSIA _hoops_GA'_hoops_RA _hoops_PSSP
			if (BIT (nr->transform_rendition->flags, _hoops_GRHH) &&
				BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES))
				ENSURE_TEXTURE_ENV_MODE(_hoops_CSRGR, GL_MODULATE, 0);
			else
				ENSURE_TEXTURE_ENV_MODE(_hoops_CSRGR, GL_DECAL, 0);		
		}
	}
	/* _hoops_HHIGR _hoops_HRGR _hoops_HAR _hoops_ICIC _hoops_IS _hoops_CAH _hoops_GRHCP _hoops_RGR _hoops_PPSR */

	if (BIT (pe->_hoops_SRHA, DL_LIGHTWEIGHT_DISPLAY_LIST)) {
		do {
			if (_hoops_CAPA != null) {
				_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			}
			_hoops_GPRH(_hoops_AHRGH) += pe->total - pe->_hoops_PHHA;
			if (!BIT(dc->flags, _hoops_CHSI))
				glCallList (V2I (pe->_hoops_GAHA));	 /* _hoops_AA _hoops_SCH! */

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);

		//_hoops_GGR _hoops_RH _hoops_HSPR _hoops_III, _hoops_ASIRC _hoops_HRGR _hoops_IGI _hoops_IS _hoops_IRHC _hoops_SGS _hoops_SR
		//_hoops_GA'_hoops_RA _hoops_ACPA _hoops_IGH _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_ICGI _hoops_PSHA _hoops_PAR _hoops_HAR
		if (_hoops_PCHA || _hoops_ASHA || BIT (pe->_hoops_SRHA, DL_DO_NOT_RECOMPILE))
			_hoops_ICGRC(_hoops_CSRGR);
		if (BIT(pe->_hoops_SRHA, _hoops_GGIA))
			_hoops_AARRC (_hoops_CSRGR, 0);
		return;
	}

	if (BIT (pe->_hoops_SRHA, DL_DO_NOT_RECOMPILE))
		_hoops_CRRS = true;
	else if (nr->_hoops_IRR->_hoops_GAHA == Display_List_GEOMETRY)
		_hoops_CRRS = !BIT(pe->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS);
	else if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT) {
		if (_hoops_RRHA)
			_hoops_CRRS = !BIT(pe->_hoops_SRHA, DL_SUPPRESS_SEGMENT_DISPLAY_LISTS);
		else
			_hoops_CRRS = !BIT(pe->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS);
	}
	else
		_hoops_CRRS = false;

	if (!_hoops_CSRGR->_hoops_RRSGC ||
		_hoops_RRIRC == _hoops_PRIRC)
		_hoops_CRRS = false;

	bool _hoops_PSIRC = nr->_hoops_IRR->_hoops_GAHA &&
		!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC &&
		_hoops_CSRGR->_hoops_RRSGC &&
		!BIT(pe->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS);
	if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT &&
		!_hoops_RRHA && !pe->_hoops_GAHA && !_hoops_CSRGR->_hoops_GIIGC)
		_hoops_PSIRC = false;
	if (BIT(pe->_hoops_SRHA, DL_DO_NOT_RECOMPILE))
		_hoops_PSIRC = true;

	if (_hoops_CRRS && 
		!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		unsigned int error;

		ENSURE_LIST_BASE(_hoops_CSRGR, 0);

		_hoops_RACR = _hoops_AACR(nr, &_hoops_HPAS->_hoops_GAHA, &dl, &odl, OGL_DL_GEOMETRY);

		if (_hoops_RACR) {
			error = glGetError ();
			/* _hoops_CAHP _hoops_SPR _hoops_PPRAR _hoops_AIRI _hoops_HIGR _hoops_CRSRR */
			odl->item.geometry.id = glGenLists(1);
			odl->_hoops_CARH = _hoops_ARHRC (pe);
			if (HOOPS_WORLD->display_list_vram_usage + odl->_hoops_CARH > HOOPS_WORLD->_hoops_PHARR) {
				dl->_hoops_AGRI |= DL_INSUFFICIENT_VRAM;
				odl->item.geometry.id = _hoops_RSARR; /* _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GRHP _hoops_IRCC */
				odl->_hoops_CARH = 0;
			}
			else
				HOOPS_WORLD->display_list_vram_usage += odl->_hoops_CARH;
		}

		if (!_hoops_CSRGR->_hoops_CSC._hoops_RAIH)
			_hoops_ICIRC = true;
		else if ((dl->_hoops_AGRI & _hoops_ACRC) == (pe->_hoops_SRHA & _hoops_ACRC) &&
				 (dl->_hoops_PRRI & _hoops_AHCGP) == (pe->_hoops_CARI & _hoops_AHCGP))
			_hoops_ICIRC = true;

		if (	(odl->item.geometry._hoops_GSAI != pe->_hoops_GSAI) &&
			(_hoops_GHP == nr->_hoops_RHP) ) {
			_hoops_ICIRC = false;
		}

		/* _hoops_CASRR, _hoops_RPP _hoops_HAHH */
		if (odl->item.geometry.id != _hoops_RSARR &&
			(_hoops_RACR ||
				dl->_hoops_GSAI == DL_FLAG_INVALID ||
				!_hoops_ICIRC)) {

			if (BIT(pe->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
				HD_Queue_Destroy_List (odl, true);
				return;
			}

			/* _hoops_ISIA _hoops_GAR _hoops_IRS _hoops_HSCI _hoops_IS _hoops_IRHH _hoops_HSIRC _hoops_SIGC */
			if (!_hoops_RACR)
				_hoops_RCCA(_hoops_SGAGR)++;

			/* _hoops_CASRR _hoops_RH _hoops_HIGR */
			glNewList (odl->item.geometry.id, GL_COMPILE);
			_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = true;
			_hoops_CSRGR->_hoops_CSC._hoops_SCIRC = true;
			really_draw_3d_polyedge(nr, _hoops_GHP, pe, _hoops_RRHA); /* _hoops_GHHA */
			_hoops_CSRGR->_hoops_CSC._hoops_SCIRC = false;
			_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = false;
			glEndList ();

			if ((error = glGetError ()) != 0) {
				/* _hoops_CIH _hoops_SCH _hoops_PPR _hoops_GRHHR _hoops_IH _hoops_RH _hoops_AAH */
				glDeleteLists (odl->item.geometry.id, 1);
				/* _hoops_PISPR _hoops_IRS _hoops_ISPC _hoops_HIGR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GRHP _hoops_IRCC */
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"OpenGL reported an error during display list compilation in draw_3d_polyedge");
				odl->item.geometry.id = _hoops_RSARR;
			}

			dl->_hoops_GSAI = pe->_hoops_GSAI;
			dl->_hoops_AGRI = pe->_hoops_SRHA;
			odl->item.geometry._hoops_GSAI = pe->_hoops_GSAI;
		}

		/* _hoops_GRCI */
		if (odl->item.geometry.id != _hoops_RSARR) {
			do {
				if (_hoops_CAPA != null) {
					_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				}

				_hoops_GPRH(_hoops_AHRGH) += pe->total - pe->_hoops_PHHA;
				odl->_hoops_GPPI = HOOPS_WORLD->_hoops_GPPI;
				if (!BIT(dc->flags, _hoops_CHSI))
					glCallList (odl->item.geometry.id);	 /* _hoops_AA _hoops_SCH! */

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);

			_hoops_ICGRC(_hoops_CSRGR);
			if (BIT(pe->_hoops_SRHA, _hoops_GGIA))
				_hoops_AARRC (_hoops_CSRGR, 0);
			return;
		}
		else
			/* _hoops_HSSC _hoops_RHIR _hoops_PPR _hoops_PGSA _hoops_CIPH _hoops_RH _hoops_GSSR _hoops_PPRRR */
			odl = null;
	}

	if (BIT(dc->flags, _hoops_CHSI) &&
		!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC)
		goto done;

	if (matrix) {
		_hoops_CCIRC = false;
		if ((_hoops_ICHA || _hoops_RSHA) &&
			matrix->_hoops_APRA == null)
			HI_Validate_Matrix_Adjoint((_hoops_HRPA alter *)matrix);
	}

	if (_hoops_GPCP && !_hoops_PCHA) {
		RGB *ptr, *end;
		ALLOC_ARRAY_CACHED (_hoops_PCHA, pe->point_count, RGB);
		ptr = (RGB *)_hoops_PCHA;
		end = ptr + pe->point_count;
		while (ptr < end) {
			_hoops_RSAI (_hoops_GPCP, RGB, ptr);
			ptr++;
		}
	}

	do {
		_hoops_GPRH(_hoops_ICCA) += pe->total - pe->_hoops_PHHA;
		if (_hoops_CAPA != null) {
			_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
		}

		if (!_hoops_RSHA && !_hoops_ASHA) {
			/* _hoops_PSP _hoops_ISHA _hoops_AIRC */
			int _hoops_ISIRC = _hoops_IICIA;

			/* _hoops_IH _hoops_HA, _hoops_SAHR _hoops_SGH _hoops_RH _hoops_PSHR _hoops_CGGR _hoops_CSIRC _hoops_GAR _hoops_IH _hoops_CCGI.
			 * _hoops_GAAP _hoops_SR'_hoops_GCPP _hoops_GGCR _hoops_PCCP _hoops_SSIRC _hoops_GGCRC _hoops_GCSRP _hoops_IH
			 * _hoops_AHHA _hoops_CPRH... _hoops_PAR _hoops_HAR */
			if (_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
				_hoops_ISIRC = _hoops_CSRGR->_hoops_PRARR->_hoops_SIIPP;
			}
			else {

				if ( BIT(pe->_hoops_SRHA,DL_TEMPORARY_DATA) &&
					XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_DELAYED_VERTEX_ARRAYS) )
					_hoops_CCIRC = false;

				if (_hoops_RRIRC ||
					XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_NONDL_VERTEX_ARRAYS))
					_hoops_CCIRC = false;

				if (_hoops_IRIR < 1.0 && pe->_hoops_PCHA)
					_hoops_CCIRC = false;

				if (pe->_hoops_HCHA)
					_hoops_CCIRC = false;

				_hoops_ISIRC = _hoops_CSRGR->_hoops_PRARR->_hoops_CIIPP;
			}

			if (!_hoops_AIHA)
				_hoops_ISIRC = _hoops_IICIA;

			if (_hoops_CCIRC) {
				int *_hoops_RGCRC, *_hoops_AGCRC;
				int _hoops_PGCRC = 0;

				_hoops_CPPRC(_hoops_CSRGR);
				glVertexPointer(3, GL_FLOAT, 0, points);
				if (_hoops_ICHA) {
					_hoops_HGCRC(_hoops_CSRGR);
					glNormalPointer(GL_FLOAT, 0, _hoops_ICHA);
				}
				if (_hoops_PCHA) {
					ENSURE_COLOR_ARRAY_ON(_hoops_CSRGR);
					glColorPointer(3, GL_FLOAT, 0, _hoops_PCHA);
				}

				if (_hoops_ISIRC < _hoops_IICIA) {
					j=0;
					for (i = 0; i < _hoops_PHHA; i++) {
						ASSERT (lengths[i] > 0);
						if (lengths[i] < _hoops_ISIRC)
							_hoops_PGCRC += lengths[i] - 1;
						else
							glDrawElements(GL_LINE_STRIP, lengths[i], GL_UNSIGNED_INT, &_hoops_AIHA[j]);
						j += lengths[i];
					}
				}
				else
					_hoops_PGCRC = pe->total;
				if (_hoops_PGCRC) {
					if (!_hoops_CSRGR->_hoops_IHSGC)
						ALLOC_ARRAY(_hoops_CSRGR->_hoops_IHSGC, _hoops_CHSGC, int);
					_hoops_RGCRC = _hoops_CSRGR->_hoops_IHSGC;
					_hoops_AGCRC = _hoops_RGCRC;
					j=0;
					for (i = 0; i < _hoops_PHHA; i++) {
						if (lengths[i] < _hoops_ISIRC) {
							_hoops_SAHAR = j+lengths[i];
							j += 1;
							while (j<_hoops_SAHAR) {
								if (_hoops_AGCRC - _hoops_RGCRC + 2 >= _hoops_CHSGC) {
									glDrawElements(GL_LINES, _hoops_AGCRC - _hoops_RGCRC, GL_UNSIGNED_INT, _hoops_RGCRC);
									_hoops_AGCRC = _hoops_RGCRC;
								}
								ASSERT(_hoops_AGCRC-_hoops_RGCRC < _hoops_CHSGC-2);
								if (_hoops_AIHA) {
									*_hoops_AGCRC++ = _hoops_AIHA[j-1];
									*_hoops_AGCRC++ = _hoops_AIHA[j];
								}
								else {
									*_hoops_AGCRC++ = j-1;
									*_hoops_AGCRC++ = j;
								}
								j++;
							}
						}
						else
							j += lengths[i];
					}
					if (_hoops_AGCRC-_hoops_RGCRC > 0)
						glDrawElements(GL_LINES, _hoops_AGCRC - _hoops_RGCRC, GL_UNSIGNED_INT, _hoops_RGCRC);
				}
				_hoops_AHPRC(_hoops_CSRGR);
				_hoops_IGCRC(_hoops_CSRGR);
				_hoops_RHPRC(_hoops_CSRGR);
			}
			else {
				j=0;
				for (i=0; i<_hoops_PHHA; i++) {

					glBegin (GL_LINE_STRIP);
					_hoops_SAHAR = j + lengths[i];

					if (_hoops_PCHA || matrix || _hoops_ICHA || pe->_hoops_HCHA) {

						while (j<_hoops_SAHAR) {
							if (_hoops_AIHA)
								_hoops_HCGS = _hoops_AIHA[j];
							else
								_hoops_HCGS = j;
							if (_hoops_PCHA) {
								RGB const *_hoops_CGCRC = &_hoops_PCHA[_hoops_HCGS];
								glColor4f (_hoops_CGCRC->red, _hoops_CGCRC->green, _hoops_CGCRC->blue, _hoops_IRIR);
							}
							else if (pe->_hoops_HCHA) {
								glTexCoord1f (pe->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
							}
							
							if (matrix) {
								_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HIPCP);
								if (_hoops_ICHA) {
									_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_IIPCP);
									_hoops_RRCRC (_hoops_RRIRC, _hoops_IIPCP, _hoops_HIPCP, _hoops_CSRGR->_hoops_SRIRC);
								}
								glVertex3fv (&_hoops_HIPCP.x);
							}
							else {
								if (_hoops_ICHA)
									_hoops_RRCRC(_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
								glVertex3fv (&points[_hoops_HCGS].x);
							}
							j++;
						}
					}
					else {

						while (j<_hoops_SAHAR) {

							if (_hoops_AIHA)
								_hoops_HCGS = _hoops_AIHA[j];
							else
								_hoops_HCGS = j;

							_hoops_SSAGR(&points[_hoops_HCGS].x);

							glVertex3fv (&points[_hoops_HCGS].x);

							j++;
						}
					}

					glEnd ();
				}
			}
		}
		else {
			/* _hoops_ISHA _hoops_AIRC.
			   _hoops_GIGHR: _hoops_IAAAR _hoops_CAAAR'_hoops_SAAAR/_hoops_ARCRC'_hoops_SAAAR _hoops_GCIGC _hoops_PRCRC _hoops_HAPCA _hoops_HRCRC _hoops_SGAPR _hoops_IRCRC _hoops_PCSPR*/
			glBegin (GL_LINES);
			j=0;
			_hoops_SHPC = -1;
			for (i=0; i<_hoops_PHHA; i++) {
				_hoops_SAHAR = j + lengths[i];
				if (_hoops_AIHA)
					_hoops_HCIRC = _hoops_AIHA[j];
				else
					_hoops_HCIRC = j;
				j++;
				while (j<_hoops_SAHAR) {
					if (_hoops_AIHA)
						_hoops_HCGS = _hoops_AIHA[j];
					else
						_hoops_HCGS = j;
					if (_hoops_SPII)
						_hoops_SHPC = _hoops_SPII[j];
					else
						_hoops_SHPC++;
					if (_hoops_RSHA) {
						if (matrix) {
							_hoops_CRCRC (matrix, _hoops_RSHA[_hoops_SHPC], points[_hoops_HCGS], _hoops_HIPCP);
							_hoops_RRCRC (_hoops_RRIRC, _hoops_HIPCP, points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
						}
						else
							_hoops_RRCRC (_hoops_RRIRC, _hoops_RSHA[_hoops_SHPC], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
					}

					if (_hoops_PCHA)
						glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCIRC]);
					else if (_hoops_ASHA)
						glColor3fv ((float const *) &_hoops_ASHA[_hoops_SHPC]);
					else if (pe->_hoops_HCHA)
						glTexCoord1f (pe->_hoops_HCHA[_hoops_HCIRC] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);

					if (matrix) {
						_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HIPCP);
						if (_hoops_ICHA) {
							_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_IIPCP);
							_hoops_RRCRC (_hoops_RRIRC, _hoops_IIPCP, _hoops_HIPCP, _hoops_CSRGR->_hoops_SRIRC);
						}
						glVertex3fv (&_hoops_HIPCP.x);
					}
					else {
						if (_hoops_ICHA)
							_hoops_RRCRC(_hoops_RRIRC, _hoops_ICHA[_hoops_HCIRC], points[_hoops_HCIRC], _hoops_CSRGR->_hoops_SRIRC);
						glVertex3fv (&points[_hoops_HCIRC].x);
					}

					if (_hoops_PCHA)
						glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
					else if (pe->_hoops_HCHA)
						glTexCoord1f (pe->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);

					//_hoops_PSP _hoops_RRP _hoops_IS _hoops_ARP _hoops_ISHA _hoops_HAIR _hoops_GICS.  _hoops_IGSCP _hoops_CCACR'_hoops_RA _hoops_HGAS
					//_hoops_SHS _hoops_RPP (_hoops_SRCRC)
					//	_hoops_GACRC ((_hoops_AIIC _hoops_RCIC *) &_hoops_SRCRC[_hoops_IGSCP]);
					if (matrix) {
						_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HIPCP);
						if (_hoops_ICHA) {
							_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_IIPCP);
							_hoops_RRCRC (_hoops_RRIRC, _hoops_IIPCP, _hoops_HIPCP, _hoops_CSRGR->_hoops_SRIRC);
						}
						glVertex3fv (&_hoops_HIPCP.x);
					}
					else {
						if (_hoops_ICHA)
							_hoops_RRCRC(_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
						glVertex3fv (&points[_hoops_HCGS].x);
					}
					_hoops_HCIRC = _hoops_HCGS;
					j++;
				}
			}
			glEnd ();
		}
		if (!BIT(pe->_hoops_CARI, _hoops_IPHS))
			_hoops_HAPRC = false;
		if (_hoops_HAPRC) {
			j = 0;
			glBegin (GL_POINTS);
			for (i = 0; i < _hoops_PHHA; i++) {
				_hoops_HCGS = _hoops_AIHA[j + lengths[i] - 1];
				if (_hoops_PCHA)
					glColor3fv ((float const *) &_hoops_PCHA[_hoops_HCGS]);
				else if (pe->_hoops_HCHA)
					glTexCoord1f (pe->_hoops_HCHA[_hoops_HCGS] * nr->_hoops_ARA->_hoops_CICP.scale + nr->_hoops_ARA->_hoops_CICP.translate);
				if (_hoops_SPII) {
					_hoops_SHPC = _hoops_SPII[j + lengths[i] - 1];
					if (_hoops_RSHA) {
						if (matrix) {
							_hoops_CRCRC (matrix, _hoops_RSHA[_hoops_SHPC], points[_hoops_HCGS], _hoops_HIPCP);
							_hoops_RRCRC (_hoops_RRIRC, _hoops_HIPCP, points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
						}
						else
							_hoops_RRCRC (_hoops_RRIRC, _hoops_RSHA[_hoops_SHPC], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
					}
					if (_hoops_ASHA)
						glColor3fv ((float const *) &_hoops_ASHA[_hoops_SHPC]);
				}
				if (matrix) {
					_hoops_SGCRC (matrix, points[_hoops_HCGS], _hoops_HIPCP);
					if (_hoops_ICHA) {
						_hoops_GRCRC (matrix, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_IIPCP);
						_hoops_RRCRC (_hoops_RRIRC, _hoops_IIPCP, _hoops_HIPCP, _hoops_CSRGR->_hoops_SRIRC);
					}
					glVertex3fv (&_hoops_HIPCP.x);
				}
				else {
					if (_hoops_ICHA)
						_hoops_RRCRC(_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
					glVertex3fv (&points[_hoops_HCGS].x);
				}
				j += lengths[i];
			}
			glEnd ();
		}

		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);

  done:

	if (_hoops_GPCP && _hoops_PCHA != pe->_hoops_PCHA)
		FREE_ARRAY (_hoops_PCHA, pe->point_count, RGB);

	if (_hoops_PCHA || _hoops_ASHA || _hoops_GPCP || pe->_hoops_HCHA)
		_hoops_ICGRC(_hoops_CSRGR);
	if (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		if (BIT(pe->_hoops_SRHA, _hoops_GGIA))
			_hoops_AARRC (_hoops_CSRGR, 0);
	}

} /* _hoops_RSGR _hoops_API _hoops_CCRI */

local void
draw_3d_polyedge (
		Net_Rendition const &nr,
		Polyedge const * pe)
{
	really_draw_3d_polyedge (nr, nr->_hoops_RHP, pe, null);
}

local void
_hoops_ISRI (
		Net_Rendition const &  nr,
		Polyedge const * pe,
		OGL_Display_List_Bin * _hoops_RRHA)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	Polyedge alter *_hoops_HPAS = (Polyedge alter *) pe;
	Line_Rendition const &_hoops_GHP = nr->_hoops_RHP;
	int weight;

	if ((weight = _hoops_GHP->weight) < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
	if (weight == 0)
		weight = 1;
	if (!pe) {
		_hoops_IPSGC *pair = _hoops_RRHA->_hoops_CRHA->PeekFirst();
		pe = (Polyedge const *)pair->geo;
	}
	if (_hoops_HSRI (nr, _hoops_GHP, pe, weight)) {
		if (_hoops_CSRGR->_hoops_CIGI)
			_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_GHCI;
		HD_Draw_Indexicated_3D_Polyedge (nr, pe);
		return;
	}

	if (_hoops_RRHA)
		_hoops_RRHA->_hoops_AGRI |= (_hoops_GGIA | DL_INDEX_INTERPOLATION);
	else
		_hoops_HPAS->_hoops_SRHA |= (_hoops_GGIA | DL_INDEX_INTERPOLATION);
	really_draw_3d_polyedge(nr, nr->_hoops_RHP, _hoops_HPAS, _hoops_RRHA);
}


local void
_hoops_PPAS (
		Net_Rendition const & nr,
		Polyedge const *pe)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);

	_hoops_RAPRC("draw_indexed_polyedge", true);

	_hoops_ISRI (nr, pe, null);
}


local void
draw_3d_grid (
		Net_Rendition const & nr,
		Grid const			*grid)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);

	_hoops_RAPRC("draw_3d_grid", true);

	if (_hoops_CSRGR->_hoops_CIGI)
		_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_RGCP;
	HD_Std_3D_Grid (nr, grid);
}

#ifndef WINDOWS_SYSTEM
local void
draw_3d_text (
		Net_Rendition const & nr,
		_hoops_HACC const			*text)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);

	_hoops_RAPRC("draw_3d_text", true);

	if (_hoops_CSRGR->_hoops_CIGI)
		_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_PGCP;
	HD_Std_3D_Text (nr, text);
}
#endif


local void
draw_3d_polyedge_from_tristrip (
	Net_Rendition const &		nr,
	Polyedge const *			pe,
	Tristrip const *			ts) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	OGLData alter *				_hoops_CSRGR = OGLD (dc);
	Point const *				points = pe->points;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Line_Rendition const &		_hoops_GHP = nr->_hoops_RHP;
	Tristrip const *			_hoops_RACRC = ts;
	_hoops_IAPA const *	_hoops_CAPA = null;
	bool 						_hoops_ICIRC = false;
	bool						antialias = false;
	OGL_Display_List alter *	odl = null;
	int							weight;

	_hoops_RAPRC("draw_3d_polyedge_from_tristrip", true);

	if ((weight = _hoops_GHP->weight) < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, _hoops_GHP->_hoops_PHP, _hoops_GHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
	if (weight == 0)
		weight = 1;

	if (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
			_hoops_SSP const &	_hoops_GGH = _hoops_IHCR->_hoops_RGH;

			if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
				if (_hoops_GGH->_hoops_IRH == null)
					HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
				_hoops_CAPA = _hoops_GGH->_hoops_IRH;
#if 0
				if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
					_hoops_IAHC = true;
#endif
			}
			else {
				_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
#if 0
				if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
					_hoops_IAHC = true;
#endif
			}
		}

		_hoops_GGGH(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		_hoops_AIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));

		antialias = weight == 1 &&
			BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)&&
			BIT(nr->_hoops_SRA->_hoops_PGCC.flags, _hoops_SPPGH);

		if (_hoops_CSRGR->_hoops_RPCI != _hoops_GHP->_hoops_CPA) {
			_hoops_CSRGR->_hoops_RPCI = _hoops_GHP->_hoops_CPA;

			if (_hoops_GHP->_hoops_CHA->_hoops_IRIR != 1.0f) {
				_hoops_SCIGC (_hoops_CSRGR);
				OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_GHP->_hoops_CHA, 0, 0);
			}
			else {
				_hoops_SCIGC (_hoops_CSRGR);
				_hoops_APIGC (_hoops_CSRGR, &_hoops_GHP->color, nr);
			}

			ENSURE_LINE_PATTERN (_hoops_CSRGR, _hoops_GHP->line_style);
			ENSURE_LINE_WEIGHT (_hoops_CSRGR, weight);
		}

		ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH||antialias);
		_hoops_IPGP(_hoops_CSRGR, BIT(_hoops_IHCR->flags, _hoops_CASP));
		ENSURE_LINE_SMOOTH(_hoops_CSRGR, antialias);

		ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);
	}

	if (nr->_hoops_IRR->_hoops_GAHA &&
		!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC &&
		_hoops_CSRGR->_hoops_RRSGC &&
		!BIT(pe->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS)) {
		Polyedge alter *_hoops_HPAS = (Polyedge alter *) pe;
		_hoops_GACR alter *dl;
		bool alter _hoops_RACR=false;
		unsigned int error;

		ENSURE_LIST_BASE(_hoops_CSRGR, 0);

		_hoops_RACR = _hoops_AACR(nr, &_hoops_HPAS->_hoops_GAHA, &dl, &odl, OGL_DL_GEOMETRY);

		if (_hoops_RACR) {
			error = glGetError ();
			/* _hoops_CAHP _hoops_SPR _hoops_PPRAR _hoops_AIRI _hoops_HIGR _hoops_CRSRR */
			odl->item.geometry.id = glGenLists(1);
			odl->_hoops_CARH = 16 * pe->total;
			if (pe->_hoops_ICHA)
				odl->_hoops_CARH += 12 * pe->total;
			if (pe->_hoops_CCHA)
				odl->_hoops_CARH += pe->total * pe->_hoops_GSHA * sizeof(_hoops_RSSH);
			if (HOOPS_WORLD->display_list_vram_usage + odl->_hoops_CARH > HOOPS_WORLD->_hoops_PHARR) {
				odl->item.geometry.id = _hoops_RSARR; /* _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GRHP _hoops_IRCC */
				odl->_hoops_CARH = 0;
			}
			else
				HOOPS_WORLD->display_list_vram_usage += odl->_hoops_CARH;
		}

		if (!_hoops_CSRGR->_hoops_CSC._hoops_RAIH ||
			(dl->_hoops_AGRI & _hoops_ACRC) == (pe->_hoops_SRHA & _hoops_ACRC))
			_hoops_ICIRC = true;

		/* _hoops_CASRR, _hoops_RPP _hoops_HAHH */
		if (odl->item.geometry.id != _hoops_RSARR &&
			(_hoops_RACR ||
				dl->_hoops_GSAI != pe->_hoops_GSAI ||
				!_hoops_ICIRC)) {

			if (BIT(pe->_hoops_SRHA, DL_DO_NOT_RECOMPILE)) {
				HD_Queue_Destroy_List (odl, true);
				return;
			}

			/* _hoops_CASRR _hoops_RH _hoops_HIGR */
			glNewList (odl->item.geometry.id, GL_COMPILE);
			_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = true;
			_hoops_CSRGR->_hoops_CSC._hoops_SCIRC = true;
			draw_3d_polyedge_from_tristrip(nr, pe, ts); /* _hoops_GHHA */
			_hoops_CSRGR->_hoops_CSC._hoops_SCIRC = false;
			_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = false;
			glEndList ();

			if ((error = glGetError ()) != 0) {
				/* _hoops_CIH _hoops_SCH _hoops_PPR _hoops_GRHHR _hoops_IH _hoops_RH _hoops_AAH */
				glDeleteLists (odl->item.geometry.id, 1);
				/* _hoops_PISPR _hoops_IRS _hoops_ISPC _hoops_HIGR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GRHP _hoops_IRCC */
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"OpenGL reported an error during display list compilation in draw_3d_polyedge");
				odl->item.geometry.id = _hoops_RSARR;
			}

			dl->_hoops_GSAI = pe->_hoops_GSAI;
			dl->_hoops_AGRI = pe->_hoops_SRHA;
		}

		/* _hoops_GRCI */
		if (odl->item.geometry.id) {
			do {
				if (_hoops_CAPA != null) {
					_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				}

				odl->_hoops_GPPI = HOOPS_WORLD->_hoops_GPPI;
				glCallList (odl->item.geometry.id);	 /* _hoops_AA _hoops_SCH! */

				if (_hoops_CAPA != null)
					_hoops_CAPA = _hoops_CAPA->next;
			} while (_hoops_CAPA != null);

#if 0
			if (_hoops_PCHA || _hoops_ASHA)
				_hoops_ICGRC(_hoops_CSRGR);
#endif
			return;
		}
	}


	if (ANYBIT (nr->_hoops_RGP, T_GENERIC_EDGES|_hoops_CRHGP))
		ENSURE_CULLING_OFF (_hoops_CSRGR);
	else if (ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA))
		_hoops_AGSP (_hoops_CSRGR, _hoops_IHCR, _hoops_RGCGC);

	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
	do {
		if (_hoops_CAPA != null) {
			_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
		}

		ts = _hoops_RACRC;
		do {
			int _hoops_PHHA = ts->_hoops_PHHA;
			int *lengths = ts->lengths;
			int *_hoops_AIHA = ts->_hoops_AIHA;
			int *face_indices = ts->face_indices;

			if (BIT (ts->face_attributes.flags, _hoops_HSIPR) &&
				!BIT (nr->_hoops_IRR->locks._hoops_RGP, T_FACES) &&
				BIT (nr->_hoops_RGP, _hoops_CRHGP) &&
				!BIT (nr->_hoops_RGP, T_GENERIC_EDGES)) {
				/* _hoops_HSGR _hoops_SPPR _hoops_IIGR _hoops_PSIPR _hoops_CCGI _hoops_CGPR _hoops_RGAR _hoops_HCHAR _hoops_IH _hoops_SCCPR _hoops_SPPR */
			}
			else if (face_indices == null) {	/* _hoops_HCR _hoops_HIPH */
				glBegin (GL_TRIANGLES);
				while (_hoops_PHHA-- > 0) {
					int			length = *lengths++;
					bool	_hoops_SICPR = false;
					bool	_hoops_AGRCA = false;
					int			_hoops_HSPI, _hoops_ISPI, _hoops_CSPI;

					if (length < 0) {
						length = -length;
						_hoops_SICPR = true;
					}

					_hoops_HSPI = *_hoops_AIHA++;
					_hoops_ISPI = *_hoops_AIHA++;

					length -= 2;
					while (length-- > 0) {
						_hoops_CSPI = *_hoops_AIHA++;

						if (!_hoops_AGRCA) {
							glVertex3fv (&points[_hoops_HSPI].x);
							glVertex3fv (&points[_hoops_ISPI].x);
							glVertex3fv (&points[_hoops_CSPI].x);
						}
						else {
							glVertex3fv (&points[_hoops_HSPI].x);
							glVertex3fv (&points[_hoops_CSPI].x);
							glVertex3fv (&points[_hoops_ISPI].x);
						}

						if (!_hoops_SICPR) {
							_hoops_HSPI = _hoops_ISPI;
							_hoops_AGRCA = !_hoops_AGRCA;
						}
						_hoops_ISPI = _hoops_CSPI;
					}
				}
				glEnd ();
			}
			else {
				while (_hoops_PHHA-- > 0) {
					int			length = *lengths++;
					bool	_hoops_SICPR = false;
					bool	_hoops_AGRCA = false;
					int			_hoops_HSPI, _hoops_ISPI;

					if (length < 0) {
						length = -length;
						_hoops_SICPR = true;
					}

					_hoops_HSPI = *_hoops_AIHA++;
					_hoops_ISPI = *_hoops_AIHA++;
					face_indices += 2;

					length -= 2;

					while (length > 0) {
						int			count, i;

						for (count=1; count<length; count++)
							if (face_indices[count] != face_indices[0])
								break;

						glBegin (GL_POLYGON);
						if (_hoops_SICPR) {
							glVertex3fv (&points[_hoops_HSPI].x);
							glVertex3fv (&points[_hoops_ISPI].x);
							i = count;
							while (i-- > 0) {
								_hoops_ISPI = *_hoops_AIHA++;
								glVertex3fv (&points[_hoops_ISPI].x);
							}
						}
						else {
							if (!_hoops_AGRCA) {
								glVertex3fv (&points[_hoops_HSPI].x);
								glVertex3fv (&points[_hoops_ISPI].x);
								i = 1;
								while (i < count) {
									glVertex3fv (&points[_hoops_AIHA[i]].x);
									i += 2;
								}
								if ((count & 1) == 0)
									i = count-2;
								else
									i = count-1;
								while (i >= 0) {
									glVertex3fv (&points[_hoops_AIHA[i]].x);
									i -= 2;
								}
							}
							else {
								glVertex3fv (&points[_hoops_ISPI].x);
								glVertex3fv (&points[_hoops_HSPI].x);
								i = 0;
								while (i < count) {
									glVertex3fv (&points[_hoops_AIHA[i]].x);
									i += 2;
								}
								if ((count & 1) == 0)
									i = count-1;
								else
									i = count-2;
								while (i > 0) {
									glVertex3fv (&points[_hoops_AIHA[i]].x);
									i -= 2;
								}
							}

							_hoops_AIHA += count-2;
							_hoops_HSPI = *_hoops_AIHA++;
							_hoops_ISPI = *_hoops_AIHA++;

							if ((count & 1) != 0)	/* _hoops_PISC _hoops_RPSA */
								_hoops_AGRCA = !_hoops_AGRCA;
						}
						glEnd ();

						face_indices += count;
						length -= count;
					}
				}
			}
		} while ((ts = ts->next) != null);


		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

#if 0
	if (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC) {
		if (_hoops_PCHA || _hoops_ASHA)
			_hoops_ICGRC(_hoops_CSRGR);
	}
#endif
}


#define OGL_GLYPH_DOT				1
#define OGL_GLYPH_FILLED_CIRCLE		2
#define OGL_GLYPH_FILLED_SQUARE		3

/* _hoops_CGIC _hoops_RPP _hoops_RH _hoops_SCGR _hoops_RPHH _hoops_HRGR _hoops_IIGR _hoops_IRS _hoops_GPRR _hoops_SGS _hoops_PAH _hoops_SHH _hoops_GSIA _hoops_HCCP,
	_hoops_PPR _hoops_RPP _hoops_HIS, _hoops_PGAP _hoops_SPR _hoops_SCH _hoops_HRGR*/
local bool
_hoops_SRSC (_hoops_GASC const & g, int alter *_hoops_AACRC)
{
	char const *t;

	if (g->name.length == 1) {
		if (g->name.text[0] == '.') {
			*_hoops_AACRC = OGL_GLYPH_DOT;
			return true;
		}
		else if (g->name.text[0] == '@') {
			*_hoops_AACRC = OGL_GLYPH_FILLED_CIRCLE;
			return true;
		}
	}
	else if (g->name.length == 3) {
		t = g->name.text;
		if (t[0] == '(' && t[1] == '*' && t[2] == ')') {
			*_hoops_AACRC = OGL_GLYPH_FILLED_CIRCLE;
			return true;
		}
		else if (t[0] == '[' && t[1] == '*' && t[2] == ']') {
			*_hoops_AACRC = OGL_GLYPH_FILLED_SQUARE;
			return true;
		}
	}
	return false;
}


/* _hoops_IH _hoops_IGGA _hoops_GIHA _hoops_SGS _hoops_SR _hoops_CGIC _hoops_CHR _hoops_GRHCP _hoops_RH _hoops_RGIRR
	_hoops_CIAS _hoops_PPSR _hoops_IGIR _hoops_IH _hoops_RH _hoops_RAGA _hoops_GSIA, _hoops_SR _hoops_RRP _hoops_IS _hoops_CAH */
local void
_hoops_PACRC (Net_Rendition const &nr, Polymarker const *pm, int _hoops_HCGS)
{
	Polymarker _hoops_HACRC;

	ZERO_STRUCT (&_hoops_HACRC, Polymarker);
	_hoops_HACRC._hoops_SRHA |= _hoops_SRHH;
	_hoops_HACRC.length = _hoops_HACRC.point_count = 1;
	_hoops_HACRC._hoops_AIHA = null;
	_hoops_HACRC.points = &pm->points[_hoops_HCGS];
	_hoops_HACRC._hoops_PCHA = (pm->_hoops_PCHA ? &pm->_hoops_PCHA[_hoops_HCGS] : null);
	_hoops_HACRC._hoops_HCHA = (pm->_hoops_HCHA ? &pm->_hoops_HCHA[_hoops_HCGS] : null);
	_hoops_HACRC._hoops_ICHA = (pm->_hoops_ICHA ? &pm->_hoops_ICHA[_hoops_HCGS] : null);
	_hoops_HACRC._hoops_CCHA = (pm->_hoops_CCHA ? &pm->_hoops_CCHA[_hoops_HCGS*pm->_hoops_GSHA] : null);
	_hoops_HACRC._hoops_IPII = 0; /* _hoops_ISCP _hoops_CICRR _hoops_CHR _hoops_CRGR _hoops_RH _hoops_IRGP _hoops_IIGR _hoops_PSPP _hoops_GSRSA, _hoops_HIS _hoops_SSIA _hoops_PAHA'_hoops_RA _hoops_SGIPR _hoops_RRP _hoops_IS _hoops_SHH _hoops_HGGPR */
	_hoops_HACRC.next = null;
	HD_Std_3D_Polymarker (nr, &_hoops_HACRC);
}

// _hoops_PASC _hoops_HASC _hoops_IS _hoops_IASC 
local float _hoops_CASC (_hoops_SASC const & cuboid, _hoops_HRPA const & matrix)
{
	Point	p[8];
	cuboid._hoops_GPSC(&p[0]);

	float	_hoops_RPSC = MAX_FLOAT;

	for (int i = 0; i < 8; i++) {
		float z = _hoops_CPRA (matrix.elements, p[i]);
		if (z < _hoops_RPSC)
			_hoops_RPSC = z;
	}

	return _hoops_RPSC;
}

local void _hoops_IACRC (
		Net_Rendition const & nr,
		Polymarker const * pm,
		float size,
		_hoops_HRPA *_hoops_PHSC,
		bool _hoops_RIHRC,
		bool _hoops_CACRC,
		int _hoops_PCIGI,
		int _hoops_HCIGI,
		bool _hoops_RRIRC) {


	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	Point const *points = pm->points;
	RGB const *_hoops_PCHA = pm->_hoops_PCHA;
	RGBAS32 const* _hoops_RGIA = pm->_hoops_RGIA;
	Vector const *_hoops_ICHA = pm->_hoops_ICHA;
	int *_hoops_AIHA = pm->_hoops_AIHA;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	_hoops_IAPA const	*_hoops_CAPA = null;
	int i;
	int length;
	int _hoops_HCGS;

	if (_hoops_AIHA || !pm->point_count)
		length = pm->length;
	else
		length = pm->point_count;

	do {
		if (_hoops_CAPA != null) {
			_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
		}

		_hoops_GPRH(_hoops_ICGS) += (_hoops_HCIGI - _hoops_PCIGI);

		if (_hoops_CACRC) {
			float z, _hoops_SACPA, _hoops_SACRC, _hoops_GPCRC;

			/* _hoops_ARI _hoops_SR _hoops_RRP _hoops_IS _hoops_ARP _hoops_IRS _hoops_GIAH _hoops_GPIA _hoops_IGIR _hoops_IH _hoops_GRR _hoops_IGGA _hoops_GPIA */
			ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); /* _hoops_RPP _hoops_HHPS _hoops_AIRI _hoops_CPCI, _hoops_SR _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_ARI!!! */
			_hoops_SACRC = 1/_hoops_IHCR->_hoops_SPH->_hoops_SRIR;
			_hoops_GPCRC = -_hoops_IHCR->_hoops_SPH->_hoops_SRIR;
			_hoops_HCGS = -1;
			/* _hoops_RPCRC _hoops_SIGP: _hoops_HGI _hoops_GPGH'_hoops_RA _hoops_APCRC _hoops_GGR _hoops_PPCRC */
			for (i = 0; i < length; i++) {
				if (_hoops_AIHA)
					_hoops_HCGS = _hoops_AIHA[i];
				else
					_hoops_HCGS++;
				z = _hoops_CPRA (_hoops_PHSC->elements, pm->points[_hoops_HCGS]);
				/* _hoops_ISPR _hoops_IH _hoops_GHIPR _hoops_RH _hoops_RHC */
				if (z < _hoops_GPCRC)
					continue;
				_hoops_SACPA = size / (z*_hoops_SACRC + 1);
				if (_hoops_SACPA > _hoops_CSRGR->_hoops_HPCRC) {
					_hoops_GPPRC (_hoops_CSRGR, 1);
					_hoops_ICGRC(_hoops_CSRGR);
					_hoops_PACRC (nr, pm, _hoops_HCGS);
				}
				else {
					if (_hoops_SACPA < 1)
						_hoops_SACPA = 1;
					_hoops_GPPRC (_hoops_CSRGR, _hoops_SACPA);
					glBegin (GL_POINTS);
						if (_hoops_PCHA != null)
							_hoops_IPCRC (_hoops_RIHRC, (float const *) &_hoops_PCHA[_hoops_HCGS]);
						else if (_hoops_RGIA != null)
							FORCE_COLOR_4F(_hoops_RGIA[_hoops_HCGS].r/255.0, _hoops_RGIA[_hoops_HCGS].g/255.0, _hoops_RGIA[_hoops_HCGS].b/255.0, _hoops_RGIA[_hoops_HCGS].a/255.0, _hoops_RIHRC);
						if (_hoops_ICHA != null)
							_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
						if (pm->_hoops_HCHA)
							glTexCoord1f (pm->_hoops_HCHA[_hoops_HCGS]);
						glVertex3fv (&points[_hoops_HCGS].x);
					glEnd ();
				}
			}
		}
		else {
			/* _hoops_HAR _hoops_ICIC _hoops_IS _hoops_CAH _hoops_RAS _hoops_RGR _hoops_PPSR */
			glBegin (GL_POINTS);
			{
				i= _hoops_PCIGI;
				_hoops_HCGS = -1;
				while (i<_hoops_HCIGI && i < length) {
					if (_hoops_AIHA)
						_hoops_HCGS = _hoops_AIHA[i];
					else
						_hoops_HCGS++;

					if (_hoops_ICHA)
						_hoops_RRCRC (_hoops_RRIRC, _hoops_ICHA[_hoops_HCGS], points[_hoops_HCGS], _hoops_CSRGR->_hoops_SRIRC);
					if (_hoops_PCHA)
						_hoops_IPCRC (_hoops_RIHRC, (float const *) &_hoops_PCHA[_hoops_HCGS]);
					else if (_hoops_RGIA != null)
						FORCE_COLOR_4F(_hoops_RGIA[_hoops_HCGS].r/255.0, _hoops_RGIA[_hoops_HCGS].g/255.0, _hoops_RGIA[_hoops_HCGS].b/255.0, _hoops_RGIA[_hoops_HCGS].a/255.0, _hoops_RIHRC);
					if (pm->_hoops_HCHA)
						glTexCoord1f (pm->_hoops_HCHA[_hoops_HCGS]);
					glVertex3fv (&points[_hoops_HCGS].x);
					i++;
				}
			}
			glEnd ();
		}

		if (_hoops_CAPA != null)
			_hoops_CAPA = _hoops_CAPA->next;
	} while (_hoops_CAPA != null);

}



/*
 * _hoops_SRAC
 */
local void
_hoops_CPCRC (
		Net_Rendition const & nr,
		Polymarker const * pm,
		float size,
		_hoops_HRPA *_hoops_PHSC,
		bool _hoops_RIHRC,
		bool _hoops_CACRC,
		int _hoops_PCIGI,
		int _hoops_HCIGI,
		bool _hoops_RRIRC)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	RGB const *_hoops_PCHA = pm->_hoops_PCHA;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	bool _hoops_CRRS = false;
	unsigned int _hoops_SPCRC;
	OGL_Polymarker_Vertex_Buffer_Object *	_hoops_SAAS = null;

	_hoops_RAPRC("old_draw_3d_polymarker", true);

	if (_hoops_CSRGR->_hoops_CIGI)
		_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_RGPI;

	if (pm->_hoops_ICHA) {
		if (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI) ||
		   !ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA)) {
			_hoops_RRIRC = _hoops_PRIRC;
			_hoops_HRIRC (_hoops_CSRGR, nr);
			ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC);
		}
	}

	if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI))
		_hoops_RIHRC = true;

	if (BIT (pm->_hoops_SRHA, DL_DO_NOT_RECOMPILE))
		_hoops_CRRS = true;
	else if (nr->_hoops_IRR->_hoops_GAHA == Display_List_GEOMETRY)
		_hoops_CRRS = !BIT(pm->_hoops_SRHA, DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS) && (pm->length > 8);
	else if (nr->_hoops_IRR->_hoops_GAHA == Display_List_SEGMENT)
		_hoops_CRRS = !BIT(pm->_hoops_SRHA, DL_SUPPRESS_SEGMENT_DISPLAY_LISTS) && (pm->length > 8);
	else
		_hoops_CRRS = false;

	if (_hoops_CRRS) {
		Polymarker alter *_hoops_PRRS = (Polymarker alter *) pm;
		_hoops_GACR alter *dl;
		OGL_Display_List alter *odl=0;
		bool alter _hoops_RACR=false;
		unsigned int error;

		ENSURE_LIST_BASE(_hoops_CSRGR, 0);

		if (_hoops_CSRGR->_hoops_IHPGC)
			_hoops_SPCRC = OGL_DL_POLYMARKER_VBO_LIST;
		else
			_hoops_SPCRC = OGL_DL_GEOMETRY_LIST;

		_hoops_RACR = _hoops_AACR(nr, &_hoops_PRRS->_hoops_GAHA, &dl, &odl, _hoops_SPCRC);

		if (!_hoops_RACR &&
			!_hoops_SPRC (nr, T_VERTICES, pm, dl, odl)) {
			HD_Queue_Destroy_List (odl, true);
			if (BIT (pm->_hoops_SRHA, DL_DO_NOT_RECOMPILE))
				return;
			_hoops_RACR = _hoops_AACR(nr, &_hoops_PRRS->_hoops_GAHA, &dl, &odl, _hoops_SPCRC);
		}

		if (_hoops_RACR) {
			error = glGetError ();

			if (_hoops_SPCRC == OGL_DL_GEOMETRY_LIST) {
				/* _hoops_HA _hoops_SR _hoops_CAHP _hoops_PPSGA _hoops_IIGR _hoops_PPRAR _hoops_AIRI _hoops_HIGR _hoops_GHCRC */
				OGL_DL_ID_List* list;
				odl->type = OGL_DL_GEOMETRY_LIST;
				list = POOL_NEW(dc->memory_pool, OGL_DL_ID_List)(dc->memory_pool);
				odl->item.geometry.id = (POINTER_SIZED_INT)list;
				for (int i = pm->length; i > 0; i-= _hoops_CSRGR->_hoops_PHAI) {
					GLuint id = glGenLists(1);
					list->AddLast(id);
				}
				odl->_hoops_CARH = 12 * pm->point_count;
				if (pm->_hoops_ICHA)
					odl->_hoops_CARH += 12 * pm->point_count;
				if (pm->_hoops_CCHA)
					odl->_hoops_CARH += pm->point_count * pm->_hoops_GSHA * sizeof(_hoops_RSSH);
				if (HOOPS_WORLD->display_list_vram_usage + odl->_hoops_CARH > HOOPS_WORLD->_hoops_PHARR) {
					odl->item.geometry.id = _hoops_RSARR; /* _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GRHP _hoops_IRCC */
					odl->_hoops_CARH = 0;
				}
				else
					HOOPS_WORLD->display_list_vram_usage += odl->_hoops_CARH;

				list->ResetCursor();
				for (int i = _hoops_PCIGI; i < _hoops_HCIGI; i += _hoops_CSRGR->_hoops_PHAI) {
					GLuint _hoops_RHCRC = (GLuint)list->PeekCursor();

					glNewList (_hoops_RHCRC, GL_COMPILE);
					_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = true;
					_hoops_CSRGR->_hoops_CSC._hoops_SCIRC = true;
					ASSERT (!_hoops_CACRC);
						_hoops_IACRC(nr, pm, size, _hoops_PHSC, _hoops_RIHRC, false,i, i+_hoops_CSRGR->_hoops_PHAI, _hoops_RRIRC);
					_hoops_CSRGR->_hoops_CSC._hoops_SCIRC = true;
					_hoops_CSRGR->_hoops_CSC._hoops_IPAGC = false;
					glEndList ();


					if ((error = glGetError ()) != 0) {
						/* _hoops_CIH _hoops_SCH _hoops_PPR _hoops_GRHHR _hoops_IH _hoops_RH _hoops_AAH */
						glDeleteLists (_hoops_RHCRC, 1);
						/* _hoops_PISPR _hoops_IRS _hoops_ISPC _hoops_HIGR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_GRHP _hoops_IRCC */
						_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							"OpenGL reported an error during display list compilation in draw_3d_polymarker");
						odl->item.geometry.id = _hoops_RSARR;
					}

					list->AdvanceCursor();
				}
			}
			else {
				/* _hoops_SSAI _hoops_RH _hoops_RSSA _hoops_CRGR _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_AHCRC */
				OGL_DL_VBO_List* list;
				list = POOL_NEW(dc->memory_pool, OGL_DL_VBO_List)(dc->memory_pool);
				odl->item.geometry.id = (POINTER_SIZED_INT)list;
				odl->_hoops_CARH = 0;

				for (int i = pm->length; i > 0; i-= _hoops_CSRGR->_hoops_PHAI) {
					int end = -1;
					int start = i - _hoops_CSRGR->_hoops_PHAI;

					if (start < 0)
						start = 0;
					if (i <= _hoops_CSRGR->_hoops_PHAI)
						end = i;
					else {
						end = start + (int)( ((float)_hoops_CSRGR->_hoops_PHAI));
					}
					_hoops_AIHRC (&_hoops_SAAS, nr, pm, _hoops_RIHRC, start, end);
					if (!_hoops_SAAS) {
						if (list->Count() == 0) {
							delete list;
							odl->item.geometry.id = _hoops_RSARR;
						}
						else {
							//_hoops_SCH _hoops_CSAP _hoops_HAH _hoops_AHSC _hoops_IS _hoops_SIHRR.  _hoops_SAHR _hoops_PGSA _hoops_RH _hoops_ACSP
							end = (int)( ((float)pm->length)*nr->_hoops_SCP->_hoops_CSRS);
							_hoops_IACRC(nr, pm, size, _hoops_PHSC, _hoops_RIHRC, _hoops_CACRC, start, end, _hoops_RRIRC);
						}
						break;
					}
					else
						list->AddLast(_hoops_SAAS);
				}
			}
			dl->_hoops_GSAI = pm->_hoops_GSAI;
			dl->_hoops_AGRI = pm->_hoops_SRHA;
		}

		/* _hoops_GRCI */
		if (odl->item.geometry.id != _hoops_RSARR) {
			odl->_hoops_GPPI = HOOPS_WORLD->_hoops_GPPI;
			if (odl->type == OGL_DL_GEOMETRY_LIST) {
				_hoops_GPRH (_hoops_RPAS) += (int)( ((float)pm->length)*nr->_hoops_SCP->_hoops_CSRS);
				OGL_DL_ID_List* list = (OGL_DL_ID_List *)I2V(odl->item.geometry.id);
				list->ResetCursor();
				for (int i = 0; i < (int)( ((float)pm->length)*nr->_hoops_SCP->_hoops_CSRS); i += _hoops_CSRGR->_hoops_PHAI) {
					glCallList(list->PeekCursor());
					list->AdvanceCursor();
				}
			}
			else if (odl->type == OGL_DL_POLYMARKER_VBO_LIST) {
				OGL_DL_VBO_List* list = (OGL_DL_VBO_List*)I2V(odl->item.geometry.id);

				list->ResetCursor();

				int _hoops_PHCRC = (int)(nr->_hoops_SCP->_hoops_CSRS*(float)pm->length);
				int _hoops_HAAS = _hoops_PHCRC;
				int _hoops_CAAS = 0;
				for (;;) {
					OGL_Polymarker_Vertex_Buffer_Object* _hoops_SAAS = (OGL_Polymarker_Vertex_Buffer_Object*)list->PeekCursor();
					if (!_hoops_SAAS)
						break;
					if (_hoops_PHCRC > _hoops_SAAS->point_count) {
						_hoops_HHCRC (nr, _hoops_SAAS, 1.0);
						_hoops_PHCRC -= _hoops_SAAS->point_count;
						_hoops_CAAS += _hoops_SAAS->point_count;
					}
					else {
						float _hoops_RCGCR = (float)_hoops_PHCRC/_hoops_SAAS->point_count;
						_hoops_HHCRC (nr, _hoops_SAAS, _hoops_RCGCR);
						_hoops_CAAS = _hoops_HAAS;
						break;
					}
					list->AdvanceCursor();
				}
				if (_hoops_CAAS < _hoops_HAAS)
					_hoops_IACRC(nr, pm, size, _hoops_PHSC, _hoops_RIHRC, _hoops_CACRC, _hoops_CAAS, _hoops_HAAS, _hoops_RRIRC);
			}
			else {
				_hoops_GPRH (_hoops_RPAS) += pm->length;
				glCallList (odl->item.geometry.id);	 /* _hoops_AA _hoops_SCH! */
			}

			/* _hoops_CASI _hoops_GH */
			if (_hoops_PCHA)
				_hoops_ICGRC(_hoops_CSRGR);
			return;
		}
		else {
			_hoops_IACRC(nr, pm, size, _hoops_PHSC, _hoops_RIHRC, _hoops_CACRC,0, (int)( ((float)pm->length)*nr->_hoops_SCP->_hoops_CSRS), _hoops_RRIRC);
		}
	}
	else {
		_hoops_IACRC(nr, pm, size, _hoops_PHSC, _hoops_RIHRC, _hoops_CACRC,0, (int)( ((float)pm->length)*nr->_hoops_SCP->_hoops_CSRS), _hoops_RRIRC);
	}
}


local void
draw_3d_marker (Net_Rendition const & nr,
				Marker const * m)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	bool						single = !_hoops_CSRGR->_hoops_AHPI;

	if (_hoops_CSRGR->_hoops_ISCI)	{
		if (!_hoops_CSRGR->_hoops_CIGI->_hoops_IHAI)
			_hoops_CSRGR->_hoops_CIGI->_hoops_IHAI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);

		if (dc->_hoops_SPA->color != null &&
			_hoops_CCAI (dc->_hoops_SPA->color, Color_MARKER) != null)
			_hoops_CSRGR->_hoops_CIGI->_hoops_GGHRC |= Color_MARKER;

		_hoops_IPSGC *pair = POOL_NEW(dc->memory_pool, _hoops_IPSGC)(nr, m, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color, single);	

		_hoops_CSRGR->_hoops_CIGI->_hoops_IHAI->AddFirst(pair);
		return;
	}
	_hoops_IAPA const		*_hoops_CAPA = null;
	bool						_hoops_IHCRC = false;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = nr->transform_rendition->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IHCRC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IHCRC = true;
		}
	}

	if (nr->_hoops_GSP->ysize < 0.0f ||
		nr->_hoops_GSP->ysize > 0.5f ||
		(nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) ||
		ANYBIT (nr->_hoops_GSP->glyph->flags, _hoops_GRAI) ||
		_hoops_IHCRC) {

		Point points[1024];
		Marker const *first = m;
		Marker const *prev = null;
		int count=0;

		do {
			if (m->orientation) {
				dc->_hoops_RAI = m;
				HD_Std_3D_Marker (nr, m);
			}
			else {
				points[count] = m->_hoops_CSAI;
				count++;
				if (count == _hoops_GGAPR(points)) {
					HD_Markers_To_Polymarker (nr, count, points);
					count = 0;
					first = m;
				}
			}
			prev = m;
			if (single || (m = (Marker const *)m->next) == null)
				break;
		} while (m->type == _hoops_PCIP);

		if (count == 1)
			HD_Std_3D_Marker (nr, prev);
		else
			HD_Markers_To_Polymarker (nr, count, points);
	}
	else {
		Marker const *	_hoops_CHCRC = m;

		_hoops_SCIGC (_hoops_CSRGR);
		_hoops_GGGH(_hoops_CSRGR, nr);
		_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
		_hoops_AIIGC(_hoops_CSRGR, nr);
		ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
		ENSURE_TRANSPARENCY (_hoops_CSRGR, nr->_hoops_CPP->_hoops_PRH._hoops_HRH);
		_hoops_IPGP(_hoops_CSRGR, BIT(nr->transform_rendition->flags, _hoops_CASP));
		_hoops_APIGC (_hoops_CSRGR, &nr->_hoops_GSP->color, nr);
		_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
		do {
			if (_hoops_CAPA != null) {
				_hoops_HCIGC (_hoops_CSRGR);
				_hoops_CPIGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
				_hoops_IGCGC (_hoops_CSRGR);
			}
			m = _hoops_CHCRC;


			glBegin (GL_POINTS);
				do {
					_hoops_GPRH(_hoops_SCCA)++;
					glVertex3fv ((float *) &(m->_hoops_CSAI));
					m = (Marker const *)m->next;
				} _hoops_RGGA (single || (m == null) || (m->type != _hoops_PCIP));
			glEnd ();

			if (_hoops_CAPA != null)
				_hoops_CAPA = _hoops_CAPA->next;
		} while (_hoops_CAPA != null);

		if (m == null)
			return;
	}
}

local bool
_hoops_SGAI (Net_Rendition const & nr,
					_hoops_ICP const & _hoops_CCP,
					Polymarker const * pm,
					int *_hoops_SHCRC)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	int _hoops_AACRC = OGL_GLYPH_DOT;

	if ((nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) ||
		(BIT (_hoops_IHCR->flags, _hoops_GRHH) && !BIT (_hoops_IHCR->flags, _hoops_PRIR)) ||
		ANYBIT (_hoops_CCP->glyph->flags, _hoops_GRAI))
		return true;
	if (_hoops_CCP->ysize < 0.0f || _hoops_CCP->ysize > 0.5f) {
		if (!_hoops_SRSC (_hoops_CCP->glyph, &_hoops_AACRC))
			return true;
		if (!_hoops_CSRGR->dc->options._hoops_HPSC) {
			if (_hoops_AACRC == OGL_GLYPH_FILLED_CIRCLE)
				return true;
			if (_hoops_AACRC == OGL_GLYPH_FILLED_SQUARE &&
				_hoops_CSRGR->_hoops_AIPGA > 1)
				return true;
		}
	}
	if (_hoops_SHCRC)
		*_hoops_SHCRC = _hoops_AACRC;
	if (_hoops_CCP->_hoops_CHA->_hoops_ARIR)
		return true;
	UNREFERENCED (pm);
	return false;
}


local void
draw_3d_polymarker (Net_Rendition const & nr,
					Polymarker const * pm)
{
	Display_Context alter *dc = (Display_Context alter *) nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	RGB const *_hoops_PCHA = pm->_hoops_PCHA;
	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
	_hoops_ICP const &_hoops_CCP = nr->_hoops_SCP;
	int *_hoops_AIHA = pm->_hoops_AIHA;
	_hoops_IAPA const	*_hoops_CAPA = null;
	int _hoops_AACRC;
	float size = 1;
	_hoops_HRPA *_hoops_PHSC = null;
	bool _hoops_IAHC = false;
	bool _hoops_RIHRC = false;
	bool _hoops_CACRC = false;
	bool _hoops_RRIRC = 0;
	bool _hoops_CRSPH = false;

	_hoops_RAPRC("draw_3d_polymarker", true);

	_hoops_IAHC = _hoops_SGAI (nr, nr->_hoops_SCP, pm, &_hoops_AACRC);

	if (!_hoops_IAHC) {
		if (pm->_hoops_HCHA) {
			Polymarker alter *_hoops_PRRS = (Polymarker alter *) pm;
			_hoops_PRRS->_hoops_SRHA |= (_hoops_GGIA | DL_INDEX_INTERPOLATION);
		}
		if (BIT (pm->_hoops_SRHA, _hoops_GGIA)) {
			_hoops_IAHC = !OGL_DEFINE_INTERPOLATION_TEXTURE (_hoops_CSRGR, nr);
			_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, 0);
		}
	}

	if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
		_hoops_SSP const &	_hoops_GGH = _hoops_IHCR->_hoops_RGH;

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			if (_hoops_GGH->_hoops_CRH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			if (_hoops_GGH->_hoops_PGH > _hoops_CSRGR->_hoops_GAH)
				_hoops_IAHC = true;
		}
	}

	if (_hoops_IAHC) {
		if (_hoops_CSRGR->_hoops_CIGI) {
			if (dc->_hoops_RAI && dc->_hoops_RAI->type == _hoops_PIRS)
				_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_HCIP;
			else
				_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_RGPI;
		}
		HD_Std_3D_Polymarker (nr, pm);
		goto done;
	}


	if (_hoops_CSRGR->_hoops_ISCI > 0) {
		bool _hoops_HIRS = false;

		if (BIT (pm->_hoops_SRHA, DL_DO_NOT_DEFER))
			_hoops_HIRS = true;

		if (!_hoops_HIRS) {
			_hoops_IPSGC *pair;
			_hoops_AIGI *list = null;
			bool _hoops_IIRS = false;

			if (dc->_hoops_RAI && 
				dc->_hoops_RAI->type == _hoops_PIRS) 
			{
				_hoops_IIRS = (dc->_hoops_SPA->color && BIT (dc->_hoops_SPA->color->_hoops_GHA, Color_MARKER));
				if (BIT (_hoops_CSRGR->_hoops_CIGI->_hoops_RRSI, _hoops_HCIP))
					return;  //_hoops_CIRS _hoops_SIRS _hoops_IS _hoops_CRHR _hoops_GCRS _hoops_RCRS _hoops_CPAP
				if (!_hoops_CSRGR->_hoops_CIGI->_hoops_IHAI)
					_hoops_CSRGR->_hoops_CIGI->_hoops_IHAI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
				list = _hoops_CSRGR->_hoops_CIGI->_hoops_IHAI;			
			}
			else {
				_hoops_IIRS = (dc->_hoops_SPA->color && BIT (dc->_hoops_SPA->color->_hoops_GHA, Color_VERTEX));
				if (BIT (_hoops_CSRGR->_hoops_CIGI->_hoops_RRSI, _hoops_RGPI))
					return;  //_hoops_CIRS _hoops_SIRS _hoops_IS _hoops_CRHR _hoops_GCRS _hoops_RCRS _hoops_CPAP
				if (!_hoops_CSRGR->_hoops_CIGI->_hoops_HHAI)
					_hoops_CSRGR->_hoops_CIGI->_hoops_HHAI = POOL_NEW(dc->memory_pool, _hoops_AIGI)(dc->memory_pool);
				list = _hoops_CSRGR->_hoops_CIGI->_hoops_HHAI;			
			}
			if (BIT(pm->_hoops_SRHA, DL_TEMPORARY_DATA))
				HD_Isolate_Polymarker_Data (dc, pm);

			Polymarker alter *_hoops_RARS = (Polymarker alter *) pm;
			_hoops_RARS->_hoops_CARI |= _hoops_SARI;

			if (dc->_hoops_SPA->color != null &&
				_hoops_CCAI (dc->_hoops_SPA->color, Color_VERTEX) != null)
				_hoops_CSRGR->_hoops_CIGI->_hoops_GGHRC |= Color_VERTEX;

			pair = POOL_NEW(dc->memory_pool, _hoops_IPSGC)(nr, pm, dc->_hoops_SPA->modelling_matrix, dc->_hoops_SPA->color);

			list->AddFirst(pair);
			return;
		}
		_hoops_CSRGR->_hoops_CIGI->mask &= ~_hoops_RGPI;
	}

	_hoops_CRSPH = BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI);

	_hoops_GGGH(_hoops_CSRGR, nr);
	_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
	_hoops_AIIGC(_hoops_CSRGR, nr);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
	ENSURE_TRANSPARENCY (_hoops_CSRGR, 
		nr->_hoops_CPP->_hoops_PRH._hoops_HRH && 
		!_hoops_CSRGR->_hoops_GIIGC &&
		_hoops_CCP->_hoops_CHA->_hoops_IRIR != 1.0f);
	if (_hoops_CSRGR->_hoops_HSAC) {
		_hoops_IPGP(_hoops_CSRGR, BIT(_hoops_IHCR->flags, _hoops_CASP));
	}
	else {
		_hoops_IPGP(_hoops_CSRGR, true);
	}
	if (_hoops_AACRC != OGL_GLYPH_DOT) {
		GLint _hoops_GICRC[2];

		glGetIntegerv (GL_POINT_SIZE_RANGE, _hoops_GICRC);
		float _hoops_HPCRC = (float)_hoops_GICRC[1];

		if (_hoops_CCP->ysize < 0)
			size = 0.707f * HD_Compute_Generic_Size (nr, _hoops_CCP->_hoops_PHP, _hoops_CCP->_hoops_HHP, 1.0f, false, 0, true);
		else
			size = 1.414f * _hoops_CCP->ysize;

		if (_hoops_AACRC == OGL_GLYPH_FILLED_CIRCLE) {
			_hoops_AAPRC (_hoops_CSRGR, true);
			size *= 1.273f; //_hoops_RH _hoops_AHHSR _hoops_IIGR _hoops_CCAC _hoops_GAPA _hoops_IRS _hoops_PRHC _hoops_PPR _hoops_RRAA
		}
		else {
			_hoops_AAPRC (_hoops_CSRGR, false);
			size += 0.95f;
		}


		if (_hoops_CCP->_hoops_HHP == _hoops_SPSC &&
			_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH) {
			
				ZALLOC (_hoops_PHSC, _hoops_HRPA);
				HI_Multiply_Matrices (&_hoops_IHCR->_hoops_IPH->data, &_hoops_IHCR->_hoops_SPH->_hoops_PRPA, _hoops_PHSC);

				float _hoops_HHSC = ((size/_hoops_HPCRC)-1)*_hoops_IHCR->_hoops_SPH->_hoops_SRIR;

				float	_hoops_RPSC = -1.0f;
				if (pm->bounding != null)
					_hoops_RPSC = _hoops_CASC(pm->bounding->cuboid, *_hoops_PHSC);

				if (_hoops_RPSC > 1e-5f && size * _hoops_IHCR->_hoops_SPH->_hoops_SRIR / _hoops_RPSC < 2) {
					/* _hoops_IHH _hoops_RISA */
					size = 1;
				}
				else if (_hoops_CSRGR->_hoops_HPPGC &&
					(_hoops_CSRGR->dc->options._hoops_HPSC || // _hoops_CSAP _hoops_IRRC (_hoops_HGPGA->_hoops_CSPH->_hoops_AAP._hoops_HISRA, _hoops_RICRC) ||
					_hoops_RPSC > _hoops_HHSC)) {
						/* _hoops_AICRC */
						GLfloat _hoops_PCSSR[3] = { 0, 0, 0 };
						_hoops_PCSSR[2] = 1/(_hoops_IHCR->_hoops_SPH->_hoops_SRIR*_hoops_IHCR->_hoops_SPH->_hoops_SRIR);
						_hoops_CSRGR->_hoops_CPPGC(GL_DISTANCE_ATTENUATION_EXT, _hoops_PCSSR);
				}
				else {
					/* _hoops_IHH _hoops_CHPP */
					_hoops_CACRC = true;
					//_hoops_PICRC = _hoops_IHPR;
				}
		}
		else if (!_hoops_CSRGR->dc->options._hoops_HPSC &&  //_hoops_CSAP: _hoops_IRRC (_hoops_HGPGA->_hoops_CSPH->_hoops_AAP._hoops_HISRA, _hoops_RICRC) &&
				 size > _hoops_HPCRC) {
			HD_Std_3D_Polymarker (nr, pm);
			return;
		}
		_hoops_GPPRC (_hoops_CSRGR, size);
	}

	if (BIT (HOOPS_WORLD->system_flags, _hoops_RGRI) ||
		!ANYBIT (_hoops_IHCR->heuristics, _hoops_RSA)) {
			_hoops_RRIRC = _hoops_PRIRC;
			_hoops_HRIRC (_hoops_CSRGR, nr);
	}

	if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_HAI))
		_hoops_RIHRC = true;

	if (_hoops_CSRGR->_hoops_RPCI != _hoops_CCP->_hoops_CPA) {
		_hoops_CSRGR->_hoops_RPCI = _hoops_CCP->_hoops_CPA;

		if ((_hoops_CCP->_hoops_AGP != null
			&& BIT (nr->_hoops_RGP, T_LIGHTS_FOR_MARKERS))
			|| _hoops_CCP->_hoops_CHA->_hoops_IRIR != 1.0f ||
			pm->_hoops_RGIA != null) {
				if (_hoops_CCP->_hoops_AGP != null
					&& BIT (nr->_hoops_RGP, T_LIGHTS_FOR_MARKERS)) {
						_hoops_GIGRC (_hoops_CSRGR, nr, _hoops_CCP->_hoops_AGP);
				}
				else {
					_hoops_SCIGC (_hoops_CSRGR);
				}

				if (pm->_hoops_HCHA)
					OGL_SET_TEXTURE_INDEXED_MATERIAL (_hoops_CSRGR, nr, _hoops_CCP->_hoops_CHA);
				else
					OGL_SET_MATERIAL (_hoops_CSRGR, nr, _hoops_CCP->_hoops_CHA, 0, 0);
		}
		else {
			_hoops_SCIGC (_hoops_CSRGR);

			if (pm->_hoops_HCHA || pm->_hoops_RGIA)
				FORCE_COLOR_4F(1, 1, 1, _hoops_CCP->_hoops_CHA->_hoops_IRIR, _hoops_CRSPH);
			else
				FORCE_COLOR (_hoops_CSRGR, &_hoops_CCP->color, _hoops_CRSPH);
			_hoops_ICGRC(_hoops_CSRGR);
		}
		ENSURE_SHADE_MODEL (_hoops_CSRGR, GL_FLAT);
	}
	if (pm->_hoops_GPPPI) {
		/* _hoops_SR _hoops_PAH _hoops_ARP _hoops_RH _hoops_HAIR _hoops_ARR _hoops_PPR _hoops_PSCR _hoops_HPRAR _hoops_CRGR _hoops_RH _hoops_ARACP _hoops_AGIR */
		if (_hoops_PCHA != null) {
			/* _hoops_SGH _hoops_CIHA _hoops_IIGR _hoops_SRS _hoops_PPSR */
			if (_hoops_AIHA)
				_hoops_IPCRC (_hoops_RIHRC, (float const *) &_hoops_PCHA[_hoops_AIHA[0]]);
			else
				_hoops_IPCRC (_hoops_RIHRC, (float const *) &_hoops_PCHA[0]);
			_hoops_CSRGR->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR;
			_hoops_PCHA = null;
			_hoops_ICGRC(_hoops_CSRGR);
		}
	}

	if (_hoops_CAPA != null) {
		while (_hoops_CAPA != null) {
			_hoops_HGCGC (_hoops_CSRGR, _hoops_CAPA->_hoops_APPA);
			_hoops_CPCRC (nr, pm, size, _hoops_PHSC, _hoops_RIHRC, _hoops_CACRC, 0, pm->length, _hoops_RRIRC);
			_hoops_CAPA = _hoops_CAPA->next;
		}
	}
	else
		_hoops_CPCRC (nr, pm, size, _hoops_PHSC, _hoops_RIHRC, _hoops_CACRC, 0, pm->length, _hoops_RRIRC);

	if (_hoops_AACRC != OGL_GLYPH_DOT) {
		_hoops_GPPRC (_hoops_CSRGR, 1);
		_hoops_AAPRC (_hoops_CSRGR, false);
		if (_hoops_CCP->_hoops_HHP == _hoops_SPSC &&
			_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH &&
			_hoops_CSRGR->_hoops_HPPGC) {
				GLfloat _hoops_GSAAR[3] = { 1, 0, 0 };
				_hoops_CSRGR->_hoops_CPPGC(GL_DISTANCE_ATTENUATION_EXT, _hoops_GSAAR);
		}
		if (_hoops_PHSC)
			FREE (_hoops_PHSC, _hoops_HRPA);
	}
  done:
	_hoops_AARRC(_hoops_CSRGR, 0);
}


/*****************************************************************************
 *****************************************************************************
							_hoops_HRRAH
 _hoops_AGCR _hoops_PSCH _hoops_CHR _hoops_SIGR _hoops_IH 3d _hoops_IAGIP _hoops_PPR 2d _hoops_GACC...
 *****************************************************************************
 *****************************************************************************/


#define _hoops_HICRC 0
#if _hoops_HICRC
local void
_hoops_IICRC (
	Net_Rendition const & nr,
	const char * name,
	void alter * image,
	void alter * z)
{
	static long int _hoops_CICRC=0;
	_hoops_SICRC *_hoops_PARAH = (_hoops_SICRC *) image;
	_hoops_SICRC *_hoops_GCCRC = (_hoops_SICRC *) z;
	GLint l, b, w, h;
	char _hoops_RCCRC[4096];

	if (_hoops_PARAH) {
		l = _hoops_PARAH->_hoops_ACCRC.left;
		b = _hoops_PARAH->_hoops_ACCRC.bottom;
		w = _hoops_PARAH->_hoops_ACCRC.right - _hoops_PARAH->_hoops_ACCRC.left;
		h = _hoops_PARAH->_hoops_ACCRC.top - _hoops_PARAH->_hoops_ACCRC.bottom;
	}
	else {
		l = _hoops_GCCRC->_hoops_ACCRC.left;
		b = _hoops_GCCRC->_hoops_ACCRC.bottom;
		w = _hoops_GCCRC->_hoops_ACCRC.right - _hoops_GCCRC->_hoops_ACCRC.left;
		h = _hoops_GCCRC->_hoops_ACCRC.top - _hoops_GCCRC->_hoops_ACCRC.bottom;
	}

	if (_hoops_PARAH) {
		FILE * file;
		int x,y;

		sprintf(_hoops_RCCRC,"%s_%ld_c.hmf",name,_hoops_CICRC);
		file = fopen(_hoops_RCCRC, "wb");
		fprintf(file,";; HMF V1.24 TEXT\n");
		fprintf(file,"(Image 0 0 0 \"rgba, name=%s\" (\n", _hoops_RCCRC);

		for (y=b+h;y>=b;y--) {
			fprintf(file,"(");
			for (x=l;x<=l+w;x++) {
				int index = (y*(w+1)+x)*4;
				unsigned char _hoops_PIAGI = ((unsigned char*)_hoops_PARAH->buffer)[index+0];
				unsigned char _hoops_RSIGH = ((unsigned char*)_hoops_PARAH->buffer)[index+1];
				unsigned char _hoops_HIAGI = ((unsigned char*)_hoops_PARAH->buffer)[index+2];
				unsigned char _hoops_IIAGI = ((unsigned char*)_hoops_PARAH->buffer)[index+3];
				fprintf(file,"%d %d %d %d ", _hoops_PIAGI, _hoops_RSIGH, _hoops_HIAGI, _hoops_IIAGI);
				if (x%3 == 0) fprintf(file,"\n");
			}
			fprintf(file,")\n");
		}
		fprintf(file,"))");
		fclose(file);
	}
	if (_hoops_GCCRC) {
		FILE * file;
		int x,y;

		sprintf(_hoops_RCCRC,"%s_%ld_z.hmf",name,_hoops_CICRC);
		file = fopen(_hoops_RCCRC, "wb");
		fprintf(file,";; HMF V1.24 TEXT\n");
		fprintf(file,"(Image 0 0 0 \"rgb, name=%s\" (\n", _hoops_RCCRC);

		for (y=b+h;y>=b;y--) {
			fprintf(file,"(");
			for (x=l;x<=l+w;x++) {
				int index = y*(w+1)+x;
				int value = (int)(((float*)_hoops_GCCRC->buffer)[index] * 255.0f);
				fprintf(file,"%d %d %d ", value, value, value);
				if (x%3 == 0) fprintf(file,"\n");
			}
			fprintf(file,")\n");
		}
		fprintf(file,"))");
		fclose(file);
	}
	_hoops_CICRC++;
}

local void _hoops_PCCRC(
	Net_Rendition const & nr,
	const char * name,
	_hoops_SICRC *_hoops_PARAH,
	_hoops_SICRC *_hoops_GCCRC) {

	_hoops_SICRC *_hoops_HCCRC = 0;
	_hoops_SICRC *_hoops_ICCRC = 0;

	/* _hoops_AGCR _hoops_CHR _hoops_CPHR _hoops_CCCRC _hoops_IS _hoops_RPGP _hoops_SCCRC*/
	if (_hoops_PARAH)
		create_region(nr, &_hoops_PARAH->_hoops_ACCRC, (void **)&_hoops_HCCRC, 0);
	if (_hoops_GCCRC)
		create_region(nr, &_hoops_GCCRC->_hoops_ACCRC, 0, (void **)&_hoops_ICCRC);

	_hoops_HIPGR (nr, 0, _hoops_HCCRC, _hoops_ICCRC);

	_hoops_IICRC(nr,name,_hoops_HCCRC,_hoops_ICCRC);

	if (_hoops_HCCRC)
		_hoops_ISPGR(nr, _hoops_HCCRC, 0);
	if (_hoops_ICCRC)
		_hoops_ISPGR(nr, 0, _hoops_ICCRC);
}
#else
#define _hoops_IICRC(nr,name,image,z)
#define _hoops_PCCRC(nr,name,_hoops_PARAH,_hoops_GCCRC)
#endif

/*
 * _hoops_SRAC
 * _hoops_RPP _hoops_GHGPR _hoops_RHGPR, _hoops_RGR _hoops_PIHA _hoops_SHH _hoops_PIGS _hoops_ARPP _hoops_RH _hoops_GGSHR _hoops_PSCA
 */
local bool
snapshot(
	Net_Rendition const & nr,
	int width,
	int height,
	unsigned char * data) {

	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	Int_Rectangle const * area = &nr->_hoops_SAIR->_hoops_SCIH;
	GLint w,h;
	int x,y,index;
	unsigned char * _hoops_IGHSI;

#ifdef GLX_DRIVER
	bool _hoops_GSCRC = false;
	if (!glXGetCurrentContext()) {
		if (glXMakeCurrent (_hoops_CSRGR->display, _hoops_CSRGR->window, _hoops_CSRGR->context) == GL_FALSE) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "glXMakeCurrent failed for snapshot.");
			return false;
		}
		_hoops_GSCRC = true;
	}
#endif
#ifdef WGL_DRIVER
	bool _hoops_GSCRC = false;
	if (!wglGetCurrentContext()) {
		if (wglMakeCurrent (_hoops_CSRGR->hDC, _hoops_CSRGR->hGLRC) == GL_FALSE) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "wglMakeCurrent failed for snapshot.");
			return false;
		}
		_hoops_GSCRC = true;
	}
#endif

	w = area->right - area->left + 1;
	h = area->top - area->bottom + 1;

	if (w*h > width*height) return false;

	/* _hoops_SRGC _hoops_CPAP _hoops_IS _hoops_HCHSR _hoops_PSCA _hoops_ARPP _hoops_GPS */
	glFlush ();

	ALLOC_ARRAY(_hoops_IGHSI, w*h*3, unsigned char);

	if (_hoops_CSRGR->_hoops_SRRRR)
		glReadBuffer(GL_BACK);
	else
		glReadBuffer(GL_FRONT);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glReadPixels (0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, (void *)_hoops_IGHSI);

	for (y=h-1;y>=0;y--) {
		for (x=0;x<w;x++) {
			index=(y*w+x)*3;
			*data++ = (unsigned char)_hoops_IGHSI[index+0];
			*data++ = (unsigned char)_hoops_IGHSI[index+1];
			*data++ = (unsigned char)_hoops_IGHSI[index+2];
		}
	}

	FREE_ARRAY(_hoops_IGHSI, w*h*3, unsigned char);

#ifdef GLX_DRIVER
	if (_hoops_GSCRC)
		glXMakeCurrent(_hoops_CSRGR->display, 0, 0);
#endif
#ifdef WGL_DRIVER
	if (_hoops_GSCRC)
		wglMakeCurrent (0, 0);
#endif

	return true;
}


local int _hoops_RSCRC (OGLData *_hoops_CSRGR)
{
	GLint _hoops_ASCRC = 0;
	GLuint _hoops_SISGC, _hoops_GCSGC;
	const char *_hoops_PSCRC;

	/* _hoops_PSHR _hoops_GAR _hoops_HSCRC, _hoops_HIH _hoops_CCA _hoops_RH _hoops_HPRGR _hoops_ISCRC _hoops_RIIA _hoops_IIGR _hoops_RH _hoops_SPR
       _hoops_CHIA _hoops_GAR _hoops_ARIP _hoops_IIGR _hoops_CSCRC */
	if (_hoops_CSRGR->_hoops_AIPGA > 1)
		_hoops_PSCRC =
			"uniform sampler2D depth_sampler; \n"
			"void main() { \n"
			"	vec4 tmp = texture2D(depth_sampler, gl_TexCoord[0].xy); \n"
			"	gl_FragDepth = tmp.r + 0.001; \n"
			"} \n";
	else
		_hoops_PSCRC =
			"uniform sampler2D depth_sampler; \n"
			"void main() { \n"
			"	vec4 tmp = texture2D(depth_sampler, gl_TexCoord[0].xy); \n"
			"	gl_FragDepth = tmp.r; \n"
			"} \n";


	  /* _hoops_ARP _hoops_GH _hoops_RH _hoops_RRAA-_hoops_IIHA _hoops_CI */
	_hoops_SISGC = (*_hoops_CSRGR->glCreateProgramObjectARB)();
	_hoops_GCSGC = (*_hoops_CSRGR->glCreateShaderObjectARB) (GL_FRAGMENT_SHADER_ARB);
	(*_hoops_CSRGR->glShaderSourceARB)(_hoops_GCSGC, 1, &_hoops_PSCRC, null);
	(*_hoops_CSRGR->glCompileShaderARB)(_hoops_GCSGC);
	(*_hoops_CSRGR->glGetObjectParameterivARB) (_hoops_GCSGC, GL_OBJECT_COMPILE_STATUS_ARB, &_hoops_ASCRC);
	_hoops_CSRGR->_hoops_SSCRC = _hoops_SISGC;
	_hoops_CSRGR->_hoops_GGSRC = _hoops_GCSGC;
	return _hoops_ASCRC;
}


local int _hoops_RGSRC (OGLData *_hoops_CSRGR)
{
	GLuint _hoops_SISGC, _hoops_GCSGC;
	GLint _hoops_ASCRC = 0;
	char buffer[4096];
	GLsizei length;
	int _hoops_GAHGC = OGLR_DEPTH_TEXTURE_RECT;
	const char *_hoops_AGSRC;

	/* _hoops_IRS _hoops_CPPPR _hoops_IHGP _hoops_SPPPR _hoops_SGS _hoops_PGSRC _hoops_RH _hoops_HCH _hoops_PIRA _hoops_HII _hoops_IRS _hoops_HH _hoops_IS _hoops_RH
	   _hoops_IIPR _hoops_HCH (_hoops_PGAP _hoops_CHH _hoops_HCAGR _hoops_SHH _hoops_RAGA _hoops_RH _hoops_HCH _hoops_PIRA _hoops_IIGR _hoops_RH _hoops_HSSP) */
	if (_hoops_CSRGR->_hoops_AIPGA > 1)
		//_hoops_HGSRC _hoops_GCA _hoops_IRS _hoops_HCH _hoops_CHAA
		_hoops_AGSRC =
			"uniform sampler2DRect depth_sampler; \n"
			"void main() { \n"
			"	vec4 tmp = texture2DRect(depth_sampler, gl_TexCoord[0].xy); \n"
			"	gl_FragDepth = tmp.r + 0.001; \n"
			"} \n";
	else
		_hoops_AGSRC =
			"uniform sampler2DRect depth_sampler; \n"
			"void main() { \n"
			"	vec4 tmp = texture2DRect(depth_sampler, gl_TexCoord[0].xy); \n"
			"	gl_FragDepth = tmp.r; \n"
			"} \n";

	_hoops_SISGC = (*_hoops_CSRGR->glCreateProgramObjectARB)();
	_hoops_GCSGC = (*_hoops_CSRGR->glCreateShaderObjectARB) (GL_FRAGMENT_SHADER_ARB);
	glEnable (GL_TEXTURE_RECTANGLE_ARB);
	(*_hoops_CSRGR->glShaderSourceARB)(_hoops_GCSGC, 1, &_hoops_AGSRC, null);
	(*_hoops_CSRGR->glCompileShaderARB)(_hoops_GCSGC);
	glDisable (GL_TEXTURE_RECTANGLE_ARB);
	(*_hoops_CSRGR->glGetObjectParameterivARB) (_hoops_GCSGC, GL_OBJECT_COMPILE_STATUS_ARB, &_hoops_ASCRC);

	/* _hoops_HHH _hoops_RSIH _hoops_IRSP _hoops_IIGR _hoops_CCPGC _hoops_SARS'_hoops_RA _hoops_GCGH _hoops_IGSRC, _hoops_HIS _hoops_SR _hoops_HS _hoops_IS
	   _hoops_HSSC _hoops_ISSC _hoops_IS _hoops_RH _hoops_RSAHH _hoops_SGS _hoops_CSAP _hoops_IIHA _hoops_GPP _hoops_RRAA _hoops_AI */
	if (!_hoops_ASCRC) {
		  /* _hoops_CASI _hoops_GH _hoops_RH _hoops_IIPSI-_hoops_IIHA _hoops_CI */
		(*_hoops_CSRGR->_hoops_PSPGC) (_hoops_CSRGR->_hoops_SISGC, _hoops_CSRGR->_hoops_GCSGC);
		(*_hoops_CSRGR->glDeleteShaderARB) (_hoops_CSRGR->_hoops_GCSGC);
		(*_hoops_CSRGR->glDeleteProgramARB) (_hoops_CSRGR->_hoops_SISGC);

		  /* _hoops_ARP _hoops_GH _hoops_RH _hoops_RRAA-_hoops_IIHA _hoops_CI */
		_hoops_ASCRC = _hoops_RSCRC (_hoops_CSRGR);
		_hoops_SISGC = _hoops_CSRGR->_hoops_SSCRC;
		_hoops_GCSGC = _hoops_CSRGR->_hoops_GGSRC;
		_hoops_GAHGC = OGLR_DEPTH_TEXTURE_SQUARE;
	}

	(*_hoops_CSRGR->glAttachObjectARB) (_hoops_SISGC, _hoops_GCSGC);
	(*_hoops_CSRGR->glLinkProgramARB) (_hoops_SISGC);
	if (!_hoops_ASCRC) {
		(*_hoops_CSRGR->glGetInfoLogARB) (_hoops_GCSGC, sizeof(buffer), &length, buffer);
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
			Sprintf_S (null, "shader compilation error reported by opengl:\n%S", buffer));
	}
	_hoops_CSRGR->_hoops_SISGC = _hoops_SISGC;
	_hoops_CSRGR->_hoops_GCSGC = _hoops_GCSGC;
	return _hoops_GAHGC;
}

/* _hoops_HGI _hoops_API _hoops_HRGR _hoops_SIGR _hoops_IS _hoops_HGCR _hoops_RH _hoops_RPHR _hoops_PRGIA _hoops_RSGA _hoops_CRGR _hoops_IRS _hoops_CGSRC
	_hoops_GGSC _hoops_SIHH _hoops_SGSRC _hoops_RH _hoops_PIAP _hoops_IIGR _hoops_HGPGA. */
local void _hoops_GRSRC(int w, int h, float _hoops_PCHH, OGLData *_hoops_CSRGR)
{
	float matrix[16];

	matrix[0] = (GLfloat) (2.0 / w);
	matrix[1] = (GLfloat) 0;
	matrix[2] = (GLfloat) 0;
	matrix[3] = (GLfloat) 0;
	matrix[4] = (GLfloat) 0;
	matrix[5] = (GLfloat) (2.0 / h);
	matrix[6] = (GLfloat) 0;
	matrix[7] = (GLfloat) 0;
	matrix[8] = (GLfloat) 0;
	matrix[9] = (GLfloat) 0;
	matrix[10] = (GLfloat) (2.0 / _hoops_PCHH);
	matrix[11] = (GLfloat) 0;
	matrix[12] = (GLfloat) - 1;
	matrix[13] = (GLfloat) - 1;
	matrix[14] = (GLfloat) - 1;
	matrix[15] = (GLfloat) 1;
	glLoadMatrixf (matrix);
	UNREFERENCED (_hoops_CSRGR);
}


/*
 * _hoops_SRAC
 */
local void
_hoops_CGAGR (Display_Context const *dc, void *list)
{
	OGL_Display_List alter * odl = (OGL_Display_List alter*)list;
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	Image alter *image = (Image alter *)odl->_hoops_PPAH->owner;
	int w = image->width;
	int h = image->height;

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	if (image->format == _hoops_PCCRH) {			
		if (image->_hoops_PHGH == null)
			ALLOC_ARRAY (image->_hoops_PHGH, w*h, float);
		_hoops_IPRGC(_hoops_CSRGR, 0, GL_TEXTURE_2D, odl->item.texture.id);
		glGetTexImage (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, GL_FLOAT, (unsigned char *)image->_hoops_PHGH);
		_hoops_IPRGC(_hoops_CSRGR, 0, GL_TEXTURE_2D, 0);
	}
	else if (image->format == _hoops_AHGH) {
		if (image->_hoops_PHGH == null)
			ALLOC_ARRAY (image->_hoops_PHGH, w*h, unsigned char);
		_hoops_IPRGC(_hoops_CSRGR, 0, GL_TEXTURE_2D, odl->item.texture.id);
		glGetTexImage (GL_TEXTURE_2D, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, (unsigned char *)image->_hoops_PHGH);
		_hoops_IPRGC(_hoops_CSRGR, 0, GL_TEXTURE_2D, 0);
	}
	else if (image->format == _hoops_HHGH) {
		if (image->_hoops_PHGH == null)
			ALLOC_ARRAY (image->_hoops_PHGH, 3*w*h, unsigned char);
		_hoops_IPRGC(_hoops_CSRGR, 0, GL_TEXTURE_2D, odl->item.texture.id);
		glGetTexImage (GL_TEXTURE_2D, 0,GL_RGB, GL_UNSIGNED_BYTE, (unsigned char *)image->_hoops_PHGH);
		_hoops_IPRGC(_hoops_CSRGR, 0, GL_TEXTURE_2D, 0);
	}
	else if (image->format == Image_RGBA32) {		
		if (image->_hoops_PHGH == null)
			ALLOC_ARRAY (image->_hoops_PHGH, 4*w*h, unsigned char);
		_hoops_IPRGC(_hoops_CSRGR, 0, GL_TEXTURE_2D, odl->item.texture.id);
		glGetTexImage (GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char *)image->_hoops_PHGH);
		_hoops_IPRGC(_hoops_CSRGR, 0, GL_TEXTURE_2D, 0);
	}
	else {
		HE_ERROR (0, 0, "unrecognized image format in show_image_data()");
		return;
	}

	if (image->rasters == null) {
		ALLOC_ARRAY (image->rasters, image->height, void const *);
		void **_hoops_RARAH = (void **)image->rasters;
		for (int i = 0 ; i < image->height ; i++) {
			_hoops_RARAH[i] = &((unsigned char *)image->_hoops_PHGH)[image->row_bytes*i];
		}
	}
	image->flags &= ~(_hoops_GRRH|_hoops_APAH);
}


/*
 * _hoops_SRAC
 * _hoops_HSSIA _hoops_PPGS _hoops_IH _hoops_SRGIA _hoops_HHH _hoops_CSCR _hoops_PIH.
 * _hoops_HRS _hoops_PSCA _hoops_GGR _hoops_RH _hoops_SRSGR _hoops_IIGR _hoops_CSCR _hoops_PPR _hoops_PPR/_hoops_PAR _hoops_IARAH
 * _hoops_HRS _hoops_IRAP _hoops_IH _hoops_CARAH _hoops_RPP _hoops_SSH-_hoops_RHGPR _hoops_HRGR _hoops_IHPPP _hoops_PSAP
 */
local void
create_region (
	Net_Rendition const & nr,
	Int_Rectangle const * area,
	void **image,
	void **z)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_SICRC *_hoops_PARAH = null;
	_hoops_SICRC *_hoops_GCCRC = null;
	bool _hoops_RRSRC;
	int type; /* _hoops_CGH _hoops_SHH _hoops_ARSRC */
	_hoops_GSPGR	_hoops_RSPGR, _hoops_ASPGR;

	_hoops_RAPRC("create_region", true);

	_hoops_RSPGR = HI_What_Time();

	if (!area)
		area = &nr->_hoops_SAIR->_hoops_SCIH;

	/* _hoops_IRHH _hoops_IRS _hoops_PRSRC _hoops_AHCA _hoops_PCPA _hoops_IAHA _hoops_IIGR _hoops_ASAC/_hoops_PHIH _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_SHH _hoops_GRP */
	type = OGLR_FIRST_METHOD;
#if 0
	type = OGLR_DRAW_PIXELS;
#endif
	do {
		_hoops_RRSRC = false;
		switch (type) {
			case OGLR_DEPTH_TEXTURE_RECT:
				if (!_hoops_CSRGR->_hoops_PPPGC)
					_hoops_RRSRC = true;
				if (area->right - area->left < 1 ||
                    area->top - area->bottom < 1)
                    _hoops_RRSRC = true;
				_hoops_HHHI;
			case OGLR_DEPTH_TEXTURE_SQUARE:
				if (_hoops_CSRGR->_hoops_GSGRR)
					_hoops_RRSRC = true;
				if (z) {
					if (!_hoops_CSRGR->_hoops_GGHGC)
						_hoops_RRSRC = true;
					if (_hoops_CSRGR->_hoops_AIPGA > 1 &&
						XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_SLOW_MSAA_DEPTH_TEXTURE))
						_hoops_RRSRC = true;
				}
				break;
			case OGLR_KTX_BUFFER_REGION:
				if (_hoops_CSRGR->_hoops_HRSRC)
					_hoops_RRSRC = true;
				if (!_hoops_CSRGR->_hoops_ACPGC)
					_hoops_RRSRC = true;
				break;
			case OGLR_WGL_ARB_BUFFER:
				if (_hoops_CSRGR->_hoops_HRSRC)
					_hoops_RRSRC = true;
				if (!_hoops_CSRGR->_hoops_RAHGC)
					_hoops_RRSRC = true;
				if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_WGL_ARB_BUFFER_1024_LIMIT) &&
					area->right - area->left >= 1023)
					_hoops_RRSRC = true;
				if (_hoops_CSRGR->_hoops_AIPGA > 1 &&
					XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_MSAA_WGL_ARB_BUFFER))
					_hoops_RRSRC = true;
				break;
			case OGLR_MAKE_CONTEXT_CURRENT:
				if (!image)
					_hoops_RRSRC = true;
				if (!_hoops_CSRGR->_hoops_AAHGC || !_hoops_CSRGR->_hoops_PAHGC)
					_hoops_RRSRC = true;
			break;

			case OGLR_DRAW_PIXELS:
			default:
				break;
		}
		if (_hoops_RRSRC)
			type++; /* _hoops_HSSC _hoops_ISSC _hoops_IS _hoops_RH _hoops_SPS _hoops_AAH */
	} while (_hoops_RRSRC);

	switch (type) {
		case OGLR_DEPTH_TEXTURE_RECT:
		case OGLR_DEPTH_TEXTURE_SQUARE: {
			int w = area->right - area->left + 1;
			int h = area->top - area->bottom + 1;
			GLenum _hoops_IRSRC;
			GLuint *buffer = null;
			int _hoops_CRSRC = 512;

			if (!_hoops_CSRGR->_hoops_SISGC && _hoops_CSRGR->_hoops_GGHGC) {
				/* _hoops_ISCP _hoops_SRSRC _hoops_PAH _hoops_AGRP _hoops_HII _hoops_GACRH _hoops_IS _hoops_GASRC _hoops_ARI */
				_hoops_CSRGR->_hoops_GAHGC = type = (_hoops_RASRC)_hoops_RGSRC (_hoops_CSRGR);
			}

			if (type == OGLR_DEPTH_TEXTURE_RECT) {
			    ALLOC_ARRAY (buffer, w*h, GLuint);
				_hoops_IRSRC = GL_TEXTURE_RECTANGLE_ARB;
			}
			else {
			    while (_hoops_CRSRC < w || _hoops_CRSRC < h)
				    _hoops_CRSRC = _hoops_CRSRC << 1;
				w = h = _hoops_CRSRC;
				_hoops_IRSRC = GL_TEXTURE_2D;
			}
			glEnable (_hoops_IRSRC);
			if (image) {
				ALLOC(_hoops_PARAH, _hoops_SICRC);
				ZERO_STRUCT (_hoops_PARAH, _hoops_SICRC);
				glGenTextures(1, &_hoops_PARAH->id);
				_hoops_IPRGC(_hoops_CSRGR, 0, _hoops_IRSRC, _hoops_PARAH->id);
				glTexImage2D (_hoops_IRSRC, 0, GL_RGBA8,
						w, h, 0,
						GL_RGBA, GL_UNSIGNED_BYTE, buffer);
				_hoops_GPRH(_hoops_RPRH)++;
				glTexParameteri (_hoops_IRSRC, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri (_hoops_IRSRC, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				_hoops_PARAH->size = _hoops_CRSRC; /* _hoops_PPRAR _hoops_RPP _hoops_GACRH */
				*image = _hoops_PARAH;
			}
			if (z) {
			    GLuint _hoops_AASRC;
				ALLOC(_hoops_GCCRC, _hoops_SICRC);
				ZERO_STRUCT(_hoops_GCCRC, _hoops_SICRC);
			    if (_hoops_CSRGR->_hoops_IGARR == 16)
				    _hoops_AASRC = GL_DEPTH_COMPONENT16_ARB;
			    else
				    _hoops_AASRC = GL_DEPTH_COMPONENT24_ARB;
			    glGenTextures(1, &_hoops_GCCRC->id);
			    _hoops_IPRGC(_hoops_CSRGR, 0, _hoops_IRSRC,_hoops_GCCRC->id);
			    glTexImage2D (_hoops_IRSRC, 0, _hoops_AASRC, w, h, 0,
				      GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, buffer);
				_hoops_GPRH(_hoops_RPRH)++;
			    glTexParameteri (_hoops_IRSRC, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			    glTexParameteri (_hoops_IRSRC, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			    glTexParameteri (_hoops_IRSRC, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			    glTexParameteri (_hoops_IRSRC, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				_hoops_GCCRC->size = _hoops_CRSRC; /* _hoops_PPRAR _hoops_RPP _hoops_GACRH */
				*z = _hoops_GCCRC;
			}
			glDisable (_hoops_IRSRC);
			if (buffer)
				FREE_ARRAY (buffer, w*h, GLuint);

		} break;

#ifdef WGL_DRIVER
		case OGLR_MAKE_CONTEXT_CURRENT: {
			_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;
			int w = area->right - area->left + 1;
			int h = area->top - area->bottom + 1;
			int format = GetPixelFormat(_hoops_CSRGR->hDC); /* _hoops_SAHR _hoops_SGH _hoops_RH _hoops_PSHR _hoops_RPCC _hoops_GAR _hoops_GPP-_hoops_SHPR */
			int _hoops_PASRC[] = { 0 };

			ALLOC(_hoops_PARAH, _hoops_SICRC);
			ZERO_STRUCT (_hoops_PARAH, _hoops_SICRC);
			_hoops_PARAH->pbuffer = _hoops_CSRGR->wglCreatePbufferARB(_hoops_CSRGR->hDC, format, w, h, _hoops_PASRC);
			_hoops_PARAH->hDC = _hoops_CSRGR->wglGetPbufferDCARB(_hoops_PARAH->pbuffer);
			/* _hoops_RIIA _hoops_IIGR _hoops_SGP _hoops_IRS _hoops_CCAH _hoops_GGSC, _hoops_PII:	 _hoops_HASRC->_hoops_IASRC = _hoops_CASRC(_hoops_HASRC->_hoops_SASRC);
			   _hoops_HS _hoops_RH _hoops_HASRC _hoops_HSSRR _hoops_IRS _hoops_GGSC _hoops_CCA _hoops_RH _hoops_HGSI _hoops_AGPGI */
			_hoops_PARAH->hGLRC = _hoops_CSRGR->hGLRC;
_hoops_PARAH->hGLRC = wglCreateContext(_hoops_PARAH->hDC); /* _hoops_PHHR _hoops_ISSC _hoops_IS _hoops_RH _hoops_RHGS _hoops_PPRRR _hoops_IH _hoops_HA, _hoops_CCGR _hoops_SR _hoops_CAHA _hoops_GGSR _hoops_PCPA _hoops_RH _hoops_GPSRC _hoops_HRGR _hoops_CPIC _hoops_GPP */
			wglMakeCurrent (_hoops_PARAH->hDC, _hoops_PARAH->hGLRC);
			_hoops_RPSRC(_hoops_CSRGR);
			ENSURE_DEPTH_MASK (_hoops_CSRGR, !BIT(nr->transform_rendition->flags, _hoops_ISH));
			glMatrixMode (GL_PROJECTION);
			_hoops_GRSRC(w-1, h-1, _hoops_IHCR->_hoops_PCHH, _hoops_CSRGR);
			glMatrixMode (GL_MODELVIEW);
			if (_hoops_CSRGR->_hoops_APSRC)
				wglMakeCurrent (_hoops_CSRGR->_hoops_HIISI, _hoops_CSRGR->hGLRC);
			else
				wglMakeCurrent (_hoops_CSRGR->hDC, _hoops_CSRGR->hGLRC);
			if (image) {
				*image = _hoops_PARAH;
			}
			if (z) {
				ALLOC(_hoops_GCCRC, _hoops_SICRC);
				ZERO_STRUCT(_hoops_GCCRC, _hoops_SICRC);
				if (type == OGLR_MAKE_CONTEXT_CURRENT) {
					/* _hoops_RISCP _hoops_PSCA _hoops_RIIA _hoops_IIGR _hoops_CGSRC _hoops_SSH */
					float *_hoops_PPSRC;
					int _hoops_HPSRC = w * h;

					ALLOC_ARRAY(_hoops_PPSRC, _hoops_HPSRC, float);
					_hoops_GCCRC->buffer = (void *) _hoops_PPSRC;
					_hoops_GCCRC->size = _hoops_HPSRC * 4;
					*z = _hoops_GCCRC;
				}
				else {
					glGenTextures(1,&_hoops_GCCRC->id);
					_hoops_GCCRC->size = w;
				}
			}
		} break;

		case OGLR_WGL_ARB_BUFFER: {
			/*_hoops_IPSRC _hoops_RCIC & _hoops_CPSP = _hoops_SCII->_hoops_RICC;*/
			UINT _hoops_CPSRC;

			ZALLOC(_hoops_PARAH, _hoops_SICRC);
			_hoops_RSAI (area, Int_Rectangle, &_hoops_PARAH->_hoops_ACCRC);
			if (_hoops_CSRGR->_hoops_SRRRR)
				_hoops_CPSRC = WGL_BACK_COLOR_BUFFER_BIT_ARB;
			else
				_hoops_CPSRC = WGL_FRONT_COLOR_BUFFER_BIT_ARB;

			if (z)
				_hoops_CPSRC |= WGL_DEPTH_BUFFER_BIT_ARB;

			_hoops_PARAH->handle = (_hoops_CSRGR->wglCreateBufferRegionARB) (_hoops_CSRGR->hDC, 0, _hoops_CPSRC);
			if (image)
				*image = _hoops_PARAH;
			if (z)
				*z = _hoops_PARAH;
			_hoops_CSRGR->_hoops_HRSRC = true;
		} break;
#else
		case OGLR_MAKE_CONTEXT_CURRENT:
		case OGLR_WGL_ARB_BUFFER:
			break;
#endif
		case OGLR_KTX_BUFFER_REGION: {
			if (image) {
				ZALLOC(_hoops_PARAH, _hoops_SICRC);
				if (_hoops_CSRGR->_hoops_SRRRR)
					_hoops_PARAH->id = (*_hoops_CSRGR->glNewKTXBufferRegion) (GL_KTX_BACK_REGION);
				else
					_hoops_PARAH->id = (*_hoops_CSRGR->glNewKTXBufferRegion) (GL_KTX_FRONT_REGION);
				*image = _hoops_PARAH;
			}
			if (z) {
				ZALLOC(_hoops_GCCRC, _hoops_SICRC);
				_hoops_GCCRC->id = (*_hoops_CSRGR->glNewKTXBufferRegion) (GL_KTX_Z_REGION);
				*z = _hoops_GCCRC;
			}
			_hoops_CSRGR->_hoops_HRSRC = true;
		} break;

		case OGLR_DRAW_PIXELS: {
			char * _hoops_IGHSI;
			float * _hoops_PPSRC;
			int w = area->right - area->left + 1;
			int h = area->top - area->bottom + 1;
			int _hoops_HPSRC = w * h;

			if (image) {
				ZALLOC(_hoops_PARAH, _hoops_SICRC);
				ALLOC_ARRAY(_hoops_IGHSI, _hoops_HPSRC*4, char);
				_hoops_PARAH->buffer = (void *) _hoops_IGHSI;
				_hoops_PARAH->size = _hoops_HPSRC * 4;
				*image = _hoops_PARAH;
			}

			if (z) {
				ZALLOC(_hoops_GCCRC, _hoops_SICRC);
				ALLOC_ARRAY(_hoops_PPSRC, _hoops_HPSRC, float);
				_hoops_GCCRC->buffer = (void *) _hoops_PPSRC;
				_hoops_GCCRC->size = _hoops_HPSRC;
				*z = _hoops_GCCRC;
			}
		} break;

		default:
			break;
	}
	if (_hoops_PARAH) {
		_hoops_PARAH->type = (_hoops_RASRC)type;
		_hoops_RSAI (area, Int_Rectangle, &_hoops_PARAH->_hoops_ACCRC);
	}
	if (_hoops_GCCRC) {
		_hoops_GCCRC->type = (_hoops_RASRC)type;
		_hoops_RSAI (area, Int_Rectangle, &_hoops_GCCRC->_hoops_ACCRC);
	}

	_hoops_ASPGR = HI_What_Time();
	_hoops_GPRH(_hoops_PSPGR) += (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}/* _hoops_RSGR _hoops_API _hoops_HARAH */


/*
 * _hoops_SRAC
 * _hoops_PHRAH
 */
local void
_hoops_ISPGR (Net_Rendition const & nr,
				void alter * image, void alter * z) {
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_SICRC *_hoops_PARAH = (_hoops_SICRC *) image;
	_hoops_SICRC *_hoops_GCCRC = (_hoops_SICRC *) z;
	_hoops_RASRC type;
	_hoops_GSPGR	_hoops_RSPGR, _hoops_ASPGR;

	_hoops_RAPRC("destroy_region", true);

	_hoops_RSPGR = HI_What_Time();

	if (_hoops_PARAH && _hoops_GCCRC &&
		_hoops_PARAH->type != _hoops_GCCRC->type) {
		_hoops_ISPGR (nr, image, null);
		_hoops_PARAH = null;
	}
	type = (_hoops_PARAH ? _hoops_PARAH->type : _hoops_GCCRC->type);

	switch (type) {
		case OGLR_DEPTH_TEXTURE_RECT:
		case OGLR_DEPTH_TEXTURE_SQUARE: {
			if (type == OGLR_DEPTH_TEXTURE_RECT) {
				_hoops_PPRGC (_hoops_CSRGR, 0);
				if (_hoops_PARAH && _hoops_PARAH->id) {
				    glDeleteTextures (1, &_hoops_PARAH->id);
				}
				if (_hoops_GCCRC && _hoops_GCCRC->id) {
				    glDeleteTextures (1, &_hoops_GCCRC->id);
				}
				_hoops_CSRGR->_hoops_CSC._hoops_SGAGC[0] = _hoops_RSARR;
			}
			if (_hoops_PARAH == _hoops_GCCRC) {
				FREE(_hoops_PARAH, _hoops_SICRC);
			}
			else {
				if (_hoops_GCCRC) {
					FREE(_hoops_GCCRC, _hoops_SICRC);
				}
				if (_hoops_PARAH) {
					FREE(_hoops_PARAH, _hoops_SICRC);
				}
			}
		} break;

#ifdef WGL_DRIVER
		case OGLR_MAKE_CONTEXT_CURRENT: {
			if (z && z!=image) {
				if (_hoops_GCCRC->id)
					glDeleteLists (_hoops_GCCRC->id, 1);
				FREE_ARRAY(_hoops_GCCRC->buffer, _hoops_GCCRC->size, char);
				FREE(_hoops_GCCRC, _hoops_SICRC);
			}
			if (_hoops_PARAH) {
				if (_hoops_CSRGR->hGLRC != _hoops_PARAH->hGLRC)
					wglDeleteContext (_hoops_PARAH->hGLRC);
				_hoops_CSRGR->wglReleasePbufferDCARB(_hoops_PARAH->pbuffer, _hoops_PARAH->hDC);
				_hoops_CSRGR->wglDestroyPbufferARB (_hoops_PARAH->pbuffer);
				FREE(_hoops_PARAH, _hoops_SICRC);
			}
		} break;

		case OGLR_WGL_ARB_BUFFER: {
			if (_hoops_PARAH) {
				_hoops_CSRGR->wglDeleteBufferRegionARB(_hoops_PARAH->handle);
				FREE(_hoops_PARAH, _hoops_SICRC);
			}
			else {
				_hoops_CSRGR->wglDeleteBufferRegionARB(_hoops_GCCRC->handle);
				FREE(_hoops_GCCRC, _hoops_SICRC);
			}
			_hoops_CSRGR->_hoops_HRSRC = false;
		} break;

#else
		case OGLR_MAKE_CONTEXT_CURRENT:
		case OGLR_WGL_ARB_BUFFER:
			break;
#endif
		case OGLR_KTX_BUFFER_REGION: {
			if (_hoops_PARAH) {
				(*_hoops_CSRGR->glDeleteKTXBufferRegion) (_hoops_PARAH->id);
				FREE(_hoops_PARAH, _hoops_SICRC);
			}
			if (z) {
				(*_hoops_CSRGR->glDeleteKTXBufferRegion) (_hoops_GCCRC->id);
				FREE(_hoops_GCCRC, _hoops_SICRC);
			}
			_hoops_CSRGR->_hoops_HRSRC = false;
		} break;

		case OGLR_DRAW_PIXELS: {
			if (_hoops_PARAH) {
				if (_hoops_PARAH->id)
					glDeleteLists (_hoops_PARAH->id, 1);
				FREE_ARRAY(_hoops_PARAH->buffer, _hoops_PARAH->size, char);
				FREE(_hoops_PARAH, _hoops_SICRC);
			}
			if (z) {
				if (_hoops_GCCRC->id)
					glDeleteLists (_hoops_GCCRC->id, 1);
				FREE_ARRAY(_hoops_GCCRC->buffer, _hoops_GCCRC->size, float);
				FREE(_hoops_GCCRC, _hoops_SICRC);
			}
		} break;

		default:
			break;
	}

	_hoops_ASPGR = HI_What_Time();
	_hoops_GPRH(_hoops_PSPGR) += (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}/* _hoops_RSGR _hoops_API _hoops_PHRAH */


/*
 * _hoops_SRAC
 */
local void
_hoops_HIPGR (Net_Rendition const & nr,
			 Int_Rectangle const * area,
			 void alter * image,
			 void alter * z)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_SICRC *_hoops_PARAH = (_hoops_SICRC *) image;
	_hoops_SICRC *_hoops_GCCRC = (_hoops_SICRC *) z;
	GLint l,b,r,t,w,h;
	_hoops_RASRC type;
	Int_Rectangle const *_hoops_ACCRC;
	_hoops_GSPGR	_hoops_RSPGR, _hoops_ASPGR;

	_hoops_RAPRC("save_region", true);

	_hoops_RSPGR = HI_What_Time();

	if (_hoops_PARAH && _hoops_GCCRC &&
		_hoops_PARAH->type != _hoops_GCCRC->type) {
		_hoops_HIPGR (nr, area, image, null);
		_hoops_PARAH = null;
	}
	type = (_hoops_PARAH ? _hoops_PARAH->type : _hoops_GCCRC->type);

	if (_hoops_PARAH)
		_hoops_ACCRC = &_hoops_PARAH->_hoops_ACCRC;
	else
		_hoops_ACCRC = &_hoops_GCCRC->_hoops_ACCRC;

	if (area) {
		/* _hoops_SGH _hoops_PPR _hoops_IPS _hoops_CCAC */
		if (_hoops_PARAH && area != &_hoops_PARAH->_hoops_ACCRC)
			_hoops_RSAI (area, Int_Rectangle, &_hoops_PARAH->_hoops_ACCRC);
		if (z && area != &_hoops_GCCRC->_hoops_ACCRC)
			_hoops_RSAI (area, Int_Rectangle, &_hoops_GCCRC->_hoops_ACCRC);
		if (area->left > area->right)
			goto _hoops_PP;
		if (area->bottom > area->top)
			goto _hoops_PP;
	}
	else
		area = _hoops_ACCRC;

	l = area->left;
	b = area->bottom;
	r = area->right + 1;
	t = area->top + 1;
	w = r - l;
	h = t - b;

	/* _hoops_SRGC _hoops_CPAP _hoops_IS _hoops_HCHSR _hoops_PSCA _hoops_ARPP _hoops_GPS */
	glFlush ();

	switch (type) {

		case OGLR_DEPTH_TEXTURE_RECT:
		case OGLR_DEPTH_TEXTURE_SQUARE: {
			GLenum _hoops_IRSRC = (type == OGLR_DEPTH_TEXTURE_RECT ? GL_TEXTURE_RECTANGLE_ARB : GL_TEXTURE_2D);

			ENSURE_SCISSOR_SET (_hoops_CSRGR, l, b, w, h);
			ENSURE_SCISSOR_OFF (_hoops_CSRGR);
			ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
			_hoops_IPGP(_hoops_CSRGR, false);
			ENSURE_LINE_SMOOTH(_hoops_CSRGR, false);
			_hoops_PPRGC(_hoops_CSRGR, 0);

			glEnable (_hoops_IRSRC);
			if (_hoops_PARAH) {
				_hoops_IPRGC(_hoops_CSRGR, 0, _hoops_IRSRC, _hoops_PARAH->id);
				glCopyTexSubImage2D(_hoops_IRSRC, 0, 0, 0, l, b, w, h);
				_hoops_CSRGR->dc->_hoops_IGGI->_hoops_RPRH++;
			}
			if (_hoops_GCCRC) {
				_hoops_IPRGC(_hoops_CSRGR, 0, _hoops_IRSRC, _hoops_GCCRC->id);
				glCopyTexSubImage2D(_hoops_IRSRC, 0, 0, 0, l, b, w, h);
				_hoops_CSRGR->dc->_hoops_IGGI->_hoops_RPRH++;
			}
			glDisable (_hoops_IRSRC);
			_hoops_AARRC(_hoops_CSRGR, 0);
		} break;
#ifdef WGL_DRIVER
		case OGLR_MAKE_CONTEXT_CURRENT: {
			if (_hoops_PARAH != null) {
				/* _hoops_IRIGR _hoops_HII _hoops_HGSI _hoops_SASRC, _hoops_GGI _hoops_IS _hoops_CSCR _hoops_SASRC */
				_hoops_CSRGR->wglMakeContextCurrentARB (_hoops_PARAH->hDC, _hoops_CSRGR->hDC, _hoops_PARAH->hGLRC);
				glRasterPos2i (l, b);
				/* _hoops_SPSRC _hoops_PIGS _hoops_PPPSR _hoops_HRII _hoops_HSAR _hoops_RHIR _hoops_GHSGR _hoops_CIGR _hoops_PGGA _hoops_CGSRC _hoops_GGSC _hoops_HRGR _hoops_SCGR */
				glDepthMask (GL_FALSE);
				glCopyPixels (l, b, w, h, GL_COLOR);
				glDepthMask (GL_TRUE);
				if (_hoops_GCCRC == _hoops_PARAH) {
					glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
					glCopyPixels (l, b, w, h, GL_DEPTH);
					glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
				}
				if (_hoops_CSRGR->_hoops_APSRC)
					wglMakeCurrent (_hoops_CSRGR->_hoops_HIISI, _hoops_CSRGR->hGLRC);
				else
					wglMakeCurrent (_hoops_CSRGR->hDC, _hoops_CSRGR->hGLRC);
			}
			if (_hoops_GCCRC && _hoops_GCCRC != _hoops_PARAH) {
				_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
				int x,y;
				float _hoops_CCCRR, *_hoops_GHSRC;

				_hoops_GIAC(_hoops_CSRGR, nr);
				_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
				ENSURE_PIXEL_UNPACK_ALIGNMENT(_hoops_CSRGR, 4);
				glReadPixels (l, b, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, _hoops_GCCRC->buffer);
				/* _hoops_RHSRC _hoops_AHSRC */
				if (_hoops_GCCRC->id)
					glDeleteLists (_hoops_GCCRC->id, 1);
				_hoops_GCCRC->id = glGenLists (1);
				glNewList (_hoops_GCCRC->id, GL_COMPILE);
				glBegin (GL_POINTS);
				_hoops_GHSRC = (float*)_hoops_GCCRC->buffer;
				for (y = b; y < t; y++) {
					for (x = l; x < r; x++) {
						_hoops_CCCRR = *_hoops_GHSRC++;
						if (_hoops_CCCRR < 1.0f) {
							_hoops_CCCRR *= _hoops_IHCR->_hoops_PCHH;
							glVertex3f((float)x, (float)y, _hoops_CCCRR);
						}
					}
				}
				glEnd ();
				glEndList ();
			}
		} break;

		case OGLR_WGL_ARB_BUFFER: {
			_hoops_RGIGC (_hoops_CSRGR, nr->transform_rendition->_hoops_RHPHP);
			if (_hoops_PARAH)
				(_hoops_CSRGR->wglSaveBufferRegionARB) (_hoops_PARAH->handle, l, b, w, h);
			else
				(_hoops_CSRGR->wglSaveBufferRegionARB) (_hoops_GCCRC->handle, l, b, w, h);
		} break;

#else
		case OGLR_WGL_ARB_BUFFER:
		case OGLR_MAKE_CONTEXT_CURRENT:
			break;
#endif
		case OGLR_KTX_BUFFER_REGION: {
			ENSURE_SCISSOR_SET (_hoops_CSRGR, l, b, w, h);
			ENSURE_SCISSOR_OFF (_hoops_CSRGR);
			_hoops_RGIGC (_hoops_CSRGR, nr->transform_rendition->_hoops_RHPHP);
			if (_hoops_PARAH)
				(*_hoops_CSRGR->glReadKTXBufferRegion) (_hoops_PARAH->id, l, b, w, h);
			if (z)
				(*_hoops_CSRGR->glReadKTXBufferRegion) (_hoops_GCCRC->id, l, b, w, h);
		} break;

		case OGLR_DRAW_PIXELS: {
			_hoops_GIAC(_hoops_CSRGR, nr);
			_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
			ENSURE_PIXEL_UNPACK_ALIGNMENT(_hoops_CSRGR, 4);
			if (_hoops_PARAH)
				glReadPixels (l, b, w, h, GL_RGB, GL_UNSIGNED_BYTE, _hoops_PARAH->buffer);
			if (z)
				glReadPixels (l, b, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, _hoops_GCCRC->buffer);

#if 0
			{
				int i;
				char * tmp=(char *)_hoops_PARAH->buffer;
				for (i=0; i<_hoops_PARAH->size; i+=8) {

					tmp[i+0] = 0;
					tmp[i+1] = 0;
					tmp[i+2] = 0;
				}
			}
#endif

		default:
			break;

		} break;
	}
_hoops_PP:
	_hoops_ASPGR = HI_What_Time();
	_hoops_GPRH(_hoops_PSPGR) += (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}/* _hoops_RSGR _hoops_API _hoops_CCPIP */


/*
 * _hoops_SRAC
 */
local void
_hoops_PIPGR (Net_Rendition const & nr,
				Int_Rectangle const * area,
				void alter * image,
				void alter * z)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_SICRC *_hoops_PARAH = (_hoops_SICRC *) image;
	_hoops_SICRC *_hoops_GCCRC = (_hoops_SICRC *) z;
	GLint l, b, r, t, w, h, dx, _hoops_CRRAR, _hoops_PHSRC, _hoops_HHSRC;
	GLboolean _hoops_CSHH;
	GLint _hoops_IHSRC;
	Int_Rectangle const *_hoops_ACCRC;
	_hoops_RASRC type;
	bool _hoops_CHSRC = false;
	_hoops_GSPGR	_hoops_RSPGR, _hoops_ASPGR;

	_hoops_RAPRC("restore_region", true);

	_hoops_RSPGR = HI_What_Time();

	if (_hoops_PARAH && _hoops_GCCRC &&
		_hoops_PARAH->type != _hoops_GCCRC->type) {
		_hoops_PIPGR (nr, area, image, null);
		_hoops_PARAH = null;
	}
	type = (_hoops_PARAH ? _hoops_PARAH->type : _hoops_GCCRC->type);


	if (_hoops_PARAH)
		_hoops_ACCRC = &_hoops_PARAH->_hoops_ACCRC;
	else
		_hoops_ACCRC = &_hoops_GCCRC->_hoops_ACCRC;

	if (!area) {
		area = _hoops_ACCRC;
		_hoops_CHSRC = true;
	}

	l = area->left;
	b = area->bottom;
	r = area->right + 1;
	t = area->top + 1;
	w = r - l;
	h = t - b;
	dx = l - _hoops_ACCRC->left;
	_hoops_CRRAR = b - _hoops_ACCRC->bottom;
	_hoops_PHSRC = _hoops_ACCRC->right - _hoops_ACCRC->left + 1;
	_hoops_HHSRC = _hoops_ACCRC->top - _hoops_ACCRC->bottom + 1;
	if (area->left > area->right)
		goto _hoops_PP;
	if (area->bottom > area->top)
		goto _hoops_PP;

	_hoops_CSHH = _hoops_CSRGR->_hoops_CSC._hoops_AAIH;
	_hoops_IHSRC = _hoops_CSRGR->_hoops_CSC._hoops_GHAGC;

	switch (type) {
		case OGLR_DEPTH_TEXTURE_RECT:
		case OGLR_DEPTH_TEXTURE_SQUARE: {
			GLenum _hoops_IRSRC = (type == OGLR_DEPTH_TEXTURE_RECT ? GL_TEXTURE_RECTANGLE_ARB : GL_TEXTURE_2D);
			float _hoops_SHSRC, _hoops_GISRC, _hoops_RISRC, _hoops_PGPIR;
			float _hoops_AISRC;
			Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

			if (type == OGLR_DEPTH_TEXTURE_SQUARE) {
				if (_hoops_PARAH)
					_hoops_AISRC = _hoops_PARAH->size;
				else
					_hoops_AISRC = _hoops_GCCRC->size;
			}
			else
				_hoops_AISRC = 1;
			_hoops_SHSRC = (l-_hoops_ACCRC->left) / _hoops_AISRC;
			_hoops_GISRC = (r-_hoops_ACCRC->left) / _hoops_AISRC;
			_hoops_RISRC = (b-_hoops_ACCRC->bottom) / _hoops_AISRC;
			_hoops_PGPIR = (t-_hoops_ACCRC->bottom) / _hoops_AISRC;

			if (_hoops_GCCRC && _hoops_CSRGR->_hoops_AIPGA > 1)
				_hoops_CAAGR (nr, l,  r, b, t);

			_hoops_GIAC(_hoops_CSRGR, nr);
			_hoops_SCIGC (_hoops_CSRGR);
			_hoops_RPSRC (_hoops_CSRGR);
			ENSURE_DEPTH_MASK (_hoops_CSRGR, GL_FALSE);
			_hoops_PISRC (_hoops_CSRGR, GL_ALWAYS);
			ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
			_hoops_IPGP(_hoops_CSRGR, false);
			ENSURE_LINE_SMOOTH(_hoops_CSRGR, false);

			ENSURE_SCISSOR_SET(_hoops_CSRGR,
				_hoops_GPHH.left, _hoops_GPHH.bottom,
				_hoops_GPHH.right - _hoops_GPHH.left + 1,
				_hoops_GPHH.top - _hoops_GPHH.bottom + 1);
			ENSURE_SCISSOR_OFF (_hoops_CSRGR);

			_hoops_PPRGC(_hoops_CSRGR, 0);
			glEnable (_hoops_IRSRC);
			_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, 0);
			_hoops_SRGRC (_hoops_CSRGR, 0);
		    ENSURE_TEXTURE_ENV_MODE (_hoops_CSRGR, GL_REPLACE, 0);

			glMatrixMode (GL_TEXTURE);
			glPushMatrix ();
			glLoadIdentity ();
			glMatrixMode (GL_MODELVIEW);

			if (_hoops_PARAH) {
				_hoops_IPRGC(_hoops_CSRGR, 0, _hoops_IRSRC, _hoops_PARAH->id);
				glBegin(GL_QUADS);
					glTexCoord2f(_hoops_SHSRC, _hoops_RISRC);	glVertex2f(l, b);
					glTexCoord2f(_hoops_SHSRC, _hoops_PGPIR);	glVertex2f(l, t);
					glTexCoord2f(_hoops_GISRC, _hoops_PGPIR);	glVertex2f(r, t);
					glTexCoord2f(_hoops_GISRC, _hoops_RISRC);	glVertex2f(r, b);
				glEnd();
				DEBUG_FLUSH();
			}
			if (_hoops_GCCRC) {
				GLboolean _hoops_ISHH = _hoops_CSRGR->_hoops_CSC._hoops_RAIH;
				_hoops_RPAP (_hoops_CSRGR, GL_FALSE);
				ENSURE_DEPTH_MASK (_hoops_CSRGR, GL_TRUE);
				_hoops_IPRGC(_hoops_CSRGR, 0, _hoops_IRSRC, _hoops_GCCRC->id);
				glEnable (GL_FRAGMENT_PROGRAM_ARB);
				(*_hoops_CSRGR->glUseProgramObjectARB) (_hoops_CSRGR->_hoops_SISGC);
				glBegin(GL_QUADS);
					glTexCoord2f(_hoops_SHSRC, _hoops_RISRC);	glVertex2f(l, b);
					glTexCoord2f(_hoops_SHSRC, _hoops_PGPIR);	glVertex2f(l, t);
					glTexCoord2f(_hoops_GISRC, _hoops_PGPIR);	glVertex2f(r, t);
					glTexCoord2f(_hoops_GISRC, _hoops_RISRC);	glVertex2f(r, b);
				glEnd();
				DEBUG_FLUSH();
				(*_hoops_CSRGR->glUseProgramObjectARB) (0);
				glDisable (GL_FRAGMENT_PROGRAM_ARB);
				_hoops_RPAP (_hoops_CSRGR, _hoops_ISHH);
			}

			glMatrixMode (GL_TEXTURE);
			glPopMatrix ();
			glMatrixMode (GL_MODELVIEW);

			_hoops_AARRC (_hoops_CSRGR, 0);
			glDisable (_hoops_IRSRC);
		} break;

#ifdef WGL_DRIVER
		case OGLR_MAKE_CONTEXT_CURRENT: {
			_hoops_HHCR alter &		_hoops_IHCR = (_hoops_HHCR alter &)nr->transform_rendition;
			bool _hoops_HISRC = false;

			if (!BIT(_hoops_IHCR->flags, _hoops_PASP)) {
				_hoops_IHCR->flags |= _hoops_PASP;
				_hoops_HISRC = true;
			}
			_hoops_GIAC(_hoops_CSRGR, nr);
			_hoops_HISP(_hoops_CSRGR, false);
			ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
			_hoops_IPGP(_hoops_CSRGR, false);
			if (_hoops_PARAH) {
				/* _hoops_IRIGR _hoops_HII _hoops_CSCR _hoops_SASRC, _hoops_GGI _hoops_IS _hoops_HGSI _hoops_SASRC */
				_hoops_CSRGR->wglMakeContextCurrentARB(_hoops_CSRGR->hDC, _hoops_PARAH->hDC, _hoops_CSRGR->hGLRC);
				/* _hoops_PHIH _hoops_HAIR _hoops_IH _hoops_RH _hoops_SHSC _hoops_RPPS */
				_hoops_RIIGC(_hoops_CSRGR);
				ENSURE_DEPTH_MASK (_hoops_CSRGR, GL_FALSE);
				glRasterPos2i(_hoops_ACCRC->left, _hoops_ACCRC->bottom);
				glCopyPixels(_hoops_ACCRC->left, _hoops_ACCRC->bottom, _hoops_PHSRC, _hoops_HHSRC, GL_COLOR);
				if (_hoops_GCCRC == _hoops_PARAH) {
					_hoops_RPSRC(_hoops_CSRGR);
					glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
					glCopyPixels(_hoops_ACCRC->left, _hoops_ACCRC->bottom, _hoops_PHSRC, _hoops_HHSRC, GL_DEPTH);
					glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
				}
				if (_hoops_CSRGR->_hoops_APSRC)
					wglMakeCurrent (_hoops_CSRGR->_hoops_HIISI, _hoops_CSRGR->hGLRC);
				else
					wglMakeCurrent (_hoops_CSRGR->hDC, _hoops_CSRGR->hGLRC);
			}
			if (_hoops_GCCRC != _hoops_PARAH && _hoops_GCCRC != null) {
				if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_RESTORE_REGION_ZBUFFER_OFF)) {
					_hoops_RIIGC(_hoops_CSRGR);
				}
				else {
					_hoops_RPSRC(_hoops_CSRGR);
					_hoops_PISRC (_hoops_CSRGR,GL_ALWAYS);
				}
				glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
				ENSURE_DEPTH_MASK (_hoops_CSRGR, GL_TRUE);
				if (_hoops_GCCRC->id) {
					/* _hoops_RHSRC _hoops_AHSRC */
					_hoops_GGIGC (_hoops_CSRGR);
					ENSURE_SCISSOR_SET(_hoops_CSRGR, l, b, w, h);
					glClear (GL_DEPTH_BUFFER_BIT);
					glCallList (_hoops_GCCRC->id);
				}
				else {
					glRasterPos2i (_hoops_ACCRC->left, _hoops_ACCRC->bottom);
					ENSURE_PIXEL_UNPACK_ALIGNMENT(_hoops_CSRGR,4);
					glDrawPixels (_hoops_PHSRC, _hoops_HHSRC, GL_DEPTH_COMPONENT, GL_FLOAT, (unsigned char *) _hoops_GCCRC->buffer);
				}
				glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			}
			if (_hoops_HISRC)
				_hoops_IHCR->flags &= ~_hoops_PASP;
		} break;

		case OGLR_WGL_ARB_BUFFER: {
			Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

			/* _hoops_AGSGR _hoops_PSAP _hoops_IISRC _hoops_PPR _hoops_ARP _hoops_RH _hoops_IISRC _hoops_IIRRH _hoops_SAHR _hoops_GGR _hoops_AGIR,
			 * _hoops_PRGI _hoops_PHRI _hoops_SCH _hoops_CGH _hoops_SHH _hoops_IAIH _hoops_PGGA _hoops_SCH _hoops_HRGR _hoops_GRGR. */
			ENSURE_SCISSOR_OFF (_hoops_CSRGR);
			if (area)
				ENSURE_SCISSOR_SET(_hoops_CSRGR,
					_hoops_GPHH.left, _hoops_GPHH.bottom,
					_hoops_GPHH.right - _hoops_GPHH.left + 1,
					_hoops_GPHH.top - _hoops_GPHH.bottom + 1);
			else
				ENSURE_SCISSOR_SET(_hoops_CSRGR, l, b, w, h);

			_hoops_RGIGC (_hoops_CSRGR, nr->transform_rendition->_hoops_RHPHP);
			if (_hoops_PARAH)
				(_hoops_CSRGR->wglRestoreBufferRegionARB) (_hoops_PARAH->handle, l, b, w, h, dx, _hoops_CRRAR);
			else
				(_hoops_CSRGR->wglRestoreBufferRegionARB) (_hoops_GCCRC->handle, l, b, w, h, dx, _hoops_CRRAR);
		} break;
#else
		case OGLR_MAKE_CONTEXT_CURRENT:
		case OGLR_WGL_ARB_BUFFER:
			break;
#endif
		case OGLR_KTX_BUFFER_REGION: {
			Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

			/* _hoops_AGSGR _hoops_PSAP _hoops_IISRC _hoops_PPR _hoops_ARP _hoops_RH _hoops_IISRC _hoops_IIRRH _hoops_SAHR _hoops_GGR _hoops_AGIR,
			 * _hoops_PRGI _hoops_PHRI _hoops_SCH _hoops_CGH _hoops_SHH _hoops_IAIH _hoops_PGGA _hoops_SCH _hoops_HRGR _hoops_GRGR. */
			ENSURE_SCISSOR_OFF (_hoops_CSRGR);
			if (area)
				ENSURE_SCISSOR_SET(_hoops_CSRGR,
					_hoops_GPHH.left, _hoops_GPHH.bottom,
					_hoops_GPHH.right - _hoops_GPHH.left + 1,
					_hoops_GPHH.top - _hoops_GPHH.bottom + 1);
			else
				ENSURE_SCISSOR_SET(_hoops_CSRGR, l, b, w, h);

			_hoops_RGIGC (_hoops_CSRGR, nr->transform_rendition->_hoops_RHPHP);

			if (_hoops_PARAH)
				(*_hoops_CSRGR->glDrawKTXBufferRegion) (_hoops_PARAH->id, l, b, w, h, dx, _hoops_CRRAR);
			if (_hoops_GCCRC)
				(*_hoops_CSRGR->glDrawKTXBufferRegion) (_hoops_GCCRC->id, l, b, w, h, dx, _hoops_CRRAR);
		} break;

		case OGLR_DRAW_PIXELS: {

			_hoops_GIAC(_hoops_CSRGR, nr);
			ENSURE_VIEWPORT_SET (_hoops_CSRGR, _hoops_ACCRC->left, _hoops_ACCRC->bottom, _hoops_PHSRC, _hoops_HHSRC);
			ENSURE_SCISSOR_OFF (_hoops_CSRGR);

			/* _hoops_CISRC _hoops_SISRC _hoops_GCSRC*/
			if (_hoops_CHSRC) {
				_hoops_HHCR alter &		_hoops_IHCR = (_hoops_HHCR alter &)nr->transform_rendition;
				bool							_hoops_RCSRC = BIT(_hoops_IHCR->flags, _hoops_PASP);

				if (_hoops_GCCRC && !BIT(_hoops_IHCR->flags, _hoops_PASP))
					_hoops_IHCR->flags |= _hoops_PASP;

				_hoops_HISP(_hoops_CSRGR, false);
				ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
				_hoops_IPGP(_hoops_CSRGR, false);
				ENSURE_PIXEL_UNPACK_ALIGNMENT(_hoops_CSRGR,4);

				if (_hoops_PARAH) {
					_hoops_RIIGC(_hoops_CSRGR);
					ENSURE_DEPTH_MASK (_hoops_CSRGR, GL_FALSE);
					if (_hoops_PARAH->id) {
						/* _hoops_RHSRC _hoops_AHSRC */
						glCallList (_hoops_PARAH->id);
					}
					else {
						glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
						glRasterPos2i (_hoops_ACCRC->left, _hoops_ACCRC->bottom);
						glDrawPixels (_hoops_PHSRC, _hoops_HHSRC, GL_RGB, GL_UNSIGNED_BYTE, (unsigned char *)_hoops_PARAH->buffer);
					}
				}
				if (_hoops_GCCRC) {
					if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_RESTORE_REGION_ZBUFFER_OFF)) {
						_hoops_RIIGC(_hoops_CSRGR);
					}
					else {
						_hoops_RPSRC(_hoops_CSRGR);
						_hoops_PISRC (_hoops_CSRGR, GL_ALWAYS);
					}
					glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
					ENSURE_DEPTH_MASK (_hoops_CSRGR, GL_TRUE);
					if (_hoops_GCCRC->id) {
						/* _hoops_RHSRC _hoops_AHSRC */
						glClear (GL_DEPTH_BUFFER_BIT);
						glCallList (_hoops_GCCRC->id);
					}
					else {
						glRasterPos2i (_hoops_ACCRC->left, _hoops_ACCRC->bottom);
						glDrawPixels (_hoops_PHSRC, _hoops_HHSRC, GL_DEPTH_COMPONENT, GL_FLOAT, (unsigned char *) _hoops_GCCRC->buffer);
					}
					glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
				}

				if (_hoops_RCSRC)
					_hoops_IHCR->flags |= _hoops_PASP;
				else
					_hoops_IHCR->flags &= ~_hoops_PASP;
			}
			else if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_PIXEL_STORE)) {
				/* _hoops_SGPIP _hoops_RAIGR _hoops_GHCR _hoops_ACSRC */
				int _hoops_PCSRC, offset;

				_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
				_hoops_RIIGC(_hoops_CSRGR);
				ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
				_hoops_IPGP(_hoops_CSRGR, false);
				ENSURE_PIXEL_UNPACK_ALIGNMENT (_hoops_CSRGR, 4);

				/*_hoops_IPS _hoops_IRS _hoops_CSCIP*/
				if (_hoops_PARAH) {
					_hoops_PCSRC = _hoops_PHSRC * 3;
					/* _hoops_CRPSR _hoops_IS _hoops_RH _hoops_GRGP/_hoops_HCSRC _hoops_AHSGP */
					if (_hoops_PCSRC%4)
						_hoops_PCSRC += (4 - _hoops_PCSRC%4);
					offset = _hoops_PCSRC * _hoops_CRRAR;
					glRasterPos2i (_hoops_ACCRC->left, area->bottom);
					ENSURE_DEPTH_MASK(_hoops_CSRGR,GL_FALSE);
					glDrawPixels (_hoops_PHSRC, h, GL_RGB, GL_UNSIGNED_BYTE,
						(unsigned char *) _hoops_PARAH->buffer + offset);
					ENSURE_DEPTH_MASK(_hoops_CSRGR,GL_TRUE);
				}
				if (_hoops_GCCRC) {
					_hoops_PCSRC = _hoops_PHSRC * sizeof(float);
					offset = _hoops_PCSRC * _hoops_CRRAR;
					if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_RESTORE_REGION_ZBUFFER_OFF)) {
						_hoops_RIIGC(_hoops_CSRGR);
					}
					else {
						_hoops_RPSRC(_hoops_CSRGR);
						_hoops_PISRC (_hoops_CSRGR, GL_ALWAYS);
					}
					glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
					glRasterPos2i (_hoops_ACCRC->left, area->bottom);
					glDrawPixels (_hoops_PHSRC, h, GL_DEPTH_COMPONENT, GL_FLOAT,
						(unsigned char *) _hoops_GCCRC->buffer + offset);
					glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
				}
			}
			else {
				/* _hoops_ACGPA _hoops_RAIGR _hoops_ICSRC _hoops_GRPIP */
				/* "_hoops_SHI" _hoops_APPP _hoops_IHHH _hoops_HII _hoops_RH _hoops_GSSC _hoops_RAAP _hoops_RPIA _hoops_IIGR _hoops_RH _hoops_GIGR _hoops_RCPGR _hoops_CSCR _hoops_IS _hoops_RH
				 * _hoops_GSSC _hoops_RAAP _hoops_RPIA _hoops_IIGR _hoops_CCSRC. "_hoops_SCCIA" _hoops_APPP _hoops_IHHH _hoops_HII _hoops_RH _hoops_RSGI _hoops_IIGR _hoops_RH _hoops_GAGHR
				 * _hoops_IS _hoops_RH _hoops_RSGI _hoops_IIGR _hoops_RH _hoops_PRPRR */
				int _hoops_PCSRC, offset, offset2;

				_hoops_HISP(_hoops_CSRGR, BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_GPSP));
				_hoops_RIIGC(_hoops_CSRGR);
				ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
				_hoops_IPGP(_hoops_CSRGR, false);

				glRasterPos2i (area->left, area->bottom);
				glPixelStorei(GL_UNPACK_ROW_LENGTH, _hoops_PHSRC);
				if (_hoops_PARAH) {
					_hoops_PCSRC = _hoops_PHSRC * 3;
					/* _hoops_CRPSR _hoops_IS _hoops_RH _hoops_GRGP/_hoops_HCSRC _hoops_AHSGP */
					if (_hoops_PCSRC%4)
						_hoops_PCSRC += (4 - _hoops_PCSRC%4);
					offset = _hoops_PCSRC * _hoops_CRRAR;
					offset2 = offset + dx*3;
					glDrawPixels (w, h, GL_RGB, GL_UNSIGNED_BYTE,
						(unsigned char *) _hoops_PARAH->buffer + offset2);
				}
				if (_hoops_GCCRC) {
					ENSURE_DEPTH_MASK(_hoops_CSRGR,GL_TRUE);
					if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_RESTORE_REGION_ZBUFFER_OFF)) {
						_hoops_RIIGC(_hoops_CSRGR);
					}
					else {
						_hoops_RPSRC(_hoops_CSRGR);
						_hoops_PISRC (_hoops_CSRGR, GL_ALWAYS);
					}
					_hoops_PCSRC = _hoops_PHSRC * sizeof(float);
					offset = _hoops_PCSRC * _hoops_CRRAR;
					offset2 = offset + dx*sizeof(float);
					glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
					glRasterPos2i (area->left, area->bottom);
					glDrawPixels (w, h, GL_DEPTH_COMPONENT, GL_FLOAT,
						(unsigned char *) _hoops_GCCRC->buffer + offset2);
					glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
				}
				glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

			}
		} break;

		default:
			break;
	}

	_hoops_CSRGR->_hoops_GPAGC = -1;	// _hoops_HPSP: _hoops_HHSA _hoops_SCSRC _hoops_IS _hoops_GAGAH
	_hoops_CSRGR->_hoops_HCAC = _hoops_CCC;

	ENSURE_DEPTH_MASK (_hoops_CSRGR, _hoops_CSHH);
	_hoops_PISRC (_hoops_CSRGR, _hoops_IHSRC);
	UNREFERENCED (nr);

_hoops_PP:
	_hoops_ASPGR = HI_What_Time();
	_hoops_GPRH(_hoops_PSPGR) += (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}/* _hoops_RSGR _hoops_API _hoops_SPRAH */



/*
 * _hoops_SRAC
 */
local void
_hoops_CSPGR (
	Display_Context alter *		dc) {
	OGLData *					_hoops_CSRGR = OGLD(dc);

	_hoops_CSRGR->_hoops_SSPGR = _hoops_CSRGR->_hoops_CIGI;
	_hoops_CSRGR->_hoops_GGHGR = _hoops_CSRGR->_hoops_ISCI;
	_hoops_CSRGR->_hoops_RGHGR = dc->_hoops_IPCI->mask;

	_hoops_CSRGR->_hoops_CIGI = null;
	_hoops_CSRGR->_hoops_ISCI = 0;
	dc->_hoops_IPCI->mask = _hoops_RAPI;
}
local void
_hoops_AGHGR (
	Display_Context alter *		dc) {
	OGLData *					_hoops_CSRGR = OGLD(dc);

	_hoops_CSRGR->_hoops_CIGI = _hoops_CSRGR->_hoops_SSPGR;
	_hoops_CSRGR->_hoops_ISCI = _hoops_CSRGR->_hoops_GGHGR;
	dc->_hoops_IPCI->mask = _hoops_CSRGR->_hoops_RGHGR;
}






local char const *	_hoops_GSSRC =
"!!ARBfp1.0\n\
	OPTION ARB_fragment_program_shadow;\n\
	PARAM offset = program.env[0];\n\
	TEMP R0;\n\
	MOV R0, fragment.position;\n\
	ADD R0, R0, -offset;\n\
	ADD R0.z, R0.z, -0.00001;\n\
	TEX R0.x, R0, texture[1], SHADOWRECT;\n\
	ADD R0.x, R0.x, -0.5;\n\
	KIL R0.x;\n\
	MOV result.color, fragment.color;\n\
	END\n";

//_hoops_GAR _hoops_ARRS, _hoops_HIH _hoops_CCA _hoops_IRS _hoops_HH _hoops_ISAR _hoops_GGR _hoops_HGHC _hoops_IIGR _hoops_RH _hoops_GCPSH _hoops_HAIR
local char const *	_hoops_RSSRC =
"!!ARBfp1.0\n\
	OPTION ARB_fragment_program_shadow;\n\
	PARAM offset = program.env[0];\n\
	TEMP R0;\n\
	MOV R0, fragment.position;\n\
	ADD R0, R0, -offset;\n\
	ADD R0.z, R0.z, -0.00001;\n\
	TEX R0.x, R0, texture[1], SHADOWRECT;\n\
	ADD R0.x, R0.x, -0.5;\n\
	KIL R0.x;\n\
	TEX R0, fragment.texcoord[0], texture[0], 2D; \n\
	MUL result.color, R0, fragment.color;\n\
	END\n";


/* _hoops_PIHA _hoops_PSSP _hoops_RH _hoops_ASSRC _hoops_HCPH _hoops_GGR _hoops_RH _hoops_GCPSH _hoops_HAACI _hoops_ARRS */
#define _hoops_PSSRC  1

void _hoops_RHH (
	Display_Context alter *	dc)
{
	OGLData alter *			_hoops_CSRGR = OGLD (dc);
	int						_hoops_RIRAH = dc->_hoops_AHAGH;
	int						_hoops_AIRAH;
	_hoops_PGCIP alter *		list;
	int						i;
	GLuint					*_hoops_IPRRR;
	GLuint					*_hoops_CPRRR;
	GLuint *				buffer = null;
	GLenum					_hoops_AASRC;
	int						_hoops_IAAIP, _hoops_CAAIP;
	int						width, height;
	Int_Rectangle const *	extent;
	bool					_hoops_HSSRC[_hoops_APRRR+1];
	bool					_hoops_IAHC = false;

	if (dc->_hoops_PPSIP != null)
		HD_Process_Deferred_Octrees(dc);

	/* _hoops_HCH _hoops_ICH _hoops_SSCP _hoops_SPGC _hoops_CCA _hoops_CASH (16-_hoops_IGRH) _hoops_HAIR _hoops_IH _hoops_HHH _hoops_GAR _hoops_GAPR _hoops_RHGC _hoops_SCPC */
	if (_hoops_CSRGR->_hoops_CRHGC)
		_hoops_IAHC = true;
	if (_hoops_CSRGR->_hoops_AIPGA > 1)
		_hoops_IAHC = true;

	if (_hoops_IAHC) {
		_hoops_RIRAH = 1;
		dc->_hoops_PGCC._hoops_AHAGH = 1;
	}
	else
		dc->_hoops_PGCC._hoops_AHAGH = _hoops_APRRR;

	if (_hoops_RIRAH == 1 || BIT (dc->flags, _hoops_CHSHP)) {
		HD_Std_Depth_Peeling (dc);
		return;
	}
	if (_hoops_RIRAH > _hoops_APRRR)
		_hoops_RIRAH = _hoops_APRRR;

	if ((list = dc->_hoops_GPSS[dc->_hoops_IASS]) == null)
		return;
	dc->_hoops_GPSS[dc->_hoops_IASS] = null;
	if (BIT(dc->flags, _hoops_CHSI)) {
		HD_Free_Deferred_3D_Geometry (list);
		return;
	}
	dc->flags |= _hoops_ICPGR;
	_hoops_CSRGR->_hoops_GIIGC = true;
	_hoops_CSRGR->_hoops_ISSRC = -1;
	_hoops_CPPRR (_hoops_CSRGR, true);

	extent = &list->nr->_hoops_SAIR->_hoops_PHRA;
	_hoops_IAAIP = extent->left;
	_hoops_CAAIP = extent->bottom;
	width = extent->right - extent->left + 1;
	height = extent->top - extent->bottom + 1;

	if (dc->_hoops_PHAGH < 0)
		_hoops_AIRAH = -(int)dc->_hoops_PHAGH;
	else
		_hoops_AIRAH = (int)(dc->_hoops_PHAGH * width * height / 100.0f);

	/* _hoops_ASAC _hoops_IGHP _hoops_CSCR _hoops_PPR _hoops_SSH */
	if (_hoops_CSRGR->_hoops_IGARR == 16)
		_hoops_AASRC = GL_DEPTH_COMPONENT16_ARB;
	else
		_hoops_AASRC = GL_DEPTH_COMPONENT24_ARB;

    ENSURE_VIEWPORT_SET (_hoops_CSRGR, _hoops_IAAIP, _hoops_CAAIP, width, height);
    ENSURE_SCISSOR_SET (_hoops_CSRGR, _hoops_IAAIP, _hoops_CAAIP, width, height);
	_hoops_GGIGC (_hoops_CSRGR);
	DEBUG_FLUSH();

	_hoops_AARRC (_hoops_CSRGR, 0);
#if (_hoops_PSSRC != 0)
	_hoops_PPRGC (_hoops_CSRGR, _hoops_PSSRC);
	/* _hoops_SR _hoops_SGH _hoops_CSCRC _hoops_GGR _hoops_RGR _hoops_API, _hoops_HAR _hoops_RPPGC */
	_hoops_AARRC (_hoops_CSRGR, _hoops_PSSRC);
#endif
	glEnable (GL_TEXTURE_RECTANGLE_ARB);
	ENSURE_LINE_SMOOTH(_hoops_CSRGR, false);

	_hoops_IPRRR = _hoops_CSRGR->_hoops_IISGC;
	_hoops_CPRRR = _hoops_CSRGR->_hoops_CISGC;
	if (width != _hoops_CSRGR->_hoops_CSSRC ||
		height != _hoops_CSRGR->_hoops_SSSRC) {
		for (i = 0; i < _hoops_HISGC; i++)
			if (_hoops_IPRRR[i])
				glDeleteTextures (1, &_hoops_IPRRR[i]);
		for (i = 0; i < _hoops_APRRR; i++)
			if (_hoops_CPRRR[i])
				glDeleteTextures (1, &_hoops_CPRRR[i]);
		_hoops_CSRGR->_hoops_CSC._hoops_SGAGC[_hoops_PSSRC] = _hoops_RSARR;
		ZERO_ARRAY (_hoops_IPRRR, _hoops_HISGC, GLuint);
		ZERO_ARRAY (_hoops_CPRRR, _hoops_APRRR, GLuint);
		_hoops_CSRGR->_hoops_CSSRC = width;
		_hoops_CSRGR->_hoops_SSSRC = height;
	}
	if (!_hoops_IPRRR[0]) {
		if (!buffer)
			ALLOC_ARRAY (buffer, width * height, GLuint);
		glGenTextures (_hoops_HISGC, _hoops_IPRRR);
		for (i=0; i<_hoops_HISGC; i++) {
			_hoops_IPRGC(_hoops_CSRGR, _hoops_PSSRC, GL_TEXTURE_RECTANGLE_ARB, _hoops_IPRRR[i]);
			glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
			glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_COMPARE_FUNC_ARB, GL_GREATER);
			glTexImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, _hoops_AASRC, width, height, 0,
						  GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, buffer);
			dc->_hoops_IGGI->_hoops_RPRH++;
		}
	}

	ZERO_ARRAY (_hoops_HSSRC, _hoops_RIRAH, bool);	/* _hoops_HSGR _hoops_RH _hoops_CGHI _hoops_RARP, _hoops_PGAP _hoops_SR _hoops_IPASR _hoops_CAPP */
	for (i=0; i<=_hoops_RIRAH; i++) {
		if (!_hoops_CPRRR[i]) {
			if (!buffer)
				ALLOC_ARRAY (buffer, width * height, GLuint);
			glGenTextures (1, &_hoops_CPRRR[i]);
			_hoops_IPRGC(_hoops_CSRGR, _hoops_PSSRC, GL_TEXTURE_RECTANGLE_ARB, _hoops_CPRRR[i]);
			glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA8, width, height, 0,
						  GL_RGBA, GL_UNSIGNED_BYTE, buffer);
			dc->_hoops_IGGI->_hoops_RPRH++;
		}
	}
	/* _hoops_ASAC _hoops_GIGR _hoops_AIHSR _hoops_HSH _hoops_CRGR _hoops_GGGAC[_hoops_IGAAH] */
	_hoops_IPRGC(_hoops_CSRGR, _hoops_PSSRC, GL_TEXTURE_RECTANGLE_ARB, _hoops_CPRRR[_hoops_RIRAH]);
	glCopyTexSubImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, _hoops_IAAIP, _hoops_CAAIP, width, height);
	dc->_hoops_IGGI->_hoops_RPRH++;
	_hoops_HSSRC[_hoops_RIRAH] = true;
	if (buffer)
	FREE_ARRAY (buffer, width * height, GLuint);

	/* _hoops_ASAH _hoops_RGAP */

    /* _hoops_HICGC (_hoops_RGGAC); */
	_hoops_CSRGR->_hoops_PSGRC = true;

	if (!_hoops_CSRGR->_hoops_RHSGC) {
		GLint _hoops_AGGAC;
		(*_hoops_CSRGR->glGenProgramsARB) (1, &_hoops_CSRGR->_hoops_RHSGC);
		(*_hoops_CSRGR->glBindProgramARB) (GL_FRAGMENT_PROGRAM_ARB, _hoops_CSRGR->_hoops_RHSGC);
		(*_hoops_CSRGR->glProgramStringARB) (GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
										(GLsizei)strlen (_hoops_GSSRC), _hoops_GSSRC);
		glGetIntegerv (GL_PROGRAM_ERROR_POSITION_ARB, &_hoops_AGGAC);
		if (_hoops_AGGAC != -1) {
			HE_ERROR (0, 0, Sprintf_D (null, "Error in peeling fragment program peel_fp at %d", _hoops_AGGAC));
		}

		(*_hoops_CSRGR->glGenProgramsARB) (1, &_hoops_CSRGR->_hoops_AHSGC);
		(*_hoops_CSRGR->glBindProgramARB) (GL_FRAGMENT_PROGRAM_ARB, _hoops_CSRGR->_hoops_AHSGC);
		(*_hoops_CSRGR->glProgramStringARB) (GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
										(GLsizei)strlen (_hoops_RSSRC), _hoops_RSSRC);
		glGetIntegerv (GL_PROGRAM_ERROR_POSITION_ARB, &_hoops_AGGAC);
		if (_hoops_AGGAC != -1) {
			HE_ERROR (0, 0, Sprintf_D (null, "Error in peeling fragment program peel_fp_texture at %d", _hoops_AGGAC));
		}
	}

	(*_hoops_CSRGR->glBindProgramARB) (GL_FRAGMENT_PROGRAM_ARB, _hoops_CSRGR->_hoops_RHSGC);
    (*_hoops_CSRGR->glProgramEnvParameter4fARB) (GL_FRAGMENT_PROGRAM_ARB, 0, _hoops_IAAIP, _hoops_CAAIP, 0, 0);

	/* _hoops_PGSA _hoops_CRGR _hoops_RH _hoops_APSP _hoops_SRHR _hoops_IS _hoops_RPR _hoops_RH _hoops_PHI _hoops_IIGR _hoops_IACH _hoops_GRR _hoops_AIR
	   _hoops_HRGR _hoops_RHIAA _hoops_HPP _hoops_CPHP _hoops_RRH */
	ENSURE_STENCIL_ON (_hoops_CSRGR);
	glStencilMask (0x00ff);
	/* _hoops_PPSI 1'_hoops_GRI _hoops_CRGR _hoops_RH _hoops_AAPA _hoops_IGRH (_hoops_GHCA _hoops_SHH _hoops_GCGSP _hoops_SPHR _hoops_HPP _hoops_HSPH _hoops_PGHH),
	   _hoops_PPR 0'_hoops_GRI _hoops_CRGR _hoops_RH _hoops_GSSC _hoops_SIH */
	glClearStencil (0x0080);
	glClear (GL_STENCIL_BUFFER_BIT);
	glClearStencil (0);
	_hoops_CSRGR->_hoops_RSHH = _hoops_CCC;
	glStencilOp(
		GL_KEEP, /* _hoops_AA _hoops_ISAP _hoops_RPP _hoops_APSP _hoops_RPGP _hoops_ISHS (_hoops_PGGAC _hoops_CCA _hoops_APSP _hoops_RPGP _hoops_PSAP) */
		GL_KEEP, /* _hoops_AA _hoops_ISAP _hoops_RPP _hoops_HCH _hoops_RPGP _hoops_ISHS */
		GL_INCR  /* _hoops_GPISR _hoops_APSP _hoops_SRHR _hoops_RPP _hoops_HCH _hoops_RPGP _hoops_PCGGR */
	);
	/* _hoops_APSP _hoops_RPGP _hoops_SHR _hoops_HHHH (_hoops_PSHR _hoops_GAR _hoops_APSP _hoops_RPGP _hoops_PSAP) */
	ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
	glStencilFunc (GL_EQUAL, 0x0080, 0x0080);
	_hoops_RPAP (_hoops_CSRGR, GL_FALSE);
	ENSURE_DEPTH_MASK (_hoops_CSRGR, GL_FALSE);
	_hoops_PPRGC (_hoops_CSRGR, 0);
	HD_Draw_Deferred_3D_Geometry (list, true);
	_hoops_PPRGC (_hoops_CSRGR, _hoops_PSSRC);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	_hoops_RPAP (_hoops_CSRGR, GL_TRUE);
    ENSURE_SCISSOR_SET (_hoops_CSRGR, _hoops_IAAIP, _hoops_CAAIP, width, height);

	/* _hoops_HPPP _hoops_IGAAH */
	glClearColor (0, 0, 1.0f, 0);
	glDisable (GL_TEXTURE_RECTANGLE_ARB);
	for (i=0; i<_hoops_RIRAH; i++) {
		void *			_hoops_CGAAH = null;
		int				result = 0;

		glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		DEBUG_FLUSH();

		/* _hoops_ASSS _hoops_GRR _hoops_AIR _hoops_IS _hoops_SHH _hoops_RHIAA _hoops_RGAR _hoops_GAR _hoops_AHPH _hoops_IACH _hoops_GAR _hoops_SR _hoops_SGAAH */
		glStencilFunc (GL_LESS, i | 0x80, 0x00FF);
		_hoops_CSRGR->_hoops_ISSRC = i;

		_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
		if (_hoops_AIRAH > 0)
			_hoops_CGAAH = _hoops_AACGH (list->nr, false);

		_hoops_PPRGC (_hoops_CSRGR, 0);
		_hoops_CSRGR->_hoops_PSGRC = true;
		HD_Draw_Deferred_3D_Geometry (list, false);
		DEBUG_FLUSH();
		ENSURE_LINE_SMOOTH(_hoops_CSRGR, false);
		_hoops_PPRGC (_hoops_CSRGR, _hoops_PSSRC);
		ENSURE_VIEWPORT_SET (_hoops_CSRGR, _hoops_IAAIP, _hoops_CAAIP, width, height);
		ENSURE_SCISSOR_SET (_hoops_CSRGR, _hoops_IAAIP, _hoops_CAAIP, width, height);

		if (_hoops_CGAAH) {
			_hoops_PACGH (list->nr, _hoops_CGAAH);
			result = _hoops_IACGH (list->nr, _hoops_CGAAH);
			_hoops_CACGH (list->nr, _hoops_CGAAH);
		}

		/* _hoops_ASAC _hoops_PIRAI */
		_hoops_IPRGC(_hoops_CSRGR, _hoops_PSSRC, GL_TEXTURE_RECTANGLE_ARB, _hoops_CPRRR[i]);
		glCopyTexSubImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, _hoops_IAAIP, _hoops_CAAIP, width, height);
		dc->_hoops_IGGI->_hoops_RPRH++;
		_hoops_HSSRC[i] = true;

		_hoops_IPRGC(_hoops_CSRGR, _hoops_PSSRC, GL_TEXTURE_RECTANGLE_ARB, _hoops_IPRRR[0]);
		if (i < _hoops_RIRAH-1) {/* _hoops_GA'_hoops_RA _hoops_RRP _hoops_RPP _hoops_CGHI _hoops_ASAH */
			/* _hoops_ASAC _hoops_SSH */
			glCopyTexSubImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, _hoops_IAAIP, _hoops_CAAIP, width, height);
			dc->_hoops_IGGI->_hoops_RPRH++;
		}

		if (result < _hoops_AIRAH)
			break;

		if (i == 0) {
			/* _hoops_SRS _hoops_ASAH _hoops_RRRS _hoops_HCAGR, _hoops_HIASR _hoops_RRP _hoops_RH _hoops_IHH '_hoops_SSH' _hoops_RPGP */
			glEnable (GL_FRAGMENT_PROGRAM_ARB);
			glEnable (GL_TEXTURE_RECTANGLE_ARB);
		}
	}
    glDisable(GL_FRAGMENT_PROGRAM_ARB);
	(*_hoops_CSRGR->glBindProgramARB) (GL_FRAGMENT_PROGRAM_ARB, 0); /* _hoops_RSIAH */
	_hoops_RSIGC (_hoops_CSRGR);

	_hoops_CSRGR->_hoops_PSGRC = false;


	/* _hoops_CPRP _hoops_CCAH _hoops_RRRH _hoops_IAPR _hoops_GIGR _hoops_IS _hoops_HGCR _hoops_RH _hoops_GHPP */
	glMatrixMode (GL_PROJECTION);
	glPushMatrix ();
	glLoadIdentity ();
	glOrtho (0, width, 0, height, -1, 1);
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glLoadIdentity();

    ENSURE_VIEWPORT_SET (_hoops_CSRGR, _hoops_IAAIP, _hoops_CAAIP, width, height);
    ENSURE_SCISSOR_SET (_hoops_CSRGR, _hoops_IAAIP, _hoops_CAAIP, width, height);
	_hoops_GGIGC (_hoops_CSRGR);

	glClear(GL_COLOR_BUFFER_BIT);
	DEBUG_FLUSH();

#if (_hoops_PSSRC != 0)
	//_hoops_HA _hoops_CICA _hoops_ISSC _hoops_IS _hoops_HH _hoops_HPI 0 (_hoops_RPP _hoops_SR _hoops_GSAHA'_hoops_RA _hoops_IIH _hoops_AIAH)
	glDisable (GL_TEXTURE_RECTANGLE_ARB);
	_hoops_IPRGC(_hoops_CSRGR, _hoops_PSSRC, GL_TEXTURE_RECTANGLE_ARB, 0);
	_hoops_PPRGC (_hoops_CSRGR, 0);
	glEnable (GL_TEXTURE_RECTANGLE_ARB);
#endif

	glMatrixMode (GL_TEXTURE);
	glPushMatrix ();
	glLoadIdentity ();
	glMatrixMode (GL_MODELVIEW);

	glDisable (GL_DEPTH_TEST);
	_hoops_HCIGC (_hoops_CSRGR);
	ENSURE_CULLING_OFF (_hoops_CSRGR);
	_hoops_SCIGC (_hoops_CSRGR);
	ENSURE_BLEND_FUNC (_hoops_CSRGR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ENSURE_TEXTURE_ENV_MODE (_hoops_CSRGR, GL_REPLACE, 0);
	/* _hoops_CCGSP _hoops_IGHP _hoops_HGGAC */
	ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
	for (i=_hoops_RIRAH; i>=0; i--) {
		if (_hoops_HSSRC[i]) {
			_hoops_IPRGC(_hoops_CSRGR, 0, GL_TEXTURE_RECTANGLE_ARB, _hoops_CPRRR[i]);
			glBegin(GL_QUADS);
				glTexCoord2f(0, 0);				glVertex2f(0, 0);
				glTexCoord2f(0, height);		glVertex2f(0, height);
				glTexCoord2f(width, height);	glVertex2f(width, height);
				glTexCoord2f(width, 0);			glVertex2f(width, 0);
			glEnd();
		}
		/* _hoops_HCR _hoops_HHHH _hoops_RAS _hoops_RH _hoops_SRS _hoops_CGH _hoops_SHH _hoops_CCA _hoops_IGGAC _hoops_PPP */
		ENSURE_TRANSPARENCY (_hoops_CSRGR, true);
		DEBUG_FLUSH();
	}
	glDisable (GL_TEXTURE_RECTANGLE_ARB);
	_hoops_IPRGC(_hoops_CSRGR, 0, GL_TEXTURE_RECTANGLE_ARB, 0);
	ENSURE_TRANSPARENCY (_hoops_CSRGR, false);
	glEnable (GL_DEPTH_TEST);

	glMatrixMode (GL_TEXTURE);
	glPopMatrix ();
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();

	/* _hoops_HRCI _hoops_CIPH */
	_hoops_RSIGC (_hoops_CSRGR);
	FORCE_BLEND_FUNC (_hoops_CSRGR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_hoops_SICGC (_hoops_CSRGR);
	_hoops_ACCGC (_hoops_CSRGR);
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_ICGRC (_hoops_CSRGR);
	_hoops_CSRGR->_hoops_CSC._hoops_GPIR = _hoops_CAHSR::_hoops_SAHSR;

	/* _hoops_HCR _hoops_CPHR _hoops_CCA _hoops_RGR _hoops_HIGR _hoops_IIGR _hoops_RRH _hoops_IGCGA */
	HD_Free_Deferred_3D_Geometry (list);
	_hoops_CSRGR->_hoops_GIIGC = false;
	_hoops_CPPRR (_hoops_CSRGR, false); //_hoops_IRHS _hoops_IS _hoops_RCPS _hoops_RAS _hoops_RH _hoops_CGGAC = _hoops_RCPP
}


#include "hic_calls.h"

local void * _hoops_IGHGR(
	Net_Rendition const & nr,
	long					request,
	void alter				*pointer,
	POINTER_SIZED_INT		_hoops_ISPI,
	POINTER_SIZED_INT		_hoops_CSPI,
	POINTER_SIZED_INT		_hoops_SSPI,
	POINTER_SIZED_INT		_hoops_SGHI,
	float f1,
	float f2,
	float _hoops_CGHGR,
	float _hoops_SGHGR)
{
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);

	UNREFERENCED(_hoops_CSPI);
	UNREFERENCED(_hoops_SSPI);
	UNREFERENCED(_hoops_SGHI);
	UNREFERENCED(f1);
	UNREFERENCED(f2);
	UNREFERENCED(_hoops_CGHGR);
	UNREFERENCED(_hoops_SGHGR);

	switch (request) {

		case _hoops_GRHGR: {
			return (void*)(POINTER_SIZED_INT)_hoops_CSRGR->window_width;
		}_hoops_HHHI;

		case _hoops_RRHGR: {
			return (void*)(POINTER_SIZED_INT)_hoops_CSRGR->window_height;
		}_hoops_HHHI;

		case _hoops_HPCCH: {
			return (void*)(POINTER_SIZED_INT)_hoops_CSRGR->_hoops_SRRRR;
		}_hoops_HHHI;

#ifdef WGL_DRIVER
		case _hoops_IPCCH: {
			return (void*)(POINTER_SIZED_INT)_hoops_CSRGR->hDC;
		}_hoops_HHHI;
#endif

		case _hoops_CPCCH: {
			Tristrip const *ts=(Tristrip const *)pointer;

			_hoops_GACR		*dl;

			if ((dl = ts->_hoops_GAHA) != null) do {
				if (dl->_hoops_GHRI == nr->_hoops_SRA->_hoops_GHRI) {
					OGL_Display_List *	odl = (OGL_Display_List *)dl->list;

					if (odl != null)
						return (void*)(POINTER_SIZED_INT)(odl->item.geometry.id != _hoops_RSARR);
				}
			} while ((dl = dl->next) != null);

			return (void*)(POINTER_SIZED_INT)false;
		}_hoops_HHHI;

		case _hoops_SPCCH: {
			_hoops_PPRGC(_hoops_CSRGR, _hoops_ISPI);
		} break;

		case _hoops_GHCCH: {
			_hoops_RSGRC (_hoops_CSRGR, GL_TEXTURE_2D, _hoops_ISPI);
		} break;

		case _hoops_RHCCH: {
			_hoops_AARRC (_hoops_CSRGR, _hoops_ISPI);
		} break;

		case _hoops_AHCCH: {
			_hoops_SGGAC (_hoops_CSRGR, _hoops_ISPI);
		} break;

		case _hoops_PHCCH: {
			/* _hoops_SRHIR _hoops_RH _hoops_CICRR _hoops_IS _hoops_SRPS _hoops_RH _hoops_HH _hoops_CRSRR */
			Image const * image = (Image const *)pointer;
			if (!image->_hoops_GAHA || !image->_hoops_GAHA->list)
				return 0;
			_hoops_GACR *dl = image->_hoops_GAHA;
			OGL_Display_List * odl = (OGL_Display_List *)dl->list;
			int _hoops_GRRA = _hoops_CSRGR->_hoops_CSC._hoops_GRGAC;
			_hoops_IPRGC(_hoops_CSRGR, _hoops_GRRA, GL_TEXTURE_2D, odl->item.texture.id);
		} break;

		case _hoops_HHCCH:
		case _hoops_IHCCH: {
			/* _hoops_IPS _hoops_RH _hoops_AGPGI _hoops_PAR _hoops_SSH _hoops_SRHR _hoops_SRGR _hoops_CRGR _hoops_IRS _hoops_HH.
			 * _hoops_GCA _hoops_GCGH _hoops_IH _hoops_CSCRC */
			if (!_hoops_CSRGR->_hoops_PPPGC)
				return 0;
			GLuint id = V2I (pointer);
			long l = 0;
			long b = 0;
			long w = _hoops_CSRGR->window_width;
			long h = _hoops_CSRGR->window_height;
			int _hoops_AHCGR = 0;
			GLint format, _hoops_CCSGC;

			if (request == _hoops_HHCCH) {
				format = GL_RGBA;
			    _hoops_CCSGC = GL_RGBA8;
			}
			else {
				ASSERT (request == _hoops_IHCCH);
				format = GL_DEPTH_COMPONENT;
			    if (_hoops_CSRGR->_hoops_IGARR == 16)
				    _hoops_CCSGC = GL_DEPTH_COMPONENT16_ARB;
			    else
				    _hoops_CCSGC = GL_DEPTH_COMPONENT24_ARB;
			}
			glEnable (GL_TEXTURE_RECTANGLE_ARB);
			if (id == 0) {
				GLuint *buffer = null;
				glGenTextures (1, &id);
				_hoops_IPRGC(_hoops_CSRGR, _hoops_AHCGR, GL_TEXTURE_RECTANGLE_ARB, id);
				glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri (GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				//_hoops_RRGAC _hoops_IHAGH _hoops_SGS _hoops_SR _hoops_HS _hoops_IS _hoops_CCPP _hoops_PCCP _hoops_RHPA _hoops_SRHR, _hoops_HIH _hoops_HHH _hoops_APAC
				//_hoops_SCCHH _hoops_RPP _hoops_SR _hoops_RIH _hoops_IRAP _hoops_IH _hoops_IRS _hoops_HH _hoops_ARRGR _hoops_CSCR.  
			    ZALLOC_ARRAY_CACHED (buffer, w*h, GLuint);
				glTexImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, _hoops_CCSGC,
						w, h, 0,
						format, GL_UNSIGNED_BYTE, buffer);
				FREE_ARRAY (buffer, w*h, GLuint); 
			}
			else
				_hoops_IPRGC(_hoops_CSRGR, _hoops_AHCGR, GL_TEXTURE_RECTANGLE_ARB, id);
			glCopyTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, l, b, w, h);
			_hoops_CSRGR->_hoops_CSC._hoops_SGAGC[_hoops_AHCGR] = _hoops_RSARR;
			glDisable (GL_TEXTURE_RECTANGLE_ARB);
			return I2V(id);
		} /*_hoops_IHSA;*/

 		case _hoops_PPHGR:
 		case _hoops_APHGR: {
			float *matrix		= (float *) pointer;

			_hoops_GGGH(_hoops_CSRGR, nr);
			_hoops_AIIGC(_hoops_CSRGR, nr);
			glMatrixMode (GL_PROJECTION);
			glGetFloatv (GL_PROJECTION_MATRIX, matrix);
			glMatrixMode (GL_MODELVIEW);
		} break;

 		case _hoops_CHCCH: {
			_hoops_CSRGR->_hoops_CSC._hoops_GPIR._hoops_HRIR.r = 255;
			_hoops_CSRGR->_hoops_CSC._hoops_GPIR._hoops_HRIR.g = 255;
			_hoops_CSRGR->_hoops_CSC._hoops_GPIR._hoops_HRIR.b = 255;
			_hoops_CSRGR->_hoops_CSC._hoops_GPIR._hoops_HRIR.a = 0;
			glClearColor (1, 1, 1, 0);
			glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		} break;

		default:break;
	}
	return 0;
}


#endif /* _hoops_PAPR(_hoops_ARGAC) || _hoops_PAPR(_hoops_PRGAC) */



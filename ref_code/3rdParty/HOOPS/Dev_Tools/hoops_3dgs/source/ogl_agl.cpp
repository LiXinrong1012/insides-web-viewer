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
 * $Id: obf_tmp.txt 1.163 2010-12-10 03:32:35 covey Exp $
 */

#include "hoops.h"
#include "hd_proto.h"

#ifdef OSX_SYSTEM     /* _hoops_SR'_hoops_ASAR _hoops_GPP _hoops_SSIGI */
#ifndef OPENGL_DRIVER 

/*
 * _hoops_APICR _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_OpenGL_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED(request_info);
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "opengl");
}

#else /* _hoops_SR'_hoops_ASAR _hoops_GPP _hoops_SSIGI _hoops_PPR _hoops_HHPS _hoops_GGR _hoops_RH _hoops_SRCIA _hoops_RHPP */

/*_hoops_CPCHR _hoops_IH _hoops_PRIPC*/
local void * MyAGLGetProcAddress(const char *_hoops_SCPGA);

#if 1
#  define agl_ctx  _hoops_CSRGR->curr_AGLContext
#  include <AGL/aglMacro.h>
#  define AGLM(x) x
#else
#  define AGLM(x)
#endif

#define AGL_DRIVER
#define DECLARE_OGL_PROTOTYPES
#include "ogl.cpp"
#include "qtzdrive.cpp"

static EventHandlerRef _hoops_HRIPC = 0;
static EventHandlerUPP _hoops_IRIPC = 0;

/*
 * _hoops_PGAA
 */
local void
choose_pixel_format (Display_Context alter * dc)
{
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	AGLPixelFormat pixel_format;
	GLint _hoops_CRIPC[32];
	GLint value;
	GLint accum_buff_size = 0;
	GLint _hoops_SRIPC = 0;
	GLint green_accum_size = 0;
	GLint blue_accum_size = 0;
	GLint alpha_accum_size = 0;
	GLint _hoops_AIPGA = 0;
	int i = 0;

	_hoops_CRIPC[i++] = AGL_RGBA;
	if (dc->options._hoops_SRRRR) _hoops_CRIPC[i++] = AGL_DOUBLEBUFFER;
	_hoops_CRIPC[i++] = AGL_DEPTH_SIZE;
	_hoops_CRIPC[i++] = 16;
	if (dc->options._hoops_RIPGA && dc->options._hoops_AIPGA != 0) {
		_hoops_CRIPC[i++] = AGL_SAMPLE_BUFFERS_ARB;
		_hoops_CRIPC[i++] = 1;
		_hoops_CRIPC[i++] = AGL_SAMPLES_ARB;
		if (dc->options._hoops_AIPGA < 0)
			_hoops_CRIPC[i++] = 2;
		else
			_hoops_CRIPC[i++] = dc->options._hoops_AIPGA;
	}

#ifndef AGL_GENERIC_RENDERER_ID
#define AGL_GENERIC_RENDERER_ID 0x00020200
#endif
	/* _hoops_GSRRI _hoops_ICCGR _hoops_IIHGC _hoops_PAH'_hoops_RA _hoops_AA _hoops_SRGAC, _hoops_HIS _hoops_PHHS _hoops_SSPC _hoops_RH _hoops_IAGC
		_hoops_IS _hoops_HHSA _hoops_ICCGR */
	if (dc->options._hoops_IRARR & _hoops_ARRAH &&
	    _hoops_CSRGR->_hoops_PIGRR != _hoops_IPSGR) {
		_hoops_CRIPC[i++] = AGL_RENDERER_ID;
		_hoops_CRIPC[i++] = AGL_GENERIC_RENDERER_ID;
	}

	if (dc->options._hoops_PIPGA) {
		_hoops_CRIPC[i++] = AGL_STENCIL_SIZE;
		_hoops_CRIPC[i++] = 1;
	}

	_hoops_CRIPC[i++] = AGL_ACCUM_RED_SIZE;
	_hoops_CRIPC[i++] = 8;
	_hoops_CRIPC[i++] = AGL_ACCUM_GREEN_SIZE;
	_hoops_CRIPC[i++] = 8;
	_hoops_CRIPC[i++] = AGL_ACCUM_BLUE_SIZE;
	_hoops_CRIPC[i++] = 8;
	_hoops_CRIPC[i++] = AGL_ACCUM_ALPHA_SIZE;
	_hoops_CRIPC[i++] = 8;

	_hoops_CRIPC[i++] = AGL_NONE;

	pixel_format = aglChoosePixelFormat(NULL, 0, _hoops_CRIPC);

	if (!pixel_format) {
		i=0;
		_hoops_CRIPC[i++] = AGL_RGBA;
		if (dc->options._hoops_SRRRR) _hoops_CRIPC[i++] = AGL_DOUBLEBUFFER;
		_hoops_CRIPC[i++] = AGL_DEPTH_SIZE;
		_hoops_CRIPC[i++] = 16;
		_hoops_CRIPC[i++] = AGL_NONE;

		pixel_format = aglChoosePixelFormat(NULL, 0, _hoops_CRIPC);
	}

	if (!pixel_format) {
		i=0;
		_hoops_CRIPC[i++] = AGL_RGBA;
		_hoops_CRIPC[i++] = AGL_DOUBLEBUFFER;
		_hoops_CRIPC[i++] = AGL_DEPTH_SIZE;
		_hoops_CRIPC[i++] = 16;
		_hoops_CRIPC[i++] = AGL_NONE;

		pixel_format = aglChoosePixelFormat(NULL, 0, _hoops_CRIPC);
	}

	if (!pixel_format) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_SET_ATTRIBUTE, "aglChoosePixelFormat Failed");
		HD_Kill_Driver (dc);
		return;
	}

	/*_hoops_HGPGA->_hoops_GAHAC = _hoops_GAIPC();*/
	
	if (BIT(dc->options._hoops_IRARR, _hoops_APGAC)) {
		if (dc->options._hoops_ISPRP != 0) {
			_hoops_CSRGR->curr_AGLContext = (AGLContext) dc->options._hoops_ISPRP;
		}
		else{
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_SET_ATTRIBUTE, "Invalid QGLContext parameter");
			HD_Kill_Driver (dc);
			return;
		}
	}
	else
		_hoops_CSRGR->curr_AGLContext = aglCreateContext(pixel_format, NULL);
	

	if (aglDescribePixelFormat(pixel_format, AGL_BACKING_STORE, &value)) {
		if (value) {
			dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;
		}else{
			dc->_hoops_PGCC._hoops_CHHSR = _hoops_ACPGA;
		}
	}
	
	/* _hoops_SSS _hoops_GGSR _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_RH _hoops_AAHRP _hoops_SRHR _hoops_CR _hoops_SR _hoops_HS _hoops_RH _hoops_AIR _hoops_RPCC */
	aglDescribePixelFormat(pixel_format, AGL_ACCUM_RED_SIZE, &_hoops_SRIPC);
	aglDescribePixelFormat(pixel_format, AGL_ACCUM_GREEN_SIZE, &green_accum_size);
	aglDescribePixelFormat(pixel_format, AGL_ACCUM_BLUE_SIZE, &blue_accum_size);
	aglDescribePixelFormat(pixel_format, AGL_ACCUM_ALPHA_SIZE, &alpha_accum_size);
	accum_buff_size = _hoops_SRIPC + green_accum_size + blue_accum_size + alpha_accum_size;
	_hoops_CSRGR->accumulation_bits = accum_buff_size;
	
	aglDescribePixelFormat(pixel_format, AGL_SAMPLES_ARB, &_hoops_AIPGA);
	_hoops_CSRGR->_hoops_PHHGC = (_hoops_AIPGA != 0);
	_hoops_CSRGR->_hoops_AIPGA = _hoops_AIPGA;

	aglDestroyPixelFormat(pixel_format);

	if (!_hoops_CSRGR->curr_AGLContext) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_SET_ATTRIBUTE, "aglCreateContext Failed");
		HD_Kill_Driver (dc);
		return;
	}

} /* _hoops_RSGR _hoops_API '_hoops_HSRS _hoops_AIR _hoops_RPCC' */


/*
 * _hoops_PGAA
 */
local void
identify_renderer (Display_Context alter * dc) {

	OGLData alter *_hoops_CSRGR = OGLD (dc);
	char const *test;
	char const *version;

	test = (char const *) glGetString (GL_RENDERER);
	if (test) {
		if (_hoops_CSRGR->_hoops_PRARR)
			HI_Free_Driver_Config(_hoops_CSRGR->_hoops_PRARR);
			version = (char const *) glGetString (GL_VERSION);
			if (version)
				version = "*";

			_hoops_RGAIR(dc->_hoops_PGCC._hoops_GSPGH);
			_hoops_RGAIR(dc->_hoops_PGCC._hoops_RSPGH);
			HI_Copy_Chars_To_Name(test, &dc->_hoops_PGCC._hoops_GSPGH);
			HI_Copy_Chars_To_Name(version, &dc->_hoops_PGCC._hoops_RSPGH);
			dc->_hoops_PGCC._hoops_PRARR = _hoops_CSRGR->_hoops_PRARR = HI_Lookup_Driver_Config(dc->_hoops_RIGC, "opengl", test, version, true, _hoops_RSPRH);
	}

	if (!BIT(_hoops_CSRGR->_hoops_PRARR->flags, _hoops_IIIPP)) {
		dc->_hoops_PGCC.driver_type = _hoops_SCGGC;
		_hoops_CSRGR->_hoops_GSGRR = false;
	}else {
		dc->_hoops_PGCC.driver_type = _hoops_CCGGC;
		_hoops_CSRGR->_hoops_GSGRR = true;
	}

}

local void
unset_ogl (Display_Context const * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	aglSetCurrentContext(NULL);
	aglSetDrawable(_hoops_CSRGR->curr_AGLContext, NULL);
	//_hoops_RAIPC(_hoops_HGPGA->_hoops_GAHAC, _hoops_IHHAH);
	aglDestroyContext(_hoops_CSRGR->curr_AGLContext);
	_hoops_CSRGR->curr_AGLContext = 0;

	if (_hoops_CSRGR->prev_AGLContext) {
		aglSetCurrentContext (_hoops_CSRGR->prev_AGLContext);
		_hoops_CSRGR->prev_AGLContext = 0;
	}

	if (_hoops_CSRGR->prev_GrafPtr) {
		SetPort (_hoops_CSRGR->prev_GrafPtr);
		_hoops_CSRGR->prev_GrafPtr = 0;
	}
}


/*_hoops_CPCHR*/
local void
free_outer_window (Display_Context const * dc);

local void
stop_device (Display_Context alter * dc);



/*
 * _hoops_SRAC
 */
local void
finish_picture (Net_Rendition const &  nr,
				bool swap_buffers) 
{
	Display_Context const *dc = nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLNRD (nr);

	if (_hoops_CSRGR->_hoops_SARGC == _hoops_RPRGC)
		_hoops_GHRGC(_hoops_CSRGR);
	ENSURE_SCISSOR_OFF(_hoops_CSRGR);

	glFlush ();
	if (dc->_hoops_RIGC->_hoops_HCPGR != 0)
		glFinish();

    if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		int i,j;
		int w = _hoops_CSRGR->_hoops_IHGRR->width;
		int h = _hoops_CSRGR->_hoops_IHGRR->height;
		_hoops_AIGH *_hoops_AAIPC;

		if (!BIT (dc->flags, _hoops_SAISR))	// _hoops_PAHH _hoops_IASRH _hoops_ISHP _hoops_RH _hoops_RHPP
			return;

		if (!_hoops_CSRGR->output_image_scratch) {
			ALLOC_ARRAY(_hoops_AAIPC, w*h, _hoops_AIGH);
			_hoops_CSRGR->output_image_scratch = _hoops_AAIPC;
		}
		_hoops_AAIPC = (_hoops_AIGH alter *) _hoops_CSRGR->output_image_scratch;

		if (_hoops_CSRGR->_hoops_SRRRR)
				glReadBuffer(GL_BACK);
		else
				glReadBuffer(GL_FRONT);

		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glPixelStorei(GL_PACK_ROW_LENGTH, 0);
		glReadPixels (0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, _hoops_AAIPC);
		_hoops_AAIPC = (_hoops_AIGH alter *) _hoops_CSRGR->output_image_scratch;

		if (_hoops_CSRGR->_hoops_IHGRR->format == Image_RGBA32 
#ifdef RGB32_ORDER_RGBA
			|| _hoops_CSRGR->_hoops_IHGRR->format == _hoops_CSGSP 
#endif
		) {
			_hoops_AIGH *_hoops_PAIPC;  
		    _hoops_PAIPC = (_hoops_AIGH alter *)_hoops_CSRGR->_hoops_IHGRR->_hoops_PHGH;
			for (i = 0 ; i < h ; i++)
				_hoops_AIGA(_hoops_AAIPC + w*i, w, _hoops_AIGH, _hoops_PAIPC + w*(h-i-1));
		}
		else 
		if (_hoops_CSRGR->_hoops_IHGRR->format == _hoops_CSGSP) {
			RGBAS32 *_hoops_PAIPC;  

			for (i = 0 ; i < h ; i++) {
		        _hoops_PAIPC = (RGBAS32 alter *)_hoops_CSRGR->_hoops_IHGRR->_hoops_PHGH + w*(h-i-1);
				for (j = 0 ; j < w ; j++) {
					_hoops_PAIPC->r = _hoops_AAIPC->r;
					_hoops_PAIPC->g = _hoops_AAIPC->g;
					_hoops_PAIPC->b = _hoops_AAIPC->b;
					_hoops_PAIPC->a = _hoops_AAIPC->a;
					_hoops_AAIPC++;
					_hoops_PAIPC++;
				}
			}
		}
		else 
		if (_hoops_CSRGR->_hoops_IHGRR->format == _hoops_HRSRH) {
			_hoops_IRSRH *_hoops_PAIPC;  
			for (i = 0 ; i < h ; i++) {
		        _hoops_PAIPC = (_hoops_IRSRH alter *)_hoops_CSRGR->_hoops_IHGRR->_hoops_PHGH + w*(h-i-1);
				for (j = 0 ; j < w ; j++) {
					_hoops_PAIPC->r = _hoops_AAIPC->r;
					_hoops_PAIPC->g = _hoops_AAIPC->g;
					_hoops_PAIPC->b = _hoops_AAIPC->b;
					_hoops_PAIPC->a = _hoops_AAIPC->a;
					_hoops_AAIPC++;
					_hoops_PAIPC++;
				}
			}
		}
		else 
		if (_hoops_CSRGR->_hoops_IHGRR->format == _hoops_HHGH) {
			_hoops_SHGH *_hoops_PAIPC;  
			for (i = 0 ; i < h ; i++) {
		        _hoops_PAIPC = (_hoops_SHGH alter *)_hoops_CSRGR->_hoops_IHGRR->_hoops_PHGH + w*(h-i-1);
				for (j = 0 ; j < w ; j++) {
					_hoops_PAIPC->r = _hoops_AAIPC->r;
					_hoops_PAIPC->g = _hoops_AAIPC->g;
					_hoops_PAIPC->b = _hoops_AAIPC->b;
					_hoops_AAIPC++;
					_hoops_PAIPC++;
				}
			}
		}
	}
	else {
		if (swap_buffers && 
			_hoops_CSRGR->_hoops_SRRRR  && 
			!BIT(dc->flags, _hoops_CHSI)) {
			aglSwapBuffers (_hoops_CSRGR->curr_AGLContext);
		}
	}

	if (_hoops_CSRGR->_hoops_PISGC) {
		delete _hoops_CSRGR->_hoops_PISGC;
		_hoops_CSRGR->_hoops_PISGC = null;
	}
}


/*
 * _hoops_SRAC
 */
local void
init_picture (Net_Rendition const &  nr) {
	OGLData alter *_hoops_CSRGR = OGLNRD (nr);
	int i;

	if (nr->_hoops_SRA->_hoops_RIGC->_hoops_HCPGR == 0)
		glFinish();

	FORCE_DRAW_MODE (_hoops_CSRGR, _hoops_CSRGR->_hoops_CSC._hoops_GGAGC);
	FORCE_SCISSOR_OFF(_hoops_CSRGR);
	for (i = 0 ; i < OGL_MAX_TEXTURE_UNITS ; i++)
		_hoops_SGGAC(_hoops_CSRGR, i);
	_hoops_HAHAC(_hoops_CSRGR);
	if (_hoops_CSRGR->_hoops_SHCGC)
		_hoops_IIPAC(_hoops_CSRGR);
	_hoops_PHHAC(_hoops_CSRGR, _hoops_CSRGR->_hoops_CSC._hoops_CGAGC);

	// [#9627] _hoops_IRRPH _hoops_RGCH _hoops_HIRGR _hoops_IHAH _hoops_IS _hoops_GACHR _hoops_GGSR _hoops_IIGR _hoops_RGAS _hoops_CCA _hoops_IAPRR
	_hoops_CSRGR->_hoops_CSC._hoops_PHIGC = _hoops_RSARR;
	_hoops_CSRGR->_hoops_CSC._hoops_APH = _hoops_RSARR;
	_hoops_CAAGC(_hoops_CSRGR);
	_hoops_AAHAC(_hoops_CSRGR);
	INVALIDATE_PIXEL_UNPACK_ALIGNMENT(_hoops_CSRGR);
	_hoops_CSRGR->_hoops_PPAGC = false;
	if (BIT(nr->transform_rendition->flags, _hoops_PIHIP)) {
		FORCE_DEPTH_FUNCTION(_hoops_CSRGR, GL_GREATER);
	}
	else {
		FORCE_DEPTH_FUNCTION(_hoops_CSRGR, GL_LEQUAL);
	}
	_hoops_AHPRR(_hoops_CSRGR,!nr->_hoops_IRR->_hoops_GIRC);

	_hoops_CSRGR->_hoops_RIRGC =
		XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_SPOTLIGHT_TEXTURE) ||
		BIT(nr->_hoops_SRA->options.flags, Drivo_VERTEX_SPOTLIGHT);
}

/*_hoops_CPCHR*/
local void
check_events (OGLData alter * _hoops_CSRGR);

/*
 * _hoops_SRAC
 */
local void
finish_update (Display_Context const * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	if (!BIT(dc->flags, _hoops_SAISR))
		return;

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR)
		if (!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH))
			check_events (_hoops_CSRGR);

	if (_hoops_CSRGR->prev_AGLContext) {
		aglSetCurrentContext (_hoops_CSRGR->prev_AGLContext);
		_hoops_CSRGR->prev_AGLContext = 0;
	}

	if (_hoops_CSRGR->prev_GrafPtr) {
		SetPort (_hoops_CSRGR->prev_GrafPtr);
		_hoops_CSRGR->prev_GrafPtr = 0;
	}

}


/*
 * _hoops_SRAC
 */
local void
init_update (Display_Context const * dc) 
{
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	OSStatus err;
	int _hoops_HAIPC = 0;

	_hoops_CSRGR->prev_AGLContext = 0;

	if (BIT(dc->options._hoops_IRARR, _hoops_APGAC)) {
		_hoops_HAIPC = -1;
	}

	if (!BIT(dc->flags, _hoops_SAISR))
		return;

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR) {
		if (!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH))
			check_events (_hoops_CSRGR);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		_hoops_CSRGR = OGLD (dc);

		if (!_hoops_CSRGR) 
			return;
	}
	invalidate_cache (_hoops_CSRGR);

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		int _hoops_HHRAR = 0;
		if (!aglSetPBuffer(_hoops_CSRGR->curr_AGLContext, _hoops_CSRGR->pbuffer, 0, 0, _hoops_HHRAR)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
				"Unable to set OpenGL pbuffer rendering context in ogl_agl:init update");
			HD_Kill_Driver (dc);
		}		
	}
	else {

		int * _hoops_SIGHP = _hoops_CSRGR->_hoops_CSPRP;
		GLint bufferRect[4];
		Rect rect;

		if (!_hoops_CSRGR->window || !IsValidWindowPtr(_hoops_CSRGR->window))
			return;
		_hoops_CSRGR->prev_GrafPtr = 0;
		GetPort (&_hoops_CSRGR->prev_GrafPtr);

#define OUTER_OVERRIDE_X 0
#define OUTER_OVERRIDE_Y 1
#define OUTER_OVERRIDE_W 2
#define _hoops_IAIPC 3
#define _hoops_CAIPC 4
#define INNER_OVERRIDE_Y 5
#define INNER_OVERRIDE_W 6
#define _hoops_SAIPC 7

		if (_hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR && _hoops_SIGHP) {

			rect.left	= _hoops_SIGHP[OUTER_OVERRIDE_X] + _hoops_SIGHP[_hoops_CAIPC];
			rect.right	= rect.left + _hoops_SIGHP[INNER_OVERRIDE_W]; 

			rect.bottom = _hoops_SIGHP[OUTER_OVERRIDE_Y] + _hoops_SIGHP[_hoops_IAIPC] - _hoops_SIGHP[INNER_OVERRIDE_Y];
			rect.top	= rect.bottom - _hoops_SIGHP[_hoops_SAIPC];

		}else{
			err = GetWindowBounds (_hoops_CSRGR->window, kWindowContentRgn, &rect);
		}

		if (	(rect.right-rect.left != _hoops_CSRGR->window_width) || 
			(rect.bottom-rect.top != _hoops_CSRGR->window_height) ||
			(_hoops_SIGHP && (
			(_hoops_CSRGR->_hoops_IPAAC[OUTER_OVERRIDE_X] != _hoops_SIGHP[OUTER_OVERRIDE_X]) ||
			(_hoops_CSRGR->_hoops_IPAAC[OUTER_OVERRIDE_Y] != _hoops_SIGHP[OUTER_OVERRIDE_Y]) ||
			(_hoops_CSRGR->_hoops_IPAAC[OUTER_OVERRIDE_W] != _hoops_SIGHP[OUTER_OVERRIDE_W]) ||
			(_hoops_CSRGR->_hoops_IPAAC[_hoops_IAIPC] != _hoops_SIGHP[_hoops_IAIPC]) ||
			(_hoops_CSRGR->_hoops_IPAAC[_hoops_CAIPC] != _hoops_SIGHP[_hoops_CAIPC]) ||
			(_hoops_CSRGR->_hoops_IPAAC[INNER_OVERRIDE_Y] != _hoops_SIGHP[INNER_OVERRIDE_Y]) ||
			(_hoops_CSRGR->_hoops_IPAAC[INNER_OVERRIDE_W] != _hoops_SIGHP[INNER_OVERRIDE_W]) ||
			(_hoops_CSRGR->_hoops_IPAAC[_hoops_SAIPC] != _hoops_SIGHP[_hoops_SAIPC]))) 
		) {

			_hoops_CSRGR->window_width = rect.right-rect.left;
			_hoops_CSRGR->window_height = rect.bottom-rect.top;

			if (_hoops_SIGHP) {
				int i = 0;
				for (i = 0; i < 8; i++)
					_hoops_CSRGR->_hoops_IPAAC[i] = _hoops_SIGHP[i];
			}

			_hoops_CSRGR->yfudge = (rect.bottom-rect.top);

#if 0
printf("resized %d %d %d %d %d %d\n",
		rect.left, rect.top, rect.right, rect.bottom,
		rect.right-rect.left, rect.bottom-rect.top);
#endif
				
			if (!aglUpdateContext (_hoops_CSRGR->curr_AGLContext)) {
				HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY,
						  "Unable to Update Current OpenGL Rendering Context");
				HD_Kill_Driver (dc);
				return;
			}

			HD_Resize_Subscreen (dc, true,
								 0, (rect.right-rect.left)-1, 
								 0, (rect.bottom-rect.top)-1);

			if (!_hoops_HAIPC && _hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR && _hoops_SIGHP) {

				/*_hoops_RAAP*/
				bufferRect[0] = _hoops_SIGHP[_hoops_CAIPC];

				/*_hoops_PRPC*/
				bufferRect[1] = _hoops_SIGHP[INNER_OVERRIDE_Y];

				/*_hoops_IGAA*/
				bufferRect[2] = _hoops_SIGHP[INNER_OVERRIDE_W];

				/*_hoops_APPS*/
				bufferRect[3] = _hoops_SIGHP[_hoops_SAIPC];

#if 0
printf("AGL_BUFFER_RECT lbwh: %ld %ld %ld %ld\n",		
	bufferRect[0], bufferRect[1], bufferRect[2], bufferRect[3]);
#endif

				aglSetInteger(_hoops_CSRGR->curr_AGLContext, AGL_BUFFER_RECT, bufferRect);
				aglEnable(_hoops_CSRGR->curr_AGLContext, AGL_BUFFER_RECT);
				
				if (BIT (_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_CAGAC) && 
						_hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR)
				{
					CGContextRef cgx;
					CGRect _hoops_GPIPC;

					QDBeginCGContext(GetWindowPort(_hoops_CSRGR->window), &cgx);
					_hoops_GPIPC.origin.x = 0;
					_hoops_GPIPC.origin.y = 0;
					_hoops_GPIPC.size.width = rect.right-rect.left;
					_hoops_GPIPC.size.height = rect.bottom-rect.top;
					CGContextClearRect(cgx, _hoops_GPIPC);
					QDEndCGContext(GetWindowPort(_hoops_CSRGR->window), &cgx);
				} 
			}
		}
		SetPort ((GrafPtr) GetWindowPort (_hoops_CSRGR->window));
	}



	
	_hoops_CSRGR->prev_AGLContext = aglGetCurrentContext();
	if (!aglSetCurrentContext (_hoops_CSRGR->curr_AGLContext)) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY,
				  "Unable to Make Current OpenGL Rendering Context");
		HD_Kill_Driver (dc);
		return;
	}
} 



/*****************************************************************************
 *****************************************************************************
								_hoops_CPIRH _hoops_SPIRH
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_PGAA
 */
local void
check_events (OGLData alter * _hoops_CSRGR) {

	EventTargetRef target;
	EventRef event;

	_hoops_CSRGR->_hoops_IRRRR = false;

	target = GetEventDispatcherTarget();

	while (!ReceiveNextEvent(0, 0, kEventDurationNoWait, true, &event)) {
		SendEventToEventTarget(event, target);
		ReleaseEvent(event);
	}
}

/*
 * _hoops_SRAC
 */
local bool
_hoops_HSCSP (Display_Context const * dc,
				  int alter * button,
				  int alter * x, int alter * y) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	if (_hoops_CSRGR != null) {
		check_events (_hoops_CSRGR);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		_hoops_CSRGR = OGLD (dc);
		/*
		 * _hoops_HGI _hoops_API _hoops_PIHA _hoops_SHR _hoops_RHRRH _hoops_IRS _hoops_GISAP "_hoops_PIAP",
		 * _hoops_HIS _hoops_RPP _hoops_RIIRH _hoops_SSAS _hoops_HAR _hoops_RHRRH _hoops_PCCP _hoops_CPGGR _hoops_AIH
		 * _hoops_AIIRH, _hoops_SR _hoops_PIHA _hoops_RHRRH _hoops_SPR _hoops_ARI.
		 * _hoops_PS _hoops_GRS _hoops_SAHR _hoops_ASAR-_hoops_RHRRH _hoops_RH _hoops_CGHI _hoops_GISAP _hoops_PIAP _hoops_SGS
		 * _hoops_SR _hoops_HARRA.
		 */
		if (_hoops_CSRGR == null || _hoops_CSRGR->_hoops_IRRRR)
			return false;
		else {
			*button = _hoops_CSRGR->_hoops_HRRRR;
			*x = _hoops_CSRGR->_hoops_SCGRR;
			*y = _hoops_CSRGR->mouse_y;
			return true;
		}
	}

	return false;
}


/*
 * _hoops_SRAC
 */
local bool
_hoops_ISCSP (Display_Context const * dc,
				  int alter * button, int alter * status) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	if (_hoops_CSRGR != null) {
		check_events (_hoops_CSRGR);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		_hoops_CSRGR = OGLD (dc);

		/*
		 * _hoops_RIIRH _hoops_GRS _hoops_SHR _hoops_HS _hoops_PIIRH _hoops_GII _hoops_HIIRH
		 * _hoops_IS _hoops_IRISR _hoops_AIH _hoops_IIIRH.  _hoops_CPGP _hoops_IRISR _hoops_ASSP'_hoops_RA
		 * _hoops_RRP _hoops_IS _hoops_ACPA _hoops_RH "_hoops_PIAP" _hoops_IIGR _hoops_RH _hoops_CIIRH, _hoops_RGR _hoops_API
		 * _hoops_PAH _hoops_IGIRR _hoops_ASRC _hoops_RCPP.
		 */
	}
	return false;
}

/*****************************************************************************
 *****************************************************************************
								_hoops_HGGSP _hoops_PARPI
 *****************************************************************************
 *****************************************************************************/




/*****************************************************************************
 *****************************************************************************
				_hoops_RRIA _hoops_RPGGP _hoops_SICAR
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_SRAC
 */
local void
get_current_info (Display_Context alter * dc) {

	OGLData alter *_hoops_CSRGR = OGLD (dc);
	GDHandle device; 

	if (_hoops_CSRGR->device == 0)
		device = _hoops_CSRGR->info_device;
	else
		device = _hoops_CSRGR->device;

	if (dc->options._hoops_GCHSR != 0) {
		dc->options._hoops_RASSP = true;
		dc->options._hoops_AASSP = true;
		dc->options._hoops_PASSP = true;
		dc->options._hoops_HPHRP = false;
	}
#if 0
	if (_hoops_CSRGR->curr_AGLContext) {
		GLint _hoops_RCHA[3] = { 0, 0, 0 };

		glGetIntegerv (GL_RED_BITS, _hoops_RCHA);
		glGetIntegerv (GL_BLUE_BITS, _hoops_RCHA + 1);
		glGetIntegerv (GL_GREEN_BITS, _hoops_RCHA + 2);
		_hoops_CSRGR->_hoops_SAHGC = _hoops_RCHA[0] + _hoops_RCHA[1] + _hoops_RCHA[2];
	}
#endif
	/* _hoops_HIHH _hoops_SHR _hoops_APPP 8 _hoops_SIH _hoops_RIR _hoops_AIHSR */
	dc->current._hoops_AAPSR = 1L << 24;
	dc->current._hoops_APASR = 0;

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		dc->current.extent.left = (float) 0;
		dc->current.extent.right = (float) dc->_hoops_PGCC._hoops_PRPSR.x - 1;
		dc->current.extent.bottom = (float) 0;
		dc->current.extent.top = (float) dc->_hoops_PGCC._hoops_PRPSR.y - 1;
	}
	else if (_hoops_CSRGR->window) {
		int *_hoops_SIGHP = _hoops_CSRGR->_hoops_CSPRP;
		Rect rect;

		if (_hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR && _hoops_SIGHP) {
			rect.left	= _hoops_SIGHP[OUTER_OVERRIDE_X] + _hoops_SIGHP[_hoops_CAIPC];
			rect.right	= rect.left + _hoops_SIGHP[INNER_OVERRIDE_W]; 
			rect.bottom = _hoops_SIGHP[OUTER_OVERRIDE_Y] + _hoops_SIGHP[_hoops_IAIPC] - _hoops_SIGHP[INNER_OVERRIDE_Y];
			rect.top	= rect.bottom - _hoops_SIGHP[_hoops_SAIPC];
		} else {
			GetWindowBounds (_hoops_CSRGR->window, kWindowContentRgn, &rect);
		}

		dc->current.extent.left = (float) rect.left;
		dc->current.extent.right = (float) rect.right - 1;
		dc->current.extent.bottom = (float) (_hoops_CSRGR->_hoops_CCGRR - (rect.bottom - 1));
		dc->current.extent.top = (float) (_hoops_CSRGR->_hoops_CCGRR - rect.top);
	}
	else{
		GDHandle device; 

		if (_hoops_CSRGR->device == 0)
			device = _hoops_CSRGR->info_device;
		else
			device = _hoops_CSRGR->device;

		dc->current.extent.left = 0.0f;
		dc->current.extent.right = (float) (*device)->gdRect.right;
		dc->current.extent.bottom = (float) (*device)->gdRect.bottom;
		dc->current.extent.top = 0.0f;
	}

}


/*
 * _hoops_SRAC
 */
local void
get_physical_info (Display_Context alter * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	GDHandle device; 

	if (_hoops_CSRGR->device == 0)
		device = _hoops_CSRGR->info_device;
	else
		device = _hoops_CSRGR->device;

	dc->_hoops_PGCC.flags |= _hoops_PPPGH;

	/* _hoops_PS _hoops_AA _hoops_HAR _hoops_AA _hoops_IPPSR _hoops_PCRR */
	dc->_hoops_PGCC._hoops_PIPGH = false;

	if (_hoops_CSRGR->_hoops_PIGRR == DCT_IMAGE ||
		_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {

		dc->_hoops_PGCC._hoops_PRPSR.x = _hoops_CSRGR->_hoops_IHGRR->width;
		dc->_hoops_PGCC._hoops_PRPSR.y = _hoops_CSRGR->_hoops_IHGRR->height;
		dc->_hoops_PGCC.size.x = dc->_hoops_PGCC._hoops_PRPSR.x *  (2.54f /72.0f);
		dc->_hoops_PGCC.size.y = dc->_hoops_PGCC._hoops_PRPSR.y *  (2.54f /72.0f);
	}
	else {
		short HRes,VRes;

		ScreenRes(&HRes, &VRes);

		dc->_hoops_PGCC._hoops_PRPSR.x = (*device)->gdRect.right;
		dc->_hoops_PGCC._hoops_PRPSR.y = (*device)->gdRect.bottom;
		dc->_hoops_PGCC.size.x = ((*device)->gdRect.right / (float)HRes) * 2.54f;
		dc->_hoops_PGCC.size.y = ((*device)->gdRect.bottom / (float)VRes) * 2.54f;
	}

	if (dc->options._hoops_SPHSR.x != -1) {
		dc->_hoops_PGCC.size.x = dc->options._hoops_SPHSR.x;
		dc->_hoops_PGCC.size.y = dc->options._hoops_SPHSR.y;
	}

	_hoops_CSRGR->yfudge = _hoops_CSRGR->_hoops_CCGRR = dc->_hoops_PGCC._hoops_PRPSR.y - 1;

	/* _hoops_PPSI _hoops_GGR _hoops_GHAR _hoops_RGGHR _hoops_ARI..._hoops_SAHR _hoops_GGR _hoops_AGIR _hoops_RH _hoops_RPGP _hoops_RPPS _hoops_ISHS */
	dc->_hoops_PGCC._hoops_PCHSR = 256;
	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	dc->_hoops_PGCC.driver_type = "AOGL";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.163 $";
	dc->_hoops_PGCC._hoops_ICHSR = "frame buffer";
	dc->_hoops_PGCC._hoops_RCPGH = "mouse";
	
	/* _hoops_IHH _hoops_AAARR _hoops_ARP _hoops_IS _hoops_RCPP _hoops_CCGR _hoops_SR _hoops_CACH _hoops_IRS _hoops_APIP _hoops_GGSC */
	dc->_hoops_PGCC.flags &= ~_hoops_SGICP;
	dc->_hoops_PGCC.flags &= ~_hoops_GPPGH;

	dc->_hoops_PGCC.flags &= ~_hoops_GGISR;

	_hoops_CSRGR->_hoops_PPHGC = false;

	/*
	 * _hoops_SIHPC:	 _hoops_PGGA _hoops_IIH _hoops_HRGR _hoops_GCHPC _hoops_IIGR _hoops_HPHS _hoops_SGS _hoops_SR _hoops_AA _hoops_ASAI
	 * _hoops_ACPA _hoops_CCGR _hoops_PCCP _hoops_HIHH-_hoops_RAHRH-_hoops_RCHPC _hoops_RPPS _hoops_HRGR _hoops_SCGH, _hoops_SR _hoops_AA
	 * _hoops_PCCP _hoops_PAAP _hoops_CPHSR _hoops_SIHC _hoops_GGR _hoops_HGSR _hoops_ICCI
	 * _hoops_HGI _hoops_IGISR _hoops_GGR _hoops_AGRR _hoops_HPHS (_hoops_ACHPC _hoops_AHCA _hoops_RH _hoops_PHI
	 * _hoops_IIGR _hoops_GHC _hoops_HHPA _hoops_CR _hoops_SCH _hoops_HRGR _hoops_AACC _hoops_GGR _hoops_HHAA _hoops_CGPR _hoops_RHAC _hoops_AA _hoops_GHGPR
	 * _hoops_RHGPR) _hoops_SGS _hoops_CGH _hoops_PCHPC _hoops_SHH _hoops_CPHR _hoops_ARI... _hoops_AA _hoops_PCCP
	 * _hoops_HCHPC _hoops_ARI _hoops_HIH _hoops_PCSA _hoops_SGS _hoops_RGR _hoops_SIHC _hoops_GHCA _hoops_AGRP...
	 */
	if (_hoops_CSRGR->curr_AGLContext)
		_hoops_IAHGC (dc);

	/* _hoops_CCRAA _hoops_ICHPC _hoops_CRPGH _hoops_HRGR _hoops_SHR _hoops_HHPA _hoops_GGR _hoops_HIHH */
	dc->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;

	/* _hoops_IHH _hoops_AAARR */
	dc->_hoops_PGCC.flags |= _hoops_SGICP;
	dc->_hoops_PGCC.flags |= _hoops_GPPGH;

	dc->_hoops_PGCC._hoops_HGCC = 1; /*_hoops_RGR _hoops_ICHHR _hoops_AAPA _hoops_PAPA _hoops_SCSAH*/

	if (BIT (dc->options._hoops_IRARR, _hoops_GHGAC))
		dc->_hoops_PGCC.flags |= _hoops_GIHSR;

	dc->_hoops_PGCC.flags |= _hoops_RSHSR;
	dc->_hoops_PGCC._hoops_ASHSR = 3;

	dc->_hoops_PGCC.flags |= _hoops_ASSHP;
	dc->_hoops_PGCC.flags |= _hoops_PSSHP;
}

/*****************************************************************************
 *****************************************************************************
						_hoops_GCIH/_hoops_SCPRH _hoops_IPSRH 
 *****************************************************************************
 *****************************************************************************/

static EventTypeSpec app_events[] = {
	{ kEventClassAppleEvent, kEventAppleEvent },
};

static pascal OSStatus our_app_event_handler(EventHandlerCallRef _hoops_GHP, EventRef event, void* userData);

/*_hoops_CIPH _hoops_IH _hoops_GHHS _hoops_IPPAC _hoops_CICRR*/
static unsigned int ogl_bundle_users = 0;
static CFBundleRef ogl_bundle_ref = 0;

local CFBundleRef LoadSystemFrameWorkBundle(const char *frameworkName)
{
	FSRef _hoops_GSPGA, _hoops_RSPGA;
	CFBundleRef _hoops_ASPGA = NULL;

	if (FSFindFolder(kSystemDomain, kFrameworksFolderType, false, &_hoops_GSPGA) == noErr) {

			HFSUniStr255 _hoops_PSPGA;
			CFStringRef _hoops_HSPGA;

			/* _hoops_CAAA _hoops_IHRPR _hoops_GSGR _hoops_IS _hoops_ISPGA [_hoops_CSPGA] _hoops_PIH _hoops_PPARR */
			_hoops_HSPGA = CFStringCreateWithCString(CFAllocatorGetDefault(), frameworkName, kCFStringEncodingMacRoman);
			_hoops_PSPGA.length = CFStringGetLength(_hoops_HSPGA);
			CFStringGetCharacters(_hoops_HSPGA, CFRangeMake(0,_hoops_PSPGA.length), _hoops_PSPGA.unicode);
			CFRelease(_hoops_HSPGA);

			if (FSMakeFSRefUnicode(&_hoops_GSPGA, _hoops_PSPGA.length, _hoops_PSPGA.unicode, CFStringGetSystemEncoding(), &_hoops_RSPGA) == noErr) {

					CFURLRef urlRef = CFURLCreateFromFSRef(CFAllocatorGetDefault(), &_hoops_RSPGA);

					if (urlRef) {
							_hoops_ASPGA=CFBundleCreate(CFAllocatorGetDefault(), urlRef);
							CFRelease(urlRef);
					}
			}
	}  
	/* _hoops_PCSA _hoops_IS _hoops_SSPGA _hoops_RGR _hoops_CGPR _hoops_RHAC _hoops_CHR _hoops_CPHR!! */
	return _hoops_ASPGA;	  
}

local void * GetFunctionPointerFromBundle(const char *name, CFBundleRef _hoops_HCPGA)
{
	void *function = 0;

	if (_hoops_HCPGA) {
			CFStringRef _hoops_ICPGA = CFStringCreateWithCString(CFAllocatorGetDefault(), name, kCFStringEncodingMacRoman);
			function = CFBundleGetFunctionPointerForName(_hoops_HCPGA, _hoops_ICPGA);
			CFRelease(_hoops_ICPGA);
	}
	return function;
}

local void * MyAGLGetProcAddress(const char *_hoops_SCPGA)
{
	if (!ogl_bundle_ref) {
		 return 0;
	}

	return GetFunctionPointerFromBundle(_hoops_SCPGA, ogl_bundle_ref);
}

/*
 * _hoops_SRAC
 */
local bool
start_device (Display_Context alter * dc) {
	OGLData *_hoops_CSRGR;

	ZALLOC (_hoops_CSRGR, OGLData);
	/* _hoops_CSPH->_hoops_PIH _hoops_GHCA _hoops_HS _hoops_RH _hoops_PCHAC _hoops_RHPP'_hoops_GRI _hoops_PIH _hoops_GPP _hoops_SCH */
	if (!dc->data) 
		dc->data = (void alter *) _hoops_CSRGR;
	dc->_hoops_RIHGR = (void alter *) _hoops_CSRGR;
	_hoops_CSRGR->dc = dc;
	_hoops_CSRGR->info_device = GetMainDevice();

	/* _hoops_PIRC _hoops_IIGR _hoops_RH _hoops_HSPR _hoops_HRGR _hoops_HAHH _hoops_PGGA _hoops_IIGR _hoops_RH _hoops_RPIPC _hoops_ARRS 
		_hoops_HGPGA->_hoops_APIPC = 0;
		_hoops_HGPGA->_hoops_PPIPC = 0;
		_hoops_HGPGA->_hoops_HPIPC = 0;
		_hoops_HGPGA->_hoops_IPIPC = _hoops_RCPP;
		_hoops_HGPGA->_hoops_IGPGA=0;
		_hoops_HGPGA->_hoops_CPIPC = _hoops_RCPP;
		_hoops_HGPGA->_hoops_SPIPC = _hoops_RCPP;
		_hoops_HGPGA->_hoops_RPPS = 0;
		_hoops_HGPGA->_hoops_GHIPC = 0;
		_hoops_HGPGA->_hoops_SISS = 0;
		_hoops_HGPGA->_hoops_GAHAC=0;
		_hoops_HGPGA->_hoops_RHIPC=0;
		_hoops_HGPGA->_hoops_AHIPC=0;
		_hoops_HGPGA->_hoops_PHIPC=0;
		_hoops_HGPGA->_hoops_HHIPC = _hoops_RCPP;
	*/

	if (!dc->options._hoops_GCHSR) {

		_hoops_CSRGR->_hoops_PIGRR = _hoops_PPSGR;

		if (!_hoops_IRIPC) {

			ProcessSerialNumber _hoops_IHIPC;
			if (GetCurrentProcess(&_hoops_IHIPC) != noErr) return false;
			SetFrontProcess(&_hoops_IHIPC);

			_hoops_IRIPC = NewEventHandlerUPP(our_app_event_handler);
			InstallEventHandler(GetApplicationEventTarget(), _hoops_IRIPC,
				GetEventTypeCount(app_events), app_events, 
				(void*)_hoops_CSRGR, &_hoops_HRIPC); 

		}

	} 
    else if (dc->options._hoops_RGHRP == _hoops_GGHRP || BIT (dc->options._hoops_IRARR, _hoops_GCSRH)) {
        Image alter              *image;
		bool					supported_format;

        image = (Image alter *)_hoops_RCSSR (dc->_hoops_RIGC, dc->options._hoops_GCHSR);
        if (image == null) {
            HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
                    "An invalid key was passed to the OpenGL driver with USE_WINDOW_IS_IMAGE set."); 
            return false;
        }
		supported_format = (image->format == Image_RGBA32 ||
							image->format == _hoops_CSGSP ||
							image->format == _hoops_HRSRH ||
							image->format == _hoops_HHGH);
        if (!supported_format || image->_hoops_PHGH == 0) {
            HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
                    "OpenGL output image unsupported format."); 
            return false;
        }
        if (image->height < 1 || image->width < 1) {
            HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
                    "OpenGL output images must be at least 1x1."); 
            return false;
        }
		/* _hoops_CHIPC _hoops_HRGR _hoops_IRS _hoops_SHIPC _hoops_GIIPC _hoops_RRPR _hoops_SGS _hoops_GRS _hoops_SHH _hoops_GRAA-_hoops_IRAP _hoops_GPP
		 * _hoops_CSPP 10.3 _hoops_PAR _hoops_SPHR _hoops_RGAR */
#if 0
		if (aglCreatePBuffer == nullroutine) {
			HE_ERROR (HEC_QUARTZ_DRIVER, HES_CANNOT_CREATE_WINDOW, 
					"opengl image driver on MacOS requires MacOS 10.3 or later");
			return false;
		}
#endif

        _hoops_CSRGR->_hoops_IHGRR = image;
		_hoops_CSRGR->window_width = _hoops_CSRGR->_hoops_IHGRR->width;
		_hoops_CSRGR->window_height = _hoops_CSRGR->_hoops_IHGRR->height;
        _hoops_PRRH (_hoops_CSRGR->_hoops_IHGRR);
        _hoops_CSRGR->_hoops_PIGRR = _hoops_IPSGR; /* _hoops_GPP _hoops_SSIGI, _hoops_CGSRC _hoops_HPCS _hoops_HRGR _hoops_GGHGI */
    }
	else {
		_hoops_CSRGR->_hoops_PIGRR = _hoops_HPSGR;
		_hoops_CSRGR->window = (WindowRef) dc->options._hoops_GCHSR;
		((Display_Context alter *) dc)->current._hoops_RAPGH = (POINTER_SIZED_INT) _hoops_CSRGR->window;

		_hoops_CSRGR->_hoops_CSPRP = (int*)dc->options._hoops_CSPRP;

		if (!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH)) {

		}
	}

	ogl_bundle_users++;
	if (ogl_bundle_users==1) {
		ogl_bundle_ref = LoadSystemFrameWorkBundle("OpenGL.framework");
	}

	return true;
}


/*
 * _hoops_SRAC
 */
local void
stop_device (Display_Context alter * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	/* _hoops_RCSH _hoops_GII _hoops_ASSRH _hoops_SHCA'_hoops_GRI _hoops_SR _hoops_SPIP */
	switch (_hoops_CSRGR->_hoops_PIGRR) {
		case _hoops_IPSGR:
			if (_hoops_CSRGR->_hoops_IHGRR) {
				if (_hoops_CSRGR->output_image_scratch) {
					int w = _hoops_CSRGR->_hoops_IHGRR->width;
					int h = _hoops_CSRGR->_hoops_IHGRR->height;
					FREE_ARRAY(_hoops_CSRGR->output_image_scratch, w*h, RGBAS32);
				}
				_hoops_HPRH (_hoops_CSRGR->_hoops_IHGRR); /* _hoops_IPIH _hoops_RGAR _hoops_ARGPR _hoops_IS _hoops_SRGAC */
			}
		break;

		case _hoops_PPSGR:
		case _hoops_HPSGR:
			/* _hoops_ISAP _hoops_IS _hoops_AA */
		break;
	}
	unset_ogl (dc);
	_hoops_CSRGR->_hoops_PIGRR = _hoops_APSGR;

	if (_hoops_CSRGR->_hoops_PRARR)
		HI_Free_Driver_Config(_hoops_CSRGR->_hoops_PRARR);

	FREE (_hoops_CSRGR, OGLData);
	if (dc->data == dc->_hoops_RIHGR)
		dc->data = null;
	dc->_hoops_RIHGR = null;

	ogl_bundle_users--;

	if (ogl_bundle_users==0) {
		if (ogl_bundle_ref) {
			CFRelease(ogl_bundle_ref);
			ogl_bundle_ref=0;
		}
	}
}




/*****************************************************************************
 *****************************************************************************
						_hoops_HGGSP _hoops_PARPI _hoops_ACPIH 
 *****************************************************************************
 *****************************************************************************/

static pascal OSStatus our_app_event_handler(EventHandlerCallRef _hoops_GHP, EventRef event, void* userData)
{
	OSStatus			result = eventNotHandledErr;
		
	UInt32				iclass = GetEventClass (event);
	UInt32				_hoops_RIIPC = GetEventKind (event);

#if 0
	OGLData *_hoops_CSRGR = (OGLData*)userData;
	WindowRef			window = NULL;
#endif

	switch (iclass) {

		case kEventClassAppleEvent:

			switch (_hoops_RIIPC) {
				case kEventAppleEvent: 
					{
						OSType _hoops_AIIPC, aeClass;

						GetEventParameter(event, kEventParamAEEventClass, typeType,
							  NULL, sizeof(aeClass), NULL, &aeClass);
						GetEventParameter(event, kEventParamAEEventID, typeType,
							  NULL, sizeof(_hoops_AIIPC), NULL, &_hoops_AIIPC);
						if (aeClass == kCoreEventClass) {

							switch (_hoops_AIIPC) {
								case kAEQuitApplication: 

									result = noErr;
									break; 
								default:{
									EventRecord _hoops_PACPA;
									if (ConvertEventRefToEventRecord(event, &_hoops_PACPA)) {

										if (noErr == AEProcessAppleEvent(&_hoops_PACPA)) {
											result = noErr;
										}

									}else{
/*
										_hoops_IPRPR("_hoops_SRSH _hoops_IS _hoops_PIIPC()");
*/
									}	
								}
								break;
							}
						}else{
/*
					_hoops_IPRPR("_hoops_RHGC");
*/
						}
					} 
					break;

				default:
/*
_hoops_IPRPR("_hoops_SHIR");
*/
					break;
			}
		break;

		default: 
/*
_hoops_IPRPR("_hoops_RHGC _hoops_CSHGR %_hoops_GSGGR%_hoops_GSGGR%_hoops_GSGGR%_hoops_GSGGR", 
		(_hoops_GSPR)(_hoops_HIIPC>>24), 
		(_hoops_GSPR)((_hoops_HIIPC>>16)&255), 
		(_hoops_GSPR)((_hoops_HIIPC>>8)&255),
		(_hoops_GSPR)(_hoops_HIIPC&255));
*/
		break;
	}
	return result;
}

static void consume_key(OGLData *_hoops_CSRGR, EventRef event)
{
		UInt32 _hoops_ASAGA;
		UInt32 key_mod;
		UInt32 key;
		int status = 0;

#define B_SHIFT					0x00000100
#define B_CONTROL				0x00000200 
#define B_NUM_LOCK				0x00000400
#define B_ALT					0x00000800
#define B_CAPS_LOCK				0x00001000
#define B_SCROLL_LOCK			0x00002000
#define B_LEFT_SHIFT			0x00004000
#define B_RIGB_SHIFT			0x00008000
#define B_RIGB_CONTROL			0x00010000
#define B_LEFT_CONTROL			0x00020000
#define B_RIGB_ALT				0x00040000
#define B_LEFT_ALT				0x00080000

		GetEventParameter (event, kEventParamKeyCode, typeUInt32, NULL, sizeof(UInt32), NULL, &_hoops_ASAGA);
		GetEventParameter (event, kEventParamKeyModifiers, typeUInt32, NULL, sizeof(UInt32), NULL, &key_mod);

		if (key_mod & shiftKey) {
			status |= B_SHIFT;
		}
		if (key_mod & controlKey) {
			status |= B_CONTROL;
		}
		if (key_mod & optionKey) {
			status |= B_ALT;
		}

/*_hoops_SIGP
		_hoops_RPP (_hoops_PSAGA &&) _hoops_HSAGA |= _hoops_ISAGA;
		_hoops_RPP (_hoops_PSAGA &&) _hoops_HSAGA |= _hoops_CSAGA;
		_hoops_RPP (_hoops_PSAGA &&) _hoops_HSAGA |= _hoops_SSAGA;
*/

		key = KeyTranslate((void *)GetScriptManagerVariable(smUnicodeScript), 
				key_mod | _hoops_ASAGA, &_hoops_CSRGR->key_state);

		switch (key) {
			case kHelpCharCode:			key = _hoops_GAPPH; break;
			case kEndCharCode:			key = END_KEY; break;
			case kPageUpCharCode:		key = PAGE_UP_KEY; break;
			case kHomeCharCode:			key = HOME_KEY; break;
			case kPageDownCharCode:		key = PAGE_DOWN_KEY; break;

			case kBackspaceCharCode:	key = RUBOUT_KEY; break;

			case kLeftArrowCharCode:	key = LEFT_ARROW_KEY; break;
			case kRightArrowCharCode:	key = RIGHT_ARROW_KEY; break;
			case kUpArrowCharCode:		key = UP_ARROW_KEY; break;
			case kDownArrowCharCode:	key = DOWN_ARROW_KEY; break;
			default:break;
		}

		if ((key_mod & 0x00010000L) && (key >= '0' && key<= '9')) {
				key = FIRST_KEYPAD_KEY + key - '0';
		}

		HI_Queue_Keyboard_Event ((_hoops_GGAGR alter *)_hoops_CSRGR->dc->_hoops_GHRI, key, status);

}

/*
 * _hoops_PGAA
 */
local void
consume_mouse(OGLData *_hoops_CSRGR, EventRef event)
{
	EventMouseButton button = 0;
	_hoops_SARRI _hoops_ICAGA = {0, 0};
	UInt32 _hoops_GCSAH = 0;
	Rect rect;

	UInt32 _hoops_RIIPC = GetEventKind (event);

	GetEventParameter(event, kEventParamMouseButton, typeMouseButton, NULL, sizeof(EventMouseButton), NULL, &button);
	GetEventParameter(event, kEventParamMouseLocation, typeQDPoint, NULL, sizeof(Point), NULL, &_hoops_ICAGA); 
	GetEventParameter(event, kEventParamKeyModifiers, typeUInt32, NULL, sizeof(UInt32), NULL, &_hoops_GCSAH);

	GetWindowBounds (_hoops_CSRGR->window, kWindowContentRgn, &rect);

	if (!(_hoops_ICAGA.v>rect.top)) return;

	if (_hoops_GCSAH & controlKey) {
		button = kEventMouseButtonSecondary;
	}

	switch (_hoops_RIIPC) {
		case kEventMouseDown:

			switch (button) {
				case kEventMouseButtonSecondary:
				{
					_hoops_CSRGR->_hoops_HRRRR |= _hoops_ARRRR;
				}
				break;
				case kEventMouseButtonTertiary:
				{
					_hoops_CSRGR->_hoops_HRRRR |= _hoops_PRRRR;
				}
				break;
				case kEventMouseButtonPrimary:
				{
					_hoops_CSRGR->_hoops_HRRRR |= _hoops_RRRRR;
				}
				break;
			}

			break;

		case kEventMouseUp:

			switch (button) {
				case kEventMouseButtonSecondary:
				{
					_hoops_CSRGR->_hoops_HRRRR &= ~_hoops_ARRRR;
				}
				break;
				case kEventMouseButtonTertiary:
				{
					_hoops_CSRGR->_hoops_HRRRR &= ~_hoops_PRRRR;
				}
				break;
				case kEventMouseButtonPrimary:
				{
					_hoops_CSRGR->_hoops_HRRRR &= ~_hoops_RRRRR;
				}
				break;
			}

			break;

		case kEventMouseDragged:
			break;
		default:
			break;
	}

	_hoops_CSRGR->_hoops_SCGRR = _hoops_ICAGA.h-rect.left-1;
	_hoops_CSRGR->mouse_y = _hoops_CSRGR->yfudge - (_hoops_ICAGA.v-rect.top-1);

	HD_Queue_Pixel_Location_Event (_hoops_CSRGR->dc, _hoops_CSRGR->_hoops_HRRRR,
								   _hoops_CSRGR->_hoops_SCGRR, _hoops_CSRGR->mouse_y);

	_hoops_CSRGR->_hoops_IRRRR = true;

}


static pascal OSStatus our_window_handler(EventHandlerCallRef myHandler, EventRef event, void* userData)
{
	OSStatus result = eventNotHandledErr;
	UInt32 iclass = GetEventClass (event);
	UInt32 _hoops_RIIPC = GetEventKind (event);
	OGLData *_hoops_CSRGR = (OGLData*)userData;

	Display_Context alter *dc;

	if ((dc = HD_Find_DC_From_WID ((POINTER_SIZED_INT) _hoops_CSRGR->window)) != null) {
		
	switch (iclass) {
		case kEventClassMouse:
			consume_mouse(_hoops_CSRGR, event);
			break;

		case kEventClassKeyboard:

			switch (_hoops_RIIPC) {
				case kEventRawKeyDown:
						consume_key(_hoops_CSRGR, event);
						result = noErr;
					break;
				default: break;
			}
			break;
		case kEventClassWindow:
/*
_hoops_IPRPR("_hoops_IIIPC ");
*/
/*
			_hoops_CIIPC(_hoops_PGRRR, _hoops_SIIPC, _hoops_GCIPC, _hoops_IHHAH, _hoops_GGHSP(_hoops_RCIPC), _hoops_IHHAH, &_hoops_RPPS);
*/
			switch (_hoops_RIIPC) {
				case kEventWindowCollapsing:
/*
_hoops_IPRPR("_hoops_ACIPC\_hoops_ACHP");
*/
					break;
				case kEventWindowActivated: 
/* _hoops_PIGS _hoops_GPP _hoops_PCIPC _hoops_HCIPC _hoops_PPR _hoops_PAHHH
_hoops_IPRPR("_hoops_ICIPC\_hoops_ACHP");
*/
					break;
				case kEventWindowDrawContent:
						{
/*
_hoops_IPRPR("_hoops_CCIPC\_hoops_ACHP");
*/
						result = noErr;
						HD_Force_Refresh (_hoops_CSRGR->dc);
						}
					break;
				case kEventWindowClose: 
					{
/* _hoops_PIGS _hoops_CGPR _hoops_RPPS _hoops_HRGR _hoops_IHGS _hoops_CAHC (_hoops_GGGR _hoops_AHCRR)
_hoops_IPRPR("_hoops_SCIPC\_hoops_ACHP");
*/
						char event_string[1024];

						result = noErr;

						if (dc->options._hoops_GASSP && !dc->options._hoops_IRSSP) {

							HI_Queue_Special_Event (dc->_hoops_RIGC, "OpenGL:DeleteWindow",
								HI_Build_Special_Event_String(event_string, "OPENGL", dc->_hoops_AAHSR, 
									(POINTER_SIZED_INT) _hoops_CSRGR->window, -1));
						}

						HideWindow(_hoops_CSRGR->window);

						HI_Queue_Actor_Shutdown(dc->_hoops_GHRI, false);
						dc->options._hoops_IRSSP = true;

					}
					break;
				case kEventWindowShown: 
/* _hoops_PIGS _hoops_GPP _hoops_CIGS _hoops_CRGH (_hoops_HAR _hoops_GPP _hoops_ISSPR-_hoops_GSIPC)
_hoops_IPRPR("_hoops_RSIPC\_hoops_ACHP");
*/
					result = noErr;
					if (_hoops_CSRGR->window == FrontWindow()) {
							SetUserFocusWindow(_hoops_CSRGR->window);
					}

					break;
				case kEventWindowBoundsChanging:
					{
						Rect _hoops_ASIPC, _hoops_PSIPC, _hoops_HSIPC;

						result = noErr;

						GetEventParameter(event, kEventParamOriginalBounds, typeQDRectangle, NULL, sizeof(Rect), NULL, &_hoops_ASIPC);
						GetEventParameter(event, kEventParamPreviousBounds, typeQDRectangle, NULL, sizeof(Rect), NULL, &_hoops_HSIPC);
						GetEventParameter(event, kEventParamCurrentBounds, typeQDRectangle, NULL, sizeof(Rect), NULL, &_hoops_PSIPC);

/*
_hoops_IPRPR("_hoops_GCSR: %_hoops_GHGP %_hoops_GHGP %_hoops_GHGP %_hoops_GHGP\_hoops_ACHP", _hoops_ISIPC._hoops_RAAP, _hoops_ISIPC._hoops_RPHR, _hoops_ISIPC._hoops_PRPC, _hoops_ISIPC._hoops_SCIA);
_hoops_IPRPR("_hoops_CCAHR: %_hoops_GHGP %_hoops_GHGP %_hoops_GHGP %_hoops_GHGP\_hoops_ACHP", _hoops_CSIPC._hoops_RAAP, _hoops_CSIPC._hoops_RPHR, _hoops_CSIPC._hoops_PRPC, _hoops_CSIPC._hoops_SCIA);
_hoops_IPRPR("_hoops_GSGGR: %_hoops_GHGP %_hoops_GHGP %_hoops_GHGP %_hoops_GHGP\_hoops_ACHP", _hoops_SSIPC._hoops_RAAP, _hoops_SSIPC._hoops_RPHR, _hoops_SSIPC._hoops_PRPC, _hoops_SSIPC._hoops_SCIA);
*/

						if (!dc->options._hoops_RASSP) {
							SetEventParameter(event, kEventParamCurrentBounds, typeQDRectangle, sizeof(Rect), &_hoops_ASIPC);
						}

						if (!dc->options._hoops_PASSP) {

							Rect _hoops_HSIHP;

							int _hoops_GGCPC,_hoops_RGCPC;
							int _hoops_GPGSI,_hoops_AGCPC;

							int _hoops_IRAAH,_hoops_PGCPC;
							int nw,nh;
							int _hoops_HGCPC,_hoops_IGCPC;
								
							_hoops_GGCPC = _hoops_ASIPC.right-_hoops_ASIPC.left;
							_hoops_RGCPC = _hoops_ASIPC.bottom-_hoops_ASIPC.top;

							_hoops_GPGSI = _hoops_PSIPC.right-_hoops_PSIPC.left;
							_hoops_AGCPC = _hoops_PSIPC.bottom-_hoops_PSIPC.top;

							if (_hoops_GGCPC == _hoops_GPGSI && _hoops_RGCPC == _hoops_AGCPC) break;

							if (abs(_hoops_GGCPC-_hoops_GPGSI) > abs(_hoops_RGCPC-_hoops_AGCPC)) {
								_hoops_IRAAH = _hoops_GGCPC-_hoops_GPGSI;
								_hoops_PGCPC = (int)((float)_hoops_IRAAH*(1.0f/_hoops_CSRGR->_hoops_ISIH));  
							}else{
								_hoops_PGCPC = _hoops_RGCPC-_hoops_AGCPC;
								_hoops_IRAAH = (int)((float)_hoops_PGCPC*_hoops_CSRGR->_hoops_ISIH); 
							}

							nw=_hoops_GGCPC-_hoops_IRAAH;
							nh=_hoops_RGCPC-_hoops_PGCPC;

							_hoops_PSIPC.right=_hoops_PSIPC.left+nw;
							_hoops_PSIPC.bottom=_hoops_PSIPC.top+nh;

							GetAvailableWindowPositioningBounds(_hoops_CSRGR->info_device, &_hoops_HSIHP);

/*
							_hoops_RPP (_hoops_CGCPC._hoops_RAAP>_hoops_SSIPC._hoops_RAAP) _hoops_SSIPC._hoops_RAAP=_hoops_CGCPC._hoops_RAAP;
*/
							if (_hoops_PSIPC.right>_hoops_HSIHP.right) _hoops_PSIPC.right=_hoops_HSIHP.right;
		
							_hoops_HGCPC=_hoops_PSIPC.right-_hoops_PSIPC.left;

							if (_hoops_HGCPC != nw) {
								nw = _hoops_HGCPC;
								nh = (int)((float)nw*(1.0f/_hoops_CSRGR->_hoops_ISIH));
								_hoops_PSIPC.bottom=_hoops_PSIPC.top+nh;
							}

							if (_hoops_HSIHP.top>_hoops_PSIPC.top) _hoops_PSIPC.top=_hoops_HSIHP.top;
							if (_hoops_PSIPC.bottom>_hoops_HSIHP.bottom) _hoops_PSIPC.bottom=_hoops_HSIHP.bottom;
		
							_hoops_IGCPC=_hoops_PSIPC.bottom-_hoops_PSIPC.top;

							if (_hoops_IGCPC != nh) {
								_hoops_PGCPC = _hoops_IGCPC;
								_hoops_IRAAH = (int)((float)_hoops_PGCPC*_hoops_CSRGR->_hoops_ISIH); 
								_hoops_PSIPC.right = _hoops_PSIPC.left+_hoops_IRAAH;
							}

							SetEventParameter(event, kEventParamCurrentBounds, typeQDRectangle, sizeof(Rect), &_hoops_PSIPC);
						}

					}
					break;
				case kEventWindowBoundsChanged: 
					{
						Rect rect;
						result = noErr;
						_hoops_CSRGR->pending_resize = true;

						GetWindowBounds (_hoops_CSRGR->window, kWindowContentRgn, &rect);

						if ((rect.right-rect.left != _hoops_CSRGR->window_width) || 
							(rect.bottom-rect.top != _hoops_CSRGR->window_height)) {
							HD_Force_Refresh (_hoops_CSRGR->dc);
						}
					}

					break;
				case kEventWindowZoomed: 
/* _hoops_PIGS _hoops_CGPR _hoops_IPSP _hoops_SGCPC _hoops_GPP _hoops_GRCPC _hoops_CHSAP
_hoops_IPRPR("_hoops_RRCPC\_hoops_ACHP");
*/
					break;
			}
			break;

		default: 
/*
_hoops_IPRPR("_hoops_RHGC _hoops_CSHGR\_hoops_ACHP");
*/
		break;
	}

	}/*_hoops_ARCPC _hoops_SHCA*/

	return result;
}


local POINTER_SIZED_INT
create_standalone_window(Display_Context * dc)
{
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	OSStatus status;

	EventTypeSpec _hoops_PRCPC[] = { 
		{ kEventClassWindow, kEventWindowCollapsing },
		{ kEventClassWindow, kEventWindowCollapsed },
		{ kEventClassWindow, kEventWindowShown },
		{ kEventClassWindow, kEventWindowActivated },
		{ kEventClassWindow, kEventWindowClose },
		{ kEventClassWindow, kEventWindowDrawContent },
		{ kEventClassWindow, kEventWindowBoundsChanging },
		{ kEventClassWindow, kEventWindowBoundsChanged },
		{ kEventClassWindow, kEventWindowZoomed },

		{ kEventClassMouse, kEventMouseDown },
		{ kEventClassMouse, kEventMouseUp },
		{ kEventClassMouse, kEventMouseDragged },

		{ kEventClassKeyboard, kEventRawKeyDown } };

	char _hoops_IAPIR[4096];
	CFStringRef _hoops_HRCPC=0;
	WindowAttributes attribs;
	WindowClass window_class;
	Rect rect;

	HI_Copy_Name_To_Chars (&dc->options._hoops_IAPIR, _hoops_IAPIR);
	_hoops_IAPIR[79] = '\0';

	attribs = kWindowStandardDocumentAttributes | kWindowStandardHandlerAttribute;

	if (!dc->options._hoops_AASSP) {
		attribs &= ~kWindowResizableAttribute;
	}

	window_class = kDocumentWindowClass;

	rect.left = dc->_hoops_RHPGA.left;
	rect.right = dc->_hoops_RHPGA.right;
	rect.top = _hoops_CSRGR->_hoops_CCGRR - dc->_hoops_RHPGA.top;
	rect.bottom = _hoops_CSRGR->_hoops_CCGRR - dc->_hoops_RHPGA.bottom;

	_hoops_CSRGR->_hoops_ISIH = (float)(rect.right-rect.left)/(float)(rect.bottom-rect.top);

	status = CreateNewWindow(window_class, attribs, &rect, &_hoops_CSRGR->window);

	if (status || !_hoops_CSRGR->window) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_CREATE_WINDOW, "Unable to Create a Window");
		HD_Kill_Driver (dc);
	}

	_hoops_HRCPC = CFStringCreateWithCString (0, _hoops_IAPIR, kCFStringEncodingASCII);

	SetWindowTitleWithCFString (_hoops_CSRGR->window, _hoops_HRCPC);

	_hoops_CSRGR->window_EventHandlerUPP = NewEventHandlerUPP(our_window_handler);

	InstallWindowEventHandler(
		_hoops_CSRGR->window, 
		_hoops_CSRGR->window_EventHandlerUPP, 
		GetEventTypeCount (_hoops_PRCPC), 
		_hoops_PRCPC, 
		(void*)_hoops_CSRGR, 
		&_hoops_CSRGR->event_handler_ref); 

	ShowWindow (_hoops_CSRGR->window);

	return (POINTER_SIZED_INT)(POINTER_SIZED_INT) _hoops_CSRGR->window;
}


/*
 * _hoops_SRAC
 */
local POINTER_SIZED_INT
get_outer_window (Display_Context const * _hoops_SAGRH) {
	Display_Context alter * dc = (Display_Context alter *) _hoops_SAGRH;
	POINTER_SIZED_INT retval = 0L;
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	invalidate_cache (_hoops_CSRGR);
	_hoops_CHCGC((Display_Context alter *) dc);

	switch (_hoops_CSRGR->_hoops_PIGRR) {
	
		case _hoops_IPSGR:
		{
			/* _hoops_ASRC _hoops_PIRA _hoops_IIGR 0 _hoops_HII _hoops_CHIPC _hoops_AGSR _hoops_HPCS */
 			if (aglCreatePBuffer (
					_hoops_CSRGR->_hoops_IHGRR->width, 
					_hoops_CSRGR->_hoops_IHGRR->height, 
					GL_TEXTURE_RECTANGLE_EXT, GL_RGBA, 
					0, &(_hoops_CSRGR->pbuffer)))
				retval = (POINTER_SIZED_INT)(POINTER_SIZED_INT)_hoops_CSRGR->pbuffer;
		}
		break;

		case _hoops_PPSGR:
			retval = create_standalone_window(dc);
		break;

		case _hoops_HPSGR:
			retval = (POINTER_SIZED_INT)(POINTER_SIZED_INT) _hoops_CSRGR->window;
		break;

		case DCT_IMAGE:
		default:
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
				"internal error: unsupported display context type in ogl_agl:get outer window");
			HD_Kill_Driver (dc);
	}

	/* _hoops_RH _hoops_AASA _hoops_CAPP _hoops_GACC _hoops_ARH _hoops_RH _hoops_PHI _hoops_IIGR _hoops_AAHRP _hoops_SIH _hoops_HA, _hoops_RIIA _hoops_IIGR _hoops_IRCPC _hoops_IS 16 */
	choose_pixel_format(dc);

	_hoops_CSRGR->prev_GrafPtr = 0;
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		int _hoops_HHRAR = 0;
		if (!aglSetPBuffer(_hoops_CSRGR->curr_AGLContext, _hoops_CSRGR->pbuffer, 0, 0, _hoops_HHRAR)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
				"Unable to set OpenGL pbuffer rendering context in ogl_agl:get outer window");
			HD_Kill_Driver (dc);
		}
		
		if (!aglSetCurrentContext(_hoops_CSRGR->curr_AGLContext)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
				"Unable to set Current OpenGL Rendering Context");
			HD_Kill_Driver (dc);
		}
	}
	else {
		if (BIT (_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_CAGAC) && 
			_hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR) {
			GLint _hoops_HGA = -1;
			aglSetInteger(_hoops_CSRGR->curr_AGLContext, AGL_SURFACE_ORDER, &_hoops_HGA);
			SetWindowAlpha(_hoops_CSRGR->window, 0.999f);
		}

		GetPort (&_hoops_CSRGR->prev_GrafPtr);
		SetPort ((GrafPtr) GetWindowPort (_hoops_CSRGR->window));
	
		if (!aglSetDrawable(_hoops_CSRGR->curr_AGLContext, GetWindowPort(_hoops_CSRGR->window))) {
		//_hoops_RPP (!_hoops_RAIPC(_hoops_HGPGA->_hoops_GAHAC, _hoops_HGPGA->_hoops_RPPS)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
				"Unable to set drawable");
			HD_Kill_Driver (dc);
		}
	
		if (!aglSetCurrentContext(_hoops_CSRGR->curr_AGLContext)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
				"Unable to set Current OpenGL Rendering Context");
			HD_Kill_Driver (dc);
		}
	}

	identify_renderer(dc);

	_hoops_CSRGR->_hoops_SRRRR = dc->options._hoops_SRRRR;

	/* _hoops_IH _hoops_HA, _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_SCGH _hoops_IAPR _hoops_RH _hoops_SCGR _hoops_AIR _hoops_RPCC _hoops_IAGC _hoops_GRPAR
	   _hoops_IS _hoops_IRS _hoops_CRCPC, _hoops_PPR _hoops_RGSR _hoops_RGR _hoops_SRCPC = 16 _hoops_ASSP'_hoops_RA _hoops_IPHR _hoops_CCA _hoops_RH
	   _hoops_SHIR _hoops_GACPC */
	if (BIT(dc->options._hoops_IRARR, _hoops_APGAC))
		_hoops_CSRGR->accumulation_bits = 0;

	_hoops_PICGC((Display_Context alter *) dc);

	/* _hoops_HHSP _hoops_IRPHR _hoops_CAPRH -- _hoops_CGH _hoops_RGR _hoops_AGIIP _hoops_SHH _hoops_GGCRC? */
	{
		GLint _hoops_HGGHA=0;
		aglSetInteger (_hoops_CSRGR->curr_AGLContext, AGL_SWAP_INTERVAL, &_hoops_HGGHA);
	}

	return retval;
}


/*
 * _hoops_SRAC
 */
local void
free_outer_window (Display_Context const * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	aglSetCurrentContext(_hoops_CSRGR->curr_AGLContext);

	_hoops_SPSGC(dc);

	aglSetCurrentContext(NULL);
	unset_ogl (dc);

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR) {
		DisposeWindow (_hoops_CSRGR->window);
		_hoops_CSRGR->window = null;
		if (_hoops_CSRGR->window_EventHandlerUPP) {
			DisposeEventHandlerUPP(_hoops_CSRGR->window_EventHandlerUPP);
			_hoops_CSRGR->window_EventHandlerUPP = null;
		}
	}
	else if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		aglDestroyPBuffer (_hoops_CSRGR->pbuffer);
		_hoops_CSRGR->pbuffer = null;
	}
}


/*
 * _hoops_SRAC
 */
local void
_hoops_RSCSP (Display_Context const * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	_hoops_CSRGR->_hoops_HCAC = _hoops_CCC;
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_CSRGR->_hoops_IARRR = _hoops_CCC;
	_hoops_CSRGR->_hoops_ICAC = _hoops_CCC;

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR) return;

	MoveWindow(_hoops_CSRGR->window, dc->_hoops_RHPGA.left, dc->_hoops_RHPGA.top, false);
	SizeWindow(_hoops_CSRGR->window, 
		dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left, 
		dc->_hoops_RHPGA.bottom - dc->_hoops_RHPGA.top, 
		true);
#if 0
	if ((_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR ||
		 _hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR) &&
		IsWindow (_hoops_CSRGR->hWND) &&
		(IsIconic (_hoops_CSRGR->hWND) || IsZoomed (_hoops_CSRGR->hWND))) {
		/* _hoops_CGP _hoops_RH _hoops_RPPS _hoops_HRGR _hoops_PRRAH _hoops_SR _hoops_SSPC _hoops_HCR _hoops_PCCS _hoops_SSHRH */
		return;
	}

	_hoops_CSRGR->_hoops_SIGRR.x = dc->_hoops_RHPGA.left - _hoops_CSRGR->_hoops_PCGRR;
	_hoops_CSRGR->_hoops_SIGRR.y = _hoops_CSRGR->_hoops_CCGRR - dc->_hoops_RHPGA.top - _hoops_CSRGR->_hoops_HCGRR;
	_hoops_CSRGR->_hoops_CIGRR.x = dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left + _hoops_CSRGR->_hoops_ACGRR + _hoops_CSRGR->_hoops_PCGRR;
	_hoops_CSRGR->_hoops_CIGRR.y = dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom + _hoops_CSRGR->_hoops_HCGRR + _hoops_CSRGR->_hoops_RCGRR;

	MoveWindow (_hoops_CSRGR->hWND,
				dc->_hoops_RHPGA.left - _hoops_CSRGR->_hoops_PCGRR,
				_hoops_CSRGR->_hoops_CCGRR - dc->_hoops_RHPGA.top - _hoops_CSRGR->_hoops_HCGRR,
				dc->_hoops_RHPGA.right - dc->_hoops_RHPGA.left + _hoops_CSRGR->_hoops_ACGRR + _hoops_CSRGR->_hoops_PCGRR,
				dc->_hoops_RHPGA.top - dc->_hoops_RHPGA.bottom + _hoops_CSRGR->_hoops_HCGRR + _hoops_CSRGR->_hoops_RCGRR, 
		true);
#endif
}

/*****************************************************************************
 *****************************************************************************
				_hoops_PPSRH
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_HRGSI _hoops_PGSI.
 */
struct OGLFontData {
	GLuint list[0xFFFF];
	FMFontFamily family;
	OSX_Style face;
};


/*
 * _hoops_SRAC
 */
local void
draw_dc_text (Net_Rendition const &  nr,
			  DC_Point const * where,
			  int count, Karacter const * kstring) {
	_hoops_IGCSR const &_hoops_HRCIR = nr->_hoops_SISI;
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	OGLFontData alter *_hoops_RHCSR = (OGLFontData alter *) (_hoops_HRCIR->font->_hoops_GAASR);

	if (nr->transform_rendition->_hoops_HCHH && !_hoops_CSRGR->_hoops_PPHGC) {
			HD_Clip_DC_Text(nr,where,count,kstring);
			return;
	} 

	if (_hoops_CSRGR->_hoops_RPCI != _hoops_HRCIR->_hoops_CPA) {
		_hoops_CSRGR->_hoops_RPCI = _hoops_HRCIR->_hoops_CPA;
		_hoops_APIGC (_hoops_CSRGR, &_hoops_HRCIR->color, nr);
	}

	_hoops_GIAC(_hoops_CSRGR, nr);

	_hoops_AIIGC(_hoops_CSRGR, nr);

	if ((_hoops_HRCIR->rotation < 45.0 || _hoops_HRCIR->rotation >= 315.0) && _hoops_HRCIR->_hoops_IPGRP == 0.0f) {

		int n;

		glRasterPos3f (0.0, 0.0, (GLfloat) where->z);
		glBitmap (0, 0, 0, 0, (GLfloat) where->x, (GLfloat) where->y, (GLubyte *) 0);

		for (n=0; n<count; n++) {

			int c = kstring[n];

			if (!_hoops_RHCSR->list[c]) {

				_hoops_RHCSR->list[c] = glGenLists (1);

				if (_hoops_RHCSR->list[c]) 
					aglUseFont (_hoops_CSRGR->curr_AGLContext, 
						_hoops_RHCSR->family, _hoops_RHCSR->face, _hoops_HRCIR->font->_hoops_IGGGH,
						c, 1, _hoops_RHCSR->list[c]);
			}

			if (_hoops_RHCSR->list[c]) {
				glCallList(_hoops_RHCSR->list[c]);
			}
		}
	}
	else {
		HD_Draw_Dead_Font(nr, _hoops_HRCIR->font, (Point*)where, count, kstring, 0);
	}
}


/*
 * _hoops_SRAC
 */
local void
find_all_fonts (Display_Context alter * dc) {

	const char * font_names[] = {
		"applFont", "los Angeles", "athens","monaco", "Futura",
		"cairo", "sanFran", "courier","times" ,
		"Geneva","symbol", "helvetica", "systemFont",
		"mobile","toronto", "new York","venice", "london",""}; 
				

	Str255 pstr;
	short f;
	int n=0;

#if 1
	return;
#endif

#if 0
	_hoops_CSRGR->prev_GrafPtr = 0;
	GetPort (&_hoops_CSRGR->prev_GrafPtr);
	_hoops_CSRGR->prev_AGLContext = aglGetCurrentContext();
	SetPort ((GrafPtr) GetWindowPort (_hoops_CSRGR->window));
#endif

	while (1) {

		if (font_names[n][0] == '\0') break;

/*
		_hoops_IPRPR("%_hoops_GRI ", _hoops_RACPC[_hoops_ACHP]);
*/

#if 0
		c2pstrcpy(pstr,font_names[n]);
		family = FMGetFontFamilyFromName(pstr);
		printf(": %d\n",(int)family);
		if (family == kInvalidFontFamily) {n++; continue;}
#else
		c2pstrcpy(pstr,font_names[n]);
		GetFNum(pstr, &f);
/*
		_hoops_IPRPR("_hoops_RAS %_hoops_GHGP\_hoops_ACHP",(_hoops_SCSH)_hoops_RCHP);
*/
		if (!f) {n++; continue;}
#endif

		HD_Record_Font_With_Encoding(dc, font_names[n], null, _hoops_SACSR, 0.0f, 1.7f);

		n++;
	}

#if 0
	if (_hoops_CSRGR->prev_AGLContext) {
		aglSetCurrentContext (_hoops_CSRGR->prev_AGLContext);
		_hoops_CSRGR->prev_AGLContext = 0;
	}
	if (_hoops_CSRGR->prev_GrafPtr) {
		SetPort (_hoops_CSRGR->prev_GrafPtr);
		_hoops_CSRGR->prev_GrafPtr = 0;
	}
#endif

#if 0
	HD_Mark_Font_As_Generic (dc, "helvetica", GFN_SANS_SERIF);
	HD_Mark_Font_As_Generic (dc, "times", GFN_ROMAN);
	HD_Mark_Font_As_Generic (dc, "courier", GFN_TYPEWRITER);
	HD_Mark_Font_As_System_Default (dc, "systemFont", -1);
#endif
		
}

/*
 *	* _hoops_SRAC
 *	 */
local bool measure_char(
		Net_Rendition const & nr,
		Font_Instance const * instance,
		Karacter _hoops_IPCSR,
		float alter *_hoops_GGGS,
		bool alter *_hoops_CPCSR,
		void ** _hoops_HPSRH) 
{
	OGLFontData *_hoops_RHCSR = (OGLFontData *) instance->_hoops_GAASR;

	int width;

/*
	_hoops_AACPC _hoops_SIHC;
	_hoops_PACPC(&_hoops_SIHC);
*/

	TextFont(_hoops_RHCSR->family);
	TextFace(_hoops_RHCSR->face);
	TextSize(instance->_hoops_IGGGH);

	width = TextWidth((void*)&_hoops_IPCSR, 0, 2);

/*
_hoops_IPRPR("_hoops_HACPC %_hoops_GHGP %_hoops_GHGP\_hoops_ACHP",(_hoops_SCSH)_hoops_IACPC, (_hoops_SCSH)_hoops_IGAA);
*/

#if 0
	*_hoops_GGGS = 0.0f;
	*_hoops_CPCSR = true;
	*_hoops_HPSRH=(void*)0;
#endif

	*_hoops_GGGS = (float)width;
	*_hoops_CPCSR = false;
	*_hoops_HPSRH=(void*)1;

	return true;
}

/*
 * _hoops_SRAC
 */
local void * 
load_font (Display_Context const * dc,
		   char const * name,
		   Font_Instance alter * instance) {

	OGLFontData alter *_hoops_RHCSR;
	Str255 pstr;
	short f;

	ALLOC (_hoops_RHCSR, OGLFontData);

#if 0
		c2pstrcpy(pstr,name);
		_hoops_RHCSR->family = FMGetFontFamilyFromName(pstr);
#else
		c2pstrcpy(pstr,name);
		GetFNum(pstr, &f);
		_hoops_RHCSR->family = f;
#endif
		
/*
_hoops_IPRPR("_hoops_CACPC %_hoops_GRI \_hoops_ACHP", _hoops_RSIRR);
*/
	if (_hoops_RHCSR->family == kInvalidFontFamily) {
		FREE (_hoops_RHCSR, OGLFontData);
		return 0;
	}

/*
_hoops_IPRPR("_hoops_CACPC _hoops_AICS\_hoops_ACHP");
*/
	_hoops_RHCSR->face=0;

	SET_MEMORY(_hoops_RHCSR->list, sizeof(GLuint)*0xFFFF,0);

	return (void *) _hoops_RHCSR;
}


/*
 * _hoops_SRAC
 */
local void
unload_font (Display_Context const * dc, Font_Instance alter *instance) 
{
	AGLM(OGLData alter *_hoops_CSRGR = OGLD (dc);)
	OGLFontData const *_hoops_RHCSR = (OGLFontData const *) instance->_hoops_GAASR;
	int i;

/*
_hoops_IPRPR("_hoops_SACPC\_hoops_ACHP");
*/
	if (!_hoops_RHCSR) return;

	for (i=0;i<0xFFFF;i++) {

		if (_hoops_RHCSR->list[i])
			glDeleteLists (_hoops_RHCSR->list[i], 1);
	}

	FREE (_hoops_RHCSR, OGLFontData);
}


/*****************************************************************************
 *****************************************************************************
 *****************************************************************************
 *****************************************************************************/

/*
 * _hoops_SRAC
 * _hoops_IPCP _hoops_GRGPR _hoops_IIGR _hoops_RGR _hoops_PCPH _hoops_HRGR _hoops_GIIA _hoops_HPP _hoops_GAAAH.
 * _hoops_HGI _hoops_PCPH _hoops_RAAAH _hoops_RH _hoops_CIACP _hoops_IIGR _hoops_RH _hoops_RII _hoops_SRAC _hoops_SICAR.
 */
local void
_hoops_RSCSR (_hoops_APARR alter & _hoops_RRCI) {

	/* _hoops_SISS _hoops_GASCA _hoops_CIPH */
	_hoops_RRCI->start_device = start_device;
	_hoops_RRCI->stop_device = stop_device;
	_hoops_RRCI->get_physical_info = get_physical_info;
	_hoops_RRCI->get_outer_window = get_outer_window;
	_hoops_RRCI->finish_update = finish_update;
	_hoops_RRCI->init_update = init_update;
	_hoops_RRCI->_hoops_HSCSP = _hoops_HSCSP;
	_hoops_RRCI->_hoops_ISCSP = _hoops_ISCSP;
	_hoops_RRCI->finish_picture = finish_picture;
	_hoops_RRCI->init_picture = init_picture;
	_hoops_RRCI->free_outer_window = free_outer_window;
	_hoops_RRCI->_hoops_RSCSP = _hoops_RSCSP;
	_hoops_RRCI->get_current_info = get_current_info;

	_hoops_RRCI->draw_overlay_list = draw_overlay_list;
	_hoops_RRCI->_hoops_SCPGR = _hoops_SCPGR;


	/* _hoops_RHCAC _hoops_SICAR */
	_hoops_RRCI->draw_dc_polyline = draw_dc_polyline;
	_hoops_RRCI->draw_dc_face = draw_dc_face;
	_hoops_RRCI->draw_dc_polytriangle = draw_dc_polytriangle;
	_hoops_RRCI->draw_dc_colorized_face = draw_dc_colorized_face;
	_hoops_RRCI->draw_dc_rgb32_rasters = draw_dc_rgb32_rasters;
	_hoops_RRCI->draw_dc_rectangle = draw_dc_rectangle;
	_hoops_RRCI->draw_dc_polydot = draw_dc_polydot;
	_hoops_RRCI->draw_dc_gouraud_polyline = draw_dc_gouraud_polyline;
	_hoops_RRCI->draw_dc_colorized_polyline = draw_dc_colorized_polyline;
	_hoops_RRCI->draw_dc_colorized_polydot = draw_dc_colorized_polydot;
	_hoops_RRCI->draw_dc_gouraud_polytriangle = draw_dc_gouraud_polytriangle;
	_hoops_RRCI->draw_dc_colorized_polytriangle = draw_dc_colorized_polytriangle;
#ifndef DISABLE_TEXTURING
	_hoops_RRCI->draw_dc_textured_polytriangle = draw_dc_textured_polytriangle;
#endif

	/* _hoops_AHCR _hoops_SRHR _hoops_PCPH */
	_hoops_RRCI->_hoops_CAAGR = _hoops_CAAGR;

	/* _hoops_PGSA 3D _hoops_SICAR */
	_hoops_RRCI->_hoops_CHCI = segment_render;

	_hoops_RRCI->draw_3d_polygon = draw_3d_polygon;
	_hoops_RRCI->draw_3d_ellipse = draw_3d_ellipse;
	_hoops_RRCI->draw_3d_polyline = draw_3d_polyline;
	_hoops_RRCI->draw_3d_tristrip = draw_3d_tristrip;
	_hoops_RRCI->draw_3d_polyedge = draw_3d_polyedge;
	_hoops_RRCI->draw_3d_marker = draw_3d_marker; 
	_hoops_RRCI->draw_3d_polymarker = draw_3d_polymarker;
	_hoops_RRCI->draw_3d_nurbs_curve = draw_3d_nurbs_curve;
	_hoops_RRCI->_hoops_ARCI = _hoops_ARCI; 
	_hoops_RRCI->_hoops_PPAS = _hoops_PPAS; 
	_hoops_RRCI->draw_3d_grid = draw_3d_grid; 
	_hoops_RRCI->draw_3d_text = draw_3d_text; 
	_hoops_RRCI->draw_3d_polycylinder = draw_3d_polycylinder; 
	_hoops_RRCI->draw_3d_cylinder = draw_3d_cylinder;
	_hoops_RRCI->draw_3d_sphere = draw_3d_sphere;
	/* _hoops_HPGR->_hoops_GPCPC = _hoops_GPCPC; */
	_hoops_RRCI->draw_3d_image = draw_3d_image;

	/* _hoops_AGCR _hoops_CGH _hoops_IIP _hoops_SHH _hoops_PIGS..._hoops_SR _hoops_PHCAC _hoops_RH _hoops_HHCAC _hoops_HSRPR _hoops_RPP _hoops_SSIA _hoops_AA... */
	_hoops_RRCI->_hoops_GSCGA = null;
	_hoops_RRCI->_hoops_CCCSR = null;
	_hoops_RRCI->_hoops_PSCGA = null;

	/* _hoops_HRCSR _hoops_PRCA */
	_hoops_RRCI->measure_char = measure_char;
	_hoops_RRCI->draw_dc_text = draw_dc_text;
	_hoops_RRCI->find_all_fonts = find_all_fonts;
	_hoops_RRCI->load_font = load_font;
	_hoops_RRCI->unload_font = unload_font;

	/* _hoops_AIRI _hoops_CPCI */
	_hoops_RRCI->_hoops_AICI = _hoops_AICI;
	_hoops_RRCI->_hoops_GGSI = _hoops_GGSI;
	_hoops_RRCI->_hoops_AIGC = _hoops_AIGC;
	_hoops_RRCI->_hoops_PPCI = _hoops_PPCI;

	_hoops_RRCI->_hoops_SSRGR = _hoops_SSRGR;
	_hoops_RRCI->_hoops_CGAGR = _hoops_CGAGR;

	_hoops_RRCI->snapshot = snapshot;
	_hoops_RRCI->_hoops_IGHGR = _hoops_IGHGR;

	/* _hoops_IAGIP _hoops_SICAR... _hoops_CCAH _hoops_GGR _hoops_AGAH 5.0 */
	_hoops_RRCI->create_region = create_region;
	_hoops_RRCI->_hoops_HIPGR = _hoops_HIPGR;
	_hoops_RRCI->_hoops_PIPGR = _hoops_PIPGR;
	_hoops_RRCI->_hoops_ISPGR = _hoops_ISPGR;
	_hoops_RRCI->_hoops_CSPGR = _hoops_CSPGR;
	_hoops_RRCI->_hoops_AGHGR = _hoops_AGHGR;

}/* _hoops_RSGR _hoops_API _hoops_SRAAH */


/*
 * _hoops_IAAAH _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_OpenGL_Driver (
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_GGAGR alter *			_hoops_GHRI,
	int						request,
	void *					request_info) 
{
	UNREFERENCED (request_info);
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR);
}

#if (_hoops_IARAC < _hoops_CARAC)
  /* _hoops_GSRS _hoops_CRRHA _hoops_IH _hoops_CGPR _hoops_SR _hoops_CHR _hoops_HHPS _hoops_GPP _hoops_RPAC _hoops_IRSP _hoops_IIGR _hoops_RH _hoops_RSHAC */
#error
  _hoops_ASHAC CGGLContextCreate = 0;
  aglSetPBufferProc aglSetPBuffer = 0;
  aglCreatePBufferProc aglCreatePBuffer = 0;
  aglDestroyPBufferProc aglDestroyPBuffer = 0;
#endif

#endif 
#endif



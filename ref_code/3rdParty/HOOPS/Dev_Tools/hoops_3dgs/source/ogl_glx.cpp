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
 * $Id: obf_tmp.txt 2.208 2010-12-10 03:32:35 covey Exp $
 */

#include "hoops.h"
#include "hd_proto.h"

#ifndef OSX_SYSTEM
#ifndef OPENGL_DRIVER

#include "hoops.h"
#include "hd_proto.h"

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

#else /* _hoops_ARGAC */

#include "hoops.h"
#include "hd_proto.h"

#ifndef __cplusplus
#define c_class class
#endif

#define _hoops_HHAGC
//#_hoops_PPIP _hoops_HCCPC

#define GLX_DRIVER
#define DECLARE_OGL_PROTOTYPES
#include "ogl.cpp"

/* _hoops_IRGH _hoops_GCAII _hoops_PIH: */
/*
 *  _hoops_SCSA _hoops_GCAII _hoops_PIH _hoops_HRGR _hoops_CCGC _hoops_CHHH, _hoops_HIH _hoops_GGR _hoops_RGR _hoops_AGIR _hoops_RH
 *  _hoops_PIRA _hoops_HRGR _hoops_IRS _hoops_PCPH _hoops_GRGPR _hoops_PGAP _hoops_CGH _hoops_IIP _hoops_AGRP _hoops_ARR _hoops_SCH'_hoops_GRI
 *  _hoops_RPII _hoops_CPSIA. _hoops_PHGP _hoops_RGR _hoops_HRGR _hoops_HHSH _hoops_IRS _hoops_IRIGR-_hoops_RGAR!
 */
static _hoops_PSISP _hoops_AGRPC;

#if 0
#define DEBUG_PRINTS 1
#endif

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

#if 0
int _hoops_ICCPC = 0;

static void
_hoops_CCCPC(const char *filename, const GLubyte *buffer, int width, int height)
{
   FILE *f = fopen( filename, "w" );
   if (f) {
      int i, x, y;
      const GLubyte *ptr = buffer;
      printf ("osdemo, writing tga file \n");
      fputc (0x00, f);  /* _hoops_RCC _hoops_GISHR, 0 => _hoops_CSH _hoops_RCC        */
      fputc (0x00, f);  /* _hoops_CSSGR _hoops_IPHH _hoops_GIIC, 0 => _hoops_CSH _hoops_HAIR _hoops_ARCR _hoops_PGPAA   */
      fputc (0x02, f);  /* _hoops_AARSP _hoops_GIIC, 2 => _hoops_SCCPC, _hoops_GSCPC-_hoops_HAIR _hoops_AARSP */
      fputc (0x00, f);  /* _hoops_CPR _hoops_HRGAH _hoops_GCSRR _hoops_CHR _hoops_AHCA _hoops_RH _hoops_HAIR _hoops_ARCR _hoops_AIRP */
      fputc (0x00, f);  /* 2 _hoops_GCSRR _hoops_SPPAH, 2 _hoops_GCSRR _hoops_SPCC, 1 _hoops_RAPSR _hoops_IGIR */
      fputc (0x00, f);
      fputc (0x00, f);
      fputc (0x00, f);
      fputc (0x00, f);  /* _hoops_SPCR-_hoops_CGRS _hoops_IIGR _hoops_AARSP    */
      fputc (0x00, f);
      fputc (0x00, f);  /* _hoops_GHCR-_hoops_CGRS _hoops_IIGR _hoops_AARSP    */
      fputc (0x00, f);
      fputc (width & 0xff, f);      /* _hoops_AARSP _hoops_AGAAH      */
      fputc ((width>>8) & 0xff, f);
      fputc (height & 0xff, f);     /* _hoops_AARSP _hoops_PGAAH     */
      fputc ((height>>8) & 0xff, f);
      fputc (0x18, f);          /* _hoops_SSHI _hoops_RGHSP, 0x18 => 24 _hoops_CRRAI */
      fputc (0x20, f);          /* _hoops_AARSP _hoops_RSCPC     */
      fclose(f);
      f = fopen( filename, "ab" );  /* _hoops_IIARC _hoops_GGR _hoops_PSHPR _hoops_CIGAA _hoops_CCH */
	for (y=height-1; y>=0; y--) {
         for (x=0; x<width; x++) {
            i = (y*width + x) * 4;
            fputc(ptr[i+2], f); /* _hoops_GGI _hoops_HRRRA */
            fputc(ptr[i+1], f); /* _hoops_GGI _hoops_ASSAA */
            fputc(ptr[i], f);   /* _hoops_GGI _hoops_PRRRA */
         }
      }
   }
}
#endif


/*
 * _hoops_SRAC
 */
local void
finish_picture (Net_Rendition const &  nr,
				bool swap_buffers) {
	Display_Context const *dc = nr->_hoops_SRA;
	OGLData *_hoops_CSRGR = OGLNRD (nr);

#ifdef DEBUG_PRINTS
fprintf(stderr, "finish_picture %p\n", (void*)_hoops_CSRGR);
#endif

	if (_hoops_CSRGR->_hoops_SARGC == _hoops_RPRGC)
		_hoops_GHRGC(_hoops_CSRGR);

	if (_hoops_CSRGR->_hoops_PIGRR != _hoops_IPSGR && 
		_hoops_CSRGR->_hoops_PIGRR != _hoops_CPSGR &&
		_hoops_CSRGR->_hoops_PIGRR != _hoops_SSRAC) {

		if (_hoops_CSRGR->_hoops_RPAAC->finish_picture) {
			/*
			 * _hoops_SIGP _hoops_ASCPC _hoops_SGS _hoops_SR _hoops_HHGC _hoops_IS _hoops_AA _hoops_IRS _hoops_PSCPC _hoops_PPR _hoops_HSCPC _hoops_GPAAC _hoops_SPR _hoops_IS _hoops_RCPP
			 * _hoops_SAGS _hoops_HAR _hoops_ISCPC _hoops_GPAAC _hoops_PPR _hoops_HIHH..._hoops_HIS _hoops_IPIHR _hoops_AHCA _hoops_CPAPC _hoops_HPIRA _hoops_PPR _hoops_SAHR _hoops_SGH
			 * _hoops_HIHH _hoops_IH _hoops_CPS...
			 */
			(*_hoops_CSRGR->_hoops_RPAAC->finish_picture) (nr, swap_buffers);
		}
	}

#ifdef _hoops_HRGAC
//	_hoops_RPP(_hoops_HGPGA->_hoops_PSHPC == _hoops_CSCPC) 
//		_hoops_SSCPC( _hoops_HGPGA->_hoops_GGSPC, _hoops_HGPGA->_hoops_RGSPC, _hoops_CRIAC,_hoops_HGPGA->_hoops_AGSPC->_hoops_IGAA ,_hoops_HGPGA->_hoops_AGSPC->_hoops_APPS); 
#endif

	glFlush ();
	if (dc->_hoops_RIGC->_hoops_HCPGR != 0)
		glFinish();

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR || 
		_hoops_CSRGR->_hoops_PIGRR == _hoops_CPSGR ||
		_hoops_CSRGR->_hoops_PIGRR == _hoops_SSRAC) {

		int w = _hoops_CSRGR->_hoops_IHGRR->width;
		int h = _hoops_CSRGR->_hoops_IHGRR->height;
		_hoops_AIGH *_hoops_AAIPC;  
		int i, j;

		if (!BIT (dc->flags, _hoops_SAISR))	// _hoops_PAHH _hoops_IASRH _hoops_ISHP _hoops_RH _hoops_RHPP
			return;

/* ??? _hoops_RRP _hoops_IS _hoops_SRGS _hoops_HH _hoops_GGR _hoops_IS _hoops_AGPGI _hoops_HII _hoops_IPIAC ... _hoops_AHPP _hoops_PII _hoops_SCH _hoops_HRGR _hoops_AIAH _hoops_IIH */
/* ??? _hoops_GHAP _hoops_PAH'_hoops_RA _hoops_IIGGR _hoops_IS _hoops_PGSPC _hoops_RCSC _hoops_HIH _hoops_GHAP'_hoops_SPHAI _hoops_HGSPC _hoops_GAR _hoops_SCH _hoops_ASAC _hoops_IRS _hoops_IHH _hoops_HHSPR */
	
		if(_hoops_CSRGR->_hoops_PIGRR != _hoops_SSRAC){
		if (!_hoops_CSRGR->output_image_scratch) {
			ALLOC_ARRAY(_hoops_AAIPC, w*h, _hoops_AIGH);
			_hoops_CSRGR->output_image_scratch = _hoops_AAIPC;
		}
		_hoops_AAIPC = (_hoops_AIGH alter *) _hoops_CSRGR->output_image_scratch;

#if !defined _hoops_HRGAC
		if (_hoops_CSRGR->_hoops_SRRRR)
			glReadBuffer(GL_BACK);
		else
			glReadBuffer(GL_FRONT);
#else
			glReadBuffer(GL_FRONT);
#endif

		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glPixelStorei(GL_PACK_ROW_LENGTH, 0);
		glReadPixels (0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, _hoops_AAIPC);
		_hoops_AAIPC = (_hoops_AIGH alter *) _hoops_CSRGR->output_image_scratch;
		}
		else{
			/*_hoops_SCSH _hoops_RPCC = 0;
			_hoops_IGSPC(_hoops_HGPGA->_hoops_GGSPC, &_hoops_SSCHA, &_hoops_GGHR, &_hoops_RPCC, &_hoops_HGPGA->_hoops_RGSPC);
			_hoops_GSPR _hoops_CGSPC[120];
			_hoops_SGSPC(_hoops_CGSPC, "_hoops_GRSPC%_hoops_GHGP._hoops_RRSPC", _hoops_ARSPC++);
			 _hoops_PRSPC(_hoops_CGSPC, (_hoops_RCIC _hoops_HRSPC*)_hoops_HGPGA->_hoops_RGSPC, _hoops_SSCHA, _hoops_GGHR);*/
			_hoops_AAIPC = (_hoops_AIGH alter *) _hoops_CSRGR->_hoops_IHPAC;
		}

		if (_hoops_CSRGR->_hoops_IHGRR->format == Image_RGBA32 
#ifdef RGB32_ORDER_RGBA
			|| _hoops_CSRGR->_hoops_IHGRR->format == _hoops_CSGSP 
#endif
		) {
			_hoops_AIGH *_hoops_PAIPC;  
		    _hoops_PAIPC = (_hoops_AIGH alter *)_hoops_CSRGR->_hoops_IHGRR->_hoops_PHGH;
			for (i = 0 ; i < h ; i++)
				_hoops_AIGA(_hoops_AAIPC + w*i, w, RGBAS32, _hoops_PAIPC + w*(h-i-1));
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

		HI_Clear_Image_Cache(_hoops_CSRGR->_hoops_IHGRR);

		HI_Set_Delayed_Activity (_hoops_CSRGR->_hoops_IHGRR->owner, _hoops_IHSSR,
								 _hoops_CSRGR->_hoops_IHGRR, _hoops_HHSSR);

	}

	if (_hoops_CSRGR->_hoops_PIGRR != _hoops_CPSGR && _hoops_CSRGR->_hoops_PIGRR != _hoops_SSRAC) {

		if (swap_buffers && 
			!BIT(nr->_hoops_SRA->flags, _hoops_CHSI))
			glXSwapBuffers (_hoops_CSRGR->display, _hoops_CSRGR->window);
	}

#if !defined _hoops_HRGAC
	glXMakeCurrent (_hoops_CSRGR->display, 0, 0);
#endif

	if (_hoops_CSRGR->_hoops_PISGC) {
		delete _hoops_CSRGR->_hoops_PISGC;
		_hoops_CSRGR->_hoops_PISGC = null;
	}
}


/*
 * _hoops_SRAC
 */
local void
init_picture (Net_Rendition const &  nr) 
{
	Display_Context const *dc = nr->_hoops_SRA;
	OGLData alter *_hoops_CSRGR = OGLNRD (nr);
	int i;

#ifdef DEBUG_PRINTS
fprintf(stderr, "init_picture %p\n", (void*)_hoops_CSRGR);
#endif

#if !defined _hoops_HRGAC
	if (glXMakeCurrent (_hoops_CSRGR->display, _hoops_CSRGR->window, _hoops_CSRGR->context) == GL_FALSE) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "glXMakeCurrent failed for init_picture.");
		HD_Kill_Driver (nr->_hoops_SRA);
		return;
	}
#endif

	if (dc->_hoops_RIGC->_hoops_HCPGR == 0)
		glFinish();

#if !defined _hoops_HRGAC
	FORCE_DRAW_MODE (_hoops_CSRGR, _hoops_CSRGR->_hoops_CSC._hoops_GGAGC);
#endif

	FORCE_SCISSOR_OFF(_hoops_CSRGR);
	for (i = 0 ; i < OGL_MAX_TEXTURE_UNITS ; i++)
		_hoops_SGGAC(_hoops_CSRGR, i);
	_hoops_HAHAC(_hoops_CSRGR);
	if (_hoops_CSRGR->_hoops_SHCGC)
		_hoops_IIPAC(_hoops_CSRGR);
	_hoops_PHHAC(_hoops_CSRGR, _hoops_CSRGR->_hoops_CSC._hoops_CGAGC);

	_hoops_CAAGC(_hoops_CSRGR);
	_hoops_AAHAC(_hoops_CSRGR);
	INVALIDATE_PIXEL_UNPACK_ALIGNMENT(_hoops_CSRGR);
	_hoops_CSRGR->_hoops_PPAGC = false;
	if (BIT(nr->transform_rendition->flags , _hoops_PIHIP))
		FORCE_DEPTH_FUNCTION(_hoops_CSRGR, GL_GREATER);
	else
		FORCE_DEPTH_FUNCTION(_hoops_CSRGR, GL_LEQUAL);
	_hoops_AHPRR(_hoops_CSRGR,!nr->_hoops_IRR->_hoops_GIRC);


	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_SSRAC){

		int _hoops_IRSPC = _hoops_CSRGR->_hoops_IHGRR->width;
		int _hoops_CRSPC = _hoops_CSRGR->_hoops_IHGRR->height;
		/* _hoops_IIPP _hoops_RH _hoops_CSCR _hoops_SRHR */
		//_hoops_SRSPC(_hoops_HGPGA->_hoops_RGSPC, _hoops_GASPC*_hoops_RASPC , _hoops_GCAGI);
		for(int k = 0; k < _hoops_IRSPC*_hoops_CRSPC*4; k+=4){
			((char*)_hoops_CSRGR->_hoops_IHPAC)[k] = 10;
			((char*)_hoops_CSRGR->_hoops_IHPAC)[k+1] = 140;
			((char*)_hoops_CSRGR->_hoops_IHPAC)[k+2] = 200;
		}

		/* _hoops_IARP _hoops_RH _hoops_SRHR _hoops_IS _hoops_RH _hoops_GGSC _hoops_PPR _hoops_IRHH _hoops_SCH _hoops_SCGR */
#ifdef _hoops_HRGAC
		if (!_hoops_AASPC( _hoops_CSRGR->_hoops_HHPAC, _hoops_CSRGR->_hoops_IHPAC, GL_UNSIGNED_BYTE,_hoops_CSRGR->_hoops_IHGRR->width ,_hoops_CSRGR->_hoops_IHGRR->height)) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "OSMesaMakeCurrent failed for init_picture.");
			HD_Kill_Driver (nr->_hoops_SRA);
			return;
		}
#endif
		int z, s, a;
		glGetIntegerv(GL_DEPTH_BITS, &z);
		glGetIntegerv(GL_STENCIL_BITS, &s);
		glGetIntegerv(GL_ACCUM_RED_BITS, &a);

		if(z == 0){
			z += 1;
		}
	}

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_CPSGR) {

		if (!_hoops_PIAGC(_hoops_CSRGR)) {

#ifdef DEBUG_PRINTS
fprintf(stderr, "common_make_fbo_current failed!!! ack... time to die...\n");
#endif
			/* _hoops_RRP _hoops_IS _hoops_GGAS ??? */
	
			_hoops_IHAGC(_hoops_CSRGR);

			/*
			_hoops_PASPC (_hoops_CSPH);
			*/
			return;
		}

#if 0
#ifdef DEBUG_PRINTS
fprintf(stderr, "common_make_fbo_current worked!!!\n");
#endif
#endif
	}

	if (_hoops_CSRGR->_hoops_PIGRR != _hoops_IPSGR && 
		_hoops_CSRGR->_hoops_PIGRR != _hoops_CPSGR &&
		_hoops_CSRGR->_hoops_PIGRR != _hoops_SSRAC) {

		if (_hoops_CSRGR->_hoops_RPAAC->init_picture)
			(*_hoops_CSRGR->_hoops_RPAAC->init_picture) (nr);
	}

	if (_hoops_CSRGR->_hoops_SRRRR)
		glDrawBuffer (GL_BACK);
	else{
		if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_SINGLE_BUFFERING))
			glDrawBuffer (GL_FRONT_AND_BACK);
		else glDrawBuffer (GL_FRONT);
	}

	_hoops_CSRGR->_hoops_RIRGC =
		XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_SPOTLIGHT_TEXTURE) ||
		BIT(nr->_hoops_SRA->options.flags, Drivo_VERTEX_SPOTLIGHT);
}



/*
 * _hoops_SRAC
 */
local void
finish_update (Display_Context const * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

#ifdef DEBUG_PRINTS
fprintf(stderr, "finish_update %p\n", (void*)_hoops_CSRGR);
#endif

	if (_hoops_CSRGR->_hoops_PIGRR != _hoops_IPSGR && 
		_hoops_CSRGR->_hoops_PIGRR != _hoops_CPSGR &&
		_hoops_CSRGR->_hoops_PIGRR != _hoops_SSRAC) {

		if (_hoops_CSRGR->_hoops_RPAAC->finish_update)
			(*_hoops_CSRGR->_hoops_RPAAC->finish_update) (dc);

	}

	if (glXGetCurrentContext ())
		glFlush ();
}


/*
 * _hoops_SRAC
 */
local void
init_update (Display_Context const * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

#ifdef DEBUG_PRINTS
fprintf(stderr, "init_update %p\n", (void*)_hoops_CSRGR);
#endif

	invalidate_cache(_hoops_CSRGR);

	if (_hoops_CSRGR->_hoops_PIGRR != _hoops_IPSGR && 
		_hoops_CSRGR->_hoops_PIGRR != _hoops_CPSGR &&
		_hoops_CSRGR->_hoops_PIGRR != _hoops_SSRAC) {

		if (_hoops_CSRGR->_hoops_RPAAC->init_update) {
			X11Data alter *_hoops_RRRPC = X11D (dc);

			(*_hoops_CSRGR->_hoops_RPAAC->init_update) (dc);
			_hoops_CSRGR->window_width = _hoops_RRRPC->window_width;
			_hoops_CSRGR->window_height = _hoops_RRRPC->window_height;
		}
	}
}


/*****************************************************************************
 *****************************************************************************
			    _hoops_ARRPC _hoops_IAIGC
 *****************************************************************************
 *****************************************************************************/


/*
 * _hoops_RHCS _hoops_RPP _hoops_SR _hoops_AIR _hoops_PSCA _hoops_CHR _hoops_HHPA _hoops_IH _hoops_IRS _hoops_SAGHR _hoops_SPCR _hoops_SHPR.
 * _hoops_CPIRH:  _hoops_PRRPC - _hoops_RH _hoops_SPCR _hoops_AIRI
 *         _hoops_SHPR - _hoops_SHPR _hoops_PHI
 * _hoops_HCGAR:  0 = _hoops_AIR _hoops_PSCA _hoops_HAR _hoops_HHPA.
 *          1 = _hoops_AIR _hoops_PSCA _hoops_CHR _hoops_HHPA.
 */
local int has_pbuffers(Display *_hoops_HRRPC, int screen)
{
   char *extensions;
    extensions = (char *) glXQueryServerString(_hoops_HRRPC, screen, GLX_EXTENSIONS);

    if (!extensions ||
	!strstr(extensions,"GLX_SGIX_fbconfig") ||
	!strstr(extensions,"GLX_SGIX_pbuffer"))
	return 0;
    else
        return 1;
}


/* _hoops_HGI _hoops_HRGR _hoops_RGAR _hoops_IGI _hoops_HPP _hoops_IRRPC() */
local int XErrorFlag = 0;
local int _hoops_CRRPC(Display *_hoops_HRRPC, XErrorEvent *event)   
{
    XErrorFlag = 1;
    return 0;
}

#ifdef HPUX_SYSTEM
#define _hoops_SRRPC
#endif

#ifndef _hoops_SRRPC
/*
 * _hoops_HII _hoops_GARPC _hoops_GCCHI'_hoops_GRI _hoops_IGRGC (_hoops_SHII _hoops_IS _hoops_ASSS _hoops_IH _hoops_RARPC)
 * 
 * _hoops_GISA _hoops_IRS _hoops_AIR _hoops_SRHR.  _hoops_PS _hoops_HAPR _hoops_IAPR _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_AARPC _hoops_IRCC _hoops_IS _hoops_ARPR
 * _hoops_IRS _hoops_AIR _hoops_SRHR.  _hoops_PS _hoops_ASRC _hoops_RH _hoops_SRS _hoops_AIR _hoops_SRHR _hoops_PGAP _hoops_SR _hoops_PPHRH 
 * _hoops_ARPR.  _hoops_HGI _hoops_API _hoops_PARPC _hoops_RH _hoops_HARPC _hoops_IIGR _hoops_GACH _hoops_CCA _hoops_IARPC _hoops_SPCR
 * _hoops_CARPC _hoops_SPHS.
 *
 * _hoops_CPIRH:  _hoops_PRRPC - _hoops_RH _hoops_SPCR _hoops_AIRI
 *         _hoops_SARPC - _hoops_PCCP _hoops_GPRPC _hoops_GAR _hoops_GIIA _hoops_HPP _hoops_RPRPC().
 *         _hoops_IGAA, _hoops_APPS - _hoops_IGIR _hoops_IIGR _hoops_AIR _hoops_SRHR _hoops_IS _hoops_IAGC, _hoops_GGR _hoops_ASPA. 
 *         _hoops_APRPC - _hoops_HIGR _hoops_IIGR _hoops_AIR _hoops_SRHR _hoops_AIRC _hoops_GAR _hoops_IGI _hoops_HPP
 *                     _hoops_PPRPC().
 * _hoops_HCGAR:  _hoops_IRS _hoops_AIR _hoops_SRHR _hoops_PAR _hoops_GHHSI.
 */
local GLXPbuffer
_hoops_HPRPC(Display *_hoops_HRRPC, GLXFBConfig _hoops_IPRPC,
               int width, int height, int *_hoops_CPRPC)
{
   int (*_hoops_SPRPC)(Display *, XErrorEvent *);
   GLXPbuffer _hoops_GHRPC = None;
   int i;

   /* _hoops_SCASR _hoops_SPCR _hoops_CARPC _hoops_SPHS _hoops_CCA _hoops_ISCP _hoops_HAII _hoops_RIHH _hoops_HARPR */
   _hoops_SPRPC = XSetErrorHandler(_hoops_CRRPC);

   XErrorFlag = 0;

#ifdef _hoops_RHRPC
   _hoops_GHRPC = glXCreateGLXPbufferSGIX(_hoops_HRRPC, _hoops_IPRPC, width, height, _hoops_CPRPC);
#else
   {
      int _hoops_AHRPC[128];
      _hoops_AHRPC[0] = GLX_PBUFFER_WIDTH;
      _hoops_AHRPC[1] = width;
      _hoops_AHRPC[2] = GLX_PBUFFER_HEIGHT;
      _hoops_AHRPC[3] = height;
      for (i = 0 ; _hoops_CPRPC[i] != None ; i += 2) {
         _hoops_AHRPC[i+4] = _hoops_CPRPC[i];
         _hoops_AHRPC[i+5] = _hoops_CPRPC[i+1];
      }
      _hoops_AHRPC[i+4] = None;
      _hoops_GHRPC = glXCreatePbuffer (_hoops_HRRPC, _hoops_IPRPC, _hoops_AHRPC); 
   }
#endif

   /* _hoops_IPRP _hoops_GIGR _hoops_SPCR _hoops_RIHH _hoops_HARPR */
   (void) XSetErrorHandler(_hoops_SPRPC);

   /* _hoops_HCGAR _hoops_CGSRC (_hoops_GHCA _hoops_SHH _hoops_GHHSI) */
   if (!XErrorFlag && _hoops_GHRPC!=None) {
#ifdef DEBUG_PRINTS
      fprintf(stderr, "config %d worked!\n", i);
#endif
      return _hoops_GHRPC;
   }
   else {
      return None;
   }
}


#define _hoops_PHRPC 4
/*
 * _hoops_GISA _hoops_RH _hoops_CGSRC _hoops_PPR _hoops_ASRC _hoops_IRS _hoops_HHRPC _hoops_RGHH.
 * _hoops_IRGGR _hoops_GPP _hoops_GARPC _hoops_GCCHI'_hoops_GRI _hoops_IGRGC _hoops_HII _hoops_IHRPC 97 _hoops_IPGAA 24
 */
local int 
_hoops_CHPGA(
		Display *_hoops_HRRPC, 
		int screen, 
		int width, 
		int height, 
		GLXPbuffer *_hoops_CHRPC, 
		GLXContext *_hoops_SHRPC,
		XVisualInfo **_hoops_RPIPR)
{
	int _hoops_GIRPC[_hoops_PHRPC][100] = {
		{
			/* _hoops_CCRAA _hoops_ACHGR, _hoops_CCA _hoops_HCH _hoops_SRHR */
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_DRAWABLE_TYPE, GLX_PIXMAP_BIT,
			GLX_RED_SIZE, 1,
			GLX_GREEN_SIZE, 1,
			GLX_BLUE_SIZE, 1,
			GLX_DEPTH_SIZE, 1,
			GLX_DOUBLEBUFFER, 1,
			GLX_STENCIL_SIZE, 0,
			None
		},
		{
			/* _hoops_GRAAH _hoops_ACHGR, _hoops_CCA _hoops_HCH _hoops_SRHR */
			GLX_RENDER_TYPE, GLX_RGBA_BIT,   
			GLX_DRAWABLE_TYPE, GLX_PIXMAP_BIT,
			GLX_RED_SIZE, 1,
			GLX_GREEN_SIZE, 1,
			GLX_BLUE_SIZE, 1,
			GLX_DEPTH_SIZE, 1,
			GLX_DOUBLEBUFFER, 0,
			GLX_STENCIL_SIZE, 0,
			None
		},
		{
			/* _hoops_GRAAH _hoops_ACHGR, _hoops_SIHH _hoops_HCH _hoops_SRHR */
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_DRAWABLE_TYPE, GLX_PIXMAP_BIT,
			GLX_RED_SIZE, 1,
			GLX_GREEN_SIZE, 1,
			GLX_BLUE_SIZE, 1,
			GLX_DEPTH_SIZE, 0,
			GLX_DOUBLEBUFFER, 0,
			GLX_STENCIL_SIZE, 0,
			None
		},
		{
			/* _hoops_CCRAA _hoops_ACHGR, _hoops_SIHH _hoops_HCH _hoops_SRHR */
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_DRAWABLE_TYPE, GLX_PIXMAP_BIT,
			GLX_RED_SIZE, 1,
			GLX_GREEN_SIZE, 1,
			GLX_BLUE_SIZE, 1,
			GLX_DEPTH_SIZE, 0,
			GLX_DOUBLEBUFFER, 1,
			GLX_STENCIL_SIZE, 0,
			None
		}
	};
	int _hoops_CPRPC[] = {
		GLX_LARGEST_PBUFFER, True,
		GLX_PRESERVED_CONTENTS, False,
		None
	};
	GLXFBConfig *_hoops_RIRPC = null, _hoops_AIRPC;
	GLXPbuffer _hoops_GHRPC = None;
	int _hoops_PIRPC;
	int i;
	int _hoops_HSIRI;
	XVisualInfo *_hoops_HIRPC = NULL;
	int valid = 0;
	GLXContext _hoops_HSHAC;

#if 0
#ifdef DEBUG_PRINTS
#define _hoops_IIRPC
#endif
#endif

	/* _hoops_RHCS _hoops_SGS _hoops_SRGAC _hoops_CHR _hoops_HHPA */
	if (!has_pbuffers(_hoops_HRRPC, screen)) {
#ifdef _hoops_IIRPC
		fprintf(stderr, "Error: pbuffers not available on this screen\n");
#endif
		return 0;
	}

	for (_hoops_HSIRI = 0 ; _hoops_HSIRI < _hoops_PHRPC && !valid ; _hoops_HSIRI++)	 {

		/* _hoops_SIPR _hoops_HIGR _hoops_IIGR _hoops_SSRR _hoops_HCHSR _hoops_SRHR _hoops_GIGAA */
		_hoops_RIRPC = glXChooseFBConfig(_hoops_HRRPC, screen, _hoops_GIRPC[_hoops_HSIRI], &_hoops_PIRPC);
		if (_hoops_PIRPC==0 || !_hoops_RIRPC) {
#ifdef _hoops_IIRPC
			fprintf(stderr, "Error: glxChooseFBConfig failed\n");
#endif
			return 0;
		}

#ifdef _hoops_IIRPC
		for (i=0;i<_hoops_PIRPC;i++) {
			fprintf(stderr, "Config %d\n", i);
			/*
			_hoops_CIRPC(_hoops_PRRPC, _hoops_SIRPC[_hoops_HAS], 0);
			*/
		}
#endif

		/* _hoops_GISA _hoops_RH _hoops_CGSRC _hoops_GRP _hoops_SRS _hoops_SARPC _hoops_GGR _hoops_RH _hoops_HIGR _hoops_SGS _hoops_IIAH. */
		for (i = 0 ; i < _hoops_PIRPC && !valid ; i++) {
			_hoops_GHRPC = _hoops_HPRPC(_hoops_HRRPC, _hoops_RIRPC[i], width, height, _hoops_CPRPC);
			_hoops_HIRPC = glXGetVisualFromFBConfig(_hoops_HRRPC, _hoops_RIRPC[i]);
			valid = (_hoops_GHRPC != 0 && _hoops_HIRPC != 0);
			if (valid)
				_hoops_AIRPC = _hoops_RIRPC[i];
			else if (_hoops_HIRPC)
		 		XFree(_hoops_HIRPC);
		}
	}
	if (!valid) {
#ifdef _hoops_IIRPC
		fprintf(stderr, "couldn't get a pbuffer");
#endif
		return 0;
	}

	_hoops_HSHAC = glXCreateContext(_hoops_HRRPC, _hoops_HIRPC, NULL, True);
	if (!_hoops_HSHAC) {
		/* _hoops_HPPR _hoops_GCRPC */
		_hoops_HSHAC = glXCreateContext(_hoops_HRRPC, _hoops_HIRPC, NULL, False);
		if (!_hoops_HSHAC) {
#ifdef _hoops_IIRPC
			fprintf(stderr, "Error: Couldn't create GLXContext\n");
#endif
			return 0;
		}
		else {
#ifdef _hoops_IIRPC
			fprintf(stderr, "Warning: using indirect GLXContext\n");
#endif
		}
	}

	if (_hoops_GHRPC == None) {
#ifdef _hoops_IIRPC
		fprintf(stderr, "failed to create pbuffer in function create_pbuffer\n");
#endif
		return 0;
	}
	*_hoops_CHRPC = _hoops_GHRPC;
	if (!glXMakeCurrent(_hoops_HRRPC, _hoops_GHRPC, _hoops_HSHAC)) {
#ifdef _hoops_IIRPC
		fprintf(stderr, "Error: glXMakeCurrent failed in function create_pbuffer\n");
#endif
		XFree(_hoops_HIRPC);
		return 0;
	}
	*_hoops_SHRPC = _hoops_HSHAC;
	*_hoops_RPIPR = _hoops_HIRPC;

	XFree(_hoops_RIRPC);
	return 1;

} /* _hoops_RSGR _hoops_API '_hoops_ARPR _hoops_CGSRC' */

#else

local int 
_hoops_CHPGA(
		Display *_hoops_HRRPC, 
		int screen, 
		int width, 
		int height, 
		GLXPbuffer *_hoops_CHRPC, 
		GLXContext *_hoops_SHRPC,
		XVisualInfo **_hoops_RPIPR)
{
	return 0;
}

#endif /* _hoops_RCRPC */

/*****************************************************************************
 *****************************************************************************
							_hoops_PPSRH
 *****************************************************************************
 *****************************************************************************/

struct OGLFontData {
	GLuint list[0xFFFF];
};


/*
 * _hoops_SRAC
 */
local void
draw_dc_text (Net_Rendition const &  nr,
			  DC_Point const * where,
			  int count, Karacter const * kstring) {


	/* _hoops_RGR _hoops_GRS _hoops_HGAP _hoops_IRS _hoops_ARGHR _hoops_IIGR _hoops_IPHR
	 * _hoops_ACRPC _hoops_GRS _hoops_IRHH _hoops_SSSCI _hoops_IIGR _hoops_PAPR _hoops_GSPIP _hoops_HIH _hoops_PCPA _hoops_AHCA _hoops_PCRPC _hoops_PPR
	 * _hoops_CSCHA?  _hoops_HCRPC _hoops_GRS _hoops_HS _hoops_IS _hoops_IHAAR _hoops_IRHH _hoops_RH _hoops_SSSCI _hoops_IH _hoops_CAPR _hoops_PPR _hoops_AA _hoops_RH
	 * _hoops_ICRPC/_hoops_GPAAC _hoops_PPRRR _hoops_IIGR _hoops_CCRPC _hoops_SIH _hoops_IS _hoops_CAHP _hoops_HGRAR/_hoops_SCRPC _hoops_HCGR.
	 * _hoops_HCRPC _hoops_PAH _hoops_HGIHR _hoops_RH _hoops_GPAAC _hoops_RHPP _hoops_HPP _hoops_RCPH _hoops_SRCIA _hoops_CIPH _hoops_SAHR _hoops_RAS _hoops_CPS
	 * _hoops_SSCP _hoops_RPII _hoops_CIIAR _hoops_CRGR _hoops_IRS _hoops_PSSCI...
	 */
	_hoops_IGCSR const &_hoops_HRCIR = nr->_hoops_SISI;
	OGLData alter *_hoops_CSRGR = OGLD (nr->_hoops_SRA);
	_hoops_GSRPC alter *_hoops_RSRPC = (_hoops_GSRPC alter *) (_hoops_HRCIR->font->_hoops_GAASR);
	OGLFontData alter *_hoops_RHCSR = (OGLFontData alter *) _hoops_RSRPC->_hoops_CSSGA;

#ifdef DEBUG_PRINTS
fprintf(stderr, "draw_dc_text\n");
#endif

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

	if ((_hoops_HRCIR->rotation < 45.0 || _hoops_HRCIR->rotation >= 315.0) && _hoops_HRCIR->_hoops_IPGRP == 0.0) {

		int n;

		/* _hoops_SR _hoops_RRP _hoops_RH 0.5'_hoops_GRI _hoops_IS _hoops_SRCH _hoops_ASRPC _hoops_PSAP _hoops_RH _hoops_ICIH _hoops_CGPR _hoops_RH _hoops_PSRPC
		 * _hoops_HRGR _hoops_CISI */
		glRasterPos3f (0.5f, 0.5f, (GLfloat) where->z);
		glBitmap (0, 0, 0, 0, (GLfloat) where->x, (GLfloat) where->y, (GLubyte *) 0);

		for (n=0; n<count; n++) {

			int c = kstring[n];

			/*_hoops_SIGP _hoops_PAAP _hoops_RGR*/
			if (!_hoops_RHCSR->list[c]) {

				_hoops_RHCSR->list[c] = glGenLists (1);

				if (_hoops_RHCSR->list[c]) 
					glXUseXFont (_hoops_RSRPC->_hoops_HSRPC->fid, c, 1, _hoops_RHCSR->list[c]);
			}

			if (_hoops_RHCSR->list[c]) {
				glCallList(_hoops_RHCSR->list[c]);
			}
		}
	}
	else {
		HD_Draw_Dead_Font(nr, _hoops_HRCIR->font, (Point*)where, count, kstring, 0);
	}

	_hoops_RIHAC(_hoops_CSRGR);
}

/*
 * _hoops_SRAC
 */
local void
_hoops_CACSR (Display_Context alter * dc) {
	OGLData const *_hoops_CSRGR = OGLD (dc);

	if (_hoops_CSRGR->_hoops_RPAAC->_hoops_CACSR)
		(*_hoops_CSRGR->_hoops_RPAAC->_hoops_CACSR) (dc);
}

/*
 * _hoops_SRAC
 */
local void
find_all_fonts (Display_Context alter * dc) {
	OGLData const *_hoops_CSRGR = OGLD (dc);

	if (_hoops_CSRGR->_hoops_RPAAC->find_all_fonts)
		(*_hoops_CSRGR->_hoops_RPAAC->find_all_fonts) (dc);
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
	OGLData const *_hoops_CSRGR = OGLD (nr->_hoops_SRA);

	if (_hoops_CSRGR->_hoops_RPAAC->measure_char)
		return (*_hoops_CSRGR->_hoops_RPAAC->measure_char) 
			(nr, instance, _hoops_IPCSR, _hoops_GGGS, _hoops_CPCSR, _hoops_HPSRH);
	else
		return false;
}

/*
 * _hoops_SRAC
 */
local void * 
load_font (Display_Context const * dc,
		   char const * name,
		   Font_Instance alter * instance) {

	OGLData const *_hoops_CSRGR = OGLD (dc);
	_hoops_GSRPC alter *_hoops_RSRPC;
	OGLFontData alter *_hoops_RHCSR;

#if !defined _hoops_HRGAC
	if (_hoops_CSRGR->_hoops_RPAAC->load_font)
		_hoops_RSRPC = (_hoops_GSRPC alter *) ((*_hoops_CSRGR->_hoops_RPAAC->load_font) (dc, name, instance));
	else
#endif
		return 0;

	if (_hoops_RSRPC == null)
		return 0;

	instance->_hoops_HRGGH = true;

	ALLOC (_hoops_RHCSR, OGLFontData);

	{
		int i;
		for (i=0;i<0xFFFF;i++)
			_hoops_RHCSR->list[i] = 0;
	}

	_hoops_RSRPC->_hoops_CSSGA = _hoops_RHCSR;
	return (void *) _hoops_RSRPC;
}


/*
 * _hoops_SRAC
 */
local void HC_CDECL _hoops_SRCSR (
	Net_Rendition const &	nr,
	Font_Instance const		*instance,
	Point const				*position,
	int							count,
	Karacter const			*_hoops_IHSCP,
	Vector const				*scale) {

	HD_Draw_Stenciled_Font (nr, instance, position, count, _hoops_IHSCP, scale);
	
}


/*
 * _hoops_SRAC
 */
local void
unload_font (Display_Context const * dc, 
			 Font_Instance alter *instance) 
{
#if !defined _hoops_HRGAC
	OGLData const *_hoops_CSRGR = OGLD (dc);
	_hoops_GSRPC alter *_hoops_RSRPC = (_hoops_GSRPC alter *) instance->_hoops_GAASR;
	OGLFontData const *_hoops_RHCSR;

	if (!_hoops_RSRPC) 
		return;
	_hoops_RHCSR = (OGLFontData*) _hoops_RSRPC->_hoops_CSSGA;
	if (!_hoops_RHCSR) 
		return;

	{
		int i;
		for (i=0;i<0xFFFF;i++) {

			if (_hoops_RHCSR->list[i])
				glDeleteLists (_hoops_RHCSR->list[i], 1);
		}
	}

	FREE (_hoops_RHCSR, OGLFontData);

	if (_hoops_CSRGR->_hoops_RPAAC->unload_font)
		(*_hoops_CSRGR->_hoops_RPAAC->unload_font) (dc, instance);
#endif
}


#ifndef GLX_SAMPLE_BUFFERS_ARB
#define GLX_SAMPLE_BUFFERS_ARB	100000
#endif
#ifndef GLX_SAMPLES_ARB
#define GLX_SAMPLES_ARB			100001
#endif


/*
 * _hoops_SRAC
 */
local XVisualInfo * _hoops_ISRPC(
		Display_Context const * dc,
		Display alter *display) {


	/*
	_hoops_HASPC _hoops_RAPC *_hoops_HGPGA = _hoops_CSRPC (_hoops_CSPH);
	*/

	XVisualInfo *visual = 0;
	int _hoops_IPPGR[32];
	int index;

	/*_hoops_IIAPR _hoops_SSRPC _hoops_HSRRH _hoops_GGAPC*/
	index = 0;
	_hoops_IPPGR[index++] = GLX_RGBA;
	_hoops_IPPGR[index++] = GLX_DEPTH_SIZE;
	_hoops_IPPGR[index++] = 1;	
	_hoops_IPPGR[index++] = GLX_RED_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_BLUE_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_GREEN_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_ALPHA_SIZE;
	_hoops_IPPGR[index++] = 1;
	if (dc->options._hoops_PIPGA) { 
		_hoops_IPPGR[index++] = GLX_STENCIL_SIZE;
		_hoops_IPPGR[index++] = 1;
	}
	if (dc->options._hoops_AHIIP) {
		_hoops_IPPGR[index++] = GLX_STEREO;
	}
	if (dc->options._hoops_RIPGA) {
		_hoops_IPPGR[index++] = GLX_SAMPLE_BUFFERS_ARB;
		_hoops_IPPGR[index++] = 1;
		/*_hoops_RGAPC _hoops_RGRRH _hoops_GHGPR _hoops_RHGPR*/
		_hoops_IPPGR[index++] = GLX_DOUBLEBUFFER;
	}else{
#if defined(HPUX_SYSTEM) || defined(IRIX_SYSTEM)
/* _hoops_IASPC _hoops_PPR _hoops_GRCHH _hoops_AHPP _hoops_IS _hoops_HS _hoops_AHCI _hoops_SGAPC _hoops_CASPC _hoops_RSRA _hoops_RHGPR. */
		_hoops_IPPGR[index++] = GLX_DOUBLEBUFFER;
#else
		 if (dc->options._hoops_SRRRR) 
			 _hoops_IPPGR[index++] = GLX_DOUBLEBUFFER;
#endif
	}
	_hoops_IPPGR[index] = None;

	visual = glXChooseVisual (display, DefaultScreen (display), _hoops_IPPGR);

	if (visual) return visual;


	/*_hoops_AGAPC _hoops_HGHRR*/
	index = 0;
	_hoops_IPPGR[index++] = GLX_RGBA;
	_hoops_IPPGR[index++] = GLX_DEPTH_SIZE;
	_hoops_IPPGR[index++] = 1;	
	_hoops_IPPGR[index++] = GLX_RED_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_BLUE_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_GREEN_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_ALPHA_SIZE;
	_hoops_IPPGR[index++] = 1;

	if (dc->options._hoops_AHIIP) {
		_hoops_IPPGR[index++] = GLX_STEREO;
	}
	if (dc->options._hoops_RIPGA) {
		_hoops_IPPGR[index++] = GLX_SAMPLE_BUFFERS_ARB;
		_hoops_IPPGR[index++] = 1;
		/*_hoops_RGAPC _hoops_RGRRH _hoops_GHGPR _hoops_RHGPR*/
		_hoops_IPPGR[index++] = GLX_DOUBLEBUFFER;
	}else{
		 if (dc->options._hoops_SRRRR) 
				_hoops_IPPGR[index++] = GLX_DOUBLEBUFFER;
	}
	_hoops_IPPGR[index] = None;

	visual = glXChooseVisual (display, DefaultScreen (display), _hoops_IPPGR);

	if (visual) return visual;


	/*_hoops_AGAPC _hoops_PGAPC*/
	index = 0;
	_hoops_IPPGR[index++] = GLX_RGBA;
	_hoops_IPPGR[index++] = GLX_DEPTH_SIZE;
	_hoops_IPPGR[index++] = 1;	
	_hoops_IPPGR[index++] = GLX_RED_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_BLUE_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_GREEN_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_ALPHA_SIZE;
	_hoops_IPPGR[index++] = 1;
	if (dc->options._hoops_AHIIP) {
		_hoops_IPPGR[index++] = GLX_STEREO;
	}
	if (dc->options._hoops_SRRRR) {
		_hoops_IPPGR[index++] = GLX_DOUBLEBUFFER;
	}
	_hoops_IPPGR[index] = None;

	visual = glXChooseVisual (display, DefaultScreen (display), _hoops_IPPGR);

	if (visual) return visual;


	/* _hoops_SSRPC _hoops_HGAPC _hoops_AIIRI _hoops_HGSRA _hoops_IGAPC _hoops_AGGPA _hoops_CGAPC*/
	index = 0;
	_hoops_IPPGR[index++] = GLX_RGBA;
	_hoops_IPPGR[index++] = GLX_DEPTH_SIZE;
	_hoops_IPPGR[index++] = 1;	
	_hoops_IPPGR[index++] = GLX_RED_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_BLUE_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_GREEN_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_ALPHA_SIZE;
	_hoops_IPPGR[index++] = 1;
	if (dc->options._hoops_AHIIP) {
		_hoops_IPPGR[index++] = GLX_STEREO;
		_hoops_IPPGR[index++] = GLX_DOUBLEBUFFER;
	}else
	if (dc->options._hoops_SRRRR) {
		_hoops_IPPGR[index++] = GLX_DOUBLEBUFFER;
	}
	_hoops_IPPGR[index] = None;

	visual = glXChooseVisual (display, DefaultScreen (display), _hoops_IPPGR);

	if (visual) return visual;


	/* _hoops_AGAPC _hoops_HGAPC _hoops_HPPR _hoops_GCRAC _hoops_RGAR*/
	index = 0;
	/* _hoops_HHH _hoops_AAPGH (_hoops_RPAC _hoops_ARIPR) _hoops_AHGS _hoops_IS _hoops_HS _hoops_SPGC _hoops_SIGSP
	   _hoops_HII _hoops_GHGPR _hoops_ACHGR _hoops_CCH _hoops_IS _hoops_RSRA _hoops_ACHGR _hoops_CCH */
#if defined (SOLARIS_SYSTEM) || defined (HPUX_SYSTEM) || defined (IRIX_SYSTEM)
	_hoops_IPPGR[index++] = GLX_DOUBLEBUFFER;	
#else
	if (dc->options._hoops_SRRRR)
		_hoops_IPPGR[index++] = GLX_DOUBLEBUFFER;
#endif
	_hoops_IPPGR[index++] = GLX_RGBA;
	_hoops_IPPGR[index++] = GLX_DEPTH_SIZE;
	_hoops_IPPGR[index++] = 1;	
	_hoops_IPPGR[index++] = GLX_RED_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_BLUE_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_GREEN_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index] = None;

	visual = glXChooseVisual (display, DefaultScreen (display), _hoops_IPPGR);

	if (visual) return visual;

	/*_hoops_HPPR _hoops_ARR _hoops_RRI _hoops_IH _hoops_AAPGH _hoops_CCA _hoops_GGSR _hoops_GII _hoops_RSRA _hoops_SRHR _hoops_SGAPC*/
	index = 0;
	_hoops_IPPGR[index++] = GLX_RGBA;
	_hoops_IPPGR[index++] = GLX_DEPTH_SIZE;
	_hoops_IPPGR[index++] = 1;	
	_hoops_IPPGR[index++] = GLX_RED_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_BLUE_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_GREEN_SIZE;
	_hoops_IPPGR[index++] = 1;
	_hoops_IPPGR[index++] = GLX_DOUBLEBUFFER;
	_hoops_IPPGR[index] = None;

	visual = glXChooseVisual (display, DefaultScreen (display), _hoops_IPPGR);

	return visual;
}


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

#ifdef DEBUG_PRINTS
fprintf(stderr, "get_current_info %p\n", (void*)_hoops_CSRGR);
#endif

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR) {
		dc->options._hoops_RASSP = true;
		dc->options._hoops_AASSP = true;
		dc->options._hoops_PASSP = true;
		dc->options._hoops_HPHRP = false;
		dc->options.border = false;
		dc->options._hoops_HRSSP = false;
	}

	if (_hoops_CSRGR->_hoops_RPAAC->get_current_info)
		(*_hoops_CSRGR->_hoops_RPAAC->get_current_info) (dc);


#if 0
	GLint _hoops_RCHA[3];
	if (glXGetCurrentContext ()) {
		glGetIntegerv (GL_RED_BITS, _hoops_RCHA);
		glGetIntegerv (GL_BLUE_BITS, _hoops_RCHA + 1);
		glGetIntegerv (GL_GREEN_BITS, _hoops_RCHA + 2);
		_hoops_CSRGR->_hoops_SAHGC = _hoops_RCHA[0] + _hoops_RCHA[1] + _hoops_RCHA[2];
	}
#endif
	/* _hoops_RCSC _hoops_HAR _hoops_CSPH->_hoops_CPHSR?  _hoops_GRAPC _hoops_RRGSI */
	dc->current._hoops_AAPSR = 1L << 24;	/* _hoops_HIHH _hoops_SHR _hoops_APPP 8 _hoops_SIH _hoops_RIR _hoops_AIHSR */
	dc->current._hoops_APASR = 0;

}


/*_hoops_CPCHR*/
local void _hoops_RSCSR (_hoops_APARR alter &);

/*
 * _hoops_SRAC
 */
local void
get_physical_info (Display_Context alter * dc) 
{
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	X11Data alter *_hoops_RRRPC = X11D (dc);
	char const *_hoops_RRAPC;
	XVisualInfo alter *vi;

#ifdef DEBUG_PRINTS
fprintf(stderr, "get_physical_info %p\n", (void*)_hoops_CSRGR);
#endif

#if !defined _hoops_HRGAC
	if (_hoops_RRRPC) {
		/* _hoops_HSPP _hoops_PSAP _hoops_CCA _hoops_ARAPC _hoops_HGCR _hoops_CPHSR _hoops_SIHC */
		(*_hoops_RRRPC->_hoops_PRAPC) (dc);
		_hoops_CSRGR->window = _hoops_RRRPC->window;
		_hoops_CSRGR->screen = _hoops_RRRPC->screen;
		_hoops_CSRGR->visual = _hoops_RRRPC->visual;
		_hoops_CSRGR->_hoops_CAAAC = _hoops_RRRPC->_hoops_CAAAC;
		if (_hoops_CSRGR->display && _hoops_CSRGR->display != _hoops_RRRPC->display) 
			HE_ERROR (HEC_X11_DRIVER, HES_X11_SYSTEM_ERROR, "Leaking X11 display get_physical_info()");
		_hoops_CSRGR->display = _hoops_RRRPC->display;
	}
#endif
	/* _hoops_PPSI _hoops_GGR _hoops_GHAR _hoops_RGGHR _hoops_ARI..._hoops_SAHR _hoops_GGR _hoops_AGIR _hoops_RH _hoops_RPGP _hoops_RPPS _hoops_ISHS */
	dc->_hoops_PGCC._hoops_PCHSR = 256;		
	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	dc->_hoops_PGCC.driver_type = "OpenGL";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 2.208 $";
	dc->_hoops_PGCC._hoops_ICHSR = "frame buffer";

	/* _hoops_IHH _hoops_AAARR _hoops_ARP _hoops_IS _hoops_RCPP _hoops_CCGR _hoops_SR _hoops_CACH _hoops_IRS _hoops_APIP _hoops_GGSC */
	dc->_hoops_PGCC.flags &= ~_hoops_SGICP;
	dc->_hoops_PGCC.flags &= ~_hoops_GPPGH;
#if defined(IRIX_SYSTEM) 
	/* _hoops_HRAPC _hoops_SIISR _hoops_HRGR _hoops_GIR _hoops_HPP _hoops_RH _hoops_GHARR; _hoops_CACH: _hoops_AASAI _hoops_GAASP - _hoops_IRAPC@_hoops_RPHPI._hoops_HIHRH */
	dc->_hoops_PGCC.flags &= ~_hoops_GGISR;
#else 
	dc->_hoops_PGCC.flags |= _hoops_GGISR;
#endif 

	_hoops_CSRGR->_hoops_PPHGC = false;

	dc->_hoops_PGCC.flags |= _hoops_SGICP;
	dc->_hoops_PGCC.flags |= _hoops_GPPGH;

	dc->_hoops_PGCC.flags |= _hoops_ASSHP;
	dc->_hoops_PGCC.flags |= _hoops_PSSHP;

	_hoops_RSCSR (dc->_hoops_ACPGR);

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR || _hoops_CSRGR->_hoops_PIGRR == _hoops_SSRAC) {
		dc->_hoops_PGCC._hoops_PRPSR.x = _hoops_CSRGR->_hoops_IHGRR->width;
		dc->_hoops_PGCC._hoops_PRPSR.y = _hoops_CSRGR->_hoops_IHGRR->height;
		dc->_hoops_PGCC.size.x = dc->_hoops_PGCC._hoops_PRPSR.x * 2.54 /72.0;
		dc->_hoops_PGCC.size.y = dc->_hoops_PGCC._hoops_PRPSR.y * 2.54 /72.0;
		/* _hoops_ICCI _hoops_AASC.  _hoops_GHCA _hoops_ASRHA _hoops_CGPR _hoops_PAAP _hoops_CPHSR _hoops_SIHC _hoops_HRGR _hoops_PIGS */
		dc->_hoops_PGCC._hoops_HGCC = 8; 

#if 0
		((Display_Context alter *)dc)->options._hoops_IASSP = true;
		((Display_Context alter *)dc)->options._hoops_CRSSP = true;
#endif

	}
	else {
		dc->_hoops_PGCC._hoops_RCPGH = "Mouse";
	}


#if !defined _hoops_HRGAC
	if (_hoops_CSRGR->_hoops_PIGRR != _hoops_HPSGR) {

		vi = _hoops_ISRPC(dc, _hoops_CSRGR->display);

		if (!vi) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
					"Can't find visual for OpenGL.");
			return;
		}

		if (_hoops_CSRGR->_hoops_CAAAC) 
			XFree(_hoops_CSRGR->_hoops_CAAAC);

		_hoops_CSRGR->_hoops_CAAAC = vi;
		_hoops_CSRGR->visual = _hoops_RRRPC->visual = vi->visual;
		_hoops_RRRPC->depth = vi->depth;
		_hoops_RRRPC->_hoops_CRAPC = vi->bits_per_rgb;

		(*_hoops_RRRPC->_hoops_SRAPC) (dc);
		_hoops_CSRGR->window = _hoops_RRRPC->window;
	}

	if (BIT(_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_IAGAC))
		_hoops_CSRGR->context = glXCreateContext (_hoops_CSRGR->display, _hoops_CSRGR->_hoops_CAAAC, null, GL_FALSE);
	else
		_hoops_CSRGR->context = glXCreateContext (_hoops_CSRGR->display, _hoops_CSRGR->_hoops_CAAAC, null, GL_TRUE);

	switch ((int)(POINTER_SIZED_INT) _hoops_CSRGR->context) {
		case 0:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Client could not create OpenGL test context.");
			HD_Kill_Driver (dc);
			return;
		case BadMatch:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "OpenGL context cannot access test visual.");
			HD_Kill_Driver (dc);
			return;
		case BadValue:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Invalid visual (bad screen number) for OpenGL test context.");
			HD_Kill_Driver (dc);
			return;
		default:
			break;
	}

	if (glXMakeCurrent (_hoops_CSRGR->display, _hoops_CSRGR->window, _hoops_CSRGR->context) == GL_FALSE) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "glXMakeCurrent failed for get_physical_info test window.");
			HD_Kill_Driver (dc);
			return;
	}
#else
	_hoops_PHPAC _hoops_HSHAC;
	void *buffer;
	char *filename = NULL; 

	/* _hoops_GISA _hoops_PCCP _hoops_RGPP-_hoops_CCH _hoops_GGSC */
	/* _hoops_AAIR _hoops_AHCR, _hoops_APSP, _hoops_SPPPC _hoops_PGRR */
	_hoops_CSRGR->_hoops_HHPAC = _hoops_SASPC( _hoops_GPSPC, 24, 8, 0, NULL ); 
	if (!_hoops_CSRGR->_hoops_HHPAC) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_GLXMAKECURRENT_FAILED,
										  "failed to create OSMesa context.");
	}
	if (!_hoops_AASPC( _hoops_CSRGR->_hoops_HHPAC, _hoops_CSRGR->_hoops_IHPAC, GL_UNSIGNED_BYTE,_hoops_CSRGR->_hoops_IHGRR->width ,_hoops_CSRGR->_hoops_IHGRR->height)) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "OSMesaMakeCurrent failed for init_picture.");
		//_hoops_PASPC (_hoops_SCII->_hoops_GHCSR);
		return;
	}
#endif

	identify_renderer ((Display_Context alter *)dc);
	_hoops_RRAPC = (const char*)glGetString (GL_RENDERER);
	if (!_hoops_RRAPC) 
		_hoops_RRAPC="";
	strncpy (_hoops_RRRPC->_hoops_IPHIH, _hoops_RRAPC, _hoops_GAAPC);
	/* _hoops_RAAPC _hoops_ASSP'_hoops_RA _hoops_GHHR _hoops_GPP _hoops_GAHR*/
	_hoops_RRRPC->_hoops_IPHIH[_hoops_GAAPC - 1] = '\0';

	_hoops_IAHGC (dc);

#if !defined _hoops_HRGAC
	XFlush (_hoops_CSRGR->display);
#endif

	glFlush ();

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
#ifdef DEBUG_PRINTS
fprintf(stderr,"ogldata->dc_type == DCT_PBUFFER_IMAGE\n");
#endif
		if (_hoops_SIAGC(_hoops_CSRGR, true)) {
			_hoops_CSRGR->_hoops_PIGRR = _hoops_CPSGR;
#ifdef DEBUG_PRINTS
fprintf(stderr,"ogldata->dc_type == DCT_FBO_IMAGE\n");
#endif
		}
	}


#if !defined _hoops_HRGAC
	if (_hoops_CSRGR->_hoops_PIGRR != _hoops_CPSGR && _hoops_CSRGR->_hoops_PIGRR != _hoops_SSRAC) {
		/* _hoops_SGPHP _hoops_GGSC _hoops_ARPP _hoops_RHAC _hoops_CIH _hoops_SCH! */
		glXMakeCurrent (_hoops_CSRGR->display, 0, 0);
		if (_hoops_CSRGR->context) {
			glXDestroyContext (_hoops_CSRGR->display, _hoops_CSRGR->context);
			_hoops_CSRGR->context = (GLXContext) 0;
		}

		if (_hoops_CSRGR->_hoops_PIGRR != _hoops_HPSGR) {

			(*_hoops_RRRPC->_hoops_AAAPC) (dc);
		}
	}
	else {

		/* _hoops_GRHP _hoops_SCH _hoops_PPR _hoops_IPPR _hoops_SCH */
		(*_hoops_RRRPC->_hoops_PAAPC) (dc);
	}
#endif

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		_hoops_CSRGR->_hoops_PAHGC = has_pbuffers(_hoops_CSRGR->display, DefaultScreen (_hoops_CSRGR->display));
#if defined(IRIX_SYSTEM) 
		_hoops_CSRGR->_hoops_PAHGC = false;
#endif
		if (!_hoops_CSRGR->_hoops_PAHGC) {
			HE_ERROR (HEC_X11_DRIVER, HES_VISUAL_FOR_OPENGL_MISSING, "OpenGL cannot find pbuffer support");
			HD_Kill_Driver (dc);
			return;
		}
	}
}

#if !defined _hoops_RPSPC
/*_hoops_RGR _hoops_API _hoops_HRGR _hoops_PIGS _hoops_HPP _hoops_RH _hoops_HAAPC */
local void
_hoops_IAAPC (Display_Context const * dc) 
{
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	X11Data alter *_hoops_RRRPC = X11D (dc);
	Display alter *display = _hoops_CSRGR->display;
	XVisualInfo *vi = 0;

	vi = _hoops_ISRPC(dc, display);

	if (!vi) {
		HE_ERROR (HEC_X11_DRIVER, HES_VISUAL_FOR_OPENGL_MISSING, "OpenGL cannot find visual");
		HD_Kill_Driver (dc);
		return;
	}

	if(_hoops_CSRGR->_hoops_CAAAC)
		XFree(_hoops_CSRGR->_hoops_CAAAC);

	_hoops_CSRGR->_hoops_CAAAC = vi;
	_hoops_CSRGR->visual = vi->visual;
	_hoops_RRRPC->depth = vi->depth;
	_hoops_RRRPC->_hoops_CRAPC = vi->bits_per_rgb;
	return;
}



/*
 * _hoops_PGAA
 */
local bool
_hoops_CAAPC (Display_Context alter * dc) {
	OGLData alter *_hoops_CSRGR = OGLD(dc);
	X11Data alter *_hoops_RRRPC = null; /* _hoops_HAR _hoops_GAPR _hoops_PSPP */
	int _hoops_SAAPC;
	int _hoops_GPAPC;

#ifdef DEBUG_PRINTS
fprintf(stderr, "connect_x11_driver\n");
#endif

	/* _hoops_HIHH _hoops_PAH'_hoops_RA _hoops_ARAS _hoops_SIHH _hoops_GPAAC _hoops_IH _hoops_HA... */
	if (!(*_hoops_AGRPC) (dc)) {
		return false;
	}
	/* _hoops_RPAPC _hoops_SSCP _hoops_SRAHR _hoops_APAPC _hoops_HA */
	_hoops_RRRPC = X11D (dc);
	_hoops_RRRPC->driver_type = _hoops_PPAPC;
	_hoops_RRRPC->_hoops_HPAPC = null;
	_hoops_CSRGR->window = _hoops_RRRPC->window;
	_hoops_CSRGR->screen = _hoops_RRRPC->screen;
	_hoops_CSRGR->visual = _hoops_RRRPC->visual;

	if (_hoops_CSRGR->display && _hoops_CSRGR->display != _hoops_RRRPC->display) 
		HE_ERROR (HEC_X11_DRIVER, HES_X11_SYSTEM_ERROR, "Leaking X11 display connect_to_display()");
	_hoops_CSRGR->display = _hoops_RRRPC->display;

	/* _hoops_IGI _hoops_IS _hoops_IHIS _hoops_IPAPC _hoops_HCPH _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_CPAPC * _hoops_RHPP */
	_hoops_RRRPC->_hoops_IAAPC = _hoops_IAAPC;
	
	/*
	 * _hoops_GRS _hoops_RRP _hoops_IS _hoops_AASA _hoops_GPAAC _hoops_SICAR _hoops_IS _hoops_GRHP _hoops_GPAAC _hoops_SGGHA
	 * _hoops_HPGP _hoops_HIHH _hoops_HRGR _hoops_SGGHA
	 * _hoops_AGAH _hoops_HCPH _hoops_HIHH, _hoops_HIHH _hoops_HCPH _hoops_GPAAC
	 */
	_hoops_CSRGR->_hoops_RPAAC->stop_device = dc->_hoops_ACPGR->stop_device;
	_hoops_CSRGR->_hoops_RPAAC->get_current_info = dc->_hoops_ACPGR->get_current_info;
	_hoops_CSRGR->_hoops_RPAAC->init_picture = dc->_hoops_ACPGR->init_picture;
	_hoops_CSRGR->_hoops_RPAAC->finish_picture = dc->_hoops_ACPGR->finish_picture;
	_hoops_CSRGR->_hoops_RPAAC->get_outer_window = dc->_hoops_ACPGR->get_outer_window;
	_hoops_CSRGR->_hoops_RPAAC->free_outer_window = dc->_hoops_ACPGR->free_outer_window;
	_hoops_CSRGR->_hoops_RPAAC->_hoops_RSCSP = dc->_hoops_ACPGR->_hoops_RSCSP;
	_hoops_CSRGR->_hoops_RPAAC->init_update = dc->_hoops_ACPGR->init_update;
	_hoops_CSRGR->_hoops_RPAAC->finish_update = dc->_hoops_ACPGR->finish_update;
	_hoops_CSRGR->_hoops_RPAAC->_hoops_HSCSP = dc->_hoops_ACPGR->_hoops_HSCSP;
	_hoops_CSRGR->_hoops_RPAAC->_hoops_ISCSP = dc->_hoops_ACPGR->_hoops_ISCSP;
	_hoops_CSRGR->_hoops_RPAAC->get_physical_info = dc->_hoops_ACPGR->get_physical_info;
	_hoops_CSRGR->_hoops_RPAAC->find_all_fonts = dc->_hoops_ACPGR->find_all_fonts;
	_hoops_CSRGR->_hoops_RPAAC->_hoops_CACSR = dc->_hoops_ACPGR->_hoops_CACSR;
	_hoops_CSRGR->_hoops_RPAAC->load_font = dc->_hoops_ACPGR->load_font;
	_hoops_CSRGR->_hoops_RPAAC->unload_font = dc->_hoops_ACPGR->unload_font;
	_hoops_CSRGR->_hoops_RPAAC->measure_char = dc->_hoops_ACPGR->measure_char;
	_hoops_CSRGR->_hoops_RPAAC->_hoops_RGSSP = dc->_hoops_ACPGR->_hoops_RGSSP;
	_hoops_CSRGR->_hoops_RPAAC->_hoops_SRCSR = dc->_hoops_ACPGR->_hoops_SRCSR;

	/* _hoops_HHSA _hoops_IRS _hoops_AASA _hoops_IS _hoops_HIHH _hoops_HGCR _hoops_CPHSR _hoops_SIHC */
	dc->_hoops_ACPGR->get_physical_info = get_physical_info;

	if (
		glXQueryExtension
			(_hoops_CSRGR->display, &_hoops_SAAPC, &_hoops_GPAPC) == GL_FALSE) {
		HE_ERROR (HEC_OPENGL_DRIVER, HES_GLX_EXTENSIONS_NOT_PRESENT,
				  "Server does not have GLX extension.");
		return false;
	}
	_hoops_RSCSR(dc->_hoops_ACPGR);

	return true;
}
#endif

/*
 * _hoops_SRAC
 */
local bool
start_device (Display_Context alter * dc) 
{
	OGLData alter *_hoops_CSRGR;
	int _hoops_APSPC = 0;

#ifdef _hoops_ICGGC
	_hoops_APSPC = 1;
#endif

	/* _hoops_HGCR _hoops_IRS _hoops_HRPR _hoops_IS _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_PIAP _hoops_HPHS */
	ZALLOC (_hoops_CSRGR, OGLData);

	dc->_hoops_RIHGR = (void alter *) _hoops_CSRGR;
	_hoops_CSRGR->dc = dc;
	_hoops_CSRGR->_hoops_RPAAC = _hoops_APARR::Create(dc->memory_pool);

	if (!dc->options._hoops_GCHSR)
		_hoops_CSRGR->_hoops_PIGRR = _hoops_PPSGR;
	else if (_hoops_APSPC || dc->options._hoops_RGHRP == _hoops_GGHRP || BIT (dc->options._hoops_IRARR, _hoops_GCSRH)) {
		Image alter				*image;

		image = (Image alter *)_hoops_RCSSR (dc->_hoops_RIGC, dc->options._hoops_GCHSR);
		if (image == null) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
					"An invalid key was passed to the OpenGL driver with USE_WINDOW_IS_IMAGE set."); 
			return false;
		}
		if (image->_hoops_PHGH == 0 ||
			!(image->format == Image_RGBA32 || 
			 image->format == _hoops_HRSRH || 
			 image->format == _hoops_CSGSP || 
			 image->format == _hoops_HHGH)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
					"OpenGL output image unsupported format."); 
			return false;
		}
		if (image->height < 1 || image->width < 1) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_KEY,
					"OpenGL output images must be at least 1x1."); 
			return false;
		}

		_hoops_CSRGR->_hoops_IHGRR = image;
		_hoops_CSRGR->window_width = _hoops_CSRGR->_hoops_IHGRR->width;
		_hoops_CSRGR->window_height = _hoops_CSRGR->_hoops_IHGRR->height;
		_hoops_PRRH (_hoops_CSRGR->_hoops_IHGRR);	
#ifdef _hoops_HRGAC
		_hoops_CSRGR->_hoops_PIGRR = _hoops_SSRAC; /* _hoops_GPP _hoops_IPAPC, _hoops_CGSRC _hoops_HPCS _hoops_HRGR _hoops_GGHGI */
		int _hoops_IRSPC = _hoops_CSRGR->_hoops_IHGRR->width;
		int _hoops_CRSPC = _hoops_CSRGR->_hoops_IHGRR->height;
		ALLOC_ARRAY(_hoops_CSRGR->_hoops_IHPAC, _hoops_IRSPC*_hoops_CRSPC , _hoops_AIGH);
#else
		_hoops_CSRGR->_hoops_PIGRR = _hoops_IPSGR; /* _hoops_GPP _hoops_IPAPC, _hoops_CGSRC _hoops_HPCS _hoops_HRGR _hoops_GGHGI */
#endif
		
	}
	else
		_hoops_CSRGR->_hoops_PIGRR = _hoops_HPSGR;

	/* _hoops_AA _hoops_GPAAC _hoops_CIPH */
	if (!_hoops_CAAPC (dc))
		return false;

	return true;
}


/*
 * _hoops_SRAC
 */
local void
stop_device (Display_Context alter * dc) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);
	X11Data alter *_hoops_RRRPC = X11D (dc);

#ifdef DEBUG_PRINTS
fprintf(stderr, "stop_device %p\n", (void*)_hoops_CSRGR);
#endif

#if !defined _hoops_HRGAC
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_CPSGR) {

		glXMakeCurrent (_hoops_CSRGR->display, _hoops_CSRGR->window, _hoops_CSRGR->context);
		_hoops_IHAGC(_hoops_CSRGR);
		(*_hoops_RRRPC->_hoops_AAAPC) (dc);
	}
#endif

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_SSRAC){
#ifdef _hoops_HRGAC
		_hoops_PPSPC( _hoops_CSRGR->_hoops_HHPAC);
#endif
	}

#if !defined _hoops_HRGAC
	glXMakeCurrent (_hoops_CSRGR->display, None, null);
	if (_hoops_CSRGR->context) {
		glXDestroyContext (_hoops_CSRGR->display, _hoops_CSRGR->context);
		_hoops_CSRGR->context = (GLXContext) 0;
	}

	if (_hoops_CSRGR->_hoops_RPAAC->stop_device)
		(*_hoops_CSRGR->_hoops_RPAAC->stop_device) (dc);  /* _hoops_PAISR _hoops_GPAAC _hoops_CIPH */
#endif

	if (_hoops_CSRGR->_hoops_IHGRR) {
		if (_hoops_CSRGR->output_image_scratch) {
		    int w = _hoops_CSRGR->_hoops_IHGRR->width;
		    int h = _hoops_CSRGR->_hoops_IHGRR->height;
		    FREE_ARRAY(_hoops_CSRGR->output_image_scratch, w*h, _hoops_AIGH);
		}
		_hoops_HPRH (_hoops_CSRGR->_hoops_IHGRR); 

	}

	if (_hoops_CSRGR->_hoops_PRARR)
		HI_Free_Driver_Config(_hoops_CSRGR->_hoops_PRARR);

#if 0
/*_hoops_ASIGA*/
	if (_hoops_CSRGR->_hoops_AHAPC)
		HI_Delete_VList(_hoops_CSRGR->_hoops_AHAPC);
#endif

#if 0
	if (_hoops_CSRGR->display && _hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR)
		HD_Free_X11_Display(_hoops_CSRGR->display);
#endif

	_hoops_CSRGR->_hoops_RPAAC = null;

	/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_HRPR _hoops_IS _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_PIAP _hoops_HPHS */
	FREE (_hoops_CSRGR, OGLData);
	dc->_hoops_RIHGR = null;
}


/*
 * _hoops_SRAC
 */
local bool
_hoops_ISCSP (Display_Context const * dc,
				  int alter * button, int alter * status) {
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	if (_hoops_CSRGR->_hoops_RPAAC->_hoops_ISCSP)
		return (*_hoops_CSRGR->_hoops_RPAAC->_hoops_ISCSP) (dc, button, status);
	else
		return false;
}


/*
 * _hoops_SRAC
 */
local bool
_hoops_HSCSP (Display_Context const * dc,
				  int alter * button,
				  int alter * x, int alter * y) {
	OGLData const *_hoops_CSRGR = OGLD (dc);

	if (_hoops_CSRGR->_hoops_RPAAC->_hoops_HSCSP)
		return (*_hoops_CSRGR->_hoops_RPAAC->_hoops_HSCSP) (dc, button, x, y);
	else
		return false;
}



/*
 * _hoops_PGAA
 */
local Bool
WaitForMapNotify (Display * d, XEvent * e, char *arg) {

	if (e->type == MapNotify && e->xmap.window == (X_Window) arg)
		return GL_TRUE;
	else
		return GL_FALSE;
}

/*
 * _hoops_PGAA
 */
local XVisualInfo alter *
_hoops_HPSPC (Display alter * display,
							Visual alter * visual) {
	XVisualInfo _hoops_IPSPC;
	XVisualInfo alter *_hoops_CPSPC;
	int n;

	_hoops_IPSPC.visualid = XVisualIDFromVisual (visual);
	_hoops_CPSPC = XGetVisualInfo (display, VisualIDMask, &_hoops_IPSPC, &n);
	if (n == 0) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Could not find XVisualInfo for window.");
		return null;
	}
	else
		return _hoops_CPSPC;
}


#if !defined _hoops_HRGAC
/*
 * _hoops_PGAA
 */
local void
_hoops_SPSPC (Display_Context alter * dc) {
	X11Data alter *_hoops_RRRPC = X11D (dc);
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	Display alter *display = _hoops_CSRGR->display;
	XVisualInfo alter *vi = null;

	_hoops_CSRGR->_hoops_CSHGC = false;
	SET_MEMORY(&_hoops_CSRGR->overlay, sizeof(_hoops_CSRGR->overlay), 0);

	if (dc->options._hoops_ISPRP != 0) {

		XWindowAttributes _hoops_GHSPC;

		if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR) {
			HE_ERROR2 (HEC_OPENGL_DRIVER, HES_MAIN_WINDOW_ID_MISSING,
					   "You cannot specify an overlay window ID",
					   "without also giving a main window ID");
			HD_Kill_Driver (dc);
			goto _hoops_RCCSR;
		}

		_hoops_CSRGR->overlay.window = dc->options._hoops_ISPRP;
		_hoops_RRRPC->_hoops_RHSPC = _hoops_CSRGR->overlay.window;

		XGetWindowAttributes (display, _hoops_CSRGR->overlay.window, &_hoops_GHSPC);

		vi = _hoops_HPSPC (display, _hoops_GHSPC.visual);

		if (!vi) {
			HE_WARNING (HEC_OPENGL_DRIVER, HES_COMPUTE_VISUALINFO_FAILED,
						"Could not compute visualinfo for overlay planes from use window ID 2.");
			goto _hoops_RCCSR;
		}

		if (BIT(_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_IAGAC))
			_hoops_CSRGR->overlay.context = glXCreateContext (display, vi, _hoops_CSRGR->context, GL_FALSE);

		if (!_hoops_CSRGR->overlay.context) 
			_hoops_CSRGR->overlay.context = glXCreateContext (display, vi, _hoops_CSRGR->context, GL_TRUE);

		if (!_hoops_CSRGR->overlay.context) 
			_hoops_CSRGR->overlay.context = glXCreateContext (display, vi, _hoops_CSRGR->context, GL_FALSE);

		if (!_hoops_CSRGR->overlay.context) {
			HE_WARNING (HEC_OPENGL_DRIVER, HES_COMPUTE_CONTEXT_FAILED,
					"Could not compute context for overlay planes from use window ID 2.");
			goto _hoops_RCCSR;
		}

		/*_hoops_PSHA*/
		_hoops_CSRGR->overlay.colormap = _hoops_GHSPC.colormap;
		_hoops_CSRGR->overlay._hoops_AHISI = vi->colormap_size;
		ALLOC_ARRAY (_hoops_CSRGR->overlay.colors, _hoops_CSRGR->overlay._hoops_AHISI, Driver_Color);

	}else{

		long screen = DefaultScreen (display);

#define _hoops_AHSPC 12
		int _hoops_PHSPC[_hoops_AHSPC][8] = {
			{GLX_LEVEL, 1, GLX_RGBA, GLX_DEPTH_SIZE, 0, None, None, None},
			{GLX_LEVEL, 1, GLX_RGBA, GLX_DEPTH_SIZE, 0, GLX_DOUBLEBUFFER, None , None},
			{GLX_LEVEL, 1, GLX_BUFFER_SIZE, 16, GLX_DEPTH_SIZE, 0, None, None},
			{GLX_LEVEL, 1, GLX_BUFFER_SIZE, 16, GLX_DEPTH_SIZE, 0, GLX_DOUBLEBUFFER, None},
			{GLX_LEVEL, 1, GLX_BUFFER_SIZE, 8, GLX_DEPTH_SIZE, 0, None, None},
			{GLX_LEVEL, 1, GLX_BUFFER_SIZE, 8, GLX_DEPTH_SIZE, 0, GLX_DOUBLEBUFFER, None},
			{GLX_LEVEL, 1, GLX_BUFFER_SIZE, 4, GLX_DEPTH_SIZE, 0, None, None},
			{GLX_LEVEL, 1, GLX_BUFFER_SIZE, 4, GLX_DEPTH_SIZE, 0, GLX_DOUBLEBUFFER, None},
			{GLX_LEVEL, 1, GLX_BUFFER_SIZE, 2, GLX_DEPTH_SIZE, 0, None, None},
			{GLX_LEVEL, 1, GLX_BUFFER_SIZE, 2, GLX_DEPTH_SIZE, 0, GLX_DOUBLEBUFFER, None},
			{GLX_LEVEL, 1, GLX_BUFFER_SIZE, 1, GLX_DEPTH_SIZE, 0, None, None},
			{GLX_LEVEL, 1, GLX_BUFFER_SIZE, 1, GLX_DEPTH_SIZE, 0, GLX_DOUBLEBUFFER, None}
		};

		int n;

		_hoops_CSRGR->overlay._hoops_SIHGC = 0;

		/*_hoops_SRS _hoops_HPPR _hoops_IPAPC _hoops_IS _hoops_HGCR _hoops_RH _hoops_APHSR */ 
		for (n=0; n<_hoops_AHSPC; n++) {
			vi = glXChooseVisual (display, screen, _hoops_PHSPC[n]);
			if (vi) break;
		}

		/* _hoops_HPPR _hoops_IS _hoops_SGH _hoops_HHSPC _hoops_ACASI _hoops_IHSPC _hoops_SSICI _hoops_RPP _hoops_IPAPC _hoops_SRSH */ 
		if (!vi) {

			unsigned long _hoops_CHSPC;
			unsigned long _hoops_SHSPC;
			Atom _hoops_GISPC;
			int _hoops_RISPC;
			XOverlayVisual *_hoops_AISPC = NULL;
			int _hoops_PISPC;
			XVisualInfo alter *_hoops_HISPC;
			XVisualInfo alter _hoops_IISPC;
			Atom _hoops_SGSAP;
			int i;
			unsigned int j;


			ZERO_STRUCT(&_hoops_IISPC, XVisualInfo);
			_hoops_IISPC.screen = (int) screen;

			if (!(_hoops_HISPC = XGetVisualInfo(display, 
					VisualScreenMask, &_hoops_IISPC, &_hoops_RISPC))) {
				HE_WARNING (HEC_OPENGL_DRIVER, HES_ALLOC_OVERLAY_PLANE, 
					"Could not get visual information.");
				goto _hoops_RCCSR;
			}else
			if ((_hoops_GISPC = XInternAtom (display, "SERVER_OVERLAY_VISUALS", True)) == None) {
				/* _hoops_AIRS _hoops_IS _hoops_SSS _hoops_ACRAC _hoops_SGCCP _hoops_GPP _hoops_RH _hoops_SRRPR _hoops_RPPS. */
				HE_WARNING (HEC_OPENGL_DRIVER, HES_ALLOC_OVERLAY_PLANE,
					"No SERVER_OVERLAY_VISUALS atoms.");
				goto _hoops_RCCSR;
			}else 
			if (XGetWindowProperty (display, RootWindow (display, screen), 
				_hoops_GISPC, 0, 2 * 64, False, _hoops_GISPC, 
				&_hoops_SGSAP, &_hoops_PISPC, &_hoops_SHSPC, 
				&_hoops_CHSPC, (unsigned char **) (&_hoops_AISPC)) != Success) {

				/* _hoops_AIRS _hoops_IS _hoops_SSS _hoops_RH _hoops_APHSR _hoops_HRPRA _hoops_GPP _hoops_RH _hoops_SRRPR _hoops_RPPS. */
				HE_WARNING (HEC_OPENGL_DRIVER, HES_ALLOC_OVERLAY_PLANE,
					"Could not get SERVER_OVERLAY_VISUALS property info.");
				goto _hoops_RCCSR;
			}

			for (i = 0; i < _hoops_RISPC; i++) {
				for (j = 0; j < (_hoops_SHSPC / 4); j++) {
					if (_hoops_AISPC[j]._hoops_HCRAC == _hoops_HISPC[i].visualid &&
						_hoops_HISPC[i].c_class == PseudoColor &&
						_hoops_AISPC[j]._hoops_ICRAC == _hoops_SCRAC &&
						_hoops_HISPC[i].colormap_size > vi->colormap_size) {

						_hoops_CSRGR->overlay._hoops_SIHGC = _hoops_AISPC[j].value;
						vi = &_hoops_HISPC[i];
						break;
					}
				}
			}
		}

		if (!vi) {
			HE_WARNING (HEC_OPENGL_DRIVER, HES_ALLOC_OVERLAY_PLANE,
				"Could not allocate overlay.");
			goto _hoops_RCCSR;
		}

		if (BIT(_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_IAGAC))
			_hoops_CSRGR->overlay.context = glXCreateContext (display, vi, _hoops_CSRGR->context, GL_FALSE);

		if (!_hoops_CSRGR->overlay.context) 
			_hoops_CSRGR->overlay.context = glXCreateContext (display, vi, _hoops_CSRGR->context, GL_TRUE);

		if (!_hoops_CSRGR->overlay.context) 
			_hoops_CSRGR->overlay.context = glXCreateContext (display, vi, _hoops_CSRGR->context, GL_FALSE);

		if (!_hoops_CSRGR->overlay.context) {
			HE_WARNING (HEC_OPENGL_DRIVER, HES_COMPUTE_CONTEXT_FAILED,
					"Could not create glx context for overlay.");
			goto _hoops_RCCSR;
		}

		/*_hoops_PSHA*/
		_hoops_CSRGR->overlay.colormap = XCreateColormap (display, _hoops_RRRPC->_hoops_CISPC, vi->visual, AllocNone);
		_hoops_CSRGR->overlay._hoops_AHISI = vi->colormap_size;
		ALLOC_ARRAY (_hoops_CSRGR->overlay.colors, _hoops_CSRGR->overlay._hoops_AHISI, Driver_Color);

		if (vi->c_class != StaticColor && 
			vi->c_class != StaticGray && 
			vi->c_class != TrueColor) {
			unsigned long _hoops_SISPC[1];
			unsigned long error;
			unsigned long alter *pixels;
			unsigned long _hoops_GCSPC = 1;

			/* _hoops_HAGIP _hoops_IH _hoops_RCSPC-1 _hoops_PSHA..._hoops_SSSCP _hoops_AHGS _hoops_IS _hoops_HAGIP _hoops_IH _hoops_HAIR 0...
			 * _hoops_SCH _hoops_PIHA _hoops_SHH _hoops_CRPHH _hoops_IS _hoops_SHH _hoops_RH _hoops_RRH _hoops_HAIR _hoops_IH _hoops_HCR _hoops_APHSR _hoops_SGAPC...
			 * _hoops_GPP _hoops_HIRPR _hoops_RHAC _hoops_PAH _hoops_HAGIP _hoops_IH _hoops_RCSPC */
#ifdef AIX_SYSTEM
			_hoops_GCSPC = 0;
#endif
			ALLOC_ARRAY (pixels, _hoops_CSRGR->overlay._hoops_AHISI, unsigned long);
			
			error = XAllocColorCells (display, 
					_hoops_CSRGR->overlay.colormap, True, _hoops_SISPC, 
					0, pixels, _hoops_CSRGR->overlay._hoops_AHISI - _hoops_GCSPC);

			if (error == 0) {
				HE_WARNING (HEC_OPENGL_DRIVER, HES_ALLOC_COLOR_OVERLAY_PLANE,
							"Cannot alloc colors for overlay planes.\n");
			}
			FREE_ARRAY (pixels, _hoops_CSRGR->overlay._hoops_AHISI, unsigned long);
		}
		else {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							   "Overlay planes are not color indexed!");
		}

		{
		XSetWindowAttributes _hoops_ACSPC;
		unsigned long mask;

		_hoops_ACSPC.override_redirect = !dc->options._hoops_HRSSP;
		_hoops_ACSPC.colormap = _hoops_CSRGR->overlay.colormap;
		_hoops_ACSPC.border_pixel = BlackPixelOfScreen (_hoops_CSRGR->screen);

#if defined (AIX_SYSTEM)
		_hoops_ACSPC.background_pixel = _hoops_CSRGR->overlay._hoops_SIHGC;
		mask = CWColormap | CWBackPixel | CWBorderPixel | CWOverrideRedirect;
#elif defined (HPUX_SYSTEM)
		_hoops_ACSPC.background_pixel = 255;		/* _hoops_RRH _hoops_IGHP */
		mask = CWColormap | CWBackPixel | CWBorderPixel | CWOverrideRedirect;
#else
		_hoops_ACSPC.background_pixel = 0;		/* _hoops_RRH _hoops_IGHP */
		mask = CWColormap | CWBackPixel | CWBorderPixel | CWOverrideRedirect;
#endif

		_hoops_CSRGR->overlay.window = XCreateWindow(
				display, _hoops_CSRGR->window, 0, 0, 
				_hoops_RRRPC->window_width, _hoops_RRRPC->window_height, 
				0, vi->depth, InputOutput, vi->visual, mask, &_hoops_ACSPC);
		}

		_hoops_RRRPC->_hoops_RHSPC = _hoops_CSRGR->overlay.window;

		{
		XSizeHints _hoops_PCSPC;
		_hoops_PCSPC.x = _hoops_RRRPC->window_x;
		_hoops_PCSPC.y = _hoops_RRRPC->window_y;
		_hoops_PCSPC.width = _hoops_RRRPC->window_width;
		_hoops_PCSPC.height = _hoops_RRRPC->window_height;
		_hoops_PCSPC.flags = USPosition | USSize;
		XSetNormalHints (display, _hoops_CSRGR->overlay.window, &_hoops_PCSPC);
		}

		/* _hoops_CHCRH _hoops_RH _hoops_APHSR _hoops_RPPS */
		/*#_hoops_IHS _hoops_ICAPR*/
		if (1) {
			/* _hoops_HCSPC - _hoops_RRAI _hoops_ICSPC _hoops_IS _hoops_ASSS _hoops_ACAPA _hoops_IS _hoops_CCSPC _hoops_PGRRR */
			/* _hoops_HCSPC - _hoops_IPPRH _hoops_IH _hoops_APHSR _hoops_RPPS _hoops_IS _hoops_SHH _hoops_SCGH, _hoops_IAII _hoops_SCSPC _hoops_HHS _hoops_PHIS */
			XEvent _hoops_GSSPC;
			XSelectInput (display, _hoops_CSRGR->overlay.window, StructureNotifyMask);
			XMapWindow (display, _hoops_CSRGR->overlay.window);
			XFlush (display);
			XIfEvent (display, &_hoops_GSSPC, WaitForMapNotify, (XPointer)_hoops_CSRGR->overlay.window);
		}else{
			XMapWindow (display, _hoops_CSRGR->overlay.window);
			XFlush (display);
		}
	}

	/* _hoops_RGR _hoops_IRHH _hoops_SCGR _hoops_GRS _hoops_IHPI _hoops_RH _hoops_APHSR */
	if (glXMakeCurrent (display, _hoops_CSRGR->overlay.window, _hoops_CSRGR->context) == GL_FALSE) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
			"glXMakeCurrent failed for overlay.");
		goto _hoops_RCCSR;
	}

	dc->current._hoops_PAPGH = _hoops_RRRPC->_hoops_RHSPC;

	XFlush (display);

	/* _hoops_ICRP _hoops_IIGR _hoops_AGCR _hoops_CHR _hoops_HSSHH, _hoops_HIH _hoops_IPCGC _hoops_IIPGR _hoops_AHGS _hoops_IS _hoops_RRP _hoops_RRI _hoops_PICP... */
	if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_SINGLE_BUFFERING))
		glDrawBuffer (GL_FRONT_AND_BACK);
	else glDrawBuffer (GL_FRONT);
	glDisable (GL_POLYGON_STIPPLE);
	glDisable (GL_LIGHTING);
	glDisable (GL_DEPTH_TEST);
	glShadeModel (GL_FLAT);

	/* _hoops_HA _hoops_PPSI _hoops_RH _hoops_HGSI _hoops_RPPS _hoops_ISSC _hoops_GGR _hoops_RGSHA */
	if (glXMakeCurrent (display, _hoops_CSRGR->window, _hoops_CSRGR->context) == GL_FALSE) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
		   "glXMakeCurrent failed for main window back from overlay.");
	}

	_hoops_CSRGR->_hoops_CSHGC = true;
	_hoops_CSRGR->_hoops_RIPGR = true;

_hoops_RCCSR:
	XFlush (display);
	if (vi) XFree ((caddr_t) vi);

	if (!_hoops_CSRGR->_hoops_CSHGC) {

		glXMakeCurrent (_hoops_CSRGR->display, None, null);
		if (_hoops_CSRGR->overlay.context) {
			glXDestroyContext (_hoops_CSRGR->display, _hoops_CSRGR->overlay.context);
			_hoops_CSRGR->context = (GLXContext) 0;
		}

		if (_hoops_CSRGR->overlay.colors) 
			FREE_ARRAY (_hoops_CSRGR->overlay.colors, _hoops_CSRGR->overlay._hoops_AHISI, Driver_Color);

		if (dc->options._hoops_ISPRP == 0) {

			if (_hoops_CSRGR->overlay.colormap)
				XFreeColormap (display, _hoops_CSRGR->overlay.colormap);

			if (_hoops_CSRGR->overlay.window)
				XDestroyWindow (display, _hoops_CSRGR->overlay.window);
		}

		SET_MEMORY(&_hoops_CSRGR->overlay, sizeof(_hoops_CSRGR->overlay), 0);
	}

}
#endif


/*
 * _hoops_SRAC
 */
local POINTER_SIZED_INT
get_outer_window (Display_Context const * dc) 
{
	X11Data alter *_hoops_RRRPC = X11D (dc);
	OGLData alter *_hoops_CSRGR = OGLD (dc);

#ifdef DEBUG_PRINTS
fprintf(stderr, "get_outer_window %p\n", (void*)_hoops_CSRGR);
#endif

	_hoops_CHCGC ((Display_Context alter *) dc);

#ifdef _hoops_HRGAC
	if(_hoops_CSRGR->_hoops_PIGRR == _hoops_SSRAC) {
		((Display_Context alter *)dc)->options._hoops_IASSP = true;
		((Display_Context alter *)dc)->options._hoops_CRSSP = true;

	}
#else

	if (_hoops_RRRPC) {

		if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR ||
			_hoops_CSRGR->_hoops_PIGRR == _hoops_CPSGR ||
			_hoops_CSRGR->_hoops_PIGRR == _hoops_SSRAC) {

			((Display_Context alter *)dc)->options._hoops_IASSP = true;
			((Display_Context alter *)dc)->options._hoops_CRSSP = true;

		}

		if (_hoops_CSRGR->_hoops_PIGRR != _hoops_CPSGR &&
		    _hoops_CSRGR->_hoops_PIGRR != _hoops_SSRAC) {

			if (_hoops_CSRGR->_hoops_RPAAC->get_outer_window)
				(*_hoops_CSRGR->_hoops_RPAAC->get_outer_window) (dc);
			_hoops_CSRGR->window = _hoops_RRRPC->window;
			_hoops_CSRGR->screen = _hoops_RRRPC->screen;
			_hoops_CSRGR->visual = _hoops_RRRPC->visual;

			if (_hoops_CSRGR->display && _hoops_CSRGR->display != _hoops_RRRPC->display) 
				HE_ERROR (HEC_X11_DRIVER, HES_X11_SYSTEM_ERROR, "Leaking X11 display get_outer_window()");
			_hoops_CSRGR->display = _hoops_RRRPC->display;
		}
	}
#endif

	if (_hoops_CSRGR->_hoops_PIGRR != _hoops_IPSGR && 
		_hoops_CSRGR->_hoops_PIGRR != _hoops_CPSGR &&
		_hoops_CSRGR->_hoops_PIGRR != _hoops_SSRAC) {
#if !defined _hoops_HRGAC
		if (!_hoops_CSRGR->_hoops_CAAAC) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_COMPUTE_VISUALINFO_FAILED,
					  "Could not compute visualinfo from use window ID's visual.");
			return 0L;
		}
		/* _hoops_RPPS _hoops_SSCP _hoops_RPII _hoops_SPIP _hoops_HPP _hoops_SPCR, _hoops_HA _hoops_HSCR _hoops_SCH _hoops_IS _hoops_PCCP _hoops_HIHH _hoops_GGSC */
		if (BIT(_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_IAGAC))
			_hoops_CSRGR->context = glXCreateContext (_hoops_CSRGR->display, _hoops_CSRGR->_hoops_CAAAC, null, GL_FALSE);
		else
			_hoops_CSRGR->context = glXCreateContext (_hoops_CSRGR->display, _hoops_CSRGR->_hoops_CAAAC, null, GL_TRUE);
		switch ((long) _hoops_CSRGR->context) {
			case 0:
				HE_ERROR (HEC_OPENGL_DRIVER, HES_CREATE_CONTEXT_FAILED,
						  "Client could not create OpenGL context.");
				return 0L;
				_hoops_HHHI;
			case BadMatch:
				HE_ERROR (HEC_OPENGL_DRIVER, HES_GET_OUTER_WINDOW,
						  "OpenGL context cannot access visual in get_outer_window ().");
				return 0L;
				_hoops_HHHI;
			case BadValue:
				HE_ERROR (HEC_OPENGL_DRIVER, HES_INVALID_VISUAL,
						  "Invalid visual (bad screen number) for OpenGL context.");
				return 0L;
				_hoops_HHHI;
			default:
			break;
		}
	
		if (!glXMakeCurrent (_hoops_CSRGR->display, _hoops_CSRGR->window, _hoops_CSRGR->context)) {
			HE_ERROR (HEC_OPENGL_DRIVER, HES_GLXMAKECURRENT_FAILED,
					  "glXMakeCurrent failed for main window.");
		}
	
		identify_renderer ((Display_Context alter *)dc);
	
		if (BIT(_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_RHGAC)) {
			bool _hoops_RSSPC = false;
	
			if (BIT(_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_HPGAC) &&
				BIT(_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_RHGAC)) {
				HE_WARNING (HEC_OPENGL_DRIVER, HES_OVERLAY_MODE_NOT_SUPPORTED,
					"DEBUG_FORCE_XOR_OVERLAY and DEBUG_FORCE_REAL_OVERLAY are mutually exclusive. Using XOR.");
			}
			else if (!XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_OVERLAY) ||
				BIT (_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_RHGAC)) {
				_hoops_RSSPC = true;
			}
			else if (BIT (_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_HPGAC)) {
				_hoops_RSSPC = false;
			}
	
			/* _hoops_ASIGA _hoops_SGHHR _hoops_IS _hoops_HGCR _hoops_PCCP _hoops_APHSR _hoops_RPPS */
			if (0 && _hoops_RSSPC)
				_hoops_SPSPC ((Display_Context alter *) dc);
		}
	
		if (!_hoops_CSRGR->_hoops_CSHGC) {
			XSetWMColormapWindows (_hoops_CSRGR->display, _hoops_CSRGR->window, &_hoops_CSRGR->window, 1);
			_hoops_RRRPC->_hoops_PHAPC = false;
		}
		else {
			X_Window _hoops_ASSPC[2];
			_hoops_ASSPC[0] = _hoops_CSRGR->window;
			_hoops_ASSPC[1] = _hoops_CSRGR->overlay.window;
			XSetWMColormapWindows (_hoops_CSRGR->display, _hoops_CSRGR->window, _hoops_ASSPC, 2);
			_hoops_RRRPC->_hoops_PHAPC = true;
		}
#endif
	}
	else {
		

		if (_hoops_CSRGR->_hoops_PIGRR == _hoops_SSRAC){
#ifdef _hoops_HRGAC
			_hoops_PHPAC _hoops_HSHAC;
			void *buffer;
			char *filename = NULL;

			/* _hoops_GISA _hoops_PCCP _hoops_RGPP-_hoops_CCH _hoops_GGSC */
			/* _hoops_AAIR _hoops_AHCR, _hoops_APSP, _hoops_SPPPC _hoops_PGRR */
			if (!_hoops_CSRGR->_hoops_HHPAC) {
				_hoops_CSRGR->_hoops_HHPAC = _hoops_SASPC( _hoops_GPSPC, 24, 8, 0, NULL );
				if (!_hoops_CSRGR->_hoops_HHPAC) {
					HE_ERROR (HEC_OPENGL_DRIVER, HES_GLXMAKECURRENT_FAILED, "failed to create OSMesa context.");
				}
			}
#endif

		}

#if !defined _hoops_HRGAC
		if (_hoops_CSRGR->_hoops_PIGRR == _hoops_CPSGR) {

#ifdef DEBUG_PRINTS
fprintf(stderr, "DCT_FBO_IMAGE %p display: %p window: %p context: %p\n",
	(void*)_hoops_CSRGR,(void*)_hoops_CSRGR->display,(void*)_hoops_CSRGR->window,(void*)_hoops_CSRGR->context);
#endif
	
			if (!glXMakeCurrent (_hoops_CSRGR->display, _hoops_CSRGR->window, _hoops_CSRGR->context)) {
				HE_ERROR (HEC_OPENGL_DRIVER, HES_GLXMAKECURRENT_FAILED,
						  "glXMakeCurrent failed for main window.");
			}
		
			identify_renderer ((Display_Context alter *)dc);


			if (!_hoops_PIAGC(_hoops_CSRGR)) {

#ifdef DEBUG_PRINTS
fprintf(stderr, "common_make_fbo_current failed!!! retreat...\n");
#endif
				_hoops_IHAGC(_hoops_CSRGR);

				_hoops_CSRGR->_hoops_PIGRR = _hoops_IPSGR;
			}

#if 0
#ifdef DEBUG_PRINTS
fprintf(stderr, "common_make_fbo_current worked!!!\n");
#endif
#endif

		}

		if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {

#ifdef DEBUG_PRINTS
fprintf(stderr, "DCT_PBUFFER_IMAGE\n");
#endif

			/* _hoops_HHHGC */
			_hoops_CSRGR->screen = DefaultScreenOfDisplay (_hoops_CSRGR->display);
			if (!_hoops_CHPGA (
					_hoops_CSRGR->display, 
					0, 
					_hoops_CSRGR->_hoops_IHGRR->width,
					_hoops_CSRGR->_hoops_IHGRR->height,
					&_hoops_CSRGR->pbuffer,
					&_hoops_CSRGR->context,
					&_hoops_CSRGR->_hoops_CAAAC))
				return 0;
// 11-_hoops_ACHSP-2009 _hoops_PSSPC;  _hoops_HSSPC _hoops_III _hoops_RHAP _hoops_HAR _hoops_CASRR _hoops_GPP _hoops_ISSPC
#if !defined NUTCRACKER
			_hoops_CSRGR->window = _hoops_CSRGR->pbuffer;
#endif
			_hoops_CSRGR->visual = _hoops_CSRGR->_hoops_CAAAC->visual;
			identify_renderer ((Display_Context alter *)dc);
			_hoops_IAHGC ((Display_Context alter *)dc);
		}
#endif

	}

	/* _hoops_HA _hoops_SGS _hoops_GGSC _hoops_HRGR _hoops_ASCR _hoops_IS _hoops_RPPS _hoops_SR _hoops_PIHA _hoops_HGSR _hoops_IIIGC _hoops_IH _hoops_SCH */
	_hoops_CSRGR->_hoops_SRRRR = dc->options._hoops_SRRRR;

#if !defined _hoops_HRGAC
	if (_hoops_CSRGR->_hoops_PIGRR != _hoops_CPSGR && _hoops_CSRGR->_hoops_PIGRR != _hoops_SSRAC) {

		if (_hoops_CSRGR->visual) {

			int _hoops_HHAPC, _hoops_IHAPC;

			glXGetConfig(_hoops_CSRGR->display, _hoops_CSRGR->_hoops_CAAAC, GLX_SAMPLE_BUFFERS_ARB, &_hoops_IHAPC);
			glXGetConfig(_hoops_CSRGR->display, _hoops_CSRGR->_hoops_CAAAC, GLX_STEREO, &_hoops_HHAPC);

			_hoops_CSRGR->_hoops_PHHGC = (_hoops_IHAPC > 0);

			Display_Context alter * _hoops_HAPRH = (Display_Context alter *)dc;
			if (_hoops_HHAPC)
				_hoops_HAPRH->_hoops_PGCC.flags |= _hoops_IPPHP;
			else
				_hoops_HAPRH->_hoops_PGCC.flags &= ~_hoops_IPPHP;

		}

		/* _hoops_SAHR _hoops_HPCAR _hoops_SGS _hoops_RH _hoops_GGSC _hoops_SSCP _hoops_AAHRP _hoops_PSCA */
		glXGetConfig(_hoops_CSRGR->display, _hoops_CSRGR->_hoops_CAAAC, GLX_ACCUM_RED_SIZE, &_hoops_CSRGR->accumulation_bits);

	}
#endif

	_hoops_PICGC ((Display_Context alter *)dc);

	/* _hoops_ASIGA _hoops_RRP _hoops_IS _hoops_CAHA _hoops_RGR _hoops_GGSR _hoops_CIAH */
	if (_hoops_CSRGR->_hoops_SRRRR){
#ifdef SOLARIS_SYSTEM
		((Display_Context alter*)dc)->_hoops_PGCC._hoops_CHHSR = _hoops_RCPGA;
#else
		((Display_Context alter*)dc)->_hoops_PGCC._hoops_CHHSR = _hoops_ACPGA;
#endif
        }

	return (POINTER_SIZED_INT) _hoops_CSRGR->window;
}

#if !defined _hoops_HRGAC
/*
 * _hoops_PGAA
 */
local void
_hoops_CHAPC (Display_Context const * dc) 
{
	OGLData alter *_hoops_CSRGR = OGLD (dc);

	/* _hoops_PHHR _hoops_IS _hoops_GSSR _hoops_ARPP _hoops_SR _hoops_SHAPC _hoops_RH _hoops_APHSR _hoops_PIH */
	ENSURE_DRAW_MODE (_hoops_CSRGR, DRAW_MODE_NORMAL);
	if (dc->options._hoops_ISPRP == 0) {
		XFreeColormap (_hoops_CSRGR->display, _hoops_CSRGR->overlay.colormap);
		XDestroyWindow (_hoops_CSRGR->display, _hoops_CSRGR->overlay.window);
	}
	FREE_ARRAY (_hoops_CSRGR->overlay.colors, _hoops_CSRGR->overlay._hoops_AHISI, Driver_Color);
}
#endif


/*
 * _hoops_SRAC
 */
local void
free_outer_window (Display_Context const * dc) 
{
	OGLData alter *_hoops_CSRGR = OGLD (dc);

#ifdef DEBUG_PRINTS
fprintf(stderr, "free_outer_window %p\n", (void*)_hoops_CSRGR);
#endif


#if !defined _hoops_HRGAC
	glXMakeCurrent (_hoops_CSRGR->display, _hoops_CSRGR->window, _hoops_CSRGR->context);
#endif

	_hoops_SPSGC(dc);

#if !defined _hoops_HRGAC
	glXMakeCurrent (_hoops_CSRGR->display, None, null);

	if (_hoops_CSRGR->_hoops_PIGRR != _hoops_CPSGR && _hoops_CSRGR->_hoops_PIGRR != _hoops_SSRAC) {

		if (_hoops_CSRGR->_hoops_CSHGC) 
			_hoops_CHAPC (dc);
		if (_hoops_CSRGR->context != null) {
			XFlush (_hoops_CSRGR->display);
			glXDestroyContext (_hoops_CSRGR->display, _hoops_CSRGR->context);
			_hoops_CSRGR->context = (GLXContext) 0;
		}
		if (_hoops_CSRGR->_hoops_CAAAC && _hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
			XFree(_hoops_CSRGR->_hoops_CAAAC);
			_hoops_CSRGR->_hoops_CAAAC = null;
		}

		if (_hoops_CSRGR->_hoops_RPAAC->free_outer_window)
			(*_hoops_CSRGR->_hoops_RPAAC->free_outer_window) (dc);
		if (_hoops_CSRGR->_hoops_RPAAC->finish_update)
			(*_hoops_CSRGR->_hoops_RPAAC->finish_update) (dc);  /* _hoops_RGR _hoops_GRS _hoops_HAGGR _hoops_RH _hoops_RPPS */
	}
#endif

}


/*
 * _hoops_SRAC
 */
local void
_hoops_RSCSP (Display_Context const * dc) 
{
	OGLData alter *_hoops_CSRGR = OGLD (dc);
#if !defined _hoops_HRGAC

	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) return;

	/* _hoops_SGH _hoops_GPAAC _hoops_SRS */
	(*_hoops_CSRGR->_hoops_RPAAC->_hoops_RSCSP) (dc);
	_hoops_CSRGR->_hoops_HCAC = _hoops_CCC;
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_CSRGR->_hoops_IARRR = _hoops_CCC;
	_hoops_CSRGR->_hoops_ICAC = _hoops_CCC;
	/*
	 * _hoops_SIGP: _hoops_RH _hoops_RPSI _hoops_RPPS _hoops_IIP _hoops_SAGGR _hoops_RH _hoops_PCCS _hoops_PGRRR!	
	 * _hoops_PPRII _hoops_SHH _hoops_GHGA _hoops_CPHP _hoops_RHPH...
	 * _hoops_HIH _hoops_RGR _hoops_HRGR _hoops_IRS _hoops_GHRP _hoops_HGASI _hoops_IH _hoops_HA...
	 */
	if (_hoops_CSRGR->_hoops_CSHGC) {
		X11Data const *_hoops_RRRPC = X11D (dc);
		XResizeWindow (_hoops_CSRGR->display, _hoops_CSRGR->overlay.window,
					   _hoops_RRRPC->window_width, _hoops_RRRPC->window_height);
	}
#endif
}



/*
 * _hoops_SRAC
 */
local void
_hoops_RSCSR (_hoops_APARR alter & _hoops_RRCI) {
	/* _hoops_SR _hoops_CHR _hoops_HAR _hoops_CHRCP _hoops_GPAAC _hoops_IS _hoops_PGSA _hoops_PA..._hoops_CR _hoops_SR _hoops_SSSCP _hoops_RGSHA _hoops_PGAP _hoops_SRHR
	 * _hoops_SCH _hoops_RRRS _hoops_CRGR _hoops_GGR _hoops_GHGPR _hoops_SRHR _hoops_CCH.	 _hoops_PHGP _hoops_SR _hoops_CHASA _hoops_HCR _hoops_GPAAC _hoops_ASCA _hoops_SICAR.
	 */

	/* _hoops_SISS _hoops_GASCA _hoops_CIPH */
	_hoops_RRCI->start_device = start_device;
	_hoops_RRCI->stop_device = stop_device;
	_hoops_RRCI->get_physical_info = get_physical_info;
	_hoops_RRCI->get_outer_window = get_outer_window;
	_hoops_RRCI->free_outer_window = free_outer_window;
	_hoops_RRCI->_hoops_RSCSP = _hoops_RSCSP;
	_hoops_RRCI->finish_picture = finish_picture;
	_hoops_RRCI->init_picture = init_picture;
	_hoops_RRCI->finish_update = finish_update;
	_hoops_RRCI->init_update = init_update;
	_hoops_RRCI->get_current_info = get_current_info;

	/* _hoops_RHCAC _hoops_SICAR */
	_hoops_RRCI->draw_dc_polyline = draw_dc_polyline;
	_hoops_RRCI->draw_dc_face = draw_dc_face;
	_hoops_RRCI->draw_dc_polytriangle = draw_dc_polytriangle;
	_hoops_RRCI->draw_dc_colorized_face = draw_dc_colorized_face;
	_hoops_RRCI->draw_dc_rgb32_rasters = draw_dc_rgb32_rasters;
	_hoops_RRCI->draw_dc_rectangle = draw_dc_rectangle;
	_hoops_RRCI->draw_dc_polydot = draw_dc_polydot;
	_hoops_RRCI->draw_dc_colorized_polydot = draw_dc_colorized_polydot;
	_hoops_RRCI->draw_dc_ellipse = HD_Std_DC_Ellipse;
	_hoops_RRCI->_hoops_SCISR = HD_Std_DC_Outline_Ellipse;
	_hoops_RRCI->_hoops_RPCGA = HD_Std_DC_Polygon;
	_hoops_RRCI->draw_dc_polymarker = HD_Std_DC_Polymarker;
	_hoops_RRCI->draw_dc_gouraud_polyline = draw_dc_gouraud_polyline;
	_hoops_RRCI->draw_dc_colorized_polyline = draw_dc_colorized_polyline;
	_hoops_RRCI->draw_dc_gouraud_polytriangle = draw_dc_gouraud_polytriangle;
	_hoops_RRCI->draw_dc_colorized_polytriangle = draw_dc_colorized_polytriangle;
#ifndef DISABLE_TEXTURING
	_hoops_RRCI->draw_dc_textured_polytriangle = draw_dc_textured_polytriangle;
#endif

	/* _hoops_HCR _hoops_RH _hoops_HRCSR _hoops_SICAR */
	_hoops_RRCI->find_all_fonts = find_all_fonts;
	_hoops_RRCI->_hoops_CACSR = _hoops_CACSR;
	_hoops_RRCI->load_font = load_font;
	_hoops_RRCI->unload_font = unload_font;
	_hoops_RRCI->draw_dc_text = draw_dc_text;
	_hoops_RRCI->measure_char = measure_char;
	_hoops_RRCI->_hoops_SRCSR = _hoops_SRCSR;

	/* _hoops_CIIA _hoops_SICAR */
	_hoops_RRCI->_hoops_HSCSP = _hoops_HSCSP;
	_hoops_RRCI->_hoops_ISCSP = _hoops_ISCSP;

	/* _hoops_AHCR _hoops_SRHR _hoops_PCPH */
	_hoops_RRCI->_hoops_CAAGR = _hoops_CAAGR;

	/* _hoops_APHSR _hoops_SICAR */
	_hoops_RRCI->draw_overlay_list = draw_overlay_list;
	_hoops_RRCI->_hoops_SCPGR = _hoops_SCPGR;

	/* _hoops_PGSA 3D _hoops_SICAR */
#ifdef _hoops_CGSPR
	if (HI_Show_Environment ("NO3D", &_hoops_CSSPC))
		return;
#endif

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
// 11-_hoops_ACHSP-2009 _hoops_PSSPC;  _hoops_HSSPC _hoops_III _hoops_RHAP _hoops_HAR _hoops_CASRR _hoops_GPP _hoops_ISSPC
#if !defined NUTCRACKER
	_hoops_RRCI->draw_3d_text = draw_3d_text;
#endif
	_hoops_RRCI->draw_3d_polycylinder = draw_3d_polycylinder; 
	_hoops_RRCI->draw_3d_cylinder = draw_3d_cylinder;
	_hoops_RRCI->draw_3d_sphere = draw_3d_sphere;
	/* _hoops_HPGR->_hoops_GPCPC = _hoops_GPCPC; */
	_hoops_RRCI->draw_3d_image = draw_3d_image;

	/* _hoops_AIRI _hoops_CPCI */
	_hoops_RRCI->_hoops_AICI = _hoops_AICI;
	_hoops_RRCI->_hoops_GGSI = _hoops_GGSI;
	_hoops_RRCI->_hoops_AIGC = _hoops_AIGC;
	_hoops_RRCI->_hoops_PPCI = _hoops_PPCI;

	_hoops_RRCI->_hoops_SSRGR = _hoops_SSRGR;
	_hoops_RRCI->_hoops_CGAGR = _hoops_CGAGR;

	/* _hoops_IAGIP _hoops_SICAR... */
	_hoops_RRCI->create_region = create_region;
	_hoops_RRCI->_hoops_HIPGR = _hoops_HIPGR;
	_hoops_RRCI->_hoops_PIPGR = _hoops_PIPGR;
	_hoops_RRCI->_hoops_ISPGR = _hoops_ISPGR;
	_hoops_RRCI->_hoops_CSPGR = _hoops_CSPGR;
	_hoops_RRCI->_hoops_AGHGR = _hoops_AGHGR;
	_hoops_RRCI->snapshot = snapshot;
	_hoops_RRCI->_hoops_IGHGR = _hoops_IGHGR;

}/* _hoops_RSGR _hoops_API _hoops_SRAAH */


/*
 * _hoops_IAAAH _hoops_PPICR
 */
#ifndef _hoops_ICGGC
extern "C" bool HC_CDECL HD_OpenGL_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter * _hoops_GHRI, int request, void * request_info) {
#else
extern "C" bool HC_CDECL HD_MGL_Driver (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR alter * _hoops_GHRI, int request, void * request_info) {
#endif


	Display_Context alter *dc;


	if (request == _hoops_GAGRH)
		return true;

	/*
	 * _hoops_HPGGR _hoops_RGR _hoops_GAR _hoops_IRS _hoops_IPSP _hoops_IIGR _hoops_RH _hoops_SPCR _hoops_RHPP - _hoops_RGAR _hoops_ICPRA _hoops_RPHR _hoops_HA
	 * _hoops_IS _hoops_SPCR _hoops_RIHH _hoops_PRCA.
	 */
	_hoops_GHRI->_hoops_AAIAP = HD_X11_Driver;

	/* _hoops_AA _hoops_PCPA'_hoops_GRI _hoops_SSGRR */
	if (!HD_X11_Driver (_hoops_RIGC, _hoops_GHRI, request, request_info)) 
		return false;

	/* _hoops_HPGR _hoops_RGR _hoops_PPSR _hoops_CSPH _hoops_SSCP _hoops_RPII _hoops_PSPP _hoops_PPR _hoops_GPAAC'_hoops_GRI _hoops_ACPH _hoops_GASR _hoops_PIISR _hoops_GGR */
	dc = (Display_Context alter *) _hoops_GHRI->_hoops_PPRPR;

	/* _hoops_PCSA _hoops_RH _hoops_ACAGR _hoops_IIGR _hoops_RH _hoops_GPAAC _hoops_HSPP _hoops_SISS _hoops_HIS _hoops_SR _hoops_PAH _hoops_AASA _hoops_SCH */
	_hoops_AGRPC = dc->_hoops_ACPGR->start_device;

	/* _hoops_PAIHR! _hoops_HS _hoops_GPAAC'_hoops_GRI _hoops_HSPP _hoops_SISS _hoops_CPSA _hoops_AASA _hoops_CARS */
	dc->_hoops_ACPGR->start_device = start_device;

	return true;
}

#endif /* _hoops_ARGAC */
#endif





/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a 
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.19 2010-12-06 22:42:23 heppe Exp $
 */

// '_hoops_CRSRR' _hoops_HRGR _hoops_PCCP _hoops_RPCPC-_hoops_GSGGR _hoops_PGGRA
#define id _hoops_APCPC
#include "hoops.h"
#include "hd_proto.h"
#undef id

#ifdef OSX_SYSTEM     /* _hoops_SR'_hoops_ASAR _hoops_GPP _hoops_SSIGI */
#ifndef COCOA_OPENGL_DRIVER /* _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_RH _hoops_PPCPC _hoops_RHPP */

/*
 * _hoops_APICR _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_Cocoa_OpenGL_Driver (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR alter *		_hoops_GHRI,
	int					request,
	void *				request_info) {
	return HD_No_Driver (_hoops_RIGC, _hoops_GHRI, request, "cocoa_opengl");
}

#else /* _hoops_SR'_hoops_ASAR _hoops_GPP _hoops_SSIGI _hoops_PPR _hoops_HHPS _hoops_GGR _hoops_RH _hoops_SRCIA _hoops_RHPP */

local void * _hoops_CCPGA(const char *_hoops_SCPGA);

#define COCOA_OGL_DRIVER // _hoops_RGR _hoops_AGSR _hoops_SR'_hoops_ASAR _hoops_ASSA _hoops_RH _hoops_HPCPC _hoops_RHPP, _hoops_RH _hoops_RSIRR _hoops_HRGR _hoops_PAHH _hoops_HAH _hoops_CRICR _hoops_IS _hoops_IPCPC _hoops_HA _hoops_PHRI
#define DECLARE_OGL_PROTOTYPES

struct OGLData;
static void _hoops_CPCPC(OGLData *_hoops_CSRGR);

#define id _hoops_APCPC
#include "ogl.cpp"
#undef id

#define Point _hoops_SARRI
#define Style OSX_Style
#define Marker _hoops_GPRRI
#define Polygon _hoops_RPRRI
#define Button OSX_Button
#define Line _hoops_APRRI

#include <AppKit/AppKit.h>
#include <Cocoa/Cocoa.h>
#include <Foundation/Foundation.h>
#include <OpenGL/CGLCurrent.h>
#include <OpenGL/CGLTypes.h>
#include <OpenGL/OpenGL.h>

#undef Point
#undef Style
#undef Marker
#undef Polygon 
#undef Button
#undef Line

struct _hoops_SPCPC : public OGLData
{
	NSOpenGLView *_hoops_IHPGA;
	NSWindow *window;
	
	NSOpenGLContext *_hoops_SIPGA;
	NSOpenGLContext *_hoops_GCPGA;
	
	NSOpenGLPixelBuffer *pbuffer;
	CGDirectDisplayID _hoops_GHCPC;
	
	int yfudge;
    int _hoops_CCGRR;	
    float _hoops_ISIH;	
	
	bool _hoops_IRRRR;
	int _hoops_HRRRR;	
	NSUInteger key_state;	
    int _hoops_SCGRR;
    int mouse_y;	
};

#define _hoops_RHCPC(dc) ((_hoops_SPCPC alter *)((dc)->_hoops_RIHGR))
#define _hoops_AHCPC(nr) (_hoops_RHCPC((nr)->_hoops_SRA))

// _hoops_PHCPC _hoops_GRS _hoops_RCHPP _hoops_RH _hoops_PGCR _hoops_HSPR _hoops_HHCPC _hoops_CGPR _hoops_SCH'_hoops_GRI _hoops_CPHR _hoops_CCA _hoops_CAPR
#define OGLDATA _hoops_SPCPC
#define _hoops_PIAGA _hoops_IHCPC
#include "cocoa_common.mm"


static void _hoops_CPCPC(OGLData *_hoops_CSRGR) {
	
	NSOpenGLContext *_hoops_HSHAC = ((_hoops_SPCPC*)_hoops_CSRGR)->_hoops_SIPGA;	
	[_hoops_HSHAC makeCurrentContext];
}

/*
 * _hoops_PGAA
 */
void
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

/*
 * _hoops_SRAC
 */
local void
finish_picture (Net_Rendition const &  nr,
				bool swap_buffers) 
{
	Display_Context const *dc = nr->_hoops_SRA;
	_hoops_SPCPC alter *_hoops_CSRGR = _hoops_AHCPC (nr);	
	
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
								
			[_hoops_CSRGR->_hoops_SIPGA flushBuffer];				
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
check_events (_hoops_SPCPC alter * _hoops_CSRGR);

/*
 * _hoops_SRAC
 */
local void
finish_update (Display_Context const * dc) {
	
	_hoops_SPCPC alter *_hoops_CSRGR = _hoops_RHCPC (dc);
	
	if (!BIT(dc->flags, _hoops_SAISR))
		return;
	
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR)
		if (!dc->options._hoops_CRSSP &&
			!BIT (dc->options._hoops_IRARR, _hoops_GCCRH))
			check_events (_hoops_CSRGR);
	
	[NSOpenGLContext clearCurrentContext];
	
	if (_hoops_CSRGR->_hoops_GCPGA) {
		[_hoops_CSRGR->_hoops_GCPGA makeCurrentContext];
	}
		
	_hoops_CSRGR->_hoops_GCPGA = 0;	
		
}


/*
 * _hoops_SRAC
 */
local void
init_update (Display_Context const * dc) 
{
	// _hoops_GHHSI _hoops_IIGR _hoops_RH _hoops_HPCPC _hoops_PSCH _hoops_SR _hoops_AASA _hoops_ARI _hoops_PAH _hoops_CPSA _hoops_PHIS _hoops_IH _hoops_IHHH _hoops_IS _hoops_ASRC _hoops_RIHH _hoops_SSHRH, _hoops_SR _hoops_SIAS _hoops_HHGC _hoops_IS _hoops_HPPR/_hoops_IGHAR _hoops_RSIPH _hoops_ARI _hoops_RIIA.
	
	_hoops_SPCPC alter *_hoops_CSRGR = _hoops_RHCPC(dc);
	
	int _hoops_HAIPC = 0;	
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
		_hoops_CSRGR = _hoops_RHCPC (dc);
		
		if (!_hoops_CSRGR) 
			return;
	}
	
	invalidate_cache (_hoops_CSRGR);
	
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {	
		
		[_hoops_CSRGR->_hoops_SIPGA setPixelBuffer:_hoops_CSRGR->pbuffer
										  cubeMapFace:0
										  mipMapLevel:0
								 currentVirtualScreen:0];
	}
	else {		
		
		if (!_hoops_CSRGR->_hoops_IHPGA)
			return;					
		
		Rect rect = _hoops_SHPGA<_hoops_SPCPC>(dc);		
		
		if ( (rect.right-rect.left != _hoops_CSRGR->window_width) || 
			 (rect.bottom-rect.top != _hoops_CSRGR->window_height) ) {
			
			_hoops_CSRGR->window_width = rect.right-rect.left;
			_hoops_CSRGR->window_height = rect.bottom-rect.top;
						
			_hoops_CSRGR->yfudge = (rect.bottom-rect.top);
			
#if 0
			printf("resized %d %d %d %d %d %d\n",
				   rect.left, rect.top, rect.right, rect.bottom,
				   rect.right-rect.left, rect.bottom-rect.top);
#endif						
			
			[_hoops_CSRGR->_hoops_SIPGA update];
			
			HD_Resize_Subscreen (dc, true,
								 0, (rect.right-rect.left)-1, 
								 0, (rect.bottom-rect.top)-1);			
			
		}
	}
		
	_hoops_CSRGR->_hoops_GCPGA = [NSOpenGLContext currentContext];
	[_hoops_CSRGR->_hoops_SIPGA makeCurrentContext];
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
check_events (_hoops_SPCPC alter * _hoops_CSRGR) {		
	
	check_events<_hoops_SPCPC>(_hoops_CSRGR);
}

/*
 * _hoops_SRAC
 */
local bool
_hoops_HSCSP (Display_Context const * dc,
				  int alter * button,
				  int alter * x, int alter * y) {
	_hoops_SPCPC alter *_hoops_CSRGR = _hoops_RHCPC (dc);
	
	
	if (_hoops_CSRGR != null) {
		check_events (_hoops_CSRGR);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		_hoops_CSRGR = _hoops_RHCPC (dc);
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
	_hoops_SPCPC alter *_hoops_CSRGR = _hoops_RHCPC (dc);
	
	if (_hoops_CSRGR != null) {
		check_events (_hoops_CSRGR);
		/* _hoops_HGI _hoops_SPS _hoops_III _hoops_HRGR _hoops_GIIRH _hoops_HAHH _hoops_IS _hoops_SGHIP _hoops_RH _hoops_CRS */
		_hoops_CSRGR = _hoops_RHCPC (dc);
		
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
	
	_hoops_SPCPC alter *_hoops_CSRGR = _hoops_RHCPC(dc);	
	
	if (dc->options._hoops_GCHSR != 0) {
		dc->options._hoops_RASSP = true;
		dc->options._hoops_AASSP = true;
		dc->options._hoops_PASSP = true;
		dc->options._hoops_HPHRP = false;
	}

	/* _hoops_HIHH _hoops_SHR _hoops_APPP 8 _hoops_SIH _hoops_RIR _hoops_AIHSR */
	dc->current._hoops_AAPSR = 1L << 24;
	dc->current._hoops_APASR = 0;
	
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		dc->current.extent.left = (float) 0;
		dc->current.extent.right = (float) dc->_hoops_PGCC._hoops_PRPSR.x - 1;
		dc->current.extent.bottom = (float) 0;
		dc->current.extent.top = (float) dc->_hoops_PGCC._hoops_PRPSR.y - 1;
	}
	else if (_hoops_CSRGR->_hoops_IHPGA) {		
		
		Rect rect = _hoops_SHPGA<_hoops_SPCPC>(dc);
		
		dc->current.extent.left = (float) rect.left;
		dc->current.extent.right = (float) rect.right - 1;
		dc->current.extent.bottom = (float) (_hoops_CSRGR->_hoops_CCGRR - (rect.bottom - 1));
		dc->current.extent.top = (float) (_hoops_CSRGR->_hoops_CCGRR - rect.top);
	
	}
	else {	
		
		dc->current.extent.left = 0.0f;
		dc->current.extent.right = CGDisplayPixelsWide(_hoops_CSRGR->_hoops_GHCPC);
		dc->current.extent.bottom = CGDisplayPixelsHigh(_hoops_CSRGR->_hoops_GHCPC);
		dc->current.extent.top = 0.0f;
	}	
	
}


/*
 * _hoops_SRAC
 */
local void
get_physical_info (Display_Context alter * dc) {
	
	_hoops_SPCPC alter *_hoops_CSRGR = _hoops_RHCPC(dc);
		
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
				
		dc->_hoops_PGCC._hoops_PRPSR.x = CGDisplayPixelsWide(_hoops_CSRGR->_hoops_GHCPC);
		dc->_hoops_PGCC._hoops_PRPSR.y = CGDisplayPixelsHigh(_hoops_CSRGR->_hoops_GHCPC);
		
		CGSize size = CGDisplayScreenSize(_hoops_CSRGR->_hoops_GHCPC);
		
		dc->_hoops_PGCC.size.x = size.width / 10;
		dc->_hoops_PGCC.size.y = size.height / 10;		
		
	}
	
	if (dc->options._hoops_SPHSR.x != -1) {
		dc->_hoops_PGCC.size.x = dc->options._hoops_SPHSR.x;
		dc->_hoops_PGCC.size.y = dc->options._hoops_SPHSR.y;
	}
	
	_hoops_CSRGR->yfudge = _hoops_CSRGR->_hoops_CCGRR = dc->_hoops_PGCC._hoops_PRPSR.y - 1;
	
	/* _hoops_PPSI _hoops_GGR _hoops_GHAR _hoops_RGGHR _hoops_ARI..._hoops_SAHR _hoops_GGR _hoops_AGIR _hoops_RH _hoops_RPGP _hoops_RPPS _hoops_ISHS */
	dc->_hoops_PGCC._hoops_PCHSR = 256;
	dc->_hoops_PGCC._hoops_PIHSR = _hoops_HIHSR;
	dc->_hoops_PGCC.driver_type = "COCOA_OGL";
	dc->_hoops_PGCC._hoops_SCHSR = "$Revision: 1.19 $";
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
	
	if (_hoops_CSRGR->_hoops_SIPGA)	
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

/*
 * _hoops_SRAC
 */
local bool
start_device (Display_Context alter * dc) {
	
	_hoops_SPCPC *_hoops_CSRGR;
	ZALLOC (_hoops_CSRGR, _hoops_SPCPC);
	/* _hoops_CSPH->_hoops_PIH _hoops_GHCA _hoops_HS _hoops_RH _hoops_PCHAC _hoops_RHPP'_hoops_GRI _hoops_PIH _hoops_GPP _hoops_SCH */
	if (!dc->data) 
		dc->data = (void alter *) _hoops_CSRGR;
	dc->_hoops_RIHGR = (void alter *) _hoops_CSRGR;
	_hoops_CSRGR->dc = dc;	
	
	_hoops_CSRGR->_hoops_GHCPC = CGMainDisplayID();
	
	if (!dc->options._hoops_GCHSR) {
		
		_hoops_CSRGR->_hoops_PIGRR = _hoops_PPSGR;	
		
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
		
        _hoops_CSRGR->_hoops_IHGRR = image;
		_hoops_CSRGR->window_width = _hoops_CSRGR->_hoops_IHGRR->width;
		_hoops_CSRGR->window_height = _hoops_CSRGR->_hoops_IHGRR->height;
        _hoops_PRRH (_hoops_CSRGR->_hoops_IHGRR);
        _hoops_CSRGR->_hoops_PIGRR = _hoops_IPSGR; 
    }
	else {
		
		_hoops_CSRGR->_hoops_PIGRR = _hoops_HPSGR;
		
		_hoops_CSRGR->_hoops_IHPGA = (NSOpenGLView*)dc->options._hoops_GCHSR;			
		dc->current._hoops_RAPGH = (POINTER_SIZED_INT)_hoops_CSRGR->_hoops_IHPGA;		
				
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

	_hoops_CSRGR->_hoops_PIGRR = _hoops_APSGR;
	
	if (_hoops_CSRGR->_hoops_PRARR)
		HI_Free_Driver_Config(_hoops_CSRGR->_hoops_PRARR);
	
	FREE (_hoops_CSRGR, _hoops_SPCPC);
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

/*
 * _hoops_SRAC
 */
local POINTER_SIZED_INT
get_outer_window (Display_Context const * _hoops_SAGRH) {
	
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	Display_Context alter * dc = (Display_Context alter *) _hoops_SAGRH;
	POINTER_SIZED_INT retval = 0L;
	_hoops_SPCPC alter *_hoops_CSRGR = _hoops_RHCPC(dc);
	
	invalidate_cache (_hoops_CSRGR);
	_hoops_CHCGC(dc);
	
	switch (_hoops_CSRGR->_hoops_PIGRR) {
			
		case _hoops_IPSGR:
			retval = _hoops_CHPGA<_hoops_SPCPC>(dc);		
			break;
			
		case _hoops_PPSGR:
			retval = create_standalone_window<_hoops_SPCPC,_hoops_IHCPC>(dc);
			break;
			
		case _hoops_HPSGR:
			retval = (POINTER_SIZED_INT)_hoops_CSRGR->_hoops_IHPGA;
			break;
			
		case DCT_IMAGE:
		default:
			HE_ERROR (HEC_OPENGL_DRIVER, HES_CANNOT_OPEN_DISPLAY, 
					  "internal error: unsupported display context type in ogl_cocoa:get outer window");
			HD_Kill_Driver (dc);
	}	
	
	choose_pixel_format<_hoops_SPCPC>(dc);	
	
	// _hoops_RIPPR _hoops_RGR _hoops_GGSR _hoops_IIGR _hoops_CHCPC _hoops_PGGA _hoops_CGSAC (_hoops_HCIAR _hoops_RHPP) _hoops_ASSP'_hoops_RA _hoops_HS _hoops_PCCP _hoops_SHCPC _hoops_PAIP.
	{	
		GLint _hoops_AIPGA = 0;
		//[[_hoops_HGPGA->_hoops_RAR _hoops_GICPC] _hoops_RICPC : &_hoops_SHCPC _hoops_AICPC : _hoops_PICPC _hoops_HICPC : 0];
		CGLPixelFormatObj _hoops_IICPC = CGLRetainPixelFormat(CGLGetPixelFormat((CGLContextObj)[_hoops_CSRGR->_hoops_SIPGA CGLContextObj]));
		CGLDescribePixelFormat(_hoops_IICPC, 0, kCGLPFASamples, &_hoops_AIPGA);
		CGLReleasePixelFormat(_hoops_IICPC);
		_hoops_CSRGR->_hoops_AIPGA = _hoops_AIPGA;
		_hoops_CSRGR->_hoops_PHHGC = (_hoops_AIPGA != 0);	
	}	
	
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {		
		
		[_hoops_CSRGR->_hoops_SIPGA setPixelBuffer:_hoops_CSRGR->pbuffer
										  cubeMapFace:0
										  mipMapLevel:0
								 currentVirtualScreen:0];		
	}	
	else if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR) {	
		
		ProcessSerialNumber _hoops_IHIPC = {0, kCurrentProcess};
		TransformProcessType(&_hoops_IHIPC, kProcessTransformToForegroundApplication);        
        [_hoops_CSRGR->window makeKeyAndOrderFront:NSApp]; // _hoops_CRGH _hoops_RH _hoops_RPPS, _hoops_PIHA _hoops_IHPS *_hoops_RAS* _hoops_CHCPC     
        
	}
	else {
			
	}
	
	// _hoops_CPPPR _hoops_SAPIA _hoops_IS _hoops_IRHH _hoops_GGSC _hoops_SCGR _hoops_ARPP _hoops_HCHPC _hoops_SRIPR _hoops_GGR _hoops_CICPC _hoops_CAPP.
	[_hoops_CSRGR->_hoops_SIPGA makeCurrentContext];
	
	identify_renderer(dc);
	
	_hoops_CSRGR->_hoops_SRRRR = dc->options._hoops_SRRRR;
	
	/* _hoops_IH _hoops_HA, _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_SCGH _hoops_IAPR _hoops_RH _hoops_SCGR _hoops_AIR _hoops_RPCC _hoops_IAGC _hoops_GRPAR
	 _hoops_IS _hoops_IRS _hoops_CRCPC, _hoops_PPR _hoops_RGSR _hoops_RGR _hoops_SRCPC = 16 _hoops_ASSP'_hoops_RA _hoops_IPHR _hoops_CCA _hoops_RH
	 _hoops_SHIR _hoops_GACPC */
	if (BIT(dc->options._hoops_IRARR, _hoops_APGAC))
		_hoops_CSRGR->accumulation_bits = 0;
	
	_hoops_PICGC((Display_Context alter *) dc);
	
	/* _hoops_RAGAC _hoops_RHPP _hoops_GHSAI _hoops_SICPC _hoops_ARI */
	
	[pool drain];
	
	return retval;	
}


/*
 * _hoops_SRAC
 */
local void
free_outer_window (Display_Context const * dc) {
	
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];	
	_hoops_SPCPC alter *_hoops_CSRGR = _hoops_RHCPC (dc);	
	
	_hoops_SPSGC(dc);	
	
	[NSOpenGLContext clearCurrentContext];
	
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_PPSGR) {			
		
		[_hoops_CSRGR->window close];	
		[_hoops_CSRGR->_hoops_IHPGA release];
		[_hoops_CSRGR->window release];			
	}
	else if (_hoops_CSRGR->_hoops_PIGRR == _hoops_IPSGR) {
		
		[_hoops_CSRGR->pbuffer release];		
		_hoops_CSRGR->pbuffer = null;
		
		// _hoops_RPP _hoops_RGR _hoops_CSAP _hoops_IRS _hoops_CGSRC _hoops_PSCR _hoops_SR _hoops_HAII _hoops_RH _hoops_GGSC _hoops_HIS _hoops_RCSH _hoops_SCH
		printf("releasing pbuffer context\n");
		[_hoops_CSRGR->_hoops_SIPGA release];
		_hoops_CSRGR->_hoops_SIPGA = null;		
	}	
	
	[pool drain];	
}

/*
 * _hoops_SRAC
 */
local void
_hoops_RSCSP (Display_Context const * dc) {	
	
	_hoops_SPCPC alter *_hoops_CSRGR = _hoops_RHCPC (dc);
	_hoops_CSRGR->_hoops_HCAC = _hoops_CCC;
	_hoops_CSRGR->_hoops_RPCI = _hoops_CCC;
	_hoops_CSRGR->_hoops_IARRR = _hoops_CCC;
	_hoops_CSRGR->_hoops_ICAC = _hoops_CCC;
	
	if (_hoops_CSRGR->_hoops_PIGRR == _hoops_HPSGR) return;
	
	//_hoops_IAHPC(_hoops_HGPGA->_hoops_RPPS, _hoops_CSPH->_hoops_GCCPC._hoops_RAAP, _hoops_CSPH->_hoops_GCCPC._hoops_SCIA, _hoops_RCPP);
	//_hoops_RCCPC(_hoops_HGPGA->_hoops_RPPS, 
	//		   _hoops_CSPH->_hoops_GCCPC._hoops_RPHR - _hoops_CSPH->_hoops_GCCPC._hoops_RAAP, 
	//		   _hoops_CSPH->_hoops_GCCPC._hoops_PRPC - _hoops_CSPH->_hoops_GCCPC._hoops_SCIA, 
	//		   _hoops_IHPR);
	
	// _hoops_SIGP
	
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
	CGFontRef family;
	OSX_Style face;
};


/*
 * _hoops_SRAC
 */
local void
draw_dc_text (Net_Rendition const &  nr,
			  DC_Point const * where,
			  int count, Karacter const * kstring) {
	
	printf("draw_dc_text \n");
	
}


/*
 * _hoops_SRAC
 */
local void
find_all_fonts (Display_Context alter * dc) {
	
	/* _hoops_RGR _hoops_ACPH _hoops_RHAP _hoops_ISAP _hoops_GGR _hoops_ACCPC _hoops_RHPP */	
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
						void ** _hoops_HPSRH) {
	
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
	ZALLOC (_hoops_RHCSR, OGLFontData);	
	
	CFStringRef _hoops_PCCPC = CFStringCreateWithCString(0,name,kCFStringEncodingUTF8);

	_hoops_RHCSR->family = CGFontCreateWithFontName(_hoops_PCCPC);
	
	/*
	 _hoops_IPRPR("_hoops_CACPC %_hoops_GRI \_hoops_ACHP", _hoops_RSIRR);
	 */
	if (_hoops_RHCSR->family == 0) {
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
unload_font (Display_Context const * dc, Font_Instance alter *instance) {
	
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
	
	
	/* _hoops_AGCR _hoops_CGH _hoops_IIP _hoops_SHH _hoops_PIGS..._hoops_SR _hoops_PHCAC _hoops_RH _hoops_HHCAC _hoops_HSRPR _hoops_RPP _hoops_SSIA _hoops_AA... */
	_hoops_RRCI->_hoops_GSCGA = null;
	_hoops_RRCI->_hoops_CCCSR = null;
	_hoops_RRCI->_hoops_PSCGA = null;
	
		
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
	
	/* _hoops_HRCSR _hoops_PRCA */
	_hoops_RRCI->measure_char = measure_char;
	_hoops_RRCI->draw_dc_text = draw_dc_text;
	_hoops_RRCI->find_all_fonts = find_all_fonts;
	_hoops_RRCI->load_font = load_font;
	_hoops_RRCI->unload_font = unload_font;	

	
}/* _hoops_RSGR _hoops_API _hoops_SRAAH */


/*
 * _hoops_IAAAH _hoops_PPICR
 */
extern "C" bool HC_CDECL HD_Cocoa_OpenGL_Driver (
										   _hoops_AIGPR *	_hoops_RIGC,
										   _hoops_GGAGR alter *		_hoops_GHRI,
										   int					request,
										   void *				request_info) {
	UNREFERENCED (request_info);
	
	return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, ::_hoops_RSCSR);
}

#endif
#endif


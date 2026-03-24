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
 * $Id: obf_tmp.txt 1.228 2010-12-08 23:11:56 warren Exp $
 */

#ifndef OGL2_H_DEFINED
#define OGL2_H_DEFINED


//_hoops_SGH _hoops_GPHA _hoops_SIRGR _hoops_RIIA _hoops_IIGR _hoops_AHCRC _hoops_IH _hoops_RH _hoops_GICAC/_hoops_RICAC
#define _hoops_AICAC
#define _hoops_PICAC


#define _hoops_IGCAC 600


#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "driver.h"
#include "hpserror.h"
#include "patterns.h"
#include "phedron.h"
#include "please.h"
#include "searchh.h"
#include "tandt.h"
#include "hversion.h"
#include "adt.h"

#include "3d_common.cpp"


#include "GL/glew.h"

#ifdef GLX_OPENGL2_DRIVER
#define Window X_Window
#define _hoops_PGIIR X_Font
#define Drawable X_Drawable
#define _hoops_RAAH X_Depth
#define _hoops_GSPGR X_Time

# include "GL/glxew.h"
#undef GLXPbufferClobberEvent
# include <GL/glx.h>

#undef Window 
#undef _hoops_PGIIR
#undef Drawable
#undef _hoops_RAAH
#undef _hoops_GSPGR 

# include "x11data.h"

# ifdef LINUX_SYSTEM
#   define caddr_t char*
#   ifndef __cplusplus
      typedef struct GLUquadric GLUquadric;
#   endif
# endif
# ifdef IRIX_SYSTEM
#   undef	_hoops_IRGAC	
#   undef 	_hoops_CRGAC	
# endif
# if defined(NUTCRACKER)
/* _hoops_IH _hoops_IGIGC _hoops_IGRIP _hoops_SRGAC */
      typedef Window GLXPbuffer;
#ifndef EXCEED_BUILD
      typedef void *GLXFBConfig;
#endif
#define glXChooseFBConfig(x1,x2,_hoops_SSIPA,_hoops_AGCPA) null
#define glXGetVisualFromFBConfig(x1,x2) null
#define glXCreatePbuffer(x1,x2,_hoops_SSIPA) null 
#endif
# define _hoops_GAGAC 256
# define SOLARIS_RESERVED_COLORS 65
#endif

#ifdef WGL2_DRIVER
#	include "msw.h"
#endif

#ifdef OSX_SYSTEM

#define Point _hoops_SARRI
#define Style OSX_Style
#define Marker _hoops_GPRRI
#define Polygon _hoops_RPRRI
#define Button OSX_Button

# undef local
# undef _hoops_AHRRI
# define _hoops_AHRRI static _hoops_PHRRI /* _hoops_HGASI _hoops_IH _hoops_IRS _hoops_ARPC _hoops_GGR _hoops_RAGAC _hoops_IRAGP */
# define Line AGLLine
# include <AGL/agl.h>
# undef Line
# undef local
# define local static
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <Carbon/Carbon.h>

#undef Point
#undef Style
#undef Marker
#undef Polygon 
#undef Button

#elif defined(WINDOWS_SYSTEM)
#include "glew/include/GL/wglew.h"
#endif

#define glewGetContext() _hoops_CSRGR->glewcontext
#define wglewGetContext() _hoops_CSRGR->wglewcontext

#ifndef AGLM
# define AGLM(x)
#endif




/* _hoops_AAGAC _hoops_HRGR _hoops_IRS _hoops_PPRRR _hoops_IIGR _hoops_CPIRA _hoops_SGS _hoops_SCH _hoops_HRGR _hoops_PAGAC _hoops_IH _hoops_RH 
 * _hoops_ISSC _hoops_HSP _hoops_IIGR _hoops_AGSAR _hoops_IS _hoops_RPGAH _hoops_HAGAC, _hoops_PRGI _hoops_RPP _hoops_SSIA _hoops_CHR _hoops_HAR _hoops_RHGCP _hoops_SGGR.  _hoops_HGI
 * _hoops_GRS _hoops_RASHR _hoops_HSRAP _hoops_PGARH _hoops_GPP _hoops_HHH _hoops_AAPGH. */
#define	_hoops_SIAAH	0x00000001
#define	_hoops_IAGAC			0x00000002
#define	_hoops_CAGAC			0x00000004
#define	_hoops_CIPRC		0x00000008
#define	_hoops_HICAC 0x00000010
#define	_hoops_IICAC  0x00000020
/* _hoops_IPACI _hoops_HRGR _hoops_ARSAR _hoops_HIS _hoops_SGS _hoops_SSHSR _hoops_PAH _hoops_CRGS _hoops_IHHH _hoops_HAR _hoops_IS _hoops_PSSRH _hoops_CRGR
 * _hoops_RH _hoops_GPSRR _hoops_GSSHR _hoops_IH _hoops_IRS _hoops_RPPS - _hoops_RGR _hoops_AGSR _hoops_SGS _hoops_RH _hoops_IPSP _hoops_PIHA _hoops_HPPP
 * _hoops_HCSRH _hoops_SSHRH _hoops_PPR _hoops_AASA _hoops_CPACI _hoops_CGPR _hoops_SSIA _hoops_HHGC _hoops_CHARP _hoops_IS _hoops_PGSA
 * _hoops_CRGR _hoops_RH _hoops_ARSAR _hoops_RPPS _hoops_HRGR _hoops_PPRAR _hoops_GPP _hoops_RPGAC*/
#define	_hoops_GCCRH		0x00000040
#define	_hoops_APGAC		0x00000080
#define	_hoops_HCARC		0x00000100
#define	Debug_QMOVES_NO_ZDAMAGE		0x00000200
#define	_hoops_CHARC 0x00000400
#define	_hoops_GSAAH				0x00000800
#define	_hoops_PPGAC		0x00001000
/*_hoops_SHIR _hoops_SCAC _hoops_HRGR _hoops_PGS*/
#define _hoops_PSCGC		0x00002000
#define	_hoops_PSAAH	0x00004000
#define _hoops_HPGAC		0x00008000
#define _hoops_ARHGC		0x00010000
#define _hoops_IPGAC		0x00020000
#define _hoops_SSAAH				0x00040000
#define _hoops_GGPAH				0x00080000
#define _hoops_GCSRH	0x00100000
#define _hoops_CPGAC			0x00200000
#define _hoops_SPGAC			0x00400000
#define _hoops_GHGAC	0x00800000
#define _hoops_ARRAH		0x01000000
#define _hoops_RHGAC	0x02000000
#define _hoops_AHGAC	0x04000000
#define _hoops_PHGAC				0x08000000



#define _hoops_RAPRC(a,b)



/* _hoops_HRARR _hoops_SCPGH */

#define XBIT_NONE							0L
#define XBIT_DOUBLE_BUFFER_SWAP_ONLY		1L
#define XBIT_FORCE_DEFAULT_SOFTWARE			2L
#define XBIT_BAD_OVERLAY					3L
#define XBIT_BAD_STENCIL					4L
#define XBIT_BAD_DISPLAY_LIST               5L
#define XBIT_LIES_ABOUT_SWAP				6L
#define XBIT_BAD_SINGLE_BUFFERING           7L
#define XBIT_BAD_ACCUMULATION_BUFFER		8L
#define XBIT_NO_INDEXED_PRIMITIVES			9L
#define XBIT_BAD_MSAA_SPRITING				10L
#define XBIT_BAD_DEPTH_PEELING				11L
#define XBIT_BAD_NON_POWER_OF_2_TEXTURES	12L
#define XBIT_TEXTURE_SIZE_OFF_BY_ONE		13L
#define XBIT_BAD_GLSL4_SAMPLER_CUBE			14L
#define XBIT_BAD_FLAT_SHADE_MODEL			15L


/* _hoops_ASHGR _hoops_PSHGR */
bool start_device (Display_Context alter * dc);
void stop_device (Display_Context alter * dc);

void get_physical_info (Display_Context alter * dc);
POINTER_SIZED_INT get_outer_window (Display_Context const * _hoops_SAGRH);
void get_current_info (Display_Context alter * dc);

void finish_update (Display_Context const * dc);
void init_update (Display_Context const * dc);

bool _hoops_ISCSP (Display_Context const * dc,
				  int alter * button, int alter * status);

bool _hoops_HSCSP (Display_Context const * dc,
				  int alter * button,
				  int alter * x, int alter * y);


void init_picture (Net_Rendition const &  nr);
void finish_picture (Net_Rendition const &  nr,
				bool swap_buffers);
void _hoops_PCPGR (Net_Rendition const &nr);

void _hoops_SPSGC(Display_Context const * dc);
void free_outer_window (Display_Context const * dc);
void _hoops_ASCSP (Display_Context const	*dc);
void _hoops_RSCSP (Display_Context const * dc);




void _hoops_IAHGC (Display_Context alter * dc);


#ifdef _DEBUG
#	define DEBUG_FLUSH()	glFlush()
#else
#	define DEBUG_FLUSH()	(void)0
#endif

#if 0
typedef struct _hoops_CICAC {
	H3DRenderTarget *pCurrentSurface;	// _hoops_RH _hoops_SCGR _hoops_CSCR/_hoops_SSH _hoops_ISPH
	H3DRenderTarget *pSavedSurface;		// _hoops_RCPGR _hoops_CSCR/_hoops_SSH _hoops_ISPH
	void * _hoops_HPRS;
	Int_Rectangle _hoops_ACCRC;
	struct _hoops_CICAC * next;			// _hoops_CRS _hoops_IS _hoops_SPS _hoops_ISPH - _hoops_RGHP _hoops_RHSP _hoops_IIPI _hoops_IIGR _hoops_SISS
} _hoops_SICRC;
#endif

typedef struct {
    /* _hoops_IGI _hoops_IH _hoops_GCRAC _hoops_IRIGR/_hoops_PGSA _hoops_ASPA _hoops_AGIR */
    void *buffer;
    int size;
    Int_Rectangle _hoops_ACCRC;
    
	H3DRenderTarget *surface;
	H3DRenderTarget *texture;
#ifdef WGL_DRIVER
    /* _hoops_IGI _hoops_IH _hoops_IGHGC _hoops_SRHR _hoops_ISPH _hoops_AGIR */
    HANDLE handle;
    _hoops_SIRAC pbuffer;
    HDC hDC;
    HGLRC hGLRC;
#endif
} _hoops_SICRC;


struct HOGLData;
class H3DRenderTarget;
class _hoops_HGCAC;


#include "ogl2_post.h"


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_CSCP -> _hoops_PIRGC _hoops_PHCSH _hoops_PSCH
*****************************************************************************
*****************************************************************************/
//#_hoops_PPIP _hoops_SICAC

GLenum _hoops_GCCAC(H3DPRIMITIVETYPE type)
{
	switch (type) {
		case H3DPT_POINTLIST:		return GL_POINTS;
		case H3DPT_LINELIST:		return GL_LINES;
		case H3DPT_LINESTRIP:    	return GL_LINE_STRIP;
		case H3DPT_TRIANGLELIST: 	return GL_TRIANGLES;
		case H3DPT_TRIANGLESTRIP:	return GL_TRIANGLE_STRIP;
		case H3DPT_TRIANGLEFAN:  	return GL_TRIANGLE_FAN;
		default:
#ifdef _hoops_RCCAC
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled primitive type mapping.");
#endif
			return GL_POINTS;
	}
}

GLenum _hoops_ACCAC(H3DBLEND type)
{
	switch (type) {
		case H3DBLEND_ZERO:				return GL_ZERO;
		case H3DBLEND_ONE:				return GL_ONE;
		case H3DBLEND_SRCCOLOR:			return GL_SRC_COLOR;
		case H3DBLEND_INVSRCCOLOR:		return GL_ONE_MINUS_SRC_COLOR;
		case H3DBLEND_SRCALPHA:			return GL_SRC_ALPHA;
		case H3DBLEND_INVSRCALPHA:		return GL_ONE_MINUS_SRC_ALPHA;
		case H3DBLEND_DESTALPHA:		return GL_DST_ALPHA;
		case H3DBLEND_INVDESTALPHA:		return GL_ONE_MINUS_DST_ALPHA;
		case H3DBLEND_DESTCOLOR:		return GL_DST_COLOR;
		case H3DBLEND_INVDESTCOLOR:		return GL_ONE_MINUS_DST_COLOR;
		case H3DBLEND_SRCALPHASAT:		return GL_SRC_ALPHA_SATURATE;
		case H3DBLEND_BOTHSRCALPHA:		return GL_CONSTANT_ALPHA;
		case H3DBLEND_BOTHINVSRCALPHA:	return GL_ONE_MINUS_CONSTANT_ALPHA;
		case H3DBLEND_BLENDFACTOR:		return GL_CONSTANT_COLOR;
		case H3DBLEND_INVBLENDFACTOR:	return GL_ONE_MINUS_CONSTANT_COLOR;
		default:
#ifdef _hoops_RCCAC
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled blend type mapping.");
#endif
			return GL_ZERO;
	}
}

GLbitfield _hoops_PCCAC(int flags)
{
	GLbitfield _hoops_PHAAH = 0;
	if (BIT(flags, H3DCLEAR_TARGET))
		_hoops_PHAAH |= GL_COLOR_BUFFER_BIT;
	if (BIT(flags, H3DCLEAR_ZBUFFER))
		_hoops_PHAAH |= GL_DEPTH_BUFFER_BIT;
	if (BIT(flags, H3DCLEAR_STENCIL))
		_hoops_PHAAH |= GL_STENCIL_BUFFER_BIT;
	return _hoops_PHAAH;
}

GLenum _hoops_HCCAC(H3DCULL type)
{
	switch (type) {
		case H3DCULL_NONE:		return GL_NONE;
		case H3DCULL_CW:		return GL_BACK;
		case H3DCULL_CCW:		return GL_FRONT;
		default:
#ifdef _hoops_RCCAC
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled cull type mapping.");
#endif
			return GL_NONE;
	}
}


GLenum _hoops_ICCAC(H3DSHADEMODE type)
{
	switch (type) {
		case H3DSHADE_FLAT:		return GL_FLAT;
		case H3DSHADE_GOURAUD:	return GL_SMOOTH;
		case H3DSHADE_PHONG:	return GL_SMOOTH;
		default:
#ifdef _hoops_RCCAC
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled shade mode mapping.");
#endif
			return GL_SMOOTH;
	}
}


GLint _hoops_ARCAC(H3DTEXTUREADDRESS type)
{
	switch (type) {
		case H3DTADDRESS_WRAP:			return GL_REPEAT;
		case H3DTADDRESS_MIRROR:		return GL_MIRRORED_REPEAT;
		case H3DTADDRESS_CLAMP:			return GL_CLAMP_TO_EDGE;
		case H3DTADDRESS_BORDER:		return GL_CLAMP_TO_BORDER;
		case H3DTADDRESS_MIRRORONCE:	return GL_MIRROR_CLAMP_EXT;
		default:
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled shade mode mapping.");
			return GL_REPEAT;
	}
}

GLint _hoops_SPIAC(H3DTEXTUREFILTERTYPE type)
{
	switch (type) {
		case H3DTEXF_NONE:				return GL_NEAREST;
		case H3DTEXF_POINT:				return GL_NEAREST;
		case H3DTEXF_LINEAR:			return GL_LINEAR;
		case H3DTEXF_ANISOTROPIC:		return GL_LINEAR_MIPMAP_NEAREST;
		case H3DTEXF_PYRAMIDALQUAD:		return GL_NEAREST;
		case H3DTEXF_GAUSSIANQUAD:		return GL_NEAREST;
		default:
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled shade mode mapping.");
			return GL_NEAREST;
	}
}

GLenum _hoops_CCCAC(H3DCMPFUNC type)
{
	switch (type) {
		case H3DCMP_NEVER :			return GL_NEVER;
		case H3DCMP_LESS :          return GL_LESS;
		case H3DCMP_EQUAL :         return GL_EQUAL;
		case H3DCMP_LESSEQUAL :     return GL_LEQUAL;
		case H3DCMP_GREATER :       return GL_GREATER;
		case H3DCMP_NOTEQUAL :      return GL_NOTEQUAL;
		case H3DCMP_GREATEREQUAL :  return GL_GEQUAL;
		case H3DCMP_ALWAYS :        return GL_ALWAYS;
		default:
#ifdef _hoops_RCCAC
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled comparison function mapping.");
#endif
			return GL_ALWAYS;
	}
}

GLenum _hoops_SCCAC(H3DSTENCILOP type)
{
	switch (type) {
		case H3DSTENCILOP_KEEP :		return GL_KEEP;
		case H3DSTENCILOP_ZERO :		return GL_ZERO;
		case H3DSTENCILOP_REPLACE :		return GL_REPLACE;
		case H3DSTENCILOP_INCRSAT :		return GL_INCR;
		case H3DSTENCILOP_DECRSAT :		return GL_DECR;
		case H3DSTENCILOP_INVERT :		return GL_INVERT;
		case H3DSTENCILOP_INCR :		return GL_INCR;
		case H3DSTENCILOP_DECR :		return GL_DECR;
		default:
#ifdef _hoops_RCCAC
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled stencil op mapping.");
#endif
			return GL_KEEP;
	}
}

GLenum _hoops_GSCAC(H3DFACE face)
{
	switch (face) {
		case H3DFACE_POSITIVE_X :		return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
		case H3DFACE_NEGATIVE_X : 		return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
		case H3DFACE_POSITIVE_Y : 		return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
		case H3DFACE_NEGATIVE_Y : 		return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
		case H3DFACE_POSITIVE_Z : 		return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
		case H3DFACE_NEGATIVE_Z : 		return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
		default:
#ifdef _hoops_RCCAC
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled texture cube face mapping.");
#endif
			return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	}
}

GLsizei _hoops_RSCAC(H3DPRIMITIVETYPE type, int _hoops_PGHS)
{
	switch (type) {
		case H3DPT_POINTLIST:		return _hoops_PGHS;
		case H3DPT_LINELIST:		return _hoops_PGHS * 2;
		case H3DPT_LINESTRIP:    	return _hoops_PGHS + 2;
		case H3DPT_TRIANGLELIST: 	return _hoops_PGHS * 3;
		case H3DPT_TRIANGLESTRIP:	return _hoops_PGHS + 2;
		case H3DPT_TRIANGLEFAN:  	return _hoops_PGHS + 2;
		default:
#ifdef _hoops_RCCAC
			HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
				"Internal error: Unhandled primitive type.");
#endif
			return 0;
	}
}

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_AIAP/_hoops_HRCR _hoops_ASCAC
*****************************************************************************
*****************************************************************************/
#define FORCE_ARRAY_BUFFER(_hoops_CSRGR,buffer) _hoops_GHIA(\
	_hoops_CSRGR->_hoops_PRCAC._hoops_PSCAC = buffer; \
	glBindBuffer(GL_ARRAY_BUFFER, buffer); \
)

#define ENSURE_ARRAY_BUFFER(_hoops_CSRGR,buffer) _hoops_GHIA(\
	if (buffer != _hoops_CSRGR->_hoops_PRCAC._hoops_PSCAC) \
		FORCE_ARRAY_BUFFER(_hoops_CSRGR,buffer); \
)

#define FORCE_ELEMENT_BUFFER(_hoops_CSRGR,buffer) _hoops_GHIA(\
	_hoops_CSRGR->_hoops_PRCAC._hoops_HSCAC = buffer; \
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer); \
)

#define ENSURE_ELEMENT_BUFFER(_hoops_CSRGR,buffer) _hoops_GHIA(\
	if (buffer != _hoops_CSRGR->_hoops_PRCAC._hoops_HSCAC) \
		FORCE_ELEMENT_BUFFER(_hoops_CSRGR,buffer); \
)

#define _hoops_ISCAC(_hoops_CSRGR,_hoops_RHIA) _hoops_GHIA(\
	_hoops_CSRGR->_hoops_PRCAC._hoops_CSCAC = _hoops_RHIA; \
	glClientActiveTexture(GL_TEXTURE0 + _hoops_RHIA); \
)

#define _hoops_SSCAC(_hoops_CSRGR,_hoops_RHIA) _hoops_GHIA(\
	if (_hoops_RHIA != _hoops_CSRGR->_hoops_PRCAC._hoops_CSCAC) \
		_hoops_ISCAC(_hoops_CSRGR,_hoops_RHIA); \
)

void _hoops_IPRRC(H3DData *h3ddata, int _hoops_RHIA);
#define _hoops_IHRRC(_hoops_CSRGR,_hoops_RHIA) _hoops_GHIA(\
	if ((int) _hoops_RHIA != ((HOGLData*)_hoops_CSRGR)->_hoops_PRCAC._hoops_HRCAC) \
		_hoops_IPRRC(_hoops_CSRGR,_hoops_RHIA); \
)

#define _hoops_GGSAC(_hoops_CSRGR,_hoops_ICAGA,size,type,_hoops_RGSAC,stride,pointer) _hoops_GHIA( \
	if (_hoops_ICAGA >= 0) { \
		glVertexAttribPointer(_hoops_ICAGA,size,type,_hoops_RGSAC,stride,pointer); \
		glEnableVertexAttribArray(_hoops_ICAGA); \
		(_hoops_CSRGR)->_hoops_PRCAC._hoops_AGSAC[_hoops_ICAGA] = true; \
	} \
)
#define _hoops_PGSAC(_hoops_CSRGR) SET_MEMORY((_hoops_CSRGR)->_hoops_PRCAC._hoops_AGSAC, sizeof((_hoops_CSRGR)->_hoops_PRCAC._hoops_AGSAC), false); 
#define _hoops_HGSAC(_hoops_CSRGR) _hoops_GHIA( \
	for (int _i_ = 0; _i_ < sizeof((_hoops_CSRGR)->_hoops_PRCAC._hoops_AGSAC)/sizeof((_hoops_CSRGR)->_hoops_PRCAC._hoops_AGSAC[0]); _i_++) \
		if ((_hoops_CSRGR)->_hoops_PRCAC._hoops_AGSAC[_i_] == false) \
			glDisableVertexAttribArray(_i_); \
)


#define _hoops_CRPAH(_hoops_CSRGR, _hoops_GRRA, mode)	_hoops_GHIA(\
	_hoops_IHRRC (_hoops_CSRGR, _hoops_GRRA); \
	((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_GRRA])->_hoops_PGPRR = mode; \
	GLenum _hoops_SRCRP = _hoops_CSRGR->_hoops_CSC->_hoops_CAGRR[_hoops_GRRA]; \
	glTexParameteri (_hoops_SRCRP, GL_TEXTURE_WRAP_S, _hoops_ARCAC(mode)); \
)

#define ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, _hoops_GRRA, mode)	_hoops_GHIA(\
	if (((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_GRRA])->_hoops_PGPRR != mode) \
		_hoops_CRPAH(_hoops_CSRGR, _hoops_GRRA, mode); \
)

#define _hoops_SRPAH(_hoops_CSRGR, _hoops_GRRA, mode)	_hoops_GHIA(\
	_hoops_IHRRC (_hoops_CSRGR, _hoops_GRRA); \
	((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_GRRA])->_hoops_HGPRR = mode; \
	GLenum _hoops_SRCRP = _hoops_CSRGR->_hoops_CSC->_hoops_CAGRR[_hoops_GRRA]; \
	glTexParameteri (_hoops_SRCRP, GL_TEXTURE_WRAP_T, _hoops_ARCAC(mode)); \
)

#define _hoops_SAIRH(_hoops_CSRGR, _hoops_GRRA, mode)	_hoops_GHIA(\
	if (((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_GRRA])->_hoops_HGPRR != mode) \
		_hoops_SRPAH(_hoops_CSRGR, _hoops_GRRA, mode); \
)


#define _hoops_AAPAH(_hoops_CSRGR, _hoops_RHIA, mode) _hoops_GHIA(\
	_hoops_IHRRC (_hoops_CSRGR, _hoops_RHIA); \
	((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_RHIA])->_hoops_AGPRR = mode; \
	GLenum _hoops_SRCRP = _hoops_CSRGR->_hoops_CSC->_hoops_CAGRR[_hoops_RHIA]; \
	if (((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_RHIA])->_hoops_GGPRR == H3DTEXF_POINT)\
		switch(mode) {\
			case H3DTEXF_NONE:\
				glTexParameteri (_hoops_SRCRP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); \
				break;\
			case H3DTEXF_POINT:\
				glTexParameteri (_hoops_SRCRP, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST); \
				break;\
			case H3DTEXF_LINEAR:\
				glTexParameteri (_hoops_SRCRP, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); \
				break;\
		}\
	else if (((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_RHIA])->_hoops_GGPRR == H3DTEXF_LINEAR)\
		switch(mode) {\
			case H3DTEXF_NONE:\
				glTexParameteri (_hoops_SRCRP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); \
				break;\
			case H3DTEXF_POINT:\
				glTexParameteri (_hoops_SRCRP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); \
				break;\
			case H3DTEXF_LINEAR:\
				glTexParameteri (_hoops_SRCRP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); \
				break;\
		}\
)

#define _hoops_APIRH(_hoops_CSRGR, _hoops_RHIA, mode) _hoops_GHIA(\
	if (((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_RHIA])->_hoops_AGPRR != mode) \
		_hoops_AAPAH(_hoops_CSRGR, _hoops_RHIA, mode); \
)

#define _hoops_GAPAH(_hoops_CSRGR, _hoops_RHIA, mode) _hoops_GHIA(\
	_hoops_IHRRC (_hoops_CSRGR, _hoops_RHIA); \
	((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_RHIA])->_hoops_GGPRR = mode; \
	_hoops_AAPAH(_hoops_CSRGR, _hoops_RHIA, ((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_RHIA])->_hoops_AGPRR); \
)

#define _hoops_GPIRH(_hoops_CSRGR, _hoops_RHIA, mode) _hoops_GHIA(\
	if (((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_RHIA])->_hoops_GGPRR != mode) \
		_hoops_GAPAH(_hoops_CSRGR, _hoops_RHIA, mode); \
)

#define _hoops_RAPAH(_hoops_CSRGR, _hoops_RHIA, mode) _hoops_GHIA(\
	_hoops_IHRRC (_hoops_CSRGR, _hoops_RHIA); \
	((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_RHIA])->_hoops_RGPRR = mode; \
	GLenum _hoops_SRCRP = _hoops_CSRGR->_hoops_CSC->_hoops_CAGRR[_hoops_RHIA]; \
	glTexParameteri (_hoops_SRCRP, GL_TEXTURE_MAG_FILTER, _hoops_SPIAC(mode)); \
)

#define _hoops_RPIRH(_hoops_CSRGR, _hoops_RHIA, mode) _hoops_GHIA(\
	if (((_hoops_HGCAC *) _hoops_CSRGR->_hoops_CSC->texture[_hoops_RHIA])->_hoops_RGPRR != mode) \
		_hoops_RAPAH(_hoops_CSRGR, _hoops_RHIA, mode); \
)


#define _hoops_IHIAC(_hoops_CSRGR, _hoops_IGSAC) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_PRCAC.fbo != _hoops_IGSAC) { \
		_hoops_CSRGR->_hoops_PRCAC.fbo = _hoops_IGSAC; \
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _hoops_IGSAC); \
	}\
)

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_CGSAC
*****************************************************************************
*****************************************************************************/
class HOGLFrameBufferObject;

struct HOGLData : H3DData
{
	GLEWContext *glewcontext;

#ifdef GLX_OPENGL2_DRIVER
    Display 			*display;
    X_Window 			window;
    GLXContext 			context;
    XVisualInfo 		*_hoops_CAAAC;
    Screen 				*screen;
    Visual 				*visual;
	GLXPbuffer			pbuffer;  /* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCAC _hoops_GAR _hoops_IRS _hoops_CGSRC _hoops_CSCR */

    /* _hoops_SGH _hoops_IS _hoops_SAAAC _hoops_RH _hoops_GPAAC _hoops_RHPP */
    _hoops_APARR _hoops_RPAAC;

    struct {
		X_Window window;
		GLXContext context;
		Colormap colormap;
		int _hoops_HIHGC;
		int _hoops_AHISI;
		long width;
		long height;
		int _hoops_SIHGC;
		Driver_Color alter *colors;
    } overlay;

#endif

#ifdef AGL_DRIVER

	WindowRef window;
	AGLPbuffer pbuffer;  /* _hoops_PCGR _hoops_IH "_hoops_RPPS" _hoops_CGPR _hoops_ASCA _hoops_IS _hoops_SRGAC */

	/* _hoops_SISR,_hoops_HAPC,_hoops_SSCHA,_hoops_GGHR _hoops_CRIPR _hoops_PSCR _hoops_PSSPR*/
	int * _hoops_CSPRP;
	int _hoops_IPAAC[8];

	GDHandle device;
	GDHandle info_device;

	AGLContext curr_AGLContext;
	AGLContext prev_AGLContext;
	GrafPtr _hoops_CPAAC;
	GrafPtr prev_GrafPtr;

	EventHandlerUPP window_EventHandlerUPP; 
	EventHandlerRef event_handler_ref;

	int yfudge;
	int _hoops_CCGRR;

	float _hoops_ISIH;

	int _hoops_SCGRR;
	int mouse_y;

#define      _hoops_RRRRR      0x01
#define      _hoops_PRRRR    0x04
#define      _hoops_ARRRR     0x02

	int _hoops_HRRRR;
	bool _hoops_IRRRR;

	UInt32 key_state;

	bool pending_resize;

#endif

#ifdef WINDOWS_SYSTEM
	HGLRC hGLRC;
	HDC   _hoops_APAAC;
	HGLRC _hoops_PPAAC;
	HGLRC overlayGLRC;

	WGLEWContext *wglewcontext;

	/*_hoops_IH _hoops_ICCGR _hoops_RSAIP*/
	bool _hoops_APSRC;
    HDC _hoops_HIISI; 
    HBITMAP hBitmap;
    HBITMAP old_hBitmap;
#endif

	int window_width;
    int window_height;


	int _hoops_RPICI;

	bool _hoops_CRHGC;

	int accumulation_bits;

	bool _hoops_PPHGC;
	GLint _hoops_APHGC;

	bool _hoops_GAGRR;

	bool _hoops_PHHGC;
	int _hoops_APCAC;

	int _hoops_AHHGC;
	float _hoops_GSSGC;

	int glsl_version;


	struct {
		bool _hoops_IGPAC;
		bool _hoops_CGPAC;
		bool _hoops_SGPAC[H3D_MAX_TEXTURES];
		bool _hoops_HGPAC;

		GLuint fbo;
		
		GLuint _hoops_PSCAC;
		GLuint _hoops_HSCAC;
		int _hoops_HRCAC;
		int _hoops_CSCAC;

		bool _hoops_AGSAC[12];
	} _hoops_PRCAC;

	H3DTexture *_hoops_IPCAC;

	HOGLFrameBufferObject *fbo;
	HOGLFrameBufferObject *_hoops_AGIAC;		//_hoops_PCCP _hoops_GIRPA _hoops_HHSPR _hoops_ARPP _hoops_SGSAC _hoops_IS _hoops_ISSC _hoops_SRHR
	HOGLFrameBufferObject *_hoops_PGIAC;		//_hoops_PCCP _hoops_GIRPA _hoops_HHSPR _hoops_ARPP _hoops_SGSAC _hoops_IS _hoops_ISSC _hoops_SRHR
	HOGLFrameBufferObject *_hoops_PPCAC;

	H3DRenderTarget *_hoops_CACAC;

	//_hoops_IAGIP
	_hoops_SICRC * _hoops_PSARH;		
	_hoops_SICRC * _hoops_GRSAC;	
	float *_hoops_RRSAC;		// _hoops_GIRPA _hoops_CASPR _hoops_IH _hoops_ARSAC
	int _hoops_PRSAC;

	GLuint _hoops_SISGC;
	GLuint _hoops_GCSGC;
	GLuint _hoops_SSCRC;
	GLuint _hoops_GGSRC;

	bool _hoops_CCRGC;

	// _hoops_ASC _hoops_PGCR _hoops_AI _hoops_CHR _hoops_IGI _hoops_CCA _hoops_HRSAC _hoops_IH _hoops_IRSAC
	GLuint _hoops_SGIAC;
	GLuint _hoops_PAIAC;

	// _hoops_IPSP _hoops_CI
	GLuint _hoops_CRSAC;
};

#define OGLD(dc) ((HOGLData alter *)((dc)->_hoops_RIHGR))
#define OGLNRD(nr) (OGLD((nr)->_hoops_SRA))

#ifdef GLX_OPENGL2_DRIVER
#  define X11D(dc) ((X11Data alter *)((dc)->data))
#  define X11NRD(nr) (X11D(nr->_hoops_SRA))
#endif


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_AIIAC _hoops_CSHGR
*****************************************************************************
*****************************************************************************/
#define glUniformfv(_hoops_ICAGA, _hoops_GPIGR, data) _hoops_GHIA (\
	switch (_hoops_GPIGR) { \
		case 1: glUniform1fv (_hoops_ICAGA, 1, (const GLfloat *) data); break; \
		case 2: glUniform2fv (_hoops_ICAGA, 1, (const GLfloat *) data); break; \
		case 3: glUniform3fv (_hoops_ICAGA, 1, (const GLfloat *) data); break; \
		case 4: glUniform4fv (_hoops_ICAGA, 1, (const GLfloat *) data); break; \
	} \
)

#define glUniformiv(_hoops_ICAGA, _hoops_GPIGR, data) _hoops_GHIA (\
	switch (_hoops_GPIGR) { \
		case 1: glUniform1iv (_hoops_ICAGA, 1, (const GLint *) data); break; \
		case 2: glUniform2iv (_hoops_ICAGA, 1, (const GLint *) data); break; \
		case 3: glUniform3iv (_hoops_ICAGA, 1, (const GLint *) data); break; \
		case 4: glUniform4iv (_hoops_ICAGA, 1, (const GLint *) data); break; \
	} \
)


class _hoops_PIIAC : public H3DShader
{
protected:
	char const * _hoops_CAHR(){return "glsl";};

public:
	GLint _hoops_HIIAC;
	GLuint _hoops_AGHRH;
	GLuint _hoops_PGHRH;

	GLint _hoops_SRSAC;
	GLint _hoops_GASAC;
	GLint _hoops_RASAC;
	GLint _hoops_AASAC;
	GLint _hoops_PASAC;
	GLint _hoops_HASAC[8];

public:
	_hoops_PIIAC (const H3DShaderID& id);
	~_hoops_PIIAC ();

	bool Create(H3DData *h3ddata, const char *_hoops_IASRR = null);
	bool _hoops_HHIH();

	void _hoops_RAPRR(H3DTexture *texture, H3DData *h3ddata);
	void _hoops_GGIR (bool _hoops_AIAAR = false);
	GLuint _hoops_IASAC() {return _hoops_HIIAC;};

	void _hoops_RCAAR(H3D_Constant_Table table, int _hoops_HGHAH, int data)
	{
		UNREFERENCED (table);
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		UNREFERENCED(_hoops_CSRGR);

		if (_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] && EQUAL_MEMORY(_hoops_ISS->_hoops_CCRRR[_hoops_HGHAH], sizeof(int), &data))
			return;
		COPY_MEMORY(&data, sizeof(int), _hoops_ISS->_hoops_CCRRR[_hoops_HGHAH]);
		_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] = true;

		GLint glhandle = (GLint) _hoops_CSC[_hoops_HGHAH];
		glUniform1i (glhandle, data);
	}

	void _hoops_ACAAR(H3D_Constant_Table table, int _hoops_HGHAH, float data)
	{
		UNREFERENCED (table);
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		UNREFERENCED(_hoops_CSRGR);

		if (_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] && data == _hoops_ISS->_hoops_CCRRR[_hoops_HGHAH][0])
			return;
		_hoops_ISS->_hoops_CCRRR[_hoops_HGHAH][0] = data;
		_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] = true;

		GLint glhandle = (GLint) _hoops_CSC[_hoops_HGHAH];
		glUniform1f (glhandle, data);
	}

	void _hoops_PCAAR(H3D_Constant_Table table, int _hoops_HGHAH, void const *data, int _hoops_HCAAR, int _hoops_GPIGR = 1)
	{
		UNREFERENCED (table);
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		UNREFERENCED(_hoops_CSRGR);

		int _hoops_IGHAH = _hoops_GPIGR;

		if (_hoops_HCAAR == H3D_Vector)
			_hoops_IGHAH = _hoops_GPIGR * 4;

		if (_hoops_IGHAH <= 16) {
			if (_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] && EQUAL_MEMORY(_hoops_ISS->_hoops_CCRRR[_hoops_HGHAH], _hoops_IGHAH * sizeof(float), (float *) data))
				return;
			COPY_MEMORY(data, _hoops_IGHAH * sizeof(float), _hoops_ISS->_hoops_CCRRR[_hoops_HGHAH]);
			_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] = true;
		}

		GLint glhandle = (GLint) _hoops_CSC[_hoops_HGHAH];
		GLfloat *value = (GLfloat *) data;

		switch (_hoops_HCAAR) {
			case H3D_Integer:
				glUniformiv (glhandle, _hoops_GPIGR, (GLint *) data);
				break;
			case H3D_Float:
				glUniformfv (glhandle, _hoops_GPIGR, value);
				break;
			case H3D_Matrix:

				switch (_hoops_GPIGR) {
					case 4:
						glUniformMatrix2fv (glhandle, 1, false, value);
						break;
					case 9:
						glUniformMatrix3fv (glhandle, 1, false, value);
						break;
					case 16:
						glUniformMatrix4fv (glhandle, 1, false, value);
						break;
					default:
						ASSERT(0);		//6,8,12 _hoops_IAGH: _hoops_HAR _hoops_APP _hoops_GAPR!
						break;
				}
				break;
			default:
				ASSERT(0);
				break;
		}
	}

	void _hoops_ICAAR(H3D_Constant_Table table, int _hoops_HGHAH, float *data, int width) {
		_hoops_CCAAR(table, _hoops_HGHAH, data, 1, width);
	}
	void _hoops_CCAAR(H3D_Constant_Table table, int _hoops_HGHAH, float *data, int _hoops_SIIRR, int width) {
		UNREFERENCED (table);
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		UNREFERENCED(_hoops_CSRGR);

		int _hoops_IGHAH = _hoops_SIIRR * width;
		if (_hoops_IGHAH <= 16) {
			if (_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] && EQUAL_MEMORY(_hoops_ISS->_hoops_CCRRR[_hoops_HGHAH], _hoops_IGHAH * sizeof(float), (float *) data))
				return;
			COPY_MEMORY(data, _hoops_IGHAH * sizeof(float), _hoops_ISS->_hoops_CCRRR[_hoops_HGHAH]);
			_hoops_ISS->_hoops_SCRRR[_hoops_HGHAH] = true;
		}

		GLint glhandle = (GLint) _hoops_CSC[_hoops_HGHAH];

		switch(width) {
			case 1: 
				glUniform1fv (glhandle, _hoops_SIIRR, data);
				break;
			case 2: 
				glUniform2fv (glhandle, _hoops_SIIRR, data);
				break;
			case 3: 
				glUniform3fv (glhandle, _hoops_SIIRR, data);
				break;
			case 4: 
				glUniform4fv (glhandle, _hoops_SIIRR, data);
				break;
		}
	}

	H3D_Shader_Handle GetConstantByName(H3D_Constant_Table table, char const * _hoops_SCAAR, char const * _hoops_GSAAR)
	{
		UNREFERENCED(table);
		char buf[1024];
		H3D_Shader_Handle result = -2;
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		UNREFERENCED(_hoops_CSRGR);

		if (_hoops_SCAAR) {
			sprintf(buf, "%s.%s", _hoops_SCAAR, _hoops_GSAAR);
			result = (H3D_Shader_Handle) glGetUniformLocation (_hoops_HIIAC, buf);
		}
		else
			result = (H3D_Shader_Handle) glGetUniformLocation (_hoops_HIIAC, _hoops_GSAAR);

#ifdef _DEBUG
		if (result == -1) {
			char error[1024];
			char const *handle = (_hoops_SCAAR) ? buf : _hoops_GSAAR;

			sprintf(error, "Shader constant \"%s\" is inactive or nonexistent.\n", handle);

			// _hoops_SRHRH _hoops_CHR _hoops_GGR _hoops_GAHRH _hoops_RPCC _hoops_IH _hoops_RAHRH _hoops_AAHRH - _hoops_HSPAA _hoops_IS _hoops_HISRA _hoops_GGSR
			OutputDebugString("OpenGL2 reports errors:\n");
			OutputDebugStringA(error);
#if 0
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, 
				Sprintf_S (null, "error reported by opengl:\n%S", error));
#endif
		}
#endif // _hoops_PAHRH

		if (result == -1)
			result = _hoops_SSRAR;
		//_hoops_AGHR(_hoops_GHPP != _hoops_CASAC);
		return result;
	}

	void _hoops_PCIAC()
	{
		HOGLData *_hoops_CSRGR = (HOGLData*) _hoops_ISS;
		_hoops_SRSAC = glGetAttribLocation(_hoops_HIIAC, "in_position");
		_hoops_GASAC = glGetAttribLocation(_hoops_HIIAC, "in_normal");
		_hoops_RASAC = glGetAttribLocation(_hoops_HIIAC, "in_color");
		_hoops_AASAC = glGetAttribLocation(_hoops_HIIAC, "in_secondary_color");
		_hoops_HASAC[0] = glGetAttribLocation(_hoops_HIIAC, "in_texcoord0");
		_hoops_HASAC[1] = glGetAttribLocation(_hoops_HIIAC, "in_texcoord1");
		_hoops_HASAC[2] = glGetAttribLocation(_hoops_HIIAC, "in_texcoord2");
		_hoops_HASAC[3] = glGetAttribLocation(_hoops_HIIAC, "in_texcoord3");
		_hoops_HASAC[4] = glGetAttribLocation(_hoops_HIIAC, "in_texcoord4");
		_hoops_HASAC[5] = glGetAttribLocation(_hoops_HIIAC, "in_texcoord5");
		_hoops_HASAC[6] = glGetAttribLocation(_hoops_HIIAC, "in_texcoord6");
		_hoops_HASAC[7] = glGetAttribLocation(_hoops_HIIAC, "in_texcoord7");
		_hoops_PASAC = glGetAttribLocation(_hoops_HIIAC, "in_fogcoord");
	}

	char alter *_hoops_SCIAC (
		const char *filename,
		const char *_hoops_ICPR,
		char alter *ptr,
		char const *end,
		const char *glsl_version,
		_hoops_AHGR type);
};


/*****************************************************************************
*****************************************************************************
				_hoops_GR: _hoops_SASAC _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
// _hoops_RGR _hoops_HRGR _hoops_RH _hoops_SRHR _hoops_CARA _hoops_PIH _hoops_HRPR _hoops_PGAP _hoops_RIAH _hoops_RH _hoops_GPHA _hoops_PPR _hoops_CIHA _hoops_PSCA
// _hoops_IHPAH _hoops_PCCP _hoops_RSIR _hoops_AASGR _hoops_PAR _hoops_CSHS
class HOGLIndexedBufferObject : public H3DIndexedBufferObject
{
private:
	HOGLData *_hoops_PHIAC;

	GLuint m_pVertexBuffer;
	GLuint _hoops_SSPAH;
	int _hoops_HPRAC;
	int colors_offset;
	int _hoops_GPSAC;
	
	H3DPRIMITIVETYPE _hoops_RPSAC;
	unsigned int _hoops_APSAC;
	unsigned int _hoops_PPSAC;

	bool _hoops_HPSAC;
	bool _hoops_IPSAC;

	int _hoops_CPSAC;

public:
	HOGLIndexedBufferObject() 
	{
		_hoops_HPSAC = false;
		_hoops_IPSAC = false;
	}
	~HOGLIndexedBufferObject()
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		HOOPS_WORLD->display_list_vram_usage -= (_hoops_RAIRR * _hoops_GSHRR);
		HOOPS_WORLD->display_list_vram_usage -= _hoops_CPSAC;

		glDeleteBuffers(1, &_hoops_SSPAH);
		glDeleteBuffers(1, &m_pVertexBuffer);

		FORCE_ELEMENT_BUFFER(_hoops_CSRGR, 0);
		FORCE_ARRAY_BUFFER(_hoops_CSRGR, 0);
	}

	//_hoops_PIGS _hoops_ARR _hoops_RIR _hoops_AASGR
	bool CreateVertexBuffer (H3DData *h3ddata,
								unsigned int point_count, 
								H3DVertexFormat VF)
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC = (HOGLData *) h3ddata;
		UNREFERENCED(_hoops_CSRGR);

		_hoops_GSHRR		= VF._hoops_HGHS();
		_hoops_AAIRR			= VF;
		_hoops_RAIRR	= point_count;

		glGenBuffers(1, &m_pVertexBuffer);
		ENSURE_ARRAY_BUFFER(_hoops_CSRGR, m_pVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, _hoops_GSHRR * point_count, NULL, GL_STATIC_DRAW);
		HOOPS_WORLD->display_list_vram_usage += (_hoops_RAIRR * _hoops_GSHRR);
		return true;
	}

	//_hoops_PIGS _hoops_GARI->_hoops_IIRGR _hoops_IACH _hoops_RIR _hoops_AASGR
	bool CreateIndexBuffer (H3DData *h3ddata,
							   H3DPRIMITIVETYPE type, 
							   unsigned int length,
							   unsigned int count)
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC = (HOGLData *) h3ddata;
		UNREFERENCED(_hoops_CSRGR);

		if (_hoops_RAIRR <= 0x0000ffff && count <= 0x0000ffff)
			_hoops_GSPP = H3DFMT_INDEX16;
		else
			_hoops_GSPP = H3DFMT_INDEX32;

		_hoops_RPSAC = type;
		_hoops_CPSAC = length * ((_hoops_GSPP == H3DFMT_INDEX16) ? sizeof(short) : sizeof(int));
		_hoops_APSAC = length;
		_hoops_PPSAC = count;

		glGenBuffers(1, &_hoops_SSPAH);
		ENSURE_ELEMENT_BUFFER(_hoops_CSRGR, _hoops_SSPAH);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _hoops_CPSAC, NULL, GL_STATIC_DRAW);

		HOOPS_WORLD->display_list_vram_usage += _hoops_CPSAC;
		_hoops_HAIRR &= true;
		return _hoops_HAIRR;
	}

	bool LockIndexBuffer(unsigned int _hoops_SAIRR, unsigned int _hoops_GPIRR, H3DIndexBuffer *_hoops_RAHC, unsigned int Flags)
	{
		UNREFERENCED(_hoops_SAIRR);
		UNREFERENCED(_hoops_GPIRR);
		UNREFERENCED(Flags);

		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		short *_hoops_PAHC = null;

		ASSERT(_hoops_HPSAC == false);
		_hoops_HPSAC = true;

		// _hoops_HRAH _hoops_RH _hoops_GPHA _hoops_SRHR.
		ENSURE_ELEMENT_BUFFER(_hoops_CSRGR, _hoops_SSPAH);
		_hoops_PAHC = (short *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		ASSERT (_hoops_PAHC != null);
		_hoops_RAHC->_hoops_IRA(_hoops_GSPP, _hoops_PAHC);

		_hoops_HAIRR &= (_hoops_PAHC != null);
		return _hoops_HAIRR;
	}

	bool LockVertexBuffer(unsigned int _hoops_SAIRR, unsigned int _hoops_GPIRR, H3DVertexBuffer *_hoops_PAIH, unsigned int Flags)
	{
		UNREFERENCED(_hoops_SAIRR);
		UNREFERENCED(Flags);

		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		float *_hoops_GIIGR = null;

		ASSERT(_hoops_IPSAC == false);
		_hoops_IPSAC = true;

		if (_hoops_GPIRR == 0)
			_hoops_GPIRR = _hoops_GSHRR * _hoops_RAIRR;

		// _hoops_HRAH _hoops_RH _hoops_GPHA _hoops_SRHR.
		ENSURE_ARRAY_BUFFER(_hoops_CSRGR, m_pVertexBuffer);
		_hoops_GIIGR = (float *)glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);

		_hoops_PAIH->_hoops_IRA(_hoops_GIIGR, &_hoops_AAIRR);
		_hoops_HPRAC = _hoops_PAIH->_hoops_GPCGR() * sizeof(float);
		colors_offset = _hoops_PAIH->_hoops_RPCGR() * sizeof(float);
		_hoops_GPSAC = _hoops_PAIH->_hoops_APCGR() * sizeof(float);

		return (_hoops_GIIGR != null);
	}

	void UnlockIndexBuffer()
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		//_hoops_SPSAC _hoops_GHPP = _hoops_GHSAC(_hoops_RHSAC);
		glUnmapBufferARB(GL_ELEMENT_ARRAY_BUFFER);

		ASSERT(_hoops_HPSAC == true);
		_hoops_HPSAC = false;

		return;
	}

	void UnlockVertexBuffer()
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		//_hoops_SPSAC _hoops_GHPP = _hoops_GHSAC(_hoops_AHSAC);
		glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);

		ASSERT(_hoops_IPSAC == true);
		_hoops_IPSAC = false;
		return;
	}

#define _hoops_PHSAC(i) ((char *)NULL + (i))
	void _hoops_HHSAC()
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC;
		_hoops_PIIAC *_hoops_RSR = (_hoops_PIIAC *) _hoops_CSRGR->_hoops_CSC->_hoops_AGSA;
		H3DVertexFormat *_hoops_PPCP = &_hoops_AAIRR;

		GLint _hoops_IHSAC;
		GLint _hoops_CHSAC;
		GLint _hoops_SHSAC;
		GLint _hoops_GISAC;
		GLint _hoops_RISAC[8];
		
		GLint program;
		glGetIntegerv(GL_CURRENT_PROGRAM, &program);
		if (_hoops_RSR && program == _hoops_RSR->_hoops_HIIAC) {
			_hoops_IHSAC = _hoops_RSR->_hoops_SRSAC;
			_hoops_GISAC = _hoops_RSR->_hoops_GASAC;
			_hoops_CHSAC = _hoops_RSR->_hoops_RASAC;
			_hoops_SHSAC = _hoops_RSR->_hoops_AASAC;
			_hoops_RISAC[0] = _hoops_RSR->_hoops_HASAC[0];
			_hoops_RISAC[1] = _hoops_RSR->_hoops_HASAC[1];
			_hoops_RISAC[2] = _hoops_RSR->_hoops_HASAC[2];
			_hoops_RISAC[3] = _hoops_RSR->_hoops_HASAC[3];
			_hoops_RISAC[4] = _hoops_RSR->_hoops_HASAC[4];
			_hoops_RISAC[5] = _hoops_RSR->_hoops_HASAC[5];
			_hoops_RISAC[6] = _hoops_RSR->_hoops_HASAC[6];
			_hoops_RISAC[7] = _hoops_RSR->_hoops_HASAC[7];
		}
		else {
			_hoops_IHSAC = glGetAttribLocation(program, "in_position");
			_hoops_GISAC = glGetAttribLocation(program, "in_normal");
			_hoops_CHSAC = glGetAttribLocation(program, "in_color");
			_hoops_SHSAC = glGetAttribLocation(program, "in_secondary_color");
			_hoops_RISAC[0] = glGetAttribLocation(program, "in_texcoord0");
			_hoops_RISAC[1] = glGetAttribLocation(program, "in_texcoord1");
			_hoops_RISAC[2] = glGetAttribLocation(program, "in_texcoord2");
			_hoops_RISAC[3] = glGetAttribLocation(program, "in_texcoord3");
			_hoops_RISAC[4] = glGetAttribLocation(program, "in_texcoord4");
			_hoops_RISAC[5] = glGetAttribLocation(program, "in_texcoord5");
			_hoops_RISAC[6] = glGetAttribLocation(program, "in_texcoord6");
			_hoops_RISAC[7] = glGetAttribLocation(program, "in_texcoord7");
		}


		int stride = _hoops_PPCP->_hoops_HGHS();
		int _hoops_RICP = 0;
		int _hoops_AISAC = _hoops_GPSAC;
		_hoops_PGSAC(_hoops_CSRGR); 
		{
			_hoops_GGSAC(_hoops_CSRGR, _hoops_IHSAC, 3, GL_FLOAT, GL_FALSE, stride, (char *) 0);
			if (_hoops_PPCP->_hoops_HHCP())
				_hoops_GGSAC(_hoops_CSRGR, _hoops_GISAC, 3, GL_FLOAT, GL_FALSE, stride, (char *) 0 + _hoops_HPRAC);
			if (_hoops_PPCP->_hoops_SHCP())
				_hoops_GGSAC(_hoops_CSRGR, _hoops_CHSAC, 4, GL_UNSIGNED_BYTE, GL_TRUE, stride, (char *) 0 + colors_offset);
			for (_hoops_RICP = 0; _hoops_RICP < H3D_MAX_TEXTURES; _hoops_RICP++) {
				_hoops_GGSAC(_hoops_CSRGR, _hoops_RISAC[_hoops_RICP], _hoops_PPCP->_hoops_CPIGR(_hoops_RICP), GL_FLOAT, GL_FALSE, stride, (char *) 0 + _hoops_AISAC);
				_hoops_AISAC += _hoops_PPCP->_hoops_CPIGR(_hoops_RICP) * sizeof(float);
			}
		}
		_hoops_HGSAC(_hoops_CSRGR);
	}

	void _hoops_CHSA(H3DData *h3ddata, Test *cull_results = null)
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;
		Display_Context *dc = (Display_Context *)h3ddata->dc;

		ASSERT(!_hoops_IPSAC && !_hoops_HPSAC);

		ENSURE_ARRAY_BUFFER(_hoops_CSRGR, m_pVertexBuffer);
		ENSURE_ELEMENT_BUFFER(_hoops_CSRGR, _hoops_SSPAH);

		_hoops_HHSAC();		

		if (cull_results == null || !_hoops_PPSAC) {
			if (_hoops_PPSAC) {
				switch (_hoops_RPSAC) {
					case H3DPT_TRIANGLELIST:
					case H3DPT_TRIANGLESTRIP:
						h3ddata->dc->_hoops_IGGI->_hoops_AGCAR += _hoops_PPSAC;
						break;
					case H3DPT_LINELIST:
					case H3DPT_LINESTRIP:
						h3ddata->dc->_hoops_IGGI->_hoops_AHRGH += _hoops_PPSAC;
						break;
					default:
						ASSERT(0);
						break;
				}

				glDrawElements (
					_hoops_GCCAC(_hoops_RPSAC), 
					_hoops_RSCAC(_hoops_RPSAC, _hoops_PPSAC),
					(_hoops_GSPP == H3DFMT_INDEX16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, 
					null);
			}
			else {
				glDrawArrays (
					_hoops_GCCAC(_hoops_RPSAC),
					0,
					_hoops_RAIRR);
			}
		}
		else {
			int prev = 0;
			int len = 0;
			int i = 0;  //0.._hoops_RIPAH->_hoops_RPR
			int k = 0;  //0.._hoops_AIPAH
			int _hoops_PGHS = 0;

			for (;;) {
				if (_hoops_RPHS) {
					if (_hoops_IAHS && 
						_hoops_IAHS->_hoops_ACHS) {
						while (k < _hoops_SAHS) {
							while (_hoops_IAHS->_hoops_ACHS[i] > 0)
								i++;

							if (_hoops_RRIRR(cull_results[i + _hoops_GPHS])) {
								len = _hoops_RPHS[k] - prev;				
								k++;
								i++;
							}
							else
								break;
						}
					}
					else {
						while (k < _hoops_SAHS && 
							_hoops_RRIRR(cull_results[k + _hoops_GPHS])) {
								len = _hoops_RPHS[k] - prev;				
								k++;
						}
					}

					// _hoops_PIPAH _hoops_SR _hoops_SRSH _hoops_GPP _hoops_IRS _hoops_IAPRR _hoops_RPGP, _hoops_PAR _hoops_SR _hoops_PPHRH _hoops_APCRR. _hoops_GPGP _hoops_GIPR _hoops_ARAR, _hoops_SR
					// _hoops_RRP _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_PCPA _hoops_SPCC _hoops_IIGR _hoops_RH _hoops_CGHI _hoops_PAIRR _hoops_IS _hoops_SHH _hoops_CHCC, _hoops_PPR _hoops_GGCR _hoops_IS _hoops_RH
					// _hoops_APSR _hoops_SPCC.
					if (k == _hoops_SAHS) {
						// _hoops_CR _hoops_SR _hoops_RGAR _hoops_ASH _hoops_RH _hoops_SRS _hoops_CIHA _hoops_IIGR _hoops_GRR _hoops_PAIRR, _hoops_SR _hoops_RRP _hoops_IS _hoops_CSGA
						// _hoops_RH _hoops_SPCC _hoops_IIGR _hoops_RH _hoops_CGHI _hoops_SPR (_hoops_GAR _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_HIPAH _hoops_GCSS _hoops_GGR _hoops_RH _hoops_AII _hoops_CRPR)
						if (_hoops_GSPP == H3DFMT_INDEX32)
							len += ((_hoops_CPSAC >> 2) - _hoops_RPHS[k-1]); //_hoops_GHCH _hoops_HPP 4
						else
							len += ((_hoops_CPSAC >> 1) - _hoops_RPHS[k-1]); //_hoops_GHCH _hoops_HPP 2

					}
					else
						len = _hoops_RPHS[k] - prev;
				}
				else if (_hoops_RRIRR(cull_results[_hoops_GPHS])) {
					if (_hoops_GSPP == H3DFMT_INDEX32)
						len = (_hoops_CPSAC >> 2); //_hoops_GHCH _hoops_HPP 4
					else
						len = (_hoops_CPSAC >> 1); //_hoops_GHCH _hoops_HPP 2
				}

				if (len > 0) {
					switch (_hoops_RPSAC) {
						case H3DPT_TRIANGLELIST:
							_hoops_PGHS = len / 3;
							_hoops_RCCA(_hoops_AGCAR) += _hoops_PGHS;
							if (dc->_hoops_PGCAR > 0 &&
								_hoops_RCCA(_hoops_AGCAR) > _hoops_RCCA(_hoops_HGCAR)+dc->_hoops_PGCAR) {
								_hoops_RCCA(_hoops_HGCAR) = _hoops_RCCA(_hoops_AGCAR);
								_hoops_RCCA(_hoops_IGCAR)++;
								_hoops_SGPAR(h3ddata);
							}
							break;
						case H3DPT_TRIANGLESTRIP:
							_hoops_PGHS = len - 2;
							_hoops_RCCA(_hoops_AGCAR) += _hoops_PGHS;
							if (dc->_hoops_PGCAR > 0 &&
								_hoops_RCCA(_hoops_AGCAR) > _hoops_RCCA(_hoops_HGCAR)+dc->_hoops_PGCAR) {
								_hoops_RCCA(_hoops_HGCAR) = _hoops_RCCA(_hoops_AGCAR);
								_hoops_RCCA(_hoops_IGCAR)++;
								_hoops_SGPAR(h3ddata);
							}
							break;
						case H3DPT_LINELIST:
							_hoops_PGHS = len / 2;
							_hoops_RCCA(_hoops_AHRGH) += _hoops_PGHS;
							break;
						case H3DPT_LINESTRIP:
							_hoops_PGHS = len - 1;
							_hoops_RCCA(_hoops_AHRGH) += _hoops_PGHS;
							break;
						default:
							ASSERT(0);
							break;
					}

					int _hoops_PISAC = (_hoops_GSPP == H3DFMT_INDEX32) ? 4 : 2;
					glDrawElements (
						_hoops_GCCAC(_hoops_RPSAC), 
						_hoops_RSCAC(_hoops_RPSAC, _hoops_PGHS),
						(_hoops_GSPP == H3DFMT_INDEX16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, 
						(char *)0 + prev*_hoops_PISAC);
				}
				if (_hoops_RPHS == null)
					break;

				if (_hoops_IAHS && 
					_hoops_IAHS->_hoops_ACHS) {
					while (k < _hoops_SAHS) {
						while (_hoops_IAHS->_hoops_ACHS[i] > 0)
							i++;

						if (!_hoops_RRIRR(cull_results[i + _hoops_GPHS])) {
							prev = _hoops_RPHS[k];
							k++;
							i++;
						}
						else
							break;
					}
				}
				else {
					while (k < _hoops_SAHS && 
						!_hoops_RRIRR(cull_results[k + _hoops_GPHS])) {
							prev = _hoops_RPHS[k];
							k++;
					}
				}

				if (k == _hoops_SAHS)
					break;
			}
		}

		return;
	}

	void _hoops_GPAS(H3DData *h3ddata, float _hoops_RPIRR = 1.0f)
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;
		UNREFERENCED(_hoops_CSRGR);

		ASSERT(!_hoops_IPSAC && !_hoops_HPSAC);

		ENSURE_ARRAY_BUFFER(_hoops_CSRGR, m_pVertexBuffer);
		ENSURE_ELEMENT_BUFFER(_hoops_CSRGR, _hoops_SSPAH);

		_hoops_HHSAC();

		if (_hoops_SSPAH) {
			glDrawElements (
					_hoops_GCCAC(_hoops_RPSAC), 
					_hoops_RSCAC(_hoops_RPSAC, _hoops_PPSAC*_hoops_RPIRR),
					(_hoops_GSPP == H3DFMT_INDEX16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, 
					null);
		}
		else {
			glDrawArrays (
				_hoops_GCCAC(_hoops_RPSAC),
				0,
				_hoops_RAIRR * _hoops_RPIRR);
		}

		return;
	}

};


/*****************************************************************************
*****************************************************************************
				_hoops_GR: _hoops_SASAC _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
#define _hoops_HISAC 128

#if 0
// _hoops_RGR _hoops_HRGR _hoops_RH _hoops_HRSAR _hoops_GPHA _hoops_SRHR _hoops_IHAH, _hoops_IHGS _hoops_IGI _hoops_IH _hoops_RAR _hoops_AAR _hoops_CPAP
class _hoops_IISAC : public H3DVertexBufferCache
{
public:
	_hoops_IISAC()
	{
		HOOPS_WORLD->display_list_vram_usage += _hoops_HISAC;
		m_pVertexBuffer = 0;
		_hoops_GRIC	= 0;
		_hoops_PPIH = 0;
		_hoops_APIH = 0;
		m_data			= null;
	}

	~_hoops_IISAC()
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		glDeleteBuffers(1, &m_pVertexBuffer);
		FORCE_ARRAY_BUFFER(_hoops_CSRGR, 0);

		HOOPS_WORLD->display_list_vram_usage -= _hoops_HISAC;
		HOOPS_WORLD->display_list_vram_usage -= (_hoops_GRIC * _hoops_CPIRR);
	}

	bool CreateVertexBuffer(H3DData *h3ddata, unsigned int _hoops_APIRR, 
		H3DVertexFormat VF)
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC = (HOGLData *) h3ddata;
		UNREFERENCED(_hoops_CSRGR);

		_hoops_GRIC	= _hoops_APIRR;
		_hoops_CPIRR = VF._hoops_HGHS();
		_hoops_AAIRR			= VF;

		glGenBuffersARB(1, &m_pVertexBuffer);
		HOOPS_WORLD->display_list_vram_usage += (_hoops_GRIC * _hoops_CPIRR);
		return true;
	}

	bool Reset()
	{
		//_hoops_SIGP: _hoops_CISAC(_hoops_SISAC);
		HOOPS_WORLD->display_list_vram_usage -= (_hoops_GRIC * _hoops_CPIRR);

		_hoops_GRIC	= 0;
		_hoops_PPIH = 0;
		_hoops_APIH = 0;
		return true;
	}

	bool _hoops_RIAC()
	{
		return true;
	}

	bool Lock(unsigned int count, H3DVertexBuffer *_hoops_PAIH)
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		float *_hoops_GIIGR = null;

		// _hoops_HGH _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_PIH _hoops_IS _hoops_SHH _hoops_RIPPR _hoops_CRGR _hoops_RH _hoops_GPHA _hoops_SRHR.
		unsigned int data_size = count * _hoops_CPIRR;

		// _hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_RH _hoops_RSIR _hoops_GPHA _hoops_SRHR _hoops_SSCP _hoops_RPII _hoops_IGI _hoops_GH _hoops_GAPR.
		if (_hoops_PPIH > (_hoops_GRIC*_hoops_CPIRR - data_size))
		{
			// _hoops_CSH _hoops_GC _hoops_IGICR. _hoops_GCIH _hoops_IAPR _hoops_HII _hoops_RH _hoops_RSGI 
			//		 _hoops_IIGR _hoops_RH _hoops_GPHA _hoops_SRHR.
			_hoops_APIH = 0;
			_hoops_PPIH = 0;
		}

		// _hoops_HRAH _hoops_RH _hoops_GPHA _hoops_SRHR.
		ENSURE_ARRAY_BUFFER(_hoops_CSRGR, m_pVertexBuffer);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, data_size, NULL, GL_DYNAMIC_DRAW);
		_hoops_GIIGR = (float *)glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);
		ASSERT (_hoops_GIIGR != null);
		_hoops_PAIH->_hoops_IRA(_hoops_GIIGR, &_hoops_AAIRR);
		_hoops_HPRAC = _hoops_PAIH->_hoops_GPCGR() * sizeof(float);
		colors_offset = _hoops_PAIH->_hoops_RPCGR() * sizeof(float);
		_hoops_GPSAC = _hoops_PAIH->_hoops_APCGR() * sizeof(float);

		// _hoops_RCPAH _hoops_IS _hoops_RH _hoops_SPS _hoops_AHC _hoops_GGR _hoops_RH _hoops_GPHA _hoops_SRHR.
		_hoops_PPIH += data_size;

		return (_hoops_GIIGR != null);
	}

	bool Unlock()
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		GLboolean result = glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
		return (result == GL_NO_ERROR);
	}

	bool _hoops_CHSA(H3DData *h3ddata , H3DPRIMITIVETYPE _hoops_HPIRR, unsigned int _hoops_IPIRR)
	{
		bool result = _hoops_HGSA(h3ddata, _hoops_HPIRR, _hoops_IPIRR);
		_hoops_CGSA();
		return result;
	}

	bool _hoops_HGSA(H3DData *h3ddata , H3DPRIMITIVETYPE _hoops_HPIRR, unsigned int _hoops_IPIRR)
	{
		GLenum _hoops_SCGS = _hoops_GCCAC(_hoops_HPIRR);
		GLsizei _hoops_GCSAC = _hoops_IPIRR;
		HOGLData *_hoops_CSRGR;
		_hoops_CSRGR = _hoops_PHIAC = (HOGLData *) h3ddata;

		ENSURE_ARRAY_BUFFER(_hoops_CSRGR, m_pVertexBuffer);

		ENSURE_NORMAL_ARRAY(_hoops_PHIAC,_hoops_AAIRR._hoops_HHCP()); 
		if (_hoops_AAIRR._hoops_HHCP())
			glNormalPointer (GL_FLOAT, _hoops_CPIRR, (char *) null + _hoops_HPRAC);	

		int _hoops_RICP = 0;
		int _hoops_AISAC = _hoops_GPSAC;
		for (_hoops_RICP = 0; _hoops_RICP < H3D_MAX_TEXTURES; _hoops_RICP++) {
			if (_hoops_RICP < _hoops_AAIRR._hoops_APIGR()) {
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_PHIAC, _hoops_RICP, true);
				glTexCoordPointer (_hoops_AAIRR._hoops_CPIGR(_hoops_RICP), GL_FLOAT, _hoops_CPIRR, (char *) 0 + _hoops_AISAC);
				_hoops_AISAC += _hoops_AAIRR._hoops_CPIGR(_hoops_RICP) * sizeof(float);
			}
			else
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_PHIAC, _hoops_RICP, false);
		}

		ENSURE_COLOR_ARRAY(_hoops_PHIAC,_hoops_AAIRR._hoops_SHCP());
		if (_hoops_AAIRR._hoops_SHCP())
			glColorPointer (4, GL_UNSIGNED_BYTE, _hoops_CPIRR, (char *) null + colors_offset);

		ENSURE_VERTEX_ARRAY(_hoops_PHIAC, true);
		glVertexPointer (3, GL_FLOAT, _hoops_CPIRR, (char *) null);


		//_hoops_RCSAC(_hoops_ACSAC(_hoops_PCSAC), _hoops_HCSAC/_hoops_ICSAC, _hoops_CCSAC);
		_hoops_GCSAC = _hoops_RSCAC(_hoops_HPIRR, _hoops_IPIRR);	
		glDrawArrays(_hoops_SCGS, 0, _hoops_GCSAC);
		return glGetError() == GL_NO_ERROR;
	}

	void _hoops_CGSA()
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		_hoops_APIH = _hoops_PPIH;


	}

	float *m_data;

	GLuint m_pVertexBuffer;
	int _hoops_HPRAC;
	int colors_offset;
	int _hoops_GPSAC;
	HOGLData *_hoops_PHIAC;
};
#else

// _hoops_RGR _hoops_HRGR _hoops_RH _hoops_HRSAR _hoops_GPHA _hoops_SRHR _hoops_IHAH, _hoops_IHGS _hoops_IGI _hoops_IH _hoops_RAR _hoops_AAR _hoops_CPAP
class _hoops_IISAC : public H3DVertexBufferCache
{
public:
	_hoops_IISAC()
	{
		HOOPS_WORLD->display_list_vram_usage += _hoops_HISAC;
		m_pVertexBuffer = 0;
		_hoops_ACPAH = 0;
		_hoops_PCPAH = 0;
		_hoops_GRIC	= 0;
		_hoops_PPIH = 0;
		_hoops_APIH = 0;
		_hoops_RHIRR = 0;
		_hoops_GHIRR = 0;
	}

	~_hoops_IISAC()
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC;
		glDeleteBuffers(1, &m_pVertexBuffer);
		if (_hoops_ACPAH)
			glDeleteBuffers(1, &_hoops_ACPAH);
		if (_hoops_PCPAH)
			glDeleteBuffers(1, &_hoops_PCPAH);

		if (_hoops_SHIRR)
			FREE_ARRAY_ALIGNED(_hoops_SHIRR, _hoops_GRIC*_hoops_CPIRR/4, float, 16);
		if (_hoops_GIIRR)
			FREE_ARRAY_ALIGNED(_hoops_GIIRR, _hoops_GRIC*_hoops_CPIRR/4, float, 16);
		if (_hoops_RIIRR)
			FREE_ARRAY(_hoops_RIIRR, _hoops_GRIC*_hoops_SPIRR/4, float);

		HOOPS_WORLD->display_list_vram_usage -= _hoops_HISAC;
		HOOPS_WORLD->display_list_vram_usage -= (_hoops_GRIC * _hoops_CPIRR);
	}

	bool CreateVertexBuffer(H3DData *h3ddata, unsigned int _hoops_APIRR, 
		H3DVertexFormat VF)
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC = (HOGLData *) h3ddata;
		UNREFERENCED(_hoops_CSRGR);

		_hoops_GRIC		= _hoops_APIRR;
		_hoops_AAIRR				= VF;
		_hoops_CPIRR		= 12;
		_hoops_SPIRR	= VF._hoops_HGHS(true, false);

		ALLOC_ARRAY_ALIGNED(_hoops_SHIRR, _hoops_GRIC*_hoops_CPIRR/4, float, 16);
		if (_hoops_AAIRR._hoops_HHCP()) {
			ALLOC_ARRAY_ALIGNED(_hoops_GIIRR, _hoops_GRIC*_hoops_CPIRR/4, float, 16);
		}
		if (_hoops_AAIRR._hoops_PSCP()) {
			ALLOC_ARRAY(_hoops_RIIRR, _hoops_GRIC*_hoops_SPIRR/4, float);
		}

#ifndef _hoops_AICAC
		glGenBuffersARB(1, &m_pVertexBuffer);
		ENSURE_ARRAY_BUFFER(_hoops_CSRGR, m_pVertexBuffer);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, _hoops_SCSAC * sizeof(float), NULL, GL_DYNAMIC_DRAW);
#endif

		HOOPS_WORLD->display_list_vram_usage += (_hoops_GRIC * _hoops_CPIRR);
		return glGetError() == GL_NO_ERROR;
	}

	bool Reset()
	{
		//_hoops_SIGP: _hoops_CISAC(_hoops_SISAC);
		HOOPS_WORLD->display_list_vram_usage -= (_hoops_GRIC * _hoops_CPIRR);

		if (_hoops_SHIRR)
			FREE_ARRAY_ALIGNED(_hoops_SHIRR, _hoops_GRIC*_hoops_CPIRR/4, float, 16);
		if (_hoops_GIIRR)
			FREE_ARRAY_ALIGNED(_hoops_GIIRR, _hoops_GRIC*_hoops_CPIRR/4, float, 16);
		if (_hoops_RIIRR)
			FREE_ARRAY(_hoops_RIIRR, _hoops_GRIC*_hoops_SPIRR/4, float);

		_hoops_GRIC	= 0;
		_hoops_PPIH = 0;
		_hoops_APIH = 0;
		return glGetError() == GL_NO_ERROR;
	}

	bool _hoops_RIAC()
	{
		return glGetError() == GL_NO_ERROR;
	}

	bool _hoops_PPIRR(_hoops_HRPA const *matrix = null, int length = -1)
	{
		bool result = true;
		int _hoops_ICPAH = (length >= 0) ? length : _hoops_AHIRR/_hoops_CPIRR;
		_hoops_ICPAH -= _hoops_PHIRR;
		if (_hoops_ICPAH <= 0)
			return true;

		int offset = _hoops_PHIRR*3;
		if (matrix)
			HI_Compute_Transformed_Points(_hoops_ICPAH, (Point*)(_hoops_SHIRR+offset), &matrix->elements[0][0], (Point*)(_hoops_SHIRR+offset));
		
		if (_hoops_AAIRR._hoops_HHCP()) {
			if (matrix)
				HI_Compute_Transformed_Vectors(_hoops_ICPAH, (Vector*)(_hoops_GIIRR+offset), &matrix->_hoops_APRA->data.elements[0][0], (Vector*)(_hoops_GIIRR+offset));
		}

		_hoops_PHIRR += _hoops_ICPAH;
		return result;
	}

	bool Lock(unsigned int count, H3DVertexBuffer *_hoops_PAIH)
	{
		_hoops_PHIRR = 0;
		_hoops_GSSAC = true;

		// _hoops_HGH _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_PIH _hoops_IS _hoops_SHH _hoops_RIPPR _hoops_CRGR _hoops_RH _hoops_GPHA _hoops_SRHR.
		unsigned int data_size = count * _hoops_CPIRR;
		unsigned int _hoops_CCPAH = count * _hoops_SPIRR;
		_hoops_AHIRR = data_size;

		// _hoops_ARGH _hoops_IS _hoops_CACH _hoops_RPP _hoops_RH _hoops_RSIR _hoops_GPHA _hoops_SRHR _hoops_SSCP _hoops_RPII _hoops_IGI _hoops_GH _hoops_GAPR.
#ifndef _hoops_AICAC
		if (_hoops_PPIH > (_hoops_GRIC*_hoops_CPIRR - data_size))
#endif
		{
			// _hoops_CSH _hoops_GC _hoops_IGICR. _hoops_GCIH _hoops_IAPR _hoops_HII _hoops_RH _hoops_RSGI 
			//		 _hoops_IIGR _hoops_RH _hoops_GPHA _hoops_SRHR.
			_hoops_APIH = 0;
			_hoops_PPIH = 0;
		}

		// _hoops_HRAH _hoops_RH _hoops_GPHA _hoops_SRHR.
		_hoops_PAIH->_hoops_IRA(_hoops_SHIRR, _hoops_GIIRR, _hoops_RIIRR, &_hoops_AAIRR);
		_hoops_HPRAC = _hoops_PAIH->_hoops_GPCGR() * sizeof(float);
		colors_offset = _hoops_PAIH->_hoops_RPCGR() * sizeof(float);
		_hoops_GPSAC = _hoops_PAIH->_hoops_APCGR() * sizeof(float);

		// _hoops_RCPAH _hoops_IS _hoops_RH _hoops_SPS _hoops_AHC _hoops_GGR _hoops_RH _hoops_GPHA _hoops_SRHR.
		_hoops_PPIH += data_size;
		_hoops_RHIRR += _hoops_CCPAH;

		// _hoops_ACGR _hoops_SPS _hoops_PPCAR 12-_hoops_RAPSR _hoops_PPR 16-_hoops_RAPSR _hoops_AHSGP (_hoops_CHGC _hoops_PPCAR _hoops_GPGR _hoops_IIGR 12 _hoops_PPR 16 > _hoops_SCPAH)
		if (_hoops_PPIH % 16 || _hoops_PPIH % 12) {
			int start = _hoops_PPIH;
			int _hoops_GSPAH = 0;

			// _hoops_RSPAH _hoops_IS _hoops_SPS 16 _hoops_RAPSR _hoops_AHSGP
			_hoops_PPIH += (16 - (_hoops_PPIH % 16));

			// _hoops_ACGR _hoops_SPS 16 _hoops_RAPSR _hoops_AHSGP _hoops_SGS'_hoops_GRI _hoops_GACC 12 _hoops_RAPSR _hoops_RGCGA
			while (_hoops_PPIH % 12)
				_hoops_PPIH += 16;

			_hoops_GSPAH = (_hoops_PPIH - start) / 12;
			_hoops_RHIRR += _hoops_GSPAH * _hoops_SPIRR;
		}

		return (_hoops_SHIRR != null);
	}

	bool Unlock(_hoops_HRPA const *matrix)
	{
		_hoops_PPIRR(matrix);

#ifndef _hoops_AICAC
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		ENSURE_ARRAY_BUFFER(_hoops_CSRGR, m_pVertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, _hoops_APIH, _hoops_RSSAC, m_data + (_hoops_APIH/sizeof(float)));
#endif

		_hoops_GSSAC = false;

		return glGetError() == GL_NO_ERROR;
	}

	int _hoops_ASPAH()
	{
		return  _hoops_APIH/_hoops_CPIRR;
	}

	bool _hoops_CHSA(H3DData *h3ddata , H3DPRIMITIVETYPE _hoops_HPIRR, unsigned int _hoops_IPIRR)
	{
		bool result = _hoops_HGSA(h3ddata, _hoops_HPIRR, _hoops_IPIRR);
		_hoops_CGSA();
		return result;
	}

	bool _hoops_HGSA(H3DData *h3ddata , H3DPRIMITIVETYPE _hoops_HPIRR, unsigned int _hoops_IPIRR)
	{
		GLenum _hoops_SCGS = _hoops_GCCAC(_hoops_HPIRR);
		GLsizei _hoops_GCSAC = _hoops_RSCAC(_hoops_HPIRR, _hoops_IPIRR);
		HOGLData *_hoops_CSRGR = _hoops_PHIAC = (HOGLData *) h3ddata;
		_hoops_PIIAC *_hoops_RSR = (_hoops_PIIAC *)_hoops_CSRGR->_hoops_CSC->_hoops_AGSA;

		ENSURE_ARRAY_BUFFER(_hoops_CSRGR, m_pVertexBuffer);

		_hoops_PGSAC(_hoops_CSRGR);
		{
			_hoops_GGSAC(_hoops_CSRGR, _hoops_RSR->_hoops_SRSAC, 3, GL_FLOAT, GL_FALSE, _hoops_CPIRR, (char *) _hoops_SHIRR);
			if (_hoops_AAIRR._hoops_HHCP())
				_hoops_GGSAC(_hoops_CSRGR, _hoops_RSR->_hoops_GASAC, 3, GL_FLOAT, GL_FALSE, _hoops_CPIRR, (char *) _hoops_GIIRR + _hoops_HPRAC);
			if (_hoops_AAIRR._hoops_SHCP())
				_hoops_GGSAC(_hoops_CSRGR, _hoops_RSR->_hoops_RASAC, 4, GL_UNSIGNED_BYTE, GL_TRUE, _hoops_SPIRR, (char *) _hoops_RIIRR + colors_offset);
			if (_hoops_AAIRR._hoops_APIGR() > 0) {
				int _hoops_RICP = 0;
				int _hoops_AISAC = _hoops_GPSAC;
				for (_hoops_RICP = 0; _hoops_RICP < H3D_MAX_TEXTURES; _hoops_RICP++) {
					_hoops_GGSAC(_hoops_CSRGR, _hoops_RSR->_hoops_HASAC[_hoops_RICP], _hoops_AAIRR._hoops_CPIGR(_hoops_RICP), GL_FLOAT, GL_FALSE, _hoops_SPIRR, (char *) _hoops_RIIRR + _hoops_AISAC);
					_hoops_AISAC += _hoops_AAIRR._hoops_CPIGR(_hoops_RICP) * sizeof(float);
				}
			}
		}
		_hoops_HGSAC(_hoops_CSRGR);

		glDrawArrays(_hoops_SCGS, _hoops_APIH/_hoops_CPIRR, _hoops_GCSAC);
		return glGetError() == GL_NO_ERROR;
	}

	void _hoops_CGSA()
	{
		_hoops_APIH = _hoops_PPIH;
		_hoops_GHIRR = _hoops_RHIRR;
	}

	GLuint m_pVertexBuffer;
	GLuint _hoops_ACPAH;
	GLuint _hoops_PCPAH;
	int _hoops_HPRAC;
	int colors_offset;
	int _hoops_GPSAC;
	HOGLData *_hoops_PHIAC;

	bool _hoops_GSSAC;
};
#endif

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_ASSAC _hoops_CSHGR
*****************************************************************************
*****************************************************************************/

#if 1
class _hoops_PSSAC : public H3DIndexBufferCache
{
public:
	_hoops_PSSAC()
	{
		_hoops_SSPAH = 0;
		_hoops_PGHAH = null;
		_hoops_RGHAH = 0;
		_hoops_GGHAH = 0;
	}

	~_hoops_PSSAC()
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

#ifndef _hoops_PICAC
		glDeleteBuffers(1, &_hoops_SSPAH);
#endif

		if (m_data)
			FREE_ARRAY(m_data, _hoops_GHIH, short);
	}

	bool CreateIndexBuffer(H3DData *h3ddata)
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC = (HOGLData *) h3ddata;
		UNREFERENCED(_hoops_CSRGR);

#ifndef _hoops_PICAC
		glGenBuffers(1, &_hoops_SSPAH);
		ENSURE_ELEMENT_BUFFER(_hoops_CSRGR, _hoops_SSPAH);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _hoops_GHIH * sizeof(short), NULL, GL_DYNAMIC_DRAW);
#endif

		ALLOC_ARRAY(m_data, _hoops_GHIH, short);
		return true;
	}


	bool Lock(short count, short **_hoops_AIIRR)
	{
		if (_hoops_GSSAC)
			return false;

		_hoops_HSSAC = count;

		if (_hoops_RGHAH + count >= _hoops_GHIH) {
			_hoops_RGHAH = 0;
		}

		_hoops_GGHAH = _hoops_RGHAH + count;

#ifdef _DEBUG
		m_data[_hoops_GGHAH - 1] = -1;	// _hoops_IH _hoops_GSPHR _hoops_GCGC; _hoops_IHIGR _hoops_IHHH _hoops_IS _hoops_CACH _hoops_CAS _hoops_RSGR _hoops_IIGR _hoops_SRHR _hoops_HRGR
#endif

		// _hoops_HRAH _hoops_RH _hoops_GPHA _hoops_SRHR.
		*_hoops_AIIRR = m_data + _hoops_RGHAH;
		_hoops_GSSAC = true;
		
		return true;
	}

	bool Unlock()
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		if (!_hoops_GSSAC)
			return false;

#ifndef _hoops_PICAC
		ENSURE_ELEMENT_BUFFER(_hoops_CSRGR, _hoops_SSPAH);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, _hoops_HSSAC * sizeof(short), m_data);
#endif

		_hoops_GSSAC = false;
		return true;
	}


#if 0
	bool Lock(short count, short **_hoops_AIIRR)
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		int _hoops_AGHAH = count * sizeof(short);
		_hoops_GGHAH = _hoops_AGHAH;

		// _hoops_HRAH _hoops_RH _hoops_GPHA _hoops_SRHR.
		//_hoops_ISSAC(_hoops_RHSAC, _hoops_CSSAC);
		//_hoops_SSSAC(_hoops_RHSAC, _hoops_GGGPC, _hoops_IHHAH, _hoops_RGGPC);
		//*_hoops_AGGPC = (_hoops_ICHRR *)_hoops_PGGPC(_hoops_RHSAC, _hoops_HGGPC);
		
		return (*_hoops_AIIRR != null);
	}

	bool Unlock()
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		//_hoops_SPSAC _hoops_GHPP = _hoops_GHSAC(_hoops_RHSAC);
		return (result == GL_NO_ERROR);
	}
#endif

	bool _hoops_CHSA(H3DData *h3ddata, H3DPRIMITIVETYPE _hoops_HPIRR, 
		unsigned int _hoops_PIIRR,
		unsigned int _hoops_IPIRR)
	{
		UNREFERENCED(_hoops_PIIRR);
		HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;
		_hoops_PIIAC *_hoops_RSR = (_hoops_PIIAC *) _hoops_CSRGR->_hoops_CSC->_hoops_AGSA;
		float *_hoops_IGGPC = (float*) _hoops_PGHAH->_hoops_APIH;
		float *_hoops_CGGPC;
		float *_hoops_SGGPC;
		short *_hoops_GRGPC = null;

#ifdef _hoops_AICAC
		_hoops_IGGPC = _hoops_PGHAH->_hoops_SHIRR;
		_hoops_CGGPC = _hoops_PGHAH->_hoops_GIIRR;
		_hoops_SGGPC = _hoops_PGHAH->_hoops_RIIRR;
#endif

#ifdef _hoops_PICAC
		_hoops_GRGPC = m_data;
#endif

		//_hoops_AGHR(_hoops_RRGPC->_hoops_SISAC);
		ENSURE_ARRAY_BUFFER(_hoops_CSRGR, _hoops_PGHAH->m_pVertexBuffer);
		ENSURE_ELEMENT_BUFFER(_hoops_CSRGR, _hoops_SSPAH);

		H3DVertexFormat *_hoops_PPCP = &_hoops_PGHAH->_hoops_AAIRR;

		_hoops_PGSAC(_hoops_CSRGR);
		{
			_hoops_GGSAC(_hoops_CSRGR, _hoops_RSR->_hoops_SRSAC, 3, GL_FLOAT, GL_FALSE, _hoops_PGHAH->_hoops_CPIRR, (char *) _hoops_IGGPC);
			if (_hoops_PPCP->_hoops_HHCP())
				_hoops_GGSAC(_hoops_CSRGR, _hoops_RSR->_hoops_GASAC, 3, GL_FLOAT, GL_FALSE, _hoops_PGHAH->_hoops_CPIRR, (char *) _hoops_CGGPC + _hoops_PGHAH->_hoops_HPRAC);	
			if (_hoops_PPCP->_hoops_SHCP())
				_hoops_GGSAC(_hoops_CSRGR, _hoops_RSR->_hoops_RASAC, 4, GL_UNSIGNED_BYTE, GL_TRUE, _hoops_PGHAH->_hoops_SPIRR, (char *) _hoops_SGGPC + _hoops_PGHAH->colors_offset);	
			int _hoops_RICP = 0;
			int _hoops_AISAC = _hoops_PGHAH->_hoops_GPSAC;
			for (_hoops_RICP = 0; _hoops_RICP < H3D_MAX_TEXTURES; _hoops_RICP++) {
				_hoops_GGSAC(_hoops_CSRGR, _hoops_RSR->_hoops_HASAC[_hoops_RICP], _hoops_PPCP->_hoops_CPIGR(_hoops_RICP), GL_FLOAT, GL_FALSE, _hoops_PGHAH->_hoops_SPIRR, (char *) _hoops_SGGPC + _hoops_AISAC);
				_hoops_AISAC += _hoops_PPCP->_hoops_CPIGR(_hoops_RICP) * sizeof(float);
			}
		}
		_hoops_HGSAC(_hoops_CSRGR);
			

		glDrawRangeElements (
			_hoops_GCCAC(_hoops_HPIRR), 
			_hoops_RGHAH,
			_hoops_RGHAH + _hoops_RSCAC(_hoops_HPIRR, _hoops_IPIRR),
			_hoops_RSCAC(_hoops_HPIRR, _hoops_IPIRR),
			GL_UNSIGNED_SHORT, 
			_hoops_GRGPC);
		/*_hoops_ARGPC (
			_hoops_ACSAC(_hoops_PCSAC), 
			_hoops_PRGPC(_hoops_PCSAC, _hoops_CCSAC),
			_hoops_HRGPC, 
			_hoops_IRGPC);*/

		return true;
	}

	void _hoops_CGSA()
	{
		//_hoops_CRGPC = _hoops_SRGPC;
		_hoops_PGHAH->_hoops_APIH = _hoops_PGHAH->_hoops_PPIH;
	}

	void _hoops_GAPRR (H3DVertexBufferCache *_hoops_IRPRR)
	{
		_hoops_PGHAH = (_hoops_IISAC *) _hoops_IRPRR;
	}

	short					*m_data;
	bool					_hoops_GSSAC;
	int						_hoops_HSSAC;

	HOGLData					*_hoops_PHIAC;
	GLuint					_hoops_SSPAH;
	_hoops_IISAC	*_hoops_PGHAH;
	unsigned int			_hoops_RGHAH;
	unsigned int			_hoops_GGHAH;
};
#else
class _hoops_PSSAC : public H3DIndexBufferCache
{
public:
	_hoops_PSSAC()
	{
		_hoops_PGHAH = null;
		_hoops_RGHAH = 0;
		_hoops_GGHAH = 0;
	}

	~_hoops_PSSAC()
	{
		if (m_data) {
			FREE_ARRAY(m_data, _hoops_GHIH, short);
			m_data = null;
		}
	}

	bool CreateIndexBuffer(H3DData *h3ddata)
	{
		_hoops_PHIAC = (HOGLData *) h3ddata;

		ALLOC_ARRAY(m_data, _hoops_GHIH, short);
		return true;
	}

	bool Lock(short count, short **_hoops_AIIRR)
	{
		if (_hoops_GSSAC)
			return false;

		_hoops_HSSAC = count;

		if (_hoops_RGHAH + count >= _hoops_GHIH) {
			_hoops_RGHAH = 0;
		}

		_hoops_GGHAH = _hoops_RGHAH + count;

#ifdef _DEBUG
		m_data[_hoops_GGHAH - 1] = -1;	// _hoops_IH _hoops_GSPHR _hoops_GCGC; _hoops_IHIGR _hoops_IHHH _hoops_IS _hoops_CACH _hoops_CAS _hoops_RSGR _hoops_IIGR _hoops_SRHR _hoops_HRGR
#endif

		// _hoops_HRAH _hoops_RH _hoops_GPHA _hoops_SRHR.
		*_hoops_AIIRR = m_data + _hoops_RGHAH;
		_hoops_GSSAC = true;
		
		return true;
	}

	bool Unlock()
	{
		if (!_hoops_GSSAC)
			return false;

		_hoops_GSSAC = false;
		return true;
	}

	bool _hoops_CHSA(H3DData *h3ddata, H3DPRIMITIVETYPE _hoops_HPIRR, 
		unsigned int _hoops_PIIRR,
		unsigned int _hoops_IPIRR)
	{
		UNREFERENCED(_hoops_PIIRR);
		HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;

		ENSURE_ARRAY_BUFFER(_hoops_PGHAH->m_pVertexBuffer);

		H3DVertexFormat *_hoops_PPCP = &_hoops_PGHAH->_hoops_AAIRR;

		int stride = _hoops_PPCP->_hoops_HGHS();
		ENSURE_VERTEX_ARRAY(_hoops_PHIAC, _hoops_PPCP->_hoops_IPIGR());
		if (_hoops_PPCP->_hoops_IPIGR())
			glVertexPointer (3, GL_FLOAT, stride, (char *) 0);	
		
		ENSURE_COLOR_ARRAY(_hoops_PHIAC, _hoops_PPCP->_hoops_SHCP());
		if (_hoops_PPCP->_hoops_SHCP())
			glColorPointer (4, GL_UNSIGNED_BYTE, stride, (char *) 0 + _hoops_PGHAH->colors_offset);	
		
		ENSURE_NORMAL_ARRAY(_hoops_PHIAC, _hoops_PPCP->_hoops_HHCP());
		if (_hoops_PPCP->_hoops_HHCP())
			glNormalPointer (GL_FLOAT, stride, (char *) 0 + _hoops_PGHAH->_hoops_HPRAC);	
		
		int _hoops_RICP = 0;
		int _hoops_AISAC = _hoops_PGHAH->_hoops_GPSAC;
		for (_hoops_RICP = 0; _hoops_RICP < H3D_MAX_TEXTURES; _hoops_RICP++) {
			if (_hoops_RICP < _hoops_PPCP->_hoops_APIGR()) {
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_PHIAC, _hoops_RICP, true);
				glTexCoordPointer (_hoops_PPCP->_hoops_CPIGR(_hoops_RICP), GL_FLOAT, stride, (char *) 0 + _hoops_AISAC);
				_hoops_AISAC += _hoops_PPCP->_hoops_CPIGR(_hoops_RICP) * sizeof(float);
			}
			else
				ENSURE_TEXTURE_COORD_ARRAY(_hoops_PHIAC, _hoops_RICP, false);
		}

		glDrawElements (
			_hoops_GCCAC(_hoops_HPIRR), 
			_hoops_RSCAC(_hoops_HPIRR, _hoops_IPIRR),
			GL_UNSIGNED_SHORT, 
			&m_data[_hoops_RGHAH]);

		return true;
	}

	void _hoops_CGSA()
	{
		_hoops_RGHAH = _hoops_GGHAH;
		_hoops_PGHAH->_hoops_APIH = _hoops_PGHAH->_hoops_PPIH;
	}

	void _hoops_GAPRR (H3DVertexBufferCache *_hoops_IRPRR)
	{
		_hoops_PGHAH = (_hoops_IISAC *) _hoops_IRPRR;
	}

	short					*m_data;
	bool					_hoops_GSSAC;
	int						_hoops_HSSAC;
	
	HOGLData					*_hoops_PHIAC;
	_hoops_IISAC	*_hoops_PGHAH;
	unsigned int			_hoops_RGHAH;
	unsigned int			_hoops_GGHAH;
};
#endif


/*****************************************************************************
*****************************************************************************
							_hoops_GAGPC _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
class _hoops_RGIAC : public H3DRenderTarget
{
private:
	GLuint _hoops_PCC;
	GLuint _hoops_RAGPC;			// _hoops_IGI _hoops_RPP _hoops_SR _hoops_RRP _hoops_GIPR _hoops_HCH _hoops_PPR _hoops_APSP, _hoops_HIH _hoops_PAH'_hoops_RA _hoops_GRGP _hoops_CRGR _hoops_IRS _hoops_RSRA _hoops_SAAP

public:
	_hoops_RGIAC(H3DData *h3ddata, 
		unsigned int width, 
		unsigned int height,
		unsigned int _hoops_GCI,		// _hoops_RAHAH
		H3DFORMAT format,
		int _hoops_ISARR = 0) :
		H3DRenderTarget(h3ddata, width, height, _hoops_GCI, format, _hoops_ISARR)
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) h3ddata;
		UNREFERENCED(_hoops_CSRGR);

		GLint gl_usage = 0, gl_usage2 = 0;
		_hoops_ISARR = _hoops_AHIA(_hoops_ISARR, _hoops_CSRGR->_hoops_APCAC);

		// _hoops_ARPR _hoops_PPR _hoops_CCPP _hoops_PPGS _hoops_IH _hoops_SRHR
		glGenRenderbuffersEXT (1, &_hoops_PCC);
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _hoops_PCC);


		switch (_hoops_GCI) {
			case H3DTEXUSAGE_DEPTHSTENCIL:
				if (GL_EXT_packed_depth_stencil)
					gl_usage = GL_DEPTH24_STENCIL8_EXT;
				else {
					gl_usage = GL_DEPTH_COMPONENT;
					gl_usage2 = GL_STENCIL_INDEX;
				}
				break;
			default: {
				_hoops_AAPIR const *_hoops_AAGPC;

				gl_usage = GL_RGBA;
				if ((_hoops_AAGPC = h3ddata->dc->options._hoops_HAPIR) != null) do {
					if (!strcmp (_hoops_AAGPC->name.text, "rgba16f")) {
						gl_usage = GL_RGBA16F_ARB;
						break;
					}
				} while ((_hoops_AAGPC = _hoops_AAGPC->next) != null);
				gl_usage2 = 0;
				break;
			}
		}	

		if (gl_usage) {
			if (_hoops_ISARR > 1)
				glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, _hoops_ISARR, gl_usage, width, height);
			else
				glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, gl_usage, width, height);

		}

		if (gl_usage2) {
			ASSERT(0);		// _hoops_HGI _hoops_RRGR _hoops_HRGR _hoops_HAR _hoops_GGSP?
			if (_hoops_ISARR > 1)
				glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, _hoops_ISARR, gl_usage2, width, height);
			else
				glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, gl_usage2, width, height);
		}
	}

	~_hoops_RGIAC()
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		UNREFERENCED(_hoops_CSRGR);

		if (_hoops_PCC != 0) {
			glDeleteRenderbuffersEXT(1, &_hoops_PCC);
			_hoops_PCC = 0;
		}
		if (_hoops_RAGPC != 0) {
			glDeleteRenderbuffersEXT(1, &_hoops_RAGPC);
			_hoops_RAGPC = 0;
		}
	}

	GLuint _hoops_IIARH() {return _hoops_PCC;}
	GLuint _hoops_PAGPC() {return _hoops_RAGPC;}
};


class _hoops_HGCAC : public H3DTexture
{
private:
	GLuint _hoops_PCC;
	GLuint _hoops_GSPP, _hoops_HAGPC;
	bool _hoops_GSSAC;
	unsigned int _hoops_IAGPC;
	unsigned char *m_data;

	unsigned int _hoops_CAGPC;

	bool _hoops_SAGPC;
	bool _hoops_GPGPC;
	bool _hoops_RPGPC;
	int _hoops_APGPC;

	H3DRect _hoops_PPGPC;
	bool _hoops_HPGPC;

public:
	_hoops_HGCAC(H3DData *h3ddata, 
		unsigned int width, 
		unsigned int height,
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI,
		H3DFORMAT format) :
		H3DTexture(h3ddata, width, height, _hoops_ICRH, _hoops_GCI, format)
	{
		GLint gl_type = GL_UNSIGNED_BYTE;

		UNREFERENCED(_hoops_ICRH);
		UNREFERENCED(_hoops_GCI);

		// _hoops_HIHH _hoops_HSSHH
		_hoops_GGPRR = H3DTEXF_POINT;
		_hoops_RGPRR = H3DTEXF_LINEAR;
		_hoops_AGPRR = H3DTEXF_NONE;
		_hoops_PGPRR = H3DTADDRESS_WRAP;
		_hoops_HGPRR = H3DTADDRESS_WRAP;
		//_hoops_RPCC _hoops_PPR _hoops_IPGPC _hoops_CHR _hoops_IS _hoops_SHH _hoops_AISP _hoops_CAPP
		_hoops_GSPP = 0; 
		_hoops_HAGPC = 0; 

		_hoops_ISS = h3ddata;
		m_data = null;
		_hoops_GSSAC = false;
		_hoops_SAGPC = false;
		_hoops_GPGPC = false;
		glGenTextures (1, &_hoops_PCC);

		if (ANYBIT(_hoops_GCI, H3DTEXUSAGE_RENDERTARGET | H3DTEXUSAGE_DEPTHSTENCIL)) {
			GLint _hoops_CRCAC = 0;

			glGetIntegerv(GL_TEXTURE_BINDING_2D, &_hoops_CRCAC);
			glBindTexture(GL_TEXTURE_2D, _hoops_PCC);
			
			_hoops_SSARR = 4;

			switch (format) {
				case H3DFMT_DXT1:
				case H3DFMT_DXT3:
				case H3DFMT_DXT5:
					ASSERT(0); // _hoops_AGCR _hoops_CGH _hoops_IIP _hoops_SHH _hoops_IGI _hoops_GAR _hoops_SRGS _hoops_HCSS
					break;
				case H3DFMT_D24S8:
					_hoops_HAGPC = GL_DEPTH24_STENCIL8_EXT;
					_hoops_GSPP = GL_DEPTH_STENCIL_EXT;
					break;
				case H3DFMT_L8:
					_hoops_GSPP = GL_LUMINANCE;
					_hoops_HAGPC = 1;
					_hoops_SSARR = 1;
					break;
				case H3DFMT_R8G8B8:
					_hoops_GSPP = GL_RGB;
					_hoops_HAGPC = GL_RGB8;
					_hoops_SSARR = 3;
					break;
				case H3DFMT_R32F:
				case H3DFMT_A8R8G8B8:
				default:
					_hoops_GSPP = GL_RGBA;
					_hoops_HAGPC = GL_RGBA8;
					break;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, _hoops_HAGPC, width, height, 0, _hoops_GSPP, gl_type, NULL);

			// _hoops_PPRII _hoops_SGH _hoops_AGCR _hoops_HRP _hoops_IS _hoops_SRCH _hoops_SISPR _hoops_IS _hoops_CPGPC _hoops_SPGPC (_hoops_PGAP _hoops_HRGR _hoops_CPPPR _hoops_HIAC)
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			_hoops_GGPRR = H3DTEXF_POINT;
			_hoops_RGPRR = H3DTEXF_POINT;
			_hoops_AGPRR = H3DTEXF_NONE;
			_hoops_PGPRR = H3DTADDRESS_CLAMP;
			_hoops_HGPRR = H3DTADDRESS_CLAMP;

			glBindTexture(GL_TEXTURE_2D, _hoops_CRCAC);
		}
		else {
			GLint _hoops_CRCAC = 0;
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &_hoops_CRCAC);
			glBindTexture(GL_TEXTURE_2D, _hoops_PCC);

			switch (format) {
				case H3DFMT_L8:
					_hoops_GSPP = GL_LUMINANCE;
					_hoops_HAGPC = 1;
					_hoops_SSARR = 1;
					break;
				case H3DFMT_R8G8B8:
					if (h3ddata->_hoops_CHGH) {
						_hoops_GSPP = GL_RGB;
						_hoops_HAGPC = GL_RGB8;
						_hoops_SSARR = 3;
						break;
					}
				case H3DFMT_A8R8G8B8:
					_hoops_GSPP = GL_RGBA;
					_hoops_HAGPC = GL_RGBA8;
					_hoops_SSARR = 4;
					break;
				case H3DFMT_DXT1:
					_hoops_RPGPC = true;
					_hoops_GSPP = GL_COMPRESSED_RGB_ARB;
					_hoops_HAGPC = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
					_hoops_SSARR = -1; //_hoops_RHGC
					break;
				case H3DFMT_DXT3:
					_hoops_RPGPC = true;
					_hoops_GSPP = GL_COMPRESSED_RGB_ARB;
					_hoops_HAGPC = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
					_hoops_SSARR = -1; //_hoops_RHGC
					break;
				case H3DFMT_DXT5:
					_hoops_RPGPC = true;
					_hoops_GSPP = GL_COMPRESSED_RGB_ARB;
					_hoops_HAGPC = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
					_hoops_SSARR = -1; //_hoops_RHGC
					break;
				default:
					_hoops_SSARR = 4;
					ASSERT (0); //_hoops_IACRI _hoops_HH _hoops_RPCC
			}

			if (!_hoops_RPGPC)
				glTexImage2D(GL_TEXTURE_2D, 0, _hoops_HAGPC, width, height, 0, _hoops_GSPP, GL_UNSIGNED_BYTE, null);

			// _hoops_PPRII _hoops_SGH _hoops_AGCR _hoops_HRP _hoops_IS _hoops_SRCH _hoops_SISPR _hoops_IS _hoops_CPGPC _hoops_SPGPC (_hoops_PGAP _hoops_HRGR _hoops_CPPPR _hoops_HIAC)
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			_hoops_GGPRR = H3DTEXF_POINT;
			_hoops_RGPRR = H3DTEXF_POINT;
			_hoops_AGPRR = H3DTEXF_NONE;
			_hoops_PGPRR = H3DTADDRESS_CLAMP;
			_hoops_HGPRR = H3DTADDRESS_CLAMP;


			glBindTexture(GL_TEXTURE_2D, _hoops_CRCAC);
		}
	}

	~_hoops_HGCAC()
	{
		if (m_data)
			FREE_ARRAY (m_data, _hoops_CAGPC, unsigned char);
		glDeleteTextures (1, &_hoops_PCC);
	};

	bool Lock(int _hoops_SHGGR, unsigned char ** data)
	{
		_hoops_CAGPC = _hoops_SHGGR;
		ALLOC_ARRAY_CACHED(m_data, _hoops_CAGPC, unsigned char);
		*data = m_data;
		return true;
	}

	bool Lock(H3DRect *_hoops_CGPRR, int level, unsigned char ** data, int * pitch = null)
	{
		if (_hoops_GSSAC == true) {
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"Attempting to lock a locked texture.");
			return false;
		}
		_hoops_GSSAC = true;
		_hoops_IAGPC = level;
		_hoops_GPGPC = true;
		
		// _hoops_CIH _hoops_GII _hoops_RHGS _hoops_PIH
		if (m_data) {
			FREE_ARRAY(m_data, _hoops_CAGPC, unsigned char);
			m_data = null;
		}

		if (_hoops_CGPRR) {
			_hoops_PPGPC = *_hoops_CGPRR;
			_hoops_PPGPC.top = _hoops_CGPRR->bottom;
			_hoops_PPGPC.bottom = _hoops_CGPRR->top;

			_hoops_HPGPC = true;
			_hoops_CAGPC = Abs((_hoops_CGPRR->right - _hoops_CGPRR->left) * (_hoops_CGPRR->bottom - _hoops_CGPRR->top) * _hoops_SSARR);
		}
		else {
			_hoops_HPGPC = false;
			_hoops_CAGPC = _hoops_IRRP * _hoops_CRRP * _hoops_SSARR;
		}

		ALLOC_ARRAY_CACHED(m_data, _hoops_CAGPC, unsigned char);
		*data = m_data;
		
		if (pitch)
			*pitch = _hoops_IRRP * _hoops_SSARR;

		return true;
	}

	bool Lock(H3DRect *_hoops_CGPRR, unsigned char ** data, int * pitch = null)
	{
		return Lock(_hoops_CGPRR, 0, data, pitch);
	}

	void Unlock()
	{
		HOGLData *_hoops_CSRGR = (HOGLData*) _hoops_ISS;
		GLint _hoops_CRCAC = 0;

		glGetIntegerv(GL_TEXTURE_BINDING_2D, &_hoops_CRCAC);
		glBindTexture(GL_TEXTURE_2D, _hoops_PCC);
		
		if (_hoops_RPGPC) {
			glCompressedTexImage2D (GL_TEXTURE_2D, 0, _hoops_HAGPC, 
					_hoops_IRRP, _hoops_CRRP, 0, _hoops_CAGPC, m_data);
		}
		else {
			/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GGRRA _hoops_GHGPC, _hoops_SR _hoops_PIHA _hoops_SRHR _hoops_PIH _hoops_GAR _hoops_HAAI _hoops_GAR _hoops_SR _hoops_SSIAA,
			 * _hoops_GGR _hoops_AGIR _hoops_SR _hoops_HHGC _hoops_IS _hoops_PAAP _hoops_GPGR _hoops_PGHH _hoops_IIGR _hoops_RH _hoops_HH _hoops_ARPP _hoops_PCIA
			 */
			if (_hoops_HPGPC)
				glTexSubImage2D(GL_TEXTURE_2D, _hoops_IAGPC, 
									_hoops_PPGPC.left, 
									_hoops_PPGPC.bottom, 
									_hoops_PPGPC.right - _hoops_PPGPC.left,
									_hoops_PPGPC.top - _hoops_PPGPC.bottom,
									_hoops_GSPP, GL_UNSIGNED_BYTE, m_data);
			else
				glTexImage2D(GL_TEXTURE_2D, _hoops_IAGPC, 
								_hoops_HAGPC, _hoops_IRRP, _hoops_CRRP, 0,
								_hoops_GSPP, GL_UNSIGNED_BYTE, m_data);
		}
		if (m_data) {
			FREE_ARRAY (m_data, _hoops_CAGPC, unsigned char);
			m_data = NULL;
			_hoops_CAGPC = 0;
		}

		_hoops_GSSAC = false;
		glBindTexture(GL_TEXTURE_2D, _hoops_CRCAC);
	}

	void _hoops_APRH()
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		UNREFERENCED(_hoops_CSRGR);

		GLint _hoops_CRCAC;
		_hoops_SAGPC = true;

		_hoops_IHRRC(_hoops_CSRGR, 0);
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &_hoops_CRCAC);
		glEnable( GL_TEXTURE_2D );
		glBindTexture(GL_TEXTURE_2D, _hoops_PCC);
		glGenerateMipmapEXT( GL_TEXTURE_2D );
		glBindTexture(GL_TEXTURE_2D, _hoops_CRCAC);
	}

	bool _hoops_CAAH(_hoops_RCR *txr) {
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		UNREFERENCED(_hoops_CSRGR);

		GLint _hoops_CRCAC;
		GLuint format = GL_RGB, _hoops_CCSGC = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;


		_hoops_IHRRC(_hoops_CSRGR, 0);
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &_hoops_CRCAC);
		glEnable( GL_TEXTURE_2D );
		glBindTexture(GL_TEXTURE_2D, _hoops_PCC);

		switch (txr->_hoops_RHGH->format) {
			case _hoops_AHGH:
				format = GL_LUMINANCE;
				break;
			case _hoops_HHGH:
				format = GL_RGB;
				break;
			case Image_RGBA32:
				format = GL_RGBA;
				_hoops_CCSGC = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;
		}
		glTexImage2D (GL_TEXTURE_2D, 0, _hoops_CCSGC,
				txr->_hoops_RHGH->width,
				txr->_hoops_RHGH->height,
				0, format, GL_UNSIGNED_BYTE,
				(GLvoid *)txr->_hoops_RHGH->_hoops_PHGH);

		glBindTexture(GL_TEXTURE_2D, _hoops_CRCAC);
		return true;
	}

	bool _hoops_SAAH(_hoops_RCR *txr) {
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		UNREFERENCED(_hoops_CSRGR);

		GLint _hoops_CRCAC;
		GLuint format = GL_RGB, _hoops_CCSGC = GL_RGB8;

		_hoops_IHRRC(_hoops_CSRGR, 0);
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &_hoops_CRCAC);
		glEnable( GL_TEXTURE_2D );
		glBindTexture(GL_TEXTURE_2D, _hoops_PCC);

		switch (txr->_hoops_RHGH->format) {
			case _hoops_AHGH:
				format = GL_LUMINANCE;
				break;
			case _hoops_HHGH:
				format = GL_RGB;
				break;
			case Image_RGBA32:
				format = GL_RGBA;
				_hoops_CCSGC = GL_RGBA8;
				break;
		}
		glTexImage2D (GL_TEXTURE_2D, 0, _hoops_CCSGC,
				txr->_hoops_RHGH->width,
				txr->_hoops_RHGH->height,
				0, format, GL_UNSIGNED_BYTE,
				(GLvoid *)txr->_hoops_RHGH->_hoops_PHGH);

		glBindTexture(GL_TEXTURE_2D, _hoops_CRCAC);
		return true;
	}

	/* _hoops_GAGPC _hoops_SASI _hoops_PISRR */
	/********************************/
	void _hoops_SRCAC(int _hoops_RHGPC)
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		UNREFERENCED(_hoops_CSRGR);

		glActiveTexture( GL_TEXTURE0 + _hoops_RHGPC );
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, _hoops_PCC);

		if (_hoops_SAGPC) {
			_hoops_SAGPC = false;
			glGenerateMipmapEXT( GL_TEXTURE_2D );
		}
	}

	GLuint _hoops_AIARH()
	{
		return _hoops_PCC;
	}
};



class _hoops_AHGPC : public H3DCubeTexture
{
private:
	GLuint _hoops_PCC;
	bool _hoops_GSSAC;
	H3DFACE _hoops_PHGPC;
	unsigned char *m_data;

	unsigned int _hoops_CAGPC;

	bool _hoops_SAGPC;
	bool _hoops_GPGPC;

	H3DRect _hoops_PPGPC;
	bool _hoops_HPGPC;

public:
	_hoops_AHGPC(H3DData *h3ddata, 
		unsigned int size, 
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI) :
		H3DCubeTexture(h3ddata, size, _hoops_ICRH, _hoops_GCI, H3DFMT_A8R8G8B8)
	{
		GLint _hoops_CRCAC = 0;
		UNREFERENCED(_hoops_ICRH);
		UNREFERENCED(_hoops_GCI);

		_hoops_ISS = h3ddata;
		m_data = null;
		_hoops_GSSAC = false;
		_hoops_SAGPC = false;
		_hoops_GPGPC = false;
		_hoops_SSARR = 4;
		glGenTextures (1, &_hoops_PCC);
	
		glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &_hoops_CRCAC);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _hoops_PCC);

		for (int i = 0; i < 6; i++) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGBA8, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		}

		glBindTexture(GL_TEXTURE_CUBE_MAP, _hoops_CRCAC);
	}

	~_hoops_AHGPC()
	{
		if (m_data)
			FREE_ARRAY (m_data, _hoops_CAGPC, unsigned char);
		glDeleteTextures (1, &_hoops_PCC);
	};

	bool Lock(H3DFACE face, H3DRect *_hoops_CGPRR, unsigned char ** data, int * pitch = null)
	{
		if (_hoops_GSSAC == true) {
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"Attempting to lock a locked texture.");
			return false;
		}
		_hoops_GSSAC = true;
		_hoops_PHGPC = face;
		_hoops_GPGPC = true;

		if (_hoops_CGPRR) {
			_hoops_PPGPC = *_hoops_CGPRR;
			_hoops_PPGPC.top = _hoops_CGPRR->bottom;
			_hoops_PPGPC.bottom = _hoops_CGPRR->top;
			_hoops_HPGPC = true;
		}
		else
			_hoops_HPGPC = false;
		
		if (!m_data) {
			_hoops_CAGPC = _hoops_IRRP * _hoops_CRRP * _hoops_SSARR;
			ALLOC_ARRAY_CACHED(m_data, _hoops_CAGPC, unsigned char);
		}
		*data = m_data;
		
		if (pitch)
			*pitch = _hoops_IRRP * _hoops_SSARR;

		return true;
	}

	void Unlock(H3DFACE face)
	{
		GLint _hoops_CRCAC = 0;
		ASSERT(_hoops_PHGPC == face);	// _hoops_IPIH, _hoops_PAH _hoops_RGAR _hoops_AAHS _hoops_PPR _hoops_SSIAA _hoops_SPR _hoops_HSP _hoops_HPGR _hoops_IRS _hoops_GHIR

		glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &_hoops_CRCAC);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _hoops_PCC);
		
		/* _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GGRRA _hoops_GHGPC, _hoops_SR _hoops_PIHA _hoops_SRHR _hoops_PIH _hoops_GAR _hoops_HAAI _hoops_GAR _hoops_SR _hoops_SSIAA,
		 * _hoops_GGR _hoops_AGIR _hoops_SR _hoops_HHGC _hoops_IS _hoops_PAAP _hoops_GPGR _hoops_PGHH _hoops_IIGR _hoops_RH _hoops_HH _hoops_ARPP _hoops_PCIA
		 */
		if (_hoops_HPGPC)
			glTexSubImage2D(_hoops_GSCAC(face), 0, 
								_hoops_PPGPC.left, 
								_hoops_PPGPC.bottom, 
								_hoops_PPGPC.right - _hoops_PPGPC.left,
								_hoops_PPGPC.top - _hoops_PPGPC.bottom,
								GL_RGBA, GL_UNSIGNED_BYTE, m_data);
		else
			glTexSubImage2D(_hoops_GSCAC(face), 0, 
								0,0,_hoops_IRRP, _hoops_CRRP,
								GL_RGBA, GL_UNSIGNED_BYTE, m_data);

		_hoops_GSSAC = false;
		glBindTexture(GL_TEXTURE_CUBE_MAP, _hoops_CRCAC);

		if (m_data) {
			FREE_ARRAY (m_data, _hoops_CAGPC, unsigned char);
			m_data = null;
		}
	}

	void _hoops_APRH()
	{
		_hoops_SAGPC = true;
	}

	GLuint _hoops_AIARH()
	{
		return _hoops_PCC;
	}
};



class _hoops_HHGPC : public H3DTexture3D
{
private:
	GLuint _hoops_PCC;
	GLuint _hoops_GSPP, _hoops_HAGPC;
	bool _hoops_GSSAC;
	H3DFACE _hoops_PHGPC;
	unsigned char *m_data;

	unsigned int _hoops_CAGPC;

	bool _hoops_SAGPC;
	bool _hoops_GPGPC;

	H3DRect _hoops_PPGPC;
	bool _hoops_HPGPC;

public:
	_hoops_HHGPC(H3DData *h3ddata, 
		unsigned int w, 
		unsigned int h, 
		unsigned int depth, 
		unsigned int _hoops_ICRH,
		unsigned int _hoops_GCI, 
		H3DFORMAT format) :
		H3DTexture3D(h3ddata, w, h, depth, _hoops_ICRH, _hoops_GCI, format)
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		GLint _hoops_CRCAC = 0;
		UNREFERENCED(_hoops_ICRH);
		UNREFERENCED(_hoops_GCI);

		_hoops_ISS = h3ddata;
		m_data = null;
		_hoops_GSSAC = false;
		_hoops_SAGPC = false;
		_hoops_GPGPC = false;
		_hoops_SSARR = 4;

		_hoops_GSPP = 0;
		_hoops_HAGPC = 0; 

		switch (format) {
			case H3DFMT_L8:
				_hoops_GSPP = GL_LUMINANCE;
				_hoops_HAGPC = 1;
				_hoops_SSARR = 1;
				break;
			case H3DFMT_R8G8B8:
				_hoops_GSPP = GL_RGB;
				_hoops_HAGPC = GL_RGB8;
				if (h3ddata->_hoops_CHGH)
					_hoops_SSARR = 3;
				else
					_hoops_SSARR = 4;
				break;
			case H3DFMT_A8R8G8B8:
				_hoops_GSPP = GL_RGBA;
				_hoops_HAGPC = GL_RGBA8;
				_hoops_SSARR = 4;
				break;
			case H3DFMT_DXT1:
			case H3DFMT_DXT3:
			case H3DFMT_DXT5:
			default:
				HE_ERROR(HEC_INTERNAL_ERROR, HEC_INTERNAL_ERROR,
					"Internal error: Unhandled texture type in opengl2 driver.");
		}

		glGenTextures (1, &_hoops_PCC);
		glGetIntegerv(GL_TEXTURE_3D, &_hoops_CRCAC);
		glBindTexture(GL_TEXTURE_3D, _hoops_PCC);

		glTexImage3D(GL_TEXTURE_3D, 0, _hoops_HAGPC, w, h, depth, 0, _hoops_GSPP, GL_UNSIGNED_BYTE, null);

		glBindTexture(GL_TEXTURE_3D, _hoops_CRCAC);
	}

	virtual ~_hoops_HHGPC()
	{
		if (m_data)
			FREE_ARRAY (m_data, _hoops_CAGPC, unsigned char);
		glDeleteTextures (1, &_hoops_PCC);
	};

	bool Lock(unsigned char ** data, int *_hoops_SRAH, int *_hoops_GAAH)
	{
		if (_hoops_GSSAC == true) {
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"Attempting to lock a locked texture.");
			return false;
		}
		_hoops_GSSAC = true;
		_hoops_GPGPC = true;
		*_hoops_SRAH = 0;
		*_hoops_GAAH = 0;
		
		if (!m_data) {
			_hoops_CAGPC = _hoops_IRRP * _hoops_CRRP * m_depth * _hoops_SSARR;
			ALLOC_ARRAY_CACHED(m_data, _hoops_CAGPC, unsigned char);
		}
		*data = m_data;
		
		return true;
	}

	void Unlock()
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		GLint _hoops_CRCAC = 0;

		glGetIntegerv(GL_TEXTURE_BINDING_3D, &_hoops_CRCAC);
		glBindTexture(GL_TEXTURE_3D, _hoops_PCC);
		
		glTexSubImage3D(GL_TEXTURE_3D, 0, 
							0, 0, 0, _hoops_IRRP, _hoops_CRRP, m_depth,
							_hoops_GSPP, GL_UNSIGNED_BYTE, m_data);

		_hoops_GSSAC = false;
		glBindTexture(GL_TEXTURE_3D, _hoops_CRCAC);

		if (m_data) {
			FREE_ARRAY (m_data, _hoops_CAGPC, unsigned char);
			_hoops_CAGPC = 0;
			m_data = null;
		}
	}

	void _hoops_APRH()
	{
		_hoops_SAGPC = true;
	}


	/* _hoops_GAGPC _hoops_SASI _hoops_PISRR */
	/********************************/
	void _hoops_SRCAC(int _hoops_RHGPC)
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		UNREFERENCED(_hoops_CSRGR);

		glActiveTexture( GL_TEXTURE0 + _hoops_RHGPC );
		glEnable( GL_TEXTURE_3D );
		glBindTexture( GL_TEXTURE_3D, _hoops_PCC );
	}

	GLuint _hoops_AIARH()
	{
		return _hoops_PCC;
	}
};


/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_IHGPC _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
GLuint _hoops_CHGPC(H3DRenderTarget *texture) {
	if (texture && texture->_hoops_CSARR()) {
		H3DTexture *_hoops_CIGH = (H3DTexture *)texture;

		if (_hoops_CIGH->_hoops_SGPRR())
			return ((_hoops_AHGPC *) texture)->_hoops_AIARH();
		else if (_hoops_CIGH->_hoops_GRPRR())
			return ((_hoops_HHGPC *) texture)->_hoops_AIARH();
		else
			return ((_hoops_HGCAC *) texture)->_hoops_AIARH();
	}
	else
		return 0;
}

GLenum _hoops_SHGPC(H3DRenderTarget *texture) {
	if (texture && texture->_hoops_CSARR()) {
		H3DTexture *_hoops_CIGH = (H3DTexture *)texture;

		if (_hoops_CIGH->_hoops_SGPRR())
			return GL_TEXTURE_CUBE_MAP;
		else if (_hoops_CIGH->_hoops_GRPRR())
			return GL_TEXTURE_3D;
		else
			return GL_TEXTURE_2D;
	}
	else
		return 0;
}	

static const GLenum _hoops_GIGPC[] = { 
	GL_COLOR_ATTACHMENT0_EXT, 
	GL_COLOR_ATTACHMENT1_EXT,
	GL_COLOR_ATTACHMENT2_EXT, 
	GL_COLOR_ATTACHMENT3_EXT
};

class HOGLFrameBufferObject
{
public:
	HOGLData *_hoops_PHIAC;
	GLuint _hoops_CGIAC;

	// _hoops_PIAH _hoops_HCSS
	H3DRenderTarget *_hoops_HHIAC[4];
	H3DRenderTarget *m_depth;
	H3DRenderTarget *_hoops_RIGPC;

	// _hoops_RCPGR _hoops_PIAH _hoops_HCSS
	H3DRenderTarget *_hoops_AIGPC[4];
	H3DRenderTarget *_hoops_PIGPC;
	H3DRenderTarget *_hoops_HIGPC;

	H3DRenderTarget *_hoops_IIGPC;
	bool _hoops_CIGPC;

public:
	HOGLFrameBufferObject(HOGLData *_hoops_CSRGR) 
	{
		_hoops_PHIAC = _hoops_CSRGR;
		_hoops_CGIAC = 0;
		_hoops_HHIAC[0] = null;
		_hoops_HHIAC[1] = null;
		_hoops_HHIAC[2] = null;
		_hoops_HHIAC[3] = null;
		m_depth = null;
		_hoops_RIGPC = null;

		_hoops_CIGPC = true;
		_hoops_IIGPC = null;

		glGenFramebuffersEXT(1, &_hoops_CGIAC);
		_hoops_IHIAC(_hoops_CSRGR, _hoops_CGIAC);
	}

	~HOGLFrameBufferObject()
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		glDeleteFramebuffersEXT(1, &_hoops_CGIAC);
	}

	bool _hoops_HAIAC(bool _hoops_SIGPC = true)
	{
		return _hoops_ASRAC(_hoops_SIGPC);
	}

	bool _hoops_ASRAC(bool _hoops_SIGPC = true) 
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC;
		_hoops_IHIAC(_hoops_CSRGR, _hoops_CGIAC);

		// _hoops_HHPR _hoops_GPGR _hoops_AHCS
		int _hoops_GSARH = 0;
		if (_hoops_HHIAC[0]) _hoops_GSARH++;
		if (_hoops_HHIAC[1]) _hoops_GSARH++;
		if (_hoops_HHIAC[2]) _hoops_GSARH++;
		if (_hoops_HHIAC[3]) _hoops_GSARH++;
		glDrawBuffers(_hoops_GSARH, _hoops_GIGPC);

		GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		if (status != GL_FRAMEBUFFER_COMPLETE_EXT) {
			char _hoops_GCGPC[1024];
			char _hoops_RCGPC[1024];

			switch (status) {
				case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
					sprintf(_hoops_GCGPC, "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT");
					break;
				case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
					sprintf(_hoops_GCGPC, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT");
					break;
				case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
					sprintf(_hoops_GCGPC, "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT");
					break;
				case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
					sprintf(_hoops_GCGPC, "GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT");
					break;
				case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
					sprintf(_hoops_GCGPC, "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT");
					break;
				case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
					sprintf(_hoops_GCGPC, "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT");
					break;
				case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT:
					sprintf(_hoops_GCGPC, "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT");
					break;
				case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
					sprintf(_hoops_GCGPC, "GL_FRAMEBUFFER_UNSUPPORTED_EXT");
					break;
				case 0:
					status = glGetError();
					return false;
			}

			sprintf(_hoops_RCGPC, "Failed to set up frame buffer object.  \nFramebuffer status: %s", _hoops_GCGPC);
			if (_hoops_SIGPC)
				HE_ERROR(_hoops_CSRGR->_hoops_HSRH, _hoops_CSRGR->_hoops_HSRH,
					_hoops_RCGPC);
			return false;
		}


		// _hoops_CGP _hoops_PPGAR, _hoops_SR _hoops_RRP _hoops_IS _hoops_HIAP _hoops_IRS _hoops_CIAGR _hoops_AAIP _hoops_GAR _hoops_RH _hoops_RRGR _hoops_GSSS _hoops_CAPR _hoops_IS _hoops_SHH _hoops_HIAP
		int _hoops_ACGPC=0, _hoops_PCGPC=0;
		if (_hoops_HHIAC[0]) {
			_hoops_ACGPC = _hoops_HHIAC[0]->_hoops_IRRP;
			_hoops_PCGPC = _hoops_HHIAC[0]->_hoops_CRRP;
		}
		else if (m_depth) {
			_hoops_ACGPC = m_depth->_hoops_IRRP;
			_hoops_PCGPC = m_depth->_hoops_CRRP;
		}

		if (_hoops_PHIAC->_hoops_IHP) {
			_hoops_ACGPC /= _hoops_PHIAC->_hoops_HSAA;
			_hoops_PCGPC /= _hoops_PHIAC->_hoops_ISAA;
		}

		_hoops_HHRS(_hoops_PHIAC, 0, 0, _hoops_ACGPC, _hoops_PCGPC);
		_hoops_SIPRR(_hoops_PHIAC, false);

		return true;
	}

#define _hoops_HCGPC(target,_hoops_CSC) _hoops_GHIA(\
	if (target == _hoops_CSC) \
		return; \
	_hoops_CSC = target; \
)

	void _hoops_IGIAC(GLuint _hoops_HGIAC, H3DRenderTarget *target)
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		_hoops_IHIAC(_hoops_CSRGR, _hoops_CGIAC);

		if (_hoops_HGIAC == GL_COLOR_ATTACHMENT0_EXT &&
			target != _hoops_CSRGR->_hoops_CACAC)
			_hoops_IIGPC = target;

		if (!_hoops_CIGPC && target != _hoops_CSRGR->_hoops_CACAC)
			return;

		switch(_hoops_HGIAC) {
			case GL_COLOR_ATTACHMENT0_EXT:
				_hoops_HCGPC(target, _hoops_HHIAC[0]);
				break;
			case GL_COLOR_ATTACHMENT1_EXT:
				_hoops_HCGPC(target, _hoops_HHIAC[1]);
				break;
			case GL_COLOR_ATTACHMENT2_EXT:
				_hoops_HCGPC(target, _hoops_HHIAC[2]);
				break;
			case GL_COLOR_ATTACHMENT3_EXT:
				_hoops_HCGPC(target, _hoops_HHIAC[3]);
				break;
			case GL_DEPTH_ATTACHMENT_EXT:
				_hoops_HCGPC(target, m_depth);
				break;
			case GL_STENCIL_ATTACHMENT_EXT:
				_hoops_HCGPC(target, _hoops_RIGPC);
				break;
			case GL_DEPTH_STENCIL_EXT:
				_hoops_HCGPC(target, m_depth);
				_hoops_HCGPC(target, _hoops_RIGPC);
				break;
		}

		if (target) {
			if (target->_hoops_CSARR()) {
				glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, _hoops_HGIAC, GL_TEXTURE_2D, _hoops_CHGPC(target), 0);
				glGetError();
			}
			else {
				GLuint buffer, _hoops_ICGPC;
				_hoops_RGIAC *_hoops_CCGPC = (_hoops_RGIAC *) target;

				// _hoops_RPP _hoops_SR _hoops_HS _hoops_SCGPC, _hoops_PSCR _hoops_SR _hoops_HS _hoops_GIAH _hoops_HCH _hoops_PPR _hoops_APSP _hoops_PSCA
				if (_hoops_HGIAC == GL_DEPTH_STENCIL_EXT) {
					buffer = _hoops_ICGPC = _hoops_CCGPC->_hoops_IIARH();

					if (_hoops_CCGPC->_hoops_PAGPC() != 0)
						_hoops_ICGPC = _hoops_CCGPC->_hoops_PAGPC();

					glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, buffer);
					glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _hoops_ICGPC);
				}
				else {
					buffer = _hoops_CCGPC->_hoops_IIARH();
					glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, _hoops_HGIAC, GL_RENDERBUFFER_EXT, buffer);
				}
			}
		}
		else {
			if (_hoops_HGIAC == GL_DEPTH_STENCIL_EXT) {
				glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, 0);
				glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, 0);
			}
			else
				glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, _hoops_HGIAC, GL_RENDERBUFFER_EXT, 0);
		}
	}

	void _hoops_GSGPC(bool mode)
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_PHIAC;
		if (mode != _hoops_CIGPC) {
			_hoops_CIGPC = mode;

			if (mode) {
				_hoops_IGIAC(GL_COLOR_ATTACHMENT0_EXT,_hoops_IIGPC);
			}
			else {
				_hoops_IGIAC(GL_COLOR_ATTACHMENT0_EXT,_hoops_CSRGR->_hoops_CACAC);
			}
			_hoops_HAIAC();
		}
	}

	void _hoops_APIAC()
	{
		_hoops_AIGPC[0] = _hoops_HHIAC[0];
		_hoops_AIGPC[1] = _hoops_HHIAC[1];
		_hoops_AIGPC[2] = _hoops_HHIAC[2];
		_hoops_AIGPC[3] = _hoops_HHIAC[3];
		_hoops_PIGPC = m_depth;
		_hoops_HIGPC = _hoops_RIGPC;
	}

	void _hoops_RHIAC()
	{
		_hoops_IGIAC(GL_COLOR_ATTACHMENT0_EXT, _hoops_AIGPC[0]);
		_hoops_IGIAC(GL_COLOR_ATTACHMENT1_EXT, _hoops_AIGPC[1]);
		_hoops_IGIAC(GL_COLOR_ATTACHMENT2_EXT, _hoops_AIGPC[2]);
		_hoops_IGIAC(GL_COLOR_ATTACHMENT3_EXT, _hoops_AIGPC[3]);
		_hoops_IGIAC(GL_DEPTH_ATTACHMENT_EXT, _hoops_PIGPC);
		_hoops_IGIAC(GL_STENCIL_ATTACHMENT_EXT, _hoops_HIGPC);
	}
};

/*****************************************************************************
*****************************************************************************
					_hoops_GR: _hoops_GRCAC _hoops_ISHGR
*****************************************************************************
*****************************************************************************/
class _hoops_AHIAC : public H3DActions
{
private:
	HOGLData *_hoops_PHIAC;

public:
	_hoops_AHIAC(){};
	_hoops_AHIAC(HOGLData *_hoops_CSRGR) : 
		H3DActions(_hoops_CSRGR),
		_hoops_PHIAC(_hoops_CSRGR) {};
	~_hoops_AHIAC(){};

	void _hoops_ASCRR(wchar_t const *string){ 
		UNREFERENCED(string);
	}
	void _hoops_PSCRR(wchar_t const *string){ 
		UNREFERENCED(string);
	}
	bool _hoops_HSCRR(size_t _hoops_HHARR)
	{
		return (HOOPS_WORLD->display_list_vram_usage + HOOPS_WORLD->_hoops_SARH + (size_t)(_hoops_HHARR) < HOOPS_WORLD->_hoops_PHARR);
	}
	H3DVertexBufferCache *_hoops_HAIH() {return NEW(_hoops_IISAC)();}
	H3DIndexBufferCache *_hoops_SRPRR() {return NEW(_hoops_PSSAC)();}
	H3DIndexedBufferObject *_hoops_PRAS() {return NEW(HOGLIndexedBufferObject)();}

	void SetViewport(H3DViewport const *_hoops_APPRR) 
	{
		H3DViewport _hoops_PAPH = *_hoops_APPRR;
		if ( _hoops_PHIAC->_hoops_IHP ) {
			_hoops_PAPH.X *= _hoops_PHIAC->_hoops_HSAA;
			_hoops_PAPH.Y *= _hoops_PHIAC->_hoops_ISAA;
			_hoops_PAPH.Width *= _hoops_PHIAC->_hoops_HSAA;
			_hoops_PAPH.Height *= _hoops_PHIAC->_hoops_ISAA;
		}
		glViewport(_hoops_PAPH.X, _hoops_PAPH.Y, _hoops_PAPH.Width, _hoops_PAPH.Height);
	}

	void Clear(int flags, int color, float _hoops_CCCRR, int _hoops_SCCRR, bool _hoops_GSCRR)
	{
		_hoops_GPRP(_hoops_PHIAC, H3DMASK_RGBA);

		float a = ((color & 0xff000000) >> 24) / 255.0f;
		float b = ((color & 0xff0000) >> 16) / 255.0f;
		float g = ((color & 0xff00) >> 8) / 255.0f;
		float r = (color & 0xff) / 255.0f;
		GLbitfield _hoops_HIHAH = _hoops_PCCAC(flags);

		if (_hoops_GSCRR) {
			glClearColor(r, g, b, a);
			glClearStencil(_hoops_SCCRR);
			glClearDepth(_hoops_CCCRR);
			glClear(_hoops_HIHAH);
			return;
		}

		// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_HCH _hoops_AGI, _hoops_GA'_hoops_RA _hoops_SCAC _hoops_RH _hoops_HCH _hoops_HH _hoops_IS _hoops_RH _hoops_GISH _hoops_PIRA.
		_hoops_PPRS _hoops_HPRS = { { NULL, NULL, NULL, NULL }, NULL };
		if ( _hoops_PHIAC->_hoops_II.mode && !_hoops_PHIAC->_hoops_PI.mode ) {
			_hoops_IPRS(&_hoops_HPRS);
			_hoops_GPAP(_hoops_HPRS._hoops_PGRGR[0], _hoops_HPRS.depth_stencil);
		}

		// _hoops_CAAP _hoops_RH _hoops_HAIR _hoops_SAAP _hoops_PPR _hoops_AHCR/_hoops_APSP _hoops_HCAGR _hoops_AIH _hoops_RAPA.
		glClearColor(r, g, b, a);
		glClearStencil(_hoops_SCCRR);
		glClearDepth(_hoops_CCCRR);
		glClear(_hoops_HIHAH);

		// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_GRP _hoops_HCH _hoops_AGI, _hoops_SR _hoops_RRP _hoops_IS _hoops_PPSI _hoops_ISSC _hoops_RH _hoops_RHGS _hoops_HCSS.
		if ( _hoops_PHIAC->_hoops_II.mode && !_hoops_PHIAC->_hoops_PI.mode ) {
			// _hoops_CGP _hoops_RH _hoops_HCH _hoops_SRHR _hoops_CSAP _hoops_GCGSP, _hoops_SCAC _hoops_RH _hoops_HCH _hoops_HH _hoops_IS _hoops_IRS _hoops_PIS _hoops_HAIR _hoops_PIRA.
			if ( flags & H3DCLEAR_ZBUFFER ) {
				// _hoops_CGP _hoops_SR'_hoops_ASAR _hoops_HSSGR _hoops_IS _hoops_RH _hoops_SGIP _hoops_IPPA, _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_GA'_hoops_RA _hoops_RHHR _hoops_SCH.
				if( _hoops_CCCRR == 1.0f )
					_hoops_CCCRR = 254.0f/255.0f;

				_hoops_GPAP(_hoops_HPRS._hoops_PGRGR[1]);

				float packed[4];
				_hoops_HSRP(_hoops_CCCRR, packed);
				glClearColor(packed[0], packed[1], packed[2], packed[3]);
				//_hoops_RSGPC(_hoops_ASGPC, _hoops_ASGPC, _hoops_ASGPC, _hoops_ASGPC);

				glClearStencil(0);
				glClearDepth(0);
				glClear(GL_COLOR_BUFFER_BIT);
			}

			// _hoops_IPRP _hoops_GIGR _hoops_HCSS.
			_hoops_PHIAC->_hoops_GSCR->_hoops_CHRS(&_hoops_HPRS);
		}
	}

	H3DPost *_hoops_HCCRR();

	void _hoops_GGSS (float _hoops_RGSRR, float _hoops_SICS) {
		glPolygonOffset(_hoops_SICS, _hoops_RGSRR);
	}

	/*******************/
	/* _hoops_GGPR _hoops_IIHAH */
	/*******************/
	H3DShader *_hoops_ICCRR(H3DShaderID id) 
	{
		return NEW(_hoops_PIIAC)(id);
	};

	/********************/
	/* _hoops_GRAR _hoops_IIHAH */
	/********************/

	bool _hoops_GSAC(const Net_Rendition &nr, _hoops_RCR *txr, int _hoops_GCI, H3DTexture *id, int _hoops_GRRA);

	bool CreateTexture(unsigned int width, unsigned int height, unsigned int _hoops_ICRH, unsigned int _hoops_GCI, H3DFORMAT format, H3DTexture **id)
	{
		*id = NEW(_hoops_HGCAC)(_hoops_PHIAC, width, height, _hoops_ICRH, _hoops_GCI, format);
		return true;
	}
	bool CreateCubeTexture(unsigned int size, unsigned int _hoops_ICRH, unsigned int _hoops_GCI, H3DCubeTexture **id)
	{
		*id = NEW(_hoops_AHGPC)(_hoops_PHIAC,size, _hoops_ICRH, _hoops_GCI);
		return true;
	}
	bool _hoops_PSRH(unsigned int w, unsigned int h, unsigned int depth, unsigned int _hoops_ICRH, unsigned int _hoops_GCI, H3DFORMAT format, H3DTexture3D **id)
	{
		*id = NEW(_hoops_HHGPC)(_hoops_PHIAC, w, h, depth, _hoops_ICRH, _hoops_GCI, format);
		return true;
	}
	bool CreateRenderTarget(unsigned int width, unsigned int height, unsigned int _hoops_GCI, H3DFORMAT format, unsigned int _hoops_ISARR, H3DRenderTarget **id)
	{
		*id = NEW(_hoops_RGIAC)(_hoops_PHIAC, width, height, _hoops_GCI, format, _hoops_ISARR);
		return true;
	}
	void SetTexture(int _hoops_RHIA, H3DTexture *id)
	{	
		_hoops_SCCR(_hoops_ISS, _hoops_RHIA, id);
	}

	/******************/
	/* _hoops_CIHAH _hoops_PGSI */
	/******************/
	void create_region (Net_Rendition const &  nr,
			Int_Rectangle const * area, void **image, void **z);

	void _hoops_HIPGR (Net_Rendition const &  nr,
			Int_Rectangle const * area, void alter * image, void alter * z);

	void _hoops_PIPGR (Net_Rendition const &  nr,
			Int_Rectangle const * area, void alter * image, void alter * z);

	void _hoops_ISPGR (Display_Context alter * dc,
			void alter * image, void alter * z);


	/********************/
	/* _hoops_SIHAH */
	/********************/
	void _hoops_IPRS (_hoops_PPRS *_hoops_HPRS);
	void _hoops_CHRS (_hoops_PPRS *_hoops_HPRS, bool release = true);

	void _hoops_GPAP (
		H3DRenderTarget		*_hoops_ISCRR, 
		H3DRenderTarget		*_hoops_AASP = null,
		H3DRenderTarget		*_hoops_CSCRR = null, 
		H3DRenderTarget		*_hoops_SSCRR = null, 
		H3DRenderTarget		*_hoops_GGSRR = null);

	bool _hoops_PHCS (H3DRenderTarget *_hoops_ISCRR, H3DRenderTarget *_hoops_AASP = null, H3DRenderTarget *_hoops_CSCRR = null, H3DRenderTarget *_hoops_SSCRR = null, H3DRenderTarget *_hoops_GGSRR = null );

	/************************/
	/* _hoops_IPSRH _hoops_PIAP "_hoops_HHSA" */
	/************************/
	void _hoops_SPPRR(bool mode)
	{
		if (mode){
			glEnable (GL_ALPHA_TEST);
			glAlphaFunc (GL_GEQUAL, 0.05f);
		}
		else
			glDisable(GL_ALPHA_TEST);
		_hoops_PHIAC->_hoops_CSC->_hoops_HRGRR = mode;

	}

	void _hoops_RHPRR(bool mode)
	{
		_hoops_PHIAC->_hoops_CSC->antialias = mode;
		if (mode)
			glEnable (GL_MULTISAMPLE_ARB);
		else
			glDisable (GL_MULTISAMPLE_ARB);
	}

	void _hoops_GHHRR(H3DBLEND src, H3DBLEND _hoops_PCAP)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_PHSS = src;
		_hoops_PHIAC->_hoops_CSC->_hoops_IHSS = _hoops_PCAP;
		glBlendFunc(_hoops_ACCAC(src),_hoops_ACCAC(_hoops_PCAP));
	}

	void _hoops_PHPRR(bool mode)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_RAIH = mode;
		if (true || !_hoops_PHIAC->fbo) {
			if (mode)
				glColorMask (BIT(_hoops_PHIAC->_hoops_CSC->_hoops_GRPP,H3DMASK_R), 
							BIT(_hoops_PHIAC->_hoops_CSC->_hoops_GRPP,H3DMASK_G), 
							BIT(_hoops_PHIAC->_hoops_CSC->_hoops_GRPP,H3DMASK_B), 
							BIT(_hoops_PHIAC->_hoops_CSC->_hoops_GRPP,H3DMASK_A));
			else
				glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		}
		else {
			_hoops_PHIAC->fbo->_hoops_GSGPC(mode);
		}
	}

	void _hoops_IHPRR(int mode)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_GRPP = mode;
		if (_hoops_PHIAC->_hoops_CSC->_hoops_RAIH)
			glColorMask (BIT(mode,H3DMASK_R), BIT(mode,H3DMASK_G), BIT(mode,H3DMASK_B), BIT(mode,H3DMASK_A));
		else
			glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	}

	void _hoops_CHPRR(bool mode)
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC;
		UNREFERENCED(_hoops_CSRGR);

		_hoops_PHIAC->_hoops_CSC->_hoops_AAIH = mode;
		glDepthMask ((GLboolean)mode);

		if (_hoops_PHIAC->_hoops_II.mode) {
			if (mode) {
				int _hoops_PGRGR = 0;
				while(_hoops_PHIAC->fbo->_hoops_HHIAC[_hoops_PGRGR])
					_hoops_PGRGR++;
				glDrawBuffers(_hoops_PGRGR, _hoops_GIGPC);
			}
			else {
				glDrawBuffers(1, _hoops_GIGPC);
			}
		}
	}

	void _hoops_GIPRR(float _hoops_RICR, float _hoops_AICR)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_GSCH[0] = _hoops_RICR;
		_hoops_PHIAC->_hoops_CSC->_hoops_GSCH[1] = _hoops_AICR;
		glDepthRange(_hoops_RICR,_hoops_AICR);
	}

	void _hoops_CSPRR(bool mode)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_HSAC = mode;
		if (mode)
			glEnable (GL_BLEND);
		else
			glDisable (GL_BLEND);
	}

	void _hoops_CCHC(H3DCULL mode)
	{
		if (mode == H3DCULL_NONE)
			_hoops_PHIAC->_hoops_APH = false;
		else
			_hoops_PHIAC->_hoops_APH = true;
		_hoops_PHIAC->_hoops_CSC->_hoops_HRSA = mode;
		
		if (_hoops_PHIAC->_hoops_APH) {
			glCullFace (_hoops_HCCAC(mode));
			glEnable (GL_CULL_FACE);
		}
		else
			glDisable (GL_CULL_FACE);
	}

	void _hoops_HIPRR (Net_Rendition const & nr, bool mode)
	{
		// _hoops_PSP _hoops_RSAHH _hoops_PGGA _hoops_CCPGC _hoops_AIRRR _hoops_PIHA _hoops_IHAAR _hoops_PAIR
		UNREFERENCED(nr);
		UNREFERENCED(mode);
	}

	void _hoops_PGHRR (bool _hoops_AGHRR, float _hoops_CCGH, float _hoops_ICGH)
	{
		HOGLData *_hoops_CSRGR = _hoops_PHIAC;
		GLint _hoops_CRCAC = 0;
		char data[4];
		memset(data, 0, sizeof(data));

		if (_hoops_AGHRR)
			glEnable(GL_POINT_SPRITE);
		else
			glDisable(GL_POINT_SPRITE);
	
		_hoops_IHRRC(_hoops_CSRGR, 0);
		glEnable(GL_TEXTURE_2D);
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &_hoops_CRCAC);

		if (_hoops_CSRGR->_hoops_IPCAC == null) {
			_hoops_CSRGR->_hoops_GSCR->CreateTexture(1,1,1,0,H3DFMT_A8R8G8B8,&_hoops_CSRGR->_hoops_IPCAC);

			glBindTexture(GL_TEXTURE_2D, _hoops_CHGPC(_hoops_CSRGR->_hoops_IPCAC));
			_hoops_CSRGR->_hoops_CSC->texture[0] = _hoops_CSRGR->_hoops_IPCAC;

			glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
			glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glTexImage2D( GL_TEXTURE_2D, 0, 4, 1, 1, 0,
				     GL_RGBA, GL_UNSIGNED_BYTE, data );
			_hoops_CSRGR->dc->_hoops_IGGI->_hoops_RPRH++;

			if (_hoops_CRCAC)
				glBindTexture(GL_TEXTURE_2D, _hoops_CRCAC);
		}
		if (!_hoops_CRCAC)
			_hoops_SCCR(_hoops_CSRGR, 0, _hoops_CSRGR->_hoops_IPCAC);
		
		glPointParameteri (GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
		glPointParameterf (GL_POINT_SIZE_MIN_EXT, _hoops_CCGH);
		glPointParameterf (GL_POINT_SIZE_MAX_EXT, _hoops_ICGH);
	}

	void _hoops_RSCR (
		int _hoops_GRRA, 
		H3DTEXTUREFILTERTYPE filter, 
		H3DTEXTUREFILTERTYPE _hoops_PHHRR, 
		H3DTEXTUREADDRESS _hoops_HHHRR)
	{
		_hoops_GAPAH(_hoops_PHIAC, _hoops_GRRA, filter);
		_hoops_RAPAH(_hoops_PHIAC, _hoops_GRRA, filter);
		_hoops_AAPAH(_hoops_PHIAC, _hoops_GRRA, _hoops_PHHRR);
		_hoops_CRPAH(_hoops_PHIAC, _hoops_GRRA, _hoops_HHHRR);
		_hoops_SRPAH(_hoops_PHIAC, _hoops_GRRA, _hoops_HHHRR);
	}

	void _hoops_GCPRR(bool mode)
	{
		if (_hoops_PHIAC->_hoops_HGARR) {
			_hoops_RCPRR(_hoops_PHIAC);
			_hoops_PHIAC->_hoops_CSC->_hoops_IRGRR = mode;
			if (mode)
				glEnable(GL_SCISSOR_TEST);
			else
				glDisable(GL_SCISSOR_TEST);
		}
	}

	void _hoops_SCPRR(int _hoops_PCPRR, int _hoops_HCPRR, int _hoops_ICPRR, int _hoops_CCPRR)
	{
		int width = _hoops_ICPRR - _hoops_PCPRR + 1;
		int height = _hoops_CCPRR - _hoops_HCPRR + 1;

		if ( _hoops_PHIAC->_hoops_IHP ) {
			_hoops_PCPRR *= _hoops_PHIAC->_hoops_HSAA;
			_hoops_HCPRR *= _hoops_PHIAC->_hoops_ISAA;
			width *= _hoops_PHIAC->_hoops_HSAA;
			height *= _hoops_PHIAC->_hoops_ISAA;
		}

		glScissor (_hoops_PCPRR, _hoops_HCPRR, width, height);
	}

	void _hoops_CIPRR(H3DSHADEMODE mode)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_SAGRR = mode;
		glShadeModel(_hoops_ICCAC(mode));
	}

	void _hoops_RSPRR(bool mode)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_PRGRR = mode;
		if (mode)
			glEnable (GL_STENCIL_TEST);
		else
			glDisable (GL_STENCIL_TEST);

	}

	void _hoops_CRHRR(H3DCMPFUNC _hoops_HAGR)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_RGIH = _hoops_HAGR;

		int _hoops_IGIH;
		int _hoops_PGIH;
		glGetIntegerv (GL_STENCIL_VALUE_MASK, (GLint*)(&_hoops_PGIH));
		glGetIntegerv (GL_STENCIL_REF, (GLint*)(&_hoops_IGIH));

		glStencilFunc (_hoops_CCCAC(_hoops_HAGR),_hoops_IGIH,_hoops_PGIH);
	}

	void _hoops_CGHRR(int _hoops_HAGR)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_PGIH = _hoops_HAGR;

		int _hoops_RGIH;
		int _hoops_IGIH;
		glGetIntegerv (GL_STENCIL_FUNC, (GLint*)(&_hoops_RGIH));
		glGetIntegerv (GL_STENCIL_REF, (GLint*)(&_hoops_IGIH));

		glStencilFunc (_hoops_RGIH, _hoops_IGIH, _hoops_HAGR);
	}

	void _hoops_PRHRR(int _hoops_HAGR)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_IGIH = _hoops_HAGR;
		
		int _hoops_RGIH;
		int _hoops_PGIH;
		glGetIntegerv (GL_STENCIL_FUNC, (GLint*)(&_hoops_RGIH));
		glGetIntegerv (GL_STENCIL_VALUE_MASK, (GLint*)(&_hoops_PGIH));
		
		glStencilFunc (_hoops_RGIH, _hoops_HAGR, _hoops_PGIH);
	}

	void _hoops_GRHRR(int _hoops_HAGR)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_IRIH = _hoops_HAGR;
		glStencilMask(_hoops_HAGR);
	}

	void _hoops_AAHRR(H3DSTENCILOP _hoops_AAIS, H3DSTENCILOP _hoops_RAHRR, H3DSTENCILOP pass)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_RRIH = _hoops_AAIS;
		_hoops_PHIAC->_hoops_CSC->_hoops_PRIH = _hoops_RAHRR;
		_hoops_PHIAC->_hoops_CSC->_hoops_SGIH = pass;
		glStencilOp(_hoops_SCCAC(_hoops_AAIS),_hoops_SCCAC(_hoops_RAHRR),_hoops_SCCAC(pass));
	}

	void _hoops_IAHRR(H3DCMPFUNC cmp, unsigned long ref, unsigned long mask, unsigned long _hoops_HAHRR)
	{
		_hoops_PHIAC->_hoops_CSC->_hoops_RGIH = cmp;
		_hoops_PHIAC->_hoops_CSC->_hoops_IGIH = ref;
		_hoops_PHIAC->_hoops_CSC->_hoops_PGIH = mask;

		glStencilFunc(_hoops_CCCAC(cmp), ref, mask);
		if (_hoops_HAHRR != _hoops_PHIAC->_hoops_CSC->_hoops_IRIH)
			_hoops_GRHRR(_hoops_HAHRR);
	}

	void _hoops_PSPRR (int _hoops_RHIA, H3DTexture *texture)
	{
		ASSERT(_hoops_RHIA < H3D_MAX_TEXTURES);

		HOGLData *_hoops_CSRGR = _hoops_PHIAC;
		GLuint _hoops_PSGPC = texture ? _hoops_CHGPC(texture) : 0;
		GLenum _hoops_HSGPC = texture ? _hoops_SHGPC(texture) : _hoops_CSRGR->_hoops_CSC->_hoops_CAGRR[_hoops_RHIA];

		// _hoops_GHSGR _hoops_ISGPC _hoops_HRGR _hoops_APIP
		if (!(_hoops_HSGPC == GL_TEXTURE_1D ||
			_hoops_HSGPC == GL_TEXTURE_2D ||
			_hoops_HSGPC == GL_TEXTURE_3D ||
			_hoops_HSGPC == GL_TEXTURE_CUBE_MAP))
			_hoops_HSGPC = GL_TEXTURE_2D;

		_hoops_IHRRC(_hoops_CSRGR, _hoops_RHIA);
		glBindTexture(_hoops_HSGPC, _hoops_PSGPC);

		_hoops_CSRGR->_hoops_CSC->_hoops_CAGRR[_hoops_RHIA] = _hoops_HSGPC;
		_hoops_CSRGR->_hoops_CSC->texture[_hoops_RHIA] = texture;
		_hoops_CSRGR->dc->_hoops_IGGI->_hoops_GSAC++;

		if (texture)
			texture->_hoops_IGPRR = &_hoops_CSRGR->_hoops_CSC->texture[_hoops_RHIA];
	}

	void _hoops_AGSRR (int _hoops_RHIA, H3DTexture *texture)
	{
		if (_hoops_PHIAC->_hoops_CSC->texture[_hoops_RHIA] != texture)
			_hoops_PSPRR(_hoops_RHIA, texture);
	}

	void _hoops_IPPRR(H3DVertexFormat _hoops_PPCP)
	{
		UNREFERENCED(_hoops_PPCP);
		return;
	}

	void _hoops_GGHRR(bool mode)
	{
		glEnable(GL_DEPTH_TEST);
		_hoops_PHIAC->_hoops_CSC->_hoops_ARGRR = mode;
		if (!mode)
			glDepthFunc(GL_ALWAYS);
		else {
			if (_hoops_PHIAC->_hoops_CSC->_hoops_CRGRR)
				glDepthFunc(GL_GREATER);
			else
				glDepthFunc(GL_LEQUAL);
		}
	}	
	
	void _hoops_GHIP(H3DData				*h3ddata,
									H3DTexture			*texture,
									int					x, 
									int					y, 
									int					width, 
									int					height,
									float				_hoops_ACCRR = 0,
									float				_hoops_ISPI = 0,
									float				_hoops_PCCRR = 1,
									float				_hoops_CSPI = 1);

	void * _hoops_PRHGR(_hoops_AHGR type, const char *source) 
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		int status = 0;
		GLenum _hoops_CSGPC = (type == _hoops_GCGR) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
		GLuint _hoops_SSGPC = glCreateShader(_hoops_CSGPC);

		glShaderSource(_hoops_SSGPC, 1, &source, null);
		glCompileShader(_hoops_SSGPC);

		//_hoops_CI _hoops_HSSI _hoops_IR?
		glGetShaderiv(_hoops_SSGPC, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) {
			char log[1024];
			char err[1024];
			int len = 0;
			glGetShaderInfoLog(_hoops_SSGPC, sizeof(log), &len, log);
			sprintf(err, "User shader error: Compilation error: %s", log);
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER, err);
			return null;
		}

		return (void *) _hoops_SSGPC;
	}

	void _hoops_IRHGR(POINTER_SIZED_INT _hoops_RSR) 
	{
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		glDeleteShader(_hoops_RSR);
	}

	bool _hoops_SRHGR(_hoops_AHGR type, POINTER_SIZED_INT _hoops_RSR)
	{
		bool _hoops_CCHAH = false;
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		if (type == _hoops_GCGR)
			_hoops_ISS->_hoops_GAARR = _hoops_RSR;
		else
			_hoops_ISS->_hoops_RAARR = _hoops_RSR;

		// _hoops_CGP _hoops_SR'_hoops_RISP _hoops_GGHP _hoops_GIPR _hoops_AIRRR _hoops_ARP, _hoops_PSCR _hoops_SGHHR _hoops_IS _hoops_ARPR _hoops_PCCP _hoops_IIC
		if (_hoops_ISS->_hoops_GAARR && _hoops_ISS->_hoops_RAARR &&
			(_hoops_ISS->_hoops_GAARR != _hoops_ISS->_hoops_CRARR ||
			_hoops_ISS->_hoops_RAARR != _hoops_ISS->_hoops_SRARR))
		{
			H3DShaderID id;
			id._hoops_PASRR(_hoops_ISS->_hoops_GAARR, _hoops_ISS->_hoops_RAARR);

			_hoops_PIIAC *_hoops_SCHAH = (_hoops_PIIAC *) _hoops_ISS->_hoops_IP->Lookup (id);
			if (!_hoops_SCHAH) {
				_hoops_SCHAH = (_hoops_PIIAC*)_hoops_ISS->_hoops_GSCR->_hoops_ICCRR(id);
				if (_hoops_SCHAH->Create(_hoops_ISS))
					_hoops_ISS->_hoops_IP->Insert (id, _hoops_SCHAH);
				else
					_hoops_HP(_hoops_SCHAH);
			}

			if (_hoops_SCHAH) {
				_hoops_CSRGR->_hoops_CRSAC = _hoops_SCHAH->_hoops_IASAC();
				glUseProgram(_hoops_CSRGR->_hoops_CRSAC);
				_hoops_SCHAH->_hoops_PCIAC();
			}

			_hoops_CCHAH = true;
		}
		return _hoops_CCHAH;
	}

	void _hoops_RAHGR(_hoops_AHGR type, char const * name, int count, int *data)
	{
		UNREFERENCED(type);
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		if (_hoops_CSRGR->_hoops_CRSAC == 0) {
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"User shader error: Cannot set uniform when user shader is not set!");
			return;
		}

		GLint handle = glGetUniformLocation (_hoops_CSRGR->_hoops_CRSAC, name);
		if (_hoops_CSRGR->_hoops_CRSAC == 0) {
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"User shader error: Uniform name not found in shader.");
			return;
		}

		glUniform1iv(handle, count, data);
	}

	void _hoops_PAHGR(_hoops_AHGR type, char const * name, int count, float *data)
	{
		UNREFERENCED(type);
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		if (_hoops_CSRGR->_hoops_CRSAC == 0) {
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"User shader error: Cannot set uniform when user shader is not set!");
			return;
		}
		GLint handle = glGetUniformLocation (_hoops_CSRGR->_hoops_CRSAC, name);
		if (_hoops_CSRGR->_hoops_CRSAC == 0) {
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"User shader error: Uniform name not found in shader.");
			return;
		}

		glUniform1fv(handle, count, data);
	}

	void _hoops_IAHGR(_hoops_AHGR type, char const * name, int width, int count, float *data)
	{
		UNREFERENCED(type);
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		if (_hoops_CSRGR->_hoops_CRSAC == 0) {
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"User shader error: Cannot set uniform when user shader is not set!");
			return;
		}

		GLint handle = glGetUniformLocation (_hoops_CSRGR->_hoops_CRSAC, name);
		if (_hoops_CSRGR->_hoops_CRSAC == 0) {
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"User shader error: Uniform name not found in shader.");
			return;
		}

		switch(width) {
			case 1: glUniform1fv(handle, count, data);
			case 2:	glUniform2fv(handle, count, data);
			case 3:	glUniform3fv(handle, count, data);
			case 4:	glUniform4fv(handle, count, data);
			default:
				return;			
		}
	}

	void _hoops_SAHGR(_hoops_AHGR type, char const * name, int count, float *data)
	{
		UNREFERENCED(type);
		HOGLData *_hoops_CSRGR = (HOGLData *) _hoops_ISS;
		if (_hoops_CSRGR->_hoops_CRSAC == 0) {
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"User shader error: Cannot set uniform when user shader is not set!");
			return;
		}
		GLint handle = glGetUniformLocation (_hoops_CSRGR->_hoops_CRSAC, name);
		if (_hoops_CSRGR->_hoops_CRSAC == 0) {
			HE_ERROR(HEC_OPENGL_DRIVER, HEC_OPENGL_DRIVER,
				"User shader error: Uniform name not found in shader.");
			return;
		}

		//_hoops_GGRPC(_hoops_RGHH, _hoops_RPR * 16, _hoops_PIH);
		glUniformMatrix4fv(handle, count, false, data);
	}
}; // _hoops_GRCAC

	  
#endif
/*_hoops_RGRPC*/

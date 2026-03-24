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
 * $Id: obf_tmp.txt 1.490 2010-12-09 21:52:14 heppe Exp $
 */



#ifndef OGL_H_DEFINED
#define OGL_H_DEFINED


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

#if _hoops_HRGAC
#include "GL/osmesa.h"
#endif

#ifdef GLX_DRIVER
#define Window X_Window
#define _hoops_PGIIR X_Font
#define Drawable X_Drawable
#define _hoops_RAAH X_Depth
#define _hoops_GSPGR X_Time

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
#ifndef EXCEED_BUILD
/* _hoops_IH _hoops_IGIGC _hoops_IGRIP _hoops_SRGAC */
      typedef Window GLXPbuffer;
      typedef void *GLXFBConfig;
#endif
#define glXChooseFBConfig(x1,x2,_hoops_SSIPA,_hoops_AGCPA) null
#define glXGetVisualFromFBConfig(x1,x2) null
#define glXCreatePbuffer(x1,x2,_hoops_SSIPA) null 
#endif
# define _hoops_GAGAC 256
# define SOLARIS_RESERVED_COLORS 65
#endif

#ifdef WGL_DRIVER
#	include "msw.h"
#endif

#ifdef OSX_SYSTEM

#define Point _hoops_SARRI
#define Style OSX_Style
#define Marker _hoops_GPRRI
#define Polygon _hoops_RPRRI
#define Button OSX_Button
#define Line _hoops_APRRI

#ifdef AGL_DRIVER
# undef local
# undef _hoops_AHRRI
# define _hoops_AHRRI static _hoops_PHRRI /* _hoops_HGASI _hoops_IH _hoops_IRS _hoops_ARPC _hoops_GGR _hoops_RAGAC _hoops_IRAGP */
# include <AGL/agl.h>
# undef local
# define local static
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <Carbon/Carbon.h>
#endif

#ifdef COCOA_OGL_DRIVER

# undef local

# include <ApplicationServices/ApplicationServices.h>
# include <CoreFoundation/CoreFoundation.h>
# include <CoreServices/CoreServices.h>


# define local static

# include <OpenGL/gl.h>
# include <OpenGL/glu.h>


#endif

#undef Point
#undef Style
#undef Marker
#undef Polygon 
#undef Button
#undef Line

#else
# include <GL/gl.h>
# include <GL/glu.h>
#endif




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
#define	_hoops_SAGAC 0x00000010  //_hoops_AA _hoops_HAR _hoops_RPRS _hoops_CCGR _hoops_AGAH 19
#define	_hoops_GPGAC 0x00000020  //_hoops_AA _hoops_HAR _hoops_RPRS _hoops_CCGR _hoops_AGAH 19
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

//#_hoops_PPIP _hoops_HHGAC 
#ifdef _hoops_IHGAC
#  define _hoops_AGHRC(_hoops_RPSHA) \
	OutputDebugString (_hoops_RPSHA); \
	OutputDebugString ("\n"); 
#else
#  define _hoops_AGHRC(_hoops_RPSHA) _hoops_GRSSH(_hoops_RPSHA)
#endif
#define _hoops_RAPRC(_hoops_RPSHA, _hoops_CHGAC) \
	_hoops_AGHRC (_hoops_RPSHA); \
	if (_hoops_CHGAC && BIT(_hoops_CSRGR->dc->options._hoops_IRARR, _hoops_PHGAC)) \
		return;


/* _hoops_HRARR _hoops_SCPGH */

#define XBIT_NONE							0L
#define XBIT_UNDRAW_OVERLAY_FRONT_AND_BACK	1L
#define XBIT_BAD_KTX						2L
#define XBIT_DOUBLE_BUFFER_SWAP_ONLY		3L
#define XBIT_BAD_VERTEX_ARRAYS				4L
#define XBIT_BAD_SCISSORING					5L
#define XBIT_EYE_SPACE_DEPTH				6L
#define XBIT_FORCE_DEFAULT_SOFTWARE			7L
#define XBIT_BAD_OVERLAY					8L
#define XBIT_BAD_STENCIL					9L
#define XBIT_BAD_TRANSPARENT_POINT			10L
#define XBIT_RESTORE_REGION_ZBUFFER_OFF		11L
#define XBIT_BAD_MULTILIGHT					12L
#define XBIT_BAD_DISPLAY_LIST               13L
#define XBIT_FORCE_OLD_CHOOSE_PIXEL_FORMAT  14L
#define XBIT_BAD_PIXEL_STORE                15L
#define XBIT_RASTERS_AS_VERTICES			16L
#define XBIT_ALLOW_DRAWPIXEL_RESTORE		17L
#define XBIT_DOUBLE_BUFFER_COPY_ONLY		18L
#define XBIT_LIES_ABOUT_SWAP				19L
#define XBIT_PIXEL_OPERATIONS_EXPENSIVE		20L /* ***_hoops_SHGAC*** _hoops_IPIH _hoops_IGI _hoops_RGAR _hoops_GGR _hoops_PPPSR-_hoops_IS-_hoops_ICCI _hoops_GIGAC _hoops_HII _hoops_HACIA */
#define XBIT_BAD_PHONG						21L
#define XBIT_BAD_PATTERNED_LINES			22L
#define XBIT_BAD_PBUFFER					23L
#define XBIT_BAD_SPOTLIGHT_TEXTURE			24L
#define XBIT_4142_WORKAROUND				25L
#define XBIT_BAD_TWO_SIDED_LIGHTING			26L
#define XBIT_BAD_FLAT_VERTEX_ARRAYS			27L
#define XBIT_BAD_WGL_ARB_BUFFER				28L
#define XBIT_BAD_MSAA_WGL_ARB_BUFFER		29L
#define XBIT_WGL_ARB_BUFFER_1024_LIMIT		30L
#define XBIT_FLAT_TRISTRIP_MISMATCH			31L
#define XBIT_BAD_NONDL_VERTEX_ARRAYS		32L
#define XBIT_BAD_SINGLE_BUFFERING           33L
#define XBIT_BAD_ACCUMULATION_BUFFER		34L
#define XBIT_BAD_16BIT_ACCUMULATION_BUFFER	35L
#define XBIT_LINE_PATTERN_NEEDS_BLENDING	36L
#define XBIT_SLOW_MSAA_DEPTH_TEXTURE		37L
#define XBIT_BAD_MSAA_ACCUMULATION_BUFFER	38L
#define XBIT_BAD_VERTEX_BUFFER_OBJECT		39L
#define XBIT_BAD_ELEMENT_BUFFER				40L
#define XBIT_BAD_CUT_POINTS					41L
#define XBIT_BAD_FRAGMENT_PROGRAM			42L
#define XBIT_BAD_SEPARATE_SPECULAR			43L
#define XBIT_DELAYED_VERTEX_ARRAYS			44L
#define XBIT_BAD_TEXTURE_RECTANGLE			45L
#define XBIT_BAD_MULTIPLE_CLIP_PLANES		46L
#define XBIT_SLOW_PEELED_LINESMOOTH			47L
#define XBIT_BAD_NON_POWER_OF_2_TEXTURES	48L
#define XBIT_TEXTURE_SIZE_OFF_BY_ONE		49L
//#_hoops_PPIP _hoops_RIGAC			64L // _hoops_CACH _hoops_AIGAC _hoops_GGR _hoops_CHARP._hoops_GGHR

/* _hoops_IRGH _hoops_PIGAC: */


/****************************
* _hoops_HIGAC _hoops_PSCH _hoops_CHCPI
****************************/

#ifdef WGL_DRIVER
	/* _hoops_HGSR */
	typedef const char * (FAR __stdcall * wglGetExtensionsStringARBProc)(HDC _hoops_IIGAC);
	typedef GLboolean (FAR __stdcall * wglChoosePixelFormatARBProc) (HDC _hoops_IIGAC, const int *_hoops_CIGAC, const FLOAT *_hoops_SIGAC, UINT _hoops_GCGAC, int *_hoops_RCGAC, UINT *_hoops_ACGAC);
	typedef GLboolean (FAR __stdcall * wglGetPixelFormatAttribivARBProc) (HDC _hoops_IIGAC, int _hoops_PCGAC, int _hoops_HCGAC, UINT _hoops_ICGAC, const int *_hoops_CCGAC, int *_hoops_SCGAC);
	typedef GLboolean (FAR __stdcall * wglGetPixelFormatAttribfvARBProc) (HDC _hoops_IIGAC, int _hoops_PCGAC, int _hoops_HCGAC, UINT _hoops_ICGAC, const int *_hoops_CCGAC, float *_hoops_GSGAC);
	typedef GLboolean (FAR __stdcall * wglChoosePixelFormatARBProc) (HDC _hoops_IIGAC, const int *_hoops_CIGAC, const FLOAT *_hoops_SIGAC, UINT _hoops_GCGAC, int *_hoops_RCGAC, UINT *_hoops_ACGAC);
	/* _hoops_IAGIP */
	typedef HANDLE (FAR __stdcall * wglCreateBufferRegionARBProc) (HDC hDC, int _hoops_HCGAC, UINT _hoops_RSGAC);
	typedef void (FAR __stdcall * wglDeleteBufferRegionARBProc) (HANDLE region);
	typedef void (FAR __stdcall * wglSaveBufferRegionARBProc) (HANDLE region, GLint x, GLint y, GLsizei width, GLsizei height);
	typedef void (FAR __stdcall * wglRestoreBufferRegionARBProc) (HANDLE region, GLint x, GLint y, GLsizei width, GLsizei height, GLint _hoops_ASGAC, GLint _hoops_PSGAC);
	typedef GLboolean (FAR __stdcall * wglMakeContextCurrentARBProc) (HDC _hoops_HSGAC, HDC _hoops_ISGAC, HGLRC _hoops_CSGAC);
	typedef HANDLE (FAR __stdcall * wglCreatePbufferARBProc) (HDC hDC, int _hoops_PCGAC, int _hoops_SSGAC, int _hoops_GGRAC, const int *_hoops_RGRAC);
	typedef HDC (FAR __stdcall * wglGetPbufferDCARBProc) (HANDLE _hoops_AGRAC);
	typedef int (FAR __stdcall * wglReleasePbufferDCARBProc) (HANDLE _hoops_AGRAC, HDC hDC);
	typedef GLboolean (FAR __stdcall * wglDestroyPbufferARBProc) (HANDLE _hoops_AGRAC);
	typedef GLboolean (FAR __stdcall * wglQueryPbufferARBProc) (HANDLE _hoops_AGRAC);
	typedef GLuint (FAR __stdcall * glNewKTXBufferRegionProc) (GLenum type);
	typedef void (FAR __stdcall * glDeleteKTXBufferRegionProc) (GLuint region);
	typedef void (FAR __stdcall * glReadKTXBufferRegionProc) (GLuint region, GLint x, GLint y, GLsizei width, GLsizei height);
	typedef void (FAR __stdcall * glDrawKTXBufferRegionProc) (GLuint region, GLint x, GLint y, GLsizei width, GLsizei height, GLint _hoops_ASGAC, GLint _hoops_PSGAC);
	typedef GLuint (FAR __stdcall * glKTXBufferRegionEnabledProc) (void);
	/* _hoops_PGRAC */
	typedef void (FAR __stdcall * glActiveTextureARBProc) (GLenum format);
	typedef void (FAR __stdcall * glClientActiveTextureARBProc) (GLenum format);
	typedef void (FAR __stdcall * glMultiTexCoord2fvARBProc) (GLenum format, const GLfloat *);
	typedef void (FAR __stdcall * glMultiTexCoord3fvARBProc) (GLenum format, const GLfloat *);
	/* _hoops_GPHA/_hoops_AIR _hoops_AIRRR */
	typedef void (FAR __stdcall *glGenProgramsARBProc) (GLsizei n, GLuint *programs);
	typedef void (FAR __stdcall *glDeleteProgramsARBProc) (GLsizei n, const GLuint *programs);
	typedef void (FAR __stdcall *glProgramStringARBProc) (GLenum target, GLenum format, GLsizei len, const void *string);
	typedef void (FAR __stdcall *glBindProgramARBProc) (GLenum target, GLuint program);
	typedef void (FAR __stdcall *glProgramEnvParameter4fARBProc) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	/* _hoops_SCRGC _hoops_CI _hoops_AGSAR */
	typedef void (FAR __stdcall *glShaderSourceARBProc) (GLuint _hoops_RSR, GLsizei _hoops_HGRAC, const char **strings, const GLint *lengths);
	typedef void (FAR __stdcall *glCompileShaderARBProc) (GLuint _hoops_RSR);
	typedef void (FAR __stdcall *glGetInfoLogARBProc) (GLuint _hoops_RSR, GLsizei _hoops_IGRAC, GLsizei *length, char *buffer);
	typedef void (FAR __stdcall *glAttachObjectARBProc) (GLuint program, GLuint _hoops_RSR);
	typedef void (FAR __stdcall *glDetachObjectARBProc) (GLuint program, GLuint _hoops_RSR);
	typedef void (FAR __stdcall *glDeleteShaderARBProc) (GLuint _hoops_RSR);
	typedef void (FAR __stdcall *glLinkProgramARBProc) (GLuint program);
	typedef GLuint (FAR __stdcall *glCreateShaderObjectARBProc) (GLenum _hoops_RCS);
	typedef GLuint (FAR __stdcall *glCreateProgramObjectARBProc) (void);
	typedef void (FAR __stdcall *glDeleteProgramARBProc) (GLuint program);
	typedef void (FAR __stdcall *glUseProgramObjectARBProc) (GLuint program);
	typedef void (FAR __stdcall *glGetObjectParameterfvARBProc) (GLuint _hoops_RSR, GLenum pname, GLfloat *params);
	typedef void (FAR __stdcall *glGetObjectParameterivARBProc) (GLuint _hoops_RSR, GLenum pname, GLint *params);
	/* _hoops_SCRGC _hoops_IAGP _hoops_RACGH */
	typedef void (FAR __stdcall *glGenQueriesARBProc) (GLsizei n, GLuint *_hoops_GPICA);
	typedef void (FAR __stdcall *glDeleteQueriesARBProc) (GLsizei n, const GLuint *_hoops_GPICA);
	typedef void (FAR __stdcall *glBeginQueryARBProc) (GLenum target, GLuint id);
	typedef void (FAR __stdcall *glEndQueryARBProc) (GLenum target);
	typedef void (FAR __stdcall *glGetQueryivARBProc) (GLenum target, GLenum pname, GLint *params);
	typedef void (FAR __stdcall *glGetQueryObjectuivARBProc) (GLuint id, GLenum pname, GLuint *params);
	/* _hoops_RSRGC _hoops_IAGP _hoops_RACGH */
	typedef void (FAR __stdcall *glBeginOcclusionQueryNVProc) (GLuint id);
	typedef void (FAR __stdcall *glEndOcclusionQueryNVProc) (void);
	typedef void (FAR __stdcall *glGetOcclusionQueryuivNVProc) (GLuint id, GLenum pname, GLuint *params);
	/* _hoops_RSRGC _hoops_CGRAC */
	typedef void (FAR __stdcall *glGenFencesNVProc)(GLsizei n, GLuint *fences);
	typedef void (FAR __stdcall *glDeleteFencesNVProc)(GLsizei n, const GLuint *fences);
	typedef void (FAR __stdcall *glSetFenceNVProc)(GLuint fence, GLenum condition);
	typedef GLboolean (FAR __stdcall *glTestFenceNVProc)(GLuint fence);
	typedef void (FAR __stdcall *glFinishFenceNVProc)(GLuint fence);
	typedef GLboolean (FAR __stdcall *glIsFenceNVProc)(GLuint fence);
	typedef void (FAR __stdcall *glGetFenceivNVProc)(GLuint fence, GLenum pname, GLint *params);
	/* _hoops_SCRGC _hoops_SGRAC */
	typedef void (FAR __stdcall *glPointParameterfARBProc)(GLenum pname, GLfloat param);
	typedef void (FAR __stdcall *glPointParameterfvARBProc)(GLenum pname, const GLfloat *param);
	/* _hoops_SCRGC _hoops_GRAR _hoops_GRRAC */
	typedef void (FAR __stdcall *glCompressedTexImage2DARBProc)(GLenum target, GLint level, 
				GLenum internalformat, GLsizei width, GLsizei height, 
				GLint border, GLsizei imageSize, const GLvoid *data);
	typedef void (FAR __stdcall *glPrimitiveRestartNVProc)(void);
	typedef void (FAR __stdcall *glPrimitiveRestartIndexNVProc)(GLuint index);
	/* _hoops_SCRGC 3D _hoops_AI */
	typedef void (FAR __stdcall *glTexImage3DProc)(
				GLenum target,  
				GLint level,  
				GLint internalFormat,  
				GLsizei width,  
				GLsizei height,  
				GLsizei depth,  
				GLint border,  
				GLenum format,  
				GLenum type,  
				const GLvoid *data); 
	typedef void (FAR __stdcall *glTexSubImage3DProc)(
				GLenum   target,  
				GLint level,  
				GLint xoffset,  
				GLint yoffset,  
				GLint zoffset,  
				GLsizei width,  
				GLsizei height,  
				GLsizei depth,  
				GLenum format,  
				GLenum type,  
				const GLvoid * data); 

	/* _hoops_RRRAC */
	typedef GLboolean (FAR __stdcall *glIsRenderbufferEXTProc)(GLuint _hoops_ARRAC);
	
	typedef void (FAR __stdcall *glBindRenderbufferEXTProc)(GLenum target, GLuint _hoops_ARRAC);
	typedef void (FAR __stdcall *glDeleteRenderbuffersEXTProc)(GLsizei n, const GLuint *_hoops_PRRAC);
	typedef void (FAR __stdcall *glGenRenderbuffersEXTProc)(GLsizei n, GLuint *_hoops_PRRAC);
	typedef void (FAR __stdcall *glRenderbufferStorageEXTProc)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
	typedef void (FAR __stdcall *glGetRenderbufferParameterivEXTProc)(GLenum target, GLenum pname, GLint *params);

	typedef GLboolean (FAR __stdcall *glIsFramebufferEXTProc)(GLuint _hoops_HRRAC);
	typedef void (FAR __stdcall *glBindFramebufferEXTProc)(GLenum target, GLuint _hoops_HRRAC);
	typedef void (FAR __stdcall *glDeleteFramebuffersEXTProc)(GLsizei n, const GLuint *_hoops_IRRAC);
	typedef void (FAR __stdcall *glGenFramebuffersEXTProc)(GLsizei n, GLuint *_hoops_IRRAC);
	typedef GLenum (FAR __stdcall *glCheckFramebufferStatusEXTProc)(GLenum target);

	typedef void (FAR __stdcall *glFramebufferTexture1DEXTProc)(GLenum target, GLenum _hoops_CRRAC, GLenum _hoops_SRRAC, GLuint texture, GLint level);
	typedef void (FAR __stdcall *glFramebufferTexture2DEXTProc)(GLenum target, GLenum _hoops_CRRAC, GLenum _hoops_SRRAC, GLuint texture, GLint level);
	typedef void (FAR __stdcall *glFramebufferTexture3DEXTProc)(GLenum target, GLenum _hoops_CRRAC, GLenum _hoops_SRRAC, GLuint texture, GLint level, GLint zoffset);

	typedef void (FAR __stdcall *glFramebufferRenderbufferEXTProc)(GLenum target, GLenum _hoops_CRRAC, GLenum _hoops_GARAC, GLuint _hoops_ARRAC);
	typedef void (FAR __stdcall *glGetFramebufferAttachmentParameterivEXTProc)(GLenum target, GLenum _hoops_CRRAC, GLenum pname, GLint *params);
	typedef void (FAR __stdcall *glGenerateMipmapEXTProc)(GLenum target);

	/* _hoops_SCRGC _hoops_RHCP _hoops_GRSCP _hoops_RARAC */
	typedef void (FAR __stdcall *glBindBufferARBProc)(GLenum target, GLuint buffer);
	typedef void (FAR __stdcall *glDeleteBuffersARBProc)(GLsizei n, const GLuint *_hoops_AARAC);
	typedef void (FAR __stdcall *glGenBuffersARBProc)(GLsizei n, GLuint *_hoops_AARAC);
	typedef GLboolean (FAR __stdcall *glIsBufferARBProc)(GLuint buffer);
	typedef void (FAR __stdcall *glBufferDataARBProc)(GLenum target, GLsizei size, const void *data, GLenum _hoops_GCI);
	typedef void (FAR __stdcall *glBufferSubDataARBProc)(GLenum target, GLint *offset, GLsizei *size, const void *data);
	typedef void (FAR __stdcall *glGetBufferSubDataARBProc)(GLenum target, GLint *offset, GLsizei *size, void *data);
	typedef void * (FAR __stdcall *glMapBufferARBProc)(GLenum target, GLenum access);
	typedef GLboolean (FAR __stdcall *glUnmapBufferARBProc)(GLenum target);
	typedef void (FAR __stdcall *glGetBufferParameterivARBProc)(GLenum target, GLenum pname, int *params);
	typedef void (FAR __stdcall *glGetBufferPointervARBProc)(GLenum target, GLenum pname, void **params);

	/* _hoops_PARAC */
	typedef void (FAR __stdcall *glDrawRangeElementsEXTProc)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);

	/* _hoops_HARAC */
	typedef void (FAR __stdcall *glMultiDrawArraysEXTProc) (GLenum, GLint *, GLsizei *, GLsizei);
	typedef void (FAR __stdcall *glMultiDrawElementsEXTProc) (GLenum, const GLsizei *, GLenum, const GLvoid* *, GLsizei);

#endif

#if defined(GLX_DRIVER) || defined(AGL_DRIVER) || defined(COCOA_OGL_DRIVER)
	/* _hoops_IAGIP */
	typedef GLuint (*glNewKTXBufferRegionProc) (GLenum type);
	typedef void (*glDeleteKTXBufferRegionProc) (GLuint region);
	typedef void (*glReadKTXBufferRegionProc) (GLuint region, GLint x, GLint y, GLsizei width, GLsizei height);
	typedef void (*glDrawKTXBufferRegionProc) (GLuint region, GLint x, GLint y, GLsizei width, GLsizei height, GLint _hoops_ASGAC, GLint _hoops_PSGAC);
	typedef GLuint (*glKTXBufferRegionEnabledProc) (void);
	/* _hoops_PGRAC */
	typedef void (*glActiveTextureARBProc) (GLenum format);
	typedef void (*glClientActiveTextureARBProc) (GLenum format);
	typedef void (*glMultiTexCoord2fvARBProc) (GLenum format, const GLfloat *);
	typedef void (*glMultiTexCoord3fvARBProc) (GLenum format, const GLfloat *);
	/* _hoops_GPHA/_hoops_AIR _hoops_AIRRR */
	typedef void (*glGenProgramsARBProc) (GLsizei n, GLuint *programs);
	typedef void (*glDeleteProgramsARBProc) (GLsizei n, const GLuint *programs);
	typedef void (*glProgramStringARBProc) (GLenum target, GLenum format, GLsizei len, const void *string);
	typedef void (*glBindProgramARBProc) (GLenum target, GLuint program);
	typedef void (*glProgramEnvParameter4fARBProc) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	/* _hoops_SCRGC _hoops_CI _hoops_AGSAR */
	typedef void (*glShaderSourceARBProc) (GLuint _hoops_RSR, GLsizei _hoops_HGRAC, const char **strings, const GLint *lengths);
	typedef void (*glCompileShaderARBProc) (GLuint _hoops_RSR);
	typedef void (*glGetInfoLogARBProc) (GLuint _hoops_RSR, GLsizei _hoops_IGRAC, GLsizei *length, char *buffer);
	typedef void (*glAttachObjectARBProc) (GLuint program, GLuint _hoops_RSR);
	typedef void (*glDetachObjectARBProc) (GLuint program, GLuint _hoops_RSR);
	typedef void (*glDeleteShaderARBProc) (GLuint _hoops_RSR);
	typedef void (*glLinkProgramARBProc) (GLuint program);
	typedef GLuint (*glCreateShaderObjectARBProc) (GLenum _hoops_RCS);
	typedef GLuint (*glCreateProgramObjectARBProc) (void);
	typedef void (*glDeleteProgramARBProc) (GLuint program);
	typedef void (*glUseProgramObjectARBProc) (GLuint program);
	typedef void (*glGetObjectParameterfvARBProc) (GLuint _hoops_RSR, GLenum pname, GLfloat *params);
	typedef void (*glGetObjectParameterivARBProc) (GLuint _hoops_RSR, GLenum pname, GLint *params);
	/* _hoops_SCRGC _hoops_IAGP _hoops_RACGH */
	typedef void (*glGenQueriesARBProc) (GLsizei n, GLuint *_hoops_GPICA);
	typedef void (*glDeleteQueriesARBProc) (GLsizei n, const GLuint *_hoops_GPICA);
	typedef void (*glBeginQueryARBProc) (GLenum target, GLuint id);
	typedef void (*glEndQueryARBProc) (GLenum target);
	typedef void (*glGetQueryivARBProc) (GLenum target, GLenum pname, GLint *params);
	typedef void (*glGetQueryObjectuivARBProc) (GLuint id, GLenum pname, GLuint *params);
	/* _hoops_RSRGC _hoops_IAGP _hoops_RACGH */
	typedef void (*glGenOcclusionQueriesNVProc) (GLsizei n, GLuint *_hoops_GPICA);
	typedef void (*glDeleteOcclusionQueriesNVProc) (GLsizei n, const GLuint *_hoops_GPICA);
	typedef void (*glBeginOcclusionQueryNVProc) (GLuint id);
	typedef void (*glEndOcclusionQueryNVProc) (void);
	typedef void (*glGetOcclusionQueryuivNVProc) (GLuint id, GLenum pname, GLuint *params);
	/* _hoops_RSRGC _hoops_CGRAC */
	typedef void (*glGenFencesNVProc)(GLsizei n, GLuint *fences);
	typedef void (*glDeleteFencesNVProc)(GLsizei n, const GLuint *fences);
	typedef void (*glSetFenceNVProc)(GLuint fence, GLenum condition);
	typedef GLboolean (*glTestFenceNVProc)(GLuint fence);
	typedef void (*glFinishFenceNVProc)(GLuint fence);
	typedef GLboolean (*glIsFenceNVProc)(GLuint fence);
	typedef void (*glGetFenceivNVProc)(GLuint fence, GLenum pname, GLint *params);
	/* _hoops_SCRGC _hoops_SGRAC */
	typedef void (*glPointParameterfARBProc)(GLenum pname, GLfloat param);
	typedef void (*glPointParameterfvARBProc)(GLenum pname, const GLfloat *param);
	/* _hoops_SCRGC _hoops_GRAR _hoops_GRRAC */
	typedef void (*glCompressedTexImage2DARBProc)(GLenum target, GLint level, 
				GLenum internalformat, GLsizei width, GLsizei height, 
				GLint border, GLsizei imageSize, const GLvoid *data);
	typedef void (*glPrimitiveRestartNVProc)(void);
	typedef void (*glPrimitiveRestartIndexNVProc)(GLuint index);
	/* _hoops_SCRGC 3d _hoops_AI */
	typedef void (*glTexImage3DProc)(
				GLenum target,  
				GLint level,  
				GLint internalFormat,  
				GLsizei width,  
				GLsizei height,  
				GLsizei depth,  
				GLint border,  
				GLenum format,  
				GLenum type,  
				const GLvoid *data); 
	typedef void (*glTexSubImage3DProc)(
				GLenum   target,  
				GLint level,  
				GLint xoffset,  
				GLint yoffset,  
				GLint zoffset,  
				GLsizei width,  
				GLsizei height,  
				GLsizei depth,  
				GLenum format,  
				GLenum type,  
				const GLvoid * data); 

	/* _hoops_RRRAC */
	typedef GLboolean (*glIsRenderbufferEXTProc)(GLuint _hoops_ARRAC);
	
	typedef void (*glBindRenderbufferEXTProc)(GLenum target, GLuint _hoops_ARRAC);
	typedef void (*glDeleteRenderbuffersEXTProc)(GLsizei n, const GLuint *_hoops_PRRAC);
	typedef void (*glGenRenderbuffersEXTProc)(GLsizei n, GLuint *_hoops_PRRAC);
	typedef void (*glRenderbufferStorageEXTProc)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
	typedef void (*glGetRenderbufferParameterivEXTProc)(GLenum target, GLenum pname, GLint *params);

	typedef GLboolean (*glIsFramebufferEXTProc)(GLuint _hoops_HRRAC);
	typedef void (*glBindFramebufferEXTProc)(GLenum target, GLuint _hoops_HRRAC);
	typedef void (*glDeleteFramebuffersEXTProc)(GLsizei n, const GLuint *_hoops_IRRAC);
	typedef void (*glGenFramebuffersEXTProc)(GLsizei n, GLuint *_hoops_IRRAC);
	typedef GLenum (*glCheckFramebufferStatusEXTProc)(GLenum target);

	typedef void (*glFramebufferTexture1DEXTProc)(GLenum target, GLenum _hoops_CRRAC, GLenum _hoops_SRRAC, GLuint texture, GLint level);
	typedef void (*glFramebufferTexture2DEXTProc)(GLenum target, GLenum _hoops_CRRAC, GLenum _hoops_SRRAC, GLuint texture, GLint level);
	typedef void (*glFramebufferTexture3DEXTProc)(GLenum target, GLenum _hoops_CRRAC, GLenum _hoops_SRRAC, GLuint texture, GLint level, GLint zoffset);

	typedef void (*glFramebufferRenderbufferEXTProc)(GLenum target, GLenum _hoops_CRRAC, GLenum _hoops_GARAC, GLuint _hoops_ARRAC);
	typedef void (*glGetFramebufferAttachmentParameterivEXTProc)(GLenum target, GLenum _hoops_CRRAC, GLenum pname, GLint *params);
	typedef void (*glGenerateMipmapEXTProc)(GLenum target);

	/* _hoops_SCRGC _hoops_RHCP _hoops_GRSCP _hoops_RARAC */
	typedef void (*glBindBufferARBProc)(GLenum target, GLuint buffer);
	typedef void (*glDeleteBuffersARBProc)(GLsizei n, const GLuint *_hoops_AARAC);
	typedef void (*glGenBuffersARBProc)(GLsizei n, GLuint *_hoops_AARAC);
	typedef GLboolean (*glIsBufferARBProc)(GLuint buffer);
	typedef void (*glBufferDataARBProc)(GLenum target, GLsizei size, const void *data, GLenum _hoops_GCI);
	typedef void (*glBufferSubDataARBProc)(GLenum target, GLint *offset, GLsizei *size, const void *data);
	typedef void (*glGetBufferSubDataARBProc)(GLenum target, GLint *offset, GLsizei *size, void *data);
	typedef void * (*glMapBufferARBProc)(GLenum target, GLenum access);
	typedef GLboolean (*glUnmapBufferARBProc)(GLenum target);
	typedef void (*glGetBufferParameterivARBProc)(GLenum target, GLenum pname, int *params);
	typedef void (*glGetBufferPointervARBProc)(GLenum target, GLenum pname, void **params);

	/* _hoops_PARAC */
	typedef void (*glDrawRangeElementsEXTProc)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);

	/* _hoops_HARAC */
	typedef void (*glMultiDrawArraysEXTProc) (GLenum, GLint *, GLsizei *, GLsizei);
	typedef void (*glMultiDrawElementsEXTProc) (GLenum, const GLsizei *, GLenum, const GLvoid* *, GLsizei);

# if (_hoops_IARAC < _hoops_CARAC)
	typedef void *AGLPbuffer;
# endif

#endif


typedef struct {
    GLint factor;
    GLushort pattern;
}
OGLlpattern;


#define OGL_MAX_PASSES 64
typedef int OGL_Render_Pass;
#define _hoops_RCGRC						(OGL_Render_Pass)(0x0001)
#define _hoops_SARAC				(OGL_Render_Pass)(0x0002)
#define _hoops_GPRAC				(OGL_Render_Pass)(0x0004)
#define _hoops_ISSGC				(OGL_Render_Pass)(0x0008)
#define _hoops_CSSGC		(OGL_Render_Pass)(0x0010)
#define _hoops_SSSGC			(OGL_Render_Pass)(0x0020)
#define _hoops_HCSGC			(OGL_Render_Pass)(0x0040)
#define _hoops_GGGRC			(OGL_Render_Pass)(0x0080)
#define _hoops_PCSGC				(OGL_Render_Pass)(0x0100)
#define _hoops_HSSGC						(OGL_Render_Pass)(0x0200)
#define _hoops_RIGRC						(OGL_Render_Pass)(0x0400)
															 
typedef int OGL_Render_Control_Flags;						 
#define _hoops_RHARC			(OGL_Render_Control_Flags)(0x0001) 
#define _hoops_ACGRC	(OGL_Render_Control_Flags)(0x0002) 
#define _hoops_AGRRC		(OGL_Render_Control_Flags)(0x0004) 
#define _hoops_GPGRC		(OGL_Render_Control_Flags)(0x0008) 
#define _hoops_HSGRC		(OGL_Render_Control_Flags)(0x0010)
#define _hoops_GGRRC	(OGL_Render_Control_Flags)(0x0020) 
#define _hoops_CARRC				(OGL_Render_Control_Flags)(0x0040) 
#define _hoops_AGCGC				(OGL_Render_Control_Flags)(0x0080) 
#define _hoops_RPRAC			(OGL_Render_Control_Flags)(0x0100) 
#define _hoops_CIGRC					(OGL_Render_Control_Flags)(0x0200) 
#define _hoops_RGCGC	(OGL_Render_Control_Flags)(0x0400) 
#define _hoops_APRAC		(OGL_Render_Control_Flags)(0x0800) 
#define _hoops_SHGRC		(OGL_Render_Control_Flags)(0x1000) 


typedef struct {
	Vector *_hoops_AHRRC;
	Vector *_hoops_GHRRC;
	Vector *_hoops_RHRRC;
	Point *_hoops_PHRRC;
	int length;
} _hoops_PPRAC;


struct OGL_Render_Control {
    unsigned int n;
    unsigned int pass;
    unsigned int _hoops_CHRRC;
    GLuint id[OGL_MAX_PASSES];
    
    _hoops_RCR *txr[OGL_MAX_PASSES];
    OGL_Render_Pass _hoops_GCI[OGL_MAX_PASSES];
    RGB _hoops_AIGRC[OGL_MAX_PASSES];
    RGB _hoops_PIGRC[OGL_MAX_PASSES];
    int	_hoops_RSCP[OGL_MAX_PASSES];
    _hoops_RSSH const *params[OGL_MAX_PASSES];
    Integer32 param_width[OGL_MAX_PASSES];    
    int flags[OGL_MAX_PASSES];
    int _hoops_RSIC[OGL_MAX_PASSES];
    _hoops_AS const *light[OGL_MAX_PASSES];
	int _hoops_SIGRC[OGL_MAX_PASSES];
 	_hoops_PPRAC  _hoops_IARRC;
};



#define OGL_VBO_ARRAYS				0x0002 
#define OGL_VBO_STRIP_ARRAYS		0x0004

struct OGL_Vertex_Buffer_Object{
	_hoops_CAIS const * _hoops_SSARC;
	int			count;			/* _hoops_PHI _hoops_IIGR _hoops_GARI'_hoops_GRI _hoops_PAR _hoops_SAHA'_hoops_GRI */
	int			point_count;

	GLuint		_hoops_IGPRC;
	GLuint		_hoops_CGPRC;
	GLuint		_hoops_SGPRC;
	GLuint		_hoops_GRPRC;
	int			param_width;

	int			_hoops_CPPSP;
	int			_hoops_HPRAC;
	int			*_hoops_RSARC;
	int			colors_offset;
	int			stride;
	int			_hoops_AGPRC;
	int			_hoops_ASARC;

	GLuint		_hoops_RRPRC;   /* _hoops_IIRGR */
	int			*_hoops_ISARC;
	int			*_hoops_PSARC;
	int			_hoops_HSARC;
	int			_hoops_RGPRC;
	unsigned short	*_hoops_GGPRC;

	GLuint		_hoops_ARPRC;  /* _hoops_HIPH _hoops_PAR _hoops_APGR */
	int			_hoops_HGPRC;
	int			*_hoops_CSARC;
	unsigned short	*_hoops_PGPRC;

	int			flags;
};


struct OGL_Polymarker_Vertex_Buffer_Object{
	int			point_count;
	GLuint		_hoops_HRPRC;	//_hoops_PACGR _hoops_PPSR,_hoops_GSSR,_hoops_PRGH,_hoops_HAIR
	unsigned int _hoops_PPCP;
	unsigned int _hoops_GPGC;
};

struct OGLData; //_hoops_CPCHR

#define OGL_DL_NONE					0
#define OGL_DL_TEXTURE				1
#define OGL_DL_GEOMETRY				2
#define OGL_DL_GEOMETRY_VBO			3
#define OGL_DL_SEGMENT_POLYLINE		4
#define OGL_DL_SEGMENT_POLYGON		5
#define OGL_DL_SEGMENT_TREE			6
#define OGL_DL_SHADOW_MAP			7
#define OGL_DL_GEOMETRY_LIST		8
#define OGL_DL_POLYMARKER_VBO_LIST	9

#define OGL_DL_BLESSED_GEOMETRY 0x0001
#define OGL_DL_BLESSED_SEGMENT  0x0002
#define OGL_DL_SINGLE_INSTANCED 0x0004 /* _hoops_SIGH _hoops_SGS _hoops_GGRRI'_hoops_GRI _hoops_PAH _hoops_SHH _hoops_SHPS _hoops_IS _hoops_HCGI'_hoops_GRI _hoops_IH _hoops_CIH */
#define OGL_SEGDL_HAS_EXPLICIT_VISIBLE  0x0008

#define _hoops_IPRAC 100

class OGL_Display_List;
typedef VList<OGL_Display_List *> OGL_Display_List_List;
typedef VList<GLuint> OGL_DL_ID_List;
typedef VList<OGL_Polymarker_Vertex_Buffer_Object *> OGL_DL_VBO_List;

class OGL_Display_List : public _hoops_AGCI{
public:
    void *_hoops_HHCAP;
	AGLM(OGLData *_hoops_CSRGR);
    unsigned int type;
	int _hoops_CARH;		/* _hoops_SCCGR _hoops_HCHC _hoops_IIGR _hoops_PPGS _hoops_RGR _hoops_CARA _hoops_GSCGR */

	union {
		struct {
			GLuint id;
			GLuint *_hoops_SRAGR;
		} texture;
		struct {
			/* _hoops_RH _hoops_HSPR _hoops_RIRIA _hoops_PAH _hoops_HCAAA _hoops_PGI _hoops_IRS _hoops_HRCGP _hoops_PAR _hoops_IRS 
			   _hoops_CPRAC *, _hoops_GPGA _hoops_GPP _hoops_RH _hoops_GPRR */
			POINTER_SIZED_INT id;
			Integer32 param_width;
			Integer32 param_flags[32];
			unsigned int _hoops_GSAI;
			unsigned int _hoops_SRHA;
			unsigned int _hoops_CARI;
			unsigned int _hoops_IRRI;
			struct {
				int total;
				int _hoops_PHHA;
				int point_count;
			}	_hoops_IGGI;
		} geometry;
		struct {
			POINTER_SIZED_INT	id;
			int					_hoops_HAP;
			float				transform[16];
			//_hoops_CICC _hoops_SPRAC;
			//_hoops_AIIC _hoops_GHRAC[16];
			//_hoops_AIIC _hoops_RHRAC[16];
			//_hoops_AIIC _hoops_AHRAC;
			//_hoops_PHRAC _hoops_HHRAC;
		}	_hoops_HRR;
		struct {
			Polyedge *pe;
			int	_hoops_PPPI;
			int _hoops_HPPI;
			float _hoops_IPPI;
			float _hoops_CPPI;
			float _hoops_SPPI;
		}   _hoops_RPPI;
		struct {
			OGL_Display_List_List *_hoops_PCII; // _hoops_CRHH _hoops_CGHS
			OGL_Display_List_List *_hoops_GHPI; // _hoops_ACRI _hoops_CGHS
			int					_hoops_PPPI, _hoops_HPPI;
			float				_hoops_IPPI, _hoops_CPPI, _hoops_SPPI;
		}   _hoops_ACII;
		struct {
			OGL_Display_List_List *_hoops_ARRI;		
			OGL_Display_List_List *_hoops_AGAI;
			OGL_Display_List_List *_hoops_GGAI;	// _hoops_AHHA
			OGL_Display_List_List *_hoops_RGAI;   // _hoops_AHHA
			OGL_Display_List_List *_hoops_CAPI;		
			OGL_Display_List_List *_hoops_RCII; 
			OGL_Display_List_List *_hoops_ICARC;
			OGL_Display_List_List *_hoops_GAAI;
			_hoops_GRGGI *_hoops_CRPRC;
			_hoops_GRGGI *_hoops_SRPRC; 
			_hoops_GRGGI *_hoops_HGHRC;

			_hoops_ACHR _hoops_RGP;
			_hoops_ACHR _hoops_PCGI;  //_hoops_IAGH _hoops_SGS _hoops_SSCGR _hoops_GGR _hoops_HPP _hoops_GGSGR _hoops_IIGR _hoops_IRGH _hoops_RGSGR
			Color_Object _hoops_CSPRC;	//_hoops_RH _hoops_HAIR _hoops_SGHS _hoops_SGS _hoops_AAPR _hoops_IGI _hoops_HPGR _hoops_RH _hoops_GHIR _hoops_IIGR _hoops_RH _hoops_HCGI _hoops_HSSI
			Color_Object _hoops_GGHRC;	//_hoops_RH _hoops_ARP _hoops_IIGR _hoops_HAIR _hoops_CSSC _hoops_CCA _hoops_AAHA _hoops_PSHA _hoops_HISS
			unsigned int flags; 
		} _hoops_ACGI;

    } item;
};


struct OGL_Display_List_Bin;
typedef VList<OGL_Display_List_Bin *> OGL_Display_List_Bin_List;

class _hoops_IPSGC;
typedef VList<_hoops_IPSGC *> _hoops_AIGI;

/* _hoops_CPIP _hoops_HIGR "_hoops_SCGI _hoops_PIHRR" */
struct OGL_Display_List_Bin{
	Net_Rendition		nr;
	_hoops_AIGI *	_hoops_CRHA;		/* _hoops_HIGR _hoops_IIGR _hoops_CPAP */
	OGL_Display_List *	odl;			/* _hoops_IIPR; _hoops_RH _hoops_ARGR _hoops_AIRI _hoops_HIGR */
	OGL_Display_List *	_hoops_CHGI;			/* _hoops_IIPR; _hoops_RH _hoops_ARGR _hoops_AIRI _hoops_HIGR */
	unsigned int		id;
	int					_hoops_GSHA;
	unsigned int 		_hoops_AGRI;		/* _hoops_GII _hoops_GRH _hoops_SGI */
	unsigned int 		_hoops_PRRI;		/* _hoops_GII _hoops_GRH _hoops_SGI */
	int 				point_count;	/* _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_RH _hoops_SCGR _hoops_IGIR, _hoops_HIS _hoops_SR _hoops_ACPA _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_GHHS _hoops_HAH _hoops_AHSC */
	int 				_hoops_HGAC;		/* _hoops_GII _hoops_IHH _hoops_PSIGA _hoops_PIH (_hoops_HGPP _hoops_GAR _hoops_HSP _hoops_RPR) */
	int					_hoops_GPGC;
};

/* _hoops_GGGAR _hoops_ARI _hoops_HRGR _hoops_IRS _hoops_RSCA _hoops_RGGAR _hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH _hoops_AGGAR _hoops_GIRP 
 * _hoops_PGGAR _hoops_HGGAR _hoops_ACPP.  _hoops_HHPC _hoops_SR'_hoops_GHGP _hoops_HS _hoops_IS 
 * _hoops_AASA _hoops_SCH _hoops_ARR _hoops_ARPP _hoops_IGGAR _hoops_PPR _hoops_GICS _hoops_IS _hoops_CAHP _hoops_RH _hoops_RSSA -- _hoops_PPR 
 * _hoops_SCH _hoops_PAH _hoops_HGCR _hoops_IS _hoops_SHH _hoops_CGGAR _hoops_IIGR _hoops_IHPH. */
struct _hoops_CHRGR {
	Point *points;
	int _hoops_SGII; //_hoops_AAPA _hoops_ASCR _hoops_IH _hoops_GHCS
	int count;  //_hoops_RIHRR _hoops_RPR
	Type type;
	RGB const *_hoops_IGII;
};
struct _hoops_GSHI : public _hoops_CHRGR {
	_hoops_ARPA plane;
	RGB const *_hoops_CGII;
};
typedef VList<_hoops_CHRGR *> _hoops_HHRGR;
typedef VList<_hoops_GSHI *> _hoops_CCHI;


#include "hi_proto.h"

/* _hoops_RAIGR _hoops_CPAP / _hoops_RSGA _hoops_PSAI */
class _hoops_IPSGC : public CMO_Pooled {

public:

	enum Type {
		_hoops_CGSGR = 0,
		_hoops_SGSGR,
		_hoops_GRSGR,
		_hoops_HCAI,
		_hoops_RRSGR,
	};

	_hoops_IPSGC(Net_Rendition const &inr, Tristrip const *its, _hoops_ISGI const * _hoops_ARSGR,
				_hoops_SSGI const * _hoops_PRSGR, bool _hoops_HRSGR = false) : nr(inr) {
		if ((geo = (void*)its) != null) {
			type = _hoops_SGSGR;
			_hoops_CAHS(its);
		}

		if ((_hoops_CPAI = _hoops_ARSGR) != null)
			_hoops_PRRH (_hoops_CPAI);

		if ((color = _hoops_PRSGR) != null)
			_hoops_PRRH (color);

		single = _hoops_HRSGR;
	};

	
	_hoops_IPSGC(Net_Rendition const &inr, Polyedge const *_hoops_RASGR, _hoops_ISGI const * _hoops_ARSGR,
				_hoops_SSGI const * _hoops_PRSGR, bool _hoops_HRSGR = false) : nr(inr) {
		if ((geo = (void*)_hoops_RASGR) != null) {
			type = _hoops_GRSGR;
			_hoops_CAHS(_hoops_RASGR);
		}

		if ((_hoops_CPAI = _hoops_ARSGR) != null)
			_hoops_PRRH (_hoops_CPAI);

		if ((color = _hoops_PRSGR) != null)
			_hoops_PRRH (color);

		single = _hoops_HRSGR;
	};

	_hoops_IPSGC(Net_Rendition const &inr, Polymarker const *_hoops_PASGR, _hoops_ISGI const * _hoops_ARSGR,
				_hoops_SSGI const * _hoops_PRSGR, bool _hoops_HRSGR = false) : nr(inr) {
		if ((geo = (void*)_hoops_PASGR) != null) {
			type = _hoops_HCAI;
			_hoops_CAHS(_hoops_PASGR);
		}

		if ((_hoops_CPAI = _hoops_ARSGR) != null)
			_hoops_PRRH (_hoops_CPAI);

		if ((color = _hoops_PRSGR) != null)
			_hoops_PRRH (color);

		single = _hoops_HRSGR;
	};

	_hoops_IPSGC(Net_Rendition const &inr, Geometry const * _hoops_HASGR, _hoops_ISGI const * _hoops_ARSGR,
				_hoops_SSGI const * _hoops_PRSGR, bool _hoops_HRSGR = false) : nr(inr) {
		if ((geo = (void*)_hoops_HASGR) != null) {
			type = _hoops_RRSGR;
			_hoops_PRRH (_hoops_HASGR);
		}

		if ((_hoops_CPAI = _hoops_ARSGR) != null)
			_hoops_PRRH (_hoops_CPAI);

		if ((color = _hoops_PRSGR) != null)
			_hoops_PRRH (color);

		single = _hoops_HRSGR;
	};

	~_hoops_IPSGC() {
		if (type == _hoops_SGSGR) {
			if (_hoops_ISAI ((Tristrip *)geo) == 0)
				HI_Free_Tristrip ((Tristrip *)geo);
		}
		else if (type == _hoops_GRSGR) {
			if (_hoops_ISAI ((Polyedge *)geo) == 0)
				HI_Free_Polyedge ((Polyedge *)geo);
		}
		else if (type == _hoops_HCAI) {
			if (_hoops_ISAI ((Polymarker *)geo) == 0)
				HI_Free_Polymarker ((Polymarker *)geo);
		}
		else if (type == _hoops_RRSGR) 
			_hoops_HPRH ((Geometry*)geo);

		if (_hoops_CPAI)
			_hoops_HPRH (_hoops_CPAI);

		if (color)
			_hoops_HPRH (color);
	};

	Type						type;
	void *						geo;
	_hoops_ISGI const *	_hoops_CPAI;
	_hoops_SSGI const *				color;
	Net_Rendition				nr;
	bool						single;
};

local RGB const *_hoops_RPCA (_hoops_APCA const *color, int mask);
#define _hoops_CCAI(_hoops_IASGR,bit) (_hoops_IASGR==null?null:(BIT(_hoops_IASGR->_hoops_GHA,bit)?_hoops_RPCA((_hoops_APCA const *)_hoops_IASGR->colors,bit):null))


/* _hoops_PGCAI _hoops_CHR _hoops_ASHPA, _hoops_CASGI, _hoops_RACIR, _hoops_CASGI _hoops_RAPC */
#define _hoops_GRCRC(mat,_hoops_IHRAC,pt,_hoops_CHRAC) _hoops_GHIA(\
	_hoops_RPRA const *	_hoops_APRA = mat->_hoops_APRA->data.elements; \
	float d = _hoops_IHRAC.x*pt.x + _hoops_IHRAC.y*pt.y + _hoops_IHRAC.z*pt.z; \
	_hoops_CHRAC.x = _hoops_IHRAC.x * _hoops_APRA[0][0] + _hoops_IHRAC.y * _hoops_APRA[0][1] + _hoops_IHRAC.z * _hoops_APRA[0][2] + d * _hoops_APRA[0][3]; \
	_hoops_CHRAC.y = _hoops_IHRAC.x * _hoops_APRA[1][0] + _hoops_IHRAC.y * _hoops_APRA[1][1] + _hoops_IHRAC.z * _hoops_APRA[1][2] + d * _hoops_APRA[1][3]; \
	_hoops_CHRAC.z = _hoops_IHRAC.x * _hoops_APRA[2][0] + _hoops_IHRAC.y * _hoops_APRA[2][1] + _hoops_IHRAC.z * _hoops_APRA[2][2] + d * _hoops_APRA[2][3]; \
	if (BIT (mat->_hoops_RAGR, _hoops_CHCP)) \
		HI_Normalize ((Vector *)&_hoops_CHRAC); \
)

#define _hoops_CRCRC(mat,_hoops_IHRAC,pt,_hoops_CHRAC) _hoops_GRCRC(mat,_hoops_IHRAC,pt,_hoops_CHRAC)

/* _hoops_PGCAI _hoops_CHR _hoops_ASHPA, _hoops_SPGGR, _hoops_SPGGR _hoops_RAPC 
 * _hoops_IGIPR _hoops_SGS _hoops_HGPI->_hoops_GGRA _hoops_SSCP _hoops_RPII _hoops_SHRAC _hoops_CCA _hoops_PGRRC */
#define _hoops_GIRAC(mat,pln,_hoops_CHRAC) _hoops_GHIA(\
	_hoops_RPRA const *	_hoops_APRA = mat->_hoops_APRA->data.elements; \
	_hoops_CHRAC.a = pln.a * _hoops_APRA[0][0] + pln.b * _hoops_APRA[0][1] + pln.c * _hoops_APRA[0][2] + pln.d * _hoops_APRA[0][3]; \
	_hoops_CHRAC.b = pln.a * _hoops_APRA[1][0] + pln.b * _hoops_APRA[1][1] + pln.c * _hoops_APRA[1][2] + pln.d * _hoops_APRA[1][3]; \
	_hoops_CHRAC.c = pln.a * _hoops_APRA[2][0] + pln.b * _hoops_APRA[2][1] + pln.c * _hoops_APRA[2][2] + pln.d * _hoops_APRA[2][3]; \
	_hoops_CHRAC.d = pln.a * _hoops_APRA[3][0] + pln.b * _hoops_APRA[3][1] + pln.c * _hoops_APRA[3][2] + pln.d * _hoops_APRA[3][3]; \
	if (BIT (mat->_hoops_RAGR, _hoops_CHCP)) \
		HI_Normalize_Plane ((_hoops_ARPA *)&_hoops_CHRAC); \
)
/* _hoops_PGCAI _hoops_CHR _hoops_ASHPA, _hoops_RACIR, _hoops_RACIR _hoops_RAPC */
#define _hoops_SGCRC(mat,pt,_hoops_RIRAC) _hoops_GHIA(\
	float _hoops_APCP = 1.0f / _hoops_PHCP (mat->elements,pt); \
	_hoops_RIRAC.x = _hoops_HPRA(mat->elements, pt) * _hoops_APCP; \
	_hoops_RIRAC.y = _hoops_IPRA(mat->elements, pt) * _hoops_APCP; \
	_hoops_RIRAC.z = _hoops_CPRA(mat->elements, pt) * _hoops_APCP; \
)
#define _hoops_CAIRC(mat,pt) _hoops_GHIA(\
	Point _hoops_AIRAC; \
	_hoops_SGCRC(mat,pt,_hoops_AIRAC); \
	glVertex3fv ((GLfloat *)&_hoops_AIRAC.x); \
)

#define _hoops_PIRAC(mat,_hoops_ASSRR,_hoops_HIRAC,_hoops_IHRAC,pt) _hoops_GHIA(\
	Point _hoops_AIRAC; \
	Vector _hoops_IIRAC; \
	_hoops_SGCRC(mat,pt,_hoops_AIRAC); \
	_hoops_GRCRC (mat,_hoops_IHRAC,pt,_hoops_IIRAC);\
	_hoops_RRCRC (_hoops_ASSRR,_hoops_IIRAC, _hoops_AIRAC, _hoops_HIRAC);\
	glVertex3fv ((GLfloat *)&_hoops_AIRAC.x); \
)

struct OGL_Collector {
	OGL_Collector *next;
	Net_Rendition nr;
	_hoops_AIGI *_hoops_RCGI;
	_hoops_AIGI *_hoops_IIRI;
	_hoops_AIGI *_hoops_CIRI;
	_hoops_AIGI *_hoops_SIRI;
	_hoops_AIGI *_hoops_HRPI;	/* _hoops_APGR, _hoops_GRRC _hoops_PPR _hoops_RRRC*/
	_hoops_AIGI *_hoops_IIII;
	_hoops_AIGI *_hoops_HHAI;
	_hoops_AIGI *_hoops_IHAI;
	Action_Mask mask, _hoops_RRSI, _hoops_PRGC;	/* _hoops_CIRAC* _hoops_SIH 1==_hoops_GIR, 0==_hoops_HAR _hoops_GIR */
	Color_Object _hoops_GGHRC;
	bool _hoops_SIGI;
	bool _hoops_CPPGR;
	bool _hoops_IHGI;
	bool _hoops_ASHRC;
};


#ifdef WGL_DRIVER
/* _hoops_AGCR _hoops_CHR _hoops_IGI _hoops_HPP _hoops_RH _hoops_HRRAH */
typedef void * _hoops_SIRAC;
#endif

// _hoops_GGR _hoops_AGR _hoops_IIGR _hoops_CIHCA
typedef enum {
	OGLR_INVALID = 0,
	OGLR_FIRST_METHOD = 1,
	OGLR_DEPTH_TEXTURE_RECT = 1,
	OGLR_DEPTH_TEXTURE_SQUARE = 2,
	OGLR_KTX_BUFFER_REGION = 3,
	OGLR_WGL_ARB_BUFFER = 4,
	OGLR_MAKE_CONTEXT_CURRENT = 5,
	OGLR_DRAW_PIXELS = 6,
	OGLR_LAST_METHOD = 6
} _hoops_RASRC;

typedef struct {
    /* _hoops_IGI _hoops_IH _hoops_GCRAC _hoops_IRIGR/_hoops_PGSA _hoops_ASPA _hoops_AGIR */
    void *buffer;
    int size;
	_hoops_RASRC type;
    Int_Rectangle _hoops_ACCRC;
    GLuint id;   
#ifdef WGL_DRIVER
    /* _hoops_IGI _hoops_IH _hoops_IGHGC _hoops_SRHR _hoops_ISPH _hoops_AGIR */
    HANDLE handle;
    _hoops_SIRAC pbuffer;
    HDC hDC;
    HGLRC hGLRC;
#endif
} _hoops_SICRC;


#ifdef _DEBUG
#	define DEBUG_FLUSH()	glFlush(),glFinish()
#else
#	define DEBUG_FLUSH()	(void)0
#endif


#ifdef GLX_DRIVER

/* _hoops_RCRAC _hoops_RPCC _hoops_IH _hoops_ACRAC _hoops_SGCCP. */
typedef struct _hoops_PCRAC {
    unsigned long _hoops_HCRAC;
    unsigned long _hoops_ICRAC;
#define _hoops_CCRAC                   0x0
#define _hoops_SCRAC       0x1
#define _hoops_GSRAC        0x2
    unsigned long value;
    unsigned long layer;
}
XOverlayVisual;

#endif


#ifdef WGL_DRIVER
#include "hi_proto.h"

class OGL_Master_Context:public CMO {
public:
	OGL_Master_Context(int format) {

		_hoops_GCARC = 0;

		hWND = CreateWindowA ("HoopsWClassOGL", "hmasterc", 
			WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			1,1,1,1,
			null, null, _hoops_RCSRH (_hoops_ACSRH), null);

		if (hWND == null)
			goto _hoops_RSRAC;

		hDC = GetDC (hWND);

		if (hDC == null)
			goto _hoops_RSRAC;
		
		SetPixelFormat (hDC, format, 0);

		hGLRC = wglCreateContext (hDC);

		_hoops_GCARC = HI_Create_Mutex();

_hoops_RSRAC:;
	};
	~OGL_Master_Context() {
		if (hGLRC != null)
			wglDeleteContext (hGLRC);
		if (hDC != null)
			ReleaseDC (hWND, hDC);
		if (hWND != null)
			DestroyWindow(hWND);
		
		if (_hoops_GCARC != 0)
			HI_Destroy_Mutex(_hoops_GCARC);
	};
	bool _hoops_ASRAC() {
		if (hWND == null || hDC == null || hGLRC == null)
			return false;
		return true;
	};

	static void _hoops_IRACI()
	{
		_hoops_RRPRH *_hoops_IRSRA = _hoops_ARPRH ();
		delete _hoops_IRSRA->_hoops_HRACI;
	}

	HGLRC hGLRC;
	HWND hWND;
	HDC hDC;
	_hoops_CPGRR _hoops_GCARC;
};



/****************************
* _hoops_HRGSI _hoops_PRCA _hoops_PIH
****************************/

typedef struct OGLFontData {
    float _hoops_HIIH;
    int _hoops_PSRAC;
    int _hoops_RCGCI;
    int descent;
    int _hoops_ACGCI;

#define OGL_FONT_DATA_BUFFER_SIZE (1<<8)
#define OGL_FONT_DATA_BUFFER_MASK (OGL_FONT_DATA_BUFFER_SIZE-1)

    _hoops_RAARP * stencil[OGL_FONT_DATA_BUFFER_SIZE];

    LOGFONT _hoops_PCGCI;
    HFONT _hoops_HCGCI;

	float xrrotation;
	_hoops_RAARP * _hoops_HSRAC[OGL_FONT_DATA_BUFFER_SIZE];
    LOGFONT _hoops_ISRAC;
    HFONT _hoops_CSRAC;
}
OGLFontData;

#endif

typedef int _hoops_RPSGR;
#define _hoops_APSGR		((_hoops_RPSGR)0)
#define _hoops_PPSGR		((_hoops_RPSGR)1)
#define _hoops_HPSGR	((_hoops_RPSGR)2)
#define DCT_IMAGE			((_hoops_RPSGR)3)
#define _hoops_IPSGR	((_hoops_RPSGR)4)
#define _hoops_CPSGR		((_hoops_RPSGR)5)
#define _hoops_SSRAC	((_hoops_RPSGR)6)




#define _hoops_PGGRC 11
#define _hoops_PHSGC 20


/* _hoops_GGAAC _hoops_SRAC _hoops_CHASR */
 
typedef void (HC_CDECL *_hoops_RGAAC)(OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr);
typedef void (HC_CDECL *_hoops_AGAAC)(OGLData alter * _hoops_CSRGR);
typedef void (HC_CDECL *_hoops_PGAAC)(OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr, _hoops_PC const & _hoops_HC);
typedef void (HC_CDECL *_hoops_HGAAC)(OGLData alter * _hoops_CSRGR, _hoops_HHCR const & _hoops_IHCR, int flags);
typedef void (HC_CDECL *_hoops_IGAAC)(OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr, Line_Rendition const & _hoops_HC);
typedef void (HC_CDECL *_hoops_CGAAC)(OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr, _hoops_HHA const & matr, RGB const *_hoops_PRSGC, RGB const *_hoops_HRSGC);
typedef void (HC_CDECL *_hoops_SGAAC)(OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr, _hoops_HHA const & matr);
typedef void (HC_CDECL *_hoops_GRAAC)(OGLData alter * _hoops_CSRGR, Driver_Color const * color);
typedef GLuint (HC_CDECL *_hoops_RRAAC)(OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr, _hoops_RCR alter *txr, _hoops_ARGRA _hoops_GCI, int _hoops_GRRA);
typedef bool (HC_CDECL *_hoops_ARAAC)(OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr);

struct _hoops_PRAAC{
	_hoops_RGAAC 		_hoops_GIIH;
	_hoops_RGAAC 		_hoops_SAHH;
	_hoops_RGAAC 		_hoops_HRAAC;
	_hoops_RGAAC 		_hoops_IRAAC;
	_hoops_AGAAC 	_hoops_GHRGC;
	_hoops_PGAAC 	_hoops_AHRGC;
	_hoops_HGAAC 	_hoops_AGSP;
	_hoops_IGAAC	set_line_rendition;
	_hoops_CGAAC		_hoops_HHCGC;
	_hoops_SGAAC	_hoops_IHCGC;
	_hoops_GRAAC	_hoops_RIHGC;
	_hoops_RRAAC	_hoops_PIGH;
	_hoops_ARAAC	_hoops_GHAH;
};
 

#ifndef _hoops_CRAAC

/*_hoops_SRAAC*/
 
/*_hoops_GGAAC _hoops_SRAC _hoops_GAAAC*/
#define OGL_SET_3D_XFORM(_hoops_CSRGR, nr) \
	(*(_hoops_CSRGR)->_hoops_ACPGR._hoops_GIIH)(_hoops_CSRGR, nr)

#define OGL_SET_DC_XFORM(_hoops_CSRGR, nr) \
	(*(_hoops_CSRGR)->_hoops_ACPGR._hoops_SAHH)(_hoops_CSRGR, nr)

#define OGL_TURN_OFF_LIGHTS(_hoops_CSRGR) \
	(*(_hoops_CSRGR)->_hoops_ACPGR._hoops_GHRGC)(_hoops_CSRGR)

#define OGL_TURN_ON_LIGHTS(_hoops_CSRGR, nr, _hoops_HC) \
	(*(_hoops_CSRGR)->_hoops_ACPGR._hoops_AHRGC)(_hoops_CSRGR, nr, _hoops_HC)

#define OGL_SET_HANDEDNESS(_hoops_CSRGR, _hoops_IHCR, flags) \
	(*(_hoops_CSRGR)->_hoops_ACPGR._hoops_AGSP)(_hoops_CSRGR, _hoops_IHCR, flags)

#define OGL_SET_LINE_RENDITION(_hoops_CSRGR, nr, _hoops_HC) \
	(*(_hoops_CSRGR)->_hoops_ACPGR.set_line_rendition)(_hoops_CSRGR, nr, _hoops_HC)

#define OGL_SET_MATERIAL(_hoops_CSRGR, nr, _hoops_RRGH, _hoops_IASGR, _hoops_RAAAC) \
    (*(_hoops_CSRGR)->_hoops_ACPGR._hoops_HHCGC)(_hoops_CSRGR, nr, _hoops_RRGH, _hoops_IASGR, _hoops_RAAAC)

#define OGL_SET_TEXTURE_INDEXED_MATERIAL(_hoops_CSRGR, nr, _hoops_RRGH) \
	(*(_hoops_CSRGR)->_hoops_ACPGR._hoops_IHCGC)(_hoops_CSRGR, nr, _hoops_RRGH)

#define OGL_SET_OVERLAY_COLOR(_hoops_CSRGR, color) \
	(*(_hoops_CSRGR)->_hoops_ACPGR._hoops_RIHGC)(_hoops_CSRGR, color)
	
#define OGL_DEFINE_TEXTURE(_hoops_CSRGR, nr, txr, _hoops_GCI, _hoops_GRRA) \
	(*(_hoops_CSRGR)->_hoops_ACPGR._hoops_PIGH)(_hoops_CSRGR, nr, txr, _hoops_GCI, _hoops_GRRA)
	
#define OGL_DEFINE_INTERPOLATION_TEXTURE(_hoops_CSRGR, nr) \
	(*(_hoops_CSRGR)->_hoops_ACPGR._hoops_GHAH)(_hoops_CSRGR, nr)
	
#else

/*_hoops_AAAAC*/
 
/*_hoops_GGAAC _hoops_SRAC _hoops_GAAAC*/
#define OGL_SET_3D_XFORM(_hoops_CSRGR, nr) _hoops_GIIH(_hoops_CSRGR, nr);

#define OGL_SET_DC_XFORM(_hoops_CSRGR, nr) _hoops_SAHH(_hoops_CSRGR, nr);

#define OGL_TURN_OFF_LIGHTS(_hoops_CSRGR) _hoops_GHRGC(_hoops_CSRGR);

#define OGL_TURN_ON_LIGHTS(_hoops_CSRGR, nr, _hoops_HC) _hoops_AHRGC(_hoops_CSRGR, nr, _hoops_HC);

#define OGL_SET_HANDEDNESS(_hoops_CSRGR, _hoops_IHCR, flags) _hoops_AGSP(_hoops_CSRGR, _hoops_IHCR, flags);

#define OGL_SET_LINE_RENDITION(_hoops_CSRGR, nr, _hoops_HC) set_line_rendition(_hoops_CSRGR, nr, _hoops_HC);

#define OGL_SET_MATERIAL(_hoops_CSRGR, nr, _hoops_RRGH, _hoops_IASGR, _hoops_RAAAC) _hoops_HHCGC(_hoops_CSRGR, nr, _hoops_RRGH, _hoops_IASGR, _hoops_RAAAC);

#define OGL_SET_TEXTURE_INDEXED_MATERIAL(_hoops_CSRGR, nr, _hoops_RRGH) _hoops_IHCGC(_hoops_CSRGR, nr, _hoops_RRGH);

#define OGL_SET_OVERLAY_COLOR(_hoops_CSRGR, color) _hoops_RIHGC(_hoops_CSRGR, color);
	
#define OGL_DEFINE_TEXTURE(_hoops_CSRGR, nr) _hoops_PIGH(_hoops_CSRGR, nr);
	
#define OGL_DEFINE_INTERPOLATION_TEXTURE(_hoops_CSRGR, nr) _hoops_GHAH(_hoops_CSRGR, nr);
	
#endif

/*_hoops_PAAAC _hoops_GGAAC _hoops_SRAC _hoops_GAAAC*/

#define OGL_DEFAULT_SET_3D_XFORM(_hoops_CSRGR, nr) \
	(*(_hoops_CSRGR)->_hoops_PHCGC._hoops_GIIH)(_hoops_CSRGR, nr);

#define OGL_DEFAULT_SET_DC_XFORM(_hoops_CSRGR, nr) \
	(*(_hoops_CSRGR)->_hoops_PHCGC._hoops_SAHH)(_hoops_CSRGR, nr);

#define OGL_DEFAULT_TURN_OFF_LIGHTS(_hoops_CSRGR) \
	(*(_hoops_CSRGR)->_hoops_PHCGC._hoops_GHRGC)(_hoops_CSRGR);

#define OGL_DEFAULT_TURN_ON_LIGHTS(_hoops_CSRGR, nr, _hoops_HC) \
	(*(_hoops_CSRGR)->_hoops_PHCGC._hoops_AHRGC)(_hoops_CSRGR, nr, _hoops_HC);

#define OGL_DEFAULT_SET_HANDEDNESS(_hoops_CSRGR, _hoops_IHCR, flags) \
	(*(_hoops_CSRGR)->_hoops_PHCGC._hoops_AGSP)(_hoops_CSRGR, _hoops_IHCR, flags);

#define OGL_DEFAULT_SET_LINE_RENDITION(_hoops_CSRGR, nr, _hoops_HC) \
	(*(_hoops_CSRGR)->_hoops_PHCGC.set_line_rendition)(_hoops_CSRGR, nr, _hoops_HC);

#define OGL_DEFAULT_SET_MATERIAL(_hoops_CSRGR, nr, _hoops_RRGH, _hoops_IASGR, _hoops_RAAAC) \
	(*(_hoops_CSRGR)->_hoops_PHCGC._hoops_HHCGC)(_hoops_CSRGR, nr, _hoops_RRGH, _hoops_IASGR, _hoops_RAAAC);

#define OGL_DEFAULT_SET_TEXTURE_INDEXED_MATERIAL(_hoops_CSRGR, nr, _hoops_RRGH) \
	(*(_hoops_CSRGR)->_hoops_PHCGC._hoops_IHCGC)(_hoops_CSRGR, nr, _hoops_RRGH);

#define OGL_DEFAULT_SET_OVERLAY_COLOR(_hoops_CSRGR, color) \
	(*(_hoops_CSRGR)->_hoops_PHCGC._hoops_RIHGC)(_hoops_CSRGR, color);
	
#define OGL_DEFAULT_DEFINE_TEXTURE(_hoops_CSRGR, nr) \
	(*(_hoops_CSRGR)->_hoops_PHCGC._hoops_PIGH)(_hoops_CSRGR, nr);
	
#define OGL_DEFAULT_DEFINE_INTERPOLATION_TEXTURE(_hoops_CSRGR, nr) \
	(*(_hoops_CSRGR)->_hoops_PHCGC._hoops_GHAH)(_hoops_CSRGR, nr);


class OptimizerScratch;  //_hoops_CPCHR _hoops_CAPHR.  _hoops_CSHGR _hoops_HAAAC _hoops_GGR _hoops_IAAAC


struct OGLData {

#ifdef GLX_DRIVER

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

#ifdef WGL_DRIVER

    HWND hWND;

    HDC hDC; 
    HDC _hoops_SHGRR;
    _hoops_SIRAC pbuffer; /* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GCAC _hoops_GAR _hoops_IRS _hoops_CGSRC _hoops_CSCR */

    /*_hoops_IH _hoops_ICCGR _hoops_RSAIP*/
    bool _hoops_APSRC;
    HDC _hoops_HIISI; 
    HBITMAP hBitmap;
    HBITMAP old_hBitmap;

    HGLRC hGLRC;
    HDC   _hoops_APAAC;
    HGLRC _hoops_PPAAC;
    HGLRC overlayGLRC;
    WNDPROC _hoops_GIGRR;
    HPALETTE _hoops_RIGRR, _hoops_AIGRR;

    /*
     * _hoops_PGGRR
     */
    RECT _hoops_IIGRR;
    Int_XY _hoops_CIGRR;
    Int_XY _hoops_SIGRR;
    Int_XY _hoops_GCGRR;

    int _hoops_RCGRR;
    int _hoops_ACGRR;
    int _hoops_PCGRR;
    int _hoops_HCGRR;

    int yfudge;
    int _hoops_CCGRR;
    int _hoops_SCGRR;
    int mouse_y;

    /***********************/
    /*_hoops_CGHGH _hoops_HPAAC */
    int _hoops_RPICI;

    /* _hoops_IRRPI _hoops_HRCSR _hoops_HIGR */
    _hoops_SGRRR *_hoops_GRRRR;

#define      _hoops_RRRRR      0x01
#define      _hoops_PRRRR    0x04
#define      _hoops_ARRRR     0x02

    int _hoops_HRRRR;
    bool _hoops_IRRRR;
    bool pending_resize;
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

    /*_hoops_CAAAR"_hoops_SAAAR _hoops_SPAAC _hoops_ISHIP _hoops_GHAAC _hoops_RHAAC _hoops_HPAAC _hoops_AHAAC _hoops_RRAGC _hoops_PHAAC _hoops_AGGPA _hoops_RCSPR _hoops_HHAAC _hoops_GCSRC*/
    _hoops_RPSGR _hoops_PIGRR;
    char *_hoops_CRRRR;

    _hoops_PRAAC _hoops_ACPGR;
    _hoops_PRAAC _hoops_PHCGC;

    bool _hoops_SRRRR;
	int accumulation_bits;

    Image * _hoops_IHGRR;
    void *output_image_scratch;
	int _hoops_IHAAC;
    
    Display_Context const *dc;

	unsigned int _hoops_CHAAC;
    GLint _hoops_APHGC;
    GLint _hoops_IGARR;
    int _hoops_CGARR;

    int _hoops_AHHGC;

    bool _hoops_SHAAC;
    bool _hoops_PPHGC;
    bool _hoops_PHHGC; 
    int _hoops_AIPGA; 
    bool _hoops_IARGC;

    bool _hoops_GAGRR;
    bool _hoops_HSAC;
    bool _hoops_GIAAC;

    int _hoops_GAHGC;
    bool _hoops_CSHGC;
    bool _hoops_RIPGR;

#define _hoops_CHSGC 0xffff
    int *_hoops_IHSGC;
#define OGL_SCRATCH_SPACE_SIZE 4096 /* _hoops_PIHA _hoops_SHH _hoops_PRGI */
    Point *_hoops_SHSGC;
    Vector *_hoops_GISGC;
    RGB *_hoops_RISGC;
    float *_hoops_AISGC;

	int _hoops_HIHS;
	Test *_hoops_IIHS;

	OptimizerScratch *_hoops_PISGC;
#ifdef _hoops_PSRGC
	/* _hoops_RIAAC _hoops_CHR _hoops_AGPAA _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_IAGP _hoops_IIPRH, _hoops_PPR _hoops_CHR _hoops_PPP _hoops_RGAR _hoops_CGPR
	 * _hoops_RGHP (_hoops_GAR _hoops_CHIA _hoops_HPP _hoops_AIAAC) _hoops_IS _hoops_SRCH _hoops_HGPHP. */
#define _hoops_SSRGC  100000
	POINTER_SIZED_INT _hoops_ISRGC[2];
	int _hoops_HSRGC;
	int _hoops_CSRGC;
#endif


    GLint _hoops_SHRGC;
    int _hoops_CHRGC;
#define _hoops_GPRGC	-1
#define _hoops_RHRGC	0
#define _hoops_ICRGC	1
#define _hoops_RPRGC	2
    int _hoops_SARGC;
    bool _hoops_GIRGC[32];
    bool _hoops_RIRGC;
    bool _hoops_AIRGC;

    GLint _hoops_GAH;
    GLint _hoops_HPHGC;

#define OGL_POLYMARKER_BATCH_SIZE 600
	int	_hoops_PHAI;

    bool _hoops_PPAGC;
    float alter _hoops_SRIRC[4];

    int _hoops_SPIGC;
    bool _hoops_GICGC;

    bool _hoops_IICH;
    GLfloat alter _hoops_CIRGC[16];
    GLfloat alter _hoops_HPCGC[4][4];	

#define _hoops_CCC	(_hoops_GARRR) -1
#define _hoops_RARRR(_hoops_AARRR)		(-(_hoops_AARRR))
#define _hoops_PARRR(_hoops_AARRR)		(_hoops_AARRR)
    _hoops_GARRR _hoops_HCAC;
    _hoops_GARRR _hoops_RPCI;
    _hoops_GARRR _hoops_IARRR;
    _hoops_GARRR _hoops_ICAC;
    _hoops_GARRR _hoops_SARRR;
    _hoops_GARRR _hoops_RSHH;
	_hoops_GARRR _hoops_GPRRR;
	bool _hoops_SHIGC;

    /* _hoops_IHAH _hoops_SCGR _hoops_HIHH _hoops_PIAP */
#define _hoops_RSARR		(0xfeeeeeedU)
    struct {
        int _hoops_GRRA;
        bool _hoops_RGAGC;
        GLenum _hoops_PIAAC;
        int _hoops_CRIA;
        Line_Style	line_style;
        GLfloat line_weight;
        Driver_Color color;
        Driver_Color _hoops_HIAAC;
        Driver_Color _hoops_GPIR;

        /* _hoops_IIAAC: */
#define _hoops_RRIGC                   0
#define _hoops_GRIGC                1
#define _hoops_SGIGC             2
#define _hoops_CIAAC			3
        int _hoops_PRIGC;
        float		_hoops_PCHH;
        float		_hoops_GSCH[2];
        float		_hoops_ARIGC;
		bool		_hoops_HRIGC;

        GLenum _hoops_SIAAC;

        /* _hoops_ASCA _hoops_CAPRR: */
#define DRAW_MODE_NORMAL	0
#define DRAW_MODE_OVERLAY	1
        int _hoops_GGAGC;

        /* _hoops_ASCA _hoops_APHSR _hoops_AIH _hoops_PIHHR */
        bool _hoops_SCHGC;

        struct
        {
            RGBA _hoops_PGAGC;		/* _hoops_AASR _hoops_PPR _hoops_SPI _hoops_HAIR _hoops_IIGR _hoops_GCAAC _hoops_AGSAR */
            RGB _hoops_SGC;	/* _hoops_GHI _hoops_RCAAC _hoops_IIGR _hoops_GCAAC _hoops_AGSAR */
            RGB _hoops_IRC;	/* _hoops_ACAAC _hoops_AGSAR */
            RGB _hoops_IIRGC;	/* _hoops_RH _hoops_HRSAR _hoops_AASR _hoops_PCAAC _hoops_GGR _hoops_IRS _hoops_HIRA */
            GLfloat _hoops_HGAGC;
        }
        _hoops_ISHIR, _hoops_IGAGC;

        GLint _hoops_CGAGC;	/* _hoops_IRGH _hoops_PAR _hoops_PGGS _hoops_HCAAC _hoops_IH _hoops_RH _hoops_RRR _hoops_SARR*/

        /* _hoops_IAPRR _hoops_CIPH */
        bool _hoops_APH;
        GLenum _hoops_PHIGC;

#define _hoops_ICAAC 	0
#define _hoops_CCAAC 	1
        /* _hoops_IGH _hoops_HHAHP _hoops_CIHH _hoops_HRGR _hoops_PPP */
        bool _hoops_SCAAC;	
        GLint _hoops_GSAAC;		
        GLint _hoops_RSAAC;
        GLsizei _hoops_ASAAC;
        GLsizei _hoops_PSAAC;

        GLint _hoops_HSAAC;		
        GLint _hoops_ISAAC;
        GLsizei _hoops_CSAAC;
        GLsizei _hoops_SSAAC;

        GLfloat _hoops_GGPAC;
        GLfloat _hoops_RGPAC;

        GLint _hoops_AGPAC;

        /* _hoops_IGH _hoops_SPRS _hoops_HPGIR _hoops_HRGR _hoops_PPP */
        bool _hoops_AAIAR;	

        GLenum _hoops_PGPAC;
        int _hoops_SSIGC;

        bool _hoops_HGPAC;
        bool _hoops_IGPAC;
        bool _hoops_CGPAC;
        bool _hoops_SGPAC[8];
		int _hoops_GRGAC;

        /* _hoops_PIP _hoops_SGS _hoops_SR _hoops_CGH _hoops_IIP _hoops_GGCR _hoops_SRSRR _hoops_IH _hoops_GRPAC (_hoops_HPGR _hoops_CHGC _hoops_HAR
         * _hoops_ARI) _hoops_PGGA _hoops_SCH _hoops_HRGR _hoops_GIAH _hoops_RIR-_hoops_HH _hoops_PIAP, _hoops_HAR _hoops_RIR-_hoops_RRPAC */
#define OGL_MAX_TEXTURE_UNITS 8
        GLint _hoops_RAGRR[OGL_MAX_TEXTURE_UNITS];
        GLint _hoops_AAGRR[OGL_MAX_TEXTURE_UNITS];
        GLint _hoops_PAAGC[OGL_MAX_TEXTURE_UNITS];
        GLint _hoops_HAAGC[OGL_MAX_TEXTURE_UNITS];
        bool _hoops_ARPAC[OGL_MAX_TEXTURE_UNITS];
        GLint _hoops_IAAGC[OGL_MAX_TEXTURE_UNITS];
        GLenum _hoops_PRPAC[OGL_MAX_TEXTURE_UNITS];		//_hoops_RPPGC _hoops_PAR _hoops_HRPAC _hoops_RPP _hoops_PPP
        GLuint _hoops_SGAGC[OGL_MAX_TEXTURE_UNITS];
        GLuint _hoops_PSAH;
        GLuint _hoops_GSCGC;
        Named_Material* _hoops_AAAGC;


        bool  _hoops_IRPAC;

        int	_hoops_CRPAC;
        float	_hoops_CHHCR;
        GLenum	_hoops_SSHGC;
#define _hoops_SRPAC 0
#define _hoops_GAPAC  1
        int _hoops_HPAGC;

        struct {
            GLuint _hoops_HPRGC;
            float gloss;
            _hoops_HHRA const *_hoops_CARGC;
        } _hoops_HAACP;

        int _hoops_GHAGC;
        GLboolean _hoops_AAIH;
        GLboolean _hoops_RAIH;
		GLboolean _hoops_IASP;
        bool _hoops_IPAGC;
        bool _hoops_SCIRC;

		bool _hoops_RAPAC;
		GLfloat _hoops_AAPAC;

        OGL_Render_Control _hoops_PAPAC;

        GLuint _hoops_SPAGC;
        GLenum _hoops_CPAGC;

        GLenum _hoops_HAPAC;
        GLenum _hoops_IAPAC;
        bool _hoops_CAPAC;

		//_hoops_SAPAC *_hoops_PACIP;
    } _hoops_CSC;

    bool _hoops_PRHGC;

#define _hoops_CRPH		(FP_WINDOW_TRANSPARENT + 1)
    /* 32b_hoops_SCH _hoops_SISR 32b_hoops_SCH _hoops_PISH */
    GLubyte alter _hoops_SRPH[_hoops_CRPH][128];	
	
	/* _hoops_IH _hoops_IHSP _hoops_GPPAC _hoops_PPR _hoops_IPSP-_hoops_PAPR _hoops_PAIA */
	int _hoops_AGAGC;
    unsigned int _hoops_RIPRC[32];

    /*_hoops_HRARR _hoops_SCPGH */
    _hoops_ARARR *_hoops_PRARR;

    /* _hoops_IH _hoops_GCAC _hoops_PPPHH _hoops_GRRC */
    GLUnurbsObj *_hoops_SCPIR;

    /* _hoops_IH _hoops_ICHRR-_hoops_RPPAC _hoops_ISPAA _hoops_IIGR _hoops_HHGSR[_hoops_CSPH,3d]_hoops_APPAC _hoops_PSCH */
    bool _hoops_GCHGC;
    bool _hoops_GSIGC;
    _hoops_HHRA const *_hoops_CARGC;
	float _hoops_SAAGC;
    float _hoops_CSIH;
    long _hoops_IIIH;
    long _hoops_SIIH;
    int window_width;
    int window_height;
    long _hoops_GPAGC;
    long _hoops_RPAGC;
    _hoops_SCASP _hoops_GACGC;
    _hoops_GARRR _hoops_APAGC;
	bool _hoops_CRHGC;

    /*_hoops_SPAAC _hoops_ISHIP _hoops_HHAAC _hoops_SCPGH _hoops_AHAAC _hoops_RRAGC _hoops_PPPAC _hoops_GHAAC _hoops_RHAAC _hoops_HPPAC*/

    /* _hoops_IHPR _hoops_RPP _hoops_RH _hoops_PPGRR _hoops_SSCP _hoops_IPPAC*/ 
    /* _hoops_PRGI _hoops_RPP _hoops_HHRPR _hoops_AIR _hoops_RPCC/_hoops_RAHRH _hoops_RHAP _hoops_HAR */
    bool _hoops_SHCGC; 
    bool _hoops_RAPGC;
    bool _hoops_AAPGC;
	bool _hoops_CAPGC;
    bool _hoops_IRPGC;
	bool _hoops_CRPGC;
	bool _hoops_PGHGC;
    int _hoops_SGPGC;
    int _hoops_GRPGC;
    int _hoops_RRPGC;

	bool _hoops_SRPGC;
	bool _hoops_GAPGC;
    bool _hoops_RAHGC;
    bool _hoops_PAHGC;	
    bool _hoops_CPPAC;	
    bool _hoops_AAHGC; 
    bool _hoops_PAPGC;
    bool _hoops_RRSGC;
	bool _hoops_HAPGC;
	bool _hoops_PPPGC;
	bool _hoops_AHPGC;
	bool _hoops_SPPGC;
	bool _hoops_GHPGC;

#ifdef WGL_DRIVER
    bool _hoops_SPPAC;
    wglGetPixelFormatAttribivARBProc wglGetPixelFormatAttribivARB;
    wglChoosePixelFormatARBProc wglChoosePixelFormatARB;

    wglCreateBufferRegionARBProc wglCreateBufferRegionARB;
    wglDeleteBufferRegionARBProc wglDeleteBufferRegionARB;
    wglSaveBufferRegionARBProc wglSaveBufferRegionARB;
    wglRestoreBufferRegionARBProc wglRestoreBufferRegionARB;

    wglCreatePbufferARBProc wglCreatePbufferARB;
    wglGetPbufferDCARBProc wglGetPbufferDCARB;
    wglReleasePbufferDCARBProc wglReleasePbufferDCARB;
    wglDestroyPbufferARBProc wglDestroyPbufferARB;
    wglQueryPbufferARBProc wglQueryPbufferARB;

    wglMakeContextCurrentARBProc wglMakeContextCurrentARB;
#endif

    bool _hoops_ACPGC;
    glNewKTXBufferRegionProc glNewKTXBufferRegion;
    glDeleteKTXBufferRegionProc glDeleteKTXBufferRegion;
    glReadKTXBufferRegionProc glReadKTXBufferRegion;
    glDrawKTXBufferRegionProc glDrawKTXBufferRegion;

#ifdef glActiveTextureARB
#  undef glActiveTextureARB
#endif
#ifdef glGenProgramsARB
#  undef glGenProgramsARB
#endif
#ifdef glDeleteProgramsARB
#  undef glDeleteProgramsARB
#endif
#ifdef glProgramStringARB
#  undef glProgramStringARB
#endif
#ifdef glBindProgramARB
#  undef glBindProgramARB
#endif
#ifdef glShaderSourceARB
#  undef glShaderSourceARB
#endif
#ifdef glCompileShaderARB
#  undef glCompileShaderARB
#endif
#ifdef glGetInfoLogARB
#  undef glGetInfoLogARB
#endif
#ifdef glAttachObjectARB
#  undef glAttachObjectARB
#endif
#ifdef _hoops_PSPGC
#  undef _hoops_PSPGC
#endif
#ifdef glDeleteShaderARB
#  undef glDeleteShaderARB
#endif
#ifdef glLinkProgramARB
#  undef glLinkProgramARB
#endif
#ifdef glCreateShaderObjectARB
#  undef glCreateShaderObjectARB
#endif
#ifdef glDeleteProgramARB
#  undef glDeleteProgramARB
#endif
#ifdef glUseProgramObjectARB
#  undef glUseProgramObjectARB
#endif

#ifdef glGetObjectParameterfvARB
#  undef glGetObjectParameterfvARB
#endif
#ifdef glGetObjectParameterivARB
#  undef glGetObjectParameterivARB
#endif

    glActiveTextureARBProc glActiveTextureARB;
    glClientActiveTextureARBProc _hoops_RGHGC;
    glMultiTexCoord2fvARBProc glMultiTexCoord2fvARB;
    glMultiTexCoord3fvARBProc glMultiTexCoord3fvARB;
    GLint _hoops_AGHGC;

    bool _hoops_GSPGC;
    bool _hoops_RSPGC;
	bool _hoops_ASPGC;
    glGenProgramsARBProc glGenProgramsARB;
    glDeleteProgramsARBProc glDeleteProgramsARB;
    glProgramStringARBProc glProgramStringARB;
    glBindProgramARBProc glBindProgramARB;

    bool _hoops_GGHGC;
	glShaderSourceARBProc glShaderSourceARB;
	glCompileShaderARBProc glCompileShaderARB;
	glAttachObjectARBProc glAttachObjectARB;
	glGetInfoLogARBProc glGetInfoLogARB;
	glDetachObjectARBProc _hoops_PSPGC;
	glDeleteShaderARBProc glDeleteShaderARB;
	glLinkProgramARBProc glLinkProgramARB;
	glCreateShaderObjectARBProc glCreateShaderObjectARB;
	glCreateProgramObjectARBProc glCreateProgramObjectARB;
	glDeleteProgramARBProc glDeleteProgramARB;
	glUseProgramObjectARBProc glUseProgramObjectARB;
	glGetObjectParameterfvARBProc glGetObjectParameterfvARB;
	glGetObjectParameterivARBProc glGetObjectParameterivARB;
	glProgramEnvParameter4fARBProc glProgramEnvParameter4fARB;

    /* _hoops_IAGP _hoops_RACGH */
    glGenQueriesARBProc glGenQueries;
    glDeleteQueriesARBProc glDeleteQueries;
    glBeginQueryARBProc glBeginQueryARB;
    glEndQueryARBProc glEndQueryARB;
    glGetQueryivARBProc glGetQueryivARB;
    glGetQueryObjectuivARBProc glGetQueryObjectuiv;
	glBeginOcclusionQueryNVProc glBeginOcclusionQueryNV;
    glEndOcclusionQueryNVProc glEndOcclusionQueryNV;
    bool _hoops_CCRGC;

	/* _hoops_GHPAC */
	bool _hoops_IHPGC;
	glBindBufferARBProc _hoops_PSPGI;
	glDeleteBuffersARBProc _hoops_ISPGI;			
	glGenBuffersARBProc _hoops_CHPGC;				
	glIsBufferARBProc _hoops_SHPGC;					
	glBufferDataARBProc _hoops_HSPGI;				
	glBufferSubDataARBProc _hoops_GIPGC;			
	glGetBufferSubDataARBProc _hoops_RIPGC;		
	glMapBufferARBProc _hoops_AIPGC;				
	glUnmapBufferARBProc _hoops_PIPGC;				
	glGetBufferParameterivARBProc _hoops_HIPGC;		
	glGetBufferPointervARBProc _hoops_IIPGC;		

	/* _hoops_RHPAC */
	glDrawRangeElementsEXTProc glDrawRangeElementsEXT;
	glMultiDrawElementsEXTProc glMultiDrawElementsEXT;
	glMultiDrawArraysEXTProc glMultiDrawArraysEXT;

	/* _hoops_RSRGC _hoops_CGRAC */
	bool _hoops_HHPGC;
	glGenFencesNVProc glGenFencesNV;
	glDeleteFencesNVProc glDeleteFencesNV; 
	glSetFenceNVProc glSetFenceNV;
	glTestFenceNVProc glTestFenceNV;
	glFinishFenceNVProc glFinishFenceNV;
	glIsFenceNVProc glIsFenceNV;
	glGetFenceivNVProc glGetFenceivNV; 

	/* _hoops_SCRGC _hoops_SGRAC */
	bool _hoops_HPPGC;
	glPointParameterfARBProc _hoops_IPPGC;
	glPointParameterfvARBProc _hoops_CPPGC;

	/* _hoops_AHPAC _hoops_IGR */
#define _hoops_RCPGC 0xFFFFFFFF
	bool _hoops_IAPGC;
	glPrimitiveRestartNVProc _hoops_SIPGC;
	glPrimitiveRestartIndexNVProc _hoops_GCPGC;

	/* _hoops_SCRGC _hoops_GRAR _hoops_GRRAC */
	bool _hoops_RHPGC;
	glCompressedTexImage2DARBProc glCompressedTexImage2DARB;

	/* _hoops_SCRGC _hoops_GRAR _hoops_GRRAC */
	bool _hoops_PHPGC;
	glTexImage3DProc glTexImage3D;
	glTexSubImage3DProc glTexSubImage3D;

	/* _hoops_RRRAC */
	bool _hoops_RCAGC;
	bool _hoops_SSAGC;

	glIsRenderbufferEXTProc _glIsRenderbufferEXT;
	glBindRenderbufferEXTProc _hoops_ACAGC;
	glDeleteRenderbuffersEXTProc _glDeleteRenderbuffersEXT;
	glGenRenderbuffersEXTProc _hoops_PCAGC;
	glRenderbufferStorageEXTProc _hoops_HCAGC;
	glGetRenderbufferParameterivEXTProc glGetRenderbufferParameterivEXT;

	glIsFramebufferEXTProc _hoops_ICAGC;
	glBindFramebufferEXTProc _hoops_HIAGC;
	glDeleteFramebuffersEXTProc _hoops_AIAGC;
	glGenFramebuffersEXTProc _hoops_CCAGC;
	glCheckFramebufferStatusEXTProc _hoops_IIAGC;

	glFramebufferTexture1DEXTProc _hoops_SCAGC;
	glFramebufferTexture2DEXTProc _hoops_GSAGC;
	glFramebufferTexture3DEXTProc _hoops_RSAGC;

	glFramebufferRenderbufferEXTProc _hoops_ASAGC;
	glGetFramebufferAttachmentParameterivEXTProc glGetFramebufferAttachmentParameterivEXT;
	glGenerateMipmapEXTProc glGenerateMipmapEXT;

	GLuint _hoops_RIAGC;
	GLuint _hoops_CHAGC;
	GLuint _hoops_GIAGC;
	GLuint _hoops_RGPGC;
	GLuint _hoops_SHAGC;
	GLint _hoops_PSAGC;
	GLint _hoops_HSAGC;

	int _hoops_ISAGC;
	int _hoops_CSAGC;

#if _hoops_HRGAC
	_hoops_PHPAC	_hoops_HHPAC;
#endif
	void *			_hoops_IHPAC;
	int				_hoops_CHPAC;
	int				_hoops_SHPAC;

    /* _hoops_IGI _hoops_IH _hoops_ASCA _hoops_GCPA */
    GLUquadric *_hoops_IGSGC; 
    GLUquadric *_hoops_CGSGC;
    /* _hoops_IGI _hoops_IH _hoops_ASCA _hoops_CRCIA */
    GLUquadric *_hoops_SGSGC; 
    GLUquadric *_hoops_GRSGC;

    bool _hoops_GSGRR;
    bool _hoops_AHPI;
    bool _hoops_HCPRC;

    _hoops_RCR *_hoops_HHSGC[ _hoops_PHSGC + 1 ];
    bool _hoops_PSGRC;

#define	_hoops_APRRR	16
#define _hoops_HISGC	1
	GLuint _hoops_IISGC[_hoops_HISGC];
	GLuint _hoops_CISGC[_hoops_APRRR+1];
	int _hoops_CSSRC;
	int _hoops_SSSRC;
    bool _hoops_GIIGC;
    int _hoops_ISSRC;
	GLuint _hoops_RHSGC;
	GLuint _hoops_AHSGC;

	GLuint _hoops_SISGC;
	GLuint _hoops_GCSGC;
	GLuint _hoops_SSCRC;
	GLuint _hoops_GGSRC;

	Integer32				_hoops_ISCI;
	Integer32				_hoops_GGHGR;
	OGL_Collector			*_hoops_CIGI;
	OGL_Collector			*_hoops_SSPGR;
	unsigned Integer32		_hoops_RGHGR;
	bool					_hoops_GGCGC;
	_hoops_GRGGI			*_hoops_GIPAC;

	bool _hoops_HRSRC;

	bool _hoops_GIHGC;
	_hoops_SICRC *_hoops_GHSGC;
	int	_hoops_RIPAC;
	int	_hoops_AIPAC;

	_hoops_SICRC *_hoops_PCHGC;
	_hoops_SICRC *_hoops_CCHGC;
	int	_hoops_HCHGC;
	int	_hoops_ICHGC;
	bool _hoops_PIPAC;

	int _hoops_HPCRC;
	bool _hoops_SPGRC;
};


#ifndef _hoops_HIPAC
# ifdef _hoops_GGHSH
#   define _hoops_IIPAC(_hoops_CSRGR)  _hoops_GHIA (\
      _hoops_CSRGR->_hoops_CSC._hoops_HPAGC = _hoops_SRPAC;    \
      if (_hoops_CSRGR->_hoops_PHHGC)                       \
          glDisable(MULTISAMPLE_ARB);                   \
      else                                                \
          _hoops_CIPAC(_hoops_CSRGR);                \
  )

#   define _hoops_SIPAC(_hoops_CSRGR)  _hoops_GHIA (\
      _hoops_CSRGR->_hoops_CSC._hoops_HPAGC = _hoops_GAPAC;     \
      if (_hoops_CSRGR->_hoops_PHHGC) {                     \
          glEnable(MULTISAMPLE_ARB);                    \
      } else {                                            \
          _hoops_GCPAC(_hoops_CSRGR);                \
		  _hoops_ASGRC(_hoops_CSRGR);						\
      }                                                   \
  )
# else
#   define _hoops_IIPAC(_hoops_CSRGR)  _hoops_GHIA (\
      _hoops_CSRGR->_hoops_CSC._hoops_HPAGC = _hoops_SRPAC;    \
      if (_hoops_CSRGR->_hoops_PHHGC)                       \
          glDisable(MULTISAMPLE_ARB);                   \
  )

#   define _hoops_SIPAC(_hoops_CSRGR)  _hoops_GHIA (\
      _hoops_CSRGR->_hoops_CSC._hoops_HPAGC = _hoops_GAPAC;     \
      if (_hoops_CSRGR->_hoops_PHHGC)                       \
          glEnable(MULTISAMPLE_ARB);                    \
  )
# endif
# define _hoops_HISP(_hoops_CSRGR, mode) _hoops_GHIA (\
      if (_hoops_CSRGR->_hoops_CSC._hoops_SCHGC) {                        \
          if (_hoops_CSRGR->_hoops_CSC._hoops_HPAGC)            \
              _hoops_IIPAC(_hoops_CSRGR);              \
      }                                                   \
      else if (_hoops_CSRGR->_hoops_CSC._hoops_HPAGC != mode) {  \
          if (mode)                                        \
              _hoops_SIPAC(_hoops_CSRGR);               \
          else                                            \
              _hoops_IIPAC(_hoops_CSRGR);              \
      }                                                   \
)
#else
# define _hoops_IIPAC(_hoops_CSRGR,mode) 
# define _hoops_SIPAC(_hoops_CSRGR,mode) 
# define _hoops_HISP(_hoops_CSRGR,mode) 
#endif


#define _hoops_HHRRC(_hoops_CSRGR, _hoops_RCPAC)	_hoops_GHIA(	\
	if (_hoops_CSRGR->glActiveTextureARB) {					\
		(*_hoops_CSRGR->glActiveTextureARB)(GL_TEXTURE0_ARB + _hoops_RCPAC); }	\
	_hoops_CSRGR->_hoops_CSC._hoops_GRRA = _hoops_RCPAC;					\
)

#define _hoops_PPRGC(_hoops_CSRGR, _hoops_RCPAC)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_GRRA != _hoops_RCPAC)  {			\
		_hoops_HHRRC (_hoops_CSRGR, _hoops_RCPAC);  }			\
)


#define _hoops_ACPAC(_hoops_CSRGR, _hoops_AHCGR, _hoops_PCPAC, _hoops_HCPAC) _hoops_GHIA(\
	_hoops_PPRGC(_hoops_CSRGR, _hoops_AHCGR); \
	glBindTexture (_hoops_PCPAC, _hoops_HCPAC); \
	_hoops_CSRGR->_hoops_CSC._hoops_SGAGC[_hoops_AHCGR] = _hoops_HCPAC; \
	_hoops_CSRGR->dc->_hoops_IGGI->_hoops_GSAC++; \
	_hoops_APSS(_hoops_CSRGR, _hoops_AHCGR); \
)

#define _hoops_IPRGC(_hoops_CSRGR, _hoops_AHCGR, _hoops_PCPAC, _hoops_HCPAC) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_SGAGC[_hoops_AHCGR] != _hoops_HCPAC) \
		_hoops_ACPAC (_hoops_CSRGR, _hoops_AHCGR, _hoops_PCPAC, _hoops_HCPAC); \
)

#define _hoops_AARRC(_hoops_CSRGR, _hoops_RHIA) _hoops_GHIA (\
	_hoops_PPRGC(_hoops_CSRGR, _hoops_RHIA);					\
 	if (_hoops_CSRGR->_hoops_CSC._hoops_PRPAC[_hoops_RHIA])	{				\
		GLenum target = _hoops_CSRGR->_hoops_CSC._hoops_PRPAC[_hoops_RHIA]; \
		glDisable (target);						\
		_hoops_CSRGR->_hoops_CSC._hoops_PRPAC[_hoops_RHIA] = false;				\
		if (_hoops_RHIA == 0 && _hoops_CSRGR->_hoops_GIIGC && _hoops_CSRGR->_hoops_ISSRC > 0) \
			(*_hoops_CSRGR->glBindProgramARB) (GL_FRAGMENT_PROGRAM_ARB, _hoops_CSRGR->_hoops_RHSGC); \
	} \
)

#define _hoops_RSGRC(_hoops_CSRGR, target, _hoops_RHIA) _hoops_GHIA (\
	_hoops_PPRGC(_hoops_CSRGR, _hoops_RHIA);					\
 	if (!_hoops_CSRGR->_hoops_CSC._hoops_PRPAC[_hoops_RHIA])	{				\
		glEnable (target);						\
		_hoops_CSRGR->_hoops_CSC._hoops_PRPAC[_hoops_RHIA] = target;				\
		if (_hoops_RHIA == 0 && _hoops_CSRGR->_hoops_GIIGC && _hoops_CSRGR->_hoops_ISSRC > 0) \
			(*_hoops_CSRGR->glBindProgramARB) (GL_FRAGMENT_PROGRAM_ARB, _hoops_CSRGR->_hoops_AHSGC); \
	} \
)


/* _hoops_PPPSR _hoops_HIIA _hoops_HII _hoops_AAPA _hoops_ICPAC _hoops_IS _hoops_IIIGC _hoops_SRHR _hoops_GHSHA */
static const GLenum _hoops_CCPAC[]  = { GL_BACK,  GL_BACK_LEFT,  GL_BACK_RIGHT  };
static const GLenum _hoops_SCPAC[] = { GL_FRONT, GL_FRONT_LEFT, GL_FRONT_RIGHT };

#define _hoops_ASCGC(_hoops_CSRGR, mode) _hoops_GHIA (									\
	if (_hoops_CSRGR->_hoops_SRRRR)													\
		glDrawBuffer (_hoops_CCPAC[_hoops_CSRGR->_hoops_CSC._hoops_CRPAC = mode]);		\
	else																			\
		glDrawBuffer (_hoops_SCPAC[_hoops_CSRGR->_hoops_CSC._hoops_CRPAC = mode]); 	\
)

#define _hoops_RGIGC(_hoops_CSRGR, mode) _hoops_GHIA (\
	if (_hoops_CSRGR->_hoops_CSC._hoops_CRPAC != mode) 		\
		_hoops_ASCGC(_hoops_CSRGR, mode);				\
)



#define _hoops_HIRGC(_hoops_AIGCR, _hoops_PIGCR) ((_hoops_AIGCR).red == (_hoops_PIGCR).red && (_hoops_AIGCR).green == (_hoops_PIGCR).green && (_hoops_AIGCR).blue == (_hoops_PIGCR).blue)

#define FORCE_CULLING(_hoops_CSRGR, face)		_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_PHIGC = face; \
	glCullFace (face); \
	_hoops_CSRGR->_hoops_CSC._hoops_APH = true; \
	glEnable (GL_CULL_FACE); \
)

#define _hoops_RHSA(_hoops_CSRGR, face)		_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_PHIGC != face) { \
		_hoops_CSRGR->_hoops_CSC._hoops_PHIGC = face; \
		glCullFace (face); \
	} \
	if (!_hoops_CSRGR->_hoops_CSC._hoops_APH) { \
		_hoops_CSRGR->_hoops_CSC._hoops_APH = true; \
		glEnable (GL_CULL_FACE); \
	} \
)

#define _hoops_ICCGC(_hoops_CSRGR) _hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_APH = false; \
	glDisable (GL_CULL_FACE); \
)

#define ENSURE_CULLING_OFF(_hoops_CSRGR) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_APH) { \
		_hoops_ICCGC (_hoops_CSRGR); \
	} \
)

#define FORCE_SHADE_MODEL(_hoops_CSRGR, _hoops_CRRR) _hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_SIAAC = _hoops_CRRR; \
	glShadeModel (_hoops_CRRR); \
)

#define ENSURE_SHADE_MODEL(_hoops_CSRGR, _hoops_CRRR) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_SIAAC != _hoops_CRRR) \
		FORCE_SHADE_MODEL (_hoops_CSRGR, _hoops_CRRR); \
)



#define FORCE_LIGHTS_OFF(_hoops_CSRGR) _hoops_GHIA(\
	OGL_TURN_OFF_LIGHTS(_hoops_CSRGR); \
	_hoops_CSRGR->_hoops_SARGC = _hoops_RHRGC; \
)

#define _hoops_GSPAC(_hoops_CSRGR, nr, _hoops_HC, mode) _hoops_GHIA(\
	OGL_TURN_ON_LIGHTS(_hoops_CSRGR, nr, (_hoops_HC)); \
	_hoops_CSRGR->_hoops_SARGC = mode; \
	_hoops_CSRGR->_hoops_IARRR = (_hoops_HC)->_hoops_CPA; \
)

#define _hoops_SCIGC(_hoops_CSRGR) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_SARGC != _hoops_RHRGC) \
		FORCE_LIGHTS_OFF(_hoops_CSRGR); \
)

#define _hoops_GIGRC(_hoops_CSRGR, nr, _hoops_HC) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_SARGC != _hoops_ICRGC || _hoops_CSRGR->_hoops_IARRR != (_hoops_HC)->_hoops_CPA || \
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.red != nr->_hoops_IRR->_hoops_HASR.red || \
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.green != nr->_hoops_IRR->_hoops_HASR.green || \
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.blue != nr->_hoops_IRR->_hoops_HASR.blue) \
		_hoops_GSPAC(_hoops_CSRGR, (nr), (_hoops_HC), _hoops_ICRGC); \
)

#define _hoops_APRGC(_hoops_CSRGR, nr, _hoops_HC) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_SARGC != _hoops_RPRGC || _hoops_CSRGR->_hoops_IARRR != (_hoops_HC)->_hoops_CPA || \
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.red != nr->_hoops_IRR->_hoops_HASR.red || \
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.green != nr->_hoops_IRR->_hoops_HASR.green || \
		_hoops_CSRGR->_hoops_CSC._hoops_ISHIR._hoops_IIRGC.blue != nr->_hoops_IRR->_hoops_HASR.blue) \
		_hoops_GSPAC(_hoops_CSRGR, (nr), (_hoops_HC), _hoops_RPRGC); \
)

#define _hoops_HCCGC(_hoops_CSRGR, mode) _hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_SSIGC = mode; \
	glLightModeli (GL_LIGHT_MODEL_TWO_SIDE, mode); \
)

#define ENSURE_TWO_SIDED(_hoops_CSRGR, mode)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_SSIGC != mode) \
		_hoops_HCCGC (_hoops_CSRGR, mode); \
)

#define _hoops_PCCGC(_hoops_CSRGR, mode)	_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_PGPAC = mode; \
	glFrontFace (mode); \
)

#define ENSURE_FRONT_FACE(_hoops_CSRGR, mode) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_PGPAC != mode) \
		_hoops_PCCGC (_hoops_CSRGR, mode); \
)


#define _hoops_RSPAC(_hoops_CSRGR, _hoops_HRSPH) _hoops_GHIA(\
	RGB			_hoops_PAGR; \
	(_hoops_CSRGR)->_hoops_CSC._hoops_GPIR = *(_hoops_HRSPH); \
	_hoops_PAGR.red   = _hoops_IRGCR ((_hoops_HRSPH)->_hoops_HRIR.r) * (1.0f/255.0f); \
	_hoops_PAGR.green = _hoops_IRGCR ((_hoops_HRSPH)->_hoops_HRIR.g) * (1.0f/255.0f); \
	_hoops_PAGR.blue  = _hoops_IRGCR ((_hoops_HRSPH)->_hoops_HRIR.b) * (1.0f/255.0f); \
	glClearColor (_hoops_PAGR.red, _hoops_PAGR.green, _hoops_PAGR.blue, 1.0f); \
)

#define _hoops_PPPRC(_hoops_CSRGR, _hoops_HRSPH)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_GPIR != *(_hoops_HRSPH) || \
		_hoops_CSRGR->_hoops_CSC._hoops_GPIR == _hoops_CAHSR::_hoops_SAHSR) \
		_hoops_RSPAC(_hoops_CSRGR, _hoops_HRSPH); \
)


#define _hoops_RIIGC(_hoops_CSRGR) _hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_PRIGC != _hoops_RRIGC || \
		_hoops_CSRGR->_hoops_CSC._hoops_GSCH[0] != 0 || \
		_hoops_CSRGR->_hoops_CSC._hoops_GSCH[1] != 0) { \
		_hoops_PGIGC( _hoops_CSRGR, nr, _hoops_RRIGC ); \
	} \
)


#define _hoops_RPSRC(_hoops_CSRGR) _hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_PRIGC != _hoops_CIAAC || \
		_hoops_CSRGR->_hoops_CSC._hoops_GSCH[0] != 0 || \
		_hoops_CSRGR->_hoops_CSC._hoops_GSCH[1] != 1) { \
		_hoops_PGIGC( _hoops_CSRGR, null, _hoops_CIAAC ); \
	} \
)

#define _hoops_AIIGC(_hoops_CSRGR,nr) _hoops_GHIA( \
	if (BIT((nr)->transform_rendition->flags, _hoops_PASP)) { \
		if (_hoops_CSRGR->_hoops_CSC._hoops_PRIGC != _hoops_GRIGC || \
			_hoops_CSRGR->_hoops_CSC._hoops_GSCH[0] != (nr)->transform_rendition->_hoops_GSCH[0] || \
			_hoops_CSRGR->_hoops_CSC._hoops_GSCH[1] != (nr)->transform_rendition->_hoops_GSCH[1] || \
			_hoops_CSRGR->_hoops_CSC._hoops_ARIGC != \
				(nr)->transform_rendition->_hoops_SHIH) { \
			_hoops_PGIGC(_hoops_CSRGR, nr, _hoops_GRIGC); \
		} \
	} else { \
		_hoops_RIIGC ((_hoops_CSRGR)); \
	} \
)


#define _hoops_PIIGC(_hoops_CSRGR,nr) _hoops_GHIA( \
	if (BIT((nr)->transform_rendition->flags, _hoops_PASP)) { \
		if (_hoops_CSRGR->_hoops_CSC._hoops_PRIGC != _hoops_SGIGC || \
			_hoops_CSRGR->_hoops_CSC._hoops_GSCH[0] != (nr)->transform_rendition->_hoops_GSCH[0] || \
			_hoops_CSRGR->_hoops_CSC._hoops_GSCH[1] != (nr)->transform_rendition->_hoops_GSCH[1] || \
			_hoops_CSRGR->_hoops_CSC._hoops_ARIGC != \
				((nr)->transform_rendition->_hoops_CHIH + \
				 (nr)->transform_rendition->_hoops_SHIH + \
				 (_hoops_CSRGR->_hoops_CSC._hoops_HRIGC?1.0f:0) ) ) { \
			_hoops_PGIGC(_hoops_CSRGR, nr, _hoops_SGIGC); \
		} \
	} else { \
		_hoops_RIIGC (_hoops_CSRGR); \
	} \
)

#define ENSURE_ZBUFFER_NOT_DISPLACED(_hoops_CSRGR,nr)            _hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_ARIGC != 0.0f)			    \
		_hoops_PGIGC(_hoops_CSRGR, nr, _hoops_CIAAC);			    \
)


#define FORCE_DEPTH_FUNCTION(_hoops_CSRGR,_hoops_HAGR) _hoops_GHIA(\
	glDepthFunc(_hoops_HAGR); \
	_hoops_CSRGR->_hoops_CSC._hoops_GHAGC = _hoops_HAGR; \
)

#define _hoops_PISRC(_hoops_CSRGR,_hoops_HAGR) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_GHAGC != _hoops_HAGR) \
		FORCE_DEPTH_FUNCTION(_hoops_CSRGR,_hoops_HAGR); \
)


#define _hoops_CIAP(_hoops_CSRGR,_hoops_HAGR) _hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_AAIH = (GLboolean)_hoops_HAGR; \
	glDepthMask ((GLboolean)_hoops_HAGR); \
)

#define ENSURE_DEPTH_MASK(_hoops_CSRGR,_hoops_HAGR) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_AAIH != (GLboolean)(_hoops_HAGR)) \
		_hoops_CIAP(_hoops_CSRGR,_hoops_HAGR); \
)

#define _hoops_CPPRR(_hoops_CSRGR,_hoops_HAGR) _hoops_GHIA(\
	if ((_hoops_HAGR)){\
		if (_hoops_CSRGR->_hoops_GIIGC) \
			glAlphaFunc(GL_GREATER, 0.01f);\
		else \
			glAlphaFunc(GL_GREATER, 0.5f);\
		glEnable(GL_ALPHA_TEST);\
	}\
	else\
		glDisable(GL_ALPHA_TEST);\
	_hoops_CSRGR->_hoops_CSC._hoops_IASP = (_hoops_HAGR); \
)


#define _hoops_IPGP(_hoops_CSRGR, _hoops_HAGR) _hoops_GHIA(\
	if (!_hoops_CSRGR->_hoops_CSC._hoops_IASP != !(_hoops_HAGR||_hoops_CSRGR->_hoops_GIIGC)) \
		_hoops_CPPRR(_hoops_CSRGR,(_hoops_HAGR||_hoops_CSRGR->_hoops_GIIGC)); \
)


#define _hoops_AHPRR(_hoops_CSRGR,_hoops_HAGR) _hoops_GHIA(\
	if (!(_hoops_HAGR)) \
		glColorMask (GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); \
	else \
		glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); \
	_hoops_CSRGR->_hoops_CSC._hoops_RAIH = (_hoops_HAGR); \
)

#define _hoops_RPAP(_hoops_CSRGR, _hoops_HAGR) _hoops_GHIA(\
	if (!_hoops_CSRGR->_hoops_CSC._hoops_RAIH != !(_hoops_HAGR)) \
		_hoops_AHPRR(_hoops_CSRGR,(_hoops_HAGR)); \
)


#define FORCE_COLOR(_hoops_CSRGR, _hoops_HRSPH, _hoops_CRSPH)	_hoops_GHIA(\
	(_hoops_CSRGR)->_hoops_CSC.color = *(_hoops_HRSPH); \
	if (_hoops_CSRGR->_hoops_CSC._hoops_GGAGC == DRAW_MODE_NORMAL) { \
		if (_hoops_CRSPH) { \
			unsigned char _hoops_ASPAC = _hoops_IRASP ((_hoops_HRSPH)->_hoops_HRIR.r, (_hoops_HRSPH)->_hoops_HRIR.g, (_hoops_HRSPH)->_hoops_HRIR.b); \
			if ((_hoops_HRSPH)->_hoops_HRIR.a != 255) \
				glColor4ub (_hoops_ASPAC, _hoops_ASPAC, _hoops_ASPAC , (_hoops_HRSPH)->_hoops_HRIR.a); \
			else \
				glColor3ub (_hoops_ASPAC, _hoops_ASPAC, _hoops_ASPAC); \
		} \
		else { \
			if ((_hoops_HRSPH)->_hoops_HRIR.a != 255) \
				glColor4ub ((_hoops_HRSPH)->_hoops_HRIR.r, (_hoops_HRSPH)->_hoops_HRIR.g, \
							(_hoops_HRSPH)->_hoops_HRIR.b, (_hoops_HRSPH)->_hoops_HRIR.a); \
			else \
				glColor3ub ((_hoops_HRSPH)->_hoops_HRIR.r, (_hoops_HRSPH)->_hoops_HRIR.g, (_hoops_HRSPH)->_hoops_HRIR.b); \
		} \
	} else { \
		OGL_SET_OVERLAY_COLOR (_hoops_CSRGR, &((_hoops_CSRGR)->_hoops_CSC.color)); \
	} \
)

#define FORCE_COLOR_4F(r,g,b,a,_hoops_CRSPH) _hoops_GHIA(\
	if (_hoops_CRSPH) { \
		float _hoops_ASPAC = _hoops_IRASP (r,g,b); \
		glColor4f(_hoops_ASPAC, _hoops_ASPAC, _hoops_ASPAC, a); \
	} \
	else { \
		glColor4f(r,g,b,a); \
	} \
)

#define _hoops_PSPAC(_hoops_HAGR,_hoops_CRSPH) _hoops_GHIA(\
	FORCE_COLOR_4F ((_hoops_HAGR)[0],(_hoops_HAGR)[1],(_hoops_HAGR)[2],1.0f,_hoops_CRSPH); \
)


#define _hoops_PAPRC(r,g,b,a,_hoops_CRSPH) _hoops_GHIA(\
	if (_hoops_CRSPH) { \
		unsigned char _hoops_ASPAC = _hoops_IRASP (r,g,b); \
		glColor4ub(_hoops_ASPAC, _hoops_ASPAC, _hoops_ASPAC, a); \
	} \
	else { \
		glColor4ub(r,g,b,a); \
	} \
)

#define _hoops_APIGC(_hoops_CSRGR, _hoops_HRSPH, nr)     _hoops_GHIA(\
	if ((_hoops_CSRGR)->_hoops_CSC._hoops_SCHGC) { \
		Driver_Color _hoops_HSPAC; \
		_hoops_HSPAC = *(_hoops_HRSPH); \
		_hoops_HSPAC._hoops_HRIR.r ^= (nr)->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.r; \
		_hoops_HSPAC._hoops_HRIR.g ^= (nr)->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.g; \
		_hoops_HSPAC._hoops_HRIR.b ^= (nr)->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.b; \
		if ((_hoops_CSRGR)->_hoops_CSC.color == _hoops_CAHSR::_hoops_SAHSR || \
			(_hoops_CSRGR)->_hoops_CSC.color != _hoops_HSPAC) { \
			FORCE_COLOR(_hoops_CSRGR, &_hoops_HSPAC, false); \
		} \
	} else { \
		if ((_hoops_CSRGR)->_hoops_CSC.color == _hoops_CAHSR::_hoops_SAHSR || \
			(_hoops_CSRGR)->_hoops_CSC.color != *(_hoops_HRSPH)) { \
			FORCE_COLOR(_hoops_CSRGR, _hoops_HRSPH, false); \
		} \
	} \
	(_hoops_CSRGR)->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.red = -1.0f; \
	(_hoops_CSRGR)->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.green = -1.0f; \
	(_hoops_CSRGR)->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.blue = -1.0f; \
	(_hoops_CSRGR)->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.alpha = -1.0f; \
)

#define _hoops_ISPAC(_hoops_CSRGR, _hoops_CSPAC) \
	(_hoops_CSRGR)->_hoops_CSC.line_style = _hoops_CSPAC; \
	if (!BIT(_hoops_CSPAC->flags, LSF_SOLID) && !_hoops_CSRGR->_hoops_CSC._hoops_SCHGC) { \
		glLineStipple ((GLint)(_hoops_CSPAC)->_hoops_CPCAP, (GLushort)(_hoops_CSPAC)->_hoops_SPCAP); \
		glEnable (GL_LINE_STIPPLE); \
		if (XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_LINE_PATTERN_NEEDS_BLENDING)) \
			_hoops_ASGRC (_hoops_CSRGR); \
	} else \
		glDisable (GL_LINE_STIPPLE);

#define ENSURE_LINE_PATTERN(_hoops_CSRGR, _hoops_CSPAC) _hoops_GHIA(\
	if ((_hoops_CSRGR)->_hoops_CSC.line_style != (_hoops_CSPAC)) \
		_hoops_ISPAC(_hoops_CSRGR, _hoops_CSPAC); \
)

#define _hoops_SSPAC(_hoops_CSRGR, width) \
	glLineWidth ((GLfloat)((_hoops_CSRGR)->_hoops_CSC.line_weight = (GLfloat)(width)))

#define ENSURE_LINE_WEIGHT(_hoops_CSRGR, _hoops_GGHAC)	_hoops_GHIA(\
	if ((_hoops_CSRGR)->_hoops_CSC.line_weight != (GLfloat)(_hoops_GGHAC)) { \
		_hoops_SSPAC(_hoops_CSRGR, _hoops_GGHAC); \
	} \
)

#ifndef OGL_MAX_LINE_WEIGHT
#  ifdef _hoops_GGHSH
#    define OGL_MAX_LINE_WEIGHT 3
#  else
#    define OGL_MAX_LINE_WEIGHT 2
#  endif
#endif


#define _hoops_GAPI(_hoops_CSRGR,_hoops_HC,weight)\
		(!BIT((_hoops_HC)->line_style->flags, LSF_SOLID) && \
		 (\
			/* _hoops_PAH'_hoops_RA _hoops_RICGC _hoops_RGR _hoops_PGPRH'_hoops_GRI _hoops_RGHAC */ \
			XBIT_TEST(_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_BAD_PATTERNED_LINES) || \
			/* _hoops_PSP _hoops_CCCI 16-_hoops_IGRH _hoops_SCCI */ \
			!BIT((_hoops_HC)->line_style->flags, LSF_BITS16) || \
			ANYBIT((_hoops_HC)->line_style->flags, LSF_COMPLEX_ANYBITS)\
		) ||\
	     weight > OGL_MAX_LINE_WEIGHT && !BIT ((_hoops_CSRGR)->dc->options._hoops_IRARR, _hoops_PPGAC) ||\
		 weight > (_hoops_CSRGR)->_hoops_AHHGC\
		)

#define _hoops_AGHAC(_hoops_CSRGR, _hoops_PGHAC) \
	glPolygonStipple ((GLubyte const *)((_hoops_CSRGR)->_hoops_SRPH[(_hoops_CSRGR)->_hoops_CSC._hoops_CRIA = _hoops_PGHAC]))

#define ENSURE_FACE_PATTERN(_hoops_CSRGR, _hoops_PGHAC)	_hoops_GHIA(\
	if (_hoops_PGHAC == FP_USER_DEFINED) { \
		glPolygonStipple ((GLubyte const *)((_hoops_CSRGR)->_hoops_RIPRC)); \
	} \
	else if ((_hoops_CSRGR)->_hoops_CSC._hoops_CRIA != (_hoops_PGHAC)) { \
		_hoops_AGHAC(_hoops_CSRGR, _hoops_PGHAC); \
	} \
)

#define _hoops_HGHAC(_hoops_CSRGR)		_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_RGAGC = true; \
	glEnable (GL_COLOR_MATERIAL); \
)

#define _hoops_SRSGC(_hoops_CSRGR)	_hoops_GHIA(\
	if (!_hoops_CSRGR->_hoops_CSC._hoops_RGAGC) { \
		_hoops_HGHAC(_hoops_CSRGR); \
	} \
)

#define _hoops_SCCGC(_hoops_CSRGR)	_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_RGAGC = false; \
	glDisable (GL_COLOR_MATERIAL); \
)

#define ENSURE_MATERIAL_COLOR_OFF(_hoops_CSRGR)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_RGAGC) { \
		_hoops_SCCGC(_hoops_CSRGR); \
	} \
)

#define _hoops_CCCGC(_hoops_CSRGR,mode)	_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_PIAAC = mode; \
	glColorMaterial(mode,GL_AMBIENT_AND_DIFFUSE); \
)

#define _hoops_GASGC(_hoops_CSRGR,mode)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_PIAAC != mode) { \
		_hoops_CCCGC(_hoops_CSRGR,mode); \
	} \
)


#define _hoops_SGCGC(_hoops_CSRGR)              _hoops_GHIA(\
	int _hoops_IGHAC = _hoops_CSRGR->_hoops_SPIGC; \
	while (--_hoops_IGHAC >= 0)  \
		glDisable (GL_CLIP_PLANE0 + _hoops_IGHAC); \
	_hoops_CSRGR->_hoops_GICGC = false; \
	_hoops_CSRGR->_hoops_SPIGC=0; \
)

#define _hoops_HCIGC(_hoops_CSRGR)             _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_GICGC) { \
		_hoops_SGCGC(_hoops_CSRGR); \
	} \
)

#define _hoops_CGHAC(_hoops_CSRGR)               _hoops_GHIA(\
	int _hoops_SGHAC = _hoops_CSRGR->_hoops_SPIGC; \
	while (_hoops_SGHAC-- > 0) \
		glEnable (GL_CLIP_PLANE0 + _hoops_SGHAC); \
	_hoops_CSRGR->_hoops_GICGC = true; \
)

#define _hoops_IGCGC(_hoops_CSRGR)              _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_GICGC == false) { \
		_hoops_CGHAC(_hoops_CSRGR); \
	} \
)


#define _hoops_SPRRC(_hoops_CSRGR)		_hoops_GHIA(\
	_hoops_CSRGR->_hoops_HSAC = true; \
	_hoops_ASGRC(_hoops_CSRGR); \
)

#define _hoops_GRHAC(_hoops_CSRGR)		_hoops_GHIA (\
	if (!_hoops_CSRGR->_hoops_HSAC) \
		_hoops_SPRRC(_hoops_CSRGR); \
)

#define _hoops_ACCGC(_hoops_CSRGR)		_hoops_GHIA(\
	_hoops_CSRGR->_hoops_HSAC = false; \
	_hoops_RRHAC(_hoops_CSRGR); \
)

#define _hoops_ARHAC(_hoops_CSRGR)		_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_HSAC) \
		_hoops_ACCGC(_hoops_CSRGR); \
)

#define ENSURE_TRANSPARENCY(_hoops_CSRGR, set)		_hoops_GHIA(\
	if ((set) && !_hoops_CSRGR->_hoops_PSGRC)	_hoops_GRHAC(_hoops_CSRGR);  \
	else	_hoops_ARHAC(_hoops_CSRGR); \
)

#define _hoops_CIPAC(_hoops_CSRGR) _hoops_GHIA (\
	if (_hoops_CSRGR->_hoops_GIAAC) { \
		_hoops_CSRGR->_hoops_GIAAC = false; \
		glDisable (GL_LINE_SMOOTH); \
	} \
)

#define _hoops_GCPAC(_hoops_CSRGR) _hoops_GHIA (\
	if (!_hoops_CSRGR->_hoops_GIAAC && \
		(!_hoops_CSRGR->_hoops_GIIGC || !XBIT_TEST (_hoops_CSRGR->_hoops_PRARR->_hoops_HHIPP, XBIT_SLOW_PEELED_LINESMOOTH))) { \
		_hoops_CSRGR->_hoops_GIAAC = true; \
		glEnable (GL_LINE_SMOOTH); \
	} \
)

#define ENSURE_LINE_SMOOTH(_hoops_CSRGR, set) _hoops_GHIA (\
	if (set) \
		_hoops_GCPAC(_hoops_CSRGR); \
	else \
		_hoops_CIPAC(_hoops_CSRGR); \
)


#define ENSURE_FOG_OFF(_hoops_CSRGR, nr) _hoops_GHIA (\
	if (_hoops_CSRGR->_hoops_GAGRR) { \
	_hoops_CSRGR->_hoops_GAGRR = false; \
	glDisable (GL_FOG); \
	} \
)

#define ENSURE_FOG_ON(_hoops_CSRGR, nr) _hoops_GHIA (\
    _hoops_CSRGR->_hoops_GAGRR = true; \
    glEnable (GL_FOG); \
    if (nr->_hoops_CPP->_hoops_CPA != _hoops_CSRGR->_hoops_SARRR) { \
        float _hoops_PRHAC[4]; \
        _hoops_CSRGR->_hoops_SARRR = nr->_hoops_CPP->_hoops_CPA; \
        glFogi (GL_FOG_MODE, GL_LINEAR); \
        _hoops_PRHAC[0] = nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.r * (1.0f / 255.0f); \
        _hoops_PRHAC[1] = nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.g * (1.0f / 255.0f); \
        _hoops_PRHAC[2] = nr->_hoops_SAIR->_hoops_GPIR._hoops_HRIR.b * (1.0f / 255.0f); \
        _hoops_PRHAC[3] = _hoops_GPGCR; \
        glFogfv (GL_FOG_COLOR, _hoops_PRHAC); \
        /* _hoops_AA _hoops_HAR _hoops_AA _hoops_AIR _hoops_PAIR _hoops_IISRR */ \
        glHint (GL_FOG_HINT, GL_DONT_CARE);	\
        if (nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH) { \
            glFogf (GL_FOG_START, nr->_hoops_CPP->_hoops_CRIR.hither); \
            glFogf (GL_FOG_END, nr->_hoops_CPP->_hoops_CRIR.yon); \
        }  \
        else {  \
            glFogf (GL_FOG_START, nr->_hoops_CPP->_hoops_CRIR.hither - _hoops_IHCR->_hoops_SPH->_hoops_SRIR); \
            glFogf (GL_FOG_END, nr->_hoops_CPP->_hoops_CRIR.yon - _hoops_IHCR->_hoops_SPH->_hoops_SRIR); \
        } \
    } \
)


#ifdef AGL_DRIVER

#define FORCE_DRAW_MODE(_hoops_CSRGR, mode)		_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_GGAGC = mode; \
	if (mode == DRAW_MODE_NORMAL) { \
		aglSetCurrentContext(_hoops_CSRGR->curr_AGLContext); \
	} else { \
		/*_hoops_SIGP: _hoops_HRHAC _hoops_IRHAC _hoops_CRHAC _hoops_RRAGC*/ \
	} \
)

#endif

#ifdef COCOA_OGL_DRIVER

#define FORCE_DRAW_MODE(_hoops_CSRGR, mode)		_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_GGAGC = mode; \
	if (mode == DRAW_MODE_NORMAL) { \
		/*_hoops_SRHAC(_hoops_HGPGA->_hoops_GAHAC);*/ \
	} else { \
		/*_hoops_SIGP: _hoops_HRHAC _hoops_IRHAC _hoops_CRHAC _hoops_RRAGC*/ \
	} \
)

#endif

#ifdef GLX_DRIVER

#define FORCE_DRAW_MODE(_hoops_CSRGR, mode)		_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_GGAGC = mode; \
	if (mode == DRAW_MODE_NORMAL) { \
	glXMakeCurrent (_hoops_CSRGR->display, _hoops_CSRGR->window, _hoops_CSRGR->context); \
	} else { \
	glXMakeCurrent (_hoops_CSRGR->display, _hoops_CSRGR->overlay.window, _hoops_CSRGR->overlay.context); \
	} \
)

#endif

#ifdef WGL_DRIVER

#define FORCE_DRAW_MODE(_hoops_CSRGR, mode)		_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_GGAGC = mode;\
	if (mode == DRAW_MODE_NORMAL) {\
		if (_hoops_CSRGR->_hoops_APSRC)\
		wglMakeCurrent (_hoops_CSRGR->_hoops_HIISI, _hoops_CSRGR->hGLRC);\
		else\
		wglMakeCurrent (_hoops_CSRGR->hDC, _hoops_CSRGR->hGLRC);\
	} else { \
		/*_hoops_SIGP: _hoops_HRHAC _hoops_IRHAC _hoops_CRHAC _hoops_RRAGC*/ \
		wglMakeCurrent (_hoops_CSRGR->hDC, _hoops_CSRGR->hGLRC);\
	} \
)

#endif

#define ENSURE_DRAW_MODE(_hoops_CSRGR, mode)		_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_GGAGC != mode) \
	FORCE_DRAW_MODE(_hoops_CSRGR, mode); \
)


#define _hoops_RCPRR(_hoops_CSRGR)  _hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_GSAAC = _hoops_RSARR; \
	_hoops_CSRGR->_hoops_CSC._hoops_RSAAC = _hoops_RSARR; \
	_hoops_CSRGR->_hoops_CSC._hoops_ASAAC = _hoops_RSARR; \
	_hoops_CSRGR->_hoops_CSC._hoops_PSAAC = _hoops_RSARR; \
)

#define FORCE_SCISSOR_OFF(_hoops_CSRGR)	_hoops_GHIA(\
	_hoops_RCPRR(_hoops_CSRGR); \
	_hoops_CSRGR->_hoops_CSC._hoops_SCAAC = _hoops_ICAAC; \
	glDisable (GL_SCISSOR_TEST); \
)

#define ENSURE_SCISSOR_OFF(_hoops_CSRGR)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_SCAAC != _hoops_ICAAC) \
	FORCE_SCISSOR_OFF (_hoops_CSRGR); \
)

#define _hoops_RAHAC(_hoops_CSRGR)	_hoops_GHIA(\
	_hoops_RCPRR(_hoops_CSRGR); \
	_hoops_CSRGR->_hoops_CSC._hoops_SCAAC = _hoops_CCAAC; \
	glEnable (GL_SCISSOR_TEST); \
)

#define _hoops_GGIGC(_hoops_CSRGR)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_SCAAC != _hoops_CCAAC) \
	_hoops_RAHAC (_hoops_CSRGR); \
)

#define ENSURE_SCISSOR_SET(_hoops_CSRGR, x, y, w, h)  _hoops_GHIA(\
	if ((x != _hoops_CSRGR->_hoops_CSC._hoops_GSAAC) || (y != _hoops_CSRGR->_hoops_CSC._hoops_RSAAC) || \
	(w != _hoops_CSRGR->_hoops_CSC._hoops_ASAAC) || (h != _hoops_CSRGR->_hoops_CSC._hoops_PSAAC)) { \
	glScissor ((_hoops_CSRGR->_hoops_CSC._hoops_GSAAC = x), (_hoops_CSRGR->_hoops_CSC._hoops_RSAAC = y), \
		   (_hoops_CSRGR->_hoops_CSC._hoops_ASAAC = w), (_hoops_CSRGR->_hoops_CSC._hoops_PSAAC = h)); \
	} \
)

#define _hoops_AAHAC(_hoops_CSRGR)  _hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_GGPAC = 10000000.0f; \
	_hoops_CSRGR->_hoops_CSC._hoops_RGPAC = 10000000.0f; \
)

#define _hoops_PAHAC(_hoops_CSRGR, x, y)  _hoops_GHIA(\
	if (((x) != _hoops_CSRGR->_hoops_CSC._hoops_GGPAC) || ((y) != _hoops_CSRGR->_hoops_CSC._hoops_RGPAC)) { \
	glPixelZoom ((_hoops_CSRGR->_hoops_CSC._hoops_GGPAC = (x)), (_hoops_CSRGR->_hoops_CSC._hoops_RGPAC = (y))); \
	} \
)

#define INVALIDATE_PIXEL_UNPACK_ALIGNMENT(_hoops_CSRGR)  _hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_AGPAC = _hoops_RSARR; \
)

#define ENSURE_PIXEL_UNPACK_ALIGNMENT(_hoops_CSRGR, a)  _hoops_GHIA(\
	if (((a) != _hoops_CSRGR->_hoops_CSC._hoops_AGPAC)) { \
		_hoops_CSRGR->_hoops_CSC._hoops_AGPAC = (a); \
	glPixelStorei (GL_PACK_ALIGNMENT, (a)); \
	glPixelStorei (GL_UNPACK_ALIGNMENT, (a)); \
	} \
)



#define _hoops_HAHAC(_hoops_CSRGR)	_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_IRPAC = false; \
	glDisable (GL_STENCIL_TEST); \
)

#define _hoops_RSIGC(_hoops_CSRGR)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_IRPAC) \
		_hoops_HAHAC (_hoops_CSRGR); \
)

#define _hoops_IAHAC(_hoops_CSRGR)	_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_IRPAC = true; \
	glEnable (GL_STENCIL_TEST); \
)

#define ENSURE_STENCIL_ON(_hoops_CSRGR)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_IRPAC != _hoops_CCAAC) \
		_hoops_IAHAC (_hoops_CSRGR); \
)





#define _hoops_CAAGC(_hoops_CSRGR)  _hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_HSAAC = _hoops_RSARR; \
	_hoops_CSRGR->_hoops_CSC._hoops_ISAAC = _hoops_RSARR; \
	_hoops_CSRGR->_hoops_CSC._hoops_CSAAC = _hoops_RSARR; \
	_hoops_CSRGR->_hoops_CSC._hoops_SSAAC = _hoops_RSARR; \
)

#define ENSURE_VIEWPORT_SET(_hoops_CSRGR, x, y, w, h)  _hoops_GHIA(\
	if ((x != _hoops_CSRGR->_hoops_CSC._hoops_HSAAC) || (y != _hoops_CSRGR->_hoops_CSC._hoops_ISAAC) || \
	(w != _hoops_CSRGR->_hoops_CSC._hoops_CSAAC) || (h != _hoops_CSRGR->_hoops_CSC._hoops_SSAAC)) { \
	glViewport((_hoops_CSRGR->_hoops_CSC._hoops_HSAAC = x), (_hoops_CSRGR->_hoops_CSC._hoops_ISAAC = y), \
		   (_hoops_CSRGR->_hoops_CSC._hoops_CSAAC = w), (_hoops_CSRGR->_hoops_CSC._hoops_SSAAC = h)); \
	} \
)


#define _hoops_CICGC(_hoops_CSRGR)	_hoops_GHIA( \
	_hoops_CSRGR->_hoops_CSC._hoops_AAIAR = false; \
	glDisable (GL_NORMALIZE); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#define _hoops_CPCGC(_hoops_CSRGR)	_hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_AAIAR) \
		_hoops_CICGC (_hoops_CSRGR); \
)

#define _hoops_CAHAC(_hoops_CSRGR)	_hoops_GHIA( \
	_hoops_CSRGR->_hoops_CSC._hoops_AAIAR = true; \
	glEnable (GL_NORMALIZE); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#define ENSURE_NORMALIZE_ON(_hoops_CSRGR)	_hoops_GHIA( \
	if (!_hoops_CSRGR->_hoops_CSC._hoops_AAIAR) \
		_hoops_CAHAC (_hoops_CSRGR); \
)



#define _hoops_SAHAC(_hoops_CSRGR) _hoops_GHIA( \
	_hoops_CSRGR->_hoops_CSC._hoops_HGPAC = true; \
	glEnableClientState(GL_COLOR_ARRAY); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#define FORCE_COLOR_ARRAY_OFF(_hoops_CSRGR) _hoops_GHIA( \
	_hoops_CSRGR->_hoops_CSC._hoops_HGPAC = false; \
	glDisableClientState(GL_COLOR_ARRAY); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#define ENSURE_COLOR_ARRAY_ON(_hoops_CSRGR) _hoops_GHIA( \
	if (!_hoops_CSRGR->_hoops_CSC._hoops_HGPAC) \
		_hoops_SAHAC(_hoops_CSRGR); \
)

#define _hoops_RHPRC(_hoops_CSRGR) _hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_HGPAC) \
		FORCE_COLOR_ARRAY_OFF(_hoops_CSRGR); \
)


#define _hoops_GPHAC(_hoops_CSRGR) _hoops_GHIA( \
	_hoops_CSRGR->_hoops_CSC._hoops_IGPAC = true; \
	glEnableClientState(GL_VERTEX_ARRAY); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#define FORCE_VERTEX_ARRAY_OFF(_hoops_CSRGR) _hoops_GHIA( \
	_hoops_CSRGR->_hoops_CSC._hoops_IGPAC = false; \
	glDisableClientState(GL_VERTEX_ARRAY); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#define _hoops_CPPRC(_hoops_CSRGR) _hoops_GHIA( \
	if (!_hoops_CSRGR->_hoops_CSC._hoops_IGPAC) {\
		_hoops_GPHAC(_hoops_CSRGR); \
	} \
)

#define _hoops_AHPRC(_hoops_CSRGR) _hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_IGPAC) { \
		FORCE_VERTEX_ARRAY_OFF(_hoops_CSRGR); \
	} \
)


#define _hoops_RPHAC(_hoops_CSRGR) _hoops_GHIA( \
	_hoops_CSRGR->_hoops_CSC._hoops_CGPAC = true; \
	glEnableClientState(GL_NORMAL_ARRAY); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#define FORCE_NORMAL_ARRAY_OFF(_hoops_CSRGR) _hoops_GHIA( \
	_hoops_CSRGR->_hoops_CSC._hoops_CGPAC = false; \
	glDisableClientState(GL_NORMAL_ARRAY); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#define _hoops_HGCRC(_hoops_CSRGR) _hoops_GHIA( \
	if (!_hoops_CSRGR->_hoops_CSC._hoops_CGPAC) \
		_hoops_RPHAC(_hoops_CSRGR); \
)

#define _hoops_IGCRC(_hoops_CSRGR) _hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_CGPAC) \
		FORCE_NORMAL_ARRAY_OFF(_hoops_CSRGR); \
)


#define _hoops_APHAC(_hoops_CSRGR) _hoops_GHIA( \
	_hoops_CSRGR->_hoops_CSC._hoops_SGPAC = true; \
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#define FORCE_TEXTURE_COORD_ARRAY_OFF(_hoops_CSRGR) _hoops_GHIA( \
	_hoops_CSRGR->_hoops_CSC._hoops_SGPAC = false; \
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#if 0
#define _hoops_PPHAC(_hoops_CSRGR) _hoops_GHIA( \
	if (!_hoops_CSRGR->_hoops_CSC._hoops_SGPAC) \
		_hoops_APHAC(_hoops_CSRGR); \
)

#define _hoops_HPHAC(_hoops_CSRGR) _hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_SGPAC) \
		FORCE_TEXTURE_COORD_ARRAY_OFF(_hoops_CSRGR); \
)
#endif

#define _hoops_IPRRC(_hoops_CSRGR,_hoops_AHCGR) _hoops_GHIA( \
	_hoops_CSRGR->_hoops_RGHGC (GL_TEXTURE0 + _hoops_AHCGR); \
	_hoops_CSRGR->_hoops_CSC._hoops_GRGAC = _hoops_AHCGR; \
)

#define _hoops_IHRRC(_hoops_CSRGR,_hoops_AHCGR) _hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_GRGAC != _hoops_AHCGR) { \
		_hoops_IPRRC(_hoops_CSRGR,_hoops_AHCGR); \
	} \
)

#define _hoops_HPRRC(_hoops_CSRGR,_hoops_RHIA,mode) _hoops_GHIA(\
 _hoops_CSRGR->_hoops_CSC._hoops_SGPAC[_hoops_RHIA] = mode; \
 _hoops_IHRRC (_hoops_CSRGR,_hoops_RHIA); \
 if (mode) \
  glEnableClientState(GL_TEXTURE_COORD_ARRAY); \
 else \
  glDisableClientState(GL_TEXTURE_COORD_ARRAY); \
)


#define ENSURE_TEXTURE_COORD_ARRAY(_hoops_CSRGR,_hoops_RHIA,mode) _hoops_GHIA(\
 if (mode != _hoops_CSRGR->_hoops_CSC._hoops_SGPAC[_hoops_RHIA]) \
  _hoops_HPRRC(_hoops_CSRGR,_hoops_RHIA,mode); \
 else \
  _hoops_IHRRC (_hoops_CSRGR, _hoops_RHIA); /* _hoops_IS _hoops_SRCH _hoops_CPCIP _hoops_RGSR */ \
)




#define _hoops_CRPAH(_hoops_CSRGR, target, mode, _hoops_GRRA)	_hoops_GHIA( \
	_hoops_PPRGC(_hoops_CSRGR, _hoops_GRRA); \
	_hoops_CSRGR->_hoops_CSC._hoops_RAGRR[_hoops_GRRA] = mode; \
	glTexParameteri (target, GL_TEXTURE_WRAP_S, mode); \
)

#define ENSURE_TEXTURE_WRAP_S(_hoops_CSRGR, target, mode, _hoops_GRRA)	_hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_RAGRR[_hoops_GRRA] != mode) \
		_hoops_CRPAH(_hoops_CSRGR, target, mode, _hoops_GRRA); \
)

#define _hoops_SRPAH(_hoops_CSRGR, target, mode, _hoops_GRRA)	_hoops_GHIA( \
	_hoops_PPRGC(_hoops_CSRGR, _hoops_GRRA); \
	_hoops_CSRGR->_hoops_CSC._hoops_AAGRR[_hoops_GRRA] = mode; \
	glTexParameteri (target, GL_TEXTURE_WRAP_T, mode); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#define _hoops_SAIRH(_hoops_CSRGR, target, mode, _hoops_GRRA)	_hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_AAGRR[_hoops_GRRA] != mode) \
		_hoops_SRPAH(_hoops_CSRGR, target, mode, _hoops_GRRA); \
)

#define _hoops_IPHAC(_hoops_CSRGR, mode, _hoops_GRRA)	_hoops_GHIA( \
	_hoops_PPRGC(_hoops_CSRGR, _hoops_GRRA); \
	_hoops_CSRGR->_hoops_CSC._hoops_PAAGC[_hoops_GRRA] = mode; \
	glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode); \
	ASSERT (!_hoops_CSRGR->_hoops_CSC._hoops_IPAGC); \
)

#define ENSURE_TEXTURE_ENV_MODE(_hoops_CSRGR, mode, _hoops_GRRA)	_hoops_GHIA( \
	if (_hoops_CSRGR->_hoops_CSC._hoops_PAAGC[_hoops_GRRA] != mode) \
	_hoops_IPHAC(_hoops_CSRGR, mode, _hoops_GRRA); \
)

#define _hoops_CPHAC(_hoops_CSRGR, _hoops_GRRA)	_hoops_GHIA(\
	_hoops_PPRGC(_hoops_CSRGR, _hoops_GRRA); \
	_hoops_CSRGR->_hoops_CSC._hoops_IAAGC[_hoops_GRRA] = 1; \
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); \
)

#define ENSURE_TEXTURE_PERSPECTIVE_CORRECTION_ON(_hoops_CSRGR, _hoops_GRRA)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_IAAGC[_hoops_GRRA] != 1) \
		_hoops_CPHAC(_hoops_CSRGR, _hoops_GRRA); \
)

#define _hoops_SPHAC(_hoops_CSRGR, _hoops_GRRA)	_hoops_GHIA(\
	_hoops_PPRGC(_hoops_CSRGR, _hoops_GRRA); \
	_hoops_CSRGR->_hoops_CSC._hoops_IAAGC[_hoops_GRRA] = 0; \
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST); \
)

#define _hoops_GHHAC(_hoops_CSRGR, _hoops_GRRA)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_IAAGC[_hoops_GRRA] != 0) \
		_hoops_SPHAC(_hoops_CSRGR, _hoops_GRRA); \
)

#define _hoops_SGGAC(_hoops_CSRGR, _hoops_GRRA)	_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_ARPAC[_hoops_GRRA] = false; \
	glDisable (GL_TEXTURE_GEN_S); \
	glDisable (GL_TEXTURE_GEN_T); \
)

#define _hoops_SRGRC(_hoops_CSRGR, _hoops_GRRA)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_ARPAC[_hoops_GRRA]) \
		_hoops_SGGAC (_hoops_CSRGR, _hoops_GRRA); \
)

#define _hoops_RHHAC(_hoops_CSRGR, _hoops_GRRA)	_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_ARPAC[_hoops_GRRA] = true; \
	glEnable (GL_TEXTURE_GEN_S); \
	glEnable (GL_TEXTURE_GEN_T); \
)

#define _hoops_ISGRC(_hoops_CSRGR, _hoops_GRRA)	_hoops_GHIA(\
	if (!_hoops_CSRGR->_hoops_CSC._hoops_ARPAC[_hoops_GRRA]) \
		_hoops_RHHAC (_hoops_CSRGR, _hoops_GRRA); \
)

#define _hoops_AHHAC(_hoops_CSRGR, mode, _hoops_GRRA)	_hoops_GHIA(\
	_hoops_PPRGC(_hoops_CSRGR, _hoops_GRRA); \
	_hoops_CSRGR->_hoops_CSC._hoops_HAAGC[_hoops_GRRA] = mode; \
	glTexGenf (GL_S, GL_TEXTURE_GEN_MODE, mode); \
	glTexGenf (GL_T, GL_TEXTURE_GEN_MODE, mode); \
)

#define ENSURE_TEXTURE_GEN_MODE(_hoops_CSRGR, mode, _hoops_GRRA)  _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_HAAGC[_hoops_GRRA] != mode) \
		_hoops_AHHAC(_hoops_CSRGR, mode, _hoops_GRRA); \
)




#define _hoops_APSS(_hoops_CSRGR, _hoops_GRRA) _hoops_GHIA(\
	(_hoops_CSRGR)->_hoops_CSC._hoops_RAGRR[_hoops_GRRA] = _hoops_RSARR; \
	(_hoops_CSRGR)->_hoops_CSC._hoops_AAGRR[_hoops_GRRA] = _hoops_RSARR; \
)


#define _hoops_ICGRC(_hoops_CSRGR) _hoops_GHIA(\
	(_hoops_CSRGR)->_hoops_CSC.color = _hoops_CAHSR::_hoops_SAHSR; \
	(_hoops_CSRGR)->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.red = -1.0f; \
	(_hoops_CSRGR)->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.green = -1.0f; \
	(_hoops_CSRGR)->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.blue = -1.0f; \
	(_hoops_CSRGR)->_hoops_CSC._hoops_ISHIR._hoops_PGAGC.alpha = -1.0f; \
)


#define _hoops_PHHAC(_hoops_CSRGR, mode) _hoops_GHIA(\
	(_hoops_CSRGR)->_hoops_CSC._hoops_CGAGC = mode;\
	glLightModeli (GL_LIGHT_MODEL_LOCAL_VIEWER, mode); \
)

#define ENSURE_LOCAL_VIEWER(_hoops_CSRGR, mode) _hoops_GHIA(\
	if ((_hoops_CSRGR)->_hoops_CSC._hoops_CGAGC != mode) { \
	_hoops_PHHAC(_hoops_CSRGR, mode); \
	} \
)


#define FORCE_BLEND_FUNC(_hoops_CSRGR, _hoops_HHHAC, _hoops_IHHAC) _hoops_GHIA(\
	(_hoops_CSRGR)->_hoops_CSC._hoops_HAPAC = _hoops_HHHAC; \
	(_hoops_CSRGR)->_hoops_CSC._hoops_IAPAC = _hoops_IHHAC; \
	glBlendFunc(_hoops_HHHAC, _hoops_IHHAC); \
)

#define ENSURE_BLEND_FUNC(_hoops_CSRGR, _hoops_HHHAC, _hoops_IHHAC) _hoops_GHIA(\
	if ((_hoops_CSRGR)->_hoops_CSC._hoops_HAPAC != _hoops_HHHAC || \
	(_hoops_CSRGR)->_hoops_CSC._hoops_IAPAC != _hoops_IHHAC) { \
	FORCE_BLEND_FUNC(_hoops_CSRGR, _hoops_HHHAC, _hoops_IHHAC); \
	} \
)

#define _hoops_SICGC(_hoops_CSRGR)	_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_CAPAC = false; \
	glDisable (GL_BLEND); \
)

#define _hoops_RRHAC(_hoops_CSRGR)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_CAPAC) \
		_hoops_SICGC (_hoops_CSRGR); \
)

#define _hoops_CHHAC(_hoops_CSRGR)	_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_CAPAC = true; \
	glEnable (GL_BLEND); \
)

#define _hoops_ASGRC(_hoops_CSRGR)	_hoops_GHIA(\
	if (!_hoops_CSRGR->_hoops_CSC._hoops_CAPAC) \
		_hoops_CHHAC (_hoops_CSRGR); \
)


#define _hoops_GIAC(_hoops_CSRGR, nr) _hoops_GHIA(\
	if ((_hoops_CSRGR)->_hoops_HCAC != _hoops_RARRR ((nr)->transform_rendition->_hoops_CPA)) { \
		OGL_SET_DC_XFORM ((_hoops_CSRGR), (nr)); \
	} \
)


/* _hoops_PAAP _hoops_RH _hoops_SHHAC _hoops_AIHGR, _hoops_PPR _hoops_IRHH _hoops_RCRR _hoops_RSSP _hoops_SHSGH 
 * _hoops_GGR _hoops_CAPRH.  (_hoops_SHHAC _hoops_GIASP _hoops_IGH _hoops_CPAP _hoops_SSCP _hoops_RPII _hoops_PPSI 
 * _hoops_RHIR _hoops_IRS _hoops_CPAP _hoops_CGRPR _hoops_CCA _hoops_IRS _hoops_HHHR _hoops_CSRA _hoops_RSGA */
#define _hoops_SAHRC(_hoops_CSRGR, _hoops_IHCR, _hoops_HAGR) _hoops_GHIA(\
	if (_hoops_HAGR != _hoops_CSRGR->_hoops_GGCGC) { \
		_hoops_CSRGR->_hoops_GGCGC = _hoops_HAGR; \
		OGL_SET_HANDEDNESS (_hoops_CSRGR, _hoops_IHCR, 0); \
	} \
	else \
		_hoops_CSRGR->_hoops_GGCGC = _hoops_HAGR; \
)


#define _hoops_GGGH(_hoops_CSRGR, nr) _hoops_GHIA(\
	if ((_hoops_CSRGR)->_hoops_HCAC != _hoops_PARRR ((nr)->transform_rendition->_hoops_CPA)) { \
		OGL_SET_3D_XFORM ((_hoops_CSRGR), (nr)); \
	} \
	else { \
		bool _hoops_HAHRC = false; \
		if (nr->_hoops_SRA->_hoops_SPA && \
			nr->_hoops_SRA->_hoops_SPA->modelling_matrix) \
			_hoops_HAHRC = BIT (nr->_hoops_SRA->_hoops_SPA->modelling_matrix->matrix._hoops_RAGR, _hoops_CASA); \
		_hoops_SAHRC (_hoops_CSRGR, nr->transform_rendition, _hoops_HAHRC); \
	} \
)

#define _hoops_HRIRC(_hoops_CSRGR, nr) _hoops_GHIA(\
	if (!(_hoops_CSRGR)->_hoops_PPAGC) { \
		if (nr->transform_rendition->matrix->data._hoops_APRA != null) { \
			_hoops_CSRGR->_hoops_SRIRC[0] = nr->transform_rendition->matrix->data._hoops_APRA->data.elements[2][0]; \
			_hoops_CSRGR->_hoops_SRIRC[1] = nr->transform_rendition->matrix->data._hoops_APRA->data.elements[2][1]; \
			_hoops_CSRGR->_hoops_SRIRC[2] = nr->transform_rendition->matrix->data._hoops_APRA->data.elements[2][2]; \
			_hoops_CSRGR->_hoops_SRIRC[3] = nr->transform_rendition->matrix->data._hoops_APRA->data.elements[2][3]; \
		} \
		else { \
			HI_Adjoint_44_Z (&nr->transform_rendition->matrix->data.elements[0][0], \
							 _hoops_CSRGR->_hoops_SRIRC); \
		} \
		(_hoops_CSRGR)->_hoops_PPAGC = true; \
	} \
)

#define _hoops_GIHAC(_hoops_CSRGR, _hoops_SHGCR)	_hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_SPAGC = _hoops_SHGCR; \
	glListBase (_hoops_SHGCR); \
)

#define ENSURE_LIST_BASE(_hoops_CSRGR, _hoops_SHGCR)	_hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_SPAGC != _hoops_SHGCR) \
	_hoops_GIHAC(_hoops_CSRGR, _hoops_SHGCR); \
)

#define _hoops_RIHAC(_hoops_CSRGR) _hoops_GHIA(\
	_hoops_CSRGR->_hoops_CSC._hoops_SPAGC = _hoops_RSARR; \
)

#define ENSURE_CLIP_VOLUME_HINT(_hoops_CSRGR, _hoops_AIHAC) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_RAPGC && _hoops_CSRGR->_hoops_CSC._hoops_CPAGC != _hoops_AIHAC) { \
		glHint(GL_CLIP_VOLUME_CLIPPING_HINT_EXT,(_hoops_CSRGR->_hoops_CSC._hoops_CPAGC=_hoops_AIHAC)); \
	} \
)


#define _hoops_GPPRC(_hoops_CSRGR,size) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_AAPAC != size) { \
		glPointSize(size); \
		_hoops_CSRGR->_hoops_CSC._hoops_AAPAC = size; \
	} \
)

#define _hoops_AAPRC(_hoops_CSRGR,_hoops_PIHAC) _hoops_GHIA(\
	if (_hoops_CSRGR->_hoops_CSC._hoops_RAPAC != _hoops_PIHAC) { \
		if (_hoops_PIHAC) \
			glEnable (GL_POINT_SMOOTH); \
		else \
			glDisable (GL_POINT_SMOOTH); \
		_hoops_CSRGR->_hoops_CSC._hoops_RAPAC = _hoops_PIHAC; \
	} \
)





/*
 * _hoops_PGAA
 */
#define _hoops_IPCRC(_hoops_RIHRC, color) _hoops_GHIA (\
	if (_hoops_RIHRC) {\
		float const *_hoops_HIHAC = (float *)color;\
		float _hoops_ARCAR[3];\
		_hoops_ARCAR[0] = _hoops_ARCAR[1] = _hoops_ARCAR[2] = _hoops_IRASP (_hoops_HIHAC[0], _hoops_HIHAC[1], _hoops_HIHAC[2]);\
		glColor3fv ((float const *)(_hoops_ARCAR));\
	}\
	else {\
		glColor3fv ((float const *)(color));\
	}\
)


#define _hoops_PRIRC		1
#define _hoops_IIHAC	2

#define _hoops_RRCRC(_hoops_ASSRR, normal, point, _hoops_APRA) _hoops_GHIA (\
		if ((_hoops_ASSRR) == _hoops_PRIRC) {						\
			if ((normal).x*(_hoops_APRA)[0] +					\
				(normal).y*(_hoops_APRA)[1] +					\
				(normal).z*(_hoops_APRA)[2] +					\
				(_hoops_APRA)[3] * (-((point).x * (normal).x +	\
				  (point).y * (normal).y +					\
				  (point).z * (normal).z)) > 0.0f) {		\
				glNormal3f (-(normal).x, -(normal).y, -(normal).z);	\
			}												\
			else											\
				glNormal3fv ((GLfloat const *)&(normal));	\
		}													\
		else if (_hoops_ASSRR)										\
			glNormal3f (-(normal).x, -(normal).y, -(normal).z);	\
		else												\
			glNormal3fv ((GLfloat const *)&(normal));		\
)

#define _hoops_CIHAC(_hoops_ASSRR, pln, _hoops_APRA)	_hoops_GHIA (	\
		if ((_hoops_ASSRR) == _hoops_PRIRC) {						\
			if ((pln).a*(_hoops_APRA)[0] +						\
				(pln).b*(_hoops_APRA)[1] +						\
				(pln).c*(_hoops_APRA)[2] +						\
				(pln).d*(_hoops_APRA)[3] > 0.0f) 				\
				glNormal3f (-(pln).a, -(pln).b, -(pln).c);	\
			else											\
				glNormal3fv ((GLfloat const *)&(pln));		\
		}													\
		else if (_hoops_ASSRR)										\
			glNormal3f (-(pln).a, -(pln).b, -(pln).c);		\
		else												\
			glNormal3fv ((GLfloat const *)&(pln));			\
)

#define _hoops_SIHAC(_hoops_ASSRR, normal, point, _hoops_APRA, target) _hoops_GHIA (\
		if ((_hoops_ASSRR) == _hoops_PRIRC) {						\
			if ((normal).x*(_hoops_APRA)[0] +					\
				(normal).y*(_hoops_APRA)[1] +					\
				(normal).z*(_hoops_APRA)[2] +					\
				(_hoops_APRA)[3] * (-((point).x * (normal).x +	\
				  (point).y * (normal).y +					\
				  (point).z * (normal).z)) > 0.0f) {		\
				target.x = -(normal).x;						\
				target.y = -(normal).y;						\
				target.z = -(normal).z;						\
			}												\
			else {											\
				target.x = (normal).x;						\
				target.y = (normal).y;						\
				target.z = (normal).z;						\
			}												\
		}													\
		else if (_hoops_ASSRR)		{								\
			target.x = -(normal).x;							\
			target.y = -(normal).y;							\
			target.z = -(normal).z;							\
		}													\
		else {												\
			target.x = (normal).x;							\
			target.y = (normal).y;							\
			target.z = (normal).z;							\
		}													\
)

#define _hoops_GCHAC(_hoops_ASSRR, pln, _hoops_APRA, target) _hoops_GHIA (\
		if ((_hoops_ASSRR) == _hoops_PRIRC) { \
			if ((pln).a*(_hoops_APRA)[0] +					\
				(pln).b*(_hoops_APRA)[1] +					\
				(pln).c*(_hoops_APRA)[2] +					\
				(pln).d*(_hoops_APRA)[3] > 0.0f) {			\
				target.x = -(pln).a;					\
				target.y = -(pln).b;					\
				target.z = -(pln).c;					\
			}											\
			else {										\
				target.x = (pln).a;						\
				target.y = (pln).b;						\
				target.z = (pln).c;						\
			}											\
		}												\
		else if (_hoops_ASSRR) {								\
			target.x = -(pln).a;						\
			target.y = -(pln).b;						\
			target.z = -(pln).c;						\
		}												\
		else {											\
			target.x = (pln).a;							\
			target.y = (pln).b;							\
			target.z = (pln).c;							\
		}												\
)

#ifdef OSX_SYSTEM
#define _hoops_RCHAC 0
#else
#define _hoops_RCHAC 20
#endif


#  define OGL_ALLOC_TEXTURE(id) do { id=0 ; glGenTextures (1, &id); }while (0)
#  define OGL_FREE_TEXTURE(id) do { glDeleteTextures (1, &id); id=0;}while (0)

/* _hoops_GPP _hoops_ACHAC _hoops_PAR _hoops_PCHAC _hoops_RHPP, _hoops_PCHAC _hoops_PIH _hoops_HRGR _hoops_GPP _hoops_CSPH->_hoops_PIH */
#define OGLD(dc) ((OGLData alter *)((dc)->_hoops_RIHGR))
#define OGLNRD(nr) (OGLD((nr)->_hoops_SRA))

#ifdef GLX_DRIVER
#  define X11D(dc) ((X11Data alter *)((dc)->data))
#  define X11NRD(nr) (X11D(nr->_hoops_SRA))
#endif



/* _hoops_HCHAC _hoops_ICHAC _hoops_IH _hoops_ARAS-_hoops_GHIR _hoops_GHRS _hoops_IIGR _hoops_ICHRH _hoops_SGS _hoops_SRS _hoops_CCHAC _hoops_HHPA
 * _hoops_RAS _hoops_SCHAC 10.2, _hoops_PPR _hoops_CAPHR _hoops_IIGR _hoops_CRRHA _hoops_IH _hoops_GSHAC _hoops_GPP _hoops_RPAC _hoops_RSHAC _hoops_IRSP */
#ifdef AGL_DRIVER
#  if (_hoops_IARAC < _hoops_CARAC)
  typedef CGContextRef (*_hoops_ASHAC) (void *glContext, CGSize size, CGColorSpaceRef _hoops_PSHAC);
  typedef GLboolean (*aglSetPBufferProc) (AGLContext, AGLPbuffer, GLint, GLint, GLint);
  typedef GLboolean (*aglCreatePBufferProc) (GLint, GLint, GLenum, GLenum, long, AGLPbuffer *);
  typedef GLboolean (*aglDestroyPBufferProc) (AGLPbuffer);
  extern _hoops_ASHAC CGGLContextCreate;
  extern aglSetPBufferProc aglSetPBuffer;
  extern aglCreatePBufferProc aglCreatePBuffer;
  extern aglDestroyPBufferProc aglDestroyPBuffer;
#  else
  extern CGContextRef CGGLContextCreate (
	void *glContext, 
	CGSize size, 
	CGColorSpaceRef _hoops_PSHAC
)  __attribute__((weak_import));

  extern GLboolean aglSetPBuffer (
	AGLContext _hoops_HSHAC, 
	AGLPbuffer pbuffer, 
	GLint face, 
	GLint level, 
	GLint screen 
)  __attribute__((weak_import));

  extern GLboolean aglCreatePBuffer (
	GLint width, 
	GLint height, 
	GLenum target, 
	GLenum internalFormat, 
	long max_level, 
	AGLPbuffer *pbuffer
)  __attribute__((weak_import));

  extern GLboolean aglDestroyPBuffer (
	AGLPbuffer pbuffer
)  __attribute__((weak_import));
#  endif
#endif


#ifdef DECLARE_OGL_PROTOTYPES
local void _hoops_PICGC (Display_Context alter * dc);
local void _hoops_CHCGC (Display_Context alter * dc);
local void _hoops_AHCGC (OGLData alter * _hoops_CSRGR);
local void invalidate_cache (OGLData alter * _hoops_CSRGR);
local void identify_renderer (Display_Context alter * dc);
local void _hoops_ARPGC (OGLData alter * _hoops_CSRGR);
local void _hoops_IAHGC (Display_Context alter * dc);

local void _hoops_CAAGR (Net_Rendition const &  nr, int left, int right, int bottom, int top);

local void _hoops_CIHGC (Display_Context const * dc);
local void _hoops_ISHGC (Display_Context const * dc);

local void _hoops_GHRGC (OGLData alter * _hoops_CSRGR);
local void _hoops_AHRGC (OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr, _hoops_PC const & _hoops_HC);

local void _hoops_SAHH (OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr);
local void _hoops_GIIH (OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr);
local void _hoops_AGSP (OGLData alter * _hoops_CSRGR, _hoops_HHCR const & _hoops_IHCR, int flags);

local void set_line_rendition (OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr, Line_Rendition const & _hoops_HC);
local void _hoops_HHCGC (OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr, _hoops_HHA const & matr, RGB const *_hoops_PRSGC, RGB const *_hoops_HRSGC);
local void _hoops_IHCGC (OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr, _hoops_HHA const & _hoops_RRGH);
local void _hoops_RIHGC (OGLData alter * _hoops_CSRGR, Driver_Color const * color);


local void draw_overlay_list (Net_Rendition const &  nr);
local void _hoops_SCPGR (Net_Rendition const &  nr);


local void _hoops_HASGC  (Net_Rendition const &  nr, GLint width, int _hoops_IASGC);

local GLuint _hoops_PIGH (
    OGLData alter * _hoops_CSRGR, 
    Net_Rendition const &  nr, 
    _hoops_RCR alter *txr, 
    _hoops_ARGRA _hoops_GCI,
	int _hoops_GRRA
	);
local bool _hoops_GSAC (
    OGLData alter *_hoops_CSRGR,
    Net_Rendition const &  nr, 
    _hoops_RCR alter *txr, 
    OGL_Render_Control_Flags _hoops_GAGRC,
    _hoops_ARGRA _hoops_GCI,
    GLuint id,
	int _hoops_GRRA
	); 

local bool _hoops_GHAH (OGLData alter * _hoops_CSRGR, Net_Rendition const &  nr);

local void draw_dc_polydot (Net_Rendition const &  nr, int count, DC_Point const * where);
local void draw_dc_polyline (Net_Rendition const &  nr, int count, DC_Point const * points);
local void draw_dc_rectangle (Net_Rendition const &  nr, int left, int right, int bottom, int top);
local void draw_dc_polytriangle (Net_Rendition const &  nr, int count, DC_Point const * points);
local void draw_dc_colorized_polytriangle (Net_Rendition const &  nr, int count, DC_Point const * points, RGBAS32 const * color, bool single);
local void draw_dc_gouraud_polytriangle (Net_Rendition const &  nr, int count, DC_Point const * points, RGBAS32 const * colors);
local void draw_dc_gouraud_polyline (Net_Rendition const &  nr, int count, DC_Point const *points, RGBAS32 const *colors);
local void draw_dc_face (Net_Rendition const &  nr, int count, DC_Point const * points);
local void draw_dc_colorized_face (Net_Rendition const &  nr, int count, DC_Point const * points, RGBAS32 const * color);
local void draw_dc_textured_polytriangle (Net_Rendition const &  nr, int count, DC_Point const * points, RGBA const * color, _hoops_ARPA const * plane, _hoops_RSSH const * _hoops_CCHA, Integer32 param_width, _hoops_SSIC param_flags);
local void draw_dc_rgb32_rasters (Net_Rendition const &  nr, DC_Point const * start, DC_Point const * end, int row_bytes, RGBAS32 const * _hoops_GAAC);

local void _hoops_RRRI (Net_Rendition const & nr, Tristrip const *ts, OGL_Display_List_Bin *_hoops_RRHA);
local void _hoops_CRRI (Net_Rendition const & nr, Tristrip const *ts, OGL_Display_List_Bin *_hoops_RRHA);
local void draw_3d_tristrip (Net_Rendition const &  nr, Tristrip const * ts);
local void _hoops_ARCI (Net_Rendition const &  nr, Tristrip const * ts);

local Geometry const * segment_render (Net_Rendition const &  nr, Geometry const * g, Action_Mask mask, bool single);
local void draw_3d_polyline (Net_Rendition const &  nr, Polyline const * polyline);
local void draw_3d_polygon (Net_Rendition const &  nr, Polygon const * polygon);
local void draw_3d_ellipse (Net_Rendition const &  nr, Ellipse const * ellipse);
local bool _hoops_HSIS (Net_Rendition const &nr, Polygon const *g, bool single);

local void draw_3d_nurbs_curve (Net_Rendition const &  nr, _hoops_PIRGR const * curve);

local void really_draw_3d_polyedge (Net_Rendition const &  nr, Line_Rendition const & _hoops_GHP, Polyedge const * pe, OGL_Display_List_Bin alter *_hoops_RRHA);
local void draw_3d_polyedge (Net_Rendition const &  nr, Polyedge const * pe);
local void _hoops_GPCI (Net_Rendition const &  nr, Polymarker const * pm, OGL_Display_List_Bin alter *_hoops_RRHA);
local void draw_3d_marker (Net_Rendition const &  nr, Marker const * m);
local void draw_3d_polymarker (Net_Rendition const &  nr, Polymarker const * pm);

local void create_region (Net_Rendition const &  nr, Int_Rectangle const * area, void **image, void **z);
local void _hoops_HIPGR (Net_Rendition const &  nr, Int_Rectangle const * area, void alter * image, void alter * z);
local void _hoops_PIPGR (Net_Rendition const &  nr, Int_Rectangle const * area, void alter * image, void alter * z);
local void _hoops_ISPGR (Net_Rendition const &  nr, void alter * image, void alter * z);
local void _hoops_CSPGR (Display_Context alter * dc);
local void _hoops_AGHGR (Display_Context alter * dc);

local void _hoops_CGAGR (Display_Context const * dc, void *list);

local bool start_device (Display_Context alter * dc);
local void stop_device (Display_Context alter * dc);
local void init_picture (Net_Rendition const &  nr);
local void finish_picture (Net_Rendition const &  nr,
				bool swap_buffers);
local void finish_update (Display_Context const * dc);
local void init_update (Display_Context const * dc);
local POINTER_SIZED_INT get_outer_window (Display_Context const *_hoops_SAGRH);
local void free_outer_window (Display_Context const *dc);
local void _hoops_RSCSP (Display_Context const *dc);
local void get_current_info (Display_Context alter * dc);
local void get_physical_info (Display_Context alter * dc);
local bool _hoops_HSCSP (
	Display_Context const * dc,
	int alter * button,
	int alter * x, 
	int alter * y);
local bool _hoops_ISCSP (
	Display_Context const * dc,
	int alter * button, 
	int alter * status);
local void _hoops_PGIGC (OGLData alter * _hoops_CSRGR, Net_Rendition nr, int mode);

		
local bool _hoops_PIAGC(OGLData alter * _hoops_CSRGR);
local bool _hoops_SIAGC(OGLData alter * _hoops_CSRGR, bool _hoops_GCAGC);
local void _hoops_IHAGC(OGLData alter * _hoops_CSRGR);


local bool _hoops_AACR(Net_Rendition const & nr,
						_hoops_GACR alter **_hoops_ASRGR,
						_hoops_GACR alter **dl,
						OGL_Display_List alter **odl,
						unsigned int type);

local void _hoops_GSARC (OGL_Vertex_Buffer_Object *_hoops_SAAS); 
local void _hoops_PRPRC (OGL_Polymarker_Vertex_Buffer_Object *_hoops_SAAS); 
local void _hoops_SPSI (_hoops_AGCI *_hoops_AGAGR); 
local void _hoops_SSRGR (Display_Context const *dc);

local void _hoops_HGCGC (OGLData alter * _hoops_CSRGR, _hoops_GPPA const *_hoops_RPPA);
local bool _hoops_HGRI (Net_Rendition const &nr, unsigned Integer32 _hoops_SRHA, bool _hoops_CISP);
local bool _hoops_HSRI (Net_Rendition const &nr, Line_Rendition const &_hoops_GHP, Polyedge const *pe, int weight);
local bool _hoops_SGAI (Net_Rendition const &nr, _hoops_ICP const &_hoops_CCP, Polymarker const *pm, int *glyph_id_out);
local void _hoops_SCARC (Net_Rendition const & nr, Tristrip const *ts);
local void _hoops_SAARC (Net_Rendition const &		nr,
						OGL_Render_Control *		rc,
						Tristrip const *			ts);
local bool _hoops_RPRC (
						Net_Rendition const &		nr,
						Tristrip const *			ts,
						_hoops_GACR const *		dl,
						OGL_Display_List const *	odl);
local bool pre_pass(	Net_Rendition const &		nr,
						OGL_Render_Control *		rc,
						Tristrip const *			ts);
local bool _hoops_GPRRC (	Net_Rendition const & nr,
						Integer32 _hoops_RPRRC,
						_hoops_SSIC _hoops_APRRC,
						OGL_Render_Control *rc);
local void _hoops_HGCGC (
						OGLData alter * _hoops_CSRGR,
						_hoops_GPPA const *_hoops_RPPA);
local int _hoops_RRHRC (Tristrip const *ts); 
local bool _hoops_HSHS (
						Net_Rendition const &nr, 
						Geometry const *g,
						bool single);

#endif /* _hoops_ICCI _hoops_CHCPI */

#endif
/*_hoops_ISHAC*/











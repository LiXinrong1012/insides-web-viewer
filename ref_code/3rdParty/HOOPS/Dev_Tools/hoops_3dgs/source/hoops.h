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
 * $Id: obf_tmp.txt 1.1123.2.2 2011-01-21 19:38:35 jason Exp $
 */

#ifndef HOOPS_DEFINED
#define HOOPS_DEFINED


/*
 * _hoops_HSRR _hoops_GRR _hoops_GHARR, _hoops_RH _hoops_HSPR _hoops_CHR _hoops_PAPR:
 * 1. _hoops_GHARR _hoops_PPIP - _hoops_IGI _hoops_GGR _hoops_GHARR _hoops_SASI _hoops_AGAH _hoops_GSIHH
 * 2. _hoops_CACSH
 * 3. _hoops_HGGPA _hoops_CPCP - _hoops_RAPSR _hoops_SACSH _hoops_IIGR _hoops_PSHA (_hoops_RIRCP)
 * 4. <_hoops_RIRCP _hoops_PHIAH _hoops_SASI _hoops_APSAR>
 * 5. _hoops_PHIAH _hoops_GSGR - _hoops_IGI _hoops_GGR _hoops_RH _hoops_AGAH _hoops_CSPP _hoops_GPSRR _hoops_GPCSH
 *
 * _hoops_IPCP _hoops_AAPGH _hoops_RPGAH _hoops_GGR _hoops_RH _hoops_PSHR _hoops_AGR _hoops_GAR _hoops_SSIA _hoops_RPGAH _hoops_GGR _hoops_RH _hoops_RPCSH._hoops_APCSH _hoops_RGHR.
 */

#ifdef _AIX
#	ifndef AIX_SYSTEM
#		define	AIX_SYSTEM
#	endif
#	ifndef UNIX_SYSTEM
#		define	UNIX_SYSTEM
#	endif
#	define		HOOPS_BIGENDIAN			1
#	define		HK_PLATFORM				"AIX 4.3.2"
#	define		HK_PLATFORM_ID			0x004
#	define		HK_DEFAULT_PICTURE		H_FORMAT_TEXT("x11/%s", getenv("DISPLAY") ? getenv("DISPLAY") : ":0.0")
#	define		USE_PTHREADS_MUTEX
#	define		_hoops_AGGGA(_yy_,_xx_)		HI_ATan2(_yy_,_xx_)
#	ifdef __64BIT__
#		define	LONG_SIZE				64
#		define	ALIGNMENT				3
#	endif
#endif
#ifdef __hpux
#	ifndef HPUX_SYSTEM
#		define	HPUX_SYSTEM
#	endif
#	ifndef UNIX_SYSTEM
#		define	UNIX_SYSTEM
#	endif
#	define		HOOPS_BIGENDIAN			1
#	define		_hoops_RCRSP			a, r, g, b
#	define		RGB32_ORDER_ARGB
#	define		HK_PLATFORM				"HP-UX 11.0"
#	define		HK_PLATFORM_ID			0x008
#	define		HK_DEFAULT_PICTURE		H_FORMAT_TEXT("x11/%s", getenv("DISPLAY") ? getenv("DISPLAY") : ":0.0")
#	define		USE_PTHREADS_MUTEX
#	ifdef __LP64__
#				define	LONG_SIZE								64
#				define	ALIGNMENT								3
#	endif
#endif
#ifdef __sgi
#	ifndef IRIX_SYSTEM
#		define	IRIX_SYSTEM
#	endif
#	ifndef UNIX_SYSTEM
#		define	UNIX_SYSTEM
#	endif
#	define		HOOPS_BIGENDIAN			1
#	if (_MIPS_SZLONG == 64)
#		define	LONG_SIZE				64
#		define	ALIGNMENT				3
#	endif
#	define		HK_PLATFORM				"IRIX 6.5"
#	define		HK_PLATFORM_ID			0x010
#	define		HK_DEFAULT_PICTURE		H_FORMAT_TEXT("opengl/%s", getenv("DISPLAY") ? getenv("DISPLAY") : ":0.0")
#	define		USE_PTHREADS_MUTEX
#endif
#ifdef __osf__
#	ifndef _hoops_PPCSH
#		define	_hoops_PPCSH
#	endif
#	ifndef UNIX_SYSTEM
#		define	UNIX_SYSTEM
#	endif
#	define		HOOPS_BIGENDIAN			0
#	define		_hoops_RCRSP			b, g, r, a
#	define		RGB32_ORDER_BGRA
#	define		LONG_SIZE				64
#	define		ALIGNMENT				3
#	define		HK_PLATFORM				"DEC OSF/1 Alpha 4.0d"
#	define		HK_PLATFORM_ID			0x002
#	define		HK_DEFAULT_PICTURE		H_FORMAT_TEXT("x11/%s", getenv("DISPLAY") ? getenv("DISPLAY") : ":0.0")
#	define		USE_PTHREADS_MUTEX
#endif
#ifdef vms
#	define		VMS_SYSTEM
#	define		HOOPS_BIGENDIAN			0
#	define		MULTIPLE_DOT_FILENAMES	0
#	define		_hoops_RCRSP			b, g, r, a
#	define		RGB32_ORDER_BGRA
#	ifdef _hoops_HPCSH
#		define	VMS_VAX_SYSTEM
#		if CC$gfloat
#			define		HK_PLATFORM		"OpenVMS/VAX /G_FLOAT 6.0"
#		else
#			define		HK_PLATFORM		"OpenVMS/VAX 6.0"
#		endif
#		ifndef _hoops_CGSPR
#			/* '_hoops_RCIC' _hoops_HIRGR _hoops_GRAA-_hoops_IPCSH _hoops_CIACP _hoops_GGR _hoops_RRGR _hoops_GC,		  */
#			/* _hoops_HIS _hoops_GA'_hoops_RA _hoops_AA _hoops_SCH _hoops_IH _hoops_HPHR _hoops_GSHRA (_hoops_IHRI _hoops_IH _hoops_GSPHR/_hoops_PIPPR _hoops_ISPR) */
#			define		const
#		endif
#		define	signed	/* _hoops_ASSP'_hoops_RA _hoops_PII _hoops_SGH _hoops_IIGR _hoops_HHHA _hoops_CPCSH */
#	else
#		define	_hoops_SPCSH	/* _hoops_HGHP */
#		if __IEEE_FLOAT
#			define		HK_PLATFORM		"OpenVMS/AXP /IEEE_FLOAT 6.1"
#		else
#			define		HK_PLATFORM		"OpenVMS/AXP 6.1"
#		endif
		void *__MEMSET(void *_hoops_GHCSH, int _hoops_RHCSH, unsigned int _hoops_AHCSH);
#		define	SET_MEMORY(_hoops_PCAP, size, value)	__MEMSET (_hoops_PCAP, value, size)
#	endif
#	define		HK_PLATFORM_ID			0x001
#	define		HK_DEFAULT_PICTURE		"x11/decw$display"
#endif
#ifdef __sun
#	ifndef SOLARIS_SYSTEM
#		define	SOLARIS_SYSTEM
#	endif
#	ifndef UNIX_SYSTEM
#		define	UNIX_SYSTEM
#	endif
#	ifdef __sparc
#		define		HOOPS_BIGENDIAN			1
#		define		HK_PLATFORM				"Solaris-Sparc"
#		define		HK_PLATFORM_ID			0x040
#	        define		HK_DEFAULT_PICTURE		H_FORMAT_TEXT("x11/%s", getenv("DISPLAY") ? getenv("DISPLAY") : ":0.0")
#		ifdef __sparcv9
#			define	LONG_SIZE			64
#			define	ALIGNMENT			3
#		endif
#		define		USE_PTHREADS_MUTEX
#	endif
#	ifdef __i386
#		define		HOOPS_BIGENDIAN			0
#		define		HK_PLATFORM				"Solaris-I386"
#		define		HK_PLATFORM_ID			0x040
#	        define		HK_DEFAULT_PICTURE		H_FORMAT_TEXT("x11/%s", getenv("DISPLAY") ? getenv("DISPLAY") : ":0.0")
#		define		USE_PTHREADS_MUTEX
#		define		_hoops_RCRSP			r, g, b, a
#		define		RGB32_ORDER_RGBA
#	endif
#	ifdef __amd64
#		define		HOOPS_BIGENDIAN			0
#		define		HK_PLATFORM				"Solaris-AMD64"
#		define		HK_PLATFORM_ID			0x040
#	        define		HK_DEFAULT_PICTURE		H_FORMAT_TEXT("x11/%s", getenv("DISPLAY") ? getenv("DISPLAY") : ":0.0")
#		define		LONG_SIZE				64
#		define		ALIGNMENT				3
#		define		USE_PTHREADS_MUTEX
#		define		_hoops_RCRSP			r, g, b, a
#		define		RGB32_ORDER_RGBA
#	endif
#endif
#ifdef _MSC_VER
#	pragma warning (disable: 4127)	// _hoops_RAGPR _hoops_CRHRH _hoops_HRGR _hoops_SRSR
#	pragma warning (disable: 4244)	// _hoops_PHCSH _hoops_IS _hoops_SCSH _hoops_IIGR _hoops_HRHC _hoops_IGIR
#	pragma warning (disable: 4996)	// _hoops_HPRGR _hoops_GSGR _hoops_PSCH _hoops_GHSAR _hoops_HGPSA

#	ifndef WIN32_SYSTEM
#		define	WIN32_SYSTEM
#	endif
#	ifndef WINDOWS_SYSTEM
#		define	WINDOWS_SYSTEM
#	endif

#	define		HOOPS_BIGENDIAN			0
#	define		_hoops_RCRSP			b, g, r, a
#	define		RGB32_ORDER_BGRA
#	define		HK_PLATFORM_ID	0x200
#	define		PATH_DELIMITER			'\\'
#	define		PATH_DELIMITER_TWO		':'

#	ifndef HOOPS_DEBUG_BUILD
#		define NODEFAULT	default: __assume (0);
#	endif

#	if !defined (HOOPS_STATIC_LIB)
#		if defined (HOOPS_WINDOWS_HDI_DRIVER)
#			define HOOPS_API __declspec(dllimport)
#		else
#			define HOOPS_API __declspec(dllexport)
#		endif
#	endif

#	ifndef INLINE
#		define	INLINE		__forceinline
#	endif

#	ifndef HC_CDECL
#		define	HC_CDECL						__cdecl
#	endif
#	ifndef HF_STDCL
#		define	HF_STDCL						__stdcall
#	endif

#	if defined (_M_X64)
#		define		POINTER_SIZED_INT __int64
#		define		ALIGNMENT			3
#		ifndef WIN64_SYSTEM
#			define		WIN64_SYSTEM
#		endif
#		define		HK_PLATFORM "Microsoft Win64 X64"
#		define		_hoops_HHCSH
#		define		_hoops_CHAGP
extern "C" void __cdecl _mm_prefetch (char const *a, int _hoops_RIRIP);
#pragma intrinsic(_mm_prefetch)

extern "C" unsigned char __cdecl _InterlockedCompareExchange128 (__int64 volatile *_hoops_IHCSH, __int64 _hoops_CHCSH, __int64 _hoops_SHCSH, __int64 * _hoops_GICSH);
#pragma intrinsic(_InterlockedCompareExchange128)

#	endif

#	ifdef _M_IX86
#		define		HK_PLATFORM		"Microsoft Win32 Intel x86"
#		define		_hoops_IIIPA
#		define		_hoops_CHAGP

#	endif

extern "C" long __cdecl _InterlockedIncrement(long volatile *_hoops_RICSH);
extern "C" long __cdecl _InterlockedDecrement(long volatile *_hoops_AICSH);
extern "C" long __cdecl _InterlockedExchange(long volatile *_hoops_PICSH, long _hoops_HICSH);
#pragma intrinsic (_InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange)

extern "C" long __cdecl _InterlockedCompareExchange (long volatile *_hoops_IHCSH, long _hoops_IICSH, long _hoops_GICSH);
extern "C" __int64 __cdecl _InterlockedCompareExchange64 (__int64 volatile *_hoops_IHCSH, __int64 _hoops_IICSH, __int64 _hoops_GICSH);
#pragma intrinsic (_InterlockedCompareExchange, _InterlockedCompareExchange64)



#	ifdef _WIN32_WCE
#		define		HK_PLATFORM		"Microsoft Win32 CE"
#		define		HK_DEFAULT_PICTURE		"msw/window0"
#	endif

#	ifndef HK_PLATFORM
#		define		HK_PLATFORM		"Microsoft Win32 Unknown"
#	endif

#	ifndef _WIN32_WCE
#	include		<math.h>
#	define		_INCLUDED_SYSTEM_MATH_H_
#	define		_hoops_RICH(_hoops_CPAIH,_hoops_CICSH,_hoops_SICSH) do {					\
					float _hoops_GCCSH = _hoops_PCSR (_hoops_CPAIH); \
					_hoops_CICSH = (float) sin (_hoops_GCCSH);				\
					_hoops_SICSH = (float) cos (_hoops_GCCSH);				\
				} while (0)
#	define		COS(_hoops_CPAIH)		(float) cos (_hoops_PCSR (_hoops_CPAIH))
#	define		_hoops_RCCSH
#	endif

#	ifndef	HK_DEFAULT_PICTURE
#		define		HK_DEFAULT_PICTURE		"opengl/window0"
#	endif
#endif
#ifdef __linux__
#	ifndef LINUX_SYSTEM
#		define	LINUX_SYSTEM
#	endif
#	ifndef UNIX_SYSTEM
#		define	UNIX_SYSTEM
#	endif
#	define		HOOPS_BIGENDIAN			0
#	define		_hoops_RCRSP			r, g, b, a
#	define		RGB32_ORDER_RGBA
#	define		HK_PLATFORM				"Linux"
#	define		HK_PLATFORM_ID			0x400
#	define		HK_DEFAULT_PICTURE		H_FORMAT_TEXT("x11/%s", getenv("DISPLAY") ? getenv("DISPLAY") : ":0.0")
#	define		USE_PTHREADS_MUTEX
#	if defined (__i386__)
#		define	_hoops_ACCSH
#	endif
#	if defined (_hoops_PCCSH)
#		define	_hoops_HCCSH
#	endif
#	ifdef _LP64
#		define	LONG_SIZE				64
#		define	ALIGNMENT				3
#	endif
#	define	_hoops_HIAGP
#endif
#ifdef __APPLE_CC__
#	ifndef OSX_SYSTEM
#		define	OSX_SYSTEM
#	endif
#	ifndef UNIX_SYSTEM
#		define	UNIX_SYSTEM
#	endif
#	define		HOOPS_BIGENDIAN		0
#	define		_hoops_RCRSP		r, g, b, a
#	define		RGB32_ORDER_RGBA
#	define		HK_PLATFORM			"OSX"
#	define		HK_PLATFORM_ID		0x400
#	define		USE_PTHREADS_MUTEX
#	if defined 	(__x86_64__)
#		define	HK_DEFAULT_PICTURE	"cocoa_opengl/window"
#		define 	LONG_SIZE		64
#		define 	ALIGNMENT		3
#	else
#		define	HK_DEFAULT_PICTURE	"opengl/window"
#	endif
#endif

#ifndef NODEFAULT
#define NODEFAULT default: ASSERT(0); break;
#endif

#ifndef INLINE
#	define	INLINE		inline
#endif

#ifndef nullroutine
#	define		nullroutine		null
#endif

#ifndef ALIGNMENT
#	define		ALIGNMENT		2				/* _hoops_CSCS _hoops_PPGS _hoops_AHSGP */
#endif
#ifndef _hoops_ICCSH
#	define		_hoops_ICCSH		32
#endif
#ifndef LONG_SIZE
#	define		LONG_SIZE		32
#endif
#ifndef POINTER_SIZED_INT
#	define		POINTER_SIZED_INT		long
#endif

#ifndef _hoops_RCRSP
#	define		_hoops_RCRSP			a, b, g, r
#	define		_hoops_CCCSH
#endif

#ifndef HK_PLATFORM_ID
#	define		HK_PLATFORM_ID			0x800	/* _hoops_PIHA _hoops_SHH _hoops_IRS _hoops_HCGP _hoops_RIPHR */
#endif

#ifndef PATH_DELIMITER
#	define		PATH_DELIMITER			'/'
#endif
#ifndef PATH_DELIMITER_TWO
#	define		PATH_DELIMITER_TWO		'\0'
#endif

#ifndef MULTIPLE_DOT_FILENAMES
#	define		MULTIPLE_DOT_FILENAMES	1		/* _hoops_ICRP _hoops_AAPGH _hoops_GCGH */
#endif

#ifndef _hoops_HSPGR
#	define		_hoops_HSPGR			1000.0f				/* _hoops_SCCSH _hoops_RIR _hoops_GIAP */
#endif

#ifndef UNREFERENCED
#		define UNREFERENCED(param) ((void)(param))
#endif

#define HK_PLATFORM_LEN 38 /* _hoops_PIHA _hoops_SIHRR _hoops_GSCSH */

#define HK_Pi							3.141592653589793238
#define _hoops_PCSR(_hoops_RSCSH)		((_hoops_RSCSH) * (float)(HK_Pi / 180.0))
#define RADIANS_TO_DEGREES(_hoops_ASCSH)		((_hoops_ASCSH) * (float)(180.0 / HK_Pi))

INLINE int _hoops_PSCSH(double d)
{
   union _hoops_HSCSH
   {
      double d;
      int l[2];
   };
   volatile _hoops_HSCSH c;
   if (d < 0)
	   d += (0.5 - 1.5e-8);
   else
	   d -= (0.5 - 1.5e-8);
   c.d = d + 6755399441055744.0;
#if HOOPS_BIGENDIAN
   return c.l[1];
#else
   return c.l[0];
#endif
}


INLINE int _hoops_ISCSH(double d)
{
   union _hoops_HSCSH
   {
      double d;
      int l[2];
   };
   volatile _hoops_HSCSH c;
   c.d = d + 6755399441055744.0;
#if HOOPS_BIGENDIAN
   return c.l[1];
#else
   return c.l[0];
#endif
}


/* _hoops_RPGP _hoops_IH "_hoops_HAR _hoops_IRS _hoops_PHI" (_hoops_IGIPR _hoops_GPRR _hoops_AIIC _hoops_ICPAA _hoops_GGR) */
#define _hoops_CSCSH(x) (!((x)==(x)))


/* _hoops_SSCSH _hoops_PIH _hoops_CSSC... */
#if (_hoops_ICCSH == 32)
#  define		Integer32	int
#else
#  define		Integer32	long
#endif

#ifndef HK_DEFAULT_PICTURE
#	error	_hoops_GGSSH for ?_hoops_RGSSH not _hoops_AGSSH in -- _hoops_AHPGR define or system not _hoops_PGSSH
#endif

#ifndef _INCLUDED_SYSTEM_MATH_H_
#	include		<math.h>
#	define		_INCLUDED_SYSTEM_MATH_H_
#endif

#include	<string.h>
#ifdef _DEBUG
#	include	<stdio.h>
#	include	<stdarg.h>

#	ifdef _MSC_VER
        extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA (char const * _hoops_HGSSH);
#		define OutputDebugString OutputDebugStringA
#	endif
#endif

inline void _hoops_IGSSH (char const * format, ...) {
#ifdef _DEBUG
	char		buffer[1024];
	va_list		_hoops_CGSSH;

	va_start (_hoops_CGSSH, format);
	vsprintf (buffer, format, _hoops_CGSSH);
	va_end (_hoops_CGSSH);

#	if defined (_MSC_VER) && !defined (_WIN32_WCE)
		OutputDebugString (buffer);
#	else
		fprintf(stdout, buffer);
		fflush(stdout);
#	endif
#else
	UNREFERENCED (format);
#endif
}



//#_hoops_PPIP _hoops_SGSSH

#ifdef HOOPS_DEBUG_BUILD
#ifdef _MSC_VER
#  undef ASSERT
#define ASSERT(x) ((!(x))?__debugbreak():1)
#else
#  include <assert.h>
#  undef ASSERT
#  define ASSERT(x) assert(x)
#endif
#else
#  undef ASSERT
#  define ASSERT(x) _hoops_GRSSH(x)
#endif

#define	alter		/* _hoops_RRSSH */

#define globaldata		extern
#define local			static	/* _hoops_IRGH _hoops_PIH _hoops_CGH _hoops_SHH '_hoops_RCIC' _hoops_HAH! */

#ifndef _hoops_PCCAR
#	define _hoops_PCCAR		while (1)
#endif
#ifndef _hoops_RGGA
#	define _hoops_RGGA(x)		while (!(x))
#endif
#ifndef _hoops_GGAPR
#	define _hoops_GGAPR(x)	(int)(sizeof(x)/sizeof(x[0]))
#endif
#ifndef _hoops_HHHI
#	define _hoops_HHHI		/* (_hoops_HSSC _hoops_RHIR -- _hoops_RIIA _hoops_IIGR _hoops_IHSA) */
#endif

/* _hoops_AA _hoops_GII _hoops_RGHP _hoops_PAIGR _hoops_HAR _hoops_CHIA _hoops_HPP _hoops_RH _hoops_GHARR _hoops_RIS _hoops_ARRS */

#define _hoops_AHAGP(condition, message) \
	class message { char array[condition ? 1 : -1]; }

#ifndef HOOPS_API
#		define HOOPS_API
#endif

#ifndef HC_CDECL
#	define		HC_CDECL
#endif
#ifndef HF_STDCL
#	define		HF_STDCL
#endif


/*****************************************************************************/
/*				_hoops_HGH _hoops_IGPC _hoops_IS _hoops_HHPR/_hoops_HHSP						 */

/* _hoops_SIGP: _hoops_RCSAR _hoops_PPIP _hoops_GGR _hoops_RGR _hoops_PCAPA _hoops_CGH _hoops_SHH _hoops_ARSSH _hoops_CCA _hoops_RGCI _hoops_HAII _hoops_CHS */
#ifdef _hoops_PRSSH
#	define		DISABLE_METAFILE
#	define		DISABLE_TABLE_LOOKUPS
#	define		DISABLE_PHONG
#	define		DISABLE_TEXTURING
#	define		DISABLE_SORTING_HSR
#	define		DISABLE_DRAW_3D
#	define		DISABLE_RASTERIZER
#	define		DISABLE_DATABASE_EDIT
#	define		DISABLE_GEOMETRY_EDIT
#	define		DISABLE_GEOMETRY_SHOW
#	define		DISABLE_SEARCH
#	define		DISABLE_SHOW
#	define		DISABLE_UNSET
#	define		DISABLE_GEOMETRY_ATTRIBUTES
#	define		DISABLE_LOD_GENERATION
#	define		DISABLE_CODE_GENERATION
#	define		DISABLE_DEFINED_FONTS
#	define		DISABLE_EVENTS
#	define		DISABLE_COLOR_NAMES
#	define		DISABLE_COLOR_MAPS
#	define		DISABLE_PARTIAL_ERASE
#	define		DISABLE_INSTANCING
#	define		DISABLE_POLY_SELECTION
#	define		DISABLE_COMPUTE
#	define		DISABLE_SELECTION
#	define		DISABLE_BIT_RASTERS
#	define		DISABLE_GRAY8_RASTERS
#	define		DISABLE_MAPPED16_RASTERS
#	define		DISABLE_MAPPED8_RASTERS
#	define		DISABLE_STYLE_SEGMENT
#	define		DISABLE_CALLBACKS
#	define		DISABLE_NURBS
#	define		DISABLE_CUT_GEOMETRY
#	define		DISABLE_SIMPLE_SHADOW
#	define		DISABLE_UNICODE_OPTIONS
#	define		DISABLE_ERROR_WARNING_INFO
#	define		DISABLE_NON_MANIFOLD_OPTIMIZATION
#	define		DISABLE_NON_RGB_IMAGES
#	define		DISABLE_EXTENDED_TEXTURE
#	define		DISABLE_SOFTWARE_TEXTURE
#	define		DISABLE_AIR_OPTIONS
#endif

#ifdef _hoops_GGHSH
#	define DISABLE_NON_MANIFOLD_OPTIMIZATION
#	define DISABLE_NON_RGB_IMAGES
#	define DISABLE_EXTENDED_TEXTURE
#	define DISABLE_SOFTWARE_TEXTURE
#	define DISABLE_AIR_OPTIONS
#	define DISABLE_TABLE_LOOKUPS
#	define _hoops_HRSSH
#	define _hoops_IRSSH
#	define DISABLE_CODE_GENERATION
#	define DISABLE_PARTIAL_ERASE
#	define DISABLE_BIT_RASTERS
#	define DISABLE_GRAY8_RASTERS
#	define DISABLE_MAPPED16_RASTERS
#	define DISABLE_MAPPED8_RASTERS
#	define _hoops_CRHSA
#ifndef _DEBUG
#	define DISABLE_ERROR_WARNING_INFO
#	define DISABLE_METAFILE
#	define _hoops_CRSSH
#endif
#	define DISABLE_PHONG
#	define DISABLE_LOD_GENERATION
#	define _hoops_SGRCP
#	define _hoops_GSPIR
#	define _hoops_SRSSH
#	define DISABLE_RASTERIZER
#	define _hoops_SRIRA
#   define _hoops_GASSH
#   define _hoops_HPAIH
#   define _hoops_RASSH
#   define _hoops_AASSH
/*
# _hoops_PPIP _hoops_PASSH
# _hoops_PPIP _hoops_HASSH
# _hoops_PPIP _hoops_IASSH
# _hoops_PPIP _hoops_CASSH
# _hoops_PPIP _hoops_SASSH
#	_hoops_PPIP _hoops_GPSSH
*/
#endif

#ifdef DISABLE_SHOW
#	define		_hoops_RPSSH
#	define		_hoops_PRPCR
#endif

#ifdef DISABLE_NURBS
#	define		_hoops_CCPIR
#	define		_hoops_GSPIR
#endif

#ifdef DISABLE_GEOMETRY_ATTRIBUTES
#	define		_hoops_GCGHR
#	define		_hoops_HCGHR
#	define		_hoops_PGPHR
#	define		_hoops_RGIPR
#	define		_hoops_CSGHR
#	define		_hoops_IIICA	/* _hoops_SHCAR, _hoops_HPRC */
#endif

#ifdef _hoops_GCGHR
#	define		_hoops_SGRCP
#endif


#ifdef DISABLE_SORTING_HSR
#	define		_hoops_CRHSA
#	define		_hoops_IRRHP
#	define		_hoops_IRSSH
#endif

#ifdef DISABLE_RASTERIZER
#	define		_hoops_RGGCR
#	define		_hoops_GCSIR
#endif

#ifdef DISABLE_DEFINED_FONTS
#	define		_hoops_HRSSH
#endif

#ifdef DISABLE_SELECTION
#	define		_hoops_SSAPA
#endif


/* _hoops_HHSA _hoops_HICA _hoops_GCHH _hoops_GPP _hoops_APSSH _hoops_GRAA-_hoops_IGRP _hoops_GGGRR */
#ifdef DISABLE_COLOR_MAPS
#	ifndef _hoops_SGRCP
#		error	_hoops_PPSSH _hoops_HPSSH _hoops_IPSSH
#	endif
#endif

#ifdef DISABLE_DRAW_3D
#	ifndef DISABLE_SORTING_HSR
#		error	_hoops_CPSSH _hoops_HPSSH _hoops_SPSSH
#	endif
#	ifndef _hoops_CRHSA
#		error	_hoops_GHSSH _hoops_HPSSH _hoops_SPSSH
#	endif
#	ifndef _hoops_IRRHP
#		error	_hoops_AHHSA _hoops_HPSSH _hoops_SPSSH
#	endif
#	ifndef _hoops_IRSSH
#		error	_hoops_RHSSH _hoops_HPSSH _hoops_SPSSH
#	endif
#	ifndef _hoops_GCSIR
#		error	_hoops_AHSSH _hoops_HPSSH _hoops_SPSSH
#	endif
#	ifndef _hoops_RGGCR
#		error	_hoops_PHSSH _hoops_HPSSH _hoops_SPSSH
#	endif
#	ifndef DISABLE_PHONG
#		error	_hoops_HHSSH _hoops_HPSSH _hoops_SPSSH
#	endif
#	ifndef DISABLE_SELECTION
#		error	_hoops_IHSSH _hoops_HPSSH _hoops_SPSSH
#	endif
#endif



#ifdef DISABLE_PHONG
#	ifdef DISABLE_TEXTURING
#		define _hoops_IHSIP /* _hoops_PPCAR _hoops_ICCGR _hoops_RRGR _hoops_GPAC */
#	endif
#endif


/*****************************************************************************/

/* _hoops_AGCR _hoops_RRP _hoops_IS _hoops_PSSP _hoops_CHSSH/_hoops_SHSSH _hoops_HSH _hoops_GGR _hoops_GISSH._hoops_GGHR */
#	define		_hoops_RISSH				2
#	define		_hoops_AISSH				2


// _hoops_CSCS _hoops_RIHH _hoops_HARH
#define _hoops_CCSPP		0x00
#define _hoops_ICSPP	0x01
#define _hoops_HCSPP		0x02
#define _hoops_PCSPP		0x03
// _hoops_HIGPH
#define _hoops_GPSAH	0x10
#define _hoops_RPSAH		0x20
// _hoops_PISSH _hoops_GGGRR
#define _hoops_HISSH		0x12
#define _hoops_IISSH	0x32

#ifndef DISABLE_ERROR_WARNING_INFO

#	define	_hoops_SGSPR(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)	\
				HI_Basic_Error (null, _hoops_CCSPP, _hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#	define	_hoops_SHCHR(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)		\
				HI_Basic_Error (null, _hoops_CCSPP, _hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)
#	define	_hoops_PCSSH(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)		\
				HI_Basic_Error (null, _hoops_CCSPP, _hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)
#	define	HE_WARNING(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)		\
				HI_Basic_Error (null, _hoops_ICSPP, _hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#	define	_hoops_PHPGR(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)		\
				HI_Basic_Error (null, _hoops_ICSPP, _hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)
#	define	_hoops_ARGIP(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)	\
				HI_Basic_Error (null, _hoops_ICSPP, _hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)
#	define	HE_ERROR(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)	\
				HI_Basic_Error (null, _hoops_HCSPP, _hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#	define	HE_ERROR2(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)		\
				HI_Basic_Error (null, _hoops_HCSPP, _hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)
#	define	HE_ERROR3(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)		\
				HI_Basic_Error (null, _hoops_HCSPP, _hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)
#	define	_hoops_HRAIR(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)	\
				HI_Basic_Error (null, _hoops_PCSPP, _hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#	define	_hoops_RIHPH(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)		\
				HI_Basic_Error (null, _hoops_PCSPP, _hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)
#	define	_hoops_ICSSH(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)		\
				HI_Basic_Error (null, _hoops_PCSPP, _hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)
#	define	_hoops_IPR(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH) \
				HI_Basic_Error (null, _hoops_HISSH, _hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#	define	_hoops_IISCP(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)		\
				HI_Basic_Error (0, _hoops_HISSH, _hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)
#	define	_hoops_CCSSH(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH) \
				HI_Basic_Error (null, _hoops_HISSH, _hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)
#	define	_hoops_SPCI(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)	\
				HI_Basic_Error (null, _hoops_IISSH, _hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#else
#	define	_hoops_SGSPR(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#	define	_hoops_SHCHR(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)
#	define	HE_WARNING(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#	define	_hoops_PHPGR(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)
#	define	_hoops_ARGIP(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)
#	define	HE_ERROR(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#	define	HE_ERROR2(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)
#	define	HE_ERROR3(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)
#	define	_hoops_HRAIR(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#	define	_hoops_RIHPH(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)
#	define	_hoops_ICSSH(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)
#	define	_hoops_IPR(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#	define	_hoops_IISCP(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH)
#	define	_hoops_CCSSH(_hoops_CISSH,_hoops_SISSH,_hoops_RCSSH,_hoops_ACSSH,_hoops_HCSSH)
#	define	_hoops_SPCI(_hoops_CISSH,_hoops_SISSH,_hoops_GCSSH)
#endif

#define HC_INTERFACE		extern "C" HOOPS_API
#define GLOBAL_FUNCTION		extern HOOPS_API
#define GLOBAL_DATA			extern HOOPS_API
#define _hoops_SCSSH ...


#define	Begin_HOOPS_Namespace	namespace HOOPS {
#define	End_HOOPS_Namespace		}
#define	Use_HOOPS_Namespace		using namespace HOOPS


Begin_HOOPS_Namespace
	typedef POINTER_SIZED_INT		Key;
	struct _hoops_HPAH;
	struct _hoops_CRCP;
	struct _hoops_AIGPR;
	struct _hoops_IGHGP;
	struct _hoops_GSSSH;
	struct _hoops_SIHIR;
	struct _hoops_IGRCR;
	struct _hoops_GCIIR;
	struct Memory_Pool;
	struct _hoops_HRPA;
End_HOOPS_Namespace;
Use_HOOPS_Namespace;



// _hoops_RSSSH _hoops_SGS _hoops_CHR _hoops_HAR _hoops_GGR _hoops_RH _hoops_AGAH _hoops_RSIRR _hoops_GC _hoops_HIH _hoops_GRP _hoops_SCH

GLOBAL_DATA	_hoops_IGHGP *			HOOPS_WORLD;

GLOBAL_DATA	_hoops_GSSSH *	HOOPS_ETERNAL_WORLD;


GLOBAL_FUNCTION bool HI_Do_Update (
	_hoops_AIGPR *	_hoops_RIGC,
	double					limit,
	bool					_hoops_SCSIH);

GLOBAL_FUNCTION void HI_Propagate_Activity (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_SIHIR *_hoops_CISIR,
	Integer32 which);

GLOBAL_FUNCTION void HI_Define_Constant_Options (
	_hoops_IGRCR const *_hoops_PPCIH,
	int _hoops_HPCIH,
	_hoops_GCIIR *_hoops_SPHHR);


GLOBAL_FUNCTION void HI_Basic_Error (
	_hoops_AIGPR * _hoops_RIGC,
	int level, int category, int specific,
	char const * buf1, char const  *buf2 = 0, char const * buf3 = 0);

GLOBAL_FUNCTION char const * HI_Last_Substring_In_String (char const *_hoops_RHCIH, char const *string);

GLOBAL_FUNCTION char const * HI_CI_Last_Substring_In_String (char const *_hoops_RHCIH, char const *string);

GLOBAL_FUNCTION char const * HI_CI_First_Substring_In_String (char const *_hoops_RHCIH, char const *string);

GLOBAL_FUNCTION bool HI_CI_Equal_Strings (char const *a, char const *b);

GLOBAL_FUNCTION bool HI_CI_Equal_Strings_To_Max (char const *a, int m, char const *b);

GLOBAL_FUNCTION void HI_SinCos (float _hoops_RAHCR, float *_hoops_GGHCR, float *_hoops_AGHCR);

GLOBAL_FUNCTION float HI_Cos (float _hoops_RAHCR);

GLOBAL_FUNCTION Key HI_Key_To_Internal (_hoops_AIGPR * _hoops_RIGC, Key key, _hoops_CRCP const * _hoops_SRCP);

GLOBAL_FUNCTION void HI_Start_Hoops (char const *_hoops_SCPGA);

GLOBAL_FUNCTION void HI_Dump_Code (char const *string);

GLOBAL_FUNCTION void HI_Chain_Code_Files (void);

GLOBAL_FUNCTION char * HI_Sprintf4 (
	_hoops_AIGPR * _hoops_RIGC,
	char *buf,
	char const *spec,
	int _hoops_CPIPP,
	int _hoops_SPIPP,
	void const *_hoops_AIPPA,
	void const *_hoops_PIPPA);


/*
** _hoops_PRCR _hoops_IIGR _hoops_IRS _hoops_ASSSH _hoops_IRHS _hoops_PPGS, _hoops_GSSR _hoops_PPGS _hoops_GCA _hoops_IRS _hoops_ASSSH...
** _hoops_AGCR _hoops_RIGR/_hoops_PSSSH _hoops_SRCH _hoops_RH _hoops_ARPC (_hoops_HPIAA _hoops_RH _hoops_HSSSH
** _hoops_PPGS _hoops_GHARR _hoops_HRGR _hoops_ACAS _hoops_ISSSH-_hoops_ICIC)
*/

GLOBAL_FUNCTION void * HI_System_Alloc (size_t size);
GLOBAL_FUNCTION void HI_System_Free (void *pntr);

#define ALLOCATE_MEMORY(p,t) (p = (t *)HI_System_Alloc (sizeof(t)))
#define FREE_MEMORY(p,t) HI_System_Free (p)

#define	ALLOCATE_MEMORY_ARRAY(p,c,t)	(p = (t *)HI_System_Alloc ((c)*sizeof(t)))
#define	FREE_MEMORY_ARRAY(p,c,t)		HI_System_Free (p)


/* _hoops_PIGGP _hoops_CCA _hoops_CSSC _hoops_GGR _hoops_CSSSH._hoops_GGHR _hoops_HIH _hoops_GRP _hoops_IRISR _hoops_SSSSH _hoops_RCAPH */
typedef void *	_hoops_CPGRR;
typedef void *	Lock;

GLOBAL_FUNCTION int HI_Check_Lock (Lock hl, char const * file, int line);


#define HMUTEX_ERROR(_m_)	_hoops_IISCP (0, 0, "Multithreading control error", _m_)
#include "hmutex.h"


GLOBAL_FUNCTION _hoops_AIGPR * HI_Find_Thread_Specific_Data (HThreadID _hoops_GGGGI, bool _hoops_RGGGI);

GLOBAL_FUNCTION _hoops_AIGPR * HI_Set_Name (const char * _hoops_SCPGA);

GLOBAL_FUNCTION void HI_Adjoint_44 (float const *matp, float alter *_hoops_IRIPA);


/* _hoops_PHHR _hoops_HGCR _hoops_RH _hoops_HRPR _hoops_AGGGI _hoops_GSSRH _hoops_IGRC _hoops_APHR _hoops_IS _hoops_PPIP
 * _hoops_PA. _hoops_PGGGI _hoops_HGGGI _hoops_AARRH _hoops_HGAP _hoops_RGR _hoops_CPCP.
 */
#include "tags.h"


typedef VList<_hoops_PHIP *> _hoops_RPAPA;
typedef VHash<void const *, _hoops_RPAPA *> _hoops_IGGGI;

typedef VList<int *> _hoops_CGGCA;
typedef VList<_hoops_CGGCA *> _hoops_CRGCA;

typedef VList<_hoops_CPGGH *> _hoops_RGSIH;
typedef VList<_hoops_HCHSP *> _hoops_CSHSP;
typedef VList<_hoops_HSPPP *> _hoops_CGGGI;

typedef VList<_hoops_CRCP *> _hoops_IIPSA;
typedef VList<Shell *> _hoops_SGGGI;

typedef VList<_hoops_HPPIR const *> _hoops_CGGSA;
typedef VList<_hoops_SPPIR const *> _hoops_SPGIP;
typedef VList<Geometry *> _hoops_GRGGI;

typedef VStringHash<Named_Material *> _hoops_ISGPH;
typedef VStringHash<_hoops_CRCP *> _hoops_CRPSA;
typedef VStringHash<int> _hoops_SSAH;
typedef VStringHash<size_t> _hoops_RRGGI;
typedef VStringHash<POINTER_SIZED_INT> _hoops_PCS;

typedef _hoops_RRPSA<_hoops_CRCP const *> _hoops_PAPSA;

#define _hoops_PAPHP		128
typedef VHash<void const *, int> _hoops_AAPHP;

typedef VHash<POINTER_SIZED_INT, POINTER_SIZED_INT> _hoops_HICRA;
typedef VList<POINTER_SIZED_INT> _hoops_IICRA;

typedef VHash<_hoops_HSPPP *, POINTER_SIZED_INT> _hoops_ARGGI;

typedef VHash<long, void *> _hoops_PGGSA;
typedef VHash<POINTER_SIZED_INT, _hoops_IHSCA *> _hoops_GISCA;

typedef VHash<HThreadID, _hoops_AIGPR *> _hoops_PRGGI;


typedef VArray<POINTER_SIZED_INT> _hoops_HRGGI;
typedef VArray<Geometry *> _hoops_IPGIA;
typedef VArray<Key> _hoops_IRGIA;
typedef VArray<unsigned short> _hoops_IRGGI;
typedef VArray<wchar_t> _hoops_CRGGI;
typedef VArray<char> _hoops_SRGGI;
typedef VArray<int> _hoops_GAGGI;
typedef VArray<unsigned int> _hoops_RAGGI;
typedef VArray<Point> _hoops_AAGGI;
typedef VArray<_hoops_ARPA> _hoops_PAGGI;
typedef VArray<float> _hoops_HAGGI;

typedef VHeap<_hoops_CRCP const *,float, false, false> _hoops_IAGGI;
typedef VHeap<_hoops_CRCP const *,int, true, false> _hoops_CAGGI;



Begin_HOOPS_Namespace

class _hoops_GPPGP {
	public:
		_hoops_GPPGP () {}
		// _hoops_HHH _hoops_IHAGH _hoops_AARRH _hoops_HGAP _hoops_SGS _hoops_SR _hoops_SHH _hoops_SHSS _hoops_IS _hoops_HSPC _hoops_IRS _hoops_CSHGR _hoops_PRGI _hoops_CCA _hoops_PSP _hoops_PIH...
		explicit _hoops_GPPGP (int) {}

		// _hoops_RH _hoops_PRRPA _hoops_SGH _hoops_IIGR _hoops_RH _hoops_CSHGR _hoops_SCH _hoops_IS _hoops_ASRC _hoops_IRS _hoops_IRAP _hoops_CRS _hoops_PIRA _hoops_IH _hoops_GII _hoops_GSSR _hoops_CRS _hoops_GPRR
		template <typename T>	operator T* () const	{ return 0; }

		//_hoops_SAGGI <_hoops_GPGGI _hoops_SAAAR> 	_hoops_CICC _hoops_SIRRR== (_hoops_SAAAR _hoops_RCIC & _hoops_SGS) _hoops_RCIC;
		//_hoops_SAGGI <_hoops_GPGGI _hoops_SAAAR> 	_hoops_CICC _hoops_SIRRR!= (_hoops_SAAAR _hoops_RCIC & _hoops_SGS) _hoops_RCIC;

	private:
		_hoops_GPPGP (_hoops_GPPGP const &);
		_hoops_GPPGP & operator= (_hoops_GPPGP const &);
		void	operator& () const;
};

#if defined (_MSC_VER) && (_MSC_VER <= 1200) || defined (__sun) || defined (__hpux)
#	define null	0	/// _hoops_IHAGH _hoops_RHGS _hoops_HICA _hoops_RPGGI _hoops_PAH'_hoops_RA _hoops_RGHH _hoops_RH _hoops_APGGI _hoops_RIRIA _hoops_API
#else
	const _hoops_GPPGP null (0);

	//_hoops_SAGGI <_hoops_GPGGI _hoops_SAAAR> 	_hoops_PPGGI _hoops_CICC _hoops_HPGGI::_hoops_SIRRR== (_hoops_SAAAR _hoops_RCIC & _hoops_SGS) _hoops_RCIC { _hoops_ASRC _hoops_SGS == _hoops_IRAP; }
	//_hoops_SAGGI <_hoops_GPGGI _hoops_SAAAR> 	_hoops_PPGGI _hoops_CICC _hoops_HPGGI::_hoops_SIRRR!= (_hoops_SAAAR _hoops_RCIC & _hoops_SGS) _hoops_RCIC { _hoops_ASRC _hoops_SGS != _hoops_IRAP; }
#endif

namespace _hoops_IPGGI {
	template<class _hoops_PRSHH> struct _hoops_CPGGI							{	enum { result = 0 };	};
	template<> struct _hoops_CPGGI <float>							{	enum { result = 1 };	};
	template<> struct _hoops_CPGGI <double>						{	enum { result = 1 };	};
	template<> struct _hoops_CPGGI <long double>					{	enum { result = 1 };	};

	template <class _hoops_PRSHH> struct _hoops_SPGGI						{	enum { result = 0 };	};
	template <class _hoops_PRSHH> struct _hoops_SPGGI <_hoops_PRSHH *>					{	enum { result = 1 };	};
	template <class _hoops_PRSHH, class _hoops_GHGGI> struct _hoops_SPGGI <_hoops_PRSHH _hoops_GHGGI::*>		{	enum { result = 1 };	};

	template<class _hoops_PRSHH> struct _hoops_RHGGI							{	enum { result = 0 };	};
	template<> struct _hoops_RHGGI <int>								{	enum { result = 1 };	};
	template<> struct _hoops_RHGGI <unsigned int>					{	enum { result = 1 };	};
	template<> struct _hoops_RHGGI <long int>						{	enum { result = 1 };	};
	template<> struct _hoops_RHGGI <unsigned long int>				{	enum { result = 1 };	};
	template<> struct _hoops_RHGGI <short int>						{	enum { result = 1 };	};
	template<> struct _hoops_RHGGI <unsigned short int>				{	enum { result = 1 };	};
	template<> struct _hoops_RHGGI <char>							{	enum { result = 1 };	};
	template<> struct _hoops_RHGGI <signed char>						{	enum { result = 1 };	};
	template<> struct _hoops_RHGGI <unsigned char>					{	enum { result = 1 };	};
	template<> struct _hoops_RHGGI <bool>							{	enum { result = 1 };	};
	template<> struct _hoops_RHGGI <wchar_t>							{	enum { result = 1 };	};
}

template <typename T>
class TypeTraits {
	public:
		enum { _hoops_AHGGI	 = _hoops_IPGGI::_hoops_SPGGI<T>::result };
		enum { _hoops_PHGGI		 = _hoops_IPGGI::_hoops_RHGGI<T>::result };
		enum { _hoops_HHGGI		 = _hoops_IPGGI::_hoops_CPGGI<T>::result };
		enum { IsFundamental = _hoops_AHGGI || _hoops_PHGGI || _hoops_HHGGI };
};


/*****************************************************************************/

// _hoops_SGSS _hoops_CIPH
template <typename T>	INLINE	T alter *	_hoops_PGRCA (T const * a)	{ return const_cast<T alter *>(a); }
template <typename T>	INLINE	T alter &	_hoops_PGRCA (T const & a)	{ return const_cast<T alter &>(a); }

template <typename T>	INLINE	T			Abs (T const & a)				{ return  a < 0 ? -a : a; }
template <typename T>	INLINE	int			Sign (T a)						{ return a == 0 ? 0 : a < 0 ? -1 : 1; }
template <typename T>	INLINE	void		Swap (T alter & a, T alter & b)	{ T temp = a; a = b; b = temp; }

template <typename T>	INLINE	T const &	_hoops_AHIA (T const & a, T const & b)	{ return  a < b ? a : b; }
template <typename T>	INLINE	T const &	_hoops_AHIA (T const & a, T const & b, T const & c)	{ return  _hoops_AHIA(_hoops_AHIA(a,b),c); }
template <typename T>	INLINE	T const &	_hoops_AHIA (T const & a, T const & b, T const & c, T const & d) { return _hoops_AHIA(_hoops_AHIA(a, b, c),d); }
template <typename T>	INLINE	T const &	_hoops_AHIA (T const & a, T const & b, T const & c, T const & d, T const & e) { return _hoops_AHIA(_hoops_AHIA(a,b,c,d),e); }
template <typename T>	INLINE	T const &	_hoops_AHIA (T const & a, T const & b, T const & c, T const & d, T const & e, T const & f) { return _hoops_AHIA(_hoops_AHIA(a,b,c,d,e),f); }

template <typename T>	INLINE	T const &	_hoops_IAAA (T const & a, T const & b)	{ return  a > b ? a : b; }
template <typename T>	INLINE	T const &	_hoops_IAAA (T const & a, T const & b, T const & c)	{ return  _hoops_IAAA(_hoops_IAAA(a,b),c); }
template <typename T>	INLINE	T const &	_hoops_IAAA (T const & a, T const & b, T const & c, T const & d) { return _hoops_IAAA(_hoops_IAAA(a, b, c),d); }
template <typename T>	INLINE	T const &	_hoops_IAAA (T const & a, T const & b, T const & c, T const & d, T const & e) { return _hoops_IAAA(_hoops_IAAA(a,b,c,d),e); }
template <typename T>	INLINE	T const &	_hoops_IAAA (T const & a, T const & b, T const & c, T const & d, T const & e, T const & f) { return _hoops_IAAA(_hoops_IAAA(a,b,c,d,e),f); }

template <typename T>
INLINE	T	_hoops_SGIHR (T const & a) {
	if (a > 0)
		return sqrt (a);
#ifndef DISABLE_ERROR_WARNING_INFO
	if (a < (T)-1e-20f)
		_hoops_IPR (_hoops_RISSH, _hoops_AISSH,
						 "Attempted square root of a negative number");
#endif
	return 0;
}

/*****************************************************************************/
/* _hoops_ICRP _hoops_GSGR _hoops_PGPP _hoops_PAH _hoops_SHH _hoops_GIR _hoops_GRP _hoops_IHGGI */

/* _hoops_GAAP _hoops_ASSS _hoops_SGH _hoops_IIGR _hoops_IHGGI _hoops_PII _hoops_CHGGI()/_hoops_SHGGI() _hoops_PPR "_hoops_ACHP" _hoops_IRSP,
 * _hoops_HIH _hoops_RRP _hoops_IS _hoops_CACH _hoops_RPP _hoops_SSIA _hoops_HS _hoops_SHGGP "_hoops_GIGGI" _hoops_AHRPA.
 */
#ifndef _hoops_RIGGI
#	define _hoops_RIGGI			!HI_CI_Equal_Strings
#endif
#ifndef _hoops_AIGGI
#	define _hoops_PIGGI(_hoops_HIGGI,_hoops_ISSGH,_m_)	HI_CI_Equal_Strings_To_Max(_hoops_HIGGI,_m_,_hoops_ISSGH)
#	define _hoops_AIGGI			!_hoops_PIGGI
#endif


#define _hoops_SSGR(_hoops_IIGGI)					(int)strlen(_hoops_IIGGI)
#define _hoops_GPASA(_hoops_RHAIH,_hoops_AHAIH)				strcmp(_hoops_RHAIH,_hoops_AHAIH)
#define _hoops_CIGGI(_hoops_RHAIH,_m_,_hoops_AHAIH)	strncmp(_hoops_RHAIH,_hoops_AHAIH,_m_)
#define _hoops_AGGR(_hoops_RHAIH,_hoops_AHAIH)				(!strcmp(_hoops_RHAIH,_hoops_AHAIH))
#define _hoops_GPPSA(_hoops_RHAIH,_m_,_hoops_AHAIH)	(!strncmp(_hoops_RHAIH,_hoops_AHAIH,_m_))
#define _hoops_IGGPA(_hoops_RHAIH,_hoops_AHAIH)				(!_hoops_RIGGI(_hoops_RHAIH,_hoops_AHAIH))
#define _hoops_GIIPP(_hoops_RHAIH,_hoops_AHAIH,_m_) (!_hoops_AIGGI(_hoops_RHAIH,_hoops_AHAIH,_m_))
/* _hoops_SIGGI() _hoops_PII _hoops_GCGGI(), _hoops_HIH _hoops_ASSP'_hoops_RA _hoops_RRP _hoops_HCGC _hoops_IH _hoops_IRAP _hoops_RCPHR */
#define EQUAL_MEMORY(_hoops_RHAIH,_m_,_hoops_AHAIH)				(!memcmp(_hoops_RHAIH,_hoops_AHAIH,_m_))
#define _hoops_PAGH(_hoops_RHAIH,_m_,_hoops_AHAIH)			memcmp(_hoops_RHAIH,_hoops_AHAIH,_m_)

#define _hoops_AAHR(_hoops_RCGGI,_hoops_ACGGI)					strcpy(_hoops_ACGGI,_hoops_RCGGI)
#define _hoops_RAHR(_hoops_RCGGI,_m_,_hoops_ACGGI)		(strncpy(_hoops_ACGGI,_hoops_RCGGI,_m_), _hoops_ACGGI[_m_ - 1] = '\0')
#define _hoops_HPRPR(_hoops_RCGGI,_hoops_ACGGI)				strcat(_hoops_ACGGI,_hoops_RCGGI)
#define _hoops_PCGGI(_hoops_RCGGI,_m_,_hoops_ACGGI)	strncat(_hoops_ACGGI,_hoops_RCGGI,_m_)

#define _hoops_HCGGI(_hoops_ICGGI,_hoops_IIGGI)		strchr(_hoops_IIGGI,_hoops_ICGGI)
#define _hoops_CCGGI(_hoops_ICGGI,_hoops_IIGGI)		strrchr(_hoops_IIGGI,_hoops_ICGGI)
#define _hoops_CISGH(_hoops_SCGGI,_hoops_GSGGI)	strstr(_hoops_GSGGI,_hoops_SCGGI)
#define _hoops_RSGGI(_hoops_ASGGI,_hoops_IIGGI)				HI_Last_Substring_In_String(_hoops_ASGGI,_hoops_IIGGI)
#define _hoops_PSGGI(_hoops_SCGGI,_hoops_GSGGI)	HI_CI_First_Substring_In_String(_hoops_SCGGI,_hoops_GSGGI)
#define _hoops_HSGGI(_hoops_ASGGI,_hoops_IIGGI)			HI_CI_Last_Substring_In_String(_hoops_ASGGI,_hoops_IIGGI)

/* _hoops_CSCS _hoops_PPGS _hoops_CCCH & _hoops_RGSR */

#ifndef COPY_MEMORY
#	define		COPY_MEMORY(_hoops_SPAIH, _hoops_IPAIH, _dst_)	memcpy(_dst_, _hoops_SPAIH, _hoops_IPAIH)
#endif
#define	_hoops_RSAI(_hoops_SPAIH, _type_, _dst_)			COPY_MEMORY (_hoops_SPAIH, sizeof(_type_), _dst_)
#define	_hoops_AIGA(_hoops_SPAIH, _cnt_, _type_, _dst_)		COPY_MEMORY (_hoops_SPAIH, (_cnt_) * sizeof(_type_), _dst_)

#define _hoops_APRGA(_hoops_SPAIH, _cnt_, _type_, _dst_) do { \
	void* _hoops_ISGGI = (void*)_hoops_SPAIH; \
	if (_cnt_ <= 0 || _hoops_SPAIH == null) { \
		_dst_ = null; \
		break; \
	} \
	ALLOC_ARRAY(_dst_, _cnt_, _type_); \
	_hoops_AIGA(_hoops_ISGGI, _cnt_, _type_, _dst_); \
	} while (0)

#define _hoops_HAHSA(_hoops_SPAIH, _cnt_, _type_, _dst_, _pool_) do { \
	void* _hoops_ISGGI = (void*)_hoops_SPAIH; \
	if (_cnt_ <= 0 || _hoops_SPAIH == null) { \
		_dst_ = null; \
		break; \
	} \
	POOL_ALLOC_ARRAY(_dst_, _cnt_, _type_, _pool_); \
	_hoops_AIGA(_hoops_ISGGI, _cnt_, _type_, _dst_); \
	} while (0)

#define _hoops_GGIPR(_hoops_SPAIH, _cnt_, _type_, _dst_) do { \
	void* _hoops_ISGGI = (void*)_hoops_SPAIH; \
	if (_cnt_ <= 0 || _hoops_SPAIH == null) { \
		_dst_ = null; \
		break; \
	} \
	ALLOC_ARRAY_CACHED(_dst_, _cnt_, _type_); \
	_hoops_AIGA(_hoops_ISGGI, _cnt_, _type_, _dst_); \
	} while (0)

#define _hoops_CHRSH(_hoops_SPAIH, _cnt_, _type_, _dst_, _pool_) do { \
	void* _hoops_ISGGI = (void*)_hoops_SPAIH; \
	if (_cnt_ <= 0 || _hoops_SPAIH == null) { \
		_dst_ = null; \
		break; \
	} \
	POOL_ALLOC_ARRAY_CACHED(_dst_, _cnt_, _type_, _pool_); \
	_hoops_AIGA(_hoops_ISGGI, _cnt_, _type_, _dst_); \
	} while (0)

#ifndef SET_MEMORY
#	define		SET_MEMORY(_dst_, _hoops_IPAIH, _hoops_CPAIH)		memset(_dst_, _hoops_CPAIH, _hoops_IPAIH)
#endif
#define	ZERO_STRUCT(_dst_, _type_)					SET_MEMORY (_dst_, sizeof(_type_), 0)
#define	ZERO_ARRAY(_dst_, _cnt_, _type_)			SET_MEMORY (_dst_, (_cnt_) * sizeof(_type_), 0)


/* _hoops_PPCAR _hoops_CSGGI/_hoops_IASPA _hoops_PGPP */



#ifndef _hoops_RICH
#	define		_hoops_RICH(_hoops_CPAIH,_hoops_CICSH,_hoops_SSGGI)		HI_SinCos (_hoops_CPAIH, &_hoops_CICSH, &_hoops_SSGGI)
#endif

#ifndef COS
#	define		COS(_hoops_CPAIH)				HI_Cos(_hoops_CPAIH)
#endif

#ifndef _hoops_ISSSR
#	define		_hoops_ISSSR(_hoops_CPAIH)												\
						((_hoops_CPAIH > 1.0f) ? 0.0f :						\
						 (_hoops_CPAIH < -1.0f) ? 180.0f :						\
						 RADIANS_TO_DEGREES ((float)acos(_hoops_CPAIH)))
#	define		_hoops_GGRGI
#endif

#ifndef _hoops_AGGGA
#	define		_hoops_AGGGA(_yy_, _xx_)										\
						((_xx_ == 0.0f && _yy_ == 0.0f) ? 0.0f :		\
						 RADIANS_TO_DEGREES((float)atan2(_yy_, _xx_)))
#	define		_hoops_RGRGI
#endif


/* "_hoops_CAGRH" _hoops_GGR _hoops_RISCP _hoops_HIRPR _hoops_IRAGP */
#ifdef AIX_SYSTEM
#  ifdef index
#	  undef index  /* _hoops_HIS '_hoops_CIHA' _hoops_PAH _hoops_SHH _hoops_IGI _hoops_GAR _hoops_IRS _hoops_PSGR _hoops_RSIRR _hoops_GGR _hoops_AGRGI */
#  endif
#endif

/*****************************************************************************/



/* _hoops_GGHSA _hoops_IHRPR _hoops_PGRGI _hoops_HGRGI */

extern "C" {
	// _hoops_CHPPR _hoops_API _hoops_CICRR (_hoops_IH _hoops_IGRGI _hoops_CGRGI _hoops_CAPGR _hoops_PRSAR)
	typedef void (HC_CDECL * _hoops_IRPCR) (_hoops_SCSSH);
	typedef int (HC_CDECL * _hoops_SGRGI) (_hoops_SCSSH);

	typedef	void (HC_CDECL * _hoops_IGGHP) (void);

	typedef	void (HC_CDECL * _hoops_SGGHP) (Key);

	typedef	void * (HC_CDECL * _hoops_CHSPP) (size_t);
	typedef	void (HC_CDECL * _hoops_GISPP) (void *);

	// _hoops_GRRGI _hoops_RRP _hoops_GRAA-_hoops_RRRGI _hoops_RPPCR (_hoops_IH _hoops_AAHAR _hoops_ARRGI)
	typedef bool (HC_CDECL * Driver_Action) (_hoops_AIGPR * _hoops_RIGC, _hoops_GGAGR *driver, int request, void * request_info);

	typedef void (HC_CDECL * _hoops_SPSAP) (void);

	typedef void (HC_CDECL * _hoops_GHSAP)
		(int category, int specific, int severity,
		int msgc, char const * const * msgv,
		int _hoops_PRRGI, char const * const * _hoops_HRRGI);
}

// _hoops_IRRGI _hoops_ARRGI _hoops_PCAAA
typedef Driver_Action (HC_CDECL * _hoops_CRRGI)(char const *_hoops_HSS);


typedef void (HC_CDECL * _hoops_CRRHH) (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP alter *			_hoops_SRCP,
	void alter *			info);

typedef Key (HC_CDECL * _hoops_CICIH) (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				segment,
	_hoops_CRCP *				owner,
	Subsegment **			backlink,
	Subsegment *			_hoops_SRRGI,
	_hoops_HCRPR *					name,
	bool					_hoops_PIGSA,
	void *					info);

typedef bool (HC_CDECL * _hoops_RRPHP) (_hoops_AGCI alter *_hoops_AGAGR, void *_hoops_HHCAP);


#	define		_hoops_RHHPP(c)		(c)


/* _hoops_IH _hoops_IGRH _hoops_IIAP, _hoops_CAS _hoops_IHPR/_hoops_RCPP _hoops_CPSA _hoops_SPGA'_hoops_RA _hoops_IRPR */
#define _hoops_IHGPR			0
#define _hoops_GARGI		(-1)

#define MAX_ERRMSG				16530	/* (_hoops_PHI _hoops_IIGR _hoops_HPS) */
#define _hoops_CGHHP			16530	/* (_hoops_PHI _hoops_IIGR _hoops_HPS) */
#define MAX_FLOAT				1e30f
#define _hoops_RARGI			30
#define _hoops_GHAPH			500		/* (_hoops_PHI _hoops_IIGR _hoops_HPS) */
#define _hoops_AARGI				0x7F	/* _hoops_AASC _hoops_PARGI _hoops_HCR _hoops_IACAR */
#define _hoops_HARGI				0xFF	/* _hoops_AASC _hoops_PARGI _hoops_HCR _hoops_IACAR */
#define _hoops_IARGI				(short)(((unsigned short)~0L)>>1)
#define _hoops_IICIA					(int)(((unsigned int)~0L)>>1)
#define _hoops_CARGI				(long)(((unsigned long)~0L)>>1)
#define _hoops_GPARA				((unsigned short)~0L)
#define _hoops_SARGI			1e15f



#define _hoops_PSPPR					128
#define _hoops_PAPCR		 64
#define _hoops_GPRGI					 64
#define _hoops_RPRGI			 32
#define _hoops_GSHPP			128
#define _hoops_APRGI					512


struct _hoops_GCIIR {
	_hoops_PIIIR **		table;
	int					size;
	int					count;
};

enum _hoops_PPRGI {
	_hoops_IIACR,
	_hoops_RIPCR,
	_hoops_RAPPP,
	_hoops_HPRGI,
	_hoops_GGPCA,
	_hoops_AAPPP,
	_hoops_PAPPP,
	_hoops_IPRGI,
	_hoops_HAPPP,
	_hoops_IAPPP,
	_hoops_CAPPP,
	_hoops_CPRGI,
	_hoops_SAPPP,
	_hoops_CPPPP,
	_hoops_CPSAA,
	_hoops_SPRGI,

	_hoops_GHRGI,
	_hoops_RHRGI,
	_hoops_RHHPA,
	_hoops_ISCSA,
	_hoops_AHRGI,
	_hoops_PHRGI,
	_hoops_HHRGI,
	_hoops_IHRGI,
	_hoops_CPCHH,
	_hoops_IHCHH,
	_hoops_CHRGI,

	_hoops_HIIPP,
	_hoops_SHRGI,
	_hoops_GIRGI,
	_hoops_RIRGI,
	_hoops_AIRGI,
	_hoops_ACSPP,

	_hoops_HPSAA,
	_hoops_SRPPP,
	_hoops_PPPPP,
	_hoops_GRRHA,
	_hoops_PIRGI,
	_hoops_HCCCA,

	_hoops_RIGAA,
	_hoops_SHSIA,
	_hoops_HIRGI,
	_hoops_SRCHA,
 	_hoops_HRSIA,
	_hoops_GHRCA,
	_hoops_IIRGI,
	_hoops_GCCHA,
	_hoops_HHAGA,
	_hoops_SRPCA,
	_hoops_CIRGI
};




#ifndef FLOOR
# define FLOOR(a)		(((a) > 0.0f || (float)(int)(a) == (a)) ? (int)(a) : ((int)(a) - 1))
#endif
#ifndef CEILING
# define CEILING(a)		(((a) < 0.0f || (float)(int)(a) == (a)) ? (int)(a) : ((int)(a) + 1))
#endif
#define BIT(v, mask)	(((v) & (mask)) != 0)
#define _hoops_SAAIP(c)		(((int)(char)-1 == -1) ? \
								 (int)(char)(c) : \
								 (_hoops_IRGCR(c) & 0x80) ? \
								  _hoops_IRGCR(c) - 256 : \
								 _hoops_IRGCR(c))
#define _hoops_IRGCR(c)	(((int)(unsigned char)0xFF == 0xFF) ? \
						 (int)(unsigned char)(c) : (0xFF & (int)(c)))
#define _hoops_SIRGI(c)	(((long)(unsigned char)0xFF == 0xFF) ? \
						 (long)(unsigned char)(c) : (0xFF & (long)(c)))
#define _hoops_SHPCR(c)	HOOPS_READ_ONLY._hoops_GCRGI[_hoops_IRGCR(c)]
#define ALLBITS(v, mask) (((v) & (mask)) == (mask))
#define ANYBIT(v, mask) (((v) & (mask)) != 0)
#define _hoops_RIII(v)		((long)(v) & -(long)(v))

#define _hoops_RAHSR(a,b)						\
				((a).length == (b).length && ((a).length == 0 || \
				 EQUAL_MEMORY ((a).text, (a).length, (b).text)))
#define _hoops_RARPH(a,b)						\
				((a).length == (b).length && ((a).length == 0 || \
				 EQUAL_MEMORY ((a)._hoops_IPPPP, (a).length*sizeof(Karacter), (b)._hoops_IPPPP)))



#define _hoops_AAISA()		(HOOPS_WORLD->_hoops_RCRGI *= (int)69069, ++HOOPS_WORLD->_hoops_RCRGI)
#define URANDOM()		((unsigned int)_hoops_AAISA())

#define _hoops_GHIA(x) do {x} while (0)	/* (';' _hoops_IGRIP _hoops_GPP _hoops_AHAR) */

/* _hoops_HHH _hoops_AARRH/_hoops_HRP _hoops_HPPPR _hoops_RPP _hoops_RIGR _hoops_PRSAR _hoops_CHR _hoops_PPRAR,
 * _hoops_RH _hoops_HSPR _hoops_IIGS _hoops_IRS _hoops_AGSR _hoops_IIGR _hoops_CPIRA _hoops_SGS _hoops_RH _hoops_ACRGI _hoops_HRGR
 * "_hoops_PSHS" _hoops_SIHH _hoops_PPAP _hoops_AGI _hoops_HGPP _hoops_GAR _hoops_PCRGI _hoops_API _hoops_HCPH
 */
#define _hoops_GRSSH(x)	do if (0 && (x)) {UNREFERENCED(x);} while (0)


#ifdef DISABLE_CODE_GENERATION
#	define CODE_GENERATION(_hoops_PCGIH) do {} while (0)
#else
#	define CODE_GENERATION(_hoops_PCGIH)									\
	do if (BIT (HOOPS_WORLD->system_flags, _hoops_IGHGA)) {				\
		_hoops_AIGPR *_thread_data_;							\
		_hoops_HCRGI (_thread_data_);								\
		if (_thread_data_->_hoops_CACAA ==						\
						_thread_data_->_hoops_SACAA) {			\
			_hoops_CAAI (HOOPS_WORLD->_hoops_ICRGI);				\
			{ _hoops_PCGIH }												\
			if (HOOPS_WORLD->_hoops_CGHGA > HOOPS_WORLD->_hoops_CCRGI)				\
				HI_Chain_Code_Files ();									\
			_hoops_APAI (HOOPS_WORLD->_hoops_ICRGI);			\
		}																\
	} while (0)
#endif



#define _hoops_CAAI(x)											\
			do {												\
				if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))	\
					LOCK_MUTEX (x);								\
			} while (0)
#define _hoops_APAI(x)										\
			do {												\
				if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))	\
					UNLOCK_MUTEX (x);							\
			} while (0)

#define _hoops_SCRGI(x)											\
			do {												\
				if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))	\
					READ_LOCK (x);								\
			} while (0)


#define _hoops_GSRGI(x, thread_id)							\
			do {												\
				if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))	\
					SHARE_READ_LOCK (x, thread_id);				\
			} while (0)

// _hoops_HRS _hoops_IHPR _hoops_RPP _hoops_AAHS _hoops_PCIAH _hoops_SSPP, _hoops_CSAP _hoops_AIAH _hoops_GGI _hoops_PCPAR, _hoops_PAR _hoops_IGIRR _hoops_RSRGI _hoops_HII _hoops_IRS _hoops_IRIGR _hoops_AAHS
// _hoops_RPP '_hoops_PCCIR' _hoops_HRGR _hoops_RCPP, _hoops_RHAP _hoops_HAR _hoops_GRRAR (_hoops_IPPRH) _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_ICIC
#define _hoops_ASRGI(x,r)										\
			((BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))		\
				? WRITE_LOCK (x,r) : 1)
// _hoops_RGAR "_hoops_ISHS" _hoops_RPP _hoops_PSRGI _hoops_HII _hoops_IRS _hoops_GGI _hoops_IS _hoops_IRS _hoops_IRIGR _hoops_IIS'_hoops_GRI _hoops_HPIH _hoops_HSRGI _hoops_PHHR _hoops_SRS
#define _hoops_ISRGI(x)										\
			((BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))		\
				? UNLOCK_LOCK (x) : 1)

#define _hoops_CSRGI(x)											\
			((BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))		\
				? HI_Check_Lock	(x,__FILE__,__LINE__) : HM_LOCK_STATE_READ|HM_LOCK_STATE_WRITE)


#define _hoops_CSPPR()		_hoops_SCRGI(HOOPS_WORLD->_hoops_SSRGI)
#define _hoops_GGAGI(thread_id) _hoops_GSRGI(HOOPS_WORLD->_hoops_SSRGI, thread_id)
#define _hoops_RPPPR()		(_hoops_ASRGI(HOOPS_WORLD->_hoops_SSRGI, 1) != 0)
#define _hoops_GSGPR()	(_hoops_ASRGI(HOOPS_WORLD->_hoops_SSRGI, 0) != 0)
#define _hoops_IRRPR()	(_hoops_ISRGI(HOOPS_WORLD->_hoops_SSRGI) != 0)
#define _hoops_RGAGI()		_hoops_CSRGI(HOOPS_WORLD->_hoops_SSRGI)

#ifdef HOOPS_DEBUG_BUILD
#define _hoops_RSIIR(_hoops_RSPGP) \
	do { \
		UNREFERENCED(_hoops_RSPGP); \
		if (!ANYBIT(_hoops_RGAGI(), HM_LOCK_STATE_READ|HM_LOCK_STATE_WRITE)) \
			ASSERT(0); \
	} while (0)
#else
#define _hoops_RSIIR(_hoops_RSPGP) _hoops_GRSSH(_hoops_RSPGP)
#endif

#ifdef HOOPS_DEBUG_BUILD
#define _hoops_ICIIR(_hoops_RSPGP) \
	do { \
		if (BIT ((_hoops_RSPGP)->flags, _hoops_PGPSA)) { \
			if (!BIT(_hoops_RGAGI(), HM_LOCK_STATE_READ)) \
				ASSERT(0); \
		}else if (!BIT(_hoops_RGAGI(), HM_LOCK_STATE_WRITE)) \
			ASSERT(0); \
	} while (0)
#else
#define _hoops_ICIIR(_hoops_RSPGP) _hoops_GRSSH(_hoops_RSPGP)
#endif

typedef unsigned short		_hoops_GARSR;
typedef float				_hoops_ACGHR;

typedef Integer32			_hoops_ACHR;
typedef Integer32			_hoops_CGSP;
typedef Integer32			Activity;
typedef Integer32			_hoops_PSPGP;
typedef int					Button;
typedef Integer32			_hoops_SSIC;
typedef char				_hoops_GIGRP;

typedef Integer32			_hoops_APSHA;	 /* _hoops_PAPR _hoops_GASAR _hoops_GGR "_hoops_IPHIA._hoops_GGHR" */


typedef unsigned Integer32 	_hoops_GHRIR;			/* _hoops_IGI _hoops_IH _hoops_AARPR _hoops_AGSAR */
typedef unsigned Integer32 	_hoops_PHASP;	/* _hoops_IH _hoops_PA _hoops_SHS */



#ifndef _hoops_AGAGI
#  define _hoops_PGAGI(ref)  ((ref)->_hoops_HSAI > 1)
#else
#  define _hoops_PGAGI(ref)  true
#endif



struct XY {
	float				x, y;
};



struct Vector;

struct HOOPS_API Point {

	float			x, y, z;

	Point () {}
	Point (float _hoops_ISPI, float _hoops_CSPI, float _hoops_SSPI) : x (_hoops_ISPI), y (_hoops_CSPI), z (_hoops_SSPI) {}

	bool			operator== (Point const & p) const	{ return  x == p.x && y == p.y && z == p.z; }
	bool			operator!= (Point const & p) const	{ return  !(*this == p); }

	Point &			operator*= (float s) alter	{ x *= s; y *= s; z *= s;  return *this; }
	Point &			operator/= (float s) alter	{ return operator*= (1.0f / s); }
	Point const		operator* (float s) const	{ return Point (x * s, y * s, z * s); }
	Point const		operator/ (float s) const	{ return operator* (1.0f / s); }

	Point &			operator+= (Vector const & v) alter;
	Point &			operator-= (Vector const & v) alter;

	Vector const	operator- (Point const & p) const;

	Point const		operator+ (Vector const & v) const;
	Point const		operator- (Vector const & v) const;
};

namespace _hoops_HPCH {
		extern HOOPS_API	Point const	_hoops_IPCH;
}

typedef	Point	DC_Point;	// _hoops_HAGH _hoops_RSIRR _hoops_HRGR _hoops_SAHR _hoops_IRS _hoops_AISIP _hoops_IIGR _hoops_RH _hoops_ISRR _hoops_GC

INLINE Point operator* (float s, Point const & a) { return Point (s*a.x, s*a.y, s*a.z); }

INLINE Point _hoops_AICIR (Point const & a, Point const & b) {
	return Point (0.5f*(a.x+b.x), 0.5f*(a.y+b.y), 0.5f*(a.z+b.z));
}

struct _hoops_PPCIR;

struct _hoops_APCIR {

	double			x, y, z;

	_hoops_APCIR () {}
	_hoops_APCIR (Point const & _hoops_HACIR) : x (_hoops_HACIR.x), y (_hoops_HACIR.y), z (_hoops_HACIR.z) {}
	_hoops_APCIR (float _hoops_ISPI, float _hoops_CSPI, float _hoops_SSPI) : x (_hoops_ISPI), y (_hoops_CSPI), z (_hoops_SSPI) {}
	_hoops_APCIR (double _hoops_ISPI, double _hoops_CSPI, double _hoops_SSPI) : x (_hoops_ISPI), y (_hoops_CSPI), z (_hoops_SSPI) {}

	bool			operator== (_hoops_APCIR const & p) const	{ return  x == p.x && y == p.y && z == p.z; }
	bool			operator!= (_hoops_APCIR const & p) const	{ return  !(*this == p); }

	_hoops_APCIR &		operator*= (double s) alter	{ x *= s; y *= s; z *= s;  return *this; }
	_hoops_APCIR &		operator/= (double s) alter	{ return operator*= (1.0 / s); }
	_hoops_APCIR const	operator* (double s) const	{ return _hoops_APCIR (x * s, y * s, z * s); }
	_hoops_APCIR const	operator/ (double s) const	{ return operator* (1.0 / s); }

	_hoops_APCIR &		operator+= (_hoops_PPCIR const & v) alter;
	_hoops_APCIR &		operator-= (_hoops_PPCIR const & v) alter;

	_hoops_PPCIR const	operator- (_hoops_APCIR const & p) const;

	_hoops_APCIR const	operator+ (_hoops_PPCIR const & v) const;
	_hoops_APCIR const	operator- (_hoops_PPCIR const & v) const;
};

namespace _hoops_HGAGI {
	extern HOOPS_API	_hoops_APCIR const	_hoops_IPCH;
}

INLINE _hoops_APCIR operator* (double s, _hoops_APCIR const & a) { return _hoops_APCIR (s*a.x, s*a.y, s*a.z); }

INLINE _hoops_APCIR _hoops_AICIR (_hoops_APCIR const & a, _hoops_APCIR const & b) {
	return _hoops_APCIR (0.5*(a.x+b.x), 0.5*(a.y+b.y), 0.5*(a.z+b.z));
}


struct Vector {

	float			x, y, z;

	Vector () {}
	Vector (float _hoops_ISPI, float _hoops_CSPI, float _hoops_SSPI) : x (_hoops_ISPI), y (_hoops_CSPI), z (_hoops_SSPI) {}

	Vector const	operator- () const						{ return Vector (-x, -y, -z); }

	bool			operator== (Vector const & v) const		{ return  x == v.x && y == v.y && z == v.z; }
	bool			operator!= (Vector const & v) const		{ return  !(*this == v); }

	Vector &		operator+= (Vector const & v) alter		{ x += v.x; y += v.y; z += v.z;  return *this; }
	Vector &		operator-= (Vector const & v) alter		{ x -= v.x; y -= v.y; z -= v.z;  return *this; }
	Vector const	operator+ (Vector const & v) const		{ return Vector (x + v.x, y + v.y, z + v.z); }
	Vector const	operator- (Vector const & v) const		{ return Vector (x - v.x, y - v.y, z - v.z); }

	Vector &		operator*= (float s) alter				{ x *= s; y *= s; z *= s;  return *this; }
	Vector &		operator/= (float s) alter				{ return operator*= (1.0f / s); }
	Vector const	operator* (float s) const				{ return Vector (x * s, y * s, z * s); }
	Vector const	operator/ (float s) const				{ return operator* (1.0f / s); }

	float			length () const { return sqrt (x*x + y*y + z*z); }

	float			_hoops_PPSSR () const { return x*x + y*y + z*z; }

	Vector &		_hoops_AAIAR () alter {		// _hoops_HAR _hoops_RCIC &; _hoops_ASSS _hoops_RRGGR._hoops_HPGIR() *= _hoops_IISGA;
						float len = length();
						if (len > 1.0E-20f)
							operator/= (len);
						return *this;
					}

	float			_hoops_SSRP (Vector const & v) const { return x * v.x  +  y * v.y  +  z * v.z; }

	Vector const	_hoops_SAIAR (Vector const & v) const {
						return Vector (y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
					}
};
namespace _hoops_IRGA {
		extern HOOPS_API	Vector const		X_Axis;
		extern HOOPS_API	Vector const		_hoops_RCPCR;
		extern HOOPS_API	Vector const		_hoops_IGHH;
		extern HOOPS_API	Vector const		_hoops_CRGA;
}

INLINE	Vector const	operator* (float s, Vector const & v) { return Vector (s * v.x, s * v.y, s * v.z); }


INLINE	Point &			Point::operator+= (Vector const & v) alter	{ x += v.x; y += v.y; z += v.z;  return *this; }
INLINE	Point &			Point::operator-= (Vector const & v) alter	{ x -= v.x; y -= v.y; z -= v.z;  return *this; }

INLINE	Vector const	Point::operator- (Point const & p) const	{ return Vector (x - p.x, y - p.y, z - p.z); }

INLINE	Point const		Point::operator+ (Vector const & v) const	{ return Point  (x + v.x, y + v.y, z + v.z); }
INLINE	Point const		Point::operator- (Vector const & v) const	{ return Point  (x - v.x, y - v.y, z - v.z); }


INLINE	float _hoops_SRCIR(Point const & p1, Point const & p2)
{
	return (p2 - p1).length();
}



struct _hoops_PPCIR {

	double			x, y, z;

	_hoops_PPCIR () {}
	_hoops_PPCIR (float _hoops_ISPI, float _hoops_CSPI, float _hoops_SSPI) : x (_hoops_ISPI), y (_hoops_CSPI), z (_hoops_SSPI) {}
	_hoops_PPCIR (Vector const & _hoops_HACIR) : x (_hoops_HACIR.x), y (_hoops_HACIR.y), z (_hoops_HACIR.z) {}
	_hoops_PPCIR (double _hoops_ISPI, double _hoops_CSPI, double _hoops_SSPI) : x (_hoops_ISPI), y (_hoops_CSPI), z (_hoops_SSPI) {}

	_hoops_PPCIR const	operator- () const						{ return _hoops_PPCIR (-x, -y, -z); }

	bool			operator== (_hoops_PPCIR const & v) const	{ return  x == v.x && y == v.y && z == v.z; }
	bool			operator!= (_hoops_PPCIR const & v) const	{ return  !(*this == v); }

	_hoops_PPCIR &		operator+= (_hoops_PPCIR const & v) alter	{ x += v.x; y += v.y; z += v.z;  return *this; }
	_hoops_PPCIR &		operator-= (_hoops_PPCIR const & v) alter	{ x -= v.x; y -= v.y; z -= v.z;  return *this; }
	_hoops_PPCIR const	operator+ (_hoops_PPCIR const & v) const		{ return _hoops_PPCIR (x + v.x, y + v.y, z + v.z); }
	_hoops_PPCIR const	operator- (_hoops_PPCIR const & v) const		{ return _hoops_PPCIR (x - v.x, y - v.y, z - v.z); }

	_hoops_PPCIR &		operator*= (float s) alter				{ x *= s; y *= s; z *= s;  return *this; }
	_hoops_PPCIR &		operator/= (float s) alter				{ return operator*= (1.0 / s); }
	_hoops_PPCIR const	operator* (float s) const				{ return _hoops_PPCIR (x * s, y * s, z * s); }
	_hoops_PPCIR const	operator/ (float s) const				{ return operator* (1.0 / s); }

	double			length () const { return sqrt (x*x + y*y + z*z); }

	double			_hoops_PPSSR () const { return x*x + y*y + z*z; }

	_hoops_PPCIR &		_hoops_AAIAR () alter {		// _hoops_HAR _hoops_RCIC &; _hoops_ASSS _hoops_RRGGR._hoops_HPGIR() *= _hoops_IISGA;
		double len = length();
		if (len > 1.0E-20)
			operator/= (len);
		return *this;
	}

#if 0
	/* _hoops_IGAGI _hoops_IRS _hoops_AAGA */
	local bool _hoops_CGAGI (_hoops_SGAGI *in, _hoops_SGAGI *_hoops_GIHI) {
		double _hoops_GRAGI, _hoops_RRAGI, _hoops_ARAGI, length;
		_hoops_GIHI->x = in->x;
		_hoops_GIHI->y = in->y;
		_hoops_GIHI->z = in->z;
		if (_hoops_GIHI->x >= 0) 
			_hoops_GRAGI = _hoops_GIHI->x;
		else 
			_hoops_GRAGI = -_hoops_GIHI->x;
		if (_hoops_GIHI->y >= 0) 
			_hoops_RRAGI = _hoops_GIHI->y;
		else 
			_hoops_RRAGI = -_hoops_GIHI->y;
		if (_hoops_GIHI->z >= 0) 
			_hoops_ARAGI = _hoops_GIHI->z;
		else 
			_hoops_ARAGI = -_hoops_GIHI->z;

		length = _hoops_GRAGI * _hoops_GRAGI  +  _hoops_RRAGI * _hoops_RRAGI  +  _hoops_ARAGI * _hoops_ARAGI;

		if (length == 0)
			return false;

		length = ((double)1.0) / (double)sqrt (length);

		_hoops_GIHI->x *= length;
		_hoops_GIHI->y *= length;
		_hoops_GIHI->z *= length;
		return true;
	}
#endif

	double			_hoops_SSRP (_hoops_PPCIR const & v) const { return x * v.x  +  y * v.y  +  z * v.z; }

	_hoops_PPCIR const	_hoops_SAIAR (_hoops_PPCIR const & v) const {
		return _hoops_PPCIR (y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

namespace _hoops_GPIRA {
	extern HOOPS_API	_hoops_PPCIR const		X_Axis;
	extern HOOPS_API	_hoops_PPCIR const		_hoops_RCPCR;
	extern HOOPS_API	_hoops_PPCIR const		_hoops_IGHH;
	extern HOOPS_API	_hoops_PPCIR const		_hoops_CRGA;
}

INLINE	_hoops_PPCIR const	operator* (double s, _hoops_PPCIR const & v) { return _hoops_PPCIR (s * v.x, s * v.y, s * v.z); }


INLINE	_hoops_APCIR &		_hoops_APCIR::operator+= (_hoops_PPCIR const & v) alter	{ x += v.x; y += v.y; z += v.z;  return *this; }
INLINE	_hoops_APCIR &		_hoops_APCIR::operator-= (_hoops_PPCIR const & v) alter	{ x -= v.x; y -= v.y; z -= v.z;  return *this; }

INLINE	_hoops_PPCIR const	_hoops_APCIR::operator- (_hoops_APCIR const & p) const	{ return _hoops_PPCIR (x - p.x, y - p.y, z - p.z); }

INLINE	_hoops_APCIR const	_hoops_APCIR::operator+ (_hoops_PPCIR const & v) const	{ return _hoops_APCIR  (x + v.x, y + v.y, z + v.z); }
INLINE	_hoops_APCIR const	_hoops_APCIR::operator- (_hoops_PPCIR const & v) const	{ return _hoops_APCIR  (x - v.x, y - v.y, z - v.z); }


INLINE	double _hoops_SRCIR(_hoops_APCIR const & p1, _hoops_APCIR const & p2)
{
	return (p2 - p1).length();
}


struct _hoops_ARPA {
	float		a, b, c, d;

	_hoops_ARPA () {}
	_hoops_ARPA (float _hoops_ISPI, float _hoops_CSPI, float _hoops_SSPI, float _hoops_SGHI) : a (_hoops_ISPI), b (_hoops_CSPI), c (_hoops_SSPI), d (_hoops_SGHI) {}
	_hoops_ARPA (Vector const & v, float f) : a (v.x), b (v.y), c (v.z), d (f) {}
	_hoops_ARPA (Vector const & v, Point const & p) :
				a (v.x), b (v.y), c (v.z), d (-(p.x * v.x + p.y * v.y + p.z * v.z)) {}
	_hoops_ARPA (Point const & p, Vector const & v) :
				a (v.x), b (v.y), c (v.z), d (-(p.x * v.x + p.y * v.y + p.z * v.z)) {}

	_hoops_ARPA const		operator- () const						{ return _hoops_ARPA (-a, -b, -c, -d); }

	bool			operator== (_hoops_ARPA const & p) const		{ return  a == p.a && b == p.b && c == p.c && d == p.d; }
	bool			operator!= (_hoops_ARPA const & p) const		{ return  !(*this == p); }

	operator Vector () const								{ return Vector (a, b, c); }

	_hoops_ARPA &		_hoops_AAIAR () alter {
					float		len = sqrt (a * a + b * b + c * c);
					if (len > 1.0E-20f) {
						float	_hoops_PRAGI = 1.0f / len;
						a *= _hoops_PRAGI;	b *= _hoops_PRAGI;	c *= _hoops_PRAGI;	d *= _hoops_PRAGI;
					}
					return *this;
				}

	Point		_hoops_HRAGI(Point const & p1, Point const & p2, float _hoops_ISCIA = 1e-5f) const {
					float	_hoops_RSS = Abs (a * p1.x + b * p1.y + c * p1.z + d);
					float	_hoops_ASS = Abs (a * p2.x + b * p2.y + c * p2.z + d);

					if (_hoops_RSS >= _hoops_ISCIA) {
						return Point (((_hoops_RSS * p2.x) + (_hoops_ASS * p1.x)) / (_hoops_RSS + _hoops_ASS),
									  ((_hoops_RSS * p2.y) + (_hoops_ASS * p1.y)) / (_hoops_RSS + _hoops_ASS),
									  ((_hoops_RSS * p2.z) + (_hoops_ASS * p1.z)) / (_hoops_RSS + _hoops_ASS));
					}
					else
						return Point(p1);
				}

	Point		_hoops_RIHHA(Point const & p1, Point const & p2) const {
					float	 u = (a * p1.x + b * p1.y + c * p1.z + d) /
									(a * (p1.x - p2.x) + b * (p1.y - p2.y) + c * (p1.z - p2.z));

					return Point(p1.x + u * (p2.x - p1.x), p1.y + u * (p2.y - p1.y), p1.z + u * (p2.z - p1.z));
				}
};

namespace _hoops_CGISA {
		extern HOOPS_API	_hoops_ARPA const		_hoops_CRGA;
}


INLINE	float 	operator* (_hoops_ARPA const & plane, Point const & point)
						{ return plane.a * point.x  +  plane.b * point.y  +  plane.c * point.z  +  plane.d; }
INLINE	float 	operator* (Point const & point, _hoops_ARPA const & plane)
						{ return plane * point; }


struct _hoops_AAIRA {
	double		a, b, c, d;

	_hoops_AAIRA () {}
	_hoops_AAIRA (float _hoops_ISPI, float _hoops_CSPI, float _hoops_SSPI, float _hoops_SGHI) : a (_hoops_ISPI), b (_hoops_CSPI), c (_hoops_SSPI), d (_hoops_SGHI) {}
	_hoops_AAIRA (_hoops_PPCIR const & v, float f) : a (v.x), b (v.y), c (v.z), d (f) {}
	_hoops_AAIRA (_hoops_PPCIR const & v, _hoops_APCIR const & p) :
				a (v.x), b (v.y), c (v.z), d (-(p.x * v.x + p.y * v.y + p.z * v.z)) {}
	_hoops_AAIRA (_hoops_APCIR const & p, _hoops_PPCIR const & v) :
				a (v.x), b (v.y), c (v.z), d (-(p.x * v.x + p.y * v.y + p.z * v.z)) {}

	_hoops_AAIRA const	operator- () const						{ return _hoops_AAIRA (-a, -b, -c, -d); }

	bool			operator== (_hoops_AAIRA const & p) const		{ return  a == p.a && b == p.b && c == p.c && d == p.d; }
	bool			operator!= (_hoops_AAIRA const & p) const		{ return  !(*this == p); }

	operator _hoops_PPCIR () const								{ return _hoops_PPCIR (a, b, c); }

	_hoops_AAIRA &	_hoops_AAIAR () alter {
					double		len = sqrt (a * a + b * b + c * c);
					if (len > 1.0E-20) {
						double	_hoops_PRAGI = 1.0 / len;
						a *= _hoops_PRAGI;	b *= _hoops_PRAGI;	c *= _hoops_PRAGI;	d *= _hoops_PRAGI;
					}
					return *this;
				}

	_hoops_APCIR		_hoops_HRAGI(_hoops_APCIR const & p1, _hoops_APCIR const & p2, float _hoops_ISCIA = 1e-5) const {
					double	_hoops_RSS = Abs (a * p1.x + b * p1.y + c * p1.z + d);
					double	_hoops_ASS = Abs (a * p2.x + b * p2.y + c * p2.z + d);

					if (_hoops_RSS >= _hoops_ISCIA) {
						return _hoops_APCIR (((_hoops_RSS * p2.x) + (_hoops_ASS * p1.x)) / (_hoops_RSS + _hoops_ASS),
									   ((_hoops_RSS * p2.y) + (_hoops_ASS * p1.y)) / (_hoops_RSS + _hoops_ASS),
									   ((_hoops_RSS * p2.z) + (_hoops_ASS * p1.z)) / (_hoops_RSS + _hoops_ASS));
					}
					else
						return _hoops_APCIR(p1);
				}

	_hoops_APCIR		_hoops_RIHHA(_hoops_APCIR const & p1, _hoops_APCIR const & p2) const {
					double	 u = (a * p1.x + b * p1.y + c * p1.z + d) /
									(a * (p1.x - p2.x) + b * (p1.y - p2.y) + c * (p1.z - p2.z));

					return _hoops_APCIR(p1.x + u * (p2.x - p1.x), p1.y + u * (p2.y - p1.y), p1.z + u * (p2.z - p1.z));
				}
};

namespace _hoops_PPIRA {
	extern HOOPS_API	_hoops_AAIRA const		_hoops_CRGA;
}


INLINE	double 	operator* (_hoops_AAIRA const & plane, _hoops_APCIR const & point)
			{ return plane.a * point.x  +  plane.b * point.y  +  plane.c * point.z  +  plane.d; }
INLINE	double 	operator* (_hoops_APCIR const & point, _hoops_AAIRA const & plane)
			{ return plane * point; }



typedef float _hoops_RSSH;

#define COPY_PARAMETER(src, _hoops_PCAP, width) \
		_hoops_AIGA((src), (width), _hoops_RSSH, (_hoops_PCAP))

#define _hoops_HPRSH(src, _hoops_PCAP, width, count) \
		_hoops_AIGA((src), (count)*(width), _hoops_RSSH, (_hoops_PCAP))

#define _hoops_IRAGI(_hoops_PAPH, offset, _hoops_PAGR, width) do { \
		COPY_PARAMETER(&(_hoops_PAPH)[(offset)*(width)], (_hoops_PAGR), width); \
	} while (0)

#define _hoops_CRAGI(param,width) \
		ZERO_ARRAY((param), (width), _hoops_RSSH)

#define _hoops_SRAGI(param,count,width) \
		ZERO_ARRAY((param), (count)*(width), _hoops_RSSH)


typedef unsigned char Test;
#define Test_DISJOINT				(Test)0x00
#define _hoops_GAAGI				(Test)0x01
#define _hoops_RAAGI			(Test)0x02
#define Test_EXTENT					(Test)0x04
#define _hoops_AAAGI		(Test)(_hoops_GAAGI | Test_EXTENT)
#define _hoops_PAAGI	(Test)(_hoops_RAAGI | Test_EXTENT)


typedef unsigned char _hoops_RACIH;
typedef short _hoops_RAPGP;


typedef Integer32	_hoops_HGIAA;

#define _hoops_GACAA		0x0001
#define _hoops_SPIAA				0x0002
#define _hoops_AACAA		0x0004
#define _hoops_CRIAA					0x0008
#define _hoops_ICIAA			0x0010
#define _hoops_GRCAA			0x0020
#define _hoops_RACAA			0x0040
#define _hoops_SRCAA		0x0080
#define _hoops_GISAA		0x0100
#define _hoops_IHIAA				0x0200


#define _hoops_ICHC(_hoops_HAAGI, _hoops_IAAGI, _hoops_CAAGI) do {						\
			if (_hoops_HAAGI > 0) {	_hoops_HAAGI -= (_hoops_CAAGI - 1); _hoops_IAAGI = 1;			}	\
			else {				_hoops_HAAGI /= -(_hoops_CAAGI);	_hoops_IAAGI = _hoops_CAAGI; }	\
		} while (0)

/* _hoops_IRHH _hoops_SCH _hoops_CRS _hoops_PCPP _hoops_HIS _hoops_SGS _hoops_RCSSA _hoops_SAAGI _hoops_CGGHR */
typedef POINTER_SIZED_INT _hoops_GPAGI;

struct _hoops_HCRPR {
	char *				text;
	_hoops_GPAGI			length;
};

struct _hoops_SRHSR {
	char const * const		text;
	_hoops_GPAGI const		length;

	_hoops_SRHSR (char const * s, int l) : text (s), length (l) {}

private:
	_hoops_SRHSR ();
	//_hoops_RPAGI (_hoops_RPAGI _hoops_RCIC &);
	void operator= (_hoops_SRHSR const &);
};

// _hoops_PAGA: _hoops_CAAPA() _hoops_CGH _hoops_SHH _hoops_IGI _hoops_RGAR _hoops_IH _hoops_APAGI _hoops_SRSR _hoops_HCCGR
#define _hoops_GRRCR(s)			_hoops_SRHSR (s, sizeof(s)-1)
#define _hoops_PCGSA			_hoops_SRHSR (null, 0)

struct _hoops_AAPIR {
	_hoops_AAPIR *		next;

	_hoops_HCRPR			name;
	Integer32		key;
};

/* "_hoops_PPAGI" _hoops_CHR _hoops_ICIGP 16-_hoops_IGRH (_hoops_PAR _hoops_RRI) _hoops_HPS. _hoops_CGP _hoops_RH _hoops_AAPA
 * _hoops_RAPSR(_hoops_GRI) _hoops_CHR _hoops_HCR _hoops_HPAGI, _hoops_RH _hoops_GAS _hoops_RRGR _hoops_HRGR _hoops_HSAPH, _hoops_GGR _hoops_RH _hoops_HISAR
 * _hoops_GCSRR. _hoops_CGP _hoops_RH _hoops_AAPA _hoops_GPGH'_hoops_RA _hoops_HCR _hoops_HPAGI, _hoops_PSCR _hoops_SCH'_hoops_GRI _hoops_CPHP _hoops_SHS,
 * _hoops_PSHRR _hoops_IPAGI-16 _hoops_CPAGI, _hoops_HIH _hoops_GAAP _hoops_SPAGI _hoops_PAR _hoops_ICIGP _hoops_GHAGI _hoops_GSPIP.
 */

typedef unsigned short	Karacter;

struct KName {
	Karacter *		_hoops_IPPPP;
	_hoops_GPAGI		length;
};


template <typename T, typename _hoops_PRSHH>
INLINE void _hoops_RHAGI (T const * string, _hoops_PRSHH alter & _hoops_GCAH) {
	/* _hoops_AHAGI */
	_hoops_GCAH = 5381;
	if (string != null) {
		int			c;
		while ((c = (int)*string++) != 0)
			_hoops_GCAH = ((_hoops_GCAH << 5) + _hoops_GCAH) ^ c;
	}
}

#define _hoops_PCIPP(_n_, _hoops_PHAGI)		_hoops_RHAGI ((_n_).text, _hoops_PHAGI)
#define _hoops_HCIPP(_n_, _hoops_PHAGI)	_hoops_RHAGI ((_n_)._hoops_IPPPP, _hoops_PHAGI)


INLINE void _hoops_HCARA(_hoops_HCRPR const & name, Integer32 & key)
{
	/* _hoops_HHAGI */
	key = 0;
	for (int i=0; i<name.length; i++)
		key = name.text[i] + (key << 6) + (key << 16) - key;
}

INLINE void _hoops_HGGIH(_hoops_HCRPR alter & name)
{
	name.length = 0;
	name.text = 0;
}

INLINE void _hoops_IHAGI(KName alter & name)
{
	name.length = 0;
	name._hoops_IPPPP = 0;
}

#define _hoops_RGAIR(name)	do { \
	if ((name).length != 0) { \
		if ((name).length > 0) \
			FREE_ARRAY((name).text, (name).length+1, char); \
		else \
			FREE_ARRAY((name).text, (-(name).length+7)/8, char); \
		_hoops_HGGIH(name); \
	} \
} while (0)

#define _hoops_PRPIR(name) do { \
	if ((name).length != 0) { \
		if ((name).length > 0) \
			FREE_ARRAY((name)._hoops_IPPPP, (name).length+1, Karacter); \
		else \
			FREE_ARRAY((name)._hoops_IPPPP, (-(name).length+15)/16, Karacter); \
		_hoops_IHAGI(name); \
	} \
} while (0)




struct _hoops_AIGH;
struct _hoops_SHGH;

struct RGB {
	public:
		float			red, green, blue;

		RGB () {}
		RGB (float _hoops_ACSAA) : red (_hoops_ACSAA), green (_hoops_ACSAA), blue (_hoops_ACSAA) {}
		RGB (float r, float g, float b) : red (r), green (g), blue (b) {}
		RGB (RGBAS32 const & _hoops_CHAGI);
		RGB (_hoops_AIGH const & _hoops_CHAGI);
		RGB (_hoops_SHGH const & _hoops_SHAGI);

		INLINE	bool	_hoops_PAIIP() const {return (red == green && green == blue);}

		INLINE	float	_hoops_CPIR() const	{ return  0.3125f * red  +  0.5000f * green  +  0.1875f * blue; }

		bool	operator== (RGB const & c) const	{ return  red == c.red && green == c.green && blue == c.blue; }
		bool	operator!= (RGB const & c) const	{ return  !(*this == c); }

		RGB &		operator*= (RGB const & c) alter	{ red *= c.red; green *= c.green; blue *= c.blue;  return *this; }
		RGB &		operator+= (RGB const & c) alter	{ red += c.red; green += c.green; blue += c.blue;  return *this; }
		RGB &		operator-= (RGB const & c) alter	{ red -= c.red; green -= c.green; blue -= c.blue;  return *this; }
		RGB const	operator* (RGB const & c) const		{ return RGB (red * c.red, green * c.green, blue * c.blue); }
		RGB const	operator+ (RGB const & c) const		{ return RGB (red + c.red, green + c.green, blue + c.blue); }
		RGB const	operator- (RGB const & c) const		{ return RGB (red - c.red, green - c.green, blue - c.blue); }

		RGB &		operator*= (float s) alter			{ red *= s; green *= s; blue *= s;  return *this; }
		RGB &		operator/= (float s) alter			{ return operator*= (1.0f / s); }
		RGB &		operator+= (float s) alter			{ red += s; green += s; blue += s;  return *this; }
		RGB &		operator-= (float s) alter			{ red -= s; green -= s; blue -= s;  return *this; }
		RGB const	operator* (float s) const			{ return RGB (red * s, green * s, blue * s); }
		RGB const	operator/ (float s) const			{ return operator* (1.0f / s); }
		RGB const	operator+ (float s) const			{ return RGB (red + s, green + s, blue + s); }
		RGB const	operator- (float s) const			{ return RGB (red - s, green - s, blue - s); }
};
namespace _hoops_GPSR {
		extern HOOPS_API	RGB const		_hoops_RPSR, _hoops_IAHHP;
}

INLINE	RGB const	operator* (float s, RGB const & v) { return RGB (s * v.red, s * v.green, s * v.blue); }
INLINE	RGB const	operator+ (float s, RGB const & v) { return RGB (s + v.red, s + v.green, s + v.blue); }
INLINE	RGB const	operator- (float s, RGB const & v) { return RGB (s - v.red, s - v.green, s - v.blue); }


struct RGBA {
	public:
		float			red, green, blue, alpha;

		RGBA () {}
		RGBA (float _hoops_ACSAA, float a = 1) : red (_hoops_ACSAA), green (_hoops_ACSAA), blue (_hoops_ACSAA), alpha (a) {}
		RGBA (float r, float g, float b, float a = 1) : red (r), green (g), blue (b), alpha (a) {}
		RGBA (RGB const & c, float a = 1) : red (c.red), green (c.green), blue (c.blue), alpha (a) {}
		RGBA (RGBAS32 const & _hoops_CHAGI);

		INLINE bool	_hoops_PAIIP() const {return (red == green && green == blue);}

		INLINE	float	_hoops_CPIR() const	{ return  0.3125f * red  +  0.5000f * green  +  0.1875f * blue; }

		bool			operator== (RGBA const & c) const		{ return  red == c.red && green == c.green &&
																		  blue == c.blue && alpha == c.alpha; }
		bool			operator!= (RGBA const & c) const		{ return  !(*this == c); }

		operator	RGB () const	{ return RGB (red, green, blue); }
};
namespace _hoops_IGISA {
		extern HOOPS_API	RGBA const		_hoops_RPSR, _hoops_IAHHP, _hoops_SAHSR;
}


#define _hoops_GIAGI(t)		((int)(255.99f * (1.0f - t)))
#define _hoops_GPGCR			0xFF

/**
 *	_hoops_IPCP _hoops_CPCP _hoops_IIGR _hoops_HGGPA _hoops_IH 32 _hoops_SIH _hoops_HRGR _hoops_GHARR _hoops_AAR.	 _hoops_PS _hoops_PPIP
 *	_hoops_RH _hoops_HGGPA _hoops_CPCP _hoops_CIAH _hoops_ARI _hoops_PPR _hoops_GGR _hoops_AIICP._hoops_GGHR _hoops_IH _hoops_IRGH _hoops_AIRI
 *	_hoops_PAR _hoops_AIRI _hoops_GPP _hoops_PSHR-_hoops_RIAGI _hoops_GSIA.	 _hoops_CGP _hoops_RH _hoops_AIRI _hoops_HRGR _hoops_ARHI _hoops_RH
 *	_hoops_GGRIR _hoops_IS _hoops_HAGH-_hoops_RIAGI _hoops_GSIA, _hoops_PSCR _hoops_RH _hoops_GRRGI _hoops_PIHA _hoops_ISPR
 *	_hoops_RH _hoops_CPCP _hoops_IIGR _hoops_HGGPA _hoops_PPR _hoops_AIAGI _hoops_SCH _hoops_RPP _hoops_HAHH.
**/
struct RGBAS32 {
	public:
		unsigned char	_hoops_RCRSP;

		RGBAS32 () {}
		RGBAS32 (unsigned char _hoops_PIAGI, unsigned char _hoops_RSIGH, unsigned char _hoops_HIAGI, unsigned char _hoops_IIAGI = 255)
				: r (_hoops_PIAGI), g (_hoops_RSIGH), b (_hoops_HIAGI), a (_hoops_IIAGI) {}
		RGBAS32 (RGB const & c, float alpha = 1.0f)
				: r ((unsigned char)(c.red   * 255.99f))
				, g ((unsigned char)(c.green * 255.99f))
				, b ((unsigned char)(c.blue  * 255.99f))
				, a ((unsigned char)(alpha   * 255.99f)) {}
		RGBAS32 (RGB const & c, unsigned char _hoops_IIAGI)
				: r ((unsigned char)(c.red   * 255.99f))
				, g ((unsigned char)(c.green * 255.99f))
				, b ((unsigned char)(c.blue  * 255.99f))
				, a (_hoops_IIAGI) {}
		RGBAS32 (RGBA const & c, unsigned char _hoops_CIAGI = _hoops_GPGCR)
				: r ((unsigned char)(c.red   * 255.99f))
				, g ((unsigned char)(c.green * 255.99f))
				, b ((unsigned char)(c.blue  * 255.99f))
				, a ((unsigned char)(c.alpha * (_hoops_CIAGI + 0.99f))) {}

		//_hoops_GCRSP _hoops_RCIC &	_hoops_SIRRR= (_hoops_GCRSP _hoops_RCIC & _hoops_GSGGR) _hoops_RAPC		{ _hoops_SHSC() = _hoops_GSGGR._hoops_SHSC(); _hoops_ASRC *_hoops_RGR; }

		bool			operator== (RGBAS32 const & c) const	{ return  _hoops_PCRSP() == c._hoops_PCRSP(); }
		bool			operator!= (RGBAS32 const & c) const	{ return  !(*this == c); }

	private:
		// _hoops_ASSS _hoops_IHHH _hoops_IS _hoops_HCRSP _hoops_AA _hoops_PCPA _hoops_RH _hoops_RHGS "_hoops_ICRSP" _hoops_ARIP (_hoops_GAR _hoops_IRS _hoops_HIPRA) _hoops_IIS _hoops_IHHH _hoops_AA _hoops_GRGA
		Integer32 const &	_hoops_PCRSP() const	{ return *(Integer32 const *)this; }
		//_hoops_RGRHA _hoops_RAPC &	_hoops_SHSC() _hoops_RAPC	{ _hoops_ASRC *(_hoops_RGRHA _hoops_RAPC *)_hoops_RGR; }
};
namespace _hoops_CAHSR {
		extern HOOPS_API	RGBAS32 const		_hoops_RPSR, _hoops_IAHHP, _hoops_SAHSR;
}
_hoops_AHAGP (sizeof(RGBAS32) == sizeof(Integer32), _hoops_SIAGI);


INLINE RGB::RGB (RGBAS32 const & _hoops_CHAGI)
			: red   (_hoops_CHAGI.r * (1.0f/255.0f))
			, green (_hoops_CHAGI.g * (1.0f/255.0f))
			, blue  (_hoops_CHAGI.b * (1.0f/255.0f)) {}
INLINE RGBA::RGBA (RGBAS32 const & _hoops_CHAGI)
			: red   (_hoops_CHAGI.r * (1.0f/255.0f))
			, green (_hoops_CHAGI.g * (1.0f/255.0f))
			, blue  (_hoops_CHAGI.b * (1.0f/255.0f))
			, alpha (_hoops_CHAGI.a * (1.0f/255.0f)) {}



struct _hoops_AIGH {
	public:
		unsigned char		r, g, b, a;

		_hoops_AIGH () {}
		_hoops_AIGH (unsigned char _hoops_PIAGI, unsigned char _hoops_RSIGH, unsigned char _hoops_HIAGI, unsigned char _hoops_IIAGI = 255)
				: r (_hoops_PIAGI), g (_hoops_RSIGH), b (_hoops_HIAGI), a (_hoops_IIAGI) {}
		_hoops_AIGH (RGBAS32 const & _hoops_CHAGI)
				: r (_hoops_CHAGI.r), g (_hoops_CHAGI.g), b (_hoops_CHAGI.b), a (_hoops_CHAGI.a) {}
		_hoops_AIGH (RGB const & c, float alpha = 1.0f)
				: r ((unsigned char)(c.red   * 255.99f))
				, g ((unsigned char)(c.green * 255.99f))
				, b ((unsigned char)(c.blue  * 255.99f))
				, a ((unsigned char)(alpha   * 255.99f)) {}
		_hoops_AIGH (RGB const & c, unsigned char _hoops_IIAGI)
				: r ((unsigned char)(c.red   * 255.99f))
				, g ((unsigned char)(c.green * 255.99f))
				, b ((unsigned char)(c.blue  * 255.99f))
				, a (_hoops_IIAGI) {}
		_hoops_AIGH (RGBA const & c, unsigned char _hoops_CIAGI = _hoops_GPGCR)
				: r ((unsigned char)(c.red   * 255.99f))
				, g ((unsigned char)(c.green * 255.99f))
				, b ((unsigned char)(c.blue  * 255.99f))
				, a ((unsigned char)(c.alpha * (_hoops_CIAGI + 0.99f))) {}

		//_hoops_GCAGI _hoops_RCIC &	_hoops_SIRRR= (_hoops_GCAGI _hoops_RCIC & _hoops_GSGGR) _hoops_RAPC		{ _hoops_SHSC() = _hoops_GSGGR._hoops_SHSC(); _hoops_ASRC *_hoops_RGR; }

		bool			operator== (_hoops_AIGH const & c) const	{ return  _hoops_PCRSP() == c._hoops_PCRSP(); }
		bool			operator!= (_hoops_AIGH const & c) const	{ return  !(*this == c); }

	private:
		// _hoops_ASSS _hoops_IHHH _hoops_IS _hoops_HCRSP _hoops_AA _hoops_PCPA _hoops_RH _hoops_RHGS "_hoops_ICRSP" _hoops_ARIP (_hoops_GAR _hoops_IRS _hoops_HIPRA) _hoops_IIS _hoops_IHHH _hoops_AA _hoops_GRGA
		Integer32 const &	_hoops_PCRSP() const	{ return *(Integer32 const *)this; }
		//_hoops_RGRHA _hoops_RAPC &	_hoops_SHSC() _hoops_RAPC	{ _hoops_ASRC *(_hoops_RGRHA _hoops_RAPC *)_hoops_RGR; }
};
_hoops_AHAGP (sizeof(_hoops_AIGH) == sizeof(Integer32), _hoops_RCAGI);

INLINE RGB::RGB (_hoops_AIGH const & _hoops_CHAGI)
			: red   (_hoops_CHAGI.r * (1.0f/255.0f))
			, green (_hoops_CHAGI.g * (1.0f/255.0f))
			, blue  (_hoops_CHAGI.b * (1.0f/255.0f)) {}






struct _hoops_SHGH {
	unsigned char		r, g, b;
};

INLINE RGB::RGB (_hoops_SHGH const & _hoops_SHAGI)
			: red   (_hoops_SHAGI.r * (1.0f/255.0f))
			, green (_hoops_SHAGI.g * (1.0f/255.0f))
			, blue  (_hoops_SHAGI.b * (1.0f/255.0f)) {}


struct _hoops_IRSRH {
	unsigned char		a, r, g, b;
};


struct _hoops_SGGCR {
	int					r, g, b;
};

struct _hoops_PACHR {
	float				_hoops_SCPHR, _hoops_HSPHR, _hoops_ISPHR;
};



typedef int		_hoops_ARGRA;
#define _hoops_GSGPH					(_hoops_ARGRA)0x0000
#define M_DIFFUSE				(_hoops_ARGRA)0x0001
#define _hoops_RHGPH			M_DIFFUSE	/* _hoops_ARPP _hoops_CHAAR _hoops_IS _hoops_SASI _hoops_RCAP */
#define M_SPECULAR				(_hoops_ARGRA)0x0002
#define M_MIRROR				(_hoops_ARGRA)0x0004
#define M_TRANSMISSION			(_hoops_ARGRA)0x0008
#define M_EMISSION				(_hoops_ARGRA)0x0010

#define _hoops_RAGRA					(_hoops_ARGRA)0x0020
#define _hoops_AAGRA					(_hoops_ARGRA)0x0040

#define _hoops_RHGRA		(_hoops_ARGRA)0x0100
#define _hoops_GHGPH		_hoops_RHGRA /* _hoops_ARPP _hoops_CHAAR _hoops_IS _hoops_SASI _hoops_RCAP */
#define _hoops_PIARA		(_hoops_ARGRA)0x0200
#define _hoops_HIARA		(_hoops_ARGRA)0x0400
#define _hoops_IIARA	(_hoops_ARGRA)0x0800
#define _hoops_CIARA		(_hoops_ARGRA)0x1000

#define _hoops_SIARA			(_hoops_ARGRA)0x2000
#define _hoops_GCARA	(_hoops_ARGRA)0x4000

#define _hoops_CHGRA			(_hoops_ARGRA)0x8000

#define _hoops_PSARA			(_hoops_ARGRA)0x7F00
#define _hoops_ASARA				(_hoops_ARGRA)0x001F

#define _hoops_CIGRA				(_hoops_ARGRA)0x607F


#define	_hoops_IAA				 0
#define _hoops_RSHHP					 1
#define _hoops_SAA					 2
#define _hoops_RPA					 3
#define _hoops_PPA				 4
#define _hoops_APA				 5
#define _hoops_GGIHP					 6
#define _hoops_PAIHP				 7
#define _hoops_IAIHP				 8
#define _hoops_HSHHP				 9
//
#define _hoops_RAIHP    11
//	_hoops_AA _hoops_CGARA _hoops_PSHA _hoops_RRP _hoops_IS _hoops_SHH _hoops_IHIR _hoops_GCHR?
#define _hoops_SGIHP		12
#define _hoops_RRIHP		13
#define _hoops_HRIHP		14
#define _hoops_IRIHP		15
#define _hoops_SRIHP		16
#define _hoops_CRIHP		17
#define _hoops_GAIHP		18
#define _hoops_ACAGI	19
#define _hoops_PCAGI	20
#define _hoops_PGIHP		21
//
//
#define _hoops_HCAGI				24
#define _hoops_ICAGI			25
#define _hoops_CCAGI			26

// _hoops_GRHP _hoops_CGHI
#define _hoops_SCAGI				31


#define	_hoops_IIGRA		22
#define	_hoops_SSGRA			27

/* _hoops_RRP _hoops_IS _hoops_PSSP _hoops_GSAGI */
typedef int		Color_Object;
#define Color_NONE				(Color_Object)0x00000000
#define _hoops_SRARA			(Color_Object)(1<<_hoops_SCAGI)

#define Color_FRONT				(Color_Object)(1<<_hoops_IAA)
#define Color_BACK				(Color_Object)(1<<_hoops_RSHHP)
#define Color_EDGE				(Color_Object)(1<<_hoops_SAA)
#define Color_LINE				(Color_Object)(1<<_hoops_RPA)
#define Color_VERTEX			(Color_Object)(1<<_hoops_PPA)
#define Color_MARKER			(Color_Object)(1<<_hoops_APA)
#define Color_TEXT				(Color_Object)(1<<_hoops_GGIHP)
#define Color_CUT_FACE			(Color_Object)(1<<_hoops_PAIHP)
#define Color_CUT_EDGE			(Color_Object)(1<<_hoops_IAIHP)
#define Color_WINDOW			(Color_Object)(1<<_hoops_HSHHP)
#define _hoops_SGARA	(Color_Object)(1<<_hoops_RAIHP)
#define _hoops_RRARA	(Color_Object)(1<<_hoops_SGIHP)
#define _hoops_GRARA		(Color_Object)(1<<_hoops_RRIHP)
#define Color_EDGE_CONTRAST		(Color_Object)(1<<_hoops_HRIHP)
#define Color_LINE_CONTRAST		(Color_Object)(1<<_hoops_IRIHP)
#define Color_VERTEX_CONTRAST	(Color_Object)(1<<_hoops_SRIHP)
#define Color_MARKER_CONTRAST	(Color_Object)(1<<_hoops_CRIHP)
#define Color_TEXT_CONTRAST		(Color_Object)(1<<_hoops_GAIHP)
#define _hoops_HGARA	(Color_Object)(1<<_hoops_ACAGI)
#define _hoops_PGARA	(Color_Object)(1<<_hoops_PCAGI)
#define Color_WINDOW_CONTRAST	(Color_Object)(1<<_hoops_PGIHP)
#define Color_LIGHTING			(Color_Object)(1<<_hoops_HCAGI)
#define _hoops_PRARA		(Color_Object)(1<<_hoops_ICAGI)
#define _hoops_HRARA		(Color_Object)(1<<_hoops_CCAGI)


#define _hoops_IRARA				(_hoops_PRARA|_hoops_HRARA)
#define Color_FACE						(Color_FRONT|Color_BACK)
#define Color_FACE_CONTRAST				(_hoops_RRARA|_hoops_GRARA)
#define Color_POLYGON					(Color_FACE|Color_EDGE)
#define Color_GEOMETRY					(Color_POLYGON|Color_LINE|Color_MARKER|Color_VERTEX|Color_TEXT)
#define Color_CUT_GEOMETRY				(Color_CUT_FACE|Color_CUT_EDGE)
#define _hoops_IGARA		(_hoops_HGARA|_hoops_PGARA)

#define _hoops_AGIHP					(Color_FACE_CONTRAST|Color_EDGE_CONTRAST|Color_LINE_CONTRAST|\
										 Color_MARKER_CONTRAST|Color_VERTEX_CONTRAST|Color_TEXT_CONTRAST|\
										 Color_WINDOW_CONTRAST|_hoops_HGARA)

#define Color_EVERYTHING				(Color_WINDOW|Color_GEOMETRY|Color_CUT_GEOMETRY|_hoops_AGIHP|\
										 Color_LIGHTING|_hoops_IRARA)

/* _hoops_RH _hoops_HSPR _hoops_PGCR _hoops_APSAR _hoops_GA'_hoops_RA _hoops_GCIS _hoops_SPI, _hoops_PGAP _hoops_HRGR _hoops_GGR _hoops_IRS _hoops_GIAH _hoops_CCHHR _hoops_HIGR */
#define _hoops_GAGRA	6
#define _hoops_CRGRA		4

#define _hoops_HIA		0
#define _hoops_ACA			1
#define _hoops_PCA	2
#define _hoops_HCA		3
#define _hoops_IIA			4
#define _hoops_RIA		5

typedef unsigned int Material_Channel_Flags;
#define _hoops_RSAGI					(Material_Channel_Flags)0x0000
#define _hoops_PRA			(Material_Channel_Flags)0x0001  /* _hoops_ASAGI _hoops_RH _hoops_HH _hoops_HPP _hoops_RGCI _hoops_PSAGI */
#define _hoops_CCARA				(Material_Channel_Flags)0x0002  /* _hoops_AI _hoops_PIHA _hoops_GPCPR _hoops_PSSP _hoops_PAIGR */
#define _hoops_SGGRA				(Material_Channel_Flags)0x0004  /* _hoops_PRSCA _hoops_IS _hoops_HCR _hoops_RCHAR _hoops_GRIP */
#define _hoops_PPIR	(Material_Channel_Flags)0x0008  /* _hoops_RPP _hoops_CGRAR _hoops_RH _hoops_HH _hoops_SGH _hoops_RH _hoops_HSAGI */

struct _hoops_HIR {
	_hoops_HIR *		next;
	_hoops_RCR *					texture;
	_hoops_HCRPR						name;
	float						_hoops_IRIR;
	int							_hoops_HGA;
	Material_Channel_Flags		flags;
};

struct Named_Material {
	_hoops_RCR *					texture[_hoops_GAGRA];  /* _hoops_GRAA-_hoops_SPI _hoops_GRIP _hoops_RGAR */
	_hoops_HIR *		_hoops_SCA;
	RGB							_hoops_CSHR;				// _hoops_ACHSP _hoops_CPSA _hoops_SHH _hoops_HHGPH _hoops_HII _hoops_GAPRA
	_hoops_HCRPR						_hoops_IRGRA;
	RGB							color[_hoops_CRGRA];		// _hoops_PCAGR
	_hoops_HCRPR						name[_hoops_CRGRA];
	Material_Channel_Flags		flags[_hoops_CRGRA];

	int							_hoops_HRGRA;

	float						gloss,
								_hoops_PAGRA,
								_hoops_IRIR;
	_hoops_ARGRA			_hoops_PRGRA;
};


/* _hoops_HHIPR/_hoops_CRS _hoops_PSAI _hoops_IGI _hoops_IH _hoops_ISAGI */

struct _hoops_CSAGI {
	long				index;
	void				*value;
};

typedef double			_hoops_GSPGR;
#define _hoops_SSAGI(_hoops_GGPGI)		((_hoops_GSPGR)(_hoops_HSPGR*(_hoops_GGPGI)))  /* _hoops_RGPGI _hoops_IS _hoops_SCCSH */
#define _hoops_HIAPR	_hoops_SSAGI(1.0/100.0)

typedef short				Type;

#define	_hoops_GCCPP		0x0000
#define	_hoops_RCCPP		0x0001
#define	_hoops_ACCPP		0x0002

#define	_hoops_RHSPP	0x0100

typedef int						Error_Mask;

struct _hoops_CPSPP {
	_hoops_CPSPP *		next;
	int					category,
						specific;
	short				_hoops_GHSPP,	/* _hoops_ARSAR _hoops_HPP _hoops_IPSP */
						state;		/* _hoops_RGSR, _hoops_AHSAR _hoops_ARR -> _hoops_PSAP _hoops_RAS _hoops_SGH */
};



typedef char					_hoops_IHGRP;

typedef unsigned Integer32	_hoops_PCARP;
typedef unsigned Integer32	_hoops_GHGI;
typedef Integer32			_hoops_GSGAP;

typedef int						_hoops_GCRAP,
								_hoops_ISAAP,
								_hoops_RRPAP,
								Quantization_Flags,
								_hoops_SHCRP,
								_hoops_PPAAP,
								_hoops_GPCRP,
								_hoops_GICRP,
								_hoops_RRPHA,
								_hoops_CCSRP,
								_hoops_IHGAP,
								_hoops_HIGAP,
								_hoops_CCGAP,
								_hoops_ASSRP,
								_hoops_HGGAP,
								_hoops_RAGAP,
								_hoops_SAGAP,
								_hoops_AHAAP,
								_hoops_RIHRP,
								_hoops_RHHRP,
								_hoops_RCHRP,
								_hoops_SCHRP;

typedef Integer32			_hoops_RAAH;
typedef char					Image_Format;
#define _hoops_CAHPA				(Image_Format)0
#define Image_MAPPED_8			(Image_Format)1
#define Image_MAPPED_16			(Image_Format)2
#define _hoops_HHGH				(Image_Format)3
#define _hoops_HRSRH			(Image_Format)4
#define Image_RGBA32			(Image_Format)5
#define _hoops_PCCRH		(Image_Format)6
/* _hoops_SGCRP _hoops_AGPGI _hoops_RPCC */
#define _hoops_CSGSP			(Image_Format)7
/* _hoops_RII _hoops_SGCRP _hoops_AGHS */
#define _hoops_PGPGI			(Image_Format)8
#define _hoops_PGGSP			(Image_Format)9
#define _hoops_AGGSP			(Image_Format)10
#define _hoops_IRRH				(Image_Format)11
#define _hoops_CRRH				(Image_Format)12
#define _hoops_SRRH				(Image_Format)13
#define _hoops_GGRH				(Image_Format)14
#define _hoops_RGRH				(Image_Format)15
#define _hoops_AGRH				(Image_Format)16
#define _hoops_AHGH		(Image_Format)17


/* _hoops_AARSP _hoops_HCGP _hoops_CSSC */
#define _hoops_HGPGI								0
#define _hoops_IGPGI								1
#define _hoops_CGPGI								2
#define _hoops_SGPGI		3
#define _hoops_HISCP		4
#define _hoops_GRPGI								5
#define _hoops_RRPGI								6

typedef int				_hoops_ARASA;
#define _hoops_HRIHR					(_hoops_ARASA)0x00
#define _hoops_ARPGI					(_hoops_ARASA)0x01
#define _hoops_PRPGI		(_hoops_ARASA)0x02


typedef unsigned short			_hoops_RCCCA;

#define _hoops_HGAGR				(_hoops_RCCCA)0x0001 // _hoops_IH _hoops_PA
#define _hoops_PASIR			(_hoops_RCCCA)0x0002 // _hoops_IH _hoops_CPAP, _hoops_GCIS, _hoops_CAGH
#define _hoops_RSPCR			(_hoops_RCCCA)0x0004 // _hoops_IH _hoops_CPAP, _hoops_RSGA, _hoops_SARA
#define _hoops_CHRIR			(_hoops_RCCCA)0x0008 // _hoops_CPAP _hoops_RGGAR _hoops_GPRR
#define _hoops_GGSCA				(_hoops_RCCCA)0x0010 // _hoops_SGHC & _hoops_CPAP
#define _hoops_GGCCA			(_hoops_RCCCA)0x0020 // _hoops_SGHC & _hoops_CPAP
#define _hoops_HRPGI			(_hoops_RCCCA)0x0040 // _hoops_IRHP _hoops_CPAP
#define _hoops_IRPGI				(_hoops_RCCCA)0x0080 // _hoops_IH _hoops_PGPI _hoops_PPR _hoops_PHHIP _hoops_CRPGI

#define _hoops_HCIGP(v)		(_hoops_RCCCA)(1 << (7+(v)))	/* _hoops_IPIH _hoops_SCIA 8 _hoops_HPAP _hoops_SIH _hoops_HHGHR 1-8 */


#define _hoops_AGGHP		(1L<<20)	/* 1_hoops_CACS */



#define XBIT_SIZE   2

#define XBIT_BIT(item)		(item%32)
#define XBIT_OFFSET(item)	(item/32)

#define XBIT_TEST(a,b) (((a)[XBIT_OFFSET(b)] & (1<<XBIT_BIT(b))) != 0)
#define XBIT_APPEND(a,b) (((a)[XBIT_OFFSET(b)] |= (1<<XBIT_BIT(b))))

typedef Integer32 _hoops_SRPGI;

#define _hoops_GAPGI		(_hoops_SRPGI)0x00000000
#define _hoops_IIIPP	(_hoops_SRPGI)0x00000001

struct _hoops_ARARR {
	_hoops_HCRPR		driver;
	_hoops_HCRPR		id;
	_hoops_HCRPR		version;
	_hoops_HCRPR		_hoops_AAIPP;

	_hoops_SRPGI flags;

	Integer32	_hoops_HHIPP[XBIT_SIZE];

	_hoops_AAPIR	*config;

	int			_hoops_CIIPP;
	int			_hoops_SIIPP;
	int			_hoops_GCIPP;
	int			_hoops_RCIPP;

	_hoops_ARARR * next;
};


struct _hoops_AISIA {
	Point hit_location;
};


struct XBits {
	const char		*options;
	Integer32	bit;
};


#define	_hoops_RAPGI	256

struct _hoops_AAPGI {
	_hoops_AAPGI		*forward;
	_hoops_AAPGI		*_hoops_PAPGI;
	struct {
		Key					owner;
		Key					key;
		int						region;
	} original,
								_hoops_HAPGI;
};

struct _hoops_IAPGI {
	_hoops_IAPGI		*next;
	_hoops_CRCP const				*segment;
	_hoops_AAPGI			*forward[_hoops_RAPGI];
	_hoops_AAPGI			*_hoops_PAPGI[_hoops_RAPGI];
};

typedef struct _hoops_CAPGI {
	_hoops_PSSAP					**table;
	Integer32				size;
	Integer32				_hoops_SAPGI;
} _hoops_GPPGI;





INLINE void	_hoops_SSAGR (void const * item)
{
#if defined (_hoops_IIIPA)
	__asm {
		mov			eax, item
		prefetcht0	[eax]
	}
#elif defined (_hoops_HHCSH)
	_mm_prefetch ((char const *)item, 1);
#elif defined (_hoops_HIAGP)
	__builtin_prefetch (item);
#elif defined (_hoops_ACCSH)
	asm volatile("prefetcht0 %0" :: "m" (*(unsigned long *)item));
#else
	UNREFERENCED(item);
#endif
}

#if 0
// _hoops_GA'_hoops_RA _hoops_SGH _hoops_IH _hoops_HA
INLINE void	PrefetchW (void const * item)
{
#ifdef _hoops_IIIPA
	__asm {
		mov			eax, item
		prefetchw	[eax]
	}
#endif
#ifdef _hoops_ACCSH
	asm volatile("prefetcht0 %0" :: "m" (*(unsigned long *)item));
#endif
	UNREFERENCED(item);
}
#endif



typedef	void (HC_CDECL *_hoops_RPPGI)(void);

typedef	int (HC_CDECL * _hoops_APPGI)
(_hoops_HHCR const & _hoops_IHCR,
 int point_count, Point const *in, float const *matrix, _hoops_PACIR const *_hoops_GPHH,
 DC_Point alter *_hoops_PAGR, float alter *ws, unsigned char alter *_hoops_RRCAR);

typedef Attribute alter * (HC_CDECL * _hoops_RSCIH)
(_hoops_AIGPR * _hoops_RIGC, _hoops_HPAH * item, Attribute const * _hoops_PISCA, Attribute *	_hoops_SISCA);

struct _hoops_RSAHP {
	_hoops_GICGP	**_hoops_SCAHP;
	int 					allocated;
	int 					used;
};

struct _hoops_PPPGI {
	union {
		_hoops_HPAH *		item;			// _hoops_GSSR _hoops_IPI
		_hoops_PPPGI *		_hoops_HPPGI;		// _hoops_IS _hoops_AASH _hoops_RHPA _hoops_AIRP
	};
	Key				key;
	int				offset;				// -1 _hoops_GPP _hoops_IPPGI
};

#define		_hoops_GRSCA			0x0001
#define		_hoops_APGHP		0x0002

struct _hoops_CPPGI {
	_hoops_CRCP	const *			_hoops_RPGHP;
	_hoops_SRPPR **				_hoops_ASPPR;
	_hoops_PGIIR **					_hoops_SPPGI;
	_hoops_RSHIR **			_hoops_SCHPP;
	_hoops_SCHIR *				_hoops_AIHPP;
	_hoops_HCHIR **		_hoops_RAPCR;
	_hoops_ISGPH *	_hoops_HIHPP;
	_hoops_GPPGI				global_keys;
	_hoops_HCRPR					_hoops_ISHAP;
	int						flags;
};

#define		_hoops_RRSCA			0x0001
#define		_hoops_PGPSA				0x1000

struct _hoops_AIGPR {	/* _hoops_ISSSH-_hoops_SASI _hoops_PAAP _hoops_SIHC */
	_hoops_GSPGR						_hoops_GHPGI;
	_hoops_GSPGR						_hoops_ACHGH;
	_hoops_GSPGR						_hoops_RHPGI;

	_hoops_AIGPR *		next;

	Memory_Pool *				memory_pool;

	HThreadID					thread_id;
	HM_Semaphore				semaphore;
	bool						_hoops_GSHGH;

	/* _hoops_GGSC-_hoops_ISIAH _hoops_CIPH */
	_hoops_SIRIR *					open_list;

	char const *				_hoops_RCSPP;
	char const *				_hoops_SACAA[20]; /* (20 _hoops_HRGR _hoops_CHPP!) */
	char const **				_hoops_CACAA;

	_hoops_SSPPR *				_hoops_AHPGI;
	_hoops_SSPPR *				_hoops_GHHCA;
	_hoops_SSPPR *				_hoops_RGHPR;
	_hoops_SSPPR *				_hoops_AAPCR;
	_hoops_SSPPR *				_hoops_PSHPP;
	_hoops_SSPPR *				_hoops_PHPGI;
	_hoops_SSPPR *				_hoops_HHPGI;
	_hoops_SSPPR *				_hoops_IHPGI;
	_hoops_SSPPR *				_hoops_CHPGI;
	_hoops_SSPPR *				glyph_search_stack;
	_hoops_SSPPR *				_hoops_SHPGI;
	_hoops_SSPPR *				_hoops_GIPGI;
	_hoops_SSPPR *				_hoops_RHSAH;
	_hoops_SSPPR *				_hoops_HCHPH;

	_hoops_HISHA *						_hoops_PAARH;
	_hoops_HISHA *						_hoops_PCRPH;
	_hoops_HISHA *						_hoops_PISHA;
	_hoops_AISIA *		_hoops_SIPPH;

	void *						_hoops_PRCIA;
	void *						_hoops_RAHPA;
	void *						_hoops_HSIHA;

	/* _hoops_AGCR _hoops_RRP _hoops_IS _hoops_SHH _hoops_GARPR _hoops_RIR-_hoops_ISSSH */
	char						_hoops_RIPGI[_hoops_CGHHP];

	int							_hoops_SGSAH;
	int							_hoops_GRSAH;
	int							_hoops_RRSAH;

	int							_hoops_IAPCR;
	int							flags;

	/* _hoops_ISSSH-_hoops_SASI _hoops_PAAP _hoops_SIHC */

#define _hoops_AIPGI				0		/* _hoops_SHHA _hoops_APHR _hoops_PIAP */
#define _hoops_HAGRH					1
#define _hoops_IAGRH		2
#define _hoops_PIPGI					3

	int							_hoops_PAGRH;
	int							_hoops_HCPGR;
	volatile bool				_hoops_IIHGH;
};



struct _hoops_GSSSH {

	int							system_flags;
	int							_hoops_RRHGA;

	bool						_hoops_SCSPP;
	_hoops_CHSPP				malloc;
	_hoops_GISPP					free;
};

struct _hoops_IGHGP {
	virtual	~_hoops_IGHGP() {}		// _hoops_RRP _hoops_IS _hoops_PSSP _hoops_AHSGP _hoops_IIGR _hoops_HIPGI _hoops_AARPR _hoops_APSAR, _hoops_HIS _hoops_HHSA _hoops_IRS _hoops_IIPGI

	_hoops_IGHGP				*next,
						**backlink;
	void				*owner;			/* _hoops_CIPGI */
	_hoops_GHRIR				_hoops_HIHI;
	Type				type;
	_hoops_RCCCA		_hoops_RRHH;		/* (_hoops_SPASR _hoops_GSRRR _hoops_CPGC) */

	bool						_hoops_GCSPP;
	bool						_hoops_PRRPH;
	bool						_hoops_PPRIR;
    bool						_hoops_PASAH;



	_hoops_AIGPR *		_hoops_PGSCA;
	_hoops_AIGPR *		_hoops_SIPGI;

	_hoops_CPPGI *			_hoops_SARHP;
	int							_hoops_CARHP;

	int							_hoops_GCPGI;

	bool						_hoops_APPSA;

	_hoops_GSPGR volatile *				time_stamp;
	Memory_Pool *				memory_pool;
	_hoops_SRIAP *				_hoops_ACARR;

	_hoops_PRGGI *		_hoops_RCPGI;

	long						_hoops_ICRGH;
	long						_hoops_CCRGH;
	long						_hoops_SCRGH;
	long						_hoops_GSRGH;

	long						_hoops_PSRGH;
	long						_hoops_HSRGH;

	size_t						raw_memory_usage;

	Memory_Pool *				_hoops_ACPGI;

	bool						_hoops_SCSPP;
	_hoops_CHSPP				malloc;
	_hoops_GISPP					free;
	_hoops_CHSPP				_hoops_GSSPP;
	_hoops_GISPP					_hoops_RSSPP;

	size_t						_hoops_PCPGI;
	float						_hoops_HCPGI;
	_hoops_IIPSA *				_hoops_HIPSA;
	long						_hoops_SHPSA;
	long						_hoops_CIPSA;
	long						_hoops_ISRGH;
	long						_hoops_ICPGI;

	long						_hoops_PCRGH;
	long						_hoops_HCRGH;

	_hoops_PAPSA *				_hoops_AAPSA;

	_hoops_IGGGI *	_hoops_PPAPA;

	_hoops_GGAGR *						_hoops_CISHA;
	_hoops_CRCP *					root;
	int							_hoops_RCRGI;

	_hoops_GPPGI					_hoops_CCPGI;

	struct {
		_hoops_PPPGI *		table;
		int				count;
		int				allocated;
		_hoops_PPPGI *		_hoops_CRIGP;		// _hoops_AASH _hoops_AHRRA _hoops_IAGH _hoops_CAPP _hoops_RH _hoops_SCIA
	}							_hoops_GCHCA;


	_hoops_RGIIR *				_hoops_RASAH;
	_hoops_SSHIR *				_hoops_AIHPH;
	_hoops_RGIIR *				_hoops_RPAPH;
	bool						_hoops_GASAH;
	bool						_hoops_ACHPH;

	_hoops_HCRPR						fortran_bufs[6];

	unsigned char *				_hoops_SCPGI;
	unsigned char *				_hoops_SCSHH;
	unsigned short *			_hoops_IPSHH;

	long						_hoops_IPAPA;

	_hoops_GCIIR			_hoops_GSPGI[_hoops_CIRGI];

	_hoops_PIIIR **				_hoops_PCIIR;
	int							_hoops_AGCAA;

	int							_hoops_RSPGI;

	_hoops_HRIIR *					_hoops_CGAPH;
	void *						_hoops_GPAPR;

	bool						_hoops_ASPGI;
	int							_hoops_SIHGH;

	_hoops_HCHIR *				_hoops_HGGHP;

	_hoops_IGGHP		_hoops_PGGHP;

	_hoops_HCHIR *				_hoops_CGGHP;

	_hoops_SGGHP			_hoops_HHRIR;

	_hoops_APPGI	_hoops_PHCAR[6];

	_hoops_RPPGI	_hoops_CIHPH;
	void						*_hoops_PSPGI;
	void						*_hoops_HSPGI;
	void						*_hoops_ISPGI;

	_hoops_CRRGI	_hoops_IARPR;


	unsigned Integer32			_hoops_GPPI;
	bool						_hoops_AARPH;
	bool						_hoops_RAAPH;

	unsigned Integer32			global_id; // _hoops_IH _hoops_CI _hoops_CSPGI'_hoops_GRI, _hoops_AHI...

	void *						_hoops_SSPGI;

	_hoops_AAPHP *			_hoops_RAPHP;
	unsigned Integer32			_hoops_HAPHP;

	/* _hoops_GHARR _hoops_AAP... */
	Error_Mask					error_mask;
	_hoops_CPSPP *				_hoops_PSSPP[4];	/* _hoops_SIHC, _hoops_ASRHR, _hoops_RIHH, _hoops_GGHGI */
	int							_hoops_RAPPR;
	_hoops_HCRPR						_hoops_GRGHP;	/* _hoops_RGHGI _hoops_HIICP */
	_hoops_HCRPR						_hoops_GRHGA;
	_hoops_HCRPR						_hoops_PARPR;
	_hoops_IHGRP				encoding;		/* _hoops_RGHGI+1 _hoops_HIICP */
	char						_hoops_AGHGI;	/* _hoops_ISSC _hoops_IS _hoops_PGHGI _hoops_HIICP */	// _hoops_PAGA: _hoops_GGHSP(_hoops_CICC) _hoops_HAR _hoops_GICPR 1
	int							_hoops_RRGHP,
								_hoops_ARGHP;

#	define		_hoops_HGHGI						0x00000001
#	define		_hoops_IGHGI				0x00000002
#	define		_hoops_CGHGI							0x00000004
#	define		_hoops_PRIHR			0x00000100
#	define		_hoops_AACHR				0x00000200
#	define		_hoops_AHCHR			0x00000400
#	define		_hoops_HRRIR			0x00000800
#	define		_hoops_IRIHR				0x00001000
#	define		_hoops_SGHGI	0x00002000
#	define		_hoops_CRIHR				0x00004000
#	define		_hoops_IGPSA		0x00008000
#	define		_hoops_GRHGI					0x00010000
#	define		_hoops_RRHGI				0x00020000
#	define		_hoops_ARHGI							0x00040000

	int							_hoops_IRARR;

#	define		_hoops_HSCPP				0x00000001
#	define		_hoops_ISCPP				0x00000002
#	define		_hoops_PRHGI						0x00000004
#	define		_hoops_HCAGP						0x00000008
#	define		_hoops_HRHGI						0x00000010
#	define		_hoops_IGHGA					0x00000020
#	define		_hoops_RGRI			0x00000040
#	define		_hoops_PGSPP				0x00000080
#	define		_hoops_AGSPP			0x00000100
#	define		_hoops_SSCPP			0x00000200
#	define		_hoops_CSRRA			0x00000400
#	define		_hoops_GGSPP			0x00000800
#	define		_hoops_RGSPP			0x00001000
#	define		_hoops_HGSPP	0x00002000
#	define		_hoops_CSCPP			0x00004000
#	define		Sysop_RAW_MEMORY					0x00008000
#	define		_hoops_PAI		0x00010000
	int							system_flags;

#	define		_hoops_PICPP					0x0000
#	define		_hoops_SRRIR		0x0001
#	define		_hoops_IICPP	0x0002
#	define		_hoops_AHSSR	0x0004
#	define		_hoops_IGGHR				0x0008
#	define		_hoops_HICPP				0x000F
	int							_hoops_HGGHR;

#	define		_hoops_GPPPR			0x0001
#	define		_hoops_IRHGI			0x0002

	int							_hoops_SAPPR;

	Integer32					_hoops_CRHGI;
	Pending_Special *			_hoops_SRHGI;
	_hoops_ISSAP *			_hoops_GAHGI;


	void *						_hoops_RAHGI;
	_hoops_ARARR *				_hoops_IHIPP;

	/* _hoops_IHIS _hoops_RH _hoops_ACSP, _hoops_RPP _hoops_GII, _hoops_GH _hoops_CGPR _hoops_AAHGI... */

	bool						_hoops_PAHGI;

	int							_hoops_PRGHP;

	_hoops_AAPIR *					_hoops_AAGHP;
	_hoops_HCRPR						_hoops_HAHGI;
	bool						_hoops_RAGHP;

	/*_hoops_IAHGI _hoops_IH _hoops_HRCSR _hoops_CAHGI*/
	void *						global_font_data_freetype;

	void *						_hoops_SAHGI;

	float						_hoops_CRGHP;
	float						_hoops_IRGHP;

	void *						_hoops_AGHGA;
	int							_hoops_RRHGA;
	int							_hoops_CGHGA;
	int							_hoops_CCRGI;
	int							_hoops_ISPPR;
	bool						_hoops_PGHGA;

#	define		_hoops_CPCPP		0x0001
#	define		_hoops_GHCPP		0x0002
#	define		_hoops_RHCPP	0x0004
#	define		_hoops_SPCPP 0x0008
#	define		_hoops_AHCPP		0x0010
	int							_hoops_HPSPP;

	_hoops_AAPIR *					_hoops_PAGHP;
	_hoops_AAPIR *					_hoops_HAGHP;

	bool						_hoops_IPSPP;
	unsigned int				_hoops_GPHGI;

	_hoops_CPGRR						_hoops_RPHGI;
	_hoops_CPGRR						_hoops_PIPSA;
	_hoops_CPGRR						_hoops_GAPHP;
	_hoops_CPGRR						_hoops_IIAGP;
	_hoops_CPGRR						_hoops_RIPSA;
	_hoops_CPGRR						_hoops_RAPSA;
	_hoops_CPGRR						_hoops_HPSAP;
	_hoops_CPGRR						_hoops_ICRGI;
	_hoops_CPGRR						_hoops_APHGI;			// _hoops_RGAR _hoops_IH _hoops_CAPP _hoops_HPRGR _hoops_RHPP
	_hoops_CPGRR						_hoops_PPHGI;	// _hoops_RGAR _hoops_IH _hoops_ARRS _hoops_HPRGR _hoops_RHPP
	_hoops_CPGRR						_hoops_HPHGI;
	_hoops_CPGRR						_hoops_SAAI;
	_hoops_CPGRR						_hoops_RSASA;
	_hoops_CPGRR						_hoops_IGAPH;

	Lock						_hoops_SSRGI;

#define _hoops_IPHGI			0x00000000
#define _hoops_CPHGI			0x00000001
#define _hoops_SIIPA			0x00000002
#define _hoops_SPHGI			0x00000004
#define _hoops_GHHGI			0x00000008
#define _hoops_RHHGI			0x00000010	// _hoops_AHHGI _hoops_PHHGI
#define _hoops_HHHGI			0x00000020	// _hoops_IHHGI.1
#define _hoops_CHHGI			0x00000040	// _hoops_IHHGI.2
#define _hoops_SHHGI	0x00000080
#define _hoops_GIHGI			0x00010000
#define _hoops_RIHGI		0x00020000
#define _hoops_AIHGI		0x00040000
	int							_hoops_CIIPA;
	int							_hoops_GAGHP;
	int							_hoops_SRGHP;
	unsigned int				_hoops_RCIPA;

	float const *				_hoops_GAIAA;

#define _hoops_CSSPP ((size_t)(~0))
	int							_hoops_HHPAH; //_hoops_PIHGI _hoops_GPP _hoops_AHHS _hoops_RGAR
	size_t						display_list_vram_usage;
	size_t						_hoops_SARH;
	size_t						_hoops_PHARR;
	size_t						vram_size;

	_hoops_RSAHP			_hoops_GGPHP;  //_hoops_GSHHR _hoops_HPP _hoops_SISRP
	_hoops_AGCI *	_hoops_GPAI;  //_hoops_GSHHR _hoops_HPP _hoops_GHIR _hoops_HIHGI


	unsigned int				_hoops_ACPIR;


	_hoops_IAPGI *	_hoops_IIHGI;

	float						_hoops_GCPCR;

	Image *						_hoops_CIHGI;

	char						_hoops_SIHGI[2048];

	User_Option_Compressor *	_hoops_GCHGI;

	int							_hoops_RCHGI;
};


struct _hoops_ACHGI {
	unsigned short				_hoops_CHGCR[8][8];

	int							incr_mod_4[4];
	int							_hoops_PCHGI[8];
	int							_hoops_HCHGI[16];
	short						_hoops_ICHGI[16];
	int							_hoops_CCHGI[64];
	unsigned char				_hoops_SCHGI[256];

	char						_hoops_GCRGI[256];
	float						_hoops_GSHGI[1024];

	float						_hoops_RSHGI[256];

	char const					*_hoops_SAGHP;

	_hoops_ARGRA	_hoops_SRGRA[_hoops_CRGRA];
	_hoops_ARGRA	_hoops_AHGRA[_hoops_GAGRA];
	_hoops_ARGRA	_hoops_APGRA[_hoops_GAGRA];
};

/* _hoops_HRSAR _hoops_RPIHR _hoops_PIH (_hoops_HGPP _hoops_GAR _hoops_SCH _hoops_HRGR) */

#define _hoops_RSPPR(_hoops_RSPGP, _x_) (HOOPS_WORLD->_hoops_SARHP[(_hoops_RSPGP)->_hoops_IAPCR]._x_)

#define _hoops_ASHGI()		(HOOPS_READ_ONLY._hoops_GSHGI[++HOOPS_WORLD->_hoops_CRHGI & 0x3FF])
#define _hoops_PSHGI(x) (HOOPS_READ_ONLY._hoops_RSHGI[_hoops_IRGCR(x)])

INLINE unsigned Integer32 _hoops_HSHGI(unsigned Integer32 v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	v += (v == 0);
	return v;
}




#define _hoops_ISHGI	(POINTER_SIZED_INT)((unsigned POINTER_SIZED_INT)1 << (int)(8 * sizeof (POINTER_SIZED_INT) - 1))
#define _hoops_CSHGI	(POINTER_SIZED_INT)((unsigned POINTER_SIZED_INT)1 << (int)(8 * sizeof (POINTER_SIZED_INT) - 2))

INLINE POINTER_SIZED_INT V2I (void *x) {
	return (POINTER_SIZED_INT)x;
}
INLINE void *I2V (POINTER_SIZED_INT x) {
	return (void *)x;
}


/*** _hoops_IGIPR _hoops_IRS _hoops_CRS _hoops_PAH _hoops_ARCR _hoops_CRGR _hoops_IRS _hoops_HHHR _hoops_RGRRR ***/
#define _hoops_SHSSR				(-1L)

#define _hoops_AIRIR(p)  (HOOPS::Key)((((unsigned POINTER_SIZED_INT)(p))>>2) | _hoops_ISHGI)


INLINE _hoops_HPAH * _hoops_SISIR (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	int alter *				offset = null,
	_hoops_CRCP const *			_hoops_SRCP = null) {

	_hoops_RSIIR(_hoops_RIGC);

	if (offset != null)
		*offset = 0;

	if (key > _hoops_SHSSR)
		key = HI_Key_To_Internal (_hoops_RIGC, key, _hoops_SRCP);
	if (key == _hoops_SHSSR)
		return null;
	if (BIT (key, _hoops_CSHGI)) {
		int		index = ~key;

		if (index >= HOOPS_WORLD->_hoops_GCHCA.count || HOOPS_WORLD->_hoops_GCHCA.table[index].offset < 0)
			return null;
		if (offset != null)
			*offset = HOOPS_WORLD->_hoops_GCHCA.table[index].offset;
		return HOOPS_WORLD->_hoops_GCHCA.table[index].item;
	}
	return (_hoops_HPAH *)(key << 2);
}
INLINE _hoops_HPAH * _hoops_SISIR (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	_hoops_CRCP const *			_hoops_SRCP) 
{
	return _hoops_SISIR (_hoops_RIGC, key, null, _hoops_SRCP);
}

// _hoops_RPAC _hoops_IPI _hoops_RHAP _hoops_HAR _hoops_RGHH _hoops_SHI, _hoops_CPAC _hoops_RRGR _hoops_CGH _hoops_SGH _hoops_RH _hoops_SSHGI _hoops_PSCH
#define _hoops_RCSSR(_hoops_RSPGP, key)				_hoops_SISIR (_hoops_RSPGP, key)






#define _hoops_GGIGI(thread_id, _hoops_RGIGI)		HI_Find_Thread_Specific_Data (thread_id, _hoops_RGIGI)

#define _hoops_HCRGI(_thread_data_) do {								\
			HThreadID _hoops_GGGGI;											\
			_thread_data_ = HOOPS_WORLD->_hoops_SIPGI;									\
			if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP) &&					\
				(_thread_data_->thread_id != (_hoops_GGGGI = THREAD_ID())))	\
				_thread_data_ = _hoops_GGIGI (_hoops_GGGGI, false);			\
		} while (0)

#define _hoops_IIRIR(_thread_data_) do {							\
			HThreadID _hoops_GGGGI;											\
			_thread_data_ = HOOPS_WORLD->_hoops_SIPGI;									\
			if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP) &&					\
				(_thread_data_->thread_id != (_hoops_GGGGI = THREAD_ID())))	\
				_thread_data_ = _hoops_GGIGI (_hoops_GGGGI, true);			\
		} while (0)


#define _hoops_AASAH(_thread_data_, x)	do {			\
			_thread_data_->_hoops_RCSPP = (x);		\
			if (_thread_data_->_hoops_CACAA ==	\
				_thread_data_->_hoops_SACAA) {	\
				_thread_data_->_hoops_SGSAH = -1;		\
				_thread_data_->_hoops_GRSAH = -1;		\
				_thread_data_->_hoops_RRSAH = -1;		\
			}											\
		} while (0)

#define PUSHNAME(_thread_data_)	do {												\
			*_thread_data_->_hoops_CACAA++ = _thread_data_->_hoops_RCSPP;	\
		} while (0)
#define POPNAME(_thread_data_)	do {												\
			_thread_data_->_hoops_RCSPP = *--_thread_data_->_hoops_CACAA;	\
		} while (0)

#ifdef HOOPS_DEBUG_BUILD
#define _hoops_AGIGI
#endif

class _hoops_PAPPR {
private:
	_hoops_AIGPR *	_hoops_RIGC;
#ifdef _hoops_AGIGI
	int _hoops_PGIGI;
	int _hoops_HGIGI; 
#endif

public:
	_hoops_PAPPR (const char * name) {
		_hoops_RIGC = HI_Set_Name(name);
		ASSERT(_hoops_RIGC != null);
		_hoops_IGSCA();
	}

	_hoops_PAPPR (_hoops_AIGPR *	_hoops_SISPP) {
		_hoops_RIGC = _hoops_SISPP;
		ASSERT(_hoops_RIGC != null);
		_hoops_IGSCA();
	}

	~_hoops_PAPPR () {
#ifdef _hoops_AGIGI
		_hoops_HGIGI = _hoops_CSRGI(HOOPS_WORLD->_hoops_SSRGI);
		ASSERT((_hoops_PGIGI & ~(HM_LOCK_STATE_OTHER_SHARED|HM_LOCK_STATE_OTHER_READ|HM_LOCK_STATE_OTHER_WRITE)) == 
			   (_hoops_HGIGI & ~(HM_LOCK_STATE_OTHER_SHARED|HM_LOCK_STATE_OTHER_READ|HM_LOCK_STATE_OTHER_WRITE)));
#endif
		_hoops_RIGC->flags &= ~_hoops_PGPSA;

		if (BIT (HOOPS_WORLD->system_flags, _hoops_HSCPP) &&
			HOOPS_WORLD->_hoops_RAAPH)	 {
			PUSHNAME(_hoops_RIGC); 
			_hoops_AASAH (HOOPS_WORLD->_hoops_PGSCA, "Continuous Update (internal)");
			HI_Do_Update (_hoops_RIGC, -1.0, false);
			POPNAME(_hoops_RIGC);
		}	
	}

	INLINE void _hoops_IGSCA() {
#ifdef _hoops_AGIGI
		_hoops_HGIGI = 0;
		_hoops_PGIGI = _hoops_CSRGI(HOOPS_WORLD->_hoops_SSRGI);	
#endif
	}

	INLINE operator _hoops_AIGPR * () {return _hoops_RIGC;}

	// _hoops_HIS _hoops_SR _hoops_PAH _hoops_ACAPA _hoops_PIH _hoops_IAGH _hoops_SSPP _hoops_GAR _hoops_GGR _hoops_IHRPR _hoops_HRII _hoops_HSAR _hoops_IAGIR _hoops_CPS _hoops_GGR _hoops_ARP/_hoops_CRGH _hoops_PSCH
	INLINE _hoops_AIGPR const *	operator-> () const		{ return _hoops_RIGC; }
	INLINE _hoops_AIGPR alter *	operator-> () alter		{ return _hoops_RIGC; }

private:
	_hoops_PAPPR ();
	_hoops_PAPPR (_hoops_PAPPR const &);
	void operator= (_hoops_PAPPR const &);
};



// _hoops_IGIGI _hoops_RSRA _hoops_PRSAR
#define Sprintf_D(buf,spec,a)	 	HI_Sprintf4(null,buf,spec,a,0,null,null)			//	%_hoops_GHGP, %_hoops_SISR, %_hoops_GCSR	(_hoops_HCR "_hoops_ICHRR" _hoops_SCSH)
#define Sprintf_X(buf,spec,a)	 	HI_Sprintf4(null,buf,spec,0,0,(void*)&a,null)		//	%_hoops_SPCR (_hoops_CRS)
#define _hoops_GRSPR(buf,spec,a)	 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,null)		//	%_hoops_ARGI (_hoops_SIC)
#define Sprintf_F(buf,spec,a)	 	HI_Sprintf4(null,buf,spec,0,0,(void*)&a,null)		//	%_hoops_RCHP (_hoops_AIIC), %_hoops_RCCH (_hoops_GHGPR)
#define Sprintf_S(buf,spec,a)	 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,null)		//	%_hoops_GRI, %_hoops_IISGA (_hoops_CPARA _hoops_RRAI)
#define Sprintf_N(buf,spec,a)	 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,null)		//	%_hoops_ACHP, %_hoops_PGGIR (_hoops_CGIGI _hoops_RPP _hoops_GRH)
#define Sprintf_P(buf,spec,a)	 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,null)		//	%_hoops_CCAHR (_hoops_CAGH _hoops_CRAA)
// _hoops_GRH _hoops_CGIGI _hoops_AGHS (_hoops_PIP: %_hoops_SGIGI _hoops_SSCP _hoops_HAGH _hoops_GRIGI _hoops_IIGR _hoops_GRH _hoops_HSAR %_hoops_PGGIR)
#define _hoops_RRIGI(buf,spec,a)	 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,null)		//	%_hoops_ARIGI (_hoops_GSGR, _hoops_CGIGI _hoops_RPP _hoops_GRH)
#define _hoops_PRIGI(buf,spec,a)	 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,null)		//	%_hoops_SGIGI (_hoops_RSIRR, _hoops_CGIGI _hoops_RPP _hoops_GRH)
// _hoops_RSRA _hoops_ACRGI _hoops_AHIPP _hoops_HSH, _hoops_IIGR _hoops_RGRRR _hoops_PAR _hoops_CRS _hoops_IGIR
#define Sprintf_LD(buf,spec,a)	 	HI_Sprintf4(null,buf,spec,0,0,(void*)&a,null)		//	%_hoops_APCAR (_hoops_RGRRR)
#define _hoops_HRIGI(buf,spec,a)	 	HI_Sprintf4(null,buf,spec,0,0,(void*)&a,null)		//	%_hoops_HAICR (_hoops_CRS _hoops_PAR _hoops_RCGRA)
// 2 _hoops_PRSAR, _hoops_PPCAR _hoops_GGGRR _hoops_IIGR _hoops_IHGP _hoops_RAACR
#define Sprintf_DD(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,a,b,null,null)
#define _hoops_CHCHR(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,a,0,(void*)&b,null)
#define Sprintf_FF(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,0,0,(void*)&a,(void*)&b)
#define Sprintf_SS(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,(void*)b)
#define Sprintf_SD(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,b,0,(void*)a,null)
#define _hoops_SAPRA(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,(void*)&b)
#define Sprintf_SN(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,(void*)b)
#define Sprintf_SP(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,(void*)b)
#define Sprintf_NN(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,(void*)b)
#define _hoops_IRIGI(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,(void*)b)
#define Sprintf_ND(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,b,0,(void*)a,null)
#define Sprintf_NS(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,(void*)b)
#define Sprintf_PP(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,(void*)b)
#define Sprintf_PS(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,(void*)b)
#define Sprintf_PN(buf,spec,a,b) 	HI_Sprintf4(null,buf,spec,0,0,(void*)a,(void*)b)
#define _hoops_CRIGI(buf,spec,a,b)	HI_Sprintf4(null,buf,spec,a,0,(void*)&b,null)

// _hoops_PSHR _hoops_GAR _hoops_ARRS, _hoops_CCA _hoops_HHHA _hoops_ISSSH _hoops_PIH
#define _hoops_RHRHH(_hoops_RSPGP,buf,spec,a)		HI_Sprintf4(_hoops_RSPGP,buf,spec,a,0,null,null)
#define _hoops_SRIGI(_hoops_RSPGP,buf,spec,a)		HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)&a,null)
#define _hoops_GAIGI(_hoops_RSPGP,buf,spec,a)		HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,null)
#define _hoops_HHRHH(_hoops_RSPGP,buf,spec,a)		HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)&a,null)
#define _hoops_GIRHH(_hoops_RSPGP,buf,spec,a)		HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,null)
#define _hoops_PIRHH(_hoops_RSPGP,buf,spec,a)		HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,null)
#define _hoops_RAIGI(_hoops_RSPGP,buf,spec,a)		HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,null)
#define _hoops_AAIGI(_hoops_RSPGP,buf,spec,a)		HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,null)
#define _hoops_PAIGI(_hoops_RSPGP,buf,spec,a)		HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,null)
#define _hoops_RIRHH(_hoops_RSPGP,buf,spec,a)		HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)&a,null)
#define _hoops_CHRHH(_hoops_RSPGP,buf,spec,a)		HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)&a,null)
#define _hoops_PHRHH(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,a,b,null,null)
#define _hoops_HAIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,a,0,(void*)&b,null)
#define _hoops_SPRHH(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)&a,(void*)&b)
#define _hoops_IAIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,(void*)b)
#define _hoops_CAIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,b,0,(void*)a,null)
#define _hoops_SAIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,(void*)&b)
#define _hoops_GPIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,(void*)b)
#define _hoops_RPIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,(void*)b)
#define _hoops_APIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,(void*)b)
#define _hoops_PPIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,(void*)b)
#define _hoops_HPIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,b,0,(void*)a,null)
#define _hoops_IPIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,(void*)b)
#define _hoops_CPIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,(void*)b)
#define _hoops_SPIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,(void*)b)
#define _hoops_GHIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,0,0,(void*)a,(void*)b)
#define _hoops_RHIGI(_hoops_RSPGP,buf,spec,a,b)	HI_Sprintf4(_hoops_RSPGP,buf,spec,a,0,(void*)&b,null)


/* _hoops_AHIGI _hoops_SGGR _hoops_PHIGI! _hoops_HGI _hoops_HRGR _hoops_HAR _hoops_ISSSH-_hoops_ICIC. */
#define _hoops_HHIGI(ref) (++*(_hoops_PHASP alter *)&((ref)->_hoops_HSAI))
#define _hoops_IHIGI(ref) (--*(_hoops_PHASP alter *)&((ref)->_hoops_HSAI))
#define _hoops_CARSH(ref) ((ref)->_hoops_HSAI = 0)

#if defined (_hoops_CHIGI)
#	 define _hoops_CAHS(ref) \
		(_hoops_IGSSH ("+%p %d->%d %s %d\n", (void*)(ref), (ref)->_hoops_HSAI, (ref)->_hoops_HSAI+1, __FILE__, __LINE__),\
		 _hoops_HHIGI(ref))
#	 define _hoops_ISAI(ref) \
		(_hoops_IGSSH ("-%p %d->%d %s %d\n", (void*)(ref), (ref)->_hoops_HSAI, (ref)->_hoops_HSAI-1, __FILE__, __LINE__),\
		 _hoops_IHIGI(ref))
#	 define _hoops_ICAI(ref) (((ref)->_hoops_HSAI = 0), _hoops_CAHS (ref))

#elif defined (VALIDATE_MEMORY)
#	define _hoops_CAHS(ref) ((((ref)->_hoops_HSAI)==0x55555555) ? (HE_ERROR(0, 0, "detected INCR_UTILITY after free")),1 : _hoops_HHIGI(ref))
#	define _hoops_ISAI(ref) ((((ref)->_hoops_HSAI)==0x55555555) ? (HE_ERROR(0, 0, "detected DECR_UTILITY after free")),1 : _hoops_IHIGI(ref))
#	define _hoops_ICAI(ref) ((ref)->_hoops_HSAI = 1)
#else
#	define _hoops_CAHS(ref) _hoops_HHIGI(ref)
#	define _hoops_ISAI(ref) _hoops_IHIGI(ref)
#	define _hoops_ICAI(ref) ((ref)->_hoops_HSAI = 1)
#endif




#define _hoops_CIACR(index)		(&HOOPS_WORLD->_hoops_GSPGI[index])

/* _hoops_RH _hoops_HSPR _hoops_CHH _hoops_HCAGR _hoops_SHH _hoops_GGR _hoops_AARPR._hoops_GGHR, _hoops_HIH _hoops_PPSI _hoops_ARI
 * _hoops_IH _hoops_RH _hoops_SPSIR.
 */
/* _hoops_RGCA _hoops_ARAGP _hoops_CHASR _hoops_AGGPA _hoops_SHIGI! */
typedef int		_hoops_CSSGP;
typedef char	_hoops_GSPAP,
				_hoops_SPGRP;

#define GFN_NONE				(_hoops_CSSGP)0 /* _hoops_IH _hoops_SGH _hoops_GGR _hoops_SPSIR */
#define GFN_SPECIFIED			(_hoops_CSSGP)1
#define GFN_SYSTEM_DEFAULT		(_hoops_CSSGP)2
#define GFN_SANS_SERIF			(_hoops_CSSGP)3
#define GFN_TYPEWRITER			(_hoops_CSSGP)4
#define GFN_ROMAN				(_hoops_CSSGP)5
#define GFN_STROKED				(_hoops_CSSGP)6
#define _hoops_GIIGI		(_hoops_CSSGP)7
#define _hoops_RIIGI		(_hoops_CSSGP)8
#define _hoops_AIIGI			(_hoops_CSSGP)9
#define _hoops_ARHGH			_hoops_AIIGI


#define _hoops_PIIGI		(_hoops_IHGRP)0

#define _hoops_SSAIP	(_hoops_IHGRP)1
#define _hoops_HIIGI		(_hoops_IHGRP)2
#define _hoops_RPHPH			(_hoops_IHGRP)3		/* _hoops_ACIH-_hoops_IIIGI */
#define _hoops_APHPH			(_hoops_IHGRP)4
#define _hoops_RGHPH			(_hoops_IHGRP)5
#define _hoops_SACSR		(_hoops_IHGRP)6
#define _hoops_GSPPH			(_hoops_IHGRP)7
#define _hoops_AGHPH			(_hoops_IHGRP)8
#define _hoops_HSPPH			(_hoops_IHGRP)9
#define _hoops_SSPPH			(_hoops_IHGRP)10
#define _hoops_CSPPH			(_hoops_IHGRP)11
#define _hoops_CIIGI		(_hoops_IHGRP)12

#define _hoops_SIIGI			(_hoops_IHGRP)12

#define _hoops_GCIGI	(int)0
#define _hoops_RCIGI (int)1
#define _hoops_ACIGI (int)2


struct Intersection {
	struct {
		Point const *		start;
		Point const *		end;
		int						_hoops_PCIGI;
		int						_hoops_HCIGI;
		float					_hoops_RCGCR;
	}					_hoops_PICHR[2];
};



#ifndef _hoops_ICIGI
#	define	_hoops_CCIGI	_hoops_SSAIP
#else
#	define	_hoops_CCIGI	_hoops_RPHPH
#endif

#ifdef _hoops_SCIGI
#  ifdef __sparc
#	undef HK_PLATFORM
#	ifdef SOLARIS_SYSTEM
#	  define HK_PLATFORM  "Solaris 2.6 (SunOS 5.6, XGL 3.0.1)"
#	else
#	  define HK_PLATFORM  "SunOS 4.1.3 (XGL 2.0-17)"
#	endif
#  endif
#endif


#define _hoops_IRPPR(part)		HE_ERROR2 (0, 0, HOOPS_READ_ONLY._hoops_SAGHP, part)

#define _hoops_ARPRH() ((_hoops_RRPRH alter *)HOOPS_WORLD->_hoops_SSPGI)



End_HOOPS_Namespace;
Use_HOOPS_Namespace;

#include "hoops_memory.h"


Begin_HOOPS_Namespace




template <typename _hoops_RGHGP, typename _hoops_AGHGP>
struct _hoops_HGHGP : public CMO {
public:
	_hoops_RGHGP *				next;
	_hoops_RGHGP **			backlink;
	_hoops_AGHGP *			owner;
	_hoops_GHRIR					_hoops_HIHI;
	Type					type;
	_hoops_RCCCA			_hoops_RRHH;
};



class _hoops_GSIGI : public CMO {
private:
	mutable int				_hoops_HIHI;

protected:
	_hoops_GSIGI () : _hoops_HIHI (0) {}
	_hoops_GSIGI (_hoops_GSIGI const &) : _hoops_HIHI (0) {}

public:
	INLINE void	retain () const		{ ++_hoops_HIHI; }
	INLINE void	release () const	{ if (--_hoops_HIHI == 0) delete this; }

	INLINE bool	shared () const		{ return _hoops_HIHI > 1; }


private:
	_hoops_GSIGI const &	operator= (_hoops_GSIGI const & x) alter;		// _hoops_PSP _hoops_CHAAR, _hoops_RGAR _hoops_IPS
};


class _hoops_RGCGP : public CMO_Pooled_Copyable {
private:
	mutable int				_hoops_HIHI;

protected:
	_hoops_RGCGP (Memory_Pool * pool) : CMO_Pooled_Copyable(pool), _hoops_HIHI (0) {}
	_hoops_RGCGP (_hoops_RGCGP const & x) : CMO_Pooled_Copyable(x), _hoops_HIHI (0) {}

public:
	INLINE void	retain () const		{ ++_hoops_HIHI; }
	INLINE void	release () const	{ if (--_hoops_HIHI == 0) delete this; }

	INLINE bool	shared () const		{ return _hoops_HIHI > 1; }


private:
	_hoops_RGCGP ();
	_hoops_RGCGP const &	operator= (_hoops_RGCGP const & x) alter;		// _hoops_PSP _hoops_CHAAR, _hoops_RGAR _hoops_IPS
};


template <typename T>
class Counted_Pointer {
protected:
	T *				_hoops_RPPGP;

public:	//_hoops_RSIGI:	// _hoops_ASIGI _hoops_IH _hoops_HA _hoops_HIS _hoops_SR _hoops_PAH _hoops_IIS _hoops_PHHR _hoops_IIGR _hoops_CGSI _hoops_SGS _hoops_CHR _hoops_GGR _hoops_PSIGI (_hoops_HRII _hoops_HSAR _hoops_HSIGI) _hoops_AGRGI
	INLINE void	retain () const		{ if (_hoops_RPPGP != 0) _hoops_RPPGP->retain(); }
	INLINE void	release () const	{ if (_hoops_RPPGP != 0) _hoops_RPPGP->release(); }

public:
	Counted_Pointer () : _hoops_RPPGP (0) {};
	Counted_Pointer (Counted_Pointer const & _hoops_HACIR) : _hoops_RPPGP (_hoops_HACIR._hoops_RPPGP) { retain(); }
	Counted_Pointer (_hoops_GPPGP const &) : _hoops_RPPGP (0) {}
#ifdef null
	Counted_Pointer (int) : _hoops_RPPGP (0) {}
#endif
	~Counted_Pointer () { release(); }

	INLINE Counted_Pointer const &	operator= (Counted_Pointer const & _hoops_HACIR) alter {
		if (_hoops_HACIR._hoops_RPPGP != _hoops_RPPGP) {
			_hoops_HACIR.retain();
			release();
			_hoops_RPPGP = _hoops_HACIR._hoops_RPPGP;
		}
		return *this;
	}
	INLINE Counted_Pointer const &	operator= (_hoops_GPPGP const &) alter {
		release();
		_hoops_RPPGP = 0;
		return *this;
	}
#ifdef null
	INLINE Counted_Pointer const &	operator= (int) alter {
		release();
		_hoops_RPPGP = 0;
		return *this;
	}
#endif

	INLINE bool operator== (Counted_Pointer const & _hoops_HACIR) const { return _hoops_RPPGP == _hoops_HACIR._hoops_RPPGP; }
	INLINE bool operator!= (Counted_Pointer const & _hoops_HACIR) const { return _hoops_RPPGP != _hoops_HACIR._hoops_RPPGP; }
	INLINE bool operator== (_hoops_GPPGP const &) const { return _hoops_RPPGP == 0; }
	INLINE bool operator!= (_hoops_GPPGP const &) const { return _hoops_RPPGP != 0; }
#ifdef null
	INLINE bool operator== (int) const { return _hoops_RPPGP == 0; }
	INLINE bool operator!= (int) const { return _hoops_RPPGP != 0; }
#endif
	INLINE bool operator! () const { return _hoops_RPPGP == 0; }
	INLINE operator bool () const { return _hoops_RPPGP != 0; }

	static Counted_Pointer Create () {
		Counted_Pointer		temp;
		typedef T _hoops_ISIGI;
		temp._hoops_RPPGP = NEW(_hoops_ISIGI)();
		temp->retain();
		return temp;
	}
	INLINE Counted_Pointer Copy () const {
		Counted_Pointer		temp;
		typedef T _hoops_ISIGI;
		temp._hoops_RPPGP = NEW(_hoops_ISIGI)(*_hoops_RPPGP);
		temp->retain();
		return temp;
	}


	INLINE void	_hoops_SSAGR () const {
		HOOPS::_hoops_SSAGR(_hoops_RPPGP);
	}

	// _hoops_HIS _hoops_SR _hoops_PAH _hoops_ACAPA _hoops_PIH _hoops_IAGH _hoops_SSPP _hoops_GAR _hoops_GGR _hoops_IHRPR _hoops_HRII _hoops_HSAR _hoops_IAGIR _hoops_CPS _hoops_GGR _hoops_ARP/_hoops_CRGH _hoops_PSCH
	INLINE T const *	operator-> () const		{ return _hoops_RPPGP; }
	INLINE T alter *	operator-> () alter		{ return _hoops_RPPGP; }
};


template <typename T>
class _hoops_AGCGP : public Counted_Pointer<T> {
	typedef		Counted_Pointer<T>		CP;		// _hoops_PPIHR _hoops_RSIRR _hoops_HIS _hoops_RRGR _hoops_HRGR _hoops_SRRAH

private:
	static _hoops_AGCGP Create ();

public:
	_hoops_AGCGP () : CP () {};	// _hoops_SIGR _hoops_PGGA _hoops_RH _hoops_SPS _hoops_SPR _hoops_HRGR _hoops_SIGR...
	// _hoops_AGCR _hoops_GA'_hoops_RA _hoops_CAPGP _hoops_GAR _hoops_SIGR _hoops_SAPGP _hoops_IS _hoops_RH _hoops_CGRIR _hoops_GPRR _hoops_IIGR _hoops_RH _hoops_GHPP
	_hoops_AGCGP (_hoops_GPPGP const &) : CP () {}
	_hoops_AGCGP const &	operator= (_hoops_GPPGP const &) alter {
		CP::release();
		CP::_hoops_RPPGP = 0;
		return *this;
	}
#ifdef null
	_hoops_AGCGP (int) : CP () {}
	INLINE _hoops_AGCGP const &	operator= (int) alter {
		CP::release();
		CP::_hoops_RPPGP = 0;
		return *this;
	}
#endif

	static _hoops_AGCGP	Create (Memory_Pool * pool) {
		_hoops_AGCGP		temp;
		typedef T _hoops_CSIGI;
		temp._hoops_RPPGP = POOL_NEW(pool, _hoops_CSIGI) (pool);
		temp->retain();
		return temp;
	}
	INLINE _hoops_AGCGP & Modify () alter {
		if (CP::_hoops_RPPGP->shared()) {
			typedef T _hoops_CSIGI;
			T *	temp = POOL_NEW(CP::_hoops_RPPGP->memory_pool, _hoops_CSIGI)(*CP::_hoops_RPPGP);
			CP::release();
			CP::_hoops_RPPGP = temp;
			CP::retain();
		}
		return *this;
	}
	INLINE _hoops_AGCGP Copy () const {
		_hoops_AGCGP		temp;
		typedef T _hoops_CSIGI;
		temp._hoops_RPPGP = POOL_NEW(CP::_hoops_RPPGP->memory_pool, _hoops_CSIGI)(*CP::_hoops_RPPGP);
		temp->retain();
		return temp;
	}
};


class _hoops_CPASP : public _hoops_RGCGP {
public:
	Display_Context const *	_hoops_SRA;
	int						_hoops_CPA;

protected:
	HOOPS_API _hoops_CPASP (Display_Context const *);
	HOOPS_API _hoops_CPASP (_hoops_CPASP const &);


private:
	_hoops_CPASP();		// _hoops_PSP _hoops_SHIR
};


// _hoops_PAGA: _hoops_SSIGI _hoops_HICA _hoops_PAH'_hoops_RA _hoops_AHGS _hoops_IS _hoops_PRRHP _hoops_PA _hoops_SGS _hoops_GGCGI _hoops_RGCGI _hoops_HII _hoops_AGCGI
// _hoops_SIHH _hoops_GRGA _hoops_PGCGI _hoops_CPS
template <typename T>
class Rendition_Pointer : public Counted_Pointer<T> {
	typedef		Counted_Pointer<T>		CP;		// _hoops_PPIHR _hoops_RSIRR _hoops_HIS _hoops_RRGR _hoops_HRGR _hoops_SRRAH

private:
	static Rendition_Pointer Create ();

public:
	Rendition_Pointer () : CP () {};	// _hoops_SIGR _hoops_PGGA _hoops_RH _hoops_SPS _hoops_SPR _hoops_HRGR _hoops_SIGR...
	// _hoops_AGCR _hoops_GA'_hoops_RA _hoops_CAPGP _hoops_GAR _hoops_SIGR _hoops_SAPGP _hoops_IS _hoops_RH _hoops_CGRIR _hoops_GPRR _hoops_IIGR _hoops_RH _hoops_GHPP
	Rendition_Pointer (_hoops_GPPGP const &) : CP () {}
	Rendition_Pointer const &	operator= (_hoops_GPPGP const &) alter {
		CP::release();
		CP::_hoops_RPPGP = 0;
		return *this;
	}
#ifdef null
	Rendition_Pointer (int) : CP () {}
	INLINE Rendition_Pointer const &	operator= (int) alter {
		CP::release();
		CP::_hoops_RPPGP = 0;
		return *this;
	}
#endif
	INLINE Rendition_Pointer Copy () const {
		Rendition_Pointer		temp;
		temp._hoops_RPPGP = POOL_NEW(CP::_hoops_RPPGP->memory_pool, T)(*CP::_hoops_RPPGP);
		temp->retain();
		return temp;
	}

	static Rendition_Pointer	Create (Display_Context const * dc);

	INLINE Rendition_Pointer &			Modify (int offset = 0) alter;
	INLINE Rendition_Pointer &			Renew () alter;
};





typedef float _hoops_RPRA[4];
typedef unsigned char Matrix_Flags;
typedef unsigned char Matrix_Contents;

struct _hoops_HGCGI;
typedef	_hoops_AGCGP<_hoops_HGCGI>		_hoops_CRSPA;

struct _hoops_HRPA {
	mutable	_hoops_CRSPA		_hoops_APRA;

	_hoops_RPRA			elements[4];
	float				_hoops_CPH;

#	define _hoops_SGICR			(Matrix_Contents)0x00
#	define _hoops_GRICR		(Matrix_Contents)0x01
#	define _hoops_CHCP		(Matrix_Contents)0x02
#	define _hoops_PRICR	(Matrix_Contents)0x04
#	define _hoops_HRICR	(Matrix_Contents)0x08
#	define _hoops_RRICR			(Matrix_Contents)0x10
#	define _hoops_CASA		(Matrix_Contents)0x20 /* _hoops_RGAR _hoops_IGCGI _hoops_GGR _hoops_PPAC _hoops_RGHSH */
#	define _hoops_CICH		(Matrix_Contents)0x3F
	Matrix_Contents		_hoops_RAGR;

#	define _hoops_HASA			(Matrix_Flags)0x01
	Matrix_Flags		flags;

	INLINE bool _hoops_PPGH() const {
		return !ANYBIT (_hoops_RAGR, _hoops_CICH);
#if 0
		local int _hoops_CGCGI(float *matrix) {
			float _hoops_SGCGI[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
			int i;

			if (matrix == null)
				return 1;

			for (i = 0; i < 16; i++)
				if (_hoops_SGCGI[i] != matrix[i])
					return 0;
			return 1;
		}
#endif
	}
};

struct _hoops_HGCGI : public _hoops_RGCGP {
	_hoops_HRPA			data;

public:
	_hoops_HGCGI (Memory_Pool * memory_pool)
		: _hoops_RGCGP (memory_pool) {
			data.elements[0][0] =
				data.elements[1][1] =
				data.elements[2][2] =
				data.elements[3][3] = 1.0f;
			data._hoops_CPH = 1.0f;
	}
};


typedef int	_hoops_IPRRA;

typedef Integer32 _hoops_RIARP;

struct _hoops_SHCGP;
typedef	_hoops_AGCGP<_hoops_SHCGP>	_hoops_GPAGR;

End_HOOPS_Namespace;
Use_HOOPS_Namespace;

GLOBAL_DATA	_hoops_ACHGI		HOOPS_READ_ONLY;

#endif


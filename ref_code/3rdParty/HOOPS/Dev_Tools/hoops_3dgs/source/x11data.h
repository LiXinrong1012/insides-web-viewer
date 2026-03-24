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
 * $Id: obf_tmp.txt 1.164 2010-07-17 06:23:29 jason Exp $
 */

#ifndef X11DATA_DEFINED

/*		_hoops_ARHHGR _hoops_PRHHGR _hoops_IRAGP _hoops_HII _hoops_HRHHGR._hoops_GSGGR _hoops_IS _hoops_APAPC._hoops_GGHR.
 *
 *		_hoops_IRHHGR _hoops_HRGR _hoops_RIHGH _hoops_RH _hoops_GPAAC _hoops_SCPPGR _hoops_IS _hoops_SCCHH _hoops_RPP _hoops_RH
 *		_hoops_AGAH _hoops_SPPPR _hoops_HRGR _hoops_AGRRR _hoops_PAR _hoops_CRHHGR _hoops_GPP _hoops_HHH _hoops_AAPGH.
 *		_hoops_IPCP _hoops_ARPC _hoops_SSCP _hoops_RPII _hoops_SRHHGR _hoops_GGR _hoops_PCCP _hoops_HCCSS _hoops_SCPCR _hoops_APACA _hoops_SPCR
 *		_hoops_SPPPR _hoops_PPR _hoops_SSCP _hoops_RPII _hoops_PIIRH _hoops_IS _hoops_IRPR _hoops_AICGC.
 *		_hoops_GAHHGR _hoops_SR _hoops_HGRAI _hoops_IRS _hoops_HGIHR _hoops_IH _hoops_RH _hoops_SCPPGR _hoops_SCCHH _hoops_SR _hoops_GRS _hoops_SGH
 *		_hoops_RSAPGR _hoops_GHGPR _hoops_RHGPR (_hoops_CAS _hoops_IRPR).
 *		_hoops_RCPA _hoops_HHPR _hoops_RSAPGR _hoops_GHGPR _hoops_RHGPR _hoops_SAHR _hoops_PPIP
 *						  #		  _hoops_PPIP				_hoops_ICAPGR
 *		_hoops_IH _hoops_RH _hoops_GHARR _hoops_CAPP (_hoops_RPP _hoops_HAR _hoops_AIAH _hoops_GPRI).
 */


#define Window X_Window
#define _hoops_PGIIR X_Font
#define Drawable X_Drawable
#define _hoops_RAAH X_Depth
#define _hoops_GSPGR X_Time

#ifdef NUTCRACKER
# define XK_MISCELLANY
# define XK_LATIN1
# include <keysymdef.h>
#endif

#ifdef _hoops_CISPGR
#include <X11/extensions/XInput.h>
#endif



#ifdef _hoops_RAHHGR
#		ifdef HPUX_SYSTEM
#				include <X11/PEX5/PEXlib.h>
#		else
#				include <PEX5/PEXlib.h>
#		endif /* _hoops_RHSAI */
#endif /* _hoops_AAHHGR */

#ifdef _hoops_ICIGI
#		include <X11/XJplib.h>
#endif /* _hoops_ARSPGR */

/*		_hoops_CSH _hoops_IRHHGR _hoops_GCGH _hoops_HRGR _hoops_HHPA _hoops_GPP _hoops_RGR _hoops_PHIAH */
#ifdef AIX_SYSTEM
#		define X11R5
#		ifndef NeedFunctionPrototypes
#				define NeedFunctionPrototypes 1
#		endif /* _hoops_PAHHGR */
#		include <X11/Xlib.h>
#		include <X11/X.h>
#		include <X11/keysym.h>
#		include <X11/Xutil.h>
#		define Multibuffer int
#		define _hoops_GIAPGR
#		define MultibufferUpdateActionUntouched 1
#		define MultibufferUpdateHintFrequent 2
#		define XmbufBufferInfo int*
#endif /* _hoops_ICAPR */

#ifdef HPUX_SYSTEM
#		define			X11R5
#		define NeedFunctionPrototypes 1
#		include <X11/Xlib.h>
#		include <X11/X.h>
#		include <X11/keysym.h>
#		include <X11/Xutil.h>
#ifdef __LP64__
#		define _hoops_GIAPGR
#				define XmbufGetScreenInfo _hoops_HAHHGR
#				define XmbufQueryExtension _hoops_IAHHGR
#				define XmbufCreateBuffers _hoops_CAHHGR
#				define XmbufDisplayBuffers _hoops_SAHHGR
#				define XmbufDestroyBuffers _hoops_GPHHGR
#		include <X11/extensions/multibuf.h>
#				undef XmbufGetScreenInfo
#				undef XmbufQueryExtension
#				undef XmbufCreateBuffers
#				undef XmbufDisplayBuffers
#				undef XmbufDestroyBuffers
#				define XmbufGetScreenInfo XmbufGetScreenInfo
#				define XmbufQueryExtension XmbufQueryExtension
#				define XmbufCreateBuffers XmbufCreateBuffers
#				define XmbufDisplayBuffers XmbufDisplayBuffers
#				define XmbufDestroyBuffers XmbufDestroyBuffers
#else
#		include <X11/extensions/multibuf.h>
#endif
#endif /* _hoops_RHSAI */

#ifdef _hoops_PPCSH
#		define			X11R5
#		ifndef NeedFunctionPrototypes
#				define NeedFunctionPrototypes 1
#		endif /* _hoops_PAHHGR */
#		include <X11/Xlib.h>
#		include <X11/X.h>
#		include <X11/keysym.h>
#		include <X11/Xutil.h>
#		include <X11/extensions/multibuf.h>
#endif /* _hoops_GCAPGR */

#ifdef IRIX_SYSTEM
#		define			X11R4
#		define NeedFunctionPrototypes 1
#		include <X11/Xlib.h>
#		include <X11/X.h>
#		include <X11/keysym.h>
#		include <X11/Xutil.h>
#ifdef MISSING_MBUF
				/*_hoops_RPHPI _hoops_RHSI _hoops_RPHHGR._hoops_GGHR _hoops_GGR _hoops_GRCHH 6.5 _hoops_IH _hoops_HHH _hoops_SCPC*/

#				define Multibuffer int
#				define _hoops_GIAPGR
#				define MultibufferUpdateActionUntouched 1
#				define MultibufferUpdateHintFrequent 2
#				define XmbufBufferInfo int* 
#else
#				include <X11/extensions/multibuf.h>
#endif /*_hoops_APHHGR*/
#endif /* _hoops_SSHPI */

#ifdef SOLARIS_SYSTEM
#		define			X11R4
#		ifndef NeedFunctionPrototypes
#				define NeedFunctionPrototypes 1
#		endif /* _hoops_PAHHGR */
#		include <X11/Xlib.h>
#		include <X11/X.h>
#		include <X11/keysym.h>
#		include <X11/Xutil.h>
#ifdef MISSING_MBUF
#				define Multibuffer int
#				define _hoops_GIAPGR
#				define MultibufferUpdateActionUntouched 1
#				define MultibufferUpdateHintFrequent 2
#				define XmbufBufferInfo int*
#else
#		include <X11/extensions/multibuf.h>
#endif /*_hoops_APHHGR*/
#endif /* _hoops_SPPHS */

#ifdef _hoops_PPHHGR
#		define			X11R4
#		define NeedFunctionPrototypes 1
#		include <X11/Xlib.h>
#		include <X11/X.h>
#		include <X11/keysym.h>
#		include <X11/Xutil.h>
#		include <X11/extensions/multibuf.h>
#endif /* _hoops_HPHHGR */

#ifdef LINUX_SYSTEM
#		define	X11R5
#		define NeedFunctionPrototypes 1
#		include <X11/Xlib.h>
#		include <X11/X.h>
#		include <X11/keysym.h>
#		include <X11/Xutil.h>
#		include <X11/extensions/multibuf.h>
#endif /* _hoops_PHCPI */

#ifdef OSX_SYSTEM
#		define	X11R5
#		define NeedFunctionPrototypes 1
#		include <X11/Xlib.h>
#		include <X11/X.h>
#		include <X11/keysym.h>
#		include <X11/Xutil.h>
#		include <X11/extensions/multibuf.h>
#endif /* _hoops_PHCPI */

#ifdef VMS_SYSTEM
#		include <decw$include:X.h>
#		include <decw$include:Xlib.h>
#		include <decw$include:keysym.h>
#		include <decw$include:Xutil.h>
#		include <decw$include:Xresource.h>
#		ifdef _hoops_HPCSH
#				define _hoops_GIAPGR
#				include <sys$sysroot:[decw$include.extensions]multibuf.h>
#		else
#				include <decw$include:multibuf.h>
#		endif
#endif /* _hoops_SGGHGR */

#ifdef NUTCRACKER
# include <Xlib.h>
# include <driver.h>
# include <Xutil.h>
#ifdef EXCEED_BUILD
# include <multibuf.h>
#else
#define Multibuffer int
#endif
#endif /* _hoops_IGCAGR */


/*
 *		_hoops_IPHHGR _hoops_IGI _hoops_IS _hoops_CRGS _hoops_IHHH _hoops_PGAP _hoops_GPAAC _hoops_HHSPC _hoops_SR _hoops_CHR _hoops_GRP.
 */
#define _hoops_PSRHGR					0

#define _hoops_ACRHGR				1

#define _hoops_CPHHGR				9
#define _hoops_SPHHGR				10
#define _hoops_GHHHGR				11
#define _hoops_RHHHGR				12
#define _hoops_AHHHGR				13

#define _hoops_PHHHGR					20
#define _hoops_HHHHGR				21
#define _hoops_IHHHGR					22
#define _hoops_CHHHGR					23

#define _hoops_SHHHGR					29
#define _hoops_GIHHGR				30
#define _hoops_RIHHGR				31
#define _hoops_AIHHGR				32
#define _hoops_PIHHGR				33
#define _hoops_HIHHGR				34
#define _hoops_IIHHGR				35

#define _hoops_SHGHGR					39
#define _hoops_CIHHGR				40
#define _hoops_SIHHGR				41
#define _hoops_GCHHGR				42

#define _hoops_AAPHGR					49
#define _hoops_RCHHGR				50
#define _hoops_ACHHGR				51
#define _hoops_PCHHGR				52
#define _hoops_HCHHGR				53
#define _hoops_ICHHGR				54

#define _hoops_CCHHGR					59
#define _hoops_SCHHGR				60
#define _hoops_GSHHGR				61
#define _hoops_RSHHGR				62
#define _hoops_PPHPGR				63

#define _hoops_PAPHGR					64
#define _hoops_ASHHGR					65

/*
 *		_hoops_IPHHGR _hoops_IGI _hoops_IS _hoops_CRGS _hoops_IHHH _hoops_PGAP _hoops_IRISR _hoops_SCHGR _hoops_SR _hoops_CHR _hoops_GRP.
 */
#define X11_ONLY				0
#define _hoops_HRPHGR				1
#define XGL_ON_X11				2
#define GL_ON_X11				3
#define _hoops_PCGHGR 4
#define _hoops_PPAPC	5


#ifdef _hoops_ICIGI
		typedef struct _hoops_PSHHGR {
				struct _hoops_PSHHGR	*next;
				long					id;
				char					*name;
		} Xftab;
#endif

#define _hoops_GAAPC 200

typedef struct {
		/* _hoops_IRISR _hoops_SCHGR _hoops_GGR _hoops_SGH */
		int										driver_type;

		/* _hoops_GPAAC _hoops_HHSPC _hoops_RCHSP */
		Display alter			*display;
		Screen alter			*screen;
		Visual alter			*visual;
												/* _hoops_GPAAC _hoops_HHSPC _hoops_RIAGI */
		int										_hoops_APHPGR;

												/* _hoops_SIGR _hoops_IS _hoops_SSS _hoops_GGSR _hoops_GSIA _hoops_IHAHP */
		char							_hoops_IPHIH[_hoops_GAAPC];

		bool						_hoops_PHAPC;
		Window							_hoops_RHSPC;

#		ifdef AIX_SYSTEM
												/* _hoops_SIGR _hoops_IS _hoops_SSS _hoops_GGSR _hoops_RPP _hoops_SR _hoops_CHR _hoops_GPP _hoops_HSHHGR */
				char					_hoops_SPSPGR[32];
#		endif

		/* _hoops_ISSC _hoops_AGGAR _hoops_IH _hoops_RIHH _hoops_PRCA */
		Display_Context		*dc;

		/* _hoops_SPHGR _hoops_PPR _hoops_PGRR */
		Window							window,
												_hoops_IRSPGR,
												_hoops_CISPC;
		char							_hoops_IAPIR[4096];
		int										window_x,
												window_y,
												_hoops_PGRHGR,
												_hoops_HGRHGR;
		unsigned int			window_width,
												window_height;

		/* _hoops_HCISR _hoops_IIHGC _hoops_PPR _hoops_ISIS */
		GC										_hoops_AAPPGR,
												_hoops_PPPPGR,
												_hoops_ISHPGR,
												_hoops_PHPPGR,
												_hoops_GRPHGR,
												_hoops_IHHPGR,
												_hoops_CHHPGR,
												_hoops_AHPPGR;

		_hoops_GARRR			_hoops_SAICC,
												_hoops_HPPPGR,
												_hoops_HSHPGR,
												_hoops_SHHPGR;

		_hoops_GARRR			_hoops_GAHPGR,
												_hoops_HAHPGR,
												_hoops_CSHPGR,
												_hoops_HHPPGR,
												_hoops_GIHPGR,
												_hoops_GPHPGR;

		/* _hoops_CPHSR _hoops_API _hoops_CICRR */
		void							(*_hoops_PRAPC)(Display_Context alter *dc),
												(*_hoops_SRAPC)(Display_Context const *dc),
												(*_hoops_AAAPC)(Display_Context const *dc),
												(*_hoops_PAAPC)(Display_Context const *dc);

		/* _hoops_HRCSR _hoops_API _hoops_CICRR */
		void							(*_hoops_IACPGR)(Display_Context alter *dc),
												(*_hoops_HACPGR)(Display_Context alter *dc);

		bool						(*_hoops_PGCPGR)(Display_Context alter *dc,char const *name);
		char							_hoops_ISIPGR[5];

		/* _hoops_CCAH _hoops_IPP _hoops_API _hoops_CICRR, _hoops_ARP _hoops_IIHA _hoops_GPP _hoops_RAHRH _hoops_GPRR */
		bool						(*_hoops_IAGGS)(Net_Rendition const & nr,
																						  Driver_Color const *_hoops_RSISR);
		bool						(*_hoops_RHPPGR)(Net_Rendition const & nr,
																										Driver_Color const *_hoops_RSISR);

		/* _hoops_PS _hoops_ISHHGR _hoops_RH _hoops_SPS _hoops_PCPH _hoops_PGGA _hoops_CSHHGR _hoops_SSSCP _hoops_RGHH _hoops_RH _hoops_ACGIA */
		void							(*_hoops_CSASR)(Net_Rendition const & nr,
																						   XGCValues alter *_hoops_RGPPGR,
																						   Driver_Color const *_hoops_SHRIC,
																						   Driver_Color const *_hoops_AGPPGR);

		/* _hoops_GHGPR-_hoops_RHGPR _hoops_CCPAR */
		Drawable						_hoops_SRASH;
		bool						_hoops_SPGHGR,
												_hoops_PCSPGR,
												_hoops_SSSGP,
												_hoops_PSAPGR;
		Multibuffer						_hoops_HCSPGR[2];
		Pixmap							_hoops_CCSPGR;
		int										_hoops_ICSPGR,
												_hoops_HSAPGR,
												_hoops_ISAPGR,
												_hoops_CSAPGR,
												_hoops_SSAPGR;
		long							_hoops_RACSH;
		XPoint			  alter *_hoops_RAHPGR;

		/* _hoops_HAIR _hoops_GHCS _hoops_CCPAR */
		unsigned long alter *_hoops_SRPPGR;
		Colormap						_hoops_GPIHP,
												_hoops_IAIPGR;
												/* # _hoops_IIGR _hoops_GHC (_hoops_RIR _hoops_HAIR, _hoops_RPP _hoops_PPPSR) */
		int										_hoops_CRAPC;
		bool						_hoops_HISPGR;
		int										_hoops_GAPPGR;
												/* # _hoops_SSHHGR _hoops_IIGR _hoops_RGR _hoops_RPPS */
		int										depth;

		/* _hoops_RPHPGR */
		Pixmap							stipples[TOTAL_BIT_PATTERNS];

		/* _hoops_CHIAR _hoops_HCGR */
		Pixmap							bitmap;
		int										_hoops_PSHPGR;
		char alter						*_hoops_SIRRC;

		/* _hoops_CSCR _hoops_CRPR _hoops_PIH */
#		define _hoops_SHPPGR						0x01
#		define _hoops_GIPPGR			0x02
		int										_hoops_IHPPGR;

#		define _hoops_RCPPGR			0
#		define _hoops_ACPPGR			1
#		define _hoops_PCPPGR			2
#		define _hoops_HCPPGR			3
#		define _hoops_ICPPGR			4
#		define _hoops_GGIHGR			5
		int										_hoops_GCPPGR;
												/* _hoops_ACHP _hoops_SISR 1 _hoops_CSCR */
		XImage alter			*_hoops_CHPPGR;
												/* _hoops_ACHP _hoops_SISR _hoops_SPHAI _hoops_CSCR */
		XImage alter			*_hoops_SIPPGR;
		RGBAS32		alter	*_hoops_PHGH;
		int										_hoops_PASIH;
												/* _hoops_IH _hoops_GSGHGR _hoops_AIHSR'_hoops_GRI */
		bool						_hoops_HGPPGR;
		unsigned char			_hoops_RRHPGR[_hoops_HIRSP];
		unsigned char alter *_hoops_SGHPGR;
		int										_hoops_GRHPGR;
		unsigned short			_hoops_HRHPGR[_hoops_HIRSP],
												*_hoops_ARHPGR;
		int										_hoops_PRHPGR;

				/*_hoops_CSCR _hoops_SRSRR _hoops_PAH _hoops_SHH _hoops_CHPCI _hoops_ARI _hoops_HIH _hoops_GA'_hoops_RA _hoops_SHAC*/
				/*_hoops_SCH'_hoops_GRI _hoops_RCRAR*/
#				define _hoops_HSPPGR 2
#				define _hoops_ISPPGR 512
				XImage alter	*_hoops_SSPPGR[_hoops_HSPPGR][_hoops_ISPPGR];

		/* _hoops_GISAP _hoops_PRCA */
		int										yfudge;
		int										_hoops_SCGRR,
												mouse_y,
												_hoops_HRRRR;
		bool						_hoops_IRRRR;
		int										_hoops_ISCPGR;

		/* _hoops_GGRRR _hoops_SSGHGR */
		bool						_hoops_HCRHGR,
												_hoops_ICRHGR;

		/*
		 *		_hoops_RACCI _hoops_IS _hoops_CRHR _hoops_RGIHGR _hoops_HCPH _hoops_IS _hoops_PCASS-_hoops_HAIR-_hoops_ARCR _hoops_GGR _hoops_RPIPGR
		 *		_hoops_PAR _hoops_GSSC - _hoops_HAR _hoops_IGI _hoops_PAR _hoops_SIGR _hoops_GGR _hoops_AGIHGR _hoops_PAR _hoops_PHPA.
		 */
		bool						_hoops_SAIPGR,
												_hoops_GPIPGR;

		/* _hoops_ASSS _hoops_CCCSI _hoops_IS _hoops_PCCS _hoops_CGSI */
		bool						_hoops_CCRHGR;

		/* _hoops_RIP _hoops_IH _hoops_PCCS _hoops_PGRRR _hoops_IRPSP */
		bool						_hoops_RISPGR;

		/* _hoops_RIP _hoops_IS _hoops_IRHC _hoops_CGPR _hoops_GACHS() _hoops_CSAP _hoops_PIGS _hoops_IH _hoops_IRS _hoops_RPPS */
		bool						_hoops_ASAHGR;

		/* _hoops_RIP _hoops_IS _hoops_CCPH _hoops_HISRA _hoops_IIPR */
		bool						_hoops_IPSPGR;

		/* _hoops_PIH _hoops_IH _hoops_IHHH _hoops_IS _hoops_SGH _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_HPSSA _hoops_SAIGS. */
#		define _hoops_RGSPGR											(0)
#		define _hoops_SCCPGR							(-1)
		int										_hoops_HCCPGR;
		bool						_hoops_SSCPGR;

#		ifdef _hoops_ICIGI
				Xftab					*start;
				bool				_hoops_PGIHGR;
				unsigned long	_hoops_HHAHGR;
				unsigned long	values;
#		endif /* _hoops_ARSPGR */

#		ifdef AIX_SYSTEM
				/* _hoops_HIRPR _hoops_SGPSI _hoops_RIP _hoops_IH _hoops_IIIGC _hoops_GPP _hoops_GPAAC.  _hoops_AIHH _hoops_HGIHGR _hoops_GGR _hoops_GPAAC _hoops_SCHGR. */
				bool				_hoops_RCSPGR;
#		endif /* _hoops_ICAPR */


				/*_hoops_PCRHGR _hoops_SCPGH*/
		/* _hoops_SGH _hoops_PHIGR _hoops_GCRSS _hoops_IH _hoops_GGSC (_hoops_PCIC _hoops_AHPH _hoops_CRRPR) */
		void alter						*context;

		/* _hoops_SIGR _hoops_IH _hoops_IGIHGR */
		XVisualInfo alter		*_hoops_CAAAC;

				/* _hoops_GPP _hoops_CGIHGR, _hoops_SR _hoops_RRP _hoops_RGR _hoops_IS _hoops_ARP _hoops_RGR _hoops_IS _hoops_SGIHGR */
				bool								  first;

				 /* _hoops_HIHH _hoops_RHPP _hoops_GRS _hoops_CAHA _hoops_GGSR _hoops_RH _hoops_HIGR _hoops_HIH _hoops_GPAAC _hoops_RHPP*/
				 /* _hoops_GRS _hoops_SGH _hoops_SCH _hoops_IS _hoops_SSS _hoops_RH _hoops_AAH _hoops_RAHRH.*/
				int alter								*_hoops_HPAPC;
				/*_hoops_RGR _hoops_HRGR _hoops_ARI _hoops_IS _hoops_IHIS _hoops_IPAPC _hoops_HCPH _hoops_GGSR _hoops_IIGR _hoops_RH _hoops_CPAPC _hoops_RHPP*/
				void (*_hoops_IAAPC)(Display_Context const *dc);

		/* _hoops_SRCH _hoops_PGIAS _hoops_RHIR _hoops_PPCIA/_hoops_RIIRH */
		bool						_hoops_HPSPGR;

				/*_hoops_HIGGR _hoops_PCRHGR _hoops_SCPGH*/

		/* _hoops_SIHC _hoops_SIGR _hoops_IS _hoops_SICR _hoops_GAPA _hoops_ISCP _hoops_HAIR _hoops_PPR _hoops_ACGHGR _hoops_RAHRH _hoops_HAIR */
		unsigned int _hoops_SGPPGR;
		int _hoops_CGPPGR;
		unsigned int _hoops_RRPPGR;
		int _hoops_GRPPGR;
		unsigned int _hoops_PRPPGR;
		int _hoops_ARPPGR;
} X11Data;


/*
 *		_hoops_HGI _hoops_HRPR _hoops_SAPCC _hoops_GAPA _hoops_HHCAC _hoops_IRISR _hoops_PPR _hoops_GPAAC _hoops_GSPIP, _hoops_HIS _hoops_SGS
 *		_hoops_RH _hoops_IIGCR _hoops_SPSIR _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_GPAAC _hoops_PAH _hoops_ASH _hoops_RRI _hoops_SIHC _hoops_AHCA _hoops_GSPIP.
 */
typedef struct	_hoops_GRIHGR {
		XFontStruct *_hoops_HSRPC;						/* _hoops_CRS _hoops_IS _hoops_GPAAC _hoops_HRCSR	*/

		/* _hoops_HRGSI _hoops_GAS _hoops_IASC _hoops_AHCRR _hoops_GRPAR */
		int						lbearing,				/* _hoops_RAAP-_hoops_ICRP _hoops_CRRPA _hoops_HII _hoops_CGRS */
								rbearing,				/* _hoops_RPHR-_hoops_ICRP _hoops_CRRPA _hoops_HII _hoops_CGRS */
								ascent,					/* _hoops_GPSGR _hoops_CRRPA _hoops_ARRS _hoops_CGRS */
								descent;				/* _hoops_ISPP _hoops_CRRPA _hoops_CAPP _hoops_CGRS */

		void alter		*_hoops_CSSGA;				/* _hoops_RPP _hoops_ASAI _hoops_IRAP, _hoops_RH _hoops_HRCSR _hoops_HRGR _hoops_HAR _hoops_PCCP _hoops_GPAAC _hoops_HRCSR */
																/* _hoops_RH _hoops_PIH _hoops_HRGR _hoops_RHPP _hoops_AAR */
		int alter		*_hoops_RRIHGR;
} _hoops_GSRPC;

/*
 * _hoops_IS _hoops_GRHP _hoops_IHGC _hoops_IIGR _hoops_SSHGR _hoops_GPP _hoops_IRS _hoops_RIR-_hoops_RPPS _hoops_HARGR
 */

struct X11_Event_Info {
		X11_Event_Info *		next;
		Display_Context *		dc;
		X11Data *				_hoops_RRRPC;
		bool					_hoops_GHSPGR;
		bool					_hoops_RHSPGR;
		bool					_hoops_CGRRR;
		bool					_hoops_AHSPGR;
		Int_Rectangle			_hoops_PISPGR;
		int						_hoops_PHSPGR;
		int						_hoops_HHSPGR;
		int						_hoops_IHSPGR;
		int						_hoops_CHSPGR;
};


#undef Window 
#undef _hoops_PGIIR
#undef Drawable
#undef _hoops_RAAH
#undef _hoops_GSPGR 



#define X11DATA_DEFINED

#endif /* _hoops_CHS _hoops_ARIHGR */

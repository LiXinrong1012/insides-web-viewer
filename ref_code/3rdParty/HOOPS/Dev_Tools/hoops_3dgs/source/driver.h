/*
 * Copyright (c) 1998-2001 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.1190 2011-01-12 00:57:46 heppe Exp $
 */


#ifndef _hoops_IPRSP


#ifndef _hoops_GRAGP
#	include "database.h"
#endif
#ifndef HOOPS_ERRORS_DEFINED
#	include "hpserror.h"
#endif

Begin_HOOPS_Namespace

#define _hoops_CPRSP 17	 /* _hoops_SHHH _hoops_PSSP _hoops_PAIA._hoops_GGHR */
#define _hoops_SPRSP		65	 /* _hoops_GHRSP 0.0 _hoops_PIRIA 1.0, _hoops_RHRSP */
#define TOTAL_BIT_PATTERNS		(_hoops_CPRSP+_hoops_SPRSP)

#define _hoops_AHRSP	64	 /* _hoops_SHCAR, 1 _hoops_ARIP _hoops_GGR 64 */

#define _hoops_PHRSP	256


#define _hoops_HHRSP			128


/* _hoops_SPCA _hoops_HRGR _hoops_IRS _hoops_CIHH _hoops_GPPS _hoops_ARPC _hoops_RPP _hoops_SR _hoops_HPPR _hoops_IS _hoops_AACC _hoops_PSAP _hoops_HHSH _hoops_HCR
 * _hoops_IIGR _hoops_IRS _hoops_III _hoops_CRSIR _hoops_ACGGA - _hoops_SHCAR, _hoops_RPP _hoops_RH _hoops_ACGGA '_hoops_RA' _hoops_PIRA _hoops_HRGR _hoops_CPPPR _hoops_GCISR
 * 1.0. _hoops_CGP _hoops_PHRP _hoops_HS 6 _hoops_IHRSP _hoops_IIGR _hoops_GPPS, _hoops_PSCR "0.99" _hoops_GRS _hoops_ASSS
 * 4 _hoops_IHRSP _hoops_IS _hoops_SGAGA. _hoops_PGPR _hoops_IRS _hoops_CPPPR _hoops_CIAGR _hoops_APGR _hoops_GRS _hoops_SHH _hoops_GIAA _hoops_HIH _hoops_CRGP
 * _hoops_HSAR 1% (1 - .99) _hoops_GIAA.
 */
#define _hoops_CHRSP		0.01f
#define _hoops_SHRSP			(1.0f - _hoops_CHRSP)

/* _hoops_ASSS _hoops_IH _hoops_CPPPR _hoops_RISS _hoops_GIRR-_hoops_PSAP _hoops_HHGS _hoops_CGPR _hoops_CIHH */
#define _hoops_GIRSP		0.001f

/*
 * _hoops_RIRSP _hoops_RH _hoops_HCH _hoops_IIGR _hoops_RH _hoops_SIHP _hoops_GC _hoops_GGR _hoops_SSH,
 * _hoops_AIHCR _hoops_CSCHR _hoops_IS _hoops_RH _hoops_SARA-_hoops_IS-_hoops_SAAP _hoops_GIRA
 * _hoops_RGR _hoops_PIRA _hoops_HRGR _hoops_SGGA _hoops_IS _hoops_GIPR _hoops_AIRSP _hoops_IIGR _hoops_RH _hoops_SAAP
 */
#define _hoops_PIRSP	   4.0f

#define _hoops_IGSC(z,_hoops_IHCR)	((!BIT(_hoops_IHCR->flags, _hoops_PASP)) ? z : \
						 (z < 0.0f) ? 0.0f : (z > _hoops_IHCR->_hoops_PCHH) ? _hoops_IHCR->_hoops_PCHH : z)

#define _hoops_HIRSP	2048

#define _hoops_RRRIP		0.015f


//_hoops_PCCP _hoops_SHI _hoops_GPP _hoops_RICC _hoops_HSHR _hoops_IS _hoops_SGH _hoops_CGPR _hoops_IIRSP _hoops_SSH _hoops_CIGCP
#define _hoops_HRCIP  (0x71649572)




struct Int_XY {
	int					x, y;
};

struct _hoops_RCSIR {
	int					x, y ,z;
};



typedef float			_hoops_CIRSP;
typedef short			_hoops_SIRSP;
typedef Integer32		_hoops_GARRR;




struct _hoops_ISC {							// _hoops_PSHR _hoops_GAR _hoops_GCRSP _hoops_HIH _hoops_SIHH _hoops_IRS _hoops_PPII _hoops_HIS _hoops_SR _hoops_PAH _hoops_SGH _hoops_ASSA _hoops_HIPRA
	unsigned char		_hoops_RCRSP;
};

typedef Integer32	_hoops_HIHHP;

struct Driver_Color {
	public:
		union {
			_hoops_ISC			_hoops_HRIR;		// _hoops_IGI _hoops_CCA _hoops_ACRSP _hoops_HAIR _hoops_GHARR
			_hoops_GARSR			_hoops_PGGCR;		// _hoops_IGI _hoops_CCA _hoops_AIIHP _hoops_HAIR _hoops_GHARR
			_hoops_HIHHP			_hoops_PIHHP;		// _hoops_IGI _hoops_CCA _hoops_AIHHP _hoops_HAIR _hoops_GHARR
		};

		Driver_Color () {}
		Driver_Color (Driver_Color const & c) { *this = c; }
		Driver_Color (RGBAS32 const & c) { *this = c; }

		Driver_Color const &	operator= (Driver_Color const & c) alter	{ _hoops_PCRSP() = c._hoops_PCRSP(); return *this; }
		Driver_Color const &	operator= (RGBAS32 const & c) alter			{ _hoops_PCRSP() = (Integer32 const &)c; return *this; }

		bool			operator== (Driver_Color const & c) const	{ return  _hoops_PCRSP() == c._hoops_PCRSP(); }
		bool			operator!= (Driver_Color const & c) const	{ return  !(*this == c); }

		operator RGBAS32 const & () const	{ return *(RGBAS32 const *)this; }

	private:
		// _hoops_ASSS _hoops_IHHH _hoops_IS _hoops_HCRSP _hoops_AA _hoops_PCPA _hoops_RH _hoops_RHGS "_hoops_ICRSP" _hoops_ARIP (_hoops_GAR _hoops_IRS _hoops_HIPRA) _hoops_IIS _hoops_IHHH _hoops_AA _hoops_GRGA
		Integer32 const &	_hoops_PCRSP() const	{ return *(Integer32 const *)this; }
		Integer32 alter &	_hoops_PCRSP() alter	{ return *(Integer32 alter *)this; }
};
_hoops_AHAGP (sizeof (Driver_Color) == sizeof (RGBAS32), _hoops_CCRSP);


typedef short _hoops_SCHSA;
#define _hoops_PPHSA				(_hoops_SCHSA)0x0001
#define _hoops_CPHSA				(_hoops_SCHSA)0x0002
#define _hoops_SPHSA				(_hoops_SCHSA)0x0004
#define _hoops_GHHSA				(_hoops_SCHSA)0x0008
#define _hoops_RHHSA			(_hoops_SCHSA)0x0010
#define _hoops_SCRSP				(_hoops_SCHSA)0x0020

#define _hoops_GSRSP					(_hoops_SSIC)0x00000000
#define _hoops_RSRSP		(_hoops_SSIC)0x00000001
#define _hoops_ASRSP				(_hoops_SSIC)0x00000002
#define _hoops_PSRSP				(_hoops_SSIC)0x00000004
#define _hoops_HSRSP		(_hoops_SSIC)0x00000010
#define _hoops_ISRSP		(_hoops_SSIC)0x00000020
#define _hoops_CSRSP			(_hoops_SSIC)0x00000040
#define _hoops_SSRSP			(_hoops_SSIC)0x00000080
#define _hoops_GGASP		(_hoops_SSIC)0x00000100
#define _hoops_RGASP		(_hoops_SSIC)0x00000200
#define _hoops_AGASP		(_hoops_SSIC)0x00000400
#define _hoops_PGASP		(_hoops_SSIC)0x00000800
#define _hoops_HPPAR			(_hoops_SSIC)0x00001000
#define _hoops_HGASP		(_hoops_SSIC)0x00002000
#define _hoops_IGASP				(_hoops_SSIC)0x00004000

#define _hoops_ARCC	(_hoops_SSIC)0x80000000


#define _hoops_CGASP (_hoops_SSRSP|_hoops_GGASP|_hoops_RGASP|_hoops_AGASP|_hoops_PGASP)



/* _hoops_RGGHR _hoops_HHRPR _hoops_HIS _hoops_SGS _hoops_CGPR _hoops_SGASP _hoops_HPP 256, _hoops_ACPP _hoops_CHR _hoops_GRASP */
#define _hoops_RRASP			0.3125f
#define _hoops_ARASP			0.5000f		/* _hoops_PAR .59? (_hoops_PRASP) */
#define _hoops_HRASP			0.1875f		/* _hoops_PAR .11? (_hoops_PRASP) */

#define _hoops_IRASP(r, g, b)	\
		(_hoops_RRASP*(r) + _hoops_ARASP*(g) + _hoops_HRASP*(b))

/*
 * _hoops_HGI _hoops_CRASP _hoops_RIGR _hoops_SRASP _hoops_IRS _hoops_RHPP _hoops_HAIR, _hoops_PGAP _hoops_SSCP _hoops_AIAH
 * _hoops_RPII _hoops_GAASP _hoops_RAASP.
 */
#define _hoops_AAASP(_hoops_IHRHP, _hoops_PRSGR, _hoops_PIHSR, _hoops_PAASP) do {	\
			Display_Context const *	_hoops_SHARR = _hoops_IHRHP;							\
			Driver_Color const *	_hoops_HAASP = &_hoops_PRSGR;						\
			RGBAS32					_hoops_PAGR = _hoops_CAHSR::_hoops_SAHSR;				\
			switch (_hoops_PIHSR) {										\
			  case _hoops_RIIHP: {										\
				  _hoops_PAGR.r =												\
					  (unsigned char)(255.99f * (float)_hoops_HAASP->_hoops_PIHHP / \
					  (float)(_hoops_SHARR->_hoops_PGCC._hoops_PCHSR - 1));\
				  _hoops_PAGR.g = _hoops_PAGR.r;										\
				  _hoops_PAGR.b = _hoops_PAGR.r;										\
				  _hoops_PAGR.a = _hoops_GPGCR;					\
			  }	  break;												\
			  case _hoops_SIHSR: {										\
				  RGB const			*_hoops_SPRAR;								\
				  _hoops_SPRAR = &_hoops_SHARR->_hoops_CHHIP[_hoops_HAASP->_hoops_PGGCR];				\
				  _hoops_PAGR.r = (unsigned char)(255.99f * _hoops_SPRAR->red);			\
				  _hoops_PAGR.g = (unsigned char)(255.99f * _hoops_SPRAR->green);		\
				  _hoops_PAGR.b = (unsigned char)(255.99f * _hoops_SPRAR->blue);			\
				  _hoops_PAGR.a = _hoops_GPGCR;						\
			  }	  break;												\
			  case _hoops_HIHSR: {										\
				  _hoops_PAGR = *_hoops_HAASP;											\
			  }	  break;												\
			}															\
			_hoops_PAASP = _hoops_PAGR;												\
		} while (0)


#define _hoops_IAASP	_hoops_CAHSR::_hoops_SAHSR

#define _hoops_PIPCP(_hoops_GGIAR, p1, _hoops_RCGCR, _hoops_PAGR) do {									\
			(_hoops_PAGR).red	= ((_hoops_GGIAR).red	  + ((p1).red	- (_hoops_GGIAR).red	) * (_hoops_RCGCR));	\
			(_hoops_PAGR).green = ((_hoops_GGIAR).green + ((p1).green - (_hoops_GGIAR).green) * (_hoops_RCGCR));	\
			(_hoops_PAGR).blue	= ((_hoops_GGIAR).blue  + ((p1).blue	- (_hoops_GGIAR).blue) * (_hoops_RCGCR));		\
		} while (0)

#define _hoops_ACRGA(_hoops_GGIAR, p1, _hoops_RCGCR, _hoops_PAGR) do {								\
			(_hoops_PAGR).red	= ((_hoops_GGIAR).red	  + ((p1).red	- (_hoops_GGIAR).red	) * (_hoops_RCGCR));	\
			(_hoops_PAGR).green = ((_hoops_GGIAR).green + ((p1).green - (_hoops_GGIAR).green) * (_hoops_RCGCR));	\
			(_hoops_PAGR).blue	= ((_hoops_GGIAR).blue  + ((p1).blue	- (_hoops_GGIAR).blue) * (_hoops_RCGCR));		\
			(_hoops_PAGR).alpha = ((_hoops_GGIAR).alpha + ((p1).alpha - (_hoops_GGIAR).alpha) * (_hoops_RCGCR));	\
		} while (0)

#define _hoops_PCRGA(_hoops_GGIAR, p1, _hoops_RCGCR, _hoops_PAGR) do {															\
			(_hoops_PAGR).r = (unsigned char)((_hoops_GGIAR).r + ((float)(p1).r - (float)(_hoops_GGIAR).r) * (_hoops_RCGCR));	\
			(_hoops_PAGR).g = (unsigned char)((_hoops_GGIAR).g + ((float)(p1).g - (float)(_hoops_GGIAR).g) * (_hoops_RCGCR));	\
			(_hoops_PAGR).b = (unsigned char)((_hoops_GGIAR).b + ((float)(p1).b - (float)(_hoops_GGIAR).b) * (_hoops_RCGCR));	\
			(_hoops_PAGR).a = (unsigned char)((_hoops_GGIAR).a + ((float)(p1).a - (float)(_hoops_GGIAR).a) * (_hoops_RCGCR));	\
		} while (0)


#define _hoops_RGRGA(_hoops_GGIAR, p1, _hoops_RCGCR, _hoops_PAGR) do {	\
			(_hoops_PAGR).a = ((_hoops_GGIAR).a + ((p1).a - (_hoops_GGIAR).a) * (_hoops_RCGCR));	\
			(_hoops_PAGR).b = ((_hoops_GGIAR).b + ((p1).b - (_hoops_GGIAR).b) * (_hoops_RCGCR));	\
			(_hoops_PAGR).c = ((_hoops_GGIAR).c + ((p1).c - (_hoops_GGIAR).c) * (_hoops_RCGCR));	\
			(_hoops_PAGR).d = ((_hoops_GGIAR).d + ((p1).d - (_hoops_GGIAR).d) * (_hoops_RCGCR));	\
		} while (0)

#define _hoops_GGRGA(nr, _hoops_GGIAR, p1, _hoops_RCGCR, _hoops_PAGR, _hoops_PRPHA, param_width) do { \
			int _hoops_CAASP; \
			if (BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) { \
				float _hoops_SAASP; \
				_hoops_SAASP = (_hoops_RCGCR) / ((_hoops_PRPHA) + (1.0f - (_hoops_PRPHA)) * (_hoops_RCGCR)); \
				for (_hoops_CAASP=0; _hoops_CAASP<(param_width); _hoops_CAASP++) { \
					(_hoops_PAGR)[_hoops_CAASP] = ((_hoops_GGIAR)[_hoops_CAASP] + ((p1)[_hoops_CAASP] - (_hoops_GGIAR)[_hoops_CAASP]) * _hoops_SAASP); \
				} \
			} \
			else { \
				for (_hoops_CAASP=0; _hoops_CAASP<(param_width); _hoops_CAASP++) { \
					(_hoops_PAGR)[_hoops_CAASP] = ((_hoops_GGIAR)[_hoops_CAASP] + ((p1)[_hoops_CAASP] - (_hoops_GGIAR)[_hoops_CAASP]) * (_hoops_RCGCR)); \
				} \
			} \
		} while (0)



#define QUICK_NORMALIZE(_hoops_GIHI) do {																\
			Vector alter *	_hoops_GPASP = (Vector alter *)&_hoops_GIHI;										\
			float _hoops_RPASP = _hoops_SGIHR (_hoops_GPASP->x*_hoops_GPASP->x + _hoops_GPASP->y*_hoops_GPASP->y + _hoops_GPASP->z*_hoops_GPASP->z);		\
			if (_hoops_RPASP > 0.000001f) {															\
				_hoops_RPASP = 1.0f / _hoops_RPASP;															\
				_hoops_GPASP->x *= _hoops_RPASP;	_hoops_GPASP->y *= _hoops_RPASP;	_hoops_GPASP->z *= _hoops_RPASP;						\
			}																					\
		} while (0)


#define	_hoops_APASP(pln) do {	\
			(pln).a = -(pln).a;	\
			(pln).b = -(pln).b;	\
			(pln).c = -(pln).c;	\
			(pln).d = -(pln).d;	\
		} while (0)

#define	_hoops_PPASP(_hoops_HPASP) do {	\
			_hoops_APASP (_hoops_HPASP->_hoops_SHPA);		\
			_hoops_APASP (_hoops_HPASP->_hoops_SPPA);			\
		} while (0)

struct _hoops_GPPA {
	_hoops_GPPA alter *	next;
	_hoops_ARPA							_hoops_SHPA, _hoops_SPPA;
	int								id;

	bool							internal;	/* _hoops_HAR _hoops_HII _hoops_IPSP, _hoops_HIS _hoops_HAR _hoops_IH _hoops_AACC _hoops_CPAP */
};

struct _hoops_IAPA {
	_hoops_IAPA alter		*	next;

	_hoops_GPPA const *	_hoops_APPA;
	int								_hoops_IPASP;
};


struct Internal_Cutting_Plane_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Cutting_Plane_Rendition>;

	public:
		_hoops_IAPA const	*	_hoops_ISIGA;			// _hoops_SPASP _hoops_GAR _hoops_GGR _hoops_AARPR
		_hoops_IAPA const	*	_hoops_PHCA;		// _hoops_SPASP _hoops_IH _hoops_ASCA _hoops_GGR _hoops_GPGR _hoops_HHHH
		_hoops_IAPA const	*	_hoops_IRH;		// "" _hoops_HIH _hoops_CCA _hoops_PSP _hoops_GHASP _hoops_RHASP
		int							_hoops_PGH;
		int							_hoops_CRH;
		int							_hoops_AHASP;

	public:
		HOOPS_API Internal_Cutting_Plane_Rendition (Internal_Cutting_Plane_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Cutting_Plane_Rendition ();

	private:
		Internal_Cutting_Plane_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Cutting_Plane_Rendition>	_hoops_SSP;





struct _hoops_ASHH {
	_hoops_ASHH *		next;

	DC_Point *					points;
	_hoops_GPPA *	_hoops_GRCPR;
	_hoops_PACIR			_hoops_RCHS;
	int							count;
	int							flags;

	_hoops_PHASP				_hoops_HSAI;
};

struct _hoops_HHASP : public _hoops_CPASP {
	friend class Rendition_Pointer<_hoops_HHASP>;

	public:
		_hoops_ASHH const *	_hoops_PSHH;		// _hoops_CSRGA/_hoops_IIAP _hoops_GAR _hoops_GGR _hoops_AARPR
		_hoops_ASHH const *	_hoops_AHGGA;		// _hoops_AHAAR _hoops_IS _hoops_SGCS _hoops_PGHH
		int							_hoops_IPRGA;			// _hoops_CIAS _hoops_HII _hoops_GII _hoops_IHASP
		bool						_hoops_ISRGA;			// _hoops_GGR _hoops_CHASP

	public:
		HOOPS_API _hoops_HHASP (_hoops_HHASP const & _hoops_HACIR);
		HOOPS_API ~_hoops_HHASP ();

	private:
		_hoops_HHASP (Display_Context const * dc);
};
typedef Rendition_Pointer<_hoops_HHASP>	_hoops_HSRGA;











typedef int _hoops_GPGGA;

#define _hoops_SHASP			(_hoops_GPGGA)0x00000000
#define _hoops_PHGGA		(_hoops_GPGGA)0x00000001
#define _hoops_RHGGA	(_hoops_GPGGA)0x00000002
#define _hoops_GPHC	(_hoops_GPGGA)0x00000004
#define _hoops_CGRGA		(_hoops_GPGGA)0x00000008
#define _hoops_AAIC	(_hoops_GPGGA)0x00000010
#define _hoops_PAIC		(_hoops_GPGGA)0x00000020
#define _hoops_RAIC	(_hoops_GPGGA)0x00000040

#define _hoops_SCSIR			(_hoops_PHGGA|_hoops_RHGGA|_hoops_GPHC)
#define	_hoops_CGAGA		(_hoops_AAIC|_hoops_PAIC|_hoops_RAIC)

#define _hoops_SGRGA	1024

struct _hoops_SIHHP {
	unsigned char const *		pattern;
	int							height;
	int							width;
	bool						_hoops_RCHHP;
	int							_hoops_ACHHP;

	int							stipple;

	_hoops_PHASP			_hoops_HSAI;
	_hoops_GARRR				_hoops_CPA;
};


/* _hoops_HGI _hoops_IPP _hoops_RGAR _hoops_GIASP _hoops_PCPA _hoops_CSAP _hoops_IGRC _hoops_CHCC _hoops_GGR _hoops_RH _hoops_RPPS _hoops_ARRS _hoops_RH _hoops_CAGH
   _hoops_IHGS _hoops_CHHHP.  _hoops_HGGSP _hoops_AIRC _hoops_CHR _hoops_RIASP _hoops_GH _hoops_PPR _hoops_ISHP _hoops_CRGR _hoops_RH _hoops_AIASP->_hoops_RPPS */
struct Internal_Window_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Window_Rendition>;

	public:
		_hoops_AHAGR *				_hoops_ASSIR;
		_hoops_RCR const *				_hoops_SICSR;
		_hoops_SIHHP const	*	_hoops_PGPH;

		Driver_Color				_hoops_GPIR;
		Driver_Color				contrast_color;
		RGB							_hoops_GRAIP; /* _hoops_PIASP'_hoops_GHGP _hoops_CSPP */
		RGB							_hoops_CGIHP; /* _hoops_PIASP'_hoops_GHGP _hoops_CSPP */

		int							_hoops_CGAIP;
		bool						_hoops_SGAIP;

		_hoops_PACIR			extent;
		_hoops_PACIR			_hoops_HHCAR;

		Int_Rectangle				_hoops_PHRA;
		Int_Rectangle				_hoops_CIIH;
		Int_Rectangle				_hoops_SCIH;
		Int_Rectangle				_hoops_GAHIP;
		Int_Rectangle				_hoops_RRAIP;

		float						_hoops_CSIH;

		_hoops_RIARP			_hoops_ASIHP;

		float						shadow_resolution;

	public:
		HOOPS_API Internal_Window_Rendition (Internal_Window_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Window_Rendition ();

	private:
		Internal_Window_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Window_Rendition>	_hoops_CGRA;



struct Internal_Material_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Material_Rendition>;

	public:
		_hoops_HIR *		_hoops_SCA;
		_hoops_RCR *					texture[_hoops_GAGRA];
		RGB							_hoops_CSHR;
		RGB							color[_hoops_GAGRA];

		float						_hoops_IRIR; /* 0.0=_hoops_RRH, 1.0=_hoops_CIGC */
		float						gloss;
		float						_hoops_PAGRA;

		bool						_hoops_ARIR;
		int							_hoops_HGHHP;

	public:
		HOOPS_API Internal_Material_Rendition (Internal_Material_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Material_Rendition ();

	private:
		Internal_Material_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Material_Rendition>	_hoops_HHA;



struct Internal_Color_Map_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Color_Map_Rendition>;

	public:
		_hoops_RHAH const *			_hoops_ISIR;		/* _hoops_CRS _hoops_IS _hoops_AARPR */
		Driver_Color const *		_hoops_ACIHP;	/* _hoops_IH _hoops_GRAA-_hoops_IIHSR _hoops_CCH */
		_hoops_GARSR					_hoops_HSIR;

		_hoops_RHAH const *			_hoops_CSIR;		/* _hoops_CRS _hoops_IS _hoops_AARPR */
		Driver_Color const *		_hoops_AHHHP;	 /* _hoops_IH _hoops_GRAA-_hoops_IIHSR _hoops_CCH */

		_hoops_GARSR					_hoops_RHHHP; /* _hoops_IH _hoops_IIHSR _hoops_CCH */
		_hoops_GARSR					length;

	public:
		HOOPS_API Internal_Color_Map_Rendition (Internal_Color_Map_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Color_Map_Rendition ();

	private:
		Internal_Color_Map_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Color_Map_Rendition>	_hoops_CAHHP;



struct Internal_Texture_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Texture_Rendition>;

	public:
		_hoops_RCR **					textures;
		Integer32 *					keys;
		int							count;

	public:
		HOOPS_API Internal_Texture_Rendition (Internal_Texture_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Texture_Rendition ();

	private:
		Internal_Texture_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Texture_Rendition>	_hoops_IPRIP;



struct Internal_Line_Style_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Line_Style_Rendition>;

	public:
		Line_Style *				_hoops_HPAIR;
		Line_Style					_hoops_IHRIP;
		Integer32 *					keys;
		int							count;

	public:
		HOOPS_API Internal_Line_Style_Rendition (Internal_Line_Style_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Line_Style_Rendition ();

	private:
		Internal_Line_Style_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Line_Style_Rendition>	_hoops_PHRIP;



struct Internal_Glyph_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Glyph_Rendition>;

	public:
		_hoops_GASC *						glyphs;
		Integer32 *					keys;
		int							count;

	public:
		HOOPS_API Internal_Glyph_Rendition (Internal_Glyph_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Glyph_Rendition ();

	private:
		Internal_Glyph_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Glyph_Rendition>	_hoops_GHRIP;


struct _hoops_HIASP : public _hoops_CPASP {
	friend class Rendition_Pointer<_hoops_HIASP>;

public:
	_hoops_GPAIR *				_hoops_SAAIR;
	Integer32 *					keys;
	int							count;

public:
	HOOPS_API _hoops_HIASP (_hoops_HIASP const & _hoops_HACIR);
	HOOPS_API ~_hoops_HIASP ();

private:
	_hoops_HIASP (Display_Context const * dc);
};
typedef Rendition_Pointer<_hoops_HIASP>	_hoops_RIGIP;



struct Internal_Misc_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Misc_Rendition>;

	public:
		_hoops_GAAIR const *		_hoops_APGH;

		_hoops_ACHR					_hoops_AARIP,
									_hoops_CRR,
									_hoops_GHIHP;

		_hoops_GHGI					_hoops_GASHP;
		_hoops_GHGI					_hoops_PPH;
		_hoops_GHGI					_hoops_CSA;
		_hoops_GSGAP					_hoops_GSSIR; /* _hoops_CACH _hoops_AARPR._hoops_GGHR _hoops_IH _hoops_PAIGR */
		Quantization_Flags			_hoops_SIRAP;
		_hoops_GCRAP			_hoops_RCRAP;
		_hoops_SHCRP				_hoops_SRI;


		_hoops_PIGRA				locks;			// _hoops_CISI _hoops_SGHS
		_hoops_PIGRA				_hoops_HHGIP;	// _hoops_PPGP _hoops_SGHS (_hoops_RPSI _hoops_SSSCP _hoops_AGRP)

		Vector						_hoops_HRGA;
		RGB							_hoops_HASR, _hoops_RPIHP;
		RGB							_hoops_CASR, _hoops_PPIHP;
		RGB							_hoops_PCP;

		/* _hoops_RGAR _hoops_IGI _hoops_RHSP _hoops_IIASP... */
		_hoops_ACHR					_hoops_AAICA,
									restricted_selectability,
									_hoops_PHARP;
		int							_hoops_GCCIA;
		struct {
			int							_hoops_SPHPR, polyline;
		}							_hoops_CCIRP;
		int							_hoops_GRCRP;

		int							_hoops_ACIRP;
		bool						_hoops_PCIRP;
		int							_hoops_GRGC;
		int							_hoops_PCHS;
		int							_hoops_SHHS;
		int							_hoops_GCHS;
		int							_hoops_CIIRP;

		Vector						vector;
		float						_hoops_IIIRP;

		int							_hoops_RRCRP;
		float						_hoops_ARCRP;

		int							_hoops_IRCRP;

		int							_hoops_GAHA;
		bool						_hoops_RPSHP;

		bool						_hoops_GIRC;

		short						_hoops_CHP;

	public:
		//_hoops_ASCGP _hoops_CIASP (_hoops_CIASP _hoops_RCIC & _hoops_SGS);
		//_hoops_ASCGP ~_hoops_CIASP ();

	private:
		Internal_Misc_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Misc_Rendition>	_hoops_GRGH;



struct Internal_Display_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Display_Rendition>;

	public:
		_hoops_CAHHP			_hoops_PSIR;

		struct {
			_hoops_PPAAP				options;
			int							_hoops_SPAAP;
			_hoops_AHAAP					_hoops_GHAAP;
		}							buffer;

		struct _hoops_SIASP {
			_hoops_GPCRP			options;
			RGB							color;
			Line_Style					line_style;
			float						_hoops_IHCRP;
			float						_hoops_CHIH;
			float						_hoops_CHCRP;
			_hoops_HCAIR				weight;
			_hoops_SHCRP				_hoops_SRI;
		}							_hoops_GCCI;

		struct _hoops_CPCPA {					/* _hoops_CGRIR _hoops_RPPS _hoops_HSH, _hoops_GCASP _hoops_ARI _hoops_CCGR _hoops_SR _hoops_IGRC _hoops_HGCR _hoops_IRS _hoops_RPPS */
			Driver_Color				color;
			Driver_Color				_hoops_HGIHP;
			Driver_Color				_hoops_SCHHP;
			Driver_Color				_hoops_IGIHP;
			RGB							_hoops_PGC; /* _hoops_PIASP'_hoops_GHGP _hoops_CSPP */
			RGB							_hoops_CGIHP; /* _hoops_PIASP'_hoops_GHGP _hoops_CSPP */

			_hoops_RCR const *				texture;
			_hoops_SIHHP const *	_hoops_PGPH;
			int							pattern;
			bool						_hoops_RARIP;
			_hoops_RIARP			_hoops_ASIHP;
		}							window;

		struct {
			unsigned int *			_hoops_RCHA;
			int						count;
			_hoops_PCACA *	_hoops_ACPGR;
			_hoops_SPGIP *		_hoops_CPGIP;
		}							conditions;

	public:
		HOOPS_API Internal_Display_Rendition (Internal_Display_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Display_Rendition ();

	private:
		Internal_Display_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Display_Rendition>	_hoops_ISHHP;



struct Internal_Geometry_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Geometry_Rendition>;

	public:
		struct L {
			_hoops_RRPHA				options;
			float					_hoops_PRPHA[_hoops_IGAIR]; /* _hoops_RISRP _hoops_AHHSR */
			float					_hoops_AISRP[_hoops_IGAIR]; /* _hoops_CICA _hoops_PISRP */
			int						_hoops_HISRP;
			int						_hoops_IISRP;			/* _hoops_CISRP _hoops_IS _hoops_PAPA.	-1 _hoops_RPP _hoops_GRGR */
			int						_hoops_IRSH;
			int						_hoops_RHPHA;
			float					tolerance;
			Bounding				bounding;
			float					_hoops_GHRGR[_hoops_IGAIR]; /* _hoops_SHRRR _hoops_GCSRP */
			int						_hoops_SRHHR; /* _hoops_SISRP _hoops_CSHHR (_hoops_RAR _hoops_HIAGR) */
			int						_hoops_RCSRP; /* _hoops_IIPGA _hoops_GGR _hoops_AGIR _hoops_SR _hoops_IAGC _hoops_IRS _hoops_GRAA-_hoops_PHIPR _hoops_PRCCA */
			int						_hoops_ARPHA;
		}						_hoops_PRSI;

		_hoops_PARC		_hoops_APPI;

		_hoops_AIIAA
								_hoops_APSHP;

		struct T {
			int						cylinder[_hoops_IGAIR];
			int						sphere[_hoops_IGAIR];
		}						_hoops_GAICA;

		struct _hoops_RCASP {
			float					width_scale;
			float					_hoops_IISHP;
			RGB						_hoops_RSCC;
			RGB						_hoops_HRA;
		}						image;

		_hoops_AHAH					_hoops_IHRH;

		int						geometry_options;
		float					_hoops_GCIPR;

		struct _hoops_HGHHA {
			_hoops_ACHR				_hoops_RGP;
			int						_hoops_CCCRP;
			float					scale, translate;
		}						_hoops_CICP;

		struct _hoops_ACASP {
			int						_hoops_RSCRP;
			int						_hoops_CIAIR;
			float *					_hoops_SIAIR;

			int						_hoops_GCAIR;
			RGB *					colors;

			int						_hoops_RCAIR;
			_hoops_HCRPR *					_hoops_ACAIR;
			Integer32 *				_hoops_PCAIR;

			int						weight_count;
			_hoops_HCAIR *			weights;

			bool					_hoops_PCP;
		}						_hoops_ACP;

	public:
		HOOPS_API Internal_Geometry_Rendition (Internal_Geometry_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Geometry_Rendition ();

	private:
		Internal_Geometry_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Geometry_Rendition>	_hoops_GRA;


struct Internal_Visualization_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Visualization_Rendition>;

	public:
		struct _hoops_SRGAP {
			_hoops_ARPA					plane;
			Vector					light;
			RGBAS32					color;
			float					_hoops_IRIR;
			int						_hoops_HAP;
			int						_hoops_IGGGR;
			bool					_hoops_RPHHP;
		}						_hoops_GHSS;

		struct {
			int						_hoops_HAP;
			int						_hoops_CAP;
			bool					_hoops_HI;
			bool					_hoops_SAR;
		}						_hoops_HRR;

		struct _hoops_CPGAP {
			_hoops_ARPA					plane;
			_hoops_ACHR				_hoops_RGP;
			float					_hoops_IRIR;
			float					hither, yon;
			int						_hoops_IGGGR;
			bool					_hoops_SIRH; /* _hoops_HPP _hoops_GIRA */
			bool					_hoops_IHSHP; /* _hoops_HPP _hoops_RCSA */
		}						_hoops_RHGGR;

		struct {
			int						options;
			int						style;
			_hoops_SHCRP			_hoops_SRI;
			int						_hoops_RPAAP;
			float					_hoops_APAAP;
			bool					_hoops_HRH;
			bool					_hoops_RGGIP;
		}						_hoops_PRH;

		struct {
			int						level;
			float					tolerance;
			float					_hoops_GSPHP;
			bool					_hoops_CCPHP;
			int						_hoops_SRIGA;
		}							_hoops_PRIGA;

		struct {
			float					hither;
			float					yon;
		}						_hoops_CRIR;

		struct {
			float					_hoops_HCIR[2];
			float					_hoops_GRCR;
		}						_hoops_GIC;

		float					_hoops_SSIRP[_hoops_ISIRP];
		float					_hoops_GGCRP;
		int						_hoops_RGCRP;
		int						_hoops_AGCRP;

	private:
		Internal_Visualization_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Visualization_Rendition>	_hoops_GCIR;


struct _hoops_AS {
	_hoops_AS alter *	next;
	Point const *			points;
	_hoops_GSAR const *		_hoops_HRR;
	Key						_hoops_PCASP;
	Integer32				time_stamp;
	Type					_hoops_PRR;
	RGB						color;
	RGB						_hoops_HASR;
	RGB						_hoops_CASR;
	Point					position;
	Point					target;
	Vector					direction;
	Vector					_hoops_ARSR;
	float					_hoops_ACSR,
							_hoops_HCSR;
	float					inner_cos,
							_hoops_HCASP;
	float					_hoops_CCSGP;
	int						count;
	float					area;
	int						_hoops_HSSGP;
	_hoops_ACHR				_hoops_RGP;
	_hoops_ACHR				_hoops_CRR;
	bool					_hoops_ICASP;
};

struct Internal_Light_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Light_Rendition>;

	public:
		_hoops_AS *		_hoops_CGR;
		float					scale;
		int						count;
		bool					_hoops_ISPHP;

	public:
		HOOPS_API ~Internal_Light_Rendition ();

	private:
		Internal_Light_Rendition (Internal_Light_Rendition const & _hoops_HACIR);
		Internal_Light_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Light_Rendition>	_hoops_PC;




struct _hoops_CCASP : public _hoops_CPASP {
	friend class Rendition_Pointer<_hoops_CCASP>;

	public:
		_hoops_HRPA										data;

		_hoops_CRSPA const &	_hoops_PPRA () const {
			if (data._hoops_APRA == null)
				data._hoops_APRA = _hoops_CRSPA::Create (memory_pool);

			if (ANYBIT (data._hoops_RAGR, _hoops_CICH))
				HI_Adjoint_44 (&data.elements[0][0], &data._hoops_APRA->data.elements[0][0]);

			return data._hoops_APRA;
		}

	private:
		HOOPS_API _hoops_CCASP (Display_Context const * dc);
};
typedef Rendition_Pointer<_hoops_CCASP>	_hoops_SGCC;



#	define		_hoops_PRIR			(_hoops_SCASP)0x00000001
#	define		_hoops_GRHH						(_hoops_SCASP)0x00000002
#	define		_hoops_GSIHP				(_hoops_SCASP)0x00000004
#	define		_hoops_PGCH			(_hoops_SCASP)0x00000008

#	define		_hoops_PRAIP		(_hoops_SCASP)0x00000010
#	define		_hoops_IGCC (_hoops_SCASP)0x00000020
#	define		_hoops_AIPHP	(_hoops_SCASP)0x00000040
#	define		_hoops_IGSP					(_hoops_SCASP)0x00000080

#	define		_hoops_RCRIP		(_hoops_SCASP)0x00000100
#	define		_hoops_CSP				(_hoops_SCASP)0x00000200
#	define		_hoops_HHGGA		(_hoops_SCASP)0x00000400
#	define		_hoops_AIHS			(_hoops_SCASP)0x00000800

#	define		_hoops_GSASP			(_hoops_SCASP)0x00001000
#	define		TR_SORT_HIDDEN_BY_PRIORITY		(_hoops_SCASP)0x00002000
#	define		_hoops_RSASP				(_hoops_GSASP|TR_SORT_HIDDEN_BY_PRIORITY)
#	define		_hoops_CGHIP				(_hoops_SCASP)0x00004000
#	define		_hoops_ASPIP					(_hoops_SCASP)0x00008000

#	define		_hoops_GPSHP			(_hoops_SCASP)0x00010000
#	define		_hoops_HCPHP	(_hoops_SCASP)0x00020000
#	define		_hoops_ICPHP	(_hoops_SCASP)0x00040000
#	define		_hoops_SPP				(_hoops_SCASP)0x00080000

#	define		_hoops_CAHPP		(_hoops_SCASP)0x00100000
#	define		_hoops_APGSP		(_hoops_SCASP)0x00200000
#	define		_hoops_CHHS		(_hoops_SCASP)0x00400000
#	define		_hoops_ASASP						(_hoops_SCASP)0x00800000

#	define		_hoops_PASP					(_hoops_SCASP)0x01000000
#	define		_hoops_ISH				(_hoops_SCASP)0x02000000
#	define		_hoops_PIHIP			(_hoops_SCASP)0x04000000
#	define		_hoops_CASP			(_hoops_SCASP)0x08000000

#	define		_hoops_PSASP				(_hoops_SCASP)0x10000000
#	define		_hoops_HSASP						(_hoops_SCASP)0x20000000
#	define		_hoops_ISASP						(_hoops_SCASP)0x40000000
#	define		_hoops_CSASP						(_hoops_SCASP)0x80000000


#	define		_hoops_AHPHP		0
#	define		_hoops_PHPHP		1
#	define		_hoops_HHPHP	2

#	define		_hoops_GGHPP			0
#	define		_hoops_SGGIP			1
#	define		_hoops_CGGIP			2
#	define		_hoops_SSASP	4

#	define		_hoops_GRGIP	(_hoops_SGGIP|_hoops_SSASP)
#	define		_hoops_APHPP	(_hoops_CGGIP|_hoops_SSASP)

typedef Integer32	_hoops_SCASP;

struct Internal_Transform_Rendition  : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Transform_Rendition>;

	public:
		_hoops_HHRA const *				_hoops_SPH;
		_hoops_SGCC			matrix;
		_hoops_SGCC			_hoops_IPH;

		_hoops_SGCC			_hoops_CGCC;
		_hoops_SGCC			_hoops_GGPSP;
		_hoops_SGCC			object_to_projection_matrix;

		_hoops_SSP		_hoops_RGH;
		_hoops_HSRGA			_hoops_HCHH;

		int							_hoops_HGSC;

		_hoops_SCASP					flags;

		Int_Rectangle				_hoops_AGAA;
		Int_Rectangle				_hoops_RGPSP;

		float						_hoops_CHCR;
		float						_hoops_RIPHP;
		float						_hoops_PCHH;
		float						_hoops_GSCH[2];
		_hoops_PACIR			_hoops_HCIH;
		float						_hoops_CHIH;
		float						_hoops_RASHP;
		float						_hoops_IGAAP;
		float						_hoops_CASHP;
		float						_hoops_SHIH;
		float						_hoops_SASHP;
		float						_hoops_HIPHP;
		float						_hoops_IIPHP;

		_hoops_CGSP			heuristics;

		short						_hoops_APH;

		char						_hoops_RHPHP;
		char						_hoops_PGGIP;
		float						_hoops_ACSRP;
		float						_hoops_PCSRP;

		int							_hoops_SSPPP;

	public:
		HOOPS_API Internal_Transform_Rendition (Internal_Transform_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Transform_Rendition ();

	private:
		Internal_Transform_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Transform_Rendition>	_hoops_HHCR;


struct Internal_Face_Rendition  : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Face_Rendition>;

	public:
		_hoops_HHA			_hoops_CHA;
		_hoops_HHA			_hoops_GIA;
		_hoops_PC				_hoops_AGP;
		_hoops_SIHHP const	*	_hoops_PGPH;

		Driver_Color				color,
									contrast_color,
									_hoops_RGIR,
									_hoops_ARIHP,
									_hoops_SCHHP,
									_hoops_GRIHP,
									_hoops_GSHHP,
									_hoops_PRIHP;

		int							pattern;

	public:
		HOOPS_API Internal_Face_Rendition (Internal_Face_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Face_Rendition ();

	private:
		Internal_Face_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Face_Rendition>	_hoops_CIGA;



#define _hoops_CSGIP	(_hoops_IICIA>>4)

typedef int Line_Rendition_Flags;

#define LRF_NONE						(Line_Rendition_Flags) 0x00000000
#define _hoops_HHISA		(Line_Rendition_Flags) 0x00000001
#define _hoops_PHISA			(Line_Rendition_Flags) 0x00000002
#define _hoops_HGRIP		(Line_Rendition_Flags) 0x00000004
#define _hoops_SSGIP		(Line_Rendition_Flags) 0x00000010
#define _hoops_RGRIP			(Line_Rendition_Flags) 0x00000020
#define _hoops_SRPI					(Line_Rendition_Flags) 0x00000040

#define _hoops_AGPSP (_hoops_HHISA|_hoops_PHISA)
#define _hoops_AGRIP		(_hoops_AGPSP|_hoops_HGRIP)


struct Internal_Line_Rendition;
typedef Rendition_Pointer<Internal_Line_Rendition>	Line_Rendition;

struct Internal_Line_Rendition  : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Line_Rendition>;

	public:
		_hoops_HHA			_hoops_CHA;
		_hoops_PC				_hoops_AGP;
		Line_Style					line_style;

		_hoops_GASC						start_glyph;
		_hoops_GASC						middle_glyph;
		_hoops_GASC						end_glyph;

		_hoops_CIGA				_hoops_IHA;
		Line_Rendition				_hoops_SSHHP;
		Line_Rendition				contrast_rendition;

		Driver_Color				color,
									contrast_color,
									_hoops_SCHHP,
									_hoops_GRIHP;

		Line_Rendition_Flags		flags;
		int							style;
		float						weight;
		float						_hoops_HCAA;
		float						_hoops_PHP;
		_hoops_GIGRP			_hoops_HHP;

	public:
		//_hoops_ASCGP _hoops_PGPSP (_hoops_PGPSP _hoops_RCIC & _hoops_SGS);
		//_hoops_ASCGP ~_hoops_PGPSP ();

	private:
		Internal_Line_Rendition (Display_Context const * dc);
};



typedef unsigned char Marker_Rendition_Flags;
#define _hoops_HGPSP			(Marker_Rendition_Flags) 0x00000000
#define _hoops_IGPSP			(Marker_Rendition_Flags) 0x00000001
#define _hoops_CGPSP		(Marker_Rendition_Flags) 0x00000002
#define _hoops_SGPSP		(Marker_Rendition_Flags) 0x00000004


struct Internal_Marker_Rendition  : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Marker_Rendition>;

	public:
		_hoops_HHA			_hoops_CHA;
		_hoops_PC				_hoops_AGP;
		Line_Rendition				_hoops_SSHHP;
		Line_Rendition				contrast_rendition;

		_hoops_GASC						glyph;

		Driver_Color				color,
									contrast_color,
									_hoops_SCHHP,
									_hoops_GRIHP;

		float						_hoops_RGRS,
									ysize;
		float						_hoops_PHP;
		float						_hoops_CSRS;
		_hoops_GIGRP			_hoops_HHP;
		_hoops_HCAIR				_hoops_GRPSP;
		Marker_Rendition_Flags		flags;

	public:
		//_hoops_ASCGP _hoops_RRPSP (_hoops_RRPSP _hoops_RCIC & _hoops_SGS);
		//_hoops_ASCGP ~_hoops_RRPSP ();

	private:
		Internal_Marker_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Marker_Rendition>	_hoops_ICP;



struct Internal_Text_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Text_Rendition>;

	public:
		mutable	Font_Instance const *	font;			/* _hoops_RHPP _hoops_CCCHA _hoops_HRCSR */
		_hoops_HHA				_hoops_CHA;
		Line_Rendition					_hoops_RGIHP; /* _hoops_IRAP _hoops_RPP _hoops_HAR _hoops_SIGR */
		_hoops_AGPIR const *				_hoops_HSRIP; /* _hoops_RH _hoops_PPARR _hoops_SGS _hoops_ARPSP _hoops_RH _hoops_RPPCR */

		Driver_Color					color,
										contrast_color,
										_hoops_SCHHP,
										_hoops_GRIHP;

		int								_hoops_PRRIP;
		int								_hoops_HRRIP;
		float							spacing;
		Vector							path;

		mutable	int						fallback_index;
		bool							_hoops_PRPSP;

		/* _hoops_RH _hoops_HSPR _hoops_CHR _hoops_AGGP, _hoops_RIRRR _hoops_HII _hoops_RH _hoops_AARPR... */
		float							_hoops_PHP,/* (_hoops_HRPSP = _hoops_AARPR = _hoops_CRHR _hoops_IRPSP) */
										_hoops_ACPAP,
										_hoops_PCPAP,
										_hoops_HCPAP;
		float							rotation;
		float							width_scale;
		float							_hoops_ICPAP;
		float							_hoops_IPGRP;
		float							_hoops_CCPAP;
		float							_hoops_SCPAP;
		bool							_hoops_CRRIP;
		bool							_hoops_HCRIP;
		bool							_hoops_ICRIP;
		bool							outline;
		bool							_hoops_SCRIP;
		bool							_hoops_GSRIP;
		bool							_hoops_CCRIP;
		bool							_hoops_RSRIP;
		bool							_hoops_ASRIP;
		bool							_hoops_PSRIP;
		bool							_hoops_CRPSP;	/* _hoops_GRH _hoops_PRCA _hoops_IH _hoops_CGSI _hoops_PII _hoops_SRPSP */

		int								_hoops_GRCSR; /* _hoops_IGI _hoops_IH _hoops_RCICR _hoops_HRCSR _hoops_GASR */

		_hoops_GSPAP					transform;
		_hoops_SIPAP					_hoops_ISPAP[2];
		_hoops_RCPAP					_hoops_CSPAP[2];
		_hoops_GCPAP				_hoops_SGHAP;

		_hoops_SPGRP					_hoops_GHGRP,
										_hoops_SSPAP,
										_hoops_GGHAP,
										_hoops_RGHAP,
										_hoops_AGHAP,
										_hoops_PGHAP;

	public:
		HOOPS_API Internal_Text_Rendition (Internal_Text_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Text_Rendition ();

		void _hoops_SRRIP () const { font = null; fallback_index = 0; }

	private:
		Internal_Text_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Text_Rendition>	_hoops_IGCSR;


struct Internal_User_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_User_Rendition>;

	public:
		_hoops_CGGSA *				_hoops_IGGSA;

	public:
		HOOPS_API Internal_User_Rendition (Internal_User_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_User_Rendition ();

	private:
		Internal_User_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_User_Rendition>	_hoops_CIGIP;


struct Segment_Info {
	Segment_Info alter *		next;
	_hoops_CRCP const *				segment;
	_hoops_HICS				path;
	int							_hoops_GAPSP;
	bool						_hoops_IHICP;
};


typedef int Text_Info_Flags;
#define _hoops_RAPSP			(Text_Info_Flags) 0x00000000
#define _hoops_AAPSP	(Text_Info_Flags) 0x00000001
#define _hoops_PAPSP	(Text_Info_Flags) 0x00000002
#define _hoops_HAPSP	(Text_Info_Flags) 0x00000004



#define TKIF_NONE				(Text_Info_Flags) 0x00000000
#define TKIF_OMITTED			(Text_Info_Flags) 0x00000001
#define _hoops_IAPSP			(Text_Info_Flags) 0x00000002
#define _hoops_CAPSP			(Text_Info_Flags) 0x00000004
#define _hoops_SAPSP	(Text_Info_Flags) 0x00000010
#define _hoops_GPPSP	(Text_Info_Flags) 0x00000020
#define _hoops_RPPSP				(Text_Info_Flags) 0x00000040

struct _hoops_PGCSR {
	Net_Rendition			nr;
	_hoops_AGPIR *				_hoops_APPSP;

	Point					position;
	Point					point;
	float					width;
	float					height;

	struct {
		float					width;
		float					height;
		float					x;
		float					y;
	}						string,	/* _hoops_CSCHR _hoops_IS _hoops_CSCS _hoops_CRAA (_hoops_ARPP _hoops_ISPH) */
							screen;	/* _hoops_CSCHR _hoops_IS _hoops_SHPR (_hoops_ARPP _hoops_ISPH) */

	RGB						color;
	float					slant_extra;
	float					_hoops_HPGRP;
	float					_hoops_PPGRP;
	float					_hoops_CGSIR;

	Text_Info_Flags			flags;
	int						offset;
};

struct Text_Info {
	_hoops_HACC const			*text;
	_hoops_PGCSR	*_hoops_HGCSR;
	int						*_hoops_PPPSP;

	KName				_hoops_SIHSA;

	Point				position;
	Point				_hoops_CSAGR;
	Point				_hoops_HPPSP;
	Point				_hoops_IPPSP;
	Vector				_hoops_CPPSP; /* _hoops_IGI _hoops_CCA _hoops_GHAP._hoops_RPRAR. */
	Vector				path;			/* _hoops_HACH _hoops_CRAA _hoops_IIGR _hoops_SPPSP _hoops_HCGR */
	Vector				_hoops_GHPSP;			/* _hoops_RHPSP _hoops_CRAA _hoops_IIGR _hoops_GRR _hoops_GAS */
	Vector				_hoops_AHPSP;
	Vector				scale;
	Vector				_hoops_PHPSP;		/* _hoops_HPGCA _hoops_IS _hoops_HASSA _hoops_APGR */

	/* _hoops_AGCR _hoops_CIAGR _hoops_RGAR _hoops_SIGR _hoops_HPP _hoops_GHAP._hoops_RPRAR. _hoops_HIH _hoops_AGCA _hoops_ARPP _hoops_RH _hoops_ACSP _hoops_IH _hoops_AHSGP */
	Vector				_hoops_HHPSP;
	Vector				_hoops_IHPSP;
	Vector				_hoops_CHPSP;
	Point				_hoops_AGRI;
	int						which;
	int						line_index;

	float					_hoops_SHPSP;
	float					_hoops_PCPAP;
	float					_hoops_HCPAP;

	/* _hoops_SARPA _hoops_HII _hoops_HCR _hoops_HPS */
	float					_hoops_GIPSP;
	float					_hoops_ICGH;

	int						_hoops_RIPSP;

	Text_Info_Flags		flags;
};


#define ACTION_CALL HC_CDECL


typedef void (ACTION_CALL * _hoops_IACHP)
				(Net_Rendition const * nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_SACHP)
				(Net_Rendition const * nr, int count, DC_Point const *points, RGBAS32 const *color, bool single);
typedef void (ACTION_CALL * _hoops_RPCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points, RGBAS32 const *colors);
typedef void (ACTION_CALL * _hoops_APCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points, RGBA const *colors, _hoops_ARPA const *planes);
typedef void (ACTION_CALL * _hoops_PPCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points, RGBA const *colors, _hoops_ARPA const *planes,
					float const *params, int param_width, Integer32 param_flags);

typedef void (ACTION_CALL * _hoops_IGCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_CRCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points, RGBAS32 const *color, bool _hoops_AIPSP);
typedef void (ACTION_CALL * _hoops_GACHP)
				(Net_Rendition const * nr, int count, DC_Point const *points, RGBAS32 const *colors);
typedef void (ACTION_CALL * _hoops_RACHP)
				(Net_Rendition const * nr, int count, DC_Point const *points, RGBA const *colors, _hoops_ARPA const *planes);
typedef void (ACTION_CALL * _hoops_AACHP)
				(Net_Rendition const * nr, int count, DC_Point const *points, RGBA const *colors, _hoops_ARPA const *planes,
					float const *params, int param_width, Integer32 param_flags);

typedef void (ACTION_CALL * _hoops_IPCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points, float const *rotations, float const *size_fixups);
typedef void (ACTION_CALL * _hoops_CPCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points,
						RGBAS32 const *color, bool _hoops_AIPSP, float const *rotations, float const *size_fixups);

typedef void (ACTION_CALL * _hoops_PIPSP)
				(Net_Rendition const * nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_HIPSP)
				(Net_Rendition const * nr, int count, DC_Point const *points, RGBAS32 const *color, bool single);


typedef void (ACTION_CALL * _hoops_HACHP)
				(Net_Rendition const * nr, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_CACHP)
				(Net_Rendition const * nr, DC_Point const *points, RGBAS32 const *color);
typedef void (ACTION_CALL * _hoops_GPCHP)
				(Net_Rendition const * nr, DC_Point const *points, RGBAS32 const *colors);
typedef void (ACTION_CALL * _hoops_HPCHP)
				(Net_Rendition const * nr, DC_Point const *points, RGBA const *colors, _hoops_ARPA const *planes,
					float const *params, int param_width, Integer32 param_flags);

typedef void (ACTION_CALL * _hoops_HRCHP)
				(Net_Rendition const * nr, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_IRCHP)
				(Net_Rendition const * nr, DC_Point const *points, RGBAS32 const *color);
typedef void (ACTION_CALL * _hoops_SRCHP)
				(Net_Rendition const * nr, DC_Point const *points, RGBAS32 const *colors);
typedef void (ACTION_CALL * _hoops_PACHP)
				(Net_Rendition const * nr, DC_Point const *points, RGBA const *colors, _hoops_ARPA const *planes,
					float const *params, int param_width, Integer32 param_flags);


typedef void (ACTION_CALL * _hoops_AGCHP)
				(Net_Rendition const * nr, DC_Point const *where);
typedef void (ACTION_CALL * _hoops_ARCHP)
				(Net_Rendition const * nr, DC_Point const *where, RGBAS32 const *color);

typedef void (ACTION_CALL * _hoops_GRCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_PRCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points, RGBAS32 const *color);

typedef void (ACTION_CALL * _hoops_SGCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points);

typedef void (ACTION_CALL * _hoops_GHCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_AHCHP)
				(Net_Rendition const * nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_PHCHP)
				(Net_Rendition const * nr, Text_Info const *info);


typedef void (ACTION_CALL * _hoops_HCCHP)
				(Net_Rendition const * nr, Int_Rectangle const *extent);
typedef void (ACTION_CALL * _hoops_ICCHP)
				(Net_Rendition const * nr, Int_Rectangle const *extent, Int_Rectangle alter *frame, bool calculate_only);



typedef void (ACTION_CALL * _hoops_AIIGA)
				(Net_Rendition const * nr, Cylinder const *_hoops_CPSSA);
typedef void (ACTION_CALL * _hoops_GCIGA)
				(Net_Rendition const * nr, Ellipse const *_hoops_IHHIR);
typedef void (ACTION_CALL * _hoops_ACIGA)
				(Net_Rendition const * nr, Elliptical_Arc const *_hoops_IIPSP);
typedef void (ACTION_CALL * _hoops_CCIGA)
				(Net_Rendition const * nr, Grid const *_hoops_RRA);
typedef void (ACTION_CALL * _hoops_IICHP)
				(Net_Rendition const * nr, Image const *img);
typedef void (ACTION_CALL * _hoops_IHCHP)
				(Net_Rendition const * nr, Marker const *pl);
typedef void (ACTION_CALL * _hoops_CIPSP)
				(Net_Rendition const * nr, _hoops_GRPGR const *_hoops_CPAI);
typedef void (ACTION_CALL * _hoops_CGSHP)
				(Net_Rendition const * nr, _hoops_PIRGR const *_hoops_SIPSP);
typedef void (ACTION_CALL * _hoops_GIIGA)
				(Net_Rendition const * nr, _hoops_APPGR const *_hoops_GCPSP);
typedef void (ACTION_CALL * _hoops_HIIGA)
				(Net_Rendition const * nr, PolyCylinder const *_hoops_RCPSP);
typedef void (ACTION_CALL * _hoops_HCIGA)
				(Net_Rendition const * nr, Polygon const *_hoops_RPIGA);
typedef void (ACTION_CALL * _hoops_CHIGA)
				(Net_Rendition const * nr, Polyhedron const *_hoops_HPGPR);
typedef void (ACTION_CALL * _hoops_CHCHP)
				(Net_Rendition const * nr, Polyline const *pl);
typedef void (ACTION_CALL * _hoops_CIIGA)
				(Net_Rendition const * nr, Sphere const *s);
typedef void (ACTION_CALL * _hoops_HICHP)
				(Net_Rendition const * nr, _hoops_HACC const *tx);

typedef void (ACTION_CALL * _hoops_CICHP)
				(Net_Rendition const * nr, Geometry const *g);

typedef void (ACTION_CALL * _hoops_PICHP)
				(Net_Rendition const * nr, Tristrip const *ts);
typedef void (ACTION_CALL * _hoops_RICHP)
				(Net_Rendition const * nr, Polyedge const *pe);
typedef void (ACTION_CALL * _hoops_AICHP)
				(Net_Rendition const * nr, Polymarker const *pm);
typedef void (ACTION_CALL * _hoops_ACPSP)
				(Net_Rendition const * nr, Polyedge const *pe, Tristrip const *ts);

typedef void (ACTION_CALL * _hoops_GICHP)
				(Net_Rendition const * nr, _hoops_PRHIR const *_hoops_PCPSP);
typedef void (ACTION_CALL * _hoops_RCCHP)
				(Net_Rendition const * nr, Polyline const *pl);
typedef void (ACTION_CALL * _hoops_PCCHP)
				(Net_Rendition const * nr, Polygon const *_hoops_RPIGA);


typedef void (ACTION_CALL * _hoops_CCCHP)
				(Net_Rendition const * nr, Segment_Info const *info);
typedef void (ACTION_CALL * _hoops_SCCHP)
				(Net_Rendition const * nr, Segment_Info const *info);


typedef void (ACTION_CALL * _hoops_PRSHP)(Net_Rendition const * nr);

typedef void (ACTION_CALL * _hoops_RSCHP)
				(Net_Rendition const * nr);
typedef void (ACTION_CALL * _hoops_PSCHP)
				(Net_Rendition const * nr);


typedef void (ACTION_CALL * _hoops_RGSHP)
				(Net_Rendition const * nr, bool swap_buffers);


typedef void (ACTION_CALL * _hoops_AGSHP)
				(Net_Rendition const * nr, Int_Rectangle const *area,
					void alter * alter *image_buffer, void alter * alter *z_buffer);
typedef void (ACTION_CALL * _hoops_PGSHP)
				(Net_Rendition const * nr, Int_Rectangle const *area,
					void alter *image_buffer, void alter *z_buffer);
typedef void (ACTION_CALL * _hoops_HGSHP)
				(Net_Rendition const * nr, Int_Rectangle const *area,
					void alter *image_buffer, void alter *z_buffer);
typedef void (ACTION_CALL * _hoops_IGSHP)
				(Net_Rendition const * nr, void alter *image_buffer, void alter *z_buffer);

typedef void (ACTION_CALL * _hoops_GRSHP)
				(Net_Rendition const * nr, Key key);

typedef void (ACTION_CALL * _hoops_RRSHP)
				(Net_Rendition const * nr, int driver_type, int geom_type, int geom_bits, void *thing);

typedef Integer32	_hoops_PRGIP;
typedef unsigned Integer32	Action_Mask;

struct Internal_Action_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Action_Rendition>;

	public:

		struct {

			_hoops_IACHP				draw_dc_polytriangle;
			_hoops_SACHP	draw_dc_colorized_polytriangle;
			_hoops_RPCHP		draw_dc_gouraud_polytriangle;
			_hoops_APCHP		draw_dc_phong_polytriangle;
			_hoops_PPCHP		draw_dc_textured_polytriangle;

			_hoops_IGCHP					draw_dc_polyline;
			_hoops_CRCHP		draw_dc_colorized_polyline;
			_hoops_GACHP			draw_dc_gouraud_polyline;
			_hoops_RACHP			draw_dc_phong_polyline;
			_hoops_AACHP			draw_dc_textured_polyline;

			_hoops_IPCHP				draw_dc_polymarker;
			_hoops_CPCHP		draw_dc_colorized_polymarker;
			_hoops_PIPSP					draw_dc_polydot;
			_hoops_HIPSP			draw_dc_colorized_polydot;

			_hoops_HACHP					draw_dc_triangle;
			_hoops_CACHP		draw_dc_colorized_triangle;
			_hoops_GPCHP			draw_dc_gouraud_triangle;
			_hoops_HPCHP			draw_dc_reshaded_triangle;

			_hoops_HRCHP						draw_dc_line;
			_hoops_IRCHP			draw_dc_colorized_line;
			_hoops_SRCHP				draw_dc_gouraud_line;
			_hoops_PACHP				draw_dc_reshaded_line;

			_hoops_AGCHP					draw_dc_marker;
			_hoops_ARCHP			draw_dc_colorized_marker;

			_hoops_GRCHP						draw_dc_face;
			_hoops_PRCHP			draw_dc_colorized_face;

			_hoops_SGCHP						draw_dc_edge;

			_hoops_PHCHP							draw_text;
			_hoops_GHCHP				_hoops_SPCHP;
			_hoops_AHCHP					_hoops_RHCHP;

			_hoops_HCCHP						draw_window;
			_hoops_ICCHP					draw_window_frame;

			_hoops_IHCHP					draw_3d_marker;
			_hoops_CIPSP				_hoops_RIICP;
			_hoops_CHCHP					draw_3d_polyline;
			_hoops_CHCHP					draw_3d_infinite_line;
			_hoops_HCIGA					draw_3d_polygon;
			_hoops_CHIGA				draw_3d_polyhedron;
			_hoops_CGSHP				draw_3d_nurbs_curve;
			_hoops_GIIGA				draw_3d_nurbs_surface;
			_hoops_AIIGA					draw_3d_cylinder;
			_hoops_HIIGA				draw_3d_polycylinder;
			_hoops_CIIGA					draw_3d_sphere;
			_hoops_HICHP						draw_3d_text;
			_hoops_IICHP						draw_3d_image;
			_hoops_CCIGA						draw_3d_grid;
			_hoops_GCIGA					draw_3d_ellipse;
			_hoops_ACIGA			draw_3d_elliptical_arc;

			_hoops_CICHP					draw_3d_geometry;

			_hoops_GICHP					_hoops_SHCHP;
			_hoops_RICHP					draw_3d_polyedge;
			_hoops_AICHP				draw_3d_polymarker;
			_hoops_PICHP					draw_3d_tristrip;
			_hoops_RCCHP				_hoops_GCCHP;
			_hoops_PCCHP				_hoops_ACCHP;

			_hoops_CCCHP						draw_segment;
			_hoops_SCCHP					draw_segment_tree;

			_hoops_RSCHP					_hoops_GSCHP;
			_hoops_PSCHP					_hoops_ASCHP;

			_hoops_IGCHP					_hoops_HSCHP;
			_hoops_RICHP					draw_3d_isoline;

			_hoops_IGCHP					_hoops_ISCHP;
			_hoops_AGCHP					_hoops_CSCHP;
			_hoops_IGCHP					_hoops_SSCHP;
			_hoops_AGCHP					_hoops_GGSHP;
			_hoops_PIPSP					_hoops_HCPSP;
			_hoops_PIPSP					_hoops_ICPSP;
			_hoops_HIPSP			_hoops_CCPSP;
			_hoops_HIPSP			_hoops_SCPSP;

			_hoops_RGSHP					finish_picture;

			_hoops_AGSHP						create_region;
			_hoops_PGSHP						_hoops_HIPGR;
			_hoops_HGSHP					_hoops_PIPGR;
			_hoops_IGSHP					_hoops_ISPGR;

			_hoops_GRSHP					_hoops_SGSHP;

			_hoops_RRSHP						set_shader;

			_hoops_PRSHP					_hoops_ARSHP;

		} action;

		_hoops_CRCP const **		_hoops_RGCHP;
		void const **			_hoops_AIACR;

		_hoops_PRGIP			_hoops_PGCHP;
		Action_Mask				action_mask;

		int						_hoops_GGCHP;

	public:
		HOOPS_API Internal_Action_Rendition (Internal_Action_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Action_Rendition ();

	private:
		Internal_Action_Rendition (Display_Context const * dc);
};
typedef Rendition_Pointer<Internal_Action_Rendition>	_hoops_PSIHP;




#define _hoops_GAHPP							(_hoops_PRGIP)0x00000001
#define _hoops_CRSI					(_hoops_PRGIP)0x00000002
#define _hoops_SRSI					(_hoops_PRGIP)0x00000004
#define _hoops_CSGGR						(_hoops_PRGIP)0x00000008
#define _hoops_CRHPP						(_hoops_PRGIP)0x00000010
#define _hoops_SARIP					(_hoops_PRGIP)0x00000020
#define _hoops_GSSHP					(_hoops_PRGIP)0x00000040
#define _hoops_RRSIP				(_hoops_PRGIP)0x00000080
#define _hoops_AIPIP						(_hoops_PRGIP)0x00000100
#define _hoops_CISHP	(_hoops_PRGIP)0x00000200
#define _hoops_RSSHP		(_hoops_PRGIP)0x00000400
#define _hoops_RRCHP			(_hoops_PRGIP)0x00000800
#define _hoops_CGCHP			(_hoops_PRGIP)0x00001000
#define _hoops_GPRIP				(_hoops_PRGIP)0x00002000
#define _hoops_HGCHP			(_hoops_PRGIP)0x00004000
#define _hoops_PRHIP				(_hoops_PRGIP)0x00008000
#define _hoops_HHCHP			(_hoops_PRGIP)0x00010000
#define _hoops_AHIHP				(_hoops_PRGIP)0x00020000
#define _hoops_SRGIP					(_hoops_PRGIP)0x00040000
#define _hoops_HSGGR				(_hoops_PRGIP)0x00080000
#define _hoops_CSPPP					(_hoops_PRGIP)0x00100000
#define _hoops_GSPSP					(_hoops_PRGIP)0x00200000
#define _hoops_ISGGR				(_hoops_PRGIP)0x00400000
#define _hoops_HSSHP						(_hoops_PRGIP)0x00800000
#define _hoops_RPCIP					(_hoops_PRGIP)0x80000000

/* _hoops_HAR _hoops_CPSA _hoops_IRS _hoops_PIAP _hoops_HIH _hoops_IRS _hoops_RIP _hoops_IH _hoops_IRS _hoops_GRH _hoops_AGIR, _hoops_RGCI _hoops_IPI *_hoops_CGH*
 * _hoops_IIP _hoops_RAGS _hoops_CCA _hoops_RSPSP, _hoops_HIS _hoops_SR _hoops_PAH _hoops_SGH _hoops_RH _hoops_PSHR _hoops_IGRH
 */
#define _hoops_PGCGA		(_hoops_PRGIP)0x80000000

#define _hoops_IRGIP			\
	   (_hoops_CSGGR|_hoops_RSSHP|_hoops_GSSHP|_hoops_HSSHP)

#define _hoops_HPGSP			\
		(_hoops_RRCHP|_hoops_CGCHP| \
		 _hoops_HGCHP|_hoops_HHCHP)

#define _hoops_CGHPP		(_hoops_CSPPP)


#define _hoops_ICHHP								0x00000000
#define _hoops_PHIHP			0x00000001
#define _hoops_ACSHP			0x00000002
#define _hoops_IASHP		0x00000004
#define _hoops_IPIHP			0x00000010
#define _hoops_HHIHP								0x00000020
#define _hoops_HARIP			0x00000040
#define _hoops_GSGIP			0x00000080

#define _hoops_ASPSP	(_hoops_PHIHP | _hoops_ACSHP | \
								 _hoops_IASHP | _hoops_IPIHP)


#define _hoops_PSPSP				0x00000100

#define _hoops_PHSHP				0x00010000
#define _hoops_HHSHP					0x00020000
#define _hoops_GHSHP					0x00040000
#define _hoops_SPSHP						0x00080000
#define _hoops_AHSHP							0x00100000
#define _hoops_CPSHP					0x00200000
#define _hoops_IPSHP							0x00400000
#define _hoops_SISHP						0x00800000
#define _hoops_RRGIP						0x01000000
#define _hoops_HRSHP						0x02000000
#define _hoops_AHGIP						0x04000000
#define _hoops_HSPSP							0x08000000


struct Internal_Net_Rendition : public _hoops_CPASP {
	friend class Rendition_Pointer<Internal_Net_Rendition>;

	public:

		int							flags;
		_hoops_PRGIP				current;
		_hoops_PRGIP				_hoops_RCSHR;
		int							_hoops_RGPGR;
		_hoops_ACHR					_hoops_RGP;
		_hoops_ACHR					_hoops_PSGI;

		_hoops_PSIHP			_hoops_RSGC;
		_hoops_ISHHP			_hoops_ASIR;
		_hoops_GRA			_hoops_ARA;
		_hoops_GHRIP				glyph_rendition;
		_hoops_RIGIP		_hoops_PIGIP;
		_hoops_PHRIP		_hoops_GCSHP;	
		_hoops_GRGH				_hoops_IRR;
		_hoops_IPRIP			_hoops_GCCSR;
		_hoops_HHCR			transform_rendition;
		_hoops_CIGIP				_hoops_GCGIP;
		_hoops_GCIR		_hoops_CPP;

		Line_Rendition				_hoops_RHP;
		_hoops_CIGA				_hoops_IHA;
		Line_Rendition				_hoops_AHP;
		_hoops_ICP			_hoops_GSP;
		_hoops_IGCSR				_hoops_SISI;
		_hoops_ICP			_hoops_SCP;
		_hoops_CGRA			_hoops_SAIR;

		Line_Rendition				_hoops_CAIHP;
		_hoops_CIGA				_hoops_HAIHP;
		_hoops_CIGA				_hoops_AAIHP;


		// _hoops_HPGR _hoops_CHGC _hoops_CCGR _hoops_HCR _hoops_RH _hoops_ISPAA _hoops_CHR _hoops_GACC _hoops_ISPSP _hoops_CICRR,
		// _hoops_HIH _hoops_GAAP _hoops_SR _hoops_HHGC _hoops_SAHR _hoops_SPR _hoops_IPS _hoops_IIGR _hoops_RH _hoops_RRGR _hoops_RIIA _hoops_IIGR _hoops_SSRR _hoops_CSPSP...
	public:
		HOOPS_API Internal_Net_Rendition(Internal_Net_Rendition const & _hoops_HACIR);
		HOOPS_API ~Internal_Net_Rendition();

	private:
		Internal_Net_Rendition (Display_Context const * dc);
};






#define _hoops_SSPSP			24				/* _hoops_GGHSP(_hoops_RGHSP)*8 */
#define _hoops_HSCHA			((1<<_hoops_SSPSP)-1)
#define _hoops_GGGCR	0x7F7F7F7F
#define	_hoops_ISSIR(_hoops_AGHSP)((_hoops_AGHSP)->_hoops_RIPHP)

struct _hoops_PGHSP {
		DC_Point const		*point;
		RGBAS32 const			*color;

		_hoops_ARPA const			*plane;
		float const				*_hoops_HGHSP;		/* _hoops_PSGR _hoops_IGIR */

		/* _hoops_HGGPA _hoops_RCIC			_hoops_AIHSR; */
};

struct _hoops_IGHSP {
	/* _hoops_RIR-_hoops_GPHA _hoops_HSH (_hoops_III=2, _hoops_SCPH=3, _hoops_ARRGR=4 (_hoops_GCPP,_hoops_HGICP,_hoops_CGHSP,_hoops_SGHSP) */
	_hoops_PGHSP		vertex[4];

	/* _hoops_RIR-_hoops_CARRA _hoops_HSH */
	Key				key;
	Driver_Color		color;
	int					_hoops_GRHSP;

/* _hoops_SGI _hoops_IH _hoops_APSAR _hoops_PGAP _hoops_GHCA _hoops_SHH _hoops_RRHSP, _hoops_ARHSP, _hoops_PPR _hoops_PRHSP */
#define _hoops_HRHSP		0x0000	/*	   */
#define _hoops_IRHSP		0x0001	/* _hoops_CRHSP */
#define _hoops_SRHSP		0x0002	/* _hoops_GAHSP  */
#define _hoops_GPSCP		0x0004	/*	_hoops_GRGGR  */
#define FBI_OCCLUSION	0x0008	/*	_hoops_GRGGR  */
#define _hoops_RAHSP		0x0002	/*	 _hoops_GHAP */
#define _hoops_AAHSP		0x0004	/*	 _hoops_GHAP */
#define _hoops_PAHSP		0x0008	/*	 _hoops_GHAP */

	struct {
		int				_hoops_PPCCP;
		int				test;
		int				update;
	}					_hoops_AIPRA,		/* _hoops_PCPA _hoops_IRS _hoops_API _hoops_HCAGR _hoops_RHAP */
						required,		/* _hoops_GRH _hoops_ASCA _hoops_CAPRR _hoops_RRP _hoops_AGCR */
						_hoops_SASCP;		/*	 _hoops_HIH _hoops_HAR _hoops_AGCR */


#define _hoops_HAHSP		0x00
#define _hoops_IAHSP		0x01
#define TEST_EQUAL		0x02
#define TEST_GREATER	0x04
#define _hoops_ACSCP		0x03
#define _hoops_CAHSP		0x06
#define _hoops_SAHSP	0x05
#define _hoops_GPHSP		0x07
	int					_hoops_RCSCP;
	int					_hoops_RPHSP;

	int					_hoops_APHSP;

#define _hoops_PPHSP		0
#define _hoops_HPHSP	1
#define _hoops_IPHSP		2
#define _hoops_CPHSP		3
#define _hoops_SPHSP	4
#define _hoops_GHHSP		5
	int					_hoops_RRIH;
	int					_hoops_PRIH;
	int					_hoops_RHHSP;

	int					_hoops_AHHSP;
	int					_hoops_PHHSP;	/* _hoops_CPSA _hoops_RRI _hoops_IIPR :) */
};


struct _hoops_HCSIR {
	_hoops_HCSIR *		next;
	_hoops_HCSIR **	backlink;

	_hoops_AHAGR			*_hoops_SISCP;
	/* _hoops_HHHSP _hoops_IH _hoops_RH _hoops_ICCGR _hoops_SSH-_hoops_SRHR */
	Image alter				*_hoops_HIAI;
	Image alter				*depth_buffer;
	void alter				*_hoops_IASCP;
	void alter				*_hoops_HASCP;

	Image_Format			_hoops_GCSCP;
	bool					_hoops_ISSCP;

	Int_XY					offset;					/* _hoops_IPS _hoops_IIGR _hoops_CPSP->_hoops_CRRPA */
	Net_Rendition			_hoops_RSSCP;
	bool					_hoops_GHIAA;
	bool					_hoops_RPSCP;
	bool					_hoops_HRSCP;
	bool					_hoops_GRGSP;
	bool					_hoops_IHHSP;
	bool					_hoops_PCGSP;
	_hoops_CPSCP alter		*_hoops_GHSCP;
	_hoops_CGRA		_hoops_SAIR;

	/* _hoops_APSAR _hoops_IGI _hoops_HPP _hoops_IAGIP */
	void alter				*_hoops_AIIIP[2];
	void alter				*_hoops_GCIIP[2];
	Image alter				*_hoops_RIIIP;
	Image alter				*_hoops_SCSCP;
	void alter				*_hoops_CCSCP;
	void alter				*_hoops_GSSCP;
	Int_Rectangle			_hoops_SIIIP;
	Int_Rectangle			_hoops_PCIIP;
	Int_Rectangle			_hoops_HCIIP;
	bool					_hoops_PSPIP;
	bool					_hoops_SCIIP;

	_hoops_IGHSP				input;
	Image alter				*_hoops_HCSCP;
	void alter				*_hoops_ICSCP;
	Image_Format			_hoops_PSSCP;
	Int_Rectangle			_hoops_CHHSP;
	unsigned Integer32		_hoops_HSGSP;
};






struct _hoops_RRSGA {
	_hoops_RRSGA				*next;
	Geometry					*geometry;
	int							_hoops_AAHGA;
};

struct _hoops_PHSGA {
	_hoops_RRSGA				*_hoops_RHSGA;
	Driver_Color				_hoops_RSISR;
	Driver_Color				_hoops_IHSGA;
	Driver_Color				_hoops_SHHSP;
	Driver_Color				_hoops_GIHSP;
	bool						valid;
};



struct _hoops_CHCGP {
	bool						valid;
	bool						_hoops_CHSS;
	bool						_hoops_APGGR;
	bool						used;
	Integer32					time_stamp;
	bool						_hoops_RIHSP;
	Net_Rendition				master_rendition;
};

struct _hoops_CPSS : public _hoops_CHCGP {
	Image *						image;
	_hoops_RCR *					texture;
	Point						points[5];
	float						_hoops_CHRP, _hoops_SHRP;
	float						_hoops_AIHSP;
};


struct _hoops_GSAR  : public _hoops_CHCGP {
	_hoops_GSAR const *			next;

	_hoops_GACR *				_hoops_PACR;

	Key							_hoops_PCASP;
	float						_hoops_PIHSP[16];
	float						_hoops_HIHSP[16];
	float						_hoops_IIHSP;

	/* _hoops_HCIC _hoops_RGR _hoops_IRS _hoops_RAR-_hoops_AAR _hoops_APR? _hoops_CGP _hoops_HIS, _hoops_RH _hoops_HSPR _hoops_HPHS _hoops_GRS _hoops_SHH _hoops_APIP. */
	bool						_hoops_SAR;

	/* _hoops_GRSH _hoops_AHPH _hoops_CACR _hoops_SCAR _hoops_AA _hoops_SR _hoops_GCGH? */
	enum { _hoops_RSAR = 4 };

	/* _hoops_CIHSP _hoops_IIGR _hoops_IRS _hoops_RSRA _hoops_CHRA _hoops_ARAA. */
	struct _hoops_APCR
	{
		Vector size;
		Point _hoops_CPAA;
		float _hoops_RICR, _hoops_AICR;

		/* _hoops_HCIC _hoops_RGR _hoops_ARAA _hoops_CISI? _hoops_CGP _hoops_HAR, _hoops_AA _hoops_HAR _hoops_SRGS _hoops_PAR _hoops_SGH _hoops_SCH. */
		bool _hoops_CPCR;
	};

	/* _hoops_SIHSP _hoops_IH _hoops_RH _hoops_SCGR _hoops_CHRA */
	_hoops_APCR _hoops_HPCR[_hoops_RSAR];

	/* _hoops_AHH: _hoops_GCHSP _hoops_HSH _hoops_IH _hoops_SPCHR _hoops_RCHSP _hoops_HII _hoops_RHPP. _hoops_ACHSP _hoops_HGCR _hoops_RIPPR. */
	float _hoops_SCCS, _hoops_GSCS;
};


struct _hoops_PCHSP {
	_hoops_PCHSP *			next;
	_hoops_CRCP const *			segment;
	_hoops_HICS			path;
	_hoops_SASC			_hoops_RCHS;		/* _hoops_CGGPR, _hoops_AHPA */
};

struct _hoops_HCHSP {
	_hoops_HCHSP *		_hoops_SCAAR;
	_hoops_HCHSP **		_hoops_ICHSP;
	_hoops_PCHSP *	items;
	void *			_hoops_CCHSP;
	_hoops_SASC	limits;			/* _hoops_CGGPR, _hoops_AHPA _hoops_IIGR _hoops_SCHSP _hoops_GIIS*/
	_hoops_SASC	_hoops_RCHS;			/* _hoops_CGGPR, _hoops_AHPA _hoops_IIGR _hoops_CPAP */
	int				count;			/* _hoops_PHI _hoops_IIGR _hoops_APSAR _hoops_RPP _hoops_HAR _hoops_GSHSP */
/* _hoops_HAGC _hoops_RH _hoops_SRS 2 _hoops_SCHSP _hoops_SGI _hoops_PSSP _hoops_CAGH _hoops_SGI _hoops_IHIGR _hoops_RPGS _hoops_RRGR */
#define _hoops_RSHSP			_hoops_ACHGP
#define _hoops_ASHSP			_hoops_PCHGP
#define _hoops_PSHSP	_hoops_PRSIR		/* _hoops_PA _hoops_HAGH */
	int				flags;

	int				_hoops_HSHSP;
	int				_hoops_ISHSP;
};




struct _hoops_PGSGP {
	_hoops_HCHSP *		root;
	_hoops_CSHSP *	_hoops_SSHSP;
	int				_hoops_GGISP;
	int				_hoops_RGISP;
	_hoops_SASC	_hoops_RCHS;		/* _hoops_CGGPR, _hoops_AHPA _hoops_IIGR _hoops_CPAP */
	float			_hoops_AGISP;
};


struct _hoops_PGISP {
	_hoops_PGISP	*	next;
	Net_Rendition		nr;
	_hoops_PGSGP *		_hoops_HGISP;
};


struct DC_Polydot_Batch {
	DC_Point *					pts;
	RGBAS32	*					colors;
	int							allocated;
	int							used;
};


#define _hoops_GIHHP				((_hoops_GARSR)-1)

struct _hoops_SHHHP {
	_hoops_SHHHP alter *		next;
	_hoops_GARSR					index;
	Driver_Color				_hoops_HSHCP; /* _hoops_SHR ._hoops_AIHSR */
};

struct _hoops_HIIHP {
	_hoops_HIIHP alter *		next;
	_hoops_RHAH const	*			_hoops_IGISP;
	_hoops_GARSR					_hoops_SIIHP;
	int							length;
	bool						_hoops_CGISP;
};




/**********************************************************************

	_hoops_IPCP _hoops_ASCA _hoops_ICPPR _hoops_IH _hoops_GRR _hoops_CHCA, _hoops_AHSAR _hoops_CCGI, _hoops_PSSI,
	_hoops_PPR _hoops_AHHA, _hoops_HRGR:

		3D				- _hoops_RHAP _hoops_HIHP-_hoops_PPR-_hoops_HSPH
		_hoops_SGISP			- _hoops_RHAP _hoops_HPPA _hoops_GHC
		_hoops_GRISP				- _hoops_RHAP _hoops_RRISP _hoops_RSSI/_hoops_PGRC
		_hoops_ARISP			- _hoops_RCGPA _hoops_RRR _hoops_CRGR _hoops_IRS _hoops_IRGH _hoops_HAIR
			_hoops_PRISP	- _hoops_HRISP _hoops_IS _hoops_HPGCR _hoops_HIPH
						   (_hoops_PAR _hoops_SAGGR _hoops_RGRGR _hoops_HPP _hoops_CCSHP)
		_hoops_SHCA _hoops_ISSS	- _hoops_IPSP _hoops_RHAP _hoops_PCPA _hoops_GRI/_hoops_IRISP _hoops_APSI
		_hoops_CRISP		- _hoops_ICCGR _hoops_CCSHP-_hoops_AARAR _hoops_IHPS
		_hoops_SHCA				- _hoops_RRRS

	*_hoops_GPGP _hoops_SGS _hoops_AGR.*   _hoops_RAPAR _hoops_ASAH _hoops_HRGR _hoops_HGSAR _hoops_IH _hoops_HAGC _hoops_RCRR _hoops_SGS
	_hoops_RH _hoops_SPS "_hoops_HAHH" _hoops_ASAH _hoops_HRGR _hoops_PIGS, _hoops_GGR _hoops_ICPPR. _hoops_HSRR _hoops_HICIP,
	"_hoops_HAHH" _hoops_PSHRR _hoops_SAGGR _hoops_AISP _hoops_HPP _hoops_RH _hoops_CIS _hoops_HRII _hoops_HSAR _hoops_RH
	_hoops_SRISP.

	_hoops_HSRR _hoops_CCGI, _hoops_PSSI, _hoops_AHHA, _hoops_RH _hoops_ICPPR _hoops_HRGR:

		3D_hoops_GAISP	- _hoops_IAAI _hoops_IIGR _hoops_RAISP
		_hoops_AAISP		- _hoops_RHAP _hoops_PAISP
		3D_hoops_HAISP			- _hoops_RHAP _hoops_HIHP, _hoops_HSPH/_hoops_AACC-_hoops_HHCPR, _hoops_RCA & _hoops_GHC
		_hoops_IAISP			- _hoops_RHAP _hoops_CIHH, _hoops_HPPA _hoops_GHC
		_hoops_CAISP				- _hoops_SAISP _hoops_RH _hoops_PIH, _hoops_RGCSA "_hoops_AHSC" _hoops_ARIPR, _hoops_GPISP _hoops_SHCA _hoops_HCPH
		(_hoops_SHCA _hoops_ISSS - _hoops_IPSP _hoops_RHAP _hoops_PCPA _hoops_GRI/_hoops_IRISP _hoops_APSI - _hoops_SRPR _hoops_HGPS)
		_hoops_CRISP		- _hoops_ICCGR _hoops_CCSHP-_hoops_AARAR _hoops_IHPS
		_hoops_SHCA				- _hoops_RRRS

**********************************************************************/

struct Internal_Action_Table;
typedef _hoops_AGCGP<Internal_Action_Table> _hoops_APARR;


typedef void (ACTION_CALL * _hoops_RHCGA)
				(Net_Rendition const & nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_AHCGA)
				(Net_Rendition const & nr, int count, DC_Point const *points, RGBAS32 const *color, bool single);
typedef void (ACTION_CALL * _hoops_PHCGA)
				(Net_Rendition const & nr, int count, DC_Point const *points, RGBAS32 const *colors);
typedef void (ACTION_CALL * _hoops_HHCGA)
				(Net_Rendition const & nr, int count, DC_Point const *points, RGBA const *colors, _hoops_ARPA const *planes);
typedef void (ACTION_CALL * _hoops_IHCGA)
				(Net_Rendition const & nr, int count, DC_Point const *points, RGBA const *colors, _hoops_ARPA const *planes,
					float const *params, int param_width, Integer32 param_flags);

typedef void (ACTION_CALL * _hoops_CHCGA)
				(Net_Rendition const & nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_SHCGA)
				(Net_Rendition const & nr, int count, DC_Point const *points, RGBAS32 const *color, bool _hoops_AIPSP);
typedef void (ACTION_CALL * _hoops_GICGA)
				(Net_Rendition const & nr, int count, DC_Point const *points, RGBAS32 const *colors);
typedef void (ACTION_CALL * _hoops_RICGA)
				(Net_Rendition const & nr, int count, DC_Point const *points, RGBA const *colors, _hoops_ARPA const *planes);
typedef void (ACTION_CALL * _hoops_AICGA)
				(Net_Rendition const & nr, int count, DC_Point const *points, RGBA const *colors, _hoops_ARPA const *planes,
					float const *params, int param_width, Integer32 param_flags);

typedef void (ACTION_CALL * _hoops_PICGA)
				(Net_Rendition const & nr, int count, DC_Point const *points, float const *rotations, float const *size_fixups);
typedef void (ACTION_CALL * _hoops_HICGA)
				(Net_Rendition const & nr, int count, DC_Point const *points,
						RGBAS32 const *color, bool _hoops_AIPSP, float const *rotations, float const *size_fixups);

typedef void (ACTION_CALL * _hoops_IICGA)
				(Net_Rendition const & nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * Draw_DC_Colorized_Polydot_Action)
				(Net_Rendition const & nr, int count, DC_Point const *points, RGBAS32 const *color, bool single);


typedef void (ACTION_CALL * Draw_DC_Marker_Action)
				(Net_Rendition const & nr, DC_Point const *where);
typedef void (ACTION_CALL * _hoops_RPISP)
				(Net_Rendition const & nr, DC_Point const *where, RGBAS32 const *color);

typedef void (ACTION_CALL * _hoops_SACGA)
				(Net_Rendition const & nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_GPCGA)
				(Net_Rendition const & nr, int count, DC_Point const *points, RGBAS32 const *color);

typedef void (ACTION_CALL * _hoops_APISP)
				(Net_Rendition const & nr, int count, DC_Point const *points);

typedef void (ACTION_CALL * _hoops_GHCGA)
				(Net_Rendition const & nr, DC_Point const *pts, _hoops_RAARP const *_hoops_PPISP);

typedef void (ACTION_CALL * _hoops_CPCGA)
				(Net_Rendition const & nr, DC_Point const *where, int count, unsigned short const *kstring);
typedef void (ACTION_CALL * _hoops_HPISP)
				(Net_Rendition const & nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_IPISP)
				(Net_Rendition const & nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_CPISP)
				(Net_Rendition const & nr, Text_Info const *info);

typedef void (ACTION_CALL * _hoops_APCGA)
				(Net_Rendition const & nr, int count, DC_Point const *points);
typedef void (ACTION_CALL * _hoops_PPCGA)
				(Net_Rendition const & nr, int left, int right, int bottom, int top);

typedef void (ACTION_CALL * _hoops_HACGA)
				(Net_Rendition const & nr, DC_Point const *where, DC_Point const *radius);
typedef void (ACTION_CALL * _hoops_IACGA)
				(Net_Rendition const & nr, DC_Point const *where, DC_Point const *radius);
typedef void (ACTION_CALL * _hoops_CACGA)
				(Net_Rendition const & nr, DC_Point const *where, DC_Point const *radius,
					float start, float end);

typedef void (ACTION_CALL * _hoops_SPISP)
				(Net_Rendition const & nr, DC_Point const *point);


typedef void (ACTION_CALL * _hoops_IPCGA)
				(Net_Rendition const & nr, DC_Point const *start, DC_Point const *end,
					int hoffset, Image_Format format, int row_bytes, void const *const *rasters,
					int pattern, Driver_Color const *contrast_color, Image const *db_image);

typedef void (ACTION_CALL * _hoops_SCCGA)
				(Net_Rendition const & nr, DC_Point const *start, DC_Point const *end,
					int row_bytes, unsigned char const *rasters);
typedef void (ACTION_CALL * _hoops_RSCGA)
				(Net_Rendition const & nr, DC_Point const *start, DC_Point const *end,
					int row_bytes, unsigned char const *rasters);
typedef void (ACTION_CALL * _hoops_ASCGA)
				(Net_Rendition const & nr, DC_Point const *start, DC_Point const *end,
					int row_bytes, unsigned char const *rasters);
typedef void (ACTION_CALL * _hoops_HSCGA)
				(Net_Rendition const & nr, DC_Point const *start, DC_Point const *end,
					int row_bytes, unsigned short const *rasters);
typedef void (ACTION_CALL * _hoops_ISCGA)
				(Net_Rendition const & nr, DC_Point const *start, DC_Point const *end,
					int row_bytes, RGBAS32 const *rasters);

typedef void (ACTION_CALL * _hoops_SICGA)
				(Net_Rendition const & nr, _hoops_GHISP const & _hoops_RHISP, _hoops_AHISP const *span, int _hoops_PHISP, int top);
typedef void (ACTION_CALL * _hoops_RCCGA)
				(Net_Rendition const & nr, _hoops_GHISP const & _hoops_RHISP, _hoops_AHISP const *span, int _hoops_PHISP, int top);
typedef void (ACTION_CALL * _hoops_PCCGA)
				(Net_Rendition const & nr, _hoops_GHISP const & _hoops_RHISP, _hoops_AHISP const *span, int _hoops_PHISP, int top);
typedef void (ACTION_CALL * _hoops_ICCGA)
				(Net_Rendition const & nr, _hoops_GHISP const & _hoops_RHISP, _hoops_AHISP const *span, int _hoops_PHISP, int top,
					Integer32 param_flags);


typedef void (ACTION_CALL * _hoops_HHISP)
				(Net_Rendition const & nr, Int_Rectangle const *extent);
typedef void (ACTION_CALL * _hoops_IHISP)
				(Net_Rendition const & nr, Int_Rectangle const *extent, Int_Rectangle alter *frame, bool calculate_only);




typedef void (ACTION_CALL * _hoops_PIIGA)
				(Net_Rendition const & nr, Cylinder const *_hoops_CPSSA);
typedef void (ACTION_CALL * _hoops_RCIGA)
				(Net_Rendition const & nr, Ellipse const *_hoops_IHHIR);
typedef void (ACTION_CALL * _hoops_PCIGA)
				(Net_Rendition const & nr, Elliptical_Arc const *_hoops_IIPSP);
typedef void (ACTION_CALL * _hoops_SCIGA)
				(Net_Rendition const & nr, Grid const *_hoops_RRA);
typedef void (ACTION_CALL * _hoops_ARCGA)
				(Net_Rendition const & nr, Image const *img);
typedef void (ACTION_CALL * _hoops_IRCGA)
				(Net_Rendition const & nr, Light const *_hoops_IHHIR);
typedef void (ACTION_CALL * _hoops_SGCGA)
				(Net_Rendition const & nr, Marker const *m);
typedef void (ACTION_CALL * _hoops_CHISP)
				(Net_Rendition const & nr, _hoops_GRPGR const *_hoops_CPAI);
typedef void (ACTION_CALL * _hoops_RRCGA)
				(Net_Rendition const & nr, _hoops_PIRGR const *_hoops_SIPSP);
typedef void (ACTION_CALL * _hoops_RIIGA)
				(Net_Rendition const & nr, _hoops_APPGR const *_hoops_GCPSP);
typedef void (ACTION_CALL * _hoops_IIIGA)
				(Net_Rendition const & nr, PolyCylinder const *_hoops_RCPSP);
typedef void (ACTION_CALL * _hoops_ICIGA)
				(Net_Rendition const & nr, Polygon const *_hoops_RPIGA);
typedef void (ACTION_CALL * _hoops_SHIGA)
				(Net_Rendition const & nr, Polyhedron const *_hoops_HPGPR);
typedef void (ACTION_CALL * _hoops_GRCGA)
				(Net_Rendition const & nr, Polyline const *pl);
typedef void (ACTION_CALL * _hoops_SIIGA)
				(Net_Rendition const & nr, Sphere const *s);
typedef void (ACTION_CALL * _hoops_PRCGA)
				(Net_Rendition const & nr, _hoops_HACC const *tx);

typedef void (ACTION_CALL * _hoops_SHISP)
				(Net_Rendition const & nr, Geometry const *g);

typedef void (ACTION_CALL * _hoops_PACGA)
				(Net_Rendition const & nr, Tristrip const *ts);
typedef void (ACTION_CALL * _hoops_GACGA)
				(Net_Rendition const & nr, Polyedge const *pe);
typedef void (ACTION_CALL * _hoops_AACGA)
				(Net_Rendition const & nr, Polymarker const *pm);
typedef void (ACTION_CALL * _hoops_RACGA)
				(Net_Rendition const & nr, Polyedge const *pe, Tristrip const *ts);

typedef void (ACTION_CALL * _hoops_GIISP)
				(Net_Rendition const & nr, _hoops_PRHIR const *_hoops_PCPSP);
typedef void (ACTION_CALL * _hoops_SRCGA)
				(Net_Rendition const & nr, Point const *pts, _hoops_RAARP const *_hoops_PPISP);
typedef void (ACTION_CALL * _hoops_RIISP)
				(Net_Rendition const & nr, Polyline const *pl);
typedef void (ACTION_CALL * _hoops_AIISP)
				(Net_Rendition const & nr, Polygon const *_hoops_RPIGA);


typedef void (ACTION_CALL * _hoops_PIISP)
				(Net_Rendition const & nr, Segment_Info const *info);
typedef void (ACTION_CALL * _hoops_HIISP)
				(Net_Rendition const & nr, Segment_Info const *info);


typedef void (ACTION_CALL * _hoops_IIISP)
				 (_hoops_APARR alter & _hoops_RRCI);

typedef void (ACTION_CALL * _hoops_CIISP)
				(Net_Rendition const & nr);
typedef void (ACTION_CALL * _hoops_SIISP)
				(Net_Rendition const & nr);

typedef void (ACTION_CALL * _hoops_GCISP)
				(Net_Rendition const & nr);
typedef void (ACTION_CALL * _hoops_RCISP)
				(Net_Rendition const & nr);
typedef void (ACTION_CALL * _hoops_ACISP)
				(Net_Rendition const & nr, bool swap_buffers);


typedef void (ACTION_CALL * _hoops_PCISP)
				(Net_Rendition const & nr, Int_Rectangle const *area,
					void alter * alter *image_buffer, void alter * alter *z_buffer);
typedef void (ACTION_CALL * _hoops_HCISP)
				(Net_Rendition const & nr, Int_Rectangle const *area,
					void alter *image_buffer, void alter *z_buffer);
typedef void (ACTION_CALL * _hoops_ICISP)
				(Net_Rendition const & nr, Int_Rectangle const *area,
					void alter *image_buffer, void alter *z_buffer);
typedef void (ACTION_CALL * _hoops_CCISP)
				(Net_Rendition const & nr, void alter *image_buffer, void alter *z_buffer);



typedef bool (ACTION_CALL * Update_Action)
				(Display_Context alter * dc, Activity _hoops_SCISP);

typedef void (ACTION_CALL * _hoops_GSISP)
				(Net_Rendition const & nr, _hoops_CRCP const *_hoops_SRCP, _hoops_HICS const & path);
typedef Geometry const * (ACTION_CALL * _hoops_RSISP)
				(Net_Rendition const & nr, Geometry const *geom, unsigned Integer32 mask, bool single);

typedef bool (ACTION_CALL * _hoops_ASISP)
				(Display_Context alter * dc, Selection_Event alter *_hoops_GPIIR);



typedef bool (ACTION_CALL * _hoops_PSISP)
				(Display_Context alter * dc);
typedef void (ACTION_CALL * _hoops_HSISP)
				(Display_Context alter * dc);

typedef void (ACTION_CALL * _hoops_ISISP)
				(Display_Context alter * dc);
typedef void (ACTION_CALL * _hoops_CSISP)
				(Display_Context alter * dc);

typedef void (ACTION_CALL * _hoops_SSISP)
				(Display_Context const * dc);
typedef void (ACTION_CALL * _hoops_GGCSP)
				(Display_Context const * dc);

typedef POINTER_SIZED_INT (ACTION_CALL * _hoops_RGCSP)
				(Display_Context const * dc);
typedef void (ACTION_CALL * _hoops_AGCSP)
				(Display_Context const * dc);
typedef void (ACTION_CALL * Resize_Outer_Window_Action)
				(Display_Context const * dc);
typedef void (ACTION_CALL * _hoops_PGCSP)
				(Display_Context const * dc);
typedef void (ACTION_CALL * _hoops_HGCSP)
				(Display_Context const * dc);


typedef bool (ACTION_CALL * _hoops_IGCSP)
				(Net_Rendition const & nr, Font_Instance const *_hoops_CGCSP, unsigned short _hoops_CSAIP,
					float *_hoops_GGGS, bool *_hoops_AHPGR, void ** _hoops_SPCSR);

typedef void (ACTION_CALL * _hoops_SGCSP)
				(Net_Rendition const & nr, Font_Instance const *_hoops_CGCSP, Point const *position,
					int count, unsigned short const *_hoops_CSAIP, Vector const *scale);
typedef bool (ACTION_CALL * _hoops_GRCSP)
				(Net_Rendition const & nr, _hoops_IGPIR const *_hoops_RRCSP, _hoops_IGPIR alter *_hoops_ARCSP);
					typedef void (ACTION_CALL * _hoops_PRCSP)
				(Net_Rendition const & nr, Font_Instance alter *_hoops_CGCSP);
typedef bool (ACTION_CALL * _hoops_HRCSP)
				(Net_Rendition const & nr, Font_Instance const *_hoops_CGCSP);
typedef unsigned short (ACTION_CALL * _hoops_IRCSP)
				(Font_Instance const *_hoops_CGCSP, unsigned short count);
typedef _hoops_RAARP * (ACTION_CALL * _hoops_CRCSP)
				(Net_Rendition const & nr, Font_Instance const *_hoops_CGCSP, unsigned short _hoops_SRCSP,
					int bitmap_height, int bolding_level, float _hoops_IPGRP, float rotation, float width_scale, bool antialias);




typedef void (ACTION_CALL * _hoops_SSCGA)
				(Net_Rendition const & nr, Text_Info const *text_info);
typedef void (ACTION_CALL * _hoops_GGSGA)
				(Net_Rendition const & nr, _hoops_HACC const * text, Point const * position,
					int count, unsigned short const * _hoops_IHSCP, _hoops_PGCSR const * _hoops_HGCSR);


typedef void (ACTION_CALL * Draw_Overlay_List_Action)
				(Net_Rendition const & nr);
typedef void (ACTION_CALL * Undraw_Overlay_List_Action)
				(Net_Rendition const & nr);

typedef bool (ACTION_CALL * _hoops_GACSP)
				(Display_Context const * dc, int alter *button, int alter *x, int alter *y);
typedef bool (ACTION_CALL * _hoops_RACSP)
				(Display_Context const * dc, int alter *button, int alter *status);
typedef void (ACTION_CALL * _hoops_AACSP)
				(Display_Context const * dc, unsigned int r, unsigned int g, unsigned int b, int index);


typedef bool (ACTION_CALL * _hoops_PACSP)
				(Display_Context alter * dc, char const *name);
typedef void (ACTION_CALL * _hoops_HACSP)
				(Display_Context alter * dc);
typedef void * (ACTION_CALL * _hoops_IACSP)
				(Display_Context const * dc, char const *name, Font_Instance alter *instance);
typedef void (ACTION_CALL * _hoops_CACSP)
				(Display_Context const * dc, Font_Instance alter *instance);

typedef void (ACTION_CALL * _hoops_SACSP)
				(Net_Rendition const & nr, int left, int right, int bottom, int top);

typedef void (ACTION_CALL * _hoops_GPCSP)
				(Net_Rendition const & nr, _hoops_PC const & _hoops_RPPHP, _hoops_HHA const & _hoops_RRGH,
					Point const *_hoops_ICAGA, RGB const *color, _hoops_ARPA const *plane, Vector const *_hoops_ASACP,
					float const *params, int param_width, int param_flags,
					RGBA alter *result, RGBA alter *_hoops_RPCSP);

typedef void (ACTION_CALL * _hoops_APCSP)
				(Net_Rendition const & nr, long priority);
typedef void (ACTION_CALL * _hoops_PPCSP)
				(Net_Rendition const & nr);

typedef void (ACTION_CALL * _hoops_HPCSP)
				(Display_Context const * dc);


typedef void (ACTION_CALL * _hoops_IPCSP)
				 (Display_Context const * dc, void * id);


typedef void * (ACTION_CALL * _hoops_CPCSP)
				(Net_Rendition const & nr, bool disable_write);
typedef void (ACTION_CALL * _hoops_SPCSP)
				(Net_Rendition const & nr, void * id);
typedef int (ACTION_CALL * _hoops_GHCSP)
				(Net_Rendition const & nr, void * id);
typedef void (ACTION_CALL * _hoops_RHCSP)
				(Net_Rendition const & nr, void * id);


typedef void (ACTION_CALL * _hoops_AHCSP)
				(Net_Rendition const & nr, int width, int height, Image_Format format,
					Image alter * alter *image, void alter * alter *_hoops_PISCP);
typedef void (ACTION_CALL * _hoops_PHCSP)
				(Net_Rendition const & nr, DC_Point const *start, DC_Point const *end,
					Image const *image, int hoffset, int voffset, void const *_hoops_PISCP);
typedef void (ACTION_CALL * _hoops_HHCSP)
				(Net_Rendition const & nr, Image alter *buffer, void alter *_hoops_PISCP);


typedef bool (ACTION_CALL * _hoops_IHCSP) (Net_Rendition const & nr, void const *data);


typedef bool (ACTION_CALL * _hoops_CHCSP)
				(Net_Rendition const & nr, int width, int height, unsigned char alter *data);

typedef void (ACTION_CALL * _hoops_SHCSP)
				(Display_Context alter * dc);
typedef void (ACTION_CALL * _hoops_GICSP)
				(Net_Rendition const & nr, _hoops_CRCP const *_hoops_SRCP, _hoops_HICS const & path);
typedef void (ACTION_CALL * _hoops_RICSP)
				(Net_Rendition const & nr, _hoops_CRCP const *_hoops_SRCP, _hoops_HICS const & path);
typedef void (ACTION_CALL * _hoops_AICSP)
				(Net_Rendition const & nr, _hoops_CRCP const *_hoops_SRCP, _hoops_HICS const & path, float _hoops_IRIR, float radius);


typedef bool (ACTION_CALL * _hoops_PICSP)
				(Net_Rendition const & nr, _hoops_GACR **_hoops_PICI, unsigned Integer32 *mask, bool _hoops_IHGI);
typedef void (ACTION_CALL * _hoops_HICSP)
				(Net_Rendition const & nr, _hoops_GACR **_hoops_PICI, unsigned Integer32 *mask, unsigned Integer32 *_hoops_IICI);
typedef void (ACTION_CALL * _hoops_IICSP)
				(Net_Rendition const & nr, _hoops_GACR **_hoops_PICI, bool _hoops_IHGI);
typedef void (ACTION_CALL * _hoops_CICSP)
				(Net_Rendition const & nr, _hoops_GACR *_hoops_PICI);


typedef void (ACTION_CALL * _hoops_SICSP)
				(Display_Context alter * dc);
typedef void (ACTION_CALL * _hoops_GCCSP)
				(Display_Context alter * dc);


typedef void * (ACTION_CALL * _hoops_RCCSP)
				(Net_Rendition const & nr, long request, void *pointer,
					POINTER_SIZED_INT _hoops_ISPI,  POINTER_SIZED_INT _hoops_CSPI,  POINTER_SIZED_INT _hoops_SSPI, POINTER_SIZED_INT _hoops_SGHI,
					float f1, float f2, float _hoops_CGHGR, float _hoops_SGHGR);



/* _hoops_HCGI-_hoops_SHSS */
#define	_hoops_GCGI					0x00000001
#define	_hoops_SSCI				0x00000002
#define	_hoops_ASRI					0x00000004
#define	_hoops_GHCI				0x00000008
#define	_hoops_CIIP					0x00000010
#define	_hoops_AIIP				0x00000020
#define	_hoops_SHIP					0x00000040
#define	_hoops_RGPI					0x00000080
#define	_hoops_ACIP						0x00000100
#define	_hoops_ARCP						0x00000200
#define	_hoops_HCIP						0x00000400
#define	_hoops_RSRI						0x00000800
/* _hoops_GRAA-_hoops_HCGI-_hoops_SHSS */
#define	_hoops_ACCSP				0x00001000
#define	_hoops_RGCP						0x00002000
#define	_hoops_GCIP				0x00004000
#define	_hoops_PCCSP						0x00008000
#define	_hoops_IGCP						0x00010000
#define	_hoops_PGCP						0x00020000
#define	_hoops_CCIP						0x00040000
#define	_hoops_RCSI			0x00080000
#define	_hoops_ACSI				0x00100000
#define	_hoops_HCCSP		0x00200000
/* _hoops_PPRAR												0x00400000 */
/* _hoops_PPRAR												0x00800000 */
#define	_hoops_HRGC							0x01000000
#define	_hoops_IRGC								0x02000000
/* _hoops_PPRAR												0x04000000 */
/* _hoops_PPRAR												0x08000000 */
#define _hoops_PSIP					0x10000000 /* _hoops_GACC _hoops_HAHAR _hoops_PPR _hoops_CRCIA */
#define _hoops_HRCP				0x20000000
/* _hoops_PPRAR												0x40000000 */
#define _hoops_RSIP					0x80000000


#define	_hoops_IRPI (					\
			_hoops_CIIP |			\
			_hoops_AIIP |	\
			_hoops_SHIP)

#define _hoops_PGRI (					\
			_hoops_GCGI |			\
			_hoops_SSCI)

#define _hoops_IGAI (					\
			_hoops_ASRI |			\
			_hoops_GHCI  |	\
			_hoops_RCSI |	\
			_hoops_ACSI |	\
			_hoops_HCCSP)

#define _hoops_PCSI (		\
			_hoops_PGRI |				\
			_hoops_IGAI |				\
			_hoops_RGPI |		\
			_hoops_RSRI)

#define _hoops_SHSI (				\
			_hoops_PSIP |			\
			_hoops_HRCP |		\
			_hoops_RSIP)

#define _hoops_SIII (					\
			_hoops_RGCP |				\
			_hoops_ACIP |			\
			_hoops_ARCP)

#define _hoops_RSCI (				\
			_hoops_RGPI |		\
			_hoops_HCIP |			\
			_hoops_ASRI |			\
			_hoops_GHCI |		\
			_hoops_PGRI |				\
			_hoops_ACIP |			\
			_hoops_ARCP |			\
			_hoops_IRPI)


#define	_hoops_SSIP				_hoops_PSIP
#define	_hoops_ISIP						_hoops_PSIP
#define _hoops_RAPI									0xFFFFFFFF
#define _hoops_SICHP						(_hoops_RAPI & ~(_hoops_HRGC|_hoops_IRGC))

#define	_hoops_ICCSP(_hoops_CCCSP, _type_)		ANYBIT ((_hoops_CCCSP)->_hoops_SRA->_hoops_IPCI->mask, _type_)

/* _hoops_SHH _hoops_RCRR _hoops_IS _hoops_GGCR _hoops_IS _hoops_HGCR _hoops_PGSI */
struct Internal_Action_Table : public _hoops_RGCGP {
	friend class _hoops_AGCGP<Internal_Action_Table>;

private:
	HOOPS_API Internal_Action_Table (Memory_Pool *p);

public:

	_hoops_APARR						prev;
	char const *						id;
	_hoops_PRGIP						mode;
	Action_Mask							mask;

	_hoops_PSISP						start_device;
	_hoops_HSISP						stop_device;
	_hoops_ISISP				get_physical_info;
	_hoops_CSISP					get_current_info;

	Update_Action							update;
	_hoops_GSISP						_hoops_SCCSP;
	_hoops_RSISP							_hoops_CHCI;
	_hoops_ASISP							_hoops_GSCSP;

	_hoops_SSISP						init_update;
	_hoops_GGCSP					finish_update;

	_hoops_GCISP						init_picture;
	_hoops_RCISP				_hoops_PCPGR;
	_hoops_ACISP					finish_picture;

	_hoops_RGCSP					get_outer_window;
	_hoops_AGCSP				free_outer_window;
	Resize_Outer_Window_Action				_hoops_RSCSP;
	_hoops_PGCSP				_hoops_ASCSP;

	_hoops_RCIGA					draw_3d_ellipse;
	_hoops_PCIGA			draw_3d_elliptical_arc;
	_hoops_SCIGA						draw_3d_grid;
	_hoops_SGCGA					draw_3d_marker;
	_hoops_CHISP				_hoops_RIICP;
	_hoops_GRCGA					draw_3d_polyline;
	_hoops_GRCGA					draw_3d_infinite_line;
	_hoops_RRCGA				draw_3d_nurbs_curve;
	_hoops_RIIGA			draw_3d_nurbs_surface;
	_hoops_PIIGA					draw_3d_cylinder;
	_hoops_IIIGA				draw_3d_polycylinder;
	_hoops_SIIGA					draw_3d_sphere;
	_hoops_ICIGA					draw_3d_polygon;
	_hoops_GIISP					_hoops_SHCHP;
	_hoops_ARCGA					draw_3d_image;
	_hoops_SHIGA				draw_3d_polyhedron;
	_hoops_PRCGA						draw_3d_text;
	_hoops_IRCGA					_hoops_HRCGA;

	_hoops_SRCGA			_hoops_CRCGA;

	_hoops_GACGA					draw_3d_polyedge;
	_hoops_PACGA					draw_3d_tristrip;
	_hoops_AACGA				draw_3d_polymarker;

	_hoops_GACGA					draw_silhouette_polyedge;
	_hoops_GACGA					_hoops_PSCSP;
	_hoops_RACGA	draw_3d_polyedge_from_tristrip;

	_hoops_GACGA					_hoops_PPAS;
	_hoops_PACGA					_hoops_ARCI;

	_hoops_HHISP						draw_window;
	_hoops_IHISP				draw_window_frame;

	_hoops_PPCGA				draw_dc_rectangle;

	_hoops_RHCGA				draw_dc_polytriangle;
	_hoops_AHCGA	draw_dc_colorized_polytriangle;
	_hoops_PHCGA		draw_dc_gouraud_polytriangle;
	_hoops_HHCGA		draw_dc_phong_polytriangle;
	_hoops_IHCGA	draw_dc_textured_polytriangle;
	_hoops_CHCGA					draw_dc_polyline;
	_hoops_SHCGA		draw_dc_colorized_polyline;
	_hoops_GICGA			draw_dc_gouraud_polyline;
	_hoops_RICGA			draw_dc_phong_polyline;
	_hoops_AICGA		draw_dc_textured_polyline;
	_hoops_PICGA				draw_dc_polymarker;
	_hoops_HICGA		draw_dc_colorized_polymarker;
	_hoops_IICGA					draw_dc_polydot;
	Draw_DC_Colorized_Polydot_Action		draw_dc_colorized_polydot;

	_hoops_APCGA					_hoops_RPCGA;
	_hoops_SACGA						draw_dc_face;
	_hoops_GPCGA			draw_dc_colorized_face;

	_hoops_HACGA					draw_dc_ellipse;
	_hoops_CACGA			_hoops_CCISR;
	_hoops_IACGA			_hoops_SCISR;

	_hoops_IPCGA					_hoops_HPCGA;
	_hoops_CPCGA						draw_dc_text;
	_hoops_GHCGA			_hoops_SPCGA;

	_hoops_SICGA					_hoops_CICGA;
	_hoops_RCCGA			_hoops_GCCGA;
	_hoops_PCCGA			_hoops_ACCGA;
	_hoops_ICCGA			_hoops_HCCGA;

	_hoops_SCCGA				_hoops_CCCGA;
	_hoops_RSCGA			_hoops_GSCGA;
	_hoops_ASCGA			_hoops_CCCSR;
	_hoops_HSCGA			_hoops_PSCGA;
	_hoops_ISCGA			draw_dc_rgb32_rasters;

	_hoops_SSCGA					_hoops_CSCGA;
	_hoops_GGSGA					_hoops_AGCSR;

	Draw_Overlay_List_Action				draw_overlay_list;
	Undraw_Overlay_List_Action				_hoops_SCPGR;

	_hoops_GACSP					_hoops_HSCSP;
	_hoops_RACSP					_hoops_ISCSP;

	_hoops_AACSP				_hoops_SCCSR;

	_hoops_HACSP				_hoops_CACSR;
	_hoops_HACSP				find_all_fonts;
	_hoops_PACSP					_hoops_AACSR;
	_hoops_IACSP						load_font;
	_hoops_CACSP						unload_font;
	_hoops_IGCSP						measure_char;
	_hoops_SGCSP						_hoops_SRCSR;
	_hoops_GRCSP						_hoops_CSCSP;
	_hoops_IRCSP				map_font_char_index;
	_hoops_PRCSP						_hoops_SSCSP;
	_hoops_HRCSP			_hoops_GGSSP;
	_hoops_CRCSP				_hoops_RGSSP;

	_hoops_SACSP					_hoops_CAAGR;

	_hoops_GPCSP					_hoops_AGSSP;

	_hoops_APCSP					_hoops_PGSSP;
	_hoops_PPCSP					_hoops_HGSSP;

	_hoops_AHCSP				_hoops_IGSSP;
	_hoops_PHCSP				_hoops_CGSSP;
	_hoops_HHCSP				_hoops_SGSSP;

	_hoops_HPCSP				_hoops_SSRGR;

	_hoops_IPCSP					_hoops_CGAGR;

	_hoops_CPCSP			_hoops_GRSSP;
	_hoops_SPCSP				_hoops_RRSSP;
	_hoops_GHCSP				_hoops_CRGIP;
	_hoops_RHCSP			_hoops_ARSSP;

	_hoops_PCISP					create_region;
	_hoops_HCISP						_hoops_HIPGR;
	_hoops_ICISP					_hoops_PIPGR;
	_hoops_CCISP					_hoops_ISPGR;

	_hoops_SHCSP					_hoops_RHH;

	_hoops_PICSP				_hoops_GGSI;
	_hoops_HICSP				_hoops_AICI;
	_hoops_IICSP					_hoops_AIGC;
	_hoops_CICSP				_hoops_PPCI;

	_hoops_SICSP					_hoops_CSPGR;
	_hoops_GCCSP						_hoops_AGHGR;

	_hoops_CHCSP							snapshot;
	_hoops_RCCSP						_hoops_IGHGR;

	_hoops_RICSP				_hoops_PICS;
	_hoops_GICSP			_hoops_IPSS;
	_hoops_AICSP		_hoops_GHGGR;
};
/* _hoops_SHH _hoops_RCRR _hoops_IS _hoops_GGCR _hoops_IS _hoops_HGCR _hoops_PGSI */



struct _hoops_PRSSP {
	_hoops_PCARP						flags;
	_hoops_PCARP						values;

	bool							backing_store;
	bool							border;
	bool							_hoops_HRSSP;

	bool							_hoops_IRSSP;
	bool							_hoops_CRSSP;
	bool							_hoops_SRRRR;

	bool							_hoops_RAHHP;
	bool							_hoops_SIAH;
	bool							_hoops_SRSSP;

	bool							_hoops_GASSP;
	bool							_hoops_RASSP;
	bool							_hoops_AASSP;
	bool							_hoops_PASSP;

	bool							_hoops_HPHRP;
	bool							_hoops_HASSP;
	bool							_hoops_AHIIP;
	bool							_hoops_RIPGA;
	bool							_hoops_PIPGA;
	bool							_hoops_HHHSR;
	bool							_hoops_IASSP;
	bool							_hoops_CASSP;
	bool							_hoops_SASSP;
	bool							_hoops_GPSSP;
	bool							_hoops_HPSC;
	bool							_hoops_RPSSP;
	bool							_hoops_APSSP;
	bool							_hoops_PPSSP;
	bool							_hoops_GAPP;
	bool							_hoops_RGSH;
	bool							_hoops_HPSSP;

	int								_hoops_APPIR;
	int								*_hoops_RPPIR;
	int								_hoops_IRARR;

	int								_hoops_APASR;
	int								_hoops_GCPRP;
	int								_hoops_IPSSP[3];

	int								_hoops_ARPSR;
#ifndef _hoops_PGHRP
#	define	  _hoops_PGHRP				0
#	define	  Drivo_Landscape_ON				1
#	define	  _hoops_HGHRP		2
#endif

	float							_hoops_RCPRP;
	float							_hoops_ACPRP;
	float							_hoops_PCPRP[3][2];
	Integer32						_hoops_AAPSR;
	float							_hoops_GSHSR;
	XY								_hoops_SPHSR;
	float							_hoops_SHSHA;

	_hoops_PACIR				_hoops_HCPRP;

	_hoops_HCRPR							_hoops_IAPIR;
	_hoops_IGPIR *						_hoops_SAPIR;
	_hoops_IGPIR *						_hoops_GPPIR;
	int								_hoops_GSPRP;

	POINTER_SIZED_INT				_hoops_GCHSR;
	POINTER_SIZED_INT				_hoops_ISPRP;
	POINTER_SIZED_INT				_hoops_RCHSR;
	POINTER_SIZED_INT				_hoops_CSPRP;
	int								_hoops_RGHRP;

	int								_hoops_AGHRP;
	_hoops_AAPIR *						_hoops_HAPIR;

	int								_hoops_GHHSR;
	int								_hoops_IAHRP[_hoops_HAHRP+1];
	int								_hoops_PPHRP;

	int								_hoops_AIPGA;

	float							_hoops_GAHP;

	float							_hoops_GIGP;

	int								_hoops_HSPRP;

	int								_hoops_HRSH;
	int								_hoops_IGSH;
	float							_hoops_SHSH;

	float							_hoops_SCHP;
	float							_hoops_ICHP;
	float							_hoops_HSHP;
	_hoops_IHCSP			_hoops_CPSSP;
	void *							_hoops_HSHRP;
};

struct _hoops_SPSSP {
	Integer32 const *			_hoops_GHSSP;
	bool						_hoops_RHSSP,
								_hoops_AHSSP,
								_hoops_PHSSP,
								_hoops_HHSSP;
};

enum _hoops_IHSSP {
	_hoops_ICCIP,
	_hoops_RGSIP,
	_hoops_HRSIP,
	_hoops_APSIP
};

struct _hoops_HSPPP {
	_hoops_HSPPP alter *		next;
	_hoops_CRCP const *					segment;
	_hoops_HICS					path;
	Geometry const *				geometry;
	Net_Rendition					_hoops_APHGA;
	Activity						_hoops_CPGPR;
	int								stage;
	_hoops_PRGIP					_hoops_ARSIP;
	_hoops_HSPPP alter *		_hoops_CPCR;
	bool							_hoops_SPIIP;
	float							value;
};


struct _hoops_RGHPP {
	_hoops_HSPPP alter *			list;
	_hoops_HSPPP alter * alter *	_hoops_ASRGR;
};

typedef VHeap<_hoops_RGHPP *,int, false, false> _hoops_PGHPP;
typedef VHash<int, _hoops_RGHPP *> _hoops_IGHPP;


#define _hoops_SRHPP			0
#define _hoops_IRHPP		1
#define _hoops_RAHPP				2
#define _hoops_CHSSP			3
#define _hoops_ICHS	10


struct _hoops_SHSSP {
	_hoops_SHSSP alter	*			_hoops_SSCAP;
	_hoops_HCRPR						name;
	short						type;

#	define		_hoops_GISSP		0
#	define		_hoops_RISSP		1
};

/* _hoops_AISSP _hoops_IH _hoops_AGPAA _hoops_GGR _hoops_GSPIP */
#define _hoops_PISSP			1L
#define _hoops_HISSP			2L
#define _hoops_IISSP			3L

/* _hoops_HRCSR _hoops_CSSC */
#define _hoops_CISSP				0
#define _hoops_SISSP				1
#define _hoops_ARCSR				2

#define _hoops_GCSSP					3

struct _hoops_RCSSP : public _hoops_SHSSP {	/* _hoops_RSIRR = _hoops_ACSSP _hoops_SSCHA/_hoops_GRCIR \0 */
	_hoops_RCSSP alter			*next;
	int							_hoops_RRCSR;
	bool						_hoops_PCSSP,
								_hoops_HCSSP;
	_hoops_PGIIR		const			*font;
	Font_Instance const			*_hoops_ICSSP;

	void const					*data;
};

#define _hoops_CCSSP 32

struct _hoops_SCSSP {

	/*_hoops_PIH _hoops_HRGR _hoops_IRS _hoops_GRAA-_hoops_GSSSP _hoops_CGRPR*/
	void * data;
	Font_Instance const * _hoops_RSSSP;

	int valid;

	int _hoops_ASRIP;

	float _hoops_ASSSP; /* _hoops_CSCS _hoops_GSPR _hoops_PSSSP */
	float _hoops_HSSSP; /* _hoops_PSSSP _hoops_IIGR _hoops_ISSSP */

	Karacter _hoops_CSAIP;
	Karacter _hoops_CSSSP;

};

struct Font_Instance : public _hoops_SHSSP {	/* _hoops_RSIRR = _hoops_IHIR _hoops_HHHA _hoops_RSIRR _hoops_SSCHA/ \0 */
	Font_Instance alter				*_hoops_SSSSP;		/* _hoops_GSHHR _hoops_HPP _hoops_APPS */
	Font_Instance alter				*_hoops_GGGGH;		/* _hoops_GSHHR _hoops_HPP _hoops_APPS */
	Font_Instance const				*next;					/* _hoops_RGGGH _hoops_AGR */

	_hoops_RCSSP const				*family;
	Font_Instance const				*_hoops_AGGGH;
	void *							_hoops_GAASR;		/* _hoops_APIP _hoops_CGPR _hoops_PGGGH */

#define _hoops_HGGGH 256
#define _hoops_GGPIP(k) (k&0xFF)
	_hoops_SCSSP			*_hoops_RGPIP;


	_hoops_IACSP				load_font;
	_hoops_CACSP				unload_font;
	_hoops_IGCSP				measure_char;
	_hoops_SGCSP				_hoops_SRCSR;
	_hoops_IRCSP		map_font_char_index;
	_hoops_PRCSP				_hoops_SSCSP;
	_hoops_CRCSP		_hoops_RGSSP;
	_hoops_HRCSP	_hoops_GGSSP;

	float							_hoops_ISISR;	/* _hoops_APPS _hoops_IIGR _hoops_IHHPP _hoops_RAIGR */
	float							_hoops_IGGGH;		/* _hoops_CGGGH _hoops_IRPHR _hoops_SGGGH */


	float							_hoops_GRGGH;	/* _hoops_RHAA _hoops_GGARP _hoops_IGIR _hoops_SIISR */
	float							_hoops_RACSR; /* _hoops_GPGGR _hoops_GGR _hoops_PGSA 3d _hoops_HCGR */
	float							_hoops_GCHSA;
	bool							_hoops_RRGGH;

	bool							_hoops_ARGGH;

	bool							_hoops_CGCSR;			/* _hoops_HRPP _hoops_IH _hoops_ASCA */
	bool							_hoops_PRGGH;			/* _hoops_GA'_hoops_RA _hoops_HPPR _hoops_IS _hoops_GGARP _hoops_RGR */
	bool							_hoops_HRGGH; /* _hoops_CIIHP _hoops_HPP _hoops_GGARP _hoops_HRCSR */
	_hoops_CSSGP				_hoops_IRGGH;

#define _hoops_CRGGH				0x00

#define _hoops_SRGGH			0x01	/* _hoops_CSCS _hoops_RAACR */
#define _hoops_GPCSR			0x02
#define _hoops_GAGGH				0x04
#define _hoops_RAGGH				0x08
#define _hoops_AAGGH					0x10
#define _hoops_PAGGH				0x20	/* _hoops_AA _hoops_GII _hoops_AHGGR 1 _hoops_GSPR _hoops_HPGR _hoops_IRS _hoops_GHIR */

#define _hoops_HAGGH					0x0E	/* _hoops_HPRGR _hoops_GGGRR */
#define _hoops_IAGGH				0x1E
	int								_hoops_CAGGH;

	_hoops_HCRPR							_hoops_SAGGH;
	long							_hoops_SSPAR;
	_hoops_IHGRP					encoding;		/* _hoops_IPISR _hoops_IIGR _hoops_RGR _hoops_HRCSR */
};

struct _hoops_GPGGH {
	void				*_hoops_RPGGH;
	_hoops_HCRPR				_hoops_APGGH;
	_hoops_HCRPR				_hoops_SSISR;
	_hoops_PHASP		_hoops_HSAI;
};

struct _hoops_PPGGH {
	void *			_hoops_HPGGH;
	void *			_hoops_IPGGH;
};


struct _hoops_CPGGH {
	int	count;
	int *points;
};


struct _hoops_PGCIP {
	_hoops_PGCIP *				next;
	void const *				item;
	Net_Rendition				nr;
	_hoops_ISGI const *	_hoops_IRCIP;
	_hoops_SSGI const *				_hoops_GPCP;
	int							type;
	Geometry const *			g; /* _hoops_IHIGA */
	_hoops_CRCP const *				segment;
	_hoops_HICS				path;
	/* _hoops_RPRHR _hoops_CSSC _hoops_CHR _hoops_GSSR _hoops_SPGGH _hoops_CPAP _hoops_APSAR */
#	define	_hoops_CRCIP	(-1)
#	define	_hoops_HACIP	(-2)
#	define	_hoops_CACIP	(-3)
};

struct _hoops_GHGGH {
	_hoops_HACC const *			_hoops_RHGGH;
	_hoops_PIGPR const *	_hoops_AHGGH;
	int						_hoops_PHGGH;
	float					_hoops_HHGGH,
							_hoops_IHGGH;
	int						_hoops_CHGGH;
	_hoops_ACHR				_hoops_SHGGH;
};


struct _hoops_GIGGH {
	_hoops_GIGGH *	next;
	_hoops_ISGI const *	modelling_matrix;
	_hoops_SSGI const *				color;
};



// _hoops_HRPR _hoops_IS _hoops_CRCC _hoops_PGSI/_hoops_PIH _hoops_SGS _hoops_RRP _hoops_IS _hoops_SHH _hoops_CPHR _hoops_GGR _hoops_RH _hoops_RIGGH _hoops_PAR _hoops_GGAS _hoops_AIGGH
struct _hoops_HIHCP : public CMO_Pooled {
	_hoops_HIHCP *			prev;

	_hoops_HIHCP () : prev (null) {}
	virtual bool _hoops_SIHCP (Net_Rendition alter & nr, bool _hoops_PPHPP=false) alter = 0;
};

// _hoops_CRICR, _hoops_HIH _hoops_PIGGH _hoops_GACC _hoops_RRP _hoops_IS _hoops_IGGRA _hoops_GPP _hoops_RH _hoops_SCGR _hoops_CAGH
struct _hoops_HIGGH: public CMO_Pooled {
	_hoops_HIGGH *			prev;

	_hoops_HIGGH () : prev (null) {}
	virtual bool _hoops_PPCRR (Net_Rendition alter & nr, _hoops_CRCP const * _hoops_SRCP, _hoops_HICS const & path) alter = 0;
};


enum Tree_Progress {
	_hoops_IIGGH,
	_hoops_CIGGH,
	_hoops_SIGGH,
	_hoops_GCGGH,
	_hoops_RCGGH,
	_hoops_ACGGH,
	_hoops_PCGGH,
	_hoops_HCGGH,
	_hoops_ICGGH,
	_hoops_CCGGH,
	_hoops_SCGGH,
	_hoops_GSGGH,
	_hoops_ACHCP,
	_hoops_RSGGH
};

enum _hoops_ASGGH {
	_hoops_PSGGH		= 0x0001,
	_hoops_HSGGH	= 0x0002,
	_hoops_ISGGH		= 0x0004,
	_hoops_CSGGH			= 0x0008,
	_hoops_SSGGH			= 0x0010,
	_hoops_GGRGH	= 0x0020,
	_hoops_RGRGH		= 0x0040,
	_hoops_AGRGH		= 0x0080,
	_hoops_PGRGH	= 0x0100,
	_hoops_HGRGH			= 0x0200,
	_hoops_IGRGH				= 0x0400,

	_hoops_CGRGH			= 0x0800
};

struct _hoops_SGRGH;

struct _hoops_AAGSP : public CMO_Pooled {
	public:
		_hoops_AAGSP *			next;

		Net_Rendition				nr;
		_hoops_PHIP const *	_hoops_CSAGR;
		Geometry const *			geometry;
		Geometry const *			start;		// _hoops_RCPGR _hoops_IPS _hoops_IIGR _hoops_SRS '_hoops_CPAP' _hoops_PIRA

		_hoops_ISGI const *	modelling_matrix;
		_hoops_SSGI const *				color;
#ifdef HOOPS_DEBUG_BUILD
		_hoops_ISGI const *	_hoops_GRRGH;
		_hoops_SSGI const *				_hoops_RRRGH;
#endif
		int							index;

		bool						_hoops_ARRGH;
		bool						single;


		~_hoops_AAGSP();
};

struct Tree_Node : public CMO_Pooled {
	public:
		Tree_Node *					next;

		int							stage;		// _hoops_PRRGH
		int							flags;		// _hoops_HRRGH

		Net_Rendition				nr;
		_hoops_CRCP const *				segment;
		_hoops_AHAGR alter *		_hoops_CSC;
		Bounding					_hoops_IRRGH;
		_hoops_APARR				_hoops_ACPGR;
		Activity					_hoops_CPGPR;
		_hoops_PSPGP				_hoops_PCGPR;

		_hoops_HICS				path;
		_hoops_HICS				_hoops_CRRGH;

		Action_Mask					_hoops_RGHGR;
		Action_Mask					_hoops_SRRGH;
		_hoops_PGCIP alter *			_hoops_GARGH;

		Net_Rendition				_hoops_SSGS;
		Subsegment const *			_hoops_SSGPR;
		Geometry const *			geometry;
		Geometry const *			_hoops_RARGH;
		_hoops_SGRGH *			_hoops_AARGH;
		_hoops_RAHGA	*		_hoops_PARGH;


		_hoops_HIHCP *				_hoops_HARGH;
		_hoops_HIHCP *				_hoops_HPAGR;

		bool						single;

		float						_hoops_IARGH;
		float						_hoops_CIHS;

		_hoops_PGCIP *				_hoops_CARGH;
		_hoops_CASS const *				_hoops_SARGH;
		int							_hoops_GPRGH;
		bool						_hoops_RPRGH;


		Tree_Node (Net_Rendition const & n, _hoops_CRCP const * s, _hoops_HICS const & p);
		~Tree_Node ();

		void _hoops_GARSP (_hoops_HIHCP alter * ps) alter {
			stage = _hoops_SIGGH;	// _hoops_HSPP _hoops_IAPR _hoops_CGPR _hoops_SR _hoops_APRGH _hoops_RGR _hoops_GIIS
			ps->prev = _hoops_HARGH;
			_hoops_HARGH = ps;
		}
		void _hoops_GSHCP (_hoops_HIHCP alter * _hoops_PPRGH) alter {
			_hoops_PPRGH->prev = _hoops_HPAGR;
			_hoops_HPAGR = _hoops_PPRGH;
		}

};



struct _hoops_HPRGH {
	_hoops_GSPGR						_hoops_IPRGH;
	_hoops_GSPGR						_hoops_CPRGH;
	_hoops_GSPGR						_hoops_SPRGH;
	_hoops_GSPGR						_hoops_GHRGH;
	_hoops_GSPGR						_hoops_RHRGH;
	_hoops_GSPGR						_hoops_PSPGR;
	long						_hoops_CCCA;
	long						_hoops_SCCA;
	long						_hoops_ICGS;
	long						_hoops_RPAS;
	long						_hoops_HCCA;
	long						_hoops_ICCA;
	long						_hoops_AHRGH;
	long						_hoops_PHRGH;
	long						_hoops_GRCS;
	long						_hoops_ACCA;
	long						_hoops_PCCA;
	long						_hoops_AGCAR;
	long						rasters;
	long						_hoops_HHRGH;
	long						_hoops_IHRGH;
	long						tristrips;
	long						_hoops_CSIAR;
	long						_hoops_SSIAR;
	long						_hoops_GGCAR;
	long						_hoops_GRHAR;
	long						_hoops_SGAGR;
	long						_hoops_HIGC;
	long						_hoops_SISAA;
	long						_hoops_CHRGH;
	long						_hoops_SHRGH;
	long						_hoops_GIRGH;
	long						_hoops_RIRGH;
	long						_hoops_AIRGH;
	long						_hoops_CCHS;
	long						_hoops_PIRGH;
	long						_hoops_HIRGH;
	long						_hoops_IIRGH;
	long						_hoops_CIRGH;
	long						_hoops_CPGIP;
	long						_hoops_SIRGH;
	long						_hoops_GCRGH;

	long						_hoops_PRHPP;
	long						_hoops_GRHPP;
	long						_hoops_RRHPP;
	long						_hoops_SGHPP;
	long						_hoops_ARHPP;

	long						_hoops_RCRGH;
	long						_hoops_ACRGH;
	long						_hoops_PCRGH;
	long						_hoops_RPRH;
	long						_hoops_GSAC;
	long						_hoops_HCRGH;

	long						_hoops_SASIP;
	long						_hoops_HASIP;
	long						_hoops_CASIP;
	long						_hoops_IASIP;
	long						_hoops_ICRGH;
	long						_hoops_CCRGH;
	long						_hoops_SCRGH;
	long						_hoops_GSRGH;
	bool						_hoops_RSRGH;
	bool						_hoops_ASRGH;
	long						_hoops_IGCAR;
	long						_hoops_HGCAR;
	long						_hoops_PSRGH;
	long						_hoops_HSRGH;

	long						_hoops_SHPSA;
	long						_hoops_CIPSA;
	long						_hoops_ISRGH;

	long						_hoops_CSRGH;
	long						_hoops_SSRGH;

	float						_hoops_GGAGH;
	float						_hoops_RGAGH;
};




//#_hoops_PPIP _hoops_AGAGH

#ifdef _hoops_PGAGH
struct _hoops_HGAGH {

	const char * message;
	const char * file;
	int line;

	_hoops_PHIP const *	ref;
	int							_hoops_IGAGH;
	Geometry const *			_hoops_CGAGH;

	_hoops_GSPGR time;
	_hoops_GSPGR _hoops_ASPGR;
};
#endif



struct _hoops_HPHPP {
	_hoops_HPHPP *		next;
	_hoops_HSPPP *	list;
	float					_hoops_SAHPP;
	float					_hoops_GPHPP;
	float					_hoops_GGCRP;
	int						_hoops_RGCRP;
	int						_hoops_AGCRP;
};

struct Display_Context {
	public:

		_hoops_GGAGR const *			_hoops_GHRI;
		_hoops_CRCP const *			_hoops_AAHSR;
		char const *			_hoops_PCRSR;
		int						_hoops_HCRSR;

		void alter *			data;
		void alter *			_hoops_RIHGR;				// _hoops_IH _hoops_SGAGH _hoops_SPSIR

		_hoops_CPGRR					_hoops_RASCA;
		HThreadID				_hoops_GRAGH;

		_hoops_AIGPR *	_hoops_RIGC;
		Memory_Pool *			memory_pool;

		_hoops_APARR			_hoops_ACPGR;
		_hoops_APARR			_hoops_IPCI;
		_hoops_APARR			_hoops_RRAGH;

		_hoops_HIGGH *				_hoops_ARAGH;

		_hoops_AAGSP *			_hoops_ISAGR;
		_hoops_AAGSP *			_hoops_SPA;


		Geometry const *			_hoops_RAI;	/* _hoops_IH _hoops_ASGC */
		_hoops_CRCP const *				_hoops_RRCIP;
		_hoops_HICS				path;

		Tree_Node *					_hoops_AHSI;
		Tree_Node *					_hoops_PRAGH;

#define	_hoops_HRAGH			0x00
#define	_hoops_GGCIP		0x01
#define	_hoops_IHPGR		0x02
#define	_hoops_HHIIP		0x04
#define	_hoops_PSGGR	0x08
#define _hoops_AGSS		0x10
#define	_hoops_GPPIP			32

		int						_hoops_IASS;



#define _hoops_IRAGH				0x00000001
#define _hoops_RPSRR				0x00000002
#define _hoops_GPHHP		0x00000004
#define _hoops_GIHCP			0x00000008
#define _hoops_IGSS				0x00000010
#define _hoops_CHSHP						0x00000020
#define _hoops_HHICP					0x00000040
#define _hoops_RGSGA			0x00000080
#define _hoops_CHSI					0x00000100
#define _hoops_RASS						0x00000200
#define _hoops_IIGC	0x00000400
#define _hoops_CPPHP						0x00000800
#define _hoops_CRAGH		0x00001000
#define _hoops_GIRIP				0x00002000
#define _hoops_SHIIP					0x00004000
#define _hoops_CHIIP		0x00008000
#define _hoops_ICPGR						0x00010000
#define _hoops_IIPIP		0x00020000
#define _hoops_CSHSR			0x00040000
#define _hoops_SRAGH			0x00080000
#define _hoops_GAAGH			0x00100000 //_hoops_ARAS _hoops_RHIR _hoops_RH _hoops_RPGH/_hoops_RSGR _hoops_HCGI _hoops_PRGI _hoops_GGR _hoops_HGAI _hoops_CCH
#define _hoops_RAAGH	0x00200000 // _hoops_AAAGH _hoops_PAAGH _hoops_GCPAR _hoops_CPAP _hoops_SASPR _hoops_GGR _hoops_HCH _hoops_SAGGR _hoops_HAAGH
#define _hoops_AASHP	0x00400000 // _hoops_CPHSR._hoops_IAAGH == 0
#define _hoops_SAISR				0x00800000
#define _hoops_CAAGH				0x01000000
#define _hoops_RCHCP					0x02000000
#define _hoops_IRSI						0x04000000
#define _hoops_SAAGH				0x08000000
#define _hoops_HSAGR				0x10000000

		Integer32					flags;

		Activity					_hoops_CPGPR;
		Activity					_hoops_RIIAP;
		_hoops_PSPGP				_hoops_PCGPR;


		Integer32					_hoops_GPAGH;
		Integer32					_hoops_CGAP;
		Integer32					_hoops_RPAGH;

		bool						_hoops_APAGH;
		bool						_hoops_PPAGH;

		_hoops_CRCP const *				_hoops_HPAGH;
		POINTER_SIZED_INT			_hoops_IPAGH;
		_hoops_CRCP const *				_hoops_CPAGH;
		POINTER_SIZED_INT			_hoops_SPAGH;
		_hoops_CRCP const *				_hoops_GHAGH;

		Int_Rectangle				_hoops_RHPGA;
		Int_Rectangle				_hoops_RCGA;	// _hoops_RAS _hoops_RHAGH

		_hoops_ACCCP alter *	_hoops_APHHP;
		Segment_Info const *		_hoops_CHICP;


		int							_hoops_AHAGH;
		float						_hoops_PHAGH;
		_hoops_PGCIP *				_hoops_GPSS[_hoops_GPPIP];

		_hoops_PGCIP *				_hoops_RPSS[_hoops_GPPIP];
		unsigned int				_hoops_GSGC;
		unsigned int				_hoops_SCGC;
		Geometry const *			_hoops_HHAGH; /* _hoops_IHAGH _hoops_CRS -- _hoops_AA _hoops_HAR _hoops_AAGGR */

		int							_hoops_SASS[_hoops_GPPIP];
		_hoops_CASS const *				_hoops_HASS[_hoops_GPPIP];
		_hoops_CHAGH *			_hoops_SRSIP[_hoops_GPPIP];

		unsigned int 				_hoops_SHAGH;
		Geometry const *			_hoops_GIAGH; /* _hoops_IHAGH _hoops_CRS -- _hoops_AA _hoops_HAR _hoops_AAGGR */

		_hoops_CASS const *				_hoops_RIAGH;
		_hoops_CPSIP alter *		_hoops_SPSIP;
		_hoops_SISIP *		_hoops_AHGCP;


		_hoops_PRSSP			options;

	private:
		mutable	_hoops_GARRR			_hoops_AIAGH;
		int							_hoops_PIAGH;

	public:
		int		_hoops_GCHHP() const { return ++_hoops_AIAGH; }


#define	_hoops_AASIP					0
#define	_hoops_HIAGH						1
#define	_hoops_IIAGH				2

#define	_hoops_HRIIP				2
#define	_hoops_GICI		3
#define	_hoops_RICI		4
#define	_hoops_CRIIP		5
#define	_hoops_GAIIP	6

		INLINE int	_hoops_SHCI() const { return _hoops_PIAGH; }

		INLINE void	_hoops_RASIP(int _hoops_CIAGH) {
			_hoops_PIAGH = _hoops_CIAGH;
			switch(_hoops_PIAGH) {

				case _hoops_HIAGH:
					flags = _hoops_IRSI|(~_hoops_RCHCP&~_hoops_SAAGH&flags);
					break;
				case _hoops_AASIP:
					flags = _hoops_RCHCP|(~_hoops_IRSI&~_hoops_SAAGH&flags);
					break;
				case _hoops_IIAGH:
				/*_hoops_AGIR _hoops_SIAGH:*/
					flags = _hoops_SAAGH|(~_hoops_RCHCP&~_hoops_IRSI&flags);
					break;
				case _hoops_GICI:
				case _hoops_RICI:
				case _hoops_CRIIP:
				case _hoops_GAIIP:
					flags &= ~(_hoops_SAAGH|_hoops_RCHCP|_hoops_IRSI);
					break;
			}
		}

		_hoops_HCSIR *		_hoops_CISCP;

		// _hoops_HISAR _hoops_GCAGH _hoops_APSAR
		bool					_hoops_AGGIP;
		bool					_hoops_RCAGH;
		bool					_hoops_ACAGH;
		bool					_hoops_PCAGH;
		bool					_hoops_HAHHP;
		bool					_hoops_HCAGH;
		bool					_hoops_ICAGH;
		bool					_hoops_HRIC;
		bool					_hoops_CCAGH;
		bool					_hoops_SCAGH;
		bool					_hoops_CHHCP;
		bool					_hoops_GSAGH;
		bool					_hoops_RSAGH;
		bool					_hoops_CPIGA;
		bool					_hoops_ASAGH;
		bool					_hoops_PSAGH;
		bool					_hoops_HSAGH;
		bool					_hoops_ISAGH;
		bool					_hoops_CSAGH;
		bool					_hoops_RAIGA;
		bool					_hoops_GRAGR;

		int						_hoops_SSAGH,
								_hoops_GGPGH,
								_hoops_RGPGH,
								_hoops_RIHHP,
								_hoops_GCPRP,
								_hoops_RHGCR;

		_hoops_SGGCR					_hoops_AGPGH,
								_hoops_HHGCR,
								_hoops_AHGCR;

		/*
		 * _hoops_PGPGH _hoops_HRGR _hoops_IGI _hoops_HCRSP _hoops_GAR _hoops_RH "_hoops_HPHR" _hoops_PHI
		 * _hoops_IIGR _hoops_HGPGH _hoops_IGPGH _hoops_IIGR _hoops_PSHA.	 _hoops_HHIGR'_hoops_GRI _hoops_CGPGH _hoops_HPP
		 * _hoops_RH "_hoops_HAIR _hoops_SGPGH" _hoops_RHPP _hoops_HCSP _hoops_PPR _hoops_RH
		 * _hoops_CPHSR _hoops_PIRA "_hoops_CGGGH _hoops_HAIR _hoops_RAAA".
		 */
		int						_hoops_GRPGH;

		_hoops_SHHHP alter *	_hoops_RRPGH;
		_hoops_SHHHP alter *	_hoops_ARPGH;

		_hoops_HIIHP alter *	_hoops_PRPGH;
		_hoops_HIIHP alter *	_hoops_HRPGH;

		Driver_Color const *	_hoops_CSIR; /* 1 _hoops_IH _hoops_GRR - _hoops_AIHSR _hoops_RGAR */
		RGB const *				_hoops_CHHIP;	/* _hoops_PPR _hoops_RH _hoops_PIS _hoops_AIIC _hoops_HGGPA */
		int						_hoops_IRPGH;
		Driver_Color			_hoops_SPHHP,
								_hoops_GHHHP;

		struct {
			/*		_hoops_HAIR _hoops_SIHC */
			int						_hoops_APASR;
			Integer32				_hoops_AAPSR;
			int						_hoops_GCPRP;

			/*		_hoops_IGIR _hoops_SIHC */
			Int_XY					_hoops_PRPSR;
			Int_XY					_hoops_ARISR;
			_hoops_PACIR		extent;					/* _hoops_CGGPR/_hoops_AHPA*/

			/* _hoops_RH _hoops_ACSP _hoops_GCIS _hoops_RH _hoops_AGI _hoops_IIGR _hoops_RH '_hoops_CPHSR _hoops_IGIR' _hoops_CRPGH */
			XY						_hoops_HAP;				/* _hoops_ASPA/_hoops_SRPGH */
			float					_hoops_AGRS;	/* _hoops_APPS/_hoops_SRGSA / _hoops_IGAA/_hoops_SRGSA */

			/* '_hoops_IGIR' _hoops_GACC _hoops_CRRPR _hoops_RH _hoops_GAPGH, _hoops_AHI */
			XY						size;					/* _hoops_GGR _hoops_SAPSR */

			POINTER_SIZED_INT		_hoops_RAPGH;		/* _hoops_RPPS _hoops_AAPGH _hoops_RGAR */
			POINTER_SIZED_INT		_hoops_PAPGH;		/* _hoops_RPPS _hoops_AAPGH _hoops_RGAR */

			Int_Rectangle			border;

			long					_hoops_HAPGH;	/* _hoops_RPPS _hoops_AAPGH _hoops_RGAR */
		}						current;

		struct {
			// _hoops_HHH _hoops_CPHSR _hoops_GGR _hoops_SCIA _hoops_PAPA _hoops_SGI
#define 	_hoops_IAPGH			0x00000001
#define 	_hoops_CAPGH						0x00000002
#define 	_hoops_RSHSR						0x00000004
#define 	_hoops_PSHSR						0x00000008
#define 	_hoops_HSHSR					0x00000010
#define 	_hoops_SAPGH			0x00000020
#define 	_hoops_SGICP				0x00000040
#define 	_hoops_GPPGH				0x00000080
#define 	_hoops_RPPGH					0x00000100
#define 	_hoops_APPGH				0x00000200
#define 	_hoops_GIHSR				0x00000400
#define 	_hoops_GGISR				0x00000800
#define 	_hoops_PPPGH			0x00001000
#define 	_hoops_ISHSR					0x00002000
#define 	_hoops_HPPGH				0x00004000
#define 	_hoops_PAGIP		0x00008000
#define 	_hoops_ISRIP				0x00010000
#define 	_hoops_CCHSR					0x00020000
#define 	_hoops_IPPGH						0x00040000
#define 	_hoops_IPPHP					0x00080000
#define 	_hoops_CPPGH						0x00100000
#define 	_hoops_SPPGH				0x00200000
#define 	_hoops_ASSHP				0x00400000
#define 	_hoops_PSSHP				0x00800000
#define 	_hoops_GHPGH			0x01000000
#define 	_hoops_RHPGH				0x02000000
#define		_hoops_ISSHP						0x04000000 /* _hoops_SSCP _hoops_GSIA _hoops_AHPGH _hoops_IH _hoops_GHCP _hoops_IISI */
#define		_hoops_PHPGH						0x08000000 

			Integer32					flags;

			/*		_hoops_HAIR _hoops_SIHC */
			int						_hoops_APASR;

			Integer32				_hoops_AAPSR;
			Integer32				_hoops_HHPGH;

			int						_hoops_GCPRP;

			/*		_hoops_IGIR _hoops_SIHC */
			Int_XY					_hoops_PRPSR;
			Int_XY					_hoops_ARISR;

			XY						size;					/* _hoops_GGR _hoops_SAPSR */
			_hoops_PACIR		extent;					/* _hoops_CGGPR/_hoops_AHPA*/

			/* _hoops_RRI _hoops_HAIR _hoops_SIHC */

#define		_hoops_SIHSR		0		/* 1-_hoops_RCAP (2/4/8-_hoops_IGRH) */
#define		_hoops_HIHSR		1		/* 3-_hoops_RCAP (24-_hoops_IGRH) */
#define		_hoops_RIIHP		2		/* _hoops_CPHP _hoops_SHS */
			int						_hoops_PIHSR;

			/* _hoops_IHPGH _hoops_HRGR _hoops_IGI _hoops_GAR _hoops_RH _hoops_CSRA _hoops_SIPIR _hoops_IH _hoops_CHPGH _hoops_PPR
			 * _hoops_SHPGH _hoops_GCSS _hoops_GIPGH _hoops_HSH, _hoops_PPR _hoops_GAR _hoops_RH _hoops_CSRA _hoops_SIPIR _hoops_IH
			 * _hoops_IIHSR _hoops_HCPH _hoops_IS "_hoops_RIPGH". _hoops_HHIGR _hoops_HRGR _hoops_PSHRR _hoops_IRS _hoops_RIIR
			 * _hoops_IIGR 2. _hoops_HSRR _hoops_CHPGH _hoops_PSHA, _hoops_SCH _hoops_PIHA _hoops_SHH <= 256, _hoops_CR _hoops_SGS'_hoops_GRI _hoops_HCR _hoops_SGS
			 * _hoops_GRS _hoops_SIHRR _hoops_GGR _hoops_AIPGH._hoops_PCCIR/_hoops_ISHI/_hoops_RCSR.
			 */
			Integer32				_hoops_PCHSR;

			/* _hoops_RRI _hoops_IGIR _hoops_SIHC */
			int						_hoops_PIPGH;

			float					_hoops_IHHSR; /* _hoops_SGCR _hoops_IIGR "1.0" _hoops_III;
															_hoops_CGH _hoops_SHH _hoops_HIPGH _hoops_PHI */
#define 	_hoops_SHHSR		0
#define 	_hoops_ACPGA		1
#define 	_hoops_RCPGA		2
			int						_hoops_CHHSR;

#define 	QMoves_NONE				0
#define 	QMoves_XOR				1
#define 	QMoves_Real_Overlay		2
#define 	QMoves_Spriting			3
#define 	QMoves_Accumulation		4
			int						_hoops_IIPGH[_hoops_HAHRP+1];


			_hoops_SGGCR					_hoops_CIPGH;
			int						_hoops_SIPGH;


			int						_hoops_ASHSR;
			char const *			driver_type;
			char const *			_hoops_SCHSR;		 /* _hoops_GCPGH _hoops_CRSRR */
			char const *			_hoops_ICHSR;
			char const *			_hoops_RCPGH;


			int						_hoops_HASHP;
			float					_hoops_PASHP; /* _hoops_GGSRA _hoops_HII _hoops_IAAGH*/

			int						_hoops_HGCC;
			int						_hoops_ACPGH;

			int						_hoops_PCPGH;
			int						_hoops_HCPGH; //_hoops_RPAC _hoops_APAC _hoops_PAH'_hoops_RA _hoops_RGHH _hoops_RRI _hoops_HSAR _hoops_SPR


#			if _hoops_PHRSP > 256
				short				_hoops_HHHHP[_hoops_PHRSP];
#			else
				unsigned char		_hoops_HHHHP[_hoops_PHRSP];
#			endif

			/* _hoops_CSRA _hoops_SIPIR _hoops_IH _hoops_IIPH _hoops_PGRC */
			float					_hoops_ICPGH;

			/* _hoops_CSRA _hoops_SIPIR _hoops_IH _hoops_ISCRA _hoops_PGRC */
			float					_hoops_CCPGH;

			int						_hoops_AHAGH;

			/*_hoops_HRARR _hoops_SCPGH */

			/* _hoops_PCPA _hoops_SR _hoops_PPRIP _hoops_GH */
			_hoops_HCRPR					_hoops_GSPGH;
			_hoops_HCRPR					_hoops_RSPGH;

			/* _hoops_GRAA-_hoops_GSSSP _hoops_CGRPR _hoops_HHRI _hoops_HPP _hoops_RH _hoops_RHPP _hoops_PIH */
			_hoops_ARARR *			_hoops_PRARR;
		}						_hoops_PGCC;



		unsigned short const *	_hoops_GRPH[TOTAL_BIT_PATTERNS];
		int						_hoops_ASPGH; /* _hoops_PGAP _hoops_CHR _hoops_PGGGH? 0/8/16 */

		_hoops_SCCIP const *	_hoops_GCHCP;
		_hoops_SCCIP const *	_hoops_RSCIP;


		_hoops_PRGIP			_hoops_PSPGH;
		Activity				_hoops_HSPGH;

		_hoops_RGHPP		_hoops_HRHPP[_hoops_CHSSP];

		_hoops_RGHPP		_hoops_GPSIP;

		_hoops_PGHPP *	_hoops_AGHPP;
		_hoops_IGHPP *	_hoops_HGHPP;

		_hoops_HPHPP *		_hoops_IAHPP;

		_hoops_IIPSA *			_hoops_ISPGH;
		_hoops_IIPSA *			_hoops_CSPGH;

		Bounding				global_bounds;

		_hoops_ARPA *					_hoops_PGPCP;
		int						_hoops_PAHCP;
		_hoops_ARPA *					_hoops_AIACP;
		int						_hoops_PIACP;
		int *					_hoops_CGHAR;
		int						_hoops_ICACP;

typedef char			_hoops_CSSHA;
#define _hoops_AARCA		(_hoops_CSSHA)0x1
#define _hoops_HARCA	(_hoops_CSSHA)0x2
#define _hoops_PARCA		(_hoops_CSSHA)0x4
#define _hoops_CCICP		(_hoops_CSSHA)0x8

		_hoops_CSSHA alter *_hoops_ACICP;
		int						_hoops_RCICP;

		RGB *					_hoops_SSPGH;
		int						_hoops_GGHGH;
		RGB *					_hoops_RGHGH;
		int						_hoops_AGHGH;


		_hoops_PGHGH alter *_hoops_HGHGH;		/* _hoops_RIH-_hoops_RHIR */

		_hoops_GHGGH alter *	_hoops_IGHGH;		/* _hoops_IH _hoops_GHSHA */

		Net_Rendition			_hoops_SHCIP;

		/* _hoops_CGHGH _hoops_SCPGH */
		_hoops_RCSSP const *		_hoops_SGHGH;
		_hoops_SHSSP const *		_hoops_GRHGH[_hoops_HHRSP];
		Font_Instance const *	_hoops_RRHGH[_hoops_ARHGH+1];

		unsigned int			_hoops_PRHGH[_hoops_GCSSP];
		Font_Instance const *	_hoops_HRHGH[_hoops_GCSSP];
		_hoops_AAPIR *				_hoops_IRHGH;

		_hoops_SGSGP alter *			_hoops_SHSHP;

		_hoops_HSIIP alter *			_hoops_IHIIP[2];
		_hoops_HSIIP alter * alter	*	_hoops_RIHCP;
		_hoops_HSIIP alter *			_hoops_CHPGR;
		_hoops_HSIIP alter * alter	*	_hoops_IHHCP;
		_hoops_HSIIP alter *			_hoops_CRHGH;

		/* _hoops_HCHCP _hoops_HRGR _hoops_RH _hoops_SRHGH _hoops_GAPA _hoops_PCPA _hoops_RH _hoops_RHPP _hoops_GAHGH _hoops_PPR
		 * _hoops_RH _hoops_IPSP'_hoops_GRI _hoops_RHPP _hoops_AAP _hoops_PSGC */
		int							_hoops_SHPGR;

		int							_hoops_ARAIP;

		int							_hoops_RAHGH;
		int *						_hoops_GGGCA;


		float						(*_hoops_AAHGH)[4];

		_hoops_RAHGA *		_hoops_CRIGA;
		_hoops_CRCP const *				_hoops_RHIGA;
		Driver_Color				_hoops_PAIGA;
		Driver_Color				_hoops_HAIGA;


		_hoops_GGACP *			_hoops_GPACP;

		struct {
			Image *						image;
			_hoops_GGAGR *						_hoops_GHRI;
			_hoops_PSISP			start_device;
			_hoops_CSISP		get_current_info;
			int							_hoops_PAHGH;
			_hoops_CPSS *				current;
		}							_hoops_GHSS;

		struct {
			_hoops_GSAR *				current;
		}							_hoops_HRR;


		struct {
			_hoops_SGGCR						color, _hoops_PSHCP;		/* _hoops_RPPS _hoops_HAIR _hoops_PPR _hoops_AGRP _hoops_IS _hoops_CGARA */
		}							_hoops_ASHCP;

		_hoops_SASC *				_hoops_HAHGH;
		_hoops_RCR *					_hoops_IAHGH;

		_hoops_HPRGH *					_hoops_IGGI;
		_hoops_HPRGH *					_hoops_CAHGH;

		_hoops_CRCP	const *				_hoops_RGCHP;
		void const *				_hoops_AIACR;
		DC_Polydot_Batch *			_hoops_GASIP;


		int							_hoops_SSGC;

		int							_hoops_HGCAR;
		int							_hoops_PGCAR;


		_hoops_PGISP *			_hoops_PPSIP;

		_hoops_HRPA *				_hoops_SAHGH;


		Integer32				_hoops_GPHGH;
		void alter *			_hoops_RPHGH;

#ifdef _hoops_PGAGH
#define _hoops_APHGH 1024*8
		_hoops_HGAGH				_hoops_PPHGH[_hoops_APHGH];
		int							_hoops_HPHGH;
#endif

	public:
		Tree_Node *
			Push_Tree (Net_Rendition const & n, _hoops_CRCP const * s, _hoops_HICS const & p, bool _hoops_IPHGH=false) alter {
				Tree_Node *	node = POOL_NEW(n->_hoops_SRA->memory_pool,Tree_Node)(n, s, p);

				if (_hoops_IPHGH) {
					node->next = _hoops_PRAGH;
					_hoops_PRAGH = node;
				}
				else {
					node->next = _hoops_AHSI;
					_hoops_AHSI = node;
				}

				return node;
			}
		void
			Pop_Tree () alter {
				Tree_Node *		node = _hoops_AHSI;

				_hoops_AHSI = node->next;
				_hoops_SSAGR(_hoops_AHSI);

				delete node;
				if (_hoops_AHSI != null)
					_hoops_IPCI = _hoops_AHSI->_hoops_ACPGR;
				else
					_hoops_IPCI = _hoops_ACPGR;
			}
		bool
			_hoops_CPHGH() alter {
				Tree_Node *		node;

				if (_hoops_PRAGH == null)
					return false;

				while ((node = _hoops_PRAGH) != null) {
					_hoops_PRAGH = node->next;
					node->next = _hoops_AHSI;
					_hoops_AHSI = node;
				}

				return true;
			}

		_hoops_APARR alter &
			Push_Actions (char const * id, Net_Rendition const & nr) alter {
				_hoops_APARR	_hoops_RRCI = _hoops_IPCI.Copy();

				_hoops_RRCI->prev = _hoops_IPCI;
				_hoops_IPCI = _hoops_RRCI;
				_hoops_RRCI->id = id;
				_hoops_RRCI->mode = nr->current;
				if (_hoops_AHSI != null)
					_hoops_AHSI->_hoops_ACPGR = _hoops_RRCI;

				return _hoops_IPCI;
			}
		_hoops_APARR alter &
			Pop_Actions (char const * id) alter {
				_hoops_APARR	_hoops_RRCI = _hoops_IPCI;
				UNREFERENCED(id);
				if (_hoops_RRCI->prev == null
#ifdef HOOPS_DEBUG_BUILD
					|| id != null && !_hoops_AGGR(id, _hoops_RRCI->id)
#endif
					)
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									   "Push/Pop _Actions mismatch");
				else
					_hoops_IPCI = _hoops_RRCI->prev;
				if (_hoops_AHSI != null)
					_hoops_AHSI->_hoops_ACPGR = _hoops_IPCI;

				return _hoops_IPCI;
			}

		_hoops_APARR alter &
			Use_Previous_Actions () alter {
				_hoops_APARR	_hoops_RRCI = _hoops_IPCI;

				if (_hoops_RRCI->prev == null)
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									   "Push/Pop _Actions mismatch");
				else {
					_hoops_IPCI = _hoops_RRCI->prev;
					_hoops_RRCI->prev = _hoops_RRAGH;
					_hoops_RRAGH = _hoops_RRCI;
				}
				if (_hoops_AHSI != null)
					_hoops_AHSI->_hoops_ACPGR = _hoops_IPCI;

				return _hoops_IPCI;
			}

		_hoops_APARR alter &
			Resume_Current_Actions () alter {
				_hoops_APARR	_hoops_RRCI = _hoops_RRAGH;

				if (_hoops_RRCI == null)
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									   "Previous/Resume _Actions mismatch");
				else {
					_hoops_RRAGH = _hoops_RRCI->prev;
					_hoops_RRCI->prev = _hoops_IPCI;
					_hoops_IPCI = _hoops_RRCI;
				}
				if (_hoops_AHSI != null)
					_hoops_AHSI->_hoops_ACPGR = _hoops_IPCI;

				return _hoops_IPCI;
			}


		void
			Add_Filter (_hoops_HIGGH alter * f) alter {
				f->prev = _hoops_ARAGH;
				_hoops_ARAGH = f;
			}
		void
			Remove_Filter () alter {
				_hoops_HIGGH alter *		f = _hoops_ARAGH;

				if (f == null)
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									   "Remove_Filter mismatch");
				else {
					_hoops_ARAGH = f->prev;
					delete f;
				}
			}

};

#define	_hoops_HGCGA(_hoops_SPHGH, _id_, _hoops_CCCSP)			((Display_Context alter *)_hoops_SPHGH)->Push_Actions (_id_, _hoops_CCCSP)
#define	_hoops_HGSGA(_hoops_SPHGH, _id_)					((Display_Context alter *)_hoops_SPHGH)->Pop_Actions (_id_)
#define	_hoops_IGRS(_hoops_SPHGH)				((Display_Context alter *)_hoops_SPHGH)->Use_Previous_Actions ()
#define	_hoops_SGRS(_hoops_SPHGH)			((Display_Context alter *)_hoops_SPHGH)->Resume_Current_Actions ()


#define _hoops_GPRH(x) ((Display_Context alter*)nr->_hoops_SRA)->_hoops_IGGI->x
#define _hoops_RCCA(x) ((Display_Context alter*)dc)->_hoops_IGGI->x


class _hoops_AGSGA {
private:
	Display_Context *		_hoops_SRA;
	Integer32				_hoops_GHHGH;
	
public:
	INLINE _hoops_AGSGA (Display_Context * dc) :
		_hoops_SRA (dc),
		_hoops_GHHGH (dc->flags & _hoops_RPSRR) {
		_hoops_SRA->flags |= _hoops_RPSRR;
	}
	INLINE ~_hoops_AGSGA () { restore(); }

	INLINE void	restore () alter {
		_hoops_SRA->flags &= ~_hoops_RPSRR;
		_hoops_SRA->flags |= _hoops_GHHGH;
	}

private:
	_hoops_AGSGA ();
	_hoops_AGSGA (_hoops_AGSGA const &);
	_hoops_AGSGA & operator= (_hoops_AGSGA const &);
};


INLINE Tree_Node::Tree_Node (Net_Rendition const & n, _hoops_CRCP const * s, _hoops_HICS const & p)
	: nr (n)
	, segment (s)
	, path (p)
	, _hoops_CRRGH (p) {
	Display_Context const *		dc = nr->_hoops_SRA;

	_hoops_CPGPR = dc->_hoops_CPGPR;
	_hoops_PCGPR = dc->_hoops_PCGPR;
	_hoops_ACPGR = dc->_hoops_IPCI;

	_hoops_RPRGH = BIT(dc->flags, _hoops_CRAGH);
}


template <typename T>
Rendition_Pointer<T>	Rendition_Pointer<T>::Create (Display_Context const * dc) {
	Rendition_Pointer<T>		temp;
	typedef T _hoops_RHHGH;
	temp._hoops_RPPGP = POOL_NEW(dc->memory_pool, _hoops_RHHGH)(dc);
	temp->retain();
	return temp;
}

template <typename T>
INLINE	Rendition_Pointer<T> & Rendition_Pointer<T>::Modify (int offset) alter {
	if (CP::_hoops_RPPGP->shared()) {
		typedef T _hoops_RHHGH;
		T *		temp = POOL_NEW(CP::_hoops_RPPGP->memory_pool, _hoops_RHHGH)(*CP::_hoops_RPPGP);

		if (offset != 0)
			temp->_hoops_CPA = CP::_hoops_RPPGP->_hoops_CPA + offset;

		CP::_hoops_RPPGP->release();	// _hoops_AASA _hoops_SSPP _hoops_RIIA _hoops_IIGR _hoops_GRP _hoops_AHHGH::_hoops_PHHGH() _hoops_GAR _hoops_SR _hoops_ACPA _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_IRAP
		CP::_hoops_RPPGP = temp;
		CP::_hoops_RPPGP->retain();		// _hoops_HHHGH
	}
	else
		Renew();
	return *this;
}
template <typename T>
INLINE	Rendition_Pointer<T> & Rendition_Pointer<T>::Renew () alter {
	CP::_hoops_RPPGP->_hoops_CPA = CP::_hoops_RPPGP->_hoops_SRA->_hoops_GCHHP();
	return *this;
}




struct _hoops_SCCIP {
	_hoops_SCCIP alter *	next;
	_hoops_CRCP const *			segment;
};


struct _hoops_HSIIP {
	_hoops_HSIIP alter *	next;
	Net_Rendition			nr;
	Geometry const *		geometry;
	_hoops_CRCP const *			segment;
	_hoops_HICS			path;
	Tristrip alter *		_hoops_ISIIP;
	Action_Mask				mask;
	bool					single;
};


#define _hoops_IHHGH			0.20f /* _hoops_IIGR _hoops_GSPR _hoops_IGAA: _hoops_IRS _hoops_AHGC */
#define _hoops_CHHGH			0.44f /* _hoops_IIGR _hoops_GSPR _hoops_APPS: _hoops_IRS _hoops_AHGC */
#define _hoops_SHHGH			0.40f /* _hoops_IIGR _hoops_GSPR _hoops_APPS: _hoops_IRS _hoops_AHGC */




#ifdef HOOPS_WINDOWS_HDI_DRIVER
#	define _hoops_HSCSR(_hoops_RSCSR) \
		extern "C" __declspec(dllexport) bool HD_Driver (\
			_hoops_AIGPR *	_hoops_RIGC, \
			_hoops_GGAGR alter *			_hoops_GHRI, \
			int						request) { \
			return HD_Connect_Standard_Driver (_hoops_RIGC, _hoops_GHRI, request, _hoops_RSCSR); \
		}
#else
/*_hoops_HGI _hoops_GIHGH _hoops_GHPHR _hoops_HRGR _hoops_IS _hoops_GSRS _hoops_IRS _hoops_PAGGR _hoops_IS _hoops_RH _hoops_RIGR _hoops_RSCRR*/
/*_hoops_CCA _hoops_GGSR _hoops_RIHGH _hoops_IRS _hoops_AIHGH _hoops_ASRHR _hoops_GGR _hoops_RH _hoops_HPPP*/
#	define _hoops_HSCSR(_hoops_RSCSR) \
		local	void _hoops_PIHGH(void) { \
						_hoops_APARR _hoops_RRCI; _hoops_RSCSR(_hoops_RRCI); _hoops_PIHGH();}
#endif


#ifndef DISABLE_MUTEX
# define _hoops_PIAPR(flag) do {		\
		_hoops_AIGPR		*_hoops_RSPGP;	\
		bool	_hoops_HIHGH = (flag);			\
		HI_What_Time();	\
		_hoops_RSPGP = HOOPS_WORLD->_hoops_PGSCA;			\
		do {_hoops_RSPGP->_hoops_IIHGH = _hoops_HIHGH;	\
		} while ((_hoops_RSPGP = _hoops_RSPGP->next) != null);\
	} while (0)
#else
# define _hoops_PIAPR(flag) do { \
		bool	_hoops_HIHGH = (flag);	\
		HOOPS_WORLD->_hoops_PGSCA->_hoops_IIHGH = _hoops_HIHGH; \
		HI_What_Time(); \
	} while (0)
#endif


#ifdef _hoops_PGAGH
#define _hoops_APSRR(dc, message, file, line) HD_Update_Log(dc, message, file, line)
#else
#define _hoops_APSRR(dc, message, file, line) UNREFERENCED(dc)
#endif


#define _hoops_CIHGH(_hoops_RSPGP)				\
	(_hoops_RSPGP->_hoops_IIHGH || \
		HOOPS_WORLD->_hoops_SIHGH == 0 && _hoops_RSPGP->_hoops_HCPGR && \
             (_hoops_RSPGP->_hoops_HCPGR =	(_hoops_RSPGP->_hoops_HCPGR & 0x01FF) + 1) == 1)

#define _hoops_GCHGH(_hoops_CCCSP,_hoops_SPHGH) \
	(_hoops_SPHGH->options._hoops_CPSSP? \
		(_hoops_SPHGH->options._hoops_CPSSP(_hoops_CCCSP, _hoops_SPHGH->options._hoops_HSHRP), \
			BIT((_hoops_SPHGH)->flags, _hoops_IRAGH)): \
				HD_Exit_Update ((Display_Context alter*)_hoops_SPHGH))

#define _hoops_RCHGH(_hoops_RSPGP, _hoops_CCCSP,_hoops_SPHGH) \
	(BIT((_hoops_SPHGH)->flags, _hoops_RPSRR)?0: \
		(BIT((_hoops_SPHGH)->flags, _hoops_IRAGH)?1: \
			(_hoops_RSPGP->_hoops_HCPGR != 0 && *HOOPS_WORLD->time_stamp >= _hoops_RSPGP->_hoops_ACHGH)? \
				(HD_Interrupt_Update(_hoops_SPHGH, false, false), BIT((_hoops_SPHGH)->flags, _hoops_IRAGH)): \
				(_hoops_CIHGH((_hoops_RSPGP)) && _hoops_GCHGH (_hoops_CCCSP, _hoops_SPHGH))))


#define _hoops_GGPGR(_hoops_CCCSP) \
	(_hoops_RCHGH((_hoops_CCCSP)->_hoops_SRA->_hoops_RIGC, (_hoops_CCCSP), (_hoops_CCCSP)->_hoops_SRA)? \
		_hoops_APSRR((_hoops_CCCSP)->_hoops_SRA, "update_interrupted",__FILE__, __LINE__), true :false)

#define _hoops_IACI(dc) \
	(!BIT((dc)->flags, _hoops_RPSRR)&&BIT((dc)->flags, _hoops_IRAGH))

/* _hoops_PCHGH _hoops_CIGR */

#define _hoops_GACIP(nr, _hoops_APRPR) \
			(*(nr)->_hoops_SRA->_hoops_IPCI->_hoops_APRPR)
#define _hoops_SHICP(nr, _hoops_APRPR) \
			(*(nr)->_hoops_RSGC->action._hoops_APRPR)



#define _hoops_HCHGH(nr, _hoops_ICHGH) do { \
	Display_Context *_hoops_CCHGH = (Display_Context alter *)(nr)->_hoops_SRA; \
	_hoops_CCHGH->_hoops_AIACR = (nr)->_hoops_RSGC->_hoops_AIACR[(_hoops_ICHGH)]; \
	_hoops_CCHGH->_hoops_RGCHP = (nr)->_hoops_RSGC->_hoops_RGCHP[(_hoops_ICHGH)]; \
} while (0)

#define _hoops_SCHGH(nr) do { \
	Display_Context *_hoops_CCHGH = (Display_Context alter *)(nr)->_hoops_SRA; \
	_hoops_CCHGH->_hoops_AIACR = 0; \
	_hoops_CCHGH->_hoops_RGCHP = 0; \
	_hoops_CCHGH->_hoops_RIGC->_hoops_GSHGH = false; \
} while (0)

#define _hoops_RSHGH(nr) \
	do if ((nr)->_hoops_RSGC->action._hoops_GSCHP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_RRACR); \
		_hoops_SHICP (nr, _hoops_GSCHP) (&nr); \
		_hoops_SCHGH(nr); \
} while (0)

#define _hoops_ASHGH(nr) \
	do if ((nr)->_hoops_RSGC->action._hoops_ASCHP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_ARACR); \
		_hoops_SHICP (nr, _hoops_ASCHP) (&nr); \
		_hoops_SCHGH(nr); \
} while (0)


#define _hoops_PSHGH(nr, key) \
	do if ((nr)->_hoops_RSGC->action._hoops_SGSHP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_APACR); \
		_hoops_SHICP (nr, _hoops_SGSHP) (&nr, key); \
		_hoops_SCHGH(nr); \
} while (0)

#define _hoops_GASRR(nr, driver_type, geom_type, geom_bits, thing) \
	do if ((nr)->_hoops_RSGC->action.set_shader != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PPACR); \
		_hoops_SHICP (nr, set_shader) (&nr, driver_type, geom_type, geom_bits, thing); \
		_hoops_SCHGH(nr); \
} while (0)

#define _hoops_RAPCP(nr, count, points) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_polytriangle != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_RPRCR); \
		_hoops_SHICP (nr, draw_dc_polytriangle)(&nr, count, points); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_triangle != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_IARCR); \
		HD_Unwrap_Polytriangle (nr, count, points); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_polytriangle)(nr, count, points); \
} while (0)

#define _hoops_GAPCP(nr, count, points, color, single) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_colorized_polytriangle != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_APRCR); \
		_hoops_SHICP (nr, draw_dc_colorized_polytriangle)(&nr, count, points, color, single); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_colorized_triangle != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_CARCR); \
		HD_Unwrap_Colorized_Polytriangle (nr, count, points, color, single); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_colorized_polytriangle)(nr, count, points, color, single); \
} while (0)

#define _hoops_SRPCP(nr, count, points, colors) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_gouraud_polytriangle != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PPRCR); \
		_hoops_SHICP (nr, draw_dc_gouraud_polytriangle)(&nr, count, points, colors); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_gouraud_triangle != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_SARCR); \
		HD_Unwrap_Gouraud_Polytriangle (nr, count, points, colors); \
		_hoops_SCHGH(nr); \
	} else \
				_hoops_GACIP (nr, draw_dc_gouraud_polytriangle)(nr, count, points, colors); \
} while (0)

#define _hoops_CRPCP(nr, count, points, colors, planes) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_phong_polytriangle != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_HPRCR); \
		_hoops_SHICP (nr, draw_dc_phong_polytriangle)(&nr, count, points, colors, planes); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_reshaded_triangle != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_GPRCR); \
		HD_Unwrap_Reshaded_Polytriangle (nr, count, points, colors, planes, 0, 0, 0); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_phong_polytriangle)(nr, count, points, colors, planes); \
} while (0)

#define _hoops_HSHGH(nr, count, points, colors, planes, params, param_width, param_flags) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_textured_polytriangle != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_IPRCR); \
		_hoops_SHICP (nr, draw_dc_textured_polytriangle)(&nr, count, points, colors, planes, params, param_width, param_flags); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_reshaded_triangle != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_GPRCR); \
		HD_Unwrap_Reshaded_Polytriangle (nr, count, points, colors, planes, params, param_width, param_flags); \
		_hoops_SCHGH(nr); \
	} else \
				_hoops_GACIP (nr, draw_dc_textured_polytriangle)(nr, count, points, colors, planes, params, param_width, param_flags); \
} while (0)

#define _hoops_SRPIP(nr, count, points) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_polyline != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_HRRCR); \
		_hoops_SHICP (nr, draw_dc_polyline)(&nr, count, points); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_line != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_RARCR); \
		HD_Unwrap_Polyline (nr, count, points); \
		_hoops_SCHGH(nr); \
	} else \
				_hoops_GACIP (nr, draw_dc_polyline)(nr, count, points); \
} while (0)

#define _hoops_ISHGH(nr, count, points) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_polyline != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_IRRCR); \
		_hoops_SHICP (nr, draw_dc_polyline)(&nr, count, points); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_line != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_IRRCR); \
		HD_Unwrap_Polyline (nr, count, points); \
		_hoops_SCHGH(nr); \
	} else \
				_hoops_GACIP (nr, draw_dc_polyline)(nr, count, points); \
} while (0)

#define _hoops_CSHGH(nr, count, points, color, single) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_colorized_polyline != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_CPRCR); \
		_hoops_SHICP (nr, draw_dc_colorized_polyline)(&nr, count, points, color, single); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_colorized_line != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_AARCR); \
		HD_Unwrap_Colorized_Polyline (nr, count, points, color, single); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_colorized_polyline)(nr, count, points, color, single); \
} while (0)

#define _hoops_SSHGH(nr, count, points, colors) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_gouraud_polyline != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_SPRCR); \
		_hoops_SHICP (nr, draw_dc_gouraud_polyline)(&nr, count, points, colors); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_gouraud_line != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PARCR); \
		HD_Unwrap_Gouraud_Polyline (nr, count, points, colors); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_gouraud_polyline)(nr, count, points, colors); \
} while (0)

#define _hoops_GGIGH(nr, count, points, colors, planes) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_phong_polyline != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_GHRCR); \
		_hoops_SHICP (nr, draw_dc_phong_polyline)(&nr, count, points, colors, planes); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_reshaded_line != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_HARCR); \
		HD_Unwrap_Reshaded_Polyline (nr, count, points, colors, planes, 0, 0, 0); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_phong_polyline)(nr, count, points, colors, planes); \
} while (0)

#define _hoops_RGIGH(nr, count, points, colors, planes, params, param_width, param_flags) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_textured_polyline != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_RHRCR); \
		_hoops_SHICP (nr, draw_dc_textured_polyline)(&nr, count, points, colors, planes, params, param_width, param_flags); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_reshaded_line != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_HARCR); \
		HD_Unwrap_Reshaded_Polyline (nr, count, points, colors, planes, params, param_width, param_flags); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_textured_polyline)(nr, count, points, colors, planes, params, param_width, param_flags); \
} while (0)

#define _hoops_AGIGH(nr, count, points, rotations, size_fixups) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_polymarker != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_AHRCR); \
		_hoops_SHICP (nr, draw_dc_polymarker)(&nr, count, points, rotations, size_fixups); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_marker != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_ARRCR); \
		HD_Unwrap_Polymarker (nr, count, points, rotations, size_fixups); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_polymarker)(nr, count, points, rotations, size_fixups); \
} while (0)

#define _hoops_PGIGH(nr, count, points, color, _hoops_AIPSP, rotations, size_fixups) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_colorized_polymarker != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PHRCR); \
		_hoops_SHICP (nr, draw_dc_colorized_polymarker)(&nr, count, points, color, _hoops_AIPSP, rotations, size_fixups); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_dc_colorized_marker != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_GARCR); \
		HD_Unwrap_Colorized_Polymarker (nr, count, points, color, _hoops_AIPSP, rotations, size_fixups); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_colorized_polymarker)(nr, count, points, color, _hoops_AIPSP, rotations, size_fixups); \
} while (0)

#define _hoops_HRPIP(nr, count, points) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_face != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_CRRCR); \
		_hoops_SHICP (nr, draw_dc_face)(&nr, count, points); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_face)(nr, count, points); \
} while (0)

#define _hoops_IPHCP(nr, count, points, rgb) do { \
	if ((nr)->_hoops_RSGC->action.draw_dc_colorized_face != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_SRRCR); \
		_hoops_SHICP (nr, draw_dc_colorized_face)(&nr, count, points, rgb); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_colorized_face)(nr, count, points, rgb); \
} while (0)

#define _hoops_HGIGH(nr, count, points) do { \
	if ((nr)->_hoops_RSGC->action._hoops_HSCHP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PRACR); \
		_hoops_SHICP (nr, _hoops_HSCHP)(&nr, count, points); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_polyline)(nr, count, points); \
} while (0)

#define _hoops_IGIGH(nr, points, stencil) do { \
	_hoops_GACIP (nr, _hoops_SPCGA)(nr, points, stencil); \
} while (0)

#define	 _hoops_CGIGH(nr, text_info) do { \
	if ((nr)->_hoops_RSGC->action.draw_text != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_GIRCR); \
		_hoops_SHICP (nr, draw_text) (&nr, text_info); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, _hoops_CSCGA)(nr, text_info); \
} while (0)

#define	 _hoops_SGIGH(nr, si) do { \
	if ((nr)->_hoops_RSGC->action.draw_segment_tree != nullroutine) { \
		Net_Rendition				_hoops_PPHIP = nr; \
		_hoops_PSIHP alter &	_hoops_GRIGH = _hoops_PPHIP.Modify()->_hoops_RSGC.Modify(); \
		if (_hoops_GRIGH->action.draw_segment_tree != nullroutine) { --_hoops_GRIGH->_hoops_GGCHP; \
			if (_hoops_GRIGH->_hoops_GGCHP == 0) _hoops_PPHIP->flags &= ~_hoops_HRSHP; \
		} \
		_hoops_GRIGH->action.draw_segment_tree = nullroutine; \
		_hoops_HCHGH(_hoops_PPHIP, _hoops_SSRCR); \
		_hoops_SHICP (nr, draw_segment_tree) (&_hoops_PPHIP, si); \
		_hoops_SCHGH(_hoops_PPHIP); \
	} else {\
		_hoops_HCHGH(nr, _hoops_CSRCR); \
		_hoops_SHICP (nr, draw_segment) (&nr, si); \
		_hoops_SCHGH(nr); \
	}\
} while (0)

#define	 _hoops_RRIGH(nr) do { \
	_hoops_HCHGH(nr, _hoops_HPACR); \
	_hoops_SHICP (nr, _hoops_ARSHP) (&nr); \
	_hoops_SCHGH(nr); \
} while (0)

#define	 _hoops_ARIGH(nr, si) do { \
	if ((nr)->_hoops_RSGC->action.draw_segment_tree != nullroutine) { \
		Net_Rendition		_hoops_PPHIP = nr; \
		_hoops_PPHIP.Modify()->_hoops_RSGC.Modify()->action.draw_segment_tree = nullroutine; \
		_hoops_HCHGH(_hoops_PPHIP, _hoops_GRACR); \
		_hoops_SHICP (nr, draw_segment_tree) (&_hoops_PPHIP, si); \
		_hoops_SCHGH(_hoops_PPHIP); \
	} else {\
		_hoops_HCHGH(nr, _hoops_SGACR); \
		_hoops_SHICP (nr, draw_segment) (&nr, si); \
		_hoops_SCHGH(nr); \
	} \
} while (0)

#define _hoops_GPICP(nr, marker) do if (_hoops_ICCSP (nr, _hoops_HCIP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_marker != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_RIRCR); \
		_hoops_SHICP (nr, draw_3d_marker)(&nr, marker); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)marker); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_marker)(nr, marker); \
} while (0)

#define _hoops_RPICP(nr, _hoops_CHPIR) do if (_hoops_ICCSP (nr, _hoops_HCIP)) { \
	if ((nr)->_hoops_RSGC->action._hoops_RIICP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PAHAP); \
		_hoops_SHICP (nr, _hoops_RIICP)(&nr, _hoops_CHPIR); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)_hoops_CHPIR); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, _hoops_RIICP)(nr, _hoops_CHPIR); \
} while (0)

#define _hoops_CCAIP(nr, polyline) do if (_hoops_ICCSP (nr, _hoops_CIIP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_polyline != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_AIRCR); \
		_hoops_SHICP (nr, draw_3d_polyline)(&nr, polyline); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)polyline); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_polyline)(nr, polyline); \
} while (0)

#define _hoops_PRIGH(nr, polyline) do if (_hoops_ICCSP (nr, _hoops_GCIP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_infinite_line != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PIRCR); \
		_hoops_SHICP (nr, draw_3d_infinite_line)(&nr, polyline); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)polyline); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_infinite_line)(nr, polyline); \
} while (0)

#define _hoops_SAICP(nr, curve) do if (_hoops_ICCSP (nr, _hoops_SHIP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_nurbs_curve != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_RSRCR); \
		_hoops_SHICP (nr, draw_3d_nurbs_curve)(&nr, curve); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)curve); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_nurbs_curve)(nr, curve); \
} while (0)

#define _hoops_IPICP(nr, surface) do if (_hoops_ICCSP (nr, _hoops_HRCP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_nurbs_surface != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_ASRCR); \
		_hoops_SHICP (nr, draw_3d_nurbs_surface)(&nr, surface); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)surface); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_nurbs_surface)(nr, surface); \
} while (0)

#define _hoops_CPICP(nr, _hoops_CPSSA) do if (_hoops_ICCSP (nr, _hoops_PSIP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_cylinder != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_SCRCR); \
		_hoops_SHICP (nr, draw_3d_cylinder)(&nr, _hoops_CPSSA); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)_hoops_CPSSA); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_cylinder)(nr, _hoops_CPSSA); \
} while (0)

#define _hoops_SPICP(nr, _hoops_RCPSP) do if (_hoops_ICCSP (nr, _hoops_SSIP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_polycylinder != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_GSRCR); \
		_hoops_SHICP (nr, draw_3d_polycylinder)(&nr, _hoops_RCPSP); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)_hoops_RCPSP); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_polycylinder)(nr, _hoops_RCPSP); \
} while (0)

#define _hoops_GHICP(nr, _hoops_RCPSP) do if (_hoops_ICCSP (nr, _hoops_ISIP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_sphere != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_CCRCR); \
		_hoops_SHICP (nr, draw_3d_sphere)(&nr, _hoops_RCPSP); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)_hoops_RCPSP); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_sphere)(nr, _hoops_RCPSP); \
} while (0)

#define _hoops_RCAIP(nr, polygon) do if (_hoops_ICCSP (nr, _hoops_ACIP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_polygon != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_HIRCR); \
		_hoops_SHICP (nr, draw_3d_polygon)(&nr, polygon); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)polygon); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_polygon)(nr, polygon); \
} while (0)

#if 0
#define _hoops_HRIGH(nr, _hoops_CICP) do if (_hoops_ICCSP (nr, _hoops_PCCSP)) { \
	if ((nr)->_hoops_RSGC->action._hoops_SHCHP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_RPACR); \
		_hoops_SHICP (nr, _hoops_SHCHP)(&nr, _hoops_CICP); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, _hoops_SHCHP)(nr, _hoops_CICP); \
} while (0)
#endif

#define _hoops_APICP(nr, text) do if (_hoops_ICCSP (nr, _hoops_PGCP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_text != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_IIRCR); \
		_hoops_SHICP (nr, draw_3d_text)(&nr, text); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)text); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_text)(nr, text); \
} while (0)


#define _hoops_IRIGH(nr, points, stencil) do if (_hoops_ICCSP (nr, _hoops_ACCSP)) { \
	_hoops_GACIP (nr, _hoops_CRCGA)(nr, points, stencil); \
} while (0)

#define _hoops_CRIGH(nr, image) do if (_hoops_ICCSP (nr, _hoops_IGCP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_image != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_CIRCR); \
		_hoops_SHICP (nr, draw_3d_image)(&nr, image); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)image); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_image)(nr, image); \
} while (0)

#define _hoops_PPICP(nr, grid) do if (_hoops_ICCSP (nr, _hoops_RGCP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_grid != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_SIRCR); \
		_hoops_SHICP (nr, draw_3d_grid)(&nr, grid); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)grid); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_grid)(nr, grid); \
} while (0)

#define _hoops_HPICP(nr, _hoops_IPRI) do if (_hoops_ICCSP (nr, _hoops_RSIP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_polyhedron != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_GCRCR); \
		_hoops_SHICP (nr, draw_3d_polyhedron)(&nr, _hoops_IPRI); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)_hoops_IPRI); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_polyhedron)(nr, _hoops_IPRI); \
} while (0)

#define _hoops_IAICP(nr, ellipse) do if (_hoops_ICCSP (nr, _hoops_ARCP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_ellipse != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_RCRCR); \
		_hoops_SHICP (nr, draw_3d_ellipse)(&nr, ellipse); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)ellipse); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_ellipse)(nr, ellipse); \
} while (0)

#define _hoops_CAICP(nr, _hoops_SRIGH) do if (_hoops_ICCSP (nr, _hoops_AIIP)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_elliptical_arc != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_ACRCR); \
		_hoops_SHICP (nr, draw_3d_elliptical_arc)(&nr, _hoops_SRIGH); \
		_hoops_SCHGH(nr); \
	} else if ((nr)->_hoops_RSGC->action.draw_3d_geometry != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PSRCR); \
		_hoops_SHICP (nr, draw_3d_geometry)(&nr, (Geometry const *)_hoops_SRIGH); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_elliptical_arc)(nr, _hoops_SRIGH); \
} while (0)

#define _hoops_HPHCP(nr, ts) do if (_hoops_ICCSP (nr, _hoops_GCGI)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_tristrip != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_ICRCR); \
		_hoops_SHICP (nr, draw_3d_tristrip)(&nr, ts); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_tristrip)(nr, ts); \
} while (0)

#define _hoops_GAIGH(nr, ts) do if (_hoops_ICCSP (nr, _hoops_SSCI)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_tristrip != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_ICRCR); \
		_hoops_SHICP (nr, draw_3d_tristrip)(&nr, ts); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, _hoops_ARCI)(nr, ts); \
} while (0)

#define _hoops_RAIGH(nr, pe) do if (_hoops_ICCSP (nr, _hoops_ASRI)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_polyedge != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PCRCR); \
		_hoops_SHICP (nr, draw_3d_polyedge)(&nr, pe); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_polyedge)(nr, pe); \
} while (0)

#define _hoops_AAIGH(nr, pe) do if (_hoops_ICCSP (nr, _hoops_RSRI)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_isoline != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_HRACR); \
		_hoops_SHICP (nr, draw_3d_isoline)(&nr, pe); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_polyedge)(nr, pe); \
} while (0)

#define _hoops_PAIGH(nr, pe) do if (_hoops_ICCSP (nr, _hoops_GHCI)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_polyedge != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PCRCR); \
		_hoops_SHICP (nr, draw_3d_polyedge)(&nr, pe); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, _hoops_PPAS)(nr, pe); \
} while (0)

#define _hoops_HAIGH(nr, pm) do if (_hoops_ICCSP (nr, _hoops_RGPI)) { \
	if ((nr)->_hoops_RSGC->action.draw_3d_polymarker != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_HCRCR); \
		_hoops_SHICP (nr, draw_3d_polymarker)(&nr, pm); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_3d_polymarker)(nr, pm); \
} while (0)

/*
 * _hoops_IAIGH _hoops_CAIGH _hoops_CIGR
 */

#define _hoops_HCHIP(nr, specific, _hoops_SAIGH, _hoops_GPIGH) \
	((nr)->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR ? \
		(nr)->specific._hoops_HRIR._hoops_SAIGH * (1.0f/255.0f) :\
	 (nr)->_hoops_SRA->_hoops_PGCC._hoops_PIHSR == _hoops_RIIHP ? \
		(nr)->specific._hoops_PIHHP / ((nr)->_hoops_SRA->_hoops_PGCC._hoops_PCHSR - 1) : \
	 (nr)->_hoops_SRA->_hoops_CHHIP != null ? \
		(nr)->_hoops_SRA->_hoops_CHHIP[(nr)->specific._hoops_PGGCR]._hoops_GPIGH : \
	 0)


/* _hoops_CRGH _hoops_RHPP _hoops_PSHA */

#define _hoops_CIHIP(nr) \
	_hoops_HCHIP (nr, _hoops_SAIR->_hoops_GPIR, r, red)

#define _hoops_SIHIP(nr) \
	_hoops_HCHIP (nr, _hoops_SAIR->_hoops_GPIR, g, green)

#define _hoops_GCHIP(nr) \
	_hoops_HCHIP (nr, _hoops_SAIR->_hoops_GPIR, b, blue)

#define _hoops_RCHIP(nr) \
	_hoops_HCHIP (nr, _hoops_SAIR->contrast_color, r, red)

#define _hoops_ACHIP(nr) \
	_hoops_HCHIP (nr, _hoops_SAIR->contrast_color, g, green)

#define _hoops_PCHIP(nr) \
	_hoops_HCHIP (nr, _hoops_SAIR->contrast_color, b, blue)

#define _hoops_RPIGH(nr) \
	_hoops_HCHIP (nr, _hoops_IHA->color, r, red)

#define _hoops_APIGH(nr) \
	_hoops_HCHIP (nr, _hoops_IHA->color, g, green)

#define _hoops_PPIGH(nr) \
	_hoops_HCHIP (nr, _hoops_IHA->color, b, blue)

#define _hoops_HPIGH(nr) \
	_hoops_HCHIP (nr, _hoops_IHA->_hoops_RGIR, r, red)

#define _hoops_IPIGH(nr) \
	_hoops_HCHIP (nr, _hoops_IHA->_hoops_RGIR, g, green)

#define _hoops_CPIGH(nr) \
	_hoops_HCHIP (nr, _hoops_IHA->_hoops_RGIR, b, blue)

#define _hoops_SPIGH(nr) \
	_hoops_HCHIP (nr, _hoops_IHA->contrast_color, r, red)

#define _hoops_GHIGH(nr) \
	_hoops_HCHIP (nr, _hoops_IHA->contrast_color, g, green)

#define _hoops_RHIGH(nr) \
	_hoops_HCHIP (nr, _hoops_IHA->contrast_color, b, blue)

#define _hoops_AHIGH(nr) \
	_hoops_HCHIP (nr, _hoops_AHP->color, r, red)

#define _hoops_PHIGH(nr) \
	_hoops_HCHIP (nr, _hoops_AHP->color, g, green)

#define _hoops_HHIGH(nr) \
	_hoops_HCHIP (nr, _hoops_AHP->color, b, blue)

#define _hoops_IHIGH(nr) \
	_hoops_HCHIP (nr, _hoops_GSP->color, r, red)

#define _hoops_CHIGH(nr) \
	_hoops_HCHIP (nr, _hoops_GSP->color, g, green)

#define _hoops_SHIGH(nr) \
	_hoops_HCHIP (nr, _hoops_GSP->color, b, blue)

#define _hoops_GIIGH(nr) \
	_hoops_HCHIP (nr, _hoops_SISI->color, r, red)

#define _hoops_RIIGH(nr) \
	_hoops_HCHIP (nr, _hoops_SISI->color, g, green)

#define _hoops_AIIGH(nr) \
	_hoops_HCHIP (nr, _hoops_SISI->color, b, blue)

/* _hoops_PGSA _hoops_HCPH */

#define _hoops_PIIGH(nr, pe) do if (_hoops_ICCSP (nr, _hoops_RCSI)) { \
	_hoops_GACIP (nr, draw_silhouette_polyedge)(nr, pe); \
} while (0)

#define _hoops_HIIGH(nr, pe) do if (_hoops_ICCSP (nr, _hoops_ACSI)) { \
	_hoops_GACIP (nr, _hoops_PSCSP)(nr, pe); \
} while (0)

#define _hoops_RGGSP(nr) do { \
	if ((nr)->_hoops_RSGC->action.draw_window != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_CHRCR); \
		_hoops_SHICP (nr, draw_window)(&nr, &(nr)->_hoops_SAIR->_hoops_PHRA); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_window)(nr, &(nr)->_hoops_SAIR->_hoops_PHRA); \
} while (0)

#define _hoops_ARHIP(nr, extent, frame, _hoops_HCHS) do { \
	if ((nr)->_hoops_RSGC->action.draw_window_frame != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_SHRCR); \
		_hoops_SHICP (nr, draw_window_frame)(&nr, extent, frame, _hoops_HCHS); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_window_frame)(nr, extent, frame, _hoops_HCHS); \
} while (0)

#define _hoops_IIIGH(nr, swap_buffers) do { \
	if ((nr)->_hoops_RSGC->action.finish_picture != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_PAACR); \
		_hoops_SHICP (nr, finish_picture)(&nr, swap_buffers); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, finish_picture)(nr, swap_buffers); \
} while (0)

#define _hoops_GSIIP(nr, area, image_buffer, z_buffer) do { \
	if ((nr)->_hoops_RSGC->action.create_region != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_HAACR); \
		_hoops_SHICP (nr, create_region)(&nr, area, image_buffer, z_buffer); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, create_region)(nr, area, image_buffer, z_buffer); \
} while (0)

#define _hoops_PSIIP(nr, area, image_buffer, z_buffer) do { \
	if ((nr)->_hoops_RSGC->action._hoops_HIPGR != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_IAACR); \
		_hoops_SHICP (nr, _hoops_HIPGR)(&nr, area, image_buffer, z_buffer); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, _hoops_HIPGR)(nr, area, image_buffer, z_buffer); \
} while (0)

#define _hoops_ICIIP(nr, area, image_buffer, z_buffer) do { \
	if ((nr)->_hoops_RSGC->action._hoops_PIPGR != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_CAACR); \
		_hoops_SHICP (nr, _hoops_PIPGR)(&nr, area, image_buffer, z_buffer); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, _hoops_PIPGR)(nr, area, image_buffer, z_buffer); \
} while (0)

#define _hoops_CIIGH(nr, image_buffer, z_buffer) do { \
	if ((nr)->_hoops_RSGC->action._hoops_ISPGR != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_SAACR); \
		_hoops_SHICP (nr, _hoops_ISPGR)(&nr, image_buffer, z_buffer); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, _hoops_ISPGR)(nr, image_buffer, z_buffer); \
} while (0)


/* _hoops_RHAA-_hoops_CCSI _hoops_SIIGH */

#define _hoops_GCIGH(nr, count, points) do { \
	if ((nr)->_hoops_RSGC->action._hoops_ISCHP != nullroutine)  { \
		_hoops_HCHGH(nr, _hoops_IRACR); \
		_hoops_SHICP (nr, _hoops_ISCHP)(&nr, count, points); \
		_hoops_SCHGH(nr); \
	} else \
			_hoops_GACIP (nr, draw_dc_polyline)(nr, count, points); \
} while (0)

#define _hoops_RCIGH(nr, point, rotation, _hoops_ACIGH) do { \
	if ((nr)->_hoops_RSGC->action._hoops_CSCHP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_CRACR); \
		_hoops_SHICP (nr, _hoops_CSCHP)(&nr, point); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_polymarker)(nr, 1, point, rotation, _hoops_ACIGH); \
} while (0)

#define _hoops_PCIGH(nr, point) do { \
	if ((nr)->_hoops_RSGC->action._hoops_HCPSP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_RAHAP); \
		_hoops_SHICP (nr, _hoops_HCPSP)(&nr, 1, point); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_polydot)(nr, 1, point); \
} while (0)

#define _hoops_HCIGH(nr, point, color) do { \
	if ((nr)->_hoops_RSGC->action._hoops_CCPSP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_AAHAP); \
		_hoops_SHICP (nr, _hoops_CCPSP)(&nr, 1, point, color, true); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_colorized_polydot)(nr, 1, point, color, true); \
} while (0)

#define _hoops_ICIGH(nr, count, points) do { \
	if ((nr)->_hoops_RSGC->action._hoops_SSCHP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_SRACR); \
		_hoops_SHICP (nr, _hoops_SSCHP)(&nr, count, points); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_polyline)(nr, count, points); \
} while (0)

#define _hoops_CCIGH(nr, point, rotation, _hoops_ACIGH) do { \
	if ((nr)->_hoops_RSGC->action._hoops_GGSHP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_GAACR); \
		_hoops_SHICP (nr, _hoops_GGSHP)(&nr, point); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_polymarker)(nr, 1, point, rotation, _hoops_ACIGH); \
} while (0)

#define _hoops_SCIGH(nr, point) do { \
	if ((nr)->_hoops_RSGC->action._hoops_ICPSP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_SRHAP); \
		_hoops_SHICP (nr, _hoops_ICPSP)(&nr, 1, point); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_polydot)(nr, 1, point); \
} while (0)

#define _hoops_GSIGH(nr, point, color) do { \
	if ((nr)->_hoops_RSGC->action._hoops_SCPSP != nullroutine) { \
		_hoops_HCHGH(nr, _hoops_GAHAP); \
		_hoops_SHICP (nr, _hoops_SCPSP)(&nr, 1, point, color, true); \
		_hoops_SCHGH(nr); \
	} else \
		_hoops_GACIP (nr, draw_dc_colorized_polydot)(nr, 1, point, color, true); \
} while (0)

/* _hoops_SGCRP _hoops_CAGH _hoops_PHSPR */

#define _hoops_AASS(nr, tree, _hoops_CSHPP) do if (_hoops_ICCSP (nr, _hoops_HRGC)) { \
	_hoops_GACIP (nr, _hoops_SCCSP)(nr, tree, _hoops_CSHPP); \
} while (0)

#define _hoops_RPHPP(nr, _hoops_RSIGH, _hoops_CPAI, _hoops_SIIS) \
	(_hoops_ICCSP (nr, _hoops_IRGC) ? _hoops_GACIP (nr, _hoops_CHCI)(nr, _hoops_RSIGH, _hoops_CPAI, _hoops_SIIS) : null)


/* _hoops_SGCRP _hoops_CSPH _hoops_ASCA */

#define _hoops_ASIGH(nr, text, position, count, _hoops_IHSCP, ki) \
	_hoops_GACIP (nr, _hoops_AGCSR)(nr, text, position, count, _hoops_IHSCP, ki)

#define _hoops_GGRCP(nr, points, stencil) \
	_hoops_GACIP (nr, _hoops_SPCGA)(nr, points, stencil)

#define _hoops_HAPIP(nr, point) \
	_hoops_GACIP (nr, draw_dc_polydot)(nr, 1, point)

#define _hoops_AIGGA(nr, count, point) \
	_hoops_GACIP (nr, draw_dc_polydot)(nr, count, point)

#define _hoops_RIGGA(nr, count, point, color, single) \
	_hoops_GACIP (nr, draw_dc_colorized_polydot)(nr, count, point, color, single)

#define _hoops_PSGCP(nr, count, points) \
	_hoops_GACIP (nr, _hoops_RPCGA)(nr, count, points)

#define _hoops_RSGCP(nr, count, points) \
	_hoops_GACIP (nr, draw_dc_face)(nr, count, points)

#define _hoops_AAPIP(nr, where, radius) \
	_hoops_GACIP (nr, draw_dc_ellipse)(nr, where, radius)

#define _hoops_PSIGH(nr, where, radius, start, end) \
	_hoops_GACIP (nr, _hoops_CCISR)(nr, where, radius, start, end)

#define _hoops_PAPIP(nr, where, radius) \
	_hoops_GACIP (nr, _hoops_SCISR)(nr, where, radius)

#define _hoops_ASGCP(nr, count, points, color) \
	_hoops_GACIP (nr, draw_dc_colorized_face)(nr, count, points, color)

#define _hoops_HSIGH(nr, left, right, bottom, top) \
	_hoops_GACIP (nr, draw_dc_rectangle)(nr, left, right, bottom, top)

#define _hoops_SSGCP(nr, start, end, hoffset, format, rowbytes, rasters, pattern, contrast_color, _hoops_ISIGH) \
	_hoops_GACIP (nr, _hoops_HPCGA)(nr, start, end, hoffset, format, rowbytes, rasters, pattern, contrast_color, _hoops_ISIGH)

#define _hoops_RAICP(nr, where, count, string) \
	_hoops_GACIP (nr, draw_dc_text)(nr, where, count, string)

#define _hoops_CSIGH(nr, points) \
	_hoops_GACIP (nr, draw_dc_polytriangle)(nr, 3, points)

#define _hoops_SSIGH(nr, points, color) \
	_hoops_GACIP (nr, draw_dc_colorized_polytriangle)(nr, 3, points, color, true)

#define _hoops_GGCGH(nr, points, colors) \
	_hoops_GACIP (nr, draw_dc_gouraud_polytriangle)(nr, 3, points, colors)

#define _hoops_RGCGH(nr, points, colors, planes, params, param_width, param_flags) \
	_hoops_GACIP (nr, draw_dc_textured_polytriangle)(nr, 3, points, colors, planes, params, param_width, param_flags)

#define _hoops_GSRGA(nr, count, points) \
	_hoops_GACIP (nr, draw_dc_polytriangle)(nr, count, points)

#define _hoops_SCRGA(nr, count, points, color, single) \
	_hoops_GACIP (nr, draw_dc_colorized_polytriangle)(nr, count, points, color, single)

#define _hoops_CCRGA(nr, count, points, colors) \
	_hoops_GACIP (nr, draw_dc_gouraud_polytriangle)(nr, count, points, colors)

#define _hoops_ICRGA(nr, count, points, colors, planes) \
	_hoops_GACIP (nr, draw_dc_phong_polytriangle)(nr, count, points, colors, planes)

#define _hoops_HCRGA(nr, count, points, colors, planes, params, param_width, param_flags) \
	_hoops_GACIP (nr, draw_dc_textured_polytriangle)(nr, count, points, colors, planes, params, param_width, param_flags)

#define _hoops_ISGCP(nr, point) \
	_hoops_GACIP (nr, draw_dc_polymarker)(nr, 1, point, null, null)

#define _hoops_SSHCP(nr, count, point, rotations, size_fixups) \
	_hoops_GACIP (nr, draw_dc_polymarker)(nr, count, point, rotations, size_fixups)

#define _hoops_ICGCP(nr, points) \
	_hoops_GACIP (nr, draw_dc_polyline)(nr, 2, points)

#define _hoops_CCGCP(nr, points, color) \
	_hoops_GACIP (nr, draw_dc_colorized_polyline)(nr, 2, points, color, true)

#define _hoops_SCGCP(nr, points, colors) \
	_hoops_GACIP (nr, draw_dc_gouraud_polyline)(nr, 2, points, colors)

#define _hoops_GSGCP(nr, points, colors, planes, params, param_width, param_flags) \
	_hoops_GACIP (nr, draw_dc_textured_polyline)(nr, 2, points, colors, planes, params, param_width, param_flags)

#define _hoops_SCGGA(nr, count, points) \
	_hoops_GACIP (nr, draw_dc_polyline)(nr, count, points)

#define _hoops_CCGGA(nr, count, points, color, single) \
	_hoops_GACIP (nr, draw_dc_colorized_polyline)(nr, count, points, color, single)

#define _hoops_ICGGA(nr, count, points, colors) \
	_hoops_GACIP (nr, draw_dc_gouraud_polyline)(nr, count, points, colors)

#define _hoops_HCGGA(nr, count, points, colors, planes) \
	_hoops_GACIP (nr, draw_dc_phong_polyline)(nr, count, points, colors, planes)

#define _hoops_PCGGA(nr, count, points, colors, planes, params, param_width, param_flags) \
	_hoops_GACIP (nr, draw_dc_textured_polyline)(nr, count, points, colors, planes, params, param_width, param_flags)


/* _hoops_SGCRP 3d _hoops_ASCA */

#define _hoops_PCAIP(nr, ellipse) \
	_hoops_GACIP (nr, draw_3d_ellipse)(nr, ellipse)

#define _hoops_PPAGR(nr, arc) \
	_hoops_GACIP (nr, draw_3d_elliptical_arc)(nr, arc)

#define _hoops_IPAGR(nr, curve) \
	_hoops_GACIP (nr, draw_3d_nurbs_curve)(nr, curve)

#define _hoops_RPPGR(nr, surface) \
	_hoops_GACIP (nr, draw_3d_nurbs_surface)(nr, surface)

#define _hoops_CRPGR(nr, cylinder) \
	_hoops_GACIP (nr, draw_3d_cylinder)(nr, cylinder)

#define _hoops_GAPGR(nr, polycylinder) \
	_hoops_GACIP (nr, draw_3d_polycylinder)(nr, polycylinder)

#define _hoops_SRPGR(nr, sphere) \
	_hoops_GACIP (nr, draw_3d_sphere)(nr, sphere)

#define _hoops_RAPGR(nr, grid) \
	_hoops_GACIP (nr, draw_3d_grid)(nr, grid)

#define _hoops_HAPGR(nr, image) \
	_hoops_GACIP (nr, draw_3d_image)(nr, image)

#define _hoops_RRPGR(nr, light) \
	_hoops_GACIP (nr, _hoops_HRCGA)(nr, light)

#define _hoops_SACIP(nr, pm) \
	_hoops_GACIP (nr, draw_3d_polymarker)(nr, pm)

#define _hoops_AGCGH(nr, marker) \
	_hoops_GACIP (nr, draw_3d_marker)(nr, marker)

#define _hoops_PGCGH(nr, _hoops_CHPIR) \
	_hoops_GACIP (nr, _hoops_RIICP)(nr, _hoops_CHPIR)

#define _hoops_CPAGR(nr, polyline) \
	_hoops_GACIP (nr, draw_3d_polyline)(nr, polyline)

#define _hoops_IGPGR(nr, polyline) \
	_hoops_GACIP (nr, draw_3d_infinite_line)(nr, polyline)

#define _hoops_SGPGR(nr, polygon) \
	_hoops_GACIP (nr, draw_3d_polygon)(nr, polygon)

#define _hoops_PAPGR(nr, text) \
	_hoops_GACIP (nr, draw_3d_text)(nr, text)

#define _hoops_HGCGH(nr, points, stencil) \
	_hoops_GACIP (nr, _hoops_CRCGA)(nr, points, stencil)

#define _hoops_RACIP(nr, ts) \
	if ((ts)->_hoops_HCHA != null) \
		_hoops_GACIP (nr, _hoops_ARCI)(nr, ts); \
	else _hoops_GACIP (nr, draw_3d_tristrip)(nr, ts)

#define _hoops_HRPGR(nr, phon)						\
		_hoops_GACIP (nr, draw_3d_polyhedron)(nr, phon);

#define _hoops_IACIP(nr, pe) \
	if ((pe)->_hoops_HCHA != null) \
		_hoops_GACIP (nr, _hoops_PPAS)(nr, pe); \
	else _hoops_GACIP (nr, draw_3d_polyedge)(nr, pe)

#define _hoops_IGCGH(nr, pe, ts) \
	_hoops_GACIP (nr, draw_3d_polyedge_from_tristrip)(nr, pe, ts)


/* _hoops_SGCRP _hoops_PPSCP _hoops_ASCA */

#define _hoops_CGCGH(nr, start, end, rowbytes, rasters) \
	_hoops_GACIP (nr, _hoops_CCCGA)(nr, start, end, rowbytes, rasters)

#define _hoops_SGCGH(nr, start, end, rowbytes, rasters) \
	_hoops_GACIP (nr, _hoops_GSCGA)(nr, start, end, rowbytes, rasters)

#define _hoops_GRCGH(nr, start, end, rowbytes, rasters) \
	_hoops_GACIP (nr, _hoops_CCCSR)(nr, start, end, rowbytes, rasters)

#define _hoops_RRCGH(nr, start, end, rowbytes, rasters) \
	_hoops_GACIP (nr, _hoops_PSCGA)(nr, start, end, rowbytes, rasters)

#define _hoops_ARCGH(nr, start, end, rowbytes, rasters) \
	_hoops_GACIP (nr, draw_dc_rgb32_rasters)(nr, start, end, rowbytes, rasters)

/* _hoops_SGCRP _hoops_PRCGH _hoops_SICAR */

#define _hoops_HRCGH(nr, _hoops_RHISP, _hoops_IRCGH, _hoops_PHISP, top) \
	_hoops_GACIP (nr, _hoops_CICGA)(nr, _hoops_RHISP, _hoops_IRCGH, _hoops_PHISP, top)

#define _hoops_CRCGH(nr, _hoops_RHISP, _hoops_IRCGH, _hoops_PHISP, top) \
	_hoops_GACIP (nr, _hoops_GCCGA)(nr, _hoops_RHISP, _hoops_IRCGH, _hoops_PHISP, top)

#define _hoops_SRCGH(nr, _hoops_RHISP, _hoops_IRCGH, _hoops_PHISP, top) \
	_hoops_GACIP (nr, _hoops_ACCGA)(nr, _hoops_RHISP, _hoops_IRCGH, _hoops_PHISP, top)

#define _hoops_GACGH(nr, _hoops_RHISP, _hoops_IRCGH, _hoops_PHISP, top, param_flags) \
	_hoops_GACIP (nr, _hoops_HCCGA)(nr, _hoops_RHISP, _hoops_IRCGH, _hoops_PHISP, top, param_flags)

/* _hoops_SGCRP _hoops_RPIC */

#define _hoops_ISACP(nr, _hoops_RPPHP, _hoops_ISHIR, _hoops_ICAGA, color, plane, _hoops_ASACP, params, param_width, param_flags, result, _hoops_RPCSP) \
	_hoops_GACIP (nr, _hoops_AGSSP)(nr, _hoops_RPPHP, _hoops_ISHIR, _hoops_ICAGA, color, plane, _hoops_ASACP, params, param_width, param_flags, result, _hoops_RPCSP)

/* _hoops_SRHR _hoops_CPGGR */

#define _hoops_CSSCP(nr, width, height, format, image, _hoops_PISCP) \
	_hoops_GACIP (nr, _hoops_IGSSP) (nr, width, height, format, image, _hoops_PISCP)

#define _hoops_PASCP(nr, start, end, image, hoffset, voffset, _hoops_PISCP) \
	_hoops_GACIP (nr, _hoops_CGSSP) (nr, start, end, image, hoffset, voffset, _hoops_PISCP)

#define _hoops_PCSCP(nr, image, _hoops_PISCP) \
	_hoops_GACIP (nr, _hoops_SGSSP) (nr, image, _hoops_PISCP)

/* _hoops_IAGP _hoops_RACGH */

#define _hoops_AACGH(nr, disable_write)  \
	((nr)->_hoops_SRA->_hoops_ACPGR->_hoops_GRSSP) ? \
		_hoops_GACIP (nr, _hoops_GRSSP)(nr, disable_write) : (void *)null

#define _hoops_PACGH(nr, _hoops_HACGH)  \
	((nr)->_hoops_SRA->_hoops_ACPGR->_hoops_RRSSP) ? \
		_hoops_GACIP (nr, _hoops_RRSSP)(nr, (_hoops_HACGH)) : (void)(nr)

#define _hoops_IACGH(nr, _hoops_HACGH)  \
	(((nr)->_hoops_SRA->_hoops_ACPGR->_hoops_CRGIP) ? \
		_hoops_GACIP (nr, _hoops_CRGIP)(nr, _hoops_HACGH) : 0)

#define _hoops_CACGH(nr, _hoops_HACGH)  \
	((nr)->_hoops_SRA->_hoops_ACPGR->_hoops_ARSSP) ? \
		_hoops_GACIP (nr, _hoops_ARSSP)(nr, _hoops_HACGH) : (void)(nr)

#define _hoops_SACGH(nr)  \
	((nr)->_hoops_SRA->_hoops_ACPGR->_hoops_GRSSP) ? true : false


/* _hoops_HCH _hoops_ICH */

#define _hoops_SSGGR(dc)  \
	(*(dc)->_hoops_ACPGR->_hoops_RHH)(dc)


/* _hoops_CAGH [_hoops_HHIS] _hoops_AIRI _hoops_CPCI */

#define _hoops_GPCGH(nr, dl, _hoops_CPAI, _hoops_IHGI)  \
	(((nr)->_hoops_SRA->_hoops_IPCI->_hoops_GGSI) ? \
		_hoops_GACIP (nr, _hoops_GGSI)(nr, dl, _hoops_CPAI, _hoops_IHGI) : false)

#define _hoops_RPCGH(nr, dl, _hoops_CPAI, _hoops_APCGH)  \
	(((nr)->_hoops_SRA->_hoops_IPCI->_hoops_AICI) ? \
		_hoops_GACIP (nr, _hoops_AICI)(nr, dl, _hoops_CPAI, _hoops_APCGH) : (void)0)

#define _hoops_PPCGH(nr, dl, _hoops_IHGI)  \
	(((nr)->_hoops_SRA->_hoops_IPCI->_hoops_AIGC) ? \
		_hoops_GACIP (nr, _hoops_AIGC)(nr, dl, _hoops_IHGI) : (void)0)

/* _hoops_AHSAR _hoops_IH _hoops_PISI _hoops_CPAP (_hoops_IAS._hoops_ISHI. _hoops_HCH _hoops_ICH), _hoops_GRCI _hoops_HRGR _hoops_HCAGR
 * _hoops_CHHA _hoops_GAR _hoops_ARIP _hoops_IIGR _hoops_RPGH/_hoops_RSGR */
#define _hoops_GPCIP(nr, dl)  \
	(((nr)->_hoops_SRA->_hoops_IPCI->_hoops_PPCI) ? \
		_hoops_GACIP (nr, _hoops_PPCI)(nr, dl) : (void)0)


/* _hoops_IAGIP _hoops_APGIP */

#define _hoops_HAGSP(dc)  \
	(((dc)->_hoops_IPCI->_hoops_CSPGR) ? \
		(*(dc)->_hoops_IPCI->_hoops_CSPGR)(dc) : (void)0)

#define _hoops_CHGSP(dc)  \
	(((dc)->_hoops_IPCI->_hoops_AGHGR) ? \
		(*(dc)->_hoops_IPCI->_hoops_AGHGR)(dc) : (void)0)


/* _hoops_HAIR _hoops_GGRIP */

#define _hoops_RSHIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_IGCSR alter & _hoops_IPCGH = (nr).Modify()->_hoops_SISI.Modify(); \
			_hoops_IPCGH->_hoops_CHA.Modify(); \
			_hoops_IPCGH->_hoops_RGIHP = null; \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_IPCGH->color); \
		if (_hoops_HPCGH) _hoops_IPCGH->_hoops_SCHHP = _hoops_IPCGH->color; \
		_hoops_IPCGH->_hoops_CHA->_hoops_CSHR = *(rgb);)

#define _hoops_IPIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_IGCSR alter & _hoops_IPCGH = (nr).Modify()->_hoops_SISI.Modify(); \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_IPCGH->contrast_color); \
		if (_hoops_HPCGH) _hoops_IPCGH->_hoops_GRIHP = _hoops_IPCGH->contrast_color;)


#define _hoops_ICHIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		Line_Rendition alter & _hoops_CPCGH = (nr).Modify()->_hoops_AHP.Modify(); \
			_hoops_CPCGH->_hoops_CHA.Modify(); \
			_hoops_CPCGH->_hoops_SSHHP = null; \
			_hoops_CPCGH->_hoops_IHA = null; \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_CPCGH->color); \
		if (_hoops_HPCGH) _hoops_CPCGH->_hoops_SCHHP = _hoops_CPCGH->color; \
		_hoops_CPCGH->_hoops_CHA->_hoops_CSHR = *(rgb);)

#define _hoops_RPIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		Line_Rendition alter & _hoops_CPCGH = (nr).Modify()->_hoops_AHP.Modify(); \
			_hoops_CPCGH->contrast_rendition = null; \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_CPCGH->contrast_color); \
		if (_hoops_HPCGH) _hoops_CPCGH->_hoops_GRIHP = _hoops_CPCGH->contrast_color;)

#define _hoops_GSHIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_ICP alter & _hoops_SPCGH = (nr).Modify()->_hoops_GSP.Modify(); \
			_hoops_SPCGH->_hoops_CHA.Modify(); \
			_hoops_SPCGH->_hoops_SSHHP = null; \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_SPCGH->color); \
		if (_hoops_HPCGH) _hoops_SPCGH->_hoops_SCHHP = _hoops_SPCGH->color; \
		_hoops_SPCGH->_hoops_CHA->_hoops_CSHR = *(rgb);)

#define _hoops_PPIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_ICP alter & _hoops_SPCGH = (nr).Modify()->_hoops_GSP.Modify(); \
			_hoops_SPCGH->_hoops_SSHHP = null; \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_SPCGH->contrast_color); \
		if (_hoops_HPCGH) _hoops_SPCGH->_hoops_GRIHP = _hoops_SPCGH->contrast_color;)

#define _hoops_ARIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_ICP alter & _hoops_SPCGH = (nr).Modify()->_hoops_SCP.Modify(); \
			_hoops_SPCGH->_hoops_CHA.Modify(); \
			_hoops_SPCGH->_hoops_SSHHP = null; \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_SPCGH->color); \
		if (_hoops_HPCGH) _hoops_SPCGH->_hoops_SCHHP = _hoops_SPCGH->color; \
		_hoops_SPCGH->_hoops_CHA->_hoops_CSHR = *(rgb);)

#define _hoops_HPIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_ICP alter & _hoops_SPCGH = (nr).Modify()->_hoops_SCP.Modify(); \
			_hoops_SPCGH->_hoops_SSHHP = null; \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_SPCGH->contrast_color); \
		if (_hoops_HPCGH) _hoops_SPCGH->_hoops_GRIHP = _hoops_SPCGH->contrast_color;)

#define _hoops_SCHIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_CIGA alter & _hoops_GHCGH = (nr).Modify()->_hoops_IHA.Modify(); \
			_hoops_GHCGH->_hoops_CHA.Modify(); \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_GHCGH->color); \
		if (_hoops_HPCGH) _hoops_GHCGH->_hoops_SCHHP = _hoops_GHCGH->color; \
		_hoops_GHCGH->_hoops_CHA->_hoops_CSHR = *(rgb);)

#define _hoops_IGIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_CIGA alter & _hoops_GHCGH = (nr).Modify()->_hoops_IHA.Modify(); \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_GHCGH->contrast_color); \
		if (_hoops_HPCGH) _hoops_GHCGH->_hoops_GRIHP = _hoops_GHCGH->contrast_color;)

#define _hoops_CGIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_CIGA alter & _hoops_GHCGH = (nr).Modify()->_hoops_IHA.Modify(); \
			_hoops_GHCGH->_hoops_GIA.Modify(); \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_GHCGH->_hoops_RGIR); \
		if (_hoops_HPCGH) _hoops_GHCGH->_hoops_GSHHP = _hoops_GHCGH->_hoops_RGIR; \
		_hoops_GHCGH->_hoops_GIA->_hoops_CSHR = *(rgb);)

#define _hoops_SGIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_CIGA alter & _hoops_GHCGH = (nr).Modify()->_hoops_IHA.Modify(); \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_GHCGH->_hoops_ARIHP); \
		if (_hoops_HPCGH) _hoops_GHCGH->_hoops_PRIHP = _hoops_GHCGH->_hoops_ARIHP;)

#define _hoops_GRIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_CIGA alter & _hoops_GHCGH = (nr).Modify()->_hoops_AAIHP.Modify(); \
			_hoops_GHCGH->_hoops_CHA.Modify(); \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_GHCGH->color); \
		if (_hoops_HPCGH) _hoops_GHCGH->_hoops_SCHHP = _hoops_GHCGH->color; \
		_hoops_GHCGH->_hoops_CHA->_hoops_CSHR = *(rgb);)

#define _hoops_RRIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_CIGA alter & _hoops_GHCGH = (nr).Modify()->_hoops_HAIHP.Modify(); \
			_hoops_GHCGH->_hoops_CHA.Modify(); \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_GHCGH->color); \
		if (_hoops_HPCGH) _hoops_GHCGH->_hoops_SCHHP = _hoops_GHCGH->color; \
		_hoops_GHCGH->_hoops_CHA->_hoops_CSHR = *(rgb);)

#define _hoops_RHCGH(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_CIGA alter & _hoops_GHCGH = (nr).Modify()->_hoops_HAIHP.Modify(); \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_GHCGH->color); \
		if (_hoops_HPCGH) _hoops_GHCGH->_hoops_GRIHP = _hoops_GHCGH->contrast_color;)


#define _hoops_SAIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_ISHHP alter & _hoops_AHCGH = (nr).Modify()->_hoops_ASIR.Modify(); \
		_hoops_CGRA alter & _hoops_PHCGH = (nr).Modify()->_hoops_SAIR.Modify(); \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_AHCGH->window.color); \
		_hoops_PHCGH->_hoops_GPIR = _hoops_AHCGH->window.color; \
		if (_hoops_HPCGH) _hoops_AHCGH->window._hoops_SCHHP = _hoops_AHCGH->window.color;)

#define _hoops_GPIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_ISHHP alter & _hoops_AHCGH = (nr).Modify()->_hoops_ASIR.Modify(); \
		_hoops_CGRA alter & _hoops_PHCGH = (nr).Modify()->_hoops_SAIR.Modify(); \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_AHCGH->window._hoops_HGIHP); \
		_hoops_PHCGH->contrast_color = _hoops_AHCGH->window._hoops_HGIHP; \
		if (_hoops_HPCGH) _hoops_AHCGH->window._hoops_IGIHP = _hoops_AHCGH->window._hoops_HGIHP;)


#define _hoops_HHCGH(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_CIGA alter & _hoops_GHCGH = (nr).Modify()->_hoops_IHA.Modify(); \
		_hoops_GHCGH->_hoops_CHA->color[_hoops_ACA] = *(rgb);)


#define _hoops_CCHIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		Line_Rendition alter & _hoops_CPCGH = (nr).Modify()->_hoops_RHP.Modify(); \
			_hoops_CPCGH->_hoops_CHA.Modify(); \
			_hoops_CPCGH->_hoops_SSHHP = null; \
			_hoops_CPCGH->_hoops_IHA = null; \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_CPCGH->color); \
		if (_hoops_HPCGH) _hoops_CPCGH->_hoops_SCHHP = _hoops_CPCGH->color; \
		_hoops_CPCGH->_hoops_CHA->_hoops_CSHR = *(rgb);)

#define _hoops_APIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		Line_Rendition alter & _hoops_CPCGH = (nr).Modify()->_hoops_RHP.Modify(); \
			_hoops_CPCGH->contrast_rendition = null; \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_CPCGH->contrast_color); \
		if (_hoops_HPCGH) _hoops_CPCGH->_hoops_GRIHP = _hoops_CPCGH->contrast_color;)

#define _hoops_RGIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		Line_Rendition alter & _hoops_CPCGH = (nr).Modify()->_hoops_CAIHP.Modify(); \
			_hoops_CPCGH->_hoops_CHA.Modify(); \
			_hoops_CPCGH->_hoops_SSHHP = null; \
			_hoops_CPCGH->_hoops_IHA = null; \
		HD_Figure_Driver_Color (nr, (rgb), &_hoops_CPCGH->color); \
		if (_hoops_HPCGH) _hoops_CPCGH->_hoops_SCHHP = _hoops_CPCGH->color; \
		_hoops_CPCGH->_hoops_CHA->_hoops_CSHR = *(rgb);)


#define _hoops_IAIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_GRGH alter & _hoops_IHCGH = (nr).Modify()->_hoops_IRR.Modify(); \
		_hoops_IHCGH->_hoops_HASR = *(rgb); \
		if (_hoops_HPCGH) _hoops_IHCGH->_hoops_RPIHP = *(rgb);)

#define _hoops_CAIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_GRGH alter & _hoops_IHCGH = (nr).Modify()->_hoops_IRR.Modify(); \
		_hoops_IHCGH->_hoops_CASR = *(rgb); \
		if (_hoops_HPCGH) _hoops_IHCGH->_hoops_PPIHP = *(rgb);)

#define _hoops_HAIIP(nr, rgb, _hoops_HPCGH) \
	_hoops_GHIA (\
		_hoops_IAIIP(nr, rgb, _hoops_HPCGH); \
		_hoops_CAIIP(nr, rgb, _hoops_HPCGH); \
	)


/* _hoops_PRGH _hoops_CHCGH _hoops_HRGR _hoops_IRS _hoops_APIR _hoops_IPP
   _hoops_HRS _hoops_IHPR _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_PA _hoops_AHCA _hoops_RH _hoops_APIR _hoops_IPP _hoops_SGS _hoops_CGH
   _hoops_RGRIR _hoops_IHSP _hoops_SGSI */
INLINE bool _hoops_RIRGR(Named_Material const &	mat)
{
	return ((BIT (mat._hoops_PRGRA, M_TRANSMISSION) && mat._hoops_IRIR != 1.0f) || 
			 mat.texture[_hoops_PCA] || 
			(mat._hoops_SCA && 
				BIT (mat._hoops_SCA->texture->flags, _hoops_IAPS) && 
				!BIT (mat._hoops_SCA->texture->_hoops_SCR, _hoops_PGA)));
}

INLINE bool _hoops_RIRGR(_hoops_HHA const &	matr)
{
	return (matr->_hoops_IRIR != 1.0f || 
			matr->texture[_hoops_PCA] || 
		   (matr->_hoops_SCA && 
			BIT (matr->_hoops_SCA->texture->flags, _hoops_IAPS) && 
			!BIT (matr->_hoops_SCA->texture->_hoops_SCR, _hoops_PGA)));
}

End_HOOPS_Namespace;

#define _hoops_IPRSP
#endif

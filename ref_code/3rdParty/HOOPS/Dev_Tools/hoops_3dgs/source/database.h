/*
 * Copyright (c) 1998-2008 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.955.2.1 2010-12-22 19:33:20 warren Exp $
 */

#ifndef _hoops_GRAGP
#define _hoops_GRAGP

#include "hi_proto.h"

Begin_HOOPS_Namespace

// _hoops_RRAGP _hoops_SIHC _hoops_CSSC		***** _hoops_RGCA _hoops_ARAGP _hoops_CHASR _hoops_AGGPA _hoops_PRAGP! _hoops_PPR _hoops_GAAP _hoops_HRAGP _hoops_IRAGP *****
enum _hoops_CRAGP {
	HK_STYLE,				/*  0 */		/* _hoops_GRH _hoops_SRAGP */						_hoops_GAAGP = HK_STYLE,

	_hoops_CPPIR,						_hoops_RAAGP = _hoops_CPPIR,
	_hoops_IPAIR,
	_hoops_RAAIR,
	_hoops_RPAIR,
	_hoops_HAAIR,	/*  5 */

	HK_RENDERING_OPTIONS,					_hoops_AAAGP = HK_RENDERING_OPTIONS,
	HK_SELECTABILITY,
	HK_VISIBILITY,
	HK_COLOR_MAP,							// _hoops_PIHA _hoops_SHH _hoops_ARPP _hoops_RII _hoops_PSHA
	HK_COLOR,				/* 10 */
	HK_WINDOW_FRAME,						// _hoops_PIHA _hoops_SHH _hoops_ARPP _hoops_PAAGP
	HK_WINDOW_PATTERN,
	HK_WINDOW,								// _hoops_SRPR _hoops_SRAGP, _hoops_HIH _hoops_GRHP _hoops_GAR _hoops_RSIH _hoops_GAR _hoops_GHAR
	HK_CAMERA,
	HK_HEURISTICS,			/* 15 */
	HK_MODELLING_MATRIX,					// _hoops_RHIR _hoops_ARI _hoops_HAAGP _hoops_IAAGP _hoops_RHSP _hoops_PHSPR, _hoops_HIS _hoops_GRHP _hoops_RSIH
	HK_CALLBACK,
	HK_CLIP_REGION,
	HK_DRIVER,
	HK_DRIVER_OPTIONS,		/* 20 */
	HK_EDGE_PATTERN,
	HK_EDGE_WEIGHT,
	HK_FACE_PATTERN,
	HK_HANDEDNESS,
	HK_LINE_PATTERN,		/* 25 */
	HK_LINE_WEIGHT,
	HK_MARKER_SIZE,
	HK_MARKER_SYMBOL,
	HK_TEXT_ALIGNMENT,
	HK_TEXT_FONT,			/* 30 */
	HK_TEXT_PATH,
	HK_TEXT_SPACING,
	HK_USER_OPTIONS,
	HK_USER_VALUE,
	HK_TEXTURE_MATRIX,		/* 35 */		_hoops_CAAGP = HK_TEXTURE_MATRIX,

	_hoops_GRAIR,					_hoops_CRCCA = _hoops_GRAIR,


	// _hoops_HPPA _hoops_GHC _hoops_PPR _hoops_SS _hoops_SRS _hoops_IS _hoops_IRHH _hoops_SAAGP _hoops_CIGCR _hoops_GPAGP
	_hoops_HGPGR,					_hoops_AHRIR = _hoops_HGPGR,
	_hoops_ICIP,
	// _hoops_SIRAR _hoops_ISSGR _hoops_CSSC
	_hoops_SCIP,
	_hoops_GSIP,				/* 40 */
	_hoops_GGCP,
	_hoops_PRCP,
	_hoops_ASIP,
	_hoops_CSIP,
	_hoops_HSIP,				/* 45 */
	// _hoops_IHGP _hoops_RPAGP _hoops_CSSC
	_hoops_RCIP,
	_hoops_SGCP,
	_hoops_GRCP,
	_hoops_RRCP,
	_hoops_CGCP,				/* 50 */
	// _hoops_IHGP _hoops_ISII _hoops_CSSC
	_hoops_PIIP,
	_hoops_HIIP,
	_hoops_IIIP,
	_hoops_CHIP,
	_hoops_RIIP,		/* 55 */
	_hoops_GIIP,
	_hoops_SIIP,
	// _hoops_APAGP
	_hoops_HGCP,
	_hoops_PCIP,
	_hoops_PIRS,			/* 60 */
	_hoops_AGCP,
	HK_STRING_CURSOR,
	_hoops_AHIP,
	// _hoops_GGAGA _hoops_GGR _hoops_AGIR _hoops_IIGR "_hoops_PPGS _hoops_PPAGP", _hoops_PIHA _hoops_SHH _hoops_CGHI
	_hoops_GHPGR,				_hoops_PHRIR = _hoops_GHPGR,


	_hoops_AGRPR,				/* 65 */	_hoops_IISIR = _hoops_AGRPR,
	_hoops_IRCP,							_hoops_IHRIR = _hoops_IRCP,


	// _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_AGCR _hoops_PAH _hoops_SHH _hoops_GGR _hoops_GII _hoops_AGR...
	_hoops_AGAIR,						_hoops_HPAGP = _hoops_AGAIR,
	_hoops_CIRIR,
	_hoops_PRAIR,
	_hoops_IIPPR,				/* 70 */
	_hoops_PCHIR,
	_hoops_CCHIR,
	_hoops_GGIIR,
	_hoops_CSHIR,
	_hoops_AGIIR,				/* 75 */
	_hoops_GRIIR,
	_hoops_PRIIR,
	_hoops_AIIIR,
	_hoops_PARIR,
	_hoops_IARIR,		/* 80 */
	_hoops_CARIR,
	_hoops_HCIIR,
	_hoops_ARHIR,
	_hoops_PIRIR,					_hoops_IPAGP = _hoops_PIRIR,

	_hoops_CRIIR,		/* 85 */	_hoops_CPAGP = _hoops_CRIIR,
	_hoops_AAIIR,
	_hoops_SAIIR,
	_hoops_GIIIR,
	_hoops_RHIIR,
	_hoops_PHIIR,		/* 90 */	_hoops_SPAGP = _hoops_PHIIR,				_hoops_GHAGP = _hoops_SPAGP,

	_hoops_RHAGP
};
_hoops_AHAGP (1+(_hoops_CAAGP-_hoops_AAAGP+1) <= 32, _hoops_PHAGP);



typedef unsigned Integer32	_hoops_HHAGP;

INLINE _hoops_HHAGP 	_hoops_GGCAA (Type type) {
	if (type == HK_STYLE)
		return (_hoops_HHAGP)1UL;

	return (_hoops_HHAGP) (1UL << (type - _hoops_AAAGP + 1));
}





_hoops_AHAGP (sizeof(_hoops_GHRIR) == sizeof(unsigned Integer32), _hoops_IHAGP);

// _hoops_HAR _hoops_CPSA _hoops_RCIC, _hoops_HIH _hoops_PCIC _hoops_IHH _hoops_CIPSR _hoops_GPP _hoops_CIS
INLINE	int		_hoops_SPRIR (unsigned Integer32 const * value) {
	int		result;

#	if defined(_hoops_CHAGP)
		result = _InterlockedDecrement ((long*)value);
#	elif defined(_hoops_IIIPA)
		__asm {
			mov				edi, dword ptr value	; edi = value
			mov				eax, -1					; eax = -1
			lock _hoops_SHAGP		dword ptr [edi], eax	; add 1 to value, eax = _hoops_GIAGP
			dec				eax						; _hoops_RIAGP _hoops_SSPCR _hoops_AIAGP
			mov				result, eax				; result = _hoops_PIAGP;
		}
#	elif defined(_hoops_HIAGP)
		result = __sync_fetch_and_sub ((unsigned Integer32 volatile *)value, 1) - 1;
#	else
		_hoops_CAAI (HOOPS_WORLD->_hoops_IIAGP);
		result = --*(unsigned Integer32 alter *)value;
		_hoops_APAI (HOOPS_WORLD->_hoops_IIAGP);
#	endif

	return result;
}

// _hoops_HAR _hoops_CPSA _hoops_RCIC, _hoops_HIH _hoops_PCIC _hoops_IHH _hoops_CIPSR _hoops_GPP _hoops_CIS
INLINE	int		_hoops_CIAGP (unsigned Integer32 const * value) {
	int		result;

#	if defined(_hoops_CHAGP)
		result = _InterlockedIncrement ((long*)value);
#	elif defined(_hoops_IIIPA)
		__asm {
			mov				edi, dword ptr value	; edi = value
			mov				eax, 1					; eax = 1
			lock _hoops_SHAGP		dword ptr [edi], eax	; add 1 to value, eax = _hoops_GIAGP
			inc				eax						; _hoops_RIAGP _hoops_SSPCR _hoops_AIAGP
			mov				result, eax				; result = _hoops_PIAGP;
		}
#	elif defined(_hoops_HIAGP)
		result = __sync_fetch_and_add ((unsigned Integer32 volatile *)value, 1) + 1;
#	else
		_hoops_CAAI (HOOPS_WORLD->_hoops_IIAGP);
		result = ++*(unsigned Integer32 alter *)value;
		_hoops_APAI (HOOPS_WORLD->_hoops_IIAGP);
#	endif

	return result;
}



INLINE	int		_hoops_SIAGP (unsigned Integer32 alter * value) {
	int		result;

#	if defined(_hoops_CHAGP)
		result = _InterlockedExchange ((long *)value, 1);
#	elif defined(_hoops_IIIPA)
		__asm {
			mov				edi, dword ptr value	; edi = value
			mov				eax, 1					; eax = set
			lock _hoops_GCAGP		dword ptr [edi], eax	; _hoops_RCAGP
			mov				result, eax				; result = old value
		}
#	elif defined(_hoops_HIAGP)
		result =  __sync_lock_test_and_set (value, 1);
#	else
		_hoops_CAAI (HOOPS_WORLD->_hoops_IIAGP);
		result = *value;
		*value = 1;
		_hoops_APAI (HOOPS_WORLD->_hoops_IIAGP);
#	endif

	return result;
}

INLINE	void	_hoops_ACAGP (unsigned Integer32 alter * value) {
#	if defined(_hoops_CHAGP)
		_InterlockedExchange ((long *)value, 0);
#	elif defined(_hoops_IIIPA)
		__asm {
			mov				edi, dword ptr value	; edi = value
			mov				eax, 0					; eax = clear
			lock _hoops_GCAGP		dword ptr [edi], eax	; _hoops_RCAGP
		}
#	elif defined(_hoops_HIAGP)
		__sync_lock_release (value);
#	else
		_hoops_CAAI (HOOPS_WORLD->_hoops_IIAGP);
		*value = 0;
		_hoops_APAI (HOOPS_WORLD->_hoops_IIAGP);
#	endif
}




local INLINE bool _hoops_PCAGP (unsigned Integer32 const * value) {
#ifdef VALIDATE_MEMORY
	if (*value == 0x55555555) {
		HE_ERROR (0, 0, "detected modify after free");
		return false;
	}
#else
	UNREFERENCED(value);
#endif
	return true;
}

// _hoops_IHIR _hoops_AARPR _hoops_APSAR _hoops_HGCR _hoops_AAII _hoops_CGPR _hoops_SSIA _hoops_PHHR _hoops_IS _hoops_AHHR

template <typename T>
local INLINE void _hoops_PRRH (T const * ref) {
	_hoops_GHRIR *	_hoops_HIHI = (_hoops_GHRIR *) &ref->_hoops_HIHI;

	if (_hoops_PCAGP (_hoops_HIHI)) {
		if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))
			_hoops_CIAGP (_hoops_HIHI);
		else
			++*_hoops_HIHI;
	}
}

template <typename T>
local INLINE void _hoops_HPRH (T const * ref) {
	_hoops_GHRIR *	_hoops_HIHI = (_hoops_GHRIR *) &ref->_hoops_HIHI;

	if (_hoops_PCAGP (_hoops_HIHI)) {
		if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP)) {
			if (_hoops_SPRIR (_hoops_HIHI) == 0)
				HI_Au_Revoir ((_hoops_HPAH *)ref);
		}
		else {
			if (--*_hoops_HIHI == 0)
				HI_Au_Revoir ((_hoops_HPAH *)ref);
		}
	}
}




class _hoops_ICAGP : public CMO {
	protected:
		mutable unsigned Integer32		_hoops_HIHI;

	protected:
		_hoops_ICAGP () : _hoops_HIHI (0) {}
		_hoops_ICAGP (_hoops_ICAGP const &) : _hoops_HIHI (0) {}

	public:
		INLINE void	retain () const {
			if (_hoops_PCAGP (&_hoops_HIHI)) {
				if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP))
					_hoops_CIAGP (&_hoops_HIHI);
				else
					++_hoops_HIHI;
			}
		}
		INLINE void	release () const {
			if (_hoops_PCAGP (&_hoops_HIHI)) {
				if (BIT (HOOPS_WORLD->system_flags, _hoops_HCAGP)) {
					if (_hoops_SPRIR (&_hoops_HIHI) == 0)
						delete this;
				}
				else {
					if (--_hoops_HIHI == 0)
						delete this;
				}
			}
		}

		INLINE bool	shared () const		{ return _hoops_HIHI > 1; }


	private:
		void operator= (_hoops_ICAGP const &) alter;		// _hoops_PSP _hoops_CHAAR, _hoops_RGAR _hoops_IPS
};



class _hoops_CCAGP {
	private:
		mutable HThreadID				owner;
		mutable unsigned Integer32		flag;
		mutable unsigned Integer32		_hoops_SCAGP;

	public:
		_hoops_CCAGP () : owner (0), flag (0), _hoops_SCAGP (0) {}

		// _hoops_GA'_hoops_RA _hoops_CPSA _hoops_HHGC _hoops_PAR _hoops_RRP _hoops_AGCR (_hoops_GAPR), _hoops_AHSAR _hoops_IS _hoops_GSAGP _hoops_GH _hoops_RH _hoops_HICA
		_hoops_CCAGP (_hoops_CCAGP const &) : owner (0), flag (0), _hoops_SCAGP (0) {}
		_hoops_CCAGP const & operator= (_hoops_CCAGP const &) { owner = 0; flag = 0; _hoops_SCAGP = 0; return *this; }

		INLINE void _hoops_PRPGR(HThreadID me) const {
			if (owner == me) {
				++_hoops_SCAGP;		// _hoops_CARS _hoops_APIC
				return;
			}

			int					_hoops_RSAGP = 0;

			while (_hoops_SIAGP (&flag) != 0) {
				if (++_hoops_RSAGP == 64) {
					MILLI_SECOND_SLEEP (0);
					_hoops_RSAGP = 0;
				}
			}

			owner = me;
			_hoops_SCAGP = 1;
		}

		INLINE void _hoops_IRPGR() const {
			if (owner != 0 && --_hoops_SCAGP == 0) {
				owner = 0;
				_hoops_ACAGP (&flag);
			}
		}

		INLINE bool _hoops_ASAGP(HThreadID me) const {
			return(owner == me);
		}
};


class _hoops_SPAGR {
	private:
		_hoops_CCAGP const &		data;
		HThreadID				id;
		bool					_hoops_PSAGP;

	public:
		_hoops_SPAGR (_hoops_CCAGP const & _hoops_HSAGP, HThreadID _hoops_ISAGP, bool _hoops_CSAGP=true) : data (_hoops_HSAGP), id(_hoops_ISAGP), _hoops_PSAGP(false) {
			if (_hoops_CSAGP)
				_hoops_SSAGP();	
		}

		~_hoops_SPAGR () {
			if (_hoops_PSAGP)
				_hoops_GGPGP();
		}

		void _hoops_SSAGP() {
			ASSERT(!_hoops_PSAGP);
			data._hoops_PRPGR(id);
			_hoops_PSAGP = true;
		}

		void _hoops_GGPGP() {
			ASSERT(_hoops_PSAGP);
			data._hoops_IRPGR();
			_hoops_PSAGP = false;
		}

	private:
		_hoops_SPAGR (_hoops_SPAGR const &);
		void operator= (_hoops_SPAGR const &);
};


struct Int_Rectangle {
	int			left, right, bottom, top;

	Int_Rectangle ()
		: left (_hoops_IICIA), right (-_hoops_IICIA), bottom (_hoops_IICIA), top (-_hoops_IICIA) {}

	Int_Rectangle (int _hoops_PCPRR, int _hoops_ICPRR, int _hoops_HCPRR, int _hoops_CCPRR)
		: left (_hoops_PCPRR), right (_hoops_ICPRR), bottom (_hoops_HCPRR), top (_hoops_CCPRR) {}

	Int_Rectangle (Int_Rectangle const & _hoops_HACIR)
		: left (_hoops_HACIR.left), right (_hoops_HACIR.right), bottom (_hoops_HACIR.bottom), top (_hoops_HACIR.top) {}

	Int_Rectangle (_hoops_PACIR const & _hoops_HACIR);

	bool			operator== (Int_Rectangle const & rect) const	{
		return  (left == rect.left && right == rect.right && bottom == rect.bottom && top == rect.top);
	}
	bool			operator!= (Int_Rectangle const & rect) const	{ return  !(*this == rect); }

	INLINE bool _hoops_RPCIR (Int_Rectangle const & rect) const {
		return	(right >= rect.left && left <= rect.right ||
				 rect.right >= left && rect.left <= right) &&
				(top >= rect.bottom && bottom <= rect.top ||
				 rect.top >= bottom && rect.bottom <= top);
	}

#if 0
	INLINE bool _hoops_HPCIR(DC_Point const & _hoops_RGPGP) const {

		return (_hoops_RGPGP.x >= left && _hoops_RGPGP.x <= right &&
			_hoops_RGPGP.y >= bottom && _hoops_RGPGP.y <= top);
	}
#endif

	INLINE bool _hoops_HPCIR(Int_Rectangle const & rect) const {
		return (left <= rect.left && right >= rect.right &&
				bottom <= rect.bottom && top >= rect.top);
	}

	INLINE Int_Rectangle & _hoops_IACHA(int border) alter {
		left -= border;
		right += border;
		bottom -= border;
		top += border;
		return *this;
	}

	INLINE Int_Rectangle & _hoops_IACHA(Int_Rectangle const & rect) alter {
		left -= rect.left;
		right += rect.right;
		bottom -= rect.bottom;
		top += rect.top;
		return *this;
	}

	INLINE Int_Rectangle & _hoops_AGPGP(int border) alter {
		left += border;
		right -= border;
		bottom += border;
		top -= border;
		return *this;
	}

	INLINE Int_Rectangle & _hoops_AGPGP(Int_Rectangle const & rect) alter {
		left += rect.left;
		right -= rect.right;
		bottom += rect.bottom;
		top -= rect.top;
		return *this;
	}

	INLINE Int_Rectangle & _hoops_PGPGP(Int_Rectangle const & rect) alter {
		left = _hoops_IAAA(left, rect.left);
		right = _hoops_AHIA(right, rect.right);
		bottom = _hoops_IAAA(bottom, rect.bottom);
		top = _hoops_AHIA(top, rect.top);
		return *this;
	}

	INLINE Int_Rectangle & _hoops_AACIR(Int_Rectangle const& rect) alter {
		left = _hoops_AHIA(left, rect.left);
		right = _hoops_IAAA(right, rect.right);
		bottom = _hoops_AHIA(bottom, rect.bottom);
		top = _hoops_IAAA(top, rect.top);
		return *this;
	}
};


INLINE Int_Rectangle _hoops_IACHA(Int_Rectangle const & a, Int_Rectangle const & border) {
	Int_Rectangle temp = a;
	return temp._hoops_IACHA(border);
}

INLINE Int_Rectangle _hoops_IACHA(Int_Rectangle const & a, int border) {
	Int_Rectangle temp = a;
	return temp._hoops_IACHA(border);
}

INLINE Int_Rectangle _hoops_AGPGP(Int_Rectangle const & a, int border) {
	Int_Rectangle temp = a;
	return temp._hoops_AGPGP(border);
}

INLINE Int_Rectangle _hoops_AGPGP(Int_Rectangle const & a, Int_Rectangle const & border) {
	Int_Rectangle temp = a;
	return temp._hoops_AGPGP(border);
}

INLINE Int_Rectangle _hoops_PGPGP(Int_Rectangle const & a, Int_Rectangle const & b) {
	Int_Rectangle temp = a;
	return temp._hoops_PGPGP(b);
}

INLINE Int_Rectangle _hoops_AACIR(Int_Rectangle const & a, Int_Rectangle const & b) {
	Int_Rectangle temp = a;
	return temp._hoops_AACIR(b);
}

struct _hoops_PACIR {
	float		left, right, bottom, top;

	_hoops_PACIR ()
		: left (MAX_FLOAT), right (-MAX_FLOAT), bottom (MAX_FLOAT), top (-MAX_FLOAT) {}

	_hoops_PACIR (float _hoops_PCPRR, float _hoops_ICPRR, float _hoops_HCPRR, float _hoops_CCPRR)
		: left (_hoops_PCPRR), right (_hoops_ICPRR), bottom (_hoops_HCPRR), top (_hoops_CCPRR) {}

	_hoops_PACIR (_hoops_PACIR const & _hoops_HACIR)
		: left (_hoops_HACIR.left), right (_hoops_HACIR.right), bottom (_hoops_HACIR.bottom), top (_hoops_HACIR.top) {}

	_hoops_PACIR (Int_Rectangle const & _hoops_HACIR)
		: left ((float)_hoops_HACIR.left), right ((float)_hoops_HACIR.right), bottom ((float)_hoops_HACIR.bottom), top ((float)_hoops_HACIR.top) {}

	_hoops_PACIR (int count, DC_Point const * points) {
		left = right = points[0].x;
		bottom = top = points[0].y;
		for (int j=1; j<count; j++) {
			if (left > points[j].x)
				left = points[j].x;
			else if (right < points[j].x)
				right = points[j].x;

			if (bottom > points[j].y)
				bottom = points[j].y;
			else if (top < points[j].y)
				top = points[j].y;
		}
	}

	bool			operator== (_hoops_PACIR const & rect) const	{
		return  (left == rect.left && right == rect.right && bottom == rect.bottom && top == rect.top);
	}
	bool			operator!= (_hoops_PACIR const & rect) const	{ return  !(*this == rect); }


	INLINE bool _hoops_RPCIR (_hoops_PACIR const & rect) const {
		return	(right >= rect.left && left <= rect.right ||
				 rect.right >= left && rect.left <= right) &&
				(top >= rect.bottom && bottom <= rect.top ||
				 rect.top >= bottom && rect.bottom <= top);
	}

	INLINE bool _hoops_HPCIR(DC_Point const & _hoops_RGPGP) const {

		return (_hoops_RGPGP.x >= left && _hoops_RGPGP.x <= right &&
				_hoops_RGPGP.y >= bottom && _hoops_RGPGP.y <= top);
	}

	INLINE bool _hoops_HPCIR(_hoops_PACIR const & rect) {

		return (left <= rect.left &&
			right >= rect.right &&
			bottom <= rect.bottom &&
			top >= rect.top);
	}

	INLINE bool _hoops_HPCIR(_hoops_PACIR const & rect, float _hoops_GSAHR) {

		return (left <= rect.left + _hoops_GSAHR &&
				right >= rect.right - _hoops_GSAHR &&
				bottom <= rect.bottom + _hoops_GSAHR &&
				top >= rect.top	- _hoops_GSAHR);
	}

	INLINE _hoops_PACIR & _hoops_IACHA(int border) alter {
		left -= border;
		right += border;
		bottom -= border;
		top += border;
		return *this;
	}

	INLINE _hoops_PACIR & _hoops_IACHA(Int_Rectangle const & rect) alter {
		left -= rect.left;
		right += rect.right;
		bottom -= rect.bottom;
		top += rect.top;
		return *this;
	}

	INLINE _hoops_PACIR & _hoops_AGPGP(int border) alter {
		left += border;
		right -= border;
		bottom += border;
		top -= border;
		return *this;
	}

	INLINE _hoops_PACIR & _hoops_AGPGP(_hoops_PACIR const & rect) alter {
		left += rect.left;
		right -= rect.right;
		bottom += rect.bottom;
		top -= rect.top;
		return *this;
	}

	INLINE _hoops_PACIR & _hoops_PGPGP(_hoops_PACIR const & rect) alter {
		left = _hoops_IAAA(left, rect.left);
		right = _hoops_AHIA(right, rect.right);
		bottom = _hoops_IAAA(bottom, rect.bottom);
		top = _hoops_AHIA(top, rect.top);
		return *this;
	}

	INLINE _hoops_PACIR & _hoops_AACIR(_hoops_PACIR const& rect) alter {
		left = _hoops_AHIA(left, rect.left);
		right = _hoops_IAAA(right, rect.right);
		bottom = _hoops_AHIA(bottom, rect.bottom);
		top = _hoops_IAAA(top, rect.top);
		return *this;
	}

	INLINE _hoops_PACIR & _hoops_HGPGP (_hoops_PACIR const & scope) {

		float scale = (scope.right - scope.left) * 0.5f;
		float _hoops_IGPGP = (scope.right + scope.left) * 0.5f;

		left = left * scale + _hoops_IGPGP;
		right = right * scale + _hoops_IGPGP;

		scale = (scope.top - scope.bottom) * 0.5f;
		_hoops_IGPGP = (scope.top + scope.bottom) * 0.5f;

		bottom = bottom * scale + _hoops_IGPGP;
		top = top * scale + _hoops_IGPGP;
		return *this;
	}

	INLINE _hoops_PACIR & _hoops_CGPGP (_hoops_PACIR const & scope) {

		float tmp = 2.0f/(scope.right - scope.left);
		right = (right - scope.left) * tmp - 1.0f;
		left = (left - scope.left) * tmp - 1.0f;

		tmp = 2.0f/(scope.top - scope.bottom);
		top = (top - scope.bottom) * tmp - 1.0f;
		bottom = (bottom - scope.bottom) * tmp - 1.0f;
		return *this;
	}
};


INLINE _hoops_PACIR _hoops_IACHA(_hoops_PACIR const & a, _hoops_PACIR const & border) {
	_hoops_PACIR temp = a;
	return temp._hoops_IACHA(border);
}

INLINE _hoops_PACIR _hoops_IACHA(_hoops_PACIR const & a, int border) {
	_hoops_PACIR temp = a;
	return temp._hoops_IACHA(border);
}

INLINE _hoops_PACIR _hoops_AGPGP(_hoops_PACIR const & a, int border) {
	_hoops_PACIR temp = a;
	return temp._hoops_AGPGP(border);
}

INLINE _hoops_PACIR _hoops_AGPGP(_hoops_PACIR const & a, _hoops_PACIR const & border) {
	_hoops_PACIR temp = a;
	return temp._hoops_AGPGP(border);
}

INLINE _hoops_PACIR _hoops_PGPGP(_hoops_PACIR const & a, _hoops_PACIR const & b) {
	_hoops_PACIR temp = a;
	return temp._hoops_PGPGP(b);
}

INLINE _hoops_PACIR _hoops_AACIR(_hoops_PACIR const & a, _hoops_PACIR const & b) {
	_hoops_PACIR temp = a;
	return temp._hoops_AACIR(b);
}

INLINE _hoops_PACIR _hoops_HGPGP(_hoops_PACIR const & a, _hoops_PACIR const & scope) {
	_hoops_PACIR temp = a;
	return temp._hoops_HGPGP(scope);
}

INLINE _hoops_PACIR _hoops_CGPGP(_hoops_PACIR const & a, _hoops_PACIR const & scope) {
	_hoops_PACIR temp = a;
	return temp._hoops_CGPGP(scope);
}


struct _hoops_PGCIR : public _hoops_PACIR {
	float	hither, yon;
};


namespace _hoops_SGPGP {
	extern HOOPS_API const _hoops_PACIR		_hoops_GRPGP;
}

/* _hoops_RRPGP _hoops_GRPC _hoops_HII _hoops_IPIS _hoops_GAR _hoops_ARPGP _hoops_RSSA */
INLINE void	HI_Generate_Cuboid_Points (Point const & min, Point const & max, Point alter * points, int alter * face_list = null) {
	points[0].x = min.x;	 points[0].y = min.y;	  points[0].z = min.z;
	points[1].x = min.x;	 points[1].y = min.y;	  points[1].z = max.z;
	points[2].x = min.x;	 points[2].y = max.y;	  points[2].z = min.z;
	points[3].x = min.x;	 points[3].y = max.y;	  points[3].z = max.z;
	points[4].x = max.x;	 points[4].y = min.y;	  points[4].z = min.z;
	points[5].x = max.x;	 points[5].y = min.y;	  points[5].z = max.z;
	points[6].x = max.x;	 points[6].y = max.y;	  points[6].z = min.z;
	points[7].x = max.x;	 points[7].y = max.y;	  points[7].z = max.z;

	if (face_list) {
		face_list[0] = 4;
		face_list[1] = 0;
		face_list[2] = 1;
		face_list[3] = 2;
		face_list[4] = 3;

		face_list[5] = 4;
		face_list[6] = 7;
		face_list[7] = 6;
		face_list[8] = 5;
		face_list[9] = 4;

		face_list[10] = 4;
		face_list[11] = 1;
		face_list[12] = 5;
		face_list[13] = 6;
		face_list[14] = 2;

		face_list[15] = 4;
		face_list[16] = 4;
		face_list[17] = 0;
		face_list[18] = 3;
		face_list[19] = 7;

		face_list[20] = 4;
		face_list[21] = 3;
		face_list[22] = 2;
		face_list[23] = 6;
		face_list[24] = 7;

		face_list[25] = 4;
		face_list[26] = 4;
		face_list[27] = 5;
		face_list[28] = 1;
		face_list[29] = 0;
	}
}

struct HOOPS_API _hoops_SASC {
	Point				min, max;

	_hoops_SASC () {
		min = Point(MAX_FLOAT, MAX_FLOAT, MAX_FLOAT);
		max = Point(-MAX_FLOAT, -MAX_FLOAT, -MAX_FLOAT);
	}

	_hoops_SASC (int count, Point const * points) {
		min = max = *points++;
		--count;
		if (count>0)
			Merge(count, points);
	}

	_hoops_SASC (Point const & _hoops_PRPGP, Point const & _hoops_HRPGP) {
		min = _hoops_PRPGP;
		max = _hoops_HRPGP;
	}

	_hoops_SASC (_hoops_PACIR const & _hoops_HACIR) {
		min = Point(_hoops_HACIR.left, _hoops_HACIR.bottom, 0.0f);
		max = Point(_hoops_HACIR.right, _hoops_HACIR.top, 0);
	}

	_hoops_SASC (_hoops_SASC const & _hoops_HACIR) {
		min = _hoops_HACIR.min;
		max = _hoops_HACIR.max;
	}

	_hoops_SASC (_hoops_CAIS const & _hoops_HACIR);

	bool			operator== (_hoops_SASC const & cuboid) const	{ return  (min == cuboid.min && max == cuboid.max); }
	bool			operator!= (_hoops_SASC const & cuboid) const	{ return  !(*this == cuboid); }

	INLINE void _hoops_GPSC (Point alter * points) const {
		HI_Generate_Cuboid_Points (min, max, points);
	}

	INLINE Vector _hoops_RSAIA() const {
		return Vector(max-min);
	}

	INLINE float _hoops_PGCIR () const {
		return (max.x - min.x) * (max.y - min.y) * (max.z - min.z);
	}

	INLINE bool _hoops_RPCIR (_hoops_SASC const & cuboid) const {
		return	(max.x >= cuboid.min.x && min.x <= cuboid.max.x ||
				 cuboid.max.x >= min.x && cuboid.min.x <= max.x) &&
				(max.y >= cuboid.min.y && min.y <= cuboid.max.y ||
				 cuboid.max.y >= min.y && cuboid.min.y <= max.y) &&
				(max.z >= cuboid.min.z && min.z <= cuboid.max.z ||
				 cuboid.max.z >= min.z && cuboid.min.z <= max.z);
	}

	bool _hoops_RPCIR (Point const & start, Vector const & direction) const;

	INLINE void Merge(_hoops_SASC const & cuboid) alter {
		if (cuboid.min.x < min.x)
			min.x = cuboid.min.x;
		if (cuboid.min.y < min.y)
			min.y = cuboid.min.y;
		if (cuboid.min.z < min.z)
			min.z = cuboid.min.z;
		if (cuboid.max.x > max.x)
			max.x = cuboid.max.x;
		if (cuboid.max.y > max.y)
			max.y = cuboid.max.y;
		if (cuboid.max.z > max.z)
			max.z = cuboid.max.z;
	}

	INLINE void Merge(_hoops_CAIS const & sphere) alter;

	INLINE void Merge(Point const & point) alter {
		min.x = _hoops_AHIA (min.x, point.x);
		min.y = _hoops_AHIA (min.y, point.y);
		min.z = _hoops_AHIA (min.z, point.z);
		max.x = _hoops_IAAA (max.x, point.x);
		max.y = _hoops_IAAA (max.y, point.y);
		max.z = _hoops_IAAA (max.z, point.z);
	}

	INLINE void Merge(int count, Point const * points) alter {

		while (count > 1) {
			if (points[0].x > points[1].x) {
				min.x = _hoops_AHIA (min.x, points[1].x);
				max.x = _hoops_IAAA (max.x, points[0].x);
			}
			else {
				min.x = _hoops_AHIA (min.x, points[0].x);
				max.x = _hoops_IAAA (max.x, points[1].x);
			}

			if (points[0].y > points[1].y) {
				min.y = _hoops_AHIA (min.y, points[1].y);
				max.y = _hoops_IAAA (max.y, points[0].y);
			}
			else {
				min.y = _hoops_AHIA (min.y, points[0].y);
				max.y = _hoops_IAAA (max.y, points[1].y);
			}

			if (points[0].z > points[1].z) {
				min.z = _hoops_AHIA (min.z, points[1].z);
				max.z = _hoops_IAAA (max.z, points[0].z);
			}
			else {
				min.z = _hoops_AHIA (min.z, points[0].z);
				max.z = _hoops_IAAA (max.z, points[1].z);
			}

			points += 2;
			count -= 2;
		}

		if (count > 0) {
			min.x = _hoops_AHIA (min.x, points->x);
			min.y = _hoops_AHIA (min.y, points->y);
			min.z = _hoops_AHIA (min.z, points->z);
			max.x = _hoops_IAAA (max.x, points->x);
			max.y = _hoops_IAAA (max.y, points->y);
			max.z = _hoops_IAAA (max.z, points->z);
		}
	}

	_hoops_SASC _hoops_SCIS(float const * matrix) const;

	INLINE _hoops_SASC _hoops_SCIS(_hoops_HRPA const & matrix) const {
		if (matrix._hoops_PPGH())
			return _hoops_SASC(*this);
		return _hoops_SCIS(&matrix.elements[0][0]);
	}

	INLINE bool _hoops_HPCIR(_hoops_SASC const & _hoops_RGPGP) const {

		return (_hoops_RGPGP.min.x >= min.x &&
				_hoops_RGPGP.min.y >= min.y &&
				_hoops_RGPGP.min.z >= min.z &&
				_hoops_RGPGP.max.x <= max.x &&
				_hoops_RGPGP.max.y <= max.y &&
				_hoops_RGPGP.max.z <= max.z);
	}

	INLINE bool _hoops_HPCIR(Point const & _hoops_RGPGP) const {

		return (_hoops_RGPGP.x >= min.x &&
				_hoops_RGPGP.y >= min.y &&
				_hoops_RGPGP.z >= min.z &&
				_hoops_RGPGP.x <= max.x &&
				_hoops_RGPGP.y <= max.y &&
				_hoops_RGPGP.z <= max.z);
	}

	INLINE bool _hoops_HPCIR(Point const & _hoops_RGPGP, float _hoops_GSAHR) const {

		return (_hoops_RGPGP.x >= min.x - _hoops_GSAHR &&
				_hoops_RGPGP.y >= min.y - _hoops_GSAHR &&
				_hoops_RGPGP.z >= min.z - _hoops_GSAHR &&
				_hoops_RGPGP.x <= max.x + _hoops_GSAHR &&
				_hoops_RGPGP.y <= max.y + _hoops_GSAHR &&
				_hoops_RGPGP.z <= max.z + _hoops_GSAHR);
	}

	INLINE _hoops_SASC & _hoops_PGPGP(_hoops_SASC const& cuboid) alter {
		min.x = _hoops_IAAA(min.x, cuboid.min.x);
		min.y = _hoops_IAAA(min.y, cuboid.min.y);
		min.z = _hoops_IAAA(min.z, cuboid.min.z);
		max.x = _hoops_AHIA(max.x, cuboid.max.x);
		max.y = _hoops_AHIA(max.y, cuboid.max.y);
		max.z = _hoops_AHIA(max.z, cuboid.max.z);
		return *this;
	}

	INLINE _hoops_SASC & _hoops_AACIR(_hoops_SASC const& cuboid) alter {
		min.x = _hoops_AHIA(min.x, cuboid.min.x);
		min.y = _hoops_AHIA(min.y, cuboid.min.y);
		min.z = _hoops_AHIA(min.z, cuboid.min.z);
		max.x = _hoops_IAAA(max.x, cuboid.max.x);
		max.y = _hoops_IAAA(max.y, cuboid.max.y);
		max.z = _hoops_IAAA(max.z, cuboid.max.z);
		return *this;
	}

	INLINE _hoops_SASC & _hoops_IACHA(float border) alter {
		min.x -= border;
		min.y -= border;
		min.z -= border;
		max.x += border;
		max.y += border;
		max.z += border;
		return *this;
	}

	INLINE _hoops_SASC & _hoops_AGPGP(float border) alter {
		min.x += border;
		min.y += border;
		min.z += border;
		max.x -= border;
		max.y -= border;
		max.z -= border;
		return *this;
	}
};

INLINE _hoops_SASC _hoops_PGPGP(_hoops_SASC const & a, _hoops_SASC const & b) {
	_hoops_SASC temp = a;
	return temp._hoops_PGPGP(b);
}

INLINE _hoops_SASC _hoops_AACIR(_hoops_SASC const & a, _hoops_SASC const & b) {
	_hoops_SASC temp = a;
	return temp._hoops_AACIR(b);
}

INLINE _hoops_SASC _hoops_IACHA(_hoops_SASC const & a, float border) {
	_hoops_SASC temp = a;
	return temp._hoops_IACHA(border);
}

INLINE _hoops_SASC _hoops_AGPGP(_hoops_SASC const & a, float border) {
	_hoops_SASC temp = a;
	return temp._hoops_AGPGP(border);
}


struct _hoops_GPCIR {
	_hoops_APCIR				min, max;

	_hoops_GPCIR () {
		min = _hoops_APCIR(MAX_FLOAT, MAX_FLOAT, MAX_FLOAT);
		max = _hoops_APCIR(-MAX_FLOAT, -MAX_FLOAT, -MAX_FLOAT);
	}

	_hoops_GPCIR (int count, _hoops_APCIR const * points) {
		min = max = *points++;
		--count;
		if (count>0)
			Merge(count, points);
	}

	_hoops_GPCIR (_hoops_APCIR const & _hoops_PRPGP, _hoops_APCIR const & _hoops_HRPGP) {
		min = _hoops_PRPGP;
		max = _hoops_HRPGP;
	}

	_hoops_GPCIR (_hoops_PACIR const & _hoops_HACIR) {
		min = _hoops_APCIR(_hoops_HACIR.left, _hoops_HACIR.bottom, 0);
		max = _hoops_APCIR(_hoops_HACIR.right, _hoops_HACIR.top, 0);
	}

	_hoops_GPCIR (_hoops_GPCIR const & _hoops_HACIR) {
		min = _hoops_HACIR.min;
		max = _hoops_HACIR.max;
	}

	_hoops_GPCIR (_hoops_SASC const & _hoops_HACIR) {
		min = _hoops_HACIR.min;
		max = _hoops_HACIR.max;
	}

	_hoops_GPCIR (_hoops_CAIS const & _hoops_HACIR);

	bool			operator== (_hoops_GPCIR const & cuboid) const	{ return  (min == cuboid.min && max == cuboid.max); }
	bool			operator!= (_hoops_GPCIR const & cuboid) const	{ return  !(*this == cuboid); }

	INLINE _hoops_PPCIR _hoops_RSAIA() const {
		return _hoops_PPCIR(max-min);
	}

	INLINE bool _hoops_RPCIR (_hoops_GPCIR const & cuboid) const {
		return	(max.x >= cuboid.min.x && min.x <= cuboid.max.x ||
			cuboid.max.x >= min.x && cuboid.min.x <= max.x) &&
			(max.y >= cuboid.min.y && min.y <= cuboid.max.y ||
			cuboid.max.y >= min.y && cuboid.min.y <= max.y) &&
			(max.z >= cuboid.min.z && min.z <= cuboid.max.z ||
			cuboid.max.z >= min.z && cuboid.min.z <= max.z);
	}

	bool _hoops_RPCIR (_hoops_APCIR const & start, _hoops_PPCIR const & direction) const;

	INLINE void Merge(_hoops_GPCIR const & cuboid) {
		if (cuboid.min.x < min.x)
			min.x = cuboid.min.x;
		if (cuboid.min.y < min.y)
			min.y = cuboid.min.y;
		if (cuboid.min.z < min.z)
			min.z = cuboid.min.z;
		if (cuboid.max.x > max.x)
			max.x = cuboid.max.x;
		if (cuboid.max.y > max.y)
			max.y = cuboid.max.y;
		if (cuboid.max.z > max.z)
			max.z = cuboid.max.z;
	}

	INLINE void Merge(_hoops_APCIR const & point) {
		min.x = _hoops_AHIA (min.x, point.x);
		min.y = _hoops_AHIA (min.y, point.y);
		min.z = _hoops_AHIA (min.z, point.z);
		max.x = _hoops_IAAA (max.x, point.x);
		max.y = _hoops_IAAA (max.y, point.y);
		max.z = _hoops_IAAA (max.z, point.z);
	}

	INLINE void Merge(int count, _hoops_APCIR const * points) {

		while (count > 1) {
			if (points[0].x > points[1].x) {
				min.x = _hoops_AHIA (min.x, points[1].x);
				max.x = _hoops_IAAA (max.x, points[0].x);
			}
			else {
				min.x = _hoops_AHIA (min.x, points[0].x);
				max.x = _hoops_IAAA (max.x, points[1].x);
			}

			if (points[0].y > points[1].y) {
				min.y = _hoops_AHIA (min.y, points[1].y);
				max.y = _hoops_IAAA (max.y, points[0].y);
			}
			else {
				min.y = _hoops_AHIA (min.y, points[0].y);
				max.y = _hoops_IAAA (max.y, points[1].y);
			}

			if (points[0].z > points[1].z) {
				min.z = _hoops_AHIA (min.z, points[1].z);
				max.z = _hoops_IAAA (max.z, points[0].z);
			}
			else {
				min.z = _hoops_AHIA (min.z, points[0].z);
				max.z = _hoops_IAAA (max.z, points[1].z);
			}

			points += 2;
			count -= 2;
		}

		if (count > 0) {
			min.x = _hoops_AHIA (min.x, points->x);
			min.y = _hoops_AHIA (min.y, points->y);
			min.z = _hoops_AHIA (min.z, points->z);
			max.x = _hoops_IAAA (max.x, points->x);
			max.y = _hoops_IAAA (max.y, points->y);
			max.z = _hoops_IAAA (max.z, points->z);
		}
	}

	INLINE bool _hoops_HPCIR(_hoops_GPCIR const & _hoops_RGPGP) const {

		return (_hoops_RGPGP.min.x >= min.x &&
			_hoops_RGPGP.min.y >= min.y &&
			_hoops_RGPGP.min.z >= min.z &&
			_hoops_RGPGP.max.x <= max.x &&
			_hoops_RGPGP.max.y <= max.y &&
			_hoops_RGPGP.max.z <= max.z);
	}

	INLINE bool _hoops_HPCIR(_hoops_APCIR const & _hoops_RGPGP) const {

		return (_hoops_RGPGP.x >= min.x &&
			_hoops_RGPGP.y >= min.y &&
			_hoops_RGPGP.z >= min.z &&
			_hoops_RGPGP.x <= max.x &&
			_hoops_RGPGP.y <= max.y &&
			_hoops_RGPGP.z <= max.z);
	}

	INLINE bool _hoops_HPCIR(_hoops_APCIR const & _hoops_RGPGP, double _hoops_GSAHR) const {
		return (_hoops_RGPGP.x >= min.x - _hoops_GSAHR &&
			_hoops_RGPGP.y >= min.y - _hoops_GSAHR &&
			_hoops_RGPGP.z >= min.z - _hoops_GSAHR &&
			_hoops_RGPGP.x <= max.x + _hoops_GSAHR &&
			_hoops_RGPGP.y <= max.y + _hoops_GSAHR &&
			_hoops_RGPGP.z <= max.z + _hoops_GSAHR);
	}

	INLINE _hoops_GPCIR & _hoops_PGPGP(_hoops_GPCIR const& cuboid) alter {
		min.x = _hoops_IAAA(min.x, cuboid.min.x);
		min.y = _hoops_IAAA(min.y, cuboid.min.y);
		min.z = _hoops_IAAA(min.z, cuboid.min.z);
		max.x = _hoops_AHIA(max.x, cuboid.max.x);
		max.y = _hoops_AHIA(max.y, cuboid.max.y);
		max.z = _hoops_AHIA(max.z, cuboid.max.z);
		return *this;
	}

	INLINE _hoops_GPCIR & _hoops_AACIR(_hoops_GPCIR const& cuboid) alter {
		min.x = _hoops_AHIA(min.x, cuboid.min.x);
		min.y = _hoops_AHIA(min.y, cuboid.min.y);
		min.z = _hoops_AHIA(min.z, cuboid.min.z);
		max.x = _hoops_IAAA(max.x, cuboid.max.x);
		max.y = _hoops_IAAA(max.y, cuboid.max.y);
		max.z = _hoops_IAAA(max.z, cuboid.max.z);
		return *this;
	}

	INLINE _hoops_GPCIR & _hoops_IACHA(double border) alter {
		min.x -= border;
		min.y -= border;
		min.z -= border;
		max.x += border;
		max.y += border;
		max.z += border;
		return *this;
	}

	INLINE _hoops_GPCIR & _hoops_AGPGP(double border) alter {
		min.x += border;
		min.y += border;
		min.z += border;
		max.x -= border;
		max.y -= border;
		max.z -= border;
		return *this;
	}
};

INLINE _hoops_GPCIR _hoops_PGPGP(_hoops_GPCIR const & a, _hoops_GPCIR const & b) {
	_hoops_GPCIR temp = a;
	return temp._hoops_PGPGP(b);
}

INLINE _hoops_GPCIR _hoops_AACIR(_hoops_GPCIR const & a, _hoops_GPCIR const & b) {
	_hoops_GPCIR temp = a;
	return temp._hoops_AACIR(b);
}

INLINE _hoops_GPCIR _hoops_IACHA(_hoops_GPCIR const & a, double border) {
	_hoops_GPCIR temp = a;
	return temp._hoops_IACHA(border);
}

INLINE _hoops_GPCIR _hoops_AGPGP(_hoops_GPCIR const & a, double border) {
	_hoops_GPCIR temp = a;
	return temp._hoops_AGPGP(border);
}








struct _hoops_CAIS {
	Point				center;
	float				radius;

	_hoops_CAIS ()
		: center(Point(0.0f, 0.0f, 0.0f)), radius(0.0f) {}

	_hoops_CAIS (Point const & _hoops_IRPGP, float _hoops_CRPGP = 0.0f)
		: center(_hoops_IRPGP), radius(_hoops_CRPGP) {}

	_hoops_CAIS (int count, Point const * points)
		: radius(0.0f) {

		_hoops_SASC	cuboid(count, points);
		center = _hoops_AICIR(cuboid.min, cuboid.max);

		while (count-- > 0) {
			float			_hoops_CGSIR, delta;

			_hoops_CGSIR = 0.0f;
			delta = points->x - center.x;
			_hoops_CGSIR += delta * delta;
			delta = points->y - center.y;
			_hoops_CGSIR += delta * delta;
			delta = points->z - center.z;
			_hoops_CGSIR += delta * delta;

			if (_hoops_CGSIR > radius * radius)
				radius = _hoops_SGIHR(_hoops_CGSIR);

			++points;
		}
	}

	_hoops_CAIS (int count, Point const * points, Point const & _hoops_IRPGP)
		: center(_hoops_IRPGP), radius(0.0f) {

		while (count-- > 0) {
			float			_hoops_CGSIR, delta;

			_hoops_CGSIR = 0.0f;
			delta = points->x - center.x;
			_hoops_CGSIR += delta * delta;
			delta = points->y - center.y;
			_hoops_CGSIR += delta * delta;
			delta = points->z - center.z;
			_hoops_CGSIR += delta * delta;

			if (_hoops_CGSIR > radius * radius)
				radius = _hoops_SGIHR(_hoops_CGSIR);

			++points;
		}
	}

	_hoops_CAIS (_hoops_SASC const & cuboid) {
		center = _hoops_AICIR(cuboid.min, cuboid.max);
		radius = 0.0f;
		Merge (cuboid);
	}

	_hoops_CAIS (_hoops_CAIS const & _hoops_HACIR)
		: center(_hoops_HACIR.center), radius(_hoops_HACIR.radius) {}

	bool			operator== (_hoops_CAIS const & sphere) const	{ return  (center == sphere.center && radius == sphere.radius); }
	bool			operator!= (_hoops_CAIS const & sphere) const	{ return  !(*this == sphere); }

	INLINE float _hoops_PGCIR () const {
		return (4.0 / 3.0 * HK_Pi) * radius * radius * radius;
	}

	_hoops_CAIS _hoops_SCIS(float const * matrix) const;

	INLINE _hoops_CAIS _hoops_SCIS(_hoops_HRPA const & matrix) const {
		if (matrix._hoops_PPGH())
			return _hoops_CAIS(*this);
		return _hoops_SCIS(&matrix.elements[0][0]);
	}

	INLINE void Merge(Point const & point) alter {

		Vector		_hoops_CCSAR = point - center;
		float		_hoops_CGSIR = _hoops_CCSAR.length();

		if (_hoops_CGSIR > radius) {
			float t = 0.5f * (_hoops_CGSIR - radius);
			center += t * _hoops_CCSAR._hoops_AAIAR();
			radius += t;
		}
	}

	INLINE void Merge(int count, Point const * points) alter {

		while (count-- > 0) {
			Vector		_hoops_CCSAR = *points - center;
			float		_hoops_CGSIR = _hoops_CCSAR.length();

			if (_hoops_CGSIR > radius) {
				float t = 0.5f * (_hoops_CGSIR - radius);
				center += t * _hoops_CCSAR._hoops_AAIAR();
				radius += t;
			}

			++points;
		}
	}

	INLINE void	Merge (_hoops_SASC const & cuboid) alter {

		Vector	_hoops_CCSAR = cuboid.max - cuboid.min;
		Point	_hoops_GPIS = cuboid.min + 0.5f * _hoops_CCSAR;
		float	_hoops_CRAIR = _hoops_CCSAR.length() * 0.5f;

		_hoops_CCSAR = _hoops_GPIS - center;

		float	_hoops_CGSIR = _hoops_CCSAR.length();

		if (_hoops_CGSIR + _hoops_CRAIR > radius) {
			if (_hoops_CGSIR + radius > _hoops_CRAIR) {
				float	t = 0.5f * (_hoops_CRAIR + _hoops_CGSIR - radius);
				center += t * _hoops_CCSAR._hoops_AAIAR();
				radius += t;
			}
			else {
				center = _hoops_GPIS;
				radius = _hoops_CRAIR;
			}
		}
	}

	INLINE void	Merge (_hoops_CAIS const & sphere) alter {

		Vector	_hoops_CCSAR = sphere.center - center;
		float	_hoops_CGSIR = _hoops_CCSAR.length();

		if (_hoops_CGSIR + sphere.radius > radius) {
			if (_hoops_CGSIR + radius > sphere.radius) {
				float	t = 0.5f * (sphere.radius + _hoops_CGSIR - radius);
				center += t * _hoops_CCSAR._hoops_AAIAR();
				radius += t;
			}
			else {
				center = sphere.center;
				radius = sphere.radius;
			}
		}
	}
};


INLINE void _hoops_SASC::Merge(_hoops_CAIS const & sphere) alter {
	Point	_hoops_SRPGP(sphere.center.x - sphere.radius, sphere.center.y - sphere.radius, sphere.center.z - sphere.radius);
	Merge(1, &_hoops_SRPGP);
	Point	_hoops_GAPGP(sphere.center.x + sphere.radius, sphere.center.y + sphere.radius, sphere.center.z + sphere.radius);
	Merge(1, &_hoops_GAPGP);
};



#define Bounding_EMPTY					(_hoops_RAPGP)0x0001
#define _hoops_CCIIR					(_hoops_RAPGP)0x0002
#define _hoops_CRCAA				(_hoops_RAPGP)0x0004
#define _hoops_AAPGP				(_hoops_RAPGP)0x0008		// _hoops_GHCA _hoops_SHH _hoops_GHGC _hoops_PAPGP
#define _hoops_HGCIR					(_hoops_RAPGP)0x0010
#define _hoops_IGCIR					(_hoops_RAPGP)0x0020
#define Bounding_TRANSFORM_DEPENDENT	(_hoops_RAPGP)0x0040		// _hoops_RII _hoops_HSAR _hoops_HCGR/_hoops_CSCR
#define _hoops_HAPGP			(_hoops_RAPGP)0x0080
#define _hoops_RGCIR		(_hoops_RAPGP)0x0100
#define _hoops_AGCIR		(_hoops_RAPGP)0x0200
#define _hoops_IAPGP				(_hoops_RAPGP)0x0400

class _hoops_CHCIR : public _hoops_ICAGP {
	friend class Bounding;
	public:
		_hoops_SASC		cuboid;
		_hoops_CAIS		sphere;

		float				_hoops_CGCIR;
		mutable short		flags;


		_hoops_CHCIR *	_hoops_ICCIR () const {
			return NEW(_hoops_CHCIR)(*this);
		}

		virtual	bool		Merge (int count, Point const * points) alter;
		bool				Merge (Bounding const & bounding) alter;
		bool				Merge (_hoops_SASC const & cuboid) alter;
		bool				Merge (_hoops_CAIS const & sphere) alter;

		_hoops_CHCIR *	_hoops_SCIS (float const * matrix) const;

		_hoops_CHCIR *	_hoops_SCIS (_hoops_HRPA const & matrix) const {
			if (matrix._hoops_PPGH())
				return NEW(_hoops_CHCIR)(*this);
			return _hoops_SCIS (&matrix.elements[0][0]);
		}

		float				_hoops_PGCIR () const;

	protected:
		_hoops_CHCIR () :  _hoops_CGCIR (1.0f), flags (Bounding_EMPTY) {}
};

class Bounding : public Counted_Pointer<_hoops_CHCIR> {
	typedef		Counted_Pointer<_hoops_CHCIR>		CP;
	public:
		Bounding () : CP () {};	// _hoops_SIGR _hoops_PGGA _hoops_RH _hoops_SPS _hoops_SPR _hoops_HRGR _hoops_SIGR...
		// _hoops_AGCR _hoops_GA'_hoops_RA _hoops_CAPGP _hoops_GAR _hoops_SIGR _hoops_SAPGP _hoops_IS _hoops_RH _hoops_CGRIR _hoops_GPRR _hoops_IIGR _hoops_RH _hoops_GHPP
		Bounding (_hoops_GPPGP const &) : CP () {}
		INLINE Bounding const &	operator= (_hoops_GPPGP const &) alter {
			CP::release();
			CP::_hoops_RPPGP = 0;
			return *this;
		}
#ifdef null
		Bounding (int) : CP () {}
		INLINE Bounding const &	operator= (int) alter {
			CP::release();
			CP::_hoops_RPPGP = 0;
			return *this;
		}
#endif
		INLINE Bounding Copy () const {
			Bounding	temp;
			temp._hoops_RPPGP = CP::_hoops_RPPGP->_hoops_ICCIR();
			temp->retain();
			return temp;
		}
		INLINE Bounding & Modify () alter {
			if (CP::_hoops_RPPGP == null) {
				CP::_hoops_RPPGP = NEW(_hoops_CHCIR)();
				retain();
			}
			else if (CP::_hoops_RPPGP->shared()) {
				_hoops_CHCIR *	temp = CP::_hoops_RPPGP->_hoops_ICCIR();
				release();
				CP::_hoops_RPPGP = temp;
				retain();
			}
			return *this;
		}

		INLINE bool Merge (int count, Point const * points) alter {
			return Modify()->Merge (count, points);
		}

		INLINE bool Merge (_hoops_CAIS const & sphere) alter {
			return Modify()->Merge (sphere);
		}

		INLINE bool Merge (_hoops_SASC const & cuboid) alter {
			return Modify()->Merge (cuboid);
		}

		INLINE bool Merge (Bounding const & bounding) alter {
			if (CP::_hoops_RPPGP == null) {
				*this = bounding;
				return true;
			}
			else
				return Modify()->Merge (bounding);
		}

		INLINE Bounding _hoops_SCIS (float const * _hoops_SSCIR) const {
			Bounding	temp;
			temp._hoops_RPPGP = CP::_hoops_RPPGP->_hoops_SCIS (_hoops_SSCIR);
			temp->retain();
			return temp;
		}

		INLINE Bounding _hoops_SCIS (_hoops_HRPA const & matrix) const {
			Bounding	temp;
			temp._hoops_RPPGP = CP::_hoops_RPPGP->_hoops_SCIS (matrix);
			temp->retain();
			return temp;
		}

		INLINE bool _hoops_HICAR () const {
			return CP::_hoops_RPPGP == null || BIT (CP::_hoops_RPPGP->flags, Bounding_EMPTY);
		}

		INLINE float _hoops_SGCIR () const {
			if (_hoops_HICAR())
				return 0.0f;
			else
				return CP::_hoops_RPPGP->_hoops_CGCIR;
		}

		INLINE float _hoops_PGCIR () const {
			if (_hoops_HICAR())
				return 0.0f;
			else
				return CP::_hoops_RPPGP->_hoops_PGCIR();
		}

		static Bounding Create () {
			Bounding	temp;
			temp._hoops_RPPGP = NEW(_hoops_CHCIR)();
			temp.retain();
			return temp;
		}

		static Bounding Create (int count, Point const * points) {
			Bounding	temp;
			temp._hoops_RPPGP = NEW(_hoops_CHCIR)();
			temp.retain();
			if (count != 0)
				temp.Merge(count, points);
			return temp;
		}

		static Bounding Create (_hoops_SASC const & cuboid) {
			Bounding	temp;
			temp._hoops_RPPGP = NEW(_hoops_CHCIR)();
			temp.retain();
			temp.Merge(cuboid);
			return temp;
		}

		static Bounding Create (_hoops_CAIS const & sphere) {
			Bounding	temp;
			temp._hoops_RPPGP = NEW(_hoops_CHCIR)();
			temp.retain();
			temp.Merge(sphere);
			return temp;
		}

		INLINE _hoops_CHCIR const *	operator-> () const		{ return (_hoops_CHCIR const *)CP::_hoops_RPPGP; }
		INLINE _hoops_CHCIR alter *	operator-> () alter		{ return (_hoops_CHCIR alter *)CP::_hoops_RPPGP; }
};


#define _hoops_APPGP				(Activity)0x00000001
#define _hoops_ICHPA				(Activity)0x00000002
#define _hoops_PPPGP		(Activity)0x00000004
#define _hoops_HPPGP		(Activity)0x00000008
#define _hoops_IPPGP				(Activity)0x00000010
#define _hoops_CPPGP		(Activity)0x00000020
#define _hoops_SPPGP		(Activity)0x00000040
#define _hoops_GHPGP				(Activity)0x00000080
#define _hoops_AASCA			(Activity)0x00000100
#define _hoops_RHPGP						(Activity)0x00000200
#define _hoops_AHPGP				(Activity)0x000003FF

#define _hoops_AHSGA					(Activity)0x00000400
#define _hoops_CASIR						(Activity)0x00000800
#define _hoops_AHGPR				(Activity)0x00001000

#define _hoops_PHPGP		(Activity)0x00002000	// _hoops_IASIR = _hoops_GGSR _hoops_IIGR _hoops_AGR

#define _hoops_HHPGP					(Activity)0x00004000

#define _hoops_SIGPR				(Activity)0x00008000
#define _hoops_IHPGP						(Activity)0x00010000

#define _hoops_CHPGP					(Activity)0x00020000	// _hoops_RGAR _hoops_IGI _hoops_RHSP _hoops_PAAP
#define _hoops_SHPGP				_hoops_CHPGP			// _hoops_RGAR _hoops_IGI _hoops_RHSP _hoops_PRSCA _hoops_CPGGR

#define _hoops_GIPGP				(Activity)0x00040000
#define _hoops_SSCCA			(Activity)0x00080000

#define _hoops_ISCCA		(Activity)0x00100000
#define _hoops_PISSR			(Activity)0x00200000
#define _hoops_RIPGP				(Activity)0x00400000
#define _hoops_RPSIR		(Activity)0x00800000
#define _hoops_HISSR	(Activity)0x01000000
#define _hoops_PSCCA	(Activity)0x02000000
#define _hoops_HSCCA			(Activity)0x04000000
#define _hoops_AIPGP					(Activity)0x08000000
#define _hoops_IISSR		(Activity)0x10000000
#define _hoops_RSCCA	(Activity)0x20000000
#define _hoops_PIPGP			(Activity)0x40000000

#define _hoops_HIPGP		(Activity)0x80000000	// _hoops_RGAR _hoops_IGI _hoops_RHSP _hoops_PAAP

#define _hoops_CSCCA			(_hoops_ISCCA|_hoops_HISSR|_hoops_IISSR)


#define _hoops_CCHPA			_hoops_AHGPR
#define _hoops_HGSCA			(_hoops_CCHPA|_hoops_IPPGP)
#define _hoops_IIPGP		(_hoops_HGSCA|_hoops_GHPGP|_hoops_AASCA)
#define _hoops_IHSSR	(_hoops_IIPGP|_hoops_HPPGP|_hoops_GIPGP/*|_hoops_CIPGP*/)
#define _hoops_GGARA			(_hoops_IHSSR|_hoops_ICHPA)
#define _hoops_GAGSA			(_hoops_IIPGP|_hoops_APPGP)
#define _hoops_SIPGP	(_hoops_IIPGP|_hoops_PPPGP)
#define _hoops_GCPGP	(_hoops_IIPGP|_hoops_PPPGP|_hoops_APPGP)
#define _hoops_RCGSA		(_hoops_GGARA|_hoops_PPPGP|_hoops_APPGP)
#define _hoops_RAGGA			(_hoops_GGARA|_hoops_APPGP|_hoops_RHPGP)
#define _hoops_GSCCA		(_hoops_RCGSA|_hoops_RHPGP)
#define _hoops_HRCCA			(_hoops_IHSSR|_hoops_CPPGP|_hoops_SPPGP)
#define _hoops_CAHRA				(_hoops_CCHPA|_hoops_AHSGA)
#define _hoops_HCHPA					(_hoops_CCHPA|_hoops_CASIR)
#define _hoops_HHSSR		(_hoops_GGARA|_hoops_AHSGA) /* _hoops_SSCHA/ _hoops_RCPGP? */
#define _hoops_PHSSR		(_hoops_GGARA|_hoops_CASIR)  /* _hoops_SSCHA/ _hoops_RCPGP? */
#define _hoops_GPSIR	(_hoops_GGARA|_hoops_SIGPR)
#define _hoops_GCGSA	(_hoops_RCGSA|_hoops_SIGPR)
#define _hoops_AISSR		(_hoops_RAGGA|_hoops_SIGPR)
#define _hoops_ACPGP	(_hoops_GSCCA|_hoops_SIGPR)
#define _hoops_PCPGP		(_hoops_HRCCA|_hoops_SIGPR)
#define _hoops_SCCCA					(_hoops_SIPGP|_hoops_IHPGP)
#define _hoops_HCPGP (_hoops_HGSCA|_hoops_ISCCA)
#define _hoops_ICPGP		(_hoops_HGSCA|_hoops_PISSR)
#define _hoops_CCPGP	(_hoops_HGSCA|_hoops_RPSIR)
#define _hoops_AICSA		(_hoops_HGSCA|_hoops_HISSR)
#define _hoops_SCPGP		(_hoops_HGSCA|_hoops_CSCCA)
#define _hoops_GSPGP		(_hoops_HGSCA|_hoops_HSCCA)

#define _hoops_SASIR(_hoops_RSPGP, _hoops_CAPRA, what) HI_Propagate_Activity (_hoops_RSPGP, (_hoops_SIHIR *)(_hoops_CAPRA), (what))



#define	_hoops_ASPGP				(_hoops_PSPGP)0x00000000
#define	_hoops_HSPGP			(_hoops_PSPGP)0x00000001
#define	_hoops_ISPGP			(_hoops_PSPGP)0x00000002




// _hoops_SRPR _hoops_PHPHA _hoops_HII _hoops_CSPGP _hoops_IS _hoops_PSRAR _hoops_SSPGP _hoops_GGHGP
template <typename _hoops_RGHGP, typename _hoops_AGHGP>
struct _hoops_PGHGP : public CMO {
	public:
		_hoops_RGHGP *				next;
		_hoops_RGHGP **			backlink;
		_hoops_AGHGP *			owner;
		_hoops_GHRIR					_hoops_HIHI;
		Type					type;
		_hoops_RCCCA			_hoops_RRHH;
		// _hoops_ARRS _hoops_SPASR _hoops_CSPGP
		Activity				_hoops_CPGPR;
		Activity				_hoops_SPGPR;
		Key						key;
};



struct _hoops_HPAH : public _hoops_PGHGP<_hoops_HPAH, _hoops_HPAH> {};
struct Attribute : public _hoops_PGHGP<Attribute, _hoops_CRCP> {};
struct Geometry : public _hoops_PGHGP<Geometry, _hoops_CRCP> {
	public:
		long					priority;
		Attribute *				_hoops_IPPGR;
};
struct _hoops_SIHIR : public _hoops_PGHGP<_hoops_SIHIR, _hoops_CRCP> {};


struct _hoops_HISHA : public _hoops_HGHGP<_hoops_HISHA, _hoops_IGHGP> {
	public:
		_hoops_GSPGR					_hoops_PHSHA;
};





/* _hoops_IPCP _hoops_HSPR _hoops_SGI _hoops_CHR _hoops_CGHGP _hoops_PGGA _hoops_SSIA _hoops_CHR _hoops_IGI _hoops_GIPR _hoops_GAR
 * "_hoops_SGHGP" _hoops_SGI _hoops_PPR _hoops_IH _hoops_GRHGP/_hoops_RRHGP. _hoops_HHIGR _hoops_CHH _hoops_SHH _hoops_AGAPR _hoops_IS
 * _hoops_IHSA _hoops_RH _hoops_PGCR _hoops_ARHGP _hoops_PAHAR, _hoops_HIH _hoops_IIH _hoops_CHR _hoops_GRRRA _hoops_IIHP _hoops_CAS
 * "(_hoops_SGHGP & _hoops_HPRC) != 0" _hoops_HRGR _hoops_PSIGA.  _hoops_PRHGP _hoops_HRGR _hoops_HRHGP _hoops_IGI
 * _hoops_GGR _hoops_SGS _hoops_AGIR _hoops_IS _hoops_SAIPR _hoops_RH _hoops_ISPR _hoops_IS _hoops_PCHC _hoops_SIH.
 */

/* _hoops_RH _hoops_HSPR _hoops_CHR _hoops_PGCPR _hoops_GIAA _hoops_GIPR '_hoops_HPRC' _hoops_PPR '_hoops_SGHGP' */
#define T_FACES							(_hoops_ACHR)0x00000001L
#define T_EDGES							(_hoops_ACHR)0x00000002L
#define T_LINES							(_hoops_ACHR)0x00000004L
#define T_MARKERS						(_hoops_ACHR)0x00000008L
#define T_VERTICES						(_hoops_ACHR)0x00000010L
#define T_IMAGES						(_hoops_ACHR)0x00000020L
#define T_TEXT							(_hoops_ACHR)0x00000040L
#define T_STRING_CURSORS				(_hoops_ACHR)0x00000080L
#define T_WINDOWS						(_hoops_ACHR)0x00000100L

#define T_CUTTING_PLANES				(_hoops_ACHR)0x00000200L
#define T_CUT_GEOMETRY					(_hoops_ACHR)0x00000400L

#define	_hoops_IRHGP						(_hoops_ACHR)0x000007FFL

/* _hoops_RH _hoops_HSPR _hoops_CHR _hoops_PGCPR _hoops_GIAA '_hoops_HPRC' */
#define T_INTERIOR_SILHOUETTE_EDGES		(_hoops_ACHR)0x00010000L
#define T_PERIMETER_EDGES				(_hoops_ACHR)0x00020000L
#define _hoops_CRHGP				(_hoops_ACHR)0x00040000L
#define T_MESH_QUAD_EDGES				(_hoops_ACHR)0x00080000L
#define T_HARD_EDGES					(_hoops_ACHR)0x00100000L
#define _hoops_GCSI				(_hoops_ACHR)0x00200000L

#define T_LIGHTS_FOR_FACES				(_hoops_ACHR)0x00400000L
#define T_LIGHTS_FOR_EDGES				(_hoops_ACHR)0x00800000L
#define T_LIGHTS_FOR_MARKERS			(_hoops_ACHR)0x01000000L

#define T_ANY_SHADOW					(_hoops_ACHR)0x02000000L

#define	_hoops_GPA						(_hoops_ACHR)0x04000000L


#define T_GENERIC_EDGES					T_EDGES
#define T_ANY_POLYGON_EDGE				(_hoops_ACHR)(T_GENERIC_EDGES|T_PERIMETER_EDGES|_hoops_CRHGP)
#define T_ANY_GRID_EDGE					T_ANY_POLYGON_EDGE
#define T_ANY_SHELL_EDGE				(_hoops_ACHR)(T_ANY_POLYGON_EDGE|T_HARD_EDGES|T_INTERIOR_SILHOUETTE_EDGES|_hoops_GCSI)
#define T_ANY_MESH_EDGE					(_hoops_ACHR)(T_ANY_SHELL_EDGE|T_MESH_QUAD_EDGES)
#define _hoops_SRHGP				(_hoops_ACHR)(T_GENERIC_EDGES|T_INTERIOR_SILHOUETTE_EDGES|T_MESH_QUAD_EDGES|_hoops_GCSI)
#define _hoops_PSRI		(_hoops_ACHR)(T_EDGES|T_MESH_QUAD_EDGES|T_HARD_EDGES|T_PERIMETER_EDGES|_hoops_CRHGP)
#define T_ANY_EDGE						T_ANY_MESH_EDGE

#define T_ANY_LIGHTS					(_hoops_ACHR)(T_LIGHTS_FOR_FACES|T_LIGHTS_FOR_EDGES|T_LIGHTS_FOR_MARKERS)

#define T_ANY_DRAWABLE_GEOMETRY			(_hoops_ACHR)(T_FACES|T_ANY_EDGE|T_LINES|T_MARKERS|T_VERTICES| \
														T_IMAGES|T_TEXT|T_STRING_CURSORS|T_ANY_LIGHTS)
#define _hoops_GAHGP			T_ANY_DRAWABLE_GEOMETRY
#define _hoops_RAHGP		T_ANY_DRAWABLE_GEOMETRY
#define _hoops_AAHGP					(_hoops_ACHR)(T_ANY_DRAWABLE_GEOMETRY|T_CUTTING_PLANES)
#define _hoops_PAHGP			(_hoops_ACHR)(T_ANY_DRAWABLE_GEOMETRY|T_WINDOWS)
#define _hoops_HAHGP			(_hoops_ACHR)(_hoops_AAHGP|T_WINDOWS)
#define _hoops_IAHGP		(_hoops_ACHR)(_hoops_RAHGP|T_WINDOWS|_hoops_GPA)
#define _hoops_CAHGP			(_hoops_ACHR)(_hoops_AAHGP|T_WINDOWS|T_CUT_GEOMETRY|T_ANY_SHADOW)


/* _hoops_RH _hoops_HSPR _hoops_CHR _hoops_PGCPR _hoops_GIAA '_hoops_SGHGP' */
#define _hoops_SAHGP					(_hoops_ACHR)0x00004000L
#define _hoops_GPHGP						(_hoops_ACHR)0x00008000L
#define _hoops_ASPCR							(_hoops_ACHR)0x00010000L
#define _hoops_HPRRA						(_hoops_ACHR)0x00020000L
#define _hoops_ASRRA		(_hoops_ACHR)0x00040000L
#define _hoops_RPHGP			(_hoops_ACHR)0x00080000L
#define _hoops_APHGP				(_hoops_ACHR)0x00100000L
#define _hoops_PPHGP			(_hoops_ACHR)0x00200000L
#define _hoops_HPHGP				(_hoops_ACHR)0x00400000L
#define _hoops_IPHGP				(_hoops_ACHR)0x00800000L
#define _hoops_CPHGP					(_hoops_ACHR)0x01000000L
#define _hoops_SPHGP						(_hoops_ACHR)0x02000000L
#define _hoops_GHHGP					(_hoops_ACHR)0x04000000L
#define _hoops_AHASA						(_hoops_ACHR)0x08000000L
#define _hoops_PSPCR					(_hoops_ACHR)0x10000000L
#define _hoops_RHHGP						(_hoops_ACHR)0x20000000L
#define _hoops_AHHGP						(_hoops_ACHR)0x40000000L

#define _hoops_HHSAA						(_hoops_ACHR)0x80000000L

/* _hoops_HAR _hoops_GAPR _hoops_PHHGP _hoops_PGI _hoops_PPRRR -- _hoops_HPRC _hoops_SSCP _hoops_IRS _hoops_CIAGR _hoops_HHHGP _hoops_SIH, _hoops_HIH _hoops_SGHGP _hoops_PPR _hoops_GCSP _hoops_GRS _hoops_RRP _hoops_IS _hoops_AGGHA _hoops_HII _hoops_AGCR */
#define	_hoops_IHHGP					(_hoops_ACHR)0x00003800L



/* _hoops_AGCR _hoops_CHR _hoops_GGR _hoops_PAII _hoops_HAII _hoops_CHHGP _hoops_GGR _hoops_HPRC */
#define T_SHADOW_RECEIVING				(_hoops_ACHR)0x00000001L
#define _hoops_SHHGP				(_hoops_ACHR)0x00000002L
#define _hoops_GIHGP				(_hoops_ACHR)0x00000004L
#define _hoops_RIHGP					(_hoops_ACHR)0x00000007L


/* _hoops_IPCP _hoops_HSPR _hoops_CHR _hoops_IGI _hoops_GGR _hoops_AIHGP */

typedef Integer32	_hoops_PIHGP;
#define _hoops_PRSIR					(_hoops_PIHGP)0x00000001
#define _hoops_AASIR			(_hoops_PIHGP)0x00000002
#define _hoops_GGPSA		(_hoops_PIHGP)0x00000004
#define _hoops_SHSIR					(_hoops_PIHGP)0x00000008
#define _hoops_GISIR					(_hoops_PIHGP)0x00000010
#define _hoops_HIHGP			(_hoops_PIHGP)0x00000020
#define _hoops_IIHGP			(_hoops_PIHGP)0x00000040
#define _hoops_CIHGP		(_hoops_PIHGP)0x00000080
#define _hoops_HCGPR				(_hoops_PIHGP)0x00000100
#define _hoops_CGPSA		(_hoops_PIHGP)0x00000200
#define _hoops_SIHGP				(_hoops_PIHGP)0x00000400
#define _hoops_GCHGP			(_hoops_PIHGP)0x00000800
#define _hoops_RCHGP			(_hoops_PIHGP)0x00001000
#define _hoops_ARRPR			(_hoops_PIHGP)0x00002000
#define _hoops_ACHGP					(_hoops_PIHGP)0x00004000
#define _hoops_PCHGP						(_hoops_PIHGP)0x00008000
#define _hoops_PACAA				(_hoops_PIHGP)0x00010000
#define _hoops_GIGSA					(_hoops_PIHGP)0x00020000
#define _hoops_RIGSA			(_hoops_PIHGP)0x00040000
#define _hoops_HCHGP					(_hoops_PIHGP)0x00080000
#define _hoops_ICHGP			(_hoops_PIHGP)0x00100000
#define _hoops_ICGPR				(_hoops_PIHGP)0x00200000
#define _hoops_CCHGP			(_hoops_PIHGP)0x00400000
#define _hoops_SCHGP				(_hoops_PIHGP)0x00800000
#define _hoops_HHSI	(_hoops_PIHGP)0x01000000
#define _hoops_GSHGP					(_hoops_PIHGP)0x02000000
#define _hoops_RSHGP					(_hoops_PIHGP)0x04000000
#define _hoops_ASHGP					(_hoops_PIHGP)0x08000000
#define _hoops_PSHGP					(_hoops_PIHGP)0x10000000
#define _hoops_GIPSA					(_hoops_PIHGP)0x20000000
#define _hoops_HSHGP					(_hoops_PIHGP)0x40000000
#define _hoops_AGPSA						(_hoops_PIHGP)0x80000000
#define _hoops_ISHGP					_hoops_HSHGP // _hoops_CGAPA

#define _hoops_CSHGP					(_hoops_GIGSA | _hoops_RIGSA)


typedef char			_hoops_SSHGP;

#define _hoops_GGIGP		(_hoops_SSHGP)0x01
#define _hoops_RGIGP		(_hoops_SSHGP)0x02
#define _hoops_AGIGP			(_hoops_SSHGP)0x04
#define _hoops_PGIGP		(_hoops_SSHGP)0x08
#define _hoops_HGIGP		(_hoops_SSHGP)0x10
#define _hoops_IGIGP			(_hoops_SSHGP)0x20
#define _hoops_CGIGP		(_hoops_SSHGP)0x40

#define _hoops_SGIGP		(_hoops_RGIGP|_hoops_AGIGP|_hoops_PGIGP|_hoops_HGIGP|_hoops_IGIGP)
#define _hoops_GRIGP	(_hoops_SGIGP|_hoops_GGIGP)



#define _hoops_IHPCA	-1
#define _hoops_AIPCA	-2
#define _hoops_RIPCA	-3
#define _hoops_HIPCA	-4
#define _hoops_ISACA	-5
#define _hoops_SIPCA	-6

struct _hoops_CCPCA {
	int *						_hoops_ASACA;
	int							count;
};


INLINE Integer32	_hoops_RRIGP (Integer32	v) {
	Integer32 c;
#if 0
	v = v - ((v >> 1) & 0x55555555);
	v = (v & 0x33333333) + ((v >>2) & 0x33333333);
	c = ((v + (v >> 4) & 0x0F0F0F0F) * 0x1010101) >> 24;
#else
	c = 0;
	while (v != 0) {
		++c;
		v &= v - 1;
	}
#endif
	return c;
}

struct _hoops_ARIGP : public CMO {
	protected:
		void **			_hoops_AICHR;
		Integer32		size;
		Integer32		_hoops_PRIGP;

		void			_hoops_HRIGP (Integer32 index) {
							void **		_hoops_RRSAA = _hoops_AICHR;
							ALLOC_ARRAY (_hoops_AICHR, size+1, void *);
							if (index > 0)
								_hoops_AIGA (_hoops_RRSAA, index, void *, _hoops_AICHR);
							if (index < size)
								_hoops_AIGA (&_hoops_RRSAA[index], size-index, void *, &_hoops_AICHR[index+1]);
							if (size > 0)
								FREE_ARRAY (_hoops_RRSAA, size, void *);
							++size;
						}

		void			_hoops_IRIGP (Integer32 index) {
							void **		_hoops_RRSAA = _hoops_AICHR;
							if (--size > 0) {
								ALLOC_ARRAY (_hoops_AICHR, size, void *);
								if (index > 0)
									_hoops_AIGA (_hoops_RRSAA, index, void *, _hoops_AICHR);
								if (index < size)
									_hoops_AIGA (&_hoops_RRSAA[index+1], size-index, void *, &_hoops_AICHR[index]);
							}
							else
								_hoops_AICHR = null;
							FREE_ARRAY (_hoops_RRSAA, size+1, void *);
						}

	public:
		_hoops_ARIGP () : _hoops_AICHR (null), size (0), _hoops_PRIGP (0) {}
		~_hoops_ARIGP () {
			if (size > 0)
				FREE_ARRAY (_hoops_AICHR, size, void *);
		}

		INLINE void *	_hoops_AACP (Integer32 id) const {
							Integer32			bit = 1 << id;
							if (!BIT (_hoops_PRIGP, bit))
								return null;
							Integer32			index = _hoops_RRIGP (_hoops_PRIGP & (bit-1));
							return _hoops_AICHR[index];
						}

		void			set (Integer32 id, void * pointer) {
							Integer32			bit = 1 << id;
							Integer32			index = _hoops_RRIGP (_hoops_PRIGP & (bit-1));
							if (pointer != null) {
								if (!BIT (_hoops_PRIGP, bit)) {
									_hoops_HRIGP (index);
									_hoops_PRIGP |= bit;
								}
								_hoops_AICHR[index] = pointer;
							}
							else {
								if (BIT (_hoops_PRIGP, bit)) {
									_hoops_IRIGP (index);
									_hoops_PRIGP &= ~bit;
								}
							}
						}

		bool			_hoops_CRIGP () const { return _hoops_PRIGP == 0; }
};



#define _hoops_IIAGR(x)		(int)((x)-_hoops_AHRIR)			// _hoops_AHHR-_hoops_IIHA _hoops_CIHA _hoops_HII _hoops_IRS _hoops_CPAP _hoops_GIIC
#define _hoops_AGPGR(x)		(1 << _hoops_IIAGR(x))						// _hoops_RSRA _hoops_PISH _hoops_IGRH _hoops_HII _hoops_IRS _hoops_GIIC
#define _hoops_RACP			(_hoops_PHRIR-_hoops_AHRIR+1)	// _hoops_SRIGP _hoops_IIGR _hoops_GAIGP _hoops_CPAP _hoops_GASR _hoops_CIHA

_hoops_AHAGP (_hoops_RACP < 32, _hoops_RAIGP);


struct _hoops_AAIGP : public _hoops_ARIGP {
	public:
		// _hoops_IH _hoops_RHRP, _hoops_ASRC _hoops_RH _hoops_PISH
		int					_hoops_PAIGP () const { return _hoops_PRIGP; }

		// _hoops_IISPR _hoops_GPRR _hoops_IPI
		Geometry *			_hoops_AACP (int id) const { return (Geometry *)_hoops_ARIGP::_hoops_AACP (id); }

		// _hoops_PSCH _hoops_IH _hoops_HCHAR _hoops_HPGR "_hoops_HIGR"
		Geometry *			_hoops_HAIGP () const {
								if (_hoops_AICHR == null)
									return null;
								return (Geometry *)_hoops_AICHR[0];
							}
		Geometry *			_hoops_IAIGP () const {
								if (_hoops_AICHR == null)
									return null;
								return (Geometry *)_hoops_AICHR[size-1];
							}
		INLINE Geometry *	_hoops_CAIGP (int id) const {
								int			bit = 1 << id;
								if (!BIT (_hoops_PRIGP, bit))
									return null;
								int			index = _hoops_RRIGP (_hoops_PRIGP & (bit-1));
								if (++index < size)
									return null;
								return (Geometry *)_hoops_AICHR[index];
							}
		INLINE Geometry *	_hoops_SAIGP (int id) const {
								int			bit = 1 << id;
								if (!BIT (_hoops_PRIGP, bit))
									return null;
								int			index = _hoops_RRIGP (_hoops_PRIGP & (bit-1));
								if (--index < 0)
									return null;
								return (Geometry *)_hoops_AICHR[index];
							}
};


/*
 * _hoops_RAIGR _hoops_RIGR _hoops_IS _hoops_GPIGP _hoops_ISGR _hoops_CHIA _hoops_CPAP _hoops_CSSC _hoops_GGR _hoops_CPAP _hoops_HIGR,
 */

// _hoops_RPIGP _hoops_SGS _hoops_APIGP (_hoops_PAGA: _hoops_PAH'_hoops_RA _hoops_SGH _hoops_AA {} _hoops_HPGP (0) _hoops_GAR _hoops_SGS _hoops_CHH _hoops_RIS _hoops_RH _hoops_RGHP _hoops_APIGP
#define _hoops_CSHI(_hoops_PPIGP, _hoops_HPIGP) { \
	int _hoops_IPIGP = _hoops_HPIGP; \
	if (_hoops_PPIGP != null && _hoops_PPIGP->type == _hoops_IPIGP) { \
		int _hoops_CPIGP = _hoops_IIAGR(_hoops_IPIGP); \
		if (_hoops_PPIGP->next == null) { \
			_hoops_PPIGP = null; \
			break; \
		} \
		if (_hoops_PPIGP->owner == null || _hoops_PPIGP->owner->_hoops_GACP == null || \
			BIT (_hoops_PPIGP->_hoops_RRHH, _hoops_PASIR)) { \
			do if ((_hoops_PPIGP = _hoops_PPIGP->next) == null) \
				break; \
			while (_hoops_PPIGP->type == _hoops_IPIGP); \
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
		} \
		break;\
	} \
}

#define _hoops_PGPGR(_hoops_PPIGP, geom_type) do { \
	_hoops_CSHI(_hoops_PPIGP, geom_type); \
} while (0)





#define _hoops_IGAIR 8
struct _hoops_PGAIR : public _hoops_HPAH {
	Geometry *					data[_hoops_IGAIR];
};


struct Subsegment : public _hoops_PGHGP<Subsegment, _hoops_CRCP> {
	long						priority;
};



struct _hoops_AHAGR;

struct _hoops_SPIGP : public CMO {
	short					_hoops_GHIGP;
	short					_hoops_RHIGP;
	short					_hoops_AHIGP;
};

struct _hoops_PHIGP : public _hoops_ARIGP {
	~_hoops_PHIGP ();

	protected:
		enum {
			_hoops_HHIGP,
			_hoops_IHIGP,
			_hoops_CHIGP,
			_hoops_SHIGP,
			_hoops_GIIGP,
			_hoops_RIIGP
		};

		struct _hoops_AIIGP : public CMO {
			Xref *				_hoops_PIIGP;
		};
		struct _hoops_HIIGP : public CMO {
			Geometry *			geometry;
			Subsegment *		_hoops_RGRPR;
		};
		struct _hoops_IIIGP : public CMO {
			_hoops_PGAIR *			_hoops_HGAIR;
		};


	public:
		void				_hoops_PHASA (_hoops_AAASA * _hoops_PSRGA) {
								set (_hoops_SHIGP, _hoops_PSRGA);
							}
		_hoops_AAASA *		_hoops_RHASA () const {
								return (_hoops_AAASA *)_hoops_AACP (_hoops_SHIGP);
							}

		void				_hoops_ISRIR (Xref * x);	// _hoops_RAS _hoops_CIIGP _hoops_IPPHR
		Xref *				_hoops_SGRPR () const {
								_hoops_AIIGP *	rc = (_hoops_AIIGP *)_hoops_AACP (_hoops_CHIGP);
								if (rc == null)
									return null;
								return rc->_hoops_PIIGP;
							}

		void				_hoops_RSGPR (Geometry * g) {
								_hoops_HIIGP *		dc = (_hoops_HIIGP *)_hoops_AACP (_hoops_IHIGP);
								if (g != null) {
									if (dc == null) {
										dc = NEW(_hoops_HIIGP)();
										set (_hoops_IHIGP, dc);
									}
									dc->geometry = g;
									g->backlink = (Geometry **)&dc->geometry;
								}
								else {
									if (dc->_hoops_RGRPR != null)
										dc->geometry = null;
									else {
										delete dc;
										set (_hoops_IHIGP, null);
									}
								}
							}
		Geometry *			_hoops_SCGPR () const {
								_hoops_HIIGP *		dc = (_hoops_HIIGP *)_hoops_AACP (_hoops_IHIGP);
								if (dc == null)
									return null;
								return dc->geometry;
							}

		void				_hoops_HRRPR (Subsegment * s) {
								_hoops_HIIGP *		dc = (_hoops_HIIGP *)_hoops_AACP (_hoops_IHIGP);
								if (s != null) {
									if (dc == null) {
										dc = NEW(_hoops_HIIGP)();
										set (_hoops_IHIGP, dc);
									}
									dc->_hoops_RGRPR = s;
									s->backlink = (Subsegment **)&dc->_hoops_RGRPR;
								}
								else {
									if (dc->geometry != null)
										dc->_hoops_RGRPR = null;
									else {
										delete dc;
										set (_hoops_IHIGP, null);
									}
								}
							}
		Subsegment *		_hoops_PRRPR () const {
								_hoops_HIIGP *		dc = (_hoops_HIIGP *)_hoops_AACP (_hoops_IHIGP);
								if (dc == null)
									return null;
								return dc->_hoops_RGRPR;
							}

		void				_hoops_GGAIR (_hoops_PGAIR * _hoops_PSAPA) {
								_hoops_IIIGP *			_hoops_SIIGP = (_hoops_IIIGP *)_hoops_AACP (_hoops_RIIGP);
								if (_hoops_PSAPA != null) {
									if (_hoops_SIIGP == null) {
										_hoops_SIIGP = NEW(_hoops_IIIGP)();
										set (_hoops_RIIGP, _hoops_SIIGP);
									}
									_hoops_SIIGP->_hoops_HGAIR = _hoops_PSAPA;
									_hoops_PSAPA->backlink = (_hoops_HPAH **)&_hoops_SIIGP->_hoops_HGAIR;
								}
								else {
									delete _hoops_SIIGP;
									set (_hoops_RIIGP, null);
								}
							}
		_hoops_PGAIR *			_hoops_SSRIR () const {
								_hoops_IIIGP *		_hoops_SIIGP = (_hoops_IIIGP *)_hoops_AACP (_hoops_RIIGP);
								if (_hoops_SIIGP == null)
									return null;
								return _hoops_SIIGP->_hoops_HGAIR;
							}


		_hoops_SPIGP *			_hoops_GCIGP (bool _hoops_HSIPA) {
								_hoops_SPIGP *	_hoops_ICI = (_hoops_SPIGP *)_hoops_AACP (_hoops_HHIGP);
								if (_hoops_HSIPA) {
									if (_hoops_ICI == null) {
										_hoops_ICI = NEW(_hoops_SPIGP)();
										set (_hoops_HHIGP, _hoops_ICI);
									}
									return _hoops_ICI;
								}
								else {
									delete _hoops_ICI;
									set (_hoops_HHIGP, null);
								}
								return null;
							}
		_hoops_SPIGP *			_hoops_RCIGP () const {
								return (_hoops_SPIGP *)_hoops_AACP (_hoops_HHIGP);
							}

		void				_hoops_ACIGP (Integer32 value) {
								set (_hoops_GIIGP, (void *)(POINTER_SIZED_INT)value);
							}
		Integer32			_hoops_PCIGP () const {
								return (Integer32)(POINTER_SIZED_INT)_hoops_AACP (_hoops_GIIGP);
							}
};






#define _hoops_HIRIR		_hoops_HCIGP(1)

struct _hoops_CRCP : public Subsegment {
	Subsegment *				_hoops_RGRPR;
	Attribute *					_hoops_IPPGR;
	_hoops_AHAGR *				_hoops_CSC;
	_hoops_PIHGP					_hoops_PHSI;
	_hoops_ACHR					_hoops_RCGC;
	Bounding					bounding;			// _hoops_CRRPR _hoops_CHAPA
	_hoops_CCAGP					_hoops_RHAGR;			// _hoops_SAPGP _hoops_IS _hoops_IHAH

	// _hoops_GAAP _hoops_ICIGP?
	Geometry *					geometry;
	_hoops_AAIGP *			_hoops_GACP;
	Bounding					_hoops_HSRIR;	// _hoops_IRGH _hoops_CPAP _hoops_RGAR

	_hoops_HCRPR						name;
	_hoops_PSPGP				_hoops_PCGPR;					// _hoops_HAH _hoops_PPCAR _hoops_IH _hoops_ICIGP
	int							_hoops_IGCCA;	// _hoops_HAH _hoops_PPCAR _hoops_IH _hoops_ICIGP
	_hoops_PHIGP *		extended;


	protected:
		void					_hoops_CCIGP () {
									if (extended == null)
										extended = NEW(_hoops_PHIGP)();
								}
		void					_hoops_SCIGP () {
									if (extended->_hoops_CRIGP()) {
										delete extended;
										extended = null;
									}
								}

		// _hoops_IGPI _hoops_IH _hoops_ISIA _hoops_ACAPA
		_hoops_SPIGP *				_hoops_GCIGP (bool _hoops_HSIPA) {
									if (_hoops_HSIPA) {
										_hoops_CCIGP ();
										return extended->_hoops_GCIGP(_hoops_HSIPA);
									}
									else if (extended != null) {
										extended->_hoops_GCIGP(false);
										_hoops_SCIGP ();
									}
									return null;
								}
		_hoops_SPIGP *				_hoops_RCIGP () const {
									if (extended == null)
										return null;
									return extended->_hoops_RCIGP();
								}

	public:
		// _hoops_ACAPA _hoops_IS _hoops_PRCHR
		void				_hoops_ISRIR (Xref * x) {
								if (x != null) {
									_hoops_CCIGP ();
									extended->_hoops_ISRIR(x);
								}
								else if (extended != null) {
									extended->_hoops_ISRIR(null);
									_hoops_SCIGP ();
								}
							}
		Xref *				_hoops_SGRPR () const {
								if (extended == null)
									return null;
								return extended->_hoops_SGRPR();
							}

		// _hoops_ACAPA _hoops_IS _hoops_ICSI _hoops_HIIA _hoops_GASR
		void				_hoops_PHASA (_hoops_AAASA * _hoops_PSRGA) {
								if (_hoops_PSRGA != null) {
									_hoops_CCIGP ();
									extended->_hoops_PHASA(_hoops_PSRGA);
								}
								else {
									extended->_hoops_PHASA(null);
									_hoops_SCIGP ();
								}
							}
		_hoops_AAASA *		_hoops_RHASA () const {
								if (extended == null)
									return null;
								return extended->_hoops_RHASA ();
							}

		// _hoops_ACAPA _hoops_IS _hoops_PGHPR _hoops_CPAP
		void				_hoops_RSGPR (Geometry * g) {
								if (g != null) {
									_hoops_CCIGP ();
									extended->_hoops_RSGPR(g);
								}
								else if (extended != null) {
									extended->_hoops_RSGPR(null);
									_hoops_SCIGP ();
								}
							}
		Geometry *			_hoops_SCGPR () const {
								if (extended == null)
									return null;
								return extended->_hoops_SCGPR();
							}
		// _hoops_ACAPA _hoops_IS _hoops_PGHPR _hoops_CHAPA
		void				_hoops_HRRPR (Subsegment * s) {
								if (s != null) {
									_hoops_CCIGP ();
									extended->_hoops_HRRPR(s);
								}
								else if (extended != null) {
									extended->_hoops_HRRPR(null);
									_hoops_SCIGP ();
								}
							}
		Subsegment *		_hoops_PRRPR () const {
								if (extended == null)
									return null;
								return extended->_hoops_PRRPR();
							}

		// _hoops_ACAPA _hoops_IS _hoops_PRCCA _hoops_CASPR
		void				_hoops_GGAIR (_hoops_PGAIR * _hoops_PSAPA) {
								if (_hoops_PSAPA != null) {
									_hoops_CCIGP ();
									extended->_hoops_GGAIR (_hoops_PSAPA);
								}
								else if (extended != null) {
									extended->_hoops_GGAIR(null);
									_hoops_SCIGP ();
								}
							}
		_hoops_PGAIR *			_hoops_SSRIR () const {
								if (extended == null)
									return null;
								return extended->_hoops_SSRIR();
							}

		// _hoops_ACAPA _hoops_IS _hoops_PAAP _hoops_RGAP (_hoops_RHPP _hoops_SGHC)
		void				_hoops_ACIGP (Integer32 _hoops_RIGRA) {
								_hoops_CCIGP ();
								extended->_hoops_ACIGP (_hoops_RIGRA);
							}
		unsigned Integer32	_hoops_PCIGP () const {
								if (extended == null)
									return 0;
								return extended->_hoops_PCIGP();
							}

		// _hoops_ACAPA _hoops_IS _hoops_ISIA _hoops_IH _hoops_SS, _hoops_HPPA _hoops_GHC, _hoops_PPR _hoops_RGCH
		void				_hoops_GSIGP (int _hoops_SIIGP) {
								if (_hoops_SIIGP != 0) {
									_hoops_SPIGP *	_hoops_ICI = _hoops_GCIGP (true);
									_hoops_ICI->_hoops_GHIGP = _hoops_SIIGP;
								}
								else {
									_hoops_SPIGP *	_hoops_ICI = _hoops_RCIGP ();
									if (_hoops_ICI != null) {
										if (_hoops_ICI->_hoops_RHIGP == 0 &&
											_hoops_ICI->_hoops_AHIGP == 0)
											_hoops_GCIGP (false);
										else
											_hoops_ICI->_hoops_GHIGP = 0;
									}
								}
							}
		int					_hoops_AAGSA () const {
								_hoops_SPIGP *	_hoops_ICI = _hoops_RCIGP ();
								if (_hoops_ICI == null)
									return 0;
								return _hoops_ICI->_hoops_GHIGP;
							}

		void				_hoops_RSIGP (int _hoops_ARCAR) {
								if (_hoops_ARCAR != 0) {
									_hoops_SPIGP *	_hoops_ICI = _hoops_GCIGP (true);
									_hoops_ICI->_hoops_RHIGP = _hoops_ARCAR;
								}
								else {
									_hoops_SPIGP *	_hoops_ICI = _hoops_RCIGP ();
									if (_hoops_ICI != null) {
										if (_hoops_ICI->_hoops_GHIGP == 0 &&
											_hoops_ICI->_hoops_AHIGP == 0)
											_hoops_GCIGP (false);
										else
											_hoops_ICI->_hoops_RHIGP = 0;
									}
								}
							}
		int					_hoops_PAGSA () const {
								_hoops_SPIGP *	_hoops_ICI = _hoops_RCIGP ();
								if (_hoops_ICI == null)
									return 0;
								return _hoops_ICI->_hoops_RHIGP;
							}

		void				_hoops_ASIGP (int sc) {
								if (sc != 0) {
									_hoops_SPIGP *	_hoops_ICI = _hoops_GCIGP (true);
									_hoops_ICI->_hoops_AHIGP = sc;
								}
								else {
									_hoops_SPIGP *	_hoops_ICI = _hoops_RCIGP ();
									if (_hoops_ICI != null) {
										if (_hoops_ICI->_hoops_GHIGP == 0 &&
											_hoops_ICI->_hoops_RHIGP == 0)
											_hoops_GCIGP (false);
										else
											_hoops_ICI->_hoops_AHIGP = 0;
									}
								}
							}
		int					_hoops_SHGSA () const {
								_hoops_SPIGP *	_hoops_ICI = _hoops_RCIGP ();
								if (_hoops_ICI == null)
									return 0;
								return _hoops_ICI->_hoops_AHIGP;
							}
};

// _hoops_AGCR _hoops_PAH _hoops_CGAPA _hoops_GAR _hoops_SSIA _hoops_CHR _hoops_PGIA _hoops_HGIA
#define _hoops_HPAPA			_hoops_HCIGP(1)
#define _hoops_PSIGP	_hoops_HCIGP(1)

struct _hoops_PGRPR : public Subsegment {
								// _hoops_HSPP _hoops_HSIGP _hoops_PPCAR _hoops_ICSHR
	_hoops_CRCP const *				_hoops_IGRPR;
	Xref *						_hoops_GRRPR;
	Xref **						_hoops_SHAIR;
	_hoops_CCPCA					condition;
								// _hoops_RSGR _hoops_HSIGP _hoops_PPCAR _hoops_ICSHR
};



struct Style : public Attribute {
	long						_hoops_ISIGP;		// _hoops_ICHHR _hoops_HCCGR _hoops_RGCGA _hoops_SAPGP _hoops_IS _hoops_PPIHR _hoops_CSIGP
								// _hoops_HSPP _hoops_HSIGP _hoops_PPCAR _hoops_ICSHR
	_hoops_CRCP const *				_hoops_IGRPR;
	Xref *						_hoops_GRRPR;
	Xref **						_hoops_SHAIR;
	_hoops_CCPCA					condition;
								// _hoops_RSGR _hoops_HSIGP _hoops_PPCAR _hoops_ICSHR
	_hoops_HCRPR						_hoops_SGAIR;
	Integer32					_hoops_PCSCA;
};


struct Xref : public _hoops_PGRPR {};


#define _hoops_IIHIR	_hoops_HCIGP(1)

struct _hoops_PHIP : public Geometry {		// _hoops_CRICR _hoops_IS _hoops_CIIGP _hoops_CSSC, _hoops_HIH _hoops_RHAP _hoops_HAR _hoops_PHHR _hoops_GGR _hoops_PSHR _hoops_CPCI
	_hoops_SIHIR const * alter *	_hoops_IHIP;
	_hoops_CCPCA					condition;

	Bounding					bounding;
	int							_hoops_HHIP;
	int							_hoops_RGPGR;
};


INLINE	void	_hoops_PHIGP::_hoops_ISRIR (Xref * x) {
	_hoops_AIIGP *		rc = (_hoops_AIIGP *)_hoops_AACP (_hoops_CHIGP);
	if (x != null) {
		if (rc == null) {
			rc = NEW(_hoops_AIIGP)();
			set (_hoops_CHIGP, rc);
		}
		rc->_hoops_PIIGP = x;
		x->_hoops_SHAIR = (Xref **)&rc->_hoops_PIIGP;
	}
	else {
		delete rc;
		set (_hoops_CHIGP, null);
	}
}





INLINE _hoops_CRCP const * _hoops_SSIGP (Subsegment const * _hoops_GIPIA) {
	if (_hoops_GIPIA != null && _hoops_GIPIA->type == _hoops_AGRPR) {
		_hoops_PGRPR const *		include = (_hoops_PGRPR const *)_hoops_GIPIA;

		return (_hoops_CRCP const *)include->_hoops_IGRPR;
	}
	return (_hoops_CRCP const *)_hoops_GIPIA;
}
INLINE _hoops_CRCP alter * _hoops_SSIGP (Subsegment alter * _hoops_GIPIA) {
	if (_hoops_GIPIA != null && _hoops_GIPIA->type == _hoops_AGRPR) {
		_hoops_PGRPR alter *		include = (_hoops_PGRPR alter *)_hoops_GIPIA;

		return (_hoops_CRCP alter *)include->_hoops_IGRPR;
	}
	return (_hoops_CRCP alter *)_hoops_GIPIA;
}



struct _hoops_GGCGP : public _hoops_RGCGP {
	friend class _hoops_AGCGP<_hoops_GGCGP>;

private:
	HOOPS_API _hoops_GGCGP (Memory_Pool *p);

public:
	_hoops_PGRPR const **	_hoops_PGCGP;
	POINTER_SIZED_INT	key;
	int					count;

	~_hoops_GGCGP();
};

class _hoops_HICS : public _hoops_AGCGP<_hoops_GGCGP> {
	typedef		_hoops_AGCGP<_hoops_GGCGP>		CP;
	public:
		_hoops_HICS () : CP () {};	// _hoops_SIGR _hoops_PGGA _hoops_RH _hoops_SPS _hoops_SPR _hoops_HRGR _hoops_SIGR...
		// _hoops_AGCR _hoops_GA'_hoops_RA _hoops_CAPGP _hoops_GAR _hoops_SIGR _hoops_SAPGP _hoops_IS _hoops_RH _hoops_CGRIR _hoops_GPRR _hoops_IIGR _hoops_RH _hoops_GHPP
		_hoops_HICS (_hoops_GPPGP const &) : CP () {}
		INLINE _hoops_HICS const &	operator= (_hoops_GPPGP const &) alter {
			CP::release();
			CP::_hoops_RPPGP = 0;
			return *this;
		}
#ifdef null
		_hoops_HICS (int) : CP () {}
		INLINE _hoops_HICS const &	operator= (int) alter {
			CP::release();
			CP::_hoops_RPPGP = 0;
			return *this;
		}
#endif
		_hoops_HICS (_hoops_AGCGP<_hoops_GGCGP> const & _hoops_HACIR) : CP (_hoops_HACIR) {};

		void _hoops_IACHA (_hoops_PGRPR const * _hoops_HGCGP, Display_Context const * dc);
};


typedef unsigned Integer32	_hoops_IGCGP;
#define	_hoops_CGCGP						(_hoops_IGCGP)0x00000000
#define	_hoops_AAHH						(_hoops_IGCGP)0x00000001	// _hoops_IHHA & _hoops_CIHA _hoops_CRPR(_hoops_GRI) -- _hoops_RH _hoops_ASGH _hoops_AGIR
#define	_hoops_AIPI						(_hoops_IGCGP)0x00000002
#define	_hoops_PIPI				(_hoops_IGCGP)0x00000004
#define	_hoops_HRRHR				(_hoops_IGCGP)0x00000008
#define	_hoops_RCGHR				(_hoops_IGCGP)0x00000010
#define	_hoops_ICGHR				(_hoops_IGCGP)0x00000020
#define	_hoops_CCGHR			(_hoops_IGCGP)0x00000040
#define	_hoops_HIPI			(_hoops_IGCGP)0x00000080
#define	_hoops_SGCGP				(_hoops_IGCGP)0x00000100
#define	_hoops_GRCGP				(_hoops_IGCGP)0x00000200
#define	_hoops_RRCGP					(_hoops_IGCGP)0x000003FF

#define	_hoops_SHRI					_hoops_SGCGP
#define	_hoops_PCGHR					_hoops_SGCGP
#define	_hoops_RCPI				_hoops_GRCGP		// _hoops_GHC
#define	_hoops_GHII				_hoops_GRCGP



typedef unsigned Integer32	_hoops_ARCGP;
// _hoops_SGI _hoops_IS _hoops_SHH _hoops_GCSS _hoops_GPP _hoops_CRHH->_hoops_CCRC
#define DL_FLAG_INVALID					(_hoops_ARCGP)0xFFFFFFFF
#define DL_LIGHTING						(_hoops_ARCGP)0x00000001
#define DL_FLAT_LIGHTING				(_hoops_ARCGP)0x00000002
#define DL_TEXTURING					(_hoops_ARCGP)0x00000004
#define DL_PATTERN						(_hoops_ARCGP)0x00000008
#define DL_COLOR_INTERPOLATION			(_hoops_ARCGP)0x00000010
#define DL_INDEX_INTERPOLATION			(_hoops_ARCGP)0x00000020
#define DL_FORCE_SMOOTH_SHADE_MODEL		(_hoops_ARCGP)0x00000040 /* _hoops_SGH _hoops_HSIAR _hoops_IGSGR _hoops_SARR _hoops_CGPR _hoops_ASCA */
#define _hoops_IIRC				(_hoops_ARCGP)0x00000080
#define DL_NATURAL_PARAMETERS			(_hoops_ARCGP)0x00000100
#define DL_LOCAL_GRAYSCALE				(_hoops_ARCGP)0x00000200 /* _hoops_HIAH _hoops_PSHA _hoops_PRCGP _hoops_CRGR _hoops_AIRI _hoops_HIGR */
#define _hoops_GAHH				(_hoops_ARCGP)0x00000400 /* _hoops_HAR _hoops_HISS _hoops_IS _hoops_AARPR */
#define DL_TEMPORARY_DATA				(_hoops_ARCGP)0x00000800 /* _hoops_SRSIR _hoops_SIGR _hoops_ARPP _hoops_SGSI */
#define DL_DO_NOT_DEFER					(_hoops_ARCGP)0x00001000
#define DL_3D_TRANSPARENCY				(_hoops_ARCGP)0x00002000
#define DL_DO_NOT_RECOMPILE				(_hoops_ARCGP)0x00004000 /* _hoops_PPARR _hoops_SSCP _hoops_PSP _hoops_HPHR _hoops_PIH.  _hoops_SCH _hoops_HRGR _hoops_IRS _hoops_AIRI _hoops_HIGR _hoops_RGGAR _hoops_RGAR.  _hoops_AA _hoops_HAR _hoops_CAH, _hoops_PSCPR _hoops_PAR _hoops_HRSPR */
#define DL_POLYEDGE_FROM_TRISTRIP		(_hoops_ARCGP)0x00008000
#define DL_LIGHTWEIGHT_DISPLAY_LIST		(_hoops_ARCGP)0x00010000 /* _hoops_AIRI _hoops_HIGR _hoops_HRGR _hoops_IRS _hoops_HRCGP (_hoops_PAR _hoops_RCGRA), _hoops_HAR _hoops_PCCP _hoops_IRCGP _hoops_CRS */
#define DL_INSUFFICIENT_VRAM			(_hoops_ARCGP)0x00020000 /* _hoops_AIRI _hoops_CPCI _hoops_AAPR _hoops_AGSI _hoops_PGGA _hoops_IIGR _hoops_AAGC _hoops_PCSRR */
#define DL_TEXTURE_PREBOUND				(_hoops_ARCGP)0x00040000 /* _hoops_HSGR _hoops_HH _hoops_HGSR */
#define DL_NEGATIVE_3X3					(_hoops_ARCGP)0x00080000 /* _hoops_CCGI _hoops_RGAR: _hoops_RSSI _hoops_AAPR _hoops_CHIAR _hoops_RHIR _hoops_IRS _hoops_HHHR _hoops_CSRA _hoops_RSGA _hoops_HPGR _hoops_AIRI _hoops_HIGR _hoops_PRCR _hoops_GHIR (_hoops_HAS._hoops_IAS. _hoops_RSSP _hoops_AAGIR) */
#define _hoops_CRCGP						(_hoops_ARCGP)0x00100000
#define _hoops_SRCGP						(_hoops_ARCGP)0x00200000
#define	_hoops_GACGP						(_hoops_ARCGP)0x00400000
#define _hoops_CAGI			(_hoops_ARCGP)0x00800000 /* _hoops_AHRI _hoops_CHR _hoops_RHRI _hoops_CRGR _hoops_HSP _hoops_PSHA.  _hoops_RACGP/_hoops_AACGP _hoops_CGH _hoops_SHH _hoops_PACGP _hoops_CCA _hoops_RGR */
#define _hoops_HACGP						(_hoops_ARCGP)0x01000000 */
#define DL_SHADOW_TRISTRIP				(_hoops_ARCGP)0x02000000 /* _hoops_RGRIR _hoops_GRH _hoops_PRCA _hoops_IH _hoops_RH _hoops_IHGP _hoops_RCAR'_hoops_GRI _hoops_CRHH */
#define DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS	(_hoops_ARCGP)0x04000000 /* _hoops_AA _hoops_HAR _hoops_SGHHR _hoops_IS _hoops_ARPR _hoops_CPAP-_hoops_PAPA _hoops_AIRI _hoops_CPCI (_hoops_CAGH-_hoops_PAPA _hoops_HGGC _hoops_IHRI, _hoops_PHRI, _hoops_HCCPR _hoops_IAII _hoops_CHIA)*/
#define DL_SUPPRESS_SEGMENT_DISPLAY_LISTS   (_hoops_ARCGP)0x08000000 /* _hoops_AA _hoops_HAR _hoops_SGHHR _hoops_IS _hoops_ARPR _hoops_CAGH-_hoops_PAPA _hoops_AIRI _hoops_CPCI (_hoops_CPAP-_hoops_PAPA _hoops_HGGC _hoops_IHRI, _hoops_PHRI, _hoops_HCCPR _hoops_IAII _hoops_CHIA)*/
#define DL_COLORS_BY_FINDEX				(_hoops_ARCGP)0x10000000 /* _hoops_RH _hoops_CRHH _hoops_PAR _hoops_ACRI _hoops_SSCP _hoops_PSHA _hoops_HPP _hoops_SIGRA _hoops_HISS */
#define _hoops_GGIA					(_hoops_ARCGP)0x20000000 /* _hoops_SSCP _hoops_PSHA _hoops_HPP _hoops_SIGRA _hoops_PPR _hoops_CSAP _hoops_CPIAR _hoops_CCA _hoops_IACGP (_hoops_HAIR _hoops_CIHA _hoops_GGAR) _hoops_PPP */
#define DL_VCOLORED_TRISTRIP			(_hoops_ARCGP)0x40000000 /* _hoops_SSCP _hoops_GPHA _hoops_PSHA _hoops_HPP _hoops_SIGRA _hoops_PAR _hoops_PIRA _hoops_PPR _hoops_CSAP _hoops_CPIAR _hoops_CCA _hoops_CACGP (_hoops_HAIR _hoops_GGAR) _hoops_PPP */
#define DL_HAS_TRANSPARENCY				(_hoops_ARCGP)0x80000000
// _hoops_SGI _hoops_IS _hoops_SHH _hoops_GCSS _hoops_GPP _hoops_CRHH->_hoops_SCRC
#define _hoops_SARI		(_hoops_ARCGP)0x00000001 /* _hoops_IRS _hoops_HCGI _hoops_HRGR _hoops_IPIH _hoops_IHGS _hoops_CPIAR */
#define _hoops_RAHAR				(_hoops_ARCGP)0x00000002 /* _hoops_HAHAR: _hoops_SCGR _hoops_ACRI _hoops_HRGR _hoops_IRS _hoops_RSRRA _hoops_IRSS */
#define _hoops_GCRI						(_hoops_ARCGP)0x00000004 /* _hoops_HAHAR: _hoops_SCGR _hoops_ACRI _hoops_HRGR _hoops_IRS _hoops_RSRRA _hoops_IRSS */
#define _hoops_HCRC			(_hoops_ARCGP)0x00000008 /* _hoops_HAHAR: _hoops_PIIA _hoops_SACGP */
#define _hoops_ICRC			(_hoops_ARCGP)0x00000010 /* _hoops_HAHAR: _hoops_PIIA _hoops_PSHA */
#define _hoops_PCRC				(_hoops_ARCGP)0x00000020 /* _hoops_HAHAR: _hoops_RSRRA _hoops_CSAP _hoops_PRHI _hoops_GAR _hoops_RAAP _hoops_IGCH */
#define _hoops_IHSI			(_hoops_ARCGP)0x00000040 /* _hoops_RPP _hoops_CPIAR _hoops_CCA "_hoops_CASRR _hoops_RGAR", _hoops_SR _hoops_RRP _hoops_IS _hoops_RARI _hoops_HCR _hoops_GRAA-_hoops_GRRI _hoops_CPAP _hoops_GGR _hoops_RH _hoops_CAGH */
#define _hoops_HPII						(_hoops_ARCGP)0x00000080 /* _hoops_RH _hoops_CARA _hoops_AIS _hoops_IHPHR _hoops_GAR _hoops_IRS _hoops_HSSP, _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGIC _hoops_AHCA _hoops_GGAR _hoops_AAP _hoops_PAR _hoops_GPCGP */
#define _hoops_RPCGP				(_hoops_ARCGP)0x00000100
#define _hoops_APCGP		(_hoops_ARCGP)0x00000200
#define _hoops_APIA				(_hoops_ARCGP)0x00000400 /* _hoops_RH _hoops_CARA _hoops_AIS _hoops_IHPHR _hoops_GAR _hoops_PCCP _hoops_HCPI, _hoops_CGH _hoops_SHH _hoops_CHCC _hoops_GAR _hoops_IRS _hoops_PCPI _hoops_PPR _hoops_PPCGP. */
#define _hoops_HPCGP						(_hoops_ARCGP)0x00000800 /* _hoops_HHSA _hoops_HH _hoops_PCRR */
#define _hoops_IPHS				(_hoops_ARCGP)0x00001000 /* _hoops_AHHA: _hoops_PGSA _hoops_IRS _hoops_PSCHR _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_GRR _hoops_CGGR */
#define _hoops_RCRI						(_hoops_ARCGP)0x00002000 /* _hoops_AHHA: _hoops_SCGR _hoops_ACRI _hoops_HRGR _hoops_PCCP _hoops_IPCGP */
#define _hoops_PGAI					(_hoops_ARCGP)0x00004000 /* _hoops_AHHA: _hoops_CPIAR _hoops_CGPR _hoops_ICPP _hoops_CSAP _hoops_CISI */
#define _hoops_HRRI				(_hoops_ARCGP)0x00008000 /* _hoops_AIRI _hoops_HIGR _hoops_CPIAR _hoops_CCA _hoops_GHCP _hoops_HSH _hoops_GPP _hoops_RH _hoops_GIHA (_hoops_CAGAR _hoops_SGS _hoops_RPP _hoops_AGHC _hoops_AGRP, _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_IRHS _hoops_IS _hoops_SHH _hoops_CPCGP) */
#define DL2_MARKER_POINT_SPRITE			(_hoops_ARCGP)0x00010000 /* */
#define DL2_MARKER_CIRCLE				(_hoops_ARCGP)0x00020000 /* */
#define _hoops_AASI		(_hoops_ARCGP)0x80000000 /* _hoops_IGI _hoops_IS _hoops_PIAAR _hoops_SPCGP (_hoops_PGAP _hoops_CHR _hoops_GGR _hoops_ICRP, _hoops_HIH _hoops_HAR _hoops_HCR, _hoops_GHCGP _hoops_SAHR _hoops_PII _hoops_HCGI'_hoops_GRI */


/* _hoops_SGSS _hoops_PISH _hoops_IS _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_HHH _hoops_SIH _hoops_SGS _hoops_CGH _hoops_HAR _hoops_RGRIR _hoops_AIRI _hoops_HIGR _hoops_RHCGP */
#define _hoops_ACRC  (				\
	~(DL_FORCE_SMOOTH_SHADE_MODEL | 	\
	DL_DO_NOT_RECOMPILE | 			\
	_hoops_GAHH | 			\
	DL_TEMPORARY_DATA | 			\
	DL_INSUFFICIENT_VRAM | 			\
	DL_LIGHTWEIGHT_DISPLAY_LIST |	\
	_hoops_GGIA)					\
	)
#define _hoops_AHCGP ~(_hoops_PCRC)


#define _hoops_SRHH (			\
	DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS |		\
	DL_SUPPRESS_SEGMENT_DISPLAY_LISTS)


#define _hoops_PHCGP		0
#define _hoops_HHCGP			1

class _hoops_AGCI {
public:
	_hoops_GACR *				_hoops_PPAH;
	_hoops_AGCI *	next;
	_hoops_AGCI **	prev;
	_hoops_GGAGR const *				_hoops_GHRI;
	Integer32					_hoops_GPPI;  //_hoops_ICRP _hoops_RPAI _hoops_SGH
	Integer32					time_stamp;			//_hoops_ICRP _hoops_RPAI _hoops_IHCGP
	_hoops_CHCGP *				_hoops_ISCS;
};


struct _hoops_GACR : public _hoops_HGHGP<_hoops_GACR, _hoops_HPAH> {
	_hoops_GGAGR const *					_hoops_GHRI;			/* _hoops_RRRPR */
	_hoops_AGCI *		list;			/* _hoops_HISI */
	_hoops_GACR *					_hoops_GASI;			/* _hoops_HCGI _hoops_PPR _hoops_SPCGP _hoops_RGAR: _hoops_SPCGP _hoops_RSSA _hoops_HPGR _hoops_HCGI, _hoops_PPR _hoops_GPHP _hoops_RPHP */
	unsigned Integer32				action_mask;
	_hoops_GHGI						_hoops_GSAI;	/* _hoops_AAP _hoops_HPGR _hoops_PRCR */
	unsigned int					_hoops_AGRI;		/* _hoops_IHH _hoops_SIHC */
	unsigned int					_hoops_PRRI;		/* _hoops_IHH _hoops_SIHC */
	int								_hoops_GGCI;	/* _hoops_ACAGR, _hoops_RPP _hoops_GII, _hoops_GGR _hoops_RH _hoops_SIHPA (_hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH _hoops_CIHPA _hoops_SCH _hoops_GGSR _hoops_RPP _hoops_SCH _hoops_SAGGR _hoops_HGGPR) */
};


struct _hoops_SHCGP :  public _hoops_RGCGP {
	friend class _hoops_AGCGP<_hoops_SHCGP>;

	_hoops_SHCGP(Memory_Pool * memory_pool) : _hoops_RGCGP (memory_pool) {}

	~_hoops_SHCGP() {

		_hoops_GACR *				dl;

		while ((dl = _hoops_GAHA) != null) {
			_hoops_GAHA = dl->next;
			_hoops_HPRH(dl);
		}

		while ((dl = _hoops_HHICA) != null) {
			_hoops_HHICA = dl->next;
			_hoops_HPRH(dl);
		}

		while ((dl = _hoops_IHAGR) != null) {
			_hoops_IHAGR = dl->next;
			_hoops_HPRH(dl);
		}
	}

	_hoops_GACR *			_hoops_GAHA;
	_hoops_GACR *			_hoops_HHICA;
	_hoops_GACR *			_hoops_IHAGR;
};

typedef _hoops_AGCGP<_hoops_SHCGP> _hoops_GPAGR;


struct _hoops_GICGP {
	_hoops_GACR alter *dl; //_hoops_GRAA-_hoops_RICGP
	float priority;
	int _hoops_GPGC;
};



struct _hoops_RHPSA : public CMO {
	_hoops_CRCP *				_hoops_IHPSA;
	Integer32				_hoops_PHPSA;
};


typedef VHash<POINTER_SIZED_INT, _hoops_AHAGR *> _hoops_AICGP;

struct _hoops_AHAGR : public _hoops_ARIGP {
	private:
		enum {
			_hoops_PICGP,
			_hoops_HICGP,
			_hoops_IICGP,
			_hoops_CICGP,
			_hoops_SICGP,
			_hoops_GCCGP,
			_hoops_RCCGP,
			_hoops_ACCGP,
			_hoops_PCCGP,
			_hoops_HCCGP,
			_hoops_ICCGP,
			_hoops_CCCGP
		};

		struct _hoops_SCCGP : public CMO {
			_hoops_PGRPR *				_hoops_GSCGP;
		};

	public:
		_hoops_AHAGR *		next;
		_hoops_CRCP const *		segment;
		_hoops_HICS		path;
		_hoops_GPAGR	_hoops_RSCGP;

		Net_Rendition		_hoops_APHGA;		// _hoops_HAR _hoops_IRS _hoops_PICAA _hoops_CRS
		_hoops_PSPGP		_hoops_PCGPR;			// _hoops_HAH _hoops_PPCAR _hoops_IS _hoops_IPPR _hoops_SGGR

		//_hoops_ASCGP _hoops_PSCGP ();
		HOOPS_API _hoops_AHAGR (_hoops_CRCP const * s, _hoops_HICS const & p);
		HOOPS_API ~_hoops_AHAGR ();

		bool						_hoops_CRIGP () const { return _hoops_ARIGP::_hoops_CRIGP() && _hoops_APHGA == null; }

		void						_hoops_HSCGP (_hoops_HCSIR * _hoops_ICSIR) { set (_hoops_SICGP, _hoops_ICSIR); }
		INLINE _hoops_HCSIR *	_hoops_PSSIR () const { return (_hoops_HCSIR *)_hoops_AACP (_hoops_SICGP); }

		void						_hoops_HHPSA (_hoops_RHPSA * _hoops_HSPIR) { set (_hoops_IICGP, _hoops_HSPIR); }
		INLINE _hoops_RHPSA *		_hoops_AHPSA () const { return (_hoops_RHPSA *)_hoops_AACP (_hoops_IICGP); }

		void						_hoops_ISCGP (_hoops_CPSS * _hoops_SIIS) { set (_hoops_GCCGP, _hoops_SIIS); }
		INLINE _hoops_CPSS *		_hoops_CSCGP () const { return (_hoops_CPSS *)_hoops_AACP (_hoops_GCCGP); }

		void						_hoops_SSCGP (_hoops_GSAR * _hoops_SSGCR) { set (_hoops_RCCGP, _hoops_SSGCR); }
		INLINE _hoops_GSAR *			_hoops_GGSGP () const { return (_hoops_GSAR *)_hoops_AACP (_hoops_RCCGP); }

		void						_hoops_RGSGP (_hoops_PHSGA * _hoops_HSPIR) { set (_hoops_ACCGP, _hoops_HSPIR); }
		INLINE _hoops_PHSGA *	_hoops_GHSGA () const { return (_hoops_PHSGA *)_hoops_AACP (_hoops_ACCGP); }

		void						_hoops_AGSGP (_hoops_PGSGP * _hoops_HGSGP) { set (_hoops_PCCGP, _hoops_HGSGP); }
		INLINE _hoops_PGSGP *		_hoops_IGSGP () const { return (_hoops_PGSGP *)_hoops_AACP (_hoops_PCCGP); }

		void						_hoops_CGSGP (_hoops_SGSGP * hl) { set (_hoops_HCCGP, hl); }
		INLINE _hoops_SGSGP *			_hoops_GRSGP () const { return (_hoops_SGSGP *)_hoops_AACP (_hoops_HCCGP); }

		void						_hoops_RRSGP (_hoops_HRPA * _hoops_HSGA) { set (_hoops_HICGP, _hoops_HSGA); }
		INLINE _hoops_HRPA *		_hoops_ARSGP () const { return (_hoops_HRPA *)_hoops_AACP (_hoops_HICGP); }

		void						_hoops_PRSGP (_hoops_AICGP * _hoops_HRSGP) { set (_hoops_PICGP, _hoops_HRSGP); }
		INLINE _hoops_AICGP *		_hoops_IRSGP () const { return (_hoops_AICGP *)_hoops_AACP (_hoops_PICGP); }

		void						_hoops_CRSGP (_hoops_PIHGP f) { set (_hoops_ICCGP, (void *)(POINTER_SIZED_INT)f); }
		INLINE _hoops_PIHGP			_hoops_SRSGP () const { return (_hoops_PIHGP)(POINTER_SIZED_INT)_hoops_AACP (_hoops_ICCGP); }

		void						_hoops_GAPSA (_hoops_CRPSA * _hoops_GASGP) { set (_hoops_CCCGP, _hoops_GASGP); }
		INLINE _hoops_CRPSA *_hoops_SRPSA () const { return (_hoops_CRPSA *)_hoops_AACP (_hoops_CCCGP); }


		void	_hoops_RASGP (_hoops_PGRPR * _hoops_RRCI) {
			_hoops_SCCGP * sc = (_hoops_SCCGP *)_hoops_AACP (_hoops_CICGP);

			if (_hoops_RRCI != null) {
				if (sc == null) {
					sc = NEW(_hoops_SCCGP)();
					set (_hoops_CICGP, sc);
				}
				sc->_hoops_GSCGP = _hoops_RRCI;
				_hoops_RRCI->backlink = (Subsegment **)&sc->_hoops_GSCGP;
			}
			else {
				delete sc;
				set (_hoops_CICGP, null);
			}
		}
		INLINE _hoops_PGRPR *	_hoops_CHICA () const {
			_hoops_SCCGP * sc = (_hoops_SCCGP *)_hoops_AACP (_hoops_CICGP);

			if (sc == null)
				return null;
			return sc->_hoops_GSCGP;
		}

		void	_hoops_HHAGR (_hoops_GPAGR const & _hoops_AASGP) {
			_hoops_RSCGP = _hoops_AASGP;
		}
		INLINE _hoops_GPAGR const &	_hoops_PHAGR () const {
			return _hoops_RSCGP;
		}
};








// _hoops_PASGP _hoops_SPSRA _hoops_GRS _hoops_SGH _hoops_RH _hoops_HASGP _hoops_IGRH _hoops_IIGR _hoops_IRS _hoops_SIA _hoops_CIHA _hoops_IS _hoops_ASH "_hoops_PGCPR"
#define _hoops_RIRIR	(int)((unsigned int)1 << (int)(8 * sizeof (int) - 1))



struct Line : public Geometry {
	Point						points[2];
};


#define _hoops_HIHCA			_hoops_HCIGP(1)
#define _hoops_PCPIR	_hoops_HCIGP(2)
#define _hoops_HCPIR		_hoops_HCIGP(3)
#define _hoops_IHHCA	_hoops_HCIGP(4)

struct Polyline : public Geometry {
	Point *						points;
	Vector *					orientation;
	int							count,
								allocated;
};

struct _hoops_SHRIR : public Geometry {
	Point *						points;
	int *						mapping;
	int							count,
								allocated;
};

#define _hoops_ARHH	   _hoops_HCIGP(1)
#define _hoops_IASGP		   _hoops_HCIGP(2)

struct Polygon : public Geometry {
	Point *						points;
	int							count,
								allocated;

	_hoops_ARPA						plane;
};

struct _hoops_PRHIR : public Geometry {
	Point *						points;
	int							count, allocated;
	int *						lengths;
	int							_hoops_CASGP, _hoops_IRHIR;

	_hoops_ARPA						plane;
};

struct _hoops_HHPIR : public Geometry {
	_hoops_ARPA *						planes;
	int							count;
};

/* _hoops_GIGHR: _hoops_HCR _hoops_PRHC & _hoops_HCPI _hoops_HCCGR _hoops_CHR _hoops_AAIHR _hoops_IS _hoops_HSSRR _hoops_HCR _hoops_PPCAR
 * _hoops_HSH _hoops_CRGC _hoops_RAS _hoops_RH _hoops_RGSPR.	 _hoops_GPGP _hoops_PIHRA, _hoops_HCR _hoops_PPCAR _hoops_PGIS
 * _hoops_GRPAR _hoops_PSCR _hoops_PSSP _hoops_GRR _hoops_RII.
 * _hoops_SASGP & _hoops_GPSGP _hoops_CHR _hoops_SAHR _hoops_GRH _hoops_ARAR _hoops_IIGR _hoops_RPSGP
 * _hoops_PGAP _hoops_PPIP _hoops_PCCP _hoops_IHH _hoops_PPSR _hoops_PAR _hoops_PGCR, _hoops_PPR _hoops_CHR _hoops_PIISR _hoops_RIIA _hoops_IIGR _hoops_RRIC
 */

/* _hoops_RHRIR: _hoops_APSGP _hoops_PPPPR'_hoops_RA _hoops_SIHRR _hoops_CRGR _hoops_RH _hoops_HSGP _hoops_IIGR _hoops_PPSGP _hoops_RPP
 * _hoops_IRRC (_hoops_PRHC->_hoops_CPGC, _hoops_HPSGP) */
struct _hoops_GSPI : public Geometry {
	Point						center;			/* _hoops_PPCAR _hoops_IS _hoops_HCR */
	_hoops_ARPA						plane;
	Vector						_hoops_GGHI,
								_hoops_RGHI;
};
struct _hoops_GHHI : public _hoops_GSPI {
	float						arc_start,		/* _hoops_PPCAR _hoops_IS _hoops_RRRC */
								_hoops_PHHI;
};


struct _hoops_PHPIR : public _hoops_GSPI {
	float						radius;			/* _hoops_IRGH */
	Point						start,
								_hoops_GGSSR,
								end;
};

struct Ellipse : public _hoops_GSPI {
	Point						major,			/* _hoops_IRGH */
								minor;
};

struct Circular_Arc : public _hoops_GHHI {
	float						radius;			/* _hoops_IRGH */
	Point						start,
								_hoops_GGSSR,
								end;
};

struct Elliptical_Arc : public _hoops_GHHI {
	Point						major,			/* _hoops_IRGH */
								minor;
};



#define _hoops_HGGGA		_hoops_HCIGP(1)
#define _hoops_SHHI		_hoops_HCIGP(2)
#define _hoops_RGGGA		_hoops_HCIGP(3)

struct _hoops_AIHI : public Geometry {
	struct {
		float	x, y;
	}							center;
	float						radius;
};

struct Circular_Arc_Lite : public Geometry {
	struct {
		float	x, y;
	}							center;
	float						radius;
	float						arc_start,
								_hoops_PHHI;
};


/* _hoops_RPP _hoops_RGR _hoops_HRPR _hoops_HRGR _hoops_SIGR, _hoops_SCH _hoops_CGH _hoops_SHH _hoops_PSPP _hoops_GAR _hoops_IRS _hoops_IPSGP
 * _hoops_RIIA, _hoops_GGR _hoops_AGIR _hoops_SR _hoops_RRP _hoops_IS _hoops_IHCGP _hoops_SCH _hoops_GGR _hoops_HGHC _hoops_SPHR. */
struct _hoops_SSSSR : public Geometry {
	Point			points[3];
};


#define _hoops_CHIAA _hoops_HCIGP(1)


struct _hoops_PIRGR : public Geometry {
	int							degree;
	int							control_point_count;
	Point *						control_points;
	float *						weights;/* _hoops_SPCC _hoops_HRGR _hoops_PPCAR._hoops_CPSGP */
	float *						knots;	/* _hoops_SPCC _hoops_HRGR _hoops_PPCAR._hoops_CPSGP + _hoops_PPCAR._hoops_CPSH + 1 */
	float						start_u, end_u;
	/* _hoops_SPSGP _hoops_PCHC _hoops_GCAC _hoops_AAP, _hoops_SR _hoops_PGSA _hoops_IRS _hoops_GHSGP _hoops_ISII _hoops_GGR _hoops_HGHC _hoops_IIGR _hoops_RH _hoops_AGIS. */
	struct {
		Point *						points;
		int							count, allocated;
	}							polyline;
};

#define _hoops_ASCSA		0x00
#define _hoops_IHHIA		0x01
#define _hoops_SHHIA		0x02
#define _hoops_PSCSA		0x03
#define _hoops_PPSSA		0x03
#define _hoops_GASSA			0x04
/* _hoops_RHSGP _hoops_IH _hoops_RSGR _hoops_AHSGP _hoops_GPP _hoops_HAHAR */
#define _hoops_RSICA	0x10
#define _hoops_ASICA	0x20
#define _hoops_PHSGP	0x30

struct _hoops_SSPIR {
	Vector					axis[2];
};

struct Cylinder : public Geometry {
	Point						axis[2];
	float						radius;
	int							flags;
	_hoops_SSPIR					_hoops_CSPIR;
};

typedef unsigned char _hoops_CGHIR;
#define _hoops_SHRRA	 (_hoops_CGHIR)0x01
#define _hoops_IHRRA	 (_hoops_CGHIR)0x02
#define _hoops_GPPRA			 (_hoops_CGHIR)0x03
#define _hoops_GIRRA	 (_hoops_CGHIR)0x04
#define _hoops_CHRRA	 (_hoops_CGHIR)0x08
#define _hoops_RPPRA			 (_hoops_CGHIR)0x0C
#define _hoops_HHSGP	 (_hoops_CGHIR)0x05
#define _hoops_IHSGP (_hoops_CGHIR)0x0A
#define _hoops_CHSGP			 (_hoops_CGHIR)0x0F

struct _hoops_AGHIR {
	/* _hoops_PGII _hoops_SIRGR _hoops_IIGR _hoops_IGIR == _hoops_RSHS */
	_hoops_CGHIR *		flags;
	RGB *					fcolors;
	RGB *					ecolors;
	_hoops_ACGHR *		_hoops_IGHIR;
	_hoops_ACGHR *		_hoops_HGHIR;
	int						_hoops_RCRHR;
	int						_hoops_SIRHR;
	int						_hoops_SCHPR;
	int						_hoops_CCHPR;
};

struct PolyCylinder : public Geometry {
	_hoops_CCAGP					_hoops_RHAGR;	// _hoops_SAPGP _hoops_IS _hoops_AIRI _hoops_CPCI

	Point *						points;
	float *						radii;
	_hoops_SSPIR *				_hoops_CSPIR;
	float *						_hoops_GGHIR;
	_hoops_AGHIR	*	_hoops_RGHIR;
	_hoops_GACR *				_hoops_SGHIR;
	_hoops_GACR *				_hoops_GRHIR;
	int							point_count;
	int							_hoops_ISPIR;
	int							flags;
	Vector						_hoops_ACCSA[2];
	float						_hoops_PCCSA;
	int							_hoops_SHSGP;
	Bounding					bounding;
};



struct Sphere : public Geometry {
	_hoops_CAIS				data;
	Vector *					_hoops_CSPIR;	 /* _hoops_RPP _hoops_GRAA-_hoops_IRAP, _hoops_PSPP _hoops_GAR _hoops_CRPR _hoops_IIGR 3 _hoops_PSPAR */
};

#define _hoops_IHPIR		_hoops_HCIGP(1)

struct Marker : public Geometry {
	Point						_hoops_CSAI;
	Vector *					orientation;
};

struct _hoops_GRPGR : public Geometry {
	Point *						points;
	int *						mapping;
	int							count,
								allocated;
};

typedef short	_hoops_GISGP;
#	define		_hoops_RISGP		(_hoops_GISGP)0x0001
#	define		_hoops_AISGP				(_hoops_GISGP)0x0002 /* _hoops_ARGPR _hoops_IS _hoops_GISR _hoops_SS _hoops_RGAR */
#	define		_hoops_PISGP				(_hoops_GISGP)0x0004 /* _hoops_ARGPR _hoops_IS _hoops_GISR _hoops_SS _hoops_RGAR */
#	define		_hoops_HISGP		(_hoops_GISGP)0x0008 /* _hoops_ARGPR _hoops_IS _hoops_GISR _hoops_SS _hoops_RGAR */
#	define		_hoops_IISGP			(_hoops_GISGP)0x0010 /* _hoops_ARGPR _hoops_IS _hoops_CCAC _hoops_SS _hoops_RGAR */
#	define		_hoops_CISGP				(_hoops_GISGP)0x0020 /* _hoops_ARGPR _hoops_IS _hoops_CCAC _hoops_SS _hoops_RGAR */
#	define		_hoops_SISGP					(_hoops_GISGP)0x0040 /* _hoops_ARGPR _hoops_IS _hoops_CCAC _hoops_SS _hoops_RGAR */
#	define		_hoops_GCSGP					(_hoops_GISGP)0x0080 /* _hoops_ARGPR _hoops_IS _hoops_CCAC _hoops_SS _hoops_RGAR */

typedef char	_hoops_RCSGP;
#	define		_hoops_ACSGP	(_hoops_RCSGP)0
#	define		_hoops_PCSGP			(_hoops_RCSGP)1
#	define		_hoops_HCSGP		(_hoops_RCSGP)2
#	define		_hoops_ICSGP		(_hoops_RCSGP)3


struct Light : public Geometry {
#define _hoops_H			(Type)0
#define _hoops_C				(Type)1
#define _hoops_I				(Type)2
#define _hoops_S				(Type)3
	Type						_hoops_PRR;
	_hoops_GISGP					flags;
	Integer32					time_stamp;
};

struct _hoops_HIPIR : public Light {
	Vector						original;
	Vector						direction;
};

struct _hoops_AIPIR : public Light {
	Point						position;
};

struct _hoops_PIPIR : public Light {
	Point						position;
	Point						target;
	float						_hoops_HCSR,
								_hoops_ACSR;
	float						_hoops_CCSGP;
	_hoops_RCSGP		_hoops_SCSGP,
								_hoops_GSSGP;

	float						_hoops_RSSGP,
								_hoops_ASSGP;
};

struct _hoops_PSSGP {
	Point					position;
	Point					target;
	float					_hoops_ACSR;
	float					_hoops_HCSR;
	float					_hoops_CCSGP;
	_hoops_GISGP				flags;
	_hoops_RCSGP	_hoops_GSSGP;
	_hoops_RCSGP	_hoops_SCSGP;

	float					_hoops_ASSGP;
	float					_hoops_RSSGP;

	Light *					light;
	int						_hoops_IGSSR;
};

struct _hoops_SHPIR : public Light {
	int							count;
	Point *						points;
	_hoops_GISGP					_hoops_HSSGP;
};



struct _hoops_RHPGR : public Geometry {
	_hoops_ACHR					which;
};


struct _hoops_PIGPR : public Geometry {
	int							row,
								column;
};

struct _hoops_IGPIR {
	_hoops_IGPIR *				next;

	/* (_hoops_PHIGR _hoops_HRCSR _hoops_RSIRR _hoops_HSH (_hoops_ISSGP) _hoops_CHR _hoops_PAPR _hoops_GGR _hoops_IRISR._hoops_GGHR, _hoops_IH
	 *	_hoops_RHPP _hoops_GSGAR) */
	_hoops_CSSGP		_hoops_SSSGP;
	_hoops_HCRPR					specified;
};

struct _hoops_AIHIR {
	int						count;
	Point					points[4];		/* 2, 3, _hoops_PAR 4 */
#define _hoops_GGGRP		0x0001	/* _hoops_SHIR _hoops_CARA */
#define _hoops_RGGRP	0x0002	/* _hoops_SHIR _hoops_IPPSR */
#define _hoops_AGGRP		0x0004	/* _hoops_SHIR _hoops_RHHSR _hoops_HAGA */

#define _hoops_PGGRP		0x0000
#define _hoops_HGGRP		0x0010
#define _hoops_IGGRP			0x0020
#define _hoops_CGGRP	0x0030	/* _hoops_CRSRR & _hoops_PISH */

#define	_hoops_SGGRP		0x0040
#define	_hoops_GRGRP		0x0080
#define	_hoops_RRGRP		0x00C0
	int						options;

#define _hoops_ARGRP		0
#define _hoops_PRGRP		1
#define _hoops_HRGRP		2
	unsigned char			_hoops_IRGRP;
	unsigned char			_hoops_CRGRP;
};


typedef Integer32 _hoops_SRGRP;

#define _hoops_GAGRP					(_hoops_SRGRP)0x00000001
#define _hoops_RAGRP					(_hoops_SRGRP)0x00000002
#define _hoops_AAGRP		(_hoops_SRGRP)0x00000004
#define _hoops_PAGRP				(_hoops_SRGRP)0x00000008
#define _hoops_HAGRP			(_hoops_SRGRP)0x00000010
#define _hoops_IAGRP				(_hoops_SRGRP)0x00000020
#define _hoops_CAGRP			(_hoops_SRGRP)0x00000040
#define _hoops_SAGRP				(_hoops_SRGRP)0x00000080
#define _hoops_GPGRP		(_hoops_SRGRP)0x00000100
#define _hoops_RPGRP				(_hoops_SRGRP)0x00000200
#define _hoops_APGRP	(_hoops_SRGRP)0x00000400

struct _hoops_HIHIR {
	_hoops_IGPIR *				_hoops_HGPIR;

	RGB						color;
	float					size;
	float					_hoops_PPGRP;
	float					_hoops_HPGRP;
	float					_hoops_IPGRP;
	float					rotation;
	float					width_scale;

	_hoops_SRGRP		_hoops_HAICA, _hoops_CPGRP;

	_hoops_SPGRP			_hoops_GHGRP;
	_hoops_SPGRP			_hoops_RHGRP;
	_hoops_SPGRP			_hoops_AHGRP;
};

struct _hoops_HACC : public Geometry {
	Point						_hoops_CSAI;
	int							count;
	int							_hoops_PICHR;
	Karacter *					karacters;
	_hoops_HIHIR *				_hoops_PIHIR;
	int							_hoops_PHGRP;
	int *						_hoops_ICI;
	Karacter **					_hoops_RIHIR;

	_hoops_PIGPR *				_hoops_AAPGR;
	_hoops_AIHIR *				region;
	Bounding					bounding;
	unsigned Integer32			_hoops_HHGRP;

	_hoops_IHGRP				encoding;
};


/* _hoops_RHRIR: _hoops_PIS _hoops_CRPR _hoops_GGR _hoops_CHGRP */
#	define		_hoops_SHGRP (_hoops_GIGRP)0
#	define		GSU_ORU			(_hoops_GIGRP)1
#	define		GSU_SRU			(_hoops_GIGRP)2
#	define		GSU_WRU			(_hoops_GIGRP)3
#	define		GSU_PIXELS		(_hoops_GIGRP)4
#	define		GSU_POINTS		(_hoops_GIGRP)5
#	define		GSU_PERCENT		(_hoops_GIGRP)6
#	define		GSU_SCALE		(_hoops_GIGRP)7
#	define		_hoops_SPSC		(_hoops_GIGRP)8
/* _hoops_RPP _hoops_RRI _hoops_CHR _hoops_RRAI _hoops_IS _hoops_RGR _hoops_HIGR, _hoops_CHGRP _hoops_GRS _hoops_RRP _hoops_RIGRP */

struct _hoops_HCAIR {
	float					value;
	_hoops_GIGRP		_hoops_HHP;
};







#define _hoops_CHRH		0x0001			// _hoops_GHAA _hoops_GII _hoops_CHIA _hoops_AAP
#define _hoops_AIGRP		0x0002			// _hoops_CSRA & _hoops_PHCH _hoops_HSH
#define _hoops_PIGRP		0x0004			// _hoops_PGSR _hoops_HAIR
#define _hoops_HIGRP		0x0008			// _hoops_PGSR _hoops_HAIR

// _hoops_PIP _hoops_SGS _hoops_IIGRP _hoops_IGRH _hoops_HRGR _hoops_IGI _hoops_GGR _hoops_GRRRA _hoops_IIGR _hoops_AGCR "_hoops_PHSGR" _hoops_HSH
#define _hoops_CIGRP				0x0001
#define _hoops_SIGRP				0x0002
#define _hoops_GCGRP		0x0003
#define _hoops_RCGRP					0x0005

struct _hoops_AHAH {
	int				options;
	int				_hoops_ACGRP;
	float			scale, translate;
	RGB				color;

	_hoops_AHAH () : options (0) {}

	bool	operator== (_hoops_AHAH const & _hoops_HACIR) const {
		return	options		==	_hoops_HACIR.options	&&
				_hoops_ACGRP		==	_hoops_HACIR._hoops_ACGRP		&&
				scale		==	_hoops_HACIR.scale		&&
				translate	==	_hoops_HACIR.translate	&&
				color		==	_hoops_HACIR.color;
	}
	bool	operator!= (_hoops_AHAH const & _hoops_HACIR) const { return  !(*this == _hoops_HACIR); }
};







typedef char Param_Source;
#define HK_PS_UNSPECIFIED			(Param_Source)0
#define HK_PS_U						(Param_Source)1
#define HK_PS_UV					(Param_Source)2
#define HK_PS_UVW					(Param_Source)3
#define HK_PS_OBJECT				(Param_Source)4
#define HK_PS_WORLD					(Param_Source)5
#define HK_PS_SURFACE_NORMAL		(Param_Source)6
#define HK_PS_REFLECTION_VECTOR 	(Param_Source)7
#define HK_PS_NATURAL_UV			(Param_Source)8
#define HK_PS_LOCAL_PIXELS			(Param_Source)9
#define HK_PS_OUTER_PIXELS			(Param_Source)10
#define HK_PS_LOCAL_WINDOW			(Param_Source)11
#define HK_PS_OUTER_WINDOW			(Param_Source)12
#define HK_PS_TRANSMISSION_VECTOR	(Param_Source)13
#define HK_PS_SPHERE				(Param_Source)14
#define HK_PS_CYLINDER				(Param_Source)15
#define _hoops_HSR	(Param_Source)16

typedef char _hoops_PCGRP;
#define _hoops_HCGRP		(Param_Source)0
#define _hoops_ICGRP		(Param_Source)1
#define _hoops_CCGRP			(Param_Source)2
#define _hoops_SCGRP		(Param_Source)3
#define _hoops_GSGRP		(Param_Source)4

typedef char _hoops_RSGRP;
#define _hoops_ASGRP			(_hoops_RSGRP)0
#define _hoops_ASCC				(_hoops_RSGRP)1
#define _hoops_PSGRP			(_hoops_RSGRP)2
#define _hoops_SGA				(_hoops_RSGRP)3

typedef char _hoops_PPCRR;
#define _hoops_HSCC			(_hoops_PPCRR)0
#define _hoops_HSGRP		(_hoops_PPCRR)1
#define _hoops_ISGRP		(_hoops_PPCRR)2
#define _hoops_AARH		(_hoops_PPCRR)3
#define _hoops_CSGRP	(_hoops_PPCRR)4
#define _hoops_SSGRP		(_hoops_PPCRR)5
#define _hoops_GGRRP	(_hoops_PPCRR)6
#define _hoops_PARH	(_hoops_PPCRR)7

typedef char _hoops_RGRRP;
#define _hoops_AGRRP			(_hoops_RGRRP)0
#define _hoops_PGRRP				(_hoops_RGRRP)1
#define _hoops_HGRRP			(_hoops_RGRRP)2
#define _hoops_IGRRP			(_hoops_RGRRP)3
#define _hoops_CGRRP			(_hoops_RGRRP)4
#define _hoops_SGRRP			(_hoops_RGRRP)5
#define _hoops_GRRRP				(_hoops_RGRRP)6
#define _hoops_RRRRP		(_hoops_RGRRP)7

typedef Integer32 _hoops_ARRRP;
#define _hoops_PRRRP					(_hoops_ARRRP)0x00000000
#define _hoops_HRRRP			(_hoops_ARRRP)0x00000001
#define _hoops_IRRRP			(_hoops_ARRRP)0x00000002
#define _hoops_CRRRP			(_hoops_ARRRP)0x00000004
#define _hoops_SRRRP				(_hoops_ARRRP)0x00000008
#define _hoops_GARRP				(_hoops_ARRRP)0x00000010
#define _hoops_RARRP (_hoops_ARRRP)0x00000020
#define _hoops_AARRP	(_hoops_ARRRP)0x00000040
#define _hoops_PARRP		(_hoops_ARRRP)0x00000080
#define _hoops_HARRP	(_hoops_ARRRP)0x00000100
#define _hoops_IARRP	(_hoops_ARRRP)0x00000200
#define _hoops_CARRP	(_hoops_ARRRP)0x00000400
#define _hoops_HIRH (_hoops_ARRRP)0x00000780
#define _hoops_SARRP			(_hoops_ARRRP)0x00000800
#define _hoops_GPRRP				(_hoops_ARRRP)0x00001000
#define _hoops_RPRRP	(_hoops_ARRRP)0x00002000
#define _hoops_IAPS			(_hoops_ARRRP)0x00004000
#define _hoops_APRRP		(_hoops_ARRRP)0x00008000
#define TF_UNEVALUATED			(_hoops_ARRRP)0x00010000
#define _hoops_PPRRP				(_hoops_ARRRP)0x00020000
#define _hoops_HPRRP			(_hoops_ARRRP)0x00040000
#define _hoops_IPRRP				(_hoops_ARRRP)0x00080000
#define _hoops_CPRRP		(_hoops_ARRRP)0x00100000
#define _hoops_SPRRP			(_hoops_ARRRP)0x00200000
#define _hoops_GHRRP			(_hoops_ARRRP)0x00400000
#define _hoops_AIA				(_hoops_ARRRP)0x00800000
#define _hoops_IPGH	(_hoops_ARRRP)0x01000000
#define _hoops_RHRRP				(_hoops_ARRRP)0x02000000
#define _hoops_ASR	(_hoops_ARRRP)0x04000000
#define _hoops_AHRRP	(_hoops_ARRRP)0x08000000
#define _hoops_CSGH			(_hoops_ARRRP)0x10000000
#define _hoops_PHRRP	(_hoops_ARRRP)0x20000000

#define _hoops_HHRRP				(_hoops_ARRRP)0x00000000
#define _hoops_IGA			(_hoops_ARRRP)0x00000001
#define _hoops_RCRH		(_hoops_ARRRP)0x00000002
#define _hoops_PGA				(_hoops_ARRRP)0x00000004
#define _hoops_IHRRP			(_hoops_ARRRP)0x00000008
#define _hoops_ICARA		(_hoops_ARRRP)0x00000010
#define _hoops_CHRRP		(_hoops_ARRRP)0x00000020
#define _hoops_GSR				(_hoops_ARRRP)0x00000040

/* _hoops_IGI _hoops_GGR _hoops_SHRRP */
struct _hoops_GIRRP {
	_hoops_HCRPR				name; /*_hoops_PCSA _hoops_IS _hoops_CIH _hoops_RGR*/
	Image_Format		format;
	bool 				_hoops_RIRRP;
	bool 				_hoops_AIRRP;
	bool 				texture;
	_hoops_HCAIR 		_hoops_PIRRP;
	_hoops_HCAIR 		_hoops_HIRRP;
	bool				_hoops_IIRRP;
};

#define _hoops_IIPIR		_hoops_HCIGP(1)

typedef unsigned int _hoops_HIGH;
#define _hoops_CIRRP				(_hoops_HIGH)0x00000000
#define _hoops_SHCC		(_hoops_HIGH)0x00000001
#define _hoops_GHRH		(_hoops_HIGH)0x00000002
#define _hoops_AGSC			(_hoops_HIGH)0x00000004
#define _hoops_SIRRP			(_hoops_HIGH)0x00000008
#define _hoops_PPRH		(_hoops_HIGH)0x00000010
#define _hoops_RIRH			(_hoops_HIGH)0x00000020
#define _hoops_GCRH			(_hoops_HIGH)0x00000040
#define _hoops_HHRH			(_hoops_HIGH)0x00000080
#define _hoops_GCRRP		(_hoops_HIGH)0x00000100
#define _hoops_APAH			(_hoops_HIGH)0x00000200
#define _hoops_RCRRP		(_hoops_HIGH)0x00000400
#define _hoops_ACRRP		(_hoops_HIGH)0x00000800
#define _hoops_GIRH		(_hoops_HIGH)0x00001000
#define _hoops_PCRH			(_hoops_HIGH)0x00002000
#define _hoops_AIRH		(_hoops_HIGH)0x00004000
#define _hoops_PCRRP		(_hoops_HIGH)0x00008000
#define _hoops_GRRH			(_hoops_HIGH)0x00010000
#define _hoops_GICC	(_hoops_HIGH)0x00020000
#define _hoops_SSGH		(_hoops_HIGH)0x00040000
#define _hoops_GPAH			(_hoops_HIGH)0x00080000
#define _hoops_HAAH	(_hoops_HIGH)0x00100000
#define _hoops_HCRRP		(_hoops_HIGH)0x00200000


// _hoops_ICRRP _hoops_PGAP _hoops_SIH _hoops_HII _hoops_CSCR _hoops_SGI _hoops_IRS (_hoops_CCRRP) _hoops_CCAH _hoops_CSCR _hoops_CGH _hoops_CAPGP 
// _hoops_HII _hoops_RH (_hoops_SGRH) _hoops_HCGP _hoops_CSCR
#define _hoops_SCRRP (		\
	_hoops_HAAH |	\
	_hoops_GICC |		\
	_hoops_AIRH |		\
	_hoops_GIRH |		\
	_hoops_RIRH |			\
	_hoops_SIRRP |			\
	_hoops_GHRH)


struct _hoops_GSRRP {
	_hoops_RGRRP						_hoops_RSRRP;
	_hoops_RGRRP						_hoops_ASRRP;
	_hoops_RGRRP						_hoops_PSRRP;
	_hoops_RGRRP						_hoops_HSRRP;
	float						_hoops_IIRH, _hoops_CIRH;
	float						_hoops_SIRH;
	RGB							_hoops_IPIR;

	bool	operator== (_hoops_GSRRP const & _hoops_HACIR) const {
		return	_hoops_RSRRP		== 	_hoops_HACIR._hoops_RSRRP		&&
				_hoops_ASRRP	== 	_hoops_HACIR._hoops_ASRRP	&&
				_hoops_PSRRP		== 	_hoops_HACIR._hoops_PSRRP	&&
				_hoops_HSRRP	== 	_hoops_HACIR._hoops_HSRRP	&&
				_hoops_IIRH				== 	_hoops_HACIR._hoops_IIRH				&&
				_hoops_CIRH				== 	_hoops_HACIR._hoops_CIRH				&&
				_hoops_SIRH				== 	_hoops_HACIR._hoops_SIRH			&&
				_hoops_IPIR		== 	_hoops_HACIR._hoops_IPIR;
	}
	bool	operator!= (_hoops_GSRRP const & _hoops_HACIR) const { return  !(*this == _hoops_HACIR); }
};

struct Image : public Geometry {
	Image_Format				format, _hoops_ISRRP;
	char						_hoops_GCPIR, _hoops_CSRRP;
	int							row_bytes;
	int							_hoops_IARH;  //_hoops_RGAR _hoops_IGI _hoops_IH _hoops_SGRH _hoops_RRRH
	float						_hoops_SSRRP;    //_hoops_RPP _hoops_CRGP _hoops_HSAR 1.0, _hoops_HS _hoops_RHPP _hoops_SAGR _hoops_GPP _hoops_GGARP
	Point						_hoops_CSAI;
	int							width, height;
	void const * const *		rasters;
	void const * const *		_hoops_RCPIR;
	void const *				_hoops_PHGH;

	_hoops_GARSR					_hoops_RGARP;
	Integer32					_hoops_AGARP;
	Integer32					_hoops_PGARP;

	_hoops_HCRPR						name;

	/* _hoops_HH _hoops_IPPAR _hoops_CIPH */
	_hoops_GACR *				_hoops_GAHA;
	_hoops_RCR	*					texture;
	Image *						next;
	Image *						prev;

	_hoops_HCAIR				_hoops_PIRRP, _hoops_HIRRP;

	_hoops_GSRRP				_hoops_HPIR;
	_hoops_AHAH						_hoops_PHAH;

	_hoops_HIGH					flags;
};

struct _hoops_GAAIR : public Attribute {
	_hoops_HRPA					matrix;
};

struct _hoops_CPAIR : public Attribute {
	_hoops_RCR **					textures;
	Integer32 *					keys;
	int							count;
};


enum _hoops_HGARP {
	_hoops_IGARP = 0,
	_hoops_CGARP = 1
	//_hoops_SGARP = 2,
	//_hoops_GRARP = 3,
};

//_hoops_SHR _hoops_HHRI _hoops_HPP _hoops_GRAR, _hoops_IIP _hoops_CGI _hoops_GPP _hoops_RGCI _hoops_HAII
struct _hoops_AGSA {
	//_hoops_PHSGR _hoops_RRARP    _hoops_ARARP; //_hoops_SHR _hoops_PRARP _hoops_IH _hoops_HA
	Integer32			id;
	_hoops_HCRPR				shader_source;
};

struct _hoops_RCR : public _hoops_HGHGP<_hoops_RCR, _hoops_HPAH> {
	_hoops_HCRPR				name;
	_hoops_AAPIR *			_hoops_PAPIR;
	Integer32			key;
	Integer32			_hoops_PSSGA;
	_hoops_HCHIR *		_hoops_HGIIR;
	void  *				_hoops_HRARP;
	Image *				image;
	Image *				_hoops_RHGH;
	_hoops_CRCP *			_hoops_IRARP;
	_hoops_GAAIR *	_hoops_GAGH;
	_hoops_RCR	**			_hoops_PRAH;  //_hoops_HII _hoops_CRARP>1 _hoops_PAR _hoops_GSGH
	_hoops_CRCP *			_hoops_SRARP;
	_hoops_HHRA *			_hoops_RRIIR;
	_hoops_AGSA *			_hoops_RSR;
	_hoops_ARRRP		flags;
	_hoops_ARRRP		_hoops_SCR;
	int					_hoops_RSCP;
	Param_Source		_hoops_PSR;
	_hoops_PCGRP		_hoops_GAARP;
	_hoops_RSGRP		_hoops_CGA;
	_hoops_PPCRR				_hoops_PSCC;
	_hoops_PPCRR				_hoops_RARH;
	_hoops_GSRRP		_hoops_HPIR;
	int					_hoops_ICR[3];
};

struct _hoops_RAARP {
	_hoops_RAARP *	next;
	unsigned char *		bitmap;
	_hoops_RCR *			txr;
	unsigned char *		_hoops_AAARP;
	unsigned int		_hoops_PAARP;
	int					width;
	int					height;
	int					_hoops_HAARP;
	int					_hoops_IAARP;
	int					_hoops_CAARP;
	int					_hoops_SAARP;
	int					_hoops_GPARP;
	int					_hoops_RPARP;
	int					_hoops_APARP;
	int					_hoops_PPARP;
	int					id;
	/* _hoops_AGCR _hoops_RIHCR _hoops_AII _hoops_CHR _hoops_IGI _hoops_IS _hoops_IHIS _hoops_RH _hoops_GAS _hoops_HPARP,
	   _hoops_SGGR _hoops_HII _hoops_RH _hoops_APSP _hoops_SPPR, _hoops_HIS _hoops_ISAP _hoops_HRGR _hoops_GSAS _hoops_PSAP */
	int					_hoops_IPARP;
	int					_hoops_CPARP;
	float				rotation;
	float				width_scale;
};


struct Grid : public Geometry {
	int					_hoops_APIAA;
#define _hoops_PPIAA		1
#define _hoops_SPARP				2
	Point				origin,
						ref1,
						ref2;
	int					count1,
						count2;

	Vector				_hoops_GGHI,
						_hoops_RGHI;
	_hoops_ARPA				plane;
	int					_hoops_IPIAA;				/* _hoops_GHARP _hoops_RGAR */
};




struct _hoops_ISGI : public Attribute {
	_hoops_HRPA			matrix;
};

struct Window : public Attribute {
	_hoops_PACIR	_hoops_RCHS;
	_hoops_PACIR	_hoops_ISGPR;
	_hoops_PACIR	_hoops_HSGPR;
};


#define	_hoops_SPAGA		0x01
#define	_hoops_RHIH			0x02

struct _hoops_IRAIR : public Attribute {
	Point *				points;
	int					count;
	int					flags;
};


struct _hoops_RSAIR : public Attribute {
	_hoops_ACHR			mask,
						value;
	struct {
		_hoops_ACHR			mask,
							value;
	}					_hoops_PRIGA;
	struct {
		_hoops_ACHR			mask,
							value;
	}					_hoops_SPSS;
};

struct _hoops_ASAIR : public Attribute {
	_hoops_ACHR			mask,
						up,
						down,
						_hoops_RHARP,
						_hoops_AHARP,
						_hoops_PHARP,
						_hoops_HHARP;
};


//_hoops_ACGIA _hoops_RGRHA _hoops_IHARP; // _hoops_IHIS _hoops_IS _hoops_CHARP._hoops_GGHR _hoops_IH _hoops_SHARP

#define _hoops_GIARP							(_hoops_RIARP)0x00000001
#define	_hoops_AIARP							(_hoops_RIARP)0x00000002
#define _hoops_PIARP						(_hoops_RIARP)0x00000004
#define _hoops_HIARP						(_hoops_RIARP)0x00000008
#define _hoops_IIARP				(_hoops_RIARP)0x00000010
#define _hoops_CIARP					(_hoops_RIARP)0x00000020
#define _hoops_SIARP				(_hoops_RIARP)0x0000FFFF

/* _hoops_AGCR _hoops_CHR _hoops_IGI _hoops_HPP _hoops_RH _hoops_RPPS _hoops_IPP */
#define	_hoops_GCARP			(_hoops_RIARP)0x00010000
#define	_hoops_RCARP	(_hoops_RIARP)0x00020000
#define	_hoops_ACARP				(_hoops_RIARP)0x80000000

struct _hoops_GSAIR : public Attribute {
	_hoops_RIARP	flags;
};

struct _hoops_ARAIR : public Attribute {
	int					which;
#	define		_hoops_RAACA	0
#	define		_hoops_GIACA		1
};

struct _hoops_RRAIR : public Attribute {
	_hoops_CRCP *			_hoops_PHSCA;
	bool				flag;
};

struct _hoops_GAPIR : public Attribute {
	_hoops_PCARP			_hoops_IAICA,
						_hoops_HCARP;

#	define	  _hoops_ICARP						(_hoops_PCARP)0x00000001
#	define	  _hoops_CCARP				(_hoops_PCARP)0x00000002
#	define	  _hoops_SCARP					(_hoops_PCARP)0x00000004
#	define	  _hoops_GSARP				(_hoops_PCARP)0x00000008
#	define	  _hoops_RSARP		(_hoops_PCARP)0x00000010
#	define	  _hoops_ASARP				(_hoops_PCARP)0x00000020
#	define	  _hoops_PSARP			(_hoops_PCARP)0x00000040
#	define	  _hoops_HSARP			(_hoops_PCARP)0x00000080
#	define	  _hoops_ISARP			(_hoops_PCARP)0x00000100
#	define	  _hoops_CSARP					(_hoops_PCARP)0x00000200
#	define	  _hoops_SSARP				(_hoops_PCARP)0x00000400
#	define	  _hoops_GGPRP			(_hoops_PCARP)0x00000800
#	define	  _hoops_RGPRP					(_hoops_PCARP)0x00001000
#	define	  _hoops_AGPRP						(_hoops_PCARP)0x00002000
#	define	  _hoops_PGPRP			(_hoops_PCARP)0x00004000
#	define	  _hoops_HGPRP				(_hoops_PCARP)0x00008000
#	define	  _hoops_IGPRP				(_hoops_PCARP)0x00010000
#	define	  _hoops_CGPRP				(_hoops_PCARP)0x00020000
#	define	  _hoops_SGPRP					(_hoops_PCARP)0x00040000
#	define	  _hoops_GRPRP				(_hoops_PCARP)0x00080000
#	define	  _hoops_RRPRP			(_hoops_PCARP)0x00100000
#	define	  _hoops_ARPRP				(_hoops_PCARP)0x00200000
#	define	  _hoops_PRPRP			(_hoops_PCARP)0x00400000
#	define	  _hoops_HRPRP			(_hoops_PCARP)0x00800000
#	define	  _hoops_IRPRP			(_hoops_PCARP)0x01000000
#	define	  _hoops_CRPRP				(_hoops_PCARP)0x02000000
#	define	  _hoops_SRPRP		(_hoops_PCARP)0x04000000
#	define	  _hoops_GAPRP					(_hoops_PCARP)0x08000000
#	define	  _hoops_RAPRP	(_hoops_PCARP)0x10000000
#	define	  _hoops_AAPRP				    (_hoops_PCARP)0x20000000
#	define	  _hoops_PAPRP			(_hoops_PCARP)0x40000000

#	define	  _hoops_HAPRP						(_hoops_PCARP)0x80000000

	_hoops_PCARP			_hoops_HAICA,
						_hoops_IAPRP;

#	define	  _hoops_CAPRP				(_hoops_PCARP)0x80000001
#	define	  _hoops_SAPRP						(_hoops_PCARP)0x80000002
#	define	  _hoops_GPPRP				(_hoops_PCARP)0x80000004
#	define	  _hoops_RPPRP			(_hoops_PCARP)0x80000008
#	define	  _hoops_APPRP		(_hoops_PCARP)0x80000010
#	define	  _hoops_PPPRP			(_hoops_PCARP)0x80000020
#	define	  _hoops_HPPRP			(_hoops_PCARP)0x80000040
#	define	  _hoops_IPPRP			(_hoops_PCARP)0x80000080
#	define	  _hoops_CPPRP			(_hoops_PCARP)0x80000100
#	define	  _hoops_SPPRP		(_hoops_PCARP)0x80000200
#	define	  _hoops_GHPRP				(_hoops_PCARP)0x80000400
#	define	  _hoops_RHPRP			(_hoops_PCARP)0x80000800
#	define	  _hoops_AHPRP			(_hoops_PCARP)0x80001000
#	define	  _hoops_PHPRP		(_hoops_PCARP)0x80002000
#	define	  Drivo_VERTEX_SPOTLIGHT			(_hoops_PCARP)0x80004000
#	define	  _hoops_HHPRP				(_hoops_PCARP)0x80008000
#	define	  _hoops_IHPRP				(_hoops_PCARP)0x80010000
#	define	  _hoops_CHPRP			(_hoops_PCARP)0x80020000
#	define	  _hoops_SHPRP		(_hoops_PCARP)0x80040000
#	define	  _hoops_GIPRP					(_hoops_PCARP)0x80080000
#	define	  _hoops_RIPRP		(_hoops_PCARP)0x80100000
#	define	  _hoops_AIPRP		(_hoops_PCARP)0x80200000
#	define	  _hoops_PIPRP		(_hoops_PCARP)0x80400000
#	define	  _hoops_HIPRP						(_hoops_PCARP)0x80800000
#   define	  _hoops_IIPRP				(_hoops_PCARP)0x81000000
#   define	  _hoops_CIPRP				(_hoops_PCARP)0x82000000
#	define	  _hoops_SIPRP					(_hoops_PCARP)0xC0000000

	int					_hoops_APPIR;
	int *				_hoops_RPPIR;
	int					_hoops_IRARR;
	int					_hoops_APASR;
	int					_hoops_GCPRP[3];
	float				_hoops_RCPRP;
	float				_hoops_ACPRP;
	float				_hoops_PCPRP[3][2];
	int					_hoops_AAPSR;
	float				_hoops_GSHSR;
	XY					_hoops_SPHSR;
	float				_hoops_SHSHA;
	_hoops_PACIR	_hoops_HCPRP;
	_hoops_HCRPR				_hoops_IAPIR;
	int					_hoops_AIPGA;
	_hoops_IGPIR *			_hoops_SAPIR;
	_hoops_IGPIR *			_hoops_GPPIR;

#	define		_hoops_ICPRP			0
#	define		_hoops_CCPRP		1
#	define		_hoops_SCPRP	3
	int					_hoops_GSPRP;

#	define		_hoops_RSPRP		0
#	define		_hoops_ASPRP		1
#	define		_hoops_PSPRP		2
	int					_hoops_HSPRP;


	POINTER_SIZED_INT 	_hoops_GCHSR;
	POINTER_SIZED_INT 	_hoops_ISPRP;
	POINTER_SIZED_INT 	_hoops_RCHSR;
	POINTER_SIZED_INT 	_hoops_CSPRP;

#	define		_hoops_SSPRP			0
#	define		_hoops_GGHRP			1
	int					_hoops_RGHRP;

	int					_hoops_AGHRP;
	_hoops_AAPIR *			_hoops_HAPIR;

#	define	  _hoops_PGHRP				0
#	define	  Drivo_Landscape_ON				1
#	define	  _hoops_HGHRP		2
	int					_hoops_IGHRP;

#	define	  _hoops_CGHRP					0
#	define	  _hoops_SGHRP				1
#	define	  _hoops_GRHRP				2
#	define	  _hoops_RRHRP		3
	int					_hoops_ARHRP;

#	define	  _hoops_PRHRP		0
#	define	  _hoops_HRHRP		1
#	define	  _hoops_IRHRP	2
	int					_hoops_CRHRP;

#	define	  _hoops_SRHRP		0
#	define	  _hoops_GAHRP			1
#	define	  _hoops_RAHRP		2 /* _hoops_PAH _hoops_PHGA "_hoops_APHSR" _hoops_PAR "_hoops_AAHRP" */
#	define	  _hoops_PAHRP		3
#   define	  _hoops_HAHRP				_hoops_PAHRP
	int					_hoops_IAHRP[_hoops_HAHRP+1];

#	define	  _hoops_CAHRP		0
#	define	  _hoops_SAHRP		1
#	define	  _hoops_GPHRP		2
#	define	  _hoops_RPHRP			3
#	define	  _hoops_APHRP		4
	int					_hoops_PPHRP;

	bool				_hoops_HPHRP;

	int					_hoops_GHHSR;

#	define    _hoops_IPHRP				0x0001
#	define    _hoops_CPHRP		0x0002
#	define    _hoops_SPHRP	0x0004
	struct _hoops_GHHRP {
		_hoops_RHHRP   mask, value;
		float					_hoops_GAHP;
	} _hoops_AHHRP;

#	define    _hoops_PHHRP			0x0001
#	define    _hoops_HHHRP		0x0002
#	define    _hoops_IHHRP			0x0004
#	define    _hoops_CHHRP			0x0008
#	define    _hoops_SHHRP	(_hoops_IHHRP|_hoops_CHHRP)
	struct _hoops_GIHRP {
		_hoops_RIHRP   mask, value;
		float					_hoops_GIGP;
	} _hoops_AIHRP;

#	define    _hoops_PIHRP				0x0001
#	define    _hoops_HIHRP			0x0002
#	define    _hoops_IIHRP		0x0004
#	define    _hoops_CGSH				0x0008
#	define    _hoops_CIHRP			0x0010
#	define    _hoops_SIHRP			(_hoops_CGSH|_hoops_CIHRP)
	struct _hoops_GCHRP {
		_hoops_RCHRP				mask, value;
		float					_hoops_SHGP;
		int						_hoops_HGGGR;
	} _hoops_RGSH;

#	define    _hoops_ACHRP		0x0001
#	define    _hoops_PCHRP		0x0002
#	define    _hoops_HCHRP		0x0004
#	define    _hoops_ICHRP	0x0008
	struct _hoops_CCHRP {
		_hoops_SCHRP	mask, value;
		float					_hoops_GSHRP;
		float					_hoops_RSHRP;
		float					_hoops_SHGP;
	} _hoops_ASHRP;

	void *				_hoops_PSHRP;

	_hoops_HCHIR *		_hoops_PPPIR;
	void *				_hoops_HSHRP;
};


/* _hoops_SAHR _hoops_PIHHR _hoops_IRS _hoops_ARGHR _hoops_IIGR _hoops_CIPH _hoops_GIRP */
#define _hoops_ISHRP(configs) \
	((configs)._hoops_GRPPA = \
	   ((configs)._hoops_CSHRP) ^\
	   ((configs)._hoops_SSHRP << 16) ^\
	   ((*(const int *)(&(configs)._hoops_GGIRP))) ^\
	   ((*(const int *)(&(configs)._hoops_RGIRP)>>2)) ^\
	   ((*(const int *)(&(configs)._hoops_AGIRP)>>4)) ^\
	   ((*(const int *)(&(configs)._hoops_PGIRP)>>6))\
	)

struct _hoops_PARC {
	int			_hoops_PPPI,
				_hoops_HPPI;
	float		_hoops_IPPI,
				_hoops_CPPI,
				_hoops_SPPI;
	bool		_hoops_SAR;
};


struct _hoops_AIIAA {
	int			_hoops_GRPPA;
	float		_hoops_GGIRP;	/* _hoops_SCGA [0..1] _hoops_PRISA _hoops_GC */
	int			_hoops_CSHRP;			/* _hoops_RSHS */
	float		_hoops_RGIRP;		/* _hoops_CARA _hoops_GC */
	float		_hoops_AGIRP;			/* _hoops_ASIPR */
	float		_hoops_PGIRP;			/* _hoops_SCGA [0..1] _hoops_PRISA _hoops_GC */
	int			_hoops_SSHRP;				/* _hoops_PPSR _hoops_RPR */
};




struct _hoops_GHAIR : public Attribute {
	_hoops_CGSP	mask,
						value;
#	define		_hoops_HGIRP						(_hoops_CGSP)0x00000000
#	define		_hoops_PICAR					(_hoops_CGSP)0x00000001
#	define		_hoops_IGIRP			(_hoops_CGSP)0x00000002
#	define		_hoops_CGIRP		(_hoops_CGSP)0x00000004
#	define		_hoops_SGIRP				(_hoops_CGSP)0x00000008
#	define		_hoops_CGCS			(_hoops_CGSP)0x00000010
#	define		_hoops_GRIRP			(_hoops_CGSP)0x00000020
#	define		_hoops_SASA (_hoops_CGSP)0x00000040
#	define		_hoops_GPSA	(_hoops_CGSP)0x00000080
#	define		_hoops_RRIRP		(_hoops_CGSP)0x00000100
#	define		_hoops_IRI			(_hoops_CGSP)0x00000200
#	define		_hoops_ARIRP						(_hoops_CGSP)0x00000400
#	define		_hoops_PRIRP				(_hoops_CGSP)0x00000800
#	define		_hoops_HRIRP				(_hoops_CGSP)0x00001000
#	define		_hoops_IRIRP			(_hoops_CGSP)0x00002000
#	define		_hoops_CRIRP					(_hoops_CGSP)0x00004000
#	define		_hoops_SICIA	(_hoops_CGSP)0x00008000
#	define		_hoops_SRIRP	(_hoops_CGSP)0x00010000
#	define		_hoops_GAIRP			(_hoops_CGSP)0x00020000
#	define		_hoops_RAIRP					(_hoops_CGSP)0x00040000
#	define		_hoops_AAIRP			(_hoops_CGSP)0x00080000
#	define		_hoops_CCIAA			(_hoops_CGSP)0x00100000
#	define		_hoops_PAIRP			(_hoops_CGSP)0x00200000
#	define		_hoops_HAIRP			(_hoops_CGSP)0x00400000
#	define		_hoops_IAIRP				(_hoops_CGSP)0x00800000
#	define		_hoops_CAIRP			(_hoops_CGSP)0x01000000
#	define		_hoops_SAIRP			(_hoops_CGSP)0x02000000
#	define		_hoops_GPIRP				(_hoops_CGSP)0x04000000
#	define		_hoops_RPIRP			(_hoops_CGSP)0x08000000
#	define		_hoops_APIRP			(_hoops_CGSP)0x10000000
#	define		_hoops_PPIRP					(_hoops_CGSP)0x20000000


#	define		_hoops_RSA	(_hoops_CGSP)(_hoops_SASA|_hoops_GPSA)
#	define		_hoops_HPIRP		(_hoops_CGSP)(_hoops_HRIRP|_hoops_IRIRP|_hoops_CRIRP)
#	define		_hoops_IPIRP		(_hoops_CGSP)(_hoops_HAIRP|_hoops_IAIRP)


#	define		_hoops_CPIRP				0x0000
#	define		Heur_Culling_VIEW_FRUSTUM		0x0001
#	define		Heur_Culling_EXTENT				0x0002
#	define		_hoops_SPIRP		0x0004
#   define		_hoops_GHIRP				0x0008
#	define		_hoops_RHIRP		0x0100
#	define		_hoops_AHIRP	0x0200
#	define		_hoops_PHIRP	0x0400
#	define		_hoops_RIHS		0x0800
#	define		_hoops_HHIRP		0x1000
#	define		_hoops_IHIRP				0x1F0F

#	define		_hoops_CHIRP			0
#	define		_hoops_SHIRP			1
#	define		_hoops_GIIRP		2
#	define		Heur_MAX_EXTENT_MODE_DEFER			3

#	define		_hoops_RIIRP			0x00
#	define		_hoops_AIIRP		0x01
#	define		_hoops_PIIRP		0x02
#	define		_hoops_GIHS		0x04
#	define		_hoops_HIIRP			0x07

	struct {
		short				mask,
							value;
		/* _hoops_CAGH-_hoops_PAPA _hoops_IAPRR _hoops_AAGA */
		Vector				vector;
		float				_hoops_IIIRP;
		/* _hoops_CIAS _hoops_CRRPA _hoops_IAPRR */
		int					_hoops_GRGC;
		int					_hoops_CIIRP;
		int					_hoops_PCHS;
		int					_hoops_SHHS;
		int					_hoops_GCHS;

#	define		_hoops_SIIRP    0
#	define		_hoops_GCIRP			1
		/* _hoops_RCIRP _hoops_IAPRR */
		int					_hoops_ACIRP;
		bool				_hoops_PCIRP;
	}					_hoops_APH;

	int					_hoops_GCCIA;
	struct {
		int					_hoops_SPHPR,
							polyline;
#		define	_hoops_HCIRP			0x01
#		define	_hoops_ICIRP		0x02
		short				mask,
							value;
	}					_hoops_CCIRP;

#	define		_hoops_SCIRP			0 
#	define		_hoops_GSIRP		1
#	define		_hoops_RSIRP				2
#	define		_hoops_ASIRP			3
#	define		_hoops_PSIRP				4
#	define		_hoops_HSIRP				5
#	define		_hoops_ISIRP				6

	int					_hoops_CSIRP;
	float				_hoops_SSIRP[_hoops_ISIRP];
	float				_hoops_GGCRP;
	int					_hoops_RGCRP;
	int					_hoops_AGCRP;				

#	define 		_hoops_PGCRP			0
#	define 		_hoops_HGCRP		1
#	define 		_hoops_IGCRP	2
#	define 		_hoops_CGCRP		3	/* _hoops_SGCRP */
	int					_hoops_GRCRP;

	int					_hoops_RRCRP;
	float				_hoops_ARCRP;

#	define		_hoops_PRCRP			0
#	define		_hoops_HRCRP				1

	int					_hoops_IRCRP;

	int					_hoops_PPSHA;
	float				_hoops_SHSHA;
};



#define _hoops_CRCRP(_hoops_SRCRP, _hoops_GACRP, _hoops_RACRP, _hoops_AACRP) {				\
	int						_size_ = _hoops_RACRP;						\
	unsigned char			*_hoops_PACRP = (unsigned char *)_hoops_SRCRP;		\
	unsigned char const		*_hoops_HACRP = (unsigned char const *)_hoops_GACRP;\
	while (_size_ >= 4) {											\
	*(unsigned int *)_hoops_PACRP _hoops_AACRP *(unsigned int const *)_hoops_HACRP;			\
	_hoops_PACRP += 4;	_hoops_HACRP += 4;	_size_ -= 4;							\
	}																\
	while (_size_-- > 0) *_hoops_PACRP++ _hoops_AACRP *_hoops_HACRP++;						\
}

/* _hoops_RCGRA _hoops_IIGR '_hoops_IRS |= _hoops_RCSR' _hoops_IH _hoops_HCCGR */
#define _hoops_ISIAA(_hoops_SRCRP, _hoops_GACRP, _hoops_RACRP) _hoops_CRCRP((_hoops_SRCRP), (_hoops_GACRP), (_hoops_RACRP), |= )

/* _hoops_RCGRA _hoops_IIGR '_hoops_IRS ^= _hoops_RCSR' _hoops_IH _hoops_HCCGR */
#define _hoops_IACRP(_hoops_SRCRP, _hoops_GACRP, _hoops_RACRP) _hoops_CRCRP((_hoops_SRCRP), (_hoops_GACRP), (_hoops_RACRP), ^= )

/* _hoops_RCGRA _hoops_IIGR '_hoops_IRS &= _hoops_RCSR' _hoops_IH _hoops_HCCGR */
#define _hoops_IGCAA(_hoops_SRCRP, _hoops_GACRP, _hoops_RACRP) _hoops_CRCRP((_hoops_SRCRP), (_hoops_GACRP), (_hoops_RACRP), &= )

/* _hoops_RCGRA _hoops_IIGR '_hoops_IRS &= ~_hoops_RCSR' _hoops_IH _hoops_HCCGR */
#define _hoops_HSIAA(_hoops_SRCRP, _hoops_GACRP, _hoops_RACRP) _hoops_CRCRP((_hoops_SRCRP), (_hoops_GACRP), (_hoops_RACRP), &= ~ )


struct _hoops_PIGRA {
	_hoops_HHAGP			_hoops_IPPGR;
	Color_Object			color;
	_hoops_ARGRA		_hoops_HAA[_hoops_IIGRA];
	_hoops_ACHR				_hoops_RGP;
	_hoops_GHGI				_hoops_RSHCA;
};



struct _hoops_CACRP {
	_hoops_PIGRA		mask, value;
};

struct _hoops_CCAIR {
	_hoops_CACRP	normal, _hoops_SACRP;
};

struct _hoops_HIAIR {
	_hoops_GPCRP			mask,
								value;
#	define		_hoops_RCCI			(_hoops_GPCRP)0x0001
#	define		_hoops_RPCRP				(_hoops_GPCRP)0x0002
#	define		_hoops_APCRP			(_hoops_GPCRP)0x0004
#	define		_hoops_PPCRP	(_hoops_GPCRP)0x0008
#	define		_hoops_HPCRP		(_hoops_GPCRP)0x0010
#	define		_hoops_IPCRP			(_hoops_GPCRP)0x0020
#	define		_hoops_CPCRP	(_hoops_GPCRP)0x0040
#	define		_hoops_SPCRP				(_hoops_GPCRP)0x0080
#	define		_hoops_GHCRP				(_hoops_GPCRP)0x0100
#	define		_hoops_RHCRP		(_hoops_GPCRP)0x0200
#	define		_hoops_AHCRP		(_hoops_GPCRP)0x0400
#	define		_hoops_PHCRP	(_hoops_GPCRP)0x0800

	RGB						color;
	_hoops_HCRPR					_hoops_PIAIR;
	Integer32				_hoops_HHCRP;
	float					_hoops_IHCRP;
	float					_hoops_CHIH;
	float					_hoops_CHCRP;
	_hoops_HCAIR			weight;
	_hoops_SHCRP			_hoops_SRI;	/* _hoops_GAR _hoops_GSSR _hoops_SHASA _hoops_ARRS */
};

struct _hoops_ICAIR {
	_hoops_GICRP	mask,
							value;
#define	_hoops_RICRP	(_hoops_GICRP)0x00000001
#define _hoops_AICRP	(_hoops_GICRP)0x00000002
#define _hoops_PICRP		(_hoops_GICRP)0x000000FF
#define	_hoops_HICRP	(_hoops_GICRP)0x00000100
#define	_hoops_IICRP	(_hoops_GICRP)0x00000200
#define	_hoops_CICRP		(_hoops_GICRP)0x00000400
#define	_hoops_SICRP		(_hoops_GICRP)0x00000800
#define	_hoops_GCCRP		(_hoops_GICRP)0x00001000
#define	_hoops_RCCRP	(_hoops_GICRP)0x00002000
#define _hoops_ACCRP		(_hoops_GICRP)0x0000FF00

	struct {
		_hoops_ACHR				mask,
								value;
	}						_hoops_RGP;

#define _hoops_PCCRP			0
#define _hoops_HCCRP	1
#define _hoops_ICCRP		2
	int						_hoops_CCCRP;
	float					scale, translate;


#define	_hoops_SCCRP	0
#define _hoops_GSCRP	1
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
};

struct _hoops_PHAIR {
#define _hoops_IGAIR 8
/* _hoops_RGAP-_hoops_GHIR _hoops_AAP */
#	define _hoops_HRSI					(_hoops_RRPHA)0x00000001
#	define _hoops_ASCRP	(_hoops_RRPHA)0x00000002
#	define _hoops_PSCRP		(_hoops_RRPHA)0x00000004
#	define _hoops_HSCRP		(~(_hoops_PSCRP))
#	define _hoops_ISCRP					(_hoops_RRPHA)0x00000008
#	define _hoops_CSCRP		(_hoops_RRPHA)0x00000010
#	define _hoops_SSCRP				(_hoops_RRPHA)0x00000020
#	define _hoops_GGSRP				(_hoops_RRPHA)0x00000040
#	define _hoops_RGSRP		(_hoops_RRPHA)0x00000080
#	define _hoops_AGSRP				(_hoops_RRPHA)0x00000100  /* _hoops_PGSRP _hoops_IS _hoops_HGSRP */
#	define _hoops_IGSRP				(_hoops_RRPHA)0x00000200
#	define _hoops_CGSRP				(_hoops_RRPHA)0x00000400
#	define _hoops_SGSRP			(_hoops_RRPHA)0x00000800  /* _hoops_RHGS */
#	define _hoops_GRSRP		(_hoops_RRPHA)0x00001000  /* _hoops_RHGS */
#	define _hoops_RRSRP					(_hoops_RRPHA)0x00002000  /* _hoops_RHGS */
#	define _hoops_ARSRP	(_hoops_RRPHA)0x00004000  /* _hoops_RHGS */
#	define _hoops_PRSRP	(_hoops_RRPHA)0x00008000  /* _hoops_RHGS */
#	define _hoops_HRSRP		(_hoops_ARSRP|_hoops_PRSRP)
#	define _hoops_IRSRP		(_hoops_RRPHA)0x00010000  /* _hoops_RHGS */
/* _hoops_PGSA-_hoops_GHIR _hoops_AAP */
#	define _hoops_CRSRP			(_hoops_RRPHA)0x00020000
#	define _hoops_SRSRP		(_hoops_RRPHA)0x00040000
#	define _hoops_GASRP		(_hoops_RRPHA)0
#	define _hoops_RASRP	(_hoops_RRPHA)0x00080000
#	define _hoops_AASRP			(_hoops_RRPHA)0x00100000
#	define _hoops_PASRP					(_hoops_RRPHA)0x00200000
#	define _hoops_HASRP					(_hoops_RRPHA)0x00400000
#	define _hoops_IASRP				(_hoops_RRPHA)0x00800000

#	define _hoops_CASRP		1
#	define _hoops_SASRP			2
#	define _hoops_GPSRP			3
#	define _hoops_RPSRP				4
#	define _hoops_APSRP		5
#	define _hoops_PPSRP			6
#	define _hoops_HPSRP				7
#	define _hoops_IPSRP					8
#	define _hoops_CPSRP				9

#	define _hoops_SPSRP			  0x01	 /* _hoops_PGSA _hoops_ISAP */
#	define _hoops_GHSRP		  0x02	 /* _hoops_PGSA _hoops_RH _hoops_IASC _hoops_IPIS */
#	define _hoops_RHSRP		  0x04	 /* _hoops_PGSA _hoops_RH _hoops_CGHI _hoops_PRCCA _hoops_GGR _hoops_RH _hoops_HIGR */
#	define _hoops_AHSRP	  0x08	 /* _hoops_PHSRP _hoops_RPP _hoops_HHSRP, _hoops_ISAP _hoops_IAII */
#	define _hoops_IHSRP 0x10	 /* _hoops_PHSRP _hoops_RPP _hoops_HHSRP, _hoops_IASC _hoops_IAII */
#	define _hoops_CHSRP	  0x20	 /* _hoops_IASC _hoops_RPP _hoops_PSAP _hoops_HPP _hoops_RGAR _hoops_SPR _hoops_PAPA, _hoops_ISAP _hoops_IAII*/

#	define _hoops_SHSRP 0
#	define _hoops_GISRP 1

		_hoops_RRPHA				mask,
								value;
		float					_hoops_PRPHA[_hoops_IGAIR]; /* _hoops_RISRP _hoops_AHHSR */
		float					_hoops_AISRP[_hoops_IGAIR]; /* _hoops_CICA _hoops_PISRP */
		int						_hoops_HISRP;
		int						_hoops_IISRP;			/* _hoops_CISRP _hoops_IS _hoops_PAPA.	-1 _hoops_RPP _hoops_GRGR */
		int						_hoops_IRSH;
		int						_hoops_RHPHA;
		float					tolerance;
		Bounding				bounding;
		float					_hoops_GHRGR[_hoops_IGAIR]; /* _hoops_SHRRR _hoops_SISRP _hoops_GCSRP */
		int						_hoops_SRHHR; /* _hoops_SISRP _hoops_CSHHR (_hoops_RAR _hoops_HIAGR) */
		int						_hoops_RCSRP; /* _hoops_IIPGA _hoops_GGR _hoops_AGIR _hoops_SR _hoops_IAGC _hoops_IRS _hoops_GRAA-_hoops_PHIPR _hoops_PRCCA */
		int						_hoops_ARPHA;
};




struct _hoops_RIAIR {
	struct {
		float					hither,
								yon;
	}						_hoops_CRIR;

	float					_hoops_ACSRP;
	float					_hoops_PCSRP;

	Vector					_hoops_HRGA;

	bool					_hoops_HCSRP;

	struct {
#	define _hoops_ICSRP			(_hoops_CCSRP)0x0001
#	define _hoops_SCSRP			(_hoops_CCSRP)0x0002
#	define _hoops_GSSRP				(_hoops_CCSRP)0x0004
		_hoops_CCSRP				mask,
								value;
		float					_hoops_HCIR[2];
		float					_hoops_GRCR;
		Style *					_hoops_CHAIR;
		_hoops_HCRPR					_hoops_GIAIR;
		bool					_hoops_RGAHA;
	}						_hoops_IHAIR;

#define _hoops_RSSRP				(_hoops_ASSRP)0x00000001
#define _hoops_PSSRP			(_hoops_ASSRP)0x00000002
#define _hoops_HSSRP		(_hoops_ASSRP)0x00000004
#define _hoops_ISSRP		(_hoops_ASSRP)0x00000010
#define _hoops_CSSRP			0		/* _hoops_SGCRP */
#define _hoops_AHIGA		1
#define _hoops_SSSRP		2
#define _hoops_GGGAP 3
#define _hoops_RGGAP		0
#define _hoops_AGGAP		1
#define _hoops_GAIGA		2
#define _hoops_AAIGA			3
	struct {
		_hoops_ASSRP		mask,
								value;
		int						level;
		int						_hoops_SRIGA;
		float					tolerance;
	}						_hoops_PRIGA;

#define _hoops_PGGAP				(_hoops_HGGAP)0x00000001
#define _hoops_IGGAP					(_hoops_HGGAP)0x00000002
#define _hoops_CGGAP					(_hoops_HGGAP)0x00000004
#define _hoops_SGGAP					(_hoops_HGGAP)0x00000008
#define _hoops_GRGAP				(_hoops_HGGAP)0x00000010
#define _hoops_RRGAP			(_hoops_HGGAP)0x00000020
#define _hoops_ARGAP				(_hoops_HGGAP)0x00000040
#define _hoops_PRGAP	(_hoops_HGGAP)0x00000080

#define _hoops_HRGAP				0
#define _hoops_IRGAP				1
#define _hoops_CRGAP				2
	struct _hoops_SRGAP {
		_hoops_HGGAP		mask,
								value;
		_hoops_ARPA					plane;
		Vector					light;
		struct {
			_hoops_HCRPR					name;
			RGB						rgb;	/* _hoops_ISHI & _hoops_RCSR _hoops_HHHR _hoops_RPP _hoops_PCCIR _hoops_PAHGA _hoops_CIHA */
		}						color;
		float					_hoops_IRIR;

		int						_hoops_RGP;
		int						_hoops_HAP;
		int						_hoops_IGGGR;
	}						_hoops_GHSS;

#define _hoops_GAGAP			(_hoops_RAGAP)0x00000001
#define _hoops_AAGAP			(_hoops_RAGAP)0x00000002
#define _hoops_PAGAP		(_hoops_RAGAP)0x00000004
#define _hoops_HAGAP			(_hoops_RAGAP)0x00000008
#define _hoops_IAGAP	(_hoops_RAGAP)0x00000010

	struct {
		_hoops_RAGAP		mask,
								value;
		int						_hoops_HAP;
		int						_hoops_CAP;
	}						_hoops_HRR;

#define _hoops_CAGAP		(_hoops_SAGAP)0x00000001
#define _hoops_GPGAP			(_hoops_SAGAP)0x00000002
#define _hoops_RPGAP		(_hoops_SAGAP)0x00000004
#define _hoops_APGAP		(_hoops_SAGAP)0x00000008
#define _hoops_PPGAP	(_hoops_SAGAP)0x00000010
#define _hoops_HPGAP		(_hoops_SAGAP)0x00000020
#define _hoops_IPGAP	(_hoops_SAGAP)0x00000040

	struct _hoops_CPGAP {
		_hoops_SAGAP	mask,
								value;
		_hoops_ARPA					plane;
		float					_hoops_IRIR;
		float					hither, yon;
		int						_hoops_IGGGR;
		struct _hoops_SPGAP {
			_hoops_ACHR				mask,
									value;
		}						_hoops_RGP;
	}						_hoops_RHGGR;
};


struct _hoops_SCAIR{
#define	_hoops_GHGAP					0x01
#define	_hoops_RHGAP		0x02
#define	_hoops_AHGAP	0x04
#define	_hoops_PHGAP			0x06

	int						mask;
	int						value;

	float					_hoops_GCIPR;

	struct {
#define _hoops_HHGAP		(_hoops_IHGAP)0x00000001
#define _hoops_CHGAP				(_hoops_IHGAP)0x00000002
#define _hoops_SHGAP	(_hoops_IHGAP)0x00000004
#define _hoops_GIGAP		(_hoops_IHGAP)0x00000008
#define _hoops_RIGAP			(_hoops_IHGAP)0x00000010
#define _hoops_AIGAP			(_hoops_IHGAP)0x00000020

		_hoops_IHGAP		mask,
								value;
		int						_hoops_PPPI;
		int						_hoops_HPPI;
		float					_hoops_IPPI;		/* _hoops_CARA _hoops_GC */
		float					_hoops_CPPI;			/* _hoops_ASIPR */
		float					_hoops_SPPI;			/* _hoops_SCGA [0..1] _hoops_PRISA _hoops_GC */
	}						_hoops_APPI;


#define _hoops_PIGAP	(_hoops_HIGAP)0x00000001
#define _hoops_IIGAP			(_hoops_HIGAP)0x00000002
#define _hoops_CIGAP		(_hoops_HIGAP)0x00000004
#define _hoops_SIGAP			(_hoops_HIGAP)0x00000008
#define _hoops_GCGAP			(_hoops_HIGAP)0x00000010
#define _hoops_RCGAP					(_hoops_HIGAP)0x00000020
	struct {
		_hoops_HIGAP		mask,
								value;
		_hoops_AIIAA configs;
	}						_hoops_PSRIR;

#define _hoops_ACGAP			0x00000001
#define _hoops_PCGAP				0x00000002
#define _hoops_HCGAP		0x00000004
#define _hoops_ICGAP				(_hoops_ACGAP|_hoops_PCGAP)
	struct {
		_hoops_CCGAP		mask;
		int						cylinder[_hoops_IGAIR];
		int						sphere[_hoops_IGAIR];
	}						_hoops_GAICA;
};


struct _hoops_SCGAP {
	_hoops_GSGAP		clear, set;
};


struct _hoops_RHAIR : public Attribute {
#	define _hoops_AHGI					(_hoops_GHGI)0xC0000000
#	define _hoops_RSGAP				(_hoops_GHGI)0x00000000
#	define _hoops_ASGAP					(_hoops_GHGI)0x40000000
#	define _hoops_PSGAP			(_hoops_GHGI)0x80000000
#	define _hoops_HSGAP					(_hoops_GHGI)0xC0000000

	_hoops_GHGI				_hoops_SCIAA,
							_hoops_RSIAA;
#	define _hoops_GSIAA					(_hoops_GHGI)0x00000001
#	define _hoops_GGICA					(_hoops_GHGI)0x00000002
#	define _hoops_ARICA			(_hoops_GHGI)0x00000004
#	define _hoops_HRICA				(_hoops_GHGI)0x00000008
#	define _hoops_IGICA			(_hoops_GHGI)0x00000010
#	define _hoops_SGICA					(_hoops_GHGI)0x00000020
#	define _hoops_AGICA				(_hoops_GHGI)0x00000040
#	define _hoops_IRICA			(_hoops_GHGI)0x00000080
#	define _hoops_CRICA			(_hoops_GHGI)0x00000100
#	define _hoops_RRICA			(_hoops_GHGI)0x00000200
#	define _hoops_SRICA			(_hoops_GHGI)0x00000400
#	define _hoops_CSHCA			(_hoops_GHGI)0x00000800
#	define _hoops_ISGAP				(_hoops_GHGI)0x00001000
#	define _hoops_CSGAP				(_hoops_GHGI)0x00002000
#	define _hoops_SSGAP		(_hoops_GHGI)0x00004000
#   define _hoops_GGRAP					(_hoops_GHGI)0x00010000
#	define _hoops_RGRAP					(_hoops_GHGI)0x00020000
#	define _hoops_AGRAP				(_hoops_GHGI)0x00040000
#	define _hoops_PRICA				(_hoops_GHGI)0x00080000
#	define _hoops_PGRAP				(_hoops_GHGI)0x00100000
#	define _hoops_HGRAP				(_hoops_GHGI)0x10000000
#	define _hoops_IGRAP				(_hoops_GHGI)0x20000000
#	define _hoops_CGRAP	(_hoops_GHGI)0xC0000000

/* '_hoops_SPIGA' _hoops_APSH _hoops_PII _hoops_IRS _hoops_CASH-_hoops_PAPA _hoops_HCSP, _hoops_HIH _hoops_HRGR _hoops_GCSS _hoops_RRGI _hoops_SGRAP, _hoops_HIS _hoops_GII _hoops_HSGS _hoops_PIRA _hoops_ARI */
#	define _hoops_GRRAP							(_hoops_GHGI)0x00000021

	_hoops_GHGI				_hoops_PSHCA,
							_hoops_RRRAP;
#	define _hoops_ARRAP						(_hoops_GHGI)0x40000001
#	define _hoops_HPH		(_hoops_GHGI)0x40000002
#	define _hoops_PRRAP							(_hoops_GHGI)0x40000004
#	define _hoops_HRRAP					(_hoops_GHGI)0x40000008
#	define _hoops_IRRAP					(_hoops_GHGI)0x40000010
#	define _hoops_CRRAP				(_hoops_GHGI)0x40000020
#	define _hoops_HAI				(_hoops_GHGI)0x40000040
#	define _hoops_SRRAP					(_hoops_GHGI)0x40000080
#	define _hoops_GARAP					(_hoops_GHGI)0x40000100
#	define _hoops_RARAP						(_hoops_GHGI)0x40000200
#	define Rendo_LOCAL_VIEWER					(_hoops_GHGI)0x40000400
#	define _hoops_AARAP			(_hoops_GHGI)0x40000800
#	define _hoops_CSGGA			(_hoops_GHGI)0x40001000
#	define _hoops_PARAP					(_hoops_GHGI)0x40002000
#	define _hoops_HARAP							(_hoops_GHGI)0x40004000
#	define _hoops_IARAP				(_hoops_GHGI)0x40008000
#	define _hoops_CARAP						(_hoops_GHGI)0x40010000
#	define _hoops_SARAP			(_hoops_GHGI)0x40020000
#	define _hoops_GPRAP				(_hoops_GHGI)0x40040000
#	define _hoops_RPRAP				(_hoops_GHGI)0x40080000
#	define _hoops_APRAP					(_hoops_GHGI)0x40100000
#	define _hoops_PPRAP				(_hoops_GHGI)0x40200000
#	define _hoops_HPRAP				(_hoops_GHGI)0x40400000
#	define _hoops_IPRAP			(_hoops_GHGI)0x40800000
#	define _hoops_CRI			(_hoops_GHGI)0x41000000
#	define _hoops_CPRAP			(_hoops_GHGI)0x42000000
#	define _hoops_SPRAP			(_hoops_GHGI)0x44000000

	_hoops_GHGI				_hoops_ISHCA,
							_hoops_GHRAP;
#	define _hoops_RHRAP		(_hoops_GHGI)0x80000001
#	define _hoops_SSRC			(_hoops_GHGI)0x80000002
#	define _hoops_HIRC			(_hoops_GHGI)0x80000004
#	define _hoops_AHRAP				(_hoops_GHGI)0x80000007

#	define _hoops_PHRAP	(_hoops_GHGI)0x80000010
#	define _hoops_CSRC	(_hoops_GHGI)0x80000020
#	define _hoops_PHGI	(_hoops_GHGI)0x80000040
#	define _hoops_HHRAP			(_hoops_GHGI)0x80000070
#	define _hoops_IHRAP			(_hoops_GHGI)0x80000080

#	define _hoops_CHRAP		(_hoops_GHGI)0x80000100
#	define _hoops_RGAC		(_hoops_GHGI)0x80000200
#	define _hoops_GSRC		(_hoops_GHGI)0x80000400
#	define _hoops_SHRAP				(_hoops_GHGI)0x80000700

#	define _hoops_GIRAP				(_hoops_GHGI)0x80000111
#	define _hoops_RIRAP				(_hoops_GHGI)0x80000222
#	define _hoops_AIRAP				(_hoops_GHGI)0x80000444

#	define _hoops_PIRAP				(_hoops_GHGI)0x80000777


#	define _hoops_GCP						(_hoops_GHGI)0x80010000
#	define _hoops_HIRAP						(_hoops_GHGI)0x80020000
#	define _hoops_RCP						(_hoops_GHGI)0x80040000
#	define _hoops_SSA						(_hoops_GHGI)0x80080000
#	define _hoops_IIRAP						(_hoops_GHGI)0x80100000
#	define _hoops_GGP						(_hoops_GHGI)0x80200000
#	define _hoops_CIRAP				(_hoops_GHGI)0x803F0000


	Quantization_Flags		_hoops_SIRAP;
#	define Quantization_THRESHOLD				(Quantization_Flags)0x01
#	define Quantization_DITHER					(Quantization_Flags)0x02
#	define Quantization_ERROR_DIFFUSION			(Quantization_Flags)0x04

	_hoops_GCRAP		_hoops_RCRAP;
#	define		_hoops_ACRAP						(_hoops_GCRAP)0x01
#	define		_hoops_PCRAP					(_hoops_GCRAP)0x02
#	define		_hoops_HCRAP					(_hoops_GCRAP)0x04
#	define		_hoops_ICRAP		(_hoops_GCRAP)0x08

	_hoops_GSGAP				_hoops_IRARR;
#	define		_hoops_CCRAP			(_hoops_GSGAP)0x00000002
#	define		_hoops_SCRAP		(_hoops_GSGAP)0x00000008
#	define		_hoops_GSRAP	(_hoops_GSGAP)0x00000010
#	define		_hoops_RSRAP		(_hoops_GSGAP)0x00000020
#	define		_hoops_ASRAP			(_hoops_GSGAP)0x00000040
#	define		_hoops_PSRAP					(_hoops_GSGAP)0x00000080
	/*
	 * _hoops_IPCP _hoops_HSPR _hoops_CHR _hoops_IH _hoops_HSRAP _hoops_HHCPR.
	 * _hoops_PAAS _hoops_ARP, _hoops_SSIA _hoops_ICHRR-_hoops_GGSR _hoops_SASI _hoops_GCAC _hoops_SICAR _hoops_CCA _hoops_IRS "_hoops_ASRC".
	 */
#	define		_hoops_ISRAP		(_hoops_GSGAP)0x00010000
#	define		_hoops_RSSIR				(_hoops_GSGAP)0x00020000
#	define		_hoops_CSRAP			(_hoops_GSGAP)0x00040000
#	define		_hoops_SSRAP					(_hoops_GSGAP)0x00080000
#	define		_hoops_GGAAP		(_hoops_GSGAP)0x00100000
#	define		_hoops_IPIGA					(_hoops_GSGAP)0x00200000
#	define		_hoops_PSGCR				(_hoops_GSGAP)0x00400000
#	define		_hoops_RGAAP					(_hoops_GSGAP)0x00800000
#	define		_hoops_AGAAP				(_hoops_GSGAP)0x01000000


	/* _hoops_HHH _hoops_SGI _hoops_IH _hoops_AIRI _hoops_HIGR _hoops_PGAAP */
#	define Rendo_TRISTRIP_MASK (_hoops_GGP|_hoops_SSA|_hoops_IIRAP|_hoops_GSRC)
#	define _hoops_RHII (_hoops_RCP|_hoops_GCP|_hoops_HIRAP|_hoops_RGAC)
#	define _hoops_HGAAP (_hoops_RHRAP)
#   define _hoops_HCSI ((_hoops_PHGI|_hoops_IHRAP) & ~_hoops_AHGI)

	Integer32				_hoops_CHIH;
	Integer32				_hoops_IGAAP;
	Integer32				_hoops_SHIH;



	_hoops_SHCRP			_hoops_SRI;
#	define		_hoops_CGAAP						(_hoops_SHCRP)0x0000
#	define		_hoops_SGAAP			(_hoops_SHCRP)0x0001
#	define		_hoops_GRAAP					(_hoops_SHCRP)0x0002
#	define		_hoops_RRAAP			(_hoops_SHCRP)0x0004
#	define		_hoops_ARAAP					(_hoops_SHCRP)0x0008
#	define		_hoops_HSSS					(_hoops_SHCRP)0x0010
#	define		_hoops_GAI					(_hoops_SHCRP)0x0020
#	define		_hoops_PRAAP					(_hoops_SHCRP)0x0040
#	define		_hoops_SICI				(_hoops_SHCRP)0x0080
#	define		_hoops_PIII				(_hoops_SHCRP)0x0100	/* _hoops_RGAR _hoops_IH _hoops_IHSP */
#	define		_hoops_HRAAP					(_hoops_SHCRP)0x8000

	struct {
#	define		_hoops_IRAAP				0x0000
#	define		_hoops_GPSP			0x0001
#	define		_hoops_CRAAP				0x0002
#	define		_hoops_SHP				0x0004
#	define		_hoops_SRAAP				(_hoops_GPSP|_hoops_CRAAP|_hoops_SHP)
#	define		_hoops_GAAAP		(_hoops_GPSP|_hoops_CRAAP|_hoops_SHP)

		short					mask,
								value;
	}						_hoops_CHP;

	struct {
		short					mask,
								value;
#	define		_hoops_RAAAP				0x0001
#	define		_hoops_AAAAP				0x0002
#	define		_hoops_PAAAP			0x0004 /* _hoops_HAR _hoops_IGI */
#	define		_hoops_HAAAP		0x0008
#	define		_hoops_IAAAP	0x0010
#	define		_hoops_CAAAP	0x0018
#	define		_hoops_SAAAP			0x0020
#   define      _hoops_GPAAP      0x0040

		char					style;
#	define		_hoops_AIII				0
#	define		Transparency_STYLE_BLENDING			1
#	define		_hoops_GCPI		2

		_hoops_SHCRP		_hoops_SRI;	/* _hoops_PACIA _hoops_CSSC _hoops_RIR _hoops_GSSR _hoops_SHASA _hoops_ARRS */

		int						_hoops_RPAAP;
		float					_hoops_APAAP;
	}						_hoops_SSHCA;

	struct {
		_hoops_PPAAP			mask,
								value;
#	define		_hoops_HPAAP				(_hoops_PPAAP)0x01
#	define		_hoops_IPAAP				(_hoops_PPAAP)0x02
#	define		_hoops_CPAAP				(_hoops_PPAAP)0x04
		int						_hoops_SPAAP;

		int						_hoops_GHAAP;
#	define		_hoops_RHAAP		(_hoops_AHAAP)0x01
#	define		_hoops_PHAAP			(_hoops_AHAAP)0x02
	}						_hoops_RGICA;

	_hoops_PHAIR *			_hoops_PRSI;

	_hoops_HIAIR *			_hoops_AIAIR;

	_hoops_RIAIR *		_hoops_HHAIR;

	_hoops_SCAIR *	geometry;

	_hoops_CCAIR *		locks;

	_hoops_ICAIR *		_hoops_IIAIR;

	float					_hoops_CSRS;

	float					_hoops_HHAAP[2];
	_hoops_PACIR		_hoops_HCIH;
	float					_hoops_IHAAP[2];
	RGB						_hoops_CHAAP;
	RGB						_hoops_HRA;

	short					_hoops_SHAAP, _hoops_GIAAP;
	_hoops_AHAH					_hoops_IHRH;

#define _hoops_RIAAP			0x01
#define _hoops_AIAAP			0x02
#define _hoops_PIAAP		0x04
#define _hoops_HIAAP		0x08
#define _hoops_IIAAP				0x10
#define _hoops_CIAAP			0x20
#define _hoops_SIAAP		0x40

#define _hoops_GCAAP					0x00
#define _hoops_RCAAP					0x0F
#define _hoops_ACAAP					0x70
#define _hoops_PCAAP					0x11
#define _hoops_HCAAP				0x22
#define _hoops_ICAAP				0x44
#define _hoops_CCAAP				0x08
#define _hoops_SCAAP						0x7F

	int						_hoops_PGICA;
	int						_hoops_HGICA;

	int						_hoops_GSAAP;
	int						_hoops_RSAAP;

#	define Display_List_NONE					0
#	define Display_List_GEOMETRY				1
#	define Display_List_SEGMENT					2
#	define _hoops_ASAAP			3
	int						_hoops_PSAAP;


	_hoops_SCGAP *	_hoops_PSHRP;


#ifndef DISABLE_AIR_OPTIONS
#	define _hoops_HSAAP			(_hoops_ISAAP)0x0001
#	define _hoops_CSAAP			(_hoops_ISAAP)0x0002
#	define _hoops_SSAAP				(_hoops_ISAAP)0x0004
#	define _hoops_GGPAP		(_hoops_ISAAP)0x0008
#	define _hoops_RGPAP					(_hoops_ISAAP)0x0010
#	define _hoops_AGPAP		(_hoops_ISAAP)0x0020
#	define _hoops_PGPAP		(_hoops_ISAAP)0x0040
#	define _hoops_HGPAP					(_hoops_ISAAP)0x0080
#	define _hoops_IGPAP					(_hoops_ISAAP)0x0100
#	define _hoops_CGPAP		(_hoops_ISAAP)0x0200
#	define _hoops_SGPAP					(_hoops_ISAAP)0x0400

#	define _hoops_GRPAP				(_hoops_RRPAP)0x0001
#	define _hoops_ARPAP			(_hoops_RRPAP)0x0002
#	define _hoops_PRPAP				(_hoops_RRPAP)0x0004
#	define _hoops_HRPAP				(_hoops_RRPAP)0x0008
#	define _hoops_IRPAP		(_hoops_RRPAP)0x0010
#	define _hoops_CRPAP				(_hoops_RRPAP)0x0020
#	define _hoops_SRPAP					(_hoops_RRPAP)0x0040

#	define _hoops_GAPAP			(_hoops_RRPAP)0x01

#	define _hoops_RAPAP				(_hoops_RRPAP)0x00
#	define _hoops_AAPAP				(_hoops_RRPAP)0x01
#	define _hoops_PAPAP						(_hoops_RRPAP)0x02
#	define _hoops_HAPAP				(_hoops_RRPAP)0x03
#	define _hoops_IAPAP					(_hoops_RRPAP)0x03
#	define _hoops_CAPAP						(_hoops_RRPAP)0x04

#endif
};

typedef Integer32 _hoops_SAPAP;

#define _hoops_GPPAP					(_hoops_SAPAP)0x00000001
#define _hoops_RPPAP					(_hoops_SAPAP)0x00000002
#define _hoops_APPAP		(_hoops_SAPAP)0x00000004
#define _hoops_PPPAP			(_hoops_SAPAP)0x00000008
#define _hoops_HPPAP				(_hoops_SAPAP)0x00000010
#define _hoops_IPPAP			(_hoops_SAPAP)0x00000020
#define _hoops_CPPAP			(_hoops_SAPAP)0x00000040
#define _hoops_SPPAP				(_hoops_SAPAP)0x00000080
#define _hoops_GHPAP		(_hoops_SAPAP)0x00000100
#define _hoops_RHPAP			(_hoops_SAPAP)0x00000200
#define _hoops_AHPAP			(_hoops_SAPAP)0x00000400
#define _hoops_PHPAP				(_hoops_SAPAP)0x00000800
#define _hoops_HHPAP			(_hoops_SAPAP)0x00001000
#define _hoops_IHPAP		(_hoops_SAPAP)0x00002000
#define _hoops_CHPAP				(_hoops_SAPAP)0x00004000
#define _hoops_SHPAP			(_hoops_SAPAP)0x00008000
#define _hoops_GIPAP		(_hoops_SAPAP)0x00010000
#define _hoops_RIPAP			(_hoops_SAPAP)0x00020000
#define _hoops_AIPAP					(_hoops_SAPAP)0x00040000
#define _hoops_PIPAP				(_hoops_SAPAP)0x00080000
#define _hoops_HIPAP				(_hoops_SAPAP)0x00100000
#define _hoops_IIPAP		(_hoops_SAPAP)0x00200000
#define _hoops_CIPAP			(_hoops_SAPAP)0x00400000

typedef	char	_hoops_SIPAP, _hoops_GCPAP, _hoops_RCPAP;

struct _hoops_AGPIR : public Attribute {
	_hoops_IGPIR		*_hoops_HGPIR;

	float				size;
	float				_hoops_ACPAP;
	float				_hoops_PCPAP;
	float				_hoops_HCPAP;
	float				rotation;
	float				width_scale;
	float				_hoops_ICPAP;
	float				_hoops_IPGRP;

	_hoops_SAPAP		_hoops_HAICA, _hoops_CPGRP;

	float				_hoops_CCPAP;
	float				_hoops_SCPAP;

	/* (_hoops_PPSI _hoops_HCR _hoops_RH "_hoops_GSPR" _hoops_APSAR _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HRPR) */

	_hoops_GSPAP	transform;		/* _hoops_HSRS _hoops_SPR */

#define _hoops_RSPAP		(_hoops_SIPAP)0
#define _hoops_ASPAP		(_hoops_SIPAP)1
#define _hoops_PSPAP		(_hoops_SIPAP)2
#define _hoops_HSPAP		(_hoops_SIPAP)3
	_hoops_SIPAP	_hoops_ISPAP[2];

	_hoops_RCPAP	_hoops_CSPAP[2];

	_hoops_SPGRP	_hoops_GHGRP;
	_hoops_SPGRP	_hoops_SSPAP;
	_hoops_SPGRP	_hoops_GGHAP;
	_hoops_SPGRP	_hoops_RGHAP;
	_hoops_SPGRP	_hoops_AGHAP;
	_hoops_SPGRP	_hoops_PGHAP;

#define	_hoops_HGHAP		(_hoops_GCPAP)0
#define	_hoops_IGHAP		(_hoops_GCPAP)1
#define	_hoops_CGHAP			(_hoops_GCPAP)2
	_hoops_GCPAP	_hoops_SGHAP;
};




#define _hoops_SHGRA			(Type)0
#define _hoops_PPCA			(Type)1
#define _hoops_GIGRA			(Type)2

struct _hoops_ACSGA {
	_hoops_ACSGA *		next;
	void *				_hoops_PPRPR;
	Color_Object		_hoops_GHA;
	Type				type;
};

struct _hoops_PCSGA : public _hoops_ACSGA {
	_hoops_ACGHR	value;
};

struct _hoops_APCA : public _hoops_ACSGA {
	RGB					rgb;
	_hoops_HCRPR				name;
};

struct _hoops_HCSGA : public _hoops_ACSGA {
	Named_Material		_hoops_ISHIR;
	_hoops_HCRPR				name;
};



struct _hoops_SSGI : public Attribute {
	Color_Object		_hoops_GHA,
						_hoops_CCCIR;
	_hoops_ACSGA *		colors;
};




struct _hoops_RHAH : public Attribute {
	int					length;
	// _hoops_IPPSA->_hoops_GRHAP _hoops_HPGR _hoops_GHIR _hoops_IIGR _hoops_ICRP _hoops_RPAI _hoops_AGRP
	Integer32			time_stamp;
	Named_Material *	_hoops_HAA;
	void *				_hoops_PPRPR;

	_hoops_ARGRA	_hoops_SRHRA;
};


struct _hoops_RGPIR : public Attribute {
	Vector				value;
};



struct _hoops_GCHIR : public Attribute {
	_hoops_IHACR *				_hoops_ACHIR;
};

typedef int _hoops_RRHAP;

struct _hoops_HCHIR : public _hoops_HGHGP<_hoops_HCHIR, _hoops_IGHGP> {
	_hoops_IRPCR		address;
	_hoops_HCRPR				name;
};



#define _hoops_GIHCR	   _hoops_HCIGP(1)

struct _hoops_HHRA : public Attribute {
#define _hoops_CGHCR			0
#define _hoops_SGHCR		1
#define _hoops_PRHCR		2
#define _hoops_HRHCR		3
#define _hoops_IRHCR			4
#define _hoops_CRHCR	5
#define _hoops_SRHCR	6

#define _hoops_GAHCR			7
#define _hoops_AAHCR			8
#define _hoops_IAHCR			9
#define _hoops_CAHCR			10
#define _hoops_SAHCR			11

	Point				position,
						target;			/* _hoops_GHCA _hoops_SHH == _hoops_AHC */
	Vector				up_vector;		/* _hoops_SCGA */
	float				_hoops_ISPA,
						_hoops_SSPA;			/* (_hoops_GHCA _hoops_SHH _hoops_AHHR) */

#	define		_hoops_GHH	0
#	define		_hoops_CPPCR 1
#	define		_hoops_SSIH	2
	int					projection;
	float				_hoops_HHCH,
						_hoops_IHCH;
	float				_hoops_CIPCR;
	float const *		_hoops_SIPCR;

	/* _hoops_PHPHA _hoops_SIHC... */
	Vector				_hoops_IIPCR,			/* _hoops_SAAP - _hoops_AHC, _hoops_SCGA */
						_hoops_CRSS;	/* _hoops_SCGA */
	float				_hoops_SRIR,	/* _hoops_GHCA _hoops_SHH _hoops_AHHR */
						_hoops_ARSS, /* _hoops_PAIP / _hoops_ARHAP; _hoops_SHR _hoops_RIRA */
						_hoops_PRSS;
	float				_hoops_CSIH;
	_hoops_HRPA			_hoops_PRPA,		/* _hoops_PIISR _hoops_GGR _hoops_HPP _hoops_PRHAP-_hoops_IS-_hoops_HRHAP */
						_hoops_AIIH,		/* _hoops_PIISR _hoops_GGR _hoops_HPP _hoops_PRHAP-_hoops_IS-_hoops_HRHAP */
						_hoops_GRCC;		/* _hoops_PIISR _hoops_GGR _hoops_HPP _hoops_PRHAP-_hoops_IS-_hoops_HRHAP */
};


struct _hoops_IHACR {
	_hoops_IHACR *		next;
	/* _hoops_PAGA: 0 _hoops_HRGR _hoops_IGI _hoops_IH _hoops_PCCP _hoops_RIHH _hoops_ASRC _hoops_HPP _hoops_RH _hoops_GRPRA _hoops_SICAR,
	 * _hoops_HIS _hoops_HSPP _hoops_AGCR _hoops_RGGHR _hoops_HPGR 1. _hoops_HIPR: _hoops_IPCP _hoops_RIHH-_hoops_IPAC _hoops_IRHAP
	 * _hoops_GPP _hoops_AGCR _hoops_HSH _hoops_IHGS _hoops_ISIAR.
	 */
#	define		_hoops_SGPCR				1
#	define		_hoops_ARRCR				(_hoops_RRHAP)_hoops_SGPCR
#	define		_hoops_IRRCR				(_hoops_RRHAP)3
#	define		_hoops_CRRCR				(_hoops_RRHAP)4

#	define		_hoops_GARCR	(_hoops_RRHAP)5
#	define		_hoops_SRRCR		(_hoops_RRHAP)6

#	define		_hoops_RARCR				(_hoops_RRHAP)7
#	define		_hoops_AARCR		(_hoops_RRHAP)8
#	define		_hoops_PARCR		(_hoops_RRHAP)9
#	define		_hoops_HARCR		(_hoops_RRHAP)10
#	define		_hoops_IARCR			(_hoops_RRHAP)11
#	define		_hoops_CARCR	(_hoops_RRHAP)12
#	define		_hoops_SARCR	(_hoops_RRHAP)13
#	define		_hoops_GPRCR	(_hoops_RRHAP)14

#	define		_hoops_HHRCR		(_hoops_RRHAP)15
#	define		_hoops_IHRCR			(_hoops_RRHAP)16

#	define		_hoops_CHRCR					(_hoops_RRHAP)17
#	define		_hoops_SHRCR			(_hoops_RRHAP)18

#	define		_hoops_GIRCR					(_hoops_RRHAP)19

#	define		_hoops_RIRCR				(_hoops_RRHAP)20
#	define		_hoops_AIRCR			(_hoops_RRHAP)21
#	define		_hoops_HIRCR				(_hoops_RRHAP)22
#	define		_hoops_IIRCR				(_hoops_RRHAP)23
#	define		_hoops_PCRCR			(_hoops_RRHAP)24
#	define		_hoops_HCRCR			(_hoops_RRHAP)25
#	define		_hoops_ICRCR			(_hoops_RRHAP)26
#	define		_hoops_PSRCR			(_hoops_RRHAP)27

#	define		_hoops_HSRCR		(_hoops_RRHAP)28
#	define		_hoops_ISRCR			(_hoops_RRHAP)29

#	define		_hoops_CSRCR				(_hoops_RRHAP)30
#	define		_hoops_SSRCR			(_hoops_RRHAP)31

#	define		_hoops_GGACR			(_hoops_RRHAP)32
#	define		_hoops_RGACR			(_hoops_RRHAP)33
#	define		_hoops_AGACR			(_hoops_RRHAP)34
#	define		_hoops_PGACR				(_hoops_RRHAP)35
#	define		_hoops_HGACR			(_hoops_RRHAP)36
#	define		_hoops_IGACR					(_hoops_RRHAP)37

#	define		_hoops_CGACR				(_hoops_RRHAP)38

#	define		_hoops_SGACR				(_hoops_RRHAP)39
#	define		_hoops_GRACR			(_hoops_RRHAP)40
#	define		_hoops_GCRCR			(_hoops_RRHAP)41

#	define		_hoops_RRACR				(_hoops_RRHAP)42
#	define		_hoops_ARACR				(_hoops_RRHAP)43

#	define		_hoops_PRACR			(_hoops_RRHAP)44

#	define		_hoops_IRACR				(_hoops_RRHAP)45
#	define		_hoops_CRACR					(_hoops_RRHAP)46
#	define		_hoops_SRACR			(_hoops_RRHAP)47
#	define		_hoops_GAACR			(_hoops_RRHAP)48
#	define		_hoops_PAACR				(_hoops_RRHAP)49

#	define		_hoops_CCRCR				(_hoops_RRHAP)50
#	define		_hoops_SCRCR			(_hoops_RRHAP)51
#	define		_hoops_GSRCR		(_hoops_RRHAP)52
#	define		_hoops_RSRCR				(_hoops_RRHAP)53
#	define		_hoops_ASRCR				(_hoops_RRHAP)54

#	define		_hoops_RPRCR				(_hoops_RRHAP)55
#	define		_hoops_APRCR		(_hoops_RRHAP)56
#	define		_hoops_PPRCR		(_hoops_RRHAP)57
#	define		_hoops_HPRCR			(_hoops_RRHAP)58
#	define		_hoops_IPRCR		(_hoops_RRHAP)59
#	define		_hoops_HRRCR					(_hoops_RRHAP)60
#	define		_hoops_CPRCR			(_hoops_RRHAP)61
#	define		_hoops_SPRCR			(_hoops_RRHAP)62
#	define		_hoops_GHRCR				(_hoops_RRHAP)63
#	define		_hoops_RHRCR			(_hoops_RRHAP)64
#	define		_hoops_AHRCR					(_hoops_RRHAP)65
#	define		_hoops_PHRCR		(_hoops_RRHAP)66
#	define		_hoops_CRHAP						(_hoops_RRHAP)67

#	define		_hoops_GPACR				(_hoops_RRHAP)68

#	define		_hoops_SGRCR							(_hoops_RRHAP)69
#	define		_hoops_RPACR						(_hoops_RRHAP)70
#	define		_hoops_CIRCR						(_hoops_RRHAP)71
#	define		_hoops_SIRCR						(_hoops_RRHAP)72
#	define		_hoops_RCRCR						(_hoops_RRHAP)73
#	define		_hoops_ACRCR				(_hoops_RRHAP)74
#	define		_hoops_HRACR						(_hoops_RRHAP)75
#	define		_hoops_PIRCR				(_hoops_RRHAP)76

#	define		_hoops_HAACR						(_hoops_RRHAP)77
#	define		_hoops_IAACR							(_hoops_RRHAP)78
#	define		_hoops_CAACR						(_hoops_RRHAP)79
#	define		_hoops_SAACR						(_hoops_RRHAP)80

#	define		_hoops_APACR					(_hoops_RRHAP)81
#	define		_hoops_PPACR							(_hoops_RRHAP)82

#	define		_hoops_SRHAP					(_hoops_RRHAP)83
#	define		_hoops_GAHAP		(_hoops_RRHAP)84
#	define		_hoops_RAHAP							(_hoops_RRHAP)85
#	define		_hoops_AAHAP				(_hoops_RRHAP)86

#	define		_hoops_PAHAP					(_hoops_RRHAP)87

#	define		_hoops_HPACR						(_hoops_RRHAP)88

#	define		_hoops_GRPCR								_hoops_HPACR

	_hoops_RRHAP		type;
	_hoops_HCHIR *		name;
	bool				_hoops_PIACR;
	void const *		_hoops_AIACR;
};



#define _hoops_SGIIR		_hoops_HCIGP(1)

struct _hoops_PGIIR : public _hoops_HGHGP<_hoops_PGIIR, _hoops_IGHGP> {
	int					data_length;
	char const *		data;
	_hoops_HCHIR *		_hoops_HGIIR;
	_hoops_HCRPR				name;
	_hoops_IHGRP		encoding;
	char				_hoops_HAHAP;

	char const * const *_hoops_CGIIR;
	int					_hoops_IGIIR;
	bool				_hoops_IAHAP;
	float				_hoops_CSIH;
};

typedef void (HC_CDECL * _hoops_CAHAP)
				(char const * name, char const * data, Karacter _hoops_IPCSR, char const * alter * _hoops_SAHCA);

typedef void (HC_CDECL * _hoops_SAHAP)
				(int _hoops_GPHAP, int height, int _hoops_RPHAP,
				 int * _hoops_APHAP, int * _hoops_PPHAP, int * _hoops_HPHAP, char ** _hoops_SAHCA,
				 int _hoops_IPHAP, void * data);


#define _hoops_CPHAP(p)	_hoops_IRGCR(*(p))
#define _hoops_SPHAP(p)	((_hoops_IRGCR(*(p)) << 8) + \
						 _hoops_IRGCR(*((p)+1)))


struct _hoops_RHPIR : public Attribute {
	POINTER_SIZED_INT	data;
};

struct Metafile {
#	define		_hoops_GHHAP						(int)0x00000001
#	define		_hoops_RHHAP						(int)0x00000002
#	define		_hoops_AHHAP						(int)0x00000004
#	define		_hoops_PHHAP					(int)0x00000008
#	define		_hoops_HHHAP					(int)0x00000010
#	define		_hoops_IHHAP				(int)0x00000020
#	define		_hoops_CHHAP	(int)0x00000040
#	define		_hoops_SHHAP					(int)0x00000080
#	define		_hoops_GIHAP					(int)0x00000100
#	define		_hoops_RIHAP			(int)0x00000200
#	define		_hoops_AIHAP				(int)0x00000400
#	define		_hoops_PIHAP				(int)0x00000800
#	define		_hoops_HIHAP				(int)0x00001000
#	define		_hoops_IIHAP				(int)0x00002000
#	define		_hoops_CIHAP			(int)0x00004000
#	define		_hoops_SIHAP				(int)0x00008000
#	define		_hoops_GCHAP				(int)0x00010000
	int					mask,
						value;
#	define		_hoops_RCHAP				(int)0x0001
#	define		_hoops_ACHAP			(int)0x0002
#	define		_hoops_PCHAP			(int)0x0004
#	define		_hoops_HCHAP				(int)0x0008
#	define		_hoops_ICHAP				(int)0x0010
#	define		_hoops_CCHAP			(int)0x001F
	int					_hoops_HPCI,
						_hoops_SCHAP,
						_hoops_GSHAP,
						_hoops_RSHAP;
	unsigned int		_hoops_ASHAP;
	_hoops_HCRPR				name,
						_hoops_PSHAP,
						comment,
						_hoops_HSHAP,
						_hoops_ISHAP;

#	define		_hoops_CSHAP				0
#	define		_hoops_SSHAP			1
#	define		_hoops_GGIAP				2
	int					_hoops_RGIAP;
#	define		_hoops_AGIAP				0
#	define		_hoops_PGIAP			1
#	define		_hoops_HGIAP			2
	int					_hoops_IGIAP;
	bool				_hoops_CGIAP;
};

typedef Integer32		_hoops_SGIAP;		 /* _hoops_PAPR _hoops_GASAR _hoops_GGR "_hoops_IPHIA._hoops_GGHR" */

struct _hoops_RRPIR {
	_hoops_RRPIR		*next,
					*prev;
	KName			string;
};


enum {
	_hoops_GRIAP = 0,
	_hoops_RRIAP = 1,
	_hoops_ARIAP = 2,
	_hoops_PRIAP = 3
};


#define _hoops_HISAA(_thread_data_,_hoops_HRIAP, _hoops_IRIAP, _hoops_CRIAP) \
	((_hoops_HRIAP)->connected_action)((_thread_data_),(_hoops_GGAGR alter*)(_hoops_HRIAP), _hoops_IRIAP, _hoops_CRIAP)

struct _hoops_GGAGR : public Attribute {
	_hoops_SRIAP *		_hoops_GRPIR; // _hoops_IH _hoops_GIARR _hoops_HGISR

	_hoops_SRIAP *		_hoops_ACARR; // _hoops_IH _hoops_HGISR _hoops_PPR _hoops_AIRI _hoops_HIGR _hoops_GGAS

	unsigned Integer32	_hoops_GPPI;
	unsigned Integer32	_hoops_GAIAP;

	_hoops_SGIAP		_hoops_CGPIR;
	_hoops_GGAGR *				_hoops_CISHA;
	_hoops_GGAGR **			_hoops_RAIAP;

	Driver_Action		action;
	Driver_Action		connected_action;
	Driver_Action		_hoops_AAIAP;	/* _hoops_IH _hoops_PGCR-_hoops_PAPA _hoops_SPSIR (_hoops_PAIAP) */

	void *				_hoops_PPRPR;
	void *				_hoops_HAIAP;	/* _hoops_IGI _hoops_RGAR _hoops_HPP _hoops_IAIAP */

	_hoops_AGCI *	_hoops_RGAGR;
	int							_hoops_CAIAP;

	struct _hoops_SAIAP {
		_hoops_GGAGR *				target;

		int					_hoops_GPIAP,
							_hoops_RPIAP,
							_hoops_APIAP,
							_hoops_PPIAP;

		int					_hoops_HPIAP,
							_hoops_IPIAP;

		int *				_hoops_IRPIR;

		Integer32			_hoops_CPIAP;

		int					_hoops_SPIAP;
		_hoops_PIGPR *		_hoops_SRPIR;
		int					_hoops_GHIAP;
	}	_hoops_RCSHR, _hoops_CPCR;

	int					_hoops_RHIAP;
	KName				_hoops_HRPIR;
	_hoops_RRPIR *		_hoops_ARPIR;
	_hoops_RRPIR *		_hoops_AHIAP;
	_hoops_RRPIR *		_hoops_PHIAP;
	int					_hoops_HHIAP;

	bool				_hoops_IHIAP;

	_hoops_APSHA		_hoops_CHIAP;				/* _hoops_GCHRR _hoops_IIGR _hoops_RH _hoops_ARRS */

	_hoops_APSHA		_hoops_SHIAP;

	struct {
		_hoops_APSHA		action;
		float				x, y;
		int					status;
	}					_hoops_GIIAP;

	Activity			_hoops_RIIAP;

	Window				_hoops_CSGPR;	/* _hoops_IS _hoops_CRCC _hoops_AIIAP _hoops_CPSRR _hoops_SGI _hoops_AHI */



	Karacter			_hoops_PIIAP;
	char				_hoops_HIIAP;
};

struct _hoops_IHSCA : CMO {
	_hoops_IHSCA(void const * in_data, long _hoops_IIIAP): data(0), data_length(0) {
		if (_hoops_IIIAP > 0 && in_data != null) {
			data_length = _hoops_IIIAP;
			ALLOC_ARRAY (data, data_length, char);
			COPY_MEMORY(in_data, data_length, data);
		}
	};

	~_hoops_IHSCA() {
		if (data_length > 0)
		FREE_ARRAY(data, data_length, char);
	};

	void *	data;
	long	data_length;
};


#define _hoops_CIIAP	0x01
#define _hoops_SIIAP	0x02
#define _hoops_GCIAP	0x04
#define _hoops_RCIAP		0x08
#define _hoops_ACIAP		(_hoops_CIIAP|_hoops_SIIAP|_hoops_GCIAP|_hoops_RCIAP)
#define _hoops_PCIAP	0x10

struct _hoops_HPPIR : public Attribute {
	Option_Value *			option_list;
	Option_Value *			_hoops_APICA;
	_hoops_PGGSA *			_hoops_AGGSA;
	_hoops_GISCA *	_hoops_HGGSA;

	_hoops_CGGSA *		_hoops_IGGSA; // _hoops_IGI _hoops_IH _hoops_CRGH _hoops_GCHRR

	int						_hoops_PRGCA; // _hoops_IGI _hoops_HPP _hoops_SGGC
};


#define _hoops_PRPCA	0x0001
#define _hoops_RSACA			0x8000

#define _hoops_CRPCA	1

struct _hoops_PCACA {
	_hoops_PCACA *	next;
	_hoops_CCPCA				condition;
	short					type;
	short					flags;
};

struct _hoops_SPPIR : public Attribute {

	_hoops_PCACA *	_hoops_ACPGR;

	unsigned int *			_hoops_SGCAA;
	unsigned int *			values;
	int						count;

	int						_hoops_PRGCA; // _hoops_IGI _hoops_HPP _hoops_SGGC
};



typedef int _hoops_HCIAP;
#define _hoops_ICIAP			(_hoops_HCIAP)0x00000000
#define _hoops_CCIAP			(_hoops_HCIAP)0x00000001
#define _hoops_PAGS		(_hoops_HCIAP)0x00000002
#define _hoops_HAGS			(_hoops_HCIAP)0x00000004
#define _hoops_SCIAP		(_hoops_HCIAP)0x00000008
#define _hoops_GSIAP			(_hoops_HCIAP)0x00000010
#define _hoops_RSIAP		(_hoops_HCIAP)0x00000020
#define	_hoops_IGGS		(_hoops_HCIAP)0x00000040

#define _hoops_GRAI (_hoops_PAGS|_hoops_HAGS|_hoops_SCIAP)

#define _hoops_ASIAP				1
#define _hoops_PSIAP			0
#define _hoops_HSIAP			-1
#define _hoops_ISIAP		-2
#define _hoops_CSIAP			-3
#define _hoops_SSIAP		-4
#define _hoops_GGCAP			-5
#define _hoops_RGCAP		-6
#define _hoops_AGCAP		-7
#define _hoops_PGCAP		-8
#define _hoops_HGCAP		-9
#define _hoops_IGCAP			-10
#define _hoops_CGCAP		-11
#define _hoops_SGCAP			-12


#define GLYPH_RADIUS(glyph) (int)(glyph)->data[0]
#define GLYPH_HOTSPOT_X(glyph) (int)(glyph)->data[1]
#define GLYPH_HOTSPOT_Y(glyph) (int)(glyph)->data[2]
#define GLYPH_OPS(glyph) (&((glyph)->data[3]))

struct _hoops_GRCAP : public _hoops_ICAGP {
	_hoops_HCRPR				name;
	Integer32			key;
	_hoops_HCIAP			flags;
	char *				data;
	unsigned int		length;
	float				scale;

	_hoops_GRCAP () : _hoops_ICAGP () {}
	~_hoops_GRCAP () {
		_hoops_RGAIR (name);
		if (length > 0)
			FREE_ARRAY (data, length, char);
	}

private:
	_hoops_GRCAP (_hoops_GRCAP const &);
};
typedef Counted_Pointer<_hoops_GRCAP>	_hoops_GASC;


struct _hoops_AAAIR : public Attribute {
	_hoops_GASC *				glyphs;
	Integer32 *			keys;
	int					count;
};

struct _hoops_RRCAP : public _hoops_ICAGP {
	_hoops_HCRPR				name;
	Integer32			key;

	_hoops_CRCP *			segment;

	_hoops_RRCAP () : _hoops_ICAGP () {}
	~_hoops_RRCAP () {
		_hoops_RGAIR (name);
		_hoops_HPRH(segment);
	}

private:
	_hoops_RRCAP (_hoops_RRCAP const &);
};
typedef Counted_Pointer<_hoops_RRCAP>	_hoops_GPAIR;

struct _hoops_IAAIR : public Attribute {
	_hoops_GPAIR *		_hoops_SAAIR;
	Integer32 *			keys;
	int					count;
};




typedef int Line_Style_Flags;
#define LSF_NONE				(Line_Style_Flags)0x00000000
#define LSF_SOLID				(Line_Style_Flags)0x00000001
#define LSF_BITS16				(Line_Style_Flags)0x00000002
#define LSF_BITS32				(Line_Style_Flags)0x00000004
#define LSF_ABSOLUTE_LENGTH		(Line_Style_Flags)0x00000008
#define LSF_ABSOLUTE_WEIGHT		(Line_Style_Flags)0x00000010
#define LSF_PATTERN_ITEMS		(Line_Style_Flags)0x00000020
#define LSF_LONG_LENGTHS		(Line_Style_Flags)0x00000040
#define LSF_CONTRAST			(Line_Style_Flags)0x00000080
#define LSF_GLYPHS				(Line_Style_Flags)0x00000100
#define LSF_PARALLELS			(Line_Style_Flags)0x00000200
#define LSF_OFFSET				(Line_Style_Flags)0x00000400
#define LSF_MIDDLE_GLYPH		(Line_Style_Flags)0x00000800
#define LSF_START_GLYPH			(Line_Style_Flags)0x00001000
#define LSF_END_GLYPH			(Line_Style_Flags)0x00002000
#define LSF_FIXED_OFFSET		(Line_Style_Flags)0x00004000
#define LSF_WEIGHT				(Line_Style_Flags)0x00008000
#define LSF_FIXED_WEIGHT		(Line_Style_Flags)0x00010000
#define LSF_SEGMENTED			(Line_Style_Flags)0x00020000
#define LSF_PERCENT				(Line_Style_Flags)0x00040000
#define LSF_JOIN				(Line_Style_Flags)0x00080000
#define LSF_CAP					(Line_Style_Flags)0x00100000
#define LSF_FIT_CENTER			(Line_Style_Flags)0x00200000
#define LSF_FIT_STRETCH			(Line_Style_Flags)0x00400000
#define _hoops_ARCAP		(Line_Style_Flags)0x00800000
#define _hoops_PRCAP			(Line_Style_Flags)0x01000000
#define _hoops_HRCAP			(Line_Style_Flags)0x02000000
#define _hoops_IRCAP			(Line_Style_Flags)0x04000000
#define _hoops_CRCAP			(Line_Style_Flags)0x08000000


#define _hoops_RHISA (LSF_START_GLYPH|LSF_END_GLYPH|LSF_MIDDLE_GLYPH)

#define LSF_COMPLEX_ANYBITS		(LSF_ABSOLUTE_LENGTH|LSF_ABSOLUTE_WEIGHT|_hoops_RHISA| \
	LSF_PATTERN_ITEMS|LSF_LONG_LENGTHS|LSF_CONTRAST|LSF_GLYPHS|LSF_WEIGHT| \
	LSF_PARALLELS|LSF_OFFSET|LSF_SEGMENTED|LSF_FIT_CENTER|LSF_FIT_STRETCH| \
	_hoops_ARCAP|_hoops_PRCAP|_hoops_HRCAP|_hoops_IRCAP|_hoops_CRCAP)

#define _hoops_SRCAP				(Line_Style_Flags)0x00000000
#define _hoops_GACAP		(Line_Style_Flags)0x00000001
#define _hoops_RACAP		(Line_Style_Flags)0x00000002
#define _hoops_AACAP		(Line_Style_Flags)0x00000004
#define _hoops_PACAP		(Line_Style_Flags)0x00000010
#define _hoops_HACAP		(Line_Style_Flags)0x00000020
#define _hoops_IACAP		(Line_Style_Flags)0x00000040
#define _hoops_CACAP		(Line_Style_Flags)0x00000100
#define _hoops_SACAP		(Line_Style_Flags)0x00000200


struct Line_Style_Item {
	_hoops_HCRPR				name;
	Integer32			key;
	_hoops_HCAIR		size;
	Line_Style_Flags	flags;
	float				rotation;
	_hoops_HCAIR		weight;
	RGB					rgb;
	int					index;
};


struct Line_Style_Parallel {
	Line_Style_Parallel *		next;

	Line_Style_Flags			flags;

	_hoops_HCAIR				offset;
	_hoops_HCAIR				weight;

	Line_Style_Item *			start_glyph;
	Line_Style_Item *			middle_glyph;
	Line_Style_Item *			end_glyph;

	Line_Style_Item *			pattern_items;
	int *						pattern;

	unsigned int				pattern_items_n;
	unsigned int				_hoops_RHISR;
};

#define _hoops_GPCAP		(int)-1
#define _hoops_RPCAP		(int)-2
#define _hoops_APCAP	(int)-3
#define _hoops_PPCAP		(int)-4

struct _hoops_HPCAP : public _hoops_ICAGP {
	_hoops_HCRPR						name;
	Integer32					key;
	Integer32					id;
	Line_Style_Flags			flags;
	_hoops_HCRPR						definition;

	Line_Style_Parallel *		_hoops_GHISR;
	unsigned int				_hoops_IPCAP;

	int							scale32;
	int							_hoops_CPCAP;
	unsigned Integer32			bits32;
	unsigned short				_hoops_SPCAP;

	_hoops_HPCAP () : _hoops_ICAGP () {}
	~_hoops_HPCAP () {
		_hoops_RGAIR(name);
		_hoops_RGAIR(definition);

		Line_Style_Parallel *	p;

		while ((p = _hoops_GHISR) != null) {
			_hoops_GHISR = p->next;

			if (p->start_glyph) {
				_hoops_RGAIR(p->start_glyph->name);
				FREE(p->start_glyph, Line_Style_Item);
			}
			if (p->middle_glyph) {
				_hoops_RGAIR(p->middle_glyph->name);
				FREE(p->middle_glyph, Line_Style_Item);
			}
			if (p->end_glyph) {
				_hoops_RGAIR(p->end_glyph->name);
				FREE(p->end_glyph, Line_Style_Item);
			}
			if (p->pattern_items) {
				for (unsigned int i=0; i<p->pattern_items_n; ++i)
					_hoops_RGAIR(p->pattern_items[i].name);
				FREE_ARRAY(p->pattern_items, p->pattern_items_n, Line_Style_Item);
			}
			if (p->pattern)
				FREE_ARRAY(p->pattern, p->_hoops_RHISR, int);

			FREE(p, Line_Style_Parallel);
		}
	}

private:
	_hoops_HPCAP (_hoops_HPCAP const &);
};
typedef Counted_Pointer<_hoops_HPCAP>	Line_Style;


struct _hoops_APAIR : public Attribute {
	Line_Style *		_hoops_HPAIR;
	Integer32 *			keys;
	int					count;
};




struct _hoops_AHPIR : public Attribute {
	_hoops_HCAIR				data;
};

typedef _hoops_AHPIR		_hoops_GHCAP,
								_hoops_RHCAP,
								_hoops_AHCAP,
								_hoops_PHCAP;


struct _hoops_GGPIR : public Attribute {
	unsigned char				value;
	unsigned char				_hoops_HHCAP;
};

typedef _hoops_GGPIR			_hoops_IHCAP,
								_hoops_CHCAP,
								_hoops_SHCAP;

struct _hoops_SSAIR : public Attribute {
	_hoops_HCRPR						name;
	Integer32					key;
	short						_hoops_HHCAP;
};

typedef _hoops_SSAIR			_hoops_GICAP;

#define _hoops_RICAP					0x00000000
#define _hoops_AICAP				0x00000001
#define _hoops_PICAP						0x00000002
#define _hoops_HICAP					0x00000004
#define _hoops_IICAP				0x00000008
#define _hoops_CICAP					0x00000010

#define _hoops_SICAP				0x00000020
#define _hoops_GCCAP				0x00000040
#define _hoops_RCCAP			0x00000080
#define _hoops_ACCAP					(_hoops_SICAP|_hoops_RCCAP|_hoops_GCCAP)
#define _hoops_PCCAP			0x00000100
#define _hoops_HCCAP					(_hoops_SICAP|_hoops_PCCAP)
#define _hoops_ICCAP			0x00000200
#define _hoops_CCCAP		0x00000400

struct _hoops_PSAIR : public Attribute {
	_hoops_HCRPR		line_style;
	Integer32	_hoops_SCCAP;
	_hoops_HCRPR		start_glyph;
	Integer32	_hoops_GSCAP;
	_hoops_HCRPR		middle_glyph;
	Integer32	_hoops_RSCAP;
	_hoops_HCRPR		end_glyph;
	Integer32	_hoops_ASCAP;
	Integer32	mask;
	Integer32	value;
};

struct _hoops_ISAIR : public Attribute {
	_hoops_HCRPR		line_style;
	Integer32	_hoops_SCCAP;
	Integer32	mask;
	Integer32	value;
};


#define _hoops_PSCAP					0x00
#define _hoops_SRACA			0x01
#define _hoops_HSCAP	0x02
#define	_hoops_ISCAP			0x04
#define	_hoops_CSCAP			0x08
#define	_hoops_HRPCR						0x10

struct _hoops_CRACA {
	_hoops_HHRA const *			_hoops_SPH;
	_hoops_RHAH const *		_hoops_CSIR;
	_hoops_PIGRA *		locks;
	_hoops_PIGRA *		_hoops_SACRP;
	unsigned int const *	conditions;
	float					_hoops_ISIH;
};


struct _hoops_RSHIR {
	_hoops_RSHIR *			next;
	_hoops_SCHIR *				_hoops_AAPPR;
	_hoops_RSHIR *			_hoops_SSCAP;
	_hoops_RSHIR **			_hoops_GGSAP;
	_hoops_HCRPR					name;
	int						degree;
};

struct _hoops_SCHIR : public _hoops_HGHGP<_hoops_SCHIR, _hoops_IGHGP> {
	_hoops_RSHIR *				_hoops_HSHIR;
	Named_Material				_hoops_ISHIR;
	_hoops_HCRPR						definition;
};

struct _hoops_SRPPR : public _hoops_HGHGP<_hoops_SRPPR, _hoops_IGHGP> {
	_hoops_RSAPR *				_hoops_AAPPR;
	_hoops_HCRPR						name;
};
#define _hoops_ACPPR		_hoops_HCIGP(1)

/* _hoops_RH "_hoops_PSPA" _hoops_CAPP _hoops_CHR _hoops_PHPHA _hoops_HII _hoops_RH "_hoops_RGSAP" _hoops_GASR _hoops_IH _hoops_RH _hoops_HCSP */

struct _hoops_AGSAP {
	float					value;
	long					_hoops_HHP;
};

struct Option_Value {
	Option_Value *			next;
	_hoops_PIIIR *			type;
	union {
		bool					*_hoops_PGSAP;
		float					*_hoops_PIPCR;
		int						*_hoops_RIARA;
		_hoops_HCRPR					*_name;
		KName					*_hoops_HGSAP;
		long					*_hoops_RARHA;
		void					*_hoops_IGSAP;
		POINTER_SIZED_INT		*_hoops_CGSAP;
		Option_Value			*option_list; /* _hoops_IH _hoops_PHRSA _hoops_GRPRA */
		_hoops_AGSAP		*_hoops_RRRHA;
	}						value;
	bool					_hoops_GCACR;
	int						_hoops_AIPCR;
	int						_hoops_SGSAP;
};

/* _hoops_GRSAP _hoops_CSSC */
#define _hoops_RRRCR						 0
#define _hoops_RRSAP					 1
#define _hoops_SPPCR					 2
#define _hoops_APRCA						 3
#define _hoops_PRRCR						 4
#define _hoops_ARSAP					 5	/* _hoops_PSHR _hoops_GAR _hoops_RCSSA, _hoops_AHSAR _hoops_HAR _hoops_PRSAP */
#define _hoops_SIGHA						 6
#define _hoops_HRSAP				 7
#define _hoops_CIGHA 		 8
#define _hoops_IRSAP						 9
#define _hoops_CRSAP				10
#define _hoops_SRSAP					11
#define _hoops_GASAP					12
#define _hoops_ACIIR				13
// _hoops_RGAR "_hoops_RGSAP" _hoops_CSSC _hoops_HII _hoops_RASAP _hoops_GPP
#define _hoops_GHAGA				14	/* _hoops_PHRSA _hoops_PPPCR */
#define _hoops_AASAP		15	/* _hoops_RSRA _hoops_SCSH _hoops_PAR _hoops_PHRSA _hoops_PASAP */
#define _hoops_HASAP		16	/* _hoops_RSRA _hoops_CRS _hoops_PAR _hoops_PHRSA _hoops_PASAP */
#define _hoops_IASAP		17	/* _hoops_RSRA _hoops_AIIC _hoops_PAR _hoops_PHRSA _hoops_PASAP */
#define _hoops_CASAP			18	/* _hoops_RSRA _hoops_SCSH _hoops_PAR _hoops_GAAP _hoops_HAR */


#define _hoops_IIIIR		_hoops_HCIGP(1)
#define _hoops_SIIIR	_hoops_HCIGP(2)

struct _hoops_PIIIR : public _hoops_HGHGP<_hoops_PIIIR, _hoops_HPAH> {
	long						id;
	_hoops_HCRPR						name;
	int							_hoops_RCIIR;
	int							_hoops_RHSAA;	/* -1 _hoops_RPP _hoops_PSGR */
	bool						_hoops_GHSAA;
	_hoops_GCIIR *			_hoops_CIIIR;
};

struct _hoops_IGRCR {
	Integer32							id;
	_hoops_SRHSR							name;
	short								_hoops_RCIIR;
	short								_hoops_RHSAA;	/* -1 _hoops_RPP _hoops_PSGR */
	bool								_hoops_GHSAA;
	_hoops_HPAGA const *	_hoops_SASAP;
};

/* (_hoops_IRS _hoops_GPSAP _hoops_HICP _hoops_SAHR _hoops_IS _hoops_ASAC _hoops_SISPR _hoops_IS _hoops_PPSI '_hoops_RPR' _hoops_CRGR _hoops_RH _hoops_ARRS) */
struct _hoops_HPAGA {
	int									count;
	_hoops_IGRCR const *		options;
};


struct _hoops_RPSAP : public _hoops_HGHGP<_hoops_RPSAP, _hoops_HPAH> {
	long						id;
	KName						_hoops_SIHSA;
	int							_hoops_RCIIR;
	int							_hoops_RHSAA;	/* -1 _hoops_RPP _hoops_PSGR */
	bool						_hoops_GHSAA;
	_hoops_GCIIR *			_hoops_CIIIR;
};


#define	_hoops_HIACR(_hoops_APSAP, _hoops_PPSAP)						    \
		do {																\
			_hoops_CAAI (HOOPS_WORLD->_hoops_HPSAP);							\
			if (_hoops_CIACR (_hoops_APSAP)->table == null)					    \
				HI_Define_Constant_Options (_hoops_PPSAP, _hoops_GGAPR (_hoops_PPSAP),	\
											_hoops_CIACR (_hoops_APSAP));		\
			_hoops_APAI (HOOPS_WORLD->_hoops_HPSAP);							\
	    } while (0)

#define	_hoops_SIACR			0x00
#define	_hoops_CGPCR	0x01
#define	_hoops_PAPCA			0x02
#define	_hoops_IPSAP		0x04
#define	_hoops_CPSAP	0x08


struct _hoops_SSHIR : public _hoops_HGHGP<_hoops_SSHIR, _hoops_IGHGP> {
	_hoops_SPSAP		_hoops_APRPR;
};



struct _hoops_RGIIR : public _hoops_HGHGP<_hoops_RGIIR, _hoops_IGHGP> {
	_hoops_GHSAP		_hoops_APRPR;
};

struct _hoops_HRIIR : public _hoops_HGHGP<_hoops_HRIIR, _hoops_IGHGP> {
	_hoops_GSPGR						_hoops_SPAPR, _hoops_RHSAP;
	int							_hoops_AHSAP;
	float						_hoops_PHSAP;
	int							_hoops_HHSAP;
};

#define _hoops_IHSAP		_hoops_HCIGP(1)


struct _hoops_HHIIR : public _hoops_HISHA {
	_hoops_HRIIR *					_hoops_CHIIR;
};

struct _hoops_SRIIR : public _hoops_HISHA {
	_hoops_GGAGR *						source;
	Button						button;
	Integer32					status;
		/* _hoops_GGR _hoops_AGIR _hoops_IRS _hoops_GSGR _hoops_PGRRR _hoops_PRHI _hoops_HPP _hoops_RH _hoops_PSHR _hoops_CHSAP _hoops_SHSAP */
	_hoops_AHIIR *				_hoops_RAIIR;
};

struct _hoops_AHIIR : public _hoops_HISHA {
	_hoops_GGAGR *						source;
	KName						string;
	_hoops_IHGRP				encoding;
};

struct _hoops_RIIIR : public _hoops_HISHA {
	_hoops_HCRPR						name,
								value;
};

struct _hoops_PAIIR : public _hoops_HISHA {
	_hoops_GGAGR *						source;
	float						x, y;
	Integer32					status;
	_hoops_APSHA				action;
		/* _hoops_PPR _hoops_RPP _hoops_IRS _hoops_GHSHA _hoops_HRGR _hoops_PRHI _hoops_HPP _hoops_RH _hoops_PSHR _hoops_GISAP _hoops_ACPH */
	Selection_Event	*			_hoops_CAIIR;
};


struct _hoops_RISAP {
	_hoops_RISAP *			prev;
	_hoops_PGRPR const *			include;
};

struct _hoops_AISAP {
	_hoops_AISAP *		next;
	int						_hoops_PISAP[3];
	float					_hoops_HISAP;
	float					_hoops_IISAP;
};

struct _hoops_RPIIR {
	_hoops_RPIIR *		next;
	_hoops_HPAH const *		item;
	Key						_hoops_HSICA;
	Key						_hoops_CISAP;
	_hoops_RISAP *			_hoops_SISAP;
	_hoops_APSHA			_hoops_GCSAP;
	int						offset1, offset2, offset3;
	float					xw, yw, _hoops_RCSAP;
	float					xc, yc, zc;

	_hoops_AISAP *		_hoops_ACSAP;

	/* _hoops_AGCR _hoops_CHR _hoops_IH _hoops_RHPP _hoops_GSGAR */
	float					_hoops_PCSAP;
	float					_hoops_HCSAP;
	Net_Rendition			_hoops_APHGA;
};


typedef int _hoops_ICSAP;
#define _hoops_CCSAP (_hoops_ICSAP)0x0001

struct _hoops_IPIIR {
	_hoops_ICSAP				flags;
	_hoops_RPIIR **		_hoops_SPIIR;
	bool					(*compare)(_hoops_RPIIR *, _hoops_RPIIR*);
	int 					allocated;
	int 					used;
	_hoops_RPIIR *		_hoops_SCSAP;
	int						_hoops_GSSAP;
};



typedef int		_hoops_RSSAP;
#define _hoops_HHSHA				(_hoops_RSSAP)0x0001
#define _hoops_HCSHA	(_hoops_RSSAP)0x0002
#define _hoops_ICSHA	(_hoops_RSSAP)0x0004
#define _hoops_CCSHA	(_hoops_RSSAP)0x0008
#define _hoops_ASSAP		(_hoops_RSSAP)0x0010

struct Selection_Event : public _hoops_HISHA {
	_hoops_GGAGR *					source;
	_hoops_GGAGR *					target;
	_hoops_APSHA				_hoops_CHSHA;
	Integer32					status;
	_hoops_PGCIR						_hoops_IHSHA;
	_hoops_CRCP *					_hoops_GHIIR;
	_hoops_IPIIR *		_hoops_HPIIR;
	_hoops_RPIIR *			_hoops_APIIR;
	Point *						_hoops_HARIR;
	int							count;
	_hoops_RSSAP					flags;

	_hoops_GHAIR *				heuristics;
};



struct _hoops_PSSAP {
	_hoops_PSSAP *				next;

	_hoops_HPAH *				owner;
	Key						_hoops_HSSAP;
	Key						original;
};

struct Pending_Special {
	Pending_Special	*		next;
	_hoops_HCRPR					type,
							value;
};

struct _hoops_ISSAP {
	_hoops_ISSAP *		next;
	_hoops_CRCP const *			segment;
	Activity				_hoops_CSSAP;
	Geometry const *		geometry;
	Activity				_hoops_SSSAP;
};



struct _hoops_IISCA {
	Geometry const *	geometry;	// _hoops_GIGR _hoops_CPAP _hoops_RPP _hoops_GII
	Key					key;		// _hoops_RH _hoops_IIPR _hoops_CAGH _hoops_SR _hoops_IRHH
	Key const *			old_keys;	// _hoops_CRGIA _hoops_IS _hoops_PSSSR _hoops_IH
	Key *				new_keys;	// _hoops_RCGRA _hoops_CRGIA _hoops_RPP _hoops_GCRHA
	int					count;		// _hoops_PHI _hoops_IIGR _hoops_CRGIA _hoops_IS _hoops_PSSSR
	bool				_hoops_IIGSA;	// _hoops_RIP _hoops_HII _hoops_GGGPP
};



#define _hoops_RGGPP				0
#define _hoops_AGGPP		1
#define _hoops_PGGPP		2
#define _hoops_HGGPP				3


struct _hoops_PCCCA {
	struct {
		Activity				clear,
								set;
	}						_hoops_CCCCA;
	struct {
		_hoops_RCCCA			clear,
								set;
	}						database;
	_hoops_PACIR		area;
	bool					_hoops_RGSCA;
	bool					_hoops_AGSCA;
	bool					_hoops_IHGI;
	bool					_hoops_ASCCA;
};


#define _hoops_IGGPP				0x00000000
#define _hoops_CGGPP		0x00000001
#define _hoops_SGGPP	0x00000002
#define _hoops_GRGPP			0x00000004





struct _hoops_SIRIR : public _hoops_HGHGP<_hoops_SIRIR, _hoops_IGHGP> {
	_hoops_IPRRA				_hoops_GCRIR;

#define		_hoops_RRGPP				(_hoops_IPRRA)0x00000000
#define		_hoops_RCRIR			(_hoops_IPRRA)0x00000001
#define		_hoops_HCRIR			(_hoops_IPRRA)0x00000002
#define		_hoops_CCRIR				(_hoops_IPRRA)0x00000004
#define		_hoops_SCRIR				(_hoops_IPRRA)0x00000010
#define		_hoops_ICRIR				(_hoops_IPRRA)0x00000020
#define		_hoops_RSRIR				(_hoops_IPRRA)0x00000040
#define		_hoops_ASRIR				(_hoops_IPRRA)0x00000100
#define		_hoops_GSRIR				(_hoops_IPRRA)0x00000200

	
#define		_hoops_ARGPP			(_hoops_IPRRA)0x00001000
#define		_hoops_GSIIR	(_hoops_IPRRA)0x00002000
#define		_hoops_PRGPP		(_hoops_IPRRA)0x00004000
#define		_hoops_HRGPP				(_hoops_IPRRA)0x00008000
//#_hoops_PPIP	_hoops_IRGPP		(_hoops_CRGPP)0x00FF0000
#define		_hoops_SRGPP		(_hoops_IPRRA)0x01000000


#define		_hoops_GAGPP(_type_)	((((_type_)<<16)&0x00FF0000)|_hoops_ARGPP)
#define		_hoops_RAGPP(_hoops_AAGPP)	(((_hoops_AAGPP)&0x00FF0000)>>16)

#define		_hoops_PAGPP(_type_)	((((_type_)<<16)&0x00FF0000)|_hoops_PRGPP)
#define		_hoops_HAGPP(_hoops_AAGPP, _hoops_IAGPP)	((_hoops_IAGPP)[(((_hoops_AAGPP)&0x00FF0000)>>16)])


// _hoops_IRGH _hoops_SCSH _hoops_RCIC	_hoops_CAGPP[] _hoops_HRGR _hoops_GGR _hoops_SAGPP._hoops_CRSC

#define		_hoops_GPGPP					0
#define		_hoops_RPGPP	1
#define		_hoops_APGPP					2
#define		_hoops_PPGPP					3
#define		_hoops_HPGPP					4
#define		_hoops_IPGPP				5
#define		_hoops_CPGPP						6
#define		_hoops_SPGPP				7
#define		_hoops_GHGPP						8
#define		_hoops_RHGPP						9
#define		_hoops_AHGPP						10
#define		_hoops_PHGPP				11
#define		_hoops_HHGPP				12
#define		_hoops_IHGPP			13
#define		_hoops_CHGPP				14
#define		_hoops_SHGPP					15
#define		_hoops_GIGPP					16
#define		_hoops_RIGPP				17
#define		_hoops_AIGPP				18
#define		_hoops_PIGPP						19
#define		_hoops_HIGPP						20
#define		_hoops_IIGPP				21
#define		_hoops_CIGPP				22
#define		_hoops_SIGPP					23
#define		_hoops_GCGPP						24
#define		_hoops_RCGPP					25


#define		_hoops_ACGPP		(_hoops_HCRIR|_hoops_PAGPP(_hoops_RPGPP))
#define		_hoops_PCGPP		(_hoops_HCRIR|_hoops_PAGPP(_hoops_APGPP))
#define		_hoops_HCGPP	(_hoops_HCRIR|_hoops_PAGPP(_hoops_APGPP))
#define		_hoops_ICGPP		(_hoops_HCRIR|_hoops_PAGPP(_hoops_APGPP))
#define		_hoops_CCGPP	(_hoops_HCRIR|_hoops_PAGPP(_hoops_APGPP))

#define		_hoops_SCGPP				(_hoops_HCRIR|_hoops_PAGPP(_hoops_CPGPP))
#define		_hoops_CISSR			(_hoops_HCRIR|_hoops_PAGPP(_hoops_GHGPP))
#define		_hoops_GSGPP		(_hoops_HCRIR|_hoops_PAGPP(_hoops_SPGPP))
#define		_hoops_RSGPP				(_hoops_HCRIR|_hoops_PAGPP(_hoops_RHGPP))
#define		_hoops_ASGPP				(_hoops_HCRIR|_hoops_PAGPP(_hoops_AHGPP))
#define		_hoops_AAGGA		(_hoops_HCRIR|_hoops_PAGPP(_hoops_PHGPP))
#define		_hoops_PAGGA	(_hoops_HCRIR|_hoops_PAGPP(_hoops_HHGPP))
#define		_hoops_PSGPP	(_hoops_HCRIR|_hoops_PAGPP(_hoops_IHGPP))
#define		_hoops_HSGPP		(_hoops_HCRIR|_hoops_PAGPP(_hoops_CHGPP))
#define		_hoops_ISGPP		(_hoops_HCRIR|_hoops_PAGPP(_hoops_SHGPP))
#define		_hoops_CSGPP			(_hoops_HCRIR|_hoops_PAGPP(_hoops_GIGPP))
#define		_hoops_SSGPP	(_hoops_HCRIR|_hoops_PAGPP(_hoops_RIGPP))
#define		_hoops_GGRPP		(_hoops_HCRIR|_hoops_PAGPP(_hoops_AIGPP))
#define		_hoops_RGRPP				(_hoops_HCRIR|_hoops_PAGPP(_hoops_PIGPP))
#define		_hoops_AGRPP			(_hoops_HCRIR|_hoops_PAGPP(_hoops_HIGPP))
#define		_hoops_PGRPP		(_hoops_HCRIR|_hoops_PAGPP(_hoops_IIGPP))
#define		_hoops_HGRPP		(_hoops_HCRIR|_hoops_PAGPP(_hoops_CIGPP))
#define		_hoops_IGRPP			(_hoops_HCRIR|_hoops_PAGPP(_hoops_SIGPP))
#define		_hoops_CGRPP			(_hoops_HCRIR|_hoops_PAGPP(_hoops_GCGPP))
#define		_hoops_SGRPP			(_hoops_HCRIR|_hoops_PAGPP(_hoops_RCGPP))

#define		_hoops_GISSR		(_hoops_RCRIR|_hoops_RSRIR)

#define		_hoops_SCIIR			(_hoops_RCRIR)
#define		_hoops_HSIIR			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_PAGPP(_hoops_PPGPP)|_hoops_GSRIR|_hoops_SCRIR|_hoops_CCRIR|_hoops_ICRIR)

#define		_hoops_GRRPP		(_hoops_HCRIR|_hoops_PAGPP(_hoops_CPGPP))
#define		_hoops_RRRPP		(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_CPGPP))
#define		_hoops_SCGPP				(_hoops_HCRIR|_hoops_PAGPP(_hoops_CPGPP))

#define		_hoops_RRGGA	(_hoops_HCRIR|_hoops_PAGPP(_hoops_HPGPP))
#define		_hoops_HRGGA	(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_HPGPP))

#define		_hoops_AHHPA	(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_IPGPP))

#define		_hoops_IAPRA					(_hoops_RCRIR|_hoops_HCRIR|_hoops_CCRIR|_hoops_ICRIR|_hoops_SCRIR|_hoops_GSRIR|_hoops_GAGPP(HK_COLOR))
#define		_hoops_ARRPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_LINE_PATTERN))
#define		_hoops_PRRPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_CCRIR|_hoops_GAGPP(HK_EDGE_PATTERN))
#define		_hoops_HRRPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_SCRIR|_hoops_GAGPP(HK_MARKER_SYMBOL))
#define		_hoops_GSACR				(_hoops_RCRIR|_hoops_GAGPP(HK_CALLBACK))
#define		_hoops_PPHCR					(_hoops_RCRIR|_hoops_GAGPP(HK_CAMERA))
#define		_hoops_SHAGA			(_hoops_RCRIR|_hoops_GAGPP(HK_CLIP_REGION))
#define		_hoops_RGHRA				(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_COLOR_MAP))
#define		_hoops_PGPCA				(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(_hoops_CPPIR))
#define		_hoops_IRRPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_LINE_WEIGHT))
#define		_hoops_CRRPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_CCRIR|_hoops_GAGPP(HK_EDGE_WEIGHT))
#define		_hoops_SRRPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_SCRIR|_hoops_GAGPP(HK_MARKER_SIZE))
#define		_hoops_GARPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_TEXT_SPACING))
#define		_hoops_RARPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_ICRIR|_hoops_GSRIR|_hoops_GAGPP(HK_FACE_PATTERN))
#define		_hoops_AARPP			(_hoops_RCRIR|_hoops_GAGPP(HK_WINDOW_PATTERN))
#define		_hoops_PARPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_TEXT_ALIGNMENT))
#define		_hoops_HARPP				(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_TEXT_PATH))
#define		_hoops_IARPP				(_hoops_RCRIR|_hoops_GAGPP(_hoops_RAAIR))
#define		_hoops_CARPP		(_hoops_RCRIR|_hoops_GAGPP(_hoops_RPAIR))
#define		_hoops_SARPP				(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_TEXT_FONT))
#define		_hoops_GPRPP			(_hoops_RCRIR|_hoops_GAGPP(HK_DRIVER_OPTIONS))
#define		_hoops_RPRPP					(_hoops_RCRIR|_hoops_GAGPP(HK_DRIVER))
#define		_hoops_APRPP				(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_HANDEDNESS))
#define		_hoops_PPRPP				(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_HEURISTICS))
#define		_hoops_HPRPP		(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_MODELLING_MATRIX))
#define		_hoops_IPRPP		(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_RENDERING_OPTIONS))
#define		_hoops_CPRPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_SELECTABILITY))
#define		_hoops_SPRPP			(_hoops_RCRIR|_hoops_GAGPP(_hoops_GRAIR))
#define		_hoops_GHRPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_TEXTURE_MATRIX))
#define		_hoops_RHRPP			(_hoops_RCRIR|_hoops_GAGPP(_hoops_IPAIR))
#define		_hoops_AHRPP				(_hoops_RCRIR|_hoops_HCRIR|_hoops_SCRIR|_hoops_CCRIR|_hoops_ICRIR|_hoops_GSRIR|_hoops_GAGPP(HK_VISIBILITY))
#define		_hoops_PHRPP					(_hoops_RCRIR|_hoops_GAGPP(HK_WINDOW))
#define		_hoops_HHRPP			(_hoops_RCRIR|_hoops_GAGPP(HK_WINDOW_FRAME))
#define		_hoops_IHRPP			(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_USER_OPTIONS))
#define		_hoops_CHRPP				(_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_USER_VALUE))
#define		_hoops_SHRPP		(_hoops_RCRIR|_hoops_GAGPP(_hoops_HAAIR))

#define		_hoops_ISPRA					(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_CCRIR|_hoops_ICRIR|_hoops_SCRIR|_hoops_GSRIR|_hoops_GAGPP(HK_COLOR))
#define		_hoops_GIRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_LINE_PATTERN))
#define		_hoops_RIRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_CCRIR|_hoops_GAGPP(HK_EDGE_PATTERN))
#define		_hoops_AIRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_SCRIR|_hoops_GAGPP(HK_MARKER_SYMBOL))
#define		_hoops_RRPCR				(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(HK_CALLBACK))
#define		_hoops_HHHCR				(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(HK_CAMERA))
#define		_hoops_GIAGA			(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(HK_CLIP_REGION))
#define		_hoops_HGHRA				(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_COLOR_MAP))
#define		_hoops_SGPCA			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(_hoops_CPPIR))
#define		_hoops_PIRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_LINE_WEIGHT))
#define		_hoops_HIRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_CCRIR|_hoops_GAGPP(HK_EDGE_WEIGHT))
#define		_hoops_IIRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_SCRIR|_hoops_GAGPP(HK_MARKER_SIZE))
#define		_hoops_CIRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_TEXT_SPACING))
#define		_hoops_SIRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_ICRIR|_hoops_GSRIR|_hoops_GAGPP(HK_FACE_PATTERN))
#define		_hoops_GCRPP		(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(HK_WINDOW_PATTERN))
#define		_hoops_RCRPP		(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_TEXT_ALIGNMENT))
#define		_hoops_ACRPP				(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_TEXT_PATH))
#define		_hoops_PCRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(_hoops_RAAIR))
#define		_hoops_HCRPP		(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(_hoops_RPAIR))
#define		_hoops_ICRPP				(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_TEXT_FONT))
#define		_hoops_CCRPP		(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(HK_DRIVER_OPTIONS))
#define		_hoops_SCRPP				(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(HK_DRIVER))
#define		_hoops_GSRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_HANDEDNESS))
#define		_hoops_RSRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_HEURISTICS))
#define		_hoops_ASRPP		(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_MODELLING_MATRIX))
#define		_hoops_PSRPP		(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_RENDERING_OPTIONS))
#define		_hoops_HSRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_SELECTABILITY))
#define		_hoops_ISRPP		(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(_hoops_GRAIR))
#define		_hoops_CSRPP		(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_TEXTURE_MATRIX))
#define		_hoops_SSRPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(_hoops_IPAIR))
#define		_hoops_GGAPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_SCRIR|_hoops_CCRIR|_hoops_ICRIR|_hoops_GSRIR|_hoops_GAGPP(HK_VISIBILITY))
#define		_hoops_RGAPP				(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(HK_WINDOW))
#define		_hoops_AGAPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(HK_WINDOW_FRAME))
#define		_hoops_PGAPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_USER_OPTIONS))
#define		_hoops_HGAPP			(_hoops_HRGPP|_hoops_RCRIR|_hoops_HCRIR|_hoops_GAGPP(HK_USER_VALUE))
#define		_hoops_IGAPP		(_hoops_HRGPP|_hoops_RCRIR|_hoops_GAGPP(_hoops_HAAIR))

#define		_hoops_CGAPP			(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_SPGPP))
#define		_hoops_SGAPP					(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_CPGPP))
#define		_hoops_GRAPP				(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_GHGPP))
#define		_hoops_RRAPP					(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_RHGPP))
#define		_hoops_ARAPP					(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_AHGPP))
#define		_hoops_PRAPP			(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_PHGPP))
#define		_hoops_HRAPP		(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_HHGPP))
#define		_hoops_IRAPP		(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_IHGPP))
#define		_hoops_CRAPP			(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_CHGPP))
#define		_hoops_SRAPP			(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_SHGPP))
#define		_hoops_GAAPP				(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_GIGPP))
#define		_hoops_RAAPP		(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_RIGPP))
#define		_hoops_AAAPP			(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_AIGPP))
#define		_hoops_PAAPP					(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_PIGPP))
#define		_hoops_HAAPP				(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_HIGPP))
#define		_hoops_IAAPP			(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_IIGPP))
#define		_hoops_CAAPP			(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_CIGPP))
#define		_hoops_SAAPP				(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_SIGPP))
#define		_hoops_GPAPP				(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_GCGPP))
#define		_hoops_RPAPP				(_hoops_HRGPP|_hoops_HCRIR|_hoops_PAGPP(_hoops_RCGPP))




	union {
		struct {
#			define			_hoops_APAPP		_hoops_HCIGP(1)
			_hoops_CRCP *		_hoops_IGRPR;
			_hoops_CRCP *		_hoops_PCRIR;
			Polyline *		_hoops_ACRIR;
		}				segment;

		struct {
			Geometry *		_hoops_IGRPR;
			int				offset;
		}				geometry;

		struct {
			Polyhedron *	_hoops_IGRPR;
			int				offset;
		}				_hoops_IPRI;

		struct {
			_hoops_HPAH *		_hoops_IGRPR;
			int				offset;
		}				_hoops_PRSI;

		struct {
			_hoops_APPGR *	_hoops_IGRPR;
			int				offset;
		}				_hoops_PSRIR;
	}				info;
};



//#_hoops_PPIP _hoops_PPAPP

template <typename T>
local INLINE void _hoops_CIGPR (_hoops_AIGPR * _hoops_RIGC, T * item) {

#ifdef _hoops_HPAPP
	_hoops_ICIIR(_hoops_RIGC);
#else
	UNREFERENCED(_hoops_RIGC);
#endif

	if ((*item->backlink = item->next) != null)
		item->next->backlink = item->backlink;

	item->backlink = &item->next;
	item->next = null;
}

local INLINE void _hoops_CIGPR (_hoops_AIGPR * _hoops_RIGC, _hoops_SIRIR * item) {

	UNREFERENCED(_hoops_RIGC);

	_hoops_CAAI (HOOPS_WORLD->_hoops_RIPSA);
	if ((*item->backlink = item->next) != null)
		item->next->backlink = item->backlink;

	item->backlink = &item->next;
	item->next = null;
	_hoops_APAI (HOOPS_WORLD->_hoops_RIPSA);
}



local INLINE void _hoops_IPAPP (_hoops_AIGPR * _hoops_RIGC, _hoops_SIRIR * item) {

	_hoops_CAAI (HOOPS_WORLD->_hoops_RIPSA);
	if ((item->next = _hoops_RIGC->open_list) != null)
		_hoops_RIGC->open_list->backlink = &item->next;
	item->backlink = &_hoops_RIGC->open_list;
	_hoops_RIGC->open_list = item;
	_hoops_APAI (HOOPS_WORLD->_hoops_RIPSA);
}



local INLINE void _hoops_CPAPA (_hoops_AIGPR * _hoops_RIGC,
								   Subsegment * _hoops_SIIS, _hoops_CRCP * const _hoops_SRCP) {

#ifdef _hoops_HPAPP
	_hoops_ICIIR(_hoops_RIGC);
#else
	UNREFERENCED(_hoops_RIGC);
#endif

	if ((_hoops_SIIS->next = _hoops_SRCP->_hoops_RGRPR) != null) 
		_hoops_SRCP->_hoops_RGRPR->backlink = &_hoops_SIIS->next;

	_hoops_PGRCA(_hoops_SRCP)->_hoops_RGRPR = _hoops_SIIS;
	_hoops_SIIS->backlink = &_hoops_PGRCA(_hoops_SRCP)->_hoops_RGRPR;
}

GLOBAL_FUNCTION void _hoops_ISRSA (_hoops_AIGPR * _hoops_RIGC, _hoops_PHIP * _hoops_RRA);

GLOBAL_FUNCTION void _hoops_CIHIR (_hoops_AIGPR * _hoops_RIGC, _hoops_PHIP * _hoops_RRA, _hoops_SIHIR const * _hoops_SIIS, bool _hoops_CPAPP=false);

INLINE void _hoops_CIHIR (_hoops_AIGPR * _hoops_RIGC, _hoops_PHIP * _hoops_RRA, bool _hoops_CPAPP=false) 
{
	for (int i=0; i< _hoops_RRA->_hoops_HHIP; ++i)
		_hoops_CIHIR (_hoops_RIGC, _hoops_RRA, _hoops_RRA->_hoops_IHIP[i], _hoops_CPAPP);
}


local INLINE void _hoops_SPAPA (_hoops_AIGPR * _hoops_RIGC,
	_hoops_PGRPR * include, _hoops_CRCP const * _hoops_IGRPR) {

#ifdef _hoops_HPAPP
	_hoops_ICIIR(_hoops_RIGC);
#else
	UNREFERENCED(_hoops_RIGC);
#endif
	if ((include->_hoops_GRRPR = _hoops_IGRPR->_hoops_SGRPR()) != null)
		include->_hoops_GRRPR->_hoops_SHAIR = &include->_hoops_GRRPR;
	_hoops_PGRCA(_hoops_IGRPR)->_hoops_ISRIR ((Xref *)include);
}

local INLINE void _hoops_ACSCA (_hoops_AIGPR * _hoops_RIGC,
	Style * style, _hoops_CRCP const * _hoops_IGRPR) {

#ifdef _hoops_HPAPP
	_hoops_ICIIR(_hoops_RIGC);
#else
	UNREFERENCED(_hoops_RIGC);
#endif
	if ((style->_hoops_GRRPR = _hoops_IGRPR->_hoops_SGRPR()) != null)
		style->_hoops_GRRPR->_hoops_SHAIR = &style->_hoops_GRRPR;
	_hoops_PGRCA(_hoops_IGRPR)->_hoops_ISRIR ((Xref *)style);
}



End_HOOPS_Namespace;

#endif

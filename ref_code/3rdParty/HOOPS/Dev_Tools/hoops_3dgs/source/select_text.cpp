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
 * $Id: obf_tmp.txt 1.90 2010-07-14 23:29:16 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "driver.h"
#include "tandt.h"
#include "topology.h"
#include "select.h"
#include "hd_proto.h"
#include "hi_proto.h"

#ifndef DISABLE_SELECTION

local void _hoops_SGRPS (
	Net_Rendition const & nr,
	int								count,
	DC_Point const *				points,
	bool						_hoops_GRRPS) {
	Display_Context alter		*dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter		*sc = dc->_hoops_APHHP;
	_hoops_HACC const					*text;
	DC_Point const				*pp = points;
	DC_Point const				*end;
	DC_Point const				*prev;
	float							_hoops_AGRSH, _hoops_PGRSH,
												x1 = 0.0f, _hoops_AGSIR = 0.0f,
												_hoops_HSHGA, _hoops_ISHGA,
												xc, yc,
												_hoops_HGRSH, _hoops_HGSIR, _hoops_CSHGA,
												_hoops_GPHAS, _hoops_RPHAS,
												tc,
												_hoops_CIGGA, _hoops_SIGGA,
												_hoops_PHHAS,
												_hoops_HISAP, _hoops_CIPAS,
												_hoops_RRRPS = 0.0f;
	bool						_hoops_CARGA = false;
	int								offset = 0;
	bool						_hoops_ARRPS;
	bool						_hoops_HHAHR = false;
	float							_hoops_HPCII;

	if ((text = dc->_hoops_IGHGH->_hoops_RHGGH) == null)
		return;			/* _hoops_GA'_hoops_RA _hoops_HAIHR _hoops_RPP _hoops_RGAR _hoops_IRS _hoops_HASRH */

#ifndef DISABLE_POLY_SELECTION
	if (sc->_hoops_CAPAS != 0) {
		_hoops_GPCIH alter					* alter *_hoops_PRHAS;
		int								_hoops_HRHAS;
		int								_hoops_IRHAS;

		_hoops_HRHAS = HI_Create_Polyglin_Wings (count, (Point *)points,
													  true, _hoops_GAPAS,
													  &_hoops_PRHAS);
		_hoops_IRHAS = HI_Wings_Intersect (_hoops_HRHAS, _hoops_PRHAS,
										  sc->_hoops_CAPAS, sc->_hoops_SAPAS);

		HI_Free_Wings (_hoops_HRHAS, _hoops_PRHAS);

		if (_hoops_IRHAS) {
			dc->_hoops_IGHGH->_hoops_HHGGH	  = 0.0f;
			dc->_hoops_IGHGH->_hoops_IHGGH	  = points[0].z;
			dc->_hoops_IGHGH->_hoops_CHGGH = dc->_hoops_IGHGH->_hoops_PHGGH;
		}
		return;
	}
#endif

	/* _hoops_AISRA _hoops_RH _hoops_RRGR _hoops_HII _hoops_PRRPS(), _hoops_GPICR _hoops_IIHA
	 * _hoops_GPP _hoops_ISCP _hoops_ICSHC _hoops_IIGR _hoops_RH _hoops_HRRPS _hoops_SSSC */

	end = pp + count;
	_hoops_HISAP = sc->_hoops_GICAH;

	_hoops_RRRPS = x1 = points[0].x;
	_hoops_ARRPS = false;
	_hoops_AGRSH = 0.0f;
	_hoops_PGRSH = 0.0f;

	_hoops_RGGA ((++offset, prev = pp, ++pp) == end) {
		if (_hoops_HHAHR) {		/* (_hoops_IRGGS _hoops_RAAP _hoops_IAPR _hoops_HII _hoops_PGHC _hoops_HAPR) */
			x1 = _hoops_AGRSH;
			_hoops_AGSIR = _hoops_PGRSH;
			_hoops_HHAHR = false;
		}

		/* _hoops_HGCR _hoops_SPCR _hoops_PCRR */
		_hoops_AGRSH = x1;
		x1 = pp->x;

		_hoops_IRRPS:;

		/* _hoops_RAH _hoops_IRS _hoops_HHCI _hoops_IASC _hoops_AHCRR _hoops_RPGP _hoops_GPP _hoops_SPCR */
		if (x1 < sc->bounding.left) {
			if (_hoops_AGRSH < sc->bounding.left) {
				_hoops_ARRPS = false;
				continue;
			}
		}
		else if (x1 > sc->bounding.right) {
			if (_hoops_AGRSH > sc->bounding.right) {
				_hoops_ARRPS = false;
				continue;
			}
		}

		/* _hoops_HGCR _hoops_GHCR _hoops_PCRR */
		if (!_hoops_ARRPS) {
			_hoops_PGRSH = prev->y;
			_hoops_AGSIR = pp->y;
		}
		else {
			_hoops_PGRSH = _hoops_AGSIR;
			_hoops_AGSIR = pp->y;
		}
		_hoops_ARRPS = true;

		/*	_hoops_RAH _hoops_IRS _hoops_HHCI _hoops_IASC _hoops_AHCRR _hoops_RPGP _hoops_GPP _hoops_GHCR */
		if (_hoops_AGSIR < sc->bounding.bottom) {
			if (_hoops_PGRSH < sc->bounding.bottom) continue;
		}
		else if (_hoops_AGSIR > sc->bounding.top) {
			if (_hoops_PGRSH > sc->bounding.top) {
				/* _hoops_RPR _hoops_ACCGI _hoops_ARRSH _hoops_IH _hoops_ASSA _hoops_ISPR */
				if (_hoops_AGRSH <= sc->_hoops_AICAH.x) {
					if (sc->_hoops_AICAH.x < x1) _hoops_CARGA = !_hoops_CARGA;
				}
				else if (x1 <= sc->_hoops_AICAH.x) {
					if (sc->_hoops_AICAH.x < _hoops_AGRSH) _hoops_CARGA = !_hoops_CARGA;
				}
				continue;
			}
		}

		/* _hoops_ACGR _hoops_RH _hoops_HISGR _hoops_PPSR */
		_hoops_HSHGA = x1 - _hoops_AGRSH;
		_hoops_ISHGA = _hoops_AGSIR - _hoops_PGRSH;

		tc = _hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA*_hoops_ISHGA;		/* _hoops_GRAS _hoops_PCHAS */
		if (tc < 0.000001f) {
			/* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_PPSR, _hoops_HAR _hoops_IRS _hoops_III! */
			xc = _hoops_AGRSH;
			yc = _hoops_PGRSH;
			tc = 0.0f;
		}
		else {
			tc = (_hoops_HSHGA * (sc->_hoops_AICAH.x - _hoops_AGRSH) +
				  _hoops_ISHGA * (sc->_hoops_AICAH.y - _hoops_PGRSH)) / tc;

			if (tc > _hoops_SHRSP) {	/* _hoops_HCHAS _hoops_ICCAR. _hoops_CACH _hoops_ICHAS _hoops_GGR _hoops_RHPP._hoops_GGHR */
				_hoops_HSHGA = -_hoops_HSHGA;
				_hoops_ISHGA = -_hoops_ISHGA;
				_hoops_HPCII = _hoops_AGRSH; _hoops_AGRSH = x1; x1 = _hoops_HPCII;
				_hoops_HPCII = _hoops_PGRSH; _hoops_PGRSH = _hoops_AGSIR; _hoops_AGSIR = _hoops_HPCII;
				_hoops_HHAHR = true;

				tc = (_hoops_HSHGA * (sc->_hoops_AICAH.x - _hoops_AGRSH) +
					  _hoops_ISHGA * (sc->_hoops_AICAH.y - _hoops_PGRSH)) / (_hoops_HSHGA*_hoops_HSHGA + _hoops_ISHGA*_hoops_ISHGA);
			}

			/* _hoops_IRHH _hoops_RCRR _hoops_SR'_hoops_ASAR _hoops_HCHAR _hoops_GIAA _hoops_RH _hoops_III **_hoops_CAGH** ... */
			if (tc <= 0.0f) {
				tc = 0.0f;
				xc = _hoops_AGRSH;
				yc = _hoops_PGRSH;
			}
			else if (tc >= 1.0f) {
				tc = 1.0f;
				xc = x1;
				yc = _hoops_AGSIR;
			}
			else {
				xc = _hoops_AGRSH + _hoops_HSHGA * tc;
				yc = _hoops_PGRSH + _hoops_ISHGA * tc;
			}
		}

		/* _hoops_RPR _hoops_ACCGI _hoops_ARRSH _hoops_IH _hoops_ASSA _hoops_ISPR */
		if (yc >= sc->_hoops_AICAH.y) {
			if (_hoops_AGRSH <= sc->_hoops_AICAH.x) {
				if (sc->_hoops_AICAH.x < x1) _hoops_CARGA = !_hoops_CARGA;
			}
			else if (x1 <= sc->_hoops_AICAH.x) {
				if (sc->_hoops_AICAH.x < _hoops_AGRSH) _hoops_CARGA = !_hoops_CARGA;
			}
		}

		/* _hoops_CCHAS _hoops_RPGP _hoops_GPP _hoops_RH _hoops_HISGR _hoops_PPSR */
		_hoops_GPHAS = (xc - sc->_hoops_AICAH.x) / sc->_hoops_HICAH.x;
		_hoops_RPHAS = (yc - sc->_hoops_AICAH.y) / sc->_hoops_HICAH.y;
		_hoops_CIPAS = _hoops_GPHAS*_hoops_GPHAS + _hoops_RPHAS*_hoops_RPHAS;

		if (_hoops_CIPAS >= _hoops_HISAP) continue;

		/* _hoops_APSH _hoops_RRRIR _hoops_RIRA - _hoops_HA _hoops_AA _hoops_IHIR-_hoops_CSRA _hoops_PCGC */

		/* _hoops_GAGA _hoops_AHCR _hoops_HAH - _hoops_SR'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_RRP _hoops_SCH */

		_hoops_HGRSH = prev->z;
		_hoops_HGSIR = pp->z;

		if (_hoops_HHAHR) {
			_hoops_HPCII = _hoops_HGSIR; _hoops_HGSIR = _hoops_HGRSH; _hoops_HGRSH = _hoops_HPCII;
		}

		_hoops_CSHGA = _hoops_HGSIR - _hoops_HGRSH;

		/* _hoops_HSPH _hoops_HISGR _hoops_IS _hoops_RH _hoops_IASC _hoops_AHCRR _hoops_IS _hoops_GHGPR _hoops_ISPR */

		_hoops_SIGGA = 1.0f;
		_hoops_CIGGA = 0.0f;

		if (_hoops_HSHGA > 0.0f) {
			if (_hoops_AGRSH < sc->bounding.left) {
				_hoops_PHHAS = (sc->bounding.left - _hoops_AGRSH) / _hoops_HSHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
			if (x1 > sc->bounding.right) {
				_hoops_PHHAS = (sc->bounding.right - _hoops_AGRSH) / _hoops_HSHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
		}
		else {
			if (x1 < sc->bounding.left) {
				if (_hoops_HSHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.left - _hoops_AGRSH) / _hoops_HSHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
			if (_hoops_AGRSH > sc->bounding.right) {
				if (_hoops_HSHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.right - _hoops_AGRSH) / _hoops_HSHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
		}

		if (_hoops_ISHGA > 0.0f) {
			if (_hoops_PGRSH < sc->bounding.bottom) {
				_hoops_PHHAS = (sc->bounding.bottom - _hoops_PGRSH) / _hoops_ISHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
			if (_hoops_AGSIR > sc->bounding.top) {
				_hoops_PHHAS = (sc->bounding.top - _hoops_PGRSH) / _hoops_ISHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
		}
		else {
			if (_hoops_AGSIR < sc->bounding.bottom) {
				if (_hoops_ISHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.bottom - _hoops_PGRSH) / _hoops_ISHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
			if (_hoops_PGRSH > sc->bounding.top) {
				if (_hoops_ISHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.top - _hoops_PGRSH) / _hoops_ISHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
		}

		if (_hoops_CSHGA > 0.0f) {
			if (_hoops_HGRSH < sc->bounding.hither) {
				_hoops_PHHAS = (sc->bounding.hither - _hoops_HGRSH) / _hoops_CSHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
			if (_hoops_HGSIR > sc->bounding.yon) {
				_hoops_PHHAS = (sc->bounding.yon - _hoops_HGRSH) / _hoops_CSHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
		}
		else {
			if (_hoops_HGSIR < sc->bounding.hither) {
				if (_hoops_CSHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.hither - _hoops_HGRSH) / _hoops_CSHGA;
				if (_hoops_SIGGA > _hoops_PHHAS) _hoops_SIGGA = _hoops_PHHAS;
			}
			if (_hoops_HGRSH > sc->bounding.yon) {
				if (_hoops_CSHGA == 0.0f) continue;
				_hoops_PHHAS = (sc->bounding.yon - _hoops_HGRSH) / _hoops_CSHGA;
				if (_hoops_CIGGA < _hoops_PHHAS) _hoops_CIGGA = _hoops_PHHAS;
			}
		}

		if (_hoops_CIGGA >= _hoops_SIGGA) continue; /* _hoops_HCR _hoops_PPRGA */

		/* _hoops_CGP _hoops_SCH _hoops_GGHP _hoops_SACH - _hoops_RHSHA _hoops_IPCAH */

		if (tc < _hoops_CIGGA || tc > _hoops_SIGGA) {
			if (tc < _hoops_CIGGA)
				tc = _hoops_CIGGA;
			else
				tc = _hoops_SIGGA;

			xc = _hoops_AGRSH + _hoops_HSHGA * tc;
			yc = _hoops_PGRSH + _hoops_ISHGA * tc;

			_hoops_GPHAS = (xc - sc->_hoops_AICAH.x) / sc->_hoops_HICAH.x;
			_hoops_RPHAS = (yc - sc->_hoops_AICAH.y) / sc->_hoops_HICAH.y;
			_hoops_CIPAS = _hoops_GPHAS*_hoops_GPHAS + _hoops_RPHAS*_hoops_RPHAS;

			if (_hoops_CIPAS >= _hoops_HISAP) continue;
		}

		/* _hoops_GGHP _hoops_SCH */
		if ((_hoops_HISAP = _hoops_CIPAS) < dc->_hoops_IGHGH->_hoops_HHGGH) {
			dc->_hoops_IGHGH->_hoops_HHGGH	  = _hoops_HISAP;
			dc->_hoops_IGHGH->_hoops_IHGGH	  = _hoops_HGRSH + _hoops_CSHGA * tc;
			dc->_hoops_IGHGH->_hoops_CHGGH = dc->_hoops_IGHGH->_hoops_PHGGH;
		}
	}


	if (offset == count) {
		if (_hoops_HHAHR) {		/* (_hoops_IRGGS _hoops_RAAP _hoops_IAPR _hoops_HII _hoops_HAPR) */
			x1 = _hoops_AGRSH;
			_hoops_AGSIR = _hoops_PGRSH;
			_hoops_HHAHR = false;
		}

		pp = points;					/* _hoops_GGHC _hoops_RH _hoops_HAPR _hoops_IS... */
		end = pp + 1;					/* _hoops_HAPR _hoops_GGSR _hoops_SPS _hoops_GHIR */

		/* _hoops_PPR _hoops_HPGCA _hoops_ISSC _hoops_GGR */
		_hoops_ARRPS = false;

		_hoops_AGRSH = x1;
		x1 = _hoops_RRRPS;

		goto _hoops_IRRPS;
	}


	if (_hoops_CARGA && _hoops_GRRPS) {
		_hoops_ARPA		plane;

		/* _hoops_SSS _hoops_RH _hoops_IHPR _hoops_RHC-_hoops_HGGS/_hoops_HSSP _hoops_SGSSR _hoops_AHCR */
		HI_Figure_Plane_From_Points (count, (Point const *)points, &plane);

		if (plane.c == 0.0f) {
			/* _hoops_SR _hoops_CHR _hoops_CPPPR _hoops_PCCGS - _hoops_GPP _hoops_ISHA, _hoops_HIS _hoops_PAH'_hoops_RA _hoops_SHH _hoops_ASSA! */
			dc->_hoops_IGHGH->_hoops_IHGGH = 0.0f; /* ?? */
		}
		else {
			dc->_hoops_IGHGH->_hoops_IHGGH =
				-(plane.a * sc->_hoops_AICAH.x +
				  plane.b * sc->_hoops_AICAH.y + plane.d) / plane.c;
		}

		dc->_hoops_IGHGH->_hoops_HHGGH	  = 0.0f;
		dc->_hoops_IGHGH->_hoops_CHGGH =	dc->_hoops_IGHGH->_hoops_PHGGH;
	}
}

local void _hoops_CRRPS (
	Net_Rendition const & nr,
	int								count,
	DC_Point const *				points) {

	_hoops_SGRPS (nr, count, points, false);
}

local void _hoops_SRRPS (
	Net_Rendition const & nr,
	int								count,
	DC_Point const *				points) {
	int								_hoops_RRC = 1;

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count--) {
		_hoops_SGRPS (nr, 3, points, true);
		points += _hoops_RRC;
	}
}

local void _hoops_GARPS (
	Net_Rendition const & nr,
	Point const					*points,
	_hoops_RAARP const			*stencil) {
	DC_Point alter				_hoops_CGCAR[4];		

	UNREFERENCED (stencil);

	HI_Compute_Transformed_Points  (4, points, &nr->transform_rendition->matrix->data.elements[0][0],
									(Point alter *)_hoops_CGCAR);
	_hoops_SRRPS (nr, 4, _hoops_CGCAR);
}

local void _hoops_RARPS (
	Net_Rendition const & nr,
	DC_Point const				*points,
	_hoops_RAARP const			*stencil) {

	UNREFERENCED (stencil);

	_hoops_SRRPS (nr, 4, points);
}


local void _hoops_AGCSR (
	Net_Rendition const &		nr,
	_hoops_HACC const *				text,
	Point const *				position,
	int							count,
	Karacter const *			_hoops_AARPS,
	_hoops_PGCSR const *	_hoops_HGCSR) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	Display_Context const *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	int							left = (int)position->x,
								bottom = (int)position->y;
	float						_hoops_HSHGA, _hoops_ISHGA,
								a, b,
								_hoops_HHGGH,
								_hoops_IHGGH;
	int							right, top;
	int							offset2;
	float						_hoops_PARPS;
	Karacter const *			_hoops_IHSCP = (Karacter const *) _hoops_AARPS;

	if (text == null) return; /* _hoops_SCH'_hoops_GRI _hoops_IRS _hoops_GSGR _hoops_HASRH! */	 

	if (_hoops_HGCSR) {
		left -= int (_hoops_HGCSR->screen.x);
		bottom -= int (_hoops_HGCSR->screen.y);
		right = left + int (_hoops_HGCSR->screen.width);
		top = bottom + int (_hoops_HGCSR->screen.height);
		offset2 = _hoops_HGCSR->offset;
	}
	else {
		HD_Measure_Characters (nr, count, _hoops_IHSCP, text->encoding, &_hoops_PARPS);
	
		right = int (left + _hoops_PARPS);
		top = bottom + (int)_hoops_HRCIR->font->_hoops_ISISR;
		offset2 = 0;
	}

	if (left > sc->bounding.right || bottom > sc->bounding.top ||
		right < sc->bounding.left || top < sc->bounding.bottom) 
		return;

	if (count == 1) { /* _hoops_HCHAS _hoops_ICCAR */
		if (_hoops_HRCIR->spacing > 1.0f) { /* _hoops_RPP _hoops_HARPS-_hoops_GGSR, _hoops_ASSS _hoops_CGCH _hoops_CCSIA _hoops_GPP _hoops_CGHC */
			if (_hoops_HRCIR->path.x > 0.0f)
				right += (int)(_hoops_HRCIR->spacing * (float)(right - left));
			else
				left -= (int)(_hoops_HRCIR->spacing * (float)(right - left));
		}
	}

	if (right < sc->bounding.left || top < sc->bounding.bottom) return;

	/* _hoops_APSH _hoops_IARPS... */

	if ((_hoops_HSHGA = left - sc->_hoops_AICAH.x) > 0.0f) {/* _hoops_HASRH _hoops_HRGR _hoops_IS _hoops_RH _hoops_RAAP */}
	else if ((_hoops_HSHGA = sc->_hoops_AICAH.x - right) > 0.0f) {/* _hoops_PAR _hoops_IS _hoops_RH _hoops_RPHR */}
	else _hoops_HSHGA = 0.0f;						/* _hoops_PAR _hoops_GIAA */

	if ((_hoops_ISHGA = bottom - sc->_hoops_AICAH.y) > 0.0f) {/* _hoops_HASRH _hoops_HRGR _hoops_CAPP */}
	else if ((_hoops_ISHGA = sc->_hoops_AICAH.y - top) > 0.0f) {/* _hoops_PAR _hoops_ARRS */}
	else _hoops_ISHGA = 0.0f;						/* _hoops_PAR _hoops_GIAA */

	if (_hoops_HSHGA == 0.0f && _hoops_ISHGA == 0.0f) {
		/* _hoops_HASRH'_hoops_GRI _hoops_GIAA - _hoops_IRAA _hoops_SCH! */
		_hoops_HHGGH = 0.0f;
	}
	else {
		/* _hoops_HASRH'_hoops_GRI _hoops_GSPCA _hoops_AIRAI - _hoops_RPGP _hoops_RRI _hoops_HRGHR */

		/* _hoops_SRS, _hoops_SISR & _hoops_HAPC */
		if (_hoops_HSHGA > sc->_hoops_RICAH.x || _hoops_ISHGA > sc->_hoops_RICAH.y) return;

		/* _hoops_PSCR _hoops_GHARP _hoops_RPGP */
		a = _hoops_HSHGA / sc->_hoops_HICAH.x;
		b = _hoops_ISHGA / sc->_hoops_HICAH.y;
		_hoops_HHGGH = a*a + b*b;
		if (_hoops_HHGGH >= sc->_hoops_GICAH) return;

		/* _hoops_SCH'_hoops_GRI _hoops_AIRAI _hoops_PPR _hoops_IRS _hoops_RIRA _hoops_SPR */
	}

	/* _hoops_HGCR _hoops_AHCR */
	if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC)) _hoops_IHGGH = position->z;
	else {
		_hoops_IHGGH = _hoops_CPRA (_hoops_IHCR->matrix->data.elements, text->_hoops_CSAI);
		if (_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC))
			_hoops_IHGGH /= _hoops_PHCP (_hoops_IHCR->matrix->data.elements, text->_hoops_CSAI);
	}

	/* _hoops_RPGP _hoops_AHCR */
	if (_hoops_IHGGH < sc->bounding.hither || _hoops_IHGGH > sc->bounding.yon) return;

	/* _hoops_AICP _hoops_SCH. _hoops_SSCR _hoops_GGSR _hoops_PGAP _hoops_GAS. */

	if (dc->_hoops_IGHGH->_hoops_AHGGH != null) {
		/* _hoops_CCAAS, _hoops_CPSA _hoops_IRS _hoops_GPIAS _hoops_GSGR _hoops_HASRH, _hoops_IPGIR _hoops_SAHR _hoops_PRIA _hoops_SCH */
		HD_Elaborate_Selection (nr, (Geometry alter *)dc->_hoops_IGHGH->_hoops_AHGGH,
								dc->_hoops_IGHGH->_hoops_AHGGH->key, _hoops_AIRIR(dc->_hoops_IGHGH->_hoops_AHGGH),
								0, 0, 0,
								_hoops_IHGGH,
								_hoops_HHGGH, T_STRING_CURSORS, null);
		return;
	}	

	if (sc->_hoops_AICAH.x < left) { /* _hoops_PSP _hoops_AGRP */ }
	else if (_hoops_HSHGA > 0.0f) offset2 += count - 1;
	else {
		_hoops_RGGA (--count == 0) {
			float _hoops_CARPS;
			HD_Measure_Characters (nr, 1, _hoops_IHSCP, text->encoding, &_hoops_CARPS);
			left += (int)_hoops_CARPS;

			if (left > sc->_hoops_AICAH.x) break;  /* _hoops_CGI _hoops_SCH */
			++offset2;
			++_hoops_IHSCP;
		}
	}

	if (_hoops_HHGGH < dc->_hoops_IGHGH->_hoops_HHGGH) {
		dc->_hoops_IGHGH->_hoops_HHGGH	  = _hoops_HHGGH;
		dc->_hoops_IGHGH->_hoops_IHGGH	  = _hoops_IHGGH;
		dc->_hoops_IGHGH->_hoops_CHGGH = offset2;
	}
}


local void draw_3d_polyline (
	Net_Rendition const & nr,
	Polyline const		*pl) {
	/* _hoops_GRRRI _hoops_HCGR */

	HD_Select_Polyglin (nr, (Geometry alter *)pl, false);
}

local void draw_3d_polygon (
	Net_Rendition const & nr,
	Polygon const		*_hoops_RPIGA) {
	/* _hoops_GRRRI _hoops_HCGR */

	HD_Select_Polyglin (nr, (Geometry alter *)_hoops_RPIGA, true);
}
#endif


GLOBAL_FUNCTION void HD_Select_Text (
	Net_Rendition const &		nr,
	_hoops_HACC const *				text) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;
	_hoops_GHGGH				_hoops_IGHGH;
	_hoops_ACHR					_hoops_SARPS;

	if (BIT (sc->options, _hoops_IICAH)) {
		_hoops_IGCSR const &	_hoops_HRCIR = nr->_hoops_SISI;

		if (_hoops_HRCIR->transform != FT_FULL || (_hoops_HRCIR->_hoops_GHGRP != GSU_ORU && _hoops_HRCIR->_hoops_GHGRP != _hoops_SPSC)) {
			HD_Select_Dot (nr, (Geometry alter *)text, text->key, _hoops_AIRIR(text), T_TEXT, &text->_hoops_CSAI);
			return;
		}

		/* _hoops_SR _hoops_PAH _hoops_AA _hoops_IHIR _hoops_HIHP _hoops_GPRPS _hoops_HCGR -- _hoops_SCH _hoops_IAGA _hoops_RHIR _hoops_GAR _hoops_APGR */
	}

	/* _hoops_ASGGR _hoops_IH _hoops_GGSPR _hoops_AAH _hoops_GHSHA (_hoops_RPP _hoops_GII) _hoops_GPP _hoops_RGR _hoops_HCGR */
	_hoops_SARPS = nr->_hoops_IRR->_hoops_AAICA;
	_hoops_SARPS &= nr->_hoops_RGP |
						   nr->_hoops_IRR->_hoops_PHARP;

	_hoops_IGHGH._hoops_RHGGH = null;		/* _hoops_PIISR _hoops_GGR _hoops_HPP 3d_hoops_RPRPS */
	_hoops_IGHGH._hoops_AHGGH = null;
	_hoops_IGHGH._hoops_PHGGH = 0;
	_hoops_IGHGH._hoops_HHGGH = sc->_hoops_GICAH + 0.001f;
	_hoops_IGHGH._hoops_IHGGH = 0.0f;
	_hoops_IGHGH._hoops_CHGGH = -1;
	_hoops_IGHGH._hoops_SHGGH = _hoops_SARPS;

	dc->_hoops_IGHGH = &_hoops_IGHGH;

	_hoops_HGCGA (dc, "text selection", nr);
	dc->_hoops_IPCI->_hoops_CSCGA = HD_Standard_Draw_Inter_Text;
	dc->_hoops_IPCI->_hoops_AGCSR = _hoops_AGCSR;
	dc->_hoops_IPCI->draw_dc_polyline = _hoops_CRRPS;
	dc->_hoops_IPCI->draw_dc_polytriangle = _hoops_SRRPS;
	dc->_hoops_IPCI->draw_3d_polyline = draw_3d_polyline;
	dc->_hoops_IPCI->draw_3d_polygon = draw_3d_polygon;
	dc->_hoops_IPCI->draw_3d_ellipse = HD_Std_3D_Ellipse;
	dc->_hoops_IPCI->draw_3d_elliptical_arc = HD_Std_3D_Elliptical_Arc;
	dc->_hoops_IPCI->_hoops_SPCGA = _hoops_RARPS;
	dc->_hoops_IPCI->_hoops_CRCGA = _hoops_GARPS;

	HD_Std_3D_Text (nr, text);

	_hoops_HGSGA (dc, "text selection");

	dc->_hoops_IGHGH = null;


	/* _hoops_SSAS _hoops_SR _hoops_HGCR _hoops_SPR? */
	if (_hoops_IGHGH._hoops_CHGGH != -1) {
		HD_Elaborate_Selection (nr, (Geometry alter *)text, text->key, _hoops_AIRIR(text),
								0, _hoops_IGHGH._hoops_CHGGH, 0,
								_hoops_IGHGH._hoops_IHGGH,
								_hoops_IGHGH._hoops_HHGGH, T_TEXT, null);
	}
#endif
}

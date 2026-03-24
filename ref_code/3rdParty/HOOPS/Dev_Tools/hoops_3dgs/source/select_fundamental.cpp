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
 * $Id: obf_tmp.txt 1.111 2010-08-06 19:05:09 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "select.h"
#include "tandt.h"
#include "topology.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



/*
 * _hoops_AHGHR 2D (_hoops_HAS._hoops_IAS. _hoops_AHCR _hoops_HRGR _hoops_IAIH) _hoops_III _hoops_SGHC _hoops_CCPAS _hoops_PPR _hoops_SCPAS,
 * _hoops_CGIC _hoops_RPP _hoops_SSIA _hoops_ARCRA.	 _hoops_GCAAA _hoops_RH _hoops_HSPR _hoops_ACPP:
 *		1	 _hoops_APGR _hoops_SGHC _hoops_ARCRA _hoops_GGR _hoops_IRS _hoops_RSRA _hoops_PPSR
 *	   -1	 _hoops_APGR _hoops_CHR _hoops_SPRPA (_hoops_GGAIA, _hoops_ASPSR) _hoops_IH _hoops_HHH _hoops_SGAHP
 *		0	 _hoops_APGR _hoops_SGHC _hoops_AA _hoops_HAR _hoops_ARCRA, _hoops_PAR _hoops_HS _hoops_SASPR _hoops_RIHC _hoops_CICRR.
 * _hoops_IPCP _hoops_RIHRR _hoops_PPSR _hoops_IIGR _hoops_SGSSR (_hoops_RPP _hoops_HSGS) _hoops_HRGR _hoops_GIIA _hoops_RPP _hoops_RH
 * _hoops_ACRGI _hoops_IGI _hoops_IS _hoops_HGRAI _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_IRAP.
 */
GLOBAL_FUNCTION int HI_Intersect_Line_Segments_2D (
	Point		*_hoops_GGIAR,
	Point		*p1,
	Point		*_hoops_RICIH,
	Point		*_hoops_AICIH,
	Point		*_hoops_RSPSA) {
#ifndef DISABLE_POLY_SELECTION
	float			_hoops_GSPAS, _hoops_ICGHH, _hoops_RSPAS;
	Vector		_hoops_PAPH, _hoops_ASPAS, _hoops_RCIR;

	if (_hoops_GGIAR == p1 ||
		_hoops_RICIH == _hoops_AICIH ||
		_hoops_GGIAR == _hoops_RICIH ||
		p1 == _hoops_AICIH)
		return false;

	/*
	 * _hoops_PCSH _hoops_CCA _hoops_IRS _hoops_IASC-_hoops_AHCRR _hoops_ISPR
	 */
	if (p1->x >= _hoops_GGIAR->x) {
		if (_hoops_RICIH->x > p1->x && _hoops_AICIH->x > p1->x ||
			_hoops_RICIH->x < _hoops_GGIAR->x && _hoops_AICIH->x < _hoops_GGIAR->x) return 0;
	}
	else {
		if (_hoops_RICIH->x > _hoops_GGIAR->x && _hoops_AICIH->x > _hoops_GGIAR->x ||
			_hoops_RICIH->x < p1->x && _hoops_AICIH->x < p1->x) return 0;
	}

	if (p1->y >= _hoops_GGIAR->y) {
		if (_hoops_RICIH->y > p1->y && _hoops_AICIH->y > p1->y ||
			_hoops_RICIH->y < _hoops_GGIAR->y && _hoops_AICIH->y < _hoops_GGIAR->y) return 0;
	}
	else {
		if (_hoops_RICIH->y > _hoops_GGIAR->y && _hoops_AICIH->y > _hoops_GGIAR->y ||
			_hoops_RICIH->y < p1->y && _hoops_AICIH->y < p1->y) return 0;
	}


	_hoops_PAPH.x = p1->x - _hoops_GGIAR->x;
	_hoops_PAPH.y = p1->y - _hoops_GGIAR->y;

	_hoops_ASPAS.x = _hoops_AICIH->x - _hoops_RICIH->x;
	_hoops_ASPAS.y = _hoops_AICIH->y - _hoops_RICIH->y;

	_hoops_RCIR.x = _hoops_RICIH->x - _hoops_GGIAR->x;
	_hoops_RCIR.y = _hoops_RICIH->y - _hoops_GGIAR->y;

	_hoops_GSPAS = _hoops_ASPAS.x * _hoops_PAPH.y - _hoops_PAPH.x * _hoops_ASPAS.y;
	_hoops_ICGHH = _hoops_PAPH.x * _hoops_RCIR.y - _hoops_RCIR.x * _hoops_PAPH.y;

	if (_hoops_GSPAS == 0) {
		/* _hoops_ARHHI _hoops_GGAIA _hoops_IS _hoops_CCAHR */

		if (_hoops_ICGHH == 0)
			return -1; /* _hoops_SPRPA */
		else
			return 0;		   /* _hoops_PGICR _hoops_GGAIA */
	}
	if (_hoops_GSPAS > 0) {
		if (_hoops_ICGHH < 0 || _hoops_ICGHH > _hoops_GSPAS) return 0;
		_hoops_RSPAS = _hoops_ASPAS.x * _hoops_RCIR.y - _hoops_RCIR.x * _hoops_ASPAS.y;
		if (_hoops_RSPAS < 0 || _hoops_RSPAS > _hoops_GSPAS) return 0;
	}
	else {
		if (_hoops_ICGHH > 0 || _hoops_ICGHH < _hoops_GSPAS) return 0;
		_hoops_RSPAS = _hoops_ASPAS.x * _hoops_RCIR.y - _hoops_RCIR.x * _hoops_ASPAS.y;
		if (_hoops_RSPAS > 0 || _hoops_RSPAS < _hoops_GSPAS) return 0;
	}

	if (_hoops_RSPSA != null) {
		_hoops_ICGHH /= _hoops_GSPAS;
		_hoops_RSPSA->x = _hoops_RICIH->x + _hoops_ICGHH * _hoops_ASPAS.x;
		_hoops_RSPSA->y = _hoops_RICIH->y + _hoops_ICGHH * _hoops_ASPAS.y;
		_hoops_RSPSA->z = 0.0f;
	}

	return 1;
#else
	return 0;
#endif
}


#ifndef DISABLE_POLY_SELECTION

local void _hoops_PSPAS (
	Vector alter		*_hoops_PAHHA,
	_hoops_RGASA alter *tree,
	int alter			*_hoops_HSPAS,
	int alter			*_hoops_SGHPR) {
	float				_hoops_SAIAR;
	Vector alter		*_hoops_ISPAS = &tree->_hoops_GRASA;

	_hoops_SAIAR = _hoops_PAHHA->x * _hoops_ISPAS->y - _hoops_ISPAS->x * _hoops_PAHHA->y;
	if (_hoops_SAIAR == 0.0f) {
		/* _hoops_HGGS _hoops_SSPAA _hoops_IGIAR _hoops_RH _hoops_PHCRA */
		*_hoops_HSPAS = *_hoops_SGHPR = tree->_hoops_HGASA;
	}
	else if (_hoops_SAIAR < 0) {
		/*
		 * _hoops_HGGS _hoops_HRGR _hoops_CRAPH-_hoops_SRGGA _hoops_CSCHR _hoops_IS _hoops_PHCRA,
		 * _hoops_SR'_hoops_GCPP _hoops_IRAA _hoops_RH _hoops_RPHR _hoops_RPSI, _hoops_IS _hoops_ASRHA _hoops_RH _hoops_CIHA
		 */
		*_hoops_HSPAS = tree->_hoops_HGASA;
		if (tree->right != null)
			_hoops_PSPAS (_hoops_PAHHA, tree->right, _hoops_HSPAS, _hoops_SGHPR);
	}
	else {
		/*
		 * _hoops_HGGS _hoops_HRGR _hoops_SRGGA _hoops_CSCHR _hoops_IS _hoops_PHCRA,
		 * _hoops_SR'_hoops_GCPP _hoops_IRAA _hoops_RH _hoops_RAAP _hoops_RPSI, _hoops_IS _hoops_CSPAS _hoops_RH _hoops_CIHA
		 */
		*_hoops_SGHPR = tree->_hoops_HGASA;
		if (tree->left != null)
			_hoops_PSPAS (_hoops_PAHHA, tree->left, _hoops_HSPAS, _hoops_SGHPR);
	}
}

#endif


GLOBAL_FUNCTION bool HD_Select_Point_By_Polygon (
	Net_Rendition const &			nr,
	DC_Point alter *				center) {
#ifndef DISABLE_POLY_SELECTION
	_hoops_ACCCP alter	*		sc = nr->_hoops_SRA->_hoops_APHHP;
	Vector							target;
	int								_hoops_RHPCP, _hoops_AHPCP;
	DC_Point						_hoops_CPPCP, _hoops_HCPSR;

	if (sc->_hoops_HAPAS != null) {
		target.x = center->x - sc->_hoops_GPIS.x;
		target.y = center->y - sc->_hoops_GPIS.y;
		target.z = 0.0f;

		if (sc->_hoops_IAPAS) {
			_hoops_RHPCP = 0;
			_hoops_AHPCP = 1;
		}
		else {
			_hoops_RHPCP = 1;
			_hoops_AHPCP = 0;
		}
		_hoops_PSPAS (&target, sc->_hoops_HAPAS, &_hoops_RHPCP, &_hoops_AHPCP);

		_hoops_CPPCP.x = sc->_hoops_RAPAS[_hoops_RHPCP].x - sc->_hoops_RAPAS[_hoops_AHPCP].x;
		_hoops_CPPCP.y = sc->_hoops_RAPAS[_hoops_RHPCP].y - sc->_hoops_RAPAS[_hoops_AHPCP].y;
		_hoops_HCPSR.x = center->x - sc->_hoops_RAPAS[_hoops_AHPCP].x;
		_hoops_HCPSR.y = center->y - sc->_hoops_RAPAS[_hoops_AHPCP].y;

		return (_hoops_CPPCP.x * _hoops_HCPSR.y <= _hoops_CPPCP.y * _hoops_HCPSR.x);
	}
	else {		/* _hoops_HAR _hoops_IRS _hoops_SGCS _hoops_SSPAS -- _hoops_RRP _hoops_GGHAS _hoops_RPGP */
		_hoops_GPCIH							_hoops_RGHAS;
		_hoops_GPCIH alter					*_hoops_AGHAS = &_hoops_RGHAS;

		_hoops_RGHAS.next = null;
		_hoops_RGHAS.owner = _hoops_GAPAS;
		_hoops_RGHAS.region = _hoops_GAPAS;
		_hoops_RGHAS._hoops_GRCPR[_hoops_HRASA].pt[_hoops_PGHAS] = (Point *)center;
		_hoops_RGHAS._hoops_GRCPR[_hoops_HRASA].pt[_hoops_HGHAS] = (Point *)center;
		_hoops_RGHAS._hoops_GRCPR[_hoops_HRASA].owner = _hoops_GAPAS;
		_hoops_RGHAS._hoops_GRCPR[_hoops_HRASA].region = _hoops_GAPAS;
		_hoops_RGHAS._hoops_GRCPR[_hoops_HRASA]._hoops_HASHH = true;
		_hoops_RGHAS._hoops_GRCPR[_hoops_IGHAS].pt[_hoops_PGHAS] = (Point *)center;
		_hoops_RGHAS._hoops_GRCPR[_hoops_IGHAS].pt[_hoops_HGHAS] = (Point *)center;
		_hoops_RGHAS._hoops_GRCPR[_hoops_IGHAS].owner = _hoops_GAPAS;
		_hoops_RGHAS._hoops_GRCPR[_hoops_IGHAS].region = false;
		_hoops_RGHAS._hoops_GRCPR[_hoops_IGHAS]._hoops_HASHH = true;
		_hoops_RGHAS._hoops_HASHH = true;
		_hoops_RGHAS._hoops_SSAGS[_hoops_HRASA] = _hoops_RGHAS._hoops_SSAGS[_hoops_IGHAS] = 0.0f;
		_hoops_RGHAS.type = _hoops_CGHAS;

		return	HI_Wings_Intersect (1, &_hoops_AGHAS, sc->_hoops_CAPAS, sc->_hoops_SAPAS) > 0;
	}
#else
	return false;
#endif
}



GLOBAL_FUNCTION bool HD_Select_Circle_By_Polyline (
	Net_Rendition const &		nr,
	DC_Point alter		*		center,
	float						radius) {
#ifndef DISABLE_POLY_SELECTION
	_hoops_ACCCP alter	*	sc = nr->_hoops_SRA->_hoops_APHHP;
	Point alter *				origin = &sc->_hoops_RAPAS[-1];
	Vector alter *				vector = &sc->_hoops_AAPAS[-1];
	float alter *				scale = &sc->_hoops_PAPAS[-1];
	int							count = sc->count;

	if (radius > 0.0f) {
		float					_hoops_SGHAS = radius * radius;

		while (--count) {
			float			_hoops_SSRP;
			float			_hoops_CGSIR;
			Vector		_hoops_GRHAS;
			Vector		projection;

			++origin; ++vector; ++scale;

			_hoops_GRHAS.x = center->x - origin->x;
			_hoops_GRHAS.y = center->y - origin->y;

			_hoops_SSRP = _hoops_GRHAS.x * vector->x + _hoops_GRHAS.y * vector->y;

			if (_hoops_SSRP > *scale) _hoops_SSRP = *scale;
			else if (_hoops_SSRP < 0.0f) _hoops_SSRP = 0.0f;

			projection.x = vector->x * _hoops_SSRP;
			projection.x -= _hoops_GRHAS.x + 0.5f;
			_hoops_CGSIR = projection.x * projection.x;
			if (_hoops_CGSIR > _hoops_SGHAS) continue;

			projection.y = vector->y * _hoops_SSRP;
			projection.y -= _hoops_GRHAS.y + 0.5f;
			_hoops_CGSIR += projection.y * projection.y;
			if (_hoops_CGSIR > _hoops_SGHAS) continue;

			return true;
		}
	}
	else {
		while (--count) {
			float			_hoops_SSRP;
			Vector		_hoops_GRHAS;

			++origin; ++vector; ++scale;

			_hoops_GRHAS.x = center->x - origin->x;
			_hoops_GRHAS.y = center->y - origin->y;

			_hoops_SSRP = _hoops_GRHAS.x * vector->x + _hoops_GRHAS.y * vector->y;

			if (_hoops_SSRP < 0.0f || _hoops_SSRP > *scale ||
				vector->x * _hoops_SSRP != _hoops_GRHAS.x ||
				vector->y * _hoops_SSRP != _hoops_GRHAS.y) continue;

			return true;
		}
	}

#endif
	return false;
}



#ifndef DISABLE_POLY_SELECTION

local void _hoops_RRHAS (
	Net_Rendition const &		nr,
	Geometry const *			geometry,
	bool						_hoops_SPGPA) {

	switch (geometry->type) {
		case _hoops_RCIP:
			if (_hoops_SPGPA)
				HD_Std_3D_Polygon (nr, (Polygon const *)geometry);
			else
				HD_Std_3D_Polyline (nr, (Polyline const *)geometry);
			break;
		case _hoops_CHIP:
			HD_Std_3D_NURBS_Curve(nr, (_hoops_PIRGR alter *)geometry);
			break;
		case _hoops_GIIP:
		case _hoops_RIIP:
			HD_Std_3D_Elliptical_Arc(nr, (Elliptical_Arc const *)geometry);
			break;
		case _hoops_SIIP:
			HD_Std_3D_Infinite_Line(nr, (Polyline const *)geometry);
			break;
		case _hoops_SGCP:
		case _hoops_CGCP:
			HD_Std_3D_Ellipse(nr, (Ellipse const *)geometry);
			break;
		case _hoops_PIIP:
		case _hoops_HIIP:
		case _hoops_IIIP:
			HD_Std_3D_Polyline(nr, (Polyline const *)geometry);
			break;
		default:
			_hoops_IPR(HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Not implemented in cutting plane select");
	}
}

local bool _hoops_ARHAS (
	Net_Rendition const &		nr,
	Geometry const *			geometry,
	int							count,
	Point const *				pl,
	bool						_hoops_SPGPA,
	bool						_hoops_CSHIH) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	Point alter *				pp;
	Point alter *				pe;
	Point alter *				points;
	_hoops_GPCIH alter * alter *		_hoops_PRHAS;
	int							_hoops_HRHAS;
	int							_hoops_IRHAS = 0;

	if (nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		sc->_hoops_HPPAS._hoops_CIHIA = false;
		_hoops_RRHAS(nr, geometry, _hoops_SPGPA);
		return sc->_hoops_HPPAS._hoops_CIHIA;
	}

	/*
	 * _hoops_RHRRA: _hoops_PCPA _hoops_AHCA _hoops_CAHC _hoops_RIP ?
	 * _hoops_RHRRA: _hoops_RRP _hoops_IS _hoops_RGHH _hoops_AGSAR _hoops_GHIPR _hoops_RH _hoops_RHC
	 */
	if (count == 1) 
		ALLOC_ARRAY (points, 2, Point);
	else 
		ALLOC_ARRAY (points, count, Point);

	pp = points;
	pe = pp + count;

	if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC))
		do {
			pp->x = _hoops_HPRA (elements, pl[0]);
			pp->y = _hoops_IPRA (elements, pl[0]);
			pp->z = 0.0f; /* _hoops_IH _hoops_IGAAI - _hoops_HAR _hoops_CPSA _hoops_SIGR */
			++pl;
		} _hoops_RGGA (++pp == pe);
	else {
		float			w;

		do {
			w = _hoops_PHCP (elements, pl[0]);
			if (w >= _hoops_IHCR->_hoops_CHCR) {
				pp->x = _hoops_HPRA (elements, pl[0]) / w;
				pp->y = _hoops_IPRA (elements, pl[0]) / w;
			}
			else {
#if 0
				pp->x = _hoops_HPRA (_hoops_IHCR->matrix->elements, pl[0]);
				pp->y = _hoops_IPRA (_hoops_IHCR->matrix->elements, pl[0]);
#endif
				sc->_hoops_HPPAS._hoops_CIHIA = false;
				HD_Std_3D_Polyline (nr, (Polyline const *)geometry);

				if (count == 1) 
					FREE_ARRAY (points, 2, Point);
				else 
					FREE_ARRAY (points, count, Point);

				return sc->_hoops_HPPAS._hoops_CIHIA;
			}
			pp->z = 0.0f; /* _hoops_IH _hoops_IGAAI - _hoops_HAR _hoops_CPSA _hoops_SIGR */
			++pl;
		} _hoops_RGGA (++pp == pe);
	}

	if (count == 1) {
		points[1] = points[0];
		count = 2;
	}


	if (!_hoops_CSHIH && count > 2 &&
		points[0].y == points[count-1].y && points[0].x != points[count-1].x) {
		for (int i=0; i<count-1; ++i) {
			_hoops_HRHAS = HI_Create_Polyglin_Wings (2, &points[i],
														  false, _hoops_GAPAS,
														  &_hoops_PRHAS);
			_hoops_IRHAS = HI_Wings_Intersect (_hoops_HRHAS, _hoops_PRHAS,
											 sc->_hoops_CAPAS, sc->_hoops_SAPAS);

			HI_Free_Wings (_hoops_HRHAS, _hoops_PRHAS);

			if (_hoops_IRHAS)
				break;
		}
	}
	else {
		_hoops_HRHAS = HI_Create_Polyglin_Wings (count, points,
													  _hoops_CSHIH, _hoops_GAPAS,
													  &_hoops_PRHAS);
		_hoops_IRHAS = HI_Wings_Intersect (_hoops_HRHAS, _hoops_PRHAS,
										 sc->_hoops_CAPAS, sc->_hoops_SAPAS);

		HI_Free_Wings (_hoops_HRHAS, _hoops_PRHAS);
	}

	if (_hoops_IRHAS < 0) {
		/* _hoops_CRHAS _hoops_RPGP _hoops_SGPSA _hoops_CRGR _hoops_SPGC, _hoops_SGH _hoops_SRHAS _hoops_HHSA */
		Point				_hoops_IPPSH;
		Point *				_hoops_GAHAS;
		Point *				_hoops_RAHAS = sc->_hoops_RAPAS + sc->count;

		_hoops_IRHAS = 0;

		pp = points;
		if (_hoops_SPGPA)
			_hoops_GAHAS = pe-1;
		else
			_hoops_GAHAS = pp++;

		while (pp != pe && !_hoops_IRHAS) {
			Point *				_hoops_AAHAS;
			Point *				_hoops_CAARA;

			_hoops_CAARA = sc->_hoops_RAPAS;
			if (BIT (sc->options, _hoops_PRPAS))
				_hoops_AAHAS = _hoops_RAHAS-1;
			else
				_hoops_AAHAS = _hoops_CAARA++;

			while (_hoops_CAARA != _hoops_RAHAS && !_hoops_IRHAS) {
				if (HI_Intersect_Line_Segments_2D (_hoops_GAHAS, pp, _hoops_AAHAS, _hoops_CAARA,
												   &_hoops_IPPSH))
					_hoops_IRHAS = 1;
				_hoops_AAHAS = _hoops_CAARA++;
			}

			_hoops_GAHAS = pp++;
		}

		if (!_hoops_IRHAS) {
			Point const *		_hoops_HAPAR;

			/* _hoops_RPP _hoops_PGI _hoops_SCIRA _hoops_PAR _hoops_PAHAS _hoops_HRGR _hoops_IRS _hoops_HSSP, _hoops_CACH _hoops_RPP _hoops_IRS _hoops_PPSR _hoops_GPP
			 * _hoops_RH _hoops_RII _hoops_HRGR _hoops_ASSA _hoops_SCH
			 */

			if (BIT (sc->options, _hoops_PRPAS)) {
				pp = sc->_hoops_RAPAS;
				pe = _hoops_RAHAS = sc->_hoops_RAPAS + sc->count;
				_hoops_HAPAR = points;
			}
			else if (_hoops_SPGPA) {
				pp = points;			/* _hoops_SAHA _hoops_HGGC _hoops_IHRI :) */
				_hoops_HAPAR = sc->_hoops_RAPAS;
			}
			else {
				pp = null;				/* _hoops_SAHA,_hoops_CHSPR _hoops_GA'_hoops_RA _hoops_RPSHR */
				_hoops_HAPAR = null;
			}

			if (pp != null) {
				_hoops_GAHAS = pe-1;
				/* _hoops_RPP _hoops_RPGP _hoops_PPSR _hoops_ASSA _hoops_ISPH _hoops_HAHAS->_hoops_SAHA, _hoops_SR _hoops_HS _hoops_IRS _hoops_RHHR */
				while (pp != pe) {
					if (_hoops_GAHAS->x <= _hoops_HAPAR->x && pp->x > _hoops_HAPAR->x	||
						pp->x <= _hoops_HAPAR->x && _hoops_GAHAS->x > _hoops_HAPAR->x) {
						float			y;

						y = _hoops_GAHAS->y + (pp->y - _hoops_GAHAS->y) *
										(_hoops_HAPAR->x - _hoops_GAHAS->x) / (pp->x - _hoops_GAHAS->x);

						if (y > _hoops_HAPAR->y)	/* _hoops_GIARC _hoops_GPP _hoops_GRR _hoops_ACCGI _hoops_HPGAS */
							_hoops_IRHAS = 1-_hoops_IRHAS;
					}
					_hoops_GAHAS = pp++;
				}
			}
		}
	}

	FREE_ARRAY (points, count, Point);

	return (_hoops_IRHAS > 0);
}

local bool _hoops_IAHAS (
	Net_Rendition const &		nr,
	int							count,
	Point *						points,
	bool						_hoops_SPGPA,
	bool						_hoops_CSHIH) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter *	sc = dc->_hoops_APHHP;
	_hoops_GPCIH alter * alter *		_hoops_PRHAS;
	int							_hoops_HRHAS;
	int							_hoops_IRHAS = 0;

	if (count < 0) {
		count = -count / 2;

		while (count-- > 0) {
			if (_hoops_IAHAS (nr, 2, points, _hoops_SPGPA, _hoops_CSHIH))
				return true;

			points += 2;
		}

		return false;
	}

	if (!_hoops_CSHIH && count > 2 &&
		points[0].y == points[count-1].y && points[0].x != points[count-1].x) {
		for (int i=0; i<count-1; ++i) {
			_hoops_HRHAS = HI_Create_Polyglin_Wings (2, &points[i],
														  false, _hoops_GAPAS,
														  &_hoops_PRHAS);
			_hoops_IRHAS = HI_Wings_Intersect (_hoops_HRHAS, _hoops_PRHAS,
											 sc->_hoops_CAPAS, sc->_hoops_SAPAS);

			HI_Free_Wings (_hoops_HRHAS, _hoops_PRHAS);

			if (_hoops_IRHAS)
				break;
		}
	}
	else {
		_hoops_HRHAS = HI_Create_Polyglin_Wings (count, points,
													  _hoops_CSHIH, _hoops_GAPAS,
													  &_hoops_PRHAS);
		_hoops_IRHAS = HI_Wings_Intersect (_hoops_HRHAS, _hoops_PRHAS,
										 sc->_hoops_CAPAS, sc->_hoops_SAPAS);

		HI_Free_Wings (_hoops_HRHAS, _hoops_PRHAS);
	}

	if (_hoops_IRHAS < 0) {
		/* _hoops_CRHAS _hoops_RPGP _hoops_SGPSA _hoops_CRGR _hoops_SPGC, _hoops_SGH _hoops_SRHAS _hoops_HHSA */
		Point				_hoops_IPPSH;
		Point *				_hoops_GAHAS;
		Point *				_hoops_RAHAS = sc->_hoops_RAPAS + sc->count;
		Point alter			*pp = points;
		Point alter			*pe = pp + count;

		_hoops_IRHAS = 0;

		if (_hoops_SPGPA)
			_hoops_GAHAS = pe-1;
		else
			_hoops_GAHAS = pp++;

		while (pp != pe && !_hoops_IRHAS) {
			Point *				_hoops_AAHAS;
			Point *				_hoops_CAARA;

			_hoops_CAARA = sc->_hoops_RAPAS;
			if (BIT (sc->options, _hoops_PRPAS))
				_hoops_AAHAS = _hoops_RAHAS-1;
			else
				_hoops_AAHAS = _hoops_CAARA++;

			while (_hoops_CAARA != _hoops_RAHAS && !_hoops_IRHAS) {
				if (HI_Intersect_Line_Segments_2D (_hoops_GAHAS, pp, _hoops_AAHAS, _hoops_CAARA,
												   &_hoops_IPPSH))
					_hoops_IRHAS = 1;
				_hoops_AAHAS = _hoops_CAARA++;
			}

			_hoops_GAHAS = pp++;
		}

		if (!_hoops_IRHAS) {
			Point const *		_hoops_HAPAR;

			/* _hoops_RPP _hoops_PGI _hoops_SCIRA _hoops_PAR _hoops_PAHAS _hoops_HRGR _hoops_IRS _hoops_HSSP, _hoops_CACH _hoops_RPP _hoops_IRS _hoops_PPSR _hoops_GPP
			 * _hoops_RH _hoops_RII _hoops_HRGR _hoops_ASSA _hoops_SCH
			 */

			if (BIT (sc->options, _hoops_PRPAS)) {
				pp = sc->_hoops_RAPAS;
				pe = _hoops_RAHAS = sc->_hoops_RAPAS + sc->count;
				_hoops_HAPAR = points;
			}
			else if (_hoops_SPGPA) {
				pp = points;			/* _hoops_SAHA _hoops_HGGC _hoops_IHRI :) */
				_hoops_HAPAR = sc->_hoops_RAPAS;
			}
			else {
				pp = null;				/* _hoops_SAHA,_hoops_CHSPR _hoops_GA'_hoops_RA _hoops_RPSHR */
				_hoops_HAPAR = null;
			}

			if (pp != null) {
				_hoops_GAHAS = pe-1;
				/* _hoops_RPP _hoops_RPGP _hoops_PPSR _hoops_ASSA _hoops_ISPH _hoops_HAHAS->_hoops_SAHA, _hoops_SR _hoops_HS _hoops_IRS _hoops_RHHR */
				while (pp != pe) {
					if (_hoops_GAHAS->x <= _hoops_HAPAR->x && pp->x > _hoops_HAPAR->x	||
						pp->x <= _hoops_HAPAR->x && _hoops_GAHAS->x > _hoops_HAPAR->x) {
						float			y;

						y = _hoops_GAHAS->y + (pp->y - _hoops_GAHAS->y) *
										(_hoops_HAPAR->x - _hoops_GAHAS->x) / (pp->x - _hoops_GAHAS->x);

						if (y > _hoops_HAPAR->y)	/* _hoops_GIARC _hoops_GPP _hoops_GRR _hoops_ACCGI _hoops_HPGAS */
							_hoops_IRHAS = 1-_hoops_IRHAS;
					}
					_hoops_GAHAS = pp++;
				}
			}
		}
	}

	return (_hoops_IRHAS > 0);
}
#endif


#ifndef DISABLE_SELECTION

local bool _hoops_CAHAS (
	Net_Rendition const &		nr,
	Geometry const *			geometry,
	int							_hoops_ICGPA,
	Point const *				_hoops_IAIRA,
	bool						_hoops_SPGPA,
	bool						_hoops_CSHIH,
	int alter *					offset1,
	int alter *					offset2,
	float alter *				_hoops_HISAP,
	float alter *				_hoops_RCSAP) {
	Point const *				pl = _hoops_IAIRA;
	Point const *				end;
	int							count = _hoops_ICGPA;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	Point const *				_hoops_SAHAS;
	float						_hoops_AGRSH, _hoops_PGRSH, _hoops_HGRSH,
								x1 = 0.0f, _hoops_AGSIR = 0.0f, _hoops_HGSIR = 0.0f,
								_hoops_HSHGA, _hoops_ISHGA, _hoops_CSHGA,
								xc, yc,
								_hoops_GPHAS, _hoops_RPHAS,
								_hoops_APHAS, _hoops_PPHAS = 0.0f,
								_hoops_HPHAS, _hoops_IPHAS = 0.0f,
								_hoops_CPHAS, _hoops_SPHAS = 0.0f,
								_hoops_GHHAS = 0.0f, _hoops_RHHAS = 0.0f,
								tc,
								_hoops_AHHAS = 0.0f,
								_hoops_SIGGA,
								_hoops_CIGGA,
								_hoops_PHHAS,
								_hoops_CIPAS,
								_hoops_HHHAS = 0.0f;
	Point						first;
	bool						_hoops_CARGA = false,
								_hoops_IHHAS = false;
	int							_hoops_CHHAS = 0,
								offset = 0;
	int							off1, off2;
	bool						_hoops_SHHAS = false;
	_hoops_ARPA						plane;
	bool						_hoops_HHAHR = false;
	float						_hoops_HPCII;
	_hoops_IAPA const *	_hoops_GIHAS = null;

	*offset1 = -1;
	*offset2 = -1;

	if (BIT (_hoops_IHCR->flags, _hoops_CSP))
		_hoops_GIHAS = _hoops_IHCR->_hoops_RGH->_hoops_PHCA;

	end = pl + count;
	*_hoops_HISAP = sc->_hoops_GICAH;

	if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
		first.x = x1 = _hoops_HPRA (elements, pl[0]);
		first.y = _hoops_AGSIR = _hoops_IPRA (elements, pl[0]);
		first.z = _hoops_HGSIR = _hoops_CPRA (elements, pl[0]);
	}
	else {
		_hoops_PPHAS = _hoops_HPRA (elements, pl[0]);
		_hoops_IPHAS = _hoops_IPRA (elements, pl[0]);
		_hoops_SPHAS = _hoops_CPRA (elements, pl[0]);
		_hoops_HHHAS = _hoops_RHHAS = _hoops_PHCP (elements, pl[0]);
		if (_hoops_RHHAS >= _hoops_IHCR->_hoops_CHCR) {
			first.x = x1 = _hoops_PPHAS / _hoops_RHHAS;
			first.y = _hoops_AGSIR = _hoops_IPHAS / _hoops_RHHAS;
			first.z = _hoops_HGSIR = _hoops_SPHAS / _hoops_RHHAS;
			_hoops_IHHAS = true;
		}
		else
			first.x = first.y = first.z = 0.0f;
	}

	_hoops_AGRSH = 0.0f;
	_hoops_PGRSH = 0.0f;
	_hoops_HGRSH = 0.0f;

	_hoops_RGGA ((++offset, _hoops_SAHAS = pl, ++pl) == end) {
		_hoops_IAPA const *	_hoops_HRCAR;

		if (_hoops_HHAHR) {		/* (_hoops_IRGGS _hoops_RAAP _hoops_IAPR _hoops_HII _hoops_PGHC _hoops_HAPR) */
			x1 = _hoops_AGRSH;
			_hoops_AGSIR = _hoops_PGRSH;
			_hoops_HGSIR = _hoops_HGRSH;
			_hoops_HHAHR = false;
		}

		/* 1)  _hoops_CAAA _hoops_IS _hoops_SHPR _hoops_PCRR (_hoops_HII _hoops_CIHH _hoops_PCPH) */

		if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
			_hoops_AGRSH = x1;
			_hoops_PGRSH = _hoops_AGSIR;
			_hoops_HGRSH = _hoops_HGSIR;
			x1 = _hoops_HPRA (elements, pl[0]);
			_hoops_AGSIR = _hoops_IPRA (elements, pl[0]);
			_hoops_HGSIR = _hoops_CPRA (elements, pl[0]);

			_hoops_RIHAS:;
		}
		else {
			_hoops_APHAS = _hoops_PPHAS;
			_hoops_HPHAS = _hoops_IPHAS;
			_hoops_CPHAS = _hoops_SPHAS;
			_hoops_GHHAS = _hoops_RHHAS;

			_hoops_PPHAS = _hoops_HPRA (elements, pl[0]);
			_hoops_IPHAS = _hoops_IPRA (elements, pl[0]);
			_hoops_SPHAS = _hoops_CPRA (elements, pl[0]);
			_hoops_RHHAS = _hoops_PHCP (elements, pl[0]);

			if (_hoops_GHHAS < _hoops_IHCR->_hoops_CHCR) {
				if (_hoops_RHHAS < _hoops_IHCR->_hoops_CHCR) { /* _hoops_GIPR _hoops_CHR _hoops_GHIPR */
					continue;
				}

				/* '0' _hoops_PPSR _hoops_HRGR _hoops_GHIPR _hoops_RH _hoops_SARA; '1' _hoops_HRGR _hoops_GGR _hoops_RIPS */

				x1 = _hoops_PPHAS / _hoops_RHHAS;
				_hoops_AGSIR = _hoops_IPHAS / _hoops_RHHAS;
				_hoops_HGSIR = _hoops_SPHAS / _hoops_RHHAS;

				/* _hoops_SSS '_hoops_RA' _hoops_HGPP _hoops_SGS _hoops_SSCHA _hoops_HRGR _hoops_SASPR _hoops_IS +_hoops_PRSHA,
				   _hoops_PSCR _hoops_CAHA _hoops_RH _hoops_SISR/_hoops_SSCHA _hoops_PPR _hoops_HAPC/_hoops_SSCHA _hoops_HPGR _hoops_SGS _hoops_PPSR */

				_hoops_AHHAS = (_hoops_IHCR->_hoops_CHCR - _hoops_RHHAS) / (_hoops_GHHAS - _hoops_RHHAS);
				_hoops_AGRSH = (_hoops_PPHAS + (_hoops_APHAS - _hoops_PPHAS) * _hoops_AHHAS) / _hoops_IHCR->_hoops_CHCR;
				_hoops_PGRSH = (_hoops_IPHAS + (_hoops_HPHAS - _hoops_IPHAS) * _hoops_AHHAS) / _hoops_IHCR->_hoops_CHCR;
				_hoops_HGRSH = (_hoops_SPHAS + (_hoops_CPHAS - _hoops_SPHAS) * _hoops_AHHAS) / _hoops_IHCR->_hoops_CHCR;
				if (!_hoops_IHHAS) {
					first.x = _hoops_AGRSH;
					first.y = _hoops_PGRSH;
					first.z = _hoops_HGRSH;
					_hoops_IHHAS = true;
				}
				_hoops_CHHAS = 0;
			}
			else if (_hoops_RHHAS < _hoops_IHCR->_hoops_CHCR) {
				/* '0' _hoops_PPSR _hoops_HRGR _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_SARA; '1' _hoops_HRGR _hoops_GHIPR */

				_hoops_AGRSH = x1;		/* _hoops_RHGS _hoops_HSH _hoops_CGH _hoops_HGGC _hoops_SHH _hoops_PSIGA */
				_hoops_PGRSH = _hoops_AGSIR;		/* _hoops_RHGS _hoops_HSH _hoops_CGH _hoops_HGGC _hoops_SHH _hoops_PSIGA */
				_hoops_HGRSH = _hoops_HGSIR;		/* _hoops_RHGS _hoops_HSH _hoops_CGH _hoops_HGGC _hoops_SHH _hoops_PSIGA */

				_hoops_AHHAS = (_hoops_IHCR->_hoops_CHCR - _hoops_GHHAS) / (_hoops_RHHAS - _hoops_GHHAS);
				x1 = (_hoops_APHAS + (_hoops_PPHAS - _hoops_APHAS) * _hoops_AHHAS) / _hoops_IHCR->_hoops_CHCR;
				_hoops_AGSIR = (_hoops_HPHAS + (_hoops_IPHAS - _hoops_HPHAS) * _hoops_AHHAS) / _hoops_IHCR->_hoops_CHCR;
				_hoops_HGSIR = (_hoops_CPHAS + (_hoops_SPHAS - _hoops_CPHAS) * _hoops_AHHAS) / _hoops_IHCR->_hoops_CHCR;
				_hoops_CHHAS = 1;
			}
			else {
				_hoops_AGRSH = x1;
				_hoops_PGRSH = _hoops_AGSIR;
				_hoops_HGRSH = _hoops_HGSIR;
				x1 = _hoops_PPHAS / _hoops_RHHAS;
				_hoops_AGSIR = _hoops_IPHAS / _hoops_RHHAS;
				_hoops_HGSIR = _hoops_SPHAS / _hoops_RHHAS;
				_hoops_CHHAS = -1;
			}

			_hoops_AIHAS:;
		}

		/* 2) _hoops_RAH _hoops_IRS _hoops_HHCI _hoops_IASC _hoops_AHCRR _hoops_RPGP _hoops_GPP _hoops_SPCR */

		if (x1 < sc->bounding.left) {
			if (_hoops_AGRSH < sc->bounding.left)
				continue;
		}
		else if (x1 > sc->bounding.right) {
			if (_hoops_AGRSH > sc->bounding.right)
				continue;
		}

		/* 4) _hoops_RAH _hoops_IRS _hoops_HHCI _hoops_IASC _hoops_AHCRR _hoops_RPGP _hoops_GPP _hoops_GHCR */

		if (_hoops_AGSIR < sc->bounding.bottom) {
			if (_hoops_PGRSH < sc->bounding.bottom)
				continue;
		}
		else if (_hoops_AGSIR > sc->bounding.top) {
			if (_hoops_PGRSH > sc->bounding.top) {
				/* _hoops_PRIA _hoops_ASSA/_hoops_SIPP _hoops_RPGP _hoops_IH _hoops_HSSP _hoops_PIHAS */
				if (_hoops_AGRSH <= sc->_hoops_AICAH.x) {
					if (sc->_hoops_AICAH.x < x1) _hoops_CARGA = !_hoops_CARGA;
				}
				else if (x1 <= sc->_hoops_AICAH.x) {
					if (sc->_hoops_AICAH.x < _hoops_AGRSH) _hoops_CARGA = !_hoops_CARGA;
				}
				continue;
			}
		}

		/* 5) _hoops_ACGR _hoops_RH _hoops_HISGR _hoops_PPSR _hoops_IS _hoops_RH _hoops_HASRH _hoops_GPP _hoops_RH _hoops_PRISA _hoops_III ==

			_hoops_AHGHR _hoops_RH _hoops_PRISA _hoops_III _hoops_CGSSR:

				_hoops_SISR = _hoops_HIHAS + _hoops_IIHAS * _hoops_RA			(_hoops_IIHAS = _hoops_RCRIA - _hoops_HIHAS)
				_hoops_HAPC = _hoops_CIHAS + _hoops_SIHAS * _hoops_RA			(_hoops_SIHAS = _hoops_GSRIA - _hoops_CIHAS)


			_hoops_AHGHR _hoops_RH _hoops_IHGP _hoops_GIRA _hoops_HII _hoops_IRS _hoops_III _hoops_IS _hoops_IRS _hoops_PPSR (_hoops_GCHAS, _hoops_RCHAS):

				 2			 2			 2
				_hoops_PCCIR  = (_hoops_SISR - _hoops_GCHAS)  + (_hoops_HAPC - _hoops_RCHAS)

																	   2
			_hoops_SPAA _hoops_RH _hoops_RA-_hoops_PIRA _hoops_HPGR _hoops_RH _hoops_HISGR _hoops_CCHRA - _hoops_RH _hoops_AASC _hoops_IIGR _hoops_PCCIR	 - _hoops_HRGR,
			_hoops_RRPS _hoops_IS _hoops_GAIPA:

					  _hoops_IIHAS * (_hoops_GCHAS - _hoops_HIHAS) + _hoops_SIHAS * (_hoops_RCHAS - _hoops_CIHAS)
				_hoops_ACHAS =  -------------------------------
								   2	 2
								 _hoops_IIHAS	 + _hoops_SIHAS

		*/

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
				_hoops_HPCII = _hoops_HGRSH; _hoops_HGRSH = _hoops_HGSIR; _hoops_HGSIR = _hoops_HPCII;
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

		/* _hoops_PRIA _hoops_ASSA/_hoops_SIPP _hoops_RPGP _hoops_IH _hoops_HSSP _hoops_PIHAS */
		/* (_hoops_AISRA, _hoops_RPR _hoops_RSH _hoops_AHPH _hoops_SPPR _hoops_RIH _hoops_ACCGI) */
		if (yc >= sc->_hoops_AICAH.y) {
			if (_hoops_AGRSH <= sc->_hoops_AICAH.x) {
				if (sc->_hoops_AICAH.x < x1) _hoops_CARGA = !_hoops_CARGA;
			}
			else if (x1 <= sc->_hoops_AICAH.x) {
				if (sc->_hoops_AICAH.x < _hoops_AGRSH) _hoops_CARGA = !_hoops_CARGA;
			}
		}

		/* 6) _hoops_CCHAS _hoops_RPGP _hoops_GPP _hoops_RH _hoops_HISGR _hoops_PPSR */

		_hoops_GPHAS = (xc - sc->_hoops_AICAH.x) / sc->_hoops_HICAH.x;
		_hoops_RPHAS = (yc - sc->_hoops_AICAH.y) / sc->_hoops_HICAH.y;
		_hoops_CIPAS = _hoops_GPHAS*_hoops_GPHAS + _hoops_RPHAS*_hoops_RPHAS;

		if (_hoops_CIPAS > sc->_hoops_GICAH) continue;

		/* _hoops_APSH _hoops_RRRIR _hoops_RIRA - _hoops_HA _hoops_AA _hoops_IHIR-_hoops_CSRA _hoops_PCGC */

		_hoops_CSHGA = _hoops_HGSIR - _hoops_HGRSH;

		/* 7) _hoops_IHHSI _hoops_RH _hoops_III _hoops_ACSRR _hoops_RH _hoops_HPPA _hoops_GHC, _hoops_RPP _hoops_GII */

		_hoops_HRCAR = _hoops_GIHAS;
		do {
			_hoops_CIGGA = 0.0f;
			_hoops_SIGGA = 1.0f;

			if (_hoops_HRCAR != null) {
				_hoops_GPPA const		*_hoops_IRCAR;

				_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA;
				do {
					float							_hoops_SCHAS, _hoops_GSHAS;

					_hoops_SCHAS = _hoops_IRCAR->_hoops_SPPA.a * _hoops_AGRSH + _hoops_IRCAR->_hoops_SPPA.b * _hoops_PGRSH +
							_hoops_IRCAR->_hoops_SPPA.c * _hoops_HGRSH + _hoops_IRCAR->_hoops_SPPA.d;
					_hoops_GSHAS = _hoops_IRCAR->_hoops_SPPA.a * x1 + _hoops_IRCAR->_hoops_SPPA.b * _hoops_AGSIR +
							_hoops_IRCAR->_hoops_SPPA.c * _hoops_HGSIR + _hoops_IRCAR->_hoops_SPPA.d;

					if (_hoops_SCHAS <= 0.0f) { /* _hoops_RSHAS _hoops_HRGR _hoops_PGPAA */
						if (_hoops_GSHAS <= 0.0f) {
							/* _hoops_PPAAI _hoops_HRGR _hoops_GACC _hoops_PGPAA. _hoops_GRSH _hoops_AGAPR. */
						}
						else {
							/* _hoops_PPAAI _hoops_HRGR _hoops_HAR _hoops_PGPAA. _hoops_PPRII _hoops_CCPH _hoops_ASHAS. */

							/* _hoops_IPCP _hoops_SGSSR _hoops_PPSR _hoops_IIGR _hoops_RH _hoops_ISHA _hoops_PPR _hoops_PSHAS _hoops_IPPA. */
							/* (_hoops_HSHAS _hoops_PPR _hoops_ISHAS _hoops_PAHHP _hoops_GGR _hoops_HRASR, _hoops_HIS _hoops_PAH'_hoops_RA _hoops_GHCH _hoops_HPP 0) */
							_hoops_AHHAS = _hoops_SCHAS / (_hoops_SCHAS - _hoops_GSHAS);

							if (_hoops_AHHAS < _hoops_SIGGA) {
								_hoops_SIGGA = _hoops_AHHAS;
								if (_hoops_CIGGA >= _hoops_SIGGA) break; /* _hoops_AIIA _hoops_PIRC _hoops_RAAP */
							}
						}
					}
					else {
						/* _hoops_RSHAS _hoops_HRGR _hoops_HAR _hoops_PGPAA */
						if (_hoops_GSHAS > 0.0f) {
							/* _hoops_PPAAI _hoops_HRGR _hoops_GACC _hoops_HAR _hoops_PGPAA. _hoops_GRSH _hoops_AGAPR. */
							_hoops_SIGGA = -999.0f; /* (_hoops_HHSA '_hoops_SAS' _hoops_CAPP) */
							break;
						}
						else {
							/* _hoops_PPAAI *_hoops_HRGR* _hoops_PGPAA. _hoops_PPRII _hoops_CCPH _hoops_CSHAS. */

							/* _hoops_IPCP _hoops_SGSSR _hoops_PPSR _hoops_IIGR _hoops_RH _hoops_ISHA _hoops_PPR _hoops_PSHAS _hoops_IPPA. */
							/* (_hoops_HSHAS _hoops_PPR _hoops_ISHAS _hoops_PAHHP _hoops_GGR _hoops_HRASR, _hoops_HIS _hoops_PSHAS _hoops_PAH'_hoops_RA _hoops_GHCH _hoops_HPP 0)*/
							_hoops_AHHAS = _hoops_SCHAS / (_hoops_SCHAS - _hoops_GSHAS);

							if (_hoops_AHHAS > _hoops_CIGGA) {
								_hoops_CIGGA = _hoops_AHHAS;	  /* _hoops_IHHSI _hoops_GH _hoops_HII _hoops_RH _hoops_HISAR _hoops_RSGR */
								if (_hoops_CIGGA >= _hoops_SIGGA) break; /* _hoops_AIIA _hoops_PIRC _hoops_RAAP */
							}
						}
					}
				} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);

				_hoops_HRCAR = _hoops_HRCAR->next;
				if (_hoops_CIGGA >= _hoops_SIGGA) continue; /* _hoops_HCR _hoops_PPRGA, _hoops_HPPR _hoops_HPIH _hoops_ARP (_hoops_RPP _hoops_GII) */
			}

			/* 8) _hoops_HSPH _hoops_HISGR _hoops_IS _hoops_RH _hoops_IASC _hoops_AHCRR _hoops_IS _hoops_GHGPR _hoops_ISPR */

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

			if (_hoops_CIGGA >= _hoops_SIGGA + 0.0001f) continue; /* _hoops_HCR _hoops_PPRGA */

			/* 9) _hoops_CGP _hoops_SCH _hoops_GGHP _hoops_SACH - _hoops_RHSHA _hoops_IPCAH */

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

				if (_hoops_CIPAS > sc->_hoops_GICAH) continue;
			}

			/* 10) _hoops_SSHAS _hoops_HCCHA. _hoops_GSIH _hoops_SCH. */

			_hoops_SHHAS = true;

			if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC) || _hoops_CHHAS < 0)
				off1 = (tc < 0.5f) ? (offset - 1) : offset;
			else
				off1 = (_hoops_CHHAS > 0) ? (offset - 1) : offset;

			off2 = (off1 == offset) ? (offset - 1) : offset;

			if (_hoops_HHAHR) {
				int		_hoops_GGIAS = off1;

				off1 = off2;
				off2 = _hoops_GGIAS;
			}

			if (!BIT (nr->transform_rendition->heuristics, _hoops_PAIRP)) {
				/* _hoops_RGHH _hoops_GPGR _hoops_GHSHA _hoops_CRGC */
				if (dc->_hoops_APHHP->_hoops_HPPAS._hoops_RPPAS > 0) {
					/* _hoops_GGCR _hoops_SCGR _hoops_III _hoops_CAGH _hoops_IS _hoops_RGIAS _hoops_RPP _hoops_HAR _hoops_IIH _hoops_AIAH */
					_hoops_AISAP *	_hoops_HHCAP = dc->_hoops_APHHP->_hoops_HPPAS._hoops_ACSAP;

					if (_hoops_HHCAP != null) do {
						if (_hoops_HHCAP->_hoops_PISAP[0] == off1 && _hoops_HHCAP->_hoops_PISAP[1] == off2 ||
							_hoops_HHCAP->_hoops_PISAP[0] == off2 && _hoops_HHCAP->_hoops_PISAP[1] == off1) {
							if (_hoops_CIPAS < _hoops_HHCAP->_hoops_HISAP) {
								_hoops_HHCAP->_hoops_HISAP = _hoops_CIPAS;
								_hoops_HHCAP->_hoops_IISAP = _hoops_HGRSH + _hoops_CSHGA * tc;
							}
							break;
						}
					} while ((_hoops_HHCAP = _hoops_HHCAP->next) != null);

					if (_hoops_HHCAP == null) {
						ALLOC (_hoops_HHCAP, _hoops_AISAP);
						_hoops_HHCAP->_hoops_PISAP[0] = off1;
						_hoops_HHCAP->_hoops_PISAP[1] = off2;
						_hoops_HHCAP->_hoops_PISAP[2] = -1;
						_hoops_HHCAP->_hoops_HISAP = _hoops_CIPAS;
						_hoops_HHCAP->_hoops_IISAP = _hoops_HGRSH + _hoops_CSHGA * tc;

						_hoops_HHCAP->next = null;
						*dc->_hoops_APHHP->_hoops_HPPAS._hoops_APPAS = _hoops_HHCAP;
						dc->_hoops_APHHP->_hoops_HPPAS._hoops_APPAS = &_hoops_HHCAP->next;
						if (/* !_hoops_SHCAH && */
							++dc->_hoops_APHHP->_hoops_HPPAS._hoops_PPPAS >=
								nr->_hoops_IRR->_hoops_CCIRP.polyline)
							dc->_hoops_APHHP->_hoops_HPPAS._hoops_RPPAS = 0;
					}
				}
			}

			if (_hoops_CIPAS < *_hoops_HISAP) {
				*_hoops_HISAP = _hoops_CIPAS;
				*_hoops_RCSAP = _hoops_HGRSH + _hoops_CSHGA * tc;

				*offset1 = off1;
				*offset2 = off2;
			}

			if (dc->_hoops_APHHP->_hoops_HPPAS._hoops_RPPAS < 0 && *offset1 != -1)
				return true;
		} while (_hoops_HRCAR != null);
	}

	if (!_hoops_SPGPA) {
		if (_hoops_SHHAS) {
			if (sc->_hoops_SRA->_hoops_IGHGH != null) {	/* _hoops_GRRRI _hoops_HCGR */
				_hoops_HACC const		*text;

				if ((text = dc->_hoops_IGHGH->_hoops_RHGGH) != null) {
					/* _hoops_PPR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_IRS _hoops_GSGR _hoops_HASRH */

					if (*_hoops_HISAP < dc->_hoops_IGHGH->_hoops_HHGGH) {
						dc->_hoops_IGHGH->_hoops_HHGGH	  = *_hoops_HISAP;
						dc->_hoops_IGHGH->_hoops_IHGGH	  = *_hoops_RCSAP;
						dc->_hoops_IGHGH->_hoops_CHGGH =	dc->_hoops_IGHGH->_hoops_PHGGH;
					}
				}
			}
			else if (sc->_hoops_HPPAS._hoops_RAI != null) {	/* _hoops_CICAR _hoops_GHSHA */
				sc->_hoops_HPPAS._hoops_HHGGH	 = *_hoops_HISAP;
				sc->_hoops_HPPAS._hoops_IHGGH	 = *_hoops_RCSAP;
				sc->_hoops_HPPAS._hoops_CHGGH = sc->_hoops_HPPAS._hoops_PHGGH;
			}
			else if (*offset1 != -1)									/* _hoops_GSSR _hoops_AGIR */
				return true;
			else
				return false;
		}
		return false;
	}

	if (offset == _hoops_ICGPA) {
		if (_hoops_HHAHR) {		/* (_hoops_IRGGS _hoops_RAAP _hoops_IAPR _hoops_HII _hoops_HAPR) */
			x1 = _hoops_AGRSH;
			_hoops_AGSIR = _hoops_PGRSH;
			_hoops_HGSIR = _hoops_HGRSH;
			_hoops_HHAHR = false;
		}

		/* _hoops_ARP _hoops_CGSI _hoops_GH _hoops_GAR _hoops_RPP _hoops_SR _hoops_RIAGR _hoops_RIAGR _hoops_SPR _hoops_RRI _hoops_PPSR */

		pl = _hoops_IAIRA;						/* _hoops_GGHC _hoops_RH _hoops_HAPR _hoops_IS... */
		end = pl + 1;					/* _hoops_HAPR _hoops_GGSR _hoops_SPS _hoops_GHIR */

		/* _hoops_PPR _hoops_HPGCA _hoops_ISSC _hoops_GGR */

		if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC)) {
			_hoops_AGRSH = x1;
			_hoops_PGRSH = _hoops_AGSIR;
			_hoops_HGRSH = _hoops_HGSIR;
			x1 = first.x;
			_hoops_AGSIR = first.y;
			_hoops_HGSIR = first.z;
			goto _hoops_RIHAS;
		}
		else if (_hoops_IHHAS) {
			/* _hoops_PHHR _hoops_ISSC _hoops_IS _hoops_CAS _hoops_SR _hoops_SRS _hoops_RIPPR _hoops_GGR _hoops_RIPS */
			_hoops_AGRSH = x1;
			_hoops_PGRSH = _hoops_AGSIR;
			_hoops_HGRSH = _hoops_HGSIR;
			_hoops_GHHAS = _hoops_PPHAS;
			x1 = first.x;
			_hoops_AGSIR = first.y;
			_hoops_HGSIR = first.z;
			_hoops_RHHAS = _hoops_IHCR->_hoops_CHCR;
			goto _hoops_AIHAS;
		}
	}
	else {		/* _hoops_HCR _hoops_CPHR _hoops_CCA _hoops_IRS _hoops_HSSP _hoops_ISHA */
		/* _hoops_HHGSI _hoops_AII _hoops_RPP _hoops_SR _hoops_RHHR _hoops_GPP _hoops_RH _hoops_CGHI _hoops_SPR */
		if (_hoops_SHHAS) {
			if (*offset1 == _hoops_ICGPA)
				*offset1 = 0;
			else if (*offset2 == _hoops_ICGPA)
				*offset2 = 0;
		}
	}

	if (!_hoops_CARGA || !_hoops_CSHIH) {
		if (*offset1 != -1)
			return _hoops_SHHAS;
		else
			return false;
	}

	/* _hoops_SR'_hoops_ASAR _hoops_ASSA _hoops_IRS _hoops_HSP - _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR'_hoops_ASAR *_hoops_GGR _hoops_RIPS*? */

	/* (_hoops_IPCP _hoops_AGIAS _hoops_HRGR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_PGIAS - _hoops_IHSH _hoops_IH _hoops_RH _hoops_HGIAS
	 *	_hoops_ISHP _hoops_CAPP.)
	 */
	if (_hoops_SHHAS || sc->_hoops_GICAH >= .999*MAX_FLOAT) {
		if (!ANYBIT (sc->options, _hoops_RHCAH|_hoops_RSCAH))  {
			/* _hoops_SSS _hoops_RH _hoops_IHPR _hoops_RHC-_hoops_HGGS/_hoops_HSSP _hoops_SGSSR _hoops_AHCR */
			HD_Find_Geometry_Screen_Plane (nr, geometry, &plane);

			if (plane.c == 0.0f) {
				/* _hoops_SR _hoops_CHR _hoops_CPPPR _hoops_PCCGS - _hoops_GPP _hoops_ISHA, _hoops_HIS _hoops_PAH'_hoops_RA _hoops_SHH _hoops_ASSA! */
				/* _hoops_IGGRA _hoops_GAR _hoops_RPP _hoops_HAR _hoops_ASSA */
				if (!_hoops_SHHAS) return false;
				*_hoops_RCSAP = 0.0f; /* ?? */
			}
			else {
				*_hoops_RCSAP = -(plane.a * sc->_hoops_AICAH.x +
						plane.b * sc->_hoops_AICAH.y + plane.d) / plane.c;
			}
			*_hoops_HISAP = 0.0f;		/* _hoops_ASSA _hoops_HRGR _hoops_IRS _hoops_PPPSR _hoops_RHHR */
		}
		if (!_hoops_SHHAS) {
			/* _hoops_SR _hoops_AHGS _hoops_IS _hoops_SHH _hoops_ASSA _hoops_HIH _hoops_SR _hoops_IRPSR'_hoops_RA _hoops_SSS _hoops_PCCP _hoops_ISHA _hoops_PRGI
			 * _hoops_PHRI _hoops_RH _hoops_PRCH _hoops_AAPR _hoops_ARP _hoops_IS _hoops_RH _hoops_SHSC _hoops_RPPS.
			 * _hoops_PHAA, _hoops_CACH _hoops_RPP _hoops_GAAP _hoops_RGR _hoops_HRGR _hoops_PAHH _hoops_PGGA _hoops_RH _hoops_HSSP
			 * _hoops_HRGR _hoops_AACC _hoops_SGGR (_hoops_RPP _hoops_ISCP _hoops_GGSRA _hoops_PPSR _hoops_HRGR _hoops_AACC, _hoops_ASRC _hoops_RCPP).
			 * _hoops_HHPC, _hoops_ASRC _hoops_CPHP _hoops_PAR _hoops_RII.
			 */


			if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
				_hoops_GPPA const		*_hoops_IRCAR;

				_hoops_IRCAR = _hoops_IHCR->_hoops_RGH->_hoops_PHCA->_hoops_APPA;
				do {
					float							test;

					test = _hoops_IRCAR->_hoops_SPPA.a * sc->_hoops_AICAH.x +
						   _hoops_IRCAR->_hoops_SPPA.b * sc->_hoops_AICAH.y +
						   _hoops_IRCAR->_hoops_SPPA.c * *_hoops_RCSAP +
						   _hoops_IRCAR->_hoops_SPPA.d;

					if (test >= 0.0f)	/* _hoops_AACC _hoops_SGGR */
						return false;
				} _hoops_RGGA ((_hoops_IRCAR = _hoops_IRCAR->next) == null);
			}

			*offset1 = 0;
			*offset2 = 1;
		}
		if (*offset1 != -1)
			return true;
		else
			return false;
	}
	else {
		float					_hoops_IGIAS;
		_hoops_PACIR		_hoops_CGIAS;
		bool					_hoops_IA;

		/* _hoops_PS'_hoops_ASAR _hoops_ASSA, _hoops_HIH _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RH _hoops_HISGR _hoops_ISHA */
		/* _hoops_ISCGR _hoops_IRS _hoops_SGRIR _hoops_AHCRR, _hoops_PPR _hoops_HPPR _hoops_GICS */

		_hoops_IGIAS = sc->_hoops_GICAH;
		_hoops_CGIAS = sc->bounding;

		sc->_hoops_GICAH = MAX_FLOAT;
		if (BIT (sc->options, _hoops_IICAH)) {
			sc->bounding.left = -MAX_FLOAT;
			sc->bounding.right = MAX_FLOAT;
			sc->bounding.bottom = -MAX_FLOAT;
			sc->bounding.top = MAX_FLOAT;

			_hoops_IA = HD_Select_Point_List (nr, geometry, _hoops_ICGPA, _hoops_IAIRA,
											_hoops_SPGPA, _hoops_CSHIH,
											offset1, offset2, _hoops_HISAP, _hoops_RCSAP);

			/* _hoops_PHIH, _hoops_HRGHR */
			/* (_hoops_IPCP .999'_hoops_GRI _hoops_PPR _hoops_RH ><'_hoops_GRI _hoops_PHGA "_hoops_HRPAI _hoops_SGIAS") */

			if (sc->bounding.left <= .999 * -MAX_FLOAT)
				sc->bounding.left = _hoops_CGIAS.left;
			if (sc->bounding.right >= .999 * MAX_FLOAT)
				sc->bounding.right = _hoops_CGIAS.right;
			if (sc->bounding.bottom <= .999 * -MAX_FLOAT)
				sc->bounding.bottom = _hoops_CGIAS.bottom;
			if (sc->bounding.top >= .999 * MAX_FLOAT)
				sc->bounding.top = _hoops_CGIAS.top;
		}
		else {
			_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;

			sc->bounding.left = (float)_hoops_SGRA->_hoops_PHRA.left;
			sc->bounding.right = (float)_hoops_SGRA->_hoops_PHRA.right;
			sc->bounding.bottom = (float)_hoops_SGRA->_hoops_PHRA.bottom;
			sc->bounding.top = (float)_hoops_SGRA->_hoops_PHRA.top;

			_hoops_IA = HD_Select_Point_List (nr, geometry, _hoops_ICGPA, _hoops_IAIRA,
											_hoops_SPGPA, _hoops_CSHIH,
											offset1, offset2, _hoops_HISAP, _hoops_RCSAP);

			/* _hoops_PHIH, _hoops_HRGHR */
			if (sc->bounding.left == _hoops_SGRA->_hoops_PHRA.left)
				sc->bounding.left = _hoops_CGIAS.left;
			if (sc->bounding.right == _hoops_SGRA->_hoops_PHRA.right)
				sc->bounding.right = _hoops_CGIAS.right;
			if (sc->bounding.bottom == _hoops_SGRA->_hoops_PHRA.bottom)
				sc->bounding.bottom = _hoops_CGIAS.bottom;
			if (sc->bounding.top == _hoops_SGRA->_hoops_PHRA.top)
				sc->bounding.top = _hoops_CGIAS.top;
		}
		if (sc->_hoops_GICAH == MAX_FLOAT)
			sc->_hoops_GICAH = _hoops_IGIAS;

		if (*offset1 != -1)
			return _hoops_IA;
		else
			return false;
	}
}

local bool _hoops_GRIAS (
	Net_Rendition const &		nr,
	int							_hoops_ICGPA,
	DC_Point const *			_hoops_IAIRA,
	bool						_hoops_SPGPA,
	bool						_hoops_CSHIH,
	int alter *					offset1,
	int alter *					offset2,
	float alter *				_hoops_HISAP,
	float alter *				_hoops_RCSAP) {
	DC_Point const *			pl = _hoops_IAIRA;
	DC_Point const *			end;
	int							count = _hoops_ICGPA;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	DC_Point const *			_hoops_SAHAS;
	float						_hoops_AGRSH, _hoops_PGRSH, _hoops_HGRSH,
								x1 = 0.0f, _hoops_AGSIR = 0.0f, _hoops_HGSIR = 0.0f,
								_hoops_HSHGA, _hoops_ISHGA, _hoops_CSHGA,
								xc, yc,
								_hoops_GPHAS, _hoops_RPHAS,
								tc,
								_hoops_AHHAS = 0.0f,
								_hoops_SIGGA,
								_hoops_CIGGA,
								_hoops_PHHAS,
								_hoops_CIPAS;
	Point						first;
	bool						_hoops_CARGA = false;
	int							offset = 0, off1, off2;
	bool						_hoops_SHHAS = false;
	bool						_hoops_HHAHR = false;
	float						_hoops_HPCII;
	_hoops_IAPA const *	_hoops_GIHAS = null;

	*offset1 = -1;
	*offset2 = -1;
	if (BIT (_hoops_IHCR->flags, _hoops_CSP))
		_hoops_GIHAS = _hoops_IHCR->_hoops_RGH->_hoops_PHCA;

	end = pl + count;
	*_hoops_HISAP = sc->_hoops_GICAH;

	first.x = x1 = pl[0].x;
	first.y = _hoops_AGSIR = pl[0].y;
	first.z = _hoops_HGSIR = pl[0].z;

	_hoops_AGRSH = 0.0f;
	_hoops_PGRSH = 0.0f;
	_hoops_HGRSH = 0.0f;

	_hoops_RGGA ((++offset, _hoops_SAHAS = pl, ++pl) == end) {
		_hoops_IAPA const *	_hoops_HRCAR;

		if (_hoops_HHAHR) {		/* (_hoops_IRGGS _hoops_RAAP _hoops_IAPR _hoops_HII _hoops_PGHC _hoops_HAPR) */
			x1 = _hoops_AGRSH;
			_hoops_AGSIR = _hoops_PGRSH;
			_hoops_HGSIR = _hoops_HGRSH;
			_hoops_HHAHR = false;
		}

		/* 1)  _hoops_SIPR _hoops_SHPR _hoops_PCRR */

		_hoops_AGRSH = x1;
		_hoops_PGRSH = _hoops_AGSIR;
		_hoops_HGRSH = _hoops_HGSIR;
		x1 = pl[0].x;
		_hoops_AGSIR = pl[0].y;
		_hoops_HGSIR = pl[0].z;

		_hoops_RIHAS:;

		/* 2) _hoops_RAH _hoops_IRS _hoops_HHCI _hoops_IASC _hoops_AHCRR _hoops_RPGP _hoops_GPP _hoops_SPCR */

		if (x1 < sc->bounding.left) {
			if (_hoops_AGRSH < sc->bounding.left)
				continue;
		}
		else if (x1 > sc->bounding.right) {
			if (_hoops_AGRSH > sc->bounding.right)
				continue;
		}

		/* 4) _hoops_RAH _hoops_IRS _hoops_HHCI _hoops_IASC _hoops_AHCRR _hoops_RPGP _hoops_GPP _hoops_GHCR */

		if (_hoops_AGSIR < sc->bounding.bottom) {
			if (_hoops_PGRSH < sc->bounding.bottom)
				continue;
		}
		else if (_hoops_AGSIR > sc->bounding.top) {
			if (_hoops_PGRSH > sc->bounding.top) {
				/* _hoops_PRIA _hoops_ASSA/_hoops_SIPP _hoops_RPGP _hoops_IH _hoops_HSSP _hoops_PIHAS */
				if (_hoops_AGRSH <= sc->_hoops_AICAH.x) {
					if (sc->_hoops_AICAH.x < x1) _hoops_CARGA = !_hoops_CARGA;
				}
				else if (x1 <= sc->_hoops_AICAH.x) {
					if (sc->_hoops_AICAH.x < _hoops_AGRSH) _hoops_CARGA = !_hoops_CARGA;
				}
				continue;
			}
		}

		/* 5) _hoops_ACGR _hoops_RH _hoops_HISGR _hoops_PPSR _hoops_IS _hoops_RH _hoops_HASRH _hoops_GPP _hoops_RH _hoops_PRISA _hoops_III ==

			_hoops_AHGHR _hoops_RH _hoops_PRISA _hoops_III _hoops_CGSSR:

				_hoops_SISR = _hoops_HIHAS + _hoops_IIHAS * _hoops_RA			(_hoops_IIHAS = _hoops_RCRIA - _hoops_HIHAS)
				_hoops_HAPC = _hoops_CIHAS + _hoops_SIHAS * _hoops_RA			(_hoops_SIHAS = _hoops_GSRIA - _hoops_CIHAS)


			_hoops_AHGHR _hoops_RH _hoops_IHGP _hoops_GIRA _hoops_HII _hoops_IRS _hoops_III _hoops_IS _hoops_IRS _hoops_PPSR (_hoops_GCHAS, _hoops_RCHAS):

				 2			 2			 2
				_hoops_PCCIR  = (_hoops_SISR - _hoops_GCHAS)  + (_hoops_HAPC - _hoops_RCHAS)

																	   2
			_hoops_SPAA _hoops_RH _hoops_RA-_hoops_PIRA _hoops_HPGR _hoops_RH _hoops_HISGR _hoops_CCHRA - _hoops_RH _hoops_AASC _hoops_IIGR _hoops_PCCIR	 - _hoops_HRGR,
			_hoops_RRPS _hoops_IS _hoops_GAIPA:

					  _hoops_IIHAS * (_hoops_GCHAS - _hoops_HIHAS) + _hoops_SIHAS * (_hoops_RCHAS - _hoops_CIHAS)
				_hoops_ACHAS =  -------------------------------
								   2	 2
								 _hoops_IIHAS	 + _hoops_SIHAS

		*/

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
				_hoops_HPCII = _hoops_HGRSH; _hoops_HGRSH = _hoops_HGSIR; _hoops_HGSIR = _hoops_HPCII;
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

		/* _hoops_PRIA _hoops_ASSA/_hoops_SIPP _hoops_RPGP _hoops_IH _hoops_HSSP _hoops_PIHAS */
		/* (_hoops_AISRA, _hoops_RPR _hoops_RSH _hoops_AHPH _hoops_SPPR _hoops_RIH _hoops_ACCGI) */
		if (yc >= sc->_hoops_AICAH.y) {
			if (_hoops_AGRSH <= sc->_hoops_AICAH.x) {
				if (sc->_hoops_AICAH.x < x1) _hoops_CARGA = !_hoops_CARGA;
			}
			else if (x1 <= sc->_hoops_AICAH.x) {
				if (sc->_hoops_AICAH.x < _hoops_AGRSH) _hoops_CARGA = !_hoops_CARGA;
			}
		}

		/* 6) _hoops_CCHAS _hoops_RPGP _hoops_GPP _hoops_RH _hoops_HISGR _hoops_PPSR */

		_hoops_GPHAS = (xc - sc->_hoops_AICAH.x) / sc->_hoops_HICAH.x;
		_hoops_RPHAS = (yc - sc->_hoops_AICAH.y) / sc->_hoops_HICAH.y;
		_hoops_CIPAS = _hoops_GPHAS*_hoops_GPHAS + _hoops_RPHAS*_hoops_RPHAS;

		if (_hoops_CIPAS >= sc->_hoops_GICAH) continue;

		/* _hoops_APSH _hoops_RRRIR _hoops_RIRA - _hoops_HA _hoops_AA _hoops_IHIR-_hoops_CSRA _hoops_PCGC */

		_hoops_CSHGA = _hoops_HGSIR - _hoops_HGRSH;

		/* 7) _hoops_IHHSI _hoops_RH _hoops_III _hoops_ACSRR _hoops_RH _hoops_HPPA _hoops_GHC, _hoops_RPP _hoops_GII */

		_hoops_HRCAR = _hoops_GIHAS;
		do {
			_hoops_CIGGA = 0.0f;
			_hoops_SIGGA = 1.0f;

			if (_hoops_HRCAR != null) {
				_hoops_GPPA const		*_hoops_IRCAR;

				_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA;
				do {
					float							_hoops_SCHAS, _hoops_GSHAS;

					_hoops_SCHAS = _hoops_IRCAR->_hoops_SPPA.a * _hoops_AGRSH + _hoops_IRCAR->_hoops_SPPA.b * _hoops_PGRSH +
							_hoops_IRCAR->_hoops_SPPA.c * _hoops_HGRSH + _hoops_IRCAR->_hoops_SPPA.d;
					_hoops_GSHAS = _hoops_IRCAR->_hoops_SPPA.a * x1 + _hoops_IRCAR->_hoops_SPPA.b * _hoops_AGSIR +
							_hoops_IRCAR->_hoops_SPPA.c * _hoops_HGSIR + _hoops_IRCAR->_hoops_SPPA.d;

					if (_hoops_SCHAS <= 0.0f) { /* _hoops_RSHAS _hoops_HRGR _hoops_PGPAA */
						if (_hoops_GSHAS <= 0.0f) {
							/* _hoops_PPAAI _hoops_HRGR _hoops_GACC _hoops_PGPAA. _hoops_GRSH _hoops_AGAPR. */
						}
						else {
							/* _hoops_PPAAI _hoops_HRGR _hoops_HAR _hoops_PGPAA. _hoops_PPRII _hoops_CCPH _hoops_ASHAS. */

							/* _hoops_IPCP _hoops_SGSSR _hoops_PPSR _hoops_IIGR _hoops_RH _hoops_ISHA _hoops_PPR _hoops_PSHAS _hoops_IPPA. */
							/* (_hoops_HSHAS _hoops_PPR _hoops_ISHAS _hoops_PAHHP _hoops_GGR _hoops_HRASR, _hoops_HIS _hoops_PAH'_hoops_RA _hoops_GHCH _hoops_HPP 0) */
							_hoops_AHHAS = _hoops_SCHAS / (_hoops_SCHAS - _hoops_GSHAS);

							if (_hoops_AHHAS < _hoops_SIGGA) {
								_hoops_SIGGA = _hoops_AHHAS;
								if (_hoops_CIGGA >= _hoops_SIGGA) break; /* _hoops_AIIA _hoops_PIRC _hoops_RAAP */
							}
						}
					}
					else {
						/* _hoops_RSHAS _hoops_HRGR _hoops_HAR _hoops_PGPAA */
						if (_hoops_GSHAS > 0.0f) {
							/* _hoops_PPAAI _hoops_HRGR _hoops_GACC _hoops_HAR _hoops_PGPAA. _hoops_GRSH _hoops_AGAPR. */
							_hoops_SIGGA = -999.0f; /* (_hoops_HHSA '_hoops_SAS' _hoops_CAPP) */
							break;
						}
						else {
							/* _hoops_PPAAI *_hoops_HRGR* _hoops_PGPAA. _hoops_PPRII _hoops_CCPH _hoops_CSHAS. */

							/* _hoops_IPCP _hoops_SGSSR _hoops_PPSR _hoops_IIGR _hoops_RH _hoops_ISHA _hoops_PPR _hoops_PSHAS _hoops_IPPA. */
							/* (_hoops_HSHAS _hoops_PPR _hoops_ISHAS _hoops_PAHHP _hoops_GGR _hoops_HRASR, _hoops_HIS _hoops_PSHAS _hoops_PAH'_hoops_RA _hoops_GHCH _hoops_HPP 0)*/
							_hoops_AHHAS = _hoops_SCHAS / (_hoops_SCHAS - _hoops_GSHAS);

							if (_hoops_AHHAS > _hoops_CIGGA) {
								_hoops_CIGGA = _hoops_AHHAS;	  /* _hoops_IHHSI _hoops_GH _hoops_HII _hoops_RH _hoops_HISAR _hoops_RSGR */
								if (_hoops_CIGGA >= _hoops_SIGGA) break; /* _hoops_AIIA _hoops_PIRC _hoops_RAAP */
							}
						}
					}
				} while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);

				_hoops_HRCAR = _hoops_HRCAR->next;
				if (_hoops_CIGGA >= _hoops_SIGGA) continue; /* _hoops_HCR _hoops_PPRGA, _hoops_HPPR _hoops_HPIH _hoops_ARP (_hoops_RPP _hoops_GII) */
			}

			/* 8) _hoops_HSPH _hoops_HISGR _hoops_IS _hoops_RH _hoops_IASC _hoops_AHCRR _hoops_IS _hoops_GHGPR _hoops_ISPR */

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

			/* 9) _hoops_CGP _hoops_SCH _hoops_GGHP _hoops_SACH - _hoops_RHSHA _hoops_IPCAH */

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

				if (_hoops_CIPAS >= sc->_hoops_GICAH) continue;
			}

			/* 10) _hoops_SSHAS _hoops_HCCHA. _hoops_GSIH _hoops_SCH. */

			_hoops_SHHAS = true;

			off1 = (tc < 0.5f) ? (offset - 1) : offset;
			off2 = (off1 == offset) ? (offset - 1) : offset;

			if (_hoops_HHAHR) {
				int		_hoops_GGIAS = off1;

				off1 = off2;
				off2 = _hoops_GGIAS;
			}

			/* _hoops_RPP _hoops_SR _hoops_SSGRR _hoops_IH _hoops_AHSIR _hoops_HIH _hoops_SARS'_hoops_RA _hoops_RHHR _hoops_RRIAS, _hoops_RGHH _hoops_GII _hoops_RGIAS _hoops_HA */
			if (sc->_hoops_HPPAS._hoops_PHGGH == -1) {
				/* _hoops_RGHH _hoops_GPGR _hoops_GHSHA _hoops_CRGC */
				if (dc->_hoops_APHHP->_hoops_HPPAS._hoops_RPPAS > 0) {
					/* _hoops_GGCR _hoops_SCGR _hoops_III _hoops_CAGH _hoops_IS _hoops_RGIAS _hoops_RPP _hoops_HAR _hoops_IIH _hoops_AIAH */
					_hoops_AISAP *	_hoops_HHCAP;

					if ((_hoops_HHCAP = dc->_hoops_APHHP->_hoops_HPPAS._hoops_ACSAP) != null) do {
						if (_hoops_HHCAP->_hoops_PISAP[0] == off1 && _hoops_HHCAP->_hoops_PISAP[1] == off2 ||
							_hoops_HHCAP->_hoops_PISAP[0] == off2 && _hoops_HHCAP->_hoops_PISAP[1] == off1) {
							if (_hoops_CIPAS < _hoops_HHCAP->_hoops_HISAP) {
								_hoops_HHCAP->_hoops_HISAP = _hoops_CIPAS;
								_hoops_HHCAP->_hoops_IISAP = _hoops_HGRSH + _hoops_CSHGA * tc;
							}
							break;
						}
					} while ((_hoops_HHCAP = _hoops_HHCAP->next) != null);

					if (_hoops_HHCAP == null) {
						ALLOC (_hoops_HHCAP, _hoops_AISAP);
						_hoops_HHCAP->next = null;
						_hoops_HHCAP->_hoops_PISAP[0] = off1;
						_hoops_HHCAP->_hoops_PISAP[1] = off2;
						_hoops_HHCAP->_hoops_PISAP[2] = -1;
						_hoops_HHCAP->_hoops_HISAP = _hoops_CIPAS;
						_hoops_HHCAP->_hoops_IISAP = _hoops_HGRSH + _hoops_CSHGA * tc;
						_hoops_HHCAP->next = null;
						*dc->_hoops_APHHP->_hoops_HPPAS._hoops_APPAS = _hoops_HHCAP;
						dc->_hoops_APHHP->_hoops_HPPAS._hoops_APPAS = &_hoops_HHCAP->next;
						if (/* !_hoops_SHCAH && */
							++dc->_hoops_APHHP->_hoops_HPPAS._hoops_PPPAS >=
								nr->_hoops_IRR->_hoops_CCIRP.polyline)
							dc->_hoops_APHHP->_hoops_HPPAS._hoops_RPPAS = 0;
					}
				}

				sc->_hoops_HPPAS._hoops_CIHIA = true;
				sc->_hoops_HPPAS._hoops_CHGGH = _hoops_AHIA (off1, off2);
				sc->_hoops_HPPAS._hoops_IHGGH = _hoops_HGRSH + _hoops_CSHGA * tc;
				sc->_hoops_HPPAS._hoops_HHGGH = _hoops_CIPAS;
			}

			if (_hoops_CIPAS < *_hoops_HISAP) {
				*_hoops_HISAP = _hoops_CIPAS;
				*_hoops_RCSAP = _hoops_HGRSH + _hoops_CSHGA * tc;

				*offset1 = off1;
				*offset2 = off2;
			}

			if (dc->_hoops_APHHP->_hoops_HPPAS._hoops_RPPAS < 0 && *offset1 != -1)
				return true;
		} while (_hoops_HRCAR != null);
	}

	if (!_hoops_SPGPA) {
		if (_hoops_SHHAS) {
			if (sc->_hoops_SRA->_hoops_IGHGH != null) {	/* _hoops_GRRRI _hoops_HCGR */
				_hoops_HACC const		*text;

				if ((text = dc->_hoops_IGHGH->_hoops_RHGGH) != null) {
					/* _hoops_PPR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_IRS _hoops_GSGR _hoops_HASRH */

					if (*_hoops_HISAP < dc->_hoops_IGHGH->_hoops_HHGGH) {
						dc->_hoops_IGHGH->_hoops_HHGGH	  = *_hoops_HISAP;
						dc->_hoops_IGHGH->_hoops_IHGGH	  = *_hoops_RCSAP;
						dc->_hoops_IGHGH->_hoops_CHGGH =	dc->_hoops_IGHGH->_hoops_PHGGH;
					}
				}
			}
			else if (sc->_hoops_HPPAS._hoops_RAI != null) {	/* _hoops_CICAR _hoops_GHSHA */
				if (sc->_hoops_HPPAS._hoops_PHGGH != -1) {			/* _hoops_PPR _hoops_SR _hoops_IIAC _hoops_RCAHR _hoops_GGR _hoops_RRIAS */
					sc->_hoops_HPPAS._hoops_HHGGH = *_hoops_HISAP;
					sc->_hoops_HPPAS._hoops_IHGGH	 = *_hoops_RCSAP;
					sc->_hoops_HPPAS._hoops_CHGGH = sc->_hoops_HPPAS._hoops_PHGGH;
				}
			}
			else if (*offset1 != -1)													/* _hoops_GSSR _hoops_AGIR */
				return true;
			else
				return false;
		}
		return false;
	}

	if (offset == _hoops_ICGPA) {
		if (_hoops_HHAHR) {		/* (_hoops_IRGGS _hoops_RAAP _hoops_IAPR _hoops_HII _hoops_HAPR) */
			x1 = _hoops_AGRSH;
			_hoops_AGSIR = _hoops_PGRSH;
			_hoops_HGSIR = _hoops_HGRSH;
			_hoops_HHAHR = false;
		}

		/* _hoops_ARP _hoops_CGSI _hoops_GH _hoops_GAR _hoops_RPP _hoops_SR _hoops_RIAGR _hoops_RIAGR _hoops_SPR _hoops_RRI _hoops_PPSR */

		pl = _hoops_IAIRA;						/* _hoops_GGHC _hoops_RH _hoops_HAPR _hoops_IS... */
		end = pl + 1;					/* _hoops_HAPR _hoops_GGSR _hoops_SPS _hoops_GHIR */

		/* _hoops_PPR _hoops_HPGCA _hoops_ISSC _hoops_GGR */

		_hoops_AGRSH = x1;
		_hoops_PGRSH = _hoops_AGSIR;
		_hoops_HGRSH = _hoops_HGSIR;
		x1 = first.x;
		_hoops_AGSIR = first.y;
		_hoops_HGSIR = first.z;
		goto _hoops_RIHAS;
	}
	else {		/* _hoops_HCR _hoops_CPHR _hoops_CCA _hoops_IRS _hoops_HSSP _hoops_ISHA */
		/* _hoops_HHGSI _hoops_AII _hoops_RPP _hoops_SR _hoops_RHHR _hoops_GPP _hoops_RH _hoops_CGHI _hoops_SPR */
		if (_hoops_SHHAS) {
			if (*offset1 == _hoops_ICGPA)
				*offset1 = 0;
			else if (*offset2 == _hoops_ICGPA)
				*offset2 = 0;
		}
	}

	if (!_hoops_CARGA || !_hoops_CSHIH) {
		if (*offset1 != -1)
			return _hoops_SHHAS;
		else
			return false;
	}

	/* _hoops_SR'_hoops_ASAR _hoops_ASSA _hoops_IRS _hoops_HSP - _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR'_hoops_ASAR *_hoops_GGR _hoops_RIPS*? */

	/* (_hoops_IPCP _hoops_AGIAS _hoops_HRGR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_PGIAS - _hoops_IHSH _hoops_IH _hoops_RH _hoops_HGIAS
	 *	_hoops_ISHP _hoops_CAPP.)
	 */
	if (_hoops_SHHAS || sc->_hoops_GICAH >= .999*MAX_FLOAT) {
		if (!ANYBIT (sc->options, _hoops_RHCAH|_hoops_RSCAH))  {
			_hoops_ARPA		plane;
			Vector		_hoops_HSPI, _hoops_ISPI;

			_hoops_HSPI.x = _hoops_IAIRA[1].x - _hoops_IAIRA[0].x;
			_hoops_HSPI.y = _hoops_IAIRA[1].y - _hoops_IAIRA[0].y;
			_hoops_HSPI.z = _hoops_IAIRA[1].z - _hoops_IAIRA[0].z;
			_hoops_ISPI.x = _hoops_IAIRA[2].x - _hoops_IAIRA[0].x;
			_hoops_ISPI.y = _hoops_IAIRA[2].y - _hoops_IAIRA[0].y;
			_hoops_ISPI.z = _hoops_IAIRA[2].z - _hoops_IAIRA[0].z;
			HI_Cross_Product (&_hoops_HSPI, &_hoops_ISPI, (Vector *)&plane);
			plane.d = -(plane.a * _hoops_IAIRA[0].x + plane.b * _hoops_IAIRA[0].y + plane.c * _hoops_IAIRA[0].z);

			sc->_hoops_HPPAS._hoops_HHGGH = 0.0f;
			if (plane.c == 0.0f)	/* ? */
				sc->_hoops_HPPAS._hoops_IHGGH = 0.0f;
			else
				sc->_hoops_HPPAS._hoops_IHGGH = -(plane.a * sc->_hoops_AICAH.x +
									   plane.b * sc->_hoops_AICAH.y + plane.d) / plane.c;
			sc->_hoops_HPPAS._hoops_CHGGH = sc->_hoops_HPPAS._hoops_PHGGH;
#if 0
			/* _hoops_SSS _hoops_RH _hoops_IHPR _hoops_RHC-_hoops_HGGS/_hoops_HSSP _hoops_SGSSR _hoops_AHCR */
			HD_Find_Geometry_Screen_Plane (nr, geometry, &plane);

			if (plane.c == 0.0f) {
				/* _hoops_SR _hoops_CHR _hoops_CPPPR _hoops_PCCGS - _hoops_GPP _hoops_ISHA, _hoops_HIS _hoops_PAH'_hoops_RA _hoops_SHH _hoops_ASSA! */
				/* _hoops_IGGRA _hoops_GAR _hoops_RPP _hoops_HAR _hoops_ASSA */
				if (!_hoops_SHHAS) return false;
				*_hoops_RCSAP = 0.0f; /* ?? */
			}
			else {
				*_hoops_RCSAP = -(plane.a * sc->_hoops_AICAH.x +
						plane.b * sc->_hoops_AICAH.y + plane.d) / plane.c;
			}
			*_hoops_HISAP = 0.0f;		/* _hoops_ASSA _hoops_HRGR _hoops_IRS _hoops_PPPSR _hoops_RHHR */
#endif
		}
		if (!_hoops_SHHAS) {
			/* _hoops_SR _hoops_AHGS _hoops_IS _hoops_SHH _hoops_ASSA _hoops_HIH _hoops_SR _hoops_IRPSR'_hoops_RA _hoops_SSS _hoops_PCCP _hoops_ISHA _hoops_PRGI
			 * _hoops_PHRI _hoops_RH _hoops_PRCH _hoops_AAPR _hoops_ARP _hoops_IS _hoops_RH _hoops_SHSC _hoops_RPPS.
			 * _hoops_PHAA, _hoops_CACH _hoops_RPP _hoops_GAAP _hoops_RGR _hoops_HRGR _hoops_PAHH _hoops_PGGA _hoops_RH _hoops_HSSP
			 * _hoops_HRGR _hoops_AACC _hoops_SGGR (_hoops_RPP _hoops_ISCP _hoops_GGSRA _hoops_PPSR _hoops_HRGR _hoops_AACC, _hoops_ASRC _hoops_RCPP).
			 * _hoops_HHPC, _hoops_ASRC _hoops_CPHP _hoops_PAR _hoops_RII.
			 */


			if (BIT (_hoops_IHCR->flags, _hoops_CSP)) {
				_hoops_GPPA const		*_hoops_IRCAR;

				_hoops_IRCAR = _hoops_IHCR->_hoops_RGH->_hoops_PHCA->_hoops_APPA;
				do {
					float							test;

					test = _hoops_IRCAR->_hoops_SPPA.a * sc->_hoops_AICAH.x +
						   _hoops_IRCAR->_hoops_SPPA.b * sc->_hoops_AICAH.y +
						   _hoops_IRCAR->_hoops_SPPA.c * *_hoops_RCSAP +
						   _hoops_IRCAR->_hoops_SPPA.d;

					if (test >= 0.0f)	/* _hoops_AACC _hoops_SGGR */
						return false;
				} _hoops_RGGA ((_hoops_IRCAR = _hoops_IRCAR->next) == null);
			}

			*offset1 = 0;
			*offset2 = 1;
		}

		if (*offset1 != -1)
			return true;
		else
			return false;
	}
	else {
		float				_hoops_IGIAS;
		_hoops_PACIR	_hoops_CGIAS;
		bool				_hoops_IA;

		/* _hoops_PS'_hoops_ASAR _hoops_ASSA, _hoops_HIH _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RH _hoops_HISGR _hoops_ISHA */
		/* _hoops_ISCGR _hoops_IRS _hoops_SGRIR _hoops_AHCRR, _hoops_PPR _hoops_HPPR _hoops_GICS */

		_hoops_IGIAS = sc->_hoops_GICAH;
		_hoops_CGIAS = sc->bounding;

		sc->_hoops_GICAH = MAX_FLOAT;
		if (BIT (sc->options, _hoops_IICAH)) {
			sc->bounding.left = -MAX_FLOAT;
			sc->bounding.right = MAX_FLOAT;
			sc->bounding.bottom = -MAX_FLOAT;
			sc->bounding.top = MAX_FLOAT;

			_hoops_IA = _hoops_GRIAS (nr, _hoops_ICGPA, _hoops_IAIRA,
											_hoops_SPGPA, _hoops_CSHIH,
											offset1, offset2, _hoops_HISAP, _hoops_RCSAP);

			/* _hoops_PHIH, _hoops_HRGHR */
			/* (_hoops_IPCP .999'_hoops_GRI _hoops_PPR _hoops_RH ><'_hoops_GRI _hoops_PHGA "_hoops_HRPAI _hoops_SGIAS") */

			if (sc->bounding.left <= .999 * -MAX_FLOAT)
				sc->bounding.left = _hoops_CGIAS.left;
			if (sc->bounding.right >= .999 * MAX_FLOAT)
				sc->bounding.right = _hoops_CGIAS.right;
			if (sc->bounding.bottom <= .999 * -MAX_FLOAT)
				sc->bounding.bottom = _hoops_CGIAS.bottom;
			if (sc->bounding.top >= .999 * MAX_FLOAT)
				sc->bounding.top = _hoops_CGIAS.top;
		}
		else {
			_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;

			sc->bounding.left = (float)_hoops_SGRA->_hoops_PHRA.left;
			sc->bounding.right = (float)_hoops_SGRA->_hoops_PHRA.right;
			sc->bounding.bottom = (float)_hoops_SGRA->_hoops_PHRA.bottom;
			sc->bounding.top = (float)_hoops_SGRA->_hoops_PHRA.top;

			_hoops_IA = _hoops_GRIAS (nr, _hoops_ICGPA, _hoops_IAIRA,
											_hoops_SPGPA, _hoops_CSHIH,
											offset1, offset2, _hoops_HISAP, _hoops_RCSAP);

			/* _hoops_PHIH, _hoops_HRGHR */
			if (sc->bounding.left == _hoops_SGRA->_hoops_PHRA.left)
				sc->bounding.left = _hoops_CGIAS.left;
			if (sc->bounding.right == _hoops_SGRA->_hoops_PHRA.right)
				sc->bounding.right = _hoops_CGIAS.right;
			if (sc->bounding.bottom == _hoops_SGRA->_hoops_PHRA.bottom)
				sc->bounding.bottom = _hoops_CGIAS.bottom;
			if (sc->bounding.top == _hoops_SGRA->_hoops_PHRA.top)
				sc->bounding.top = _hoops_CGIAS.top;
		}
		if (sc->_hoops_GICAH == MAX_FLOAT)
			sc->_hoops_GICAH = _hoops_IGIAS;

		if (_hoops_IA) {
			if (sc->_hoops_HPPAS._hoops_RAI != null) {	/* _hoops_CICAR _hoops_GHSHA */
				sc->_hoops_HPPAS._hoops_HHGGH = *_hoops_HISAP;
				sc->_hoops_HPPAS._hoops_IHGGH	 = *_hoops_RCSAP;
				sc->_hoops_HPPAS._hoops_CHGGH = sc->_hoops_HPPAS._hoops_PHGGH;
			}
		}

		if (*offset1 != -1)
			return _hoops_IA;
		else
			return false;
	}
}
#endif


GLOBAL_FUNCTION void HD_Select_DC_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;

	if (count == 0)
		return;

	if (nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, null, null, null, null, 0, 0, _hoops_RHGGA|_hoops_GPHC);
		return;
	}

	if (!BIT (nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1) {
		HD_Std_DC_Polyline (nr, count, points);
		return;
	}

	if (BIT (sc->options, _hoops_CRPAS) && !nr->_hoops_SRA->_hoops_IGHGH) {
		bool				_hoops_RCAI = false;

		_hoops_IGRS (dc);

		if (sc->_hoops_GPPAS) {
			void *							_hoops_CCHSP;

			_hoops_CCHSP = _hoops_AACGH (nr, true);
			HD_Std_DC_Polyline (nr, count, points);
			_hoops_PACGH (nr, _hoops_CCHSP);

			if (_hoops_IACGH (nr, _hoops_CCHSP) == 0)
				_hoops_RCAI = true;
		}
		else {
			_hoops_HCSIR alter *	_hoops_ICSIR = null;

			if (nr->_hoops_SAIR->_hoops_ASSIR != null)
				_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
			if (_hoops_ICSIR == null) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Expected frame buffer not found");
				_hoops_RCAI = true;
				goto _hoops_SIPAS;
			}

			_hoops_ICSIR->input._hoops_PHHSP = 0;
			_hoops_SCGGA (nr, count, points);
			if (_hoops_ICSIR->input._hoops_PHHSP == 0)
				_hoops_RCAI = true;
		}

	  _hoops_SIPAS:
		_hoops_SGRS (dc);
		if (_hoops_RCAI)
			return;
	}

#ifndef DISABLE_POLY_SELECTION
	if (sc->_hoops_CAPAS != 0) {
		bool		_hoops_CIHIA;

#if 0
		*offset1 = *offset2 = -1;
#endif
		if ((_hoops_CIHIA = _hoops_IAHAS (nr, count, (Point *)points, false, false)) != false) {
#if 0
			*_hoops_HISAP = 0.0f;		/* _hoops_SHR */

			/* _hoops_PSP _hoops_HPHR _hoops_SSH _hoops_HSH _hoops_HHPA, _hoops_HIS _hoops_SAHR _hoops_SGH _hoops_RH _hoops_PHRHA _hoops_PPSR */
			*_hoops_RCSAP = _hoops_IAIRA->z;
			while (--_hoops_ICGPA > 0) {
				++_hoops_IAIRA;
				if (*_hoops_RCSAP > _hoops_IAIRA->z)
					*_hoops_RCSAP = _hoops_IAIRA->z;
			}

			if (sc->_hoops_SRA->_hoops_IGHGH != null) {
				/* _hoops_HHPPA - _hoops_SCH _hoops_CSAP _hoops_GRRRI _hoops_HCGR */
				Display_Context alter		*dc;
				_hoops_HACC const					*text;

				dc = (Display_Context alter *)nr->_hoops_SRA;
				if ((text = dc->_hoops_IGHGH->_hoops_RHGGH) != null) {
					/* _hoops_PPR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_IRS _hoops_GSGR _hoops_HASRH */

					if (*_hoops_HISAP < dc->_hoops_IGHGH->_hoops_HHGGH) {
						dc->_hoops_IGHGH->_hoops_HHGGH	  = *_hoops_HISAP;
						dc->_hoops_IGHGH->_hoops_IHGGH	  = *_hoops_RCSAP;
						dc->_hoops_IGHGH->_hoops_CHGGH =	dc->_hoops_IGHGH->_hoops_PHGGH;
					}

					/* _hoops_IIS _hoops_RH _hoops_HCGR _hoops_PCPH _hoops_RGHH _hoops_RH _hoops_HPHR _hoops_RHHR */
					return;
				}
			}
#endif
			sc->_hoops_HPPAS._hoops_CIHIA = true;
		}
	}
	else
#endif
	{
		int alter					offset1;
		int alter					offset2;
		float alter					_hoops_HISAP;
		float alter					_hoops_RCSAP;

		if (count > 0) {
			_hoops_HISAP = sc->_hoops_GICAH;
			_hoops_GRIAS (nr, count, points,
										false, false,
										&offset1, &offset2, &_hoops_HISAP, &_hoops_RCSAP);
		}
		else {
			int							_hoops_RRC;

			_hoops_ICHC (count, _hoops_RRC, 2);
			while (count-- > 0) {
				_hoops_HISAP = sc->_hoops_GICAH;
				_hoops_GRIAS (nr, 2, points,
											false, false,
											&offset1, &offset2, &_hoops_HISAP, &_hoops_RCSAP);
				points += _hoops_RRC;
			}
		}
	}
#endif
}

GLOBAL_FUNCTION void HD_Select_DC_Polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;

	if (count == 0)
		return;

	if (nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, null, null, null, null, 0, 0, _hoops_RHGGA|_hoops_GPHC);
		return;
	}

	if (BIT (sc->options, _hoops_CRPAS) && !nr->_hoops_SRA->_hoops_IGHGH) {
		bool				_hoops_RCAI = false;

		_hoops_IGRS (dc);

		if (sc->_hoops_GPPAS) {
			void *							_hoops_CCHSP;

			_hoops_CCHSP = _hoops_AACGH (nr, true);
			HD_Std_DC_Polytriangle (nr, count, points);
			_hoops_PACGH (nr, _hoops_CCHSP);

			if (_hoops_IACGH (nr, _hoops_CCHSP) == 0)
				_hoops_RCAI = true;
		}
		else {
			_hoops_HCSIR alter *	_hoops_ICSIR = null;

			if (nr->_hoops_SAIR->_hoops_ASSIR != null)
				_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
			if (_hoops_ICSIR == null) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Expected frame buffer not found");
				_hoops_RCAI = true;
				goto _hoops_SIPAS;
			}

			_hoops_ICSIR->input._hoops_PHHSP = 0;
			HD_Std_DC_Polytriangle (nr, count, points);
			if (_hoops_ICSIR->input._hoops_PHHSP == 0)
				_hoops_RCAI = true;
		}

	  _hoops_SIPAS:
		_hoops_SGRS (dc);
		if (_hoops_RCAI)
			return;
	}

#ifndef DISABLE_POLY_SELECTION
	if (sc->_hoops_CAPAS != 0) {
		bool		_hoops_CIHIA;

#if 0
		*offset1 = *offset2 = -1;
#endif
		if ((_hoops_CIHIA = _hoops_IAHAS (nr, count, (Point *)points, false, false)) != 0) {
#if 0
			*_hoops_HISAP = 0.0f;		/* _hoops_SHR */

			/* _hoops_PSP _hoops_HPHR _hoops_SSH _hoops_HSH _hoops_HHPA, _hoops_HIS _hoops_SAHR _hoops_SGH _hoops_RH _hoops_PHRHA _hoops_PPSR */
			*_hoops_RCSAP = _hoops_IAIRA->z;
			while (--_hoops_ICGPA > 0) {
				++_hoops_IAIRA;
				if (*_hoops_RCSAP > _hoops_IAIRA->z)
					*_hoops_RCSAP = _hoops_IAIRA->z;
			}

			if (sc->_hoops_SRA->_hoops_IGHGH != null) {
				/* _hoops_HHPPA - _hoops_SCH _hoops_CSAP _hoops_GRRRI _hoops_HCGR */
				Display_Context alter		*dc;
				_hoops_HACC const					*text;

				dc = (Display_Context alter *)nr->_hoops_SRA;
				if ((text = dc->_hoops_IGHGH->_hoops_RHGGH) != null) {
					/* _hoops_PPR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_IRS _hoops_GSGR _hoops_HASRH */

					if (*_hoops_HISAP < dc->_hoops_IGHGH->_hoops_HHGGH) {
						dc->_hoops_IGHGH->_hoops_HHGGH	  = *_hoops_HISAP;
						dc->_hoops_IGHGH->_hoops_IHGGH	  = *_hoops_RCSAP;
						dc->_hoops_IGHGH->_hoops_CHGGH =	dc->_hoops_IGHGH->_hoops_PHGGH;
					}

					/* _hoops_IIS _hoops_RH _hoops_HCGR _hoops_PCPH _hoops_RGHH _hoops_RH _hoops_HPHR _hoops_RHHR */
					return;
				}
			}
#endif
			sc->_hoops_HPPAS._hoops_CIHIA = true;
		}
	}
	else
#endif
	{
		int alter					offset1;
		int alter					offset2;
		float alter					_hoops_HISAP;
		float alter					_hoops_RCSAP;
		int							_hoops_RRC;

		_hoops_ICHC (count, _hoops_RRC, 3);
		while (count-- > 0) {
			_hoops_HISAP = sc->_hoops_GICAH;
			if (_hoops_GRIAS (nr, 3, points,
										true, true,
										&offset1, &offset2, &_hoops_HISAP, &_hoops_RCSAP)) {
				if (_hoops_HISAP < sc->_hoops_HPPAS._hoops_HHGGH) {
					sc->_hoops_HPPAS._hoops_HHGGH = _hoops_HISAP;
					sc->_hoops_HPPAS._hoops_IHGGH	 = _hoops_RCSAP;
					sc->_hoops_HPPAS._hoops_CHGGH = sc->_hoops_HPPAS._hoops_PHGGH;
				}
			}
			points += _hoops_RRC;
		}
	}
#endif
}

GLOBAL_FUNCTION bool HD_Select_Point_List (
	Net_Rendition const &		nr,
	Geometry const *			geometry,
	int							_hoops_ICGPA,
	Point const *				_hoops_IAIRA,
	bool						_hoops_SPGPA,
	bool						_hoops_CSHIH,
	int alter *					offset1,
	int alter *					offset2,
	float alter *				_hoops_HISAP,
	float alter *				_hoops_RCSAP) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
#ifndef DISABLE_SELECTION
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;

	if (_hoops_ICGPA == 0) return false;

	if (BIT (sc->options, _hoops_CRPAS) && !dc->_hoops_IGHGH) {
		bool				_hoops_RCAI = false;

		_hoops_IGRS (dc);

		if (sc->_hoops_GPPAS) {
			void *							_hoops_CCHSP;

			_hoops_CCHSP = _hoops_AACGH (nr, true);
			if (_hoops_CSHIH) {
				Polygon *	polygon;

				ZALLOC (polygon, Polygon);

				polygon->_hoops_HIHI = 1;
				polygon->type = _hoops_RCIP;
				polygon->_hoops_CPGPR = _hoops_PHSSR;
				ALLOC_ARRAY (polygon->points, _hoops_ICGPA, Point);
				polygon->allocated = _hoops_ICGPA;

				_hoops_AIGA (_hoops_IAIRA, _hoops_ICGPA, Point, polygon->points);
				polygon->count = _hoops_ICGPA;

				_hoops_RCAIP (nr, polygon);

				_hoops_HPRH (polygon);
			}
			else {
				Polyline *	polyline;

				ZALLOC (polyline, Polyline);

				polyline->_hoops_HIHI = 1;
				polyline->type = _hoops_IIIP;
				polyline->_hoops_CPGPR = _hoops_PHSSR;
				ALLOC_ARRAY (polyline->points, Abs(_hoops_ICGPA)+1, Point);
				polyline->allocated = Abs(_hoops_ICGPA)+1;

				_hoops_AIGA (_hoops_IAIRA, Abs(_hoops_ICGPA), Point, polyline->points);
				polyline->count = _hoops_ICGPA;
				if (_hoops_SPGPA) {
					_hoops_RSAI (_hoops_IAIRA, Point, &polyline->points[_hoops_ICGPA]);
					polyline->count++;
				}

				_hoops_CCAIP (nr, polyline);

				_hoops_HPRH (polyline);
			}
			_hoops_PACGH (nr, _hoops_CCHSP);

			if (_hoops_IACGH (nr, _hoops_CCHSP) == 0)
				_hoops_RCAI = true;
		}
		else {
			_hoops_HCSIR alter *	_hoops_ICSIR = null;

			if (nr->_hoops_SAIR->_hoops_ASSIR != null)
				_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
			if (_hoops_ICSIR == null) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									"Expected frame buffer not found");
				_hoops_RCAI = true;
				goto _hoops_SIPAS;
			}

			_hoops_ICSIR->input._hoops_PHHSP = 0;

			if (_hoops_CSHIH) {
				Polygon *	polygon;

				ZALLOC (polygon, Polygon);

				polygon->_hoops_HIHI = 1;
				polygon->type = _hoops_RCIP;
				polygon->_hoops_CPGPR = _hoops_PHSSR;
				ALLOC_ARRAY (polygon->points, _hoops_ICGPA, Point);
				polygon->allocated = _hoops_ICGPA;

				_hoops_AIGA (_hoops_IAIRA, _hoops_ICGPA, Point, polygon->points);
				polygon->count = _hoops_ICGPA;

				_hoops_RCAIP (nr, polygon);

				_hoops_HPRH (polygon);
			}
			else {
				Polyline *	polyline;

				ZALLOC (polyline, Polyline);

				polyline->_hoops_HIHI = 1;
				polyline->type = _hoops_IIIP;
				polyline->_hoops_CPGPR = _hoops_PHSSR;
				ALLOC_ARRAY (polyline->points, Abs(_hoops_ICGPA)+1, Point);
				polyline->allocated = Abs(_hoops_ICGPA)+1;

				_hoops_AIGA (_hoops_IAIRA, Abs(_hoops_ICGPA), Point, polyline->points);
				polyline->count = _hoops_ICGPA;
				if (_hoops_SPGPA) {
					_hoops_RSAI (_hoops_IAIRA, Point, &polyline->points[_hoops_ICGPA]);
					polyline->count++;
				}

				_hoops_CCAIP (nr, polyline);

				_hoops_HPRH (polyline);
			}

			if (_hoops_ICSIR->input._hoops_PHHSP == 0)
				_hoops_RCAI = true;
		}

	  _hoops_SIPAS:
		_hoops_SGRS (dc);
		if (_hoops_RCAI)
			return false;
	}


#ifndef DISABLE_POLY_SELECTION
	if (sc->_hoops_CAPAS != 0) {
		*offset1 = *offset2 = -1;

		if (_hoops_ICGPA < 0) {
			Point const *pl = _hoops_IAIRA;

			_hoops_ICGPA = -_hoops_ICGPA;
			while (_hoops_ICGPA > 0) {
				if (_hoops_ARHAS (nr, geometry, 2, pl, _hoops_SPGPA, _hoops_CSHIH)) {
					_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
					_hoops_RPRA const *				elements = _hoops_IHCR->matrix->data.elements;

					*_hoops_HISAP = 0.0f;		/* _hoops_SHR */

					*_hoops_RCSAP = nr->transform_rendition->_hoops_PCHH;

					for (int i = 0; i < 2; ++i) {
						float		z = nr->transform_rendition->_hoops_PCHH;

						if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC))
							z = _hoops_CPRA (elements, pl[i]);
						else {
							float	w = _hoops_PHCP (elements, pl[i]);

							if (w >= _hoops_IHCR->_hoops_CHCR)
								z = _hoops_CPRA (elements, pl[i]) / w;
						}

						if (z < *_hoops_RCSAP)
							*_hoops_RCSAP = z;
					}

					return true;
				}
				pl += 2;
				_hoops_ICGPA -= 2;
			}
		}
		else {
			if (_hoops_ARHAS (nr, geometry, _hoops_ICGPA, _hoops_IAIRA, _hoops_SPGPA, _hoops_CSHIH)) {
				_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
				_hoops_RPRA const *				elements = _hoops_IHCR->matrix->data.elements;

				*_hoops_HISAP = 0.0f;		/* _hoops_SHR */

				/* _hoops_PSP _hoops_HPHR _hoops_SSH _hoops_HSH _hoops_HHPA, _hoops_HIS _hoops_SAHR _hoops_SGH _hoops_RH _hoops_PHRHA _hoops_PPSR */
				*_hoops_RCSAP = nr->transform_rendition->_hoops_PCHH;
				for (int i = 0; i < _hoops_ICGPA; ++i) {
					float		z = nr->transform_rendition->_hoops_PCHH;

					if (!_hoops_IHGSP (_hoops_IHCR->_hoops_HGSC))
						z = _hoops_CPRA (elements, _hoops_IAIRA[i]);
					else {
						float	w = _hoops_PHCP (elements, _hoops_IAIRA[i]);

						if (w >= _hoops_IHCR->_hoops_CHCR)
							z = _hoops_CPRA (elements, _hoops_IAIRA[i]) / w;
					}

					if (z < *_hoops_RCSAP)
						*_hoops_RCSAP = z;
				}

				if (sc->_hoops_SRA->_hoops_IGHGH != null) {
					/* _hoops_HHPPA - _hoops_SCH _hoops_CSAP _hoops_GRRRI _hoops_HCGR */
					_hoops_HACC const					*text;

					if ((text = dc->_hoops_IGHGH->_hoops_RHGGH) != null) {
						/* _hoops_PPR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_IRS _hoops_GSGR _hoops_HASRH */

						if (*_hoops_HISAP < dc->_hoops_IGHGH->_hoops_HHGGH) {
							dc->_hoops_IGHGH->_hoops_HHGGH	  = *_hoops_HISAP;
							dc->_hoops_IGHGH->_hoops_IHGGH	  = *_hoops_RCSAP;
							dc->_hoops_IGHGH->_hoops_CHGGH =	dc->_hoops_IGHGH->_hoops_PHGGH;
						}

						/* _hoops_IIS _hoops_RH _hoops_HCGR _hoops_PCPH _hoops_RGHH _hoops_RH _hoops_HPHR _hoops_RHHR */
						return false;
					}
				}

				return true;
			}
		}

		return false;
	}
	else
#endif
	{
		if (_hoops_ICGPA < 0) {
			bool			_hoops_CIHIA = false;
			Point const *	pl = _hoops_IAIRA;

			_hoops_ICGPA = -_hoops_ICGPA;
			while (_hoops_ICGPA > 0) {
				int			_hoops_ARIAS = -1, _hoops_PRIAS = -1;
				float		pp = *_hoops_HISAP, _hoops_HRIAS = *_hoops_RCSAP;

				if (_hoops_CAHAS (nr, geometry, 2, pl,
										 _hoops_SPGPA, _hoops_CSHIH,
										 &_hoops_ARIAS, &_hoops_PRIAS, &pp, &_hoops_HRIAS)) {
					if (pp < *_hoops_HISAP || _hoops_HRIAS < *_hoops_RCSAP) {
						*offset1 = _hoops_ARIAS + (pl - _hoops_IAIRA);
						*offset2 = _hoops_PRIAS + (pl - _hoops_IAIRA);
						*_hoops_HISAP = pp;
						*_hoops_RCSAP = _hoops_HRIAS;
						_hoops_CIHIA = true;
					}
				}
				pl += 2;
				_hoops_ICGPA -= 2;
			}

			return _hoops_CIHIA;
		}
		else
			return _hoops_CAHAS (nr, geometry, _hoops_ICGPA, _hoops_IAIRA,
										_hoops_SPGPA, _hoops_CSHIH,
										offset1, offset2, _hoops_HISAP, _hoops_RCSAP);
	}
#else
	return false;
#endif
}

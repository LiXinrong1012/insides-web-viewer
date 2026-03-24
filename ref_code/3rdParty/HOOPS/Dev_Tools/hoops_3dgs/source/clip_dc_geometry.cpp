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
 * $Id: obf_tmp.txt 1.79 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "patterns.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HD_Validate_Clip_Half_Planes (
	_hoops_ASHH *	_hoops_CRAIR,
	bool					_hoops_HAGGA) {
#ifndef DISABLE_DRAW_3D
	int						i;

	if (_hoops_CRAIR->_hoops_GRCPR == null)
		ALLOC_ARRAY (_hoops_CRAIR->_hoops_GRCPR, _hoops_CRAIR->count, _hoops_GPPA);
	ZERO_ARRAY(_hoops_CRAIR->_hoops_GRCPR, _hoops_CRAIR->count, _hoops_GPPA);

	for (i=0; i<_hoops_CRAIR->count-1; i++) {
		_hoops_CRAIR->_hoops_GRCPR[i].next = &_hoops_CRAIR->_hoops_GRCPR[i+1];
	}

	for (i=0; i<_hoops_CRAIR->count; i++) {
		int				j;

		if ((j = i+1) == _hoops_CRAIR->count)
			j = 0;

		_hoops_CRAIR->_hoops_GRCPR[i]._hoops_SPPA.a = _hoops_CRAIR->points[j].y - _hoops_CRAIR->points[i].y;
		_hoops_CRAIR->_hoops_GRCPR[i]._hoops_SPPA.b = _hoops_CRAIR->points[i].x - _hoops_CRAIR->points[j].x;
		// ._hoops_GSGGR _hoops_PPR ._hoops_GHGP _hoops_IAGGA _hoops_ARRS

		_hoops_CRAIR->_hoops_GRCPR[i]._hoops_SPPA._hoops_AAIAR();

		_hoops_CRAIR->_hoops_GRCPR[i]._hoops_SPPA.d =
			-(_hoops_CRAIR->_hoops_GRCPR[i]._hoops_SPPA.a * _hoops_CRAIR->points[i].x +
				_hoops_CRAIR->_hoops_GRCPR[i]._hoops_SPPA.b * _hoops_CRAIR->points[i].y);
	}

	/* _hoops_ISPR _hoops_HSCHR _hoops_PPR _hoops_GAAP _hoops_IHAA _hoops_HCR */
	if ((_hoops_CRAIR->_hoops_GRCPR[0]._hoops_SPPA.a * _hoops_CRAIR->_hoops_GRCPR[1]._hoops_SPPA.b -
		 _hoops_CRAIR->_hoops_GRCPR[0]._hoops_SPPA.b * _hoops_CRAIR->_hoops_GRCPR[1]._hoops_SPPA.a < 0.0f) != _hoops_HAGGA) {

		for (i=0; i<_hoops_CRAIR->count; i++)
			_hoops_CRAIR->_hoops_GRCPR[i]._hoops_SPPA = -_hoops_CRAIR->_hoops_GRCPR[i]._hoops_SPPA;
	}
#endif
}


GLOBAL_FUNCTION _hoops_GPPA * HD_Create_Hard_Clip_Cuts (
	Net_Rendition const &			inr,
	Int_Rectangle const *			rect,
	_hoops_HRPA const *				mat,
	int								bias) {
	_hoops_GPPA alter *	_hoops_CAGGA;
	_hoops_GPPA alter *	_hoops_IRCAR;
	_hoops_GPPA alter **	_hoops_SAGGA = &_hoops_CAGGA;
	int								i;

	for (i=0; i<4; i++) {
		POOL_ZALLOC (_hoops_IRCAR, _hoops_GPPA, inr->_hoops_SRA->memory_pool);
		*_hoops_SAGGA = _hoops_IRCAR;
		_hoops_SAGGA = &_hoops_IRCAR->next;
		_hoops_IRCAR->next = null;
		_hoops_IRCAR->internal = true;

		switch (i) {
			case 0: {
				_hoops_IRCAR->_hoops_SPPA.a = -1.0f;
				_hoops_IRCAR->_hoops_SPPA.b = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.c = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.d = (float)(rect->left - bias) - 0.5f;
			}	break;
			case 1: {
				_hoops_IRCAR->_hoops_SPPA.a = 1.0f;
				_hoops_IRCAR->_hoops_SPPA.b = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.c = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.d = -(float)(rect->right + bias) - 1.0f;
			}	break;
			case 2: {
				_hoops_IRCAR->_hoops_SPPA.a = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.b = -1.0f;
				_hoops_IRCAR->_hoops_SPPA.c = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.d = (float)(rect->bottom - bias) - 0.5f;
			}	break;
			case 3: {
				_hoops_IRCAR->_hoops_SPPA.a = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.b = 1.0f;
				_hoops_IRCAR->_hoops_SPPA.c = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.d = -(float)(rect->top + bias) - 1.0f;
			}	break;
		}

		if (mat) {
			_hoops_IRCAR->_hoops_SHPA.a =
					   mat->elements[0][0] * _hoops_IRCAR->_hoops_SPPA.a +
					   mat->elements[0][1] * _hoops_IRCAR->_hoops_SPPA.b +
					   mat->elements[0][2] * _hoops_IRCAR->_hoops_SPPA.c +
					   mat->elements[0][3] * _hoops_IRCAR->_hoops_SPPA.d;

			_hoops_IRCAR->_hoops_SHPA.b =
					   mat->elements[1][0] * _hoops_IRCAR->_hoops_SPPA.a +
					   mat->elements[1][1] * _hoops_IRCAR->_hoops_SPPA.b +
					   mat->elements[1][2] * _hoops_IRCAR->_hoops_SPPA.c +
					   mat->elements[1][3] * _hoops_IRCAR->_hoops_SPPA.d;

			_hoops_IRCAR->_hoops_SHPA.c =
					   mat->elements[2][0] * _hoops_IRCAR->_hoops_SPPA.a +
					   mat->elements[2][1] * _hoops_IRCAR->_hoops_SPPA.b +
					   mat->elements[2][2] * _hoops_IRCAR->_hoops_SPPA.c +
					   mat->elements[2][3] * _hoops_IRCAR->_hoops_SPPA.d;

			_hoops_IRCAR->_hoops_SHPA.d =
					   mat->elements[3][0] * _hoops_IRCAR->_hoops_SPPA.a +
					   mat->elements[3][1] * _hoops_IRCAR->_hoops_SPPA.b +
					   mat->elements[3][2] * _hoops_IRCAR->_hoops_SPPA.c +
					   mat->elements[3][3] * _hoops_IRCAR->_hoops_SPPA.d;

			if (!HI_Normalize_Plane (&_hoops_IRCAR->_hoops_SHPA))
				HE_WARNING (HEC_CUTTING_PLANE, HES_SINGULAR_PLANE,
					"A cutting plane became singular after transforming");
		}
	}

	return _hoops_CAGGA;
}


GLOBAL_FUNCTION _hoops_ASHH * HD_Create_Hard_Clip_Region (
	Int_Rectangle const *			rect,
	int								bias) {
	_hoops_ASHH alter *		region;

	ZALLOC (region, _hoops_ASHH);
	_hoops_ICAI(region);
	region->count = 4;
	ZALLOC_ARRAY (region->points, 4, DC_Point);

	region->points[0] = Point (rect->left  - bias, rect->bottom - bias, 0);
	region->points[1] = Point (rect->left  - bias, rect->top    + bias, 0);
	region->points[2] = Point (rect->right + bias, rect->top    + bias, 0);
	region->points[3] = Point (rect->right + bias, rect->bottom - bias, 0);

	return region;
}



GLOBAL_FUNCTION void HD_Clip_DC_Polydot (
	Net_Rendition const &			inr,
	int								count,
	DC_Point const *				points,
	RGBAS32 const *					colors,
	_hoops_GPGGA					flags) {
	_hoops_GPPA const *	_hoops_RPGGA[4];
	Net_Rendition					nr = inr.Copy();
	_hoops_HHCR				_hoops_GGCC = nr->transform_rendition.Modify();;
	_hoops_GPPA const *	_hoops_APGGA = 0;
	_hoops_IAPA const *		_hoops_CAPA = null;
	_hoops_ASHH const *		_hoops_PPGGA = null;
	int								_hoops_HPGGA = -1;
	int								_hoops_IPGGA = -1;
	int								_hoops_CPGGA = 0;
	int								_hoops_HAHC = count;
	DC_Point const *				_hoops_SPGGA = points;
	RGBAS32 const *					_hoops_GHGGA = colors;


	if (BIT (flags, _hoops_RHGGA) && _hoops_GGCC->_hoops_HCHH) {
		if (_hoops_GGCC->_hoops_HCHH->_hoops_AHGGA == null)
			HD_Validate_Clipping_Rendition (_hoops_GGCC, _hoops_GGCC->_hoops_HCHH, flags);	// _hoops_RSIH _hoops_GGR _hoops_AGIR _hoops_SCH _hoops_SHPH _hoops_SGI

		if (_hoops_GGCC->_hoops_HCHH->_hoops_AHGGA->count == 0)	// _hoops_ISAP _hoops_PAH _hoops_SHH _hoops_CHCC
			return;
	}



	if (BIT (flags, _hoops_PHGGA) &&  !BIT (_hoops_GGCC->flags, _hoops_AIHS)) {
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_APGGA = HD_Create_Hard_Clip_Cuts (inr, &_hoops_GGCC->_hoops_AGAA, null, 0);
		_hoops_GGCC->flags |= _hoops_AIHS;
	}

	if (BIT (flags, _hoops_RHGGA) && _hoops_GGCC->_hoops_HCHH) {
		_hoops_IPGGA = _hoops_CPGGA;

		_hoops_PPGGA = _hoops_GGCC->_hoops_HCHH->_hoops_AHGGA;
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_PPGGA->_hoops_GRCPR;
		_hoops_PPGGA = _hoops_PPGGA->next;

		_hoops_GGCC->_hoops_HCHH = null;
	}

	if (BIT (flags, _hoops_GPHC) && BIT (_hoops_GGCC->flags, _hoops_CSP)) {
		_hoops_SSP const &		_hoops_GGH = inr->transform_rendition->_hoops_RGH;

		if (BIT (_hoops_GGCC->flags, _hoops_HHGGA))
			HD_Set_DC_Cutting_Planes (nr);

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
		}
		else
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;

		_hoops_HPGGA = _hoops_CPGGA;
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_CAPA->_hoops_APPA;
		_hoops_CAPA = _hoops_CAPA->next;

		/* _hoops_PAGA: _hoops_PAH'_hoops_RA _hoops_CIH _hoops_HICC _hoops_GAPR _hoops_GAR _hoops_SR _hoops_HHGC _hoops_IS _hoops_ACAHR _hoops_IS _hoops_RGCI _hoops_SRGR */
		_hoops_GGCC->_hoops_RGH = null;
		_hoops_GGCC->flags &= ~_hoops_CSP;
	}

	_hoops_RPGGA[_hoops_CPGGA] = 0;



	_hoops_PCCAR {
		_hoops_PCCAR {
			while (count-- > 0) {
				_hoops_GPPA const *_hoops_GRCPR;
				_hoops_GPPA const **_hoops_IHGGA = _hoops_RPGGA;

				while ((_hoops_GRCPR=*_hoops_IHGGA++) != null) {
					while (_hoops_GRCPR) {
						float			_hoops_CHGGA;

						_hoops_CHGGA = _hoops_GRCPR->_hoops_SPPA.a * points[0].x +
									_hoops_GRCPR->_hoops_SPPA.b * points[0].y +
									 _hoops_GRCPR->_hoops_SPPA.c * points[0].z +
									  _hoops_GRCPR->_hoops_SPPA.d;

						if (_hoops_CHGGA > 0.0f)
							goto _hoops_SHGGA;

						_hoops_GRCPR = _hoops_GRCPR->next;
					}
				}

				/* _hoops_RGR _hoops_HHS _hoops_PGGC _hoops_GH _hoops_HCR _hoops_RH _hoops_PSCHR _hoops_IH _hoops_IRS _hoops_RSRA _hoops_GIGGA _hoops_AASA */
				if (colors)
					_hoops_RIGGA (nr, 1, &points[0], colors, true);
				else
					_hoops_AIGGA (nr, 1, &points[0]);

			  _hoops_SHGGA:

				if (colors) {
					if (ANYBIT (flags, _hoops_AAIC|_hoops_PAIC))
						colors++;
					/*_hoops_PIGGA _hoops_AA _hoops_ISAP */
				}
				points++;
			}

			if (_hoops_CAPA == null)
				break;
			else {
				_hoops_RPGGA[_hoops_HPGGA] = _hoops_CAPA->_hoops_APPA;
				_hoops_CAPA = _hoops_CAPA->next;

				count = _hoops_HAHC;
				points = _hoops_SPGGA;
				colors = _hoops_GHGGA;
			}
		}

		if (_hoops_PPGGA == null)
			break;
		else {
			_hoops_RPGGA[_hoops_IPGGA] = _hoops_PPGGA->_hoops_GRCPR;
			_hoops_PPGGA = _hoops_PPGGA->next;

			count = _hoops_HAHC;
			points = _hoops_SPGGA;
			colors = _hoops_GHGGA;
		}
	}

	while (_hoops_APGGA) {
		_hoops_GPPA const *	c = _hoops_APGGA;

		_hoops_APGGA = _hoops_APGGA->next;
		FREE (c, _hoops_GPPA);
	}
}

local void _hoops_HIGGA (
	Net_Rendition const &			nr,
	DC_Point const *				points,
	RGBAS32 const *					colors,
	RGBA const *					rgba_colors,
	_hoops_ARPA const *					planes,
	_hoops_RSSH const *				_hoops_CCHA,
	int								param_width,
	_hoops_SSIC					param_flags,
	_hoops_GPGGA					flags,
	_hoops_GPPA const **	_hoops_RPGGA,
	int								depth) {
	_hoops_GPPA const **	_hoops_IIGGA = _hoops_RPGGA;
	_hoops_GPPA const *	_hoops_GRCPR;
	float							_hoops_CIGGA = 0.0f, _hoops_SIGGA = 1.0f;
	bool							_hoops_GCGGA = false;
	float							dx, _hoops_CRRAR, _hoops_AAAC;
	float							t;

	dx = points[1].x - points[0].x;
	_hoops_CRRAR = points[1].y - points[0].y;
	_hoops_AAAC = points[1].z - points[0].z;

	while ((_hoops_GRCPR = *_hoops_RPGGA++) != null) {
		while (_hoops_GRCPR) {
			float	_hoops_RCGGA, _hoops_CHGGA;

			_hoops_RCGGA =  _hoops_GRCPR->_hoops_SPPA.a * points[0].x +
						_hoops_GRCPR->_hoops_SPPA.b * points[0].y +
						 _hoops_GRCPR->_hoops_SPPA.c * points[0].z +
						  _hoops_GRCPR->_hoops_SPPA.d;

			_hoops_CHGGA = _hoops_GRCPR->_hoops_SPPA.a * points[1].x +
						_hoops_GRCPR->_hoops_SPPA.b * points[1].y +
						 _hoops_GRCPR->_hoops_SPPA.c * points[1].z +
						  _hoops_GRCPR->_hoops_SPPA.d;

			if (_hoops_RCGGA > 0.0f) {
				if (_hoops_CHGGA > 0.0f) {
					/* _hoops_GIPR _hoops_SIPP _hoops_RGR _hoops_PPAP */
					_hoops_CIGGA = 1.0f;
					_hoops_SIGGA = 0.0f;
					return;
				}
				else {
					/* _hoops_HSPH _hoops_ACGGA */
					t = -_hoops_RCGGA / (
						_hoops_GRCPR->_hoops_SPPA.a * dx +
						 _hoops_GRCPR->_hoops_SPPA.b * _hoops_CRRAR +
						  _hoops_GRCPR->_hoops_SPPA.c * _hoops_AAAC);

					/* _hoops_PSSSR _hoops_IH _hoops_GPPS _hoops_HHGS */
					if (t > 0.999f && t != 1.0f && depth < 2) {
						DC_Point		_hoops_HHAHR[2];

						_hoops_HHAHR[1] = points[0];
						_hoops_HHAHR[0] = points[1];
						_hoops_HIGGA (nr, _hoops_HHAHR, colors, rgba_colors, planes,
								   _hoops_CCHA, param_width, param_flags,
								   flags, _hoops_IIGGA, depth+1);
						return;
					}

					if (t > _hoops_CIGGA) {
						_hoops_CIGGA = t;
						if (_hoops_CIGGA > _hoops_SIGGA)
							return;
						_hoops_GCGGA = true;
					}
				}
			}
			else {
				if (_hoops_CHGGA > 0.0f) {
					/* _hoops_HSPH _hoops_PHGHR */
					t = -_hoops_RCGGA / (
						_hoops_GRCPR->_hoops_SPPA.a * dx +
						 _hoops_GRCPR->_hoops_SPPA.b * _hoops_CRRAR +
						  _hoops_GRCPR->_hoops_SPPA.c * _hoops_AAAC);

					if (t < _hoops_SIGGA) {
						_hoops_SIGGA = t;
						if (_hoops_SIGGA < _hoops_CIGGA)
							return;
						_hoops_GCGGA = true;
					}
				}
				else {
					/* _hoops_GIPR _hoops_ASSA _hoops_RGR _hoops_PPAP */
				}
			}
			_hoops_GRCPR = _hoops_GRCPR->next;
		}
	}

	/* _hoops_PGSA _hoops_PA _hoops_SGS _hoops_IGICR */
	if (!_hoops_GCGGA) {
		if (_hoops_CCHA)
			_hoops_PCGGA (nr, 2, points, rgba_colors, planes,
										   _hoops_CCHA, param_width, param_flags);
		else if (planes)
			_hoops_HCGGA (nr, 2, points, rgba_colors, planes);
		else if (colors) {
			if (BIT (flags, _hoops_AAIC))
				_hoops_ICGGA (nr, 2, points, colors);
			else
				_hoops_CCGGA (nr, 2, points, colors, true);
		}
		else
			_hoops_SCGGA (nr, 2, points);
	}
	else {
		DC_Point _hoops_GSGGA[2];

		_hoops_GSGGA[0].x = points[0].x + _hoops_CIGGA * dx;
		_hoops_GSGGA[0].y = points[0].y + _hoops_CIGGA * _hoops_CRRAR;
		_hoops_GSGGA[0].z = points[0].z + _hoops_CIGGA * _hoops_AAAC;
		_hoops_GSGGA[1].x = points[0].x + _hoops_SIGGA * dx;
		_hoops_GSGGA[1].y = points[0].y + _hoops_SIGGA * _hoops_CRRAR;
		_hoops_GSGGA[1].z = points[0].z + _hoops_SIGGA * _hoops_AAAC;

		if (_hoops_CCHA) {
			_hoops_RSSH			_hoops_RSGGA[256];
			_hoops_ARPA				_hoops_ASGGA[2];
			RGBA				_hoops_PSGGA[2];
			float				_hoops_HSGGA;
			float				_hoops_ISGGA = 1.0f;

			if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
				_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
				_hoops_SGCC const &	mat = _hoops_IHCR->_hoops_CGCC;
				_hoops_RPRA const *			_hoops_APRA;
				float						ws[2];
				Point						_hoops_SSGGA;
				float						_hoops_APCP;

				if (!BIT (_hoops_IHCR->flags, _hoops_IGCC))
					HD_Validate_World_To_Screen (nr);

				_hoops_APRA = mat->_hoops_PPRA()->data.elements;

				_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[0]);
				_hoops_SSGGA.x = _hoops_HPRA (_hoops_APRA, points[0]) * _hoops_APCP;
				_hoops_SSGGA.y = _hoops_IPRA (_hoops_APRA, points[0]) * _hoops_APCP;
				_hoops_SSGGA.z = _hoops_CPRA (_hoops_APRA, points[0]) * _hoops_APCP;
				ws[0] = _hoops_PHCP (mat->data.elements, _hoops_SSGGA);

				_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[1]);
				_hoops_SSGGA.x = _hoops_HPRA (_hoops_APRA, points[1]) * _hoops_APCP;
				_hoops_SSGGA.y = _hoops_IPRA (_hoops_APRA, points[1]) * _hoops_APCP;
				_hoops_SSGGA.z = _hoops_CPRA (_hoops_APRA, points[1]) * _hoops_APCP;
				ws[1] = _hoops_PHCP (mat->data.elements, _hoops_SSGGA);

				_hoops_ISGGA = ws[1] / ws[0];
			}

			_hoops_GGRGA (nr, &_hoops_CCHA[0], &_hoops_CCHA[param_width],
								   _hoops_CIGGA, &_hoops_RSGGA[0], _hoops_ISGGA, param_width);
			_hoops_GGRGA (nr, &_hoops_CCHA[0], &_hoops_CCHA[param_width],
								   _hoops_SIGGA, &_hoops_RSGGA[param_width], _hoops_ISGGA, param_width);

			if (planes != null) {
				_hoops_RGRGA (planes[0], planes[1], _hoops_CIGGA, _hoops_ASGGA[0]);
				_hoops_RGRGA (planes[0], planes[1], _hoops_SIGGA, _hoops_ASGGA[1]);
			}

			if (colors != null) {
				dx = rgba_colors[1].red	  - rgba_colors[0].red;
				_hoops_CRRAR = rgba_colors[1].green - rgba_colors[0].green;
				_hoops_AAAC = rgba_colors[1].blue  - rgba_colors[0].blue;
				_hoops_HSGGA = rgba_colors[1].alpha - rgba_colors[0].alpha;

				_hoops_PSGGA[0].red	= rgba_colors[0].red + _hoops_CIGGA * dx;
				_hoops_PSGGA[0].green	= rgba_colors[0].green + _hoops_CIGGA * _hoops_CRRAR;
				_hoops_PSGGA[0].blue	= rgba_colors[0].blue + _hoops_CIGGA * _hoops_AAAC;
				_hoops_PSGGA[0].alpha	= rgba_colors[0].alpha + _hoops_CIGGA * _hoops_HSGGA;

				_hoops_PSGGA[1].red	= rgba_colors[0].red + _hoops_SIGGA * dx;
				_hoops_PSGGA[1].green	= rgba_colors[0].green + _hoops_SIGGA * _hoops_CRRAR;
				_hoops_PSGGA[1].blue	= rgba_colors[0].blue + _hoops_SIGGA * _hoops_AAAC;
				_hoops_PSGGA[1].alpha	= rgba_colors[0].alpha + _hoops_SIGGA * _hoops_HSGGA;
			}

			_hoops_PCGGA (nr, 2, _hoops_GSGGA,
										   colors ? _hoops_PSGGA :(RGBA*)null,
										   planes ? _hoops_ASGGA : (_hoops_ARPA*)null,
										   _hoops_RSGGA, param_width, param_flags);
		}
		else if (planes) {
			_hoops_ARPA		_hoops_ASGGA[2];
			RGBA		_hoops_PSGGA[2];
			float		_hoops_HSGGA;

			_hoops_RGRGA (planes[0], planes[1], _hoops_CIGGA, _hoops_ASGGA[0]);
			_hoops_RGRGA (planes[0], planes[1], _hoops_SIGGA, _hoops_ASGGA[1]);

			if (colors != null) {
				dx = rgba_colors[1].red - rgba_colors[0].red;
				_hoops_CRRAR = rgba_colors[1].green - rgba_colors[0].green;
				_hoops_AAAC = rgba_colors[1].blue - rgba_colors[0].blue;
				_hoops_HSGGA = rgba_colors[1].alpha - rgba_colors[0].alpha;

				_hoops_PSGGA[0].red	= rgba_colors[0].red + _hoops_CIGGA * dx;
				_hoops_PSGGA[0].green	= rgba_colors[0].green + _hoops_CIGGA * _hoops_CRRAR;
				_hoops_PSGGA[0].blue	= rgba_colors[0].blue + _hoops_CIGGA * _hoops_AAAC;
				_hoops_PSGGA[0].alpha	= rgba_colors[0].alpha + _hoops_CIGGA * _hoops_HSGGA;

				_hoops_PSGGA[1].red	= rgba_colors[0].red + _hoops_SIGGA * dx;
				_hoops_PSGGA[1].green	= rgba_colors[0].green + _hoops_SIGGA * _hoops_CRRAR;
				_hoops_PSGGA[1].blue	= rgba_colors[0].blue + _hoops_SIGGA * _hoops_AAAC;
				_hoops_PSGGA[1].alpha	= rgba_colors[0].alpha + _hoops_SIGGA * _hoops_HSGGA;

				_hoops_HCGGA (nr, 2, _hoops_GSGGA, _hoops_PSGGA, _hoops_ASGGA);
			}
			else
				_hoops_HCGGA (nr, 2, _hoops_GSGGA, null, _hoops_ASGGA);
		}
		else if (colors) {
			if (BIT (flags, _hoops_AAIC)) {
				RGBAS32	_hoops_AGRGA[2];

				dx = colors[1].r - colors[0].r;
				_hoops_CRRAR = colors[1].g - colors[0].g;
				_hoops_AAAC = colors[1].b - colors[0].b;

				_hoops_AGRGA[0].r = (unsigned char)(colors[0].r + _hoops_CIGGA * dx);
				_hoops_AGRGA[0].g = (unsigned char)(colors[0].g + _hoops_CIGGA * _hoops_CRRAR);
				_hoops_AGRGA[0].b = (unsigned char)(colors[0].b + _hoops_CIGGA * _hoops_AAAC);
				_hoops_AGRGA[0].a = colors[0].a;

				_hoops_AGRGA[1].r = (unsigned char)(colors[0].r + _hoops_SIGGA * dx);
				_hoops_AGRGA[1].g = (unsigned char)(colors[0].g + _hoops_SIGGA * _hoops_CRRAR);
				_hoops_AGRGA[1].b = (unsigned char)(colors[0].b + _hoops_SIGGA * _hoops_AAAC);
				_hoops_AGRGA[1].a = colors[1].a;

				_hoops_ICGGA (nr, 2, _hoops_GSGGA, _hoops_AGRGA);
			}
			else
				_hoops_CCGGA (nr, 2, _hoops_GSGGA, colors, true);
		}
		else
			_hoops_SCGGA (nr, 2, _hoops_GSGGA);
	}

}


GLOBAL_FUNCTION void HD_Clip_DC_Polyline (
	Net_Rendition const &			inr,
	int								count,
	DC_Point const *				points,
	RGBAS32 const *					colors,
	RGBA const *					rgba_colors,
	_hoops_ARPA const *					planes,
	_hoops_RSSH const *				_hoops_CCHA,
	int								param_width,
	_hoops_SSIC					param_flags,
	_hoops_GPGGA					flags) {
	Net_Rendition					nr = inr;
	_hoops_GPPA const *	_hoops_RPGGA[4];
	_hoops_GPPA const *	_hoops_APGGA = null;
	_hoops_IAPA const *		_hoops_CAPA = null;
	_hoops_ASHH const *		_hoops_PPGGA = null;
	int								_hoops_HPGGA = -1;
	int								_hoops_IPGGA = -1;
	int								_hoops_HAHC;
	DC_Point const *				_hoops_SPGGA = points;
	RGBAS32 const *					_hoops_GHGGA = colors;
	RGBA const *					_hoops_PGRGA = rgba_colors;
	_hoops_ARPA const *					_hoops_HGRGA = planes;
	_hoops_RSSH const *				_hoops_IGRGA = _hoops_CCHA;
	_hoops_HHCR				_hoops_GGCC;
	int 							_hoops_CPGGA = 0;
	int 							_hoops_RRC;

	_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

	if (BIT (flags, _hoops_RHGGA) && _hoops_GGCC->_hoops_HCHH) {
		if (_hoops_GGCC->_hoops_HCHH->_hoops_AHGGA == null)
			HD_Validate_Clipping_Rendition (_hoops_GGCC, _hoops_GGCC->_hoops_HCHH, flags);	// _hoops_RSIH _hoops_GGR _hoops_AGIR _hoops_SCH _hoops_SHPH _hoops_SGI

		if (_hoops_GGCC->_hoops_HCHH->_hoops_AHGGA->count == 0)	// _hoops_ISAP _hoops_PAH _hoops_SHH _hoops_CHCC
			return;
	}



	if (BIT (flags, _hoops_PHGGA) && !BIT (_hoops_GGCC->flags, _hoops_AIHS)) {
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_APGGA = HD_Create_Hard_Clip_Cuts (inr, &_hoops_GGCC->_hoops_AGAA, null, 0);
		_hoops_GGCC->flags |= _hoops_AIHS;
	}
	else if (BIT (flags, _hoops_CGRGA)) {
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_APGGA = HD_Create_Hard_Clip_Cuts (inr, &_hoops_GGCC->_hoops_AGAA, null, _hoops_SGRGA);
	}

	if (BIT (flags, _hoops_RHGGA) && _hoops_GGCC->_hoops_HCHH) {
		_hoops_IPGGA = _hoops_CPGGA;

		_hoops_PPGGA = _hoops_GGCC->_hoops_HCHH->_hoops_AHGGA;
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_PPGGA->_hoops_GRCPR;
		_hoops_PPGGA = _hoops_PPGGA->next;

		_hoops_GGCC->_hoops_HCHH = null;
	}

	if (BIT (flags, _hoops_GPHC) && BIT (_hoops_GGCC->flags, _hoops_CSP)) {
		_hoops_SSP const &		_hoops_GGH = inr->transform_rendition->_hoops_RGH;

		if (BIT (_hoops_GGCC->flags, _hoops_HHGGA))
			HD_Set_DC_Cutting_Planes (nr);

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
		}
		else
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;

		_hoops_HPGGA = _hoops_CPGGA;
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_CAPA->_hoops_APPA;
		_hoops_CAPA = _hoops_CAPA->next;

		_hoops_GGCC->_hoops_RGH = null;
		_hoops_GGCC->flags &= ~_hoops_CSP;
	}

	_hoops_RPGGA[_hoops_CPGGA] = 0;


	_hoops_ICHC (count, _hoops_RRC, 2);
	_hoops_HAHC = count;

	_hoops_PCCAR {
		_hoops_PCCAR {
			while (count-- > 0) {
				_hoops_HIGGA (nr, points, colors, rgba_colors, planes, _hoops_CCHA, param_width, param_flags, flags, _hoops_RPGGA, 0);
				points += _hoops_RRC;

				if (colors) {
					if (BIT (flags, _hoops_AAIC))
						colors += _hoops_RRC;
					else if (BIT (flags, _hoops_PAIC))
						colors++;
					/*_hoops_PIGGA _hoops_AA _hoops_ISAP */
				}
				else if (rgba_colors)
					rgba_colors += _hoops_RRC;

				if (planes)
					planes += _hoops_RRC;
				if (_hoops_CCHA)
					_hoops_CCHA += param_width*_hoops_RRC;
			}

			if (_hoops_CAPA == null)
				break;
			else {
				_hoops_RPGGA[_hoops_HPGGA] = _hoops_CAPA->_hoops_APPA;
				_hoops_CAPA = _hoops_CAPA->next;

				count = _hoops_HAHC;
				points = _hoops_SPGGA;
				colors = _hoops_GHGGA;
				rgba_colors = _hoops_PGRGA;
				planes = _hoops_HGRGA;
				_hoops_CCHA = _hoops_IGRGA;
			}
		}

		if (_hoops_PPGGA == null)
			break;
		else {
			_hoops_RPGGA[_hoops_IPGGA] = _hoops_PPGGA->_hoops_GRCPR;
			_hoops_PPGGA = _hoops_PPGGA->next;

			count = _hoops_HAHC;
			points = _hoops_SPGGA;
			colors = _hoops_GHGGA;
			rgba_colors = _hoops_PGRGA;
			planes = _hoops_HGRGA;
			_hoops_CCHA = _hoops_IGRGA;
		}
	}

	while (_hoops_APGGA) {
		_hoops_GPPA const *	c = _hoops_APGGA;

		_hoops_APGGA = _hoops_APGGA->next;
		FREE (c, _hoops_GPPA);
	}
}


local _hoops_ASHH * _hoops_GRRGA (
	_hoops_ASHH const *		_hoops_RRRGA,
	_hoops_ASHH const *		_hoops_ARRGA,
	bool							_hoops_PRRGA) {
	int								count = _hoops_RRRGA->count;
	DC_Point const *				points = _hoops_RRRGA->points;
	_hoops_GPPA const *	_hoops_GRCPR = _hoops_ARRGA->_hoops_GRCPR;
	DC_Point const *				_hoops_HRRGA = null;
	DC_Point alter *				_hoops_IRRGA = null;
	DC_Point alter *				_hoops_CRRGA = null;
	DC_Point alter *				buffer = null;
	int								_hoops_SRRGA = count + _hoops_ARRGA->count;
	int								_hoops_GARGA = 3 * _hoops_SRRGA;
	int								_hoops_RARGA = 0;
	_hoops_ASHH *			_hoops_AARGA = null;
	_hoops_ASHH **			_hoops_PARGA = &_hoops_AARGA;

	ALLOC_ARRAY(buffer, _hoops_GARGA, DC_Point);

	_hoops_HRRGA = points;
	_hoops_CRRGA = &buffer[2 * _hoops_SRRGA];

	while (_hoops_GRCPR) {
		DC_Point const		*prev, *point;
		float				_hoops_RCGGA, _hoops_CHGGA;
		int					_hoops_HARGA = 0;
		int					_hoops_IARGA = 0;
		bool				_hoops_CARGA;

		_hoops_IRRGA = &buffer[_hoops_RARGA * _hoops_SRRGA];

		prev = &_hoops_HRRGA[count-1];

		_hoops_RCGGA =
			_hoops_GRCPR->_hoops_SPPA.a * prev->x +
			 _hoops_GRCPR->_hoops_SPPA.b * prev->y +
			  _hoops_GRCPR->_hoops_SPPA.c * prev->z +
			   _hoops_GRCPR->_hoops_SPPA.d;

		_hoops_CARGA = (_hoops_RCGGA < 0.0f && Abs(_hoops_RCGGA) > 1.0e-4f);

		point = _hoops_HRRGA;

		for (int j=0; j<count; j++) {
			_hoops_CHGGA =	_hoops_GRCPR->_hoops_SPPA.a * point->x +
						 _hoops_GRCPR->_hoops_SPPA.b * point->y +
						  _hoops_GRCPR->_hoops_SPPA.c * point->z +
						   _hoops_GRCPR->_hoops_SPPA.d;


			if (_hoops_CHGGA < 0.0f) { // _hoops_ASSA
				if (!_hoops_CARGA && _hoops_CHGGA < -1.0e-9f) {
					// _hoops_SARGA _hoops_CPIC _hoops_GGR
					Vector		delta = *point - *prev;
					float		t = -_hoops_RCGGA / delta._hoops_SSRP (_hoops_GRCPR->_hoops_SPPA);

					_hoops_IRRGA[_hoops_HARGA++] = _hoops_CRRGA[_hoops_IARGA++] = *prev + t * delta;

					_hoops_CARGA = true;
				}

				// _hoops_PPR _hoops_PRIA _hoops_ASSA _hoops_PPSR
				_hoops_IRRGA[_hoops_HARGA++] = *point;
			}
			else {
				if (_hoops_CARGA  && Abs(_hoops_CHGGA) > 1.0e-4f) {
					// _hoops_SARGA _hoops_CPIC _hoops_GGSR
					Vector		delta = *point - *prev;
					float		t = -_hoops_RCGGA / delta._hoops_SSRP (_hoops_GRCPR->_hoops_SPPA);

					_hoops_CRRGA[_hoops_IARGA++] = _hoops_IRRGA[_hoops_HARGA++] = *prev + t * delta;

					_hoops_CARGA = false;
				}

				// _hoops_PPR _hoops_PRIA _hoops_SIPP _hoops_PPSR
				_hoops_CRRGA[_hoops_IARGA++] = *point;
			}

			_hoops_RCGGA = _hoops_CHGGA;
			prev = point++;
		}

		if (!_hoops_PRRGA && _hoops_IARGA > 0) {
			// _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_GPRGA _hoops_CCA _hoops_AGCR _hoops_SIPP _hoops_RSSA
			_hoops_ASHH *	_hoops_RPRGA;

			ZALLOC (_hoops_RPRGA, _hoops_ASHH);
			_hoops_ICAI(_hoops_RPRGA);
			*_hoops_PARGA = _hoops_RPRGA;
			_hoops_PARGA = &_hoops_RPRGA->next;

			_hoops_RPRGA->count = _hoops_IARGA;
			_hoops_APRGA(_hoops_CRRGA, _hoops_IARGA, Point, _hoops_RPRGA->points);
		}

		// _hoops_HRGR _hoops_SCH _hoops_HCR _hoops_PPRGA?
		if ((count = _hoops_HARGA) == 0)
			break;

		_hoops_HRRGA = _hoops_IRRGA;
		_hoops_RARGA = 1 - _hoops_RARGA;

		_hoops_GRCPR = _hoops_GRCPR->next;
	}


	if (_hoops_PRRGA && count > 0) {
		ZALLOC (_hoops_AARGA, _hoops_ASHH);
		_hoops_ICAI(_hoops_AARGA);
		_hoops_AARGA->count = count;
		_hoops_APRGA(_hoops_IRRGA, count, Point, _hoops_AARGA->points);
	}


	FREE_ARRAY(buffer, _hoops_GARGA, DC_Point);

	return _hoops_AARGA;
}


local void _hoops_HPRGA (
	Net_Rendition const &			nr,
	int								count,
	DC_Point const *				points,
	RGBAS32 const *					colors,
	RGBA const *					rgba_colors,
	_hoops_ARPA const *					planes,
	_hoops_RSSH const *				_hoops_CCHA,
	int								param_width,
	_hoops_SSIC					param_flags,
	_hoops_GPGGA					flags,
	_hoops_GPPA const **	_hoops_RPGGA,
	int								_hoops_IPRGA) {
	_hoops_GPPA const *	_hoops_GRCPR;
	int								_hoops_RARGA = 0;
	DC_Point const *				_hoops_CPRGA = null;
	DC_Point alter *				_hoops_SPRGA = null;
	DC_Point alter *				buffer = null;
	RGBAS32 const *					_hoops_GHRGA = null;
	RGBAS32 alter *					_hoops_AGRGA = null;
	RGBAS32 alter *					_hoops_HIAI = null;
	RGBA const *					_hoops_RHRGA = null;
	RGBA alter *					_hoops_AHRGA = null;
	RGBA alter *					_hoops_PHRGA = null;
	_hoops_ARPA const *					_hoops_HHRGA = null;
	_hoops_ARPA alter *					_hoops_ASGGA = null;
	_hoops_ARPA alter *					_hoops_IHRGA = null;
	_hoops_RSSH const *				_hoops_CHRGA = null;
	_hoops_RSSH alter *				_hoops_RSGGA = null;
	_hoops_RSSH alter *				_hoops_SHRGA = null;
	float const *					_hoops_GIRGA = null;
	float alter *					_hoops_RIRGA = null;
	float alter *					_hoops_AIRGA = null;
	bool							single = (BIT (flags, _hoops_RAIC) || !colors);
	int								_hoops_SRRGA = count + _hoops_IPRGA;
	int								_hoops_GARGA = 2 * _hoops_SRRGA;

	POOL_ALLOC_ARRAY(buffer, _hoops_GARGA, DC_Point, nr->_hoops_SRA->memory_pool);
	POOL_ALLOC_ARRAY(_hoops_HIAI, _hoops_GARGA, RGBAS32, nr->_hoops_SRA->memory_pool);
	if (rgba_colors)
		POOL_ALLOC_ARRAY(_hoops_PHRGA, _hoops_GARGA, RGBA, nr->_hoops_SRA->memory_pool);
	if (planes)
		POOL_ALLOC_ARRAY(_hoops_IHRGA, _hoops_GARGA, _hoops_ARPA, nr->_hoops_SRA->memory_pool);
	if (_hoops_CCHA && param_width > 0)
		POOL_ALLOC_ARRAY(_hoops_SHRGA, _hoops_GARGA*param_width, _hoops_RSSH, nr->_hoops_SRA->memory_pool);
	POOL_ALLOC_ARRAY(_hoops_AIRGA, _hoops_GARGA, float, nr->_hoops_SRA->memory_pool);

	_hoops_CPRGA = points;
	_hoops_GHRGA = colors;
	_hoops_RHRGA = rgba_colors;
	_hoops_HHRGA = planes;
	_hoops_CHRGA = _hoops_CCHA;

	_hoops_RIRGA = &_hoops_AIRGA[(1-_hoops_RARGA) * _hoops_SRRGA];
	if ((_hoops_CCHA||planes) &&
		BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
		_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
		_hoops_SGCC const &	mat = _hoops_IHCR->_hoops_CGCC;

		if (!BIT (_hoops_IHCR->flags, _hoops_IGCC))
			HD_Validate_World_To_Screen (nr);

		_hoops_RPRA const *			_hoops_APRA = mat->_hoops_PPRA()->data.elements;

		for (int j=0; j<count; j++) {
			Point					_hoops_SSGGA;
			float						_hoops_APCP;

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[j]);
			_hoops_SSGGA.x = _hoops_HPRA (_hoops_APRA, points[j]) * _hoops_APCP;
			_hoops_SSGGA.y = _hoops_IPRA (_hoops_APRA, points[j]) * _hoops_APCP;
			_hoops_SSGGA.z = _hoops_CPRA (_hoops_APRA, points[j]) * _hoops_APCP;
			_hoops_RIRGA[j] = _hoops_PHCP (mat->data.elements, _hoops_SSGGA);

			if (_hoops_RIRGA[j] < _hoops_IHCR->_hoops_CHCR)
				_hoops_RIRGA[j] = _hoops_IHCR->_hoops_CHCR;
		}
	}
	else {
		for (int j=0; j<count; j++)
			_hoops_RIRGA[j] = 1.0f;
	}
	_hoops_GIRGA = _hoops_RIRGA;

	while ((_hoops_GRCPR = *_hoops_RPGGA++) != null) {
		while (_hoops_GRCPR) {
			DC_Point const		*prev, *point;
			RGBAS32 const		*_hoops_PIRGA = null, *color;
			RGBA const			*_hoops_HIRGA = null, *_hoops_IIRGA;
			_hoops_ARPA const			*_hoops_CIRGA = null, *plane;
			_hoops_RSSH const		*_hoops_SIRGA = null, *param;
			float const			*_hoops_GCRGA = null, *w;
			float				_hoops_RCGGA, _hoops_CHGGA;
			int					_hoops_RCRGA = 0;
			bool				_hoops_CARGA;

			_hoops_SPRGA = &buffer[_hoops_RARGA * _hoops_SRRGA];
			_hoops_AGRGA = &_hoops_HIAI[_hoops_RARGA * _hoops_SRRGA];
			if (rgba_colors)
				_hoops_AHRGA = &_hoops_PHRGA[_hoops_RARGA * _hoops_SRRGA];
			if (planes)
				_hoops_ASGGA = &_hoops_IHRGA[_hoops_RARGA * _hoops_SRRGA];
			if (_hoops_CCHA)
				_hoops_RSGGA = &_hoops_SHRGA[_hoops_RARGA * param_width * _hoops_SRRGA];
			_hoops_RIRGA = &_hoops_AIRGA[_hoops_RARGA * _hoops_SRRGA];

			prev = &_hoops_CPRGA[count-1];
			if (!single)
				_hoops_PIRGA = &_hoops_GHRGA[count-1];
			else if (rgba_colors)
				_hoops_HIRGA = &_hoops_RHRGA[count-1];

			if (planes)
				_hoops_CIRGA = &_hoops_HHRGA[count-1];
			if (_hoops_CCHA)
				_hoops_SIRGA = &_hoops_CHRGA[(count-1)*param_width];
			_hoops_GCRGA = &_hoops_GIRGA[count-1];

			_hoops_RCGGA =
				_hoops_GRCPR->_hoops_SPPA.a * prev->x +
				 _hoops_GRCPR->_hoops_SPPA.b * prev->y +
				  _hoops_GRCPR->_hoops_SPPA.c * prev->z +
				   _hoops_GRCPR->_hoops_SPPA.d;

			_hoops_CARGA = (_hoops_RCGGA <= 0.0f);

			point = _hoops_CPRGA;
			color = _hoops_GHRGA;
			_hoops_IIRGA = _hoops_RHRGA;
			plane = _hoops_HHRGA;
			param = _hoops_CHRGA;
			w = _hoops_GIRGA;

			for (int j=0; j<count; j++) {
				_hoops_CHGGA =	_hoops_GRCPR->_hoops_SPPA.a * point->x +
							 _hoops_GRCPR->_hoops_SPPA.b * point->y +
							  _hoops_GRCPR->_hoops_SPPA.c * point->z +
							   _hoops_GRCPR->_hoops_SPPA.d;


				if (_hoops_CHGGA <= 0.0f) { /* _hoops_ASSA */
					if (!_hoops_CARGA && _hoops_CHGGA < -1.0e-9f) {
						/* _hoops_SARGA _hoops_CPIC _hoops_GGR */
						Vector		delta = *point - *prev;
						float		t = -_hoops_RCGGA / delta._hoops_SSRP (_hoops_GRCPR->_hoops_SPPA);

						_hoops_SPRGA[_hoops_RCRGA] = *prev + t * delta;

						if (rgba_colors)
							_hoops_ACRGA (*_hoops_HIRGA, *_hoops_IIRGA, t, _hoops_AHRGA[_hoops_RCRGA]);
						else if (!single)
							_hoops_PCRGA (*_hoops_PIRGA, *color, t, _hoops_AGRGA[_hoops_RCRGA]);

						if (planes)
							_hoops_RGRGA (*_hoops_CIRGA, *plane, t, _hoops_ASGGA[_hoops_RCRGA]);
						if (_hoops_CCHA)
							_hoops_GGRGA (nr, _hoops_SIRGA, param,
									t, &_hoops_RSGGA[_hoops_RCRGA*param_width], (*w)/(*_hoops_GCRGA), param_width);
						_hoops_RIRGA[_hoops_RCRGA] = *_hoops_GCRGA + t * (*w - *_hoops_GCRGA);

						_hoops_RCRGA++;
					}

					/* _hoops_PPR _hoops_PRIA _hoops_ASSA _hoops_PPSR */
					_hoops_SPRGA[_hoops_RCRGA] = *point;

					if (rgba_colors)
						_hoops_AHRGA[_hoops_RCRGA] = *_hoops_IIRGA;
					else
					if (!single)
						_hoops_AGRGA[_hoops_RCRGA] = *color;

					if (planes)
						_hoops_ASGGA[_hoops_RCRGA] = *plane;
					if (_hoops_CCHA)
						_hoops_AIGA (param, param_width, float, &_hoops_RSGGA[_hoops_RCRGA*param_width]);
					_hoops_RIRGA[_hoops_RCRGA] = *w;

					_hoops_RCRGA++;

					_hoops_CARGA = true;
				}
				else {
					if (_hoops_CARGA) {
						/* _hoops_SARGA _hoops_CPIC _hoops_GGSR */
						Vector		delta = *point - *prev;
						float		t = -_hoops_RCGGA / delta._hoops_SSRP (_hoops_GRCPR->_hoops_SPPA);

						_hoops_SPRGA[_hoops_RCRGA] = *prev+ t * delta;

						if (rgba_colors)
							_hoops_ACRGA (*_hoops_HIRGA, *_hoops_IIRGA, t, _hoops_AHRGA[_hoops_RCRGA]);
						else if (!single)
							_hoops_PCRGA (*_hoops_PIRGA, *color, t, _hoops_AGRGA[_hoops_RCRGA]);

						if (planes)
							_hoops_RGRGA (*_hoops_CIRGA, *plane, t, _hoops_ASGGA[_hoops_RCRGA]);
						if (_hoops_CCHA)
							_hoops_GGRGA (nr, _hoops_SIRGA, param,
									t, &_hoops_RSGGA[_hoops_RCRGA*param_width], (*w)/(*_hoops_GCRGA), param_width);
						_hoops_RIRGA[_hoops_RCRGA] = *_hoops_GCRGA + t * (*w - *_hoops_GCRGA);

						_hoops_RCRGA++;

						_hoops_CARGA = false;
					}
					else {
						/* _hoops_HGGC _hoops_SIPP, _hoops_ISAP _hoops_IS _hoops_AA */
					}
				}

				_hoops_RCGGA = _hoops_CHGGA;
				prev = point++;

				if (rgba_colors)
					_hoops_HIRGA = _hoops_IIRGA++;
				else if (!single)
					_hoops_PIRGA = color++;

				if (planes)
					_hoops_CIRGA = plane++;
				if (_hoops_CCHA) {
					_hoops_SIRGA = param;
					param += param_width;
				}
				_hoops_GCRGA = w++;
			}

			/* _hoops_HRGR _hoops_SCH _hoops_HCR _hoops_PPRGA */
			if ((count = _hoops_RCRGA) == 0)
				goto _hoops_RCCSR;

			_hoops_CPRGA = _hoops_SPRGA;
			_hoops_GHRGA = _hoops_AGRGA;
			_hoops_RHRGA = _hoops_AHRGA;
			_hoops_HHRGA = _hoops_ASGGA;
			_hoops_CHRGA = _hoops_RSGGA;
			_hoops_GIRGA = _hoops_RIRGA;

			_hoops_RARGA = 1 - _hoops_RARGA;

			_hoops_GRCPR = _hoops_GRCPR->next;
		}
	}

	/* _hoops_PA _hoops_IS _hoops_PGSA? */
	if (count >= 3) {
		if (count>3) {
			_hoops_SPRGA = &buffer[_hoops_RARGA * _hoops_SRRGA];
			_hoops_AGRGA = &_hoops_HIAI[_hoops_RARGA * _hoops_SRRGA];
			if (rgba_colors)
				_hoops_AHRGA = &_hoops_PHRGA[_hoops_RARGA * _hoops_SRRGA];
			if (planes)
				_hoops_ASGGA = &_hoops_IHRGA[_hoops_RARGA * _hoops_SRRGA];
			if (_hoops_CCHA)
				_hoops_RSGGA = &_hoops_SHRGA[_hoops_RARGA * param_width * _hoops_SRRGA];

			for (int i=0; i<count; i++) {
				int		index;

				if (i & 1)
					index = count-(i+1)/2;
				else
					index = i/2;

				_hoops_SPRGA[i] = _hoops_CPRGA[index];

				if (rgba_colors)
					_hoops_AHRGA[i] = _hoops_RHRGA[index];
				else if (!single)
					_hoops_AGRGA[i] = _hoops_GHRGA[index];

				if (planes)
					_hoops_ASGGA[i] = _hoops_HHRGA[index];
				if (_hoops_CCHA)
					_hoops_AIGA (&_hoops_CHRGA[index*param_width], param_width, float, &_hoops_RSGGA[i*param_width]);
			}

			_hoops_CPRGA = _hoops_SPRGA;
			_hoops_GHRGA = _hoops_AGRGA;
			_hoops_RHRGA = _hoops_AHRGA;
			_hoops_HHRGA = _hoops_ASGGA;
			_hoops_CHRGA = _hoops_RSGGA;
		}

		if (rgba_colors == null)
			_hoops_RHRGA = null;

		if (_hoops_CCHA) {
			if (planes == null)
				_hoops_HHRGA = null;

			_hoops_HCRGA (nr, count, _hoops_CPRGA, _hoops_RHRGA, _hoops_HHRGA,
											   _hoops_CHRGA, param_width, param_flags);
		}
		else if (planes)
			_hoops_ICRGA (nr, count, _hoops_CPRGA, _hoops_RHRGA, _hoops_HHRGA);
		else if (colors) {
			if (!single) {
				if (colors == null)
					_hoops_GHRGA = null;

				_hoops_CCRGA (nr, count, _hoops_CPRGA, _hoops_GHRGA);
			}
			else
				_hoops_SCRGA (nr, count, _hoops_CPRGA, colors, true);
		}
		else
			_hoops_GSRGA (nr, count, _hoops_CPRGA);
	}


_hoops_RCCSR:

	FREE_ARRAY(buffer, _hoops_GARGA, DC_Point);
	FREE_ARRAY(_hoops_HIAI, _hoops_GARGA, RGBAS32);
	if (rgba_colors)
		FREE_ARRAY(_hoops_PHRGA, _hoops_GARGA, RGBA);
	if (planes)
		FREE_ARRAY(_hoops_IHRGA, _hoops_GARGA, _hoops_ARPA);
	if (_hoops_CCHA && param_width > 0)
		FREE_ARRAY(_hoops_SHRGA, _hoops_GARGA*param_width, _hoops_RSSH);
	FREE_ARRAY(_hoops_AIRGA, _hoops_GARGA, float);
}

struct _hoops_RSRGA {
	Net_Rendition		nr;
	DC_Point const *	points;
	RGBAS32 const *		color;
	_hoops_GPGGA		flags;
};


local void _hoops_ASRGA (
	void *						info,
	int							_hoops_HAPH,
	Point const *				p1,
	Point const *				p2,
	Point const *				_hoops_IAPH,
	int							s1,
	int							s2,
	int							_hoops_CAPH,
	Intersection const * 		i1,
	Intersection const * 		i2,
	Intersection const * 		_hoops_SAPH) {
	_hoops_RSRGA const *	pt = (_hoops_RSRGA const *)info;
	DC_Point					points[3];

	UNREFERENCED(_hoops_HAPH);
	UNREFERENCED(s1);
	UNREFERENCED(s2);
	UNREFERENCED(_hoops_CAPH);
	UNREFERENCED(i1);
	UNREFERENCED(i2);
	UNREFERENCED(_hoops_SAPH);

	points[0].x = p1->x;
	points[0].y = p1->y;
	points[0].z = p1->z;
	points[1].x = p2->x;
	points[1].y = p2->y;
	points[1].z = p2->z;
	points[2].x = _hoops_IAPH->x;
	points[2].y = _hoops_IAPH->y;
	points[2].z = _hoops_IAPH->z;

	HD_Clip_DC_Face (pt->nr, 3, points, pt->color, pt->flags);
}

GLOBAL_FUNCTION void HD_Clip_DC_Face (
	Net_Rendition const &			inr,
	int								count,
	DC_Point const *				points,
	RGBAS32 const *					color,
	_hoops_GPGGA					flags) {
	Net_Rendition					nr = inr;
	_hoops_GPPA const *	_hoops_RPGGA[4];
	_hoops_GPPA const *	_hoops_APGGA = null;
	_hoops_IAPA const *		_hoops_CAPA = null;
	_hoops_ASHH const *		_hoops_PPGGA = null;
	int								_hoops_HPGGA = -1;
	int								_hoops_IPGGA = -1;
	_hoops_HHCR				_hoops_GGCC;
	int								_hoops_CPGGA = 0;
	int								_hoops_IPRGA = 0;

	if (count > 3 && BIT (nr->transform_rendition->heuristics, _hoops_CGCS)) {
		_hoops_RSRGA			pt;
		int alter *					face_list;

		pt.nr = nr;
		pt.points = points;
		pt.color = color;
		pt.flags = flags;

		POOL_ALLOC_ARRAY (face_list, count + 1, int, nr->_hoops_SRA->memory_pool);
		{
			int alter *				_hoops_PSRGA;
			int						vertex = 0;

			_hoops_PSRGA = face_list;

			*_hoops_PSRGA++ = count;
			do *_hoops_PSRGA++ = vertex;
			_hoops_RGGA (++vertex == count);
		}

		HI_Triangulate_Face_X ((Point const *)points, &_hoops_IRGA::_hoops_IGHH,
							 face_list, face_list + count + 1,
							 _hoops_ASRGA, (void *)&pt);

		FREE_ARRAY (face_list, count + 1, int);
		return;
	}


	_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

	if (BIT (flags, _hoops_RHGGA) && _hoops_GGCC->_hoops_HCHH) {
		if (_hoops_GGCC->_hoops_HCHH->_hoops_AHGGA == null)
			HD_Validate_Clipping_Rendition (_hoops_GGCC, _hoops_GGCC->_hoops_HCHH, flags);	// _hoops_RSIH _hoops_GGR _hoops_AGIR _hoops_SCH _hoops_SHPH _hoops_SGI

		if (_hoops_GGCC->_hoops_HCHH->_hoops_AHGGA->count == 0)	// _hoops_ISAP _hoops_PAH _hoops_SHH _hoops_CHCC
			return;
	}



	if (BIT (flags, _hoops_PHGGA) && !BIT (_hoops_GGCC->flags, _hoops_AIHS)) {
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_APGGA = HD_Create_Hard_Clip_Cuts (inr, &_hoops_GGCC->_hoops_AGAA, null, 0);
		_hoops_GGCC->flags |= _hoops_AIHS;
		_hoops_IPRGA += 4;
	}

	if (BIT (flags, _hoops_RHGGA) && _hoops_GGCC->_hoops_HCHH) {
		_hoops_IPGGA = _hoops_CPGGA;
		_hoops_IPRGA += _hoops_GGCC->_hoops_HCHH->_hoops_IPRGA;

		_hoops_PPGGA = _hoops_GGCC->_hoops_HCHH->_hoops_AHGGA;
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_PPGGA->_hoops_GRCPR;
		_hoops_PPGGA = _hoops_PPGGA->next;

		_hoops_GGCC->_hoops_HCHH = null;
	}

	if (BIT (flags, _hoops_GPHC) && BIT (_hoops_GGCC->flags, _hoops_CSP)) {
		_hoops_SSP const &		_hoops_GGH = inr->transform_rendition->_hoops_RGH;

		if (BIT (_hoops_GGCC->flags, _hoops_HHGGA))
			HD_Set_DC_Cutting_Planes (nr);

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			_hoops_IPRGA += _hoops_GGH->_hoops_CRH;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			_hoops_IPRGA += _hoops_GGH->_hoops_PGH;
		}

		_hoops_HPGGA = _hoops_CPGGA;
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_CAPA->_hoops_APPA;
		_hoops_CAPA = _hoops_CAPA->next;

		_hoops_GGCC->_hoops_RGH = null;
		_hoops_GGCC->flags &= ~_hoops_CSP;
	}

	_hoops_RPGGA[_hoops_CPGGA] = 0;

	_hoops_PCCAR {
		_hoops_PCCAR {
			_hoops_HPRGA (nr, count, points, color, 0, 0, 0, 0, 0, _hoops_RAIC, _hoops_RPGGA, _hoops_IPRGA);

			if (_hoops_CAPA == null)
				break;
			else {
				_hoops_RPGGA[_hoops_CPGGA-1] = _hoops_CAPA->_hoops_APPA;
				_hoops_CAPA = _hoops_CAPA->next;
			}
		}

		if (_hoops_PPGGA == null)
			break;
		else {
			_hoops_RPGGA[_hoops_IPGGA] = _hoops_PPGGA->_hoops_GRCPR;
			_hoops_PPGGA = _hoops_PPGGA->next;
		}
	}

	while (_hoops_APGGA) {
		_hoops_GPPA const *	c = _hoops_APGGA;

		_hoops_APGGA = _hoops_APGGA->next;
		FREE (c, _hoops_GPPA);
	}
}

GLOBAL_FUNCTION void HD_Validate_Clipping_Rendition (
	_hoops_HHCR alter &		_hoops_IHCR,
	_hoops_HSRGA alter &		_hoops_CRAIR) {
	_hoops_GPGGA					flags = 0;

	HD_Validate_Clipping_Rendition (_hoops_IHCR, _hoops_CRAIR, flags);
}

GLOBAL_FUNCTION void HD_Validate_Clipping_Rendition (
	_hoops_HHCR alter &		_hoops_IHCR,
	_hoops_HSRGA alter &		_hoops_CRAIR,
	_hoops_GPGGA alter &			flags) {

	if (_hoops_CRAIR->_hoops_AHGGA != null)
		return;

	if (_hoops_CRAIR->_hoops_PSHH->next == null && !BIT (_hoops_CRAIR->_hoops_PSHH->flags, _hoops_RHIH)) {
		// _hoops_IHGP "_hoops_RHGS _hoops_IAHA" _hoops_AGIR, _hoops_SAHR _hoops_HSSRR _hoops_SCH
		_hoops_CRAIR->_hoops_AHGGA = _hoops_CRAIR->_hoops_PSHH;
		_hoops_CAHS (_hoops_CRAIR->_hoops_AHGGA);
		// _hoops_PPR _hoops_HGCR _hoops_HRPP _hoops_IH _hoops_SGH
		_hoops_CRAIR->_hoops_IPRGA = _hoops_CRAIR->_hoops_AHGGA->count;
		HD_Validate_Clip_Half_Planes ((_hoops_ASHH alter *)_hoops_CRAIR->_hoops_AHGGA);
		return;
	}

	_hoops_ASHH const *		target = null;
	_hoops_ASHH const *		_hoops_ARRGA;

	if (BIT (flags, _hoops_PHGGA) && !BIT (_hoops_IHCR->flags, _hoops_AIHS)) {
		target = HD_Create_Hard_Clip_Region (&_hoops_IHCR->_hoops_AGAA, 0);
		_hoops_IHCR->flags |= _hoops_AIHS;
		flags &= ~_hoops_PHGGA;
	}
	else if (BIT (flags, _hoops_CGRGA) || _hoops_CRAIR->_hoops_ISRGA) {
		target = HD_Create_Hard_Clip_Region (&_hoops_IHCR->_hoops_AGAA, _hoops_SGRGA);
		flags &= ~_hoops_CGRGA;
	}

	if (target == null) {
		target = _hoops_CRAIR->_hoops_PSHH;
		_hoops_ARRGA = target->next;
		_hoops_CAHS (target);	// _hoops_SHI _hoops_SPRS-_hoops_CIH _hoops_RHSP _hoops_HAPR
	}
	else
		_hoops_ARRGA = _hoops_CRAIR->_hoops_PSHH;


	do {
		HD_Validate_Clip_Half_Planes ((_hoops_ASHH alter *)_hoops_ARRGA);

		if (!BIT (_hoops_ARRGA->flags, _hoops_RHIH)) {
			// _hoops_RGAR _hoops_SGCS _hoops_HIS _hoops_SGIP (_hoops_ACIPR _hoops_HSPH _hoops_PAR _hoops_SGCS _hoops_CSRGA), _hoops_HIS _hoops_HGGC _hoops_IRS _hoops_RSRA _hoops_SAAP _hoops_IS _hoops_SSRGA
			_hoops_ASHH *	result = _hoops_GRRGA (target, _hoops_ARRGA, true);

			if (result == null) {
				ZALLOC (_hoops_CRAIR->_hoops_AHGGA, _hoops_ASHH);		// _hoops_RHPA _hoops_GGAGA
				return;
			}

			HD_Free_Convex_Clip_Region (target);
			target = result;
		}
		else {
			// _hoops_SAAP _hoops_GHCA _hoops_SHH _hoops_IRS _hoops_HIGR _hoops_HII _hoops_PGHC _hoops_IIAP, _hoops_HIS _hoops_RRP _hoops_IS _hoops_HPPP _hoops_GRR, _hoops_IGGC _hoops_ACPP
			_hoops_ASHH const *		_hoops_RGAGA = target;
			_hoops_ASHH const *		current = target;
			_hoops_ASHH const **		_hoops_ASRGR = &target;

			target = null;

			do {
				// _hoops_SIGP: _hoops_RPP "_hoops_AGAGA (_hoops_SAAP, _hoops_PGAGA, _hoops_IHPR)" _hoops_HRGR _hoops_IRAP, _hoops_RH _hoops_PISH _hoops_PGAGA
				// _hoops_ASSP'_hoops_RA _hoops_CPSA _hoops_HAHA _hoops_RH _hoops_SAAP, _hoops_HIH _hoops_RH _hoops_PHSPR _hoops_SIAS _hoops_IHSA _hoops_GH _hoops_RH _hoops_ISPH
				// _hoops_CRGR _hoops_IRS _hoops_HGAGA _hoops_PGAP _hoops_HRGR _hoops_APGP _hoops_RH _hoops_PSHR, _hoops_HIS _hoops_SR _hoops_HHS _hoops_SGGC _hoops_RGR
				// _hoops_HPP _hoops_RIIA _hoops_GAGPR _hoops_HGIPR "_hoops_SCGR" _hoops_IAPR _hoops_IS _hoops_RH _hoops_CCAH _hoops_HIGR
				_hoops_ASHH const *	result = _hoops_GRRGA (current, _hoops_ARRGA, false);

				*_hoops_ASRGR = result;

				while ((result = *_hoops_ASRGR) != null)
					_hoops_ASRGR = (_hoops_ASHH const **)&result->next;
			} while ((current = current->next) != null);

			HD_Free_Convex_Clip_Region (_hoops_RGAGA);

			if (target == null) {
				ZALLOC (_hoops_CRAIR->_hoops_AHGGA, _hoops_ASHH);		// _hoops_RHPA _hoops_GGAGA
				return;
			}
		}
	} while ((_hoops_ARRGA = _hoops_ARRGA->next) != null);

	_hoops_CRAIR->_hoops_AHGGA = target;

	do {
		HD_Validate_Clip_Half_Planes ((_hoops_ASHH alter *)target);

		if (target->count > _hoops_CRAIR->_hoops_IPRGA)
			_hoops_CRAIR->_hoops_IPRGA = target->count;
	} while ((target = target->next) != null);
}



GLOBAL_FUNCTION void HD_Clip_DC_Polytriangle (
	Net_Rendition const &			inr,
	int								count,
	DC_Point const *				points,
	RGBAS32 const *					colors,
	RGBA const *					rgba_colors,
	_hoops_ARPA const *					planes,
	_hoops_RSSH const *				_hoops_CCHA,
	int								param_width,
	_hoops_SSIC					param_flags,
	_hoops_GPGGA					flags) {
	_hoops_GPPA const *	_hoops_RPGGA[4];
	Net_Rendition					nr = inr;
	_hoops_GPGGA					_hoops_IGAGA = flags & _hoops_CGAGA;
	_hoops_GPPA const *	_hoops_APGGA = null;
	_hoops_IAPA const *		_hoops_CAPA = null;
	_hoops_ASHH const *		_hoops_PPGGA = null;
	int								_hoops_HPGGA = -1;
	int								_hoops_IPGGA = -1;
	int								_hoops_HAHC;
	DC_Point const *				_hoops_SPGGA = points;
	RGBAS32 const *					_hoops_GHGGA = colors;
	RGBA const *					_hoops_PGRGA = rgba_colors;
	_hoops_ARPA const *					_hoops_HGRGA = planes;
	_hoops_RSSH const *				_hoops_IGRGA = _hoops_CCHA;
	_hoops_HHCR				_hoops_GGCC;
	int								_hoops_CPGGA = 0;
	int								_hoops_IPRGA = 0;
	int								_hoops_RRC;

	// _hoops_RIR-_hoops_SCPH _hoops_PSHA _hoops_GPP _hoops_CIIA _hoops_GACHR _hoops_RSRA _hoops_HAIR _hoops_IH _hoops_HISI _hoops_IIPR _hoops_SR _hoops_CAHP _hoops_HPGR _hoops_GRR _hoops_HSPH _hoops_HHSPR
	// _hoops_RIR-_hoops_GPHA _hoops_PSHA _hoops_GRS _hoops_SGAGA _hoops_RIR-_hoops_GPHA
	if (BIT (_hoops_IGAGA, _hoops_PAIC))
		_hoops_IGAGA = _hoops_RAIC;

	_hoops_GGCC = nr.Modify()->transform_rendition.Modify();


	if (BIT (flags, _hoops_RHGGA) && _hoops_GGCC->_hoops_HCHH) {
		if (_hoops_GGCC->_hoops_HCHH->_hoops_AHGGA == null)
			HD_Validate_Clipping_Rendition (_hoops_GGCC, _hoops_GGCC->_hoops_HCHH, flags);	// _hoops_RSIH _hoops_GGR _hoops_AGIR _hoops_SCH _hoops_SHPH _hoops_SGI

		if (_hoops_GGCC->_hoops_HCHH->_hoops_AHGGA->count == 0)	// _hoops_ISAP _hoops_PAH _hoops_SHH _hoops_CHCC
			return;
	}



	if (BIT (flags, _hoops_PHGGA) && !BIT (_hoops_GGCC->flags, _hoops_AIHS)) {
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_APGGA = HD_Create_Hard_Clip_Cuts (inr, &_hoops_GGCC->_hoops_AGAA, null, 0);
		_hoops_GGCC->flags |= _hoops_AIHS;
		_hoops_IPRGA += 4;
	}
	else if (BIT (flags, _hoops_CGRGA)) {
		Int_Rectangle				_hoops_GPHH = nr->_hoops_SAIR->_hoops_HHCAR;
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_APGGA = HD_Create_Hard_Clip_Cuts (inr, &_hoops_GPHH, null, 0);
		_hoops_IPRGA += 4;
	}
	else {
		_hoops_CPGGA = 0;
		_hoops_IPRGA = 0;
	}

	if (BIT (flags, _hoops_RHGGA) && _hoops_GGCC->_hoops_HCHH) {
		_hoops_IPGGA = _hoops_CPGGA;
		_hoops_IPRGA += _hoops_GGCC->_hoops_HCHH->_hoops_IPRGA;

		_hoops_PPGGA = _hoops_GGCC->_hoops_HCHH->_hoops_AHGGA;
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_PPGGA->_hoops_GRCPR;
		_hoops_PPGGA = _hoops_PPGGA->next;

		_hoops_GGCC->_hoops_HCHH = null;
	}

	if (BIT (flags, _hoops_GPHC) && BIT (_hoops_GGCC->flags, _hoops_CSP)) {
		_hoops_SSP const &		_hoops_GGH = inr->transform_rendition->_hoops_RGH;

		if (BIT (_hoops_GGCC->flags, _hoops_HHGGA))
			HD_Set_DC_Cutting_Planes (nr);

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			if (_hoops_GGH->_hoops_IRH == null)
				HD_Validate_Transparent_Cutting_Sets (_hoops_GGH);
			_hoops_CAPA = _hoops_GGH->_hoops_IRH;
			_hoops_IPRGA += _hoops_GGH->_hoops_CRH;
		}
		else {
			_hoops_CAPA = _hoops_GGH->_hoops_PHCA;
			_hoops_IPRGA += _hoops_GGH->_hoops_PGH;
		}

		_hoops_HPGGA = _hoops_CPGGA;
		_hoops_RPGGA[_hoops_CPGGA++] = _hoops_CAPA->_hoops_APPA;
		_hoops_CAPA = _hoops_CAPA->next;

		_hoops_GGCC->_hoops_RGH = null;
		_hoops_GGCC->flags &= ~_hoops_CSP;
	}

	_hoops_RPGGA[_hoops_CPGGA] = 0;


	_hoops_ICHC (count, _hoops_RRC, 3);
	_hoops_HAHC = count;


	_hoops_PCCAR {
		_hoops_PCCAR {
			while (count-- > 0) {
				_hoops_HPRGA (nr, 3, points, colors, rgba_colors, planes,
						   _hoops_CCHA, param_width, param_flags,
						   _hoops_IGAGA, _hoops_RPGGA, _hoops_IPRGA);

				points += _hoops_RRC;
				if (colors) {
					if (BIT (flags, _hoops_AAIC))
						colors += _hoops_RRC;
					else if (BIT (flags, _hoops_PAIC))
						colors++;
					/*_hoops_PIGGA _hoops_AA _hoops_ISAP */
				}
				else if (rgba_colors)
					rgba_colors += _hoops_RRC;

				if (planes)
					planes += _hoops_RRC;
				if (_hoops_CCHA)
					_hoops_CCHA += param_width*_hoops_RRC;
			}

			if (_hoops_CAPA == null)
				break;
			else {
				_hoops_RPGGA[_hoops_HPGGA] = _hoops_CAPA->_hoops_APPA;
				_hoops_CAPA = _hoops_CAPA->next;

				count = _hoops_HAHC;
				points = _hoops_SPGGA;
				colors = _hoops_GHGGA;
				rgba_colors = _hoops_PGRGA;
				planes = _hoops_HGRGA;
				_hoops_CCHA = _hoops_IGRGA;
			}
		}

		if (_hoops_PPGGA == null)
			break;
		else {
			_hoops_RPGGA[_hoops_IPGGA] = _hoops_PPGGA->_hoops_GRCPR;
			_hoops_PPGGA = _hoops_PPGGA->next;

			count = _hoops_HAHC;
			points = _hoops_SPGGA;
			colors = _hoops_GHGGA;
			rgba_colors = _hoops_PGRGA;
			planes = _hoops_HGRGA;
			_hoops_CCHA = _hoops_IGRGA;
		}
	}


	while (_hoops_APGGA) {
		_hoops_GPPA const *	c = _hoops_APGGA;

		_hoops_APGGA = _hoops_APGGA->next;
		FREE (c, _hoops_GPPA);
	}
}



/*_hoops_GRAGA-_hoops_RRAGA _hoops_HSSP _hoops_CIHH*/

#define _hoops_ARAGA (0.001f)

#define _hoops_PRAGA(p) { \
		_hoops_HRAGA[*count].x = (p)->x; \
		_hoops_HRAGA[*count].y = (p)->y; \
		_hoops_HRAGA[*count].z = (p)->z; \
		(*count)++; }


#define _hoops_IRAGA() { \
		float _hoops_HGRCR = 0.0f; \
		if ((_hoops_CRAGA->x - _hoops_ASPS->x) > _hoops_ARAGA || \
			(_hoops_CRAGA->x - _hoops_ASPS->x) < -_hoops_ARAGA) \
			if ((_hoops_CRAGA->y - _hoops_ASPS->y) > _hoops_ARAGA || \
				(_hoops_CRAGA->y - _hoops_ASPS->y) < -_hoops_ARAGA) \
				_hoops_HGRCR = (_hoops_CRAGA->y - _hoops_ASPS->y) / (_hoops_CRAGA->x - _hoops_ASPS->x); \
		_hoops_HRAGA[*count].x = _hoops_GPHH; \
		_hoops_HRAGA[*count].y = _hoops_ASPS->y + (_hoops_GPHH - _hoops_ASPS->x) * _hoops_HGRCR; \
		_hoops_HGRCR = 0.0f; \
		if ((_hoops_CRAGA->x - _hoops_ASPS->x) > _hoops_ARAGA || \
			(_hoops_CRAGA->x - _hoops_ASPS->x) < -_hoops_ARAGA) \
			if ((_hoops_CRAGA->z - _hoops_ASPS->z) > _hoops_ARAGA || \
				(_hoops_CRAGA->z - _hoops_ASPS->z) < -_hoops_ARAGA) \
				_hoops_HGRCR = (_hoops_CRAGA->z - _hoops_ASPS->z) / (_hoops_CRAGA->x - _hoops_ASPS->x); \
		_hoops_HRAGA[*count].z = _hoops_ASPS->z + (_hoops_GPHH - _hoops_ASPS->x) * _hoops_HGRCR; \
		(*count)++; }

#define _hoops_SRAGA() { \
		float _hoops_HGRCR = 0.0f; \
		_hoops_HRAGA[*count].x = _hoops_ASPS->x; \
		if ((_hoops_CRAGA->x - _hoops_ASPS->x) > _hoops_ARAGA || \
			(_hoops_CRAGA->x - _hoops_ASPS->x) < -_hoops_ARAGA) \
			if ((_hoops_CRAGA->y - _hoops_ASPS->y) > _hoops_ARAGA || \
				(_hoops_CRAGA->y - _hoops_ASPS->y) < -_hoops_ARAGA) { \
				_hoops_HGRCR = (_hoops_CRAGA->y - _hoops_ASPS->y) / (_hoops_CRAGA->x - _hoops_ASPS->x); \
				_hoops_HRAGA[*count].x += (_hoops_GPHH - _hoops_ASPS->y) / _hoops_HGRCR; \
				} \
		_hoops_HRAGA[*count].y = _hoops_GPHH; \
		_hoops_HGRCR = 0.0f; \
		if ((_hoops_CRAGA->y - _hoops_ASPS->y) > _hoops_ARAGA || \
			(_hoops_CRAGA->y - _hoops_ASPS->y) < -_hoops_ARAGA) \
			if ((_hoops_CRAGA->z - _hoops_ASPS->z) > _hoops_ARAGA || \
				(_hoops_CRAGA->z - _hoops_ASPS->z) < -_hoops_ARAGA) \
				_hoops_HGRCR = (_hoops_CRAGA->z - _hoops_ASPS->z) / (_hoops_CRAGA->y - _hoops_ASPS->y); \
		_hoops_HRAGA[*count].z = _hoops_ASPS->z + (_hoops_GPHH - _hoops_ASPS->y) * _hoops_HGRCR; \
		(*count)++; }

local void _hoops_GAAGA (DC_Point const * _hoops_CRAGA,
			 DC_Point const * _hoops_ASPS,
		int * count, DC_Point * _hoops_HRAGA, float _hoops_GPHH) {

	if (_hoops_CRAGA->x < _hoops_GPHH) {			/*_hoops_SIPP*/
		if (_hoops_ASPS->x < _hoops_GPHH)		/*_hoops_SIPP*/
			return;
		else {							/*_hoops_ASSA*/
			_hoops_IRAGA();
			_hoops_PRAGA(_hoops_ASPS);
		}
	}
	else {								/*_hoops_ASSA*/
		if (*count == 0)
			_hoops_PRAGA(_hoops_CRAGA);
		if (_hoops_ASPS->x < _hoops_GPHH) {		/*_hoops_SIPP*/
			_hoops_IRAGA();
		}
		else {							/*_hoops_ASSA*/
			_hoops_PRAGA(_hoops_ASPS);
		}
	}
}

local void _hoops_RAAGA (DC_Point const * _hoops_CRAGA,
			  DC_Point const * _hoops_ASPS,
		int * count,DC_Point * _hoops_HRAGA,float _hoops_GPHH) {

	if (_hoops_CRAGA->x > _hoops_GPHH) {			/*_hoops_SIPP*/
		if (_hoops_ASPS->x > _hoops_GPHH)		/*_hoops_SIPP*/
			return;
		else {							/*_hoops_ASSA*/
			_hoops_IRAGA();
			_hoops_PRAGA(_hoops_ASPS);
		}
	}
	else {								/*_hoops_ASSA*/
		if (*count == 0)
			_hoops_PRAGA(_hoops_CRAGA);
		if (_hoops_ASPS->x > _hoops_GPHH) {		/*_hoops_SIPP*/
			_hoops_IRAGA();
		}
		else {							/*_hoops_ASSA*/
			_hoops_PRAGA(_hoops_ASPS);
		}
	}
}

local void _hoops_AAAGA (DC_Point const * _hoops_CRAGA,
			DC_Point const * _hoops_ASPS,
		int * count,DC_Point * _hoops_HRAGA,float _hoops_GPHH) {

	if (_hoops_CRAGA->y > _hoops_GPHH) {			/*_hoops_SIPP*/
		if (_hoops_ASPS->y > _hoops_GPHH)		/*_hoops_SIPP*/
			return;
		else {							/*_hoops_ASSA*/
			_hoops_SRAGA();
			_hoops_PRAGA(_hoops_ASPS);
		}
	}
	else {								/*_hoops_ASSA*/
		if (*count == 0)
			_hoops_PRAGA(_hoops_CRAGA);
		if (_hoops_ASPS->y > _hoops_GPHH) {		/*_hoops_SIPP*/
			_hoops_SRAGA();
		}
		else {							/*_hoops_ASSA*/
			_hoops_PRAGA(_hoops_ASPS);
		}
	}
}

local void _hoops_PAAGA (DC_Point const * _hoops_CRAGA,
			   DC_Point const * _hoops_ASPS,
		int * count,DC_Point * _hoops_HRAGA,float _hoops_GPHH) {

	if (_hoops_CRAGA->y < _hoops_GPHH) {			/*_hoops_SIPP*/
		if (_hoops_ASPS->y < _hoops_GPHH)		/*_hoops_SIPP*/
			return;
		else {							/*_hoops_ASSA*/
			_hoops_SRAGA();
			_hoops_PRAGA(_hoops_ASPS);
		}
	}
	else {								/*_hoops_ASSA*/
		if (*count == 0)
			_hoops_PRAGA(_hoops_CRAGA);
		if (_hoops_ASPS->y < _hoops_GPHH) {		/*_hoops_SIPP*/
			_hoops_SRAGA();
		}
		else {							/*_hoops_ASSA*/
			_hoops_PRAGA(_hoops_ASPS);
		}
	}
}

#define _hoops_HAAGA 32

GLOBAL_FUNCTION void HD_Clip_Poly (
	Int_Rectangle const *		rect,
	int							_hoops_IAAGA,
	DC_Point const *			in_points,
	int alter *					_hoops_CAAGA,
	DC_Point alter *			out_points,
	bool						close) {
	DC_Point					_hoops_SAAGA[2][_hoops_HAAGA*2];
	DC_Point *					points[2];
	int							count[2];
	int							i;

	/*_hoops_RPP _hoops_SR _hoops_HS _hoops_IRS _hoops_CHPP _hoops_PHI _hoops_IIGR _hoops_RSSA*/
	/*_hoops_SR _hoops_SIAS _hoops_RRP _hoops_HHH _hoops_RRI _hoops_PPGS _hoops_HIS _hoops_IPGIR _hoops_ISPR*/
	if (_hoops_IAAGA <= _hoops_HAAGA) {
		points[0] = _hoops_SAAGA[0];
		points[1] = _hoops_SAAGA[1];
	}
	else {
		ALLOC_ARRAY (points[0], _hoops_IAAGA*2 , DC_Point);
		ALLOC_ARRAY (points[1], _hoops_IAAGA*2 , DC_Point);
	}

	/*_hoops_RAAP*/
	count[0] = 0;

	for (i = 0; i < _hoops_IAAGA -1; i++)
		_hoops_GAAGA (&in_points[i], &in_points[i + 1],
				   &count[0], points[0], (float)rect->left);

	if (close)
		_hoops_GAAGA (&in_points[_hoops_IAAGA - 1], &in_points[0],
			   &count[0], points[0], (float)rect->left);

	/*_hoops_RPHR*/
	count[1] = 0;

	for (i = 0; i < count[0] - 1; i++)
		_hoops_RAAGA (&points[0][i], &points[0][i + 1],
					&count[1], points[1], (float)rect->right);

	if (close)
		_hoops_RAAGA (&points[0][count[0] -1], &points[0][0],
				&count[1], points[1], (float)rect->right);

	/*_hoops_SCIA*/
	count[0] = 0;

	for (i = 0; i < count[1] - 1; i++)
		_hoops_AAAGA (&points[1][i], &points[1][i+1],
				  &count[0], points[0], (float)rect->top);

	if (close)
		_hoops_AAAGA (&points[1][count[1] - 1], &points[1][0],
			  &count[0], points[0], (float)rect->top);

	/*_hoops_PRPC*/
	*_hoops_CAAGA = 0;

	for (i = 0; i < count[0] - 1; i++)
		_hoops_PAAGA (&points[0][i], &points[0][i + 1],
					 _hoops_CAAGA, out_points, (float)rect->bottom);

	if (close)
		_hoops_PAAGA (&points[0][count[0] - 1], &points[0][0],
				 _hoops_CAAGA, out_points, (float)rect->bottom);

	/*_hoops_RPP _hoops_SR _hoops_SIGR _hoops_IHH _hoops_PPGS _hoops_CIH _hoops_SCH*/
	if (_hoops_IAAGA > _hoops_HAAGA) {
		FREE_ARRAY (points[0], _hoops_IAAGA*2 , DC_Point);
		FREE_ARRAY (points[1], _hoops_IAAGA*2 , DC_Point);
	}
}


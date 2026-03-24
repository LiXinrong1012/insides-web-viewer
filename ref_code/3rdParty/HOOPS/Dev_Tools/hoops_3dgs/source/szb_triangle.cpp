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
 * $Id: obf_tmp.txt 1.33 2010-08-11 02:53:57 covey Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "hd_proto.h"
#include "span.h"


GLOBAL_FUNCTION void HD_SZB_DC_Polytriangle (
	Net_Rendition const & 		nr,
	int							count,
	DC_Point const *			points) {
	_hoops_HCSIR alter *	_hoops_ICSIR;
	int							_hoops_RRC;

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
		_hoops_PACIR const *	_hoops_GPHH = &nr->_hoops_SAIR->_hoops_HHCAR;
		DC_Point const *			p = points;
		int							_hoops_GPIGR = Abs (count);

		while (_hoops_GPIGR-- > 0) {
		
			if (!_hoops_GPHH->_hoops_HPCIR(*p)) {
				Net_Rendition		_hoops_PIRCP = nr.Copy();
				_hoops_PIRCP->transform_rendition.Modify()->flags |= _hoops_AIHS;
				HD_Clip_DC_Polytriangle (_hoops_PIRCP, count, points, 0,0,0,0,0,0, _hoops_CGRGA | _hoops_GPHC);
				return;
			}

			++p;
		}
	}
	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0,0,0,0,0,0, _hoops_GPHC);
		return;
	}


	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICSIR->input.color = nr->_hoops_IHA->color;

	_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.test = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.update = _hoops_GPSCP;
	if (BIT(nr->transform_rendition->flags, _hoops_PASP)) {
		_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP		|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.test				|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.update				|= _hoops_IRHSP;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_ICSIR->input.vertex[0].point = &points[0];
		_hoops_ICSIR->input.vertex[1].point = &points[1];
		_hoops_ICSIR->input.vertex[2].point = &points[2];

		HD_SZB_Process_Triangle (nr);

		points += _hoops_RRC;
	}
}

GLOBAL_FUNCTION void HD_SZB_DC_Colorized_Polytris (
	Net_Rendition const & 		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						single) {
	_hoops_HCSIR alter *	_hoops_ICSIR;
	int							_hoops_RRC;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0,0,0,0,0,
								 _hoops_GPHC | (single ? _hoops_RAIC : _hoops_PAIC));
		return;
	}

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.test = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.update = _hoops_GPSCP;
	if (BIT(nr->transform_rendition->flags, _hoops_PASP)) {
		_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP		|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.test				|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.update				|= _hoops_IRHSP;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_ICSIR->input.vertex[0].point = &points[0];
		_hoops_ICSIR->input.vertex[1].point = &points[1];
		_hoops_ICSIR->input.vertex[2].point = &points[2];
		_hoops_ICSIR->input.color = *colors;

		HD_SZB_Process_Triangle (nr);

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
}

GLOBAL_FUNCTION void HD_SZB_DC_Gouraud_Polytris (
	Net_Rendition const & 		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors) {
	_hoops_HCSIR alter *	_hoops_ICSIR;
	int							_hoops_RRC;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0,0,0,0,0,
								 _hoops_GPHC | _hoops_AAIC);
		return;
	}

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP = _hoops_RAHSP;
	_hoops_ICSIR->input._hoops_AIPRA.test = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.update = _hoops_GPSCP;
	if (BIT(nr->transform_rendition->flags, _hoops_PASP)) {
		_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP		|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.test				|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.update				|= _hoops_IRHSP;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_ICSIR->input.vertex[0].point = &points[0];
		_hoops_ICSIR->input.vertex[1].point = &points[1];
		_hoops_ICSIR->input.vertex[2].point = &points[2];
		_hoops_ICSIR->input.vertex[0].color = &colors[0];
		_hoops_ICSIR->input.vertex[1].color = &colors[1];
		_hoops_ICSIR->input.vertex[2].color = &colors[2];

		HD_SZB_Process_Triangle (nr);

		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
}

GLOBAL_FUNCTION void HD_SZB_DC_Phong_Polytris (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBA const					*colors,
	_hoops_ARPA const					*planes) {

	UNREFERENCED (colors);
	UNREFERENCED (planes);

	HD_SZB_DC_Polytriangle (nr, count, points);
}

GLOBAL_FUNCTION void HD_SZB_DC_Textured_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	_hoops_SSIC				param_flags) {

	UNREFERENCED (colors);
	UNREFERENCED (planes);
	UNREFERENCED (params);
	UNREFERENCED (param_width);
	UNREFERENCED (param_flags);

	HD_SZB_DC_Polytriangle (nr, count, points);
}




GLOBAL_FUNCTION void HD_SZB_Process_Triangle (
	Net_Rendition const &		nr) {
#ifndef _hoops_GCSIR
	_hoops_HCSIR alter *	_hoops_ICSIR;
	_hoops_PGHSP const *			v[3];
	_hoops_RCSIR					pts[3];
	Int_Rectangle				_hoops_GPHH;
	_hoops_ISGCR					_hoops_CSGCR, _hoops_SSGCR;
	int							test, update, _hoops_PPCCP;

	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	ZERO_STRUCT (&_hoops_CSGCR, _hoops_ISGCR);
	ZERO_STRUCT (&_hoops_SSGCR, _hoops_ISGCR);

#if 0	/* _hoops_SIGP */
	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Gouraud_Tri (nr, _hoops_CGICP, _hoops_SRRGGR);
		return;
	}

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Gouraud_Triangle (nr, _hoops_CGICP, _hoops_SRRGGR);
		return;
	}
#endif

#if 0
#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	test = _hoops_ICSIR->input._hoops_AIPRA.test & ~_hoops_ICSIR->input._hoops_SASCP.test | _hoops_ICSIR->input.required.test;
	update = _hoops_ICSIR->input._hoops_AIPRA.update & ~_hoops_ICSIR->input._hoops_SASCP.update | _hoops_ICSIR->input.required.update;
	_hoops_PPCCP = _hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP & ~_hoops_ICSIR->input._hoops_SASCP._hoops_PPCCP | _hoops_ICSIR->input.required._hoops_PPCCP;

	_hoops_GPHH.left	= _hoops_IHCR->_hoops_AGAA.left	- _hoops_ICSIR->offset.x;
	_hoops_GPHH.right	= _hoops_IHCR->_hoops_AGAA.right	- _hoops_ICSIR->offset.x;
	_hoops_GPHH.bottom = _hoops_IHCR->_hoops_AGAA.bottom - _hoops_ICSIR->offset.y;
	_hoops_GPHH.top	= _hoops_IHCR->_hoops_AGAA.top	- _hoops_ICSIR->offset.y;


	/* _hoops_GHIS _hoops_GIHA */
	v[0] = &_hoops_ICSIR->input.vertex[0];
	v[1] = &_hoops_ICSIR->input.vertex[1];
	v[2] = &_hoops_ICSIR->input.vertex[2];

	if (v[0]->point->y <= v[1]->point->y) {
		if (v[1]->point->y <= v[2]->point->y) {
			/* _hoops_AIAH _hoops_GGR _hoops_AGR */
		}
		else if (v[0]->point->y <= v[2]->point->y) {
			/* _hoops_HPPC[0] : [0] */
			v[1] = &_hoops_ICSIR->input.vertex[2];
			v[2] = &_hoops_ICSIR->input.vertex[1];
		}
		else {
			v[0] = &_hoops_ICSIR->input.vertex[2];
			v[1] = &_hoops_ICSIR->input.vertex[0];
			v[2] = &_hoops_ICSIR->input.vertex[1];
		}
	}
	else {
		if (v[0]->point->y <= v[2]->point->y) {
			v[0] = &_hoops_ICSIR->input.vertex[1];
			v[1] = &_hoops_ICSIR->input.vertex[0];
			/* _hoops_HPPC[2] : [2] */
		}
		else if (v[1]->point->y <= v[2]->point->y) {
			v[0] = &_hoops_ICSIR->input.vertex[1];
			v[1] = &_hoops_ICSIR->input.vertex[2];
			v[2] = &_hoops_ICSIR->input.vertex[0];
		}
		else {
			v[0] = &_hoops_ICSIR->input.vertex[2];
			/* _hoops_HPPC[1] : [1] */
			v[2] = &_hoops_ICSIR->input.vertex[0];
		}
	}

	pts[0].y = (int)v[0]->point->y - _hoops_ICSIR->offset.y;
	pts[1].y = (int)v[1]->point->y - _hoops_ICSIR->offset.y;
	pts[2].y = (int)v[2]->point->y - _hoops_ICSIR->offset.y;

	if (pts[0].y > _hoops_GPHH.top || pts[2].y < _hoops_GPHH.bottom)
		return;


	if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
		_hoops_ISGCR alter			*left;
		_hoops_ISGCR alter			*right;
		_hoops_RAAH alter * const			*_hoops_PCSIR = null;
		RGBAS32 alter * const		*_hoops_ACSIR = null;
		unsigned char alter * const		*_hoops_RARGGR = null;
		int								y = pts[0].y;
		int								_hoops_AASIC;
		/* _hoops_RGR _hoops_HRGR _hoops_RGIRR _hoops_ARI _hoops_HIS _hoops_SR _hoops_PAH _hoops_HSPC _hoops_ARR, _hoops_IAII _hoops_SCH'_hoops_GHGP _hoops_SHH _hoops_CCA _hoops_SISR & _hoops_CAASH _hoops_CAPP */
		_hoops_ISGCR					span;
		int								offset;

		ZERO_STRUCT (&span, _hoops_ISGCR);


		if (_hoops_ICSIR->_hoops_HCSCP != null)
			_hoops_RARGGR = &((unsigned char alter * alter *)
						 _hoops_ICSIR->_hoops_HCSCP->_hoops_RCPIR)[y];
		if (_hoops_ICSIR->depth_buffer != null)
			_hoops_PCSIR = &((_hoops_RAAH alter * alter *)
						 _hoops_ICSIR->depth_buffer->_hoops_RCPIR)[y];
		if (_hoops_ICSIR->_hoops_HIAI != null)
			_hoops_ACSIR = &((RGBAS32 alter * alter *)
						 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[y];


		offset = (int)((nr->transform_rendition->_hoops_CHIH +
						nr->transform_rendition->_hoops_SHIH) *
					   _hoops_ISSIR(nr->transform_rendition));
		pts[0].x = (int)v[0]->point->x - _hoops_ICSIR->offset.x;
		pts[0].z = (int)v[0]->point->z + offset;
		pts[1].x = (int)v[1]->point->x - _hoops_ICSIR->offset.x;
		pts[1].z = (int)v[1]->point->z + offset;
		pts[2].x = (int)v[2]->point->x - _hoops_ICSIR->offset.x;
		pts[2].z = (int)v[2]->point->z + offset;

		_hoops_IAGCR (_hoops_CSGCR.bx, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
		if (_hoops_PPCCP != 0) {
			if (BIT (_hoops_PPCCP, _hoops_IRHSP)) {
				_hoops_IAGCR (_hoops_CSGCR.bz, pts[0].z, pts[2].z, _hoops_CSGCR._hoops_CRRAR);
			}
			if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
				RGBAS32 const *		_hoops_AGCII = v[0]->color;
				RGBAS32 const *		_hoops_PIGCR = v[2]->color;

				_hoops_HAGCR (_hoops_CSGCR.r, _hoops_AGCII->r, _hoops_PIGCR->r, _hoops_CSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_CSGCR.g, _hoops_AGCII->g, _hoops_PIGCR->g, _hoops_CSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_CSGCR.b, _hoops_AGCII->b, _hoops_PIGCR->b, _hoops_CSGCR._hoops_CRRAR);
			}
		}


		for (_hoops_AASIC=0; _hoops_AASIC<2; _hoops_AASIC++) {
			if ((_hoops_SSGCR._hoops_CRRAR = pts[_hoops_AASIC+1].y - pts[_hoops_AASIC+0].y) > 0) {
				_hoops_IAGCR (_hoops_SSGCR.bx, pts[_hoops_AASIC+0].x, pts[_hoops_AASIC+1].x, _hoops_SSGCR._hoops_CRRAR);
				if (_hoops_PPCCP != 0) {
					if (BIT (_hoops_PPCCP, _hoops_IRHSP)) {
						_hoops_IAGCR (_hoops_SSGCR.bz, pts[_hoops_AASIC+0].z, pts[_hoops_AASIC+1].z, _hoops_SSGCR._hoops_CRRAR);
					}
					if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
						RGBAS32 const * _hoops_PRIAA = v[_hoops_AASIC+0]->color;
						RGBAS32 const * _hoops_RCHIR = v[_hoops_AASIC+1]->color;

						_hoops_HAGCR (_hoops_SSGCR.r, _hoops_PRIAA->r, _hoops_RCHIR->r, _hoops_SSGCR._hoops_CRRAR);
						_hoops_HAGCR (_hoops_SSGCR.g, _hoops_PRIAA->g, _hoops_RCHIR->g, _hoops_SSGCR._hoops_CRRAR);
						_hoops_HAGCR (_hoops_SSGCR.b, _hoops_PRIAA->b, _hoops_RCHIR->b, _hoops_SSGCR._hoops_CRRAR);
					}
				}

				if (_hoops_AASIC == 0) {
					if (_hoops_SSGCR.bx._hoops_HGRCR.simple <= _hoops_CSGCR.bx._hoops_HGRCR.simple) {
						left = &_hoops_SSGCR; right = &_hoops_CSGCR;
					}
					else {
						left = &_hoops_CSGCR; right = &_hoops_SSGCR;
					}
				}
				else {
					if (_hoops_SSGCR.bx._hoops_HAGR._hoops_SAGCR < _hoops_CSGCR.bx._hoops_HAGR._hoops_SAGCR) {
						left = &_hoops_SSGCR; right = &_hoops_CSGCR;
					}
					else {
						left = &_hoops_CSGCR; right = &_hoops_SSGCR;
					}
				}

				/* _hoops_IRPHR _hoops_HSPH */
				if (y < _hoops_GPHH.bottom) {
					/* _hoops_IHIS _hoops_GH _hoops_IS _hoops_PRPC _hoops_PAR _hoops_RHIR _hoops_RPCAI._hoops_SRRAA */
					int				_hoops_HGCGP;

					if (y + _hoops_SSGCR._hoops_CRRAR > _hoops_GPHH.bottom)
						_hoops_HGCGP = _hoops_GPHH.bottom - y;
					else
						_hoops_HGCGP = _hoops_SSGCR._hoops_CRRAR;

					y += _hoops_HGCGP;
					_hoops_SSGCR._hoops_CRRAR -= _hoops_HGCGP;
					_hoops_CIHHS (_hoops_CSGCR.bx, _hoops_HGCGP);
					_hoops_CIHHS (_hoops_SSGCR.bx, _hoops_HGCGP);
					if (_hoops_PPCCP != 0) {
						if (BIT (_hoops_PPCCP, _hoops_IRHSP)) {
							_hoops_CIHHS (_hoops_CSGCR.bz, _hoops_HGCGP);
							_hoops_CIHHS (_hoops_SSGCR.bz, _hoops_HGCGP);
						}
						if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
							_hoops_RHHHS (_hoops_CSGCR.r, _hoops_HGCGP);
							_hoops_RHHHS (_hoops_CSGCR.g, _hoops_HGCGP);
							_hoops_RHHHS (_hoops_CSGCR.b, _hoops_HGCGP);
							_hoops_RHHHS (_hoops_SSGCR.r, _hoops_HGCGP);
							_hoops_RHHHS (_hoops_SSGCR.g, _hoops_HGCGP);
							_hoops_RHHHS (_hoops_SSGCR.b, _hoops_HGCGP);
						}
					}

					if (_hoops_RARGGR != null)
						_hoops_RARGGR += _hoops_HGCGP;
					if (_hoops_PCSIR != null)
						_hoops_PCSIR += _hoops_HGCGP;
					if (_hoops_ACSIR != null)
						_hoops_ACSIR += _hoops_HGCGP;
				}
				if (y + _hoops_SSGCR._hoops_CRRAR > _hoops_GPHH.top) {
					/* _hoops_PSRAR _hoops_RPCAI._hoops_SRRAA */

					_hoops_SSGCR._hoops_CRRAR = _hoops_GPHH.top+1 - y;
				}

				/* _hoops_HPPP _hoops_PA _hoops_HHRPA */
				if (_hoops_SSGCR._hoops_CRRAR > 0) _hoops_PCCAR {
					unsigned int					x;
					int								dx;

					x = left->bx._hoops_HAGR._hoops_SAGCR;
					dx = right->bx._hoops_HAGR._hoops_SAGCR - x;


					if (right->bx._hoops_HAGR._hoops_SAGCR < _hoops_GPHH.left ||
						(int)x > _hoops_GPHH.right) {
						/* _hoops_CCGC _hoops_SACH */
						dx = 0;
					}
					else {
						if (_hoops_PPCCP != 0) {
							if (BIT (_hoops_PPCCP, _hoops_IRHSP)) {
								_hoops_IAGCR (span.bz, left->bz._hoops_HAGR._hoops_SAGCR, right->bz._hoops_HAGR._hoops_SAGCR, dx);
							}
							if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
								_hoops_HAGCR (span.r, left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR, right->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR, dx);
								_hoops_HAGCR (span.g, left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR, right->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR, dx);
								_hoops_HAGCR (span.b, left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR, right->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR, dx);
							}
						}

						/* _hoops_IRGGA _hoops_HSPH */
						if ((int)x < _hoops_GPHH.left) {
							/* _hoops_IHIS _hoops_GH _hoops_IS _hoops_RAAP */
							int				_hoops_HGCGP;

							_hoops_HGCGP = _hoops_GPHH.left - x;

							x += _hoops_HGCGP;
							dx -= _hoops_HGCGP;
							if (_hoops_PPCCP != 0) {
								if (BIT (_hoops_PPCCP, _hoops_IRHSP)) {
									_hoops_CIHHS (span.bz, _hoops_HGCGP);
								}
								if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
									_hoops_RHHHS (span.r, _hoops_HGCGP);
									_hoops_RHHHS (span.g, _hoops_HGCGP);
									_hoops_RHHHS (span.b, _hoops_HGCGP);
								}
							}
						}
						if ((int)x + dx > _hoops_GPHH.right) {
							/* _hoops_PSRAR _hoops_CAASH */
							dx = _hoops_GPHH.right+1 - x;
						}
					}

					/* _hoops_HPPP _hoops_PA _hoops_HHRPA */
					if (dx > 0) {
						_hoops_RAAH alter *			_hoops_HSSIR = null;
						RGBAS32 alter *			_hoops_RPPA = null;
						unsigned char alter *	sp = null;

						if (_hoops_RARGGR != null)
							sp = &_hoops_RARGGR[0][x];
						if (_hoops_PCSIR != null)
							_hoops_HSSIR = &_hoops_PCSIR[0][x];
						if (_hoops_ACSIR != null)
							_hoops_RPPA = &_hoops_ACSIR[0][x];

						_hoops_PCCAR {
							int		_hoops_AARGGR = _hoops_PPHSP;

							if (BIT (test, _hoops_SRHSP)) {
								int		_hoops_PARGGR = _hoops_ICSIR->input._hoops_RPHSP;
								int		_hoops_HAGR = *sp;
								int		ref = _hoops_ICSIR->input._hoops_APHSP;
								int		result;
									
								if (_hoops_HAGR < ref)
									result = _hoops_IAHSP;
								else if (_hoops_HAGR == ref)
									result = TEST_EQUAL;
								else
									result = TEST_GREATER;

								if ((result & _hoops_PARGGR) == 0) {
									_hoops_AARGGR = _hoops_ICSIR->input._hoops_RRIH;
									goto _hoops_SCAIP;
								}
							}

							if (BIT (test, _hoops_IRHSP)) {
								int		_hoops_CHRAS = _hoops_ICSIR->input._hoops_RCSCP;
								int		_hoops_HAGR = span.bz._hoops_HAGR._hoops_SAGCR;
								int		ref = *_hoops_HSSIR;
								int		result;

								if (_hoops_HAGR < ref)
									result = _hoops_IAHSP;
								else if (_hoops_HAGR == ref)
									result = TEST_EQUAL;
								else
									result = TEST_GREATER;

								if ((result & _hoops_CHRAS) == 0) {
									_hoops_AARGGR = _hoops_ICSIR->input._hoops_PRIH;
									goto _hoops_SCAIP;
								}
							}

							_hoops_AARGGR = _hoops_ICSIR->input._hoops_RHHSP;

/* _hoops_GGCR _hoops_IRPR _hoops_GIPRC _hoops_RPGP & _hoops_GIAGR (_hoops_RHGGP _hoops_RRH _hoops_HCPC _hoops_CGARA)
							_hoops_RPP (_hoops_HARGGR && ! _hoops_IARGGR  )
								_hoops_HHIIA _hoops_GCHGA;
*/

							if (BIT (update, _hoops_IRHSP))
								*_hoops_HSSIR = span.bz._hoops_HAGR._hoops_SAGCR;

							if (BIT (update, _hoops_GPSCP)) {
								if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
									_hoops_RPPA[0].r = (unsigned char)span.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
									_hoops_RPPA[0].g = (unsigned char)span.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
									_hoops_RPPA[0].b = (unsigned char)span.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
									_hoops_RPPA[0].a = _hoops_GPGCR;
								}
								else {
									_hoops_RPPA[0] = _hoops_ICSIR->input.color;
								}
							}

							if (BIT (update, FBI_OCCLUSION)) {
								if (++_hoops_ICSIR->input._hoops_PHHSP >=
										  _hoops_ICSIR->input._hoops_AHHSP)
									return;
							}

						  _hoops_SCAIP:
							if (BIT (update, _hoops_SRHSP)) {
								switch (_hoops_AARGGR) {
									case _hoops_PPHSP:
										break;
									case _hoops_HPHSP:
										*sp = _hoops_ICSIR->input._hoops_APHSP;
										break;
									case _hoops_IPHSP:
										if (*sp < 255) ++*sp;
										break;
									case _hoops_CPHSP:
										if (*sp > 0) --*sp;
										break;
									case _hoops_SPHSP:
										*sp = ~*sp & 0x00FF;
										break;
									case _hoops_GHHSP:
										*sp = 0;
										break;
								}
							}

							if (--dx == 0)
								break;

							if (sp != null)
								sp++;
							if (_hoops_HSSIR != null)
								_hoops_HSSIR++;
							if (_hoops_RPPA != null)
								_hoops_RPPA++;

							if (_hoops_PPCCP != 0) {
								if (BIT (_hoops_PPCCP, _hoops_IRHSP)) {
									_hoops_APGCR (span.bz);
								}
								if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
									_hoops_RPGCR (span.r);
									_hoops_RPGCR (span.g);
									_hoops_RPGCR (span.b);
								}
							}
						}
					}

					_hoops_APGCR (_hoops_CSGCR.bx);
					if (_hoops_PPCCP != 0) {
						if (BIT (_hoops_PPCCP, _hoops_IRHSP)) {
							_hoops_APGCR(_hoops_CSGCR.bz);
						}
						if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
							_hoops_RPGCR (_hoops_CSGCR.r);
							_hoops_RPGCR (_hoops_CSGCR.g);
							_hoops_RPGCR (_hoops_CSGCR.b);
						}
					}

					if (_hoops_RARGGR != null)
						++_hoops_RARGGR;
					if (_hoops_PCSIR != null)
						++_hoops_PCSIR;
					if (_hoops_ACSIR != null)
						++_hoops_ACSIR;

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;
					++y;

					_hoops_APGCR (_hoops_SSGCR.bx);
					if (_hoops_PPCCP != 0) {
						if (BIT (_hoops_PPCCP, _hoops_IRHSP)) {
							_hoops_APGCR (_hoops_SSGCR.bz);
						}
						if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
							_hoops_RPGCR (_hoops_SSGCR.r);
							_hoops_RPGCR (_hoops_SSGCR.g);
							_hoops_RPGCR (_hoops_SSGCR.b);
						}
					}
				}
			}
		}
	}
#endif
}

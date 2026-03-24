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
 * $Id: obf_tmp.txt 1.41 2010-10-06 19:15:52 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "hd_proto.h"
#include "span.h"


/*
 * _hoops_IGGCR _hoops_IRS _hoops_III _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z16_U (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points) { /* _hoops_CGGCR 2 */
#ifndef _hoops_GCSIR

	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Polyline (nr, count, points);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, 
			0, 0, 0, 0, 0, _hoops_SCSIR);
		return;
	}

	HD_Buffer_DC_Polyline_C24_Z16_C (nr, count, points,
		(RGBAS32 const *)&nr->_hoops_AHP->color, true);
#endif
}


/*
 * _hoops_IGGCR _hoops_IRIC-_hoops_RCIAR _hoops_III _hoops_CRGR _hoops_PCCP 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z16_G (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors) {
#ifndef _hoops_GCSIR
	_hoops_RCSIR					pts[2];
	_hoops_SGGCR						_hoops_IASGR[2];
	int								_hoops_CRRAR;
	RGBAS32 alter * const		*_hoops_ACSIR;
	_hoops_RAAH alter * const			*_hoops_PCSIR;
	int								dx;
	_hoops_GRGCR			r, g, b;
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);

	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Gouraud_Polyline (nr, count, points, colors);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0,
			0, 0, 0, 0, _hoops_SCSIR|_hoops_AAIC);
		return;
	}


#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count--) {

		RGBAS32 const	*_hoops_RRGCR = colors;
		int				_hoops_ARGCR;

		if (_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], b)) {
			HD_Buffer_DC_Polyline_C24_Z16_C (nr, 2, points, colors, true);
			goto _hoops_HRGCR;
		}


		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y <= pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);
			TRUNCATE_2_POINTS (points, pts, 0, 1, z);

			_hoops_IASGR[0].r = _hoops_IRGCR (colors[0].r);
			_hoops_IASGR[0].g = _hoops_IRGCR (colors[0].g);
			_hoops_IASGR[0].b = _hoops_IRGCR (colors[0].b);
			_hoops_IASGR[1].r = _hoops_IRGCR (colors[1].r);
			_hoops_IASGR[1].g = _hoops_IRGCR (colors[1].g);
			_hoops_IASGR[1].b = _hoops_IRGCR (colors[1].b);
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			TRUNCATE_2_POINTS (points, pts, 1, 0, z);
			_hoops_CRGCR (pts[0].y, pts[1].y);

			_hoops_IASGR[0].r = _hoops_IRGCR (colors[1].r);
			_hoops_IASGR[0].g = _hoops_IRGCR (colors[1].g);
			_hoops_IASGR[0].b = _hoops_IRGCR (colors[1].b);
			_hoops_IASGR[1].r = _hoops_IRGCR (colors[0].r);
			_hoops_IASGR[1].g = _hoops_IRGCR (colors[0].g);
			_hoops_IASGR[1].b = _hoops_IRGCR (colors[0].b);
		}

		{
			int						row = pts[0].y - _hoops_ICSIR->offset.y;
			int						offset = -_hoops_ICSIR->offset.x;

			_hoops_ACSIR = &((_hoops_CSSIR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
			_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[row];
			pts[0].x += offset;
			pts[1].x += offset;

			offset = (int)(nr->transform_rendition->_hoops_SHIH * 
				_hoops_ISSIR(nr->transform_rendition));
			pts[0].z += offset;
			pts[1].z += offset;
		}

		{
			_hoops_SRGCR					a0;
			RGBAS32 alter				*_hoops_RPPA;
			_hoops_RAAH alter					*_hoops_HSSIR;
			unsigned int					x;

			_hoops_CRRAR = pts[1].y - pts[0].y;
			dx = pts[1].x - pts[0].x;

			if (_hoops_CRRAR == 0)
				goto _hoops_GAGCR;
			if (dx == 0)
				goto _hoops_RAGCR;
			else if (dx > 0) {
				if (dx > _hoops_CRRAR)
					goto _hoops_AAGCR;
				else
					goto _hoops_RAGCR;
			}
			else {
				dx = -dx;
				if (dx > _hoops_CRRAR)
					goto _hoops_PAGCR;
				else
					goto _hoops_RAGCR;
			}

			/* _hoops_HAR _hoops_GCSPR */

			_hoops_RAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_CRRAR);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_CRRAR);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_CRRAR);
				++_hoops_CRRAR;

				_hoops_PCCAR {
					_hoops_HSSIR = &_hoops_PCSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR];

					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_RPPA = &_hoops_ACSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR];
						_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].a = _hoops_GPGCR;
					}

					if (--_hoops_CRRAR == 0) break;

					_hoops_RPGCR (a0.x);
					_hoops_APGCR (a0.bz);
					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);
					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];
				}
				goto _hoops_HRGCR;
			}

			_hoops_GAGCR: {
				if (dx < 0) {
					x = pts[1].x;
					dx = -dx;
					_hoops_IAGCR (a0.bz, pts[1].z, pts[0].z, dx);
					_hoops_HAGCR (r, _hoops_IASGR[1].r, _hoops_IASGR[0].r, dx);
					_hoops_HAGCR (g, _hoops_IASGR[1].g, _hoops_IASGR[0].g, dx);
					_hoops_HAGCR (b, _hoops_IASGR[1].b, _hoops_IASGR[0].b, dx);
				}
				else {
					x = pts[0].x;
					_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);
					_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
					_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
					_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);
				}
				++dx;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].a = _hoops_GPGCR;
					}

					if (--dx <= 0) break;

					_hoops_APGCR (a0.bz);
					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					_hoops_RPPA = &_hoops_RPPA[1];
					_hoops_HSSIR = &_hoops_HSSIR[1];
				}

				goto _hoops_HRGCR;
			}

			_hoops_AAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_HSSIR = &_hoops_PCSIR[0][x];

					_hoops_PCCAR {
						if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
							if (_hoops_CCSIR)
								_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
							else if (_hoops_HSSIR[0] == _hoops_GGGCR)
								_hoops_HSSIR[0]--;

							_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							_hoops_RPPA[0].a = _hoops_GPGCR;
						}

						_hoops_APGCR (a0.bz);
						_hoops_RPGCR (r);
						_hoops_RPGCR (g);
						_hoops_RPGCR (b);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[1];
						_hoops_HSSIR = &_hoops_HSSIR[1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = pts[1].x - x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].a = _hoops_GPGCR;
					}

					if (--dx <= 0) break;

					_hoops_APGCR (a0.bz);
					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					_hoops_RPPA = &_hoops_RPPA[1];
					_hoops_HSSIR = &_hoops_HSSIR[1];
				}

				goto _hoops_HRGCR;
			}

			_hoops_PAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = x - a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_HSSIR = &_hoops_PCSIR[0][x];

					_hoops_PCCAR {
						if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
							if (_hoops_CCSIR)
								_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
							else if (_hoops_HSSIR[0] == _hoops_GGGCR)
								_hoops_HSSIR[0]--;

							_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							_hoops_RPPA[0].a = _hoops_GPGCR;
						}

						_hoops_APGCR (a0.bz);
						_hoops_RPGCR (r);
						_hoops_RPGCR (g);
						_hoops_RPGCR (b);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[-1];
						_hoops_HSSIR = &_hoops_HSSIR[-1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = x - pts[1].x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].a = _hoops_GPGCR;
					}

					_hoops_APGCR (a0.bz);
					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					if (--dx <= 0) break;

					_hoops_RPPA = &_hoops_RPPA[-1];
					_hoops_HSSIR = &_hoops_HSSIR[-1];
				}

				goto _hoops_HRGCR;
			}
		}

_hoops_HRGCR:
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}


/*
 * _hoops_IGGCR _hoops_IRS _hoops_HPGCR _hoops_III _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z16_C (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors,
	bool						single) {
#ifndef _hoops_GCSIR
	_hoops_RCSIR					pts[2];
	Driver_Color				color;
	int							_hoops_CRRAR;
	RGBAS32 alter * const		*_hoops_ACSIR;
	_hoops_RAAH alter * const			*_hoops_PCSIR;
	int							dx;
	int							_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);

	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Colorized_Polyline (nr, count, points, colors, single);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0,
			0, 0, 0, 0, _hoops_SCSIR|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y <= pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);
			TRUNCATE_2_POINTS (points, pts, 0, 1, z);
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			TRUNCATE_2_POINTS (points, pts, 1, 0, z);
			_hoops_CRGCR (pts[0].y, pts[1].y);
		}

	
		int						row = pts[0].y - _hoops_ICSIR->offset.y;
		int						offset = -_hoops_ICSIR->offset.x;

		_hoops_ACSIR = &((_hoops_CSSIR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
		_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[row];
		pts[0].x += offset;
		pts[1].x += offset;

		offset = (int)(nr->transform_rendition->_hoops_SHIH * 
			_hoops_ISSIR(nr->transform_rendition));
		pts[0].z += offset;
		pts[1].z += offset;
	
		_hoops_SRGCR			a0;
		_hoops_RAAH alter			*_hoops_HSSIR;
		RGBAS32 alter		*_hoops_RPPA;
		unsigned int		x;

		color = *colors;

		_hoops_CRRAR = pts[1].y - pts[0].y;
		dx = pts[1].x - pts[0].x;

		if (_hoops_CRRAR == 0)
			goto _hoops_GAGCR;
		if (dx == 0)
			goto _hoops_RAGCR;
		else if (dx > 0) {
			if (dx > _hoops_CRRAR)
				goto _hoops_AAGCR;
			else
				goto _hoops_RAGCR;
		}
		else {
			dx = -dx;
			if (dx > _hoops_CRRAR)
				goto _hoops_PAGCR;
			else
				goto _hoops_RAGCR;
		}

		/* _hoops_HAR _hoops_GCSPR */

		_hoops_RAGCR: {
			_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
			_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
			++_hoops_CRRAR;

			_hoops_PCCAR {
				_hoops_HSSIR = &_hoops_PCSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR];

				if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
					if (_hoops_CCSIR)
						_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
					else if (_hoops_HSSIR[0] == _hoops_GGGCR)
						_hoops_HSSIR[0]--;

					_hoops_ACSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR] = color;
				}

				if (--_hoops_CRRAR == 0) break;

				_hoops_RPGCR (a0.x);
				_hoops_APGCR (a0.bz);
				_hoops_ACSIR = &_hoops_ACSIR[1];
				_hoops_PCSIR = &_hoops_PCSIR[1];
			}

			goto next;
		}

		_hoops_GAGCR: {
			if (dx < 0) {
				x = pts[1].x;
				dx = -dx;
				_hoops_IAGCR (a0.bz, pts[1].z, pts[0].z, dx);
			}
			else {
				x = pts[0].x;
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);
			}
			++dx;
			_hoops_RPPA = &_hoops_ACSIR[0][x];
			_hoops_HSSIR = &_hoops_PCSIR[0][x];

			_hoops_PCCAR {
				if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
					if (_hoops_CCSIR)
						_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
					else if (_hoops_HSSIR[0] == _hoops_GGGCR)
						_hoops_HSSIR[0]--;

					_hoops_RPPA[0] = color;
				}

				if (--dx <= 0) break;

				_hoops_APGCR (a0.bz);

				_hoops_RPPA = &_hoops_RPPA[1];
				_hoops_HSSIR = &_hoops_HSSIR[1];
			}

			goto next;
		}

		_hoops_AAGCR: {
			_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
			_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);

			x = pts[0].x;
			_hoops_PPGCR (a0.x);

			_hoops_PCCAR {
				dx = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_RPPA[0] = color;
					}

					_hoops_APGCR (a0.bz);

					if (--dx <= 0) break;

					_hoops_RPPA = &_hoops_RPPA[1];
					_hoops_HSSIR = &_hoops_HSSIR[1];
				}

				x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				_hoops_ACSIR = &_hoops_ACSIR[1];
				_hoops_PCSIR = &_hoops_PCSIR[1];

				if (--_hoops_CRRAR <= 0) break;

				_hoops_RPGCR (a0.x);
			}

			dx = pts[1].x - x + 1;
			_hoops_RPPA = &_hoops_ACSIR[0][x];
			_hoops_HSSIR = &_hoops_PCSIR[0][x];

			_hoops_PCCAR {
				if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
					if (_hoops_CCSIR)
						_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
					else if (_hoops_HSSIR[0] == _hoops_GGGCR)
						_hoops_HSSIR[0]--;

					_hoops_RPPA[0] = color;
				}

				_hoops_APGCR (a0.bz);

				if (--dx <= 0) break;

				_hoops_RPPA = &_hoops_RPPA[1];
				_hoops_HSSIR = &_hoops_HSSIR[1];
			}

			goto next;
		}

		_hoops_PAGCR: {
			_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
			_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);

			x = pts[0].x;
			_hoops_PPGCR (a0.x);

			_hoops_PCCAR {
				dx = x - a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_RPPA[0] = color;
					}

					_hoops_APGCR (a0.bz);

					if (--dx <= 0) break;

					_hoops_RPPA = &_hoops_RPPA[-1];
					_hoops_HSSIR = &_hoops_HSSIR[-1];
				}

				x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				_hoops_ACSIR = &_hoops_ACSIR[1];
				_hoops_PCSIR = &_hoops_PCSIR[1];

				if (--_hoops_CRRAR <= 0) break;

				_hoops_RPGCR (a0.x);
			}

			dx = x - pts[1].x + 1;
			_hoops_RPPA = &_hoops_ACSIR[0][x];
			_hoops_HSSIR = &_hoops_PCSIR[0][x];

			_hoops_PCCAR {
				if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
					if (_hoops_CCSIR)
						_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
					else if (_hoops_HSSIR[0] == _hoops_GGGCR)
						_hoops_HSSIR[0]--;

					_hoops_RPPA[0] = color;
				}

				if (--dx <= 0) break;

				_hoops_APGCR (a0.bz);

				_hoops_RPPA = &_hoops_RPPA[-1];
				_hoops_HSSIR = &_hoops_HSSIR[-1];
			}

			goto next;
		}

	  next:
		points += _hoops_RRC;
		if (!single)
			colors++;
	}
#endif
}



/*
 * _hoops_IGGCR _hoops_IRS _hoops_III _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z00_U (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points) {
#ifndef _hoops_RGGCR

	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Polyline (nr, count, points);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_SCSIR);
		return;
	}

	HD_Buffer_DC_Polyline_C24_Z00_C (nr, count, points,
		(RGBAS32 const *)&nr->_hoops_AHP->color, true);
#endif
}




/*
 * _hoops_GISP _hoops_IRS _hoops_IRIC-_hoops_RCIAR _hoops_III _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z00_G (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors) {
#ifndef _hoops_RGGCR
	_hoops_RCSIR					pts[2];
	_hoops_SGGCR						_hoops_IASGR[2];
	int								_hoops_CRRAR;
	RGBAS32 alter * const		*_hoops_ACSIR;
	int								dx;
	_hoops_GRGCR			r, g, b;
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;

	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Gouraud_Polyline (nr, count, points, colors);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0, 
			0, 0, 0, 0, _hoops_SCSIR|_hoops_AAIC);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count--) {

		RGBAS32 const	*_hoops_RRGCR = colors;
		int				_hoops_ARGCR;

		if (_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], b)) {
			HD_Buffer_DC_Polyline_C24_Z00_C (nr, 2, points, colors, true);
			goto _hoops_HRGCR;
		}

		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y <= pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);

			_hoops_IASGR[0].r = _hoops_IRGCR (colors[0].r);
			_hoops_IASGR[0].g = _hoops_IRGCR (colors[0].g);
			_hoops_IASGR[0].b = _hoops_IRGCR (colors[0].b);
			_hoops_IASGR[1].r = _hoops_IRGCR (colors[1].r);
			_hoops_IASGR[1].g = _hoops_IRGCR (colors[1].g);
			_hoops_IASGR[1].b = _hoops_IRGCR (colors[1].b);
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			_hoops_CRGCR (pts[0].y, pts[1].y);

			_hoops_IASGR[0].r = _hoops_IRGCR (colors[1].r);
			_hoops_IASGR[0].g = _hoops_IRGCR (colors[1].g);
			_hoops_IASGR[0].b = _hoops_IRGCR (colors[1].b);
			_hoops_IASGR[1].r = _hoops_IRGCR (colors[0].r);
			_hoops_IASGR[1].g = _hoops_IRGCR (colors[0].g);
			_hoops_IASGR[1].b = _hoops_IRGCR (colors[0].b);
		}

		{
			int						row = pts[0].y - _hoops_ICSIR->offset.y;
			int						offset = -_hoops_ICSIR->offset.x;

			_hoops_ACSIR = &((_hoops_CSSIR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
			pts[0].x += offset;
			pts[1].x += offset;
		}

		{
			_hoops_IPGCR						a0;
			RGBAS32 alter				*_hoops_RPPA;
			unsigned int					x;

			_hoops_CRRAR = pts[1].y - pts[0].y;
			dx = pts[1].x - pts[0].x;

			if (_hoops_CRRAR == 0)
				goto _hoops_GAGCR;
			if (dx == 0)
				goto _hoops_RAGCR;
			else if (dx > 0) {
				if (dx > _hoops_CRRAR)
					goto _hoops_AAGCR;
				else
					goto _hoops_RAGCR;
			}
			else {
				dx = -dx;
				if (dx > _hoops_CRRAR)
					goto _hoops_PAGCR;
				else
					goto _hoops_RAGCR;
			}

			/* _hoops_HAR _hoops_GCSPR */

			_hoops_RAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_CRRAR);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_CRRAR);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_CRRAR);

				++_hoops_CRRAR;

				_hoops_PCCAR {
					_hoops_RPPA = &_hoops_ACSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR];
					_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].a = _hoops_GPGCR;

					if (--_hoops_CRRAR == 0) break;

					_hoops_RPGCR (a0.x);
					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);
					_hoops_ACSIR = &_hoops_ACSIR[1];
				}

				goto _hoops_HRGCR;
			}

			_hoops_GAGCR: {
				if (dx < 0) {
					x = pts[1].x;
					dx = -dx;
					_hoops_HAGCR (r, _hoops_IASGR[1].r, _hoops_IASGR[0].r, dx);
					_hoops_HAGCR (g, _hoops_IASGR[1].g, _hoops_IASGR[0].g, dx);
					_hoops_HAGCR (b, _hoops_IASGR[1].b, _hoops_IASGR[0].b, dx);
				}
				else {
					x = pts[0].x;
					_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
					_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
					_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);
				}
				++dx;
				_hoops_RPPA = &_hoops_ACSIR[0][x];

				_hoops_PCCAR {
					_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].a = _hoops_GPGCR;

					if (--dx <= 0) break;

					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					_hoops_RPPA = &_hoops_RPPA[1];
				}

				goto _hoops_HRGCR;
			}

			_hoops_AAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;
					_hoops_RPPA = &_hoops_ACSIR[0][x];

					_hoops_PCCAR {
						_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].a = _hoops_GPGCR;

						_hoops_RPGCR (r);
						_hoops_RPGCR (g);
						_hoops_RPGCR (b);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = pts[1].x - x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];

				_hoops_PCCAR {
					_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].a = _hoops_GPGCR;

					if (--dx <= 0) break;

					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					_hoops_RPPA = &_hoops_RPPA[1];
				}

				goto _hoops_HRGCR;
			}

			_hoops_PAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = x - a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA = &_hoops_ACSIR[0][x];

					_hoops_PCCAR {
						_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
						_hoops_RPPA[0].a = _hoops_GPGCR;

						_hoops_RPGCR (r);
						_hoops_RPGCR (g);
						_hoops_RPGCR (b);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[-1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = x - pts[1].x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];

				_hoops_PCCAR {
					_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA[0].a = _hoops_GPGCR;

					if (--dx <= 0) break;

					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					_hoops_RPPA = &_hoops_RPPA[-1];
				}

				goto _hoops_HRGCR;
			}
		}

_hoops_HRGCR:
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}



/*
 * _hoops_IGGCR _hoops_IRS _hoops_HPGCR _hoops_III _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C24_Z00_C (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors,
	bool						single) {
#ifndef _hoops_RGGCR
	_hoops_RCSIR					pts[2];
	int								_hoops_CRRAR;
	RGBAS32 alter * const		*_hoops_ACSIR;
	Driver_Color				color;
	int								dx;
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;

	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Colorized_Polyline (nr, count, points, colors, single);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0,
			0, 0, 0, 0, _hoops_SCSIR|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y <= pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			_hoops_CRGCR (pts[0].y, pts[1].y);
		}

		{
			int				row = pts[0].y - _hoops_ICSIR->offset.y;
			int				offset = -_hoops_ICSIR->offset.x;

			_hoops_ACSIR = &((_hoops_CSSIR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
			pts[0].x += offset;
			pts[1].x += offset;
		}

		{
			_hoops_IPGCR						a0;
			RGBAS32 alter				*_hoops_RPPA;
			unsigned int					x;

			color = *colors;

			_hoops_CRRAR = pts[1].y - pts[0].y;
			dx = pts[1].x - pts[0].x;

			if (_hoops_CRRAR == 0)
				goto _hoops_GAGCR;
			if (dx == 0)
				goto _hoops_RAGCR;
			else if (dx > 0) {
				if (_hoops_CRRAR == 0)
					goto _hoops_GAGCR;
				else if (dx > _hoops_CRRAR)
					goto _hoops_AAGCR;
				else
					goto _hoops_RAGCR;
			}
			else {
				dx = -dx;
				if (_hoops_CRRAR == 0)
					goto _hoops_GAGCR;
				else if (dx > _hoops_CRRAR)
					goto _hoops_PAGCR;
				else
					goto _hoops_RAGCR;
			}

			/* _hoops_HAR _hoops_GCSPR */

			_hoops_RAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				++_hoops_CRRAR;

				_hoops_PCCAR {
					_hoops_ACSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR] = color;

					if (--_hoops_CRRAR == 0) break;

					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_RPGCR (a0.x);
				}
				goto next;
			}


			_hoops_GAGCR: {
				if (dx < 0) {
					x = pts[1].x;
					dx = -dx;
				}
				else
					x = pts[0].x;

				++dx;
				_hoops_RPPA = &_hoops_ACSIR[0][x];

				switch (dx) {
					case 16: _hoops_RPPA[15] = color; _hoops_HHHI;
					case 15: _hoops_RPPA[14] = color; _hoops_HHHI;
					case 14: _hoops_RPPA[13] = color; _hoops_HHHI;
					case 13: _hoops_RPPA[12] = color; _hoops_HHHI;
					case 12: _hoops_RPPA[11] = color; _hoops_HHHI;
					case 11: _hoops_RPPA[10] = color; _hoops_HHHI;
					case 10: _hoops_RPPA[9]	= color; _hoops_HHHI;
					case  9: _hoops_RPPA[8]	= color; _hoops_HHHI;
					case  8: _hoops_RPPA[7]	= color; _hoops_HHHI;
					case  7: _hoops_RPPA[6]	= color; _hoops_HHHI;
					case  6: _hoops_RPPA[5]	= color; _hoops_HHHI;
					case  5: _hoops_RPPA[4]	= color; _hoops_HHHI;
					case  4: _hoops_RPPA[3]	= color; _hoops_HHHI;
					case  3: _hoops_RPPA[2]	= color; _hoops_HHHI;
					case  2: _hoops_RPPA[1]	= color; _hoops_HHHI;
					case  1: _hoops_RPPA[0]	= color; break;
					case  0: break;

					default: {
						_hoops_PCCAR {
							_hoops_RPPA[0] = color;

							if (--dx <= 0) break;

							_hoops_RPPA = &_hoops_RPPA[1];
						}
					}	break;
				}

				goto next;
			}

			_hoops_AAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;
					_hoops_RPPA = &_hoops_ACSIR[0][x];

					switch (dx) {
						case 16: _hoops_RPPA[15] = color; _hoops_HHHI;
						case 15: _hoops_RPPA[14] = color; _hoops_HHHI;
						case 14: _hoops_RPPA[13] = color; _hoops_HHHI;
						case 13: _hoops_RPPA[12] = color; _hoops_HHHI;
						case 12: _hoops_RPPA[11] = color; _hoops_HHHI;
						case 11: _hoops_RPPA[10] = color; _hoops_HHHI;
						case 10: _hoops_RPPA[9]	= color; _hoops_HHHI;
						case  9: _hoops_RPPA[8]	= color; _hoops_HHHI;
						case  8: _hoops_RPPA[7]	= color; _hoops_HHHI;
						case  7: _hoops_RPPA[6]	= color; _hoops_HHHI;
						case  6: _hoops_RPPA[5]	= color; _hoops_HHHI;
						case  5: _hoops_RPPA[4]	= color; _hoops_HHHI;
						case  4: _hoops_RPPA[3]	= color; _hoops_HHHI;
						case  3: _hoops_RPPA[2]	= color; _hoops_HHHI;
						case  2: _hoops_RPPA[1]	= color; _hoops_HHHI;
						case  1: _hoops_RPPA[0]	= color; break;
						case  0: break;

						default: {
							_hoops_PCCAR {
								_hoops_RPPA[0] = color;

								if (--dx <= 0) break;

								_hoops_RPPA = &_hoops_RPPA[1];
							}
						}	break;
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = pts[1].x - x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];

				switch (dx) {
					case 16: _hoops_RPPA[15] = color; _hoops_HHHI;
					case 15: _hoops_RPPA[14] = color; _hoops_HHHI;
					case 14: _hoops_RPPA[13] = color; _hoops_HHHI;
					case 13: _hoops_RPPA[12] = color; _hoops_HHHI;
					case 12: _hoops_RPPA[11] = color; _hoops_HHHI;
					case 11: _hoops_RPPA[10] = color; _hoops_HHHI;
					case 10: _hoops_RPPA[9]	= color; _hoops_HHHI;
					case  9: _hoops_RPPA[8]	= color; _hoops_HHHI;
					case  8: _hoops_RPPA[7]	= color; _hoops_HHHI;
					case  7: _hoops_RPPA[6]	= color; _hoops_HHHI;
					case  6: _hoops_RPPA[5]	= color; _hoops_HHHI;
					case  5: _hoops_RPPA[4]	= color; _hoops_HHHI;
					case  4: _hoops_RPPA[3]	= color; _hoops_HHHI;
					case  3: _hoops_RPPA[2]	= color; _hoops_HHHI;
					case  2: _hoops_RPPA[1]	= color; _hoops_HHHI;
					case  1: _hoops_RPPA[0]	= color; break;
					case  0: break;

					default: {
						_hoops_PCCAR {
							_hoops_RPPA[0] = color;

							if (--dx <= 0) break;

							_hoops_RPPA = &_hoops_RPPA[1];
						}
					}	break;
				}

				goto next;
			}

			_hoops_PAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = x - a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA = &_hoops_ACSIR[0][x];

					switch (dx) {
						case 16: _hoops_RPPA[-15] = color; _hoops_HHHI;
						case 15: _hoops_RPPA[-14] = color; _hoops_HHHI;
						case 14: _hoops_RPPA[-13] = color; _hoops_HHHI;
						case 13: _hoops_RPPA[-12] = color; _hoops_HHHI;
						case 12: _hoops_RPPA[-11] = color; _hoops_HHHI;
						case 11: _hoops_RPPA[-10] = color; _hoops_HHHI;
						case 10: _hoops_RPPA[-9]	 = color; _hoops_HHHI;
						case  9: _hoops_RPPA[-8]	 = color; _hoops_HHHI;
						case  8: _hoops_RPPA[-7]	 = color; _hoops_HHHI;
						case  7: _hoops_RPPA[-6]	 = color; _hoops_HHHI;
						case  6: _hoops_RPPA[-5]	 = color; _hoops_HHHI;
						case  5: _hoops_RPPA[-4]	 = color; _hoops_HHHI;
						case  4: _hoops_RPPA[-3]	 = color; _hoops_HHHI;
						case  3: _hoops_RPPA[-2]	 = color; _hoops_HHHI;
						case  2: _hoops_RPPA[-1]	 = color; _hoops_HHHI;
						case  1: _hoops_RPPA[ 0]	 = color; break;
						case  0: break;

						default: {
							_hoops_PCCAR {
								_hoops_RPPA[0] = color;

								if (--dx <= 0) break;

								_hoops_RPPA = &_hoops_RPPA[-1];
							}
						}	break;
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = x - pts[1].x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];

				switch (dx) {
					case 16: _hoops_RPPA[-15] = color; _hoops_HHHI;
					case 15: _hoops_RPPA[-14] = color; _hoops_HHHI;
					case 14: _hoops_RPPA[-13] = color; _hoops_HHHI;
					case 13: _hoops_RPPA[-12] = color; _hoops_HHHI;
					case 12: _hoops_RPPA[-11] = color; _hoops_HHHI;
					case 11: _hoops_RPPA[-10] = color; _hoops_HHHI;
					case 10: _hoops_RPPA[-9]	 = color; _hoops_HHHI;
					case  9: _hoops_RPPA[-8]	 = color; _hoops_HHHI;
					case  8: _hoops_RPPA[-7]	 = color; _hoops_HHHI;
					case  7: _hoops_RPPA[-6]	 = color; _hoops_HHHI;
					case  6: _hoops_RPPA[-5]	 = color; _hoops_HHHI;
					case  5: _hoops_RPPA[-4]	 = color; _hoops_HHHI;
					case  4: _hoops_RPPA[-3]	 = color; _hoops_HHHI;
					case  3: _hoops_RPPA[-2]	 = color; _hoops_HHHI;
					case  2: _hoops_RPPA[-1]	 = color; _hoops_HHHI;
					case  1: _hoops_RPPA[ 0]	 = color; break;
					case  0: break;

					default: {
						_hoops_PCCAR {
							_hoops_RPPA[0] = color;

							if (--dx <= 0) break;

							_hoops_RPPA = &_hoops_RPPA[-1];
						}
					}	break;
				}

				goto next;
			}
		}

	  next:
		points += _hoops_RRC;
		if (!single)
			colors++;
	}
#endif
}



/*
 * _hoops_IGGCR _hoops_IRS _hoops_III _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z16_U (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points) {
#ifndef _hoops_GCSIR
	_hoops_RCSIR					pts[2];
	int								_hoops_CRRAR;
	unsigned char alter * const		*_hoops_ACSIR;
	_hoops_RAAH alter * const			*_hoops_PCSIR;
	unsigned char					color;
	int								dx;
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);

	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Polyline (nr, count, points);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_SCSIR);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif


	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	color = (unsigned char)nr->_hoops_AHP->color._hoops_PGGCR;

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y <= pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);
			TRUNCATE_2_POINTS (points, pts, 0, 1, z);
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			TRUNCATE_2_POINTS (points, pts, 1, 0, z);
			_hoops_CRGCR (pts[0].y, pts[1].y);
		}

		{
			int						offset = -_hoops_ICSIR->offset.x;

			int		row = pts[0].y - _hoops_ICSIR->offset.y;
			_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
			_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[row];
			pts[0].x += offset;
			pts[1].x += offset;

			offset = (int)(nr->transform_rendition->_hoops_SHIH * 
				_hoops_ISSIR(nr->transform_rendition));
			pts[0].z += offset;
			pts[1].z += offset;
		}

		{
			_hoops_SRGCR					a0;
			unsigned char alter				*_hoops_RPPA;
			_hoops_RAAH alter					*_hoops_HSSIR;
			unsigned int					x;

			_hoops_CRRAR = pts[1].y - pts[0].y;
			dx = pts[1].x - pts[0].x;

			if (_hoops_CRRAR == 0)
				goto _hoops_GAGCR;
			if (dx == 0)
				goto _hoops_RAGCR;
			else if (dx > 0) {
				if (dx > _hoops_CRRAR)
					goto _hoops_AAGCR;
				else
					goto _hoops_RAGCR;
			}
			else {
				dx = -dx;
				if (dx > _hoops_CRRAR)
					goto _hoops_PAGCR;
				else
					goto _hoops_RAGCR;
			}

			/* _hoops_HAR _hoops_GCSPR */

			_hoops_RAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				++_hoops_CRRAR;

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_PCSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR]) {
						_hoops_PCSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR] = a0.bz._hoops_HAGR._hoops_SAGCR;
						_hoops_ACSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR] = color;
					}

					if (--_hoops_CRRAR == 0) break;

					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];
					_hoops_RPGCR (a0.x);
					_hoops_APGCR (a0.bz);
				}

				goto next;
			}

			_hoops_GAGCR: {
				if (dx < 0) {
					x = pts[1].x;
					dx = -dx;
					_hoops_IAGCR (a0.bz, pts[1].z, pts[0].z, dx);
				}
				else {
					x = pts[0].x;
					_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);
				}
				++dx;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_RPPA[0] = color;
					}

					if (--dx <= 0) break;

					_hoops_APGCR (a0.bz);

					_hoops_RPPA = &_hoops_RPPA[1];
					_hoops_HSSIR = &_hoops_HSSIR[1];
				}

				goto next;
			}

			_hoops_AAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_HSSIR = &_hoops_PCSIR[0][x];

					_hoops_PCCAR {
						if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
							if (_hoops_CCSIR)
								_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
							else if (_hoops_HSSIR[0] == _hoops_GGGCR)
								_hoops_HSSIR[0]--;

							_hoops_RPPA[0] = color;
						}

						_hoops_APGCR (a0.bz);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[1];
						_hoops_HSSIR = &_hoops_HSSIR[1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = pts[1].x - x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_RPPA[0] = color;
					}

					if (--dx <= 0) break;

					_hoops_APGCR (a0.bz);

					_hoops_RPPA = &_hoops_RPPA[1];
					_hoops_HSSIR = &_hoops_HSSIR[1];
				}

				goto next;
			}

			_hoops_PAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = x - a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_HSSIR = &_hoops_PCSIR[0][x];

					_hoops_PCCAR {
						if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
							if (_hoops_CCSIR)
								_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
							else if (_hoops_HSSIR[0] == _hoops_GGGCR)
								_hoops_HSSIR[0]--;

							_hoops_RPPA[0] = color;
						}

						_hoops_APGCR (a0.bz);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[-1];
						_hoops_HSSIR = &_hoops_HSSIR[-1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = x - pts[1].x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_RPPA[0] = color;
					}

					if (--dx <= 0) break;

					_hoops_APGCR (a0.bz);

					_hoops_RPPA = &_hoops_RPPA[-1];
					_hoops_HSSIR = &_hoops_HSSIR[-1];
				}

				goto next;
			}
		}

	  next:
		points += _hoops_RRC;
	}
#endif
}


/*
 * _hoops_IGGCR _hoops_IRIC-_hoops_RCIAR _hoops_III _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z16_G (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors) {
#ifndef _hoops_GCSIR
	_hoops_RCSIR					pts[2];
	_hoops_SGGCR						_hoops_IASGR[2];
	int								_hoops_CRRAR;
	unsigned char alter * const		*_hoops_ACSIR;
	_hoops_RAAH alter * const			*_hoops_PCSIR;
	int								dx;
	int								row;
	unsigned short					_hoops_CPGCR;
	_hoops_GRGCR			r, g, b;
	_hoops_SGGCR						_hoops_SPGCR;
	_hoops_GHGCR					result;
	int								_hoops_RHGCR;
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);

	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Gouraud_Polyline (nr, count, points, colors);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0,
			0, 0, 0, 0, _hoops_SCSIR|_hoops_AAIC);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		RGBAS32 const	*_hoops_RRGCR = colors;
		int				_hoops_ARGCR;

		if (_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], b)) {
			HD_Buffer_DC_Polyline_C08_Z16_C (nr, 2, points, colors, true);
			goto _hoops_HRGCR;
		}

		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y <= pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);
			TRUNCATE_2_POINTS (points, pts, 0, 1, z);

			_hoops_IASGR[0].r = _hoops_IRGCR (colors[0].r);
			_hoops_IASGR[0].g = _hoops_IRGCR (colors[0].g);
			_hoops_IASGR[0].b = _hoops_IRGCR (colors[0].b);
			_hoops_IASGR[1].r = _hoops_IRGCR (colors[1].r);
			_hoops_IASGR[1].g = _hoops_IRGCR (colors[1].g);
			_hoops_IASGR[1].b = _hoops_IRGCR (colors[1].b);
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			TRUNCATE_2_POINTS (points, pts, 1, 0, z);
			_hoops_CRGCR (pts[0].y, pts[1].y);

			_hoops_IASGR[0].r = _hoops_IRGCR (colors[1].r);
			_hoops_IASGR[0].g = _hoops_IRGCR (colors[1].g);
			_hoops_IASGR[0].b = _hoops_IRGCR (colors[1].b);
			_hoops_IASGR[1].r = _hoops_IRGCR (colors[0].r);
			_hoops_IASGR[1].g = _hoops_IRGCR (colors[0].g);
			_hoops_IASGR[1].b = _hoops_IRGCR (colors[0].b);
		}

		{
			row = pts[0].y - _hoops_ICSIR->offset.y;

			_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
			_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[row];

			{
				int								offset;

				offset = -_hoops_ICSIR->offset.x;
				pts[0].x += offset;
				pts[1].x += offset;

				offset = (int)(nr->transform_rendition->_hoops_SHIH * 
					_hoops_ISSIR(nr->transform_rendition));
				pts[0].z += offset;
				pts[1].z += offset;
			}
		}

		{
			Display_Context const		*dc;
			int								_hoops_RPIS;

			dc = nr->_hoops_SRA;
			_hoops_RPIS = dc->_hoops_AHGCR.r;
			_hoops_IASGR[0].r = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].r);
			_hoops_IASGR[1].r = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].r);
			_hoops_RPIS = dc->_hoops_AHGCR.g;
			_hoops_IASGR[0].g = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].g);
			_hoops_IASGR[1].g = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].g);
			_hoops_RPIS = dc->_hoops_AHGCR.b;
			_hoops_IASGR[0].b = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].b);
			_hoops_IASGR[1].b = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].b);

			_hoops_SPGCR.r = dc->_hoops_HHGCR.r;
			_hoops_SPGCR.g = dc->_hoops_HHGCR.g;
			_hoops_SPGCR.b = dc->_hoops_HHGCR.b;
			_hoops_RHGCR = dc->_hoops_RHGCR;
		}

		{
			_hoops_SRGCR					a0;
			unsigned char alter				*_hoops_RPPA;
			_hoops_RAAH alter					*_hoops_HSSIR;
			unsigned int					x;
			unsigned short const			*_hoops_IHGCR;

			_hoops_CRRAR = pts[1].y - pts[0].y;
			dx = pts[1].x - pts[0].x;

			if (_hoops_CRRAR == 0)
				goto _hoops_GAGCR;
			if (dx == 0)
				goto _hoops_RAGCR;
			else if (dx > 0) {
				if (dx > _hoops_CRRAR)
					goto _hoops_AAGCR;
				else
					goto _hoops_RAGCR;
			}
			else {
				dx = -dx;
				if (dx > _hoops_CRRAR)
					goto _hoops_PAGCR;
				else
					goto _hoops_RAGCR;
			}

			/* _hoops_HAR _hoops_GCSPR */

			_hoops_RAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_CRRAR);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_CRRAR);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_CRRAR);

				++_hoops_CRRAR;

				_hoops_PCCAR {
					_hoops_HSSIR = &_hoops_PCSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR];

					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_RPPA = &_hoops_ACSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR];
						_hoops_CPGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7][(POINTER_SIZED_INT)_hoops_RPPA & 7];

						result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

						_hoops_RPPA[0] = _hoops_RHGCR +
								_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
								_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
								result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
					}

					if (--_hoops_CRRAR == 0) break;

					_hoops_RPGCR (a0.x);
					_hoops_APGCR (a0.bz);
					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);
					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];
					++row;
				}
				goto _hoops_HRGCR;
			}

			_hoops_GAGCR: {
				if (dx < 0) {
					x = pts[1].x;
					dx = -dx;
					_hoops_IAGCR (a0.bz, pts[1].z, pts[0].z, dx);
					_hoops_HAGCR (r, _hoops_IASGR[1].r, _hoops_IASGR[0].r, dx);
					_hoops_HAGCR (g, _hoops_IASGR[1].g, _hoops_IASGR[0].g, dx);
					_hoops_HAGCR (b, _hoops_IASGR[1].b, _hoops_IASGR[0].b, dx);
				}
				else {
					x = pts[0].x;
					_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);
					_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
					_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
					_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);
				}
				++dx;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];

						result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

						_hoops_RPPA[0] = _hoops_RHGCR +
								_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
								_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
								result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
					}

					_hoops_APGCR (a0.bz);
					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					if (--dx <= 0) break;

					_hoops_RPPA = &_hoops_RPPA[1];
					_hoops_HSSIR = &_hoops_HSSIR[1];
				}

				goto _hoops_HRGCR;
			}

			_hoops_AAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_HSSIR = &_hoops_PCSIR[0][x];
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					_hoops_PCCAR {
						if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
							if (_hoops_CCSIR)
								_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
							else if (_hoops_HSSIR[0] == _hoops_GGGCR)
								_hoops_HSSIR[0]--;

							_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];

							result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
							result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
							result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

							_hoops_RPPA[0] = _hoops_RHGCR +
									_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
									_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
									result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
						}

						_hoops_APGCR (a0.bz);
						_hoops_RPGCR (r);
						_hoops_RPGCR (g);
						_hoops_RPGCR (b);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[1];
						_hoops_HSSIR = &_hoops_HSSIR[1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];
					++row;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = pts[1].x - x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];

						result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

						_hoops_RPPA[0] = _hoops_RHGCR +
								_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
								_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
								result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
					}

					if (--dx <= 0) break;

					_hoops_APGCR (a0.bz);
					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					_hoops_RPPA = &_hoops_RPPA[1];
					_hoops_HSSIR = &_hoops_HSSIR[1];
				}

				goto _hoops_HRGCR;
			}

			_hoops_PAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = x - a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_HSSIR = &_hoops_PCSIR[0][x];
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					_hoops_PCCAR {
						if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
							if (_hoops_CCSIR)
								_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
							else if (_hoops_HSSIR[0] == _hoops_GGGCR)
								_hoops_HSSIR[0]--;

							_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];

							result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
							result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
							result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

							_hoops_RPPA[0] = _hoops_RHGCR +
									_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
									_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
									result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
						}

						_hoops_APGCR (a0.bz);
						_hoops_RPGCR (r);
						_hoops_RPGCR (g);
						_hoops_RPGCR (b);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[-1];
						_hoops_HSSIR = &_hoops_HSSIR[-1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];
					++row;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = x - pts[1].x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];

						result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

						_hoops_RPPA[0] = _hoops_RHGCR +
								_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
								_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
								result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
					}

					if (--dx <= 0) break;

					_hoops_APGCR (a0.bz);
					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					_hoops_RPPA = &_hoops_RPPA[-1];
					_hoops_HSSIR = &_hoops_HSSIR[-1];
				}

				goto _hoops_HRGCR;
			}
		}

_hoops_HRGCR:
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}




/*
 * _hoops_IGGCR _hoops_IRS _hoops_HPGCR _hoops_III _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z16_C (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors,
	bool						single) {
#ifndef _hoops_GCSIR
	_hoops_RCSIR					pts[2];
	int								_hoops_CRRAR;
	unsigned char alter * const		*_hoops_ACSIR;
	_hoops_RAAH alter * const			*_hoops_PCSIR;
	int								dx;
	unsigned char					_hoops_SHGCR;
	unsigned short					_hoops_CPGCR;
	unsigned short					_hoops_GIGCR, _hoops_RIGCR, d3;		/* _hoops_SICIR */
	unsigned char					_hoops_AIGCR, _hoops_PIGCR, _hoops_HIGCR;		/* _hoops_IIGCR _hoops_CIGCR */
	int								row;
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);

	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Colorized_Polyline (nr, count, points, colors, single);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0,
			0, 0, 0, 0, _hoops_SCSIR|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y <= pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);
			TRUNCATE_2_POINTS (points, pts, 0, 1, z);
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			TRUNCATE_2_POINTS (points, pts, 1, 0, z);
			_hoops_CRGCR (pts[0].y, pts[1].y);
		}

		{
			int						offset = -_hoops_ICSIR->offset.x;

			row = pts[0].y - _hoops_ICSIR->offset.y;
			_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
			_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[row];
			pts[0].x += offset;
			pts[1].x += offset;

			offset = (int)(nr->transform_rendition->_hoops_SHIH * 
				_hoops_ISSIR(nr->transform_rendition));
			pts[0].z += offset;
			pts[1].z += offset;
		}

		{
			Display_Context const		*dc;
			_hoops_SGGCR const				*_hoops_RPIS;
			_hoops_SGGCR const				*_hoops_SPGCR;
			_hoops_GHGCR					result;

			dc = nr->_hoops_SRA;
			_hoops_RPIS = &dc->_hoops_AHGCR;
			_hoops_SPGCR = &dc->_hoops_HHGCR;

			result.r.number = _hoops_PHGCR (_hoops_RPIS->r, colors->r) << 8;
			result.g.number = _hoops_PHGCR (_hoops_RPIS->g, colors->g) << 8;
			result.b.number = _hoops_PHGCR (_hoops_RPIS->b, colors->b) << 8;

			_hoops_SHGCR = dc->_hoops_RHGCR +
				_hoops_PHGCR (_hoops_SPGCR->r, result.r._hoops_CAGCR._hoops_SAGCR) +
				_hoops_PHGCR (_hoops_SPGCR->g, result.g._hoops_CAGCR._hoops_SAGCR) +
				result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP->_hoops_RCSR */ ;

#			define _hoops_SIGCR(_hoops_ICIPR, _hoops_CCIPR, _hoops_GCGCR) do {							\
					_hoops_GIGCR = 0xFFFF - result._hoops_ICIPR._hoops_CAGCR._hoops_RCGCR;				\
					_hoops_RIGCR = 0xFFFF - result._hoops_CCIPR._hoops_CAGCR._hoops_RCGCR;				\
					d3 = 0xFFFF - result._hoops_GCGCR._hoops_CAGCR._hoops_RCGCR;				\
					_hoops_AIGCR = _hoops_SHGCR + _hoops_SPGCR->_hoops_ICIPR;							\
					_hoops_PIGCR = _hoops_AIGCR + _hoops_SPGCR->_hoops_CCIPR;							\
					_hoops_HIGCR = _hoops_PIGCR + _hoops_SPGCR->_hoops_GCGCR;							\
				} while (0)

			if (result.r._hoops_CAGCR._hoops_RCGCR >= result.g._hoops_CAGCR._hoops_RCGCR) {
				if (result.g._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
					_hoops_SIGCR (r, g, b);
				else if (result.r._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
					_hoops_SIGCR (r, b, g);
				else
					_hoops_SIGCR (b, r, g);
			}
			else {
				if (result.r._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
					_hoops_SIGCR (g, r, b);
				else if (result.g._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
					_hoops_SIGCR (g, b, r);
				else
					_hoops_SIGCR (b, g, r);
			}

#			undef _hoops_SIGCR
		}

		{
			_hoops_SRGCR					a0;
			unsigned char alter				*_hoops_RPPA;
			_hoops_RAAH alter					*_hoops_HSSIR;
			unsigned int					x;
			unsigned short const			*_hoops_IHGCR;

			_hoops_CRRAR = pts[1].y - pts[0].y;
			dx = pts[1].x - pts[0].x;

			if (_hoops_CRRAR == 0)
				goto _hoops_GAGCR;
			if (dx == 0)
				goto _hoops_RAGCR;
			else if (dx > 0) {
				if (dx > _hoops_CRRAR)
					goto _hoops_AAGCR;
				else
					goto _hoops_RAGCR;
			}
			else {
				dx = -dx;
				if (dx > _hoops_CRRAR)
					goto _hoops_PAGCR;
				else
					goto _hoops_RAGCR;
			}

			/* _hoops_HAR _hoops_GCSPR */

			_hoops_RAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				++_hoops_CRRAR;

				_hoops_PCCAR {
					_hoops_HSSIR = &_hoops_PCSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR];

					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_RPPA = &_hoops_ACSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR];
						_hoops_CPGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7][(POINTER_SIZED_INT)_hoops_RPPA & 7];

						_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
					}

					if (--_hoops_CRRAR == 0) break;

					_hoops_RPGCR (a0.x);
					_hoops_APGCR (a0.bz);
					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];
					++row;
				}

				goto next;
			}

			_hoops_GAGCR: {
				if (dx < 0) {
					x = pts[1].x;
					dx = -dx;
					_hoops_IAGCR (a0.bz, pts[1].z, pts[0].z, dx);
				}
				else {
					x = pts[0].x;
					_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);
				}
				++dx;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
						_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
					}

					_hoops_APGCR (a0.bz);

					if (--dx <= 0) break;

					_hoops_RPPA = &_hoops_RPPA[1];
					_hoops_HSSIR = &_hoops_HSSIR[1];
				}

				goto next;
			}

			_hoops_AAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_HSSIR = &_hoops_PCSIR[0][x];
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					_hoops_PCCAR {
						if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
							if (_hoops_CCSIR)
								_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
							else if (_hoops_HSSIR[0] == _hoops_GGGCR)
								_hoops_HSSIR[0]--;

							_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
							_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						}

						_hoops_APGCR (a0.bz);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[1];
						_hoops_HSSIR = &_hoops_HSSIR[1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];
					++row;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = pts[1].x - x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
						_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
					}

					if (--dx <= 0) break;

					_hoops_APGCR (a0.bz);

					_hoops_RPPA = &_hoops_RPPA[1];
					_hoops_HSSIR = &_hoops_HSSIR[1];
				}

				goto next;
			}

			_hoops_PAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, dx);

				x = pts[0].x;
				_hoops_RPGCR (a0.x);

				_hoops_PCCAR {
					dx = x - a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_HSSIR = &_hoops_PCSIR[0][x];
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					_hoops_PCCAR {
						if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
							if (_hoops_CCSIR)
								_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
							else if (_hoops_HSSIR[0] == _hoops_GGGCR)
								_hoops_HSSIR[0]--;

							_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
							_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						}

						_hoops_APGCR (a0.bz);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[-1];
						_hoops_HSSIR = &_hoops_HSSIR[-1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_PCSIR = &_hoops_PCSIR[1];
					++row;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = x - pts[1].x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_HSSIR = &_hoops_PCSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					if (a0.bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
						if (_hoops_CCSIR)
							_hoops_HSSIR[0] = a0.bz._hoops_HAGR._hoops_SAGCR;
						else if (_hoops_HSSIR[0] == _hoops_GGGCR)
							_hoops_HSSIR[0]--;

						_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
						_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
					}

					if (--dx <= 0) break;

					_hoops_APGCR (a0.bz);

					_hoops_RPPA = &_hoops_RPPA[-1];
					_hoops_HSSIR = &_hoops_HSSIR[-1];
				}

				goto next;
			}
		}

	  next:
		points += _hoops_RRC;
		if (!single)
			colors++;
	}
#endif
}



/*
 * _hoops_IGGCR _hoops_IRS _hoops_III _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z00_U (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points) {
#ifndef _hoops_RGGCR
	_hoops_RCSIR					pts[2];
	int								_hoops_CRRAR;
	unsigned char alter * const		*_hoops_ACSIR;
	unsigned char					color;
	int								dx;
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;


	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Polyline (nr, count, points);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_SCSIR);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	color = (unsigned char)nr->_hoops_AHP->color._hoops_PGGCR;

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y <= pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			_hoops_CRGCR (pts[0].y, pts[1].y);
		}

		{
			int				row = pts[0].y - _hoops_ICSIR->offset.y;
			int				offset = -_hoops_ICSIR->offset.x;

			_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
			pts[0].x += offset;
			pts[1].x += offset;
		}

		{
			_hoops_IPGCR						a0;
			unsigned char alter				*_hoops_RPPA;
			unsigned int					x;

			_hoops_CRRAR = pts[1].y - pts[0].y;
			dx = pts[1].x - pts[0].x;

			if (_hoops_CRRAR == 0)
				goto _hoops_GAGCR;
			if (dx == 0)
				goto _hoops_RAGCR;
			else if (dx > 0) {
				if (dx > _hoops_CRRAR)
					goto _hoops_AAGCR;
				else
					goto _hoops_RAGCR;
			}
			else {
				dx = -dx;
				if (dx > _hoops_CRRAR)
					goto _hoops_PAGCR;
				else
					goto _hoops_RAGCR;
			}

			/* _hoops_HAR _hoops_GCSPR */

			_hoops_RAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				++_hoops_CRRAR;

				_hoops_PCCAR {
					_hoops_ACSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR] = color;

					if (--_hoops_CRRAR == 0) break;

					_hoops_ACSIR = &_hoops_ACSIR[1];
					_hoops_RPGCR (a0.x);
				}

				goto next;
			}

			_hoops_GAGCR : {
				if (dx < 0) {
					x = pts[1].x;
					dx = -dx;
				}
				else
					x = pts[0].x;

				++dx;

				_hoops_RPPA = &_hoops_ACSIR[0][x];

				switch (dx) {
					case 16: _hoops_RPPA[15] = color; _hoops_HHHI;
					case 15: _hoops_RPPA[14] = color; _hoops_HHHI;
					case 14: _hoops_RPPA[13] = color; _hoops_HHHI;
					case 13: _hoops_RPPA[12] = color; _hoops_HHHI;
					case 12: _hoops_RPPA[11] = color; _hoops_HHHI;
					case 11: _hoops_RPPA[10] = color; _hoops_HHHI;
					case 10: _hoops_RPPA[9]	= color; _hoops_HHHI;
					case  9: _hoops_RPPA[8]	= color; _hoops_HHHI;
					case  8: _hoops_RPPA[7]	= color; _hoops_HHHI;
					case  7: _hoops_RPPA[6]	= color; _hoops_HHHI;
					case  6: _hoops_RPPA[5]	= color; _hoops_HHHI;
					case  5: _hoops_RPPA[4]	= color; _hoops_HHHI;
					case  4: _hoops_RPPA[3]	= color; _hoops_HHHI;
					case  3: _hoops_RPPA[2]	= color; _hoops_HHHI;
					case  2: _hoops_RPPA[1]	= color; _hoops_HHHI;
					case  1: _hoops_RPPA[0]	= color; break;
					case  0: break;

					default: {
						_hoops_PCCAR {
							_hoops_RPPA[0] = color;

							if (--dx <= 0) break;

							_hoops_RPPA = &_hoops_RPPA[1];
						}
					}	break;
				}

				goto next;
			}

			_hoops_AAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;
					_hoops_RPPA = &_hoops_ACSIR[0][x];

					switch (dx) {
						case 16: _hoops_RPPA[15] = color; _hoops_HHHI;
						case 15: _hoops_RPPA[14] = color; _hoops_HHHI;
						case 14: _hoops_RPPA[13] = color; _hoops_HHHI;
						case 13: _hoops_RPPA[12] = color; _hoops_HHHI;
						case 12: _hoops_RPPA[11] = color; _hoops_HHHI;
						case 11: _hoops_RPPA[10] = color; _hoops_HHHI;
						case 10: _hoops_RPPA[9]	= color; _hoops_HHHI;
						case  9: _hoops_RPPA[8]	= color; _hoops_HHHI;
						case  8: _hoops_RPPA[7]	= color; _hoops_HHHI;
						case  7: _hoops_RPPA[6]	= color; _hoops_HHHI;
						case  6: _hoops_RPPA[5]	= color; _hoops_HHHI;
						case  5: _hoops_RPPA[4]	= color; _hoops_HHHI;
						case  4: _hoops_RPPA[3]	= color; _hoops_HHHI;
						case  3: _hoops_RPPA[2]	= color; _hoops_HHHI;
						case  2: _hoops_RPPA[1]	= color; _hoops_HHHI;
						case  1: _hoops_RPPA[0]	= color; break;
						case  0: break;

						default: {
							_hoops_PCCAR {
								_hoops_RPPA[0] = color;

								if (--dx <= 0) break;

								_hoops_RPPA = &_hoops_RPPA[1];
							}
						}	break;
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = pts[1].x - x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];

				switch (dx) {
					case 16: _hoops_RPPA[15] = color; _hoops_HHHI;
					case 15: _hoops_RPPA[14] = color; _hoops_HHHI;
					case 14: _hoops_RPPA[13] = color; _hoops_HHHI;
					case 13: _hoops_RPPA[12] = color; _hoops_HHHI;
					case 12: _hoops_RPPA[11] = color; _hoops_HHHI;
					case 11: _hoops_RPPA[10] = color; _hoops_HHHI;
					case 10: _hoops_RPPA[9]	= color; _hoops_HHHI;
					case  9: _hoops_RPPA[8]	= color; _hoops_HHHI;
					case  8: _hoops_RPPA[7]	= color; _hoops_HHHI;
					case  7: _hoops_RPPA[6]	= color; _hoops_HHHI;
					case  6: _hoops_RPPA[5]	= color; _hoops_HHHI;
					case  5: _hoops_RPPA[4]	= color; _hoops_HHHI;
					case  4: _hoops_RPPA[3]	= color; _hoops_HHHI;
					case  3: _hoops_RPPA[2]	= color; _hoops_HHHI;
					case  2: _hoops_RPPA[1]	= color; _hoops_HHHI;
					case  1: _hoops_RPPA[0]	= color; break;
					case  0: break;

					default: {
						_hoops_PCCAR {
							_hoops_RPPA[0] = color;

							if (--dx <= 0) break;

							_hoops_RPPA = &_hoops_RPPA[1];
						}
					}	break;
				}

				goto next;
			}

			_hoops_PAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = x - a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA = &_hoops_ACSIR[0][x];

					switch (dx) {
						case 16: _hoops_RPPA[-15] = color; _hoops_HHHI;
						case 15: _hoops_RPPA[-14] = color; _hoops_HHHI;
						case 14: _hoops_RPPA[-13] = color; _hoops_HHHI;
						case 13: _hoops_RPPA[-12] = color; _hoops_HHHI;
						case 12: _hoops_RPPA[-11] = color; _hoops_HHHI;
						case 11: _hoops_RPPA[-10] = color; _hoops_HHHI;
						case 10: _hoops_RPPA[-9]	 = color; _hoops_HHHI;
						case  9: _hoops_RPPA[-8]	 = color; _hoops_HHHI;
						case  8: _hoops_RPPA[-7]	 = color; _hoops_HHHI;
						case  7: _hoops_RPPA[-6]	 = color; _hoops_HHHI;
						case  6: _hoops_RPPA[-5]	 = color; _hoops_HHHI;
						case  5: _hoops_RPPA[-4]	 = color; _hoops_HHHI;
						case  4: _hoops_RPPA[-3]	 = color; _hoops_HHHI;
						case  3: _hoops_RPPA[-2]	 = color; _hoops_HHHI;
						case  2: _hoops_RPPA[-1]	 = color; _hoops_HHHI;
						case  1: _hoops_RPPA[ 0]	 = color; break;
						case  0: break;

						default: {
							_hoops_PCCAR {
								_hoops_RPPA[0] = color;

								if (--dx <= 0) break;

								_hoops_RPPA = &_hoops_RPPA[-1];
							}
						}	break;
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = x - pts[1].x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];

				switch (dx) {
					case 16: _hoops_RPPA[-15] = color; _hoops_HHHI;
					case 15: _hoops_RPPA[-14] = color; _hoops_HHHI;
					case 14: _hoops_RPPA[-13] = color; _hoops_HHHI;
					case 13: _hoops_RPPA[-12] = color; _hoops_HHHI;
					case 12: _hoops_RPPA[-11] = color; _hoops_HHHI;
					case 11: _hoops_RPPA[-10] = color; _hoops_HHHI;
					case 10: _hoops_RPPA[-9]	 = color; _hoops_HHHI;
					case  9: _hoops_RPPA[-8]	 = color; _hoops_HHHI;
					case  8: _hoops_RPPA[-7]	 = color; _hoops_HHHI;
					case  7: _hoops_RPPA[-6]	 = color; _hoops_HHHI;
					case  6: _hoops_RPPA[-5]	 = color; _hoops_HHHI;
					case  5: _hoops_RPPA[-4]	 = color; _hoops_HHHI;
					case  4: _hoops_RPPA[-3]	 = color; _hoops_HHHI;
					case  3: _hoops_RPPA[-2]	 = color; _hoops_HHHI;
					case  2: _hoops_RPPA[-1]	 = color; _hoops_HHHI;
					case  1: _hoops_RPPA[ 0]	 = color; break;
					case  0: break;

					default: {
						_hoops_PCCAR {
							_hoops_RPPA[0] = color;

							if (--dx <= 0) break;

							_hoops_RPPA = &_hoops_RPPA[-1];
						}
					}	break;
				}

				goto next;
			}
		}

	  next:
		points += _hoops_RRC;
	}
#endif
}




/*
 * _hoops_IGGCR _hoops_IRIC-_hoops_RCIAR _hoops_III _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z00_G (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors) {
#ifndef _hoops_RGGCR
	_hoops_RCSIR					pts[2];
	_hoops_SGGCR						_hoops_IASGR[2];
	int								_hoops_CRRAR;
	unsigned char alter * const		*_hoops_ACSIR;
	int								dx;
	int								row;
	unsigned short					_hoops_CPGCR;
	_hoops_GRGCR			r, g, b;
	_hoops_SGGCR						_hoops_SPGCR;
	_hoops_GHGCR					result;
	int								_hoops_RHGCR;
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;

	  
	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Gouraud_Polyline (nr, count, points, colors);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0,
			0, 0, 0, 0, _hoops_SCSIR|_hoops_AAIC);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {

		RGBAS32 const	*_hoops_RRGCR = colors;
		int				_hoops_ARGCR;

		if (_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], b)) {
			HD_Buffer_DC_Polyline_C08_Z00_C (nr, 2, points, colors, true);
			goto _hoops_HRGCR;
		}

		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y <= pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);

			_hoops_IASGR[0].r = _hoops_IRGCR (colors[0].r);
			_hoops_IASGR[0].g = _hoops_IRGCR (colors[0].g);
			_hoops_IASGR[0].b = _hoops_IRGCR (colors[0].b);
			_hoops_IASGR[1].r = _hoops_IRGCR (colors[1].r);
			_hoops_IASGR[1].g = _hoops_IRGCR (colors[1].g);
			_hoops_IASGR[1].b = _hoops_IRGCR (colors[1].b);
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			_hoops_CRGCR (pts[0].y, pts[1].y);

			_hoops_IASGR[0].r = _hoops_IRGCR (colors[1].r);
			_hoops_IASGR[0].g = _hoops_IRGCR (colors[1].g);
			_hoops_IASGR[0].b = _hoops_IRGCR (colors[1].b);
			_hoops_IASGR[1].r = _hoops_IRGCR (colors[0].r);
			_hoops_IASGR[1].g = _hoops_IRGCR (colors[0].g);
			_hoops_IASGR[1].b = _hoops_IRGCR (colors[0].b);
		}

		{
			int								offset = -_hoops_ICSIR->offset.x;

			row = pts[0].y - _hoops_ICSIR->offset.y;
			_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
			pts[0].x += offset;
			pts[1].x += offset;
		}

		{
			Display_Context const		*dc;
			int								_hoops_RPIS;

			dc = nr->_hoops_SRA;
			_hoops_RPIS = dc->_hoops_AHGCR.r;
			_hoops_IASGR[0].r = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].r);
			_hoops_IASGR[1].r = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].r);
			_hoops_RPIS = dc->_hoops_AHGCR.g;
			_hoops_IASGR[0].g = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].g);
			_hoops_IASGR[1].g = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].g);
			_hoops_RPIS = dc->_hoops_AHGCR.b;
			_hoops_IASGR[0].b = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].b);
			_hoops_IASGR[1].b = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].b);

			_hoops_SPGCR.r = dc->_hoops_HHGCR.r;
			_hoops_SPGCR.g = dc->_hoops_HHGCR.g;
			_hoops_SPGCR.b = dc->_hoops_HHGCR.b;
			_hoops_RHGCR = dc->_hoops_RHGCR;
		}

		{
			_hoops_IPGCR						a0;
			unsigned char alter				*_hoops_RPPA;
			unsigned int					x;
			unsigned short const			*_hoops_IHGCR;

			_hoops_CRRAR = pts[1].y - pts[0].y;
			dx = pts[1].x - pts[0].x;

			if (_hoops_CRRAR == 0)
				goto _hoops_GAGCR;
			if (dx == 0)
				goto _hoops_RAGCR;
			else if (dx > 0) {
				if (dx > _hoops_CRRAR)
					goto _hoops_AAGCR;
				else
					goto _hoops_RAGCR;
			}
			else {
				dx = -dx;
				if (dx > _hoops_CRRAR)
					goto _hoops_PAGCR;
				else
					goto _hoops_RAGCR;
			}

			/* _hoops_HAR _hoops_GCSPR */

			_hoops_RAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_CRRAR);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_CRRAR);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_CRRAR);

				++_hoops_CRRAR;

				_hoops_PCCAR {
					_hoops_RPPA = &_hoops_ACSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR];
					_hoops_CPGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7][(POINTER_SIZED_INT)_hoops_RPPA & 7];

					result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
					result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
					result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

					_hoops_RPPA[0] = _hoops_RHGCR +
							_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
							_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
							result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;

					if (--_hoops_CRRAR == 0) break;

					_hoops_RPGCR (a0.x);
					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);
					_hoops_ACSIR = &_hoops_ACSIR[1];
					++row;
				}

				goto _hoops_HRGCR;
			}

			_hoops_GAGCR: {
				if (dx < 0) {
					x = pts[1].x;
					dx = -dx;
					_hoops_HAGCR (r, _hoops_IASGR[1].r, _hoops_IASGR[0].r, dx);
					_hoops_HAGCR (g, _hoops_IASGR[1].g, _hoops_IASGR[0].g, dx);
					_hoops_HAGCR (b, _hoops_IASGR[1].b, _hoops_IASGR[0].b, dx);
				}
				else {
					x = pts[0].x;
					_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
					_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
					_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);
				}
				++dx;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];

					result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
					result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
					result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

					_hoops_RPPA[0] = _hoops_RHGCR +
							_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
							_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
							result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;

					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					if (--dx <= 0) break;

					_hoops_RPPA = &_hoops_RPPA[1];
				}

				goto _hoops_HRGCR;
			}

			_hoops_AAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					_hoops_PCCAR {
						_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];

						result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

						_hoops_RPPA[0] = _hoops_RHGCR +
								_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
								_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
								result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;

						_hoops_RPGCR (r);
						_hoops_RPGCR (g);
						_hoops_RPGCR (b);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					++row;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = pts[1].x - x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];

					result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
					result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
					result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

					_hoops_RPPA[0] = _hoops_RHGCR +
							_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
							_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
							result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;

					if (--dx <= 0) break;

					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					_hoops_RPPA = &_hoops_RPPA[1];
				}

				goto _hoops_HRGCR;
			}

			_hoops_PAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_HAGCR (r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, dx);
				_hoops_HAGCR (g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, dx);
				_hoops_HAGCR (b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, dx);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = x - a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					_hoops_PCCAR {
						_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];

						result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
						result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

						_hoops_RPPA[0] = _hoops_RHGCR +
								_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
								_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
								result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;

						_hoops_RPGCR (r);
						_hoops_RPGCR (g);
						_hoops_RPGCR (b);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[-1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					++row;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = x - pts[1].x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];

					result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
					result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
					result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

					_hoops_RPPA[0] = _hoops_RHGCR +
							_hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
							_hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
							result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;

					if (--dx <= 0) break;

					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);

					_hoops_RPPA = &_hoops_RPPA[-1];
				}

				goto _hoops_HRGCR;
			}
		}

_hoops_HRGCR:
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}




/*
 * _hoops_IGGCR _hoops_IRS _hoops_HPGCR _hoops_III _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polyline_C08_Z00_C (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors,
	bool						single) {
#ifndef _hoops_RGGCR
	_hoops_RCSIR					pts[2];
	int								_hoops_CRRAR;
	unsigned char alter * const		*_hoops_ACSIR;
	int								dx;
	unsigned char					_hoops_SHGCR;
	unsigned short					_hoops_CPGCR;
	unsigned short					_hoops_GIGCR, _hoops_RIGCR, d3;		/* _hoops_SICIR */
	unsigned char					_hoops_AIGCR, _hoops_PIGCR, _hoops_HIGCR;		/* _hoops_IIGCR _hoops_CIGCR */
	int								row;
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;

	
	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) || 
		nr->_hoops_AHP->weight > 1 ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS) ) {
		HD_Std_DC_Colorized_Polyline (nr, count, points, colors, single);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0, 
			0, 0, 0, 0, _hoops_SCSIR|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}


#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y <= pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			_hoops_CRGCR (pts[0].y, pts[1].y);
		}

		{
			int								offset = -_hoops_ICSIR->offset.x;

			row = pts[0].y - _hoops_ICSIR->offset.y;
			_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
			pts[0].x += offset;
			pts[1].x += offset;
		}

		{
			Display_Context const		*dc;
			_hoops_SGGCR const				*_hoops_RPIS;
			_hoops_SGGCR const				*_hoops_SPGCR;
			_hoops_GHGCR					result;

			dc = nr->_hoops_SRA;
			_hoops_RPIS = &dc->_hoops_AHGCR;
			_hoops_SPGCR = &dc->_hoops_HHGCR;

			result.r.number = _hoops_PHGCR (_hoops_RPIS->r, colors->r) << 8;
			result.g.number = _hoops_PHGCR (_hoops_RPIS->g, colors->g) << 8;
			result.b.number = _hoops_PHGCR (_hoops_RPIS->b, colors->b) << 8;

			_hoops_SHGCR = dc->_hoops_RHGCR +
				_hoops_PHGCR (_hoops_SPGCR->r, result.r._hoops_CAGCR._hoops_SAGCR) +
				_hoops_PHGCR (_hoops_SPGCR->g, result.g._hoops_CAGCR._hoops_SAGCR) +
				result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP->_hoops_RCSR */ ;

#			define _hoops_SIGCR(_hoops_ICIPR, _hoops_CCIPR, _hoops_GCGCR) do {					\
					_hoops_GIGCR = 0xFFFF - result._hoops_ICIPR._hoops_CAGCR._hoops_RCGCR;				\
					_hoops_RIGCR = 0xFFFF - result._hoops_CCIPR._hoops_CAGCR._hoops_RCGCR;				\
					d3 = 0xFFFF - result._hoops_GCGCR._hoops_CAGCR._hoops_RCGCR;				\
					_hoops_AIGCR = _hoops_SHGCR + _hoops_SPGCR->_hoops_ICIPR;							\
					_hoops_PIGCR = _hoops_AIGCR + _hoops_SPGCR->_hoops_CCIPR;							\
					_hoops_HIGCR = _hoops_PIGCR + _hoops_SPGCR->_hoops_GCGCR;} while (0)

			if (result.r._hoops_CAGCR._hoops_RCGCR >= result.g._hoops_CAGCR._hoops_RCGCR) {
				if (result.g._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
					_hoops_SIGCR (r, g, b);
				else if (result.r._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
					_hoops_SIGCR (r, b, g);
				else
					_hoops_SIGCR (b, r, g);
			}
			else {
				if (result.r._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
					_hoops_SIGCR (g, r, b);
				else if (result.g._hoops_CAGCR._hoops_RCGCR >= result.b._hoops_CAGCR._hoops_RCGCR)
					_hoops_SIGCR (g, b, r);
				else
					_hoops_SIGCR (b, g, r);
			}

#		undef _hoops_SIGCR
		}

		{
			_hoops_IPGCR						a0;
			unsigned char alter				*_hoops_RPPA;
			unsigned int					x;
			unsigned short const			*_hoops_IHGCR;

			_hoops_CRRAR = pts[1].y - pts[0].y;
			dx = pts[1].x - pts[0].x;

			if (_hoops_CRRAR == 0)
				goto _hoops_GAGCR;
			if (dx == 0)
				goto _hoops_RAGCR;
			else if (dx > 0) {
				if (dx > _hoops_CRRAR)
					goto _hoops_AAGCR;
				else
					goto _hoops_RAGCR;
			}
			else {
				dx = -dx;
				if (dx > _hoops_CRRAR)
					goto _hoops_PAGCR;
				else
					goto _hoops_RAGCR;
			}

			/* _hoops_HAR _hoops_GCSPR */

			_hoops_RAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				++_hoops_CRRAR;

				_hoops_PCCAR {
					_hoops_RPPA = &_hoops_ACSIR[0][a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR];
					_hoops_CPGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7][(POINTER_SIZED_INT)_hoops_RPPA & 7];

					_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);

					if (--_hoops_CRRAR == 0) break;

					_hoops_RPGCR (a0.x);
					_hoops_ACSIR = &_hoops_ACSIR[1];
					++row;
				}

				goto next;
			}


			_hoops_GAGCR: {
				if (dx < 0) {
					x = pts[1].x;
					dx = -dx;
				}
				else
					x = pts[0].x;
				++dx;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
					_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);

					if (--dx <= 0) break;

					_hoops_RPPA = &_hoops_RPPA[1];
				}

				goto next;
			}

			_hoops_AAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);

				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					_hoops_PCCAR {
						_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
						_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					++row;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = pts[1].x - x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
					_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);

					if (--dx <= 0) break;

					_hoops_RPPA = &_hoops_RPPA[1];
				}

				goto next;
			}

			_hoops_PAGCR: {
				_hoops_HAGCR (a0.x, pts[0].x, pts[1].x, _hoops_CRRAR);
				x = pts[0].x;
				_hoops_PPGCR (a0.x);

				_hoops_PCCAR {
					dx = x - a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_RPPA = &_hoops_ACSIR[0][x];
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					_hoops_PCCAR {
						_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
						_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);

						if (--dx <= 0) break;

						_hoops_RPPA = &_hoops_RPPA[-1];
					}

					x = a0.x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					_hoops_ACSIR = &_hoops_ACSIR[1];
					++row;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_RPGCR (a0.x);
				}

				dx = x - pts[1].x + 1;
				_hoops_RPPA = &_hoops_ACSIR[0][x];
				_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

				_hoops_PCCAR {
					_hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
					_hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);

					if (--dx <= 0) break;

					_hoops_RPPA = &_hoops_RPPA[-1];
				}

				goto next;
			}
		}

	  next:
		points += _hoops_RRC;
		if (!single)
			colors++;
	}
#endif
}







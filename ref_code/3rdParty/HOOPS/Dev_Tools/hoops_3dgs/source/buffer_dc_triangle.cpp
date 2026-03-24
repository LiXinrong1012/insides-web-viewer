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
 * $Id: obf_tmp.txt 1.38 2010-10-06 19:15:52 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "hd_proto.h"
#include "span.h"
#include "patterns.h"


/*
 * _hoops_IGGCR _hoops_IRS _hoops_SCPH _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z16_U (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points) {
#ifndef _hoops_GCSIR

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Polytriangle (nr, count, points);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_SCSIR);
		return;
	}

	HD_Buffer_DC_Polytris_C24_Z16_C (nr, count, points,
		(RGBAS32 const *)&nr->_hoops_IHA->color, true);
#endif
}



/*
 * _hoops_PPIC _hoops_IGSGR _hoops_IRS _hoops_SCPH _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z16_G (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors) {
#ifndef _hoops_GCSIR
	_hoops_ISGCR					_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	_hoops_SGGCR						_hoops_IASGR[3];
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Gouraud_Polytris (nr, count, points, colors);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 0, 0, 0, 0, _hoops_SCSIR|_hoops_AAIC);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		RGBAS32 const	*_hoops_RRGCR = colors;
		int				_hoops_ARGCR;

		if (_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], b) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], b)) {
			HD_Buffer_DC_Polytris_C24_Z16_C (nr, 3, points, colors, true);
			goto _hoops_GGRCR;
		}

		LOAD_ARGUMENT (points);
		TRUNCATE_3_POINTS (points, pts, 0, 1, 2, y);

		/* _hoops_GHSGR : _hoops_RGRCR->_hoops_HAPC <= _hoops_IIHHR->_hoops_HAPC <= _hoops_CIHHR->_hoops_HAPC */
		{
			int						temp;
			if (pts[0].y <= pts[1].y) {
				if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, x);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, z);
					_hoops_AGRCR (colors, _hoops_IASGR, 0, 1, 2);
				}
				else if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, x);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, z);
					_hoops_CRGCR (pts[2].y, pts[1].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 0, 2, 1);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, x);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, z);
					temp = pts[0].y; pts[0].y = pts[2].y; pts[2].y = pts[1].y; pts[1].y = temp;
					_hoops_AGRCR (colors, _hoops_IASGR, 2, 0, 1);
				}
			}
			else {
				if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, x);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, z);
					_hoops_CRGCR (pts[1].y, pts[0].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 1, 0, 2);
				}
				else if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, x);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, z);
					temp = pts[1].y; pts[1].y = pts[2].y; pts[2].y = pts[0].y; pts[0].y = temp;
					_hoops_AGRCR (colors, _hoops_IASGR, 1, 2, 0);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, x);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, z);
					_hoops_CRGCR (pts[2].y, pts[0].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 2, 1, 0);
				}
			}
		}

		if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
			_hoops_ISGCR alter			*left;
			_hoops_ISGCR alter			*right;
			_hoops_RAAH alter					*_hoops_HSSIR;
			RGBAS32 alter				*_hoops_RPPA;
			_hoops_RAAH alter * const			*_hoops_PCSIR;
			RGBAS32 alter * const		*_hoops_ACSIR;
			unsigned int					x;
			int								dx;
			_hoops_RSGCR		bz;
			_hoops_GHGCR					result;
			_hoops_GRGCR			r, g, b;

			{
				int						row = pts[0].y - _hoops_ICSIR->offset.y;
				int						offset = -_hoops_ICSIR->offset.x;

				_hoops_ACSIR = &((_hoops_CSSIR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
				_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[row];
				pts[0].x += offset;
				pts[1].x += offset;
				pts[2].x += offset;

				offset = (int)((nr->transform_rendition->_hoops_CHIH +
								nr->transform_rendition->_hoops_SHIH) *
							   _hoops_ISSIR(nr->transform_rendition));


				pts[0].z += offset;
				pts[1].z += offset;
				pts[2].z += offset;
			}

			_hoops_HAGCR (_hoops_CSGCR.x, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_IAGCR (_hoops_CSGCR.bz, pts[0].z, pts[2].z, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.r, _hoops_IASGR[0].r, _hoops_IASGR[2].r, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.g, _hoops_IASGR[0].g, _hoops_IASGR[2].g, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.b, _hoops_IASGR[0].b, _hoops_IASGR[2].b, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[0].z, pts[1].z, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HGRCR.number <= _hoops_CSGCR.x._hoops_HGRCR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_HSSIR = &_hoops_PCSIR[0][x];
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  bz._hoops_HAGR._hoops_SAGCR = (left->bz._hoops_HAGR._hoops_SAGCR >> 1) +
											 (right->bz._hoops_HAGR._hoops_SAGCR >> 1);
							  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[1]) {
								  _hoops_HSSIR[1] = bz._hoops_HAGR._hoops_SAGCR;

								  result.r.number = (left->r._hoops_HAGR.number	 >> 1) +
													(right->r._hoops_HAGR.number >> 1);
								  result.g.number = (left->g._hoops_HAGR.number	 >> 1) +
													(right->g._hoops_HAGR.number >> 1);
								  result.b.number = (left->b._hoops_HAGR.number	 >> 1) +
													(right->b._hoops_HAGR.number >> 1);

								  _hoops_RPPA[1].r = (unsigned char)result.r._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[1].g = (unsigned char)result.g._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[1].b = (unsigned char)result.b._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[1].a = _hoops_GPGCR;
							  }
						  } _hoops_HHHI;

						  case 1: {
							  if (left->bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
								  if (_hoops_CCSIR)
									  _hoops_HSSIR[0] = left->bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

								  _hoops_RPPA[0].r = (unsigned char)left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].g = (unsigned char)left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].b = (unsigned char)left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].a = _hoops_GPGCR;
							  }
						  }	  break;

						  default: {
							  _hoops_IAGCR (bz,
										   left->bz._hoops_HAGR._hoops_SAGCR,
										   right->bz._hoops_HAGR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (r,
										   left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (g,
										   left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (b,
										   left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
									  if (_hoops_CCSIR)
										  _hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

									  _hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
									  _hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
									  _hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
									  _hoops_RPPA[0].a = _hoops_GPGCR;
								  }

								  if (--dx == 0)
									  break;

								  _hoops_APGCR (bz);
								  _hoops_RPGCR (r);
								  _hoops_RPGCR (g);
								  _hoops_RPGCR (b);
								  ++_hoops_HSSIR;
								  ++_hoops_RPPA;
							  }
						  }	  break;
						}
					}

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_RPGCR (_hoops_CSGCR.r);
					_hoops_RPGCR (_hoops_CSGCR.g);
					_hoops_RPGCR (_hoops_CSGCR.b);
					++_hoops_PCSIR;
					++_hoops_ACSIR;
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_APGCR (_hoops_SSGCR.bz);
					_hoops_RPGCR (_hoops_SSGCR.r);
					_hoops_RPGCR (_hoops_SSGCR.g);
					_hoops_RPGCR (_hoops_SSGCR.b);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[1].z, pts[2].z, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.r, _hoops_IASGR[1].r, _hoops_IASGR[2].r, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.g, _hoops_IASGR[1].g, _hoops_IASGR[2].g, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.b, _hoops_IASGR[1].b, _hoops_IASGR[2].b, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HAGR.number < _hoops_CSGCR.x._hoops_HAGR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_HSSIR = &_hoops_PCSIR[0][x];
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  bz._hoops_HAGR._hoops_SAGCR = (left->bz._hoops_HAGR._hoops_SAGCR >> 1) +
											 (right->bz._hoops_HAGR._hoops_SAGCR >> 1);
							  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[1]) {
								  _hoops_HSSIR[1] = bz._hoops_HAGR._hoops_SAGCR;

								  result.r.number = (left->r._hoops_HAGR.number	 >> 1) +
													(right->r._hoops_HAGR.number >> 1);
								  result.g.number = (left->g._hoops_HAGR.number	 >> 1) +
													(right->g._hoops_HAGR.number >> 1);
								  result.b.number = (left->b._hoops_HAGR.number	 >> 1) +
													(right->b._hoops_HAGR.number >> 1);

								  _hoops_RPPA[1].r = (unsigned char)result.r._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[1].g = (unsigned char)result.g._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[1].b = (unsigned char)result.b._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[1].a = _hoops_GPGCR;
							  }
						  } _hoops_HHHI;

						  case 1: {
							  if (left->bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
								  if (_hoops_CCSIR)
									  _hoops_HSSIR[0] = left->bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

								  _hoops_RPPA[0].r = (unsigned char)left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].g = (unsigned char)left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].b = (unsigned char)left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].a = _hoops_GPGCR;
							  }
						  }	  break;

						  default: {
							  _hoops_IAGCR (bz,
										   left->bz._hoops_HAGR._hoops_SAGCR,
										   right->bz._hoops_HAGR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (r,
										   left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (g,
										   left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (b,
										   left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
									  if (_hoops_CCSIR)
										  _hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

									  _hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
									  _hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
									  _hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
									  _hoops_RPPA[0].a = _hoops_GPGCR;
								  }

								  if (--dx == 0)
									  break;

								  _hoops_APGCR (bz);
								  _hoops_RPGCR (r);
								  _hoops_RPGCR (g);
								  _hoops_RPGCR (b);
								  ++_hoops_HSSIR;
								  ++_hoops_RPPA;
							  }
						  }	  break;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_RPGCR (_hoops_CSGCR.r);
					_hoops_RPGCR (_hoops_CSGCR.g);
					_hoops_RPGCR (_hoops_CSGCR.b);
					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_APGCR (_hoops_SSGCR.bz);
					_hoops_RPGCR (_hoops_SSGCR.r);
					_hoops_RPGCR (_hoops_SSGCR.g);
					_hoops_RPGCR (_hoops_SSGCR.b);
					++_hoops_PCSIR;
					++_hoops_ACSIR;
				}
			}
		}
_hoops_GGRCR:
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}




/*
 * _hoops_IGGCR _hoops_IRS _hoops_HPGCR _hoops_SCPH _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR.
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z16_C (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors,
	bool						single) {
#ifndef _hoops_GCSIR
	_hoops_SRGCR					_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Colorized_Polytris (nr, count, points, colors, single);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 
			0, 0, 0, 0, _hoops_SCSIR|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}


#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_3_POINTS (points, pts, 0, 1, 2, y);

		/* _hoops_GHSGR : _hoops_RGRCR->_hoops_HAPC <= _hoops_IIHHR->_hoops_HAPC <= _hoops_CIHHR->_hoops_HAPC */
		{
			int						temp;
			if (pts[0].y <= pts[1].y) {
				if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, x);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, z);
				}
				else if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, x);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, z);
					_hoops_CRGCR (pts[2].y, pts[1].y);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, x);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, z);
					temp = pts[0].y; pts[0].y = pts[2].y; pts[2].y = pts[1].y; pts[1].y = temp;
				}
			}
			else {
				if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, x);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, z);
					_hoops_CRGCR (pts[1].y, pts[0].y);
				}
				else if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, x);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, z);
					temp = pts[1].y; pts[1].y = pts[2].y; pts[2].y = pts[0].y; pts[0].y = temp;
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, x);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, z);
					_hoops_CRGCR (pts[2].y, pts[0].y);
				}
			}
		}

		if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
			_hoops_SRGCR alter				*left;
			_hoops_SRGCR alter				*right;
			_hoops_RAAH alter					*_hoops_HSSIR;
			RGBAS32 alter				*_hoops_RPPA;
			_hoops_RAAH alter * const			*_hoops_PCSIR;
			RGBAS32 alter * const		*_hoops_ACSIR;
			unsigned int					x;
			int								dx;
			_hoops_RSGCR		bz;
			RGBAS32						color = *colors;
			int								row = pts[0].y - _hoops_ICSIR->offset.y;
			int								offset;

			_hoops_ACSIR = &((_hoops_CSSIR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
			_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[row];
			pts[0].x += -_hoops_ICSIR->offset.x;
			pts[1].x += -_hoops_ICSIR->offset.x;
			pts[2].x += -_hoops_ICSIR->offset.x;

			offset = (int)((nr->transform_rendition->_hoops_CHIH +
							nr->transform_rendition->_hoops_SHIH) *
						   _hoops_ISSIR(nr->transform_rendition));
			pts[0].z += offset;
			pts[1].z += offset;
			pts[2].z += offset;

			_hoops_HAGCR (_hoops_CSGCR.x, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_IAGCR (_hoops_CSGCR.bz, pts[0].z, pts[2].z, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[0].z, pts[1].z, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HGRCR.number <= _hoops_CSGCR.x._hoops_HGRCR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_HSSIR = &_hoops_PCSIR[0][x];
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  bz._hoops_HAGR._hoops_SAGCR = (left->bz._hoops_HAGR._hoops_SAGCR >> 1) +
											 (right->bz._hoops_HAGR._hoops_SAGCR >> 1);
							  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[1]) {
								  _hoops_HSSIR[1] = bz._hoops_HAGR._hoops_SAGCR;
								  _hoops_RPPA[1] = color;
							  }
						  } _hoops_HHHI;

						  case 1: {
							  if (left->bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
								  if (_hoops_CCSIR)
									  _hoops_HSSIR[0] = left->bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

								  _hoops_RPPA[0] = color;
							  }
						  }	  break;

						  default: {
							  _hoops_IAGCR (bz,
										   left->bz._hoops_HAGR._hoops_SAGCR,
										   right->bz._hoops_HAGR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
									  if (_hoops_CCSIR)
										  _hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

									  _hoops_RPPA[0] = color;
								  }

								  if (--dx == 0)
									  break;

								  _hoops_APGCR (bz);
								  _hoops_HSSIR = &_hoops_HSSIR[1];
								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_PCSIR = &_hoops_PCSIR[1];
					_hoops_ACSIR = &_hoops_ACSIR[1];
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_APGCR (_hoops_SSGCR.bz);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[1].z, pts[2].z, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HAGR.number < _hoops_CSGCR.x._hoops_HAGR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_HSSIR = &_hoops_PCSIR[0][x];
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  bz._hoops_HAGR._hoops_SAGCR = (left->bz._hoops_HAGR._hoops_SAGCR >> 1) +
											 (right->bz._hoops_HAGR._hoops_SAGCR >> 1);
							  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[1]) {
								  _hoops_HSSIR[1] = bz._hoops_HAGR._hoops_SAGCR;
								  _hoops_RPPA[1] = color;
							  }
						  } _hoops_HHHI;

						  case 1: {
							  if (left->bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
								  if (_hoops_CCSIR)
									  _hoops_HSSIR[0] = left->bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

								  _hoops_RPPA[0] = color;
							  }
						  }	  break;

						  default: {
							  _hoops_IAGCR (bz,
										   left->bz._hoops_HAGR._hoops_SAGCR,
										   right->bz._hoops_HAGR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
									  if (_hoops_CCSIR)
										  _hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

									  _hoops_RPPA[0] = color;
								  }

								  if (--dx == 0)
									  break;

								  _hoops_APGCR (bz);
								  _hoops_HSSIR = &_hoops_HSSIR[1];
								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_APGCR (_hoops_SSGCR.bz);
					_hoops_PCSIR = &_hoops_PCSIR[1];
					_hoops_ACSIR = &_hoops_ACSIR[1];
				}
			}
		}

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
#endif
}




/*
 * _hoops_IGGCR _hoops_IRS _hoops_SCPH _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z00_U (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points) {
#ifndef _hoops_RGGCR

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Polytriangle (nr, count, points);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_SCSIR);
		return;
	}


	HD_Buffer_DC_Polytris_C24_Z00_C (nr, count, points,
		(RGBAS32 const *)&nr->_hoops_IHA->color, true);
#endif
}




/*
 * _hoops_PPIC _hoops_IGSGR _hoops_IRS _hoops_SCPH _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z00_G (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors) {
#ifndef _hoops_RGGCR
	_hoops_ISGCR					_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	_hoops_SGGCR						_hoops_IASGR[3];
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;


	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Gouraud_Polytris (nr, count, points, colors);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 0, 0, 0, 0, _hoops_SCSIR|_hoops_AAIC);
		return;
	}


#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		RGBAS32 const	*_hoops_RRGCR = colors;
		int				_hoops_ARGCR;

		if (_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], b) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], b)) {
			HD_Buffer_DC_Polytris_C24_Z00_C (nr, 3, points, colors, true);
			goto _hoops_GGRCR;
		}

		LOAD_ARGUMENT (points);
		TRUNCATE_3_POINTS (points, pts, 0, 1, 2, y);

		/* _hoops_GHSGR : _hoops_RGRCR->_hoops_HAPC <= _hoops_IIHHR->_hoops_HAPC <= _hoops_CIHHR->_hoops_HAPC */
		{
			int						temp;
			if (pts[0].y <= pts[1].y) {
				if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, x);
					_hoops_AGRCR (colors, _hoops_IASGR, 0, 1, 2);
				}
				else if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, x);
					_hoops_CRGCR (pts[2].y, pts[1].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 0, 2, 1);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, x);
					temp = pts[0].y; pts[0].y = pts[2].y; pts[2].y = pts[1].y; pts[1].y = temp;
					_hoops_AGRCR (colors, _hoops_IASGR, 2, 0, 1);
				}
			}
			else {
				if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, x);
					_hoops_CRGCR (pts[1].y, pts[0].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 1, 0, 2);
				}
				else if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, x);
					temp = pts[1].y; pts[1].y = pts[2].y; pts[2].y = pts[0].y; pts[0].y = temp;
					_hoops_AGRCR (colors, _hoops_IASGR, 1, 2, 0);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, x);
					_hoops_CRGCR (pts[2].y, pts[0].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 2, 1, 0);
				}
			}
		}

		if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
			_hoops_ISGCR alter			*left;
			_hoops_ISGCR alter			*right;
			RGBAS32 alter				*_hoops_RPPA;
			RGBAS32 alter * const		*_hoops_ACSIR;
			unsigned int					x;
			int								dx;
			_hoops_GHGCR					result;
			_hoops_GRGCR			r, g, b;

			{
				int						row = pts[0].y - _hoops_ICSIR->offset.y;
				int						offset = -_hoops_ICSIR->offset.x;

				_hoops_ACSIR = &((_hoops_CSSIR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
				pts[0].x += offset;
				pts[1].x += offset;
				pts[2].x += offset;
			}

			_hoops_HAGCR (_hoops_CSGCR.x, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.r, _hoops_IASGR[0].r, _hoops_IASGR[2].r, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.g, _hoops_IASGR[0].g, _hoops_IASGR[2].g, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.b, _hoops_IASGR[0].b, _hoops_IASGR[2].b, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HGRCR.number <= _hoops_CSGCR.x._hoops_HGRCR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  result.r.number = (left->r._hoops_HAGR.number	 >> 1) +
												(right->r._hoops_HAGR.number >> 1);
							  result.g.number = (left->g._hoops_HAGR.number	 >> 1) +
												(right->g._hoops_HAGR.number >> 1);
							  result.b.number = (left->b._hoops_HAGR.number	 >> 1) +
												(right->b._hoops_HAGR.number >> 1);

							  _hoops_RPPA[1].r = (unsigned char)result.r._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[1].g = (unsigned char)result.g._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[1].b = (unsigned char)result.b._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[1].a = _hoops_GPGCR;
						  } _hoops_HHHI;

						  case 1: {
							  _hoops_RPPA[0].r = (unsigned char)left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[0].g = (unsigned char)left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[0].b = (unsigned char)left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[0].a = _hoops_GPGCR;
						  }	  break;

						  default: {
							  _hoops_HAGCR (r,
										   left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (g,
										   left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (b,
										   left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  _hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].a = _hoops_GPGCR;

								  if (--dx == 0)
									  break;

								  _hoops_RPGCR (r);
								  _hoops_RPGCR (g);
								  _hoops_RPGCR (b);
								  ++_hoops_RPPA;
							  }
						  }	  break;
						}
					}

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_RPGCR (_hoops_CSGCR.r);
					_hoops_RPGCR (_hoops_CSGCR.g);
					_hoops_RPGCR (_hoops_CSGCR.b);
					++_hoops_ACSIR;
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_RPGCR (_hoops_SSGCR.r);
					_hoops_RPGCR (_hoops_SSGCR.g);
					_hoops_RPGCR (_hoops_SSGCR.b);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.r, _hoops_IASGR[1].r, _hoops_IASGR[2].r, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.g, _hoops_IASGR[1].g, _hoops_IASGR[2].g, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.b, _hoops_IASGR[1].b, _hoops_IASGR[2].b, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HAGR.number < _hoops_CSGCR.x._hoops_HAGR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  result.r.number = (left->r._hoops_HAGR.number	 >> 1) +
												(right->r._hoops_HAGR.number >> 1);
							  result.g.number = (left->g._hoops_HAGR.number	 >> 1) +
												(right->g._hoops_HAGR.number >> 1);
							  result.b.number = (left->b._hoops_HAGR.number	 >> 1) +
												(right->b._hoops_HAGR.number >> 1);

							  _hoops_RPPA[1].r = (unsigned char)result.r._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[1].g = (unsigned char)result.g._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[1].b = (unsigned char)result.b._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[1].a = _hoops_GPGCR;
						  } _hoops_HHHI;

						  case 1: {
							  _hoops_RPPA[0].r = (unsigned char)left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[0].g = (unsigned char)left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[0].b = (unsigned char)left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							  _hoops_RPPA[0].a = _hoops_GPGCR;
						  }	  break;

						  default: {
							  _hoops_HAGCR (r,
										   left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (g,
										   left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (b,
										   left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  _hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
								  _hoops_RPPA[0].a = _hoops_GPGCR;

								  if (--dx == 0)
									  break;

								  _hoops_RPGCR (r);
								  _hoops_RPGCR (g);
								  _hoops_RPGCR (b);
								  ++_hoops_RPPA;
							  }
						  }	  break;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_RPGCR (_hoops_CSGCR.r);
					_hoops_RPGCR (_hoops_CSGCR.g);
					_hoops_RPGCR (_hoops_CSGCR.b);
					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_RPGCR (_hoops_SSGCR.r);
					_hoops_RPGCR (_hoops_SSGCR.g);
					_hoops_RPGCR (_hoops_SSGCR.b);
					++_hoops_ACSIR;
				}
			}
		}
_hoops_GGRCR:
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}




/*
 * _hoops_IGGCR _hoops_IRS _hoops_HPGCR _hoops_SCPH _hoops_CRGR _hoops_IRS 24 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C24_Z00_C (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors,
	bool						single) {
#ifndef _hoops_RGGCR
	_hoops_IPGCR						_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Colorized_Polytris (nr, count, points, colors, single);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0,
			0, 0, 0, 0, _hoops_SCSIR|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}


#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_3_POINTS (points, pts, 0, 1, 2, y);

		/* _hoops_GHSGR : _hoops_RGRCR->_hoops_HAPC <= _hoops_IIHHR->_hoops_HAPC <= _hoops_CIHHR->_hoops_HAPC */
		{
			int						temp;
			if (pts[0].y <= pts[1].y) {
				if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, x);
				}
				else if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, x);
					_hoops_CRGCR (pts[2].y, pts[1].y);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, x);
					temp = pts[0].y; pts[0].y = pts[2].y; pts[2].y = pts[1].y; pts[1].y = temp;
				}
			}
			else {
				if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, x);
					_hoops_CRGCR (pts[1].y, pts[0].y);
				}
				else if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, x);
					temp = pts[1].y; pts[1].y = pts[2].y; pts[2].y = pts[0].y; pts[0].y = temp;
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, x);
					_hoops_CRGCR (pts[2].y, pts[0].y);
				}
			}
		}

		if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
			_hoops_IPGCR alter				*left;
			_hoops_IPGCR alter				*right;
			RGBAS32 alter				*_hoops_RPPA;
			RGBAS32 alter * const		*_hoops_ACSIR;
			unsigned int					x;
			int								dx;
			RGBAS32						color = *colors;

			{
				int						row = pts[0].y - _hoops_ICSIR->offset.y;
				int						offset = -_hoops_ICSIR->offset.x;

				_hoops_ACSIR = &((_hoops_CSSIR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
				pts[0].x += offset;
				pts[1].x += offset;
				pts[2].x += offset;
			}

			_hoops_HAGCR (_hoops_CSGCR.x, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HGRCR.number <= _hoops_CSGCR.x._hoops_HGRCR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  _hoops_RPPA[1] = color;
						  } _hoops_HHHI;

						  case 1: {
							  _hoops_RPPA[0] = color;
						  }	  break;

						  default: {
							  _hoops_PCCAR {
								  _hoops_RPPA[0] = color;

								  if (--dx == 0)
									  break;
								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_ACSIR = &_hoops_ACSIR[1];
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_SSGCR.x);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HAGR.number < _hoops_CSGCR.x._hoops_HAGR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  _hoops_RPPA[1] = color;
						  } _hoops_HHHI;

						  case 1: {
							  _hoops_RPPA[0] = color;
						  }	  break;

						  default: {
							  _hoops_PCCAR {
								  _hoops_RPPA[0] = color;

								  if (--dx == 0)
									  break;
								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_ACSIR = &_hoops_ACSIR[1];
				}
			}
		}

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
#endif
}



/*
 * _hoops_IGGCR _hoops_IRS _hoops_SCPH _hoops_CRGR _hoops_IRS 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z16_U (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points) {
#ifndef _hoops_GCSIR
	_hoops_SRGCR					_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;
	unsigned char					color;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Polytriangle (nr, count, points);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_SCSIR);
		return;
	}


#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	color = (unsigned char)nr->_hoops_IHA->color._hoops_PGGCR;

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_3_POINTS (points, pts, 0, 1, 2, y);

		/* _hoops_GHSGR : _hoops_RGRCR->_hoops_HAPC <= _hoops_IIHHR->_hoops_HAPC <= _hoops_CIHHR->_hoops_HAPC */
		{
			int						temp;
			if (pts[0].y <= pts[1].y) {
				if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, x);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, z);
				}
				else if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, x);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, z);
					_hoops_CRGCR (pts[2].y, pts[1].y);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, x);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, z);
					temp = pts[0].y; pts[0].y = pts[2].y; pts[2].y = pts[1].y; pts[1].y = temp;
				}
			}
			else {
				if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, x);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, z);
					_hoops_CRGCR (pts[1].y, pts[0].y);
				}
				else if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, x);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, z);
					temp = pts[1].y; pts[1].y = pts[2].y; pts[2].y = pts[0].y; pts[0].y = temp;
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, x);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, z);
					_hoops_CRGCR (pts[2].y, pts[0].y);
				}
			}
		}

		if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
			_hoops_SRGCR alter				*left;
			_hoops_SRGCR alter				*right;
			_hoops_RAAH alter					*_hoops_HSSIR;
			unsigned char alter				*_hoops_RPPA;
			_hoops_RAAH alter * const			*_hoops_PCSIR;
			unsigned char alter * const		*_hoops_ACSIR;
			unsigned int					x;
			int								dx;
			_hoops_RSGCR		bz;

			{
				int						row = pts[0].y-_hoops_ICSIR->offset.y;
				int						offset = -_hoops_ICSIR->offset.x;

				_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
				_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[row];
				pts[0].x += offset;
				pts[1].x += offset;
				pts[2].x += offset;

				offset = (int)((nr->transform_rendition->_hoops_CHIH +
								nr->transform_rendition->_hoops_SHIH) *
							   _hoops_ISSIR(nr->transform_rendition));
				pts[0].z += offset;
				pts[1].z += offset;
				pts[2].z += offset;
			}

			_hoops_HAGCR (_hoops_CSGCR.x, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_IAGCR (_hoops_CSGCR.bz, pts[0].z, pts[2].z, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[0].z, pts[1].z, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HGRCR.number <= _hoops_CSGCR.x._hoops_HGRCR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_HSSIR = &_hoops_PCSIR[0][x];
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  bz._hoops_HAGR._hoops_SAGCR = (left->bz._hoops_HAGR._hoops_SAGCR >> 1) +
											 (right->bz._hoops_HAGR._hoops_SAGCR >> 1);
							  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[1]) {
								  _hoops_HSSIR[1] = bz._hoops_HAGR._hoops_SAGCR;
								  _hoops_RPPA[1] = color;
							  }
						  } _hoops_HHHI;

						  case 1: {
							  if (left->bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
								  if (_hoops_CCSIR)
									  _hoops_HSSIR[0] = left->bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

								  _hoops_RPPA[0] = color;
							  }
						  }	  break;

						  default: {
							  _hoops_IAGCR (bz,
										   left->bz._hoops_HAGR._hoops_SAGCR,
										   right->bz._hoops_HAGR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
									  if (_hoops_CCSIR)
										  _hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

									  _hoops_RPPA[0] = color;
								  }

								  if (--dx == 0)
									  break;

								  _hoops_APGCR (bz);
								  _hoops_HSSIR = &_hoops_HSSIR[1];
								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_PCSIR = &_hoops_PCSIR[1];
					_hoops_ACSIR = &_hoops_ACSIR[1];
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_APGCR (_hoops_SSGCR.bz);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[1].z, pts[2].z, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HAGR.number < _hoops_CSGCR.x._hoops_HAGR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_HSSIR = &_hoops_PCSIR[0][x];
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  bz._hoops_HAGR._hoops_SAGCR = (left->bz._hoops_HAGR._hoops_SAGCR >> 1) +
											 (right->bz._hoops_HAGR._hoops_SAGCR >> 1);
							  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[1]) {
								  _hoops_HSSIR[1] = bz._hoops_HAGR._hoops_SAGCR;
								  _hoops_RPPA[1] = color;
							  }
						  } _hoops_HHHI;

						  case 1: {
							  if (left->bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
								  if (_hoops_CCSIR)
									  _hoops_HSSIR[0] = left->bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

								  _hoops_RPPA[0] = color;
							  }
						  }	  break;

						  default: {
							  _hoops_IAGCR (bz,
										   left->bz._hoops_HAGR._hoops_SAGCR,
										   right->bz._hoops_HAGR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
									  if (_hoops_CCSIR)
										  _hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

									  _hoops_RPPA[0] = color;
								  }

								  if (--dx == 0)
									  break;

								  _hoops_APGCR (bz);
								  _hoops_HSSIR = &_hoops_HSSIR[1];
								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_APGCR (_hoops_SSGCR.bz);
					_hoops_PCSIR = &_hoops_PCSIR[1];
					_hoops_ACSIR = &_hoops_ACSIR[1];
				}
			}
		}

		points += _hoops_RRC;
	}
#endif
}


/*
 * _hoops_PPIC _hoops_IGSGR _hoops_IRS _hoops_SCPH _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z16_G (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors) {
#ifndef _hoops_GCSIR
	_hoops_ISGCR					_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	_hoops_SGGCR						_hoops_IASGR[3];
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Gouraud_Polytris (nr, count, points, colors);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 0, 0, 0, 0, _hoops_SCSIR|_hoops_AAIC);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		RGBAS32 const	*_hoops_RRGCR = colors;
		int				_hoops_ARGCR;

		if (_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], b) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], b)) {
			HD_Buffer_DC_Polytris_C08_Z16_C (nr, 3, points, colors, true);
			goto _hoops_GGRCR;
		}

		LOAD_ARGUMENT (points);
		TRUNCATE_3_POINTS (points, pts, 0, 1, 2, y);

		/* _hoops_GHSGR : _hoops_RGRCR->_hoops_HAPC <= _hoops_IIHHR->_hoops_HAPC <= _hoops_CIHHR->_hoops_HAPC */
		{
			int						temp;
			if (pts[0].y <= pts[1].y) {
				if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, x);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, z);
					_hoops_AGRCR (colors, _hoops_IASGR, 0, 1, 2);
				}
				else if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, x);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, z);
					_hoops_CRGCR (pts[2].y, pts[1].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 0, 2, 1);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, x);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, z);
					temp = pts[0].y; pts[0].y = pts[2].y; pts[2].y = pts[1].y; pts[1].y = temp;
					_hoops_AGRCR (colors, _hoops_IASGR, 2, 0, 1);
				}
			}
			else {
				if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, x);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, z);
					_hoops_CRGCR (pts[1].y, pts[0].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 1, 0, 2);
				}
				else if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, x);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, z);
					temp = pts[1].y; pts[1].y = pts[2].y; pts[2].y = pts[0].y; pts[0].y = temp;
					_hoops_AGRCR (colors, _hoops_IASGR, 1, 2, 0);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, x);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, z);
					_hoops_CRGCR (pts[2].y, pts[0].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 2, 1, 0);
				}
			}
		}

		if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
			_hoops_ISGCR alter			*left;
			_hoops_ISGCR alter			*right;
			_hoops_RAAH alter					*_hoops_HSSIR;
			unsigned char alter				*_hoops_RPPA;
			_hoops_RAAH alter * const			*_hoops_PCSIR;
			unsigned char alter * const		*_hoops_ACSIR;
			unsigned int					x;
			int								dx;
			_hoops_RSGCR		bz;
			_hoops_SGGCR						_hoops_SPGCR;
			_hoops_GHGCR					result;
			int								row;
			int								_hoops_RHGCR;
			unsigned short const			*_hoops_IHGCR;
			unsigned short					_hoops_CPGCR;
			_hoops_GRGCR			r, g, b;

			{
				int						offset = -_hoops_ICSIR->offset.x;

				row = pts[0].y - _hoops_ICSIR->offset.y;
				_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
				_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[row];
				pts[0].x += offset;
				pts[1].x += offset;
				pts[2].x += offset;

				offset = (int)((nr->transform_rendition->_hoops_CHIH +
								nr->transform_rendition->_hoops_SHIH) *
							   _hoops_ISSIR(nr->transform_rendition));
				pts[0].z += offset;
				pts[1].z += offset;
				pts[2].z += offset;
			}

			{
				Display_Context const		*dc;
				int								_hoops_RPIS;

				dc = nr->_hoops_SRA;
				_hoops_RPIS = dc->_hoops_AHGCR.r;
				_hoops_IASGR[0].r = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].r);
				_hoops_IASGR[1].r = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].r);
				_hoops_IASGR[2].r = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[2].r);
				_hoops_RPIS = dc->_hoops_AHGCR.g;
				_hoops_IASGR[0].g = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].g);
				_hoops_IASGR[1].g = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].g);
				_hoops_IASGR[2].g = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[2].g);
				_hoops_RPIS = dc->_hoops_AHGCR.b;
				_hoops_IASGR[0].b = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].b);
				_hoops_IASGR[1].b = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].b);
				_hoops_IASGR[2].b = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[2].b);

				_hoops_SPGCR.r = dc->_hoops_HHGCR.r;
				_hoops_SPGCR.g = dc->_hoops_HHGCR.g;
				_hoops_SPGCR.b = dc->_hoops_HHGCR.b;
				_hoops_RHGCR = dc->_hoops_RHGCR;
			}

			_hoops_HAGCR (_hoops_CSGCR.x, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_IAGCR (_hoops_CSGCR.bz, pts[0].z, pts[2].z, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.r, _hoops_IASGR[0].r, _hoops_IASGR[2].r, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.g, _hoops_IASGR[0].g, _hoops_IASGR[2].g, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.b, _hoops_IASGR[0].b, _hoops_IASGR[2].b, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[0].z, pts[1].z, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HGRCR.number <= _hoops_CSGCR.x._hoops_HGRCR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_HSSIR = &_hoops_PCSIR[0][x];
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  bz._hoops_HAGR._hoops_SAGCR = (left->bz._hoops_HAGR._hoops_SAGCR >> 1) +
											 (right->bz._hoops_HAGR._hoops_SAGCR >> 1);
							  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[1]) {
								  _hoops_HSSIR[1] = bz._hoops_HAGR._hoops_SAGCR;

								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[1] & 7];
								  result.r.number = (left->r._hoops_HAGR.number	 >> 9) +
													(right->r._hoops_HAGR.number >> 9) + _hoops_CPGCR;
								  result.g.number = (left->g._hoops_HAGR.number	 >> 9) +
													(right->g._hoops_HAGR.number >> 9) + _hoops_CPGCR;
								  result.b.number = (left->b._hoops_HAGR.number	 >> 9) +
													(right->b._hoops_HAGR.number >> 9) + _hoops_CPGCR;

								  _hoops_RPPA[1] = _hoops_RHGCR +
										  _hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
										  _hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
										  result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
							  }
						  } _hoops_HHHI;

						  case 1: {
							  if (left->bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
								  if (_hoops_CCSIR)
									  _hoops_HSSIR[0] = left->bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
								  result.r.number = (left->r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
								  result.g.number = (left->g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
								  result.b.number = (left->b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

								  _hoops_RPPA[0] = _hoops_RHGCR +
										  _hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
										  _hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
										  result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
							  }
						  }	  break;

						  default: {
							  _hoops_IAGCR (bz,
										   left->bz._hoops_HAGR._hoops_SAGCR,
										   right->bz._hoops_HAGR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (r,
										   left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (g,
										   left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (b,
										   left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
									  if (_hoops_CCSIR)
										  _hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
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

								  if (--dx == 0)
									  break;

								  _hoops_APGCR (bz);
								  _hoops_RPGCR (r);
								  _hoops_RPGCR (g);
								  _hoops_RPGCR (b);
								  ++_hoops_HSSIR;
								  ++_hoops_RPPA;
							  }
						  }	  break;
						}
					}

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_RPGCR (_hoops_CSGCR.r);
					_hoops_RPGCR (_hoops_CSGCR.g);
					_hoops_RPGCR (_hoops_CSGCR.b);
					++_hoops_PCSIR;
					++_hoops_ACSIR;
					++row;
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_APGCR (_hoops_SSGCR.bz);
					_hoops_RPGCR (_hoops_SSGCR.r);
					_hoops_RPGCR (_hoops_SSGCR.g);
					_hoops_RPGCR (_hoops_SSGCR.b);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[1].z, pts[2].z, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.r, _hoops_IASGR[1].r, _hoops_IASGR[2].r, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.g, _hoops_IASGR[1].g, _hoops_IASGR[2].g, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.b, _hoops_IASGR[1].b, _hoops_IASGR[2].b, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HAGR.number < _hoops_CSGCR.x._hoops_HAGR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_HSSIR = &_hoops_PCSIR[0][x];
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  bz._hoops_HAGR._hoops_SAGCR = (left->bz._hoops_HAGR._hoops_SAGCR >> 1) +
											 (right->bz._hoops_HAGR._hoops_SAGCR >> 1);
							  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[1]) {
								  _hoops_HSSIR[1] = bz._hoops_HAGR._hoops_SAGCR;

								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[1] & 7];
								  result.r.number = (left->r._hoops_HAGR.number	 >> 9) +
													(right->r._hoops_HAGR.number >> 9) + _hoops_CPGCR;
								  result.g.number = (left->g._hoops_HAGR.number	 >> 9) +
													(right->g._hoops_HAGR.number >> 9) + _hoops_CPGCR;
								  result.b.number = (left->b._hoops_HAGR.number	 >> 9) +
													(right->b._hoops_HAGR.number >> 9) + _hoops_CPGCR;

								  _hoops_RPPA[1] = _hoops_RHGCR +
										  _hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
										  _hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
										  result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
							  }
						  } _hoops_HHHI;

						  case 1: {
							  if (left->bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
								  if (_hoops_CCSIR)
									  _hoops_HSSIR[0] = left->bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
								  result.r.number = (left->r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
								  result.g.number = (left->g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
								  result.b.number = (left->b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

								  _hoops_RPPA[0] = _hoops_RHGCR +
										  _hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
										  _hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
										  result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
							  }
						  }	  break;

						  default: {
							  _hoops_IAGCR (bz,
										   left->bz._hoops_HAGR._hoops_SAGCR,
										   right->bz._hoops_HAGR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (r,
										   left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (g,
										   left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (b,
										   left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
									  if (_hoops_CCSIR)
										  _hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
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

								  if (--dx == 0)
									  break;

								  _hoops_APGCR (bz);
								  _hoops_RPGCR (r);
								  _hoops_RPGCR (g);
								  _hoops_RPGCR (b);
								  ++_hoops_HSSIR;
								  ++_hoops_RPPA;
							  }
						  }	  break;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_RPGCR (_hoops_CSGCR.r);
					_hoops_RPGCR (_hoops_CSGCR.g);
					_hoops_RPGCR (_hoops_CSGCR.b);
					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_APGCR (_hoops_SSGCR.bz);
					_hoops_RPGCR (_hoops_SSGCR.r);
					_hoops_RPGCR (_hoops_SSGCR.g);
					_hoops_RPGCR (_hoops_SSGCR.b);
					++_hoops_PCSIR;
					++_hoops_ACSIR;
					++row;
				}
			}
		}
_hoops_GGRCR:
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}




/*
 * _hoops_IGGCR _hoops_IRS _hoops_HPGCR _hoops_SCPH _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 * _hoops_PPR 16 _hoops_IGRH _hoops_HCH _hoops_SRHR.
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z16_C (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors,
	bool						single) {
#ifndef _hoops_GCSIR
	_hoops_SRGCR					_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;
	bool						_hoops_CCSIR = !BIT(nr->transform_rendition->flags, _hoops_ISH);

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Colorized_Polytris (nr, count, points, colors, single);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0,
			0, 0, 0, 0, _hoops_SCSIR|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}


#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_3_POINTS (points, pts, 0, 1, 2, y);

		/* _hoops_GHSGR : _hoops_RGRCR->_hoops_HAPC <= _hoops_IIHHR->_hoops_HAPC <= _hoops_CIHHR->_hoops_HAPC */
		{
			int						temp;
			if (pts[0].y <= pts[1].y) {
				if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, x);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, z);
				}
				else if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, x);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, z);
					_hoops_CRGCR (pts[2].y, pts[1].y);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, x);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, z);
					temp = pts[0].y; pts[0].y = pts[2].y; pts[2].y = pts[1].y; pts[1].y = temp;
				}
			}
			else {
				if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, x);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, z);
					_hoops_CRGCR (pts[1].y, pts[0].y);
				}
				else if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, x);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, z);
					temp = pts[1].y; pts[1].y = pts[2].y; pts[2].y = pts[0].y; pts[0].y = temp;
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, x);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, z);
					_hoops_CRGCR (pts[2].y, pts[0].y);
				}
			}
		}

		if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
			_hoops_SRGCR alter				*left;
			_hoops_SRGCR alter				*right;
			_hoops_RAAH alter					*_hoops_HSSIR;
			unsigned char alter				*_hoops_RPPA;
			_hoops_RAAH alter * const			*_hoops_PCSIR;
			unsigned char alter * const		*_hoops_ACSIR;
			unsigned int					x;
			int								dx;
			_hoops_RSGCR		bz;
			unsigned char					_hoops_SHGCR;
			int								row;
			unsigned short const			*_hoops_IHGCR;
			unsigned short					_hoops_CPGCR;
			unsigned short					_hoops_GIGCR, _hoops_RIGCR, d3;		/* _hoops_SICIR */
			unsigned char					_hoops_AIGCR, _hoops_PIGCR, _hoops_HIGCR;		/* _hoops_IIGCR _hoops_CIGCR */

			{
				int						offset = -_hoops_ICSIR->offset.x;

				row = pts[0].y - _hoops_ICSIR->offset.y;
				_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
				_hoops_PCSIR = &((_hoops_SSSIR)_hoops_ICSIR->depth_buffer->_hoops_RCPIR)[row];
				pts[0].x += offset;
				pts[1].x += offset;
				pts[2].x += offset;

				offset = (int)((nr->transform_rendition->_hoops_CHIH +
								nr->transform_rendition->_hoops_SHIH) *
							   _hoops_ISSIR(nr->transform_rendition));
				pts[0].z += offset;
				pts[1].z += offset;
				pts[2].z += offset;
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

#				define _hoops_SIGCR(_hoops_ICIPR, _hoops_CCIPR, _hoops_GCGCR) do {						\
					_hoops_GIGCR = 0xFFFF - result._hoops_ICIPR._hoops_CAGCR._hoops_RCGCR;				\
					_hoops_RIGCR = 0xFFFF - result._hoops_CCIPR._hoops_CAGCR._hoops_RCGCR;				\
					d3 = 0xFFFF - result._hoops_GCGCR._hoops_CAGCR._hoops_RCGCR;				\
					_hoops_AIGCR = _hoops_SHGCR + _hoops_SPGCR->_hoops_ICIPR;					\
					_hoops_PIGCR = _hoops_AIGCR + _hoops_SPGCR->_hoops_CCIPR;					\
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

#				undef _hoops_SIGCR
			}

			_hoops_HAGCR (_hoops_CSGCR.x, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_IAGCR (_hoops_CSGCR.bz, pts[0].z, pts[2].z, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[0].z, pts[1].z, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HGRCR.number <= _hoops_CSGCR.x._hoops_HGRCR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_HSSIR = &_hoops_PCSIR[0][x];
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  bz._hoops_HAGR._hoops_SAGCR = (left->bz._hoops_HAGR._hoops_SAGCR >> 1) +
											 (right->bz._hoops_HAGR._hoops_SAGCR >> 1);
							  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[1]) {
								  _hoops_HSSIR[1] = bz._hoops_HAGR._hoops_SAGCR;
								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[1] & 7];
								  _hoops_RPPA[1] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
							  }
						  } _hoops_HHHI;

						  case 1: {
							  if (left->bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
								  if (_hoops_CCSIR)
									  _hoops_HSSIR[0] = left->bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
								  _hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
							  }
						  }	  break;

						  default: {
							  _hoops_IAGCR (bz,
										   left->bz._hoops_HAGR._hoops_SAGCR,
										   right->bz._hoops_HAGR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
									  if (_hoops_CCSIR)
										  _hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
									  else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

									  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
									  _hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
								  }

								  if (--dx == 0)
									  break;

								  _hoops_APGCR (bz);
								  _hoops_HSSIR = &_hoops_HSSIR[1];
								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_PCSIR = &_hoops_PCSIR[1];
					_hoops_ACSIR = &_hoops_ACSIR[1];
					++row;
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_APGCR (_hoops_SSGCR.bz);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[1].z, pts[2].z, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HAGR.number < _hoops_CSGCR.x._hoops_HAGR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_HSSIR = &_hoops_PCSIR[0][x];
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  bz._hoops_HAGR._hoops_SAGCR = (left->bz._hoops_HAGR._hoops_SAGCR >> 1) +
											 (right->bz._hoops_HAGR._hoops_SAGCR >> 1);
							  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[1]) {
								  _hoops_HSSIR[1] = bz._hoops_HAGR._hoops_SAGCR;
								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[1] & 7];
								  _hoops_RPPA[1] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
							  }
						  } _hoops_HHHI;

						  case 1: {
							  if (left->bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
								  if (_hoops_CCSIR)
									  _hoops_HSSIR[0] = left->bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
								  _hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
							  }
						  }	  break;

						  default: {
							  _hoops_IAGCR (bz,
										   left->bz._hoops_HAGR._hoops_SAGCR,
										   right->bz._hoops_HAGR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  if (bz._hoops_HAGR._hoops_SAGCR <= _hoops_HSSIR[0]) {
									  if (_hoops_CCSIR)
										  _hoops_HSSIR[0] = bz._hoops_HAGR._hoops_SAGCR;
									else if (_hoops_HSSIR[0] == _hoops_GGGCR)
										_hoops_HSSIR[0]--;

									  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
									  _hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
								  }

								  if (--dx == 0)
									  break;

								  _hoops_APGCR (bz);
								  _hoops_HSSIR = &_hoops_HSSIR[1];
								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_APGCR (_hoops_SSGCR.bz);
					_hoops_PCSIR = &_hoops_PCSIR[1];
					_hoops_ACSIR = &_hoops_ACSIR[1];
					++row;
				}
			}
		}

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
#endif
}



/*
 * _hoops_IGGCR _hoops_IRS _hoops_SCPH _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z00_U (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points) {
#ifndef _hoops_RGGCR
	_hoops_IPGCR						_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;
	unsigned char					color;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Polytriangle (nr, count, points);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_SCSIR);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	color = (unsigned char)nr->_hoops_IHA->color._hoops_PGGCR;

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_3_POINTS (points, pts, 0, 1, 2, y);

		/* _hoops_GHSGR : _hoops_RGRCR->_hoops_HAPC <= _hoops_IIHHR->_hoops_HAPC <= _hoops_CIHHR->_hoops_HAPC */
		{
			int						temp;
			if (pts[0].y <= pts[1].y) {
				if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, x);
				}
				else if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, x);
					_hoops_CRGCR (pts[2].y, pts[1].y);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, x);
					temp = pts[0].y; pts[0].y = pts[2].y; pts[2].y = pts[1].y; pts[1].y = temp;
				}
			}
			else {
				if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, x);
					_hoops_CRGCR (pts[1].y, pts[0].y);
				}
				else if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, x);
					temp = pts[1].y; pts[1].y = pts[2].y; pts[2].y = pts[0].y; pts[0].y = temp;
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, x);
					_hoops_CRGCR (pts[2].y, pts[0].y);
				}
			}
		}

		if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
			_hoops_IPGCR alter				*left;
			_hoops_IPGCR alter				*right;
			unsigned char alter				*_hoops_RPPA;
			unsigned char alter * const		*_hoops_ACSIR;
			unsigned int					x;
			int								dx;

			{
				int						row = pts[0].y - _hoops_ICSIR->offset.y;
				int						offset = -_hoops_ICSIR->offset.x;

				_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
				pts[0].x += offset;
				pts[1].x += offset;
				pts[2].x += offset;
			}

			_hoops_HAGCR (_hoops_CSGCR.x, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HGRCR.number <= _hoops_CSGCR.x._hoops_HGRCR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 8: _hoops_RPPA[7] = color;
						  case 7: _hoops_RPPA[6] = color;
						  case 6: _hoops_RPPA[5] = color;
						  case 5: _hoops_RPPA[4] = color;
						  case 4: _hoops_RPPA[3] = color;
						  case 3: _hoops_RPPA[2] = color;
						  case 2: _hoops_RPPA[1] = color;
						  case 1: _hoops_RPPA[0] = color; break;

						  default: {
							  _hoops_PCCAR {
								  _hoops_RPPA[0] = color;

								  if (--dx == 0)
									  break;

								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_ACSIR = &_hoops_ACSIR[1];
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_SSGCR.x);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HAGR.number < _hoops_CSGCR.x._hoops_HAGR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 8: _hoops_RPPA[7] = color;
						  case 7: _hoops_RPPA[6] = color;
						  case 6: _hoops_RPPA[5] = color;
						  case 5: _hoops_RPPA[4] = color;
						  case 4: _hoops_RPPA[3] = color;
						  case 3: _hoops_RPPA[2] = color;
						  case 2: _hoops_RPPA[1] = color;
						  case 1: _hoops_RPPA[0] = color; break;

						  default: {
							  _hoops_PCCAR {
								  _hoops_RPPA[0] = color;

								  if (--dx == 0)
									  break;

								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_ACSIR = &_hoops_ACSIR[1];
				}
			}
		}

		points += _hoops_RRC;
	}
#endif
}




/*
 * _hoops_PPIC _hoops_IGSGR _hoops_IRS _hoops_SCPH _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z00_G (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors) {
#ifndef _hoops_RGGCR
	_hoops_ISGCR					_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	_hoops_SGGCR						_hoops_IASGR[3];
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;


	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Gouraud_Polytris (nr, count, points, colors);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 0, 0, 0, 0, _hoops_SCSIR|_hoops_AAIC);
		return;
	}


#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		RGBAS32 const	*_hoops_RRGCR = colors;
		int				_hoops_ARGCR;

		if (_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], b) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], b)) {
			HD_Buffer_DC_Polytris_C08_Z00_C (nr, 3, points, colors, true);
			goto _hoops_GGRCR;
		}

		LOAD_ARGUMENT (points);
		TRUNCATE_3_POINTS (points, pts, 0, 1, 2, y);

		/* _hoops_GHSGR : _hoops_RGRCR->_hoops_HAPC <= _hoops_IIHHR->_hoops_HAPC <= _hoops_CIHHR->_hoops_HAPC */
		{
			int						temp;
			if (pts[0].y <= pts[1].y) {
				if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, x);
					_hoops_AGRCR (colors, _hoops_IASGR, 0, 1, 2);
				}
				else if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, x);
					_hoops_CRGCR (pts[2].y, pts[1].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 0, 2, 1);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, x);
					temp = pts[0].y; pts[0].y = pts[2].y; pts[2].y = pts[1].y; pts[1].y = temp;
					_hoops_AGRCR (colors, _hoops_IASGR, 2, 0, 1);
				}
			}
			else {
				if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, x);
					_hoops_CRGCR (pts[1].y, pts[0].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 1, 0, 2);
				}
				else if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, x);
					temp = pts[1].y; pts[1].y = pts[2].y; pts[2].y = pts[0].y; pts[0].y = temp;
					_hoops_AGRCR (colors, _hoops_IASGR, 1, 2, 0);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, x);
					_hoops_CRGCR (pts[2].y, pts[0].y);
					_hoops_AGRCR (colors, _hoops_IASGR, 2, 1, 0);
				}
			}
		}

		if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
			_hoops_ISGCR alter			*left;
			_hoops_ISGCR alter			*right;
			unsigned char alter				*_hoops_RPPA;
			unsigned char alter * const		*_hoops_ACSIR;
			unsigned int					x;
			int								dx;
			_hoops_SGGCR						_hoops_SPGCR;
			_hoops_GHGCR					result;
			int								row;
			int								_hoops_RHGCR;
			unsigned short const			*_hoops_IHGCR;
			unsigned short					_hoops_CPGCR;
			_hoops_GRGCR			r, g, b;

			{
				int						offset = -_hoops_ICSIR->offset.x;

				row = pts[0].y - _hoops_ICSIR->offset.y;
				_hoops_ACSIR = &((_hoops_HGGCR) _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
				pts[0].x += offset;
				pts[1].x += offset;
				pts[2].x += offset;
			}

			{
				Display_Context const		*dc;
				int								_hoops_RPIS;

				dc = nr->_hoops_SRA;
				_hoops_RPIS = dc->_hoops_AHGCR.r;
				_hoops_IASGR[0].r = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].r);
				_hoops_IASGR[1].r = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].r);
				_hoops_IASGR[2].r = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[2].r);
				_hoops_RPIS = dc->_hoops_AHGCR.g;
				_hoops_IASGR[0].g = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].g);
				_hoops_IASGR[1].g = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].g);
				_hoops_IASGR[2].g = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[2].g);
				_hoops_RPIS = dc->_hoops_AHGCR.b;
				_hoops_IASGR[0].b = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[0].b);
				_hoops_IASGR[1].b = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[1].b);
				_hoops_IASGR[2].b = _hoops_PHGCR (_hoops_RPIS, _hoops_IASGR[2].b);

				_hoops_SPGCR.r = dc->_hoops_HHGCR.r;
				_hoops_SPGCR.g = dc->_hoops_HHGCR.g;
				_hoops_SPGCR.b = dc->_hoops_HHGCR.b;
				_hoops_RHGCR = dc->_hoops_RHGCR;
			}

			_hoops_HAGCR (_hoops_CSGCR.x, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.r, _hoops_IASGR[0].r, _hoops_IASGR[2].r, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.g, _hoops_IASGR[0].g, _hoops_IASGR[2].g, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.b, _hoops_IASGR[0].b, _hoops_IASGR[2].b, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HGRCR.number <= _hoops_CSGCR.x._hoops_HGRCR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[1] & 7];
							  result.r.number = (left->r._hoops_HAGR.number	 >> 9) +
												(right->r._hoops_HAGR.number >> 9) + _hoops_CPGCR;
							  result.g.number = (left->g._hoops_HAGR.number	 >> 9) +
												(right->g._hoops_HAGR.number >> 9) + _hoops_CPGCR;
							  result.b.number = (left->b._hoops_HAGR.number	 >> 9) +
												(right->b._hoops_HAGR.number >> 9) + _hoops_CPGCR;

							  _hoops_RPPA[1] = _hoops_RHGCR +
									  _hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
									  _hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
									  result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
						  } _hoops_HHHI;

						  case 1: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
							  result.r.number = (left->r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
							  result.g.number = (left->g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
							  result.b.number = (left->b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

							  _hoops_RPPA[0] = _hoops_RHGCR +
									  _hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
									  _hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
									  result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
						  }	  break;

						  default: {
							  _hoops_HAGCR (r,
										   left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (g,
										   left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (b,
										   left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
								  result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
								  result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
								  result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

								  _hoops_RPPA[0] = _hoops_RHGCR +
										  _hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
										  _hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
										  result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;

								  if (--dx == 0)
									  break;

								  _hoops_RPGCR (r);
								  _hoops_RPGCR (g);
								  _hoops_RPGCR (b);
								  ++_hoops_RPPA;
							  }
						  }	  break;
						}
					}

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_RPGCR (_hoops_CSGCR.r);
					_hoops_RPGCR (_hoops_CSGCR.g);
					_hoops_RPGCR (_hoops_CSGCR.b);
					++_hoops_ACSIR;
					++row;
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_RPGCR (_hoops_SSGCR.r);
					_hoops_RPGCR (_hoops_SSGCR.g);
					_hoops_RPGCR (_hoops_SSGCR.b);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.r, _hoops_IASGR[1].r, _hoops_IASGR[2].r, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.g, _hoops_IASGR[1].g, _hoops_IASGR[2].g, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.b, _hoops_IASGR[1].b, _hoops_IASGR[2].b, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HAGR.number < _hoops_CSGCR.x._hoops_HAGR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 2: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[1] & 7];
							  result.r.number = (left->r._hoops_HAGR.number	 >> 9) +
												(right->r._hoops_HAGR.number >> 9) + _hoops_CPGCR;
							  result.g.number = (left->g._hoops_HAGR.number	 >> 9) +
												(right->g._hoops_HAGR.number >> 9) + _hoops_CPGCR;
							  result.b.number = (left->b._hoops_HAGR.number	 >> 9) +
												(right->b._hoops_HAGR.number >> 9) + _hoops_CPGCR;

							  _hoops_RPPA[1] = _hoops_RHGCR +
									  _hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
									  _hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
									  result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
						  } _hoops_HHHI;

						  case 1: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
							  result.r.number = (left->r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
							  result.g.number = (left->g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
							  result.b.number = (left->b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

							  _hoops_RPPA[0] = _hoops_RHGCR +
									  _hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
									  _hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
									  result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;
						  }	  break;

						  default: {
							  _hoops_HAGCR (r,
										   left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (g,
										   left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);
							  _hoops_HAGCR (b,
										   left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   right->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
										   dx);

							  _hoops_PCCAR {
								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
								  result.r.number = (r._hoops_HAGR.number >> 8) + _hoops_CPGCR;
								  result.g.number = (g._hoops_HAGR.number >> 8) + _hoops_CPGCR;
								  result.b.number = (b._hoops_HAGR.number >> 8) + _hoops_CPGCR;

								  _hoops_RPPA[0] = _hoops_RHGCR +
										  _hoops_PHGCR (_hoops_SPGCR.r, result.r._hoops_CAGCR._hoops_SAGCR) +
										  _hoops_PHGCR (_hoops_SPGCR.g, result.g._hoops_CAGCR._hoops_SAGCR) +
										  result.b._hoops_CAGCR._hoops_SAGCR /* * _hoops_CHGP._hoops_RCSR */;

								  if (--dx == 0)
									  break;

								  _hoops_RPGCR (r);
								  _hoops_RPGCR (g);
								  _hoops_RPGCR (b);
								  ++_hoops_RPPA;
							  }
						  }	  break;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_RPGCR (_hoops_CSGCR.r);
					_hoops_RPGCR (_hoops_CSGCR.g);
					_hoops_RPGCR (_hoops_CSGCR.b);
					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_RPGCR (_hoops_SSGCR.r);
					_hoops_RPGCR (_hoops_SSGCR.g);
					_hoops_RPGCR (_hoops_SSGCR.b);
					++_hoops_ACSIR;
					++row;
				}
			}
		}
_hoops_GGRCR:
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}



/*
 * _hoops_IGGCR _hoops_IRS _hoops_HPGCR _hoops_SCPH _hoops_CRGR _hoops_PCCP 8 _hoops_IGRH _hoops_HAIR _hoops_SRHR
 */
GLOBAL_FUNCTION void HD_Buffer_DC_Polytris_C08_Z00_C (
	Net_Rendition const & nr,
	int								count,
	DC_Point const				*points,
	RGBAS32 const				*colors,
	bool						single) {
#ifndef _hoops_RGGCR
	_hoops_IPGCR						_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	int								_hoops_RRC;
	_hoops_HCSIR const		*_hoops_ICSIR;

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Colorized_Polytris (nr, count, points, colors, single);
		return;
	}

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS) ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 
			0, 0, 0, 0, _hoops_SCSIR|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_3_POINTS (points, pts, 0, 1, 2, y);

		/* _hoops_GHSGR : _hoops_RGRCR->_hoops_HAPC <= _hoops_IIHHR->_hoops_HAPC <= _hoops_CIHHR->_hoops_HAPC */
		{
			int						temp;

			if (pts[0].y <= pts[1].y) {
				if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 1, 2, x);
				}
				else if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, x);
					_hoops_CRGCR (pts[2].y, pts[1].y);
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, x);
					temp = pts[0].y; pts[0].y = pts[2].y; pts[2].y = pts[1].y; pts[1].y = temp;
				}
			}
			else {
				if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, x);
					_hoops_CRGCR (pts[1].y, pts[0].y);
				}
				else if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, x);
					temp = pts[1].y; pts[1].y = pts[2].y; pts[2].y = pts[0].y; pts[0].y = temp;
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, x);
					_hoops_CRGCR (pts[2].y, pts[0].y);
				}
			}
		}

		if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
			_hoops_IPGCR alter				*left;
			_hoops_IPGCR alter				*right;
			unsigned char alter				*_hoops_RPPA;
			unsigned char alter * const		*_hoops_ACSIR;
			unsigned int					x;
			int								dx;
			unsigned char					_hoops_SHGCR;
			int								row;
			unsigned short const			*_hoops_IHGCR;
			unsigned short					_hoops_CPGCR;
			unsigned short					_hoops_GIGCR, _hoops_RIGCR, d3;		/* _hoops_SICIR */
			unsigned char					_hoops_AIGCR, _hoops_PIGCR, _hoops_HIGCR;		/* _hoops_IIGCR _hoops_CIGCR */

			{
				int						offset = -_hoops_ICSIR->offset.x;

				row = pts[0].y - _hoops_ICSIR->offset.y;
				_hoops_ACSIR = &((_hoops_HGGCR)_hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[row];
				pts[0].x += offset;
				pts[1].x += offset;
				pts[2].x += offset;
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

#				define _hoops_SIGCR(_hoops_ICIPR, _hoops_CCIPR, _hoops_GCGCR) do {						\
					_hoops_GIGCR = 0xFFFF - result._hoops_ICIPR._hoops_CAGCR._hoops_RCGCR;				\
					_hoops_RIGCR = 0xFFFF - result._hoops_CCIPR._hoops_CAGCR._hoops_RCGCR;				\
					d3 = 0xFFFF - result._hoops_GCGCR._hoops_CAGCR._hoops_RCGCR;				\
					_hoops_AIGCR = _hoops_SHGCR + _hoops_SPGCR->_hoops_ICIPR;					\
					_hoops_PIGCR = _hoops_AIGCR + _hoops_SPGCR->_hoops_CCIPR;					\
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

#				undef _hoops_SIGCR
			}

			_hoops_HAGCR (_hoops_CSGCR.x, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HGRCR.number <= _hoops_CSGCR.x._hoops_HGRCR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 8: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[7] & 7];
							  _hoops_RPPA[7] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 7: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[6] & 7];
							  _hoops_RPPA[6] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 6: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[5] & 7];
							  _hoops_RPPA[5] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 5: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[4] & 7];
							  _hoops_RPPA[4] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 4: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[3] & 7];
							  _hoops_RPPA[3] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 3: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[2] & 7];
							  _hoops_RPPA[2] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 2: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[1] & 7];
							  _hoops_RPPA[1] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 1: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
							  _hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  }	  break;

						  default: {
							  _hoops_PCCAR {
								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
								  _hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);

								  if (--dx == 0)
									  break;

								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_ACSIR = &_hoops_ACSIR[1];
					++row;
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_SSGCR.x);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_HAGCR (_hoops_SSGCR.x, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.x._hoops_HAGR.number < _hoops_CSGCR.x._hoops_HAGR.number) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					_hoops_IHGCR = HOOPS_READ_ONLY._hoops_CHGCR[row & 7];

					x = left->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					dx = right->x._hoops_HAGR._hoops_CAGCR._hoops_SAGCR - x;

					if (dx > 0) {
						_hoops_RPPA = &_hoops_ACSIR[0][x];

						switch (dx) {
						  case 8: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[7] & 7];
							  _hoops_RPPA[7] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 7: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[6] & 7];
							  _hoops_RPPA[6] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 6: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[5] & 7];
							  _hoops_RPPA[5] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 5: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[4] & 7];
							  _hoops_RPPA[4] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 4: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[3] & 7];
							  _hoops_RPPA[3] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 3: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[2] & 7];
							  _hoops_RPPA[2] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 2: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)&_hoops_RPPA[1] & 7];
							  _hoops_RPPA[1] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  } _hoops_HHHI;

						  case 1: {
							  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
							  _hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);
						  }	  break;

						  default: {
							  _hoops_PCCAR {
								  _hoops_CPGCR = _hoops_IHGCR[(POINTER_SIZED_INT)_hoops_RPPA & 7];
								  _hoops_RPPA[0] = _hoops_ACGCR (_hoops_CPGCR, _hoops_SHGCR, _hoops_GIGCR, _hoops_AIGCR, _hoops_RIGCR, _hoops_PIGCR, d3, _hoops_HIGCR);

								  if (--dx == 0)
									  break;

								  _hoops_RPPA = &_hoops_RPPA[1];
							  }
						  }	  break;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_RPGCR (_hoops_CSGCR.x);
					_hoops_RPGCR (_hoops_SSGCR.x);
					_hoops_ACSIR = &_hoops_ACSIR[1];
					++row;
				}
			}
		}

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
#endif
}





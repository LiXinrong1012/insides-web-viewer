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
 * $Id: obf_tmp.txt 1.108 2010-06-04 21:37:19 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "phdraw.h"
#include "database.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "tandt.h"
#include "span.h"


GLOBAL_FUNCTION void HD_Span_DC_Polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
#ifndef DISABLE_RASTERIZER
	_hoops_ISGCR					_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	int							_hoops_RRC;

	if (nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_RHGGA|_hoops_GPHC);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

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
			_hoops_ISGCR alter *			left;
			_hoops_ISGCR alter *			right;
			_hoops_GHISP				_hoops_RHISP;
			_hoops_AHISP						_hoops_CGIHS[_hoops_GGIHS];
			_hoops_AHISP alter *				_hoops_SGIHS;
			_hoops_AHISP alter *				span;
			int							y;
			Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;
			int							offset;

			_hoops_RHISP.color = nr->_hoops_IHA->color;
			_hoops_RHISP._hoops_PIHSR = nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR;
			_hoops_RHISP.contrast_color = nr->_hoops_IHA->contrast_color;
			_hoops_RHISP.pattern = nr->_hoops_IHA->pattern;

			span = _hoops_CGIHS;
			_hoops_SGIHS = _hoops_CGIHS+_hoops_GGAPR(_hoops_CGIHS);
			y = pts[0].y;

			offset = (int)((nr->transform_rendition->_hoops_CHIH +
							nr->transform_rendition->_hoops_SHIH) *
						   _hoops_ISSIR(nr->transform_rendition));
			pts[0].z += offset;
			pts[1].z += offset;
			pts[2].z += offset;

			_hoops_IAGCR (_hoops_CSGCR.bx, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_IAGCR (_hoops_CSGCR.bz, pts[0].z, pts[2].z, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_IAGCR (_hoops_SSGCR.bx, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[0].z, pts[1].z, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.bx._hoops_HGRCR.simple <= _hoops_CSGCR.bx._hoops_HGRCR.simple) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = left->bx._hoops_HAGR._hoops_SAGCR;
						span->right.bx._hoops_HAGR._hoops_SAGCR = right->bx._hoops_HAGR._hoops_SAGCR;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = left->bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = right->bz._hoops_HAGR._hoops_SAGCR;
							++span;
							if (span == _hoops_SGIHS) {
								int			rows = _hoops_GGIHS;

								_hoops_HRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
						}
						else {
							if (span != _hoops_CGIHS) {
								int			rows = span - _hoops_CGIHS;

								_hoops_HRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
							++y;
						}
					}

					_hoops_APGCR (_hoops_CSGCR.bx);
					_hoops_APGCR (_hoops_CSGCR.bz);
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_APGCR (_hoops_SSGCR.bx);
					_hoops_APGCR (_hoops_SSGCR.bz);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_IAGCR (_hoops_SSGCR.bx, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[1].z, pts[2].z, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.bx._hoops_HAGR._hoops_SAGCR < _hoops_CSGCR.bx._hoops_HAGR._hoops_SAGCR) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = left->bx._hoops_HAGR._hoops_SAGCR;
						span->right.bx._hoops_HAGR._hoops_SAGCR = right->bx._hoops_HAGR._hoops_SAGCR;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = left->bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = right->bz._hoops_HAGR._hoops_SAGCR;
							++span;
							if (span == _hoops_SGIHS) {
								int			rows = _hoops_GGIHS;

								_hoops_HRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
						}
						else {
							if (span != _hoops_CGIHS) {
								int			rows = span - _hoops_CGIHS;

								_hoops_HRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
							++y;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_APGCR (_hoops_CSGCR.bx);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_APGCR (_hoops_SSGCR.bx);
					_hoops_APGCR (_hoops_SSGCR.bz);
				}
			}

			if (span != _hoops_CGIHS) {
				int			rows = span - _hoops_CGIHS;

				_hoops_HRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
			}
		}

		points += _hoops_RRC;
	}
#endif
}



GLOBAL_FUNCTION void HD_Span_DC_Colorized_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				_hoops_IASGR,
	bool						single) {
#ifndef DISABLE_RASTERIZER
	_hoops_ISGCR					_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	int							_hoops_RRC;


	if (nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, _hoops_IASGR, 0,
								 0, 0, 0, 0, _hoops_RHGGA|_hoops_GPHC|
												(single ? _hoops_RAIC : _hoops_PAIC));
		return;
	}


#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

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
			_hoops_ISGCR alter *			left;
			_hoops_ISGCR alter *			right;
			_hoops_GHISP				_hoops_RHISP;
			_hoops_AHISP						_hoops_CGIHS[_hoops_GGIHS];
			_hoops_AHISP alter *				_hoops_SGIHS;
			_hoops_AHISP alter *				span;
			int							y;
			Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;
			int							offset;

			_hoops_RHISP.color = *_hoops_IASGR;
			_hoops_RHISP._hoops_PIHSR = _hoops_HIHSR;
			_hoops_RHISP.contrast_color = nr->_hoops_IHA->contrast_color;
			_hoops_RHISP.pattern = nr->_hoops_IHA->pattern;

			span = _hoops_CGIHS;
			_hoops_SGIHS = _hoops_CGIHS+_hoops_GGAPR(_hoops_CGIHS);
			y = pts[0].y;

			offset = (int)((nr->transform_rendition->_hoops_CHIH +
							nr->transform_rendition->_hoops_SHIH) *
						   _hoops_ISSIR(nr->transform_rendition));
			pts[0].z += offset;
			pts[1].z += offset;
			pts[2].z += offset;

			_hoops_IAGCR (_hoops_CSGCR.bx, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_IAGCR (_hoops_CSGCR.bz, pts[0].z, pts[2].z, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_IAGCR (_hoops_SSGCR.bx, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[0].z, pts[1].z, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.bx._hoops_HGRCR.simple <= _hoops_CSGCR.bx._hoops_HGRCR.simple) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = left->bx._hoops_HAGR._hoops_SAGCR;
						span->right.bx._hoops_HAGR._hoops_SAGCR = right->bx._hoops_HAGR._hoops_SAGCR;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = left->bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = right->bz._hoops_HAGR._hoops_SAGCR;
							++span;
							if (span == _hoops_SGIHS) {
								int			rows = _hoops_GGIHS;

								_hoops_CRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
						}
						else {
							if (span != _hoops_CGIHS) {
								int			rows = span - _hoops_CGIHS;

								_hoops_CRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
							++y;
						}
					}

					_hoops_APGCR (_hoops_CSGCR.bx);
					_hoops_APGCR (_hoops_CSGCR.bz);
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_APGCR (_hoops_SSGCR.bx);
					_hoops_APGCR (_hoops_SSGCR.bz);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_IAGCR (_hoops_SSGCR.bx, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[1].z, pts[2].z, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.bx._hoops_HAGR._hoops_SAGCR < _hoops_CSGCR.bx._hoops_HAGR._hoops_SAGCR) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = left->bx._hoops_HAGR._hoops_SAGCR;
						span->right.bx._hoops_HAGR._hoops_SAGCR = right->bx._hoops_HAGR._hoops_SAGCR;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = left->bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = right->bz._hoops_HAGR._hoops_SAGCR;
							++span;
							if (span == _hoops_SGIHS) {
								int			rows = _hoops_GGIHS;

								_hoops_CRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
						}
						else {
							if (span != _hoops_CGIHS) {
								int			rows = span - _hoops_CGIHS;

								_hoops_CRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
							++y;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_APGCR (_hoops_CSGCR.bx);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_APGCR (_hoops_SSGCR.bx);
					_hoops_APGCR (_hoops_SSGCR.bz);
				}
			}

			if (span != _hoops_CGIHS) {
				int			rows = span - _hoops_CGIHS;

				_hoops_CRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
			}
		}

		points += _hoops_RRC;
		if (!single)
			_hoops_IASGR++;
	}
#endif
}


GLOBAL_FUNCTION void HD_Span_DC_Gouraud_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors) {
#ifndef DISABLE_RASTERIZER
	_hoops_ISGCR					_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	_hoops_SGGCR						_hoops_IASGR[3];
	int							_hoops_RRC;

	if (nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 0, 0, 0, 0, _hoops_RHGGA|_hoops_GPHC|
																			_hoops_AAIC);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {

		RGBAS32 const	*_hoops_RRGCR = colors;
		int					_hoops_ARGCR;

		if (_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], r) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], g) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[1], b) &&
			_hoops_PRGCR (_hoops_RRGCR[0], _hoops_RRGCR[2], b)) {
			HD_Span_DC_Colorized_Polytris (nr, 3, points, colors, true);
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
			_hoops_ISGCR alter *			left;
			_hoops_ISGCR alter *			right;
			_hoops_GHISP				_hoops_RHISP;
			_hoops_AHISP						_hoops_CGIHS[_hoops_GGIHS];
			_hoops_AHISP alter *				_hoops_SGIHS;
			_hoops_AHISP alter *				span;
			int							y;
			Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;
			int							offset;

			_hoops_RHISP._hoops_CHA = nr->_hoops_IHA->_hoops_CHA;
			_hoops_RHISP.contrast_color = nr->_hoops_IHA->contrast_color;
			_hoops_RHISP.pattern = nr->_hoops_IHA->pattern;

			span = _hoops_CGIHS;
			_hoops_SGIHS = _hoops_CGIHS+_hoops_GGAPR(_hoops_CGIHS);
			y = pts[0].y;

			offset = (int)((nr->transform_rendition->_hoops_CHIH +
							nr->transform_rendition->_hoops_SHIH) *
						   _hoops_ISSIR(nr->transform_rendition));
			pts[0].z += offset;
			pts[1].z += offset;
			pts[2].z += offset;

			_hoops_IAGCR (_hoops_CSGCR.bx, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_IAGCR (_hoops_CSGCR.bz, pts[0].z, pts[2].z, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.r, _hoops_IASGR[0].r, _hoops_IASGR[2].r, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.g, _hoops_IASGR[0].g, _hoops_IASGR[2].g, _hoops_CSGCR._hoops_CRRAR);
			_hoops_HAGCR (_hoops_CSGCR.b, _hoops_IASGR[0].b, _hoops_IASGR[2].b, _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_IAGCR (_hoops_SSGCR.bx, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[0].z, pts[1].z, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.bx._hoops_HGRCR.simple <= _hoops_CSGCR.bx._hoops_HGRCR.simple) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = left->bx._hoops_HAGR._hoops_SAGCR;
						span->right.bx._hoops_HAGR._hoops_SAGCR = right->bx._hoops_HAGR._hoops_SAGCR;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = left->bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = right->bz._hoops_HAGR._hoops_SAGCR;
							span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = right->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = right->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = right->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							++span;
							if (span == _hoops_SGIHS) {
								int			rows = _hoops_GGIHS;

								_hoops_SRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
						}
						else {
							if (span != _hoops_CGIHS) {
								int			rows = span - _hoops_CGIHS;

								_hoops_SRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
							++y;
						}
					}

					_hoops_APGCR (_hoops_CSGCR.bx);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_RPGCR (_hoops_CSGCR.r);
					_hoops_RPGCR (_hoops_CSGCR.g);
					_hoops_RPGCR (_hoops_CSGCR.b);
					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_APGCR (_hoops_SSGCR.bx);
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
				_hoops_IAGCR (_hoops_SSGCR.bx, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[1].z, pts[2].z, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.r, _hoops_IASGR[1].r, _hoops_IASGR[2].r, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.g, _hoops_IASGR[1].g, _hoops_IASGR[2].g, _hoops_SSGCR._hoops_CRRAR);
				_hoops_HAGCR (_hoops_SSGCR.b, _hoops_IASGR[1].b, _hoops_IASGR[2].b, _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.bx._hoops_HAGR._hoops_SAGCR < _hoops_CSGCR.bx._hoops_HAGR._hoops_SAGCR) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = left->bx._hoops_HAGR._hoops_SAGCR;
						span->right.bx._hoops_HAGR._hoops_SAGCR = right->bx._hoops_HAGR._hoops_SAGCR;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = left->bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = right->bz._hoops_HAGR._hoops_SAGCR;
							span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= left->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = right->r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= left->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = right->g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= left->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = right->b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							++span;
							if (span == _hoops_SGIHS) {
								int			rows = _hoops_GGIHS;

								_hoops_SRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
						}
						else {
							if (span != _hoops_CGIHS) {
								int			rows = span - _hoops_CGIHS;

								_hoops_SRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
								span = _hoops_CGIHS;
							}
							++y;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_APGCR (_hoops_CSGCR.bx);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_RPGCR (_hoops_CSGCR.r);
					_hoops_RPGCR (_hoops_CSGCR.g);
					_hoops_RPGCR (_hoops_CSGCR.b);
					_hoops_APGCR (_hoops_SSGCR.bx);
					_hoops_APGCR (_hoops_SSGCR.bz);
					_hoops_RPGCR (_hoops_SSGCR.r);
					_hoops_RPGCR (_hoops_SSGCR.g);
					_hoops_RPGCR (_hoops_SSGCR.b);
				}
			}

			if (span != _hoops_CGIHS) {
				int			rows = span - _hoops_CGIHS;

				_hoops_SRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
			}
		}
_hoops_GGRCR:
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}

GLOBAL_FUNCTION void HD_Span_DC_Phong_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes) {

	HD_Span_DC_Textured_Polytris (nr, count, points, colors, planes, null, 0, 0);
}

GLOBAL_FUNCTION void HD_Span_DC_Textured_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	_hoops_SSIC				param_flags) {
#ifndef DISABLE_RASTERIZER
#ifndef _hoops_IHSIP
	_hoops_ISGCR					_hoops_CSGCR, _hoops_SSGCR;
	_hoops_RCSIR					pts[3];
	int							_hoops_HSPI, _hoops_ISPI, _hoops_CSPI;
	int							_hoops_RRC;
	int							i;
	int							_hoops_RRIHS = 0;
	Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;
	Int_Rectangle				_hoops_CRIHS;
	_hoops_GPGGA				_hoops_SRIHS = 0;

	static RGBA const			_hoops_ARPSH[] = {	_hoops_IGISA::_hoops_IAHHP, _hoops_IGISA::_hoops_IAHHP, _hoops_IGISA::_hoops_IAHHP	};
	static _hoops_ARPA const			_hoops_ARIHS[] = {	_hoops_CGISA::_hoops_CRGA, _hoops_CGISA::_hoops_CRGA, _hoops_CGISA::_hoops_CRGA	};

#define _hoops_GAIHS	(2*_hoops_SGRGA)

	if (!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {
		_hoops_CRIHS.left = _hoops_GPHH.left - _hoops_GAIHS;
		_hoops_CRIHS.right = _hoops_GPHH.right + _hoops_GAIHS;
		_hoops_CRIHS.bottom = _hoops_GPHH.bottom - _hoops_GAIHS;
		_hoops_CRIHS.top = _hoops_GPHH.top + _hoops_GAIHS;
		if ((i = count) < 0)
			i = -i;
		while (i-- > 0) {
			if (points[i].x < _hoops_CRIHS.left || points[i].x > _hoops_CRIHS.right ||
				points[i].y < _hoops_CRIHS.bottom || points[i].y > _hoops_CRIHS.top) {
				_hoops_SRIHS = _hoops_CGRGA;
				break;
			}
		}
	}

	if (_hoops_SRIHS != 0 ||
		nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, colors, planes,
								 params, param_width, param_flags,
								 _hoops_SRIHS | _hoops_RHGGA|_hoops_GPHC | _hoops_AAIC);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	if (colors)
		_hoops_RRIHS |= _hoops_SSPGS;
	else
		colors = _hoops_ARPSH;	/* _hoops_SPCS _hoops_GGAR _hoops_HSH */

	if (planes)
		_hoops_RRIHS |= _hoops_GGHGS;
	else
		planes = _hoops_ARIHS;	/* _hoops_SPCS _hoops_GGAR _hoops_HSH */

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
					_hoops_HSPI = 0; _hoops_ISPI = 1; _hoops_CSPI = 2;
				}
				else if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, x);
					TRUNCATE_3_POINTS (points, pts, 0, 2, 1, z);
					_hoops_CRGCR (pts[2].y, pts[1].y);
					_hoops_HSPI = 0; _hoops_ISPI = 2; _hoops_CSPI = 1;
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, x);
					TRUNCATE_3_POINTS (points, pts, 2, 0, 1, z);
					temp = pts[0].y; pts[0].y = pts[2].y; pts[2].y = pts[1].y; pts[1].y = temp;
					_hoops_HSPI = 2; _hoops_ISPI = 0; _hoops_CSPI = 1;
				}
			}
			else {
				if (pts[0].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, x);
					TRUNCATE_3_POINTS (points, pts, 1, 0, 2, z);
					_hoops_CRGCR (pts[1].y, pts[0].y);
					_hoops_HSPI = 1; _hoops_ISPI = 0; _hoops_CSPI = 2;
				}
				else if (pts[1].y <= pts[2].y) {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, x);
					TRUNCATE_3_POINTS (points, pts, 1, 2, 0, z);
					temp = pts[1].y; pts[1].y = pts[2].y; pts[2].y = pts[0].y; pts[0].y = temp;
					_hoops_HSPI = 1; _hoops_ISPI = 2; _hoops_CSPI = 0;
				}
				else {
					LOAD_ARGUMENT (points);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, x);
					TRUNCATE_3_POINTS (points, pts, 2, 1, 0, z);
					_hoops_CRGCR (pts[2].y, pts[0].y);
					_hoops_HSPI = 2; _hoops_ISPI = 1; _hoops_CSPI = 0;
				}
			}
		}
		ASSERT (pts[0].y <= pts[1].y && pts[1].y <= pts[2].y);

		if ((_hoops_CSGCR._hoops_CRRAR = pts[2].y - pts[0].y) > 0) {
			_hoops_ISGCR alter *			left;
			_hoops_ISGCR alter *			right;
			_hoops_GHISP				_hoops_RHISP;
			_hoops_AHISP						_hoops_CGIHS[_hoops_GGIHS];
			_hoops_AHISP alter *				_hoops_SGIHS;
			_hoops_AHISP alter *				span;
			int							y;
			Point						_hoops_RGCC[3];
			float						_hoops_GRIHS[3];
			int							offset;

			_hoops_RHISP._hoops_CHA = nr->_hoops_IHA->_hoops_CHA;
			_hoops_RHISP._hoops_AGP = nr->_hoops_IHA->_hoops_AGP;

			if ((_hoops_RHISP._hoops_AGP != null &&
				 _hoops_RHISP._hoops_AGP->_hoops_ISPHP) ||
				ANYBIT (nr->_hoops_IRR->_hoops_PPH,
						Rendo_LOCAL_VIEWER|_hoops_HPH) ||
				 params != null &&
				BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
				_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
				_hoops_SGCC const &		mat = _hoops_IHCR->_hoops_CGCC;
				_hoops_RPRA const *				_hoops_APRA;
				float							_hoops_APCP;

				if (!BIT (_hoops_IHCR->flags, _hoops_IGCC))
					HD_Validate_World_To_Screen (nr);

				_hoops_APRA = _hoops_IHCR->_hoops_CGCC->_hoops_PPRA()->data.elements;

				_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[_hoops_HSPI]);
				_hoops_RGCC[_hoops_HSPI].x = _hoops_HPRA (_hoops_APRA, points[_hoops_HSPI]) * _hoops_APCP;
				_hoops_RGCC[_hoops_HSPI].y = _hoops_IPRA (_hoops_APRA, points[_hoops_HSPI]) * _hoops_APCP;
				_hoops_RGCC[_hoops_HSPI].z = _hoops_CPRA (_hoops_APRA, points[_hoops_HSPI]) * _hoops_APCP;
				_hoops_GRIHS[_hoops_HSPI]	 = _hoops_PHCP (mat->data.elements, _hoops_RGCC[_hoops_HSPI]);

				_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[_hoops_ISPI]);
				_hoops_RGCC[_hoops_ISPI].x = _hoops_HPRA (_hoops_APRA, points[_hoops_ISPI]) * _hoops_APCP;
				_hoops_RGCC[_hoops_ISPI].y = _hoops_IPRA (_hoops_APRA, points[_hoops_ISPI]) * _hoops_APCP;
				_hoops_RGCC[_hoops_ISPI].z = _hoops_CPRA (_hoops_APRA, points[_hoops_ISPI]) * _hoops_APCP;
				_hoops_GRIHS[_hoops_ISPI]	 = _hoops_PHCP (mat->data.elements, _hoops_RGCC[_hoops_ISPI]);

				_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[_hoops_CSPI]);
				_hoops_RGCC[_hoops_CSPI].x = _hoops_HPRA (_hoops_APRA, points[_hoops_CSPI]) * _hoops_APCP;
				_hoops_RGCC[_hoops_CSPI].y = _hoops_IPRA (_hoops_APRA, points[_hoops_CSPI]) * _hoops_APCP;
				_hoops_RGCC[_hoops_CSPI].z = _hoops_CPRA (_hoops_APRA, points[_hoops_CSPI]) * _hoops_APCP;
				_hoops_GRIHS[_hoops_CSPI]	 = _hoops_PHCP (mat->data.elements, _hoops_RGCC[_hoops_CSPI]);

				_hoops_RRIHS |= _hoops_AGHGS;
			}
			else {
				_hoops_RGCC[0] = _hoops_HPCH::_hoops_IPCH;
				_hoops_RGCC[1] = _hoops_HPCH::_hoops_IPCH;
				_hoops_RGCC[2] = _hoops_HPCH::_hoops_IPCH;
				_hoops_GRIHS[0] = _hoops_GRIHS[1] = _hoops_GRIHS[2] = 1.0f;
			}

			_hoops_RHISP.contrast_color = nr->_hoops_IHA->contrast_color;
			_hoops_RHISP.pattern = nr->_hoops_IHA->pattern;

			span = _hoops_CGIHS;
			_hoops_SGIHS = _hoops_CGIHS+_hoops_GGAPR(_hoops_CGIHS);

			span->left.param_width = span->right.param_width = param_width;

			y = pts[0].y;

			offset = (int)((nr->transform_rendition->_hoops_CHIH +
							nr->transform_rendition->_hoops_SHIH) *
						   _hoops_ISSIR(nr->transform_rendition));
			pts[0].z += offset;
			pts[1].z += offset;
			pts[2].z += offset;

			_hoops_IAGCR (_hoops_CSGCR.bx, pts[0].x, pts[2].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_IAGCR (_hoops_CSGCR.bz, pts[0].z, pts[2].z, _hoops_CSGCR._hoops_CRRAR);

			_hoops_PHHHS (_hoops_CSGCR._hoops_SIGA, colors[_hoops_HSPI].red,	  colors[_hoops_CSPI].red,	_hoops_CSGCR._hoops_CRRAR);
			_hoops_PHHHS (_hoops_CSGCR._hoops_SHRIC, colors[_hoops_HSPI].green, colors[_hoops_CSPI].green, _hoops_CSGCR._hoops_CRRAR);
			_hoops_PHHHS (_hoops_CSGCR._hoops_PPGGS, colors[_hoops_HSPI].blue,  colors[_hoops_CSPI].blue,	_hoops_CSGCR._hoops_CRRAR);

			_hoops_PHHHS (_hoops_CSGCR._hoops_IPAIA, planes[_hoops_HSPI].a, planes[_hoops_CSPI].a, _hoops_CSGCR._hoops_CRRAR);
			_hoops_PHHHS (_hoops_CSGCR._hoops_CPAIA, planes[_hoops_HSPI].b, planes[_hoops_CSPI].b, _hoops_CSGCR._hoops_CRRAR);
			_hoops_PHHHS (_hoops_CSGCR._hoops_HSPIR, planes[_hoops_HSPI].c, planes[_hoops_CSPI].c, _hoops_CSGCR._hoops_CRRAR);
			_hoops_PHHHS (_hoops_CSGCR._hoops_RGHGS, planes[_hoops_HSPI].d, planes[_hoops_CSPI].d, _hoops_CSGCR._hoops_CRRAR);

#ifndef DISABLE_TEXTURING
			for (i=0; i<param_width; i++) {
				_hoops_PHHHS (_hoops_CSGCR.param[i], params[(_hoops_HSPI*param_width)+i], params[(_hoops_CSPI*param_width)+i], _hoops_CSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_CSGCR._hoops_RSHHS[i], 0.0f, params[(_hoops_CSPI*param_width)+i] - params[(_hoops_HSPI*param_width)+i], _hoops_CSGCR._hoops_CRRAR);
				_hoops_CSGCR._hoops_PSHHS[i] = params[(_hoops_HSPI*param_width)+i];
			}
#endif
			_hoops_PHHHS (_hoops_CSGCR._hoops_PGHGS, _hoops_RGCC[_hoops_HSPI].x, _hoops_RGCC[_hoops_CSPI].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_PHHHS (_hoops_CSGCR._hoops_HGHGS, _hoops_RGCC[_hoops_HSPI].y, _hoops_RGCC[_hoops_CSPI].y, _hoops_CSGCR._hoops_CRRAR);
			_hoops_PHHHS (_hoops_CSGCR._hoops_IGHGS, _hoops_RGCC[_hoops_HSPI].z, _hoops_RGCC[_hoops_CSPI].z, _hoops_CSGCR._hoops_CRRAR);

			_hoops_PHHHS (_hoops_CSGCR._hoops_ACHHS, 0.0f, _hoops_RGCC[_hoops_CSPI].x - _hoops_RGCC[_hoops_HSPI].x, _hoops_CSGCR._hoops_CRRAR);
			_hoops_PHHHS (_hoops_CSGCR._hoops_HCHHS, 0.0f, _hoops_RGCC[_hoops_CSPI].y - _hoops_RGCC[_hoops_HSPI].y, _hoops_CSGCR._hoops_CRRAR);
			_hoops_PHHHS (_hoops_CSGCR._hoops_ICHHS, 0.0f, _hoops_RGCC[_hoops_CSPI].z - _hoops_RGCC[_hoops_HSPI].z, _hoops_CSGCR._hoops_CRRAR);

			_hoops_PHHHS (_hoops_CSGCR._hoops_CSHHS, _hoops_GRIHS[_hoops_CSPI] / _hoops_GRIHS[_hoops_HSPI], 1.0f, _hoops_CSGCR._hoops_CRRAR);
			_hoops_CSGCR._hoops_CCHHS = _hoops_RGCC[_hoops_HSPI].x; _hoops_CSGCR._hoops_SCHHS = _hoops_RGCC[_hoops_HSPI].y; _hoops_CSGCR._hoops_GSHHS = _hoops_RGCC[_hoops_HSPI].z;

			_hoops_PHHHS (_hoops_CSGCR._hoops_HSHHS, _hoops_GRIHS[_hoops_HSPI], _hoops_GRIHS[_hoops_CSPI], _hoops_CSGCR._hoops_CRRAR);

			/*
			 * _hoops_PGRCR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_RGRCR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[1].y - pts[0].y) > 0) {
				_hoops_IAGCR (_hoops_SSGCR.bx, pts[0].x, pts[1].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[0].z, pts[1].z, _hoops_SSGCR._hoops_CRRAR);

				_hoops_PHHHS (_hoops_SSGCR._hoops_SIGA, colors[_hoops_HSPI].red,	  colors[_hoops_ISPI].red,	_hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_SHRIC, colors[_hoops_HSPI].green, colors[_hoops_ISPI].green, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_PPGGS, colors[_hoops_HSPI].blue,  colors[_hoops_ISPI].blue,	_hoops_SSGCR._hoops_CRRAR);

				_hoops_PHHHS (_hoops_SSGCR._hoops_IPAIA, planes[_hoops_HSPI].a, planes[_hoops_ISPI].a, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_CPAIA, planes[_hoops_HSPI].b, planes[_hoops_ISPI].b, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_HSPIR, planes[_hoops_HSPI].c, planes[_hoops_ISPI].c, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_RGHGS, planes[_hoops_HSPI].d, planes[_hoops_ISPI].d, _hoops_SSGCR._hoops_CRRAR);

#ifndef DISABLE_TEXTURING
				for (i=0; i<param_width; i++) {
					_hoops_PHHHS (_hoops_SSGCR.param[i], params[(_hoops_HSPI*param_width)+i], params[(_hoops_ISPI*param_width)+i], _hoops_SSGCR._hoops_CRRAR);
					_hoops_PHHHS (_hoops_SSGCR._hoops_RSHHS[i], 0.0f, params[(_hoops_ISPI*param_width)+i] - params[(_hoops_HSPI*param_width)+i], _hoops_SSGCR._hoops_CRRAR);
					_hoops_SSGCR._hoops_PSHHS[i] = params[(_hoops_HSPI*param_width)+i];
				}
#endif

				_hoops_PHHHS (_hoops_SSGCR._hoops_PGHGS, _hoops_RGCC[_hoops_HSPI].x, _hoops_RGCC[_hoops_ISPI].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_HGHGS, _hoops_RGCC[_hoops_HSPI].y, _hoops_RGCC[_hoops_ISPI].y, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_IGHGS, _hoops_RGCC[_hoops_HSPI].z, _hoops_RGCC[_hoops_ISPI].z, _hoops_SSGCR._hoops_CRRAR);

				_hoops_PHHHS (_hoops_SSGCR._hoops_ACHHS, 0.0f, _hoops_RGCC[_hoops_ISPI].x - _hoops_RGCC[_hoops_HSPI].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_HCHHS, 0.0f, _hoops_RGCC[_hoops_ISPI].y - _hoops_RGCC[_hoops_HSPI].y, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_ICHHS, 0.0f, _hoops_RGCC[_hoops_ISPI].z - _hoops_RGCC[_hoops_HSPI].z, _hoops_SSGCR._hoops_CRRAR);

				_hoops_PHHHS (_hoops_SSGCR._hoops_CSHHS, _hoops_GRIHS[_hoops_ISPI] / _hoops_GRIHS[_hoops_HSPI], 1.0f, _hoops_SSGCR._hoops_CRRAR);
				_hoops_SSGCR._hoops_CCHHS = _hoops_RGCC[_hoops_HSPI].x; _hoops_SSGCR._hoops_SCHHS = _hoops_RGCC[_hoops_HSPI].y; _hoops_SSGCR._hoops_GSHHS = _hoops_RGCC[_hoops_HSPI].z;

				_hoops_PHHHS (_hoops_SSGCR._hoops_HSHHS, _hoops_GRIHS[_hoops_HSPI], _hoops_GRIHS[_hoops_ISPI], _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.bx._hoops_HGRCR.simple <= _hoops_CSGCR.bx._hoops_HGRCR.simple) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						y++;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						/* _hoops_SHSC _hoops_PHI _hoops_GPP _hoops_SISR _hoops_HSH _hoops_HIS _hoops_HAGAH _hoops_PAH _hoops_CGIC _hoops_RAIHS _hoops_ISGSP */
						_hoops_IIHHS (left->bx, span->left.bx);
						_hoops_IIHHS (right->bx, span->right.bx);

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = left->bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = right->bz._hoops_HAGR._hoops_SAGCR;
							span->left._hoops_SIGA._hoops_HAGR  = left->_hoops_SIGA._hoops_HAGR;
							span->right._hoops_SIGA._hoops_HAGR = right->_hoops_SIGA._hoops_HAGR;
							span->left._hoops_SHRIC._hoops_HAGR  = left->_hoops_SHRIC._hoops_HAGR;
							span->right._hoops_SHRIC._hoops_HAGR = right->_hoops_SHRIC._hoops_HAGR;
							span->left._hoops_PPGGS._hoops_HAGR  = left->_hoops_PPGGS._hoops_HAGR;
							span->right._hoops_PPGGS._hoops_HAGR = right->_hoops_PPGGS._hoops_HAGR;
							span->left._hoops_IPAIA._hoops_HAGR  = left->_hoops_IPAIA._hoops_HAGR;
							span->right._hoops_IPAIA._hoops_HAGR = right->_hoops_IPAIA._hoops_HAGR;
							span->left._hoops_CPAIA._hoops_HAGR  = left->_hoops_CPAIA._hoops_HAGR;
							span->right._hoops_CPAIA._hoops_HAGR = right->_hoops_CPAIA._hoops_HAGR;
							span->left._hoops_HSPIR._hoops_HAGR  = left->_hoops_HSPIR._hoops_HAGR;
							span->right._hoops_HSPIR._hoops_HAGR = right->_hoops_HSPIR._hoops_HAGR;
							span->left._hoops_RGHGS._hoops_HAGR  = left->_hoops_RGHGS._hoops_HAGR;
							span->right._hoops_RGHGS._hoops_HAGR = right->_hoops_RGHGS._hoops_HAGR;

#ifndef DISABLE_TEXTURING
							for (i=0; i<param_width; i++) {
								span->left.param[i]._hoops_HAGR	 = left->param[i]._hoops_HAGR;
								span->right.param[i]._hoops_HAGR = right->param[i]._hoops_HAGR;
							}
#endif
							span->left._hoops_PGHGS._hoops_HAGR  = left->_hoops_PGHGS._hoops_HAGR;
							span->right._hoops_PGHGS._hoops_HAGR = right->_hoops_PGHGS._hoops_HAGR;
							span->left._hoops_HGHGS._hoops_HAGR  = left->_hoops_HGHGS._hoops_HAGR;
							span->right._hoops_HGHGS._hoops_HAGR = right->_hoops_HGHGS._hoops_HAGR;
							span->left._hoops_IGHGS._hoops_HAGR  = left->_hoops_IGHGS._hoops_HAGR;
							span->right._hoops_IGHGS._hoops_HAGR = right->_hoops_IGHGS._hoops_HAGR;
							span->left._hoops_HSHHS._hoops_HAGR  = left->_hoops_HSHHS._hoops_HAGR;
							span->right._hoops_HSHHS._hoops_HAGR = right->_hoops_HSHHS._hoops_HAGR;

							span->valid = _hoops_RRIHS;
							++span;
							if (span == _hoops_SGIHS) {
								int			rows = _hoops_GGIHS;

								_hoops_GACGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows, param_flags);
								span = _hoops_CGIHS;
							}
						}
						else {
							if (span != _hoops_CGIHS) {
								int			rows = span - _hoops_CGIHS;

								_hoops_GACGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows, param_flags);
								span = _hoops_CGIHS;
							}
							++y;
						}
					}

					_hoops_APGCR (_hoops_CSGCR.bx);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_IHHHS (_hoops_CSGCR._hoops_SIGA);
					_hoops_IHHHS (_hoops_CSGCR._hoops_SHRIC);
					_hoops_IHHHS (_hoops_CSGCR._hoops_PPGGS);
					_hoops_IHHHS (_hoops_CSGCR._hoops_IPAIA);
					_hoops_IHHHS (_hoops_CSGCR._hoops_CPAIA);
					_hoops_IHHHS (_hoops_CSGCR._hoops_HSPIR);
					_hoops_IHHHS (_hoops_CSGCR._hoops_RGHGS);
					if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
						float	_hoops_SAASP;

						_hoops_SAASP = 1.0f / (_hoops_CSGCR._hoops_CSHHS._hoops_HAGR	+= _hoops_CSGCR._hoops_CSHHS._hoops_HGRCR);

#ifndef DISABLE_TEXTURING
						for (i=0; i<param_width; i++) {
							_hoops_IHHHS (_hoops_CSGCR._hoops_RSHHS[i]);
							_hoops_CSGCR.param[i]._hoops_HAGR	 = _hoops_CSGCR._hoops_PSHHS[i] + _hoops_CSGCR._hoops_RSHHS[i]._hoops_HAGR * _hoops_SAASP;
						}
#endif

						_hoops_IHHHS (_hoops_CSGCR._hoops_ACHHS);
						_hoops_IHHHS (_hoops_CSGCR._hoops_HCHHS);
						_hoops_IHHHS (_hoops_CSGCR._hoops_ICHHS);

						_hoops_CSGCR._hoops_PGHGS._hoops_HAGR = _hoops_CSGCR._hoops_CCHHS + _hoops_CSGCR._hoops_ACHHS._hoops_HAGR * _hoops_SAASP;
						_hoops_CSGCR._hoops_HGHGS._hoops_HAGR = _hoops_CSGCR._hoops_SCHHS + _hoops_CSGCR._hoops_HCHHS._hoops_HAGR * _hoops_SAASP;
						_hoops_CSGCR._hoops_IGHGS._hoops_HAGR = _hoops_CSGCR._hoops_GSHHS + _hoops_CSGCR._hoops_ICHHS._hoops_HAGR * _hoops_SAASP;
					}
					else {
#ifndef DISABLE_TEXTURING
						for (i=0; i<param_width; i++) {
							_hoops_IHHHS (_hoops_CSGCR.param[i]);
						}
#endif
						_hoops_IHHHS (_hoops_CSGCR._hoops_PGHGS);
						_hoops_IHHHS (_hoops_CSGCR._hoops_HGHGS);
						_hoops_IHHHS (_hoops_CSGCR._hoops_IGHGS);
					}
					_hoops_IHHHS (_hoops_CSGCR._hoops_HSHHS);

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_APGCR (_hoops_SSGCR.bx);
					_hoops_APGCR (_hoops_SSGCR.bz);
					_hoops_IHHHS (_hoops_SSGCR._hoops_SIGA);
					_hoops_IHHHS (_hoops_SSGCR._hoops_SHRIC);
					_hoops_IHHHS (_hoops_SSGCR._hoops_PPGGS);
					_hoops_IHHHS (_hoops_SSGCR._hoops_IPAIA);
					_hoops_IHHHS (_hoops_SSGCR._hoops_CPAIA);
					_hoops_IHHHS (_hoops_SSGCR._hoops_HSPIR);
					_hoops_IHHHS (_hoops_SSGCR._hoops_RGHGS);
					if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
						float	_hoops_SAASP;

						_hoops_SAASP = 1.0f / (_hoops_SSGCR._hoops_CSHHS._hoops_HAGR	+= _hoops_SSGCR._hoops_CSHHS._hoops_HGRCR);
#ifndef DISABLE_TEXTURING
						for (i=0; i<param_width; i++) {
							_hoops_IHHHS (_hoops_SSGCR._hoops_RSHHS[i]);
							_hoops_SSGCR.param[i]._hoops_HAGR	 = _hoops_SSGCR._hoops_PSHHS[i] + _hoops_SSGCR._hoops_RSHHS[i]._hoops_HAGR * _hoops_SAASP;
						}
#endif
						_hoops_IHHHS (_hoops_SSGCR._hoops_ACHHS);
						_hoops_IHHHS (_hoops_SSGCR._hoops_HCHHS);
						_hoops_IHHHS (_hoops_SSGCR._hoops_ICHHS);

						_hoops_SSGCR._hoops_PGHGS._hoops_HAGR = _hoops_SSGCR._hoops_CCHHS + _hoops_SSGCR._hoops_ACHHS._hoops_HAGR * _hoops_SAASP;
						_hoops_SSGCR._hoops_HGHGS._hoops_HAGR = _hoops_SSGCR._hoops_SCHHS + _hoops_SSGCR._hoops_HCHHS._hoops_HAGR * _hoops_SAASP;
						_hoops_SSGCR._hoops_IGHGS._hoops_HAGR = _hoops_SSGCR._hoops_GSHHS + _hoops_SSGCR._hoops_ICHHS._hoops_HAGR * _hoops_SAASP;
					}
					else {
#ifndef DISABLE_TEXTURING
						for (i=0; i<param_width; i++) {
							_hoops_IHHHS (_hoops_SSGCR.param[i]);
						}
#endif
						_hoops_IHHHS (_hoops_SSGCR._hoops_PGHGS);
						_hoops_IHHHS (_hoops_SSGCR._hoops_HGHGS);
						_hoops_IHHHS (_hoops_SSGCR._hoops_IGHGS);
					}
					_hoops_IHHHS (_hoops_SSGCR._hoops_HSHHS);
				}
			}

			/*
			 * _hoops_AGGRR _hoops_HHAA _hoops_RRRS _hoops_RSSA[_hoops_IIHHR]._hoops_HAPC _hoops_IS _hoops_RSSA[_hoops_CIHHR]._hoops_HAPC
			 */
			if ((_hoops_SSGCR._hoops_CRRAR = pts[2].y - pts[1].y) > 0) {
				_hoops_IAGCR (_hoops_SSGCR.bx, pts[1].x, pts[2].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_IAGCR (_hoops_SSGCR.bz, pts[1].z, pts[2].z, _hoops_SSGCR._hoops_CRRAR);

				_hoops_PHHHS (_hoops_SSGCR._hoops_SIGA, colors[_hoops_ISPI].red,	  colors[_hoops_CSPI].red,	_hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_SHRIC, colors[_hoops_ISPI].green, colors[_hoops_CSPI].green, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_PPGGS, colors[_hoops_ISPI].blue,  colors[_hoops_CSPI].blue,	_hoops_SSGCR._hoops_CRRAR);

				_hoops_PHHHS (_hoops_SSGCR._hoops_IPAIA, planes[_hoops_ISPI].a, planes[_hoops_CSPI].a, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_CPAIA, planes[_hoops_ISPI].b, planes[_hoops_CSPI].b, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_HSPIR, planes[_hoops_ISPI].c, planes[_hoops_CSPI].c, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_RGHGS, planes[_hoops_ISPI].d, planes[_hoops_CSPI].d, _hoops_SSGCR._hoops_CRRAR);

#ifndef DISABLE_TEXTURING
				for (i=0; i<param_width; i++) {
					_hoops_PHHHS (_hoops_SSGCR.param[i], params[(_hoops_ISPI*param_width)+i], params[(_hoops_CSPI*param_width)+i], _hoops_SSGCR._hoops_CRRAR);
					_hoops_PHHHS (_hoops_SSGCR._hoops_RSHHS[i], 0.0f, params[(_hoops_CSPI*param_width)+i] - params[(_hoops_ISPI*param_width)+i], _hoops_SSGCR._hoops_CRRAR);
					_hoops_SSGCR._hoops_PSHHS[i] = params[(_hoops_ISPI*param_width)+i];
				}
#endif

				_hoops_PHHHS (_hoops_SSGCR._hoops_PGHGS, _hoops_RGCC[_hoops_ISPI].x, _hoops_RGCC[_hoops_CSPI].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_HGHGS, _hoops_RGCC[_hoops_ISPI].y, _hoops_RGCC[_hoops_CSPI].y, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_IGHGS, _hoops_RGCC[_hoops_ISPI].z, _hoops_RGCC[_hoops_CSPI].z, _hoops_SSGCR._hoops_CRRAR);

				_hoops_PHHHS (_hoops_SSGCR._hoops_ACHHS, 0.0f, _hoops_RGCC[_hoops_CSPI].x - _hoops_RGCC[_hoops_ISPI].x, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_HCHHS, 0.0f, _hoops_RGCC[_hoops_CSPI].y - _hoops_RGCC[_hoops_ISPI].y, _hoops_SSGCR._hoops_CRRAR);
				_hoops_PHHHS (_hoops_SSGCR._hoops_ICHHS, 0.0f, _hoops_RGCC[_hoops_CSPI].z - _hoops_RGCC[_hoops_ISPI].z, _hoops_SSGCR._hoops_CRRAR);



				_hoops_PHHHS (_hoops_SSGCR._hoops_CSHHS, _hoops_GRIHS[_hoops_CSPI] / _hoops_GRIHS[_hoops_ISPI], 1.0f, _hoops_SSGCR._hoops_CRRAR);
				_hoops_SSGCR._hoops_CCHHS = _hoops_RGCC[_hoops_ISPI].x; _hoops_SSGCR._hoops_SCHHS = _hoops_RGCC[_hoops_ISPI].y; _hoops_SSGCR._hoops_GSHHS = _hoops_RGCC[_hoops_ISPI].z;

				_hoops_PHHHS (_hoops_SSGCR._hoops_HSHHS, _hoops_GRIHS[_hoops_ISPI], _hoops_GRIHS[_hoops_CSPI], _hoops_SSGCR._hoops_CRRAR);

				if (_hoops_SSGCR.bx._hoops_HAGR._hoops_SAGCR < _hoops_CSGCR.bx._hoops_HAGR._hoops_SAGCR) {
					left = &_hoops_SSGCR; right = &_hoops_CSGCR;
				}
				else {
					left = &_hoops_CSGCR; right = &_hoops_SSGCR;
				}

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						y++;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						/* _hoops_SHSC _hoops_PHI _hoops_GPP _hoops_SISR _hoops_HSH _hoops_HIS _hoops_HAGAH _hoops_PAH _hoops_CGIC _hoops_RAIHS _hoops_ISGSP */
						_hoops_IIHHS (left->bx, span->left.bx);
						_hoops_IIHHS (right->bx, span->right.bx);

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = left->bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = right->bz._hoops_HAGR._hoops_SAGCR;
							span->left._hoops_SIGA._hoops_HAGR  = left->_hoops_SIGA._hoops_HAGR;
							span->right._hoops_SIGA._hoops_HAGR = right->_hoops_SIGA._hoops_HAGR;
							span->left._hoops_SHRIC._hoops_HAGR  = left->_hoops_SHRIC._hoops_HAGR;
							span->right._hoops_SHRIC._hoops_HAGR = right->_hoops_SHRIC._hoops_HAGR;
							span->left._hoops_PPGGS._hoops_HAGR  = left->_hoops_PPGGS._hoops_HAGR;
							span->right._hoops_PPGGS._hoops_HAGR = right->_hoops_PPGGS._hoops_HAGR;
							span->left._hoops_IPAIA._hoops_HAGR  = left->_hoops_IPAIA._hoops_HAGR;
							span->right._hoops_IPAIA._hoops_HAGR = right->_hoops_IPAIA._hoops_HAGR;
							span->left._hoops_CPAIA._hoops_HAGR  = left->_hoops_CPAIA._hoops_HAGR;
							span->right._hoops_CPAIA._hoops_HAGR = right->_hoops_CPAIA._hoops_HAGR;
							span->left._hoops_HSPIR._hoops_HAGR  = left->_hoops_HSPIR._hoops_HAGR;
							span->right._hoops_HSPIR._hoops_HAGR = right->_hoops_HSPIR._hoops_HAGR;
							span->left._hoops_RGHGS._hoops_HAGR  = left->_hoops_RGHGS._hoops_HAGR;
							span->right._hoops_RGHGS._hoops_HAGR = right->_hoops_RGHGS._hoops_HAGR;
#ifndef DISABLE_TEXTURING
							for (i=0; i<param_width; i++) {
								span->left.param[i]._hoops_HAGR	 = left->param[i]._hoops_HAGR;
								span->right.param[i]._hoops_HAGR = right->param[i]._hoops_HAGR;
							}
#endif
							span->left._hoops_PGHGS._hoops_HAGR  = left->_hoops_PGHGS._hoops_HAGR;
							span->right._hoops_PGHGS._hoops_HAGR = right->_hoops_PGHGS._hoops_HAGR;
							span->left._hoops_HGHGS._hoops_HAGR  = left->_hoops_HGHGS._hoops_HAGR;
							span->right._hoops_HGHGS._hoops_HAGR = right->_hoops_HGHGS._hoops_HAGR;
							span->left._hoops_IGHGS._hoops_HAGR  = left->_hoops_IGHGS._hoops_HAGR;
							span->right._hoops_IGHGS._hoops_HAGR = right->_hoops_IGHGS._hoops_HAGR;
							span->left._hoops_HSHHS._hoops_HAGR  = left->_hoops_HSHHS._hoops_HAGR;
							span->right._hoops_HSHHS._hoops_HAGR = right->_hoops_HSHHS._hoops_HAGR;

							span->valid = _hoops_RRIHS;
							++span;
							if (span == _hoops_SGIHS) {
								int			rows = _hoops_GGIHS;

								_hoops_GACGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows, param_flags);
								span = _hoops_CGIHS;
							}
						}
						else {
							if (span != _hoops_CGIHS) {
								int			rows = span - _hoops_CGIHS;

								_hoops_GACGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows, param_flags);
								span = _hoops_CGIHS;
							}
							++y;
						}
					}

					if (--_hoops_SSGCR._hoops_CRRAR == 0)
						break;

					_hoops_APGCR (_hoops_CSGCR.bx);
					_hoops_APGCR (_hoops_CSGCR.bz);
					_hoops_IHHHS (_hoops_CSGCR._hoops_SIGA);
					_hoops_IHHHS (_hoops_CSGCR._hoops_SHRIC);
					_hoops_IHHHS (_hoops_CSGCR._hoops_PPGGS);
					_hoops_IHHHS (_hoops_CSGCR._hoops_IPAIA);
					_hoops_IHHHS (_hoops_CSGCR._hoops_CPAIA);
					_hoops_IHHHS (_hoops_CSGCR._hoops_HSPIR);
					_hoops_IHHHS (_hoops_CSGCR._hoops_RGHGS);

					_hoops_APGCR (_hoops_SSGCR.bx);
					_hoops_APGCR (_hoops_SSGCR.bz);
					_hoops_IHHHS (_hoops_SSGCR._hoops_SIGA);
					_hoops_IHHHS (_hoops_SSGCR._hoops_SHRIC);
					_hoops_IHHHS (_hoops_SSGCR._hoops_PPGGS);
					_hoops_IHHHS (_hoops_SSGCR._hoops_IPAIA);
					_hoops_IHHHS (_hoops_SSGCR._hoops_CPAIA);
					_hoops_IHHHS (_hoops_SSGCR._hoops_HSPIR);
					_hoops_IHHHS (_hoops_SSGCR._hoops_RGHGS);
					if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
						float	_hoops_SAASP;

						_hoops_SAASP = 1.0f / (_hoops_CSGCR._hoops_CSHHS._hoops_HAGR	+= _hoops_CSGCR._hoops_CSHHS._hoops_HGRCR);

#ifndef DISABLE_TEXTURING
						for (i=0; i<param_width; i++) {
							_hoops_IHHHS (_hoops_CSGCR._hoops_RSHHS[i]);
							_hoops_CSGCR.param[i]._hoops_HAGR	 = _hoops_CSGCR._hoops_PSHHS[i] + _hoops_CSGCR._hoops_RSHHS[i]._hoops_HAGR * _hoops_SAASP;

						}
#endif
						_hoops_IHHHS (_hoops_CSGCR._hoops_ACHHS);
						_hoops_IHHHS (_hoops_CSGCR._hoops_HCHHS);
						_hoops_IHHHS (_hoops_CSGCR._hoops_ICHHS);

						_hoops_CSGCR._hoops_PGHGS._hoops_HAGR = _hoops_CSGCR._hoops_CCHHS + _hoops_CSGCR._hoops_ACHHS._hoops_HAGR * _hoops_SAASP;
						_hoops_CSGCR._hoops_HGHGS._hoops_HAGR = _hoops_CSGCR._hoops_SCHHS + _hoops_CSGCR._hoops_HCHHS._hoops_HAGR * _hoops_SAASP;
						_hoops_CSGCR._hoops_IGHGS._hoops_HAGR = _hoops_CSGCR._hoops_GSHHS + _hoops_CSGCR._hoops_ICHHS._hoops_HAGR * _hoops_SAASP;

						_hoops_SAASP = 1.0f / (_hoops_SSGCR._hoops_CSHHS._hoops_HAGR	+= _hoops_SSGCR._hoops_CSHHS._hoops_HGRCR);

#ifndef DISABLE_TEXTURING
						for (i=0; i<param_width; i++) {
							_hoops_IHHHS (_hoops_SSGCR._hoops_RSHHS[i]);
							_hoops_SSGCR.param[i]._hoops_HAGR	 = _hoops_SSGCR._hoops_PSHHS[i] + _hoops_SSGCR._hoops_RSHHS[i]._hoops_HAGR * _hoops_SAASP;
						}
#endif
						_hoops_IHHHS (_hoops_SSGCR._hoops_ACHHS);
						_hoops_IHHHS (_hoops_SSGCR._hoops_HCHHS);
						_hoops_IHHHS (_hoops_SSGCR._hoops_ICHHS);

						_hoops_SSGCR._hoops_PGHGS._hoops_HAGR = _hoops_SSGCR._hoops_CCHHS + _hoops_SSGCR._hoops_ACHHS._hoops_HAGR * _hoops_SAASP;
						_hoops_SSGCR._hoops_HGHGS._hoops_HAGR = _hoops_SSGCR._hoops_SCHHS + _hoops_SSGCR._hoops_HCHHS._hoops_HAGR * _hoops_SAASP;
						_hoops_SSGCR._hoops_IGHGS._hoops_HAGR = _hoops_SSGCR._hoops_GSHHS + _hoops_SSGCR._hoops_ICHHS._hoops_HAGR * _hoops_SAASP;
					}
					else {
#ifndef DISABLE_TEXTURING
						for (i=0; i<param_width; i++) {
							_hoops_IHHHS (_hoops_CSGCR.param[i]);
							_hoops_IHHHS (_hoops_SSGCR.param[i]);
						}
#endif
						_hoops_IHHHS (_hoops_CSGCR._hoops_PGHGS);
						_hoops_IHHHS (_hoops_CSGCR._hoops_HGHGS);
						_hoops_IHHHS (_hoops_CSGCR._hoops_IGHGS);

						_hoops_IHHHS (_hoops_SSGCR._hoops_PGHGS);
						_hoops_IHHHS (_hoops_SSGCR._hoops_HGHGS);
						_hoops_IHHHS (_hoops_SSGCR._hoops_IGHGS);
					}
					_hoops_IHHHS (_hoops_CSGCR._hoops_HSHHS);
					_hoops_IHHHS (_hoops_SSGCR._hoops_HSHHS);
				}
			}

			if (span != _hoops_CGIHS) {
				int			rows = span - _hoops_CGIHS;

				_hoops_GACGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows, param_flags);
			}
		}

		points += _hoops_RRC;
		if (colors && colors != _hoops_ARPSH)
			colors += _hoops_RRC;
		if (planes && planes != _hoops_ARIHS)
			planes += _hoops_RRC;
		if (params)
			params += _hoops_RRC * param_width;
	}
#endif
#endif
}

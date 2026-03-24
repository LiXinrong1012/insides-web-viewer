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
 * $Id: obf_tmp.txt 1.96 2010-06-04 21:37:19 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "span.h"
#include "patterns.h"
#include "tandt.h"


GLOBAL_FUNCTION void HD_Span_DC_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
#ifndef DISABLE_RASTERIZER
	_hoops_RCSIR					pts[2];
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	_hoops_GHISP				_hoops_RHISP;
	_hoops_AHISP						_hoops_CGIHS[_hoops_GGIHS];
	_hoops_AHISP alter *				_hoops_SGIHS = _hoops_CGIHS+_hoops_GGAPR(_hoops_CGIHS);
	_hoops_AHISP alter *				span;
	int							y;
	int							_hoops_RRC;
	int							offset;


	if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP) ||
		!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) ||
		nr->_hoops_AHP->weight > 1) {
		HD_Std_DC_Polyline (nr, count, points);
		return;
	}

	if (nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_RHGGA|_hoops_GPHC);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	offset = (int)(nr->transform_rendition->_hoops_SHIH *
					_hoops_ISSIR(nr->transform_rendition));

	_hoops_RHISP._hoops_PIHSR = nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR;
	_hoops_RHISP.color = _hoops_HC->color;
	_hoops_RHISP.contrast_color = _hoops_HC->color;
	_hoops_RHISP.pattern = FP_SOLID;

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y < pts[1].y) {
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

		pts[0].z += offset;
		pts[1].z += offset;

		y = (int)pts[0].y;
		span = _hoops_CGIHS;

		{
			_hoops_ISGCR					a0;
			int							x;
			int							z;
			int							dx;
			int							_hoops_CRRAR;
			Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

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
				_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = a0.bx._hoops_HAGR._hoops_SAGCR;
						span->right.bx._hoops_HAGR._hoops_SAGCR = a0.bx._hoops_HAGR._hoops_SAGCR + 1;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = a0.bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = a0.bz._hoops_HAGR._hoops_SAGCR;
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

					if (_hoops_CRRAR-- == 0) break;

					_hoops_APGCR (a0.bx);
					_hoops_APGCR (a0.bz);
				}

				if (span != _hoops_CGIHS) {
					int			rows = span - _hoops_CGIHS;

					_hoops_HRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
				}
				goto next;
			}

			_hoops_GAGCR: {
				if (_hoops_GPHH.bottom <= y && y <= _hoops_GPHH.top) {
					if (dx >= 0) {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = pts[0].x;
						span->right.bx._hoops_HAGR._hoops_SAGCR = pts[1].x + 1;
						span->left.bz._hoops_HAGR._hoops_SAGCR  = pts[0].z;
						span->right.bz._hoops_HAGR._hoops_SAGCR = pts[1].z;
					}
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = pts[1].x;
						span->right.bx._hoops_HAGR._hoops_SAGCR = pts[0].x + 1;
						span->left.bz._hoops_HAGR._hoops_SAGCR  = pts[1].z;
						span->right.bz._hoops_HAGR._hoops_SAGCR = pts[0].z;
					}

					_hoops_HRCGH (nr, _hoops_RHISP, _hoops_CGIHS, 1, y);
				}

				goto next;
			}

			_hoops_AAGCR: {
				_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				x = pts[0].x;
				z = pts[0].z;
				_hoops_SIHHS (a0.bx);
				_hoops_SIHHS (a0.bz);

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = x;
						span->right.bx._hoops_HAGR._hoops_SAGCR = a0.bx._hoops_HAGR._hoops_SAGCR;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = z;
							span->right.bz._hoops_HAGR._hoops_SAGCR = a0.bz._hoops_HAGR._hoops_SAGCR;
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

					x = a0.bx._hoops_HAGR._hoops_SAGCR;
					z = a0.bz._hoops_HAGR._hoops_SAGCR;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_APGCR (a0.bx);
					_hoops_APGCR (a0.bz);
				}

				if (_hoops_GPHH.bottom <= y && y <= _hoops_GPHH.top) {
					++y;
					span->left.bx._hoops_HAGR._hoops_SAGCR  = x;
					span->right.bx._hoops_HAGR._hoops_SAGCR = pts[1].x + 1;
					span->left.bz._hoops_HAGR._hoops_SAGCR  = z;
					span->right.bz._hoops_HAGR._hoops_SAGCR = pts[1].z;
					++span;
				}

				if (span != _hoops_CGIHS) {
					int			rows = span - _hoops_CGIHS;

					_hoops_HRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
				}
				goto next;
			}

			_hoops_PAGCR: {
				_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				x = pts[0].x;
				z = pts[0].z;
				_hoops_SIHHS (a0.bx);
				_hoops_SIHHS (a0.bz);

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = a0.bx._hoops_HAGR._hoops_SAGCR + 1;
						span->right.bx._hoops_HAGR._hoops_SAGCR = x + 1;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = a0.bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = z;
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

					x = a0.bx._hoops_HAGR._hoops_SAGCR;
					z = a0.bz._hoops_HAGR._hoops_SAGCR;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_APGCR (a0.bx);
					_hoops_APGCR (a0.bz);
				}

				if (_hoops_GPHH.bottom <= y && y <= _hoops_GPHH.top) {
					++y;
					span->left.bx._hoops_HAGR._hoops_SAGCR  = pts[1].x;
					span->right.bx._hoops_HAGR._hoops_SAGCR = x + 1;
					span->left.bz._hoops_HAGR._hoops_SAGCR  = pts[1].z;
					span->right.bz._hoops_HAGR._hoops_SAGCR = z;
					++span;
				}

				if (span != _hoops_CGIHS) {
					int			rows = span - _hoops_CGIHS;

					_hoops_HRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
				}
				goto next;
			}
		}

	  next:
		points += _hoops_RRC;
	}
#endif
}



GLOBAL_FUNCTION void HD_Span_DC_Colorized_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				_hoops_IASGR,
	bool						single) {
#ifndef DISABLE_RASTERIZER
	_hoops_RCSIR					pts[2];
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	_hoops_GHISP				_hoops_RHISP;
	_hoops_AHISP						_hoops_CGIHS[_hoops_GGIHS];
	_hoops_AHISP alter *				_hoops_SGIHS = _hoops_CGIHS+_hoops_GGAPR(_hoops_CGIHS);
	_hoops_AHISP alter *				span;
	int							y;
	int							_hoops_RRC;
	int							offset;


	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) ||
		nr->_hoops_AHP->weight > 1) {
		HD_Std_DC_Colorized_Polyline (nr, count, points, _hoops_IASGR, single);
		return;
	}

	if (nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, _hoops_IASGR, 0,
							 0, 0, 0, 0, _hoops_RHGGA|_hoops_GPHC|
											(single ? _hoops_RAIC : _hoops_PAIC));
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	offset = (int)(nr->transform_rendition->_hoops_SHIH *
					_hoops_ISSIR(nr->transform_rendition));

	_hoops_RHISP._hoops_PIHSR = _hoops_HIHSR;
	_hoops_RHISP.contrast_color = _hoops_HC->color;
	_hoops_RHISP.pattern = FP_SOLID;

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y < pts[1].y) {
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

		pts[0].z += offset;
		pts[1].z += offset;

		y = (int)pts[0].y;
		span = _hoops_CGIHS;

		_hoops_RHISP.color = *_hoops_IASGR;
		{
			_hoops_ISGCR						a0;
			int								x;
			int								z;
			int								dx;
			int								_hoops_CRRAR;
			Int_Rectangle const &			_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

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
				_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = a0.bx._hoops_HAGR._hoops_SAGCR;
						span->right.bx._hoops_HAGR._hoops_SAGCR = a0.bx._hoops_HAGR._hoops_SAGCR + 1;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = a0.bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = a0.bz._hoops_HAGR._hoops_SAGCR;
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

					if (_hoops_CRRAR-- == 0) break;

					_hoops_APGCR (a0.bx);
					_hoops_APGCR (a0.bz);
				}

				if (span != _hoops_CGIHS) {
					int			rows = span - _hoops_CGIHS;

					_hoops_CRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
				}
				goto next;
			}

			_hoops_GAGCR: {
				if (_hoops_GPHH.bottom <= y && y <= _hoops_GPHH.top) {
					if (dx >= 0) {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = pts[0].x;
						span->right.bx._hoops_HAGR._hoops_SAGCR = pts[1].x + 1;
						span->left.bz._hoops_HAGR._hoops_SAGCR  = pts[0].z;
						span->right.bz._hoops_HAGR._hoops_SAGCR = pts[1].z;
					}
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = pts[1].x;
						span->right.bx._hoops_HAGR._hoops_SAGCR = pts[0].x + 1;
						span->left.bz._hoops_HAGR._hoops_SAGCR  = pts[1].z;
						span->right.bz._hoops_HAGR._hoops_SAGCR = pts[0].z;
					}

					_hoops_CRCGH (nr, _hoops_RHISP, _hoops_CGIHS, 1, y);
				}

				goto next;
			}

			_hoops_AAGCR: {
				_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				x = pts[0].x;
				z = pts[0].z;
				_hoops_SIHHS (a0.bx);
				_hoops_SIHHS (a0.bz);

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR	= x;
						span->right.bx._hoops_HAGR._hoops_SAGCR = a0.bx._hoops_HAGR._hoops_SAGCR;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = z;
							span->right.bz._hoops_HAGR._hoops_SAGCR = a0.bz._hoops_HAGR._hoops_SAGCR;
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

					x = a0.bx._hoops_HAGR._hoops_SAGCR;
					z = a0.bz._hoops_HAGR._hoops_SAGCR;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_APGCR (a0.bx);
					_hoops_APGCR (a0.bz);
				}

				if (_hoops_GPHH.bottom <= y && y <= _hoops_GPHH.top) {
					++y;
					span->left.bx._hoops_HAGR._hoops_SAGCR  = x;
					span->right.bx._hoops_HAGR._hoops_SAGCR = pts[1].x + 1;
					span->left.bz._hoops_HAGR._hoops_SAGCR  = z;
					span->right.bz._hoops_HAGR._hoops_SAGCR = pts[1].z;
					++span;
				}

				if (span != _hoops_CGIHS) {
					int			rows = span - _hoops_CGIHS;

					_hoops_CRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
				}
				goto next;
			}

			_hoops_PAGCR: {
				_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				x = pts[0].x;
				z = pts[0].z;
				_hoops_SIHHS (a0.bx);
				_hoops_SIHHS (a0.bz);

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR	= a0.bx._hoops_HAGR._hoops_SAGCR + 1;
						span->right.bx._hoops_HAGR._hoops_SAGCR = x + 1;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = a0.bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = z;
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

					x = a0.bx._hoops_HAGR._hoops_SAGCR;
					z = a0.bz._hoops_HAGR._hoops_SAGCR;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_APGCR (a0.bx);
					_hoops_APGCR (a0.bz);
				}

				if (_hoops_GPHH.bottom <= y && y <= _hoops_GPHH.top) {
					++y;
					span->left.bx._hoops_HAGR._hoops_SAGCR  = pts[1].x;
					span->right.bx._hoops_HAGR._hoops_SAGCR = x + 1;
					span->left.bz._hoops_HAGR._hoops_SAGCR  = pts[1].z;
					span->right.bz._hoops_HAGR._hoops_SAGCR = z;
					++span;
				}

				if (span != _hoops_CGIHS) {
					int			rows = span - _hoops_CGIHS;

					_hoops_CRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
				}
				goto next;
			}
		}

	  next:
		points += _hoops_RRC;
		if (!single)
			_hoops_IASGR++;
	}
#endif
}



GLOBAL_FUNCTION void HD_Span_DC_Gouraud_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors) {
#ifndef DISABLE_RASTERIZER
	_hoops_RCSIR					pts[2];
	RGBAS32						_hoops_IASGR[2];
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	_hoops_GHISP				_hoops_RHISP;
	_hoops_AHISP						_hoops_CGIHS[_hoops_GGIHS];
	_hoops_AHISP alter *				_hoops_SGIHS = _hoops_CGIHS+_hoops_GGAPR(_hoops_CGIHS);
	_hoops_AHISP alter *				span;
	int							y;
	int							_hoops_RRC;
	int							offset;

	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) ||
		nr->_hoops_AHP->weight > 1) {
		HD_Std_DC_Gouraud_Polyline (nr, count, points, colors);
		return;
	}

	if (nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0,
							 0, 0, 0, 0, _hoops_RHGGA|_hoops_GPHC|_hoops_AAIC);
		return;
	}


#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif

	offset = (int)(nr->transform_rendition->_hoops_SHIH *
					_hoops_ISSIR(nr->transform_rendition));

	_hoops_RHISP.contrast_color = _hoops_HC->color;
	_hoops_RHISP.pattern = FP_SOLID;
	_hoops_RHISP._hoops_CHA = _hoops_HC->_hoops_CHA;

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y < pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);
			TRUNCATE_2_POINTS (points, pts, 0, 1, z);
			_hoops_IASGR[0] = colors[0];
			_hoops_IASGR[1] = colors[1];
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			TRUNCATE_2_POINTS (points, pts, 1, 0, z);
			_hoops_CRGCR (pts[0].y, pts[1].y);
			_hoops_IASGR[0] = colors[1];
			_hoops_IASGR[1] = colors[0];
		}

		pts[0].z += offset;
		pts[1].z += offset;

		y = (int)pts[0].y;
		span = _hoops_CGIHS;

		{
			_hoops_ISGCR					a0;
			int							x;
			int							z;
			int							r;
			int							g;
			int							b;
			int							dx;
			int							_hoops_CRRAR;
			Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

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
				_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				_hoops_HAGCR (a0.r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_CRRAR);
				_hoops_HAGCR (a0.g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_CRRAR);
				_hoops_HAGCR (a0.b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_CRRAR);

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = a0.bx._hoops_HAGR._hoops_SAGCR;
						span->right.bx._hoops_HAGR._hoops_SAGCR = a0.bx._hoops_HAGR._hoops_SAGCR + 1;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = a0.bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = a0.bz._hoops_HAGR._hoops_SAGCR;
							span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= a0.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = a0.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= a0.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = a0.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= a0.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = a0.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
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

					if (_hoops_CRRAR-- == 0) break;

					_hoops_APGCR (a0.bx);
					_hoops_APGCR (a0.bz);
					_hoops_RPGCR (a0.r);
					_hoops_RPGCR (a0.g);
					_hoops_RPGCR (a0.b);
				}

				if (span != _hoops_CGIHS) {
					int			rows = span - _hoops_CGIHS;

					_hoops_SRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
				}
				goto next;
			}

			_hoops_GAGCR: {
				if (_hoops_GPHH.bottom <= y && y <= _hoops_GPHH.top) {
					if (dx >= 0) {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = pts[0].x;
						span->right.bx._hoops_HAGR._hoops_SAGCR = pts[1].x + 1;
						span->left.bz._hoops_HAGR._hoops_SAGCR  = pts[0].z;
						span->right.bz._hoops_HAGR._hoops_SAGCR = pts[1].z;
						span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= _hoops_IASGR[0].r;
						span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = _hoops_IASGR[1].r;
						span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= _hoops_IASGR[0].g;
						span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = _hoops_IASGR[1].g;
						span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= _hoops_IASGR[0].b;
						span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = _hoops_IASGR[1].b;
					}
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = pts[1].x;
						span->right.bx._hoops_HAGR._hoops_SAGCR = pts[0].x + 1;
						span->left.bz._hoops_HAGR._hoops_SAGCR  = pts[1].z;
						span->right.bz._hoops_HAGR._hoops_SAGCR = pts[0].z;
						span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= _hoops_IASGR[1].r;
						span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = _hoops_IASGR[0].r;
						span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= _hoops_IASGR[1].g;
						span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = _hoops_IASGR[0].g;
						span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= _hoops_IASGR[1].b;
						span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = _hoops_IASGR[0].b;
					}

					_hoops_SRCGH (nr, _hoops_RHISP, _hoops_CGIHS, 1, y);
				}

				goto next;
			}

			_hoops_AAGCR: {
				_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				_hoops_HAGCR (a0.r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_CRRAR);
				_hoops_HAGCR (a0.g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_CRRAR);
				_hoops_HAGCR (a0.b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_CRRAR);
				x = pts[0].x;
				z = pts[0].z;
				r = _hoops_IASGR[0].r;
				g = _hoops_IASGR[0].g;
				b = _hoops_IASGR[0].b;
				_hoops_SIHHS (a0.bx);
				_hoops_SIHHS (a0.bz);
				_hoops_PPGCR (a0.r);
				_hoops_PPGCR (a0.g);
				_hoops_PPGCR (a0.b);

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = x;
						span->right.bx._hoops_HAGR._hoops_SAGCR = a0.bx._hoops_HAGR._hoops_SAGCR;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = z;
							span->right.bz._hoops_HAGR._hoops_SAGCR = a0.bz._hoops_HAGR._hoops_SAGCR;
							span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= r;
							span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = a0.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= g;
							span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = a0.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= b;
							span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = a0.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
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

					x = a0.bx._hoops_HAGR._hoops_SAGCR;
					z = a0.bz._hoops_HAGR._hoops_SAGCR;
					r = a0.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					g = a0.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					b = a0.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_APGCR (a0.bx);
					_hoops_APGCR (a0.bz);
					_hoops_RPGCR (a0.r);
					_hoops_RPGCR (a0.g);
					_hoops_RPGCR (a0.b);
				}

				if (_hoops_GPHH.bottom <= y && y <= _hoops_GPHH.top) {
					++y;
					span->left.bx._hoops_HAGR._hoops_SAGCR  = x;
					span->right.bx._hoops_HAGR._hoops_SAGCR = pts[1].x + 1;
					span->left.bz._hoops_HAGR._hoops_SAGCR  = z;
					span->right.bz._hoops_HAGR._hoops_SAGCR = pts[1].z;
					span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= r;
					span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = _hoops_IASGR[1].r;
					span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= g;
					span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = _hoops_IASGR[1].g;
					span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR	= b;
					span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = _hoops_IASGR[1].b;
					++span;
				}

				if (span != _hoops_CGIHS) {
					int			rows = span - _hoops_CGIHS;

					_hoops_SRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
				}
				goto next;
			}

			_hoops_PAGCR: {
				_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				_hoops_HAGCR (a0.r, _hoops_IASGR[0].r, _hoops_IASGR[1].r, _hoops_CRRAR);
				_hoops_HAGCR (a0.g, _hoops_IASGR[0].g, _hoops_IASGR[1].g, _hoops_CRRAR);
				_hoops_HAGCR (a0.b, _hoops_IASGR[0].b, _hoops_IASGR[1].b, _hoops_CRRAR);
				x = pts[0].x;
				z = pts[0].z;
				r = _hoops_IASGR[0].r;
				g = _hoops_IASGR[0].g;
				b = _hoops_IASGR[0].b;
				_hoops_SIHHS (a0.bx);
				_hoops_SIHHS (a0.bz);
				_hoops_PPGCR (a0.r);
				_hoops_PPGCR (a0.g);
				_hoops_PPGCR (a0.b);

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
						span->left.bx._hoops_HAGR._hoops_SAGCR  = a0.bx._hoops_HAGR._hoops_SAGCR + 1;
						span->right.bx._hoops_HAGR._hoops_SAGCR = x + 1;

						if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
							span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
							++y;
							span->left.bz._hoops_HAGR._hoops_SAGCR  = a0.bz._hoops_HAGR._hoops_SAGCR;
							span->right.bz._hoops_HAGR._hoops_SAGCR = z;
							span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR  = a0.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = r;
							span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR  = a0.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = g;
							span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR  = a0.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
							span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = b;
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

					x = a0.bx._hoops_HAGR._hoops_SAGCR;
					z = a0.bz._hoops_HAGR._hoops_SAGCR;
					r = a0.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					g = a0.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
					b = a0.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;

					if (--_hoops_CRRAR <= 0) break;

					_hoops_APGCR (a0.bx);
					_hoops_APGCR (a0.bz);
					_hoops_RPGCR (a0.r);
					_hoops_RPGCR (a0.g);
					_hoops_RPGCR (a0.b);
				}

				if (_hoops_GPHH.bottom <= y && y <= _hoops_GPHH.top) {
					++y;
					span->left.bx._hoops_HAGR._hoops_SAGCR  = pts[1].x;
					span->right.bx._hoops_HAGR._hoops_SAGCR = x + 1;
					span->left.bz._hoops_HAGR._hoops_SAGCR  = pts[1].z;
					span->right.bz._hoops_HAGR._hoops_SAGCR = z;
					span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR  = _hoops_IASGR[1].r;
					span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = r;
					span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR  = _hoops_IASGR[1].g;
					span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = g;
					span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR  = _hoops_IASGR[1].b;
					span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR = b;
					++span;
				}

				if (span != _hoops_CGIHS) {
					int			rows = span - _hoops_CGIHS;

					_hoops_SRCGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows);
				}
				goto next;
			}
		}

	  next:
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}


GLOBAL_FUNCTION void HD_Span_DC_Phong_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes) {

	HD_Span_DC_Textured_Polyline (nr, count, points, colors, planes, null, 0, 0);
}


GLOBAL_FUNCTION void HD_Span_DC_Textured_Polyline (
	Net_Rendition const	&		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	_hoops_SSIC				param_flags) {
#ifndef DISABLE_RASTERIZER
#ifndef _hoops_IHSIP
	_hoops_RCSIR					pts[2];
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	_hoops_GHISP				_hoops_RHISP;
	_hoops_AHISP						_hoops_CGIHS[_hoops_GGIHS];
	_hoops_AHISP alter *				_hoops_SGIHS = _hoops_CGIHS+_hoops_GGAPR(_hoops_CGIHS);
	_hoops_AHISP alter *				span;
	int							y;
	Point						_hoops_RGCC[2];
	float						_hoops_GRIHS[2];
	int							lower, upper;
	int							_hoops_RRC;
	int							i;
	int							_hoops_RRIHS = 0;
	int							offset;

	static RGBA const			_hoops_ARPSH[] = {	_hoops_IGISA::_hoops_IAHHP, _hoops_IGISA::_hoops_IAHHP	};
	static _hoops_ARPA const			_hoops_ARIHS[] = {	_hoops_CGISA::_hoops_CRGA, _hoops_CGISA::_hoops_CRGA	};

#if 0
	if (!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) ||
		nr->_hoops_AHP->weight > 1) {
		HD_Std_DC_Textured_Polyline (nr, count, points, colors, planes, params, param_width, param_flags);
		return;
	}
#endif

	if (nr->transform_rendition->_hoops_HCHH != null ||
		BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, colors,
							 planes, params, param_width, param_flags, _hoops_RHGGA|_hoops_GPHC|_hoops_AAIC);
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

	offset = (int)(nr->transform_rendition->_hoops_SHIH *
		_hoops_ISSIR(nr->transform_rendition));

	_hoops_RHISP._hoops_AGP = _hoops_HC->_hoops_AGP;
	_hoops_RHISP._hoops_CHA = _hoops_HC->_hoops_CHA;

	_hoops_RHISP.contrast_color = _hoops_HC->color;
	_hoops_RHISP.pattern = FP_SOLID;

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		LOAD_ARGUMENT (points);
		TRUNCATE_2_POINTS (points, pts, 0, 1, y);

		if (pts[0].y < pts[1].y) {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 0, 1, x);
			TRUNCATE_2_POINTS (points, pts, 0, 1, z);
			lower = 0;
			upper = 1;
		}
		else {
			LOAD_ARGUMENT (points);
			TRUNCATE_2_POINTS (points, pts, 1, 0, x);
			TRUNCATE_2_POINTS (points, pts, 1, 0, z);
			_hoops_CRGCR (pts[0].y, pts[1].y);
			lower = 1;
			upper = 0;
		}

		pts[0].z += offset;
		pts[1].z += offset;

		if ((_hoops_RHISP._hoops_AGP != null &&
			 _hoops_RHISP._hoops_AGP->_hoops_ISPHP) ||
			BIT (nr->_hoops_IRR->_hoops_PPH, Rendo_LOCAL_VIEWER) ||
			BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH) ||
			params != null &&
			BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
			_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
			_hoops_SGCC const &		mat = _hoops_IHCR->_hoops_CGCC;
			_hoops_RPRA const *				_hoops_APRA;
			float							_hoops_APCP;

			/*
			 * _hoops_SSSA _hoops_GSSP _hoops_CPHH _hoops_HII _hoops_CSPH _hoops_RSSA
			 */

			if (!BIT (_hoops_IHCR->flags, _hoops_IGCC))
				HD_Validate_World_To_Screen (nr);

			_hoops_APRA = mat->_hoops_PPRA()->data.elements;

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[0]);
			_hoops_RGCC[0].x = _hoops_HPRA (_hoops_APRA, points[0]) * _hoops_APCP;
			_hoops_RGCC[0].y = _hoops_IPRA (_hoops_APRA, points[0]) * _hoops_APCP;
			_hoops_RGCC[0].z = _hoops_CPRA (_hoops_APRA, points[0]) * _hoops_APCP;
			_hoops_GRIHS[0]	= _hoops_PHCP (mat->data.elements, _hoops_RGCC[0]);

			_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[1]);
			_hoops_RGCC[1].x = _hoops_HPRA (_hoops_APRA, points[1]) * _hoops_APCP;
			_hoops_RGCC[1].y = _hoops_IPRA (_hoops_APRA, points[1]) * _hoops_APCP;
			_hoops_RGCC[1].z = _hoops_CPRA (_hoops_APRA, points[1]) * _hoops_APCP;
			_hoops_GRIHS[1]	= _hoops_PHCP (mat->data.elements, _hoops_RGCC[1]);

			_hoops_RRIHS |= _hoops_AGHGS;
		}
		else {
			_hoops_RGCC[0].x = _hoops_RGCC[0].y = _hoops_RGCC[0].z = 0.0f;
			_hoops_RGCC[1].x = _hoops_RGCC[1].y = _hoops_RGCC[1].z = 0.0f;
			_hoops_GRIHS[0]	= _hoops_GRIHS[1]		  = 1.0f;
		}

		y = (int)pts[0].y;
		span = _hoops_CGIHS;

		span->left.param_width = span->right.param_width = param_width;

		{
			_hoops_ISGCR					a0;
			_hoops_ISGCR					a1;
			_hoops_ISGCR alter			*left;
			_hoops_ISGCR alter			*right;
			int							dx;
			int							_hoops_CRRAR;
			Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

			_hoops_CRRAR = pts[1].y - pts[0].y;
			dx = pts[1].x - pts[0].x;

			if (dx == 0) {
				goto _hoops_RAGCR;
			}
			else if (dx > 0) {
				if (dx > _hoops_CRRAR) {
					left = &a0;
					right = &a1;
					goto _hoops_PRIHS;
				}
				else {
					goto _hoops_RAGCR;
				}
			}
			else {
				if (-dx > _hoops_CRRAR) {
					left = &a1;
					right = &a0;
					goto _hoops_PRIHS;
				}
				else {
					goto _hoops_RAGCR;
				}
			}

			  /* _hoops_HAR _hoops_GCSPR */

			_hoops_RAGCR: {
				if (_hoops_CRRAR) {
					_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, _hoops_CRRAR);
					_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_SIGA, colors[lower].red,	 colors[upper].red,	  _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_SHRIC, colors[lower].green, colors[upper].green, _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_PPGGS, colors[lower].blue,	 colors[upper].blue,  _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_IPAIA, planes[lower].a, planes[upper].a, _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_CPAIA, planes[lower].b, planes[upper].b, _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_HSPIR, planes[lower].c, planes[upper].c, _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_RGHGS, planes[lower].d, planes[upper].d, _hoops_CRRAR);

#ifndef DISABLE_TEXTURING
					for (i=0; i<param_width; i++) {
						_hoops_PHHHS (a0.param[i], params[(lower*param_width)+i], params[(upper*param_width)+i], _hoops_CRRAR);
						_hoops_PHHHS (a0._hoops_RSHHS[i], 0.0f, params[(upper*param_width)+i] - params[(lower*param_width)+i], _hoops_CRRAR);
						a0._hoops_PSHHS[i] = params[(lower*param_width)+i];
					}
#endif

					_hoops_PHHHS (a0._hoops_PGHGS, _hoops_RGCC[lower].x, _hoops_RGCC[upper].x, _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_HGHGS, _hoops_RGCC[lower].y, _hoops_RGCC[upper].y, _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_IGHGS, _hoops_RGCC[lower].z, _hoops_RGCC[upper].z, _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_ACHHS, 0.0f, _hoops_RGCC[upper].x - _hoops_RGCC[lower].x, _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_HCHHS, 0.0f, _hoops_RGCC[upper].y - _hoops_RGCC[lower].y, _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_ICHHS, 0.0f, _hoops_RGCC[upper].z - _hoops_RGCC[lower].z, _hoops_CRRAR);

					_hoops_PHHHS (a0._hoops_CSHHS, _hoops_GRIHS[upper] / _hoops_GRIHS[lower], 1.0f, _hoops_CRRAR);
					a0._hoops_CCHHS = _hoops_RGCC[lower].x; a0._hoops_SCHHS = _hoops_RGCC[lower].y; a0._hoops_GSHHS = _hoops_RGCC[lower].z;

					_hoops_PHHHS (a0._hoops_HSHHS, _hoops_GRIHS[lower], _hoops_GRIHS[upper], _hoops_CRRAR);

					_hoops_PCCAR {
						if (y < _hoops_GPHH.bottom)
							++y;
						else if (y > _hoops_GPHH.top)
							break;
						else {
							_hoops_IIHHS (a0.bx, span->left.bx);
							_hoops_IIHHS (a0.bx, span->right.bx);
							++span->right.bx._hoops_HAGR._hoops_SAGCR;

							if (span->left.bx._hoops_HAGR._hoops_SAGCR <= _hoops_GPHH.right &&
								span->right.bx._hoops_HAGR._hoops_SAGCR >= _hoops_GPHH.left) {
								++y;
								span->left.bz._hoops_HAGR._hoops_SAGCR  = a0.bz._hoops_HAGR._hoops_SAGCR;
								span->right.bz._hoops_HAGR._hoops_SAGCR = a0.bz._hoops_HAGR._hoops_SAGCR;
								span->left._hoops_SIGA._hoops_HAGR  = a0._hoops_SIGA._hoops_HAGR;
								span->right._hoops_SIGA._hoops_HAGR = a0._hoops_SIGA._hoops_HAGR;
								span->left._hoops_SHRIC._hoops_HAGR  = a0._hoops_SHRIC._hoops_HAGR;
								span->right._hoops_SHRIC._hoops_HAGR = a0._hoops_SHRIC._hoops_HAGR;
								span->left._hoops_PPGGS._hoops_HAGR  = a0._hoops_PPGGS._hoops_HAGR;
								span->right._hoops_PPGGS._hoops_HAGR = a0._hoops_PPGGS._hoops_HAGR;
								span->left._hoops_IPAIA._hoops_HAGR  = a0._hoops_IPAIA._hoops_HAGR;
								span->right._hoops_IPAIA._hoops_HAGR = a0._hoops_IPAIA._hoops_HAGR;
								span->left._hoops_CPAIA._hoops_HAGR  = a0._hoops_CPAIA._hoops_HAGR;
								span->right._hoops_CPAIA._hoops_HAGR = a0._hoops_CPAIA._hoops_HAGR;
								span->left._hoops_HSPIR._hoops_HAGR  = a0._hoops_HSPIR._hoops_HAGR;
								span->right._hoops_HSPIR._hoops_HAGR = a0._hoops_HSPIR._hoops_HAGR;
								span->left._hoops_RGHGS._hoops_HAGR  = a0._hoops_RGHGS._hoops_HAGR;
								span->right._hoops_RGHGS._hoops_HAGR = a0._hoops_RGHGS._hoops_HAGR;
#ifndef DISABLE_TEXTURING
								for (i=0; i<param_width; i++) {
									span->left.param[i]._hoops_HAGR	 = a0.param[i]._hoops_HAGR;
									span->right.param[i]._hoops_HAGR = a0.param[i]._hoops_HAGR;
								}
#endif
								span->left._hoops_PGHGS._hoops_HAGR  = a0._hoops_PGHGS._hoops_HAGR;
								span->right._hoops_PGHGS._hoops_HAGR = a0._hoops_PGHGS._hoops_HAGR;
								span->left._hoops_HGHGS._hoops_HAGR  = a0._hoops_HGHGS._hoops_HAGR;
								span->right._hoops_HGHGS._hoops_HAGR = a0._hoops_HGHGS._hoops_HAGR;
								span->left._hoops_IGHGS._hoops_HAGR  = a0._hoops_IGHGS._hoops_HAGR;
								span->right._hoops_IGHGS._hoops_HAGR = a0._hoops_IGHGS._hoops_HAGR;
								span->left._hoops_HSHHS._hoops_HAGR  = a0._hoops_HSHHS._hoops_HAGR;
								span->right._hoops_HSHHS._hoops_HAGR = a0._hoops_HSHHS._hoops_HAGR;

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

						if (_hoops_CRRAR-- == 0) break;

						_hoops_APGCR (a0.bx);
						_hoops_APGCR (a0.bz);
						_hoops_IHHHS (a0._hoops_SIGA);
						_hoops_IHHHS (a0._hoops_SHRIC);
						_hoops_IHHHS (a0._hoops_PPGGS);
						_hoops_IHHHS (a0._hoops_IPAIA);
						_hoops_IHHHS (a0._hoops_CPAIA);
						_hoops_IHHHS (a0._hoops_HSPIR);
						_hoops_IHHHS (a0._hoops_RGHGS);

						if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
							float	_hoops_SAASP;

							_hoops_SAASP = 1.0f / (a0._hoops_CSHHS._hoops_HAGR	+= a0._hoops_CSHHS._hoops_HGRCR);

#ifndef DISABLE_TEXTURING
							for (i=0; i<param_width; i++) {
								_hoops_IHHHS (a0._hoops_RSHHS[i]);
								a0.param[i]._hoops_HAGR	 = a0._hoops_PSHHS[i] + a0._hoops_RSHHS[i]._hoops_HAGR * _hoops_SAASP;
							}
#endif
							_hoops_IHHHS (a0._hoops_ACHHS);
							_hoops_IHHHS (a0._hoops_HCHHS);
							_hoops_IHHHS (a0._hoops_ICHHS);

							a0._hoops_PGHGS._hoops_HAGR = a0._hoops_CCHHS + a0._hoops_ACHHS._hoops_HAGR * _hoops_SAASP;
							a0._hoops_HGHGS._hoops_HAGR = a0._hoops_SCHHS + a0._hoops_HCHHS._hoops_HAGR * _hoops_SAASP;
							a0._hoops_IGHGS._hoops_HAGR = a0._hoops_GSHHS + a0._hoops_ICHHS._hoops_HAGR * _hoops_SAASP;
						}
						else {
#ifndef DISABLE_TEXTURING
							for (i=0; i<param_width; i++) {
								_hoops_IHHHS (a0.param[i]);
							}
#endif
							_hoops_IHHHS (a0._hoops_PGHGS);
							_hoops_IHHHS (a0._hoops_HGHGS);
							_hoops_IHHHS (a0._hoops_IGHGS);
						}
						_hoops_IHHHS (a0._hoops_HSHHS);
					}
				}

				if (span != _hoops_CGIHS) {
					int			rows = span - _hoops_CGIHS;

					_hoops_GACGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows, param_flags);
				}

				goto next;
			}


			_hoops_PRIHS: {
				_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, _hoops_CRRAR);
				_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_SIGA, colors[lower].red,	 colors[upper].red,	  _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_SHRIC, colors[lower].green, colors[upper].green, _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_PPGGS, colors[lower].blue,	 colors[upper].blue,  _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_IPAIA, planes[lower].a, planes[upper].a, _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_CPAIA, planes[lower].b, planes[upper].b, _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_HSPIR, planes[lower].c, planes[upper].c, _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_RGHGS, planes[lower].d, planes[upper].d, _hoops_CRRAR);

#ifndef DISABLE_TEXTURING
				for (i=0; i<param_width; i++) {
					_hoops_PHHHS (a0.param[i], params[(lower*param_width)+i], params[(upper*param_width)+i], _hoops_CRRAR);
					_hoops_PHHHS (a0._hoops_RSHHS[i], 0.0f, params[(upper*param_width)+i] - params[(lower*param_width)+i], _hoops_CRRAR);
					a0._hoops_PSHHS[i] = params[(lower*param_width)+i];
				}
#endif
				_hoops_PHHHS (a0._hoops_PGHGS, _hoops_RGCC[lower].x, _hoops_RGCC[upper].x, _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_HGHGS, _hoops_RGCC[lower].y, _hoops_RGCC[upper].y, _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_IGHGS, _hoops_RGCC[lower].z, _hoops_RGCC[upper].z, _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_ACHHS, 0.0f, _hoops_RGCC[upper].x - _hoops_RGCC[lower].x, _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_HCHHS, 0.0f, _hoops_RGCC[upper].y - _hoops_RGCC[lower].y, _hoops_CRRAR);
				_hoops_PHHHS (a0._hoops_ICHHS, 0.0f, _hoops_RGCC[upper].z - _hoops_RGCC[lower].z, _hoops_CRRAR);

				_hoops_PHHHS (a0._hoops_CSHHS, _hoops_GRIHS[upper] / _hoops_GRIHS[lower], 1.0f, _hoops_CRRAR);
				a0._hoops_CCHHS = _hoops_RGCC[lower].x; a0._hoops_SCHHS = _hoops_RGCC[lower].y; a0._hoops_GSHHS = _hoops_RGCC[lower].z;

				_hoops_PHHHS (a0._hoops_HSHHS, _hoops_GRIHS[lower], _hoops_GRIHS[upper], _hoops_CRRAR);

				_hoops_IIHHS (a0.bx, a1.bx);
				_hoops_IIHHS (a0.bz, a1.bz);
				_hoops_HHHHS (a0._hoops_SIGA, a1._hoops_SIGA);
				_hoops_HHHHS (a0._hoops_SHRIC, a1._hoops_SHRIC);
				_hoops_HHHHS (a0._hoops_PPGGS, a1._hoops_PPGGS);
				_hoops_HHHHS (a0._hoops_IPAIA, a1._hoops_IPAIA);
				_hoops_HHHHS (a0._hoops_CPAIA, a1._hoops_CPAIA);
				_hoops_HHHHS (a0._hoops_HSPIR, a1._hoops_HSPIR);
				_hoops_HHHHS (a0._hoops_RGHGS, a1._hoops_RGHGS);
#ifndef DISABLE_TEXTURING
				for (i=0; i<param_width; i++) {
					_hoops_HHHHS (a0.param[i], a1.param[i]);
					_hoops_HHHHS (a0._hoops_RSHHS[i], a1._hoops_RSHHS[i]);
					a1._hoops_PSHHS[i] = a0._hoops_PSHHS[i];
				}
#endif
				_hoops_HHHHS (a0._hoops_PGHGS, a1._hoops_PGHGS);
				_hoops_HHHHS (a0._hoops_HGHGS, a1._hoops_HGHGS);
				_hoops_HHHHS (a0._hoops_HGHGS, a1._hoops_HGHGS);
				_hoops_HHHHS (a0._hoops_HSHHS, a1._hoops_HSHHS);
				_hoops_HHHHS (a0._hoops_ACHHS, a1._hoops_ACHHS);
				_hoops_HHHHS (a0._hoops_HCHHS, a1._hoops_HCHHS);
				_hoops_HHHHS (a0._hoops_ICHHS, a1._hoops_ICHHS);

				_hoops_HHHHS (a0._hoops_CSHHS, a1._hoops_CSHHS);
				a1._hoops_CCHHS = a0._hoops_CCHHS;
				a1._hoops_SCHHS = a0._hoops_SCHHS;
				a1._hoops_GSHHS = a0._hoops_GSHHS;

				_hoops_APGCR (a1.bx);
				_hoops_APGCR (a1.bz);
				_hoops_IHHHS (a1._hoops_SIGA);
				_hoops_IHHHS (a1._hoops_SHRIC);
				_hoops_IHHHS (a1._hoops_PPGGS);
				_hoops_IHHHS (a1._hoops_IPAIA);
				_hoops_IHHHS (a1._hoops_CPAIA);
				_hoops_IHHHS (a1._hoops_HSPIR);
				_hoops_IHHHS (a1._hoops_RGHGS);

				if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
					float	_hoops_SAASP;

					_hoops_SAASP = 1.0f / (a1._hoops_CSHHS._hoops_HAGR	+= a1._hoops_CSHHS._hoops_HGRCR);
#ifndef DISABLE_TEXTURING
					for (i=0; i<param_width; i++) {
						_hoops_IHHHS (a1._hoops_RSHHS[i]);
						a1.param[i]._hoops_HAGR	 = a1._hoops_PSHHS[i] + a1._hoops_RSHHS[i]._hoops_HAGR * _hoops_SAASP;
					}
#endif
					_hoops_IHHHS (a1._hoops_ACHHS);
					_hoops_IHHHS (a1._hoops_HCHHS);
					_hoops_IHHHS (a1._hoops_ICHHS);

					a1._hoops_PGHGS._hoops_HAGR = a1._hoops_CCHHS + a1._hoops_ACHHS._hoops_HAGR * _hoops_SAASP;
					a1._hoops_HGHGS._hoops_HAGR = a1._hoops_SCHHS + a1._hoops_HCHHS._hoops_HAGR * _hoops_SAASP;
					a1._hoops_IGHGS._hoops_HAGR = a1._hoops_GSHHS + a1._hoops_ICHHS._hoops_HAGR * _hoops_SAASP;
				}
				else {
#ifndef DISABLE_TEXTURING
					for (i=0; i<param_width; i++) {
						_hoops_IHHHS (a1.param[i]);
					}
#endif
					_hoops_IHHHS (a1._hoops_PGHGS);
					_hoops_IHHHS (a1._hoops_HGHGS);
					_hoops_IHHHS (a1._hoops_IGHGS);
				}
				_hoops_IHHHS (a1._hoops_HSHHS);

				_hoops_PCCAR {
					if (y < _hoops_GPHH.bottom)
						++y;
					else if (y > _hoops_GPHH.top)
						break;
					else {
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

					if (--_hoops_CRRAR <= 0) break;

					_hoops_IIHHS (a1.bx, a0.bx);
					_hoops_IIHHS (a1.bz, a0.bz);
					_hoops_HHHHS (a1._hoops_SIGA, a0._hoops_SIGA);
					_hoops_HHHHS (a1._hoops_SHRIC, a0._hoops_SHRIC);
					_hoops_HHHHS (a1._hoops_PPGGS, a0._hoops_PPGGS);
					_hoops_HHHHS (a1._hoops_IPAIA, a0._hoops_IPAIA);
					_hoops_HHHHS (a1._hoops_CPAIA, a0._hoops_CPAIA);
					_hoops_HHHHS (a1._hoops_HSPIR, a0._hoops_HSPIR);
					_hoops_HHHHS (a1._hoops_RGHGS, a0._hoops_RGHGS);
#ifndef DISABLE_TEXTURING
					for (i=0; i<param_width; i++) {
						_hoops_HHHHS (a1.param[i], a0.param[i]);
						_hoops_HHHHS (a1._hoops_RSHHS[i], a0._hoops_RSHHS[i]);
						a0._hoops_PSHHS[i] = a1._hoops_PSHHS[i];
					}
#endif
					_hoops_HHHHS (a1._hoops_PGHGS, a0._hoops_PGHGS);
					_hoops_HHHHS (a1._hoops_HGHGS, a0._hoops_HGHGS);
					_hoops_HHHHS (a1._hoops_HGHGS, a0._hoops_HGHGS);
					_hoops_HHHHS (a1._hoops_HSHHS, a0._hoops_HSHHS);
					_hoops_HHHHS (a1._hoops_ACHHS, a0._hoops_ACHHS);
					_hoops_HHHHS (a1._hoops_HCHHS, a0._hoops_HCHHS);
					_hoops_HHHHS (a1._hoops_ICHHS, a0._hoops_ICHHS);

					_hoops_HHHHS (a1._hoops_CSHHS, a0._hoops_CSHHS);
					a0._hoops_CCHHS = a1._hoops_CCHHS;
					a0._hoops_SCHHS = a1._hoops_SCHHS;
					a0._hoops_GSHHS = a1._hoops_GSHHS;

					_hoops_APGCR (a1.bx);
					_hoops_APGCR (a1.bz);
					_hoops_IHHHS (a1._hoops_SIGA);
					_hoops_IHHHS (a1._hoops_SHRIC);
					_hoops_IHHHS (a1._hoops_PPGGS);
					_hoops_IHHHS (a1._hoops_IPAIA);
					_hoops_IHHHS (a1._hoops_CPAIA);
					_hoops_IHHHS (a1._hoops_HSPIR);
					_hoops_IHHHS (a1._hoops_RGHGS);

					if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
						float	_hoops_SAASP;

						_hoops_SAASP = 1.0f / (a1._hoops_CSHHS._hoops_HAGR	+= a1._hoops_CSHHS._hoops_HGRCR);
#ifndef DISABLE_TEXTURING
						for (i=0; i<param_width; i++) {
							_hoops_IHHHS (a1._hoops_RSHHS[i]);
							a1.param[i]._hoops_HAGR	 = a1._hoops_PSHHS[i] + a1._hoops_RSHHS[i]._hoops_HAGR * _hoops_SAASP;
						}
#endif
						_hoops_IHHHS (a1._hoops_ACHHS);
						_hoops_IHHHS (a1._hoops_HCHHS);
						_hoops_IHHHS (a1._hoops_ICHHS);

						a1._hoops_PGHGS._hoops_HAGR = a1._hoops_CCHHS + a1._hoops_ACHHS._hoops_HAGR * _hoops_SAASP;
						a1._hoops_HGHGS._hoops_HAGR = a1._hoops_SCHHS + a1._hoops_HCHHS._hoops_HAGR * _hoops_SAASP;
						a1._hoops_IGHGS._hoops_HAGR = a1._hoops_GSHHS + a1._hoops_ICHHS._hoops_HAGR * _hoops_SAASP;
					}
					else {
#ifndef DISABLE_TEXTURING
						for (i=0; i<param_width; i++) {
							_hoops_IHHHS (a1.param[i]);
						}
#endif
						_hoops_IHHHS (a1._hoops_PGHGS);
						_hoops_IHHHS (a1._hoops_HGHGS);
						_hoops_IHHHS (a1._hoops_IGHGS);
					}
					_hoops_IHHHS (a1._hoops_HSHHS);
				}

				if (span != _hoops_CGIHS) {
					int			rows = span - _hoops_CGIHS;

					_hoops_GACGH (nr, _hoops_RHISP, _hoops_CGIHS, rows, y - rows, param_flags);
				}

				goto next;
			}
		}

	  next:
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

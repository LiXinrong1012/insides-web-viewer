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
 * $Id: obf_tmp.txt 1.94 2010-06-04 21:37:18 jason Exp $
 */


#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "tandt.h"
#include "span.h"
#include "phdraw.h"


#ifndef DISABLE_RASTERIZER
local void *_hoops_RCPGS (
	Display_Context const *			_hoops_IHRHP,
	long							size) {

	if (_hoops_IHRHP->_hoops_GPHGH < size) {
		Display_Context alter		*dc;

		dc = (Display_Context alter *)_hoops_IHRHP;

		if (dc->_hoops_GPHGH > 0)
			FREE_ARRAY (dc->_hoops_RPHGH, dc->_hoops_GPHGH, char);
		POOL_ALLOC_ARRAY (dc->_hoops_RPHGH, size, char, dc->memory_pool);
		dc->_hoops_GPHGH = size;
	}

	return _hoops_IHRHP->_hoops_RPHGH;
}
#endif


GLOBAL_FUNCTION void HD_Rasterize_DC_Spans_C08_U (
	Net_Rendition const &			nr,
	_hoops_GHISP const &			_hoops_RHISP,
	_hoops_AHISP const *					span,
	int								_hoops_PHISP,
	int								bottom) {
#ifndef DISABLE_RASTERIZER
	unsigned char					color;
	int                             _hoops_ACPGS;
	_hoops_CAHHP				_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
	Int_Rectangle const & 			_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	_hoops_ACPGS = nr->_hoops_ASIR->_hoops_PSIR->_hoops_RHHHP;
	_hoops_SAHHP->_hoops_RHHHP = 0;
	color = (unsigned char)_hoops_RHISP.color._hoops_PGGCR;

	_hoops_PCCAR {
		unsigned char alter		*_hoops_RPPA;
		unsigned char			_hoops_PCPGS[_hoops_HIRSP];
		void const				*_hoops_GAAC;
		int						dx;
		DC_Point				start, end;

		/* _hoops_ARP _hoops_RH _hoops_CIGS _hoops_AIR */
		start.x = span->left.bx._hoops_HAGR._hoops_SAGCR;
		end.x	= span->right.bx._hoops_HAGR._hoops_SAGCR;

		dx = (int)(end.x - start.x);

		if (dx > 0 && start.x <= _hoops_GPHH.right && end.x > _hoops_GPHH.left) {
			--end.x;
			start.y = end.y = (float)bottom;
			start.z = (float)span->left.bz._hoops_HAGR._hoops_SAGCR;
			end.z	= (float)span->right.bz._hoops_HAGR._hoops_SAGCR;

			if (dx > _hoops_HIRSP)
				_hoops_RPPA = (unsigned char alter *)_hoops_RCPGS (nr->_hoops_SRA,
																   (long)sizeof (unsigned char) * dx);
			else
				_hoops_RPPA = _hoops_PCPGS;

			_hoops_GAAC = _hoops_RPPA;

			if (end.x > _hoops_GPHH.right) {
				int			_hoops_ARGCR = (int)(end.x - _hoops_GPHH.right);

				end.z = start.z + (end.z - start.z) * (end.x - start.x - _hoops_ARGCR) / (end.x - start.x);
				dx -= _hoops_ARGCR;
				end.x = _hoops_GPHH.right;
			}

			if (start.x < _hoops_GPHH.left) {
				int			_hoops_ARGCR = (int)(_hoops_GPHH.left - start.x);

				start.z = start.z + (end.z - start.z) * _hoops_ARGCR / (end.x - start.x);
				dx -= _hoops_ARGCR;
				start.x = _hoops_GPHH.left;
			}

			_hoops_PCCAR {
				_hoops_RPPA[0] = color;

				if (--dx == 0)
					break;

				_hoops_RPPA = &_hoops_RPPA[1];
			}

			_hoops_SSGCP (nr, &start, &end, 0, Image_MAPPED_8, 0, &_hoops_GAAC,
							   _hoops_RHISP.pattern, &_hoops_RHISP.contrast_color, null);
		}

		if (--_hoops_PHISP == 0)
			break;
		++span;
		++bottom;
	}
	_hoops_SAHHP->_hoops_RHHHP = _hoops_ACPGS;
#endif
}



GLOBAL_FUNCTION void HD_Rasterize_DC_Spans_C24_U (
	Net_Rendition const &		nr,
	_hoops_GHISP const &		_hoops_RHISP,
	_hoops_AHISP const *				span,
	int							_hoops_PHISP,
	int							bottom) {
#ifndef DISABLE_RASTERIZER
	RGBAS32						color;
	Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	_hoops_AAASP (nr->_hoops_SRA, _hoops_RHISP.color, _hoops_RHISP._hoops_PIHSR, color);

	_hoops_PCCAR {
		RGBAS32 alter *		_hoops_RPPA;
		RGBAS32				_hoops_PCPGS[_hoops_HIRSP];
		void const *		_hoops_GAAC;
		int					dx;
		DC_Point			start, end;

		/* _hoops_ARP _hoops_RH _hoops_CIGS _hoops_AIR */
		start.x = span->left.bx._hoops_HAGR._hoops_SAGCR;
		end.x	= span->right.bx._hoops_HAGR._hoops_SAGCR;

		dx = (int)(end.x - start.x);

		if (dx > 0 && start.x <= _hoops_GPHH.right && end.x > _hoops_GPHH.left) {
			--end.x;
			start.y = end.y = (float)bottom;
			start.z = (float)span->left.bz._hoops_HAGR._hoops_SAGCR;
			end.z	= (float)span->right.bz._hoops_HAGR._hoops_SAGCR;

			if (dx > _hoops_HIRSP)
				_hoops_RPPA = (RGBAS32 alter *)_hoops_RCPGS (nr->_hoops_SRA,
															  (long)sizeof (RGBAS32) * dx);
			else
				_hoops_RPPA = _hoops_PCPGS;
			_hoops_GAAC = _hoops_RPPA;

			if (end.x > _hoops_GPHH.right) {
				int			_hoops_ARGCR = (int)(end.x - _hoops_GPHH.right);

				end.z = start.z + (end.z - start.z) * (end.x - start.x - _hoops_ARGCR) / (end.x - start.x);
				dx -= _hoops_ARGCR;
				end.x = _hoops_GPHH.right;
			}

			if (start.x < _hoops_GPHH.left) {
				int			_hoops_ARGCR = (int)(_hoops_GPHH.left - start.x);

				start.z = start.z + (end.z - start.z) * _hoops_ARGCR / (end.x - start.x);
				dx -= _hoops_ARGCR;
				start.x = _hoops_GPHH.left;
			}

			_hoops_PCCAR {
				_hoops_RPPA[0] = color;

				if (--dx == 0)
					break;

				_hoops_RPPA = &_hoops_RPPA[1];
			}

			_hoops_SSGCP (nr, &start, &end, 0, _hoops_CSGSP, 0, &_hoops_GAAC,
							   _hoops_RHISP.pattern, &_hoops_RHISP.contrast_color, null);
		}

		if (--_hoops_PHISP == 0)
			break;
		++span;
		++bottom;
	}
#endif
}



GLOBAL_FUNCTION void HD_Rasterize_DC_Spans_C24_G (
	Net_Rendition const &		nr,
	_hoops_GHISP const &		_hoops_RHISP,
	_hoops_AHISP const *				span,
	int							_hoops_PHISP,
	int							bottom) {
#ifndef DISABLE_RASTERIZER
	unsigned char				_hoops_IRIR;
	Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH)
		_hoops_IRIR = (unsigned char)(255.99f * _hoops_RHISP._hoops_CHA->_hoops_IRIR);
	else
		_hoops_IRIR = _hoops_GPGCR;

	_hoops_PCCAR {
		RGBAS32 alter		*_hoops_RPPA;
		RGBAS32				_hoops_PCPGS[_hoops_HIRSP];
		void const				*_hoops_GAAC;
		int						dx;
		DC_Point				start, end;
		_hoops_GRGCR	r;
		_hoops_GRGCR	g;
		_hoops_GRGCR	b;

		start.x = span->left.bx._hoops_HAGR._hoops_SAGCR;
		end.x	= span->right.bx._hoops_HAGR._hoops_SAGCR;

		dx = (int)(end.x - start.x);

		if (dx > 0 && start.x <= _hoops_GPHH.right && end.x > _hoops_GPHH.left) {
			if (dx > _hoops_HIRSP)
				_hoops_RPPA = (RGBAS32 alter *) _hoops_RCPGS (nr->_hoops_SRA, (long)sizeof (RGBAS32) * dx);
			else
				_hoops_RPPA = _hoops_PCPGS;
			_hoops_GAAC = _hoops_RPPA;

			--end.x;
			start.y = end.y = (float)bottom;
			start.z = (float)span->left.bz._hoops_HAGR._hoops_SAGCR;
			end.z	= (float)span->right.bz._hoops_HAGR._hoops_SAGCR;

			_hoops_HAGCR (r,
						 span->left.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
						 span->right.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
						 dx);
			_hoops_HAGCR (g,
						 span->left.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
						 span->right.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
						 dx);
			_hoops_HAGCR (b,
						 span->left.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
						 span->right.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR,
						 dx);

			if (end.x > _hoops_GPHH.right) {
				int			_hoops_ARGCR = (int)(end.x - _hoops_GPHH.right);

				end.z = start.z + (end.z - start.z) * (end.x - start.x - _hoops_ARGCR) / (end.x - start.x);
				dx -= _hoops_ARGCR;
				end.x = _hoops_GPHH.right;
			}

			if (start.x < _hoops_GPHH.left) {
				int			_hoops_ARGCR = (int)(_hoops_GPHH.left - start.x);

				start.z = start.z + (end.z - start.z) * _hoops_ARGCR / (end.x - start.x);
				dx -= _hoops_ARGCR;
				start.x = _hoops_GPHH.left;

				while (_hoops_ARGCR-- > 0) {
					_hoops_RPGCR (r);
					_hoops_RPGCR (g);
					_hoops_RPGCR (b);
				}
			}

			_hoops_PCCAR {
				_hoops_RPPA[0].r = (unsigned char)r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				_hoops_RPPA[0].g = (unsigned char)g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				_hoops_RPPA[0].b = (unsigned char)b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				_hoops_RPPA[0].a = _hoops_IRIR;

				if (--dx == 0)
					break;

				_hoops_RPPA = &_hoops_RPPA[1];

				_hoops_RPGCR (r);
				_hoops_RPGCR (g);
				_hoops_RPGCR (b);
			}

			_hoops_SSGCP (nr, &start, &end, 0, _hoops_CSGSP, 0, &_hoops_GAAC,
							   _hoops_RHISP.pattern, &_hoops_RHISP.contrast_color, null);
		}

		if (--_hoops_PHISP == 0)
			break;
		++span;
		++bottom;
	}
#endif
}



GLOBAL_FUNCTION void HD_Rasterize_DC_Spans_C24_R (
	Net_Rendition const &		nr,
	_hoops_GHISP const &		_hoops_RHISP,
	_hoops_AHISP const *				span,
	int							_hoops_PHISP,
	int							bottom,
	_hoops_SSIC				param_flags) {
#ifndef DISABLE_RASTERIZER
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	unsigned char				_hoops_IRIR;
	RGB							_hoops_HCPGS;
	RGB alter					*color = &_hoops_HCPGS;
	Integer32					param_width=span->left.param_width;
	int							i;
	RGB							/*	*/ _hoops_CPHHP;
	_hoops_ARPA						plane, _hoops_ICPGS;
	Point						_hoops_SSGGA, _hoops_CCPGS, _hoops_SCPGS;
	Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH)
		_hoops_IRIR = (unsigned char)(255.99f * _hoops_RHISP._hoops_CHA->_hoops_IRIR);
	else
		_hoops_IRIR = _hoops_GPGCR;

	_hoops_CPHHP.red = _hoops_CPHHP.green = _hoops_CPHHP.blue = 0.0f;
	plane.a = plane.b = plane.c = plane.d = 0.0f;
	_hoops_ICPGS.a = _hoops_ICPGS.b = _hoops_ICPGS.c = _hoops_ICPGS.d = 0.0f;
	_hoops_SSGGA.x = _hoops_SSGGA.y = _hoops_SSGGA.z = 0.0f;
	_hoops_CCPGS.x = _hoops_CCPGS.y = _hoops_CCPGS.z = 0.0f;
	_hoops_SCPGS.x = _hoops_SCPGS.y = _hoops_SCPGS.z = 0.0f;

	_hoops_PCCAR {
		RGBAS32 alter		*_hoops_RPPA;
		RGBAS32				_hoops_PCPGS[_hoops_HIRSP];
		void const				*_hoops_GAAC;
		int						dx;
		DC_Point				start, end;
		_hoops_RSSH			param[_hoops_GSPGS],
												_hoops_RSPGS[_hoops_GSPGS],
												_hoops_ASPGS[_hoops_GSPGS];
		RGBA					_hoops_PSPGS;
		int						x;
		float					_hoops_HSPGS, _hoops_ISPGS;
		float					_hoops_CSPGS;

		start.x = span->left.bx._hoops_HAGR._hoops_SAGCR;
		end.x	= span->right.bx._hoops_HAGR._hoops_SAGCR;

		{
			int						_hoops_HAGR;

			_hoops_HAGR = (int)span->left.bx._hoops_HAGR.simple;
			_hoops_HSPGS = span->left.bx._hoops_HAGR.simple - (float)_hoops_HAGR;
			if (_hoops_HSPGS < 0.0f)
				_hoops_HSPGS += 1.0f;
			_hoops_HSPGS = 1.0f - _hoops_HSPGS;

			_hoops_HAGR = (int)span->right.bx._hoops_HAGR.simple;
			_hoops_ISPGS = span->right.bx._hoops_HAGR.simple - (float)_hoops_HAGR;
			if (_hoops_ISPGS < 0.0f)
				_hoops_ISPGS += 1.0f;
			_hoops_ISPGS = 1.0f - _hoops_ISPGS;
		}

		x = span->left.bx._hoops_HAGR._hoops_SAGCR;
		dx = (int)(end.x - start.x);

		if (dx > 0 && start.x <= _hoops_GPHH.right && end.x > _hoops_GPHH.left) {
			if (dx > _hoops_HIRSP)
				_hoops_RPPA = (RGBAS32 alter *) _hoops_RCPGS (nr->_hoops_SRA, (long)sizeof (RGBAS32) * dx);
			else
				_hoops_RPPA = _hoops_PCPGS;

			_hoops_GAAC = _hoops_RPPA;

			--end.x;
			start.y = end.y = (float)bottom;
			start.z = (float)span->left.bz._hoops_HAGR._hoops_SAGCR;
			end.z	= (float)span->right.bz._hoops_HAGR._hoops_SAGCR;

			if (BIT(span->valid, _hoops_SSPGS)) {
				color->red	 = span->left._hoops_SIGA._hoops_HAGR;
				color->green = span->left._hoops_SHRIC._hoops_HAGR;
				color->blue	 = span->left._hoops_PPGGS._hoops_HAGR;
			}

			if (BIT(span->valid, _hoops_GGHGS)) {
				plane.a		 = span->left._hoops_IPAIA._hoops_HAGR;
				plane.b		 = span->left._hoops_CPAIA._hoops_HAGR;
				plane.c		 = span->left._hoops_HSPIR._hoops_HAGR;
				plane.d		 = span->left._hoops_RGHGS._hoops_HAGR;
				(void)HI_Normalize_Plane (&plane);
			}
			if (BIT(span->valid, _hoops_AGHGS)) {
				_hoops_SSGGA.x		 = span->left._hoops_PGHGS._hoops_HAGR;
				_hoops_SSGGA.y		 = span->left._hoops_HGHGS._hoops_HAGR;
				_hoops_SSGGA.z		 = span->left._hoops_IGHGS._hoops_HAGR;
			}
#ifndef DISABLE_TEXTURING
			for (i=0; i<param_width; i++) {
				param[i] = span->left.param[i]._hoops_HAGR;
			}
#endif

			_hoops_CSPGS = 1.0f / (float)dx;

			if (BIT(span->valid, _hoops_SSPGS)) {
				_hoops_CPHHP.red	 = (span->right._hoops_SIGA._hoops_HAGR - color->red	) * _hoops_CSPGS;
				_hoops_CPHHP.green = (span->right._hoops_SHRIC._hoops_HAGR - color->green) * _hoops_CSPGS;
				_hoops_CPHHP.blue	 = (span->right._hoops_PPGGS._hoops_HAGR - color->blue) * _hoops_CSPGS;
			}
			if (BIT(span->valid, _hoops_GGHGS)) {
				_hoops_ICPGS.a	 = (span->right._hoops_IPAIA._hoops_HAGR - plane.a) * _hoops_CSPGS;
				_hoops_ICPGS.b	 = (span->right._hoops_CPAIA._hoops_HAGR - plane.b) * _hoops_CSPGS;
				_hoops_ICPGS.c	 = (span->right._hoops_HSPIR._hoops_HAGR - plane.c) * _hoops_CSPGS;
				_hoops_ICPGS.d	 = (span->right._hoops_RGHGS._hoops_HAGR - plane.d) * _hoops_CSPGS;
			}

			_hoops_CSPGS = 1.0f / (float)(dx + _hoops_HSPGS - _hoops_ISPGS);

			if (BIT(span->valid, _hoops_AGHGS)) {
				_hoops_CCPGS.x	 = (span->right._hoops_PGHGS._hoops_HAGR - _hoops_SSGGA.x) * _hoops_CSPGS;
				_hoops_CCPGS.y	 = (span->right._hoops_HGHGS._hoops_HAGR - _hoops_SSGGA.y) * _hoops_CSPGS;
				_hoops_CCPGS.z	 = (span->right._hoops_IGHGS._hoops_HAGR - _hoops_SSGGA.z) * _hoops_CSPGS;
				_hoops_SCPGS.x = (_hoops_SSGGA.x += _hoops_HSPGS * _hoops_CCPGS.x);
				_hoops_SCPGS.y = (_hoops_SSGGA.y += _hoops_HSPGS * _hoops_CCPGS.y);
				_hoops_SCPGS.z = (_hoops_SSGGA.z += _hoops_HSPGS * _hoops_CCPGS.z);
			}
#ifndef DISABLE_TEXTURING
			for (i=0; i<param_width; i++) {
				_hoops_RSPGS[i] = (span->right.param[i]._hoops_HAGR - param[i]) * _hoops_CSPGS;
				_hoops_ASPGS[i] = (param[i] += _hoops_HSPGS * _hoops_RSPGS[i]);
			}
#endif

			if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_CSGGA)) {
				Point				_hoops_CGHGS = _hoops_HPCH::_hoops_IPCH;
				_hoops_RSSH			_hoops_SGHGS[_hoops_GSPGS];
				float				_hoops_SSHGA, _hoops_GRHGS;

				_hoops_CRAGI (_hoops_SGHGS, param_width);

				{
					Point				_hoops_RRHGS;

					_hoops_RRHGS.x = span->right._hoops_PGHGS._hoops_HAGR;
					_hoops_RRHGS.y = span->right._hoops_HGHGS._hoops_HAGR;
					_hoops_RRHGS.z = span->right._hoops_IGHGS._hoops_HAGR;
					_hoops_SSHGA = _hoops_PHCP (_hoops_IHCR->_hoops_CGCC->data.elements, _hoops_RRHGS) /
							_hoops_PHCP (_hoops_IHCR->_hoops_CGCC->data.elements, _hoops_SSGGA);
				}
				_hoops_GRHGS = (1.0f - _hoops_SSHGA) * _hoops_CSPGS;

				_hoops_PCCAR {
					if (x < _hoops_GPHH.left) {
						start.x = (float)_hoops_GPHH.left;
					}
					else if (x > _hoops_GPHH.right) {
						end.x = (float)_hoops_GPHH.right;
						break;
					}
					else {
						_hoops_ARPA		_hoops_ARHGS;

						if (BIT (span->valid, _hoops_GGHGS)) {
							_hoops_ARHGS = plane;
							(void)HI_Normalize_Plane (&_hoops_ARHGS);
						}

						_hoops_ISACP (nr, _hoops_RHISP._hoops_AGP,
											 _hoops_RHISP._hoops_CHA, 
											 BIT (span->valid, _hoops_AGHGS) ? &_hoops_SSGGA : null,
											 BIT (span->valid, _hoops_SSPGS) ? color : null, 
											 BIT (span->valid, _hoops_GGHGS) ? &_hoops_ARHGS : null, 
											 null,
											 &param[0], param_width, param_flags,
											 &_hoops_PSPGS, null);
						_hoops_RPPA[0] = RGBAS32 (_hoops_PSPGS, _hoops_IRIR);
						_hoops_SIPCP (nr->_hoops_SRA, _hoops_RPPA[0]);

						_hoops_RPPA++;
					}

					if (--dx == 0)
						break;

					x++;

					if (BIT(span->valid, _hoops_SSPGS)) {
						color->red	 += _hoops_CPHHP.red;
						color->green += _hoops_CPHHP.green;
						color->blue	 += _hoops_CPHHP.blue;
					}

					if (BIT(span->valid, _hoops_GGHGS)) {
						plane.a		 += _hoops_ICPGS.a;
						plane.b		 += _hoops_ICPGS.b;
						plane.c		 += _hoops_ICPGS.c;
						plane.d		 += _hoops_ICPGS.d;
					}

					{
						float			_hoops_SAASP;

						_hoops_SAASP = 1.0f / (_hoops_SSHGA += _hoops_GRHGS);

						if (BIT(span->valid, _hoops_AGHGS)) {
							_hoops_SSGGA.x = _hoops_SCPGS.x + (_hoops_CGHGS.x += _hoops_CCPGS.x) * _hoops_SAASP;
							_hoops_SSGGA.y = _hoops_SCPGS.y + (_hoops_CGHGS.y += _hoops_CCPGS.y) * _hoops_SAASP;
							_hoops_SSGGA.z = _hoops_SCPGS.z + (_hoops_CGHGS.z += _hoops_CCPGS.z) * _hoops_SAASP;
						}

#ifndef DISABLE_TEXTURING
						for (i=0; i<param_width; i++) {
							param[i] = _hoops_ASPGS[i] + (_hoops_SGHGS[i] += _hoops_RSPGS[i]) * _hoops_SAASP;
						}
#endif
					}
				}
			}
			else {
				_hoops_PCCAR {
					if (x < _hoops_GPHH.left) {
						start.x = (float)_hoops_GPHH.left;
					}
					else if (x > _hoops_GPHH.right) {
						end.x = (float)_hoops_GPHH.right;
						break;
					}
					else {
						_hoops_ARPA		_hoops_ARHGS;

						if (BIT (span->valid, _hoops_GGHGS)) {
							_hoops_ARHGS = plane;
							(void)HI_Normalize_Plane (&_hoops_ARHGS);
						}

						_hoops_ISACP (nr, _hoops_RHISP._hoops_AGP,
											 _hoops_RHISP._hoops_CHA,
											 BIT (span->valid, _hoops_AGHGS) ? &_hoops_SSGGA : null,
											 BIT (span->valid, _hoops_SSPGS) ? color : null,
											 BIT (span->valid, _hoops_GGHGS) ? &_hoops_ARHGS : null,
											 null,
											 &param[0], param_width, param_flags,
											 &_hoops_PSPGS, null);
						_hoops_RPPA[0] = RGBAS32 (_hoops_PSPGS, _hoops_IRIR);
						_hoops_SIPCP (nr->_hoops_SRA, _hoops_RPPA[0]);

						_hoops_RPPA++;
					}

					if (--dx == 0)
						break;

					x++;

					if (BIT(span->valid, _hoops_SSPGS)) {
						color->red	 += _hoops_CPHHP.red;
						color->green += _hoops_CPHHP.green;
						color->blue	 += _hoops_CPHHP.blue;
					}
					if (BIT(span->valid, _hoops_GGHGS)) {
						plane.a		 += _hoops_ICPGS.a;
						plane.b		 += _hoops_ICPGS.b;
						plane.c		 += _hoops_ICPGS.c;
						plane.d		 += _hoops_ICPGS.d;
					}
					if (BIT(span->valid, _hoops_AGHGS)) {
						_hoops_SSGGA.x		 += _hoops_CCPGS.x;
						_hoops_SSGGA.y		 += _hoops_CCPGS.y;
						_hoops_SSGGA.z		 += _hoops_CCPGS.z;
					}
#ifndef DISABLE_TEXTURING
					for (i=0; i<param_width; i++) {
						param[i] += _hoops_RSPGS[i];
					}
#endif
				}
			}

			_hoops_SSGCP (nr, &start, &end, 0, _hoops_CSGSP, 0, &_hoops_GAAC,
							   _hoops_RHISP.pattern, &_hoops_RHISP.contrast_color, null);
		}

		if (--_hoops_PHISP == 0)
			break;
		++span;
		++bottom;
	}
#endif
}


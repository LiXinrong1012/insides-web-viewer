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
 * $Id: obf_tmp.txt 1.55 2010-06-04 21:37:19 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "patterns.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HD_Std_DC_Gouraud_Polyline (
	Net_Rendition const &		_hoops_ACRIP,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors) {
#ifndef DISABLE_DRAW_3D
	Net_Rendition				nr = _hoops_ACRIP;
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	Display_Context const *		dc = nr->_hoops_SRA;
	int const *					pattern;
	float						_hoops_ICPGH;
	int							_hoops_RRCCS;
	int							_hoops_PHPSR;
	int							section;
	float						_hoops_IIIPI;
	DC_Point					_hoops_GSGGA[32];
	RGBAS32						_hoops_ARCCS[32];
	Vector						path;
	RGB /* _hoops_AAGA */			_hoops_GHPSP;
	bool						draw;
	bool						_hoops_HASHH;
	float						r;	/* _hoops_HHAA _hoops_SGCR */
	float						factor;
	float						length;
	Line_Rendition				_hoops_ASGIP;

	if (count != 2) {
		int						_hoops_RRC;

		_hoops_ICHC (count, _hoops_RRC, 2);
		while (count-- > 0) {
			HD_Std_DC_Gouraud_Polyline (nr, 2, points, colors);
			points += _hoops_RRC;
			colors += _hoops_RRC;
		}

		return;
	}

	_hoops_HASHH = BIT(_hoops_HC->line_style->flags, LSF_SOLID);

	_hoops_ICPGH = dc->_hoops_PGCC._hoops_ICPGH;
	pattern = _hoops_HC->line_style->_hoops_GHISR[0].pattern;
	_hoops_RRCCS = _hoops_HC->line_style->_hoops_GHISR[0]._hoops_RHISR;

	if (BIT(_hoops_HC->line_style->flags, LSF_ABSOLUTE_LENGTH))
		_hoops_ICPGH = 1.0f;

	_hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify(1000000);

	HD_Replace_Line_Style(_hoops_ASGIP, nr->_hoops_GCSHP->_hoops_IHRIP);
	_hoops_ASGIP->weight = 1;

	/* _hoops_HAIR _hoops_ISGSP _hoops_IH _hoops_RH _hoops_CAGH */
	_hoops_GHPSP.red	= (float)(_hoops_IRGCR (colors[1].r) -
						  _hoops_IRGCR (colors[0].r));
	_hoops_GHPSP.green = (float)(_hoops_IRGCR (colors[1].g) -
						  _hoops_IRGCR (colors[0].g));
	_hoops_GHPSP.blue	= (float)(_hoops_IRGCR (colors[1].b) -
						  _hoops_IRGCR (colors[0].b));

	if (_hoops_ACRIP->_hoops_AHP->weight > 1) {
		r = _hoops_ACRIP->_hoops_AHP->weight * 0.5f;

		if (_hoops_ASGIP->_hoops_IHA == null) {
			_hoops_ASGIP->_hoops_IHA = nr->_hoops_IHA;
			_hoops_CIGA alter &		_hoops_SIGA = _hoops_ASGIP->_hoops_IHA.Modify(1000000);

			_hoops_SIGA->color = _hoops_HC->color;
			_hoops_SIGA->contrast_color = _hoops_HC->color;
			_hoops_SIGA->pattern = FP_SOLID;
		}
		nr->_hoops_IHA = _hoops_ASGIP->_hoops_IHA;

		nr->transform_rendition.Modify()->_hoops_CHIH = 0;

		/* _hoops_CAHP _hoops_RPAGP _hoops_SGHC */
		draw = true;
		_hoops_PHPSR = 0;
		_hoops_IIIPI = 0;

		path.x = points[1].x - points[0].x;
		path.y = points[1].y - points[0].y;
		path.z = points[1].z - points[0].z;

		factor = _hoops_SGIHR (path.x * path.x + path.y * path.y);
		if ((length = factor) > 0.0f) {
			factor = 1.0f / factor;
			path.x *= factor;
			path.y *= factor;
			path.z *= factor;

			/* _hoops_CSRA _hoops_IS _hoops_SRPA _hoops_IH _hoops_SPCC _hoops_HPP _hoops_ASPA */
			_hoops_GHPSP.red	*= factor;
			_hoops_GHPSP.green *= factor;
			_hoops_GHPSP.blue	*= factor;

			_hoops_GSGGA[0].x = points[0].x + path.y * r;
			_hoops_GSGGA[0].y = points[0].y - path.x * r;
			_hoops_GSGGA[0].z = points[0].z;
			_hoops_GSGGA[1].x = points[0].x - path.y * r;
			_hoops_GSGGA[1].y = points[0].y + path.x * r;
			_hoops_GSGGA[1].z = points[0].z;

			_hoops_ARCCS[0] = _hoops_ARCCS[1] = colors[0];

			if (!_hoops_HASHH) {
				DC_Point					tmp;

				if (_hoops_PHPSR == _hoops_RRCCS) _hoops_PHPSR = 0;
				section = (int)(_hoops_ICPGH * (float)pattern[_hoops_PHPSR++]);
				if (section < 1) section = 1;
				_hoops_IIIPI += section;

				_hoops_RGGA (_hoops_IIIPI > length) {
					if (draw) {
						tmp.x = points[0].x + _hoops_IIIPI * path.x;
						tmp.y = points[0].y + _hoops_IIIPI * path.y;
						tmp.z = points[0].z + _hoops_IIIPI * path.z;

						_hoops_GSGGA[2].x = tmp.x - path.y * r;
						_hoops_GSGGA[2].y = tmp.y + path.x * r;
						_hoops_GSGGA[2].z = tmp.z;

						_hoops_ARCCS[2].r = (unsigned char)(colors[0].r + _hoops_IIIPI * _hoops_GHPSP.red);
						_hoops_ARCCS[2].g = (unsigned char)(colors[0].g + _hoops_IIIPI * _hoops_GHPSP.green);
						_hoops_ARCCS[2].b = (unsigned char)(colors[0].b + _hoops_IIIPI * _hoops_GHPSP.blue);
						_hoops_ARCCS[2].a = colors[0].a;

						_hoops_GGCGH (nr, _hoops_GSGGA, _hoops_ARCCS);

						_hoops_GSGGA[1].x = tmp.x + path.y * r;
						_hoops_GSGGA[1].y = tmp.y - path.x * r;
						_hoops_GSGGA[1].z = tmp.z;

						_hoops_ARCCS[1] = _hoops_ARCCS[2];

						_hoops_GGCGH (nr, _hoops_GSGGA, _hoops_ARCCS);
					}
					else {
						tmp.x = points[0].x + _hoops_IIIPI * path.x;
						tmp.y = points[0].y + _hoops_IIIPI * path.y;
						tmp.z = points[0].z + _hoops_IIIPI * path.z;

						_hoops_GSGGA[0].x = tmp.x + path.y * r;
						_hoops_GSGGA[0].y = tmp.y - path.x * r;
						_hoops_GSGGA[0].z = tmp.z;
						_hoops_GSGGA[1].x = tmp.x - path.y * r;
						_hoops_GSGGA[1].y = tmp.y + path.x * r;
						_hoops_GSGGA[1].z = tmp.z;

						_hoops_ARCCS[0].r = (unsigned char)(colors[0].r + _hoops_IIIPI * _hoops_GHPSP.red);
						_hoops_ARCCS[0].g = (unsigned char)(colors[0].g + _hoops_IIIPI * _hoops_GHPSP.green);
						_hoops_ARCCS[0].b = (unsigned char)(colors[0].b + _hoops_IIIPI * _hoops_GHPSP.blue);
						_hoops_ARCCS[0].a = colors[0].a;

						_hoops_ARCCS[1] = _hoops_ARCCS[0];
					}

					draw = !draw;

					if (_hoops_PHPSR == _hoops_RRCCS) _hoops_PHPSR=0;
					section = (int)(_hoops_ICPGH * (float)pattern[_hoops_PHPSR++]);
					if (section < 1) section = 1;
					_hoops_IIIPI += section;
				}

				_hoops_IIIPI -= length;
				if (_hoops_PHPSR == _hoops_RRCCS) _hoops_PHPSR=0;
				section = (int)(_hoops_ICPGH * (float)pattern[_hoops_PHPSR++]);
				if (section < 1) section = 1;
				_hoops_IIIPI -= section;
			}

			if (draw) {
				_hoops_GSGGA[2].x = points[1].x - path.y * r;
				_hoops_GSGGA[2].y = points[1].y + path.x * r;
				_hoops_GSGGA[2].z = points[1].z;

				_hoops_ARCCS[2] = colors[1];

				_hoops_GGCGH (nr, _hoops_GSGGA, _hoops_ARCCS);

				_hoops_GSGGA[1].x = points[1].x + path.y * r;
				_hoops_GSGGA[1].y = points[1].y - path.x * r;
				_hoops_GSGGA[1].z = points[1].z;

				_hoops_ARCCS[1] = _hoops_ARCCS[2];

				_hoops_GGCGH (nr, _hoops_GSGGA, _hoops_ARCCS);
			}
		}
	}
	else if (!_hoops_HASHH) {

		draw = true;
		_hoops_PHPSR=0;
		_hoops_IIIPI = 0;

		path.x = points[1].x - points[0].x;
		path.y = points[1].y - points[0].y;
		path.z = points[1].z - points[0].z;

		factor = _hoops_SGIHR (path.x * path.x + path.y * path.y);
		if ((length = factor) > 0.0f) {
			factor = 1.0f / factor;
			path.x *= factor;
			path.y *= factor;
			path.z *= factor;

			/* _hoops_CSRA _hoops_IS _hoops_SRPA _hoops_IH _hoops_SPCC _hoops_HPP _hoops_ASPA */
			_hoops_GHPSP.red	*= factor;
			_hoops_GHPSP.green *= factor;
			_hoops_GHPSP.blue	*= factor;

			_hoops_GSGGA[0].x = points[0].x;
			_hoops_GSGGA[0].y = points[0].y;
			_hoops_GSGGA[0].z = points[0].z;

			_hoops_ARCCS[0] = colors[0];

			if (_hoops_PHPSR == _hoops_RRCCS) _hoops_PHPSR=0;
			section = (int)(_hoops_ICPGH * (float)pattern[_hoops_PHPSR++]);
			if (section < 1) section = 1;
			_hoops_IIIPI += section;

			_hoops_RGGA (_hoops_IIIPI > length) {
				if (draw) {
					_hoops_GSGGA[1].x = points[0].x + _hoops_IIIPI * path.x;
					_hoops_GSGGA[1].y = points[0].y + _hoops_IIIPI * path.y;
					_hoops_GSGGA[1].z = points[0].z + _hoops_IIIPI * path.z;

					_hoops_ARCCS[1].r = (unsigned char)(colors[0].r + _hoops_IIIPI * _hoops_GHPSP.red);
					_hoops_ARCCS[1].g = (unsigned char)(colors[0].g + _hoops_IIIPI * _hoops_GHPSP.green);
					_hoops_ARCCS[1].b = (unsigned char)(colors[0].b + _hoops_IIIPI * _hoops_GHPSP.blue);
					_hoops_ARCCS[1].a = colors[0].a;

					_hoops_SCGCP (nr, _hoops_GSGGA, _hoops_ARCCS);
				}
				else {
					_hoops_GSGGA[0].x = points[0].x + _hoops_IIIPI * path.x;
					_hoops_GSGGA[0].y = points[0].y + _hoops_IIIPI * path.y;
					_hoops_GSGGA[0].z = points[0].z + _hoops_IIIPI * path.z;

					_hoops_ARCCS[0].r = (unsigned char)(colors[0].r + _hoops_IIIPI * _hoops_GHPSP.red);
					_hoops_ARCCS[0].g = (unsigned char)(colors[0].g + _hoops_IIIPI * _hoops_GHPSP.green);
					_hoops_ARCCS[0].b = (unsigned char)(colors[0].b + _hoops_IIIPI * _hoops_GHPSP.blue);
					_hoops_ARCCS[0].a = colors[0].a;
				}

				draw = !draw;

				if (_hoops_PHPSR == _hoops_RRCCS) _hoops_PHPSR=0;
				section = (int)(_hoops_ICPGH * (float)pattern[_hoops_PHPSR++]);
				if (section < 1) section = 1;
				_hoops_IIIPI += section;
			}

			if (draw) {
				_hoops_GSGGA[1].x = points[1].x;
				_hoops_GSGGA[1].y = points[1].y;
				_hoops_GSGGA[1].z = points[1].z;

				_hoops_ARCCS[1] = colors[1];

				_hoops_SCGCP (nr, _hoops_GSGGA, _hoops_ARCCS);
			}

			_hoops_IIIPI -= length;
			if (_hoops_PHPSR == _hoops_RRCCS) _hoops_PHPSR=0;
			section = (int)(_hoops_ICPGH * (float)pattern[_hoops_PHPSR++]);
			if (section < 1) section = 1;
			_hoops_IIIPI -= section;
		}
	}
	else if (nr->transform_rendition->_hoops_HCHH != null) {
		_hoops_ASHH const *		_hoops_CRAIR;
		_hoops_GPPA const *	_hoops_GRCPR;
		int								i;
		bool							_hoops_GCGGA = false;
		DC_Point const *				prev = points++;
		float							dx, _hoops_CRRAR;
		float							_hoops_CIGGA = 0.0f, _hoops_SIGGA = 1.0f;

		_hoops_CRAIR = nr->transform_rendition->_hoops_HCHH->_hoops_PSHH;
		if ((_hoops_GRCPR = _hoops_CRAIR->_hoops_GRCPR) == null) {
			HD_Validate_Clip_Half_Planes ((_hoops_ASHH alter *)_hoops_CRAIR);
			_hoops_GRCPR = _hoops_CRAIR->_hoops_GRCPR;
		}

		/* _hoops_IHGP _hoops_IASC _hoops_PIRRC */
		if (points->x < _hoops_CRAIR->_hoops_RCHS.left && prev->x < _hoops_CRAIR->_hoops_RCHS.left ||
			points->x > _hoops_CRAIR->_hoops_RCHS.right && prev->x > _hoops_CRAIR->_hoops_RCHS.right ||
			points->y < _hoops_CRAIR->_hoops_RCHS.bottom && prev->y < _hoops_CRAIR->_hoops_RCHS.bottom ||
			points->y > _hoops_CRAIR->_hoops_RCHS.top && prev->y > _hoops_CRAIR->_hoops_RCHS.top) {
			return;
		}

		/* _hoops_PIRRC _hoops_PAR _hoops_CCPH _hoops_RGR _hoops_CAGH _hoops_HPP _hoops_GRR _hoops_HHAA-_hoops_IPPA */
		dx = points->x - prev->x;
		_hoops_CRRAR = points->y - prev->y;

		for (i=0; i<_hoops_CRAIR->count; i++) {
			float			_hoops_RCGGA, _hoops_CHGGA;

			_hoops_RCGGA =  _hoops_GRCPR[i]._hoops_SPPA.a * prev->x +
						_hoops_GRCPR[i]._hoops_SPPA.b * prev->y +
						 _hoops_GRCPR[i]._hoops_SPPA.d;
			_hoops_CHGGA = _hoops_GRCPR[i]._hoops_SPPA.a * points->x +
						_hoops_GRCPR[i]._hoops_SPPA.b * points->y +
						 _hoops_GRCPR[i]._hoops_SPPA.d;

			if (_hoops_RCGGA > 0.0f) {
				if (_hoops_CHGGA > 0.0f) {
					/* _hoops_GIPR _hoops_SIPP _hoops_RGR _hoops_PPAP */
					_hoops_CIGGA = 1.0f;
					_hoops_SIGGA = 0.0f;
					break;
				}
				else {
					/* _hoops_HSPH _hoops_ACGGA */
					float			t;

					t = -_hoops_RCGGA / (_hoops_GRCPR[i]._hoops_SPPA.a * dx + _hoops_GRCPR[i]._hoops_SPPA.b * _hoops_CRRAR);
					if (t > _hoops_CIGGA) {
						_hoops_CIGGA = t;
						if (_hoops_CIGGA > _hoops_SIGGA)
							break;
						_hoops_GCGGA = true;
					}
				}
			}
			else {
				if (_hoops_CHGGA > 0.0f) {
					/* _hoops_HSPH _hoops_PHGHR */
					float			t;

					t = -_hoops_RCGGA / (_hoops_GRCPR[i]._hoops_SPPA.a * dx + _hoops_GRCPR[i]._hoops_SPPA.b * _hoops_CRRAR);
					if (t < _hoops_SIGGA) {
						_hoops_SIGGA = t;
						if (_hoops_SIGGA < _hoops_CIGGA)
							break;
						_hoops_GCGGA = true;
					}
				}
				else {
					/* _hoops_GIPR _hoops_ASSA _hoops_RGR _hoops_PPAP */
				}
			}
		}

		/* _hoops_PGSA _hoops_PA _hoops_SGS _hoops_IGICR */
		if (_hoops_CIGGA < _hoops_SIGGA) {
			_hoops_HHCR alter &		_hoops_AHICP = nr->transform_rendition.Modify();

			_hoops_AHICP->_hoops_HCHH = null;

			if (!_hoops_GCGGA)
				_hoops_SCGCP (nr, prev, colors);
			else {
				_hoops_GSGGA[0].x = prev->x + _hoops_CIGGA * dx;
				_hoops_GSGGA[0].y = prev->y + _hoops_CIGGA * _hoops_CRRAR;
				_hoops_GSGGA[0].z = prev->z + _hoops_CIGGA * (points->z - prev->z);
				_hoops_GSGGA[1].x = prev->x + _hoops_SIGGA * dx;
				_hoops_GSGGA[1].y = prev->y + _hoops_SIGGA * _hoops_CRRAR;
				_hoops_GSGGA[1].z = prev->z + _hoops_SIGGA * (points->z - prev->z);

				_hoops_ARCCS[0].r = (unsigned char)(colors[0].r + _hoops_CIGGA * _hoops_GHPSP.red);
				_hoops_ARCCS[0].g = (unsigned char)(colors[0].g + _hoops_CIGGA * _hoops_GHPSP.green);
				_hoops_ARCCS[0].b = (unsigned char)(colors[0].b + _hoops_CIGGA * _hoops_GHPSP.blue);
				_hoops_ARCCS[0].a = colors[0].a;
				_hoops_ARCCS[1].r = (unsigned char)(colors[0].r + _hoops_SIGGA * _hoops_GHPSP.red);
				_hoops_ARCCS[1].g = (unsigned char)(colors[0].g + _hoops_SIGGA * _hoops_GHPSP.green);
				_hoops_ARCCS[1].b = (unsigned char)(colors[0].b + _hoops_SIGGA * _hoops_GHPSP.blue);
				_hoops_ARCCS[1].a = colors[1].a;

				_hoops_SCGCP (nr, _hoops_GSGGA, _hoops_ARCCS);
			}
		}
	}
	else {
		if (dc->_hoops_IPCI->draw_dc_gouraud_polyline == HD_Std_DC_Gouraud_Polyline)
			HD_Span_DC_Gouraud_Polyline (nr, 2, points, colors);
		else
			_hoops_ICGGA (nr, 2, points, colors);
	}
#endif
}

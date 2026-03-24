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
 * $Id: obf_tmp.txt 1.23 2010-06-04 21:37:19 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "hd_proto.h"
#include "span.h"


GLOBAL_FUNCTION void HD_SZB_DC_Polyline (
	Net_Rendition const &			nr,
	int								count,
	DC_Point const *				points) {
	_hoops_HCSIR alter *		_hoops_ICSIR;
	int								_hoops_RRC;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0,0,0,0,0,0, _hoops_GPHC);
		return;
	}

	_hoops_ICSIR = (_hoops_HCSIR alter *)
				nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICSIR->input.vertex[2].point = null;
	_hoops_ICSIR->input.color = nr->_hoops_IHA->color;

	_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.test = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.update = _hoops_GPSCP;
	if (BIT(nr->transform_rendition->flags, _hoops_PASP)) {
		_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP		|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.test				|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.update				|= _hoops_IRHSP;
	}

	if (count == 1) {
		_hoops_ICSIR->input.vertex[0].point = &points[0];
		_hoops_ICSIR->input.vertex[1].point = &points[0];
		HD_SZB_Process_Line (nr);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		_hoops_ICSIR->input.vertex[0].point = &points[0];
		_hoops_ICSIR->input.vertex[1].point = &points[1];

		HD_SZB_Process_Line (nr);

		points += _hoops_RRC;
	}
}

GLOBAL_FUNCTION void HD_SZB_DC_Colorized_Polyline (
	Net_Rendition const &			nr,
	int								count,
	DC_Point const *				points,
	RGBAS32 const *					colors,
	bool							single) {
	_hoops_HCSIR alter *		_hoops_ICSIR;
	int								_hoops_RRC;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0,0,0,0,0,
							 _hoops_GPHC | (single ? _hoops_RAIC : _hoops_PAIC));
		return;
	}

	_hoops_ICSIR = (_hoops_HCSIR alter *)
				nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICSIR->input.vertex[2].point = null;

	_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.test = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.update = _hoops_GPSCP;
	if (BIT(nr->transform_rendition->flags, _hoops_PASP)) {
		_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP		|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.test				|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.update				|= _hoops_IRHSP;
	}

	if (count == 1) {
		_hoops_ICSIR->input.vertex[0].point = &points[0];
		_hoops_ICSIR->input.vertex[1].point = &points[0];
		_hoops_ICSIR->input.color = *colors;
		HD_SZB_Process_Line (nr);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		_hoops_ICSIR->input.vertex[0].point = &points[0];
		_hoops_ICSIR->input.vertex[1].point = &points[1];
		_hoops_ICSIR->input.color = *colors;

		HD_SZB_Process_Line (nr);

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
}

GLOBAL_FUNCTION void HD_SZB_DC_Gouraud_Polyline (
	Net_Rendition const & 			nr,
	int								count,
	DC_Point const *				points,
	RGBAS32 const *					colors) {
	_hoops_HCSIR alter *		_hoops_ICSIR;
	int								_hoops_RRC;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0,0,0,0,0,
							 _hoops_GPHC | _hoops_AAIC);
		return;
	}

	_hoops_ICSIR = (_hoops_HCSIR alter *)
				nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	_hoops_ICSIR->input.vertex[2].point = null;
	_hoops_ICSIR->input.vertex[2].color = null;

	_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP = _hoops_RAHSP;
	_hoops_ICSIR->input._hoops_AIPRA.test = _hoops_HRHSP;
	_hoops_ICSIR->input._hoops_AIPRA.update = _hoops_GPSCP;
	if (BIT(nr->transform_rendition->flags, _hoops_PASP)) {
		_hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP		|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.test				|= _hoops_IRHSP;
		_hoops_ICSIR->input._hoops_AIPRA.update				|= _hoops_IRHSP;
	}

	if (count == 1) {
		_hoops_ICSIR->input.vertex[0].point = &points[0];
		_hoops_ICSIR->input.vertex[1].point = &points[0];
		_hoops_ICSIR->input.vertex[0].color = &colors[0];
		_hoops_ICSIR->input.vertex[1].color = &colors[0];
		HD_SZB_Process_Line (nr);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		_hoops_ICSIR->input.vertex[0].point = &points[0];
		_hoops_ICSIR->input.vertex[1].point = &points[1];
		_hoops_ICSIR->input.vertex[0].color = &colors[0];
		_hoops_ICSIR->input.vertex[1].color = &colors[1];

		HD_SZB_Process_Line (nr);

		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
}


#define _hoops_HRRGGR			0x01	/* |_hoops_CAASH| >= |_hoops_CAASH| */
#define _hoops_IRRGGR		0x02	/*	_hoops_CAASH	<	0	*/
#define _hoops_CRRGGR		0x04	/*	_hoops_CAASH	>	0	*/


GLOBAL_FUNCTION void HD_SZB_Process_Line (
	Net_Rendition const &		nr) {
#ifndef _hoops_GCSIR
	_hoops_HCSIR alter *	_hoops_ICSIR;
	_hoops_PGHSP const *			v[2];
	_hoops_RCSIR					pts[2];
	_hoops_ISGCR					a0;
	int							test, update, _hoops_PPCCP;
	int							delta;
	Int_Rectangle				_hoops_GPHH;
	int							direction;
	int							offset;

	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;

	ZERO_STRUCT (&a0, _hoops_ISGCR);


#if 0	/* _hoops_SIGP */
	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Gouraud_Line (nr, _hoops_CGICP, _hoops_SRRGGR);
		return;
	}

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Gouraud_Line (nr, _hoops_CGICP, _hoops_SRRGGR);
		return;
	}
#endif

#if 0
#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_RSSIR)) return;
#endif
#endif

	_hoops_ICSIR = (_hoops_HCSIR alter *)
				nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

	test = _hoops_ICSIR->input._hoops_AIPRA.test & ~_hoops_ICSIR->input._hoops_SASCP.test | _hoops_ICSIR->input.required.test;
	update = _hoops_ICSIR->input._hoops_AIPRA.update & ~_hoops_ICSIR->input._hoops_SASCP.update | _hoops_ICSIR->input.required.update;
	_hoops_PPCCP = _hoops_ICSIR->input._hoops_AIPRA._hoops_PPCCP & ~_hoops_ICSIR->input._hoops_SASCP._hoops_PPCCP | _hoops_ICSIR->input.required._hoops_PPCCP;

	_hoops_GPHH.left	= _hoops_IHCR->_hoops_AGAA.left	- _hoops_ICSIR->offset.x;
	_hoops_GPHH.right	= _hoops_IHCR->_hoops_AGAA.right	- _hoops_ICSIR->offset.x;
	_hoops_GPHH.bottom = _hoops_IHCR->_hoops_AGAA.bottom - _hoops_ICSIR->offset.y;
	_hoops_GPHH.top	= _hoops_IHCR->_hoops_AGAA.top	- _hoops_ICSIR->offset.y;


	/* _hoops_GHIS _hoops_GIHA _hoops_HIS _hoops_RGRCR->_hoops_PPSR._hoops_HAPC <= _hoops_IIHHR->_hoops_PPSR._hoops_HAPC */
	if (_hoops_ICSIR->input.vertex[0].point->y <= _hoops_ICSIR->input.vertex[1].point->y) {
		v[0] = &_hoops_ICSIR->input.vertex[0];
		v[1] = &_hoops_ICSIR->input.vertex[1];
	}
	else {
		v[0] = &_hoops_ICSIR->input.vertex[1];
		v[1] = &_hoops_ICSIR->input.vertex[0];
	}

	pts[0].x = (int)v[0]->point->x - _hoops_ICSIR->offset.x;
	pts[0].y = (int)v[0]->point->y - _hoops_ICSIR->offset.y;
	pts[0].z = (int)v[0]->point->z;
	pts[1].x = (int)v[1]->point->x - _hoops_ICSIR->offset.x;
	pts[1].y = (int)v[1]->point->y - _hoops_ICSIR->offset.y;
	pts[1].z = (int)v[1]->point->z;

	
	offset = (int)(nr->transform_rendition->_hoops_SHIH * 
		_hoops_ISSIR(nr->transform_rendition));
	pts[0].z += offset;
	pts[1].z += offset;

	if (pts[0].y > _hoops_GPHH.top || pts[1].y < _hoops_GPHH.bottom)
		return;

	direction = 0;
	{
		int				dx = pts[1].x - pts[0].x;
		int				_hoops_CRRAR = pts[1].y - pts[0].y;

		if (dx == 0) {
			if (pts[0].x < _hoops_GPHH.left || pts[0].x > _hoops_GPHH.right)
				return;

			delta = _hoops_CRRAR;
			direction |= _hoops_HRRGGR;
		}
		else if (dx >= 0) {
			if (pts[0].x > _hoops_GPHH.right || pts[1].x < _hoops_GPHH.left)
				return;

			direction |= _hoops_CRRGGR;
			if (dx > _hoops_CRRAR)
				delta = dx;
			else {
				delta = _hoops_CRRAR;
				direction |= _hoops_HRRGGR;
			}
		}
		else {
			if (pts[0].x < _hoops_GPHH.left || pts[1].x > _hoops_GPHH.right)
				return;

			direction |= _hoops_IRRGGR;
			dx = -dx;
			if (dx > _hoops_CRRAR)
				delta = dx;
			else {
				delta = _hoops_CRRAR;
				direction |= _hoops_HRRGGR;
			}
		}
	}

	_hoops_IAGCR (a0.bx, pts[0].x, pts[1].x, delta);
	_hoops_HAGCR (a0.y, pts[0].y, pts[1].y, delta);
	if (_hoops_PPCCP != 0) {
		if (BIT (_hoops_PPCCP, _hoops_IRHSP)) {
			_hoops_IAGCR (a0.bz, pts[0].z, pts[1].z, delta);
		}
		if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
			RGBAS32 const *		_hoops_AGCII = v[0]->color;
			RGBAS32 const *		_hoops_AIGCR = v[1]->color;

			_hoops_HAGCR (a0.r, _hoops_AGCII->r, _hoops_AIGCR->r, delta);
			_hoops_HAGCR (a0.g, _hoops_AGCII->g, _hoops_AIGCR->g, delta);
			_hoops_HAGCR (a0.b, _hoops_AGCII->b, _hoops_AIGCR->b, delta);
		}
	}
	++delta;	/* _hoops_PGSA _hoops_HACH _hoops_AIR _hoops_HAH */

	/* _hoops_RPP _hoops_APHR _hoops_SIPP _hoops_HSPH, _hoops_HPGCA _hoops_SCHIA */
/* _hoops_RGAR _hoops_SCRHA _hoops_IIHA _hoops_GPP _hoops_PRRPA _hoops_HAGA, _hoops_CCA _hoops_IRS _hoops_RSCA _hoops_RRI _hoops_IPHR, _hoops_CGH
   _hoops_SHH _hoops_SHSS _hoops_IS _hoops_CACH _hoops_RPP _hoops_HPGCA _hoops_GGR _hoops_GARGGR _hoops_GRS _hoops_HGCR _hoops_IHHH _hoops_SCHIA
*/
	{
		int				_hoops_HGCGP = 0;

		if (BIT (direction, _hoops_HRRGGR) && a0.y._hoops_HAGR._hoops_CAGCR._hoops_SAGCR < _hoops_GPHH.bottom)
			_hoops_HGCGP = _hoops_GPHH.bottom - a0.y._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
		else if (BIT (direction, _hoops_CRRGGR)) {
			int				_hoops_ARGCR = _hoops_GPHH.left - a0.bx._hoops_HAGR._hoops_SAGCR;

			if (_hoops_HGCGP < _hoops_ARGCR)
				_hoops_HGCGP = _hoops_ARGCR;
		}
		else if (BIT (direction, _hoops_IRRGGR)) {
			int				_hoops_ARGCR = a0.bx._hoops_HAGR._hoops_SAGCR - _hoops_GPHH.right;

			if (_hoops_HGCGP < _hoops_ARGCR)
				_hoops_HGCGP = _hoops_ARGCR;
		}

		if (_hoops_HGCGP != 0) {
			delta -= _hoops_HGCGP;
			_hoops_CIHHS (a0.bx, _hoops_HGCGP);
			_hoops_RHHHS (a0.y, _hoops_HGCGP);
			if (_hoops_PPCCP != 0) {
				if (BIT (_hoops_PPCCP, _hoops_IRHSP)) {
					_hoops_CIHHS (a0.bz, _hoops_HGCGP);
				}
				if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
					_hoops_RHHHS (a0.r, _hoops_HGCGP);
					_hoops_RHHHS (a0.g, _hoops_HGCGP);
					_hoops_RHHHS (a0.b, _hoops_HGCGP);
				}
			}
		}
	}

	_hoops_PCCAR {
		_hoops_RAAH alter					*_hoops_HSSIR = null;
		RGBAS32 alter				*_hoops_RPPA = null;
		unsigned char alter				*sp = null;
		_hoops_RAAH alter * const			*_hoops_PCSIR = null;
		RGBAS32 alter * const		*_hoops_ACSIR = null;
		unsigned char alter * const		*_hoops_RARGGR = null;
		int								x, y;
		int								_hoops_AARGGR = _hoops_PPHSP;

		x = a0.bx._hoops_HAGR._hoops_SAGCR;
		y = a0.y._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;

		/* _hoops_RIPPR _hoops_SIPP? */
		if (BIT (direction, _hoops_IRRGGR) && x < _hoops_GPHH.left ||
			BIT (direction, _hoops_CRRGGR) && x > _hoops_GPHH.right ||
			y > _hoops_GPHH.top)
			return;

		/* _hoops_RPP _hoops_SIPP _hoops_ARI, _hoops_PIHA _hoops_SHH _hoops_CRSH _hoops_ISCP _hoops_PPRRR _hoops_GGR */
		if (x < _hoops_GPHH.left || x > _hoops_GPHH.right || y < _hoops_GPHH.bottom)
			goto _hoops_SCAIP;

		if (_hoops_ICSIR->_hoops_HCSCP != null) {
			_hoops_RARGGR = &((unsigned char alter * alter *)
						 _hoops_ICSIR->_hoops_HCSCP->_hoops_RCPIR)[y];
			sp = &_hoops_RARGGR[0][x];
		}
		if (_hoops_ICSIR->depth_buffer != null) {
			_hoops_PCSIR = &((_hoops_RAAH alter * alter *)
						 _hoops_ICSIR->depth_buffer->_hoops_RCPIR)[y];
			_hoops_HSSIR = &_hoops_PCSIR[0][x];
		}
		if (_hoops_ICSIR->_hoops_HIAI != null) {
			_hoops_ACSIR = &((RGBAS32 alter * alter *)
						 _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[y];
			_hoops_RPPA = &_hoops_ACSIR[0][x];
		}


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
			int		_hoops_HAGR = a0.bz._hoops_HAGR._hoops_SAGCR;
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

		/* _hoops_GIPRC? */

		if (BIT (update, _hoops_IRHSP))
			*_hoops_HSSIR = a0.bz._hoops_HAGR._hoops_SAGCR;

		if (BIT (update, _hoops_GPSCP)) {
			if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
				_hoops_RPPA[0].r = (unsigned char)a0.r._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				_hoops_RPPA[0].g = (unsigned char)a0.g._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				_hoops_RPPA[0].b = (unsigned char)a0.b._hoops_HAGR._hoops_CAGCR._hoops_SAGCR;
				_hoops_RPPA[0].a = _hoops_GPGCR;
			}
			else {
				_hoops_RPPA[0] = _hoops_ICSIR->input.color;
			}
		}

		if (BIT (update, FBI_OCCLUSION)) {
			if (++_hoops_ICSIR->input._hoops_PHHSP >= _hoops_ICSIR->input._hoops_AHHSP)
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

		if (--delta == 0)
			break;


		_hoops_APGCR (a0.bx);
		_hoops_RPGCR (a0.y);
		if (_hoops_PPCCP != 0) {
			if (BIT (_hoops_PPCCP, _hoops_IRHSP))
				_hoops_APGCR (a0.bz);
			if (BIT (_hoops_PPCCP, _hoops_RAHSP)) {
				_hoops_RPGCR (a0.r);
				_hoops_RPGCR (a0.g);
				_hoops_RPGCR (a0.b);
			}
		}
	}
#endif
}

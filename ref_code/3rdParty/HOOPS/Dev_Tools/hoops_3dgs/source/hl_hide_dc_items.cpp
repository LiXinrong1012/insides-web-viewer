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
 * $Id: obf_tmp.txt 1.139 2010-09-17 21:08:40 covey Exp $
 */


#include "hoops.h"
#include "driver.h"

#ifndef _hoops_IRRHP
#include "hd_proto.h"
#include "hi_proto.h"
#include "database.h"
#include "hpserror.h"
#include "hidden.h"
#include "phedron.h"
#include "hl.h"
#include "patterns.h"




GLOBAL_FUNCTION void HD_Initialize_HL_Data (
	Display_Context alter *		dc) {
	_hoops_SGSGP alter *				data;

	POOL_ZALLOC (data, _hoops_SGSGP, dc->memory_pool);

	data->_hoops_HARHA = 1.0e-16f;

	data->dc = dc;
	dc->_hoops_SHSHP = data;
}


local void _hoops_CRASH (
	Net_Rendition const	&		nr,
	int							count,
	DC_Point const *			points,
    bool						_hoops_SRASH) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_SGSGP alter *				data = dc->_hoops_SHSHP;
	_hoops_RCRSH alter *			_hoops_RCHHR;

	POOL_ZALLOC (_hoops_RCHHR, _hoops_RCRSH, dc->memory_pool);
	_hoops_RCHHR->next = data->_hoops_CPGCP;
	data->_hoops_CPGCP = _hoops_RCHHR;
	data->_hoops_SGASH++;
	if (count < 0)
		data->_hoops_APPH += Abs(count/3);
	else
		data->_hoops_APPH += count-2;


	_hoops_RCHHR->_hoops_APHGA = nr;
	_hoops_RCHHR->_hoops_RAI = nr->_hoops_SRA->_hoops_RAI;
	_hoops_RCHHR->_hoops_RRCIP = nr->_hoops_SRA->_hoops_RRCIP;
	_hoops_RCHHR->path = nr->_hoops_SRA->path;

	_hoops_RCHHR->count = count;

	POOL_ALLOC_ARRAY_CACHED(_hoops_RCHHR->points, Abs(count), DC_Point, dc->memory_pool);
	_hoops_AIGA(points, Abs(count), DC_Point, _hoops_RCHHR->points);

    if (_hoops_SRASH) {
		int	_hoops_RRC, i;
		_hoops_ICHC (count, _hoops_RRC, 3);
		POOL_ALLOC_ARRAY(_hoops_RCHHR->_hoops_CAP, count, DC_Point, dc->memory_pool);
		for (i=0; i<count; i++) {
			_hoops_RCHHR->_hoops_CAP[i].x = (points[0].x + points[1].x + points[2].x) / 3.0f;
			_hoops_RCHHR->_hoops_CAP[i].y = (points[0].y + points[1].y + points[2].y) / 3.0f;
			_hoops_RCHHR->_hoops_CAP[i].z = (points[0].z + points[1].z + points[2].z) / 3.0f;
			points += _hoops_RRC;
		}
    }
}

local void _hoops_GAASH (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_SGSGP alter *				data = dc->_hoops_SHSHP;
	_hoops_CCRSH alter *			polyline;

	if (Abs (count) > data->_hoops_ARASH)
		data->_hoops_ARASH = count;

	POOL_ZALLOC (polyline, _hoops_CCRSH, dc->memory_pool);
	polyline->next = data->_hoops_GPHGA;
	data->_hoops_GPHGA = polyline;
	data->_hoops_GRASH++;
	if (count > 0)
		data->polyline_count += count - 1;
	else
		data->polyline_count -= count / 2;

	polyline->_hoops_APHGA = nr;
	polyline->_hoops_RAI = nr->_hoops_SRA->_hoops_RAI;
	polyline->_hoops_RRCIP = nr->_hoops_SRA->_hoops_RRCIP;
	polyline->path = nr->_hoops_SRA->path;

	polyline->count = count;
	_hoops_HAHSA (points, Abs (count), DC_Point, polyline->points, dc->memory_pool);
	if (colors != null)
		_hoops_HAHSA (colors, Abs (count), RGBAS32, polyline->colors, dc->memory_pool);

	polyline->_hoops_HSIPH = true;
}


local void _hoops_RAASH (
	DC_Point alter *	pts) {

	if (pts[0].y > pts[1].y)
		Swap (pts[0], pts[1]);
	if (pts[1].y > pts[2].y)
		Swap (pts[1], pts[2]);
	if (pts[0].y > pts[1].y)
		Swap (pts[0], pts[1]);
}


local int _hoops_AAASH (
	DC_Point const *	_hoops_GAPPA,
	DC_Point const *	_hoops_RAPPA) {

	return	(_hoops_GAPPA->x == _hoops_RAPPA->x) && (_hoops_GAPPA->y == _hoops_RAPPA->y) && (_hoops_GAPPA->z == _hoops_RAPPA->z);
}

local int _hoops_PAASH (
	DC_Point const *	pts) {

	return	!(_hoops_AAASH (pts,	pts+1) ||
			  _hoops_AAASH (pts+1, pts+2) ||
			  _hoops_AAASH (pts+2, pts));
}



/* _hoops_HAPI _hoops_HRGR _hoops_RH _hoops_RHGS _hoops_CSPP _hoops_IIGR _hoops_RH _hoops_API _hoops_SGS _hoops_SSCP _hoops_RPII
 * _hoops_HAASH _hoops_GAR _hoops_IRS _hoops_RIGR _hoops_CAPP */
/*
_hoops_IRGH _hoops_SRPC _hoops_IAASH (
	_hoops_AIIC			_hoops_CAASH,
	_hoops_AIIC			_hoops_SRRAA,
	_hoops_AIIC			_hoops_SAASH,
	_hoops_AIIC			*_hoops_GPASH) {
	_hoops_RPP (_hoops_CAASH == 0)
		*_hoops_GPASH = 0;
	_hoops_SHS _hoops_RPP ((_hoops_SRRAA < _hoops_RPASH) && (_hoops_SRRAA > -_hoops_RPASH))
		*_hoops_GPASH = _hoops_APASH;
	_hoops_SHS
		*_hoops_GPASH = _hoops_SAASH * _hoops_CAASH / _hoops_SRRAA;
}
*/


/* _hoops_SR _hoops_PAH'_hoops_RA _hoops_PPASH _hoops_CSGA _hoops_HPASH _hoops_IH _hoops_RISA _hoops_RGGHR, _hoops_HIS _hoops_RCRP _hoops_GH */
#define _hoops_ARAGA (0.01f)
#define _hoops_IPASH (0)
/*
 * _hoops_CSGA _hoops_RH _hoops_HHSPR _hoops_RGHP _hoops_IS _hoops_SHGR _hoops_IRS _hoops_III.
 * _hoops_IPCP _hoops_CCPAR _hoops_CHR _hoops_ACGIP _hoops_IH _hoops_RH _hoops_SISR _hoops_SPIS, _hoops_HIH
 *	 _hoops_RGR _hoops_API _hoops_PAH _hoops_SAHR _hoops_GAR _hoops_SSHCR _hoops_SHH _hoops_SGGA _hoops_IS _hoops_SSH
 * _hoops_CAASH _hoops_PPR _hoops_SRRAA _hoops_ACAHR _hoops_IS _hoops_RH _hoops_RSIR _hoops_III, _hoops_SAASH _hoops_HRGR _hoops_RH _hoops_RISA _hoops_AGRP _hoops_GGR _hoops_HAPC
 */
#define _hoops_CPASH(dx,_hoops_CRRAR,_hoops_SPASH,_hoops_GHASH)							\
{																\
	if ((dx) == 0)												\
		*(_hoops_GHASH) = 0;											\
	else if (((_hoops_CRRAR) < _hoops_ARAGA) && ((_hoops_CRRAR) > -_hoops_ARAGA))	\
		*(_hoops_GHASH) = _hoops_IPASH;									\
	else														\
		*(_hoops_GHASH) = (_hoops_SPASH) * (dx) / (_hoops_CRRAR);						\
}


/*
 * _hoops_RGR _hoops_RIGR _hoops_RHASH _hoops_CRAPH-_hoops_SRGGA _hoops_AHCA _hoops_RH _hoops_SSH-_hoops_IRSS
 * _hoops_PIP: _hoops_IGIPR _hoops_SGS _hoops_AHASH _hoops_PPR _hoops_PHASH _hoops_CHR _hoops_HHASH.
 */
#define _hoops_IHASH(_hoops_RPSPA,_hoops_GGHCR,_hoops_AGHCR,_hoops_APSPA)						\
{																		\
	(_hoops_APSPA)->x = (float)(((_hoops_AGHCR)*(_hoops_RPSPA)->x) + (-(_hoops_GGHCR)	 *(_hoops_RPSPA)->y));\
	(_hoops_APSPA)->y = (float)(((_hoops_GGHCR)  *(_hoops_RPSPA)->x) +	((_hoops_AGHCR)*(_hoops_RPSPA)->y));\
	(_hoops_APSPA)->z = (_hoops_RPSPA)->z;											\
}


#define _hoops_CHASH (0.7071067811865f)
#define _hoops_SHASH (0.15f)
/*
 * _hoops_RPP _hoops_RH _hoops_HSP _hoops_HSGP _hoops_CSAP _hoops_CHIA _hoops_GGR _hoops_RH _hoops_CCSHP _hoops_III _hoops_CCH,
 *	  _hoops_RGR _hoops_API _hoops_APPP _hoops_PICP _hoops_IIGR _hoops_SCH.
 * _hoops_IH _hoops_RH _hoops_GCGC _hoops_IIGR _hoops_RCAPH _hoops_RH _hoops_CCPAR _hoops_GIASH, _hoops_RIASH, _hoops_AIASH, _hoops_SCGGR, _hoops_PPR _hoops_SRRAA,
 *	  _hoops_III 1 _hoops_HRGR _hoops_GAPA _hoops_PRPC _hoops_PPR _hoops_IRGP,
 *	  _hoops_III 2 _hoops_HRGR _hoops_GAPA _hoops_PRPC _hoops_PPR _hoops_SCIA, _hoops_PPR
 *	  _hoops_III 3 _hoops_HRGR _hoops_GAPA _hoops_IRGP _hoops_PPR _hoops_SCIA.
 */
local void _hoops_PIASH (
	Net_Rendition const &	nr,
	DC_Point const *		points) {
	int						pattern = nr->_hoops_IHA->pattern;
	int						_hoops_HIASH = 0;
	DC_Point				pts[3], _hoops_IIASH[3], _hoops_CIASH[3];
	double dx1, dx2, dx3;
	double _hoops_AHAIP, _hoops_PHAIP, _hoops_SIASH;
	double _hoops_GCASH, _hoops_RCASH, _hoops_ACASH;
	double _hoops_PCASH, _hoops_HCASH, _hoops_ICASH;
	double _hoops_CCASH, _hoops_SCASH, _hoops_GSASH;
	double _hoops_RSASH, _hoops_ASASH, _hoops_PSASH;
	double _hoops_HSASH, _hoops_ISASH, _hoops_CSASH;
	double _hoops_SSASH, _hoops_GGPSH, yy;
	double _hoops_RGPSH, _hoops_AGPSH;
	double _hoops_GGHCR, _hoops_AGHCR;

	if (!_hoops_PAASH (points))
		return;

	switch (pattern) {
		case FP_CROSSHATCH:
			pattern = FP_HORIZONTAL_BARS;
			_hoops_HIASH = FP_VERTICAL_BARS;
			break;

		case FP_DIAMONDS:
			pattern = FP_SLANT_LEFT;
			_hoops_HIASH = FP_SLANT_RIGHT;
			break;
	}

	while (pattern) {
		/* _hoops_CSGA _hoops_RH _hoops_HSGP _hoops_PPR _hoops_RH _hoops_PGPSH */
		_hoops_SSASH = (double) nr->_hoops_SRA->_hoops_PGCC._hoops_PRPSR.y /
								 nr->_hoops_SRA->_hoops_PGCC.size.y;

		switch (pattern) {
			case FP_HORIZONTAL_BARS:
				_hoops_GGHCR   = 0;
				_hoops_AGHCR = 1;
				break;
			case FP_VERTICAL_BARS:
				_hoops_GGHCR   = 1;
				_hoops_AGHCR = 0;
				_hoops_SSASH = (double) nr->_hoops_SRA->_hoops_PGCC._hoops_PRPSR.x /
										 nr->_hoops_SRA->_hoops_PGCC.size.x;
				break;

			/* _hoops_SRPA _hoops_RCSA & _hoops_SGGGH _hoops_RPP _hoops_RPP _hoops_HAR _hoops_RRAA _hoops_ASPA? */
			case FP_SLANT_LEFT:
				_hoops_GGHCR   = _hoops_CHASH;
				_hoops_AGHCR = _hoops_CHASH;
				break;
			case FP_SLANT_RIGHT:
				_hoops_GGHCR   = _hoops_CHASH;
				_hoops_AGHCR = -_hoops_CHASH;
				break;

			default:
				return;	 /* _hoops_PSP _hoops_RII _hoops_PAIA _hoops_CHR _hoops_APP */
		}

		_hoops_GGPSH = (int)(_hoops_SSASH * _hoops_SHASH);
		if (_hoops_GGPSH < 1) _hoops_GGPSH = 1;

		/* _hoops_HGPSH _hoops_IRSHR _hoops_PPR _hoops_IPS */
		_hoops_IHASH (&points[0], _hoops_GGHCR, _hoops_AGHCR, &pts[0]);
		_hoops_IHASH (&points[1], _hoops_GGHCR, _hoops_AGHCR, &pts[1]);
		_hoops_IHASH (&points[2], _hoops_GGHCR, _hoops_AGHCR, &pts[2]);
		_hoops_RAASH (pts);

		dx1 = pts[1].x - pts[0].x;
		dx2 = pts[2].x - pts[0].x;
		dx3 = pts[2].x - pts[1].x;
		_hoops_AHAIP = pts[1].y - pts[0].y;
		_hoops_PHAIP = pts[2].y - pts[0].y;
		_hoops_SIASH = pts[2].y - pts[1].y;
		_hoops_GCASH = pts[1].z - pts[0].z;
		_hoops_RCASH = pts[2].z - pts[0].z;
		_hoops_ACASH = pts[2].z - pts[1].z;
		_hoops_CPASH (dx1, _hoops_AHAIP, _hoops_GGPSH, &_hoops_PCASH);
		_hoops_CPASH (dx2, _hoops_PHAIP, _hoops_GGPSH, &_hoops_HCASH);
		_hoops_CPASH (dx3, _hoops_SIASH, _hoops_GGPSH, &_hoops_ICASH);
		_hoops_CPASH (_hoops_GCASH, _hoops_AHAIP, _hoops_GGPSH, &_hoops_CCASH);
		_hoops_CPASH (_hoops_RCASH, _hoops_PHAIP, _hoops_GGPSH, &_hoops_SCASH);
		_hoops_CPASH (_hoops_ACASH, _hoops_SIASH, _hoops_GGPSH, &_hoops_GSASH);

		if (pts[0].y > 0) {
			_hoops_RGPSH = _hoops_GGPSH - ((int)pts[0].y % (int)_hoops_GGPSH);
			_hoops_RGPSH += (int)pts[0].y - pts[0].y;
		}
		else {
			_hoops_RGPSH = -((int)pts[0].y % (int)_hoops_GGPSH);
			_hoops_RGPSH += (int)pts[0].y - pts[0].y;
		}
		if (pts[1].y > 0) {
			_hoops_AGPSH = _hoops_GGPSH - ((int)pts[1].y % (int)_hoops_GGPSH);
			_hoops_AGPSH += (int)pts[1].y - pts[1].y;
		}
		else {
			_hoops_AGPSH = -((int)pts[1].y % (int)_hoops_GGPSH);
			_hoops_AGPSH += (int)pts[1].y - pts[1].y;
		}
		_hoops_CPASH (dx1, _hoops_AHAIP, _hoops_RGPSH, &_hoops_RSASH);
		_hoops_CPASH (dx2, _hoops_PHAIP, _hoops_RGPSH, &_hoops_ASASH);
		_hoops_CPASH (dx3, _hoops_SIASH, _hoops_AGPSH, &_hoops_PSASH);
		_hoops_CPASH (_hoops_GCASH, _hoops_AHAIP, _hoops_RGPSH, &_hoops_HSASH);
		_hoops_CPASH (_hoops_RCASH, _hoops_PHAIP, _hoops_RGPSH, &_hoops_ISASH);
		_hoops_CPASH (_hoops_ACASH, _hoops_SIASH, _hoops_AGPSH, &_hoops_CSASH);

		_hoops_IIASH[0].x = (float)(pts[0].x + _hoops_RSASH);
		_hoops_IIASH[1].x = (float)(pts[0].x + _hoops_ASASH);
		yy = pts[0].y + _hoops_RGPSH;	 /* _hoops_PHHR _hoops_IS _hoops_HISGR _hoops_SHHP _hoops_III _hoops_ARRS _hoops_IGPSH[0] */
		_hoops_IIASH[0].y = _hoops_IIASH[1].y = (float)yy;
		_hoops_IIASH[0].z = (float)(pts[0].z + _hoops_HSASH);
		_hoops_IIASH[1].z = (float)(pts[0].z + _hoops_ISASH);

		/* _hoops_CGPSH _hoops_HII _hoops_RH _hoops_PRPC _hoops_SGPSH _hoops_IS _hoops_RH _hoops_IRGP */
		for (; yy < pts[1].y;) {
			_hoops_IHASH	(&_hoops_IIASH[0], -_hoops_GGHCR, _hoops_AGHCR, &_hoops_CIASH[0]);
			_hoops_IHASH	(&_hoops_IIASH[1], -_hoops_GGHCR, _hoops_AGHCR, &_hoops_CIASH[1]);
			_hoops_GAASH (nr, 2, _hoops_CIASH, null);
			_hoops_IIASH[0].x += (float)_hoops_PCASH;
			_hoops_IIASH[1].x += (float)_hoops_HCASH;
			yy += _hoops_GGPSH;
			_hoops_IIASH[0].y = (float)yy;
			_hoops_IIASH[1].y = (float)yy;
			_hoops_IIASH[0].z += (float)_hoops_CCASH;
			_hoops_IIASH[1].z += (float)_hoops_SCASH;
		}

		_hoops_IIASH[0].x = (float)(pts[1].x + _hoops_PSASH);
		_hoops_IIASH[0].z = (float)(pts[1].z + _hoops_CSASH);
		/* _hoops_CGPSH _hoops_HII _hoops_RH _hoops_IRGP _hoops_SGPSH _hoops_IS _hoops_RH _hoops_SCIA */
		for (; yy < pts[2].y;) {
			_hoops_IHASH	(&_hoops_IIASH[0], -_hoops_GGHCR, _hoops_AGHCR, &_hoops_CIASH[0]);
			_hoops_IHASH	(&_hoops_IIASH[1], -_hoops_GGHCR, _hoops_AGHCR, &_hoops_CIASH[1]);
			_hoops_GAASH (nr, 2, _hoops_CIASH, null);
			_hoops_IIASH[0].x += (float)_hoops_ICASH;
			_hoops_IIASH[1].x += (float)_hoops_HCASH;
			yy += _hoops_GGPSH;
			_hoops_IIASH[0].y = (float)yy;
			_hoops_IIASH[1].y = (float)yy;
			_hoops_IIASH[0].z += (float)_hoops_GSASH;
			_hoops_IIASH[1].z += (float)_hoops_SCASH;
		}

		pattern = _hoops_HIASH;
		_hoops_HIASH = 0;
	}
}

GLOBAL_FUNCTION void HD_HL_DC_Polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	RGB							_hoops_HIHIP;
	bool						_hoops_SRASH = false;

	if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < nr->_hoops_ASIR->_hoops_GCCI._hoops_CHCRP)
		return;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP) ||
		nr->transform_rendition->_hoops_HCHH != null) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC|_hoops_RHGGA);
		return;
	}

	/* _hoops_SCPH _hoops_HII _hoops_HCGR _hoops_CHR _hoops_HAICP, _hoops_HIASR _hoops_CCA "_hoops_SRGS _hoops_RSSI" _hoops_CHR _hoops_GIR _hoops_GGR _hoops_IRS _hoops_GIAH _hoops_RIH */
	if (nr->_hoops_SRA->_hoops_RAI != null &&
		nr->_hoops_SRA->_hoops_RAI->type == _hoops_AGCP)
		_hoops_SRASH = true;

	_hoops_CRASH (nr, count, points, _hoops_SRASH);

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		int	_hoops_RRC;

		/* _hoops_RGR _hoops_ICSHR _hoops_IIGR _hoops_RRGR _hoops_IS _hoops_RGHH _hoops_AIRC _hoops_CSAP _hoops_RIRRR _hoops_PPR _hoops_SHII _hoops_HII _hoops_GRPSH._hoops_GSGGR */
		Net_Rendition				_hoops_RRPSH = nr;
		Line_Rendition alter &		_hoops_AHISA = _hoops_RRPSH.Modify()->_hoops_AHP.Modify();
		_hoops_AHISA->_hoops_CPA = nr->_hoops_IHA->_hoops_CPA + 123456;

		_hoops_HIHIP.red   = (float)_hoops_SPIGH (nr);
		_hoops_HIHIP.green = (float)_hoops_GHIGH (nr);
		_hoops_HIHIP.blue  = (float)_hoops_RHIGH (nr);
		_hoops_ICHIP (_hoops_RRPSH, &_hoops_HIHIP, true);

		_hoops_ICHC (count, _hoops_RRC, 3);
		while (count--) {
			_hoops_PIASH (_hoops_RRPSH, points);
			points += _hoops_RRC;
		}
	}
}

GLOBAL_FUNCTION void HD_HL_DC_Colorized_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						single) {
	UNREFERENCED (colors);
	UNREFERENCED (single);

	if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < nr->_hoops_ASIR->_hoops_GCCI._hoops_CHCRP)
		return;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP) ||
		nr->transform_rendition->_hoops_HCHH != null) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC|_hoops_RHGGA);
		return;
	}

	HD_HL_DC_Polytriangle (nr, count, points);
}



GLOBAL_FUNCTION void HD_HL_DC_Gouraud_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors) {
	UNREFERENCED (colors);

	if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < nr->_hoops_ASIR->_hoops_GCCI._hoops_CHCRP)
		return;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP) ||
		nr->transform_rendition->_hoops_HCHH != null) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC|_hoops_RHGGA);
		return;
	}

	HD_HL_DC_Polytriangle (nr, count, points);
}


GLOBAL_FUNCTION void HD_HL_DC_Phong_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes) {
#ifndef DISABLE_PHONG
	UNREFERENCED (colors);
	UNREFERENCED (planes);

	if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < nr->_hoops_ASIR->_hoops_GCCI._hoops_CHCRP)
		return;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP) ||
		nr->transform_rendition->_hoops_HCHH != null) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC|_hoops_RHGGA);
		return;
	}

	HD_HL_DC_Polytriangle (nr, count, points);
#endif
}

GLOBAL_FUNCTION void HD_HL_DC_Textured_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	_hoops_SSIC				param_flags) {
#ifndef DISABLE_PHONG
	UNREFERENCED (colors);
	UNREFERENCED (planes);
	UNREFERENCED (params);
	UNREFERENCED (param_width);
	UNREFERENCED (param_flags);

	if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < nr->_hoops_ASIR->_hoops_GCCI._hoops_CHCRP)
		return;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP) ||
		nr->transform_rendition->_hoops_HCHH != null) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC|_hoops_RHGGA);
		return;
	}

	HD_HL_DC_Polytriangle (nr, count, points);
#endif
}




GLOBAL_FUNCTION void HD_HL_DC_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	_hoops_SGSGP alter *				data = nr->_hoops_SRA->_hoops_SHSHP;
	Line_Rendition const &		_hoops_HC = nr->_hoops_AHP;
	_hoops_GPGGA				_hoops_SGII = _hoops_SHASP;
	int							weight;

	if ((weight = _hoops_HC->weight) < 0)
		weight = (int)(HD_Compute_Generic_Size (nr,	 _hoops_HC->_hoops_PHP,  _hoops_HC->_hoops_HHP, 1.0f, false, 0, true)+0.5f);
	if (weight < 1)
		weight = 1;

	if (!data->_hoops_IRASH && weight == 1 &&
		!BIT (nr->transform_rendition->flags, _hoops_AIHS) &&
		!BIT(_hoops_HC->flags, _hoops_SRPI) &&
		 BIT (_hoops_HC->line_style->flags, LSF_SOLID) &&
		!ANYBIT (_hoops_HC->line_style->flags, LSF_COMPLEX_ANYBITS)) {

		Int_Rectangle const &	_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

		_hoops_SASC	cuboid(Abs (count), (Point const *)points);

		if (cuboid.min.x > _hoops_GPHH.right ||
			cuboid.max.x < _hoops_GPHH.left ||
			cuboid.min.y > _hoops_GPHH.top ||
			cuboid.max.y < _hoops_GPHH.bottom)
			return;

		if (cuboid.min.x < _hoops_GPHH.left ||
			cuboid.max.x > _hoops_GPHH.right ||
			cuboid.min.y < _hoops_GPHH.bottom ||
			cuboid.max.y > _hoops_GPHH.top)
			_hoops_SGII |= _hoops_PHGGA;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP))
		_hoops_SGII |= _hoops_GPHC;

	if (_hoops_SGII) {
		HD_Clip_DC_Polyline (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_SGII);
		return;
	}

	_hoops_GAASH (nr, count, points, null);
}

GLOBAL_FUNCTION void HD_HL_DC_Colorized_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						single) {
	RGBAS32						_hoops_ARPSH[2];
	int							_hoops_RRC;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0,
			0, 0, 0, 0, _hoops_GPHC|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		_hoops_ARPSH[0] = _hoops_ARPSH[1] = *colors;
		_hoops_GAASH (nr, 2, points, _hoops_ARPSH);

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
}

GLOBAL_FUNCTION void HD_HL_DC_Gouraud_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point	const *			points,
	RGBAS32	const *				colors) {

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0,
			0, 0, 0, 0, _hoops_GPHC|_hoops_AAIC);
		return;
	}

	_hoops_GAASH (nr, count, points, colors);
}

GLOBAL_FUNCTION void HD_HL_DC_Phong_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes) {
#ifndef DISABLE_PHONG
	RGBAS32						_hoops_ARPSH[2];
	int							_hoops_RRC;

	UNREFERENCED (planes);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, colors,
			null, null, 0, 0, _hoops_GPHC|_hoops_AAIC);
		return;
	}

	if (colors != null) {
		_hoops_ICHC (count, _hoops_RRC, 2);
		while (count-- > 0) {
			_hoops_ARPSH[0] = _hoops_ARPSH[1] = *colors;
			_hoops_GAASH (nr, 2, points, _hoops_ARPSH);

			points += _hoops_RRC;
			colors += _hoops_RRC;
		}
	}
	else
		_hoops_GAASH (nr, count, points, null);
#endif
}

GLOBAL_FUNCTION void HD_HL_DC_Textured_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	_hoops_SSIC				param_flags) {
#ifndef DISABLE_PHONG
	RGBAS32						_hoops_ARPSH[2];
	int							_hoops_RRC;

	UNREFERENCED (planes);
	UNREFERENCED (params);
	UNREFERENCED (param_width);
	UNREFERENCED (param_flags);

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, colors,
			null, null, 0, 0, _hoops_GPHC|_hoops_AAIC);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		if (colors) {
			_hoops_ARPSH[0] = _hoops_ARPSH[1] = *colors;
			_hoops_GAASH (nr, 2, points, _hoops_ARPSH);
		}
		else {
			_hoops_GAASH (nr, 2, points, null);
		}

		points += _hoops_RRC;
		if (colors)
			colors += _hoops_RRC;
	}
#endif
}


GLOBAL_FUNCTION void HD_HL_3D_Image (
	Net_Rendition const & 		nr,
	Image const *				image) {
	float						_hoops_IACC, _hoops_CACC, _hoops_SACC;
	int							width, height;
	DC_Point					box[5];

	if (!HD_Calc_Image_Position_And_Size (nr, image, &width, &height, &_hoops_IACC, &_hoops_CACC, &_hoops_SACC))
		return;

	box[0].x = box[2].x = _hoops_IACC - width  * 0.5f;
	box[1].x = box[3].x = _hoops_IACC + width  * 0.5f;
	box[0].y = box[1].y = _hoops_CACC - height * 0.5f;
	box[2].y = box[3].y = _hoops_CACC + height * 0.5f;
	box[0].z = box[1].z = box[2].z = box[3].z = _hoops_SACC;

	_hoops_CRASH (nr, 4, box, false);

	if (BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RHCRP) &&
		!BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_HPCRP)) {
		box[4].x = box[0].x;
		box[4].y = box[0].y;
		box[4].z = box[0].z;

		/* _hoops_IRHH _hoops_SCH _hoops_IRS _hoops_III */
		box[2].x = box[1].x;
		box[3].x = box[0].x;

		_hoops_GAASH (nr, 5, box, null);
	}
}

GLOBAL_FUNCTION void HD_HL_DC_Text_Rasters (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							row_bytes,
	RGBAS32 const *				rasters) {

		UNREFERENCED(row_bytes);
		int width = end->x - start->x + 1;
		for (int i = 0; i < width; i++) {
			if (rasters->a != 0) {
				DC_Point pt = *start;
				pt.x += i;
				HD_HL_DC_Colorized_Polydot(nr, 1, &pt, rasters, true);
			}
			++rasters;
		}
}


GLOBAL_FUNCTION void HD_HL_DC_Image (
	Net_Rendition const &		nr,
	DC_Point const *			start,
	DC_Point const *			end,
	int							hoffset,
	Image_Format				format,
	int							row_bytes,
	void const * const *		rasters,
	int							pattern,
	Driver_Color const *		contrast_color,
	Image const *				db_image) {
#if 0
	_hoops_SGSGP alter *				data = nr->_hoops_SRA->_hoops_SHSHP;
#endif
	DC_Point					box[5];

	UNREFERENCED(db_image);
	UNREFERENCED(contrast_color);
	UNREFERENCED(pattern);
	UNREFERENCED(rasters);
	UNREFERENCED(row_bytes);
	UNREFERENCED(format);
	UNREFERENCED(hoffset);

	box[0].x = box[2].x = start->x;
	box[1].x = box[3].x = end->x;
	box[0].y = box[1].y = end->y;
	box[2].y = box[3].y = start->y;
	box[0].z = box[1].z = box[2].z = box[3].z = start->z;

	_hoops_CRASH (nr, 4, box, false);

	if (BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RHCRP) &&
		!BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_HPCRP)) {

		box[4].x = box[0].x;
		box[4].y = box[0].y;
		box[4].z = box[0].z;

		/* _hoops_IRHH _hoops_SCH _hoops_IRS _hoops_III */
		box[2].x = box[1].x;
		box[3].x = box[0].x;

		_hoops_GAASH (nr, 5, box, null);
	}
}


GLOBAL_FUNCTION void HD_HL_DC_Polymarker (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	float const *				rotations,
	float const *				size_fixups) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_SGSGP alter *				data = dc->_hoops_SHSHP;
	_hoops_HSRSH alter *			marker;

	while (count-- > 0) {
		POOL_ZALLOC (marker, _hoops_HSRSH, dc->memory_pool);
		marker->_hoops_GGIAR = *points;		/* _hoops_HSPH _hoops_HPP _hoops_AGGPR _hoops_PPSR */

		if (rotations)
			marker->rotation = *rotations++;
		else
			marker->rotation = 0.0f;
		if (size_fixups)
			marker->_hoops_ACIGH = *size_fixups++;
		else
			marker->_hoops_ACIGH = 1.0f;

		marker->_hoops_HSIPH = true;

		marker->next = data->_hoops_IGASH;
		data->_hoops_IGASH = marker;

		marker->_hoops_APHGA = nr;
		marker->_hoops_RAI = nr->_hoops_SRA->_hoops_RAI;
		marker->_hoops_RRCIP = nr->_hoops_SRA->_hoops_RRCIP;
		marker->path = nr->_hoops_SRA->path;

		points++;
	}
}



GLOBAL_FUNCTION void HD_HL_DC_Polydot (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points)
{
	_hoops_HSRSH alter *			marker;
	_hoops_SGSGP alter *				data = nr->_hoops_SRA->_hoops_SHSHP;

	while (count-- > 0) {
		ZALLOC (marker, _hoops_HSRSH);
		marker->type = _hoops_ASRSH;
		marker->_hoops_GGIAR = *points;		/* _hoops_HSPH _hoops_HPP _hoops_AGGPR _hoops_PPSR */

		marker->_hoops_HSIPH = true;

		marker->next = data->_hoops_IGASH;
		data->_hoops_IGASH = marker;

		marker->_hoops_APHGA = nr;
		marker->_hoops_RAI = nr->_hoops_SRA->_hoops_RAI;
		marker->_hoops_RRCIP = nr->_hoops_SRA->_hoops_RRCIP;

		points++;
	}
}

GLOBAL_FUNCTION void HD_HL_DC_Colorized_Polydot (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				_hoops_IASGR,
	bool						single)
{
	_hoops_HSRSH alter *			marker;
	_hoops_SGSGP alter *				data = nr->_hoops_SRA->_hoops_SHSHP;

	while (count-- > 0) {
		ZALLOC (marker, _hoops_HSRSH);
		marker->type = _hoops_PSRSH;
		marker->_hoops_GGIAR = *points;		/* _hoops_HSPH _hoops_HPP _hoops_AGGPR _hoops_PPSR */

		marker->color = *_hoops_IASGR;

		marker->_hoops_HSIPH = true;

		marker->next = data->_hoops_IGASH;
		data->_hoops_IGASH = marker;

		marker->_hoops_APHGA = nr;
		marker->_hoops_RAI = nr->_hoops_SRA->_hoops_RAI;
		marker->_hoops_RRCIP = nr->_hoops_SRA->_hoops_RRCIP;

		points++;
		if (!single)
			_hoops_IASGR++;
	}
}


GLOBAL_FUNCTION void HD_HL_Plain_Text (
	Net_Rendition const &		nr,
	_hoops_HACC const *				_hoops_PCHIH,
	Point const *				point,
	int							count,
	Karacter const *			_hoops_IHSCP,
	_hoops_PGCSR const *	_hoops_HGCSR) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_SGSGP alter *				data = dc->_hoops_SHSHP;
	_hoops_HIHSA alter *	_hoops_CSGCP;
	KName						_hoops_SIHSA;
	_hoops_ISRSH alter *			string;

	POOL_ZALLOC (string, _hoops_ISRSH, dc->memory_pool);

	string->_hoops_GGIAR = *point;	/* _hoops_HSPH _hoops_HPP _hoops_AGGPR _hoops_PPSR */

	string->_hoops_HSIPH = true;

	string->next = data->strings;
	data->strings = string;

	string->_hoops_APHGA = nr;
	string->_hoops_RAI = nr->_hoops_SRA->_hoops_RAI;
	string->_hoops_RRCIP = nr->_hoops_SRA->_hoops_RRCIP;
	string->path = nr->_hoops_SRA->path;

	POOL_ALLOC (_hoops_CSGCP, _hoops_HIHSA, dc->memory_pool);
	string->_hoops_CSRSH = _hoops_CSGCP;

	_hoops_SIHSA.length = count;
	_hoops_SIHSA._hoops_IPPPP = (Karacter alter *)_hoops_IHSCP;
	HI_Copy_KName (&_hoops_SIHSA, &_hoops_CSGCP->_hoops_SIHSA);
	_hoops_CSGCP->_hoops_RACSR = nr->_hoops_SISI->font->_hoops_RACSR;
	_hoops_CSGCP->_hoops_GCHSA = nr->_hoops_SISI->font->_hoops_GCHSA;

	if (_hoops_HGCSR != null) {
		POOL_ALLOC_ARRAY (string->_hoops_HGCSR, count, _hoops_PGCSR, dc->memory_pool);
		_hoops_AIGA (_hoops_HGCSR, count, _hoops_PGCSR, string->_hoops_HGCSR);
	}

	if ((_hoops_CSGCP->text = _hoops_PCHIH) != null)
		_hoops_PRRH (_hoops_PCHIH);
}



/*
 * _hoops_PS _hoops_CGH _hoops_IIP _hoops_HS _hoops_IS _hoops_IPPR _hoops_RH _hoops_HSPR _hoops_CSSC _hoops_IIGR _hoops_SHCA _hoops_CPAP.
 * _hoops_GCACP, _hoops_SR'_hoops_RISP _hoops_HHRSH _hoops_ASCA _hoops_HPGR _hoops_IRS _hoops_PHPA _hoops_PAPA.
 */

local void _hoops_AARHP (
	char const		*which) {

	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
		Sprintf_S (null, "Unexpected 'HL_DC_%s'", which));
}


GLOBAL_FUNCTION void HD_HL_DC_Text (
	Net_Rendition const &		nr,
	DC_Point const *			where,
	int							count,
	Karacter const *			kstring) {
	UNREFERENCED (nr);
	UNREFERENCED (where);
	UNREFERENCED (count);
	UNREFERENCED (kstring);

	_hoops_AARHP ("Text");
}


#define _hoops_PRPSH (1e-5f)
local bool _hoops_HRPSH(
	_hoops_PCRSH const *		first,
	_hoops_PCRSH const *		_hoops_IAGRA,
	DC_Point alter *	_hoops_RSPSA,
	float alter *		_hoops_SPRAA,
	float alter *		st) {
	Vector				_hoops_IRPSH = first->points[1] - first->points[0];
	Vector				_hoops_CRPSH = _hoops_IAGRA->points[1] - _hoops_IAGRA->points[0];
	float				a1, _hoops_IHHI, a2, _hoops_CHHI, _hoops_AIGCR, _hoops_PIGCR;
	float				_hoops_HIHHA, _hoops_PIAIA, _hoops_SRPSH, _hoops_GAPSH;
	float				_hoops_SSHGA;
	float				_hoops_RAPSH, _hoops_AAPSH;

	a1 = _hoops_IRPSH.y;
	_hoops_IHHI = -_hoops_IRPSH.x;
	_hoops_AIGCR = -((a1 * first->points[0].x) + (_hoops_IHHI * first->points[0].y));
	_hoops_SRPSH = (a1 * _hoops_IAGRA->points[0].x) + (_hoops_IHHI * _hoops_IAGRA->points[0].y) + _hoops_AIGCR;
	_hoops_GAPSH = (a1 * _hoops_IAGRA->points[1].x) + (_hoops_IHHI * _hoops_IAGRA->points[1].y) + _hoops_AIGCR;
	/* _hoops_RPP _hoops_GIPR _hoops_RSSA _hoops_IIGR '_hoops_GIAP' _hoops_PRCS _hoops_GPP _hoops_RH _hoops_PSHR _hoops_PPAP _hoops_IIGR '_hoops_SRS', _hoops_RH _hoops_III
	 * _hoops_SGHC _hoops_AA _hoops_HAR _hoops_ARCRA... */
	if ((_hoops_SRPSH > 0) == (_hoops_GAPSH > 0))
		return false;
	a2 = _hoops_CRPSH.y;
	_hoops_CHHI = -_hoops_CRPSH.x;
	_hoops_PIGCR = -((a2 * _hoops_IAGRA->points[0].x) + (_hoops_CHHI * _hoops_IAGRA->points[0].y));
	_hoops_HIHHA = (a2 * first->points[0].x) + (_hoops_CHHI * first->points[0].y) + _hoops_PIGCR;
	_hoops_PIAIA = (a2 * first->points[1].x) + (_hoops_CHHI * first->points[1].y) + _hoops_PIGCR;
	/* ..._hoops_PPR _hoops_GPHP _hoops_RPHP */
	if ((_hoops_HIHHA > 0) == (_hoops_PIAIA > 0))
		return false;
	_hoops_SSHGA = (a1*_hoops_CHHI) - (a2*_hoops_IHHI);
	/* _hoops_RCPP _hoops_RPP _hoops_HAH _hoops_GGGR _hoops_IS _hoops_SPRPA */
	if (-_hoops_PRPSH < _hoops_SSHGA && _hoops_SSHGA < _hoops_PRPSH)
		return false;

	_hoops_RAPSH = _hoops_HIHHA / (_hoops_HIHHA - _hoops_PIAIA);
	_hoops_AAPSH = _hoops_SRPSH / (_hoops_SRPSH - _hoops_GAPSH);

	if ((_hoops_RAPSH < 1e-5f || _hoops_RAPSH > 0.99999f) && (_hoops_AAPSH < 1e-5f || _hoops_AAPSH > 0.99999f))
		return false;

	if (_hoops_SPRAA != null)
		*_hoops_SPRAA = _hoops_RAPSH;
	if (st != null)
		*st = _hoops_AAPSH;

	if (_hoops_RSPSA != null)
		*_hoops_RSPSA = first->points[0] + _hoops_IRPSH * _hoops_RAPSH;

	return true;
}


#define _hoops_CACIR		0.1f
#define _hoops_PAPSH(a,b, _hoops_ISCIA, _hoops_HAPSH)	\
		((a)->x < (b)->x + (_hoops_ISCIA)   &&  (a)->x > (b)->x - (_hoops_ISCIA)	&& \
		 (a)->y < (b)->y + (_hoops_ISCIA)   &&  (a)->y > (b)->y - (_hoops_ISCIA)	&& \
		 (a)->z < (b)->z + (_hoops_HAPSH)  &&  (a)->z > (b)->z - (_hoops_HAPSH))
#define _hoops_IAPSH	4
#define _hoops_CAPSH(_hoops_PRIAA,_hoops_RCHIR, _hoops_ISCIA)		\
		((_hoops_PRIAA) == null && (_hoops_RCHIR) == null ||							  \
		 (_hoops_PRIAA) != null && (_hoops_RCHIR) != null &&							  \
		 (_hoops_PRIAA)->r < (_hoops_RCHIR)->r + (_hoops_ISCIA)	&&	(_hoops_PRIAA)->r > (_hoops_RCHIR)->r - (_hoops_ISCIA)  && \
		 (_hoops_PRIAA)->g < (_hoops_RCHIR)->g + (_hoops_ISCIA)	&&	(_hoops_PRIAA)->g > (_hoops_RCHIR)->g - (_hoops_ISCIA)  && \
		 (_hoops_PRIAA)->b < (_hoops_RCHIR)->b + (_hoops_ISCIA)	&&	(_hoops_PRIAA)->b > (_hoops_RCHIR)->b - (_hoops_ISCIA))


/*
 * _hoops_RACRR _hoops_AGIR: _hoops_IS _hoops_HGCR _hoops_ASSIA _hoops_SPPR _hoops_GAR _hoops_AGAPR _hoops_HPISR _hoops_SCSHR, _hoops_SR _hoops_RRP
 * _hoops_IS _hoops_IGHAR _hoops_HCR _hoops_RH _hoops_RSCA _hoops_SIH _hoops_PPR _hoops_HPPR _hoops_IS _hoops_HSGIR _hoops_CAPR...
 */
static int _hoops_SAPSH = 3;

#define _hoops_GPPSH(_hoops_RPPSH,_hoops_APPSH,_hoops_PPPSH)							\
		(((_hoops_APPSH).x - (_hoops_RPPSH).x) * ((_hoops_PPPSH).y - (_hoops_RPPSH).y) -	\
		 ((_hoops_PPPSH).x - (_hoops_RPPSH).x) * ((_hoops_APPSH).y - (_hoops_RPPSH).y))

GLOBAL_FUNCTION void HD_HL_Expand_Polyline (_hoops_CCRSH alter * polyline);
GLOBAL_FUNCTION void HD_HL_Collapse_Polyline (_hoops_CCRSH alter * polyline);


local void _hoops_GGSCP (
	_hoops_CCRSH *				current) {

	HD_HL_Expand_Polyline (current);

	_hoops_PCRSH *					line;

	if ((line = current->_hoops_PICHR) != null) do {
		_hoops_PCRSH *				test = line->next;
		int							_hoops_HPPSH = 0;
		float						s, t;
		DC_Point					_hoops_IPPSH;

		if (test != null) _hoops_PCCAR {
			if (_hoops_HPPSH++ >= _hoops_SAPSH)
				break;
			if ((test = test->next) == null)
				break;

			/* _hoops_PAHA'_hoops_RA _hoops_RGR _hoops_HS _hoops_HHH _hoops_GHIS _hoops_IIGR _hoops_AAHP? */
			if (_hoops_HRPSH (line, test, &_hoops_IPPSH, &s, &t) &&
				line->start < s && s < line->end &&
				test->start < t && t < test->end) {
				bool				_hoops_CPPSH = true;

				/* _hoops_CACH _hoops_RPP _hoops_HCR _hoops_RSSA _hoops_IGIAR _hoops_RH _hoops_ICSHR _hoops_CHR _hoops_GIAA _hoops_IRS _hoops_SPPSH _hoops_ISPH */
				if (_hoops_HPPSH > 1) {
					_hoops_PCRSH const *	_hoops_IHPCR = line->next->next;
					float				_hoops_GHPSH;

					_hoops_GHPSH = _hoops_GPPSH (_hoops_IPPSH, line->points[1], test->points[0]);

					do if (_hoops_GHPSH * _hoops_GPPSH (_hoops_IPPSH, line->points[1], _hoops_IHPCR->points[0]) < 0.0f ||
						   _hoops_GHPSH * _hoops_GPPSH (line->points[1], test->points[0], _hoops_IHPCR->points[0]) < 0.0f ||
						   _hoops_GHPSH * _hoops_GPPSH (test->points[0], _hoops_IPPSH, _hoops_IHPCR->points[0]) < 0.0f) {
						_hoops_CPPSH = false;
						break;
					} while ((_hoops_IHPCR = _hoops_IHPCR->next) != test);
				}

				if (_hoops_CPPSH) {
					/* _hoops_HPGGR _hoops_RHPSH _hoops_IIGR _hoops_AGCR _hoops_APGR _hoops_GAR _hoops_PSIPR */
					line->end = s;
					test->start = t;

					/* _hoops_PPR _hoops_APRI _hoops_AGAP _hoops_GAPA */
					do {
						_hoops_PCRSH *	victim = line->next;

						line->next = victim->next;

						if (victim->colors != null)
							FREE_ARRAY (victim->colors, 2, RGBAS32);
						FREE (victim, _hoops_PCRSH);
					} while (line->next != test);

					/* _hoops_SIAPR _hoops_HHCPR */
					line = current->_hoops_PICHR;
					test = line->next;
					_hoops_HPPSH = 0;
				}
			}
		}
	} while ((line = line->next) != null);

	HD_HL_Collapse_Polyline (current);
}

local void _hoops_AHPSH (
	Net_Rendition const & 		nr,
	_hoops_CCRSH *				list,
	bool						_hoops_IRASH) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_SGSGP alter *				data = dc->_hoops_SHSHP;
	_hoops_CCRSH *				current = list;
	_hoops_CCRSH *				tmp;
	_hoops_CCRSH **				_hoops_ASRGR;
	float						_hoops_HAPSH;

	_hoops_HAPSH = _hoops_CACIR * nr->transform_rendition->_hoops_PCHH / nr->_hoops_SRA->_hoops_PGCC.size.x;

	/* _hoops_SRS _hoops_ACRAA _hoops_GII _hoops_APRAR _hoops_RGHS _hoops_SR _hoops_GHCA _hoops_AIAH _hoops_HS */
	_hoops_ASRGR = &current;
	while ((tmp = *_hoops_ASRGR) != null) {
		if (tmp->count > 0) {
			if (_hoops_PAPSH (&tmp->points[0], &tmp->points[tmp->count-1], _hoops_CACIR, _hoops_HAPSH)) {
				*_hoops_ASRGR = tmp->next;
				tmp->next = data->_hoops_GPHGA;
				data->_hoops_GPHGA = tmp;
			}
			else
				_hoops_ASRGR = &tmp->next;
		}
		else
			_hoops_ASRGR = &tmp->next;
	}

	/* _hoops_HPPR _hoops_IS _hoops_HASC _hoops_RH _hoops_SCSHR _hoops_SR _hoops_HS */
	while (current != null) {
		if (current->count > 0) {
			_hoops_ASRGR = &current->next;
			while ((tmp = *_hoops_ASRGR) != null) {
				if (current->_hoops_APHGA->_hoops_AHP == tmp->_hoops_APHGA->_hoops_AHP &&
					tmp->count > 0) {
					DC_Point		* _hoops_PHPSH, * _hoops_GSPPR;
					DC_Point		* _hoops_HHPSH, * _hoops_IHPSH;
					RGBAS32			* _hoops_CHPSH = null, * _hoops_SHPSH = null;
					RGBAS32			* _hoops_GIPSH = null, * _hoops_RIPSH = null;

					_hoops_PHPSH = &current->points[0];
					_hoops_GSPPR = &current->points[current->count-1];
					if (current->colors != null) {
						_hoops_CHPSH = &current->colors[0];
						_hoops_SHPSH = &current->colors[current->count-1];
					}

					_hoops_HHPSH = &tmp->points[0];
					_hoops_IHPSH = &tmp->points[tmp->count-1];
					if (tmp->colors != null) {
						_hoops_GIPSH = &tmp->colors[0];
						_hoops_RIPSH = &tmp->colors[tmp->count-1];
					}

					if (_hoops_PAPSH (_hoops_GSPPR, _hoops_HHPSH, _hoops_CACIR, _hoops_HAPSH) && _hoops_CAPSH (_hoops_SHPSH, _hoops_GIPSH, _hoops_IAPSH)) {
						/* _hoops_CIGAA _hoops_AIPSH _hoops_CIAA _hoops_SCGR */
						DC_Point *		points;
						RGBAS32 *		colors;

						POOL_ALLOC_ARRAY (points, current->count + tmp->count, DC_Point, dc->memory_pool);
						_hoops_AIGA (current->points, current->count, DC_Point, points);
						_hoops_AIGA (tmp->points, tmp->count, DC_Point, points + current->count);
						FREE_ARRAY (current->points, current->count, DC_Point);
						current->points = points;

						if (current->colors != null) {
							POOL_ALLOC_ARRAY (colors, current->count + tmp->count, RGBAS32, dc->memory_pool);
							_hoops_AIGA (current->colors, current->count, RGBAS32, colors);
							_hoops_AIGA (tmp->colors, tmp->count, RGBAS32, colors + current->count);
							FREE_ARRAY (current->colors, current->count, RGBAS32);
							current->colors = colors;
						}

						current->count += tmp->count;


						*_hoops_ASRGR = tmp->next;

						tmp->_hoops_APHGA.release();
						tmp->path.release();
						FREE_ARRAY (tmp->points, tmp->count, DC_Point);
						if (tmp->colors != null)
							FREE_ARRAY (tmp->colors, tmp->count, RGBAS32);
						FREE (tmp, _hoops_CCRSH);

						_hoops_ASRGR = &current->next;
					}
					else if (_hoops_PAPSH (_hoops_IHPSH, _hoops_PHPSH, _hoops_CACIR, _hoops_HAPSH) && _hoops_CAPSH (_hoops_RIPSH, _hoops_CHPSH, _hoops_IAPSH)) {
						/* _hoops_PIPSH _hoops_AIPSH _hoops_CIAA _hoops_SCGR */
						DC_Point *		points;
						RGBAS32 *		colors;

						POOL_ALLOC_ARRAY (points, current->count + tmp->count, DC_Point, dc->memory_pool);
						_hoops_AIGA (tmp->points, tmp->count, DC_Point, points);
						_hoops_AIGA (current->points, current->count, DC_Point, points + tmp->count);
						FREE_ARRAY (current->points, current->count, DC_Point);
						current->points = points;

						if (current->colors != null) {
							POOL_ALLOC_ARRAY (colors, current->count + tmp->count, RGBAS32, dc->memory_pool);
							_hoops_AIGA (tmp->colors, tmp->count, RGBAS32, colors);
							_hoops_AIGA (current->colors, current->count, RGBAS32, colors + tmp->count);
							FREE_ARRAY (current->colors, current->count, RGBAS32);
							current->colors = colors;
						}

						current->count += tmp->count;


						*_hoops_ASRGR = tmp->next;

						tmp->_hoops_APHGA.release();
						tmp->path.release();
						FREE_ARRAY (tmp->points, tmp->count, DC_Point);
						if (tmp->colors != null)
							FREE_ARRAY (tmp->colors, tmp->count, RGBAS32);
						FREE (tmp, _hoops_CCRSH);

						_hoops_ASRGR = &current->next;
					}
					else if (_hoops_PAPSH (_hoops_GSPPR, _hoops_IHPSH, _hoops_CACIR, _hoops_HAPSH) && _hoops_CAPSH (_hoops_SHPSH, _hoops_RIPSH, _hoops_IAPSH)) {
						/* _hoops_CIGAA _hoops_AAGIR _hoops_AIPSH _hoops_CIAA _hoops_SCGR */
						DC_Point *		points;
						RGBAS32 *		colors;

						POOL_ALLOC_ARRAY (points, current->count + tmp->count, DC_Point, dc->memory_pool);
						_hoops_AIGA (current->points, current->count, DC_Point, points);
						for (int i=0; i < tmp->count; ++i)
							points[current->count + i] = tmp->points[tmp->count-1 - i];
						FREE_ARRAY (current->points, current->count, DC_Point);
						current->points = points;

						if (current->colors != null) {
							POOL_ALLOC_ARRAY (colors, current->count + tmp->count, RGBAS32, dc->memory_pool);
							_hoops_AIGA (current->colors, current->count, RGBAS32, colors);
							for (int i=0; i < tmp->count; ++i)
								colors[current->count + i] = tmp->colors[tmp->count-1 - i];
							FREE_ARRAY (current->colors, current->count, RGBAS32);
							current->colors = colors;
						}

						current->count += tmp->count;


						*_hoops_ASRGR = tmp->next;

						tmp->_hoops_APHGA.release();
						tmp->path.release();
						FREE_ARRAY (tmp->points, tmp->count, DC_Point);
						if (tmp->colors != null)
							FREE_ARRAY (tmp->colors, tmp->count, RGBAS32);
						FREE (tmp, _hoops_CCRSH);

						_hoops_ASRGR = &current->next;
					}
					else if (_hoops_PAPSH (_hoops_PHPSH, _hoops_HHPSH, _hoops_CACIR, _hoops_HAPSH) && _hoops_CAPSH (_hoops_CHPSH, _hoops_GIPSH, _hoops_IAPSH)) {
						/* _hoops_PIPSH _hoops_AAGIR _hoops_AIPSH _hoops_CIAA _hoops_SCGR */
						DC_Point *		points;
						RGBAS32 *		colors;

						POOL_ALLOC_ARRAY (points, current->count + tmp->count, DC_Point, dc->memory_pool);
						for (int i=0; i < tmp->count; ++i)
							points[i] = tmp->points[tmp->count-1 - i];
						_hoops_AIGA (current->points, current->count, DC_Point, points + tmp->count);
						FREE_ARRAY (current->points, current->count, DC_Point);
						current->points = points;

						if (current->colors != null) {
							POOL_ALLOC_ARRAY (colors, current->count + tmp->count, RGBAS32, dc->memory_pool);
							for (int i=0; i < tmp->count; ++i)
								colors[i] = tmp->colors[tmp->count-1 - i];
							_hoops_AIGA (current->colors, current->count, RGBAS32, colors + tmp->count);
							FREE_ARRAY (current->colors, current->count, RGBAS32);
							current->colors = colors;
						}

						current->count += tmp->count;


						*_hoops_ASRGR = tmp->next;

						tmp->_hoops_APHGA.release();
						tmp->path.release();
						FREE_ARRAY (tmp->points, tmp->count, DC_Point);
						if (tmp->colors != null)
							FREE_ARRAY (tmp->colors, tmp->count, RGBAS32);
						FREE (tmp, _hoops_CCRSH);

						_hoops_ASRGR = &current->next;
					}
					else
						_hoops_ASRGR = &tmp->next;
				}
				else
					_hoops_ASRGR = &tmp->next;
			}

			if (_hoops_IRASH)
				_hoops_GGSCP (current);
		}

		if (Abs (current->count) > data->_hoops_ARASH)
			data->_hoops_ARASH = Abs (current->count);

		tmp = current;
		current = tmp->next;

		tmp->next = data->_hoops_GPHGA;
		data->_hoops_GPHGA = tmp;
	}
}

local void _hoops_HIPSH (
	Net_Rendition const & 		nr,
	Polyedge const *			pe) {
	_hoops_SGSGP alter *				data = nr->_hoops_SRA->_hoops_SHSHP;
	_hoops_CCRSH *				tmp;
	_hoops_CCRSH *				current;

	tmp = data->_hoops_GPHGA;
	data->_hoops_GPHGA = null;
	data->_hoops_IRASH = true;

	HD_Draw_Silhouette_Edges (nr, pe);

	data->_hoops_IRASH = false;
	if ((current = data->_hoops_GPHGA) != null) {
		if (data->_hoops_CGASH != null) {
			while (current->next != null)
				current = current->next;
			current->next = data->_hoops_CGASH;
		}
		data->_hoops_CGASH = data->_hoops_GPHGA;
	}
	data->_hoops_GPHGA = tmp;
}

#endif


GLOBAL_FUNCTION void HD_HL_3D_Polyhedron (
	Net_Rendition const & 		nr,
	Polyhedron const *			_hoops_IPRI) {
#ifndef _hoops_IRRHP
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_SGSGP alter *				data = dc->_hoops_SHSHP;
	_hoops_GACGA		_hoops_IIPSH = dc->_hoops_IPCI->draw_silhouette_polyedge;
	_hoops_ACHR					_hoops_CIPSH;
	_hoops_CCRSH *				current;
	_hoops_CCRSH *				tmp;

	_hoops_CIPSH = nr->_hoops_RGP &
		((_hoops_IPRI->type == _hoops_GSIP) ? T_ANY_MESH_EDGE : T_ANY_SHELL_EDGE);

	/* _hoops_HRGR _hoops_IIH _hoops_GII _hoops_CGGC _hoops_IIGR _hoops_GHGA _hoops_SAHP? */
	if (!ANYBIT (_hoops_CIPSH, T_INTERIOR_SILHOUETTE_EDGES |
										T_PERIMETER_EDGES) ||
		 BIT (_hoops_CIPSH, T_GENERIC_EDGES)) {
		/* _hoops_SSCHR... */
		HD_Std_3D_Polyhedron (nr, _hoops_IPRI);
		return;
	}

	/* _hoops_GII _hoops_CGGC _hoops_IIGR _hoops_CAPR _hoops_IHGS _hoops_CHCC _hoops_IIPH _hoops_PAR _hoops_RRP _hoops_PHARA? */
	if (BIT(nr->_hoops_RHP->line_style->flags, LSF_SOLID) &&
		_hoops_IPRI->_hoops_IHHPR._hoops_SRAPA == 0 &&
		(!BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI) ||
		 BIT(nr->_hoops_ASIR->_hoops_GCCI.line_style->flags, LSF_SOLID)) &&
		!BIT (nr->_hoops_ASIR->_hoops_GCCI.options,
			  _hoops_CPCRP)) {
		/* _hoops_SSCHR... */
		HD_Std_3D_Polyhedron (nr, _hoops_IPRI);
		return;
	}

	dc->_hoops_IPCI->draw_silhouette_polyedge = _hoops_HIPSH;
	tmp = data->_hoops_GPHGA;
	data->_hoops_GPHGA = null;
	HD_Std_3D_Polyhedron (nr, _hoops_IPRI);
	current = data->_hoops_GPHGA;
	data->_hoops_GPHGA = tmp;
	dc->_hoops_IPCI->draw_silhouette_polyedge = _hoops_IIPSH;

	_hoops_AHPSH (nr, current, false);
	if (data->_hoops_CGASH != null) {
		_hoops_AHPSH (nr, data->_hoops_CGASH,
					   BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_CPCRP));
		data->_hoops_CGASH = null;
	}
#endif
}


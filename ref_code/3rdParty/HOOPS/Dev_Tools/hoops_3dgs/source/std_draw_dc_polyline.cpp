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
 * $Id: obf_tmp.txt 1.213 2011-01-11 22:28:46 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "patterns.h"
#include "tandt.h"
#include "select.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



#define _hoops_SHCCS					1
#define _hoops_GICCS				2
#define _hoops_RICCS					3
#define _hoops_AICCS					4




struct _hoops_PICCS {
	int 				count;
	int 				_hoops_SAGCA;
	DC_Point *			points;
	DC_Point *			_hoops_ASPS;
	float *				_hoops_RRSR;
};

struct _hoops_HICCS {
	Net_Rendition			nr;
	Net_Rendition			_hoops_IICCS;
	_hoops_PICCS *	_hoops_CICCS;
	_hoops_PICCS *	_hoops_SICCS;
	_hoops_PICCS *	_hoops_GCCCS;
};

struct _hoops_RCCCS {
	_hoops_RCCCS *next, *_hoops_SSAC;

	_hoops_GASC					glyph;
	int						mode;
	float					size;
	float					_hoops_AHHRI;
	float					_hoops_ACCCS;
	int						width;
	float					rotation;
	_hoops_HCAIR			weight;
	Line_Style_Flags		flags;

	_hoops_HICCS *			_hoops_CSC;
	_hoops_PICCS *	glyph_lsic;
};

#define _hoops_PCCCS 32

local INLINE _hoops_PICCS * _hoops_HCCCS(
	Net_Rendition const &nr, 
	bool glyph,
	int _hoops_ICCCS)
{
	_hoops_PICCS * _hoops_CICCS;

	POOL_ZALLOC(_hoops_CICCS, _hoops_PICCS, nr->_hoops_SRA->memory_pool);
	_hoops_CICCS->_hoops_SAGCA = _hoops_ICCCS;
	POOL_ALLOC_ARRAY_CACHED(_hoops_CICCS->points, _hoops_ICCCS, DC_Point, nr->_hoops_SRA->memory_pool);
	if (glyph)
		POOL_ALLOC_ARRAY_CACHED(_hoops_CICCS->_hoops_RRSR, _hoops_ICCCS, float, nr->_hoops_SRA->memory_pool);
	_hoops_CICCS->count = 0;
	_hoops_CICCS->_hoops_ASPS = _hoops_CICCS->points;

	return _hoops_CICCS;
}

local INLINE void _hoops_CCCCS(
	Net_Rendition const &nr, 
	_hoops_RCCCS * _hoops_SCCCS, 
	float weight, 								 
	bool _hoops_GSCCS)
{
	ASSERT(_hoops_SCCCS != null);
	ASSERT(_hoops_SCCCS->_hoops_CSC != null);

	if (!_hoops_SCCCS->_hoops_CSC->_hoops_CICCS) 
		_hoops_SCCCS->_hoops_CSC->_hoops_CICCS = _hoops_HCCCS(nr, false, _hoops_PCCCS);

	if (weight > 1) {

		_hoops_SCCCS->mode = _hoops_GICCS;

		if (!_hoops_SCCCS->_hoops_CSC->_hoops_SICCS)
			_hoops_SCCCS->_hoops_CSC->_hoops_SICCS = _hoops_HCCCS(nr, false, _hoops_PCCCS);

		if (_hoops_GSCCS) {

			if (!_hoops_SCCCS->_hoops_CSC->_hoops_GCCCS)
				_hoops_SCCCS->_hoops_CSC->_hoops_GCCCS = _hoops_HCCCS(nr, false, _hoops_PCCCS);
		}
	}
	else
		_hoops_SCCCS->mode = _hoops_SHCCS;
}

local INLINE void _hoops_RSCCS(
	Net_Rendition const &nr, 
	_hoops_RCCCS * _hoops_SCCCS, 
	_hoops_GASC const & glyph, 
	float rotation, 
	float size, 
	Line_Style_Flags flags,
	_hoops_HCAIR const & weight,
	int _hoops_ICCCS)
{
	ASSERT(_hoops_SCCCS != null);

	if (!_hoops_SCCCS->glyph_lsic) 
		_hoops_SCCCS->glyph_lsic = _hoops_HCCCS(nr, true, _hoops_ICCCS);

	_hoops_SCCCS->mode = _hoops_AICCS;
	_hoops_SCCCS->glyph = glyph;
	_hoops_SCCCS->flags = flags;
	_hoops_SCCCS->rotation = rotation;
	_hoops_SCCCS->size = size;
	_hoops_SCCCS->weight = weight;
}

local INLINE void _hoops_ASCCS(
	Net_Rendition const &nr, 
	Line_Style_Item const * _hoops_HSIPI, 
	_hoops_GASC & glyph, 
	float & rotation, 
	Line_Style_Flags & flags, 
	float & size)
{

	glyph = HD_Find_Glyph(nr->glyph_rendition, 0, &_hoops_HSIPI->name, _hoops_HSIPI->key, true);
	rotation = _hoops_HSIPI->rotation;
	flags = _hoops_HSIPI->flags;

	if (!glyph) 
		glyph = nr->_hoops_GSP->glyph;

	if (_hoops_HSIPI->size._hoops_HHP != _hoops_SHGRP)
		size = 0.5f * HD_Compute_Generic_Size (nr, _hoops_HSIPI->size.value, _hoops_HSIPI->size._hoops_HHP, nr->_hoops_GSP->ysize, false, 0, true);
	else
		size = nr->_hoops_GSP->ysize;

}

local INLINE void _hoops_PSCCS(Net_Rendition const &nr, _hoops_PICCS * _hoops_CICCS, int _hoops_ICCCS, int _hoops_HSCCS)
{
	DC_Point *_hoops_IACCS;
	float *_hoops_ISCCS = null;

	int _hoops_CGCGR = _hoops_CICCS->_hoops_SAGCA * 2 + (_hoops_ICCCS*_hoops_HSCCS);

	POOL_ALLOC_ARRAY_CACHED(_hoops_IACCS, _hoops_CGCGR, DC_Point, nr->_hoops_SRA->memory_pool);
	if (_hoops_CICCS->count) 
		_hoops_AIGA(_hoops_CICCS->points, _hoops_CICCS->count*_hoops_HSCCS, DC_Point, _hoops_IACCS);
	FREE_ARRAY(_hoops_CICCS->points, _hoops_CICCS->_hoops_SAGCA, DC_Point);

	if (_hoops_CICCS->_hoops_RRSR != null) {
		POOL_ALLOC_ARRAY_CACHED(_hoops_ISCCS, _hoops_CGCGR, float, nr->_hoops_SRA->memory_pool);
		if (_hoops_CICCS->count) 
			_hoops_AIGA(_hoops_CICCS->_hoops_RRSR, _hoops_CICCS->count*_hoops_HSCCS, float, _hoops_ISCCS); 
		FREE_ARRAY(_hoops_CICCS->_hoops_RRSR, _hoops_CICCS->_hoops_SAGCA, float);
	}

	_hoops_CICCS->_hoops_SAGCA = _hoops_CGCGR;
	_hoops_CICCS->points = _hoops_IACCS;
	_hoops_CICCS->_hoops_RRSR = _hoops_ISCCS;
	_hoops_CICCS->_hoops_ASPS = &_hoops_CICCS->points[_hoops_CICCS->count*_hoops_HSCCS];
}

local INLINE void _hoops_CSCCS(_hoops_PICCS * _hoops_CICCS)
{
	if (_hoops_CICCS->points)
		FREE_ARRAY(_hoops_CICCS->points, _hoops_CICCS->_hoops_SAGCA, DC_Point);
	if (_hoops_CICCS->_hoops_RRSR)
		FREE_ARRAY(_hoops_CICCS->_hoops_RRSR, _hoops_CICCS->_hoops_SAGCA, float);
	FREE(_hoops_CICCS, _hoops_PICCS);
}

local INLINE void _hoops_SSCCS(Net_Rendition const &nr, _hoops_PICCS * _hoops_CICCS, DC_Point * _hoops_GSGGA)
{
	if ((_hoops_CICCS->count+1)*2 >= _hoops_CICCS->_hoops_SAGCA) 
		_hoops_PSCCS(nr ,_hoops_CICCS, 1, 2);
	_hoops_AIGA(_hoops_GSGGA, 2, DC_Point, _hoops_CICCS->_hoops_ASPS);
	_hoops_CICCS->_hoops_ASPS+=2;
	_hoops_CICCS->count++;
}

local INLINE void _hoops_GGSCS(Net_Rendition const &nr, _hoops_PICCS * _hoops_CICCS, DC_Point * _hoops_GSGGA, Vector const & path, float radius)
{
	if ((_hoops_CICCS->count+1)*2 >= _hoops_CICCS->_hoops_SAGCA) 
		_hoops_PSCCS(nr ,_hoops_CICCS, 1, 2);
	_hoops_CICCS->_hoops_ASPS[0].x = _hoops_GSGGA[0].x + path.y * radius;
	_hoops_CICCS->_hoops_ASPS[0].y = _hoops_GSGGA[0].y - path.x * radius;
	_hoops_CICCS->_hoops_ASPS[0].z = _hoops_GSGGA[0].z;
	_hoops_CICCS->_hoops_ASPS[1].x = _hoops_GSGGA[0].x - path.y * radius;
	_hoops_CICCS->_hoops_ASPS[1].y = _hoops_GSGGA[0].y + path.x * radius;
	_hoops_CICCS->_hoops_ASPS[1].z = _hoops_GSGGA[0].z;
	_hoops_CICCS->_hoops_ASPS+=2;
	_hoops_CICCS->count++;
}

local INLINE void _hoops_RGSCS(Net_Rendition const &nr, _hoops_PICCS * _hoops_CICCS, DC_Point * _hoops_GSGGA, Vector const & path, float radius)
{
	if ((_hoops_CICCS->count+4)*3 >= _hoops_CICCS->_hoops_SAGCA) 
		_hoops_PSCCS(nr ,_hoops_CICCS, 4, 3);
	_hoops_CICCS->_hoops_ASPS[0].x = _hoops_CICCS->_hoops_ASPS[6].x = _hoops_CICCS->_hoops_ASPS[9].x = _hoops_GSGGA[0].x;
	_hoops_CICCS->_hoops_ASPS[0].y = _hoops_CICCS->_hoops_ASPS[6].y = _hoops_CICCS->_hoops_ASPS[9].y = _hoops_GSGGA[0].y;
	_hoops_CICCS->_hoops_ASPS[0].z = _hoops_CICCS->_hoops_ASPS[6].z = _hoops_CICCS->_hoops_ASPS[9].z = _hoops_GSGGA[0].z;
	_hoops_CICCS->_hoops_ASPS[1].x = _hoops_CICCS->_hoops_ASPS[3].x = _hoops_GSGGA[0].x - path.y * radius;
	_hoops_CICCS->_hoops_ASPS[1].y = _hoops_CICCS->_hoops_ASPS[3].y = _hoops_GSGGA[0].y + path.x * radius;
	_hoops_CICCS->_hoops_ASPS[1].z = _hoops_CICCS->_hoops_ASPS[3].z = _hoops_GSGGA[0].z;
	_hoops_CICCS->_hoops_ASPS[2].x = _hoops_CICCS->_hoops_ASPS[5].x = _hoops_CICCS->_hoops_ASPS[7].x = _hoops_GSGGA[1].x;
	_hoops_CICCS->_hoops_ASPS[2].y = _hoops_CICCS->_hoops_ASPS[5].y = _hoops_CICCS->_hoops_ASPS[7].y = _hoops_GSGGA[1].y;
	_hoops_CICCS->_hoops_ASPS[2].z = _hoops_CICCS->_hoops_ASPS[5].z = _hoops_CICCS->_hoops_ASPS[7].z = _hoops_GSGGA[1].z;
	_hoops_CICCS->_hoops_ASPS[4].x = _hoops_GSGGA[1].x - path.y * radius;
	_hoops_CICCS->_hoops_ASPS[4].y = _hoops_GSGGA[1].y + path.x * radius;
	_hoops_CICCS->_hoops_ASPS[4].z = _hoops_GSGGA[1].z;
	_hoops_CICCS->_hoops_ASPS[8].x = _hoops_CICCS->_hoops_ASPS[10].x = _hoops_GSGGA[1].x + path.y * radius;
	_hoops_CICCS->_hoops_ASPS[8].y = _hoops_CICCS->_hoops_ASPS[10].y = _hoops_GSGGA[1].y - path.x * radius;
	_hoops_CICCS->_hoops_ASPS[8].z = _hoops_CICCS->_hoops_ASPS[10].z = _hoops_GSGGA[1].z;
	_hoops_CICCS->_hoops_ASPS[11].x= _hoops_GSGGA[0].x + path.y * radius;
	_hoops_CICCS->_hoops_ASPS[11].y= _hoops_GSGGA[0].y - path.x * radius;
	_hoops_CICCS->_hoops_ASPS[11].z= _hoops_GSGGA[0].z;
	_hoops_CICCS->count+=4;
	_hoops_CICCS->_hoops_ASPS+=12;
}

local INLINE void _hoops_AGSCS(Net_Rendition const &nr, _hoops_PICCS * _hoops_CICCS, DC_Point & pts, Vector const & _hoops_CGSSA, Vector const & _hoops_SGSSA, float _hoops_RAHCR, float radius)
{
	float	arc = 0.0f, _hoops_SIIS, _hoops_ARCAR, delta;
	bool	_hoops_SAACP = true;
	float	px, py;

	int		_hoops_HGSSR = (int)(Abs(radius) * 0.5f);
	if (_hoops_HGSSR < 4) 
		_hoops_HGSSR = 4;

	if (_hoops_HGSSR > 400) 
		_hoops_HGSSR = 400;

	delta = 180.0f / (float)_hoops_HGSSR;
	_hoops_HGSSR = (int)(Abs(_hoops_RAHCR) / delta) + 1;
	delta = Abs(_hoops_RAHCR) / (float)_hoops_HGSSR;

	while ((_hoops_CICCS->count+_hoops_HGSSR)*3 >= _hoops_CICCS->_hoops_SAGCA) 
		_hoops_PSCCS(nr ,_hoops_CICCS, _hoops_HGSSR, 3);

	if (_hoops_RAHCR < 0.0f) {
		px = -_hoops_CGSSA.y;  
		py = _hoops_CGSSA.x;
	} else {
		px = _hoops_CGSSA.y;  
		py = -_hoops_CGSSA.x;
	}

	while (1) {
		_hoops_CICCS->_hoops_ASPS[0].x = pts.x;
		_hoops_CICCS->_hoops_ASPS[0].y = pts.y;
		_hoops_CICCS->_hoops_ASPS[0].z = pts.z;
		if (_hoops_SAACP) {
			_hoops_CICCS->_hoops_ASPS[1].x = pts.x + px * radius;
			_hoops_CICCS->_hoops_ASPS[1].y = pts.y + py * radius;
			_hoops_CICCS->_hoops_ASPS[1].z = pts.z;
		} else {
			_hoops_CICCS->_hoops_ASPS[1].x = _hoops_CICCS->_hoops_ASPS[-1].x;
			_hoops_CICCS->_hoops_ASPS[1].y = _hoops_CICCS->_hoops_ASPS[-1].y;
			_hoops_CICCS->_hoops_ASPS[1].z = _hoops_CICCS->_hoops_ASPS[-1].z;
		}
		arc += delta;
		_hoops_RICH (arc, _hoops_SIIS, _hoops_ARCAR);/* _hoops_RCSA _hoops_HII _hoops_PPAP */
		if (_hoops_HGSSR > 1) {
			_hoops_CICCS->_hoops_ASPS[2].x = pts.x + px * _hoops_ARCAR*radius + _hoops_CGSSA.x *_hoops_SIIS*radius;
			_hoops_CICCS->_hoops_ASPS[2].y = pts.y + py * _hoops_ARCAR*radius + _hoops_CGSSA.y *_hoops_SIIS*radius;
			_hoops_CICCS->_hoops_ASPS[2].z = pts.z;
		} else {
			if (_hoops_RAHCR < 0.0f) {
				px = -_hoops_SGSSA.y;  py = _hoops_SGSSA.x;
			} else {
				px = _hoops_SGSSA.y;  py = -_hoops_SGSSA.x;
			}
			_hoops_CICCS->_hoops_ASPS[2].x = pts.x + px * radius;
			_hoops_CICCS->_hoops_ASPS[2].y = pts.y + py * radius;
			_hoops_CICCS->_hoops_ASPS[2].z = pts.z;
		}
		_hoops_CICCS->_hoops_ASPS += 3;
		_hoops_CICCS->count++;
		if (--_hoops_HGSSR <= 0) 
			break;
		_hoops_SAACP = false;
	}
}


local INLINE void _hoops_PGSCS(Net_Rendition const &nr, _hoops_PICCS * _hoops_CICCS, DC_Point & pts, Vector const & path, float radius)
{
	float	arc = 0.0f, _hoops_SIIS, _hoops_ARCAR, delta;
	bool	_hoops_SAACP = true;

	int		_hoops_HGSSR = (int)(Abs(radius) * 0.5f);
	if (_hoops_HGSSR < 4) 
		_hoops_HGSSR = 4;

	if (_hoops_HGSSR > 400) 
		_hoops_HGSSR = 400;

	delta = 180.0f / (float)_hoops_HGSSR;

	while ((_hoops_CICCS->count+_hoops_HGSSR)*3 >= _hoops_CICCS->_hoops_SAGCA) 
		_hoops_PSCCS(nr, _hoops_CICCS, _hoops_HGSSR, 3);

	while (1) {
		_hoops_CICCS->_hoops_ASPS[0].x = pts.x;
		_hoops_CICCS->_hoops_ASPS[0].y = pts.y;
		_hoops_CICCS->_hoops_ASPS[0].z = pts.z;
		if (_hoops_SAACP) {
			_hoops_CICCS->_hoops_ASPS[1].x = pts.x - (path).y * radius;
			_hoops_CICCS->_hoops_ASPS[1].y = pts.y + (path).x * radius;
			_hoops_CICCS->_hoops_ASPS[1].z = pts.z;
		} else {
			_hoops_CICCS->_hoops_ASPS[1].x = _hoops_CICCS->_hoops_ASPS[-1].x;
			_hoops_CICCS->_hoops_ASPS[1].y = _hoops_CICCS->_hoops_ASPS[-1].y;
			_hoops_CICCS->_hoops_ASPS[1].z = _hoops_CICCS->_hoops_ASPS[-1].z;
		}
		arc += delta;
		_hoops_RICH (arc, _hoops_SIIS, _hoops_ARCAR);/* _hoops_RCSA _hoops_HII _hoops_PPAP */
		_hoops_CICCS->_hoops_ASPS[2].x = pts.x - path.y * _hoops_ARCAR*radius - path.x *_hoops_SIIS*radius;
		_hoops_CICCS->_hoops_ASPS[2].y = pts.y + path.x * _hoops_ARCAR*radius - path.y *_hoops_SIIS*radius;
		_hoops_CICCS->_hoops_ASPS[2].z = pts.z;
		_hoops_CICCS->_hoops_ASPS += 3;
		_hoops_CICCS->count++;
		if (--_hoops_HGSSR <= 0) 
			break;
		_hoops_SAACP=false;
	}
}

local INLINE void _hoops_HGSCS(Net_Rendition const &nr, _hoops_PICCS * _hoops_CICCS, DC_Point & pts, Vector const & path, float radius)
{
	if ((_hoops_CICCS->count+3)*3 >= _hoops_CICCS->_hoops_SAGCA) 
		_hoops_PSCCS(nr ,_hoops_CICCS, 3, 3);
	_hoops_CICCS->_hoops_ASPS[0].x = _hoops_CICCS->_hoops_ASPS[3].x = _hoops_CICCS->_hoops_ASPS[6].x = pts.x;
	_hoops_CICCS->_hoops_ASPS[0].y = _hoops_CICCS->_hoops_ASPS[3].y = _hoops_CICCS->_hoops_ASPS[6].y = pts.y;
	_hoops_CICCS->_hoops_ASPS[0].z = _hoops_CICCS->_hoops_ASPS[3].z = _hoops_CICCS->_hoops_ASPS[6].z = pts.z;
	_hoops_CICCS->_hoops_ASPS[1].x = pts.x - path.y * radius;
	_hoops_CICCS->_hoops_ASPS[1].y = pts.y + path.x * radius;
	_hoops_CICCS->_hoops_ASPS[1].z = pts.z;
	_hoops_CICCS->_hoops_ASPS[2].x = _hoops_CICCS->_hoops_ASPS[8].x = pts.x - path.x * radius - path.y * radius;
	_hoops_CICCS->_hoops_ASPS[2].y = _hoops_CICCS->_hoops_ASPS[8].y = pts.y - path.y * radius + path.x * radius;
	_hoops_CICCS->_hoops_ASPS[2].z = _hoops_CICCS->_hoops_ASPS[8].z = pts.z - path.z * radius;
	_hoops_CICCS->_hoops_ASPS[4].x = pts.x + path.y * radius;
	_hoops_CICCS->_hoops_ASPS[4].y = pts.y - path.x * radius;
	_hoops_CICCS->_hoops_ASPS[4].z = pts.z;
	_hoops_CICCS->_hoops_ASPS[5].x = _hoops_CICCS->_hoops_ASPS[7].x = pts.x - path.x * radius + path.y * radius;
	_hoops_CICCS->_hoops_ASPS[5].y = _hoops_CICCS->_hoops_ASPS[7].y = pts.y - path.y * radius - path.x * radius;
	_hoops_CICCS->_hoops_ASPS[5].z = _hoops_CICCS->_hoops_ASPS[7].z = pts.z - path.z * radius;
	_hoops_CICCS->_hoops_ASPS += 9;
	_hoops_CICCS->count += 3;
}

local INLINE void _hoops_IGSCS(Net_Rendition const &nr, _hoops_PICCS * _hoops_CICCS, DC_Point & pts, Vector const & path, float radius)
{
	if ((_hoops_CICCS->count+1)*3 >= _hoops_CICCS->_hoops_SAGCA) 
		_hoops_PSCCS(nr ,_hoops_CICCS, 1, 3);
	_hoops_CICCS->_hoops_ASPS[0].x = pts.x - path.y * radius;
	_hoops_CICCS->_hoops_ASPS[0].y = pts.y + path.x * radius;
	_hoops_CICCS->_hoops_ASPS[0].z = pts.z;
	_hoops_CICCS->_hoops_ASPS[1].x = pts.x - path.x * radius;
	_hoops_CICCS->_hoops_ASPS[1].y = pts.y - path.y * radius;
	_hoops_CICCS->_hoops_ASPS[1].z = pts.z;
	_hoops_CICCS->_hoops_ASPS[2].x = pts.x + path.y * radius;
	_hoops_CICCS->_hoops_ASPS[2].y = pts.y - path.x * radius;
	_hoops_CICCS->_hoops_ASPS[2].z = pts.z;
	_hoops_CICCS->_hoops_ASPS += 3;
	_hoops_CICCS->count++;
}

local INLINE void _hoops_CGSCS(Net_Rendition const &nr, Line_Style const & _hoops_ACCI, DC_Point & _hoops_GSGGA)
{
	if (!BIT(_hoops_ACCI->flags,_hoops_PRCAP)) {
		if (_hoops_GSGGA.z < 0.0f) 
			_hoops_GSGGA.z = 0.0f;
		if (_hoops_GSGGA.z > nr->transform_rendition->_hoops_PCHH) 
			_hoops_GSGGA.z = nr->transform_rendition->_hoops_PCHH;
	}
}


GLOBAL_FUNCTION void HD_Std_DC_Polyline (
	Net_Rendition const &		_hoops_ACRIP,
	int							incount,
	DC_Point const *			_hoops_IRRAA) {
#ifndef DISABLE_DRAW_3D
	Line_Rendition const &		_hoops_SGSCS = _hoops_ACRIP->_hoops_AHP;
	Net_Rendition				nr = _hoops_ACRIP.Copy();
	Line_Rendition				_hoops_HC = nr->_hoops_AHP;
	Display_Context const *		dc = nr->_hoops_SRA;
	Line_Style const &			_hoops_ACCI = _hoops_HC->line_style;
	Line_Style_Parallel *		_hoops_RIIPI;
	Net_Rendition				_hoops_PIRCP;
	Net_Rendition				_hoops_GRSCS;
	Net_Rendition				_hoops_RRSCS;
	Line_Rendition				_hoops_IASGR;
	_hoops_HHCR			_hoops_GGCC;
	DC_Point const				*points, *_hoops_PSHCS;
	int							count, use_count;
	bool 						_hoops_SPGPA = false;
	bool 						_hoops_ARSCS;
	bool 						_hoops_PRSCS = false;
	int 						weight = 0;
	int 						_hoops_HRSCS;
	int 						_hoops_RRC;

	_hoops_HICCS *				_hoops_IRSCS[256];
	int							_hoops_CRSCS = 0;

	if (BIT(nr->_hoops_AHP->line_style->flags, _hoops_CRCAP))
		return;

	if ((weight = nr->_hoops_AHP->weight) < 0)
		weight = (int)(HD_Compute_Generic_Size (nr, 
					nr->_hoops_AHP->_hoops_PHP, 
					nr->_hoops_AHP->_hoops_HHP, 1.0f, false, 0, true)+0.5f);

	//_hoops_RPP (_hoops_SGCR < 1) _hoops_SGCR = 1;

	_hoops_HRSCS = weight;

	if (ANYBIT(_hoops_ACCI->flags, _hoops_RHISA) &&
		nr->_hoops_GSP->ysize < 0) {
			_hoops_ICP alter &	_hoops_HCSHP = nr->_hoops_GSP.Modify();
			float						size;

			size = HD_Compute_Generic_Size (nr, _hoops_HCSHP->_hoops_PHP, _hoops_HCSHP->_hoops_HHP, 1.0f, false, 0, true);
			_hoops_HCSHP->ysize = size*0.5f;
			_hoops_HCSHP->_hoops_RGRS = size*0.5f*dc->current._hoops_AGRS;
#if 0
			/*_hoops_HSGR _hoops_IH _hoops_HA */
			if (nr->_hoops_GSP->_hoops_HHP == _hoops_SPSC &&	nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH) {
				_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
				Point temp;
				float _hoops_SACPA;

				temp.x = _hoops_HPRA (_hoops_IHCR->_hoops_IPH->elements, marker->_hoops_CSAI);
				temp.y = _hoops_IPRA (_hoops_IHCR->_hoops_IPH->elements, marker->_hoops_CSAI);
				temp.z = _hoops_CPRA (_hoops_IHCR->_hoops_IPH->elements, marker->_hoops_CSAI);
				z = _hoops_CPRA (_hoops_IHCR->_hoops_SPH->_hoops_PRPA.elements, temp);
				w = _hoops_PHCP (_hoops_IHCR->_hoops_SPH->_hoops_PRPA.elements, temp);
				z /= w;
				z /= _hoops_IHCR->_hoops_SPH->_hoops_SRIR;
				_hoops_SACPA = 1 / (z + 1);
				_hoops_HCSHP->ysize *= _hoops_SACPA;
				_hoops_HCSHP->_hoops_RGRS *= _hoops_SACPA;
			}
#endif
	}

	if (BIT(nr->transform_rendition->flags, _hoops_AIHS) &&
		(weight > 1 ||
		!BIT(_hoops_ACCI->flags, LSF_SOLID) || 
		ANYBIT(_hoops_ACCI->flags, _hoops_RHISA|LSF_OFFSET))) {

		nr->transform_rendition.Modify()->flags &= ~_hoops_AIHS;
	}

	if ((_hoops_HC = _hoops_ACRIP->_hoops_AHP->_hoops_SSHHP) == null) {
		_hoops_HC = nr->_hoops_AHP;
		((Line_Rendition alter &)_hoops_ACRIP->_hoops_AHP)->_hoops_SSHHP = _hoops_HC.Modify();

		HD_Replace_Line_Style(_hoops_HC, nr->_hoops_GCSHP->_hoops_IHRIP);

		_hoops_HC->weight = 1;
		_hoops_HC->flags = 0;
		_hoops_HC->style = LCAP_BUTT|LJOIN_MITER;
	}
	nr->_hoops_AHP = _hoops_HC;


	if (weight > 1 || BIT(_hoops_ACCI->flags, LSF_WEIGHT)) {
		if (_hoops_HC->_hoops_IHA == null) {
			_hoops_HC->_hoops_IHA = nr->_hoops_IHA;
			_hoops_CIGA alter &		_hoops_SIGA = _hoops_HC->_hoops_IHA.Modify();

			_hoops_SIGA->_hoops_RGIR = _hoops_SIGA->color = _hoops_HC->color;
			_hoops_SIGA->contrast_color = _hoops_HC->contrast_color;
			
			_hoops_SIGA->pattern = FP_SOLID;

			_hoops_SIGA->_hoops_CHA = _hoops_HC->_hoops_CHA;
		}
		nr->_hoops_IHA = _hoops_HC->_hoops_IHA;

		_hoops_GGCC = nr->transform_rendition.Modify();

		_hoops_GGCC->_hoops_CHIH = 0;
#if 0
		_hoops_GGCC->flags &= ~_hoops_IGSP;
		_hoops_GGCC->heuristics &= ~(_hoops_SASA | _hoops_GPSA);
#endif
	}

	// _hoops_HHGPR _hoops_RIPS _hoops_HAIR _hoops_SRSCS _hoops_RIAH
	POOL_ZALLOC(_hoops_IRSCS[0], _hoops_HICCS, dc->memory_pool);
	_hoops_IRSCS[0]->nr = nr;
	_hoops_CRSCS++;
	
	if (BIT(_hoops_ACCI->flags, LSF_CONTRAST)) {
		_hoops_PIRCP = nr;
   
		if ((_hoops_IASGR = _hoops_ACRIP->_hoops_AHP->contrast_rendition) == null) {
			_hoops_IASGR = nr->_hoops_AHP;
			((Line_Rendition alter &)_hoops_ACRIP->_hoops_AHP)->contrast_rendition = _hoops_IASGR.Modify();

			_hoops_IASGR->color = _hoops_IASGR->contrast_color;

			_hoops_IASGR->_hoops_SSHHP = null;
			_hoops_IASGR->_hoops_IHA = null;
		}
		_hoops_PIRCP.Modify()->_hoops_AHP = _hoops_IASGR;

		/* _hoops_RRP _hoops_CGARA _hoops_HSP */
		if (weight > 1 || BIT(_hoops_ACCI->flags, LSF_WEIGHT)) {
			if (_hoops_IASGR->_hoops_IHA == null) {
				_hoops_IASGR->_hoops_IHA = _hoops_PIRCP->_hoops_IHA;

				_hoops_CIGA alter &		_hoops_SIGA = _hoops_IASGR->_hoops_IHA.Modify();

				_hoops_SIGA->_hoops_RGIR = _hoops_SIGA->color = _hoops_IASGR->color;
				_hoops_SIGA->contrast_color = _hoops_IASGR->contrast_color;
				_hoops_SIGA->pattern = FP_SOLID;
			}
			_hoops_PIRCP->_hoops_IHA = _hoops_IASGR->_hoops_IHA;
		}

		POOL_ZALLOC(_hoops_IRSCS[1], _hoops_HICCS, dc->memory_pool);
		_hoops_IRSCS[1]->nr = _hoops_PIRCP;
		_hoops_CRSCS++;
	}


	_hoops_ARSCS = (dc->_hoops_APHHP != null) &&
						 BIT (nr->transform_rendition->heuristics, _hoops_PAIRP);

	_hoops_PSHCS = _hoops_IRRAA;
	use_count = incount;
	_hoops_RRC = 0;

	if (incount < 0) {
		_hoops_ICHC (incount, _hoops_RRC, 2);
		use_count=2;
	}

_hoops_GASCS:

	_hoops_RIIPI = _hoops_ACCI->_hoops_GHISR;

	_hoops_SPGPA = (_hoops_PSHCS[0].x == _hoops_PSHCS[use_count-1].x &&
			  _hoops_PSHCS[0].y == _hoops_PSHCS[use_count-1].y &&
			  _hoops_PSHCS[0].z == _hoops_PSHCS[use_count-1].z);

_hoops_RASCS:

	points = _hoops_PSHCS;
	count = use_count;

	if (BIT(_hoops_RIIPI->flags, LSF_WEIGHT)) {
		weight = (int)(HD_Compute_Generic_Size (nr, 
												_hoops_RIIPI->weight.value, 
												_hoops_RIIPI->weight._hoops_HHP, 
												1.0f, false, 0, true) + 0.5f);

		//_hoops_RPP (_hoops_SGCR < 1) 
		//	_hoops_SGCR = 1;

		if (!BIT(_hoops_RIIPI->flags, LSF_FIXED_WEIGHT)) 
			weight *= _hoops_HRSCS;
	}
	else
		weight = _hoops_HRSCS;

	if (weight > 1 &&	
		!BIT(_hoops_ACRIP->_hoops_AHP->flags, _hoops_SSGIP) &&
			(!dc->options._hoops_HHHSR &&
				!BIT(_hoops_RIIPI->flags, LSF_ABSOLUTE_WEIGHT)))
			weight = int (weight * dc->_hoops_PGCC._hoops_CCPGH);

	/* _hoops_PCPC _hoops_GGAIA */
	if (BIT(_hoops_SGSCS->flags, _hoops_HGRIP) && BIT(_hoops_RIIPI->flags, LSF_JOIN))
		goto _hoops_AASCS;
			
	if (weight == 1 && BIT(_hoops_RIIPI->flags, LSF_SOLID) &&
		!ANYBIT(_hoops_RIIPI->flags, _hoops_RHISA|LSF_OFFSET)) {
		if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP)) {
			nr->_hoops_IRR.Modify()->_hoops_CHP &= ~_hoops_SHP;

			if (BIT(_hoops_ACCI->flags,_hoops_PRCAP) || _hoops_ACCI->_hoops_IPCAP > 1)
				if (BIT(_hoops_RIIPI->flags,LSF_CONTRAST))
					_hoops_SCGGA(_hoops_PIRCP, count, points);
				else
					_hoops_SCGGA(nr, count, points);
			else {
				HD_Span_DC_Polyline (nr, count, points);
			}
		}
		else {
			if (BIT(_hoops_ACCI->flags,_hoops_PRCAP) || _hoops_ACCI->_hoops_IPCAP > 1)
				if (BIT(_hoops_RIIPI->flags,LSF_CONTRAST))
					_hoops_SCGGA(_hoops_PIRCP, count, points);
				else
					_hoops_SCGGA(nr, count, points);
			else
				HD_Span_DC_Polyline (nr, count, points);
		}
	}
	else {
		/* _hoops_RSGI _hoops_IIGR _hoops_IIPH _hoops_PAR _hoops_SIRAR _hoops_III _hoops_RRGR */
		/*_hoops_PASCS*/

		Int_Rectangle  				_hoops_GPHH;
		_hoops_GPPA	*	_hoops_HASCS = null;

		_hoops_RCCCS *			_hoops_IASCS = null;
		_hoops_RCCCS *			_hoops_CASCS = null;
		_hoops_RCCCS *			_hoops_SCCCS = null;
		_hoops_RCCCS *			_hoops_SASCS = null; 
		
		_hoops_RCCCS *			_hoops_GPSCS = null;
		_hoops_RCCCS *			_hoops_RPSCS = null;
		_hoops_RCCCS *			_hoops_APSCS = null;

		DC_Point 					_hoops_PPSCS, _hoops_HPSCS;
		DC_Point 					_hoops_GSGGA[2];
		int							_hoops_PCIGI, _hoops_HCIGI;
		float						_hoops_IPSCS, _hoops_CPSCS;
		float						offset = 0, factor, length;
		double						_hoops_IIIPI = 0;
		float 						_hoops_SPSCS = 0;
		float 						_hoops_SPHH, _hoops_GHHH;
		float 						_hoops_RSIPA;
		float 						_hoops_GHSCS = 0.0f;
		int							_hoops_RHSCS = 0;
		bool 						_hoops_AHSCS = false;
		bool 						_hoops_PHSCS = true, _hoops_HHSCS = true, _hoops_IHSCS;
		bool 						_hoops_GSCCS = BIT(dc->_hoops_PGCC.flags, _hoops_CCHSR);
		Vector						path = _hoops_IRGA::_hoops_CRGA, _hoops_CHSCS;
		int const *					pattern = _hoops_RIIPI->pattern;
		int							_hoops_RCAIR = _hoops_RIIPI->_hoops_RHISR;
		Line_Style_Item *			pattern_items = _hoops_RIIPI->pattern_items;
		float						_hoops_ICPGH;
		float 						_hoops_SHSCS = 0.0f;
		float 						_hoops_GISCS = 0.0f;
		float 						_hoops_RISCS = 0.0f;	
		int 						_hoops_AISCS = 0;
		int 						_hoops_PISCS = 0;
		float						radius = weight * 0.5f;
		DC_Point					*_hoops_HISCS = null, *_hoops_IISCS = null;
		DC_Point					_hoops_CISCS[2];
		float						_hoops_SISCS;

		/* _hoops_RHPP _hoops_SSCP _hoops_GCRHA _hoops_PPR _hoops_GCSCS _hoops_IRS _hoops_IHGP _hoops_AAIA _hoops_III */
		if (BIT(_hoops_RIIPI->flags, LSF_SOLID) &&
			!ANYBIT(_hoops_RIIPI->flags, _hoops_RHISA|LSF_OFFSET))
			_hoops_GSCCS = false;

		if (BIT(_hoops_RIIPI->flags, LSF_OFFSET)) 
			offset = -HD_Compute_Generic_Size (nr, _hoops_RIIPI->offset.value, _hoops_RIIPI->offset._hoops_HHP, 
												_hoops_HRSCS, false, 0, true);

		/*_hoops_CSRA _hoops_SHI _hoops_HPP _hoops_III _hoops_SGCR */
		if (!BIT(_hoops_RIIPI->flags, LSF_FIXED_OFFSET))
			offset *= _hoops_HRSCS;

		if (BIT(_hoops_RIIPI->flags, LSF_ABSOLUTE_LENGTH))
			_hoops_ICPGH = 1.0f;
		else
			_hoops_ICPGH = dc->_hoops_PGCC._hoops_ICPGH;

		/* _hoops_HGSR _hoops_HSPH _hoops_CCA _hoops_IHH _hoops_IH _hoops_III _hoops_IGAA */
		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

		_hoops_GPHH._hoops_IACHA(weight*2);

		{//////////////////////////////

		_hoops_RCCCS **		_hoops_RCSCS = &_hoops_SASCS;
		int							_hoops_ACSCS = _hoops_SHCCS;

		/* _hoops_ASGGR _hoops_HSGP _hoops_SRSCS _hoops_HIGR */
		for (int i=0; i<_hoops_RCAIR; i++) {

			POOL_ZALLOC (_hoops_SCCCS, _hoops_RCCCS, nr->_hoops_SRA->memory_pool);

			_hoops_SCCCS->_hoops_SSAC = _hoops_IASCS;
			_hoops_IASCS = _hoops_SCCCS;

			*_hoops_RCSCS = _hoops_SCCCS;
			_hoops_RCSCS = &_hoops_SCCCS->next;

			if (pattern[i] < 0) {

				Line_Style_Item *	_hoops_PCSCS = &pattern_items[_hoops_RHSCS];

				if (pattern[i] == _hoops_PPCAP) {

					_hoops_GASC glyph;
					float rotation;
					Line_Style_Flags flags;
					float size;

					_hoops_ASCCS(nr, _hoops_PCSCS, glyph, rotation, flags, size);
					_hoops_RSCCS(nr, _hoops_SCCCS, glyph, rotation, size, flags, _hoops_PCSCS->weight, 1);

					_hoops_AHSCS = true;
				}
				else {

					if (_hoops_PCSCS->size._hoops_HHP == GSU_PERCENT) {
						_hoops_SCCCS->flags |= _hoops_SACAP;
						_hoops_SCCCS->_hoops_ACCCS = _hoops_PCSCS->size.value;
						_hoops_PISCS++;
					}
					else {
						_hoops_SCCCS->size = HD_Compute_Generic_Size (nr,
							_hoops_PCSCS->size.value, _hoops_PCSCS->size._hoops_HHP, 1.0f, false, 0, true);

						/* _hoops_HCSCS _hoops_AGSR _hoops_ICSCS _hoops_HIS _hoops_SHH _hoops_RHRIR */
						if (_hoops_SCCCS->size != _hoops_IICIA &&
							_hoops_PCSCS->size._hoops_HHP == GSU_PIXELS)
							_hoops_SCCCS->size *= _hoops_ICPGH;
					}

					if (pattern[i] == _hoops_RPCAP) {
						
						_hoops_SCCCS->mode = _hoops_RICCS;	
						_hoops_ACSCS = _hoops_SHCCS;
					}
					else {
						if (pattern[i] == _hoops_APCAP) {

							_hoops_SCCCS->_hoops_CSC = _hoops_IRSCS[1];
							_hoops_CCCCS(nr, _hoops_SCCCS, weight, _hoops_GSCCS);
						} else {

							if (!ANYBIT(_hoops_PCSCS->flags, _hoops_HRCAP|_hoops_IRCAP)) {

								_hoops_SCCCS->_hoops_CSC = _hoops_IRSCS[0];
							}
							else {

								// _hoops_CRICR _hoops_IS _hoops_RPHH _hoops_HAIR _hoops_RRGR
								Driver_Color	_hoops_CPHHP = nr->_hoops_AHP->color; 

								if (BIT(_hoops_PCSCS->flags, _hoops_IRCAP)) {

									RGB		color = _hoops_PCSCS->rgb;

									if (dc->options._hoops_RAHHP) {
										_hoops_CPHHP = dc->_hoops_SPHHP;
									}
									else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR ||
												(ANYBIT (nr->current, _hoops_RSSHP|_hoops_CISHP) &&
													nr->_hoops_ASIR->buffer._hoops_GHAAP == _hoops_PHAAP)) {

											float _hoops_PHHHP;
											_hoops_PHHHP = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f;
											_hoops_CPHHP._hoops_HRIR.r = dc->_hoops_PGCC._hoops_HHHHP[(int)(color.red   * _hoops_PHHHP)];
											_hoops_CPHHP._hoops_HRIR.g = dc->_hoops_PGCC._hoops_HHHHP[(int)(color.green * _hoops_PHHHP)];
											_hoops_CPHHP._hoops_HRIR.b = dc->_hoops_PGCC._hoops_HHHHP[(int)(color.blue  * _hoops_PHHHP)];
											_hoops_CPHHP._hoops_HRIR.a = _hoops_GPGCR;
									}
									else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
										int			index;
										_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR; 
										index = (int)(color.red * ((float)dc->_hoops_AGPGH.r - 0.001f));
										index *= dc->_hoops_AGPGH.g;
										index += (int)(color.green * ((float)dc->_hoops_AGPGH.g - 0.001f));
										index *= dc->_hoops_AGPGH.b;
										index += (int)(color.blue * ((float)dc->_hoops_AGPGH.b - 0.001f));
										_hoops_CPHHP._hoops_PGGCR = index + dc->_hoops_RHGCR;
									}
									else /* _hoops_AIHHP */ {
										_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR;
										_hoops_CPHHP._hoops_PIHHP = (_hoops_HIHHP)(color._hoops_CPIR() * 
											((float)dc->_hoops_PGCC._hoops_PCHSR - 0.001f));
									}
								}
								else {
									// _hoops_CCSCS 
#ifndef DISABLE_COLOR_MAPS
									_hoops_CAHHP const &		_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
									int								index = _hoops_PCSCS->index;

									if (index >= (int)_hoops_SAHHP->length) {
										char			buf[MAX_ERRMSG];
										Sprintf_DD (buf, "The current color map has only %d entries; offset %d was requested.", 
											(int)_hoops_SAHHP->length, index);
										_hoops_PHPGR (HEC_COLOR, HES_OUT_OF_RANGE_COLOR_INDEX,
											Sprintf_N (null, "A color-by-index in line style %n is out of range -", &_hoops_ACCI->name), buf);
									}
									else {
										if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
											_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR;	/* _hoops_CASI _hoops_SCH _hoops_GGSR */
											_hoops_CPHHP._hoops_PGGCR = _hoops_SAHHP->_hoops_RHHHP + index;
										}
										else {
											_hoops_CPHHP = _hoops_SAHHP->_hoops_AHHHP[index];
										}
									}
#endif
								}

								if (BIT(nr->_hoops_ARA->_hoops_IHRH.options, _hoops_CHRH))
									HD_Tint_Driver_Color (nr, &_hoops_CPHHP);

								/* _hoops_SSS _hoops_PIS _hoops_HAIR */
								for (int i=0; i<_hoops_CRSCS; i++) {

									if (_hoops_IRSCS[i]->nr->_hoops_AHP->color == _hoops_CPHHP) {
										_hoops_SCCCS->_hoops_CSC = _hoops_IRSCS[i];
										break;
									}
								}

								if (_hoops_SCCCS->_hoops_CSC == null) {

									POOL_ZALLOC(_hoops_IRSCS[_hoops_CRSCS], _hoops_HICCS, dc->memory_pool);
									_hoops_SCCCS->_hoops_CSC = _hoops_IRSCS[_hoops_CRSCS++];

									_hoops_SCCCS->_hoops_CSC->nr = nr.Copy();

									Line_Rendition	alter &	_hoops_SCSCS = _hoops_SCCCS->_hoops_CSC->nr->_hoops_AHP.Modify();

									_hoops_SCSCS->color = _hoops_CPHHP;

									if (weight > 1 || BIT(_hoops_ACCI->flags, LSF_WEIGHT)) {

										_hoops_SCSCS->_hoops_IHA = nr->_hoops_IHA;
										_hoops_CIGA alter &	_hoops_GSSCS = _hoops_SCSCS->_hoops_IHA.Modify();

										_hoops_GSSCS->_hoops_RGIR = _hoops_GSSCS->color = _hoops_SCSCS->color;
										_hoops_GSSCS->contrast_color = _hoops_SCSCS->contrast_color;

										_hoops_GSSCS->pattern = FP_SOLID;

										_hoops_GSSCS->_hoops_CHA = _hoops_SCSCS->_hoops_CHA;

										_hoops_SCCCS->_hoops_CSC->nr->_hoops_IHA = _hoops_GSSCS;
									}
								}
							}

							_hoops_CCCCS(nr, _hoops_SCCCS, weight, _hoops_GSCCS);
						}
						_hoops_ACSCS = _hoops_RICCS;
					}
				}

				_hoops_RHSCS++;
			}
			else {	

				/* _hoops_HGSR "_hoops_GSSR" _hoops_HSGP */
				_hoops_SCCCS->size = (float)pattern[i];

				/* _hoops_HCSCS _hoops_AGSR _hoops_ICSCS _hoops_HIS _hoops_SHH _hoops_RHRIR */
				if (_hoops_SCCCS->size != _hoops_IICIA)
					_hoops_SCCCS->size *= _hoops_ICPGH;

				if (_hoops_ACSCS == _hoops_SHCCS) { 

					_hoops_SCCCS->_hoops_CSC = _hoops_IRSCS[0];
					_hoops_CCCCS(nr, _hoops_SCCCS, weight, _hoops_GSCCS);
					_hoops_ACSCS = _hoops_RICCS;
				}
				else {
		
					_hoops_SCCCS->mode = _hoops_RICCS;	
					_hoops_ACSCS = _hoops_SHCCS;
				}
			}
		}

		if (!_hoops_SASCS) {

			/* _hoops_SHI _hoops_RPHSR _hoops_III */
			POOL_ZALLOC (_hoops_SCCCS, _hoops_RCCCS, nr->_hoops_SRA->memory_pool);

			_hoops_SCCCS->_hoops_CSC = _hoops_IRSCS[0];
			_hoops_CCCCS(nr, _hoops_SCCCS, weight, _hoops_GSCCS);

			_hoops_SCCCS->size = (float)_hoops_IICIA;

			_hoops_SCCCS->_hoops_SSAC = _hoops_SCCCS->next = _hoops_SASCS = _hoops_SCCCS;
		}
		else {
			/* _hoops_PSSRH _hoops_GH _hoops_RSRPA */
			_hoops_SASCS->_hoops_SSAC = _hoops_IASCS;
			_hoops_IASCS->next = _hoops_SASCS;
		}

		} //////////////////////////////

		/*_hoops_IRHH _hoops_RCRR _hoops_SR _hoops_HS _hoops_IRS _hoops_RSSCS _hoops_IH _hoops_ACPC _hoops_PPR _hoops_PCPC */
		if (weight > 1 && 
			((_hoops_SGSCS->style & LCAP_MASK) != LCAP_BUTT || 
			(_hoops_SGSCS->style & LJOIN_MASK))) {

				if (!_hoops_IRSCS[0]->_hoops_SICCS)
					_hoops_IRSCS[0]->_hoops_SICCS = _hoops_HCCCS(nr, false, _hoops_PCCCS);

				if (BIT(_hoops_ACCI->flags, LSF_CONTRAST) && !_hoops_IRSCS[1]->_hoops_SICCS) 
					_hoops_IRSCS[1]->_hoops_SICCS = _hoops_HCCCS(nr, false, _hoops_PCCCS);
		}

		/* _hoops_CCIH _hoops_GH _hoops_RPHH _hoops_PAIA*/
		if (_hoops_AHSCS) {
			_hoops_SCCCS = _hoops_SASCS;

			do {
				if (_hoops_SCCCS->mode == _hoops_AICCS) {
					if (BIT(_hoops_SCCCS->flags, _hoops_GACAP)) {
						float size = _hoops_SCCCS->size;

						while (_hoops_SCCCS->next->mode != _hoops_AICCS &&
								!BIT(_hoops_SCCCS->next->flags, _hoops_AACAP)) {

							if (size >= _hoops_SCCCS->next->size) {
								_hoops_IASCS = _hoops_SCCCS->next;
								_hoops_SCCCS->next = _hoops_SCCCS->next->next;
								_hoops_SCCCS->next->_hoops_SSAC = _hoops_SCCCS;
								if (_hoops_IASCS->glyph_lsic)
									_hoops_CSCCS(_hoops_IASCS->glyph_lsic);
								FREE(_hoops_IASCS, _hoops_RCCCS);
							}
							else {
								_hoops_SCCCS->next->size -= _hoops_SCCCS->size;
								break;
							}
						}

						size = _hoops_SCCCS->size;

						while (_hoops_SCCCS->_hoops_SSAC->mode != _hoops_AICCS &&
								!BIT(_hoops_SCCCS->_hoops_SSAC->flags, _hoops_AACAP)) {

							if (size >= _hoops_SCCCS->_hoops_SSAC->size) {
								_hoops_IASCS = _hoops_SCCCS->_hoops_SSAC;
								_hoops_SCCCS->_hoops_SSAC = _hoops_SCCCS->_hoops_SSAC->_hoops_SSAC;
								_hoops_SCCCS->_hoops_SSAC->next = _hoops_SCCCS;
								if (_hoops_IASCS->glyph_lsic)
									_hoops_CSCCS(_hoops_IASCS->glyph_lsic);
								FREE(_hoops_IASCS, _hoops_RCCCS);
							}
							else {
								_hoops_SCCCS->_hoops_SSAC->size -= _hoops_SCCCS->size;
								break;
							}
						}
					}

					if (ANYBIT(_hoops_SCCCS->flags, _hoops_GACAP|_hoops_AACAP)) {
						POOL_ZALLOC(_hoops_IASCS, _hoops_RCCCS, nr->_hoops_SRA->memory_pool);

						_hoops_SCCCS->_hoops_SSAC->next = _hoops_IASCS;
						_hoops_IASCS->_hoops_SSAC = _hoops_SCCCS->_hoops_SSAC;
						_hoops_IASCS->next = _hoops_SCCCS;
						_hoops_SCCCS->_hoops_SSAC = _hoops_IASCS;

						_hoops_IASCS->mode = _hoops_RICCS;
						_hoops_IASCS->size = _hoops_SCCCS->size;
						_hoops_IASCS->flags |= _hoops_AACAP;

						POOL_ZALLOC(_hoops_IASCS, _hoops_RCCCS, nr->_hoops_SRA->memory_pool);

						_hoops_SCCCS->next->_hoops_SSAC = _hoops_IASCS;
						_hoops_IASCS->_hoops_SSAC = _hoops_SCCCS;
						_hoops_IASCS->next = _hoops_SCCCS->next;
						_hoops_SCCCS->next = _hoops_IASCS;

						_hoops_IASCS->mode = _hoops_RICCS;
						_hoops_IASCS->size = _hoops_SCCCS->size;
						_hoops_IASCS->flags |= _hoops_AACAP;

						/* _hoops_HSGR _hoops_ISGR _hoops_PCPA _hoops_CSAP _hoops_RRAI */
						_hoops_SCCCS = _hoops_IASCS;
					}
				}

				_hoops_SCCCS = _hoops_SCCCS->next;
			} while (_hoops_SCCCS != _hoops_SASCS);

			_hoops_SCCCS = _hoops_SASCS;

			while (1) {
				if (_hoops_SCCCS->mode == _hoops_AICCS && _hoops_SCCCS->next->mode == _hoops_AICCS) {
					POOL_ZALLOC(_hoops_IASCS, _hoops_RCCCS, nr->_hoops_SRA->memory_pool);
			
					_hoops_IASCS->mode = _hoops_RICCS;
					_hoops_IASCS->size = _hoops_SCCCS->size+_hoops_SCCCS->next->size;
					_hoops_IASCS->flags |= _hoops_AACAP;

					_hoops_IASCS->_hoops_SSAC = _hoops_SCCCS;
					_hoops_IASCS->next = _hoops_SCCCS->next;

					_hoops_SCCCS->next->_hoops_SSAC = _hoops_IASCS;
					_hoops_SCCCS->next = _hoops_IASCS;
				}
				
				_hoops_SCCCS = _hoops_SCCCS->next;
				
				if (_hoops_SCCCS == _hoops_SASCS) break;
			}
		}

		/* _hoops_ASGGR _hoops_HSPP _hoops_RPHH _hoops_SRSCS */
		if (!BIT(_hoops_SGSCS->flags, _hoops_HHISA) &&
			(BIT(_hoops_RIIPI->flags, LSF_START_GLYPH) || _hoops_SGSCS->start_glyph != null)) {

			_hoops_GASC glyph = _hoops_SGSCS->start_glyph;
			float rotation = 0;
			Line_Style_Flags flags = 0;
			float size = nr->_hoops_GSP->ysize;

			if (!glyph)
				_hoops_ASCCS(nr, _hoops_RIIPI->start_glyph, glyph, rotation, flags, size);

			POOL_ZALLOC(_hoops_SCCCS, _hoops_RCCCS, nr->_hoops_SRA->memory_pool);
			_hoops_RSCCS(nr, _hoops_SCCCS, glyph, rotation, size, flags, _hoops_RIIPI->start_glyph->weight, 1);

			_hoops_SCCCS->next = _hoops_CASCS;
			_hoops_CASCS = _hoops_SCCCS;
			_hoops_GPSCS = _hoops_SCCCS;
		}

		/* _hoops_ASGGR _hoops_IRGP _hoops_RPHH _hoops_SRSCS */
		if (count > 2 && !BIT(_hoops_SGSCS->flags, _hoops_HGRIP) &&
			(BIT(_hoops_RIIPI->flags, LSF_MIDDLE_GLYPH) || _hoops_SGSCS->middle_glyph != null)) {

			_hoops_GASC glyph = _hoops_SGSCS->middle_glyph;
			float rotation = 0;
			Line_Style_Flags flags = 0;
			float size = nr->_hoops_GSP->ysize;

			if (!glyph)
				_hoops_ASCCS(nr, _hoops_RIIPI->middle_glyph, glyph, rotation, flags, size);

			POOL_ZALLOC(_hoops_SCCCS, _hoops_RCCCS, nr->_hoops_SRA->memory_pool);
			_hoops_RSCCS(nr, _hoops_SCCCS, glyph, rotation, size, flags, _hoops_RIIPI->middle_glyph->weight, 32);

			_hoops_SCCCS->next = _hoops_CASCS;
			_hoops_CASCS = _hoops_SCCCS;
			_hoops_RPSCS = _hoops_SCCCS;
		}

		/* _hoops_ASGGR _hoops_RSGR _hoops_RPHH _hoops_SRSCS */
		if (!BIT(_hoops_SGSCS->flags, _hoops_PHISA) &&
			(BIT(_hoops_RIIPI->flags, LSF_END_GLYPH) || _hoops_SGSCS->end_glyph != null)) {

			_hoops_GASC glyph = _hoops_SGSCS->end_glyph;
			float rotation = 0;
			Line_Style_Flags flags = 0;
			float size = nr->_hoops_GSP->ysize;

			if (!glyph)
				_hoops_ASCCS(nr, _hoops_RIIPI->end_glyph, glyph, rotation, flags, size);

			POOL_ZALLOC(_hoops_SCCCS, _hoops_RCCCS, nr->_hoops_SRA->memory_pool);
			_hoops_RSCCS(nr, _hoops_SCCCS, glyph, rotation, size, flags, _hoops_RIIPI->end_glyph->weight, 1);

			_hoops_SCCCS->next = _hoops_CASCS;
			_hoops_CASCS = _hoops_SCCCS;
			_hoops_APSCS = _hoops_SCCCS;
		}

		/* _hoops_ASGGR _hoops_SPCC _hoops_ASSCS */
		_hoops_SCCCS = _hoops_SASCS;
		while (1) {
			_hoops_SCCCS->_hoops_AHHRI = _hoops_SCCCS->size;

			if (_hoops_SCCCS->size == (float)_hoops_IICIA) {
				_hoops_SCCCS->flags |= _hoops_CACAP;
				_hoops_AISCS++;
			}
			else if (BIT(_hoops_SCCCS->flags, _hoops_SACAP))
				_hoops_RISCS += _hoops_SCCCS->_hoops_ACCCS;
			else if (_hoops_SCCCS->mode != _hoops_AICCS) 
				_hoops_SHSCS += _hoops_SCCCS->size;
			else
				_hoops_GISCS += _hoops_SCCCS->size;

			if ((_hoops_SCCCS = _hoops_SCCCS->next) == _hoops_SASCS) break;
		}

		/* _hoops_GAAP _hoops_SGGGA _hoops_HPP _hoops_SIHRR */
		_hoops_IIIPI = 0.0f;

		/* _hoops_GRAA _hoops_PSSCS _hoops_SPR _hoops_GHIR _hoops_ASSCS */
		if (!BIT(_hoops_RIIPI->flags, LSF_SEGMENTED) && 
			(_hoops_AISCS>0 || _hoops_PISCS>0 ||
			ANYBIT(_hoops_RIIPI->flags, LSF_FIT_CENTER|LSF_FIT_STRETCH))) {
			
			float _hoops_HSSCS = 0.0f;

			for (int i=0; i<count-1; i++) {
				path.x = points[i+1].x - points[i].x;
				path.y = points[i+1].y - points[i].y;
				length = path.x*path.x + path.y*path.y;
				_hoops_HSSCS+=_hoops_SGIHR (length);
			}

			_hoops_SCCCS = _hoops_SASCS;
			while (1) {
				if (BIT(_hoops_SCCCS->flags, _hoops_CACAP)) {
					float _hoops_SHIHP = _hoops_HSSCS - _hoops_SHSCS;
					_hoops_SHIHP -= _hoops_HSSCS * _hoops_RISCS / 100.0f;
					_hoops_SHIHP /= _hoops_AISCS;
					_hoops_SCCCS->size = _hoops_SHIHP;
				}
				else if (BIT(_hoops_SCCCS->flags, _hoops_SACAP))
					_hoops_SCCCS->size = HD_Compute_Generic_Size (nr, _hoops_SCCCS->_hoops_ACCCS, GSU_PERCENT, _hoops_HSSCS, false, 0, true);

				if (_hoops_SCCCS->size < 1.0f)
					_hoops_SCCCS->size = 1.0f;
				if ((_hoops_SCCCS = _hoops_SCCCS->next) == _hoops_SASCS) break;
			}

			if (ANYBIT(_hoops_RIIPI->flags, LSF_FIT_CENTER|LSF_FIT_STRETCH)) {
				float _hoops_ISSCS = 0.0f;
				float glyph_inline_total_lengths = 0.0f;
				
				_hoops_SCCCS = _hoops_SASCS;
				while (1) {
					if (_hoops_SCCCS->mode != _hoops_AICCS) {
						_hoops_ISSCS += _hoops_SCCCS->size;
						if (BIT(_hoops_SCCCS->flags, _hoops_AACAP))
							glyph_inline_total_lengths += _hoops_SCCCS->size;
					}
					if ((_hoops_SCCCS = _hoops_SCCCS->next) == _hoops_SASCS) break;
				}

				if (BIT(_hoops_RIIPI->flags, LSF_FIT_CENTER)) {
					float _hoops_CSSCS, _hoops_SSSCS, _hoops_GGGSS;

					_hoops_CSSCS = _hoops_ISSCS-_hoops_SASCS->size;
			
					if (_hoops_HSSCS>_hoops_CSSCS) {
						_hoops_SSSCS = _hoops_HSSCS-_hoops_CSSCS;
						_hoops_SSSCS *= 0.5f;
						_hoops_SSSCS = fmod(_hoops_SSSCS, _hoops_ISSCS);
						_hoops_SSSCS = _hoops_SASCS->size-_hoops_SSSCS;


						_hoops_GGGSS = _hoops_HSSCS-_hoops_SASCS->size;
						_hoops_GGGSS *= 0.5f;
						_hoops_GGGSS = fmod(_hoops_GGGSS, _hoops_ISSCS);
						_hoops_GGGSS = _hoops_ISSCS-_hoops_GGGSS;

						if (_hoops_SSSCS < 0)
							_hoops_IIIPI = -_hoops_GGGSS;
						else if (_hoops_GGGSS < 0)
							_hoops_IIIPI = -_hoops_SSSCS;
						else if (_hoops_SSSCS < _hoops_GGGSS) 
							_hoops_IIIPI = -_hoops_SSSCS;
						else
							_hoops_IIIPI = -_hoops_GGGSS;
					}
				}
				else {	/* _hoops_RGGSS */
					float _hoops_AGGSS, _hoops_PGGSS;
					int _hoops_HGGSS;

					_hoops_HGGSS = (int)(_hoops_HSSCS/_hoops_ISSCS+0.5f);

					if (_hoops_HGGSS == 0) 
						_hoops_HGGSS=1;

					_hoops_AGGSS = _hoops_HSSCS/((float)_hoops_HGGSS*_hoops_ISSCS);

					if (_hoops_ISSCS!=glyph_inline_total_lengths) {
						_hoops_PGGSS = (_hoops_AGGSS*_hoops_ISSCS-glyph_inline_total_lengths)/
										(_hoops_ISSCS-glyph_inline_total_lengths);

						_hoops_SCCCS = _hoops_SASCS;
						while (1) {
							if (_hoops_SCCCS->mode != _hoops_AICCS &&
								!BIT(_hoops_SCCCS->flags, _hoops_AACAP)) {
								
								_hoops_SCCCS->size *= _hoops_PGGSS;
								if (_hoops_SCCCS->size<1)
									_hoops_SCCCS->size=1;
							}
							if ((_hoops_SCCCS = _hoops_SCCCS->next) == _hoops_SASCS) break;
						}
					
						_hoops_IIIPI = -0.5f * _hoops_SASCS->size;
					}
					else {
						_hoops_SCCCS = _hoops_SASCS;
						while (1) {
							if (_hoops_SCCCS->mode != _hoops_AICCS) {
								
								_hoops_SCCCS->size *= _hoops_AGGSS;
								if (_hoops_SCCCS->size<1)
									_hoops_SCCCS->size=1;
							}
							if ((_hoops_SCCCS = _hoops_SCCCS->next) == _hoops_SASCS) break;
						}
					}
				}
			}
		}
		else if (_hoops_SHSCS+_hoops_GISCS < 1.0f) {
			/* _hoops_IGGSS _hoops_RISA _hoops_HSGP, _hoops_SAHR _hoops_IRHH _hoops_SCH _hoops_RPHSR */
			_hoops_SCCCS = _hoops_SASCS;
			while (1) {
				if (_hoops_SCCCS->mode == _hoops_SHCCS || _hoops_SCCCS->mode == _hoops_GICCS)
					_hoops_SCCCS->size = (float)_hoops_IICIA;

				if ((_hoops_SCCCS = _hoops_SCCCS->next) == _hoops_SASCS) 
					break;
			}
		}



		_hoops_PCIGI = 0;
		_hoops_HCIGI = count-1;

		_hoops_IPSCS = _hoops_CPSCS = 0.0f;

		/* _hoops_RGHH _hoops_HSPP _hoops_RPHH */
		if (_hoops_GPSCS) {
			path.x = points[1].x - points[0].x;
			path.y = points[1].y - points[0].y;
			path.z = points[1].z - points[0].z;

			length = path.x*path.x + path.y*path.y;

			/* _hoops_CGGSS _hoops_RGAR _hoops_HAR _hoops_RIRR */
			if (length < 1.0f && _hoops_GPSCS->rotation == 90.0f)
				goto _hoops_SGGSS;

			if (BIT(_hoops_RIIPI->flags, LSF_OFFSET)) {
				DC_Point	where;

				where = points[0];

				if (length != 1.0f) {
					length = 1.0f/_hoops_SGIHR (length);
					path.x *= length;
					path.y *= length;
				}

				where.x += path.y*offset;
				where.y -= path.x*offset;

				_hoops_GPSCS->glyph_lsic->points[0] = where;
			}
			else
				_hoops_GPSCS->glyph_lsic->points[0] = points[0];

			if (!BIT(_hoops_GPSCS->flags, _hoops_RACAP))
				_hoops_GPSCS->glyph_lsic->_hoops_RRSR[0] = _hoops_AGGGA(path.y, path.x) + _hoops_GPSCS->rotation;
			else
				_hoops_GPSCS->glyph_lsic->_hoops_RRSR[0] = _hoops_GPSCS->rotation;

			/* _hoops_SSPC _hoops_RPP _hoops_SIPP */
			if (BIT(_hoops_ACCI->flags,_hoops_PRCAP) ||
				_hoops_GPSCS->glyph_lsic->points[0].y-_hoops_GPSCS->size < _hoops_GPHH.top &&
				_hoops_GPSCS->glyph_lsic->points[0].y+_hoops_GPSCS->size > _hoops_GPHH.bottom &&
				_hoops_GPSCS->glyph_lsic->points[0].x-_hoops_GPSCS->size < _hoops_GPHH.right &&
				_hoops_GPSCS->glyph_lsic->points[0].x+_hoops_GPSCS->size > _hoops_GPHH.left)
				_hoops_GPSCS->glyph_lsic->count++;

			if (ANYBIT(_hoops_GPSCS->flags, _hoops_GACAP|_hoops_AACAP)) {
				DC_Point	_hoops_GRGSS;

				if (BIT(_hoops_GPSCS->flags, _hoops_GACAP)) 
					_hoops_IIIPI=-_hoops_GPSCS->size;

				_hoops_GRGSS.x = points[_hoops_PCIGI].x;
				_hoops_GRGSS.y = points[_hoops_PCIGI].y;
				_hoops_GRGSS.z = points[_hoops_PCIGI].z;

				for (; _hoops_PCIGI<_hoops_HCIGI; _hoops_PCIGI++) {
					_hoops_CHSCS.x = points[_hoops_PCIGI+1].x - _hoops_GRGSS.x;
					_hoops_CHSCS.y = points[_hoops_PCIGI+1].y - _hoops_GRGSS.y;
					_hoops_CHSCS.z = points[_hoops_PCIGI+1].z - _hoops_GRGSS.z;

					length = _hoops_CHSCS.x*_hoops_CHSCS.x + _hoops_CHSCS.y*_hoops_CHSCS.y;
					if (length != 1.0f) length = _hoops_SGIHR (length);

					if (length >= _hoops_GPSCS->size) {
						float _hoops_RRGSS, _hoops_ARGSS, _hoops_PRGSS, _hoops_HRGSS, _hoops_IRGSS, _hoops_HPRPA, _hoops_CRGSS, root;

						path.x = points[_hoops_PCIGI+1].x - points[_hoops_PCIGI].x;
						path.y = points[_hoops_PCIGI+1].y - points[_hoops_PCIGI].y;
						path.z = points[_hoops_PCIGI+1].z - points[_hoops_PCIGI].z;

						_hoops_RRGSS = path.x*path.x;
						_hoops_ARGSS = path.y*path.y;

						_hoops_PRGSS = _hoops_RRGSS+_hoops_ARGSS;

						_hoops_HRGSS = _hoops_GRGSS.x - points[_hoops_PCIGI].x;
						_hoops_IRGSS = _hoops_GRGSS.y - points[_hoops_PCIGI].y;

						_hoops_HPRPA = path.x*_hoops_IRGSS - path.y*_hoops_HRGSS;
						_hoops_CRGSS = path.x*_hoops_HRGSS + path.y*_hoops_IRGSS;

						root = _hoops_GPSCS->size*_hoops_GPSCS->size*_hoops_PRGSS - _hoops_HPRPA*_hoops_HPRPA;
						root = _hoops_SGIHR(root);

						_hoops_IPSCS = (_hoops_CRGSS + root)/_hoops_PRGSS;
						break;
					}
				}
			}
		}
_hoops_SGGSS:

		/* _hoops_RGHH _hoops_RSGR _hoops_RPHH */
		if (_hoops_APSCS) {
			path.x = points[count-1].x - points[count-2].x;
			path.y = points[count-1].y - points[count-2].y;
			path.z = points[count-1].z - points[count-2].z;

			length = path.x*path.x + path.y*path.y;

			if (length < 1.0f && _hoops_APSCS->rotation == 270.0f)
				goto _hoops_SRGSS;

			if (BIT(_hoops_RIIPI->flags, LSF_OFFSET)) {
				DC_Point	where;

				where = points[count-1];

				if (length != 1.0f) {
					length = 1.0f/_hoops_SGIHR (length);
					path.x *= length;
					path.y *= length;
				}

				where.x += path.y*offset;
				where.y -= path.x*offset;

				_hoops_APSCS->glyph_lsic->points[0] = where;
			}
			else
				_hoops_APSCS->glyph_lsic->points[0] = points[count-1];

			if (!BIT(_hoops_APSCS->flags, _hoops_RACAP))
				_hoops_APSCS->glyph_lsic->_hoops_RRSR[0] = _hoops_AGGGA(path.y, path.x) + _hoops_APSCS->rotation;
			else
				_hoops_APSCS->glyph_lsic->_hoops_RRSR[0] = _hoops_APSCS->rotation;

			/* _hoops_SSPC _hoops_RPP _hoops_SIPP */
			if (BIT(_hoops_ACCI->flags,_hoops_PRCAP) ||
				_hoops_APSCS->glyph_lsic->points[0].y-_hoops_APSCS->size < _hoops_GPHH.top &&
				_hoops_APSCS->glyph_lsic->points[0].y+_hoops_APSCS->size > _hoops_GPHH.bottom &&
				_hoops_APSCS->glyph_lsic->points[0].x-_hoops_APSCS->size < _hoops_GPHH.right &&
				_hoops_APSCS->glyph_lsic->points[0].x+_hoops_APSCS->size > _hoops_GPHH.left)
				_hoops_APSCS->glyph_lsic->count++;

			if (ANYBIT(_hoops_APSCS->flags, _hoops_GACAP|_hoops_AACAP)) {
				DC_Point	_hoops_GRGSS;

				_hoops_GRGSS.x = points[_hoops_HCIGI].x;
				_hoops_GRGSS.y = points[_hoops_HCIGI].y;
				_hoops_GRGSS.z = points[_hoops_HCIGI].z;

				for (; _hoops_HCIGI>_hoops_PCIGI; _hoops_HCIGI--) {
					_hoops_CHSCS.x = points[_hoops_HCIGI-1].x - _hoops_GRGSS.x;
					_hoops_CHSCS.y = points[_hoops_HCIGI-1].y - _hoops_GRGSS.y;
					_hoops_CHSCS.z = points[_hoops_HCIGI-1].z - _hoops_GRGSS.z;

					length = _hoops_CHSCS.x*_hoops_CHSCS.x + _hoops_CHSCS.y*_hoops_CHSCS.y;
					if (length != 1.0f) length = _hoops_SGIHR (length);

					if (length >= _hoops_CASCS->size) {
						float _hoops_RRGSS, _hoops_ARGSS, _hoops_PRGSS, _hoops_HRGSS, _hoops_IRGSS, _hoops_HPRPA, _hoops_CRGSS, root;

						path.x = points[_hoops_HCIGI-1].x - points[_hoops_HCIGI].x;
						path.y = points[_hoops_HCIGI-1].y - points[_hoops_HCIGI].y;
						path.z = points[_hoops_HCIGI-1].z - points[_hoops_HCIGI].z;

						_hoops_RRGSS = path.x*path.x;
						_hoops_ARGSS = path.y*path.y;

						_hoops_PRGSS = _hoops_RRGSS+_hoops_ARGSS;

						_hoops_HRGSS = _hoops_GRGSS.x - points[_hoops_HCIGI].x;
						_hoops_IRGSS = _hoops_GRGSS.y - points[_hoops_HCIGI].y;

						_hoops_HPRPA = path.x*_hoops_IRGSS - path.y*_hoops_HRGSS;
						_hoops_CRGSS = path.x*_hoops_HRGSS + path.y*_hoops_IRGSS;

						root = _hoops_CASCS->size*_hoops_CASCS->size*_hoops_PRGSS - _hoops_HPRPA*_hoops_HPRPA;

						root = _hoops_SGIHR(root);

						_hoops_CPSCS = (_hoops_CRGSS + root)/_hoops_PRGSS;
						break;
					}
				}
			}
		}
_hoops_SRGSS:

		/* _hoops_PGSA _hoops_RH _hoops_III */
		_hoops_RSIPA = _hoops_SPHH = _hoops_GHHH = 0.0f;

		if (_hoops_SPGPA && offset != 0.0f) {
			float		s, c, _hoops_GAGSS;
			float		_hoops_RAHCR;
			Vector		_hoops_RAGSS;
			bool		_hoops_AAGSS = false;

			path.x = _hoops_PSHCS[count-1].x - _hoops_PSHCS[count-2].x;
			path.y = _hoops_PSHCS[count-1].y - _hoops_PSHCS[count-2].y;
			_hoops_RAGSS.x = _hoops_PSHCS[1].x - _hoops_PSHCS[0].x;
			_hoops_RAGSS.y = _hoops_PSHCS[1].y - _hoops_PSHCS[0].y;
			length = path.x * path.x + path.y * path.y;
			_hoops_GAGSS = _hoops_RAGSS.x*_hoops_RAGSS.x + _hoops_RAGSS.y*_hoops_RAGSS.y;
			if (length != 0.0f && _hoops_GAGSS != 0.0f) {
				length = 1.0f / _hoops_SGIHR (length);
				path.x *= length;
				path.y *= length;

				_hoops_GAGSS = 1.0f / _hoops_SGIHR (_hoops_GAGSS);
				_hoops_RAGSS.x *= _hoops_GAGSS;
				_hoops_RAGSS.y *= _hoops_GAGSS;

				_hoops_RAHCR = _hoops_ISSSR (_hoops_RAGSS.x * path.x + _hoops_RAGSS.y * path.y);

				if (_hoops_RAHCR != 0.0f && Abs(_hoops_RAHCR) < _hoops_HC->_hoops_HCAA) {
					if (path.x * _hoops_RAGSS.y < path.y * _hoops_RAGSS.x)
						_hoops_RAHCR = -_hoops_RAHCR;

					if (BIT(_hoops_RIIPI->flags, _hoops_ARCAP)) 
						_hoops_AAGSS = (Abs(_hoops_RAHCR) > 90.0f && (offset * _hoops_RAHCR >= 0.0f));

					if (!_hoops_AAGSS) {
						_hoops_RICH (0.5f*_hoops_RAHCR, s, c);
						if (c != 0) {
							_hoops_RSIPA = offset * s / c;

							if ((_hoops_RSIPA > 5.0f * Abs(offset))) 
								_hoops_RSIPA = 5.0f * Abs(offset);
						}
						else {
							_hoops_RSIPA = 5.0f * Abs(offset);
						}
					}
				}
			}
		}

		_hoops_SCCCS = _hoops_SASCS;

		/* _hoops_HSGR _hoops_GII _hoops_RSSA _hoops_RHSI _hoops_HPP _hoops_PIRIS _hoops_GPPC */
		points += _hoops_PCIGI;
		count -= (count-1-_hoops_HCIGI);
		count -= _hoops_PCIGI;

		_hoops_SISCS = points[0].z;
		_hoops_HPSCS.z = 0.0f;			/* _hoops_IS _hoops_PAGSS _hoops_HAGSS _hoops_ASRHR */

		while (1) {
			float _hoops_IAGSS;
			float _hoops_CAGSS, _hoops_SAGSS;
			float _hoops_RRCCS = 0.0f;
			bool _hoops_RRRPH = false;
			bool _hoops_GPGSS = false;

			/* _hoops_RGR _hoops_SRIPR _hoops_GGR _hoops_RH _hoops_AGIR _hoops_CAS _hoops_PIRIS _hoops_HSPP _hoops_PAR _hoops_RSGR _hoops_GPPC _hoops_RHSI _hoops_HCR _hoops_RSSA */
			if (!_hoops_HISCS && --count <= 0)
				goto _hoops_RPGSS;

			if (_hoops_HISCS) {
				_hoops_PPSCS = *_hoops_HISCS;
				_hoops_HPSCS = *_hoops_IISCS;
				_hoops_GHSCS = _hoops_RSIPA = 0.0f;
				_hoops_HISCS = null;
			}
			else if (_hoops_IISCS) {
				_hoops_PPSCS = *_hoops_IISCS;
				_hoops_HPSCS = points[1];
				_hoops_GPGSS = true;
				_hoops_IISCS = null;
			}
			else {
				_hoops_PPSCS = points[0];
				_hoops_HPSCS = points[1];
			}

			if (_hoops_IISCS) {
				path.x = _hoops_HPSCS.x - _hoops_PPSCS.x;
				path.y = _hoops_HPSCS.y - _hoops_PPSCS.y;
				path.z = _hoops_HPSCS.z - _hoops_PPSCS.z;
			}
			else {
				path.x = points[1].x - points[0].x;
				path.y = points[1].y - points[0].y;
				path.z = points[1].z - points[0].z;
			}

			/* _hoops_IIS'_hoops_GRI _hoops_HAR _hoops_HSSC _hoops_PSAP _hoops_RH _hoops_APGSS _hoops_ARI */
			if (path.z > nr->transform_rendition->_hoops_PCHH)
				path.z = nr->transform_rendition->_hoops_PCHH;

			_hoops_IAGSS = length = factor = _hoops_SGIHR (path.x * path.x + path.y * path.y);

			/* _hoops_CCPH _hoops_RPP _hoops_SIGR */
			if (_hoops_IPSCS != 0.0f) {
				_hoops_PPSCS.x += path.x * _hoops_IPSCS;
				_hoops_PPSCS.y += path.y * _hoops_IPSCS;
				_hoops_PPSCS.z += path.z * _hoops_IPSCS;
				_hoops_IPSCS = 0.0f;
				_hoops_RRRPH = true;
			}

			if (count == 1 && _hoops_CPSCS != 0.0f) {
				_hoops_HPSCS.x -= path.x * _hoops_CPSCS;
				_hoops_HPSCS.y -= path.y * _hoops_CPSCS;
				_hoops_HPSCS.z -= path.z * _hoops_CPSCS;
				_hoops_CPSCS = 0.0f;
				_hoops_RRRPH = true;
			}

			if (_hoops_RRRPH) {
				path.x = _hoops_HPSCS.x - _hoops_PPSCS.x;
				path.y = _hoops_HPSCS.y - _hoops_PPSCS.y;
				path.z = _hoops_HPSCS.z - _hoops_PPSCS.z;
				if (path.z > nr->transform_rendition->_hoops_PCHH)
					path.z = nr->transform_rendition->_hoops_PCHH;
				length = factor = _hoops_SGIHR (path.x * path.x + path.y * path.y);
			}

			if (length != 0.0f) {
				factor = 1.0f / factor;
				path.x *= factor;
				path.y *= factor;
				path.z *= factor;
			}

			/* _hoops_HIHA _hoops_IH _hoops_AII */
			if (BIT(_hoops_RIIPI->flags, LSF_OFFSET) && !_hoops_IISCS) {
				bool _hoops_AAGSS = false;
				float _hoops_RAHCR = 0.0f;

				_hoops_SPHH = path.y*offset;
				_hoops_GHHH = -path.x*offset;

 				if (_hoops_GPGSS) {
					//_hoops_PPGSS = _hoops_RCPP;
				}
				else {
					_hoops_PPSCS.x += _hoops_SPHH + path.x * -_hoops_RSIPA;
					_hoops_PPSCS.y += _hoops_GHHH + path.y * -_hoops_RSIPA;
				}

				_hoops_HPSCS.x += _hoops_SPHH;
				_hoops_HPSCS.y += _hoops_GHHH;

				path.z *= length;
				length += _hoops_RSIPA;
				path.z /= length;

				/* _hoops_SSH _hoops_ASSCS */
				if (length < 0.00001f || length > -0.00001f)
					path.z += (points[0].z - _hoops_SISCS)/length;
				else		/* _hoops_HRPHR */
					path.z = 0.0f;
				/* _hoops_ARP _hoops_HSPP _hoops_PPSR _hoops_SSH-_hoops_PIRA _hoops_IS _hoops_RH _hoops_CGHI _hoops_SPR _hoops_HIS _hoops_SSIA _hoops_PCPC */
				_hoops_PPSCS.z = _hoops_SISCS;

				/*_hoops_RPGH _hoops_SPS _hoops_SRPA*/
				_hoops_GHSCS = _hoops_RSIPA;
				_hoops_RSIPA = 0.0f;

				if (count > 1 || _hoops_SPGPA) {
					float		s, c, _hoops_GAGSS;
					Vector		_hoops_RAGSS;

					if (count > 1) {
						_hoops_RAGSS.x = points[2].x - points[1].x;
						_hoops_RAGSS.y = points[2].y - points[1].y;
						_hoops_RAGSS.z = points[2].z - points[1].z;
					}
					else {
						_hoops_RAGSS.x = _hoops_PSHCS[1].x - _hoops_PSHCS[0].x;
						_hoops_RAGSS.y = _hoops_PSHCS[1].y - _hoops_PSHCS[0].y;
						_hoops_RAGSS.z = _hoops_PSHCS[1].z - _hoops_PSHCS[0].z;
					}
					if (_hoops_RAGSS.z > nr->transform_rendition->_hoops_PCHH)
						_hoops_RAGSS.z = nr->transform_rendition->_hoops_PCHH;

					_hoops_GAGSS = factor = _hoops_SGIHR (_hoops_RAGSS.x*_hoops_RAGSS.x + _hoops_RAGSS.y*_hoops_RAGSS.y);
					if (factor > 0.0f) {
						if (factor != 1.0f) {
							factor = 1.0f/factor;
							_hoops_RAGSS.x *= factor;
							_hoops_RAGSS.y *= factor;
							_hoops_RAGSS.z *= factor;
						}

						_hoops_RAHCR = _hoops_ISSSR (_hoops_RAGSS.x * path.x + _hoops_RAGSS.y * path.y);

						if (_hoops_RAHCR > 178.0f)
							_hoops_RAHCR = 178.0f;
						if (_hoops_RAHCR < -178.0f)
							_hoops_RAHCR = -178.0f;
						if (_hoops_RAHCR != 0.0f) {
							if (path.x * _hoops_RAGSS.y < path.y * _hoops_RAGSS.x)
								_hoops_RAHCR = -_hoops_RAHCR;

							if (BIT(_hoops_RIIPI->flags, _hoops_ARCAP))
								_hoops_AAGSS = (Abs(_hoops_RAHCR) > 90.0f && (offset * _hoops_RAHCR >= 0.0f));

							_hoops_RICH (0.5f*_hoops_RAHCR, s, c);
							if (c != 0)
								_hoops_RSIPA = offset * s / c;

							if (!_hoops_AAGSS && (_hoops_RSIPA > 4.0f * Abs(offset))) {
								_hoops_AAGSS = true;
							}
						}
					}

					if (_hoops_AAGSS && length > 0.0f) {
						_hoops_HISCS = &_hoops_CISCS[0];
						_hoops_IISCS = &_hoops_CISCS[1];

						/* _hoops_ASAC _hoops_SRS _hoops_HPGSS _hoops_PPSR */
						_hoops_HISCS->x = _hoops_HPSCS.x;
						_hoops_HISCS->y = _hoops_HPSCS.y;
						_hoops_HISCS->z = _hoops_HPSCS.z;

						/* _hoops_ASAC _hoops_GIAP _hoops_HPGSS _hoops_PPSR */
						if (_hoops_RAHCR < 178.0f && _hoops_RAHCR > -178.0f) {
							_hoops_IISCS->x = _hoops_HPSCS.x + path.x * _hoops_RSIPA + _hoops_RAGSS.x * _hoops_RSIPA;
							_hoops_IISCS->y = _hoops_HPSCS.y + path.y * _hoops_RSIPA + _hoops_RAGSS.y * _hoops_RSIPA;
							_hoops_IISCS->z = _hoops_HPSCS.z + path.z * _hoops_RSIPA - _hoops_RAGSS.z * _hoops_RSIPA;
						}
						else {
							Vector		_hoops_IPGSS;

							_hoops_IPGSS.x = points[1].x - _hoops_HPSCS.x;
							_hoops_IPGSS.y = points[1].y - _hoops_HPSCS.y;
							_hoops_IPGSS.z = points[1].z - _hoops_HPSCS.z;
							factor = _hoops_SGIHR (_hoops_IPGSS.x*_hoops_IPGSS.x + _hoops_IPGSS.y*_hoops_IPGSS.y);
							if (factor > 0.0f) {
								if (factor != 1.0f) {
									factor = 1.0f/factor;
									_hoops_IPGSS.x *= factor;
									_hoops_IPGSS.y *= factor;
									_hoops_IPGSS.z *= factor;
								}
							}

							_hoops_IISCS->x = _hoops_HPSCS.x + _hoops_IPGSS.x * Abs(offset) * 2.0f;
							_hoops_IISCS->y = _hoops_HPSCS.y + _hoops_IPGSS.y * Abs(offset) * 2.0f;
							_hoops_IISCS->z = _hoops_HPSCS.z + _hoops_IPGSS.z * Abs(offset) * 2.0f;
						}

						_hoops_CGSCS(nr, _hoops_ACCI, *_hoops_IISCS);
						_hoops_RSIPA =  0.0f;
					}
				}

				if (length + _hoops_RSIPA <= 0.0f) {
					length += _hoops_RSIPA;
					// _hoops_RSAIP _hoops_IS _hoops_GRHP _hoops_ISCP _hoops_GRAHA _hoops_GGSP _hoops_GAR _hoops_SCH _hoops_SCRHA _hoops_RH _hoops_CGHC
					_hoops_IAGSS = _hoops_GHSCS = 0.0f;
					/* _hoops_PGIPR _hoops_CHIAR _hoops_III _hoops_SGHC _hoops_CCA _hoops_GRAA-_hoops_HICAA _hoops_GAPHS _hoops_HGCR _hoops_SPRSH 
					* _hoops_CRGR _hoops_IRS _hoops_CPPPR _hoops_ICHRR _hoops_III.  _hoops_SR _hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_GPIGP _hoops_SGGR _hoops_RH _hoops_SRPA _hoops_IH _hoops_AGCR
					*/
					if ((BIT(_hoops_ACCI->flags,_hoops_PRCAP) && _hoops_RAHCR < 177.0f) || Abs(_hoops_RAHCR) >= 177.0f)
						_hoops_RSIPA = 0.0f;
				}
				else if (!_hoops_AAGSS || _hoops_RAHCR * offset < 0.0f) {
					_hoops_HPSCS.x += path.x * _hoops_RSIPA;
					_hoops_HPSCS.y += path.y * _hoops_RSIPA;

					path.z *= length;
					length += _hoops_RSIPA;
					path.z /= length;
				}
			}

			/* _hoops_RGHH _hoops_IRGP _hoops_RPHH */
			if (_hoops_RPSCS && count > 1 && length > 0.0f) {
				Vector		_hoops_RAGSS;
				float		_hoops_GAGSS;

				if (_hoops_RPSCS->glyph_lsic->count == _hoops_RPSCS->glyph_lsic->_hoops_SAGCA)
					_hoops_PSCCS(nr, _hoops_RPSCS->glyph_lsic, 1, 1);

				if (!BIT(_hoops_RPSCS->flags, _hoops_RACAP)) {
					_hoops_RAGSS.x = points[2].x - points[1].x;
					_hoops_RAGSS.y = points[2].y - points[1].y;
			
					_hoops_GAGSS = _hoops_RAGSS.x*_hoops_RAGSS.x + _hoops_RAGSS.y*_hoops_RAGSS.y;
					/*_hoops_ASIGA _hoops_RPP (_hoops_CPGSS != 0.0f)*/ 
					if (_hoops_GAGSS != 1.0f) {
						_hoops_GAGSS = 1.0f/_hoops_SGIHR (_hoops_GAGSS);
						_hoops_RAGSS.x *= _hoops_GAGSS;
						_hoops_RAGSS.y *= _hoops_GAGSS;
					}

					_hoops_RPSCS->glyph_lsic->_hoops_RRSR[_hoops_RPSCS->glyph_lsic->count] = 
						_hoops_AGGGA(path.y+_hoops_RAGSS.y, path.x+_hoops_RAGSS.x) + 
							_hoops_RPSCS->rotation;
				}
				else
					_hoops_RPSCS->glyph_lsic->_hoops_RRSR[_hoops_RPSCS->glyph_lsic->count] = _hoops_RPSCS->rotation;

				_hoops_RPSCS->glyph_lsic->points[_hoops_RPSCS->glyph_lsic->count] = _hoops_HPSCS;

				/* _hoops_SSPC _hoops_RPP _hoops_SIPP */
				if (BIT(_hoops_ACCI->flags,_hoops_PRCAP) ||
					_hoops_RPSCS->glyph_lsic->points[_hoops_RPSCS->glyph_lsic->count].y-_hoops_RPSCS->size < _hoops_GPHH.top &&
					_hoops_RPSCS->glyph_lsic->points[_hoops_RPSCS->glyph_lsic->count].y+_hoops_RPSCS->size > _hoops_GPHH.bottom &&
					_hoops_RPSCS->glyph_lsic->points[_hoops_RPSCS->glyph_lsic->count].x-_hoops_RPSCS->size < _hoops_GPHH.right &&
					_hoops_RPSCS->glyph_lsic->points[_hoops_RPSCS->glyph_lsic->count].x+_hoops_RPSCS->size > _hoops_GPHH.left)
					_hoops_RPSCS->glyph_lsic->count++;
			}

			_hoops_IHSCS = (weight > 1.0f && length > 0.0f && (count > 1 || (count == 1 && _hoops_SPGPA)));


			/* _hoops_AA _hoops_RIR _hoops_III _hoops_CAGH _hoops_ASSCS */
			if (BIT(_hoops_RIIPI->flags, LSF_SEGMENTED)) {
				_hoops_IIIPI = 0.0f;
				_hoops_SCCCS = _hoops_SASCS;
				while (1) {
					if (BIT(_hoops_SCCCS->flags, _hoops_CACAP)) {
						float _hoops_SHIHP = length - _hoops_SHSCS;
						_hoops_SHIHP /= _hoops_AISCS;
						_hoops_SCCCS->size = _hoops_SHIHP;
					}
					else if (BIT(_hoops_SCCCS->flags, _hoops_SACAP))
						_hoops_SCCCS->size = HD_Compute_Generic_Size (nr, _hoops_SCCCS->_hoops_ACCCS, GSU_PERCENT, length, false, 0, true);

					if (_hoops_SCCCS->size < 1.0f)
						_hoops_SCCCS->size = 1.0f;
					if ((_hoops_SCCCS = _hoops_SCCCS->next) == _hoops_SASCS) break;
				}
	
				if (ANYBIT(_hoops_RIIPI->flags, LSF_FIT_CENTER|LSF_FIT_STRETCH)) {
					float _hoops_ISSCS = 0.0f;
					float glyph_inline_total_lengths = 0.0f;
					
					_hoops_SCCCS = _hoops_SASCS;
					while (1) {
						if (_hoops_SCCCS->mode != _hoops_AICCS) {
							_hoops_ISSCS += _hoops_SCCCS->size;
							if (BIT(_hoops_SCCCS->flags, _hoops_AACAP))
								glyph_inline_total_lengths += _hoops_SCCCS->size;
						}
						if ((_hoops_SCCCS = _hoops_SCCCS->next) == _hoops_SASCS) break;
					}

					if (BIT(_hoops_RIIPI->flags, LSF_FIT_CENTER)) {
						float _hoops_CSSCS, _hoops_SSSCS, _hoops_GGGSS;

						_hoops_CSSCS = _hoops_ISSCS-_hoops_SASCS->size;
				
						if (length>_hoops_CSSCS) {
							_hoops_SSSCS = length-_hoops_CSSCS;
							_hoops_SSSCS *= 0.5f;
							_hoops_SSSCS = fmod(_hoops_SSSCS, _hoops_ISSCS);
							_hoops_SSSCS = _hoops_SASCS->size-_hoops_SSSCS;

							_hoops_GGGSS = length-_hoops_SASCS->size;
							_hoops_GGGSS *= 0.5f;
							_hoops_GGGSS = fmod(_hoops_GGGSS, _hoops_ISSCS);
							_hoops_GGGSS = _hoops_ISSCS-_hoops_GGGSS;

							if (_hoops_SSSCS < 0)
								_hoops_IIIPI = -_hoops_GGGSS;
							else if (_hoops_GGGSS < 0)
								_hoops_IIIPI = -_hoops_SSSCS;
							else if (_hoops_SSSCS < _hoops_GGGSS) 
								_hoops_IIIPI = -_hoops_SSSCS;
							else
								_hoops_IIIPI = -_hoops_GGGSS;
						}

					}
					else {	/* _hoops_RGGSS */
						float _hoops_AGGSS, _hoops_PGGSS;
						int _hoops_HGGSS;

						_hoops_HGGSS = (int)(length/_hoops_ISSCS+0.5f);

						if (_hoops_HGGSS == 0) 
							_hoops_HGGSS = 1;

						_hoops_AGGSS = length/((float)_hoops_HGGSS*_hoops_ISSCS);

						if (_hoops_ISSCS != glyph_inline_total_lengths) {

							_hoops_PGGSS = (_hoops_AGGSS*_hoops_ISSCS-glyph_inline_total_lengths)/
											(_hoops_ISSCS-glyph_inline_total_lengths);

							_hoops_SCCCS = _hoops_SASCS;
							while (1) {
								if (_hoops_SCCCS->mode != _hoops_AICCS &&
									!BIT(_hoops_SCCCS->flags, _hoops_AACAP)) {
									
									_hoops_SCCCS->size *= _hoops_PGGSS;
									if (_hoops_SCCCS->size<1)
										_hoops_SCCCS->size=1;
								}
								if ((_hoops_SCCCS = _hoops_SCCCS->next) == _hoops_SASCS) break;
							}
						
							_hoops_IIIPI = -0.5f * _hoops_SASCS->size;
						}
						else {
							_hoops_SCCCS = _hoops_SASCS;
							while (1) {
								if (_hoops_SCCCS->mode != _hoops_AICCS) {
									
									_hoops_SCCCS->size *= _hoops_AGGSS;
									if (_hoops_SCCCS->size<1)
										_hoops_SCCCS->size=1;
								}
								if ((_hoops_SCCCS = _hoops_SCCCS->next) == _hoops_SASCS) break;
							}
						}
					}
				}
			}

			_hoops_IIIPI += _hoops_SPSCS;


			/* _hoops_III _hoops_CIHH _hoops_CSGA _hoops_HSPP _hoops_PPR _hoops_RSGR _hoops_PGRAR */
			if (!BIT(_hoops_ACCI->flags,_hoops_PRCAP) &&
				(_hoops_PPSCS.y > _hoops_GPHH.top || _hoops_PPSCS.y < _hoops_GPHH.bottom ||
				_hoops_PPSCS.x > _hoops_GPHH.right || _hoops_PPSCS.x < _hoops_GPHH.left ||
				_hoops_HPSCS.y > _hoops_GPHH.top || _hoops_HPSCS.y < _hoops_GPHH.bottom ||
				_hoops_HPSCS.x > _hoops_GPHH.right || _hoops_HPSCS.x < _hoops_GPHH.left)) {

				_hoops_GPPA const *	_hoops_GRCPR;
				bool							_hoops_GCGGA = false;
				float							dx, _hoops_CRRAR, _hoops_AAAC, t;
				float							_hoops_CIGGA = 0.0f, _hoops_SIGGA = 1.0f;

				if (!_hoops_HASCS)
					_hoops_HASCS = HD_Create_Hard_Clip_Cuts (nr, &_hoops_GPHH, null, 0);

				dx = _hoops_HPSCS.x - _hoops_PPSCS.x;
				_hoops_CRRAR = _hoops_HPSCS.y - _hoops_PPSCS.y;
				_hoops_AAAC = _hoops_HPSCS.z - _hoops_PPSCS.z;

				_hoops_GRCPR = _hoops_HASCS;
				while (_hoops_GRCPR) {
					float	_hoops_RCGGA, _hoops_CHGGA;

					_hoops_RCGGA =  _hoops_GRCPR->_hoops_SPPA.a * _hoops_PPSCS.x +
								_hoops_GRCPR->_hoops_SPPA.b * _hoops_PPSCS.y +
								 _hoops_GRCPR->_hoops_SPPA.c * _hoops_PPSCS.z +
								  _hoops_GRCPR->_hoops_SPPA.d;

					_hoops_CHGGA = _hoops_GRCPR->_hoops_SPPA.a * _hoops_HPSCS.x +
								_hoops_GRCPR->_hoops_SPPA.b * _hoops_HPSCS.y +
								 _hoops_GRCPR->_hoops_SPPA.c * _hoops_HPSCS.z +
								  _hoops_GRCPR->_hoops_SPPA.d;

					if (_hoops_RCGGA > 0.0f) {
						if (_hoops_CHGGA > 0.0f) {
							/* _hoops_GIPR _hoops_SIPP _hoops_RGR _hoops_PPAP */
							_hoops_CIGGA = 1.0f;
							_hoops_SIGGA = 0.0f;
							break;
						}
						else {
							/* _hoops_HSPH _hoops_ACGGA */
							t = -_hoops_RCGGA / (
								_hoops_GRCPR->_hoops_SPPA.a * dx + 
								 _hoops_GRCPR->_hoops_SPPA.b * _hoops_CRRAR +
								  _hoops_GRCPR->_hoops_SPPA.c * _hoops_AAAC);

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
							t = -_hoops_RCGGA / (
								_hoops_GRCPR->_hoops_SPPA.a * dx + 
								 _hoops_GRCPR->_hoops_SPPA.b * _hoops_CRRAR +
								  _hoops_GRCPR->_hoops_SPPA.c * _hoops_AAAC);

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
					_hoops_GRCPR = _hoops_GRCPR->next;
				}

				if (_hoops_RRCCS == 0.0f) {
					_hoops_RCCCS *		_hoops_SPGSS = _hoops_SASCS;

					while (1) {
						if (_hoops_SPGSS->mode != _hoops_AICCS)
							_hoops_RRCCS += _hoops_SPGSS->size;

						if ((_hoops_SPGSS = _hoops_SPGSS->next) == _hoops_SASCS)
							break;
					}
				}

				_hoops_SAGSS = length * _hoops_CIGGA - _hoops_RRCCS;
				if (_hoops_SAGSS < 0.0f)
					_hoops_SAGSS = 0.0f;
				_hoops_CAGSS = _hoops_SAGSS + length * (_hoops_SIGGA-_hoops_CIGGA) + 2*_hoops_RRCCS;
			}
			else {
				/* _hoops_PSP _hoops_HSPP _hoops_PAR _hoops_RSGR _hoops_PGRAR */
				_hoops_SAGSS	= -10000.0f;
				_hoops_CAGSS = length + 10000.0f;
			}

			/* _hoops_HA _hoops_GHGSS _hoops_RH _hoops_HSGP */
			_hoops_GSGGA[0].x = _hoops_PPSCS.x;
			_hoops_GSGGA[0].y = _hoops_PPSCS.y;
			_hoops_GSGGA[0].z = _hoops_PPSCS.z;

			while (1) {
				switch (_hoops_SCCCS->mode) {
					case _hoops_SHCCS:
					case _hoops_GICCS:
					case _hoops_RICCS: {
						_hoops_IIIPI += _hoops_SCCCS->size;
					}	break;
					case _hoops_AICCS:break;
				}
		
				if (_hoops_IIIPI < 0) {
					_hoops_HHSCS = false;
					_hoops_SCCCS = _hoops_SCCCS->next;
					continue;
				}
				
				if (_hoops_SCCCS->mode == _hoops_AICCS) {
					if (_hoops_SCCCS->glyph_lsic->count == _hoops_SCCCS->glyph_lsic->_hoops_SAGCA)
						_hoops_PSCCS(nr, _hoops_SCCCS->glyph_lsic, 1, 1);

					if (!BIT(_hoops_SCCCS->flags, _hoops_RACAP))
						_hoops_SCCCS->glyph_lsic->_hoops_RRSR[_hoops_SCCCS->glyph_lsic->count] =	 
							_hoops_AGGGA(path.y, path.x) + _hoops_SCCCS->rotation;
					else
						_hoops_SCCCS->glyph_lsic->_hoops_RRSR[_hoops_SCCCS->glyph_lsic->count] = _hoops_SCCCS->rotation;

					_hoops_SCCCS->glyph_lsic->points[_hoops_SCCCS->glyph_lsic->count] = _hoops_GSGGA[0];
					
					/* _hoops_SSPC _hoops_RPP _hoops_SIPP */
					if (BIT(_hoops_ACCI->flags,_hoops_PRCAP) ||
						(_hoops_SCCCS->glyph_lsic->points[_hoops_SCCCS->glyph_lsic->count].y-_hoops_SCCCS->size < _hoops_GPHH.top &&
						_hoops_SCCCS->glyph_lsic->points[_hoops_SCCCS->glyph_lsic->count].y+_hoops_SCCCS->size > _hoops_GPHH.bottom &&
						_hoops_SCCCS->glyph_lsic->points[_hoops_SCCCS->glyph_lsic->count].x-_hoops_SCCCS->size < _hoops_GPHH.right &&
						_hoops_SCCCS->glyph_lsic->points[_hoops_SCCCS->glyph_lsic->count].x+_hoops_SCCCS->size > _hoops_GPHH.left))
						_hoops_SCCCS->glyph_lsic->count++;

					_hoops_HHSCS = false;
					_hoops_SCCCS = _hoops_SCCCS->next;
					continue;
				}

				/* _hoops_RGHH _hoops_HSPP _hoops_RIRR */
				if (_hoops_PHSCS && 
					weight > 1.0f && !_hoops_SPGPA && 
					(_hoops_SGSCS->style & LCAP_START_MASK) != LCAP_BUTT &&
					_hoops_SCCCS->mode != _hoops_RICCS &&
					_hoops_IIIPI >= _hoops_SAGSS) {

					if ((_hoops_SGSCS->style & LCAP_START_MASK) == LCAP_ROUND)
						_hoops_PGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_PPSCS, path, radius);
					else if ((_hoops_SGSCS->style & LCAP_START_MASK) == LCAP_TRIANGLE)
						_hoops_IGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_PPSCS, path, radius);
					else /*_hoops_AIAGS*/
						_hoops_HGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_PPSCS, path, radius);
				}
				_hoops_PHSCS = false;


				if (_hoops_IIIPI < length) {
					if (_hoops_IIIPI == 0.0f) {
						_hoops_HHSCS=false;
						_hoops_SCCCS = _hoops_SCCCS->next;
						continue;
					}

					if (_hoops_IIIPI >= _hoops_SAGSS &&
						_hoops_IIIPI <= _hoops_CAGSS) {

						switch (_hoops_SCCCS->mode) {

							case _hoops_SHCCS: {
								_hoops_GSGGA[1].x = _hoops_PPSCS.x + _hoops_IIIPI * path.x;
								_hoops_GSGGA[1].y = _hoops_PPSCS.y + _hoops_IIIPI * path.y;
								_hoops_GSGGA[1].z = _hoops_PPSCS.z + _hoops_IIIPI * path.z;
								_hoops_CGSCS(nr, _hoops_ACCI, _hoops_GSGGA[1]);

								_hoops_SSCCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_CICCS, _hoops_GSGGA);
								_hoops_GSGGA[0] = _hoops_GSGGA[1];
							}	break;

							case _hoops_GICCS: {
								_hoops_GSGGA[1].x = _hoops_PPSCS.x + _hoops_IIIPI * path.x;
								_hoops_GSGGA[1].y = _hoops_PPSCS.y + _hoops_IIIPI * path.y;
								_hoops_GSGGA[1].z = _hoops_PPSCS.z + _hoops_IIIPI * path.z;
								_hoops_CGSCS(nr, _hoops_ACCI, _hoops_GSGGA[1]);

								if (_hoops_SCCCS->size == 1)
									_hoops_GGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_CICCS, _hoops_GSGGA, path, (length >= 1.0f)?radius:0.0f);
								else if (_hoops_GSCCS)
									_hoops_SSCCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_GCCCS, _hoops_GSGGA);
								else
									_hoops_RGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA, path, radius);

								switch (_hoops_SGSCS->style & LPAT_MASK) {
									case LPAT_ROUND:
										if (!_hoops_HHSCS)
											_hoops_PGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[0], path, radius);
										_hoops_PGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[1], path, -radius);
									break;
									case LPAT_SQUARE:
										if (!_hoops_HHSCS)
											_hoops_HGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[0], path, radius);
										_hoops_HGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[1], path, -radius);	
									break;
									case LPAT_TRIANGLE:
										if (!_hoops_HHSCS)
											_hoops_IGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[0], path, radius);
										_hoops_IGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[1], path, -radius);
									break;
									case 0: break;
									default:ASSERT(0);break;
								}

								_hoops_GSGGA[0] = _hoops_GSGGA[1];
							}	break;

							case _hoops_RICCS: {
								_hoops_GSGGA[0].x = _hoops_PPSCS.x + _hoops_IIIPI * path.x;
								_hoops_GSGGA[0].y = _hoops_PPSCS.y + _hoops_IIIPI * path.y;
								_hoops_GSGGA[0].z = _hoops_PPSCS.z + _hoops_IIIPI * path.z;
								_hoops_CGSCS(nr, _hoops_ACCI, _hoops_GSGGA[0]);
							}	break;

							case _hoops_AICCS: break;
						}
					}
					else {
						if (_hoops_IIIPI < _hoops_SAGSS) {
							int _hoops_RCAI = (int)((_hoops_SAGSS-_hoops_IIIPI)/_hoops_RRCCS);
							
							_hoops_IIIPI += _hoops_RCAI*_hoops_RRCCS;
						}
						else if (_hoops_IIIPI > _hoops_CAGSS) {
							int _hoops_RCAI = (int)((length-_hoops_IIIPI)/_hoops_RRCCS);
							
							_hoops_IIIPI += _hoops_RCAI*_hoops_RRCCS;
						}

						_hoops_GSGGA[0].x = _hoops_PPSCS.x + _hoops_IIIPI * path.x;
						_hoops_GSGGA[0].y = _hoops_PPSCS.y + _hoops_IIIPI * path.y;
						_hoops_GSGGA[0].z = _hoops_PPSCS.z + _hoops_IIIPI * path.z;
						_hoops_CGSCS(nr, _hoops_ACCI, _hoops_GSGGA[0]);
					}

					_hoops_HHSCS = false;
					_hoops_SCCCS = _hoops_SCCCS->next;
					continue;
				}

				if (length > 0.0f && length <= _hoops_CAGSS) {

					switch (_hoops_SCCCS->mode) {

						case _hoops_SHCCS: {
							_hoops_GSGGA[1] = _hoops_HPSCS;
							_hoops_SSCCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_CICCS, _hoops_GSGGA);
						}	break;

						case _hoops_GICCS: {
							_hoops_GSGGA[1] = _hoops_HPSCS;

							if (_hoops_SCCCS->size == 1)
								_hoops_GGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_CICCS, _hoops_GSGGA, path, (length >= 1.0f)?radius:0.0f);
							else if (_hoops_GSCCS)
								_hoops_SSCCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_GCCCS, _hoops_GSGGA);
							else
								_hoops_RGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA, path, radius);

							switch (_hoops_SGSCS->style & LPAT_MASK) {
								case LPAT_ROUND:
									if (!_hoops_HHSCS)
										_hoops_PGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[0], path, radius);
									if (count != 1)
										_hoops_PGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[1], path, -radius);
								break;
								case LPAT_SQUARE:
									if (!_hoops_HHSCS)
										_hoops_HGSCS(nr ,_hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[0], path, radius);
									if (count != 1)
										_hoops_HGSCS(nr ,_hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[1], path, -radius);	
								break;
								case LPAT_TRIANGLE:
									if (!_hoops_HHSCS)
										_hoops_IGSCS(nr ,_hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[0], path, radius);
									if (count != 1)
										_hoops_IGSCS(nr ,_hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_GSGGA[1], path, -radius);
								break;
								case 0: break;
								default:ASSERT(0);break;
							}

							_hoops_GSGGA[0] = _hoops_GSGGA[1];
						}	break;

						case _hoops_RICCS: break;
						case _hoops_AICCS: break;
					}

					/* _hoops_RGHH _hoops_RSGR _hoops_RIRR */
					if (weight > 1.0f && 
						count == 1 && !_hoops_SPGPA &&
						(_hoops_SGSCS->style & LCAP_MASK) != LCAP_BUTT &&
						_hoops_SCCCS->mode != _hoops_RICCS) {

						int _hoops_RHGSS = _hoops_SGSCS->style & LCAP_MASK;
	
						if (_hoops_RHGSS & LCAP_END_MASK)
							_hoops_RHGSS=(_hoops_RHGSS>>LCAP_END_SHIFT);

						if (_hoops_RHGSS == LCAP_ROUND)
							_hoops_PGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_HPSCS, path, -radius);
						else if (_hoops_RHGSS== LCAP_TRIANGLE)
							_hoops_IGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_HPSCS, path, -radius);
						else if (_hoops_RHGSS== LCAP_SQUARE)
							_hoops_HGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_HPSCS, path, -radius);
					}

					/* _hoops_RGHH _hoops_AIRR */
					if (BIT(_hoops_RIIPI->flags, LSF_SEGMENTED)) {
						_hoops_SCCCS = _hoops_SASCS;
						/* _hoops_PAISR _hoops_CAGH _hoops_IRPCI */
						if (BIT(_hoops_RIIPI->flags, LSF_FIT_STRETCH)) {
							do _hoops_SCCCS->size = _hoops_SCCCS->_hoops_AHHRI;
							while ((_hoops_SCCCS = _hoops_SCCCS->next) != _hoops_SASCS);
						}
					}


					if (_hoops_IHSCS && _hoops_SCCCS->mode != _hoops_RICCS) {
						float					_hoops_RAHCR, _hoops_GAGSS;
						Vector					_hoops_RAGSS;
						DC_Point const *		_hoops_AHGSS;
						float					s, c;

						if (count == 1) {
							_hoops_RAGSS.x = _hoops_PSHCS[1].x - _hoops_PSHCS[0].x;
							_hoops_RAGSS.y = _hoops_PSHCS[1].y - _hoops_PSHCS[0].y;
							_hoops_RAGSS.z = _hoops_PSHCS[1].z - _hoops_PSHCS[0].z;
							_hoops_AHGSS = &_hoops_PSHCS[1];
						}
						else {
							_hoops_RAGSS.x = points[2].x - points[1].x;
							_hoops_RAGSS.y = points[2].y - points[1].y;
							_hoops_RAGSS.z = points[2].z - points[1].z;
							_hoops_AHGSS = &points[2];
						}

						_hoops_GAGSS = _hoops_RAGSS.x*_hoops_RAGSS.x + _hoops_RAGSS.y*_hoops_RAGSS.y;

						if (_hoops_GAGSS == 0.0f) 
							goto _hoops_PHGSS;
				
						if (_hoops_GAGSS != 1.0f) {
							float		_hoops_HHGSS;
							
							_hoops_GAGSS = _hoops_SGIHR (_hoops_GAGSS);
							_hoops_HHGSS = 1.0f/_hoops_GAGSS;
							_hoops_RAGSS.x *= _hoops_HHGSS;
							_hoops_RAGSS.y *= _hoops_HHGSS;
						}

						_hoops_RAHCR = _hoops_ISSSR (_hoops_RAGSS.x * path.x + _hoops_RAGSS.y * path.y);

						if (path.x * _hoops_RAGSS.y < path.y * _hoops_RAGSS.x) 
							_hoops_RAHCR = -_hoops_RAHCR;

						if (_hoops_RAHCR == 0.0f) goto _hoops_PHGSS;

						switch (_hoops_SGSCS->style & LJOIN_MASK) {

							case LJOIN_ROUND: {

								_hoops_AGSCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, _hoops_HPSCS, path, _hoops_RAGSS, _hoops_RAHCR, radius);
							}	break;

							case LJOIN_MITER:
							case LJOIN_BEVEL: {

								if ((_hoops_SCCCS->_hoops_CSC->_hoops_SICCS->count+2)*3 >= _hoops_SCCCS->_hoops_CSC->_hoops_SICCS->_hoops_SAGCA) 
									_hoops_PSCCS(nr, _hoops_SCCCS->_hoops_CSC->_hoops_SICCS, 2, 3);
								
								DC_Point *	pts = _hoops_SCCCS->_hoops_CSC->_hoops_SICCS->_hoops_ASPS;

								pts->x = _hoops_HPSCS.x;
								pts->y = _hoops_HPSCS.y;
								pts->z = _hoops_HPSCS.z;
								pts++;

								if (_hoops_RAHCR < 0.0f) {
									pts->x = _hoops_HPSCS.x - path.y * radius;
									pts->y = _hoops_HPSCS.y + path.x * radius;
									pts->z = _hoops_HPSCS.z;
								}
								else {
									pts->x = _hoops_HPSCS.x + path.y * radius;
									pts->y = _hoops_HPSCS.y - path.x * radius;
									pts->z = _hoops_HPSCS.z;
								}
								pts++;

								if ((_hoops_SGSCS->style & LJOIN_MASK) == LJOIN_MITER &&
									Abs (_hoops_RAHCR) <= _hoops_SGSCS->_hoops_HCAA) {
									float		_hoops_CRIPA;

									_hoops_RICH (0.5f*_hoops_RAHCR, s, c);
									_hoops_CRIPA = radius * s / c;

									if (_hoops_RAHCR < 0.0f) {
										pts->x = _hoops_HPSCS.x - path.y * radius - path.x * _hoops_CRIPA;
										pts->y = _hoops_HPSCS.y + path.x * radius - path.y * _hoops_CRIPA;
										pts->z = _hoops_HPSCS.z;
									}
									else {
										pts->x = _hoops_HPSCS.x + path.y * radius + path.x * _hoops_CRIPA;
										pts->y = _hoops_HPSCS.y - path.x * radius + path.y * _hoops_CRIPA;
										pts->z = _hoops_HPSCS.z;
									}
									pts++;

									_hoops_SCCCS->_hoops_CSC->_hoops_SICCS->_hoops_ASPS += 3;
									_hoops_SCCCS->_hoops_CSC->_hoops_SICCS->count++;

									pts->x = _hoops_HPSCS.x;
									pts->y = _hoops_HPSCS.y;
									pts->z = _hoops_HPSCS.z;
									pts++;

									pts->x = pts[-2].x;
									pts->y = pts[-2].y;
									pts->z = pts[-2].z;
									pts++;
								}

								if (_hoops_RAHCR < 0.0f) {
									pts->x = _hoops_HPSCS.x - _hoops_RAGSS.y * radius;
									pts->y = _hoops_HPSCS.y + _hoops_RAGSS.x * radius;
									pts->z = _hoops_HPSCS.z;
								}
								else {
									pts->x = _hoops_HPSCS.x + _hoops_RAGSS.y * radius;
									pts->y = _hoops_HPSCS.y - _hoops_RAGSS.x * radius;
									pts->z = _hoops_HPSCS.z;
								}

								_hoops_SCCCS->_hoops_CSC->_hoops_SICCS->_hoops_ASPS += 3;
								_hoops_SCCCS->_hoops_CSC->_hoops_SICCS->count++;
							} break;
						}/*_hoops_CICA*/

						/* _hoops_AA _hoops_SR _hoops_RRP _hoops_PCCP "_hoops_ASSA" _hoops_PCPC? */
						_hoops_RICH (_hoops_RAHCR, s, c);

						if (s < 0.0f)
							s = -s;

						if (s > 0.0f && radius > (length + _hoops_GAGSS) /s) {
							/* _hoops_RGAR _hoops_HPGSS _hoops_IH _hoops_HA... */
							if ((_hoops_SCCCS->_hoops_CSC->_hoops_SICCS->count+1)*3 >= _hoops_SCCCS->_hoops_CSC->_hoops_SICCS->_hoops_SAGCA) 
								_hoops_PSCCS(nr ,_hoops_SCCCS->_hoops_CSC->_hoops_SICCS, 1, 3);

							DC_Point *	pts = _hoops_SCCCS->_hoops_CSC->_hoops_SICCS->_hoops_ASPS;

							pts->x = _hoops_HPSCS.x;
							pts->y = _hoops_HPSCS.y;
							pts->z = _hoops_HPSCS.z;
							pts++;

							if (_hoops_RAHCR > 0.0f) {
								pts->x = _hoops_PPSCS.x - path.y * radius;
								pts->y = _hoops_PPSCS.y + path.x * radius;
								pts->z = _hoops_PPSCS.z;
							}
							else {
								pts->x = _hoops_PPSCS.x + path.y * radius;
								pts->y = _hoops_PPSCS.y - path.x * radius;
								pts->z = _hoops_PPSCS.z;
							}
							pts++;

							if (_hoops_RAHCR > 0.0f) {
								pts->x = _hoops_AHGSS->x - _hoops_RAGSS.y * radius;
								pts->y = _hoops_AHGSS->y + _hoops_RAGSS.x * radius;
								pts->z = _hoops_AHGSS->z;
							}
							else {
								pts->x = _hoops_AHGSS->x + _hoops_RAGSS.y * radius;
								pts->y = _hoops_AHGSS->y - _hoops_RAGSS.x * radius;
								pts->z = _hoops_AHGSS->z;
							}

							_hoops_SCCCS->_hoops_CSC->_hoops_SICCS->_hoops_ASPS += 3;
							_hoops_SCCCS->_hoops_CSC->_hoops_SICCS->count++;
						}
					}/* _hoops_RRP _hoops_PCPC */

				  _hoops_PHGSS:
					_hoops_IHSCS = false;
				}

				break;
			}

			_hoops_IIIPI -= _hoops_SCCCS->size;
			_hoops_IIIPI -= _hoops_IAGSS;
			_hoops_IIIPI -= _hoops_RSIPA;
			_hoops_IIIPI -= _hoops_GHSCS;

			/* _hoops_IGIHH _hoops_HSGP _hoops_RPP _hoops_SIGR */
			while (_hoops_IIIPI > 0.0f) {
				switch (_hoops_SCCCS->mode) {
					case _hoops_SHCCS:
					case _hoops_GICCS:
					case _hoops_RICCS: {
						_hoops_IIIPI -= _hoops_SCCCS->size;
					}	break;

					case _hoops_AICCS:
						break;
				}

				_hoops_SCCCS = _hoops_SCCCS->_hoops_SSAC;
			}

		  _hoops_RPGSS:
			if (count <= 1 /* || _hoops_PRHAI */) {

				if (_hoops_ARSCS) {
					/* _hoops_ASGGR _hoops_GHSHA _hoops_RCAHR */
					dc->_hoops_APHHP->_hoops_HPPAS._hoops_PHGGH = points - _hoops_IRRAA;
					dc->_hoops_APHHP->_hoops_HPPAS._hoops_CIHIA = false;
				}

				_hoops_IASCS = _hoops_SCCCS;

				/* _hoops_PGSA _hoops_RH _hoops_GSAGS  */
				for (int i=0; i<_hoops_CRSCS; i++) {

					_hoops_HICCS * rc = _hoops_IRSCS[i];

					if (rc->_hoops_SICCS && rc->_hoops_SICCS->count) {
						_hoops_GSRGA (rc->nr, -3*rc->_hoops_SICCS->count, rc->_hoops_SICCS->points);
						rc->_hoops_SICCS->count = 0;
						rc->_hoops_SICCS->_hoops_ASPS = rc->_hoops_SICCS->points;
					}
					if (rc->_hoops_CICCS && rc->_hoops_CICCS->count) {
						_hoops_SCGGA(rc->nr, -2*rc->_hoops_CICCS->count, rc->_hoops_CICCS->points);
						rc->_hoops_CICCS->count = 0;
						rc->_hoops_CICCS->_hoops_ASPS = rc->_hoops_CICCS->points;
					}
					if (rc->_hoops_GCCCS && rc->_hoops_GCCCS->count) {

						if (rc->_hoops_IICCS && rc->_hoops_IICCS->_hoops_AHP->weight != weight)
							rc->_hoops_IICCS = null;

						if (!rc->_hoops_IICCS) {
							rc->_hoops_IICCS = rc->nr;
							_hoops_HC = rc->_hoops_IICCS.Modify()->_hoops_AHP.Modify();

							_hoops_HC->weight = weight;	
							_hoops_HC->flags |= _hoops_SSGIP;
							_hoops_HC->style = LCAP_BUTT|LJOIN_MITER;
						}
						_hoops_SCGGA(rc->_hoops_IICCS, -2*rc->_hoops_GCCCS->count, rc->_hoops_GCCCS->points);
						rc->_hoops_GCCCS->count = 0;
						rc->_hoops_GCCCS->_hoops_ASPS = rc->_hoops_GCCCS->points;
					}
				}

				/* _hoops_PGSA _hoops_RH _hoops_GPPC */
				for (int i=0; i<2; i++) {

					_hoops_IASCS = _hoops_SCCCS;

					if (i == 0)
						_hoops_SCCCS = _hoops_SASCS;
					else
						_hoops_SCCCS = _hoops_CASCS;

					if (_hoops_SCCCS) do {
						if (_hoops_SCCCS->mode == _hoops_AICCS && _hoops_SCCCS->glyph_lsic->count) {
							Net_Rendition				_hoops_SSGS = nr;
							_hoops_ICP alter &	_hoops_GGRS = _hoops_SSGS.Modify()->_hoops_GSP.Modify();
				 
							_hoops_GGRS->glyph = _hoops_SCCCS->glyph;

							if (BIT(_hoops_ACCI->flags,_hoops_PRCAP))
								_hoops_GGRS->flags |= _hoops_CGPSP;

							if (BIT(_hoops_SCCCS->flags, _hoops_IACAP)) {
								_hoops_GGRS->flags |= _hoops_SGPSP;

								_hoops_GGRS->_hoops_GRPSP._hoops_HHP = GSU_PIXELS;

								_hoops_GGRS->_hoops_GRPSP.value = (int)(HD_Compute_Generic_Size (nr, 
									_hoops_SCCCS->weight.value, 
									_hoops_SCCCS->weight._hoops_HHP, 
									_hoops_HRSCS, 
									false, 
									0, 
									true)+0.5f);
							}

							_hoops_GGRS->color = nr->_hoops_AHP->color; 
							_hoops_GGRS->contrast_color = nr->_hoops_AHP->contrast_color;

							_hoops_GGRS->_hoops_SSHHP = _hoops_GGRS->contrast_rendition = null;

							_hoops_GGRS->ysize = _hoops_SCCCS->size;
							_hoops_GGRS->_hoops_RGRS = _hoops_SCCCS->size*dc->current._hoops_AGRS;

							if (BIT(_hoops_SCCCS->flags, _hoops_PACAP))
								_hoops_GGRS->flags |= _hoops_IGPSP;

							HD_Std_DC_Polymarker (_hoops_SSGS, _hoops_SCCCS->glyph_lsic->count, _hoops_SCCCS->glyph_lsic->points, _hoops_SCCCS->glyph_lsic->_hoops_RRSR, null);
					
							_hoops_SCCCS->glyph_lsic->count = 0;
							_hoops_SCCCS->glyph_lsic->_hoops_ASPS = _hoops_SCCCS->glyph_lsic->points;
						}
						_hoops_SCCCS = _hoops_SCCCS->next;

					} while (_hoops_SCCCS && _hoops_SCCCS != _hoops_SASCS);

					_hoops_SCCCS = _hoops_IASCS;
				}

				if (_hoops_ARSCS) {
					/* _hoops_RGHH _hoops_GPGR _hoops_GHSHA _hoops_CRGC */
					if (dc->_hoops_APHHP->_hoops_HPPAS._hoops_CIHIA) {
						_hoops_PRSCS = true;
						if (dc->_hoops_APHHP->_hoops_HPPAS._hoops_RPPAS < 1)
							dc->_hoops_APHHP->_hoops_HPPAS._hoops_CHGGH = dc->_hoops_APHHP->_hoops_HPPAS._hoops_PHGGH;
						if (dc->_hoops_APHHP->_hoops_HPPAS._hoops_RPPAS < 0)
							break;
						if (dc->_hoops_APHHP->_hoops_HPPAS._hoops_RPPAS > 0) {
							/* _hoops_GGCR _hoops_SCGR _hoops_III _hoops_CAGH _hoops_IS _hoops_RGIAS _hoops_RPP _hoops_HAR _hoops_IIH _hoops_AIAH */
							_hoops_AISAP *	_hoops_HHCAP;

							if ((_hoops_HHCAP = dc->_hoops_APHHP->_hoops_HPPAS._hoops_ACSAP) != null) do {
								if (_hoops_HHCAP->_hoops_PISAP[0] == dc->_hoops_APHHP->_hoops_HPPAS._hoops_PHGGH)
									break;
							} while ((_hoops_HHCAP = _hoops_HHCAP->next) != null);

							if (_hoops_HHCAP == null) {
								POOL_ALLOC (_hoops_HHCAP, _hoops_AISAP, dc->memory_pool);
								_hoops_HHCAP->next = null;
								_hoops_HHCAP->_hoops_PISAP[0] = dc->_hoops_APHHP->_hoops_HPPAS._hoops_PHGGH;
								_hoops_HHCAP->_hoops_PISAP[1] = _hoops_HHCAP->_hoops_PISAP[0] + 1;
								_hoops_HHCAP->_hoops_PISAP[2] = -1;
								_hoops_HHCAP->_hoops_HISAP = dc->_hoops_APHHP->_hoops_HPPAS._hoops_HHGGH;
								_hoops_HHCAP->_hoops_IISAP = dc->_hoops_APHHP->_hoops_HPPAS._hoops_IHGGH;
								_hoops_HHCAP->next = null;
								*dc->_hoops_APHHP->_hoops_HPPAS._hoops_APPAS = _hoops_HHCAP;
								dc->_hoops_APHHP->_hoops_HPPAS._hoops_APPAS = &_hoops_HHCAP->next;
								if (/* !_hoops_SHCAH && */
									++dc->_hoops_APHHP->_hoops_HPPAS._hoops_PPPAS >=
										nr->_hoops_IRR->_hoops_CCIRP.polyline)
									dc->_hoops_APHHP->_hoops_HPPAS._hoops_RPPAS = 0;
							}
						}
					}
				}

				_hoops_SCCCS = _hoops_IASCS;
			}

			if (count < 1)
				break;

			_hoops_SISCS = _hoops_HPSCS.z;
			if (!_hoops_HISCS)
				points++;
		}

		/* _hoops_CASI _hoops_GH _hoops_HSGP */
		for (int i=0; i<2; i++) {

			if (i == 0)
				_hoops_SCCCS = _hoops_SASCS;
			else
				_hoops_SCCCS = _hoops_CASCS;

			if (_hoops_SCCCS) do {

				if (_hoops_SCCCS->mode == _hoops_AICCS) {
					_hoops_CSCCS(_hoops_SCCCS->glyph_lsic);
					_hoops_SCCCS->glyph.release();
				}

				/*_hoops_CASI _hoops_GH*/
				_hoops_IASCS = _hoops_SCCCS;
				_hoops_SCCCS = _hoops_SCCCS->next;
				FREE(_hoops_IASCS, _hoops_RCCCS);
			} while (_hoops_SCCCS && _hoops_SCCCS != _hoops_SASCS);
		}


		/* _hoops_GGAS _hoops_IHGSS */
		while (_hoops_HASCS) {
			_hoops_GPPA const *c=_hoops_HASCS;
			_hoops_HASCS=_hoops_HASCS->next;		
			FREE (c, _hoops_GPPA);
		}

		/*_hoops_PASCS*/
		/* _hoops_RSGR _hoops_IIGR _hoops_IIPH _hoops_PAR _hoops_SIRAR _hoops_III _hoops_RRGR */
	}

_hoops_AASCS:
	/* _hoops_PGSA _hoops_SPS _hoops_GGAIA _hoops_RPP _hoops_SIGR */
	if ((_hoops_RIIPI = _hoops_RIIPI->next) != null)
		goto _hoops_RASCS;

	/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_ASCA _hoops_GPGR _hoops_APGR */
	if (_hoops_RRC) {
		if (--incount>0) {
			_hoops_PSHCS += _hoops_RRC;
			goto _hoops_GASCS;
		}
	}

	if (_hoops_ARSCS) {
		dc->_hoops_APHHP->_hoops_HPPAS._hoops_CIHIA = _hoops_PRSCS;
	}
		
	/* _hoops_CASI _hoops_GH _hoops_IHAH */
	for (int i=0; i<_hoops_CRSCS; i++) {

		_hoops_HICCS * rc = _hoops_IRSCS[i];

		if (rc->_hoops_CICCS)
			_hoops_CSCCS(rc->_hoops_CICCS);
		if (rc->_hoops_SICCS)
			_hoops_CSCCS(rc->_hoops_SICCS);
		if (rc->_hoops_GCCCS)
			_hoops_CSCCS(rc->_hoops_GCCCS);

		if (rc->nr)
			rc->nr->release();

		if (rc->_hoops_IICCS)
			rc->_hoops_IICCS->release();

		FREE(rc, _hoops_HICCS);
	}

#endif
}

GLOBAL_FUNCTION void HD_Replace_Line_Style(Line_Rendition alter & _hoops_HC, Line_Style const & _hoops_CAIIH, bool _hoops_SAIIH)
{
	_hoops_HC->line_style = _hoops_CAIIH;

	if (_hoops_SAIIH) {
		_hoops_HC->start_glyph = null;
		_hoops_HC->middle_glyph = null;
		_hoops_HC->end_glyph = null;
	}
}




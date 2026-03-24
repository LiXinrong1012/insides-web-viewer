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
 * $Id: obf_tmp.txt 1.229 2011-01-22 06:23:53 covey Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "hidden.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "database.h"
#include "phedron.h"
#include "hpserror.h"
#include "phdraw.h"

#ifndef DISABLE_SORTING_HSR

#define _hoops_IRRSH(in, _hoops_PAGR) do {	\
		(_hoops_PAGR).x = (in).x;			\
		(_hoops_PAGR).y = (in).y;			\
		(_hoops_PAGR).z = (in).z;			\
	} while (0)

#define _hoops_CRRSH(in, _hoops_PAGR) do {	\
		(_hoops_PAGR)[0] = (in)[0];			\
		(_hoops_PAGR)[1] = (in)[1];			\
	} while (0)

#define _hoops_SRRSH(in, _hoops_PAGR) do {	\
		(_hoops_PAGR)[0] = (in)[0];			\
		(_hoops_PAGR)[1] = (in)[1];			\
		(_hoops_PAGR)[2] = (in)[2];			\
	} while (0)

#define _hoops_GARSH(in, _hoops_PAGR) do {	\
		_hoops_PAGR[0] = in[0];				\
		_hoops_PAGR[1] = in[1];				\
	} while (0)

#define _hoops_RARSH(in, _hoops_PAGR) do {	\
		_hoops_PAGR[0] = in[0];				\
		_hoops_PAGR[1] = in[1];				\
		_hoops_PAGR[2] = in[2];				\
	} while (0)

#define _hoops_AARSH(in, _hoops_PAGR) do {	\
		_hoops_PAGR[0] = in[0];						\
		_hoops_PAGR[1] = in[1];						\
		_hoops_PAGR[2] = in[2];						\
	} while (0)

#define _hoops_PARSH(in, _hoops_PAGR) do {	\
		(_hoops_PAGR)[0] = (in)[0];			\
		(_hoops_PAGR)[1] = (in)[1];			\
	} while (0)

#define _hoops_HARSH(in, _hoops_PAGR) do {	\
		(_hoops_PAGR)[0] = (in)[0];			\
		(_hoops_PAGR)[1] = (in)[1];			\
		(_hoops_PAGR)[2] = (in)[2];			\
	} while (0)

#define _hoops_IARSH(in, _hoops_PAGR, width) do { \
		COPY_PARAMETER (in[0], _hoops_PAGR[0], width); \
		COPY_PARAMETER (in[1], _hoops_PAGR[1], width); \
	} while (0)


local _hoops_HARHH * HI_Init_Hidden_Slab (Display_Context alter *dc, unsigned char **data, int size)
{
	_hoops_HARHH* _hoops_CHCSA = (_hoops_HARHH*)*data;

	_hoops_CARSH(_hoops_CHCSA);
	_hoops_CHCSA->data = *data; _hoops_PIGSH(*data, sizeof(_hoops_HARHH));
	_hoops_CHCSA->size = size;

	if (dc->_hoops_HCAGH) {
		_hoops_SGSPR (HEC_INFO, HES_HOOPS_IS_CONFUSED, "Hidden geometry being recollected ... not good.");
	}

	return _hoops_CHCSA;
}

local void _hoops_SARSH (
	_hoops_CASS alter			*hidden) {
	_hoops_SRHSA alter		*_hoops_ASHSA = hidden->_hoops_ASHSA;
	DC_Point alter		*pt = _hoops_ASHSA->points;
	int						count = _hoops_ASHSA->count;
	float					xmin, xmax;
	float					ymin, ymax;
	float					_hoops_RICR, _hoops_AICR;

	/* _hoops_CAHA _hoops_RH _hoops_IASC _hoops_AHCRR */
	xmin = xmax = pt->x;
	ymin = ymax = pt->y;
	_hoops_RICR = _hoops_AICR = pt->z;

	while (--count > 0) {
		++pt;

		if (xmin > pt->x)
			xmin = pt->x;
		else if (xmax < pt->x)
			xmax = pt->x;

		if (ymin > pt->y)
			ymin = pt->y;
		else if (ymax < pt->y)
			ymax = pt->y;

		if (_hoops_RICR > pt->z)
			_hoops_RICR = pt->z;
		else if (_hoops_AICR < pt->z)
			_hoops_AICR = pt->z;
	}

	_hoops_ASHSA->xmin = xmin;
	_hoops_ASHSA->ymin = ymin;
	_hoops_ASHSA->_hoops_RICR = _hoops_RICR;
	_hoops_ASHSA->xmax = xmax;
	_hoops_ASHSA->ymax = ymax;
	_hoops_ASHSA->_hoops_AICR = _hoops_AICR;

	if (hidden->_hoops_ASHSA->type == _hoops_AHHSA) {
		Net_Rendition const & 	nr = hidden->_hoops_ASHSA->_hoops_APHGA;
		Line_Rendition const &	_hoops_HC = nr->_hoops_AHP;
		int						weight = _hoops_HC->weight;

		if (weight < 0)
			weight = (int)(HD_Compute_Generic_Size (nr,  _hoops_HC->_hoops_PHP,  _hoops_HC->_hoops_HHP,
													1.0f, false, 0, true) + 0.5f);
		weight /= 2;

		_hoops_ASHSA->xmin -= weight;
		_hoops_ASHSA->ymin -= weight;
		_hoops_ASHSA->xmax += weight;
		_hoops_ASHSA->ymax += weight;
	}
}


/*
 * _hoops_GRSH _hoops_IS _hoops_IPPR _hoops_HIPH
 */

local void _hoops_GPRSH (
	Net_Rendition const &		nr,
	DC_Point alter *			points,
	_hoops_CAHSA const	*	_hoops_HSGSH,
	_hoops_CASS alter *				hidden) {
	_hoops_SRHSA alter *		_hoops_ASHSA = hidden->_hoops_ASHSA;

	_hoops_ASHSA->type = _hoops_IPHSA;
	_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA alter *)_hoops_HSGSH;
	_hoops_ASHSA->_hoops_APHGA = nr;

	_hoops_ASHSA->count = 3;
	_hoops_ASHSA->points = points;

	if (nr->_hoops_SRA->_hoops_RAI == null)
		hidden->values = 0;
	else
		hidden->values = nr->_hoops_SRA->_hoops_RAI->priority;

	{
		Point				_hoops_RPRSH;
		Point				_hoops_APRSH;

		_hoops_RPRSH.x = points[0].x - points[1].x;
		_hoops_RPRSH.y = points[0].y - points[1].y;
		_hoops_RPRSH.z = points[0].z - points[1].z;
		_hoops_APRSH.x = points[1].x - points[2].x;
		_hoops_APRSH.y = points[1].y - points[2].y;
		_hoops_APRSH.z = points[1].z - points[2].z;

		_hoops_ASHSA->plane.a = _hoops_RPRSH.y * _hoops_APRSH.z - _hoops_RPRSH.z * _hoops_APRSH.y;
		_hoops_ASHSA->plane.b = _hoops_RPRSH.z * _hoops_APRSH.x - _hoops_RPRSH.x * _hoops_APRSH.z;
		_hoops_ASHSA->plane.c = _hoops_RPRSH.x * _hoops_APRSH.y - _hoops_RPRSH.y * _hoops_APRSH.x;

		HI_Normalize ((Vector alter *)&_hoops_ASHSA->plane);

		/*
		 * _hoops_GHAP _hoops_RHCA _hoops_HHH _hoops_IIGR _hoops_RH _hoops_PCGC _hoops_HGAP _hoops_RPRHR _hoops_GHC.
		 */
		if (_hoops_ASHSA->plane.c < 0.0f) {
			_hoops_ASHSA->plane.a = -_hoops_ASHSA->plane.a;
			_hoops_ASHSA->plane.b = -_hoops_ASHSA->plane.b;
			_hoops_ASHSA->plane.c = -_hoops_ASHSA->plane.c;
		}

		/* _hoops_PPRSH, _hoops_CAHA '_hoops_GHGP' _hoops_HII _hoops_SI */
		_hoops_ASHSA->plane.d = -(_hoops_ASHSA->plane.a * points[0].x +
							_hoops_ASHSA->plane.b * points[0].y +
							_hoops_ASHSA->plane.c * points[0].z);
	}

	_hoops_SARSH (hidden);

	HD_Insert_In_Hidden_Tree (hidden);
}
#endif


GLOBAL_FUNCTION void HD_Hide_DC_Polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
#ifndef DISABLE_SORTING_HSR
	int							_hoops_RRC;
	DC_Point alter *			new_points;
	_hoops_CASS alter *				hidden;
	_hoops_HARHH *				_hoops_CHCSA;
	unsigned char *				data;
	int							size;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}

	if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
		RGBAS32				color;

		_hoops_AAASP (dc, nr->_hoops_IHA->color,
							   dc->_hoops_PGCC._hoops_PIHSR, color);

		color.a = (unsigned char)(255.99f * nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR);

		HD_Hide_DC_Colorized_Polytris (nr, count, points, &color, true);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);

	if (count == 0)
		return;

	size = _hoops_GIGSH(sizeof(_hoops_HARHH),1)+
			_hoops_GIGSH(sizeof(_hoops_CASS),count)+ _hoops_GIGSH(sizeof(_hoops_SRHSA),count) +
			_hoops_GIGSH(3*sizeof(DC_Point),count);

	POOL_ZALLOC_ARRAY_CACHED(data, size, unsigned char, dc->memory_pool);

	_hoops_CHCSA = HI_Init_Hidden_Slab(dc, &data, size);

	while (count-- > 0) {
		hidden = (_hoops_CASS*)data; _hoops_PIGSH(data, sizeof(_hoops_CASS)); 
		_hoops_CAHS(_hoops_CHCSA);
		hidden->flags = HF_SLABBED;
		hidden->_hoops_ASHSA = (_hoops_SRHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_SRHSA));
		_hoops_ICAI(hidden->_hoops_ASHSA);
		hidden->_hoops_ASHSA->_hoops_CHCSA = _hoops_CHCSA;
		hidden->_hoops_ASHSA->next = 0;
		new_points = (DC_Point*)data; _hoops_PIGSH(data, sizeof(DC_Point)*3);
		_hoops_AIGA (points, 3, DC_Point, new_points);
		_hoops_GPRSH (nr, new_points, null, hidden);

		points += _hoops_RRC;
	}
#endif
}


GLOBAL_FUNCTION void HD_Hide_DC_Colorized_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						single) {
#ifndef DISABLE_SORTING_HSR
	_hoops_CAHSA alter	*	info;
	int							_hoops_RRC;
	DC_Point alter *			new_points;
	_hoops_CASS alter *				hidden;
	_hoops_HARHH *				_hoops_CHCSA;
	unsigned char *				data;
	int							size;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 0, 0, 0, 0,
								 _hoops_GPHC|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);

	if (count == 0)
		return;

	size = _hoops_GIGSH(sizeof(_hoops_HARHH),1)+
			_hoops_GIGSH(sizeof(_hoops_CAHSA),count)+
			_hoops_GIGSH(sizeof(RGBAS32),count)+
			_hoops_GIGSH(sizeof(_hoops_CASS),count)+ _hoops_GIGSH(sizeof(_hoops_SRHSA),count) +
			_hoops_GIGSH(3*sizeof(DC_Point),count);

	POOL_ZALLOC_ARRAY_CACHED(data, size, unsigned char, dc->memory_pool);

	_hoops_CHCSA = HI_Init_Hidden_Slab(dc, &data, size);

	while (count-- > 0) {
		info = (_hoops_CAHSA*)data; _hoops_PIGSH(data,sizeof(_hoops_CAHSA));
		info->_hoops_RAGR = _hoops_PPHSA;
		info->_hoops_HPHSA = (RGBAS32*)data; _hoops_PIGSH(data,sizeof(RGBAS32));
		info->_hoops_HPHSA[0] = *colors;
		info->rgba_colors = null;
		info->planes = null;
		info->params = null;
		info->param_width = 0;
		info->param_flags = 0;

		hidden = (_hoops_CASS*)data; _hoops_PIGSH(data,sizeof(_hoops_CASS)); 
		_hoops_CAHS(_hoops_CHCSA);
		hidden->flags = HF_SLABBED;
		hidden->_hoops_ASHSA = (_hoops_SRHSA*)data; _hoops_PIGSH(data,sizeof(_hoops_SRHSA));
		_hoops_ICAI(hidden->_hoops_ASHSA);
		hidden->_hoops_ASHSA->next = 0;
		hidden->_hoops_ASHSA->_hoops_CHCSA = _hoops_CHCSA;
		new_points = (DC_Point*)data; _hoops_PIGSH(data, sizeof(DC_Point)*3);
		_hoops_AIGA (points, 3, DC_Point, new_points);
		_hoops_GPRSH (nr, new_points, info, hidden);

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
#endif
}


GLOBAL_FUNCTION void HD_Hide_DC_Gouraud_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors) {
#ifndef DISABLE_SORTING_HSR
	_hoops_CAHSA alter	*	info;
	int							_hoops_RRC;
	DC_Point alter *			new_points;
	_hoops_CASS alter *				hidden;
	_hoops_HARHH *				_hoops_CHCSA;
	unsigned char *				data;
	int							size;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, colors, 0, 0, 0, 0, 0, _hoops_GPHC|_hoops_AAIC);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);

	if (count == 0) 
		return;

	size = _hoops_GIGSH(sizeof(_hoops_HARHH),1)+
			_hoops_GIGSH(sizeof(_hoops_CAHSA),count)+
			_hoops_GIGSH(3*sizeof(RGBAS32),count)+
			_hoops_GIGSH(sizeof(_hoops_CASS),count)+ _hoops_GIGSH(sizeof(_hoops_SRHSA),count) +
			_hoops_GIGSH(3*sizeof(DC_Point),count);

	POOL_ZALLOC_ARRAY_CACHED(data, size, unsigned char, dc->memory_pool);

	_hoops_CHCSA = HI_Init_Hidden_Slab(dc, &data, size);

	while (count-- > 0) {
		info = (_hoops_CAHSA*)data; _hoops_PIGSH(data,sizeof(_hoops_CAHSA));
		info->_hoops_RAGR = _hoops_CPHSA;
		info->_hoops_HPHSA = (RGBAS32*)data;	_hoops_PIGSH(data,sizeof(RGBAS32)*3);
		_hoops_SRRSH (colors, info->_hoops_HPHSA);
		info->rgba_colors = null;
		info->planes = null;
		info->params = null;
		info->param_width = 0;
		info->param_flags = 0;

		hidden = (_hoops_CASS*)data; _hoops_PIGSH(data,sizeof(_hoops_CASS)); 
		_hoops_CAHS(_hoops_CHCSA);
		hidden->flags = HF_SLABBED;
		hidden->_hoops_ASHSA = (_hoops_SRHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_SRHSA));
		_hoops_ICAI(hidden->_hoops_ASHSA);
		hidden->_hoops_ASHSA->next = 0;
		hidden->_hoops_ASHSA->_hoops_CHCSA = _hoops_CHCSA;
		new_points = (DC_Point*)data; _hoops_PIGSH(data,sizeof(DC_Point)*3);
		_hoops_AIGA (points, 3, DC_Point, new_points);
		_hoops_GPRSH (nr, new_points, info, hidden);

		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}


GLOBAL_FUNCTION void HD_Hide_DC_Phong_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes) {

	HD_Hide_DC_Textured_Polytris (nr, count, points, colors, planes, null, 0, 0);
}

GLOBAL_FUNCTION void HD_Hide_DC_Textured_Polytris (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes,
	_hoops_RSSH const *			params,
	Integer32					param_width,	
	_hoops_SSIC				param_flags) {
#ifndef DISABLE_SORTING_HSR
#ifndef _hoops_IHSIP
	_hoops_CAHSA alter	*	info;
	int							_hoops_RRC;
	DC_Point alter *			new_points;
	_hoops_CASS alter *				hidden;
	_hoops_HARHH *				_hoops_CHCSA;
	unsigned char *				data;
	int							size;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polytriangle (nr, count, points, 0, colors, planes,
								 params, param_width, param_flags, _hoops_GPHC|_hoops_AAIC);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 3);

	if (count == 0) 
		return;

	size = _hoops_GIGSH(sizeof(_hoops_HARHH),1)+
			_hoops_GIGSH(sizeof(_hoops_CAHSA),count)+
			_hoops_GIGSH(3*sizeof(RGBA),count)+
			_hoops_GIGSH(3*sizeof(_hoops_ARPA),count)+
			_hoops_GIGSH(sizeof(_hoops_CASS),count)+ _hoops_GIGSH(sizeof(_hoops_SRHSA),count) +
			_hoops_GIGSH(3*sizeof(DC_Point),count);

	if (params != null)
		size += _hoops_GIGSH(3*param_width*sizeof(_hoops_RSSH), count);

	POOL_ZALLOC_ARRAY_CACHED(data, size, unsigned char, dc->memory_pool);

	_hoops_CHCSA = HI_Init_Hidden_Slab(dc, &data, size);

	while (count-- > 0) {
		info = (_hoops_CAHSA*)data; _hoops_PIGSH(data,sizeof(_hoops_CAHSA));
		ZERO_STRUCT (info, _hoops_CAHSA);

		if (colors) {
			info->rgba_colors = (RGBA*)data; _hoops_PIGSH(data,sizeof(RGBA)*3);
			_hoops_AARSH (colors, info->rgba_colors);
			info->_hoops_RAGR |= _hoops_SPHSA;
		}

		if (planes) {
			info->planes=(_hoops_ARPA*)data; _hoops_PIGSH(data,sizeof(_hoops_ARPA)*3);
			_hoops_HARSH (planes, info->planes);
			info->_hoops_RAGR |= _hoops_GHHSA;
		}

		info->param_width = param_width;
		info->param_flags = param_flags;
		if (params != null && param_width > 0) {
			info->params = (_hoops_RSSH*)data; _hoops_PIGSH(data,3*param_width*sizeof(_hoops_RSSH));
			_hoops_HPRSH (params, info->params, param_width, 3);
			info->_hoops_RAGR |= _hoops_RHHSA;
		}

		hidden = (_hoops_CASS*)data; _hoops_PIGSH(data,sizeof(_hoops_CASS)); 
		_hoops_CAHS(_hoops_CHCSA);
		hidden->flags = HF_SLABBED;
		hidden->_hoops_ASHSA = (_hoops_SRHSA*)data; _hoops_PIGSH(data,sizeof(_hoops_SRHSA));
		_hoops_ICAI(hidden->_hoops_ASHSA);
		hidden->_hoops_ASHSA->next = 0;
		hidden->_hoops_ASHSA->_hoops_CHCSA = _hoops_CHCSA;
		new_points = (DC_Point*)data; _hoops_PIGSH(data,sizeof(DC_Point)*3);
		_hoops_AIGA (points, 3, DC_Point, new_points);
		_hoops_GPRSH (nr, new_points, info, hidden);

		points += _hoops_RRC;
		if (colors)
			colors += _hoops_RRC;
		if (planes)
			planes += _hoops_RRC;
		if (params)
			params += _hoops_RRC * param_width;
	}
#endif
#endif
}


#ifndef DISABLE_SORTING_HSR

/*
 * _hoops_GRSH _hoops_IS _hoops_IPPR _hoops_RSSI
 */

local void _hoops_IPRSH (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	char						type,
	RGBAS32 const *				color) {

	if (count < 3) {
		/* _hoops_CPRSH */
	}
	else {
		_hoops_CASS alter				*hidden;
		DC_Point const			*pt;
		DC_Point const			*prev;
		_hoops_SRHSA alter		*_hoops_ASHSA;
		_hoops_HARHH				*_hoops_CHCSA;
		int							size;
		Display_Context alter	*dc = (Display_Context alter *) nr->_hoops_SRA;
		_hoops_CAHSA alter	*info;
		unsigned char				*data;

		size = _hoops_GIGSH(sizeof(_hoops_HARHH),1) + 
				_hoops_GIGSH(sizeof(_hoops_CASS),1) + _hoops_GIGSH(sizeof(_hoops_SRHSA),1) + 
				_hoops_GIGSH(sizeof(DC_Point),count);
		if (color != null)	
			size += _hoops_GIGSH(sizeof(_hoops_CAHSA),1) + 
					_hoops_GIGSH(sizeof(RGBAS32), 1);

		POOL_ZALLOC_ARRAY_CACHED(data, size, unsigned char, dc->memory_pool);

		_hoops_CHCSA = HI_Init_Hidden_Slab(dc, &data, size);
		_hoops_CAHS(_hoops_CHCSA);

		hidden = (_hoops_CASS*)data; _hoops_PIGSH(data, sizeof(_hoops_CASS));
		_hoops_ASHSA = (_hoops_SRHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_SRHSA));
		_hoops_ICAI(_hoops_ASHSA);
		_hoops_ASHSA->next = 0;
		hidden->_hoops_ASHSA = _hoops_ASHSA;
		hidden->flags = HF_SLABBED;
		_hoops_ASHSA->_hoops_CHCSA = _hoops_CHCSA;
		_hoops_ASHSA->type = type;
		if (color == null)
			_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA alter *)color;
		else{
			info = (_hoops_CAHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_CAHSA));
			info->_hoops_HPHSA = (RGBAS32*)data; _hoops_PIGSH(data, sizeof(RGBAS32));
			info->_hoops_RAGR = _hoops_PPHSA;
			info->_hoops_HPHSA[0] = *color;
			info->rgba_colors = null;
			info->planes = null;
			info->params = null;
			info->param_width = 0;
			info->param_flags = 0;
			_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA alter *)info;
		}
		_hoops_ASHSA->_hoops_APHGA = nr;

		if (nr->_hoops_SRA->_hoops_RAI == null)
			hidden->values = 0;
		else
			hidden->values = nr->_hoops_SRA->_hoops_RAI->priority;

		/*
		 * _hoops_IGPP _hoops_RH _hoops_RSSA, _hoops_PPR _hoops_CAHA _hoops_IRS _hoops_IPPA _hoops_PPR _hoops_IRS _hoops_IASC _hoops_AHCRR.
		 */
		_hoops_ASHSA->count = count;
		_hoops_ASHSA->points = (DC_Point*)data; _hoops_PIGSH(data, sizeof(DC_Point)*count);
		_hoops_AIGA (points, count, DC_Point, _hoops_ASHSA->points);

		_hoops_ASHSA->plane.a = 0.0f;
		_hoops_ASHSA->plane.b = 0.0f;
		_hoops_ASHSA->plane.c = 0.0f;

		pt = points;
		prev = pt + count - 1;
		_hoops_RGGA (count-- == 0) {
			/* (_hoops_SGPR _hoops_RH _hoops_SPRSH-_hoops_CCAC _hoops_SPAHR _hoops_IIGR _hoops_SPAAR _hoops_RH _hoops_IPPA) */
			_hoops_ASHSA->plane.a += (prev->y + pt->y) * (pt->z - prev->z);
			_hoops_ASHSA->plane.b += (prev->z + pt->z) * (pt->x - prev->x);
			_hoops_ASHSA->plane.c += (prev->x + pt->x) * (pt->y - prev->y);

			prev = pt++;
		}

		HI_Normalize ((Vector alter *)&_hoops_ASHSA->plane);

		/*
		 * _hoops_GHAP _hoops_RHCA _hoops_HHH _hoops_IIGR _hoops_RH _hoops_PCGC _hoops_HGAP _hoops_RPRHR _hoops_GHC
		 */
		if (_hoops_ASHSA->plane.c < 0.0f) {
			_hoops_ASHSA->plane.a = -_hoops_ASHSA->plane.a;
			_hoops_ASHSA->plane.b = -_hoops_ASHSA->plane.b;
			_hoops_ASHSA->plane.c = -_hoops_ASHSA->plane.c;
		}

		/* _hoops_PPRSH, _hoops_CAHA '_hoops_GHGP' _hoops_HII _hoops_SI */
		_hoops_ASHSA->plane.d = -(_hoops_ASHSA->plane.a * points[0].x +
							_hoops_ASHSA->plane.b * points[0].y +
							_hoops_ASHSA->plane.c * points[0].z);


		_hoops_SARSH (hidden);

		HD_Insert_In_Hidden_Tree (hidden);
	}
}
#endif

GLOBAL_FUNCTION void HD_Hide_DC_Face (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
#ifndef DISABLE_SORTING_HSR
	Display_Context const *		dc = nr->_hoops_SRA;

	if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
		RGBAS32				color;

		_hoops_AAASP (dc,
							   nr->_hoops_IHA->color,
							   dc->_hoops_PGCC._hoops_PIHSR,
							   color);
		color.a = (unsigned char)(255.99f *
									  nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR);

		HD_Hide_DC_Colorized_Face (nr, count, points, &color);
	}
	else
		_hoops_IPRSH (nr, count, points, _hoops_IAHSA, null);
#endif
}

GLOBAL_FUNCTION void HD_Hide_DC_Colorized_Face (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				color) {
#ifndef DISABLE_SORTING_HSR

	_hoops_IPRSH (nr, count, points, _hoops_IAHSA, color);
#endif
}

GLOBAL_FUNCTION void HD_Hide_DC_Polygon (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
#ifndef DISABLE_SORTING_HSR
	Display_Context const *		dc = nr->_hoops_SRA;

	if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
		RGBAS32				color;

		_hoops_AAASP (dc,
							   nr->_hoops_IHA->color,
							   dc->_hoops_PGCC._hoops_PIHSR,
							   color);
		color.a = (unsigned char)(255.99f *
									  nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR);

		/* _hoops_PAGA: _hoops_SAAAA _hoops_PCGPA _hoops_PCCP _hoops_HHHA _hoops_GGGR, _hoops_GCICP _hoops_AA _hoops_HAR _hoops_RRP _hoops_SCH */
		HD_Hide_DC_Colorized_Face (nr, count-1, points, &color);
		HD_Hide_DC_Polyline (nr, count, points);
	}
	else
		_hoops_IPRSH (nr, count, points, _hoops_ACHSA, null);
#endif
}




GLOBAL_FUNCTION void HD_Hide_DC_Polydot (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
#ifndef DISABLE_SORTING_HSR
	_hoops_CASS alter *				hidden;
	_hoops_SRHSA alter *		_hoops_ASHSA;
	_hoops_HARHH *				_hoops_CHCSA;
	unsigned char *				data;
	int							size;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;

	size =	_hoops_GIGSH(sizeof(_hoops_HARHH),1)+
			_hoops_GIGSH(sizeof(_hoops_CASS),count) + _hoops_GIGSH(sizeof(_hoops_SRHSA),count)+
			_hoops_GIGSH(sizeof(DC_Point),count);

	POOL_ZALLOC_ARRAY_CACHED(data, size, unsigned char, dc->memory_pool);
	_hoops_CHCSA = HI_Init_Hidden_Slab(dc, &data, size);

	while (count-- > 0) {
		hidden = (_hoops_CASS*)data; _hoops_PIGSH(data, sizeof(_hoops_CASS));
		_hoops_CAHS(_hoops_CHCSA);
		hidden->_hoops_ASHSA = (_hoops_SRHSA*)data; _hoops_PIGSH(data,sizeof(_hoops_SRHSA));
		_hoops_ICAI(hidden->_hoops_ASHSA);
		hidden->_hoops_ASHSA->next = 0;
		_hoops_ASHSA = hidden->_hoops_ASHSA;
		hidden->flags = HF_SLABBED;
		_hoops_ASHSA->_hoops_CHCSA = _hoops_CHCSA;
		_hoops_ASHSA->type = _hoops_RCHSA;
		_hoops_ASHSA->_hoops_APHGA = nr;

		if (nr->_hoops_SRA->_hoops_RAI == null)
			hidden->values = 0;
		else
			hidden->values = nr->_hoops_SRA->_hoops_RAI->priority;

		_hoops_ASHSA->points = (DC_Point*)data; _hoops_PIGSH(data, sizeof(DC_Point));
		_hoops_RSAI (points, DC_Point, _hoops_ASHSA->points);
		_hoops_ASHSA->count = 1;

		/* _hoops_PHIR _hoops_GGR _hoops_RH _hoops_IPPA, _hoops_HIH _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_SIGR */
		_hoops_ASHSA->plane = _hoops_CGISA::_hoops_CRGA;

		_hoops_ASHSA->_hoops_GPHSA = null;

		_hoops_SARSH (hidden);

		HD_Insert_In_Hidden_Tree (hidden);

		points++;
	}
#endif
}


GLOBAL_FUNCTION void HD_Hide_DC_Colorized_Polydot (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,	
	RGBAS32 const *				colors,
	bool						single) {
#ifndef DISABLE_SORTING_HSR
	_hoops_CASS alter *				hidden;
	_hoops_SRHSA alter *		_hoops_ASHSA;
	_hoops_CAHSA alter	*	info;
	int							size;
	_hoops_HARHH *				_hoops_CHCSA;
	unsigned char *				data;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;

	size =		_hoops_GIGSH(sizeof(_hoops_HARHH),1) +
				_hoops_GIGSH(sizeof(_hoops_CASS),count) + _hoops_GIGSH(sizeof(_hoops_SRHSA),count)+
				_hoops_GIGSH(sizeof(_hoops_CAHSA),count) +
				_hoops_GIGSH(sizeof(RGBAS32),count)+
				_hoops_GIGSH(sizeof(DC_Point),count);

	POOL_ZALLOC_ARRAY_CACHED(data, size, unsigned char, dc->memory_pool);

	_hoops_CHCSA = HI_Init_Hidden_Slab(dc, &data, size);
	_hoops_CAHS(_hoops_CHCSA);

	while (count-- > 0) {
		hidden = (_hoops_CASS*)data; _hoops_PIGSH(data, sizeof(_hoops_CASS));
		info = (_hoops_CAHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_CAHSA));
		hidden->_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA alter *)info;
		hidden->_hoops_ASHSA = (_hoops_SRHSA*)data; _hoops_PIGSH(data,sizeof(_hoops_SRHSA));
		_hoops_ICAI(hidden->_hoops_ASHSA);
		hidden->_hoops_ASHSA->next = 0;
		_hoops_ASHSA = hidden->_hoops_ASHSA;
		hidden->flags = HF_SLABBED;
		_hoops_ASHSA->_hoops_CHCSA = _hoops_CHCSA;
		_hoops_ASHSA->type = _hoops_RCHSA;
		_hoops_ASHSA->_hoops_APHGA = nr;

		if (nr->_hoops_SRA->_hoops_RAI == null)
			hidden->values = 0;
		else
			hidden->values = nr->_hoops_SRA->_hoops_RAI->priority;
		
		_hoops_ASHSA->count = 1;
		_hoops_ASHSA->points = (DC_Point*)data; _hoops_PIGSH(data, sizeof(DC_Point));
		*_hoops_ASHSA->points = *points;

		ZERO_STRUCT (info, _hoops_CAHSA);
		info->_hoops_RAGR = _hoops_PPHSA;
		info->_hoops_HPHSA = (RGBAS32*)data; _hoops_PIGSH(data, sizeof(RGBAS32));
		*info->_hoops_HPHSA = *colors;

		/* _hoops_PHIR _hoops_GGR _hoops_RH _hoops_IPPA, _hoops_HIH _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_SIGR */
		_hoops_ASHSA->plane = _hoops_CGISA::_hoops_CRGA;

		_hoops_ASHSA->_hoops_GPHSA = null;

		_hoops_SARSH (hidden);

		HD_Insert_In_Hidden_Tree (hidden);

		points++;

		if (!single)
			colors++;
	}
#endif
}


#ifndef DISABLE_SORTING_HSR
/*
 * _hoops_GRSH _hoops_IS _hoops_IPPR _hoops_PGRC
 */

local void _hoops_GHRSH (
	Net_Rendition const &		nr,
	DC_Point const			*points,
	_hoops_CASS alter				*hidden) {
	_hoops_SRHSA alter		*_hoops_ASHSA;


	_hoops_ASHSA = hidden->_hoops_ASHSA;
	_hoops_ASHSA->type = _hoops_AHHSA;
	_hoops_ASHSA->_hoops_APHGA = nr;

	if (nr->_hoops_SRA->_hoops_RAI == null)
		hidden->values = 0;
	else
		hidden->values = nr->_hoops_SRA->_hoops_RAI->priority;
	
	_hoops_AIGA (points, 2, DC_Point, _hoops_ASHSA->points);
	_hoops_ASHSA->count = 2;

	/* _hoops_PHIR _hoops_GGR _hoops_RH _hoops_IPPA, _hoops_HIH _hoops_PAHA'_hoops_RA _hoops_SHH _hoops_SIGR */
	_hoops_ASHSA->plane = _hoops_CGISA::_hoops_CRGA;

	_hoops_SARSH (hidden);

	HD_Insert_In_Hidden_Tree (hidden);
}
#endif


GLOBAL_FUNCTION void HD_Hide_DC_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
#ifndef DISABLE_SORTING_HSR
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	int							_hoops_RRC;
	int							size;
	_hoops_CASS alter *				hidden;
	_hoops_HARHH *				_hoops_CHCSA;
	unsigned char *				data;

	if (count > 2 &&
		(!BIT(nr->_hoops_AHP->line_style->flags, LSF_SOLID) ||
		nr->_hoops_AHP->weight > nr->_hoops_SRA->_hoops_PGCC._hoops_IHHSR ||
		BIT(nr->_hoops_AHP->flags, _hoops_SRPI) || 
		 ANYBIT(nr->_hoops_AHP->line_style->flags, LSF_COMPLEX_ANYBITS))) {
		HD_Std_DC_Polyline (nr, count, points);
		return;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, 0, 0, 0, 0, 0, _hoops_GPHC);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 2);

	if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
		RGBAS32				color;

		_hoops_AAASP (dc,
							   nr->_hoops_AHP->color,
							   dc->_hoops_PGCC._hoops_PIHSR,
							   color);

		color.a = (unsigned char)(255.99f *
						nr->_hoops_AHP->_hoops_CHA->_hoops_IRIR);

		while (count-- > 0) {
			HD_Hide_DC_Colorized_Polyline (nr, 2, points, &color, true);
			points += _hoops_RRC;
		} 
		return;
	}


	size =	_hoops_GIGSH(sizeof(_hoops_HARHH),1) +
			_hoops_GIGSH(sizeof(_hoops_CASS),count) + _hoops_GIGSH(sizeof(_hoops_SRHSA),count) +
			_hoops_GIGSH(sizeof(DC_Point), 2*count);

	POOL_ZALLOC_ARRAY_CACHED(data, size, unsigned char, dc->memory_pool);

	_hoops_CHCSA = HI_Init_Hidden_Slab(dc, &data, size);

	while (count-- > 0) {
		hidden = (_hoops_CASS*)data; _hoops_PIGSH(data, sizeof(_hoops_CASS));
		_hoops_CAHS(_hoops_CHCSA);
		hidden->flags = HF_SLABBED;
		hidden->_hoops_ASHSA = (_hoops_SRHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_SRHSA));
		_hoops_ICAI(hidden->_hoops_ASHSA);
		hidden->_hoops_ASHSA->next = 0;
		hidden->_hoops_ASHSA->_hoops_CHCSA = _hoops_CHCSA;
		hidden->_hoops_ASHSA->points = (DC_Point*)data; _hoops_PIGSH(data, sizeof(DC_Point)*2);
		hidden->_hoops_ASHSA->_hoops_GPHSA = null;
		/* _hoops_ARP _hoops_GH _hoops_IRS _hoops_CCSHP _hoops_RHRSH */

		_hoops_GHRSH (nr, points, hidden);

		points += _hoops_RRC;
	}
#endif
}



GLOBAL_FUNCTION void HD_Hide_DC_Colorized_Polyline (
	Net_Rendition const &			nr,
	int								count,
	DC_Point const *				points,
	RGBAS32 const *					colors,
	bool							single) {
#ifndef DISABLE_SORTING_HSR
	_hoops_CAHSA alter	*		info;
	int								_hoops_RRC;
	int								size;
	_hoops_CASS alter *					hidden;
	_hoops_HARHH *					_hoops_CHCSA;
	unsigned char *					data;
	Display_Context alter *			dc = (Display_Context alter *) nr->_hoops_SRA;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0, 0, 0, 0, 0,
								 _hoops_GPHC|(single?_hoops_RAIC:_hoops_PAIC));
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 2);

	size =	_hoops_GIGSH(sizeof(_hoops_HARHH),1) +
			_hoops_GIGSH(sizeof(_hoops_CAHSA), count) +
			_hoops_GIGSH(sizeof(_hoops_CASS),count) + _hoops_GIGSH(sizeof(_hoops_SRHSA),count) +
			_hoops_GIGSH(sizeof(DC_Point), 2*count) +
			_hoops_GIGSH(sizeof(RGBAS32), count);

	POOL_ZALLOC_ARRAY_CACHED(data, size, unsigned char, dc->memory_pool);

	_hoops_CHCSA = HI_Init_Hidden_Slab(dc, &data, size);
	
	while (count-- > 0) {
		hidden = (_hoops_CASS*)data; _hoops_PIGSH(data, sizeof(_hoops_CASS));
		_hoops_CAHS(_hoops_CHCSA);
		hidden->flags = HF_SLABBED;
		hidden->_hoops_ASHSA = (_hoops_SRHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_SRHSA));
		_hoops_ICAI(hidden->_hoops_ASHSA);
		hidden->_hoops_ASHSA->next = 0;
		hidden->_hoops_ASHSA->_hoops_CHCSA = _hoops_CHCSA;
		hidden->_hoops_ASHSA->points = (DC_Point*)data; _hoops_PIGSH(data, sizeof(DC_Point)*2);
		info = (_hoops_CAHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_CAHSA));
		ZERO_STRUCT (info, _hoops_CAHSA);
		info->_hoops_RAGR = _hoops_PPHSA;
		hidden->_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA alter *)info;
		
		info->_hoops_HPHSA = (RGBAS32*)data; _hoops_PIGSH(data, sizeof(RGBAS32));
		*info->_hoops_HPHSA = *colors;

		_hoops_GHRSH (nr, points, hidden);

		points += _hoops_RRC;
		if (!single)
			colors++;
	}
#endif
}

GLOBAL_FUNCTION void HD_Hide_DC_Gouraud_Polyline (
	Net_Rendition const &			nr,
	int								count,
	DC_Point const *				points,
	RGBAS32 const *					colors) {
#ifndef DISABLE_SORTING_HSR
	_hoops_CAHSA alter	*		info;
	int								_hoops_RRC;
	int								size;
	_hoops_CASS alter *					hidden;
	_hoops_HARHH *					_hoops_CHCSA;
	unsigned char *					data;
	Display_Context alter *			dc = (Display_Context alter *) nr->_hoops_SRA;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, colors, 0, 0, 0, 0, 0, _hoops_GPHC|_hoops_AAIC);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 2);

	size =	_hoops_GIGSH(sizeof(_hoops_HARHH),1) +
			_hoops_GIGSH(sizeof(_hoops_CAHSA), count) +
			_hoops_GIGSH(sizeof(_hoops_CASS),count) + _hoops_GIGSH(sizeof(_hoops_SRHSA),count) +
			_hoops_GIGSH(sizeof(DC_Point), 2*count) +
			_hoops_GIGSH(sizeof(RGBAS32), 2*count);

	POOL_ZALLOC_ARRAY_CACHED(data, size, unsigned char, dc->memory_pool);

	_hoops_CHCSA = HI_Init_Hidden_Slab(dc, &data, size);

	while (count-- > 0) {
		hidden = (_hoops_CASS*)data; _hoops_PIGSH(data, sizeof(_hoops_CASS));
		_hoops_CAHS(_hoops_CHCSA);
		hidden->flags = HF_SLABBED;
		hidden->_hoops_ASHSA = (_hoops_SRHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_SRHSA));
		_hoops_ICAI(hidden->_hoops_ASHSA);
		hidden->_hoops_ASHSA->next = 0;
		hidden->_hoops_ASHSA->_hoops_CHCSA = _hoops_CHCSA;
		hidden->_hoops_ASHSA->points = (DC_Point*)data; _hoops_PIGSH(data, sizeof(DC_Point)*2);

		info = (_hoops_CAHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_CAHSA));
		ZERO_STRUCT (info, _hoops_CAHSA);
		info->_hoops_RAGR = _hoops_CPHSA;

		hidden->_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA alter *)info;
		
		info->_hoops_HPHSA = (RGBAS32*)data; _hoops_PIGSH(data, 2*sizeof(RGBAS32));
		_hoops_CRRSH (colors, info->_hoops_HPHSA);

		_hoops_GHRSH (nr, points, hidden);

		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
#endif
}

GLOBAL_FUNCTION void HD_Hide_DC_Phong_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes) {

	HD_Hide_DC_Textured_Polyline (nr, count, points, colors, planes, null, 0, 0);
}

GLOBAL_FUNCTION void HD_Hide_DC_Textured_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	_hoops_SSIC				param_flags) {
#ifndef DISABLE_SORTING_HSR
#ifndef _hoops_IHSIP
	_hoops_CAHSA alter	*	info;
	int							_hoops_RRC;
	int							size;
	_hoops_CASS alter *				hidden;
	_hoops_HARHH *				_hoops_CHCSA;
	unsigned char *				data;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		HD_Clip_DC_Polyline (nr, count, points, 0, colors, planes,
								 params, param_width, param_flags, _hoops_GPHC|_hoops_AAIC);
		return;
	}

	_hoops_ICHC (count, _hoops_RRC, 2);

	size =	_hoops_GIGSH(sizeof(_hoops_HARHH),1) +
			_hoops_GIGSH(sizeof(_hoops_CAHSA), count) +
			_hoops_GIGSH(sizeof(DC_Point), 2*count) +
			_hoops_GIGSH(sizeof(_hoops_CASS),count) + _hoops_GIGSH(sizeof(_hoops_SRHSA),count);

	if (colors) 
		size += _hoops_GIGSH(sizeof(RGBA), 2*count);
	if (planes) 
		size += _hoops_GIGSH(sizeof(_hoops_ARPA), 2*count);
	if (params != null && param_width > 0)
		size += _hoops_GIGSH(sizeof(_hoops_RSSH), 2*param_width*count);
	/* _hoops_IGIR _hoops_CGH _hoops_SHH _hoops_AISP _hoops_HPP _hoops_HA */

	POOL_ZALLOC_ARRAY_CACHED(data, size, unsigned char, dc->memory_pool);

	_hoops_CHCSA = HI_Init_Hidden_Slab(dc, &data, size);

	while (count-- > 0) {
		hidden = (_hoops_CASS*)data; _hoops_PIGSH(data, sizeof(_hoops_CASS));
		_hoops_CAHS(_hoops_CHCSA);
		hidden->flags = HF_SLABBED;
		hidden->_hoops_ASHSA = (_hoops_SRHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_SRHSA));
		_hoops_ICAI(hidden->_hoops_ASHSA);
		hidden->_hoops_ASHSA->next = 0;
		hidden->_hoops_ASHSA->_hoops_CHCSA = _hoops_CHCSA;
		hidden->_hoops_ASHSA->points = (DC_Point*)data; _hoops_PIGSH(data, sizeof(DC_Point)*2);
		
		info = (_hoops_CAHSA*)data; _hoops_PIGSH(data, sizeof(_hoops_CAHSA));
		ZERO_STRUCT (info, _hoops_CAHSA);
		hidden->_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA alter *)info;

		if (colors) {
			info->rgba_colors = (RGBA*)data; _hoops_PIGSH(data, sizeof(RGBA)*2);
			_hoops_GARSH (colors, info->rgba_colors);
			info->_hoops_RAGR |= _hoops_SPHSA;
		}
		if (planes) {
			info->planes = (_hoops_ARPA*)data; _hoops_PIGSH(data, sizeof(_hoops_ARPA)*2);
			_hoops_PARSH (planes, info->planes);
			info->_hoops_RAGR |= _hoops_GHHSA;
		}

		info->param_width = param_width;
		info->param_flags = param_flags;
		if (params != null && param_width > 0) {
			info->params = (_hoops_RSSH*)data; _hoops_PIGSH(data, sizeof(_hoops_RSSH)*2*param_width);
			_hoops_HPRSH (params, info->params, param_width, 2);
			info->_hoops_RAGR |= _hoops_RHHSA;
		}

		_hoops_GHRSH (nr, points, hidden);

		points += _hoops_RRC;
		if (colors)
			colors += _hoops_RRC;
		if (planes)
			planes += _hoops_RRC;
		if (params)
			params += _hoops_RRC * param_width;
	}
#endif
#endif
}



/*
 * _hoops_GRSH _hoops_IS _hoops_IPPR _hoops_RII _hoops_SIH & _hoops_SCSHR
 */

#if 0
GLOBAL_FUNCTION void HD_Hide_DC_Polymarker (
	Net_Rendition const &		nr,
	int							count;
	DC_Point const *			where) {
#ifndef DISABLE_SORTING_HSR
	_hoops_CASS alter *				hidden;
	_hoops_ICP const	&	_hoops_CCP = nr->_hoops_GSP;

	while (count-- > 0) {
		POOL_ZALLOC (hidden, _hoops_CASS, dc->memory_pool);
		hidden->flags = HF_NONE;
		hidden->type = _hoops_PCHSA;

		if (nr->_hoops_SRA->_hoops_RAI == null)
			hidden->priority = 0;
		else
			hidden->priority = nr->_hoops_SRA->_hoops_RAI->priority;

		hidden->plane.a = 0.0f;
		hidden->plane.b = 0.0f;
		hidden->plane.c = 1.0f;
		hidden->plane.d = -where->z;

		hidden->xmin = where->x - (float)_hoops_CCP->_hoops_RGRS;
		hidden->ymin = where->y - (float)_hoops_CCP->ysize;
		hidden->xmax = where->x + (float)_hoops_CCP->_hoops_RGRS;
		hidden->ymax = where->y + (float)_hoops_CCP->ysize;
		hidden->_hoops_RICR = hidden->_hoops_AICR = where->z;

		HD_Insert_In_Hidden_Tree (hidden);

		where++;
	}
#endif
}
#endif



GLOBAL_FUNCTION void HD_Hide_DC_Image (
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
#ifndef DISABLE_SORTING_HSR

	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_CASS alter *				hidden;
	_hoops_HHHSA alter *			ii;
	_hoops_SRHSA alter *		_hoops_ASHSA;

	POOL_ZALLOC (hidden, _hoops_CASS, dc->memory_pool);
	POOL_ZALLOC (_hoops_ASHSA, _hoops_SRHSA, dc->memory_pool);
	_hoops_ICAI(_hoops_ASHSA);
	hidden->_hoops_ASHSA = _hoops_ASHSA;
	_hoops_ASHSA->type = _hoops_PHHSA;

	_hoops_ASHSA->_hoops_APHGA = nr;

	if (nr->_hoops_SRA->_hoops_RAI == null)
		hidden->values = 0;
	else
		hidden->values = nr->_hoops_SRA->_hoops_RAI->priority;

	POOL_ALLOC (ii, _hoops_HHHSA, dc->memory_pool);
	_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA alter *)ii;
	ii->_hoops_HIHI = 1;

	ii->hoffset = hoffset;
	ii->format = format;
	ii->pattern = pattern;
	ii->contrast_color = contrast_color;

	if ((ii->db_image = db_image) != null) {
		_hoops_PRRH (db_image);
		ii->row_bytes = row_bytes;
		ii->rasters = rasters;
	}
	else {
		int						height;
		char					*_hoops_AHRSH;
		void					**_hoops_HCHIH;

		if (row_bytes == 0) {
			row_bytes = (int)(end->x - start->x + 1);
			switch (format) {
				case _hoops_GGRH:
				case _hoops_RGRH:
				case _hoops_AGRH:
				case _hoops_IRRH:
				case _hoops_CRRH:
				case _hoops_SRRH:	ASSERT(0);   break;  //_hoops_CSCR _hoops_PIH _hoops_CCCH _hoops_GRS _hoops_HS _hoops_IS _hoops_SHH _hoops_CPHR _hoops_IRS _hoops_RSCA _hoops_RRAR

				case _hoops_AHGH:
				case Image_MAPPED_8:					break;

				case Image_MAPPED_16:	row_bytes *= 2; break;

				case _hoops_HHGH:		row_bytes *= 3; break;

				case _hoops_CSGSP:
				case Image_RGBA32:
				case _hoops_HRSRH:		row_bytes *= 4; break;
			}
		}
		ii->row_bytes = row_bytes;
		height = (int)(start->y - end->y + 1);

		POOL_ALLOC_ARRAY_CACHED (_hoops_HCHIH, height, void *, dc->memory_pool);
		ii->rasters = (void const * const *)_hoops_HCHIH;

		POOL_ALLOC_ARRAY_CACHED (_hoops_AHRSH, row_bytes * height, char, dc->memory_pool);
		do {
			COPY_MEMORY (*rasters++, row_bytes, _hoops_AHRSH);
			*_hoops_HCHIH++ = _hoops_AHRSH;
			_hoops_AHRSH += row_bytes;
		} _hoops_RGGA (--height == 0);
	}

	_hoops_ASHSA->plane.a = 0.0f;
	_hoops_ASHSA->plane.b = 0.0f;
	_hoops_ASHSA->plane.c = 1.0f;
	_hoops_ASHSA->plane.d = -start->z;

	_hoops_ASHSA->xmin = start->x;
	_hoops_ASHSA->xmax = end->x;
	_hoops_ASHSA->ymin = end->y;
	_hoops_ASHSA->ymax = start->y;
	_hoops_ASHSA->_hoops_RICR = start->z;
	_hoops_ASHSA->_hoops_AICR = end->z;

	HD_Insert_In_Hidden_Tree (hidden);
#endif
}


GLOBAL_FUNCTION void HD_Hide_DC_Stenciled_Quad (
	Net_Rendition const &		nr,
	DC_Point const *			points,
	_hoops_RAARP const *		stencil) {
#ifndef DISABLE_SORTING_HSR
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_CASS alter *				hidden;
	_hoops_SRHSA alter *		_hoops_ASHSA;
	_hoops_GIHSA alter *		si;

	POOL_ZALLOC (hidden, _hoops_CASS, dc->memory_pool);
	POOL_ZALLOC (_hoops_ASHSA, _hoops_SRHSA, dc->memory_pool);
	_hoops_ICAI(_hoops_ASHSA);
	hidden->_hoops_ASHSA = _hoops_ASHSA;
	_hoops_ASHSA->type = _hoops_SHHSA;

	_hoops_ASHSA->_hoops_APHGA = nr;

	if (dc->_hoops_RAI == null)
		hidden->values = 0;
	else
		hidden->values = dc->_hoops_RAI->priority;

	_hoops_ASHSA->points = null;
	_hoops_ASHSA->count = 0;

	POOL_ALLOC (si, _hoops_GIHSA, dc->memory_pool);
	_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA alter *)si;
	si->_hoops_HIHI = 1;
	si->stencil = HI_Clone_Stencil(stencil);

	_hoops_ASHSA->plane.a = 0.0f;
	_hoops_ASHSA->plane.b = 0.0f;
	_hoops_ASHSA->plane.c = 1.0f;
	_hoops_ASHSA->plane.d = -points[0].z;

	_hoops_ASHSA->xmin = points[0].x;
	_hoops_ASHSA->xmax = points[3].x;
	_hoops_ASHSA->ymin = points[0].y;
	_hoops_ASHSA->ymax = points[3].y;
	_hoops_ASHSA->_hoops_RICR = _hoops_ASHSA->_hoops_AICR = points[0].z;

	HD_Insert_In_Hidden_Tree (hidden);
#endif
}


GLOBAL_FUNCTION void HD_Hide_Plain_Text (
	Net_Rendition const &		nr,
	_hoops_HACC const *				_hoops_PCHIH,
	Point const *				position,
	int							count,
	Karacter const *			_hoops_IHSCP,
	_hoops_PGCSR const *	_hoops_HGCSR) {
#ifndef DISABLE_SORTING_HSR
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	_hoops_CASS alter *				hidden;
	_hoops_HIHSA alter *	_hoops_CSGCP;
	float						width;
	float						height;
	_hoops_SRHSA alter *		_hoops_ASHSA;

	UNREFERENCED (_hoops_HGCSR);

	HD_Measure_Characters (nr, count, _hoops_IHSCP, _hoops_PCHIH->encoding, &width);
	height = (float)_hoops_HRCIR->font->_hoops_ISISR;

	if (_hoops_HRCIR->_hoops_IPGRP != 0.0f) {
		float	_hoops_GGHCR, _hoops_AGHCR, _hoops_HHCAP;

		_hoops_RICH (_hoops_HRCIR->_hoops_IPGRP, _hoops_GGHCR, _hoops_AGHCR);

		_hoops_HHCAP = height * _hoops_GGHCR / _hoops_AGHCR;
		width += _hoops_HHCAP;
	}

	POOL_ZALLOC (hidden, _hoops_CASS, dc->memory_pool);
	POOL_ZALLOC (_hoops_ASHSA, _hoops_SRHSA, dc->memory_pool);
	_hoops_ICAI(_hoops_ASHSA);
	hidden->_hoops_ASHSA = _hoops_ASHSA;
	_hoops_ASHSA->type = _hoops_PIHSA;

	_hoops_ASHSA->_hoops_APHGA = nr;

	if (dc->_hoops_RAI == null)
		hidden->values = 0;
	else
		hidden->values = dc->_hoops_RAI->priority;

	POOL_ALLOC_ARRAY (_hoops_ASHSA->points, 1, DC_Point, dc->memory_pool);
	_hoops_RSAI (position, DC_Point, _hoops_ASHSA->points);
	_hoops_ASHSA->count = 1;

	POOL_ALLOC (_hoops_CSGCP, _hoops_HIHSA, dc->memory_pool);
	_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA alter *)_hoops_CSGCP;

	_hoops_CSGCP->_hoops_SIHSA.length = count;
	ALLOC_ARRAY (_hoops_CSGCP->_hoops_SIHSA._hoops_IPPPP, count+1, Karacter); // _hoops_ASAI _hoops_PHRSH
	_hoops_AIGA (_hoops_IHSCP, count, Karacter, _hoops_CSGCP->_hoops_SIHSA._hoops_IPPPP);

	_hoops_CSGCP->_hoops_SIHSA._hoops_IPPPP[count] = 0;
	_hoops_CSGCP->_hoops_RACSR = _hoops_HRCIR->font->_hoops_RACSR;
	_hoops_CSGCP->_hoops_GCHSA = _hoops_HRCIR->font->_hoops_GCHSA;

	if ((_hoops_CSGCP->text = _hoops_PCHIH) != null) 
		_hoops_PRRH (_hoops_PCHIH);

	_hoops_ASHSA->plane.a = 0.0f;
	_hoops_ASHSA->plane.b = 0.0f;
	_hoops_ASHSA->plane.c = 1.0f;
	_hoops_ASHSA->plane.d = -position->z;

	if (_hoops_HRCIR->rotation == 0.0f) {
		_hoops_ASHSA->xmin = position->x;
		_hoops_ASHSA->xmax = position->x + width;
		_hoops_ASHSA->ymin = position->y;
		_hoops_ASHSA->ymax = position->y + height;
	}
	else {		/* _hoops_HPCAR _hoops_AHPA _hoops_GGR _hoops_GII _hoops_HAGA */
		_hoops_ASHSA->xmin = position->x - _hoops_IAAA (width, height);
		_hoops_ASHSA->xmax = position->x + _hoops_IAAA (width, height);
		_hoops_ASHSA->ymin = position->y - _hoops_IAAA (width, height);
		_hoops_ASHSA->ymax = position->y + _hoops_IAAA (width, height);
	}
	_hoops_ASHSA->_hoops_RICR = position->z;
	_hoops_ASHSA->_hoops_AICR = _hoops_ASHSA->_hoops_RICR;

	HD_Insert_In_Hidden_Tree (hidden);
#endif
}


#ifndef DISABLE_SORTING_HSR

/*
 * _hoops_PS _hoops_CGH _hoops_IIP _hoops_HS _hoops_IS _hoops_IPPR _hoops_RH _hoops_HSPR _hoops_CSSC _hoops_IIGR _hoops_SHCA _hoops_CPAP.
 * _hoops_GCACP, _hoops_SR'_hoops_RISP _hoops_HHRSH _hoops_ASCA _hoops_HPGR _hoops_IRS _hoops_PHPA _hoops_PAPA.
 */

local void _hoops_AARHP (
	char const				*which) {

	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, Sprintf_S (null, "Unexpected 'Hide_DC_%s'", which));
}
#endif


GLOBAL_FUNCTION void HD_Hide_DC_Text (
	Net_Rendition const &		nr,
	DC_Point const *			where,
	int							count,
	Karacter const *			kstring) {
#ifndef DISABLE_SORTING_HSR

	UNREFERENCED (nr);
	UNREFERENCED (where);
	UNREFERENCED (count);
	UNREFERENCED (kstring);

	_hoops_AARHP ("Text");
#endif
}


GLOBAL_FUNCTION void HD_Isolate_Tristrip_Data (
	Display_Context const *		dc,
	Tristrip const *			ts) {

	if (BIT (ts->_hoops_SRHA, DL_TEMPORARY_DATA)) {
		/* _hoops_PIH _hoops_IH _hoops_RSSA & _hoops_AIRC _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_AARI _hoops_SPHR, _hoops_HIS _hoops_IPS _hoops_HA */
		Tristrip alter *		_hoops_IHRSH = (Tristrip alter *)ts;

		_hoops_IHRSH->_hoops_SRHA &= ~DL_TEMPORARY_DATA;

		if (ts->points != null && !BIT (ts->_hoops_RAHH, _hoops_AIPI)) {
			Point *		_hoops_HRRGA = ts->points;

			POOL_ALLOC_ARRAY_ALIGNED_CACHED (_hoops_IHRSH->points, ts->point_count, Point, 16, dc->memory_pool);
			_hoops_AIGA (_hoops_HRRGA, ts->point_count, Point, _hoops_IHRSH->points);
			_hoops_IHRSH->_hoops_RAHH |= _hoops_AIPI;
		}

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
#  ifndef _hoops_GCGHR
		if (ts->_hoops_PCHA != null && !BIT (ts->_hoops_RAHH, _hoops_PIPI)) {
			_hoops_CHRSH(ts->_hoops_PCHA, ts->point_count, RGB, _hoops_IHRSH->_hoops_PCHA, dc->memory_pool);
			_hoops_IHRSH->_hoops_RAHH |= _hoops_PIPI;
		}
		if (ts->_hoops_HCHA != null && !BIT (ts->_hoops_RAHH, _hoops_RCGHR)) {
			_hoops_CHRSH(ts->_hoops_HCHA, ts->point_count, _hoops_ACGHR, _hoops_IHRSH->_hoops_HCHA, dc->memory_pool);
			_hoops_IHRSH->_hoops_RAHH |= _hoops_RCGHR;
		}

		if (ts->_hoops_PAGI != null && !BIT (ts->_hoops_RAHH, _hoops_SHRI)) {
			_hoops_CHRSH(ts->_hoops_PAGI, ts->face_count, RGB, _hoops_IHRSH->_hoops_PAGI, dc->memory_pool);
			_hoops_IHRSH->_hoops_RAHH |= _hoops_SHRI;
		}
#  endif
#  ifndef _hoops_HCGHR
		if (ts->_hoops_ICHA != null && !BIT (ts->_hoops_RAHH, _hoops_ICGHR)) {
			_hoops_CHRSH(ts->_hoops_ICHA, ts->point_count, Vector, _hoops_IHRSH->_hoops_ICHA, dc->memory_pool);
			_hoops_IHRSH->_hoops_RAHH |= _hoops_ICGHR;
		}

		if (ts->_hoops_PRHH != null && !BIT (ts->_hoops_RAHH, _hoops_RCPI)) {
			_hoops_ARPA *		_hoops_GCCSA = ts->_hoops_PRHH;

			POOL_ALLOC_ARRAY_ALIGNED_CACHED (_hoops_IHRSH->_hoops_PRHH, ts->face_count, _hoops_ARPA, 16, dc->memory_pool);
			_hoops_AIGA (_hoops_GCCSA, ts->face_count, _hoops_ARPA, _hoops_IHRSH->_hoops_PRHH);
			_hoops_IHRSH->_hoops_RAHH |= _hoops_RCPI;
		}
#  endif
#endif
	}

#  ifndef DISABLE_TEXTURING
	if (ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_CCHA != null &&
		!BIT(ts->_hoops_GSSH->_hoops_SCAI, _hoops_ARCC)) {
		_hoops_CHRSH(ts->_hoops_GSSH->_hoops_CCHA, ts->point_count * ts->_hoops_GSSH->_hoops_GSHA,
								_hoops_RSSH, ts->_hoops_GSSH->_hoops_CCHA, dc->memory_pool);
		ts->_hoops_GSSH->_hoops_CGAHR = ts->point_count;
		ts->_hoops_GSSH->_hoops_SCAI |= _hoops_ARCC;
	}
#  endif
}

GLOBAL_FUNCTION void HD_Isolate_Polymarker_Data (
	Display_Context const *			dc,
	Polymarker const *				pm) {

	if (BIT (pm->_hoops_SRHA, DL_TEMPORARY_DATA)) {
		/* _hoops_PIH _hoops_IH _hoops_RSSA & _hoops_AIRC _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_AARI _hoops_SPHR, _hoops_HIS _hoops_IPS _hoops_HA */
		Polymarker alter *		_hoops_SHRSH = (Polymarker alter *)pm;

		_hoops_SHRSH->_hoops_SRHA &= ~DL_TEMPORARY_DATA;

		if (pm->_hoops_AIHA != null && !BIT (pm->_hoops_RAHH, _hoops_AAHH)) {
			_hoops_CHRSH(pm->_hoops_AIHA, pm->point_count, int, _hoops_SHRSH->_hoops_AIHA, dc->memory_pool);
			_hoops_SHRSH->_hoops_RAHH |= _hoops_AAHH;
		}

		if (pm->points != null && !BIT (pm->_hoops_RAHH, _hoops_AIPI)) {
			Point *		_hoops_HRRGA = pm->points;

			POOL_ALLOC_ARRAY_ALIGNED_CACHED (_hoops_SHRSH->points, pm->point_count, Point, 16, dc->memory_pool);
			_hoops_AIGA (_hoops_HRRGA, pm->point_count, Point, _hoops_SHRSH->points);
			_hoops_SHRSH->_hoops_RAHH |= _hoops_AIPI;
		}

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
#  ifndef _hoops_GCGHR
		if (pm->_hoops_PCHA != null && !BIT (pm->_hoops_RAHH, _hoops_PIPI)) {
			_hoops_CHRSH(pm->_hoops_PCHA, pm->point_count, RGB, _hoops_SHRSH->_hoops_PCHA, dc->memory_pool);
			_hoops_SHRSH->_hoops_RAHH |= _hoops_PIPI;
		}
		if (pm->_hoops_HCHA != null && !BIT (pm->_hoops_RAHH, _hoops_RCGHR)) {
			_hoops_CHRSH(pm->_hoops_HCHA, pm->point_count, _hoops_ACGHR, _hoops_SHRSH->_hoops_HCHA, dc->memory_pool);
			_hoops_SHRSH->_hoops_RAHH |= _hoops_RCGHR;
		}
		if (pm->_hoops_RGIA != null && !BIT (pm->_hoops_RAHH, _hoops_HRRHR)) {
			_hoops_CHRSH(pm->_hoops_RGIA, pm->point_count, RGBAS32, _hoops_SHRSH->_hoops_RGIA, dc->memory_pool);
			_hoops_SHRSH->_hoops_RAHH |= _hoops_HRRHR;
		}
#  endif
#  ifndef _hoops_HCGHR
		if (pm->_hoops_ICHA != null && !BIT (pm->_hoops_RAHH, _hoops_ICGHR)) {
			_hoops_CHRSH(pm->_hoops_ICHA, pm->point_count, Vector, _hoops_SHRSH->_hoops_ICHA, dc->memory_pool);
			_hoops_SHRSH->_hoops_RAHH |= _hoops_ICGHR;
		}
#  endif
#  ifndef DISABLE_TEXTURING
		if (pm->_hoops_CCHA != null && !BIT (pm->_hoops_RAHH, _hoops_CCGHR)) {
			_hoops_CHRSH(pm->_hoops_CCHA, pm->point_count * pm->_hoops_GSHA, _hoops_RSSH, _hoops_SHRSH->_hoops_CCHA, dc->memory_pool);
			_hoops_SHRSH->_hoops_RAHH |= _hoops_CCGHR;
		}
#  endif
#endif
	}
}

/* _hoops_IPCP _hoops_SSH _hoops_PIRA _hoops_ARI _hoops_RGAR _hoops_SIGH _hoops_CGPR _hoops_RH 3d _hoops_CCSHP _hoops_CRHH _hoops_GRS _hoops_SHH _hoops_PISS.  
 * _hoops_IPCP _hoops_IGGA _hoops_HIPH _hoops_HS _hoops_PAII _hoops_HAII _hoops_SSH _hoops_HSH _hoops_SGS _hoops_GRS _hoops_SHH _hoops_GSHHR _hoops_CSCHR _hoops_IS 
 * _hoops_PCPA _hoops_IISA _hoops_GGSR _hoops_IIGR _hoops_CAGCP */
local void _hoops_GIRSH (
	Net_Rendition const &	nr,
	_hoops_SASC const & 	cuboid,
	float alter *			_hoops_RICR,
	float alter *			_hoops_AICR) 
{
	Point _hoops_RIRSH[8];

	cuboid._hoops_GPSC(&_hoops_RIRSH[0]);
	
	float _hoops_RPSC = MAX_FLOAT, _hoops_CGSAA = -MAX_FLOAT;

	_hoops_RPRA const * mat = (_hoops_RPRA const *)nr->transform_rendition->matrix->data.elements;

	for (int i = 0; i < 8; i++) {
		
		float z;

		float w = _hoops_PHCP (mat, _hoops_RIRSH[i]);
		
		if (w < nr->transform_rendition->_hoops_CHCR) {
			z = 0;
		}
		else {
			z = _hoops_CPRA (mat, _hoops_RIRSH[i]);
			z /= w;
		}
			
		if (z < _hoops_RPSC)
			_hoops_RPSC = z;
		if (z > _hoops_CGSAA)
			_hoops_CGSAA = z;
	}
	*_hoops_RICR = _hoops_RPSC;
	*_hoops_AICR = _hoops_CGSAA;
}


GLOBAL_FUNCTION void HD_Hide_3D_Tristrip (
	Net_Rendition const & 		inr,
	Net_Rendition const & 		_hoops_AIRSH,
	Tristrip const *			ts,
	int							flags,
	DC_Point *					_hoops_GHPCP) {
#ifndef DISABLE_SORTING_HSR
	Net_Rendition				nr = inr;
	Display_Context const *		dc = nr->_hoops_SRA;
	Net_Rendition				_hoops_PARHH = _hoops_AIRSH;
	_hoops_CASS alter *				hidden;
	_hoops_SRHSA alter *		_hoops_ASHSA;	
	Hidden_Tristrip alter *		_hoops_ACSIP;

	POOL_ZALLOC (hidden, _hoops_CASS, dc->memory_pool);
	POOL_ZALLOC (_hoops_ACSIP, Hidden_Tristrip, dc->memory_pool);
	POOL_ZALLOC (_hoops_ASHSA, _hoops_SRHSA, dc->memory_pool);
	_hoops_ICAI(_hoops_ASHSA);

	hidden->_hoops_ASHSA = _hoops_ASHSA;
	_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA*)_hoops_ACSIP;
	_hoops_ASHSA->points = _hoops_ACSIP->_hoops_GHPCP = _hoops_GHPCP;

	if (_hoops_GHPCP) {
		POOL_ALLOC_ARRAY_CACHED(_hoops_ACSIP->_hoops_GHPCP, ts->point_count, DC_Point, dc->memory_pool);
		_hoops_AIGA(_hoops_GHPCP, ts->point_count, DC_Point, _hoops_ACSIP->_hoops_GHPCP);
	}
	_hoops_ASHSA->points = _hoops_ACSIP->_hoops_GHPCP;

	_hoops_ACSIP->flags = (_hoops_SHGSH)flags;
	_hoops_ASHSA->type = _hoops_RIGCP;
	if (BIT(ts->_hoops_SRHA, DL_TEMPORARY_DATA))
		HD_Isolate_Tristrip_Data (dc, ts);
	_hoops_ACSIP->tristrips = ts;
	_hoops_CAHS (ts);

	bool	_hoops_IGCIP;

	_hoops_IGCIP = !BIT (nr->_hoops_CPP->_hoops_PRH.options, _hoops_GPAAP);
	if (BIT(nr->transform_rendition->flags, _hoops_ISH) != _hoops_IGCIP) {
		if (_hoops_IGCIP)
			nr.Modify()->transform_rendition.Modify(_hoops_HRCIP)->flags |= _hoops_ISH;
		else
			nr.Modify()->transform_rendition.Modify(_hoops_HRCIP)->flags &= ~_hoops_ISH;
	}

	if (_hoops_PARHH != null) {
		if (!BIT(_hoops_PARHH->transform_rendition->flags, _hoops_ISH) != _hoops_IGCIP) {
			if (_hoops_IGCIP)
				_hoops_PARHH.Modify()->transform_rendition.Modify(_hoops_HRCIP)->flags |= _hoops_ISH;
			else
				_hoops_PARHH.Modify()->transform_rendition.Modify(_hoops_HRCIP)->flags &= ~_hoops_ISH;
		}
		_hoops_ACSIP->_hoops_PARHH = _hoops_PARHH;
	}
	if (nr->_hoops_SRA->_hoops_RAI != null)
		hidden->values = nr->_hoops_SRA->_hoops_RAI->priority;

	if (dc->_hoops_ICACP && (dc->_hoops_ICACP == ts->face_count) ) {
		POOL_ALLOC_ARRAY_ALIGNED_CACHED (_hoops_ACSIP->_hoops_AGHAR, ts->face_count, int, 16, dc->memory_pool);
		_hoops_AIGA (dc->_hoops_CGHAR, ts->face_count, int, _hoops_ACSIP->_hoops_AGHAR);
	}
	if (dc->_hoops_PGPCP && dc->_hoops_PAHCP >= ts->point_count){
		POOL_ALLOC_ARRAY_CACHED (_hoops_ACSIP->_hoops_AARHH, ts->point_count, _hoops_ARPA, dc->memory_pool);
		_hoops_AIGA (dc->_hoops_PGPCP, ts->point_count, _hoops_ARPA, _hoops_ACSIP->_hoops_AARHH);
	}
	if (dc->_hoops_AIACP && dc->_hoops_PIACP >= ts->face_count){
		POOL_ALLOC_ARRAY_CACHED (_hoops_ACSIP->_hoops_RIACP, ts->face_count, _hoops_ARPA, dc->memory_pool);
		_hoops_AIGA (dc->_hoops_AIACP, ts->face_count, _hoops_ARPA, _hoops_ACSIP->_hoops_RIACP);
	}
	if (ts->bounding == null)
		_hoops_PGRCA(ts)->bounding = Bounding::Create(ts->point_count, ts->points);
	_hoops_GIRSH (nr, ts->bounding->cuboid, &hidden->_hoops_ASHSA->_hoops_RICR, &hidden->_hoops_ASHSA->_hoops_AICR);

	bool _hoops_PIRSH = 
		(BIT (nr->transform_rendition->flags, _hoops_IGSP) &&
		 ANYBIT (nr->transform_rendition->heuristics, _hoops_RSA));

	if (!nr->_hoops_CPP->_hoops_PRH._hoops_RGGIP || _hoops_PIRSH)  {
		_hoops_ASHSA->_hoops_APHGA = nr;
		_hoops_ACSIP->_hoops_APHGA = nr;
		HD_Insert_In_Hidden_Tree (hidden);
	}
	else {
		_hoops_CASS *_hoops_HIRSH;
		_hoops_HHCR alter _hoops_GGCC = nr.Modify()->transform_rendition.Modify();
		_hoops_ASHSA->_hoops_APHGA = nr;
		_hoops_ACSIP->_hoops_APHGA = nr;

		POOL_ZALLOC (_hoops_HIRSH, _hoops_CASS, dc->memory_pool);
		_hoops_HIRSH->_hoops_ASHSA = _hoops_ASHSA;
		_hoops_CAHS (_hoops_ASHSA);
		_hoops_HIRSH->values = hidden->values;
		_hoops_HIRSH->flags = hidden->flags;
		_hoops_HIRSH->flags |= HF_ZSORT_BACKFACE;
		HD_Insert_In_Hidden_Tree (_hoops_HIRSH);

		hidden->flags |= HF_ZSORT_FRONTFACE;
		HD_Insert_In_Hidden_Tree (hidden);
	}
#endif
}

GLOBAL_FUNCTION void HD_Hide_3D_Polymarker (
	Net_Rendition const & 		inr,
	Polymarker const *			pm,
	int							flags,
	DC_Point *					_hoops_GHPCP) {
#ifndef DISABLE_SORTING_HSR
	Net_Rendition				nr = inr;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_CASS alter *				hidden;
	_hoops_SRHSA alter *		_hoops_ASHSA;	
	_hoops_PGRCP alter *	_hoops_RGRHR;

	UNREFERENCED (flags);

	POOL_ZALLOC (hidden, _hoops_CASS, dc->memory_pool);
	POOL_ZALLOC (_hoops_RGRHR, _hoops_PGRCP, dc->memory_pool);
	POOL_ZALLOC (_hoops_ASHSA, _hoops_SRHSA, dc->memory_pool);
	_hoops_ICAI(_hoops_ASHSA);

	hidden->_hoops_ASHSA = _hoops_ASHSA;
	_hoops_ASHSA->_hoops_GPHSA = (_hoops_APHSA*)_hoops_RGRHR;
	_hoops_ASHSA->points = _hoops_RGRHR->_hoops_GHPCP = _hoops_GHPCP;

	if (_hoops_GHPCP) {
		POOL_ALLOC_ARRAY_CACHED(_hoops_RGRHR->_hoops_GHPCP, pm->point_count, DC_Point, dc->memory_pool);
		_hoops_AIGA(_hoops_GHPCP, pm->point_count, DC_Point, _hoops_RGRHR->_hoops_GHPCP);
	}
	_hoops_ASHSA->points = _hoops_RGRHR->_hoops_GHPCP;

	_hoops_ASHSA->type = _hoops_HIGCP;
	HD_Isolate_Polymarker_Data (dc, pm);
	_hoops_RGRHR->_hoops_GIGPR = pm;
	_hoops_CAHS (pm);

	if (!BIT(nr->transform_rendition->flags, _hoops_ISH))
		nr.Modify()->transform_rendition.Modify(_hoops_HRCIP)->flags |= _hoops_ISH;

	_hoops_ASHSA->_hoops_APHGA = nr;
	_hoops_RGRHR->_hoops_APHGA = nr;

	if (nr->_hoops_SRA->_hoops_RAI != null)
		hidden->values = nr->_hoops_SRA->_hoops_RAI->priority;

	_hoops_GIRSH (nr, pm->bounding->cuboid, &hidden->_hoops_ASHSA->_hoops_RICR, &hidden->_hoops_ASHSA->_hoops_AICR);
	HD_Insert_In_Hidden_Tree (hidden);
#endif
}

GLOBAL_FUNCTION void HD_Isolate_Polyedge_Data (
	Display_Context const *		dc,
	Polyedge const *			pe) {
	Polyedge alter *			_hoops_IIRSH = (Polyedge alter *)pe;

	if (BIT (pe->_hoops_SRHA, DL_TEMPORARY_DATA)) {
		/* _hoops_PIH _hoops_IH _hoops_RSSA & _hoops_AIRC _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_AARI _hoops_SPHR, _hoops_HIS _hoops_IPS _hoops_HA */

		_hoops_IIRSH->_hoops_SRHA &= ~DL_TEMPORARY_DATA;

		if (pe->points != null && !BIT (pe->_hoops_RAHH, _hoops_AIPI)) {
			Point *		_hoops_HRRGA = pe->points;

			POOL_ALLOC_ARRAY_ALIGNED_CACHED (_hoops_IIRSH->points, pe->point_count, Point, 16, dc->memory_pool);
			_hoops_AIGA (_hoops_HRRGA, pe->point_count, Point, _hoops_IIRSH->points);
			_hoops_IIRSH->_hoops_RAHH |= _hoops_AIPI;
		}


#ifndef DISABLE_GEOMETRY_ATTRIBUTES
#  ifndef _hoops_GCGHR
		if (pe->_hoops_PCHA != null) {
			_hoops_CHRSH(pe->_hoops_PCHA, pe->point_count, RGB, _hoops_IIRSH->_hoops_PCHA, dc->memory_pool);
			_hoops_IIRSH->_hoops_RAHH |= _hoops_PIPI;
		}
		if (pe->_hoops_HCHA != null) {
			_hoops_CHRSH(pe->_hoops_HCHA, pe->point_count, _hoops_ACGHR, _hoops_IIRSH->_hoops_HCHA, dc->memory_pool);
			_hoops_IIRSH->_hoops_RAHH |= _hoops_RCGHR;
		}

		if (pe->_hoops_ASHA != null) {
			_hoops_CHRSH(pe->_hoops_ASHA, pe->_hoops_SPHA, RGB, _hoops_IIRSH->_hoops_ASHA, dc->memory_pool);
			_hoops_IIRSH->_hoops_RAHH |= _hoops_PCGHR;
		}
#  endif
#  ifndef _hoops_HCGHR
		if (pe->_hoops_ICHA != null) {
			_hoops_CHRSH(pe->_hoops_ICHA, pe->point_count, Vector, _hoops_IIRSH->_hoops_ICHA, dc->memory_pool);
			_hoops_IIRSH->_hoops_RAHH |= _hoops_ICGHR;
		}

		if (pe->_hoops_RSHA != null) {
			Vector *		_hoops_CIRSH = pe->_hoops_RSHA;

			POOL_ALLOC_ARRAY_CACHED (_hoops_IIRSH->_hoops_RSHA, pe->_hoops_SPHA, Vector, dc->memory_pool);
			_hoops_AIGA (_hoops_CIRSH, pe->_hoops_SPHA, Vector, _hoops_IIRSH->_hoops_RSHA);
			_hoops_IIRSH->_hoops_RAHH |= _hoops_GHII;
		}
#  endif
#  ifndef DISABLE_TEXTURING
		if (pe->_hoops_CCHA != null) {
			_hoops_CHRSH(pe->_hoops_CCHA, pe->point_count * pe->_hoops_GSHA, _hoops_RSSH, _hoops_IIRSH->_hoops_CCHA, dc->memory_pool);
			_hoops_IIRSH->_hoops_RAHH |= _hoops_CCGHR;
		}
#  endif
#endif
	}
}





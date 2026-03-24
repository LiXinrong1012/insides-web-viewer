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
 * $Id: obf_tmp.txt 1.57 2010-11-25 00:20:15 jason Exp $
 * 
 * This file is used to define the HC_D* functions 
 */


#ifndef _hoops_HPAIH

#define V_PREFIX HOOPS_HCD_


#include "utility/vlist.h"
#include "utility/vlist.cpp"
#include "utility/vhash.h"
#include "utility/vhash.cpp"

#define BUILDING_HCD_INTERNALS
#include "hcd.h"

#undef HC_Delete_By_Key
#undef HC_Delete_Segment
#undef HC_Flush_By_Key
#undef HC_Flush_Segment
#undef HC_Flush_Contents
#undef HC_Flush_Geometry
#undef HC_Renumber_Key
#undef HC_KRenumber_Key

#include <stdlib.h>
#include <string.h>
#include <math.h>




// _hoops_AGCR _hoops_CHR _hoops_HAR _hoops_GHGA _hoops_RHSHP
#define ALLOC_ARRAY_ALIGNED(var, count, type, align_in) \
	(var) = (type *)malloc(sizeof(type)*count);

#define FREE_ARRAY_ALIGNED(var, count, type, align_in) \
	free(var);

#define ALLOC_ARRAY(var, count, type) \
	(var) = (type *)malloc(sizeof(type)*count);

#define FREE_ARRAY(var, count, type) \
	free(var);

#define ALLOC(var, type) \
	(var) = (type *)malloc(sizeof(type));

#define FREE(var, type) \
	free(var);

#ifndef SET_MEMORY
#	define		SET_MEMORY(_dst_, _hoops_IPAIH, _hoops_CPAIH)		memset(_dst_, _hoops_CPAIH, _hoops_IPAIH)
#endif
#define	ZERO_STRUCT(_dst_, _type_)					SET_MEMORY (_dst_, sizeof(_type_), 0)
#define	ZERO_ARRAY(_dst_, _cnt_, _type_)			SET_MEMORY (_dst_, (_cnt_) * sizeof(_type_), 0)

#ifndef COPY_MEMORY
#	define		COPY_MEMORY(_hoops_SPAIH, _hoops_IPAIH, _dst_)	memcpy(_dst_, _hoops_SPAIH, _hoops_IPAIH)
#endif
#define	_hoops_RSAI(_hoops_SPAIH, _type_, _dst_)			COPY_MEMORY (_hoops_SPAIH, sizeof(_type_), _dst_)
#define	_hoops_AIGA(_hoops_SPAIH, _cnt_, _type_, _dst_)		COPY_MEMORY (_hoops_SPAIH, (_cnt_) * sizeof(_type_), _dst_)

#define Abs (_hoops_GHAIH) (((_hoops_GHAIH)<0)?-(_hoops_GHAIH):(_hoops_GHAIH))

#define UNREFERENCED(param) ((void)(param))

#define _hoops_AGGR(_hoops_RHAIH,_hoops_AHAIH)				(!strcmp(_hoops_RHAIH,_hoops_AHAIH))

typedef void (HC_CDECL * _hoops_IRPCR) (HC_ANY_ARGS);

#	pragma warning (disable: 4996)	// _hoops_HPRGR _hoops_GSGR _hoops_PSCH _hoops_GHSAR _hoops_HGPSA

struct _hoops_APCIR {
	double		x, y, z;
};

struct _hoops_PHAIH {

	double		*_hoops_HHAIH, *_hoops_GIGCR, *_hoops_RIGCR, *d3;
	HC_KEY		key;
	int			_hoops_IHAIH, _hoops_HRPPA, _hoops_SPPPA, _hoops_CHAIH;

};

#include "utility/vhash.h"


typedef VHash<HC_KEY, _hoops_PHAIH *> _hoops_SHAIH;

#ifndef SYSTEM_NEW
#define SYSTEM_NEW new
#endif

#define _hoops_GIAIH			1024

static _hoops_SHAIH * global_hcd_table = 0;

static _hoops_SHAIH * _hoops_RIAIH() 
{
	if (global_hcd_table == 0)
		global_hcd_table = SYSTEM_NEW _hoops_SHAIH(_hoops_GIAIH);
	return (_hoops_SHAIH*)global_hcd_table;
}

static double *_hoops_AIAIH (const double *d, int len)
{
	double *_hoops_PAGR;

	if (d == 0 || len == 0) 
		return 0;
	ALLOC_ARRAY_ALIGNED (_hoops_PAGR, len, double, 8);
	_hoops_AIGA (d, len, double, _hoops_PAGR);
	return _hoops_PAGR;
}

static void _hoops_PIAIH (double *_hoops_PCAP, const double *src, int size) 
{
	_hoops_AIGA (src, size, double, _hoops_PCAP);
}


/* _hoops_PGAA
 * _hoops_IPS _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_HIAIH _hoops_CRGR _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_PHRP. 
 * _hoops_PIP _hoops_SGS _hoops_RH _hoops_CIS _hoops_SSCP _hoops_CSSAR _hoops_IS _hoops_CIH _hoops_RH _hoops_PPGS */
static float *_hoops_IIAIH (const double *d, int len)
{
	float *_hoops_PAGR;
	float *_hoops_PPHPA;
	const double *_hoops_CIAIH, *end;

	if (d == 0 || len == 0) 
		return 0;
	ALLOC_ARRAY (_hoops_PAGR, len, float);
	_hoops_PPHPA = _hoops_PAGR;
	_hoops_CIAIH = d;
	end = d + len;
	while (_hoops_CIAIH < end)
		*_hoops_PPHPA++ = (float) *_hoops_CIAIH++;
	return _hoops_PAGR;
}


static void _hoops_SIAIH (
		HC_KEY key, 
		int _hoops_IHAIH, double *_hoops_HHAIH, 
		int _hoops_HRPPA, double *_hoops_GIGCR, 
		int _hoops_SPPPA, double *_hoops_RIGCR,
		int _hoops_CHAIH, double *d3)
{
	_hoops_PHAIH *container;

	ALLOC (container, _hoops_PHAIH);
	container->key = key;
	container->_hoops_IHAIH = _hoops_IHAIH;
	container->_hoops_HRPPA = _hoops_HRPPA;
	container->_hoops_SPPPA = _hoops_SPPPA;
	container->_hoops_CHAIH = _hoops_CHAIH;
	container->_hoops_HHAIH = _hoops_HHAIH;
	container->_hoops_GIGCR = _hoops_GIGCR;
	container->_hoops_RIGCR = _hoops_RIGCR;
	container->d3 = d3;

	_hoops_RIAIH()->InsertItem(key, container);
}


static void _hoops_GCAIH (_hoops_PHAIH *node)
{
	if (node == 0)
		return;

	if (node->_hoops_HHAIH)
		FREE_ARRAY_ALIGNED (node->_hoops_HHAIH, node->_hoops_IHAIH, double, 8);
	if (node->_hoops_GIGCR)
		FREE_ARRAY_ALIGNED (node->_hoops_GIGCR, node->_hoops_HRPPA, double, 8);
	if (node->_hoops_RIGCR)
		FREE_ARRAY_ALIGNED (node->_hoops_RIGCR, node->_hoops_SPPPA, double, 8);
	if (node->d3)
		FREE_ARRAY_ALIGNED (node->d3, node->_hoops_CHAIH, double, 8);
	FREE (node, _hoops_PHAIH);
}


static void _hoops_RCAIH (HC_KEY key)
{
	_hoops_PHAIH *node = 0;

	if (!global_hcd_table)
		return;

	_hoops_RIAIH()->RemoveItem(key, &node);

	_hoops_GCAIH (node);
}

/* 
 * _hoops_CAICR
 */


HC_EXTERNAL HD_API void HC_DSet_Camera (
		const HCD_POINT *position, 
		const HCD_POINT *target, 
		const HCD_POINT *up, 
		double width, 
		double height, 
		const char *projection)
{
	_hoops_PHAIH *node = 0;
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 11, double, 8);
	ZERO_ARRAY (_hoops_HHAIH, 11, double);
	_hoops_AIGA ((double *)position, 3, double, _hoops_HHAIH);
	_hoops_AIGA ((double *)target, 3, double, _hoops_HHAIH+3);
	_hoops_AIGA ((double *)up, 3, double, _hoops_HHAIH+6);
	_hoops_HHAIH[9] = width;
	_hoops_HHAIH[10] = height;
	_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, 3);
	f1 = _hoops_IIAIH (_hoops_HHAIH+3, 3);
	f2 = _hoops_IIAIH (_hoops_HHAIH+6, 3);

	/* _hoops_SRPS _hoops_RH _hoops_SIC _hoops_IS _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH */
	key = HC_KOpen_Segment (".");
	HC_Close_Segment();

	_hoops_RIAIH()->LookupItem(key, &node);

	if (node == 0) {
		_hoops_SIAIH (key, 11,_hoops_HHAIH, 0,0,0,0,0,0);
	}
	else {
		FREE_ARRAY_ALIGNED (node->_hoops_HHAIH, 11, double, 8);
		node->_hoops_HHAIH = _hoops_HHAIH;
	}
	HC_Set_Camera (_hoops_AIPCP, f1, f2, width, height, projection);
	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, 3, float);
	if (f1 != 0) FREE_ARRAY (f1, 3, float);
	if (f2 != 0) FREE_ARRAY (f2, 3, float);
}


HC_EXTERNAL HD_API void HC_DSet_Camera_Position (
		double x, 
		double y, 
		double z)
{
	_hoops_PHAIH *node = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	/* _hoops_SRPS _hoops_RH _hoops_SIC _hoops_IS _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH */
	key = HC_KOpen_Segment (".");
	HC_Close_Segment();

	_hoops_RIAIH()->LookupItem(key, &node);

	if (node == 0) {
		ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 11, double, 8);
		ZERO_ARRAY (_hoops_HHAIH, 11, double);
		_hoops_SIAIH (key, 11,_hoops_HHAIH, 0,0,0,0,0,0);
	}
	else {
		_hoops_HHAIH = node->_hoops_HHAIH;
	}
	_hoops_HHAIH[0] = x;
	_hoops_HHAIH[1] = y;
	_hoops_HHAIH[2] = z;
	HC_Set_Camera_Position (x, y, z);
}


HC_EXTERNAL HD_API void HC_DSet_Camera_Target (
		double x, 
		double y, 
		double z)
{
	_hoops_PHAIH *node = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	/* _hoops_SRPS _hoops_RH _hoops_SIC _hoops_IS _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH */
	key = HC_KOpen_Segment (".");
	HC_Close_Segment();

	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) {
		ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 11, double, 8);
		ZERO_ARRAY (_hoops_HHAIH, 11, double);
		_hoops_SIAIH (key, 11,_hoops_HHAIH, 0,0,0,0,0,0);
	}
	else {
		_hoops_HHAIH = node->_hoops_HHAIH;
	}
	_hoops_HHAIH[3] = x;
	_hoops_HHAIH[4] = y;
	_hoops_HHAIH[5] = z;
	HC_Set_Camera_Target (x, y, z);
}


HC_EXTERNAL HD_API void HC_DSet_Camera_Up_Vector (
		double x, 
		double y, 
		double z)
{
	_hoops_PHAIH *node = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	/* _hoops_SRPS _hoops_RH _hoops_SIC _hoops_IS _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH */
	key = HC_KOpen_Segment (".");
	HC_Close_Segment();

	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) {
		ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 11, double, 8);
		ZERO_ARRAY (_hoops_HHAIH, 11, double);
		_hoops_SIAIH (key, 11,_hoops_HHAIH, 0,0,0,0,0,0);
	}
	else {
		_hoops_HHAIH = node->_hoops_HHAIH;
	}
	_hoops_HHAIH[6] = x;
	_hoops_HHAIH[7] = y;
	_hoops_HHAIH[8] = z;
	HC_Set_Camera_Up_Vector (x, y, z);
}


HC_EXTERNAL HD_API void HC_DSet_Camera_Field (
		double w, 
		double h)
{
	_hoops_PHAIH *node = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	/* _hoops_SRPS _hoops_RH _hoops_SIC _hoops_IS _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH */
	key = HC_KOpen_Segment (".");
	HC_Close_Segment();

	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) {
		ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 11, double, 8);
		ZERO_ARRAY (_hoops_HHAIH, 11, double);
		_hoops_SIAIH (key, 11,_hoops_HHAIH, 0,0,0,0,0,0);
	}
	else {
		_hoops_HHAIH = node->_hoops_HHAIH;
	}
	_hoops_HHAIH[9]  = w;
	_hoops_HHAIH[10] = h;
	HC_Set_Camera_Field (w, h);
}


HC_EXTERNAL HD_API void HC_DShow_Camera (
		HCD_POINT *position, 
		HCD_POINT *target, 
		HCD_POINT *up, 
		double *width, 
		double *height, 
		char *projection)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_ERROR_KEY;

	
	
	/* _hoops_SRPS _hoops_RH _hoops_SIC _hoops_IS _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH */
	key = HC_KOpen_Segment (".");
	HC_Close_Segment();

	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;

	if (position)
		_hoops_AIGA (node->_hoops_HHAIH+0, 3, double, (double *)position);
	if (target)
		_hoops_AIGA (node->_hoops_HHAIH+3, 3, double, (double *)target);
	if (up)
		_hoops_AIGA (node->_hoops_HHAIH+6, 3, double, (double *)up);
	if (width)
		*width = node->_hoops_HHAIH[9];
	if (height)
		*height = node->_hoops_HHAIH[10];
	HC_Show_Camera (0, 0, 0, 0, 0, projection);
}


HC_EXTERNAL HD_API void HC_DShow_Camera_Position (
		double *x, 
		double *y, 
		double *z)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_ERROR_KEY;

	
	
	/* _hoops_SRPS _hoops_RH _hoops_SIC _hoops_IS _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH */
	key = HC_KOpen_Segment (".");
	HC_Close_Segment();

	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;

	if (x)
		*x = node->_hoops_HHAIH[0];
	if (y)
		*y = node->_hoops_HHAIH[1];
	if (z)
		*z = node->_hoops_HHAIH[2];
}


HC_EXTERNAL HD_API void HC_DShow_Camera_Target (
		double *x, 
		double *y, 
		double *z)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_ERROR_KEY;

	
	
	/* _hoops_SRPS _hoops_RH _hoops_SIC _hoops_IS _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH */
	key = HC_KOpen_Segment (".");
	HC_Close_Segment();

	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;

	if (x)
		*x = node->_hoops_HHAIH[3];
	if (y)
		*y = node->_hoops_HHAIH[4];
	if (z)
		*z = node->_hoops_HHAIH[5];
}


HC_EXTERNAL HD_API void HC_DShow_Camera_Up_Vector (
		double *x, 
		double *y, 
		double *z)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_ERROR_KEY;

	
	
	/* _hoops_SRPS _hoops_RH _hoops_SIC _hoops_IS _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH */
	key = HC_KOpen_Segment (".");
	HC_Close_Segment();

	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;

	if (x)
		*x = node->_hoops_HHAIH[6];
	if (y)
		*y = node->_hoops_HHAIH[7];
	if (z)
		*z = node->_hoops_HHAIH[8];
}


HC_EXTERNAL HD_API void HC_DShow_Camera_Field (
		double *w, 
		double *h)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_ERROR_KEY;

	
	
	/* _hoops_SRPS _hoops_RH _hoops_SIC _hoops_IS _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH */
	key = HC_KOpen_Segment (".");
	HC_Close_Segment();

	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;

	if (w)
		*w = node->_hoops_HHAIH[9];
	if (h)
		*h = node->_hoops_HHAIH[10];
}


/* 
 * _hoops_IRCPH _hoops_AARAR
 */
HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_NURBS_Surface(
				const char		*segment,
				int				u_degree,
				int				v_degree,
				int				width,
				int				height,
				const HCD_POINT *control_points,
				const double	*weights,
				const double	*u_knots,
				const double	*v_knots)
{
	int _hoops_RSPIR = u_degree + width + 1;
	int _hoops_ASPIR = v_degree + height + 1;
	int _hoops_IHAIH = 0, _hoops_HRPPA = 0, _hoops_SPPPA = 0, _hoops_CHAIH = 0;
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0, *_hoops_CGHGR = 0;
	double *_hoops_HHAIH = 0, *_hoops_GIGCR = 0, *_hoops_RIGCR = 0, *d3 = 0;
	HC_KEY key;

	

	if (control_points != 0) {
		_hoops_IHAIH = 3 * width * height;
		_hoops_HHAIH = _hoops_AIAIH ((double *)control_points, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}
	if (weights != 0) {
		_hoops_HRPPA = width * height;
		_hoops_GIGCR = _hoops_AIAIH (weights, _hoops_HRPPA);
		f1 = _hoops_IIAIH (_hoops_GIGCR, _hoops_HRPPA);
	}
	if (u_knots != 0) {
		_hoops_SPPPA = _hoops_RSPIR;
		_hoops_RIGCR = _hoops_AIAIH (u_knots, _hoops_SPPPA);
		f2 = _hoops_IIAIH (_hoops_RIGCR, _hoops_SPPPA); 
	}
	if (v_knots != 0) {
		_hoops_CHAIH = _hoops_ASPIR;
		d3 = _hoops_AIAIH (v_knots, _hoops_CHAIH);
		_hoops_CGHGR = _hoops_IIAIH (d3, _hoops_CHAIH); 
	}
	key = HC_QKInsert_NURBS_Surface  (
				segment, 
				u_degree, v_degree,
				width, height,
				_hoops_AIPCP, f1, f2, _hoops_CGHGR);

	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, _hoops_HRPPA, _hoops_GIGCR, _hoops_SPPPA, _hoops_RIGCR, _hoops_CHAIH, d3);

	if (_hoops_AIPCP) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);
	if (f1) FREE_ARRAY (f1, _hoops_HRPPA, float);
	if (f2) FREE_ARRAY (f2, _hoops_SPPPA, float);
	if (_hoops_CGHGR) FREE_ARRAY (_hoops_CGHGR, _hoops_CHAIH, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_ACAIH */

HC_EXTERNAL HD_API void HC_DEdit_NURBS_Surface (
				HC_KEY			_hoops_PCAIH,
				int				control_point_offset,
				int				weight_offset,
				int				u_knot_offset,
				int				v_knot_offset,
				int				control_point_replace_count,
				int				weight_replace_count,
				int				u_knot_replace_count,
				int				v_knot_replace_count,
				const HCD_POINT  *control_points,
				const double	*weights,
				const double	*u_knots,
				const double	*v_knots)
{
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0, *_hoops_CGHGR = 0;
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	

	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) 
		return;

	if (control_points != 0) {
		_hoops_AIPCP = _hoops_IIAIH ((double *)control_points, control_point_replace_count*3);
		_hoops_AIGA ((double *)control_points, control_point_replace_count, double, node->_hoops_HHAIH+(control_point_offset*3));
	}
	if (weights != 0) {
		f1 = _hoops_IIAIH (weights, weight_replace_count);
		_hoops_AIGA (weights, weight_replace_count, double, node->_hoops_GIGCR + weight_offset);
	}
	if (u_knots != 0) {
		f2 = _hoops_IIAIH (u_knots, u_knot_replace_count);
		_hoops_AIGA (u_knots, u_knot_replace_count, double, node->_hoops_RIGCR + u_knot_offset);
	}
	if (v_knots != 0) {
		_hoops_CGHGR = _hoops_IIAIH (v_knots, v_knot_replace_count);
		_hoops_AIGA (v_knots, v_knot_replace_count, double, node->d3 + v_knot_offset);
	}

	HC_Edit_NURBS_Surface (
				key, 
				control_point_offset,
				weight_offset,
				u_knot_offset,
				v_knot_offset,
				control_point_replace_count,
				weight_replace_count,
				u_knot_replace_count,
				v_knot_replace_count,
				_hoops_AIPCP, f1, f2, _hoops_CGHGR
	);

	if (_hoops_AIPCP) FREE_ARRAY (_hoops_AIPCP, control_point_replace_count*3, float);
	if (f1) FREE_ARRAY (f1, weight_replace_count, float);
	if (f2) FREE_ARRAY (f2, u_knot_replace_count, float);
	if (_hoops_CGHGR) FREE_ARRAY (_hoops_CGHGR, v_knot_replace_count, float);

} /* _hoops_RSGR _hoops_API _hoops_HCAIH */


HC_EXTERNAL HD_API void HC_DShow_NURBS_Surface(
				HC_KEY	  _hoops_PCAIH,
				int		  *u_degree,
				int		  *v_degree,
				int		  *width,
				int		  *height,
				HCD_POINT  *control_points,
				double	  *weights,
				double	  *u_knots,
				double	  *v_knots)
{
	_hoops_PHAIH *node = 0;
	int i, _hoops_SHSCA, _hoops_ACCHH, w, h, _hoops_RSPIR, _hoops_ASPIR;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_NURBS_Surface  (
				key,
				&_hoops_SHSCA, &_hoops_ACCHH, &w, &h,
				0, 0, 0, 0
	);
	if (u_degree != 0) *u_degree = _hoops_SHSCA;
	if (v_degree != 0) *v_degree = _hoops_ACCHH;
	if (width != 0) *width = w;
	if (height != 0) *height = h;
	_hoops_RSPIR = _hoops_SHSCA + w + 1;
	_hoops_ASPIR = _hoops_ACCHH + h + 1;
	if (node == 0) return;

	_hoops_AIGA (node->_hoops_HHAIH, node->_hoops_IHAIH, double, control_points);

	if ((weights != 0) && (node->_hoops_GIGCR == 0)) {
		/* _hoops_SHIR _hoops_HSH */
		for (i = 0; i < w*h; i++)
			weights[i] = 1.0;
	}
	else
		_hoops_AIGA (node->_hoops_GIGCR, node->_hoops_HRPPA, double, weights);

	if ((u_knots != 0) && (node->_hoops_RIGCR == 0)) {
		/* _hoops_SHIR _hoops_HSH */
		for (i = 0; i < _hoops_RSPIR; i++)
			u_knots[i] = (double) i;
	}
	else
		_hoops_AIGA (node->_hoops_RIGCR, node->_hoops_SPPPA, double, u_knots);

	if ((v_knots != 0) && (node->_hoops_RIGCR == 0)) {
		/* _hoops_SHIR _hoops_HSH */
		for (i = 0; i < _hoops_ASPIR; i++)
			v_knots[i] = (double) i;
	}
	else
		_hoops_AIGA (node->d3, node->_hoops_CHAIH, double, v_knots);

} /* _hoops_RSGR _hoops_API _hoops_ICAIH */


/*
 * _hoops_IRCPH _hoops_GRRC
 */

HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_NURBS_Curve(
				const char		*segment,
				int				degree,
				int				control_point_count,
				const HCD_POINT  *control_points,
				const double	*weights,
				const double	*knots,
				double			start_u,
				double			end_u)
{
	int knot_count = degree + control_point_count + 1;
	int _hoops_IHAIH = 0, _hoops_HRPPA = 0, _hoops_SPPPA = 0, _hoops_CHAIH = 0;
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0, *_hoops_CGHGR = 0;
	double *_hoops_HHAIH = 0, *_hoops_GIGCR = 0, *_hoops_RIGCR = 0, *d3 = 0;
	HC_KEY key;



	_hoops_IHAIH = control_point_count*3;
	_hoops_HHAIH = _hoops_AIAIH ((double *)control_points, _hoops_IHAIH);
	_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	if (weights != 0) {
		_hoops_HRPPA = control_point_count;
		_hoops_GIGCR = _hoops_AIAIH (weights, _hoops_HRPPA);
		f1 = _hoops_IIAIH (_hoops_GIGCR, _hoops_HRPPA);
	}
	if (knots != 0) {
		_hoops_SPPPA = knot_count;
		_hoops_RIGCR = _hoops_AIAIH (knots, _hoops_SPPPA);
		f2 = _hoops_IIAIH (_hoops_RIGCR, _hoops_SPPPA);
	}
	_hoops_CHAIH = 2;
	ALLOC_ARRAY_ALIGNED (d3, 2, double, 8);
	d3[0] = start_u;
	d3[1] = end_u;

	key = HC_QKInsert_NURBS_Curve (
				segment, 
				degree, control_point_count, 
				_hoops_AIPCP, f1, f2, 
				start_u, end_u);

	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, _hoops_HRPPA, _hoops_GIGCR, _hoops_SPPPA, _hoops_RIGCR, _hoops_CHAIH, d3);

	if (_hoops_AIPCP) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);
	if (f1) FREE_ARRAY (f1, _hoops_HRPPA, float);
	if (f2) FREE_ARRAY (f2, _hoops_SPPPA, float);
	if (_hoops_CGHGR) FREE_ARRAY (_hoops_CGHGR, _hoops_CHAIH, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_CCAIH */


HC_EXTERNAL HD_API void HC_DEdit_NURBS_Curve (
				HC_KEY			_hoops_PCAIH,
				int				control_point_offset,
				int				knot_offset,
				int				control_point_replace_count,
				int				knot_replace_count,
				const HCD_POINT  *control_points,
				const double	*weights,
				const double	*knots)
{
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0;
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	

	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0)  return;

	if (control_points && control_point_replace_count) {
		_hoops_AIPCP = _hoops_IIAIH ((double *)control_points, control_point_replace_count*3); 
		_hoops_AIGA ((double *)control_points, control_point_replace_count*3, double, node->_hoops_HHAIH + (control_point_offset*3));
	}
	if (weights && control_point_replace_count) {
		f1 = _hoops_IIAIH (weights, control_point_replace_count); 
		_hoops_AIGA (weights, control_point_replace_count, double, node->_hoops_GIGCR + control_point_offset);
	}
	if (knots != 0) {
		f2 = _hoops_IIAIH (knots, knot_replace_count);
		_hoops_AIGA (knots, knot_replace_count, double, node->_hoops_RIGCR + knot_offset);
	}

	HC_Edit_NURBS_Curve  (
				key, 
				control_point_offset,
				knot_offset,
				control_point_replace_count,
				knot_replace_count,
				_hoops_AIPCP, f1, f2
	);

	if (_hoops_AIPCP) FREE_ARRAY (_hoops_AIPCP, control_point_replace_count*3, float);
	if (f1) FREE_ARRAY (f1, control_point_replace_count, float);
	if (f2) FREE_ARRAY (f2, knot_replace_count, float);

} /* _hoops_RSGR _hoops_API _hoops_SCAIH */


HC_EXTERNAL HD_API void HC_DShow_NURBS_Curve(
				HC_KEY	  _hoops_PCAIH,
				int		  *degree,
				int		  *control_point_count,
				HCD_POINT  *control_points,
				double	  *weights,
				double	  *knots,
				double	  *start_u,
				double	  *end_u)
{
	_hoops_PHAIH *node = 0;
	int i, _hoops_GSAIH, _hoops_RSAIH, knot_count;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_NURBS_Curve (
				key, 
				&_hoops_GSAIH, &_hoops_RSAIH, 
				0, 0, 0, 
				0, 0
	);
	if (degree != 0) 
		*degree = _hoops_GSAIH;
	if (control_point_count != 0) 
		*control_point_count = _hoops_RSAIH;
	knot_count = _hoops_RSAIH + _hoops_GSAIH + 1;
	if (node == 0) 
		return;

	_hoops_AIGA (node->_hoops_HHAIH, node->_hoops_IHAIH, double, (double *)control_points);

	if ((weights != 0) && (node->_hoops_GIGCR == 0))
		/* _hoops_SHIR _hoops_HSH */
		for (i = 0; i < _hoops_RSAIH; i++)
			weights[i] = 1.0;
	else
		_hoops_AIGA (node->_hoops_GIGCR, node->_hoops_HRPPA, double, weights);

	if ((knots != 0) && (node->_hoops_RIGCR == 0))
		/* _hoops_SHIR _hoops_HSH */
		for (i = 0; i < knot_count; i++)
			knots[i] = (double) i;
	else
		_hoops_AIGA (node->_hoops_RIGCR, node->_hoops_SPPPA, double, knots);

	if (start_u != 0) 
		*start_u = node->d3[0];
	if (end_u != 0)
		*end_u = node->d3[1];

} /* _hoops_RSGR _hoops_API _hoops_ASAIH */


/*
 * _hoops_GRPHR
 */
#define _hoops_RAAHR 1e-20

static void _hoops_PSAIH (
				HC_KEY		key, 
				int			point_count, 
				const _hoops_APCIR *points, 
				int			face_list_length, 
				const int	*face_list) 
{
	const int *_hoops_RIAHR, *_hoops_CHAHR, *_hoops_SHAHR;
	const _hoops_APCIR *_hoops_GIAHR;
	_hoops_APCIR *normals, *_hoops_AHAHR;
	int face_count;
	double a, b, c;
	const _hoops_APCIR *_hoops_GGIAR, *p1;
	float *_hoops_HSAIH=0;

	UNREFERENCED(point_count);

	_hoops_RIAHR = face_list;
	_hoops_SHAHR = face_list + face_list_length;

	/* _hoops_RPR _hoops_RH _hoops_PHI _hoops_IIGR _hoops_RSSI _hoops_HIS _hoops_SGS _hoops_SR _hoops_ACPA _hoops_RSH _hoops_AHPH _hoops_HSP _hoops_GHC _hoops_IS _hoops_CCPP */
	face_count = 0;
	while (face_list < _hoops_SHAHR) {
		int length = *face_list++;;

		if (length < 0)
			length = -length;
		else
			face_count++;
		face_list += length;
	}
	ALLOC_ARRAY(normals, face_count, _hoops_APCIR);
	_hoops_AHAHR = normals;

	face_list = _hoops_RIAHR;
	while (face_list < _hoops_SHAHR) {
		if (*face_list >= 3) {
			int length = *face_list++;
			if (length < 0)
				length = -length;
			_hoops_CHAHR = face_list + length;

			/* _hoops_IPCP 3 _hoops_AIAHR _hoops_RAIGR, _hoops_IHAC, _hoops_PPR _hoops_IHRPR _hoops_CHR _hoops_PIAHR _hoops_IS _hoops_RH
			 * _hoops_HIAHR _hoops_IIGR _hoops_RH _hoops_IIAHR _hoops_IIGR _hoops_RH _hoops_HSSP _hoops_CIAA _hoops_RH _hoops_CIAHR, _hoops_SIAHR, _hoops_PPR
			 * _hoops_HSHC _hoops_GHC, _hoops_GCAHR.
			 *
			 * _hoops_HSRR _hoops_APRAR _hoops_RCAHR, _hoops_ACAHR _hoops_IS _hoops_PCAHR & _hoops_ISAIH _hoops_CSAIH (1_hoops_ICPC _hoops_ICAHR) _hoops_CCAHR. 513
			 */

			/* _hoops_ARAS _hoops_AARI _hoops_RH _hoops_HSP, _hoops_IGGC _hoops_SCAHR _hoops_HIAHR */
			a = b = c = 0;
			_hoops_GIAHR = _hoops_GGIAR = points + *face_list;
			while (++face_list != _hoops_CHAHR) {
				p1 = points + *face_list;
				a += (_hoops_GGIAR->y + p1->y) * (p1->z - _hoops_GGIAR->z);
				b += (_hoops_GGIAR->z + p1->z) * (p1->x - _hoops_GGIAR->x);
				c += (_hoops_GGIAR->x + p1->x) * (p1->y - _hoops_GGIAR->y);
				_hoops_GGIAR = p1;
			}

			/*_hoops_GGGR _hoops_SCH _hoops_GH, _hoops_PPR _hoops_IPS _hoops_IRS/_hoops_RCSR/_hoops_GSGGR _hoops_CRGR '_hoops_GSSR'*/
			p1 = _hoops_GIAHR;
			_hoops_AHAHR->x = -(a + (_hoops_GGIAR->y + p1->y) * (p1->z - _hoops_GGIAR->z));
			_hoops_AHAHR->y = -(b + (_hoops_GGIAR->z + p1->z) * (p1->x - _hoops_GGIAR->x));
			_hoops_AHAHR->z = -(c + (_hoops_GGIAR->x + p1->x) * (p1->y - _hoops_GGIAR->y));

			if (fabs(_hoops_AHAHR->x) > _hoops_RAAHR ||
				fabs(_hoops_AHAHR->y) > _hoops_RAAHR ||
				fabs(_hoops_AHAHR->z) > _hoops_RAAHR) {
				double _hoops_SSAIH = (
					_hoops_AHAHR->x * _hoops_AHAHR->x +
					_hoops_AHAHR->y * _hoops_AHAHR->y +
					_hoops_AHAHR->z * _hoops_AHAHR->z);
				_hoops_AHAHR->x /= _hoops_SSAIH;
				_hoops_AHAHR->y /= _hoops_SSAIH;
				_hoops_AHAHR->z /= _hoops_SSAIH;
			}
			_hoops_AHAHR++;
		}
		else if (*face_list >= 0  /* && *_hoops_SCAPA < 3 */) {
			/* _hoops_IRS _hoops_ARHAR _hoops_HSP -- _hoops_SR _hoops_PAH'_hoops_RA _hoops_GRAS _hoops_IRS _hoops_GSSR _hoops_IH _hoops_RGR */
			_hoops_AHAHR->x = 0;
			_hoops_AHAHR->y = 0;
			_hoops_AHAHR->z = 0;
			_hoops_AHAHR++;
			face_list += *face_list + 1;
		}
		else {
			/* _hoops_SCH'_hoops_GRI _hoops_IRS "_hoops_RCCPR" _hoops_AACC _hoops_HII _hoops_RH _hoops_PGHC _hoops_HSP -- _hoops_SAHR _hoops_HSGR _hoops_SCH. */
			face_list += -(*face_list) + 1;
		}
	}

	_hoops_HSAIH = _hoops_IIAIH ((double *)normals,  3*face_count);
	HC_MSet_Face_Normals (key, 0, face_count, _hoops_HSAIH);

	face_list = _hoops_RIAHR;
	FREE_ARRAY(normals, face_count, _hoops_APCIR);
	FREE_ARRAY(_hoops_HSAIH, 3*face_count, float);
}



HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Shell (
				const char		*segment,
				int				point_count,
				const HCD_POINT  *points,
				int				face_list_length,
				const int		*face_list) 
{
	int _hoops_IHAIH=0;
	float *_hoops_AIPCP=0;
	double *_hoops_HHAIH=0;
	HC_KEY key;

	

	if (points != 0) {
		_hoops_IHAIH = 3 * point_count;
		_hoops_HHAIH = _hoops_AIAIH ((double *)points, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}

	key = HC_QKInsert_Shell  (
				segment, 
				point_count, _hoops_AIPCP, 
				face_list_length, face_list);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	_hoops_PSAIH(key, point_count, (const _hoops_APCIR*)points, face_list_length, face_list);

	if (_hoops_AIPCP) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_GGPIH */


HC_EXTERNAL HD_API void HC_DEdit_Shell_Points (
				HC_KEY			_hoops_PCAIH,
				int				offset,
				int				_hoops_RGPIH,
				int				_hoops_SSGIH,
				const HCD_POINT  *points)
{
	_hoops_PHAIH *node = 0;
	float *_hoops_AIPCP=0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);
	int _hoops_AGPIH;

	

	_hoops_AIPCP = _hoops_IIAIH ((double *)points, 3*_hoops_SSGIH);
   
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Edit_Shell_Points  (key, offset, _hoops_RGPIH, _hoops_SSGIH, _hoops_AIPCP);
	if (node == 0) 
		return;

	_hoops_AGPIH = node->_hoops_IHAIH;
	node->_hoops_IHAIH += 3 * (_hoops_SSGIH - _hoops_RGPIH);
	if (_hoops_SSGIH != _hoops_RGPIH)
	{
		double *_hoops_PGPIH, *_hoops_CIAIH;

		if (offset == -1)
			offset = _hoops_AGPIH/3;

		ALLOC_ARRAY_ALIGNED (_hoops_PGPIH, node->_hoops_IHAIH, double, 8);
		_hoops_CIAIH = _hoops_PGPIH;
		if (offset) {
			_hoops_AIGA (node->_hoops_HHAIH, 3*offset, double, _hoops_CIAIH);
			_hoops_CIAIH += offset*3;
		}
		if (_hoops_SSGIH) {
			_hoops_AIGA ((double *)points, 3*_hoops_SSGIH, double, _hoops_CIAIH);
			_hoops_CIAIH += _hoops_SSGIH*3;
		}
		if (node->_hoops_IHAIH - 3 * (offset + _hoops_SSGIH)) {
			_hoops_AIGA (node->_hoops_HHAIH + 3 * (offset + _hoops_SSGIH), node->_hoops_IHAIH - offset - _hoops_SSGIH, double, _hoops_CIAIH);
		}
		FREE_ARRAY_ALIGNED (node->_hoops_HHAIH, _hoops_AGPIH, double, 8);
		node->_hoops_HHAIH = _hoops_PGPIH;
	}
	else
		_hoops_AIGA ((double *)points, 3*_hoops_SSGIH, double, node->_hoops_HHAIH + 3*offset);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, 3*_hoops_SSGIH, float);

} /* _hoops_RSGR _hoops_API _hoops_HGPIH */


HC_EXTERNAL HD_API void HC_DShow_Shell (
				HC_KEY	  _hoops_PCAIH,
				int		  *point_countp,
				HCD_POINT  *points,
				int		  *face_list_lengthp,
				int		  *face_list) 
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Shell (
				key, 
				point_countp, 0, 
				face_list_lengthp, face_list
	);
	if (node == 0)
		return;
	_hoops_AIGA (node->_hoops_HHAIH, node->_hoops_IHAIH, double, (double *)points);

} /* _hoops_RSGR _hoops_API _hoops_IGPIH */


/*
 * _hoops_CGPHR
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Mesh (
				const char		*segment,
				int				width,
				int				height,
				const HCD_POINT  *points) 
{
	int _hoops_IHAIH=0;
	float *_hoops_AIPCP=0;
	double *_hoops_HHAIH=0;
	HC_KEY key;

	

	if (points) {
		_hoops_IHAIH = 3 * width * height;
		_hoops_HHAIH = _hoops_AIAIH ((double *)points, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}
	key = HC_QKInsert_Mesh (
				segment, 
				width, height, _hoops_AIPCP);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_CGPIH */


HC_EXTERNAL HD_API void HC_DEdit_Mesh (
				HC_KEY			_hoops_PCAIH,
				int				row_offset,
				int				column_offset,
				int				row_count,
				int				column_count,
				const HCD_POINT  *points)
{

	_hoops_PHAIH *node = 0;
	float *_hoops_AIPCP = 0;
	int w, h, i, from, to;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	

	_hoops_AIPCP = _hoops_IIAIH ((double *)points, column_count*row_count*3);
   
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Edit_Mesh (key, row_offset, column_offset, row_count, column_count, _hoops_AIPCP);
	if (node == 0) 
		return;

	HC_Show_Mesh (key, &w, &h, 0);
	
	for (i = 0; i < column_count; i++)
	{
		to	 = 3*((w * (column_offset + i)) + row_offset);
		from = 3*(row_count * i);
		_hoops_AIGA ((double *)points + from, row_count*3, double, node->_hoops_HHAIH + to);
	}

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, column_count*row_count*3, float);

} /* _hoops_RSGR _hoops_API _hoops_SGPIH */



HC_EXTERNAL HD_API void HC_DShow_Mesh (
				HC_KEY	  _hoops_PCAIH,
				int		  *width,
				int		  *height,
				HCD_POINT  *points)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Mesh (key, width, height, 0); 
	if (node == 0) return;
	
	_hoops_AIGA (node->_hoops_HHAIH, node->_hoops_IHAIH, double, (double *)points);

} /* _hoops_RSGR _hoops_API _hoops_GRPIH */


/*
 * _hoops_RRPIH
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Grid (
				const char		*segment,
				const char		*type,
				const HCD_POINT  *origin,
				const HCD_POINT  *ref1,
				const HCD_POINT  *ref2,
				int				count1,
				int				count2) 
{
	int _hoops_IHAIH = 0, _hoops_HRPPA = 0, _hoops_SPPPA = 0;
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0;
	double *_hoops_HHAIH = 0, *_hoops_GIGCR = 0, *_hoops_RIGCR = 0;
	HC_KEY key;

	

	if (origin) {
		_hoops_IHAIH = 3;
		_hoops_HHAIH = _hoops_AIAIH ((double *)origin, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}
	if (ref1 != 0) {
		_hoops_HRPPA = 3;
		_hoops_GIGCR = _hoops_AIAIH ((double *)ref1, _hoops_HRPPA);
		f1 = _hoops_IIAIH (_hoops_GIGCR, _hoops_HRPPA);
	}
	if (ref2 != 0) {
		_hoops_SPPPA = 3;
		_hoops_RIGCR = _hoops_AIAIH ((double *)ref2, _hoops_SPPPA);
		f2 = _hoops_IIAIH (_hoops_RIGCR, _hoops_SPPPA);
	}

	key = HC_QKInsert_Grid (
		segment,
		type,
		_hoops_AIPCP,
		f1,
		f2,
		count1,
		count2);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, _hoops_HRPPA, _hoops_GIGCR, _hoops_SPPPA, _hoops_RIGCR,0,0);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);
	if (f1 != 0) FREE_ARRAY (f1, _hoops_HRPPA, float);
	if (f2 != 0) FREE_ARRAY (f2, _hoops_SPPPA, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_ARPIH */


HC_EXTERNAL HD_API void HC_DShow_Grid(
				HC_KEY	  _hoops_PCAIH,
				char	  *type,
				HCD_POINT  *origin,
				HCD_POINT  *ref1,
				HCD_POINT  *ref2,
				int		  *count1,
				int		  *count2)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Grid (key, type, 0, 0, 0, count1, count2);
	if (node == 0) 
		return;

	_hoops_PIAIH ((double *)origin, node->_hoops_HHAIH, 3);
	_hoops_PIAIH ((double *)ref1, node->_hoops_GIGCR, 3);
	_hoops_PIAIH ((double *)ref2, node->_hoops_RIGCR, 3);

} /* _hoops_RSGR _hoops_API _hoops_PRPIH */


/*
 * _hoops_HRPIH
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Polyline (
				const char		*segment,
				int				pcount,
				const HCD_POINT  *points)
{
	int _hoops_IHAIH = 0;
	float *_hoops_AIPCP = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	

	if (points != 0) {
		_hoops_IHAIH = 3 * pcount;
 		_hoops_HHAIH = _hoops_AIAIH ((double *)points, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}

	key = HC_QKInsert_Polyline (segment, pcount, _hoops_AIPCP);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 0,0,0,0,0,0);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_IRPIH */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Ink (
				const char *segment,
				double	   x,
				double	   y,
				double	   z) 
{
	_hoops_PHAIH *node = 0;
	int _hoops_IHAIH = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key, _hoops_PCAIH;

	

	_hoops_PCAIH = HC_QKInsert_Ink (segment, (float) x, (float) y, (float) z);
	key = HC_KShow_Original_Key (_hoops_PCAIH);
	_hoops_RIAIH()->LookupItem(key, &node);

	if (node == 0)
	{
		_hoops_IHAIH = 3;
		ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 3, double, 8);
		_hoops_HHAIH[0] = x;
		_hoops_HHAIH[1] = y;
		_hoops_HHAIH[2] = z;
		_hoops_SIAIH (key, 3, _hoops_HHAIH, 0,0,0,0,0,0);
	}
	else
	{
		_hoops_IHAIH = node->_hoops_IHAIH + 3;
		ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, _hoops_IHAIH, double, 8);
		_hoops_AIGA (node->_hoops_HHAIH, node->_hoops_IHAIH, double, _hoops_HHAIH);
		FREE_ARRAY_ALIGNED (node->_hoops_HHAIH, node->_hoops_IHAIH, double, 8);		
		node->_hoops_HHAIH = _hoops_HHAIH;
		node->_hoops_IHAIH = _hoops_IHAIH;
		node->_hoops_HHAIH[node->_hoops_IHAIH - 3] = x;
		node->_hoops_HHAIH[node->_hoops_IHAIH - 2] = y;
		node->_hoops_HHAIH[node->_hoops_IHAIH - 1] = z;
	}

	return key;

} /* _hoops_RSGR _hoops_API _hoops_CRPIH */


HC_EXTERNAL HD_API void HC_DEdit_Polyline (
				HC_KEY			_hoops_PCAIH,
				int				offset,
				int				_hoops_RGPIH,
				int				_hoops_SSGIH,
				const HCD_POINT  *points)
{
	_hoops_PHAIH *node = 0;
	float *_hoops_AIPCP = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);
	int _hoops_AGPIH;

	

	_hoops_AIPCP = _hoops_IIAIH ((double *)points, 3*_hoops_SSGIH);
   
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Edit_Polyline  (key, offset, _hoops_RGPIH, _hoops_SSGIH, _hoops_AIPCP);
	if (node == 0) return;

	_hoops_AGPIH = node->_hoops_IHAIH;
	node->_hoops_IHAIH += _hoops_SSGIH - _hoops_RGPIH;
	if (_hoops_SSGIH != _hoops_RGPIH)
	{
		double *_hoops_PGPIH, *_hoops_CIAIH;

		ALLOC_ARRAY_ALIGNED (_hoops_PGPIH, node->_hoops_IHAIH, double, 8);
		_hoops_CIAIH = _hoops_PGPIH;
		if (offset) {
			_hoops_AIGA (node->_hoops_HHAIH, 3*offset, double, _hoops_CIAIH);
			_hoops_CIAIH += offset*3;
		}
		if (_hoops_SSGIH) {
			_hoops_AIGA ((double *)points, 3*offset, double, _hoops_CIAIH);
			_hoops_CIAIH += _hoops_SSGIH*3;
		}
		if (node->_hoops_IHAIH - offset - _hoops_SSGIH) {
			_hoops_AIGA (node->_hoops_HHAIH + offset*3 + _hoops_SSGIH*3, node->_hoops_IHAIH - offset - _hoops_SSGIH, double, _hoops_CIAIH);
		}
		FREE_ARRAY_ALIGNED (node->_hoops_HHAIH, _hoops_AGPIH, double, 8);
		node->_hoops_HHAIH = _hoops_PGPIH;
	}
	else
		_hoops_AIGA ((double *)points, 3*_hoops_SSGIH, double, node->_hoops_HHAIH + 3*offset);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, 3*_hoops_SSGIH, float);

} /* _hoops_RSGR _hoops_API _hoops_SRPIH */


HC_EXTERNAL HD_API void HC_DShow_Polyline (
				HC_KEY	  _hoops_PCAIH,
				int		  *pcount,
				HCD_POINT  *points)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Polyline (key, pcount, 0); 
	if (node == 0) return;
	
	_hoops_PIAIH ((double *)points, node->_hoops_HHAIH, node->_hoops_IHAIH);

} /* _hoops_RSGR _hoops_API _hoops_GAPIH */


/*
 * _hoops_RAPIH
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Line (
				const char *segment,
				double	   xa,
				double	   ya,
				double	   za,
				double	   xb,
				double	   yb,
				double	   zb) 
{
	int _hoops_IHAIH = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	

	_hoops_IHAIH = 6;
	ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 6, double, 8);

	_hoops_HHAIH[0] = xa;
	_hoops_HHAIH[1] = ya;
	_hoops_HHAIH[2] = za;
	_hoops_HHAIH[3] = xb;
	_hoops_HHAIH[4] = yb;
	_hoops_HHAIH[5] = zb;

	key = HC_QKInsert_Line (segment, xa, ya, za, xb, yb, zb);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_AAPIH */


HC_EXTERNAL HD_API void HC_DShow_Line (
				HC_KEY _hoops_PCAIH,
				double	   *xa,
				double	   *ya,
				double	   *za,
				double	   *xb,
				double	   *yb,
				double	   *zb) 
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;
	if (node->_hoops_HHAIH == 0) return;

	if (xa != 0) *xa = node->_hoops_HHAIH[0];
	if (ya != 0) *ya = node->_hoops_HHAIH[1];
	if (za != 0) *za = node->_hoops_HHAIH[2];
	if (xb != 0) *xb = node->_hoops_HHAIH[3];
	if (yb != 0) *yb = node->_hoops_HHAIH[4];
	if (zb != 0) *zb = node->_hoops_HHAIH[5];

} /* _hoops_RSGR _hoops_API _hoops_PAPIH */


/*
 * _hoops_SAAAA
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Polygon (
				const char		*segment,
				int				pcount,
				const HCD_POINT  *points)
{
	int _hoops_IHAIH = 0;
	float *_hoops_AIPCP = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	

	if (points != 0) {
		_hoops_IHAIH = 3 * pcount;
		_hoops_HHAIH = _hoops_AIAIH ((double *)points, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}

	key = HC_QKInsert_Polygon (segment, pcount, _hoops_AIPCP);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_HAPIH */


HC_EXTERNAL HD_API void HC_DEdit_Polygon (
				HC_KEY			_hoops_PCAIH,
				int				offset,
				int				_hoops_RGPIH,
				int				_hoops_SSGIH,
				const HCD_POINT  *points)
{
	_hoops_PHAIH *node = 0;
	float *_hoops_AIPCP = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);
	int _hoops_AGPIH;

	

	_hoops_AIPCP = _hoops_IIAIH ((double *)points, 3*_hoops_SSGIH);
   
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Edit_Polygon  (key, offset, _hoops_RGPIH, _hoops_SSGIH, _hoops_AIPCP);
	if (node == 0) return;

	_hoops_AGPIH = node->_hoops_IHAIH;
	node->_hoops_IHAIH += _hoops_SSGIH - _hoops_RGPIH;
	if (_hoops_SSGIH != _hoops_RGPIH)
	{
		double *_hoops_PGPIH, *_hoops_CIAIH;

		ALLOC_ARRAY_ALIGNED (_hoops_PGPIH, node->_hoops_IHAIH, double, 8);
		_hoops_CIAIH = _hoops_PGPIH;
		if (offset) {
			_hoops_AIGA (node->_hoops_HHAIH, 3*offset, double, _hoops_CIAIH);
			_hoops_CIAIH += offset*3;
		}
		if (_hoops_SSGIH) {
			_hoops_AIGA ((double *)points, 3*offset, double, _hoops_CIAIH);
			_hoops_CIAIH += _hoops_SSGIH*3;
		}
		if (node->_hoops_IHAIH - offset - _hoops_SSGIH) {
			_hoops_AIGA (node->_hoops_HHAIH + offset*3 + _hoops_SSGIH*3, node->_hoops_IHAIH - offset - _hoops_SSGIH, double, _hoops_CIAIH);
		}
		FREE_ARRAY_ALIGNED (node->_hoops_HHAIH, _hoops_AGPIH, double, 8);
		node->_hoops_HHAIH = _hoops_PGPIH;
	}
	else
		_hoops_AIGA ((double *)points, 3*_hoops_SSGIH, double, node->_hoops_HHAIH + 3*offset);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, 3*_hoops_SSGIH, float);

} /* _hoops_RSGR _hoops_API _hoops_IAPIH */


HC_EXTERNAL HD_API void HC_DShow_Polygon (
				HC_KEY	  _hoops_PCAIH,
				int		  *pcount,
				HCD_POINT  *points)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Polygon (key, pcount, 0); 
	if (node == 0) return;
	
	_hoops_PIAIH ((double *)points, node->_hoops_HHAIH, node->_hoops_IHAIH);

} /* _hoops_RSGR _hoops_API _hoops_CAPIH */


/*
 * _hoops_SAPIH
 */

HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Marker (
				const char *segment,
				double	   x,
				double	   y,
				double	   z) 
{
	int _hoops_IHAIH = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	

	_hoops_IHAIH = 3;
	ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 3, double, 8);

	_hoops_HHAIH[0] = x;
	_hoops_HHAIH[1] = y;
	_hoops_HHAIH[2] = z;

	key = HC_QKInsert_Marker (segment, x, y, z);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_GPPIH */


HC_EXTERNAL HD_API void HC_DShow_Marker (
				HC_KEY _hoops_PCAIH,
				double *x,
				double *y,
				double *z) 
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;
	if (node->_hoops_HHAIH == 0) return;

	if (x != 0) *x = node->_hoops_HHAIH[0];
	if (y != 0) *y = node->_hoops_HHAIH[1];
	if (z != 0) *z = node->_hoops_HHAIH[2];

} /* _hoops_RSGR _hoops_API _hoops_RPPIH */


/* 
 * _hoops_APPIH 
 */

HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Cylinder (
				const char		*segment,
				const HCD_POINT  *_hoops_GGIAR,
				const HCD_POINT  *p1,
				const double radius,
				const char *list)
{
	int _hoops_IHAIH = 0, _hoops_HRPPA = 0, _hoops_SPPPA = 0;
	float *_hoops_AIPCP = 0, *f1 = 0;
	double *_hoops_HHAIH = 0, *_hoops_GIGCR = 0, *_hoops_RIGCR = 0;
	HC_KEY key;

	

	_hoops_IHAIH = 3;
	_hoops_HHAIH = _hoops_AIAIH ((double *)_hoops_GGIAR, _hoops_IHAIH);
	_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);

	_hoops_HRPPA = 3;
	_hoops_GIGCR = _hoops_AIAIH ((double *)p1, _hoops_HRPPA);
	f1 = _hoops_IIAIH (_hoops_GIGCR, _hoops_HRPPA);

	_hoops_SPPPA = 1;
	ALLOC_ARRAY_ALIGNED (_hoops_RIGCR, 1, double, 8);
	_hoops_RIGCR[0] = radius;

	key = HC_QKInsert_Cylinder (segment, _hoops_AIPCP, f1, (float)radius, list);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, _hoops_HRPPA, _hoops_GIGCR, _hoops_SPPPA, _hoops_RIGCR, 0,0);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);
	if (f1 != 0) FREE_ARRAY (f1, _hoops_HRPPA, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_PPPIH */


HC_EXTERNAL HD_API void HC_DShow_Cylinder(
				HC_KEY	  _hoops_PCAIH,
				HCD_POINT  *_hoops_GGIAR,
				HCD_POINT  *p1,
				double *radius,
				char *list)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Cylinder (key, 0, 0, 0, list);
	if (node == 0) return;

	if (_hoops_GGIAR != 0)
		_hoops_PIAIH ((double *)_hoops_GGIAR, node->_hoops_HHAIH, 3);
	if (p1 != 0)
		_hoops_PIAIH ((double *)p1, node->_hoops_GIGCR, 3);
	if (radius != 0)
		*radius = node->_hoops_RIGCR[0];

} /* _hoops_RSGR _hoops_API _hoops_HPPIH */


/* 
 * _hoops_IPPIH 
 */
HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Circle (
				const char		*segment,
				const HCD_POINT  *_hoops_GGIAR,
				const HCD_POINT  *p1,
				const HCD_POINT  *p2)
{
	int _hoops_IHAIH = 0, _hoops_HRPPA = 0, _hoops_SPPPA = 0;
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0;
	double *_hoops_HHAIH = 0, *_hoops_GIGCR = 0, *_hoops_RIGCR = 0;
	HC_KEY key;

	

	if (_hoops_GGIAR != 0) {
		_hoops_IHAIH = 3;
		_hoops_HHAIH = _hoops_AIAIH ((double *)_hoops_GGIAR, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}
	if (p1 != 0) {
		_hoops_HRPPA = 3;
		_hoops_GIGCR = _hoops_AIAIH ((double *)p1, _hoops_HRPPA);
		f1 = _hoops_IIAIH (_hoops_GIGCR, _hoops_HRPPA);
	}
	if (p2 != 0) {
		_hoops_SPPPA = 3;
		_hoops_RIGCR = _hoops_AIAIH ((double *)p2, _hoops_SPPPA);
		f2 = _hoops_IIAIH (_hoops_RIGCR, _hoops_SPPPA);
	}

	key = HC_QKInsert_Circle (segment, _hoops_AIPCP, f1, f2);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, _hoops_HRPPA, _hoops_GIGCR, _hoops_SPPPA, _hoops_RIGCR,0,0);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);
	if (f1 != 0) FREE_ARRAY (f1, _hoops_HRPPA, float);
	if (f2 != 0) FREE_ARRAY (f2, _hoops_SPPPA, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_CPPIH */


HC_EXTERNAL HD_API void HC_DShow_Circle(
				HC_KEY	  _hoops_PCAIH,
				HCD_POINT *_hoops_GGIAR,
				HCD_POINT *p1,
				HCD_POINT *p2)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Circle (key, 0, 0, 0);
	if (node == 0) return;

	_hoops_PIAIH ((double *)_hoops_GGIAR, node->_hoops_HHAIH, 3);
	_hoops_PIAIH ((double *)p1, node->_hoops_GIGCR, 3);
	_hoops_PIAIH ((double *)p2, node->_hoops_RIGCR, 3);

} /* _hoops_RSGR _hoops_API _hoops_SPPIH */


/* 
 * _hoops_GHPIH _hoops_RHPIH 
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Circular_Arc (
				const char		*segment,
				const HCD_POINT *_hoops_GGIAR,
				const HCD_POINT *p1,
				const HCD_POINT *p2)
{
	int _hoops_IHAIH = 0, _hoops_HRPPA = 0, _hoops_SPPPA = 0;
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0;
	double *_hoops_HHAIH = 0, *_hoops_GIGCR = 0, *_hoops_RIGCR = 0;
	HC_KEY key;

	

	if (_hoops_GGIAR != 0) {
		_hoops_IHAIH = 3;
		_hoops_HHAIH = _hoops_AIAIH ((double *)_hoops_GGIAR, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}
	if (p1 != 0) {
		_hoops_HRPPA = 3;
		_hoops_GIGCR = _hoops_AIAIH ((double *)p1, _hoops_HRPPA);
		f1 = _hoops_IIAIH (_hoops_GIGCR, _hoops_HRPPA);
	}
	if (p2 != 0) {
		_hoops_SPPPA = 3;
		_hoops_RIGCR = _hoops_AIAIH ((double *)p2, _hoops_SPPPA);
		f2 = _hoops_IIAIH (_hoops_RIGCR, _hoops_SPPPA);
	}

	key = HC_QKInsert_Circular_Arc (segment, _hoops_AIPCP, f1, f2);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, _hoops_HRPPA, _hoops_GIGCR, _hoops_SPPPA, _hoops_RIGCR,0,0);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);
	if (f1 != 0) FREE_ARRAY (f1, _hoops_HRPPA, float);
	if (f2 != 0) FREE_ARRAY (f2, _hoops_SPPPA, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_AHPIH */


HC_EXTERNAL HD_API void HC_DShow_Circular_Arc(
				HC_KEY	  _hoops_PCAIH,
				HCD_POINT *_hoops_GGIAR,
				HCD_POINT *p1,
				HCD_POINT *p2)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Circular_Arc (key, 0, 0, 0);
	if (node == 0) return;

	_hoops_PIAIH ((double *)_hoops_GGIAR, node->_hoops_HHAIH, 3);
	_hoops_PIAIH ((double *)p1, node->_hoops_GIGCR, 3);
	_hoops_PIAIH ((double *)p2, node->_hoops_RIGCR, 3);

} /* _hoops_RSGR _hoops_API _hoops_PHPIH */


/* 
 * _hoops_HHPIH 
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Circular_Chord (
				const char		*segment,
				const HCD_POINT *_hoops_GGIAR,
				const HCD_POINT *p1,
				const HCD_POINT *p2)
{
	int _hoops_IHAIH = 0, _hoops_HRPPA = 0, _hoops_SPPPA = 0;
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0;
	double *_hoops_HHAIH = 0, *_hoops_GIGCR = 0, *_hoops_RIGCR = 0;
	HC_KEY key;

	

	if (_hoops_GGIAR != 0) {
		_hoops_IHAIH = 3;
		_hoops_HHAIH = _hoops_AIAIH ((double *)_hoops_GGIAR, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}
	if (p1 != 0) {
		_hoops_HRPPA = 3;
		_hoops_GIGCR = _hoops_AIAIH ((double *)p1, _hoops_HRPPA);
		f1 = _hoops_IIAIH (_hoops_GIGCR, _hoops_HRPPA);
	}
	if (p2 != 0) {
		_hoops_SPPPA = 3;
		_hoops_RIGCR = _hoops_AIAIH ((double *)p2, _hoops_SPPPA);
		f2 = _hoops_IIAIH (_hoops_RIGCR, _hoops_SPPPA);
	}

	key = HC_QKInsert_Circular_Chord (segment, _hoops_AIPCP, f1, f2);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, _hoops_HRPPA, _hoops_GIGCR, _hoops_SPPPA, _hoops_RIGCR,0,0);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);
	if (f1 != 0) FREE_ARRAY (f1, _hoops_HRPPA, float);
	if (f2 != 0) FREE_ARRAY (f2, _hoops_SPPPA, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_IHPIH */


HC_EXTERNAL HD_API void HC_DShow_Circular_Chord(
				HC_KEY	  _hoops_PCAIH,
				HCD_POINT *_hoops_GGIAR,
				HCD_POINT *p1,
				HCD_POINT *p2)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Circular_Chord (key, 0, 0, 0);
	if (node == 0) return;

	_hoops_PIAIH ((double *)_hoops_GGIAR, node->_hoops_HHAIH, 3);
	_hoops_PIAIH ((double *)p1, node->_hoops_GIGCR, 3);
	_hoops_PIAIH ((double *)p2, node->_hoops_RIGCR, 3);

} /* _hoops_RSGR _hoops_API _hoops_CHPIH */


/* 
 * _hoops_SHPIH 
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Circular_Wedge (
				const char		*segment,
				const HCD_POINT *_hoops_GGIAR,
				const HCD_POINT *p1,
				const HCD_POINT *p2)
{
	int _hoops_IHAIH = 0, _hoops_HRPPA = 0, _hoops_SPPPA = 0;
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0;
	double *_hoops_HHAIH = 0, *_hoops_GIGCR = 0, *_hoops_RIGCR = 0;
	HC_KEY key;

	

	if (_hoops_GGIAR != 0) {
		_hoops_IHAIH = 3;
		_hoops_HHAIH = _hoops_AIAIH ((double *)_hoops_GGIAR, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}
	if (p1 != 0) {
		_hoops_HRPPA = 3;
		_hoops_GIGCR = _hoops_AIAIH ((double *)p1, _hoops_HRPPA);
		f1 = _hoops_IIAIH (_hoops_GIGCR, _hoops_HRPPA);
	}
	if (p2 != 0) {
		_hoops_SPPPA = 3;
		_hoops_RIGCR = _hoops_AIAIH ((double *)p2, _hoops_SPPPA);
		f2 = _hoops_IIAIH (_hoops_RIGCR, _hoops_SPPPA);
	}

	key = HC_QKInsert_Circular_Wedge (segment, _hoops_AIPCP, f1, f2);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, _hoops_HRPPA, _hoops_GIGCR, _hoops_SPPPA, _hoops_RIGCR,0,0);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);
	if (f1 != 0) FREE_ARRAY (f1, _hoops_HRPPA, float);
	if (f2 != 0) FREE_ARRAY (f2, _hoops_SPPPA, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_GIPIH */


HC_EXTERNAL HD_API void HC_DShow_Circular_Wedge(
				HC_KEY	  _hoops_PCAIH,
				HCD_POINT *_hoops_GGIAR,
				HCD_POINT *p1,
				HCD_POINT *p2)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Circular_Wedge (key, 0, 0, 0);
	if (node == 0) return;

	_hoops_PIAIH ((double *)_hoops_GGIAR, node->_hoops_HHAIH, 3);
	_hoops_PIAIH ((double *)p1, node->_hoops_GIGCR, 3);
	_hoops_PIAIH ((double *)p2, node->_hoops_RIGCR, 3);

} /* _hoops_RSGR _hoops_API _hoops_RIPIH */


/* 
 * _hoops_CAIA 
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Ellipse (
				const char		*segment,
				const HCD_POINT *_hoops_GGIAR,
				const HCD_POINT *p1,
				const HCD_POINT *p2)
{
	int _hoops_IHAIH = 0, _hoops_HRPPA = 0, _hoops_SPPPA = 0;
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0;
	double *_hoops_HHAIH = 0, *_hoops_GIGCR = 0, *_hoops_RIGCR = 0;
	HC_KEY key;

	

	if (_hoops_GGIAR != 0) {
		_hoops_IHAIH = 3;
		_hoops_HHAIH = _hoops_AIAIH ((double *)_hoops_GGIAR, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}
	if (p1 != 0) {
		_hoops_HRPPA = 3;
		_hoops_GIGCR = _hoops_AIAIH ((double *)p1, _hoops_HRPPA);
		f1 = _hoops_IIAIH (_hoops_GIGCR, _hoops_HRPPA);
	}
	if (p2 != 0) {
		_hoops_SPPPA = 3;
		_hoops_RIGCR = _hoops_AIAIH ((double *)p2, _hoops_SPPPA);
		f2 = _hoops_IIAIH (_hoops_RIGCR, _hoops_SPPPA);
	}

	key = HC_QKInsert_Ellipse (segment, _hoops_AIPCP, f1, f2);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, _hoops_HRPPA, _hoops_GIGCR, _hoops_SPPPA, _hoops_RIGCR,0,0);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);
	if (f1 != 0) FREE_ARRAY (f1, _hoops_HRPPA, float);
	if (f2 != 0) FREE_ARRAY (f2, _hoops_SPPPA, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_AIPIH */


HC_EXTERNAL HD_API void HC_DShow_Ellipse(
				HC_KEY	  _hoops_PCAIH,
				HCD_POINT *_hoops_GGIAR,
				HCD_POINT *p1,
				HCD_POINT *p2)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Ellipse (key, 0, 0, 0);
	if (node == 0) return;

	_hoops_PIAIH ((double *)_hoops_GGIAR, node->_hoops_HHAIH, 3);
	_hoops_PIAIH ((double *)p1, node->_hoops_GIGCR, 3);
	_hoops_PIAIH ((double *)p2, node->_hoops_RIGCR, 3);

} /* _hoops_RSGR _hoops_API _hoops_PIPIH */


/* 
 * _hoops_HIPIH _hoops_RHPIH 
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Elliptical_Arc (
				const char		*segment,
				const HCD_POINT *_hoops_GGIAR,
				const HCD_POINT *p1,
				const HCD_POINT *p2, 
				double start,
				double end)
{
	int _hoops_IHAIH = 0, _hoops_HRPPA = 0, _hoops_SPPPA = 0;
	float *_hoops_AIPCP = 0, *f1 = 0, *f2 = 0;
	double *_hoops_HHAIH = 0, *_hoops_GIGCR = 0, *_hoops_RIGCR = 0, *d3 = 0;
	HC_KEY key;

	

	if (_hoops_GGIAR != 0) {
		_hoops_IHAIH = 3;
		_hoops_HHAIH = _hoops_AIAIH ((double *)_hoops_GGIAR, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}
	if (p1 != 0) {
		_hoops_HRPPA = 3;
		_hoops_GIGCR = _hoops_AIAIH ((double *)p1, _hoops_HRPPA);
		f1 = _hoops_IIAIH (_hoops_GIGCR, _hoops_HRPPA);
	}
	if (p2 != 0) {
		_hoops_SPPPA = 3;
		_hoops_RIGCR = _hoops_AIAIH ((double *)p2, _hoops_SPPPA);
		f2 = _hoops_IIAIH (_hoops_RIGCR, _hoops_SPPPA);
	}
	ALLOC_ARRAY_ALIGNED (d3, 2, double, 8);
	d3[0] = start;
	d3[1] = end;

	key = HC_QKInsert_Elliptical_Arc (segment, _hoops_AIPCP, f1, f2, start, end);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, _hoops_HRPPA, _hoops_GIGCR, _hoops_SPPPA, _hoops_RIGCR, 2, d3);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);
	if (f1 != 0) FREE_ARRAY (f1, _hoops_HRPPA, float);
	if (f2 != 0) FREE_ARRAY (f2, _hoops_SPPPA, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_IIPIH */


HC_EXTERNAL HD_API void HC_DShow_Elliptical_Arc(
				HC_KEY	  _hoops_PCAIH,
				HCD_POINT *_hoops_GGIAR,
				HCD_POINT *p1,
				HCD_POINT *p2,
				double	  *start,
				double	  *end)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;
	if (node->_hoops_HHAIH == 0) return;

	_hoops_PIAIH ((double *)_hoops_GGIAR, node->_hoops_HHAIH, 3);
	_hoops_PIAIH ((double *)p1, node->_hoops_GIGCR, 3);
	_hoops_PIAIH ((double *)p2, node->_hoops_RIGCR, 3);
	if (start != 0) *start = node->d3[0];
	if (end != 0) *end = node->d3[1];

} /* _hoops_RSGR _hoops_API _hoops_CIPIH */


/*
 * _hoops_ARCA _hoops_IRSIR
 */

HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Cutting_Plane (
				const char *segment,
				double	   a,
				double	   b,
				double	   c,
				double	   d) 
{
	int _hoops_IHAIH = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	

	_hoops_IHAIH = 4;
	ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 4, double, 8);
	_hoops_HHAIH[0] = a;
	_hoops_HHAIH[1] = b;
	_hoops_HHAIH[2] = c;
	_hoops_HHAIH[3] = d;

	key = HC_QKInsert_Cutting_Plane (segment, a, b, c, d);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_SIPIH */


HC_EXTERNAL HD_API void HC_DShow_Cutting_Plane (
				HC_KEY _hoops_PCAIH,
				double *a,
				double *b,
				double *c,
				double *d) 
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;
	if (node->_hoops_HHAIH == 0) return;

	if (a != 0) *a = node->_hoops_HHAIH[0];
	if (b != 0) *b = node->_hoops_HHAIH[1];
	if (c != 0) *c = node->_hoops_HHAIH[2];
	if (d != 0) *d = node->_hoops_HHAIH[3];

} /* _hoops_RSGR _hoops_API _hoops_GCPIH */



/*
 * _hoops_RCPIH _hoops_ACPIH
 */

/* _hoops_PGAA
 * _hoops_PCHIA _hoops_CPS _hoops_GGR _hoops_RH _hoops_IPIH _hoops_IGS _hoops_CAGH _hoops_PPR _hoops_HCR _hoops_RGCI _hoops_RASI
 */
static void _hoops_PCPIH(void)
{
	HC_KEY key;
	char _hoops_HCIS[ 128 ];
	char _hoops_HCPIH[ 4096 ];

	if (!global_hcd_table || _hoops_RIAIH()->Count() == 0)
		return;

	HC_Begin_Segment_Search ("*");
	while (HC_Find_Segment (_hoops_HCPIH)) 
	{
		HC_Open_Segment (_hoops_HCPIH);
		_hoops_PCPIH ();
		HC_Close_Segment();
	}
	HC_End_Segment_Search();

	HC_Begin_Contents_Search (".", "everything");
	while (HC_Find_Contents (_hoops_HCIS, &key)) 
		_hoops_RCAIH (HC_KShow_Original_Key (key));
	HC_End_Contents_Search ();

} /* _hoops_RSGR _hoops_API _hoops_ICPIH */


HC_EXTERNAL HD_API void HC_DFlush_Contents (
				const char *segment, 
				const char *types)
{
	char type[ 128 ];
	HC_KEY key, _hoops_PCAIH;

	if (global_hcd_table) {
		HC_Begin_Contents_Search (segment, types);
		while (HC_Find_Contents (type, &_hoops_PCAIH)) 
		{
			key = HC_KShow_Original_Key (_hoops_PCAIH);

			if (_hoops_AGGR (type, "segment"))
			{
				HC_Open_Segment_By_Key (key);
					_hoops_PCPIH();
				HC_Close_Segment(); 
			}
			else
				_hoops_RCAIH (key);
		}
		HC_End_Contents_Search ();
	}
	/* _hoops_PS _hoops_APCRR _hoops_ISCP _hoops_SCAH _hoops_GASR _hoops_HHGHH (_hoops_RPP _hoops_HAHH), _hoops_HA _hoops_CRGS _hoops_CHARP _hoops_AHCA _hoops_SCH */
	HC_Flush_Contents (segment, types);

} /* _hoops_RSGR _hoops_API _hoops_CCPIH */


HC_EXTERNAL HD_API void HC_DFlush_By_Key (
				HC_KEY _hoops_PCAIH)
{
	char type[ 128 ];
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);
	_hoops_PHAIH *node;

	if (global_hcd_table) {
		HC_Show_Key_Type (key, type);
		if (_hoops_AGGR (type, "segment"))
		{
			HC_Open_Segment_By_Key (key);
				_hoops_PCPIH();
			HC_Close_Segment(); 
		}
		else
		{
			_hoops_RIAIH()->LookupItem(key, &node);
			_hoops_RCAIH (key);
			if (node != 0)
			{
				if (node->_hoops_HHAIH != 0) 
					FREE_ARRAY_ALIGNED (node->_hoops_HHAIH, node->_hoops_IHAIH, double, 8);
				if (node->_hoops_GIGCR != 0) 
					FREE_ARRAY_ALIGNED (node->_hoops_GIGCR, node->_hoops_HRPPA, double, 8);
				if (node->_hoops_RIGCR != 0) 
					FREE_ARRAY_ALIGNED (node->_hoops_RIGCR, node->_hoops_SPPPA, double, 8);
				node->_hoops_HHAIH = node->_hoops_GIGCR = node->_hoops_RIGCR = 0;
				node->_hoops_IHAIH = node->_hoops_HRPPA = node->_hoops_SPPPA = 0;
			}
		}
	}
	HC_Flush_By_Key (key);

} /* _hoops_RSGR _hoops_API _hoops_SCPIH */


HC_EXTERNAL HD_API void HC_DDelete_By_Key (
				HC_KEY _hoops_PCAIH)
{
	if (global_hcd_table) {
		HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);
		char type[128];

		HC_Show_Key_Type (key, type);
		if (_hoops_AGGR (type, "segment"))
		{
			HC_Open_Segment_By_Key (key);
				_hoops_PCPIH();
			HC_Close_Segment(); 
		}
		else
			_hoops_RCAIH (key);
	}
	HC_Delete_By_Key (_hoops_PCAIH);
	
} /* _hoops_RSGR _hoops_API */


HC_EXTERNAL HD_API void HC_DDelete_Segment (
				const char *segment)
{
	if (global_hcd_table) {
		if (HC_KOpen_Segment (segment) != -1)
		{
			_hoops_PCPIH();
			HC_Close_Segment(); 
		}
	}
	HC_Delete_Segment (segment);

} /* _hoops_RSGR _hoops_API */



/*
 * _hoops_GSPIH
 */

HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Image (
				const char *segment,
				double	   x,
				double	   y,
				double	   z,
				const char *format,
				int		   width,
				int		   height,
				const void		 *_hoops_SHGGR) 
{
	int _hoops_IHAIH = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	

	_hoops_IHAIH = 3;
	ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 3, double, 8);
	_hoops_HHAIH[0] = x;
	_hoops_HHAIH[1] = y;
	_hoops_HHAIH[2] = z;

	key = HC_QKInsert_Image (segment, x, y, z, format, width, height, _hoops_SHGGR);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_RSPIH */


HC_EXTERNAL HD_API void HC_DMove_Image (
				HC_KEY _hoops_PCAIH,
				double x,
				double y,
				double z)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;
	if (node->_hoops_HHAIH == 0) return;

	node->_hoops_HHAIH[0] = x;
	node->_hoops_HHAIH[1] = y;
	node->_hoops_HHAIH[2] = z;

} /* _hoops_RSGR _hoops_API _hoops_ASPIH */


HC_EXTERNAL HD_API void HC_DShow_Image (
				HC_KEY _hoops_PCAIH,
				double *x,
				double *y,
				double *z,
				char   *format,
				int	   *width,
				int	   *height,
				void   *_hoops_SHGGR) 
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;
	if (node->_hoops_HHAIH == 0) return;

	if (x != 0) *x = node->_hoops_HHAIH[0];
	if (y != 0) *y = node->_hoops_HHAIH[1];
	if (z != 0) *z = node->_hoops_HHAIH[2];
	HC_Show_Image (key, 0, 0, 0, format, width, height, _hoops_SHGGR);

} /* _hoops_RSGR _hoops_API _hoops_PSPIH */


/*
 * _hoops_HSPIH
 */

HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Local_Light (
				const char *segment,
				double	   x,
				double	   y,
				double	   z) 
{
	int _hoops_IHAIH = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	

	_hoops_IHAIH = 3;
	ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 3, double, 8);
	_hoops_HHAIH[0] = x;
	_hoops_HHAIH[1] = y;
	_hoops_HHAIH[2] = z;

	key = HC_QKInsert_Local_Light (segment, x, y, z);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_ISPIH */


HC_EXTERNAL HD_API void HC_DShow_Local_Light (
				HC_KEY _hoops_PCAIH,
				double	   *x,
				double	   *y,
				double	   *z) 
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;
	if (node->_hoops_HHAIH == 0) return;

	if (x != 0) *x = node->_hoops_HHAIH[0];
	if (y != 0) *y = node->_hoops_HHAIH[1];
	if (z != 0) *z = node->_hoops_HHAIH[2];

} /* _hoops_RSGR _hoops_API _hoops_CSPIH */


/*
 * _hoops_SSPIH
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Spot_Light (
				const char		*segment,
				const HCD_POINT *position,
				const HCD_POINT *target,
				const char		*list) 
{
	int _hoops_IHAIH = 0, _hoops_HRPPA = 0;
	float *_hoops_AIPCP = 0, *f1 = 0;
	double *_hoops_HHAIH = 0, *_hoops_GIGCR = 0;
	HC_KEY key;

	

	if (position != 0) {
		_hoops_IHAIH = 3;
		_hoops_HHAIH = _hoops_AIAIH ((double *)position, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}
	if (target != 0) {
		_hoops_HRPPA = 3;
		_hoops_GIGCR = _hoops_AIAIH ((double *)target, _hoops_HRPPA);
		f1 = _hoops_IIAIH (_hoops_GIGCR, _hoops_HRPPA);
	}

	key = HC_QKInsert_Spot_Light (
		segment,
		_hoops_AIPCP,
		f1,
		list);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, _hoops_HRPPA, _hoops_GIGCR, 0,0,0,0);

	if (_hoops_AIPCP != 0) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);
	if (f1 != 0) FREE_ARRAY (f1, _hoops_HRPPA, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_GGHIH */


HC_EXTERNAL HD_API void HC_DShow_Spot_Light(
				HC_KEY	  _hoops_PCAIH,
				HCD_POINT *position,
				HCD_POINT *target,
				char	  *list)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Spot_Light (key, 0, 0, list);
	if (node == 0) return;

	_hoops_PIAIH ((double *)position, node->_hoops_HHAIH, 3);
	_hoops_PIAIH ((double *)target, node->_hoops_GIGCR, 3);

} /* _hoops_RSGR _hoops_API _hoops_RGHIH */


/*
 * _hoops_AGHIH
 */

HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Distant_Light (
				const char *segment,
				double	   x,
				double	   y,
				double	   z) 
{
	int _hoops_IHAIH = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	

	_hoops_IHAIH = 3;
	ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 3, double, 8);
	_hoops_HHAIH[0] = x;
	_hoops_HHAIH[1] = y;
	_hoops_HHAIH[2] = z;

	key = HC_QKInsert_Distant_Light (segment, x, y, z);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_PGHIH */


HC_EXTERNAL HD_API void HC_DMove_Distant_Light (
				HC_KEY _hoops_PCAIH,
				double	   x,
				double	   y,
				double	   z) 
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;
	if (node->_hoops_HHAIH == 0) return;

	node->_hoops_HHAIH[0] = x;
	node->_hoops_HHAIH[1] = y;
	node->_hoops_HHAIH[2] = z;

} /* _hoops_RSGR _hoops_API _hoops_HGHIH */


HC_EXTERNAL HD_API void HC_DShow_Distant_Light (
				HC_KEY _hoops_PCAIH,
				double	   *x,
				double	   *y,
				double	   *z) 
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;
	if (node->_hoops_HHAIH == 0) return;

	if (x != 0) *x = node->_hoops_HHAIH[0];
	if (y != 0) *y = node->_hoops_HHAIH[1];
	if (z != 0) *z = node->_hoops_HHAIH[2];

} /* _hoops_RSGR _hoops_API _hoops_IGHIH */


/*
 * _hoops_CGHIH
 */


HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Area_Light (
				const char	 *segment,
				int			 pcount,
				const HCD_POINT *points,
				const char	 *list)
{
	int _hoops_IHAIH = 0;
	float *_hoops_AIPCP = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	

	if (points != 0) {
		_hoops_IHAIH = 3 * pcount;
		_hoops_HHAIH = _hoops_AIAIH ((double *)points, _hoops_IHAIH);
		_hoops_AIPCP = _hoops_IIAIH (_hoops_HHAIH, _hoops_IHAIH);
	}

	key = HC_QKInsert_Area_Light (segment, pcount, _hoops_AIPCP, list);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	if (_hoops_AIPCP) FREE_ARRAY (_hoops_AIPCP, _hoops_IHAIH, float);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_SGHIH */



HC_EXTERNAL HD_API void HC_DShow_Area_Light (
				HC_KEY _hoops_PCAIH,
				int	   *pcount,
				HCD_POINT *points,
				char   *list)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	HC_Show_Area_Light (key, pcount, 0, list); 
	if (node == 0) return;
	
	_hoops_PIAIH ((double *)points, node->_hoops_HHAIH, node->_hoops_IHAIH);

} /* _hoops_RSGR _hoops_API _hoops_GRHIH */


/*
 * _hoops_HPSCP
 */

HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Text (
				const char *segment,
				double	   x,
				double	   y,
				double	   z,
				const char *string) 
{
	int _hoops_IHAIH = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	

	_hoops_IHAIH = 3;
	ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 3, double, 8);

	_hoops_HHAIH[0] = x;
	_hoops_HHAIH[1] = y;
	_hoops_HHAIH[2] = z;

	key = HC_QKInsert_Text (segment, x, y, z, string);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_RRHIH */


HC_EXTERNAL HD_API void HC_DShow_Text (
				HC_KEY _hoops_PCAIH,
				double *x,
				double *y,
				double *z,
				char *string) 
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;
	if (node->_hoops_HHAIH == 0) return;

	if (x != 0) *x = node->_hoops_HHAIH[0];
	if (y != 0) *y = node->_hoops_HHAIH[1];
	if (z != 0) *z = node->_hoops_HHAIH[2];
	HC_Show_Text (key, 0, 0, 0, string);

} /* _hoops_RSGR _hoops_API _hoops_ARHIH */


/*
 * _hoops_PRHIH
 */

HC_EXTERNAL HD_API HC_KEY HC_DQKInsert_Text_With_Encoding (
				const char *segment,
				double	   x,
				double	   y,
				double	   z,
				char const *encoding, 
				void const *string) 
{
	int _hoops_IHAIH = 0;
	double *_hoops_HHAIH = 0;
	HC_KEY key;

	

	_hoops_IHAIH = 3;
	ALLOC_ARRAY_ALIGNED (_hoops_HHAIH, 3, double, 8);

	_hoops_HHAIH[0] = x;
	_hoops_HHAIH[1] = y;
	_hoops_HHAIH[2] = z;

	key = HC_QKInsert_Text_With_Encoding (segment, x, y, z, encoding, string);
	_hoops_SIAIH (key, _hoops_IHAIH, _hoops_HHAIH, 
				0,0,0,0,0,0);

	return key;

} /* _hoops_RSGR _hoops_API _hoops_HRHIH */


HC_EXTERNAL HD_API void HC_DShow_Text_With_Encoding (
				HC_KEY _hoops_PCAIH,
				double *x,
				double *y,
				double *z,
				char *encoding,
				void *string) 
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	
	
	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) return;
	if (node->_hoops_HHAIH == 0) return;

	if (x != 0) *x = node->_hoops_HHAIH[0];
	if (y != 0) *y = node->_hoops_HHAIH[1];
	if (z != 0) *z = node->_hoops_HHAIH[2];
	HC_Show_Text_With_Encoding (key, 0, 0, 0, encoding, string);

} /* _hoops_RSGR _hoops_API _hoops_IRHIH */


/*
 * _hoops_SSSA _hoops_ACPIH
 */


typedef struct {
	const HCD_POINT *points;
	const float *normals;
} _hoops_CRHIH;


/* _hoops_PGAA
 * _hoops_AGAH _hoops_GRS _hoops_AASA _hoops_RGR _hoops_API _hoops_CGPR _hoops_SCH _hoops_APSI _hoops_IS _hoops_CGIC _hoops_RPP _hoops_PGCR _hoops_RAGA _hoops_RSSA
 * _hoops_CHR _hoops_HRRHA _hoops_PAR _hoops_HAR.
 * _hoops_SR _hoops_SRHIH _hoops_IRS _hoops_CRS _hoops_IS _hoops_IRS _hoops_RRSAR _hoops_HRPR _hoops_RHIR _hoops_RH _hoops_ASGA _hoops_CRS.
 */
static int _hoops_GAHIH (
				void			*_hoops_CGAHA,
				void			*_hoops_SGAHA,
				int				a,
				int				b,
				double			_hoops_HARHA,
				double			_hoops_IARHA) 
{
	_hoops_CRHIH *info= (_hoops_CRHIH *) _hoops_SGAHA;
	const double *points = (const double *)info->points;
	const double *p1, *p2;
	const float *normals = info->normals;
	const float *_hoops_ICIPR, *_hoops_CCIPR;
	double delta;
	double dist; /* _hoops_GRAHA _hoops_RRAHA _hoops_GIRA */

	(void)_hoops_CGAHA;		/* _hoops_GCGHA */

	if (points != 0)
	{
		p1 = points + a * 3;
		p2 = points + b * 3;

		delta = p1[0] - p2[0];
		dist =	delta*delta;
		delta = p1[1] - p2[1];
		dist += delta*delta;
		delta = p1[2] - p2[2];
		if ((dist +	delta*delta) > _hoops_HARHA) 
			return 0;
	}

	if (normals != 0)
	{
		_hoops_ICIPR = normals + a * 3;
		_hoops_CCIPR = normals + b * 3;

		delta = _hoops_ICIPR[0] - _hoops_CCIPR[0];
		dist =	delta*delta;
		delta = _hoops_ICIPR[1] - _hoops_CCIPR[1];
		dist += delta*delta;
		delta = _hoops_ICIPR[2] - _hoops_CCIPR[2];
		if ((dist +	delta*delta) > _hoops_IARHA) 
			return 0;
	}

	return 1;

} /* _hoops_RSGR _hoops_API _hoops_RAHIH */


HC_EXTERNAL HD_API void HC_CDECL HC_DCompute_Optimized_Shell (
				int				in_point_count,
				const HCD_POINT *_hoops_HSHRA,
				const float		*_hoops_ISHRA,
				int				in_face_list_length,
				const int		*in_face_list,
				const char		*option_string,
				int				*out_point_count,
				HCD_POINT		*_hoops_CSHRA,
				int				*out_face_list_length,
				int				*out_face_list,
				int				*vertex_mapping,
				int				*face_mapping) 
{
	const _hoops_APCIR *in_points = (const _hoops_APCIR *)_hoops_HSHRA;
	_hoops_APCIR *out_points = (_hoops_APCIR *)_hoops_CSHRA;
	char _hoops_RICIA[1028];
	int *_hoops_IHRHH;
	int i;
	float *_hoops_AIPCP = 0;
	_hoops_CRHIH info;
	info.points=in_points;
	info.normals=_hoops_ISHRA;

	/* _hoops_ARP _hoops_GH _hoops_RH _hoops_AAP _hoops_HIS _hoops_SGS _hoops_ISCP _hoops_GRH _hoops_CAPGR _hoops_GRS _hoops_SHH _hoops_PIGS */
	HC_Define_Callback_Name ("are_collapsible_callback", (_hoops_IRPCR) _hoops_GAHIH);
	_hoops_RICIA[0] = '\0';
	if  ((option_string == 0) ||  (strlen (option_string) != 0)) { 
		strcpy (_hoops_RICIA, option_string);
		strcat (_hoops_RICIA, ",");
	}
	strcat (_hoops_RICIA, "collapsible = are_collapsible_callback");

	/* _hoops_ARPR _hoops_IRS _hoops_RSRA _hoops_GPPS _hoops_CSPP _hoops_IIGR _hoops_RH _hoops_RSSA _hoops_IS _hoops_RIH _hoops_IS _hoops_CHARP */
	_hoops_AIPCP = _hoops_IIAIH ((double *)in_points, 3*in_point_count);

	/* _hoops_PRGI _hoops_RPP _hoops_RH _hoops_IPSP _hoops_GPGH'_hoops_RA _hoops_GPIHR, _hoops_SR'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_RRP _hoops_IRS _hoops_GPHA _hoops_SIA _hoops_CRPR */
	if (vertex_mapping == 0) {
		ALLOC_ARRAY (_hoops_IHRHH, in_point_count, int);
	}
	else
		_hoops_IHRHH = vertex_mapping;

	/* _hoops_IGGPH _hoops_IIGR _hoops_RH _hoops_IPHR _hoops_HRGR _hoops_CPHR _hoops_HRGR _hoops_RSRA _hoops_GPPS, _hoops_HIH _hoops_SGH _hoops_RH _hoops_CAPGR _hoops_CCHGR _hoops_IS
	 * _hoops_AA _hoops_RH _hoops_HRRHA _hoops_RPGP _hoops_GGR _hoops_GHGPR _hoops_GPPS.	 _hoops_CHPR _hoops_ISCP _hoops_AAHIH _hoops_RRSAR _hoops_HRPR
	 * _hoops_CAS _hoops_RH _hoops_ASGA _hoops_CHH _hoops_SIGHR _hoops_PHHR.  */
	HC_Compute_Optimized_Shell (
				in_point_count, _hoops_AIPCP, (void *)(&info), 
				in_face_list_length, in_face_list,
				_hoops_RICIA,
				out_point_count, _hoops_AIPCP, /* _hoops_PHHR _hoops_IAISR _hoops_PPR _hoops_GRPHA _hoops_GPP _hoops_PAHIH */	
				out_face_list_length, out_face_list,
				_hoops_IHRHH, face_mapping 
	);
	
	/* _hoops_SGH _hoops_RH _hoops_GPHA _hoops_SIA _hoops_CRPR _hoops_IS _hoops_GHPHR _hoops_RH _hoops_IIPR _hoops_CRPR _hoops_IIGR _hoops_RSSA */ 
	if (out_points != 0) {
		for (i = 0; i < in_point_count; i++) {
			if (_hoops_IHRHH[i] >= 0) {
				_hoops_PIAIH ((double *)(&out_points[_hoops_IHRHH[i]]),
							 (double *)(&in_points[i]),
							 3);
			}
		}
	}

	/* _hoops_CASI _hoops_GH _hoops_ISCP _hoops_GPGSA */
	if (_hoops_AIPCP) FREE_ARRAY (_hoops_AIPCP, 3*in_point_count, float);
	if ((vertex_mapping == 0) &&  (_hoops_IHRHH != 0)) 
		FREE_ARRAY (_hoops_IHRHH, in_point_count, int);
	HC_UnDefine_Callback_Name ("are_collapsible_callback");

} /* _hoops_RSGR _hoops_API _hoops_PHGHA */
  

typedef double _hoops_HAHIH[4];
HC_EXTERNAL HD_API void HC_DCompute_Transformed_Points (
				int pcount,
				const HCD_POINT *points,
				const double *matrix,
				HCD_POINT *result)
{
	const _hoops_HAHIH *m = (const _hoops_HAHIH *)matrix;
	double x, y, z, w, _hoops_PIIPA;
	const double *in = (double *)points;
	double *_hoops_PAGR = (double *)result;

	while (--pcount >= 0) {
		x = in[0]*m[0][0] + in[1]*m[1][0] + in[2]*m[2][0] + m[3][0];
		y = in[0]*m[0][1] + in[1]*m[1][1] + in[2]*m[2][1] + m[3][1];
		z = in[0]*m[0][2] + in[1]*m[1][2] + in[2]*m[2][2] + m[3][2];
		w = in[0]*m[0][3] + in[1]*m[1][3] + in[2]*m[2][3] + m[3][3];

		if	(w != 0.0) {
			_hoops_PIIPA = 1.0 / w;
			x *= _hoops_PIIPA;
			y *= _hoops_PIIPA;
			z *= _hoops_PIIPA;
		}
		else {
			/* _hoops_HIIPA ? */
		}

		_hoops_PAGR[0] = x;
		_hoops_PAGR[1] = y;
		_hoops_PAGR[2] = z;

		in += 3;
		_hoops_PAGR += 3;
	}

} /* _hoops_RSGR _hoops_API _hoops_IAHIH */


/* _hoops_PIP _hoops_SGS _hoops_RGR _hoops_HRGR _hoops_HAR _hoops_IRS _hoops_IHPR _hoops_GHGPR _hoops_GPPS _hoops_PCPH, _hoops_CR
 * _hoops_SCH _hoops_CAHIH _hoops_RSRA _hoops_GPPS _hoops_HCIA _hoops_HII _hoops_AGAH */
bool HC_DCompute_Coordinates (
				const char		*segment,
				const char		*in_system,
				const HCD_POINT *_hoops_CAACA,
				const char		*out_system,
				HCD_POINT		*_hoops_SAACA) 
{
	double _hoops_SAHIH[16];
	float _hoops_GPHIH[16];
	int i;

	HC_Compute_Transform (segment, in_system, out_system, _hoops_GPHIH);
	for (i = 0; i < 16; i++)
		_hoops_SAHIH[i] = (double) _hoops_GPHIH[i];

	HC_DCompute_Transformed_Points (1, _hoops_CAACA, _hoops_SAHIH, _hoops_SAACA);
	return true;

} /* _hoops_RSGR _hoops_API _hoops_RPHIH */


static void _hoops_APHIH(
	_hoops_PHAIH *info,
	HC_KEY _hoops_HCIS,
	void const * const _hoops_AGPAR) 
{
	_hoops_GCAIH(info);

	UNREFERENCED(_hoops_HCIS);
	UNREFERENCED(_hoops_AGPAR);
}


HC_EXTERNAL HD_API void HC_CDECL HI_DCleanup()
{
	if (global_hcd_table) {
		_hoops_RIAIH()->MapFunction(_hoops_APHIH, 0);
		delete _hoops_RIAIH();
		global_hcd_table = 0;
	}
}


HC_EXTERNAL HD_API int HC_DShow_Existence_By_Key(HC_KEY _hoops_PCAIH)
{
	_hoops_PHAIH *node = 0;
	HC_KEY key = HC_KShow_Original_Key (_hoops_PCAIH);

	

	_hoops_RIAIH()->LookupItem(key, &node);
	if (node == 0) 
		return 0;
	else
		return -1;

}



#else

HC_EXTERNAL HD_API void HC_DCompute_Optimized_Shell  () {}
HC_EXTERNAL HD_API void HC_DCompute_Coordinates	() {}
HC_EXTERNAL HD_API void HC_DCompute_Transformed_Points	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_NURBS_Curve		() {}
HC_EXTERNAL HD_API void HC_DEdit_NURBS_Curve	() {}
HC_EXTERNAL HD_API void HC_DShow_NURBS_Curve		() {}
HC_EXTERNAL HD_API void HC_DQKInsert_NURBS_Surface	() {}
HC_EXTERNAL HD_API void HC_DEdit_NURBS_Surface	() {}
HC_EXTERNAL HD_API void HC_DShow_NURBS_Surface	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Shell	() {}
HC_EXTERNAL HD_API void HC_DEdit_Shell_Points	() {}
HC_EXTERNAL HD_API void HC_DShow_Shell	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Grid	() {}
HC_EXTERNAL HD_API void HC_DShow_Grid	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Mesh	() {}
HC_EXTERNAL HD_API void HC_DEdit_Mesh	() {}
HC_EXTERNAL HD_API void HC_DShow_Mesh	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Polyline	() {}
HC_EXTERNAL HD_API void HC_DEdit_Polyline	() {}
HC_EXTERNAL HD_API void HC_DShow_Polyline	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Ink	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Line	() {}
HC_EXTERNAL HD_API void HC_DShow_Line	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Polygon	() {}
HC_EXTERNAL HD_API void HC_DEdit_Polygon	() {}
HC_EXTERNAL HD_API void HC_DShow_Polygon	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Marker	() {}
HC_EXTERNAL HD_API void HC_DShow_Marker	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Cylinder	() {}
HC_EXTERNAL HD_API void HC_DShow_Cylinder	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Circle	() {}
HC_EXTERNAL HD_API void HC_DShow_Circle	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Circular_Arc	() {}
HC_EXTERNAL HD_API void HC_DShow_Circular_Arc	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Circular_Chord	() {}
HC_EXTERNAL HD_API void HC_DShow_Circular_Chord	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Circular_Wedge	() {}
HC_EXTERNAL HD_API void HC_DShow_Circular_Wedge	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Ellipse	() {}
HC_EXTERNAL HD_API void HC_DShow_Ellipse	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Elliptical_Arc	() {}
HC_EXTERNAL HD_API void HC_DShow_Elliptical_Arc	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Cutting_Plane	() {}
HC_EXTERNAL HD_API void HC_DShow_Cutting_Plane	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Image	() {}
HC_EXTERNAL HD_API void HC_DMove_Image	() {}
HC_EXTERNAL HD_API void HC_DShow_Image	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Local_Light	() {}
HC_EXTERNAL HD_API void HC_DShow_Local_Light	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Spot_Light	() {}
HC_EXTERNAL HD_API void HC_DShow_Spot_Light	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Distant_Light	() {}
HC_EXTERNAL HD_API void HC_DMove_Distant_Light	() {}
HC_EXTERNAL HD_API void HC_DShow_Distant_Light	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Area_Light	() {}
HC_EXTERNAL HD_API void HC_DShow_Area_Light	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Text	() {}
HC_EXTERNAL HD_API void HC_DShow_Text	() {}
HC_EXTERNAL HD_API void HC_DQKInsert_Text_With_Encoding	() {}
HC_EXTERNAL HD_API void HC_DShow_Text_With_Encoding	() {}
HC_EXTERNAL HD_API void HC_DSet_Camera	() {}
HC_EXTERNAL HD_API void HC_DSet_Camera_Position	() {}
HC_EXTERNAL HD_API void HC_DSet_Camera_Target	() {}
HC_EXTERNAL HD_API void HC_DSet_Camera_Up_Vector	() {}
HC_EXTERNAL HD_API void HC_DSet_Camera_Field	() {}
HC_EXTERNAL HD_API void HC_DShow_Camera	() {}
HC_EXTERNAL HD_API void HC_DShow_Camera_Position	() {}
HC_EXTERNAL HD_API void HC_DShow_Camera_Target	() {}
HC_EXTERNAL HD_API void HC_DShow_Camera_Up_Vector	() {}
HC_EXTERNAL HD_API void HC_DShow_Camera_Field	() {}
HC_EXTERNAL HD_API void HC_DCleanup() {}
HC_EXTERNAL HD_API void HC_DFlush_Contents () {}
HC_EXTERNAL HD_API void HC_DFlush_By_Key () {}

#endif



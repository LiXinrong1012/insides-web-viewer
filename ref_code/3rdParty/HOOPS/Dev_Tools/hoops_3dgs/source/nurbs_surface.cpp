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
 * $Id: obf_tmp.txt 1.65 2010-10-06 19:16:00 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "phedron.h"



struct _hoops_ACSSI {
	int					u_degree;
	int					v_degree;
	int					n_u_vertices;
	int					n_v_vertices;
	Point const *		control_points;
	float const *		weights;
	float const *		u_knots;
	float const *		v_knots;
	bool				_hoops_SHCIH;

	_hoops_APPGR *		surface;
	int					_hoops_IGSSR;
};

#ifndef _hoops_GSPIR

local bool _hoops_PCSSI (
	_hoops_ACSSI *	data)
{
	if (data->u_degree == 0 &&
		data->v_degree == 0 &&
		data->n_u_vertices == 0 &&
		data->n_v_vertices == 0)
		return true;

	if ((data->u_degree < 0) ||
		(data->v_degree < 0) ||
		(data->n_u_vertices < 0) ||
		(data->n_v_vertices < 0)) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_COUNT, "Negative number given to nurbs surface for vertex count and/or degree");
		return false;
	}

	if (data->u_knots != null) {
		int _hoops_CGHSA = 0;
		for (int i = 1; i < data->n_u_vertices + data->u_degree + 1; i++) {
			if (data->u_knots[i] < data->u_knots[i-1]) {
				HE_ERROR (HEC_SURFACE, HES_BAD_VALUE, "u_knot values in Insert_NURBS_Surface must be nondecreasing");
				return false;
			}
			else if (data->u_knots[i] == data->u_knots[i-1])
				_hoops_CGHSA++;
			else
				_hoops_CGHSA = 0;
			if (_hoops_CGHSA > data->u_degree + 1) {
				HE_ERROR (HEC_SURFACE, HES_BAD_VALUE, "u_knot multiplicity greater than the order is not supported in Insert_NURBS_Surface");
				return false;
			}
		}
	}

	if (data->v_knots != null) {
		int _hoops_CGHSA = 0;
		for (int i = 1; i < data->n_v_vertices + data->v_degree + 1; i++) {
			if (data->v_knots[i] < data->v_knots[i-1]) {
				HE_ERROR (HEC_SURFACE, HES_BAD_VALUE, "v_knot values in Insert_NURBS_Surface must be nondecreasing");
				return false;
			}
			else if (data->v_knots[i] == data->v_knots[i-1])
				_hoops_CGHSA++;
			else
				_hoops_CGHSA = 0;
			if (_hoops_CGHSA > data->v_degree + 1) {
				HE_ERROR (HEC_SURFACE, HES_BAD_VALUE, "v_knot multiplicity greater than the order is not supported in Insert_NURBS_Surface");
				return false;
			}
		}
	}

	if (data->u_degree >= data->n_u_vertices) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_COUNT, "NURBS Surface n_u_vertices must be at least u_degree + 1");
		return false;
	}

	if (data->v_degree >= data->n_v_vertices) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_COUNT, "NURBS Surface n_v_vertices must be at least v_degree + 1");
		return false;
	}

	return true;
}


#define _hoops_CACIR (1e-5f)
local bool _hoops_HCSSI(_hoops_APPGR const *surface)
{
	/* _hoops_CSGA _hoops_SHHP _hoops_HPAHR _hoops_IS _hoops_CGIC _hoops_IPPA _hoops_CGSSR */
	Point * p1 = &surface->control_points[0];
	Point *	p2 = &surface->control_points[surface->n_u_vertices - 1];
	Point *	_hoops_IAPH = &surface->control_points[surface->n_v_vertices * surface->n_u_vertices - 1];

	Vector _hoops_ISPI = *p1 - *p2;
	Vector _hoops_CSPI = *p1 - *_hoops_IAPH;

	_hoops_ARPA plane = _hoops_ARPA (_hoops_ISPI._hoops_SAIAR(_hoops_CSPI), *p1);
	if (Vector(plane._hoops_AAIAR())._hoops_PPSSR() < 1.0e-20f)
		return false;

	float _hoops_HRPPA = _hoops_ISPI._hoops_PPSSR();
	float _hoops_SPPPA = _hoops_CSPI._hoops_PPSSR();

	float tolerance;

	if (_hoops_HRPPA > _hoops_SPPPA)
		tolerance = _hoops_CACIR * _hoops_SGIHR(_hoops_HRPPA);
	else
		tolerance = _hoops_CACIR * _hoops_SGIHR(_hoops_SPPPA);

	for (int i = 0; i < surface->n_v_vertices * surface->n_u_vertices; i++) {
		Point *	p = &surface->control_points[i];
		float _hoops_AIHIA = p->x*plane.a + p->y*plane.b + p->z*plane.c + plane.d;
		if (_hoops_AIHIA > tolerance || _hoops_AIHIA < -tolerance)
			return false;
	}
	return true;
}


local void _hoops_ICSSI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ACSSI *		data)
{
	_hoops_APPGR *	surface;
	ZALLOC (surface, _hoops_APPGR);

	surface->type = _hoops_PRCP;
	surface->_hoops_CPGPR = _hoops_PHSSR;

	/* _hoops_IPS _hoops_RH _hoops_PICAA _hoops_IAGH */
	surface->u_degree = data->u_degree;
	surface->v_degree = data->v_degree;
	surface->n_u_vertices = data->n_u_vertices;
	surface->n_v_vertices = data->n_v_vertices;

	/* _hoops_CCPP _hoops_PPR _hoops_HSPC _hoops_RH _hoops_HAHH _hoops_SIRGR _hoops_IH _hoops_RH _hoops_ISSGR */
	int	control_point_count = data->n_u_vertices*data->n_v_vertices;

	bool	_hoops_IGHSA = true; /* _hoops_HPCAR 2d _hoops_CCGR _hoops_SR _hoops_SSS _hoops_IAII */

	if (control_point_count) {
		ALLOC_ARRAY (surface->control_points, control_point_count, Point);
		for (int i = 0; i < control_point_count; i++) {
			surface->control_points[i].x = data->control_points[i].x;
			surface->control_points[i].y = data->control_points[i].y;
			surface->control_points[i].z = data->control_points[i].z;
			if (data->control_points[i].z != 0.0f) _hoops_IGHSA = false;
		}
	}
	else
		surface->control_points = null;
	if (data->u_knots != null) {
		ALLOC_ARRAY (surface->u_knots, data->n_u_vertices + data->u_degree + 1, float);
		for (int i = 0; i < data->n_u_vertices + data->u_degree + 1; i++)
			surface->u_knots[i] = data->u_knots[i];
	}
	else
		surface->u_knots = null;
	if (data->v_knots != null) {
		ALLOC_ARRAY (surface->v_knots, data->n_v_vertices + data->v_degree + 1, float);
		for (int i = 0; i < data->n_v_vertices + data->v_degree + 1; i++)
			surface->v_knots[i] = data->v_knots[i];
	}
	else
		surface->v_knots = null;
	if (data->weights != null) {
		ALLOC_ARRAY (surface->weights, control_point_count, float);
		for (int i = 0; i < control_point_count; i++) {
			surface->weights[i] = data->weights[i];
			if (surface->weights[i] < 0)
				surface->_hoops_SHIAA |= _hoops_GIIAA;
		}
	}
	else {
		surface->weights = null;
	}
	surface->_hoops_IPRI = null;
	surface->_hoops_GPRIR = null;

	if (surface->n_u_vertices == 2 &&
		surface->n_v_vertices == 2 &&
		_hoops_HCSSI(surface))
		surface->_hoops_SHIAA |= _hoops_CCSSI;

	HI_Insert_Geometry (_hoops_RIGC, item, (Geometry *) surface,
						_hoops_IGHSA,
						_hoops_IHSSR|_hoops_SIGPR);

	data->surface = surface;
	++data->_hoops_IGSSR;
}
#endif



GLOBAL_FUNCTION Key HI_Insert_NURBS_Surface (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						u_degree,
	int						v_degree,
	int						n_u_vertices,
	int						n_v_vertices,
	Point const *			control_points,
	float const *			weights,
	float const *			u_knots,
	float const *			v_knots)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_ACSSI data;
	ZERO_STRUCT(&data, _hoops_ACSSI);
	data.u_degree = u_degree;
	data.v_degree = v_degree;
	data.n_u_vertices = n_u_vertices;
	data.n_v_vertices = n_v_vertices;
	data.control_points = control_points;
	data.weights = weights;
	data.u_knots = u_knots;
	data.v_knots = v_knots;

	if (_hoops_PCSSI (&data))
		_hoops_ICSSI (_hoops_RIGC, item, &data);

	Key _hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.surface);

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_NURBS_Surface (
	int						u_degree,
	int						v_degree,
	int						n_u_vertices,
	int						n_v_vertices,
	Point const *			control_points,
	float const *			weights,
	float const *			u_knots,
	float const *			v_knots)
{
	_hoops_PAPPR context("Insert_NURBS_surface");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_NURBS_Surface (context, target,
			u_degree, v_degree, n_u_vertices, n_v_vertices, control_points, weights, u_knots, v_knots);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		int		count2 = n_u_vertices * n_v_vertices;
		int		_hoops_SCSSI = n_u_vertices + u_degree + 1;
		int		_hoops_GSSSI = n_v_vertices + v_degree + 1;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", n_u_vertices*n_v_vertices));
		if (weights != null)
			HI_Dump_Code (Sprintf_D (null, "float* weights = (float*) malloc(sizeof(float)*%d);\n", n_u_vertices*n_v_vertices));
		else
			HI_Dump_Code ("float *weights = NULL;\n");
		if (u_knots != null)
			HI_Dump_Code (Sprintf_D (null, "float* u_knots = (float*) malloc(sizeof(float)*%d);\n", _hoops_SCSSI));
		else
			HI_Dump_Code ("float *u_knots = NULL;\n");
		if (v_knots != null)
			HI_Dump_Code (Sprintf_D (null, "float* v_knots = (float*) malloc(sizeof(float)*%d);\n", _hoops_GSSSI));
		else
			HI_Dump_Code ("float *v_knots = NULL;\n");
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", count2, control_points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", count2, control_points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n", count2, control_points[count2].z));
		}
		if (weights != null) {
			count2 = n_u_vertices * n_v_vertices;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (_hoops_CHCHR (null, "weights[%d] = %f;\n", count2, weights[count2]));
			}
		}
		if (u_knots != null) {
			count2 = _hoops_SCSSI;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (_hoops_CHCHR (null, "u_knots[%d] = %f;\n", count2, u_knots[count2]));
			}
		}
		if (v_knots != null) {
			count2 = _hoops_GSSSI;
			_hoops_RGGA (count2-- == 0) {
				HI_Dump_Code (_hoops_CHCHR (null, "v_knots[%d] = %f;\n", count2, v_knots[count2]));
			}
		}
		HI_Dump_Code (Sprintf_DD (null, "DEFINE (HC_Insert_NURBS_Surface (%d, %d, ", u_degree, v_degree));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, points, weights, u_knots, v_knots), ", n_u_vertices, n_v_vertices));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (points);\n");
		HI_Dump_Code ("free (weights);\n");
		HI_Dump_Code ("free (u_knots);\n");
		HI_Dump_Code ("free (v_knots);}\n");
		--HOOPS_WORLD->_hoops_ISPPR;
	);
#endif
	return _hoops_CHSSR;
}




HC_INTERFACE void HC_CDECL HC_Show_NURBS_Surface_Size (
	Key					key,
	int alter *			u_degree,
	int alter *			v_degree,
	int alter *			n_u_vertices,
	int alter *			n_v_vertices,
	int alter *			weights_count,
	int alter *			u_knots_count,
	int alter *			v_knots_count)
{
	_hoops_PAPPR context("Show_NURBS_Surface_Size");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_NURBS_Surface_Size () */\n");
	);

	_hoops_CSPPR();

	_hoops_APPGR *	surface = (_hoops_APPGR *)_hoops_RCSSR (context, key);

	if (surface == null ||
		surface->type != _hoops_PRCP ||
		BIT (surface->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Provided key does not refer to a valid nurbs surface");
	}
	else {
		if (u_degree != null)
			*u_degree = surface->u_degree;
		if (v_degree != null)
			*v_degree = surface->v_degree;
		if (n_u_vertices != null)
			*n_u_vertices = surface->n_u_vertices;
		if (n_v_vertices != null)
			*n_v_vertices = surface->n_v_vertices;
		if (weights_count != null)
			*weights_count = ((surface->weights != null) ? (surface->n_u_vertices * surface->n_v_vertices) : 0);
		if (u_knots_count != null)
			*u_knots_count = ((surface->u_knots != null) ? (surface->n_u_vertices + surface->u_degree + 1) : 0);
		if (v_knots_count != null)
			*v_knots_count = ((surface->v_knots != null) ? (surface->n_v_vertices + surface->v_degree + 1) : 0);
	}

	_hoops_IRRPR();
#endif
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_NURBS_Surface (
	Key					key,
	int *				u_degree,
	int *				v_degree,
	int *				n_u_vertices,
	int *				n_v_vertices,
	Point alter *		control_points,
	float alter *		weights,
	float alter *		u_knots,
	float alter *		v_knots)
{
	_hoops_PAPPR context("Show_NURBS_Surface");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_NURBS_Surface () */\n");
	);

	_hoops_CSPPR();

	_hoops_APPGR *	surface = (_hoops_APPGR *)_hoops_RCSSR (context, key);

	if (surface == null ||
		surface->type != _hoops_PRCP ||
		BIT (surface->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_KEY, "Provided key does not refer to a valid nurbs surface");
	}
	else {
		if (u_degree != null)
			*u_degree = surface->u_degree;
		if (v_degree != null)
			*v_degree = surface->v_degree;
		if (n_u_vertices != null)
			*n_u_vertices = surface->n_u_vertices;
		if (n_v_vertices != null)
			*n_v_vertices = surface->n_v_vertices;

		if (control_points != null)
			_hoops_AIGA (surface->control_points,
						 surface->n_u_vertices * surface->n_v_vertices, Point,
						 control_points);
		if (weights != null) {
			if (surface->weights != null) {
				_hoops_AIGA (surface->weights,
						 surface->n_u_vertices * surface->n_v_vertices, float,
						 weights);
			}
			else {
				for (int i = 0; i < surface->n_u_vertices * surface->n_v_vertices; i++) {
					weights[i] = 1.0f;
				}
			}
		}

		if (u_knots != null) {
			int _hoops_RSPIR = (surface->n_u_vertices + surface->u_degree + 1);
			if (surface->u_knots != null) {
				_hoops_AIGA (surface->u_knots, _hoops_RSPIR, float, u_knots);
			}
			else {
				for (int i = 0; i < _hoops_RSPIR; i++) {
					u_knots[i] = (float)i;
				}
			}
		}

		if (v_knots != null) {
			int _hoops_ASPIR = (surface->n_v_vertices + surface->v_degree + 1);
			if (surface->v_knots != null) {
				_hoops_AIGA (surface->v_knots, _hoops_ASPIR, float, v_knots);
			}
			else {
				for (int i = 0; i < _hoops_ASPIR; i++) {
					v_knots[i] = (float)i;
				}
			}
		}
	}

	_hoops_IRRPR();
#endif
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Trim_Count (
	int *				count)
{
	_hoops_PAPPR context("Show_Trim_Count");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Trim_Count () */\n");
	);

	_hoops_APPGR *		surface;
	int					end;
	UV_Trim const *		ptr;

	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim'");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
	}
	else if (context->open_list->_hoops_GCRIR == _hoops_ASRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info._hoops_PSRIR._hoops_IGRPR);
		end = context->open_list->info._hoops_PSRIR.offset;

		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
		for (int i = 0; i < end; i++) {
			if (ptr == null)
				break;
			ptr = ptr->next;
		}
		if (ptr == null || ptr->type != _hoops_CARIR) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open trim does not refer to a valid NURBS surface trim collection");
			return;
		}
		ptr = ((UV_Trim_Collection const *)ptr)->_hoops_GPRIR;
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim'");
		return;
	}
	int i = 0;
	while (ptr != null) {
		i++;
		ptr = ptr->next;
	}
	if (count != null)
		*count = i;
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Trim_Operation(
	int				offset,
	char alter *	operation)
{
	_hoops_PAPPR context("Show_Trim_Operation");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Trim_Operation () */\n");
	);

	_hoops_APPGR *			surface;
	int						end;
	UV_Trim *				ptr;

	/* _hoops_SRS _hoops_SSS _hoops_RH _hoops_CARA _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_GHAA _hoops_RGR _hoops_RGSR _hoops_IS */
	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or an 'Open_Trim'");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
	}
	else if (context->open_list->_hoops_GCRIR == _hoops_ASRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info._hoops_PSRIR._hoops_IGRPR);
		end = context->open_list->info._hoops_PSRIR.offset;

		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
		for (int i = 0; i < end; i++) {
			if (ptr == null)
				break;
			ptr = ptr->next;
		}
		if (ptr == null || ptr->type != _hoops_CARIR) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open trim does not refer to a valid NURBS surface trim collection");
			return;
		}
		ptr = ((UV_Trim_Collection const *)ptr)->_hoops_GPRIR;
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or an 'Open_Trim'");
		return;
	}

	for (int i = 0; i < offset; i++) {
		if (ptr == null)
			break;
		ptr = ptr->next;
	}

	if (ptr->flags & _hoops_RSSSI)
		HI_Return_Chars (operation, -1, "keep", 5);
	else
		HI_Return_Chars (operation, -1, "remove", 7);
#endif
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Trim_Type (
	int				offset,
	char *			type)
{
	_hoops_PAPPR context("Show_Trim_Type");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Trim_Type () */\n");
	);

	_hoops_APPGR		*surface;
	int					end;
	UV_Trim const		*ptr;

	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim' ");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
	}
	else if (context->open_list->_hoops_GCRIR == _hoops_ASRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info._hoops_PSRIR._hoops_IGRPR);
		end = context->open_list->info._hoops_PSRIR.offset;

		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN,
					"Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
		for (int i = 0; i < end; i++) {
			if (ptr == null)
				break;
			ptr = ptr->next;
		}
		if (ptr == null || ptr->type != _hoops_CARIR) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open trim does not refer to a valid NURBS surface trim collection");
			return;
		}
		ptr = ((UV_Trim_Collection const *)ptr)->_hoops_GPRIR;
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim' ");
		return;
	}

	for (int i = 0; i < offset; i++) {
		ptr = ptr->next;
		if (ptr == null)
			break;
	}

	if (ptr == null) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET, "No trim exists at the given offset for the given nurbs surface");
		return;
	}

	switch (ptr->type) {
		case _hoops_PARIR:
				HI_Return_Chars (type, -1, "trim poly", 9);
			break;

		case _hoops_IARIR:
				HI_Return_Chars (type, -1, "trim curve", 10);
			break;

		case _hoops_CARIR:
				HI_Return_Chars (type, -1, "trim collection", 15);
			break;

		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized trim type on the given nurbs surface");
			break;
	}
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Trim_Poly (
	int						offset,
	int *					count,
	float *					uvpoints)
{
	_hoops_PAPPR context("Show_Trim_Poly");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Trim_Poly () */\n");
	);

	_hoops_APPGR const *	surface;
	int						end;
	UV_Trim const *			ptr;

	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim' ");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
	}
	else if (context->open_list->_hoops_GCRIR == _hoops_ASRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info._hoops_PSRIR._hoops_IGRPR);
		end = context->open_list->info._hoops_PSRIR.offset;
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
		for (int i = 0; i < end; i++) {
			if (ptr == null)
				break;
			ptr = ptr->next;
		}
		if (ptr == null || ptr->type != _hoops_CARIR) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open trim does not refer to a valid NURBS surface trim collection");
			return;
		}
		ptr = ((UV_Trim_Collection const *)ptr)->_hoops_GPRIR;
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim' ");
		return;
	}

	for (int i = 0; i < offset; i++) {
		if (ptr == null)
			break;
		ptr = ptr->next;
	}

	if (ptr == null) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET, "No trim exists at the given offset for the given nurbs surface");
		return;
	}
	if (ptr->type != _hoops_PARIR) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_TYPE, "Trim at given offset is not a poly");
		return;
	}

	UV_Trim_Poly const *	_hoops_ASSSI = (UV_Trim_Poly const *)ptr;

	if (count != null)
		*count = _hoops_ASSSI->count;
	if (uvpoints != null)
		_hoops_AIGA (_hoops_ASSSI->points, _hoops_ASSSI->count, UV_Point, uvpoints);

#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Trim_Poly_Count (
	int				offset,
	int *			count)
{
	_hoops_PAPPR context("Show_Trim_Poly_Count");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Trim_Poly_Count () */\n");
	);

	_hoops_APPGR const	*surface;
	int						end;
	UV_Trim const		*ptr;

	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim' ");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
	}
	else if (context->open_list->_hoops_GCRIR == _hoops_ASRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info._hoops_PSRIR._hoops_IGRPR);
		end = context->open_list->info._hoops_PSRIR.offset;

		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
		for (int i = 0; i < end; i++) {
			if (ptr == null)
				break;
			ptr = ptr->next;
		}
		if (ptr == null || ptr->type != _hoops_CARIR) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open trim does not refer to a valid NURBS surface trim collection");
			return;
		}
		ptr = ((UV_Trim_Collection const *)ptr)->_hoops_GPRIR;
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim' ");
		return;
	}
	for (int i = 0; i < offset; i++) {
		if (ptr == null)
			break;
		ptr = ptr->next;
	}

	if (ptr == null) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET, "No trim exists at the given offset for the given nurbs surface");
		return;
	}
	if (ptr->type != _hoops_PARIR) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_TYPE, "Trim at given offset is not a poly");
	}

	UV_Trim_Poly const *	_hoops_ASSSI = (UV_Trim_Poly const *)ptr;

	if (count != null)
		*count = _hoops_ASSSI->count;

#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Trim_Curve (
	int						offset,
	int *					degree,
	int *					control_point_count,
	float *					control_points,
	float *					weights,
	float *					knots,
	float *					start_u,
	float *					end_u)
{
	_hoops_PAPPR context("Show_Trim_Curve");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Trim_Curve () */\n");
	);

	_hoops_APPGR const	*	surface;
	int						end;
	UV_Trim const *			ptr;

	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim' ");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
	}
	else if (context->open_list->_hoops_GCRIR == _hoops_ASRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info._hoops_PSRIR._hoops_IGRPR);
		end = context->open_list->info._hoops_PSRIR.offset;

		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
		for (int i = 0; i < end; i++) {
			if (ptr == null)
				break;
			ptr = ptr->next;
		}
		if (ptr == null || ptr->type != _hoops_CARIR) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open trim does not refer to a valid NURBS surface trim collection");
			return;
		}
		ptr = ((UV_Trim_Collection const *)ptr)->_hoops_GPRIR;
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim' ");
		return;
	}
	for (int i = 0; i < offset; i++) {
		if (ptr == null)
			break;
		ptr = ptr->next;
	}

	if (ptr == null) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET, "No trim exists at the given offset for the given nurbs surface");
		return;
	}
	if (ptr->type != _hoops_IARIR) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_TYPE, "Trim at given offset is not a curve");
	}

	UV_Trim_Curve const *	_hoops_PSSSI = (UV_Trim_Curve const *)ptr;

	if (degree != null)
		*degree = _hoops_PSSSI->degree;
	if (control_point_count != null)
		*control_point_count = _hoops_PSSSI->control_point_count;
	if (control_points != null)
		_hoops_AIGA (_hoops_PSSSI->control_points, _hoops_PSSSI->control_point_count, UV_Point, control_points);
	if (weights != null) {
		if (_hoops_PSSSI->weights != null) {
			_hoops_AIGA (_hoops_PSSSI->weights, _hoops_PSSSI->control_point_count, float, weights);
		}
		else {
			for (int i = 0; i < _hoops_PSSSI->control_point_count; i++) {
				weights[i] = 1.0f;
			}
		}
	}
	if (knots != null) {
		int knot_count = 1 + _hoops_PSSSI->control_point_count + _hoops_PSSSI->degree;
		if (_hoops_PSSSI->knots != null) {
			_hoops_AIGA (_hoops_PSSSI->knots, knot_count, float, knots);
		}
		else {
			for (int i = 0; i < knot_count; i++) {
				knots[i] = (float)i;
			}
		}
	}
	if (start_u != null)
		*start_u = 0;
	if (end_u != null)
		*end_u = 0;

#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Trim_Curve_Count (
	int					offset,
	int *				degree,
	int *				control_point_count,
	int *				weight_count,
	int *				knot_count)
{
	_hoops_PAPPR context("Show_Trim_Curve_Count");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Trim_Curve () */\n");
	);

	_hoops_APPGR const *	surface;
	int						end;
	UV_Trim const *			ptr;

	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim' ");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
	}
	else if (context->open_list->_hoops_GCRIR == _hoops_ASRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info._hoops_PSRIR._hoops_IGRPR);
		end = context->open_list->info._hoops_PSRIR.offset;

		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		ptr = surface->_hoops_GPRIR;
		for (int i = 0; i < end; i++) {
			if (ptr == null)
				break;
			ptr = ptr->next;
		}
		if (ptr == null || ptr->type != _hoops_CARIR) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open trim does not refer to a valid NURBS surface trim collection");
			return;
		}
		ptr = ((UV_Trim_Collection const *)ptr)->_hoops_GPRIR;
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or 'Open_Trim' ");
		return;
	}
	for (int i = 0; i < offset; i++) {
		if (ptr == null)
			break;
		ptr = ptr->next;
	}

	if (ptr == null) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET, "No trim exists at the given offset for the given nurbs surface");
		return;
	}
	if (ptr->type != _hoops_IARIR) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_TYPE, "Trim at given offset is not a curve");
	}

	UV_Trim_Curve const *	_hoops_PSSSI = (UV_Trim_Curve const *)ptr;

	if (degree != null)
		*degree = _hoops_PSSSI->degree;
	if (control_point_count != null)
		*control_point_count = _hoops_PSSSI->control_point_count;
	if (weight_count != null) {
		if (_hoops_PSSSI->weights != null)
			*weight_count = _hoops_PSSSI->control_point_count;
		else
			*weight_count = 0;
	}
	if (knot_count != null) {
		if (_hoops_PSSSI->knots != null)
			*knot_count = 1 + _hoops_PSSSI->control_point_count + _hoops_PSSSI->degree;
		else
			*knot_count = 0;
	}

#endif
#endif
}


#ifndef _hoops_GSPIR
#ifndef DISABLE_GEOMETRY_EDIT
local void _hoops_HSSSI (
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	int						control_point_offset,
	int						weight_offset,
	int						u_knot_offset,
	int						v_knot_offset,
	int						control_point_replace_count,
	int						weight_replace_count,
	int						u_knot_replace_count,
	int						v_knot_replace_count,
	Point const	*			control_points,
	float const *			weights,
	float const *			u_knots,
	float const *			v_knots)
{
	int _hoops_RSPIR, _hoops_ASPIR;
	int _hoops_ISSSI;

	_hoops_RPPPR();

	_hoops_APPGR *	surface = (_hoops_APPGR *)_hoops_RCSSR (_hoops_RIGC, key);

	/* _hoops_HSPP _hoops_CCA _hoops_HHH _hoops_RIHH _hoops_IPAC */
	if (surface == null || surface->type != _hoops_PRCP ||
		BIT (surface->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_KEY, "Key does not refer to a valid nurbs surface");
		goto Release;
	}
	_hoops_ISSSI = surface->n_u_vertices * surface->n_v_vertices;
	if ((control_point_offset < 0) ||
		(control_point_offset + control_point_replace_count > _hoops_ISSSI)) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET,
				Sprintf_DD (null, "Control point offset '%d' not valid (surface has %d vertices)",
						control_point_offset + control_point_replace_count, _hoops_ISSSI));
		goto Release;
	}
	_hoops_RSPIR = surface->n_u_vertices + surface->u_degree + 1;
	if (u_knot_offset < 0 || u_knot_offset + u_knot_replace_count > _hoops_RSPIR) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET,
				Sprintf_DD (null, "Knot offset '%d' not valid (surface has %d u_knots)",
						u_knot_offset + u_knot_replace_count, _hoops_RSPIR));
		goto Release;
	}
	_hoops_ASPIR = surface->n_v_vertices + surface->v_degree + 1;
	if (v_knot_offset < 0 || v_knot_offset + v_knot_replace_count > _hoops_ASPIR) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET,
				Sprintf_DD (null, "Knot offset '%d' not valid (surface has %d v_knots)",
						v_knot_offset + v_knot_replace_count, _hoops_ASPIR));
		goto Release;
	}

	/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GRHSA _hoops_SGCR _hoops_HSH _hoops_SGS _hoops_AAPR _hoops_RRHSA _hoops_IRAP, _hoops_CCPP _hoops_PPR _hoops_HSPC */
	if (surface->weights == null && weights != null) {
		ALLOC_ARRAY (surface->weights, _hoops_ISSSI, float);
		for (int i = 0; i < _hoops_ISSSI; i++)
			surface->weights[i] = 1.0f;
	}
	if (surface->u_knots == null && u_knots != null) {
		ALLOC_ARRAY (surface->u_knots, _hoops_RSPIR, float);
		for (int i = 0; i < _hoops_RSPIR; i++)
			surface->u_knots[i] = (float) i;
	}
	if (surface->v_knots == null && v_knots != null) {
		ALLOC_ARRAY (surface->v_knots, _hoops_ASPIR, float);
		for (int i = 0; i < _hoops_ASPIR; i++)
			surface->v_knots[i] = (float) i;
	}

	/* _hoops_GCSH, _hoops_SR _hoops_PAH _hoops_AA _hoops_RH _hoops_IPHR! */
	if (control_points != null) {
		_hoops_AIGA (control_points, control_point_replace_count, Point,
					&surface->control_points[control_point_offset]);
		surface->_hoops_SHIAA &= ~_hoops_CCSSI;
	}
	if (weights != null)
		_hoops_AIGA (weights, weight_replace_count, float, &surface->weights[weight_offset]);
	if (u_knots != null)
		_hoops_AIGA (u_knots, u_knot_replace_count, float, &surface->u_knots[u_knot_offset]);
	if (v_knots != null)
		_hoops_AIGA (v_knots, v_knot_replace_count, float, &surface->v_knots[v_knot_offset]);

	if (surface->_hoops_IPRI != null) {
		HI_Au_Revoir ((_hoops_HPAH *)surface->_hoops_IPRI);
		surface->_hoops_IPRI = null;
	}

	if (surface->owner)
		HI_Antiquate_Bounding (surface->owner, true);

	_hoops_SASIR (_hoops_RIGC, surface,
							_hoops_AISSR|
							_hoops_CSCCA|
							_hoops_PISSR|
							_hoops_RPSIR);

  Release:
	_hoops_IRRPR();
}
#endif
#endif

HC_INTERFACE void HC_CDECL HC_Edit_NURBS_Surface (
	Key					key,
	int					control_point_offset,
	int					weight_offset,
	int					u_knot_offset,
	int					v_knot_offset,
	int					control_point_replace_count,
	int					weight_replace_count,
	int					u_knot_replace_count,
	int					v_knot_replace_count,
	Point const	*		control_points,
	float const *		weights,
	float const *		u_knots,
	float const *		v_knots)
{
	_hoops_PAPPR context("Edit_NURBS_Surface");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		int		count2;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		if (control_point_replace_count != 0)
			HI_Dump_Code (Sprintf_D (null, "HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", control_point_replace_count));
		else
			HI_Dump_Code ("HC_POINT *points = NULL;\n");
		if (weight_replace_count != 0)
			HI_Dump_Code (Sprintf_D (null, "float* weights = (float*) malloc(sizeof(float)*%d);\n", weight_replace_count));
		else
			HI_Dump_Code ("float *weights = NULL;\n");
		if (u_knot_replace_count != 0)
			HI_Dump_Code (Sprintf_D (null, "float* u_knots = (float*) malloc(sizeof(float)*%d);\n", u_knot_replace_count));
		else
			HI_Dump_Code ("float *u_knots = NULL;\n");
		if (v_knot_replace_count != 0)
			HI_Dump_Code (Sprintf_D (null, "float* v_knots = (float*) malloc(sizeof(float)*%d);\n", v_knot_replace_count));
		else
			HI_Dump_Code ("float *v_knots = NULL;\n");
		count2 = control_point_replace_count;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "control_points[%d].x = %f;	 ", count2, control_points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "control_points[%d].y = %f;	 ", count2, control_points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "control_points[%d].z = %f;\n", count2, control_points[count2].z));
		}
		count2 = weight_replace_count;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "weights[%d] = %f;	", count2, weights[count2]));
		}
		count2 = u_knot_replace_count;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "u_knots[%d] = %f;	", count2, u_knots[count2]));
		}
		count2 = v_knot_replace_count;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "v_knots[%d] = %f;	", count2, v_knots[count2]));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_NURBS_Surface (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", control_point_offset, weight_offset));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", u_knot_offset, v_knot_offset));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", control_point_replace_count, weight_replace_count));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", u_knot_replace_count, v_knot_replace_count));
		HI_Dump_Code ("control_points, weights, u_knots, v_knots);\n");
		HI_Dump_Code ("free (points);\n");
		HI_Dump_Code ("free (weights);\n");
		HI_Dump_Code ("free (u_knots);\n");
		HI_Dump_Code ("free (v_knots);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	_hoops_HSSSI (context, key,
			control_point_offset, weight_offset, u_knot_offset, v_knot_offset,
			control_point_replace_count, weight_replace_count, u_knot_replace_count, v_knot_replace_count,
			control_points, weights, u_knots, v_knots);
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Edit_NURBS_Surface_Points (
	Key					key,
	int					control_point_offset,
	int					control_point_replace_count,
	Point const *		control_points)
{
	_hoops_PAPPR context("Edit_NURBS_Surface_Points");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		int		count2 = control_point_replace_count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", control_point_replace_count));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", count2, control_points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", count2, control_points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n", count2, control_points[count2].z));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_NURBS_Surface_Points (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, points);\n", control_point_offset, control_point_replace_count));
		HI_Dump_Code ("free (points);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	_hoops_HSSSI (context, key, control_point_offset, 0, 0, 0,
			control_point_replace_count, 0, 0, 0,
			control_points, null, null, null);
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Edit_NURBS_Surface_Weights (
	Key					key,
	int					weight_offset,
	int					weight_replace_count,
	float const *		weights)
{
	_hoops_PAPPR context("Edit_NURBS_Surface_Weights");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		int		count2 = weight_replace_count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "float* weights = (float*) malloc(sizeof(float)*%d);\n", weight_replace_count));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "weights[%d] = %f;	", count2, weights[count2]));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_NURBS_Surface_Weights (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, weights);\n", weight_offset, weight_replace_count));
		HI_Dump_Code ("free (weights);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	_hoops_HSSSI (context, key,
			0, weight_offset, 0, 0,
			0, weight_replace_count, 0, 0,
			null, weights, null, null);

#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Edit_NURBS_Surface_Knots (
	Key					key,
	int					u_knot_offset,
	int					v_knot_offset,
	int					u_knot_replace_count,
	int					v_knot_replace_count,
	float const *		v_knots,
	float const *		u_knots)
{
	_hoops_PAPPR context("Edit_NURBS_Surface_Knots");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		int		count2;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		if (u_knot_replace_count != 0)
			HI_Dump_Code (Sprintf_D (null, "float* u_knots = (float*) malloc(sizeof(float)*%d);\n", u_knot_replace_count));
		else
			HI_Dump_Code ("float *u_knots = NULL;\n");
		if (v_knot_replace_count != 0)
			HI_Dump_Code (Sprintf_D (null, "float* v_knots = (float*) malloc(sizeof(float)*%d);\n", v_knot_replace_count));
		else
			HI_Dump_Code ("float *v_knots = NULL;\n");
		count2 = u_knot_replace_count;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "u_knots[%d] = %f;	", count2, u_knots[count2]));
		}
		count2 = v_knot_replace_count;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "v_knots[%d] = %f;	", count2, v_knots[count2]));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_NURBS_Surface_Knots (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", u_knot_offset, v_knot_offset));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, u_knots, v_knots);\n", u_knot_replace_count, v_knot_replace_count));
		HI_Dump_Code ("free (u_knots);\n");
		HI_Dump_Code ("free (v_knots);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	_hoops_HSSSI (context, key,
			0, 0, u_knot_offset, v_knot_offset,
			0, 0, u_knot_replace_count, v_knot_replace_count,
			null, null, u_knots, v_knots);
#endif
#endif
}





HC_INTERFACE void HC_CDECL HC_Set_Trim_Operation(
	int					offset,
	char const *		operation)
{
	_hoops_PAPPR context("Set_Trim_Operation");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else

/* _hoops_ASIGA _hoops_SIGP
	_hoops_CSSSI (
	);
*/
	_hoops_HCRPR					name;
	char const *			t;
	char const *			_hoops_RPPA;
	char const *			_hoops_SSRPR;
	_hoops_APPGR *			surface;
	int						i;
	UV_Trim *				trim;
	UV_Trim *				ptr;
	bool					_hoops_HPAHA;

	/* _hoops_SRS _hoops_SSS _hoops_RH _hoops_CARA _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_GHAA _hoops_RGR _hoops_RGSR _hoops_IS */
	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or an 'Open_Trim'");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
		i = offset;
		for (ptr = surface->_hoops_GPRIR; (i != 0) && (ptr != null); ptr = ptr->next) {
			i--;
		}
		if (i < 0 || ptr == null) {
			HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET, "No trim exists at the given offset for the given nurbs surface");
			return;
		}
		trim = ptr;
	}
	else if (context->open_list->_hoops_GCRIR != _hoops_ASRIR) {
		trim = (UV_Trim *)(context->open_list->info.geometry._hoops_IGRPR);
		if (trim->type != _hoops_CARIR) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open trim does not refer to a valid NURBS surface trim collection");
			return;
		}
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or an 'Open_Trim'");
		return;
	}

	/* _hoops_HA _hoops_CAHA _hoops_GGSR _hoops_RH _hoops_RGSR _hoops_SR _hoops_CHR _hoops_RRPRA */
	HI_Canonize_Chars (operation, &name);
	_hoops_RPPA = name.text;
	_hoops_SSRPR = _hoops_RPPA + name.length;
	if (_hoops_RPPA[0] == 'k')
		t = "keep";
	else
		t = "remove";
	_hoops_RPPA = name.text;
	_hoops_HPAHA = true;
	do {
		if (*_hoops_RPPA++ != *t++) {
			_hoops_HPAHA = false;
			break;
		}
	} while ((_hoops_RPPA < _hoops_SSRPR) && (*t != '\0'));
	if (!_hoops_HPAHA) {
		char _hoops_SSSSI [MAX_ERRMSG];
		HE_ERROR3 (HEC_SYNTAX, HES_PARSE_STRING, Sprintf_S (_hoops_SSSSI, "Error parsing option string '%s' -", operation), "Invalid trim operation", "");
		goto done;
	}

	if (name.text[0] == 'k')
		trim->flags |= _hoops_RSSSI;
	else
		trim->flags &= ~_hoops_RSSSI;
	done:
	_hoops_RGAIR(name);
#endif
}




HC_INTERFACE void HC_CDECL HC_Create_Trim_Collection()
{
	_hoops_PAPPR context("Create_Trim_Collection");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else

/* _hoops_SRSA _hoops_IPRPI
	_hoops_CSSSI (
	);
*/
	_hoops_APPGR *			surface;
	UV_Trim_Collection  *	_hoops_GGGGC;

	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' ");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_ASRIR) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "A trim collection may not contain another trim collection");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_HCRIR) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' ");
		return;
	}
	surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
	if (surface->type != _hoops_PRCP) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
		return;
	}
	ZALLOC (_hoops_GGGGC, UV_Trim_Collection);
	_hoops_GGGGC->type = _hoops_CARIR;
	_hoops_GGGGC->next = surface->_hoops_GPRIR;
	surface->_hoops_GPRIR = (UV_Trim *)_hoops_GGGGC;
#endif
}


HC_INTERFACE void HC_CDECL HC_Open_Trim	(int offset)
{
	_hoops_PAPPR context("Open_Trim");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else

/*
_hoops_ASIGA _hoops_IPRPI: _hoops_CSSSI
*/
	_hoops_SIRIR *_hoops_RGGGC;
	UV_Trim *node;

	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_OPEN_GEOMETRY, "Must 'Open_Geometry' first");
		return;
	}
	if (context->open_list->_hoops_GCRIR != _hoops_HCRIR) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_OPEN, "Most recent 'Open' was not an 'Open_Geometry'");
		return;
	}

	_hoops_APPGR *	surface = (_hoops_APPGR *)context->open_list->info.geometry._hoops_IGRPR;
	if (surface->type == _hoops_PRCP) {
		node = surface->_hoops_GPRIR;
		for (int i = 0; i < offset && node != null; i++) {
			node = node->next;
		}
		if (node == null || offset < 0) {
			HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET,
				Sprintf_D (null, "No trim exists at offset '%d' for the currently open NURBS surface.", offset));
		}
		if (node->type != _hoops_CARIR) {
			HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET,
				Sprintf_D (null, "Trim at offset '%d' is not a trim collection.", offset));
		}
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Can only 'Open_Trim' within an open NURBS surface");
		return;
	}

	ZALLOC (_hoops_RGGGC, _hoops_SIRIR);
	_hoops_RGGGC->type = _hoops_CIRIR;
	_hoops_RGGGC->_hoops_HIHI = 1;
	_hoops_RGGGC->owner = HOOPS_WORLD;
	_hoops_RGGGC->_hoops_GCRIR = _hoops_ASRIR;

	_hoops_RGGGC->info._hoops_PSRIR._hoops_IGRPR = surface;
	_hoops_PRRH (surface);
	_hoops_RGGGC->info._hoops_PSRIR.offset = offset;

	_hoops_IPAPP(context, _hoops_RGGGC);

#endif
}



HC_INTERFACE void HC_CDECL HC_Close_Trim ()
{
	_hoops_PAPPR context("Close_Trim");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else

/*
_hoops_ASIGA _hoops_IPRPI: _hoops_CSSSI
*/
	_hoops_SIRIR *	_hoops_AHSCA = context->open_list;
	if (_hoops_AHSCA == null || _hoops_AHSCA->_hoops_GCRIR != _hoops_ASRIR) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_OPEN, "Most recent 'Open' was not an 'Open_Trim'");
		return;
	}

	_hoops_CIGPR (context,_hoops_AHSCA);
	_hoops_HPRH (_hoops_AHSCA);
#endif
}


HC_INTERFACE void HC_CDECL HC_Delete_Trim  (
	int				offset)
{
	_hoops_PAPPR context("Delete_Trim");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "HC_Delete_Trim(%d);\n", offset));
	);

	_hoops_APPGR *surface;
	UV_Trim *node, *prev;
	UV_Trim_Collection *_hoops_RGRSA;

	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or an 'Open_Trim'");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface.");
			return;
		}
		node = surface->_hoops_GPRIR;
	}
	else if (context->open_list->_hoops_GCRIR == _hoops_ASRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info._hoops_PSRIR._hoops_IGRPR);
		node = surface->_hoops_GPRIR;
		for (int i = 0; i < offset && node != null; i++) {
			node = node->next;
		}
		_hoops_RGRSA = (UV_Trim_Collection *) node;
		if ((_hoops_RGRSA == null) || (_hoops_RGRSA->type != _hoops_CARIR)) {
			HE_ERROR (HEC_INTERNAL_ERROR, HES_MOST_RECENT_OPEN, "Currently open surface Trim_Collection is not valid");
			return;
		}
		node = _hoops_RGRSA->_hoops_GPRIR;
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' or an 'Open_Trim'");
		return;
	}

	prev = null;
	for (int i = 0; i < offset && node != null; i++) {
		prev = node;
		node = node->next;
	}
	if (node == null) {
		HE_ERROR (HEC_SURFACE, HES_INVALID_OFFSET, Sprintf_D (null, "No trim exists at offset '%d' for the currently open NURBS surface.", offset));
		return;
	}
	if (prev == null)
		surface->_hoops_GPRIR = node->next;
	else
		prev->next = node->next;

	HI_Delete_Trim (node);

	if (surface->_hoops_IPRI != null) {
		HI_Au_Revoir ((_hoops_HPAH *)surface->_hoops_IPRI);
		surface->_hoops_IPRI = null;
	}
	_hoops_SASIR (context, surface, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);

#endif
}


HC_INTERFACE void HC_CDECL HC_Trim_NURBS_Surface_By_Poly (
	int					count,
	float const *		points)
{
	_hoops_PAPPR context("Trim_NURBS_Surface_By_Poly");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
	CODE_GENERATION (
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "float points[%d];\n", count * 2));
		for (int ii = 0; ii < count; ii++) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d] = %f;  ", ii*2, points[ii*2]));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d] = %f;\n", ii*2+1, points[ii*2+1]));
		}
		HI_Dump_Code (Sprintf_D (null, "HC_Trim_NURBS_Surface_By_Poly (%d, points);\n", count));
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	_hoops_APPGR *		surface;
	UV_Trim_Poly *		_hoops_ASSSI;
	UV_Trim *node, *root, **_hoops_AGGGC;
	int	end;

	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry'");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
		root = surface->_hoops_GPRIR;
		_hoops_AGGGC = &(surface->_hoops_GPRIR);
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
	}
	else if (context->open_list->_hoops_GCRIR == _hoops_ASRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info._hoops_PSRIR._hoops_IGRPR);
		end = context->open_list->info._hoops_PSRIR.offset;
		node = surface->_hoops_GPRIR;
		for (int i = 0; i < end && node != null; i++) {
			node = node->next;
		}
		if ((node == null) || (node->type != _hoops_CARIR)) {
			HE_ERROR (HEC_INTERNAL_ERROR, HES_MOST_RECENT_OPEN, "Currently open surface Trim_Collection is not valid");
			return;
		}
		root = ((UV_Trim_Collection const *)node)->_hoops_GPRIR;
		_hoops_AGGGC = &((UV_Trim_Collection *)node)->_hoops_GPRIR;
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry' ");
		return;
	}
	ZALLOC (_hoops_ASSSI, UV_Trim_Poly);
	_hoops_ASSSI->type = _hoops_PARIR;
	_hoops_ASSSI->next = root;
	_hoops_APRGA(points, count, UV_Point , _hoops_ASSSI->points);
	_hoops_ASSSI->count = count;
	*_hoops_AGGGC = (UV_Trim *)_hoops_ASSSI;
	if (surface->_hoops_IPRI != null) {
		HI_Au_Revoir ((_hoops_HPAH *)surface->_hoops_IPRI);
		surface->_hoops_IPRI = null;
	}
	_hoops_SASIR (context, surface, _hoops_AISSR|_hoops_CSCCA|_hoops_RPSIR);
#endif
}

HC_INTERFACE void HC_CDECL HC_Trim_NURBS_Surface_By_Curve (
	int					degree,
	int					control_point_count,
	float const *		control_points,
	float const *		weights,
	float const *		knots,
	double				start_u,
	double				end_u)
{
	_hoops_PAPPR context("Trim_NURBS_Surface_By_Curve");

#ifdef _hoops_GSPIR
	_hoops_IRPPR ("NURBS Surface");
#else
	CODE_GENERATION (
		int	   knot_count = control_point_count + degree + 1;
		float	_hoops_PGGGC;
		float	_hoops_HGGGC;

		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "float control_points[%d];\n", control_point_count*2));
		if (weights != null)
			HI_Dump_Code (Sprintf_D (null, "float weights[%d];\n", control_point_count));
		else
			HI_Dump_Code ("float *weights = NULL;\n");
		if (knots != null)
			HI_Dump_Code (Sprintf_D (null, "float knots[%d];\n", knot_count));
		else
			HI_Dump_Code ("float *knots = NULL;\n");

		for (int ii = 0; ii < control_point_count; ii++) {
			HI_Dump_Code (_hoops_CHCHR (null, "control_points[%d] = %f;  ", ii*2, control_points[ii*2]));
			HI_Dump_Code (_hoops_CHCHR (null, "control_points[%d] = %f;\n", ii*2+1, control_points[ii*2+1]));
		}
		if (weights != null)
			for (int ii = 0; ii < control_point_count; ii++)
				HI_Dump_Code (_hoops_CHCHR (null, "weights[%d] = %f; \n", ii, weights[ii]));
		if (knots != null)
			for (int ii = 0; ii < knot_count; ii++)
				HI_Dump_Code (_hoops_CHCHR (null, "knots[%d] = %f; \n", ii, knots[ii]));
		HI_Dump_Code (Sprintf_DD (null, "HC_Trim_NURBS_Surface_By_Curve (%d, %d, control_points, weights, knots", degree, control_point_count));
		_hoops_PGGGC=start_u;
		_hoops_HGGGC=end_u;
		HI_Dump_Code (Sprintf_FF (null, ", %f, %f);\n", _hoops_PGGGC, _hoops_HGGGC));

		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	_hoops_APPGR *surface;
	UV_Trim_Curve  *_hoops_PSSSI;
	UV_Trim *node, *root, **_hoops_AGGGC;
	int end;

	if (context->open_list == null) {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry'");
		return;
	}
	if (context->open_list->_hoops_GCRIR == _hoops_HCRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info.geometry._hoops_IGRPR);
		root = surface->_hoops_GPRIR;
		_hoops_AGGGC = &(surface->_hoops_GPRIR);
		if (surface->type != _hoops_PRCP) {
			HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "Open geometry does not refer to a valid NURBS surface");
			return;
		}
	}
	else if (context->open_list->_hoops_GCRIR == _hoops_ASRIR) {
		surface = (_hoops_APPGR *)(context->open_list->info._hoops_PSRIR._hoops_IGRPR);
		end = context->open_list->info._hoops_PSRIR.offset;
		node = surface->_hoops_GPRIR;
		for (int i = 0; i < end && node != null; i++) {
			node = node->next;
		}
		if ((node == null) || (node->type != _hoops_CARIR)) {
			HE_ERROR (HEC_INTERNAL_ERROR, HES_MOST_RECENT_OPEN, "Currently open surface Trim_Collection is not valid");
			return;
		}
		root = ((UV_Trim_Collection const *)node)->_hoops_GPRIR;
		_hoops_AGGGC = &((UV_Trim_Collection *)node)->_hoops_GPRIR;
	}
	else {
		HE_ERROR (HEC_SURFACE, HES_MOST_RECENT_OPEN, "The most recent open was not an 'Open_Geometry'");
		return;
	}
	ZALLOC (_hoops_PSSSI, UV_Trim_Curve);
	_hoops_PSSSI->type = _hoops_IARIR;
	_hoops_PSSSI->next = root;
	_hoops_PSSSI->degree = degree;
	_hoops_PSSSI->control_point_count = control_point_count;
	_hoops_APRGA(control_points, control_point_count, UV_Point , _hoops_PSSSI->control_points);
	if (weights != null) {
		_hoops_APRGA(weights, control_point_count, float, _hoops_PSSSI->weights);
	}
	else
		_hoops_PSSSI->weights = null;
	if (knots != null) {
		int knot_count = degree + control_point_count + 1;
		_hoops_APRGA(knots, knot_count, float, _hoops_PSSSI->knots);
	}
	else
		_hoops_PSSSI->knots = null;
	*_hoops_AGGGC = (UV_Trim *)_hoops_PSSSI;
	if (surface->_hoops_IPRI != null) {
		HI_Au_Revoir ((_hoops_HPAH *)surface->_hoops_IPRI);
		surface->_hoops_IPRI = null;
	}
	_hoops_SASIR (context, surface, _hoops_AISSR|
								 _hoops_CSCCA|
								 _hoops_RPSIR);
	UNREFERENCED(start_u);
	UNREFERENCED(end_u);
#endif
}



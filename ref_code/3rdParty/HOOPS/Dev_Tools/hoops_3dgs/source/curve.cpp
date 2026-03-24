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
 * $Id: obf_tmp.txt 1.72.2.1 2010-11-15 19:14:17 chad Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_RGHSA {
	int				degree;
	int				control_point_count;
	Point const *	control_points; 
	float const *	weights;
	float const *	knots;
	float			start_u;
	float			end_u;

	_hoops_PIRGR *	curve;
	int				_hoops_IGSSR;
};


/* _hoops_RH _hoops_AGHSA _hoops_SGCR _hoops_IH _hoops_PGAP _hoops_SR _hoops_SGH _hoops_RGSHA _hoops_RSSA _hoops_IS _hoops_CAHA _hoops_IASC.
 * _hoops_CAPP _hoops_SGS, _hoops_SR _hoops_CAHP _hoops_RH _hoops_ISII _hoops_PPR _hoops_CAHP _hoops_HII _hoops_SGS. */
#define _hoops_PGHSA (0.001f)

local void _hoops_HGHSA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_RGHSA *		data)
{
	_hoops_PIRGR *		curve;
	ZALLOC (curve, _hoops_PIRGR);

	curve->type = _hoops_CHIP;
	curve->_hoops_CPGPR = _hoops_PHSSR;

	/* _hoops_IPS _hoops_RH _hoops_PICAA _hoops_IAGH */
	curve->degree = data->degree;
	curve->control_point_count = data->control_point_count;
	curve->start_u = data->start_u;
	curve->end_u = data->end_u;

	bool				_hoops_IGHSA = true; /* _hoops_HPCAR 2d _hoops_CCGR _hoops_SR _hoops_SSS _hoops_IAII */

	if (data->control_point_count != 0) {
		/* _hoops_CCPP _hoops_PPR _hoops_HSPC _hoops_RH _hoops_HAHH _hoops_SIRGR _hoops_IH _hoops_RH _hoops_AGIS */
		ALLOC_ARRAY (curve->control_points, data->control_point_count, Point);
		for (int i = 0; i < data->control_point_count; i++) {
			curve->control_points[i].x = data->control_points[i].x;
			curve->control_points[i].y = data->control_points[i].y;
			curve->control_points[i].z = data->control_points[i].z;
			if (data->control_points[i].z != 0.0f) _hoops_IGHSA = false;
		}
	}
	else
		curve->control_points = null;
	if (data->knots != null) {
		ALLOC_ARRAY (curve->knots, data->control_point_count + data->degree + 1, float);
		for (int i = 0; i < data->control_point_count + data->degree + 1; i++)
			curve->knots[i] = data->knots[i];
	}
	else
		curve->knots = null;
	if (data->weights != null) {
		ALLOC_ARRAY (curve->weights, data->control_point_count, float);
		for (int i = 0; i < data->control_point_count; i++) {
			curve->weights[i] = data->weights[i];
			if (curve->weights[i] < _hoops_PGHSA)
				curve->_hoops_RRHH |= _hoops_CHIAA;
		}
	}
	else {
		curve->weights = null;
	}
	curve->polyline.points = null;
	curve->polyline.allocated = 0;
	curve->polyline.count = 0;

	HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) curve,
		_hoops_IGHSA, curve->control_point_count > 0 ? 
			_hoops_IHSSR : _hoops_CCHPA);

	data->curve = curve;
	++data->_hoops_IGSSR;

}


GLOBAL_FUNCTION Key HI_Insert_NURBS_Curve (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	int						degree,
	int						control_point_count,
	Point const *			control_points, 
	float const *			weights,
	float const *			knots,
	float					start_u,
	float					end_u) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_RGHSA			data;
	ZERO_STRUCT(&data, _hoops_RGHSA);
	data.degree = degree;
	data.control_point_count = control_point_count;
	data.control_points = control_points;
	data.weights = weights;
	data.knots = knots;
	data.start_u = start_u;
	data.end_u = end_u;

	_hoops_HGHSA (_hoops_RIGC, owner, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.curve);

	return _hoops_CHSSR;
} 



HC_INTERFACE Key HC_CDECL HC_Insert_NURBS_Curve (
	int						degree,
	int						control_point_count,
	Point const *			control_points, 
	float const *			weights,
	float const *			knots,
	double					start_u,
	double					end_u) 
{
	_hoops_PAPPR context("KInsert_NURBS_Curve");

#ifdef _hoops_CCPIR
	_hoops_IRPPR ("NURBS Curve");
	return _hoops_SHSSR;
#else

	if (control_point_count < 0) {
		HE_ERROR (HEC_CURVE, HES_INVALID_COUNT, "Negative number of points given to Insert_NURBS_Curve");
		return _hoops_SHSSR;
	}
	if (degree > 31) {
		HE_ERROR (HEC_CURVE, HES_BAD_VALUE, "Insert_NURBS given degree greater than or equal to 32");
		return _hoops_SHSSR;
	}
	if (end_u < start_u) {
		HE_ERROR (HEC_CURVE, HES_BAD_VALUE, "Insert_NURBS given start parameter greater than end parameter");
		return _hoops_SHSSR;
	}
	if (start_u < 0) {
		HE_ERROR (HEC_CURVE, HES_BAD_VALUE, "Insert_NURBS given start parameter less than 0 (should be between 0 and 1, inclusive)");
		return _hoops_SHSSR;
	}
	if (end_u > 1) {
		HE_ERROR (HEC_CURVE, HES_BAD_VALUE, "Insert_NURBS given end parameter greater than 1 (should be between 0 and 1, inclusive)");
		return _hoops_SHSSR;
	}
	if (knots != null) {
		int _hoops_CGHSA = 0;
		for (int i = 1; i < control_point_count + degree + 1; i++) {
			if (knots[i] < knots[i-1]) {
				HE_ERROR (HEC_CURVE, HES_BAD_VALUE, "knot values in Insert_NURBS_Curve must be nondecreasing");
				return _hoops_SHSSR;
			}
			else if (knots[i] == knots[i-1])
				_hoops_CGHSA++;
			else 
				_hoops_CGHSA = 1;

			if (_hoops_CGHSA > degree + 1) {
				HE_ERROR (HEC_CURVE, HES_BAD_VALUE, "knot multiplicity greater than the order is not supported in Insert_NURBS_Curve");
				return _hoops_SHSSR;
			}	
		}				
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_NURBS_Curve (context, target, 
			degree, control_point_count, control_points, weights, knots, (float)start_u, (float)end_u); 
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		int	   knot_count = control_point_count + degree + 1;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT* cp = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", control_point_count));
		if (weights != null)
			HI_Dump_Code (Sprintf_D (null, "float* w = (float*) malloc(sizeof(float)*%d);\n", control_point_count));
		if (knots != null)
			HI_Dump_Code (Sprintf_D (null, "float* k = (float*) malloc(sizeof(float)*%d);\n", knot_count));
		for (int i = 0; i < control_point_count; i++) {
			HI_Dump_Code (_hoops_CHCHR (null, "cp[%d].x = %.6ff;	 ", i, control_points[i].x));
			HI_Dump_Code (_hoops_CHCHR (null, "cp[%d].y = %.6ff;	 ", i, control_points[i].y));
			HI_Dump_Code (_hoops_CHCHR (null, "cp[%d].z = %.6ff;\n", i, control_points[i].z));
		}
		if (weights != null)
			for (int i = 0; i < control_point_count; i++)
				HI_Dump_Code (_hoops_CHCHR (null, "w[%d] = %.6ff; \n", i, weights[i]));
		if (knots != null)
			for (int i = 0; i < knot_count; i++)
				HI_Dump_Code (_hoops_CHCHR (null, "k[%d] = %.6ff; \n", i, knots[i]));
		HI_Dump_Code ("DEFINE (");
		HI_Dump_Code (Sprintf_DD (null, "HC_Insert_NURBS_Curve (%d, %d, ", degree, control_point_count));
		HI_Dump_Code (Sprintf_SS (null, "cp, %s, %s, ", (weights == null ? "0" : "w"),(knots == null ? "0" : "k")));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F), ", start_u, end_u));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (cp);\n");
		if (weights != null)
			HI_Dump_Code ("free (w);\n");
		if (knots != null)
			HI_Dump_Code ("free (k);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CHSSR;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_NURBS_Curve (
	Key				key,
	int *			degree,
	int *			cp_count,
	Point *			control_points,
	float *			weights,
	float *			knots,
	float *			start_u,
	float *			end_u) 
{
	_hoops_PAPPR context("Show_NURBS_Curve");

#ifdef _hoops_CCPIR
	_hoops_IRPPR ("NURBS Curve");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_NURBS_Curve () */\n");
	);

	_hoops_CSPPR();

	_hoops_PIRGR * curve = (_hoops_PIRGR *)_hoops_RCSSR (context, key);

	if (curve == null ||
		curve->type != _hoops_CHIP ||
		BIT (curve->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Provided key does not refer to a valid nurbs curve");
	}
	else {
		int knot_count = curve->control_point_count + curve->degree + 1;
		if (degree != null)
			*degree = curve->degree;
		if (cp_count != null)
			*cp_count = curve->control_point_count;
		if (control_points != null)
			_hoops_AIGA (curve->control_points, curve->control_point_count, Point, control_points);
		if (knots != null)
			if (curve->knots != null) {
				_hoops_AIGA (curve->knots, knot_count, float, knots);
			}
			else {
				for (int i = 0; i < knot_count; i++)
					knots[i] = (float)i; /* _hoops_RH _hoops_SHIR: _hoops_GHRHR _hoops_SGHSA */
			}
		if (weights != null)
			if (curve->weights != null) {
				_hoops_AIGA (curve->weights, curve->control_point_count, float, weights);
			}
			else {
				for (int i = 0; i < curve->control_point_count; i++)
					weights[i] = 1.0f;	 /* _hoops_RH _hoops_SHIR: _hoops_GHRHR _hoops_HHRP */
			}

		if (start_u != null)
			*start_u = curve->start_u;
		if (end_u != null)
			*end_u = curve->end_u;
	}

	_hoops_IRRPR();
#endif
#endif
} 



HC_INTERFACE void HC_CDECL HC_Show_NURBS_Curve_Size (
	Key				key,
	int *			degree,
	int *			cp_count,
	int *			weight_count,
	int *			knot_count) 
{
	_hoops_PAPPR context("Show_NURBS_Curve_Size");

#ifdef _hoops_CCPIR
	_hoops_IRPPR ("NURBS Curve");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_NURBS_Curve_Size () */\n");
	);

	_hoops_CSPPR();

	_hoops_PIRGR *	curve = (_hoops_PIRGR *)_hoops_RCSSR (context, key);

	if (curve == null ||
		curve->type != _hoops_CHIP ||
		BIT (curve->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Provided key does not refer to a valid nurbs curve");
	}
	else {
		if (degree != null)
			*degree = curve->degree;
		if (cp_count != null)
			*cp_count = curve->control_point_count;
		if (weight_count != null) {
			if (curve->weights != null) 
				*weight_count = curve->control_point_count;
			else
				*weight_count = 0;
		}
		if (knot_count != null) {
			if (curve->knots != null) 
				*knot_count = curve->control_point_count + curve->degree + 1;
			else
				*knot_count = 0;
		}
	}

	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_Edit_NURBS_Curve (
	Key					key,
	int					control_point_offset,
	int					knot_offset,
	int					control_point_replace_count,
	int					knot_replace_count,
	Point const *		control_points,
	float const *		weights,
	float const *		knots) 
{
	_hoops_PAPPR context("Edit_NURBS_Curve");

#ifdef _hoops_CCPIR
	_hoops_IRPPR ("NURBS Curve");
#else
#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		if (control_points != null)
			HI_Dump_Code (Sprintf_D (null, "HC_POINT * cp = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", control_point_replace_count));
		if (weights != null)
			HI_Dump_Code (Sprintf_D (null, "float * w = (float*) malloc(sizeof(float)*%d);\n", control_point_replace_count));
		if (knots != null)
			HI_Dump_Code (Sprintf_D (null, "float * k = (float*) malloc(sizeof(float)*%d);\n", knot_replace_count));

		for (int i = 0; i < control_point_replace_count; i++) {
			HI_Dump_Code (_hoops_CHCHR (null, "cp[%d].x = %.6ff;	 ", i, control_points[i].x));
			HI_Dump_Code (_hoops_CHCHR (null, "cp[%d].y = %.6ff;	 ", i, control_points[i].y));
			HI_Dump_Code (_hoops_CHCHR (null, "cp[%d].z = %.6ff;\n", i, control_points[i].z));
		}
		if (weights != null)
			for (int i = 0; i < control_point_replace_count; i++)
				HI_Dump_Code (_hoops_CHCHR (null, "w[%d] = %.6ff; \n", i, weights[i]));
		if (knots != null)
			for (int i = 0; i < knot_replace_count; i++)
				HI_Dump_Code (_hoops_CHCHR (null, "k[%d] = %.6ff; \n", i, knots[i]));

		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_NURBS_Curve (LOOKUP(%ld), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", control_point_offset, knot_offset));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", control_point_replace_count, knot_replace_count));
		HI_Dump_Code (Sprintf_S	 (null, "%s, ", control_points == null ? "NULL" : "cp"));
		HI_Dump_Code (Sprintf_S	 (null, "%s, ", weights == null ? "NULL" : "w"));
		HI_Dump_Code (Sprintf_S	 (null, "%s);\n", knots == null ?  "NULL" : "k"));

		if (control_points != null)
			HI_Dump_Code ("free (cp);\n");
		if (weights != null)
			HI_Dump_Code ("free (w);\n");
		if (knots != null)
			HI_Dump_Code ("free (k);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);


	_hoops_CRCP	alter *	owner;
	int				knot_count;

	_hoops_RPPPR();

	_hoops_PIRGR	alter *	curve = (_hoops_PIRGR *)_hoops_RCSSR (context, key);
	/* _hoops_HSPP _hoops_CCA _hoops_HHH _hoops_RIHH _hoops_IPAC */
	if (curve == null || curve->type != _hoops_CHIP ||
		BIT (curve->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CURVE, HES_INVALID_KEY,
				"Key does not refer to a valid nurbs curve");
		goto Release;
	}
	if ((control_point_offset < 0) || 
		(control_point_offset + control_point_replace_count > curve->control_point_count)) {
		HE_ERROR (HEC_CURVE, HES_INVALID_OFFSET,
				Sprintf_DD (null,"Control point offset '%d' not valid (curve currently has %d vertices)",
						control_point_offset + control_point_replace_count,
						curve->control_point_count));
		goto Release;
	}
	knot_count = curve->control_point_count + curve->degree + 1;
	if (knot_offset < 0 || knot_offset + knot_replace_count > knot_count) {
		HE_ERROR (HEC_CURVE, HES_INVALID_OFFSET,
				Sprintf_DD (null,"Knot offset '%d' not valid (curve currently has %d knots)",
						knot_offset + knot_replace_count,
						knot_count));
		goto Release;
	}

	/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GRHSA _hoops_SGCR _hoops_HSH _hoops_SGS _hoops_AAPR _hoops_RRHSA _hoops_IRAP, _hoops_CCPP _hoops_PPR _hoops_HSPC */
	if (curve->weights == null && weights != null) {
		ALLOC_ARRAY (curve->weights, curve->control_point_count, float); 
		for (int i = 0; i < curve->control_point_count; i++)
			curve->weights[i] = 1.0f;
	}
	if (curve->knots == null && knots != null) {
		ALLOC_ARRAY (curve->knots, knot_count, float); 
		for (int i = 0; i < knot_count; i++)
			curve->knots[i] = (float)i;
	}

	/* _hoops_GCSH, _hoops_SR _hoops_PAH _hoops_AA _hoops_RH _hoops_IPHR! */
	if (control_points != null)
		_hoops_AIGA (control_points, control_point_replace_count, Point, &(curve->control_points[control_point_offset]));
	if (weights != null)
		_hoops_AIGA (weights, control_point_replace_count, float, &(curve->weights[control_point_offset]));
	if (knots != null)
		_hoops_AIGA (knots, knot_replace_count, float, &(curve->knots[knot_offset]));

	/* _hoops_RPP _hoops_SR _hoops_ARHSA _hoops_RH _hoops_HHRP _hoops_PAR _hoops_RGSHA _hoops_RSSA, _hoops_SR _hoops_RRP _hoops_IS _hoops_PRHSA _hoops_RH _hoops_ISII */
	if (curve->polyline.points != null) {
		FREE_ARRAY	(curve->polyline.points, curve->polyline.allocated, Point);	
		curve->polyline.points = null;
		curve->polyline.count = 0;	
		curve->polyline.allocated = 0;	
	}
	curve->_hoops_CPGPR |= _hoops_HHSSR;
	_hoops_SASIR (context, curve->owner, _hoops_RAGGA|
										_hoops_PISSR|
										_hoops_RPSIR);

	curve->_hoops_CPGPR  = _hoops_HHSSR;
	owner = curve->owner;

	if (owner)
		HI_Antiquate_Bounding (owner, true);

	if (owner != null) {
		_hoops_SASIR (context, owner, _hoops_RAGGA|_hoops_PISSR|_hoops_RPSIR);
		HI_Invalidate_Segment_Display_Lists(context, owner, _hoops_CHIP, curve, 0);
	}

  Release:
	_hoops_IRRPR();
#endif
#endif
} 



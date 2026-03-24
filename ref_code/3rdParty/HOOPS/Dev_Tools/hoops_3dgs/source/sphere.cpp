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
 * $Id: obf_tmp.txt 1.40 2010-10-06 19:16:43 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

struct _hoops_AAIHS {
	/* _hoops_CHIA */
	Point const *		center;
	Vector const *		axis; 
	Vector const *		ortho;	   
	float				radius;

	/* _hoops_PHPHA */
	Vector				_hoops_CSPIR[3];	
	bool				_hoops_PAIHS;
	Sphere *			sphere;
	bool				valid;
	int					_hoops_IGSSR;
};


local void _hoops_HAIHS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_AAIHS *		data) 
{

	if (!data->valid) {

		/* _hoops_RPP _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_IRSS _hoops_HRGR _hoops_CHIA _hoops_PPR _hoops_SCH _hoops_HRGR _hoops_HAR _hoops_SASPR _hoops_IS _hoops_RH _hoops_SHIR _hoops_PIRA */
		data->_hoops_PAIHS = (data->axis && *data->axis != _hoops_IRGA::_hoops_RCPCR) ||
							 (data->ortho && *data->ortho != _hoops_IRGA::X_Axis);
		if (data->_hoops_PAIHS) {
			if (!data->axis)
				data->axis = &_hoops_IRGA::_hoops_RCPCR;
			if (!data->ortho)
				data->ortho = &_hoops_IRGA::X_Axis;
			data->_hoops_CSPIR[2] = data->ortho->_hoops_SAIAR(*data->axis);
			data->_hoops_CSPIR[0] = data->axis->_hoops_SAIAR(data->_hoops_CSPIR[2]);
			float length = data->axis->length();
			data->_hoops_CSPIR[1].x = data->axis->x * data->radius / length;
			data->_hoops_CSPIR[1].y = data->axis->y * data->radius / length;
			data->_hoops_CSPIR[1].z = data->axis->z * data->radius / length;
			length = data->_hoops_CSPIR[0].length();
			data->_hoops_CSPIR[0].x *= data->radius / length;
			data->_hoops_CSPIR[0].y *= data->radius / length;
			data->_hoops_CSPIR[0].z *= data->radius / length;
			length = data->_hoops_CSPIR[2].length();
			data->_hoops_CSPIR[2].x *= data->radius / length;
			data->_hoops_CSPIR[2].y *= data->radius / length;
			data->_hoops_CSPIR[2].z *= data->radius / length;
		}
		data->valid = true;
	}

	Sphere *	sphere;
	if (owner != null) {
		ZALLOC (sphere, Sphere);
		sphere->type = _hoops_HSIP;
		sphere->_hoops_CPGPR = _hoops_PHSSR;
	}
	else {
		sphere = data->sphere;
		sphere->_hoops_CPGPR = _hoops_HHSSR;
	}

	sphere->data.center.x = data->center->x;
	sphere->data.center.y = data->center->y;
	sphere->data.center.z = data->center->z;
	sphere->data.radius = data->radius;
	if (data->_hoops_PAIHS) {
		if (sphere->_hoops_CSPIR == null)
			ALLOC_ARRAY(sphere->_hoops_CSPIR, 3, Vector);
		_hoops_AIGA(&data->_hoops_CSPIR[0], 3, Vector, &sphere->_hoops_CSPIR[0]);
	}
	else if (sphere->_hoops_CSPIR != null) {
		FREE_ARRAY(sphere->_hoops_CSPIR, 3, Vector);
		sphere->_hoops_CSPIR = null;
	}

	if (owner != null) {
		HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) sphere, false,
							_hoops_IHSSR|_hoops_SIGPR);

		data->sphere = sphere;
		++data->_hoops_IGSSR;
	}
}



GLOBAL_FUNCTION Key HI_Insert_Sphere (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			center,
	float					radius,
	Vector const *			axis,
	Vector const *			ortho) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_AAIHS data;
	ZERO_STRUCT(&data, _hoops_AAIHS);
	data.center = center;
	data.axis = axis;
	data.ortho = ortho;
	data.radius = radius;

	_hoops_HAIHS  (_hoops_RIGC, item, &data);

	Key _hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.sphere);

	return _hoops_CHSSR;
}




HC_INTERFACE Key HC_CDECL HC_Insert_Sphere (
	Point const *		center,
	double				radius,
	Point const *		axis,
	Point const *		ortho) 
{
	_hoops_PAPPR context("Insert_Sphere");

	if (!center) {
		HE_ERROR (HEC_SPHERE, HES_INVALID_INPUT, "Center point must be provided.");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Sphere (context, target, center, (float)radius, (Vector const *)axis, (Vector const *)ortho);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT center, axis, ortho;\n");
		HI_Dump_Code ("float radius;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "center.x = %f;	 center.y = %f;	 ", center->x, center->y));
		HI_Dump_Code (Sprintf_F (null, "center.z = %f;\n", center->z));
		HI_Dump_Code (Sprintf_F (null, "radius = %f;\n", radius));
		if (axis) {
			HI_Dump_Code (Sprintf_FF (null, "axis.x = %f;  axis.y = %f;	 ", axis->x, axis->y));
			HI_Dump_Code (Sprintf_F (null, "axis.z = %f;\n", axis->z));
		}
		else
			HI_Dump_Code ("axis.x = 0;	axis.y = 1; axis.z = 0;\n");
		if (ortho) {
			HI_Dump_Code (Sprintf_FF (null, "ortho.x = %f;	ortho.y = %f;  ", ortho->x, ortho->y));
			HI_Dump_Code (Sprintf_F (null, "ortho.z = %f;\n", ortho->z));
		}
		else
			HI_Dump_Code ("ortho.x = 1;	 ortho.y = 0; ortho.z = 0;\n");
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Insert_Sphere (&center, radius, &axis, &ortho), %D);}\n",_hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}




HC_INTERFACE void HC_CDECL HC_Edit_Sphere (
	Key					key,
	Point const *		center,
	double				_hoops_SISSR,
	Point const *		_hoops_GGRIH,
	Point const *		_hoops_RGRIH) 
{
	_hoops_PAPPR context("Edit_Sphere");

	Vector const *	axis = (Vector const *)_hoops_GGRIH;
	Vector const *	ortho = (Vector const *)_hoops_RGRIH;
	float			radius = (float)_hoops_SISSR;

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT center, axis, ortho;\n");
		HI_Dump_Code ("float radius;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "center.x = %f;	 center.y = %f;	 ",center->x, center->y));
		HI_Dump_Code (Sprintf_F (null, "center.z = %f;\n", center->z));
		HI_Dump_Code (Sprintf_F (null, "radius = %f;\n", radius));
		if (axis) {
			HI_Dump_Code (Sprintf_FF (null, "axis.x = %f;  axis.y = %f;	 ", axis->x, axis->y));
			HI_Dump_Code (Sprintf_F (null, "axis.z = %f;\n", axis->z));
		}
		else
			HI_Dump_Code ("axis.x = 0;	axis.y = 0; axis.z = 1;\n");
		if (ortho) {
			HI_Dump_Code (Sprintf_FF (null, "ortho.x = %f;	ortho.y = %f;  ", ortho->x, ortho->y));
			HI_Dump_Code (Sprintf_F (null, "ortho.z = %f;\n", ortho->z));
		}
		else
			HI_Dump_Code ("ortho.x = 0;	 ortho.y = 0; ortho.z = 1;\n");
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Sphere (LOOKUP (%D), ", key));
		HI_Dump_Code ("&center, radius, &axis, &ortho);}\n");
		--HOOPS_WORLD->_hoops_ISPPR;
	);


	_hoops_RPPPR();
	Sphere *	s = (Sphere *)_hoops_RCSSR (context, key);
	if (s == null || s->type != _hoops_HSIP ||
		BIT (s->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid sphere");
	}
	else {

		_hoops_CRCP *		owner;

		_hoops_AAIHS data;

		ZERO_STRUCT(&data, _hoops_AAIHS);
		data.center = center;
		data.radius = radius;
		data.axis = axis;
		data.ortho = ortho;
		data.sphere = s;
		_hoops_HAIHS  (context, null, &data);

		s->_hoops_CPGPR = _hoops_HHSSR;
		owner = s->owner;
		if (owner != null) {
			_hoops_SASIR (context, owner, 
				_hoops_AISSR |
				_hoops_PISSR |
				_hoops_CSCCA |
				_hoops_RAGGA);
		}

		if (owner)
			HI_Antiquate_Bounding (owner, true);
	}

	_hoops_IRRPR();
}


HC_INTERFACE void HC_CDECL HC_Show_Sphere (
	Key			key,
	Point *		center,
	float *		radius,
	Point *		axis,
	Point *		ortho) 
{
	_hoops_PAPPR context("Show_Sphere");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Sphere() */\n");
	);

	_hoops_CSPPR();

	Sphere const *	sphere = (Sphere const *)_hoops_RCSSR (context, key);

	if (sphere == null ||
		sphere->type != _hoops_HSIP ||
		BIT (sphere->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SPHERE, HES_INVALID_KEY, "Provided key does not refer to a valid sphere");
	}
	if (center != null) {
		center->x = sphere->data.center.x;
		center->y = sphere->data.center.y;
		center->z = sphere->data.center.z;
	}

	if (radius != null)
		*radius = sphere->data.radius;

	if (axis != null) {
		if (sphere->_hoops_CSPIR) {
			axis->x = sphere->_hoops_CSPIR[1].x;
			axis->y = sphere->_hoops_CSPIR[1].y;
			axis->z = sphere->_hoops_CSPIR[1].z;
		}
		else {
			axis->x = 0;
			axis->y = 1;
			axis->z = 0;
		}
	}

	if (ortho != null) {
		if (sphere->_hoops_CSPIR) {
			ortho->x = sphere->_hoops_CSPIR[0].x;
			ortho->y = sphere->_hoops_CSPIR[0].y;
			ortho->z = sphere->_hoops_CSPIR[0].z;
		}
		else {
			ortho->x = 1;
			ortho->y = 0;
			ortho->z = 0;
		}
	}

	_hoops_IRRPR();
#endif
}








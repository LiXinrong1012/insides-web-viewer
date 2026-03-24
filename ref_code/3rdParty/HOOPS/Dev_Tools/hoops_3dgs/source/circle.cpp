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
 * $Id: obf_tmp.txt 1.119 2010-11-16 01:19:09 nathan Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hd_proto.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


#define _hoops_CSCSR		1e-4

struct _hoops_SSCSR {
	Point const		*start,
					*_hoops_GGSSR,
					*end;
	/* _hoops_ARGPR _hoops_RGAR _hoops_IH "_hoops_RGSSR" _hoops_AGIR */
	Vector const	*normal;

	Point			center;
	float			radius;
	_hoops_ARPA			plane;
	Vector			_hoops_GGHI, _hoops_RGHI;

	bool			_hoops_AGSSR;
	bool			_hoops_PGSSR;
	bool			valid;

	_hoops_PHPIR *		_hoops_HGSSR;
	int				_hoops_IGSSR;
};



/*
   _hoops_RCPA _hoops_SICR _hoops_RH _hoops_HRSP _hoops_PPSR _hoops_SCCI _hoops_IS _hoops_IRS _hoops_RHCH, _hoops_PSAA
   _hoops_PPR _hoops_IPPA _hoops_CGSSR _hoops_SCCI, _hoops_CSGA _hoops_RH _hoops_SGSSR _hoops_IIGR
   _hoops_HRSP _hoops_GHC _hoops_GRSSR _hoops_CAPP _hoops_IS _hoops_CGIC _hoops_RH _hoops_RHCH _hoops_IIGR _hoops_RH _hoops_PRHC.
   _hoops_AHGHR _hoops_RH _hoops_RHCH, _hoops_CSGA _hoops_RH _hoops_GIRA _hoops_GAPA _hoops_GII _hoops_PPSR _hoops_PPR _hoops_RH
   _hoops_RHCH _hoops_IS _hoops_CGIC _hoops_RH _hoops_PSAA. _hoops_IPCP _hoops_SRS _hoops_IPPA _hoops_HRGR _hoops_RH _hoops_IPPA
   _hoops_RHIR _hoops_RH _hoops_RRSSR _hoops_IIGR _hoops_RH _hoops_CAGH _hoops_IICHR _hoops_RH _hoops_SRS _hoops_PSAI _hoops_IIGR
   _hoops_RSSA _hoops_ARSSR _hoops_RH _hoops_PRHC _hoops_PPR _hoops_AARGR _hoops_IS _hoops_SCH. _hoops_IPCP _hoops_GIAP
   _hoops_PPSR _hoops_HRGR _hoops_PRSSR _hoops_PAPR _hoops_IH _hoops_RH _hoops_GIAP _hoops_PSAI _hoops_IIGR _hoops_RH _hoops_ARSSR
   _hoops_RSSA. _hoops_IPCP _hoops_HRSSR _hoops_IPPA _hoops_HRGR _hoops_RH _hoops_SPR _hoops_SGS _hoops_HCR _hoops_HRSP _hoops_RSSA _hoops_PRCS _hoops_GGR.
*/



GLOBAL_FUNCTION bool HI_Compute_Three_Point_Circle (
	Point const &		start,
	Point const &		_hoops_GGSSR,
	Point const &		end,
	Point alter *		center,
	float alter *		radius,
	_hoops_ARPA alter *		plane,
	Vector alter *		_hoops_GGHI,
	Vector alter *		_hoops_RGHI) {
	Point				_hoops_IRSSR,
						_hoops_CRSSR;
	Vector				vector1,
						vector2;
	_hoops_ARPA				_hoops_SRSSR,
						_hoops_GASSR;
	_hoops_ARPA				*one = plane,
						*_hoops_RASSR = &_hoops_SRSSR,
						*_hoops_AASSR = &_hoops_GASSR;
	_hoops_ARPA				_hoops_PASSR;
	float				_hoops_HASSR, _hoops_IASSR, _hoops_CASSR, dc, _hoops_SASSR, _hoops_GPSSR;
	float				length;
	float				_hoops_RPSSR;

	if (plane == null)
		one = &_hoops_PASSR;

	/* _hoops_CSGA _hoops_APSSR _hoops_IIGR _hoops_III _hoops_SGHC _hoops_IICHR _hoops_RSSA */
	_hoops_IRSSR = _hoops_AICIR(start, _hoops_GGSSR);
	_hoops_CRSSR = _hoops_AICIR(_hoops_GGSSR, end);

	/* _hoops_CSGA _hoops_PSPAR _hoops_IICHR _hoops_RSSA */
	vector1 = _hoops_GGSSR - start;
	vector2 = end - _hoops_GGSSR;

	if (one != null) {
		/* _hoops_CSGA _hoops_SHHP _hoops_HPAHR _hoops_IS _hoops_CGIC _hoops_IPPA _hoops_CGSSR */
		*one = _hoops_ARPA (vector1._hoops_SAIAR(vector2), start); 
		if (Vector(one->_hoops_AAIAR())._hoops_PPSSR() < 1.0e-20f)
			return false;
	}

	/* _hoops_GHPHR _hoops_IPPA _hoops_RHIR _hoops_RRSSR _hoops_AARGR _hoops_IS _hoops_RH _hoops_AAGA */
	_hoops_SRSSR = _hoops_ARPA (vector1, _hoops_IRSSR);
	if (Vector(_hoops_SRSSR._hoops_AAIAR())._hoops_PPSSR() < 1.0e-20f)
		return false;

	/* _hoops_GHPHR _hoops_IPPA _hoops_RHIR _hoops_RRSSR _hoops_AARGR _hoops_IS _hoops_RH _hoops_AAGA */
	_hoops_GASSR = _hoops_ARPA (vector2, _hoops_CRSSR);
	if (Vector(_hoops_GASSR._hoops_AAIAR())._hoops_PPSSR() < 1.0e-20f)
		return false;

	/* _hoops_CSGA _hoops_RHCH _hoops_GRP _hoops_HPSSR'_hoops_GRI _hoops_IPSSR _hoops_IS _hoops_CPSSR 3 _hoops_SPSSR _hoops_GHSSR */
	_hoops_CASSR = _hoops_RASSR->b * _hoops_AASSR->c - _hoops_AASSR->b * _hoops_RASSR->c;
	_hoops_IASSR = _hoops_RASSR->a * _hoops_AASSR->c - _hoops_AASSR->a * _hoops_RASSR->c;
	_hoops_HASSR = _hoops_RASSR->a * _hoops_AASSR->b - _hoops_AASSR->a * _hoops_RASSR->b;
	_hoops_RPSSR = one->a * _hoops_CASSR - one->b * _hoops_IASSR + one->c * _hoops_HASSR;

	if (Abs(_hoops_RPSSR) < _hoops_CSCSR)
		return	false;

	dc = _hoops_RASSR->d * _hoops_AASSR->c - _hoops_AASSR->d * _hoops_RASSR->c;
	_hoops_SASSR = _hoops_RASSR->d * _hoops_AASSR->b - _hoops_AASSR->d * _hoops_RASSR->b;
	_hoops_GPSSR = _hoops_RASSR->a * _hoops_AASSR->d - _hoops_AASSR->a * _hoops_RASSR->d;

	_hoops_RPSSR = 1.0f / _hoops_RPSSR;

	center->x = (one->b * dc - one->d * _hoops_CASSR - one->c * _hoops_SASSR) * _hoops_RPSSR;
	center->y = (one->d * _hoops_IASSR - one->a * dc - one->c * _hoops_GPSSR) * _hoops_RPSSR;
	center->z = (one->b * _hoops_GPSSR + one->a * _hoops_SASSR - one->d * _hoops_HASSR) * _hoops_RPSSR;

	/* _hoops_CSGA _hoops_PSAA */
	Vector		v = start - *center;

	*radius = v.length();


	if (plane != null && _hoops_GGHI != null && _hoops_RGHI != null) {
		/* _hoops_CSGA _hoops_PGCR _hoops_HARGR _hoops_PSPAR */
		*_hoops_GGHI = v;

		/* _hoops_GIAP _hoops_HRGR _hoops_SHHP _hoops_HPAHR _hoops_GAPA _hoops_GSSR _hoops_PPR _hoops_SRS _hoops_SPR */
		*_hoops_RGHI = Vector(*plane)._hoops_SAIAR(*_hoops_GGHI);

		length = _hoops_RGHI->length();

		if (length != 0.0f)
			length = *radius / length;
		else
			length = 0.0f;

		*_hoops_RGHI *= length;
	}

	return	true;
}


local void _hoops_RHSSR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_SSCSR *		data) {

	_hoops_PHPIR *				_hoops_HGSSR;
	Point					start, _hoops_GGSSR, end;

	if (!data->valid) {
		if (data->_hoops_PGSSR) {
			if (!data->normal)
				data->normal = &_hoops_IRGA::_hoops_IGHH;
			if (Abs(data->normal->x) > Abs(data->normal->z))
				HI_Cross_Product(data->normal, &_hoops_IRGA::_hoops_IGHH, &data->_hoops_GGHI);
			else
				HI_Cross_Product(data->normal, &_hoops_IRGA::X_Axis, &data->_hoops_GGHI);
			HI_Cross_Product(data->normal, &data->_hoops_GGHI, &data->_hoops_RGHI);

			data->_hoops_GGHI._hoops_AAIAR() *= data->radius;
			data->_hoops_RGHI._hoops_AAIAR() *= data->radius;

			start = data->center + data->_hoops_GGHI;
			_hoops_GGSSR = data->center + data->_hoops_RGHI;
			end = data->center - data->_hoops_GGHI;
			if (!HI_Compute_Three_Point_Circle (start, _hoops_GGSSR, end,
												&data->center, &data->radius,
												&data->plane,
												&data->_hoops_GGHI, &data->_hoops_RGHI)) {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"Insert_Circle_By_Radius generated three colinear points.");
				data->_hoops_HGSSR = (_hoops_PHPIR *) null;
				return;
			}
			data->_hoops_AGSSR = (
				data->center.z == 0 &&
				data->normal->x == 0 &&
				data->normal->y == 0 &&
				data->normal->z != 0);
			data->start = &start;
			data->_hoops_GGSSR = &_hoops_GGSSR;
			data->end = &end;
		}
		else {
			/* _hoops_PPR _hoops_CAHP _hoops_IRS _hoops_PRHC _hoops_HII _hoops_IIH */
			if (!HI_Compute_Three_Point_Circle (*data->start, *data->_hoops_GGSSR, *data->end,
												&data->center, &data->radius,
												&data->plane,
												&data->_hoops_GGHI, &data->_hoops_RGHI)) {
				HE_ERROR (HEC_CIRCLE, HES_COLINEAR_POINTS,"The three definition points are colinear");
				data->_hoops_HGSSR = (_hoops_PHPIR *) null;
				return;
			}
			data->_hoops_AGSSR = (data->start->z == 0.0f && data->_hoops_GGSSR->z == 0.0f && data->end->z == 0.0f);
		}
		data->valid = true;
	}

	if (data->_hoops_AGSSR && BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_AHSSR)) {
		_hoops_AIHI *		c;

		if (owner != null) {
			ZALLOC (c, _hoops_AIHI);
			c->type = _hoops_SGCP;
			c->_hoops_CPGPR = _hoops_PHSSR;
			c->_hoops_RRHH = _hoops_SHHI;
		}
		else {
			c = (_hoops_AIHI *)data->_hoops_HGSSR;
			c->_hoops_CPGPR = _hoops_HHSSR;
		}

		c->center.x = data->center.x;
		c->center.y = data->center.y;
		c->radius = data->radius;

		_hoops_HGSSR = (_hoops_PHPIR *)c;
	}
	else {
		if (owner != null) {
			ZALLOC (_hoops_HGSSR, _hoops_PHPIR);
			_hoops_HGSSR->type = _hoops_SGCP;
			_hoops_HGSSR->_hoops_CPGPR = _hoops_PHSSR;
		}
		else {
			_hoops_HGSSR = data->_hoops_HGSSR;
			_hoops_HGSSR->_hoops_CPGPR = _hoops_HHSSR;
		}

		_hoops_HGSSR->start = *data->start;
		_hoops_HGSSR->_hoops_GGSSR = *data->_hoops_GGSSR;
		_hoops_HGSSR->end = *data->end;

		_hoops_HGSSR->center = data->center;
		_hoops_HGSSR->radius = data->radius;

		_hoops_HGSSR->plane = data->plane;
		_hoops_HGSSR->_hoops_GGHI = data->_hoops_GGHI;
		_hoops_HGSSR->_hoops_RGHI = data->_hoops_RGHI;
	}

	if (owner != null) {
		HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) _hoops_HGSSR, data->_hoops_AGSSR,
							_hoops_IHSSR|_hoops_SIGPR);

		data->_hoops_HGSSR = _hoops_HGSSR;
		++data->_hoops_IGSSR;
	}
}


GLOBAL_FUNCTION Key HI_Insert_Circle (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_SSCSR	data;
	ZERO_STRUCT(&data, _hoops_SSCSR);
	data.start = start;
	data._hoops_GGSSR = _hoops_GGSSR;
	data.end = end;

	_hoops_RHSSR (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data._hoops_HGSSR);

	return _hoops_CHSSR;
}



GLOBAL_FUNCTION Key HI_Insert_Circle_By_Radius (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			center,
	float					radius,
	Vector const *			normal)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_SSCSR			data;
	ZERO_STRUCT(&data, _hoops_SSCSR);
	data.normal = normal;
	data.center = *center;
	data.radius = radius;
	data._hoops_PGSSR = true;

	_hoops_RHSSR  (_hoops_RIGC, item, &data);

	Key		_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data._hoops_HGSSR);

	return _hoops_CHSSR;
}



HC_INTERFACE Key HC_CDECL HC_Insert_Circle_By_Radius (
	Point const *			center,
	double					radius,
	Point const *			normal)
{
	_hoops_PAPPR context("Insert_Circle_By_Radius");

	if (!center) {
		HE_ERROR (HEC_CIRCLE, HES_INVALID_INPUT, "Center point must be provided.");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Circle_By_Radius (context, target, center, (float)radius, (Vector const*)normal);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT center, normal;\n");
		HI_Dump_Code ("float radius;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "center.x = %f;	 center.y = %f;	 ",center->x, center->y));
		HI_Dump_Code (Sprintf_F (null, "center.z = %f;\n", center->z));
		HI_Dump_Code (Sprintf_F (null, "radius = %f;\n", radius));
		if (normal) {
			HI_Dump_Code (Sprintf_FF (null, "normal.x = %f;	 normal.y = %f;	 ", normal->x, normal->y));
			HI_Dump_Code (Sprintf_F (null, "normal.z = %f;\n", normal->z));
		}
		else
			HI_Dump_Code ("normal.x = 0;  normal.y = 0; normal.z = 1;\n");
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Insert_Circle_By_Radius (&center, radius, &normal), %D);}\n", _hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Circle (
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end)
{
	_hoops_PAPPR context("Insert_Circle");

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Circle (context, target, start, _hoops_GGSSR,end);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT start, middle, end;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "start.x = %f;	start.y = %f;  ",start->x, start->y));
		HI_Dump_Code (Sprintf_F (null, "start.z = %f;\n", start->z));
		HI_Dump_Code (Sprintf_FF (null, "middle.x = %f;	 middle.y = %f;	 ", _hoops_GGSSR->x, _hoops_GGSSR->y));
		HI_Dump_Code (Sprintf_F (null, "middle.z = %f;\n", _hoops_GGSSR->z));
		HI_Dump_Code (Sprintf_FF (null, "end.x = %f;  end.y = %f;  ",end->x, end->y));
		HI_Dump_Code (Sprintf_F (null, "end.z = %f;\n", end->z));
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Insert_Circle (&start, &middle, &end), %D);}\n",_hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}

GLOBAL_FUNCTION void HI_Edit_Circle(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_PHPIR	*				_hoops_HGSSR,
	Point					start,
	Point					_hoops_GGSSR,
	Point					end)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_CRCP * owner;

	if (BIT (_hoops_HGSSR->_hoops_RRHH, _hoops_SHHI)) {
		Point center;
		_hoops_AIHI *_hoops_RISSR = (_hoops_AIHI *) _hoops_HGSSR;

		if (start.z != 0.0f || _hoops_GGSSR.z != 0.0f || end.z != 0.0f) {
			HE_ERROR2 (HEC_CIRCLE, HES_INVALID_COORDINATE_SPACE,
				"Edit_Circle cannot change a circle from flat (all z==0) to non-flat.",
				"Please delete and reinsert instead.");
			return;
		}
		if (!HI_Compute_Three_Point_Circle (start, _hoops_GGSSR, end,
			&center, &_hoops_RISSR->radius,
			null, null, null)) {
				HE_ERROR (HEC_CIRCLE, HES_COLINEAR_POINTS, "The three definition points are colinear");
				return;
		}
		_hoops_RISSR->center.x = center.x;
		_hoops_RISSR->center.y = center.y;
	}
	else {
		if (!HI_Compute_Three_Point_Circle (start, _hoops_GGSSR, end,
			&_hoops_HGSSR->center, &_hoops_HGSSR->radius,
			&_hoops_HGSSR->plane,
			&_hoops_HGSSR->_hoops_GGHI, &_hoops_HGSSR->_hoops_RGHI)) {
				HE_ERROR (HEC_CIRCLE, HES_COLINEAR_POINTS, "The three definition points are colinear");
				return;
		}
		_hoops_HGSSR->start = start;
		_hoops_HGSSR->_hoops_GGSSR = _hoops_GGSSR;
		_hoops_HGSSR->end = end;
	}
	_hoops_HGSSR->_hoops_CPGPR = _hoops_HHSSR;
	owner = _hoops_HGSSR->owner;
	if (owner != null) {
		_hoops_SASIR (_hoops_RIGC, owner,
			_hoops_AISSR |
			_hoops_PISSR |
			_hoops_HISSR |
			_hoops_IISSR |
			_hoops_RPSIR);
	}

	if (owner)
		HI_Antiquate_Bounding (owner, true);
}

HC_INTERFACE void HC_CDECL HC_Edit_Circle (
	Key					key,
	Point const *		start,
	Point const *		_hoops_GGSSR,
	Point const *		end)
{
	_hoops_PAPPR context("Edit_Circle");
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, key, _hoops_CISSR)) != null) {
		HI_Edit_Circle(context, (_hoops_PHPIR *)target, *start, *_hoops_GGSSR, *end);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT start, middle, end;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "start.x = %f;	start.y = %f;  ", start->x, start->y));
		HI_Dump_Code (Sprintf_F (null, "start.z = %f;\n", start->z));
		HI_Dump_Code (Sprintf_FF (null, "middle.x = %f;	 middle.y = %f;	 ", _hoops_GGSSR->x, _hoops_GGSSR->y));
		HI_Dump_Code (Sprintf_F (null, "middle.z = %f;\n", _hoops_GGSSR->z));
		HI_Dump_Code (Sprintf_FF (null, "end.x = %f;  end.y = %f;  ", end->x, end->y));
		HI_Dump_Code (Sprintf_F (null, "end.z = %f;\n", end->z));
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Circle (LOOKUP (%D), ", key));
		HI_Dump_Code ("&start, &middle, &end);}\n");
		--HOOPS_WORLD->_hoops_ISPPR;
	);
}

HC_INTERFACE void HC_CDECL HC_Edit_Circle_By_Radius (
	Key						key,
	Point const *			center,
	double					_hoops_SISSR,
	Point const *			_hoops_GCSSR)
{
	_hoops_PAPPR context("Edit_Circle_By_Radius");

	Vector const *			normal = (Vector const *)_hoops_GCSSR;
	float					radius = (float)_hoops_SISSR;

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT center, normal;\n");
		HI_Dump_Code ("float radius;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "center.x = %f;	 center.y = %f;	 ",center->x, center->y));
		HI_Dump_Code (Sprintf_F (null, "center.z = %f;\n", center->z));
		HI_Dump_Code (Sprintf_F (null, "radius = %f;\n", radius));
		if (normal) {
			HI_Dump_Code (Sprintf_FF (null, "normal.x = %f;	 normal.y = %f;	 ", normal->x, normal->y));
			HI_Dump_Code (Sprintf_F (null, "normal.z = %f;\n", normal->z));
		}
		else
			HI_Dump_Code ("normal.x = 0;  normal.y = 0; normal.z = 1;\n");
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Circle_By_Radius (LOOKUP (%D), ", key));
		HI_Dump_Code ("&center, radius, &normal);}\n");
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_CRCP *	owner;
	_hoops_RPPPR();
	_hoops_SSCSR			data;
	_hoops_PHPIR * c = (_hoops_PHPIR *)_hoops_RCSSR (context, key);

	if (c == null || c->type != _hoops_SGCP ||
		BIT (c->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid circle");
		goto Release;
	}
	if (BIT (c->_hoops_RRHH, _hoops_SHHI) &&
		(center->z != 0 || normal->x != 0 || normal->y != 0 || normal->z == 0)) {
		HE_ERROR2 (HEC_CIRCLE, HES_INVALID_COORDINATE_SPACE,
					"Edit_Circle_By_Radius cannot change a circle from flat (all z==0) to non-flat.",
					"Please delete and reinsert instead.");
		goto Release;
	}

	ZERO_STRUCT(&data, _hoops_SSCSR);
	data.normal = normal;
	data.center = *center;
	data.radius = radius;
	data._hoops_PGSSR = true;
	data._hoops_HGSSR = c;
	_hoops_RHSSR (context, null, &data);

	c->_hoops_CPGPR = _hoops_HHSSR;
	owner = c->owner;
	if (owner != null) {
		_hoops_SASIR (context, owner, _hoops_AISSR|_hoops_PISSR|
			_hoops_HISSR|_hoops_IISSR|_hoops_RPSIR);
	}

	if (owner)
		HI_Antiquate_Bounding (owner, true);

  Release:
	_hoops_IRRPR();
}



HC_INTERFACE void HC_CDECL HC_Show_Circle (
	Key			key,
	Point *		start,
	Point *		_hoops_GGSSR,
	Point *		end)
{
	_hoops_PAPPR context("Show_Circle");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Circle () */\n");
	);

	_hoops_CSPPR();
	_hoops_PHPIR const *	_hoops_HGSSR = (_hoops_PHPIR const *)_hoops_RCSSR (context, key);

	if (_hoops_HGSSR == null ||
		_hoops_HGSSR->type != _hoops_SGCP ||
		BIT (_hoops_HGSSR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CIRCLE, HES_INVALID_KEY, "Provided key does not refer to a valid circle");
	}
	else if (BIT (_hoops_HGSSR->_hoops_RRHH, _hoops_SHHI)) {
		_hoops_AIHI const *	c;

		c = (_hoops_AIHI const *)_hoops_HGSSR;

		if (start != null)
			*start = Point (c->center.x + c->radius, c->center.y, 0.0f);
		if (_hoops_GGSSR != null)
			*_hoops_GGSSR = Point (c->center.x, c->center.y + c->radius, 0.0f);
		if (end != null)
			*end = Point (c->center.x - c->radius, c->center.y, 0.0f);
	}
	else {
		if (start != null)
			*start = _hoops_HGSSR->start;
		if (_hoops_GGSSR != null)
			*_hoops_GGSSR = _hoops_HGSSR->_hoops_GGSSR;
		if (end != null)
			*end = _hoops_HGSSR->end;
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Circle_By_Radius (
	Key			key,
	Point *		center,
	float *		radius,
	Vector *	normal)
{
	_hoops_PAPPR context("Show_Circle_By_Radius");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Circle_By_Radius () */\n");
	);

	_hoops_CSPPR();

	_hoops_PHPIR const *	_hoops_HGSSR = (_hoops_PHPIR const *)_hoops_RCSSR (context, key);

	if (_hoops_HGSSR == null ||
		_hoops_HGSSR->type != _hoops_SGCP ||
		BIT (_hoops_HGSSR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CIRCLE, HES_INVALID_KEY,"Provided key does not refer to a valid circle");
	}
	else if (BIT (_hoops_HGSSR->_hoops_RRHH, _hoops_SHHI)) {
		_hoops_AIHI const *	c;

		c = (_hoops_AIHI const *)_hoops_HGSSR;

		if (center != null)
			*center = Point (c->center.x, c->center.y, 0.0f);
		if (radius != null)
			*radius = c->radius;
		if (normal != null)
			*normal = _hoops_IRGA::_hoops_IGHH;
	}
	else {
		if (center != null)
			*center = _hoops_HGSSR->center;
		if (radius != null)
			*radius = _hoops_HGSSR->radius;
		if (normal != null)
			*normal = _hoops_HGSSR->plane;
	}

	_hoops_IRRPR();
#endif
}



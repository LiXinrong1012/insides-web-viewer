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
 * $Id: obf_tmp.txt 1.115 2010-11-16 00:25:05 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_ACSSR {
	Point const		*start,
					*_hoops_GGSSR,
					*end;

	Point			center;
	float			radius;
	_hoops_ARPA			plane;
	Vector			_hoops_GGHI, _hoops_RGHI;
	float			arc_length;

	bool			_hoops_AGSSR;
	bool			_hoops_PCSSR;
	bool			valid;

	Circular_Arc *	arc;
	int				_hoops_IGSSR;
	Type			type;
};


local float _hoops_HCSSR (
	Point const &	start,
	Point const &	_hoops_GGSSR,
	Point const &	end,
	Point const &	center,
	float			radius) {
	float			_hoops_ICSSR;
	float			theta;
	Point			_hoops_ISPI, _hoops_CSPI, _hoops_SSPI;
	Point			_hoops_CCSSR, _hoops_SCSSR, _hoops_GSSSR;

	_hoops_ISPI.x = start.x - center.x;
	_hoops_ISPI.y = start.y - center.y;
	_hoops_ISPI.z = start.z - center.z;

	_hoops_CSPI.x = _hoops_GGSSR.x - center.x;
	_hoops_CSPI.y = _hoops_GGSSR.y - center.y;
	_hoops_CSPI.z = _hoops_GGSSR.z - center.z;

	_hoops_SSPI.x = end.x - center.x;
	_hoops_SSPI.y = end.y - center.y;
	_hoops_SSPI.z = end.z - center.z;

	/* _hoops_SHHP _hoops_RSSSR _hoops_GRS _hoops_HAR _hoops_HGAP _hoops_ASSSR */
	_hoops_CCSSR.x = _hoops_ISPI.y * _hoops_CSPI.z - _hoops_ISPI.z * _hoops_CSPI.y;
	_hoops_CCSSR.y = _hoops_ISPI.z * _hoops_CSPI.x - _hoops_ISPI.x * _hoops_CSPI.z;
	_hoops_CCSSR.z = _hoops_ISPI.x * _hoops_CSPI.y - _hoops_ISPI.y * _hoops_CSPI.x;

	_hoops_SCSSR.x = _hoops_CSPI.y * _hoops_SSPI.z - _hoops_CSPI.z * _hoops_SSPI.y;
	_hoops_SCSSR.y = _hoops_CSPI.z * _hoops_SSPI.x - _hoops_CSPI.x * _hoops_SSPI.z;
	_hoops_SCSSR.z = _hoops_CSPI.x * _hoops_SSPI.y - _hoops_CSPI.y * _hoops_SSPI.x;

	_hoops_GSSSR.x = _hoops_ISPI.y * _hoops_SSPI.z - _hoops_ISPI.z * _hoops_SSPI.y;
	_hoops_GSSSR.y = _hoops_ISPI.z * _hoops_SSPI.x - _hoops_ISPI.x * _hoops_SSPI.z;
	_hoops_GSSSR.z = _hoops_ISPI.x * _hoops_SSPI.y - _hoops_ISPI.y * _hoops_SSPI.x;

	if (radius == 0.0f)
		return 0;
	_hoops_ICSSR = (_hoops_ISPI.x * _hoops_SSPI.x + _hoops_ISPI.y * _hoops_SSPI.y + _hoops_ISPI.z * _hoops_SSPI.z) /
			(radius * radius);


	/* _hoops_RRP _hoops_IS _hoops_PSSSR _hoops_IH _hoops_HSSSR _hoops_HHGS */
	if (_hoops_ICSSR > 1.0f) _hoops_ICSSR = 1.0f; else if (_hoops_ICSSR < -1.0f) _hoops_ICSSR = -1.0f;

	theta = _hoops_ISSSR (_hoops_ICSSR) * 1.0f / 360.0f;

	if (_hoops_CCSSR.x * _hoops_SCSSR.x + _hoops_CCSSR.y * _hoops_SCSSR.y + _hoops_CCSSR.z * _hoops_SCSSR.z > 0.0f &&
		_hoops_CCSSR.x * _hoops_GSSSR.x + _hoops_CCSSR.y * _hoops_GSSSR.y + _hoops_CCSSR.z * _hoops_GSSSR.z > 0.0f)
		return theta;
	else
		return 1.0f - theta;
}


local void _hoops_CSSSR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		owner,
	_hoops_ACSSR *			data)
{
	Circular_Arc *			arc;

	if (!data->valid) {
		data->_hoops_AGSSR = (data->start->z == 0.0f && data->_hoops_GGSSR->z == 0.0f && data->end->z == 0.0f);

		/* _hoops_PPR _hoops_CAHP _hoops_IRS _hoops_PRHC _hoops_HII _hoops_IIH */
		if (!HI_Compute_Three_Point_Circle (*data->start, *data->_hoops_GGSSR, *data->end,
											&data->center, &data->radius,
											&data->plane,
											&data->_hoops_GGHI, &data->_hoops_RGHI)) {
			data->_hoops_PCSSR = true;
		}
		else {
			data->_hoops_PCSSR = false;
			data->arc_length = _hoops_HCSSR (*data->start, *data->_hoops_GGSSR, *data->end, data->center, data->radius);
		}

		data->valid = true;
	}

	if (data->_hoops_PCSSR) {
		_hoops_SSSSR *a;

		/* _hoops_CCPP _hoops_IS _hoops_RH _hoops_IGIR _hoops_IIGR _hoops_IRS _hoops_SHISR (_hoops_HAR _hoops_IRS _hoops_IISGR) _hoops_GRII _hoops_PGIS _hoops_HIS
			_hoops_SGS _hoops_SCH _hoops_PAH _hoops_SHH _hoops_GGGGA _hoops_GGR _hoops_HGHC */
		ZALLOC (arc, Circular_Arc);
		a = (_hoops_SSSSR *)arc;

		a->_hoops_RRHH = _hoops_RGGGA;

		a->points[0] = *data->start;
		a->points[1] = *data->_hoops_GGSSR;
		a->points[2] = *data->end;
	}
	else if (data->_hoops_AGSSR && BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_AHSSR)) {
		Circular_Arc_Lite *			a;

		ZALLOC (a, Circular_Arc_Lite);

		a->_hoops_RRHH = _hoops_SHHI;

		a->center.x = data->center.x;
		a->center.y = data->center.y;
		a->radius = data->radius;

		a->arc_start = _hoops_AGGGA (data->_hoops_GGHI.y, data->_hoops_GGHI.x) / 360.0f;

		if (a->arc_start < 0.0f)
			a->arc_start += 1.0f;

		if (data->_hoops_GGHI.x * data->_hoops_RGHI.y -
			data->_hoops_GGHI.y * data->_hoops_RGHI.x < 0.0f)
			a->_hoops_PHHI = a->arc_start - data->arc_length;
		else
			a->_hoops_PHHI = a->arc_start + data->arc_length;

		arc = (Circular_Arc *)a;
	}
	else {
		ZALLOC (arc, Circular_Arc);

		arc->start =  *data->start;
		arc->_hoops_GGSSR = *data->_hoops_GGSSR;
		arc->end =    *data->end;

		arc->center = data->center;
		arc->radius = data->radius;

		arc->plane = data->plane;

		arc->_hoops_GGHI = data->_hoops_GGHI;
		arc->_hoops_RGHI = data->_hoops_RGHI;

		arc->arc_start = 0.0f;	/* _hoops_ICISR _hoops_PGIS _hoops_AAACR */
		arc->_hoops_PHHI = data->arc_length;
	}

	arc->type = data->type;
	arc->_hoops_CPGPR = _hoops_PHSSR;

	HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) arc, data->_hoops_AGSSR,
						data->type == _hoops_RIIP ?
								_hoops_IHSSR :
								_hoops_IHSSR |
										_hoops_SIGPR);

	data->arc = arc;
	++data->_hoops_IGSSR;
}



GLOBAL_FUNCTION Key HI_Insert_Circular_Arc (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_ACSSR			data;
	ZERO_STRUCT(&data, _hoops_ACSSR);
	data.start = start;
	data._hoops_GGSSR = _hoops_GGSSR;
	data.end = end;
	data.type = _hoops_RIIP;

	_hoops_CSSSR (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.arc);

	return _hoops_CHSSR;
}


GLOBAL_FUNCTION Key HI_Insert_Circular_Chord (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_ACSSR			data;
	ZERO_STRUCT(&data, _hoops_ACSSR);
	data.start = start;
	data._hoops_GGSSR = _hoops_GGSSR;
	data.end = end;
	data.type = _hoops_GRCP;

	_hoops_CSSSR (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.arc);

	return _hoops_CHSSR;
}

GLOBAL_FUNCTION Key HI_Insert_Circular_Wedge (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_ACSSR			data;
	ZERO_STRUCT(&data, _hoops_ACSSR);
	data.start = start;
	data._hoops_GGSSR = _hoops_GGSSR;
	data.end = end;
	data.type = _hoops_RRCP;

	_hoops_CSSSR (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.arc);

	return _hoops_CHSSR;
}



HC_INTERFACE Key HC_CDECL HC_Insert_Circular_Arc (
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end)
{
	_hoops_PAPPR context("KInsert_Circular_Arc");

	if (!start || !_hoops_GGSSR || !end) {
		HE_ERROR (HEC_CIRCULAR_ARC, HES_INVALID_INPUT, "All points must be provided.");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Circular_Arc (context, target, start, _hoops_GGSSR, end);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT start, middle, end;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "start.x = %f;	start.y = %f;  ",start->x, start->y));
		HI_Dump_Code (Sprintf_F (null, "start.z = %f;\n", start->z));
		HI_Dump_Code (Sprintf_FF (null, "middle.x = %f;	 middle.y = %f;	 ",_hoops_GGSSR->x, _hoops_GGSSR->y));
		HI_Dump_Code (Sprintf_F (null, "middle.z = %f;\n", _hoops_GGSSR->z));
		HI_Dump_Code (Sprintf_FF (null, "end.x = %f;  end.y = %f;  ", end->x, end->y));
		HI_Dump_Code (Sprintf_F (null, "end.z = %f;\n", end->z));
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_KInsert_Circular_Arc (&start, &middle, &end), %D);}\n",_hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Circular_Chord (
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end)
{
	_hoops_PAPPR context("KInsert_Circular_Chord");

	if (!start || !_hoops_GGSSR || !end) {
		HE_ERROR (HEC_CIRCULAR_CHORD, HES_INVALID_INPUT, "All points must be provided.");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Circular_Chord (context, target, start, _hoops_GGSSR, end);
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
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_KInsert_Circular_Chord (&start, &middle, &end), %D);}\n", _hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}



HC_INTERFACE Key HC_CDECL HC_Insert_Circular_Wedge (
	Point const *			start,
	Point const *			_hoops_GGSSR,
	Point const *			end)
{
	_hoops_PAPPR context("KInsert_Circular_Wedge");

	if (!start || !_hoops_GGSSR || !end) {
		HE_ERROR (HEC_CIRCULAR_WEDGE, HES_INVALID_INPUT, "All points must be provided.");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Circular_Wedge (context, target, start, _hoops_GGSSR, end);
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
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_KInsert_Circular_Wedge (&start, &middle, &end), %D);}\n", _hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}


local void _hoops_PGGGA (
	Circular_Arc *		arc,
	float				x,
	float				y,
	float				z) {

	if (BIT (arc->_hoops_RRHH, _hoops_SHHI)) {
		Circular_Arc_Lite *	a = (Circular_Arc_Lite *)arc;

		if (z != 0.0) {
			HE_ERROR2 (HEC_CIRCLE, HES_INVALID_COORDINATE_SPACE,
						"Set_Circular_Center cannot change a circular geometry from flat (all z==0) to non-flat.",
						"Please delete and reinsert instead.");
			return;
		}

		if (a->type == _hoops_SGCP) {
			/* _hoops_HAR _hoops_GSGS _hoops_SR _hoops_PAH _hoops_CPSA _hoops_AA _hoops_CCA _hoops_RGR */
			a->center.x = x;
			a->center.y = y;
			a->_hoops_RRHH |= _hoops_HGGGA;
		}
		else {
			Point				start, end, _hoops_GGSSR, center;
			float				_hoops_GGHCR, _hoops_AGHCR;
			bool				_hoops_IGGGA = (a->_hoops_PHHI < a->arc_start);

			_hoops_RICH (a->arc_start * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
			start.x = a->center.x + a->radius * _hoops_AGHCR;
			start.y = a->center.y + a->radius * _hoops_GGHCR;
			start.z = 0.0f;
			_hoops_RICH (a->_hoops_PHHI * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
			end.x = a->center.x + a->radius * _hoops_AGHCR;
			end.y = a->center.y + a->radius * _hoops_GGHCR;
			end.z = 0.0f;

			/* _hoops_RRP _hoops_IRGP _hoops_IH _hoops_CGGGA _hoops_SGGGA _hoops_SPCC */
			_hoops_RICH (0.5f * (a->arc_start + a->_hoops_PHHI) * 360.0f, _hoops_GGHCR, _hoops_AGHCR);
			_hoops_GGSSR.x = a->center.x + a->radius * _hoops_AGHCR;
			_hoops_GGSSR.y = a->center.y + a->radius * _hoops_GGHCR;
			_hoops_GGSSR.z = 0.0f;

			/* _hoops_RHCH _hoops_GAR _hoops_IRHP _hoops_AAGA */
			center.x = start.x - x;
			center.y = start.y - y;
			a->radius = _hoops_SGIHR (center.x * center.x + center.y * center.y);
			/* _hoops_CCAH _hoops_HSPP _hoops_RCSA _hoops_IIHA _hoops_GPP _hoops_AAGA */
			a->arc_start = _hoops_AGGGA (center.y, center.x) / 360.0f;
			if (a->arc_start < 0.0f)
				a->arc_start += 1.0f;

			/* _hoops_HPHR _hoops_RHCH _hoops_HA */
			center.x = a->center.x = x;
			center.y = a->center.y = y;
			center.z = 0.0f;

			/* _hoops_GRGGA _hoops_SPCC */
			float length = _hoops_HCSSR (start, _hoops_GGSSR, end, center, a->radius);
			if (_hoops_IGGGA)
				length = -length;

			a->_hoops_PHHI = a->arc_start + length;

			a->_hoops_RRHH |= _hoops_HGGGA;
		}
	}
	else {
		float		length, radius;

		arc->center.x = x;
		arc->center.y = y;
		arc->center.z = z;

		if (arc->type == _hoops_SGCP) {
			_hoops_PHPIR *		_hoops_HGSSR = (_hoops_PHPIR *)arc;

			_hoops_HGSSR->_hoops_GGHI.x = _hoops_HGSSR->start.x - x;
			_hoops_HGSSR->_hoops_GGHI.y = _hoops_HGSSR->start.y - y;
			_hoops_HGSSR->_hoops_GGHI.z = _hoops_HGSSR->start.z - z;

			length = _hoops_HGSSR->_hoops_GGHI.x * _hoops_HGSSR->_hoops_GGHI.x +
					 _hoops_HGSSR->_hoops_GGHI.y * _hoops_HGSSR->_hoops_GGHI.y +
					 _hoops_HGSSR->_hoops_GGHI.z * _hoops_HGSSR->_hoops_GGHI.z;
			radius = _hoops_HGSSR->radius = _hoops_SGIHR (length);
		}
		else {
			arc->_hoops_GGHI.x = arc->start.x - x;
			arc->_hoops_GGHI.y = arc->start.y - y;
			arc->_hoops_GGHI.z = arc->start.z - z;

			length = arc->_hoops_GGHI.x * arc->_hoops_GGHI.x +
					 arc->_hoops_GGHI.y * arc->_hoops_GGHI.y +
					 arc->_hoops_GGHI.z * arc->_hoops_GGHI.z;
			radius = arc->radius = _hoops_SGIHR (length);
		}


		/* _hoops_GIAP _hoops_HRGR _hoops_SHHP _hoops_HPAHR _hoops_GAPA _hoops_GSSR _hoops_PPR _hoops_SRS _hoops_SPR */
		arc->_hoops_RGHI.x = arc->plane.b  * arc->_hoops_GGHI.z -
						arc->_hoops_GGHI.y * arc->plane.c;
		arc->_hoops_RGHI.y = arc->plane.c  * arc->_hoops_GGHI.x -
						arc->_hoops_GGHI.z * arc->plane.a;
		arc->_hoops_RGHI.z = arc->plane.a  * arc->_hoops_GGHI.y -
						arc->_hoops_GGHI.x * arc->plane.b;

		length = arc->_hoops_RGHI.x * arc->_hoops_RGHI.x +
				 arc->_hoops_RGHI.y * arc->_hoops_RGHI.y +
				 arc->_hoops_RGHI.z * arc->_hoops_RGHI.z;
		length = _hoops_SGIHR (length);

		if (length != 0.0f)
			length = radius / length;
		else
			length = 0.0f;

		arc->_hoops_RGHI.x *= length;
		arc->_hoops_RGHI.y *= length;
		arc->_hoops_RGHI.z *= length;

		if (arc->type == _hoops_SGCP)
			arc->_hoops_RRHH |= _hoops_HGGGA;
		else {
			arc->_hoops_PHHI = arc->arc_start +
							_hoops_HCSSR (arc->start, arc->_hoops_GGSSR, arc->end,
													arc->center, radius);
			arc->_hoops_RRHH |= _hoops_HGGGA;
		}
	}
}

HC_INTERFACE void HC_CDECL HC_Set_Circular_Center (
	double					x,
	double					y,
	double					z)
{
	_hoops_PAPPR context("Set_Circular_Center");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Set_Circular_Center (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RRGGA)) != null) {
		Circular_Arc *	c = (Circular_Arc *)target;
		_hoops_PGGGA (c, (float)x, (float)y, (float)z);
		_hoops_IRRPR();
	}
}

HC_INTERFACE void HC_CDECL HC_Set_Circular_Center_By_Key (
	Key					key,
	double				x,
	double				y,
	double				z)
{
	_hoops_PAPPR context("Set_Circular_Center_By_Key");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Set_Circular_Center_By_Key (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, key, _hoops_RRGGA)) != null) {
		Circular_Arc *	c = (Circular_Arc *)target;
		_hoops_PGGGA (c, (float)x, (float)y, (float)z);
		_hoops_IRRPR();
	}
}


local void _hoops_ARGGA (
	Circular_Arc *arc,
	Point		*start,
	Point		*_hoops_GGSSR,
	Point		*end) {

	if (arc->type == _hoops_RIIP &&
		BIT (arc->_hoops_RRHH, _hoops_RGGGA)) {
		_hoops_SSSSR const *	a;

		a = (_hoops_SSSSR const *)arc;

		if (start != null)
			*start = a->points[0];
		if (start != null)
			*_hoops_GGSSR = a->points[1];
		if (start != null)
			*end = a->points[2];
	}
	else if (BIT (arc->_hoops_RRHH, _hoops_SHHI)) {
		Circular_Arc_Lite const *	a;
		float			_hoops_GGHCR, _hoops_AGHCR;

		a = (Circular_Arc_Lite const *)arc;

		if (start != null) {
			_hoops_RICH (a->arc_start * 360.0f, _hoops_GGHCR, _hoops_AGHCR);

			start->x = a->center.x + _hoops_AGHCR * a->radius;
			start->y = a->center.y + _hoops_GGHCR * a->radius;
			start->z = 0.0f;
		}

		if (_hoops_GGSSR != null) {
			_hoops_RICH (0.5f * (a->arc_start + a->_hoops_PHHI) * 360.0f,
					   _hoops_GGHCR, _hoops_AGHCR);

			_hoops_GGSSR->x = a->center.x + _hoops_AGHCR * a->radius;
			_hoops_GGSSR->y = a->center.y + _hoops_GGHCR * a->radius;
			_hoops_GGSSR->z = 0.0f;
		}

		if (end != null) {
			_hoops_RICH (a->_hoops_PHHI * 360.0f, _hoops_GGHCR, _hoops_AGHCR);

			end->x = a->center.x + _hoops_AGHCR * a->radius;
			end->y = a->center.y + _hoops_GGHCR * a->radius;
			end->z = 0.0f;
		}
	}
	else {
		if (start != null)
			*start = arc->start;

		if (_hoops_GGSSR != null)
			*_hoops_GGSSR = arc->_hoops_GGSSR;

		if (end != null)
			*end = arc->end;
	}
}

HC_INTERFACE void HC_CDECL HC_Show_Circular_Arc (
	Key			key,
	Point *		start,
	Point *		_hoops_GGSSR,
	Point *		end)
{
	_hoops_PAPPR context("Show_Circular_Arc");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Circular_Arc () */\n");
	);

	_hoops_CSPPR();

	Circular_Arc *	arc = (Circular_Arc *)_hoops_RCSSR (context, key);

	if (arc == null ||
		arc->type != _hoops_RIIP ||
		BIT (arc->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CIRCULAR_ARC, HES_INVALID_KEY, "Provided key does not refer to a valid circular arc");
	}
	else
		_hoops_ARGGA (arc, start, _hoops_GGSSR, end);

	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Circular_Chord (
	Key			key,
	Point *		start,
	Point *		_hoops_GGSSR,
	Point *		end)
{
	_hoops_PAPPR context("Show_Circular_Chord");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Circular_Chord () */\n");
	);

	_hoops_CSPPR();

	Circular_Arc *arc = (Circular_Arc *)_hoops_RCSSR (context, key);

	if (arc == null ||
		arc->type != _hoops_GRCP ||
		BIT (arc->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CIRCULAR_CHORD, HES_INVALID_KEY, "Provided key does not refer to a valid circular chord");
	}
	else
		_hoops_ARGGA (arc, start, _hoops_GGSSR, end);

	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Circular_Wedge (
	Key			key,
	Point		*start,
	Point		*_hoops_GGSSR,
	Point		*end)
{
	_hoops_PAPPR context("Show_Circular_Wedge");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Circular_Wedge ()*/\n");
	);

	_hoops_CSPPR();

	Circular_Arc *	arc = (Circular_Arc *)_hoops_RCSSR (context, key);

	if (arc == null ||
		arc->type != _hoops_RRCP ||
		BIT (arc->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CIRCULAR_WEDGE, HES_INVALID_KEY, "Provided key does not refer to a valid circular wedge");
	}
	else
		_hoops_ARGGA (arc, start, _hoops_GGSSR, end);

	_hoops_IRRPR();
#endif
}



HC_INTERFACE bool HC_CDECL HC_Show_Circular_Center (
	Key					key,
	float *				x,
	float *				y,
	float *				z)
{
	_hoops_PAPPR				context("Show_Circular_Center");
	bool				_hoops_PRGGA = false;

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Circular_Center ()*/\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, key, _hoops_HRGGA)) != null) {
		Circular_Arc const * c = (Circular_Arc const *)target;

		if (BIT (c->_hoops_RRHH, _hoops_SHHI)) {
			Circular_Arc_Lite const *	a = (Circular_Arc_Lite const *)c;
			*x = a->center.x;
			*y = a->center.y;
			*z = 0.0f;
		}
		else {
			*x = c->center.x;
			*y = c->center.y;
			*z = c->center.z;
		}

		_hoops_PRGGA = BIT (c->_hoops_RRHH, _hoops_HGGGA);

		_hoops_IRRPR();
	}

	return _hoops_PRGGA;
}

GLOBAL_FUNCTION void HI_Edit_Circular_Arc (
	_hoops_AIGPR *	_hoops_RIGC,
	Circular_Arc *			c,
	Point					start,
	Point					_hoops_GGSSR,
	Point					end)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_CRCP *owner;

	if (BIT(c->_hoops_RRHH, _hoops_SHHI)) {
		Circular_Arc_Lite *_hoops_RISSR;
		bool _hoops_AGSSR;
		_hoops_ARPA plane;
		Vector _hoops_GGHI, _hoops_RGHI;
		Point center;
		float length;

		_hoops_RISSR = (Circular_Arc_Lite *)c;
		_hoops_AGSSR = (start.z == 0.0f && _hoops_GGSSR.z == 0.0f && end.z == 0.0f);
		if (!_hoops_AGSSR) {
			HE_ERROR2 (HEC_CIRCLE, HES_INVALID_COORDINATE_SPACE,
				"Edit_Circular_Arc cannot change a circular arc from flat (all z==0) to non-flat.",
				"Please delete and reinsert instead.");
			return;
		}
		if (!HI_Compute_Three_Point_Circle (start, _hoops_GGSSR, end,
			&center, &_hoops_RISSR->radius,
			&plane, &_hoops_GGHI, &_hoops_RGHI)) {
				HE_ERROR (HEC_CIRCLE, HES_COLINEAR_POINTS, "The three definition points are colinear");
				return;
		}
		_hoops_RISSR->center.x = center.x;
		_hoops_RISSR->center.y = center.y;
		length = _hoops_HCSSR (start, _hoops_GGSSR, end, center, _hoops_RISSR->radius);
		/* _hoops_SR _hoops_RRP _hoops_HSPP _hoops_CSCHR _hoops_IS _hoops_IRGGA, _hoops_HAR 0 _hoops_CSCHR _hoops_IS _hoops_CRGGA */
		_hoops_RISSR->arc_start = _hoops_AGGGA (_hoops_GGHI.y, _hoops_GGHI.x) / 360.0f;
		if (_hoops_RISSR->arc_start < 0.0f)
			_hoops_RISSR->arc_start += 1.0f;
		/* _hoops_PPR _hoops_SICR _hoops_IS _hoops_SRGGA _hoops_RPP _hoops_SIGR */
		if (_hoops_GGHI.x * _hoops_RGHI.y -
			_hoops_GGHI.y * _hoops_RGHI.x < 0.0f)
			_hoops_RISSR->arc_start -= length;
		_hoops_RISSR->_hoops_PHHI = _hoops_RISSR->arc_start + length;
	}
	else {
		c->_hoops_RRHH = 0;
		if (HI_Compute_Three_Point_Circle (start, _hoops_GGSSR, end,
			&c->center, &c->radius,
			&c->plane,
			&c->_hoops_GGHI, &c->_hoops_RGHI)) {
				c->start = start;
				c->_hoops_GGSSR = _hoops_GGSSR;
				c->end = end;
				c->arc_start = 0.0f;
				c->_hoops_PHHI = _hoops_HCSSR (start, _hoops_GGSSR, end, c->center, c->radius);
		}
		else {
			_hoops_SSSSR *_hoops_GAGGA = (_hoops_SSSSR *)c;
			_hoops_GAGGA->_hoops_RRHH |= _hoops_RGGGA;
			_hoops_GAGGA->points[0] = start;
			_hoops_GAGGA->points[1] = _hoops_GGSSR;
			_hoops_GAGGA->points[2] = end;
		}
	}
	c->_hoops_CPGPR = _hoops_HHSSR;
	owner = c->owner;
	if (owner != null) {
		_hoops_SASIR (_hoops_RIGC, owner, _hoops_RAGGA|_hoops_PISSR|_hoops_RPSIR);
		HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, owner, _hoops_RIIP, c, 0);
	}

	if (owner)
		HI_Antiquate_Bounding (owner, true);
}

HC_INTERFACE void HC_CDECL HC_Edit_Circular_Arc (
	Key					key,
	Point const *		start,
	Point const *		_hoops_GGSSR,
	Point const *		end)
{
	_hoops_PAPPR				context("Edit_Circular_Arc");
	_hoops_HPAH *			target;

	if ((target = HI_Find_Target_And_Lock(context, key, _hoops_AAGGA)) != null) {
		HI_Edit_Circular_Arc(context, (Circular_Arc *)target, *start, *_hoops_GGSSR, *end);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT start, middle, end;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "start.x = %f;	start.y = %f;  ",start->x, start->y));
		HI_Dump_Code (Sprintf_F (null, "start.z = %f;\n", start->z));
		HI_Dump_Code (Sprintf_FF (null, "middle.x = %f;	 middle.y = %f;	 ", _hoops_GGSSR->x, _hoops_GGSSR->y));
		HI_Dump_Code (Sprintf_F (null, "middle.z = %f;\n", _hoops_GGSSR->z));
		HI_Dump_Code (Sprintf_FF (null, "end.x = %f;  end.y = %f;  ", end->x, end->y));
		HI_Dump_Code (Sprintf_F (null, "end.z = %f;\n", end->z));
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Circular_Arc (LOOKUP (%D), ", key));
		HI_Dump_Code ("&start, &middle, &end);}\n");
		--HOOPS_WORLD->_hoops_ISPPR;
	);
}



HC_INTERFACE void HC_CDECL HC_Edit_Circular_Chord (
	Key					key,
	Point const *		start,
	Point const *		_hoops_GGSSR,
	Point const *		end)
{
	_hoops_PAPPR context("Edit_Circular_Chord");

	if (!start || !_hoops_GGSSR || !end) {
		HE_ERROR (HEC_CIRCULAR_CHORD, HES_INVALID_INPUT, "All points must be provided.");
		return;
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT start, middle, end;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "start.x = %f;	start.y = %f;  ",start->x, start->y));
		HI_Dump_Code (Sprintf_F (null, "start.z = %f;\n", start->z));
		HI_Dump_Code (Sprintf_FF (null, "middle.x = %f;	 middle.y = %f;	 ",_hoops_GGSSR->x, _hoops_GGSSR->y));
		HI_Dump_Code (Sprintf_F (null, "middle.z = %f;\n", _hoops_GGSSR->z));
		HI_Dump_Code (Sprintf_FF (null, "end.x = %f;  end.y = %f;  ",end->x, end->y));
		HI_Dump_Code (Sprintf_F (null, "end.z = %f;\n", end->z));
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Circular_Chord (LOOKUP (%D), ", key));
		HI_Dump_Code ("&start, &middle, &end);}\n");
		--HOOPS_WORLD->_hoops_ISPPR;
	);


	_hoops_CRCP *owner;
	_hoops_RPPPR();
	Circular_Arc *c = (Circular_Arc *)_hoops_RCSSR (context, key);
	if (c == null || c->type != _hoops_GRCP ||
		BIT (c->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid circular chord");
			goto Release;
	}

	if (BIT(c->_hoops_RRHH, _hoops_RGGGA)) {
		HE_ERROR2 (HEC_CIRCLE, HES_INVALID_COORDINATE_SPACE,
			"Circular chords with colinear points cannot be edited.",
			"Please delete and reinsert instead.");
	}
	if (BIT(c->_hoops_RRHH, _hoops_SHHI)) {
		Circular_Arc_Lite *_hoops_RISSR = (Circular_Arc_Lite *)c;
		bool _hoops_AGSSR;
		_hoops_ARPA plane;
		Vector _hoops_GGHI, _hoops_RGHI;
		Point center;
		float length;

		_hoops_AGSSR = (start->z == 0.0f && _hoops_GGSSR->z == 0.0f && end->z == 0.0f);
		if (!_hoops_AGSSR) {
			HE_ERROR2 (HEC_CIRCLE, HES_INVALID_COORDINATE_SPACE,
				"Edit_Circular_Chord cannot change a circular chord from flat (all z==0) to non-flat.",
				"Please delete and reinsert instead.");
			goto Release;
		}
		if (!HI_Compute_Three_Point_Circle (*start, *_hoops_GGSSR, *end,
			&center, &_hoops_RISSR->radius,
			&plane, &_hoops_GGHI, &_hoops_RGHI)) {
				HE_ERROR (HEC_CIRCLE, HES_COLINEAR_POINTS, "The three definition points are colinear");
				goto Release;
		}
		_hoops_RISSR->center.x = center.x;
		_hoops_RISSR->center.y = center.y;
		length = _hoops_HCSSR (*start, *_hoops_GGSSR, *end, center, _hoops_RISSR->radius);
		/* _hoops_SR _hoops_RRP _hoops_HSPP _hoops_CSCHR _hoops_IS _hoops_IRGGA, _hoops_HAR 0 _hoops_CSCHR _hoops_IS _hoops_CRGGA */
		_hoops_RISSR->arc_start = _hoops_AGGGA (_hoops_GGHI.y, _hoops_GGHI.x) / 360.0f;
		if (_hoops_RISSR->arc_start < 0.0f)
			_hoops_RISSR->arc_start += 1.0f;
		/* _hoops_PPR _hoops_SICR _hoops_IS _hoops_SRGGA _hoops_RPP _hoops_SIGR */
		if (_hoops_GGHI.x * _hoops_RGHI.y -
			_hoops_GGHI.y * _hoops_RGHI.x < 0.0f)
			_hoops_RISSR->arc_start -= length;
		_hoops_RISSR->_hoops_PHHI = _hoops_RISSR->arc_start + length;
	}
	else {
		if (!HI_Compute_Three_Point_Circle (*start, *_hoops_GGSSR, *end,
				&c->center, &c->radius, &c->plane, &c->_hoops_GGHI, &c->_hoops_RGHI)) {
				HE_ERROR (HEC_CIRCLE, HES_COLINEAR_POINTS, "The three definition points are colinear");
				goto Release;
		}
		c->start = *start;
		c->_hoops_GGSSR = *_hoops_GGSSR;
		c->end = *end;
		c->arc_start = 0.0f;
		c->_hoops_PHHI = _hoops_HCSSR (*start, *_hoops_GGSSR, *end, c->center, c->radius);
	}
	c->_hoops_CPGPR = _hoops_HHSSR;
	owner = c->owner;
	if (owner != null) {
		_hoops_SASIR (context, owner, _hoops_AISSR|_hoops_PISSR |
			_hoops_HISSR|_hoops_IISSR|_hoops_RPSIR);
	}

	if (owner)
		HI_Antiquate_Bounding (owner, true);

Release:
	_hoops_IRRPR();
}

GLOBAL_FUNCTION void HI_Edit_Circular_Wedge (
	_hoops_AIGPR *	_hoops_RIGC,
	Circular_Arc *			c,
	Point					start,
	Point					_hoops_GGSSR,
	Point					end)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_CRCP *owner;

	if (BIT(c->_hoops_RRHH, _hoops_RGGGA)) {
		HE_ERROR2 (HEC_CIRCLE, HES_INVALID_COORDINATE_SPACE,
			"Circular wedges with colinear points cannot be edited.",
			"Please delete and reinsert instead.");
	}
	if (BIT(c->_hoops_RRHH, _hoops_SHHI)) {
		Circular_Arc_Lite *_hoops_RISSR = (Circular_Arc_Lite *)c;
		bool _hoops_AGSSR;
		_hoops_ARPA plane;
		Vector _hoops_GGHI, _hoops_RGHI;
		Point center;
		float length;

		_hoops_AGSSR = (start.z == 0.0f && _hoops_GGSSR.z == 0.0f && end.z == 0.0f);
		if (!_hoops_AGSSR) {
			HE_ERROR2 (HEC_CIRCLE, HES_INVALID_COORDINATE_SPACE,
				"Edit_Circular_Wedge cannot change a circular wedge from flat (all z==0) to non-flat.",
				"Please delete and reinsert instead.");
			return;
		}
		if (!HI_Compute_Three_Point_Circle (start, _hoops_GGSSR, end,
			&center, &_hoops_RISSR->radius, &plane, &_hoops_GGHI, &_hoops_RGHI)) {
				HE_ERROR (HEC_CIRCLE, HES_COLINEAR_POINTS, "The three definition points are colinear");
				return;
		}
		_hoops_RISSR->center.x = center.x;
		_hoops_RISSR->center.y = center.y;
		length = _hoops_HCSSR (start, _hoops_GGSSR, end, center, _hoops_RISSR->radius);
		/* _hoops_SR _hoops_RRP _hoops_HSPP _hoops_CSCHR _hoops_IS _hoops_IRGGA, _hoops_HAR 0 _hoops_CSCHR _hoops_IS _hoops_CRGGA */
		_hoops_RISSR->arc_start = _hoops_AGGGA (_hoops_GGHI.y, _hoops_GGHI.x) / 360.0f;
		if (_hoops_RISSR->arc_start < 0.0f)
			_hoops_RISSR->arc_start += 1.0f;
		/* _hoops_PPR _hoops_SICR _hoops_IS _hoops_SRGGA _hoops_RPP _hoops_SIGR */
		if (_hoops_GGHI.x * _hoops_RGHI.y -
			_hoops_GGHI.y * _hoops_RGHI.x < 0.0f)
			_hoops_RISSR->arc_start -= length;
		_hoops_RISSR->_hoops_PHHI = _hoops_RISSR->arc_start + length;
	}
	else {
		if (!HI_Compute_Three_Point_Circle (start, _hoops_GGSSR, end,
			&c->center, &c->radius, &c->plane, &c->_hoops_GGHI, &c->_hoops_RGHI)) {
				HE_ERROR (HEC_CIRCLE, HES_COLINEAR_POINTS, "The three definition points are colinear");
				return;
		}
		c->start = start;
		c->_hoops_GGSSR = _hoops_GGSSR;
		c->end = end;
		c->arc_start = 0.0f;
		c->_hoops_PHHI = _hoops_HCSSR (start, _hoops_GGSSR, end, c->center, c->radius);
	}
	c->_hoops_CPGPR = _hoops_HHSSR;
	owner = c->owner;
	if (owner != null) {
		_hoops_SASIR (_hoops_RIGC, owner, _hoops_AISSR|_hoops_PISSR|
			_hoops_HISSR|_hoops_IISSR|_hoops_RPSIR);
	}

	if (owner)
		HI_Antiquate_Bounding (owner, true);
}

HC_INTERFACE void HC_CDECL HC_Edit_Circular_Wedge (
	Key					key,
	Point const *		start,
	Point const *		_hoops_GGSSR,
	Point const *		end)
{
	_hoops_PAPPR context("Edit_Circular_Wedge");

	if (!start || !_hoops_GGSSR || !end) {
		HE_ERROR (HEC_CIRCULAR_WEDGE, HES_INVALID_INPUT, "All points must be provided.");
		return;
	}

	_hoops_HPAH *			target;

	if ((target = HI_Find_Target_And_Lock(context, key, _hoops_PAGGA)) != null) {
		HI_Edit_Circular_Wedge(context, (Circular_Arc *)target, *start, *_hoops_GGSSR, *end);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT start, middle, end;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "start.x = %f;	start.y = %f;  ",start->x, start->y));
		HI_Dump_Code (Sprintf_F (null, "start.z = %f;\n", start->z));
		HI_Dump_Code (Sprintf_FF (null, "middle.x = %f;	 middle.y = %f;	 ",_hoops_GGSSR->x, _hoops_GGSSR->y));
		HI_Dump_Code (Sprintf_F (null, "middle.z = %f;\n", _hoops_GGSSR->z));
		HI_Dump_Code (Sprintf_FF (null, "end.x = %f;  end.y = %f;  ",end->x, end->y));
		HI_Dump_Code (Sprintf_F (null, "end.z = %f;\n", end->z));
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Circular_Wedge (LOOKUP (%D), ", key));
		HI_Dump_Code ("&start, &middle, &end);}\n");
		--HOOPS_WORLD->_hoops_ISPPR;
	);
}


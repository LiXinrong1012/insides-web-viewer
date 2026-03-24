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
 * $Id: obf_tmp.txt 1.89 2010-10-06 19:16:43 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_SSCAH {
	Point const *		center,
				*		major,
				*		minor;
	float				start,
						end;
	Elliptical_Arc *	arc;
	int					_hoops_IGSSR;
};


local void _hoops_GGSAH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_SSCAH *		data) 
{
	Elliptical_Arc *		arc;
	ZALLOC (arc, Elliptical_Arc);

	arc->type = _hoops_GIIP;
	arc->_hoops_CPGPR = _hoops_PHSSR;

	/* _hoops_IPS _hoops_IAPR _hoops_RH _hoops_IPSP'_hoops_GRI _hoops_PIH */
	arc->center = *data->center;
	arc->major = *data->major;
	arc->minor = *data->minor;

	arc->arc_start = data->start;
	arc->_hoops_PHHI = data->end;

	/* _hoops_SRSGR _hoops_SRS _hoops_HARGR _hoops_AAGA */
	arc->_hoops_GGHI = arc->major - arc->center;

	/* _hoops_SRSGR _hoops_GIAP _hoops_HARGR _hoops_AAGA */
	arc->_hoops_RGHI = arc->minor - arc->center;

	/* _hoops_SGH _hoops_SHHP _hoops_HPAHR _hoops_IS _hoops_CGIC _hoops_IPPA _hoops_CGSSR */
	arc->plane = _hoops_ARPA(arc->_hoops_GGHI._hoops_SAIAR(arc->_hoops_RGHI), arc->center);

	if (Vector(arc->plane._hoops_AAIAR())._hoops_PPSSR() < 1.0e-20f) {
		HE_ERROR (HEC_ELLIPTICAL_ARC, HES_COLINEAR_POINTS, "The three definition points are colinear");
		FREE (arc, Elliptical_Arc);
		data->arc = (Elliptical_Arc *) null;
		return;
	}

	HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) arc,
						arc->center.z == 0.0f && arc->major.z == 0.0f && arc->minor.z == 0.0f,
						_hoops_IHSSR);

	data->arc = arc;
	++data->_hoops_IGSSR;
}


GLOBAL_FUNCTION Key HI_Insert_Elliptical_Arc (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					item,
	Point const *				center,
	Point const *				major,
	Point const *				minor,
	float						start,
	float						end) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_SSCAH				data;
	ZERO_STRUCT(&data, _hoops_SSCAH);
	data.center = center;
	data.major = major;
	data.minor = minor;
	data.start = start;
	data.end = end;

	_hoops_GGSAH (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.arc);

	return _hoops_CHSSR;
}



HC_INTERFACE Key HC_CDECL HC_Insert_Elliptical_Arc (
	Point const *			center,
	Point const *			major,
	Point const *			minor,
	double					start,
	double					end) 
{
	_hoops_PAPPR context("Insert_Elliptical_Arc");

	if (!center || !major || !minor) {
		HE_ERROR (HEC_ELLIPTICAL_ARC, HES_INVALID_INPUT, "All points must be provided.");
		return _hoops_SHSSR;
	}

	if (start < 0.0f || start > 1.0f || end < 0.0f || end > 1.0f) {
		HE_ERROR2 (HEC_ELLIPTICAL_ARC, HES_BAD_LENGTH,
				"Unreasonable arc lengths ---", "start and end should be between 0 and 1 (inclusive)");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Elliptical_Arc (context, target, center, major, minor, (float)start, (float)end);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT center, major, minor;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "center.x = %f;	 center.y = %f;	 ", center->x, center->y));
		HI_Dump_Code (Sprintf_F (null, "center.z = %f;\n", center->z));
		HI_Dump_Code (Sprintf_FF (null, "major.x = %f;	major.y = %f;  ", major->x, major->y));
		HI_Dump_Code (Sprintf_F (null, "major.z = %f;\n", major->z));
		HI_Dump_Code (Sprintf_FF (null, "minor.x = %f;	minor.y = %f;  ", minor->x, minor->y));
		HI_Dump_Code (Sprintf_F (null, "minor.z = %f;\n", minor->z));
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_Insert_Elliptical_Arc (&center, &major, &minor, %F, %F), ", start, end));
		HI_Dump_Code (Sprintf_LD (null, "%D);}\n", _hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}


HC_INTERFACE void HC_CDECL HC_Show_Elliptical_Arc (
	Key				key,
	Point *			center,
	Point *			major,
	Point *			minor,
	float *			start,
	float *			end) 
{
	_hoops_PAPPR context("Show_Elliptical_Arc");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Elliptical_Arc () */\n");
	);

	_hoops_CSPPR();
	Elliptical_Arc *	arc = (Elliptical_Arc *)_hoops_RCSSR (context, key);

	if (arc == null ||
		arc->type != _hoops_GIIP ||
		BIT (arc->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_ELLIPTICAL_ARC, HES_INVALID_KEY, "Provided key does not refer to a valid elliptical arc");
	}
	else {
		if (center != null)
			*center = arc->center;

		if (major != null)
			*major = arc->major;

		if (minor != null)
			*minor = arc->minor;

		if (start != null)
			*start = arc->arc_start;

		if (end != null)
			*end = arc->_hoops_PHHI;
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Edit_Elliptical_Arc (
	Key							key,
	Point const *				center,
	Point const *				major,
	Point const *				minor,
	double						start,
	double						end) 
{
	_hoops_PAPPR context("Edit_Elliptical_Arc");

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT center, major, minor;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "center.x = %f;	 center.y = %f;	 ", center->x, center->y));
		HI_Dump_Code (Sprintf_F (null, "center.z = %f;\n", center->z));
		HI_Dump_Code (Sprintf_FF (null, "major.x = %f;	major.y = %f;  ", major->x, major->y));
		HI_Dump_Code (Sprintf_F (null, "major.z = %f;\n", major->z));
		HI_Dump_Code (Sprintf_FF (null, "minor.x = %f;	minor.y = %f;  ", minor->x, minor->y));
		HI_Dump_Code (Sprintf_F (null, "minor.z = %f;\n", minor->z));
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Elliptical_Arc (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "&center, &major, &minor, %F, %F);}\n", start, end));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	if (!center || !major || !minor) {
		HE_ERROR (HEC_ELLIPTICAL_ARC, HES_INVALID_INPUT, "All points must be provided.");
		return;
	}

	if (start < 0.0f || start > 1.0f || end < 0.0f || end > 1.0f) {
		HE_ERROR2 (HEC_ELLIPTICAL_ARC, HES_BAD_LENGTH,
			"Unreasonable arc lengths ---", "start and end should be between 0 and 1 (inclusive)");
		return;
	}

	_hoops_CRCP *		owner;

	_hoops_RPPPR();
	Elliptical_Arc * e = (Elliptical_Arc *)_hoops_RCSSR (context, key);
	if (e == null || e->type != _hoops_GIIP ||
		BIT (e->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid elliptical arc");
		goto Release;
	}

	/* _hoops_IPS _hoops_IAPR _hoops_RH _hoops_IPSP'_hoops_GRI _hoops_PIH */
	e->center = *center;
	e->major = *major;
	e->minor = *minor;

	e->arc_start = (float)start;
	e->_hoops_PHHI = (float)end;

	/* _hoops_SRSGR _hoops_SRS _hoops_HARGR _hoops_AAGA */
	e->_hoops_GGHI = e->major - e->center;

	/* _hoops_SRSGR _hoops_GIAP _hoops_HARGR _hoops_AAGA */
	e->_hoops_RGHI = e->minor - e->center;

	/* _hoops_SGH _hoops_SHHP _hoops_HPAHR _hoops_IS _hoops_CGIC _hoops_IPPA _hoops_CGSSR */
	e->plane = _hoops_ARPA(e->_hoops_GGHI._hoops_SAIAR(e->_hoops_RGHI), e->center);

	if (Vector(e->plane._hoops_AAIAR())._hoops_PPSSR() < 1.0e-20f) {
		HE_ERROR (HEC_ELLIPTICAL_ARC, HES_COLINEAR_POINTS, "The three definition points are colinear");
		goto Release;
	}

	e->_hoops_CPGPR = _hoops_HHSSR;
	owner = e->owner;
	if (owner != null) {
		_hoops_SASIR (context, owner, 
			_hoops_RAGGA |
			_hoops_PISSR |
			_hoops_RPSIR);
		HI_Invalidate_Segment_Display_Lists(context, owner, _hoops_GIIP, e, 0);
	}

	if (owner)
		HI_Antiquate_Bounding (owner, true);

Release:
	_hoops_IRRPR();
}
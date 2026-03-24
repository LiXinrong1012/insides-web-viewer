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
 * $Id: obf_tmp.txt 1.85 2010-10-06 19:16:36 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_ISCAH {
	Point const		*center,
					*major,
					*minor;
	Ellipse			*ellipse;
	int				_hoops_IGSSR;
};


local void _hoops_CSCAH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_ISCAH *		data) 
{
	Ellipse *	ellipse;
	ZALLOC (ellipse, Ellipse);

	ellipse->type = _hoops_CGCP;
	ellipse->_hoops_CPGPR = _hoops_PHSSR;

	/* _hoops_IPS _hoops_IAPR _hoops_RH _hoops_IPSP'_hoops_GRI _hoops_PIH */
	ellipse->center = *data->center;
	ellipse->major = *data->major;
	ellipse->minor = *data->minor;

	/* _hoops_CSGA _hoops_PGCR _hoops_HARGR _hoops_PSPAR */
	ellipse->_hoops_GGHI = ellipse->major - ellipse->center;
	ellipse->_hoops_RGHI = ellipse->minor - ellipse->center;

	/* _hoops_SGH _hoops_SHHP _hoops_HPAHR _hoops_IS _hoops_CGIC _hoops_IPPA _hoops_CGSSR */
	ellipse->plane = _hoops_ARPA(ellipse->_hoops_GGHI._hoops_SAIAR(ellipse->_hoops_RGHI), ellipse->center);

	if (Vector(ellipse->plane._hoops_AAIAR())._hoops_PPSSR() < 1.0e-20f) {
		HE_ERROR (HEC_ELLIPSE, HES_COLINEAR_POINTS, "The three definition points are colinear");
		FREE (ellipse, Ellipse);
		data->ellipse =	null;
	}

	HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) ellipse,
						ellipse->center.z == 0.0f && ellipse->major.z == 0.0f && ellipse->minor.z == 0.0f,
						_hoops_IHSSR|_hoops_SIGPR);

	data->ellipse = ellipse;
	++data->_hoops_IGSSR;
}

GLOBAL_FUNCTION Key HI_Insert_Ellipse (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					item,
	Point const *				center,
	Point const *				major,
	Point const *				minor) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_ISCAH			data;
	ZERO_STRUCT(&data, _hoops_ISCAH);
	data.center = center;
	data.major = major;
	data.minor = minor;
	
	_hoops_CSCAH (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.ellipse);

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Ellipse (
	Point const *			center,
	Point const *			major,
	Point const *			minor) 
{
	_hoops_PAPPR context("Insert_Ellipse");

	if (!center || !major || !minor) {
		HE_ERROR (HEC_ELLIPSE, HES_INVALID_INPUT, "All points must be provided.");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Ellipse (context, target, center, major, minor);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT center, major, minor;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "center.x = %f;	 center.y = %f;	 ",center->x, center->y));
		HI_Dump_Code (Sprintf_F (null, "center.z = %f;\n", center->z));
		HI_Dump_Code (Sprintf_FF (null, "major.x = %f;	major.y = %f;  ", major->x, major->y));
		HI_Dump_Code (Sprintf_F (null, "major.z = %f;\n", major->z));
		HI_Dump_Code (Sprintf_FF (null, "minor.x = %f;	minor.y = %f;  ",minor->x, minor->y));
		HI_Dump_Code (Sprintf_F (null, "minor.z = %f;\n", minor->z));
		HI_Dump_Code (Sprintf_LD (null, "DEFINE (HC_Insert_Ellipse (&center, &major, &minor), %D);}\n",_hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}


HC_INTERFACE void HC_CDECL HC_Show_Ellipse (
	Key				key,
	Point *			center,
	Point *			major,
	Point *			minor) 
{
	_hoops_PAPPR context("Show_Ellipse");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Ellipse () */\n");
	);

	_hoops_CSPPR();

	Ellipse *		ellipse = (Ellipse *)_hoops_RCSSR (context, key);

	if (ellipse == null ||
		ellipse->type != _hoops_CGCP ||
		BIT (ellipse->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_ELLIPSE, HES_INVALID_KEY, "Provided key does not refer to a valid ellipse");
	}
	else {
		if (center != null)
			*center = ellipse->center;

		if (major != null) 
			*major = ellipse->major;

		if (minor != null)
			*minor = ellipse->minor;
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Edit_Ellipse (
	Key						key,
	Point const *			center,
	Point const *			major,
	Point const *			minor) 
{
	_hoops_PAPPR context("Edit_Ellipse");

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT center, major, minor;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "center.x = %f;	 center.y = %f;	 ",center->x, center->y));
		HI_Dump_Code (Sprintf_F (null, "center.z = %f;\n", center->z));
		HI_Dump_Code (Sprintf_FF (null, "major.x = %f;	major.y = %f;  ", major->x, major->y));
		HI_Dump_Code (Sprintf_F (null, "major.z = %f;\n", major->z));
		HI_Dump_Code (Sprintf_FF (null, "minor.x = %f;	minor.y = %f;  ", minor->x, minor->y));
		HI_Dump_Code (Sprintf_F (null, "minor.z = %f;\n", minor->z));
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Ellipse (LOOKUP (%D), ", key));
		HI_Dump_Code ("&center, &major, &minor);}\n");
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_CRCP *					owner;
	_hoops_RPPPR();
	Ellipse * e = (Ellipse *)_hoops_RCSSR (context, key);
	if (e == null || e->type != _hoops_CGCP ||
		BIT (e->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid ellipse");
			goto Release;
	}
	/* _hoops_IPS _hoops_IAPR _hoops_RH _hoops_IPSP'_hoops_GRI _hoops_PIH */
	e->center = *center;
	e->major = *major;
	e->minor = *minor;

	/* _hoops_CSGA _hoops_PGCR _hoops_HARGR _hoops_PSPAR */
	e->_hoops_GGHI = e->major - e->center;
	e->_hoops_RGHI = e->minor - e->center;

	/* _hoops_SGH _hoops_SHHP _hoops_HPAHR _hoops_IS _hoops_CGIC _hoops_IPPA _hoops_CGSSR */
	e->plane = _hoops_ARPA(e->_hoops_GGHI._hoops_SAIAR(e->_hoops_RGHI), e->center);

	if (Vector(e->plane._hoops_AAIAR())._hoops_PPSSR() < 1.0e-20f) {
		HE_ERROR (HEC_ELLIPSE, HES_COLINEAR_POINTS, "The three definition points are colinear");
		goto Release;
	}

	e->_hoops_CPGPR = _hoops_HHSSR;
	owner = e->owner;
	if (owner != null) {
		_hoops_SASIR (context, owner, 
			_hoops_AISSR|_hoops_PISSR|_hoops_HISSR|
			_hoops_IISSR|_hoops_RPSIR);
	}

	if (owner)
		HI_Antiquate_Bounding (owner, true);

Release:
	_hoops_IRRPR();
}
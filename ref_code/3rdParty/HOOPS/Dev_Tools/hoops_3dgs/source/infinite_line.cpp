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
 * $Id: obf_tmp.txt 1.31 2010-07-29 22:00:35 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_PHAPI {
	Point		a;
	Point		b;
	Polyline *	line;
	bool		_hoops_HSSIH;
	int			_hoops_IGSSR;
};


local void _hoops_HHAPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_PHAPI *		data) 
{
	Polyline *	line;
	ZALLOC (line, Polyline);

	line->type = _hoops_SIIP;
	line->_hoops_CPGPR = _hoops_PHSSR;
	line->_hoops_RRHH = data->_hoops_HSSIH ? _hoops_IHHCA : 0;

	line->count = 2;
	line->allocated = 2;
	ALLOC_ARRAY (line->points, line->allocated, Point);
	
	line->points[0] = data->a;
	line->points[1] = data->b;

	HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) line,
						line->points[0].z == 0.0f && line->points[1].z  == 0.0f,
						_hoops_IHSSR);

	data->line = line;
	++data->_hoops_IGSSR;
}


GLOBAL_FUNCTION Key HI_Insert_Infinite_Line (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const &			a,
	Point const &			b,
	bool					_hoops_HSSIH) 
{	
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_PHAPI		data;	
	ZERO_STRUCT(&data, _hoops_PHAPI);
	data.a = a;	
	data.b = b;	
	data._hoops_HSSIH = _hoops_HSSIH;

	_hoops_HHAPI (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.line);

	return _hoops_CHSSR;
}

HC_INTERFACE Key HC_CDECL HC_Insert_Infinite_Line (
	double					xa,
	double					ya,
	double					za,
	double					xb,
	double					yb,
	double					zb) 
{
	_hoops_PAPPR context("Insert_Infinite_Line");

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Infinite_Line (context, target, Point(xa,ya,za), Point(xb,yb,zb), false);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_Insert_Infinite_Line (%F, %F, ", xa, ya));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", za, xb));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F), ", yb, zb));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}

HC_INTERFACE Key HC_CDECL HC_Insert_Infinite_Ray (
	double					xa,
	double					ya,
	double					za,
	double					xb,
	double					yb,
	double					zb) 
{
	_hoops_PAPPR context("Insert_Infinite_Ray");

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Infinite_Line (context, target,  Point(xa,ya,za), Point(xb,yb,zb), true);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_Insert_Infinite_Ray (%F, %F, ", xa, ya));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", za, xb));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F), ", yb, zb));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}


HC_INTERFACE void HC_CDECL HC_Show_Infinite_Line (
	Key					key,
	float *				xa,
	float *				ya,
	float *				za,
	float *				xb,
	float *				yb,
	float *				zb) 
{
	_hoops_PAPPR context("Show_Infinite_Line");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Infinite_Line () */\n");
	);

	Point *	points;

	_hoops_CSPPR();

	Polyline *	line = (Polyline *)_hoops_RCSSR (context, key);

	if (line == null ||
		line->type != _hoops_SIIP ||
		BIT (line->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_KEY,
				"Provided key does not refer to a valid infinite line");
	}
	else {
		points = line->points;
		*xa = points->x;
		*ya = points->y;
		*za = points->z;

		points++;
		*xb = points->x;
		*yb = points->y;
		*zb = points->z;
	}

	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Infinite_Ray (
	Key					key,
	float *				xa,
	float *				ya,
	float *				za,
	float *				xb,
	float *				yb,
	float *				zb) 
{
	_hoops_PAPPR context("Show_Infinite_Ray");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Infinite_Ray () */\n");
	);

	Point *		points;

	_hoops_CSPPR();
	Polyline *	line = (Polyline *)_hoops_RCSSR (context, key);

	if (line == null ||
		line->type != _hoops_SIIP ||
		(line->type == _hoops_SIIP && !BIT(line->_hoops_RRHH, _hoops_IHHCA)) ||
		BIT (line->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_KEY, "Provided key does not refer to a valid infinite ray");
	}
	else {
		points = line->points;
		*xa = points->x;
		*ya = points->y;
		*za = points->z;

		points++;
		*xb = points->x;
		*yb = points->y;
		*zb = points->z;
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Edit_Infinite_Line (
	Key						key,
	double					xa,
	double					ya,
	double					za,
	double					xb,
	double					yb,
	double					zb) 
{
	_hoops_PAPPR context("Edit_Infinite_Line");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Infinite_Line (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", xa, ya));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", za, xb));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", yb, zb));
	);


	_hoops_CRCP *				owner;

	_hoops_RPPPR();
	Polyline *	l = (Polyline *)_hoops_RCSSR (context, key);
	if (l == null || l->type != _hoops_SIIP ||
		BIT (l->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid infinite line");
			goto Release;
	}
	l->points[0].x = (float)xa;
	l->points[0].y = (float)ya;
	l->points[0].z = (float)za;
	l->points[1].x = (float)xb;
	l->points[1].y = (float)yb;
	l->points[1].z = (float)zb;
	l->_hoops_CPGPR |= _hoops_HHSSR;
	owner = l->owner;
	if (owner != null) {
		_hoops_SASIR (context, owner, 
			_hoops_RAGGA |
			_hoops_PISSR |
			_hoops_RPSIR);
		HI_Invalidate_Segment_Display_Lists(context, owner, _hoops_SIIP, l, 0);
	}
Release:
	_hoops_IRRPR();
}


HC_INTERFACE void HC_CDECL HC_Edit_Infinite_Ray (
	Key						key,
	double					xa,
	double					ya,
	double					za,
	double					xb,
	double					yb,
	double					zb) 
{
	_hoops_PAPPR context("Edit_Infinite_Ray");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Infinite_Ray (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", xa, ya));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", za, xb));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", yb, zb));
	);

	_hoops_CRCP *	owner;

	_hoops_RPPPR();
	Polyline *	l = (Polyline *)_hoops_RCSSR (context, key);
	if (l == null || l->type != _hoops_SIIP || (l->type == _hoops_SIIP && !BIT(l->_hoops_RRHH, _hoops_IHHCA)) ||
		BIT (l->_hoops_RRHH, _hoops_HGAGR)) {
			HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid infinite ray");
			goto Release;
	}
	l->points[0].x = (float)xa;
	l->points[0].y = (float)ya;
	l->points[0].z = (float)za;
	l->points[1].x = (float)xb;
	l->points[1].y = (float)yb;
	l->points[1].z = (float)zb;
	l->_hoops_CPGPR |= _hoops_HHSSR;
	owner = l->owner;
	if (owner != null) {
		_hoops_SASIR (context, owner, 
			_hoops_RAGGA |
			_hoops_PISSR |
			_hoops_RPSIR);
		HI_Invalidate_Segment_Display_Lists(context, owner, _hoops_SIIP, l, 0);
	}
Release:
	_hoops_IRRPR();
}
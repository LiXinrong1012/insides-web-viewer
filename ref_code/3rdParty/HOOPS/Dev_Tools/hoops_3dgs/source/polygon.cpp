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
 * $Id: obf_tmp.txt 1.85 2010-10-06 19:16:43 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_IHRSC {
	int					count;
	Point const *		points;

	Polygon *			polygon;
	int					_hoops_IGSSR;
};


local void _hoops_CHRSC (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_IHRSC *		data) 
{
	Point *					points;
	Point const *			upoints = data->points;
	int						count = data->count;

	if (count > 1 &&
		upoints[0].x == upoints[count-1].x &&
		upoints[0].y == upoints[count-1].y &&
		upoints[0].z == upoints[count-1].z) --count;

	Polygon *	polygon;
	ZALLOC (polygon, Polygon);
	polygon->type = _hoops_RCIP;
	polygon->_hoops_CPGPR = _hoops_PHSSR;

	polygon->count = count;
	polygon->allocated = count;

	if (polygon->count == 0)
		polygon->_hoops_CPGPR = _hoops_HCHPA;

	if (count == 0) 
		polygon->points = null;
	else {
		ALLOC_ARRAY (points, count, Point);
		polygon->points = points;
		do {
			points->x = upoints->x;
			points->y = upoints->y;
			points->z = upoints->z;
			++upoints;
			++points;
		}
		_hoops_RGGA (--count <= 0);

		points = polygon->points;
		count = polygon->count;
		do if (points->z != 0.0f) 
			break;
		   else ++points;
		_hoops_RGGA (--count == 0);

	}

	HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) polygon,
						(count == 0), polygon->count > 0 ?
							_hoops_IHSSR|_hoops_SIGPR :
							_hoops_CCHPA);

	data->polygon = polygon;
	++data->_hoops_IGSSR;
}



GLOBAL_FUNCTION Key HI_Insert_Polygon (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						count,
	Point const	*			points) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_IHRSC		data;
	ZERO_STRUCT(&data, _hoops_IHRSC);
	data.count = count;
	data.points = points;

	_hoops_CHRSC (_hoops_RIGC, item, &data);

	Key _hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.polygon);

	return _hoops_CHSSR;
}



HC_INTERFACE Key HC_CDECL HC_Insert_Polygon (
	int					count,
	Point const	*		points) 
{
	_hoops_PAPPR context("Insert_Polygon");

	if (count < 0) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_COUNT, "Negative number of points given to Insert_Polygon");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Polygon (context, target, count, points);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code (Sprintf_D (null, "{HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", count));
		++HOOPS_WORLD->_hoops_ISPPR;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", count2, points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", count2, points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n",count2, points[count2].z));
		}
		HI_Dump_Code (Sprintf_D (null, "DEFINE (HC_Insert_Polygon (%d, points), ", count));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (points);}\n");
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}



HC_INTERFACE void HC_CDECL HC_Show_Partial_Polygon (
	Key			key,
	int			offset,
	int			count,
	Point *		list) 
{
	_hoops_PAPPR context("Show_Partial_Polygon");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Partial_Polygon () */\n");
	);

	if (offset < 0) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_OFFSET, "Provided offset is invalid (less than zero)");
		return;
	}
	if (count < 0) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_RANGE, "Provided range is invalid (less than zero points requested)");
		return;
	}

	_hoops_CSPPR();

	Polygon *	_hoops_HARIR = (Polygon *)_hoops_RCSSR (context, key);

	if (_hoops_HARIR == null ||
		_hoops_HARIR->type != _hoops_RCIP ||
		BIT (_hoops_HARIR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_KEY, "Provided key does not refer to a valid polygon");
	}
	else if (offset >= _hoops_HARIR->count) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_OFFSET, "Provided offset exceeds number of vertices in polygon");
	}
	else if (offset + count > _hoops_HARIR->count) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_RANGE, "Provided range extends past last vertex of polygon");
	}
	else {
		if (list != null)
			_hoops_AIGA (_hoops_HARIR->points + offset, count, Point, list);
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Polygon (
	Key			key,
	int *		ucount,
	Point *		list) 
{
	_hoops_PAPPR context("Show_Polygon");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Polygon () */\n");
	);

	_hoops_CSPPR();

	Polygon *	_hoops_HARIR = (Polygon *)_hoops_RCSSR (context, key);

	if (_hoops_HARIR == null ||
		_hoops_HARIR->type != _hoops_RCIP ||
		BIT (_hoops_HARIR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_KEY, "Provided key does not refer to a valid polygon");
	}
	else {
		if (ucount != null)
			*ucount = _hoops_HARIR->count;
		if (list != null)
			_hoops_AIGA (_hoops_HARIR->points, _hoops_HARIR->count, Point, list);
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Polygon_Count (
	Key			key,
	int *		count) 
{
	_hoops_PAPPR context("Show_Polygon_Count");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Polygon_Count () */\n");
	);

	_hoops_CSPPR();

	Polygon	*	_hoops_HARIR = (Polygon *)_hoops_RCSSR (context, key);

	if (_hoops_HARIR == null || _hoops_HARIR->type != _hoops_RCIP || BIT (_hoops_HARIR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_KEY, "Provided key does not refer to a valid polygon");
	}
	else {
		*count = _hoops_HARIR->count;
	}

	_hoops_IRRPR();
#endif
}




HC_INTERFACE void HC_CDECL HC_Edit_Polygon (
	Key					key,
	int					ioffset,
	int					ndelete,
	int					insert,
	Point const *		_hoops_CGICP) 
{
	_hoops_PAPPR context("Edit_Polygon");

#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		int		count2 = insert;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT * points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", count2, _hoops_CGICP[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", count2, _hoops_CGICP[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n", count2, _hoops_CGICP[count2].z));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Polygon (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", ioffset, ndelete));
		HI_Dump_Code (Sprintf_D (null, "%d, points);\n", insert));
		HI_Dump_Code ("free (points);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	Point *				points;
	int					tmp;
	Point const *		upoints = _hoops_CGICP;
	int					count;
	int					offset = ioffset;
	local const char	_hoops_SHRSC[] = "Offset '%d' not valid (polygon currently has %d vertices)";

	_hoops_RPPPR();

	Polygon *	polygon = (Polygon *)_hoops_RCSSR (context, key);

	if (polygon == null ||
		polygon->type != _hoops_RCIP ||
		BIT (polygon->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_KEY, "Key does not refer to a valid Polygon");
		goto Release;
	}

	if (offset == -1) 
		offset = polygon->count - ndelete;

	if (offset < 0 || offset > polygon->count) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_OFFSET, Sprintf_DD (null, _hoops_SHRSC, offset, polygon->count));
		goto Release;
	}

	if (insert == 0 && ndelete == 0) 
		goto Release;		/* _hoops_RPAPR */

	if (ndelete < 0) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_DELETE_COUNT, Sprintf_D (null, "'%d' is not a good number of points to delete", ndelete));
		goto Release;
	}
	else if (ndelete > polygon->count - offset) {
		if (ioffset == -1)
			HE_ERROR (HEC_POLYGON, HES_INVALID_DELETE_COUNT, "Can't delete points after the end of the polygon (offset is -1)");
		else
			HE_ERROR (HEC_POLYGON, HES_INVALID_DELETE_COUNT,
					Sprintf_DD (null, "Delete count '%d' not valid (polygon currently has %d vertices)", ndelete, polygon->count));
		goto Release;
	}

	if (insert < 0) {
		HE_ERROR (HEC_POLYGON, HES_INVALID_INSERT_COUNT, Sprintf_D (null, "'%d' is not a good number of points to insert", insert));
		goto Release;
	}

	/* _hoops_HCR _hoops_GPRS */

	if (BIT (polygon->_hoops_RRHH, _hoops_ARHH)) {
		if (BIT (polygon->_hoops_RRHH, _hoops_IASGP)) {
			// _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_IRS _hoops_GSSR, _hoops_PSCR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_PISSA _hoops_RSSA _hoops_SR _hoops_HS _hoops_IS _hoops_ASAR-_hoops_RPGP. 
			// _hoops_GIRSC _hoops_RSSA _hoops_RIRSC _hoops_GA'_hoops_RA _hoops_AGRP _hoops_IRS _hoops_APIP _hoops_APRS _hoops_GSSR.
			if (ndelete > 0) 
				polygon->_hoops_RRHH &= ~(_hoops_ARHH|_hoops_IASGP);
		}
		else {
			// _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_PSP _hoops_GSSR, _hoops_HIH _hoops_SR'_hoops_ASAR _hoops_CPRAA _hoops_RSSA, _hoops_PSCR _hoops_SCH'_hoops_GRI _hoops_GHCAR _hoops_HHCPR _hoops_IH _hoops_SCH _hoops_GICS.
			if (insert > 0) 
				polygon->_hoops_RRHH &= ~_hoops_ARHH;
		}
	}

	points = polygon->points;
	if ((count = polygon->count - ndelete + insert) > polygon->allocated) {
		Point				*_hoops_HSPHA;
		Point				*_hoops_AIRSC = points;
		int					_hoops_PIRSC = polygon->allocated;

		ALLOC_ARRAY (_hoops_HSPHA, count + 4, Point);
		polygon->points = _hoops_HSPHA;
		polygon->allocated = count + 4;

		/* _hoops_GII _hoops_HIRSC _hoops_RSSA _hoops_ARPP "_hoops_SHI" _hoops_IS _hoops_IPS? */
		_hoops_AIGA(points, offset, Point, _hoops_HSPHA);
		_hoops_HSPHA += offset;
		points += offset;

		/* _hoops_CCAH _hoops_RSSA */
		_hoops_AIGA(upoints, insert, Point, _hoops_HSPHA);
		_hoops_HSPHA += insert;

		if (offset + ndelete < polygon->count) {		/* _hoops_RAAP _hoops_HII _hoops_GIGR */
			points += ndelete;							/* _hoops_HSGR _hoops_PGHPR */

			tmp = polygon->count - (offset + ndelete);
			_hoops_AIGA(points, tmp, Point, _hoops_HSPHA);
		}

		if (_hoops_PIRSC > 0) 
			FREE_ARRAY (_hoops_AIRSC, _hoops_PIRSC, Point);
	}
	else {
		points += offset; /* _hoops_HSGR _hoops_SHI _hoops_RSSA */

		if (insert == ndelete) {
			_hoops_AIGA(upoints, insert, Point, points);
		}
		else if (insert < ndelete) {
			int		shift = ndelete - insert;

			_hoops_AIGA(upoints, insert, Point, points);
			points += insert;

			if ((tmp = polygon->count - offset - ndelete) > 0) do {
				points[0] = points[shift];
				++points;
			} _hoops_RGGA (--tmp <= 0);
		}
		else {	/* _hoops_IIRSC */
			int		shift = insert - ndelete;
			Point	*end;

			end = &polygon->points[polygon->count-1];
			if ((tmp = polygon->count - offset - ndelete) > 0) do {
				end[shift] = *end;
				--end;
			} _hoops_RGGA (--tmp <= 0);

			_hoops_AIGA(upoints, insert, Point, points);
		}
	}

	polygon->count = count;

	if (_hoops_CGICP && !BIT (polygon->_hoops_RRHH, _hoops_RSPCR)) {
		upoints = _hoops_CGICP;
		tmp = insert;
		do if (upoints->z != (float)0) break;
		_hoops_RGGA (--tmp == 0);

		if (tmp != 0) {
			polygon->_hoops_RRHH |= _hoops_RSPCR;
			if (polygon->owner && !BIT (polygon->owner->_hoops_RCGC, _hoops_ASPCR))
				HI_Propagate_Maybes (context, polygon->owner, _hoops_ASPCR);
		}
	}

	if (polygon->owner) {
		if (ndelete > 0) {
			HI_Antiquate_Bounding (polygon->owner, true);
		}
		else if (insert > 0) {
			Bounding	bounding = Bounding::Create(insert, _hoops_CGICP);
			HI_Propagate_Bounding (context, polygon->owner, bounding, null);
		}
	}

	polygon->_hoops_CPGPR |= _hoops_HHSSR;

	_hoops_SASIR (context, polygon->owner, _hoops_AISSR|
										  _hoops_PISSR|
										  _hoops_RPSIR);

  Release:
	_hoops_IRRPR();
#endif
}

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
 * $Id: obf_tmp.txt 1.91.2.2 2010-12-17 23:15:55 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_CIRSC {
	int					count;
	Point const *		points;

	Polyline *			polyline;
	int					_hoops_IGSSR;
};



local void _hoops_SIRSC (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_CIRSC *		data) 
{
	Point const *			upoints = data->points;
	Point *					points;
	int						count = data->count;
	bool					_hoops_IGHSA = true;

	Polyline *	polyline;
	ZALLOC (polyline, Polyline);

	polyline->type = _hoops_IIIP;
	polyline->_hoops_CPGPR = _hoops_PHSSR;

	polyline->count = count;
	polyline->allocated = Abs(count);

	if (polyline->count == 0)
		polyline->_hoops_CPGPR = _hoops_HCHPA;

	if (count == 0) 
		polyline->points = null;
	else {
		ALLOC_ARRAY (points, polyline->allocated, Point);
		polyline->points = points;
		count = polyline->allocated;
		do {
			points->x = upoints->x;
			points->y = upoints->y;
			points->z = upoints->z;
			if (points->z != 0.0f)
				_hoops_IGHSA = false;
			++upoints;
			++points;
		}
		_hoops_RGGA (--count <= 0);
	}

	HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) polyline, _hoops_IGHSA,
						polyline->count != 0 ? 
								_hoops_IHSSR : _hoops_CCHPA);

	data->polyline = polyline;
	++data->_hoops_IGSSR;
}


GLOBAL_FUNCTION Key HI_Insert_Polyline (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						count,
	Point const *			points) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_CIRSC		data;

	ZERO_STRUCT(&data, _hoops_CIRSC);
	data.count = count;
	data.points = points;

	_hoops_SIRSC (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.polyline);

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Polyline (
	int						count,
	Point const *			points) 
{
	_hoops_PAPPR context("Insert_Polyline");

	if (count < 0 && (count % 2 != 0)) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_COUNT, "Negative point counts must be even.");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Polyline (context, target, count, points);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		int	   count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", count));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %.6ff;	 ", count2, points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %.6ff;	 ", count2, points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %.6ff;\n", count2, points[count2].z));
		}
		HI_Dump_Code (Sprintf_D (null, "DEFINE (HC_Insert_Polyline (%d, points), ", count));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (points);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CHSSR;
}




HC_INTERFACE void HC_CDECL HC_Show_Partial_Polyline (
	Key				key,
	int				offset,
	int				count,
	Point *			list) 
{
	_hoops_PAPPR context("Show_Partial_Polyline");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Partial_Polyline () */\n");
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

	Polyline *	_hoops_HARIR = (Polyline *)_hoops_RCSSR (context, key);

	if (_hoops_HARIR == null || _hoops_HARIR->type != _hoops_IIIP || BIT (_hoops_HARIR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_KEY, "Provided key does not refer to a valid polyline");
	}
	else if (offset >= Abs(_hoops_HARIR->count)) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_OFFSET, "Provided offset exceeds number of vertices in polyline");
	}
	else if (offset + count > Abs(_hoops_HARIR->count)) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_RANGE, "Provided range extends past last vertex of polyline");
	}
	else {
		if (list != null)
			_hoops_AIGA (_hoops_HARIR->points + offset, count, Point, list);
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Polyline (
	Key				key,
	int *			ucount,
	Point *			list) 
{
	_hoops_PAPPR context("Show_Polyline");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Polyline () */\n");
	);

	_hoops_CSPPR();

	Polyline *	_hoops_HARIR = (Polyline *)_hoops_RCSSR (context, key);

	if (_hoops_HARIR == null ||
		_hoops_HARIR->type != _hoops_IIIP ||
		BIT (_hoops_HARIR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_KEY, "Provided key does not refer to a valid polyline");
	}
	else {
		if (ucount != null)
			*ucount = _hoops_HARIR->count;

		if (list != null)
			_hoops_AIGA (_hoops_HARIR->points, Abs(_hoops_HARIR->count), Point, list);
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Polyline_Count (
	Key				key,
	int *			count) 
{
	_hoops_PAPPR context("Show_Polyline_Count");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Polyline_Count () */\n");
	);

	_hoops_CSPPR();

	Polyline *	_hoops_HARIR = (Polyline *)_hoops_RCSSR (context, key);

	if (_hoops_HARIR == null ||
		_hoops_HARIR->type != _hoops_IIIP ||
		BIT (_hoops_HARIR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_KEY, "Provided key does not refer to a valid polyline");
	}
	else {
		*count = _hoops_HARIR->count;
	}

	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Edit_Polyline (
	Key					key,
	int					ioffset,
	int					ndelete,
	int					insert,
	Point const *		_hoops_CGICP) 
{
	_hoops_PAPPR context("Edit_Polyline");

#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		int		count2 = insert;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", insert));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %.6ff;	 ", count2, _hoops_CGICP[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %.6ff;	 ", count2, _hoops_CGICP[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %.6ff;\n", count2, _hoops_CGICP[count2].z));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Polyline (LOOKUP (%D), ", key));
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
	int					_hoops_CICSA;
	int					offset = ioffset;
	int					_hoops_RRHPH = Abs (insert);
	local const char	_hoops_SHRSC[] = "Offset '%d' not valid (polyline currently has %d vertices)";

	_hoops_RPPPR();

	Polyline *	polyline = (Polyline *)_hoops_RCSSR (context, key);

	if (polyline == null || polyline->type != _hoops_IIIP ||
		BIT (polyline->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_KEY, "Key does not refer to a valid Polyline");
		goto Release;
	}

	_hoops_CICSA = polyline->count;

	if (offset == -1) 
		offset = Abs(polyline->count) - ndelete;

	if (offset < 0 || offset > Abs(polyline->count)) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_OFFSET, Sprintf_DD (null, _hoops_SHRSC, offset, Abs(polyline->count)));
		goto Release;
	}

	if (ndelete < 0) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_DELETE_COUNT,
				Sprintf_D (null, "'%d' is not a good number of points to delete", ndelete));
		goto Release;
	}
	else if (ndelete > Abs(polyline->count) - offset) {
		if (ioffset == -1)
			HE_ERROR (HEC_POLYLINE, HES_INVALID_DELETE_COUNT, "Can't delete points after the end of the polyline (offset is -1)");
		else
			HE_ERROR (HEC_POLYLINE, HES_INVALID_COUNT,
					Sprintf_DD (null, "Delete count '%d' not valid (polyline currently has %d vertices)",
				ndelete, Abs(polyline->count)));
		goto Release;
	}

	if (insert < 0) {
		if (polyline->count > 0 && ndelete != Abs(polyline->count)) {
			HE_ERROR (HEC_POLYLINE, HES_INVALID_INSERT_COUNT, 
					  Sprintf_D (null, "'%d' is not a good number of points to insert", insert));
			goto Release;
		}
		if ((insert - ndelete) % 2 != 0) {
			HE_ERROR (HEC_POLYLINE, HES_INVALID_COUNT, "Negative point counts must be even.");
			goto Release;
		}
	}

	/* _hoops_HPGGR _hoops_RH _hoops_RRRPR'_hoops_GRI _hoops_AIRI _hoops_CPCI (_hoops_RPP _hoops_GII) _hoops_GAR _hoops_AIPH */
	if (polyline->owner != null && 
		polyline->owner->type == _hoops_IRCP)
		HI_Invalidate_Segment_Display_Lists(context, polyline->owner, _hoops_IIIP, polyline, 0);

	/* _hoops_HCR _hoops_GPRS */

	if (insert == 0 && ndelete == 0) 
		goto Release;		/* _hoops_RPAPR */

	ioffset = offset;	/* _hoops_GRHP _hoops_RGR _hoops_PIRA */

	points = polyline->points;
	count = Abs(polyline->count) - ndelete + _hoops_RRHPH;
	if (count > polyline->allocated) {
		Point		*_hoops_HSPHA;
		Point		*_hoops_AIRSC = points;
		int			_hoops_PIRSC = polyline->allocated;

		ALLOC_ARRAY (_hoops_HSPHA, count +32, Point);
		polyline->points = _hoops_HSPHA;
		polyline->allocated = count +32;

		_hoops_AIGA(points, offset, Point, _hoops_HSPHA);
		_hoops_HSPHA += offset;
		points += offset;

		_hoops_AIGA(upoints, _hoops_RRHPH, Point, _hoops_HSPHA);
		_hoops_HSPHA += _hoops_RRHPH;

		if (offset + ndelete < Abs(polyline->count)) {		/* _hoops_RAAP _hoops_HII _hoops_GIGR */
			points += ndelete;

			tmp = Abs(polyline->count) - (offset + ndelete);
			_hoops_AIGA(points, tmp, Point, _hoops_HSPHA);
		}

		if (_hoops_PIRSC > 0)
			FREE_ARRAY (_hoops_AIRSC, _hoops_PIRSC, Point);
	}
	else {
		points += offset; /* _hoops_HSGR _hoops_SHI _hoops_RSSA */

		if (_hoops_RRHPH == ndelete) {
			_hoops_AIGA(upoints, _hoops_RRHPH, Point, points);
		}
		else if (_hoops_RRHPH < ndelete) {
			int		shift = ndelete - _hoops_RRHPH;

			_hoops_AIGA(upoints, _hoops_RRHPH, Point, points);
			points += _hoops_RRHPH;

			if ((tmp = Abs(polyline->count) - offset - ndelete) > 0) do {
				points[0] = points[shift];
				++points;
			} _hoops_RGGA (--tmp <= 0);
		}
		else {	/* _hoops_IIRSC */
			int			shift = _hoops_RRHPH - ndelete;
			Point *		end;

			end = &polyline->points[Abs(polyline->count)-1];
			if ((tmp = Abs(polyline->count) - offset - ndelete) > 0) do {
				end[shift] = *end;
				--end;
			} _hoops_RGGA (--tmp <= 0);

			_hoops_AIGA(upoints, _hoops_RRHPH, Point, points);
		}
	}

	if (polyline->count - ndelete == 0)
		polyline->count = insert;
	else if (polyline->count < 0)
		polyline->count = -count;
	else
		polyline->count = count;

	if (_hoops_CGICP && !BIT (polyline->_hoops_RRHH, _hoops_RSPCR)) {
		upoints = _hoops_CGICP;
		tmp = _hoops_RRHPH;
		do if (upoints->z != (float)0)
			break;
		_hoops_RGGA (--tmp == 0);

		if (tmp != 0) {
			polyline->_hoops_RRHH |= _hoops_RSPCR;
			if (polyline->owner && !BIT (polyline->owner->_hoops_RCGC, _hoops_ASPCR))
				HI_Propagate_Maybes (context, polyline->owner, _hoops_ASPCR);
		}
	}

	if (polyline->owner) {
		if (ndelete > 0) {
			HI_Antiquate_Bounding (polyline->owner, true);
		}
		else if (insert > 0) {
			Bounding	bounding = Bounding::Create(insert, _hoops_CGICP);
			HI_Propagate_Bounding (context, polyline->owner, bounding, null);
		}
	}

	if (!BIT (polyline->_hoops_CPGPR, _hoops_CASIR)) {
		if (!BIT (polyline->_hoops_CPGPR, _hoops_AHSGA))
			polyline->_hoops_CPGPR |= _hoops_HHSSR;

		/* _hoops_AHPIP _hoops_RPP _hoops_PISSA _hoops_PAR _hoops_GCRSC _hoops_RII _hoops_HSAR _hoops_RSGR */
		if (ndelete > 0 ||
			insert > 0 && ioffset != _hoops_CICSA) {
			_hoops_SASIR (context, polyline->owner, _hoops_RAGGA|_hoops_PISSR|_hoops_RPSIR);
		}

		if (insert > 0) {
			polyline->_hoops_CPGPR |= _hoops_GGARA;
			_hoops_SASIR (context, polyline->owner, _hoops_IHSSR|_hoops_PISSR|_hoops_RPSIR);
		}
	}

  Release:
	_hoops_IRRPR();
#endif
}

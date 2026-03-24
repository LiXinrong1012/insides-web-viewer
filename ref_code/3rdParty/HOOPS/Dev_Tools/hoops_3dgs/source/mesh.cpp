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
 * $Id: obf_tmp.txt 1.141 2010-10-06 19:16:43 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_RCHII {
	int					rows,
						columns;
	Point const *		points;
	bool				_hoops_ISSIH;
	bool				_hoops_SHCIH;
	int					_hoops_SPHA,
						face_count,
						point_count;

	_hoops_AIHPR *				_hoops_PIHPR;
	int					_hoops_IGSSR;
};


local void _hoops_ACHII (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_RCHII *			data) 
{
	_hoops_AIHPR *	_hoops_PIHPR;
	ZALLOC (_hoops_PIHPR, _hoops_AIHPR);
	_hoops_PIHPR->type = _hoops_GSIP;
	_hoops_PIHPR->_hoops_CPGPR = _hoops_PHSSR;
	_hoops_PIHPR->rows = data->rows;
	_hoops_PIHPR->columns = data->columns;
	_hoops_PIHPR->point_count = data->point_count;
	_hoops_PIHPR->_hoops_SPHA = data->_hoops_SPHA;
	_hoops_PIHPR->face_count = data->face_count;

	if (data->_hoops_ISSIH) {
		_hoops_PIHPR->polyhedron_flags |= PHF_POINTS_BY_REFERENCE;
		_hoops_PIHPR->points = (Point *)data->points;
	}
	else if (data->point_count > 0) {
		ALLOC_ARRAY_ALIGNED (_hoops_PIHPR->points, data->rows * data->columns, Point, 16);
		_hoops_AIGA (data->points, data->rows * data->columns, Point, _hoops_PIHPR->points);
	}
	else
		_hoops_PIHPR->points = null;

	_hoops_PIHPR->_hoops_CPGPR = _hoops_AHSGA;
	HI_Figure_Geometry_Bounding ((Geometry const *)_hoops_PIHPR, _hoops_PIHPR->bounding);
	_hoops_PIHPR->_hoops_CPGPR = _hoops_PHSSR;

	/* _hoops_PAGA: _hoops_GSRGR _hoops_CRGR _hoops_PCHII 0 _hoops_PAH _hoops_APRI _hoops_RH _hoops_RRCPR _hoops_SR _hoops_GGHP */
	_hoops_PIHPR = (_hoops_AIHPR *) HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) _hoops_PIHPR, data->_hoops_SHCIH,
										   _hoops_IHSSR|_hoops_SIGPR);

	data->_hoops_PIHPR = _hoops_PIHPR;
	++data->_hoops_IGSSR;
}


local bool _hoops_HCHII (
	_hoops_RCHII	*	data) 
{

	/* _hoops_RARIR _hoops_RH _hoops_HSHRR */

	if (data->rows < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_ROW, Sprintf_D (null, "'Rows' is '%d', must be non-negative", data->rows));
		return false;
	}
	if (data->columns < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_COLUMN, Sprintf_D (null, "'Columns' is '%d', must be non-negative", data->columns));
		return false;
	}

	/* _hoops_RH _hoops_HSPR _hoops_HHS _hoops_SHH _hoops_GPICR, _hoops_HIH _hoops_SCH _hoops_GA'_hoops_RA _hoops_RPSHR */
	data->_hoops_SPHA = 3 * data->rows * data->columns;
	data->face_count = 2 * (data->rows - 1) * (data->columns - 1);
	if (data->face_count < 0)
		data->face_count = 0; /* _hoops_PGI _hoops_HAPHR _hoops_PAR _hoops_ICHII _hoops_HRGR _hoops_AHHR */
	data->point_count = data->rows * data->columns;

	data->_hoops_SHCIH = true; /* _hoops_CCGR _hoops_GIPCR _hoops_IAII */

	{
		Point const	*point = data->points;
		Point const	*end = point + data->point_count;

		_hoops_RGGA (point == end) {
			if (point++->z != 0.0f) {
				data->_hoops_SHCIH = false;
				break;
			}
		}
	}

	return true;
}


GLOBAL_FUNCTION Key HI_Insert_Mesh (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						rows,
	int						columns,
	Point const	*			points,
	bool					_hoops_PSSIH) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_RCHII		data;
	ZERO_STRUCT(&data, _hoops_RCHII);
	data.rows = rows;
	data.columns = columns;
	data.points = points;
	data._hoops_ISSIH = _hoops_PSSIH;

	if (!_hoops_HCHII (&data)) {
		return _hoops_SHSSR;
	}

	_hoops_ACHII (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data._hoops_PIHPR);

	return _hoops_CHSSR;
}



HC_INTERFACE Key HC_CDECL HC_Insert_Mesh (
	int					rows,
	int					columns,
	Point const	*		points) 
{
	_hoops_PAPPR context("Insert_Mesh");

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Mesh (context, target, rows, columns, points, false);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		long			size = rows * columns;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_LD (null, "HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%D);\n", size));
		_hoops_RGGA (size-- == 0) {
			HI_Dump_Code (Sprintf_LD (null, "points[%D].x = ", size));
			HI_Dump_Code (Sprintf_F (null, "%f;	 ", points[size].x));
			HI_Dump_Code (Sprintf_LD (null, "points[%D].y = ", size));
			HI_Dump_Code (Sprintf_F (null, "%f;	 ", points[size].y));
			HI_Dump_Code (Sprintf_LD (null, "points[%D].z = ", size));
			HI_Dump_Code (Sprintf_F (null, "%f;\n", points[size].z));
		}
		HI_Dump_Code (Sprintf_DD (null, "DEFINE (HC_Insert_Mesh (%d, %d, points), ", rows, columns));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (points);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CHSSR;
}



HC_INTERFACE Key HC_CDECL HC_Insert_Mesh_By_Ref (
	int				rows,
	int				columns,
	Point const	*	points) 
{
	_hoops_PAPPR context("Insert_Mesh_By_Ref");

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Mesh (context, target, rows, columns, points, true);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		long			size = rows * columns;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_LD (null, "HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%D);\n", size));
		_hoops_RGGA (size-- == 0) {
			HI_Dump_Code (Sprintf_LD (null, "points[%D].x = ", size));
			HI_Dump_Code (Sprintf_F (null, "%f;	 ", points[size].x));
			HI_Dump_Code (Sprintf_LD (null, "points[%D].y = ", size));
			HI_Dump_Code (Sprintf_F (null, "%f;	 ", points[size].y));
			HI_Dump_Code (Sprintf_LD (null, "points[%D].z = ", size));
			HI_Dump_Code (Sprintf_F (null, "%f;\n", points[size].z));
		}
		HI_Dump_Code (Sprintf_DD (null, "DEFINE (HC_Insert_Mesh /* By_Ref */ (%d, %d, points), ", rows, columns));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (points);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CHSSR;
}




HC_INTERFACE void HC_CDECL HC_Show_Mesh (
	Key			key,
	int *		_hoops_CCHII,
	int *		_hoops_SCHII,
	Point *		points) 
{
	_hoops_PAPPR context("Show_Mesh");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Mesh () */\n");
	);

	_hoops_CSPPR();

	_hoops_AIHPR *	_hoops_PIHPR = (_hoops_AIHPR *)_hoops_RCSSR (context, key);

	if (_hoops_PIHPR == null ||
		_hoops_PIHPR->type != _hoops_GSIP ||
		BIT (_hoops_PIHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Provided key does not refer to a valid mesh");
	}
	else {
		if (_hoops_CCHII)
			*_hoops_CCHII = _hoops_PIHPR->rows;
		if (_hoops_SCHII)
			*_hoops_SCHII = _hoops_PIHPR->columns;
		if (points != null)
			_hoops_AIGA (_hoops_PIHPR->points, _hoops_PIHPR->rows * _hoops_PIHPR->columns, Point, points);
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Mesh_Size (
	Key				key,
	int *			_hoops_CCHII,
	int *			_hoops_SCHII) 
{
	_hoops_PAPPR context("Show_Mesh_Size");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Mesh_Size () */\n");
	);

	_hoops_CSPPR();

	_hoops_AIHPR *	_hoops_PIHPR = (_hoops_AIHPR *)_hoops_RCSSR (context, key);

	if (_hoops_PIHPR == null ||
		_hoops_PIHPR->type != _hoops_GSIP ||
		BIT (_hoops_PIHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Provided key does not refer to a valid mesh");
	}
	else {
		*_hoops_CCHII = _hoops_PIHPR->rows;
		*_hoops_SCHII = _hoops_PIHPR->columns;
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Partial_Mesh (
	Key				key,
	int				row_offset,
	int				column_offset,
	int				row_count,
	int				column_count,
	Point *			points) 
{
	_hoops_PAPPR context("Show_Partial_Mesh");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Partial_Mesh () */\n");
	);

	if (row_offset < 0 || column_offset < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_OFFSET, "Offset from the array origin must be non-negative");
		return;
	}
	if (row_count < 0 || column_count < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_COUNT, "row_count or column_count is negative");
		return;
	}
	if (row_count == 0 || column_count == 0) 
		return;

	_hoops_CSPPR();

	_hoops_AIHPR *	_hoops_PIHPR = (_hoops_AIHPR *)_hoops_RCSSR (context, key);

	if (_hoops_PIHPR == null ||
		_hoops_PIHPR->type != _hoops_GSIP ||
		BIT (_hoops_PIHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Key does not refer to a valid mesh");
	}
	else if (row_offset + row_count > _hoops_PIHPR->rows ||
			 column_offset + column_count > _hoops_PIHPR->columns) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_OFFSET, "Region is not entirely within the original array");
	}
	else {
		Point *	_hoops_GSHII = &_hoops_PIHPR->points[row_offset * (long)_hoops_PIHPR->columns + column_offset];

		if (points != null) {
			do {
				_hoops_AIGA (_hoops_GSHII, column_count, Point, points);
				points += column_count;
				_hoops_GSHII += _hoops_PIHPR->columns;
			} while (--row_count > 0);
		}
	}

	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_Edit_Mesh (
	Key				key,
	int				row_offset,
	int				column_offset,
	int				row_count,
	int				column_count,
	Point const *	points)
{
	_hoops_PAPPR context("Edit_Mesh");

#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else
	CODE_GENERATION (
		int		count2 = row_count * column_count;

		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_LD (null, "HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%D);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", count2, points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", count2, points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n", count2, points[count2].z));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Mesh (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", row_offset, column_offset));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, points);\n", row_count, column_count));
		HI_Dump_Code ("free (points);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	int				_hoops_RSHII = row_count;

	_hoops_RPPPR();

	_hoops_AIHPR *	_hoops_PIHPR  = (_hoops_AIHPR *)_hoops_RCSSR (context, key);

	if (_hoops_PIHPR == null || _hoops_PIHPR->type != _hoops_GSIP ||
		BIT (_hoops_PIHPR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_KEY, "Key does not refer to a valid mesh");
		goto Release;
	}

	if (row_count < 0 || column_count < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_COUNT, "row_count or column_count is negative");
		goto Release;
	}

	if (row_offset + row_count > _hoops_PIHPR->rows ||
		column_offset + column_count > _hoops_PIHPR->columns) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_OFFSET, "Replacement is not entirely within the original array");
		goto Release;
	}

	if (row_offset < 0 || column_offset < 0) {
		HE_ERROR (HEC_TRISTRIP, HES_INVALID_OFFSET, "Offset from the array origin must be non-negative");
		goto Release;
	}

	if (row_count == 0 || column_count == 0) goto Release;

	do {
		_hoops_AIGA (points, column_count, Point,
					 &_hoops_PIHPR->points[row_offset * (long)_hoops_PIHPR->columns + column_offset]);
		points += column_count;
		++row_offset;
	} while (--row_count > 0);
	row_count = _hoops_RSHII;

	_hoops_PIHPR->bounding = Bounding::Create(_hoops_PIHPR->point_count, _hoops_PIHPR->points);

	if (_hoops_PIHPR->owner)
		HI_Antiquate_Bounding (_hoops_PIHPR->owner, true);

	if (_hoops_PIHPR->local_vertex_attributes.explicit_normal_count !=
		_hoops_PIHPR->point_count)
		_hoops_PIHPR->polyhedron_flags &= ~PHF_VERTEX_NORMALS_VALID;

	if (_hoops_PIHPR->local_face_attributes.explicit_normal_count !=
		_hoops_PIHPR->face_count)
		_hoops_PIHPR->polyhedron_flags &= ~PHF_FACE_NORMALS_VALID;

	_hoops_PIHPR->_hoops_CPGPR |= _hoops_HHSSR;

    HI_Invalidate_Display_Lists (context, _hoops_PIHPR);
	HI_Invalidate_Segment_Display_Lists(context, _hoops_PIHPR->owner, -2, _hoops_PIHPR, 0);

	_hoops_SASIR (context, _hoops_PIHPR->owner, _hoops_AISSR|
											  _hoops_CSCCA|
											  _hoops_PISSR|
											  _hoops_RPSIR);

  Release:
	_hoops_IRRPR();
#endif
}

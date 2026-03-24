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
 * $Id: obf_tmp.txt 1.95 2010-10-06 19:16:43 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_GPGIH {
	int				_hoops_APIAA;
	Point const		*origin,
					*ref1,
					*ref2;
	int				count1,
					count2;
	int				_hoops_IPIAA;

	Grid *			grid;
	int				_hoops_IGSSR;
};


local void _hoops_RPGIH (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_GPGIH *			data) 
{

	Grid *	grid;

	if (owner != null) {
		ZALLOC (grid, Grid);
		grid->type = _hoops_GGCP;
		grid->_hoops_CPGPR = _hoops_PHSSR;
	}
	else {
		grid = data->grid;
		grid->_hoops_CPGPR = _hoops_HHSSR;
	}

	grid->origin = *data->origin;
	grid->ref1 = *data->ref1;
	grid->ref2 = *data->ref2;
	grid->count1 = data->count1;
	grid->count2 = data->count2;

	grid->_hoops_APIAA = data->_hoops_APIAA;
	grid->_hoops_IPIAA = data->_hoops_IPIAA;

	Vector vector1 = *data->ref1 - *data->origin;
	Vector vector2 = *data->ref2 - *data->origin;

	/* _hoops_SGH _hoops_SHHP _hoops_HPAHR _hoops_IS _hoops_CGIC _hoops_IPPA _hoops_CGSSR */
	grid->plane = _hoops_ARPA(vector1._hoops_SAIAR(vector2), grid->origin);
	grid->plane._hoops_AAIAR();

	if (grid->_hoops_APIAA == _hoops_PPIAA) {
		grid->_hoops_GGHI = vector1;
		grid->_hoops_RGHI = vector2;
	}
	else {
		grid->_hoops_GGHI = vector1;
		grid->_hoops_RGHI.x = vector1.z * grid->plane.b - vector1.y * grid->plane.c;
		grid->_hoops_RGHI.y = vector1.x * grid->plane.c - vector1.z * grid->plane.a;
		grid->_hoops_RGHI.z = vector1.y * grid->plane.a - vector1.x * grid->plane.b;
	}

	if (owner != null) {
		HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) grid,
							grid->origin.z == 0.0f	&& grid->ref1.z == 0.0f	&& grid->ref2.z == 0.0f,
							_hoops_IHSSR|_hoops_SIGPR);

		data->grid = grid;
		++data->_hoops_IGSSR;
	}
}

local int _hoops_APGIH (
	char const		*options) {
	char const		*_hoops_RPPA = options;

	while (*_hoops_RPPA == ' ') _hoops_RPPA++;
	if (_hoops_SHPCR(_hoops_RPPA[0]) == 'r' &&
		_hoops_SHPCR(_hoops_RPPA[1]) == 'a' &&
		_hoops_SHPCR(_hoops_RPPA[2]) == 'd' &&
		_hoops_SHPCR(_hoops_RPPA[3]) == 'i' &&
		_hoops_SHPCR(_hoops_RPPA[4]) == 'a' &&
		_hoops_SHPCR(_hoops_RPPA[5]) == 'l') {
		_hoops_RPPA += 6;
		while (*_hoops_RPPA == ' ') _hoops_RPPA++;
		if (*_hoops_RPPA == '\0') 
			return	 _hoops_SPARP;
	}
	else
	if (_hoops_SHPCR(_hoops_RPPA[0])  == 'q' &&
		_hoops_SHPCR(_hoops_RPPA[1])  == 'u' &&
		_hoops_SHPCR(_hoops_RPPA[2])  == 'a' &&
		_hoops_SHPCR(_hoops_RPPA[3])  == 'd' &&
		_hoops_SHPCR(_hoops_RPPA[4])  == 'r' &&
		_hoops_SHPCR(_hoops_RPPA[5])  == 'i' &&
		_hoops_SHPCR(_hoops_RPPA[6])  == 'l' &&
		_hoops_SHPCR(_hoops_RPPA[7])  == 'a' &&
		_hoops_SHPCR(_hoops_RPPA[8])  == 't' &&
		_hoops_SHPCR(_hoops_RPPA[9])  == 'e' &&
		_hoops_SHPCR(_hoops_RPPA[10]) == 'r' &&
		_hoops_SHPCR(_hoops_RPPA[11]) == 'a' &&
		_hoops_SHPCR(_hoops_RPPA[12]) == 'l') {
		_hoops_RPPA += 13;
		while (*_hoops_RPPA == ' ') _hoops_RPPA++;
		if (*_hoops_RPPA == '\0') 
			return	 _hoops_PPIAA;
	}

	HE_ERROR (HEC_GRID, HES_INVALID_OPTION, Sprintf_S (null, "'%s' is an unknown grid option", options));
	return 0;
}


local int _hoops_PPGIH (
	Point const	*	origin,
	Point const	*	ref1,
	Point const	*	ref2) 
{
	float			_hoops_RAHCR;
	int				_hoops_IPIAA;

	Vector _hoops_GGHI = *ref1 - *origin;
	Vector _hoops_RGHI = *ref2 - *origin;

	if (!HI_Normalize (&_hoops_GGHI) || !HI_Normalize (&_hoops_RGHI)) {
		HE_ERROR (HEC_GRID, HES_BAD_REFERENCE_POINT, "Grid reference point(s) same as origin");
		return 0;
	}

	if (_hoops_GGHI.y * _hoops_RGHI.z	 -	_hoops_GGHI.z * _hoops_RGHI.y	 == 0.0f &&
		_hoops_GGHI.z * _hoops_RGHI.x	 -	_hoops_GGHI.x * _hoops_RGHI.z	 == 0.0f &&
		_hoops_GGHI.x * _hoops_RGHI.y	 -	_hoops_GGHI.y * _hoops_RGHI.x	 == 0.0f) {
		HE_ERROR (HEC_GRID, HES_COLINEAR_POINTS, "Grid origin and reference points are colinear");
		return 0;
	}

	_hoops_RAHCR = _hoops_ISSSR (_hoops_GGHI._hoops_SSRP(_hoops_RGHI));

	if (_hoops_RAHCR < 0.0f) 
		_hoops_RAHCR = -_hoops_RAHCR;

	_hoops_IPIAA = (int)(360.0f / _hoops_RAHCR + 0.5f); /* _hoops_PHI _hoops_IIGR _hoops_HPGIH _hoops_GGR _hoops_IRS _hoops_PRHC */

	return _hoops_IPIAA;
}


GLOBAL_FUNCTION Key HI_Insert_Grid (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	char const *			type,
	Point const	*			origin,
	Point const	*			ref1,
	Point const	*			ref2,
	int						count1,
	int						count2) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_GPGIH data;
	ZERO_STRUCT(&data, _hoops_GPGIH);

	if ((data._hoops_IPIAA = _hoops_PPGIH (origin, ref1, ref2)) == 0) {
		return _hoops_SHSSR;
	}

	if ((data._hoops_APIAA = _hoops_APGIH (type)) == 0) {
		return _hoops_SHSSR;
	}

	data.origin = origin;
	data.ref1 = ref1;
	data.ref2 = ref2;
	data.count1 = count1;
	data.count2 = count2;

	_hoops_RPGIH (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.grid);

	return _hoops_CHSSR;
}




HC_INTERFACE Key HC_CDECL HC_Insert_Grid (
	char const *		type,
	Point const	*		origin,
	Point const	*		ref1,
	Point const	*		ref2,
	int					count1,
	int					count2) 
{
	_hoops_PAPPR context("Insert_Grid");

	if (!origin || !ref1 || !ref2) {
		HE_ERROR (HEC_GRID, HES_INVALID_INPUT, "All points must be provided.");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Grid (context, target, type, origin, ref1, ref2, count1, count2);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT origin, ref1, ref2;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "origin.x = %f;	 origin.y = %f;	 ", origin->x, origin->y));
		HI_Dump_Code (Sprintf_F (null, "origin.z = %f;\n", origin->z));
		HI_Dump_Code (Sprintf_FF (null, "ref1.x = %f;  ref1.y = %f;	 ", ref1->x, ref1->y));
		HI_Dump_Code (Sprintf_F (null, "ref1.z = %f;\n", ref1->z));
		HI_Dump_Code (Sprintf_FF (null, "ref2.x = %f;  ref2.y = %f;	 ", ref2->x, ref2->y));
		HI_Dump_Code (Sprintf_F (null, "ref2.z = %f;\n", ref2->z));
		HI_Dump_Code (Sprintf_S (null, "DEFINE (HC_Insert_Grid (%S, &origin, &ref1, &ref2, ", type));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d), ", count1, count2));
		HI_Dump_Code (Sprintf_LD (null, "%D);}\n", _hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
}



HC_INTERFACE void HC_CDECL HC_Show_Grid (
	Key				key,
	char *			type,
	Point *			origin,
	Point *			ref1,
	Point *			ref2,
	int *			count1,
	int *			count2) 
{
	_hoops_PAPPR context("Show_Grid");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Grid () */\n");
	);

	_hoops_CSPPR();

	Grid *	grid = (Grid *)_hoops_RCSSR (context, key);

	if (grid == null ||
		grid->type != _hoops_GGCP ||
		BIT (grid->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GRID, HES_INVALID_KEY, "Provided key does not refer to a valid grid");
	}
	else {
		if (origin != null)
			*origin = grid->origin;

		if (ref1 != null)
			*ref1 = grid->ref1;

		if (ref2 != null)
			*ref2 = grid->ref2;

		if (count1 != null)
			*count1 = grid->count1;

		if (count2 != null)
			*count2 = grid->count2;

		if (type != null) {
			if (grid->_hoops_APIAA == _hoops_SPARP)
				HI_Return_Chars (type, -1, "radial", 6);
			else
				HI_Return_Chars (type, -1, "quadrilateral", 13);
		}
	}

	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Edit_Grid (
	Key				key,
	char const *	type,
	Point const	*	origin,
	Point const	*	ref1,
	Point const	*	ref2,
	int				count1,
	int				count2) 
{
	_hoops_PAPPR context("Edit_Grid");

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT origin, ref1, ref2;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "origin.x = %f;	 origin.y = %f;	 ",origin->x, origin->y));
		HI_Dump_Code (Sprintf_F (null, "origin.z = %f;\n", origin->z));
		HI_Dump_Code (Sprintf_FF (null, "ref1.x = %f;  ref1.y = %f;	 ", ref1->x, ref1->y));
		HI_Dump_Code (Sprintf_F (null, "ref1.z = %f;\n", ref1->z));
		HI_Dump_Code (Sprintf_FF (null, "ref2.x = %f;  ref2.y = %f;	 ", ref2->x, ref2->y));
		HI_Dump_Code (Sprintf_F (null, "ref2.z = %f;\n", ref2->z));
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Grid (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_S (null, "%S, &origin, &ref1, &ref2, ", type));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d);}\n", count1, count2));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_GPGIH data;
	ZERO_STRUCT(&data, _hoops_GPGIH);
	if ((data._hoops_IPIAA = _hoops_PPGIH (origin, ref1, ref2)) == 0) 
		return;
	if ((data._hoops_APIAA = _hoops_APGIH (type)) == 0) 
		return;
	data.origin = origin;
	data.ref1 = ref1;
	data.ref2 = ref2;
	data.count1 = count1;
	data.count2 = count2;

	_hoops_CRCP *owner;
	_hoops_CSPPR();
	Grid *	g = (Grid *)_hoops_RCSSR (context, key);
	if (g == null || g->type != _hoops_GGCP ||
		BIT (g->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid grid");
		goto Release;
	}
	data.grid = g;
	_hoops_RPGIH (context, null, &data);
	owner = g->owner;
	if (owner != null) {
		_hoops_SASIR (context, owner, 
			_hoops_AISSR |
			_hoops_PISSR |
			_hoops_CSCCA |
			_hoops_RPSIR);
	}

	if (owner)
		HI_Antiquate_Bounding (owner, true);

  Release:
	_hoops_IRRPR();
}

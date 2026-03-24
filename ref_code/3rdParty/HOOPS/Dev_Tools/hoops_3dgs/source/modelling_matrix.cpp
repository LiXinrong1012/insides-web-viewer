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
 * $Id: obf_tmp.txt 1.74 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local Attribute * _hoops_HGCII (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH alter *			item,
	Attribute const *			_hoops_CPACR,
	Attribute alter *			_hoops_SPACR) 
{
	_hoops_ISGI const *	_hoops_IGCII = (_hoops_ISGI const *)_hoops_CPACR;
	_hoops_ISGI alter *	_hoops_CGCII = (_hoops_ISGI alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_IGCII);

	if (BIT (_hoops_CGCII->matrix._hoops_RAGR, _hoops_RRICR)) {
		_hoops_CGCII->_hoops_RRHH |= _hoops_RSPCR;

		_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
		while(_hoops_SRCP != null && _hoops_SRCP->type != _hoops_IRCP)
			_hoops_SRCP = _hoops_SRCP->owner;

		if (_hoops_SRCP != null && !BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
			HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASPCR);
	}

	return _hoops_CGCII;
}


local Attribute * _hoops_SGCII (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH alter *			item,
	Attribute const *			_hoops_CPACR,
	Attribute alter *			_hoops_SPACR) 
{
	_hoops_ISGI const *	_hoops_IGCII = (_hoops_ISGI const *)_hoops_CPACR;
	_hoops_ISGI alter *	_hoops_CGCII = (_hoops_ISGI alter *)_hoops_SPACR;

	if (_hoops_IGCII != null &&
		ANYBIT (_hoops_IGCII->matrix._hoops_RAGR, _hoops_CICH))
		HI_Multiply_Matrices (&_hoops_IGCII->matrix, &_hoops_CGCII->matrix, &_hoops_CGCII->matrix);

	if (BIT (_hoops_CGCII->matrix._hoops_RAGR, _hoops_RRICR)) {

		_hoops_CGCII->_hoops_RRHH |= _hoops_RSPCR;

		_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
		while(_hoops_SRCP != null && _hoops_SRCP->type != _hoops_IRCP)
			_hoops_SRCP = _hoops_SRCP->owner;

		if (_hoops_SRCP != null && !BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
			HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASPCR);
	}

	return _hoops_CGCII;
}

GLOBAL_FUNCTION bool HI_Set_Modelling_Matrix(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ISGI *		modelling_matrix) 
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_MODELLING_MATRIX, _hoops_HGCII, modelling_matrix);
}

GLOBAL_FUNCTION bool HI_Append_Modelling_Matrix(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_ISGI *		modelling_matrix) 
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_MODELLING_MATRIX, _hoops_SGCII, modelling_matrix);
}


HC_INTERFACE void HC_CDECL HC_Set_Modelling_Matrix (
	float const *			_hoops_CASPA) 
{
	_hoops_PAPPR context("Set_Modelling_Matrix");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "matrix[0] = %f;  matrix[1] = %f;  ", _hoops_CASPA[0], _hoops_CASPA[1]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[2] = %f;  matrix[3] = %f;\n", _hoops_CASPA[2], _hoops_CASPA[3]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[4] = %f;  matrix[5] = %f;  ", _hoops_CASPA[4], _hoops_CASPA[5]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[6] = %f;  matrix[7] = %f;\n", _hoops_CASPA[6], _hoops_CASPA[7]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[8] = %f;  matrix[9] = %f;  ", _hoops_CASPA[8], _hoops_CASPA[9]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[10] = %f;  matrix[11] = %f;\n", _hoops_CASPA[10], _hoops_CASPA[11]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[12] = %f;  matrix[13] = %f;	 ", _hoops_CASPA[12], _hoops_CASPA[13]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[14] = %f;  matrix[15] = %f;\n", _hoops_CASPA[14], _hoops_CASPA[15]));
		HI_Dump_Code ("HC_Set_Modelling_Matrix (matrix);\n");
	);

	bool				used = false;
	_hoops_ISGI *	modelling_matrix;
	ZALLOC (modelling_matrix, _hoops_ISGI);

	if (HI_Figure_General_Modelling_Mtx (_hoops_CASPA, &modelling_matrix->matrix)) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_HPRPP)) != null) {
			used = HI_Set_Modelling_Matrix(context, target, modelling_matrix);
			_hoops_IRRPR();
		}
	}

	if (!used)
		FREE (modelling_matrix, _hoops_ISGI);
}



HC_INTERFACE void HC_CDECL HC_Translate_Object (
	double					x,
	double					y,
	double					z) 
{
	_hoops_PAPPR context("Translate_Object");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Translate_Object (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	bool				used = false;
	_hoops_ISGI *	modelling_matrix;
	ZALLOC (modelling_matrix, _hoops_ISGI);

	HI_Figure_Translation_Matrix ((float)x, (float)y, (float)z, &modelling_matrix->matrix);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HPRPP)) != null) {
		used = HI_Append_Modelling_Matrix(context, target, modelling_matrix);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (modelling_matrix, _hoops_ISGI);
}


HC_INTERFACE void HC_CDECL HC_Scale_Object (
	double					x,
	double					y,
	double					z) 
{
	_hoops_PAPPR context("Scale_Object");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Scale_Object (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	bool				used = false;
	_hoops_ISGI *	modelling_matrix;
	ZALLOC (modelling_matrix, _hoops_ISGI);

	HI_Figure_Scale_Matrix ((float)x, (float)y, (float)z, &modelling_matrix->matrix);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HPRPP)) != null) {
		used = HI_Append_Modelling_Matrix(context, target, modelling_matrix);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (modelling_matrix, _hoops_ISGI);
}


HC_INTERFACE void HC_CDECL HC_Rotate_Object_Offaxis (
	double					x,
	double					y,
	double					z,
	double					_hoops_RAHCR) 
{
	_hoops_PAPPR context("Rotate_Object_offaxis");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Rotate_Object_Offaxis (%F, %F, ", x, y));
	HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", z, _hoops_RAHCR));
	);

	bool				used = false;
	_hoops_ISGI *	modelling_matrix;
	ZALLOC (modelling_matrix, _hoops_ISGI);

	HI_Figure_Offaxis_Rotation_Mtx ((float)x, (float)y, (float)z, (float)_hoops_RAHCR, &modelling_matrix->matrix);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HPRPP)) != null) {
		used = HI_Append_Modelling_Matrix(context, target, modelling_matrix);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (modelling_matrix, _hoops_ISGI);
}


HC_INTERFACE void HC_CDECL HC_Rotate_Object (
	double					x,
	double					y,
	double					z) 
{
	_hoops_PAPPR context("Rotate_Object");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Rotate_Object (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	bool				used = false;
	_hoops_ISGI *	modelling_matrix;
	ZALLOC (modelling_matrix, _hoops_ISGI);

	HI_Figure_Rotation_Matrix ((float)x, (float)y, (float)z, &modelling_matrix->matrix);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HPRPP)) != null) {
		used = HI_Append_Modelling_Matrix(context, target, modelling_matrix);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (modelling_matrix, _hoops_ISGI);
}


HC_INTERFACE void HC_CDECL HC_Append_Modelling_Matrix (
	float const *			_hoops_CASPA) 
{
	_hoops_PAPPR context("Append_Modelling_Matrix");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "matrix[0] = %f;  matrix[1] = %f;  ", _hoops_CASPA[0], _hoops_CASPA[1]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[2] = %f;  matrix[3] = %f;\n", _hoops_CASPA[2], _hoops_CASPA[3]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[4] = %f;  matrix[5] = %f;  ", _hoops_CASPA[4], _hoops_CASPA[5]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[6] = %f;  matrix[7] = %f;\n", _hoops_CASPA[6], _hoops_CASPA[7]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[8] = %f;  matrix[9] = %f;  ", _hoops_CASPA[8], _hoops_CASPA[9]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[10] = %f;  matrix[11] = %f;\n", _hoops_CASPA[10], _hoops_CASPA[11]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[12] = %f;  matrix[13] = %f;	 ", _hoops_CASPA[12], _hoops_CASPA[13]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[14] = %f;  matrix[15] = %f;\n", _hoops_CASPA[14], _hoops_CASPA[15]));
		HI_Dump_Code ("HC_Append_Modelling_Matrix (matrix);\n");
	);

	bool				used = false;
	_hoops_ISGI *	modelling_matrix;
	ZALLOC (modelling_matrix, _hoops_ISGI);

	if (HI_Figure_General_Modelling_Mtx (_hoops_CASPA, &modelling_matrix->matrix)) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_HPRPP)) != null) {
			used = HI_Append_Modelling_Matrix(context, target, modelling_matrix);
			_hoops_IRRPR();
		}
	}

	if (!used)
		FREE (modelling_matrix, _hoops_ISGI);
}



HC_INTERFACE void HC_CDECL HC_UnSet_Modelling_Matrix (void) 
{
	_hoops_PAPPR context("UnSet_Modelling_Matrix");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Modelling_Matrix ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HPRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_MODELLING_MATRIX);
		_hoops_IRRPR();
	}
}


HC_INTERFACE void HC_CDECL HC_Show_Modelling_Matrix (
	float alter *			_hoops_CASPA) 
{
	_hoops_PAPPR context("Show_Modelling_Matrix ");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Modelling_Matrix () */\n");
	);


	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_ASRPP)) != null) {

		_hoops_ISGI *	modelling_matrix;
		if ((modelling_matrix = (_hoops_ISGI *)HI_Find_Attribute (context, target, HK_MODELLING_MATRIX)) != null) {
			_hoops_RPRA alter *		_hoops_SASPA = (_hoops_RPRA alter *)_hoops_CASPA;
			HI_Copy_43 (&modelling_matrix->matrix.elements[0][0], &_hoops_SASPA[0][0]);
			_hoops_SASPA[0][3] = _hoops_SASPA[1][3] = _hoops_SASPA[2][3] = 0.0f;
			_hoops_SASPA[3][3] = 1.0f;
			_hoops_HPRH (modelling_matrix);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Modelling_Matrix (
	int						count,
	Key const *				keys,
	float alter *			_hoops_CASPA) 
{
	_hoops_PAPPR context("PShow_Net_Modelling_Matrix ");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Modelling_Matrix () */\n");
	);

	_hoops_RPRA alter *	_hoops_SASPA = (_hoops_RPRA alter *)_hoops_CASPA;

	_hoops_ISGI *	modelling_matrix;
	if ((modelling_matrix = (_hoops_ISGI *) HI_Find_Attribute_And_Lock(context, _hoops_ASRPP, _hoops_HRPCR, count, keys)) != null) {
		HI_Copy_43 (&modelling_matrix->matrix.elements[0][0], &_hoops_SASPA[0][0]);
		_hoops_SASPA[0][3] = _hoops_SASPA[1][3] = _hoops_SASPA[2][3] = 0.0f;
		_hoops_SASPA[3][3] = 1.0f;
		_hoops_HPRH (modelling_matrix);
		_hoops_IRRPR();
	} 
	else 
		HI_Compute_Identity_Matrix(&_hoops_SASPA[0][0]);
	
#endif
}
#endif



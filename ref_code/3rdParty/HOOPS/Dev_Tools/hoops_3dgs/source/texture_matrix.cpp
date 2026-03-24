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
 * $Id: obf_tmp.txt 1.65 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_TEXTURING

local Attribute * _hoops_RHSGGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_GAAIR const *	_hoops_IGCII = (_hoops_GAAIR const *)_hoops_CPACR;	
	_hoops_GAAIR alter *	_hoops_CGCII = (_hoops_GAAIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_IGCII);

	if (_hoops_CGCII->matrix._hoops_APRA == null)
		HI_Validate_Matrix_Adjoint ((_hoops_HRPA alter *)&_hoops_CGCII->matrix);

	if (BIT (_hoops_CGCII->matrix._hoops_RAGR, _hoops_RRICR)) {
		_hoops_CGCII->_hoops_RRHH |= _hoops_RSPCR;

		_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
		ASSERT(_hoops_SRCP->type == _hoops_IRCP);

		if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
			HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASPCR);
	}

	return _hoops_CGCII;
}
#endif



GLOBAL_FUNCTION bool HI_Set_Texture_Matrix (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GAAIR *		_hoops_APGH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_TEXTURE_MATRIX, _hoops_RHSGGR, _hoops_APGH);
}


HC_INTERFACE void HC_CDECL HC_Set_Texture_Matrix (
	float const *			_hoops_CASPA) 
{
	_hoops_PAPPR context("Set_Texture_Matrix");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "matrix[0] = %f;  matrix[1] = %f;  ",_hoops_CASPA[0], _hoops_CASPA[1]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[2] = %f;  matrix[3] = %f;\n",_hoops_CASPA[2], _hoops_CASPA[3]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[4] = %f;  matrix[5] = %f;  ",_hoops_CASPA[4], _hoops_CASPA[5]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[6] = %f;  matrix[7] = %f;\n",_hoops_CASPA[6], _hoops_CASPA[7]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[8] = %f;  matrix[9] = %f;  ", _hoops_CASPA[8], _hoops_CASPA[9]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[10] = %f;  matrix[11] = %f;\n",_hoops_CASPA[10], _hoops_CASPA[11]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[12] = %f;  matrix[13] = %f;	 ", _hoops_CASPA[12], _hoops_CASPA[13]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[14] = %f;  matrix[15] = %f;\n", _hoops_CASPA[14], _hoops_CASPA[15]));
		HI_Dump_Code ("HC_Set_Texture_Matrix (matrix);\n");
	);

	bool				used = false;
	_hoops_GAAIR *	_hoops_APGH;
	ZALLOC (_hoops_APGH, _hoops_GAAIR);

	if (HI_Figure_General_Texture_Mtx (_hoops_CASPA, &_hoops_APGH->matrix)) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_GHRPP)) != null) {
			used = HI_Set_Texture_Matrix(context, target, _hoops_APGH);
			_hoops_IRRPR();
		}
	}

	if (!used)
		FREE (_hoops_APGH, _hoops_GAAIR);

#endif
}




HC_INTERFACE void HC_CDECL HC_UnSet_Texture_Matrix (void) {
	_hoops_PAPPR context("UnSet_Texture_Matrix");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Texture_Matrix ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GHRPP)) != null) {
		HI_UnSet_Attribute (context, target, HK_TEXTURE_MATRIX);
		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Texture_Matrix (
	float alter *			_hoops_CASPA) 
{
	_hoops_PAPPR context("Show_Texture_Matrix");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Texture_Matrix () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_CSRPP)) != null) {

		_hoops_GAAIR *	_hoops_APGH;
		if ((_hoops_APGH = (_hoops_GAAIR *)HI_Find_Attribute (context, target, HK_TEXTURE_MATRIX)) != null) {
			_hoops_RPRA alter *		_hoops_SASPA = (_hoops_RPRA alter *)_hoops_CASPA;
			HI_Copy_44 (&_hoops_APGH->matrix.elements[0][0], &_hoops_SASPA[0][0]);
			_hoops_HPRH (_hoops_APGH);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}



#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Texture_Matrix (
	int						count,
	Key const *				keys,
	float alter *			_hoops_CASPA) 
{
	_hoops_PAPPR context("PShow_Net_Texture_Matrix");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Teture_Matrix () */\n");
	);

	_hoops_RPRA alter *		_hoops_SASPA = (_hoops_RPRA alter *)_hoops_CASPA;

	_hoops_GAAIR *	_hoops_APGH;
	if ((_hoops_APGH = (_hoops_GAAIR *) HI_Find_Attribute_And_Lock(context, _hoops_CSRPP, _hoops_HRPCR, count, keys)) != null) {
		HI_Copy_44 (&_hoops_APGH->matrix.elements[0][0], &_hoops_SASPA[0][0]);
		_hoops_HPRH (_hoops_APGH);
		_hoops_IRRPR();
	}
	else
		HI_Compute_Identity_Matrix(&_hoops_SASPA[0][0]);
#endif
#endif
}
#endif



local Attribute * _hoops_AHSGGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR) 
{
	_hoops_GAAIR const *	_hoops_IGRRS = (_hoops_GAAIR const *)_hoops_CPACR;
	_hoops_GAAIR alter *	_hoops_AISHC = (_hoops_GAAIR alter *)_hoops_SPACR;

	if (_hoops_IGRRS != null &&
		ANYBIT (_hoops_IGRRS->matrix._hoops_RAGR, _hoops_CICH))
		HI_Multiply_Matrices (&_hoops_IGRRS->matrix, &_hoops_AISHC->matrix, &_hoops_AISHC->matrix);

	if (_hoops_AISHC->matrix._hoops_APRA == null)
		HI_Validate_Matrix_Adjoint (&_hoops_AISHC->matrix);

	if (BIT (_hoops_AISHC->matrix._hoops_RAGR, _hoops_RRICR)) {
		_hoops_AISHC->_hoops_RRHH |= _hoops_RSPCR;

		_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
		ASSERT(_hoops_SRCP->type == _hoops_IRCP);

		if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
			HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASPCR);
	}

	return _hoops_AISHC;
}

GLOBAL_FUNCTION bool HI_Append_Texture_Matrix (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GAAIR *		_hoops_APGH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_TEXTURE_MATRIX, _hoops_AHSGGR, _hoops_APGH);
}


HC_INTERFACE void HC_CDECL HC_Translate_Texture (
	double					x,
	double					y,
	double					z) 
{
	_hoops_PAPPR context("Translate_Texture");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Translate_Texture (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	bool				used = false;
	_hoops_GAAIR *	_hoops_APGH;
	ZALLOC (_hoops_APGH, _hoops_GAAIR);

	HI_Figure_Translation_Matrix ((float)x, (float)y, (float)z, &_hoops_APGH->matrix);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GHRPP)) != null) {
		used = HI_Append_Texture_Matrix(context, target, _hoops_APGH);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_APGH, _hoops_GAAIR);
#endif
}



HC_INTERFACE void HC_CDECL HC_Scale_Texture (
	double					x,
	double					y,
	double					z) 
{
	_hoops_PAPPR context("Scale_Texture");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Scale_Texture (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	bool				used = false;
	_hoops_GAAIR *	_hoops_APGH;
	ZALLOC (_hoops_APGH, _hoops_GAAIR);

	HI_Figure_Scale_Matrix ((float)x, (float)y, (float)z, &_hoops_APGH->matrix);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GHRPP)) != null) {
		used = HI_Append_Texture_Matrix(context, target, _hoops_APGH);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_APGH, _hoops_GAAIR);
#endif
}



HC_INTERFACE void HC_CDECL HC_Rotate_Texture (
	double					x,
	double					y,
	double					z) 
{
	_hoops_PAPPR context("Rotate_Texture");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Rotate_Texture (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	bool				used = false;
	_hoops_GAAIR *	_hoops_APGH;
	ZALLOC (_hoops_APGH, _hoops_GAAIR);

	HI_Figure_Rotation_Matrix ((float)x, (float)y, (float)z, &_hoops_APGH->matrix);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GHRPP)) != null) {
		used = HI_Append_Texture_Matrix(context, target, _hoops_APGH);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_APGH, _hoops_GAAIR);
#endif
}



HC_INTERFACE void HC_CDECL HC_Rotate_Texture_Offaxis (
	double					x,
	double					y,
	double					z,
	double					_hoops_RAHCR) 
{
	_hoops_PAPPR context("Rotate_Texture_Offaxis");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Rotate_Texture_Offaxis (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", z, _hoops_RAHCR));
	);

	bool				used = false;
	_hoops_GAAIR *	_hoops_APGH;
	ZALLOC (_hoops_APGH, _hoops_GAAIR);

	HI_Figure_Offaxis_Rotation_Mtx ((float)x, (float)y, (float)z, (float)_hoops_RAHCR, &_hoops_APGH->matrix);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GHRPP)) != null) {
		used = HI_Append_Texture_Matrix(context, target, _hoops_APGH);
		_hoops_IRRPR();
	}

	if (!used)
		FREE (_hoops_APGH, _hoops_GAAIR);
#endif
}




GLOBAL_FUNCTION bool HI_Figure_General_Texture_Mtx (
	float const *			_hoops_CASPA,
	_hoops_HRPA alter *		mat) 
{
#ifndef DISABLE_TEXTURING
	_hoops_RPRA const *		_hoops_SASPA = (_hoops_RPRA const *)_hoops_CASPA;
	_hoops_RPRA alter *		m = mat->elements;
	float					scale, tmp;

	if (_hoops_SASPA[3][3] == 0.0f) {
		HE_ERROR (HEC_TEXTURE, HES_SINGULAR_MATRIX, "Requested texture matrix is singular");
		return false;
	}

	mat->flags = false;
	mat->_hoops_RAGR = false;

	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;
	m[3][3] = 1.0f;

	if (_hoops_SASPA[3][3] == 1.0f) {
		m[0][0] = _hoops_SASPA[0][0];
		m[0][1] = _hoops_SASPA[0][1];
		m[0][2] = _hoops_SASPA[0][2];
		m[1][0] = _hoops_SASPA[1][0];
		m[1][1] = _hoops_SASPA[1][1];
		m[1][2] = _hoops_SASPA[1][2];
		m[2][0] = _hoops_SASPA[2][0];
		m[2][1] = _hoops_SASPA[2][1];
		m[2][2] = _hoops_SASPA[2][2];
		m[3][0] = _hoops_SASPA[3][0];
		m[3][1] = _hoops_SASPA[3][1];
		m[3][2] = _hoops_SASPA[3][2];
	}
	else {
		float			_hoops_GPSPA = 1.0f/_hoops_SASPA[3][3];

		m[0][0] = _hoops_SASPA[0][0] * _hoops_GPSPA;
		m[0][1] = _hoops_SASPA[0][1] * _hoops_GPSPA;
		m[0][2] = _hoops_SASPA[0][2] * _hoops_GPSPA;
		m[1][0] = _hoops_SASPA[1][0] * _hoops_GPSPA;
		m[1][1] = _hoops_SASPA[1][1] * _hoops_GPSPA;
		m[1][2] = _hoops_SASPA[1][2] * _hoops_GPSPA;
		m[2][0] = _hoops_SASPA[2][0] * _hoops_GPSPA;
		m[2][1] = _hoops_SASPA[2][1] * _hoops_GPSPA;
		m[2][2] = _hoops_SASPA[2][2] * _hoops_GPSPA;
		m[3][0] = _hoops_SASPA[3][0] * _hoops_GPSPA;
		m[3][1] = _hoops_SASPA[3][1] * _hoops_GPSPA;
		m[3][2] = _hoops_SASPA[3][2] * _hoops_GPSPA;
	}

	if (m[0][2] != 0.0f || m[1][2] != 0.0f || m[3][2] != 0.0f)
		mat->_hoops_RAGR |= _hoops_RRICR;

	scale = m[0][0] * m[0][0]  +  m[1][0] * m[1][0]	 +	m[2][0] * m[2][0];
	if (scale != 1.0f || m[0][0] == -1.0f)
		mat->_hoops_RAGR |= _hoops_CHCP;
	mat->_hoops_CPH = _hoops_SGIHR (scale);
	tmp = m[0][1] * m[0][1]	 +	m[1][1] * m[1][1]  +  m[2][1] * m[2][1];
	if (tmp != 1.0f || m[1][1] == -1.0f)
		mat->_hoops_RAGR |= _hoops_CHCP;
	if (tmp != scale) mat->_hoops_CPH = 0.0f;
	tmp = m[0][2] * m[0][2]	 +	m[1][2] * m[1][2]  +  m[2][2] * m[2][2];
	if (tmp != 1.0f || m[2][2] == -1.0f)
		mat->_hoops_RAGR |= _hoops_CHCP;
	if (tmp != scale) mat->_hoops_CPH = 0.0f;

	if (m[3][0] != 0.0f || m[3][1] != 0.0f || m[3][2] != 0.0f)
		mat->_hoops_RAGR |= _hoops_PRICR;

	if (m[0][1] != 0.0f || m[0][2] != 0.0f ||
		m[1][0] != 0.0f || m[1][2] != 0.0f ||
		m[2][0] != 0.0f || m[2][1] != 0.0f)
		mat->_hoops_RAGR |= _hoops_GRICR;

	if (m[0][3] != 0.0f || m[1][3] != 0.0f || m[2][3] != 0.0f)
		mat->_hoops_RAGR |= _hoops_HRICR;

	return true;
#else
	return false;
#endif
}


HC_INTERFACE void HC_CDECL HC_Append_Texture_Matrix (
	float const *			_hoops_CASPA) 
{
	_hoops_PAPPR context("Append_Texture_Matrix");

#ifdef DISABLE_TEXTURING
	_hoops_IRPPR ("Texturing");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "matrix[0] = %f;  matrix[1] = %f;  ", _hoops_CASPA[0], _hoops_CASPA[1]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[2] = %f;  matrix[3] = %f;\n", _hoops_CASPA[2], _hoops_CASPA[3]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[4] = %f;  matrix[5] = %f;  ", _hoops_CASPA[4], _hoops_CASPA[5]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[6] = %f;  matrix[7] = %f;\n",_hoops_CASPA[6], _hoops_CASPA[7]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[8] = %f;  matrix[9] = %f;  ",_hoops_CASPA[8], _hoops_CASPA[9]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[10] = %f;  matrix[11] = %f;\n", _hoops_CASPA[10], _hoops_CASPA[11]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[12] = %f;  matrix[13] = %f;	 ", _hoops_CASPA[12], _hoops_CASPA[13]));
		HI_Dump_Code (Sprintf_FF (null, "matrix[14] = %f;  matrix[15] = %f;\n", _hoops_CASPA[14], _hoops_CASPA[15]));
		HI_Dump_Code ("HC_Append_Texture_Matrix (matrix);\n");
	);

	bool				used = false;
	_hoops_GAAIR *	_hoops_APGH;
	ZALLOC (_hoops_APGH, _hoops_GAAIR);

	if (HI_Figure_General_Texture_Mtx (_hoops_CASPA, &_hoops_APGH->matrix)) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_GHRPP)) != null) {
			used = HI_Append_Texture_Matrix(context, target, _hoops_APGH);
			_hoops_IRRPR();
		}
	}

	if (!used)
		FREE (_hoops_APGH, _hoops_GAAIR);
#endif
}




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
 * $Id: obf_tmp.txt 1.58 2010-11-10 03:05:35 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hc_proto.h"

#ifdef _hoops_CACIR
#  undef _hoops_CACIR
#endif
#define _hoops_CACIR (1e-7f)
#ifndef _hoops_IAGHA
#  define _hoops_IAGHA (3.14159265358979323846264338327950288)
#endif
#ifdef _hoops_SAGHA
#  undef _hoops_SAGHA
#endif
#define _hoops_SAGHA(x) (180.0f*(x) / (float)_hoops_IAGHA)  



GLOBAL_FUNCTION double HI_Compute_Vector_Angle (
	Vector const *	in1,
	Vector const *	in2) 
{
	Vector		_hoops_IHACA, _hoops_CHACA;
	float		_hoops_HRPPA, _hoops_SPPPA;
	float		_hoops_SSRP;

	_hoops_HRPPA = in1->x * in1->x	+  in1->y * in1->y	+  in1->z * in1->z;
	_hoops_SPPPA = in2->x * in2->x	+  in2->y * in2->y	+  in2->z * in2->z;

	if (_hoops_HRPPA < _hoops_CACIR || _hoops_SPPPA < _hoops_CACIR) 
			return 0;

	if (_hoops_HRPPA != 1.0f)
				_hoops_HRPPA = _hoops_SGIHR (_hoops_HRPPA);
	if (_hoops_SPPPA != 1.0f)
				_hoops_SPPPA = _hoops_SGIHR (_hoops_SPPPA);

	_hoops_IHACA.x = in1->x / _hoops_HRPPA;
	_hoops_IHACA.y = in1->y / _hoops_HRPPA;
	_hoops_IHACA.z = in1->z / _hoops_HRPPA;
	_hoops_CHACA.x = in2->x / _hoops_SPPPA;
	_hoops_CHACA.y = in2->y / _hoops_SPPPA;
	_hoops_CHACA.z = in2->z / _hoops_SPPPA;
	_hoops_SSRP = (_hoops_IHACA.x * _hoops_CHACA.x +
					_hoops_IHACA.y * _hoops_CHACA.y +
					_hoops_IHACA.z * _hoops_CHACA.z);
	if (_hoops_SSRP >= 1)
			return 0;
	else if (_hoops_SSRP <= -1)
			return 180;
	return HI_ACos(_hoops_SSRP);
}


HC_INTERFACE double HC_CDECL HC_Compute_Vector_Angle (
	Point const	*in1,
	Point const	*in2) 
{
	_hoops_PAPPR context("Compute_Vector_Angle");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Vector_Angle () */\n");
	);

	return HI_Compute_Vector_Angle ((Vector const *)in1, (Vector const *)in2);
}

GLOBAL_FUNCTION void HI_Compute_Cross_Product (
	Vector const	*in1,
	Vector const	*in2,
	Vector alter	*_hoops_PAGR) {
	Vector		tmp;

	tmp.x = in1->y * in2->z	 -	in1->z * in2->y;
	tmp.y = in1->z * in2->x	 -	in1->x * in2->z;
	tmp.z = in1->x * in2->y	 -	in1->y * in2->x;

	_hoops_PAGR->x = tmp.x;
	_hoops_PAGR->y = tmp.y;
	_hoops_PAGR->z = tmp.z;
}

HC_INTERFACE void HC_CDECL HC_Compute_Cross_Product (
	Point const	*in1,
	Point const	*in2,
	Point alter	*_hoops_PAGR) 
{
	_hoops_PAPPR context("Compute_Cross_Product");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Cross_Product () */\n");
	);

	HI_Compute_Cross_Product ((Vector const *)in1, (Vector const *)in2, (Vector alter *)_hoops_PAGR);
}


GLOBAL_FUNCTION double HI_Compute_Dot_Product (
	Vector const	*in1,
	Vector const	*in2) 
{

	return in1->x * in2->x	+  in1->y * in2->y	+  in1->z * in2->z;
}

HC_INTERFACE double HC_CDECL HC_Compute_Dot_Product (
	Point const	*in1,
	Point const	*in2) 
{
	_hoops_PAPPR context("Compute_Dot_Product");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Dot_Product () */\n");
	);

	return HI_Compute_Dot_Product ((Vector const *) in1, (Vector const *) in2);
}


HC_INTERFACE double HC_CDECL HC_Compute_Vector_Length (
	Point const	*	in) 
{
	_hoops_PAPPR context("Compute_Vector_Length");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Vector_Length () */\n");
	);

	return HI_Compute_Vector_Length((Vector const *)in);
}

GLOBAL_FUNCTION double HI_Compute_Vector_Length (
	Vector const *	in) {
	_hoops_PPCIR			tmp = *in;

	return _hoops_SGIHR (tmp.x * tmp.x  +  tmp.y * tmp.y  +  tmp.z * tmp.z);
}


HC_INTERFACE bool HC_CDECL HC_Compute_Normalized_Vector (
	Point const	*	in,
	Point alter	*	_hoops_PAGR) 
{
	_hoops_PAPPR context("Compute_Normalized_Vector");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Normalized_Vector () */\n");
	);

	_hoops_PAGR->x = in->x;
	_hoops_PAGR->y = in->y;
	_hoops_PAGR->z = in->z;

	/* _hoops_SHACA _hoops_PRGIR _hoops_HIIC */
	return (HI_Normalize ((Vector alter *)_hoops_PAGR));
#endif
}


HC_INTERFACE bool HC_CDECL HC_Compute_Polygon_Normal (
	int				count,
	Point const	*	points,
	char const *	hand,
	Point alter	*	_hoops_PAGR) 
{
	_hoops_PAPPR context("Compute_Polygon_Normal");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Polygon_Normal () */\n");
	);

	_hoops_ARPA			plane;
	int				_hoops_HRACA;

	if (!HI_Figure_Plane_From_Points (count, points, &plane) ||
		!HI_Decipher_Handedness (hand, &_hoops_HRACA))
		return false;

	if (_hoops_HRACA == _hoops_GIACA) {
		_hoops_PAGR->x = -plane.a;
		_hoops_PAGR->y = -plane.b;
		_hoops_PAGR->z = -plane.c;
	}
	else {
		_hoops_PAGR->x = plane.a;
		_hoops_PAGR->y = plane.b;
		_hoops_PAGR->z = plane.c;
	}

	return true;
#endif
}


HC_INTERFACE bool HC_CDECL HC_Compute_Polygon_Plane (
	int				count,
	Point const	*	points,
	char const *	hand,
	_hoops_ARPA alter *	_hoops_PAGR) 
{
	_hoops_PAPPR context("Compute_Polygon_Plane");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Polygon_Plane () */\n");
	);

	int	_hoops_HRACA;

	if (!HI_Figure_Plane_From_Points (count, points, _hoops_PAGR) ||
		!HI_Decipher_Handedness (hand, &_hoops_HRACA))
		return false;

	if (_hoops_HRACA == _hoops_GIACA) {
		_hoops_PAGR->a = -_hoops_PAGR->a;
		_hoops_PAGR->b = -_hoops_PAGR->b;
		_hoops_PAGR->c = -_hoops_PAGR->c;
		_hoops_PAGR->d = -_hoops_PAGR->d;
	}

	return true;
#endif
}

GLOBAL_FUNCTION void HI_Cross_Product (
	Vector const *a,
	Vector const *b,
	Vector alter *c) {
	float           _hoops_SPSPA, _hoops_GHSPA;

	_hoops_SPSPA = a->y * b->z - a->z * b->y;
	_hoops_GHSPA = a->z * b->x - a->x * b->z;
	c->z = a->x * b->y - a->y * b->x;
	c->y = _hoops_GHSPA;
	c->x = _hoops_SPSPA;
}






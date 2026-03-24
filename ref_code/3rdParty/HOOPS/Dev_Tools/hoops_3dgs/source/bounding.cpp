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
 * $Id: obf_tmp.txt 1.85 2010-12-16 19:16:56 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "tandt.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HI_Set_Bounding(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Bounding *				bounding)
{
	_hoops_ICIIR(_hoops_RIGC);

	ASSERT(item->type == _hoops_IRCP);

	_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)item;

	_hoops_SRCP->bounding = *bounding;

	HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, _hoops_SRCP->bounding, null);
}


HC_INTERFACE void HC_CDECL HC_Set_Bounding_Cuboid (
	Point const	*			min,
	Point const	*			max)
{
	_hoops_PAPPR context("Set_Bounding_Cuboid");

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT min, max;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "min.x = %f;  min.y = %f;  ",  min->x, min->y));
		HI_Dump_Code (Sprintf_F (null, "min.z = %f;\n", min->z));
		HI_Dump_Code (Sprintf_FF (null, "max.x = %f;  max.y = %f;  ", max->x, max->y));
		HI_Dump_Code (Sprintf_F (null, "max.z = %f;\n", max->z));
		HI_Dump_Code ("HC_Set_Bounding_Cuboid (&min, &max);}\n");
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_SASC cuboid;
	cuboid.min = *min;
	cuboid.max = *max;
	Bounding	bounding = Bounding::Create(cuboid);
	bounding->flags = _hoops_CCIIR;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SCIIR)) != null) {
		HI_Set_Bounding(context, target, &bounding);
		_hoops_IRRPR();
	}
}


HC_INTERFACE void HC_CDECL HC_Set_Bounding_Sphere (
	Point const	*			center,
	double					radius)
{
	_hoops_PAPPR context("Set_Bounding_Sphere");

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT center;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "center.x = %f;	 center.y = %f;	 ", center->x, center->y));
		HI_Dump_Code (Sprintf_F (null, "center.z = %f;\n", center->z));
		HI_Dump_Code (Sprintf_F (null, "HC_Set_Bounding_Sphere (&center, %F);}\n", radius));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_CAIS sphere;
	sphere.center = *center;
	sphere.radius = radius;
	Bounding	bounding = Bounding::Create(sphere);
	bounding->flags = _hoops_CCIIR;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SCIIR)) != null) {
		HI_Set_Bounding(context, target, &bounding);
		_hoops_IRRPR();
	}
}

HC_INTERFACE void HC_CDECL HC_UnSet_Bounding_Volume (void)
{
	_hoops_PAPPR context("UnSet_Bounding_Volume");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Bounding_Volume ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SCIIR|_hoops_GSIIR)) != null) {
		ASSERT(target->type == _hoops_IRCP);

		_hoops_CRCP *	_hoops_SRCP = (_hoops_CRCP *)target;

		if (_hoops_SRCP->bounding != null)
			_hoops_SRCP->bounding->flags &= ~_hoops_CCIIR;

		_hoops_IRRPR();
	}
}

GLOBAL_FUNCTION void HI_Find_Bounding (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH const *		item,
	Bounding alter &		_hoops_RCHS)
{
	_hoops_RSIIR(_hoops_RIGC);

	_hoops_RCHS = null;

	if (item != null && item->type == _hoops_CIRIR) {

		_hoops_SIRIR const * _hoops_ASIIR = (_hoops_SIRIR const *)item;

		switch (_hoops_ASIIR->_hoops_GCRIR) {

			case _hoops_RCRIR: {
				item = (_hoops_HPAH const *)_hoops_ASIIR->info.segment._hoops_IGRPR;
			}	break;

			case _hoops_HCRIR: {
				item = (_hoops_HPAH const *)_hoops_ASIIR->info.geometry._hoops_IGRPR;
			}	break;

			case _hoops_GSRIR:
			case _hoops_SCRIR:
			case _hoops_CCRIR:
			case _hoops_ICRIR: {
				item = (_hoops_HPAH const *)_hoops_ASIIR->info._hoops_IPRI._hoops_IGRPR;
			}	break;

			default: {
				item = null; // _hoops_PSIIR _hoops_CAPP
			}	break; 
		}
	}

	if (item == null || BIT (item->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_BOUNDING_BOX, HES_INVALID_KEY, "Requested bounding on an invalid item");
	}
	else if (item->type == _hoops_IRCP)
		_hoops_RCHS = ((_hoops_CRCP *)item)->bounding;
	else if (item->type == _hoops_CSIP)
		_hoops_RCHS = ((PolyCylinder *)item)->bounding;
	else if (item->type == _hoops_AHIP)
		_hoops_RCHS = ((_hoops_PHIP *)item)->bounding;
	else if (item->type == _hoops_SCIP || item->type == _hoops_GSIP)
		_hoops_RCHS = ((Polyhedron *)item)->bounding;
	else
		HE_ERROR (HEC_BOUNDING_BOX, HES_INVALID_KEY, "Requested bounding on an item without a bounding");
}


HC_INTERFACE bool HC_CDECL HC_Show_Bounding_Cuboid_By_Key (
	Key						key,
	Point alter *			min,
	Point alter *			max)
{
	_hoops_PAPPR context("Show_Bounding_Cuboid_By_Key");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Bounding_Cuboid_By_Key () */\n");
	);

	Bounding _hoops_RCHS;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, key, _hoops_HSIIR)) != null) {
		HI_Find_Bounding (context, target, _hoops_RCHS);
		_hoops_IRRPR();
	}

	bool	result = false;
	if (!_hoops_RCHS._hoops_HICAR()) {
		*min = _hoops_RCHS->cuboid.min;
		*max = _hoops_RCHS->cuboid.max;
		result = true;
	}

	return result;
}



HC_INTERFACE bool HC_CDECL HC_Show_Bounding_Sphere_By_Key (
	Key						key,
	Point alter *			center,
	float alter *			radius)
{
	_hoops_PAPPR context("Show_Bounding_Sphere_By_Key");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Bounding_Sphere_By_Key () */\n");
	);

	Bounding _hoops_RCHS;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, key, _hoops_HSIIR)) != null) {
		HI_Find_Bounding (context, target, _hoops_RCHS);
		_hoops_IRRPR();
	}

	bool	result = false;
	if (!_hoops_RCHS._hoops_HICAR()) {
		*center = _hoops_RCHS->sphere.center;
		*radius = _hoops_RCHS->sphere.radius;
		result = true;
	}

	return result;
}


HC_INTERFACE bool HC_CDECL HC_Show_Bounding_Cuboid (
	Point alter *			min,
	Point alter *			max) {
	_hoops_PAPPR context("Show_Bounding_Cuboid");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Bounding_Cuboid () */\n");
	);

	Bounding _hoops_RCHS;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HSIIR)) != null) {
		HI_Find_Bounding (context, target, _hoops_RCHS);
		_hoops_IRRPR();
	}

	bool result = false;
	if (!_hoops_RCHS._hoops_HICAR()) {
		*min = _hoops_RCHS->cuboid.min;
		*max = _hoops_RCHS->cuboid.max;
		result = true;
	}
	
	return result;
}


HC_INTERFACE bool HC_CDECL HC_Show_Bounding_Sphere (
	Point alter *			center,
	float alter *			radius) {
	_hoops_PAPPR context("Show_Bounding_Sphere");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Bounding_Sphere () */\n");
	);

	Bounding _hoops_RCHS;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HSIIR)) != null) {
		HI_Find_Bounding (context, target, _hoops_RCHS);
		_hoops_IRRPR();
	}

	bool result = false;
	if (!_hoops_RCHS._hoops_HICAR()) {
		*center = _hoops_RCHS->sphere.center;
		*radius = _hoops_RCHS->sphere.radius;
		result = true;
	}

	return result;
}


/*
 * _hoops_IPCP _hoops_HSPR _hoops_SICAR _hoops_ASRC _hoops_HPHS _hoops_ISIIR
 * _hoops_RH _hoops_CSIIR _hoops_IIGR _hoops_RH _hoops_IASC _hoops_CISAR.
 */

local void _hoops_SSIIR (
	Bounding const &	bounding,
	char alter *		list,
	int					_hoops_GGCIR) {
	char				buf[512];
	char alter *		p = buf;

	if (bounding == null) {
		HI_Return_Chars (list, _hoops_GGCIR, "", 0);
		return;
	}

	if (!ANYBIT(bounding->flags, _hoops_RGCIR|_hoops_AGCIR))
		bounding->_hoops_PGCIR();

	if (BIT (bounding->flags, _hoops_RGCIR))
		_hoops_AAHR ("type=sphere,", p);
	else
		_hoops_AAHR ("type=cuboid,", p);

	p += 12;

	if (BIT (bounding->flags, Bounding_EMPTY)) {
		_hoops_AAHR ("empty,", p);
		p += 6;
	}

	if (ANYBIT (bounding->flags, _hoops_HGCIR|_hoops_IGCIR|Bounding_TRANSFORM_DEPENDENT)) {
		_hoops_AAHR ("transform dependent,", p);
		p += 20;
	}

	if (BIT (bounding->flags, _hoops_CCIIR)) {
		_hoops_AAHR ("user-defined,", p);
		p += 13;
	}

	float _hoops_CGCIR = bounding._hoops_SGCIR();
	p = HI_Sprintf1 (p, p+32, "density=%f,", (void *)&_hoops_CGCIR);

	--p; /* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_GRCIR _hoops_RRCIR */

	HI_Return_Chars (list, _hoops_GGCIR, buf, p - buf);
}



HC_INTERFACE void HC_CDECL HC_Show_Bounding_Info_By_Key (
	Key					key,
	char alter *		list)
{
	_hoops_PAPPR context("Show_Bounding_Info_By_Key");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Bounding_Info_By_Key () */\n");
	);

	Bounding _hoops_RCHS;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, key, _hoops_HSIIR)) != null) {
		HI_Find_Bounding (context, target, _hoops_RCHS);
		_hoops_IRRPR();
	}

	_hoops_SSIIR (_hoops_RCHS, list, -1);
}



/* _hoops_CRGH */

HC_INTERFACE void HC_CDECL HC_Show_Bounding_Info (
	char alter *		list)
{
	_hoops_PAPPR context("Show_Bounding_Info");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Bounding_Info () */\n");
	);

	Bounding _hoops_RCHS;

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HSIIR)) != null) {
		HI_Find_Bounding (context, target, _hoops_RCHS);
		_hoops_IRRPR();
	}

	_hoops_SSIIR (_hoops_RCHS, list, -1);
}






// _hoops_PASC
GLOBAL_FUNCTION bool HI_Compare_Bounding (
	Bounding const &		_hoops_IHHI,
	Bounding const &		_hoops_CHHI) {

	if (_hoops_IHHI._hoops_HICAR() && _hoops_CHHI._hoops_HICAR())
		return true;

	if (_hoops_IHHI._hoops_HICAR() || _hoops_CHHI._hoops_HICAR())
		return false;

	if (_hoops_IHHI->flags != _hoops_CHHI->flags)
		return false;

	return (_hoops_IHHI->cuboid.min == _hoops_CHHI->cuboid.min && _hoops_IHHI->cuboid.min == _hoops_CHHI->cuboid.min &&
				_hoops_IHHI->sphere.center == _hoops_CHHI->sphere.center && _hoops_IHHI->sphere.radius == _hoops_CHHI->sphere.radius);
}



GLOBAL_FUNCTION float HI_Cuboid_To_Cuboid_Distance(
	_hoops_SASC const & _hoops_ARCIR,
	_hoops_SASC const & _hoops_PRCIR)
{
	int _hoops_HRCIR, _hoops_IRCIR, _hoops_CRCIR;

	if (_hoops_PRCIR.max.x <= _hoops_ARCIR.min.x)
		_hoops_HRCIR = 0;
	else if (_hoops_PRCIR.min.x>= _hoops_ARCIR.max.x)
		_hoops_HRCIR = 2;
	else
		_hoops_HRCIR = 1;

	if (_hoops_PRCIR.max.y <= _hoops_ARCIR.min.y)
		_hoops_IRCIR = 0;
	else if (_hoops_PRCIR.min.y>= _hoops_ARCIR.max.y)
		_hoops_IRCIR = 2;
	else
		_hoops_IRCIR = 1;

	if (_hoops_PRCIR.max.z <= _hoops_ARCIR.min.z)
		_hoops_CRCIR = 0;
	else if (_hoops_PRCIR.min.z>= _hoops_ARCIR.max.z)
		_hoops_CRCIR = 2;
	else
		_hoops_CRCIR = 1;

	int _hoops_HGII = _hoops_HRCIR + (_hoops_IRCIR*3) + (_hoops_CRCIR*9);

	switch (_hoops_HGII) {
	case 0:
		return _hoops_SRCIR(Point(_hoops_ARCIR.min.x, _hoops_ARCIR.min.y, _hoops_ARCIR.min.z), Point(_hoops_PRCIR.max.x, _hoops_PRCIR.max.y, _hoops_PRCIR.max.z));
		break;
	case 1:
		return _hoops_SRCIR(Point(0, _hoops_ARCIR.min.y, _hoops_ARCIR.min.z), Point(0, _hoops_PRCIR.max.y, _hoops_PRCIR.max.z));
		break;
	case 2:
		return _hoops_SRCIR(Point(_hoops_ARCIR.max.x, _hoops_ARCIR.min.y, _hoops_ARCIR.min.z),  Point(_hoops_PRCIR.min.x,_hoops_PRCIR.max.y,_hoops_PRCIR.max.z));
		break;

	case 3:
		return _hoops_SRCIR(Point(_hoops_ARCIR.min.x, 0, _hoops_ARCIR.min.z), Point(_hoops_PRCIR.max.x, 0, _hoops_PRCIR.max.z));
		break;
	case 4:
		return _hoops_SRCIR(Point(0, 0, _hoops_ARCIR.min.z), Point(0,0,_hoops_PRCIR.max.z));
		break;
	case 5:
		return _hoops_SRCIR(Point(_hoops_ARCIR.max.x, 0, _hoops_ARCIR.min.z), Point(_hoops_PRCIR.min.x,0,_hoops_PRCIR.max.z));
		break;

	case 6:
		return _hoops_SRCIR(Point(_hoops_ARCIR.min.x, _hoops_ARCIR.max.y, _hoops_ARCIR.min.z), Point(_hoops_PRCIR.max.x, _hoops_PRCIR.min.y, _hoops_PRCIR.max.z));
		break;
	case 7:
		return _hoops_SRCIR(Point(0, _hoops_ARCIR.max.y, _hoops_ARCIR.min.z), Point(0,_hoops_PRCIR.min.y,_hoops_PRCIR.max.z));
		break;
	case 8:
		return _hoops_SRCIR(Point(_hoops_ARCIR.max.x, _hoops_ARCIR.max.y, _hoops_ARCIR.min.z), Point(_hoops_PRCIR.min.x,_hoops_PRCIR.min.y,_hoops_PRCIR.max.z));
		break;

	case 9:
		return _hoops_SRCIR(Point(_hoops_ARCIR.min.x, _hoops_ARCIR.min.y, 0), Point(_hoops_PRCIR.max.x, _hoops_PRCIR.max.y, 0));
		break;
	case 10:
		return _hoops_SRCIR(Point(0, _hoops_ARCIR.min.y, 0), Point(0,_hoops_PRCIR.max.y,0));
		break;
	case 11:
		return _hoops_SRCIR(Point(_hoops_ARCIR.max.x, _hoops_ARCIR.min.y, 0), Point(_hoops_PRCIR.min.x,_hoops_PRCIR.max.y,0));
		break;

	case 12:
		return _hoops_SRCIR(Point(_hoops_ARCIR.min.x, 0, 0), Point(_hoops_PRCIR.max.x, 0, 0));
		break;
	case 13:
		return 0.0f; //_hoops_ASRC _hoops_GACIR(_hoops_RACIR(0, 0, 0), _hoops_RACIR(0,0,0));
		break;
	case 14:
		return _hoops_SRCIR(Point(_hoops_ARCIR.max.x, 0, 0), Point(_hoops_PRCIR.min.x,0,0));
		break;

	case 15:
		return _hoops_SRCIR(Point(_hoops_ARCIR.min.x, _hoops_ARCIR.max.y, 0), Point(_hoops_PRCIR.max.x, _hoops_PRCIR.min.y, 0));
		break;
	case 16:
		return _hoops_SRCIR(Point(0, _hoops_ARCIR.max.y, 0), Point(0,_hoops_PRCIR.min.y,0));
		break;
	case 17:
		return _hoops_SRCIR(Point(_hoops_ARCIR.max.x, _hoops_ARCIR.max.y, 0), Point(_hoops_PRCIR.min.x,_hoops_PRCIR.min.y,0));
		break;

	case 18:
		return _hoops_SRCIR(Point(_hoops_ARCIR.min.x, _hoops_ARCIR.min.y, _hoops_ARCIR.max.z), Point(_hoops_PRCIR.max.x, _hoops_PRCIR.max.y, _hoops_PRCIR.min.z));
		break;
	case 19:
		return _hoops_SRCIR(Point(0, _hoops_ARCIR.min.y, _hoops_ARCIR.max.z), Point(0,_hoops_PRCIR.max.y,_hoops_PRCIR.min.z));
		break;
	case 20:
		return _hoops_SRCIR(Point(_hoops_ARCIR.max.x, _hoops_ARCIR.min.y, _hoops_ARCIR.max.z), Point(_hoops_PRCIR.min.x,_hoops_PRCIR.max.y,_hoops_PRCIR.min.z));
		break;

	case 21:
		return _hoops_SRCIR(Point(_hoops_ARCIR.min.x, 0, _hoops_ARCIR.max.z), Point(_hoops_PRCIR.max.x, 0, _hoops_PRCIR.min.z));
		break;
	case 22:
		return _hoops_SRCIR(Point(0, 0, _hoops_ARCIR.max.z), Point(0,0,_hoops_PRCIR.min.z));
		break;
	case 23:
		return _hoops_SRCIR(Point(_hoops_ARCIR.max.x, 0, _hoops_ARCIR.max.z), Point(_hoops_PRCIR.min.x,0,_hoops_PRCIR.min.z));
		break;

	case 24:
		return _hoops_SRCIR(Point(_hoops_ARCIR.min.x, _hoops_ARCIR.max.y, _hoops_ARCIR.max.z), Point(_hoops_PRCIR.max.x, _hoops_PRCIR.min.y, _hoops_PRCIR.min.z));
		break;
	case 25:
		return _hoops_SRCIR(Point(0, _hoops_ARCIR.max.y, _hoops_ARCIR.max.z), Point(0,_hoops_PRCIR.min.y,_hoops_PRCIR.min.z));
		break;
	case 26:
		return _hoops_SRCIR(Point(_hoops_ARCIR.max.x, _hoops_ARCIR.max.y, _hoops_ARCIR.max.z), Point(_hoops_PRCIR.min.x,_hoops_PRCIR.min.y,_hoops_PRCIR.min.z));
		break;
	}

	return 0.0f;
}


GLOBAL_FUNCTION float HI_Cuboid_To_Cuboid_Max_Distance(
	_hoops_SASC const & _hoops_ARCIR,
	_hoops_SASC const & _hoops_PRCIR)
{
	_hoops_SASC c = _hoops_AACIR(_hoops_ARCIR, _hoops_PRCIR);
	Vector v = c.max - c.min;
	return v.length();
}


GLOBAL_FUNCTION float HI_Cuboid_To_Point_Distance(_hoops_SASC const & cuboid, Point const & point)
{
	Point _hoops_HGII;
	if (point.x <= cuboid.min.x)
		_hoops_HGII.x = cuboid.min.x;
	else if (point.x >= cuboid.max.x)
		_hoops_HGII.x = cuboid.max.x;
	else
		_hoops_HGII.x = point.x;

	if (point.y <= cuboid.min.y)
		_hoops_HGII.y = cuboid.min.y;
	else if (point.y >= cuboid.max.y)
		_hoops_HGII.y = cuboid.max.y;
	else
		_hoops_HGII.y = point.y;

	if (point.z <= cuboid.min.z)
		_hoops_HGII.z = cuboid.min.z;
	else if (point.z >= cuboid.max.z)
		_hoops_HGII.z = cuboid.max.z;
	else
		_hoops_HGII.z = point.z;

	return Vector(_hoops_HGII - point).length();
}



Int_Rectangle::Int_Rectangle (_hoops_PACIR const & _hoops_HACIR)
: left ((int)_hoops_HACIR.left), right ((int)_hoops_HACIR.right), bottom ((int)_hoops_HACIR.bottom), top ((int)_hoops_HACIR.top) {}


_hoops_SASC::_hoops_SASC(_hoops_CAIS const & sphere) {
	min = Point(sphere.center.x - sphere.radius, sphere.center.y - sphere.radius, sphere.center.z - sphere.radius);
	max = Point(sphere.center.x + sphere.radius, sphere.center.y + sphere.radius, sphere.center.z + sphere.radius);
}


#define _hoops_IACIR (1e10f)
#define _hoops_CACIR (1e-5f)
#define _hoops_SACIR (1e-12)

bool _hoops_GPCIR::_hoops_RPCIR (_hoops_APCIR const & start, _hoops_PPCIR const & direction) const
{
	if (_hoops_HPCIR(start))
		return true;

	double _hoops_IPCIR = -_hoops_IACIR;
	double _hoops_CPCIR = 1.0;
	if (direction.x > _hoops_CACIR) {
		double t = (min.x - start.x)/direction.x;
		if (t > _hoops_IPCIR)
			_hoops_IPCIR = t;
		if (-min.x > _hoops_CPCIR)
			_hoops_CPCIR = -min.x;
		if (start.x > _hoops_CPCIR)
			_hoops_CPCIR = start.x;
	}
	else if (direction.x < -_hoops_CACIR) {
		double t = (max.x - start.x)/direction.x;
		if (t > _hoops_IPCIR)
			_hoops_IPCIR = t;
		if (max.x > _hoops_CPCIR)
			_hoops_CPCIR = max.x;
		if (start.x > _hoops_CPCIR)
			_hoops_CPCIR = start.x;
	}

	if (direction.y > _hoops_CACIR) {
		double t = (min.y - start.y)/direction.y;
		if (t > _hoops_IPCIR)
			_hoops_IPCIR = t;
		if (-min.y > _hoops_CPCIR)
			_hoops_CPCIR = -min.y;
		if (start.y > _hoops_CPCIR)
			_hoops_CPCIR = start.y;
	}
	else if (direction.y < -_hoops_CACIR) {
		double t = (max.y - start.y)/direction.y;
		if (t > _hoops_IPCIR)
			_hoops_IPCIR = t;
		if (max.y > _hoops_CPCIR)
			_hoops_CPCIR = max.y;
		if (start.y > _hoops_CPCIR)
			_hoops_CPCIR = start.y;
	}

	if (direction.z > _hoops_CACIR) {
		double t = (min.z - start.z)/direction.z;
		if (t > _hoops_IPCIR)
			_hoops_IPCIR = t;
		if (-min.z > _hoops_CPCIR)
			_hoops_CPCIR = -min.z;
		if (start.z > _hoops_CPCIR)
			_hoops_CPCIR = start.z;
	}
	else if (direction.z < -_hoops_CACIR) {
		double t = (max.z - start.z)/direction.z;
		if (t > _hoops_IPCIR)
			_hoops_IPCIR = t;
		if (max.z > _hoops_CPCIR)
			_hoops_CPCIR = max.z;
		if (start.z > _hoops_CPCIR)
			_hoops_CPCIR = start.z;
	}

	_hoops_APCIR _hoops_SPCIR = start + direction * _hoops_IPCIR;
	if (_hoops_HPCIR(_hoops_SPCIR, _hoops_SACIR*_hoops_CPCIR))
		return true;

	return false;
}


bool _hoops_SASC::_hoops_RPCIR (Point const & start, Vector const & direction) const
{
	if (_hoops_HPCIR(start))
		return true;

	float _hoops_IPCIR = -_hoops_IACIR;
	float _hoops_CPCIR = 1.0f;
	if (direction.x > _hoops_CACIR) {
		float t = (min.x - start.x)/direction.x;
		if (t > _hoops_IPCIR) 
			_hoops_IPCIR = t;
		if (-min.x > _hoops_CPCIR)
			_hoops_CPCIR = -min.x;
		if (start.x > _hoops_CPCIR)
			_hoops_CPCIR = start.x;
	}
	else if (direction.x < -_hoops_CACIR) {
		float t = (max.x - start.x)/direction.x;
		if (t > _hoops_IPCIR)
			_hoops_IPCIR = t;
		if (max.x > _hoops_CPCIR)
			_hoops_CPCIR = max.x;
		if (start.x > _hoops_CPCIR)
			_hoops_CPCIR = start.x;
	}

	if (direction.y > _hoops_CACIR) {
		float t = (min.y - start.y)/direction.y;
		if (t > _hoops_IPCIR)
			_hoops_IPCIR = t;
		if (-min.y > _hoops_CPCIR)
			_hoops_CPCIR = -min.y;
		if (start.y > _hoops_CPCIR)
			_hoops_CPCIR = start.y;
	}
	else if (direction.y < -_hoops_CACIR) {
		float t = (max.y - start.y)/direction.y;
		if (t > _hoops_IPCIR)
			_hoops_IPCIR = t;
		if (max.y > _hoops_CPCIR)
			_hoops_CPCIR = max.y;
		if (start.y > _hoops_CPCIR)
			_hoops_CPCIR = start.y;
	}

	if (direction.z > _hoops_CACIR) {
		float t = (min.z - start.z)/direction.z;
		if (t > _hoops_IPCIR)
			_hoops_IPCIR = t;
		if (-min.z > _hoops_CPCIR)
			_hoops_CPCIR = -min.z;
		if (start.z > _hoops_CPCIR)
			_hoops_CPCIR = start.z;
	}
	else if (direction.z < -_hoops_CACIR) {
		float t = (max.z - start.z)/direction.z;
		if (t > _hoops_IPCIR)
			_hoops_IPCIR = t;
		if (max.z > _hoops_CPCIR)
			_hoops_CPCIR = max.z;
		if (start.z > _hoops_CPCIR)
			_hoops_CPCIR = start.z;
	}

	/* _hoops_HPPR _hoops_GICS _hoops_GGR _hoops_GHGPR _hoops_GPPS _hoops_RPP _hoops_SR _hoops_CHR _hoops_HAH _hoops_SGIP _hoops_SGGR */
	if (_hoops_IPCIR > 100.0f)
		return _hoops_GPCIR(*this)._hoops_RPCIR(_hoops_APCIR(start),_hoops_PPCIR(direction));

	Point _hoops_SPCIR = start + direction * _hoops_IPCIR;
	if (_hoops_HPCIR(_hoops_SPCIR, _hoops_CACIR*_hoops_CPCIR))
		return true;

	return false;
}




#define _hoops_GHCIR 0.1f
local bool _hoops_RHCIR(_hoops_RPRA const *matrix)
{
	for (int i = 0; i < 3; i++) {
		int count = 0;
		for (int j = 0; j < 3; j++) {
			float _hoops_HAGR = matrix[i][j];
			if (_hoops_HAGR < -_hoops_GHCIR || _hoops_HAGR > _hoops_GHCIR)
				count++;
		}
		if (count > 1)
			return true;
	}
	return false;
}

_hoops_SASC _hoops_SASC::_hoops_SCIS(float const * _hoops_AHCIR) const
{
	_hoops_RPRA const *	matrix = (_hoops_RPRA const *)_hoops_AHCIR;

	if (matrix[0][1] != 0.0f || matrix[0][2] != 0.0f ||
		matrix[1][0] != 0.0f || matrix[1][2] != 0.0f ||
		matrix[2][0] != 0.0f || matrix[2][1] != 0.0f) {

		if (_hoops_RHCIR (matrix)) {
			Vector			_hoops_PHCIR = max - min;
			Point			center = min + 0.5f * _hoops_PHCIR;

			float length = _hoops_IAAA(matrix[0][0] * matrix[0][0] + matrix[0][1] * matrix[0][1] + matrix[0][2] * matrix[0][2],
								matrix[1][0] * matrix[1][0] + matrix[1][1] * matrix[1][1] + matrix[1][2] * matrix[1][2],
								matrix[2][0] * matrix[2][0] +matrix[2][1] * matrix[2][1] + matrix[2][2] * matrix[2][2]);

			_hoops_CAIS	sphere;

			sphere.radius = 0.5f * _hoops_PHCIR.length() * _hoops_SGIHR(length);

			sphere.center.x = _hoops_HPRA (matrix, center);
			sphere.center.y = _hoops_IPRA (matrix, center);
			sphere.center.z = _hoops_CPRA (matrix, center);

			return _hoops_SASC(sphere);
		}
		else {
			Point	in[8], _hoops_PAGR[8];
			_hoops_GPSC(in);
			HI_Compute_Transformed_Points (8, in, _hoops_AHCIR, _hoops_PAGR);
			return _hoops_SASC(8, _hoops_PAGR);
		}
	}

	Point 	p[2];

	p[0].x = _hoops_HPRA (matrix, min);
	p[0].y = _hoops_IPRA (matrix, min);
	p[0].z = _hoops_CPRA (matrix, min);

	p[1].x = _hoops_HPRA (matrix, max);
	p[1].y = _hoops_IPRA (matrix, max);
	p[1].z = _hoops_CPRA (matrix, max);

	return _hoops_SASC(2, p);
}


_hoops_CAIS _hoops_CAIS::_hoops_SCIS(float const * _hoops_AHCIR) const
{
	_hoops_RPRA const *	matrix = (_hoops_RPRA const *)_hoops_AHCIR;

	Point _hoops_HHCIR;

	_hoops_HHCIR.x = _hoops_HPRA (matrix, center);
	_hoops_HHCIR.y = _hoops_IPRA (matrix, center);
	_hoops_HHCIR.z = _hoops_CPRA (matrix, center);

	float length = _hoops_IAAA(matrix[0][0] * matrix[0][0] + matrix[0][1] * matrix[0][1] + matrix[0][2] * matrix[0][2],
						matrix[1][0] * matrix[1][0] + matrix[1][1] * matrix[1][1] + matrix[1][2] * matrix[1][2],
						matrix[2][0] * matrix[2][0] +matrix[2][1] * matrix[2][1] + matrix[2][2] * matrix[2][2]);

	float _hoops_IHCIR = _hoops_SGIHR (length) * radius;

	return _hoops_CAIS(_hoops_HHCIR, _hoops_IHCIR);
}


_hoops_CHCIR * _hoops_CHCIR::_hoops_SCIS (float const * _hoops_AHCIR) const
{
	_hoops_CHCIR * temp = NEW(_hoops_CHCIR)();

	temp->_hoops_CGCIR = _hoops_CGCIR;
	temp->cuboid = cuboid._hoops_SCIS(_hoops_AHCIR);
	temp->sphere = sphere._hoops_SCIS(_hoops_AHCIR);
	temp->flags = flags;

	return temp;
}


float _hoops_CHCIR::_hoops_PGCIR() const
{
	if (BIT(flags, _hoops_AGCIR))
		return cuboid._hoops_PGCIR();
	else if (BIT(flags, _hoops_RGCIR))
		return sphere._hoops_PGCIR();

	float _hoops_SHCIR = cuboid._hoops_PGCIR();
	float _hoops_GICIR = sphere._hoops_PGCIR();

	if (_hoops_SHCIR <= _hoops_GICIR) {
		flags |= _hoops_AGCIR;
		return _hoops_SHCIR;
	}

	flags |= _hoops_RGCIR;
	return _hoops_GICIR;
}



bool _hoops_CHCIR::Merge (int count, Point const * points) {
	if (count == 0)
		return false;

	count = Abs (count);

	if (BIT (flags, Bounding_EMPTY)) {
		flags &= ~(Bounding_EMPTY|_hoops_RGCIR|_hoops_AGCIR);

		cuboid = _hoops_SASC(count, points);
		Point _hoops_RICIR = _hoops_AICIR(cuboid.min, cuboid.max);
		sphere = _hoops_CAIS(count, points, _hoops_RICIR);

		return true;
	}

	_hoops_SASC _hoops_PICIR = cuboid;
	_hoops_CAIS _hoops_HICIR = sphere;

	cuboid.Merge(count, points);
	sphere.Merge(count, points);

	if (_hoops_PICIR == cuboid &&
		_hoops_HICIR == sphere)
		return false;

	flags &= ~(_hoops_RGCIR|_hoops_AGCIR);

	return true;
}

bool _hoops_CHCIR::Merge (_hoops_SASC const & _hoops_IICIR) {
	if (BIT (flags, Bounding_EMPTY)) {
		flags &= ~(Bounding_EMPTY|_hoops_RGCIR|_hoops_AGCIR);

		cuboid = _hoops_IICIR;
		sphere = _hoops_CAIS(_hoops_IICIR);
		return true;
	}

	_hoops_SASC _hoops_PICIR = cuboid;
	_hoops_CAIS _hoops_HICIR = sphere;

	cuboid.Merge(_hoops_IICIR);
	sphere.Merge(_hoops_IICIR);

	if (_hoops_PICIR == cuboid &&
		_hoops_HICIR == sphere)
		return false;

	flags &= ~(_hoops_RGCIR|_hoops_AGCIR);

	return true;
}

bool _hoops_CHCIR::Merge (_hoops_CAIS const & _hoops_CICIR) {
	if (BIT (flags, Bounding_EMPTY)) {
		flags &= ~(Bounding_EMPTY|_hoops_RGCIR|_hoops_AGCIR);

		cuboid = _hoops_SASC(_hoops_CICIR);
		sphere = _hoops_CICIR;
		return true;
	}

	_hoops_SASC _hoops_PICIR = cuboid;
	_hoops_CAIS _hoops_HICIR = sphere;

	cuboid.Merge(_hoops_CICIR);
	sphere.Merge(_hoops_CICIR);

	if (_hoops_PICIR == cuboid &&
		_hoops_HICIR == sphere)
		return false;

	flags &= ~(_hoops_RGCIR|_hoops_AGCIR);

	return true;
}

bool _hoops_CHCIR::Merge (Bounding const & bounding) {
	if (bounding._hoops_HICAR())
		return false;

	if (BIT (flags, Bounding_EMPTY)) {
		flags = bounding->flags;
		flags &= ~Bounding_EMPTY;

		_hoops_CGCIR = bounding->_hoops_CGCIR;
		cuboid = bounding->cuboid;
		sphere = bounding->sphere;
		return true;
	}

	//_hoops_SICIR = _hoops_IASC->_hoops_SICIR;

	_hoops_SASC _hoops_PICIR = cuboid;
	_hoops_CAIS _hoops_HICIR = sphere;

	cuboid.Merge(bounding->cuboid);
	sphere.Merge(bounding->sphere);

	if (_hoops_PICIR == cuboid &&
		_hoops_HICIR == sphere)
		return false;

	flags &= ~(_hoops_RGCIR|_hoops_AGCIR);

	return true;
}


#if 0

Internal_Bounding_Cuboid::Internal_Bounding_Cuboid ()
	: _hoops_GCCIR (Bounding_CUBOID), _hoops_RCCIR (-1.0f) {}

Internal_Bounding_Cuboid::Internal_Bounding_Cuboid (Bounding const & _hoops_HACIR)
	: _hoops_GCCIR (Bounding_CUBOID), _hoops_RCCIR (-1.0f) {
	if (_hoops_HACIR != null) {
		flags = _hoops_HACIR->flags;

		if (BIT (flags, Bounding_EMPTY)) {}
		else if (_hoops_HACIR->type == Bounding_SPHERE) {
			_hoops_ACCIR const &			sphere = (_hoops_ACCIR const &)_hoops_HACIR;

			min.x = sphere->data.center.x - sphere->data.radius;
			min.y = sphere->data.center.y - sphere->data.radius;
			min.z = sphere->data.center.z - sphere->data.radius;
			max.x = sphere->data.center.x + sphere->data.radius;
			max.y = sphere->data.center.y + sphere->data.radius;
			max.z = sphere->data.center.z + sphere->data.radius;

			_hoops_CGCIR = sphere->_hoops_CGCIR * (float)(HK_Pi / 6.0);	// * _hoops_CHHRR->_hoops_IGGRR() / _hoops_IGGRR(); _hoops_CAS _hoops_HRGR (2_hoops_PCCIR) _hoops_HCCIR
		}
		// _hoops_SHS _hoops_CGH _hoops_HAR _hoops_SHH _hoops_GHHS _hoops_PIGS...
	}
}

Internal_Bounding_Cuboid * Internal_Bounding_Cuboid::_hoops_ICCIR () const {
	return new Internal_Bounding_Cuboid (*this);
}


bool Internal_Bounding_Cuboid::Add_Bounding (Bounding const & bounding) alter {
	bool		_hoops_CCCIR = false;

	if (!bounding._hoops_HICAR()) switch (bounding->type) {
		case Bounding_CUBOID: {
			_hoops_SCCIR const &			cuboid = (_hoops_SCCIR const &)bounding;

			if (BIT (flags, Bounding_EMPTY)) {
				flags = cuboid->flags;
				min = cuboid->min;
				max = cuboid->max;
				_hoops_CGCIR = cuboid->_hoops_CGCIR;
				_hoops_RCCIR = cuboid->_hoops_RCCIR;
				_hoops_CCCIR = true;
			}
			else {
				float						_hoops_GSCIR = _hoops_PGCIR();
				Point						_hoops_RSCIR(cuboid->min.x, cuboid->min.y, cuboid->min.z),
											_hoops_ASCIR(cuboid->max.x, cuboid->max.y, cuboid->max.z);

				if (!ALLBITS (flags, cuboid->flags)) {
					flags |= cuboid->flags;
					_hoops_CCCIR = true;
				}

				if (cuboid->min.x < min.x) {
					min.x = cuboid->min.x;
					_hoops_RSCIR.x = min.x;
					_hoops_CCCIR = true;
				}
				if (cuboid->max.x > max.x) {
					max.x = cuboid->max.x;
					_hoops_ASCIR.x = max.x;
					_hoops_CCCIR = true;
				}

				if (cuboid->min.y < min.y) {
					min.y = cuboid->min.y;
					_hoops_RSCIR.y = min.y;
					_hoops_CCCIR = true;
				}
				if (cuboid->max.y > max.y) {
					max.y = cuboid->max.y;
					_hoops_ASCIR.y = max.y;
					_hoops_CCCIR = true;
				}

				if (cuboid->min.z < min.z) {
					min.z = cuboid->min.z;
					_hoops_RSCIR.z = min.z;
					_hoops_CCCIR = true;
				}
				if (cuboid->max.z > max.z) {
					max.z = cuboid->max.z;
					_hoops_ASCIR.z = max.z;
					_hoops_CCCIR = true;
				}
				if (_hoops_CCCIR)
					_hoops_RCCIR = -1.0f;		// _hoops_HRCI

				float						_hoops_PSCIR = _hoops_PGCIR();

				if (_hoops_PSCIR > 0.0f) {
					float					_hoops_HSCIR=_hoops_CGCIR;

					if (_hoops_GSCIR > 0.0f)
						_hoops_CGCIR *= _hoops_GSCIR / _hoops_PSCIR;
					else
						_hoops_CGCIR = 0.1f;

					float					_hoops_ISCIR = bounding->_hoops_PGCIR();
					float					_hoops_CSCIR = (_hoops_ASCIR.x-_hoops_RSCIR.x)
												* (_hoops_ASCIR.y-_hoops_RSCIR.y)
												* (_hoops_ASCIR.z-_hoops_RSCIR.z);

					if (_hoops_ISCIR > 0.0f)
						_hoops_CGCIR += _hoops_ISCIR / _hoops_PSCIR * bounding->_hoops_CGCIR
									- _hoops_CSCIR / _hoops_PSCIR * _hoops_AHIA(_hoops_HSCIR, bounding->_hoops_CGCIR);
					else
						_hoops_CGCIR += 0.1f * bounding->_hoops_CGCIR;

					_hoops_CGCIR = _hoops_AHIA (_hoops_CGCIR, 1.0f);
				}
			}
			if (min.z != 0.0f || max.z != 0.0f)
				type = Bounding_CUBOID;		// _hoops_IRHH _hoops_RCRR _hoops_IRS "_hoops_ARRGR" _hoops_SAGGR _hoops_SHPS
		}	break;

		case Bounding_SPHERE: {
			_hoops_ACCIR const &			sphere = (_hoops_ACCIR const &)bounding;

			if (BIT (flags, Bounding_EMPTY)) {
				flags = sphere->flags;
				min.x = sphere->data.center.x - sphere->data.radius;
				min.y = sphere->data.center.y - sphere->data.radius;
				min.z = sphere->data.center.z - sphere->data.radius;
				max.x = sphere->data.center.x + sphere->data.radius;
				max.y = sphere->data.center.y + sphere->data.radius;
				max.z = sphere->data.center.z + sphere->data.radius;
				_hoops_CGCIR = sphere->_hoops_CGCIR * (float)(HK_Pi / 6.0);
				_hoops_CCCIR = true;
			}
			else {
				float						_hoops_GSCIR = _hoops_PGCIR();
				Point						_hoops_RSCIR(sphere->data.center.x - sphere->data.radius,
														sphere->data.center.y - sphere->data.radius,
														sphere->data.center.z - sphere->data.radius),
											_hoops_ASCIR(sphere->data.center.x + sphere->data.radius,
														sphere->data.center.y + sphere->data.radius,
														sphere->data.center.z + sphere->data.radius);

				if (!ALLBITS (flags, sphere->flags)) {
					flags |= sphere->flags;
					_hoops_CCCIR = true;
				}

				if (sphere->data.center.x - sphere->data.radius < min.x) {
					min.x = sphere->data.center.x - sphere->data.radius;
					_hoops_RSCIR.x = min.x;
					_hoops_CCCIR = true;
				}
				if (sphere->data.center.x + sphere->data.radius > max.x) {
					max.x = sphere->data.center.x + sphere->data.radius;
					_hoops_ASCIR.x = max.x;
					_hoops_CCCIR = true;
				}

				if (sphere->data.center.y - sphere->data.radius < min.y) {
					min.y = sphere->data.center.y - sphere->data.radius;
					_hoops_RSCIR.y = min.y;
					_hoops_CCCIR = true;
				}
				if (sphere->data.center.y + sphere->data.radius > max.y) {
					max.y = sphere->data.center.y + sphere->data.radius;
					_hoops_ASCIR.y = max.y;
					_hoops_CCCIR = true;
				}

				if (sphere->data.center.z - sphere->data.radius < min.z) {
					min.z = sphere->data.center.z - sphere->data.radius;
					_hoops_RSCIR.z = min.z;
					_hoops_CCCIR = true;
				}
				if (sphere->data.center.z + sphere->data.radius > max.z) {
					max.z = sphere->data.center.z + sphere->data.radius;
					_hoops_ASCIR.z = max.z;
					_hoops_CCCIR = true;
				}

				float						_hoops_PSCIR = _hoops_PGCIR();

				if (_hoops_PSCIR > 0.0f) {
					float					_hoops_HSCIR=_hoops_CGCIR;

					if (_hoops_GSCIR > 0.0f)
						_hoops_CGCIR *= _hoops_GSCIR / _hoops_PSCIR;
					else
						_hoops_CGCIR = 0.1f;

					float					_hoops_ISCIR = bounding->_hoops_PGCIR();
					float					_hoops_CSCIR = (_hoops_ASCIR.x-_hoops_RSCIR.x)
												* (_hoops_ASCIR.y-_hoops_RSCIR.y)
												* (_hoops_ASCIR.z-_hoops_RSCIR.z);

					if (_hoops_ISCIR > 0.0f)
						_hoops_CGCIR += _hoops_ISCIR / _hoops_PSCIR * bounding->_hoops_CGCIR
									- _hoops_CSCIR / _hoops_PSCIR * _hoops_AHIA(_hoops_HSCIR, bounding->_hoops_CGCIR);
					else
						_hoops_CGCIR += 0.1f * _hoops_CGCIR;

					_hoops_CGCIR = _hoops_AHIA (_hoops_CGCIR, 1.0f);
				}
			}
			_hoops_RCCIR = -1.0f;			// _hoops_HRCI -- "_hoops_PSAA" _hoops_IIGR _hoops_IPIS _hoops_HAR _hoops_RH _hoops_PSHR _hoops_GAR _hoops_SGS _hoops_IIGR _hoops_RH _hoops_PSSPR _hoops_CHHRR
			type = Bounding_CUBOID;		// _hoops_IRHH _hoops_RCRR _hoops_IRS "_hoops_ARRGR" _hoops_SAGGR _hoops_SHPS
		}	break;
	}

	return _hoops_CCCIR;
}

#define _hoops_GHCIR 0.1f
bool _hoops_RHCIR(_hoops_RPRA const *matrix)
{
	int i, j, count;
	float _hoops_HAGR;

	for (i = 0; i < 3; i++) {
		count = 0;
		for (j = 0; j < 3; j++) {
			_hoops_HAGR = matrix[i][j];
			if (_hoops_HAGR < -_hoops_GHCIR || _hoops_HAGR > _hoops_GHCIR)
				count++;
		}
		if (count > 1)
			return true;
	}
	return false;
}


Bounding Internal_Bounding_Cuboid::_hoops_SCIS (float const * _hoops_SSCIR) const {
	_hoops_RPRA const *				matrix = (_hoops_RPRA const *)_hoops_SSCIR;

	if (BIT (flags, Bounding_EMPTY)) {
		_hoops_SCCIR	_hoops_GGSIR = _hoops_SCCIR::Create();
		_hoops_GGSIR->flags = flags;
		return _hoops_GGSIR;
	}

	if (matrix[0][1] != 0.0f || matrix[0][2] != 0.0f ||
		matrix[1][0] != 0.0f || matrix[1][2] != 0.0f ||
		matrix[2][0] != 0.0f || matrix[2][1] != 0.0f) {

		if (_hoops_RHCIR (matrix)) {
			_hoops_ACCIR				sphere = _hoops_ACCIR::Create();
			Vector						_hoops_PHCIR = max - min;
			Point						center = min + 0.5f * _hoops_PHCIR;
			float						length, tmp;

			sphere->flags = flags;

			sphere->data.center.x = _hoops_HPRA (matrix, center);
			sphere->data.center.y = _hoops_IPRA (matrix, center);
			sphere->data.center.z = _hoops_CPRA (matrix, center);

			length = matrix[0][0] * matrix[0][0] +
					 matrix[0][1] * matrix[0][1] +
					 matrix[0][2] * matrix[0][2];
			tmp	   = matrix[1][0] * matrix[1][0] +
					 matrix[1][1] * matrix[1][1] +
					 matrix[1][2] * matrix[1][2];
			if (tmp > length) length = tmp;
			tmp	   = matrix[2][0] * matrix[2][0] +
					 matrix[2][1] * matrix[2][1] +
					 matrix[2][2] * matrix[2][2];
			if (tmp > length) length = tmp;

			sphere->data.radius = radius();			// _hoops_RGSIR _hoops_IH _hoops_RH _hoops_SICIR _hoops_SHRRR

			//_hoops_HAH _hoops_HIAC
			//_hoops_CHHRR->_hoops_SICIR = _hoops_SICIR * _hoops_IGGRR() / _hoops_CHHRR->_hoops_IGGRR();
			sphere->_hoops_CGCIR = _hoops_CGCIR * 0.25f;

			sphere->data.radius *= _hoops_SGIHR (length);	// _hoops_PSP _hoops_RH _hoops_HPHR _hoops_SPR

			return sphere;
		}
		else {
			Point						pts[8], xpts[8];

			pts[0].x = min.x;	 pts[0].y = min.y;	  pts[0].z = min.z;
			pts[1].x = min.x;	 pts[1].y = min.y;	  pts[1].z = max.z;
			pts[2].x = min.x;	 pts[2].y = max.y;	  pts[2].z = min.z;
			pts[3].x = min.x;	 pts[3].y = max.y;	  pts[3].z = max.z;
			pts[4].x = max.x;	 pts[4].y = min.y;	  pts[4].z = min.z;
			pts[5].x = max.x;	 pts[5].y = min.y;	  pts[5].z = max.z;
			pts[6].x = max.x;	 pts[6].y = max.y;	  pts[6].z = min.z;
			pts[7].x = max.x;	 pts[7].y = max.y;	  pts[7].z = max.z;
			for (int i = 0; i < 8; i++) {
				xpts[i].x = _hoops_HPRA (matrix, pts[i]);
				xpts[i].y = _hoops_IPRA (matrix, pts[i]);
				xpts[i].z = _hoops_CPRA (matrix, pts[i]);
			}

			_hoops_SCCIR				cuboid = _hoops_SCCIR::Create(8, xpts);

			cuboid->flags = flags;

			return cuboid;
		}
	}
	else {
		_hoops_SCCIR					cuboid = _hoops_SCCIR::Create();
		float							x1, x2, _hoops_AGSIR, _hoops_PGSIR, _hoops_HGSIR, _hoops_IGSIR;

		cuboid->flags = flags;

		x1 = _hoops_HPRA (matrix, min);
		x2 = _hoops_HPRA (matrix, max);

		_hoops_AGSIR = _hoops_IPRA (matrix, min);
		_hoops_PGSIR = _hoops_IPRA (matrix, max);

		_hoops_HGSIR = _hoops_CPRA (matrix, min);
		_hoops_IGSIR = _hoops_CPRA (matrix, max);

		if (x1 < x2) {
			cuboid->min.x = x1;
			cuboid->max.x = x2;
		}
		else {
			cuboid->min.x = x2;
			cuboid->max.x = x1;
		}

		if (_hoops_AGSIR < _hoops_PGSIR) {
			cuboid->min.y = _hoops_AGSIR;
			cuboid->max.y = _hoops_PGSIR;
		}
		else {
			cuboid->min.y = _hoops_PGSIR;
			cuboid->max.y = _hoops_AGSIR;
		}

		if (_hoops_HGSIR < _hoops_IGSIR) {
			cuboid->min.z = _hoops_HGSIR;
			cuboid->max.z = _hoops_IGSIR;
		}
		else {
			cuboid->min.z = _hoops_IGSIR;
			cuboid->max.z = _hoops_HGSIR;
		}

		cuboid->_hoops_CGCIR = _hoops_CGCIR;

		return cuboid;
	}
}

float Internal_Bounding_Cuboid::_hoops_PGCIR () const {
	return (max.x - min.x) * (max.y - min.y) * (max.z - min.z);
}


Internal_Bounding_Sphere::Internal_Bounding_Sphere ()
	: _hoops_GCCIR (Bounding_SPHERE) {}

Internal_Bounding_Sphere::Internal_Bounding_Sphere (Bounding const & _hoops_HACIR)
	: _hoops_GCCIR (Bounding_SPHERE) {
	if (_hoops_HACIR != null) {
		flags = _hoops_HACIR->flags;

		if (BIT (flags, Bounding_EMPTY)) {}
		else if (_hoops_HACIR->type == Bounding_CUBOID) {
			_hoops_SCCIR const &			cuboid = (_hoops_SCCIR const &)_hoops_HACIR;
			Vector							d = cuboid->max - cuboid->min;

			data.center = cuboid->min + 0.5f * d;
			data.radius = 0.5f * d.length();

			_hoops_CGCIR = cuboid->_hoops_CGCIR * cuboid->_hoops_PGCIR() / _hoops_PGCIR();
		}
		// _hoops_SHS _hoops_CGH _hoops_HAR _hoops_SHH _hoops_GHHS _hoops_PIGS...
	}
}

Internal_Bounding_Sphere * Internal_Bounding_Sphere::_hoops_ICCIR () const {
	return new Internal_Bounding_Sphere (*this);
}

bool Internal_Bounding_Sphere::Add_Bounding (Bounding const & bounding) alter {
	bool		_hoops_CCCIR = false;

	if (!bounding._hoops_HICAR()) switch (bounding->type) {
		case Bounding_CUBOID: {
			_hoops_SCCIR const &			cuboid = (_hoops_SCCIR const &)bounding;
			Vector							_hoops_CCSAR = cuboid->max - cuboid->min;
			Point							_hoops_GPIS = cuboid->min + 0.5f * _hoops_CCSAR;
			float							_hoops_CRAIR = _hoops_CCSAR.length() * 0.5f;

			if (BIT (flags, Bounding_EMPTY)) {
				flags = cuboid->flags;
				data.center.x = _hoops_GPIS.x;
				data.center.y = _hoops_GPIS.y;
				data.center.z = _hoops_GPIS.z;
				data.radius = _hoops_CRAIR;
				_hoops_CGCIR = cuboid->_hoops_CGCIR * cuboid->_hoops_PGCIR() / _hoops_PGCIR();
				_hoops_CCCIR = true;
			}
			else {
				float						_hoops_GSCIR = _hoops_PGCIR();

				if (!ALLBITS (flags, cuboid->flags)) {
					flags |= cuboid->flags;
					_hoops_CCCIR = true;
				}

				_hoops_CCSAR = _hoops_GPIS - data.center;
				float						_hoops_CGSIR = _hoops_CCSAR.length();
				float						_hoops_SGSIR = _hoops_AHIA(_hoops_CRAIR, data.radius);

				if (_hoops_CGSIR + _hoops_CRAIR > data.radius) {
					if (_hoops_CGSIR + data.radius > _hoops_CRAIR) {
						float			t = 0.5f * (_hoops_CRAIR + _hoops_CGSIR - data.radius);

						data.center += t * _hoops_CCSAR._hoops_AAIAR();
						data.radius += t;
						_hoops_SGSIR = (data.radius + _hoops_CRAIR - _hoops_CGSIR) * 0.5f;
					}
					else {
						data.center = _hoops_GPIS;
						data.radius = _hoops_CRAIR;
					}

					_hoops_CCCIR = true;
				}

				float						_hoops_PSCIR = _hoops_PGCIR();

				if (_hoops_PSCIR > 0.0f) {
					float					_hoops_HSCIR = _hoops_CGCIR;
					if (_hoops_GSCIR > 0.0f)
						_hoops_CGCIR *= _hoops_GSCIR / _hoops_PSCIR;
					else
						_hoops_CGCIR = 0.1f;

					float					_hoops_ISCIR = bounding->_hoops_PGCIR();
					float					_hoops_CSCIR = 4.0f / 3.0f * HK_Pi
												* _hoops_SGSIR * _hoops_SGSIR * _hoops_SGSIR;

					if (_hoops_ISCIR > 0.0f)
						_hoops_CGCIR += _hoops_ISCIR / _hoops_PSCIR * bounding->_hoops_CGCIR
								- _hoops_CSCIR / _hoops_PSCIR * _hoops_AHIA(bounding->_hoops_CGCIR, _hoops_HSCIR);
					else
						_hoops_CGCIR += 0.1f * bounding->_hoops_CGCIR;

					_hoops_CGCIR = _hoops_AHIA (_hoops_CGCIR, 1.0f);
				}
			}
		}	break;

		case Bounding_SPHERE: {
			_hoops_ACCIR const &			sphere = (_hoops_ACCIR const &)bounding;

			if (BIT (flags, Bounding_EMPTY)) {
				flags = sphere->flags;
				data.center = sphere->data.center;
				data.radius = sphere->data.radius;
				_hoops_CCCIR = true;
			}
			else {
				float						_hoops_GSCIR = _hoops_PGCIR();

				if (!ALLBITS (flags, sphere->flags)) {
					flags |= sphere->flags;
					_hoops_CCCIR = true;
				}

				Vector						_hoops_CCSAR = sphere->data.center - data.center;
				float						_hoops_CGSIR = _hoops_CCSAR.length();
				float						_hoops_SGSIR = _hoops_AHIA(sphere->data.radius, data.radius);

				if (_hoops_CGSIR + sphere->data.radius > data.radius) {
					if (_hoops_CGSIR + data.radius > sphere->data.radius) {
						float			t = 0.5f * (sphere->data.radius + _hoops_CGSIR - data.radius);

						data.center += t * _hoops_CCSAR._hoops_AAIAR();
						data.radius += t;
						_hoops_SGSIR = (data.radius + sphere->data.radius - _hoops_CGSIR) * 0.5f;
					}
					else {
						data.center = sphere->data.center;
						data.radius = sphere->data.radius;
					}

					_hoops_CCCIR = true;
				}

				float						_hoops_PSCIR = _hoops_PGCIR();

				if (_hoops_PSCIR > 0.0f) {
					float					_hoops_HSCIR = _hoops_CGCIR;
					if (_hoops_GSCIR > 0.0f)
						_hoops_CGCIR *= _hoops_GSCIR / _hoops_PSCIR;
					else
						_hoops_CGCIR = 0.1f;

					float					_hoops_ISCIR = bounding->_hoops_PGCIR();
					float					_hoops_CSCIR = 4.0f / 3.0f * HK_Pi
												* _hoops_SGSIR * _hoops_SGSIR * _hoops_SGSIR;

					if (_hoops_ISCIR > 0.0f)
						_hoops_CGCIR += _hoops_ISCIR / _hoops_PSCIR * bounding->_hoops_CGCIR
								- _hoops_CSCIR / _hoops_PSCIR * _hoops_AHIA(bounding->_hoops_CGCIR, _hoops_HSCIR);
					else
						_hoops_CGCIR += 0.1f * bounding->_hoops_CGCIR;

					_hoops_CGCIR = _hoops_AHIA (_hoops_CGCIR, 1.0f);
				}
			}
		}	break;
	}

	return _hoops_CCCIR;
}

Bounding Internal_Bounding_Sphere::_hoops_SCIS (float const * _hoops_SSCIR) const {

	_hoops_RPRA const *				matrix = (_hoops_RPRA const *)_hoops_SSCIR;
	_hoops_ACCIR					sphere = _hoops_ACCIR::Create();
	float							length, tmp;

	sphere->flags = flags;

	if (BIT (flags, Bounding_EMPTY))
		return sphere;

	sphere->data.center.x = _hoops_HPRA (matrix, data.center);
	sphere->data.center.y = _hoops_IPRA (matrix, data.center);
	sphere->data.center.z = _hoops_CPRA (matrix, data.center);

	length = matrix[0][0] * matrix[0][0] +
			 matrix[0][1] * matrix[0][1] +
			 matrix[0][2] * matrix[0][2];
	tmp	   = matrix[1][0] * matrix[1][0] +
			 matrix[1][1] * matrix[1][1] +
			 matrix[1][2] * matrix[1][2];
	if (tmp > length) length = tmp;
	tmp	   = matrix[2][0] * matrix[2][0] +
			 matrix[2][1] * matrix[2][1] +
			 matrix[2][2] * matrix[2][2];
	if (tmp > length) length = tmp;

	sphere->data.radius = _hoops_SGIHR (length) * data.radius;

	sphere->_hoops_CGCIR = _hoops_CGCIR;

	return sphere;
}

float Internal_Bounding_Sphere::_hoops_PGCIR () const {
	return (4.0 / 3.0 * HK_Pi) * data.radius * data.radius * data.radius;
}
#endif

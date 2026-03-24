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
 * $Id: obf_tmp.txt 1.99 2010-10-06 19:16:36 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hpserror.h"


struct _hoops_RCCSA {
	int					point_count;
	Point const *		points;
	int					_hoops_ISPIR;
	float const *		radii;
	int					flags;

	Vector				_hoops_ACCSA[2];
	_hoops_SSPIR *		_hoops_CSPIR;
	float *				_hoops_GGHIR;
	float				_hoops_PCCSA;

	Point				_hoops_HCCSA[2];
	float				_hoops_ICCSA;
	_hoops_SSPIR			_hoops_CCCSA;

	Geometry *			geometry;
	int					_hoops_IGSSR;
	bool				_hoops_SCCSA;
	bool				_hoops_GSCSA;
};


#ifndef _hoops_PSPIR

local const _hoops_IGRCR _hoops_RSCSA[] = {
	{_hoops_ASCSA,			_hoops_GRRCR ("none"),	 _hoops_RRRCR, 0, false},
	{_hoops_ASCSA,			_hoops_GRRCR ("off"),	 _hoops_RRRCR, 0, false},
	{_hoops_IHHIA,		_hoops_GRRCR ("initial"),_hoops_RRRCR, 0, false},
	{_hoops_IHHIA,		_hoops_GRRCR ("begin"),	 _hoops_RRRCR, 0, false},
	{_hoops_IHHIA,		_hoops_GRRCR ("start"),	 _hoops_RRRCR, 0, false},
	{_hoops_IHHIA,		_hoops_GRRCR ("first"),	 _hoops_RRRCR, 0, false},
	{_hoops_SHHIA,		_hoops_GRRCR ("second"), _hoops_RRRCR, 0, false},
	{_hoops_SHHIA,		_hoops_GRRCR ("last"),	 _hoops_RRRCR, 0, false},
	{_hoops_SHHIA,		_hoops_GRRCR ("end"),	 _hoops_RRRCR, 0, false},
	{_hoops_SHHIA,		_hoops_GRRCR ("finish"), _hoops_RRRCR, 0, false},
	{_hoops_SHHIA,		_hoops_GRRCR ("final"),	 _hoops_RRRCR, 0, false},
	{_hoops_PSCSA,			_hoops_GRRCR ("both"),	 _hoops_RRRCR, 0, false},
	{_hoops_PSCSA,			_hoops_GRRCR ("all"),	 _hoops_RRRCR, 0, false},
	{_hoops_PSCSA,			_hoops_GRRCR ("on"),	 _hoops_RRRCR, 0, false},
};


local bool _hoops_HSCSA (
	_hoops_AIGPR *	_hoops_RIGC,
	int *					flags,
	char const *			list) 
{
	*flags = 0;

	if (list == null) {
		*flags = _hoops_ASCSA;
		return true;
	}

	_hoops_HIACR (_hoops_ISCSA, _hoops_RSCSA);

	Option_Value *			option_list;
	Option_Value *			option;

	if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_ISCSA), &option_list, _hoops_SIACR)) 
		return false;

	if ((option = option_list) != null) do switch (option->type->id) {
		case _hoops_ASCSA: {
			*flags = _hoops_ASCSA;			/* "_hoops_PIRC" _hoops_RCGPA _hoops_PSAP */
		}	break;

		default: {
			*flags |= option->type->id;			/* _hoops_HIASR _hoops_CSCSA */
		}
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);

	return true;
}


local void _hoops_SSCSA (
	Point const *			first,
	Point const *			_hoops_IAGRA,
	_hoops_SSPIR alter *		_hoops_CSPIR) {
	Vector					path;
	float					_hoops_ISCIA = 1e-5f;

	/* _hoops_RRP _hoops_HARGR _hoops_PSPAR _hoops_PGAP _hoops_CHR _hoops_GGSSA _hoops_AARGR _hoops_IS _hoops_RH _hoops_HGSI
	 * _hoops_CRAA _hoops_PPR _hoops_GRR _hoops_RII
	 */

	path = *_hoops_IAGRA - *first;

	/*	_hoops_AHGC, _hoops_RRP _hoops_HAR _hoops_SHH _hoops_AARGR, _hoops_SAHR _hoops_HAR _hoops_GPP _hoops_CRAA */
	_hoops_CSPIR->axis[0] = _hoops_IRGA::X_Axis;

	_hoops_CSPIR->axis[1] = path._hoops_SAIAR(_hoops_CSPIR->axis[0]);

	if (Abs(_hoops_CSPIR->axis[1].x) < _hoops_ISCIA &&
		  Abs(_hoops_CSPIR->axis[1].y) < _hoops_ISCIA &&
			Abs(_hoops_CSPIR->axis[1].z) < _hoops_ISCIA) {
		/* _hoops_AHCI _hoops_AHGC -- _hoops_RGSSA _hoops_CRAA _hoops_PIHA _hoops_SHH _hoops_IGIAR _hoops_SPCR _hoops_IRSS, _hoops_GHCR _hoops_HRGR _hoops_IHRI _hoops_PSCR */
		_hoops_CSPIR->axis[0] = _hoops_IRGA::_hoops_RCPCR;

		_hoops_CSPIR->axis[1] = path._hoops_SAIAR(_hoops_CSPIR->axis[0]);
	}

	/* _hoops_HARGR[1] _hoops_HA _hoops_RGCGA _hoops_CIAH, _hoops_AGCGA _hoops_HARGR[0] */
	_hoops_CSPIR->axis[0] = _hoops_CSPIR->axis[1]._hoops_SAIAR(path);
	
	/* _hoops_PPR _hoops_HPGIR */
	_hoops_CSPIR->axis[0]._hoops_AAIAR();
	_hoops_CSPIR->axis[1]._hoops_AAIAR();
}


local void _hoops_AGSSA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_RCCSA *		data) 
{
	Cylinder *				cylinder;


	if (owner != null) {
		/* _hoops_PGSSA _hoops_IS _hoops_RH _hoops_SCGR _hoops_IGS _hoops_IGCI */
		ZALLOC (cylinder, Cylinder);
		cylinder->type = _hoops_ASIP;
		cylinder->_hoops_CPGPR = _hoops_PHSSR;
	}
	else {
		/* _hoops_GRHSA _hoops_GGR _hoops_HGHC */
		cylinder = (Cylinder *)data->geometry;
		cylinder->_hoops_CPGPR = _hoops_HHSSR;
	}

	Point const *	first = &data->points[0];
	Point const *	_hoops_IAGRA = &data->points[1];
	
	/* _hoops_IPS _hoops_IAPR _hoops_RH _hoops_IPSP'_hoops_GRI _hoops_PIH */
	cylinder->axis[0] = *first;
	cylinder->axis[1] = *_hoops_IAGRA;

	cylinder->radius = data->_hoops_ICCSA;
	cylinder->flags	 = data->flags;

	if (!data->_hoops_SCCSA) {
		/* _hoops_HGCR _hoops_IHGP _hoops_HARGR */
		_hoops_SSCSA (first, _hoops_IAGRA, data->_hoops_CSPIR);
		data->_hoops_SCCSA = true;
	}

	cylinder->_hoops_CSPIR.axis[0] = data->_hoops_CSPIR->axis[0];
	cylinder->_hoops_CSPIR.axis[1] = data->_hoops_CSPIR->axis[1];

	if (owner != null) {
		HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) cylinder, false, 
								_hoops_IHSSR|_hoops_SIGPR);

		data->geometry = (Geometry *)cylinder;
		++data->_hoops_IGSSR;
	}
}

#endif




GLOBAL_FUNCTION Key HI_Insert_Cylinder (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const *			first,
	Point const *			_hoops_IAGRA,
	float					radius,
	char const *			list) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_RCCSA		data;
	ZERO_STRUCT(&data, _hoops_RCCSA);

	if (!_hoops_HSCSA (_hoops_RIGC, &data.flags, list)) {
		return _hoops_SHSSR;
	}

	data.points = data._hoops_HCCSA;
	data._hoops_HCCSA[0] = *first;
	data._hoops_HCCSA[1] = *_hoops_IAGRA;
	data.point_count = 1;
	data.radii = &data._hoops_ICCSA;
	data._hoops_ICCSA = radius;
	data._hoops_ISPIR = 1;
	data._hoops_CSPIR = &data._hoops_CCCSA;

	_hoops_AGSSA (_hoops_RIGC, item, &data);
	
	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.geometry);

	return _hoops_CHSSR;
}



HC_INTERFACE Key HC_CDECL HC_Insert_Cylinder (
	Point const *			first,
	Point const *			_hoops_IAGRA,
	double					radius,
	char const *			list) 
{
	_hoops_PAPPR context("Insert_Cylinder");

#ifdef _hoops_PSPIR
	_hoops_IRPPR ("Cylinder");
	return _hoops_SHSSR;
#else

	if (!first || !_hoops_IAGRA) {
		HE_ERROR (HEC_CYLINDER, HES_INVALID_INPUT, "All points must be provided.");
		return _hoops_SHSSR;
	}

	if (first->x == _hoops_IAGRA->x && first->y == _hoops_IAGRA->y && first->z == _hoops_IAGRA->z) {
		HE_ERROR (HEC_CYLINDER, HES_COINCIDENT_POINT, "The axis points are identical");
		return _hoops_SHSSR;
	}
	if (radius < 0.0f) {
		HE_ERROR (HEC_CYLINDER, HES_BAD_LENGTH, "The radius must be non-negative");
		return _hoops_SHSSR;
	}

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Cylinder (context, target, first,_hoops_IAGRA,(float)radius,list);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT first, second;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "first.x = %f;	first.y = %f;  ",first->x, first->y));
		HI_Dump_Code (Sprintf_F (null, "first.z = %f;\n", first->z));
		HI_Dump_Code (Sprintf_FF (null, "second.x = %f;	 second.y = %f;	 ",_hoops_IAGRA->x, _hoops_IAGRA->y));
		HI_Dump_Code (Sprintf_F (null, "second.z = %f;\n", _hoops_IAGRA->z));
		HI_Dump_Code ("DEFINE (HC_KInsert_Cylinder (&first, &second, ");
		HI_Dump_Code (Sprintf_F (null, "%F, ", radius));
		HI_Dump_Code (Sprintf_S (null, "\"%s\"), ", list));
		HI_Dump_Code (Sprintf_LD (null, "%D);}\n", _hoops_CHSSR));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	return _hoops_CHSSR;
#endif
}


#ifndef _hoops_PSPIR



local float _hoops_HGSSA (
	Point const *		first,
	Point const *		_hoops_IAGRA,
	Point const *		_hoops_IGSSA,
	_hoops_SSPIR alter *	_hoops_CSPIR) 
{
	Vector _hoops_CGSSA = *_hoops_IAGRA - *first;
	Vector _hoops_SGSSA = *_hoops_IGSSA - *_hoops_IAGRA;

	_hoops_CGSSA._hoops_AAIAR();
	_hoops_SGSSA._hoops_AAIAR();

	_hoops_CSPIR->axis[1] = _hoops_CGSSA._hoops_SAIAR(_hoops_SGSSA);

	float	length = _hoops_CSPIR->axis[1].length();

	if (length < 0.01) {
		_hoops_SSCSA (first, _hoops_IAGRA, _hoops_CSPIR);
		return 1.0f;
	}

	/* _hoops_HARGR[0] _hoops_ASIRA _hoops_RH _hoops_RCSA _hoops_GRSSA _hoops_HPP _hoops_RH _hoops_RRSSA */
	_hoops_CSPIR->axis[0] = _hoops_CGSSA - _hoops_SGSSA;
	_hoops_CSPIR->axis[0]._hoops_AAIAR();

	/* _hoops_HARGR[1] _hoops_HRGR _hoops_AARGR _hoops_IS _hoops_GIPR _hoops_GPAC, _hoops_PPR _hoops_PRGPR _hoops_IS _hoops_HARGR[0] */
	_hoops_CSPIR->axis[1]._hoops_AAIAR();

	/* _hoops_HARGR[0] _hoops_HRGR _hoops_RH _hoops_ARSSA _hoops_IRSS _hoops_IIGR _hoops_RH _hoops_HCPI _hoops_IIGR _hoops_SGSSR */
	length = 1.0f / (float)COS(0.5f * _hoops_ISSSR(_hoops_CGSSA._hoops_SSRP(_hoops_SGSSA)));
	_hoops_CSPIR->axis[0] *= length;

	return length;
}

#define _hoops_RAAHR 1.0e-6f

local void _hoops_PRSSA (
	_hoops_RCCSA *		data) {
	int						count = data->point_count;
	Point const *			points = data->points;
	int						rcount = data->_hoops_ISPIR;
	float const *			radii = data->radii;
	_hoops_SSPIR *			_hoops_CSPIR = data->_hoops_CSPIR;
	float *					_hoops_GGHIR = data->_hoops_GGHIR;
	float					_hoops_PCCSA = 0.0f;
	float					displacement;
	_hoops_SSPIR *			_hoops_HRSSA;
	Point const *			_hoops_IRSSA;
	Point const *			_hoops_CRSSA;
	Point					_hoops_SRSSA;
	Vector					path, tmp;
	int						ii;

	bool _hoops_SPGPA = (count >= 3) &&
			 (Abs (points[count-1].x - points[0].x) <= _hoops_RAAHR &&
			  Abs (points[count-1].y - points[0].y) <= _hoops_RAAHR &&
			  Abs (points[count-1].z - points[0].z) <= _hoops_RAAHR) &&
			 Abs (radii[(count-1) % rcount] - radii[0]) <= _hoops_RAAHR;

	_hoops_SSPIR * current = &_hoops_CSPIR[0];

	_hoops_CRSSA = &points[1];
	while (*_hoops_CRSSA == points[0])
		++_hoops_CRSSA;

	data->_hoops_ACCSA[0] = points[0] - *_hoops_CRSSA;
	data->_hoops_ACCSA[0]._hoops_AAIAR();

	if (_hoops_SPGPA) {
		data->flags |= _hoops_GASSA;

		_hoops_IRSSA = &points[count-1];
		while (*_hoops_IRSSA == points[0])
			--_hoops_IRSSA;

		displacement = _hoops_HGSSA (_hoops_IRSSA, &points[0], _hoops_CRSSA,
											current);
		_hoops_PCCSA = displacement * radii[0];

		/* _hoops_HSPC _hoops_PRP _hoops_HSCHR */
		tmp = current->axis[0]._hoops_SAIAR(current->axis[1]);
		path = points[0] - *_hoops_IRSSA;
		if (path._hoops_SSRP(tmp) < 0)
			current->axis[1] = -current->axis[1];
	}
	else {
		_hoops_SRSSA = points[0] - (*_hoops_CRSSA - points[0]);
		_hoops_IRSSA = &_hoops_SRSSA;

		_hoops_SSCSA (&points[0], _hoops_CRSSA, current);
		_hoops_PCCSA = radii[0];

		/* _hoops_APHR _hoops_HSCHR _hoops_HRGR _hoops_IHRI */
	}
	_hoops_GGHIR[0] = 0;


	for (ii=1; ii<count; ii++) {
		Vector		_hoops_RAISA, _hoops_RASSA;

		_hoops_HRSSA = current++;

		if (points[ii-1] != points[ii])
			_hoops_IRSSA = &points[ii-1];

		if (ii == count-1) {
			if (_hoops_SPGPA) {
				_hoops_CRSSA = &points[0];
				while (*_hoops_CRSSA == points[count-1])
					++_hoops_CRSSA;

				displacement = _hoops_HGSSA (_hoops_IRSSA, &points[count-1], _hoops_CRSSA,current);
			}
			else {
				_hoops_SSCSA (_hoops_IRSSA, &points[count-1],current);
				displacement = 1.0f;
			}

			data->_hoops_ACCSA[1] = points[count-1] - *_hoops_IRSSA;
			data->_hoops_ACCSA[1]._hoops_AAIAR();
		}
		else {
			_hoops_CRSSA = &points[ii+1];
			while (*_hoops_CRSSA == points[ii]) {
				if (++_hoops_CRSSA == &points[count])
					_hoops_CRSSA = &points[0];
			}
			displacement = _hoops_HGSSA (_hoops_IRSSA, &points[ii], _hoops_CRSSA,current);
		}
/* _hoops_SIGP: _hoops_CGH _hoops_HIHA _hoops_IH _hoops_HAGH _hoops_PSAA _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_AASSA */
		displacement *= radii[ii % rcount];

		if (displacement > _hoops_PCCSA)
			_hoops_PCCSA = displacement;

		/* _hoops_GACC _hoops_RRP _hoops_PRP _hoops_HSCHR */
		_hoops_RAISA = _hoops_HRSSA->axis[0]._hoops_SAIAR(_hoops_HRSSA->axis[1]);
		
		_hoops_RASSA = current->axis[0]._hoops_SAIAR(current->axis[1]);

		path = points[ii] - *_hoops_IRSSA;
		path._hoops_AAIAR();

		if (_hoops_RAISA._hoops_SSRP(path) * _hoops_RASSA._hoops_SSRP(path) < 0.0)
			current->axis[1] = -current->axis[1];

		/* _hoops_PPR _hoops_CGIC _hoops_HCHC _hoops_IIGR _hoops_PASSA _hoops_GAPA _hoops_HASSA _hoops_RRGP */
		_hoops_GGHIR[ii] = _hoops_ISSSR (_hoops_HRSSA->axis[1]._hoops_SSRP(current->axis[1]));

		_hoops_RAISA = _hoops_HRSSA->axis[1]._hoops_SAIAR(current->axis[1]);

		if (path._hoops_SSRP(_hoops_RAISA) > 0.0)
			_hoops_GGHIR[ii] = -_hoops_GGHIR[ii];

		/* _hoops_IASSA _hoops_HRGR _hoops_HPIAA _hoops_SGS _hoops_CASSA _hoops_PRCS _hoops_GGR 0..360 _hoops_CCIR, _hoops_HIS _hoops_HPGIR _hoops_AGCR _hoops_SASSA */
		_hoops_GGHIR[ii] += _hoops_GGHIR[ii-1];
		if (_hoops_GGHIR[ii] > 360)
			_hoops_GGHIR[ii] -= 360;
		else if (_hoops_GGHIR[ii] < 0)
			_hoops_GGHIR[ii] += 360;
	}

	data->_hoops_PCCSA = _hoops_PCCSA;
}


local void _hoops_GPSSA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				owner,
	_hoops_RCCSA *		data)
{
	PolyCylinder *			polycylinder;
	bool					_hoops_RPSSA = false;

	if (owner != null) {
		ZALLOC (polycylinder, PolyCylinder);
		polycylinder->type = _hoops_CSIP;
		polycylinder->_hoops_CPGPR = _hoops_PHSSR;
	}
	else {
		/* _hoops_GRHSA _hoops_GGR _hoops_HGHC */
		polycylinder = (PolyCylinder *)data->geometry;
		polycylinder->_hoops_CPGPR = _hoops_HHSSR;
	}
	polycylinder->_hoops_RRHH = 0;

	/* _hoops_IPS _hoops_IAPR _hoops_RH _hoops_IPSP'_hoops_GRI _hoops_PIH */
	_hoops_APRGA(data->points, data->point_count, Point, polycylinder->points);
	polycylinder->point_count = data->point_count;
	if (data->_hoops_ISPIR) {
		if (data->_hoops_GSCSA)
			//_hoops_IISPR _hoops_HIS _hoops_SR _hoops_PAH _hoops_RRI _hoops_SSHCR _hoops_RPGP _hoops_IGH _hoops_SR _hoops_PAH _hoops_HGCR _hoops_SGGR _hoops_CCA _hoops_SAHR _hoops_ASCA _hoops_IRS _hoops_III
			data->_hoops_ISPIR = 1;
		_hoops_APRGA(data->radii, data->_hoops_ISPIR, float, polycylinder->radii);
		polycylinder->_hoops_ISPIR = data->_hoops_ISPIR;
	}
	polycylinder->_hoops_RGHIR = null;

	if (!data->_hoops_SCCSA) {
		if (data->point_count) {
			/* _hoops_HGCR _hoops_IHGP _hoops_HARGR */
			_hoops_RPSSA=true;
			if (data->point_count) {
				ALLOC_ARRAY (data->_hoops_CSPIR, data->point_count, _hoops_SSPIR);
				ALLOC_ARRAY (data->_hoops_GGHIR, data->point_count, float);
				_hoops_PRSSA (data);
			}
		}
		else {
			data->_hoops_CSPIR = null;
			data->_hoops_GGHIR = null;
		}
		data->_hoops_SCCSA = true;
	}

	polycylinder->flags	 = data->flags; /* _hoops_APSSA _hoops_GRAS, _hoops_SCH _hoops_GHCA _hoops_AGRP _hoops_SGI */

	_hoops_AIGA (data->_hoops_ACCSA, 2, Vector, polycylinder->_hoops_ACCSA);

	if (data->point_count) {
		_hoops_APRGA(data->_hoops_CSPIR, data->point_count, _hoops_SSPIR, polycylinder->_hoops_CSPIR);
		_hoops_APRGA(data->_hoops_GGHIR, data->point_count, float, polycylinder->_hoops_GGHIR);
	}

	if (_hoops_RPSSA) {
		FREE_ARRAY (data->_hoops_CSPIR, data->point_count, _hoops_SSPIR);
		FREE_ARRAY (data->_hoops_GGHIR, data->point_count, float);
		data->_hoops_SCCSA = false;
		data->_hoops_CSPIR = 0;
		data->_hoops_GGHIR = 0;
	}

	polycylinder->_hoops_PCCSA = data->_hoops_PCCSA;

	Activity	_hoops_CPGPR = polycylinder->_hoops_CPGPR;
	polycylinder->_hoops_CPGPR = _hoops_AHSGA;
	HI_Figure_Geometry_Bounding ((Geometry const *)polycylinder, polycylinder->bounding);
	polycylinder->_hoops_CPGPR = _hoops_CPGPR;

	if (owner != null) {
		HI_Insert_Geometry (_hoops_RIGC, owner, (Geometry *) polycylinder,false,
							_hoops_IHSSR|_hoops_SIGPR);

		data->geometry = (Geometry *)polycylinder;
		++data->_hoops_IGSSR;
	}
}

#endif



GLOBAL_FUNCTION Key HI_Insert_PolyCylinder (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	int						point_count,
	Point const *			points,
	int						_hoops_ISPIR,
	float const *			radii,
	char const *			list) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_RCCSA		data;
	ZERO_STRUCT(&data, _hoops_RCCSA);

	if (!_hoops_HSCSA (_hoops_RIGC, &data.flags, list)) {
		return _hoops_SHSSR;
	}

	data.point_count = point_count;
	data.points = points;
	data._hoops_ISPIR = _hoops_ISPIR;
	data.radii = radii;
	data._hoops_GSCSA = true;

	for (int ii=1; ii<data.point_count; ii++) {
		if (data.points[ii] != data.points[0])
			break;
		if (ii == data.point_count-1) {
			HE_ERROR (HEC_CYLINDER, HES_COINCIDENT_POINT, "The points are all identical");
			return _hoops_SHSSR;
		}
	}

	for (int ii=0; ii<data._hoops_ISPIR; ii++) {
		if (data.radii[ii] < 0.0f) {
			HE_ERROR (HEC_CYLINDER, HES_BAD_LENGTH, "The radii must be non-negative");
			return _hoops_SHSSR;
		}
		if (data.radii[ii] != 0)
			data._hoops_GSCSA = false;
	}

	_hoops_GPSSA (_hoops_RIGC, item, &data);
	
	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data.geometry);

	if (data._hoops_CSPIR != null)
		FREE_ARRAY (data._hoops_CSPIR, data.point_count, _hoops_SSPIR);

	if (data._hoops_GGHIR != null)
		FREE_ARRAY (data._hoops_GGHIR, data.point_count, float);

	return _hoops_CHSSR;	
}



HC_INTERFACE Key HC_CDECL HC_Insert_PolyCylinder (
	int						point_count,
	Point const *			points,
	int						_hoops_ISPIR,
	float const *			radii,
	char const *			list) 
{
	_hoops_PAPPR context("Insert_PolyCylinder");

#ifdef _hoops_PSPIR
	_hoops_IRPPR ("Cylinder");
	return _hoops_SHSSR;
#else

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_PolyCylinder (context, target, point_count, points, _hoops_ISPIR, radii, list);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null, "HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", point_count));
		HI_Dump_Code (Sprintf_D (null, "float* radii = (float*) malloc(sizeof(float)*%d);\n", _hoops_ISPIR));
		++HOOPS_WORLD->_hoops_ISPPR;
		for (int i=0; i<point_count; i++) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", i, points[i].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", i, points[i].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n", i, points[i].z));
		}
		for (int i=0; i<_hoops_ISPIR; i++) {
			HI_Dump_Code (_hoops_CHCHR (null, "radii[%d] = %f;  ", i, radii[i]));
		}
		HI_Dump_Code ("DEFINE (HC_KInsert_PolyCylinder (");
		HI_Dump_Code (Sprintf_DD (null, "%d, points, %d, radii, ", point_count, _hoops_ISPIR));
		HI_Dump_Code (Sprintf_S (null, "\"%s\"), ", list));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (points);\n");
		HI_Dump_Code ("free (radii);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CHSSR;
#endif	
}


HC_INTERFACE void HC_CDECL HC_Show_Cylinder (
	Key				key,
	Point *			first,
	Point *			_hoops_IAGRA,
	float *			radius,
	char alter *	list) 
{
	_hoops_PAPPR context("Show_Cylinder");

#ifdef _hoops_PSPIR
	_hoops_IRPPR ("Cylinder");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Cylinder () */\n");
	);

	_hoops_CSPPR();

	Cylinder *	cylinder = (Cylinder*)_hoops_RCSSR (context, key);

	if (cylinder == null ||
		cylinder->type != _hoops_ASIP ||
		BIT (cylinder->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CYLINDER, HES_INVALID_KEY, "Provided key does not refer to a valid cylinder");
	}
	else {
		if (first != null)
			*first = cylinder->axis[0];

		if (_hoops_IAGRA != null)
			*_hoops_IAGRA = cylinder->axis[1];

		if (radius != null)
			*radius = cylinder->radius;

		if (list != null) {
			switch (cylinder->flags & _hoops_PPSSA) {
				case _hoops_ASCSA: {
					HI_Return_Chars (list, -1, "none", 4);
				}	break;

				case _hoops_IHHIA:		{
					HI_Return_Chars (list, -1, "first", 5);
				}	break;

				case _hoops_SHHIA:		{
					HI_Return_Chars (list, -1, "second", 6);
				}	break;

				case _hoops_PSCSA: {
					HI_Return_Chars (list, -1, "both", 4);
				}	break;
			}
		}
	}

	_hoops_IRRPR();
#endif
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_PolyCylinder (
	Key				key,
	int *			point_count,
	Point *			points,
	int *			_hoops_ISPIR,
	float *			radii,
	char alter *	list) 
{
	_hoops_PAPPR context("Show_PolyCylinder");

#ifdef _hoops_PSPIR
	_hoops_IRPPR ("Cylinder");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_PolyCylinder () */\n");
	);

	_hoops_CSPPR();
	
	PolyCylinder *	polycylinder = (PolyCylinder*)_hoops_RCSSR (context, key);

	if (polycylinder == null ||
		polycylinder->type != _hoops_CSIP ||
		BIT (polycylinder->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CYLINDER, HES_INVALID_KEY, "Provided key does not refer to a valid polycylinder");
	}
	else {
		if (point_count != null)
			*point_count = polycylinder->point_count;

		if (points != null)
			_hoops_AIGA (polycylinder->points, polycylinder->point_count, Point, points);

		if (_hoops_ISPIR != null)
			*_hoops_ISPIR = polycylinder->_hoops_ISPIR;

		if (radii != null)
			_hoops_AIGA (polycylinder->radii, polycylinder->_hoops_ISPIR, float, radii);

		if (list != null) {
			switch (polycylinder->flags & _hoops_PPSSA) {
				case _hoops_ASCSA: {
					HI_Return_Chars (list, -1, "none", 4);
				}	break;

				case _hoops_IHHIA:		{
					HI_Return_Chars (list, -1, "first", 5);
				}	break;

				case _hoops_SHHIA:		{
					HI_Return_Chars (list, -1, "second", 6);
				}	break;

				case _hoops_PSCSA: {
					HI_Return_Chars (list, -1, "both", 4);
				}	break;
			}
		}
	}

	_hoops_IRRPR();
#endif
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_PolyCylinder_Counts (
	Key				key,
	int alter *		point_count,
	int alter *		_hoops_ISPIR,
	char alter *	list) 
{
	_hoops_PAPPR context("Show_PolyCylinder_Counts");

#ifdef _hoops_PSPIR
	_hoops_IRPPR ("Cylinder");
#else
#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_PolyCylinder_Counts () */\n");
	);

	_hoops_CSPPR();

	PolyCylinder *polycylinder = (PolyCylinder*)_hoops_RCSSR (context, key);

	if (polycylinder == null ||
		polycylinder->type != _hoops_CSIP ||
		BIT (polycylinder->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CYLINDER, HES_INVALID_KEY, "Provided key does not refer to a valid polycylinder");
	}
	else {
		if (point_count != null)
			*point_count = polycylinder->point_count;

		if (_hoops_ISPIR != null)
			*_hoops_ISPIR = polycylinder->_hoops_ISPIR;

		if (list != null) {
			switch (polycylinder->flags & _hoops_PPSSA) {
				case _hoops_ASCSA: {
					HI_Return_Chars (list, -1, "none", 4);
				}	break;

				case _hoops_IHHIA:		{
					HI_Return_Chars (list, -1, "first", 5);
				}	break;

				case _hoops_SHHIA:		{
					HI_Return_Chars (list, -1, "second", 6);
				}	break;

				case _hoops_PSCSA: {
					HI_Return_Chars (list, -1, "both", 4);
				}	break;
			}
		}
	}

	_hoops_IRRPR();
#endif
#endif
}



HC_INTERFACE void HC_CDECL HC_Edit_Cylinder (
	Key						key,
	Point const *			first,
	Point const *			_hoops_IAGRA,
	double					radius,
	char const *			list) 
{
	_hoops_PAPPR context("Edit_Cylinder");

#ifdef _hoops_PSPIR
	_hoops_IRPPR ("Cylinder");
#else

	CODE_GENERATION (
		HI_Dump_Code ("{HC_POINT first, second;\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_FF (null, "first.x = %f;	first.y = %f;  ",first->x, first->y));
		HI_Dump_Code (Sprintf_F (null, "first.z = %f;\n", first->z));
		HI_Dump_Code (Sprintf_FF (null, "second.x = %f;	 second.y = %f;	 ", _hoops_IAGRA->x, _hoops_IAGRA->y));
		HI_Dump_Code (Sprintf_F (null, "second.z = %f;\n", _hoops_IAGRA->z));
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Cylinder (LOOKUP (%D), ", key));
		HI_Dump_Code ("&first, &second, ");
		HI_Dump_Code (Sprintf_F (null, "%F, ", radius));
		HI_Dump_Code (Sprintf_S (null, "\"%s\");}\n", list));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	if (first->x == _hoops_IAGRA->x && first->y == _hoops_IAGRA->y && first->z == _hoops_IAGRA->z) {
		HE_ERROR (HEC_CYLINDER, HES_COINCIDENT_POINT, "The axis points are identical");
		return;
	}
	if (radius < 0.0f) {
		HE_ERROR (HEC_CYLINDER, HES_BAD_LENGTH, "The radius must be non-negative");
		return;
	}

	_hoops_RCCSA		data;
	ZERO_STRUCT(&data, _hoops_RCCSA);
	if (!_hoops_HSCSA (context, &data.flags, list)) 
		return;
	data.points = data._hoops_HCCSA;
	data._hoops_HCCSA[0] = *first;
	data._hoops_HCCSA[1] = *_hoops_IAGRA;
	data.point_count = 1;
	data.radii = &data._hoops_ICCSA;
	data._hoops_ICCSA = (float)radius;
	data._hoops_ISPIR = 1;
	data._hoops_CSPIR = &data._hoops_CCCSA;

	_hoops_CRCP *				owner;
	_hoops_RPPPR();
	Cylinder * c = (Cylinder *)_hoops_RCSSR (context, key);
	if (c == null || c->type != _hoops_ASIP || BIT (c->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid cylinder");
		goto Release;
	}
	data.geometry = (Geometry *)c;

	_hoops_AGSSA (context, null, &data);
	
	owner = c->owner;
	if (owner != null) {
		_hoops_SASIR (context, owner, 
			_hoops_AISSR |
			_hoops_PISSR |
			_hoops_CSCCA |
			_hoops_RPSIR);
	}

	if (c->owner)
		HI_Antiquate_Bounding (c->owner, true);

  Release:
	_hoops_IRRPR();
#endif
}

GLOBAL_FUNCTION PolyCylinder *HI_Cylinder_To_PolyCylinder (
	Cylinder const	*		cylinder)
{
#ifndef _hoops_PSPIR
	PolyCylinder alter *_hoops_HSPIR;
	/* _hoops_SR _hoops_GA'_hoops_RA _hoops_IGRC _hoops_CIPAA _hoops_RH _hoops_RGSSA, _hoops_HIH _hoops_SR _hoops_RRP _hoops_IS _hoops_HPSSA _hoops_RH _hoops_RSRRA _hoops_ARPP
	 * _hoops_PHGSR _hoops_SCH _hoops_GPP _hoops_IS _hoops_RH _hoops_RSRRA _hoops_PGSA _hoops_API (_hoops_PGAP _hoops_IPSSA _hoops_SCH _hoops_GAR _hoops_RCIC) */
	Cylinder alter *_hoops_CPSSA = (Cylinder alter *)cylinder;

	ZALLOC (_hoops_HSPIR, PolyCylinder);
	_hoops_HSPIR->type = _hoops_CSIP;
	_hoops_HSPIR->owner = (_hoops_CRCP *) cylinder;
	_hoops_HSPIR->_hoops_CPGPR = _hoops_AHSGA;
	_hoops_PRRH (_hoops_HSPIR);
	ALLOC_ARRAY (_hoops_HSPIR->points, 2, Point);
	_hoops_AIGA (_hoops_CPSSA->axis, 2, Point, _hoops_HSPIR->points);
	ALLOC_ARRAY (_hoops_HSPIR->radii, 1, float);
	_hoops_HSPIR->radii[0] = _hoops_CPSSA->radius;
	_hoops_HSPIR->point_count = 2;
	_hoops_HSPIR->_hoops_ISPIR = 1;
	_hoops_HSPIR->flags = _hoops_CPSSA->flags;
	_hoops_HSPIR->_hoops_ACCSA[0] = _hoops_CPSSA->axis[0] - _hoops_CPSSA->axis[1];
	_hoops_HSPIR->_hoops_ACCSA[0]._hoops_AAIAR();
	_hoops_HSPIR->_hoops_ACCSA[1] = -_hoops_HSPIR->_hoops_ACCSA[0];
	_hoops_HSPIR->_hoops_RGHIR = null;
	ALLOC_ARRAY (_hoops_HSPIR->_hoops_CSPIR, 2, _hoops_SSPIR);
	_hoops_HSPIR->_hoops_CSPIR[0] = _hoops_HSPIR->_hoops_CSPIR[1] = _hoops_CPSSA->_hoops_CSPIR;
	ALLOC_ARRAY (_hoops_HSPIR->_hoops_GGHIR, 2, float);
	_hoops_HSPIR->_hoops_GGHIR[0] = _hoops_HSPIR->_hoops_GGHIR[1] = 0;
	_hoops_HSPIR->_hoops_PCCSA = _hoops_CPSSA->radius;

	Activity	_hoops_CPGPR = _hoops_HSPIR->_hoops_CPGPR;
	_hoops_HSPIR->_hoops_CPGPR = _hoops_AHSGA;
	_hoops_CAIS sphere;
	sphere.center = _hoops_AICIR(_hoops_HSPIR->points[0],_hoops_HSPIR->points[1]);
	Vector l(_hoops_HSPIR->points[1]-_hoops_HSPIR->points[0]);
	l *= 0.5f;
	sphere.radius = _hoops_SGIHR(l._hoops_PPSSR() + _hoops_CPSSA->radius * _hoops_CPSSA->radius);
	_hoops_HSPIR->bounding = Bounding::Create(sphere);
	_hoops_HSPIR->_hoops_CPGPR = _hoops_CPGPR;

	return _hoops_HSPIR;
#endif
}


HC_INTERFACE void HC_CDECL HC_Edit_PolyCylinder (
	Key						key,
	int						point_count,
	Point const *			points,
	int						_hoops_ISPIR,
	float const *			radii,
	char const *			list) 
{
	_hoops_PAPPR context("Edit_PolyCylinder");

#ifdef _hoops_PSPIR
	_hoops_IRPPR ("Cylinder");
#else

	CODE_GENERATION (
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", point_count));
		HI_Dump_Code (Sprintf_D (null, "float* radii = (float*) malloc(sizeof(float)*%d);\n", _hoops_ISPIR));
		for (int i=0; i<point_count; i++) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", i, points[i].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", i, points[i].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n", i, points[i].z));
		}
		for (int i=0; i<_hoops_ISPIR; i++) {
			HI_Dump_Code (_hoops_CHCHR (null, "radii[%d] = %f;  ", i, radii[i]));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_PolyCylinder (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, points, %d, radii, ", point_count, _hoops_ISPIR));
		HI_Dump_Code (Sprintf_S (null, "\"%s\");\n", list));
		HI_Dump_Code ("free (points);\n");
		HI_Dump_Code ("free (radii);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	_hoops_RCCSA			data;
	ZERO_STRUCT(&data, _hoops_RCCSA);

	if (!_hoops_HSCSA (context, &data.flags, list)) 
		return;

	data.point_count = point_count;
	data.points = points;
	data._hoops_ISPIR = _hoops_ISPIR;
	data.radii = radii;
	data._hoops_GSCSA = true;

	for (int ii=1; ii<data.point_count; ii++) {
		if (data.points[ii] != data.points[0])
			break;
		if (ii == data.point_count-1) {
			HE_ERROR (HEC_CYLINDER, HES_COINCIDENT_POINT, "The points are all identical");
			return;
		}
	}

	for (int ii=0; ii<data._hoops_ISPIR; ii++) {
		if (data.radii[ii] < 0.0f) {
			HE_ERROR (HEC_CYLINDER, HES_BAD_LENGTH, "The radii must be non-negative");
			return;
		}
		if (data.radii[ii] != 0)
			data._hoops_GSCSA = false;
	}

	_hoops_CRCP *owner;
	_hoops_RPPPR();

	PolyCylinder * _hoops_HSPIR = (PolyCylinder *)_hoops_RCSSR (context, key);

	if (_hoops_HSPIR == null || _hoops_HSPIR->type != _hoops_CSIP ||
		BIT (_hoops_HSPIR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid polycylinder");
		goto Release;
	}

	data.geometry = (Geometry *)_hoops_HSPIR;

	if (_hoops_HSPIR->point_count != 0) {
		FREE_ARRAY (_hoops_HSPIR->points, _hoops_HSPIR->point_count, Point);
		FREE_ARRAY (_hoops_HSPIR->_hoops_CSPIR, _hoops_HSPIR->point_count, _hoops_SSPIR);
		FREE_ARRAY (_hoops_HSPIR->_hoops_GGHIR, _hoops_HSPIR->point_count, float);
	}

	if (_hoops_HSPIR->_hoops_ISPIR != 0)
		FREE_ARRAY (_hoops_HSPIR->radii, _hoops_HSPIR->_hoops_ISPIR, float);

	if (_hoops_HSPIR->_hoops_RGHIR != null) {
		_hoops_AGHIR *		_hoops_PGHIR = _hoops_HSPIR->_hoops_RGHIR;

		if (_hoops_PGHIR->ecolors != null && _hoops_PGHIR->ecolors != _hoops_PGHIR->fcolors)
			FREE_ARRAY (_hoops_PGHIR->ecolors, _hoops_HSPIR->point_count, RGB);
		if (_hoops_PGHIR->fcolors != null)
			FREE_ARRAY (_hoops_PGHIR->fcolors, _hoops_HSPIR->point_count, RGB);
		if (_hoops_PGHIR->_hoops_HGHIR != null && _hoops_PGHIR->_hoops_HGHIR != _hoops_PGHIR->_hoops_IGHIR)
			FREE_ARRAY (_hoops_PGHIR->_hoops_HGHIR, _hoops_HSPIR->point_count, _hoops_ACGHR);
		if (_hoops_PGHIR->_hoops_IGHIR != null)
			FREE_ARRAY (_hoops_PGHIR->_hoops_IGHIR, _hoops_HSPIR->point_count, _hoops_ACGHR);
		if (_hoops_PGHIR->flags != null)
			FREE_ARRAY (_hoops_PGHIR->flags, _hoops_HSPIR->point_count, _hoops_CGHIR);
		FREE (_hoops_PGHIR, _hoops_AGHIR);
		_hoops_HSPIR->_hoops_RGHIR = null;
	}

	_hoops_GPSSA (context, null, &data);
	owner = _hoops_HSPIR->owner;

	HI_Invalidate_Display_Lists (context, _hoops_HSPIR);

	if (_hoops_HSPIR->owner)
		HI_Antiquate_Bounding (_hoops_HSPIR->owner, true);

	if (owner != null) {
		_hoops_SASIR (context, owner, 
			_hoops_AISSR |
			_hoops_PISSR |
			_hoops_CSCCA |
			_hoops_RPSIR);
	}
  Release:
	_hoops_IRRPR();
#endif
}
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
 * $Id: obf_tmp.txt 1.84 2010-10-06 19:16:36 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

struct _hoops_SHCSA {
	_hoops_ARPA const *		planes;
	_hoops_HHPIR *		_hoops_GICSA;
	int					count;
	int					_hoops_IGSSR;
};

local void _hoops_RICSA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_SHCSA *			data) 
{
	_hoops_HHPIR *			_hoops_GICSA;
	ZALLOC (_hoops_GICSA, _hoops_HHPIR);

	_hoops_GICSA->type = _hoops_HGPGR;
	_hoops_GICSA->_hoops_CPGPR = _hoops_PHSSR;

	/* _hoops_IPS _hoops_IAPR _hoops_RH _hoops_IPSP'_hoops_GRI _hoops_PIH */
	if ((_hoops_GICSA->count = data->count) > 0) {
		ALLOC_ARRAY (_hoops_GICSA->planes, data->count, _hoops_ARPA);
		_hoops_AIGA (data->planes, data->count, _hoops_ARPA, _hoops_GICSA->planes);
	}
	else
		_hoops_GICSA->planes = null;

	HI_Insert_Geometry (_hoops_RIGC, item, (Geometry *) _hoops_GICSA, true, 
		_hoops_RAGGA | _hoops_ISCCA | _hoops_AICSA);

	if (item->type == _hoops_IRCP)
		HI_More_Cutting_Planes (_hoops_RIGC, (_hoops_CRCP *)item, 1);

	data->_hoops_GICSA = _hoops_GICSA;
	++data->_hoops_IGSSR;
}

GLOBAL_FUNCTION Key HI_Insert_Cutting_Section (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item, 
	int						count,
	_hoops_ARPA const	*			planes) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_SHCSA		data;
	ZERO_STRUCT(&data, _hoops_SHCSA);
	data.planes = planes;
	data.count = count;
		
	_hoops_RICSA (_hoops_RIGC, item, &data);
	
	Key		_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = _hoops_AIRIR (data._hoops_GICSA);

	return _hoops_CHSSR;
}

local bool _hoops_PICSA (
	int				count,
	_hoops_ARPA const *	planes) 
{
	while (count-- > 0) {
		if (planes->a == 0.0f && planes->b == 0.0f && planes->c == 0.0f) {
			HE_ERROR (HEC_CUTTING_PLANE, HES_SINGULAR_PLANE, "The requested plane is singular (a,b,c all zero)");
			return false;
		}
	}

	return true;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Cutting_Plane (
	double			a,
	double			b,
	double			c,
	double			d) 
{
	_hoops_PAPPR context("Insert_Cutting_Plane");

	_hoops_ARPA			_hoops_HICSA;
	_hoops_HICSA.a = (float)a;
	_hoops_HICSA.b = (float)b;
	_hoops_HICSA.c = (float)c;
	_hoops_HICSA.d = (float)d;

	if (!_hoops_PICSA (1, &_hoops_HICSA))
		return _hoops_SHSSR;

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Cutting_Section (context, target, 1, &_hoops_HICSA);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_KInsert_Cutting_Plane (%F, %F, ", a, b));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F), ", c, d));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}

HC_INTERFACE Key HC_CDECL HC_Insert_Cutting_Section (
	int				count,
	_hoops_ARPA const	*	planes) 
{
	_hoops_PAPPR context("Insert_Cutting_Section");

	if (!_hoops_PICSA (count, planes))
		return _hoops_SHSSR;

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Cutting_Section (context, target, count, planes);
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_PLANE* planes = (HC_PLANE*) malloc(sizeof(HC_PLANE)*%d);\n", count));
		for (int i=0; i<count ; i++) {
			HI_Dump_Code (_hoops_CHCHR (null, "planes[%d].a = %f;	 ", i, planes[i].a));
			HI_Dump_Code (_hoops_CHCHR (null, "planes[%d].b = %f;	 ", i, planes[i].b));
			HI_Dump_Code (_hoops_CHCHR (null, "planes[%d].c = %f;\n", i, planes[i].c));
			HI_Dump_Code (_hoops_CHCHR (null, "planes[%d].d = %f;\n", i, planes[i].d));
		}
		HI_Dump_Code (Sprintf_D (null, "DEFINE (HC_KInsert_Cutting_Section (%d, planes), ", count));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
		HI_Dump_Code ("free (planes);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	return _hoops_CHSSR;
}


HC_INTERFACE void HC_CDECL HC_Edit_Cutting_Plane (
	Key				key,
	double			a,
	double			b,
	double			c,
	double			d) 
{	
	_hoops_PAPPR context("Edit_Cutting_Plane");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Cutting_Plane (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", a, b));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", c, d));
	);

	if (a == 0.0f && b == 0.0f && c == 0.0f) {
		HE_ERROR (HEC_CUTTING_PLANE, HES_SINGULAR_PLANE,
				"The requested plane is singular (a,b,c all zero)");
		return;
	}

	_hoops_CRCP *		owner;

	_hoops_RPPPR();
	_hoops_HHPIR *	_hoops_IICSA = (_hoops_HHPIR *)_hoops_RCSSR (context, key);
	if (_hoops_IICSA == null || _hoops_IICSA->type != _hoops_HGPGR ||
		BIT (_hoops_IICSA->_hoops_RRHH, _hoops_HGAGR) ||
		_hoops_IICSA->count != 1) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY,
				"Key does not refer to a valid cutting plane");
		goto Release;
	}
	_hoops_IICSA->planes[0].a = (float)a;
	_hoops_IICSA->planes[0].b = (float)b;
	_hoops_IICSA->planes[0].c = (float)c;
	_hoops_IICSA->planes[0].d = (float)d;
	_hoops_IICSA->_hoops_CPGPR = _hoops_HHSSR;
	owner = _hoops_IICSA->owner;
	if (owner != null) {
		_hoops_SASIR (context, owner, 
			_hoops_AISSR |
			_hoops_PISSR |
			_hoops_CSCCA |
			_hoops_RPSIR);
	}
  Release:
	_hoops_IRRPR();
}


HC_INTERFACE void HC_CDECL HC_Edit_Cutting_Section (
	Key					key,
	int					ioffset,
	int					ndelete,
	int					insert,
	_hoops_ARPA const *		iplanes) 
{
	_hoops_PAPPR context("Edit_Cutting_Section");

#ifdef DISABLE_GEOMETRY_EDIT
	_hoops_IRPPR ("Geometry Edit");
#else

	_hoops_ARPA *				planes;
	int					count;
	int					_hoops_CICSA;
	int					offset = ioffset;

	CODE_GENERATION (
		int		count2 = insert;
		HI_Dump_Code (Sprintf_D (null, "{HC_PLANE planes[%d];\n", count2));
		++HOOPS_WORLD->_hoops_ISPPR;
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "planes[%d].a = %f;	 ", count2, iplanes[count2].a));
			HI_Dump_Code (_hoops_CHCHR (null, "planes[%d].b = %f;	 ", count2, iplanes[count2].b));
			HI_Dump_Code (_hoops_CHCHR (null, "planes[%d].c = %f;\n", count2, iplanes[count2].c));
			HI_Dump_Code (_hoops_CHCHR (null, "planes[%d].d = %f;\n", count2, iplanes[count2].d));
		}
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Cutting_Section (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_DD (null, "%d, %d, ", ioffset, ndelete));
		HI_Dump_Code (Sprintf_D (null, "%d, planes);}\n", insert));
		--HOOPS_WORLD->_hoops_ISPPR;
	);

	if (!_hoops_PICSA (insert, iplanes))
		return;

	_hoops_RPPPR();

	_hoops_HHPIR *		_hoops_IICSA = (_hoops_HHPIR *)_hoops_RCSSR (context, key);

	if (_hoops_IICSA == null || _hoops_IICSA->type != _hoops_HGPGR ||
		BIT (_hoops_IICSA->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CUTTING_PLANE, HES_INVALID_KEY, "Key does not refer to a valid Cutting Section");
		goto Release;
	}

	_hoops_CICSA = _hoops_IICSA->count;

	if (offset == -1) offset = _hoops_IICSA->count - ndelete;

	if (offset < 0 || offset > _hoops_IICSA->count) {
		HE_ERROR (HEC_CUTTING_PLANE, HES_INVALID_OFFSET,
				Sprintf_DD (null, "Offset '%d' not valid (cutting section currently has %d planes)", offset, _hoops_IICSA->count));
		goto Release;
	}

	if (ndelete < 0) {
		HE_ERROR (HEC_CUTTING_PLANE, HES_INVALID_DELETE_COUNT,
				Sprintf_D (null, "'%d' is not a good number of planes to delete", ndelete));
		goto Release;
	}
	else if (ndelete > _hoops_IICSA->count - offset) {
		if (ioffset == -1)
			HE_ERROR (HEC_CUTTING_PLANE, HES_INVALID_DELETE_COUNT,
					"Can't delete planes after the end of the cutting section (offset is -1)");
		else
			HE_ERROR (HEC_CUTTING_PLANE, HES_INVALID_COUNT,
					Sprintf_DD (null, "Delete count '%d' not valid (polyline currently has %d vertices)",
					ndelete, _hoops_IICSA->count));
		goto Release;
	}

	if (insert < 0) {
		HE_ERROR (HEC_CUTTING_PLANE, HES_INVALID_INSERT_COUNT,
				Sprintf_D (null, "'%d' is not a good number of planes to insert", insert));
		goto Release;
	}


	if (insert == 0 && ndelete == 0) 
		goto Release;		/* _hoops_RPAPR */

	_hoops_SHCSA		data;
	ZERO_STRUCT(&data, _hoops_SHCSA);
	data.planes = iplanes;
	data.count = insert;

	/* _hoops_HCR _hoops_GPRS */

	ioffset = offset;	/* _hoops_GRHP _hoops_RGR _hoops_PIRA */

	planes = _hoops_IICSA->planes;
	if ((count = _hoops_IICSA->count - ndelete + insert) != _hoops_IICSA->count) {
		_hoops_ARPA		*_hoops_SICSA;
		_hoops_ARPA		*_hoops_GCCSA = planes;
		int				_hoops_IRCSA = _hoops_IICSA->count;

		if ((_hoops_IICSA->count = count) > 0) {
			ALLOC_ARRAY (_hoops_SICSA, count, _hoops_ARPA);
			_hoops_IICSA->planes = _hoops_SICSA;

			if (offset > 0) {
				_hoops_AIGA (planes, offset, _hoops_ARPA, _hoops_SICSA);
				_hoops_SICSA += offset;
				planes += offset;
			}
			if (insert > 0) {
				_hoops_AIGA (iplanes, insert, _hoops_ARPA, _hoops_SICSA);
				_hoops_SICSA += insert;
			}

			if (offset + ndelete < _hoops_IICSA->count) {		/* _hoops_RAAP _hoops_HII _hoops_GIGR */
				planes += ndelete;

				if (_hoops_IRCSA - (offset + ndelete) > 0)
					_hoops_AIGA (planes, _hoops_IRCSA - (offset + ndelete), _hoops_ARPA, _hoops_SICSA);
			}
		}
		else
			_hoops_IICSA->planes = null;

		if (_hoops_IRCSA > 0)
			FREE_ARRAY (_hoops_GCCSA, _hoops_IRCSA, _hoops_ARPA);
	}
	else {
		planes += offset;
		_hoops_AIGA (iplanes, insert, _hoops_ARPA, planes);
	}


	if (!BIT (_hoops_IICSA->_hoops_CPGPR, _hoops_CASIR)) {
		_hoops_IICSA->_hoops_CPGPR |= _hoops_HHSSR;
		if (_hoops_IICSA->owner != null) {
			_hoops_SASIR (context, _hoops_IICSA->owner,
								_hoops_AISSR | _hoops_PISSR |
								_hoops_CSCCA | _hoops_RPSIR);
		}
	}

  Release:
	_hoops_IRRPR();
#endif
}




HC_INTERFACE void HC_CDECL HC_Show_Cutting_Plane (
	Key					key,
	float *				a,
	float *				b,
	float *				c,
	float *				d) 
{
	_hoops_PAPPR context("Show_Cutting_Plane");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Cutting_Plane () */\n");
	);

	_hoops_CSPPR();

	_hoops_HHPIR *		_hoops_GICSA = (_hoops_HHPIR *)_hoops_RCSSR (context, key);

	if (_hoops_GICSA == null ||
		_hoops_GICSA->type != _hoops_HGPGR ||
		BIT (_hoops_GICSA->_hoops_RRHH, _hoops_HGAGR) ||
		_hoops_GICSA->count != 1) {
		HE_ERROR (HEC_CUTTING_PLANE, HES_INVALID_KEY,
				"Provided key does not refer to a valid cutting plane");
	}
	else {
		*a = _hoops_GICSA->planes[0].a;
		*b = _hoops_GICSA->planes[0].b;
		*c = _hoops_GICSA->planes[0].c;
		*d = _hoops_GICSA->planes[0].d;
	}

	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Cutting_Section (
	Key					key,
	int *				count,
	_hoops_ARPA alter *		planes) 
{
	_hoops_PAPPR context("Show_Cutting_Section");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Cutting_Section () */\n");
	);

	_hoops_CSPPR();

	_hoops_HHPIR *		_hoops_GICSA = (_hoops_HHPIR *)_hoops_RCSSR (context, key);

	if (_hoops_GICSA == null ||
		_hoops_GICSA->type != _hoops_HGPGR ||
		BIT (_hoops_GICSA->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CUTTING_PLANE, HES_INVALID_KEY,
				"Provided key does not refer to a valid cutting section");
	}
	else {
		if (count != null)
			*count = _hoops_GICSA->count;
		if (planes != null)
			_hoops_AIGA (_hoops_GICSA->planes, _hoops_GICSA->count, _hoops_ARPA, planes);
	}

	_hoops_IRRPR();
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Cutting_Section_Count (
	Key					key,
	int *				count) 
{
	_hoops_PAPPR context("Show_Cutting_Section_Count");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Cutting_Section_Count () */\n");
	);

	_hoops_CSPPR();

	_hoops_HHPIR *		_hoops_GICSA = (_hoops_HHPIR *)_hoops_RCSSR (context, key);

	if (_hoops_GICSA == null ||
		_hoops_GICSA->type != _hoops_HGPGR ||
		BIT (_hoops_GICSA->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_CUTTING_PLANE, HES_INVALID_KEY,
				"Provided key does not refer to a valid cutting section");
	}
	else {
		if (count != null)
			*count = _hoops_GICSA->count;
	}

	_hoops_IRRPR();
#endif
}





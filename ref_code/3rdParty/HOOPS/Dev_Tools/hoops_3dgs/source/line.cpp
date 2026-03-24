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
 * $Id: obf_tmp.txt 1.92 2010-10-06 19:15:52 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_CAIPI {
	Point		a, b;
	Key			key;
	int			_hoops_IGSSR;
};

local void _hoops_SAIPI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_CAIPI *			data) 
{
	Line *					line;
	_hoops_CRCP *				_hoops_SRCP = null;

	if (item->type == _hoops_CIRIR) {
		_hoops_SIRIR const *	open_list = (_hoops_SIRIR const *)item;
		if (open_list->_hoops_GCRIR == _hoops_RCRIR) {
			_hoops_SRCP = open_list->info.segment._hoops_IGRPR;
		}
	}
	else if (item->type == _hoops_IRCP)
		_hoops_SRCP = (_hoops_CRCP *)item;


	if (_hoops_SRCP != null) {
		data->key = HI_Add_To_Multiline (_hoops_RIGC, _hoops_SRCP, data->a, data->b);
		++data->_hoops_IGSSR;
	}
	else {
		ZALLOC (line, Line);

		line->type = _hoops_PIIP;
		line->_hoops_CPGPR = _hoops_PHSSR;

		line->points[0] = data->a;
		line->points[1] = data->b;


		HI_Insert_Geometry (_hoops_RIGC, item, (Geometry *) line,
							data->a.z == 0.0f && data->b.z == 0.0f,
							_hoops_IHSSR);

		data->key = _hoops_AIRIR(line);
		++data->_hoops_IGSSR;
	}
}

GLOBAL_FUNCTION Key HI_Insert_Line (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const &			a,
	Point const &			b) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_CAIPI			data;
	ZERO_STRUCT(&data, _hoops_CAIPI);
	data.a = a;
	data.b = b;

	_hoops_SAIPI	 (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = data.key;

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Line (
	double					xa,
	double					ya,
	double					za,
	double					xb,
	double					yb,
	double					zb) 
{
	_hoops_PAPPR context("Insert_Line");

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Line (context, target, Point(xa,ya,za), Point(xb,yb,zb));
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_Insert_Line (%F, %F, ", xa, ya));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", za, xb));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F), ", yb, zb));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}

HC_INTERFACE void HC_CDECL HC_Edit_Line (
	Key						key,
	double					xa,
	double					ya,
	double					za,
	double					xb,
	double					yb,
	double					zb) 
{
	_hoops_PAPPR context("Edit_Line");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Line (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", xa, ya));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", za, xb));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", yb, zb));
	);

	int						offset;
	_hoops_CRCP *				owner;
	Bounding				bounding;

	_hoops_RPPPR();
	Line *	l = (Line *)_hoops_SISIR (context, key, &offset);
	if (l == null || (l->type != _hoops_PIIP && l->type != _hoops_HIIP) ||
		BIT (l->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid line");
		goto Release;
	}

	if (l->type == _hoops_PIIP) {
		l->points[0] = Point (xa, ya, za);
		l->points[1] = Point (xb, yb, zb);
	}
	else {
		_hoops_SHRIR *		_hoops_GIRIR = (_hoops_SHRIR *)l;

		_hoops_GIRIR->points[2 * offset + 0] = Point (xa, ya, za);
		_hoops_GIRIR->points[2 * offset + 1] = Point (xb, yb, zb);
	}

	l->_hoops_CPGPR |= _hoops_HHSSR;
	owner = l->owner;
	if (owner != null) {
		_hoops_SASIR (context, owner, _hoops_RAGGA|_hoops_PISSR|_hoops_RPSIR);
		HI_Invalidate_Segment_Display_Lists(context, owner, _hoops_PIIP, l, 0);
	}

	if (za != 0.0f || zb != 0.0f) {
		if (!BIT (l->_hoops_RRHH, _hoops_RSPCR)) {
			l->_hoops_RRHH |= _hoops_RSPCR;
			if (l->owner && !BIT (l->owner->_hoops_RCGC, _hoops_ASPCR))
				HI_Propagate_Maybes (context, l->owner, _hoops_ASPCR);
		}
	}

	if (l->owner)
		HI_Antiquate_Bounding (l->owner, true);
  Release:
	_hoops_IRRPR();
}

HC_INTERFACE void HC_CDECL HC_Show_Line (
	Key						key,
	float *					xa,
	float *					ya,
	float *					za,
	float *					xb,
	float *					yb,
	float *					zb) 
{
	_hoops_PAPPR context("Show_Line");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Line () */\n");
	);

	int						offset;
	Point const *			points;

	_hoops_CSPPR();
	Line const *	line = (Line const *)_hoops_SISIR (context, key, &offset);

	if (line == null ||
		(line->type != _hoops_PIIP && line->type != _hoops_HIIP) ||
		BIT (line->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_POLYLINE, HES_INVALID_KEY, "Provided key does not refer to a valid line");
	}
	else {
		if (line->type == _hoops_PIIP)
			points = line->points;
		else {
			_hoops_SHRIR const *	_hoops_GIRIR = (_hoops_SHRIR const *)line;
			points = &_hoops_GIRIR->points[2 * offset + 0];
		}

		*xa = points->x;
		*ya = points->y;
		*za = points->z;

		points++;
		*xb = points->x;
		*yb = points->y;
		*zb = points->z;
	}

	_hoops_IRRPR();
#endif
}

GLOBAL_FUNCTION Key HI_Add_To_Multiline (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	Point const &			a,
	Point const &			b,
	int						index) {
	_hoops_SHRIR *				_hoops_GIRIR = null;

	if (_hoops_SRCP->_hoops_GACP == null ||
		(_hoops_GIRIR = (_hoops_SHRIR *)_hoops_SRCP->_hoops_GACP->_hoops_AACP (_hoops_IIAGR(_hoops_HIIP))) == null) {
		ZALLOC (_hoops_GIRIR, _hoops_SHRIR);

		_hoops_GIRIR->type = _hoops_HIIP;
		_hoops_GIRIR->_hoops_RRHH = _hoops_CHRIR;
		_hoops_GIRIR->_hoops_CPGPR = _hoops_PHSSR;
		_hoops_GIRIR->count = 0;
		_hoops_GIRIR->allocated = 8;

		ZALLOC_ARRAY (_hoops_GIRIR->points, _hoops_GIRIR->allocated, Point);
		ZALLOC_ARRAY (_hoops_GIRIR->mapping, _hoops_GIRIR->allocated / 2, int);

		HI_Insert_Geometry (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, (Geometry *) _hoops_GIRIR, true, _hoops_IHSSR);
	}
	if (_hoops_GIRIR->count == -_hoops_GIRIR->allocated) {
		Point *				_hoops_HRRGA = _hoops_GIRIR->points;
		int *				_hoops_IPGSA = _hoops_GIRIR->mapping;
		int					_hoops_CIGRR = _hoops_GIRIR->allocated;

		if (_hoops_GIRIR->allocated < 4096)
			_hoops_GIRIR->allocated *= 2;
		else
			_hoops_GIRIR->allocated += 4096;
		ZALLOC_ARRAY (_hoops_GIRIR->points, _hoops_GIRIR->allocated, Point);
		_hoops_AIGA (_hoops_HRRGA, _hoops_CIGRR, Point, _hoops_GIRIR->points);
		FREE_ARRAY (_hoops_HRRGA, _hoops_CIGRR, Point);
		ZALLOC_ARRAY (_hoops_GIRIR->mapping, _hoops_GIRIR->allocated / 2, int);
		_hoops_AIGA (_hoops_IPGSA, _hoops_CIGRR / 2, int, _hoops_GIRIR->mapping);
		FREE_ARRAY (_hoops_IPGSA, _hoops_CIGRR / 2, int);
	}

	int						offset = -_hoops_GIRIR->count / 2;

	_hoops_GIRIR->count -= 2;

	_hoops_GIRIR->points[2 * offset + 0] = a;
	_hoops_GIRIR->points[2 * offset + 1] = b;
	_hoops_GIRIR->mapping[offset] = HI_Record_Lightweight_Key ((_hoops_HPAH *)_hoops_GIRIR, offset, index);


	if (!BIT (_hoops_RSPPR(_hoops_RIGC, flags), _hoops_APGHP)) {
		Bounding	bounding = Bounding::Create (2, &_hoops_GIRIR->points[2 * offset + 0]);
		HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, bounding, null);
		_hoops_SRCP->_hoops_HSRIR.Merge (bounding);
	}


	if (!BIT (_hoops_GIRIR->_hoops_RRHH, _hoops_RSPCR) && (a.z != 0.0f || b.z != 0.0f)) {
		_hoops_GIRIR->_hoops_RRHH |= _hoops_RSPCR;
		if (!ALLBITS (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
			HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASPCR);
	}


	return HOOPS_WORLD->_hoops_GCHCA.table[_hoops_GIRIR->mapping[offset]].key;
}


GLOBAL_FUNCTION Line * HI_Isolate_Line_From_Multiline (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_SHRIR *				_hoops_GIRIR,
	int						offset) {
	Line *					line;

	ZALLOC (line, Line);

	line->type = _hoops_PIIP;
	line->_hoops_CPGPR = _hoops_GIRIR->_hoops_CPGPR;

	if (BIT (_hoops_GIRIR->mapping[offset], _hoops_RIRIR)) {
		line->_hoops_RRHH |= _hoops_GGCCA;
		_hoops_GIRIR->mapping[offset] &= _hoops_RIRIR;
	}

	line->points[0] = _hoops_GIRIR->points[2 * offset + 0];
	line->points[1] = _hoops_GIRIR->points[2 * offset + 1];


	HI_Insert_Geometry (_hoops_RIGC, (_hoops_HPAH *)_hoops_GIRIR->owner, (Geometry *)line,
						line->points[0].z == 0.0f && line->points[1].z == 0.0f,
						0);

	HI_Replace_Lightweight_Key (_hoops_GIRIR->mapping[offset & ~_hoops_RIRIR], (_hoops_HPAH *)line, 0);
	line->key = HOOPS_WORLD->_hoops_GCHCA.table[_hoops_GIRIR->mapping[offset]].key;

	int						count = -(_hoops_GIRIR->count += 2) / 2;

	while (offset < count) {
		int			index = _hoops_GIRIR->mapping[offset+1] & ~_hoops_RIRIR;

		_hoops_GIRIR->mapping[offset] = _hoops_GIRIR->mapping[offset+1];
		_hoops_GIRIR->points[2 * offset + 0] = _hoops_GIRIR->points[2 * offset + 2];
		_hoops_GIRIR->points[2 * offset + 1] = _hoops_GIRIR->points[2 * offset + 3];

		HOOPS_WORLD->_hoops_GCHCA.table[index].offset = offset++;
	}

	_hoops_GIRIR->mapping[count] = -666;

	return line;
}


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
 * $Id: obf_tmp.txt 1.79 2010-10-06 19:15:52 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


struct _hoops_IAAII {
	Point		where;
	Key			key;
	int			_hoops_IGSSR;
};


local void _hoops_CAAII (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_IAAII *		data) 
{
	Marker *				marker;
	_hoops_CRCP *				_hoops_SRCP = null;

	if (item->type == _hoops_CIRIR) {
		_hoops_SIRIR const *	open_list = (_hoops_SIRIR const *)item;
		if (open_list->_hoops_GCRIR == _hoops_RCRIR) {
			_hoops_SRCP = open_list->info.segment._hoops_IGRPR;
		}
	}
	else if (item->type == _hoops_IRCP)
		_hoops_SRCP = (_hoops_CRCP *)item;


	if (_hoops_SRCP != null) {		// _hoops_GRGR _hoops_CCGR _hoops_SAAII
		data->key = HI_Add_To_Multimarker (_hoops_RIGC, _hoops_SRCP, data->where);
		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_IHSSR);
		++data->_hoops_IGSSR;
	}
	else {
		ZALLOC (marker, Marker);
		marker->type = _hoops_PCIP;
		marker->_hoops_CPGPR = _hoops_PHSSR;
		marker->_hoops_CSAI = data->where;

		HI_Insert_Geometry (_hoops_RIGC, item, (Geometry *) marker,
							marker->_hoops_CSAI.z == 0.0f,
							_hoops_IHSSR);

		data->key = _hoops_AIRIR(marker);
		++data->_hoops_IGSSR;
	}
}


GLOBAL_FUNCTION Key HI_Insert_Marker (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Point const &			where) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_IAAII data;
	ZERO_STRUCT(&data, _hoops_IAAII);
	data.where = where;

	_hoops_CAAII (_hoops_RIGC, item, &data);

	Key	_hoops_CHSSR = _hoops_SHSSR;

	if (data._hoops_IGSSR != 0)
		_hoops_CHSSR = data.key;

	return _hoops_CHSSR;
}


HC_INTERFACE Key HC_CDECL HC_Insert_Marker (
	double			x,
	double			y,
	double			z) 
{
	_hoops_PAPPR context("Insert_Marker");

	Key	_hoops_CHSSR = _hoops_SHSSR;
	_hoops_HPAH * target;

	if ((target = HI_Find_Target_And_Lock(context, _hoops_GISSR)) != null) {
		_hoops_CHSSR = HI_Insert_Marker (context, target, Point(x,y,z));
		_hoops_IRRPR();
	}

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "DEFINE (HC_Insert_Marker (%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F), ", z));
		HI_Dump_Code (Sprintf_LD (null, "%D);\n", _hoops_CHSSR));
	);

	return _hoops_CHSSR;
}




HC_INTERFACE void HC_CDECL HC_Edit_Marker (
	Key				key,
	double			x,
	double			y,
	double			z) 
{
	_hoops_PAPPR context("Edit_Marker");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Edit_Marker (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F, ", x, y));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", z));
	);

	int						offset;
	_hoops_CRCP *				owner;

	_hoops_RPPPR();
	Marker *	m = (Marker *)_hoops_SISIR (context, key, &offset);
	if (m == null || (m->type != _hoops_PCIP && m->type != _hoops_PIRS) ||
		BIT (m->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_GEOMETRY_OR_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid marker");
		goto Release;
	}

	if (m->type == _hoops_PCIP) {
		m->_hoops_CSAI = Point(x,y,z);
	}
	else {
		_hoops_GRPGR *		_hoops_CPAI = (_hoops_GRPGR *)m;

		_hoops_CPAI->points[offset] = Point (x, y, z);
	}

	m->_hoops_CPGPR |= _hoops_HHSSR;
	owner = m->owner;
	if (owner != null) {
		_hoops_SASIR (context, owner, _hoops_RAGGA|_hoops_PISSR|_hoops_RPSIR);
	}
	
	if (z != 0.0f) {
		if (!BIT (m->_hoops_RRHH, _hoops_RSPCR)) {
			m->_hoops_RRHH |= _hoops_RSPCR;
			if (m->owner && !BIT (m->owner->_hoops_RCGC, _hoops_ASPCR))
				HI_Propagate_Maybes (context, m->owner, _hoops_ASPCR);
		}
	}

	if (m->owner)
		HI_Antiquate_Bounding (m->owner, true);

  Release:
	_hoops_IRRPR();
}





HC_INTERFACE void HC_CDECL HC_Show_Marker (
	Key			key,
	float *		x,
	float *		y,
	float *		z) 
{
	_hoops_PAPPR context("Show_Marker");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Marker () */\n");
	);

	_hoops_CSPPR();

	int						offset;
	Marker *	marker = (Marker *)_hoops_SISIR (context, key, & offset);

	if (marker == null ||
		(marker->type != _hoops_PCIP && marker->type != _hoops_PIRS) ||
		BIT (marker->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_MARKER, HES_INVALID_KEY, "Provided key does not refer to a valid marker");
	}
	else {
		Point const *			p;

		if (marker->type == _hoops_PCIP)
			p = &marker->_hoops_CSAI;
		else {
			_hoops_GRPGR const *	_hoops_CPAI = (_hoops_GRPGR const *)marker;
			p = &_hoops_CPAI->points[offset];
		}

		*x = p->x;
		*y = p->y;
		*z = p->z;
	}

	_hoops_IRRPR();
#endif
}


GLOBAL_FUNCTION Key HI_Add_To_Multimarker (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	Point const &			a,
	int						index) 
{
	_hoops_GRPGR *			_hoops_CPAI = null;

	if (_hoops_SRCP->_hoops_GACP == null ||
		(_hoops_CPAI = (_hoops_GRPGR *)_hoops_SRCP->_hoops_GACP->_hoops_AACP (_hoops_IIAGR(_hoops_PIRS))) == null) {
		ZALLOC (_hoops_CPAI, _hoops_GRPGR);

		_hoops_CPAI->type = _hoops_PIRS;
		_hoops_CPAI->_hoops_RRHH = _hoops_CHRIR;
		_hoops_CPAI->_hoops_CPGPR = _hoops_PHSSR;
		_hoops_CPAI->count = 0;
		_hoops_CPAI->allocated = 8;

		ZALLOC_ARRAY (_hoops_CPAI->points, _hoops_CPAI->allocated, Point);
		ZALLOC_ARRAY (_hoops_CPAI->mapping, _hoops_CPAI->allocated, int);

		HI_Insert_Geometry (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, _hoops_CPAI, true, _hoops_IHSSR);
	}
	if (_hoops_CPAI->count == _hoops_CPAI->allocated) {
		Point *				_hoops_HRRGA = _hoops_CPAI->points;
		int *				_hoops_IPGSA = _hoops_CPAI->mapping;
		int					_hoops_CIGRR = _hoops_CPAI->allocated;

		if (_hoops_CPAI->allocated < 4096)
			_hoops_CPAI->allocated *= 2;
		else
			_hoops_CPAI->allocated += 4096;
		ZALLOC_ARRAY (_hoops_CPAI->points, _hoops_CPAI->allocated, Point);
		_hoops_AIGA (_hoops_HRRGA, _hoops_CIGRR, Point, _hoops_CPAI->points);
		FREE_ARRAY (_hoops_HRRGA, _hoops_CIGRR, Point);
		ZALLOC_ARRAY (_hoops_CPAI->mapping, _hoops_CPAI->allocated, int);
		_hoops_AIGA (_hoops_IPGSA, _hoops_CIGRR, int, _hoops_CPAI->mapping);
		FREE_ARRAY (_hoops_IPGSA, _hoops_CIGRR, int);
	}

	int	offset = _hoops_CPAI->count;

	_hoops_CPAI->count++;

	_hoops_CPAI->points[offset] = a;
	_hoops_CPAI->mapping[offset] = HI_Record_Lightweight_Key ((_hoops_HPAH *)_hoops_CPAI, offset, index);

	if (!BIT (_hoops_RSPPR(_hoops_RIGC, flags), _hoops_APGHP)) {
		Bounding	bounding = Bounding::Create (1, &_hoops_CPAI->points[offset]);
		HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, bounding, null);
		_hoops_SRCP->_hoops_HSRIR.Merge (bounding);
	}

	if (!BIT (_hoops_CPAI->_hoops_RRHH, _hoops_RSPCR) && a.z != 0.0f) {
		_hoops_CPAI->_hoops_RRHH |= _hoops_RSPCR;
		if (!ALLBITS (_hoops_SRCP->_hoops_RCGC, _hoops_ASPCR))
			HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_ASPCR);
	}


	return HOOPS_WORLD->_hoops_GCHCA.table[_hoops_CPAI->mapping[offset]].key;
}



GLOBAL_FUNCTION Marker * HI_Isolate_Marker_From_Multimarker (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GRPGR *			_hoops_CPAI,
	int						offset) {
	Marker *				marker;

	ZALLOC (marker, Marker);
	marker->type = _hoops_PCIP;
	marker->_hoops_CPGPR = _hoops_CPAI->_hoops_CPGPR;

	if (BIT (_hoops_CPAI->mapping[offset], _hoops_RIRIR)) {
		marker->_hoops_RRHH |= _hoops_GGCCA;
		_hoops_CPAI->mapping[offset] &= _hoops_RIRIR;
	}

	marker->_hoops_CSAI = _hoops_CPAI->points[offset];

	HI_Insert_Geometry (_hoops_RIGC, (_hoops_HPAH *)_hoops_CPAI->owner, (Geometry *)marker,
						marker->_hoops_CSAI.z == 0.0f,
						0);

	HI_Replace_Lightweight_Key (_hoops_CPAI->mapping[offset], (_hoops_HPAH *)marker, 0);
	marker->key = HOOPS_WORLD->_hoops_GCHCA.table[_hoops_CPAI->mapping[offset]].key;

	int						count = --_hoops_CPAI->count;

	while (offset < count) {
		int			index = _hoops_CPAI->mapping[offset+1] & ~_hoops_RIRIR;

		_hoops_CPAI->mapping[offset] = _hoops_CPAI->mapping[offset+1];
		_hoops_CPAI->points[offset] = _hoops_CPAI->points[offset+1];

		HOOPS_WORLD->_hoops_GCHCA.table[index].offset = offset++;
	}

	return marker;
}

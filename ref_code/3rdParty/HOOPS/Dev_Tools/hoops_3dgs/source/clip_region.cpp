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
 * $Id: obf_tmp.txt 1.45 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

local	const char	_hoops_SSACR[] = "Return string won't fit in provided space";


#define _hoops_GPAGA	-1
#define _hoops_RPAGA			-2
#define _hoops_APAGA			-3

local const _hoops_IGRCR _hoops_PPAGA[] = {
	{_hoops_RHIH,						_hoops_GRRCR ("mask"),				_hoops_RRRCR, 0, false},
	{_hoops_RPAGA,						_hoops_GRRCR ("clip"),				_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_IPAGA = {
	_hoops_GGAPR (_hoops_PPAGA),	_hoops_PPAGA,
};


local const _hoops_IGRCR _hoops_CPAGA[] = {
	{_hoops_SPAGA,		_hoops_GRRCR ("world"),				_hoops_RRRCR, 0, false},
	{_hoops_SPAGA,		_hoops_GRRCR ("world space"),		_hoops_RRRCR, 0, false},
	{_hoops_GPAGA,		_hoops_GRRCR ("local window"),		_hoops_RRRCR, 0, false},
	{_hoops_GPAGA,		_hoops_GRRCR ("window"),			_hoops_RRRCR, 0, false},
	{_hoops_APAGA,				_hoops_GRRCR ("type"),				_hoops_GHAGA, 1, false, &_hoops_IPAGA},
};


local Attribute *_hoops_RHAGA (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH alter *			item,
	Attribute const *			_hoops_CPACR,
	Attribute alter *			_hoops_SPACR) 
{
	_hoops_IRAIR const *	_hoops_AHAGA = (_hoops_IRAIR const *)_hoops_CPACR;
	_hoops_IRAIR alter *	_hoops_PHAGA = (_hoops_IRAIR alter *)_hoops_SPACR;

	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED(item);
	UNREFERENCED(_hoops_AHAGA);

	return _hoops_PHAGA;
}


GLOBAL_FUNCTION bool HI_Set_Polygonal_Clip_Region (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH *					item, 
	_hoops_IRAIR *				_hoops_PPGGA)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_CLIP_REGION, _hoops_RHAGA, _hoops_PPGGA);
}


HC_INTERFACE void HC_CDECL HC_Set_Polygonal_Clip_Region (
	int							count,
	Point const *				points,
	char const *				options) 
{
	_hoops_PAPPR context("Set_Polygonal_Clip_Region");

	CODE_GENERATION (
		int	   count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		if (count > 0)
			HI_Dump_Code (Sprintf_D (null, "HC_POINT* points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", count));
		_hoops_RGGA (count2-- <= 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", count2, points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", count2, points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n", count2, points[count2].z));
		}
		HI_Dump_Code (Sprintf_D (null, "HC_Set_Polygonal_Clip_Region(%d, ", count));
		HI_Dump_Code (Sprintf_S (null, "%s, ", (count ? "points" : "NULL")));
		if (options)
			HI_Dump_Code (Sprintf_S (null, "%S);\n", options));
		else
			HI_Dump_Code ("0);\n");
		if (count > 0)
			HI_Dump_Code ("free (points);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	
	bool			used = false;
	_hoops_IRAIR *	_hoops_PPGGA;
	ZALLOC (_hoops_PPGGA, _hoops_IRAIR);
	_hoops_PPGGA->count = count;
	_hoops_PPGGA->points = (Point *)HI_Clone_Anything (points, count*sizeof(Point));

	Option_Value *	option_list;
	Option_Value *	option;

	_hoops_HIACR (_hoops_HHAGA, _hoops_CPAGA);

	int	_hoops_IHAGA = HI_Parse_Options (context, options, _hoops_CIACR (_hoops_HHAGA), &option_list, _hoops_SIACR);

	if (_hoops_IHAGA) {
		if ((option = option_list) != null) do {
			switch (option->type->id) {
				case _hoops_SPAGA: {
					_hoops_PPGGA->flags |= _hoops_SPAGA;
				}	break;

				case _hoops_GPAGA: {
					_hoops_PPGGA->flags &= ~_hoops_SPAGA;
				}	break;

				case _hoops_APAGA: {
					Option_Value *	_hoops_CHAGA = option->value.option_list;

					if (_hoops_CHAGA->type->id == _hoops_RHIH)
						_hoops_PPGGA->flags |= _hoops_RHIH;
					else
						_hoops_PPGGA->flags &= ~_hoops_RHIH;
				}	break;


				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized clip region option type");
					goto _hoops_PRSPR;
				}	
			}
		} while ((option = option->next) != null);

		HI_Free_Option_List (context, option_list);
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SHAGA)) != null) {
		used = HI_Set_Polygonal_Clip_Region (context, target, _hoops_PPGGA);
		_hoops_IRRPR();
	}

_hoops_PRSPR:
	if (!used) {
		FREE_ARRAY (_hoops_PPGGA->points, count, Point);
		FREE (_hoops_PPGGA, _hoops_IRAIR);
	}
}


HC_INTERFACE void HC_CDECL HC_UnSet_Clip_Region (void) 
{
	_hoops_PAPPR context("UnSet_Clip_Region");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Clip_Region ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SHAGA|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_CLIP_REGION);
		_hoops_IRRPR();
	}
}




HC_INTERFACE void HC_CDECL HC_Show_Clip_Region (
	int alter *				loops,
	int alter *				lengths,
	Point alter *			points,
	char *					spec) 
{
	_hoops_PAPPR context("Show_Clip_Region");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Clip_Region () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GIAGA)) != null) {
		_hoops_IRAIR *	_hoops_PPGGA;
		if ((_hoops_PPGGA = (_hoops_IRAIR *)HI_Find_Attribute (context, target, HK_CLIP_REGION)) != null) {

			HI_Show_Clip_Region(_hoops_PPGGA, loops, lengths, points, spec, -1);
			_hoops_HPRH (_hoops_PPGGA);
		}
		_hoops_IRRPR();
	}
#endif
}

HC_INTERFACE void HC_CDECL HC_Show_Clip_Region_Size (
	int alter *				loops,
	int alter *				total,
	char *					spec) 
{
	_hoops_PAPPR context("Show_Clip_Region_Size");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Clip_Region_Size () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GIAGA)) != null) {

		_hoops_IRAIR *	_hoops_PPGGA;
		if ((_hoops_PPGGA = (_hoops_IRAIR *)HI_Find_Attribute (context, target, HK_CLIP_REGION)) != null) {
		
			HI_Show_Clip_Region(_hoops_PPGGA, loops, total, 0, spec, -1);
			_hoops_HPRH (_hoops_PPGGA);
		}
		_hoops_IRRPR();
	}
#endif
}



#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Clip_Region (
	int						count,
	Key const *				keys,
	int alter *				loops,
	int alter *				lengths,
	Point alter *			points,
	char *					spec) 
{
	_hoops_PAPPR context("PShow_Net_Clip_Region");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Clip_Region () */\n");
	);

	_hoops_IRAIR *	_hoops_PPGGA;
	if ((_hoops_PPGGA = (_hoops_IRAIR *) HI_Find_Attribute_And_Lock(context, _hoops_GIAGA, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Clip_Region(_hoops_PPGGA, loops, lengths, points, spec, -1);
		_hoops_HPRH (_hoops_PPGGA);
		_hoops_IRRPR();
	}
	else {
		*loops = 0;
		*lengths = 0;
		HI_Return_Chars(spec, -1, "", 0);
	}
#endif
}
#endif


#ifndef _hoops_ARPCR


HC_INTERFACE void HC_CDECL HC_PShow_Net_Clip_Region_Size (
	int						count,
	Key const *				keys,
	int alter *				loops,
	int alter *				total,
	char *					spec) 
{
	_hoops_PAPPR context("PShow_Net_Clip_Region_Size");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Clip_Region_Size () */\n");
	);

	_hoops_IRAIR *	_hoops_PPGGA;
	if ((_hoops_PPGGA = (_hoops_IRAIR *) HI_Find_Attribute_And_Lock(context, _hoops_GIAGA, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Clip_Region(_hoops_PPGGA, loops, total, 0, spec, -1);
		_hoops_HPRH (_hoops_PPGGA);
		_hoops_IRRPR();
	}
	else {
		*loops = 0;
		*total = 0;
		HI_Return_Chars(spec, -1, "", 0);
	}
#endif
}

#endif



GLOBAL_FUNCTION void HI_Show_Clip_Region (
	_hoops_IRAIR *			_hoops_PPGGA,
	int alter *				loops,
	int alter *				lengths,
	Point alter				*points,
	char *					result,
	int						_hoops_RIAGA) {
	char *					_hoops_ASAPR = result;
	char *					_hoops_PSAPR;

	if (_hoops_RIAGA == -1)
		_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;		/* _hoops_IHRPR _hoops_IAHA */
	else
		_hoops_PSAPR = _hoops_ASAPR + _hoops_RIAGA;			/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

	*loops = _hoops_PPGGA->count > 0 ? 1 : 0;
	*lengths = _hoops_PPGGA->count;

	if(points)
		_hoops_AIGA (_hoops_PPGGA->points, _hoops_PPGGA->count, Point, points);


	if (BIT (_hoops_PPGGA->flags, _hoops_SPAGA))
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "world,", null);
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "window,", null);

	if (BIT (_hoops_PPGGA->flags, _hoops_RHIH))
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "type=mask,", null);
	else
		_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "type=clip,", null);

	if (_hoops_ASAPR != null) {
		if (_hoops_ASAPR > result) --_hoops_ASAPR;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */

		if (_hoops_RIAGA == -1) {	/* _hoops_IHRPR _hoops_IAHA _hoops_SRHR */
			if (_hoops_ASAPR == _hoops_PSAPR)
				_hoops_ASAPR = null;		/* _hoops_PPPPR'_hoops_RA _hoops_SIHRR */
			else
				*_hoops_ASAPR = '\0';
		}
		else					/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA _hoops_SRHR */
			_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR) *_hoops_ASAPR++ = ' ';
	}

	if (_hoops_ASAPR == null)
		HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR); /* _hoops_SARS'_hoops_RA _hoops_SIHRR */
}





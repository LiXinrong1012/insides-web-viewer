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
 * $Id: obf_tmp.txt 1.96 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


#ifndef DISABLE_COLOR_MAPS

local Attribute *_hoops_CSPRA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR)
{
	_hoops_RHAH const *		_hoops_SSPRA = (_hoops_RHAH const *)_hoops_CPACR;
	_hoops_RHAH alter *		_hoops_GGHRA = (_hoops_RHAH alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_SSPRA);

	_hoops_GGHRA->time_stamp = HOOPS_WORLD->_hoops_GPPI+1;

	_hoops_CRCP * _hoops_SRCP = (_hoops_CRCP *)item;
	ASSERT(_hoops_SRCP->type == _hoops_IRCP);

	if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPRRA))
		HI_Propagate_Maybes (_hoops_RIGC, _hoops_SRCP, _hoops_HPRRA);

	return _hoops_GGHRA;
}

#endif


GLOBAL_FUNCTION bool HI_Set_Color_Map (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_RHAH *				_hoops_CSIR)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_COLOR_MAP, _hoops_CSPRA, _hoops_CSIR);
}



HC_INTERFACE void HC_CDECL HC_Set_Color_Map_By_Value (
	char const *		style,
	int					count,
	RGB const *			values)
{
	_hoops_PAPPR context("Set_Color_Map_By_Value");

#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_RGB* values = (HC_RGB*) malloc(sizeof(HC_RGB)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].red = %f;	 ", count2, values[count2].red));
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].green = %f;	 ", count2, values[count2].green));
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].blue = %f;\n", count2, values[count2].blue));
		}
		HI_Dump_Code (Sprintf_SD (null, "HC_Set_Color_Map_By_Value (%S, %d, values);\n",style, count));
		HI_Dump_Code ("free (values);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	bool		used = false;
	_hoops_RHAH *	_hoops_CSIR;
	ZALLOC (_hoops_CSIR, _hoops_RHAH);

	if (HI_Parse_Color_Map_By_Value (context, style, count, values, _hoops_CSIR)) {
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_RGHRA)) != null) {
			used = HI_Set_Color_Map (context, target, _hoops_CSIR);
			_hoops_IRRPR();
		}
	}

	if (!used) {
		if (_hoops_CSIR->length > 0) {
			HI_Free_Material_Names (_hoops_CSIR->_hoops_HAA, _hoops_CSIR->length);
			FREE_ARRAY (_hoops_CSIR->_hoops_HAA, _hoops_CSIR->length, Named_Material);
		}
		FREE (_hoops_CSIR, _hoops_RHAH);
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_UnSet_Color_Map (void)
{
	_hoops_PAPPR context("UnSet_Color_Map");

#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Color_Map ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RGHRA|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_COLOR_MAP);
		_hoops_IRRPR();
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Set_Color_Map (
	char const *		_hoops_HSHIR)
{
	_hoops_PAPPR context("Set_Color_Map");

#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Color_Map (%S);\n", _hoops_HSHIR));
	);

	bool		used = false;
	_hoops_RHAH *	_hoops_CSIR;
	ZALLOC (_hoops_CSIR, _hoops_RHAH);

	if (HI_Parse_Color_Map (context, _hoops_HSHIR, _hoops_CSIR)) {
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_RGHRA)) != null) {
			used = HI_Set_Color_Map (context, target, _hoops_CSIR);
			_hoops_IRRPR();
		}
	}

	if (!used) {
		if (_hoops_CSIR->length > 0) {
			HI_Free_Material_Names (_hoops_CSIR->_hoops_HAA, _hoops_CSIR->length);
			FREE_ARRAY (_hoops_CSIR->_hoops_HAA, _hoops_CSIR->length, Named_Material);
		}
		FREE (_hoops_CSIR, _hoops_RHAH);
	}
#endif
}


#ifndef DISABLE_SHOW
#ifndef DISABLE_COLOR_MAPS
local void _hoops_AGHRA (
	_hoops_RHAH *			_hoops_CSIR,
	char *				style,
	int					_hoops_GSPRA,
	int *				_hoops_PGHRA,
	RGB *				values)
{
	Named_Material *		_hoops_ISHIR;
	int						remaining;


	HI_Return_Chars (style, _hoops_GSPRA, "rgb", 3);
	*_hoops_PGHRA = 0;

	_hoops_ISHIR = _hoops_CSIR->_hoops_HAA;

	if ((remaining = _hoops_CSIR->length) > 0) do {
		if (ANYBIT (_hoops_ISHIR->_hoops_PRGRA, ~(M_DIFFUSE|_hoops_RHGRA)) ||
			_hoops_ISHIR->_hoops_SCA != null) {
			HE_ERROR (HEC_COLOR_MAP, HES_COMPLEX_COLOR, "Can not return values for other than a pure diffuse color");
			return;
		}

		if (BIT (_hoops_ISHIR->_hoops_PRGRA, M_DIFFUSE)) {	// _hoops_GSSR _hoops_AGIR
			values->red = _hoops_ISHIR->_hoops_CSHR.red;
			values->green = _hoops_ISHIR->_hoops_CSHR.green;
			values->blue = _hoops_ISHIR->_hoops_CSHR.blue;
		}
		else											// _hoops_PIHA _hoops_SHH _hoops_PCCP _hoops_RHPA _hoops_GGAGA
			values->red = values->green = values->blue = -1.0f;

		++values;
		++_hoops_ISHIR;

		++*_hoops_PGHRA;	/* _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_RIHH, _hoops_RH _hoops_RPR _hoops_GRS _hoops_SHH _hoops_RH _hoops_PHI _hoops_SGS _hoops_SR _hoops_GGHP _hoops_RHIR */
	}
	_hoops_RGGA (--remaining == 0);
}
#endif
#endif



HC_INTERFACE void HC_CDECL HC_Show_Color_Map_By_Value (
	char *				style,
	int *				_hoops_PGHRA,
	RGB *				values)
{
	_hoops_PAPPR context("Show_Color_Map_By_Value");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Color_Map_By_Value () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HGHRA)) != null) {
		_hoops_RHAH *		_hoops_CSIR;
		if ((_hoops_CSIR = (_hoops_RHAH *)HI_Find_Attribute (context, target, HK_COLOR_MAP)) != null) {
			_hoops_AGHRA (_hoops_CSIR, style, -1, _hoops_PGHRA, values);
			_hoops_HPRH (_hoops_CSIR);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}



#ifndef DISABLE_SHOW
#ifndef DISABLE_COLOR_MAPS

local void _hoops_IGHRA (
	_hoops_RHAH *			_hoops_CSIR,
	int	*				_hoops_CGHRA) {
	char 				_hoops_HSHIR[4096];
	char *				_hoops_ASAPR;
	char *				_hoops_PSAPR;
	Named_Material *	_hoops_ISHIR;
	int					count;

	*_hoops_CGHRA = 0;

	if ((count = _hoops_CSIR->length) > 0) {
		_hoops_ISHIR = _hoops_CSIR->_hoops_HAA;
		do {
			_hoops_ASAPR = _hoops_HSHIR;
			_hoops_PSAPR = _hoops_ASAPR + 4096;

			_hoops_ASAPR = HI_Show_Material (_hoops_ASAPR, _hoops_PSAPR, _hoops_ISHIR, null, true);

			if (_hoops_ASAPR != null) {
				*_hoops_CGHRA += (_hoops_ASAPR-_hoops_HSHIR)+1; // 1 _hoops_IH _hoops_RH ','
				if (_hoops_ASAPR == _hoops_PSAPR) {
					_hoops_ASAPR = null;
					break;
				}
			}
			else
				break;

			++_hoops_ISHIR;
		}
		_hoops_RGGA (--count == 0);

		if (_hoops_ASAPR == null) {
			HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, "Unable to format color map - return buffer overflow");
			_hoops_CGHRA = 0;
		}
		else
			_hoops_CGHRA -= 1; // _hoops_HASIR _hoops_CGHI _hoops_RRCIR
	}
}



local void _hoops_SGHRA (
	_hoops_RHAH *			_hoops_CSIR,
	char *				_hoops_HSHIR,
	int					_hoops_GRHRA) {
	char *				_hoops_ASAPR;
	char *				_hoops_PSAPR;
	Named_Material *	_hoops_ISHIR;
	int					count;

	if ((count = _hoops_CSIR->length) > 0) {
		_hoops_ASAPR = _hoops_HSHIR;

		if (_hoops_GRHRA == -1)
			_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;	/* _hoops_IHRPR _hoops_IAHA */
		else
			_hoops_PSAPR = _hoops_ASAPR + _hoops_GRHRA;				/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

		_hoops_ISHIR = _hoops_CSIR->_hoops_HAA;
		do {
			_hoops_ASAPR = HI_Show_Material (_hoops_ASAPR, _hoops_PSAPR, _hoops_ISHIR, null, true);

			if (_hoops_ASAPR != null) {
				*_hoops_ASAPR++ = ',';
				if (_hoops_ASAPR == _hoops_PSAPR) {
					if (count > 1)
						_hoops_ASAPR = null;
					break;
				}
			}
			else
				break;

			++_hoops_ISHIR;
		}
		_hoops_RGGA (--count == 0);

		if (_hoops_ASAPR == null) {
			HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, "Unable to format color map - return buffer overflow");
			_hoops_ASAPR = _hoops_HSHIR; /* _hoops_ISSC _hoops_IS _hoops_RH _hoops_RSGI */
		}
		else
			--_hoops_ASAPR;	/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR */

		if (_hoops_GRHRA == -1)
			*_hoops_ASAPR = '\0';							/* _hoops_IHRPR _hoops_IAHA */
		else
			while (_hoops_ASAPR < _hoops_PSAPR) *_hoops_ASAPR++ = ' ';		/* _hoops_RGPCR _hoops_IAHA */
	}
	else
		HI_Return_Chars (_hoops_HSHIR, _hoops_GRHRA, "", 0);
}
#endif
#endif



HC_INTERFACE void HC_CDECL HC_Show_Color_Map (
	char *			_hoops_HSHIR)
{
	_hoops_PAPPR context("Show_Color_Map");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Color_Map () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HGHRA)) != null) {
		_hoops_RHAH *		_hoops_CSIR;
		if ((_hoops_CSIR = (_hoops_RHAH *)HI_Find_Attribute (context, target, HK_COLOR_MAP)) != null) {
			_hoops_SGHRA (_hoops_CSIR, _hoops_HSHIR, -1);
			_hoops_HPRH (_hoops_CSIR);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}




#ifndef DISABLE_SHOW
#ifndef DISABLE_COLOR_MAPS

local void _hoops_RRHRA (
	_hoops_RHAH *		_hoops_CSIR,
	int				offset,
	char *			style,
	int				_hoops_GSPRA,
	float *			x,
	float *			y,
	float *			z) {

	HI_Return_Chars (style, _hoops_GSPRA, "rgb", 3);

	if (offset >= _hoops_CSIR->length) {
		HE_ERROR (HEC_COLOR_MAP, HES_INVALID_OFFSET,
				  Sprintf_DD (null,"Can't look at color map at offset %d - map only has %d entries", offset, _hoops_CSIR->length));
		return;
	}

	/* _hoops_RH _hoops_SPI _hoops_HH _hoops_IGRH _hoops_PAH _hoops_SHH _hoops_ARP, _hoops_HIH _hoops_RGAR _hoops_RPP _hoops_SCSI _hoops_CCA _hoops_RH _hoops_SPI _hoops_HAIR _hoops_IGRH */
	if (ANYBIT (_hoops_CSIR->_hoops_HAA[offset]._hoops_PRGRA, ~(M_DIFFUSE|_hoops_RHGRA)) ||
		_hoops_CSIR->_hoops_HAA[offset]._hoops_PRGRA == _hoops_RHGRA) {
		HE_ERROR (HEC_COLOR_MAP, HES_COMPLEX_COLOR, "Can not return values for other than a pure diffuse color");
		return;
	}

	if (BIT (_hoops_CSIR->_hoops_HAA[offset]._hoops_PRGRA, M_DIFFUSE)) {
		*x = _hoops_CSIR->_hoops_HAA[offset]._hoops_CSHR.red;
		*y = _hoops_CSIR->_hoops_HAA[offset]._hoops_CSHR.green;
		*z = _hoops_CSIR->_hoops_HAA[offset]._hoops_CSHR.blue;
	}
	else
		*x = *y = *z = -1.0f;	// _hoops_RIP _hoops_RHPA _hoops_GGAGA
}
#endif
#endif


HC_INTERFACE void HC_CDECL HC_Show_One_Color_Map_By_Value (
	int						offset,
	char *					style,
	float *					x,
	float *					y,
	float *					z)
{
	_hoops_PAPPR context("Show_One_Color_Map_By_Value");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Color_Map_By_Value () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HGHRA)) != null) {
		_hoops_RHAH *		_hoops_CSIR;
		if ((_hoops_CSIR = (_hoops_RHAH *)HI_Find_Attribute (context, target, HK_COLOR_MAP)) != null) {
			_hoops_RRHRA (_hoops_CSIR, offset, style, -1, x, y, z);
			_hoops_HPRH (_hoops_CSIR);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}




#ifndef DISABLE_SHOW
#ifndef DISABLE_COLOR_MAPS

local void _hoops_ARHRA (
	_hoops_RHAH *		_hoops_CSIR,
	int				offset,
	char *			_hoops_HSHIR,
	int				_hoops_GRHRA) {
	char			buf[4096];
	char *			_hoops_ASAPR = buf;
	char *_hoops_PSAPR = buf+_hoops_GGAPR(buf)-1;

	if (offset >= _hoops_CSIR->length) {
		HE_ERROR (HEC_COLOR_MAP, HES_INVALID_OFFSET,
				  Sprintf_DD (null,
						"Can't look at color map offset %d - only has %d entries",
						offset, _hoops_CSIR->length));
		return;
	}

	_hoops_ASAPR = HI_Show_Material (_hoops_ASAPR, _hoops_PSAPR, &_hoops_CSIR->_hoops_HAA[offset], null, false);

	if (_hoops_ASAPR == null) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unable to format color map color");
		_hoops_ASAPR = buf;
	}

	HI_Return_Chars (_hoops_HSHIR, _hoops_GRHRA, buf, (int)(_hoops_ASAPR - buf));
}
#endif
#endif


HC_INTERFACE void HC_CDECL HC_Show_One_Color_Map (
	int						offset,
	char *					_hoops_HSHIR)
{
	_hoops_PAPPR context("Show_One_Color_Map");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Color_Map () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HGHRA)) != null) {
		_hoops_RHAH *		_hoops_CSIR;
		if ((_hoops_CSIR = (_hoops_RHAH *)HI_Find_Attribute (context, target, HK_COLOR_MAP)) != null) {
			_hoops_ARHRA (_hoops_CSIR, offset, _hoops_HSHIR, -1);
			_hoops_HPRH (_hoops_CSIR);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}




#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Color_Map_By_Value (
	int						count,
	Key const *				keys,
	char *					style,
	int	*					_hoops_PGHRA,
	RGB *					values)
{
	_hoops_PAPPR context("PShow_Net_Color_Map_By_Value");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Color_Map_By_Value () */\n");
	);

	_hoops_RHAH *		_hoops_CSIR;
	if ((_hoops_CSIR = (_hoops_RHAH *) HI_Find_Attribute_And_Lock(context, _hoops_HGHRA, _hoops_HRPCR, count, keys)) != null) {
		_hoops_AGHRA (_hoops_CSIR, style, -1, _hoops_PGHRA, values);
		_hoops_HPRH (_hoops_CSIR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(style, -1, "", 0);
#endif
#endif
}
#endif



#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_Net_Color_Map (
	int						count,
	Key const *				keys,
	char *					_hoops_HSHIR)
{
	_hoops_PAPPR context("PShow_Net_Color_Map");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Color_Map () */\n");
	);

	_hoops_RHAH *		_hoops_CSIR;
	if ((_hoops_CSIR = (_hoops_RHAH *) HI_Find_Attribute_And_Lock(context, _hoops_HGHRA, _hoops_HRPCR, count, keys)) != null) {
		_hoops_SGHRA (_hoops_CSIR, _hoops_HSHIR, -1);
		_hoops_HPRH (_hoops_CSIR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(_hoops_HSHIR, -1, "", 0);

#endif
#endif
}
#endif



#ifndef _hoops_ARPCR

HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Color_Map_By_V (
	int						count,
	Key const *				keys,
	int						offset,
	char *					style,
	float *					x,
	float *					y,
	float *					z)
{
	_hoops_PAPPR context("PShow_One_Net_Color_Map_By_");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Color_Map_By_ () */\n");
	);

	_hoops_RHAH *		_hoops_CSIR;
	if ((_hoops_CSIR = (_hoops_RHAH *) HI_Find_Attribute_And_Lock(context, _hoops_HGHRA, _hoops_HRPCR, count, keys)) != null) {
		_hoops_RRHRA (_hoops_CSIR, offset, style, -1, x, y, z);
		_hoops_HPRH (_hoops_CSIR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(style, -1, "", 0);
#endif
#endif
}
#endif



#ifndef _hoops_ARPCR


HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Color_Map (
	int						count,
	Key const *				keys,
	int						offset,
	char *					_hoops_HSHIR)
{
	_hoops_PAPPR context("PShow_One_Net_Color_Map");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Color_Map () */\n");
	);

	_hoops_RHAH *		_hoops_CSIR;
	if ((_hoops_CSIR = (_hoops_RHAH *) HI_Find_Attribute_And_Lock(context, _hoops_HGHRA, _hoops_HRPCR, count, keys)) != null) {
		_hoops_ARHRA (_hoops_CSIR, offset, _hoops_HSHIR, -1);
		_hoops_HPRH (_hoops_CSIR);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(_hoops_HSHIR, -1, "", 0);

#endif
#endif
}

#endif




HC_INTERFACE void HC_CDECL HC_Show_Color_Map_Count (
	int *				value)
{
	_hoops_PAPPR context("Show_Color_Map_Count");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Color_Map_Count () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HGHRA)) != null) {
		_hoops_RHAH *	_hoops_CSIR;
		if ((_hoops_CSIR = (_hoops_RHAH *)HI_Find_Attribute (context, target, HK_COLOR_MAP)) != null) {
			*value = _hoops_CSIR->length;
			_hoops_HPRH (_hoops_CSIR);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Color_Map_Count (
	int				count,
	Key const *		keys,
	int *			value)
{
	_hoops_PAPPR context("PShow_Net_Color_Map_Count");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Color_Map_Count () */\n");
	);

	_hoops_RHAH *		_hoops_CSIR;
	if ((_hoops_CSIR = (_hoops_RHAH *) HI_Find_Attribute_And_Lock(context, _hoops_HGHRA, _hoops_HRPCR, count, keys)) != null) {
		*value = _hoops_CSIR->length;
		_hoops_HPRH (_hoops_CSIR);
		_hoops_IRRPR();
	}
	else
		*value = 0;

#endif
#endif
}
#endif



HC_INTERFACE void HC_CDECL HC_Show_Color_Map_Length (
	int *				value)
{
	_hoops_PAPPR context("Show_Color_Map_Length");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Color_Map_Length () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HGHRA)) != null) {
		_hoops_RHAH *		_hoops_CSIR;
		if ((_hoops_CSIR = (_hoops_RHAH *)HI_Find_Attribute (context, target, HK_COLOR_MAP)) != null) {
			_hoops_IGHRA (_hoops_CSIR, value);
			_hoops_HPRH (_hoops_CSIR);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Color_Map_Length (
	int					count,
	Key const *			keys,
	int *				value)
{
	_hoops_PAPPR context("PShow_Net_Color_Map_Length");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Color_Map_Length () */\n");
	);

	_hoops_RHAH *		_hoops_CSIR;
	if ((_hoops_CSIR = (_hoops_RHAH *) HI_Find_Attribute_And_Lock(context, _hoops_HGHRA, _hoops_HRPCR, count, keys)) != null) {
		_hoops_IGHRA (_hoops_CSIR, value);
		_hoops_HPRH (_hoops_CSIR);
		_hoops_IRRPR();
	}
	else
		*value = 0;

#endif
#endif
}
#endif


GLOBAL_FUNCTION bool HI_Parse_Color_Map (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			_hoops_PRHRA,
	_hoops_RHAH *				_hoops_APHCR)
{
#ifndef DISABLE_COLOR_MAPS
	_hoops_HCRPR					_hoops_HSHIR;
	char *					p, *_hoops_HRHRA;
	int						count;
	Named_Material *		_hoops_PAGR;
	int						_hoops_RGPRA;
	char					_hoops_PPARA;
	char *					_hoops_IRHRA;
	const	char			_hoops_CRHRA[] = "Null (', ,') name found in color list";
	int						i;

	HI_Canonize_Chars (_hoops_PRHRA, &_hoops_HSHIR);

	if (_hoops_HSHIR.length == 0) {
		_hoops_APHCR->length = 0;
		_hoops_APHCR->_hoops_SRHRA = 0;
		_hoops_APHCR->time_stamp = HOOPS_WORLD->_hoops_GPPI;
		return true;
	}

	p = _hoops_HSHIR.text;
	_hoops_HRHRA = p + _hoops_HSHIR.length;

	if (*p == ',' || *(_hoops_HRHRA-1) == ',') {
		HE_ERROR (HEC_COLOR_MAP, HES_NULL_COLOR_NAME, _hoops_CRHRA);
		_hoops_RGAIR (_hoops_HSHIR);
		return false;
	}

	count = 1;

	_hoops_RGPRA = 0;
	_hoops_PPARA = '\0';
	while (*p) {
		if (*p == '"' || *p == '\'' || *p == '`') {
			if (*p == _hoops_PPARA || !_hoops_PPARA)
				_hoops_PPARA ^= *p;
		}
		else if (!_hoops_PPARA) {
			if (*p == '(')
				++_hoops_RGPRA;
			else if (*p == ')')
				--_hoops_RGPRA;
			else if (*p == ',' && _hoops_RGPRA <= 0)
				++count;
		}

		++p;
	}
	if (_hoops_RGPRA != 0) {
		HE_ERROR (HEC_COLOR_MAP, HES_BAD_PARENTHESES, "Unbalanced parentheses in color list");
		_hoops_RGAIR (_hoops_HSHIR);
		return false;
	}

	_hoops_APHCR->length = count;

	ZALLOC_ARRAY (_hoops_PAGR, count, Named_Material);
	_hoops_APHCR->_hoops_HAA = _hoops_PAGR;
	_hoops_APHCR->_hoops_SRHRA = 0;
	_hoops_APHCR->time_stamp = HOOPS_WORLD->_hoops_GPPI;

	_hoops_IRHRA = p = _hoops_HSHIR.text;
	count = _hoops_APHCR->length;
	_hoops_PCCAR {
		_hoops_HCRPR					_hoops_GAHRA;

		if (count > 1) {		/* _hoops_SSS _hoops_RH _hoops_RRCIR */
			_hoops_RGPRA = 0;
			_hoops_PPARA = '\0';
			while (*p) {
				if (*p == '"' || *p == '\'' || *p == '`') {
					if (*p == _hoops_PPARA || !_hoops_PPARA)
						_hoops_PPARA ^= *p;
				}
				else if (!_hoops_PPARA) {
					if (*p == '(')
						++_hoops_RGPRA;
					else if (*p == ')')
						--_hoops_RGPRA;
					else if (*p == ',' && _hoops_RGPRA <= 0)
						break;
				}

				++p;
			}

			while (*(p-1) == ' ') --p;
		}
		else
			p = _hoops_HRHRA;

		_hoops_GAHRA.text = _hoops_IRHRA;
		if ((_hoops_GAHRA.length = p - _hoops_IRHRA) <= 0) {
			HE_ERROR (HEC_COLOR_MAP, HES_NULL_COLOR_NAME, _hoops_CRHRA);
			break;
		}

		if (_hoops_GAHRA.length == 1 && _hoops_GAHRA.text[0] == '*' ||
			_hoops_GAHRA.length == 2 && _hoops_GAHRA.text[0] == '(' && _hoops_GAHRA.text[1] == ')') {
			// _hoops_GGAGA _hoops_APIR _hoops_RARP
		}
		else {
			_hoops_HCRPR _hoops_RAHRA;
			_hoops_RAHRA.length = _hoops_GAHRA.length;
			ALLOC_ARRAY(_hoops_RAHRA.text, _hoops_GAHRA.length+1, char);
			COPY_MEMORY(_hoops_GAHRA.text, _hoops_GAHRA.length, _hoops_RAHRA.text);
			_hoops_RAHRA.text[_hoops_GAHRA.length] = '\0';
			if (!HI_Evaluate_Color (_hoops_RIGC, &_hoops_RAHRA, _hoops_PAGR, 0, true)) {
				_hoops_RGAIR (_hoops_RAHRA);
				break;
			}
			_hoops_RGAIR (_hoops_RAHRA);

			if (BIT (_hoops_PAGR->_hoops_PRGRA, M_DIFFUSE))
				HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_PAGR->_hoops_CSHR, &_hoops_PAGR->_hoops_CSHR);
			for (i=0; i<_hoops_CRGRA; i++) {
				if (BIT (_hoops_PAGR->_hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i]))
					HI_HLS_To_RGB ((_hoops_PACHR const *)&_hoops_PAGR->color[i], &_hoops_PAGR->color[i]);
			}

			_hoops_APHCR->_hoops_SRHRA |= _hoops_PAGR->_hoops_PRGRA;
			_hoops_APHCR->time_stamp = HOOPS_WORLD->_hoops_GPPI;

			if (_hoops_PAGR->_hoops_SCA)
				_hoops_PAGR->_hoops_PRGRA |= _hoops_CHGRA;
		}

		_hoops_PAGR++;
		if (--count == 0)
			break;

		_hoops_RGGA (*p == ',')
			++p;
		while (*++p == ' ') {}
		_hoops_IRHRA = p;
	}

	_hoops_RGAIR (_hoops_HSHIR);

	if (count != 0) {
		HI_Free_Material_Names (_hoops_APHCR->_hoops_HAA, _hoops_APHCR->length - count);
		FREE_ARRAY (_hoops_APHCR->_hoops_HAA, _hoops_APHCR->length, Named_Material);
		return false;
	}

	return true;
#else
	return false;
#endif
}



#ifndef DISABLE_COLOR_MAPS

local void _hoops_AAHRA (
	_hoops_RHAH	*_hoops_APHCR,
	char const		*message) {

	HE_ERROR (HEC_COLOR_MAP, HES_OUT_OF_RANGE, message);
	FREE_ARRAY (_hoops_APHCR->_hoops_HAA, _hoops_APHCR->length, Named_Material);
}

#endif

GLOBAL_FUNCTION bool HI_Parse_Color_Map_By_Value (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			style,
	int						count,
	RGB const *				in,
	_hoops_RHAH *				_hoops_APHCR)
{
	UNREFERENCED(_hoops_RIGC);

#ifndef DISABLE_COLOR_MAPS

	if (count < 0) {
		HE_ERROR (HEC_COLOR_MAP, HES_INVALID_SIZE, Sprintf_D (null, "%d is an unreasonable color map size", count));
		return false;
	}

	if (count == 0) {
		_hoops_APHCR->length = 0;
		_hoops_APHCR->_hoops_SRHRA = 0;
		_hoops_APHCR->time_stamp = HOOPS_WORLD->_hoops_GPPI;
		return true;
	}

	Named_Material *	_hoops_PAGR;
	ZALLOC_ARRAY (_hoops_PAGR, count, Named_Material);
	_hoops_APHCR->_hoops_HAA = _hoops_PAGR;
	_hoops_APHCR->length = count;
	_hoops_APHCR->_hoops_SRHRA = M_DIFFUSE;
	_hoops_APHCR->time_stamp = HOOPS_WORLD->_hoops_GPPI;

	if ((style[0] == 'r' || style[0] == 'R') &&
		(style[1] == 'g' || style[1] == 'G') &&
		(style[2] == 'b' || style[2] == 'B')) {
		do {
			if (in->red == -1.0f && in->green == -1.0f && in->blue == -1.0f) {	// _hoops_GRH _hoops_AGIR _hoops_IH "_hoops_RHPA" _hoops_RARP
				// _hoops_IGPC _hoops_RAAP _hoops_RHPA
				_hoops_PAGR->_hoops_CSHR = *in;
			}
			else {
				if (!(0.0f <= in->red && in->red <= 1.0f &&
					  0.0f <= in->green && in->green <= 1.0f &&
					  0.0f <= in->blue && in->blue <= 1.0f)) {
					_hoops_AAHRA (_hoops_APHCR, "RGB value not in the range 0..1");
					return false;
				}

				_hoops_PAGR->_hoops_PRGRA = M_DIFFUSE;
				_hoops_PAGR->_hoops_CSHR.red = in->red;
				_hoops_PAGR->_hoops_CSHR.green = in->green;
				_hoops_PAGR->_hoops_CSHR.blue = in->blue;
			}
			++in, ++_hoops_PAGR;
		}
		_hoops_RGGA (--count == 0);
	}
	else if ((style[1] == 'l' || style[1] == 'L') &&
		(style[0] == 'h' || style[0] == 'H') &&	 /* (_hoops_GGSR _hoops_IIGR _hoops_AGR _hoops_GPP _hoops_AHAR) */
		(style[2] == 's' || style[2] == 'S')) {
		do {
			if (in->red == -1.0f && in->green == -1.0f && in->blue == -1.0f) {	// _hoops_GRH _hoops_AGIR _hoops_IH "_hoops_RHPA" _hoops_RARP
				// _hoops_IGPC _hoops_RAAP _hoops_RHPA
				_hoops_PAGR->_hoops_CSHR = *in;
			}
			else {
				_hoops_PACHR			_hoops_HACHR;

				if (!(-1e5f <= in->red && in->red <= 1e5f)) {
					_hoops_AAHRA (_hoops_APHCR, "Hue has unreasonable magnitude");
					return false;
				}

				if (!(0.0f <= in->green && in->green <= 1.0f)) {
					_hoops_AAHRA (_hoops_APHCR, "Lightness is not in the range 0..1");
					return false;
				}

				if (in->blue < 0.0f) {
					_hoops_AAHRA (_hoops_APHCR, "Saturation is negative");
					return false;
				}

				if ((in->green < 0.5f && in->blue > 2.0f*in->green) ||
					(in->green >= 0.5f && in->blue > 2.0f - 2.0f*in->green)) {
					_hoops_AAHRA (_hoops_APHCR, "Too much saturation, given the lightness (try HSV)");
					return false;
				}

				_hoops_HACHR._hoops_SCPHR = in->red;
				_hoops_HACHR._hoops_HSPHR = in->green;
				_hoops_HACHR._hoops_ISPHR = in->blue;
				_hoops_PAGR->_hoops_PRGRA = M_DIFFUSE;
				HI_HLS_To_RGB (&_hoops_HACHR, &_hoops_PAGR->_hoops_CSHR);
			}
			++in, ++_hoops_PAGR;
		}
		_hoops_RGGA (--count == 0);
	}
	else if ((style[0] == 'h' || style[0] == 'H') &&
			 (style[1] == 'i' || style[1] == 'I') &&
			 (style[2] == 'c' || style[2] == 'C')) {
		do {
			if (in->red == -1.0f && in->green == -1.0f && in->blue == -1.0f) {	// _hoops_GRH _hoops_AGIR _hoops_IH "_hoops_RHPA" _hoops_RARP
				// _hoops_IGPC _hoops_RAAP _hoops_RHPA
				_hoops_PAGR->_hoops_CSHR = *in;
			}
			else {
				_hoops_PACHR			_hoops_HACHR;

				if (!(-1e5f <= in->red && in->red <= 1e5f)) {
					_hoops_AAHRA (_hoops_APHCR, "Hue has unreasonable magnitude");
					return false;
				}

				if (!(0.0f <= in->blue && in->blue <= 1.0f)) {
					_hoops_AAHRA (_hoops_APHCR, "Chromaticity (saturation) is not in the range 0..1");
					return false;
				}

				if (!(0.0f <= in->green && in->green <= 1.0f)) {
					_hoops_AAHRA (_hoops_APHCR, "Intensity (lightness) is not in the range 0..1");
					return false;
				}

				_hoops_HACHR._hoops_SCPHR = in->red;
				_hoops_HACHR._hoops_HSPHR = in->green;
				if (_hoops_HACHR._hoops_HSPHR < 0.5f)
					_hoops_HACHR._hoops_ISPHR = in->blue * 2.0f * _hoops_HACHR._hoops_HSPHR;
				else
					_hoops_HACHR._hoops_ISPHR = in->blue * 2.0f * (1.0f - _hoops_HACHR._hoops_HSPHR);

				_hoops_PAGR->_hoops_PRGRA = M_DIFFUSE;
				HI_HLS_To_RGB (&_hoops_HACHR, &_hoops_PAGR->_hoops_CSHR);
			}
			++in, ++_hoops_PAGR;
		}
		_hoops_RGGA (--count == 0);
	}
	else if ((style[0] == 'h' || style[0] == 'H') &&
			 (style[1] == 's' || style[1] == 'S') &&
			 (style[2] == 'v' || style[2] == 'V')) {
		do {
			if (in->red == -1.0f && in->green == -1.0f && in->blue == -1.0f) {	// _hoops_GRH _hoops_AGIR _hoops_IH "_hoops_RHPA" _hoops_RARP
				// _hoops_IGPC _hoops_RAAP _hoops_RHPA
				_hoops_PAGR->_hoops_CSHR = *in;
			}
			else {
				_hoops_PACHR			_hoops_HACHR;

				if (!(-1e5f <= in->red && in->red <= 1e5f)) {
					_hoops_AAHRA (_hoops_APHCR, "Hue has unreasonable magnitude");
					return false;
				}

				if (!(0.0f <= in->blue && in->blue <= 1.0f)) {
					_hoops_AAHRA (_hoops_APHCR, "'Value' (lightness) is not in the range 0..1");
					return false;
				}

				if (!(0.0f <= in->green && in->green <= in->blue)) {
					_hoops_AAHRA (_hoops_APHCR, "Saturation is not in the range 0..'Value'");
					return false;
				}

				_hoops_HACHR._hoops_SCPHR = in->red;
				_hoops_HACHR._hoops_ISPHR = in->green;
				_hoops_HACHR._hoops_HSPHR = in->blue - 0.5f * in->green;

				_hoops_PAGR->_hoops_PRGRA = M_DIFFUSE;
				HI_HLS_To_RGB (&_hoops_HACHR, &_hoops_PAGR->_hoops_CSHR);
			}
			++in, ++_hoops_PAGR;
		}
		_hoops_RGGA (--count == 0);
	}
	else {
		HE_ERROR2 (HEC_COLOR_MAP, HES_INVALID_COLOR_SPACE,
				   Sprintf_S (null, "Color system '%s' not recognized -", style),
				   "Should be HLS, HIC, HSV, or RGB");

		FREE_ARRAY (_hoops_APHCR->_hoops_HAA, _hoops_APHCR->length, Named_Material);
		return false;
	}

	return true;
#else
	return false;
#endif
}

GLOBAL_FUNCTION void HI_Free_Material_Names (
	Named_Material		*mat,
	int						length)
{
	_hoops_RGGA (length-- <= 0) {
		HI_Free_Diffuse_Channel_List (mat->_hoops_SCA);
		mat->_hoops_SCA = null;
		for (int i=0; i<_hoops_CRGRA; i++)
			_hoops_RGAIR (mat->name[i]);
		for (int i=0; i<_hoops_GAGRA; i++)
			if (mat->texture[i] != null)
				_hoops_HPRH(mat->texture[i]);
		_hoops_RGAIR(mat->_hoops_IRGRA);
		++mat;
	}
}


struct _hoops_PAHRA {
	int				offset;
	_hoops_RHAH		_hoops_APHCR;
};

#ifndef DISABLE_COLOR_MAPS

local void _hoops_HAHRA (
	_hoops_RHAH *				_hoops_SRAIR,
	_hoops_PAHRA *		pt) {
	Named_Material			*in, *_hoops_PAGR;
	int						count;

	in = pt->_hoops_APHCR._hoops_HAA;
	_hoops_PAGR = _hoops_SRAIR->_hoops_HAA + pt->offset;
	count = pt->_hoops_APHCR.length;
	do HI_Copy_Named_Material (in++, _hoops_PAGR++);
	_hoops_RGGA (--count == 0);

	_hoops_PAGR = _hoops_SRAIR->_hoops_HAA;
	count = _hoops_SRAIR->length;
	_hoops_SRAIR->time_stamp = HOOPS_WORLD->_hoops_GPPI;
	_hoops_SRAIR->_hoops_SRHRA = 0;
	do {
		_hoops_SRAIR->_hoops_SRHRA |= (_hoops_PAGR++)->_hoops_PRGRA;
	} _hoops_RGGA (--count == 0);
}

local void _hoops_IAHRA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info) {
	Attribute *				_hoops_ASGPR;
	_hoops_PAHRA *		pt = (_hoops_PAHRA *)info;

	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {
		HI_Not_When_Streamed (_hoops_SRCP, "modify color map");
		return;
	}

	if ((_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR) != null) do {
		if (_hoops_ASGPR->type >= HK_COLOR_MAP) {
			if (_hoops_ASGPR->type == HK_COLOR_MAP) {
				_hoops_RHAH *			_hoops_CSIR = (_hoops_RHAH *)_hoops_ASGPR;

				if (pt->offset + pt->_hoops_APHCR.length > _hoops_CSIR->length) {
					HE_ERROR2 (HEC_COLOR_MAP, HES_INVALID_OFFSET,
							   Sprintf_P (null,
										  "Can't modify color map for '%p' -",
										  _hoops_SRCP),
							   "Size + offset of mod exceeds original length");
					return;
				}

				_hoops_HAHRA ((_hoops_RHAH *)_hoops_ASGPR, pt);

				if (!ANYBIT (_hoops_CSIR->_hoops_CPGPR, _hoops_AHSGA|_hoops_CASIR)) {
					_hoops_CSIR->_hoops_CPGPR |= _hoops_CAHRA;
					HI_Redraw_Attribute (_hoops_RIGC, _hoops_CSIR->owner, HK_COLOR_MAP, _hoops_ASGPR, _hoops_ASGPR);
				}
				_hoops_CSIR->_hoops_CPGPR |= _hoops_CAHRA;

				return;
			}
			break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	HE_ERROR (HEC_COLOR_MAP, HES_NOT_PRESENT,
			  Sprintf_P (null, "'%p' has no Color Map - can't modify", _hoops_SRCP));
}


local void _hoops_SAHRA (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_PAHRA *		pt)
{

	if ((_hoops_RIGC->open_list == null || _hoops_RIGC->open_list->_hoops_GCRIR != _hoops_RCRIR) &&
		!HI_Find_Our_Open (_hoops_RIGC))
		return;

	_hoops_RPPPR();
	_hoops_IAHRA (_hoops_RIGC, _hoops_RIGC->open_list->info.segment._hoops_IGRPR, (void *)pt);
	_hoops_IRRPR();

	HI_Free_Material_Names (pt->_hoops_APHCR._hoops_HAA, pt->_hoops_APHCR.length);
	FREE_ARRAY (pt->_hoops_APHCR._hoops_HAA, pt->_hoops_APHCR.length, Named_Material);
}


local void _hoops_GPHRA (
	int						offset,
	int						count) {

	if (offset < 0)
		HE_ERROR (HEC_COLOR_MAP, HES_INVALID_OFFSET, "Offset specified is negative");
	else if (count < 1)
		HE_ERROR (HEC_COLOR_MAP, HES_INVALID_COUNT, "Count specified is not positive");
}

#endif


HC_INTERFACE void HC_CDECL HC_Modify_Color_Map_By_Value (
	int					offset,
	char const *		style,
	int					count,
	RGB const *			values)
{
	_hoops_PAPPR context("Modify_Color_Map_By_Value");

#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_RGB* values = (HC_RGB*) malloc(sizeof(HC_RGB)*%d);\n", count2));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].red = %f;	 ", count2, values[count2].red));
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].green = %f;	 ", count2, values[count2].green));
			HI_Dump_Code (_hoops_CHCHR (null, "values[%d].blue = %f;\n", count2, values[count2].blue));
		}
		HI_Dump_Code (Sprintf_D (null, "HC_Modify_Color_Map_By_Value (%d, ", offset));
		HI_Dump_Code (Sprintf_SD (null, "%S, %d, values);\n", style, count));
		HI_Dump_Code ("free (values);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	if (offset < 0 || count < 1) {
		_hoops_GPHRA (offset, count);
		return;
	}

	_hoops_PAHRA		pt;
	pt.offset = offset;

	if (HI_Parse_Color_Map_By_Value (context, style, count, values, &pt._hoops_APHCR))
		_hoops_SAHRA (context, &pt);
#endif
}

HC_INTERFACE void HC_CDECL HC_Modify_Color_Map (
	int						offset,
	char const *			_hoops_HSHIR)
{
	_hoops_PAPPR context("Modify_Color_Map");

#ifdef DISABLE_COLOR_MAPS
	_hoops_IRPPR ("Color Maps");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_D (null,"HC_Modify_Color_Map (%d, ",offset));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", _hoops_HSHIR));
	);

	if (offset < 0) {
		_hoops_GPHRA (offset, 1);
		return;
	}

	_hoops_PAHRA		pt;
	pt.offset = offset;

	if (HI_Parse_Color_Map (context, _hoops_HSHIR, &pt._hoops_APHCR))
		_hoops_SAHRA (context, &pt);
#endif
}


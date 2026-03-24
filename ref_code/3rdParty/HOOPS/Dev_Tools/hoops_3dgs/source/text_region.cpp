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
 * $Id: obf_tmp.txt 1.33 2010-11-24 00:48:25 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local const _hoops_IGRCR _hoops_IASGGR[] = {
	{_hoops_PGGRP,		_hoops_GRRCR ("bottom"),						_hoops_RRRCR, 0, false},
	{_hoops_HGGRP,		_hoops_GRRCR ("center"),						_hoops_RRRCR, 0, false},
	{_hoops_IGGRP,			_hoops_GRRCR ("top"),							_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_CASGGR = {
	_hoops_GGAPR (_hoops_IASGGR), _hoops_IASGGR,
};


local const _hoops_IGRCR _hoops_SASGGR[] = {
	{_hoops_ARGRP,		_hoops_GRRCR ("none"),							_hoops_RRRCR, 0, false},
	{_hoops_ARGRP,		_hoops_GRRCR ("off"),							_hoops_RRRCR, 0, false},
	{_hoops_ARGRP,		_hoops_GRRCR ("no"),							_hoops_RRRCR, 0, false},
	{_hoops_ARGRP,		_hoops_GRRCR ("false"),							_hoops_RRRCR, 0, false},

	{_hoops_PRGRP,	_hoops_GRRCR ("spacing"),						_hoops_RRRCR, 0, false},
	{_hoops_PRGRP,	_hoops_GRRCR ("on"),							_hoops_RRRCR, 0, false},
	{_hoops_PRGRP,	_hoops_GRRCR ("yes"),							_hoops_RRRCR, 0, false},
	{_hoops_PRGRP,	_hoops_GRRCR ("true"),							_hoops_RRRCR, 0, false},

//	{_hoops_GPSGGR,		_hoops_CAAPA ("_hoops_IGIR"),							_hoops_RPSGGR, 0, _hoops_RCPP},
};
local const _hoops_HPAGA _hoops_APSGGR = {
	_hoops_GGAPR (_hoops_SASGGR), _hoops_SASGGR,
};


local const _hoops_IGRCR _hoops_PPSGGR[] = {
	{_hoops_ARGRP,		_hoops_GRRCR ("none"),							_hoops_RRRCR, 0, false},
	{_hoops_ARGRP,		_hoops_GRRCR ("off"),							_hoops_RRRCR, 0, false},
	{_hoops_ARGRP,		_hoops_GRRCR ("no"),							_hoops_RRRCR, 0, false},
	{_hoops_ARGRP,		_hoops_GRRCR ("false"),							_hoops_RRRCR, 0, false},

	{_hoops_PRGRP,	_hoops_GRRCR ("spacing"),						_hoops_RRRCR, 0, false},
	{_hoops_PRGRP,	_hoops_GRRCR ("on"),							_hoops_RRRCR, 0, false},
	{_hoops_PRGRP,	_hoops_GRRCR ("yes"),							_hoops_RRRCR, 0, false},
	{_hoops_PRGRP,	_hoops_GRRCR ("true"),							_hoops_RRRCR, 0, false},

//	{_hoops_GPSGGR,		_hoops_CAAPA ("_hoops_IGIR"),							_hoops_RPSGGR, 0, _hoops_RCPP},

//	{-1,						_hoops_CAAPA ("_hoops_IRGGA"),					_hoops_HPSGGR, -1, _hoops_IHPR,
//																			&_hoops_IPSGGR},
//	{-2,						_hoops_CAAPA ("_hoops_IRPHR"),						_hoops_HPSGGR, -1, _hoops_IHPR,
//																			&_hoops_IPSGGR},
};
local const _hoops_HPAGA _hoops_CPSGGR = {
	_hoops_GGAPR (_hoops_PPSGGR), _hoops_PPSGGR,
};


local const _hoops_IGRCR _hoops_SPSGGR[] = {
	{_hoops_RGGRP,		_hoops_GRRCR ("relative coordinates"),			_hoops_RRRCR, 0, true},
	{_hoops_GGGRP,		_hoops_GRRCR ("window space"),					_hoops_RRRCR, 0, true},
	{_hoops_AGGRP,		_hoops_GRRCR ("adjust direction"),				_hoops_RRRCR, 0, true},
	{_hoops_CGGRP,		_hoops_GRRCR ("alignment"),						_hoops_GHAGA, 1, true,
																			&_hoops_CASGGR},
	{_hoops_RRGRP,		_hoops_GRRCR ("fitting"),						_hoops_GHAGA, -1, true,	// -2
																			&_hoops_CPSGGR},
};

GLOBAL_FUNCTION void HI_Set_Text_Region(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HACC *					text,
	int						count,
	Point const *			points,
	int						options,
	int						_hoops_AGGCH)
{
	if (count == 0) {
		if (text->region != null) {
			FREE (text->region, _hoops_AIHIR);
			text->region = null;
		}
	}
	else {
		if (text->region == null)
			ZALLOC (text->region, _hoops_AIHIR);

		text->region->count = count;
		_hoops_AIGA (points, count, Point, text->region->points);
		text->region->options = options;

		text->region->_hoops_IRGRP = text->region->_hoops_CRGRP = _hoops_PRGRP;
		if (BIT (options, _hoops_SGGRP))
			text->region->_hoops_IRGRP = (unsigned char)_hoops_AGGCH;
		if (BIT (options, _hoops_GRGRP))
			text->region->_hoops_CRGRP = (unsigned char)(_hoops_AGGCH >> 8);
	}

	_hoops_SASIR (_hoops_RIGC, text, _hoops_RAGGA|_hoops_RPSIR);
}

HC_INTERFACE void HC_CDECL HC_Set_Text_Region (
	int					count,
	Point const *		points,
	char const *		list)
{
	_hoops_PAPPR context("Set_Text_Region");

	CODE_GENERATION (
		int		count2 = count;
		HI_Dump_Code ("{\n");
		++HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code (Sprintf_D (null, "HC_POINT * points = (HC_POINT*) malloc(sizeof(HC_POINT)*%d);\n", count));
		_hoops_RGGA (count2-- == 0) {
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].x = %f;	 ", count2, points[count2].x));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].y = %f;	 ", count2, points[count2].y));
			HI_Dump_Code (_hoops_CHCHR (null, "points[%d].z = %f;\n", count2, points[count2].z));
		}
		HI_Dump_Code (Sprintf_D (null, "HC_Set_Text_Region (%d, ", count));
		if (list && list[0] != '\0')
			HI_Dump_Code (Sprintf_S (null, "points, %s);\n", list));
		else
			HI_Dump_Code ("points, \"\");\n");
		HI_Dump_Code ("free (points);\n");
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("}\n");
	);

	if (count != 0 && count != 2 && count != 3) {
		HE_ERROR2 (HEC_TEXT, HES_INVALID_COUNT,
			Sprintf_D (null, "Point count of %d is invalid,", count),"only 0, 2, or 3 currently supported");
		return;
	}
	if (count >= 2 && points[1] == points[0] ||
		count >= 3 && (points[2] == points[0] || points[2] == points[1])) {
		HE_ERROR (HEC_TEXT, HES_BAD_POSITION, "Region points may not be identical");
		return;
	}
	if (count >= 3) {
		Vector		_hoops_ISPI = points[1] - points[0];
		Vector		_hoops_CSPI = points[2] - points[0];
		Vector		_hoops_SSPI = _hoops_ISPI._hoops_SAIAR(_hoops_CSPI);

		if (_hoops_SSPI.length() < 1.0e-6) {
			HE_ERROR (HEC_TEXT, HES_BAD_REFERENCE_POINT,
						"Region orientation (third) point may not be collinear with the first rwo points");
			return;
		}
	}

	if (!list)
		list = "";

	_hoops_HIACR (_hoops_IHRGI, _hoops_SPSGGR);

	Option_Value *	option_list;
	if (HI_Parse_Options (context, list, _hoops_CIACR (_hoops_IHRGI), &option_list, _hoops_SIACR)) {
		int				options = 0;
		int				_hoops_AGGCH = 0;
		Option_Value *	option;

		if ((option = option_list) != null) do {
			_hoops_GHGI	mask = option->type->id;

			if (mask == _hoops_RRGRP) {
				if (option->_hoops_GCACR) {
					options |= mask;
					_hoops_AGGCH = _hoops_ARGRP | (_hoops_ARGRP << 8);
				}
				else if (option->_hoops_AIPCR == 0) {
					options |= mask;
					_hoops_AGGCH |= _hoops_PRGRP | (_hoops_PRGRP << 8);
				}
				else {
					Option_Value *		_hoops_AHSAA = option->value.option_list;

					do {
						int				id = _hoops_AHSAA->type->id;

						if (_hoops_AHSAA->type->id == -1) {
							options |= _hoops_SGGRP;
							_hoops_AGGCH &= ~0x00FF;
							if (_hoops_AHSAA->_hoops_GCACR)
								_hoops_AGGCH |= _hoops_ARGRP;
							else if (_hoops_AHSAA->_hoops_AIPCR == 0)
								_hoops_AGGCH |= _hoops_PRGRP;
							else
								_hoops_AGGCH |= _hoops_AHSAA->value.option_list->type->id;
						}
						else if (_hoops_AHSAA->type->id == -2) {
							options |= _hoops_GRGRP;
							_hoops_AGGCH &= ~0xFF00;
							if (_hoops_AHSAA->_hoops_GCACR)
								_hoops_AGGCH |= _hoops_ARGRP << 8;
							else if (_hoops_AHSAA->_hoops_AIPCR == 0)
								_hoops_AGGCH |= _hoops_PRGRP << 8;
							else
								_hoops_AGGCH |= _hoops_AHSAA->value.option_list->type->id << 8;
						}
						else {
							// _hoops_GIPR _hoops_GGR _hoops_CAPRH
							options |= _hoops_SGGRP | _hoops_GRGRP;
							_hoops_AGGCH |= id | (id << 8);
						}
					} while ((_hoops_AHSAA = _hoops_AHSAA->next) != null);
				}
			}
			else if (option->_hoops_GCACR)
				options &= ~mask;
			else if (mask == _hoops_CGGRP)
				options |= option->value.option_list->type->id;
			else
				options |= mask;
		} while ((option = option->next) != null);

		HI_Free_Option_List (context, option_list);

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_GRRPP)) != null) {
			_hoops_HACC *	text = (_hoops_HACC *)target;
			HI_Set_Text_Region(context, text, count, points, options, _hoops_AGGCH);
			_hoops_IRRPR();
		}
	}
}

GLOBAL_FUNCTION char * HI_Show_Text_Region_Options (
	_hoops_AIHIR const *			region,
	char alter *				p) {
	char const *				_hoops_CSHPP = p;

	if (BIT (region->options, _hoops_RGGRP))
		p = HI_Copy_Chars ("relative coordinates,", p);

	if (BIT (region->options, _hoops_GGGRP))
		p = HI_Copy_Chars ("window space,", p);

	if (BIT (region->options, _hoops_AGGRP))
		p = HI_Copy_Chars ("adjust direction,", p);

	if (BIT (region->options, _hoops_HGGRP))
		p = HI_Copy_Chars ("alignment=center,", p);
	if (BIT (region->options, _hoops_IGGRP))
		p = HI_Copy_Chars ("alignment=top,", p);

	if (ANYBIT (region->options, _hoops_RRGRP)) {
		p = HI_Copy_Chars ("fitting=", p);
		if (ALLBITS (region->options, _hoops_RRGRP) &&
			region->_hoops_IRGRP == region->_hoops_CRGRP) {
			switch (region->_hoops_IRGRP) {
				case _hoops_ARGRP:		p = HI_Copy_Chars ("none,", p);			break;
				case _hoops_PRGRP:	p = HI_Copy_Chars ("spacing,", p);		break;
				case _hoops_HRGRP:		p = HI_Copy_Chars ("size,", p);			break;
			}
		}
		else {
			ASSERT (0);		// _hoops_PAHA'_hoops_RA _hoops_HGCR _hoops_RGR _hoops_AGIR _hoops_CCGR _hoops_SR _hoops_GHSGGR _hoops_RH _hoops_CIIA _hoops_GRPRA
			int		which = region->options & _hoops_RRGRP;

			if (_hoops_RIII (which) != which)
				p = HI_Copy_Chars ("(", p);

			if (BIT (which, _hoops_SGGRP)) {
				p = HI_Copy_Chars ("horizontal=", p);
				switch (region->_hoops_IRGRP) {
					case _hoops_ARGRP:		p = HI_Copy_Chars ("none,", p);			break;
					case _hoops_PRGRP:	p = HI_Copy_Chars ("spacing,", p);		break;
					case _hoops_HRGRP:		p = HI_Copy_Chars ("size,", p);			break;
				}
			}
			if (BIT (which, _hoops_GRGRP)) {
				p = HI_Copy_Chars ("vertical=", p);
				switch (region->_hoops_IRGRP) {
					case _hoops_ARGRP:		p = HI_Copy_Chars ("none,", p);			break;
					case _hoops_PRGRP:	p = HI_Copy_Chars ("spacing,", p);		break;
					case _hoops_HRGRP:		p = HI_Copy_Chars ("size,", p);			break;
				}
			}

			if (_hoops_RIII (which) != which) {
				--p;
				p = HI_Copy_Chars ("),", p);
			}
		}
	}

	if (p != _hoops_CSHPP)
		--p;		/* _hoops_HASIR _hoops_CGHI _hoops_RRCIR _hoops_RPP _hoops_GII _hoops_AAP _hoops_RAGA */
	*p = '\0';

	return p;
}

HC_INTERFACE void HC_CDECL HC_Show_Text_Region (
	int alter *		count,
	Point alter *	points,
	char alter *	options)
{
	_hoops_PAPPR context("Show_Text_Region");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Region () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RRRPP)) != null) {
		_hoops_HACC const *				text = (_hoops_HACC const *)target;

		if (text->region == null) {
			if (count != null)
				*count = 0;
			if (options != null)
				HI_Return_Chars (options, -1, "", 0);
		}
		else {
			_hoops_AIHIR const *		region = text->region;

			if (count != null)
				*count = region->count;
			if (points != null)
				_hoops_AIGA (region->points, text->region->count, Point, points);

			if (options != null) {
				char				buf[256];
				char *				p = HI_Show_Text_Region_Options (region, buf);

				HI_Return_Chars (options, -1, buf, p - buf);
			}
		}

		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_Show_Text_Region_Count (
	int alter *		count)
{
	_hoops_PAPPR context("Show_Text_Region_Count");

#ifdef DISABLE_GEOMETRY_SHOW
	_hoops_IRPPR ("Geometry Show");
#else

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Region () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RRRPP)) != null) {

		_hoops_HACC *	text = (_hoops_HACC *)target;

		if (text->region == null)
			*count = 0;
		else
			*count = text->region->count;
		_hoops_IRRPR();
	}
#endif
}



HC_INTERFACE void HC_CDECL HC_UnSet_Text_Region (void)
{
	_hoops_PAPPR context("UnSet_Text_Region");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Text_Region ();");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GRRPP)) != null) {

		_hoops_HACC *	text = (_hoops_HACC *)target;

		if (text->region != null) {
			FREE (text->region, _hoops_AIHIR);
			text->region = null;
			_hoops_SASIR (context, text, _hoops_RAGGA|_hoops_RPSIR);
		}
		else {
			HE_ERROR (HEC_TEXT, HES_CANNOT_UNSET_ATTRIBUTE, "Can't unset Text_Region, none set");
		}
		_hoops_IRRPR();
	}
}



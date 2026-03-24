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
 * $Id: obf_tmp.txt 1.68 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


local Attribute *_hoops_ACCAGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR)
{
	Window const *			_hoops_AISGS = (Window const *)_hoops_CPACR;
	Window alter *			_hoops_IHPIP = (Window alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_AISGS != null &&
		_hoops_AISGS->_hoops_RCHS.left == _hoops_IHPIP->_hoops_RCHS.left &&
		_hoops_AISGS->_hoops_RCHS.bottom == _hoops_IHPIP->_hoops_RCHS.bottom &&
		_hoops_AISGS->_hoops_RCHS.right == _hoops_IHPIP->_hoops_RCHS.right &&
		_hoops_AISGS->_hoops_RCHS.top == _hoops_IHPIP->_hoops_RCHS.top)
		return null;

	return _hoops_IHPIP;
}


local bool _hoops_PCCAGR (
	Window *	window) {

	if (window->_hoops_RCHS.left	  < -1.0f && window->_hoops_RCHS.left   > -1.0001f) window->_hoops_RCHS.left   = -1.0f;
	if (window->_hoops_RCHS.right  > 1.0f  && window->_hoops_RCHS.right  <  1.0001f) window->_hoops_RCHS.right  = 1.0f;
	if (window->_hoops_RCHS.bottom < -1.0f && window->_hoops_RCHS.bottom > -1.0001f) window->_hoops_RCHS.bottom = -1.0f;
	if (window->_hoops_RCHS.top	  > 1.0f  && window->_hoops_RCHS.top	   <  1.0001f) window->_hoops_RCHS.top    = 1.0f;

	if (window->_hoops_RCHS.left >= window->_hoops_RCHS.right || window->_hoops_RCHS.bottom >= window->_hoops_RCHS.top) {
		HE_ERROR2 (HEC_WINDOW, HES_OUT_OF_RANGE_NUMBER,
				   "Unreasonable screen window -",
				   window->_hoops_RCHS.left >= window->_hoops_RCHS.right ?
					 "the 'left' position is greater than or equal to the 'right'" :
					 "the 'bottom' position is greater than or equal to the 'top'");
		return false;
	}

	if (window->_hoops_RCHS.left >= 1.0f || window->_hoops_RCHS.right <= -1.0f ||
		window->_hoops_RCHS.bottom >= 1.0f || window->_hoops_RCHS.top <= -1.0f)
		_hoops_PHPGR (HEC_WINDOW, HES_OUT_OF_RANGE_NUMBER,
					 "Entire window is outside -1 to +1 range -",
					 "No part of the window will be visible");

	return true;
}

GLOBAL_FUNCTION bool HI_Set_Window (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	Window *				window)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_WINDOW, _hoops_ACCAGR, window);
}



HC_INTERFACE void HC_CDECL HC_Set_Window (
	double			left,
	double			right,
	double			bottom,
	double			top)
{
	_hoops_PAPPR context("Set_Window");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_FF (null, "HC_Set_Window (%F, %F, ", left, right));
		HI_Dump_Code (Sprintf_FF (null, "%F, %F);\n", bottom, top));
	);

	bool		used = false;
	Window *	window;
	ZALLOC (window, Window);
	window->_hoops_RCHS.left = (float)left;
	window->_hoops_RCHS.bottom = (float)bottom;
	window->_hoops_RCHS.right = (float)right;
	window->_hoops_RCHS.top = (float)top;

	if (_hoops_PCCAGR (window)) {
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_PHRPP)) != null) {
			used = HI_Set_Window(context, target, window);
			_hoops_IRRPR();
		}
	}

	if (!used)
		FREE(window, Window);
}


HC_INTERFACE void HC_CDECL HC_UnSet_Window (void)
{
	_hoops_PAPPR context("UnSet_Window");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Window ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_PHRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute(context, target, HK_WINDOW);
		_hoops_IRRPR();
	}
}



HC_INTERFACE void HC_CDECL HC_Show_Window (
	float *		left,
	float *		right,
	float *		bottom,
	float *		top)
{
	_hoops_PAPPR context("Show_Window");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Window () */\n");
	);


	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RGAPP)) != null) {
		Window *	window;
		if ((window = (Window *)HI_Find_Attribute (context, target, HK_WINDOW)) != null) {
			*left = window->_hoops_RCHS.left;
			*right = window->_hoops_RCHS.right;
			*bottom = window->_hoops_RCHS.bottom;
			*top = window->_hoops_RCHS.top;

			_hoops_HPRH (window);
		}
		_hoops_IRRPR();
	}
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Window (
	int				count,
	Key const *		keys,
	float *			left,
	float *			right,
	float *			bottom,
	float *			top)
{
	_hoops_PAPPR context("PShow_Net_Window");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Window () */\n");
	);

	Window *	window;
	if ((window = (Window *) HI_Find_Attribute_And_Lock(context, _hoops_RGAPP, _hoops_HRPCR, count, keys)) != null) {
		*left = window->_hoops_RCHS.left;
		*right = window->_hoops_RCHS.right;
		*bottom = window->_hoops_RCHS.bottom;
		*top = window->_hoops_RCHS.top;

		_hoops_HPRH (window);
		_hoops_IRRPR();
	}
	else
		*left = *right = *bottom = *top = 0;
#endif
}
#endif




local Attribute *_hoops_HCCAGR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_CPACR,
	Attribute alter *		_hoops_SPACR)
{
	_hoops_GSAIR const *	_hoops_ICCAGR = (_hoops_GSAIR const *)_hoops_CPACR;
	_hoops_GSAIR alter *	_hoops_CCCAGR = (_hoops_GSAIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_ICCAGR != null &&
		_hoops_ICCAGR->flags == _hoops_CCCAGR->flags)
		return null;

	return _hoops_CCCAGR;
}

local const _hoops_IGRCR _hoops_SCCAGR[] = {
	{_hoops_GIARP,		_hoops_GRRCR ("off"),		_hoops_RRRCR,	0, false},
	{_hoops_AIARP,		_hoops_GRRCR ("on"),		_hoops_RRRCR,	0, false},
	{_hoops_PIARP,	_hoops_GRRCR ("single"),	_hoops_RRRCR,	0, true},
	{_hoops_HIARP,		_hoops_GRRCR ("inset"),		_hoops_RRRCR,	0, true},
	{_hoops_CIARP,_hoops_GRRCR ("decorative"),_hoops_RRRCR,	0, false},
};


local bool _hoops_GSCAGR (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			spec,
	_hoops_RIARP *	flags)
{

	_hoops_HIACR (_hoops_SPRGI, _hoops_SCCAGR);

	*flags = 0;

	Option_Value *	option_list;
	Option_Value *	option;

	if (HI_Parse_Options (_hoops_RIGC, spec, _hoops_CIACR (_hoops_SPRGI), &option_list, _hoops_SIACR)) {
		bool	_hoops_RSCAGR = false;
		bool	_hoops_ASCAGR = false;
		bool	_hoops_PSCAGR = false;

		if ((option = option_list) != null) do {
			switch (option->type->id) {
				case _hoops_GIARP: {
					_hoops_RSCAGR = true;
				}	break;

				case _hoops_AIARP: {
					*flags |= _hoops_AIARP;
				}	break;

				case _hoops_PIARP: {
					if (option->_hoops_GCACR)
						*flags &= ~_hoops_PIARP;
					else
						*flags |= _hoops_PIARP|_hoops_AIARP;
				}	break;

				case _hoops_HIARP: {
					if (option->_hoops_GCACR) {
						_hoops_ASCAGR = true;
						*flags &= ~_hoops_HIARP;
					}
					else {
						_hoops_PSCAGR = true;
						*flags |= _hoops_HIARP|_hoops_AIARP;
					}
				}	break;

				case _hoops_CIARP: {
					*flags |= _hoops_CIARP;
				}	break;

				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized window frame option type");
					return false;
				}
			}
		} while ((option = option->next) != null);

		if (_hoops_RSCAGR)
			if (_hoops_ASCAGR)
				*flags = _hoops_GIARP;
			else
			if (_hoops_PSCAGR)
				*flags = _hoops_GIARP|_hoops_HIARP;
			else
				*flags = _hoops_GIARP|_hoops_IIARP;

		if (BIT(*flags, _hoops_GIARP))
			*flags &= ~_hoops_CIARP;

		HI_Free_Option_List (_hoops_RIGC, option_list);
	}

	return true;
}


GLOBAL_FUNCTION bool HI_Set_Window_Frame (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_GSAIR *			_hoops_IGGCH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_WINDOW_FRAME, _hoops_HCCAGR, _hoops_IGGCH);
}


HC_INTERFACE void HC_CDECL HC_Set_Window_Frame (
	char const *		spec)
{
	_hoops_PAPPR context("Set_Window_Frame");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Window_Frame (%S);\n", spec));
	);

	bool			used = false;
	_hoops_GSAIR *	_hoops_IGGCH;
	ZALLOC (_hoops_IGGCH, _hoops_GSAIR);
	_hoops_IGGCH->flags = _hoops_GIARP;

	if (_hoops_GSCAGR (context, spec, &_hoops_IGGCH->flags)) {
		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_HHRPP)) != null) {
			used = HI_Set_Window_Frame(context, target, _hoops_IGGCH);
			_hoops_IRRPR();
		}
	}

	if (!used)
		FREE (_hoops_IGGCH, _hoops_GSAIR);
}


HC_INTERFACE void HC_CDECL HC_UnSet_Window_Frame (void)
{
	_hoops_PAPPR context("UnSet_Window_Frame");

	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Window_Frame ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_HHRPP|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute (context, target, HK_WINDOW_FRAME);
		_hoops_IRRPR();
	}
}


local void _hoops_HSCAGR(
	char					*spec,
	int						_hoops_CSACR,
	_hoops_GSAIR			*_hoops_IGGCH) {

	if (BIT(_hoops_IGGCH->flags, _hoops_PIARP))

		if (BIT(_hoops_IGGCH->flags, _hoops_CIARP))
			if (BIT(_hoops_IGGCH->flags, _hoops_HIARP))
				HI_Return_Chars (spec, _hoops_CSACR, "single, inset, decorative", 25);
			else
				HI_Return_Chars (spec, _hoops_CSACR, "single, decorative", 18);
		else
			if (BIT(_hoops_IGGCH->flags, _hoops_HIARP))
				HI_Return_Chars (spec, _hoops_CSACR, "single, inset", 13);
			else
				HI_Return_Chars (spec, _hoops_CSACR, "single", 6);
	else
	if (BIT(_hoops_IGGCH->flags, _hoops_AIARP))

		if (BIT(_hoops_IGGCH->flags, _hoops_CIARP))
			if (BIT(_hoops_IGGCH->flags, _hoops_HIARP))
				HI_Return_Chars (spec, _hoops_CSACR, "on, inset, decorative", 21);
			else
				HI_Return_Chars (spec, _hoops_CSACR, "on, decorative", 14);
		else
			if (BIT(_hoops_IGGCH->flags, _hoops_HIARP))
				HI_Return_Chars (spec, _hoops_CSACR, "on, inset", 9);
			else
				HI_Return_Chars (spec, _hoops_CSACR, "on", 2);
	else
		if (BIT(_hoops_IGGCH->flags, _hoops_IIARP))
			HI_Return_Chars (spec, _hoops_CSACR, "off", 3);
		else
		if (BIT(_hoops_IGGCH->flags, _hoops_HIARP))
			HI_Return_Chars (spec, _hoops_CSACR, "off, inset", 10);
		else
			HI_Return_Chars (spec, _hoops_CSACR, "off, no inset", 13);
}


HC_INTERFACE void HC_CDECL HC_Show_Window_Frame (
	char *			spec)
{
	_hoops_PAPPR context("Show_Window_Frame");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Window_Frame () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_AGAPP)) != null) {
		_hoops_GSAIR *	_hoops_IGGCH;
		if ((_hoops_IGGCH = (_hoops_GSAIR *)HI_Find_Attribute (context, target, HK_WINDOW_FRAME)) != null) {
			_hoops_HSCAGR(spec, -1, _hoops_IGGCH);
			_hoops_HPRH (_hoops_IGGCH);
		}
		_hoops_IRRPR();
	}
#endif
}



#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Window_Frame (
	int					count,
	Key const *			keys,
	char *				spec)
{
	_hoops_PAPPR context("PShow_Net_Window_Frame");

#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Window_Frame () */\n");
	);

	_hoops_GSAIR *	_hoops_IGGCH;
	if ((_hoops_IGGCH = (_hoops_GSAIR *) HI_Find_Attribute_And_Lock(context, _hoops_AGAPP, _hoops_HRPCR, count, keys)) != null) {
		_hoops_HSCAGR(spec, -1, _hoops_IGGCH);
		_hoops_HPRH (_hoops_IGGCH);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(spec, -1, "", 0);

#endif
}
#endif




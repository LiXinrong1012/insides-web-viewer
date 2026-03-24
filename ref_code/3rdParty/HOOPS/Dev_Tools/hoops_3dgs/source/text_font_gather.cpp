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
 * $Id: obf_tmp.txt 1.156 2010-10-06 19:16:13 jason Exp $
 */


#include "hoops.h"
#include "driver.h"
#include "database.h"
#include "patterns.h"
#include "please.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



local const _hoops_IGRCR _hoops_HPIGGR[] = {
	{_hoops_IRRSC,				_hoops_GRRCR ("exists"),			_hoops_RRRCR,	0, false},
	{_hoops_RPRSC,				_hoops_GRRCR ("defined"),			_hoops_RRRCR,	0, false},
	{_hoops_CRRSC,					_hoops_GRRCR ("sizes"),				_hoops_RRRCR,	0, false},
	{_hoops_SRRSC,			_hoops_GRRCR ("points to sru"),		_hoops_RRRCR,	0, false},
	{_hoops_GARSC,			_hoops_GRRCR ("proportional"),		_hoops_RRRCR,	0, false},
	{_hoops_RARSC,				_hoops_GRRCR ("scaleable"),			_hoops_RRRCR,	0, false},
	{_hoops_RARSC,				_hoops_GRRCR ("scalable"),			_hoops_RRRCR,	0, false},
	{_hoops_AARSC,			_hoops_GRRCR ("max character"),		_hoops_RRRCR,	0, false},
	{_hoops_PARSC,			_hoops_GRRCR ("generic name"),		_hoops_RRRCR,	0, false},
	{_hoops_HARSC,		_hoops_GRRCR ("character widths"),	_hoops_SPPCR,	1, false},
	{_hoops_CARSC,				_hoops_GRRCR ("rotatable"),			_hoops_RRRCR,	0, false},
	{_hoops_SARSC,		_hoops_GRRCR ("width scaleable"),	_hoops_RRRCR,	0, false},
	{_hoops_GPRSC,				_hoops_GRRCR ("slantable"),			_hoops_RRRCR,	0, false},
	{_hoops_APRSC,				_hoops_GRRCR ("encoding"),			_hoops_RRRCR,	0, false},
	{_hoops_HPRSC,			_hoops_GRRCR ("outlineable"),		_hoops_RRRCR,	0, false},

	{_hoops_IRRSC,				_hoops_GRRCR ("exist"),				_hoops_RRRCR,	0, false},
	{_hoops_CRRSC,					_hoops_GRRCR ("size"),				_hoops_RRRCR,	0, false},
	{_hoops_HARSC,		_hoops_GRRCR ("character width"),	_hoops_SPPCR,	1, false},
};


local _hoops_SRHSR		system_default = _hoops_GRRCR("system default");
local _hoops_SRHSR		sans_serif = _hoops_GRRCR ("sans serif");
local _hoops_SRHSR		typewriter = _hoops_GRRCR ("typewriter");
local _hoops_SRHSR		roman = _hoops_GRRCR ("roman");
local _hoops_SRHSR		stroked = _hoops_GRRCR ("stroked");

HC_INTERFACE void HC_CDECL HC_Show_Font_Info (
	char const *			segname,
	char const *			font,
	char const *			item,
	char *					data) 
{
	_hoops_PAPPR context("Show_Font_Info");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Font_Info () */\n");
	);

	_hoops_HIACR (_hoops_RIRGI, _hoops_HPIGGR);

	Option_Value *	option_list;

	if (!HI_Parse_Options (context, item, _hoops_CIACR (_hoops_RIRGI), &option_list, _hoops_SIACR)) 
		return;

	if (option_list->next != null) {
		HE_ERROR (HEC_TEXT, HES_ONE_INFO_ITEM_ONLY, "Only one info item at a time, please");
		HI_Free_Option_List (context, option_list);
		return;
	}

	_hoops_PGHGH	_hoops_GCHIH;
	ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

	_hoops_GCHIH.item = (int)option_list->type->id;
	if (_hoops_GCHIH.item == _hoops_HARSC) {
		_hoops_GCHIH.height = option_list->value._hoops_PIPCR[0];
		if (_hoops_GCHIH.height <= 0.0f) {
			HE_ERROR (HEC_TEXT, HES_INVALID_SIZE, Sprintf_F (null, "'%f' is an unreasonable character size", _hoops_GCHIH.height));
			HI_Free_Option_List (context, option_list);
			return;
		}
	}

	HI_Free_Option_List (context, option_list);
	HI_Canonize_Chars (font, &_hoops_GCHIH.specified);

	_hoops_CSPPR();
	_hoops_GGAGR *	_hoops_GHRI;
	if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, segname, &_hoops_GCHIH.context)) != null) {

		if (_hoops_RAHSR (_hoops_GCHIH.specified, system_default))
			_hoops_GCHIH._hoops_SSSGP = GFN_SYSTEM_DEFAULT;
		else if (_hoops_RAHSR (_hoops_GCHIH.specified, sans_serif))
			_hoops_GCHIH._hoops_SSSGP = GFN_SANS_SERIF;
		else if (_hoops_RAHSR (_hoops_GCHIH.specified, typewriter))
			_hoops_GCHIH._hoops_SSSGP = GFN_TYPEWRITER;
		else if (_hoops_RAHSR (_hoops_GCHIH.specified, roman))
			_hoops_GCHIH._hoops_SSSGP = GFN_ROMAN;
		else if (_hoops_RAHSR (_hoops_GCHIH.specified, stroked))
			_hoops_GCHIH._hoops_SSSGP = GFN_STROKED;
		else
			_hoops_GCHIH._hoops_SSSGP = GFN_SPECIFIED;

		_hoops_GCHIH._hoops_SPRSC = data;
		_hoops_GCHIH._hoops_GHRSC = -1;

		_hoops_GCHIH.encoding = HOOPS_WORLD->encoding;

		if (!_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH))
			HI_Return_Chars (data, -1, "", 0);
	}
	_hoops_IRRPR();

	_hoops_RGAIR (_hoops_GCHIH.specified);
}



HC_INTERFACE void HC_CDECL HC_Show_Font_Info_By_Path (
	int						count,
	Key const *				keys,
	char const *			font,
	char const *			item,
	char *					data) 
{
	_hoops_PAPPR context("Show_Font_Info_By_Path");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Font_Info_By_Path () */\n");
	);

	_hoops_HIACR (_hoops_RIRGI, _hoops_HPIGGR);

	Option_Value *	option_list;
	if (!HI_Parse_Options (context, item, _hoops_CIACR (_hoops_RIRGI), &option_list, _hoops_SIACR)) 
		return;

	if (option_list->next != null) {
		HE_ERROR (HEC_TEXT, HES_ONE_INFO_ITEM_ONLY, "Only one info item at a time, please");
		HI_Free_Option_List (context, option_list);
		return;
	}

	_hoops_PGHGH	_hoops_GCHIH;
	ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

	_hoops_GCHIH.item = (int)option_list->type->id;

	if (_hoops_GCHIH.item == _hoops_HARSC) {
		_hoops_GCHIH.height = option_list->value._hoops_PIPCR[0];
		if (_hoops_GCHIH.height <= 0.0f) {
			HE_ERROR (HEC_TEXT, HES_INVALID_SIZE,Sprintf_F (null, "'%f' is an unreasonable character size", _hoops_GCHIH.height));
			HI_Free_Option_List (context, option_list);
			return;
		}
	}

	HI_Free_Option_List (context, option_list);

	HI_Canonize_Chars (font, &_hoops_GCHIH.specified);

	_hoops_GCHIH.encoding = HOOPS_WORLD->encoding;

	_hoops_CRCP const **		_hoops_SISAA;
	int						_hoops_CISAA;
	int						allocated;

	_hoops_CSPPR();
	if ((_hoops_CISAA = allocated = HI_Convert_Keys_To_Path (context, count, keys, _hoops_SISAA)) == 0) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");
	}
	else {

		_hoops_GGAGR *	_hoops_GHRI;
		if ((_hoops_GHRI = HI_Force_Find_Path_Actor (context, _hoops_CISAA, _hoops_SISAA, &_hoops_GCHIH.context)) != null) {

			if (_hoops_SISAA[_hoops_CISAA-1]->type == _hoops_AGCP) {
				_hoops_GCHIH.encoding = _hoops_GCHIH._hoops_PCHIH->encoding;
				--_hoops_CISAA;
			}

			_hoops_GCHIH.context = null;
			_hoops_GCHIH._hoops_CISAA = _hoops_CISAA;
			_hoops_GCHIH.path = _hoops_SISAA;

			if (_hoops_RAHSR (_hoops_GCHIH.specified, system_default))
				_hoops_GCHIH._hoops_SSSGP = GFN_SYSTEM_DEFAULT;
			else if (_hoops_RAHSR (_hoops_GCHIH.specified, sans_serif))
				_hoops_GCHIH._hoops_SSSGP = GFN_SANS_SERIF;
			else if (_hoops_RAHSR (_hoops_GCHIH.specified, typewriter))
				_hoops_GCHIH._hoops_SSSGP = GFN_TYPEWRITER;
			else if (_hoops_RAHSR (_hoops_GCHIH.specified, roman))
				_hoops_GCHIH._hoops_SSSGP = GFN_ROMAN;
			else if (_hoops_RAHSR (_hoops_GCHIH.specified, stroked))
				_hoops_GCHIH._hoops_SSSGP = GFN_STROKED;
			else
				_hoops_GCHIH._hoops_SSSGP = GFN_SPECIFIED;

			_hoops_GCHIH._hoops_SPRSC = data;
			_hoops_GCHIH._hoops_GHRSC = -1;

			if (!_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH))
				HI_Return_Chars (data, -1, "", 0);
		}
	}
	_hoops_IRRPR();

	if (_hoops_CISAA > 0)
		FREE_ARRAY (_hoops_SISAA, allocated, _hoops_CRCP *);

	_hoops_RGAIR (_hoops_GCHIH.specified);
}




///////////////////////////////////////////////////////////////////////////////////////////////////

HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline (
	char const *			segname,
	char const *			string,
	int *					count,
	Point *					points,
	int *					_hoops_PAASR,
	int *					list) 
{
	_hoops_PAPPR context("Compute_Text_Outline");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Outline () */\n");
	);

	_hoops_PGHGH	_hoops_GCHIH;
	ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

	_hoops_CSPPR();
	_hoops_GGAGR *	_hoops_GHRI;
	if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, segname, &_hoops_GCHIH.context)) != null) {

		HI_Convert_Char_To_KName (string, &_hoops_GCHIH.text, HOOPS_WORLD->encoding);
		_hoops_GCHIH.encoding = HOOPS_WORLD->encoding;

		_hoops_GCHIH.item = _hoops_PPRSC;
		_hoops_GCHIH.count = 0;
		_hoops_GCHIH.points = points;
		_hoops_GCHIH.face_list_length = 0;
		_hoops_GCHIH.face_list = list;

		_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH);

		*count = _hoops_GCHIH.count;
		*_hoops_PAASR = _hoops_GCHIH.face_list_length;
		_hoops_PRPIR (_hoops_GCHIH.text);
	}
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_Size (
	char const *			segname,
	char const *			string,
	int *					count,
	int *					_hoops_PAASR) 
{
	_hoops_PAPPR context("Compute_Text_Outline_Size");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Outline_Size () */\n");
	);

	_hoops_PGHGH	_hoops_GCHIH;
	ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

	_hoops_CSPPR();
	_hoops_GGAGR *	_hoops_GHRI;
	if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, segname, &_hoops_GCHIH.context)) != null) {

		HI_Convert_Char_To_KName (string, &_hoops_GCHIH.text, HOOPS_WORLD->encoding);
		_hoops_GCHIH.encoding = HOOPS_WORLD->encoding;

		_hoops_GCHIH.item = _hoops_PPRSC;
		_hoops_GCHIH.count = 0;
		_hoops_GCHIH.face_list_length = 0;
		/* _hoops_AGCR "_hoops_IPIGGR" _hoops_GCAPR _hoops_RH _hoops_SIHC _hoops_CPIGGR _hoops_IS _hoops_HGCR _hoops_RGAR _hoops_RH _hoops_PGRR */
		_hoops_GCHIH.points = null;
		_hoops_GCHIH.face_list = null;

		_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH);

		*count = _hoops_GCHIH.count;
		*_hoops_PAASR = _hoops_GCHIH.face_list_length;

		_hoops_PRPIR (_hoops_GCHIH.text);
	}
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_With_En (
	char const *			segname,
	char const *			encoding,
	char const *			string,
	int *					count,
	Point *					points,
	int *					_hoops_PAASR,
	int *					list) 
{
	_hoops_PAPPR context("Compute_Text_Outline_With_Encoding");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Outline_With_En () */\n");
	);

	_hoops_PGHGH	_hoops_GCHIH;
	ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

	_hoops_CSPPR();
	_hoops_GGAGR *	_hoops_GHRI;
	if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, segname, &_hoops_GCHIH.context)) != null) {

		_hoops_IHGRP	_hoops_SPIGGR = HI_Decipher_Encoding (context, encoding);
		HI_Convert_Char_To_KName (string, &_hoops_GCHIH.text, _hoops_SPIGGR);
		_hoops_GCHIH.encoding = _hoops_SPIGGR;

		_hoops_GCHIH.item = _hoops_PPRSC;
		_hoops_GCHIH.count = 0;
		_hoops_GCHIH.points = points;
		_hoops_GCHIH.face_list_length = 0;
		_hoops_GCHIH.face_list = list;

		_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH);

		*count = _hoops_GCHIH.count;
		*_hoops_PAASR = _hoops_GCHIH.face_list_length;

		_hoops_PRPIR (_hoops_GCHIH.text);
	}
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_Size_Wi (
	char const *			segname,
	char const *			encoding,
	char const *			string,
	int *					count,
	int *					_hoops_PAASR) 
{
	_hoops_PAPPR context("Compute_Text_Outline_Size_With_Encoding");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Outline_Size_Wi () */\n");
	);

	_hoops_PGHGH		_hoops_GCHIH;
	ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

	_hoops_CSPPR();
	_hoops_GGAGR *	_hoops_GHRI;
	if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, segname, &_hoops_GCHIH.context)) != null) {

		_hoops_IHGRP	_hoops_SPIGGR = HI_Decipher_Encoding (context, encoding);
		HI_Convert_Char_To_KName (string, &_hoops_GCHIH.text, _hoops_SPIGGR);
		_hoops_GCHIH.encoding = _hoops_SPIGGR;

		_hoops_GCHIH.item = _hoops_PPRSC;
		_hoops_GCHIH.count = 0;
		_hoops_GCHIH.face_list_length = 0;
		/* _hoops_AGCR "_hoops_IPIGGR" _hoops_GCAPR _hoops_RH _hoops_SIHC _hoops_CPIGGR _hoops_IS _hoops_HGCR _hoops_RGAR _hoops_RH _hoops_PGRR */
		_hoops_GCHIH.points = null;
		_hoops_GCHIH.face_list = null;

		_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH);

		*count = _hoops_GCHIH.count;
		*_hoops_PAASR = _hoops_GCHIH.face_list_length;

		_hoops_PRPIR (_hoops_GCHIH.text);
	}
	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_By_Key (
	Key						key,
	int *					count,
	Point *					points,
	int *					_hoops_PAASR,
	int *					list) 
{
	_hoops_PAPPR context("Compute_Text_Outline_By_Key");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Outline_By_Key () */\n");
	);

	_hoops_CSPPR();
	_hoops_HACC *	_hoops_SRPGGR = (_hoops_HACC *)_hoops_RCSSR (context, key);

	if (_hoops_SRPGGR == null || _hoops_SRPGGR->type != _hoops_AGCP || BIT(_hoops_SRPGGR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_KEY, "Provided key does not refer to valid text");
	}
	else {

		_hoops_PGHGH	_hoops_GCHIH;
		ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

		Key	_hoops_RCGGGR = _hoops_AIRIR(_hoops_SRPGGR->owner);

		_hoops_GGAGR *	_hoops_GHRI;
		if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, _hoops_GRSPR (null, "%k", &_hoops_RCGGGR), &_hoops_GCHIH.context)) != null) {

			_hoops_GCHIH.text.length = _hoops_SRPGGR->count;
			_hoops_GCHIH.text._hoops_IPPPP = _hoops_SRPGGR->karacters;
			_hoops_GCHIH.encoding = _hoops_SRPGGR->encoding;

			_hoops_GCHIH.item = _hoops_PPRSC;
			_hoops_GCHIH.count = 0;
			_hoops_GCHIH.points = points;
			_hoops_GCHIH.face_list_length = 0;
			_hoops_GCHIH.face_list = list;

			_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH);

			*count = _hoops_GCHIH.count;
			*_hoops_PAASR = _hoops_GCHIH.face_list_length;
		}
	}
	_hoops_IRRPR();
#endif
}



HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_Size_By (
	Key					key,
	int *				count,
	int *				_hoops_PAASR) 
{
	_hoops_PAPPR context("Compute_Text_Outline_Size_By_Key");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Outline_Size_By () */\n");
	);

	_hoops_CSPPR();
	_hoops_HACC *	_hoops_SRPGGR = (_hoops_HACC *)_hoops_RCSSR (context, key);
	if (_hoops_SRPGGR == null || _hoops_SRPGGR->type != _hoops_AGCP || BIT(_hoops_SRPGGR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_KEY, "Provided key does not refer to valid text");
	}
	else {

		_hoops_PGHGH	_hoops_GCHIH;
		ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

		Key	_hoops_RCGGGR = _hoops_AIRIR(_hoops_SRPGGR->owner);

		_hoops_GGAGR *	_hoops_GHRI;
		if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, _hoops_GRSPR (null, "%k", &_hoops_RCGGGR), &_hoops_GCHIH.context)) != null) {

			_hoops_GCHIH.text.length = _hoops_SRPGGR->count;
			_hoops_GCHIH.text._hoops_IPPPP = _hoops_SRPGGR->karacters;
			_hoops_GCHIH.encoding = _hoops_SRPGGR->encoding;

			_hoops_GCHIH.item = _hoops_PPRSC;
			_hoops_GCHIH.count = 0;
			_hoops_GCHIH.face_list_length = 0;
			/* _hoops_AGCR "_hoops_IPIGGR" _hoops_GCAPR _hoops_RH _hoops_SIHC _hoops_CPIGGR _hoops_IS _hoops_HGCR _hoops_RGAR _hoops_RH _hoops_PGRR */
			_hoops_GCHIH.points = null;
			_hoops_GCHIH.face_list = null;

			_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH);

			*count = _hoops_GCHIH.count;
			*_hoops_PAASR = _hoops_GCHIH.face_list_length;
		}
	}
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_By_Path (
	int						count,
	Key const *				keys,
	char const *			string,
	int *					point_count,
	Point *					points,
	int *					_hoops_PAASR,
	int *					list) 
{
	_hoops_PAPPR context("Compute_Text_Outline_By_Path");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Outline_By_Path () */\n");
	);

	_hoops_CRCP const **		_hoops_SISAA;
	int						_hoops_CISAA;
	int						allocated;

	_hoops_CSPPR();

	if ((_hoops_CISAA = allocated = HI_Convert_Keys_To_Path (context, count, keys, _hoops_SISAA)) == 0) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");
	}
	else {
		
		_hoops_PGHGH	_hoops_GCHIH;
		ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

		_hoops_GGAGR *	_hoops_GHRI;
		if ((_hoops_GHRI = HI_Force_Find_Path_Actor (context, _hoops_CISAA, _hoops_SISAA, &_hoops_GCHIH.context)) != null) {

			bool	_hoops_GHIGGR = false;

			if (_hoops_SISAA[_hoops_CISAA-1]->type == _hoops_AGCP) {
				_hoops_GCHIH._hoops_PCHIH = (_hoops_HACC const *)_hoops_SISAA[_hoops_CISAA-1];
				_hoops_GCHIH.text.length = _hoops_GCHIH._hoops_PCHIH->count;
				_hoops_GCHIH.text._hoops_IPPPP = _hoops_GCHIH._hoops_PCHIH->karacters;
				_hoops_GCHIH.encoding = _hoops_GCHIH._hoops_PCHIH->encoding;
				--_hoops_CISAA;
			}
			else {
				HI_Convert_Char_To_KName (string, &_hoops_GCHIH.text, HOOPS_WORLD->encoding);
				_hoops_GCHIH.encoding = HOOPS_WORLD->encoding;
				_hoops_GHIGGR = true;
			}

			_hoops_GCHIH.context = null;
			_hoops_GCHIH._hoops_CISAA = _hoops_CISAA;
			_hoops_GCHIH.path = _hoops_SISAA;

			_hoops_GCHIH.item = _hoops_PPRSC;
			_hoops_GCHIH.count = 0;
			_hoops_GCHIH.points = points;
			_hoops_GCHIH.face_list_length = 0;
			_hoops_GCHIH.face_list = list;

			_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH);

			*point_count = _hoops_GCHIH.count;
			*_hoops_PAASR = _hoops_GCHIH.face_list_length;

			if (_hoops_GHIGGR)
				_hoops_PRPIR (_hoops_GCHIH.text);
		}
	}

	_hoops_IRRPR();

	if (_hoops_CISAA > 0)
		FREE_ARRAY (_hoops_SISAA, allocated, _hoops_CRCP *);

#endif
}



HC_INTERFACE void HC_CDECL HC_Compute_Text_Outline_Size_Pa (
	int						count,
	Key const *				keys,
	char const *			string,
	int *					point_count,
	int *					_hoops_PAASR) 
{
	_hoops_PAPPR context("Compute_Text_Outline_Size_By_Path");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Outline_Size_By_Path () */\n");
	);

	_hoops_CRCP const **		_hoops_SISAA;
	int						_hoops_CISAA;
	int						allocated;

	_hoops_CSPPR();
	if ((_hoops_CISAA = allocated = HI_Convert_Keys_To_Path (context, count, keys, _hoops_SISAA)) == 0) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");
	}
	else {

		_hoops_PGHGH		_hoops_GCHIH;
		ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

		_hoops_GGAGR *	_hoops_GHRI;
		if ((_hoops_GHRI = HI_Force_Find_Path_Actor (context, _hoops_CISAA, _hoops_SISAA, &_hoops_GCHIH.context)) != null) {

			if (_hoops_SISAA[_hoops_CISAA-1]->type == _hoops_AGCP) {
				_hoops_GCHIH._hoops_PCHIH = (_hoops_HACC const *)_hoops_SISAA[_hoops_CISAA-1];
				_hoops_GCHIH.text.length = _hoops_GCHIH._hoops_PCHIH->count;
				_hoops_GCHIH.text._hoops_IPPPP = _hoops_GCHIH._hoops_PCHIH->karacters;
				_hoops_GCHIH.encoding = _hoops_GCHIH._hoops_PCHIH->encoding;
				--_hoops_CISAA;
			}
			else {
				HI_Convert_Char_To_KName (string, &_hoops_GCHIH.text, HOOPS_WORLD->encoding);
				_hoops_GCHIH.encoding = HOOPS_WORLD->encoding;
			}

			_hoops_GCHIH.context = null;
			_hoops_GCHIH._hoops_CISAA = _hoops_CISAA;
			_hoops_GCHIH.path = _hoops_SISAA;

			_hoops_GCHIH.item = _hoops_PPRSC;
			_hoops_GCHIH.count = 0;
			_hoops_GCHIH.face_list_length = 0;
			/* _hoops_AGCR "_hoops_IPIGGR" _hoops_GCAPR _hoops_RH _hoops_SIHC _hoops_CPIGGR _hoops_IS _hoops_HGCR _hoops_RGAR _hoops_RH _hoops_PGRR */
			_hoops_GCHIH.points = null;
			_hoops_GCHIH.face_list = null;

			_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH);

			*point_count = _hoops_GCHIH.count;
			*_hoops_PAASR = _hoops_GCHIH.face_list_length;
		}
	}
	_hoops_IRRPR();
	if (_hoops_CISAA > 0)
		FREE_ARRAY (_hoops_SISAA, allocated, _hoops_CRCP *);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////

HC_INTERFACE void HC_CDECL HC_Compute_Text_Extent (
	char const *			segname,
	char const *			string,
	float *					xfrac,
	float *					yfrac) 
{
	_hoops_PAPPR context("Compute_Text_Extent");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Extent () */\n");
	);

	_hoops_PGHGH	_hoops_GCHIH;
	ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

	_hoops_CSPPR();
	_hoops_GGAGR *	_hoops_GHRI;
	if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, segname, &_hoops_GCHIH.context)) != null) {

		HI_Convert_Char_To_KName (string, &_hoops_GCHIH.text, HOOPS_WORLD->encoding);
		_hoops_GCHIH.encoding = HOOPS_WORLD->encoding;

		_hoops_GCHIH.item = _hoops_IARSC;

		if (_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH)) {

			/* _hoops_RGR _hoops_HRGR _hoops_RH _hoops_AGICR _hoops_HIHP _hoops_HII _hoops_SGS (*_hoops_ASAI!!*) _hoops_GGR _hoops_RH _hoops_HHGAI */
			if (yfrac) {
				if (_hoops_GCHIH.yfrac != 0)
					*yfrac = _hoops_GCHIH.yfrac + _hoops_GCHIH._hoops_HHRSC;
				else
					*yfrac = 0.0f;
			}

			if (xfrac) {
				if (_hoops_GCHIH.text.length == 0 || _hoops_GCHIH.xfrac == 0)
					*xfrac = 0.0f;
				else
					*xfrac = _hoops_GCHIH.xfrac + _hoops_GCHIH._hoops_PHRSC;
			}
		}
		else {
			if (xfrac)
				*xfrac = 0.0f;
			if (yfrac)
				*yfrac = 0.0f;
		}

		_hoops_PRPIR (_hoops_GCHIH.text);
	}
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Compute_Text_Extent_With_Enc (
	char const *			segname,
	char const *			encoding,
	char const *			string,
	float *					xfrac,
	float *					yfrac) 
{
	_hoops_PAPPR context("Compute_Text_Extent_With_Encoding");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Extent_With_Enc () */\n");
	);

	_hoops_PGHGH	_hoops_GCHIH;
	ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

	_hoops_CSPPR();
	_hoops_GGAGR *	_hoops_GHRI;
	if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, segname, &_hoops_GCHIH.context)) != null) {

		_hoops_IHGRP	_hoops_SPIGGR = HI_Decipher_Encoding (context, encoding);

		HI_Convert_Char_To_KName (string, &_hoops_GCHIH.text, _hoops_SPIGGR);

		_hoops_GCHIH.encoding = _hoops_SPIGGR;

		_hoops_GCHIH.item = _hoops_IARSC;

		if (_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH)) {

			/* _hoops_RGR _hoops_HRGR _hoops_RH _hoops_AGICR _hoops_HIHP _hoops_HII _hoops_SGS (*_hoops_ASAI!!*) _hoops_GGR _hoops_RH _hoops_HHGAI */
			if (yfrac) {
				if (_hoops_GCHIH.yfrac != 0)
					*yfrac = _hoops_GCHIH.yfrac + _hoops_GCHIH._hoops_HHRSC;
				else
					*yfrac = 0.0f;
			}

			if (xfrac) {
				if (_hoops_GCHIH.text.length == 0 || _hoops_GCHIH.xfrac == 0)
					*xfrac = 0.0f;
				else
					*xfrac = _hoops_GCHIH.xfrac + _hoops_GCHIH._hoops_PHRSC;
			}
		}
		else {
			if (xfrac)
				*xfrac = 0.0f;
			if (yfrac)
				*yfrac = 0.0f;
		}

		_hoops_PRPIR (_hoops_GCHIH.text);
	}
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Compute_Text_Extent_By_Path (
	int						count,
	Key const *				keys,
	char const *			string,
	float *					xfrac,
	float *					yfrac) 
{
	_hoops_PAPPR context("Compute_Text_Extent_By_Path");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Extent_By_Path () */\n");
	);

	_hoops_CRCP const **		_hoops_SISAA;
	int						_hoops_CISAA;
	int						allocated;

	_hoops_CSPPR();
	if ((_hoops_CISAA = allocated = HI_Convert_Keys_To_Path (context, count, keys, _hoops_SISAA)) == 0) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");
	}
	else {

		_hoops_PGHGH	_hoops_GCHIH;
		ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

		_hoops_GGAGR *	_hoops_GHRI;
		if ((_hoops_GHRI = HI_Force_Find_Path_Actor (context, _hoops_CISAA, _hoops_SISAA, &_hoops_GCHIH.context)) != null) {

			if (_hoops_SISAA[_hoops_CISAA-1]->type == _hoops_AGCP) {
				_hoops_GCHIH._hoops_PCHIH = (_hoops_HACC const *)_hoops_SISAA[_hoops_CISAA-1];
				_hoops_GCHIH.text.length = _hoops_GCHIH._hoops_PCHIH->count;
				_hoops_GCHIH.text._hoops_IPPPP = _hoops_GCHIH._hoops_PCHIH->karacters;
				_hoops_GCHIH.encoding = _hoops_GCHIH._hoops_PCHIH->encoding;
				--_hoops_CISAA;
			}
			else {
				HI_Convert_Char_To_KName (string, &_hoops_GCHIH.text, HOOPS_WORLD->encoding);
				_hoops_GCHIH.encoding = HOOPS_WORLD->encoding;
			}

			_hoops_GCHIH.context = null;
			_hoops_GCHIH._hoops_CISAA = _hoops_CISAA;
			_hoops_GCHIH.path = _hoops_SISAA;
			_hoops_GCHIH.item = _hoops_IARSC;

			if (_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH)) {

				/* _hoops_RGR _hoops_HRGR _hoops_RH _hoops_AGICR _hoops_HIHP _hoops_HII _hoops_SGS (*_hoops_ASAI!!*) _hoops_GGR _hoops_RH _hoops_HHGAI */
				if (yfrac) {
					if (_hoops_GCHIH.yfrac != 0)
						*yfrac = _hoops_GCHIH.yfrac + _hoops_GCHIH._hoops_HHRSC;
					else
						*yfrac = 0.0f;
				}
				if (xfrac) {
					if (_hoops_GCHIH.text.length == 0 || _hoops_GCHIH.xfrac == 0)
						*xfrac = 0.0f;
					else
						*xfrac = _hoops_GCHIH.xfrac + _hoops_GCHIH._hoops_PHRSC;
				}
			}
			else {
				if (xfrac)
					*xfrac = 0.0f;
				if (yfrac)
					*yfrac = 0.0f;
			}

			if (_hoops_GCHIH._hoops_PCHIH == null)
				_hoops_PRPIR (_hoops_GCHIH.text);
		}
	}

	_hoops_IRRPR();
	if (_hoops_CISAA > 0)
		FREE_ARRAY (_hoops_SISAA, allocated, _hoops_CRCP *);
#endif
}


HC_INTERFACE void HC_CDECL HC_Compute_Text_Extent_Enc_Path (
	int					count,
	Key const *			keys,
	char const *		encoding,
	char const *		string,
	float *				xfrac,
	float *				yfrac) 
{
	_hoops_PAPPR context("Compute_Text_Extent_With_Encoding_By_Path");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Extent_With_Enc () */\n");
	);

	_hoops_CRCP const **	_hoops_SISAA;
	int					_hoops_CISAA;
	int					allocated;
	
	_hoops_CSPPR();
	if ((_hoops_CISAA = allocated = HI_Convert_Keys_To_Path (context, count, keys, _hoops_SISAA)) == 0) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid Segment");
	}
	else {

		_hoops_PGHGH	_hoops_GCHIH;
		ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

		_hoops_GGAGR *	_hoops_GHRI;
		if ((_hoops_GHRI = HI_Force_Find_Path_Actor (context, _hoops_CISAA, _hoops_SISAA, &_hoops_GCHIH.context)) != null) {

			if (_hoops_SISAA[_hoops_CISAA-1]->type == _hoops_AGCP) {
				_hoops_GCHIH._hoops_PCHIH = (_hoops_HACC const *)_hoops_SISAA[_hoops_CISAA-1];
				_hoops_GCHIH.text.length = _hoops_GCHIH._hoops_PCHIH->count;
				_hoops_GCHIH.text._hoops_IPPPP = _hoops_GCHIH._hoops_PCHIH->karacters;
				_hoops_GCHIH.encoding = _hoops_GCHIH._hoops_PCHIH->encoding;
				--_hoops_CISAA;
			}
			else {
				_hoops_IHGRP	_hoops_SPIGGR = HI_Decipher_Encoding (context, encoding);
				HI_Convert_Char_To_KName (string, &_hoops_GCHIH.text, _hoops_SPIGGR);
				_hoops_GCHIH.encoding = _hoops_SPIGGR;
			}

			_hoops_GCHIH.context = null;
			_hoops_GCHIH._hoops_CISAA = _hoops_CISAA;
			_hoops_GCHIH.path = _hoops_SISAA;
			_hoops_GCHIH.item = _hoops_IARSC;

			if (_hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH)) {

				/* _hoops_RGR _hoops_HRGR _hoops_RH _hoops_AGICR _hoops_HIHP _hoops_HII _hoops_SGS (*_hoops_ASAI!!*) _hoops_GGR _hoops_RH _hoops_HHGAI */

				if (yfrac) {
					if (_hoops_GCHIH.yfrac != 0)
						*yfrac = _hoops_GCHIH.yfrac + _hoops_GCHIH._hoops_HHRSC;
					else
						*yfrac = 0.0f;
				}

				if (xfrac) {
					if (_hoops_GCHIH.text.length == 0 || _hoops_GCHIH.xfrac == 0)
						*xfrac = 0.0f;
					else
						*xfrac = _hoops_GCHIH.xfrac + _hoops_GCHIH._hoops_PHRSC;
				}
			}
			else {
				if (xfrac)
					*xfrac = 0.0f;
				if (yfrac)
					*yfrac = 0.0f;
			}

			if (_hoops_GCHIH._hoops_PCHIH == null)
				_hoops_PRPIR (_hoops_GCHIH.text);
		}
	}
	
	_hoops_IRRPR();
	if (_hoops_CISAA > 0)
		FREE_ARRAY (_hoops_SISAA, allocated, _hoops_CRCP *);
#endif
}


/* _hoops_GCSAA _hoops_CRGPR */

HC_INTERFACE void HC_CDECL HC_Compute_Text_Extent_By_Key (
	Key						key,
	float *					xfrac,
	float *					yfrac) 
{
	_hoops_PAPPR context("Compute_Text_Extent_By_Key");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_Extent_By_Key () */\n");
	);

	_hoops_CSPPR();
	_hoops_HACC *	_hoops_SRPGGR = (_hoops_HACC *)_hoops_RCSSR (context, key);
	if (_hoops_SRPGGR == null || _hoops_SRPGGR->type != _hoops_AGCP ||
		BIT (_hoops_SRPGGR->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_KEY, "Provided key does not refer to valid text");
	}
	else {

		/* _hoops_PAGA: _hoops_RHIGGR._hoops_HCGR _hoops_SHR _hoops_AGCCA _hoops_IS _hoops_IRS _hoops_HPHR _hoops_AARPR _hoops_IGCI, _hoops_HIS _hoops_GA'_hoops_RA _hoops_CIH */
		_hoops_PGHGH		_hoops_GCHIH;
		ZERO_STRUCT (&_hoops_GCHIH, _hoops_PGHGH);

		Key	_hoops_RCGGGR = _hoops_AIRIR (_hoops_SRPGGR->owner);

		_hoops_GGAGR *	_hoops_GHRI;
		if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (context, _hoops_GRSPR (null, "%k", &_hoops_RCGGGR), &_hoops_GCHIH.context)) != null) {

			_hoops_GCHIH._hoops_PCHIH = _hoops_SRPGGR;
			_hoops_GCHIH.text.length = _hoops_SRPGGR->count;
			_hoops_GCHIH.text._hoops_IPPPP = _hoops_SRPGGR->karacters;
			_hoops_GCHIH.encoding = _hoops_SRPGGR->encoding;

			_hoops_GCHIH.item = _hoops_IARSC;

			bool _hoops_AHIGGR = _hoops_HISAA (context, _hoops_GHRI, _hoops_GPGSC, &_hoops_GCHIH);

			if (!_hoops_AHIGGR) {
				if (xfrac)
					*xfrac = 0.0f;
				if (yfrac)
					*yfrac = 0.0f;
			}
			else {
				/* _hoops_RGR _hoops_HRGR _hoops_RH _hoops_AGICR _hoops_HIHP _hoops_HII _hoops_SGS (*_hoops_ASAI!!*) _hoops_GGR _hoops_RH _hoops_HHGAI */

				if (yfrac) {
					if (_hoops_GCHIH.yfrac != 0)
						*yfrac = _hoops_GCHIH.yfrac + _hoops_GCHIH._hoops_HHRSC;
					else
						*yfrac = 0.0f;
				}

				if (xfrac) {
					if (_hoops_GCHIH.text.length == 0 || _hoops_GCHIH.xfrac == 0)
						*xfrac = 0.0f;
					else
						*xfrac = _hoops_GCHIH.xfrac + _hoops_GCHIH._hoops_PHRSC;
				}
			}
		}
	}

	_hoops_IRRPR();
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * _hoops_ASC _hoops_SICAR _hoops_GARIR _hoops_GPP _hoops_RH _hoops_RGSC _hoops_SGS _hoops_SGCRP _hoops_PPAGI _hoops_CHR _hoops_IPIH
 * _hoops_PAPR _hoops_GAR 16-_hoops_IGRH _hoops_CAIPR
 */


HC_INTERFACE void HC_CDECL HC_Compute_Text_From_Text16 (
	int						incount,
	unsigned short const *	intext16,
	char const *			encoding,
	char *					outtext) 
{
	_hoops_PAPPR context("Compute_Text_From_Text16");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text_From_Text16 () */\n");
	);

	_hoops_IHGRP	_hoops_PHIGGR;

	if ((_hoops_PHIGGR = HI_Decipher_Encoding (context, encoding)) == _hoops_PIIGI)
		return;

	HI_Return_Kars (outtext, -1, (Karacter *)intext16, incount, _hoops_PHIGGR);
#endif
}



HC_INTERFACE void HC_CDECL HC_Compute_Text16_From_Text (
	char const *			intext,
	char const *			encoding,
	int *					outcount,
	unsigned short *		outtext16) 
{
	_hoops_PAPPR context("Compute_Text16_From_Text");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Text16_From_Text () */\n");
	);

	int						count;
	Karacter *				_hoops_HHIGGR;
	unsigned short *		_hoops_IHIGGR = outtext16;
	_hoops_IHGRP			_hoops_PHIGGR;
	KName					_hoops_SIHSA;

	if ((_hoops_PHIGGR = HI_Decipher_Encoding (context, encoding)) == _hoops_PIIGI)
		return;

	HI_Convert_Char_To_KName (intext, &_hoops_SIHSA, _hoops_PHIGGR);
	*outcount = count = _hoops_SIHSA.length;
	_hoops_HHIGGR = _hoops_SIHSA._hoops_IPPPP;

	_hoops_RGGA (count-- <= 0)
		*_hoops_IHIGGR++ = (unsigned short)*_hoops_HHIGGR++;

	_hoops_PRPIR (_hoops_SIHSA);
#endif
}


///////////////////////////////////////////////////////////////////////////////////////////////////

local void _hoops_CHIGGR (
	_hoops_HCRPR alter *			start,
	_hoops_HCRPR alter *			end,
	_hoops_HCRPR const *			_hoops_SPIPI) {

	// _hoops_ASHPR _hoops_SHIGGR _hoops_CRGR _hoops_RH _hoops_HIGR; *_hoops_RSGR _hoops_HRGR _hoops_PAHHH _hoops_RHPA.

	while (start < end) {
		char const *		a = _hoops_SPIPI->text;
		char const *		b = start->text;

		/* "_hoops_SHIGGR" _hoops_CGH _hoops_PHHR _hoops_HPGR "_hoops_HSPP" _hoops_RPP _hoops_RGCI _hoops_HCGR _hoops_HRGR _hoops_CRGP _hoops_HSAR _hoops_HSPP'_hoops_GRI */

		do {
			if (*a != *b) {
				if (_hoops_IRGCR (_hoops_SHPCR (*a)) <
					_hoops_IRGCR (_hoops_SHPCR (*b))) {

					/* _hoops_PARRH _hoops_RSGR[-1] _hoops_CRGR _hoops_RSGR[0] _hoops_CCGR _hoops_RSGR == _hoops_HSPP */
					do {
						end[0].text = end[-1].text;
						end[0].length = end[-1].length;
					} while (--end != start);
					goto _hoops_PCPPR;
				}
				break;
			}
			++a, ++b;
		} while (*b != '\0');

		++start;
	}
	_hoops_PCPPR:;

	/* _hoops_PRGRI _hoops_GGSR */
	end->text = _hoops_SPIPI->text;
	end->length = _hoops_SPIPI->length;
}


GLOBAL_FUNCTION bool HD_Gather_Font_Names (
	Display_Context const *		dc,
	_hoops_RCHIH alter *	_hoops_ACHIH) {
	int							count = 0;
	_hoops_HCRPR alter *				_hoops_HGPIR;
	_hoops_RCSSP const *			family;
	Font_Instance const *		instance;

	if ((_hoops_ACHIH->_hoops_RRRSC || _hoops_ACHIH->_hoops_HRRSC) && !dc->_hoops_PSAGH)
		HD_Find_Basic_Fonts(dc);

	if ((_hoops_ACHIH->_hoops_ARRSC || _hoops_ACHIH->_hoops_PRRSC) && !dc->_hoops_HSAGH)
		HD_Find_All_Fonts(dc);

	_hoops_ACHIH->count = 0;
	_hoops_ACHIH->_hoops_HGPIR = null;

	if ((family = dc->_hoops_SGHGH) == null) return true; /* _hoops_CPPPR _hoops_SSHRR */

	/* _hoops_SRS, _hoops_RPR _hoops_GH _hoops_RSH _hoops_AHPH _hoops_RPPCR _hoops_SR _hoops_RRP _hoops_GC _hoops_IH */

	if (_hoops_ACHIH->_hoops_RRRSC) {
		if (dc->_hoops_RRHGH[GFN_ROMAN] != null) ++count;
		if (dc->_hoops_RRHGH[GFN_SANS_SERIF] != null) ++count;
		if (dc->_hoops_RRHGH[GFN_STROKED] != null) ++count;
		if (dc->_hoops_RRHGH[GFN_TYPEWRITER] != null) ++count;
		if (dc->_hoops_RRHGH[GFN_SYSTEM_DEFAULT] != null) ++count;
	}

	if (_hoops_ACHIH->_hoops_ARRSC && _hoops_ACHIH->_hoops_PRRSC) {
		do if (family->font == null) {
			++count;
			instance = family->_hoops_ICSSP;
			if (instance->name.length != 0) { /* _hoops_GIIGGR _hoops_CHR _hoops_ACGIP */
				do ++count;
				while ((instance = instance->_hoops_SSSSP) != null);
			}
		} while ((family = family->next) != null);
	}
	else if (_hoops_ACHIH->_hoops_PRRSC) {
		do if (family->font == null) {
			if (family->_hoops_PCSSP || family->_hoops_ICSSP->name.length != 0)
				++count;		/* _hoops_HPHR _hoops_PCRIP*/
		} while ((family = family->next) != null);
	}
	else if (_hoops_ACHIH->_hoops_ARRSC) {
		do if (family->font == null) {
			instance = family->_hoops_ICSSP;
			if (instance->name.length == 0) {/* _hoops_GIIGGR _hoops_CHR _hoops_HAR _hoops_ACGIP */
				++count;		/* _hoops_RH _hoops_PCRIP _hoops_RSIRR *_hoops_HRGR* _hoops_RH _hoops_SASI _hoops_RSIRR */
			}
			else {				/* _hoops_GIIGGR _hoops_CHR _hoops_ACGIP */
				do ++count;
				while ((instance = instance->_hoops_SSSSP) != null);
			}
		} while ((family = family->next) != null);
	}

	if (count == 0) return true;

	_hoops_ACHIH->count = count;

	ALLOC_ARRAY (_hoops_HGPIR, count, _hoops_HCRPR);

	_hoops_ACHIH->_hoops_HGPIR = _hoops_HGPIR;

	if (_hoops_ACHIH->_hoops_RRRSC) {
#		define	_hoops_RIIGGR(which, _hoops_AIIGGR)					\
			if (which != null) {							\
				local	char	result[] = _hoops_AIIGGR;			\
				_hoops_HGPIR->length = (int)sizeof(result) - 1;	\
				_hoops_HGPIR->text = result;						\
				++_hoops_HGPIR;									\
			}

		/* (_hoops_GPGP _hoops_PIIGGR _hoops_AGR, _hoops_RPP _hoops_RHAC _hoops_IPHIA) */
		_hoops_RIIGGR (dc->_hoops_RRHGH[GFN_ROMAN],				"roman");
		_hoops_RIIGGR (dc->_hoops_RRHGH[GFN_SANS_SERIF],		"sans serif");
		_hoops_RIIGGR (dc->_hoops_RRHGH[GFN_STROKED],			"stroked");
		_hoops_RIIGGR (dc->_hoops_RRHGH[GFN_SYSTEM_DEFAULT],	"system default");
		_hoops_RIIGGR (dc->_hoops_RRHGH[GFN_TYPEWRITER],		"typewriter");
	}

	family = dc->_hoops_SGHGH;
	if (_hoops_ACHIH->_hoops_ARRSC && _hoops_ACHIH->_hoops_PRRSC) {
		do if (family->font == null) {
			_hoops_CHIGGR (_hoops_ACHIH->_hoops_HGPIR, ++_hoops_HGPIR, &family->name);
			instance = family->_hoops_ICSSP;
			if (instance->name.length != 0) { /* _hoops_GIIGGR _hoops_CHR _hoops_ACGIP */
				do _hoops_CHIGGR (_hoops_ACHIH->_hoops_HGPIR, ++_hoops_HGPIR, &instance->name);
				while ((instance = instance->_hoops_SSSSP) != null);
			}
		} while ((family = family->next) != null);
	}
	else if (_hoops_ACHIH->_hoops_PRRSC) {
		do if (family->font == null) {
			if (family->_hoops_PCSSP || family->_hoops_ICSSP->name.length != 0)
				_hoops_CHIGGR (_hoops_ACHIH->_hoops_HGPIR, _hoops_HGPIR++, &family->name);
		} while ((family = family->next) != null);
	}
	else if (_hoops_ACHIH->_hoops_ARRSC) {
		do if (family->font == null) {
			instance = family->_hoops_ICSSP;
			if (instance->name.length == 0) {/* _hoops_GIIGGR _hoops_CHR _hoops_HAR _hoops_ACGIP */
				_hoops_CHIGGR (_hoops_ACHIH->_hoops_HGPIR, _hoops_HGPIR++, &family->name);
			}
			else {				/* _hoops_GIIGGR _hoops_CHR _hoops_ACGIP */
				do _hoops_CHIGGR (_hoops_ACHIH->_hoops_HGPIR, _hoops_HGPIR++, &instance->name);
				while ((instance = instance->_hoops_SSSSP) != null);
			}
		} while ((family = family->next) != null);
	}

	return true;
}


#ifndef DISABLE_COMPUTE

local void _hoops_IGARH (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	bool						_hoops_RCRHH) {
	Display_Context const *		dc = nr->_hoops_SRA;
	Attribute const *			_hoops_HPHCR;

	if (_hoops_SRCP != HOOPS_WORLD->root && _hoops_RCRHH) {
		while (_hoops_SRCP->_hoops_IPPGR == null) {
			_hoops_SRCP = (_hoops_CRCP const *)_hoops_SRCP->owner;
			if ((_hoops_CRCP const *)_hoops_SRCP == HOOPS_WORLD->root) break;
		}

		if (_hoops_SRCP != HOOPS_WORLD->root)
			_hoops_IGARH (nr, (_hoops_CRCP const *)_hoops_SRCP->owner, true);
	}

	if (_hoops_SRCP == dc->_hoops_AAHSR)
		HD_Calculate_Outer_Window (nr);

	if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) do {
		switch (_hoops_HPHCR->type) {
			case HK_STYLE: {
#ifndef DISABLE_STYLE_SEGMENT
				_hoops_IGARH (nr, ((Style *)_hoops_HPHCR)->_hoops_IGRPR, false);
#endif
			}	break;

			case HK_TEXT_PATH: {
				_hoops_RGPIR *					_hoops_HGGCH = (_hoops_RGPIR *)_hoops_HPHCR;
				_hoops_IGCSR alter &		_hoops_HRCIR = nr->_hoops_SISI;

				_hoops_HRCIR->path.x = _hoops_HGGCH->value.x;
				_hoops_HRCIR->path.y = _hoops_HGGCH->value.y;
				_hoops_HRCIR->path.z = _hoops_HGGCH->value.z;

				if (_hoops_HRCIR->_hoops_CRRIP) {
					if (_hoops_HRCIR->path.x != 0.0f || _hoops_HRCIR->path.y != 0.0f)
						_hoops_HRCIR->rotation = _hoops_AGGGA (_hoops_HRCIR->path.y, _hoops_HRCIR->path.x);
				}
			}	break;

			case HK_TEXT_SPACING: {
				nr->_hoops_SISI->spacing = ((_hoops_PHCAP *)_hoops_HPHCR)->data.value;
			}	break;

			case HK_TEXT_FONT: {
				HD_Downwind_Text_Font (nr, (_hoops_AGPIR const *)_hoops_HPHCR);
			}	break;

			case HK_WINDOW: {
				HD_Downwind_Window (nr, _hoops_HPHCR);
			}	break;

			case HK_WINDOW_FRAME: {
				HD_Downwind_Window_Frame (nr, _hoops_HPHCR);
			}	break;

			case HK_RENDERING_OPTIONS: {
				_hoops_RHAIR const	*_hoops_AHAIR = (_hoops_RHAIR const *) _hoops_HPHCR;

				if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_APRAP) &&
					(_hoops_AHAIR->_hoops_HCIH.left != nr->transform_rendition->_hoops_HCIH.left ||
					 _hoops_AHAIR->_hoops_HCIH.right != nr->transform_rendition->_hoops_HCIH.right ||
					 _hoops_AHAIR->_hoops_HCIH.bottom != nr->transform_rendition->_hoops_HCIH.bottom ||
					 _hoops_AHAIR->_hoops_HCIH.top != nr->transform_rendition->_hoops_HCIH.top)) {
					_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();
					_hoops_HRPA						_hoops_RHSPR;

					HD_Undo_Screen (nr, &_hoops_RHSPR);
					_hoops_GGCC->_hoops_HCIH = _hoops_AHAIR->_hoops_HCIH;
					HD_Redo_Screen (nr, &_hoops_RHSPR);
				}
			}	break;

		/* _hoops_SPS _hoops_PGCR _hoops_CR _hoops_SR _hoops_GHCA _hoops_RRP _hoops_IS _hoops_HIHP _hoops_RH _hoops_CRAA */

			case HK_CAMERA: {
				HD_Downwind_Camera (nr, _hoops_HPHCR);
			}	break;

			case HK_MODELLING_MATRIX: {
				HD_Downwind_Modelling_Matrix (nr, _hoops_HPHCR);
			}	break;

			default:	break;
		}
	} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
}

local bool _hoops_SGCHS () {return false;}

local void _hoops_HIIGGR (
	Net_Rendition const & 		nr,
	Text_Info const *			ti) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_PGHGH alter *	_hoops_GCHIH = dc->_hoops_HGHGH;
	int							count = ti->_hoops_SIHSA.length;
	int							index = 0;

	while (count-- > 0) {
		_hoops_PGCSR const *	_hoops_HGCSR;
		int								_hoops_PPPSP;
		float							l, r, b, t;

		if (ti->_hoops_PPPSP)
			_hoops_PPPSP = ti->_hoops_PPPSP[index++];
		else
			_hoops_PPPSP = index++;

		_hoops_HGCSR = &ti->_hoops_HGCSR[_hoops_PPPSP];

		l = _hoops_HGCSR->position.x - _hoops_HGCSR->screen.x;
		r = l + _hoops_HGCSR->screen.width;
		b = _hoops_HGCSR->position.y - _hoops_HGCSR->screen.y;
		t = b + _hoops_HGCSR->screen.height;

		if (l < _hoops_GCHIH->left)
			_hoops_GCHIH->left = l;
		if (r > _hoops_GCHIH->right)
			_hoops_GCHIH->right = r;

		if (b < _hoops_GCHIH->bottom)
			_hoops_GCHIH->bottom = b;
		if (t > _hoops_GCHIH->top)
			_hoops_GCHIH->top = t;

		++_hoops_HGCSR;
	}
}
#endif


GLOBAL_FUNCTION bool HD_Gather_Text_Extent (
	Display_Context alter *		dc,
	_hoops_PGHGH alter *	_hoops_GCHIH) {
#ifndef DISABLE_COMPUTE
	_hoops_HACC alter *				text = null;
	_hoops_CRCP const *				_hoops_SRCP = _hoops_GCHIH->context;
	Net_Rendition				nr;
	_hoops_APARR				_hoops_RRCI;
	float						_hoops_AHPCS,
								_hoops_RSICC;
	bool						_hoops_IA = false;
	float						_hoops_SCRHH,
								_hoops_GSRHH;
	Karacter const *			_hoops_HSGGGR;
	int							count;
	KName						_hoops_IIIGGR;
	bool						_hoops_CIIGGR = true;
	float						X_width = 0.0f, X_height = 0.0f;
	Vector						_hoops_GHPSP;	/* _hoops_IH _hoops_GRR _hoops_GAS */

	nr = Net_Rendition::Create(dc);
	_hoops_IHAGI (_hoops_IIIGGR);

	if (_hoops_SRCP != null) {
		/* _hoops_RSRA _hoops_CAGH _hoops_RAGA */
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {		/* _hoops_ARARH */
			Subsegment const *_hoops_GIPIA;

			_hoops_RGGA ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) == null) {
				_hoops_RGGA (_hoops_GIPIA->next == null) _hoops_GIPIA = _hoops_GIPIA->next;
				if (_hoops_GIPIA->type != _hoops_IRCP) break;
				_hoops_SRCP = (_hoops_CRCP const *)_hoops_GIPIA;
			}
		}

		_hoops_IGARH (nr, _hoops_SRCP, true);
	}
	else {
		/* _hoops_CAGH _hoops_CRAA _hoops_CHIA */
		_hoops_CRCP const **	_hoops_RSRHH = _hoops_GCHIH->path;
		int					_hoops_CISAA = _hoops_GCHIH->_hoops_CISAA;
		bool				_hoops_RCRHH = true;

		while (_hoops_CISAA-- != 0) {
			_hoops_SRCP = *_hoops_RSRHH++;

			if (_hoops_SRCP->type != _hoops_IRCP)
				break;

			_hoops_IGARH (nr, _hoops_SRCP, _hoops_RCRHH);
			_hoops_RCRHH = false;
		}
	}

	_hoops_CGRA const &		_hoops_SGRA = nr->_hoops_SAIR;
	_hoops_IGCSR const &			_hoops_HRCIR = nr->_hoops_SISI;

	_hoops_SCRHH =	  (float)(_hoops_SGRA->_hoops_CIIH.right - _hoops_SGRA->_hoops_CIIH.left);
	_hoops_GSRHH =  (float)(_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom);

	if (_hoops_SCRHH == 0 || _hoops_GSRHH == 0) {
		_hoops_GCHIH->xfrac = _hoops_GCHIH->yfrac = 1;
		_hoops_GCHIH->_hoops_PHRSC = _hoops_GCHIH->_hoops_HHRSC = 1;
		_hoops_IA = true;
		goto _hoops_HPAGR;
	}


	{	/* _hoops_HHSP _hoops_SIIGGR _hoops_PPR _hoops_GII _hoops_HSHCS */
		_hoops_IGCSR alter &	_hoops_IRRIP = nr->_hoops_SISI;

		_hoops_IRRIP->_hoops_HCPAP = 0;
		_hoops_IRRIP->_hoops_SCRIP = _hoops_IRRIP->_hoops_GSRIP = _hoops_IRRIP->_hoops_RSRIP = false;
	}

	_hoops_GCHIH->left = _hoops_GCHIH->bottom = MAX_FLOAT;
	_hoops_GCHIH->right = _hoops_GCHIH->top = -MAX_FLOAT;

	if ((text = (_hoops_HACC alter *)_hoops_GCHIH->_hoops_PCHIH) != null) {
		_hoops_HSGGGR = text->karacters;
		count = text->count;
	}
	else {
		_hoops_HSGGGR = _hoops_GCHIH->text._hoops_IPPPP;
		count = _hoops_GCHIH->text.length;
	}

	if (count == 0) {
		HI_Convert_Char_To_KName (".", &_hoops_IIIGGR, _hoops_SSAIP);
		_hoops_HSGGGR = _hoops_IIIGGR._hoops_IPPPP;
		count = _hoops_IIIGGR.length;
	}
	else {
		Karacter const *	_hoops_GCIGGR = _hoops_HSGGGR;
		int					_hoops_HAHC = count;
		int					_hoops_SGII = count;
		Karacter alter *	_hoops_IHSCP;

		while (count-- > 0) {
			if (*_hoops_HSGGGR++ != (Karacter)'\n')
				_hoops_CIIGGR = false;
		}
		_hoops_HSGGGR = _hoops_GCIGGR;
		count = _hoops_HAHC;

		if (_hoops_HSGGGR[0] == (Karacter)'\n')
			++_hoops_SGII;
		if (_hoops_HSGGGR[count-1] == (Karacter)'\n')
			++_hoops_SGII;

		if (_hoops_SGII != count) {
			_hoops_IIIGGR.length = _hoops_SGII;
			ALLOC_ARRAY (_hoops_IHSCP, _hoops_SGII+1, Karacter);
			_hoops_IIIGGR._hoops_IPPPP = _hoops_IHSCP;
			if (_hoops_HSGGGR[0] == (Karacter)'\n')
				*_hoops_IHSCP++ = (Karacter)'.';
			_hoops_AIGA (_hoops_HSGGGR, count, Karacter, _hoops_IHSCP);
			_hoops_IHSCP += count;
			if (_hoops_HSGGGR[count-1] == (Karacter)'\n')
				*_hoops_IHSCP++ = (Karacter)'.';
			*_hoops_IHSCP = 0;

			text = null;
			_hoops_HSGGGR = _hoops_IIIGGR._hoops_IPPPP;
			count = _hoops_IIIGGR.length;
		}
	}


	if (text == null) {
		Karacter *				_hoops_RSSIH;
		int							_hoops_HRPGGR;
		int							i;

		ZALLOC (text, _hoops_HACC);
		text->type = _hoops_AGCP;
		text->_hoops_HIHI = 1;

		text->karacters = (Karacter *)HI_Clone_Anything (_hoops_HSGGGR, (count+1) * (long)sizeof (Karacter));
		text->count = count;
		text->encoding = _hoops_GCHIH->encoding;

		text->_hoops_PICHR = 1;
		for (i = 0; i < text->count; ++i) {
			if (text->karacters[i] == (Karacter)'\n')
				++text->_hoops_PICHR;
		}

		ALLOC_ARRAY (text->_hoops_ICI, text->_hoops_PICHR, int);
		ALLOC_ARRAY (text->_hoops_RIHIR, text->_hoops_PICHR, Karacter *);

		_hoops_HRPGGR = 0;
		/* _hoops_SPS _hoops_SPAHS _hoops_RH _hoops_PISC _hoops_AGIR _hoops_IIGR _hoops_IRS _hoops_HACH \_hoops_ACHP */
		text->_hoops_RIHIR[text->_hoops_PICHR-1] = &text->karacters[text->count];

		text->_hoops_RIHIR[0] = _hoops_RSSIH = text->karacters;
		for (i = 0; i < text->count; ++i) {
			if (text->karacters[i] == (Karacter)'\n') {
				if (_hoops_RSSIH != null)
					text->_hoops_ICI[_hoops_HRPGGR++] = &text->karacters[i] - _hoops_RSSIH;
				else {
					/* _hoops_RRI _hoops_HSAR _hoops_SPR _hoops_GGR _hoops_IRS _hoops_GAGHR */
					text->_hoops_RIHIR[_hoops_HRPGGR] = &text->karacters[i];
					text->_hoops_ICI[_hoops_HRPGGR++] = 0;
				}
				_hoops_RSSIH = null;
			}
			else if (_hoops_RSSIH == null)
				text->_hoops_RIHIR[_hoops_HRPGGR] = _hoops_RSSIH = &text->karacters[i];
		}
		if (_hoops_RSSIH == null)
			text->_hoops_ICI[_hoops_HRPGGR] = 0;
		else
			text->_hoops_ICI[_hoops_HRPGGR] = &text->karacters[i] - _hoops_RSSIH;

	}
	else
		_hoops_PRRH (text);

	dc->_hoops_HGHGH = _hoops_GCHIH;
	_hoops_RRCI = _hoops_HGCGA (dc, "gather text extent", nr);
	_hoops_RRCI->_hoops_CSCGA = _hoops_HIIGGR;
	_hoops_RRCI->draw_dc_polyline = (_hoops_CHCGA)_hoops_SGCHS;

	_hoops_PAPGR (nr, text);

	_hoops_HGSGA (dc, "gather text extent");
	dc->_hoops_HGHGH = null;

	_hoops_HPRH (text);

	if (_hoops_GCHIH->right < _hoops_GCHIH->left) {
		_hoops_AHPCS = 0;
		_hoops_RSICC = 0;
	}
	else {
		_hoops_AHPCS = _hoops_GCHIH->right - _hoops_GCHIH->left + 1;
		_hoops_RSICC = _hoops_GCHIH->top - _hoops_GCHIH->bottom + 1;
	}

	if (_hoops_CIIGGR)
		_hoops_AHPCS = 0;

	if (BIT (HOOPS_WORLD->system_flags, _hoops_RGSPP)) {
		local		Karacter const				_hoops_RCIGGR = (Karacter)_hoops_RHHPP('X');

		/* _hoops_RCSA _hoops_GRR _hoops_GAS _hoops_GRS _hoops_SHH _hoops_CHCC */
		_hoops_RICH (_hoops_HRCIR->rotation, _hoops_GHPSP.y, _hoops_GHPSP.x);
		_hoops_GHPSP.z = 0.0f;

		_hoops_CAAI (HOOPS_WORLD->_hoops_HPHGI);
		if (_hoops_HRCIR->font == null || 
			!HI_Encoding_Is_Compatible (_hoops_GCHIH->encoding, _hoops_HRCIR->font->encoding)) {

			do {
				HD_Choose_Font (nr, _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR, _hoops_GCHIH->encoding, true);

				/* _hoops_GHCA _hoops_HAR _hoops_SHH _hoops_SHSS _hoops_IS _hoops_HSRS _hoops_GII _hoops_HRCSR _hoops_GGR _hoops_RGR _hoops_AGIR, _hoops_HIS _hoops_RCRP _hoops_GH */
				if (_hoops_HRCIR->font == null) {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Problems loading the requested font");
					_hoops_APAI (HOOPS_WORLD->_hoops_HPHGI);
					goto _hoops_HPAGR;
				}

			} _hoops_RGGA (HD_Load_Font (dc, _hoops_HRCIR->font));
		}
		else{
			/* _hoops_PAAP _hoops_RH _hoops_SCGR _hoops_HRCSR _hoops_HPHS */
			Font_Instance alter *_hoops_GGHCS = (Font_Instance alter *)_hoops_HRCIR->font;

			(*_hoops_GGHCS->_hoops_SSCSP)(nr, _hoops_GGHCS);
		}

		HD_Measure_Characters (nr, 1, &_hoops_RCIGGR, _hoops_GCHIH->encoding, &X_width);
		X_width *= _hoops_HRCIR->width_scale;
		X_height = _hoops_HRCIR->font->_hoops_ISISR;
		_hoops_APAI (HOOPS_WORLD->_hoops_HPHGI);
	}
	else
		ZERO_STRUCT (&_hoops_GHPSP, Vector);


	if (_hoops_HRCIR->transform == FT_FULL) {
		_hoops_HHCR const &		_hoops_IHCR = nr->transform_rendition;
		float							_hoops_RGRS, ysize, _hoops_CCGH;

		_hoops_RGRS = (float) _hoops_SCRHH;
		ysize = (float) _hoops_GSRHH * dc->current._hoops_AGRS;
		if(_hoops_SGRA->_hoops_CSIH >= 1.0)
			_hoops_CCGH = _hoops_IAAA(_hoops_RGRS, ysize);
		else
			_hoops_CCGH = _hoops_AHIA(_hoops_RGRS, ysize);

		if (_hoops_IHCR->_hoops_SPH->projection == _hoops_SSIH) {
			if (_hoops_IHCR->_hoops_SPH->_hoops_CSIH < _hoops_SGRA->_hoops_CSIH)
				ysize /= _hoops_SGRA->_hoops_CSIH;
			else
				_hoops_RGRS *= _hoops_SGRA->_hoops_CSIH;
		}
		else {
			if(nr->transform_rendition->_hoops_SPH->_hoops_CSIH <= 1.0 ){
				_hoops_RGRS *= (nr->transform_rendition->_hoops_SPH->_hoops_CSIH / _hoops_SGRA->_hoops_CSIH);
				ysize *= (nr->transform_rendition->_hoops_SPH->_hoops_CSIH / _hoops_SGRA->_hoops_CSIH);

				if (nr->transform_rendition->_hoops_SPH->_hoops_CSIH < _hoops_SGRA->_hoops_CSIH)
					_hoops_CCGH *= (nr->transform_rendition->_hoops_SPH->_hoops_CSIH / _hoops_SGRA->_hoops_CSIH);

				if (_hoops_IHCR->_hoops_SPH->_hoops_CSIH > _hoops_SGRA->_hoops_CSIH)	
					ysize = _hoops_RGRS;
				else
					_hoops_RGRS = ysize;
			}
			else{
				if (_hoops_IHCR->_hoops_SPH->_hoops_CSIH < _hoops_SGRA->_hoops_CSIH)
					ysize = _hoops_RGRS;
				else
					_hoops_RGRS = ysize;
			}

		}

		if (_hoops_HRCIR->_hoops_GHGRP == GSU_ORU) {
			_hoops_HHRA const *	_hoops_SPH = nr->transform_rendition->_hoops_SPH;

			_hoops_RGRS /= _hoops_SPH->_hoops_SSPA * 0.5f;
			ysize /= _hoops_SPH->_hoops_SSPA * 0.5f;
			_hoops_CCGH /= _hoops_SPH->_hoops_SSPA * 0.5f;
		}

		_hoops_GCHIH->xfrac = 2.0f * _hoops_AHPCS / _hoops_CCGH;
		_hoops_GCHIH->yfrac = 2.0f * _hoops_RSICC / _hoops_CCGH;

		_hoops_GCHIH->_hoops_PHRSC = 2.0f * (X_width * Abs (_hoops_GHPSP.x) + X_height * Abs (_hoops_GHPSP.y)) / _hoops_RGRS;
		_hoops_GCHIH->_hoops_HHRSC = 2.0f * (X_height * Abs (_hoops_GHPSP.x) + X_width * Abs (_hoops_GHPSP.y)) / ysize;
	}
	else {
		_hoops_GCHIH->xfrac = _hoops_AHPCS / _hoops_SCRHH;
		_hoops_GCHIH->yfrac = _hoops_RSICC / _hoops_GSRHH;

		_hoops_GCHIH->_hoops_PHRSC = (X_width * Abs (_hoops_GHPSP.x) + X_height * Abs (_hoops_GHPSP.y)) / _hoops_SCRHH;
		_hoops_GCHIH->_hoops_HHRSC = (X_height * Abs (_hoops_GHPSP.x) + X_width * Abs (_hoops_GHPSP.y)) / _hoops_GSRHH;
	}

	_hoops_IA = true;

 _hoops_HPAGR:

	_hoops_PRPIR (_hoops_IIIGGR);

	return _hoops_IA;
#else
	return false;
#endif
}



GLOBAL_FUNCTION bool HD_Gather_Font_Info (
	Display_Context alter *		dc,
	_hoops_PGHGH alter *	_hoops_GCHIH) {
	char alter *				_hoops_ASAPR;
	char alter *				_hoops_PSAPR;

	HD_Get_Current_Info (dc);

#ifndef DISABLE_COMPUTE
	if (_hoops_GCHIH->item == _hoops_PPRSC)
		return HD_Gather_Text_Outline (dc, _hoops_GCHIH);
	else if (_hoops_GCHIH->item == _hoops_IARSC)
		return HD_Gather_Text_Extent (dc, _hoops_GCHIH);
#endif

	_hoops_ASAPR = _hoops_GCHIH->_hoops_SPRSC;

	if (_hoops_GCHIH->_hoops_GHRSC == -1)
		_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;		/* _hoops_IHRPR _hoops_IAHA */
	else
		_hoops_PSAPR = _hoops_ASAPR + _hoops_GCHIH->_hoops_GHRSC;				/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */


	{
		_hoops_CRCP const *				_hoops_SRCP = _hoops_GCHIH->context;
		Net_Rendition				nr;

		nr = Net_Rendition::Create(dc);

		if (_hoops_SRCP != null) {
			/* _hoops_RSRA _hoops_CAGH _hoops_RAGA */
			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {		/* _hoops_ARARH */
				Subsegment const *_hoops_GIPIA;

				while ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) {
					while (_hoops_GIPIA->next != null)
						_hoops_GIPIA = _hoops_GIPIA->next;
					if (_hoops_GIPIA->type != _hoops_IRCP)
						break;
					_hoops_SRCP = (_hoops_CRCP const *)_hoops_GIPIA;
				}
			}

			_hoops_IGARH (nr, _hoops_SRCP, true);
		}
		else {
			/* _hoops_CAGH _hoops_CRAA _hoops_CHIA */
			_hoops_CRCP const **	_hoops_RSRHH = _hoops_GCHIH->path;
			int					_hoops_CISAA = _hoops_GCHIH->_hoops_CISAA;
			bool				_hoops_RCRHH = true;

			while (_hoops_CISAA-- != 0) {
				_hoops_SRCP = *_hoops_RSRHH++;

				if (_hoops_SRCP->type != _hoops_IRCP)
					break;

				_hoops_IGARH (nr, _hoops_SRCP, _hoops_RCRHH);
				_hoops_RCRHH = false;
			}
		}

		_hoops_IGCSR alter &	_hoops_HRCIR = nr->_hoops_SISI;
		_hoops_IHGRP			encoding = _hoops_SSAIP;
		_hoops_IGPIR				_hoops_CAGRA;
		_hoops_IGPIR const *		_hoops_ACIGGR;


		if (_hoops_GCHIH->item == _hoops_HARSC) {
			_hoops_HRCIR->_hoops_PHP = _hoops_GCHIH->height;	/* _hoops_RRP _hoops_IRS _hoops_HPHR _hoops_HRCSR */
		}
		else if (_hoops_GCHIH->item == _hoops_SRRSC) {
			/* _hoops_RRP _hoops_IRS _hoops_HPHR _hoops_HRCSR, _hoops_HIH _hoops_SR _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RH _hoops_IGIR */
			/* _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_IRS _hoops_AHSGH, _hoops_SGH _hoops_RH _hoops_IRRPA (_hoops_RCASA) */
#define _hoops_PCIGGR		500
			_hoops_HRCIR->_hoops_PHP = (float)_hoops_PCIGGR;
			_hoops_HRCIR->_hoops_ACPAP = 100.0f;
		}
		else {
			_hoops_HRCIR->_hoops_PHP = 0.0f;	/* _hoops_RSPH _hoops_SCH; _hoops_HSCRH _hoops_HRGSI _hoops_HCIGGR _hoops_RGR */
		}

		if (_hoops_GCHIH->specified.length != 0) {
			_hoops_CAGRA.next = null;
			_hoops_CAGRA._hoops_SSSGP = _hoops_GCHIH->_hoops_SSSGP;
			_hoops_CAGRA.specified.length = _hoops_GCHIH->specified.length;
			_hoops_CAGRA.specified.text = _hoops_GCHIH->specified.text;
			_hoops_ACIGGR = &_hoops_CAGRA;
		}
		else
			_hoops_ACIGGR = _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR;


		_hoops_CAAI (HOOPS_WORLD->_hoops_HPHGI);
		do {
			HD_Choose_Font (nr, _hoops_ACIGGR, encoding, false);

			if (_hoops_HRCIR->font != null) switch (_hoops_ACIGGR->_hoops_SSSGP) {
				/* _hoops_AASSC _hoops_GGSR _hoops_GSPIP _hoops_SGS _hoops_SARS'_hoops_RA _hoops_CPSA _hoops_PSSP */
				case GFN_SANS_SERIF:
				case GFN_TYPEWRITER:
				case GFN_ROMAN:
				case GFN_STROKED:
				case GFN_SYSTEM_DEFAULT: {
					if (_hoops_HRCIR->font->_hoops_IRGGH != _hoops_ACIGGR->_hoops_SSSGP)
						_hoops_HRCIR->font = null;
				}	break;

				case GFN_SPECIFIED: {
					if (_hoops_HRCIR->_hoops_PRPSP)
						_hoops_HRCIR->font = null;
				}	break;
			}

			if (_hoops_HRCIR->font != null) break;
		} _hoops_RGGA (++encoding > _hoops_SIIGI);

		if (_hoops_GCHIH->item == _hoops_IRRSC) {
			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, (_hoops_HRCIR->font != null) ? "yes" : "no", null);
		}
		else if (_hoops_HRCIR->font != null) switch (_hoops_GCHIH->item) {
			case _hoops_RPRSC: {
				if (_hoops_HRCIR->font->family->font == null)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "no", null);
				else if (_hoops_HRCIR->font->family->font->_hoops_IAHAP)
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "internal", null);
				else
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "yes", null);
			}	break;

			case _hoops_AARSC:
			case _hoops_GARSC: {
				if (_hoops_HRCIR->font->_hoops_ISISR == 0.0f) {
					/* _hoops_SCH'_hoops_GRI _hoops_ICIGGR, _hoops_PPR _hoops_SR _hoops_HS _hoops_IRS _hoops_AHCI _hoops_SPR */

					if (_hoops_HRCIR->font->_hoops_SSSSP != null) /* _hoops_GII _hoops_PGRR? */
						_hoops_HRCIR->font = _hoops_HRCIR->font->_hoops_SSSSP; /* _hoops_SGH _hoops_SCH */
					else {
						/* _hoops_HHSA _hoops_IRS _hoops_PISA _hoops_IGIR - 20 _hoops_IGPSH */
						_hoops_HRCIR->_hoops_PHP = 20.0f;
						_hoops_HRCIR->font = null;

						HD_Choose_Font (nr, &_hoops_CAGRA, encoding, true);
					}
				}

				if (_hoops_HRCIR->font->_hoops_ISISR != 0.0f && HD_Load_Font (dc, _hoops_HRCIR->font)) {
					switch (_hoops_GCHIH->item) {
						case _hoops_GARSC: {
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "unknown", null);
							/*_hoops_SIGP _hoops_PCPA _hoops_AHCA _hoops_RGR?*/
						}	break;

						case _hoops_AARSC: {
							switch (_hoops_HRCIR->font->encoding) {
								int result;

								case _hoops_SSAIP:
									result = 255;
									_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%d", &result);
									break;

								case _hoops_GSPPH:
								case _hoops_AGHPH:
								case _hoops_HSPPH:
								case _hoops_SSPPH:
								case _hoops_CSPPH:
								case _hoops_SACSR:
									result = 65535;
									_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%d", &result);
									break;

								default:
									_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "unknown", null);
									break;
							}
						}	break;
					}
				}
			}	break;

			case _hoops_APRSC: {
				HI_Show_Encoding_Type (_hoops_GCHIH->_hoops_SPRSC, _hoops_GCHIH->_hoops_GHRSC, _hoops_HRCIR->font->encoding);
				return true;
			}	_hoops_HHHI;

			case _hoops_RARSC: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, (_hoops_HRCIR->font->family->_hoops_PCSSP) ? "yes" : "no", null);
			}	break;

			case _hoops_CARSC: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR,
					 BIT (_hoops_HRCIR->font->_hoops_CAGGH, _hoops_GPCSR) ?	"yes" :
					 BIT (_hoops_HRCIR->font->_hoops_CAGGH, _hoops_SRGGH) ?	"90 degree" :
																	"no", null);
			}	break;

			case _hoops_SARSC: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, BIT (_hoops_HRCIR->font->_hoops_CAGGH, _hoops_GAGGH) ? "yes" : "no", null);
			}	break;

			case _hoops_GPRSC: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR,
					 BIT (_hoops_HRCIR->font->_hoops_CAGGH, _hoops_RAGGH) ? "yes" : "no", null);
			}	break;

			case _hoops_HPRSC: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR,
					 (_hoops_HRCIR->font->family->_hoops_RRCSR == _hoops_SISSP) ? "yes" : "no", null);
			}	break;

			case _hoops_PARSC: {
				switch (_hoops_HRCIR->font->_hoops_IRGGH) {
					case GFN_SANS_SERIF: {
						local	const char		sans_serif[] = "sans serif";
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)sans_serif);
					}	break;

					case GFN_TYPEWRITER: {
						local	const char		typewriter[] = "typewriter";
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)typewriter);
					}	break;

					case GFN_ROMAN: {
						local	const char		roman[] = "roman";
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)roman);
					}	break;

					case GFN_STROKED: {
						local	const char		stroked[] = "stroked";
						_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)stroked);
					}	break;

					case GFN_SYSTEM_DEFAULT: {
						local	const char	  system_default[] = "system default";
						if (_hoops_HRCIR->font == dc->_hoops_RRHGH[GFN_SYSTEM_DEFAULT])
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%s", (void *)system_default);
					}	break;
				}
			}	break;

			case _hoops_SRRSC: {
				if (_hoops_HRCIR->font->_hoops_IGGGH > 0 && _hoops_HRCIR->font->_hoops_ISISR > 0 ||
					HD_Load_Font (dc, _hoops_HRCIR->font)) {
					float			factor;

					factor = (float)(1.0/72 *			/* _hoops_IPIHH _hoops_RIR _hoops_PPSR */
									2.54) /				/* _hoops_SAPSR _hoops_RIR _hoops_CPIHH */
							 dc->current.size.y /		/* _hoops_SAPSR _hoops_RIR _hoops_SHPR */
							 (float)_hoops_HRCIR->font->_hoops_IGGGH *	/* _hoops_HII _hoops_SGPSH-_hoops_APPS */
							 (float)_hoops_HRCIR->font->_hoops_ISISR;	/* _hoops_IS _hoops_CCIGGR-_hoops_APPS */

					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%.8f", (void *)&factor);
				}
			}	break;

			case _hoops_HARSC: {
				_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "0.0", null);/* _hoops_HSGR _hoops_GSPR _hoops_AHHR */
				/*_hoops_SIGP _hoops_PCPA _hoops_ARI*/
			}	break;

			case _hoops_CRRSC: {
				Font_Instance const	*	instance;
				float					_hoops_HHP, result;

				_hoops_HHP = (float)(72 *					/* _hoops_RSSA _hoops_RIR _hoops_CPIHH */
							  1/2.54 *				/* _hoops_IPIHH _hoops_RIR _hoops_SPIHH */
							  1.0001) /				/* (_hoops_GIRR _hoops_GH _hoops_IRS _hoops_SCIGGR) */
						dc->current._hoops_HAP.y; /* _hoops_ASPA _hoops_RIR _hoops_SRPGH */

				switch (_hoops_GCHIH->_hoops_SSSGP) {
					case GFN_SANS_SERIF:
					case GFN_TYPEWRITER:
					case GFN_ROMAN:
					case GFN_STROKED:
					case GFN_SYSTEM_DEFAULT: {
						instance = dc->_hoops_RRHGH[_hoops_GCHIH->_hoops_SSSGP];

						if (instance == null) {
							instance = dc->_hoops_RRHGH[GFN_STROKED];

							if (instance == null)
								return false;
						}

						if (instance->family->_hoops_PCSSP) break;

						while (instance->_hoops_IGGGH < 0) {
							HD_Find_Font_Height (dc, instance);
							instance = dc->_hoops_RRHGH[_hoops_GCHIH->_hoops_SSSGP]; /* _hoops_HSPP _hoops_IAPR */
						}

						if (instance->_hoops_GGGGH == null) {
							result = (float)instance->_hoops_IGGGH * _hoops_HHP;
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%.1f", (void *)&result);
						}
						else { /* _hoops_RRI _hoops_HSAR _hoops_SPR */
							result = (float)instance->_hoops_IGGGH * _hoops_HHP;
							_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "(%.1f,", (void *)&result);
							_hoops_RGGA ((instance = instance->_hoops_GGGGH) == null) {
								result = (float)instance->_hoops_IGGGH * _hoops_HHP;
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%.1f,", (void *)&result);
							}

							if (_hoops_ASAPR != null) _hoops_ASAPR[-1] = ')'; /* _hoops_CCIH _hoops_CGHI */
						}
					}	break;

					case GFN_SPECIFIED: {
						_hoops_SHSSP const	*	_hoops_GSIGGR = null;
						_hoops_SHSSP const	*	next;
						int					length;
						char const *		_hoops_RPPA = _hoops_GCHIH->specified.text;
						int					count = _hoops_GCHIH->specified.length;
						int					_hoops_ARAHR = 0;

						_hoops_RGGA (--count < 0) _hoops_ARAHR += _hoops_SHPCR (*_hoops_RPPA), _hoops_RPPA++;
						next = dc->_hoops_GRHGH[_hoops_ARAHR & (_hoops_HHRSP - 1)];
						length = _hoops_GCHIH->specified.length;

						_hoops_PCCAR {
							if ((_hoops_GSIGGR = next) == null) break;
							next = _hoops_GSIGGR->_hoops_SSCAP;
							if (_hoops_IGGPA(_hoops_GSIGGR->name.text, _hoops_GCHIH->specified.text)) break;
						}

						/* _hoops_SARS'_hoops_RA _hoops_SSS _hoops_SCH --- _hoops_SSHRR */
						if (_hoops_GSIGGR == null) {
							/* _hoops_PSIIR? */
							break;
						}

						if (_hoops_GSIGGR->type == _hoops_RISSP) {
							instance = (Font_Instance const *)_hoops_GSIGGR;

							if (instance->_hoops_IGGGH < 0)
								HD_Find_Font_Height (dc, instance);

							if (!instance->_hoops_PRGGH && instance->_hoops_IGGGH != 0) {
								result = (float)instance->_hoops_IGGGH * _hoops_HHP;
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%.1f", (void *)&result);
							}
						}
						else {
							_hoops_RCSSP const* family = (_hoops_RCSSP const *)_hoops_GSIGGR;

							if (family->_hoops_PCSSP)
								break;

							instance = family->_hoops_ICSSP;

							while (instance->_hoops_IGGGH < 0) {
								HD_Find_Font_Height (dc, instance);
								instance = family->_hoops_ICSSP; /* _hoops_HSPP _hoops_IAPR */
							}

							if (instance->_hoops_SSSSP == null) {
								result = (float)instance->_hoops_IGGGH * _hoops_HHP;
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%.1f", (void *)&result);
							}
							else { /* _hoops_RRI _hoops_HSAR _hoops_SPR */
								result = (float)instance->_hoops_IGGGH * _hoops_HHP;
								_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "(%.1f,", (void *)&result);
								while ((instance = instance->_hoops_SSSSP) != null) {
									result = (float)instance->_hoops_IGGGH * _hoops_HHP;
									_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "%.1f,", (void *)&result);
								}

								if (_hoops_ASAPR != null) _hoops_ASAPR[-1] = ')'; /* _hoops_CCIH _hoops_CGHI */
							}
						}
					}
				}
			} break;

			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized family info request");
			}	break;
		}
		_hoops_APAI (HOOPS_WORLD->_hoops_HPHGI);
	}

	if (_hoops_ASAPR == null || (_hoops_ASAPR == _hoops_PSAPR && _hoops_GCHIH->_hoops_GHRSC == -1))
		HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW,
				"The return value didn't fit in the space provided");
	else {
		/* _hoops_GHHR _hoops_PRRP */
		if (_hoops_GCHIH->_hoops_GHRSC == -1)
			*_hoops_ASAPR = '\0';							/* _hoops_IHRPR _hoops_IAHA */
		else
			while (_hoops_ASAPR != _hoops_PSAPR) *_hoops_ASAPR++ = ' ';		/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */
	}

	return true;
}



/*
 * _hoops_RSIGGR _hoops_HCR _hoops_IIGR _hoops_RGR _hoops_RRGR _hoops_HRGR _hoops_HCHRC _hoops_HII _hoops_ASIGGR
 */

#if defined(FREETYPE)


GLOBAL_FUNCTION bool HD_Gather_Text_Outline (
	Display_Context alter *		dc,
	_hoops_PGHGH alter *	_hoops_GCHIH) {
#ifndef DISABLE_COMPUTE
	_hoops_CRCP const *				_hoops_SRCP = _hoops_GCHIH->context;
	Net_Rendition				nr;
	bool						_hoops_IA = true;
	Vector						scale;

	nr = Net_Rendition::Create(dc);

	if (_hoops_SRCP != null) {
		/* _hoops_RSRA _hoops_CAGH _hoops_RAGA */
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PRSIR)) {		/* _hoops_ARARH */
			Subsegment const *_hoops_GIPIA;

			while ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) {
				while (_hoops_GIPIA->next != null)
					_hoops_GIPIA = _hoops_GIPIA->next;
				if (_hoops_GIPIA->type != _hoops_IRCP)
					break;
				_hoops_SRCP = (_hoops_CRCP const *)_hoops_GIPIA;
			}
		}

		_hoops_IGARH (nr, _hoops_SRCP, true);
	}
	else {
		/* _hoops_CAGH _hoops_CRAA _hoops_CHIA */
		_hoops_CRCP const **	_hoops_RSRHH = _hoops_GCHIH->path;
		int					_hoops_CISAA = _hoops_GCHIH->_hoops_CISAA;
		bool				_hoops_RCRHH = true;

		while (_hoops_CISAA-- != 0) {
			_hoops_SRCP = *_hoops_RSRHH++;

			if (_hoops_SRCP->type != _hoops_IRCP)
				break;

			_hoops_IGARH (nr, _hoops_SRCP, _hoops_RCRHH);
			_hoops_RCRHH = false;
		}
	}
	//_hoops_PSIGGR (_hoops_SCII, _hoops_PHHIP, _hoops_IHPR);

	_hoops_IGCSR alter &		_hoops_HRCIR = nr->_hoops_SISI;

	/*
	 * _hoops_PS'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_RRP _hoops_PCCP _hoops_HHGPA, _hoops_PGAP _hoops_HRGR _hoops_PRHI _hoops_RGAR _hoops_CGPR _hoops_RH
	 * _hoops_HCGR _hoops_HRGR _hoops_GRRRI.
	 */
	_hoops_HRCIR->transform = FT_FULL;

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPHGI);
	if (_hoops_HRCIR->font == null)
		HD_Choose_Font (nr, _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR, _hoops_GCHIH->encoding, true);

	if (_hoops_HRCIR->font->family->_hoops_RRCSR != _hoops_SISSP) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "The requested font has no outline representation");

		_hoops_IA = false;
	}


#ifdef FREETYPE
	if (_hoops_HRCIR->font->family->_hoops_RRCSR == _hoops_SISSP) {
		if (!_hoops_HRCIR->font->_hoops_CGCSR && !HD_Load_Font (dc, _hoops_HRCIR->font)) {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					"Problems loading the requested font");

			_hoops_IA = false;
		}

		scale.x = scale.y = 1.0f / (float)_hoops_HRCIR->font->_hoops_ISISR;
		scale.z = 0.0f;

		HD_Gather_Freetype_Text (nr, _hoops_HRCIR->font,
								  _hoops_GCHIH->text.length, _hoops_GCHIH->text._hoops_IPPPP,
								  &scale, _hoops_GCHIH->encoding, _hoops_GCHIH);
	}
#endif


	_hoops_APAI (HOOPS_WORLD->_hoops_HPHGI);

	return _hoops_IA;
#else
	return false;
#endif
}

#else /* _hoops_HSIGGR*/

GLOBAL_FUNCTION bool HD_Gather_Text_Outline (
	Display_Context alter		*dc,
	_hoops_PGHGH alter		*_hoops_GCHIH) {

	_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
					   "The requested font has no outline representation");

	return false;
}

#endif

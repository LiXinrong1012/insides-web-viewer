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
 * $Id: obf_tmp.txt 1.49 2010-10-06 19:16:21 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hpserror.h"
#include "hversion.h"


#define _hoops_CSGHS				0
#define _hoops_SSGHS				1
#define _hoops_GGRHS			2
#define _hoops_RGRHS			3
#define _hoops_AGRHS			4
#define _hoops_PGRHS			5
#define _hoops_HGRHS		6


local const _hoops_IGRCR _hoops_IGRHS[] = {
	{_hoops_CSGHS,		_hoops_GRRCR ("unknown request"),		_hoops_RRRCR, 0, false},
	{_hoops_SSGHS,		_hoops_GRRCR ("version"),				_hoops_RRRCR, 0, false},
	{_hoops_SSGHS,		_hoops_GRRCR ("hoops version"),			_hoops_RRRCR, 0, false},
	{_hoops_GGRHS,	_hoops_GRRCR ("a.i.r. present"),		_hoops_RRRCR, 0, false},
	{_hoops_RGRHS,	_hoops_GRRCR ("a.i.r. version"),		_hoops_RRRCR, 0, false},
	{_hoops_AGRHS,	_hoops_GRRCR ("i.m. present"),			_hoops_RRRCR, 0, false},
	{_hoops_PGRHS,	_hoops_GRRCR ("i.m. version"),			_hoops_RRRCR, 0, false},
	{_hoops_HGRHS, _hoops_GRRCR ("kanji present"),			_hoops_RRRCR, 0, false},
};


local void _hoops_CGRHS (
	char			*data,
	int				_hoops_IHCIH,
	int				version,
	int				sub,
	bool		beta) {
	int				major = version / 100;
	int				minor = version % 100;
	char			_hoops_GPIGR[32];

	Sprintf_DD (_hoops_GPIGR, minor < 10 ? "%d.0%d" : "%d.%d", major, minor);
	if (sub > 0) {
		char	temp[32];

		Sprintf_D (temp, "-%d", sub);
		_hoops_HPRPR (temp, _hoops_GPIGR);
	}
	if (beta)
		_hoops_HPRPR ("B", _hoops_GPIGR);

	HI_Return_Chars (data, _hoops_IHCIH, _hoops_GPIGR, _hoops_SSGR (_hoops_GPIGR));
}

HC_INTERFACE void HC_CDECL HC_Show_System_Info (
	char const *		item,
	char *				data) 
{
	_hoops_PAPPR context("Show_System_Info");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_System_Info () */\n");
	);

	_hoops_HIACR (_hoops_AIRGI, _hoops_IGRHS);

	Option_Value *option_list;

	if (!HI_Parse_Options (context, item, _hoops_CIACR (_hoops_AIRGI), &option_list, _hoops_SIACR))
		return;

	if (option_list->next != null) {
		HE_ERROR (HEC_HOOPS_SYSTEM, HES_ONE_INFO_ITEM_ONLY, "Only one info item at a time, please");
		HI_Free_Option_List (context, option_list);
		return;
	}

	switch (option_list->type->id) {
		case _hoops_CSGHS:
			HI_Return_Chars (data, -1, "unknown request", 15);
			break;

		case _hoops_SSGHS:
			HI_HOOPS_Version (data, -1);
			break;

		case _hoops_GGRHS:
			HI_Return_Chars (data, -1, "no", 2);
			break;

		case _hoops_RGRHS:
			HI_Return_Chars (data, -1, "none", 2);
			break;

		case _hoops_AGRHS:
			HI_Return_Chars (data, -1, "yes", 3);
			break;

		case _hoops_PGRHS:
			HI_Return_Chars (data, -1, "I.M. 3.00-1", 11);
			break;

		case _hoops_HGRHS:
			HI_Return_Chars (data, -1, "yes", 3);
			break;
	}

	HI_Free_Option_List (context, option_list);
}




#define _hoops_SGRHS	56		/* _hoops_SPCC _hoops_IIGR _hoops_APGR */

local void _hoops_GRRHS (
	char const		*string,
	char			*buffer) {
	int				_hoops_HGHGA;
	int				count;
	char const		*in = string;
	char			*_hoops_PAGR = buffer;

	*_hoops_PAGR++ = '*';	 *_hoops_PAGR++ = '*';	  *_hoops_PAGR++ = ' ';

	_hoops_HGHGA = _hoops_SGRHS - 6 - _hoops_SSGR (string);
	if (_hoops_HGHGA < 0) _hoops_HGHGA = 0;
	count = _hoops_HGHGA / 2;
	_hoops_HGHGA -= count;
	while (count-- > 0) *_hoops_PAGR++ = ' ';

	if (*in != '\0') do *_hoops_PAGR++ = *in++; _hoops_RGGA (*in == '\0');

	count = _hoops_HGHGA;
	while (count-- > 0) *_hoops_PAGR++ = ' ';

	*_hoops_PAGR++ = ' ';	 *_hoops_PAGR++ = '*';	  *_hoops_PAGR++ = '*';	   *_hoops_PAGR++ = '\0';
}



local void _hoops_RRRHS (
	char const		*name,
	int				version,
	int				sub,
	bool		beta,
	char			*buffer) {
	char			_hoops_GPIGR[MAX_ERRMSG];
	char			temp[MAX_ERRMSG];
	int				major = version / 100;
	int				minor = version % 100;

	Sprintf_DD (_hoops_GPIGR, minor < 10 ? ", Version %d.0%d" :
								  ", Version %d.%d", major, minor);
	_hoops_AAHR (name, temp);
	_hoops_HPRPR (_hoops_GPIGR, temp);

	if (sub > 0) {
		Sprintf_D (_hoops_GPIGR, "-%d", sub);
		_hoops_HPRPR (_hoops_GPIGR, temp);
	}
	if (beta)
		_hoops_HPRPR (" (Beta Test)", temp);

	_hoops_GRRHS (temp, buffer);
}


local void _hoops_ARRHS (
	char const		*_hoops_IRGAS,
	char			*buffer) {

	if (_hoops_SSGR (_hoops_IRGAS) > HK_PLATFORM_LEN) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Platform ID string (hoops.h) is too long");
		_hoops_GRRHS ("defined string too long", buffer);
	}
	else {
		char			temp[MAX_ERRMSG];

		Sprintf_S (temp, "for %s", _hoops_IRGAS);
		_hoops_GRRHS (temp, buffer);
	}
}

local void _hoops_PRRHS (
	char    *_hoops_HRRHS) {

	_hoops_RRRHS ("This is HOOPS", HOOPS_VERSION, HOOPS_SUBVERSION, BETA_TEST, _hoops_HRRHS);
}


GLOBAL_FUNCTION void HI_HOOPS_Version (
	char *	data,
	int     _hoops_IHCIH) {

	_hoops_CGRHS (data, _hoops_IHCIH,HOOPS_VERSION, HOOPS_SUBVERSION, BETA_TEST);
}




local const		char
 _hoops_IRRHS[] =	"**			   Copyright (c) 1998-2010 by          **",
 address[] =	"**	   Tech Soft 3D, LLC, Berkeley, California	   **";


HC_INTERFACE void HC_CDECL HC_Print_Version (void) 
{
	/* _hoops_ARPP _hoops_HAPPR _hoops_GPP _hoops_AHAR */
	HOOPS_WORLD->_hoops_PAHGI = false;	

	_hoops_PAPPR context("Print_Version");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Print_Version ();\n");
	);

	char			hoops[MAX_ERRMSG];
	char			_hoops_IRGAS[MAX_ERRMSG];
	char const		*strings[32];
	int				_hoops_CRRHS = 0;

	_hoops_PRRHS (hoops);
	strings[_hoops_CRRHS++] = hoops;

	_hoops_ARRHS (HK_PLATFORM, _hoops_IRGAS);
	strings[_hoops_CRRHS++] = _hoops_IRGAS;

	strings[_hoops_CRRHS++] = _hoops_IRRHS;
	strings[_hoops_CRRHS++] = address;

	/* _hoops_SRRHS == 0 */
	HI_Generate_Error (null, HEC_DEBUG, HES_PRINT_VERSION_MESSAGE, 0, _hoops_CRRHS, strings);
}



HC_INTERFACE bool HC_CDECL HC_Show_Environment (
	char const *		type,
	char *				value) 
{
	_hoops_PAPPR context("Show_Environment");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Environment () */\n");
	);

	_hoops_HCRPR		_hoops_GARHS;
	bool		_hoops_IA = false;

	if (HI_Show_Environment (type, &_hoops_GARHS)) {
		HI_Return_Chars (value, -1, _hoops_GARHS.text, _hoops_GARHS.length);
		_hoops_RGAIR (_hoops_GARHS);
		_hoops_IA = true;
	}

	return _hoops_IA;
}


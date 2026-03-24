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
 * $Id: obf_tmp.txt 1.57 2010-08-03 23:51:11 jason Exp $
 */

#include "hoops.h"
#include "hpserror.h"
#include "database.h"
#include "please.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"



local void _hoops_PPGHS (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_CRCP *					_hoops_SRCP,
	char const *				item,
	char *						data,
	int							_hoops_IHCIH) {
	_hoops_GGAGR *						_hoops_GHRI;
	_hoops_APRHH			_hoops_PPRHH;
	local	_hoops_SRHSR			_hoops_PIGSA = _hoops_GRRCR ("exists"),
								_hoops_GCSPP = _hoops_GRRCR ("started"),
								_hoops_HPGHS = _hoops_GRRCR ("alive"),
								_hoops_RAAPH = _hoops_GRRCR ("update needed");
	local	const char			_hoops_HPRHH[] = {"yes"},
								no[] = {"no"};

	_hoops_CSPPR();

	if ((_hoops_GHRI = (_hoops_GGAGR *)_hoops_SRCP->_hoops_IPPGR) != null) {
		while (_hoops_GHRI->type != HK_DRIVER)
			if ((_hoops_GHRI = (_hoops_GGAGR *)_hoops_GHRI->next) == null) 
				break;
	}

	HI_Canonize_Chars (item, &_hoops_PPRHH.item);

	/* _hoops_CACH _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_IRS "_hoops_HPHR" _hoops_SISS... */
	if (_hoops_GHRI != null && _hoops_GHRI->connected_action == _hoops_GHRI->action) 
		_hoops_GHRI = null;

	if (_hoops_RAHSR (_hoops_PPRHH.item, _hoops_PIGSA)) {
		if (_hoops_GHRI != null)
			HI_Return_Chars (data, _hoops_IHCIH, _hoops_HPRHH, 3);
		else
			HI_Return_Chars (data, _hoops_IHCIH, no, 2);
	}
	else if (_hoops_RAHSR (_hoops_PPRHH.item, _hoops_RAAPH)) {
		if (_hoops_SRCP->_hoops_CPGPR != 0)
			HI_Return_Chars (data, _hoops_IHCIH, _hoops_HPRHH, 3);
		else
			HI_Return_Chars (data, _hoops_IHCIH, no, 2);
	}
	else {
		if (_hoops_GHRI == null) {
			HE_WARNING (HEC_INVALID_INPUT, HES_DRIVER, 
						Sprintf_SS (null, "\"%s\" doesn't exist.  Is \"%s\" a driver segment?", 
									item, _hoops_SRCP->name.text));
			HI_Return_Chars (data, _hoops_IHCIH, null, 0);
		}
		else if (_hoops_RAHSR (_hoops_PPRHH.item, _hoops_GCSPP)) {
			if (ANYBIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_SGPIR))
				HI_Return_Chars (data, _hoops_IHCIH, _hoops_HPRHH, 3);
			else
				HI_Return_Chars (data, _hoops_IHCIH, no, 2);
		}
		else if (_hoops_RAHSR (_hoops_PPRHH.item, _hoops_HPGHS)) {
			if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA) && !BIT(_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR))
				HI_Return_Chars (data, _hoops_IHCIH, _hoops_HPRHH, 3);
			else
				HI_Return_Chars (data, _hoops_IHCIH, no, 2);
		}
		else {
			if (!ANYBIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_SGPIR))
				HI_Initialize_Actor (_hoops_RIGC, _hoops_GHRI);

			if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA)) {
				if (_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_CAGSC, &_hoops_PPRHH)) {
					HI_Return_Chars (data, _hoops_IHCIH, _hoops_PPRHH.data.text, _hoops_PPRHH.data.length);
					_hoops_RGAIR (_hoops_PPRHH.data);
				}
				else {
					HE_WARNING (HEC_INVALID_INPUT, HES_DRIVER, 
								Sprintf_SS (null, "\"%s\" couldn't gather device info.  Is \"%s\" a driver segment?", 
											item, _hoops_SRCP->name.text));
					HI_Return_Chars (data, _hoops_IHCIH, null, 0);
				}
			}
		}
	}

	_hoops_IRRPR();

	_hoops_RGAIR (_hoops_PPRHH.item);
}




HC_INTERFACE void HC_CDECL HC_Show_Device_Info (
	char const *		_hoops_IPGHS,
	char const *		item,
	char *				data) 
{
	_hoops_PAPPR context("Show_Device_Info");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Device_Info () */\n");
	);

	_hoops_CSPPR();

	_hoops_CRCP *	_hoops_SRCP;

	/* (_hoops_AGGAH _hoops_RCPH _hoops_CPGHS; _hoops_SCH _hoops_SPGHS _hoops_IS _hoops_HSPP _hoops_RH _hoops_SISS _hoops_PAR _hoops_HPPPR) */
	if ((_hoops_SRCP = HI_One_Segment_Search (context, _hoops_IPGHS, true)) != null) 
		_hoops_PPGHS (context, _hoops_SRCP, item, data, -1);

	_hoops_IRRPR();
}




HC_INTERFACE void HC_CDECL HC_Show_Device_Info_By_Key (
	Key					key,
	char const *		item,
	char *				data) 
{
	_hoops_PAPPR context("Show_Device_Info_By_Key");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Device_Info_By_Key () */\n");
	);

	_hoops_CSPPR();
	
	_hoops_HPAH *	_hoops_CISIR = (_hoops_HPAH *)_hoops_RCSSR (context, key);

	if (_hoops_CISIR == null ||
		BIT (_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR) ||
		_hoops_CISIR->type != _hoops_IRCP) {
		HE_ERROR (HEC_MISC, HES_INVALID_KEY, "Key does not refer to a valid driver segment");
	}
	else {
		_hoops_PPGHS (context, (_hoops_CRCP *)_hoops_CISIR, item, data, -1);
	}

	_hoops_IRRPR();
}


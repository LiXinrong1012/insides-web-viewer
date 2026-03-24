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
 * $Id: obf_tmp.txt 1.16 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "searchh.h"
#include "hpserror.h"
#include "patterns.h"
#include "driver.h"
#include "hd_proto.h"



GLOBAL_FUNCTION _hoops_GPAIR HD_Find_Named_Style (
	_hoops_RIGIP const &	_hoops_AIGIP,
	const char *					_hoops_HSIHH,
	_hoops_HCRPR const *					_hoops_PACSR,
	Integer32						key,
	bool							error) {
	_hoops_GPAIR						_hoops_SGAIR;
	_hoops_HCRPR							_hoops_PGGIH;
	_hoops_HCRPR const *					name;

	_hoops_HGGIH(_hoops_PGGIH);

	if (!_hoops_PACSR) {
		name = &_hoops_PGGIH;
		HI_Canonize_Chars(_hoops_HSIHH, &_hoops_PGGIH);
	}
	else
		name = _hoops_PACSR;

	if (!key)
		_hoops_HCARA(*name, key);

	for (int i=0; i<_hoops_AIGIP->count; ++i) {
		if (_hoops_AIGIP->keys[i] == key && _hoops_RAHSR(*name, _hoops_AIGIP->_hoops_SAAIR[i]->name)) {
			_hoops_SGAIR = _hoops_AIGIP->_hoops_SAAIR[i];
			break;
		}
	}
	if (!_hoops_SGAIR && error) {
		HE_WARNING (HEC_STYLE, HES_NOT_AVAILABLE,
			Sprintf_N (null, "Requested named style '%n' not found", name));
	}

	if (!_hoops_PACSR)
		_hoops_RGAIR(_hoops_PGGIH);

	return _hoops_SGAIR;
}

#ifndef _hoops_GASSI
local Attribute * _hoops_RASSI (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH alter *		item,
	Attribute const *		_hoops_AASSI,
	Attribute alter *		_hoops_PASSI)
{
	_hoops_IAAIR const *	_hoops_CRGIH = (_hoops_IAAIR const *)_hoops_AASSI;
	_hoops_IAAIR alter *	_hoops_SRGIH = (_hoops_IAAIR alter *)_hoops_PASSI;

	UNREFERENCED (item);
	UNREFERENCED (_hoops_RIGC);


	ASSERT(_hoops_SRGIH->count == 1);

	if (_hoops_CRGIH) {
		for (int i=0; i<_hoops_CRGIH->count; i++) {
			if (_hoops_CRGIH->keys[i] == _hoops_SRGIH->keys[0] &&
				_hoops_RAHSR(_hoops_SRGIH->_hoops_SAAIR[0]->name, _hoops_CRGIH->_hoops_SAAIR[i]->name)) {
				/* _hoops_IIIAA _hoops_PPR _hoops_SRAI */
				_hoops_PGRCA(_hoops_CRGIH)->_hoops_SAAIR[i] = _hoops_SRGIH->_hoops_SAAIR[0];

				_hoops_SRGIH->_hoops_SAAIR[0].release();
				FREE_ARRAY(_hoops_SRGIH->_hoops_SAAIR, 1, _hoops_GPAIR);
				FREE_ARRAY(_hoops_SRGIH->keys, 1, Integer32);

				_hoops_SRGIH->_hoops_SAAIR = _hoops_CRGIH->_hoops_SAAIR;
				_hoops_SRGIH->keys = _hoops_CRGIH->keys;
				_hoops_SRGIH->count = _hoops_CRGIH->count;

				_hoops_PGRCA(_hoops_CRGIH)->_hoops_SAAIR = null;
				_hoops_PGRCA(_hoops_CRGIH)->keys = null;
				_hoops_PGRCA(_hoops_CRGIH)->count = 0;

				return _hoops_SRGIH;
			}
		}

		// _hoops_HASC
		if (_hoops_CRGIH->count > 0) {
			int	count = _hoops_CRGIH->count+1;

			_hoops_GPAIR *	_hoops_SAAIR;
			ZALLOC_ARRAY(_hoops_SAAIR, count, _hoops_GPAIR);

			Integer32 *	keys;
			ALLOC_ARRAY(keys, count, Integer32);

			_hoops_AIGA(_hoops_SRGIH->_hoops_SAAIR, 1, _hoops_GPAIR, _hoops_SAAIR);
			_hoops_AIGA(_hoops_SRGIH->keys, 1, Integer32, keys);
			FREE_ARRAY(_hoops_SRGIH->_hoops_SAAIR, 1, _hoops_GPAIR);
			FREE_ARRAY(_hoops_SRGIH->keys, 1, Integer32);

			// _hoops_RGR _hoops_HRGR _hoops_HIGIP
			_hoops_AIGA(_hoops_CRGIH->keys, _hoops_CRGIH->count, Integer32, &keys[1]);
			_hoops_AIGA(_hoops_CRGIH->_hoops_SAAIR, _hoops_CRGIH->count, _hoops_GPAIR, &_hoops_SAAIR[1]);
			FREE_ARRAY(_hoops_CRGIH->_hoops_SAAIR, _hoops_CRGIH->count, _hoops_GPAIR);
			FREE_ARRAY(_hoops_CRGIH->keys, _hoops_CRGIH->count, Integer32);
			_hoops_PGRCA(_hoops_CRGIH)->_hoops_SAAIR =null;
			_hoops_PGRCA(_hoops_CRGIH)->keys = null;
			_hoops_PGRCA(_hoops_CRGIH)->count = 0;

			_hoops_SRGIH->_hoops_SAAIR = _hoops_SAAIR;
			_hoops_SRGIH->keys = keys;
			_hoops_SRGIH->count = count;
		}
	}

	return _hoops_SRGIH;
}


local _hoops_GPAIR _hoops_HASSI (
	_hoops_HCRPR *			name,
	_hoops_CRCP *		segment) {

	_hoops_GPAIR _hoops_SGAIR = _hoops_GPAIR::Create();
	_hoops_SGAIR->segment = segment;
	_hoops_PRRH(segment);

	/*_hoops_SRAI _hoops_RSIRR*/
	_hoops_SGAIR->name.text = name->text;
	_hoops_SGAIR->name.length = name->length;
	name->text = null;
	name->length = 0;

	_hoops_HCARA(_hoops_SGAIR->name,_hoops_SGAIR->key);

	return _hoops_SGAIR;
}
#endif




GLOBAL_FUNCTION bool HI_Define_Named_Style (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH *				item,
	_hoops_IAAIR *		_hoops_SGGCH)
{
	return HI_Set_Attribute (_hoops_RIGC, item, _hoops_HAAIR, _hoops_RASSI, _hoops_SGGCH);
}

HC_INTERFACE void HC_CDECL HC_Define_Named_Style (
	char const *			style_name,
	char const *			style_segment_name)
{
	_hoops_PAPPR context("Define_Named_Style");

#ifdef _hoops_GASSI
	_hoops_IRPPR ("Named Style");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Define_Named_Style (%S, %S);}\n", style_name, style_segment_name));
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (style_name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_STYLE, HES_NULL_INPUT, "Named style name is blank or null");
		return;
	}

	_hoops_RPPPR();
	_hoops_CRCP * _hoops_IASSI = HI_One_Segment_Search (context, style_segment_name, true);

	if (_hoops_IASSI) {
		_hoops_GPAIR _hoops_SGAIR = _hoops_HASSI(&_hoops_CRPCR, _hoops_IASSI);

		if (_hoops_SGAIR) {
			bool				used = false;
			_hoops_IAAIR *	_hoops_SGGCH;
			ZALLOC (_hoops_SGGCH, _hoops_IAAIR);
			_hoops_SGGCH->count = 1;
			ZALLOC_ARRAY(_hoops_SGGCH->_hoops_SAAIR, 1, _hoops_GPAIR);
			ALLOC_ARRAY(_hoops_SGGCH->keys, 1, Integer32);

			_hoops_SGGCH->_hoops_SAAIR[0] = _hoops_SGAIR;
			_hoops_SGGCH->keys[0] = _hoops_SGAIR->key;

			_hoops_HPAH * target;
			if ((target = HI_Find_Target_And_Lock(context, _hoops_SHRPP)) != null) {
				used = HI_Define_Named_Style (context, target, _hoops_SGGCH);
				_hoops_IRRPR();
			}

			if (!used) {
				FREE_ARRAY(_hoops_SGGCH->_hoops_SAAIR, 1, _hoops_GPAIR);
				FREE_ARRAY(_hoops_SGGCH->keys, 1, Integer32);
				FREE (_hoops_SGGCH, _hoops_IAAIR);
			}
		}
	}

	_hoops_IRRPR();

	_hoops_RGAIR(_hoops_CRPCR);
#endif
}


GLOBAL_FUNCTION void HI_Undefine_Named_Style(
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_HPAH const *		item,
	_hoops_HCRPR const &			_hoops_CRPCR)
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_IAAIR * _hoops_SAHCA = (_hoops_IAAIR*) HI_Find_Attribute(_hoops_RIGC, item, -_hoops_HAAIR);

	if (!_hoops_SAHCA) {
		HE_ERROR (HEC_STYLE, HES_INVALID_INPUT, "No Named_Style definitions found");
		goto _hoops_PRSPR;
	}

	Integer32	key;
	_hoops_HCARA(_hoops_CRPCR,key);

	for (int i=0; i<_hoops_SAHCA->count; ++i) {
		if (_hoops_SAHCA->keys[i] == key && _hoops_RAHSR(_hoops_CRPCR, _hoops_SAHCA->_hoops_SAAIR[i]->name)) {
			_hoops_SAHCA->_hoops_SAAIR[i] = null;

			if (_hoops_SAHCA->count == 1) {
				FREE_ARRAY(_hoops_SAHCA->_hoops_SAAIR, 1, _hoops_GPAIR);
				FREE_ARRAY(_hoops_SAHCA->keys, 1, Integer32);
				_hoops_SAHCA->_hoops_SAAIR = null;
				_hoops_SAHCA->keys = null;
				_hoops_SAHCA->count = 0;
			}
			else {
				_hoops_GPAIR *	_hoops_GIGIP;
				Integer32 *		new_keys;
				int				_hoops_RGCCA;

				_hoops_RGCCA = _hoops_SAHCA->count-1;

				ZALLOC_ARRAY(_hoops_GIGIP, _hoops_RGCCA, _hoops_GPAIR);
				ALLOC_ARRAY(new_keys, _hoops_RGCCA, Integer32);

				if (i > 0) {
					_hoops_AIGA(_hoops_SAHCA->_hoops_SAAIR, i, _hoops_GPAIR, _hoops_GIGIP);
					_hoops_AIGA(_hoops_SAHCA->keys, i, Integer32, new_keys);
				}

				if (i < _hoops_RGCCA) {
					_hoops_AIGA(&_hoops_SAHCA->_hoops_SAAIR[i+1], _hoops_RGCCA-i, _hoops_GPAIR, &_hoops_GIGIP[i]);
					_hoops_AIGA(&_hoops_SAHCA->keys[i+1], _hoops_RGCCA-i, Integer32, &new_keys[i]);
				}

				FREE_ARRAY(_hoops_SAHCA->_hoops_SAAIR, _hoops_SAHCA->count, _hoops_GPAIR);
				FREE_ARRAY(_hoops_SAHCA->keys, _hoops_SAHCA->count, Integer32);

				_hoops_SAHCA->_hoops_SAAIR = _hoops_GIGIP;
				_hoops_SAHCA->keys = new_keys;
				_hoops_SAHCA->count = _hoops_RGCCA;
			}

			goto _hoops_PRSPR;
		}
	}

	HE_WARNING (HEC_STYLE, HES_INVALID_INPUT,
		Sprintf_N (null, "Named style '%n' not found ",&_hoops_CRPCR));

_hoops_PRSPR:
	if (_hoops_SAHCA)
		_hoops_HPRH(_hoops_SAHCA);
}

HC_INTERFACE void HC_CDECL HC_UnDefine_Named_Style (
	char const *			style_name)
{
	_hoops_PAPPR context("UnDefine_Named_Style");

#ifdef _hoops_GASSI
	_hoops_IRPPR ("Named Style");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnDefine_Named_Style (%S);\n", style_name));
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (style_name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_STYLE, HES_NULL_INPUT, "Named style name is blank or null");
		return;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_SHRPP)) != null) {
		HI_Undefine_Named_Style(context, target, _hoops_CRPCR);
		_hoops_IRRPR();
	}

	_hoops_RGAIR(_hoops_CRPCR);
#endif
}



HC_INTERFACE Key HC_CDECL HC_Show_Named_Style (char const * style_name, char *style_segment_name)
{
	_hoops_PAPPR context("Show_Named_Style");
	Key style_key = _hoops_SHSSR;

#ifdef _hoops_GASSI
	_hoops_IRPPR ("Named Style");
	return style_key;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Named_Style () */\n");
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (style_name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_STYLE, HES_NULL_INPUT, "Named style name is blank or null");
		return style_key;
	}

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_IGAPP)) != null) {

		_hoops_IAAIR *	_hoops_SAHCA;
		if ((_hoops_SAHCA = (_hoops_IAAIR *) HI_Find_Attribute(context, target, _hoops_HAAIR)) != null) {

			Integer32	key;
			_hoops_HCARA(_hoops_CRPCR,key);

			for (int i=0; i<_hoops_SAHCA->count; i++) {
				if (_hoops_SAHCA->keys[i] == key&& _hoops_RAHSR(_hoops_CRPCR, _hoops_SAHCA->_hoops_SAAIR[i]->name)) {
					_hoops_GPAIR	_hoops_SGAIR = _hoops_SAHCA->_hoops_SAAIR[i];
					_hoops_RAIGI(context, null, "%p", _hoops_SGAIR->segment);
					HI_Return_Chars (style_segment_name, -1, context->_hoops_RIPGI, _hoops_SSGR(context->_hoops_RIPGI));
					style_key = _hoops_SGAIR->segment->key;
					break;
				}
			}

			_hoops_HPRH(_hoops_SAHCA);
		}

		_hoops_IRRPR();
	}

	_hoops_RGAIR (_hoops_CRPCR);
	return style_key;
#endif
}


#ifndef DISABLE_SEARCH
#ifndef _hoops_GASSI
local void _hoops_CASSI(_hoops_AIGPR * _hoops_RIGC, _hoops_CRCP * _hoops_SRCP)
{
	_hoops_SSPPR *		_hoops_GGHPR;
	_hoops_AGHPR *		node;

	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = _hoops_RIGC->_hoops_SHPGI;
	_hoops_RIGC->_hoops_SHPGI = _hoops_GGHPR;

	if (_hoops_SRCP == null) {
		if (_hoops_RIGC->open_list != null && _hoops_RIGC->open_list->_hoops_GCRIR == _hoops_RCRIR ||
			HI_Find_Our_Open (_hoops_RIGC)) {

			if (_hoops_RIGC->open_list->_hoops_GCRIR == _hoops_RCRIR)
				_hoops_SRCP = _hoops_RIGC->open_list->info.segment._hoops_IGRPR;
			else {
				HE_ERROR (HEC_STYLE, HES_NO_OPEN_SEGMENT, "Named styles require open segment");
				return;
			}
		}
		else {
			HE_ERROR (HEC_STYLE, HES_NO_OPEN_SEGMENT, "Named styles require open segment, none can be found");
			return;
		}
	}

	_hoops_IAAIR * _hoops_SAHCA = (_hoops_IAAIR *) HI_Find_Attribute (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, -_hoops_HAAIR);

	if (_hoops_SAHCA) {
		for (int i=0; i<_hoops_SAHCA->count; ++i) {
			_hoops_GPAIR *		_hoops_SGAIR;

			ZALLOC (_hoops_SGAIR, _hoops_GPAIR);
			*_hoops_SGAIR = _hoops_SAHCA->_hoops_SAAIR[i];

			ZALLOC (node, _hoops_AGHPR);
			node->next = _hoops_GGHPR->list;
			_hoops_GGHPR->list = node;
			node->item = (_hoops_HPAH *)_hoops_SGAIR;
			++_hoops_GGHPR->count;
		}

		_hoops_HPRH(_hoops_SAHCA);
	}
}
#endif
#endif


HC_INTERFACE void HC_CDECL HC_Begin_Named_Style_Search (void) {
	_hoops_PAPPR context("Begin_Named_Style_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_GASSI
	_hoops_IRPPR ("Named Style");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Named_Style_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_CSPPR();
	_hoops_CASSI(context, null);
	_hoops_IRRPR();

#endif
#endif
}


HC_INTERFACE bool HC_CDECL HC_Find_Named_Style (
	char *					style_name) {
	_hoops_PAPPR context("Find_Named_Style");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_GASSI
	_hoops_IRPPR ("Named Style");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Named_Style () */\n");
	);

	if (context->_hoops_SHPGI == null) {
		HE_ERROR (HEC_STYLE, HES_INACTIVE_SEARCH, "No named style search is active");
		return false;
	}

	_hoops_AGHPR	*	list;

	if ((list = context->_hoops_SHPGI->list) != null) {
		_hoops_GPAIR *		item = (_hoops_GPAIR *)list->item;

		context->_hoops_SHPGI->list = list->next;
		FREE (list, _hoops_AGHPR);
		list = context->_hoops_SHPGI->list;

		HI_Return_Sprintf1 (style_name, -1, "%n", (void *)&(*item)->name);

		*item = null;
		FREE (item, _hoops_GPAIR);

		return true;
	}
#endif
#endif

	return false;
}


HC_INTERFACE void HC_CDECL HC_Show_Named_Style_Count (
	int *					count) {
	_hoops_PAPPR context("Show_Named_Style_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_GASSI
	_hoops_IRPPR ("Named Style");
	*count = 0;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Named_Style_Count () */\n");
	);

	_hoops_SSPPR * _hoops_GGHPR = context->_hoops_SHPGI;
	if (_hoops_GGHPR == null) {
		*count = 0;
		HE_ERROR (HEC_STYLE, HES_INACTIVE_SEARCH, "No named style search is active");
	}
	else
		*count = _hoops_GGHPR->count;
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Named_Style_Search (void) {

	_hoops_PAPPR context("End_Named_Style_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
#ifdef _hoops_GASSI
	_hoops_IRPPR ("Named Style");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Named_Style_Search () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_SHPGI;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_STYLE, HES_END_WITHOUT_BEGIN_SEARCH, "End without Begin");
		return;
	}

	_hoops_AGHPR *	node = _hoops_GGHPR->list;

	while (node != null) {
		_hoops_AGHPR *	_hoops_CAGIH = node->next;
		_hoops_GPAIR *	item = (_hoops_GPAIR *) node->item;
		*item = null;
		FREE (item, _hoops_GPAIR);
		FREE (node, _hoops_AGHPR);
		node = _hoops_CAGIH;
	}
	context->_hoops_SHPGI = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
#endif
}


HC_INTERFACE Key HC_CDECL HC_PShow_Net_Named_Style (
	int						count,
	Key const *				keys,
	char const *			style_name,
	char *					style_segment_name) 
{
	_hoops_PAPPR context("PShow_Net_Named_Style");
	Key style_key = _hoops_SHSSR;

#ifdef _hoops_GASSI
	_hoops_IRPPR ("Named_Style");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Named_Style () */\n");
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (style_name, &_hoops_CRPCR);

	if (_hoops_CRPCR.length == 0) {
		HE_ERROR (HEC_STYLE, HES_NULL_INPUT, "Named style name is blank or null");
		return style_key;
	}

	_hoops_IAAIR *	_hoops_SAHCA;

	if ((_hoops_SAHCA = (_hoops_IAAIR *) HI_Find_Attribute_And_Lock(context, _hoops_IGAPP, _hoops_HRPCR, count, keys)) != null) {

		Integer32	key;
		_hoops_HCARA(_hoops_CRPCR,key);

		for (int i=0; i<_hoops_SAHCA->count; i++) {
			if (_hoops_SAHCA->keys[i] == key&& _hoops_RAHSR(_hoops_CRPCR, _hoops_SAHCA->_hoops_SAAIR[i]->name)) {
				_hoops_GPAIR	_hoops_SGAIR = _hoops_SAHCA->_hoops_SAAIR[i];
				_hoops_RAIGI(context, null, "%p", _hoops_SGAIR->segment);
				HI_Return_Chars (style_segment_name, -1, context->_hoops_RIPGI, _hoops_SSGR(context->_hoops_RIPGI));
				style_key = _hoops_SGAIR->segment->key;
				break;
			}
		}

		_hoops_HPRH(_hoops_SAHCA);
		_hoops_IRRPR();
	}

	_hoops_RGAIR (_hoops_CRPCR);
#endif

	return style_key;
}


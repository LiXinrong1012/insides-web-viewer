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
 * $Id: obf_tmp.txt 1.68 2010-10-06 19:16:43 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "searchh.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "phedron.h"




GLOBAL_FUNCTION _hoops_CRCP * HI_One_Segment_Search (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	bool					required)
{
	_hoops_RSIIR(_hoops_RIGC);

	_hoops_CRCP * _hoops_SRCP = HI_Create_Segment (_hoops_RIGC, null, name, false);

	if (required && !_hoops_SRCP) {
		HE_ERROR (HEC_SEGMENT, HES_NONE_FOUND, Sprintf_S (null, "No segments named '%s' were found", name));
	}

	return _hoops_SRCP;
}


HC_INTERFACE void HC_CDECL HC_Show_Segment (
	Key			key,
	char *		pathname)
{
	_hoops_PAPPR context("Show_Segment");

#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Segment () */\n");
	);

	_hoops_CSPPR();
	_hoops_CRCP const	*_hoops_SRCP = (_hoops_CRCP const *)_hoops_RCSSR (context, key);
	if (_hoops_SRCP == null || (_hoops_SRCP->type != _hoops_IRCP && _hoops_SRCP->type != _hoops_PIRIR) ||
		BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Provided key does not refer to a valid segment");
	}
	else {
		if (_hoops_SRCP->type == _hoops_PIRIR)
			_hoops_SRCP = (_hoops_CRCP *)((_hoops_PGRPR *)_hoops_SRCP)->_hoops_IGRPR;
		HI_Return_Sprintf1 (pathname, -1, "%p", (void *)_hoops_SRCP);
	}
	_hoops_IRRPR();
#endif
}




#ifndef DISABLE_SEARCH

local void _hoops_AGPAS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info) {
	_hoops_AGHPR	***			_hoops_PGPAS = (_hoops_AGHPR ***)info;
	_hoops_AGHPR	*			node;

	ALLOC (node, _hoops_AGHPR);
	node->next = null;
	node->item = (_hoops_HPAH *)_hoops_SRCP;
	node->_hoops_AGRI = false;
	_hoops_PRRH (_hoops_SRCP);
	**_hoops_PGPAS = node;
	*_hoops_PGPAS = &node->next;
	++_hoops_RIGC->_hoops_AHPGI->count;
}

#endif


HC_INTERFACE void HC_CDECL HC_Begin_Segment_Search (
	char const *		segspec)
{
	_hoops_PAPPR context("Begin_Segment_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Segment_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_SSPPR *		_hoops_GGHPR;
	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = context->_hoops_AHPGI;
	context->_hoops_AHPGI = _hoops_GGHPR;

	_hoops_CSPPR();
	_hoops_AGHPR	**_hoops_ASRGR = &context->_hoops_AHPGI->list;
	HI_For_Each (context, segspec, false, _hoops_AGPAS, (void *)&_hoops_ASRGR);
	_hoops_IRRPR();
#endif
}

HC_INTERFACE bool HC_CDECL HC_Find_Segment (
	char alter *		pathname)
{
	_hoops_PAPPR context("Find_Segment");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Segment () */\n");
	);

	_hoops_AGHPR	*	list;

	if (context->_hoops_AHPGI == null) {
		HE_ERROR (HEC_SEGMENT, HES_INACTIVE_SEARCH, "No segment search is active");
		return false;
	}

	while ((list = context->_hoops_AHPGI->list) != null) {
		_hoops_HPAH *	item = list->item;

		context->_hoops_AHPGI->list = list->next;
		FREE (list, _hoops_AGHPR);

		if (BIT (item->_hoops_RRHH, _hoops_HGAGR))
			_hoops_HPRH (item);
		else {
			HI_Return_Sprintf1 (pathname, -1, "%p", (void *)item);
			_hoops_HPRH (item);
			return true;
		}
	}

#endif
	return false;
}


HC_INTERFACE void HC_CDECL HC_Show_Segment_Count (
	int *				count)
{
	_hoops_PAPPR context("Show_Segment_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Segment_Count () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_AHPGI;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_SEGMENT, HES_INACTIVE_SEARCH, "No segment search is active");
		*count = 0;
	}
	else
		*count = _hoops_GGHPR->count;
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Segment_Search (void)
{
	_hoops_PAPPR context("End_Segment_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Segment_Search () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_AHPGI;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_SEGMENT, HES_END_WITHOUT_BEGIN_SEARCH, "End without matching Begin");
		return;
	}

	HI_Free_Search_List (context, _hoops_GGHPR->list);

	context->_hoops_AHPGI = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
}




HC_INTERFACE void HC_CDECL HC_Begin_Open_Item_Search (void)
{
	_hoops_PAPPR context("Begin_Open_Item_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Open_Item_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_SSPPR *		_hoops_GGHPR;
	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = context->_hoops_PHPGI;
	context->_hoops_PHPGI = _hoops_GGHPR;

	_hoops_SIRIR *			_hoops_ASIIR = context->open_list;
	_hoops_AGHPR **		_hoops_ASRGR = &_hoops_GGHPR->list;
	while (_hoops_ASIIR != null) {
		++_hoops_GGHPR->count;
		_hoops_AGHPR *		node;
		ZALLOC (node, _hoops_AGHPR);
		node->item = (_hoops_HPAH *)_hoops_ASIIR;
		_hoops_PRRH (_hoops_ASIIR);
		*_hoops_ASRGR = node;
		_hoops_ASRGR = &node->next;
		_hoops_ASIIR = _hoops_ASIIR->next;
	}
#endif
}

local void _hoops_HGPAS (
	Polyhedron *		_hoops_IPRI,
	int					offset,
	int *				_hoops_PSHHC,
	int *				_hoops_HSHHC) {

	switch (_hoops_IPRI->type) {
		default: {
			HE_ERROR (HEC_EDGE, HES_INVALID_GEOMETY_OR_SEGMENT, "Not a shell or mesh");
		}	break;

		case _hoops_GSIP: {
			_hoops_AIHPR const *		_hoops_PIHPR = (_hoops_AIHPR const *)_hoops_IPRI;

			*_hoops_PSHHC = offset / 3;
			switch (offset % 3) {
				case 0:
					*_hoops_HSHHC = *_hoops_PSHHC+1;
					break;
				case 1:
					*_hoops_HSHHC = *_hoops_PSHHC + _hoops_PIHPR->columns;
					break;
				case 2:
					*_hoops_HSHHC = *_hoops_PSHHC + _hoops_PIHPR->columns-1;
			}
		}	break;

		case _hoops_SCIP: {
			Shell *					_hoops_SPHPR = (Shell *)_hoops_IPRI;
			_hoops_RHHPR *	_hoops_SRCPR;
			int						index = 0;

			if (_hoops_SPHPR->_hoops_GRCPR == null)
				HI_Create_Shell_Edges (_hoops_SPHPR, false);

			*_hoops_HSHHC = _hoops_SPHPR->_hoops_GRCPR[offset]._hoops_GIHPR;


			_hoops_SRCPR = _hoops_SPHPR->_hoops_HHHPR[index+1];

			while (_hoops_SRCPR - _hoops_SPHPR->_hoops_GRCPR <= offset) {
				_hoops_SRCPR	= _hoops_SPHPR->_hoops_HHHPR[++index+1];
			}

			*_hoops_PSHHC = index;
		}
	}
}



HC_INTERFACE bool HC_CDECL HC_Find_Open_Item (
	Key	 *					key,
	char *					type,
	int *					offset1,
	int *					offset2)
{
	_hoops_PAPPR context("Find_Open_Item");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
	return false;
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Open_Item () */\n");
	);

	if (context->_hoops_PHPGI == null) {
		HE_ERROR (HEC_SEGMENT, HES_INACTIVE_SEARCH, "No open item search is active");
		return false;
	}

	bool			result = false;
	_hoops_AGHPR	*	list;

	_hoops_CSPPR();

	while ((list = context->_hoops_PHPGI->list) != null) {
		_hoops_SIRIR const *	item = (_hoops_SIRIR const *)list->item;
		context->_hoops_PHPGI->list = list->next;
		FREE (list, _hoops_AGHPR);

		if (BIT (item->info._hoops_IPRI._hoops_IGRPR->_hoops_RRHH, _hoops_HGAGR))
			_hoops_HPRH (item);
		else {
			if (offset1 != null)
				*offset1 = -1;
			if (offset2 != null)
				*offset2 = -1;

			switch (item->_hoops_GCRIR) {
				case _hoops_HCRIR:
					HI_Return_Chars (type, -1, "geometry", 8);
					break;
				case _hoops_CCRIR:
					HI_Return_Chars (type, -1, "edge", 4);
					break;
				case _hoops_SCRIR:
					HI_Return_Chars (type, -1, "vertex", 6);
					break;
				case _hoops_ICRIR:
					HI_Return_Chars (type, -1, "face", 4);
					break;
				case _hoops_RCRIR:
					HI_Return_Chars (type, -1, "segment", 7);
					break;
				case _hoops_RSRIR:
					HI_Return_Chars (type, -1, "lod", 3);
					break;
				case _hoops_ASRIR:
					HI_Return_Chars (type, -1, "trim", 4);
					break;
				case _hoops_GSRIR:
					HI_Return_Chars (type, -1, "region", 6);
			}

			*key = item->info._hoops_IPRI._hoops_IGRPR->key;

			if (item->_hoops_GCRIR != _hoops_RCRIR && item->_hoops_GCRIR != _hoops_HCRIR) {
				if (offset1 != null)
					*offset1 = item->info._hoops_IPRI.offset;

				if (item->_hoops_GCRIR == _hoops_CCRIR && offset1 != null && offset2 != null) {
					_hoops_HGPAS ((Polyhedron *)item->info._hoops_IPRI._hoops_IGRPR,
						item->info._hoops_IPRI.offset, offset1, offset2);
				}
			}

			_hoops_HPRH (item);
			result = true;
			break;
		}
	}

	_hoops_IRRPR();

	return result;
#endif
}


HC_INTERFACE void HC_CDECL HC_Show_Open_Item_Count (
	int *					count)
{
	_hoops_PAPPR context("Show_Open_Item_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Open_Item_Count () */\n");
	);

	if (context->_hoops_PHPGI == null) {
		HE_ERROR (HEC_SEGMENT, HES_INACTIVE_SEARCH, "No open item search is active");
		*count = 0;
	}
	else
		*count = context->_hoops_PHPGI->count;
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Open_Item_Search (void)
{
	_hoops_PAPPR context("End_Open_Item_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Open_Item_Search () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_PHPGI;

	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_SEGMENT, HES_END_WITHOUT_BEGIN_SEARCH, "End without matching Begin");
		return;
	}

	HI_Free_Search_List (context, _hoops_GGHPR->list);

	context->_hoops_PHPGI = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
}



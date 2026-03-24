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
 * $Id: obf_tmp.txt 1.48 2010-11-30 21:53:27 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "searchh.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"



GLOBAL_FUNCTION void HI_Exit_Program () 
{
	CODE_GENERATION (
		HI_Finish_Code_Generation ();
	);
	HOOPS_WORLD->_hoops_PASAH = true;
	HI_Call_Exit_Handlers ();
	HI_Normal_Exit ();
}

HC_INTERFACE void HC_CDECL HC_Exit_Program (void) {
	if (HOOPS_WORLD) {
		HI_Set_Name ("Exit_Program");

		CODE_GENERATION (
			HI_Dump_Code ("HC_Exit_Program ();\n  return 0;\n}\n\n");

			HI_Finish_Code_Generation ();
		);
		HOOPS_WORLD->_hoops_PASAH = true;
		HI_Call_Exit_Handlers ();
	}

	HI_Normal_Exit ();
}

HC_INTERFACE void HC_CDECL HC_Abort_Program (
	char const *	_hoops_SSACR) 
{
	_hoops_PAPPR context("Abort_Program");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Abort_Program ();\n");
	);

	char const *	_hoops_RPPA = _hoops_SSACR;

	while (*_hoops_RPPA == ' ' || *_hoops_RPPA == '\t') ++_hoops_RPPA;

	if (*_hoops_RPPA == '\0')
		_hoops_HRAIR (HEC_FATAL_ERROR, HES_ABORT_REQUESTED_BY_APPLICATION, "Abort requested by application");
	else
		_hoops_RIHPH (HEC_FATAL_ERROR, HES_ABORT_REQUESTED_BY_APPLICATION, "Abort requested by application -", _hoops_SSACR);
}


HC_INTERFACE void HC_CDECL HC_Define_Exit_Handler (
	_hoops_IRPCR			iroutine) 
{
	_hoops_PAPPR context("Define_Exit_Handler");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Define_Exit_Handler () */\n");
	);

	_hoops_SPSAP	_hoops_APRPR = (_hoops_SPSAP)iroutine;
	if (_hoops_APRPR == 0) {
		HE_ERROR (HEC_EXIT_HANDLER, HES_NULL_INPUT,
			"Null value passed to Define_Exit_Handler");
		return;
	}

	_hoops_RPPPR();

	_hoops_SSHIR *	handler;
	if ((handler = HOOPS_WORLD->_hoops_AIHPH) != null) do {
		if (handler->_hoops_APRPR == _hoops_APRPR) {
			HE_WARNING (HEC_EXIT_HANDLER, HES_DUPLICATE_DEFINITION,
				"Attempted definition of duplicate exit handler");
			goto Release;
		}
	}
	_hoops_RGGA ((handler = handler->next) == null);

	ZALLOC (handler, _hoops_SSHIR);
	handler->_hoops_HIHI = 1;
	handler->type = _hoops_CSHIR;
	handler->owner = HOOPS_WORLD;
	handler->_hoops_APRPR = _hoops_APRPR;
	if ((handler->next = HOOPS_WORLD->_hoops_AIHPH) != null)
		HOOPS_WORLD->_hoops_AIHPH->backlink = &handler->next;
	HOOPS_WORLD->_hoops_AIHPH = handler;
	handler->backlink = &HOOPS_WORLD->_hoops_AIHPH;

Release:
	_hoops_IRRPR();
}



HC_INTERFACE void HC_CDECL HC_UnDefine_Exit_Handler (
	_hoops_IRPCR			iroutine) 
{
	_hoops_PAPPR context("UnDefine_Exit_Handler");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_UnDefine_Exit_Handler () */\n");
	);

	_hoops_SPSAP	_hoops_APRPR = (_hoops_SPSAP)iroutine;
	if (_hoops_APRPR == (_hoops_SPSAP)null) {
		HE_ERROR (HEC_EXIT_HANDLER, HES_NULL_INPUT, "Null value passed to UnDefine_Exit_Handler");
		return;
	}

	_hoops_RPPPR();

	_hoops_SSHIR *	handler;
	if ((handler = HOOPS_WORLD->_hoops_AIHPH) != null) do {
		if (handler->_hoops_APRPR == _hoops_APRPR) {
			HI_Generic_Delete (context, (_hoops_HPAH *)handler);
			_hoops_APRPR = (_hoops_SPSAP)null;
			break;
		}
	} _hoops_RGGA ((handler = handler->next) == null);
	_hoops_IRRPR();
	if (_hoops_APRPR == (_hoops_SPSAP)null)
		return;

#ifdef WIN32_SYSTEM
	/*
	* _hoops_HPSHR _hoops_PSCSR _hoops_APSAH _hoops_CCA _hoops_IRS _hoops_ASCSR, _hoops_RH _hoops_GRGPR _hoops_IIGR
	* _hoops_PIHPH _hoops_HRGR _hoops_HAGH _hoops_GGR _hoops_RH _hoops_CCRPR
	* _hoops_HSAR _hoops_GGR _hoops_RH _hoops_ASCSR _hoops_SAPGP _hoops_IS _hoops_HPSAH. _hoops_PSPC, _hoops_CGPR _hoops_RH
	* _hoops_CCRPR _hoops_HHHH _hoops_RH _hoops_GRGPR _hoops_IIGR _hoops_PIHPH,
	* _hoops_SCH _hoops_RHAP _hoops_HAR _hoops_PSSP _hoops_PCPA _hoops_AGAH _hoops_GPHR _hoops_GGR _hoops_RH _hoops_HIGR
	* _hoops_IIGR _hoops_RIARR _hoops_IASAH. _hoops_CPGP _hoops_PIHPH _hoops_HRGR _hoops_RH
	* _hoops_RGAR _hoops_AGAH _hoops_CARSR _hoops_RIARR _hoops_HARPR (_hoops_HAS._hoops_IAS. _hoops_RH _hoops_RGAR
	* _hoops_SPR _hoops_GRPAA _hoops_GRGPR _hoops_GRS _hoops_HAR _hoops_PSSP), _hoops_SR _hoops_GRS _hoops_HPCAR
	* _hoops_SGS _hoops_PIHPH _hoops_CGH _hoops_SHH _hoops_RHSI _hoops_HII _hoops_RH
	* _hoops_IPRH _hoops_HARPR _hoops_HIGR _hoops_CGPR _hoops_SR _hoops_PAH'_hoops_RA _hoops_SSS _hoops_IRS _hoops_PSSP.
	*/
	_hoops_APRPR = (_hoops_SPSAP) &HC_Reset_System;
	_hoops_RPPPR();
	if ((handler = HOOPS_WORLD->_hoops_AIHPH) != null) do {
		if (handler->_hoops_APRPR == _hoops_APRPR) {
			HI_Generic_Delete (context,(_hoops_HPAH *)handler);
			_hoops_SGSPR (HEC_EXIT_HANDLER, HES_UNDEFINE_ERROR_HANDLER,
				"Exit handler not found - undefining HC_Reset_System");
			_hoops_APRPR = (_hoops_SPSAP)null;
			break;
		}
	} _hoops_RGGA ((handler = handler->next) == null);
	_hoops_IRRPR();
	if (_hoops_APRPR == (_hoops_SPSAP)null)
		return;
#endif /* _hoops_HIHPH */

	/* _hoops_RGAR _hoops_HGCR _hoops_ARI _hoops_RPP _hoops_RHAC _hoops_HSSC _hoops_RHIR _hoops_HCR _hoops_IIGR _hoops_RH _hoops_PIIHR _hoops_RGHS */
	HE_WARNING (HEC_EXIT_HANDLER, HES_UNDEFINE_EXIT_HANDLER,
		"Exit handler not found - can't undefine");
}



GLOBAL_FUNCTION void HI_Call_Exit_Handlers (void) 
{
	if (!HOOPS_WORLD) 
		return;

	_hoops_SSHIR		*_hoops_ARSAH;
	void (*_hoops_IIHPH)() = 0;

	if (!HOOPS_WORLD->_hoops_PASAH) {
		_hoops_IIHPH = HOOPS_WORLD->_hoops_CIHPH;
	}

	if ((_hoops_ARSAH = HOOPS_WORLD->_hoops_AIHPH) != null) {
		void	(HC_CDECL * _hoops_SIHPH[30]) (void);
		void	(HC_CDECL ** _hoops_SCGCR) (void) = _hoops_SIHPH;

		/* _hoops_GCHPH _hoops_CHR _hoops_PHRH _hoops_IS _hoops_RCHPH, _hoops_HIS _hoops_IPS _hoops_SIHC _hoops_IAPR */

		//_hoops_IISPP ("_hoops_AGGGR _hoops_IPSCP (_hoops_SGCRP)");

		_hoops_AIGPR *_hoops_RIGC;
		_hoops_IIRIR (_hoops_RIGC);

		HOOPS_WORLD->_hoops_ACHPH = true;

		do {
			if (_hoops_SCGCR < _hoops_SIHPH+_hoops_GGAPR(_hoops_SIHPH) - 1)
				*_hoops_SCGCR++ = _hoops_ARSAH->_hoops_APRPR;
			else {
				HE_WARNING (HEC_EXIT_HANDLER, HES_TOO_MANY_EXIT_HANDLERS, "Too many exit handlers");
				break;
			}

			_hoops_CIGPR (_hoops_RIGC,_hoops_ARSAH);
			_hoops_HPRH (_hoops_ARSAH);
		} _hoops_RGGA ((_hoops_ARSAH = HOOPS_WORLD->_hoops_AIHPH) == null);

		*_hoops_SCGCR = nullroutine;
		_hoops_SCGCR = _hoops_SIHPH;

		//_hoops_SHAPA(_hoops_HHAPA);
		_hoops_RGGA (*_hoops_SCGCR == nullroutine) {
			void	(HC_CDECL * _hoops_PCHPH)(void) = *_hoops_SCGCR++;
			(*_hoops_PCHPH)();
		}

		if (HOOPS_WORLD) {
			//_hoops_PIAPA(_hoops_HHAPA);

			if (HOOPS_WORLD->_hoops_AIHPH != null) {
				/*
				* _hoops_RCHPH _hoops_CGH _hoops_AIAH _hoops_HS _hoops_RPII _hoops_PCCP _hoops_RIARR _hoops_HARPR,
				* _hoops_HIH _hoops_SR _hoops_RIAGR _hoops_HAH _hoops_AHPH _hoops_HRARH _hoops_ARRS, _hoops_HIS _hoops_AGIIP _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_PIGS.
				*/
				HC_Reset_System ();
			}

			HOOPS_WORLD->_hoops_ACHPH = false;
		}
	}
	if (_hoops_IIHPH) _hoops_IIHPH();
}





HC_INTERFACE void HC_CDECL HC_Begin_Exit_Handler_Search (void) 
{
	_hoops_PAPPR context("Begin_Exit_Handler_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Exit_Handler_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_SSPPR *	_hoops_GGHPR;
	

	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = context->_hoops_HCHPH;
	context->_hoops_HCHPH = _hoops_GGHPR;

	_hoops_CSPPR();

	_hoops_SSHIR *	_hoops_ARSAH;
	if ((_hoops_ARSAH = HOOPS_WORLD->_hoops_AIHPH) != null) {
		_hoops_AGHPR **	_hoops_ASRGR = &_hoops_GGHPR->list;

		do {
			++_hoops_GGHPR->count;
			_hoops_AGHPR *	node;
			ZALLOC (node, _hoops_AGHPR);
			node->item = (_hoops_HPAH *)_hoops_ARSAH;
			_hoops_PRRH (_hoops_ARSAH);
			*_hoops_ASRGR = node;
			_hoops_ASRGR = &node->next;		
		} while ((_hoops_ARSAH = _hoops_ARSAH->next) != null);
	}

	_hoops_IRRPR();
#endif
}


HC_INTERFACE bool HC_CDECL HC_Find_Exit_Handler (
	_hoops_IRPCR *		address) 
{
	_hoops_PAPPR context("Find_Exit_Handler");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Exit_Handler () */\n");
	);

	if (context->_hoops_HCHPH == null) {
		HE_ERROR (HEC_EXIT_HANDLER, HES_INACTIVE_SEARCH, "No exit handler search is active");
		return false;
	}

	_hoops_AGHPR	*	list;

	while ((list = context->_hoops_HCHPH->list) != null) {
		_hoops_SSHIR *	_hoops_ARSAH = (_hoops_SSHIR *)list->item;

		context->_hoops_HCHPH->list = list->next;
		FREE (list, _hoops_AGHPR);

		/* _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_PGHPR */
		if (!BIT (_hoops_ARSAH->_hoops_RRHH, _hoops_HGAGR)) {
			*address = (_hoops_IRPCR)_hoops_ARSAH->_hoops_APRPR;
			_hoops_HPRH (_hoops_ARSAH);
			return true;
		}
		else
			_hoops_HPRH (_hoops_ARSAH);
	}
#endif
	return false;
}


HC_INTERFACE void HC_CDECL HC_Show_Exit_Handler_Count (
	int alter *				count) 
{	
	_hoops_PAPPR context("Show_Exit_Handler_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Exit_Handler_Count () */\n");
	);

	if (context->_hoops_HCHPH == null) {
		HE_ERROR (HEC_SEGMENT, HES_INACTIVE_SEARCH, "No error handler search is active");
		*count = 0;
	}
	else
		*count = context->_hoops_HCHPH->count;
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Exit_Handler_Search (void) 
{
	_hoops_PAPPR context("End_Exit_Handler_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Exit_Handler_Search () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_HCHPH;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_EXIT_HANDLER, HES_END_WITHOUT_BEGIN_SEARCH, "End without matching Begin");
		return;
	}

	HI_Free_Search_List (context, _hoops_GGHPR->list);

	context->_hoops_HCHPH = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
}

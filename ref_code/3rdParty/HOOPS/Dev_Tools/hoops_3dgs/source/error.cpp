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
 * $Id: obf_tmp.txt 1.79 2010-12-08 22:36:55 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "searchh.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

/* _hoops_SGH _hoops_RGSAH _hoops_HIH _hoops_AGSAH _hoops_ACSRR _hoops_GII _hoops_CGGC _hoops_IIGR _hoops_CGCGA _hoops_PCCP _hoops_PGSAH _hoops_GPSRR */
local void _hoops_HGSAH (
	char *			buffer,
	int				_hoops_RSIGR,
	char const *	string,
	int				_hoops_IGSAH) {

	if (_hoops_RSIGR == -1) {
		if (_hoops_IGSAH >= HOOPS_WORLD->_hoops_RAPPR)
			_hoops_IGSAH = HOOPS_WORLD->_hoops_RAPPR - 1;
	}
	else {
		if (_hoops_IGSAH > _hoops_RSIGR)
			_hoops_IGSAH = _hoops_RSIGR;
	}

	HI_Return_Chars (buffer, _hoops_RSIGR, string, _hoops_IGSAH);
}


HC_INTERFACE bool HC_CDECL HC_Show_Error (
	char *					severity,
	int *					category,
	int *					specific) 
{
	// _hoops_PAGA: _hoops_PSP _hoops_IISPP("_hoops_CGSAH") -- _hoops_SCH _hoops_CHH _hoops_SCAC _hoops_RH _hoops_PIH _hoops_SR _hoops_CHR _hoops_IRCC _hoops_IS _hoops_CCHGA,
	//		 _hoops_SR _hoops_GACC _hoops_PAH'_hoops_RA _hoops_CAHP _hoops_PCCP _hoops_RIHH _hoops_HII _hoops_ARI, _hoops_HIS _hoops_PSP _hoops_RRP _hoops_IS _hoops_PRIA _hoops_RH _hoops_RSIRR

	if (HOOPS_WORLD == null)	/* _hoops_IIP _hoops_AIS */
		return false;

	_hoops_AIGPR *_hoops_RIGC;
	_hoops_IIRIR (_hoops_RIGC);

	if (_hoops_RIGC->_hoops_SGSAH == -1)
		return false;

	if (severity != null) switch (_hoops_RIGC->_hoops_SGSAH) {
		case 0:		_hoops_HGSAH (severity, -1, "informational", 13);	break;
		case 1:		_hoops_HGSAH (severity, -1, "warning",		  7);	break;
		case 2:		_hoops_HGSAH (severity, -1, "error",		  5);	break;
		case 3:		_hoops_HGSAH (severity, -1, "fatal error",	 11);	break;
	}
	*category = _hoops_RIGC->_hoops_GRSAH;
	*specific = _hoops_RIGC->_hoops_RRSAH;

	return true;
}



GLOBAL_FUNCTION void HI_Generate_Untrappable_Error (
	_hoops_AIGPR *	_hoops_RIGC,
	int						category,
	int						specific,
	int						severity,
	int						msgc,
	char const **			msgv) 
{
	_hoops_RGIIR *			_hoops_ARSAH;
	char const **			_hoops_PRSAH;
	int						_hoops_HRSAH;
	Error_Mask				_hoops_IRSAH;
	bool					_hoops_CRSAH = false;

	if (!_hoops_RIGC)
		_hoops_IIRIR (_hoops_RIGC);

	_hoops_RIGC->_hoops_SGSAH = severity;
	_hoops_RIGC->_hoops_GRSAH = category;
	_hoops_RIGC->_hoops_RRSAH = specific;

	_hoops_IRSAH = HOOPS_WORLD->error_mask;
	HOOPS_WORLD->error_mask = 1<<8;	/* _hoops_HAR _hoops_IRS _hoops_GSSR _hoops_PISH _hoops_IGRH, _hoops_IS _hoops_RIP _hoops_SRSAH */

	*_hoops_RIGC->_hoops_CACAA = _hoops_RIGC->_hoops_RCSPP;
	_hoops_PRSAH = _hoops_RIGC->_hoops_SACAA;
	_hoops_HRSAH = _hoops_RIGC->_hoops_CACAA - _hoops_PRSAH + 1;

	if (_hoops_HRSAH >= 2 &&
		_hoops_RIGC->_hoops_CACAA[-1] ==
				_hoops_RIGC->_hoops_CACAA[-2])
		--_hoops_HRSAH;

	if (!HOOPS_WORLD->_hoops_GASAH) {
		HC_Report_Error (category, specific, severity,
						 msgc, msgv, _hoops_HRSAH, _hoops_PRSAH);
		HOOPS_WORLD->error_mask = _hoops_IRSAH;
		return;
	}

	if ((_hoops_ARSAH = HOOPS_WORLD->_hoops_RASAH) != null) {
		PUSHNAME(_hoops_RIGC);
		_hoops_AASAH(_hoops_RIGC, "Defined error handler (callback)");
			PUSHNAME(_hoops_RIGC);
			_hoops_RGIIR * next = 0;
			do {
				next = _hoops_ARSAH->next;
				if (_hoops_ARSAH->_hoops_APRPR == (_hoops_GHSAP)HC_Report_Error ||
					_hoops_ARSAH->_hoops_APRPR == (_hoops_GHSAP)HI_Pause_Errors)
					_hoops_CRSAH = true;
				_hoops_AASAH (_hoops_RIGC, "Error Handler");		/* _hoops_IRHH _hoops_RCRR _hoops_IH _hoops_GRR _hoops_AASA */
				(*_hoops_ARSAH->_hoops_APRPR) (category, specific, severity,
								msgc, msgv, _hoops_HRSAH, _hoops_PRSAH);
			} _hoops_RGGA ((_hoops_ARSAH = next) == null);
			POPNAME(_hoops_RIGC);
		POPNAME(_hoops_RIGC);
	}

	if (!_hoops_CRSAH) {
		PUSHNAME(_hoops_RIGC);
		HC_Report_Error (category, specific, severity,
						 msgc, msgv, _hoops_HRSAH, _hoops_PRSAH);
		POPNAME(_hoops_RIGC);
	}

	HOOPS_WORLD->error_mask = _hoops_IRSAH;

	if (severity == 3) {
		HOOPS_WORLD->_hoops_PASAH = true;
		HI_Call_Exit_Handlers ();
		HI_Error_Exit ();
	}

	if (HOOPS_WORLD->_hoops_RRGHP != 0 && HOOPS_WORLD->_hoops_ARGHP >= HOOPS_WORLD->_hoops_RRGHP)
		_hoops_HRAIR (HEC_FATAL_ERROR, HES_SYSTEM_OPTION_EXCEEDED,
				  "'Message limit' system option exceeded, program exit forced");
}


GLOBAL_FUNCTION void HI_Generate_Error (
	_hoops_AIGPR *	_hoops_RIGC,
	int						category,
	int						specific,
	int						severity,
	int						msgc,
	char const **			msgv) 
{
	_hoops_RGIIR *			_hoops_ARSAH;
	char const **			_hoops_PRSAH;
	int						_hoops_HRSAH;	
	bool					_hoops_HASAH = true;
	_hoops_CPSPP **		_hoops_ASRGR;

	if (!_hoops_RIGC)
		_hoops_IIRIR (_hoops_RIGC);

	_hoops_RIGC->_hoops_SGSAH = severity;
	_hoops_RIGC->_hoops_GRSAH = category;
	_hoops_RIGC->_hoops_RRSAH = specific;

	/* _hoops_SRS _hoops_CACH _hoops_RPP _hoops_SR _hoops_HHGC _hoops_IS _hoops_RHRRH _hoops_SCH */
	_hoops_ASRGR = HI_Lookup_Error_Control (&HOOPS_WORLD->_hoops_PSSPP[severity], category, specific);
	if (*_hoops_ASRGR != null) {
		if ((*_hoops_ASRGR)->state == _hoops_GCCPP)
			_hoops_HASAH = false;
	}
	else if (BIT (HOOPS_WORLD->error_mask, 1<<severity))
		_hoops_HASAH = false;

	/* _hoops_AASA _hoops_IASAH _hoops_RPP _hoops_SR _hoops_AA */
	if (_hoops_HASAH) {
		*_hoops_RIGC->_hoops_CACAA = _hoops_RIGC->_hoops_RCSPP;
		_hoops_PRSAH = _hoops_RIGC->_hoops_SACAA;
		_hoops_HRSAH = _hoops_RIGC->_hoops_CACAA - _hoops_PRSAH + 1;

		if (_hoops_HRSAH >= 2 &&
			_hoops_RIGC->_hoops_CACAA[-1] == _hoops_RIGC->_hoops_CACAA[-2])
			--_hoops_HRSAH;

		if (!HOOPS_WORLD->_hoops_GASAH) {
			HC_Report_Error (category, specific, severity, msgc, msgv, _hoops_HRSAH, _hoops_PRSAH);
			return;
		}

		if ((_hoops_ARSAH = HOOPS_WORLD->_hoops_RASAH) != null) {
			PUSHNAME(_hoops_RIGC);
			_hoops_AASAH(_hoops_RIGC, "Defined error handler (callback)");
				PUSHNAME(_hoops_RIGC);
				_hoops_RGIIR *		next = 0;
				bool				_hoops_CASAH = _hoops_RIGC->_hoops_GSHGH;

				_hoops_RIGC->_hoops_GSHGH = true;
				do {
					next = _hoops_ARSAH->next;
					_hoops_AASAH(_hoops_RIGC, "Error Handler");		/* _hoops_IRHH _hoops_RCRR _hoops_IH _hoops_GRR _hoops_AASA */
					(*_hoops_ARSAH->_hoops_APRPR) (category, specific, severity,
									msgc, msgv, _hoops_HRSAH, _hoops_PRSAH);
				} _hoops_RGGA ((_hoops_ARSAH = next) == null);
				_hoops_RIGC->_hoops_GSHGH = _hoops_CASAH;

				POPNAME(_hoops_RIGC);
			POPNAME(_hoops_RIGC);
		}

		if (severity > 0)
			++HOOPS_WORLD->_hoops_ARGHP;
	}

	/* _hoops_HPIRA _hoops_GH (_hoops_APHS _hoops_HIIA _hoops_GGR _hoops_AGIR _hoops_IRS _hoops_HARPR _hoops_IIAC _hoops_IRS _hoops_PIAP _hoops_AGRP) */
	_hoops_ASRGR = HI_Lookup_Error_Control (&HOOPS_WORLD->_hoops_PSSPP[severity], category, specific);
	if (*_hoops_ASRGR != null) {
		if ((*_hoops_ASRGR)->_hoops_GHSPP == _hoops_ACCPP) {
			if ((*_hoops_ASRGR)->state == _hoops_ACCPP)
				(*_hoops_ASRGR)->state = _hoops_GCCPP;
			else if ((*_hoops_ASRGR)->state == _hoops_RCCPP)	/* _hoops_ASSS _hoops_HARPR _hoops_IS _hoops_HIAP _hoops_RGR _hoops_IH _hoops_HPIH _hoops_GHIR */
				(*_hoops_ASRGR)->state = _hoops_ACCPP;
		}
	}

	if (severity == 3) {
		HOOPS_WORLD->_hoops_PASAH = true;
		HI_Call_Exit_Handlers ();
		HI_Error_Exit ();
	}

	if (HOOPS_WORLD->_hoops_RRGHP != 0 && HOOPS_WORLD->_hoops_ARGHP >= HOOPS_WORLD->_hoops_RRGHP)
		_hoops_HRAIR (HEC_FATAL_ERROR, HES_SYSTEM_OPTION_EXCEEDED,
				  "'Message limit' system option exceeded, program exit forced");
}


GLOBAL_FUNCTION void HI_Basic_Error (
	_hoops_AIGPR *	_hoops_RIGC,
	int						level,
	int						category,
	int						specific,
	char const *			buf1,
	char const *			buf2,
	char const *			buf3) 
{
	char const *			_hoops_SASAH[4];
	int						count = 0;

	if (BIT (level, _hoops_GPSAH)) {
		_hoops_SASAH[count++] = "There was an unexpected Hoops internal error -";
		level &= ~_hoops_GPSAH;
	}

	_hoops_SASAH[count++] = buf1;
	if (buf2 != null) {
		_hoops_SASAH[count++] = buf2;
		if (buf3 != null)
			_hoops_SASAH[count++] = buf3;
	}

	if (BIT (level, _hoops_RPSAH)) {
		_hoops_SASAH[count++] = "(invalid memory operation detected)";
		_hoops_SASAH[count++] = "";
		level &= ~_hoops_RPSAH;
	}

	HI_Generate_Error (_hoops_RIGC, category, specific, level, count, _hoops_SASAH);
}


GLOBAL_FUNCTION void HC_Generate_Error (
	int						level,
	int						category,
	int						specific,
	char const *			buf1,
	char const *			buf2,
	char const *			buf3) 
{
	_hoops_PAPPR context("HC_Generate_Error");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Generate_Error () */\n");
	);

	HI_Basic_Error (context, category, specific, level, buf1, buf2, buf3);
}


GLOBAL_FUNCTION void HI_Not_When_Streamed (
	_hoops_CRCP *		_hoops_SRCP,
	char const *	_hoops_CHCIP) 
{
	char            buf[MAX_ERRMSG];

	HE_ERROR2 (HEC_HOOPS_SYSTEM, HES_AUTO_STREAMING_MODE,
		Sprintf_P (null, "Segment %p is in streaming mode -", _hoops_SRCP),
			Sprintf_S (buf, "Can't %s", _hoops_CHCIP));
}


GLOBAL_FUNCTION void HI_Define_Error_Handler (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GHSAP	_hoops_APRPR) 
{
	_hoops_ICIIR(_hoops_RIGC);
	ASSERT(_hoops_APRPR != null);

	_hoops_RGIIR *	handler;
	if ((handler = HOOPS_WORLD->_hoops_RASAH) != null) do {
		if (handler->_hoops_APRPR == _hoops_APRPR) {
			HE_WARNING (HEC_ERROR_HANDLER, HES_DUPLICATE_DEFINITION,
				"Attempted definition of duplicate error handler");
			return;
		}
	}
	_hoops_RGGA ((handler = handler->next) == null);

	ZALLOC (handler, _hoops_RGIIR);
	handler->_hoops_HIHI = 1;
	handler->type = _hoops_GGIIR;
	handler->owner = HOOPS_WORLD;
	handler->_hoops_APRPR = _hoops_APRPR;
	if ((handler->next = HOOPS_WORLD->_hoops_RASAH) != null)
		HOOPS_WORLD->_hoops_RASAH->backlink = &handler->next;
	HOOPS_WORLD->_hoops_RASAH = handler;
	handler->backlink = &HOOPS_WORLD->_hoops_RASAH;

	HOOPS_WORLD->_hoops_GASAH = true;
}


HC_INTERFACE void HC_CDECL HC_Define_Error_Handler (
	_hoops_IRPCR				iroutine) 
{
	_hoops_PAPPR context("Define_Error_Handler");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Define_Error_Handler () */\n");
	);

	_hoops_GHSAP	_hoops_APRPR = (_hoops_GHSAP)iroutine;
	if (_hoops_APRPR == null) {
		HE_ERROR (HEC_ERROR_HANDLER, HES_NULL_INPUT, "Null value passed to Define_Error_Handler");
		return;
	}

	_hoops_RPPPR();
	HI_Define_Error_Handler (context, _hoops_APRPR);
	_hoops_IRRPR();
}



GLOBAL_FUNCTION void HI_UnDefine_Error_Handler (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GHSAP	_hoops_APRPR)
{
	_hoops_ICIIR(_hoops_RIGC);
	ASSERT(_hoops_APRPR != null);

	_hoops_RGIIR *	handler;

	if ((handler = HOOPS_WORLD->_hoops_RASAH) != null) do {
		if (handler->_hoops_APRPR == _hoops_APRPR) {
			HI_Generic_Delete (_hoops_RIGC, (_hoops_HPAH *)handler);
			_hoops_APRPR = (_hoops_GHSAP)null;
			break;
		}
	} _hoops_RGGA ((handler = handler->next) == null);

	if (_hoops_APRPR == (_hoops_GHSAP)0)
		return;

#ifdef WIN32_SYSTEM
	/*
	* _hoops_HPSHR _hoops_PSCSR _hoops_APSAH _hoops_CCA _hoops_IRS _hoops_ASCSR, _hoops_RH _hoops_GRGPR _hoops_IIGR
	* _hoops_PPSAH _hoops_HRGR _hoops_HAGH _hoops_GGR _hoops_RH _hoops_CCRPR
	* _hoops_HSAR _hoops_GGR _hoops_RH _hoops_ASCSR _hoops_SAPGP _hoops_IS _hoops_HPSAH. _hoops_PSPC, _hoops_CGPR _hoops_RH
	* _hoops_CCRPR _hoops_HHHH _hoops_RH _hoops_GRGPR _hoops_IIGR _hoops_PPSAH,
	* _hoops_SCH _hoops_RHAP _hoops_HAR _hoops_PSSP _hoops_PCPA _hoops_AGAH _hoops_GPHR _hoops_GGR _hoops_RH _hoops_HIGR
	* _hoops_IIGR _hoops_RIHH _hoops_IASAH. _hoops_CPGP _hoops_PPSAH _hoops_HRGR _hoops_RH
	* _hoops_RGAR _hoops_AGAH _hoops_CARSR _hoops_RIHH _hoops_HARPR (_hoops_HAS._hoops_IAS. _hoops_RH _hoops_RGAR
	* _hoops_SPR _hoops_GRPAA _hoops_GRGPR _hoops_GRS _hoops_HAR _hoops_PSSP), _hoops_SR _hoops_GRS _hoops_HPCAR
	* _hoops_SGS _hoops_PPSAH _hoops_CGH _hoops_SHH _hoops_RHSI _hoops_HII _hoops_RH
	* _hoops_IPRH _hoops_HARPR _hoops_HIGR _hoops_CGPR _hoops_SR _hoops_PAH'_hoops_RA _hoops_SSS _hoops_IRS _hoops_PSSP.
	*/
	_hoops_APRPR = (_hoops_GHSAP) &HC_Report_Error;

	if ((handler = HOOPS_WORLD->_hoops_RASAH) != null) do {
		if (handler->_hoops_APRPR == _hoops_APRPR) {
			HI_Generic_Delete (_hoops_RIGC,(_hoops_HPAH *)handler);
			//_hoops_IPSAH (_hoops_CPSAH, _hoops_SPSAH,
			//	"_hoops_SASRR _hoops_HARPR _hoops_HAR _hoops_GSGI - _hoops_GHSAH _hoops_PPSAH");
			_hoops_APRPR = (_hoops_GHSAP)null;
			break;
		}
	} _hoops_RGGA ((handler = handler->next) == null);

	if (_hoops_APRPR == (_hoops_GHSAP)0)
		return;
#endif

	/* _hoops_RGAR _hoops_HGCR _hoops_ARI _hoops_RPP _hoops_RHAC _hoops_HSSC _hoops_RHIR _hoops_HCR _hoops_PIIHR _hoops_RGHS */
	HE_WARNING (HEC_EXIT_HANDLER, HES_UNDEFINE_ERROR_HANDLER,
		"Error handler not found - can't undefine");
}



HC_INTERFACE void HC_CDECL HC_UnDefine_Error_Handler (
	_hoops_IRPCR	iroutine) 
{
	_hoops_PAPPR context("UnDefine_Error_Handler");

	CODE_GENERATION (
		HI_Dump_Code ("/* HC_UnDefine_Error_Handler () */\n");
	);


	_hoops_GHSAP	_hoops_APRPR = (_hoops_GHSAP)iroutine;
	if (_hoops_APRPR == (_hoops_GHSAP)null) {
		HE_ERROR (HEC_ERROR_HANDLER, HES_NULL_INPUT,"Null value passed to UnDefine_Error_Handler");
		return;
	}

	_hoops_RPPPR();
	HI_UnDefine_Error_Handler (context, _hoops_APRPR);
	_hoops_IRRPR();
}




HC_INTERFACE void HC_CDECL HC_Begin_Error_Handler_Search (void) 
{
	_hoops_PAPPR context("Begin_Error_Handler_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Error_Handler_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_SSPPR *			_hoops_GGHPR;
	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = context->_hoops_RHSAH;
	context->_hoops_RHSAH = _hoops_GGHPR;

	_hoops_CSPPR();

	_hoops_RGIIR *	_hoops_ARSAH;

	if ((_hoops_ARSAH = HOOPS_WORLD->_hoops_RASAH) != null) {
		_hoops_AGHPR **		_hoops_ASRGR = &_hoops_GGHPR->list;

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


HC_INTERFACE bool HC_CDECL HC_Find_Error_Handler (
	_hoops_IRPCR *			address) 
{
	_hoops_PAPPR context("Find_Error_Handler");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Error_Handler () */\n");
	);

	if (context->_hoops_RHSAH == null) {
		HE_ERROR (HEC_ERROR_HANDLER, HES_INACTIVE_SEARCH, "No error handler search is active");
		return false;
	}

	bool	result = false;

	_hoops_CSPPR();
	_hoops_AGHPR	*	list;
	while ((list = context->_hoops_RHSAH->list) != null) {
		_hoops_RGIIR *		_hoops_ARSAH = (_hoops_RGIIR *)list->item;

		context->_hoops_RHSAH->list = list->next;
		FREE (list, _hoops_AGHPR);

		/* _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_PGHPR */
		if (!BIT (_hoops_ARSAH->_hoops_RRHH, _hoops_HGAGR)) {
			*address = (_hoops_IRPCR)_hoops_ARSAH->_hoops_APRPR;
			_hoops_HPRH (_hoops_ARSAH);
			result = true;
			break;
		}
		else
			_hoops_HPRH (_hoops_ARSAH);
	}
	_hoops_IRRPR();
#endif
	return result;
}


HC_INTERFACE void HC_CDECL HC_Show_Error_Handler_Count (
	int alter *				count) 
{
	_hoops_PAPPR context("Show_Error_Handler_Count");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Error_Handler_Count () */\n");
	);

	if (context->_hoops_RHSAH == null) {
		HE_ERROR (HEC_SEGMENT, HES_INACTIVE_SEARCH, "No error handler search is active");
		*count = 0;
	}
	else
		*count = context->_hoops_RHSAH->count;
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Error_Handler_Search (void) 
{
	_hoops_PAPPR context("End_Error_Handler_Search");

#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Error_Handler_Search () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_RHSAH;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_ERROR_HANDLER, HES_END_WITHOUT_BEGIN_SEARCH, "End without matching Begin");
		return;
	}

	_hoops_CSPPR();
	HI_Free_Search_List (context, _hoops_GGHPR->list);
	_hoops_IRRPR();
	context->_hoops_RHSAH = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
}


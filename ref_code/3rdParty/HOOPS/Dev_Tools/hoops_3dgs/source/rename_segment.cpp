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
 * $Id: obf_tmp.txt 1.102 2010-11-09 00:15:31 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


#ifndef DISABLE_DATABASE_EDIT

local void _hoops_HAARS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	void *					info) {

	UNREFERENCED(_hoops_RIGC);
	UNREFERENCED (info);

	if (_hoops_SRCP->name.length == 0) return; /* _hoops_IPIHR _hoops_SCH, _hoops_AASAI! */

	// _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGRIR _hoops_HHSIR _hoops_GAR _hoops_SR _hoops_CHR _hoops_GIAA _hoops_IRS _hoops_IHSIR
	HI_Remove_Fast_Lookup_Item (_hoops_SRCP->owner, false, (Subsegment*)_hoops_SRCP);
	HI_Remove_Fast_Lookup_Item (_hoops_SRCP->owner, true, (Subsegment*)_hoops_SRCP);

	_hoops_RGAIR (_hoops_SRCP->name);
	_hoops_SRCP->name.length = 0;

	if (BIT (_hoops_SRCP->_hoops_RRHH, _hoops_PASIR)) { /* _hoops_SHSP _hoops_SCH _hoops_ARI */ }
	else {
		Subsegment	*_hoops_GIPIA;
		Subsegment	**_hoops_ASRGR = &_hoops_SRCP->owner->_hoops_RGRPR;

		/* _hoops_HASIR _hoops_HII _hoops_CAS _hoops_SCH _hoops_HRGR */
		if ((*_hoops_SRCP->backlink = _hoops_SRCP->next) != null)
			_hoops_SRCP->next->backlink = _hoops_SRCP->backlink;

		/* _hoops_IHIS _hoops_SCH _hoops_IS _hoops_RH _hoops_RIPS, _hoops_RAS _hoops_RH _hoops_CRRPR _hoops_PPR _hoops_ARPP _hoops_RH _hoops_SRS _hoops_GCSR-_hoops_GCSR */

		_hoops_RGGA ((_hoops_GIPIA = *_hoops_ASRGR) == null) {
			if (_hoops_GIPIA->type == _hoops_IRCP ||
				BIT (_hoops_GIPIA->_hoops_RRHH, _hoops_PASIR)) break;
			_hoops_ASRGR = &_hoops_GIPIA->next;
		}

		/* _hoops_PPSI '_hoops_SGGPH _hoops_IIH */
		if ((_hoops_SRCP->next = _hoops_GIPIA) != null)
			_hoops_GIPIA->backlink = &_hoops_SRCP->next;
		*_hoops_ASRGR = (Subsegment *)_hoops_SRCP;
		_hoops_SRCP->backlink = _hoops_ASRGR;
	}

	HI_Add_Fast_Lookup_Item (_hoops_SRCP->owner, true, (Subsegment *)_hoops_SRCP);
}

#endif


HC_INTERFACE void HC_CDECL HC_Rename_Segment (
	char const *	oldname,
	char const *	newname)
{
	_hoops_PAPPR context("Rename_Segment");

#ifdef DISABLE_DATABASE_EDIT
	_hoops_IRPPR ("Database Edit");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Rename_Segment (%S, %S);\n",
								  oldname, newname));
	);

	while (*newname == ' ') ++newname;

	_hoops_RPPPR();
	if (*newname == '\0') {
		/* _hoops_PIP: _hoops_CHGCC _hoops_SHGCC _hoops_HGISR _hoops_IH _hoops_RH _hoops_GIGCC */
		HI_For_Each (context, oldname, true, _hoops_HAARS, null);
	}
	else {
		/* _hoops_PIP: _hoops_IAARS _hoops_SHGCC _hoops_HGISR _hoops_IH _hoops_RH _hoops_GIGCC */
		HI_Output_Parse (context, oldname, newname, HI_Rename_Segment, null);
	}
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Move_Segment (
	char const *	oldname,
	char const *	newname)
{
	_hoops_PAPPR context("Move_Segment");

#ifdef DISABLE_DATABASE_EDIT
	_hoops_IRPPR ("Database Edit");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Move_Segment (%S, %S);\n", oldname, newname));
	);

	while (*newname == ' ')
		++newname;

	_hoops_RPPPR();
	if (*newname == '\0') {
		/* _hoops_PIP: _hoops_CHGCC _hoops_SHGCC _hoops_HGISR _hoops_IH _hoops_RH _hoops_GIGCC */
		HI_For_Each (context, oldname, true, _hoops_HAARS, null);
	}
	else {
		/* _hoops_PIP: _hoops_IAARS _hoops_SHGCC _hoops_HGISR _hoops_IH _hoops_RH _hoops_GIGCC */
		HI_Output_Parse (context, oldname, newname, HI_Rename_Segment, null);
	}
	_hoops_IRRPR();
#endif
}


GLOBAL_FUNCTION Key HI_Rename_Segment (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	_hoops_CRCP *				newowner,
	Subsegment **			_hoops_ASRGR,
	Subsegment *			_hoops_AIGSA,
	_hoops_HCRPR *					newname,
	bool					_hoops_PIGSA,
	void *					info) {
#ifndef DISABLE_DATABASE_EDIT
	_hoops_CRCP *				_hoops_SRCII = _hoops_SRCP->owner;

	UNREFERENCED (_hoops_AIGSA);
	UNREFERENCED (info);
	/* _hoops_IHGP _hoops_RIHH _hoops_HCGC _hoops_SRS */

	if (BIT (newowner->_hoops_PHSI, _hoops_PRSIR)) {
		HI_Not_When_Streamed (newowner, "rename a segment under it");
		return -1;
	}

	if (newname == null && _hoops_SRCII == newowner)
		return -1;

	if (_hoops_PIGSA) {
		char			buf[MAX_ERRMSG];

		HE_ERROR2 (HEC_SEGMENT, HES_SEGMENT_EXISTS,
				   Sprintf_P (null, "A segment named '%p' already exists",*_hoops_ASRGR),
				   Sprintf_P (buf, "(the incoming segment was '%p')",_hoops_SRCP));

		return -1;
	}


	/* _hoops_RPP _hoops_RH _hoops_HGHC _hoops_CAS _hoops_SR _hoops_PHHR _hoops_HRGR _hoops_RAS _hoops_CAIR... */

	if (_hoops_ASRGR == &_hoops_SRCP->next) _hoops_ASRGR = _hoops_SRCP->backlink;

	// _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGRIR _hoops_HHSIR _hoops_GAR _hoops_SR _hoops_CHR _hoops_GIAA _hoops_IRS _hoops_IHSIR
	HI_Remove_Fast_Lookup_Item (_hoops_SRCII, false, (Subsegment *)_hoops_SRCP);
	HI_Remove_Fast_Lookup_Item (_hoops_SRCII, true, (Subsegment *)_hoops_SRCP);

	if (_hoops_SRCII == newowner) {
		if (_hoops_ASRGR != _hoops_SRCP->backlink &&
			!BIT (_hoops_SRCP->_hoops_RRHH, _hoops_PASIR)) {
			/* _hoops_IHIS _hoops_SCH */

			if ((*_hoops_SRCP->backlink = _hoops_SRCP->next) != null)
				_hoops_SRCP->next->backlink = _hoops_SRCP->backlink;

			if ((_hoops_SRCP->next = *_hoops_ASRGR) != null)
				(*_hoops_ASRGR)->backlink = &_hoops_SRCP->next;

			*_hoops_ASRGR = (Subsegment *)_hoops_SRCP;
			_hoops_SRCP->backlink = _hoops_ASRGR;
		}
		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_CAHRA);
	}
	else {
		_hoops_ACHR	_hoops_CAARS;
		Key			_hoops_SAARS;

		/* _hoops_AGRP _hoops_RH _hoops_RRRPR */

		if (HI_Would_Be_Include_Loop (newowner, _hoops_SRCP)) {
			HE_ERROR2 (HEC_SEGMENT, HES_INFINITE_LOOP,
				Sprintf_PP (null, *_hoops_RIGC->_hoops_RCSPP == 'M' ?
					"Can't move '%p' into '%p' -" : "Can't rename '%p' into '%p' -", _hoops_SRCP, newowner),
						"An infinite loop of subsegments would be created");
			return -1;
		}

		if ((_hoops_SAARS = _hoops_SRCP->key) > _hoops_SHSSR && HI_Has_Local_Key (_hoops_SRCII, _hoops_SRCP->key)) {
			if (HI_Has_Local_Key (newowner, _hoops_SRCP->key)) {
				HE_ERROR2 (HEC_SEGMENT, HES_NUMBER_ALREADY_IN_USE,
					Sprintf_PP (null, *_hoops_RIGC->_hoops_RCSPP == 'M' ?
						"Can't move '%p' into '%p' -" :"Can't rename '%p' into '%p' -",_hoops_SRCP, newowner),
							"Locally renumbered keys would overlap");
				return -1;
			}

			HI_Delete_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP);
		}
		else
			_hoops_SAARS = _hoops_SHSSR;

		if ((ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HAHGP) ||
			 BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) &&
			!BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR)) {
			/* _hoops_RPP _hoops_AISIR, _hoops_HSII _hoops_ICACR, _hoops_IAII _hoops_RH _hoops_RPPS
			 * _hoops_GRS _hoops_GPARS _hoops_GGSR _hoops_RH _hoops_RRRPR'_hoops_GRI _hoops_AIIAP.
			 */
			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
				HI_Propagate_Scoped_Activity (_hoops_RIGC, (_hoops_SIHIR *)_hoops_SRCP->owner,
												_hoops_GSCCA| _hoops_CSCCA| _hoops_PISSR|
												_hoops_SSCCA,
												&HI_Find_Scoping_Window(_hoops_SRCP)->_hoops_RCHS);
			}
			else {
				/* (_hoops_PAH'_hoops_RA _hoops_SGH _hoops_RPARS _hoops_ICGRS _hoops_PGGA _hoops_IIGR _hoops_APARS _hoops_ICSHC) */
				_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, 
									_hoops_ACPGP|_hoops_CSCCA| _hoops_PISSR| 
									_hoops_RPSIR|_hoops_SSCCA);
			}
		}
		else {
			_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_CCHPA);
		}

		if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR)) {
			if (_hoops_SRCP->_hoops_AAGSA() > 0) {
				HI_Less_Light (_hoops_RIGC, _hoops_SRCII, _hoops_SRCP->_hoops_AAGSA());
				HI_More_Light (_hoops_RIGC, newowner, _hoops_SRCP->_hoops_AAGSA());
			}
			if (_hoops_SRCP->_hoops_PAGSA() > 0) {
				HI_Less_Cutting_Planes (_hoops_RIGC, _hoops_SRCII, _hoops_SRCP->_hoops_PAGSA());
				HI_More_Cutting_Planes (_hoops_RIGC, newowner, _hoops_SRCP->_hoops_PAGSA());
			}
			if (_hoops_SRCP->_hoops_SHGSA() > 0) {
				HI_Less_Shadows (_hoops_RIGC, _hoops_SRCII, _hoops_SRCP->_hoops_SHGSA());
				HI_More_Shadows (_hoops_RIGC, newowner, _hoops_SRCP->_hoops_SHGSA());
			}

			if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA)) {
				if (_hoops_SRCP->_hoops_IGCCA > 0) {
					HI_Less_Transparencies (_hoops_RIGC, _hoops_SRCII, _hoops_SRCP->_hoops_IGCCA);
					HI_More_Transparencies (_hoops_RIGC, newowner, _hoops_SRCP->_hoops_IGCCA);
				}
			}
		}

		HI_Antiquate_Bounding (_hoops_SRCP, false);
		HI_Delete_Renditions (_hoops_RIGC, _hoops_SRCP);

		if ((*_hoops_SRCP->backlink = _hoops_SRCP->next) != null)
			_hoops_SRCP->next->backlink = _hoops_SRCP->backlink;

		if ((_hoops_SRCP->next = *_hoops_ASRGR) != null)
			(*_hoops_ASRGR)->backlink = &_hoops_SRCP->next;

		*_hoops_ASRGR = (Subsegment *)_hoops_SRCP;
		_hoops_SRCP->backlink = _hoops_ASRGR;
		_hoops_SRCP->owner = newowner;

		if (_hoops_SAARS > _hoops_SHSSR)
			HI_Set_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_SRCP, 0, _hoops_SAARS, true);

		if (BIT (_hoops_SRCP->_hoops_RRHH, _hoops_PASIR)) {
			_hoops_SRCP->_hoops_RRHH &= ~_hoops_PASIR;
			/* _hoops_GII _hoops_GHCP _hoops_CSAP (_hoops_PAHH) _hoops_RGAR _hoops_SAPGP _hoops_IS _hoops_PPARS, _hoops_HIS _hoops_AASSC _hoops_SCH _hoops_HAH */
			_hoops_SRCP->priority = 0;
		}

		_hoops_CAARS = _hoops_SRCP->_hoops_RCGC;
		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) _hoops_CAARS |= T_WINDOWS;
		if ((_hoops_CAARS &= ~newowner->_hoops_RCGC) != false)
			HI_Propagate_Maybes (_hoops_RIGC, newowner, _hoops_CAARS);

		if (_hoops_SRCP->bounding != null)
			HI_Propagate_Bounding (_hoops_RIGC, newowner, _hoops_SRCP->bounding, _hoops_SRCP);

		_hoops_SRCP->_hoops_CPGPR |= _hoops_CAHRA;

		HI_Propagate_Bounding (_hoops_RIGC, _hoops_SRCP, _hoops_SRCP->bounding, null);

		/*** _hoops_CPSIR - _hoops_HAR _hoops_HPARS _hoops_IPARS _hoops_GARPH!!!
		 *** _hoops_SHHH _hoops_GAAP _hoops_AA _hoops_IRS _hoops_IPS _hoops_RIIA, _hoops_SCRH
		 *** _hoops_HPP _hoops_ISCPR _hoops_RH _hoops_RHGS _hoops_IH _hoops_SHPPR
		 ***
		 *** _hoops_PAR _hoops_SR _hoops_HHS _hoops_HS _hoops_PCCP "_hoops_CPARS" _hoops_PAIP
		 ***/

		_hoops_SRCP->_hoops_CPGPR &= ~_hoops_AHPGP; /* _hoops_HSPP _hoops_IAPR; _hoops_CCAH _hoops_GSSP */

		if (_hoops_SRCP->_hoops_PAGSA() > 0)
			_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_ACPGP|
								_hoops_CSCCA|_hoops_PISSR| _hoops_RPSIR);
		else if (BIT (_hoops_SRCP->_hoops_RCGC, T_FACES))
			_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_GCGSA|
								_hoops_CSCCA| _hoops_PISSR|_hoops_RPSIR);
		else if (ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HAHGP) ||
				 BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR))
			_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_RCGSA|
								_hoops_PISSR| _hoops_RPSIR);
		else
			_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_CCHPA);

		/* _hoops_SAHR _hoops_IS _hoops_IRHH _hoops_RCRR */
		_hoops_SASIR (_hoops_RIGC, newowner, _hoops_CCHPA);
	}

	if (newname != null) {
		_hoops_RGAIR (_hoops_SRCP->name);
		HI_Copy_Name (newname, &_hoops_SRCP->name);
	}

	// _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_RGRIR _hoops_HHSIR _hoops_GAR _hoops_SR _hoops_CHR _hoops_GIAA _hoops_IRS _hoops_IHSIR
	HI_Add_Fast_Lookup_Item (newowner, false, (Subsegment *)_hoops_SRCP);
	HI_Add_Fast_Lookup_Item (newowner, true, (Subsegment *)_hoops_SRCP);

	HI_Flush_Seg_Path_Lookup(_hoops_RIGC);

	if (BIT (_hoops_SRCP->owner->_hoops_PHSI, _hoops_CGPSA) &&
		!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GISIR)) {
		HI_Attach_Automatic_Driver (_hoops_RIGC, _hoops_SRCP);
	}

#endif
	return _hoops_SHSSR;
}

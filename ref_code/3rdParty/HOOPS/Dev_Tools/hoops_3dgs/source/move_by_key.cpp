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
 * $Id: obf_tmp.txt 1.133 2010-10-30 01:49:31 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

local void _hoops_CRCII(
	_hoops_AIGPR *	_hoops_RIGC,
	Key						key,
	_hoops_CRCP *				newowner) {
	_hoops_CRCP *				_hoops_SRCII;
	int						offset;
	Geometry *				_hoops_GACII = (Geometry *)_hoops_SISIR (_hoops_RIGC, key, &offset);
	_hoops_ACHR				_hoops_PGPIR;
	Key						_hoops_HSICA;
	Key						_hoops_RACII;
	bool					_hoops_AACII = false;
	Geometry *				_hoops_HCIS;

	if (_hoops_GACII == null ||
		((_hoops_GACII->type < _hoops_AHRIR ||
		  _hoops_GACII->type > _hoops_PHRIR ||
		  _hoops_GACII->type == HK_STRING_CURSOR ||
		  _hoops_GACII->type == _hoops_GHPGR) &&
		 _hoops_GACII->type != _hoops_AGRPR &&
		 _hoops_GACII->type != _hoops_IRCP) ||
		BIT (_hoops_GACII->_hoops_RRHH, _hoops_HGAGR)) {
		HE_ERROR (HEC_INVALID_KEY, HES_INVALID_GEOMETY_OR_SEGMENT,
				  "The key provided does not refer to a valid segment, include, or geometry");
		return;
	}
	if (BIT (_hoops_GACII->_hoops_RRHH, _hoops_CHRIR)) {
		int			count = 0;

		if (_hoops_GACII->type == _hoops_HIIP) {
			_hoops_SHRIR const *		_hoops_GIRIR = (_hoops_SHRIR *)_hoops_GACII;
			count = -_hoops_GIRIR->count / 2;
		}
		else
			count = ((_hoops_GRPGR *)_hoops_GACII)->count;

		if (offset >= count) {
			HE_ERROR (HEC_INVALID_KEY, HES_INVALID_GEOMETY_OR_SEGMENT,
					  "The key provided does not refer to a valid segment, include, or geometry");
			return;
		}
	}


	if (_hoops_GACII->owner == null) {
		HI_Not_When_LOD ();
		return;
	}

	/* _hoops_GRH _hoops_AGIR _hoops_SGHC -- _hoops_IRHH _hoops_SCH _hoops_IHSH _hoops_PII _hoops_IRS _hoops_PACII: */
	if (_hoops_GACII->type == _hoops_IRCP) {	/* _hoops_HACII _hoops_HRGR _hoops_CPSA (_hoops_GSRRR *)  */
		Key				segkey;
		char			_hoops_IACII[_hoops_GHAPH];
		char			_hoops_CACII[_hoops_GHAPH];
		char			_hoops_SACII[_hoops_GHAPH];
		char			*_hoops_GPCII = _hoops_SACII;
		char			*_hoops_ASAPR;
		int				size;

		segkey = _hoops_AIRIR(_hoops_GACII); /* _hoops_IH _hoops_IRS _hoops_HSGS, _hoops_IHGP, _hoops_HRSAR _hoops_RSIRR */
		_hoops_ASAPR = HI_Sprintf1 (_hoops_CACII, _hoops_CACII+_hoops_GGAPR(_hoops_CACII),
						  "%k", (void *)&segkey);
		*_hoops_ASAPR = '\0';		/* _hoops_PHPRA _hoops_CGH _hoops_IIP _hoops_SHH _hoops_IRAP _hoops_HII _hoops_RH %_hoops_ARGI _hoops_RPCC */

		Sprintf_P (_hoops_IACII, "%p", (void *)newowner);
		size = _hoops_SSGR (_hoops_IACII) + 4;
		if (size > _hoops_GGAPR(_hoops_SACII))
			ALLOC_ARRAY (_hoops_GPCII, size, char);

		_hoops_ASAPR = HI_Sprintf1 (_hoops_GPCII, &_hoops_GPCII[size-1], "%s", (void *)_hoops_IACII);
		/* "_hoops_PHPRA" _hoops_CGH _hoops_IIP _hoops_SHH _hoops_IRAP _hoops_GAR _hoops_RH _hoops_CRPR _hoops_HRGR _hoops_AHSC _hoops_RAPR */
		if (*(_hoops_ASAPR-1) != '/') *_hoops_ASAPR++ = '/';
		*_hoops_ASAPR++ = '*';
		*_hoops_ASAPR = '\0';

		/* _hoops_HA _hoops_CAHAR _hoops_SR _hoops_CHR _hoops_GHGA _hoops_IRS _hoops_PACII ("@_hoops_SIC", "_hoops_RRRPR / *") */
		HI_Output_Parse (_hoops_RIGC, _hoops_CACII, _hoops_GPCII, HI_Rename_Segment, null);

		if (size > _hoops_GGAPR(_hoops_SACII))
			FREE_ARRAY (_hoops_GPCII, size, char);

		return;
	}

	_hoops_SRCII = _hoops_GACII->owner;
	if (newowner == _hoops_SRCII)
		return;

	/* _hoops_HPGGR _hoops_GII _hoops_AIRI _hoops_CPCI _hoops_SGS _hoops_GGCA _hoops_GPP _hoops_RH _hoops_RHGS _hoops_PAR _hoops_CCAH _hoops_RPCII _hoops_GAR _hoops_AIPH */
	if (_hoops_GACII->type != _hoops_AGRPR && _hoops_GACII->type != _hoops_IRCP) {
		HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, _hoops_SRCII, _hoops_GACII->type, _hoops_GACII, 0);
		HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, newowner, _hoops_GACII->type, _hoops_GACII, 0);
	}

	if (BIT (_hoops_GACII->_hoops_RRHH, _hoops_CHRIR)) {
		int *						mapping;

		if (_hoops_GACII->type == _hoops_HIIP) {
			_hoops_SHRIR alter *		_hoops_GIRIR = (_hoops_SHRIR alter *)_hoops_GACII;
			mapping = _hoops_GIRIR->mapping;
		}
		else {
			_hoops_GRPGR alter *		_hoops_CPAI = (_hoops_GRPGR alter *)_hoops_GACII;
			mapping = _hoops_CPAI->mapping;
		}

		int							index = mapping[offset] & ~_hoops_RIRIR;

		_hoops_RACII = ~(POINTER_SIZED_INT)index;
		_hoops_HSICA = HOOPS_WORLD->_hoops_GCHCA.table[index].key;
	}
	else {
		_hoops_RACII = _hoops_AIRIR (_hoops_GACII);
		_hoops_HSICA = _hoops_GACII->key;
	}

	if (_hoops_HSICA > _hoops_SHSSR) {
		_hoops_AACII = HI_Has_Local_Key (_hoops_GACII->owner, _hoops_HSICA);

		if (_hoops_AACII) {
			if (HI_Has_Local_Key (newowner, _hoops_HSICA)) {
				HE_ERROR2 (HEC_INVALID_KEY, HES_NUMBER_ALREADY_IN_USE,
						   Sprintf_P (null, "Can't move item into '%p' -", newowner),
						   "The locally renumbered keys would overlap");
				return;
			}

			HI_Delete_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_GACII);
		}
		else if (BIT (_hoops_GACII->_hoops_RRHH, _hoops_CHRIR))
			HI_Delete_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_GACII, _hoops_HSICA);
	}

	/* _hoops_HCR _hoops_GPRS */

	if (_hoops_GACII->type == _hoops_AGRPR) {
		/* _hoops_AISRA, _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_PPCPI _hoops_GGR _hoops_RH _hoops_CCAH _hoops_RRRPR _hoops_PPR _hoops_HSCI _hoops_RGR _hoops_SPR,
		 * _hoops_HIH _hoops_GGSHR _hoops_RH _hoops_RIHRR _hoops_HCCGR _hoops_IS _hoops_GRHP _hoops_CRGIA _hoops_PRP
		 */
		_hoops_PGRPR *		_hoops_APCII = (_hoops_PGRPR *)_hoops_GACII;
		_hoops_PGRPR *		_hoops_PPCII;
		_hoops_CRCP *		ref = null;
		_hoops_PGRPR			_hoops_HPCII;

		ref = (_hoops_CRCP alter *)_hoops_APCII->_hoops_IGRPR;

		if ((_hoops_PPCII = HI_Create_Include (_hoops_RIGC, ref, newowner, &_hoops_APCII->condition)) != null) {
			/* _hoops_GGSHR _hoops_SGCRP _hoops_SRGR */
			_hoops_RSAI (_hoops_APCII,_hoops_PGRPR, &_hoops_HPCII);
			_hoops_RSAI (_hoops_PPCII, _hoops_PGRPR, _hoops_APCII);
			_hoops_RSAI (&_hoops_HPCII, _hoops_PGRPR, _hoops_PPCII);
			/* _hoops_HIH _hoops_CCIH _hoops_GIGR _hoops_SIC */
			_hoops_APCII->key = _hoops_HSICA;
			/* _hoops_PPR _hoops_IPCII _hoops_GPHHR _hoops_RRP _hoops_IS _hoops_SHH _hoops_CPCII, _hoops_HIS _hoops_GGSHR _hoops_AGAP _hoops_ISSC */
			_hoops_HPCII._hoops_GRRPR = _hoops_APCII->_hoops_GRRPR;
			_hoops_APCII->_hoops_GRRPR = _hoops_PPCII->_hoops_GRRPR;
			_hoops_PPCII->_hoops_GRRPR = _hoops_HPCII._hoops_GRRPR;
			_hoops_HPCII._hoops_SHAIR = _hoops_APCII->_hoops_SHAIR;
			_hoops_APCII->_hoops_SHAIR = _hoops_PPCII->_hoops_SHAIR;
			_hoops_PPCII->_hoops_SHAIR = _hoops_HPCII._hoops_SHAIR;

			/* _hoops_GGCH _hoops_RHSGH _hoops_PRCHR */
			*_hoops_APCII->backlink = (Subsegment *)_hoops_APCII;
			if (_hoops_APCII->next != null)
				_hoops_APCII->next->backlink = &_hoops_APCII->next;
			*_hoops_PPCII->backlink = (Subsegment *)_hoops_PPCII;
			if (_hoops_PPCII->next != null)
				_hoops_PPCII->next->backlink = &_hoops_PPCII->next;


			/* _hoops_HPIRA */
			if (_hoops_HSICA > _hoops_SHSSR && _hoops_AACII)
				HI_Set_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_APCII, 0, _hoops_HSICA, _hoops_AACII);

			PUSHNAME(_hoops_RIGC);
			HC_Delete_By_Key (_hoops_AIRIR (_hoops_PPCII));
			POPNAME(_hoops_RIGC);

			if (!ALLBITS (newowner->_hoops_RCGC, ref->_hoops_RCGC))
				HI_Propagate_Maybes (_hoops_RIGC, newowner, ref->_hoops_RCGC);
		}
		return;
	}


	_hoops_RPPPR();

	HI_Antiquate_Bounding (_hoops_SRCII, true);

#ifndef DISABLE_PARTIAL_ERASE
	/* _hoops_GHCA _hoops_RRP _hoops_IS _hoops_GRHP _hoops_IRS _hoops_RSPH _hoops_IPS _hoops_AARI _hoops_IH _hoops_IASI-_hoops_AHPIP _hoops_IS _hoops_SGH.
	 * _hoops_IPCP _hoops_RGAR _hoops_SCPC _hoops_IH _hoops_SISPR _hoops_IRS _hoops_CRSIP _hoops_GGR _hoops_RH _hoops_IHAH _hoops_HRGR _hoops_IH _hoops_IASI _hoops_AHPIP.  */
	if (!BIT (_hoops_GACII->_hoops_CPGPR, _hoops_CASIR) &&
		_hoops_SRCII->_hoops_CSC &&
		_hoops_SRCII->_hoops_CSC->_hoops_APHGA) {
		_hoops_HCIS = HI_Copy_Geometry (_hoops_RIGC, _hoops_GACII);
		_hoops_HCIS->_hoops_CPGPR = _hoops_GACII->_hoops_CPGPR | _hoops_AHSGA;
		_hoops_HCIS->_hoops_RRHH |= _hoops_HGAGR;

		/* _hoops_AGGAR _hoops_SPCS _hoops_GGR _hoops_GAR _hoops_IRS _hoops_PGHPR _hoops_GIGR */
		if ((_hoops_HCIS->next = _hoops_SRCII->_hoops_SCGPR()) != null)
			_hoops_HCIS->next->backlink = &_hoops_HCIS->next;
		_hoops_SRCII->_hoops_RSGPR (_hoops_HCIS);

		/* _hoops_PCGPA _hoops_GIGR _hoops_CARA _hoops_SIC _hoops_PIRA _hoops_IH _hoops_GHAP._hoops_RPRAR. _hoops_ACAPA. */
		_hoops_HCIS->key = _hoops_HSICA;
	}
#endif

	if (BIT (_hoops_GACII->_hoops_RRHH, _hoops_CHRIR)) {
		if (_hoops_GACII->type == _hoops_HIIP) {
			_hoops_SHRIR alter *		_hoops_GIRIR = (_hoops_SHRIR alter *)_hoops_GACII;
			int						index = _hoops_GIRIR->mapping[offset] & ~_hoops_RIRIR;
			Line *					line = HI_Isolate_Line_From_Multiline (_hoops_RIGC, _hoops_GIRIR, offset);

			_hoops_RACII = HI_Add_To_Multiline (_hoops_RIGC, newowner, line->points[0], line->points[1], index);
			HI_Table_Remove_Geometry(line);
			_hoops_CIGPR (_hoops_RIGC, line);
			_hoops_HPRH (line);
		}
		else {
			_hoops_GRPGR alter *		_hoops_CPAI = (_hoops_GRPGR alter *)_hoops_GACII;
			int						index = _hoops_CPAI->mapping[offset] & ~_hoops_RIRIR;
			Marker *				marker = HI_Isolate_Marker_From_Multimarker (_hoops_RIGC, _hoops_CPAI, offset);

			_hoops_RACII = HI_Add_To_Multimarker (_hoops_RIGC, newowner, marker->_hoops_CSAI, index);
			HI_Table_Remove_Geometry(marker);
			_hoops_CIGPR (_hoops_RIGC, marker);
			_hoops_HPRH (marker);
		}

		if (_hoops_HSICA > _hoops_SHSSR) {
			int						_hoops_SPCII;
			Geometry *				_hoops_SHCPH = (Geometry *)_hoops_SISIR (_hoops_RIGC, _hoops_RACII, &_hoops_SPCII);

			HI_Set_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_SHCPH, _hoops_SPCII, _hoops_HSICA, _hoops_AACII);
		}
	}
	else {
		_hoops_GACII->_hoops_RRHH &= ~_hoops_PASIR;
		_hoops_GACII->_hoops_CPGPR &= ~(_hoops_AHSGA|_hoops_AHPGP);
		_hoops_GACII->_hoops_CPGPR |= _hoops_CASIR;

		HI_Table_Remove_Geometry(_hoops_GACII);
		_hoops_CIGPR (_hoops_RIGC,_hoops_GACII);
		HI_Table_Insert_Geometry(newowner, _hoops_GACII);
		_hoops_GACII->owner = newowner;

		/* _hoops_ARP _hoops_GH _hoops_CCAH _hoops_IRGH _hoops_SIC (_hoops_HRSAR _hoops_SIC _hoops_IIP _hoops_HGAS) */
		if (_hoops_HSICA > _hoops_SHSSR && _hoops_AACII)
			HI_Set_User_Key (_hoops_RIGC, (_hoops_HPAH *)_hoops_GACII, 0, _hoops_HSICA, true);
	}

	if (_hoops_GACII->type == _hoops_HGCP) {
		Image * image = (Image*)_hoops_GACII;

		if (image->texture && (_hoops_CRCP*)image->texture->owner == _hoops_SRCII) {
			_hoops_RCR * texture = image->texture;
			HI_Record_Texture_Definition(_hoops_RIGC, newowner, texture);
			_hoops_PRRH (texture);
			HI_UnDefine_Texture(_hoops_RIGC, image->texture);
			texture->owner = (_hoops_HPAH*)newowner;
		}
	}
	else if (_hoops_GACII->type == _hoops_HGPGR) {
		HI_Less_Cutting_Planes (_hoops_RIGC, _hoops_SRCII, 1);
		HI_More_Cutting_Planes (_hoops_RIGC, newowner, 1);
	}
	else if (_hoops_GACII->type == _hoops_ICIP) {
		HI_Less_Light (_hoops_RIGC, _hoops_SRCII, 1);
		HI_More_Light (_hoops_RIGC, newowner, 1);
	}

	_hoops_PGPIR = HI_Determine_Geometry_Maybes (_hoops_GACII);
	if (!ALLBITS (newowner->_hoops_RCGC, _hoops_PGPIR))
		HI_Propagate_Maybes (_hoops_RIGC, newowner, _hoops_PGPIR);


	Bounding		bounding;

	if (HI_Figure_Geometry_Bounding (_hoops_GACII, bounding)) {
		HI_Propagate_Bounding (_hoops_RIGC, newowner, bounding, null);
		newowner->_hoops_HSRIR.Merge (bounding);
	}

	if (_hoops_GACII->type == _hoops_HGPGR) {
		/* (_hoops_ARCA _hoops_GHC _hoops_CHR _hoops_GHCII _hoops_PGGA _hoops_SSIA _hoops_AIIAP _hoops_RRI _hoops_PII
		 *	_hoops_IRS _hoops_HGAS _hoops_IGRI _hoops_HSAR _hoops_PII _hoops_HGAS _hoops_CPAP.)
		 */
		_hoops_SASIR (_hoops_RIGC, _hoops_SRCII, _hoops_GGARA|_hoops_RPSIR|_hoops_SSCCA);
		_hoops_SASIR (_hoops_RIGC, _hoops_GACII, _hoops_RAGGA|_hoops_RPSIR|_hoops_SSCCA);
	}
	else if (BIT (_hoops_PGPIR, T_FACES)) {
		_hoops_SASIR (_hoops_RIGC, _hoops_SRCII, _hoops_PCPGP|
									  _hoops_CSCCA|
									  _hoops_PISSR|
									  _hoops_RPSIR|
									  _hoops_SSCCA);
		_hoops_SASIR (_hoops_RIGC, _hoops_GACII, _hoops_GCGSA|
								   _hoops_CSCCA|
								   _hoops_PISSR|
								   _hoops_RPSIR|
								   _hoops_SSCCA);
	}
	else {
		_hoops_SASIR (_hoops_RIGC, _hoops_SRCII, _hoops_HRCCA|
									  _hoops_PISSR|
									  _hoops_RPSIR|
									  _hoops_SSCCA);
		_hoops_SASIR (_hoops_RIGC, _hoops_GACII, _hoops_RCGSA|
								   _hoops_PISSR|
								   _hoops_RPSIR|
								   _hoops_SSCCA);
		if (_hoops_PGPIR == T_TEXT)
			_hoops_SASIR (_hoops_RIGC, _hoops_GACII, _hoops_RSCCA);
	}

	_hoops_IRRPR();
}


HC_INTERFACE void HC_CDECL HC_Move_By_Key (
	Key						key,
	char const *			_hoops_IACII) {
	_hoops_CRCP	*				newowner;
	_hoops_PAPPR context("Move_By_Key");

#ifdef DISABLE_DATABASE_EDIT
	_hoops_IRPPR ("Database Edit");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Move_By_Key (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", _hoops_IACII));
	);

	_hoops_RPPPR();
	if ((newowner = HI_One_Segment_Search (context, _hoops_IACII, true)) != null)
		_hoops_CRCII (context, key, newowner);
	_hoops_IRRPR();
#endif
}


HC_INTERFACE void HC_CDECL HC_Move_Key_By_Key (
	Key						key,
	Key						newowner) 
{
	_hoops_PAPPR context("Move_Key_By_Key");

#ifdef DISABLE_DATABASE_EDIT
	_hoops_IRPPR ("Database Edit");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "Move_Key_By_Key (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_LD (null, "LOOKUP (%D));\n", newowner));
	);

	_hoops_RPPPR();
	_hoops_CRCP *	_hoops_RHCII = (_hoops_CRCP *)_hoops_RCSSR (context, newowner);

	if (_hoops_RHCII->type == _hoops_IRCP && !BIT (_hoops_RHCII->_hoops_RRHH, _hoops_HGAGR))
		_hoops_CRCII (context, key, _hoops_RHCII);
	_hoops_IRRPR();
#endif
}


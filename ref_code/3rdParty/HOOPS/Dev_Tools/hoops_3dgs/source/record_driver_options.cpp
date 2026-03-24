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
 * $Id: obf_tmp.txt 1.103 2010-10-06 19:16:21 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"


/* _hoops_GIGHR: _hoops_RGSGS _hoops_AGSGS _hoops_ICRHR _hoops_ASAI _hoops_PGSGS _hoops_HGSGS! */

/* _hoops_GRH _hoops_CSPP _hoops_IIGR _hoops_IRRC _hoops_RIGR _hoops_PGAP _hoops_GRS _hoops_ASAC _hoops_IRS "_hoops_CASI" _hoops_SICHR _hoops_PIRA */
#define _hoops_IGSGS(_hoops_HAGR, _hoops_IHPCR)		(BIT (_hoops_HAGR, _hoops_IHPCR) ? true : false)

GLOBAL_FUNCTION void HD_Record_Driver_Options (
	Display_Context alter		*dc,
	Attribute const				*_hoops_ASGPR) {
	_hoops_GAPIR const		*options;
	_hoops_PCARP					_hoops_HAICA;
	_hoops_PCARP					_hoops_IAPRP;
	_hoops_PCARP					_hoops_IAICA;
	_hoops_PCARP					_hoops_HCARP;

	if (!BIT(dc->flags, _hoops_CPPHP)) 
		return; /* _hoops_RGR _hoops_RGAR _hoops_IIAH _hoops_RPHR _hoops_HPGR _hoops_RH _hoops_SCIA _hoops_PAPA */

	options = (_hoops_GAPIR const *)_hoops_ASGPR;
	_hoops_HAICA = options->_hoops_HAICA;
	_hoops_IAPRP = options->_hoops_IAPRP;
	_hoops_IAICA = options->_hoops_IAICA;
	_hoops_HCARP = options->_hoops_HCARP;

	dc->options.flags &= ~_hoops_HAICA;
	dc->options.flags |= _hoops_IAPRP;

	dc->options.values &= ~_hoops_IAICA;
	dc->options.values |= _hoops_HCARP;


	if (BIT (_hoops_HAICA, _hoops_CAPRP))
		dc->options.backing_store = _hoops_IGSGS (_hoops_IAPRP, _hoops_CAPRP);

	if (BIT (_hoops_HAICA, _hoops_SAPRP))
		dc->options.border = _hoops_IGSGS (_hoops_IAPRP, _hoops_SAPRP);

	if (BIT (_hoops_HAICA, _hoops_GPPRP))
		dc->options._hoops_HRSSP = _hoops_IGSGS (_hoops_IAPRP, _hoops_GPPRP);

	if (BIT (_hoops_HAICA, _hoops_RPPRP))
		dc->options._hoops_SRRRR = _hoops_IGSGS (_hoops_IAPRP, _hoops_RPPRP);

	if (BIT (_hoops_HAICA, _hoops_RHPRP))
		dc->options._hoops_AHIIP = _hoops_IGSGS (_hoops_IAPRP, _hoops_RHPRP);

	if (BIT (_hoops_HAICA, _hoops_AHPRP))
		dc->options._hoops_PIPGA = _hoops_IGSGS (_hoops_IAPRP, _hoops_AHPRP);

	if (BIT (_hoops_HAICA, _hoops_PHPRP))
		dc->options._hoops_HHHSR = _hoops_IGSGS (_hoops_IAPRP, _hoops_PHPRP);

	if (BIT (_hoops_HAICA, _hoops_APPRP))
		dc->options._hoops_RAHHP = _hoops_IGSGS (_hoops_IAPRP, _hoops_APPRP);

	if (BIT (_hoops_HAICA, _hoops_HHPRP))
		dc->options._hoops_SIAH = _hoops_IGSGS (_hoops_IAPRP, _hoops_HHPRP);

	if (BIT (_hoops_HAICA, _hoops_RIPRP))
		dc->options._hoops_HPSC = _hoops_IGSGS (_hoops_IAPRP, _hoops_RIPRP);

	if (BIT (_hoops_HAICA, _hoops_AIPRP)) {
		dc->options._hoops_RPSSP = _hoops_IGSGS (options->_hoops_AHHRP.value, _hoops_IPHRP);
		dc->options._hoops_APSSP = 
			dc->options._hoops_RPSSP && _hoops_IGSGS (options->_hoops_AHHRP.value, _hoops_SPHRP);
		if (BIT (options->_hoops_AHHRP.mask, _hoops_CPHRP))
			dc->options._hoops_GAHP = options->_hoops_AHHRP._hoops_GAHP;
	}

	if (BIT (_hoops_HAICA, _hoops_HIPRP)) {
		dc->options._hoops_RGSH = _hoops_IGSGS (options->_hoops_RGSH.value, _hoops_PIHRP);
		if (BIT (options->_hoops_RGSH.mask, _hoops_HIHRP))
			dc->options._hoops_SHSH = options->_hoops_RGSH._hoops_SHGP;
		if (BIT (options->_hoops_RGSH.mask, _hoops_IIHRP))
			dc->options._hoops_HRSH = options->_hoops_RGSH._hoops_HGGGR;
		if (BIT (options->_hoops_RGSH.mask, _hoops_SIHRP))
			dc->options._hoops_IGSH = options->_hoops_RGSH.value & _hoops_SIHRP;
	}

	if (BIT (_hoops_HAICA, _hoops_IIPRP)) {
		dc->options._hoops_HPSSP = _hoops_IGSGS (options->_hoops_ASHRP.value, _hoops_ACHRP);
		if (BIT (options->_hoops_ASHRP.mask, _hoops_PCHRP))
			dc->options._hoops_SCHP = options->_hoops_ASHRP._hoops_GSHRP;
		if (BIT (options->_hoops_ASHRP.mask, _hoops_HCHRP))
			dc->options._hoops_ICHP = options->_hoops_ASHRP._hoops_RSHRP;
		if (BIT (options->_hoops_ASHRP.mask, _hoops_ICHRP))
			dc->options._hoops_HSHP = options->_hoops_ASHRP._hoops_SHGP;
	}

	if (BIT (_hoops_HAICA, _hoops_PIPRP)) {
		dc->options._hoops_PPSSP = _hoops_IGSGS (options->_hoops_AIHRP.value, _hoops_PHHRP);
		if (BIT (options->_hoops_AIHRP.mask, _hoops_HHHRP))
			dc->options._hoops_GIGP = options->_hoops_AIHRP._hoops_GIGP;
		if (BIT (options->_hoops_AIHRP.mask, _hoops_SHHRP))
			dc->options._hoops_GAPP = BIT(options->_hoops_AIHRP.value, _hoops_IHHRP);
	}

	if (BIT (_hoops_HAICA, _hoops_IHPRP))
		dc->options._hoops_CASSP = _hoops_IGSGS (_hoops_IAPRP, _hoops_IHPRP);

	if (BIT (_hoops_HAICA, _hoops_CHPRP))
		dc->options._hoops_SASSP = _hoops_IGSGS (_hoops_IAPRP, _hoops_CHPRP);

	if (BIT (_hoops_HAICA, _hoops_SHPRP))
		dc->options._hoops_GPSSP = _hoops_IGSGS (_hoops_IAPRP, _hoops_SHPRP);

	if (BIT (_hoops_HAICA, _hoops_PPPRP))
		dc->options._hoops_SRSSP = _hoops_IGSGS (_hoops_IAPRP, _hoops_PPPRP);

	if (BIT (_hoops_HAICA, _hoops_GHPRP))
		dc->options._hoops_GASSP = _hoops_IGSGS (_hoops_IAPRP, _hoops_GHPRP);

	if (BIT (_hoops_IAICA, _hoops_ICARP)) {
		if (dc->options._hoops_APPIR > 0) {
			FREE_ARRAY (dc->options._hoops_RPPIR, dc->options._hoops_APPIR, int);
			dc->options._hoops_RPPIR = null;
		}

		if (!BIT (_hoops_HCARP, _hoops_ICARP)) {
			dc->options._hoops_APPIR = 0;
			dc->options._hoops_RPPIR = null;
			dc->options._hoops_IRARR = 0;
		}
		else {
			if ((dc->options._hoops_APPIR = options->_hoops_APPIR) > 0) {
				int				count = options->_hoops_APPIR;
				POOL_ALLOC_ARRAY (dc->options._hoops_RPPIR, count, int, dc->memory_pool);
				while (--count >= 0)
					dc->options._hoops_RPPIR[count] =
										options->_hoops_RPPIR[count];
			}
			dc->options._hoops_IRARR = options->_hoops_IRARR;
		}
	}

	if (BIT (_hoops_IAICA, _hoops_CCARP)) {
		dc->options._hoops_IRSSP = _hoops_IGSGS (_hoops_HCARP, _hoops_CCARP);
		dc->options._hoops_CRSSP =
				(options->_hoops_CRHRP == _hoops_IRHRP);
	}

	if (BIT (_hoops_IAICA, _hoops_SCARP)) {
		if (BIT (_hoops_HCARP, _hoops_SCARP))
			dc->options._hoops_APASR = options->_hoops_APASR;
		else
			dc->options._hoops_APASR = dc->_hoops_PGCC._hoops_APASR;
	}

	if (BIT (_hoops_IAICA, _hoops_GSARP)) {
		if (BIT (_hoops_HCARP, _hoops_GSARP)) {
			if (options->_hoops_GCPRP[1] == 0 &&
				options->_hoops_GCPRP[2] == 0) {
				dc->options._hoops_GCPRP = options->_hoops_GCPRP[0];
				dc->options._hoops_IPSSP[0] = 0;
				dc->options._hoops_IPSSP[1] = 0;
				dc->options._hoops_IPSSP[2] = 0;
			}
			else {
				dc->options._hoops_IPSSP[0] = options->_hoops_GCPRP[0];
				dc->options._hoops_IPSSP[1] = options->_hoops_GCPRP[1];
				dc->options._hoops_IPSSP[2] = options->_hoops_GCPRP[2];
				dc->options._hoops_GCPRP =
					options->_hoops_GCPRP[0] *
					options->_hoops_GCPRP[1] *
					options->_hoops_GCPRP[2];
			}
		}
		else {
			dc->options._hoops_GCPRP = -1;
			dc->options._hoops_IPSSP[0] = 0;
			dc->options._hoops_IPSSP[1] = 0;
			dc->options._hoops_IPSSP[2] = 0;
		}
	}

	if (BIT (_hoops_IAICA, _hoops_RSARP)) {
		if (BIT (_hoops_HCARP, _hoops_RSARP))
			dc->options._hoops_ARPSR = options->_hoops_IGHRP;
		else
			dc->options._hoops_ARPSR = _hoops_PGHRP;
	}

	if (BIT (_hoops_IAICA, _hoops_ARPRP)) {
		if (options->_hoops_ARHRP == _hoops_GRHRP)
			dc->options._hoops_HASSP = BIT(dc->_hoops_PGCC.flags, _hoops_ISRIP);
		else
			dc->options._hoops_HASSP =
				(options->_hoops_ARHRP == _hoops_SGHRP);
	}

	/* _hoops_PSP _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IH _hoops_CGSGS -- _hoops_AA _hoops_RGR _hoops_SGSGS */
	{
		int i, j, _hoops_GRSGS, _hoops_IACPA;

		/* _hoops_ARI _hoops_SR _hoops_HASC _hoops_RH _hoops_PISRR _hoops_RH _hoops_RHPP _hoops_SSCP _hoops_RGIRR _hoops_SCH _hoops_GAHGH _hoops_CCA 
		 * _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_PSGC _hoops_IS _hoops_RCPS _hoops_GH _hoops_CCA _hoops_SPR _hoops_HII _hoops_RH _hoops_HIGR _hoops_SGS _hoops_SR _hoops_PAH _hoops_AA. */
		dc->_hoops_SHPGR = -1;
		for (i = 0 ; dc->_hoops_SHPGR < 0 ; i++) {
			for (j = 0 ; dc->_hoops_SHPGR < 0 ; j++) {
				_hoops_GRSGS = options->_hoops_IAHRP[i];
				_hoops_IACPA = dc->_hoops_PGCC._hoops_IIPGH[j];
				if (_hoops_GRSGS == _hoops_SRHRP ||
					(_hoops_GRSGS == _hoops_PAHRP && _hoops_IACPA == QMoves_Spriting) ||
					(_hoops_GRSGS == _hoops_RAHRP && _hoops_IACPA == QMoves_Real_Overlay) ||
					(_hoops_GRSGS == _hoops_RAHRP && _hoops_IACPA == QMoves_Accumulation) ||
					(_hoops_GRSGS == _hoops_GAHRP && _hoops_IACPA == QMoves_XOR)) {
					dc->_hoops_SHPGR = _hoops_IACPA;
				}
				if (_hoops_IACPA == QMoves_NONE)
					break;
			}
		}
	}

	if (BIT (_hoops_IAICA, _hoops_IRPRP)) {
		dc->options._hoops_PPHRP = options->_hoops_PPHRP;
	}
	
	if (BIT (_hoops_IAICA, _hoops_RAPRP))
		dc->options._hoops_HSPRP = options->_hoops_HSPRP;

	if (BIT (_hoops_IAICA, _hoops_ASARP)) {
		if (BIT (_hoops_HCARP, _hoops_ASARP))
			dc->options._hoops_RCPRP = options->_hoops_RCPRP;
		else
			dc->options._hoops_RCPRP = -1.0f;
	}

	if (BIT (_hoops_IAICA, _hoops_PSARP)) {
		if (BIT (_hoops_HCARP, _hoops_PSARP))
			dc->options._hoops_ACPRP = options->_hoops_ACPRP;
		else
			dc->options._hoops_ACPRP = 0.0f;
	}

	if (BIT (_hoops_IAICA, _hoops_HSARP)) {
		if (BIT (_hoops_HCARP, _hoops_HSARP)) {
			dc->options._hoops_PCPRP[0][0] = options->_hoops_PCPRP[0][0];
			dc->options._hoops_PCPRP[0][1] = options->_hoops_PCPRP[0][1];
			dc->options._hoops_PCPRP[1][0] = options->_hoops_PCPRP[1][0];
			dc->options._hoops_PCPRP[1][1] = options->_hoops_PCPRP[1][1];
			dc->options._hoops_PCPRP[2][0] = options->_hoops_PCPRP[2][0];
			dc->options._hoops_PCPRP[2][1] = options->_hoops_PCPRP[2][1];
		}
		else {
			dc->options._hoops_PCPRP[0][0] = 1.0f;
			dc->options._hoops_PCPRP[0][1] = 0.0f;
			dc->options._hoops_PCPRP[1][0] = 0.0f;
			dc->options._hoops_PCPRP[1][1] = 1.0f;
			dc->options._hoops_PCPRP[2][0] = 0.0f;
			dc->options._hoops_PCPRP[2][1] = 0.0f;
		}
	}

	if (BIT (_hoops_IAICA, _hoops_ISARP)) {
		if (BIT (_hoops_HCARP, _hoops_ISARP))
			dc->options._hoops_AAPSR = options->_hoops_AAPSR;
		else
			dc->options._hoops_AAPSR = dc->_hoops_PGCC._hoops_AAPSR;
	}

	if (BIT (_hoops_IAICA, _hoops_CSARP)) {
		if (BIT (_hoops_HCARP, _hoops_CSARP))
			dc->options._hoops_GSHSR = options->_hoops_GSHSR;
		else
			dc->options._hoops_GSHSR = 1.0f;
	}

	if (BIT (_hoops_IAICA, _hoops_SSARP)) {
		if (BIT (_hoops_HCARP, _hoops_SSARP)) {
			dc->options._hoops_SPHSR.x = options->_hoops_SPHSR.x;
			dc->options._hoops_SPHSR.y = options->_hoops_SPHSR.y;
		}
		else {
			dc->options._hoops_SPHSR.x = -1.0f;
			dc->options._hoops_SPHSR.y = -1.0f;
		}
	}

	if (BIT (_hoops_IAICA, _hoops_GGPRP)) {
		if (BIT (_hoops_HCARP, _hoops_GGPRP))
			dc->options._hoops_SHSHA = options->_hoops_SHSHA;
		else
			dc->options._hoops_SHSHA = 999.0f;
	}

	if (BIT (_hoops_IAICA, _hoops_RGPRP)) {
		if (BIT (_hoops_HCARP, _hoops_RGPRP)) {
			dc->options._hoops_HCPRP.left	 = options->_hoops_HCPRP.left;
			dc->options._hoops_HCPRP.right	 = options->_hoops_HCPRP.right;
			dc->options._hoops_HCPRP.bottom = options->_hoops_HCPRP.bottom;
			dc->options._hoops_HCPRP.top	 = options->_hoops_HCPRP.top;
		}
		else {
			dc->options._hoops_HCPRP.left	 = -1.0f;
			dc->options._hoops_HCPRP.right	 = 1.0f;
			dc->options._hoops_HCPRP.bottom = -1.0f;
			dc->options._hoops_HCPRP.top	 = 1.0f;
		}
		dc->options._hoops_HPHRP = options->_hoops_HPHRP;
	}

	/*
	 *	_hoops_SCGIH
	_hoops_RPP (_hoops_IRRC (_hoops_IHSGH, _hoops_RRSGS))
		_hoops_CSPH->_hoops_AAP._hoops_ARSGS = _hoops_PRSGS (_hoops_CHSGH, _hoops_RRSGS);
	 */

	if (BIT (_hoops_HAICA, _hoops_IPPRP))
		dc->options._hoops_RASSP = _hoops_IGSGS (_hoops_IAPRP, _hoops_IPPRP);

	if (BIT (_hoops_HAICA, _hoops_CPPRP))
		dc->options._hoops_AASSP = _hoops_IGSGS (_hoops_IAPRP, _hoops_CPPRP);

	if (BIT (_hoops_HAICA, _hoops_SPPRP))
		dc->options._hoops_PASSP = _hoops_IGSGS (_hoops_IAPRP, _hoops_SPPRP);

	if (BIT (_hoops_IAICA, _hoops_AGPRP)) {
		_hoops_RGAIR (dc->options._hoops_IAPIR);
		if (BIT (_hoops_HCARP, _hoops_AGPRP)) {
			if (options->_hoops_IAPIR.length > 0)
				HI_Copy_Name (&options->_hoops_IAPIR, &dc->options._hoops_IAPIR);
			else
				HI_Copy_Name (&HOOPS_WORLD->_hoops_GRGHP, &dc->options._hoops_IAPIR);
		}
	}

	if (BIT (_hoops_IAICA, _hoops_SRPRP)) {
		dc->options._hoops_RIPGA = _hoops_IGSGS (_hoops_HCARP, _hoops_SRPRP);
		if (dc->options._hoops_RIPGA)
			dc->options._hoops_AIPGA = options->_hoops_AIPGA;
	}

	if (BIT (_hoops_IAICA, _hoops_GAPRP)) {
		if (BIT (_hoops_HCARP, _hoops_GAPRP)) {
			if (options->_hoops_PPPIR)
				dc->options._hoops_CPSSP = (_hoops_IHCSP) options->_hoops_PPPIR->address;
			else
				dc->options._hoops_CPSSP = 0;
		}
		else
			dc->options._hoops_CPSSP = 0;
	}

	if (BIT (_hoops_IAICA, _hoops_PAPRP))
		dc->options._hoops_HSHRP = options->_hoops_HSHRP;

	if (BIT (_hoops_IAICA, _hoops_CRPRP)) {
		if (dc->options._hoops_SAPIR)
			HI_Free_Font_Names (dc->options._hoops_SAPIR);
		dc->options._hoops_SAPIR = null;

		if (BIT (_hoops_HCARP, _hoops_CRPRP)) {
			dc->options._hoops_SAPIR = HI_Copy_Font_Names (options->_hoops_SAPIR);
		}
	}

	if (BIT (_hoops_IAICA, _hoops_AAPRP)) {
		if (dc->options._hoops_GPPIR)
			HI_Free_Font_Names (dc->options._hoops_GPPIR);
		dc->options._hoops_GPPIR = null;

		if (BIT (_hoops_HCARP, _hoops_AAPRP)) {
			dc->options._hoops_GPPIR = HI_Copy_Font_Names (options->_hoops_GPPIR);
		}
	}

	if (BIT (_hoops_IAICA, _hoops_PGPRP)) {
		if (BIT (_hoops_HCARP, _hoops_PGPRP))
			dc->options._hoops_GSPRP = options->_hoops_GSPRP;
		else
			dc->options._hoops_GSPRP = _hoops_ICPRP;
	}

	if (BIT (_hoops_IAICA, _hoops_HGPRP)) {
		if (BIT (_hoops_HCARP, _hoops_HGPRP))
			dc->options._hoops_RCHSR = options->_hoops_RCHSR;
		else
			dc->options._hoops_RCHSR = 0;
	}

	if (BIT (_hoops_IAICA, _hoops_IGPRP)) {
		if (BIT (_hoops_HCARP, _hoops_IGPRP)) {
			dc->options._hoops_GCHSR = options->_hoops_GCHSR;
			dc->options._hoops_RGHRP = options->_hoops_RGHRP;
		}
		else {
			dc->options._hoops_GCHSR = 0;
			dc->options._hoops_RGHRP = _hoops_SSPRP;
		}
	}

	if (BIT (_hoops_IAICA, _hoops_CGPRP)) {
		if (BIT (_hoops_HCARP, _hoops_CGPRP))
			dc->options._hoops_ISPRP = options->_hoops_ISPRP;
		else
			dc->options._hoops_ISPRP = 0;
	}

	if (BIT (_hoops_IAICA, _hoops_PRPRP)) {
		if (BIT (_hoops_HCARP, _hoops_PRPRP))
			dc->options._hoops_CSPRP = options->_hoops_CSPRP;
		else
			dc->options._hoops_CSPRP = 0;
	}


	if (BIT (_hoops_IAICA, _hoops_SGPRP)) {
		if (BIT (_hoops_HCARP, _hoops_SGPRP))
			dc->options._hoops_AGHRP = options->_hoops_AGHRP;
		else
			dc->options._hoops_AGHRP = -1;
	}

	if (BIT (_hoops_IAICA, _hoops_GRPRP)) {
		HI_Free_Name_List(dc->options._hoops_HAPIR);
		if (BIT (_hoops_HCARP, _hoops_GRPRP))
			dc->options._hoops_HAPIR = HI_Copy_Name_List (options->_hoops_HAPIR);
		else
			dc->options._hoops_HAPIR = 0;
	}

	if (BIT (_hoops_IAICA, _hoops_RRPRP)) {
		if (BIT (_hoops_HCARP, _hoops_RRPRP))
			dc->options._hoops_GHHSR = options->_hoops_GHHSR;
		else
			dc->options._hoops_GHHSR = 75;
	}
}

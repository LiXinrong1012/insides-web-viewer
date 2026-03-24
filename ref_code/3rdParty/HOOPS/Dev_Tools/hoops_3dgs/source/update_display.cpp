/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and fconsidered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.140 2010-11-30 21:47:28 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "please.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"


local void _hoops_CHPRGR (void) {
	/*
	if (!BIT (HOOPS_WORLD->_hoops_SAPPR, _hoops_IRHGI) &&
		!ANYBIT (HOOPS_WORLD->_hoops_HPSPP, _hoops_SPCPP|_hoops_AHCPP)) {
		char const				*buf[8];

		buf[0] = "This copy of HOOPS has not been licensed for commercial";
		buf[1] = "development or distribution purposes.	 Copying is prohibited.";
		buf[2] = "To obtain rights to develop and/or distribute applications";
		buf[3] = "based on HOOPS, please contact Tech Soft 3D at";
		buf[4] = "510-883-2180 or email support@techsoft3d.com";
		buf[5] = "";
		buf[6] = "The HOOPS Web page is located at:";
		buf[7] = "http://www.techsoft3d.com";

		HOOPS_WORLD->_hoops_SAPPR |= _hoops_IRHGI;

		HI_Generate_Untrappable_Error (null, HEC_SYSTEM, HES_INVALID_LICENSE, 1, 8, buf);
	}
	*/
}

local void _hoops_SHPRGR (
	_hoops_CRCP				*_hoops_SRCP) {

	/* _hoops_HPSHR _hoops_PCCP _hoops_AGRRR _hoops_PAAP, _hoops_SCAC _hoops_RH _hoops_PGRGS _hoops_SGI _hoops_GGSR _hoops_HIS _hoops_SGS
	 * _hoops_GHSI-_hoops_CHCC _hoops_SPHGR _hoops_GRS _hoops_IRARH _hoops_SHH _hoops_PPSPR _hoops_IH _hoops_IHIR _hoops_AHPIP
	 * _hoops_PPR _hoops_HAR _hoops_SHH _hoops_GGAPH _hoops_IS _hoops_SHH _hoops_RPGCA-"_hoops_SPIP".
	 */

	top:;

	_hoops_SSAGR(_hoops_SRCP->_hoops_IPPGR);

	if (BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR)) {
		_hoops_SRCP->_hoops_CPGPR &= ~_hoops_CASIR;
		_hoops_SRCP->_hoops_CPGPR |= _hoops_AHSGA;
	}
	_hoops_SRCP->_hoops_PHSI &= ~(_hoops_HCGPR|_hoops_ICGPR);

	_hoops_SSAGR(_hoops_SRCP->geometry);

	if (_hoops_SRCP->_hoops_IPPGR != null) {
		Attribute	*_hoops_ASGPR = _hoops_SRCP->_hoops_IPPGR;

		do {
			_hoops_SSAGR(_hoops_ASGPR->next);

			if (BIT (_hoops_ASGPR->_hoops_CPGPR, _hoops_CASIR)) {
				_hoops_ASGPR->_hoops_CPGPR &= ~_hoops_CASIR;
				_hoops_ASGPR->_hoops_CPGPR |= _hoops_AHSGA;
			}
		} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
	}

	_hoops_SSAGR(_hoops_SRCP->_hoops_RGRPR);

	if (_hoops_SRCP->geometry != null) {
		Geometry		*geometry = _hoops_SRCP->geometry;

		do {
			_hoops_SSAGR(geometry->next);
			if (BIT (geometry->_hoops_CPGPR, _hoops_CASIR)) {
				geometry->_hoops_CPGPR &= ~_hoops_CASIR;
				geometry->_hoops_CPGPR |= _hoops_AHSGA;
			}
		} while ((geometry = geometry->next) != null);
	}

	if (_hoops_SRCP->_hoops_RGRPR != null) {
		Subsegment	*_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR;

		do {
			_hoops_SSAGR(_hoops_SSGPR->next);
			if (BIT (_hoops_SSGPR->_hoops_CPGPR, _hoops_CASIR)) {
				_hoops_SSGPR->_hoops_CPGPR &= ~_hoops_CASIR;
				_hoops_SSGPR->_hoops_CPGPR |= _hoops_AHSGA;
			}

			if (_hoops_SSGPR->type == _hoops_IRCP &&
				BIT (_hoops_SSGPR->_hoops_CPGPR, _hoops_AHGPR)) {
				if (_hoops_SSGPR->next == null) {
					_hoops_SRCP = (_hoops_CRCP *)_hoops_SSGPR;
					goto top;
				}
				else {
					_hoops_SHPRGR ((_hoops_CRCP *)_hoops_SSGPR);
				}
			}
		} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);
	}
}



GLOBAL_FUNCTION bool HI_Do_Update (
	_hoops_AIGPR *	_hoops_RIGC,
	double					limit,
	bool					_hoops_SCSIH) {
	_hoops_GGAGR *					_hoops_GHRI;

	_hoops_CHPRGR ();

	if (_hoops_RIGC->_hoops_PAGRH == _hoops_PIPGI)
		_hoops_RIGC->_hoops_PAGRH = _hoops_AIPGI;
	if (_hoops_RIGC->_hoops_PAGRH != _hoops_AIPGI) {
		_hoops_RIGC->_hoops_PAGRH = _hoops_IAGRH;
		return false;
	}

	_hoops_CSPPR();

	_hoops_CIAGP (&HOOPS_WORLD->_hoops_GPPI);


	_hoops_RIGC->_hoops_HCPGR = (limit < 0.0) ? 0 : 1;
	if (_hoops_RIGC->_hoops_HCPGR && limit < 0.001)
		limit = 0.001;
	_hoops_RIGC->_hoops_GHPGI = HI_What_Time();
	_hoops_RIGC->_hoops_RHPGI = _hoops_RIGC->_hoops_HCPGR * _hoops_SSAGI (limit);
	_hoops_RIGC->_hoops_ACHGH = _hoops_RIGC->_hoops_GHPGI + _hoops_RIGC->_hoops_RHPGI;

_hoops_GIPRGR:;

	_hoops_RIGC->_hoops_PAGRH = _hoops_HAGRH;

	HI_Update_Actor_List (_hoops_RIGC);

	if (HOOPS_WORLD->_hoops_AARPH)
		HI_Update_Events (_hoops_RIGC);

	if (HOOPS_WORLD->root == null ||
		!ANYBIT (HOOPS_WORLD->root->_hoops_CPGPR, _hoops_AHGPR|_hoops_IPPGP) ||
		!HOOPS_WORLD->_hoops_RAAPH) {
		/* _hoops_APSH _hoops_PII _hoops_ISAP _hoops_SSCP _hoops_RIPRGR */

		if ((_hoops_GHRI = HOOPS_WORLD->_hoops_CISHA) != null) do {
			if (ALLBITS (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_RCSHA|_hoops_ISRPH) &&
				!ANYBIT(_hoops_GHRI->_hoops_CGPIR, _hoops_SISHA|_hoops_CSRPH) &&
				(_hoops_SCSIH || !BIT(_hoops_GHRI->owner->_hoops_PHSI, _hoops_ARRPR))) {
				if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_SSRPH, null)) {
					_hoops_GHRI->_hoops_CGPIR &= ~_hoops_ISRPH;
				}
				else {
					/* _hoops_CGP _hoops_SR _hoops_IICGGR _hoops_IS _hoops_GHHA, _hoops_PSCR _hoops_IIH _hoops_PIHA (_hoops_PIHA?) _hoops_SHH
					 * _hoops_PCCP _hoops_IGRSC _hoops_PGRRR _hoops_GGR _hoops_AACAR _hoops_ARI.
					 */
					if (_hoops_RIGC->_hoops_PAGRH != _hoops_HAGRH)
						break;
				}
			}
		} while ((_hoops_GHRI = _hoops_GHRI->_hoops_CISHA) != null);

		if (_hoops_GHRI == null) {
			/* _hoops_ARRP _hoops_IS _hoops_AA. */
			_hoops_RIGC->_hoops_PAGRH = _hoops_AIPGI;
			_hoops_IRRPR();
			return true;
		}
	}

	if (HOOPS_WORLD->_hoops_CISHA != null) {
		_hoops_GHRI = HOOPS_WORLD->_hoops_CISHA;

		do if (!BIT (_hoops_GHRI->owner->_hoops_RRHH, _hoops_HGAGR) &&
			   _hoops_GHRI->_hoops_GPPI < HOOPS_WORLD->_hoops_GPPI &&
			   ALLBITS (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_RCSHA) &&
			   !BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR|_hoops_SISHA|_hoops_CSRPH) &&
			   (_hoops_SCSIH || !BIT(_hoops_GHRI->owner->_hoops_PHSI, _hoops_ARRPR))) {
			_hoops_CRCP *		_hoops_SRCP = _hoops_GHRI->owner,
							*owner = _hoops_SRCP->owner;
			Activity		_hoops_AIPRGR = false;
			Activity		_hoops_AGSSS;

			/* _hoops_ISCP _hoops_RPCII' _hoops_CPGGR _hoops_RHCHR _hoops_ISCP _hoops_CPGGR... */
			_hoops_RGGA (owner->type == _hoops_PRAIR) {
				_hoops_AIPRGR |= owner->_hoops_CPGPR | owner->_hoops_SPGPR & _hoops_GHRI->_hoops_RIIAP;
				owner = owner->owner;
			}

			_hoops_AGSSS = _hoops_SRCP->_hoops_CPGPR | _hoops_SRCP->_hoops_SPGPR & _hoops_GHRI->_hoops_RIIAP;

			/* _hoops_PA _hoops_SAPIA _hoops_GH _hoops_IIH? */
			if (ANYBIT (_hoops_AIPRGR, _hoops_ICHPA |
										_hoops_APPGP))
				_hoops_AGSSS |= _hoops_AIPRGR & _hoops_AHPGP;

			if (!BIT (_hoops_AGSSS, _hoops_IPPGP)) {
				if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_ISRPH)) {
					if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_SSRPH, null))
						_hoops_GHRI->_hoops_CGPIR &= ~_hoops_ISRPH;
					else
						_hoops_AGSSS |= _hoops_SRCP->_hoops_CPGPR; /* _hoops_RHSHA */

					if (_hoops_RIGC->_hoops_PAGRH == _hoops_PIPGI)
						break;
				}
			}

			if (BIT (_hoops_AGSSS, _hoops_IPPGP)) {
				/* _hoops_CPHP _hoops_IS _hoops_PGSA */
				_hoops_GHRI->_hoops_CGPIR |= _hoops_CSRPH;
				if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_HAGSC, &_hoops_AGSSS)) {
					_hoops_GHRI->_hoops_CGPIR &= ~_hoops_RCSHA;
					_hoops_GHRI->owner->_hoops_PHSI &= ~_hoops_HIHGP;
				}
				_hoops_GHRI->_hoops_CGPIR &= ~_hoops_CSRPH;
			}

			if (_hoops_RIGC->_hoops_PAGRH == _hoops_PIPGI)
				break;

			_hoops_GHRI->_hoops_GPPI = HOOPS_WORLD->_hoops_GPPI;
		} while ((_hoops_GHRI = _hoops_GHRI->_hoops_CISHA) != null);
	}

	if (_hoops_RIGC->_hoops_PAGRH == _hoops_IAGRH &&
				HOOPS_WORLD->_hoops_SRHGI != null)
		_hoops_RIGC->_hoops_PAGRH = _hoops_PIPGI;

	if (_hoops_RIGC->_hoops_PAGRH == _hoops_IAGRH)
		goto _hoops_GIPRGR;

	if (_hoops_RIGC->_hoops_PAGRH == _hoops_PIPGI)
		_hoops_SHPRGR (HOOPS_WORLD->root);
	else {
		HI_Age_Activity (_hoops_RIGC, HOOPS_WORLD->root);

		HOOPS_WORLD->_hoops_RAAPH = false;
	}

	if (HOOPS_WORLD->_hoops_AARPH)
		HI_Update_Events (_hoops_RIGC);

	if (_hoops_RIGC->_hoops_PAGRH == _hoops_IAGRH)
		goto _hoops_GIPRGR;

	_hoops_RIGC->_hoops_PAGRH = _hoops_AIPGI;

	_hoops_IRRPR();

	if (HOOPS_WORLD->_hoops_SRHGI != null) {
		Pending_Special *	victim;

		victim = HOOPS_WORLD->_hoops_SRHGI;
		do {
			HOOPS_WORLD->_hoops_SRHGI = victim->next;

			PUSHNAME(_hoops_RIGC);
			HI_Queue_Special_Event (_hoops_RIGC, victim->type.text, victim->value.text);
			POPNAME(_hoops_RIGC);

			_hoops_RGAIR (victim->type);
			_hoops_RGAIR (victim->value);
			FREE (victim, Pending_Special);
		} while ((victim = HOOPS_WORLD->_hoops_SRHGI) != null);
	}

	if (HOOPS_WORLD->_hoops_GAHGI != null) {
		_hoops_ISSAP				*victim;

		victim = HOOPS_WORLD->_hoops_GAHGI;
		do {
			HOOPS_WORLD->_hoops_GAHGI = victim->next;

			if (victim->segment != null) {
				_hoops_SASIR (_hoops_RIGC, victim->segment, victim->_hoops_CSSAP);
				_hoops_HPRH (victim->segment);
			}

			if (victim->geometry != null &&
				!BIT (victim->geometry->_hoops_RRHH, _hoops_HGAGR)) {
				_hoops_SASIR (_hoops_RIGC, victim->geometry, victim->_hoops_SSSAP);
				_hoops_HPRH (victim->geometry);
			}

			FREE (victim, _hoops_ISSAP);
		} while ((victim = HOOPS_WORLD->_hoops_GAHGI) != null);
	}

	return !HOOPS_WORLD->_hoops_RAAPH;
}


GLOBAL_FUNCTION bool HI_Do_One_Update (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	double					limit) {
	_hoops_GGAGR *					_hoops_GHRI;
	_hoops_CRCP *				_hoops_SRCP;
	Activity				_hoops_AGSSS = 0;
	bool					_hoops_PIPRGR = false;

	//_hoops_CHPRGR ();//jerry

	_hoops_CSPPR();

	if ((_hoops_GHRI = HI_Force_Find_Driver (_hoops_RIGC, name)) == null) {
		_hoops_IRRPR();
		return false;
	}

	_hoops_CIAGP (&HOOPS_WORLD->_hoops_GPPI);

	_hoops_RIGC->_hoops_HCPGR = (limit < 0.0) ? 0 : 1;
	if (_hoops_RIGC->_hoops_HCPGR && limit < 0.001)
		limit = 0.001;
	_hoops_RIGC->_hoops_GHPGI = HI_What_Time();
	_hoops_RIGC->_hoops_RHPGI = _hoops_RIGC->_hoops_HCPGR * _hoops_SSAGI (limit);
	_hoops_RIGC->_hoops_ACHGH = _hoops_RIGC->_hoops_GHPGI + _hoops_RIGC->_hoops_RHPGI;


	_hoops_RIGC->_hoops_IIHGH = false;
	_hoops_RIGC->_hoops_PAGRH = _hoops_HAGRH;

	_hoops_SRCP = _hoops_GHRI->owner;

	if (!BIT(_hoops_SRCP->_hoops_PHSI, _hoops_ARRPR))
		_hoops_PHPGR (HEC_DRIVER, HES_DRIVER_NOT_ISOLATED,
					 "Update_One_Display on a driver that is not isolated is not recommended.",
					 "See Set_Driver_Options docs.");

	if (!ALLBITS (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_RCSHA) ||
		BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_SGPIR)) {
		_hoops_IRRPR();
		return false;
	}


	_hoops_CRCP *			owner = _hoops_SRCP->owner;
	Activity			_hoops_AIPRGR = 0;

	/* _hoops_ISCP _hoops_RPCII' _hoops_CPGGR _hoops_RHCHR _hoops_ISCP _hoops_CPGGR... */


	while (owner->type != _hoops_PRAIR) {
		if (_hoops_GHRI->_hoops_GPPI < owner->_hoops_PCIGP())
			_hoops_AIPRGR |= owner->_hoops_CPGPR | owner->_hoops_SPGPR & _hoops_GHRI->_hoops_RIIAP;

		owner = owner->owner;
	}

	_hoops_AGSSS = _hoops_SRCP->_hoops_CPGPR | _hoops_SRCP->_hoops_SPGPR & _hoops_GHRI->_hoops_RIIAP;

	/* _hoops_PA _hoops_SAPIA _hoops_GH _hoops_IIH? */
	if (ANYBIT (_hoops_AIPRGR, _hoops_ICHPA |
								_hoops_APPGP))
		_hoops_AGSSS |= _hoops_AIPRGR & _hoops_AHPGP;



	if (BIT (_hoops_AGSSS, _hoops_IPPGP)) {
		/* _hoops_CPHP _hoops_IS _hoops_PGSA */
		_hoops_GHRI->_hoops_CGPIR |= _hoops_CSRPH;
		if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_HAGSC, &_hoops_AGSSS)) {
			_hoops_GHRI->_hoops_CGPIR &= ~_hoops_RCSHA;
			_hoops_GHRI->owner->_hoops_PHSI &= ~_hoops_HIHGP;
		}
		_hoops_GHRI->_hoops_CGPIR &= ~_hoops_CSRPH;
	}

	if (_hoops_RIGC->_hoops_PAGRH == _hoops_IAGRH &&
		HOOPS_WORLD->_hoops_SRHGI != null)
		_hoops_RIGC->_hoops_PAGRH = _hoops_PIPGI;

	if (_hoops_RIGC->_hoops_PAGRH == _hoops_PIPGI) {
		_hoops_SHPRGR (_hoops_SRCP);
		_hoops_PIPRGR = true;
	}
	else {
		HI_Age_Activity (_hoops_RIGC, _hoops_SRCP);	/* _hoops_ICIC -- _hoops_RHAP _hoops_HAR _hoops_SRHIR _hoops_CRRPR */

		_hoops_GHRI->_hoops_GPPI = HOOPS_WORLD->_hoops_GPPI;
	}

	if (HOOPS_WORLD->_hoops_GAHGI != null) {
		_hoops_ISSAP				*victim;

		victim = HOOPS_WORLD->_hoops_GAHGI;
		do {
			HOOPS_WORLD->_hoops_GAHGI = victim->next;

			if (victim->segment != null) {
				_hoops_SASIR (_hoops_RIGC, victim->segment, victim->_hoops_CSSAP);
				_hoops_HPRH (victim->segment);
			}

			if (victim->geometry != null) {
				ASSERT(!BIT (victim->geometry->_hoops_RRHH, _hoops_HGAGR));
				_hoops_SASIR (_hoops_RIGC, victim->geometry, victim->_hoops_SSSAP);
				_hoops_HPRH (victim->geometry);
			}

			FREE (victim, _hoops_ISSAP);
		} while ((victim = HOOPS_WORLD->_hoops_GAHGI) != null);
	}

	_hoops_RIGC->_hoops_PAGRH = _hoops_AIPGI;

	_hoops_IRRPR();

	return !_hoops_PIPRGR;
}




HC_INTERFACE bool HC_CDECL HC_Update_Display (void) 
{
	_hoops_PAPPR context("Update_Display");

	CODE_GENERATION (
		HI_Dump_Code ("HC_Update_Display ();\n");
	);

	return HI_Do_Update (context, -1.0, false);
}

HC_INTERFACE bool HC_CDECL HC_Update_Display_Timed (
	double					limit) 
{
	_hoops_PAPPR context("Update_Display_Timed");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_F (null, "HC_Update_Display_Timed (%F);\n", limit));
	);

	return HI_Do_Update (context, limit, false);
}


HC_INTERFACE bool HC_CDECL HC_Update_One_Display (
	char const *			name) 
{
	_hoops_PAPPR context("Update_One_Display");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Update_One_Display (%S);\n", name));
	);

	return HI_Do_One_Update (context, name, -1.0);
}

HC_INTERFACE bool HC_CDECL HC_Update_One_Display_Timed (
	char const *			name,
	double					limit) 
{
	_hoops_PAPPR context("Update_One_Display_Timed");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Update_One_Display_Timed (%S, ", name));
		HI_Dump_Code (Sprintf_F (null, "%F);\n", limit));
	);

	return HI_Do_One_Update (context, name, limit);
}

GLOBAL_FUNCTION void HI_Update_Interrupted (_hoops_AIGPR *_hoops_RIGC) {

	_hoops_RIGC->_hoops_PAGRH = _hoops_PIPGI;
}


GLOBAL_FUNCTION void HI_Set_Delayed_Activity (
	_hoops_CRCP	const *			segment,
	Activity				_hoops_CSSAP,
	Geometry const *		geometry,
	Activity				_hoops_SSSAP) {
	_hoops_ISSAP *		_hoops_HIPRGR;

	ZALLOC (_hoops_HIPRGR, _hoops_ISSAP);

	if ((_hoops_HIPRGR->segment = segment) != null) {
		_hoops_PRRH (segment);
		_hoops_HIPRGR->_hoops_CSSAP = _hoops_CSSAP;
	}

	if ((_hoops_HIPRGR->geometry = geometry) != null) {
		_hoops_PRRH (geometry);
		_hoops_HIPRGR->_hoops_SSSAP = _hoops_SSSAP;
	}

	_hoops_HIPRGR->next = HOOPS_WORLD->_hoops_GAHGI;
	HOOPS_WORLD->_hoops_GAHGI = _hoops_HIPRGR;
}


GLOBAL_FUNCTION bool HI_Initialize_Actor (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GGAGR *					_hoops_GHRI) {

	if (!ANYBIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_SGPIR)) {
		_hoops_CRCP *			_hoops_SRCP = _hoops_GHRI->owner;

		if (_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_AAGSC, null)) {
			_hoops_GHRI->_hoops_CGPIR |= _hoops_GCSHA;
			if (BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_RCSHA)) {
				_hoops_GHRI->owner->_hoops_PHSI |= _hoops_HIHGP;

				// _hoops_HHSA _hoops_IRS _hoops_PHHR-_hoops_IHIPR _hoops_PPR _hoops_PCCP _hoops_PAAP
				// (_hoops_GA'_hoops_RA _hoops_SGH _hoops_ASGH _hoops_IAHA _hoops_PGGA _hoops_ARI _hoops_SR _hoops_GA'_hoops_RA _hoops_PICP _hoops_AHCA _hoops_CGRGS _hoops_IIPRGR)

				_hoops_SRCP->_hoops_CPGPR |= _hoops_GAGSA | _hoops_CAHRA;

				// _hoops_PPR _hoops_IRHH _hoops_RCRR _hoops_AGAP _hoops_SIH _hoops_HGCR _hoops_GCGSP
				_hoops_SRCP = _hoops_SRCP->owner;
				if (_hoops_SRCP->type != _hoops_PRAIR)
					_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_HGSCA);
			}
		}
		else {
			_hoops_GHRI->_hoops_CGPIR = _hoops_SGPIR;
			ASSERT(_hoops_GHRI->_hoops_PPRPR == null);
			_hoops_SRCP->_hoops_PHSI &= ~_hoops_HIHGP;
		}
	}

	return BIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA);
}


GLOBAL_FUNCTION void HI_Update_Actor_List (
	_hoops_AIGPR *	_hoops_RIGC) {
	_hoops_GGAGR *					_hoops_GHRI;

	_hoops_CAAI (HOOPS_WORLD->_hoops_PPHGI);

	if ((_hoops_GHRI = HOOPS_WORLD->_hoops_CISHA) == null) {
		// _hoops_GHCC (_hoops_CIPRGR, _hoops_SIPRGR, "_hoops_HAIC'_hoops_RA _hoops_CPACI - _hoops_IIH _hoops_CHR _hoops_PSP _hoops_CISI _hoops_GCPRGR");
	}
	else if (!BIT (HOOPS_WORLD->root->_hoops_CPGPR, _hoops_AHGPR)) {
		// _hoops_RPAPR
	}
	else do {
		if (!BIT (_hoops_GHRI->_hoops_RRHH, _hoops_HGAGR) && !BIT (_hoops_GHRI->owner->_hoops_RRHH, _hoops_HGAGR) &&
			!ANYBIT (_hoops_GHRI->_hoops_CGPIR, _hoops_GCSHA|_hoops_SGPIR))
			HI_Initialize_Actor (_hoops_RIGC, _hoops_GHRI);
	} while ((_hoops_GHRI = _hoops_GHRI->_hoops_CISHA) != null);

	_hoops_APAI (HOOPS_WORLD->_hoops_PPHGI);
}





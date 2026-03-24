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
 * $Id: obf_tmp.txt 1.477 2011-01-27 03:51:50 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "driver.h"
#include "phedron.h"
#include "phdraw.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"



#define _hoops_CAPIP(dc, _hoops_SRCP, which)			\
	(BIT ((_hoops_SRCP)->_hoops_CPGPR, which) ||	\
	 (dc->options._hoops_SRRRR &&	\
	  dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA &&		\
	  BIT ((_hoops_SRCP)->_hoops_SPGPR, which)))


local void _hoops_SAPIP (
	Display_Context const *		dc,
	_hoops_CRCP const *				_hoops_SRCP) {

	if (_hoops_SRCP == dc->_hoops_AAHSR)
		HE_WARNING (HEC_WINDOW, HES_OUTER_MOST_WINDOW_IS_CLEAR,
				"The outermost window may not be set 'clear'");
	else
		_hoops_PHPGR (HEC_WINDOW, HES_CLEAR_WINDOW_INHERITED,
				Sprintf_P (null,
			"The window on '%p' is inheriting a 'clear' window pattern -", _hoops_SRCP),
			"'Clear' must be set directly on the segment to work properly.");
}


GLOBAL_FUNCTION void HD_Alternate_Hidden_Root (
	Display_Context alter *		dc,
	int							mode) {

	if (mode >= _hoops_GPPIP || mode != _hoops_RIII (mode)) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
							"unexpected alternate mode specified");
		return;
	}

	dc->_hoops_IASS ^= mode;
}


#ifndef DISABLE_PARTIAL_ERASE
local bool _hoops_RPPIP (
	Display_Context const *	dc,
	_hoops_CRCP const *			_hoops_SRCP,
	_hoops_HICS const &	_hoops_APPIP,
	bool					_hoops_PPPIP) {
	_hoops_HICS			path = _hoops_APPIP;

	/* _hoops_HRGR _hoops_RH _hoops_HPPIP _hoops_IPPIP _hoops_CSHHR _hoops_GGR _hoops_GIRRR _hoops_IH _hoops_RCSAR _hoops_CAGH
	 * _hoops_GGR _hoops_RGR _hoops_RPPS _hoops_PGAP _hoops_SSCP _hoops_CHIA _hoops_SGS _hoops_SCH _hoops_APSI _hoops_IRS _hoops_HPPIP _hoops_IPPIP
	 * _hoops_CPPIP ?
	 *
	 * _hoops_HSRR _hoops_RH _hoops_RPAIA _hoops_IS _hoops_AGCR _hoops_PPR _hoops_RII _hoops_SAPIA _hoops_SPPIP, _hoops_GHPIP
	 * _hoops_GGR _hoops_RHPIP...
	 */
  top:;

	if (!_hoops_PPPIP &&
		(BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_SPPGP) ||
		 !BIT (_hoops_SRCP->_hoops_RCGC, _hoops_GHHGP))) {
		/* _hoops_RGR _hoops_CAGH _hoops_HRGR _hoops_HAR _hoops_GPRS */
		return false;
	}

	{
		_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path, false);

		if ((_hoops_CSC == null || _hoops_CSC->_hoops_APHGA == null) &&
			 (_hoops_PPPIP || BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_SPPGP))) {
			/* _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_GII _hoops_PSIGA _hoops_SIHC _hoops_GPP _hoops_RSH _hoops_IS _hoops_AA _hoops_IRS _hoops_IASI _hoops_AHPIP _hoops_ARI */
			return false;
		}
	}

	if (!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_GHHGP) || _hoops_SRCP->_hoops_RGRPR == null) {
		/* _hoops_IIH _hoops_CHR _hoops_PSP _hoops_PSSPR _hoops_PHPIP _hoops_AHCA _hoops_RH _hoops_IASI-_hoops_AHPIP _hoops_CSHHR */

		/* _hoops_HRGR "_hoops_GPRS" _hoops_PGI _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_AA _hoops_SCH _hoops_PAR _hoops_SR'_hoops_ASAR _hoops_PHRH _hoops_IS _hoops_AA _hoops_SCH */
		return !BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CPPGP) || _hoops_PPPIP;
	}
	else {
		Subsegment const *		_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR;

		/* _hoops_RGR _hoops_CAGH _hoops_HRGR _hoops_IHRI, _hoops_HIH _hoops_IIH _hoops_GHCA _hoops_SHH _hoops_HAGH _hoops_PSSPR _hoops_PHPIP */

		/* _hoops_ISPR _hoops_RH _hoops_PSSPR _hoops_SGHC */

		_hoops_PCCAR {
			_hoops_HICS	_hoops_HHPIP = path;

			if (_hoops_GIPIA->type == _hoops_AGRPR) {
				_hoops_PGRPR const *		include = (_hoops_PGRPR const *)_hoops_GIPIA;
				_hoops_SRCP = include->_hoops_IGRPR;
				_hoops_HHPIP._hoops_IACHA (include, dc);
			}
			else
				_hoops_SRCP = (_hoops_CRCP const *)_hoops_GIPIA;

			if (!BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CPPGP)) {
				if ((_hoops_GIPIA = _hoops_GIPIA->next) == null)
					return true;
			}
			else if (!ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|
											 _hoops_IIHGP|
											 _hoops_CIHGP)) {
				if ((_hoops_GIPIA = _hoops_GIPIA->next) == null) {
					path = _hoops_HHPIP;
					goto top;
				}
				if (!_hoops_RPPIP (dc, _hoops_SRCP, _hoops_HHPIP, _hoops_PPPIP))
					return false;
			}
			else if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) &&
					 !BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP)) {
				/* _hoops_SSPC _hoops_GRAA-_hoops_RRH _hoops_SPHGR */
				if ((_hoops_GIPIA = _hoops_GIPIA->next) == null)
					return true;
			}
			else if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_IIHGP)) {
				if ((_hoops_GIPIA = _hoops_GIPIA->next) == null) {
					path = _hoops_HHPIP;
					_hoops_PPPIP = true;
					goto top;
				}
				if (!_hoops_RPPIP (dc, _hoops_SRCP, _hoops_HHPIP, true))
					return false;
			}
			else if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_CIHGP)) {
				if ((_hoops_GIPIA = _hoops_GIPIA->next) == null) {
					path = _hoops_HHPIP;
					_hoops_PPPIP = false;
					goto top;
				}
				if (!_hoops_RPPIP (dc, _hoops_SRCP, _hoops_HHPIP, false))
					return false;
			}
			else {
				if ((_hoops_GIPIA = _hoops_GIPIA->next) == null) {
					path = _hoops_HHPIP;
					goto top;
				}
				if (!_hoops_RPPIP (dc, _hoops_SRCP, _hoops_HHPIP, _hoops_PPPIP))
					return false;
			}
		}
	}
}
#endif


local void _hoops_IHPIP (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path,
	bool						_hoops_CHPIP,
	bool						_hoops_SHPIP) {
	Display_Context alter *		dc;
	_hoops_HHCR			_hoops_IHCR;
	_hoops_CGRA			_hoops_SGRA;
	_hoops_HRPA					_hoops_RHSPR;
	bool						_hoops_GIPIP = false;

	dc = (Display_Context alter *)nr->_hoops_SRA;

	HD_Undo_Screen (nr, &_hoops_RHSPR);

	_hoops_IHCR = nr.Modify()->transform_rendition.Modify();
	_hoops_SGRA = nr->_hoops_SAIR.Modify();

	/* _hoops_GA'_hoops_RA _hoops_SHAC _hoops_CCA _hoops_SS _hoops_RPP _hoops_SR _hoops_CHR _hoops_GGR _hoops_RH _hoops_IRGP _hoops_IIGR _hoops_IRS _hoops_GHSHA */
	if (dc->_hoops_APHHP == null)
		HD_Find_Lights (nr, _hoops_SRCP);
	HD_Find_Cutting_Planes (nr, _hoops_SRCP);

	/* (_hoops_SPS _hoops_RPGP _hoops_SPASR _hoops_GRHGP _hoops_GGR _hoops_RIPIP) */
	if (nr->_hoops_IHA->_hoops_AGP != null &&
		BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES) ||
		nr->_hoops_RHP->_hoops_AGP != null &&
		BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES) ||
		nr->_hoops_SCP->_hoops_AGP != null &&
		BIT (nr->_hoops_RGP, T_LIGHTS_FOR_MARKERS))
		nr->_hoops_RCSHR |= _hoops_SARIP;
	else
		nr->_hoops_RCSHR &= ~_hoops_SARIP;

	if (nr->_hoops_IRR->_hoops_SRI != _hoops_PRAAP &&
		BIT (_hoops_IHCR->heuristics, _hoops_IRI) &&
		nr->_hoops_CPP->_hoops_PRH.style != _hoops_AIII &&
		nr->_hoops_CPP->_hoops_PRH.style != _hoops_GCPI &&
		!BIT (nr->_hoops_IRR->_hoops_GSSIR,
				_hoops_RSRAP) &&
		!BIT (nr->_hoops_RCSHR, _hoops_AIPIP) &&
		(BIT (nr->_hoops_RCSHR, _hoops_AHIHP) ||	 /* _hoops_IRS _hoops_RRSS */
		 _hoops_SRCP->_hoops_IGCCA > 0 || _hoops_SRCP->_hoops_SHGSA() > 0 ||
		 HOOPS_WORLD->_hoops_ACPIR > 0)) {	/* _hoops_PIPIP _hoops_GH */

		/* _hoops_SR _hoops_RRP _hoops_HHH _hoops_CGGAR _hoops_IIGR _hoops_SSH _hoops_SRHR.  _hoops_SGH _hoops_HIPIP _hoops_RPP _hoops_HGRC, _hoops_IAII
		 * _hoops_SGH _hoops_GSIA _hoops_RPP _hoops_HHPA, _hoops_HIPIP _hoops_RPP _hoops_HAR
		 */
		if (nr->_hoops_IRR->_hoops_SRI != _hoops_RRAAP &&
			BIT(dc->flags, _hoops_IIPIP) &&
			!BIT(dc->flags, _hoops_AASHP))
			nr->_hoops_RCSHR |= _hoops_CSGGR|_hoops_GSSHP;
		else
			nr->_hoops_RCSHR |= _hoops_CSGGR|_hoops_RSSHP;

		/*
		 * _hoops_IHIR _hoops_AIIAP!...
		 * _hoops_IPCP _hoops_HISRA _hoops_IGRH _hoops_IHIGR _hoops_SSHSR _hoops_CIPIP _hoops_PHPS _hoops_CPHP _hoops_PII _hoops_HHCI _hoops_IHCI
		 * _hoops_IS _hoops_SIPIP _hoops_RH _hoops_GCPIP _hoops_HIAC _hoops_IHIR _hoops_SHPR _hoops_AIIAP.
		 * _hoops_SPCA _hoops_HRGR _hoops_PSP _hoops_RRP _hoops_IH _hoops_IHSP _hoops_IS _hoops_RCPIP _hoops_ACPIP _hoops_PCPIP, _hoops_HGRRA,
		 * _hoops_HIS _hoops_IRAA _hoops_SGGR _hoops_RH _hoops_HCPIP _hoops_IGRH.
		 */
		if (ANYBIT (dc->_hoops_CPGPR, _hoops_APPGP|
								   _hoops_ICHPA|
								   _hoops_PPPGP|
								   _hoops_HPPGP|
								   _hoops_CPPGP|
								   _hoops_RHPGP|
								   _hoops_SIGPR) &&
			!BIT (nr->_hoops_IRR->_hoops_GSSIR,
				  _hoops_GSRAP))
			dc->_hoops_CPGPR |= (_hoops_RAGGA & ~_hoops_AASCA);
	}
	else if (nr->_hoops_IRR->_hoops_SRI == _hoops_PRAAP &&
			 ANYBIT (dc->_hoops_CPGPR, _hoops_ICHPA|
								   _hoops_HPPGP|
								   _hoops_RIPGP)) {
		dc->_hoops_CPGPR |= _hoops_RAGGA|_hoops_APPGP|_hoops_RPSIR;
	}


	if (BIT(dc->flags, _hoops_ICPGR)) {
		if (ANYBIT (dc->_hoops_CPGPR, _hoops_APPGP|
								   _hoops_ICHPA|
								   _hoops_PPPGP|
								   _hoops_HPPGP|
								   _hoops_CPPGP|
								   _hoops_RHPGP|
								   _hoops_SIGPR)) {
			dc->_hoops_CPGPR |= (_hoops_RAGGA & ~_hoops_AASCA);
			/* _hoops_ICPIP _hoops_SSHGR _hoops_RGRIR _hoops_CCPIP _hoops_RPP _hoops_IAGIP, _hoops_HIS _hoops_SR _hoops_HS _hoops_IS _hoops_IRHH
			   _hoops_RCRR _hoops_RH _hoops_HCH _hoops_GPP _hoops_RH _hoops_SHSC _hoops_RPPS _hoops_HRGR _hoops_APIP, _hoops_HAR _hoops_SAHR _hoops_ISCP _hoops_RSCA _hoops_CPSRR */
			if (BIT (dc->_hoops_CPGPR, _hoops_IHPGP) &&
				(nr->_hoops_IRR->_hoops_SRI == _hoops_SICI ||
				!ANYBIT (nr->_hoops_RCSHR, _hoops_RSSHP|_hoops_CISHP)))
				dc->_hoops_CPGPR |= _hoops_AASCA;

			dc->flags &= ~_hoops_ICPGR;
		}
	}

	if (_hoops_IHCR->_hoops_RGH != null &&
		BIT (nr->_hoops_RGP, T_CUTTING_PLANES))
		nr->_hoops_RCSHR |= _hoops_GPRIP;
	else
		nr->_hoops_RCSHR &= ~_hoops_GPRIP;

	/* _hoops_RPP _hoops_RH _hoops_HRCSR _hoops_CSAP _hoops_GGR '_hoops_SCPIP' _hoops_PSCR _hoops_SR _hoops_PAHH _hoops_HS _hoops_IS _hoops_ASAR-_hoops_SRSHR _hoops_RH _hoops_GSPIP. */
	if (nr->_hoops_SISI->_hoops_GHGRP == GSU_WRU ||
		nr->_hoops_SISI->_hoops_SSPAP == GSU_WRU)
		nr->_hoops_SISI->_hoops_SRRIP();

	/* _hoops_PSHR _hoops_IH '_hoops_RSPIP' */
	if (nr->_hoops_SISI->_hoops_GHGRP == GSU_ORU ||
		nr->_hoops_SISI->_hoops_GHGRP == _hoops_SPSC ||
		nr->_hoops_SISI->_hoops_SSPAP == GSU_ORU ||
		nr->_hoops_SISI->_hoops_SSPAP == _hoops_SPSC)
		nr->_hoops_SISI->_hoops_SRRIP();

	if (_hoops_CAPIP (dc, _hoops_SRCP, _hoops_CPPGP) &&
		!BIT (dc->_hoops_CPGPR, _hoops_APPGP)) {
		/* _hoops_AGSGR _hoops_IASI _hoops_AHPIP _hoops_CRGR _hoops_IHIR _hoops_AIIAP _hoops_RPP _hoops_HAR _hoops_RSRA-_hoops_ACHGR */
		/* _hoops_PAR _hoops_RPP _hoops_RH _hoops_CSHHR _hoops_GPGH'_hoops_RA _hoops_IGRC _hoops_IHPPP _hoops_GPP */

#ifndef DISABLE_PARTIAL_ERASE
		if (dc->options._hoops_SRRRR &&
			dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA ||
			!_hoops_RPPIP (dc, _hoops_SRCP, path, BIT (_hoops_IHCR->heuristics, _hoops_PRIRP)))
#endif
			dc->_hoops_CPGPR |= _hoops_GAGSA & ~_hoops_AASCA;
	}

	if (BIT (dc->_hoops_CPGPR, _hoops_AASCA) ||
		BIT (_hoops_IHCR->flags, _hoops_ASPIP) ||
		!_hoops_CAPIP (dc, _hoops_SRCP, _hoops_GHPGP)) {
		HD_Compute_Hard_Clip (nr, null);
	}
	else if (BIT (dc->_hoops_CPGPR, _hoops_RIPGP)) {
		dc->_hoops_CPGPR |= _hoops_AASCA;
		HD_Compute_Hard_Clip (nr, null);
	}
	else {
		_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);

		if (_hoops_CSC != null &&
			 _hoops_CSC->_hoops_PSSIR() != null &&
			 _hoops_CSC->_hoops_PSSIR()->_hoops_PSPIP) {
			Window const			*window;

			window = HI_Find_Scoping_Window ((_hoops_CRCP alter *)_hoops_SRCP);

			if (!(dc->options._hoops_SRRRR &&
				  dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA &&
				  BIT (_hoops_SRCP->_hoops_SPGPR, _hoops_GHPGP)))/* _hoops_SAHR _hoops_CCAH */
				HD_Compute_Hard_Clip (nr, &window->_hoops_ISGPR);
			else {	/* _hoops_GIPR */

				/**** _hoops_RCSPR _hoops_HSPIP _hoops_ISPIP _hoops_ACGPA _hoops_CSPIP _hoops_SSPIP _hoops_GGHIP _hoops_RGHIP _hoops_AGHIP! ***/
				_hoops_PACIR	_hoops_PGHIP = window->_hoops_ISGPR;
				_hoops_PGHIP._hoops_AACIR(window->_hoops_HSGPR);
				HD_Compute_Hard_Clip (nr, &_hoops_PGHIP);
			}
		}
		else {		/* _hoops_RCIPR _hoops_RIPIR _hoops_GGSR _hoops_IRS _hoops_CPSRR _hoops_PPR _hoops_IHSH _hoops_HPGR _hoops_SCH */
			Window const			*window;

			window = HI_Find_Scoping_Window ((_hoops_CRCP alter *)_hoops_SRCP);
			if (!BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_GHPGP))			/* _hoops_SAHR _hoops_RHGS */
				HD_Compute_Hard_Clip (nr, &window->_hoops_HSGPR);
			else if (!(dc->options._hoops_SRRRR &&
					   dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA &&
					   BIT (_hoops_SRCP->_hoops_SPGPR, _hoops_GHPGP)))/* _hoops_SAHR _hoops_CCAH */
				HD_Compute_Hard_Clip (nr, &window->_hoops_ISGPR);
			else {	/* _hoops_GIPR */

				/**** _hoops_RCSPR _hoops_HSPIP _hoops_ISPIP _hoops_ACGPA _hoops_CSPIP _hoops_SSPIP _hoops_GGHIP _hoops_RGHIP _hoops_AGHIP! ***/
				_hoops_PACIR	_hoops_PGHIP = window->_hoops_ISGPR;
				_hoops_PGHIP._hoops_AACIR(window->_hoops_HSGPR);
				HD_Compute_Hard_Clip (nr, &_hoops_PGHIP);
			}

			/* _hoops_RH _hoops_CPSRR _hoops_CSAP _hoops_GPP _hoops_RGR _hoops_RPPS,
			** _hoops_HGHIP _hoops_GHCA _hoops_HAR _hoops_HS _hoops_PAII _hoops_HAII _hoops_CPSRR
			*/
			dc->_hoops_CPGPR &= ~_hoops_GHPGP;
			dc->_hoops_CPGPR |= _hoops_AASCA;
		}
	}

	/* _hoops_SHH _hoops_RHRIR _hoops_GICS _hoops_RAS _hoops_IGHIP */
	_hoops_IHCR = nr->transform_rendition;
	_hoops_SGRA = nr->_hoops_SAIR;

	_hoops_IHCR->flags &= ~_hoops_AIHS;

	if (BIT (_hoops_IHCR->flags, _hoops_CGHIP)) {
		/* _hoops_CPHP _hoops_IS _hoops_PGSA _hoops_GCAS */

		/* _hoops_SIAS _hoops_HAR _hoops_HS _hoops_PA _hoops_HII _hoops_PGAP _hoops_SR _hoops_PAH _hoops_SGHIP */
		if (BIT (dc->_hoops_CPGPR, _hoops_IHPGP) &&
			(nr->_hoops_IRR->_hoops_SRI == _hoops_SICI ||
			 (!ANYBIT (nr->_hoops_RCSHR, _hoops_RSSHP|_hoops_CISHP) &&
				!_hoops_CHPIP))) {
			dc->_hoops_CPGPR &= ~_hoops_SCCCA;
			dc->_hoops_CPGPR |= _hoops_RCGSA;
			HD_Compute_Hard_Clip (nr, null);
			_hoops_IHCR = nr->transform_rendition;
			_hoops_SGRA = nr->_hoops_SAIR;
		}

		/* _hoops_AA _hoops_GII _hoops_GRHIP _hoops_HA! */
		if (BIT (_hoops_SGRA->_hoops_ASIHP, _hoops_AIARP)) {
			bool		_hoops_RRHIP = true;

			if (!_hoops_SHPIP &&
				BIT (dc->_hoops_CPGPR, _hoops_PPPGP) &&
			    dc->_hoops_APHHP == null &&
			    (!BIT (nr->_hoops_RCSHR, _hoops_CRSI) || _hoops_SRCP == dc->_hoops_AAHSR))
				_hoops_RRHIP = false;

			_hoops_ARHIP (nr, &_hoops_SGRA->_hoops_PHRA, &_hoops_SGRA->_hoops_RRAIP, _hoops_RRHIP);

			/* _hoops_ARP _hoops_GH _hoops_HACH _hoops_ACIPR _hoops_HSPH _hoops_IH _hoops_CPAP _hoops_ASCA... */
			/* _hoops_ICHRA _hoops_RH _hoops_HCHSR, _hoops_RPP _hoops_HAHH */

			_hoops_SGRA->_hoops_PHRA.left += _hoops_SGRA->_hoops_RRAIP.left;
			_hoops_SGRA->_hoops_PHRA.right -= _hoops_SGRA->_hoops_RRAIP.right;
			_hoops_SGRA->_hoops_PHRA.bottom += _hoops_SGRA->_hoops_RRAIP.bottom;
			_hoops_SGRA->_hoops_PHRA.top -= _hoops_SGRA->_hoops_RRAIP.top;

			if (!BIT(_hoops_SGRA->_hoops_ASIHP, _hoops_CIARP)) {
				_hoops_SGRA->_hoops_CIIH.left	= _hoops_SGRA->_hoops_PHRA.left;
				_hoops_SGRA->_hoops_CIIH.right	= _hoops_SGRA->_hoops_PHRA.right;
				_hoops_SGRA->_hoops_CIIH.bottom	= _hoops_SGRA->_hoops_PHRA.bottom;
				_hoops_SGRA->_hoops_CIIH.top	= _hoops_SGRA->_hoops_PHRA.top;
			}

			/* _hoops_HSIH _hoops_AHHSR _hoops_GGCH */
			if (_hoops_SGRA->_hoops_PHRA.right > _hoops_SGRA->_hoops_PHRA.left)
				_hoops_SGRA->_hoops_CSIH = (float)(_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom) /
							 (float)(_hoops_SGRA->_hoops_CIIH.right - _hoops_SGRA->_hoops_CIIH.left) *
							 dc->current._hoops_AGRS;

			nr->_hoops_CPA = dc->_hoops_GCHHP();		/* _hoops_HIIPA */
			_hoops_IHCR->_hoops_CPA = dc->_hoops_GCHHP();		/* _hoops_HIIPA */

			if (_hoops_IHCR->_hoops_AGAA.left < _hoops_SGRA->_hoops_PHRA.left)
				_hoops_IHCR->_hoops_AGAA.left = _hoops_SGRA->_hoops_PHRA.left;
			if (_hoops_IHCR->_hoops_AGAA.right > _hoops_SGRA->_hoops_PHRA.right)
				_hoops_IHCR->_hoops_AGAA.right = _hoops_SGRA->_hoops_PHRA.right;
			if (_hoops_IHCR->_hoops_AGAA.bottom < _hoops_SGRA->_hoops_PHRA.bottom)
				_hoops_IHCR->_hoops_AGAA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
			if (_hoops_IHCR->_hoops_AGAA.top > _hoops_SGRA->_hoops_PHRA.top)
				_hoops_IHCR->_hoops_AGAA.top = _hoops_SGRA->_hoops_PHRA.top;
		}

		/* _hoops_PGSA _hoops_RH _hoops_RPPS */
		if (!_hoops_SHPIP && ANYBIT (dc->_hoops_CPGPR, _hoops_APPGP | _hoops_PPPGP)) {
			if (_hoops_SRCP != dc->_hoops_AAHSR || dc->options._hoops_GCHSR != 0) {
				_hoops_GIPIP = BIT (dc->_hoops_CPGPR, _hoops_APPGP) &&
								!BIT(_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP);
			}
			else
				_hoops_GIPIP = BIT (dc->_hoops_CPGPR, _hoops_APPGP);

			if (_hoops_GIPIP &&
				(nr->_hoops_ASIR->window.pattern == FP_WINDOW_TRANSPARENT ||
					nr->_hoops_ASIR->window.pattern == FP_WINDOW_TRANS_NO_ZCLEAR))
				_hoops_SAPIP (dc, _hoops_SRCP);

			if (_hoops_GIPIP && !_hoops_SHPIP)
				nr->_hoops_RCSHR |= _hoops_PRHIP;

			_hoops_SGRA->_hoops_ASIHP |= _hoops_GCARP; /* _hoops_APGP, _hoops_HIH _hoops_SCAC _hoops_AHCR _hoops_PSCA _hoops_SHR */

			if (_hoops_GIPIP) {
				_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
				_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);

				if (_hoops_CSC != null && _hoops_CSC->_hoops_PSSIR() != null)
					_hoops_CSC->_hoops_PSSIR()->_hoops_PSPIP = false;
			}

			/* _hoops_IRHH _hoops_RCRR _hoops_HRHIP _hoops_CGHA, _hoops_IRHIP _hoops_AHI _hoops_HRGR _hoops_GPP _hoops_HAH _hoops_HA... */
			if (BIT (dc->_hoops_CPGPR, _hoops_APPGP))
				dc->_hoops_CPGPR |= _hoops_RCGSA &
								~_hoops_AASCA;
		}
	}
	else if (BIT (_hoops_SGRA->_hoops_ASIHP, _hoops_AIARP)) {
		/* _hoops_RRP _hoops_HCHSR _hoops_IISRR _hoops_IH _hoops_PSSPR _hoops_SPHGR */
		if (ANYBIT(dc->_hoops_CPGPR, _hoops_PPPGP) &&
			dc->_hoops_APHHP == null &&
			(!BIT (nr->_hoops_RCSHR, _hoops_CRSI) || _hoops_SRCP == dc->_hoops_AAHSR)) {

			Net_Rendition					_hoops_CRHIP = nr;
			_hoops_HHCR alter &		_hoops_SRHIP = _hoops_CRHIP.Modify()->transform_rendition.Modify();

			_hoops_SRHIP->_hoops_AGAA.left = _hoops_SGRA->_hoops_PHRA.left;
			_hoops_SRHIP->_hoops_AGAA.right = _hoops_SGRA->_hoops_PHRA.right;
			_hoops_SRHIP->_hoops_AGAA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
			_hoops_SRHIP->_hoops_AGAA.top = _hoops_SGRA->_hoops_PHRA.top;
			_hoops_SRHIP->flags |= _hoops_CGHIP;

			_hoops_ARHIP (_hoops_CRHIP, &_hoops_SGRA->_hoops_PHRA, &_hoops_SGRA->_hoops_RRAIP, false);
		}
		else
			_hoops_ARHIP (nr, &_hoops_SGRA->_hoops_PHRA, &_hoops_SGRA->_hoops_RRAIP, true);

		/* _hoops_ARP _hoops_GH _hoops_HACH _hoops_ACIPR _hoops_HSPH _hoops_IH _hoops_CPAP _hoops_ASCA... */
		/* _hoops_ICHRA _hoops_RH _hoops_HCHSR, _hoops_RPP _hoops_HAHH */

		_hoops_SGRA->_hoops_PHRA.left += _hoops_SGRA->_hoops_RRAIP.left;
		_hoops_SGRA->_hoops_PHRA.right -= _hoops_SGRA->_hoops_RRAIP.right;
		_hoops_SGRA->_hoops_PHRA.bottom += _hoops_SGRA->_hoops_RRAIP.bottom;
		_hoops_SGRA->_hoops_PHRA.top -= _hoops_SGRA->_hoops_RRAIP.top;

		if (!BIT(_hoops_SGRA->_hoops_ASIHP, _hoops_CIARP)) {
			_hoops_SGRA->_hoops_CIIH.left	= _hoops_SGRA->_hoops_PHRA.left;
			_hoops_SGRA->_hoops_CIIH.right	= _hoops_SGRA->_hoops_PHRA.right;
			_hoops_SGRA->_hoops_CIIH.bottom	= _hoops_SGRA->_hoops_PHRA.bottom;
			_hoops_SGRA->_hoops_CIIH.top	= _hoops_SGRA->_hoops_PHRA.top;
		}

		if (_hoops_IHCR->_hoops_AGAA.left < _hoops_SGRA->_hoops_PHRA.left)
			_hoops_IHCR->_hoops_AGAA.left = _hoops_SGRA->_hoops_PHRA.left;
		if (_hoops_IHCR->_hoops_AGAA.right > _hoops_SGRA->_hoops_PHRA.right)
			_hoops_IHCR->_hoops_AGAA.right = _hoops_SGRA->_hoops_PHRA.right;
		if (_hoops_IHCR->_hoops_AGAA.bottom < _hoops_SGRA->_hoops_PHRA.bottom)
			_hoops_IHCR->_hoops_AGAA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
		if (_hoops_IHCR->_hoops_AGAA.top > _hoops_SGRA->_hoops_PHRA.top)
			_hoops_IHCR->_hoops_AGAA.top = _hoops_SGRA->_hoops_PHRA.top;
	}



	if (!nr->_hoops_ASIR->window._hoops_RARIP || _hoops_SRCP == dc->_hoops_AAHSR) {
		_hoops_SGRA->_hoops_GAHIP.left	= _hoops_SGRA->_hoops_PHRA.left;
		_hoops_SGRA->_hoops_GAHIP.right	= _hoops_SGRA->_hoops_PHRA.right;
		_hoops_SGRA->_hoops_GAHIP.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
		_hoops_SGRA->_hoops_GAHIP.top	= _hoops_SGRA->_hoops_PHRA.top;
	}

	if (!BIT (dc->_hoops_CPGPR, _hoops_ICHPA) &&
		!_hoops_CAPIP (dc, _hoops_SRCP, _hoops_HPPGP)) {
		/* _hoops_IRHH _hoops_RCRR _hoops_RGR _hoops_ASSP'_hoops_RA _hoops_SAHR _hoops_RAHIP _hoops_ISHP _hoops_CRGR _hoops_RH _hoops_CCAH _hoops_RPPS */
		dc->_hoops_CPGPR &= ~_hoops_HPPGP;
	}

	if (!BIT (_hoops_IHCR->flags, _hoops_CGHIP) ||
		_hoops_IHCR->_hoops_AGAA.left > _hoops_IHCR->_hoops_AGAA.right ||
		_hoops_IHCR->_hoops_AGAA.bottom > _hoops_IHCR->_hoops_AGAA.top) {
		_hoops_IHCR->flags &= ~(_hoops_CGHIP|_hoops_ASPIP);
	}
	else if (ANYBIT (dc->_hoops_CPGPR, _hoops_HPPGP|_hoops_RIPGP|_hoops_CHPGP)) {
		/* _hoops_ASCA/_hoops_AAHIP _hoops_HHH _hoops_CPAP! */

		_hoops_IHCR->flags |= _hoops_PRAIP; /* _hoops_IRHH _hoops_RCRR */

		/* _hoops_IRHH _hoops_RCRR _hoops_SPHGR _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_SIGSA _hoops_CPAP _hoops_HGCR _hoops_RHHR */
		dc->_hoops_CPGPR |= _hoops_IHPGP|_hoops_PPPGP;
	}
	else if (BIT (dc->_hoops_CPGPR, _hoops_IHPGP)) {
		/* _hoops_PAHIP _hoops_HHH _hoops_CPAP */
		_hoops_IHCR->flags |= _hoops_PRAIP; /* _hoops_IRHH _hoops_RCRR */

		/* _hoops_IRHH _hoops_RCRR _hoops_SPHGR _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_SIGSA _hoops_CPAP _hoops_HAHIP _hoops_RPIHR _hoops_HAH */
		dc->_hoops_CPGPR |= _hoops_PPPGP;
	}


	HD_Redo_Screen (nr, &_hoops_RHSPR);

	nr->_hoops_RCSHR &= ~_hoops_CRHPP;

	if ((*nr->transform_rendition->_hoops_SPH->_hoops_SIPCR < 0.0f ||
		*nr->transform_rendition->_hoops_SPH->_hoops_SIPCR == 0.0f && _hoops_GIPHP < 0.0f)) {
		HD_Adjust_WLimit (nr, _hoops_SRCP, path);
	}

	float	width = nr->_hoops_SAIR->_hoops_PHRA.right - nr->_hoops_SAIR->_hoops_PHRA.left;
	_hoops_IHCR->_hoops_HIPHP = width / _hoops_IHCR->_hoops_SPH->_hoops_ISPA;
	if (width > 0.0f)
		_hoops_IHCR->_hoops_IIPHP = _hoops_IHCR->_hoops_SPH->_hoops_ISPA / width;
	else
		_hoops_IHCR->_hoops_IIPHP = 1.0e9f;

	/* _hoops_SHR _hoops_HS _hoops_IRS _hoops_CAGH _hoops_IHAH _hoops_HPGR _hoops_RH _hoops_RPPS _hoops_PAPA */
	_hoops_SGRA->_hoops_ASSIR = HI_Find_Segment_Cache (_hoops_SRCP, path);

	/* _hoops_HCR _hoops_ARP _hoops_GH _hoops_IH _hoops_RPPS _hoops_CPGGR _hoops_HA */
}


GLOBAL_FUNCTION void HD_Search_Null_Clip_Tree (
	Net_Rendition const &		inr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		_hoops_IAHIP,
	Activity					_hoops_CAHIP,
	bool						_hoops_SAHIP) {
	_hoops_HICS				path = _hoops_IAHIP;
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

  top:;

	/* _hoops_PCACR _hoops_IHSH _hoops_IH _hoops_PSSPR _hoops_SPHGR _hoops_SGS _hoops_HS _hoops_IRS _hoops_CIGGR _hoops_CPSRR -
	 * _hoops_RH _hoops_SCGR _hoops_AIIAP _hoops_CPSRR _hoops_AICS _hoops_GGSR _hoops_IS _hoops_SHH _hoops_IRAP.
	 */

	/* _hoops_SPIC _hoops_ISHP _hoops_HSPR _hoops_RH _hoops_GPHIP _hoops_PPR _hoops_SGHGP._hoops_ASHHP
	 * _hoops_SGI _hoops_CCGR _hoops_IRS _hoops_AISIR _hoops_CAGH _hoops_HRGR _hoops_GSGI _hoops_CCA _hoops_IRS _hoops_CIGGR _hoops_CPSRR.
	 */

	{
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);

		if (nr->_hoops_SAIR->_hoops_ASSIR == null && _hoops_CSC != null) {
			nr->_hoops_SAIR->_hoops_ASSIR = _hoops_CSC;
		}
	}

	if (_hoops_SRCP == dc->_hoops_AAHSR ||
		BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) && !nr->_hoops_ASIR->window._hoops_RARIP) {
		_hoops_CGRA alter &	_hoops_SGRA = nr->_hoops_SAIR;

		_hoops_SGRA->_hoops_GAHIP.left	= _hoops_SGRA->_hoops_PHRA.left;
		_hoops_SGRA->_hoops_GAHIP.right	= _hoops_SGRA->_hoops_PHRA.right;
		_hoops_SGRA->_hoops_GAHIP.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
		_hoops_SGRA->_hoops_GAHIP.top	= _hoops_SGRA->_hoops_PHRA.top;
	}

	/* _hoops_RH _hoops_HSPR _hoops_HRGR _hoops_IRS _hoops_AHAAR _hoops_CSPP _hoops_IIGR _hoops_RPHIP */

	if (_hoops_SRCP->_hoops_RGRPR != null) {
		Subsegment const *		_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR;

		do {
			_hoops_HICS	_hoops_HHPIP = path;
			Activity		_hoops_APHIP;

			if (_hoops_SSGPR->type == _hoops_AGRPR) {
				_hoops_SRCP = ((_hoops_PGRPR const *)_hoops_SSGPR)->_hoops_IGRPR;
				_hoops_HHPIP._hoops_IACHA ((_hoops_PGRPR *)_hoops_SSGPR, dc);
			}
			else
				_hoops_SRCP = (_hoops_CRCP const *)_hoops_SSGPR;

			_hoops_APHIP = _hoops_SRCP->_hoops_CPGPR | _hoops_CAHIP;
			if (dc->options._hoops_SRRRR &&
				dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA)
				_hoops_APHIP |= _hoops_SRCP->_hoops_SPGPR &
								  ~(_hoops_CSCCA|
									_hoops_PISSR);


			 if (BIT (_hoops_APHIP, _hoops_RIPGP)) {
				_hoops_APHIP |= _hoops_IPPGP|_hoops_IHPGP;
			 }

			/* _hoops_HRGR _hoops_IIH _hoops_IRS _hoops_SCPC _hoops_IS _hoops_PHHR _hoops_CRGR _hoops_SCH? (_hoops_RHCA _hoops_HRGHR _hoops_HA!) */

			if (BIT(dc->_hoops_CPGPR, _hoops_CHPGP) ||
				!(BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) &&
				  (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GCHGP) ||
				   (!BIT (nr->_hoops_RGP, T_WINDOWS) &&
					!BIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPHGP)))) &&

				/* (_hoops_SCH _hoops_ASSP'_hoops_RA _hoops_AHGS _hoops_IS _hoops_SHH _hoops_PCCP _hoops_PSIPR _hoops_RPPS) */

				(BIT (_hoops_APHIP, _hoops_IPPGP) &&
				 (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) ||
				  ANYBIT (_hoops_SRCP->_hoops_RCGC, T_WINDOWS|_hoops_AHASA)) &&
				 (BIT (nr->_hoops_RGP, T_WINDOWS) ||
				  ANYBIT (_hoops_SRCP->_hoops_RCGC, _hoops_HPHGP|_hoops_AHASA)))

				/* (_hoops_PAR _hoops_GGHP _hoops_PCCP _hoops_RHPA _hoops_RPPS _hoops_IS _hoops_PGSA - _hoops_GAAP) */
				) {
				Net_Rendition		_hoops_PPHIP = nr;

				if (_hoops_GGPGR(nr))
					break; /* _hoops_HRGHP! */

				if (_hoops_SRCP->_hoops_IPPGR != null) {
					_hoops_HHRA const *		_hoops_HPHIP = _hoops_PPHIP->transform_rendition->_hoops_SPH;

					HD_Downwind_Rendition (_hoops_PPHIP, _hoops_SRCP->_hoops_IPPGR, _hoops_SRCP->_hoops_RCGC, true);

					if (!BIT(dc->flags, _hoops_IRSI) &&
						(_hoops_PPHIP->transform_rendition->_hoops_SPH != _hoops_HPHIP ||
							BIT(_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) &&
						(*_hoops_PPHIP->transform_rendition->_hoops_SPH->_hoops_SIPCR < 0.0f ||
						*_hoops_PPHIP->transform_rendition->_hoops_SPH->_hoops_SIPCR == 0.0f && _hoops_GIPHP < 0.0f)) {

						HD_Adjust_WLimit (_hoops_PPHIP, _hoops_SRCP, _hoops_HHPIP);
					}
				}


				if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA|_hoops_RIGSA) ||
					BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) && !_hoops_SAHIP) {
					Activity			_hoops_IPHIP = dc->_hoops_CPGPR;
					//_hoops_CPHIP *			_hoops_SPHIP = _hoops_CSPH->_hoops_GHHIP;

					if (ANYBIT (_hoops_SRCP->_hoops_PHSI,_hoops_GIGSA|_hoops_RIGSA) ||
						(BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) && !_hoops_SAHIP &&
						 ANYBIT(_hoops_APHIP, _hoops_ICHPA|_hoops_APPGP))) {

						if (!BIT (_hoops_PPHIP->transform_rendition->flags, _hoops_CGHIP)) {
							_hoops_HHCR alter &		_hoops_GGCC = _hoops_PPHIP.Modify()->transform_rendition.Modify();
							_hoops_CGRA const &		_hoops_SGRA = _hoops_PPHIP->_hoops_SAIR;

							_hoops_GGCC->_hoops_AGAA.left = _hoops_SGRA->_hoops_PHRA.left;
							_hoops_GGCC->_hoops_AGAA.right = _hoops_SGRA->_hoops_PHRA.right;
							_hoops_GGCC->_hoops_AGAA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
							_hoops_GGCC->_hoops_AGAA.top = _hoops_SGRA->_hoops_PHRA.top;
							_hoops_GGCC->flags |= _hoops_CGHIP;
						}
					}

					dc->_hoops_CPGPR = _hoops_APHIP;
					//_hoops_CSPH->_hoops_GHHIP = _hoops_IRAP;
					//_hoops_CSPH->_hoops_RHHIP (_hoops_AHHIP, _hoops_PHHIP);
					//_hoops_CSPH->_hoops_GHHIP->_hoops_CRAA = _hoops_HHHIP;
					_hoops_AASS (_hoops_PPHIP, _hoops_SRCP, _hoops_HHPIP);
					//_hoops_CSPH->_hoops_GHHIP = _hoops_SPHIP;
					dc->_hoops_CPGPR = _hoops_IPHIP;
				}
				else {
					if (BIT(_hoops_PPHIP->flags, _hoops_SPSHP))
						_hoops_PPHIP.Modify()->flags &= ~_hoops_SPSHP;

					if (_hoops_SSGPR->next == null) {/* _hoops_AA _hoops_RIRP _hoops_PAGIR */
						nr = _hoops_PPHIP;
						path = _hoops_HHPIP;
						goto top;
					}
					else
						HD_Search_Null_Clip_Tree (_hoops_PPHIP, _hoops_SRCP, _hoops_HHPIP, _hoops_CAHIP, _hoops_SAHIP); /* _hoops_GHHA! */
				}
			}
		} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);
	}
}


local RGB _hoops_IHHIP (
	 Net_Rendition const &		nr,
	 Driver_Color const &		specific) {
	 Display_Context const *	dc = nr->_hoops_SRA;
	 RGB						color;

	 if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR)
		color = (RGBAS32 const &)specific._hoops_HRIR;
	 else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_RIIHP)
		 color = RGB (specific._hoops_PIHHP / (dc->_hoops_PGCC._hoops_PCHSR - 1));
	 else if (dc->_hoops_CHHIP != null)
		color = dc->_hoops_CHHIP[specific._hoops_PGGCR];
	 else
		 color = _hoops_GPSR::_hoops_RPSR;

	 return color;
}



/* _hoops_RPP _hoops_SR _hoops_CHR _hoops_GGR _hoops_IRS _hoops_CIAGR _hoops_GRH _hoops_CAPRR (_hoops_IAS._hoops_ISHI. _hoops_SHHIP="_hoops_HHSA _hoops_GIHIP" _hoops_PAR "_hoops_IISI=_hoops_ICSI _hoops_CCSI"),
 * _hoops_SR _hoops_GHCA _hoops_RRP _hoops_AIRC _hoops_SGS _hoops_RIHIP _hoops_HII _hoops_PCPA _hoops_CHH _hoops_IAII _hoops_SHH _hoops_RH _hoops_GHPP _hoops_IIGR
 * _hoops_IPP _hoops_AIHIP */
GLOBAL_FUNCTION void HD_Fixup_Attributes (
	Net_Rendition alter & 		nr,
	_hoops_PIGRA const *		locks,
	int							flags) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;
	bool						_hoops_GAHHP = BIT (_hoops_PHAH.options, _hoops_CHRH);

	if (nr->_hoops_IRR->_hoops_SRI == _hoops_SICI &&
		BIT(nr->transform_rendition->flags , _hoops_PIHIP)) {
		/* _hoops_ARP _hoops_GH _hoops_AIRC _hoops_IH _hoops_GII "_hoops_CCSHP" _hoops_IGCGA */
		if (BIT(flags, _hoops_PHIHP) &&
			!BIT(nr->flags, _hoops_PHIHP)) {
			float			_hoops_IHCRP = nr->_hoops_ASIR->_hoops_GCCI._hoops_IHCRP;
			RGB				_hoops_HIHIP, _hoops_IIHIP;

			_hoops_IIHIP = RGB (_hoops_CIHIP(nr),
						_hoops_SIHIP(nr),
						_hoops_GCHIP(nr));

			if (nr->_hoops_SAIR->_hoops_CGAIP >= FP_WINDOW_FIRST_GRADIENT &&
				nr->_hoops_SAIR->_hoops_CGAIP <= FP_WINDOW_LAST_GRADIENT) {
				_hoops_IIHIP.red   += (float)_hoops_RCHIP(nr);
				_hoops_IIHIP.green += (float)_hoops_ACHIP(nr);
				_hoops_IIHIP.blue  += (float)_hoops_PCHIP(nr);
				_hoops_IIHIP.red   *= 0.5f;
				_hoops_IIHIP.green *= 0.5f;
				_hoops_IIHIP.blue  *= 0.5f;
			}

			/* _hoops_APGR */
			if (BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_SPCRP)) {
				_hoops_HIHIP = nr->_hoops_ASIR->_hoops_GCCI.color;
			}
			else {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_AHP->_hoops_SCHHP, r, red),
							_hoops_HCHIP(nr, _hoops_AHP->_hoops_SCHHP, g, green),
							_hoops_HCHIP(nr, _hoops_AHP->_hoops_SCHHP, b, blue));
			}
			_hoops_HIHIP.red   += (_hoops_IIHIP.red	  - _hoops_HIHIP.red) * _hoops_IHCRP;
			_hoops_HIHIP.green += (_hoops_IIHIP.green - _hoops_HIHIP.green) * _hoops_IHCRP;
			_hoops_HIHIP.blue  += (_hoops_IIHIP.blue  - _hoops_HIHIP.blue) * _hoops_IHCRP;
			_hoops_ICHIP (nr, &_hoops_HIHIP, false);

			/* _hoops_SPPR */
			if (BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_SPCRP)) {
				_hoops_HIHIP = nr->_hoops_ASIR->_hoops_GCCI.color;
			}
			else {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_RHP->_hoops_SCHHP, r, red),
							_hoops_HCHIP(nr, _hoops_RHP->_hoops_SCHHP, g, green),
							_hoops_HCHIP(nr, _hoops_RHP->_hoops_SCHHP, b, blue));
			}
			_hoops_HIHIP.red   += (_hoops_IIHIP.red	  - _hoops_HIHIP.red) * _hoops_IHCRP;
			_hoops_HIHIP.green += (_hoops_IIHIP.green - _hoops_HIHIP.green) * _hoops_IHCRP;
			_hoops_HIHIP.blue  += (_hoops_IIHIP.blue  - _hoops_HIHIP.blue) * _hoops_IHCRP;
			_hoops_CCHIP (nr, &_hoops_HIHIP, false);

			/* _hoops_RSSI */
			_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_IHA->_hoops_SCHHP, r, red),
						_hoops_HCHIP(nr, _hoops_IHA->_hoops_SCHHP, g, green),
						_hoops_HCHIP(nr, _hoops_IHA->_hoops_SCHHP, b, blue));
			_hoops_HIHIP.red   += (_hoops_IIHIP.red	  - _hoops_HIHIP.red) * _hoops_IHCRP;
			_hoops_HIHIP.green += (_hoops_IIHIP.green - _hoops_HIHIP.green) * _hoops_IHCRP;
			_hoops_HIHIP.blue  += (_hoops_IIHIP.blue  - _hoops_HIHIP.blue) * _hoops_IHCRP;
			_hoops_SCHIP (nr, &_hoops_HIHIP, false);

			/* _hoops_SAIA */
			_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_GSP->_hoops_SCHHP, r, red),
						_hoops_HCHIP(nr, _hoops_GSP->_hoops_SCHHP, g, green),
						_hoops_HCHIP(nr, _hoops_GSP->_hoops_SCHHP, b, blue));
			_hoops_HIHIP.red   += (_hoops_IIHIP.red	  - _hoops_HIHIP.red) * _hoops_IHCRP;
			_hoops_HIHIP.green += (_hoops_IIHIP.green - _hoops_HIHIP.green) * _hoops_IHCRP;
			_hoops_HIHIP.blue  += (_hoops_IIHIP.blue  - _hoops_HIHIP.blue) * _hoops_IHCRP;
			_hoops_GSHIP (nr, &_hoops_HIHIP, false);

			/* _hoops_HCGR */
			_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_SISI->_hoops_SCHHP, r, red),
						_hoops_HCHIP(nr, _hoops_SISI->_hoops_SCHHP, g, green),
						_hoops_HCHIP(nr, _hoops_SISI->_hoops_SCHHP, b, blue));
			_hoops_HIHIP.red   += (_hoops_IIHIP.red	  - _hoops_HIHIP.red) * _hoops_IHCRP;
			_hoops_HIHIP.green += (_hoops_IIHIP.green - _hoops_HIHIP.green) * _hoops_IHCRP;
			_hoops_HIHIP.blue  += (_hoops_IIHIP.blue  - _hoops_HIHIP.blue) * _hoops_IHCRP;
			_hoops_RSHIP(nr, &_hoops_HIHIP, false);

			// _hoops_GRPHA _hoops_CRHPR _hoops_CCAH _hoops_SCII
			nr->flags |= _hoops_PHIHP;
			nr->flags &= ~_hoops_HHIHP;
		}

		if (BIT(flags, _hoops_ACSHP) &&
			!BIT(nr->flags, _hoops_ACSHP)) {
			/* _hoops_PAIA */
			Line_Style const &	line_style = nr->_hoops_ASIR->_hoops_GCCI.line_style;

			nr.Modify()->_hoops_AHP.Modify()->line_style = line_style;
			nr->_hoops_RHP.Modify()->line_style = line_style;

			nr->flags |= _hoops_ACSHP;
		}


		if (BIT(flags, _hoops_IPIHP) &&
			!BIT(nr->flags, _hoops_IPIHP)) {
			/* _hoops_RGSGR */
			if (!BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RCCI)) {
				/* _hoops_PSP _hoops_CCSHP _hoops_CIPH _hoops_IPIH _hoops_SIGC */
				nr.Modify()->_hoops_RGP = 0;
			}
			else {	/* _hoops_ASSI _hoops_HCR _hoops_HSP _hoops_ASCA (_hoops_PPR _hoops_PSHRR _hoops_RRRH) */
				int _hoops_ASHIP = ~(T_FACES | T_CUT_GEOMETRY | T_IMAGES);
				if (BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RHCRP))
					_hoops_ASHIP |= T_IMAGES;				/* _hoops_PGSA _hoops_AGCR _hoops_CAS _hoops_PIASR */
				nr.Modify()->_hoops_RGP = nr->_hoops_IRR->_hoops_AARIP & _hoops_ASHIP;
			}

			nr->flags |= _hoops_IPIHP;
		}

		if (BIT(flags, _hoops_IASHP) &&
			!BIT(nr->flags, _hoops_IASHP)) {

			_hoops_HHCR	_hoops_GGCC = nr.Modify()->transform_rendition.Modify();
			_hoops_GGCC->_hoops_CHIH = 0;
			nr->flags |= _hoops_IASHP;
		}
	}
	else {
		bool _hoops_PSHIP =  BIT(nr->flags, _hoops_PHIHP) ||
							   BIT(nr->flags, _hoops_HHIHP) && !_hoops_GAHHP;

		if (_hoops_PSHIP) {
			/* _hoops_HSHIP _hoops_ISHIP _hoops_CSHIP _hoops_SSHIP _hoops_GGIIP */
			RGB					_hoops_HIHIP, _hoops_IIHIP;

			/* _hoops_AASR */
			if (nr->_hoops_IRR->_hoops_HASR != nr->_hoops_IRR->_hoops_RPIHP) {
				_hoops_GRGH  _hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();
				_hoops_APIHP->_hoops_HASR = _hoops_APIHP->_hoops_RPIHP;
			}
			if (nr->_hoops_IRR->_hoops_CASR != nr->_hoops_IRR->_hoops_PPIHP) {
				_hoops_GRGH  _hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();
				_hoops_APIHP->_hoops_CASR = _hoops_APIHP->_hoops_PPIHP;
			}

			/* _hoops_SPHGR */
			if (nr->_hoops_ASIR->window.color !=  nr->_hoops_ASIR->window._hoops_SCHHP) {
				_hoops_ISHHP _hoops_RHIHP = nr.Modify()->_hoops_ASIR.Modify();
				_hoops_RHIHP->window.color = _hoops_RHIHP->window._hoops_SCHHP;
			}
			if (nr->_hoops_ASIR->window._hoops_HGIHP !=  nr->_hoops_ASIR->window._hoops_IGIHP) {
				_hoops_ISHHP _hoops_RHIHP = nr.Modify()->_hoops_ASIR.Modify();
				_hoops_RHIHP->window._hoops_HGIHP = _hoops_RHIHP->window._hoops_IGIHP;
			}

			/* _hoops_APGR */
			if (nr->_hoops_AHP->color != nr->_hoops_AHP->_hoops_SCHHP) {
				Line_Rendition _hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();
				_hoops_ASGIP->color = _hoops_ASGIP->_hoops_SCHHP;
			}
			if (nr->_hoops_AHP->contrast_color != nr->_hoops_AHP->_hoops_GRIHP) {
				Line_Rendition _hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();
				_hoops_ASGIP->contrast_color = _hoops_ASGIP->_hoops_GRIHP;
			}

			/* _hoops_SPPR */
			if (nr->_hoops_RHP->color != nr->_hoops_RHP->_hoops_SCHHP) {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_RHP->_hoops_SCHHP, r, red),
							_hoops_HCHIP(nr, _hoops_RHP->_hoops_SCHHP, g, green),
							_hoops_HCHIP(nr, _hoops_RHP->_hoops_SCHHP, b, blue));
				_hoops_CCHIP (nr, &_hoops_HIHIP, false);
			}
			if (nr->_hoops_RHP->contrast_color != nr->_hoops_RHP->_hoops_GRIHP) {
				Line_Rendition _hoops_ASGIP = nr.Modify()->_hoops_RHP.Modify();
				_hoops_ASGIP->contrast_color = _hoops_ASGIP->_hoops_GRIHP;
			}
			if (nr->_hoops_CAIHP->color != nr->_hoops_CAIHP->_hoops_SCHHP) {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_CAIHP->_hoops_SCHHP, r, red),
							_hoops_HCHIP(nr, _hoops_CAIHP->_hoops_SCHHP, g, green),
							_hoops_HCHIP(nr, _hoops_CAIHP->_hoops_SCHHP, b, blue));
				_hoops_RGIIP (nr, &_hoops_HIHIP, false);
			}

			/* _hoops_RSSI
			 * _hoops_PIP: _hoops_SR _hoops_HHS _hoops_AGIIP _hoops_AA _hoops_IRS _hoops_RSCA _hoops_GIH _hoops_ARI _hoops_RPP _hoops_SR _hoops_PGIIP _hoops_IS _hoops_HPPR _hoops_IS _hoops_GRHP _hoops_RH
			 * _hoops_RIPS _hoops_PPR _hoops_ISSC _hoops_HGIIP _hoops_PHPC _hoops_IS _hoops_RH _hoops_PSHR _hoops_AHAP _hoops_RPP _hoops_PPR _hoops_CGPR _hoops_SSRR. */
			if (nr->_hoops_IHA->color != nr->_hoops_IHA->_hoops_SCHHP) {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_IHA->_hoops_SCHHP, r, red),
							_hoops_HCHIP(nr, _hoops_IHA->_hoops_SCHHP, g, green),
							_hoops_HCHIP(nr, _hoops_IHA->_hoops_SCHHP, b, blue));
				_hoops_SCHIP (nr, &_hoops_HIHIP, false);
			}
			if (nr->_hoops_IHA->contrast_color != nr->_hoops_IHA->_hoops_GRIHP) {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_IHA->_hoops_GRIHP, r, red),
							_hoops_HCHIP(nr, _hoops_IHA->_hoops_GRIHP, g, green),
							_hoops_HCHIP(nr, _hoops_IHA->_hoops_GRIHP, b, blue));
				_hoops_IGIIP (nr, &_hoops_HIHIP, false);
			}
			if (nr->_hoops_IHA->_hoops_RGIR != nr->_hoops_IHA->_hoops_GSHHP) {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_IHA->_hoops_GSHHP, r, red),
							_hoops_HCHIP(nr, _hoops_IHA->_hoops_GSHHP, g, green),
							_hoops_HCHIP(nr, _hoops_IHA->_hoops_GSHHP, b, blue));
				_hoops_CGIIP (nr, &_hoops_HIHIP, false);
			}
			if (nr->_hoops_IHA->_hoops_ARIHP != nr->_hoops_IHA->_hoops_PRIHP) {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_IHA->_hoops_PRIHP, r, red),
							_hoops_HCHIP(nr, _hoops_IHA->_hoops_PRIHP, g, green),
							_hoops_HCHIP(nr, _hoops_IHA->_hoops_PRIHP, b, blue));
				_hoops_SGIIP (nr, &_hoops_HIHIP, false);
			}

#if 0
			/* _hoops_RH _hoops_HSPR _hoops_RIS _hoops_GPGH'_hoops_RA _hoops_HAHH (_hoops_GAPR) _hoops_PGGA _hoops_RGAR _hoops_RH _hoops_PH _hoops_ARCR _hoops_SSCP _hoops_PCCP _hoops_GIRRR _hoops_GPP _hoops_CHIR _hoops_APIR _hoops_HIS _hoops_SGIP. */
			if (nr->_hoops_AAIHP->color != nr->_hoops_AAIHP->_hoops_SCHHP) {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_AAIHP->_hoops_SCHHP, r, red),
							_hoops_HCHIP(nr, _hoops_AAIHP->_hoops_SCHHP, g, green),
							_hoops_HCHIP(nr, _hoops_AAIHP->_hoops_SCHHP, b, blue));
				_hoops_GRIIP (nr, &_hoops_HIHIP, false);
			}
#endif

			if (nr->_hoops_HAIHP->color != nr->_hoops_HAIHP->_hoops_SCHHP) {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_HAIHP->_hoops_SCHHP, r, red),
							_hoops_HCHIP(nr, _hoops_HAIHP->_hoops_SCHHP, g, green),
							_hoops_HCHIP(nr, _hoops_HAIHP->_hoops_SCHHP, b, blue));
				_hoops_RRIIP (nr, &_hoops_HIHIP, false);
			}
			if (nr->_hoops_HAIHP->contrast_color != nr->_hoops_HAIHP->_hoops_GRIHP) {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_HAIHP->_hoops_GRIHP, r, red),
							_hoops_HCHIP(nr, _hoops_HAIHP->_hoops_GRIHP, g, green),
							_hoops_HCHIP(nr, _hoops_HAIHP->_hoops_GRIHP, b, blue));
				_hoops_RRIIP (nr, &_hoops_HIHIP, false);
			}

			/* _hoops_SAIA */
			if (nr->_hoops_GSP->color != nr->_hoops_GSP->_hoops_SCHHP) {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_GSP->_hoops_SCHHP, r, red),
							_hoops_HCHIP(nr, _hoops_GSP->_hoops_SCHHP, g, green),
							_hoops_HCHIP(nr, _hoops_GSP->_hoops_SCHHP, b, blue));
				_hoops_GSHIP (nr, &_hoops_HIHIP, false);
			}
			if (nr->_hoops_GSP->contrast_color != nr->_hoops_GSP->_hoops_GRIHP) {
				_hoops_ICP _hoops_HCSHP = nr->_hoops_GSP.Modify();
				_hoops_HCSHP->contrast_color = _hoops_HCSHP->_hoops_GRIHP;
			}

			/* _hoops_GIHA */
			if (nr->_hoops_SCP->color != nr->_hoops_SCP->_hoops_SCHHP) {
				_hoops_HIHIP = RGB (_hoops_HCHIP(nr, _hoops_SCP->_hoops_SCHHP, r, red),
							_hoops_HCHIP(nr, _hoops_SCP->_hoops_SCHHP, g, green),
							_hoops_HCHIP(nr, _hoops_SCP->_hoops_SCHHP, b, blue));
				_hoops_ARIIP (nr, &_hoops_HIHIP, false);
			}
			if (nr->_hoops_SCP->contrast_color != nr->_hoops_SCP->_hoops_GRIHP) {
				_hoops_ICP _hoops_HCSHP = nr.Modify()->_hoops_SCP.Modify();
				_hoops_HCSHP->contrast_color = _hoops_HCSHP->_hoops_GRIHP;
			}

			/* _hoops_HCGR */
			if (nr->_hoops_SISI->color != nr->_hoops_SISI->_hoops_SCHHP) {
				_hoops_IGCSR _hoops_IRRIP = nr.Modify()->_hoops_SISI.Modify();
				_hoops_IRRIP->color = _hoops_IRRIP->_hoops_SCHHP;
			}

			nr.Modify()->flags &= ~(_hoops_PHIHP|_hoops_HHIHP);
		}

		/* _hoops_ICSI _hoops_CCSHP _hoops_III _hoops_PRIIP _hoops_AIRC _hoops_RHSP _hoops_GPGR _hoops_HHHH */
		if (nr->_hoops_IRR->_hoops_SRI == _hoops_SICI) {
			if (!BIT(nr->flags, _hoops_IPIHP)) {
				int		_hoops_ASHIP = 0;

				switch (dc->_hoops_SHCI()) {
					case _hoops_HRIIP: {
						/* _hoops_IRIIP _hoops_GGSR _hoops_ARPP _hoops_SCH _hoops_SAGGR _hoops_IS _hoops_CPAP, _hoops_HIS _hoops_ISAP _hoops_IS _hoops_AA _hoops_ARI */
					}		break;

					case _hoops_GICI: {
						_hoops_ASHIP = T_CUTTING_PLANES | T_ANY_LIGHTS |	/* _hoops_RRP _hoops_AGCR _hoops_CGPR _hoops_GII _hoops_RSSI _hoops_CHR _hoops_CHCC */
							   T_WINDOWS;
						if (BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_HPCRP))
							_hoops_ASHIP |= T_FACES | T_CUT_GEOMETRY | T_IMAGES; /* _hoops_PGSA _hoops_AGCR _hoops_CAS _hoops_PIASR */
						if (BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_IPCRP))
							_hoops_ASHIP |= T_TEXT;
					}		break;							/* _hoops_PPR _hoops_PSSSR _hoops_IH _hoops_HGHIP _hoops_RGR _hoops_RIH */

					case _hoops_RICI: {
						_hoops_ISHHP const &		_hoops_CSHHP = nr->_hoops_ASIR;

						_hoops_ASHIP = T_FACES | T_CUT_GEOMETRY | T_IMAGES | /* _hoops_AGCR _hoops_CISA _hoops_RH _hoops_AHCR _hoops_SRHR */
							   T_CUTTING_PLANES;			/* _hoops_HIH _hoops_GHCA _hoops_SHH _hoops_GSAS; _hoops_HSGR _hoops_SS _hoops_CR _hoops_ISAP _hoops_SIGC */
						nr.Modify()->transform_rendition.Modify()->flags &= ~_hoops_GRHH;
						if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < _hoops_CSHHP->_hoops_GCCI._hoops_CHCRP)
							_hoops_ASHIP &= ~T_FACES;
						if (nr->_hoops_SISI->transform == FT_FULL)
							_hoops_ASHIP |= T_TEXT;
					}		break;

					case _hoops_CRIIP: {
						/* _hoops_GIR _hoops_PPGA _hoops_ARRS _hoops_CR _hoops_PSHA _hoops_PPR _hoops_PAIA _hoops_AGRP _hoops_SRIIP */
					}		break;

					case _hoops_GAIIP: {
						/* _hoops_GSSR _hoops_PGSA _hoops_RIH, _hoops_CPS _hoops_AHSAR '_hoops_RSSI' */
						_hoops_ASHIP = ~(T_FACES | T_IMAGES);
						if (BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_RHCRP))
							_hoops_ASHIP |= T_IMAGES;				/* _hoops_PGSA _hoops_AGCR _hoops_CAS _hoops_PIASR */
					}		break;
				}

				if (_hoops_ASHIP != 0) {	/* _hoops_SR _hoops_CHR _hoops_HAGC _hoops_IRS _hoops_AGRP _hoops_RGR _hoops_GHIR */
					nr.Modify()->_hoops_RGP = nr->_hoops_IRR->_hoops_AARIP & _hoops_ASHIP;
				}

				nr.Modify()->flags |= _hoops_IPIHP;
			}
		}
		else if (BIT (nr->_hoops_IRR->_hoops_SRI, _hoops_PRAAP) &&
				 dc->_hoops_SHCI() == _hoops_GICI) {
			if (!BIT(nr->flags, _hoops_IPIHP)) {
				int _hoops_ASHIP = T_CUTTING_PLANES | T_ANY_LIGHTS;		/* _hoops_RRP _hoops_AGCR _hoops_CGPR _hoops_GII _hoops_RSSI _hoops_CHR _hoops_CHCC */

				if (BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_HPCRP))
					_hoops_ASHIP |= T_FACES | T_CUT_GEOMETRY | T_IMAGES;				/* _hoops_PGSA _hoops_AGCR _hoops_CAS _hoops_PIASR */
				if (BIT (nr->_hoops_ASIR->_hoops_GCCI.options, _hoops_IPCRP))
					_hoops_ASHIP |= T_TEXT;

				nr.Modify()->_hoops_RGP = nr->_hoops_IRR->_hoops_AARIP & _hoops_ASHIP;

				nr->flags |= _hoops_IPIHP;
			}
		}
		else {
			if (BIT (flags, _hoops_HARIP)) {
				if (!BIT (nr->flags, _hoops_HARIP)) {
					_hoops_ACHR			_hoops_PARIP = nr->_hoops_CPP->_hoops_RHGGR._hoops_RGP;

					if (ANYBIT (nr->_hoops_RGP, ~_hoops_PARIP)) {
						nr.Modify()->_hoops_RGP &= _hoops_PARIP;
					}

					nr->flags |= _hoops_HARIP;
				}
			}
			else if (BIT (flags, _hoops_GSGIP)) {
				if (!BIT (nr->flags, _hoops_GSGIP)) {
					_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;

					nr.Modify()->_hoops_RGP = _hoops_RRGH->_hoops_AARIP | _hoops_RRGH->_hoops_PHARP;

					if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < 1.0f &&
						!BIT (_hoops_RRGH->_hoops_AAICA | _hoops_RRGH->_hoops_PHARP, T_FACES))
						nr->_hoops_RGP &= ~T_FACES;
					if (nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR < 1.0f &&
						!BIT (_hoops_RRGH->_hoops_AAICA | _hoops_RRGH->_hoops_PHARP, T_EDGES))
						nr->_hoops_RGP &= ~T_ANY_EDGE;
					if (nr->_hoops_RHP->_hoops_CHA->_hoops_IRIR < 1.0f &&
						!BIT (_hoops_RRGH->_hoops_AAICA | _hoops_RRGH->_hoops_PHARP, T_EDGES))
						nr->_hoops_RGP &= ~T_ANY_EDGE;
					if (nr->_hoops_AHP->_hoops_CHA->_hoops_IRIR < 1.0f &&
						!BIT (_hoops_RRGH->_hoops_AAICA | _hoops_RRGH->_hoops_PHARP, T_LINES))
						nr->_hoops_RGP &= ~T_LINES;
					if (nr->_hoops_GSP->_hoops_CHA->_hoops_IRIR < 1.0f &&
						!BIT (_hoops_RRGH->_hoops_AAICA | _hoops_RRGH->_hoops_PHARP, T_MARKERS))
						nr->_hoops_RGP &= ~T_MARKERS;
					if (nr->_hoops_SCP->_hoops_CHA->_hoops_IRIR < 1.0f &&
						!BIT (_hoops_RRGH->_hoops_AAICA | _hoops_RRGH->_hoops_PHARP, T_VERTICES))
						nr->_hoops_RGP &= ~T_VERTICES;

					nr->flags |= _hoops_GSGIP;
				}
			}

			if (!ANYBIT (nr->flags, _hoops_HARIP|_hoops_GSGIP) &&
				nr->_hoops_RGP != nr->_hoops_IRR->_hoops_AARIP) {
				nr.Modify()->_hoops_RGP = nr->_hoops_IRR->_hoops_AARIP;
				nr->flags &= ~_hoops_IPIHP;
			}
		}
	}



	if (_hoops_GAHHP && !BIT(nr->flags, _hoops_HHIHP)) {
#if 0
/* _hoops_ASIGA _hoops_AGCR _hoops_CGSI _hoops_HGGC _hoops_RRP _hoops_IS _hoops_SHH _hoops_CPHR */
!BIT (locks->_hoops_HAA[_hoops_IAA], M_TRANSMISSION))
!BIT (locks->_hoops_HAA[_hoops_RSHHP], M_TRANSMISSION))
!BIT (locks->color, Color_AMBIENT))
#endif
		_hoops_PIGRA const *	_hoops_RAIIP = &nr->_hoops_IRR->locks;
		_hoops_PIGRA			_hoops_AAIIP;
		RGB						_hoops_HIHIP, _hoops_IIHIP;

		if (dc->options._hoops_SIAH) {
			ZERO_STRUCT (&_hoops_AAIIP, _hoops_PIGRA);
			locks = &_hoops_AAIIP;
		}
		else if (!locks)
			locks = _hoops_RAIIP;

		/* _hoops_AASR */
		_hoops_GRGH const & _hoops_RRGH = nr->_hoops_IRR;

		if (!_hoops_RRGH->_hoops_HASR._hoops_PAIIP() || !_hoops_RRGH->_hoops_CASR._hoops_PAIIP()) {
			// _hoops_ASIGA _hoops_PSP _hoops_GGRRA

			if (_hoops_RRGH->_hoops_HASR == _hoops_RRGH->_hoops_CASR) {
				_hoops_HIHIP = RGB(_hoops_RRGH->_hoops_HASR._hoops_CPIR());
				_hoops_HAIIP (nr, &_hoops_HIHIP, false);
			}
			else {
				_hoops_HIHIP = RGB(_hoops_RRGH->_hoops_HASR._hoops_CPIR());
				_hoops_IAIIP (nr, &_hoops_HIHIP, false);
				_hoops_HIHIP = RGB(_hoops_RRGH->_hoops_CASR._hoops_CPIR());
				_hoops_CAIIP (nr, &_hoops_HIHIP, false);
			}
		}

		/* _hoops_RSSI */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_IHA->color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_SCHIP (nr, &_hoops_HIHIP,
							 BIT (_hoops_RAIIP->_hoops_HAA[_hoops_IAA], M_DIFFUSE));

		/* _hoops_HSP _hoops_CGARA */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_IHA->contrast_color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_IGIIP (nr, &_hoops_HIHIP,
									  BIT (_hoops_RAIIP->_hoops_HAA[_hoops_SGIHP], M_DIFFUSE));

		/* _hoops_ISSC _hoops_HSP */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_IHA->_hoops_RGIR);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_CGIIP (nr, &_hoops_HIHIP,
								  BIT (_hoops_RAIIP->_hoops_HAA[_hoops_RSHHP], M_DIFFUSE));

		/* _hoops_ISSC _hoops_HSP _hoops_CGARA */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_IHA->_hoops_ARIHP);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_SGIIP (nr, &_hoops_HIHIP,
										   BIT (_hoops_RAIIP->_hoops_HAA[_hoops_RRIHP], M_DIFFUSE));

		/* _hoops_AACC _hoops_SPPR */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_CAIHP->color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_RGIIP (nr, &_hoops_HIHIP,
								 BIT (_hoops_RAIIP->_hoops_HAA[_hoops_IAIHP], M_DIFFUSE));

		/* _hoops_RGR _hoops_GRS _hoops_GACHR _hoops_HAHH _hoops_ARR _hoops_CH _hoops_HS _hoops_RRI _hoops_HSAR _hoops_PH _hoops_ACAR */
#if 0
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_AAIHP->color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_GRIIP (nr, &_hoops_HIHIP,
											   BIT (_hoops_RAIIP->_hoops_HAA[_hoops_RAIHP], M_DIFFUSE));
#endif

		/* _hoops_AACC _hoops_RSSI */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_HAIHP->color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_RRIIP (nr, &_hoops_HIHIP,
								 BIT (_hoops_RAIIP->_hoops_HAA[_hoops_PAIHP], M_DIFFUSE));

		/* _hoops_RPPS _hoops_HAIR */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_ASIR->window.color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_SAIIP (nr, &_hoops_HIHIP,
							   BIT (_hoops_RAIIP->_hoops_HAA[_hoops_HSHHP], M_DIFFUSE));

		/* _hoops_RPPS _hoops_CGARA */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_ASIR->window._hoops_HGIHP);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_GPIIP (nr, &_hoops_HIHIP,
										BIT (_hoops_RAIIP->_hoops_HAA[_hoops_PGIHP], M_DIFFUSE));

		/* _hoops_APGR */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_AHP->color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_ICHIP (nr, &_hoops_HIHIP,
							 BIT (_hoops_RAIIP->_hoops_HAA[_hoops_RPA], M_DIFFUSE));

		/* _hoops_III _hoops_CGARA */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_AHP->contrast_color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_RPIIP (nr, &_hoops_HIHIP,
									  BIT (_hoops_RAIIP->_hoops_HAA[_hoops_RPA], M_DIFFUSE));

		/* _hoops_SPPR */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_RHP->color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_CCHIP (nr, &_hoops_HIHIP,
				BIT (_hoops_RAIIP->_hoops_HAA[_hoops_SAA], M_DIFFUSE));

		/* _hoops_ISHA _hoops_CGARA */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_RHP->contrast_color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_APIIP (nr, &_hoops_HIHIP,
									  BIT (_hoops_RAIIP->_hoops_HAA[_hoops_HRIHP], M_DIFFUSE));

		/* _hoops_SAIA _hoops_PPR _hoops_GIHA */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_GSP->color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_GSHIP (nr, &_hoops_HIHIP,
							   BIT (_hoops_RAIIP->_hoops_HAA[_hoops_APA], M_DIFFUSE));

		/* _hoops_GPIA _hoops_CGARA */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_GSP->contrast_color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_PPIIP (nr, &_hoops_HIHIP,
										BIT (_hoops_RAIIP->_hoops_HAA[_hoops_CRIHP], M_DIFFUSE));

		/* _hoops_GPHA _hoops_HAIR */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_SCP->color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_ARIIP (nr, &_hoops_HIHIP,
							   BIT (_hoops_RAIIP->_hoops_HAA[_hoops_PPA], M_DIFFUSE));

		/* _hoops_GPHA _hoops_CGARA */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_SCP->contrast_color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_HPIIP (nr, &_hoops_HIHIP,
										BIT (_hoops_RAIIP->_hoops_HAA[_hoops_SRIHP], M_DIFFUSE));

		/* _hoops_HCGR */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_SISI->color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_RSHIP (nr, &_hoops_HIHIP,
							 BIT (_hoops_RAIIP->_hoops_HAA[_hoops_GGIHP], M_DIFFUSE));

		/* _hoops_HCGR _hoops_CGARA */
		_hoops_HIHIP = _hoops_IHHIP (nr, nr->_hoops_SISI->contrast_color);
		_hoops_HIHIP = HD_Apply_Color_Effects (_hoops_HIHIP, _hoops_PHAH);
		_hoops_IPIIP (nr, &_hoops_HIHIP,
									  BIT (_hoops_RAIIP->_hoops_HAA[_hoops_GGIHP], M_DIFFUSE));

		nr.Modify()->flags |= _hoops_HHIHP;
	}
}


local bool _hoops_CPIIP (
	Display_Context alter *			dc,
	Net_Rendition const &			nr,
	bool							_hoops_SPIIP,
	_hoops_CRCP const *					_hoops_SRCP,
	_hoops_HICS const &			path,
	_hoops_HSPPP alter *		next,
	_hoops_HSPPP const *		_hoops_GHIIP) {
	_hoops_HCSIR alter *		_hoops_ICSIR = null;
	Int_Rectangle const *			rect;
	bool							_hoops_RHIIP = BIT(dc->_hoops_PGCC.flags, _hoops_IPPHP) && dc->options._hoops_AHIIP;
	bool							_hoops_PHIIP = false;
	_hoops_HSPPP alter *		w;

	HD_Alternate_Hidden_Root (dc, _hoops_HHIIP);
	if (!_hoops_SPIIP &&
		!dc->_hoops_IHIIP[0] &&
		!dc->_hoops_HASS[dc->_hoops_IASS] &&
		!dc->_hoops_GPSS[dc->_hoops_IASS] &&
		!dc->_hoops_RPSS[dc->_hoops_IASS]) {

		if (BIT(dc->flags, _hoops_CHIIP)) {
			_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
			_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path, false);

			if (nr->_hoops_SAIR->_hoops_ASSIR != null)
				_hoops_CSC = nr->_hoops_SAIR->_hoops_ASSIR;

			if (_hoops_CSC != null)
				_hoops_ICSIR = _hoops_CSC->_hoops_PSSIR();

			if (!_hoops_ICSIR || !_hoops_ICSIR->_hoops_PSPIP ||
				BIT(dc->flags, _hoops_SHIIP)) {
				HD_Alternate_Hidden_Root (dc, _hoops_HHIIP);
				return false;
			}
		}
		else {
			HD_Alternate_Hidden_Root (dc, _hoops_HHIIP);
			return false;
		}
	}


	bool _hoops_GIIIP = BIT(dc->flags, _hoops_RPSRR);
	dc->flags |= _hoops_RPSRR;
	// _hoops_PSP _hoops_ASRC _hoops_CCGR _hoops_RH _hoops_RSGR

	int	_hoops_HGRS = 0;

	while (dc->_hoops_IPCI->prev != null) {
		_hoops_HGRS++;
		_hoops_IGRS (dc);
	}

	_hoops_ICSIR = HD_Init_Frame_Buffer_Info (nr, _hoops_SRCP, path);
	rect = &nr->_hoops_SAIR->_hoops_SCIH;

	if (!_hoops_ICSIR->_hoops_RIIIP &&
		BIT(dc->_hoops_PGCC.flags, _hoops_PAGIP)) {
		if (_hoops_ICSIR->_hoops_AIIIP[0] != null) {
			int								_hoops_PIIIP, _hoops_HIIIP;
			int								_hoops_IIIIP, _hoops_CIIIP;

			_hoops_PIIIP = _hoops_ICSIR->_hoops_SIIIP.right - _hoops_ICSIR->_hoops_SIIIP.left + 1;
			_hoops_HIIIP = _hoops_ICSIR->_hoops_SIIIP.top - _hoops_ICSIR->_hoops_SIIIP.bottom + 1;
			_hoops_IIIIP = rect->right - rect->left + 1;
			_hoops_CIIIP = rect->top - rect->bottom + 1;

			if (_hoops_IIIIP != _hoops_PIIIP || _hoops_CIIIP != _hoops_HIIIP) {
				(*dc->_hoops_ACPGR->_hoops_ISPGR) (nr, _hoops_ICSIR->_hoops_AIIIP[0],
											   _hoops_ICSIR->_hoops_GCIIP[0]);
#if 0
				if (_hoops_ICSIR->_hoops_AIIIP[1] != null)
					(*dc->_hoops_ACPGR->_hoops_ISPGR) (nr, _hoops_ICSIR->_hoops_AIIIP[1],
												   _hoops_ICSIR->_hoops_GCIIP[1]);
#endif
				_hoops_ICSIR->_hoops_AIIIP[0] = _hoops_ICSIR->_hoops_AIIIP[1] = null;
				_hoops_ICSIR->_hoops_PSPIP = false;
			}
		}

		if (_hoops_ICSIR->_hoops_PSPIP && !BIT(dc->flags, _hoops_SHIIP)) {
			if (!BIT (dc->_hoops_CPGPR, _hoops_GIPGP)) {
				Int_Rectangle const *		_hoops_RCIIP;

				if (_hoops_SPIIP)
					_hoops_RCIIP = &nr->_hoops_SAIR->_hoops_SCIH;
				else {
					/* _hoops_SGH _hoops_RH _hoops_RHGS _hoops_GAR _hoops_IRS _hoops_ACIIP (_hoops_CR _hoops_SR _hoops_PPPPR'_hoops_RA _hoops_RRP _hoops_SCH _hoops_GICS) */
					if (dc->options._hoops_SRRRR &&
						dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA) {
						if (_hoops_ICSIR->_hoops_PCIIP.left < _hoops_ICSIR->_hoops_HCIIP.left)
							_hoops_ICSIR->_hoops_HCIIP.left = _hoops_ICSIR->_hoops_PCIIP.left;
						if (_hoops_ICSIR->_hoops_PCIIP.right > _hoops_ICSIR->_hoops_HCIIP.right)
							_hoops_ICSIR->_hoops_HCIIP.right = _hoops_ICSIR->_hoops_PCIIP.right;
						if (_hoops_ICSIR->_hoops_PCIIP.bottom < _hoops_ICSIR->_hoops_HCIIP.bottom)
							_hoops_ICSIR->_hoops_HCIIP.bottom = _hoops_ICSIR->_hoops_PCIIP.bottom;
						if (_hoops_ICSIR->_hoops_PCIIP.top > _hoops_ICSIR->_hoops_HCIIP.top)
							_hoops_ICSIR->_hoops_HCIIP.top = _hoops_ICSIR->_hoops_PCIIP.top;
					}
					else
						_hoops_RSAI (&_hoops_ICSIR->_hoops_PCIIP, Int_Rectangle, &_hoops_ICSIR->_hoops_HCIIP);

					w =	(_hoops_HSPPP alter *)next;
					while (w != _hoops_GHIIP) {
						Int_Rectangle const *	subwin;

						subwin = &w->_hoops_APHGA->_hoops_SAIR->_hoops_SCIH;
						if (subwin->left < _hoops_ICSIR->_hoops_HCIIP.left)
							_hoops_ICSIR->_hoops_HCIIP.left = subwin->left;
						if (subwin->right > _hoops_ICSIR->_hoops_HCIIP.right)
							_hoops_ICSIR->_hoops_HCIIP.right = subwin->right;
						if (subwin->bottom < _hoops_ICSIR->_hoops_HCIIP.bottom)
							_hoops_ICSIR->_hoops_HCIIP.bottom = subwin->bottom;
						if (subwin->top > _hoops_ICSIR->_hoops_HCIIP.top)
							_hoops_ICSIR->_hoops_HCIIP.top = subwin->top;

#if 0
						if (w->_hoops_APHGA->_hoops_SAIR->_hoops_CGAIP == FP_WINDOW_TRANSPARENT)
#endif
							w->_hoops_CPGPR |= _hoops_GAGSA;

						w = w->next;
					}

					_hoops_RCIIP = &_hoops_ICSIR->_hoops_HCIIP;
				}


				if (_hoops_RCIIP->left <= _hoops_RCIIP->right &&
					_hoops_RCIIP->bottom <= _hoops_RCIIP->top) {
					if (!dc->_hoops_AGGIP)
						_hoops_ICIIP (nr, _hoops_RCIIP, _hoops_ICSIR->_hoops_AIIIP[0], _hoops_ICSIR->_hoops_GCIIP[0]);
					else {
						Net_Rendition					_hoops_CCIIP = nr;
						_hoops_HHCR alter &		_hoops_GGCC = _hoops_CCIIP.Modify()->transform_rendition.Modify();

						_hoops_GGCC->_hoops_RHPHP = _hoops_PHPHP;
						_hoops_ICIIP (_hoops_CCIIP, _hoops_RCIIP, _hoops_ICSIR->_hoops_AIIIP[0], _hoops_ICSIR->_hoops_GCIIP[0]);
#if 0
						_hoops_GGCC->_hoops_RHPHP = _hoops_HHPHP;
						_hoops_ICIIP (_hoops_CCIIP, _hoops_RCIIP, _hoops_ICSIR->_hoops_AIIIP[1], _hoops_ICSIR->_hoops_GCIIP[1]);
#endif
					}
					_hoops_APSRR(dc, "draw_spriting Restore_Region","", (int)(POINTER_SIZED_INT)_hoops_ICSIR);
					_hoops_ICSIR->_hoops_SCIIP = false;
				}
			}
		}
		else {
			if (_hoops_ICSIR->_hoops_AIIIP[0] == null) {
				_hoops_GSIIP (nr, rect, &_hoops_ICSIR->_hoops_AIIIP[0], &_hoops_ICSIR->_hoops_GCIIP[0]);
#if 0
				if (dc->_hoops_AGGIP)
					_hoops_GSIIP (nr, rect, &_hoops_ICSIR->_hoops_AIIIP[1], &_hoops_ICSIR->_hoops_GCIIP[1]);
#endif
				_hoops_ICSIR->_hoops_SIIIP.left	= rect->left;
				_hoops_ICSIR->_hoops_SIIIP.right	= rect->right;
				_hoops_ICSIR->_hoops_SIIIP.bottom = rect->bottom;
				_hoops_ICSIR->_hoops_SIIIP.top	= rect->top;

				_hoops_APSRR(dc, "draw_spriting Create_Region","", 0);
			}

			if (!dc->_hoops_AGGIP) {
				//_hoops_AGHR(!_hoops_RSIIP->_hoops_ASIIP);
				_hoops_PSIIP (nr, rect, _hoops_ICSIR->_hoops_AIIIP[0], _hoops_ICSIR->_hoops_GCIIP[0]);
			}
			else {
				Net_Rendition					_hoops_CCIIP = nr;
				_hoops_HHCR alter &		_hoops_GGCC = _hoops_CCIIP.Modify()->transform_rendition.Modify();

				_hoops_GGCC->_hoops_RHPHP = _hoops_PHPHP;
				ASSERT(!_hoops_ICSIR->_hoops_SCIIP);
				_hoops_PSIIP (_hoops_CCIIP, rect,_hoops_ICSIR->_hoops_AIIIP[0], _hoops_ICSIR->_hoops_GCIIP[0]);
#if 0
				_hoops_GGCC->_hoops_RHPHP = _hoops_HHPHP;
				_hoops_PSIIP (_hoops_CCIIP, rect, _hoops_ICSIR->_hoops_AIIIP[1], _hoops_ICSIR->_hoops_GCIIP[1]);
#endif
			}
			_hoops_APSRR(dc, "draw_spriting Save_Region","", 0);

			_hoops_ICSIR->_hoops_PSPIP = true;
		}
	}

	/* _hoops_ASAC _hoops_RH _hoops_SCGR _hoops_HGIIP (_hoops_RPP _hoops_HAR _hoops_AIAH) */
	{
		_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *		_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);

		if (_hoops_CSC->_hoops_APHGA == null)
			_hoops_CSC->_hoops_APHGA = nr;
	}

	if (dc->_hoops_IHIIP[0]) {
		HD_Draw_Sprites (dc, _hoops_ICSIR, true, _hoops_RHIIP);
		_hoops_ICSIR->_hoops_SCIIP = true;
		_hoops_APSRR(dc, "draw_spriting 1 Draw_Sprites","", (int)(POINTER_SIZED_INT)_hoops_ICSIR);
	}

	if (dc->_hoops_AGGIP) {
		dc->_hoops_IHIIP[0] = dc->_hoops_IHIIP[1];
		dc->_hoops_IHIIP[1] = null;
#if 0
		HD_Draw_Sprites (dc, _hoops_ICSIR, true, false);
		_hoops_ICSIR->_hoops_SCIIP = true;
		_hoops_APSRR(dc, "draw_spriting 2 Draw_Sprites","", (int)(POINTER_SIZED_INT)_hoops_ICSIR);
#else
		while (dc->_hoops_IHIIP[0] != null) {
			_hoops_HSIIP alter	*victim = dc->_hoops_IHIIP[0];

			dc->_hoops_IHIIP[0] = victim->next;
			victim->nr.release();
			victim->path.release();
			if (victim->geometry != null)
				_hoops_HPRH (victim->geometry);
			if (victim->_hoops_ISIIP != null && _hoops_ISAI (victim->_hoops_ISIIP) == 0)
				HI_Free_Tristrip (victim->_hoops_ISIIP);
			FREE (victim, _hoops_HSIIP);
		}
#endif
	}

	/* _hoops_RH _hoops_HGSI _hoops_CCSHP _hoops_HIGR _hoops_SSCP _hoops_AIAH _hoops_RPII _hoops_CHHHP.  _hoops_HGI _hoops_SPR _hoops_HRGR _hoops_SAHR _hoops_HISI _hoops_RRH
		_hoops_CIPH _hoops_IHCPR _hoops_ASSA _hoops_RH _hoops_CSIIP _hoops_SGHC */
	if (dc->_hoops_HASS[dc->_hoops_IASS]) {
		_hoops_PHIIP = true;
		// _hoops_ASIGA _hoops_RSH _hoops_PAH _hoops_RGR _hoops_SAHR _hoops_GRPHA?
		//_hoops_SCII->_hoops_SCGR |= _hoops_SSIIP;
		//_hoops_SCII->_hoops_RCAPR |= _hoops_SSIIP;
		HD_See_Whats_Hidden (nr);
		if (dc->_hoops_AGGIP) {
			HD_Alternate_Hidden_Root (dc, _hoops_GGCIP);
			HD_See_Whats_Hidden (nr);
		}
		//_hoops_SCII->_hoops_SCGR &= ~_hoops_SSIIP;
		//_hoops_SCII->_hoops_RCAPR &= ~_hoops_SSIIP;
	}
	if (dc->_hoops_GPSS[dc->_hoops_IASS] != null) {
		_hoops_PHIIP = true;
		_hoops_SSGGR (dc);
	}
	if (next != null)
		_hoops_PHIIP = true;

	if (_hoops_PHIIP) {
		_hoops_ICSIR->_hoops_PCIIP.left   = nr->_hoops_SAIR->_hoops_PHRA.left;
		_hoops_ICSIR->_hoops_PCIIP.right  = nr->_hoops_SAIR->_hoops_PHRA.right;
		_hoops_ICSIR->_hoops_PCIIP.bottom = nr->_hoops_SAIR->_hoops_PHRA.bottom;
		_hoops_ICSIR->_hoops_PCIIP.top    = nr->_hoops_SAIR->_hoops_PHRA.top;
	}

	HD_Alternate_Hidden_Root (dc, _hoops_HHIIP);
	_hoops_ICSIR->_hoops_GHIAA = true;

#if 0
	w = (_hoops_HSPPP alter *)next;
	while (w != _hoops_GHIIP) {
		if (w->_hoops_APHGA->_hoops_SAIR->_hoops_CGAIP != FP_WINDOW_TRANSPARENT)
			w->_hoops_SPIIP = true;
		w = w->next;
	}
#endif

	while (_hoops_HGRS-- > 0)
		_hoops_SGRS (dc);

	HD_Free_Sprite_List (dc, &dc->_hoops_IHIIP[0]);
	HD_Free_Sprite_List (dc, &dc->_hoops_IHIIP[1]);

	if (!_hoops_GIIIP)
		dc->flags &= ~_hoops_RPSRR;

	return true;
} /* _hoops_RSGR _hoops_API '_hoops_PGSA _hoops_IAGIP' */


local bool _hoops_RGCIP (
   	Display_Context alter *			dc,
	Net_Rendition const &			nr,
	_hoops_HCSIR alter *		_hoops_ICSIR) {
	Int_Rectangle const *			_hoops_RCIIP;
	Int_Rectangle const *			rect;
	int								_hoops_PIIIP, _hoops_HIIIP;
	int								_hoops_IIIIP, _hoops_CIIIP;

	_hoops_APSRR(dc, "undraw_spriting","", 0);

	if (!_hoops_ICSIR || !_hoops_ICSIR->_hoops_PSPIP || _hoops_ICSIR->_hoops_RIIIP != null)
		return false;

	rect = &nr->_hoops_SAIR->_hoops_SCIH;
	_hoops_PIIIP = _hoops_ICSIR->_hoops_SIIIP.right - _hoops_ICSIR->_hoops_SIIIP.left + 1;
	_hoops_HIIIP = _hoops_ICSIR->_hoops_SIIIP.top - _hoops_ICSIR->_hoops_SIIIP.bottom + 1;
	_hoops_IIIIP = rect->right - rect->left + 1;
	_hoops_CIIIP = rect->top - rect->bottom + 1;
	if (_hoops_IIIIP != _hoops_PIIIP || _hoops_CIIIP != _hoops_HIIIP) {
		/* _hoops_RPPS _hoops_SSCP _hoops_HGAS _hoops_PGRR */
		HD_Free_Frame_Buffer_Info (nr, _hoops_ICSIR);
		return false;
	}

	if (dc->options._hoops_SRRRR &&
		dc->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA) {
		/* _hoops_HASC _hoops_CCAH _hoops_CRGR _hoops_RHGS _hoops_PPR _hoops_SGH _hoops_SGS _hoops_SPR (_hoops_CR _hoops_SR _hoops_PPPPR'_hoops_RA _hoops_RRP _hoops_SCH _hoops_GICS) */
		if (_hoops_ICSIR->_hoops_PCIIP.left < _hoops_ICSIR->_hoops_HCIIP.left)
			_hoops_ICSIR->_hoops_HCIIP.left = _hoops_ICSIR->_hoops_PCIIP.left;
		if (_hoops_ICSIR->_hoops_PCIIP.right > _hoops_ICSIR->_hoops_HCIIP.right)
			_hoops_ICSIR->_hoops_HCIIP.right = _hoops_ICSIR->_hoops_PCIIP.right;
		if (_hoops_ICSIR->_hoops_PCIIP.bottom < _hoops_ICSIR->_hoops_HCIIP.bottom)
			_hoops_ICSIR->_hoops_HCIIP.bottom = _hoops_ICSIR->_hoops_PCIIP.bottom;
		if (_hoops_ICSIR->_hoops_PCIIP.top > _hoops_ICSIR->_hoops_HCIIP.top)
			_hoops_ICSIR->_hoops_HCIIP.top = _hoops_ICSIR->_hoops_PCIIP.top;

		_hoops_RCIIP = &_hoops_ICSIR->_hoops_HCIIP;
	}
	else
		_hoops_RCIIP = &_hoops_ICSIR->_hoops_PCIIP;

	if (_hoops_RCIIP->left > _hoops_RCIIP->right ||
		_hoops_RCIIP->bottom > _hoops_RCIIP->top)
		return true;

	if (_hoops_ICSIR->_hoops_AIIIP[0] == null)
		return true;

	if (_hoops_ICSIR->_hoops_AIIIP[1] == null)
		_hoops_ICIIP (nr, _hoops_RCIIP, _hoops_ICSIR->_hoops_AIIIP[0], _hoops_ICSIR->_hoops_GCIIP[0]);
	else {
		Net_Rendition					_hoops_CCIIP = nr;
		_hoops_HHCR alter &		_hoops_GGCC = _hoops_CCIIP.Modify()->transform_rendition.Modify();

		_hoops_GGCC->_hoops_RHPHP = _hoops_PHPHP;
		_hoops_ICIIP (_hoops_CCIIP, _hoops_RCIIP, _hoops_ICSIR->_hoops_AIIIP[0], _hoops_ICSIR->_hoops_GCIIP[0]);
#if 0
		_hoops_GGCC->_hoops_RHPHP = _hoops_HHPHP;
		_hoops_ICIIP (_hoops_CCIIP, _hoops_RCIIP, _hoops_ICSIR->_hoops_AIIIP[1], _hoops_ICSIR->_hoops_GCIIP[1]);
#endif
	}
	_hoops_APSRR(dc, "undraw_spriting Restore_Region","", (int)(POINTER_SIZED_INT)_hoops_ICSIR);
	_hoops_ICSIR->_hoops_SCIIP = false;

	dc->_hoops_CPGPR |= _hoops_APPGP|_hoops_PPPGP;
	return true;
} /* _hoops_RSGR _hoops_API '_hoops_AGCIP _hoops_IAGIP' */


GLOBAL_FUNCTION void HD_Std_Depth_Peeling (
	Display_Context alter *		dc) {
	_hoops_PGCIP alter *			list;

	if ((list = dc->_hoops_GPSS[dc->_hoops_IASS]) == null)
		return;
	dc->_hoops_GPSS[dc->_hoops_IASS] = null;

	if (!BIT(dc->flags, _hoops_CHSI)) {
		/* _hoops_ARP _hoops_GH _hoops_IH _hoops_AHCR _hoops_SRHR _hoops_HGCIP */
		Net_Rendition				nr = list->nr;
		nr.Modify()->_hoops_IRR.Modify()->_hoops_GIRC = true;

		(*dc->_hoops_ACPGR->init_picture) (nr);

		HD_Draw_Deferred_3D_Geometry (list, false);

		/* _hoops_PHIH _hoops_IS _hoops_GSSR _hoops_ASCA _hoops_CCH */
		(*dc->_hoops_ACPGR->init_picture) (list->nr);
		HD_Draw_Deferred_3D_Geometry (list, false);
	}

	/* _hoops_GGAS */
	HD_Free_Deferred_3D_Geometry (list);
}

GLOBAL_FUNCTION void HD_Draw_Deferred_3D_Geometry (
	_hoops_PGCIP alter *		list,
	bool					_hoops_IGCIP) {

	if (list != null) {
		Display_Context alter *		dc = (Display_Context alter *) list->nr->_hoops_SRA;
		_hoops_ISGI const *	_hoops_CGCIP = dc->_hoops_SPA->modelling_matrix;
		_hoops_SSGI const *				_hoops_SGCIP = dc->_hoops_SPA->color;
		_hoops_CRCP const *				_hoops_GRCIP = dc->_hoops_RRCIP;
		_hoops_HICS				_hoops_ARCIP = dc->path;
		int							_hoops_PRCIP = 0;
		Action_Mask					action_mask;

		while (ANYBIT (dc->_hoops_IPCI->mode, _hoops_ISGGR|_hoops_HSGGR)) {
			_hoops_IGRS (dc);
			_hoops_PRCIP++;
		}
		action_mask = dc->_hoops_IPCI->mask;
		do {
			Net_Rendition	 		nr = list->nr;

			if (_hoops_IGCIP && !BIT(nr->transform_rendition->flags, _hoops_ISH))
				nr.Modify()->transform_rendition.Modify(_hoops_HRCIP)->flags |= _hoops_ISH;

			dc->_hoops_SPA->modelling_matrix = list->_hoops_IRCIP;
			dc->_hoops_SPA->color = list->_hoops_GPCP;

			dc->_hoops_RRCIP = list->segment;
			dc->path = list->path;

			switch (list->type) {
				case _hoops_CRCIP: {
					if (ANYBIT (_hoops_PGRI, action_mask)) {
						Tristrip const *ts = (Tristrip const *)list->item;
						if (list->g)
							dc->_hoops_RAI = list->g;
						if (list->g &&
							list->g->type == _hoops_CSIP) {
							Tristrip alter *_hoops_IPIAR = (Tristrip alter *) ts;
							PolyCylinder alter *_hoops_SRCIP = (PolyCylinder alter *)list->g;

							_hoops_IPIAR->_hoops_GAHA = _hoops_SRCIP->_hoops_SGHIR;
							if (ts->_hoops_GAHA &&
								!BIT(dc->flags, _hoops_IIGC)) {
								_hoops_IPIAR->_hoops_SRHA |= DL_DO_NOT_RECOMPILE;
								if (ts->_hoops_GAHA->list) {
									if (BIT (ts->_hoops_SRHA, _hoops_GGIA))
										_hoops_GACIP (nr, _hoops_ARCI)(nr, ts);
									else
										_hoops_RACIP (nr, ts);
								}
								if (!ts->_hoops_GAHA || !ts->_hoops_GAHA->list) {
									/* _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_CSAP _hoops_HGGPR.  _hoops_RHGAR _hoops_ISHP _hoops_RH _hoops_HPHR _hoops_CPAP */
									nr.Modify()->_hoops_RGP &= (T_FACES|T_LIGHTS_FOR_FACES);
									(*dc->_hoops_IPCI->draw_3d_polycylinder)(nr, (PolyCylinder const *)list->g);
								}
								if (ts->_hoops_GAHA == _hoops_SRCIP->_hoops_SGHIR) {
									/* _hoops_GASA: _hoops_GHAP'_hoops_GHGP _hoops_PII _hoops_IS _hoops_SHH _hoops_SHSS _hoops_IS _hoops_AACIP _hoops_ARI, _hoops_HIH _hoops_GHAP _hoops_GA'_hoops_RA _hoops_RHCA _hoops_RH _hoops_PCPCA
									 * _hoops_IH _hoops_RGR _hoops_AGIR _hoops_PPGC _hoops_SPCP _hoops_RH _hoops_GAHIR _hoops_ARI */
									/*_hoops_ICPCA (_hoops_GARI->_hoops_PACIP);*/
								}
								else {
									ts->_hoops_GAHA->next = _hoops_SRCIP->_hoops_SGHIR;
									ts->_hoops_GAHA->backlink = &_hoops_SRCIP->_hoops_SGHIR;
									_hoops_SRCIP->_hoops_SGHIR = ts->_hoops_GAHA;
								}
								_hoops_IPIAR->_hoops_GAHA = null;
							}
							else {
								nr.Modify()->_hoops_RGP &= (T_FACES|T_LIGHTS_FOR_FACES);
								(*dc->_hoops_IPCI->draw_3d_polycylinder)(nr, (PolyCylinder const *)list->g);
							}
						}
						else {
							if (BIT (ts->_hoops_SRHA, _hoops_GGIA))
								_hoops_GACIP (nr, _hoops_ARCI)(nr, ts);
							else
								_hoops_RACIP (nr, ts);
						}
					}
				}	break;
				case _hoops_HACIP: {
					if (ANYBIT (action_mask, _hoops_ASRI|_hoops_GHCI)) {
						Polyedge const *pe = (Polyedge const *)list->item;
						if (list->g)
							dc->_hoops_RAI = list->g;
						if (list->g &&
							list->g->type == _hoops_CSIP) {
							Polyedge alter *_hoops_CHPS = (Polyedge alter *) pe;
							PolyCylinder alter *_hoops_SRCIP = (PolyCylinder alter *)list->g;

							_hoops_CHPS->_hoops_GAHA = _hoops_SRCIP->_hoops_GRHIR;
							if (pe->_hoops_GAHA) {
								_hoops_CHPS->_hoops_SRHA |= DL_DO_NOT_RECOMPILE;
								if (pe->_hoops_GAHA->list) {
									if (BIT (pe->_hoops_SRHA, _hoops_GGIA))
										_hoops_GACIP (nr, _hoops_PPAS)(nr, pe);
									else
										_hoops_IACIP (nr, pe);
								}
								if (!pe->_hoops_GAHA || !pe->_hoops_GAHA->list) {
									/* _hoops_RH _hoops_AIRI _hoops_HIGR _hoops_CSAP _hoops_HGGPR.  _hoops_RHGAR _hoops_ISHP _hoops_RH _hoops_HPHR _hoops_CPAP */
									nr.Modify()->_hoops_RGP &= (T_ANY_SHELL_EDGE|T_LIGHTS_FOR_EDGES);
									(*dc->_hoops_IPCI->draw_3d_polycylinder)(nr, (PolyCylinder const *)list->g);
								}
								if (pe->_hoops_GAHA == _hoops_SRCIP->_hoops_GRHIR) {
									/* _hoops_GASA: _hoops_GHAP'_hoops_GHGP _hoops_PII _hoops_IS _hoops_SHH _hoops_SHSS _hoops_IS _hoops_AACIP _hoops_ARI, _hoops_HIH _hoops_GHAP _hoops_GA'_hoops_RA _hoops_RHCA _hoops_RH _hoops_PCPCA
									 * _hoops_IH _hoops_RGR _hoops_AGIR _hoops_PPGC _hoops_SPCP _hoops_RH _hoops_GAHIR _hoops_ARI */
									/*_hoops_ICPCA (_hoops_SAHA->_hoops_PACIP);*/
								}
								else {
									pe->_hoops_GAHA->next = _hoops_SRCIP->_hoops_GRHIR;
									pe->_hoops_GAHA->backlink = &_hoops_SRCIP->_hoops_GRHIR;
									_hoops_SRCIP->_hoops_GRHIR = pe->_hoops_GAHA;
								}
								_hoops_CHPS->_hoops_GAHA = null;
							}
							else {
								nr.Modify()->_hoops_RGP &= (T_ANY_SHELL_EDGE|T_LIGHTS_FOR_EDGES);
								(*dc->_hoops_IPCI->draw_3d_polycylinder)(nr, (PolyCylinder const *)list->g);
							}
						}
						else {
							if (BIT (pe->_hoops_SRHA, _hoops_GGIA))
								_hoops_GACIP (nr, _hoops_PPAS)(nr, pe);
							else
								_hoops_IACIP (nr, pe);
						}
					}
				}	break;
				case _hoops_CACIP: {
					Polymarker const *pm = (Polymarker const *)list->item;
					if (list->g)
						dc->_hoops_RAI = list->g;
					_hoops_SACIP (nr, pm);
				}	break;

				case _hoops_IIIP: {
					_hoops_CPAGR (nr, (Polyline *)list->item);
				}	break;

				case _hoops_RCIP: {
					_hoops_SGPGR (nr, (Polygon *)list->item);
				}	break;

				case _hoops_HCIIR: {
					_hoops_GACR *dl = (_hoops_GACR *)list->item;
					_hoops_GPCIP (nr, dl);
				}	break;

				default: {	/* _hoops_GSSR _hoops_CPAP _hoops_CSSC */
					_hoops_RPHPP (nr, (Geometry *)list->item, _hoops_RAPI, true);
				}	break;
			}
			dc->_hoops_RAI = null;
		} while ((list = list->next) != null);

		dc->_hoops_RRCIP = _hoops_GRCIP;
		dc->path = _hoops_ARCIP;

		dc->_hoops_SPA->modelling_matrix = _hoops_CGCIP;
		dc->_hoops_SPA->color = _hoops_SGCIP;

		while (_hoops_PRCIP--) {
			_hoops_SGRS (dc);
		}
	}
}

GLOBAL_FUNCTION void HD_Free_Deferred_3D_Geometry (
	_hoops_PGCIP alter *			list) {

	_hoops_SSAGR(list);

	_hoops_PGCIP alter *			next;

	if (list != null) do {
		_hoops_SSAGR(list->item);
		_hoops_SSAGR(list->_hoops_IRCIP);
		_hoops_SSAGR(list->g);
		list->nr._hoops_SSAGR();

		next = list->next;

		switch (list->type) {
			case _hoops_CRCIP: {
				Tristrip *	ts = (Tristrip *)list->item;

				if (_hoops_ISAI (ts) == 0)
					HI_Free_Tristrip (ts);
			}	break;

			case _hoops_HACIP: {
				Polyedge *	pe = (Polyedge *)list->item;

				if (_hoops_ISAI (pe) == 0)
					HI_Free_Polyedge (pe);
			}	break;

			case _hoops_CACIP: {
				Polymarker *	pm = (Polymarker *)list->item;

				if (_hoops_ISAI (pm) == 0)
					HI_Free_Polymarker(pm);
			}	break;

			default: {	/* _hoops_GSSR _hoops_CPAP _hoops_CSSC */
				_hoops_HPRH ((Geometry *)list->item);
			}	break;
		}

		list->nr.release();
		list->path.release();

		_hoops_SSAGR(next);

		if (list->_hoops_IRCIP)
			_hoops_HPRH (list->_hoops_IRCIP);

		if (list->_hoops_GPCP)
			_hoops_HPRH (list->_hoops_GPCP);

		if (list->g)
			_hoops_HPRH (list->g);

		FREE (list, _hoops_PGCIP);
	} while ((list = next) != null);
}

GLOBAL_FUNCTION void HD_Reset_Tree_State (
	Net_Rendition alter &		nr) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;

	nr->_hoops_RCSHR &= ~_hoops_RPCIP;

	/* _hoops_HHSA _hoops_APCIP _hoops_AHCA 2D */
	nr->_hoops_RCSHR &= ~_hoops_GAHPP;

	if (BIT (_hoops_IHCR->heuristics, _hoops_IRI)) {
		if (!BIT(nr->current,_hoops_CSGGR)) {
			nr->_hoops_RCSHR |= _hoops_CSGGR;

			if (BIT (_hoops_RRGH->_hoops_SRI, _hoops_SGAAP))
				nr->_hoops_RCSHR |= _hoops_GSSHP;
			if (BIT (_hoops_RRGH->_hoops_SRI, _hoops_RRAAP))
				nr->_hoops_RCSHR |= _hoops_RSSHP;
		}
	}
	else {
		_hoops_PRGIP	_hoops_HRGIP = nr->_hoops_RCSHR & nr->current & _hoops_RSSHP;

		nr->_hoops_RCSHR &= ~_hoops_IRGIP;
		nr->_hoops_RCSHR |= _hoops_HRGIP;
	}

	/* _hoops_PGII _hoops_IIGR _hoops_RH _hoops_PPCIP _hoops_IH _hoops_PRHPA _hoops_AHCR _hoops_HSH - _hoops_HGPP _hoops_GAR _hoops_SISPR
	 * _hoops_CCSHP _hoops_AARAR _hoops_PAR _hoops_HPPA _hoops_GHC - _hoops_CHR _hoops_SHR _hoops_RCPP
	 * _hoops_GGR _hoops_SCII->_hoops_SCGR _hoops_CGPR _hoops_HPCIP _hoops_HRGR _hoops_AIARR.
	 * _hoops_RAH _hoops_HHH _hoops_IPCIP _hoops_IS _hoops_HGCR _hoops_RH _hoops_SCGR _hoops_HIHP _hoops_IPP
	 * _hoops_SGI (_hoops_SIHC _hoops_CPCIP _hoops_CCA _hoops_RH _hoops_PIAP!) _hoops_ISSC _hoops_GGR _hoops_RGAS _hoops_CCA
	 * _hoops_RGR _hoops_CRIPR _hoops_PIAP.
	 */
	if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC) && !BIT(nr->current, _hoops_CSGGR)) {
		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

		HD_Set_Z_Buffering_Transform (nr, false, false, 0.0f);

		if (_hoops_GGCC->_hoops_HGSC == _hoops_ACPHP)
			_hoops_GGCC->_hoops_HGSC = _hoops_PCPHP;
		else
			_hoops_GGCC->_hoops_HGSC = _hoops_RCPHP;
	}

	if (BIT (_hoops_IHCR->flags, _hoops_GRHH) && !BIT (nr->current, _hoops_SARIP)) {
		/* _hoops_SPCIP _hoops_HRGR _hoops_SHR _hoops_PSAP _hoops_ICPAA _hoops_GGR _hoops_IS _hoops_HPCIP -
		 * _hoops_AA _hoops_HHH _hoops_IPCIP _hoops_IS _hoops_IRHH _hoops_RH _hoops_SCGR _hoops_HIHP _hoops_IPP
		 * _hoops_SGI (_hoops_CPCIP _hoops_SIHC!) _hoops_IHGC "_hoops_SCGR" _hoops_GHCIP _hoops_RPHR.
		 */
		nr.Modify()->transform_rendition.Modify()->flags &= ~(_hoops_GRHH|_hoops_PRIR);
	}

	if (BIT (_hoops_IHCR->flags, _hoops_CSP) && !BIT (nr->current, _hoops_GPRIP)) {
		/* _hoops_RAHP _hoops_ARRS. */
		nr.Modify()->transform_rendition.Modify()->flags &= ~(_hoops_CSP|_hoops_RCRIP);
	}
}


#define _hoops_RHCIP		0x1
#define _hoops_AHCIP	0x2

local bool _hoops_PHCIP (
	Net_Rendition const & 		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path,
	bool						_hoops_HHCIP,
	int *						_hoops_IHCIP) {
	Display_Context const *		dc = nr->_hoops_SRA;
	bool						_hoops_HPRS = false;
	int							_hoops_CHCIP = 0;

	HD_Alternate_Hidden_Root ((Display_Context alter *)dc, _hoops_HHIIP);

	if (dc->_hoops_IHIIP[0] ||
		dc->_hoops_HASS[dc->_hoops_IASS] ||
		dc->_hoops_GPSS[dc->_hoops_IASS])
		_hoops_CHCIP |= _hoops_RHCIP;
	if (dc->_hoops_RPSS[dc->_hoops_IASS] && _hoops_HHCIP)
		_hoops_CHCIP |= _hoops_AHCIP;
	if (_hoops_IHCIP)
		*_hoops_IHCIP = _hoops_CHCIP;

	if (_hoops_CHCIP) {
		_hoops_HCSIR alter *	_hoops_ICSIR;
		Int_Rectangle const *		rect;

		_hoops_ICSIR = HD_Init_Frame_Buffer_Info (nr, _hoops_SRCP, path);
		rect = &nr->_hoops_SAIR->_hoops_SCIH;

		if (BIT(dc->_hoops_PGCC.flags, _hoops_PAGIP)) {
			if (_hoops_ICSIR->_hoops_AIIIP[0] != null) {
				int								_hoops_PIIIP, _hoops_HIIIP;
				int								_hoops_IIIIP, _hoops_CIIIP;

				_hoops_PIIIP = _hoops_ICSIR->_hoops_SIIIP.right - _hoops_ICSIR->_hoops_SIIIP.left + 1;
				_hoops_HIIIP = _hoops_ICSIR->_hoops_SIIIP.top - _hoops_ICSIR->_hoops_SIIIP.bottom + 1;
				_hoops_IIIIP = rect->right - rect->left + 1;
				_hoops_CIIIP = rect->top - rect->bottom + 1;

				if (_hoops_IIIIP != _hoops_PIIIP || _hoops_CIIIP != _hoops_HIIIP) {
					(*dc->_hoops_ACPGR->_hoops_ISPGR) (nr, _hoops_ICSIR->_hoops_AIIIP[0],
												   _hoops_ICSIR->_hoops_GCIIP[0]);
					_hoops_ICSIR->_hoops_AIIIP[0] = _hoops_ICSIR->_hoops_GCIIP[0] = null;
					_hoops_ICSIR->_hoops_PSPIP = false;
				}
			}

			if (!_hoops_ICSIR->_hoops_PSPIP) {
				if (_hoops_HHCIP) {
					if (_hoops_ICSIR->_hoops_GCIIP[0] == null)
						_hoops_GSIIP (nr, rect, null, &_hoops_ICSIR->_hoops_GCIIP[0]);
					if (_hoops_ICSIR->_hoops_GCIIP[0] == null) {
						((Display_Context alter *)dc)->_hoops_PGCC.flags &= ~_hoops_PAGIP;
						goto _hoops_HPAGR;
					}
					_hoops_PSIIP (nr, rect, null, _hoops_ICSIR->_hoops_GCIIP[0]);
				}
				else {
					if (_hoops_ICSIR->_hoops_AIIIP[0] == null)
						_hoops_GSIIP (nr, rect, &_hoops_ICSIR->_hoops_AIIIP[0], &_hoops_ICSIR->_hoops_GCIIP[0]);
					if (_hoops_ICSIR->_hoops_AIIIP[0] == null) {
						((Display_Context alter *)dc)->_hoops_PGCC.flags &= ~_hoops_PAGIP;
						goto _hoops_HPAGR;
					}
					_hoops_PSIIP (nr, rect, _hoops_ICSIR->_hoops_AIIIP[0], _hoops_ICSIR->_hoops_GCIIP[0]);
					_hoops_ICSIR->_hoops_SIIIP.left	= rect->left;
					_hoops_ICSIR->_hoops_SIIIP.right	= rect->right;
					_hoops_ICSIR->_hoops_SIIIP.bottom = rect->bottom;
					_hoops_ICSIR->_hoops_SIIIP.top	= rect->top;
					_hoops_ICSIR->_hoops_PCIIP.left   = rect->left;
					_hoops_ICSIR->_hoops_PCIIP.right	 = rect->right;
					_hoops_ICSIR->_hoops_PCIIP.bottom = rect->bottom;
					_hoops_ICSIR->_hoops_PCIIP.top	 = rect->top;
					_hoops_RSAI (&_hoops_ICSIR->_hoops_PCIIP, Int_Rectangle, &_hoops_ICSIR->_hoops_HCIIP);
					_hoops_ICSIR->_hoops_PSPIP = true;
				}
				_hoops_HPRS = true;
			}
		}
	}
_hoops_HPAGR:
	HD_Alternate_Hidden_Root ((Display_Context alter *)dc, _hoops_HHIIP);

	return _hoops_HPRS;
}


GLOBAL_FUNCTION void HD_Revisit_Overlay (
	Display_Context alter *		dc) {
	_hoops_CRCP const *				segment = dc->_hoops_AAHSR;
	Net_Rendition				nr = dc->_hoops_SHCIP.Copy();
	HD_Reset_Tree_State (nr);

	_hoops_CGRA			_hoops_SGRA = nr->_hoops_SAIR;

	dc->_hoops_CPGPR = segment->_hoops_CPGPR;

	_hoops_HCSIR alter *	_hoops_ICSIR = null;
	bool						_hoops_CHPIP = false;

	{
		_hoops_SPAGR					_hoops_GHAGR (segment->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (segment, _hoops_HICS());

		if (_hoops_CSC != null) {
			_hoops_SGRA->_hoops_ASSIR = _hoops_CSC;
			_hoops_ICSIR = _hoops_CSC->_hoops_PSSIR();
			if (_hoops_ICSIR != null)
				_hoops_CHPIP = _hoops_ICSIR->_hoops_PSPIP;
		}
	}

	_hoops_IHPIP (nr, segment, _hoops_HICS(), _hoops_CHPIP, true);

	nr.Modify()->_hoops_SAIR.Modify()->_hoops_ASIHP |= _hoops_ACARP;

	{	// _hoops_RGR _hoops_GICIP _hoops_RH _hoops_IAGIP _hoops_CPCI
		_hoops_AGSGA		_hoops_PGSGA (dc);
		_hoops_HSPPP *	_hoops_RICIP = dc->_hoops_HRHPP[_hoops_SRHPP].list;
		int						_hoops_AICIP = dc->flags;

		dc->_hoops_HRHPP[_hoops_SRHPP].list = null;
		dc->flags &= ~_hoops_RASS;
		HD_Search_Null_Clip_Tree (nr, segment, _hoops_HICS(),  0, true);
		dc->flags = _hoops_AICIP;
		dc->_hoops_HRHPP[_hoops_SRHPP].list = _hoops_RICIP;

		if (!BIT (nr->transform_rendition->flags, _hoops_CGHIP)) {
			_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

			_hoops_SGRA = nr->_hoops_SAIR;
			_hoops_GGCC->_hoops_AGAA.left = _hoops_SGRA->_hoops_PHRA.left;
			_hoops_GGCC->_hoops_AGAA.right = _hoops_SGRA->_hoops_PHRA.right;
			_hoops_GGCC->_hoops_AGAA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
			_hoops_GGCC->_hoops_AGAA.top = _hoops_SGRA->_hoops_PHRA.top;
			_hoops_GGCC->flags |= _hoops_CGHIP&_hoops_PASP;
		}
	}

	if (dc->_hoops_IHIIP[0] ||
		(_hoops_ICSIR != null && _hoops_ICSIR->_hoops_SCIIP)) {

		/* _hoops_PIP: _hoops_RGR _hoops_CGH _hoops_HAR _hoops_ARPR _hoops_PCCP _hoops_RSIIP, _hoops_RGAR _hoops_SSS _hoops_SPR */
		if (_hoops_ICSIR == null)
			_hoops_ICSIR = HD_Init_Frame_Buffer_Info (nr, segment, _hoops_HICS());

		_hoops_APSRR(dc, "Revisit_Overlay undraw_spriting","", 0);
		_hoops_RGCIP (dc, nr, _hoops_ICSIR);
	}
}

GLOBAL_FUNCTION void _hoops_PICIP (
	Display_Context alter *		dc) {
	_hoops_CRCP const *				segment = dc->_hoops_AAHSR;
	Net_Rendition				nr = dc->_hoops_SHCIP.Copy();
	HD_Reset_Tree_State (nr);

	_hoops_CGRA			_hoops_SGRA = nr->_hoops_SAIR;
	bool						_hoops_CHPIP = false;

	dc->_hoops_CPGPR = segment->_hoops_CPGPR;

	{
		_hoops_SPAGR					_hoops_GHAGR (segment->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (segment, _hoops_HICS());

		if (_hoops_CSC != null) {
			_hoops_SGRA->_hoops_ASSIR = _hoops_CSC;
			_hoops_HCSIR const *	_hoops_ICSIR = _hoops_CSC->_hoops_PSSIR();
			if (_hoops_ICSIR != null)
				_hoops_CHPIP = _hoops_ICSIR->_hoops_PSPIP;
		}
	}

	_hoops_IHPIP (nr, segment, _hoops_HICS(), _hoops_CHPIP, true);

	nr.Modify()->_hoops_SAIR.Modify()->_hoops_ASIHP |= _hoops_ACARP;

	if (!BIT (nr->transform_rendition->flags, _hoops_CGHIP)) {
		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

		_hoops_SGRA = nr->_hoops_SAIR;
		_hoops_GGCC->_hoops_AGAA.left = _hoops_SGRA->_hoops_PHRA.left;
		_hoops_GGCC->_hoops_AGAA.right = _hoops_SGRA->_hoops_PHRA.right;
		_hoops_GGCC->_hoops_AGAA.bottom = _hoops_SGRA->_hoops_PHRA.bottom;
		_hoops_GGCC->_hoops_AGAA.top = _hoops_SGRA->_hoops_PHRA.top;
		_hoops_GGCC->flags |= _hoops_CGHIP&_hoops_PASP;
	}

	_hoops_APSRR(dc, "last_call_for_spriting draw_spriting","", 0);
	_hoops_CPIIP (dc, nr, false, segment, _hoops_HICS(), null, null);
}


GLOBAL_FUNCTION void HD_Draw_Deferred_Trees (
	Display_Context alter *		dc) {
	Activity					_hoops_IPHIP;

	ASSERT(dc->_hoops_RIGC != null);

	_hoops_IPHIP = dc->_hoops_CPGPR;

	/* _hoops_SR _hoops_RRP _hoops_IS _hoops_RHAPA _hoops_PPR _hoops_IRCH _hoops_HCR _hoops_RH _hoops_CPAP _hoops_CPHRA _hoops_HII _hoops_RH
	 * _hoops_PISI _hoops_HIGR _hoops_ARPP _hoops_GHGA _hoops_GII _hoops_IIGR _hoops_RH _hoops_AISIR _hoops_CPHRA. _hoops_HSRR
	 * _hoops_HICIP, '_hoops_IICIP' _hoops_ICHHR _hoops_IHGC _hoops_IIGR _hoops_RH _hoops_CICIP _hoops_SSRR
	 * _hoops_PPSR _hoops_GGR _hoops_RH _hoops_HIGR _hoops_IRS _hoops_CPAP _hoops_HHIS _hoops_SIAS _hoops_SHH _hoops_SICIP, _hoops_PPR
	 * _hoops_CSPH->_hoops_GCCIP _hoops_ICHHR _hoops_IHGC _hoops_IIGR _hoops_IGH _hoops_IIH _hoops_CHR
	 * _hoops_GII _hoops_GGR _hoops_IIH _hoops_HPGR _hoops_HCR.
	 */

	while (dc->_hoops_HRHPP[_hoops_SRHPP].list != null) {
		_hoops_HSPPP alter *	_hoops_ISPPP = (_hoops_HSPPP alter *)dc->_hoops_HRHPP[_hoops_SRHPP].list;
		_hoops_HSPPP const *	_hoops_RCCIP = _hoops_ISPPP->next;
		_hoops_CRCP const *				segment = _hoops_ISPPP->segment;
		bool						_hoops_ACCIP = false;
		int							_hoops_PCCIP = _hoops_ISPPP->_hoops_APHGA->_hoops_RCSHR;
		Net_Rendition				nr;
		Activity					_hoops_HCCIP = 0;

		dc->_hoops_HRHPP[_hoops_SRHPP]._hoops_ASRGR = &_hoops_ISPPP->next;

		switch (_hoops_ISPPP->stage) {
			case _hoops_ICCIP: {
				_hoops_HHCR			_hoops_IHCR;
				_hoops_CGRA			_hoops_SGRA;

				HD_Reset_Tree_State (_hoops_ISPPP->_hoops_APHGA);
				nr = _hoops_ISPPP->_hoops_APHGA;
				_hoops_IHCR = nr->transform_rendition;
				_hoops_SGRA = nr->_hoops_SAIR;

				dc->_hoops_CPGPR = _hoops_ISPPP->_hoops_CPGPR;
				dc->_hoops_AGGIP = (_hoops_IHCR->_hoops_RHPHP != _hoops_AHPHP);

				/* _hoops_RPP _hoops_PIASR, _hoops_HGCR _hoops_RH _hoops_RPPS _hoops_ARP _hoops_GH _hoops_PPR (_hoops_CCCIP) _hoops_CHCC */
				if (BIT (nr->_hoops_RCSHR, _hoops_CRHPP)) {
					_hoops_HCSIR const *		_hoops_ICSIR = null;
					bool							_hoops_CHPIP = false;

					_hoops_HCCIP = dc->_hoops_CPGPR;

					{
						_hoops_SPAGR						_hoops_GHAGR (segment->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
						_hoops_AHAGR *				_hoops_CSC = HI_Find_Segment_Cache (segment, _hoops_ISPPP->path);

						if (_hoops_CSC != null) {
							_hoops_SGRA->_hoops_ASSIR = _hoops_CSC;

							_hoops_ICSIR = _hoops_CSC->_hoops_PSSIR();
							if (_hoops_ICSIR != null)
								_hoops_CHPIP = _hoops_ICSIR->_hoops_PSPIP;
						}
					}

					if (_hoops_SGRA->_hoops_SCIH._hoops_RPCIR(_hoops_SGRA->_hoops_PHRA)) {
						_hoops_IHPIP (nr, segment, _hoops_ISPPP->path, _hoops_CHPIP, false);
						/* _hoops_IRHH _hoops_RCRR _hoops_AGCR _hoops_CHR _hoops_GH-_hoops_IS-_hoops_ICGIP */
						_hoops_ISPPP->_hoops_APHGA = nr;
						_hoops_IHCR = nr->transform_rendition;
						_hoops_SGRA = nr->_hoops_SAIR;

						if (_hoops_ISPPP->_hoops_SPIIP) {
							_hoops_SCCIP alter * _hoops_GSCIP;
							/* _hoops_GHCA _hoops_RRP _hoops_IS _hoops_RCPS _hoops_ISSC _hoops_SPS _hoops_GHIR */
							ALLOC (_hoops_GSCIP, _hoops_SCCIP);
							_hoops_GSCIP->segment = segment;
							_hoops_PRRH (segment);
							_hoops_GSCIP->next = (_hoops_SCCIP alter *)dc->_hoops_RSCIP;
							dc->_hoops_RSCIP = _hoops_GSCIP;
						}
					}
					else
						_hoops_ACCIP = true;

					if (_hoops_ICSIR != null) {
						int			_hoops_ASCIP;
						int			_hoops_PSCIP;

						((_hoops_HCSIR alter *)_hoops_ICSIR)->_hoops_GHIAA = false;

						/*
						 * _hoops_HSCIP. _hoops_RAIGR _hoops_AGRP _hoops_GGR _hoops_CIHH _hoops_PGAP _hoops_GRS _hoops_AGRP _hoops_RH _hoops_SRHR
						 * _hoops_IGIR _hoops_GCA _hoops_IRS _hoops_RPPS _hoops_AIIAP, _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_RGRIR _hoops_RH
						 * _hoops_AIIAP _hoops_SGI _hoops_ARI _hoops_RIIA _hoops_IIGR _hoops_CHRPA _hoops_IH _hoops_RH _hoops_AASA _hoops_IS
						 * _hoops_ISCIP _hoops_PGAP _hoops_HRGR _hoops_HAH _hoops_IAH _hoops_IH _hoops_RPPS _hoops_PRCA.
						 */
						_hoops_ASCIP = _hoops_SGRA->_hoops_SCIH.right - _hoops_SGRA->_hoops_SCIH.left + 1  +  2 * dc->_hoops_ARAIP;
						if (!BIT(nr->flags, _hoops_SISHP))
							_hoops_PSCIP = _hoops_SGRA->_hoops_SCIH.top - _hoops_SGRA->_hoops_SCIH.bottom + 1  +  2 * dc->_hoops_ARAIP;
						else {
							_hoops_PSCIP = _hoops_IHCR->_hoops_AGAA.top - _hoops_IHCR->_hoops_AGAA.bottom + 1  +  2 * dc->_hoops_ARAIP;
							// _hoops_ASSS _hoops_IRS _hoops_CSCIP _hoops_IS _hoops_RCPS _hoops_RHIR _hoops_GRP _hoops_RH _hoops_SCGR _hoops_SRHR _hoops_RPP _hoops_SCH _hoops_SRIPR _hoops_IS _hoops_SHH _hoops_SSCIP
							if (_hoops_ICSIR->_hoops_HIAI != null &&  _hoops_PSCIP < _hoops_ICSIR->_hoops_HIAI->height)
								_hoops_PSCIP = _hoops_ICSIR->_hoops_HIAI->height;
						}

						if (_hoops_ICSIR->_hoops_HIAI != null &&
							(_hoops_ICSIR->_hoops_HIAI->width  != _hoops_ASCIP	 ||
							 _hoops_ICSIR->_hoops_HIAI->height != _hoops_PSCIP) ||
							_hoops_ICSIR->depth_buffer != null &&
							(_hoops_ICSIR->depth_buffer->width  != _hoops_ASCIP ||
							 _hoops_ICSIR->depth_buffer->height != _hoops_PSCIP)) {
							dc->_hoops_CPGPR |= _hoops_RCGSA & ~_hoops_AASCA;
							_hoops_SASIR (dc->_hoops_RIGC, segment, _hoops_HGSCA);
							((_hoops_CRCP *)segment)->_hoops_CPGPR |= dc->_hoops_CPGPR;
						}
					}
				}
				else
					_hoops_SGRA->_hoops_ASIHP |= _hoops_ACARP;

				if (!ANYBIT (dc->_hoops_CPGPR, _hoops_IPPGP|_hoops_CHPGP) || _hoops_ACCIP)
					break;


				if (!BIT(dc->_hoops_CPGPR, _hoops_CHPGP) &&
					!BIT (_hoops_IHCR->flags, _hoops_CGHIP)) {
					if (_hoops_CAPIP (dc, segment, _hoops_IPPGP) &&
						ANYBIT (segment->_hoops_RCGC, T_WINDOWS|_hoops_AHASA)) {
						nr.Modify()->_hoops_SAIR.Modify()->_hoops_ASIHP |= _hoops_ACARP;
						HD_Search_Null_Clip_Tree (nr, segment, _hoops_ISPPP->path, 0, false);
					}

					if (!BIT (nr->transform_rendition->flags, _hoops_CGHIP)) {
						_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

						_hoops_SGRA = nr->_hoops_SAIR;
						_hoops_GGCC->_hoops_AGAA = _hoops_SGRA->_hoops_PHRA;
						_hoops_GGCC->flags |= _hoops_CGHIP;
						_hoops_GGCC->flags |= _hoops_PASP;
					}

					_hoops_HSPPP const *	_hoops_GGSIP = _hoops_ISPPP->next;

					if (_hoops_GGSIP == null ||
						BIT (_hoops_GGSIP->_hoops_APHGA->_hoops_RCSHR, _hoops_CRHPP)) {

						_hoops_APSRR(dc, "Deferred_Trees Setup draw_spriting","", 0);
						_hoops_CPIIP (dc, nr, _hoops_ISPPP->_hoops_SPIIP, _hoops_ISPPP->segment, _hoops_ISPPP->path, _hoops_ISPPP->next, _hoops_RCCIP);
					}

					break;	//!
				}

				++_hoops_ISPPP->stage;
			}	_hoops_HHHI;

			case _hoops_RGSIP: {
				if (_hoops_IACI(dc))
					return;

				nr = _hoops_ISPPP->_hoops_APHGA;

				/* _hoops_IRAA _hoops_PICP _hoops_IIGR _hoops_IASI-_hoops_AHPIP _hoops_CIPH _hoops_GGR _hoops_RGR _hoops_RPPS, _hoops_RPP _hoops_GII (_hoops_AGSIP) */

				/* _hoops_IPCP "_hoops_PGSIP|_hoops_HGSIP"
				 * _hoops_AGSR "_hoops_RGHH _hoops_IASI _hoops_AHPIP _hoops_IGSIP _hoops_HA _hoops_HCCPR _hoops_SCH'_hoops_GRI
				 * _hoops_PGICR _hoops_GGR _hoops_IRS _hoops_ARAH-_hoops_RRH _hoops_RPPS".
				 */

				if (BIT (_hoops_PCCIP, _hoops_CRHPP) &&	/* _hoops_HII _hoops_RHGS _hoops_CGSIP _hoops_GPP _hoops_AHAR */
					ALLBITS (segment->_hoops_CPGPR,
							 _hoops_CPPGP|
							 _hoops_HPPGP) &&
					!ANYBIT (nr->_hoops_SAIR->_hoops_ASIHP, _hoops_GCARP |
										_hoops_RCARP)) {
#ifndef DISABLE_PARTIAL_ERASE
					HD_Draw_Partial_Erase_Tree (nr, segment, _hoops_ISPPP->path,
								BIT (segment->_hoops_CPGPR, _hoops_ICHPA));
#endif

					/* _hoops_IRHH _hoops_RCRR _hoops_SPHGR _hoops_GPP _hoops_SCIA _hoops_IIGR _hoops_CCAHR-_hoops_SGSIP _hoops_CPAP _hoops_HGCR _hoops_RHHR */
					/* (_hoops_HRGR _hoops_RGR _hoops_RH _hoops_RPHR _hoops_AHAP _hoops_IS _hoops_AA ?) */
					dc->_hoops_CPGPR |= _hoops_APPGP|_hoops_PPPGP;
				}

				/* _hoops_GGSR-_hoops_IIGR-_hoops_AGR _hoops_GHCA _hoops_HS _hoops_RPII _hoops_PISI _hoops_RAS _hoops_GGR-_hoops_AGR _hoops_CIPH
				 * _hoops_SGS _hoops_CSAP _hoops_AIAH _hoops_GPP _hoops_RH _hoops_SGSI _hoops_HIGR. _hoops_RHRPA _hoops_ISCP _hoops_SCGR _hoops_PAPA
				 * _hoops_PPR _hoops_GGSC _hoops_SCH _hoops_CGH _hoops_HA _hoops_SHH _hoops_ICIC _hoops_IS _hoops_PGSA _hoops_RH _hoops_GRSIP
				 * _hoops_AHAP _hoops_GPP _hoops_RH _hoops_HIGR. _hoops_PHGP _hoops_SCAC _hoops_RH _hoops_IGRH.
				 */
				nr->_hoops_RCSHR &= ~_hoops_RRSIP;
				_hoops_ISPPP->_hoops_ARSIP = nr->_hoops_RCSHR;

				if (!BIT (nr->_hoops_RCSHR, _hoops_CRSI) &&
					!BIT (nr->_hoops_SAIR->_hoops_ASIHP, _hoops_GCARP) &&
					BIT (dc->_hoops_CPGPR, _hoops_GIPGP)) {
					_hoops_HCSIR alter	*	_hoops_ICSIR = null;
					bool						_hoops_PRSIP;

					_hoops_PRSIP = (nr->_hoops_SAIR->_hoops_ASSIR != null &&
								 nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR() != null);

					if (!_hoops_PRSIP) {
						_hoops_SPAGR					_hoops_GHAGR (segment->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
						_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (segment, _hoops_ISPPP->path);

						_hoops_PRSIP = (_hoops_CSC != null && _hoops_CSC->_hoops_PSSIR() != null);
					}

					if (_hoops_PRSIP) {
						/* _hoops_PIP: _hoops_RGR _hoops_CGH _hoops_HAR _hoops_ARPR _hoops_PCCP _hoops_RSIIP, _hoops_RGAR _hoops_SSS _hoops_SPR */
						_hoops_ICSIR = HD_Init_Frame_Buffer_Info (nr, segment, _hoops_ISPPP->path);
					}

					_hoops_APSRR(dc, "Deferred_Trees Prepare undraw_spriting","", 0);
					_hoops_RGCIP (dc, nr, _hoops_ICSIR);
				}

				++_hoops_ISPPP->stage;
			}	_hoops_HHHI;

			case _hoops_HRSIP: {
				if (_hoops_IACI(dc))
					return;

				nr = _hoops_ISPPP->_hoops_APHGA;

				if (!BIT (dc->_hoops_IASS, _hoops_HHIIP) &&
					dc->_hoops_IHIIP[0] != null) {
					_hoops_CGRA &		_hoops_SGRA = nr->_hoops_SAIR;
					_hoops_HCSIR *		_hoops_ICSIR = null;

					if (_hoops_SGRA->_hoops_ASSIR != null)
						_hoops_ICSIR = _hoops_SGRA->_hoops_ASSIR->_hoops_PSSIR();

					if (_hoops_ICSIR != null && _hoops_ICSIR->_hoops_SCIIP) {
						_hoops_APSRR(dc, "Deferred_Trees Draw_Tree undraw_spriting","", 0);
						_hoops_RGCIP (dc, nr, _hoops_ICSIR);
					}
				}

				/* _hoops_HAPR _hoops_IH _hoops_PISI _hoops_CPAP _hoops_CPHRA */
				_hoops_PCCAR {
					/* _hoops_PHHR _hoops_PGSA _hoops_RH _hoops_HHIS _hoops_IH _hoops_HPHR */
					if (_hoops_GGPGR(nr)) {
						if (!BIT (dc->_hoops_IASS, _hoops_HHIIP)) {
							if (dc->_hoops_IHIIP[0] != null) {
								_hoops_APSRR(dc, "Deferred_Trees Draw_Tree draw_spriting 1","", 0);
								_hoops_CPIIP (dc, nr, _hoops_ISPPP->_hoops_SPIIP, _hoops_ISPPP->segment, _hoops_ISPPP->path, _hoops_ISPPP->next, _hoops_RCCIP);
							}
						}
						else
							_hoops_APSRR(dc, "exit update while draw_spriting 1","", 0);
						return;
					}

					if (dc->_hoops_AHSI != null)
						_hoops_AASS (nr, null, _hoops_HICS());
					else if (_hoops_ISPPP->_hoops_CPCR != null) {
						//_hoops_CSPH->_hoops_RHHIP (_hoops_IRSIP->_hoops_CISI->_hoops_CRSIP, _hoops_IRSIP->_hoops_CISI->_hoops_CAGH);	// _hoops_PPR _hoops_ASGGR _hoops_IRS _hoops_CCAH _hoops_GIIS _hoops_IH _hoops_SAHR _hoops_RGR _hoops_HHIS
						//_hoops_CSPH->_hoops_GHHIP->_hoops_CRAA = _hoops_IRSIP->_hoops_CISI->_hoops_CRAA;
						_hoops_AASS (_hoops_ISPPP->_hoops_CPCR->_hoops_APHGA, _hoops_ISPPP->_hoops_CPCR->segment, _hoops_ISPPP->_hoops_CPCR->path);
					}
					else if (dc->_hoops_SRSIP[dc->_hoops_IASS] == null) {
						//_hoops_CSPH->_hoops_RHHIP (_hoops_SCII, _hoops_CAGH);	// _hoops_PPR _hoops_ASGGR _hoops_IRS _hoops_CCAH _hoops_GIIS _hoops_IH _hoops_SAHR _hoops_RGR _hoops_HHIS
						//_hoops_CSPH->_hoops_GHHIP->_hoops_CRAA = _hoops_IRSIP->_hoops_CRAA;
						_hoops_AASS (nr, segment, _hoops_ISPPP->path);
					}

					if (dc->_hoops_AHSI != null) {
						if (!BIT (dc->_hoops_IASS, _hoops_HHIIP)) {
							if (dc->_hoops_IHIIP[0] != null) {
								_hoops_APSRR(dc, "Deferred_Trees Draw_Tree draw_spriting 2","", 0);
								_hoops_CPIIP (dc, nr, _hoops_ISPPP->_hoops_SPIIP, _hoops_ISPPP->segment, _hoops_ISPPP->path, _hoops_ISPPP->next, _hoops_RCCIP);
							}
						}
						else
							_hoops_APSRR(dc, "exit update while draw_spriting 2","", 0);
						return;
					}

					/* _hoops_GIGGA _hoops_SSAI*/
					if (dc->_hoops_GASIP) {
						_hoops_AGSGA	_hoops_PGSGA (dc);
						_hoops_RIGGA(nr, dc->_hoops_GASIP->used,
							dc->_hoops_GASIP->pts, dc->_hoops_GASIP->colors, 0);

						FREE_ARRAY(dc->_hoops_GASIP->pts, dc->_hoops_GASIP->allocated, DC_Point);
						FREE_ARRAY(dc->_hoops_GASIP->colors, dc->_hoops_GASIP->allocated, RGBAS32);
						FREE(dc->_hoops_GASIP, DC_Polydot_Batch);
						dc->_hoops_GASIP = 0;
					}


					/* _hoops_HHIS _hoops_SPIC _hoops_GHCA _hoops_GPGSA _hoops_SCH _hoops_GH, _hoops_PPR _hoops_SR _hoops_RRP _hoops_GIGR _hoops_GICS _hoops_SPHR */
					dc->_hoops_CPGPR = _hoops_ISPPP->_hoops_CPGPR;
					dc->flags |= _hoops_RASS;

					while (dc->_hoops_HRHPP[_hoops_IRHPP].list == null &&
							dc->_hoops_AGHPP != null &&
							dc->_hoops_AGHPP->Count() > 0) {

						_hoops_RGHPP alter *	_hoops_SGCCA;
						int							_hoops_IGIC;

						dc->_hoops_AGHPP->Pop(&_hoops_SGCCA, &_hoops_IGIC);
						dc->_hoops_HGHPP->RemoveItem(_hoops_IGIC);

						if (_hoops_SGCCA->list != null) {
							*dc->_hoops_HRHPP[_hoops_IRHPP]._hoops_ASRGR = _hoops_SGCCA->list;

							if (_hoops_SGCCA->_hoops_ASRGR == &_hoops_SGCCA->list)
								dc->_hoops_HRHPP[_hoops_IRHPP]._hoops_ASRGR = &dc->_hoops_HRHPP[_hoops_IRHPP].list;
							else
								dc->_hoops_HRHPP[_hoops_IRHPP]._hoops_ASRGR = _hoops_SGCCA->_hoops_ASRGR;
						}

						FREE (_hoops_SGCCA, _hoops_RGHPP);
					}

					if (dc->_hoops_HRHPP[_hoops_IRHPP].list == null ||
						!ANYBIT (dc->_hoops_HRHPP[_hoops_IRHPP].list->_hoops_APHGA->_hoops_RCSHR,
								 _hoops_GSSHP|_hoops_RSSHP)) {
						int			_hoops_CHCIP = 0;

						segment = _hoops_ISPPP->segment;

						/* _hoops_GRH _hoops_AGIR -- _hoops_AA _hoops_SR _hoops_HS _hoops_CIPH _hoops_RAAP _hoops_HII _hoops_ICCGR _hoops_CCSHP _hoops_AARAR _hoops_SGS
						 * _hoops_CSAP _hoops_HAR _hoops_CHHHP _hoops_HPGR _hoops_SGS _hoops_GHIR?	_hoops_RPP _hoops_HIS, _hoops_SR _hoops_PIHA _hoops_HS _hoops_IHSP, _hoops_PPR
						 * _hoops_CGH _hoops_AIRI _hoops_SCH _hoops_CGPR _hoops_SR _hoops_CHR _hoops_CPHR _hoops_CCA _hoops_RGR _hoops_RPPS (_hoops_PAR _hoops_HPGR _hoops_CHGC _hoops_CPHR
						 * _hoops_CCA _hoops_RH _hoops_SCGR _hoops_CCSHP _hoops_SSAI) */
						if (dc->_hoops_HASS[dc->_hoops_IASS] != null ||
							dc->_hoops_SRSIP[dc->_hoops_IASS] != null) {
							HD_See_Whats_Hidden (nr);

							if (dc->_hoops_SRSIP[dc->_hoops_IASS] != null) {	// _hoops_AGRRR
								if (!BIT (dc->_hoops_IASS, _hoops_HHIIP) &&
									dc->_hoops_IHIIP[0] != null) {

									_hoops_APSRR(dc, "Deferred_Trees Draw_Tree See_Whats_Hidden","", 0);
									_hoops_CPIIP (dc, nr, _hoops_ISPPP->_hoops_SPIIP, _hoops_ISPPP->segment, _hoops_ISPPP->path, _hoops_ISPPP->next, _hoops_RCCIP);
								}
								return;
							}
						}

						/* _hoops_PRSSR, _hoops_AA _hoops_SR _hoops_HS _hoops_PISI 3d _hoops_CPAP _hoops_IH _hoops_HCH-_hoops_ICH _hoops_IHSP? */
						if (dc->_hoops_GPSS[dc->_hoops_IASS] != null) {
							_hoops_PGCIP *			item = null;
							_hoops_HCSIR *		_hoops_ICSIR = HD_Init_Frame_Buffer_Info (nr, segment, _hoops_ISPPP->path);

							_hoops_PHCIP (nr, segment, _hoops_ISPPP->path, true, &_hoops_CHCIP);

							// _hoops_SRAI _hoops_RH _hoops_ARHP _hoops_HIGR
							while ((item = dc->_hoops_RPSS[dc->_hoops_IASS]) != null) {
								dc->_hoops_RPSS[dc->_hoops_IASS] = item->next;
								item->next = dc->_hoops_GPSS[dc->_hoops_IASS];
								dc->_hoops_GPSS[dc->_hoops_IASS] = item;
							}

							_hoops_SSGGR (dc);

							if (BIT(dc->flags, _hoops_ICPGR) && _hoops_CHCIP) {
								_hoops_ICIIP (nr, null, null, _hoops_ICSIR->_hoops_GCIIP[0]);
								_hoops_APSRR(dc, "depth_peeling Restore_Region","", (int)(POINTER_SIZED_INT)_hoops_ICSIR);
								_hoops_ICSIR->_hoops_SCIIP = false;
								dc->flags &= ~_hoops_ICPGR;
							}
							if (_hoops_ICSIR->_hoops_GCIIP[0] && !_hoops_ICSIR->_hoops_AIIIP[0]) {
								(*dc->_hoops_ACPGR->_hoops_ISPGR) (nr, null, _hoops_ICSIR->_hoops_GCIIP[0]);
								_hoops_ICSIR->_hoops_GCIIP[0] = null;
							}
						}

						if (dc->_hoops_RPSS[dc->_hoops_IASS] != null) {
							if (!(_hoops_GGPGR(nr)))
								HD_Draw_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS], true);
							HD_Free_Deferred_3D_Geometry (dc->_hoops_RPSS[dc->_hoops_IASS]);
							dc->_hoops_RPSS[dc->_hoops_IASS] = null;
						}
						if (BIT (_hoops_CHCIP, _hoops_RHCIP)) {
							if (!(_hoops_GGPGR(nr))) {
								_hoops_PHCIP (nr, segment, _hoops_ISPPP->path, false, null);
								dc->_hoops_CPGPR &= ~_hoops_GIPGP;
							}
						}
					}

					dc->_hoops_RASIP(_hoops_AASIP);

					if (_hoops_ISPPP->_hoops_CPCR != null) {
						_hoops_ISPPP->_hoops_CPCR->_hoops_APHGA.release();
						_hoops_ISPPP->_hoops_CPCR->path.release();
						FREE (_hoops_ISPPP->_hoops_CPCR, _hoops_HSPPP);
						_hoops_ISPPP->_hoops_CPCR = null;
					}

					if (dc->_hoops_HRHPP[_hoops_IRHPP].list != null ||
						dc->_hoops_HRHPP[_hoops_RAHPP].list != null) {
						_hoops_HSPPP alter *	_hoops_PASIP;
						_hoops_RGHPP alter *	_hoops_SGCCA;

						if (dc->_hoops_HRHPP[_hoops_IRHPP].list != null)
							_hoops_SGCCA = &dc->_hoops_HRHPP[_hoops_IRHPP];
						else
							_hoops_SGCCA = &dc->_hoops_HRHPP[_hoops_RAHPP];

						_hoops_PASIP = (_hoops_HSPPP alter *)_hoops_SGCCA->list;
						_hoops_SGCCA->list = _hoops_PASIP->next;
						_hoops_SGCCA->_hoops_ASRGR = &_hoops_SGCCA->list;

						if (_hoops_PASIP->geometry == null)
							_hoops_GPRH(_hoops_HASIP)++;
						else if (_hoops_PASIP->geometry != null) {
							if (_hoops_PASIP->geometry->type == _hoops_HCIIR)
								_hoops_GPRH(_hoops_IASIP)++;
							else if (_hoops_PASIP->geometry->type == _hoops_AHIP)
								_hoops_GPRH(_hoops_CASIP)++;
							else
								_hoops_GPRH(_hoops_SASIP)++;
						}

						HD_Reset_Tree_State (_hoops_PASIP->_hoops_APHGA);
						nr = _hoops_PASIP->_hoops_APHGA;

						segment = _hoops_PASIP->segment;
						dc->_hoops_CPGPR = _hoops_PASIP->_hoops_CPGPR;

						_hoops_ISPPP->_hoops_CPCR = _hoops_PASIP;
						_hoops_PASIP->next = null;

#if 0
						while (_hoops_SGCCA->list &&
							   _hoops_SGCCA->list->_hoops_APHGA->_hoops_RCSHR == nr->_hoops_RCSHR &&
							   !ANYBIT (nr->_hoops_IRR->_hoops_SRI, _hoops_PRAAP|_hoops_SICI)) {
							_hoops_PASIP = (_hoops_HSPPP alter *)_hoops_SGCCA->list;
							_hoops_SGCCA->list = _hoops_PASIP->next;
							_hoops_SGCCA->_hoops_ASRGR = (_hoops_HSPPP alter * alter *)&_hoops_SGCCA->list;

							_hoops_PASIP->next = *dc->_hoops_GPSIP._hoops_ASRGR;
							*dc->_hoops_GPSIP._hoops_ASRGR = _hoops_PASIP;
							dc->_hoops_GPSIP._hoops_ASRGR = &_hoops_PASIP->next;
						}
#endif
					}
					else if (dc->_hoops_AGGIP) {
						if (nr->transform_rendition->_hoops_PGGIP != _hoops_HHPHP) {
							Net_Rendition alter &		_hoops_CCIIP = _hoops_ISPPP->_hoops_APHGA.Modify();
							_hoops_HHCR alter &	_hoops_GGCC = _hoops_CCIIP->transform_rendition.Modify();

							// _hoops_ASIGA _hoops_RSH _hoops_PAH _hoops_RGR _hoops_SAHR _hoops_GRPHA?
							_hoops_CCIIP->_hoops_RCSHR = _hoops_ISPPP->_hoops_ARSIP & ~_hoops_CRHPP;
							_hoops_CCIIP->current = 0;

							_hoops_GGCC->_hoops_PGGIP = _hoops_HHPHP;
							if (_hoops_GGCC->_hoops_RHPHP == _hoops_PHPHP) {
								_hoops_GGCC->_hoops_RHPHP = _hoops_HHPHP;
								HD_Downwind_Camera (_hoops_CCIIP, (Attribute *)_hoops_GGCC->_hoops_SPH);
							}
							else
								_hoops_CCIIP->_hoops_RCSHR &= ~_hoops_PRHIP;

							nr = _hoops_ISPPP->_hoops_APHGA;
							dc->_hoops_CPGPR = _hoops_ISPPP->_hoops_CPGPR;
						}
						else
							break;
					}
					else
						break;
				}


				_hoops_HSPPP const *		_hoops_GGSIP = _hoops_ISPPP->next;

				if (_hoops_GGSIP == null ||
					BIT (_hoops_GGSIP->_hoops_APHGA->_hoops_RCSHR, _hoops_CRHPP)) {

					dc->_hoops_CPGPR = _hoops_HCCIP;

					_hoops_APSRR(dc, "Deferred_Trees Draw_Tree draw_spriting 3","", 0);
					_hoops_CPIIP (dc, nr,  _hoops_ISPPP->_hoops_SPIIP, _hoops_ISPPP->segment, _hoops_ISPPP->path, _hoops_ISPPP->next, _hoops_RCCIP);

					dc->flags &= ~_hoops_RGSGA;

					// _hoops_RPSIP _hoops_SGGR _hoops_PPRAR _hoops_HCHSR _hoops_SRHR
					if (ANYBIT (segment->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR) &&
						nr->_hoops_SAIR->_hoops_ASSIR != null &&
						nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR() != null &&
						!nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR()->_hoops_GHIAA &&
						dc->_hoops_APHHP == null) {
						HD_Free_Frame_Buffer_Info (nr, nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR());
						nr->_hoops_SAIR->_hoops_ASSIR->_hoops_HSCGP(null);
					}
				}

				++_hoops_ISPPP->stage;
			}	_hoops_HHHI;

			case _hoops_APSIP: {
				if (dc->_hoops_PPSIP != null)
					HD_Process_Deferred_Octrees(dc);
			}	break;
		}

		dc->_hoops_HRHPP[_hoops_SRHPP].list = _hoops_ISPPP->next;
		_hoops_ISPPP->_hoops_APHGA.release();
		_hoops_ISPPP->path.release();
		FREE (_hoops_ISPPP, _hoops_HSPPP);
	}

	if (dc->_hoops_IHIIP[0]) {
		_hoops_PICIP(dc);
	}

	// _hoops_IRHH _hoops_RCRR _hoops_HPSIP _hoops_HRGR _hoops_HRPP _hoops_IH _hoops_CCAH _hoops_CIPH _hoops_SPHR
	dc->_hoops_HRHPP[_hoops_SRHPP]._hoops_ASRGR = &dc->_hoops_HRHPP[_hoops_SRHPP].list;

	// _hoops_PHIH _hoops_PIAP (_hoops_PGRS _hoops_AIAH _hoops_SSAS _hoops_ICRP _hoops_IIGR _hoops_SCH)
	dc->path = null;
	dc->_hoops_CPGPR = _hoops_IPHIP;
}


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
 * $Id: obf_tmp.txt 1.133 2010-10-06 19:16:07 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"


/*
 * _hoops_GHGHR _hoops_RH _hoops_CAGH _hoops_HHIS _hoops_IS _hoops_CRGH _hoops_RH _hoops_AARPR'_hoops_GRI _hoops_CPGGR _hoops_PPR _hoops_HAHH
 * _hoops_IGSIP. _hoops_PGGGR _hoops_PAAP _hoops_RH _hoops_AIRI _hoops_GPP _hoops_GRR _hoops_AGRP.
 *
 * _hoops_RCGGS _hoops_CGH _hoops_AASA _hoops_RGR _hoops_HPGR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_HCR _hoops_PAII _hoops_ARSCA, _hoops_PAR _hoops_SSIA
 * _hoops_CGH _hoops_PRPP _hoops_PAII _hoops_IPHR _hoops_CCA _hoops_ACGGS _hoops_PPR _hoops_PCGGS.
 */

#define _hoops_RAAHR	  0.0001f /* _hoops_IRASR _hoops_IIGR _hoops_IRS _hoops_RPPS _hoops_SGS _hoops_PAH _hoops_SHH _hoops_ACAAA */


/* (_hoops_HAIC'_hoops_RA _hoops_SAHR _hoops_SGH _hoops_GPHIP _hoops_PGGA _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_HCGGS _hoops_IRS _hoops_APIP _hoops_CPSRR.
 *	_hoops_HAIC'_hoops_RA _hoops_SGH _hoops_GCRRH _hoops_PGGA _hoops_SCH _hoops_SAGGR _hoops_IHPPP _hoops_PSAP _hoops_CGPR _hoops_IIH'_hoops_GRI
 *	_hoops_PSP _hoops_RIHRR _hoops_IGSIP. _hoops_PHGP _hoops_PCSA _hoops_RH _hoops_APHR _hoops_PIAP _hoops_IH _hoops_ICGGS'_hoops_GRI.)
 */
#define _hoops_CCGGS		(_hoops_APPGP|\
								 _hoops_ICHPA|\
								 _hoops_PPPGP|\
								 _hoops_HPPGP|\
								 _hoops_CPPGP)


local void _hoops_SCGGS (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_SIHIR *					_hoops_CISIR,
	Activity					which,
	_hoops_PACIR const *	scope) {
	_hoops_CRCP *					_hoops_SRCP;
	_hoops_CRCP						_hoops_IIAPH;

	if (_hoops_CISIR->type == _hoops_IRCP)
		_hoops_SRCP = (_hoops_CRCP *)_hoops_CISIR;
	else if (_hoops_AHRIR <= _hoops_CISIR->type &&
							   _hoops_CISIR->type <= _hoops_PHRIR)
		_hoops_SRCP = _hoops_CISIR->owner;
	else
		return;

	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_AASIR)) {
		Geometry		*geometry;

		if ((geometry = _hoops_SRCP->geometry) == null) {
			_hoops_SRCP->_hoops_PHSI &= ~_hoops_AASIR;
			goto _hoops_GSGGS;
		}
		_hoops_RGGA (BIT (geometry->_hoops_RRHH, _hoops_PASIR)) {
			if ((geometry = geometry->next) == null) {
				_hoops_SRCP->_hoops_PHSI &= ~_hoops_AASIR;
				goto _hoops_GSGGS;
			}
		}

		_hoops_RGGA (!BIT (geometry->_hoops_CPGPR, _hoops_CASIR)) {
			if ((geometry = geometry->next) == null)
				goto _hoops_GSGGS;
		}

		do geometry->_hoops_CPGPR |= _hoops_ICHPA;
		while ((geometry = geometry->next) != null);
	}

	/* _hoops_GACC _hoops_HPGGR _hoops_HCR _hoops_GGSR-_hoops_IIGR-_hoops_AGR _hoops_CPAP _hoops_HHASA'_hoops_GRI _hoops_GIAA "_hoops_PHHIP" */
	_hoops_GSGGS:;
	if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GGPSA)) {

		if (_hoops_SRCP->_hoops_RGRPR == null) {
			_hoops_SRCP->_hoops_PHSI &= ~_hoops_GGPSA;
			return;
		}

		ZERO_STRUCT(&_hoops_IIAPH, _hoops_CRCP);
		_hoops_IIAPH.type = _hoops_IRCP;
		_hoops_IIAPH.next = _hoops_SRCP->_hoops_RGRPR;

		HI_Redraw_Downstream (_hoops_RIGC, (_hoops_SIHIR *)&_hoops_IIAPH, which, scope);
	}
}

typedef void (*_hoops_RSGGS)
				(_hoops_CRCP const * _hoops_SRCP, Activity _hoops_ASGGS, Activity _hoops_PSGGS);

local void _hoops_HSGGS (
	_hoops_CRCP const *	_hoops_SRCP,
	Activity			_hoops_ASGGS,
	Activity			_hoops_PSGGS) {
	Attribute const *_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR;

	if (_hoops_PSGGS == _hoops_ASGGS)
		return;

	do {
		if (_hoops_HPHCR->type >= HK_CALLBACK) {
			if (_hoops_HPHCR->type == HK_CALLBACK) {
				_hoops_IHACR alter	*_hoops_RCACR = ((_hoops_GCHIR *)_hoops_HPHCR)->_hoops_ACHIR;

				if (_hoops_RCACR != null) do {
					if (_hoops_RCACR->type == _hoops_GPACR) {
						_hoops_RSGGS	action;
						
						action = (_hoops_RSGGS)	_hoops_RCACR->name->address;
						(*action) (_hoops_SRCP, _hoops_ASGGS, _hoops_PSGGS);
						break;
					}
				} while ((_hoops_RCACR = _hoops_RCACR->next) != null);
			}
			return;
		}
	} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);
}

#if 0
local bool _hoops_ISGGS (
	_hoops_SIHIR const *	_hoops_CISIR) {
	_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)_hoops_CISIR;

	while (_hoops_SRCP != null && _hoops_SRCP->type != _hoops_IRCP)
		_hoops_SRCP = _hoops_SRCP->owner;
	while (_hoops_SRCP != null && _hoops_SRCP->type == _hoops_IRCP && !BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR)) {
		if (_hoops_SRCP->_hoops_SGRPR() != null)
			return true;
		_hoops_SRCP = _hoops_SRCP->owner;
	}
	return false;
}
#endif

local void _hoops_CSGGS (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_SIHIR *					_hoops_CISIR,
	Activity					which,
	_hoops_PACIR const *	_hoops_SSGGS,
	bool						_hoops_GGRGS) {
	_hoops_PACIR			scope;
	Activity					_hoops_RGRGS;
	_hoops_SIHIR *					_hoops_AGRGS;
#if 0
	bool						_hoops_SACRP = false;
#endif

	/* _hoops_CIPH _hoops_GHCA _hoops_SHH _hoops_GII _hoops_CPAP _hoops_PAR _hoops_HHASA _hoops_GRPAA _hoops_RRRPR _hoops_HRGR _hoops_IRS _hoops_CAGH */

	if (_hoops_CISIR == null)
		return;

#if 0
	/* _hoops_CIS _hoops_HHSH _hoops_SHR _hoops_RHAP _hoops_RGR, _hoops_HIH _hoops_IIS'_hoops_GRI _hoops_IHHH _hoops_HAH... */
	if ((_hoops_CISIR->type != _hoops_IRCP || BIT (((_hoops_CRCP const *)_hoops_CISIR)->_hoops_PHSI, _hoops_HCGPR)) &&
		ALLBITS (_hoops_CISIR->_hoops_CPGPR, which) &&
		((_hoops_SACRP = _hoops_ISGGS(_hoops_CISIR)) == false) &&
		(BIT (_hoops_CISIR->_hoops_CPGPR, _hoops_AASCA) ||
		 !BIT (which, _hoops_IPPGP)))
		return;
#endif

	/* _hoops_PRSCA _hoops_IS _hoops_ARI */
	_hoops_RGRGS = _hoops_CISIR->_hoops_CPGPR;
	_hoops_CISIR->_hoops_CPGPR |= which & ~_hoops_SHPGP;


	if (_hoops_CISIR->type == _hoops_IRCP) {
		_hoops_CRCP *		_hoops_SRCP = (_hoops_CRCP *)_hoops_CISIR;

		if (BIT(_hoops_SRCP->_hoops_PHSI, _hoops_AGPSA))
			return;
		
		if (BIT(which, _hoops_SHPGP))
			_hoops_SRCP->_hoops_PHSI |= _hoops_ICGPR;
		else
			_hoops_SRCP->_hoops_PHSI |= _hoops_HCGPR;

		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_ICHGP))
			_hoops_HSGGS (_hoops_SRCP, _hoops_RGRGS, _hoops_SRCP->_hoops_CPGPR);
	}

	/* _hoops_GHCA _hoops_SHH _hoops_CPHR _hoops_AIAH (_hoops_IIGSH _hoops_AGIR) */
	if (_hoops_CISIR == (_hoops_SIHIR *)HOOPS_WORLD->root) {
		if (BIT (which, _hoops_IPPGP)) HOOPS_WORLD->_hoops_RAAPH = true;
		return;
	}

	/* _hoops_PSSSR _hoops_IH _hoops_PCHII _hoops_GAGAI */
	if (_hoops_CISIR->owner == null)
		return;

	/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_PGRGS/_hoops_HGRGS/_hoops_AHI */
	/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_HPHR _hoops_PCPIP _hoops_HCCPR _hoops_IGRGS */
	if (!BIT (which, _hoops_RHPGP))
		which &= ~(_hoops_ICHPA|
				   _hoops_APPGP|
				   _hoops_PPPGP|
				   _hoops_CASIR|_hoops_AHSGA);
	else
		which &= ~(_hoops_CASIR|_hoops_AHSGA);

	if (BIT (which, _hoops_PHPGP)) {
		which &= ~_hoops_PHPGP;
		if (!BIT (_hoops_RGRGS, _hoops_PHPGP) &&
			!BIT (_hoops_CISIR->_hoops_CPGPR, _hoops_ICHPA))
			_hoops_SCGGS (_hoops_RIGC, _hoops_CISIR, which, _hoops_SSGGS);
	}

	/* _hoops_PSP _hoops_AIIAP _hoops_CGRGS _hoops_HCCPR _hoops_PCCP _hoops_RRRPR _hoops_HRGR _hoops_CPSA _hoops_SIGC _hoops_GPP _hoops_HHH _hoops_SISS */
	_hoops_AGRGS = _hoops_CISIR;
	if (BIT (which, _hoops_IPPGP)) {
		_hoops_CRCP				*_hoops_SRCP = _hoops_CISIR->owner;

		if (!BIT(_hoops_SRCP->_hoops_PHSI, _hoops_AGPSA)) {

			HOOPS_WORLD->_hoops_RAAPH = true;

			while (_hoops_SRCP != HOOPS_WORLD->root) {
				/* _hoops_RPP _hoops_RHAC _hoops_HGPSH _hoops_AGGAR _hoops_ACSRR _hoops_PGCR _hoops_IRSP _hoops_IIGR _hoops_AGAH, _hoops_RHAC _hoops_GRS _hoops_PAHH
				   _hoops_SCCHH _hoops_RPHR _hoops_ARI.  _hoops_SGRGS, _hoops_RPP _hoops_RHAC _hoops_SCCHH _hoops_ARI, _hoops_IRHH _hoops_RCRR _hoops_RHAC _hoops_GA'_hoops_RA _hoops_HS _hoops_PGCR
				   _hoops_PCIAR _hoops_IIGR _hoops_AGAH _hoops_GGR _hoops_GGGPR _hoops_RIPHR.  */
				if (_hoops_SRCP->type == _hoops_IRCP && /* <--- _hoops_IRHH _hoops_RCRR _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_PCCP _hoops_IHASA */
					(BIT (_hoops_SRCP->_hoops_PHSI, _hoops_HIHGP) || _hoops_SRCP->_hoops_SGRPR() != null))
					_hoops_AGRGS = (_hoops_SIHIR *)_hoops_SRCP;
				_hoops_SRCP = _hoops_SRCP->owner;

				if (_hoops_SRCP == null)
					return;		/* _hoops_AAAHH _hoops_HHIS */
			}
		}
	}

	/* _hoops_PRSCA _hoops_GRRGS _hoops_PPR _hoops_AGCPR _hoops_HA - _hoops_GA'_hoops_RA _hoops_ISPR _hoops_IH _hoops_HGAI-_hoops_RGAR */

	scope = *_hoops_SSGGS;

	while (_hoops_CISIR->type != _hoops_IRCP) {
		/* _hoops_RPP _hoops_HAR _hoops_IRS _hoops_CAGH, _hoops_IPHR _hoops_GH _hoops_RH _hoops_HHIS _hoops_HIS _hoops_SR *_hoops_AA* _hoops_PPSR _hoops_HPGR _hoops_IRS _hoops_CAGH. */

#if 0
		/* _hoops_RPP _hoops_RRRGS, _hoops_AIIAP _hoops_ICGGS. _hoops_AIIHR _hoops_RPGP, _hoops_PSCR _hoops_HIAC _hoops_RPGP. */
		if (_hoops_GGRGS && !_hoops_SACRP) {
			if (_hoops_CISIR->type == _hoops_AGRPR) {
				if (BIT (_hoops_CISIR->owner->_hoops_PHSI, _hoops_GGPSA))
					HI_Redraw_Downstream (_hoops_RIGC, _hoops_CISIR, which & ~_hoops_SHPGP, &scope);
			}
			else {
				if (BIT (_hoops_CISIR->owner->_hoops_PHSI, _hoops_AASIR))
					HI_Redraw_Downstream (_hoops_RIGC, _hoops_CISIR, which & ~_hoops_SHPGP, &scope);
			}
		}
#endif

		_hoops_CISIR = (_hoops_SIHIR *)_hoops_CISIR->owner;

#if 0
		/* _hoops_HGCR _hoops_GGSR _hoops_RPP _hoops_PSP _hoops_CCAH _hoops_SIH _hoops_PAR _hoops_CCAH _hoops_CPSRR */
		_hoops_SACRP = false;
		if ((_hoops_CISIR->type != _hoops_IRCP || BIT (((_hoops_CRCP const *)_hoops_CISIR)->_hoops_PHSI, _hoops_HCGPR)) &&
			ALLBITS (_hoops_CISIR->_hoops_CPGPR, which) &&
			((_hoops_SACRP = _hoops_ISGGS(_hoops_CISIR)) == false) &&
			(BIT (_hoops_CISIR->_hoops_CPGPR, _hoops_AASCA) ||
			 !BIT (which, _hoops_IPPGP)))
			return;
#endif

		_hoops_RGRGS = _hoops_CISIR->_hoops_CPGPR;
		_hoops_CISIR->_hoops_CPGPR |= which & ~_hoops_SHPGP;

		if (_hoops_CISIR->type == _hoops_IRCP) {
			_hoops_CRCP *		_hoops_SRCP = (_hoops_CRCP *)_hoops_CISIR;

			if (BIT(_hoops_SRCP->_hoops_PHSI, _hoops_AGPSA))
				return;

			if (BIT(which, _hoops_SHPGP))
				_hoops_SRCP->_hoops_PHSI |= _hoops_ICGPR;
			else
				_hoops_SRCP->_hoops_PHSI |= _hoops_HCGPR;

			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_ICHGP))
				_hoops_HSGGS (_hoops_SRCP, _hoops_RGRGS, _hoops_SRCP->_hoops_CPGPR);
		}

		/* _hoops_GHCA _hoops_SHH _hoops_CPHR _hoops_AIAH (_hoops_IIGSH _hoops_AGIR -- _hoops_CPAP _hoops_GGR "/") */
		if (_hoops_CISIR == (_hoops_SIHIR *)HOOPS_WORLD->root) {
			if (BIT (which, _hoops_IPPGP))
				HOOPS_WORLD->_hoops_RAAPH = true;
			return;
		}
	}

	/* _hoops_SPR _hoops_CAGH _hoops_SSCP _hoops_HA _hoops_RPII _hoops_PPSPR, _hoops_HIS _hoops_AGSGR _hoops_PSAP "_hoops_ARRGS" _hoops_IGRH(_hoops_GRI) */
	which &= ~(_hoops_SPPGP|_hoops_RSCCA);

	do {
		if (BIT (_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR))
			return;

		_hoops_CRCP *		_hoops_SRCP = (_hoops_CRCP *)_hoops_CISIR;

		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_PACAA) &&
			_hoops_SRCP->_hoops_PAGSA() == 0)
			which &= ~(_hoops_HISSR|_hoops_PSCCA|_hoops_HSCCA);

		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIPSA)) 
			which &= ~_hoops_SSCCA;

		if (ANYBIT (_hoops_SRCP->_hoops_PHSI,
					_hoops_HIHGP |
					_hoops_SHSIR |
					_hoops_GIGSA) ||
			BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RIGSA) &&
			BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR)) {

			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_ARRPR))
				return;

			if (ANYBIT (_hoops_SRCP->_hoops_PHSI,
						_hoops_SHSIR|_hoops_HIHGP)) {
				/* _hoops_GRH _hoops_AGIR: _hoops_HSSPR _hoops_PSIPR _hoops_RPPS */
				if (ALLBITS (_hoops_SRCP->_hoops_PHSI,
							 _hoops_SHSIR|_hoops_GCHGP)) {
					which = _hoops_AHGPR;
					_hoops_GGRGS = false;
				}

				if (BIT (which, _hoops_GHPGP) || _hoops_GGRGS) {
					Window				*window;

					/* _hoops_SSS _hoops_RH _hoops_RPPS */
					window = HI_Find_Scoping_Window ((_hoops_CRCP *)_hoops_CISIR);

					if (BIT (which, _hoops_GHPGP) &&
						!BIT (which, _hoops_RIPGP) &&
						!BIT (_hoops_CISIR->_hoops_CPGPR, _hoops_AASCA)) {
						/* _hoops_GGARP _hoops_PAR _hoops_CIPAA _hoops_RGR _hoops_RPPS'_hoops_GRI _hoops_AIIAP _hoops_CPSRR */

#if 0
						if (BIT (_hoops_RGRGS, _hoops_GHPGP)) {
							/* _hoops_IIH _hoops_AIAH _hoops_CSAP _hoops_IRS _hoops_CPSRR; _hoops_CACH _hoops_RPP _hoops_ISCP _hoops_CCAH _hoops_CPSRR
							 * _hoops_HRGR _hoops_AGIRH _hoops_GIHRR _hoops_GGR _hoops_SCH.
							 */
							if (ALLBITS (_hoops_RGRGS, which) &&
								scope.left - window->_hoops_ISGPR.left > -_hoops_RAAHR &&
								scope.right - window->_hoops_ISGPR.right < _hoops_RAAHR &&
								scope.bottom - window->_hoops_ISGPR.bottom > -_hoops_RAAHR &&
								scope.top - window->_hoops_ISGPR.top < _hoops_RAAHR)
								return; /* _hoops_AIAH _hoops_HCR _hoops_SIH _hoops_PPR _hoops_SHSC _hoops_CPSRR */

							window->_hoops_ISGPR._hoops_PGPGP(scope);
						}
#endif

						if (scope._hoops_HPCIR(_hoops_SGPGP::_hoops_GRPGP, _hoops_RAAHR)) {
							Activity		_hoops_SPGPR = _hoops_CISIR->_hoops_CPGPR;

							_hoops_CISIR->_hoops_CPGPR |= _hoops_AASCA;
							if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_ICHGP))
								_hoops_HSGGS ((_hoops_CRCP *)_hoops_CISIR, _hoops_SPGPR, _hoops_CISIR->_hoops_CPGPR);
						}
						else {

							/* _hoops_GGARP _hoops_RH _hoops_CPSRR */
							window->_hoops_ISGPR = window->_hoops_ISGPR._hoops_AACIR(scope);

							/* _hoops_HPGGR _hoops_SCH _hoops_IH _hoops_ACHHH */
							if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
								window->_hoops_CPGPR |= _hoops_AHSGA;
							}
							else { /* _hoops_SCH'_hoops_GRI _hoops_CPSA _hoops_IRS _hoops_RHPP _hoops_IGRI */
								Attribute	*_hoops_HPHCR;
								_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR;
								while (_hoops_HPHCR->type != HK_DRIVER)
									_hoops_HPHCR = _hoops_HPHCR->next;
								_hoops_HPHCR->_hoops_CPGPR |= _hoops_AHSGA;
							}
						}
					}

					/* _hoops_SICR _hoops_ISCP _hoops_CPSRR _hoops_IS _hoops_RH _hoops_RRRPR'_hoops_GRI _hoops_CSHCR */
					scope._hoops_HGPGP(window->_hoops_RCHS);

					/* _hoops_PAAP _hoops_RH _hoops_IHIR-_hoops_CPSRR _hoops_RIP */
					if (BIT (which, _hoops_AASCA) &&
						!scope._hoops_HPCIR(_hoops_SGPGP::_hoops_GRPGP, _hoops_RAAHR))
						which &= ~_hoops_AASCA;
				}
			}

			/* _hoops_GIGHR: _hoops_RPP _hoops_RPPS _hoops_HRGR _hoops_RRH, _hoops_RGR _hoops_CGH _hoops_ASAI _hoops_AGSGR _hoops_PSAP
			** _hoops_GAR _hoops_AHPH _hoops_CPGGR _hoops_SGI */

			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) ||
				(ANYBIT (_hoops_SRCP->_hoops_PHSI,
						 _hoops_GIGSA|_hoops_RIGSA) &&
				 _hoops_SRCP->_hoops_AAGSA() == 0 &&
				 _hoops_SRCP->_hoops_PAGSA() == 0)) {

				if (ANYBIT (_hoops_SRCP->_hoops_PHSI,_hoops_GIGSA|_hoops_RIGSA) ||
					!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP)) {
					which &= ~(_hoops_APPGP|
							   _hoops_ICHPA|
							   _hoops_PPPGP|
							   _hoops_CPPGP|
							   _hoops_HPPGP|
							   _hoops_RHPGP|
							   _hoops_SIGPR|
							   _hoops_IHPGP|
							   _hoops_GIPGP);

					if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SCHGP))
						which |= _hoops_RIPGP;  /* _hoops_GCAPR _hoops_SGS _hoops_SR'_hoops_ASAR _hoops_HII _hoops_IRS _hoops_HHCI _hoops_RIPPR _hoops_CAGH */
					else
					    which &= ~_hoops_GHPGP; /* _hoops_CIGC _hoops_SPHGR _hoops_RRS _hoops_CPSRR _hoops_PRRGS */
				}
				else if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_RCHGP) &&
						 !BIT (which, _hoops_RHPGP))
					/* (_hoops_ASSS _hoops_HRRGS _hoops_PPR _hoops_RH _hoops_IRRGS _hoops_SGI
					 *	_hoops_IS _hoops_SAS _hoops_CRRGS _hoops_GH, _hoops_HIH _hoops_HPGR _hoops_PHPA _hoops_HARH _hoops_SRCH
					 *	_hoops_RH _hoops_IHIR _hoops_PSSPR-_hoops_RPPS _hoops_IGSIP _hoops_SGS _hoops_SRRGS
					 *	_hoops_HGIIC.)
					 */
					which &= ~_hoops_HPPGP;

				which &= ~(_hoops_ISCCA|
						   _hoops_HISSR|_hoops_PSCCA|_hoops_HSCCA|
						   _hoops_IISSR|
						   _hoops_PISSR|
						   _hoops_RPSIR|
						   _hoops_AASCA);

				if (ANYBIT (_hoops_SRCP->_hoops_PHSI,_hoops_GIGSA|_hoops_RIGSA)) {
					which |= _hoops_SHPGP;
				}

			}

			if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_GIGSA))
				_hoops_GGRGS = false;
		}

		if (BIT (which, _hoops_PSCCA))
			which |= _hoops_HISSR;

		which &= ~_hoops_PIPGP;	// _hoops_RGR _hoops_GARGS _hoops_HAR _hoops_RRP _hoops_IS _hoops_PHHR _hoops_GH

		/* _hoops_PRSCA _hoops_RARGS _hoops_IS _hoops_AARGS */

		if (BIT (which, _hoops_IPPGP)) {

			_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_SRCP);

			if (_hoops_APAPA != null) {

				_hoops_RCCCA				_hoops_PARGS = _hoops_CISIR->_hoops_RRHH;

				// _hoops_HARGS: _hoops_CAHAR _hoops_SR _hoops_CHR _hoops_PGHPR, _hoops_HIS _hoops_SR _hoops_PAH'_hoops_RA _hoops_GCAS
				// _hoops_RARI _hoops_RGR _hoops_CAGH (_hoops_SHCAR, _hoops_AISIR _hoops_CAGH _hoops_PGPAA _hoops_HPP _hoops_RGCI _hoops_PCIRA)

				_hoops_CISIR->_hoops_RRHH |= _hoops_HGAGR;

				_hoops_RPAPA::UniqueCursor *	uc = _hoops_APAPA->GetUniqueCursor();
				_hoops_PHIP const *	_hoops_RRA;
				while((_hoops_RRA = uc->Peek()) != null) {
					if (!ALLBITS(_hoops_RRA->_hoops_CPGPR, which)) {
						_hoops_CSGGS (_hoops_RIGC, (_hoops_SIHIR *)_hoops_RRA, which & ~_hoops_SHPGP, &scope, _hoops_GGRGS);
					}
					uc->Advance();
				}
				delete uc;

				_hoops_CISIR->_hoops_RRHH = _hoops_PARGS;

			}

			if ((_hoops_SRCP->_hoops_SGRPR() != null)) {
				
				_hoops_RCCCA				_hoops_PARGS = _hoops_CISIR->_hoops_RRHH;

				// _hoops_HARGS: _hoops_CAHAR _hoops_SR _hoops_CHR _hoops_PGHPR, _hoops_HIS _hoops_SR _hoops_PAH'_hoops_RA _hoops_GCAS
				// _hoops_RARI _hoops_RGR _hoops_CAGH (_hoops_SHCAR, _hoops_AISIR _hoops_CAGH _hoops_PGPAA _hoops_HPP _hoops_RGCI _hoops_PCIRA)

				_hoops_CISIR->_hoops_RRHH |= _hoops_HGAGR;

				Xref const *				_hoops_AHICA;
				if ((_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR()) != null) do {
					if (!BIT (_hoops_AHICA->_hoops_RRHH, _hoops_HGAGR) &&
						_hoops_AHICA->type == _hoops_AGRPR &&
						!ALLBITS(_hoops_AHICA->_hoops_CPGPR, which) &&
						!BIT(_hoops_AHICA->owner->_hoops_RRHH,_hoops_HIRIR)) {
						_hoops_CSGGS (_hoops_RIGC, (_hoops_SIHIR *)_hoops_AHICA, which, &scope, _hoops_GGRGS);
					}
				} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

				_hoops_CISIR->_hoops_RRHH = _hoops_PARGS;
			}
		}

		if (_hoops_CISIR == _hoops_AGRGS) {
			/* _hoops_HAR _hoops_SIPSH _hoops_GPP _hoops_RPGHH _hoops_CPRIR - _hoops_RGAR _hoops_GPIHR
			 * _hoops_GGR _hoops_IARGS _hoops_HA. (_hoops_PCH _hoops_GPP _hoops_GGR '_hoops_PGAP' !)
			 */
			if (BIT (_hoops_RGRGS, _hoops_AHGPR))
				return;
			which = _hoops_AHGPR;
			_hoops_GGRGS = false;
		}

		/* _hoops_CPHR _hoops_CCA '_hoops_CIPH' _hoops_ACAS - _hoops_IHSH _hoops_AARI _hoops_GGR _hoops_RH _hoops_HRCCP */

#if 1
		/* _hoops_RPP _hoops_RRRGS, _hoops_AIIAP _hoops_ICGGS. _hoops_AIIHR _hoops_RPGP, _hoops_PSCR _hoops_HIAC _hoops_RPGP. */
		if (_hoops_GGRGS  && ANYBIT (_hoops_CISIR->owner->_hoops_PHSI, _hoops_GGPSA)/*&& !_hoops_PPGP*/)
			HI_Redraw_Downstream (_hoops_RIGC, _hoops_CISIR, which & ~_hoops_SHPGP, &scope);
#endif

		_hoops_CISIR = (_hoops_SIHIR *)_hoops_CISIR->owner;

		if (_hoops_CISIR->type != _hoops_IRCP)	/* _hoops_RSPHR _hoops_SARR _hoops_RGGAR */
			break;

		_hoops_SRCP = (_hoops_CRCP *)_hoops_CISIR;

#if 0
		/* _hoops_HGCR _hoops_GGSR _hoops_RPP _hoops_PSP _hoops_CCAH _hoops_SIH _hoops_PAR _hoops_CCAH _hoops_CPSRR */
		_hoops_SACRP = false;
		if ((_hoops_CISIR->type != _hoops_IRCP || BIT (((_hoops_CRCP const *)_hoops_CISIR)->_hoops_PHSI, _hoops_HCGPR)) &&
			ALLBITS (_hoops_CISIR->_hoops_CPGPR, which) &&
			((_hoops_SACRP = _hoops_ISGGS(_hoops_CISIR)) == false) &&
			(BIT (_hoops_CISIR->_hoops_CPGPR, _hoops_AASCA) ||
			 !BIT (which, _hoops_IPPGP)))
			return;
#endif

		_hoops_RGRGS = _hoops_CISIR->_hoops_CPGPR;
		_hoops_CISIR->_hoops_CPGPR |= which & ~_hoops_SHPGP;
	
		if (BIT(which, _hoops_SHPGP))
			_hoops_SRCP->_hoops_PHSI |= _hoops_ICGPR;
		else
			_hoops_SRCP->_hoops_PHSI |= _hoops_HCGPR;

		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_ICHGP))
			_hoops_HSGGS (_hoops_SRCP, _hoops_RGRGS, _hoops_SRCP->_hoops_CPGPR);
	} while (_hoops_CISIR != (_hoops_SIHIR *)HOOPS_WORLD->root);
}


GLOBAL_FUNCTION void HI_Propagate_Activity (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_SIHIR *				_hoops_CISIR,
	Activity				which) {

	if (BIT (_hoops_RSPPR(_hoops_RIGC, flags), _hoops_GRSCA) ||
		BIT (_hoops_RIGC->flags, _hoops_RRSCA))
		return;

	_hoops_CSGGS (_hoops_RIGC, _hoops_CISIR, which, &_hoops_SGPGP::_hoops_GRPGP, ANYBIT (which, _hoops_CCGGS));
}


GLOBAL_FUNCTION void HI_Propagate_Scoped_Activity (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_SIHIR *					_hoops_CISIR,
	Activity					which,
	_hoops_PACIR const *	scope) {

	if (BIT (_hoops_RSPPR(_hoops_RIGC, flags), _hoops_GRSCA) ||
		BIT (_hoops_RIGC->flags, _hoops_RRSCA))
		return;

	_hoops_PACIR	_hoops_CARGS = *scope;
	_hoops_CARGS._hoops_PGPGP(_hoops_SGPGP::_hoops_GRPGP);

	if (_hoops_CARGS.top - _hoops_CARGS.bottom > _hoops_RAAHR &&
		_hoops_CARGS.right - _hoops_CARGS.left > _hoops_RAAHR) {

		if (_hoops_CARGS._hoops_HPCIR(_hoops_SGPGP::_hoops_GRPGP, _hoops_RAAHR))
			_hoops_CSGGS (_hoops_RIGC, _hoops_CISIR, which, &_hoops_CARGS,
									   ANYBIT (which, _hoops_CCGGS));
		else
			_hoops_CSGGS (_hoops_RIGC, _hoops_CISIR, which & ~_hoops_AASCA,
									   &_hoops_CARGS, ANYBIT (which, _hoops_CCGGS));
	}
}


GLOBAL_FUNCTION void HI_Redraw_Downstream (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_SIHIR *					_hoops_CISIR,
	Activity					which,
	_hoops_PACIR const *	scope) {

	if (BIT (_hoops_RSPPR(_hoops_RIGC, flags), _hoops_GRSCA) ||
		BIT (_hoops_RIGC->flags, _hoops_RRSCA))
		return;

	if (_hoops_CISIR->type >= _hoops_AHRIR && _hoops_CISIR->type <= _hoops_PHRIR) {
		/* "_hoops_CIPH" _hoops_HRGR _hoops_GGR _hoops_RH _hoops_CPAP _hoops_HIGR */

		/* _hoops_HAPR _hoops_GH _hoops_IS _hoops_SRS _hoops_GGSR _hoops_IIGR _hoops_AGR */
		do if ((_hoops_CISIR = _hoops_CISIR->next) == null)
			return;
		_hoops_RGGA (BIT (_hoops_CISIR->_hoops_RRHH, _hoops_PASIR) &&
			   !BIT (_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR));

		which |= _hoops_ICHPA;

		/* _hoops_HPGGR _hoops_CPS */
		do {
			_hoops_CISIR->_hoops_CPGPR |= which & ~_hoops_SHPGP;
		} while ((_hoops_CISIR = _hoops_CISIR->next) != null);

		/* _hoops_SGS'_hoops_GRI _hoops_SCH */
	}
	else {

		/* "_hoops_CIPH" _hoops_HRGR _hoops_IRS _hoops_PSHHP */

		/* _hoops_RPP _hoops_RH _hoops_GIGR _hoops_CSAP _hoops_IRS _hoops_RPPS, _hoops_PSCR _hoops_SR _hoops_SAHR _hoops_RRP _hoops_IS _hoops_AIIAP
		 * _hoops_RH _hoops_ICGGS _hoops_SPHGR.
		 */

		/* _hoops_RPP _hoops_RH _hoops_GIGR _hoops_CSAP _hoops_HAR _hoops_IRS _hoops_RPPS, _hoops_PSCR _hoops_SR _hoops_RRP _hoops_IS _hoops_AIIAP _hoops_RH
		 * _hoops_ICGGS _hoops_GRAA-_hoops_SPHGR.
		 */

		_hoops_CRCP *	_hoops_SRCP = _hoops_SSIGP ((Subsegment *)_hoops_CISIR);

		if (!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
			/* _hoops_AIIAP _hoops_ICGGS _hoops_GRAA-_hoops_SPHGR */

			/* (_hoops_SR _hoops_GARIR _hoops_GPP _hoops_SARGS _hoops_IS _hoops_HIGSC _hoops_GPRGS
			 *	_hoops_GGR _hoops_ISCP _hoops_RRRPR _hoops_PPR _hoops_HHSA _hoops_HCR _hoops_RH _hoops_HGHIP _hoops_IS _hoops_SHH _hoops_SIGSA.)
			 */

			/* _hoops_HAPR _hoops_GH _hoops_IS _hoops_SRS _hoops_GGSR _hoops_IIGR _hoops_AGR */
			do if ((_hoops_CISIR = _hoops_CISIR->next) == null)
				return;

			while (!BIT (_hoops_CISIR->_hoops_RRHH, _hoops_PASIR) || BIT (_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR))
				; // _hoops_AA _hoops_ISAP

			which |= _hoops_ICHPA|_hoops_APPGP|
					 _hoops_PPPGP;

			do if (!BIT (_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR) && !ALLBITS (_hoops_CISIR->_hoops_CPGPR, which & ~_hoops_SHPGP)) {

				if (_hoops_CISIR->type == _hoops_AGRPR) {
					_hoops_PGRPR *	inc = (_hoops_PGRPR *)_hoops_CISIR;

					if (!BIT (((_hoops_CRCP *)inc->_hoops_IGRPR)->_hoops_PHSI, _hoops_SHSIR))
						inc->_hoops_CPGPR |= which & ~_hoops_SHPGP;
				}
				else {
					_hoops_CRCP *	_hoops_RPRGS = (_hoops_CRCP *)_hoops_CISIR;

					if (!BIT (_hoops_RPRGS->_hoops_PHSI, _hoops_SHSIR)) {
#if 0
						_hoops_CSGGS (_hoops_RIGC, (_hoops_SIHIR *)_hoops_CISIR, which, scope, true);
						break;
#else
						_hoops_RPRGS->_hoops_CPGPR |= which & ~_hoops_SHPGP;

						// _hoops_RPP _hoops_SR _hoops_SARIC _hoops_GPP _hoops_RH _hoops_CAGH, _hoops_GIPR _hoops_RGR _hoops_PAPA _hoops_PPR _hoops_RH _hoops_PAGIR _hoops_PAPA _hoops_CHH _hoops_RSGR _hoops_GH _hoops_HCHAR _hoops_HPGR ->_hoops_SPS
						// _hoops_PPR ->_hoops_RRRPR. _hoops_RCPA _hoops_SRCH _hoops_SGS, _hoops_SAHR _hoops_GHHA _hoops_GPP _hoops_RH _hoops_AARGS _hoops_IIGR _hoops_RGR _hoops_CAGH, _hoops_RPP _hoops_GII.

						_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_SRCP);

						if (_hoops_APAPA != null) {
							
							_hoops_RCCCA				_hoops_PARGS;

							_hoops_PARGS = _hoops_CISIR->_hoops_RRHH;

							// _hoops_HARGS: _hoops_CAHAR _hoops_SR _hoops_CHR _hoops_PGHPR, _hoops_HIS _hoops_SR _hoops_PAH'_hoops_RA _hoops_GCAS
							// _hoops_RARI _hoops_RGR _hoops_CAGH (_hoops_SHCAR, _hoops_AISIR _hoops_CAGH _hoops_PGPAA _hoops_HPP _hoops_RGCI _hoops_PCIRA)
							
							_hoops_CISIR->_hoops_RRHH |= _hoops_HGAGR;

							_hoops_RPAPA::UniqueCursor *	uc = _hoops_APAPA->GetUniqueCursor();

							_hoops_PHIP const *	_hoops_RRA;

							while((_hoops_RRA = uc->Peek()) != null) {
								_hoops_CSGGS (_hoops_RIGC, (_hoops_SIHIR *)_hoops_RRA, which & ~_hoops_SHPGP, scope, true);
								uc->Advance();
							}

							delete uc;

							_hoops_CISIR->_hoops_RRHH = _hoops_PARGS;
						}

						if (_hoops_RPRGS->_hoops_SGRPR() != null) {

							Xref const *				_hoops_AHICA;
							_hoops_RCCCA				_hoops_PARGS;

							_hoops_PARGS = _hoops_CISIR->_hoops_RRHH;

							// _hoops_HARGS: _hoops_CAHAR _hoops_SR _hoops_CHR _hoops_PGHPR, _hoops_HIS _hoops_SR _hoops_PAH'_hoops_RA _hoops_GCAS
							// _hoops_RARI _hoops_RGR _hoops_CAGH (_hoops_SHCAR, _hoops_AISIR _hoops_CAGH _hoops_PGPAA _hoops_HPP _hoops_RGCI _hoops_PCIRA)

							_hoops_CISIR->_hoops_RRHH |= _hoops_HGAGR;

							if ((_hoops_AHICA = _hoops_RPRGS->_hoops_SGRPR()) != null) do {
								if (!BIT (_hoops_AHICA->_hoops_RRHH, _hoops_HGAGR) &&
									_hoops_AHICA->type == _hoops_AGRPR) {
									_hoops_CSGGS (_hoops_RIGC, (_hoops_SIHIR *)_hoops_AHICA, which, scope, true);
								}
							} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

							_hoops_CISIR->_hoops_RRHH = _hoops_PARGS;
						}
#endif
					}
				}
			} while ((_hoops_CISIR = _hoops_CISIR->next) != null);
		}
		else {
			/* _hoops_AIIAP _hoops_ICGGS _hoops_SPHGR */

			/* _hoops_HAPR _hoops_GH _hoops_IS _hoops_SRS _hoops_GGSR _hoops_IIGR _hoops_AGR _hoops_HAR _hoops_HAHH - _hoops_SPHGR
			 * _hoops_CHR _hoops_SHR _hoops_GGSR _hoops_IIGR _hoops_AGR.
			 */

			if ((_hoops_CISIR = _hoops_CISIR->next) == null)
				return;

			do if (!BIT (_hoops_CISIR->_hoops_RRHH, _hoops_HGAGR)) {
				_hoops_SRCP = _hoops_SSIGP ((Subsegment *)_hoops_CISIR);

				if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR)) {
					if (!(ALLBITS (_hoops_CISIR->_hoops_CPGPR, _hoops_RCGSA) ||
						  ALLBITS (_hoops_SRCP->_hoops_CPGPR, _hoops_RCGSA))) {

						Window * window = HI_Find_Scoping_Window (_hoops_SRCP);

						_hoops_PACIR	_hoops_RSPSA = _hoops_PGPGP(*scope, window->_hoops_RCHS);

						if (_hoops_RSPSA.right - _hoops_RSPSA.left >= _hoops_RAAHR &&
							_hoops_RSPSA.top - _hoops_RSPSA.bottom >= _hoops_RAAHR) {
							/* _hoops_HIHP _hoops_SGSSR _hoops_CPSRR _hoops_CRGR _hoops_IRGH _hoops_PCRR */

							_hoops_RSPSA._hoops_CGPGP(window->_hoops_RCHS);

							if (_hoops_CISIR->type == _hoops_AGRPR) {

								_hoops_PACIR	_hoops_APRGS;

								_hoops_APRGS.left = _hoops_RSPSA.left;
								_hoops_APRGS.right = _hoops_RSPSA.right;
								_hoops_APRGS.bottom = _hoops_RSPSA.bottom;
								_hoops_APRGS.top = _hoops_RSPSA.top;

								if (BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_GHPGP))
									window->_hoops_ISGPR._hoops_PGPGP(_hoops_APRGS);

								_hoops_CISIR->_hoops_CPGPR |= _hoops_RCGSA;
								if (_hoops_APRGS._hoops_HPCIR(_hoops_SGPGP::_hoops_GRPGP, _hoops_RAAHR)) {
									/* _hoops_CPSA _hoops_HRGR _hoops_CPIC _hoops_IS _hoops_SHH _hoops_IHIR _hoops_CPSRR _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA
									 * _hoops_RRP _hoops_IS _hoops_ARHSA _hoops_RH _hoops_CAGH _hoops_ACAS.
									 */
								}
								else {
									/* _hoops_IASI _hoops_CPSRR; _hoops_PIHA _hoops_PAAP _hoops_RH _hoops_CAGH */

									/* _hoops_ISCP _hoops_GPAPA'_hoops_GRI _hoops_SCGR _hoops_SGI _hoops_CGH _hoops_GRHP _hoops_RH
									 * _hoops_SPS _hoops_III _hoops_HII _hoops_CRRGS _hoops_RPHR _hoops_ISSC _hoops_IS _hoops_SCH.
									 */
									_hoops_CSGGS (_hoops_RIGC, 
													(_hoops_SIHIR *)_hoops_SRCP,
													_hoops_RCGSA &
													~_hoops_AASCA,
													&_hoops_RSPSA, true);

									/*_hoops_AGSGR _hoops_RH _hoops_IGRH _hoops_ISSC _hoops_PSAP _hoops_RPP _hoops_SR _hoops_AAPR _hoops_PPRGS*/
									if (!BIT (_hoops_SRCP->_hoops_CPGPR,
											  _hoops_AASCA))
										_hoops_CISIR->_hoops_CPGPR &= ~_hoops_AASCA;
								}
							}
							else {
								Activity		_hoops_HPRGS;

								/* _hoops_RIGRP _hoops_IRS _hoops_ICGGS _hoops_CAGH: _hoops_HHGC _hoops_IS _hoops_AA
								 * _hoops_CPS (_hoops_ACAS, _hoops_HCSHC, _hoops_ICGGS)
								 * _hoops_AHSAR _hoops_RGCI _hoops_RRRPR.
								 */

								/* _hoops_IPRGS _hoops_RH _hoops_RRRPR'_hoops_GRI _hoops_SGI _hoops_IS _hoops_IRHH _hoops_PRSCA
								 * _hoops_ASRC _hoops_RSIH.
								 */
								_hoops_HPRGS = _hoops_CISIR->owner->_hoops_CPGPR;
								_hoops_CISIR->owner->_hoops_CPGPR = _hoops_RCGSA;

								if (_hoops_RSPSA._hoops_HPCIR(_hoops_SGPGP::_hoops_GRPGP, _hoops_RAAHR))
									_hoops_CSGGS (_hoops_RIGC, _hoops_CISIR,
												_hoops_RCGSA,
												&_hoops_RSPSA, true);
								else
									_hoops_CSGGS (_hoops_RIGC, _hoops_CISIR,
												_hoops_RCGSA &
												~_hoops_AASCA,
												&_hoops_RSPSA, true);

								_hoops_CISIR->owner->_hoops_CPGPR = _hoops_HPRGS;
							}
						}
					}
				}
				else if (BIT (_hoops_SRCP->_hoops_RCGC, T_WINDOWS))
					HI_Propagate_Scoped_Activity (_hoops_RIGC, _hoops_CISIR, which |  _hoops_SCCCA, scope);
			} while ((_hoops_CISIR = _hoops_CISIR->next) != null);
		}
	}
}


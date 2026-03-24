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
 * $Id: obf_tmp.txt 1.80 2010-10-29 21:25:34 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"


GLOBAL_FUNCTION void HI_Gather_Modelling (
	Attribute	*_hoops_ASGPR,
	Attribute	**_hoops_PSACR) {

	if (_hoops_ASGPR != null) do {
		if (_hoops_ASGPR->type > _hoops_IAAA (HK_STYLE, HK_MODELLING_MATRIX))
			break;

#ifndef DISABLE_STYLE_SEGMENT
		if (_hoops_ASGPR->type == HK_STYLE) {
			Style *		style = (Style *)_hoops_ASGPR;

			if (style->_hoops_IGRPR && style->_hoops_IGRPR->_hoops_IPPGR)
				HI_Gather_Modelling (style->_hoops_IGRPR->_hoops_IPPGR, _hoops_PSACR);
		}
		else
#endif
		if (_hoops_ASGPR->type == HK_MODELLING_MATRIX) {
			_hoops_ISGI *		_hoops_SSSPH = (_hoops_ISGI *)_hoops_ASGPR;
			_hoops_ISGI *		_hoops_CPAI;

			if ((_hoops_CPAI = (_hoops_ISGI *)*_hoops_PSACR) == null) {
				ZALLOC (_hoops_CPAI, _hoops_ISGI);
				_hoops_CPAI->type = HK_MODELLING_MATRIX;
				_hoops_CPAI->_hoops_HIHI = 1;
				*_hoops_PSACR = (Attribute *)_hoops_CPAI;
				HI_Copy_Matrix (&_hoops_SSSPH->matrix, &_hoops_CPAI->matrix);
			}
			else {
				_hoops_HRPA					_hoops_RHSPR;

				HI_Copy_Matrix (&_hoops_CPAI->matrix, &_hoops_RHSPR);
				HI_Multiply_Matrices (&_hoops_SSSPH->matrix, &_hoops_RHSPR, &_hoops_CPAI->matrix);
			}
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
}


/* _hoops_CPRGS _hoops_IH _hoops_RH _hoops_SARA _hoops_IGRI, _hoops_PPR _hoops_CACH _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_SPRS-_hoops_SPRGS.
 * _hoops_CGP _hoops_SCH _hoops_HRGR, _hoops_SR _hoops_RRP _hoops_IS _hoops_ARHCP _hoops_RH _hoops_SPS _hoops_PAAP _hoops_IS _hoops_IRS _hoops_IHIR _hoops_AIIAP. */
local void _hoops_GHRGS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	Bounding const &		_hoops_RHRGS) {
	Attribute const *		_hoops_HPHCR = (Attribute const *) _hoops_SRCP->_hoops_IPPGR;
	_hoops_HHRA const *			_hoops_ISPCR = null;
	int						_hoops_CPGPR = _hoops_AISSR | _hoops_RPSIR;
	bool					_hoops_AHRGS;
	short					_hoops_CICHH = 0;

	if (!BIT (HOOPS_WORLD->system_flags, _hoops_HGSPP))
		return;

	if (_hoops_RHRGS != null)
		_hoops_CICHH = _hoops_RHRGS->flags;

	_hoops_AHRGS = ANYBIT (_hoops_SRCP->bounding->flags & ~_hoops_CICHH,
								_hoops_IGCIR|Bounding_TRANSFORM_DEPENDENT|_hoops_HGCIR);

	if (!_hoops_AHRGS) {
		if (_hoops_HPHCR) do {
			if (_hoops_HPHCR->type == HK_CAMERA) {
				_hoops_ISPCR = (_hoops_HHRA const *)_hoops_HPHCR;
				break;
			}
		} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

		if (_hoops_ISPCR == null || *_hoops_ISPCR->_hoops_SIPCR > 0)
			return;
	}

	if (_hoops_AHRGS)
		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_CPGPR);
	else {
		_hoops_SPAGR				_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);
		_hoops_AHAGR *		_hoops_CSC = _hoops_SRCP->_hoops_CSC;

		if (_hoops_CSC != null) do {
			_hoops_HRPA const *			_hoops_HSGA = _hoops_CSC->_hoops_ARSGP();

			if (_hoops_HSGA != null) {
				float					_hoops_RPSC, _hoops_CGSAA;
				float					_hoops_PHRGS, _hoops_HHRGS;

				if (!HI_Compute_Camera_Min_Max (_hoops_HSGA, _hoops_ISPCR, _hoops_SRCP, _hoops_RHRGS, &_hoops_RPSC, &_hoops_CGSAA))
					continue;
				if (!HI_Compute_Camera_Min_Max (_hoops_HSGA, _hoops_ISPCR, _hoops_SRCP, null, &_hoops_PHRGS, &_hoops_HHRGS))
					continue;

				if (_hoops_ISPCR->projection == _hoops_GHH) {
					if (_hoops_PHRGS < _hoops_RPSC && _hoops_RPSC > 0) {
						_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_CPGPR);
						break;
					}
				}
				else {
					if (_hoops_PHRGS < _hoops_RPSC || _hoops_HHRGS > _hoops_CGSAA) {
						_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_CPGPR);
						break;
					}
				}
			}
		} while ((_hoops_CSC = _hoops_CSC->next) != null);
	}
}


GLOBAL_FUNCTION void HI_Propagate_Bounding (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP *				_hoops_SRCP,
	Bounding const &		bounding,
	_hoops_CRCP const *			_hoops_ACCIH) {
	Bounding				_hoops_SHCPH = bounding;

	if (bounding._hoops_HICAR())
		return;

	do {
		Bounding				_hoops_IHRGS;
		Xref *					_hoops_AHICA;

		if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_HCHGP))
			_hoops_IHRGS = _hoops_SRCP->bounding;

		if (_hoops_ACCIH != null &&
			_hoops_ACCIH->_hoops_IPPGR != null) {
			Attribute			*_hoops_PSACR = null;

			HI_Gather_Modelling (_hoops_ACCIH->_hoops_IPPGR, &_hoops_PSACR);

			if (_hoops_PSACR != null) {
				_hoops_SHCPH = _hoops_SHCPH._hoops_SCIS (&((_hoops_ISGI *)_hoops_PSACR)->matrix.elements[0][0]);
				_hoops_HPRH (_hoops_PSACR);
			}
		}

		if (BIT (_hoops_SRCP->_hoops_RRHH, _hoops_GGSCA)) {
			if (_hoops_SRCP->bounding == null || !BIT (_hoops_SRCP->bounding->flags, _hoops_CCIIR)) {
				if (_hoops_SRCP->bounding._hoops_HICAR())
					_hoops_SRCP->bounding = null;

				if (_hoops_SRCP->bounding == null) {
					_hoops_SRCP->bounding = _hoops_SHCPH;
				}
				else if (_hoops_SHCPH != _hoops_SRCP->bounding) {
					/* _hoops_GSSR _hoops_HASC */
					if (!_hoops_SRCP->bounding.Merge (_hoops_SHCPH))
						return;
				}
				if (BIT (_hoops_SRCP->bounding->flags, _hoops_CCIIR)) {
					_hoops_SRCP->bounding.Modify();
					_hoops_SRCP->bounding->flags &= ~_hoops_CCIIR;
				}
			}

			if (BIT (_hoops_SRCP->_hoops_PHSI, _hoops_HCHGP)) {
				if (!HI_Compare_Bounding (_hoops_SRCP->bounding, _hoops_IHRGS))
					_hoops_GHRGS (_hoops_RIGC, _hoops_SRCP, _hoops_IHRGS);

				_hoops_IHRGS = null;
			}

			//_hoops_HACH = _hoops_PHHIP->_hoops_IASC;
		}
		else
			_hoops_SRCP->bounding = null;

		/* _hoops_RRS _hoops_HPGR _hoops_RPPS _hoops_PAPA */
		if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_HCHGP))
			return;
		/* _hoops_RRS _hoops_HPGR _hoops_HHCI-_hoops_IHCI */
		if (ANYBIT (_hoops_SRCP->_hoops_PHSI,_hoops_GIGSA|_hoops_RIGSA))
			return;

		// _hoops_CHH _hoops_PII _hoops_IS _hoops_RRS _hoops_RPP _hoops_RGR _hoops_CAGH _hoops_HRGR _hoops_AGIA _hoops_IS _hoops_SHH _hoops_CHRGS, _hoops_HIH _hoops_SHRGS _hoops_HRGR _hoops_ARP _hoops_IH
		// _hoops_GIRGS _hoops_ARAR, _hoops_HPGP _hoops_ASCA _hoops_IRHS _hoops_IS _hoops_CPSA _hoops_ACPA _hoops_RH _hoops_PRCH _hoops_IH _hoops_RIRGS _hoops_CIAAI
#if 1
		if (HI_Bounding_Is_Excluded(_hoops_SRCP->_hoops_IPPGR))
			return;
#endif

		/*
		 * _hoops_AIRGS _hoops_IS _hoops_HCSHC _hoops_PPR _hoops_RRRPR
		 */
		if ((_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR()) != null) do {
			if (_hoops_AHICA->type == _hoops_AGRPR)
				HI_Propagate_Bounding (_hoops_RIGC, _hoops_AHICA->owner, _hoops_SHCPH, _hoops_SRCP);
		} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

		_hoops_ACCIH = _hoops_SRCP;
		_hoops_SRCP = _hoops_SRCP->owner;
	} while (_hoops_SRCP != null && _hoops_SRCP->type == _hoops_IRCP);
}

GLOBAL_FUNCTION void HI_Antiquate_Bounding (
	_hoops_CRCP *			_hoops_SRCP,
	bool				_hoops_PCCIH,
	bool				_hoops_HCCIH) {

	if (_hoops_SRCP->bounding._hoops_HICAR())
		return;

	if (_hoops_SRCP->_hoops_HSRIR != null)
		_hoops_SRCP->_hoops_HSRIR.Modify()->flags |= _hoops_AAPGP;

	do {
		Xref *					_hoops_AHICA;

		if (_hoops_SRCP->bounding._hoops_HICAR() ||
			BIT (_hoops_SRCP->bounding->flags, _hoops_AAPGP))
			return;

		if (BIT (_hoops_SRCP->_hoops_RRHH, _hoops_GGSCA)) {
			if (_hoops_PCCIH && !BIT (_hoops_SRCP->bounding->flags, _hoops_CCIIR))
				_hoops_SRCP->bounding.Modify()->flags |= _hoops_AAPGP;
		}

		// _hoops_RRS _hoops_HPGR _hoops_RPPS _hoops_PAPA
		if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_HCHGP)) break;

		// _hoops_AIRGS _hoops_IS _hoops_HCSHC _hoops_PPR _hoops_RRRPR
		_hoops_PCCIH = true;
		if ((_hoops_AHICA = _hoops_SRCP->_hoops_SGRPR()) != null) do {
			if (_hoops_AHICA->type == _hoops_AGRPR && _hoops_AHICA->owner != null)
				HI_Antiquate_Bounding (_hoops_AHICA->owner, _hoops_PCCIH, false);
		} while ((_hoops_AHICA = _hoops_AHICA->_hoops_GRRPR) != null);

		_hoops_SRCP = _hoops_SRCP->owner;
		_hoops_HCCIH = false;
	} while (_hoops_SRCP != null && _hoops_SRCP->type == _hoops_IRCP);
}

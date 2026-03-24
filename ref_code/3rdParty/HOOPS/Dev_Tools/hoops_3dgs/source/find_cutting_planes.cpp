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
 * $Id: obf_tmp.txt 1.91 2010-07-02 21:35:17 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

local void _hoops_GIIPH (
	Geometry const *geometry) {

	HE_WARNING (HEC_CUTTING_PLANE, HES_SINGULAR_PLANE,
				Sprintf_P (null, "A cutting plane in '%p' became singular after transforming", geometry->owner));
}


local _hoops_CRSPA _hoops_RIIPH (
	_hoops_HRPA const *				matrix,
	Display_Context const *			dc) {

	if (matrix->_hoops_APRA == null)
		matrix->_hoops_APRA = _hoops_CRSPA::Create (dc->memory_pool);

	if (ANYBIT (matrix->_hoops_RAGR, _hoops_CICH))
		HI_Adjoint_44 (&matrix->elements[0][0], &matrix->_hoops_APRA->data.elements[0][0]);

	return matrix->_hoops_APRA;
}


local void _hoops_AIIPH (
	Attribute const *			_hoops_ASGPR,
	_hoops_HRPA const * alter *	_hoops_PIIPH,
	_hoops_HRPA alter *			_hoops_HIIPH,
	_hoops_ACHR alter *			_hoops_IIIPH,
	_hoops_HHAGP alter *		_hoops_CIIPH,
	_hoops_ACHR alter *			_hoops_SIIPH,
	bool alter *				_hoops_GCIPH) {
	Attribute const *			_hoops_SIIAA = _hoops_ASGPR;
	_hoops_HHAGP				_hoops_RCIPH, _hoops_ACIPH;
	_hoops_ACHR					_hoops_PCIPH, _hoops_HCIPH;

	/* _hoops_HSPP _hoops_CCA _hoops_SGHS _hoops_GCIAA _hoops_HII _hoops_ARRS */
	_hoops_RCIPH = *_hoops_CIIPH;
	_hoops_PCIPH = *_hoops_SIIPH;
	_hoops_ACIPH = (_hoops_HHAGP)false;
	_hoops_HCIPH = (_hoops_ACHR)false;

	/* _hoops_ISPR _hoops_IH _hoops_GGRRA _hoops_SRS */
	do {
		if (_hoops_ASGPR->type > HK_RENDERING_OPTIONS)
			break;

		if (_hoops_ASGPR->type == HK_RENDERING_OPTIONS) {
			_hoops_RHAIR const	*	_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_ASGPR;

			if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA)) {
				if (BIT (_hoops_AHAIR->_hoops_RSIAA, _hoops_GSIAA)) {
					/* _hoops_SSIAA _hoops_GII _hoops_AIRC _hoops_HSGRA _hoops_ARI */
					/* _hoops_PPR _hoops_PRIA _hoops_GII _hoops_SHPH */
					_hoops_ACIPH = _hoops_AHAIR->locks->normal.mask._hoops_IPPGR;
					_hoops_RCIPH &= ~_hoops_ACIPH;
					*_hoops_CIIPH &= ~_hoops_ACIPH;
					*_hoops_CIIPH |= _hoops_ACIPH &
									_hoops_AHAIR->locks->normal.value._hoops_IPPGR;

					/* _hoops_HPRC _hoops_ARAH-_hoops_SGHS */
					if (BIT (_hoops_AHAIR->locks->normal.mask._hoops_IPPGR, _hoops_GGCAA(HK_VISIBILITY))) {
						if (BIT (_hoops_AHAIR->locks->normal.value._hoops_IPPGR, _hoops_GGCAA(HK_VISIBILITY))) {
							_hoops_HCIPH = _hoops_AHAIR->locks->normal.mask._hoops_RGP;
							_hoops_PCIPH &= ~_hoops_HCIPH;
							*_hoops_SIIPH &= ~_hoops_HCIPH;
							*_hoops_SIIPH |= _hoops_HCIPH &
											_hoops_AHAIR->locks->normal.value._hoops_RGP;
						}
						else {
							*_hoops_SIIPH = 0;
							_hoops_PCIPH = 0;
							_hoops_HCIPH = ~0;
						}
					}
				}
				else {
					/* _hoops_SSIAA _hoops_CPS */
					*_hoops_CIIPH = _hoops_RCIPH = 0;
					*_hoops_SIIPH = _hoops_PCIPH = 0;
					_hoops_ACIPH = (_hoops_HHAGP)~0;
					_hoops_HCIPH = ~0;
				}
			}

			break;
		}
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);

	_hoops_ASGPR = _hoops_SIIAA;

	do switch (_hoops_ASGPR->type) {
		case HK_VISIBILITY: if (!BIT(_hoops_RCIPH, 1L<<HK_VISIBILITY)) {
			_hoops_RSAIR const *		vis = (_hoops_RSAIR const *)_hoops_ASGPR;

			*_hoops_IIIPH &= ~vis->mask & ~_hoops_PCIPH;
			*_hoops_IIIPH |= vis->value & ~_hoops_PCIPH &
						 vis->mask;
		}	break;

		case HK_STYLE: if (!BIT(_hoops_RCIPH, 1L<<HK_STYLE)) {
#ifndef DISABLE_STYLE_SEGMENT
			Style const *		style = (Style const *)_hoops_ASGPR;

			if (style->_hoops_IGRPR && style->_hoops_IGRPR->_hoops_IPPGR) {
				_hoops_AIIPH (style->_hoops_IGRPR->_hoops_IPPGR,
											   _hoops_PIIPH, _hoops_HIIPH, _hoops_IIIPH,
											   _hoops_CIIPH, _hoops_SIIPH, _hoops_GCIPH);

				/* _hoops_IRHH _hoops_RCRR _hoops_SGHS _hoops_CHR _hoops_GH-_hoops_IS-_hoops_ICGIP */
				_hoops_RCIPH = *_hoops_CIIPH & ~_hoops_ACIPH;
				_hoops_PCIPH = *_hoops_SIIPH & ~_hoops_HCIPH;
			}
#endif
		}	break;

		case HK_RENDERING_OPTIONS: if (!BIT(_hoops_RCIPH, 1L<<HK_RENDERING_OPTIONS)) {
			_hoops_RHAIR const *	_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_ASGPR;

			if (BIT(_hoops_AHAIR->_hoops_PSHCA, _hoops_AARAP))
				*_hoops_GCIPH = BIT(_hoops_AHAIR->_hoops_RRRAP, _hoops_AARAP);
		}	break;

		case HK_MODELLING_MATRIX: if (!BIT(_hoops_RCIPH, 1L<<HK_MODELLING_MATRIX)) {
			_hoops_ISGI const *		matrix = (_hoops_ISGI const *)_hoops_ASGPR;

			if (*_hoops_PIIPH == null)
				HI_Copy_Matrix (&matrix->matrix, _hoops_HIIPH);
			else
				HI_Multiply_Matrices (&matrix->matrix, *_hoops_PIIPH, _hoops_HIIPH);

			*_hoops_PIIPH = _hoops_HIIPH;
		}	break;
	} while ((_hoops_ASGPR = _hoops_ASGPR->next) != null);
}

local void _hoops_ICIPH (
	Geometry const *				geometry,
	_hoops_IAPA alter * alter *_hoops_CCIPH,
	int alter *						count,
	_hoops_HRPA const *				_hoops_HSGA,
	Display_Context const *			dc) {
	_hoops_HHPIR const *			_hoops_RPPA = (_hoops_HHPIR const *)geometry;
	_hoops_IAPA alter *		_hoops_HRCAR;
	int								i;

	ALLOC (_hoops_HRCAR, _hoops_IAPA);
	_hoops_HRCAR->_hoops_IPASP = _hoops_RPPA->count;
	_hoops_HRCAR->_hoops_APPA = null;

	/* _hoops_RSRA _hoops_GHC _hoops_HPGR _hoops_RH _hoops_RIPS, _hoops_GPGR _hoops_RAS (_hoops_GASAR _hoops_SHCAH _hoops_HAR _hoops_SIGR) */
	if (_hoops_RPPA->count == 1 || *_hoops_CCIPH == null) {
		_hoops_HRCAR->next = *_hoops_CCIPH;
		*_hoops_CCIPH = _hoops_HRCAR;
	}
	else {
		_hoops_IAPA alter		*_hoops_SCIPH = *_hoops_CCIPH;

		while (_hoops_SCIPH->_hoops_IPASP == 1 && _hoops_SCIPH->next != null)
			_hoops_SCIPH = _hoops_SCIPH->next;

		_hoops_HRCAR->next = _hoops_SCIPH->next;
		_hoops_SCIPH->next = _hoops_HRCAR;
	}

	for (i=0; i<_hoops_RPPA->count; i++) {
		_hoops_GPPA alter		*_hoops_IRCAR;

		ALLOC (_hoops_IRCAR, _hoops_GPPA);
		_hoops_IRCAR->next = (_hoops_GPPA alter *)_hoops_HRCAR->_hoops_APPA;
		_hoops_HRCAR->_hoops_APPA = _hoops_IRCAR;
		_hoops_IRCAR->id = (*count)++;
		_hoops_IRCAR->internal = false;

		/* _hoops_HIHP _hoops_SGS _hoops_IPPA */
		/* "_hoops_IRSIR _hoops_HIHP _hoops_GAR _hoops_GPRRH . _hoops_HAICR" - _hoops_RPRRH & _hoops_APRRH */
		/* _hoops_RH _hoops_IAPGR-_hoops_GGSR _hoops_AIRP _hoops_CHR _hoops_HSSPR _hoops_IS _hoops_SHH _hoops_AHHR _hoops_GGR _hoops_IRS _hoops_IRISR 4x3 */

		if (!ANYBIT (_hoops_HSGA->_hoops_RAGR, _hoops_CICH)) {
			_hoops_IRCAR->_hoops_SHPA.a = _hoops_RPPA->planes[i].a;
			_hoops_IRCAR->_hoops_SHPA.b = _hoops_RPPA->planes[i].b;
			_hoops_IRCAR->_hoops_SHPA.c = _hoops_RPPA->planes[i].c;
			_hoops_IRCAR->_hoops_SHPA.d = _hoops_RPPA->planes[i].d;
		}
		else {
			_hoops_RPRA const *		_hoops_CRIPA = _hoops_RIIPH(_hoops_HSGA, dc)->data.elements;

			_hoops_IRCAR->_hoops_SHPA.a =
					   _hoops_CRIPA[0][0] * _hoops_RPPA->planes[i].a +
					   _hoops_CRIPA[0][1] * _hoops_RPPA->planes[i].b +
					   _hoops_CRIPA[0][2] * _hoops_RPPA->planes[i].c /* +
					   _hoops_PPRRH[0][3] * _hoops_GSIPH->_hoops_GHC[_hoops_HAS]._hoops_GHGP */;

			_hoops_IRCAR->_hoops_SHPA.b =
					   _hoops_CRIPA[1][0] * _hoops_RPPA->planes[i].a +
					   _hoops_CRIPA[1][1] * _hoops_RPPA->planes[i].b +
					   _hoops_CRIPA[1][2] * _hoops_RPPA->planes[i].c /* +
					   _hoops_PPRRH[1][3] * _hoops_GSIPH->_hoops_GHC[_hoops_HAS]._hoops_GHGP */;

			_hoops_IRCAR->_hoops_SHPA.c =
					   _hoops_CRIPA[2][0] * _hoops_RPPA->planes[i].a +
					   _hoops_CRIPA[2][1] * _hoops_RPPA->planes[i].b +
					   _hoops_CRIPA[2][2] * _hoops_RPPA->planes[i].c /* +
					   _hoops_PPRRH[2][3] * _hoops_GSIPH->_hoops_GHC[_hoops_HAS]._hoops_GHGP */;

			_hoops_IRCAR->_hoops_SHPA.d =
					   _hoops_CRIPA[3][0] * _hoops_RPPA->planes[i].a +
					   _hoops_CRIPA[3][1] * _hoops_RPPA->planes[i].b +
					   _hoops_CRIPA[3][2] * _hoops_RPPA->planes[i].c +
					   _hoops_CRIPA[3][3] * _hoops_RPPA->planes[i].d;
		}

		if (!HI_Normalize_Plane (&_hoops_IRCAR->_hoops_SHPA))
			_hoops_GIIPH (geometry);

		/* _hoops_AGGAH _hoops_SAPS-_hoops_PPSR _hoops_RSIPH _hoops_RPP _hoops_HRCC _hoops_PCIAR _hoops_AGCR... */
		_hoops_IRCAR->_hoops_SPPA.a = 0.0f;
		_hoops_IRCAR->_hoops_SPPA.b = 0.0f;
		_hoops_IRCAR->_hoops_SPPA.c = 0.0f;
		_hoops_IRCAR->_hoops_SPPA.d = 0.0f;
	}
	/* (_hoops_ASIPH _hoops_GRS _hoops_RARIR _hoops_RH _hoops_CSPH-_hoops_GHC) */
}

local void _hoops_PSIPH (
	Geometry const *				geometry,
	Display_Context const *			dc,
	_hoops_IAPA alter * alter *_hoops_CCIPH,
	int alter *						count,
	_hoops_HRPA const *				_hoops_HSGA,
	_hoops_HHAGP					_hoops_RCIPH,
	int								mask = ~0,
	bool							single = false) {

	if (geometry == null || !ANYBIT (mask, _hoops_AGPGR (_hoops_HGPGR)))
		return;

	do {
		if (geometry->type == _hoops_HGPGR) {
			if (((_hoops_HHPIR const *)geometry)->count > 0)
				_hoops_ICIPH (geometry, _hoops_CCIPH, count, _hoops_HSGA, dc);
		}
		else if (geometry->type == _hoops_AHIP) {
			_hoops_PHIP const *		_hoops_RRA = (_hoops_PHIP const *)geometry;
			_hoops_HRPA						_hoops_HIIPH;

			if (_hoops_RRA->_hoops_IPPGR != null) {
				_hoops_ACHR					_hoops_HSIPH = 0;			// _hoops_SPCS _hoops_CCPAR _hoops_IH _hoops_CGSI _hoops_SR _hoops_GA'_hoops_RA
				_hoops_ACHR					_hoops_PCIPH = 0;	// _hoops_ACRR _hoops_IS _hoops_SSS _hoops_HISS _hoops_SSPP
				bool						_hoops_ISIPH = 0;		// _hoops_GPP _hoops_IRS _hoops_HPPA _hoops_IPPA

				_hoops_AIIPH (_hoops_RRA->_hoops_IPPGR, &_hoops_HSGA, &_hoops_HIIPH, &_hoops_HSIPH,
											   &_hoops_RCIPH, &_hoops_PCIPH, &_hoops_ISIPH);
			}

			if (_hoops_RRA->_hoops_IHIP[0]->type == _hoops_IRCP) {
				_hoops_CRCP const *		_hoops_SRCP = (_hoops_CRCP const *)_hoops_RRA->_hoops_IHIP[0];

				_hoops_PSIPH (_hoops_SRCP->geometry, dc, _hoops_CCIPH, count, _hoops_HSGA, mask & _hoops_RRA->_hoops_RGPGR);
			}
			else {
				for (int i=0; i<_hoops_RRA->_hoops_HHIP; i++)
					_hoops_PSIPH ((Geometry const *)_hoops_RRA->_hoops_IHIP[i], dc, _hoops_CCIPH, count, _hoops_HSGA,
									  mask & _hoops_RRA->_hoops_RGPGR, true);
			}
		}

		if (single)
			break;
	} while ((geometry = geometry->next) != null);
}


local void _hoops_CSIPH (
	_hoops_CRCP const *						_hoops_SRCP,
	_hoops_IAPA alter * alter *	_hoops_CCIPH,
	int alter *							count,
	_hoops_HRPA const *					_hoops_HSGA,
	_hoops_ACHR							_hoops_HSIPH,
	_hoops_HHAGP						_hoops_RCIPH,
	_hoops_ACHR							_hoops_PCIPH,
	bool								_hoops_ISIPH,
	bool								_hoops_SSIPH,
	Display_Context const *				dc) {
	_hoops_HRPA							_hoops_HIIPH;

top:;

	if (_hoops_SRCP->_hoops_IPPGR != null && _hoops_SSIPH)
		_hoops_AIIPH (_hoops_SRCP->_hoops_IPPGR, &_hoops_HSGA, &_hoops_HIIPH,
									   &_hoops_HSIPH, &_hoops_RCIPH, &_hoops_PCIPH, &_hoops_ISIPH);


	if (_hoops_SRCP->geometry != null && BIT (_hoops_HSIPH, T_CUTTING_PLANES) && !_hoops_ISIPH)
		_hoops_PSIPH (_hoops_SRCP->geometry, dc, _hoops_CCIPH, count, _hoops_HSGA, _hoops_RCIPH);


	{	Subsegment const *				_hoops_GIPIA;

		if ((_hoops_GIPIA = _hoops_SRCP->_hoops_RGRPR) != null) do {
			_hoops_CRCP const *				_hoops_GGCPH = _hoops_SSIGP (_hoops_GIPIA);

			if (_hoops_GGCPH->_hoops_PAGSA() > 0 &&
				!BIT (_hoops_GGCPH->_hoops_PHSI, _hoops_SHSIR)) {
				if (1 || _hoops_GGCPH->next != null) {
					_hoops_CSIPH (_hoops_GGCPH, _hoops_CCIPH, count,
												_hoops_HSGA, _hoops_HSIPH,
												_hoops_RCIPH, _hoops_PCIPH,
												_hoops_ISIPH, true, dc);
				}
				else {
					_hoops_SRCP = _hoops_GGCPH;
					_hoops_SSIPH = true;
					goto top;
				}
			}
		} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);
	}
}

GLOBAL_FUNCTION void HD_Validate_Cutting_Plane_Sets (
	_hoops_SSP const &		_hoops_RGCPH) {
	_hoops_SSP alter &		_hoops_GGH = (_hoops_SSP alter &)_hoops_RGCPH;
	_hoops_IAPA const *			_hoops_AGCPH = _hoops_GGH->_hoops_ISIGA;

	HD_Free_Cutting_Plane_Sets (_hoops_GGH->_hoops_PHCA);
	HD_Free_Cutting_Plane_Sets (_hoops_GGH->_hoops_IRH);
	_hoops_GGH->_hoops_PHCA = null;
	_hoops_GGH->_hoops_IRH = null;
	_hoops_GGH->_hoops_PGH = 0;
	_hoops_GGH->_hoops_CRH = 0;

	if (_hoops_AGCPH != null) {
		_hoops_IAPA alter	*_hoops_HRCAR;

		ALLOC (_hoops_HRCAR, _hoops_IAPA);
		ZERO_STRUCT (_hoops_HRCAR, _hoops_IAPA);
		_hoops_GGH->_hoops_PHCA = _hoops_HRCAR;

		do {
			if (_hoops_AGCPH->_hoops_IPASP == 1) {
				/* _hoops_SAHR _hoops_GGCR _hoops_IS _hoops_RCSAR _hoops_APRS _hoops_ARP */
				_hoops_HRCAR = (_hoops_IAPA alter *)_hoops_GGH->_hoops_PHCA;

				do {
					_hoops_GPPA alter	*_hoops_IRCAR;

					ALLOC (_hoops_IRCAR, _hoops_GPPA);
					_hoops_RSAI (_hoops_AGCPH->_hoops_APPA, _hoops_GPPA, _hoops_IRCAR);
					_hoops_IRCAR->next = (_hoops_GPPA alter *)_hoops_HRCAR->_hoops_APPA;
					_hoops_HRCAR->_hoops_APPA = _hoops_IRCAR;
					++_hoops_HRCAR->_hoops_IPASP;
				} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);
			}
			else {
				/* _hoops_GRR _hoops_IPPA _hoops_SAGGR _hoops_RRAI _hoops_IS _hoops_IRS _hoops_GIAH _hoops_IPS _hoops_IIGR _hoops_RH _hoops_SCGR _hoops_ARH */
				_hoops_IAPA const		*_hoops_PGCPH;
				_hoops_IAPA alter		**_hoops_ASRGR;
				_hoops_GPPA const	*_hoops_HGCPH = _hoops_AGCPH->_hoops_APPA;

				_hoops_PGCPH = _hoops_GGH->_hoops_PHCA;
				_hoops_GGH->_hoops_PHCA = null;
				_hoops_ASRGR = (_hoops_IAPA alter **)&_hoops_GGH->_hoops_PHCA;

				do {
					if (_hoops_HGCPH->next != null)
						*_hoops_ASRGR = _hoops_HRCAR = HD_Copy_Cutting_Plane_Sets (_hoops_PGCPH);
					else
						*_hoops_ASRGR = _hoops_HRCAR = (_hoops_IAPA alter *)_hoops_PGCPH;

					do {
						_hoops_GPPA alter	*_hoops_IRCAR;

						ALLOC (_hoops_IRCAR, _hoops_GPPA);
						_hoops_RSAI (_hoops_HGCPH, _hoops_GPPA, _hoops_IRCAR);
						_hoops_IRCAR->next = (_hoops_GPPA alter *)_hoops_HRCAR->_hoops_APPA;
						_hoops_HRCAR->_hoops_APPA = _hoops_IRCAR;
						++_hoops_HRCAR->_hoops_IPASP;
						_hoops_ASRGR = &_hoops_HRCAR->next;
					} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);
				} while ((_hoops_HGCPH = _hoops_HGCPH->next) != null);
			}
		} while ((_hoops_AGCPH = _hoops_AGCPH->next) != null);

		_hoops_HRCAR = (_hoops_IAPA alter *)_hoops_GGH->_hoops_PHCA;
		do if (_hoops_HRCAR->_hoops_IPASP > _hoops_GGH->_hoops_PGH)
			_hoops_GGH->_hoops_PGH = _hoops_HRCAR->_hoops_IPASP;
		while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);
	}
}

GLOBAL_FUNCTION void HD_Validate_Transparent_Cutting_Sets (
	_hoops_SSP const &		_hoops_RGCPH) {
	_hoops_SSP alter &		_hoops_GGH = (_hoops_SSP alter &)_hoops_RGCPH;
	_hoops_IAPA const *			_hoops_AGCPH = _hoops_GGH->_hoops_ISIGA;

	/* _hoops_RGR _hoops_CGH _hoops_HCAGR _hoops_SHH _hoops_PIGS _hoops_RGAR _hoops_CGPR _hoops_AGCR _hoops_CHR _hoops_RHPA, _hoops_HIH _hoops_IRHH _hoops_RCRR... */
	HD_Free_Cutting_Plane_Sets (_hoops_GGH->_hoops_IRH);
	_hoops_GGH->_hoops_IRH = null;
	_hoops_GGH->_hoops_CRH = 0;

	if (_hoops_AGCPH != null) {
		_hoops_IAPA alter	*_hoops_HRCAR;

		ALLOC (_hoops_HRCAR, _hoops_IAPA);
		ZERO_STRUCT (_hoops_HRCAR, _hoops_IAPA);
		_hoops_GGH->_hoops_IRH = _hoops_HRCAR;

		do {
			if (_hoops_AGCPH->_hoops_IPASP == 1) {
				/* _hoops_SAHR _hoops_GGCR _hoops_IS _hoops_RCSAR _hoops_APRS _hoops_ARP */
				_hoops_HRCAR = (_hoops_IAPA alter *)_hoops_GGH->_hoops_IRH;

				do {
					_hoops_GPPA alter	*_hoops_IRCAR;

					ALLOC (_hoops_IRCAR, _hoops_GPPA);
					_hoops_RSAI (_hoops_AGCPH->_hoops_APPA, _hoops_GPPA, _hoops_IRCAR);
					_hoops_IRCAR->next = (_hoops_GPPA alter *)_hoops_HRCAR->_hoops_APPA;
					_hoops_HRCAR->_hoops_APPA = _hoops_IRCAR;
					++_hoops_HRCAR->_hoops_IPASP;
				} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);
			}
			else {
				/* _hoops_GRR _hoops_IPPA _hoops_SAGGR _hoops_RRAI _hoops_IS _hoops_IRS _hoops_GIAH _hoops_IPS _hoops_IIGR _hoops_RH _hoops_SCGR _hoops_ARH */
				_hoops_IAPA const		*_hoops_PGCPH;
				_hoops_IAPA alter		**_hoops_ASRGR;
				_hoops_GPPA const	*_hoops_HGCPH = _hoops_AGCPH->_hoops_APPA;

				_hoops_PGCPH = _hoops_GGH->_hoops_IRH;
				_hoops_GGH->_hoops_IRH = null;
				_hoops_ASRGR = (_hoops_IAPA alter **)&_hoops_GGH->_hoops_IRH;

				do {
					if (_hoops_HGCPH->next != null)
						*_hoops_ASRGR = _hoops_HRCAR = HD_Copy_Cutting_Plane_Sets (_hoops_PGCPH);
					else
						*_hoops_ASRGR = _hoops_HRCAR = (_hoops_IAPA alter *)_hoops_PGCPH;

					do {
						_hoops_GPPA alter	*_hoops_IRCAR;
						_hoops_GPPA const	*_hoops_IGCPH = _hoops_AGCPH->_hoops_APPA;

						ALLOC (_hoops_IRCAR, _hoops_GPPA);
						_hoops_RSAI (_hoops_HGCPH, _hoops_GPPA, _hoops_IRCAR);
						_hoops_IRCAR->next = (_hoops_GPPA alter *)_hoops_HRCAR->_hoops_APPA;
						_hoops_HRCAR->_hoops_APPA = _hoops_IRCAR;
						++_hoops_HRCAR->_hoops_IPASP;

						/* _hoops_ISGHR _hoops_RH _hoops_GSSR _hoops_AGIR, _hoops_HA _hoops_GGCR _hoops_IRS _hoops_PIIA _hoops_IPS _hoops_IIGR _hoops_RCSAR _hoops_CGCPH _hoops_IPPA _hoops_GGR _hoops_RGR _hoops_ARP */
						if (_hoops_IGCPH != _hoops_HGCPH) do {
							ALLOC (_hoops_IRCAR, _hoops_GPPA);
							_hoops_RSAI (_hoops_IGCPH, _hoops_GPPA, _hoops_IRCAR);
							_hoops_PPASP (_hoops_IRCAR);
							_hoops_IRCAR->next = (_hoops_GPPA alter *)_hoops_HRCAR->_hoops_APPA;
							_hoops_HRCAR->_hoops_APPA = _hoops_IRCAR;
							++_hoops_HRCAR->_hoops_IPASP;
						} while ((_hoops_IGCPH = _hoops_IGCPH->next) != _hoops_HGCPH);

						_hoops_ASRGR = &_hoops_HRCAR->next;
					} while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);
				} while ((_hoops_HGCPH = _hoops_HGCPH->next) != null);
			}
		} while ((_hoops_AGCPH = _hoops_AGCPH->next) != null);

		_hoops_HRCAR = (_hoops_IAPA alter *)_hoops_GGH->_hoops_IRH;
		do if (_hoops_HRCAR->_hoops_IPASP > _hoops_GGH->_hoops_CRH)
			_hoops_GGH->_hoops_CRH = _hoops_HRCAR->_hoops_IPASP;
		while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);
	}
}

local void _hoops_SGCPH (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HHCR alter &	_hoops_IHCR) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_IAPA alter *	_hoops_HRCAR = null;
	int							count = 0;

	_hoops_CSIPH (_hoops_SRCP,
								&_hoops_HRCAR, &count,
								&_hoops_IHCR->_hoops_IPH->data,
								nr->_hoops_RGP,
								nr->_hoops_IRR->locks._hoops_IPPGR,
								nr->_hoops_IRR->locks._hoops_RGP,
								BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_AARAP),
								false,
								nr->_hoops_SRA);

	if (_hoops_HRCAR != null) {
		_hoops_IHCR->_hoops_RGH = _hoops_SSP::Create(dc);
		_hoops_SSP alter	&_hoops_GGH = _hoops_IHCR->_hoops_RGH;

		_hoops_GGH->_hoops_ISIGA = _hoops_HRCAR;
		_hoops_GGH->_hoops_AHASP = count;
		HD_Validate_Cutting_Plane_Sets (_hoops_GGH);

		if (BIT (_hoops_IHCR->flags, _hoops_PRAIP)) {
			HD_Set_DC_Cutting_Planes (nr);
			_hoops_IHCR->flags |= _hoops_HHGGA;
		}
	}
}

/* _hoops_PAGA: _hoops_RGR _hoops_API _hoops_HA _hoops_GPHR _hoops_HRSAR _hoops_HPPA _hoops_GHC, _hoops_IRGH _hoops_ARIPR _hoops_CHR _hoops_GIR _hoops_PPGA */
GLOBAL_FUNCTION void HD_Find_Cutting_Planes (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP) {
	_hoops_HHCR alter &	_hoops_IHCR = nr->transform_rendition;	// _hoops_IGIPR _hoops_HIHP _hoops_HRGR _hoops_AIAH _hoops_SHIS

	if (_hoops_IHCR->_hoops_RGH != null) {
		_hoops_IHCR->_hoops_RGH = null;
		_hoops_IHCR->flags &= ~(_hoops_CSP|_hoops_HHGGA);
	}

	if (_hoops_SRCP->_hoops_PAGSA() > 0)
		_hoops_SGCPH (nr, _hoops_SRCP, _hoops_IHCR);
}

/* _hoops_ARI */
GLOBAL_FUNCTION void HD_Find_Local_Cutting_Planes (
	Net_Rendition alter &		nr,
	_hoops_CRCP const *				_hoops_SRCP) {
	_hoops_HHCR			_hoops_IHCR;
	Geometry const *			geometry = _hoops_SRCP->geometry;

	if (!BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_AARAP) ||
		!BIT(nr->_hoops_RGP, T_CUTTING_PLANES) ||
		_hoops_SRCP->_hoops_PAGSA() == 0 || geometry == null)
		return;


	do if (geometry->type == _hoops_HGPGR && ((_hoops_HHPIR const *)geometry)->count > 0) {
		_hoops_HHPIR const *				_hoops_RPPA = (_hoops_HHPIR const *)geometry;
		_hoops_IAPA alter *			_hoops_HRCAR;
		int									i;

		_hoops_IHCR = nr.Modify()->transform_rendition.Modify();

		if (_hoops_IHCR->_hoops_RGH == null)
			_hoops_IHCR->_hoops_RGH = _hoops_SSP::Create(nr->_hoops_SRA);

		_hoops_SSP alter &		_hoops_GGH = _hoops_IHCR->_hoops_RGH.Modify();

		ALLOC (_hoops_HRCAR, _hoops_IAPA);
		_hoops_HRCAR->_hoops_IPASP = _hoops_RPPA->count;
		_hoops_HRCAR->_hoops_APPA = null;

			/* _hoops_RSRA _hoops_GHC _hoops_HPGR _hoops_RH _hoops_RIPS, _hoops_GPGR _hoops_RAS (_hoops_GASAR _hoops_SHCAH _hoops_HAR _hoops_SIGR) */
		if (_hoops_RPPA->count == 1 || _hoops_GGH->_hoops_ISIGA == null) {
			_hoops_HRCAR->next = (_hoops_IAPA alter *)_hoops_GGH->_hoops_ISIGA;
			_hoops_GGH->_hoops_ISIGA = _hoops_HRCAR;
		}
		else {
			_hoops_IAPA alter *		_hoops_SCIPH = (_hoops_IAPA alter *)_hoops_GGH->_hoops_ISIGA;

			while (_hoops_SCIPH->_hoops_IPASP == 1 && _hoops_SCIPH->next != null)
				_hoops_SCIPH = _hoops_SCIPH->next;

			_hoops_HRCAR->next = _hoops_SCIPH->next;
			_hoops_SCIPH->next = _hoops_HRCAR;
		}

		for (i=0; i<_hoops_RPPA->count; i++) {
			_hoops_SGCC const &		_hoops_HSGA = _hoops_IHCR->_hoops_IPH;
			_hoops_GPPA alter *	_hoops_IRCAR;

			ALLOC (_hoops_IRCAR, _hoops_GPPA);
			_hoops_IRCAR->next = (_hoops_GPPA alter *)_hoops_HRCAR->_hoops_APPA;
			_hoops_HRCAR->_hoops_APPA = _hoops_IRCAR;
			_hoops_IRCAR->id = _hoops_GGH->_hoops_AHASP++;
			_hoops_IRCAR->internal = false;

			/* _hoops_HIHP _hoops_SGS _hoops_IPPA */
			/* "_hoops_IRSIR _hoops_HIHP _hoops_GAR _hoops_GPRRH . _hoops_HAICR" - _hoops_RPRRH & _hoops_APRRH */
			/* _hoops_RH _hoops_IAPGR-_hoops_GGSR _hoops_AIRP _hoops_CHR _hoops_HSSPR _hoops_IS _hoops_SHH _hoops_AHHR _hoops_GGR _hoops_IRS _hoops_IRISR 4x3 */

			if (!ANYBIT (_hoops_HSGA->data._hoops_RAGR, _hoops_CICH)) {
				_hoops_IRCAR->_hoops_SHPA.a = _hoops_RPPA->planes[i].a;
				_hoops_IRCAR->_hoops_SHPA.b = _hoops_RPPA->planes[i].b;
				_hoops_IRCAR->_hoops_SHPA.c = _hoops_RPPA->planes[i].c;
				_hoops_IRCAR->_hoops_SHPA.d = _hoops_RPPA->planes[i].d;
			}
			else {
				_hoops_RPRA const *		_hoops_CRIPA = _hoops_HSGA->_hoops_PPRA()->data.elements;

				_hoops_IRCAR->_hoops_SHPA.a =
						   _hoops_CRIPA[0][0] * _hoops_RPPA->planes[i].a +
						   _hoops_CRIPA[0][1] * _hoops_RPPA->planes[i].b +
						   _hoops_CRIPA[0][2] * _hoops_RPPA->planes[i].c /* +
						   _hoops_PPRRH[0][3] * _hoops_GSIPH->_hoops_GHC[_hoops_HAS]._hoops_GHGP */;

				_hoops_IRCAR->_hoops_SHPA.b =
						   _hoops_CRIPA[1][0] * _hoops_RPPA->planes[i].a +
						   _hoops_CRIPA[1][1] * _hoops_RPPA->planes[i].b +
						   _hoops_CRIPA[1][2] * _hoops_RPPA->planes[i].c /* +
						   _hoops_PPRRH[1][3] * _hoops_GSIPH->_hoops_GHC[_hoops_HAS]._hoops_GHGP */;

				_hoops_IRCAR->_hoops_SHPA.c =
						   _hoops_CRIPA[2][0] * _hoops_RPPA->planes[i].a +
						   _hoops_CRIPA[2][1] * _hoops_RPPA->planes[i].b +
						   _hoops_CRIPA[2][2] * _hoops_RPPA->planes[i].c /* +
						   _hoops_PPRRH[2][3] * _hoops_GSIPH->_hoops_GHC[_hoops_HAS]._hoops_GHGP */;

				_hoops_IRCAR->_hoops_SHPA.d =
						   _hoops_CRIPA[3][0] * _hoops_RPPA->planes[i].a +
						   _hoops_CRIPA[3][1] * _hoops_RPPA->planes[i].b +
						   _hoops_CRIPA[3][2] * _hoops_RPPA->planes[i].c +
						   _hoops_CRIPA[3][3] * _hoops_RPPA->planes[i].d;
			}

			if (!HI_Normalize_Plane (&_hoops_IRCAR->_hoops_SHPA))
				_hoops_GIIPH (geometry);

			/* _hoops_AGGAH _hoops_SAPS-_hoops_PPSR _hoops_RSIPH _hoops_RPP _hoops_HRCC _hoops_PCIAR _hoops_AGCR... */
			_hoops_IRCAR->_hoops_SPPA.a = 0.0f;
			_hoops_IRCAR->_hoops_SPPA.b = 0.0f;
			_hoops_IRCAR->_hoops_SPPA.c = 0.0f;
			_hoops_IRCAR->_hoops_SPPA.d = 0.0f;
		}

		/* (_hoops_ASIPH _hoops_GRS _hoops_RARIR _hoops_RH _hoops_CSPH-_hoops_GHC) */
	} while ((geometry = geometry->next) != null);

	if (_hoops_IHCR != null) {	/* _hoops_RRAI _hoops_HPGR _hoops_CHGC 1 */
		HD_Validate_Cutting_Plane_Sets (_hoops_IHCR->_hoops_RGH);

		if (BIT (_hoops_IHCR->flags, _hoops_PRAIP)) {
			HD_Set_DC_Cutting_Planes (nr);
			_hoops_IHCR->flags |= _hoops_HHGGA;
		}

		if (!BIT (nr->_hoops_RCSHR, _hoops_GPRIP)) {
			/* _hoops_PSP _hoops_HPPA _hoops_GHC _hoops_ARPP, _hoops_HIS _hoops_HGCR _hoops_GRCPH _hoops_HA */
			nr.Modify()->_hoops_RCSHR |= _hoops_GPRIP;
			_hoops_IHCR->flags |= _hoops_CSP;
		}
		else if (BIT (nr->current, _hoops_GPRIP) &&
				 BIT (_hoops_IHCR->flags, _hoops_RCRIP) &&
				 _hoops_IHCR->_hoops_RGH->_hoops_PGH >
						nr->_hoops_SRA->_hoops_PGCC._hoops_ACPGH) {
			/* _hoops_CCAH _hoops_GHC _hoops_CIPHA _hoops_GSIA _hoops_RRCPH, _hoops_HHSA _hoops_RHSHA _hoops_IS _hoops_RHHR _hoops_ICCGR */
			nr.Modify()->current &= ~_hoops_GPRIP;
		}
	}
}


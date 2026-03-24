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
 * $Id: obf_tmp.txt 1.66 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "phedron.h"
#include "adt.h"
#include "hpserror.h"


#ifndef DISABLE_LOD_GENERATION

/* _hoops_CRICR _hoops_IS _hoops_RH _hoops_PRCCA _hoops_CAPIA _hoops_GGR _hoops_CCGIP, _hoops_HIH _hoops_RGAR _hoops_PCPA _hoops_HRGR _hoops_ARGPR _hoops_IS
 * _hoops_RGAP (_hoops_HAS._hoops_IAS. _hoops_SIHH _hoops_RH _hoops_PGSA-_hoops_GHIR _hoops_SIGSP/_hoops_PHIRC _hoops_AHI...) */
struct _hoops_GRICA {
	_hoops_RRPHA			value;
	float				_hoops_PRPHA[_hoops_IGAIR]; /*  _hoops_PRAII, _hoops_CCAH/_hoops_RHGS	 _hoops_SHHH _hoops_SHH _hoops_IRS _hoops_PHI _hoops_CRGP _hoops_HSAR 1 */
	int					_hoops_HISRP;
	int					_hoops_IRSH;
	int					_hoops_RHPHA;
	float				tolerance;
	int					_hoops_ARPHA;
};


struct _hoops_ARRRS {
	_hoops_SGGGI *			list;					/* _hoops_GRPHR _hoops_IS _hoops_HASC */
	_hoops_AAPHP *		_hoops_GIPAC;
	struct _hoops_GRICA *	_hoops_PRRRS;
	float *					_hoops_HRRRS;

	/* _hoops_RH _hoops_HSPR _hoops_CHR _hoops_IGI _hoops_RGAR _hoops_RHSP _hoops_CAGH _hoops_HHIS _hoops_PRCCA _hoops_RGAP */
	int						_hoops_SCPI;
	Point *					_hoops_HCRGR;
};


local const _hoops_IGRCR _hoops_IRRRS[] = {
	{_hoops_CGSRP, _hoops_GRRCR ("segment"), _hoops_RRRCR, 0, false},
	{~_hoops_CGSRP, _hoops_GRRCR ("geometry"), _hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_CRRRS = {
	_hoops_GGAPR (_hoops_IRRRS),
	_hoops_IRRRS,
};


/* _hoops_HAR _hoops_ARGPR _hoops_IS _hoops_RGAP, _hoops_HIH _hoops_HAHH _hoops_IH _hoops_PPGAR _hoops_GRPRA _hoops_IIGR _hoops_ACPP _hoops_CGI _hoops_ISSC _hoops_HII _hoops_SRRRS */
local const _hoops_IGRCR _hoops_GARRS[] = {
	{_hoops_CRSRP, _hoops_GRRCR ("tpcm2"),		_hoops_RRRCR, 0, false},
	{_hoops_SRSRP,   _hoops_GRRCR ("tppix2"), _hoops_RRRCR, 0, false},
	{_hoops_RASRP,	  _hoops_GRRCR ("% area"),		_hoops_RRRCR, 0, false},
	{_hoops_GASRP, _hoops_GRRCR (""),			_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_RARRS = {
	_hoops_GGAPR (_hoops_GARRS),
	_hoops_GARRS,
};


local const _hoops_IGRCR _hoops_GAGHA[] = {
	{_hoops_HSCRP, _hoops_GRRCR ("oru"),						_hoops_RRRCR, 0, false},
	{_hoops_HSCRP, _hoops_GRRCR (""),						_hoops_RRRCR, 0, false},
	{_hoops_PSCRP, _hoops_GRRCR ("%"),						_hoops_RRRCR, 0, false},
	{_hoops_PSCRP, _hoops_GRRCR ("fru"),						_hoops_RRRCR, 0, false},
	{_hoops_PSCRP, _hoops_GRRCR ("% fru"),					_hoops_RRRCR, 0, false},
	{_hoops_PSCRP, _hoops_GRRCR ("% feature relative units"),_hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_RAGHA = {
	_hoops_GGAPR (_hoops_GAGHA),
	_hoops_GAGHA,
};


/* _hoops_HAR _hoops_ARGPR _hoops_IS _hoops_RGAP, _hoops_HIH _hoops_HAHH _hoops_IH _hoops_PPGAR _hoops_GRPRA _hoops_IIGR _hoops_ACPP _hoops_CGI _hoops_ISSC _hoops_HII _hoops_SRRRS */
local const _hoops_IGRCR _hoops_AARRS[] = {
	{_hoops_ARSRP, _hoops_GRRCR ("current"), _hoops_RRRCR, 0, false},
	{_hoops_PRSRP, _hoops_GRRCR ("explicit"), _hoops_SPPCR, 6, false},
};
local const _hoops_HPAGA _hoops_PARRS = {
	_hoops_GGAPR (_hoops_AARRS),
	_hoops_AARRS,
};


local const _hoops_IGRCR _hoops_HARRS[] = {
	{_hoops_CASRP, _hoops_GRRCR ("diagonal ratio per triangle"), _hoops_RRRCR, 0, false},
	{_hoops_SASRP, _hoops_GRRCR ("diagonal ratio"), _hoops_RRRCR, 0, false},
	{_hoops_GPSRP, _hoops_GRRCR ("diagonal per triangle"), _hoops_RRRCR, 0, false},
	{_hoops_RPSRP, _hoops_GRRCR ("diagonal"), _hoops_RRRCR, 0, false},
	{_hoops_APSRP, _hoops_GRRCR ("volume ratio per triangle"), _hoops_RRRCR, 0, false},
	{_hoops_PPSRP, _hoops_GRRCR ("volume ratio"), _hoops_RRRCR, 0, false},
	{_hoops_HPSRP, _hoops_GRRCR ("volume per triangle"), _hoops_RRRCR, 0, false},
	{_hoops_IPSRP, _hoops_GRRCR ("volume"), _hoops_RRRCR, 0, false},
	{_hoops_CPSRP, _hoops_GRRCR ("triangle size"), _hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_IARRS = {
	_hoops_GGAPR (_hoops_HARRS),
	_hoops_HARRS,
};


local const _hoops_IGRCR _hoops_CARRS[] = {
	{_hoops_SPSRP, _hoops_GRRCR ("none"), _hoops_RRRCR, 0, false},
	{_hoops_GHSRP, _hoops_GRRCR ("bounding"), _hoops_RRRCR, 0, false},
	{_hoops_RHSRP, _hoops_GRRCR ("coarsest"), _hoops_RRRCR, 0, false},
	{_hoops_AHSRP, _hoops_GRRCR ("coarsest none"), _hoops_RRRCR, 0, false},
	{_hoops_IHSRP, _hoops_GRRCR ("coarsest bounding"), _hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_SARRS = {
	_hoops_GGAPR (_hoops_CARRS),
	_hoops_CARRS,
};


local const _hoops_IGRCR _hoops_GPRRS[] = {
	{_hoops_SHSRP, _hoops_GRRCR ("fast"), _hoops_RRRCR, 0, false},
	{_hoops_GISRP, _hoops_GRRCR ("nice"), _hoops_RRRCR, 0, false},
	{_hoops_SHSRP, _hoops_GRRCR ("fastest"), _hoops_RRRCR, 0, false},
	{_hoops_GISRP, _hoops_GRRCR ("nicest"), _hoops_RRRCR, 0, false},
};
local const _hoops_HPAGA _hoops_RPRRS = {
	_hoops_GGAPR (_hoops_GPRRS),
	_hoops_GPRRS,
};


/* _hoops_CGH _hoops_PSSP _hoops_RH _hoops_APRRS _hoops_GASR _hoops_GGR _hoops_PPRRS, _hoops_HIH _hoops_CCA _hoops_AAP _hoops_SGS _hoops_CHR
 * _hoops_PGI _hoops_AARHA _hoops_PAR _hoops_HAR _hoops_ARGPR _hoops_IS _hoops_SPIGA _hoops_RGAP _hoops_IAPGR _hoops_GGSR */
local const _hoops_IGRCR _hoops_APGHA[] = {
	{_hoops_ISCRP, _hoops_GRRCR ("ratio"), _hoops_SPPCR, -_hoops_IGAIR, false},
	{_hoops_CSCRP, _hoops_GRRCR ("min triangle count"), _hoops_APRCA, 1, true},
	{_hoops_CSCRP, _hoops_GRRCR ("mtc"), _hoops_APRCA, 1, true}, /* _hoops_CPPC _hoops_PCCP _hoops_PHPPR */
	{_hoops_SSCRP, _hoops_GRRCR ("levels"), _hoops_APRCA, 1, false},
	{_hoops_SSCRP, _hoops_GRRCR ("num levels"), _hoops_APRCA, 1, false}, /* _hoops_CPPC _hoops_PCCP _hoops_PHPPR */
	{_hoops_IGSRP, _hoops_GRRCR ("algorithm"),_hoops_GHAGA, 1, false, &_hoops_RPRRS},
	{_hoops_ASCRP, _hoops_GRRCR ("conserve memory"),_hoops_RRRCR, 0, true},
	{_hoops_GGSRP, _hoops_GRRCR ("max degree"),_hoops_APRCA, 1, true},
	{_hoops_AGSRP, _hoops_GRRCR ("tolerance"),_hoops_CIGHA, 1, false, &_hoops_RAGHA},
	{_hoops_CGSRP, _hoops_GRRCR ("mode"),_hoops_GHAGA, 1, false, &_hoops_CRRRS},
	{_hoops_RGSRP, _hoops_GRRCR ("collapse duplicate vertices"), _hoops_RRRCR, 0, true},
	{_hoops_GRSRP, _hoops_GRRCR ("usefulness heuristic"),_hoops_GHAGA, 1, true, &_hoops_IARRS},
	{_hoops_IRSRP, _hoops_GRRCR ("calculation usefulness cutoff"),_hoops_SPPCR, -_hoops_IGAIR, true},

	/* _hoops_AAP _hoops_HRARH _hoops_HII _hoops_ARI _hoops_ISHP _hoops_CHR _hoops_HPRRS _hoops_HIH _hoops_IAIH */
	{_hoops_IASRP, _hoops_GRRCR ("threshold"), _hoops_CIGHA, -_hoops_IGAIR, false, &_hoops_RARRS},
	{_hoops_HASRP, _hoops_GRRCR ("clamp"),_hoops_APRCA, 1, true},
	{_hoops_SGSRP, _hoops_GRRCR ("preprocess"),_hoops_RRRCR, 0, true},
	{_hoops_RRSRP, _hoops_GRRCR ("bounding"),_hoops_GHAGA, 1, true, &_hoops_PARRS},
	{_hoops_PASRP, _hoops_GRRCR ("fallback"), _hoops_GHAGA, 1, true, &_hoops_SARRS},
};

local const _hoops_HPAGA _hoops_IPGHA = {
	_hoops_GGAPR (_hoops_APGHA),				_hoops_APGHA,
};


#define _hoops_IPRRS 8
local void _hoops_ACCCA (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			list,
	struct _hoops_GRICA *	_hoops_APHCR)
{
	int i, j;
	Option_Value *option_list, *option;
	_hoops_GCIIR _hoops_SPHHR;
	_hoops_RRPHA mask;

	ALLOC_ARRAY (_hoops_SPHHR.table, _hoops_IPRRS, _hoops_PIIIR *);
	ZERO_ARRAY (_hoops_SPHHR.table, _hoops_IPRRS, _hoops_PIIIR *);
	_hoops_SPHHR.size = _hoops_IPRRS;
	_hoops_SPHHR.count = 0;

	HI_Define_Constant_Options (_hoops_APGHA, _hoops_GGAPR (_hoops_APGHA), &_hoops_SPHHR);

	if (!HI_Parse_Options (_hoops_RIGC, list, &_hoops_SPHHR, &option_list, _hoops_SIACR))
		goto _hoops_HPAGR;

	if ((option = option_list) != null) do {
		mask = (_hoops_RRPHA) option->type->id;

		if (option->_hoops_GCACR) {
			_hoops_APHCR->value &= ~mask;
			if (mask == _hoops_CSCRP)
				_hoops_APHCR->_hoops_HISRP = 0;
		}
		else {
			_hoops_APHCR->value |= mask;
			if (mask == _hoops_ISCRP) {
				for (i = 0; i < option->_hoops_AIPCR; i++)
					_hoops_APHCR->_hoops_PRPHA[i] = option->value._hoops_PIPCR[i];
				for (j = i; j < _hoops_IGAIR; j++)
					_hoops_APHCR->_hoops_PRPHA[j] = _hoops_APHCR->_hoops_PRPHA[i-1];
			}
			else if (mask == _hoops_AGSRP) {
				_hoops_APHCR->tolerance =
					option->value._hoops_RRRHA[0].value;

				_hoops_APHCR->value |= _hoops_PSCRP;
				if (option->value._hoops_RRRHA[0]._hoops_HHP == _hoops_PSCRP) {
					_hoops_APHCR->value |= _hoops_PSCRP;
				}
				else
					_hoops_APHCR->value &= ~_hoops_PSCRP;
			}
			else if (mask == _hoops_CSCRP) {
				_hoops_APHCR->_hoops_HISRP = option->value._hoops_RIARA[0];
			}
			else if (mask == _hoops_SSCRP) {
				if (option->value._hoops_RIARA[0] > _hoops_IGAIR) {
					HE_ERROR (HEC_RENDERING, HES_INVALID_COUNT,
								"Number of LOD levels exceeds maximum supported");
					goto _hoops_HPAGR;
				}
				_hoops_APHCR->_hoops_IRSH = option->value._hoops_RIARA[0];
			}
			else if (mask == _hoops_IGSRP) {
				_hoops_RRPHA _hoops_PHSAA = option->value.option_list->type->id;
				_hoops_APHCR->_hoops_ARPHA = _hoops_PHSAA;
			}
			else if (mask == _hoops_CGSRP) {
				/* _hoops_IIH _hoops_CHR _hoops_CPRRS _hoops_RGAR _hoops_PGCR _hoops_AAP _hoops_IH _hoops_CCH, "_hoops_CAGH" _hoops_PPR "_hoops_CPAP",
				 * _hoops_HIS _hoops_RH _hoops_SPRRS _hoops_IGRH _hoops_GGR _hoops_SHARP->_hoops_PIRA _hoops_PAH _hoops_ASH _hoops_SCH _hoops_IH _hoops_IHHH */
				if (option->value.option_list->type->id != _hoops_CGSRP)
					_hoops_APHCR->value &= ~_hoops_CGSRP;
			}
			else if (mask == _hoops_GGSRP) {
				_hoops_APHCR->_hoops_RHPHA = option->value._hoops_RIARA[0];
			}
			/* _hoops_AGCR _hoops_ARAR _hoops_GRS _hoops_PASI _hoops_RGAR _hoops_RCPS _hoops_GH _hoops_RPP _hoops_RH _hoops_IPSP _hoops_HRGR _hoops_PHGSR _hoops_ISSC _hoops_IRS _hoops_GSGR
			 * _hoops_SSPP _hoops_HII [_hoops_HAICR]_hoops_GHRRS[_hoops_RHRRS]_hoops_AHRRS */
			else if (
				(mask == _hoops_GRSRP) ||
				(mask == _hoops_HASRP) ||
				(mask == _hoops_IRSRP) ||
				(mask == _hoops_IASRP) ||
				(mask == _hoops_RRSRP) ||
				(mask == _hoops_PASRP)) {
			}
		}
	} while ((option = option->next) != null);

_hoops_HPAGR:
	HI_Free_Option_List (_hoops_RIGC, option_list);

	{
		_hoops_PIIIR			**_hoops_PHRRS = _hoops_SPHHR.table;
		_hoops_PIIIR			**_hoops_HHRRS;

		_hoops_HHRRS = _hoops_PHRRS + _hoops_IPRRS;
		do {
			_hoops_PIIIR			*victim;

			_hoops_RGGA ((victim = *_hoops_PHRRS) == null) {
				_hoops_CIGPR (_hoops_RIGC,victim);
				_hoops_HPRH (victim);
			}
		} _hoops_RGGA (++_hoops_PHRRS == _hoops_HHRRS);
	}
	FREE_ARRAY (_hoops_SPHHR.table, _hoops_IPRRS, _hoops_PIIIR *);
} /* _hoops_RSGR _hoops_IRGH _hoops_API _hoops_IHRRS */





local void _hoops_CHRRS (Attribute *a, struct _hoops_GRICA *_hoops_APHCR)
{
	_hoops_RHAIR *	_hoops_AHAIR = (_hoops_RHAIR *)a;

	if (_hoops_AHAIR->_hoops_PRSI == null)
		return;

	_hoops_RRPHA	mask = _hoops_AHAIR->_hoops_PRSI->mask;
	_hoops_RRPHA	value = _hoops_AHAIR->_hoops_PRSI->value;
	_hoops_APHCR->value = (_hoops_APHCR->value & ~mask) | (value & mask);

	if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_ISCRP)) {
		for (int i = 0; i < _hoops_IGAIR; i++)
			_hoops_APHCR->_hoops_PRPHA[i] = _hoops_AHAIR->_hoops_PRSI->_hoops_PRPHA[i];
	}
	if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_CSCRP)) {
		_hoops_APHCR->_hoops_HISRP = _hoops_AHAIR->_hoops_PRSI->_hoops_HISRP;
	}
	if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_SSCRP)) {
		_hoops_APHCR->_hoops_IRSH = _hoops_AHAIR->_hoops_PRSI->_hoops_IRSH;
	}
	if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_GGSRP)) {
		_hoops_APHCR->_hoops_RHPHA = _hoops_AHAIR->_hoops_PRSI->_hoops_RHPHA;
	}
	if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_AGSRP)) {
		_hoops_APHCR->tolerance = _hoops_AHAIR->_hoops_PRSI->tolerance;
	}
	if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_IGSRP)) {
		_hoops_APHCR->_hoops_ARPHA = _hoops_AHAIR->_hoops_PRSI->_hoops_ARPHA;
	}
}


/* _hoops_SHRRS == _hoops_IRAP _hoops_AGSR _hoops_PCPA _hoops_SR _hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_GIRRS _hoops_AIIPA _hoops_IS _hoops_SGS _hoops_IGRI
 * (*_hoops_SHRRS) == _hoops_IRAP _hoops_AGSR _hoops_SGS _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_ARAS _hoops_CRGR _hoops_SGS _hoops_IGRI _hoops_ARPP (_hoops_PGAP
 *		  _hoops_RPP _hoops_SGS _hoops_AAPR _hoops_HAR _hoops_RH _hoops_AGIR _hoops_CHH _hoops_RIRRS _hoops_HHH _hoops_ARAPH)
 */
local void _hoops_AIRRS (
	Attribute *a,
	struct _hoops_ARRRS *data,
	struct _hoops_GRICA **_hoops_PIRRS,
	float **_hoops_HIRRS)
{
	do {
		if (a->type == HK_RENDERING_OPTIONS && _hoops_PIRRS) {
			*_hoops_PIRRS = data->_hoops_PRRRS;
			ALLOC(data->_hoops_PRRRS, struct _hoops_GRICA);
			_hoops_RSAI(*_hoops_PIRRS, struct _hoops_GRICA, data->_hoops_PRRRS);
			_hoops_CHRRS(a, data->_hoops_PRRRS);
		}
		if (a->type == HK_MODELLING_MATRIX && _hoops_HIRRS) {
			*_hoops_HIRRS = data->_hoops_HRRRS;
			ALLOC_ARRAY(data->_hoops_HRRRS, 16, float);
			_hoops_AIGA(*_hoops_HIRRS, 16, float, data->_hoops_HRRRS);
			HI_Compute_Matrix_Product(
					&((_hoops_ISGI *)a)->matrix.elements[0][0],
					data->_hoops_HRRRS,
					data->_hoops_HRRRS);
		}
		a = a->next;
	} while (a != null);
}


local void _hoops_IIRRS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	bool *					_hoops_CIRRS,
	_hoops_SGGGI *			list,
	struct _hoops_ARRRS *	data)
{

	data->_hoops_GIPAC->ReplaceItem(_hoops_SRCP, 0);

	if (_hoops_SRCP->_hoops_IPPGR != null) {
		Attribute *a;
		if ((a = _hoops_SRCP->_hoops_IPPGR) != null) do {
			if (a->type == HK_MODELLING_MATRIX) {
				*_hoops_CIRRS = true;
				break;
			}
		} while ((a = a->next) != null);
	}

	Subsegment *	s;
	if ((s = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (s->type == _hoops_AGRPR) {
			_hoops_PGRPR const *		inc = (_hoops_PGRPR const *)s;
			_hoops_IIRRS(_hoops_RIGC, inc->_hoops_IGRPR, _hoops_CIRRS, list, data);
		}
		else
			_hoops_IIRRS(_hoops_RIGC, (_hoops_CRCP const *)s, _hoops_CIRRS, list, data);
	} while ((s = s->next) != null);

	Geometry *	g;
	if ((g = _hoops_SRCP->geometry) != null) do {
		if (g->type == _hoops_SCIP)
			list->AddLast((Shell*)g);
	} while ((g = g->next) != null);
}


/* _hoops_RGR _hoops_SPR _hoops_HRGR _hoops_SIGR _hoops_RGAR _hoops_RPP _hoops_IIH _hoops_CHR _hoops_SIRRS _hoops_HCIA _hoops_GIAA _hoops_IRS _hoops_CAGH _hoops_HHIS _hoops_PRCCA */
local void _hoops_GCRRS (_hoops_CRCP const * _hoops_SRCP, struct _hoops_ARRRS * data)
{
	Subsegment *s;
	Geometry *g = null;

	float *_hoops_HIRRS = null;

	if (_hoops_SRCP->_hoops_IPPGR != null)
		_hoops_AIRRS(_hoops_SRCP->_hoops_IPPGR, data, null, &_hoops_HIRRS);

	if ((s = _hoops_SRCP->_hoops_RGRPR) != null) do {
		if (s->type == _hoops_AGRPR) {
			_hoops_PGRPR const *		inc = (_hoops_PGRPR const *)s;
			_hoops_GCRRS(inc->_hoops_IGRPR, data);
		}
		else
			_hoops_GCRRS((_hoops_CRCP const *)s, data);
	} while ((s = s->next) != null);

	if ((g = _hoops_SRCP->geometry) != null) do {
		if (g->type == _hoops_SCIP) {
			Shell *_hoops_SPHPR = (Shell *)g;
			HI_Compute_Transformed_Points(
				_hoops_SPHPR->point_count,
				_hoops_SPHPR->points,
				data->_hoops_HRRRS,
				data->_hoops_HCRGR + data->_hoops_SCPI
			);
			data->_hoops_SCPI += _hoops_SPHPR->point_count;
		}
	} while ((g = g->next) != null);

	if (_hoops_HIRRS) {
		FREE_ARRAY(data->_hoops_HRRRS, 16, float);
		data->_hoops_HRRRS = _hoops_HIRRS;
	}
}



local void _hoops_RCRRS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	void *					pass)
{
	
	_hoops_SGGGI *			list;
	int _hoops_SCPI, _hoops_ACRRS;
	int _hoops_PCRRS, _hoops_HCRRS;
	int _hoops_ICRRS, _hoops_CCRRS;
	int _hoops_SCRRS, _hoops_GSRRS;
	Point *_hoops_HCRGR, *_hoops_RSRRS;
	int *_hoops_ASRRS, *_hoops_PSRRS;
	int *ptr, *end;
	int i, len, level;
	_hoops_SIRIR *_hoops_ASIIR;
	Shell const *_hoops_CPSIH;
	Shell *_hoops_SPHPR;
	bool _hoops_SHCIH = false;
	bool _hoops_CIRRS = false;
	struct _hoops_GRICA *_hoops_HSRRS = null;
	bool _hoops_HRPHA;
	Attribute *_hoops_ISRRS;
	char _hoops_RICIA[128];
	_hoops_PGAIR *	_hoops_HGAIR = _hoops_SRCP->_hoops_SSRIR();

	if (_hoops_HGAIR != null) {
		for (i = 0; i < _hoops_IGAIR; i++) {
			if (_hoops_HGAIR->data[i] != null) {
				HI_Au_Revoir ((_hoops_HPAH *)(_hoops_HGAIR->data[i]));
				_hoops_HGAIR->data[i] = null;
			}
		}
	}

	struct _hoops_ARRRS *	data = (struct _hoops_ARRRS *)pass;

	_hoops_HSRRS = data->_hoops_PRRRS;
	list = data->list;

	/* _hoops_RPP _hoops_IIH _hoops_HRGR _hoops_IRS _hoops_SIRRS _hoops_RSGA _hoops_HPGR _hoops_RH _hoops_SCIA, _hoops_HIH _hoops_CSRRS _hoops_SHS, _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_ASSP'_hoops_RA
	 * _hoops_RPR _hoops_RRHC _hoops_RH _hoops_HACH _hoops_PIRA _hoops_IIGR "_hoops_SSRRS" */
	_hoops_ISRRS = _hoops_SRCP->_hoops_IPPGR;
	((_hoops_CRCP alter *)_hoops_SRCP)->_hoops_IPPGR = null;
	/* _hoops_SPIC _hoops_RH _hoops_CAGH _hoops_HHIS */
	_hoops_IIRRS (_hoops_RIGC, _hoops_SRCP, &_hoops_CIRRS, list, data);
	((_hoops_CRCP alter *)_hoops_SRCP)->_hoops_IPPGR = _hoops_ISRRS;
	_hoops_SCPI = 0;
	_hoops_PCRRS = 0;

	list->ResetCursor();
	while ((_hoops_CPSIH = list->PeekCursor()) != null) {
		ASSERT(_hoops_CPSIH->type == _hoops_SCIP);
		_hoops_SCPI += _hoops_CPSIH->point_count;
		if (_hoops_CPSIH->face_list == null)
			HI_Face_List_From_Tristrips(_hoops_RIGC, (Shell *)_hoops_CPSIH);
		_hoops_PCRRS += _hoops_CPSIH->face_list_length;
		list->AdvanceCursor();
	}
	if (_hoops_SCPI == 0 || _hoops_PCRRS == 0) {
		/* _hoops_RGR _hoops_CGH _hoops_GACC _hoops_IRAA _hoops_PICP _hoops_IIGR _hoops_AGIR _hoops_GGARS(_hoops_HIGR) == 0 */
		return;
	}
	_hoops_SCRRS = _hoops_SCPI;
	ALLOC_ARRAY(_hoops_HCRGR, _hoops_SCRRS, Point);
	_hoops_ICRRS = _hoops_PCRRS;
	ALLOC_ARRAY(_hoops_ASRRS, _hoops_ICRRS, int);
	if (list->Count() == 1 && !_hoops_CIRRS) {
		_hoops_CPSIH = list->RemoveFirst();
		_hoops_AIGA(_hoops_CPSIH->points, _hoops_CPSIH->point_count, Point, _hoops_HCRGR);
		_hoops_AIGA(_hoops_CPSIH->face_list, _hoops_CPSIH->face_list_length, int, _hoops_ASRRS);
		_hoops_HRPHA = BIT(_hoops_HSRRS->value, _hoops_RGSRP);
	}
	else {
		/* _hoops_GHPHR _hoops_RH _hoops_RSSA _hoops_CRPR _hoops_IH _hoops_RH _hoops_SCSI _hoops_RRCPR */
		_hoops_SCPI = 0;
		if (!_hoops_CIRRS) {
			list->ResetCursor();
			while ((_hoops_CPSIH = list->PeekCursor()) != null) {
				_hoops_AIGA (_hoops_CPSIH->points, _hoops_CPSIH->point_count, Point,
							_hoops_HCRGR + _hoops_SCPI);
				_hoops_SCPI += _hoops_CPSIH->point_count;
				list->AdvanceCursor();
			}
		}
		else {
			data->_hoops_SCPI = 0;
			data->_hoops_HCRGR = _hoops_HCRGR;
			_hoops_GCRRS (_hoops_SRCP, data);
		}
		/* _hoops_GHPHR _hoops_RH _hoops_HSP _hoops_HIGR _hoops_IIGR _hoops_RH _hoops_SCSI _hoops_RRCPR */
		_hoops_SCPI = 0;
		_hoops_PCRRS = 0;
		while ((_hoops_CPSIH = list->RemoveFirst()) != null) {
			_hoops_AIGA(_hoops_CPSIH->face_list, _hoops_CPSIH->face_list_length, int,
						_hoops_ASRRS + _hoops_PCRRS);
			/* _hoops_GPISR _hoops_RH _hoops_GPHA _hoops_PSPI _hoops_HPP _hoops_RH _hoops_APHR _hoops_SHI (_hoops_IH _hoops_HCR _hoops_SCHS _hoops_AHSAR _hoops_RH _hoops_SRS). */
			if (_hoops_SCPI > 0) {
				ptr = _hoops_ASRRS + _hoops_PCRRS;
				end = ptr + _hoops_CPSIH->face_list_length;
				while (ptr < end) {
					if (*ptr > 0)
						len = *ptr + 1;
					else
						len = -(*ptr + 1);
					for (i = 1; i < len; i++)
						ptr[i] += _hoops_SCPI;
					ptr += len;
				}
			}
			_hoops_SCPI += _hoops_CPSIH->point_count;
			_hoops_PCRRS += _hoops_CPSIH->face_list_length;
		}
		_hoops_HRPHA = true;
	}

	/* _hoops_GASA: _hoops_SRSA _hoops_PGGA _hoops_PRCCA _hoops_HRISP, _hoops_SR _hoops_PAH'_hoops_RA _hoops_SHH _hoops_RCRR _hoops_SGS _hoops_SCH _hoops_PPPPR'_hoops_RA _hoops_GAHR _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_CRPR.
	 * _hoops_PA _hoops_CCA _hoops_AHHSR < 0.3 _hoops_GRS _hoops_PASI _hoops_HAR _hoops_AA _hoops_HIS, _hoops_HIH _hoops_SR _hoops_RRP _hoops_IS _hoops_SSS _hoops_HHH _hoops_PPRRR _hoops_IS _hoops_HGCR _hoops_IRS _hoops_RRI
	 * _hoops_RGARS _hoops_AGGAI. */
	if (_hoops_HSRRS->_hoops_PRPHA[0] < 0.3f)
		_hoops_CCRRS = _hoops_PCRRS;
	else
		_hoops_CCRRS = (int)(2.5f * _hoops_PCRRS * _hoops_HSRRS->_hoops_PRPHA[0]);
	ALLOC_ARRAY(_hoops_PSRRS, _hoops_CCRRS, int);
	_hoops_GSRRS = _hoops_SCRRS;
	ALLOC_ARRAY(_hoops_RSRRS, _hoops_GSRRS, Point);

	if (_hoops_HRPHA) {
		_hoops_RICIA[0] = '\0';
		if (_hoops_HSRRS->tolerance > 0) {
			char * _hoops_AGARS;

			_hoops_AGARS = HI_Sprintf1(_hoops_RICIA, _hoops_RICIA+128, "tolerance = %f", &_hoops_HSRRS->tolerance);
			if (BIT(_hoops_HSRRS->value, _hoops_PSCRP))
				_hoops_AGARS = HI_Copy_Chars("% fru", _hoops_AGARS);
			*_hoops_AGARS = '\0';
		}

		HI_Compute_Optimized_Shell(_hoops_RIGC,
			_hoops_SCPI, _hoops_HCRGR,
			null,
			_hoops_PCRRS, _hoops_ASRRS,
			_hoops_RICIA,
			&(_hoops_ACRRS), _hoops_RSRRS,
			&(_hoops_HCRRS), _hoops_PSRRS,
			null, null);

		_hoops_AIGA(_hoops_RSRRS, _hoops_ACRRS, Point, _hoops_HCRGR);
		_hoops_AIGA(_hoops_PSRRS, _hoops_HCRRS, int, _hoops_ASRRS);
		_hoops_PCRRS = _hoops_HCRRS;
		_hoops_SCPI = _hoops_ACRRS;
	}
	else {
		_hoops_ACRRS = _hoops_SCPI;
		_hoops_HCRRS = _hoops_PCRRS;
	}

	if (_hoops_ACRRS == 0 || _hoops_HCRRS == 0) {
		/* _hoops_RGR _hoops_CGH _hoops_PAHH _hoops_IIP _hoops_IHPS */
		return;
	}

	/* _hoops_HA _hoops_GSRGR _hoops_RH _hoops_GARRA _hoops_RRCPR _hoops_CRGR _hoops_IRS _hoops_CAGH-_hoops_PAPA _hoops_PRCCA.	 _hoops_GISA _hoops_PCCP _hoops_IGS _hoops_IGCI _hoops_HIS _hoops_SGS _hoops_SR _hoops_PAH
	 * _hoops_PGARS _hoops_SCH _hoops_RHIR _hoops_RH _hoops_GSSR _hoops_HGARS */
	ZALLOC (_hoops_ASIIR, _hoops_SIRIR);
	_hoops_ASIIR->type = _hoops_CIRIR;
	_hoops_ASIIR->_hoops_HIHI = 1;
	_hoops_ASIIR->_hoops_GCRIR = _hoops_RSRIR;
	_hoops_ASIIR->info._hoops_PRSI.offset = -1; /* _hoops_AISP _hoops_SPHR */
	_hoops_ASIIR->info._hoops_PRSI._hoops_IGRPR = (_hoops_HPAH *) _hoops_SRCP;
	_hoops_PRRH (_hoops_SRCP);

	for (level = 1; level <= _hoops_HSRRS->_hoops_IRSH; level++) {
		_hoops_ASIIR->info._hoops_PRSI.offset = level;

		ZALLOC (_hoops_SPHPR, Shell);
		_hoops_SPHPR->type = _hoops_SCIP;
		_hoops_SPHPR->_hoops_CPGPR = _hoops_PHSSR;
		_hoops_SPHPR->_hoops_SPHA = -1;	/* _hoops_HAR _hoops_AISP _hoops_GAPR */
		_hoops_SPHPR->face_count = -1;	/* _hoops_HAR _hoops_AISP _hoops_GAPR */

		if (_hoops_HSRRS->_hoops_ARPHA == _hoops_SHSRP) {
			/* _hoops_ICSI _hoops_RIIRA _hoops_HRGR _hoops_SHR _hoops_SSCHA._hoops_PCCIR._hoops_RA. _hoops_AIRA _hoops_RRCPR */
			float _hoops_PRPHA = _hoops_HSRRS->_hoops_PRPHA[0];

			for (i = 1; i < level; i++)
				_hoops_PRPHA *= _hoops_HSRRS->_hoops_PRPHA[i];
			HI_Compute_LOD(_hoops_RIGC,
				_hoops_HSRRS->_hoops_ARPHA,
				_hoops_PRPHA,
				false,
				_hoops_SCPI, (float const *)_hoops_HCRGR,
				_hoops_PCRRS, _hoops_ASRRS,
				&(_hoops_ACRRS), (float *)_hoops_RSRRS,
				&(_hoops_HCRRS), _hoops_PSRRS,
				null, null);
		}
		else {
			HI_Compute_LOD(_hoops_RIGC,
				_hoops_HSRRS->_hoops_ARPHA,
				_hoops_HSRRS->_hoops_PRPHA[0],
				false,
				_hoops_SCPI, (float const *)_hoops_HCRGR,
				_hoops_PCRRS, _hoops_ASRRS,
				&(_hoops_ACRRS), (float *)_hoops_RSRRS,
				&(_hoops_HCRRS), _hoops_PSRRS,
				null, null);
			/* _hoops_AGAPR _hoops_RIIRA _hoops_HRGR _hoops_SSCHA._hoops_PCCIR._hoops_RA _hoops_GCPC _hoops_RRCPR, _hoops_HIS _hoops_IPS "_hoops_SSAAA" _hoops_ISSC _hoops_CRGR "_hoops_APSR" _hoops_GGR _hoops_IGARS
			 * _hoops_IH _hoops_RH _hoops_SPS _hoops_IPGR */
			_hoops_AIGA(_hoops_RSRRS, _hoops_ACRRS, Point, _hoops_HCRGR);
			_hoops_AIGA(_hoops_PSRRS, _hoops_HCRRS, int, _hoops_ASRRS);
			_hoops_PCRRS = _hoops_HCRRS;
			_hoops_SCPI = _hoops_ACRRS;
		}
		if (_hoops_HCRRS <= _hoops_HSRRS->_hoops_HISRP * 4) {
			FREE (_hoops_SPHPR, Shell);
			_hoops_SPHPR = null;
			break;
		}
		/* _hoops_SR _hoops_RRP _hoops_PSCA _hoops_IIGR _hoops_CGCH _hoops_SPCC _hoops_IH _hoops_SCHS, _hoops_PAR _hoops_AGAH' _hoops_PPGS _hoops_CGARS _hoops_GRS _hoops_HPPPR _hoops_CGPR _hoops_SCH'_hoops_GRI _hoops_GHIR
		 * _hoops_IS _hoops_RCAPI _hoops_PGGC.	_hoops_PHGP _hoops_SR _hoops_CCPP _hoops_CCAH _hoops_PSCA _hoops_PPR _hoops_IRHH _hoops_RH _hoops_IPS */
		ALLOC_ARRAY_ALIGNED (_hoops_SPHPR->points, _hoops_ACRRS, Point, 16);
		_hoops_AIGA (_hoops_RSRRS, _hoops_ACRRS, Point, _hoops_SPHPR->points);
		ALLOC_ARRAY (_hoops_SPHPR->face_list, _hoops_HCRRS, int);
		_hoops_AIGA (_hoops_PSRRS, _hoops_HCRRS, int, _hoops_SPHPR->face_list);
		_hoops_SPHPR->point_count = _hoops_ACRRS;
		_hoops_SPHPR->face_list_length = _hoops_HCRRS;
		_hoops_SPHPR->face_count = _hoops_SPHPR->face_list_length / 4;
		HI_Assemble_3D_Tristrips ((Polyhedron *)_hoops_SPHPR,  (_hoops_SARHR)~0,	true);
		HI_Insert_Geometry (_hoops_RIGC, (_hoops_HPAH *)_hoops_ASIIR, (Geometry *) _hoops_SPHPR,
							_hoops_SHCIH,
							_hoops_SPHPR->point_count > 0 ?
								_hoops_IHSSR |
									(_hoops_SPHPR->face_list_length > 0 ?
											_hoops_SIGPR :
											_hoops_ICHPA) :
								_hoops_CCHPA);
	}
	if (_hoops_SRCP != null)
		_hoops_SASIR (_hoops_RIGC, _hoops_SRCP, _hoops_PHSSR);
	_hoops_HPRH(_hoops_ASIIR);

	if (_hoops_HCRGR)
		FREE_ARRAY(_hoops_HCRGR, _hoops_SCRRS, Point);
	if (_hoops_RSRRS)
		FREE_ARRAY(_hoops_RSRRS, _hoops_GSRRS, Point);
	if (_hoops_ASRRS)
		FREE_ARRAY(_hoops_ASRRS, _hoops_ICRRS, int);
	if (_hoops_PSRRS)
		FREE_ARRAY(_hoops_PSRRS, _hoops_CCRRS, int);
}


local void _hoops_SGARS (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	struct _hoops_ARRRS *	data)
{
	Subsegment *s;
	Geometry *g;
	struct _hoops_GRICA *_hoops_PIRRS = null;

	data->_hoops_GIPAC->ReplaceItem(_hoops_SRCP, 0);

	if (_hoops_SRCP->_hoops_IPPGR != null)
		_hoops_AIRRS(_hoops_SRCP->_hoops_IPPGR, data, &_hoops_PIRRS, null);

	if (BIT(data->_hoops_PRRRS->value, _hoops_CGSRP)) {
		_hoops_RCRRS(_hoops_RIGC, _hoops_SRCP, data);
	}
	else {
		if ((g = _hoops_SRCP->geometry) != null) do {
			if (g->type == _hoops_SCIP || g->type == _hoops_GSIP) {
				struct _hoops_GRICA *_hoops_HSRRS = data->_hoops_PRRRS;
				HI_Compute_Polyhedron_LOD(_hoops_RIGC,
					(Polyhedron *)g,
					0,
					_hoops_HSRRS->_hoops_IRSH,
					_hoops_HSRRS->_hoops_ARPHA,
					_hoops_HSRRS->_hoops_PRPHA[0],
					BIT(_hoops_HSRRS->value,_hoops_RGSRP),
					_hoops_HSRRS->_hoops_HISRP,
					_hoops_HSRRS->_hoops_RHPHA);
			}
		} while ((g = g->next) != null);

		if ((s = _hoops_SRCP->_hoops_RGRPR) != null) do {
			if (s->type == _hoops_AGRPR) {
				_hoops_PGRPR const *		inc = (_hoops_PGRPR const *)s;
				_hoops_SGARS(_hoops_RIGC, inc->_hoops_IGRPR, data);
			}
			else
				_hoops_SGARS(_hoops_RIGC, (_hoops_CRCP const *)s, data);
		} while ((s = s->next) != null);
	}

	if (_hoops_PIRRS) {
		FREE(data->_hoops_PRRRS, struct _hoops_GRICA);
		data->_hoops_PRRRS = _hoops_PIRRS;
	}
}


local void _hoops_GRARS (
   _hoops_AIGPR *	_hoops_RIGC,
   _hoops_CRCP *				_hoops_SRCP,
   void *					pass)
{
	struct _hoops_ARRRS *	data = (struct _hoops_ARRRS *)pass;

	if (data->_hoops_GIPAC->LookupItem(_hoops_SRCP) == VHASH_STATUS_SUCCESS)
		return;

	struct _hoops_GRICA _hoops_RRARS;
	float _hoops_ARARS[16];

	_hoops_RSAI(data->_hoops_PRRRS, struct _hoops_GRICA, &_hoops_RRARS);
	_hoops_AIGA(data->_hoops_HRRRS, 16, float, _hoops_ARARS);
	_hoops_SGARS (_hoops_RIGC, _hoops_SRCP, data);
	_hoops_RSAI(&_hoops_RRARS, struct _hoops_GRICA, data->_hoops_PRRRS);
	_hoops_AIGA(_hoops_ARARS, 16, float, data->_hoops_HRRRS);
}


HC_INTERFACE void HC_CDECL HC_Regenerate_LOD (
	char const *	segment,
	char const *	_hoops_RARCC)
{
	_hoops_PAPPR context("Regenerate_LOD");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_SS (null, "HC_Regenerate_LOD (%S, %S);\n", segment, _hoops_RARCC));
	);

	/* _hoops_GHPHR _hoops_RH _hoops_CIGS _hoops_HSH _hoops_IH _hoops_RH _hoops_PRCCA _hoops_AAP _hoops_CCA _hoops_HSSHH */
	struct _hoops_GRICA _hoops_APHCR;
	ZERO_STRUCT (&_hoops_APHCR, struct _hoops_GRICA);
	for (int i = 0; i < _hoops_IGAIR; i++) {
		_hoops_APHCR._hoops_PRPHA[i] = 0.5f;
	}
	_hoops_APHCR._hoops_HISRP = 25;
	_hoops_APHCR._hoops_IRSH = 2;
	_hoops_APHCR._hoops_RHPHA = 15;
	_hoops_APHCR.tolerance = 0.0f;
	_hoops_APHCR._hoops_ARPHA = _hoops_SHSRP;

	if (_hoops_RARCC!=null && _hoops_RARCC[0]!='\0')
		_hoops_ACCCA(context, _hoops_RARCC, &_hoops_APHCR);

	struct _hoops_ARRRS data;
	data.list = POOL_NEW(context->memory_pool, _hoops_SGGGI)(context->memory_pool);
	data._hoops_GIPAC = POOL_NEW(context->memory_pool, _hoops_AAPHP)(context->memory_pool, _hoops_PAPHP);
	data._hoops_PRRRS = &_hoops_APHCR;

	float _hoops_SGCGI[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
	data._hoops_HRRRS = _hoops_SGCGI;

	_hoops_RPPPR();

	HI_For_Each (context, segment, true, _hoops_GRARS, (void *)&data);

	if (data._hoops_GIPAC->Count() == 0) {
		HE_WARNING (HEC_SEGMENT, HES_SEGMENT_EXISTS, Sprintf_S(null, "no such segment: '%s'", segment));
	}

	_hoops_IRRPR();

	delete data._hoops_GIPAC;
	delete data.list;
}

HC_INTERFACE void HC_CDECL HC_Regenerate_LOD_By_Key (
	Key				key,
	char const *	_hoops_RARCC)
{
	_hoops_PAPPR context("Regenerate_LOD_By_Key");

	CODE_GENERATION (
		HI_Dump_Code (Sprintf_LD (null, "HC_Regenerate_LOD_By_Key (LOOKUP (%D), ", key));
		HI_Dump_Code (Sprintf_S (null, "%S);\n", _hoops_RARCC));
	);

	_hoops_CSPPR();

	_hoops_CRCP	*	_hoops_SRCP = (_hoops_CRCP *)_hoops_RCSSR (context, key);

	if (_hoops_SRCP == null || BIT (_hoops_SRCP->_hoops_RRHH, _hoops_HGAGR) || _hoops_SRCP->type != _hoops_IRCP) {
		HE_ERROR (HEC_SEGMENT, HES_INVALID_KEY, "Key does not refer to a valid segment");
	}
	else {
		/* _hoops_GHPHR _hoops_RH _hoops_CIGS _hoops_HSH _hoops_IH _hoops_RH _hoops_PRCCA _hoops_AAP _hoops_CCA _hoops_HSSHH */
		struct _hoops_GRICA _hoops_APHCR;
		ZERO_STRUCT (&_hoops_APHCR, struct _hoops_GRICA);
		for (int i = 0; i < _hoops_IGAIR; i++) {
			_hoops_APHCR._hoops_PRPHA[i] = 0.5f;
		}
		_hoops_APHCR._hoops_HISRP = 25;
		_hoops_APHCR._hoops_IRSH = 2;
		_hoops_APHCR._hoops_RHPHA = 15;
		_hoops_APHCR.tolerance = 0.0f;
		_hoops_APHCR._hoops_ARPHA = _hoops_SHSRP;
		if (_hoops_RARCC!=null && _hoops_RARCC[0]!='\0')
			_hoops_ACCCA(context, _hoops_RARCC, &_hoops_APHCR);

		struct _hoops_ARRRS data;
		data.list = POOL_NEW(context->memory_pool, _hoops_SGGGI)(context->memory_pool);

		data._hoops_GIPAC = POOL_NEW(context->memory_pool, _hoops_AAPHP)(context->memory_pool, _hoops_PAPHP);

		data._hoops_PRRRS = &_hoops_APHCR;

		float _hoops_SGCGI[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
		data._hoops_HRRRS = _hoops_SGCGI;

		_hoops_RPPPR();
		_hoops_GRARS(context, _hoops_SRCP, &data);
		_hoops_IRRPR();

		delete data._hoops_GIPAC;
		delete data.list;
	}

	_hoops_IRRPR();
}


#else /* #_hoops_CHS _hoops_PRARS */


HC_INTERFACE void HC_CDECL HC_Regenerate_LOD (
	char const		*segment,
	char const		*_hoops_RARCC)
{
	UNREFERENCED(segment);
	UNREFERENCED(_hoops_RARCC);

	_hoops_PAPPR context("Regenerate_LOD");
	_hoops_IRPPR ("LOD Generation");
}
HC_INTERFACE void HC_CDECL HC_Regenerate_LOD_By_Key (
	Key			key,
	char const		*_hoops_RARCC)
{
	UNREFERENCED(key);
	UNREFERENCED(_hoops_RARCC);

	_hoops_PAPPR context("Regenerate_LOD_By_Key");
	_hoops_IRPPR ("LOD Generation");
}


#endif



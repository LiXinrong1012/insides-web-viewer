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
 * $Id: obf_tmp.txt 1.126 2010-10-06 19:15:52 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "phdraw.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"

// _hoops_RGR _hoops_CGH _hoops_SHH _hoops_IRS _hoops_SPCC _hoops_SGS _hoops_GRS _hoops_RHHR _hoops_RH _hoops_HHCI _hoops_PPGS
#define _hoops_CGRCP	64

#ifndef _hoops_SGRCP

#define _hoops_GRRCP() do									\
		if (_hoops_ACI != _hoops_PPGCP) {						\
			*_hoops_IAIPR = _hoops_ACI - _hoops_PPGCP;		\
			pe->total += *_hoops_IAIPR++;				\
			++pe->_hoops_PHHA;								\
			_hoops_PPGCP = _hoops_ACI;							\
		} while (0)

#define _hoops_RRRCP(nr) do {									\
		_hoops_GRRCP();									\
		pe->point_count = _hoops_ASPS;					\
		if (_hoops_CGSHR == 0) \
			pe->_hoops_SPHA = _hoops_SPHA; \
		else \
			pe->_hoops_SPHA = _hoops_CGSHR;					\
		(*action)(nr, pe);								\
														\
		if (_hoops_GGPGR(nr))			\
			goto _hoops_HPAGR;								\
														\
		if (pe->_hoops_HSAI > 1) { \
			_hoops_ISAI(pe); \
			ZALLOC(pe, Polyedge); \
			_hoops_ICAI(pe); \
			pe->lengths_allocated = _hoops_CGRCP; \
			pe->_hoops_IPII = _hoops_CGRCP; \
			pe->_hoops_CPII = _hoops_CGRCP; \
			ALLOC_ARRAY(pe->lengths, pe->lengths_allocated, int); \
			ALLOC_ARRAY(pe->_hoops_AIHA, pe->_hoops_IPII, int); \
			ALLOC_ARRAY(pe->_hoops_SPII, pe->_hoops_CPII, int); \
			pe->_hoops_RAHH |= _hoops_AAHH; \
			pe->points = out_points; \
			pe->_hoops_RSHA = _hoops_RSHA; \
			pe->point_count = point_count; \
			pe->_hoops_SRHA = DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS|DL_TEMPORARY_DATA; \
			pe->_hoops_GSAI = nr->_hoops_IRR->_hoops_CSA & _hoops_RHII; \
			_hoops_ARRCP = pe->_hoops_AIHA + _hoops_CGRCP - 2; \
			if (_hoops_PRRCP) \
				pe->_hoops_PCHA = _hoops_HRRCP; \
			else { \
				pe->_hoops_ASHA = _hoops_IRRCP; \
				if (_hoops_RSHA != null) \
					pe->_hoops_RSHA = _hoops_CRRCP; \
			} \
			if (_hoops_ICHA != null) \
				pe->_hoops_ICHA = _hoops_SRRCP; \
			if (_hoops_CCHA != null) { \
				pe->_hoops_CCHA = _hoops_GARCP; \
				pe->_hoops_GSHA = _hoops_RARCP; \
			} \
		} \
		_hoops_ACI = pe->_hoops_AIHA;						\
		_hoops_AARCP = pe->_hoops_SPII;						\
		pe->_hoops_PHHA = 0;									\
		pe->total = 0;									\
		_hoops_IAIPR = pe->lengths;					\
		_hoops_PPGCP = _hoops_ACI;								\
		_hoops_ASPS = 0;									\
		_hoops_CGSHR  = 0;									\
		_hoops_PARCP[0] = _hoops_PARCP[1] = -1;						\
	} while (0)

/* _hoops_ICIC _hoops_IS _hoops_SGH _hoops_SPRS-_hoops_GPISR _hoops_CCA _hoops_PRSAR _hoops_IS _hoops_RGR _hoops_RIGR */
#define _hoops_HARCP(in, index, _hoops_PAGR, _hoops_IARCP)	do {		\
		if (_hoops_RSHA != null)								\
			_hoops_CRRCP[_hoops_CGSHR] = _hoops_RSHA[in];		\
		_hoops_CARCP (_hoops_CSIR, (int)index,					\
					  _hoops_IRRCP[_hoops_CGSHR]);				\
		if (BIT (_hoops_IARCP.options, _hoops_CHRH)) {					\
			RGB &	_hoops_SARCP = _hoops_IRRCP[_hoops_CGSHR];			\
			_hoops_SARCP = HD_Apply_Color_Effects (_hoops_SARCP, _hoops_IARCP);			\
		}														\
		(_hoops_PAGR) = _hoops_CGSHR++;									\
	} while (0)



GLOBAL_FUNCTION _hoops_HHA HD_Downwind_Named_Material (
	Net_Rendition const &			nr,
	_hoops_HHA const &		mat,
	Named_Material const *			_hoops_RGHHP) {
	_hoops_HHA				_hoops_GGHHP = mat;
	int								i;
	UNREFERENCED (nr);

	for (i=0; i<_hoops_CRGRA; i++) {
		if (BIT (_hoops_RGHHP->_hoops_PRGRA, HOOPS_READ_ONLY._hoops_SRGRA[i])) {
			if (mat->color[i].red	!= _hoops_RGHHP->color[i].red ||
				mat->color[i].green != _hoops_RGHHP->color[i].green ||
				mat->color[i].blue	!= _hoops_RGHHP->color[i].blue) {
				_hoops_GGHHP.Modify();
				_hoops_GGHHP->color[i].red	 = _hoops_RGHHP->color[i].red;
				_hoops_GGHHP->color[i].green = _hoops_RGHHP->color[i].green;
				_hoops_GGHHP->color[i].blue	 = _hoops_RGHHP->color[i].blue;
			}
		}
		if (mat->_hoops_CSHR.red != _hoops_RGHHP->_hoops_CSHR.red ||
			mat->_hoops_CSHR.green != _hoops_RGHHP->_hoops_CSHR.green ||
			mat->_hoops_CSHR.blue != _hoops_RGHHP->_hoops_CSHR.blue) {
			_hoops_GGHHP.Modify();
			_hoops_GGHHP->_hoops_CSHR.red		= _hoops_RGHHP->_hoops_CSHR.red;
			_hoops_GGHHP->_hoops_CSHR.green	= _hoops_RGHHP->_hoops_CSHR.green;
			_hoops_GGHHP->_hoops_CSHR.blue	= _hoops_RGHHP->_hoops_CSHR.blue;
		}


		if (BIT (_hoops_RGHHP->_hoops_PRGRA, HOOPS_READ_ONLY._hoops_APGRA[i])) {
			if (mat->texture[i] != _hoops_RGHHP->texture[i]) {
				_hoops_GGHHP.Modify();
				_hoops_GGHHP->texture[i] = _hoops_RGHHP->texture[i];
			}
		}
	}

	if (BIT (_hoops_RGHHP->_hoops_PRGRA, _hoops_SIARA)) {
		if (mat->texture[_hoops_IIA] != _hoops_RGHHP->texture[_hoops_IIA]) {
			_hoops_GGHHP.Modify();
			if (_hoops_GGHHP->texture[_hoops_IIA])
				_hoops_HPRH(_hoops_GGHHP->texture[_hoops_IIA]);
			_hoops_GGHHP->texture[_hoops_IIA] = _hoops_RGHHP->texture[_hoops_IIA];
		}
	}

	if (BIT (_hoops_RGHHP->_hoops_PRGRA, _hoops_GCARA)) {
		if (mat->texture[_hoops_RIA] != _hoops_RGHHP->texture[_hoops_RIA]) {
			_hoops_GGHHP.Modify();
			if (_hoops_GGHHP->texture[_hoops_RIA])
				_hoops_HPRH(_hoops_GGHHP->texture[_hoops_RIA]);
			_hoops_GGHHP->texture[_hoops_RIA] = _hoops_RGHHP->texture[_hoops_RIA];
		}
	}

	if (BIT (_hoops_RGHHP->_hoops_PRGRA, M_TRANSMISSION) && mat->_hoops_IRIR != _hoops_RGHHP->_hoops_IRIR) {
		_hoops_GGHHP.Modify()->_hoops_IRIR = _hoops_RGHHP->_hoops_IRIR;
	}

	if (BIT (_hoops_RGHHP->_hoops_PRGRA, _hoops_RAGRA) && mat->gloss != _hoops_RGHHP->gloss) {
		_hoops_GGHHP.Modify()->gloss = _hoops_RGHHP->gloss;
	}

	if (BIT (_hoops_RGHHP->_hoops_PRGRA, _hoops_AAGRA) && mat->_hoops_PAGRA != _hoops_RGHHP->_hoops_PAGRA) {
		_hoops_GGHHP.Modify()->_hoops_PAGRA = _hoops_RGHHP->_hoops_PAGRA;
	}

	if (_hoops_GGHHP == mat)
		_hoops_GGHHP = null;	// _hoops_IRHC _hoops_PSP _hoops_HPHR _hoops_AGRP
	return _hoops_GGHHP;
}
#else
GLOBAL_FUNCTION _hoops_HHA HD_Downwind_Named_Material (
	Net_Rendition const &		nr,
	_hoops_HHA const &	mat,
	Named_Material const *		_hoops_RGHHP) {
	return null;
}
#endif

/*
 * _hoops_IPCP _hoops_GPRCP _hoops_IIGR _hoops_RGR _hoops_PCPH _hoops_HRGR _hoops_IS _hoops_SPIC _hoops_RH _hoops_HIGR, _hoops_SARGA _hoops_RRPS
 * _hoops_IS _hoops_RH _hoops_RCHP-_hoops_PSPI, _hoops_PPR _hoops_CAHP _hoops_IRS _hoops_CCAH _hoops_HIGR _hoops_CCA _hoops_ASISR
 * _hoops_RSSA, _hoops_PSHA, _hoops_PPR _hoops_GPHA _hoops_ASGA. (_hoops_ASCGR _hoops_RGGHR _hoops_PPR _hoops_ASGA
 * _hoops_GRS _hoops_SAHR _hoops_HGCR _hoops_CGI _hoops_RHIR.)
 */
GLOBAL_FUNCTION void HD_Draw_Indexicated_3D_Polyedge (
	Net_Rendition const &		inr,
	Polyedge const *			_hoops_RASGR) {
#ifndef _hoops_SGRCP
   	Net_Rendition				nr = inr;
	Point const *				points = _hoops_RASGR->points;
	int							_hoops_PHHA = _hoops_RASGR->_hoops_PHHA;
	int const *					lengths = _hoops_RASGR->lengths;
	int const *					_hoops_AIHA = _hoops_RASGR->_hoops_AIHA;
	int const *					_hoops_SPII = _hoops_RASGR->_hoops_SPII;
	int							length;
	_hoops_ACGHR *			_hoops_HCHA = _hoops_RASGR->_hoops_HCHA;
	Vector *					_hoops_ICHA = _hoops_RASGR->_hoops_ICHA;
	_hoops_RSSH alter *			_hoops_CCHA = _hoops_RASGR->_hoops_CCHA;
	int							_hoops_GSHA = _hoops_RASGR->_hoops_GSHA;
	Vector *					_hoops_RSHA = _hoops_RASGR->_hoops_RSHA;
	int							point_count = _hoops_RASGR->point_count;
	int							_hoops_SPHA = _hoops_RASGR->_hoops_SPHA;
	bool						_hoops_PRRCP = _hoops_RASGR->_hoops_RPRCP;
	Point						out_points[_hoops_CGRCP];
	RGB alter					_hoops_HRRCP[_hoops_CGRCP];
	Vector						_hoops_SRRCP[_hoops_CGRCP];
	_hoops_RSSH *					_hoops_GARCP = null;
	int							_hoops_RARCP = 0;
	RGB alter					_hoops_IRRCP[_hoops_CGRCP];
	Vector						_hoops_CRRCP[_hoops_CGRCP];
	int alter *					_hoops_ACI;
	int alter *					_hoops_AARCP;
	int alter *					_hoops_ARRCP;
	int alter *					_hoops_IAIPR;
	int alter *					_hoops_PPGCP;
	_hoops_GRCAR const *			_hoops_ARCAR;
	_hoops_RHAH const *			_hoops_CSIR;
	int							_hoops_APRCP;
	int							offset[2];
	int							_hoops_PARCP[2];
	float						findex[2];
	_hoops_GRCAR					_hoops_PPRCP[2];
	float						_hoops_HPRCP;
	int							_hoops_ASPS;
	int							_hoops_CGSHR;
	int							edge;
	float						_hoops_IPRCP;
	float						_hoops_CPRCP;
	int							a, b;
	_hoops_GACGA		action;
	Net_Rendition alter *		_hoops_SPRCP = null;
	Polyedge *					pe = 0;
	int							prev;
	_hoops_AHAH const &				_hoops_PHAH = nr->_hoops_ARA->_hoops_IHRH;

	DC_Point alter			*_hoops_CGCAR;
	float alter				*ws;
	unsigned char alter		*_hoops_RRCAR;
	int						_hoops_CRCAR;


	/*
	 * _hoops_RAHP _hoops_IGI _hoops_GGR _hoops_RGR _hoops_PCPH, '_hoops_CIHA' _hoops_SHR _hoops_AGCCA _hoops_IS _hoops_IRS _hoops_ACAGR
	 * _hoops_GIAA _hoops_RH _hoops_HAIR _hoops_ARCR, _hoops_PPR '_hoops_SHI' _hoops_SHR _hoops_AGCCA _hoops_IS _hoops_ACAGR
	 * _hoops_GIAA _hoops_GII _hoops_IIGR _hoops_RH _hoops_RIR-_hoops_PPSR _hoops_SIRGR.
	 */

	/*
	 * _hoops_GHRCP _hoops_HRGR _hoops_IIAC _hoops_RHRCP _hoops_HPP _hoops_RH _hoops_AHRCP _hoops_IS _hoops_ASAR-_hoops_RCAS _hoops_RH _hoops_PHPHA
	 * _hoops_SIHC _hoops_HPGR _hoops_CHGC _hoops_IH _hoops_RH *_hoops_GRAA*-_hoops_ASISR _hoops_RSSA _hoops_HII _hoops_ACRI
	 * _hoops_IS _hoops_ACRI, _hoops_PPR _hoops_HPP _hoops_RH _hoops_PHRCP _hoops_IIGR _hoops_RH _hoops_HHRCP-3D _hoops_PCPH
	 * _hoops_CCA _hoops_HHRCP-3D-_hoops_IHRCP.	 _hoops_IPCP _hoops_ARPC _hoops_HRGR _hoops_AICS _hoops_CCA _hoops_HPP
	 * _hoops_RH _hoops_HHRCP'_hoops_GRI _hoops_SHR _hoops_CHRCP '_hoops_HHH' _hoops_IHH _hoops_RSIAR _hoops_GGR _hoops_PAII
	 * _hoops_IRHP _hoops_SIRGR _hoops_IH _hoops_IHHH _hoops_IS _hoops_PPSI _hoops_RH _hoops_IHH _hoops_RSSA.
	 *
	 * _hoops_HHIGR _hoops_HRGR _hoops_SHRCP, _hoops_PHRI, _hoops_IS _hoops_ASSS _hoops_IH _hoops_IHH _hoops_RSIAR _hoops_GGR _hoops_RH
	 * '_hoops_RSSA' _hoops_CRPR _hoops_PGAP _hoops_HRGR _hoops_GACC _hoops_IHGS _hoops_CGI _hoops_GPP _hoops_IS _hoops_RH _hoops_SPS _hoops_PAPA.
	 * _hoops_PS _hoops_HIISR _hoops_CCA _hoops_RGR _hoops_HPP _hoops_GIRCP _hoops_PGCR _hoops_ASRAR: _hoops_RPP _hoops_RH _hoops_SPS _hoops_PAPA _hoops_HRGR _hoops_HHRCP-3D,
	 * _hoops_PSCR _hoops_SR '_hoops_IRAA _hoops_PICP _hoops_IIGR' _hoops_RH _hoops_GHHS _hoops_RH _hoops_CIHH _hoops_CPHR _hoops_PPR _hoops_GSRS
	 * _hoops_IRS '_hoops_HSPH-_hoops_RSSA' _hoops_CRPR _hoops_CCA _hoops_RH _hoops_HAHH _hoops_IHH _hoops_APSAR. _hoops_CGP _hoops_RH
	 * _hoops_SPS _hoops_PAPA _hoops_HRGR _hoops_CPHP _hoops_SHS, _hoops_SR _hoops_SGH _hoops_IRS *_hoops_CCGC _hoops_GIAH
	 * _hoops_HAPR* _hoops_PPR _hoops_ASAR-_hoops_GRGP *_hoops_CPS* _hoops_CRGR _hoops_RISA _hoops_SIRGR _hoops_IH _hoops_PHGSR
	 * _hoops_IGIAR. _hoops_IASHR.
	 */

	if (point_count == 0 || _hoops_SPHA == 0) {
		int				index;
		/* _hoops_SPIC _hoops_HIGR _hoops_IS _hoops_CGIC _hoops_AHPA _hoops_HSH */

		length = _hoops_RASGR->total;
		while (length-- > 0) {
			if ((index = *_hoops_AIHA++) > point_count)
				point_count = index;

			if (_hoops_SPII != null) {
				if ((index = *_hoops_SPII++) > _hoops_SPHA)
					_hoops_SPHA = index;
			}
		}
		_hoops_AIHA = _hoops_RASGR->_hoops_AIHA;
		_hoops_SPII = _hoops_RASGR->_hoops_SPII;

		if (_hoops_SPHA == 0 && _hoops_SPII == null)
			_hoops_SPHA = _hoops_RASGR->total - _hoops_RASGR->_hoops_PHHA;

		/* _hoops_AGRP _hoops_CCAH _hoops_HSH _hoops_HII "_hoops_CIAS _hoops_CIHA" _hoops_IS "_hoops_PHI _hoops_IIGR _hoops_PSPI" */
		if (_hoops_RASGR->point_count == 0)
			((Polyedge alter *)_hoops_RASGR)->point_count = ++point_count;
		if (_hoops_RASGR->_hoops_SPHA == 0)
			((Polyedge alter *)_hoops_RASGR)->_hoops_SPHA = ++_hoops_SPHA;
	}


	action = nr->_hoops_SRA->_hoops_IPCI->draw_3d_polyedge;


	/*
	 * _hoops_PARAR _hoops_RH _hoops_CSCS _hoops_CIHH _hoops_RPGP _hoops_GH _hoops_IS _hoops_ARI (_hoops_HII _hoops_HHRCP-_hoops_PGSA),
	 * _hoops_CR _hoops_SCH _hoops_CHH _hoops_SHH _hoops_AGAPR _hoops_IS _hoops_SRCH _hoops_RH _hoops_ACSP _hoops_IIGR _hoops_RH _hoops_IPHR _hoops_ARI _hoops_RPP _hoops_SSRR.
	 */
	ALLOC_ARRAY_ALIGNED (_hoops_CGCAR, _hoops_RASGR->point_count, DC_Point, 16);
	ALLOC_ARRAY_ALIGNED (ws, _hoops_RASGR->point_count, float, 16);
	ALLOC_ARRAY (_hoops_RRCAR, _hoops_RASGR->point_count, _hoops_GRCAR);
	_hoops_CRCAR = HD_Acquire_Clip_Points (nr,
												_hoops_RASGR->bounding,
												_hoops_RASGR->point_count,
												_hoops_RASGR->points,
												_hoops_CGCAR,
												ws,
												_hoops_RRCAR);

	// _hoops_ASIGA _hoops_IRHH _hoops_RIRCP _hoops_IS _hoops_AIRCP _hoops_PPR _hoops_HASIR
	FREE_ARRAY_ALIGNED (_hoops_CGCAR, _hoops_RASGR->point_count, DC_Point, 16);

	if (_hoops_CRCAR == 0) {
		FREE_ARRAY_ALIGNED (ws, _hoops_RASGR->point_count, float, 16);
		FREE_ARRAY (_hoops_RRCAR, _hoops_RASGR->point_count, _hoops_GRCAR);
		return; /* _hoops_IHRI, _hoops_IIP _hoops_IRIPR */
	}

	_hoops_ARCAR	= _hoops_RRCAR;

	ZALLOC(pe, Polyedge);
	_hoops_ICAI(pe);

	pe->lengths_allocated = _hoops_CGRCP;
	pe->_hoops_IPII = _hoops_CGRCP;
	pe->_hoops_CPII = _hoops_CGRCP;
	pe->bounding = _hoops_RASGR->bounding;

	ALLOC_ARRAY(pe->lengths, pe->lengths_allocated, int);	
	ALLOC_ARRAY(pe->_hoops_AIHA, pe->_hoops_IPII, int);	
	ALLOC_ARRAY(pe->_hoops_SPII, pe->_hoops_CPII, int);

	pe->_hoops_RAHH |= _hoops_AAHH;

	pe->points = out_points;
	pe->_hoops_RSHA = _hoops_RSHA;
	pe->point_count = point_count;
	pe->_hoops_SRHA = DL_SUPPRESS_GEOMETRY_DISPLAY_LISTS | DL_TEMPORARY_DATA;
	pe->_hoops_GSAI = nr->_hoops_IRR->_hoops_CSA & _hoops_RHII;
	pe->_hoops_GSCP = _hoops_RASGR->_hoops_GSCP;
	pe->bounding = _hoops_RASGR->bounding;

	_hoops_CSIR = nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR;
	_hoops_APRCP = _hoops_CSIR->length;

	{
		_hoops_ARGRA			_hoops_PRGRA;

		if (nr->_hoops_RHP->_hoops_CHA->_hoops_ARIR) {
			int i;

			_hoops_HHA alter &	mat = nr.Modify()->_hoops_RHP.Modify()->_hoops_CHA.Modify();

			HI_Free_Diffuse_Channel_List (mat->_hoops_SCA);
			mat->_hoops_SCA = null;
			for (i=0; i<_hoops_GAGRA; i++)
				if (mat->texture[i] != null) {
					_hoops_HPRH(mat->texture[i]);
					mat->texture[i] = null;
				}
			mat->_hoops_ARIR = false;
		}

		_hoops_PRGRA = _hoops_CSIR->_hoops_SRHRA;

		if (!_hoops_PRRCP && ANYBIT (_hoops_PRGRA, ~M_DIFFUSE)) {
			int								remaining;
			Named_Material const *			_hoops_ISHIR;
			Net_Rendition alter *			_hoops_PIRCP;
			_hoops_HHA const &		mat = nr->_hoops_RHP->_hoops_CHA;
			_hoops_HHA				_hoops_RGHHP;

			/* _hoops_RRP _hoops_PCCP _hoops_ICCSR _hoops_IIGR _hoops_SCII'_hoops_GRI _hoops_PPR _hoops_HSRPR _hoops_GRR _hoops_CSCIP _hoops_PPGA */
			ZALLOC_ARRAY (_hoops_SPRCP, _hoops_APRCP, Net_Rendition);
			_hoops_PIRCP = _hoops_SPRCP;
			_hoops_ISHIR = _hoops_CSIR->_hoops_HAA;
			if ((remaining = _hoops_APRCP) > 0) do {
				*_hoops_PIRCP = nr;
				_hoops_RGHHP = HD_Downwind_Named_Material (nr, mat, _hoops_ISHIR);
				if (_hoops_RGHHP != null)
					(*_hoops_PIRCP).Modify()->_hoops_RHP.Modify()->_hoops_CHA = _hoops_RGHHP;

				++_hoops_PIRCP;
				++_hoops_ISHIR;
			} _hoops_RGGA (--remaining == 0);
		}

		/* _hoops_SGH _hoops_GRPAR _hoops_RGAR _hoops_RPP _hoops_SR _hoops_HGCR _hoops_GII _hoops_AI _hoops_HII _hoops_RH _hoops_ARCR */

		if (_hoops_PRRCP || !ANYBIT (_hoops_PRGRA, _hoops_PSARA))
			_hoops_CCHA = null;
	}

	if (_hoops_ICHA != null)
		pe->_hoops_ICHA = _hoops_SRRCP;

	if (_hoops_CCHA != null) {
		_hoops_RARCP = _hoops_GSHA;
		ALLOC_ARRAY(_hoops_GARCP, _hoops_CGRCP*_hoops_RARCP, _hoops_RSSH);
		pe->_hoops_CCHA = _hoops_GARCP;
		pe->_hoops_GSHA = _hoops_RARCP;
	}

	if (_hoops_PRRCP) {
		_hoops_HPRCP = (float)_hoops_APRCP;

		pe->_hoops_PCHA = _hoops_HRRCP;
	}
	else {
		_hoops_HPRCP = 0.5f;

		pe->_hoops_ASHA = _hoops_IRRCP;

		if (_hoops_RSHA != null)
			pe->_hoops_RSHA = _hoops_CRRCP;		/* _hoops_CCAH _hoops_ISHA _hoops_IPGHR */
	}


	/*
	 * _hoops_RAIGR _hoops_PIP _hoops_HII _hoops_HIRCP. _hoops_IIRCP:
	 *
	 * _hoops_IPCP _hoops_RHPC _hoops_CIRCP _hoops_ICRRP _hoops_RH "_hoops_SIRCP _hoops_PPSR"
	 * _hoops_IGIAR _hoops_RH _hoops_GCRCP _hoops_III.  _hoops_HSRR _hoops_PCAI: _hoops_RH _hoops_HPRGR _hoops_IPPHR
	 * _hoops_IIGR _hoops_SIRCP _hoops_SIGH _hoops_IRS _hoops_CIRCP _hoops_IIGR 0.5.	_hoops_RCPA _hoops_GIRR _hoops_GH _hoops_CGPR >=0.6,
	 * _hoops_PPR _hoops_ISHP _hoops_CGPR <0.6, _hoops_ARP _hoops_RH _hoops_CIRCP _hoops_IS 0.6.	_hoops_RCPA _hoops_ACASA,
	 * _hoops_ARP _hoops_RH _hoops_CIRCP _hoops_IS 1.0.
	 *
	 * _hoops_RAHP _hoops_PCCP _hoops_PGCPR _hoops_PPAP _hoops_GIRRR, _hoops_RH _hoops_SAPS _hoops_PSPI _hoops_IIGR _hoops_RH
	 * _hoops_ARGR _hoops_CGGR _hoops_ASRHA _hoops_RCRCP.
	 */
#	define		_hoops_ACRCP					1.0f
#	define		_hoops_PCRCP				(1.0f - _hoops_ACRCP)


	/* _hoops_ASSS _hoops_IH _hoops_RH _hoops_PHI _hoops_IIGR _hoops_RSSA _hoops_PGAP _hoops_SR _hoops_PAH _hoops_GGCR _hoops_ARPP _hoops_SPS _hoops_ISPR */
	_hoops_ARRCP = pe->_hoops_AIHA + _hoops_CGRCP - 2;

	/* _hoops_IIS'_hoops_GRI _hoops_HGCR _hoops_CPIC */
	_hoops_ACI = pe->_hoops_AIHA;
	_hoops_AARCP = pe->_hoops_SPII;
	_hoops_ASPS = 0;
	_hoops_CGSHR = 0;
	_hoops_IAIPR = pe->lengths;
	_hoops_PPGCP = _hoops_ACI;

	edge = -1;
	while (_hoops_PHHA-- > 0) {
		offset[0] = *_hoops_AIHA++;
		_hoops_PARCP[0] = -1;
		findex[0] = _hoops_HCHA[offset[0]] + _hoops_HPRCP;
		_hoops_PPRCP[0]  = _hoops_ARCAR[offset[0]];

		length = *lengths++ - 1;
		if (_hoops_SPII != null)
			_hoops_SPII++;
		_hoops_PCCAR {
			offset[1] = *_hoops_AIHA++;
			_hoops_PARCP[1] = -1;
			findex[1] = _hoops_HCHA[offset[1]] + _hoops_HPRCP;
			_hoops_PPRCP[1]  = _hoops_ARCAR[offset[1]];

			if (_hoops_SPII != null)
				edge = *_hoops_SPII++;
			else
				++edge;

			if (_hoops_ACI >= _hoops_ARRCP) {
				if (_hoops_SPRCP != null)
					_hoops_RRRCP (_hoops_SPRCP[(int)findex[1] % _hoops_APRCP]);
				else
					_hoops_RRRCP (nr);
			}

			if (!nr->_hoops_IRR->_hoops_GAHA &&
				_hoops_PPRCP[1] != _hoops_HCRCP && _hoops_PPRCP[1] == _hoops_PPRCP[0]) {
				/*
				 * _hoops_SACH _hoops_SGGR
				 */
				_hoops_GRRCP();
			}
			else if ((int)findex[0] == (int)findex[1]) {
				/*
				 * _hoops_HCR _hoops_GIAA _hoops_PPR _hoops_PSHR _hoops_SIGRA - _hoops_IPS _hoops_GAR _hoops_HRGR
				 */
				if (_hoops_ACI == _hoops_PPGCP) {		/* _hoops_PSP _hoops_CISI _hoops_CGGR */
					if (_hoops_PARCP[0] == -1) {
						*_hoops_ACI++ = _hoops_PARCP[0] = _hoops_ASPS;
						out_points[_hoops_ASPS] = points[offset[0]];
						if (_hoops_PRRCP)
							_hoops_ICRCP (_hoops_CSIR, findex[0],
										   _hoops_HRRCP[_hoops_ASPS], true, _hoops_PHAH);
						if (_hoops_ICHA != null)
							_hoops_SRRCP[_hoops_ASPS] = _hoops_ICHA[offset[0]];
						if (_hoops_CCHA != null) {
							COPY_PARAMETER (&_hoops_CCHA[offset[0]*_hoops_RARCP], 
									&_hoops_GARCP[_hoops_ASPS*_hoops_RARCP], _hoops_RARCP);
						}
						++_hoops_ASPS;
					}
					else
						*_hoops_ACI++ = _hoops_PARCP[0];
					*_hoops_AARCP++ = 0;
				}

				*_hoops_ACI++ = _hoops_PARCP[1] = prev = _hoops_ASPS;
				out_points[_hoops_ASPS] = points[offset[1]];

				if (_hoops_PRRCP)
					_hoops_ICRCP (_hoops_CSIR, findex[1],
								   _hoops_HRRCP[_hoops_ASPS], true, _hoops_PHAH);
				if (_hoops_ICHA != null)
					_hoops_SRRCP[_hoops_ASPS] = _hoops_ICHA[offset[1]];
				if (_hoops_CCHA != null) {
					COPY_PARAMETER (&_hoops_CCHA[offset[1]*_hoops_RARCP], 
							&_hoops_GARCP[_hoops_ASPS*_hoops_RARCP], _hoops_RARCP);
				}
				++_hoops_ASPS;

				if (_hoops_PRRCP)
					*_hoops_AARCP++ = edge;
				else
					_hoops_HARCP (edge, findex[0], *_hoops_AARCP++, _hoops_PHAH);
			}
			else {
				int		_hoops_CCRCP;

				/*
				 * _hoops_HCR _hoops_GIAA, _hoops_HIH _hoops_HAGH _hoops_AHRI - _hoops_PIHA _hoops_SARGA
				 */

				/* _hoops_GHIS _hoops_HPP _hoops_SIGRA */
				if (findex[0] <= findex[1]) {
					a = 0;
					b = 1;
				}
				else {
					a = 1;
					b = 0;

					/*
					 * _hoops_RPP _hoops_SR _hoops_ASAR-_hoops_GRHC _hoops_RGR _hoops_CAGH,
					 * _hoops_PSCR _hoops_SR _hoops_PAH'_hoops_RA _hoops_SAS _hoops_RH _hoops_PGHC _hoops_HIGR
					 */
					if (_hoops_ACI != _hoops_PPGCP) {
						_hoops_GRRCP();

						if (_hoops_SPRCP != null)
							_hoops_RRRCP (_hoops_SPRCP[(int)findex[0] % _hoops_APRCP]);
					}
				}

				/* _hoops_HSPP _hoops_GH _hoops_IRS _hoops_SCRCP _hoops_RPP _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_GGHP _hoops_SPR */
				if (_hoops_ACI == _hoops_PPGCP) {
					if (_hoops_PARCP[a] == -1) {
						*_hoops_ACI++ = _hoops_PARCP[a] = _hoops_ASPS;
						out_points[_hoops_ASPS] = points[offset[a]];
						if (_hoops_PRRCP)
							_hoops_ICRCP (_hoops_CSIR, findex[a],
										   _hoops_HRRCP[_hoops_ASPS], true, _hoops_PHAH);
						if (_hoops_ICHA != null)
							_hoops_SRRCP[_hoops_ASPS] = _hoops_ICHA[offset[a]];
						if (_hoops_CCHA != null)
							COPY_PARAMETER (&_hoops_CCHA[offset[a]*_hoops_RARCP], 
									&_hoops_GARCP[_hoops_ASPS*_hoops_RARCP], _hoops_RARCP);
						++_hoops_ASPS;
					}
					else
						*_hoops_ACI++ = _hoops_PARCP[a];
					*_hoops_AARCP++ = 0;
				}

				_hoops_IPRCP = findex[b] - findex[a];
				_hoops_CPRCP = (float)(int)(findex[a] + _hoops_PCRCP) + _hoops_ACRCP;

				/* _hoops_SPS _hoops_ISHA _hoops_IS _hoops_PGSA */
				_hoops_CCRCP = (int)findex[a];

				/* _hoops_PGGC _hoops_CCAH _hoops_RSSA */
				do {
					float			_hoops_GSRCP;

					_hoops_GSRCP = (_hoops_CPRCP - findex[a]) / _hoops_IPRCP;

					_hoops_RSRCP (points[offset[a]],
									   points[offset[b]],
									   _hoops_GSRCP,
									   out_points[_hoops_ASPS]);
					if (_hoops_PRRCP)
						_hoops_ICRCP (_hoops_CSIR, _hoops_CPRCP,
									   _hoops_HRRCP[_hoops_ASPS], true, _hoops_PHAH);
					if (_hoops_ICHA != null)
						_hoops_ASRCP (_hoops_ICHA[offset[a]],
											_hoops_ICHA[offset[b]],
											_hoops_GSRCP,
											_hoops_SRRCP[_hoops_ASPS]);
					if (_hoops_CCHA != null)
						_hoops_GGRGA (nr,
											&_hoops_CCHA[offset[a]*_hoops_RARCP],
											&_hoops_CCHA[offset[b]*_hoops_RARCP],
											_hoops_GSRCP,
											&_hoops_GARCP[_hoops_ASPS*_hoops_RARCP],
											ws[offset[b]] / ws[offset[a]],
											_hoops_RARCP);

					*_hoops_ACI++ = prev = _hoops_ASPS++;

					if (_hoops_PRRCP)
						*_hoops_AARCP++ = edge;
					else {
						_hoops_HARCP (edge, _hoops_CCRCP, *_hoops_AARCP++, _hoops_PHAH);

						if (_hoops_SPRCP != null) {
							Polyedge *_hoops_PSRCP=pe;

							_hoops_RRRCP (_hoops_SPRCP[_hoops_CCRCP % _hoops_APRCP]);

							pe->points[0] = _hoops_PSRCP->points[prev]; 
							if (_hoops_ICHA != null)						
								pe->_hoops_ICHA[0] = _hoops_PSRCP->_hoops_ICHA[prev]; 
							if (_hoops_CCHA != null)						
								COPY_PARAMETER (&_hoops_PSRCP->_hoops_CCHA[prev*_hoops_RARCP], 
										&pe->_hoops_CCHA[0], _hoops_RARCP); 
							if (_hoops_PRRCP)										
								pe->_hoops_PCHA[0] = _hoops_PSRCP->_hoops_PCHA[prev]; 

							_hoops_ASPS = 1;
							*_hoops_ACI++ = 0;
							*_hoops_AARCP++ = 0;
						}
					}

					_hoops_CCRCP = (int)_hoops_CPRCP;

					_hoops_CPRCP += 1.0f;

					if (_hoops_ACI >= _hoops_ARRCP) {
						Polyedge *_hoops_PSRCP=pe;

						if (_hoops_SPRCP != null)
							_hoops_RRRCP (_hoops_SPRCP[_hoops_CCRCP % _hoops_APRCP]);
						else
							_hoops_RRRCP (nr);

						/* _hoops_IPS _hoops_RH _hoops_CISI _hoops_AH */
						pe->points[0] = _hoops_PSRCP->points[prev]; 
						if (_hoops_ICHA != null)						
							pe->_hoops_ICHA[0] = _hoops_PSRCP->_hoops_ICHA[prev]; 
						if (_hoops_CCHA != null)						
							COPY_PARAMETER (&_hoops_PSRCP->_hoops_CCHA[prev*_hoops_RARCP], 
									&pe->_hoops_CCHA[0], _hoops_RARCP); 
						if (_hoops_PRRCP)										
							pe->_hoops_PCHA[0] = _hoops_PSRCP->_hoops_PCHA[prev]; 

						_hoops_ASPS = 1;
						*_hoops_ACI++ = prev = 0;
						*_hoops_AARCP++ = 0;
					}
				} while (_hoops_CPRCP < findex[b]);

				/* _hoops_PGSA _hoops_RH _hoops_HACH _hoops_GSAS _hoops_ISHA */
				if (_hoops_PARCP[b] == -1) {
					*_hoops_ACI++ = _hoops_PARCP[b] = _hoops_ASPS;
					out_points[_hoops_ASPS] = points[offset[b]];
					if (_hoops_PRRCP)
						_hoops_ICRCP (_hoops_CSIR, findex[b],
									   _hoops_HRRCP[_hoops_ASPS], true, _hoops_PHAH);
					if (_hoops_ICHA != null)
						_hoops_SRRCP[_hoops_ASPS] = _hoops_ICHA[offset[b]];
					if (_hoops_CCHA != null)
						COPY_PARAMETER (&_hoops_CCHA[offset[b]*_hoops_RARCP], 
								&_hoops_GARCP[_hoops_ASPS*_hoops_RARCP], _hoops_RARCP);
					++_hoops_ASPS;
				}
				else
					*_hoops_ACI++ = _hoops_PARCP[b];

				if (_hoops_PRRCP)
					*_hoops_AARCP++ = edge;
				else {
					_hoops_HARCP (edge, _hoops_CCRCP, *_hoops_AARCP++, _hoops_PHAH);

					if (_hoops_SPRCP != null)
						_hoops_RRRCP (_hoops_SPRCP[_hoops_CCRCP % _hoops_APRCP]);
				}

				/*
				 * _hoops_RPP _hoops_SR _hoops_ASAR-_hoops_GRSHR _hoops_RGR _hoops_CAGH,
				 * _hoops_PSCR _hoops_SR _hoops_PAH'_hoops_RA _hoops_SAS _hoops_RGR _hoops_HIGR
				 */
				if (a != 0)
					_hoops_GRRCP();
			}

			if (--length <= 0) {
				_hoops_GRRCP();
				break;
			}

			/*
			 * _hoops_CIA _hoops_IGIAR
			 */
			offset[0] = offset[1];
			_hoops_PARCP[0] = _hoops_PARCP[1];
			findex[0] = findex[1];
			_hoops_PPRCP[0]  = _hoops_PPRCP[1];
		}

		if (_hoops_ACI > pe->_hoops_AIHA) {
			if (_hoops_SPRCP != null)
				_hoops_RRRCP (_hoops_SPRCP[(int)findex[1] % _hoops_APRCP]);
			else
				_hoops_RRRCP (nr);
		}
	}

  _hoops_HPAGR:
	if (_hoops_GARCP) 
		FREE_ARRAY (_hoops_GARCP, _hoops_CGRCP*_hoops_RARCP, _hoops_RSSH);

	if (pe && _hoops_ISAI (pe) == 0)			
		HI_Free_Polyedge(pe);

	FREE_ARRAY_ALIGNED (ws, _hoops_RASGR->point_count, float, 16);
	FREE_ARRAY (_hoops_RRCAR, _hoops_RASGR->point_count, _hoops_GRCAR);

	if (_hoops_SPRCP != null) {
		int								remaining = _hoops_APRCP;
		Net_Rendition alter *			_hoops_PIRCP = _hoops_SPRCP;

		do {
			(*_hoops_PIRCP).release();
			++_hoops_PIRCP;
		} _hoops_RGGA (--remaining == 0);

		FREE_ARRAY (_hoops_SPRCP, _hoops_APRCP, Net_Rendition);
	}
#endif
}

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
 * $Id: obf_tmp.txt 1.141 2011-01-22 06:23:53 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hd_proto.h"
#include "phdraw.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "hpserror.h"


#define _hoops_HGHPR (1<<16)

struct _hoops_IGHPR {
	_hoops_IGHPR				*_hoops_CGHPR,
								*_hoops_SGHPR,
								*up;
	_hoops_IGHPR				*_hoops_GRHPR;

	int							_hoops_RRHPR; /* _hoops_RH _hoops_PHI _hoops_IIGR _hoops_IRS _hoops_GPHA */

	/*
	 * _hoops_PS _hoops_ARHPR _hoops_HII _hoops_PRHPR _hoops_GGR 1 _hoops_PAR 2 _hoops_SSGAR.
	 * _hoops_HRHPR _hoops_RAIGR _hoops_SHR _hoops_ICGI _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_GPHA _hoops_PPR _hoops_SPR _hoops_ISHA _hoops_CIHA.
	 * _hoops_HRHPR _hoops_IHAC _hoops_GHCA _hoops_SHH _hoops_RHPA.
	 *
	 * _hoops_IPCP _hoops_RAIGR _hoops_HIGR _hoops_HRGR _hoops_GGR _hoops_RH _hoops_AGR _hoops_IAS-_hoops_HPPC-_hoops_IAS-_hoops_HPPC-_hoops_IAS-_hoops_HPPC, _hoops_AGIRR _hoops_RH _hoops_IHAC _hoops_HIGR _hoops_HRGR
	 * _hoops_GGR _hoops_RH _hoops_AGR _hoops_HPPC-_hoops_IAS-_hoops_HPPC-_hoops_IAS-_hoops_HPPC-_hoops_IAS.  _hoops_HGI _hoops_IRHPR _hoops_CRHPR _hoops_RH _hoops_CSPC _hoops_GGR
	 * _hoops_SRHPR _hoops_GAHPR _hoops_RCAC.
	 */
	int							*_hoops_RAHPR,
								*_hoops_AAHPR,
								_hoops_PAHPR,
								_hoops_HAHPR;

	_hoops_IAHPR		_hoops_PPGI; /* _hoops_CGHI _hoops_PGGA _hoops_GAAP _hoops_PISC */
};


#define _hoops_CAHPR(_hoops_SAHPR, _hoops_GPHPR) do {			\
		if (BIT ((_hoops_SAHPR), _hoops_RPHPR))		\
			(_hoops_GPHPR) |= _hoops_APHPR;					\
		else if (BIT ((_hoops_SAHPR), _hoops_PPHPR))	\
			(_hoops_GPHPR) |= _hoops_HPHPR;					\
		else															\
			(_hoops_GPHPR) |= _hoops_IPHPR;					\
	} while (0)


local void _hoops_CPHPR (
	Shell				*_hoops_SPHPR) {
	_hoops_GHHPR		*_hoops_GPHPR;
	Local_Vertex_Flags	*_hoops_SAHPR;
	_hoops_RHHPR	*edge;
	_hoops_RHHPR	**_hoops_AHHPR;
	int						_hoops_PHHPR;
	int						remaining;

	if (_hoops_SPHPR->_hoops_SPHA < 0)
		HI_Create_Shell_Edges (_hoops_SPHPR, false);

	_hoops_AHHPR		 = _hoops_SPHPR->_hoops_HHHPR;
	_hoops_GPHPR	 = &_hoops_SPHPR->_hoops_IHHPR.flags[0];
	_hoops_SAHPR = _hoops_SPHPR->local_vertex_attributes._hoops_CHHPR();

	_hoops_PHHPR = 0;
	remaining = _hoops_SPHPR->point_count;

	 _hoops_RGGA (--remaining == 0) {
		if ((edge = *_hoops_AHHPR++) != null) {
			if (edge != *_hoops_AHHPR) do {
				*_hoops_GPHPR &= ~_hoops_SHHPR;
				_hoops_CAHPR (*_hoops_SPHPR->local_vertex_attributes._hoops_CHHPR(_hoops_PHHPR), *_hoops_GPHPR);
				_hoops_CAHPR (*_hoops_SPHPR->local_vertex_attributes._hoops_CHHPR(edge->_hoops_GIHPR), *_hoops_GPHPR);
				++_hoops_GPHPR;
			} _hoops_RGGA (++edge == *_hoops_AHHPR);

			++_hoops_PHHPR;
		}
	}
}



local void _hoops_RIHPR (
	_hoops_AIHPR					*_hoops_PIHPR) {
	_hoops_GHHPR		*_hoops_GPHPR;
	Local_Vertex_Flags	*_hoops_SAHPR;
	int						_hoops_HIHPR = _hoops_PIHPR->columns;
	int						_hoops_IIHPR = _hoops_HIHPR - 1;
	int						_hoops_CIHPR;
	int						_hoops_SIHPR;
	int						_hoops_GCHPR;
	Local_Vertex_Attributes *_hoops_SPRI;

	_hoops_SPRI = &_hoops_PIHPR->local_vertex_attributes;
	_hoops_GPHPR	 = &_hoops_PIHPR->_hoops_IHHPR.flags[0];
	_hoops_SAHPR = _hoops_PIHPR->local_vertex_attributes._hoops_CHHPR(0);

	_hoops_GCHPR = 0;

	_hoops_SIHPR = _hoops_PIHPR->rows;
	_hoops_RGGA (_hoops_SIHPR-- == 1) {
		if ((_hoops_CIHPR = _hoops_HIHPR) > 1) {
			*_hoops_GPHPR &= ~_hoops_SHHPR;
			_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + 0), *_hoops_GPHPR);
			_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + 1), *_hoops_GPHPR);
			++_hoops_GPHPR;

			*_hoops_GPHPR &= ~_hoops_SHHPR;
			_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + 0), *_hoops_GPHPR);
			_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + _hoops_HIHPR), *_hoops_GPHPR);
			++_hoops_GPHPR;

			*_hoops_GPHPR &= ~_hoops_SHHPR;
			++_hoops_GPHPR;

			++_hoops_GCHPR;

			--_hoops_CIHPR;
		}

		_hoops_RGGA (_hoops_CIHPR-- == 1) {
			*_hoops_GPHPR &= ~_hoops_SHHPR;
			_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + 0), *_hoops_GPHPR);
			_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + 1), *_hoops_GPHPR);
			++_hoops_GPHPR;

			*_hoops_GPHPR &= ~_hoops_SHHPR;
			_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + 0), *_hoops_GPHPR);
			_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + _hoops_HIHPR), *_hoops_GPHPR);
			++_hoops_GPHPR;

			*_hoops_GPHPR &= ~_hoops_SHHPR;
			_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + 0), *_hoops_GPHPR);
			_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + _hoops_IIHPR), *_hoops_GPHPR);
			++_hoops_GPHPR;

			++_hoops_GCHPR;
		}

		*_hoops_GPHPR &= ~_hoops_SHHPR;
		++_hoops_GPHPR;

		*_hoops_GPHPR &= ~_hoops_SHHPR;
		_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + 0), *_hoops_GPHPR);
		_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + _hoops_HIHPR), *_hoops_GPHPR);
		++_hoops_GPHPR;

		*_hoops_GPHPR &= ~_hoops_SHHPR;
		_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + 0), *_hoops_GPHPR);
		_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + _hoops_IIHPR), *_hoops_GPHPR);
		++_hoops_GPHPR;

		++_hoops_GCHPR;
	}

	_hoops_CIHPR = _hoops_HIHPR;
	_hoops_RGGA (_hoops_CIHPR-- == 1) {
		*_hoops_GPHPR &= ~_hoops_SHHPR;
		_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + 0), *_hoops_GPHPR);
		_hoops_CAHPR (*_hoops_SPRI->_hoops_CHHPR(_hoops_GCHPR + 1), *_hoops_GPHPR);
		++_hoops_GPHPR;

		*_hoops_GPHPR++ &= ~_hoops_SHHPR;
		*_hoops_GPHPR++ &= ~_hoops_SHHPR;

		++_hoops_GCHPR;
	}

	*_hoops_GPHPR++ &= ~_hoops_SHHPR;
	*_hoops_GPHPR++ &= ~_hoops_SHHPR;
	*_hoops_GPHPR++ &= ~_hoops_SHHPR;
}



/*
 * _hoops_IPCP "_hoops_RHCP" _hoops_SGI _hoops_IIGR _hoops_PCCP _hoops_ISHA _hoops_IRHC _hoops_RSH _hoops_AHPH _hoops_HAGH _hoops_APSA
 * _hoops_PISRR _hoops_CHR _hoops_IGI _hoops_HPP _hoops_SGS _hoops_ISHA'_hoops_GRI _hoops_GIHA. _hoops_RCHPR _hoops_CHR _hoops_IGI _hoops_IS _hoops_ACHPR
 * _hoops_GH _hoops_RH _hoops_RHPP _hoops_ASCA _hoops_RRGR.
 */
local void _hoops_PCHPR (
	Polyhedron			*_hoops_IPRI) {
	_hoops_GHHPR		*_hoops_HCHPR, *_hoops_ICHPR;

	if (_hoops_IPRI->_hoops_IHHPR.flags == null) {
		if (_hoops_IPRI->local_vertex_attributes._hoops_CCHPR == 0 &&
			_hoops_IPRI->local_vertex_attributes._hoops_SCHPR == 0)
			return;
		else
			HI_Initialize_Edge_Attributes (_hoops_IPRI, false);
	}

	if (_hoops_IPRI->local_vertex_attributes._hoops_CCHPR ==
		_hoops_IPRI->point_count) {
		_hoops_HCHPR = _hoops_IPRI->_hoops_IHHPR.flags;
		_hoops_ICHPR = _hoops_HCHPR + _hoops_IPRI->_hoops_SPHA;
		do {
			*_hoops_HCHPR &= ~_hoops_SHHPR;
			*_hoops_HCHPR |= _hoops_APHPR;
		} _hoops_RGGA (++_hoops_HCHPR == _hoops_ICHPR);
	}
	else if (_hoops_IPRI->local_vertex_attributes._hoops_SCHPR ==
			 _hoops_IPRI->point_count) {
		_hoops_HCHPR = _hoops_IPRI->_hoops_IHHPR.flags;
		_hoops_ICHPR = _hoops_HCHPR + _hoops_IPRI->_hoops_SPHA;
		do {
			*_hoops_HCHPR &= ~_hoops_SHHPR;
			*_hoops_HCHPR |= _hoops_HPHPR;
		} _hoops_RGGA (++_hoops_HCHPR == _hoops_ICHPR);
	}
	else if (_hoops_IPRI->local_vertex_attributes._hoops_CCHPR == 0 &&
			 _hoops_IPRI->local_vertex_attributes._hoops_SCHPR == 0) {
		_hoops_HCHPR = _hoops_IPRI->_hoops_IHHPR.flags;
		_hoops_ICHPR = _hoops_HCHPR + _hoops_IPRI->_hoops_SPHA;
		do {
			*_hoops_HCHPR &= ~_hoops_SHHPR;
			*_hoops_HCHPR |= _hoops_IPHPR;
		} _hoops_RGGA (++_hoops_HCHPR == _hoops_ICHPR);
	}
	else { /* _hoops_SR _hoops_HS _hoops_IS _hoops_RHCA */
		if (_hoops_IPRI->type == _hoops_SCIP)
			_hoops_CPHPR ((Shell *)_hoops_IPRI);
		else /* _hoops_GSHPR */
			_hoops_RIHPR ((_hoops_AIHPR *)_hoops_IPRI);
	}

	_hoops_IPRI->_hoops_RSHPR |= _hoops_SHHPR;
}



/*
 * _hoops_ASHPR _hoops_RGR _hoops_CCAH _hoops_IRHP-_hoops_ACRI _hoops_HPP _hoops_IGRI _hoops_PIRA
 * _hoops_CRGR _hoops_IRS _hoops_PSHPR _hoops_HHIS. _hoops_IPCP _hoops_CARA _hoops_HRGR _hoops_IS _hoops_SHH _hoops_SHSS _hoops_IS
 * _hoops_SSS _hoops_RH _hoops_HSHPR-_hoops_IGRI _hoops_ACRI _hoops_ISHPR
 * _hoops_SPHR.
 */
local void _hoops_CSHPR (
	_hoops_IGHPR			*_hoops_HAPAR,
	_hoops_IGHPR			**_hoops_SSHPR) {
	_hoops_IGHPR			*node;

	if (_hoops_HAPAR->_hoops_PAHPR > 0)
		_hoops_GGIPR (_hoops_HAPAR->_hoops_RAHPR, 2*_hoops_HAPAR->_hoops_PAHPR, int, _hoops_HAPAR->_hoops_RAHPR);
	if (_hoops_HAPAR->_hoops_HAHPR > 0)
		_hoops_GGIPR (_hoops_HAPAR->_hoops_AAHPR, 2*_hoops_HAPAR->_hoops_HAHPR, int, _hoops_HAPAR->_hoops_AAHPR);

	_hoops_HAPAR->_hoops_CGHPR = null;
	_hoops_HAPAR->_hoops_SGHPR = null;

	if ((node = *_hoops_SSHPR) == null) {		/* _hoops_RH _hoops_SRS _hoops_SPR */
		*_hoops_SSHPR = _hoops_HAPAR;
		_hoops_HAPAR->_hoops_GRHPR = null;
		_hoops_HAPAR->up = null;
	}
	else _hoops_PCCAR {
		if (_hoops_HPGI (_hoops_HAPAR->_hoops_PPGI, node->_hoops_PPGI,  ~0)) {
			_hoops_HAPAR->up = node->up;
			_hoops_HAPAR->_hoops_GRHPR = node->_hoops_GRHPR;
			node->_hoops_GRHPR = _hoops_HAPAR;
			return;
		}
#ifndef _hoops_RGIPR
		else if (_hoops_AGIPR (_hoops_HAPAR->_hoops_PPGI, node->_hoops_PPGI)) {
			if (node->_hoops_CGHPR != null) node = node->_hoops_CGHPR;
			else {
				/* _hoops_PPSI _hoops_GGSR _hoops_IRS _hoops_CCAH '_hoops_CRGP' _hoops_RIIS */

				/*
				 * _hoops_IPCP _hoops_CCAH _hoops_GIIS _hoops_SHR _hoops_IAGA _hoops_GGSR _hoops_GAR _hoops_RH _hoops_RIIS, _hoops_HRII _hoops_HSAR
				 * _hoops_RH _hoops_RHGS _hoops_GIIS "_hoops_PGIPR" _hoops_HGIPR _hoops_ISHP _hoops_RRGI _hoops_SCH. _hoops_HGI _hoops_IGIPR
				 * _hoops_SGS _hoops_ISHA _hoops_IGRI _hoops_PSHPR _hoops_HSH _hoops_PPPPR'_hoops_RA _hoops_CGIPR-_hoops_SGIPR _hoops_SHH
				 * _hoops_GRIPR _hoops_RRIPR.
				 */
				node->_hoops_CGHPR = _hoops_HAPAR;
				_hoops_HAPAR->up = node;
				_hoops_HAPAR->_hoops_GRHPR = null;
				return;
			}
		}
		else {
			if (node->_hoops_SGHPR != null) node = node->_hoops_SGHPR;
			else {
				/* _hoops_PPSI _hoops_GGSR _hoops_IRS _hoops_CCAH '_hoops_RRPAR' _hoops_RIIS */

				node->_hoops_SGHPR = _hoops_HAPAR;
				_hoops_HAPAR->up = node;
				_hoops_HAPAR->_hoops_GRHPR = null;
				return;
			}
		}
#endif
	}
}





/*
 * _hoops_IGPP (_hoops_PPR _hoops_HASC) "_hoops_IRHP" _hoops_AHHA _hoops_IS _hoops_ARPR _hoops_HPHR _hoops_ARIPR
 */
local void _hoops_PRIPR (
	_hoops_IGHPR *			_hoops_HAPAR,
	Polyhedron *			_hoops_IPRI) 
{
	_hoops_IGHPR *			_hoops_HRIPR;

	if (_hoops_HAPAR == null) return;		/* _hoops_IIP _hoops_IRIPR */

	/*
	 * _hoops_IPCP _hoops_CRIPR _hoops_HAPR _hoops_ARI _hoops_SRIPR _hoops_ARR _hoops_IH _hoops_GRR _hoops_ARP _hoops_IIGR
	 * _hoops_HAGH-_hoops_AIRC _hoops_SARGR _hoops_AHHA.
	 */
	do {
		Polyedge *			pe;
		_hoops_IGHPR *		_hoops_GAIPR;

		/* _hoops_SSS _hoops_IRS _hoops_RIIS */
		_hoops_PCCAR {
			if (_hoops_HAPAR->_hoops_CGHPR != null) _hoops_HAPAR = _hoops_HAPAR->_hoops_CGHPR;
			else if (_hoops_HAPAR->_hoops_SGHPR != null) _hoops_HAPAR = _hoops_HAPAR->_hoops_SGHPR;
			else break;
		}

		/* _hoops_RAIPR _hoops_RGR _hoops_RIIS _hoops_HII _hoops_RH _hoops_HHIS */
		if ((_hoops_HRIPR = _hoops_HAPAR->up) != null) {
			if (_hoops_HRIPR->_hoops_CGHPR == _hoops_HAPAR)
				_hoops_HRIPR->_hoops_CGHPR = null;
			else if (_hoops_HRIPR->_hoops_SGHPR == _hoops_HAPAR)
				_hoops_HRIPR->_hoops_SGHPR = null;
		}

		_hoops_GAIPR = _hoops_HAPAR;


		ZALLOC (pe, Polyedge);
		_hoops_ICAI(pe);
		pe->next = _hoops_IPRI->_hoops_SHGPR;
		_hoops_IPRI->_hoops_SHGPR = pe;
		_hoops_AAIPR (_hoops_HAPAR->_hoops_PPGI, pe->_hoops_PPGI);
		pe->same_colors = _hoops_PAIPR;

		/* _hoops_RPR _hoops_GH _hoops_RH _hoops_PHI _hoops_IIGR _hoops_IIRGR */
		{
			int		_hoops_PHHA = 0;
			int		total = 0;

			do {
				int		_hoops_HAIPR = _hoops_HAPAR->_hoops_PAHPR + _hoops_HAPAR->_hoops_HAHPR + 1;

				if (total > 0 && total + _hoops_HAIPR > _hoops_HGHPR)
					break;
				total += _hoops_HAIPR;

				++_hoops_PHHA;
			} while ((_hoops_HAPAR = _hoops_HAPAR->_hoops_GRHPR) != null);
			pe->_hoops_PHHA = _hoops_PHHA;
		}
		_hoops_HAPAR = _hoops_GAIPR;

		ALLOC_ARRAY (pe->lengths, pe->_hoops_PHHA, int);
		pe->lengths_allocated = pe->_hoops_PHHA;

		/* _hoops_HGCR _hoops_RH _hoops_IHHA _hoops_PPR _hoops_APSR _hoops_SPCC */
		{
			int		total = 0;
			int *	_hoops_IAIPR = pe->lengths;

			/*
			 * (1 _hoops_CAIPR _hoops_IH _hoops_GRR _hoops_RCHAR _hoops_GPHA;
			 *	2 _hoops_CAIPR _hoops_IH _hoops_RH _hoops_PGCR _hoops_APHR _hoops_GIHA)
			 */
			do {
				int		_hoops_HAIPR = _hoops_HAPAR->_hoops_PAHPR + _hoops_HAPAR->_hoops_HAHPR + 1;

				if (total > 0 && total + _hoops_HAIPR > _hoops_HGHPR)
					break;
				total += _hoops_HAIPR;

				*_hoops_IAIPR++ = _hoops_HAIPR;
			} while ((_hoops_HAPAR = _hoops_HAPAR->_hoops_GRHPR) != null);
			pe->total = total;
		}
		_hoops_HAPAR = _hoops_GAIPR;

		_hoops_GAIPR = _hoops_HAPAR->up;	// _hoops_GGR _hoops_AGIR _hoops_IIGR _hoops_SPCC _hoops_SAIPR

		ALLOC_ARRAY (pe->_hoops_AIHA, pe->total, int);
		ALLOC_ARRAY (pe->_hoops_SPII, pe->total, int);
		pe->_hoops_IPII = pe->_hoops_CPII = pe->total;

		pe->_hoops_RAHH |= _hoops_AAHH;


		/* _hoops_GPIPR _hoops_RH _hoops_HPHR _hoops_ACRI _hoops_HA. _hoops_HIAA. */
		{
			int				total = 0;
			int *			_hoops_RPIPR = pe->_hoops_AIHA;
			int *			_hoops_APIPR = pe->_hoops_SPII;
			_hoops_IGHPR *	next;

			do {
				int			_hoops_HAIPR = _hoops_HAPAR->_hoops_PAHPR + _hoops_HAPAR->_hoops_HAHPR + 1;

				if (total > 0 && total + _hoops_HAIPR > _hoops_HGHPR)
					break;
				total += _hoops_HAIPR;

				int *		in;
				int *		_hoops_PPIPR;

				/*
				 * _hoops_IGPP _hoops_HPIPR _hoops_HII _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_IPIPR _hoops_RAIGR
				 * _hoops_CPIPR _hoops_SGS _hoops_IPIPR _hoops_RAIGR _hoops_IAGA (_hoops_IAS-_hoops_HPPC-_hoops_IAS-_hoops_HPPC-_hoops_IAS-_hoops_HPPC)
				 */
				_hoops_PPIPR = _hoops_HAPAR->_hoops_RAHPR;
				in	   = _hoops_PPIPR + 2 * _hoops_HAPAR->_hoops_PAHPR;

				*_hoops_RPIPR++ = *--in;	/* _hoops_HGCR _hoops_IRS _hoops_GPHA */
				in -= 2;
				*_hoops_APIPR++ = 0;
				/* _hoops_SPIPR: _hoops_GGSR - _hoops_HIGR _hoops_HRGR _hoops_PISC */
				_hoops_RGGA (in < _hoops_PPIPR) {
					*_hoops_RPIPR++ = *in++; /* _hoops_GPHA */
					*_hoops_APIPR++ = *in++; /* _hoops_ISHA */
					in -= 4;
				}

				/* _hoops_SPIPR: _hoops_GGSR - _hoops_HIGR _hoops_HRGR _hoops_PISC */

				/*
				 * _hoops_SPIPR: "_hoops_GGR" _hoops_HA _hoops_RSSA *_hoops_GHIPR* _hoops_RHIPR.
				 * _hoops_AHIPR _hoops_HRGR, _hoops_SCH _hoops_RSSA _hoops_IS _hoops_RH _hoops_GRAA-_hoops_PHIPR _hoops_HHIPR
				 * _hoops_ARPP _hoops_RH _hoops_SRS _hoops_ISHA _hoops_CIHA.
				 */

				/*
				 * _hoops_IGPP _hoops_RH "_hoops_PRHPR"
				 */
				*_hoops_RPIPR++ = _hoops_HAPAR->_hoops_RRHPR;
				*_hoops_APIPR++ = *++in; /* _hoops_ISHA _hoops_CIHA _hoops_HII _hoops_IPIPR _hoops_RAIGR */

				/* _hoops_SPIPR: _hoops_GGSR - _hoops_HIGR _hoops_HRGR _hoops_PISC */

				/*
				 * _hoops_IGPP _hoops_IPIPR _hoops_IHAC _hoops_CPIC _hoops_IHIPR
				 * _hoops_CPIPR _hoops_SGS _hoops_IPIPR _hoops_IHAC _hoops_IAGA (_hoops_HPPC-_hoops_IAS-_hoops_HPPC-_hoops_IAS-_hoops_HPPC-_hoops_IAS)
				 */
				in	   = _hoops_HAPAR->_hoops_AAHPR;
				_hoops_PPIPR = in + 2 * _hoops_HAPAR->_hoops_HAHPR;
				_hoops_RGGA (in == _hoops_PPIPR) {
					*_hoops_RPIPR++ = *in++;
					*_hoops_APIPR++ = *in++;
				}

				/* _hoops_SPIPR: _hoops_GGSR - _hoops_HIGR _hoops_HRGR _hoops_PISC */

				next = _hoops_HAPAR->_hoops_GRHPR;

				if (_hoops_HAPAR->_hoops_PAHPR > 0)
					FREE_ARRAY (_hoops_HAPAR->_hoops_RAHPR, 2*_hoops_HAPAR->_hoops_PAHPR, int);
				if (_hoops_HAPAR->_hoops_HAHPR > 0)
					FREE_ARRAY (_hoops_HAPAR->_hoops_AAHPR, 2*_hoops_HAPAR->_hoops_HAHPR, int);
				FREE (_hoops_HAPAR, _hoops_IGHPR);
			} while ((_hoops_HAPAR = next) != null);

			if (_hoops_HAPAR != null) {			// _hoops_HAR _hoops_CPHR _hoops_CCA _hoops_RGR _hoops_SSAI _hoops_GAPR
				_hoops_HRIPR = _hoops_HAPAR;	// _hoops_HIS _hoops_HS _hoops_CRIPR _hoops_HAPR _hoops_APHS _hoops_SCH
				_hoops_HAPAR->up = _hoops_GAIPR;
			}
		}
	} while ((_hoops_HAPAR = _hoops_HRIPR) != null);
}




local void _hoops_CHIPR (
	Polyhedron			*_hoops_IPRI,
	float					_hoops_SHIPR) {
	_hoops_GHHPR		*_hoops_GPHPR;
	_hoops_GIIPR		*_hoops_RIIPR;
	_hoops_ARPA const			*normals;
	int						_hoops_AIIPR = _hoops_PIIPR;
	int						_hoops_HIIPR = _hoops_PIIPR;
	int						_hoops_SHPC;
	float					limit;
	float					_hoops_HCIS;

	if (!BIT (_hoops_IPRI->polyhedron_flags, PHF_FACE_NORMALS_VALID))
		HI_Assemble_Face_Normals ((Polyhedron alter *)_hoops_IPRI);

	normals = _hoops_IPRI->local_face_attributes.normals;

	if (_hoops_IPRI->_hoops_IHHPR.flags == null)
		HI_Initialize_Edge_Attributes (_hoops_IPRI, false);
	else {
		int				count;

		/* _hoops_IIIPR _hoops_AHHR _hoops_GGSR _hoops_HCR _hoops_RH _hoops_SIH */
		_hoops_GPHPR = _hoops_IPRI->_hoops_IHHPR.flags;
		count = _hoops_IPRI->_hoops_SPHA;
		while ((count -= 4) >= 0) {
			_hoops_GPHPR[0] &= ~_hoops_CIIPR;
			_hoops_GPHPR[1] &= ~_hoops_CIIPR;
			_hoops_GPHPR[2] &= ~_hoops_CIIPR;
			_hoops_GPHPR[3] &= ~_hoops_CIIPR;
			_hoops_GPHPR += 4;
		}
		switch (count) {
			case -1:	_hoops_GPHPR[2] &= ~_hoops_CIIPR; /* (_hoops_HSSC _hoops_RHIR) */
			case -2:	_hoops_GPHPR[1] &= ~_hoops_CIIPR; /* (_hoops_HSSC _hoops_RHIR) */
			case -3:	_hoops_GPHPR[0] &= ~_hoops_CIIPR;
		}
	}

	if (_hoops_IPRI->local_face_attributes._hoops_SIIPR == _hoops_IPRI->face_count) {
		// _hoops_IHIS _hoops_IGIAR, _hoops_ISAP _hoops_IS _hoops_CACH _hoops_ARI
		return;
	}


	_hoops_IPRI->_hoops_GCIPR = _hoops_SHIPR;
	HI_SinCos (180.0f-_hoops_SHIPR, &_hoops_HCIS, &limit);


	_hoops_GPHPR = _hoops_IPRI->_hoops_IHHPR.flags;
  
	

	/* _hoops_RCIPR _hoops_AA _hoops_SCH _hoops_RH _hoops_ACIPR _hoops_PPRRR. */


	if (_hoops_IPRI->local_face_attributes._hoops_SIIPR == 0)
		_hoops_RIIPR = null; /* (_hoops_PSP _hoops_HSP _hoops_AIRC _hoops_GHGC _hoops_PCIPR _hoops_AHCA) */
	else
		_hoops_RIIPR = _hoops_IPRI->local_face_attributes._hoops_CHHPR();	// _hoops_PIHA _hoops_SHH _hoops_PCCP _hoops_CRPR

#		define	_hoops_HCIPR(_hoops_ICIPR,_hoops_CCIPR)	  (_hoops_ICIPR.a*_hoops_CCIPR.a + _hoops_ICIPR.b*_hoops_CCIPR.b + _hoops_ICIPR.c*_hoops_CCIPR.c)

#		define	_hoops_SCIPR(_hoops_AIIPR, _hoops_HIIPR, normals, _hoops_IPPGR, limit) \
		 /* _hoops_PGSA _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_PCCP _hoops_CRIPR _hoops_PAR _hoops_GSIPR-_hoops_SGH _hoops_ISHA */						\
		(_hoops_HIIPR >= 0 &&															\
		 /* _hoops_PPR _hoops_RSIPR _hoops_HSP _hoops_HRGR _hoops_ARHAR (_hoops_AHCI _hoops_GSSR) */						\
		 (normals[_hoops_AIIPR].a != 0.0f || normals[_hoops_AIIPR].b != 0.0f || normals[_hoops_AIIPR].c != 0.0f) &&	\
		 (normals[_hoops_HIIPR].a != 0.0f || normals[_hoops_HIIPR].b != 0.0f || normals[_hoops_HIIPR].c != 0.0f) &&	\
		 /* _hoops_PPR _hoops_RH _hoops_RCSA _hoops_GAPA _hoops_RH _hoops_RSSI _hoops_HRGR <= 135 _hoops_ASIPR */				\
		 _hoops_HCIPR (normals[_hoops_AIIPR], normals[_hoops_HIIPR]) <= limit &&						\
		 /* _hoops_PPR _hoops_RSIPR _hoops_HSP _hoops_HRGR _hoops_GRGA _hoops_PSIPR */							\
		 (_hoops_IPPGR == null ||													\
		  !BIT (_hoops_IPPGR[_hoops_AIIPR]|_hoops_IPPGR[_hoops_HIIPR], _hoops_HSIPR)))


	if (_hoops_IPRI->type == _hoops_GSIP) {
		_hoops_AIHPR const *		_hoops_PIHPR = (_hoops_AIHPR const *)_hoops_IPRI;
		int					columns;
		int					_hoops_ISIPR;
		int					_hoops_CSIPR;
		int					_hoops_SSIPR;
		int					_hoops_ISPI;
		int					row;
		int					col;
		int					inc;
			

		columns = _hoops_PIHPR->columns;
		_hoops_ISIPR = columns - 1;
		_hoops_CSIPR = _hoops_PIHPR->rows - 1;

		_hoops_SSIPR = 2*_hoops_ISIPR;
		
		for (_hoops_ISPI =0; _hoops_ISPI < _hoops_IPRI->point_count; _hoops_ISPI++) {
			for (inc = 0; inc < 3; inc++) {
				_hoops_SHPC = 3 * _hoops_ISPI + inc;

				row = _hoops_ISPI / columns;
				col = _hoops_ISPI - row * columns;

				if (inc == 0) { /* _hoops_ISHA _hoops_GGCPR _hoops_HII _hoops_PPSR */
					if (col == _hoops_ISIPR ||		/* _hoops_CCAS */
						row == 0 ||				/* _hoops_IGIAR _hoops_PRPC _hoops_ISHA */
						row == _hoops_CSIPR)			/* _hoops_IGIAR _hoops_SCIA _hoops_ISHA */
						_hoops_HIIPR = _hoops_PIIPR;
					else {
						_hoops_AIIPR = 2*col + row*_hoops_SSIPR;		/* _hoops_AAPA _hoops_HSP */
						_hoops_HIIPR = _hoops_AIIPR - _hoops_SSIPR + 1;		/* _hoops_GSSC _hoops_HSP */
					}
				}
				else if (inc == 1) { /* _hoops_ISHA _hoops_RGCPR _hoops_AGCPR _hoops_HII _hoops_PPSR */
					if (row == _hoops_CSIPR ||		/* _hoops_CCAS */
						col == 0 ||				/* _hoops_IGIAR _hoops_RAAP _hoops_ISHA */
						col == _hoops_ISIPR)		/* _hoops_IGIAR _hoops_RPHR _hoops_ISHA */
						_hoops_HIIPR = _hoops_PIIPR;
					else {
						_hoops_AIIPR = 2*col + row*_hoops_SSIPR;		/* _hoops_RPHR _hoops_HSP */
						_hoops_HIIPR = _hoops_AIIPR - 1;						/* _hoops_RAAP _hoops_HSP */
					}
				}
				else {	/* _hoops_ISHA _hoops_GH _hoops_PPR _hoops_IS _hoops_RH _hoops_RAAP _hoops_HII _hoops_PPSR */
					if (col == 0 || row == _hoops_CSIPR)		/* _hoops_CCAS */
						_hoops_HIIPR = _hoops_PIIPR;
					else {
						_hoops_AIIPR = 2*col + row*_hoops_SSIPR - 1;	/* _hoops_AAPA-_hoops_RPHR */
						_hoops_HIIPR = _hoops_AIIPR - 1;						/* _hoops_GSSC-_hoops_RAAP */
					}
				}

			/* _hoops_HCIC _hoops_SCH _hoops_PGCPR? */

				if (_hoops_SCIPR (_hoops_AIIPR, _hoops_HIIPR, normals, _hoops_RIIPR, limit)) {
					/* _hoops_PGSA _hoops_SCH */
						_hoops_GPHPR[_hoops_SHPC] ^= _hoops_CIIPR;
				}
			}
		}
	}

	else { /* _hoops_HGCPR */
		Shell alter *			_hoops_SPHPR = (Shell alter *)_hoops_IPRI;
		/* _hoops_IPCP _hoops_HSPR _hoops_IGCPR _hoops_CHR "_hoops_GGR _hoops_AGR" */
		_hoops_CGCPR const		*_hoops_SGCPR;

		if (_hoops_SPHPR->_hoops_SGCPR == null ||
			_hoops_SPHPR->_hoops_GRCPR == null || _hoops_IPRI->_hoops_SPHA < 0) {
			/* (_hoops_ASAR)_hoops_ARPR _hoops_RRCPR _hoops_SPPR _hoops_IS _hoops_GCIS _hoops_ISCP _hoops_IHH _hoops_IAS-_hoops_IS-_hoops_RCHP _hoops_SIHC */
			if (_hoops_SPHPR->_hoops_GRCPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_GRCPR, _hoops_SPHPR->_hoops_SPHA, _hoops_RHHPR);
				_hoops_SPHPR->_hoops_GRCPR = null;
			}

			if (_hoops_SPHPR->_hoops_HHHPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_HHHPR, _hoops_SPHPR->point_count + 1, _hoops_RHHPR const *);
				_hoops_SPHPR->_hoops_HHHPR = null;
			}

			if (_hoops_SPHPR->_hoops_SGCPR != null) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_SGCPR, _hoops_SPHPR->_hoops_SPHA, _hoops_CGCPR);
				_hoops_SPHPR->_hoops_SGCPR = null;
			}

			HI_Create_Shell_Edges (_hoops_SPHPR, true);
		}

		/* _hoops_IPCP _hoops_HSPR _hoops_IGIPR _hoops_SGS _hoops_GISA-_hoops_ARCPR-_hoops_PRCPR _hoops_SSCP _hoops_RPII _hoops_ASAS */

		_hoops_SGCPR	 = _hoops_SPHPR->_hoops_SGCPR;

		for (_hoops_SHPC = 0; _hoops_SHPC < _hoops_IPRI->_hoops_SPHA; _hoops_SHPC++) {
				_hoops_AIIPR = _hoops_SGCPR[_hoops_SHPC]._hoops_AIIPR;
				_hoops_HIIPR = _hoops_SGCPR[_hoops_SHPC]._hoops_HIIPR;
		
				/* _hoops_HCIC _hoops_SCH _hoops_PGCPR? */		
				if (_hoops_SCIPR (_hoops_AIIPR, _hoops_HIIPR, normals, _hoops_RIIPR, limit)) 
						/* _hoops_PGSA _hoops_SCH */
						_hoops_GPHPR[_hoops_SHPC] ^= _hoops_CIIPR;
		}
	}
}





local void _hoops_HRCPR (
	int						p1,
	int						p2,
	Shell *				_hoops_SPHPR,
	_hoops_GHHPR		flag,
	bool				_hoops_IRCPR) {
	_hoops_GHHPR		*_hoops_GPHPR;
	_hoops_RHHPR	**_hoops_HHHPR;
	_hoops_RHHPR	*_hoops_CRCPR;
	_hoops_RHHPR	*_hoops_SRCPR;

	if (p1 == p2) return;

	if(_hoops_SPHPR->_hoops_HHHPR == null)
		HI_Create_Shell_Edges (_hoops_SPHPR, true);

	_hoops_GPHPR	   = _hoops_SPHPR->_hoops_IHHPR.flags;
	_hoops_HHHPR = _hoops_SPHPR->_hoops_HHHPR;
	_hoops_CRCPR	   = _hoops_SPHPR->_hoops_GRCPR;

	if (p1 > p2) {
		int tmp = p2;
		p2 = p1;
		p1 = tmp;
	}

	/* _hoops_GACPR _hoops_ISHA _hoops_IAGA _hoops_HII 1 _hoops_IS 2 */
	_hoops_SRCPR = _hoops_HHHPR[p1];
	while (_hoops_SRCPR != _hoops_HHHPR[p1+1]) {
		if (_hoops_SRCPR->_hoops_GIHPR == p2)
			break;
		++_hoops_SRCPR;
	}

	/* _hoops_AA _hoops_SCH! */
	if (_hoops_IRCPR)
		_hoops_GPHPR[_hoops_SRCPR - _hoops_CRCPR] ^= flag;
	else
		_hoops_GPHPR[_hoops_SRCPR - _hoops_CRCPR] |= flag;
}


local void _hoops_RACPR (
	Polyhedron			*_hoops_IPRI) {
	_hoops_GHHPR		*_hoops_GPHPR;
	_hoops_GIIPR		*_hoops_RIIPR;

	if (_hoops_IPRI->_hoops_IHHPR.flags == null)
		HI_Initialize_Edge_Attributes (_hoops_IPRI, false);
	else {
		int				count;

		/* _hoops_IIIPR _hoops_AHHR _hoops_GGSR _hoops_HCR _hoops_RH _hoops_SIH */
		_hoops_GPHPR = _hoops_IPRI->_hoops_IHHPR.flags;
		count = _hoops_IPRI->_hoops_SPHA;
		while ((count -= 4) >= 0) {
			_hoops_GPHPR[0] &= ~_hoops_AACPR;
			_hoops_GPHPR[1] &= ~_hoops_AACPR;
			_hoops_GPHPR[2] &= ~_hoops_AACPR;
			_hoops_GPHPR[3] &= ~_hoops_AACPR;
			_hoops_GPHPR += 4;
		}
		switch (count) {
			case -1:	_hoops_GPHPR[2] &= ~_hoops_AACPR; /* (_hoops_HSSC _hoops_RHIR) */
			case -2:	_hoops_GPHPR[1] &= ~_hoops_AACPR; /* (_hoops_HSSC _hoops_RHIR) */
			case -3:	_hoops_GPHPR[0] &= ~_hoops_AACPR;
		}
	}

	if (ALLBITS (_hoops_IPRI->polyhedron_flags, _hoops_PACPR|_hoops_HACPR) ||
		_hoops_IPRI->local_face_attributes._hoops_SIIPR == _hoops_IPRI->face_count) {
		/*
		 * _hoops_IACPR _hoops_RSH _hoops_PPCAR _hoops_SCH _hoops_HRGR _hoops_SGS _hoops_SR _hoops_ACPA _hoops_SCH'_hoops_GRI _hoops_CAHC _hoops_PAR "_hoops_AAIA
		 * _hoops_IGS", _hoops_HIH _hoops_RPP _hoops_SCH _hoops_HRGR _hoops_PSCR _hoops_SCH'_hoops_GRI _hoops_HPHR _hoops_PIHGR!
		 */
		return;
	}

	/* _hoops_RCIPR _hoops_AA _hoops_SCH _hoops_RH _hoops_ACIPR _hoops_PPRRR. */

	/*
	 * _hoops_CACPR _hoops_ISHA _hoops_HRGR _hoops_PAPR _hoops_HRGR _hoops_IHGS _hoops_GPP _hoops_RH _hoops_SACPR _hoops_CHGRR _hoops_SCH _hoops_SSCP
	 * _hoops_GPCPR _hoops_SPR _hoops_HISS _hoops_HSP, _hoops_HAR _hoops_RPCPR _hoops_GRGA _hoops_PSIPR
	 * _hoops_RSSI.
	 */

	if (_hoops_IPRI->local_face_attributes._hoops_SIIPR == 0)
		_hoops_RIIPR = null; /* (_hoops_PSP _hoops_HSP _hoops_AIRC _hoops_GHGC _hoops_PCIPR _hoops_AHCA) */
	else
		_hoops_RIIPR = _hoops_IPRI->local_face_attributes._hoops_CHHPR();	// _hoops_PIHA _hoops_SHH _hoops_PCCP _hoops_CRPR

	if (_hoops_IPRI->type == _hoops_GSIP) {
		_hoops_AIHPR const *			_hoops_PIHPR = (_hoops_AIHPR const *)_hoops_IPRI;
		/* _hoops_IPCP _hoops_HSPR _hoops_IGCPR _hoops_CHR "_hoops_GGR _hoops_AGR" */
		int						_hoops_APCPR;
		int						_hoops_PPCPR;
		int						_hoops_HPCPR;
		int						_hoops_IPCPR;

		/* _hoops_PPSI _hoops_AGCR _hoops_CGSI _hoops_CRGR _hoops_CPCPR (_hoops_HPGR _hoops_CHGC _hoops_HPPR _hoops_IS) */
		_hoops_PPCPR = 3*_hoops_PIHPR->columns;
		_hoops_IPCPR = _hoops_PIHPR->columns - 1;
		_hoops_HPCPR = _hoops_PIHPR->rows - 1;

		/* _hoops_IPCA _hoops_HSP _hoops_HPP _hoops_HSP */
		_hoops_GPHPR = _hoops_IPRI->_hoops_IHHPR.flags;
		_hoops_APCPR = _hoops_IPCPR;
		if (_hoops_RIIPR == null) {
			/*
			 * _hoops_IPCP _hoops_HSPR _hoops_SPCPR _hoops_PSAP _hoops_RH _hoops_GHCPR _hoops_SPPR (_hoops_RHCPR)
			 * _hoops_IRS _hoops_AHCPR, _hoops_HIH "_hoops_SCH _hoops_RHAP _hoops_SCH _hoops_PHCPR".
			 */
			_hoops_PCCAR {
				_hoops_GPHPR[0] ^= _hoops_AACPR;
				_hoops_GPHPR[1] ^= _hoops_AACPR;
				_hoops_GPHPR[4] ^= _hoops_AACPR;
				_hoops_GPHPR[_hoops_PPCPR] ^= _hoops_AACPR;
				_hoops_GPHPR += 3;
				if (--_hoops_APCPR == 0) {
					if (--_hoops_HPCPR == 0) break;
					_hoops_APCPR = _hoops_IPCPR;
					_hoops_GPHPR += 3;
				}
			}
		}
		else _hoops_PCCAR {
			/* _hoops_RAH _hoops_RH _hoops_IHIR _hoops_HHCPR */

			if (!BIT (_hoops_RIIPR[0], _hoops_HSIPR)) {
				_hoops_GPHPR[0] ^= _hoops_AACPR;
				_hoops_GPHPR[1] ^= _hoops_AACPR;
				_hoops_GPHPR[5] ^= _hoops_AACPR;
			}
			if (!BIT (_hoops_RIIPR[1], _hoops_HSIPR)) {
				_hoops_GPHPR[4] ^= _hoops_AACPR;
				_hoops_GPHPR[5] ^= _hoops_AACPR;
				_hoops_GPHPR[_hoops_PPCPR] ^= _hoops_AACPR;
			}
			_hoops_GPHPR += 3;
			_hoops_RIIPR += 2;
			if (--_hoops_APCPR == 0) {
				if (--_hoops_HPCPR == 0) break;
				_hoops_APCPR = _hoops_IPCPR;
				_hoops_GPHPR += 3;
			}
		}
	}
	else { /* _hoops_HGCPR */
		/*
		 * _hoops_HSRR _hoops_GRR _hoops_SIGC _hoops_HSP, _hoops_PH _hoops_RH _hoops_SACPR _hoops_RIP _hoops_GPP _hoops_GRR _hoops_ISHA.
		 * _hoops_PS _hoops_HHS _hoops_SGH _hoops_RH _hoops_CCGI _hoops_IH _hoops_RGR, _hoops_RPP _hoops_SSIA _hoops_IHCPR,
		 * _hoops_PAR _hoops_SR _hoops_HHS _hoops_SGH _hoops_RH _hoops_CHCPR _hoops_SGI, _hoops_RPP _hoops_SSIA _hoops_IHCPR.
		 * _hoops_SHCPR _hoops_RSIPR _hoops_HRGR _hoops_GICPR _hoops_PPR _hoops_RSIPR _hoops_HRGR _hoops_PAHH
		 * _hoops_GHGC _hoops_RICPR _hoops_SAHR _hoops_IH _hoops_RGR. _hoops_PHGP _hoops_SR _hoops_AA _hoops_RH _hoops_SIA _hoops_HII _hoops_SI.
		 */

		Shell *				_hoops_SPHPR = (Shell *)_hoops_IPRI;	 
		int					_hoops_AICPR = 0;
		int					_hoops_PICPR;
		int					*_hoops_ASPH;
		int					*_hoops_HICPR;
		int					_hoops_IICPR;
		int					*_hoops_CICPR;

		_hoops_ASPH	  = _hoops_SPHPR->face_list;
		_hoops_HICPR = _hoops_ASPH + _hoops_SPHPR->face_list_length;

		if (_hoops_ASPH == null) {
			/* _hoops_HPCAR _hoops_RGAR _hoops_HIPH, _hoops_SPIC _hoops_RH _hoops_CCGI */
			Tristrip const *		ts;

			if ((ts = _hoops_SPHPR->tristrips) != null) do {
				int						_hoops_PHHA = ts->_hoops_PHHA;
				int const *				lengths = ts->lengths;
				int const *				vi = ts->_hoops_AIHA;
				int const *				fi = ts->face_indices;
				int						face = -1;

				while (_hoops_PHHA-- > 0) {
					bool			_hoops_SICPR = false;
					int				length = *lengths++;
					int				p1 = *vi++;
					int				p2 = *vi++;
					int				_hoops_IAPH;

					if (length < 0) {
						length = -length;
						_hoops_SICPR = true;
					}
					length -= 2;

					while (length-- > 0) {
						_hoops_IAPH = *vi++;
						if (fi)
							face = *fi++;
						else
							face++;

						_hoops_GIIPR	_hoops_GCCPR = 0;
						
						if (_hoops_RIIPR != null)
							_hoops_GCCPR = *_hoops_IPRI->local_face_attributes._hoops_CHHPR(face);

						if (!BIT (_hoops_GCCPR, _hoops_HSIPR)) {
							_hoops_HRCPR (p1, p2, _hoops_SPHPR, _hoops_AACPR, true);
							_hoops_HRCPR (p1, _hoops_IAPH, _hoops_SPHPR, _hoops_AACPR, true);
							_hoops_HRCPR (p2, _hoops_IAPH, _hoops_SPHPR, _hoops_AACPR, true);
						}

						if (!_hoops_SICPR)
							p1 = p2;
						p2 = _hoops_IAPH;
					}
				}
			} while ((ts = ts->next) != null);
		}
		else do {
			int		length = *_hoops_ASPH++;

			if (length < 0) {			// _hoops_RCCPR _hoops_GGR _hoops_RH _hoops_PGHC (_hoops_SIGC) _hoops_HSP
				_hoops_CICPR = _hoops_ASPH - length;
			}
			else {						// _hoops_GSSR _hoops_CCAH _hoops_HSP
				_hoops_CICPR = _hoops_ASPH + length;
				if (_hoops_RIIPR != null) {
					if (BIT (*_hoops_RIIPR++, _hoops_HSIPR)) {
						// _hoops_ACCPR _hoops_GPP _hoops_ISGR _hoops_RH _hoops_SPPR _hoops_IIGR _hoops_RGR _hoops_HSP
						_hoops_ASPH = _hoops_CICPR;
						_hoops_RGGA (_hoops_ASPH == _hoops_HICPR || *_hoops_ASPH >= 0)	// _hoops_PPR _hoops_GII _hoops_PCCPR _hoops_GGR _hoops_SCH
							_hoops_ASPH += 1 - *_hoops_ASPH;
						continue;
					}
				}
			}

			if (_hoops_ASPH != _hoops_CICPR) {
				_hoops_PICPR = _hoops_IICPR = *_hoops_ASPH++;

				_hoops_PCCAR {
					if (_hoops_ASPH != _hoops_CICPR) {
						/* _hoops_GSSR _hoops_AGIR; _hoops_HGCR _hoops_SPS _hoops_GPHA */
						_hoops_AICPR = *_hoops_ASPH++;
					}
					else {
						/*
						 * _hoops_ARGAR _hoops_SCH _hoops_AARI _hoops_IS _hoops_RH _hoops_RSGI (_hoops_HCCPR
						 * _hoops_SR _hoops_PAR _hoops_RH _hoops_IPSP _hoops_AIAH _hoops_HS!)
						 */
						if (_hoops_AICPR == _hoops_IICPR) break;
						_hoops_AICPR = _hoops_IICPR;
					}

					_hoops_HRCPR (_hoops_PICPR, _hoops_AICPR, _hoops_SPHPR, _hoops_AACPR, true);

					if (length == 2)	// _hoops_ARHAR
						break;

					_hoops_PICPR = _hoops_AICPR; /* _hoops_HAPR _hoops_IS _hoops_SCIA */
				}
			}
		} _hoops_RGGA (_hoops_ASPH == _hoops_HICPR);
	}
}



local void _hoops_ICCPR (
	Polyhedron			*_hoops_IPRI) {
	_hoops_GHHPR		*_hoops_GPHPR;
	_hoops_GIIPR		*_hoops_RIIPR;

	if (_hoops_IPRI->_hoops_IHHPR.flags == null)
		HI_Initialize_Edge_Attributes (_hoops_IPRI, false);
	else {
		int				count;

		/* _hoops_IIIPR _hoops_AHHR _hoops_GGSR _hoops_HCR _hoops_RH _hoops_SIH */
		_hoops_GPHPR = _hoops_IPRI->_hoops_IHHPR.flags;
		count = _hoops_IPRI->_hoops_SPHA;
		while ((count -= 4) >= 0) {
			_hoops_GPHPR[0] &= ~_hoops_CCCPR;
			_hoops_GPHPR[1] &= ~_hoops_CCCPR;
			_hoops_GPHPR[2] &= ~_hoops_CCCPR;
			_hoops_GPHPR[3] &= ~_hoops_CCCPR;
			_hoops_GPHPR += 4;
		}
		switch (count) {
			case -1:	_hoops_GPHPR[2] &= ~_hoops_CCCPR; /* (_hoops_HSSC _hoops_RHIR) */
			case -2:	_hoops_GPHPR[1] &= ~_hoops_CCCPR; /* (_hoops_HSSC _hoops_RHIR) */
			case -3:	_hoops_GPHPR[0] &= ~_hoops_CCCPR;
		}
	}

	if (_hoops_IPRI->local_face_attributes._hoops_SIIPR == _hoops_IPRI->face_count) {
		// _hoops_PSP _hoops_RSSI _hoops_AGSR _hoops_PSP _hoops_SCCPR _hoops_SPPR
		return;
	}


	/*
	 * _hoops_CACPR _hoops_ISHA _hoops_HRGR _hoops_PAPR _hoops_HRGR _hoops_IHGS '_hoops_SCCPR' _hoops_RPP _hoops_SCH _hoops_SSCP _hoops_GII
	 * _hoops_SIGC _hoops_HISS _hoops_HSP,
	 */

	if (_hoops_IPRI->local_face_attributes._hoops_SIIPR == 0)
		_hoops_RIIPR = null; /* (_hoops_PSP _hoops_HSP _hoops_AIRC _hoops_GHGC _hoops_PCIPR _hoops_AHCA) */
	else
		_hoops_RIIPR = _hoops_IPRI->local_face_attributes._hoops_CHHPR();	// _hoops_PIHA _hoops_SHH _hoops_PCCP _hoops_CRPR

	if (_hoops_IPRI->type == _hoops_GSIP) {
		_hoops_AIHPR const *			_hoops_PIHPR = (_hoops_AIHPR const *)_hoops_IPRI;
		int						_hoops_APCPR;
		int						_hoops_PPCPR;
		int						_hoops_HPCPR;
		int						_hoops_IPCPR;

		/* _hoops_PPSI _hoops_AGCR _hoops_CGSI _hoops_CRGR _hoops_CPCPR (_hoops_HPGR _hoops_CHGC _hoops_HPPR _hoops_IS) */
		_hoops_PPCPR = 3*_hoops_PIHPR->columns;
		_hoops_IPCPR = _hoops_PIHPR->columns - 1;
		_hoops_HPCPR = _hoops_PIHPR->rows - 1;

		/* _hoops_IPCA _hoops_HSP _hoops_HPP _hoops_HSP */
		_hoops_GPHPR = _hoops_IPRI->_hoops_IHHPR.flags;
		_hoops_APCPR = _hoops_IPCPR;
		if (_hoops_RIIPR == null) {
			/*
			 * _hoops_IPCP _hoops_HSPR _hoops_SPCPR _hoops_PSAP _hoops_RH _hoops_GHCPR _hoops_SPPR (_hoops_RHCPR)
			 * _hoops_IRS _hoops_AHCPR, _hoops_HIH "_hoops_SCH _hoops_RHAP _hoops_SCH _hoops_PHCPR".
			 */
			_hoops_PCCAR {
				_hoops_GPHPR[0] |= _hoops_CCCPR;
				_hoops_GPHPR[1] |= _hoops_CCCPR;
				_hoops_GPHPR[4] |= _hoops_CCCPR;
				_hoops_GPHPR[_hoops_PPCPR] |= _hoops_CCCPR;
				_hoops_GPHPR += 3;
				if (--_hoops_APCPR == 0) {
					if (--_hoops_HPCPR == 0) break;
					_hoops_APCPR = _hoops_IPCPR;
					_hoops_GPHPR += 3;
				}
			}
		}
		else _hoops_PCCAR {
			/* _hoops_RAH _hoops_RH _hoops_IHIR _hoops_HHCPR */

			if (!BIT (_hoops_RIIPR[0], _hoops_HSIPR)) {
				_hoops_GPHPR[0] |= _hoops_CCCPR;
				_hoops_GPHPR[1] |= _hoops_CCCPR;
				_hoops_GPHPR[5] |= _hoops_CCCPR;
			}
			if (!BIT (_hoops_RIIPR[1], _hoops_HSIPR)) {
				_hoops_GPHPR[4] |= _hoops_CCCPR;
				_hoops_GPHPR[5] |= _hoops_CCCPR;
				_hoops_GPHPR[_hoops_PPCPR] |= _hoops_CCCPR;
			}
			_hoops_GPHPR += 3;
			_hoops_RIIPR += 2;
			if (--_hoops_APCPR == 0) {
				if (--_hoops_HPCPR == 0) break;
				_hoops_APCPR = _hoops_IPCPR;
				_hoops_GPHPR += 3;
			}
		}
	}
	else { /* _hoops_HGCPR */
		/*
		 * _hoops_HSRR _hoops_GRR _hoops_SIGC _hoops_HSP, _hoops_PH _hoops_RH _hoops_SACPR _hoops_RIP _hoops_GPP _hoops_GRR _hoops_ISHA.
		 * _hoops_PS _hoops_HHS _hoops_SGH _hoops_RH _hoops_CCGI _hoops_IH _hoops_RGR, _hoops_RPP _hoops_SSIA _hoops_IHCPR,
		 * _hoops_PAR _hoops_SR _hoops_HHS _hoops_SGH _hoops_RH _hoops_CHCPR _hoops_SGI, _hoops_RPP _hoops_SSIA _hoops_IHCPR.
		 * _hoops_SHCPR _hoops_RSIPR _hoops_HRGR _hoops_GICPR _hoops_PPR _hoops_RSIPR _hoops_HRGR _hoops_PAHH
		 * _hoops_GHGC _hoops_RICPR _hoops_SAHR _hoops_IH _hoops_RGR. _hoops_PHGP _hoops_SR _hoops_AA _hoops_RH _hoops_SIA _hoops_HII _hoops_SI.
		 */

		Shell alter *		_hoops_SPHPR = (Shell alter *)_hoops_IPRI;	 
		int					_hoops_AICPR = 0;
		int					_hoops_PICPR;
		int					*_hoops_ASPH;
		int					*_hoops_HICPR;
		int					_hoops_IICPR;
		int					*_hoops_CICPR;

		_hoops_ASPH	  = _hoops_SPHPR->face_list;
		_hoops_HICPR = _hoops_ASPH + _hoops_SPHPR->face_list_length;

		if (_hoops_ASPH == null) {
			/* _hoops_HPCAR _hoops_RGAR _hoops_HIPH, _hoops_SPIC _hoops_RH _hoops_CCGI */
			Tristrip const *		ts;

			if ((ts = _hoops_SPHPR->tristrips) != null) do {
				int						_hoops_PHHA = ts->_hoops_PHHA;
				int const *				lengths = ts->lengths;
				int const *				vi = ts->_hoops_AIHA;
				int const *				fi = ts->face_indices;
				int						face = -1;

				while (_hoops_PHHA-- > 0) {
					bool			_hoops_SICPR = false;
					int				length = *lengths++;
					int				p1 = *vi++;
					int				p2 = *vi++;
					int				_hoops_IAPH;

					if (length < 0) {
						length = -length;
						_hoops_SICPR = true;
					}
					length -= 2;

					while (length-- > 0) {
						_hoops_IAPH = *vi++;
						if (fi)
							face = *fi++;
						else
							face++;

						_hoops_GIIPR	_hoops_GCCPR = 0;
						
						if (_hoops_RIIPR != null)
							_hoops_GCCPR = *_hoops_IPRI->local_face_attributes._hoops_CHHPR(face);

						if (!BIT (_hoops_GCCPR, _hoops_HSIPR)) {
							_hoops_HRCPR (p1, p2, _hoops_SPHPR, _hoops_CCCPR, false);
							_hoops_HRCPR (p1, _hoops_IAPH, _hoops_SPHPR, _hoops_CCCPR, false);
							_hoops_HRCPR (p2, _hoops_IAPH, _hoops_SPHPR, _hoops_CCCPR, false);
						}

						if (!_hoops_SICPR)
							p1 = p2;
						p2 = _hoops_IAPH;
					}
				}
			} while ((ts = ts->next) != null);
		}
		else do {
			if (*_hoops_ASPH++ < 0) {			// _hoops_RCCPR _hoops_GGR _hoops_RH _hoops_PGHC (_hoops_SIGC) _hoops_HSP
				_hoops_CICPR = _hoops_ASPH - _hoops_ASPH[-1];
			}
			else {						// _hoops_GSSR _hoops_CCAH _hoops_HSP
				_hoops_CICPR = _hoops_ASPH + _hoops_ASPH[-1];
				if (_hoops_RIIPR != null) {
					if (BIT (*_hoops_RIIPR++, _hoops_HSIPR)) {
						// _hoops_ACCPR _hoops_GPP _hoops_ISGR _hoops_RH _hoops_SPPR _hoops_IIGR _hoops_RGR _hoops_HSP
						_hoops_ASPH = _hoops_CICPR;
						_hoops_RGGA (_hoops_ASPH == _hoops_HICPR || *_hoops_ASPH >= 0)	// _hoops_PPR _hoops_GII _hoops_PCCPR _hoops_GGR _hoops_SCH
							_hoops_ASPH += 1 - *_hoops_ASPH;
						continue;
					}
				}
			}

			if (_hoops_ASPH != _hoops_CICPR) {
				_hoops_PICPR = _hoops_IICPR = *_hoops_ASPH++;

				_hoops_PCCAR {
					if (_hoops_ASPH != _hoops_CICPR) {
						/* _hoops_GSSR _hoops_AGIR; _hoops_HGCR _hoops_SPS _hoops_GPHA */
						_hoops_AICPR = *_hoops_ASPH++;
					}
					else {
						/*
						 * _hoops_ARGAR _hoops_SCH _hoops_AARI _hoops_IS _hoops_RH _hoops_RSGI (_hoops_HCCPR
						 * _hoops_SR _hoops_PAR _hoops_RH _hoops_IPSP _hoops_AIAH _hoops_HS!)
						 */
						if (_hoops_AICPR == _hoops_IICPR) break;
						_hoops_AICPR = _hoops_IICPR;
					}

					_hoops_HRCPR (_hoops_PICPR, _hoops_AICPR, _hoops_SPHPR, _hoops_CCCPR, false);

					_hoops_PICPR = _hoops_AICPR; /* _hoops_HAPR _hoops_IS _hoops_SCIA */
				}
			}
		} while (_hoops_ASPH != _hoops_HICPR);
	}
}


local void _hoops_GSCPR (
	Polyhedron			*_hoops_IPRI) {
	_hoops_GHHPR		*flags;
	_hoops_GHHPR		*_hoops_RSCPR;

	if (_hoops_IPRI->type != _hoops_GSIP) return; /* _hoops_ASCPR, _hoops_APSH _hoops_PII _hoops_SR'_hoops_ASAR _hoops_CPHR */

	if (_hoops_IPRI->_hoops_IHHPR.flags == null)
		HI_Initialize_Edge_Attributes (_hoops_IPRI, false);

	/*
	 * _hoops_PAGA: _hoops_SR _hoops_PSCPR _hoops_RH '_hoops_HSCPR' _hoops_ISCPR _hoops_CCGR _hoops_HA, _hoops_CGPR _hoops_SCH'_hoops_GRI _hoops_IGRC
	 * _hoops_RPII _hoops_SSGRR _hoops_IH, _hoops_HIS _hoops_GAR _hoops_HAR _hoops_IS _hoops_RHCPR _hoops_GGHC _hoops_RGRRR _hoops_AHHA _hoops_IS _hoops_SHH
	 * _hoops_CSCPR-_hoops_GSAS _hoops_IH _hoops_RH _hoops_SSCPR _hoops_IIGR _hoops_GGSPR _hoops_RH _hoops_IGRH _hoops_GGR _hoops_RH _hoops_ACRI _hoops_RGSPR.
	 */

	flags	   = _hoops_IPRI->_hoops_IHHPR.flags;
	_hoops_RSCPR  = flags + _hoops_IPRI->_hoops_SPHA;

	do {
		flags[0] |= _hoops_AGSPR;
		flags[1] |= _hoops_AGSPR;
		/* _hoops_SGI[2] &= ~_hoops_PGSPR; */ /* _hoops_CGH _hoops_AIAH _hoops_SHH _hoops_GGSP */
	} _hoops_RGGA ((flags += 3) == _hoops_RSCPR);
}



GLOBAL_FUNCTION _hoops_GSPGR HI_Assemble_3D_Polyedges (
	Polyhedron *			_hoops_IPRI,
	_hoops_GHHPR		_hoops_HGSPR,
	float					_hoops_SHIPR) {
	_hoops_GSPGR					_hoops_RSPGR, _hoops_ASPGR;

	_hoops_RSPGR = HI_What_Time();

	if (_hoops_IPRI->_hoops_SHGPR != null) {
#ifdef _hoops_IGSPR
# ifdef _hoops_CGSPR
		_hoops_SGSPR (HEC_INFO, HES_REBUILDING_TRISTRIP,
				_hoops_GRSPR (null, "Rebuilding polyedges for polyhedron %k", &_hoops_IPRI));
# endif /* _hoops_SHRS */
#endif /* _hoops_RRSPR */
		HI_Free_Polyedge_List (_hoops_IPRI->_hoops_SHGPR);
		_hoops_IPRI->_hoops_SHGPR = null;
	}

	/* _hoops_PSRAR _hoops_RH _hoops_SIGR _hoops_SGI _hoops_ISHP _hoops_IS _hoops_RH _hoops_CGSI _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_IIAC _hoops_APIP _hoops_GAPR. */
	_hoops_HGSPR &= ~_hoops_IPRI->_hoops_RSHPR;

	/* _hoops_PPR _hoops_HSPP _hoops_ARSPR _hoops_SGS _hoops_SR'_hoops_RISP _hoops_CPHR _hoops_SCH */
	_hoops_IPRI->_hoops_RSHPR |= _hoops_HGSPR;

	if (_hoops_IPRI->_hoops_SPHA == 0) 
		goto _hoops_PRSPR; /* _hoops_HCR _hoops_CPHR */

	/* _hoops_HHSA _hoops_GII _hoops_AIRI _hoops_CPCI _hoops_IS _hoops_HRSPR */
	{
		Polyedge *			pe;

		if ((pe = _hoops_IPRI->_hoops_SHGPR) != null) do {
			_hoops_GACR *		dl;

			if ((dl = pe->_hoops_GAHA) != null) do {
				dl->_hoops_GSAI = (_hoops_GHGI)0xffffffff;
			} while ((dl = dl->next) != null);
		} while ((pe = pe->next) != null);
	}

	if (BIT (_hoops_HGSPR, _hoops_AACPR))
		_hoops_RACPR (_hoops_IPRI);

	if (BIT (_hoops_HGSPR, _hoops_CCCPR))
		_hoops_ICCPR (_hoops_IPRI);

	if (BIT (_hoops_HGSPR, _hoops_AGSPR))
		_hoops_GSCPR (_hoops_IPRI);

	if (BIT (_hoops_HGSPR, _hoops_CIIPR))
		_hoops_CHIPR (_hoops_IPRI, _hoops_SHIPR);

	/* _hoops_PGII _hoops_RII _hoops_IRSPR-_hoops_SIH _hoops_CGH _hoops_HGCR "_hoops_SHR" _hoops_CRSPR _hoops_IS, _hoops_APCS. */


	if (_hoops_IPRI->type == _hoops_SCIP) {
		_hoops_IGHPR			*temps = null;
		int						*_hoops_SRSPR;
		int						_hoops_GASPR;
		_hoops_RHHPR		**source,
								**_hoops_RASPR;
		Shell alter				*_hoops_SPHPR = (Shell alter *)_hoops_IPRI;

		/*
		 * _hoops_AASPR _hoops_PPR _hoops_HGCR _hoops_RH _hoops_GPHA-_hoops_IS-_hoops_ISHA _hoops_HIGR - _hoops_RH _hoops_HIGR _hoops_PGAP
		 * _hoops_ACAR _hoops_GRR _hoops_SSRR _hoops_HSPP _hoops_GPHA _hoops_IS _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_PASPR _hoops_GIHA
		 *
		 * _hoops_HGI _hoops_CRS _hoops_HRGR _hoops_RGAR _hoops_IRAP _hoops_CGPR _hoops_SPPR _hoops_SIPGR'_hoops_RA _hoops_RPII _hoops_SPIP;
		 * _hoops_CGPR _hoops_PSP _hoops_SPPR _hoops_CHR _hoops_GSGI _hoops_SCH _hoops_HCPA _hoops_GH _hoops_CCA _hoops_SPCC 1.
		 */
		if ((source = _hoops_SPHPR->_hoops_HHHPR) == null) {
			HI_Create_Shell_Edges (_hoops_SPHPR, false);
			source = _hoops_SPHPR->_hoops_HHHPR;
		}

		if (_hoops_SPHPR->_hoops_SPHA == 0) 
			goto _hoops_PRSPR; /* _hoops_HASPR */

		/* _hoops_ARAS _hoops_RHIR _hoops_PPR _hoops_HGCR _hoops_RH _hoops_IASPR-_hoops_SGI _hoops_HSH _hoops_ARP _hoops_RPHR */
		if (ANYBIT (_hoops_HGSPR, _hoops_SHHPR))
			_hoops_PCHPR (_hoops_IPRI);

		/*
		 * _hoops_IPCP "_hoops_IRHP" _hoops_AHHA, _hoops_GAR _hoops_IRS _hoops_SHSC, _hoops_GRS _hoops_HGAP _hoops_PCCP _hoops_HCHC _hoops_IIGR
		 * _hoops_HHIPR _hoops_CASPR _hoops_SASPR _hoops_IS _hoops_RRPC _hoops_RH _hoops_APSR _hoops_PHI _hoops_IIGR _hoops_SPPR.
		 * (_hoops_ICAGR _hoops_GISR _hoops_IH _hoops_IRS _hoops_GPHA _hoops_CIHA, _hoops_SPR _hoops_IH _hoops_PCCP _hoops_ISHA _hoops_CIHA, _hoops_IH _hoops_GRR _hoops_ISHA.)
		 * _hoops_IIPP _hoops_RGR _hoops_GC _hoops_HA _hoops_HRII _hoops_HSAR _hoops_GPSPR-_hoops_HPP-_hoops_GPSPR.
		 * _hoops_RPSPR _hoops_SGS _hoops_CHH _hoops_SAHR _hoops_SHH _hoops_HAH _hoops_AHSC...
		 */
		_hoops_GASPR = _hoops_AHIA (2 * _hoops_SPHPR->_hoops_SPHA, 1<<20);
		ALLOC_ARRAY_CACHED (_hoops_SRSPR, _hoops_GASPR, int);

		_hoops_RASPR = source + _hoops_SPHPR->point_count;

		/*
		 * _hoops_CGP _hoops_RH _hoops_HSPP _hoops_IIGR _hoops_RGR _hoops_PASPR _hoops_HIGR _hoops_HRGR _hoops_CRGP _hoops_HSAR
		 * _hoops_RH _hoops_HSPP _hoops_IIGR _hoops_RH _hoops_SPS _hoops_PASPR _hoops_HIGR, _hoops_PSCR _hoops_SPR
		 * _hoops_PAR _hoops_RRI _hoops_PASPR _hoops_GIHA (_hoops_SHCAR, _hoops_SPPR) _hoops_HICP _hoops_IH
		 * _hoops_RGR _hoops_HCGP _hoops_GPHA.
		 */
		do if (source[0] < source[1]) {
			_hoops_RHHPR	*edge = *source;
			int						_hoops_SHPC;

			/*
			 * _hoops_APSPR (_hoops_APGP, "_hoops_SPPR") _hoops_CHR _hoops_PPSPR "_hoops_HPSPR"
			 * _hoops_HPP _hoops_IPSPR (_hoops_CPSPR) _hoops_CAPR.
			 *
			 * _hoops_AIHH _hoops_RPP _hoops_GII _hoops_GRAA-_hoops_SPSPR _hoops_GHSPR _hoops_HGGC _hoops_GGCA _hoops_IH _hoops_RGR
			 * _hoops_HCGP.
			 */
			do if (edge->_hoops_GIHPR >= 0) {
				int *				_hoops_RHSPR = _hoops_SRSPR;
				_hoops_IGHPR *		_hoops_HAPAR;

				/* _hoops_RIRA _hoops_SPR - _hoops_HSPP _hoops_IRS "_hoops_IRHP" _hoops_ACRI */

				_hoops_SHPC = edge - _hoops_SPHPR->_hoops_GRCPR;

				/*
				 * _hoops_IPCP "_hoops_IRHP" _hoops_AHHA _hoops_GRS _hoops_SHH _hoops_AHSPR _hoops_GIRP _hoops_IS _hoops_SRSGR _hoops_RH
				 * "_hoops_HPHR" _hoops_AHHA _hoops_GAR _hoops_IRS _hoops_RHAA-_hoops_PHSPR _hoops_HHSPR.
				 */
				{
					_hoops_IGHPR			*_hoops_IHSPR; /* "_hoops_CHSPR _hoops_GGR _hoops_IRS _hoops_GCPR" */
					_hoops_GHHPR		*flags;

					ALLOC (_hoops_IHSPR, _hoops_IGHPR);

					/*
					 * _hoops_IPCP _hoops_AIRC _hoops_IH _hoops_RGR _hoops_ACRI _hoops_GRS _hoops_SHH _hoops_HCR _hoops_RH _hoops_PSHR -
					 * _hoops_AGAP _hoops_IIGR _hoops_RH _hoops_SRS _hoops_ISHA, _hoops_IH _hoops_PCAI.
					 */

					_hoops_SHSPR (_hoops_IHSPR->_hoops_PPGI);
					if ((flags = _hoops_IPRI->_hoops_IHHPR.flags) != null) {
						_hoops_GISPR (&_hoops_IPRI->_hoops_IHHPR,
												  _hoops_SHPC,
												  _hoops_IHSPR->_hoops_PPGI);
					}

					/* _hoops_IHIS _hoops_RH _hoops_IRHP-_hoops_ACRI _hoops_CRS _hoops_IS _hoops_RH _hoops_SPRS */
					_hoops_HAPAR = _hoops_IHSPR;
				}

				{
					_hoops_RHHPR	*_hoops_RISPR;
					_hoops_RHHPR	*_hoops_AISPR;

					/*
					 * _hoops_IISR _hoops_RH _hoops_HIGR _hoops_IIGR _hoops_GIHA _hoops_IH _hoops_RGR _hoops_ACRI.
					 *
					 * _hoops_PS _hoops_GA'_hoops_RA _hoops_ACPA _hoops_RSH _hoops_RGRRR _hoops_RH _hoops_HIGR _hoops_HRGR _hoops_CPIC _hoops_IS _hoops_SHH _hoops_GAPR,
					 * _hoops_HIS _hoops_SCH _hoops_IAGA _hoops_CRGR _hoops_RH '_hoops_IPHR' _hoops_AH.
					 */

					/* _hoops_PISPR _hoops_RH _hoops_PGCR _hoops_RSSA _hoops_SR _hoops_AIAH _hoops_ACPA _hoops_CIAA _hoops_RH _hoops_HIGR */
					_hoops_HAPAR->_hoops_RRHPR = source - _hoops_SPHPR->_hoops_HHHPR;

					/*
					 * _hoops_HRHPR _hoops_RAIGR _hoops_HISPR _hoops_GAR _hoops_IAS-_hoops_HPPC-_hoops_IAS-_hoops_HPPC-_hoops_IAS-_hoops_HPPC
					 * _hoops_GGR _hoops_AGR _hoops_IS _hoops_IISPR _hoops_SRHPR
					 */

					_hoops_HAPAR->_hoops_RAHPR = _hoops_RHSPR;

					*_hoops_RHSPR++ = _hoops_SHPC;				/* _hoops_ISHA	  */
					*_hoops_RHSPR++ = edge->_hoops_GIHPR;		/* _hoops_GPHA */


					/*
					 * _hoops_CISPR _hoops_RGR _hoops_PASPR _hoops_RARP _hoops_GGR _hoops_RH _hoops_SPPR _hoops_CRPR _hoops_GAR _hoops_SISPR
					 * _hoops_RPII _hoops_GCSPR, _hoops_HPP _hoops_HAGC _hoops_SCH _hoops_HHHR.
					 */
					edge->_hoops_GIHPR = ~edge->_hoops_GIHPR;

					/*
					 * _hoops_SGCH _hoops_IH _hoops_HPIH _hoops_PASPR (_hoops_PPRAR) _hoops_ISGR _hoops_RGR _hoops_SPR, _hoops_SGAPR
					 * _hoops_RCSPR _hoops_ACSPR _hoops_PCSPR _hoops_GAR _hoops_RH _hoops_HCSPR _hoops_ACRI.
					 */

					/* "_hoops_ICSPR" == _hoops_GAR _hoops_RGRRR _hoops_GAR _hoops_SR _hoops_GRHP _hoops_SPAAR _hoops_CCAH _hoops_GHSPR */
					_hoops_PCCAR {
						_hoops_RISPR	   = _hoops_SPHPR->_hoops_HHHPR[_hoops_RHSPR[-1]];
						_hoops_AISPR = _hoops_SPHPR->_hoops_HHHPR[_hoops_RHSPR[-1]+1];

						if (_hoops_RISPR == _hoops_AISPR) break;
						else if (_hoops_IPRI->_hoops_IHHPR.flags == null) {
							/* _hoops_PSP _hoops_AIRC - _hoops_GII _hoops_PPRAR _hoops_PASPR _hoops_CCSPR */

							_hoops_RGGA (_hoops_RISPR->_hoops_GIHPR >= 0)
								if (++_hoops_RISPR == _hoops_AISPR) goto _hoops_SCSPR;
							_hoops_SHPC = _hoops_RISPR - _hoops_SPHPR->_hoops_GRCPR;
						}
						else {
							/* _hoops_SSS _hoops_PPRAR _hoops_PASPR _hoops_CCA _hoops_PIS _hoops_AIRC */

							_hoops_PCCAR {
								if (_hoops_RISPR->_hoops_GIHPR >= 0) {
									_hoops_SHPC = _hoops_RISPR - _hoops_SPHPR->_hoops_GRCPR;
#ifndef _hoops_RGIPR
									if (_hoops_GSSPR (
												   &_hoops_IPRI->_hoops_IHHPR,
												   _hoops_SHPC, _hoops_HAPAR->_hoops_PPGI))
#endif
										break;
								}
								if (++_hoops_RISPR == _hoops_AISPR) goto _hoops_SCSPR;
							}
						}

						/* _hoops_GSGI _hoops_SPR - _hoops_IRAA _hoops_SCH */
						*_hoops_RHSPR++ = _hoops_SHPC;					/* _hoops_ISHA	  */
						*_hoops_RHSPR++ = _hoops_RISPR->_hoops_GIHPR;		/* _hoops_GPHA */
						_hoops_RISPR->_hoops_GIHPR = ~_hoops_RISPR->_hoops_GIHPR;

						/*
						 * _hoops_PS _hoops_SAHR _hoops_RSSPR _hoops_SPR _hoops_GPHA _hoops_ASSPR, _hoops_HA _hoops_HAPR _hoops_AARI
						 * _hoops_PPR _hoops_IHSH _hoops_IH _hoops_IRS _hoops_CCAH "_hoops_PSSPR" _hoops_PASPR.
						 */
						if (_hoops_RHSPR == _hoops_SRSPR + _hoops_GASPR)
							break;
					}

				  _hoops_SCSPR:;

					/* _hoops_PCSA _hoops_RSH _hoops_AHPH */
					_hoops_HAPAR->_hoops_PAHPR = (_hoops_RHSPR - _hoops_HAPAR->_hoops_RAHPR) / 2;


					/*
					 * _hoops_AGGA _hoops_CACH _hoops_RPP _hoops_SR _hoops_PAH _hoops_PHHR _hoops_RH "_hoops_RII _hoops_PPRRR" _hoops_HII _hoops_RH _hoops_GIGR
					 * _hoops_HSPP _hoops_GPHA. _hoops_RAH _hoops_HHSH _hoops_RH _hoops_PSHR _hoops_CSPC.
					 */

					/* _hoops_PHHR _hoops_ISSC _hoops_IS _hoops_RH _hoops_GPHA _hoops_CAS _hoops_SR _hoops_AIS */
					_hoops_RISPR	   = edge + 1; /* ('_hoops_ISHA' _hoops_HRGR _hoops_HSSPR _hoops_ISSPR-_hoops_PGCPR)*/
					_hoops_AISPR = source[1];

					/*
					 * _hoops_HRHPR _hoops_RAIGR _hoops_HISPR _hoops_GAR _hoops_HPPC-_hoops_IAS-_hoops_HPPC-_hoops_IAS-_hoops_HPPC-_hoops_IAS
					 * _hoops_GAR _hoops_SPR _hoops_CHH _hoops_ACRR
					 */

					_hoops_HAPAR->_hoops_AAHPR = _hoops_RHSPR;

					_hoops_RGGA (_hoops_RISPR == _hoops_AISPR) {
						if (_hoops_RHSPR == _hoops_SRSPR + _hoops_GASPR)
							break;

						if (_hoops_IPRI->_hoops_IHHPR.flags == null) {
							/* _hoops_PSP _hoops_AIRC - _hoops_GII _hoops_PPRAR _hoops_PASPR _hoops_CCSPR */

							_hoops_RGGA (_hoops_RISPR->_hoops_GIHPR >= 0)
								if (++_hoops_RISPR == _hoops_AISPR) goto _hoops_CSSPR;
							_hoops_SHPC = _hoops_RISPR - _hoops_SPHPR->_hoops_GRCPR;
						}
						else {
							/* _hoops_SSS _hoops_PPRAR _hoops_PASPR _hoops_CCA _hoops_PIS _hoops_AIRC */

							_hoops_PCCAR {
								if (_hoops_RISPR->_hoops_GIHPR >= 0) {
									_hoops_SHPC = _hoops_RISPR - _hoops_SPHPR->_hoops_GRCPR;
#ifndef _hoops_RGIPR
									if (_hoops_GSSPR (
												   &_hoops_IPRI->_hoops_IHHPR,
												   _hoops_SHPC, _hoops_HAPAR->_hoops_PPGI))
#endif
										break;
								}
								if (++_hoops_RISPR == _hoops_AISPR) goto _hoops_CSSPR;
							}
						}

						/* _hoops_GSGI _hoops_SPR - _hoops_IRAA _hoops_SCH */
						*_hoops_RHSPR++ = _hoops_RISPR->_hoops_GIHPR;				/* _hoops_GPHA */
						*_hoops_RHSPR++ = _hoops_SHPC;							/* _hoops_ISHA	  */
						_hoops_RISPR->_hoops_GIHPR = ~_hoops_RISPR->_hoops_GIHPR;

						_hoops_RISPR	   = _hoops_SPHPR->_hoops_HHHPR[_hoops_RHSPR[-2]];
						_hoops_AISPR = _hoops_SPHPR->_hoops_HHHPR[_hoops_RHSPR[-2]+1];
					}

				  _hoops_CSSPR:;

					/* _hoops_PCSA _hoops_RSH _hoops_AHPH */
					_hoops_HAPAR->_hoops_HAHPR = (_hoops_RHSPR - _hoops_HAPAR->_hoops_AAHPR) / 2;
				}

				/* _hoops_GHIS _hoops_SCH _hoops_HPP _hoops_RH _hoops_AIRC */
				_hoops_CSHPR (_hoops_HAPAR, &temps);

				/*
				 * _hoops_HGI _hoops_IRHP _hoops_ACRI _hoops_HRGR _hoops_CPHR; _hoops_IHSH _hoops_IH _hoops_HPIH _hoops_SSRR
				 * _hoops_PASPR (_hoops_PPR _hoops_IRHP-_hoops_ACRI _hoops_HSPP) _hoops_GIAA _hoops_RH
				 * _hoops_GIGR _hoops_HCGP _hoops_GPHA.
				 */
			} _hoops_RGGA (++edge == source[1]);

			/* _hoops_IHSH _hoops_IH _hoops_IRS _hoops_CCAH _hoops_GIGR-_hoops_HCGP _hoops_GPHA */
		} _hoops_RGGA (++source == _hoops_RASPR);


		/*
		 * _hoops_SSSPR _hoops_RH _hoops_GGGHR _hoops_PASPR _hoops_RGGHR
		 */
		{
			_hoops_RHHPR	*edge;
			_hoops_RHHPR	*_hoops_AGGHR;

			edge = _hoops_SPHPR->_hoops_GRCPR;
			_hoops_AGGHR = edge + _hoops_SPHPR->_hoops_SPHA;
			do edge->_hoops_GIHPR = ~edge->_hoops_GIHPR;
			_hoops_RGGA (++edge == _hoops_AGGHR);
		}

		FREE_ARRAY (_hoops_SRSPR, _hoops_GASPR, int);

		if (temps != null) 
			_hoops_PRIPR (temps, _hoops_IPRI);
		/* (_hoops_PGGHR _hoops_HS _hoops_HA _hoops_RPII _hoops_HGGPR) */

		if (BIT (HOOPS_WORLD->_hoops_HGGHR, _hoops_IGGHR)) {
			if (_hoops_SPHPR->_hoops_GRCPR) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_GRCPR, _hoops_SPHPR->_hoops_SPHA, _hoops_RHHPR);
				_hoops_SPHPR->_hoops_GRCPR = null;
			}
			if (_hoops_SPHPR->_hoops_HHHPR) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_HHHPR, _hoops_SPHPR->point_count+1, _hoops_RHHPR *);
				_hoops_SPHPR->_hoops_HHHPR = null;
			}
			if (_hoops_SPHPR->_hoops_SGCPR) {
				FREE_ARRAY (_hoops_SPHPR->_hoops_SGCPR, _hoops_SPHPR->_hoops_SPHA, _hoops_CGCPR);
				_hoops_SPHPR->_hoops_SGCPR = null;
			}
		}
	}
	else /* _hoops_RPP _hoops_GSHPR */ {
		_hoops_AIHPR *		_hoops_PIHPR = (_hoops_AIHPR *)_hoops_IPRI;

		/* _hoops_ARAS _hoops_RHIR _hoops_PPR _hoops_HGCR _hoops_RH _hoops_IASPR-_hoops_SGI _hoops_HSH _hoops_ARP _hoops_RPHR */
		if (ANYBIT (_hoops_HGSPR, _hoops_SHHPR))
			_hoops_PCHPR (_hoops_IPRI);

		if (_hoops_PIHPR->_hoops_IHHPR.flags == null) {
			/*
			 * _hoops_RAIGR _hoops_RSRA _hoops_ACRI _hoops_GRS _hoops_AA _hoops_CGGHR _hoops_IH _hoops_IRS _hoops_HSHRR _hoops_CCA _hoops_PSP _hoops_IRGH _hoops_ISHA
			 * _hoops_AIRC. _hoops_IPCP _hoops_RGAR _hoops_SGGHR _hoops_HRGR _hoops_GRGHR _hoops_SCH _hoops_CRGR _hoops_ARAH-_hoops_AHHA.
			 */
			Polyedge		*polyedge;

			{
				int				_hoops_SPHA;

				ZALLOC (polyedge, Polyedge);
				_hoops_ICAI(polyedge);
				_hoops_PIHPR->_hoops_SHGPR = polyedge;
				polyedge->next = null;
				_hoops_SHSPR (polyedge->_hoops_PPGI);
				polyedge->same_colors = _hoops_PAIPR;

				/*
				 * _hoops_SSCR _hoops_RH '_hoops_IHPR' _hoops_ISHA _hoops_RPR - _hoops_PIP _hoops_SGS _hoops_ASHS, _hoops_HPP
				 * _hoops_RRGHR, _hoops_CRRPR _hoops_IRS _hoops_ARGHR _hoops_IIGR '_hoops_PRGHR' _hoops_SPPR _hoops_IGIAR _hoops_RH _hoops_RPHR
				 * _hoops_PPR _hoops_SCIA _hoops_IIGR _hoops_RH _hoops_HSHRR.
				 */
				_hoops_SPHA = _hoops_PIHPR->_hoops_SPHA - 2 * (_hoops_PIHPR->rows + _hoops_PIHPR->columns) + 1;

				polyedge->total = 1 + _hoops_SPHA;

				polyedge->_hoops_PHHA = 1;
				ALLOC_ARRAY (polyedge->lengths, 1, int);
				polyedge->lengths_allocated = 1;
				*polyedge->lengths = polyedge->total;

				ALLOC_ARRAY (polyedge->_hoops_AIHA, polyedge->total, int);
				ALLOC_ARRAY (polyedge->_hoops_SPII, polyedge->total, int);
				polyedge->_hoops_IPII = polyedge->_hoops_CPII = polyedge->total;

				polyedge->_hoops_RAHH |= _hoops_AAHH;
			}


			{
				/* _hoops_HGI _hoops_HIGR _hoops_IIGR _hoops_IGCPR _hoops_HRGR _hoops_HRGHR _hoops_RRIPR! */
				int		*_hoops_RPIPR = polyedge->_hoops_AIHA;
				int		*_hoops_APIPR = polyedge->_hoops_SPII;
				int		vertex;
				int		column;
				int		columns = _hoops_PIHPR->columns;
				int		row;
				int		rows = _hoops_PIHPR->rows;

				/*
				 * _hoops_GCIH _hoops_HPGR _hoops_AAPA _hoops_RAAP, _hoops_PHHR _hoops_HCR _hoops_RH _hoops_PPRRR _hoops_RPHR, _hoops_PSCR _hoops_IRGHR-_hoops_CRGHR _hoops_ISSC
				 * _hoops_HCR _hoops_RH _hoops_PPRRR _hoops_RAAP. _hoops_SRGHR _hoops_IH _hoops_GRR _hoops_GAGHR _hoops_CPIC _hoops_ISHP. _hoops_RAGHR
				 * _hoops_RAS '_hoops_HCR _hoops_RH _hoops_PPRRR _hoops_RPHR' _hoops_GPP _hoops_RH _hoops_CGHI _hoops_GAGHR.
				 */

				row = rows - 1;
				column = 0;
				vertex = row * columns;

				/* _hoops_HSPP _hoops_IRS _hoops_ACRI */
				*_hoops_RPIPR++ = vertex;
				*_hoops_APIPR++ = 0;

				_hoops_PCCAR {
					/* _hoops_PHHR _hoops_HCR _hoops_RH _hoops_PPRRR _hoops_RPHR */
					_hoops_RGGA (++column == columns) {
						*_hoops_RPIPR++ = ++vertex;
						*_hoops_APIPR++ = 3 * vertex - 3;
					}

					if (row == 0) break; /* _hoops_PSP _hoops_RRI */

					/* _hoops_HPRAR _hoops_ISHP _hoops_GPP _hoops_RH _hoops_RPHR _hoops_HPP _hoops_SPR _hoops_GAGHR */
					row -= 1;
					vertex -= columns;
					*_hoops_RPIPR++ = vertex;
					*_hoops_APIPR++ = 3 * vertex + 1;

					/* _hoops_IRGHR _hoops_CRGHR _hoops_RAAP */
					_hoops_RGGA (--column == 0) {
						*_hoops_RPIPR++ = --vertex + columns;
						*_hoops_APIPR++ = 3 * vertex + 3 + 2;
						*_hoops_RPIPR++ = vertex;
						*_hoops_APIPR++ = 3 * vertex + 1;
					}
				}
			}
		}
		else {
			_hoops_IGHPR	*temps = null;
			int				*_hoops_SRSPR;
			int				_hoops_GASPR;
			char			*_hoops_AAGHR;

			_hoops_GASPR = _hoops_AHIA (2 * _hoops_PIHPR->_hoops_SPHA, 1<<20);
			ALLOC_ARRAY_CACHED (_hoops_SRSPR, _hoops_GASPR, int);

			/*
			 * _hoops_PS'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_AA _hoops_RGR _hoops_GAR _hoops_CCA _hoops_SCHS _hoops_ARRS, _hoops_HIH _hoops_SR _hoops_RRP
			 * _hoops_HHH _hoops_HGHC _hoops_IS _hoops_ASH _hoops_RH _hoops_PAGHR _hoops_SGS _hoops_PCCP _hoops_ISHA _hoops_HRGR _hoops_HGGC
			 * "_hoops_HHPA". (_hoops_GPGP _hoops_RH _hoops_RRCPR _hoops_RRGR _hoops_GRAA-_hoops_HAGHR _hoops_CSAP _hoops_IAGHR
			 * _hoops_HPP _hoops_CPSPR "_hoops_PASPR".)
			 */

			/* _hoops_ARPR _hoops_PPR _hoops_HSPC _hoops_RH '_hoops_HHPA' _hoops_CRPR */
			ALLOC_ARRAY_CACHED (_hoops_AAGHR, _hoops_PIHPR->_hoops_SPHA, char);
			SET_MEMORY (_hoops_AAGHR, _hoops_PIHPR->_hoops_SPHA, 1);

			{
				/*
				 * _hoops_IGAS _hoops_CPS _hoops_GGR _hoops_CAGHR _hoops_CRGR _hoops_CPCPR
				 * (_hoops_RGR _hoops_HIGR *_hoops_HRGR* _hoops_GGR _hoops_IRS _hoops_SAGHR _hoops_AGR)
				 */
				int							_hoops_GPGHR;
				_hoops_IGHPR					*_hoops_HAPAR;
				int							vertex;
				int							column;
				int							columns = _hoops_PIHPR->columns;
				_hoops_RPGHR		*_hoops_APGHR;
				int							_hoops_PPGHR;
				int							*_hoops_RHSPR = _hoops_SRSPR;
				int							row;
				int							_hoops_CSIPR;


				/*
				 * _hoops_HPGHR _hoops_RRGHR, _hoops_RH _hoops_ISHA _hoops_IPGHR _hoops_IRHPR _hoops_CRRPR _hoops_CPGHR
				 * _hoops_SPGHR _hoops_SPPR _hoops_SGS _hoops_GA'_hoops_RA _hoops_CPSA _hoops_GGCA. _hoops_GHGHR _hoops_CAPR
				 * _hoops_GAR _hoops_RHGHR. (_hoops_AHGHR _hoops_IRS _hoops_GPHA _hoops_RRGGR, _hoops_RH _hoops_ISHA _hoops_PHGHR _hoops_IS
				 * _hoops_RH _hoops_RPHR _hoops_HRGR _hoops_HPP _hoops_RRGHR _hoops_HHGHR 3*_hoops_RRGGR, _hoops_AGCPR _hoops_GAR
				 * 3*_hoops_RRGGR+1, _hoops_PPR _hoops_GH-_hoops_PPR-_hoops_RAAP _hoops_GAR 3*_hoops_RRGGR+2.)
				 */

				/* _hoops_ARAS _hoops_GH _hoops_RH _hoops_RAAP _hoops_PPAP */
				row = 0;
				column = 0;
				vertex = 0;

				_hoops_CSIPR = _hoops_PIHPR->rows - 1;
				_hoops_RGGA (row++ == _hoops_CSIPR) {
					_hoops_AAGHR[3*vertex + 2] = false;
					vertex += columns;
				}
				--row;					/* _hoops_ISSC _hoops_ISHP _hoops_IS _hoops_SCIA _hoops_GAGHR */

				/* _hoops_ARAS _hoops_ARHI _hoops_RH _hoops_SCIA */
				 _hoops_RGGA (column++ == columns) {
					_hoops_AAGHR [3*vertex + 2] = false;
					_hoops_AAGHR [3*vertex + 1] = false;
					++vertex;
				}
				--column, --vertex;		/* _hoops_ISSC _hoops_SPR _hoops_HHSPR */

				/* _hoops_PPR _hoops_ISHP _hoops_RH _hoops_RPHR _hoops_PPAP */
				do {
					_hoops_AAGHR [3*vertex] = false;
					vertex -= columns;
				} _hoops_RGGA (--row < 0);



				_hoops_APGHR   = &_hoops_PIHPR->_hoops_IHHPR;
				_hoops_PPGHR = _hoops_PIHPR->_hoops_SPHA - 1;

				do if (_hoops_AAGHR[_hoops_PPGHR]) {
					/* _hoops_RIRA _hoops_SPR - _hoops_HSPP _hoops_IRS "_hoops_IRHP" _hoops_ACRI */

					vertex = _hoops_PPGHR / 3;

					ALLOC (_hoops_HAPAR, _hoops_IGHPR);
					_hoops_SHSPR (_hoops_HAPAR->_hoops_PPGI);
					_hoops_GISPR (_hoops_APGHR, _hoops_PPGHR, _hoops_HAPAR->_hoops_PPGI);

					_hoops_HAPAR->_hoops_RRHPR = vertex;

					/* _hoops_HSPP _hoops_IPIPR _hoops_RAIGR */
					_hoops_HAPAR->_hoops_RAHPR = _hoops_RHSPR;

					/* _hoops_PS _hoops_ACPA _hoops_RGR _hoops_ISHA _hoops_HRGR _hoops_GPRS, _hoops_HIS _hoops_PHHR _hoops_CRGC _hoops_IS _hoops_RGCI _hoops_PASPR */
					switch (_hoops_PPGHR % 3) {
						case 0: vertex += 1;			break;
						case 1: vertex += columns;		break;
						case 2: vertex += columns - 1;	break;
					}
					*_hoops_RHSPR++ = _hoops_PPGHR;
					*_hoops_RHSPR++ = vertex;
					_hoops_AAGHR[_hoops_PPGHR] = false;

					/*
					 * _hoops_IHGHR _hoops_GRS _hoops_GRGP _hoops_GPHA _hoops_PPR _hoops_ISHA _hoops_PSPI _hoops_CRGR _hoops_RH
					 * _hoops_IPHR _hoops_CRPR _hoops_IIGR _hoops_IPIPR _hoops_RAIGR _hoops_GGR _hoops_RH _hoops_AGR _hoops_IAS-_hoops_HPPC-_hoops_IAS-_hoops_HPPC, _hoops_IS
					 * _hoops_IISPR _hoops_SRHPR.
					 */
#			define		_hoops_CHGHR(edge, _hoops_SHGHR) {						\
						if (_hoops_AAGHR[edge]) {							\
							if (_hoops_GSSPR (	\
								_hoops_APGHR, edge, _hoops_HAPAR->_hoops_PPGI)) { \
								_hoops_AAGHR[edge] = false;				\
								*_hoops_RHSPR++ = edge;							\
								*_hoops_RHSPR++ = (vertex += _hoops_SHGHR);		\
								continue;								\
							}											\
						}												\
					} /* _hoops_GIGHR: _hoops_ASAI '_hoops_HPGP (0)' - _hoops_CRHPR '_hoops_SAS' _hoops_RIGHR */

					/* _hoops_IHSH _hoops_IH _hoops_CCAH _hoops_AIGHR _hoops_SPPR */
					_hoops_PCCAR {
						if (_hoops_RHSPR == _hoops_SRSPR + _hoops_GASPR)
							break;

						_hoops_GPGHR = vertex*3;
						_hoops_CHGHR (_hoops_GPGHR, 1);
						_hoops_CHGHR (_hoops_GPGHR + 1, columns);
						_hoops_CHGHR (_hoops_GPGHR + 2, columns - 1);
						if (_hoops_GPGHR >= 3) _hoops_CHGHR (_hoops_GPGHR - 3, -1);
						if ((_hoops_GPGHR -= 3*columns) >= 0) { /* _hoops_ISHP _hoops_IRS _hoops_GAGHR */
							_hoops_CHGHR (_hoops_GPGHR + 1, -columns);
							_hoops_CHGHR (_hoops_GPGHR + 5, -columns + 1);
						}
						break; /* _hoops_ICCAR _hoops_PRAR, _hoops_PSP _hoops_RIARR _hoops_GSGI _hoops_HII _hoops_ARI */
					}
					_hoops_HAPAR->_hoops_PAHPR = (_hoops_RHSPR - _hoops_HAPAR->_hoops_RAHPR) / 2; /* _hoops_CPHR _hoops_CCA _hoops_RAIGR */


					/*
					 * _hoops_SGCH _hoops_IH _hoops_HPIH _hoops_IPIPR _hoops_PHGHR _hoops_RH _hoops_GIGR _hoops_HSPP
					 */
					_hoops_HAPAR->_hoops_AAHPR = _hoops_RHSPR;
					vertex = _hoops_HAPAR->_hoops_RRHPR;

					/*
					 * _hoops_PIGHR _hoops_GRS _hoops_GRGP _hoops_GPHA _hoops_PPR _hoops_ISHA _hoops_PSPI _hoops_CRGR _hoops_RH
					 * _hoops_IPHR _hoops_CRPR _hoops_IIGR _hoops_IPIPR _hoops_IHAC _hoops_GGR _hoops_RH _hoops_AGR _hoops_HPPC-_hoops_IAS-_hoops_HPPC-_hoops_IAS,
					 * _hoops_PGAP _hoops_HRGR _hoops_RH _hoops_AGR _hoops_SPR _hoops_HCAGR _hoops_GSSS.
					 */
#			define		_hoops_HIGHR(edge, _hoops_SHGHR) {						\
						if (_hoops_AAGHR[edge]) {							\
							if (_hoops_GSSPR (	\
								_hoops_APGHR, edge, _hoops_HAPAR->_hoops_PPGI)) { \
								_hoops_AAGHR[edge] = false;				\
								*_hoops_RHSPR++ = (vertex += _hoops_SHGHR);		\
								*_hoops_RHSPR++ = edge;							\
								continue;								\
							}											\
						}												\
					} /* _hoops_GIGHR: _hoops_ASAI '_hoops_HPGP (0)' - _hoops_CRHPR '_hoops_SAS' _hoops_RIGHR */

					/* _hoops_IHSH _hoops_IH _hoops_CCAH _hoops_AIGHR _hoops_SPPR */
					_hoops_PCCAR {
						if (_hoops_RHSPR == _hoops_SRSPR + _hoops_GASPR)
							break;

						_hoops_GPGHR = vertex*3;
						_hoops_HIGHR (_hoops_GPGHR, 1);
						_hoops_HIGHR (_hoops_GPGHR + 1, columns);
						_hoops_HIGHR (_hoops_GPGHR + 2, columns - 1);
						if (_hoops_GPGHR >= 3) _hoops_HIGHR (_hoops_GPGHR - 3, -1);
						if ((_hoops_GPGHR -= 3*columns) >= 0) { /* _hoops_ISHP _hoops_IRS _hoops_GAGHR */
							_hoops_HIGHR (_hoops_GPGHR + 1, -columns);
							_hoops_HIGHR (_hoops_GPGHR + 5, -columns + 1);
						}
						break; /* _hoops_ICCAR _hoops_PRAR, _hoops_PSP _hoops_RIARR _hoops_GSGI _hoops_HII _hoops_ARI */
					}
					_hoops_HAPAR->_hoops_HAHPR = (_hoops_RHSPR - _hoops_HAPAR->_hoops_AAHPR) / 2; /* _hoops_CPHR _hoops_CCA _hoops_IHAC */

					/* _hoops_GHIS _hoops_SCH _hoops_HPP _hoops_RH _hoops_AIRC */
					_hoops_CSHPR (_hoops_HAPAR, &temps);

					_hoops_RHSPR = _hoops_SRSPR;

					/* _hoops_IHSH _hoops_IH _hoops_IRS _hoops_CCAH _hoops_GIGR-_hoops_HCGP _hoops_GPHA */
				} while (--_hoops_PPGHR >= 0);
			}

			FREE_ARRAY (_hoops_SRSPR, _hoops_GASPR, int);
			FREE_ARRAY (_hoops_AAGHR, _hoops_PIHPR->_hoops_SPHA, char);

			if (temps != null) 
				_hoops_PRIPR (temps, _hoops_IPRI);
			/* (_hoops_PGGHR _hoops_HS _hoops_HA _hoops_RPII _hoops_HGGPR) */
		}
	}

_hoops_PRSPR:

	/* ('_hoops_IIGHR' _hoops_SGI _hoops_HS _hoops_AIAH _hoops_RPII _hoops_ARP) */

	_hoops_ASPGR = HI_What_Time();
	return (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}



GLOBAL_FUNCTION void HI_Free_Polyedge (
	Polyedge *			pe) {

	if (BIT (pe->_hoops_RAHH, _hoops_AAHH)) {
		if (pe->lengths && pe->lengths_allocated > 0)
			FREE_ARRAY (pe->lengths, pe->lengths_allocated, int);
		if (pe->_hoops_AIHA && pe->_hoops_IPII > 0)
			FREE_ARRAY (pe->_hoops_AIHA, pe->_hoops_IPII, int);
		if (pe->_hoops_SPII && pe->_hoops_CPII > 0)
			FREE_ARRAY (pe->_hoops_SPII, pe->_hoops_CPII, int);
	}

	/* _hoops_RPP _hoops_RGR _hoops_ACRI _hoops_HRGR _hoops_HAR _hoops_CIGHR _hoops_HII _hoops_RH _hoops_AARPR, _hoops_HIH _hoops_HRGR _hoops_RIIA _hoops_RH _hoops_GGPI _hoops_HII _hoops_IRS
	   _hoops_PGSA-_hoops_SGSI _hoops_CAIH, _hoops_SR _hoops_RRP _hoops_IS _hoops_CIH _hoops_RRI _hoops_HSAR _hoops_SR _hoops_SIGHR _hoops_CHH */
	if (pe->points != null && BIT (pe->_hoops_RAHH, _hoops_AIPI))
		FREE_ARRAY_ALIGNED (pe->points, pe->point_count, Point, 16);

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
#  ifndef _hoops_GCGHR
	if (pe->_hoops_PCHA != null && BIT (pe->_hoops_RAHH, _hoops_PIPI))
		FREE_ARRAY (pe->_hoops_PCHA, pe->point_count, RGB);
	if (pe->_hoops_HCHA != null && BIT (pe->_hoops_RAHH, _hoops_RCGHR))
		FREE_ARRAY (pe->_hoops_HCHA, pe->point_count, _hoops_ACGHR);
	if (pe->_hoops_ASHA != null && BIT (pe->_hoops_RAHH, _hoops_PCGHR))
		FREE_ARRAY (pe->_hoops_ASHA, pe->_hoops_SPHA, RGB);
#  endif

#  ifndef _hoops_HCGHR
	if (pe->_hoops_ICHA != null && BIT (pe->_hoops_RAHH, _hoops_ICGHR))
		FREE_ARRAY (pe->_hoops_ICHA, pe->point_count, Vector);
	if (pe->_hoops_RSHA != null && BIT (pe->_hoops_RAHH, _hoops_GHII))
		FREE_ARRAY (pe->_hoops_RSHA, pe->_hoops_SPHA, Vector);
#  endif

#  ifndef DISABLE_TEXTURING
	if (pe->_hoops_CCHA != null && BIT (pe->_hoops_RAHH, _hoops_CCGHR))
		FREE_ARRAY (pe->_hoops_CCHA, pe->point_count * pe->_hoops_GSHA, _hoops_RSSH);
#  endif
#endif

	if (pe->_hoops_CCCP != null && BIT (pe->_hoops_RAHH, _hoops_HIPI))
		FREE_ARRAY (pe->_hoops_CCCP, pe->point_count, float);

	if (pe->_hoops_SCGHR != null && _hoops_ISAI (pe->_hoops_SCGHR) == 0)
		HI_Free_Polyedge ((Polyedge alter *)pe->_hoops_SCGHR);

	if (pe->_hoops_GAHA) {
		_hoops_GACR *      dl;

		while ((dl = pe->_hoops_GAHA) != null) {
			pe->_hoops_GAHA = dl->next;
			_hoops_HPRH(dl);
		}
	}

	pe->bounding.release();

	/* _hoops_RGR _hoops_CGH _hoops_SHH _hoops_RH _hoops_RGAR _hoops_HGHC _hoops_CAS _hoops_RHAC _hoops_CACH _hoops_PCCP _hoops_CSHS _hoops_CGI _hoops_RGCPR _hoops_CRGR _hoops_GSGHR */	
	FREE (pe, Polyedge);
}


GLOBAL_FUNCTION void HI_Free_Polyedge_List (
	Polyedge		*_hoops_RSGHR) {
	Polyedge		*next;

	if (_hoops_RSGHR) do {
		next = _hoops_RSGHR->next;
		if (_hoops_ISAI (_hoops_RSGHR) <= 0)
			HI_Free_Polyedge (_hoops_RSGHR);
	} while ((_hoops_RSGHR = next) != null);
}

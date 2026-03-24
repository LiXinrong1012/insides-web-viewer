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
 * $Id: obf_tmp.txt 1.62 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "hi_proto.h"
#include "hpserror.h"


typedef struct _hoops_ASGHR {
	struct _hoops_ASGHR		*_hoops_CGHPR,
								*_hoops_SGHPR,
								*up;
	struct _hoops_ASGHR		*_hoops_GRHPR;

	int							length;
	int							*indices;

	_hoops_PSGHR	_hoops_SACI; /* _hoops_CGHI _hoops_PGGA _hoops_GAAP _hoops_PISC */
} Temp_Polymarker;



local void _hoops_CSHPR (
	Temp_Polymarker			*tm,
	Temp_Polymarker			**_hoops_SSHPR) {
	Temp_Polymarker			*node;

	/*
	 * _hoops_ASHPR _hoops_RGR _hoops_CCAH _hoops_IRHP-_hoops_PAAI _hoops_HPP _hoops_IGRI _hoops_PIRA
	 * _hoops_CRGR _hoops_IRS _hoops_PSHPR _hoops_HHIS. _hoops_IPCP _hoops_CARA _hoops_HRGR _hoops_IS _hoops_SHH _hoops_SHSS _hoops_IS
	 * _hoops_SSS _hoops_RH _hoops_HSHPR-_hoops_IGRI _hoops_PAAI _hoops_ISHPR
	 * _hoops_SPHR.
	 */

	tm->_hoops_CGHPR = null;
	tm->_hoops_SGHPR = null;

	if ((node = *_hoops_SSHPR) == null) {		/* _hoops_RH _hoops_SRS _hoops_SPR */
		*_hoops_SSHPR = tm;
		tm->_hoops_GRHPR = null;
		tm->up = null;
	}
	else _hoops_PCCAR {
		if (_hoops_HSGHR (tm->_hoops_SACI,
										 node->_hoops_SACI)) {
			/* _hoops_SCH'_hoops_GRI _hoops_PCCP _hoops_CGCH _hoops_PSSP; _hoops_AGGAR _hoops_SCH _hoops_GGR _hoops_GGR _hoops_IRS _hoops_IISGR _hoops_HIGR. */
			/* _hoops_PAGA: _hoops_ISGHR _hoops_CCGI _hoops_PPR _hoops_AHHA, _hoops_SR _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_GHIS */
			tm->_hoops_GRHPR = node->_hoops_GRHPR;
			node->_hoops_GRHPR = tm;
			tm->up = node->up;
			return;
		}
#ifndef _hoops_CSGHR
		else if (_hoops_SSGHR (tm->_hoops_SACI,
											 node->_hoops_SACI)) {
			if (node->_hoops_CGHPR != null) node = node->_hoops_CGHPR;
			else {
				/* _hoops_PPSI _hoops_GGSR _hoops_IRS _hoops_CCAH '_hoops_CRGP' _hoops_RIIS */

				/*
				 * _hoops_IPCP _hoops_CCAH _hoops_GIIS _hoops_SHR _hoops_IAGA _hoops_GGSR _hoops_GAR _hoops_RH _hoops_RIIS, _hoops_HRII _hoops_HSAR
				 * _hoops_RH _hoops_RHGS _hoops_GIIS "_hoops_PGIPR" _hoops_HGIPR _hoops_ISHP _hoops_RRGI _hoops_SCH. _hoops_HGI _hoops_IGIPR
				 * _hoops_SGS _hoops_GPHA _hoops_IGRI _hoops_PSHPR _hoops_HSH _hoops_PPPPR'_hoops_RA _hoops_CGIPR-_hoops_SGIPR _hoops_SHH
				 * _hoops_GRIPR _hoops_RRIPR.
				 */
				node->_hoops_CGHPR = tm;
				tm->up = node;
				tm->_hoops_GRHPR = null;
				return;
			}
		}
		else {
			if (node->_hoops_SGHPR != null) node = node->_hoops_SGHPR;
			else {
				/* _hoops_PPSI _hoops_GGSR _hoops_IRS _hoops_CCAH '_hoops_RRPAR' _hoops_RIIS */

				node->_hoops_SGHPR = tm;
				tm->up = node;
				tm->_hoops_GRHPR = null;
				return;
			}
		}
#endif
	}
}



/*
 * _hoops_IGPP (_hoops_PPR _hoops_HASC) "_hoops_IRHP" _hoops_PSSI _hoops_IS _hoops_ARPR _hoops_HPHR _hoops_ARIPR
 */
local void _hoops_PRIPR (
	Temp_Polymarker			*tm,
	Polyhedron			*_hoops_IPRI) {
	Temp_Polymarker			*_hoops_GGRHR;

	if (tm == null) return;		/* _hoops_IIP _hoops_IRIPR */

	/*
	 * _hoops_IPCP _hoops_CRIPR _hoops_HAPR _hoops_ARI _hoops_SRIPR _hoops_ARR _hoops_IH _hoops_GRR _hoops_ARP _hoops_IIGR
	 * _hoops_HAGH-_hoops_AIRC _hoops_SARGR _hoops_PSSI.
	 */
	do {
		int						total;

		/*
		 * _hoops_SSS _hoops_IRS _hoops_RIIS
		 */
		_hoops_PCCAR {
			if (tm->_hoops_CGHPR != null) tm = tm->_hoops_CGHPR;
			else if (tm->_hoops_SGHPR != null) tm = tm->_hoops_SGHPR;
			else break;
		}

		/*
		 * _hoops_RAIPR _hoops_RGR _hoops_RIIS _hoops_HII _hoops_RH _hoops_HHIS
		 */
		if ((_hoops_GGRHR = tm->up) != null) {
			if (tm == _hoops_GGRHR->_hoops_CGHPR)
				_hoops_GGRHR->_hoops_CGHPR = null;
			else
				_hoops_GGRHR->_hoops_SGHPR = null;
		}

		/*
		 * _hoops_RPR _hoops_GH _hoops_RSH _hoops_GSGS _hoops_GC _hoops_SR'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_RRP _hoops_IH _hoops_RGR _hoops_PAAI.
		 */
		total = 0;
		{
			Temp_Polymarker *save = tm;

			do total += tm->length;
			while ((tm = tm->_hoops_GRHPR) != null);
			tm = save;
		}

		/*
		 * _hoops_GPIPR _hoops_RH _hoops_HPHR _hoops_PAAI _hoops_HA. _hoops_HIAA.
		 */
		{
			int					*_hoops_PAGR;
			Temp_Polymarker		*next;
			Polymarker			*_hoops_RGRHR;

			ZALLOC (_hoops_RGRHR, Polymarker);
			_hoops_ICAI(_hoops_RGRHR);
			_hoops_RGRHR->_hoops_GSCP = _hoops_IPRI;
			_hoops_RGRHR->bounding = _hoops_IPRI->bounding;
			_hoops_RGRHR->next = _hoops_IPRI->_hoops_GIGPR;
			_hoops_IPRI->_hoops_GIGPR = _hoops_RGRHR;
			COPY_ONE_VERTEX_ATTRIBUTES (tm->_hoops_SACI,
										_hoops_RGRHR->_hoops_SACI);
			_hoops_RGRHR->same_colors = _hoops_PAIPR;

			ALLOC_ARRAY (_hoops_PAGR, total, int);
			_hoops_RGRHR->_hoops_AIHA = _hoops_PAGR;
			_hoops_RGRHR->_hoops_RAHH |= _hoops_AAHH;
			_hoops_RGRHR->length = total;
			_hoops_RGRHR->_hoops_IPII = total;

			do {
				int				*in;
				int				*_hoops_PPIPR;

				in = tm->indices;
				_hoops_PPIPR = in + tm->length;
				do *_hoops_PAGR++ = *in++;
				_hoops_RGGA (in == _hoops_PPIPR);

				next = tm->_hoops_GRHPR;
				FREE_ARRAY (tm->indices, tm->length, int);
				FREE (tm, Temp_Polymarker);
			}  _hoops_RGGA ((tm = next) == null);

			/* _hoops_GHHR _hoops_HIGR */
		}
	} while ((tm = _hoops_GGRHR) != null);
}


GLOBAL_FUNCTION _hoops_GSPGR HI_Assemble_3D_Polymarkers (
	Polyhedron			*_hoops_IPRI,
	Local_Vertex_Flags	_hoops_HGSPR) {

	_hoops_GSPGR					_hoops_RSPGR, _hoops_ASPGR;

	_hoops_RSPGR = HI_What_Time();

	if (_hoops_IPRI->_hoops_GIGPR != null) {
#ifdef _hoops_IGSPR
# ifdef _hoops_CGSPR
		_hoops_SGSPR (HEC_INFO, HES_REBUILDING_TRISTRIP,
				_hoops_GRSPR (null, "Rebuilding polymarkers for polyhedron %k", &_hoops_IPRI));
# endif
#endif
		HI_Free_Polymarker_List (_hoops_IPRI->_hoops_GIGPR);
		_hoops_IPRI->_hoops_GIGPR = null;
	}

	/* _hoops_PSRAR _hoops_RH _hoops_SIGR _hoops_SGI _hoops_ISHP _hoops_IS _hoops_RH _hoops_CGSI _hoops_SR _hoops_SIPGR'_hoops_RA _hoops_IIAC _hoops_APIP _hoops_GAPR. */
	_hoops_HGSPR &= ~_hoops_IPRI->_hoops_AGRHR;

	/* _hoops_PPR _hoops_HSPP _hoops_ARSPR _hoops_SGS _hoops_SR'_hoops_RISP _hoops_CPHR _hoops_SCH */
	_hoops_IPRI->_hoops_AGRHR |= _hoops_HGSPR;

	if (_hoops_IPRI->point_count == 0) 
		goto _hoops_PRSPR; /* _hoops_HCR _hoops_CPHR */

	/* _hoops_HHSA _hoops_IRS _hoops_AIRI _hoops_HIGR _hoops_HRSPR */
	{
		Polymarker *			pm;

		if ((pm = _hoops_IPRI->_hoops_GIGPR) != null) do {
			_hoops_GACR *		dl;

			if ((dl = pm->_hoops_GAHA) != null) do {
				dl->_hoops_GSAI = (_hoops_GHGI)0xffffffff;
			} while ((dl = dl->next) != null);
		} while ((pm = pm->next) != null);
	}

	/*
	 * _hoops_RAIGR _hoops_CPHAR _hoops_CCA _hoops_PSP _hoops_GPHA _hoops_AIRC _hoops_HRGR _hoops_PGRHR _hoops_RCAC _hoops_IS _hoops_RGHH _hoops_HSAR
	 * _hoops_SPR _hoops_HGRHR _hoops_CCA _hoops_IGRHR.
	 */
	if ((BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) && _hoops_IPRI->local_vertex_attributes.flags == null) ||
		(!BIT(_hoops_IPRI->polyhedron_flags, _hoops_CGRHR) && _hoops_IPRI->local_vertex_attributes._hoops_SGRHR == 0)) {
		int				count = _hoops_IPRI->point_count;
		Polymarker *	_hoops_RGRHR;

		ZALLOC (_hoops_RGRHR, Polymarker);
		_hoops_ICAI(_hoops_RGRHR);
		_hoops_RGRHR->_hoops_GSCP = _hoops_IPRI;
		_hoops_RGRHR->bounding = _hoops_IPRI->bounding;
		_hoops_RGRHR->next = _hoops_IPRI->_hoops_GIGPR;
		_hoops_IPRI->_hoops_GIGPR = _hoops_RGRHR;
		_hoops_GRRHR (_hoops_RGRHR->_hoops_SACI);
		_hoops_RGRHR->same_colors = _hoops_PAIPR;

		_hoops_RGRHR->length = count;
		_hoops_RGRHR->_hoops_IPII = 0;
	}
	else {
		int								index = 0;
		Temp_Polymarker					*temps = null;
		Local_Vertex_Attributes				*_hoops_SPRI;

		_hoops_SPRI = &_hoops_IPRI->local_vertex_attributes;

		_hoops_RGGA (index == _hoops_IPRI->point_count) {
			Temp_Polymarker *tm;
			int				_hoops_RRRHR;

			ALLOC (tm, Temp_Polymarker);
			_hoops_GRRHR (tm->_hoops_SACI);
			_hoops_ARRHR (_hoops_SPRI, index, tm->_hoops_SACI);

			_hoops_RRRHR = index + 1;
			_hoops_RGGA (_hoops_RRRHR == _hoops_IPRI->point_count ||
				   !_hoops_PRRHR (_hoops_SPRI, _hoops_RRRHR, tm->_hoops_SACI))
				   ++_hoops_RRRHR;

			{
				int				count = _hoops_RRRHR - index;
				int				*_hoops_PAGR;

				tm->length = count;
				ALLOC_ARRAY_CACHED (_hoops_PAGR, count, int);
				tm->indices = _hoops_PAGR;
				_hoops_RGGA (index == _hoops_RRRHR) *_hoops_PAGR++ = index++;
			}

			_hoops_CSHPR (tm, &temps);
		}

		_hoops_PRIPR (temps, _hoops_IPRI);
	}

	/* ('_hoops_IIGHR' _hoops_SGI _hoops_HS _hoops_AIAH _hoops_RPII _hoops_ARP) */

_hoops_PRSPR:
	_hoops_ASPGR = HI_What_Time();
	return (_hoops_ASPGR - _hoops_RSPGR) / _hoops_HSPGR;
}



GLOBAL_FUNCTION void HI_Free_Polymarker (
	Polymarker *			pm) {

	if (pm->_hoops_IPII && BIT (pm->_hoops_RAHH, _hoops_AAHH))
		FREE_ARRAY (pm->_hoops_AIHA, pm->_hoops_IPII, int);

	if (pm->points != null && BIT (pm->_hoops_RAHH, _hoops_AIPI))
		FREE_ARRAY_ALIGNED (pm->points, pm->point_count, Point, 16);

#ifndef DISABLE_GEOMETRY_ATTRIBUTES
#  ifndef _hoops_GCGHR
	if (pm->_hoops_PCHA != null && BIT (pm->_hoops_RAHH, _hoops_PIPI))
		FREE_ARRAY (pm->_hoops_PCHA, pm->point_count, RGB);
	if (pm->_hoops_RGIA != null && BIT (pm->_hoops_RAHH, _hoops_HRRHR))
		FREE_ARRAY (pm->_hoops_RGIA, pm->point_count, RGBAS32);
	if (pm->_hoops_HCHA != null && BIT (pm->_hoops_RAHH, _hoops_RCGHR))
		FREE_ARRAY (pm->_hoops_HCHA, pm->point_count, _hoops_ACGHR);
#  endif

#  ifndef _hoops_HCGHR
	if (pm->_hoops_ICHA != null && BIT (pm->_hoops_RAHH, _hoops_ICGHR))
		FREE_ARRAY (pm->_hoops_ICHA, pm->point_count, Vector);
#  endif

#  ifndef DISABLE_TEXTURING
	if (pm->_hoops_CCHA != null && BIT (pm->_hoops_RAHH, _hoops_CCGHR))
		FREE_ARRAY (pm->_hoops_CCHA, pm->point_count * pm->_hoops_GSHA, _hoops_RSSH);
#  endif
#endif

   if (pm->_hoops_GAHA) {
        _hoops_GACR *      dl;

        while ((dl = pm->_hoops_GAHA) != null) {
            pm->_hoops_GAHA = dl->next;
            _hoops_HPRH(dl);
        }
    }

	pm->bounding.release();
	FREE (pm, Polymarker);
}


GLOBAL_FUNCTION void HI_Free_Polymarker_List (
	Polymarker *			pm) {
	Polymarker	*			next;

	if (pm) do {
		next = pm->next;
		HI_Free_Polymarker (pm);
	} while ((pm = next) != null);
}


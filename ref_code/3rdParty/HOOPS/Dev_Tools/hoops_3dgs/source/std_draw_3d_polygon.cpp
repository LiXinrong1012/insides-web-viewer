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
 * $Id: obf_tmp.txt 1.140 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "adt.h"



typedef int		_hoops_RHIIS;

struct _hoops_AHIIS;
struct Edge_Interval;

struct Edge_End {
	Edge_End alter *		next;			/* _hoops_IH _hoops_HSSP */
	Edge_End alter *		_hoops_PHIIS; /* _hoops_IH _hoops_GHIS _hoops_SACPR _hoops_HIGR */
	Edge_Interval alter *	edge;
	_hoops_AHIIS alter *	_hoops_HARIR;
	DC_Point alter *		point;
	int						_hoops_HHIIS;
	bool					_hoops_IHIIS;
	_hoops_RHIIS			_hoops_PPRCP;
#	define _hoops_CHIIS				(_hoops_RHIIS)0
#	define _hoops_SHIIS			(_hoops_RHIIS)1	 /* _hoops_PIHA _hoops_SHH _hoops_GGR _hoops_AGR! */
#	define _hoops_GIIIS			(_hoops_RHIIS)2
#	define _hoops_RIIIS			(_hoops_RHIIS)3
#	define _hoops_AIIIS		(_hoops_RHIIS)4
};

struct _hoops_AHIIS {
	Edge_End alter *	start;
	Edge_End alter *	end;
};

struct Edge_Interval {
	Edge_Interval alter *	prev;
	Edge_End				start;
	Edge_End				end;
};



#ifndef DISABLE_DRAW_3D
/*
	_hoops_PIIIS _hoops_HHGS:

	_hoops_SAAAA _hoops_CCA _hoops_SGCRP _hoops_ARRSH _hoops_GA'_hoops_RA _hoops_HCAAS _hoops_RPHR _hoops_CGPR _hoops_IHGIP _hoops_GSAS.
*/


#define _hoops_HIIIS(nr, _hoops_IHCR, count, points, geom) do {										\
	if (BIT ((_hoops_IHCR)->flags, _hoops_GRHH) ||												\
		BIT ((nr)->_hoops_IRR->_hoops_PPH, _hoops_HPH))	\
		HD_Draw_Lighted_Face (nr, count, points, (Geometry const *)geom);				\
	else																					\
		_hoops_HRPIP (nr, count, points);												\
	} while (0)

#define _hoops_IIIIS(nr, _hoops_IHCR, count, points, geom) do {									\
	if (BIT ((_hoops_IHCR)->flags, _hoops_GRHH) ||												\
		BIT ((nr)->_hoops_IRR->_hoops_PPH, _hoops_HPH))	\
		HD_Draw_Lighted_Polygon (nr, count, points, (Geometry const *)geom);				\
	else if ((nr)->_hoops_RSGC->action.draw_dc_face != nullroutine ||							\
			 (nr)->_hoops_RSGC->action.draw_dc_edge != nullroutine)							\
		HD_Std_DC_Polygon (nr, count, points);												\
	else																					\
		_hoops_PSGCP (nr, count, points);											\
	} while (0)

#define _hoops_CIIIS(nr, _hoops_IHCR, count, points) do {		\
		_hoops_SRPIP (nr, count, points);			\
	} while (0)


#define _hoops_SIIIS	 100
#define _hoops_GCIIS	 3 /* _hoops_RSH _hoops_AHPH _hoops_IACH _hoops_RRI _hoops_IIPR _hoops_RSSA _hoops_HSAR
									 _hoops_CIIA _hoops_RSSA _hoops_IIH _hoops_SIAS *_hoops_GCAS* _hoops_SHH. */

#define _hoops_RCIIS(nr, _hoops_AGRSH, _hoops_PGRSH, _hoops_HGRSH, x1, _hoops_AGSIR, _hoops_HGSIR, _hoops_PAGR) \
		_hoops_ACIIS(nr, x1, _hoops_AGSIR, _hoops_HGSIR, _hoops_AGRSH, _hoops_PGRSH, _hoops_HGRSH, _hoops_PAGR)


/* _hoops_GIGHR: _hoops_SCH _hoops_HRGR _hoops_PCIIS _hoops_IS _hoops_HSPH '_hoops_PHGHR' _hoops_GGR _hoops_ISCP _hoops_GSSP _hoops_HSAR '_hoops_ACGGA'
 * _hoops_PGGA _hoops_RH _hoops_CRHRH "_hoops_SISR = _hoops_HCIIS * _hoops_IIHAS + _hoops_HIHAS" _hoops_HRGR _hoops_AHPS _hoops_IS _hoops_GPPS
 * _hoops_HHGS _hoops_CGPR _hoops_HIHAS _hoops_PPR _hoops_HCIIS*_hoops_IIHAS _hoops_CHR _hoops_GIPR _hoops_CSACI. _hoops_CGP _hoops_SPR _hoops_HRGR '_hoops_PHGHR', _hoops_SGS
 * _hoops_RGSC _hoops_GHACP _hoops_SGS _hoops_HIHAS _hoops_HRGR _hoops_HAR '_hoops_CSACI', _hoops_PRGPR _hoops_HRGPR _hoops_RH _hoops_ARPC.
 */

local _hoops_GRCAR _hoops_ACIIS (
	Net_Rendition const &		nr,
	float						_hoops_AGRSH,
	float						_hoops_PGRSH,
	float						_hoops_HGRSH,
	float						x1,
	float						_hoops_AGSIR,
	float						_hoops_HGSIR,
	DC_Point alter *			_hoops_PAGR) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	float						_hoops_HSHGA, _hoops_ISHGA,
								_hoops_ICIIS = 1.0f,
								a,
								_hoops_SACC;
	_hoops_GRCAR					_hoops_PPRCP = _hoops_HCRCP;
	Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if ((_hoops_HSHGA = x1 - _hoops_AGRSH) < 0.0f) {
		if (x1 < _hoops_GPHH.left-_hoops_CCIIS) {
			_hoops_ICIIS = (_hoops_GPHH.left-_hoops_CCIIS - _hoops_AGRSH) / _hoops_HSHGA;
			_hoops_PPRCP = _hoops_SCIIS;
		}
	}
	else {
		if (x1 > _hoops_GPHH.right+_hoops_CCIIS) {
			_hoops_ICIIS = (_hoops_GPHH.right+_hoops_CCIIS - _hoops_AGRSH) / _hoops_HSHGA;
			_hoops_PPRCP = CC_OFF_TO_RIGHT;
		}
	}

	if ((_hoops_ISHGA = _hoops_AGSIR - _hoops_PGRSH) < 0.0f) {
		if (_hoops_AGSIR < _hoops_GPHH.bottom-_hoops_CCIIS) {
			a = (_hoops_GPHH.bottom-_hoops_CCIIS - _hoops_PGRSH) / _hoops_ISHGA;
			if (_hoops_ICIIS >= a) {
				_hoops_ICIIS = a;
				_hoops_PPRCP = CC_OFF_TO_BOTTOM;
			}
		}
	}
	else {
		if (_hoops_AGSIR > _hoops_GPHH.top+_hoops_CCIIS) {
			a = (_hoops_GPHH.top+_hoops_CCIIS - _hoops_PGRSH) / _hoops_ISHGA;
			if (_hoops_ICIIS >= a) {
				_hoops_ICIIS = a;
				_hoops_PPRCP = _hoops_GSIIS;
			}
		}
	}

	_hoops_PAGR->x = _hoops_ICIIS * _hoops_HSHGA + _hoops_AGRSH;
	_hoops_PAGR->y = _hoops_ICIIS * _hoops_ISHGA + _hoops_PGRSH;
	if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC)) {
		_hoops_SACC = _hoops_ICIIS * (_hoops_HGSIR - _hoops_HGRSH) + _hoops_HGRSH;
		_hoops_PAGR->z = _hoops_IGSC (_hoops_SACC, _hoops_IHCR);
	}
	else
		_hoops_PAGR->z = 0.0f;

	return _hoops_PPRCP;
}


local bool _hoops_RSIIS (
	Net_Rendition const &		nr,
	float						_hoops_AGRSH,
	float						_hoops_PGRSH,
	float						_hoops_HGRSH,
	float						x1,
	float						_hoops_AGSIR,
	float						_hoops_HGSIR,
	DC_Point alter *			_hoops_PAGR,
	Edge_Interval alter *		edge,
	bool						_hoops_ASIIS) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	float						_hoops_HSHGA, _hoops_ISHGA,
								_hoops_PSIIS = 0.0f,
								_hoops_ICIIS = 1.0f,
								a,
								_hoops_SACC;
	_hoops_GRCAR					_hoops_HSIIS = _hoops_HCRCP,
								_hoops_ISIIS = _hoops_HCRCP;
	Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if ((_hoops_HSHGA = x1 - _hoops_AGRSH) > 0.0f) {
		if (_hoops_AGRSH < _hoops_GPHH.left-_hoops_CCIIS) {
			if (x1 < _hoops_GPHH.left-_hoops_CCIIS) return false;
			_hoops_PSIIS = (_hoops_GPHH.left-_hoops_CCIIS - _hoops_AGRSH) / _hoops_HSHGA;
			_hoops_HSIIS = _hoops_SCIIS;
		}

		if (x1 > _hoops_GPHH.right+_hoops_CCIIS) {
			if (_hoops_AGRSH > _hoops_GPHH.right+_hoops_CCIIS) return false;
			_hoops_ICIIS = (_hoops_GPHH.right+_hoops_CCIIS - _hoops_AGRSH) / _hoops_HSHGA;
			_hoops_ISIIS = CC_OFF_TO_RIGHT;
		}
	}
	else {
		if (x1 < _hoops_GPHH.left-_hoops_CCIIS) {
			if (_hoops_AGRSH < _hoops_GPHH.left-_hoops_CCIIS) return false;
			_hoops_ICIIS = (_hoops_GPHH.left-_hoops_CCIIS - _hoops_AGRSH) / _hoops_HSHGA;
			_hoops_ISIIS = _hoops_SCIIS;
		}

		if (_hoops_AGRSH > _hoops_GPHH.right+_hoops_CCIIS) {
			if (x1 > _hoops_GPHH.right+_hoops_CCIIS) return false;
			_hoops_PSIIS = (_hoops_GPHH.right+_hoops_CCIIS - _hoops_AGRSH) / _hoops_HSHGA;
			_hoops_HSIIS = CC_OFF_TO_RIGHT;
		}
	}

	if ((_hoops_ISHGA = _hoops_AGSIR - _hoops_PGRSH) > 0.0f) {
		if (_hoops_PGRSH < _hoops_GPHH.bottom-_hoops_CCIIS) {
			if (_hoops_AGSIR < _hoops_GPHH.bottom-_hoops_CCIIS) return false;
			a = (_hoops_GPHH.bottom-_hoops_CCIIS - _hoops_PGRSH) / _hoops_ISHGA;
			if (_hoops_PSIIS <= a) {
				_hoops_PSIIS = a;
				_hoops_HSIIS = CC_OFF_TO_BOTTOM;
			}
		}

		if (_hoops_AGSIR > _hoops_GPHH.top+_hoops_CCIIS) {
			if (_hoops_PGRSH > _hoops_GPHH.top+_hoops_CCIIS) return false;
			a = (_hoops_GPHH.top+_hoops_CCIIS - _hoops_PGRSH) / _hoops_ISHGA;
			if (_hoops_ICIIS >= a) {
				_hoops_ICIIS = a;
				_hoops_ISIIS = _hoops_GSIIS;
			}
		}
	}
	else {
		if (_hoops_AGSIR < _hoops_GPHH.bottom-_hoops_CCIIS) {
			if (_hoops_PGRSH < _hoops_GPHH.bottom-_hoops_CCIIS) return false;
			a = (_hoops_GPHH.bottom-_hoops_CCIIS - _hoops_PGRSH) / _hoops_ISHGA;
			if (_hoops_ICIIS >= a) {
				_hoops_ICIIS = a;
				_hoops_ISIIS = CC_OFF_TO_BOTTOM;
			}
		}

		if (_hoops_PGRSH > _hoops_GPHH.top+_hoops_CCIIS) {
			if (_hoops_AGSIR > _hoops_GPHH.top+_hoops_CCIIS) return false;
			a = (_hoops_GPHH.top+_hoops_CCIIS - _hoops_PGRSH) / _hoops_ISHGA;
			if (_hoops_PSIIS <= a) {
				_hoops_PSIIS = a;
				_hoops_HSIIS = _hoops_GSIIS;
			}
		}
	}

	if (_hoops_ICIIS < _hoops_PSIIS) return false;

	/* _hoops_CSIIS _hoops_CIPH: _hoops_RPP _hoops_CAASH/_hoops_SRRAA/_hoops_SSIIS _hoops_CHR _hoops_SHRII _hoops_CHPP _hoops_PPR _hoops_HCIIS _hoops_HRGR _hoops_CPPPR _hoops_GGGR
	 * _hoops_IS 1, _hoops_RH "_hoops_HIHAS + _hoops_HCIIS * _hoops_CAASH" _hoops_SGHCA _hoops_GRS _hoops_HS _hoops_GPPS _hoops_HHGS
	 * _hoops_GPP _hoops_RH +, _hoops_PGAP _hoops_GRS _hoops_SHH _hoops_IRCC _hoops_IS _hoops_GGCR _hoops_PGCR _hoops_CSACI _hoops_RGGHR _hoops_IS _hoops_RCRP _hoops_IRS
	 * _hoops_GHAR _hoops_PHI. _hoops_ICCHA, _hoops_RPP _hoops_HIHAS _hoops_HRGR _hoops_CSACI _hoops_PPR _hoops_RCRIA _hoops_HRGR _hoops_GHAR, _hoops_IIH
	 * _hoops_GRS _hoops_SHH _hoops_GPPS _hoops_ARPC. _hoops_CGP _hoops_RH _hoops_HSPH _hoops_HAGA _hoops_HRGR _hoops_AAGIR, _hoops_RGR
	 * _hoops_ARPC _hoops_GGCIS. _hoops_PS _hoops_HHSHH _hoops_RGR _hoops_PISC _hoops_AGIR _hoops_HPP _hoops_PGIAS.
	 */
	if (_hoops_PSIIS > _hoops_SHRSP) {
		if (!_hoops_ASIIS) /* _hoops_RPP _hoops_HAR _hoops_CISS _hoops_ISCP _hoops_IRIPR */
			return _hoops_RSIIS (nr, x1, _hoops_AGSIR, _hoops_HGSIR, _hoops_AGRSH, _hoops_PGRSH, _hoops_HGRSH,
										 _hoops_PAGR, edge, true);
		else
			return false;
	}

	edge->start.point = _hoops_PAGR;
	edge->start._hoops_PPRCP = _hoops_HSIIS;
	_hoops_PAGR->x = _hoops_PSIIS * _hoops_HSHGA + _hoops_AGRSH;
	_hoops_PAGR->y = _hoops_PSIIS * _hoops_ISHGA + _hoops_PGRSH;
	if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC)) {
		_hoops_SACC = _hoops_PSIIS * (_hoops_HGSIR - _hoops_HGRSH) + _hoops_HGRSH;
		_hoops_PAGR->z = _hoops_IGSC (_hoops_SACC, _hoops_IHCR);
	}
	else
		_hoops_PAGR->z = 0.0f;
	++_hoops_PAGR;

	edge->end.point = _hoops_PAGR;
	edge->end._hoops_PPRCP = _hoops_ISIIS;
	_hoops_PAGR->x = _hoops_ICIIS * _hoops_HSHGA + _hoops_AGRSH;
	_hoops_PAGR->y = _hoops_ICIIS * _hoops_ISHGA + _hoops_PGRSH;
	if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC)) {
		_hoops_SACC = _hoops_ICIIS * (_hoops_HGSIR - _hoops_HGRSH) + _hoops_HGRSH;
		_hoops_PAGR->z = _hoops_IGSC (_hoops_SACC, _hoops_IHCR);
	}
	else
		_hoops_PAGR->z = 0.0f;

	return true;
}


local void _hoops_RGCIS (
	Net_Rendition const &		nr,
	DC_Point alter *			point,
	Geometry const *			geometry) 
{
	_hoops_ARPA						plane;

	if (!_hoops_PGSC (nr->transform_rendition->_hoops_HGSC))
		point->z = 0.0f;
	else {
		HD_Find_Geometry_Screen_Plane (nr, geometry, &plane);

		if (plane.c == 0)
			point->z = 0.0f;
		else
			point->z = - (plane.a*(float)point->x + plane.b*(float)point->y + plane.d) / plane.c;
	}
}


local void _hoops_AGCIS (
	Net_Rendition const &		nr,
	Polygon const *				polygon) {
	DC_Point					pt[4];
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;

	pt[0].x = _hoops_SGRA->_hoops_HHCAR.left;
	pt[0].y = _hoops_SGRA->_hoops_HHCAR.bottom;
	_hoops_RGCIS (nr, &pt[0], (Geometry const *)polygon);
	pt[1].x = _hoops_SGRA->_hoops_HHCAR.left;
	pt[1].y = _hoops_SGRA->_hoops_HHCAR.top;
	_hoops_RGCIS (nr, &pt[1], (Geometry const *)polygon);
	pt[2].x = _hoops_SGRA->_hoops_HHCAR.right;
	pt[2].y = _hoops_SGRA->_hoops_HHCAR.top;
	_hoops_RGCIS (nr, &pt[2], (Geometry const *)polygon);
	pt[3].x = _hoops_SGRA->_hoops_HHCAR.right;
	pt[3].y = _hoops_SGRA->_hoops_HHCAR.bottom;
	_hoops_RGCIS (nr, &pt[3], (Geometry const *)polygon);

	_hoops_HIIIS (nr, nr->transform_rendition, 4, pt, (Geometry const *)polygon);
}






local Edge_End alter *_hoops_PGCIS (
	Net_Rendition const & nr,
	Edge_End alter		*_hoops_ICHPR,
	Edge_End alter		*_hoops_HGCIS) {

	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;

	Int_Rectangle		_hoops_GPHH = _hoops_IHCR->_hoops_AGAA;
	_hoops_GPHH._hoops_IACHA(_hoops_CCIIS);

	switch (_hoops_ICHPR->_hoops_PPRCP) {
	  case _hoops_SCIIS: {
		  _hoops_ICHPR->_hoops_HHIIS = (int)(_hoops_ICHPR->point->y - _hoops_GPHH.bottom);
	  }	  break;

	  case _hoops_GSIIS: {
		  _hoops_ICHPR->_hoops_HHIIS = (int)(_hoops_GPHH.top-_hoops_GPHH.bottom + /* _hoops_RAAP _hoops_ISHA */
							 _hoops_ICHPR->point->x - _hoops_GPHH.left);	/* _hoops_IGCIS */
	  }	  break;

	  case CC_OFF_TO_RIGHT: {
		  _hoops_ICHPR->_hoops_HHIIS = (int)(_hoops_GPHH.top-_hoops_GPHH.bottom + /* _hoops_RAAP _hoops_ISHA */
							 _hoops_GPHH.right-_hoops_GPHH.left + /* _hoops_SCIA _hoops_ISHA */
							 _hoops_GPHH.top - _hoops_ICHPR->point->y);	/* _hoops_IGCIS */
	  }	  break;

	  default: /* _hoops_AGIR _hoops_CGCIS: */ {
		  _hoops_ICHPR->_hoops_HHIIS = (int)(_hoops_GPHH.top-_hoops_GPHH.bottom + /* _hoops_RAAP _hoops_ISHA */
							 _hoops_GPHH.right-_hoops_GPHH.left + /* _hoops_SCIA _hoops_ISHA */
							 _hoops_GPHH.top-_hoops_GPHH.bottom + /* _hoops_RPHR _hoops_ISHA */
							 _hoops_GPHH.right - _hoops_ICHPR->point->x); /* _hoops_IGCIS */
	  }	  break;
	}

	if (_hoops_HGCIS == null || _hoops_HGCIS->_hoops_HHIIS >= _hoops_ICHPR->_hoops_HHIIS) {
		_hoops_ICHPR->_hoops_PHIIS = _hoops_HGCIS;
		return _hoops_ICHPR;
	}
	else {
		Edge_End alter	*_hoops_SRRGI = _hoops_HGCIS,
											*next;

		_hoops_RGGA ((next = _hoops_SRRGI->_hoops_PHIIS) == null || next->_hoops_HHIIS >= _hoops_ICHPR->_hoops_HHIIS)
			_hoops_SRRGI = next;

		_hoops_ICHPR->_hoops_PHIIS = next;
		_hoops_SRRGI->_hoops_PHIIS = _hoops_ICHPR;
		return _hoops_HGCIS;
	}
}


local DC_Point alter *copy_points_forwards (
	DC_Point const	*in,
	DC_Point const	*_hoops_PPIPR,
	DC_Point alter	*_hoops_PAGR) {

	do {
		_hoops_PAGR->x = in->x;
		_hoops_PAGR->y = in->y;
		_hoops_PAGR->z = in->z;
		++_hoops_PAGR;
	}
	_hoops_RGGA (++in > _hoops_PPIPR);

	return _hoops_PAGR;
}


local DC_Point alter *_hoops_SGCIS (
	DC_Point const	*in,
	DC_Point const	*_hoops_PPIPR,
	DC_Point alter	*_hoops_PAGR) {

	do {
		_hoops_PAGR->x = in->x;
		_hoops_PAGR->y = in->y;
		_hoops_PAGR->z = in->z;
		++_hoops_PAGR;
	}
	_hoops_RGGA (--in < _hoops_PPIPR);

	return _hoops_PAGR;
}


local void _hoops_GRCIS (
	Net_Rendition const &		nr,
	_hoops_AHIIS const *		_hoops_HARIR,
	DC_Point const *			_hoops_RRCIS,
	DC_Point const *			_hoops_ARCIS,
	Geometry const *			_hoops_PRCIS) {
	Edge_End alter *			ee0;
	Edge_End alter *			ee1;
	DC_Point alter *			_hoops_PAGR;
	DC_Point alter *			out_base;
	Integer32					_hoops_SPAH;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	int							count;
	Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	_hoops_SPAH = 0;
	ee0 = _hoops_HARIR->start;

	do if (ee0 == &ee0->edge->start) {
		ee1 = &ee0->edge->end;

		if (ee1->point > ee0->point)
			_hoops_SPAH += ee1->point - ee0->point + 1;
		else /* _hoops_CGRI _hoops_AARI */
			_hoops_SPAH += (_hoops_ARCIS - ee0->point) +
						(ee1->point - _hoops_RRCIS) + 2;
	}
	_hoops_RGGA ((ee0 = ee0->next) == null);

	/* _hoops_IPS _hoops_RH _hoops_RSSA _hoops_CRGR _hoops_IRS _hoops_CCAH _hoops_IISGR _hoops_CRPR */

	_hoops_SPAH += 4 + 1; /* _hoops_HRGI _hoops_AGIR _hoops_ASISR _hoops_RSSA, _hoops_IPSH _hoops_HHHA _hoops_GGGR */
	ALLOC_ARRAY (_hoops_PAGR, _hoops_SPAH, DC_Point);
	out_base = _hoops_PAGR;

	ee0 = _hoops_HARIR->end;
	ee1 = _hoops_HARIR->start;

	do {
		DC_Point alter	*_hoops_GGIAR,
											*p1;

		/* _hoops_GGCR _hoops_IRS _hoops_SPCS _hoops_ISHA _hoops_HII _hoops_HRCIS _hoops_IS _hoops_IRCIS, _hoops_HGIA */
		if (ee0->_hoops_IHIIS) {
			if (ee0->_hoops_PPRCP != ee1->_hoops_PPRCP || ee0->_hoops_HHIIS > ee1->_hoops_HHIIS)
			do switch (ee0->_hoops_PPRCP) {
				case _hoops_SCIIS: {
					_hoops_PAGR->x = _hoops_GPHH.left-_hoops_CCIIS;
					_hoops_PAGR->y = _hoops_GPHH.top+_hoops_CCIIS;
					_hoops_RGCIS (nr, _hoops_PAGR, _hoops_PRCIS);
					++_hoops_PAGR;
					ee0->_hoops_PPRCP = _hoops_GSIIS;
				}	break;

				case _hoops_GSIIS: {
					_hoops_PAGR->x = _hoops_GPHH.right+_hoops_CCIIS;
					_hoops_PAGR->y = _hoops_GPHH.top+_hoops_CCIIS;
					_hoops_RGCIS (nr, _hoops_PAGR, _hoops_PRCIS);
					++_hoops_PAGR;
					ee0->_hoops_PPRCP = CC_OFF_TO_RIGHT;
				}	break;

				case CC_OFF_TO_RIGHT: {
					_hoops_PAGR->x = _hoops_GPHH.right+_hoops_CCIIS;
					_hoops_PAGR->y = _hoops_GPHH.bottom-_hoops_CCIIS;
					_hoops_RGCIS (nr, _hoops_PAGR, _hoops_PRCIS);
					++_hoops_PAGR;
					ee0->_hoops_PPRCP = CC_OFF_TO_BOTTOM;
				}	break;

				case CC_OFF_TO_BOTTOM: {
					_hoops_PAGR->x = _hoops_GPHH.left-_hoops_CCIIS;
					_hoops_PAGR->y = _hoops_GPHH.bottom-_hoops_CCIIS;
					_hoops_RGCIS (nr, _hoops_PAGR, _hoops_PRCIS);
					++_hoops_PAGR;
					ee0->_hoops_PPRCP = _hoops_SCIIS;
				}	break;
			}
			_hoops_RGGA (ee0->_hoops_PPRCP == ee1->_hoops_PPRCP);
		}
		else {
			if (ee0->_hoops_PPRCP != ee1->_hoops_PPRCP || ee0->_hoops_HHIIS < ee1->_hoops_HHIIS)
			do switch (ee0->_hoops_PPRCP) {
				case _hoops_SCIIS: {
					_hoops_PAGR->x = _hoops_GPHH.left-_hoops_CCIIS;
					_hoops_PAGR->y = _hoops_GPHH.bottom-_hoops_CCIIS;
					_hoops_RGCIS (nr, _hoops_PAGR, _hoops_PRCIS);
					++_hoops_PAGR;
					ee0->_hoops_PPRCP = CC_OFF_TO_BOTTOM;
				}	break;

				case CC_OFF_TO_BOTTOM: {
					_hoops_PAGR->x = _hoops_GPHH.right+_hoops_CCIIS;
					_hoops_PAGR->y = _hoops_GPHH.bottom-_hoops_CCIIS;
					_hoops_RGCIS (nr, _hoops_PAGR, _hoops_PRCIS);
					++_hoops_PAGR;
					ee0->_hoops_PPRCP = CC_OFF_TO_RIGHT;
				}	break;

				case CC_OFF_TO_RIGHT: {
					_hoops_PAGR->x = _hoops_GPHH.right+_hoops_CCIIS;
					_hoops_PAGR->y = _hoops_GPHH.top+_hoops_CCIIS;
					_hoops_RGCIS (nr, _hoops_PAGR, _hoops_PRCIS);
					++_hoops_PAGR;
					ee0->_hoops_PPRCP = _hoops_GSIIS;
				}	break;

				case _hoops_GSIIS: {
					_hoops_PAGR->x = _hoops_GPHH.left-_hoops_CCIIS;
					_hoops_PAGR->y = _hoops_GPHH.top+_hoops_CCIIS;
					_hoops_RGCIS (nr, _hoops_PAGR, _hoops_PRCIS);
					++_hoops_PAGR;
					ee0->_hoops_PPRCP = _hoops_SCIIS;
				}	break;
			}
			_hoops_RGGA (ee0->_hoops_PPRCP == ee1->_hoops_PPRCP);
		}

		/* _hoops_GGCR _hoops_RH _hoops_IRCIS _hoops_ISHA */


		if (ee1 == &ee1->edge->start) {
			_hoops_GGIAR = ee1->point;
			p1 = ee1->edge->end.point;

			/* _hoops_GGCR _hoops_RH _hoops_ISHA _hoops_CPIC _hoops_IHIPR _hoops_HII _hoops_CPGAS _hoops_IS _hoops_PARAA */

			if (_hoops_GGIAR < p1) _hoops_PAGR = copy_points_forwards (_hoops_GGIAR, p1, _hoops_PAGR);
			else { /* _hoops_CGRI */
				_hoops_PAGR = copy_points_forwards (_hoops_GGIAR, _hoops_ARCIS, _hoops_PAGR);
				_hoops_PAGR = copy_points_forwards (_hoops_RRCIS, p1, _hoops_PAGR);
			}
		}
		else {
			_hoops_GGIAR = ee1->edge->start.point;
			p1 = ee1->point;

			/* _hoops_GGCR _hoops_RH _hoops_ISHA _hoops_CPIC _hoops_HPIPR _hoops_HII _hoops_PARAA _hoops_IS _hoops_CPGAS */

			if (_hoops_GGIAR < p1) _hoops_PAGR = _hoops_SGCIS (p1, _hoops_GGIAR, _hoops_PAGR);
			else { /* _hoops_CGRI */
				_hoops_PAGR = _hoops_SGCIS (p1, _hoops_RRCIS, _hoops_PAGR);
				_hoops_PAGR = _hoops_SGCIS (_hoops_ARCIS, _hoops_GGIAR, _hoops_PAGR);
			}
		}

		ee0 = ee1->next;
	}
	_hoops_RGGA ((ee1 = ee0->next) == null);

	/* _hoops_GGGR _hoops_RH _hoops_HSP _hoops_GRGA */
	_hoops_PAGR->x = out_base->x;
	_hoops_PAGR->y = out_base->y;
	_hoops_PAGR->z = out_base->z;

	/* _hoops_PGSA _hoops_RH _hoops_RHRH _hoops_AHAP!! */

	count = _hoops_PAGR - out_base + 1;

	if (count < 3) {}
	else
		_hoops_HIIIS (nr, _hoops_IHCR, count, out_base, _hoops_PRCIS);

	FREE_ARRAY (out_base, _hoops_SPAH, DC_Point);
}
#endif


local void _hoops_CRCIS (
	Net_Rendition const & nr,
	Edge_Interval alter			*_hoops_SRCIS,
	DC_Point const				*_hoops_RRCIS,
	DC_Point const				*_hoops_ARCIS,
	bool						_hoops_GACIS,
	Geometry const				*_hoops_PRCIS) {
	Edge_End alter				*_hoops_CCPHS;

	/*
		_hoops_ASHPR _hoops_RH _hoops_ISHA-_hoops_HCPA _hoops_HPP _hoops_CAS _hoops_SSIA _hoops_HSSC _hoops_AARI _hoops_RH _hoops_SACPR
		_hoops_IIGR _hoops_RH _hoops_CIHH _hoops_ARRGR. (_hoops_AGHP _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_ISHA-_hoops_RSGR.)
	*/

	{	Edge_Interval alter	*edge = _hoops_SRCIS;

		_hoops_CCPHS = null;
		do {
			edge->start.edge = edge;
			edge->start._hoops_HARIR = null;
			_hoops_CCPHS = _hoops_PGCIS (nr, &edge->start, _hoops_CCPHS);
			edge->end.edge = edge;
			edge->end._hoops_HARIR = null;
			_hoops_CCPHS = _hoops_PGCIS (nr, &edge->end, _hoops_CCPHS);
		}
		_hoops_RGGA ((edge = edge->prev) == null);
	}

	if (_hoops_GACIS) {
		Edge_End alter	*_hoops_RACIS = _hoops_CCPHS;

		/* _hoops_PHRPS _hoops_RH _hoops_SRS _hoops_PPSR _hoops_ISHP _hoops_IS _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_HIGR */

		do _hoops_CCPHS = _hoops_CCPHS->_hoops_PHIIS;
		_hoops_RGGA (_hoops_CCPHS->_hoops_PHIIS == null);
		_hoops_CCPHS->_hoops_PHIIS = _hoops_RACIS;
		_hoops_CCPHS = _hoops_RACIS->_hoops_PHIIS;
		_hoops_RACIS->_hoops_PHIIS = null;
	}

	do {
		Edge_End alter		*ee0,
												*ee1;
		_hoops_AHIIS alter	*poly0,
												*poly1;

		/* _hoops_ARAS _hoops_AARI _hoops_RH _hoops_SACPR, _hoops_CPIC _hoops_HII _hoops_SIPP _hoops_IS _hoops_ASSA _hoops_IS
		 * _hoops_SIPP _hoops_PGHH, _hoops_AACIS _hoops_RRGP _hoops_IIGR _hoops_ISHA-_hoops_HCPA _hoops_GIRP.
		 */

		ee0 = _hoops_CCPHS;
		ee1 = ee0->_hoops_PHIIS;
		_hoops_CCPHS = ee1->_hoops_PHIIS;

		ee0->_hoops_IHIIS = true;
		ee1->_hoops_IHIIS = false;

		if ((poly0 = ee0->_hoops_HARIR) == null) {	 /* _hoops_HSPP _hoops_IRS _hoops_HSSP */
			Edge_Interval alter			*edge;

			ALLOC (poly0, _hoops_AHIIS);
			edge = ee0->edge;
			poly0->start = &edge->start;
			poly0->end = &edge->end;
			poly0->start->next = poly0->end;
			poly0->end->next = null;
			edge->start._hoops_HARIR = poly0;
			edge->end._hoops_HARIR = poly0;
		}

		/* _hoops_RGR _hoops_SPR _hoops_HRGR *_hoops_ASSA* _hoops_IS *_hoops_SIPP*, _hoops_PACIS _hoops_SCH (_hoops_RPP _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_AIAH) */

		if ((poly1 = ee1->_hoops_HARIR) == null) {/* _hoops_GGCR _hoops_RGR _hoops_ISHA _hoops_IS _hoops_SGS _hoops_SCIRA */
			Edge_End alter		*_hoops_HACIS;

			if (ee1 == &ee1->edge->start)
				_hoops_HACIS = &ee1->edge->end;
			else
				_hoops_HACIS = &ee1->edge->start;

			ee1->_hoops_HARIR = poly0;
			_hoops_HACIS->_hoops_HARIR = poly0;

			if (ee0 == poly0->end) {	/* _hoops_CIGAA _hoops_SCH */
				ee0->next = ee1;
				ee1->next = _hoops_HACIS;
				_hoops_HACIS->next = null;
				poly0->end = _hoops_HACIS;
			}
			else {						/* _hoops_PIPSH _hoops_SCH */
				poly0->start = _hoops_HACIS;
				_hoops_HACIS->next = ee1;
				ee1->next = ee0;
			}
		}
		else if (poly0 != poly1) {		/* _hoops_HASC _hoops_AGCR _hoops_PGCR _hoops_SCSRA */
			Edge_End alter		*ee2;

			/* (_hoops_SR _hoops_PAH _hoops_IACIS _hoops_PCCP _hoops_AIAH-_hoops_IGI-_hoops_HIH-_hoops_HAR-_hoops_CARS _hoops_RSGR-_hoops_PPSR
			 *	_hoops_CGPR _hoops_IIH'_hoops_GRI _hoops_ISHA _hoops_ARRSH _hoops_CPIC _hoops_GPP.)
			 */

			ee2 = poly1->start;
			do ee2->_hoops_HARIR = poly0;
			_hoops_RGGA ((ee2 = ee2->next) == null);

			if (ee0 == poly0->end) {
				if (ee1 == poly1->start) {		/* _hoops_CIGAA _hoops_CACIS */
					ee0->next = ee1;
					poly0->end = poly1->end;
				}
				else {			/* _hoops_RSGR-_hoops_IS-_hoops_RSGR: _hoops_PIIA _hoops_PPR _hoops_CIGAA _hoops_CACIS */
					ee0 = poly1->start;
					ee1 = ee0->next;
					ee0->next = null;
					do {
						ee2 = ee1->next;
						ee1->next = ee0;
						ee0 = ee1;
					}
					_hoops_RGGA ((ee1 = ee2) == null);
					poly0->end->next = poly1->end;
					poly0->end = poly1->start;
				}
			}
			else /* _hoops_RPP (_hoops_HRCIS == _hoops_SACIS->_hoops_HSPP) */ {
				if (ee1 == poly1->end) {		/* _hoops_PIPSH _hoops_CACIS */
					ee1->next = ee0;
					poly0->start = poly1->start;
				}
				else {			/* _hoops_RSGR-_hoops_IS-_hoops_RSGR: _hoops_PIIA _hoops_PPR _hoops_PIPSH _hoops_CACIS */
					ee0 = poly1->start;
					ee1 = ee0->next;
					ee0->next = null;
					do {
						ee2 = ee1->next;
						ee1->next = ee0;
						ee0 = ee1;
					}
					_hoops_RGGA ((ee1 = ee2) == null);
					poly1->start->next = poly0->start;
					poly0->start = poly1->end;
				}
			}
			FREE (poly1, _hoops_AHIIS);
		}
		else {
			/* _hoops_SR _hoops_HHGC _hoops_IS _hoops_GGGR _hoops_IRS _hoops_CGHC _hoops_GAPA _hoops_PGCR _hoops_GPCIS _hoops_ISHA-_hoops_RSGR _hoops_RSSA
			 * _hoops_SGS _hoops_IHPS _hoops_IS _hoops_RPCIS _hoops_IS _hoops_RH _hoops_PSHR _hoops_HSSP. _hoops_CPGP _hoops_ISCP _hoops_HCSPR
			 * _hoops_AAPI _hoops_RGAR _hoops_SGIPR _hoops_HS _hoops_SPR _hoops_CGHC _hoops_GGR _hoops_CAPR _hoops_RGR _hoops_PIHA _hoops_PHGA _hoops_RH
			 * _hoops_HSSP _hoops_HRGR _hoops_APRAR. _hoops_IPGRH _hoops_APCIS!
			 */

			_hoops_GRCIS (nr, poly0, _hoops_RRCIS, _hoops_ARCIS, _hoops_PRCIS);
			FREE (poly0, _hoops_AHIIS);
		}
	}
	_hoops_RGGA (_hoops_CCPHS == null);
}


GLOBAL_FUNCTION void HD_Std_3D_Polygon (
	Net_Rendition const &		inr,
	Polygon const				*polygon) {
#ifndef DISABLE_DRAW_3D
	Net_Rendition				nr = inr;
	Display_Context	alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	_hoops_CIGA				_hoops_SIGA = nr->_hoops_IHA;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	Int_Rectangle const &		_hoops_GPHH = _hoops_IHCR->_hoops_AGAA;
	Point const *				in;
	Point const *				end;
	DC_Point					_hoops_GIHGS[_hoops_SIIIS];
	DC_Point alter *			_hoops_PAGR;
	DC_Point alter *			out_base;
	float						_hoops_SACC;
	bool						_hoops_PPCIS = false;

	dc->_hoops_GSGC |= _hoops_ACIP;
	if (BIT(dc->flags, _hoops_CHSI))
		return;

	if (polygon->count < 2) return;
	in = polygon->points;
	end = in + polygon->count;

	if (BIT (_hoops_IHCR->flags, _hoops_IGSP)||
		ANYBIT (_hoops_IHCR->heuristics, _hoops_SASA|
								_hoops_GPSA) &&
		_hoops_SIGA->color != _hoops_SIGA->_hoops_RGIR) {
		float					c;

		c = HD_Find_Geometry_Screen_Plane_C (nr, (Geometry const *)polygon);
		if (!BIT (_hoops_IHCR->heuristics, _hoops_SASA))
			c = -c;

		if (c < 0) {
			if (BIT (_hoops_IHCR->flags, _hoops_IGSP))
				return;
			else
				_hoops_PPCIS = true;
		}
	}

	if (polygon->count < _hoops_SIIIS/_hoops_GCIIS)
		_hoops_PAGR = _hoops_GIHGS;
	else
		ALLOC_ARRAY (_hoops_PAGR, polygon->count * _hoops_GCIIS, DC_Point);

	out_base = _hoops_PAGR;

	if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE) || _hoops_PPCIS ||
		nr->_hoops_CPP->_hoops_PRH.style == _hoops_GCPI &&
		_hoops_SIGA->_hoops_CHA->_hoops_IRIR < 1.0f) {
		nr.Modify();

		if (_hoops_PPCIS) {
			_hoops_SIGA = nr->_hoops_IHA.Modify();

			Swap (_hoops_SIGA->color, _hoops_SIGA->_hoops_RGIR);
			Swap (_hoops_SIGA->_hoops_CHA, _hoops_SIGA->_hoops_GIA);
		}

		if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE)) {
			_hoops_PSIHP const &		_hoops_HSIHP = nr->_hoops_RSGC;

			/* _hoops_AHHCP _hoops_III _hoops_CCA _hoops_ISHA */
			nr->_hoops_AHP = nr->_hoops_RHP;

			if (nr->_hoops_AHP->weight < 0) {
				Line_Rendition alter &	_hoops_ASGIP = nr->_hoops_AHP.Modify();

				_hoops_ASGIP->weight = (int)(HD_Compute_Generic_Size (nr, _hoops_ASGIP->_hoops_PHP, _hoops_ASGIP->_hoops_HHP, 1.0f, false, 0, true) + 0.5f);

				if (_hoops_ASGIP->_hoops_HHP != GSU_PIXELS && _hoops_ASGIP->_hoops_HHP != GSU_PERCENT && _hoops_ASGIP->_hoops_HHP != GSU_SCALE)
					_hoops_ASGIP->flags |= _hoops_SSGIP;
			}
#if 0
			if (nr->_hoops_AHP->weight > 3 && 
				!ALLBITS(_hoops_CRAI->_hoops_AHP->style, LCAP_ROUND|LJOIN_ROUND)) {
				
				_hoops_CRAI->_hoops_AHP.Modify()->style = LCAP_ROUND|LJOIN_ROUND;
			}
#endif
			if (_hoops_HSIHP->action.draw_dc_polyline != _hoops_HSIHP->action.draw_dc_edge) {
				_hoops_PSIHP alter &	_hoops_PHGRI = nr->_hoops_RSGC.Modify();
				_hoops_PHGRI->action.draw_dc_polyline = _hoops_HSIHP->action.draw_dc_edge;
				_hoops_PHGRI->_hoops_AIACR[_hoops_HRRCR] = _hoops_HSIHP->_hoops_AIACR[_hoops_IRRCR];
				_hoops_PHGRI->_hoops_RGCHP[_hoops_HRRCR] = _hoops_HSIHP->_hoops_RGCHP[_hoops_IRRCR];
			}
		}
	}


	if (!BIT (_hoops_IHCR->heuristics, _hoops_PICAR) ||
		BIT (_hoops_IHCR->flags, _hoops_AIHS)) {
		float					w;

		switch (_hoops_IHCR->_hoops_HGSC) {
			case _hoops_SIPHP: {
				do {
					_hoops_PAGR->x = in->x;
					_hoops_PAGR->y = in->y;
					_hoops_PAGR->z = 0.0f; /* _hoops_CISPP _hoops_HPCIS _hoops_IPCIS _hoops_GSASR */
					++_hoops_PAGR;
				}
				_hoops_RGGA (++in == end);
			}	break;

			case _hoops_CIPHP: {
				do {
					_hoops_PAGR->x = _hoops_PRPPI (elements, in[0]);
					_hoops_PAGR->y = _hoops_HRPPI (elements, in[0]);
					_hoops_PAGR->z = 0.0f; /* _hoops_CISPP _hoops_HPCIS _hoops_IPCIS _hoops_GSASR */
					++_hoops_PAGR;
				}
				_hoops_RGGA (++in == end);
			}			break;

			case _hoops_PCPHP: {
				do {
					_hoops_PAGR->x = _hoops_HPRA (elements, in[0]);
					_hoops_PAGR->y = _hoops_IPRA (elements, in[0]);
					_hoops_PAGR->z = 0.0f; /* _hoops_CISPP _hoops_HPCIS _hoops_IPCIS _hoops_GSASR */
					++_hoops_PAGR;
				}
				_hoops_RGGA (++in == end);
			}			break;

			case _hoops_RCPHP: {
				do {
					if ((w = _hoops_PHCP (elements, in[0])) == 0.0f) {
						/* _hoops_ASAC _hoops_CAPR _hoops_HII _hoops_IAAHH _hoops_HPP _hoops_AHHR... */
						_hoops_PAGR->x = (_hoops_SGRA->_hoops_HHCAR.left + _hoops_SGRA->_hoops_HHCAR.right)/2.0f;
						_hoops_PAGR->y = (_hoops_SGRA->_hoops_HHCAR.bottom + _hoops_SGRA->_hoops_HHCAR.top)/2.0f;
					}
					else {
						_hoops_PAGR->x = _hoops_HPRA (elements, in[0]) / w;
						_hoops_PAGR->y = _hoops_IPRA (elements, in[0]) / w;
					}

					_hoops_PAGR->z = 0.0f; /* _hoops_CISPP _hoops_HPCIS _hoops_IPCIS _hoops_GSASR */
					++_hoops_PAGR;
				}
				_hoops_RGGA (++in == end);
			}			break;

			case _hoops_ACPHP: {
				do {
					_hoops_PAGR->x = _hoops_HPRA (elements, in[0]);
					_hoops_PAGR->y = _hoops_IPRA (elements, in[0]);
					_hoops_SACC = _hoops_CPRA (elements, in[0]);
					_hoops_PAGR->z = _hoops_IGSC (_hoops_SACC, _hoops_IHCR);
					++_hoops_PAGR;
				}
				_hoops_RGGA (++in == end);
			}			break;

			case _hoops_GCPHP: {
				do {
					if ((w = _hoops_PHCP (elements, in[0])) == 0.0f) {
						/* _hoops_ASAC _hoops_CAPR _hoops_HII _hoops_IAAHH _hoops_HPP _hoops_AHHR... */
						_hoops_PAGR->x = (_hoops_SGRA->_hoops_HHCAR.left + _hoops_SGRA->_hoops_HHCAR.right)/2.0f;
						_hoops_PAGR->y = (_hoops_SGRA->_hoops_HHCAR.bottom + _hoops_SGRA->_hoops_HHCAR.top)/2.0f;
						_hoops_PAGR->z = 0.0f;
					}
					else {
						_hoops_PAGR->x = _hoops_HPRA (elements, in[0]) / w;
						_hoops_PAGR->y = _hoops_IPRA (elements, in[0]) / w;
						_hoops_SACC = _hoops_CPRA (elements, in[0]) / w;
						_hoops_PAGR->z = _hoops_IGSC (_hoops_SACC, _hoops_IHCR);
					}
					++_hoops_PAGR;
				}
				_hoops_RGGA (++in == end);
			}			break;
		}

		/* _hoops_HHHA _hoops_GGGR */
		*_hoops_PAGR = *out_base;

		if (!BIT (nr->_hoops_RGP, T_FACES))
			_hoops_CIIIS (nr, _hoops_IHCR, polygon->count+1, out_base);
		else if (!ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE))
			_hoops_HIIIS (nr, _hoops_IHCR, polygon->count, out_base, polygon);
		else
			_hoops_IIIIS (nr, _hoops_IHCR, polygon->count+1, out_base, polygon);
	}
	else /* _hoops_CCA _hoops_CIHH */ {
		float							_hoops_AGRSH, _hoops_PGRSH, _hoops_HGRSH,
										_hoops_APHAS, _hoops_HPHAS, _hoops_CPHAS, _hoops_GHHAS,
										x1 = 0.0f, _hoops_AGSIR = 0.0f, _hoops_HGSIR = 0.0f,
										_hoops_PPHAS = 0.0f, _hoops_IPHAS = 0.0f, _hoops_SPHAS = 0.0f, _hoops_RHHAS = 0.0f,
										_hoops_AHHAS,
										_hoops_GPCCC = 0.0f, _hoops_RPCCC = 0.0f, _hoops_CPCIS = 0.0f,
										_hoops_GCRGA;
		Point const						*_hoops_GIAHR,
										*_hoops_SPCIS = null,
										*_hoops_HSPS;
		_hoops_GRCAR						_hoops_GHCIS,
										_hoops_RHCIS;
		Edge_Interval					_hoops_AHCIS,
										*edge = &_hoops_AHCIS,
										*_hoops_PHCIS;

		bool		_hoops_HHCIS = false;
		bool		done = false;

		_hoops_AHCIS.prev = null;

		switch (_hoops_IHCR->_hoops_HGSC) {
			case _hoops_SIPHP: {
				_hoops_GPCCC = x1 = in->x;
				_hoops_RPCCC = _hoops_AGSIR = in->y;
				_hoops_CPCIS = _hoops_HGSIR = -1.0f;	/* _hoops_CRHR _hoops_IHCIS */
			}	break;

			case _hoops_CIPHP: {
				_hoops_GPCCC = x1 = _hoops_PRPPI (elements, in[0]);
				_hoops_RPCCC = _hoops_AGSIR = _hoops_HRPPI (elements, in[0]);
				_hoops_CPCIS = _hoops_HGSIR = -1.0f;	/* _hoops_CRHR _hoops_IHCIS */
			}	break;

			case _hoops_PCPHP: {
				_hoops_GPCCC = x1 = _hoops_HPRA (elements, in[0]);
				_hoops_RPCCC = _hoops_AGSIR = _hoops_IPRA (elements, in[0]);
				_hoops_CPCIS = _hoops_HGSIR = -1.0f;	/* _hoops_CRHR _hoops_IHCIS */
			}	break;

			case _hoops_ACPHP: {
				_hoops_GPCCC = x1 = _hoops_HPRA (elements, in[0]);
				_hoops_RPCCC = _hoops_AGSIR = _hoops_IPRA (elements, in[0]);
				_hoops_CPCIS = _hoops_HGSIR = _hoops_CPRA (elements, in[0]);
			}	break;

			case _hoops_RCPHP: {
				_hoops_PCCAR {
					_hoops_RHHAS = _hoops_PHCP (elements, in[0]);
					if (_hoops_RHHAS >= _hoops_IHCR->_hoops_CHCR) break;
					if (++in == end)
						return;
				}

				_hoops_PPHAS = _hoops_HPRA (elements, in[0]);
				_hoops_IPHAS = _hoops_IPRA (elements, in[0]);

				_hoops_GPCCC = x1 = _hoops_PPHAS / _hoops_RHHAS;
				_hoops_RPCCC = _hoops_AGSIR = _hoops_IPHAS / _hoops_RHHAS;
				_hoops_CPCIS = _hoops_HGSIR = -1.0f;	/* _hoops_CRHR _hoops_IHCIS */
			}	break;

			case _hoops_GCPHP: {
				_hoops_PCCAR {
					_hoops_RHHAS = _hoops_PHCP (elements, in[0]);
					if (_hoops_RHHAS >= _hoops_IHCR->_hoops_CHCR) break;
					if (++in == end)
						return;
				}

				_hoops_PPHAS = _hoops_HPRA (elements, in[0]);
				_hoops_IPHAS = _hoops_IPRA (elements, in[0]);
				_hoops_SPHAS = _hoops_CPRA (elements, in[0]);

				_hoops_GPCCC = x1 = _hoops_PPHAS / _hoops_RHHAS;
				_hoops_RPCCC = _hoops_AGSIR = _hoops_IPHAS / _hoops_RHHAS;
				_hoops_CPCIS = _hoops_HGSIR = _hoops_SPHAS / _hoops_RHHAS;
			}	break;
		}

		_hoops_GIAHR = in;

		if (x1 < _hoops_GPHH.left-_hoops_CCIIS) _hoops_RHCIS = _hoops_SCIIS;
		else if (x1 > _hoops_GPHH.right+_hoops_CCIIS) _hoops_RHCIS = CC_OFF_TO_RIGHT;
		else if (_hoops_AGSIR < _hoops_GPHH.bottom-_hoops_CCIIS) _hoops_RHCIS = CC_OFF_TO_BOTTOM;
		else if (_hoops_AGSIR > _hoops_GPHH.top+_hoops_CCIIS) _hoops_RHCIS = _hoops_GSIIS;
		else _hoops_RHCIS = _hoops_HCRCP;

		do {
			_hoops_GHCIS = _hoops_RHCIS;

			if (++in == end) in = polygon->points;
			if (in == _hoops_GIAHR) done = true;

			_hoops_AGRSH = x1;
			_hoops_PGRSH = _hoops_AGSIR;
			_hoops_HGRSH = _hoops_HGSIR;

			switch (_hoops_IHCR->_hoops_HGSC) {
				case _hoops_SIPHP: {
					if (in == _hoops_GIAHR) {
						x1 = _hoops_GPCCC;
						_hoops_AGSIR = _hoops_RPCCC;
					}
					else {
						x1 = in->x;
						_hoops_AGSIR = in->y;
					}
				}	break;

				case _hoops_CIPHP: {
					if (in == _hoops_GIAHR) {
						x1 = _hoops_GPCCC;
						_hoops_AGSIR = _hoops_RPCCC;
					}
					else {
						x1 = _hoops_PRPPI (elements, in[0]);
						_hoops_AGSIR = _hoops_HRPPI (elements, in[0]);
					}
				}	break;

				case _hoops_PCPHP: {
					if (in == _hoops_GIAHR) {
						x1 = _hoops_GPCCC;
						_hoops_AGSIR = _hoops_RPCCC;
					}
					else {
						x1 = _hoops_HPRA (elements, in[0]);
						_hoops_AGSIR = _hoops_IPRA (elements, in[0]);
					}
				}	break;

				case _hoops_ACPHP: {
					if (in == _hoops_GIAHR) {
						x1 = _hoops_GPCCC;
						_hoops_AGSIR = _hoops_RPCCC;
						_hoops_HGSIR = _hoops_CPCIS;
					}
					else {
						x1 = _hoops_HPRA (elements, in[0]);
						_hoops_AGSIR = _hoops_IPRA (elements, in[0]);
						_hoops_HGSIR = _hoops_CPRA (elements, in[0]);
					}
				}	break;

				case _hoops_RCPHP: {
					_hoops_GHHAS = _hoops_RHHAS;
					_hoops_RHHAS = _hoops_PHCP (elements, in[0]);

					if (_hoops_RHHAS < _hoops_IHCR->_hoops_CHCR) {
						_hoops_APHAS = _hoops_PPHAS;
						_hoops_HPHAS = _hoops_IPHAS;

						if (_hoops_GHHAS >= _hoops_IHCR->_hoops_CHCR) {/* _hoops_PHGHR _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_RHC*/
							float	_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

							_hoops_PPHAS = _hoops_HPRA (elements, in[0]);
							_hoops_IPHAS = _hoops_IPRA (elements, in[0]);

							_hoops_AHHAS = (_hoops_IHCR->_hoops_CHCR - _hoops_GHHAS) / (_hoops_RHHAS - _hoops_GHHAS);
							x1 = (_hoops_APHAS + (_hoops_PPHAS - _hoops_APHAS) * _hoops_AHHAS) * _hoops_PASAS;
							_hoops_AGSIR = (_hoops_HPHAS + (_hoops_IPHAS - _hoops_HPHAS) * _hoops_AHHAS) * _hoops_PASAS;

							/* _hoops_RGR _hoops_HAPR _hoops_GRS _hoops_CHCIS _hoops_RH _hoops_III _hoops_CAGH
							 * _hoops_GAPA _hoops_RH _hoops_ASSA _hoops_PPSR _hoops_PPR _hoops_RH _hoops_PPSR
							 * _hoops_GPP _hoops_RH _hoops_SHCIS _hoops_IIGR _hoops_GICIS _hoops_HII _hoops_GGR _hoops_RIPS
							 * _hoops_IIGR _hoops_RH _hoops_RHC.
							 */

							/* _hoops_HHSA _hoops_RH _hoops_HAPR _hoops_IS _hoops_IHSH _hoops_HPGR _hoops_RGR _hoops_GHIPR-_hoops_RH-
							 * _hoops_RHC _hoops_GICS _hoops_SPS _hoops_GHIR _hoops_AARI.
							 */
							_hoops_SPCIS = in;
							in--;
							done = false;
						}
						else {	 /* _hoops_AA _hoops_RH _hoops_SPGCA _hoops_RHIR "_hoops_RICIS" */
							float	_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

							/* _hoops_RIIPS _hoops_CPCHR _hoops_IS _hoops_RH _hoops_AICIS _hoops_PPSR */
							do {
								_hoops_HSPS = in;
								_hoops_GCRGA = _hoops_RHHAS;
								if (++in == end) in = polygon->points;
								_hoops_RHHAS = _hoops_PHCP (elements, in[0]);
							}
							_hoops_RGGA (_hoops_RHHAS >= _hoops_IHCR->_hoops_CHCR);

							if (_hoops_HSPS == _hoops_SPCIS) {
								/* _hoops_PICIS, _hoops_HICIS, _hoops_IICIS _hoops_AIAH _hoops_PGGGH */
							}
							else {
								_hoops_APHAS = _hoops_HPRA (elements, _hoops_HSPS[0]);
								_hoops_HPHAS = _hoops_IPRA (elements, _hoops_HSPS[0]);
								_hoops_GHHAS = _hoops_GCRGA;
							}

							/* _hoops_CAHA _hoops_RH _hoops_AICIS _hoops_PPSR */
							_hoops_PPHAS = _hoops_HPRA (elements, in[0]);
							_hoops_IPHAS = _hoops_IPRA (elements, in[0]);

							/* _hoops_PAGA: _hoops_SHR _hoops_HSPH *_hoops_PHGHR*, _hoops_IH _hoops_GPPS. */
							_hoops_AHHAS = (_hoops_IHCR->_hoops_CHCR - _hoops_RHHAS) / (_hoops_GHHAS - _hoops_RHHAS);
							x1 = (_hoops_PPHAS + (_hoops_APHAS - _hoops_PPHAS) * _hoops_AHHAS) * _hoops_PASAS;
							_hoops_AGSIR = (_hoops_IPHAS + (_hoops_HPHAS - _hoops_IPHAS) * _hoops_AHHAS) * _hoops_PASAS;

							/* _hoops_RGR _hoops_HAPR _hoops_GRS _hoops_CHCIS _hoops_RH _hoops_III _hoops_CAGH
							 * _hoops_GAPA _hoops_RH _hoops_RIARR _hoops_PPSR _hoops_PPR _hoops_RH _hoops_AICIS
							 * _hoops_PPSR.
							 */

							/* _hoops_APHS _hoops_RGR _hoops_PPSR _hoops_IS _hoops_HGCR _hoops_RH _hoops_III _hoops_CAGH
							 * _hoops_GAPA _hoops_RH _hoops_AICIS _hoops_PPSR _hoops_PPR _hoops_RH _hoops_GGR-_hoops_RIPS-
							 * _hoops_IIGR-_hoops_RH-_hoops_RHC _hoops_PPSR.
							 */
							_hoops_SPCIS = in;
							in--;
							done = false;
						}
					}
					else {		/* _hoops_HA _hoops_GGR _hoops_RIPS _hoops_RH _hoops_RHC */
						if (_hoops_GHHAS < _hoops_IHCR->_hoops_CHCR) { /* _hoops_RPP _hoops_SR _hoops_AAPR _hoops_GHIPR */
							x1 = _hoops_PPHAS/_hoops_RHHAS;
							_hoops_AGSIR = _hoops_IPHAS/_hoops_RHHAS;
						}
						else {	/* _hoops_RH _hoops_GSSR _hoops_AGIR */
							if (in == _hoops_GIAHR) {
								x1 = _hoops_GPCCC;
								_hoops_AGSIR = _hoops_RPCCC;
							}
							else {
								_hoops_PPHAS = _hoops_HPRA (elements, in[0]);
								_hoops_IPHAS = _hoops_IPRA (elements, in[0]);
								x1 = _hoops_PPHAS/_hoops_RHHAS;
								_hoops_AGSIR = _hoops_IPHAS/_hoops_RHHAS;
							}
						}
					}
				}				break;

				case _hoops_GCPHP: {
					/* _hoops_HSHPR _hoops_IS _hoops_CICIS, _hoops_AHSAR _hoops_CCA _hoops_AHCR'_hoops_GRI */

					_hoops_GHHAS = _hoops_RHHAS;
					_hoops_RHHAS = _hoops_PHCP (elements, in[0]);

					if (_hoops_RHHAS < _hoops_IHCR->_hoops_CHCR) {
						_hoops_APHAS = _hoops_PPHAS;
						_hoops_HPHAS = _hoops_IPHAS;
						_hoops_CPHAS = _hoops_SPHAS;

						if (_hoops_GHHAS >= _hoops_IHCR->_hoops_CHCR) {/* _hoops_PHGHR _hoops_GGR _hoops_RIPS _hoops_IIGR _hoops_RH _hoops_RHC*/
							float	_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

							_hoops_PPHAS = _hoops_HPRA (elements, in[0]);
							_hoops_IPHAS = _hoops_IPRA (elements, in[0]);
							_hoops_SPHAS = _hoops_CPRA (elements, in[0]);

							_hoops_AHHAS = (_hoops_IHCR->_hoops_CHCR - _hoops_GHHAS) / (_hoops_RHHAS - _hoops_GHHAS);
							x1 = (_hoops_APHAS + (_hoops_PPHAS - _hoops_APHAS) * _hoops_AHHAS) * _hoops_PASAS;
							_hoops_AGSIR = (_hoops_HPHAS + (_hoops_IPHAS - _hoops_HPHAS) * _hoops_AHHAS) * _hoops_PASAS;
							_hoops_HGSIR = (_hoops_CPHAS + (_hoops_SPHAS - _hoops_CPHAS) * _hoops_AHHAS) * _hoops_PASAS;

							/* _hoops_RGR _hoops_HAPR _hoops_GRS _hoops_CHCIS _hoops_RH _hoops_III _hoops_CAGH
							 * _hoops_GAPA _hoops_RH _hoops_ASSA _hoops_PPSR _hoops_PPR _hoops_RH _hoops_PPSR
							 * _hoops_GPP _hoops_RH _hoops_SHCIS _hoops_IIGR _hoops_GICIS _hoops_HII _hoops_GGR _hoops_RIPS
							 * _hoops_IIGR _hoops_RH _hoops_RHC.
							 */

							/* _hoops_HHSA _hoops_RH _hoops_HAPR _hoops_IS _hoops_IHSH _hoops_HPGR _hoops_RGR _hoops_GHIPR-_hoops_RH-
							 * _hoops_RHC _hoops_GICS _hoops_SPS _hoops_GHIR _hoops_AARI.
							 */
							_hoops_SPCIS = in;
							in--;
							done = false;
						}
						else {	 /* _hoops_AA _hoops_RH _hoops_SPGCA _hoops_RHIR "_hoops_RICIS" */
							float	_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

							/* _hoops_RIIPS _hoops_CPCHR _hoops_IS _hoops_RH _hoops_AICIS _hoops_PPSR */
							do {
								_hoops_HSPS = in;
								_hoops_GCRGA = _hoops_RHHAS;
								if (++in == end) in = polygon->points;
								_hoops_RHHAS = _hoops_PHCP (elements, in[0]);
							}
							_hoops_RGGA (_hoops_RHHAS >= _hoops_IHCR->_hoops_CHCR);

							if (_hoops_HSPS == _hoops_SPCIS) {
								/* _hoops_PICIS, _hoops_HICIS, _hoops_IICIS _hoops_AIAH _hoops_PGGGH */
							}
							else {
								_hoops_APHAS = _hoops_HPRA (elements, _hoops_HSPS[0]);
								_hoops_HPHAS = _hoops_IPRA (elements, _hoops_HSPS[0]);
								_hoops_CPHAS = _hoops_CPRA (elements, _hoops_HSPS[0]);
								_hoops_GHHAS = _hoops_GCRGA;
							}

							/* _hoops_CAHA _hoops_RH _hoops_AICIS _hoops_PPSR */
							_hoops_PPHAS = _hoops_HPRA (elements, in[0]);
							_hoops_IPHAS = _hoops_IPRA (elements, in[0]);
							_hoops_SPHAS = _hoops_CPRA (elements, in[0]);

							/* _hoops_PAGA: _hoops_SHR _hoops_HSPH *_hoops_PHGHR*, _hoops_IH _hoops_GPPS. */
							_hoops_AHHAS = (_hoops_IHCR->_hoops_CHCR - _hoops_RHHAS) / (_hoops_GHHAS - _hoops_RHHAS);
							x1 = (_hoops_PPHAS + (_hoops_APHAS - _hoops_PPHAS) * _hoops_AHHAS) * _hoops_PASAS;
							_hoops_AGSIR = (_hoops_IPHAS + (_hoops_HPHAS - _hoops_IPHAS) * _hoops_AHHAS) * _hoops_PASAS;
							_hoops_HGSIR = (_hoops_SPHAS + (_hoops_CPHAS - _hoops_SPHAS) * _hoops_AHHAS) * _hoops_PASAS;

							/* _hoops_RGR _hoops_HAPR _hoops_GRS _hoops_CHCIS _hoops_RH _hoops_III _hoops_CAGH
							 * _hoops_GAPA _hoops_RH _hoops_RIARR _hoops_PPSR _hoops_PPR _hoops_RH _hoops_AICIS
							 * _hoops_PPSR.
							 */

							/* _hoops_APHS _hoops_RGR _hoops_PPSR _hoops_IS _hoops_HGCR _hoops_RH _hoops_III _hoops_CAGH
							 * _hoops_GAPA _hoops_RH _hoops_AICIS _hoops_PPSR _hoops_PPR _hoops_RH _hoops_GGR-_hoops_RIPS-
							 * _hoops_IIGR-_hoops_RH-_hoops_RHC _hoops_PPSR.
							 */
							_hoops_SPCIS = in;
							in--;
							done = false;
						}
					}
					else {		/* _hoops_HA _hoops_GGR _hoops_RIPS _hoops_RH _hoops_RHC */
						if (_hoops_GHHAS < _hoops_IHCR->_hoops_CHCR) { /* _hoops_RPP _hoops_SR _hoops_AAPR _hoops_GHIPR */
							x1 = _hoops_PPHAS/_hoops_RHHAS;
							_hoops_AGSIR = _hoops_IPHAS/_hoops_RHHAS;
							_hoops_HGSIR = _hoops_SPHAS/_hoops_RHHAS;
						}
						else {
							if (in == _hoops_GIAHR) {
								x1 = _hoops_GPCCC;
								_hoops_AGSIR = _hoops_RPCCC;
								_hoops_HGSIR = _hoops_CPCIS;
							}
							else {
								_hoops_PPHAS = _hoops_HPRA (elements, in[0]);
								_hoops_IPHAS = _hoops_IPRA (elements, in[0]);
								_hoops_SPHAS = _hoops_CPRA (elements, in[0]);
								x1 = _hoops_PPHAS/_hoops_RHHAS;
								_hoops_AGSIR = _hoops_IPHAS/_hoops_RHHAS;
								_hoops_HGSIR = _hoops_SPHAS/_hoops_RHHAS;
							}
						}
					}
				}				break;
			}

			if (x1 < _hoops_GPHH.left-_hoops_CCIIS) _hoops_RHCIS = _hoops_SCIIS;
			else if (x1 > _hoops_GPHH.right+_hoops_CCIIS) _hoops_RHCIS = CC_OFF_TO_RIGHT;
			else if (_hoops_AGSIR < _hoops_GPHH.bottom-_hoops_CCIIS) _hoops_RHCIS = CC_OFF_TO_BOTTOM;
			else if (_hoops_AGSIR > _hoops_GPHH.top+_hoops_CCIIS) _hoops_RHCIS = _hoops_GSIIS;
			else _hoops_RHCIS = _hoops_HCRCP;

			if (_hoops_GHCIS == _hoops_HCRCP) {
/* _hoops_RGR "_hoops_RPIHR" _hoops_IRS _hoops_SICIS _hoops_ARPC _hoops_GCCIS _hoops_RIAGR*/
#ifdef MINITAB 
				_hoops_PAGR->x = _hoops_AGRSH;
				_hoops_PAGR->y = _hoops_PGRSH;
#else
				_hoops_PAGR->x = _hoops_AGRSH + _hoops_GIRSP;
				_hoops_PAGR->y = _hoops_PGRSH + _hoops_GIRSP;
#endif
				if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC))
					_hoops_PAGR->z = _hoops_IGSC (_hoops_HGRSH, _hoops_IHCR);
				else
					_hoops_PAGR->z = 0.0f;

				++_hoops_PAGR;

				if (_hoops_RHCIS != _hoops_HCRCP) { /* _hoops_HPIRA _hoops_PCCP _hoops_ISHA */
					edge->end._hoops_PPRCP = _hoops_ACIIS (nr, _hoops_AGRSH, _hoops_PGRSH, _hoops_HGRSH,
														x1, _hoops_AGSIR, _hoops_HGSIR,
														_hoops_PAGR);
					edge->end.point = _hoops_PAGR++;
					ALLOC (_hoops_PHCIS, Edge_Interval);
					_hoops_PHCIS->prev = edge;
					edge = _hoops_PHCIS;
				}
			}
			else if (_hoops_RHCIS == _hoops_HCRCP) {		/* _hoops_HSPP _hoops_PCCP _hoops_ISHA */
				edge->start._hoops_PPRCP = _hoops_RCIIS (nr, _hoops_AGRSH, _hoops_PGRSH, _hoops_HGRSH,
												   x1, _hoops_AGSIR, _hoops_HGSIR,
												   _hoops_PAGR);
				edge->start.point = _hoops_PAGR++;
			}
			else if (_hoops_GHCIS != _hoops_RHCIS) {		/* _hoops_HAR "_hoops_PSAP" _hoops_RH _hoops_PSHR _hoops_PPAP? */
				if (_hoops_RSIIS (nr, _hoops_AGRSH, _hoops_PGRSH, _hoops_HGRSH, x1, _hoops_AGSIR, _hoops_HGSIR,
											  _hoops_PAGR, edge, false)) {
					_hoops_PAGR += 2;
					ALLOC (_hoops_PHCIS, Edge_Interval);
					_hoops_PHCIS->prev = edge;
					edge = _hoops_PHCIS;
				}
			}

			if (_hoops_GHCIS == _hoops_SCIIS || _hoops_RHCIS == _hoops_SCIIS) {
				/* _hoops_HPPR _hoops_ACIPR _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_RGR _hoops_ISHA _hoops_ICHIA _hoops_IS _hoops_RH
				 * _hoops_RAAP _hoops_IIGR _hoops_RH _hoops_GSSC _hoops_RAAP _hoops_ISHA
				 */

				if ((_hoops_PGRSH < _hoops_GPHH.bottom-_hoops_CCIIS && _hoops_AGSIR < _hoops_GPHH.bottom-_hoops_CCIIS) ||
				   (_hoops_PGRSH >= _hoops_GPHH.bottom-_hoops_CCIIS && _hoops_AGSIR >= _hoops_GPHH.bottom-_hoops_CCIIS)) {
					/* _hoops_ASSP'_hoops_RA _hoops_SHHP _hoops_RH _hoops_PRPC _hoops_III */
				}
				else if (_hoops_GHCIS == _hoops_RHCIS) /* _hoops_GIPR _hoops_IS _hoops_RAAP */
					_hoops_HHCIS = !_hoops_HHCIS;
				else if (_hoops_GHCIS == _hoops_HCRCP) {
					if (edge->prev->end._hoops_PPRCP == _hoops_SCIIS)
						_hoops_HHCIS = !_hoops_HHCIS;
				}
				else if (_hoops_RHCIS == _hoops_HCRCP) {
					if (edge->start._hoops_PPRCP == _hoops_SCIIS)
						_hoops_HHCIS = !_hoops_HHCIS;
				}
				else {	/* _hoops_RCCIS */
					if ((_hoops_GPHH.bottom-_hoops_CCIIS - _hoops_PGRSH)*(x1 - _hoops_AGRSH) <
						(_hoops_GPHH.left-_hoops_CCIIS - _hoops_AGRSH)*(_hoops_AGSIR - _hoops_PGRSH)) {
						if (_hoops_AGSIR > _hoops_PGRSH) _hoops_HHCIS = !_hoops_HHCIS;
					}
					else {
						if (_hoops_AGSIR < _hoops_PGRSH) _hoops_HHCIS = !_hoops_HHCIS;
					}
				}
			}
		}
		_hoops_RGGA (done);

		if (_hoops_PAGR != out_base)
			*_hoops_PAGR = *out_base; /* _hoops_GGGR _hoops_GRGA */

		if (edge->prev == null) { /* _hoops_SARS'_hoops_RA _hoops_SHHP _hoops_HPGR _hoops_HCR */
			if (_hoops_RHCIS == _hoops_HCRCP) {
				/* _hoops_GRH _hoops_AGIR: _hoops_CCGC _hoops_GIAA */

				if (!BIT (nr->_hoops_RGP, T_FACES))
					_hoops_ISHGH (nr, _hoops_PAGR-out_base+1, out_base);
				else if (!ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE))
					_hoops_HIIIS (nr, _hoops_IHCR, _hoops_PAGR-out_base, out_base, polygon);
				else
					_hoops_IIIIS (nr, _hoops_IHCR, _hoops_PAGR-out_base+1, out_base, polygon);
			}
			else if (_hoops_HHCIS) {
				/* _hoops_GRH _hoops_AGIR: _hoops_RPPS _hoops_CCGC _hoops_PIISR */
				if (BIT (nr->_hoops_RGP, T_FACES))
					_hoops_AGCIS (nr, polygon);
			}
			else {/* _hoops_ACCIS: _hoops_HCR _hoops_PPRGA */}
		}
		else {
			int				count;

			if (_hoops_RHCIS == _hoops_HCRCP) {
				_hoops_AHCIS.start.point = edge->start.point; /* _hoops_ARGAR _hoops_SCH */
				_hoops_AHCIS.start._hoops_PPRCP = edge->start._hoops_PPRCP;
			}

			_hoops_PHCIS = edge->prev;
			FREE (edge, Edge_Interval);
			edge = _hoops_PHCIS;

			if (BIT (nr->_hoops_RGP, T_FACES)) {	/* _hoops_RCIPR _hoops_PGSA _hoops_RH _hoops_HSP */
				if (edge->prev == null &&
					_hoops_AHCIS.start._hoops_PPRCP == _hoops_AHCIS.end._hoops_PPRCP &&
					!_hoops_HHCIS) {
					/* _hoops_GRH _hoops_AGIR: _hoops_SACH _hoops_GPCPR _hoops_ARR,
									 _hoops_GPP _hoops_PSHR _hoops_HSPH _hoops_ASCR,
									 _hoops_ISAP _hoops_AAHHP */

					count = _hoops_PAGR - out_base;

					if (count < 3) {/* _hoops_PAHA'_hoops_RA _hoops_IHPS */}
					else
						_hoops_HIIIS (nr, _hoops_IHCR, count, out_base, polygon);
				}
				else {
					/* _hoops_RHAR _hoops_AGIR: _hoops_HPGAS _hoops_RRI _hoops_HSAR _hoops_ARR, _hoops_IIRSC */

					_hoops_CRCIS (nr, edge, out_base, _hoops_PAGR-1,
												 _hoops_HHCIS, (Geometry const *)polygon);
				}
			}

			if (!ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE)) {
				/* _hoops_CIH _hoops_RH _hoops_ISHA _hoops_HIGR (_hoops_SHH _hoops_RHRIR _hoops_HAR _hoops_IS _hoops_HPPR _hoops_IS _hoops_CIH _hoops_PCCIS)*/
				_hoops_RGGA ((_hoops_PHCIS = edge->prev) == null) {
					FREE (edge, Edge_Interval);
					edge = _hoops_PHCIS;
				}
			}
			else {
			  _hoops_PCCAR { /* _hoops_PGSA _hoops_PPR _hoops_CIH _hoops_RH _hoops_SPPR */
				if (edge->start.point <= edge->end.point) {
					/* _hoops_RGR _hoops_ISHA _hoops_RHAP _hoops_HAR _hoops_ARGAR _hoops_AARI _hoops_RH _hoops_RSGR */
					count = edge->end.point - edge->start.point + 1;
					if (count < 2) {/* _hoops_PAHA'_hoops_RA _hoops_IHPS */}
					else
						_hoops_CIIIS (nr, _hoops_IHCR, count, edge->start.point);
				}
				else {
					/* _hoops_RGR _hoops_ISHA _hoops_CSGPS _hoops_AARI _hoops_RH _hoops_RSGR _hoops_IIGR _hoops_RH '_hoops_GGSR' _hoops_CRPR */

					/* _hoops_PGSA _hoops_RH _hoops_SRS _hoops_ARIP */
					count = _hoops_PAGR - edge->start.point + 1;
					if (count < 2) {/* _hoops_PAHA'_hoops_RA _hoops_IHPS */}
					else
						_hoops_CIIIS (nr, _hoops_IHCR, count, edge->start.point);

					/* _hoops_PGSA _hoops_RH _hoops_GIAP _hoops_ARIP */
					count = edge->end.point - out_base + 1;
					if (count < 2) {/* _hoops_PAHA'_hoops_RA _hoops_IHPS */}
					else
						_hoops_CIIIS (nr, _hoops_IHCR, count, out_base);
				}

				if ((_hoops_PHCIS = edge->prev) == null) break;
				FREE (edge, Edge_Interval);
				edge = _hoops_PHCIS;
			  }
			}
		}
	}

	if (polygon->count >= _hoops_SIIIS/_hoops_GCIIS) {
		_hoops_PAGR = out_base;
		FREE_ARRAY (_hoops_PAGR, polygon->count * _hoops_GCIIS, DC_Point);
	}
#endif
}




local void _hoops_PRAGA(_hoops_CPGGH *_hoops_GSHIR, int index, int v)
{
	int *new_points;

	ALLOC_ARRAY(new_points, _hoops_GSHIR->count+1, int);

	if (index >= 0)
		_hoops_AIGA(&_hoops_GSHIR->points[0], index+1, int, &new_points[0]);

	new_points[index+1] = v;

	if (index != _hoops_GSHIR->count)
		_hoops_AIGA(&_hoops_GSHIR->points[index+1], _hoops_GSHIR->count-index-1, int, &new_points[index+2]);

	FREE_ARRAY(_hoops_GSHIR->points, _hoops_GSHIR->count, int);
	
	_hoops_GSHIR->count+=1;
	_hoops_GSHIR->points=new_points;
}


GLOBAL_FUNCTION void HI_Polygon_Triangle_Collector (
	_hoops_RGSIH	alter &_hoops_ARGC,
	Integer32 _hoops_ISPI, 
	Integer32 _hoops_CSPI, 
	Integer32 _hoops_SSPI) 
{
	_hoops_CPGGH *_hoops_GSHIR;
	int			i;

	_hoops_ARGC.ResetCursor();

	while ((_hoops_GSHIR = _hoops_ARGC.PeekCursor()) != null) {
		int _hoops_HCCIS = -1, _hoops_ICCIS = -1, _hoops_CCCIS = -1;

		for (i=0; i<_hoops_GSHIR->count; i++) {
			if (_hoops_GSHIR->points[i] == _hoops_ISPI)
				_hoops_HCCIS = i;

			if (_hoops_GSHIR->points[i] == _hoops_CSPI)
				_hoops_ICCIS = i;

			if (_hoops_GSHIR->points[i] == _hoops_SSPI)
				_hoops_CCCIS = i;
		}

		if (_hoops_HCCIS != -1 && _hoops_ICCIS != -1 && _hoops_CCCIS == -1) {
			if (_hoops_ICCIS+1 == _hoops_HCCIS) {
				_hoops_PRAGA(_hoops_GSHIR, _hoops_ICCIS, _hoops_SSPI);
				return;
			}
			if (_hoops_ICCIS == _hoops_GSHIR->count-1 && _hoops_HCCIS==0) {
				_hoops_PRAGA(_hoops_GSHIR, _hoops_GSHIR->count-1, _hoops_SSPI);	
				return;
			}	
		}

		if (_hoops_HCCIS != -1 && _hoops_ICCIS == -1 && _hoops_CCCIS != -1) {
			if (_hoops_HCCIS+1 == _hoops_CCCIS) {
				_hoops_PRAGA(_hoops_GSHIR, _hoops_HCCIS, _hoops_CSPI);
				return;
			}
			if (_hoops_HCCIS == _hoops_GSHIR->count-1 && _hoops_CCCIS==0) {
				_hoops_PRAGA(_hoops_GSHIR, _hoops_GSHIR->count-1, _hoops_CSPI);
				return;
			}
		}
				
		if (_hoops_HCCIS == -1 && _hoops_ICCIS != -1 && _hoops_CCCIS != -1) {

			if (_hoops_CCCIS+1 == _hoops_ICCIS) {
				_hoops_PRAGA(_hoops_GSHIR, _hoops_CCCIS, _hoops_ISPI);
				return;
			}
			if (_hoops_CCCIS == _hoops_GSHIR->count-1 && _hoops_ICCIS==0) {
				_hoops_PRAGA(_hoops_GSHIR, _hoops_GSHIR->count-1, _hoops_ISPI);
				return;
			}	

		}

		_hoops_ARGC.AdvanceCursor();
	}

	ALLOC(_hoops_GSHIR, _hoops_CPGGH);

	_hoops_GSHIR->count = 3;
	ALLOC_ARRAY(_hoops_GSHIR->points, 3, int);

	_hoops_GSHIR->points[0] = _hoops_ISPI;
	_hoops_GSHIR->points[1] = _hoops_CSPI;
	_hoops_GSHIR->points[2] = _hoops_SSPI;

	_hoops_ARGC.AddFirst(_hoops_GSHIR);

}



GLOBAL_FUNCTION void HI_Polygon_Merge (
	_hoops_AIGPR *			_hoops_RIGC,
	_hoops_RGSIH	alter *	_hoops_ARGC) 
{
	_hoops_CPGGH *			c;
	_hoops_CPGGH *			p;
	_hoops_RGSIH *	used = POOL_NEW(_hoops_RIGC->memory_pool, _hoops_RGSIH)(_hoops_RIGC->memory_pool);
	int i,j;

_hoops_SCCIS:
	while ((p = _hoops_ARGC->RemoveFirst()) != null) {

		_hoops_ARGC->ResetCursor();

		while ((c = _hoops_ARGC->PeekCursor()) != null) {
			int _hoops_GSCIS[3];
			int _hoops_RSCIS[3];
			int _hoops_ASCIS = 0;

			for (i=0; i<c->count; i++) {
				for (j=0; j<p->count; j++) {
					if (c->points[i] == p->points[j]) {
						_hoops_GSCIS[_hoops_ASCIS] = i;
						_hoops_RSCIS[_hoops_ASCIS] = j;
						_hoops_ASCIS++;

						if (_hoops_ASCIS>2) 
							goto _hoops_PSCIS;
					}
				}
			}

			if (_hoops_ASCIS != 2)
				goto _hoops_PSCIS;


			if (_hoops_GSCIS[0] == 0 && _hoops_GSCIS[1] == c->count-1) {
				_hoops_GSCIS[0] = c->count-1;
				_hoops_GSCIS[1] = 0;

				i=_hoops_RSCIS[1];
				_hoops_RSCIS[1] = _hoops_RSCIS[0];
				_hoops_RSCIS[0] = i;
			}

			if (((_hoops_GSCIS[0]+1 == _hoops_GSCIS[1]) ||
				(_hoops_GSCIS[1] == 0 && _hoops_GSCIS[0] == c->count-1)) &&
				((_hoops_RSCIS[1]+1 == _hoops_RSCIS[0]) ||
				(_hoops_RSCIS[0] == 0 && _hoops_RSCIS[1] == p->count-1))) {

				int	_hoops_AAAHA;
				int	*new_points;

				_hoops_AAAHA = c->count + p->count - 2;

				ALLOC_ARRAY(new_points, _hoops_AAAHA, int);

				i=0;
				if (_hoops_GSCIS[1] != 0) {
					_hoops_AIGA (&c->points[0], _hoops_GSCIS[0]+1, int, &new_points[i]);
					i += _hoops_GSCIS[0]+1;
				}

				if (_hoops_RSCIS[0] == 0) {
					_hoops_AIGA (&p->points[1], p->count-2, int, &new_points[i]);
					i += p->count-2;
				}
				else {
					if (p->count-(_hoops_RSCIS[0]+1)) {
						_hoops_AIGA (&p->points[_hoops_RSCIS[0]+1], p->count-(_hoops_RSCIS[0]+1), int, &new_points[i]);
						i += p->count-(_hoops_RSCIS[0]+1);
					}
				
					if (_hoops_RSCIS[1] > 0) {
						_hoops_AIGA (&p->points[0], _hoops_RSCIS[1], int, &new_points[i]);
						i += _hoops_RSCIS[1];
					}
				}
				
				if ((c->count-_hoops_GSCIS[1])>0) {
					_hoops_AIGA (&c->points[_hoops_GSCIS[1]], c->count-_hoops_GSCIS[1], int, &new_points[i]);
					i += c->count-_hoops_GSCIS[1];
				}

				FREE_ARRAY(c->points, c->count, int);
				
				c->count=_hoops_AAAHA;
				c->points=new_points;

				FREE_ARRAY(p->points, p->count, int);
				FREE(p, _hoops_CPGGH);
				goto _hoops_SCCIS;
			}

_hoops_PSCIS:
			_hoops_ARGC->AdvanceCursor();
		}

		used->AddFirst(p);
	}

	/* _hoops_PPSI _hoops_RH _hoops_IGI _hoops_ISSC _hoops_GGR _hoops_RH _hoops_IARI */
	while ((p = used->RemoveFirst()) != null) {
		_hoops_ARGC->AddFirst(p);
	}

	delete used;
}


local void _hoops_CRASH (void *info, Integer32 _hoops_HAPH,
						 Integer32 _hoops_ISPI, Integer32 _hoops_CSPI, Integer32 _hoops_SSPI) {

	HI_Polygon_Triangle_Collector (*((_hoops_RGSIH *)info), _hoops_ISPI, _hoops_CSPI, _hoops_SSPI);
	
	UNREFERENCED(_hoops_HAPH);
}




GLOBAL_FUNCTION void HD_Std_3D_Contour (
	Net_Rendition const &		in_nr,
	_hoops_PRHIR const *				_hoops_CICP) {
#ifndef DISABLE_DRAW_3D
	Net_Rendition				nr = in_nr;
	_hoops_RGSIH *	_hoops_ARGC = POOL_NEW(nr->_hoops_SRA->memory_pool, _hoops_RGSIH)(nr->_hoops_SRA->memory_pool);

	if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE))
		nr.Modify()->_hoops_RGP &= ~T_ANY_POLYGON_EDGE;

	int	_hoops_PAAHA = _hoops_CICP->_hoops_CASGP;
	for (int i=0; i<_hoops_CICP->_hoops_CASGP; ++i)
		_hoops_PAAHA += _hoops_CICP->lengths[i];

	int alter *	new_face_list;
	ALLOC_ARRAY(new_face_list, _hoops_PAAHA, int);

	int n = 0;
	int	v = 0;
	for (int i=0; i<_hoops_CICP->_hoops_CASGP; ++i) {
		if (i == 0)
			new_face_list[n++] = _hoops_CICP->lengths[i];
		else
			new_face_list[n++] = -_hoops_CICP->lengths[i];

		for (int j=0; j<_hoops_CICP->lengths[i]; ++j)
			new_face_list[n++] = v++;
	}

	HI_Triangulate_Face (_hoops_CICP->points, &_hoops_IRGA::_hoops_IGHH, 
							new_face_list, new_face_list+_hoops_PAAHA, 
							_hoops_CRASH, (void alter *)_hoops_ARGC);

	if (_hoops_ARGC->Count() > 0)
		HI_Polygon_Merge (nr->_hoops_SRA->_hoops_RIGC, _hoops_ARGC);

	_hoops_CPGGH *	_hoops_GSHIR;
	while ((_hoops_GSHIR = _hoops_ARGC->RemoveFirst()) != null) {
		Polygon alter *		polygon;

		ZALLOC (polygon, Polygon);
		polygon->type = _hoops_RCIP;
		polygon->_hoops_HIHI = 1;

		polygon->count = _hoops_GSHIR->count;
		polygon->allocated = _hoops_GSHIR->count;
		ALLOC_ARRAY(polygon->points, polygon->allocated, Point);

		polygon->plane.a = 0.0f;
		polygon->plane.b = 0.0f;
		polygon->plane.c = 1.0f;
		polygon->plane.d = 0.0f;

		for (int i=0; i<_hoops_GSHIR->count; i++)
			polygon->points[i] = _hoops_CICP->points[_hoops_GSHIR->points[i]];

		_hoops_RCAIP (nr, polygon);
		_hoops_HPRH(polygon);

		FREE(_hoops_GSHIR, _hoops_CPGGH);
	}

	FREE_ARRAY(new_face_list, _hoops_PAAHA, int);

	delete _hoops_ARGC;
#endif
}




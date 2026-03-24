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
 * $Id: obf_tmp.txt 1.86 2010-12-06 22:05:40 jason Exp $
 */

#include "hoops.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "phedron.h"
#include "adt.h"


#ifndef DISABLE_COMPUTE

struct _hoops_CGGPA {
	_hoops_CGGPA *	next;
	_hoops_CGGPA *	prev;
	float		x, y, z;
	int			index;
	int			_hoops_HIHI;
	int			_hoops_SGGPA;
};

struct _hoops_GRGPA {
	_hoops_GRGPA *	next;
	_hoops_CGGPA *		vertex;
};

struct _hoops_RRGPA {
	_hoops_RRGPA *		next;
	_hoops_RRGPA *		prev;
	_hoops_AAIRA			plane;
	_hoops_GRGPA *	vertices;
};

struct _hoops_ARGPA {
	_hoops_ARGPA *		next;
	_hoops_CGGPA *		start;
	_hoops_CGGPA *		end;
};

struct QSP {
	int *			_hoops_PRGPA;
	Point const *	in_points;
};


#define _hoops_HRGPA		1e-2f
#define _hoops_IRGPA			1e-9f
#define _hoops_CRGPA				0.999994f		/* _hoops_SRGPA _hoops_IIGR 0.2 _hoops_ASIPR */

local void _hoops_GAGPA (
	_hoops_RRGPA *	face) {
	_hoops_CGGPA			*p1, *p2, *_hoops_IAPH;
	double			length;


	p1 = face->vertices->vertex;
	p2 = face->vertices->next->vertex;
	_hoops_IAPH = face->vertices->next->next->vertex;

	face->plane.a = (p2->y-p1->y)*(_hoops_IAPH->z-p2->z) - (p2->z-p1->z)*(_hoops_IAPH->y-p2->y);
	face->plane.b = (p2->z-p1->z)*(_hoops_IAPH->x-p2->x) - (p2->x-p1->x)*(_hoops_IAPH->z-p2->z);
	face->plane.c = (p2->x-p1->x)*(_hoops_IAPH->y-p2->y) - (p2->y-p1->y)*(_hoops_IAPH->x-p2->x);
	face->plane.d = -(face->plane.a*p1->x +
						face->plane.b*p1->y +
						  face->plane.c*p1->z);

	length = face->plane.a*face->plane.a + 
		face->plane.b*face->plane.b + 
		face->plane.c*face->plane.c;

	if (length < 1.0e-30)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Generated triangle from colinear points");
	else {
		length = sqrt(length);
		face->plane.a /= length;
		face->plane.b /= length;
		face->plane.c /= length;
		face->plane.d /= length;
	}

	++p1->_hoops_HIHI;
	++p2->_hoops_HIHI;
	++_hoops_IAPH->_hoops_HIHI;
}
#endif



typedef struct _hoops_RAGPA {
	struct _hoops_RAGPA		*next;
	int							_hoops_GIHPR;
	_hoops_CGCPR				_hoops_SGCPR;
} _hoops_AAGPA;

local int _hoops_PAGPA (
	int						point1,
	int						point2,
	int						face,
	_hoops_AAGPA **		_hoops_HHHPR) {
	int						source;
	int						_hoops_GIHPR;
	_hoops_AAGPA *			_hoops_HAGPA;
	_hoops_AAGPA **		_hoops_ASRGR;

	if (point1 == point2) return 0;

	if (point1 < point2) {
		/* _hoops_GACPR _hoops_ISHA _hoops_IAGA _hoops_HII 1 _hoops_IS 2 */
		source		= point1;
		_hoops_GIHPR = point2;
	}
	else {
		/* _hoops_CPIHR _hoops_ISHA _hoops_IAGA _hoops_HII 2 _hoops_IS 1 */
		source		= point2;
		_hoops_GIHPR = point1;
	}

	_hoops_ASRGR = &_hoops_HHHPR[source];

	while (!((_hoops_HAGPA = *_hoops_ASRGR) == null || _hoops_HAGPA->_hoops_GIHPR >= _hoops_GIHPR))
		_hoops_ASRGR = &_hoops_HAGPA->next;

	if (_hoops_HAGPA != null && _hoops_HAGPA->_hoops_GIHPR == _hoops_GIHPR) {
		/* _hoops_GSGI _hoops_PCCP _hoops_APRS _hoops_SPR */
		if (_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR == _hoops_PIIPR)
			_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR = face;
		else {
			_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR = _hoops_IAGPA;
		}
	}
	else {
		/* _hoops_HAR _hoops_GSGI - _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_ISHA */
		ALLOC (_hoops_HAGPA, _hoops_AAGPA);
		_hoops_HAGPA->next = *_hoops_ASRGR;
		*_hoops_ASRGR = _hoops_HAGPA;
		_hoops_HAGPA->_hoops_GIHPR = _hoops_GIHPR;
		_hoops_HAGPA->_hoops_SGCPR._hoops_AIIPR = face;
		_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR = _hoops_PIIPR;
		return 1;
	}

	return 0;
}

local void _hoops_CAGPA (
	int						pcount,
	int						flist_length,
	int *					_hoops_SAGPA, 
	int *					_hoops_SPHA,
	_hoops_RHHPR **	_hoops_GRCPR,
	_hoops_RHHPR ***	_hoops_GPGPA,
	_hoops_CGCPR **			_hoops_SGCPR) {
	int *					_hoops_ASPH = _hoops_SAGPA;
	int *					_hoops_HICPR = _hoops_ASPH + flist_length;
	int						face = -1;
	_hoops_AAGPA **		_hoops_HHHPR;

	*_hoops_SPHA = 0;

	// "+1" _hoops_PGGA _hoops_SR'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_SICR _hoops_RGR _hoops_CRPR _hoops_CRGR _hoops_RH _hoops_RRCPR->_hoops_RPGPA _hoops_CRPR _hoops_SPHR
	ZALLOC_ARRAY_CACHED (_hoops_HHHPR, pcount + 1, _hoops_AAGPA *);

	_hoops_RGGA (_hoops_ASPH == _hoops_HICPR) {
		int		*_hoops_CICPR;

		if (*_hoops_ASPH++ < 0)			/* (_hoops_RCCPR _hoops_GGR _hoops_RH _hoops_PGHC _hoops_HSP) */
			_hoops_CICPR = _hoops_ASPH - _hoops_ASPH[-1];
		else {						/* (_hoops_GSSR _hoops_CCAH _hoops_HSP) */
			_hoops_CICPR = _hoops_ASPH + _hoops_ASPH[-1];
			++face;
		}

		if (_hoops_ASPH != _hoops_CICPR) {
			int				_hoops_PICPR;
			int				_hoops_IICPR;
			int				_hoops_AICPR = 0;

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

				*_hoops_SPHA += _hoops_PAGPA (_hoops_AICPR, _hoops_PICPR, face,
												_hoops_HHHPR);

				_hoops_PICPR = _hoops_AICPR;
			}
		}
	}

	if (*_hoops_SPHA > 0 && _hoops_SGCPR != NULL) {
		_hoops_CGCPR *_hoops_APGPA;
		_hoops_AAGPA	*_hoops_HAGPA;
		_hoops_AAGPA	**_hoops_PPGPA = _hoops_HHHPR;
		_hoops_AAGPA	**_hoops_HPGPA = _hoops_PPGPA + pcount;

		ALLOC_ARRAY_CACHED (_hoops_APGPA, *_hoops_SPHA, _hoops_CGCPR);
		*_hoops_SGCPR = _hoops_APGPA;

		do {
			/* _hoops_IH _hoops_GRR _hoops_AH _hoops_ISHA, _hoops_IPGPA _hoops_PRIA _hoops_RH _hoops_RSSI */
			if ((_hoops_HAGPA = *_hoops_PPGPA) != null) do {
				_hoops_APGPA->_hoops_AIIPR = _hoops_HAGPA->_hoops_SGCPR._hoops_AIIPR;
				_hoops_APGPA->_hoops_HIIPR = _hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR;
				++_hoops_APGPA;
			} _hoops_RGGA ((_hoops_HAGPA = _hoops_HAGPA->next) == null);
		} _hoops_RGGA (++_hoops_PPGPA == _hoops_HPGPA);
	}

	if (sizeof(_hoops_AAGPA *) != sizeof(_hoops_RHHPR *))
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Oh drat");

	*_hoops_GPGPA = (_hoops_RHHPR **)_hoops_HHHPR;
	
	{
		_hoops_RHHPR *	_hoops_SRCPR; /* _hoops_RH _hoops_CPGPA _hoops_PIH */
		bool					_hoops_SPGPA	 = true;
		bool					_hoops_GHGPA = true;
		_hoops_AAGPA *			_hoops_HAGPA;
		_hoops_AAGPA **		_hoops_PPGPA = _hoops_HHHPR;
		_hoops_AAGPA **		_hoops_HPGPA = _hoops_PPGPA + pcount;

		/* _hoops_AGGA _hoops_SAGR _hoops_RH _hoops_CCHHR _hoops_CPCI _hoops_CRGR _hoops_IRS _hoops_RSRA _hoops_CRPR */

		if (*_hoops_SPHA > 0) {
			ALLOC_ARRAY_CACHED (_hoops_SRCPR, *_hoops_SPHA, _hoops_RHHPR);
			*_hoops_GRCPR = _hoops_SRCPR;
		}
		else
			*_hoops_GRCPR = _hoops_SRCPR = null;

		do {
			/* _hoops_HGCR _hoops_RH _hoops_CCHHR _hoops_HIGR _hoops_IIGR _hoops_AH _hoops_ISHA _hoops_SIHC */
			_hoops_HAGPA = *_hoops_PPGPA;

			/*
			 * _hoops_RHGPA _hoops_RIR-_hoops_HCGP-_hoops_GPHA _hoops_CRS _hoops_IS _hoops_PPSR _hoops_HPGR _hoops_RH _hoops_CACHR
			 * _hoops_PIH
			 */
			*(_hoops_RHHPR **)_hoops_PPGPA = _hoops_SRCPR;

			/*_hoops_IH _hoops_GRR _hoops_AH _hoops_ISHA, _hoops_IPGPA _hoops_PRIA _hoops_RH _hoops_GHSPR*/
			_hoops_RGGA (_hoops_HAGPA == null) {
				_hoops_AAGPA	*victim;

				/*
				 * _hoops_IPCP _hoops_RRCPR _hoops_HRGR _hoops_CAHC _hoops_CHGRR _hoops_HCR _hoops_SPPR _hoops_HS _hoops_HPGR _hoops_CHGC _hoops_PGCR _hoops_RSSI.
				 * _hoops_HHIGR _hoops_HRGR _hoops_AHGPA _hoops_CHGRR _hoops_GRR _hoops_ISHA _hoops_SSCP _hoops_PSP _hoops_RRI _hoops_HSAR _hoops_PGCR _hoops_RSSI.
				 */
				if (_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR == _hoops_PIIPR) _hoops_SPGPA = false;
				if (_hoops_HAGPA->_hoops_SGCPR._hoops_HIIPR == _hoops_IAGPA) _hoops_GHGPA = false;

				/* _hoops_IPS _hoops_RH _hoops_PHGPA */
				_hoops_SRCPR->_hoops_GIHPR = _hoops_HAGPA->_hoops_GIHPR;
				++_hoops_SRCPR;

				/* _hoops_IHSH _hoops_HPGR _hoops_RH _hoops_SPS _hoops_AH _hoops_PASPR _hoops_SIHC */
				victim = _hoops_HAGPA;
				_hoops_HAGPA = _hoops_HAGPA->next;
				FREE (victim, _hoops_AAGPA);
			}

			/* _hoops_CCGR _hoops_IIH _hoops_CHR _hoops_PSP _hoops_RRI _hoops_HCGP _hoops_GIHA */
		} _hoops_RGGA (++_hoops_PPGPA == _hoops_HPGPA);

		/* _hoops_CISA _hoops_GGR _hoops_RH _hoops_HACH (_hoops_SHCAR, _hoops_RSHS + 1) _hoops_RARP */
		*(_hoops_RHHPR **)_hoops_PPGPA = _hoops_SRCPR;
	}

	return;
}



/* _hoops_HGI _hoops_API _hoops_PAPRR _hoops_RH _hoops_HHGPA _hoops_IIGR _hoops_IRS _hoops_ARP _hoops_IIGR _hoops_IRPAA _hoops_RSSA */
local bool _hoops_IHGPA (
	_hoops_CGGPA *		vertices,
	int				count,
	Point const *	points,
	Vector *		normal,
	int *			_hoops_GGCIR,
	int *			list) {
	float 			length;
	float 			_hoops_CHGPA, _hoops_SHGPA, _hoops_GIGPA, _hoops_RIGPA, _hoops_AIGPA, _hoops_PIGPA;
	float 			_hoops_SSRP;
	Point 			_hoops_HIGPA;
	Point 			_hoops_IIGPA;
	int 			i;
	int 			origin;
	int 			_hoops_GGSSR;

	*_hoops_GGCIR = 0;

	/* _hoops_IPCP _hoops_RSSA _hoops_GGR _hoops_GIHA _hoops_RGCA _hoops_SHH _hoops_GGR _hoops_GSHHR _hoops_AGR (_hoops_HII -_hoops_SISR _hoops_IS +_hoops_SISR), _hoops_IAII _hoops_RGR _hoops_RIIRA _hoops_PPPPR'_hoops_RA _hoops_IPHR.
	 * _hoops_PHGP _hoops_IIS'_hoops_GRI _hoops_SAHR _hoops_AA _hoops_IRS _hoops_HHCI _hoops_RPGP _hoops_IS _hoops_IRHH _hoops_RCRR _hoops_HPGR _hoops_CHGC _hoops_RH _hoops_SISR'_hoops_GRI _hoops_CHR _hoops_GSHHR. _hoops_CGP _hoops_HAR, _hoops_GHIS _hoops_SCH _hoops_CAIR.
	 * _hoops_HIPR, _hoops_SSRS _hoops_RSSA _hoops_SIAS _hoops_CIGPA _hoops_RH _hoops_RIIRA, _hoops_HIS _hoops_AAH _hoops_IS _hoops_SIGPA _hoops_RH _hoops_HIGR _hoops_SRS.
	 */
	for (i = 0; i < count-1; i++) {
		if (vertices[i].x > vertices[i+1].x) {
			HE_ERROR (HEC_COMPUTE, HEC_INVALID_INPUT, "Vertex array must be in fully sorted order.");
			return false;
		}
	}

	/* _hoops_PHAA, _hoops_HGCR _hoops_RH _hoops_GSSR _hoops_IIGR _hoops_RH _hoops_IPPA. */
	if (normal == null) {
		_hoops_CHGPA = vertices[1].x - vertices[0].x;
		_hoops_SHGPA = vertices[1].y - vertices[0].y;
		_hoops_GIGPA = vertices[1].z - vertices[0].z;
		_hoops_RIGPA = vertices[2].x - vertices[0].x;
		_hoops_AIGPA = vertices[2].y - vertices[0].y;
		_hoops_PIGPA = vertices[2].z - vertices[0].z;
		_hoops_HIGPA.x = _hoops_SHGPA*_hoops_PIGPA - _hoops_GIGPA*_hoops_AIGPA;
		_hoops_HIGPA.y = _hoops_GIGPA*_hoops_RIGPA - _hoops_CHGPA*_hoops_PIGPA;
		_hoops_HIGPA.z = _hoops_CHGPA*_hoops_AIGPA - _hoops_SHGPA*_hoops_RIGPA;

		/* _hoops_HPGIR _hoops_RH _hoops_AAGA, _hoops_PPR _hoops_CAHA _hoops_GGSR _hoops_RPP _hoops_SCH _hoops_HCAAA _hoops_IRS _hoops_RPHR _hoops_PAR _hoops_RAAP _hoops_AGSGR */
		length = sqrt(_hoops_HIGPA.x*_hoops_HIGPA.x + _hoops_HIGPA.y*_hoops_HIGPA.y + _hoops_HIGPA.z*_hoops_HIGPA.z);
		_hoops_HIGPA.x /= length;
		_hoops_HIGPA.y /= length;
		_hoops_HIGPA.z /= length;
	}
	else {
		_hoops_HIGPA.x = -normal->x;
		_hoops_HIGPA.y = -normal->y;
		_hoops_HIGPA.z = -normal->z;
	}

	/* _hoops_RAH _hoops_RH _hoops_AAPA _hoops_GCGPA _hoops_SRS */
	/* =================================================== */
	/* _hoops_PHHR _hoops_RHIR _hoops_HCR _hoops_RH _hoops_RSSA _hoops_GGR _hoops_AHGP _hoops_SISR _hoops_AGR. */
	for (i = 0; i < count; i++) {
		/* _hoops_ARR _hoops_SR'_hoops_RISP _hoops_GGHP _hoops_RRI _hoops_HSAR 2 _hoops_CGSI _hoops_GGR _hoops_RH _hoops_HIGR, _hoops_SR _hoops_PAH _hoops_HSPP _hoops_IPAC _hoops_RAAP/_hoops_RPHR _hoops_RCGPA */
		while (*_hoops_GGCIR > 1) {
			origin = *_hoops_GGCIR-1;
			_hoops_GGSSR = *_hoops_GGCIR;
			
			_hoops_CHGPA = vertices[i].x - points[list[origin]].x;
			_hoops_SHGPA = vertices[i].y - points[list[origin]].y;
			_hoops_GIGPA = vertices[i].z - points[list[origin]].z;
			_hoops_RIGPA = points[list[_hoops_GGSSR]].x - points[list[origin]].x;
			_hoops_AIGPA = points[list[_hoops_GGSSR]].y - points[list[origin]].y;
			_hoops_PIGPA = points[list[_hoops_GGSSR]].z - points[list[origin]].z;
			_hoops_IIGPA.x = _hoops_SHGPA*_hoops_PIGPA - _hoops_GIGPA*_hoops_AIGPA;
			_hoops_IIGPA.y = _hoops_GIGPA*_hoops_RIGPA - _hoops_CHGPA*_hoops_PIGPA;
			_hoops_IIGPA.z = _hoops_CHGPA*_hoops_AIGPA - _hoops_SHGPA*_hoops_RIGPA;
			length = sqrt(_hoops_IIGPA.x*_hoops_IIGPA.x + _hoops_IIGPA.y*_hoops_IIGPA.y + _hoops_IIGPA.z*_hoops_IIGPA.z);
			
			if (length > 0) {
				_hoops_IIGPA.x /= length;
				_hoops_IIGPA.y /= length;
				_hoops_IIGPA.z /= length;
			}

			_hoops_SSRP = _hoops_IIGPA.x*_hoops_HIGPA.x + _hoops_IIGPA.y*_hoops_HIGPA.y + _hoops_IIGPA.z*_hoops_HIGPA.z;

			/* _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_RPHR _hoops_AGSGR, _hoops_PAR _hoops_RH _hoops_RSSA _hoops_CHR _hoops_GARAA, _hoops_PSCR _hoops_HSCI _hoops_IRGP _hoops_PPSR */
			if (_hoops_SSRP < 0.5f)
				(*_hoops_GGCIR)--;

			/* _hoops_IAII, _hoops_SR _hoops_ACGPA _hoops_HS _hoops_IRS _hoops_RPHR _hoops_AGSGR, _hoops_HIS _hoops_SR'_hoops_ASAR _hoops_CPHR _hoops_IPAC _hoops_PPR _hoops_IHSA _hoops_RH _hoops_HAPR */
			else
				break;
		}

		list[*_hoops_GGCIR+1] = vertices[i].index;
		(*_hoops_GGCIR)++;
	}

	/* _hoops_AGGA _hoops_AA _hoops_RH _hoops_GSSC _hoops_GCGPA */
	/* =================================================== */
	/* _hoops_PHHR _hoops_RHIR _hoops_HCR _hoops_RH _hoops_RSSA _hoops_GGR _hoops_HSRAR _hoops_SISR _hoops_AGR. */
	for (i = count-2; i >= 0; i--) {
		/* _hoops_ARR _hoops_SR'_hoops_RISP _hoops_GGHP _hoops_RRI _hoops_HSAR 2 _hoops_CGSI _hoops_GGR _hoops_RH _hoops_HIGR, _hoops_SR _hoops_PAH _hoops_HSPP _hoops_IPAC _hoops_RAAP/_hoops_RPHR _hoops_RCGPA */
		// _hoops_HIH _hoops_SHR _hoops_PCGPA _hoops_HPGR _hoops_CHGC _hoops_RH _hoops_SRS 2 _hoops_HII _hoops_RH _hoops_SRS _hoops_HAPR
		while (*_hoops_GGCIR > 2) {
			origin = *_hoops_GGCIR-1;
			_hoops_GGSSR = *_hoops_GGCIR;

			_hoops_CHGPA = vertices[i].x - points[list[origin]].x;
			_hoops_SHGPA = vertices[i].y - points[list[origin]].y;
			_hoops_GIGPA = vertices[i].z - points[list[origin]].z;
			_hoops_RIGPA = points[list[_hoops_GGSSR]].x - points[list[origin]].x;
			_hoops_AIGPA = points[list[_hoops_GGSSR]].y - points[list[origin]].y;
			_hoops_PIGPA = points[list[_hoops_GGSSR]].z - points[list[origin]].z;
			_hoops_IIGPA.x = _hoops_SHGPA*_hoops_PIGPA - _hoops_GIGPA*_hoops_AIGPA;
			_hoops_IIGPA.y = _hoops_GIGPA*_hoops_RIGPA - _hoops_CHGPA*_hoops_PIGPA;
			_hoops_IIGPA.z = _hoops_CHGPA*_hoops_AIGPA - _hoops_SHGPA*_hoops_RIGPA;
			length = sqrt(_hoops_IIGPA.x*_hoops_IIGPA.x + _hoops_IIGPA.y*_hoops_IIGPA.y + _hoops_IIGPA.z*_hoops_IIGPA.z);
			
			if (length > 0) {
				_hoops_IIGPA.x /= length;
				_hoops_IIGPA.y /= length;
				_hoops_IIGPA.z /= length;
			}

			_hoops_SSRP = _hoops_IIGPA.x*_hoops_HIGPA.x + _hoops_IIGPA.y*_hoops_HIGPA.y + _hoops_IIGPA.z*_hoops_HIGPA.z;

			/* _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_IRCC _hoops_IS _hoops_GGCR _hoops_IRS _hoops_ASPSR _hoops_PPSR */
			if (_hoops_CHGPA == 0 && _hoops_SHGPA == 0 && _hoops_GIGPA == 0)
				break;
			/* _hoops_RPP _hoops_SR _hoops_GA'_hoops_RA _hoops_HS _hoops_IRS _hoops_RPHR _hoops_AGSGR, _hoops_PAR _hoops_RH _hoops_RSSA _hoops_CHR _hoops_GARAA, _hoops_PSCR _hoops_HSCI _hoops_IRGP _hoops_PPSR */
			if (_hoops_SSRP < 0.5f)
				(*_hoops_GGCIR)--;
			/* _hoops_IAII, _hoops_SR _hoops_ACGPA _hoops_HS _hoops_IRS _hoops_RPHR _hoops_AGSGR, _hoops_HIS _hoops_SR'_hoops_ASAR _hoops_CPHR _hoops_IPAC _hoops_PPR _hoops_IHSA _hoops_RH _hoops_HAPR */
			else
				break;
		}

		if (i != 0) {
			list[*_hoops_GGCIR+1] = vertices[i].index;
			(*_hoops_GGCIR)++;
		}
	}

	list[0] = *_hoops_GGCIR;
	(*_hoops_GGCIR)++;

	return true;
}

#define QS_POINT_COMPARE(thing,f1,f2) \
		((thing.in_points[thing._hoops_PRGPA[f1]].x > thing.in_points[thing._hoops_PRGPA[f2]].x) || \
		(thing.in_points[thing._hoops_PRGPA[f1]].x == thing.in_points[thing._hoops_PRGPA[f2]].x && \
			thing.in_points[thing._hoops_PRGPA[f1]].y > thing.in_points[thing._hoops_PRGPA[f2]].y) || \
		(thing.in_points[thing._hoops_PRGPA[f1]].x == thing.in_points[thing._hoops_PRGPA[f2]].x && \
			thing.in_points[thing._hoops_PRGPA[f1]].y == thing.in_points[thing._hoops_PRGPA[f2]].y && \
			thing.in_points[thing._hoops_PRGPA[f1]].z >= thing.in_points[thing._hoops_PRGPA[f2]].z))

#define QS_TYPE				QSP
#define QS_VAL(thing,a)		(thing.in_points[thing._hoops_PRGPA[a]].x)
#define QS_COMPLEX_COMPARE(thing, f1,f2) QS_POINT_COMPARE(thing,f1,f2)
#define QS_SWAP(thing,a,b)	{int c = thing._hoops_PRGPA[b]; \
							thing._hoops_PRGPA[b] = thing._hoops_PRGPA[a]; \
							thing._hoops_PRGPA[a] = c;} 		/* _hoops_SPIHR _hoops_PGCR _hoops_HSH */
#include "utility/hqsort.h"



HC_INTERFACE void HC_CDECL HC_Compute_Convex_Hull (
	int						count,
	Point const *			points,
	int *					_hoops_GGCIR,
	int alter *				_hoops_HCGPA) 
{
	_hoops_PAPPR context("Compute_Convex_Hull");

#ifdef DISABLE_COMPUTE
	_hoops_IRPPR ("Compute");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Compute_Convex_Hull () */\n");
	);

	int						_hoops_ICGPA = count;
	_hoops_CGGPA *				vertices;
	_hoops_CGGPA *				_hoops_CCGPA = null;
	_hoops_CGGPA *				_hoops_SCGPA = null;
	_hoops_RRGPA *				faces = null;
	_hoops_RRGPA *				_hoops_GSGPA = null;
	_hoops_ARGPA *				open = null;

	_hoops_CGGPA					*_hoops_RSGPA, *_hoops_ASGPA;
	_hoops_RRGPA				*_hoops_PSGPA, *_hoops_HSGPA;
	_hoops_ARGPA				*_hoops_ISGPA, *_hoops_CSGPA;
	_hoops_GRGPA				*_hoops_SSGPA;

	int						i = 0;
	Vector *				_hoops_PRHH = null;
	int						_hoops_GGRPA = 0;
	int *					list;		/* _hoops_AH _hoops_HIGR */
	int *					_hoops_RGRPA;
	QSP						_hoops_AGRPA;
	int *					_hoops_PGRPA;
	int						_hoops_HGRPA = 0, _hoops_IGRPA = 0;
	int						_hoops_CGRPA = 0, _hoops_SGRPA = 0;
	int						_hoops_GRRPA = 0, _hoops_RRRPA = 0;

	if (count == 0) {
		*_hoops_GGCIR = 0;
		return;
	}

	ALLOC_ARRAY_CACHED(list, 8*count, int);
	_hoops_RGRPA = list;
	_hoops_AGRPA.in_points = points;

	/* _hoops_IPS _hoops_GIHA */
	/* ======================================================================= */
	/* _hoops_PHAA, _hoops_GHIS _hoops_RH _hoops_HIGR */
	ALLOC_ARRAY_CACHED(_hoops_PGRPA,_hoops_ICGPA,int);
	for (i = 0; i < _hoops_ICGPA; i++)
		_hoops_PGRPA[i] = i;

	_hoops_AGRPA._hoops_PRGPA = &_hoops_PGRPA[0];
	quick_sort(_hoops_AGRPA,0, _hoops_ICGPA - 1);

	ALLOC_ARRAY_CACHED (vertices, _hoops_ICGPA, _hoops_CGGPA);
	_hoops_RSGPA = vertices;
	count = 0;
	i = 0;
	while (i < _hoops_ICGPA) {
		_hoops_RSGPA->next = _hoops_RSGPA + 1;
		_hoops_RSGPA->prev = _hoops_RSGPA - 1;

		/* _hoops_RPP _hoops_RH _hoops_SPS _hoops_PPSR _hoops_HRGR _hoops_HAR _hoops_IRS _hoops_SSRS _hoops_IIGR _hoops_RH _hoops_PGHC _hoops_SPR, _hoops_PSCR _hoops_GGCR _hoops_IS _hoops_HIGR */
		if (i == 0 ||
			points[_hoops_PGRPA[i]].x != _hoops_RSGPA->prev->x ||
			points[_hoops_PGRPA[i]].y != _hoops_RSGPA->prev->y ||
			points[_hoops_PGRPA[i]].z != _hoops_RSGPA->prev->z) {
			_hoops_RSGPA->index = _hoops_PGRPA[i];
			_hoops_RSGPA->x = points[_hoops_PGRPA[i]].x;
			_hoops_RSGPA->y = points[_hoops_PGRPA[i]].y;
			_hoops_RSGPA->z = points[_hoops_PGRPA[i]].z;
			_hoops_RSGPA->_hoops_HIHI = 0;

			/* _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_RGR _hoops_PPSR _hoops_HRGR _hoops_PCCP _hoops_HICAA _hoops_PPSR */
			if (_hoops_RSGPA->x > vertices[_hoops_IGRPA].x)
				_hoops_IGRPA = count;
			else if (_hoops_RSGPA->x < vertices[_hoops_HGRPA].x)
				_hoops_HGRPA = count;
			if (_hoops_RSGPA->y > vertices[_hoops_SGRPA].y)
				_hoops_SGRPA = count;
			else if (_hoops_RSGPA->y < vertices[_hoops_CGRPA].y)
				_hoops_CGRPA = count;
			if (_hoops_RSGPA->z > vertices[_hoops_RRRPA].z)
				_hoops_RRRPA = count;
			else if (_hoops_RSGPA->z < vertices[_hoops_GRRPA].z)
				_hoops_GRRPA = count;

			count++;
			_hoops_RSGPA++;
		}
		i++;
	}
	vertices[0].prev = null;
	vertices[count-1].next = null;

	_hoops_CCGPA = vertices;

	FREE_ARRAY(_hoops_PGRPA,_hoops_ICGPA,int);

	*_hoops_GGCIR = 0;


	/* _hoops_HHCI _hoops_ARRPA _hoops_ISPR */
	/* ======================================================================= */
	if (count < 3) {
		HE_ERROR (HEC_COMPUTE, HES_INVALID_COUNT, "Less than three unique points given to Compute_Convex_Hull");
		goto _hoops_HPAGR;
	}

	if (count == 3) {
		_hoops_CGGPA const	*p1 = &vertices[0],
						*p2 = &vertices[1],
						*_hoops_IAPH = &vertices[2];

		if ((_hoops_IAPH->y - p1->y)*(p2->z - p1->z) - (_hoops_IAPH->z - p1->z)*(p2->y - p1->y) == 0.0f &&
			(_hoops_IAPH->z - p1->z)*(p2->x - p1->x)	- (_hoops_IAPH->x - p1->x)*(p2->z - p1->z) == 0.0f &&
			(_hoops_IAPH->x - p1->x)*(p2->y - p1->y)	- (_hoops_IAPH->y - p1->y)*(p2->x - p1->x) == 0.0f) {
				/* _hoops_GARAA/_hoops_ASPSR */
				goto _hoops_HPAGR;
		}

		/* _hoops_IHGP _hoops_SCPH */
		_hoops_HCGPA[0] = 3;
		_hoops_HCGPA[1] = vertices[0].index;
		_hoops_HCGPA[2] = vertices[1].index;
		_hoops_HCGPA[3] = vertices[2].index;
		*_hoops_GGCIR = 4;
		
		goto _hoops_HPAGR;
	}


	/* _hoops_IRHH _hoops_PRRPA _hoops_HRRPA */
	/* _hoops_HGCR _hoops_IRRPA _hoops_CRRPA */
	/* ======================================================================= */
	{
		_hoops_CGGPA			*p1, *p2, *_hoops_IAPH, *_hoops_SRRPA;
		int first_four[4];
		float _hoops_GARPA = vertices[_hoops_IGRPA].x - vertices[_hoops_HGRPA].x;
		float _hoops_RARPA = vertices[_hoops_SGRPA].y - vertices[_hoops_CGRPA].y;
		float _hoops_AARPA = vertices[_hoops_RRRPA].z - vertices[_hoops_GRRPA].z;
		float _hoops_PARPA = 0;
		float _hoops_HARPA = 1;

		/* _hoops_SRCH _hoops_SAPS _hoops_PPSR _hoops_GPPS _hoops_SPHS _hoops_RPP _hoops_HAHH */
		if (_hoops_GARPA > 0 && _hoops_GARPA < _hoops_RARPA && _hoops_GARPA < _hoops_AARPA)
			_hoops_HARPA = _hoops_GARPA;
		else if (_hoops_RARPA > 0 && _hoops_RARPA < _hoops_GARPA && _hoops_RARPA < _hoops_AARPA)
			_hoops_HARPA = _hoops_RARPA;
		else if (_hoops_AARPA > 0 && _hoops_AARPA < _hoops_GARPA && _hoops_AARPA < _hoops_RARPA)
			_hoops_HARPA = _hoops_AARPA;
		if (_hoops_HARPA < _hoops_HRGPA) {
			for (i = 0; i < count; i++) {
				vertices[i].x /= _hoops_HARPA;
				vertices[i].y /= _hoops_HARPA;
				vertices[i].z /= _hoops_HARPA;
			}
		}

		/* _hoops_HGI _hoops_SRS _hoops_PRGGR (_hoops_IARPA _hoops_CARPA[4]) _hoops_HRGR _hoops_SAHR _hoops_IS _hoops_CAHA _hoops_GGSR _hoops_RH _hoops_CIGS _hoops_RSSA,
		* _hoops_ARPP _hoops_SR _hoops_IGRC _hoops_HSPP _hoops_GRP _hoops_CAPR
		*/

		/* _hoops_SSCR _hoops_GGSR _hoops_RH _hoops_SRS 2 _hoops_PPISR _hoops_IS _hoops_SGH.  _hoops_PS _hoops_HGCR _hoops_RH _hoops_IRRPA _hoops_CRRPA, _hoops_PPR _hoops_PSCR 
		* _hoops_CAHA _hoops_GGSR _hoops_IRS _hoops_HRSSR _hoops_PPSR _hoops_SGS _hoops_CHH _hoops_CAHP _hoops_RH _hoops_SARPA _hoops_SCPH.
		*/
		if (_hoops_GARPA >= _hoops_RARPA && _hoops_GARPA >= _hoops_AARPA) {
			first_four[0] = _hoops_HGRPA;
			first_four[1] = _hoops_IGRPA;
		}
		else if (_hoops_RARPA >= _hoops_GARPA && _hoops_RARPA >= _hoops_AARPA) {
			first_four[0] = _hoops_CGRPA;
			first_four[1] = _hoops_SGRPA;
		}
		else {
			first_four[0] = _hoops_GRRPA;
			first_four[1] = _hoops_RRRPA;
		}

		/* _hoops_RH _hoops_HRSSR _hoops_CIHA _hoops_HRGR _hoops_RH _hoops_PPSR _hoops_GPRPA _hoops_HII _hoops_RH _hoops_III */
		float f, g, h;
		float _hoops_SSHGA;

		f = vertices[first_four[1]].x - vertices[first_four[0]].x;
		g = vertices[first_four[1]].y - vertices[first_four[0]].y;
		h = vertices[first_four[1]].z - vertices[first_four[0]].z;

		_hoops_SSHGA = f*f + g*g + h*h;

		_hoops_PARPA = 0;
		for (i = 0; i < count; i++) {
			if (i != first_four[0] && i != first_four[1]) {
				float _hoops_RPRPA, _hoops_APRPA, _hoops_PPRPA;
				float _hoops_HPRPA, _hoops_IPRPA, _hoops_CPRPA;
				float _hoops_ISPI, _hoops_CSPI, _hoops_SSPI;
				float r;

				_hoops_RPRPA = vertices[i].x - vertices[first_four[0]].x;
				_hoops_APRPA = vertices[i].y - vertices[first_four[0]].y;
				_hoops_PPRPA = vertices[i].z - vertices[first_four[0]].z;

				_hoops_HPRPA = f*_hoops_APRPA - g*_hoops_RPRPA;
				_hoops_IPRPA = f*_hoops_PPRPA - h*_hoops_RPRPA;
				_hoops_CPRPA = g*_hoops_PPRPA - h*_hoops_APRPA;

				_hoops_ISPI = g*_hoops_HPRPA + h*_hoops_IPRPA;
				_hoops_CSPI = h*_hoops_CPRPA - f*_hoops_HPRPA;
				_hoops_SSPI = -f*_hoops_IPRPA - g*_hoops_CPRPA;

				r = sqrt(_hoops_ISPI*_hoops_ISPI + _hoops_CSPI*_hoops_CSPI + _hoops_SSPI*_hoops_SSPI) / _hoops_SSHGA;

				/* _hoops_RPP _hoops_RGR _hoops_CCAH _hoops_PPSR _hoops_HRGR _hoops_RH _hoops_GPRPA _hoops_SGGR _hoops_HII _hoops_GIPR _hoops_RH _hoops_RII _hoops_RSSA, _hoops_PPR _hoops_HRGR _hoops_HAR _hoops_SPRPA... */
				if (r > _hoops_PARPA) {
					first_four[2] = i;
					_hoops_PARPA = r;
					/* _hoops_HPGR _hoops_RGR _hoops_PPSR, _hoops_GHRPA _hoops_CGH _hoops_HAR _hoops_SHH 0 (_hoops_RPP _hoops_SCH _hoops_HRGR, _hoops_PSCR _hoops_RH 3 _hoops_RSSA _hoops_CHR _hoops_SPRPA) */
				}
			}
		}

		if (_hoops_PARPA >= _hoops_IRGPA) {
			/* _hoops_RH _hoops_SCHCR _hoops_CIHA _hoops_HRGR _hoops_RH _hoops_PPSR _hoops_GPRPA _hoops_SGGR _hoops_HII _hoops_RH _hoops_IPPA _hoops_PAPR _hoops_HPP _hoops_RH _hoops_SRS 3 */
			float a, b, c, d;
			float _hoops_CHGPA, _hoops_SHGPA, _hoops_GIGPA, _hoops_RIGPA, _hoops_AIGPA, _hoops_PIGPA;

			/* _hoops_SRS, _hoops_HGCR _hoops_CGSSR _hoops_IIGR _hoops_IPPA */
			_hoops_CHGPA = vertices[first_four[1]].x - vertices[first_four[0]].x;
			_hoops_SHGPA = vertices[first_four[1]].y - vertices[first_four[0]].y;
			_hoops_GIGPA = vertices[first_four[1]].z - vertices[first_four[0]].z;
			_hoops_RIGPA = vertices[first_four[2]].x - vertices[first_four[0]].x;
			_hoops_AIGPA = vertices[first_four[2]].y - vertices[first_four[0]].y;
			_hoops_PIGPA = vertices[first_four[2]].z - vertices[first_four[0]].z;
			a = _hoops_SHGPA*_hoops_PIGPA - _hoops_GIGPA*_hoops_AIGPA;
			b = _hoops_GIGPA*_hoops_RIGPA - _hoops_CHGPA*_hoops_PIGPA;
			c = _hoops_CHGPA*_hoops_AIGPA - _hoops_SHGPA*_hoops_RIGPA;
			d = -(a*vertices[first_four[0]].x + b*vertices[first_four[0]].y + c*vertices[first_four[0]].z);

			_hoops_PARPA = 0;
			for (i = 0; i < count; i++) {
				if (i != first_four[0] && i != first_four[1] && i != first_four[2]) {
					float dist;
					dist = a*vertices[i].x + b*vertices[i].y + c*vertices[i].z + d;
					dist = dist*dist / (a*a + b*b + c*c);

					if (dist > _hoops_PARPA) {
						first_four[3] = i;
						_hoops_PARPA = dist;
					}
				}
			}
		}

		/* _hoops_RHRPA _hoops_RGR _hoops_PPSR, _hoops_RPP _hoops_RH _hoops_SCHCR _hoops_PPSR _hoops_HRGR _hoops_IRPAA _hoops_CCA _hoops_RH _hoops_SRS _hoops_HRSP, _hoops_PSCR _hoops_SR _hoops_ACPA _hoops_SGS _hoops_HCR _hoops_IIGR _hoops_RH _hoops_RSSA _hoops_CHR _hoops_GGR _hoops_RH _hoops_PSHR
		* _hoops_IPPA. _hoops_PS _hoops_SGH _hoops_IRS 2d _hoops_SGCS _hoops_GCGPA _hoops_RIIRA _hoops_IS _hoops_RGHH _hoops_RGR.
		* _hoops_HHPC, _hoops_SAS _hoops_CCA _hoops_RH _hoops_GSSR 3d _hoops_SGCS _hoops_GCGPA _hoops_RIIRA.
		*/
		if (_hoops_PARPA < _hoops_IRGPA) {
			/* _hoops_CGP _hoops_SR _hoops_HS _hoops_IRS _hoops_CCGC 2d _hoops_HSSP, _hoops_PSCR _hoops_IRHH 2 _hoops_RSSI (_hoops_SPR _hoops_GGR _hoops_GRR _hoops_HAGA). 
			 * _hoops_HGI _hoops_CHH _hoops_CRHR _hoops_HPPHR _hoops_IAPRR _hoops_AHRPA.
			 */
			_hoops_IHGPA(vertices, count, points, null, _hoops_GGCIR, _hoops_HCGPA);
			_hoops_HCGPA[*_hoops_GGCIR] = _hoops_HCGPA[0];
			for (i = 1; i < *_hoops_GGCIR; i++)
				_hoops_HCGPA[2*(*_hoops_GGCIR) - i] = _hoops_HCGPA[i];
			(*_hoops_GGCIR) *= 2;
		}
		/* _hoops_HGI _hoops_CRAA _hoops_PHRPA _hoops_RH "3d _hoops_SGCS _hoops_GCGPA" _hoops_RIIRA */
		else {
			/* _hoops_AGGA _hoops_SGS _hoops_SR _hoops_HS _hoops_RH _hoops_SRS _hoops_AIAA _hoops_RSSA, _hoops_SR _hoops_PAH _hoops_HGSR _hoops_RH _hoops_CCHHR _hoops_CPCI */

			/* _hoops_SRS _hoops_PPSR */
			if ((p1 = &vertices[first_four[0]]) == _hoops_CCGPA)
				_hoops_CCGPA = _hoops_CCGPA->next;
			if (p1->prev != null)
				p1->prev->next = p1->next;
			if (p1->next != null)
				p1->next->prev = p1->prev;
			p1->next = p1->prev = null;

			/* _hoops_GIAP _hoops_PPSR (_hoops_GRAA-_hoops_ASPSR)*/
			if ((p2 = &vertices[first_four[1]]) == _hoops_CCGPA)
				_hoops_CCGPA = _hoops_CCGPA->next;
			if (p2->prev != null)
				p2->prev->next = p2->next;
			if (p2->next != null)
				p2->next->prev = p2->prev;
			p2->next = p2->prev = null;


			/* _hoops_HRSSR _hoops_PPSR (_hoops_GRAA-_hoops_IISGR) */
			_hoops_IAPH = &vertices[first_four[2]];
			if ((_hoops_IAPH->y - p1->y)*(p2->z - p1->z)	- (_hoops_IAPH->z - p1->z)*(p2->y - p1->y) == 0.0f && 
				(_hoops_IAPH->z - p1->z)*(p2->x - p1->x)	- (_hoops_IAPH->x - p1->x)*(p2->z - p1->z) == 0.0f &&
				(_hoops_IAPH->x - p1->x)*(p2->y - p1->y) - (_hoops_IAPH->y - p1->y)*(p2->x - p1->x) == 0.0f) {
				HE_ERROR (HEC_COMPUTE, HES_INVALID_COUNT, "Unable to create initial tetrahedron");
				return;
			}

			if (_hoops_IAPH == _hoops_CCGPA)
				_hoops_CCGPA = _hoops_CCGPA->next;
			if (_hoops_IAPH->prev != null)
				_hoops_IAPH->prev->next = _hoops_IAPH->next;
			if (_hoops_IAPH->next != null)
				_hoops_IAPH->next->prev = _hoops_IAPH->prev;
			_hoops_IAPH->next = _hoops_IAPH->prev = null;

			ALLOC (_hoops_HSGPA, _hoops_RRGPA);
			_hoops_HSGPA->next = _hoops_HSGPA->prev = null;
			faces = _hoops_HSGPA;

			ALLOC (_hoops_HSGPA->vertices, _hoops_GRGPA);
			_hoops_SSGPA = _hoops_HSGPA->vertices;
			_hoops_SSGPA->vertex = p1;
			ALLOC (_hoops_SSGPA->next, _hoops_GRGPA);
			_hoops_SSGPA = _hoops_SSGPA->next;
			_hoops_SSGPA->vertex = p2;
			ALLOC (_hoops_SSGPA->next, _hoops_GRGPA);
			_hoops_SSGPA = _hoops_SSGPA->next;
			_hoops_SSGPA->vertex = _hoops_IAPH;
			_hoops_SSGPA->next = null;

			_hoops_GAGPA (_hoops_HSGPA);


			/* _hoops_SCHCR _hoops_PPSR (_hoops_GRAA-_hoops_HPSS) */
			_hoops_SRRPA = &vertices[first_four[3]];
			if (Abs (_hoops_HSGPA->plane.a*_hoops_SRRPA->x + _hoops_HSGPA->plane.b*_hoops_SRRPA->y + _hoops_HSGPA->plane.c*_hoops_SRRPA->z + _hoops_HSGPA->plane.d) < _hoops_IRGPA) {
				/* _hoops_HPGR _hoops_CHGC _hoops_SR _hoops_GGHP _hoops_IRS _hoops_SCPH */
				list[0] = 3;
				list[1] = p1->index;
				list[2] = p2->index;
				list[3] = _hoops_IAPH->index;
				*_hoops_GGCIR = 4;

				goto _hoops_HPAGR;
			}

			if (_hoops_SRRPA == _hoops_CCGPA)
				_hoops_CCGPA = _hoops_CCGPA->next;
			if (_hoops_SRRPA->prev != null)
				_hoops_SRRPA->prev->next = _hoops_SRRPA->next;
			if (_hoops_SRRPA->next != null)
				_hoops_SRRPA->next->prev = _hoops_SRRPA->prev;
			_hoops_SRRPA->next = _hoops_SRRPA->prev = null;

			if (faces->plane.a*_hoops_SRRPA->x + faces->plane.b*_hoops_SRRPA->y +
				faces->plane.c*_hoops_SRRPA->z + faces->plane.d > 0.0) {
				/* _hoops_PIIA _hoops_SRS _hoops_IPPA */
				faces->plane.a = -faces->plane.a;
				faces->plane.b = -faces->plane.b;
				faces->plane.c = -faces->plane.c;
				faces->plane.d = -faces->plane.d;

				_hoops_SSGPA = faces->vertices->next;
				faces->vertices->next = _hoops_SSGPA->next;
				_hoops_SSGPA->next = faces->vertices;
				faces->vertices = _hoops_SSGPA;
				_hoops_RSGPA = p1;
				p1 = p2;
				p2 = _hoops_RSGPA;
			}

			ALLOC (_hoops_CSGPA, _hoops_ARGPA);
			_hoops_CSGPA->next = open;
			open = _hoops_CSGPA;
			_hoops_CSGPA->start = p2;
			_hoops_CSGPA->end = p1;

			ALLOC (_hoops_CSGPA, _hoops_ARGPA);
			_hoops_CSGPA->next = open;
			open = _hoops_CSGPA;
			_hoops_CSGPA->start = _hoops_IAPH;
			_hoops_CSGPA->end = p2;

			ALLOC (_hoops_CSGPA, _hoops_ARGPA);
			_hoops_CSGPA->next = open;
			open = _hoops_CSGPA;
			_hoops_CSGPA->start = p1;
			_hoops_CSGPA->end = _hoops_IAPH;

			while (open) {
				ALLOC (_hoops_HSGPA, _hoops_RRGPA);
				_hoops_HSGPA->prev = null;
				_hoops_HSGPA->next = faces;
				faces->prev = _hoops_HSGPA;
				faces = _hoops_HSGPA;

				ALLOC (_hoops_HSGPA->vertices, _hoops_GRGPA);
				_hoops_SSGPA = _hoops_HSGPA->vertices;
				_hoops_SSGPA->vertex = open->start;
				ALLOC (_hoops_SSGPA->next, _hoops_GRGPA);
				_hoops_SSGPA = _hoops_SSGPA->next;
				_hoops_SSGPA->vertex = open->end;
				ALLOC (_hoops_SSGPA->next, _hoops_GRGPA);
				_hoops_SSGPA = _hoops_SSGPA->next;
				_hoops_SSGPA->vertex = _hoops_SRRPA;
				_hoops_SSGPA->next = null;

				_hoops_GAGPA (_hoops_HSGPA);

				_hoops_CSGPA = open;
				open = open->next;
				FREE (_hoops_CSGPA, _hoops_ARGPA);
			}

			/* _hoops_GGCR _hoops_HHRPA _hoops_GIHA _hoops_CAS _hoops_SSRR */

			bool	_hoops_IHRPA = false;

			// _hoops_IH _hoops_GRR _hoops_CHRPA _hoops_PPSR
			while ((_hoops_RSGPA = _hoops_CCGPA) != null) {
#if 0
				// _hoops_SHRPA _hoops_GIRPA _hoops_RIRPA _hoops_CCA _hoops_PPSR _hoops_AHCA _hoops_IS _hoops_SHH _hoops_RRAI
				// _hoops_IGIPR _hoops_SGS _hoops_RH _hoops_SCGR _hoops_CAGH _hoops_HRGR _hoops_PCCP _hoops_IRPR _hoops_HGHC _hoops_IS _hoops_AIRI
				{
				PUSHNAME(context);

					if ((_hoops_HSGPA = faces) != null) do {
						if ((_hoops_SSGPA = _hoops_HSGPA->vertices) != null) {
							i = 0;
							do i++;
							while ((_hoops_SSGPA = _hoops_SSGPA->next) != null);

							*list++ = i;								(*_hoops_GGCIR)++;
							_hoops_SSGPA = _hoops_HSGPA->vertices;
							do {
								*list++ = _hoops_SSGPA->vertex->index;			(*_hoops_GGCIR)++;
							} while ((_hoops_SSGPA = _hoops_SSGPA->next) != null);
						}
					} while ((_hoops_HSGPA = _hoops_HSGPA->next) != null);

					Key _hoops_AIRPA = HC_Open_Segment ("");
						HC_Insert_Shell (_hoops_ICGPA, points, *_hoops_GGCIR, _hoops_RGRPA);

						HC_Open_Segment ("");
							HC_Set_Color ("blue");
							HC_Set_Marker_Symbol ("()");
							HC_Set_Marker_Size (0.3);
							HC_Insert_Marker (_hoops_RSGPA->x, _hoops_RSGPA->y, _hoops_RSGPA->z);
						HC_Close_Segment();
					HC_Close_Segment();
					HC_Update_Display();
					HC_Delete_By_Key (_hoops_AIRPA);

					*_hoops_GGCIR = 0;
					list = _hoops_RGRPA;

				POPNAME(context);
				}
#endif
				// _hoops_RAIPR
				if ((_hoops_CCGPA = _hoops_CCGPA->next) != 0) 
					_hoops_CCGPA->prev = null;
				_hoops_RSGPA->next = null;

				// _hoops_PPSI "_hoops_SIGC" _hoops_RSSI _hoops_GPP _hoops_IRS _hoops_GIAH _hoops_HIGR
				_hoops_PSGPA = faces;
				while ((_hoops_HSGPA = _hoops_PSGPA) != null) {
					_hoops_PSGPA = _hoops_PSGPA->next;
					if (_hoops_HSGPA->plane.a*_hoops_RSGPA->x + _hoops_HSGPA->plane.b*_hoops_RSGPA->y +
						_hoops_HSGPA->plane.c*_hoops_RSGPA->z + _hoops_HSGPA->plane.d > _hoops_IRGPA) {

						if (_hoops_HSGPA->prev)
							_hoops_HSGPA->prev->next = _hoops_HSGPA->next;
						if (_hoops_HSGPA->next) 
							_hoops_HSGPA->next->prev = _hoops_HSGPA->prev;
						if (faces == _hoops_HSGPA) 
							faces = _hoops_HSGPA->next;

						if ((_hoops_HSGPA->next = _hoops_GSGPA) != null)
							_hoops_GSGPA->prev = _hoops_HSGPA;
						_hoops_HSGPA->prev = null;
						_hoops_GSGPA = _hoops_HSGPA;
					}
				}

				if ((_hoops_HSGPA = _hoops_GSGPA) != null) {
					int		_hoops_PIRPA = 0, _hoops_HIRPA = 0, _hoops_IIRPA = 0, shared = 0;

					// _hoops_RARIR _hoops_IPS _hoops_IIGR _hoops_GPHA _hoops_IGPI
					do {
						_hoops_SSGPA = _hoops_HSGPA->vertices;
						do {
							_hoops_SSGPA->vertex->_hoops_SGGPA = _hoops_SSGPA->vertex->_hoops_HIHI;
						} while ((_hoops_SSGPA = _hoops_SSGPA->next) != null);
					} while ((_hoops_HSGPA = _hoops_HSGPA->next) != null);


					// _hoops_HSPAR _hoops_RSSI, _hoops_CAHP _hoops_SPPR, _hoops_AGPI _hoops_IPS _hoops_IIGR _hoops_GPHA _hoops_SGSS
					_hoops_HSGPA = _hoops_GSGPA;
					do {
						_hoops_SSGPA = _hoops_HSGPA->vertices;
						while (_hoops_SSGPA) {
							if (--_hoops_SSGPA->vertex->_hoops_SGGPA == 0)	// _hoops_GRS _hoops_SHH _hoops_CIRPA _hoops_RPP _hoops_CPS _hoops_APSH _hoops_IHRI
								++_hoops_PIRPA;

							++_hoops_IIRPA;

							ALLOC (_hoops_CSGPA, _hoops_ARGPA);
							_hoops_CSGPA->next = open;
							open = _hoops_CSGPA;
							_hoops_CSGPA->start = _hoops_SSGPA->vertex;
							if ((_hoops_SSGPA = _hoops_SSGPA->next) != 0) 
								_hoops_CSGPA->end = _hoops_SSGPA->vertex;
							else				
								_hoops_CSGPA->end = _hoops_HSGPA->vertices->vertex;
						}

						++_hoops_HIRPA;							// _hoops_RPP...
					} while ((_hoops_HSGPA = _hoops_HSGPA->next) != null);

					// _hoops_HPGGR _hoops_GII _hoops_SSRS _hoops_SPPR
					for (_hoops_ISGPA = open; _hoops_ISGPA; _hoops_ISGPA = _hoops_ISGPA->next) {
						for (_hoops_CSGPA = _hoops_ISGPA->next; _hoops_CSGPA;) {
							if (_hoops_ISGPA->start != null &&
								((_hoops_ISGPA->start == _hoops_CSGPA->end &&
								  _hoops_ISGPA->end == _hoops_CSGPA->start)  ||
								 (_hoops_ISGPA->start == _hoops_CSGPA->start &&
								  _hoops_ISGPA->end == _hoops_CSGPA->end))) {
								++shared;
								_hoops_IIRPA -= 2;
								/* _hoops_SIRPA */
								_hoops_ISGPA->start = _hoops_ISGPA->end = null;
								_hoops_CSGPA->start = _hoops_CSGPA->end = null;
								_hoops_CSGPA = null;
							}
							else
								_hoops_CSGPA = _hoops_CSGPA->next;
						}
					}

					if (_hoops_IIRPA == _hoops_HIRPA + 2 - 2 * _hoops_PIRPA) {
						// _hoops_CPSA _hoops_HASIR _hoops_RSSI & _hoops_CIRPA _hoops_GIHA
						while ((_hoops_HSGPA = _hoops_GSGPA) != null) {
							if ((_hoops_GSGPA = _hoops_HSGPA->next) != null)
								_hoops_GSGPA->prev = null;

							_hoops_SSGPA = _hoops_HSGPA->vertices;
							while ((_hoops_SSGPA = _hoops_HSGPA->vertices) != 0) {
								_hoops_ASGPA = _hoops_SSGPA->vertex;

								if (_hoops_ASGPA->_hoops_SGGPA == 0) {	// _hoops_HA _hoops_CIRPA
									if (_hoops_ASGPA == _hoops_CCGPA)	
										if ((_hoops_CCGPA = _hoops_CCGPA->next) != 0) 
											_hoops_CCGPA->prev = null;
										if (_hoops_ASGPA->prev)  
											_hoops_ASGPA->prev->next = _hoops_ASGPA->next;
										if (_hoops_ASGPA->next)  
											_hoops_ASGPA->next->prev = _hoops_ASGPA->prev;
								}
								else
									_hoops_ASGPA->_hoops_HIHI = _hoops_ASGPA->_hoops_SGGPA;

								_hoops_HSGPA->vertices = _hoops_SSGPA->next;
								FREE (_hoops_SSGPA, _hoops_GRGPA);
							}

							FREE (_hoops_HSGPA, _hoops_RRGPA);
						}

						// _hoops_CAHP _hoops_CCAH _hoops_RSSI _hoops_HII _hoops_SPPR
						while ((_hoops_CSGPA = open) != null) {
							open = _hoops_CSGPA->next;

							if (_hoops_CSGPA->start) {		// _hoops_HGGC _hoops_APIP
								ALLOC (_hoops_HSGPA, _hoops_RRGPA);
								_hoops_HSGPA->prev = null;
								_hoops_HSGPA->next = faces;
								faces->prev = _hoops_HSGPA;
								faces = _hoops_HSGPA;

								ALLOC (_hoops_HSGPA->vertices, _hoops_GRGPA);
								_hoops_SSGPA = _hoops_HSGPA->vertices;
								_hoops_SSGPA->vertex = _hoops_CSGPA->start;
								ALLOC (_hoops_SSGPA->next, _hoops_GRGPA);
								_hoops_SSGPA = _hoops_SSGPA->next;
								_hoops_SSGPA->vertex = _hoops_CSGPA->end;
								ALLOC (_hoops_SSGPA->next, _hoops_GRGPA);
								_hoops_SSGPA = _hoops_SSGPA->next;
								_hoops_SSGPA->vertex = _hoops_RSGPA;
								_hoops_SSGPA->next = null;

								_hoops_GAGPA (_hoops_HSGPA);
							}

							FREE (_hoops_CSGPA, _hoops_ARGPA);
						}

						_hoops_IHRPA = true;
					}
					else {
						// _hoops_PHIH _hoops_RSSI
						_hoops_HSGPA = _hoops_GSGPA;
						while (_hoops_HSGPA->next != null)
							_hoops_HSGPA = _hoops_HSGPA->next;
						_hoops_HSGPA->next = faces;
						faces->prev = _hoops_HSGPA;
						faces = _hoops_GSGPA;
						_hoops_GSGPA = null;

						// _hoops_CASI _hoops_SPPR
						while ((_hoops_CSGPA = open) != null) {
							open = _hoops_CSGPA->next;

							FREE (_hoops_CSGPA, _hoops_ARGPA);
						}
						// _hoops_IHIS _hoops_GPHA _hoops_IS _hoops_AHCI _hoops_HIGR
						if ((_hoops_RSGPA->next = _hoops_SCGPA) != null)
							_hoops_SCGPA->prev = _hoops_RSGPA;
						_hoops_SCGPA = _hoops_RSGPA;
					}
				}

				// _hoops_RPP _hoops_CHRPA _hoops_RHPA _hoops_PPR _hoops_AHCI _hoops_GIHA _hoops_PPR _hoops_PGHC _hoops_HAPR _hoops_IIAC _hoops_GCRPA, _hoops_RCRPA
				if (_hoops_CCGPA == null && _hoops_SCGPA != null) {
					if (_hoops_IHRPA) {
						_hoops_CCGPA = _hoops_SCGPA;
						_hoops_SCGPA = null;
						_hoops_IHRPA = false;
					}
					else {
						// _hoops_ACRPA
						break;
					}
				}
			}



			/********************* (_hoops_CAHP _hoops_IGHC _hoops_HIGR) ****************/

			if ((_hoops_HSGPA = faces) != null) do {
				if ((_hoops_SSGPA = _hoops_HSGPA->vertices) != null) {
					i = 0;
					do i++;
					while ((_hoops_SSGPA = _hoops_SSGPA->next) != null);

					*list++ = i;								(*_hoops_GGCIR)++;
					_hoops_SSGPA = _hoops_HSGPA->vertices;
					do {
						*list++ = _hoops_SSGPA->vertex->index;			(*_hoops_GGCIR)++;
					} while ((_hoops_SSGPA = _hoops_SSGPA->next) != null);
				}
			} while ((_hoops_HSGPA = _hoops_HSGPA->next) != null);


			if ((_hoops_HSGPA = faces) != null) {
				_hoops_GGRPA = *_hoops_GGCIR / 4;
				ALLOC_ARRAY_CACHED(_hoops_PRHH, _hoops_GGRPA, Vector);
				i = 0;

				do {
					_hoops_PRHH[i].x = _hoops_HSGPA->plane.a;
					_hoops_PRHH[i].y = _hoops_HSGPA->plane.b;
					_hoops_PRHH[i].z = _hoops_HSGPA->plane.c;
					i++;
				} while ((_hoops_HSGPA = _hoops_HSGPA->next) != null);
			}

#if 0
			// _hoops_SHRPA _hoops_RIRPA _hoops_RAS _hoops_CIGS _hoops_PHSPR (_hoops_HIPH _hoops_RGAR)
			// _hoops_IGIPR _hoops_SGS _hoops_RH _hoops_SCGR _hoops_CAGH _hoops_HRGR _hoops_PCCP _hoops_IRPR _hoops_HGHC _hoops_IS _hoops_AIRI
			{
			PUSHNAME(context);
				Key _hoops_AIRPA = HC_Open_Segment ("");
					HC_Insert_Shell (_hoops_ICGPA, points, *_hoops_GGCIR, _hoops_RGRPA);
				HC_Close_Segment();
				HC_Update_Display();
				HC_Delete_By_Key (_hoops_AIRPA);
			POPNAME(context);
			}
#endif


			/********************** _hoops_SSRR _hoops_IGRHR ********************/

			/* [_hoops_HASC _hoops_RSSI _hoops_PGAP _hoops_CHR _hoops_SCCPR & _hoops_IRPAA] */
			{
				int		_hoops_SPHA;
				int		_hoops_PCRPA = *_hoops_GGCIR / 4;
				int *	_hoops_HCRPA;		/* -1 _hoops_AGSR _hoops_GA'_hoops_RA _hoops_RRP _hoops_IS _hoops_HASC, _hoops_IAII _hoops_PHI _hoops_HRGR _hoops_HSP# _hoops_SCH _hoops_IRHS _hoops_IS _hoops_HASC _hoops_CCA */

				_hoops_RHHPR *_hoops_GRCPR, **_hoops_HHHPR;
				_hoops_CGCPR *_hoops_SGCPR;

				_hoops_CAGPA(_hoops_ICGPA, *_hoops_GGCIR, _hoops_RGRPA, &_hoops_SPHA, &_hoops_GRCPR, &_hoops_HHHPR, &_hoops_SGCPR);
				FREE_ARRAY (_hoops_HHHPR, _hoops_ICGPA + 1, _hoops_AAGPA *);
				FREE_ARRAY (_hoops_GRCPR, _hoops_SPHA, _hoops_RHHPR);
				ALLOC_ARRAY_CACHED(_hoops_HCRPA, _hoops_PCRPA, int);
				SET_MEMORY(_hoops_HCRPA, _hoops_PCRPA * sizeof(int), -1);

				/* _hoops_HSRR _hoops_GRR _hoops_HAS, _hoops_SR _hoops_PAH _hoops_IHSH _hoops_HPGR _hoops_RH _hoops_RSHCR _hoops_ISHA _hoops_GGR _hoops_CHCPR _hoops_IS _hoops_ICRPA
				 * _hoops_PGAP _hoops_PGCR _hoops_RSSI _hoops_SCH _hoops_CCRPA _hoops_IS, _hoops_PPR _hoops_CACH _hoops_RPP _hoops_RH _hoops_PGCR _hoops_RSSI _hoops_CHR _hoops_IRPAA. _hoops_CGP _hoops_RH
				 * _hoops_PGCR _hoops_RSSI _hoops_CHR _hoops_IRPAA, _hoops_PSCR _hoops_SR _hoops_HHGC _hoops_IS _hoops_HASIR _hoops_RGR _hoops_ISHA _hoops_HII _hoops_RH _hoops_HACH _hoops_SCRPA.
				 */
				for (i = 0; i < _hoops_SPHA; i++) {
					int			_hoops_AIIPR = _hoops_SGCPR[i]._hoops_AIIPR;
					int			_hoops_HIIPR = _hoops_SGCPR[i]._hoops_HIIPR;

					if (_hoops_AIIPR == -2 || _hoops_HIIPR == -2) {}
					else if (_hoops_PRHH[_hoops_AIIPR].x * _hoops_PRHH[_hoops_HIIPR].x +
							 _hoops_PRHH[_hoops_AIIPR].y * _hoops_PRHH[_hoops_HIIPR].y +
							 _hoops_PRHH[_hoops_AIIPR].z * _hoops_PRHH[_hoops_HIIPR].z  > _hoops_CRGPA) {
						if (_hoops_HCRPA[_hoops_AIIPR] != -1) {
							if (_hoops_HCRPA[_hoops_HIIPR] != -1) {
								// _hoops_HPHRA _hoops_PGCR _hoops_GSRPA _hoops_CGH _hoops_SHH _hoops_PICAA, _hoops_HIH _hoops_RH _hoops_RSSI _hoops_GHCA _hoops_AIAH _hoops_SHH _hoops_GGR _hoops_RH _hoops_PSHR _hoops_RSRPA
								int		test = _hoops_HCRPA[_hoops_AIIPR];

								while (test != _hoops_AIIPR && test != _hoops_HIIPR)
									test = _hoops_HCRPA[test];

								if (test == _hoops_AIIPR)	// _hoops_SARS'_hoops_RA _hoops_CACH _hoops_ASRPA _hoops_GGR _hoops_RSRPA _hoops_IHIA _hoops_CCA _hoops_PSRPA
									Swap (_hoops_HCRPA[_hoops_AIIPR], _hoops_HCRPA[_hoops_HIIPR]);
							}
							else {
								// _hoops_HSRPA _hoops_ASRPA _hoops_CRGR _hoops_RSRPA _hoops_IIGR _hoops_PSRPA
								_hoops_HCRPA[_hoops_HIIPR] = _hoops_HCRPA[_hoops_AIIPR];
								_hoops_HCRPA[_hoops_AIIPR] = _hoops_HIIPR;
							}
						}
						else {
							if (_hoops_HCRPA[_hoops_HIIPR] != -1) {
								// _hoops_HSRPA _hoops_PSRPA _hoops_CRGR _hoops_RSRPA _hoops_IIGR _hoops_ASRPA
								_hoops_HCRPA[_hoops_AIIPR] = _hoops_HCRPA[_hoops_HIIPR];
								_hoops_HCRPA[_hoops_HIIPR] = _hoops_AIIPR;
							}
							else {
								// _hoops_CCAH _hoops_RSRPA
								_hoops_HCRPA[_hoops_AIIPR] = _hoops_HIIPR;
								_hoops_HCRPA[_hoops_HIIPR] = _hoops_AIIPR;
							}
						}
					}
				}


				/* _hoops_AGGA _hoops_SR'_hoops_RISP _hoops_PRHI _hoops_RH "_hoops_RSSI-_hoops_IS-_hoops_HASC" _hoops_HIGR, _hoops_SR _hoops_RPGH _hoops_HPP _hoops_IARPA _hoops_RH _hoops_SCRPA _hoops_CCA _hoops_RSSI _hoops_SR _hoops_GA'_hoops_RA _hoops_HHGC _hoops_IS _hoops_HASC */
				*_hoops_GGCIR = 0;
				for (i = 0; i < _hoops_PCRPA; i++) {
					if (_hoops_HCRPA[i] == -1) {
						_hoops_HCGPA[*_hoops_GGCIR] = 3;
						_hoops_HCGPA[*_hoops_GGCIR + 1] = _hoops_RGRPA[i*4 + 1];
						_hoops_HCGPA[*_hoops_GGCIR + 2] = _hoops_RGRPA[i*4 + 2];
						_hoops_HCGPA[*_hoops_GGCIR + 3] = _hoops_RGRPA[i*4 + 3];
						*_hoops_GGCIR += 4;
					}
				}

				/* _hoops_ISRPA _hoops_PPR _hoops_GGCR _hoops_RH _hoops_RSSI _hoops_SGS _hoops_SR _hoops_HHGC _hoops_IS _hoops_HASC */
				for (i = 0; i < _hoops_PCRPA; i++) {
					if (_hoops_HCRPA[i] != -1) {
						/* _hoops_SRS, _hoops_ARPR _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_HCR _hoops_RH _hoops_RSSA _hoops_IH _hoops_RH _hoops_IAGHR _hoops_RSSI */
						int *		_hoops_CSRPA;			/* _hoops_RGR _hoops_CRPR _hoops_PAHGA _hoops_RH _hoops_PSPI _hoops_IIGR _hoops_HCR _hoops_RH _hoops_RH _hoops_RSSA _hoops_IS _hoops_HASC */
						int *		_hoops_SSRPA;	/* _hoops_RGR _hoops_CRPR _hoops_PAHGA _hoops_RH (_hoops_GSHHR) _hoops_PSPI _hoops_IIGR _hoops_HCR _hoops_RH _hoops_RH _hoops_RSSA _hoops_IS _hoops_HASC */
						_hoops_CGGPA *	_hoops_GGAPA;			/* _hoops_RGR _hoops_GRS _hoops_SHH _hoops_RH _hoops_CRPR _hoops_IIGR _hoops_RSSA _hoops_SR _hoops_RIH _hoops_IS "_hoops_RGAPA" */
						_hoops_CGGPA *	ptr;				/* _hoops_SGH _hoops_RGR _hoops_IS _hoops_PSRC _hoops_RHIR _hoops_AGAPA */
						int *		_hoops_PGAPA;		/* _hoops_SCRPA _hoops_IIGR _hoops_SGCS _hoops_GCGPA _hoops_IH _hoops_AGCR _hoops_HPSS _hoops_RSSA */
						int 		face = i;
						int 		n = 0;
						int 		k = 0;


						ZALLOC_ARRAY_CACHED(_hoops_CSRPA, _hoops_PCRPA*3, int);
						ALLOC_ARRAY_CACHED(_hoops_SSRPA, count, int);
						ALLOC_ARRAY_CACHED(_hoops_GGAPA, count, _hoops_CGGPA);
						ALLOC_ARRAY_CACHED(_hoops_PGAPA, 8*count, int);

						n = 0;
						while (_hoops_HCRPA[face] != -1) {
							int prev = face;
							_hoops_CSRPA[n++] = _hoops_RGRPA[face*4 + 1];
							_hoops_CSRPA[n++] = _hoops_RGRPA[face*4 + 2];
							_hoops_CSRPA[n++] = _hoops_RGRPA[face*4 + 3];
							face = _hoops_HCRPA[face];
							_hoops_HCRPA[prev] = -1;
						}

#if 0
						// _hoops_SHRPA _hoops_GIRPA _hoops_RIRPA _hoops_CCA _hoops_RSSA _hoops_IIGR _hoops_RSSI _hoops_AHCA _hoops_IS _hoops_SHH _hoops_RPHGA
						// _hoops_IGIPR _hoops_SGS _hoops_RH _hoops_SCGR _hoops_CAGH _hoops_HRGR _hoops_PCCP _hoops_IRPR _hoops_HGHC _hoops_IS _hoops_AIRI
						{
						PUSHNAME(context);
							Key _hoops_AIRPA = HC_Open_Segment ("");
								HC_Insert_Shell (_hoops_ICGPA, points, *_hoops_GGCIR, _hoops_HCGPA);

								HC_Open_Segment ("");
									HC_Set_Color ("blue");
									HC_Set_Marker_Symbol ("()");
									HC_Set_Marker_Size (0.3);
									for (int ii=0; ii<n; ++ii)
										HC_Insert_Marker (points[_hoops_CSRPA[ii]].x, points[_hoops_CSRPA[ii]].y, points[_hoops_CSRPA[ii]].z);
								HC_Close_Segment();
							HC_Close_Segment();
							HC_Update_Display();
							HC_Delete_By_Key (_hoops_AIRPA);
						POPNAME(context);
						}
#endif

						
						_hoops_AGRPA._hoops_PRGPA = &_hoops_CSRPA[0];
						quick_sort(_hoops_AGRPA,0,n-1);

						/* _hoops_HA _hoops_IPS _hoops_RH _hoops_RSSA _hoops_CRGR _hoops_RH _hoops_GSHHR _hoops_HIGR, _hoops_HGAPA _hoops_GII _hoops_IGAPA */
						_hoops_SSRPA[0] = _hoops_CSRPA[0];
						face = 1;
						for (k = 1; k < n; k++)
							if (_hoops_SSRPA[face-1] != _hoops_CSRPA[k])
								_hoops_SSRPA[face++] = _hoops_CSRPA[k];
						n = face;

						face = 0;
						ptr = _hoops_GGAPA;
						while (face < n) {
							ptr->next = ptr + 1;
							ptr->prev = ptr - 1;
							ptr->_hoops_HIHI = 0;
							ptr->index = _hoops_SSRPA[face];
							ptr->x = points[_hoops_SSRPA[face]].x;
							ptr->y = points[_hoops_SSRPA[face]].y;
							ptr->z = points[_hoops_SSRPA[face]].z;

							ptr = ptr->next;
							face++;
						}
						_hoops_GGAPA[0].prev = null;
						_hoops_GGAPA[face-1].next = null;

						/* _hoops_HPGR _hoops_RGR _hoops_PPSR, _hoops_HSP _hoops_HRGR _hoops_RH _hoops_SPCC _hoops_IIGR _hoops_AGAPA, _hoops_PPR _hoops_ARGI _hoops_GRS _hoops_SHH _hoops_CGAPA _hoops_GAR _hoops_RH _hoops_ARGR _hoops_SGAPA */
						_hoops_IHGPA(_hoops_GGAPA, face, points, &_hoops_PRHH[i], &k, _hoops_PGAPA);

						/* _hoops_HA, _hoops_SR _hoops_SAHR _hoops_CIGAA _hoops_RH _hoops_SCRPA _hoops_IS _hoops_RH _hoops_GHPP */
						for (n = 0; n < k; n++) {
							_hoops_HCGPA[*_hoops_GGCIR] = _hoops_PGAPA[n];
							(*_hoops_GGCIR)++;
						}
						
						FREE_ARRAY(_hoops_PGAPA, 8*count, int);
						FREE_ARRAY(_hoops_CSRPA, _hoops_PCRPA*3, int);
						FREE_ARRAY(_hoops_SSRPA, count, int);
						FREE_ARRAY(_hoops_GGAPA, count, _hoops_CGGPA);
					}

				}

				FREE_ARRAY(_hoops_HCRPA, _hoops_PCRPA, int);
				FREE_ARRAY(_hoops_SGCPR, _hoops_SPHA, _hoops_CGCPR);
			}
		}
	}

_hoops_HPAGR:;

	while ((_hoops_HSGPA = faces) != null) {
		while ((_hoops_SSGPA = _hoops_HSGPA->vertices) != null) {
			_hoops_HSGPA->vertices = _hoops_SSGPA->next;
			FREE (_hoops_SSGPA, _hoops_GRGPA);
		}

		faces = _hoops_HSGPA->next;
		FREE (_hoops_HSGPA, _hoops_RRGPA);
	}

	_hoops_AGRPA.in_points = null;
	FREE_ARRAY (vertices, _hoops_ICGPA, _hoops_CGGPA);
	FREE_ARRAY (_hoops_RGRPA, 8*_hoops_ICGPA, int);
	if (_hoops_PRHH)
		FREE_ARRAY(_hoops_PRHH, _hoops_GGRPA, Vector);
#endif
}

////////////////////////////////////////////////////////////////////////////////

local void _hoops_GRAPA (
	_hoops_AIGPR *	_hoops_RIGC,
	Geometry alter *		geometry,
	_hoops_CRCP alter *			new_owner//,
	) {
	_hoops_CRCP alter *			_hoops_RRAPA = geometry->owner;
	_hoops_CRCP alter *			_hoops_ARAPA = new_owner->owner;

	if (_hoops_RRAPA->_hoops_GACP != null)
		HI_Table_Remove_Geometry (geometry);
	_hoops_CIGPR (_hoops_RIGC,geometry);

	HI_Insert_Geometry (_hoops_RIGC, (_hoops_HPAH *)new_owner, geometry,
						!BIT (geometry->_hoops_RRHH, _hoops_RSPCR), 0, false);
	new_owner->owner = _hoops_ARAPA;
}



#define _hoops_PRAPA	(_hoops_HRAPA|_hoops_IACHR|_hoops_HAGI)

local void _hoops_IRAPA (
	Shell alter *			s) {
	Local_Face_Attributes alter *	_hoops_CPRI = (Local_Face_Attributes alter *)&s->local_face_attributes;
	int								_hoops_CRAPA = s->face_count;

	if (BIT (s->polyhedron_flags, _hoops_CGRHR))
		_hoops_CPRI->_hoops_SGRHR &= ~_hoops_PRAPA;
	for (int i = 0; i < _hoops_CRAPA; i++)
		_hoops_CPRI->flags[i] &= ~_hoops_PRAPA;

	if (_hoops_CPRI->colors != null) {
		_hoops_CPRI->_hoops_HSRRA = 0;
		FREE_ARRAY (_hoops_CPRI->colors, _hoops_CRAPA, RGB);
		_hoops_CPRI->colors = null;
	}
	if (_hoops_CPRI->findices != null) {
		_hoops_CPRI->_hoops_PSRRA = 0;
		FREE_ARRAY (_hoops_CPRI->findices, _hoops_CRAPA, float);
		_hoops_CPRI->findices = null;
	}
	if (_hoops_CPRI->_hoops_AHHIR != null) {
		_hoops_CPRI->_hoops_SRAPA = 0;
		FREE_ARRAY (_hoops_CPRI->_hoops_AHHIR, _hoops_CRAPA, unsigned char);
		_hoops_CPRI->_hoops_AHHIR = null;
	}
}



local bool _hoops_GAAPA (
	Geometry alter *			g) {
	Polyhedron const *			p = (Polyhedron const *)g;

	if (p->local_face_attributes._hoops_HSRRA > 0 ||
		p->local_face_attributes._hoops_PSRRA > 0 ||
		p->local_face_attributes._hoops_SRAPA > 0)
		return true;
	
	return false;
}

local bool _hoops_RAAPA (
	Geometry alter *			g) {
	Attribute const *			a;

	if ((a = g->_hoops_IPPGR) != null) do {
		if (a->type != HK_USER_OPTIONS && a->type != HK_USER_VALUE)
			return true;
	} while ((a = a->next) != null);

	if (g->type == _hoops_SCIP || g->type == _hoops_GSIP) {
		if (_hoops_GAAPA (g))
			return true;

		// _hoops_SPHR _hoops_GAAP _hoops_ISHA/_hoops_GPHA _hoops_AIRC
	}

	return false;
}



local bool _hoops_AAAPA (
	Local_Face_Attributes const *	_hoops_CPRI,
	int								_hoops_AIIPR,
	int								_hoops_HIIPR) {
	_hoops_GIIPR				_hoops_PAAPA = *_hoops_CPRI->_hoops_CHHPR (_hoops_AIIPR);
	_hoops_GIIPR				_hoops_IRIA = *_hoops_CPRI->_hoops_CHHPR (_hoops_HIIPR);

	if ((_hoops_PAAPA & _hoops_PRAPA) != (_hoops_IRIA & _hoops_PRAPA))
		return false;

	if (BIT (_hoops_PAAPA, LFA_EXPLICIT_COLOR_BY_VALUE)) {
		if (_hoops_CPRI->colors[_hoops_AIIPR] != _hoops_CPRI->colors[_hoops_HIIPR])
			return false;
	}
	if (BIT (_hoops_PAAPA, LFA_EXPLICIT_COLOR_BY_FINDEX)) {
		if (_hoops_CPRI->findices[_hoops_AIIPR] != _hoops_CPRI->findices[_hoops_HIIPR])
			return false;
	}
	if (BIT (_hoops_PAAPA, _hoops_HAGI)) {
		if (_hoops_CPRI->_hoops_AHHIR[_hoops_AIIPR] != _hoops_CPRI->_hoops_AHHIR[_hoops_HIIPR])
			return false;
	}

	return true;
}


local char const * face_patterns[]  = {"solid", "[]", "#", "<>", "=", "\\", "/", ":", "="};


local _hoops_SRHSR	_hoops_HAAPA = _hoops_GRRCR ("- faces -");
local _hoops_SRHSR	_hoops_IAAPA = _hoops_GRRCR ("- edges and vertices -");	// _hoops_CAAPA ("- _hoops_SPPR -");
local _hoops_SRHSR	_hoops_SAAPA = _hoops_GRRCR ("- vertices -");


GLOBAL_FUNCTION _hoops_CRCP * HI_Separate_Geometry_Attributes (
	_hoops_AIGPR *		_hoops_RIGC,
	Geometry alter *			g) 
{
	_hoops_ICIIR(_hoops_RIGC);

	_hoops_CRCP alter *	owner = g->owner;

	if (owner == null || owner->type != _hoops_IRCP)
		return null;

	if (_hoops_RAAPA (g)) {
		
		_hoops_CRCP alter *	top = HI_Create_One_Segment (_hoops_RIGC, null, &owner->_hoops_RGRPR, null, owner, true);

		// _hoops_GII _hoops_PRCHR _hoops_SGS _hoops_CHH _hoops_SGH _hoops_RGR _hoops_CPAP _hoops_RRP _hoops_IS _hoops_HHGP _hoops_PSAP _hoops_PCCP _hoops_GPAPA _hoops_IS _hoops_RH _hoops_CCAH _hoops_RGGAR _hoops_RIIA

		_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(owner);

		if (_hoops_APAPA != null) {

			_hoops_APAPA->ResetCursor();
			_hoops_PHIP *	_hoops_RRA;
			while((_hoops_RRA = _hoops_APAPA->PeekCursor()) != null) {

				_hoops_PGRPR *	include;

				ZALLOC (include, _hoops_PGRPR);
				include->_hoops_RRHH = _hoops_HPAPA;
				include->type = _hoops_AGRPR;
				include->_hoops_HIHI = 1;
				include->owner = _hoops_RRA->owner;
				include->key = _hoops_AIRIR (include);
				include->priority = HOOPS_WORLD->_hoops_IPAPA++;
				HI_Copy_Conditional (&_hoops_RRA->condition, &include->condition);

				_hoops_CPAPA (_hoops_RIGC, include, owner);

				include->_hoops_IGRPR = top;
				_hoops_PRRH (top);
				_hoops_SPAPA(_hoops_RIGC, include, top);

				_hoops_APAPA->AdvanceCursor();
			}
		}

		_hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Remove(g);

		if (_hoops_APAPA != null) {

			_hoops_PHIP *	_hoops_RRA;
			while((_hoops_RRA = _hoops_APAPA->RemoveFirst()) != null) {

				_hoops_PGRPR *	include;

				ZALLOC (include, _hoops_PGRPR);
				include->_hoops_RRHH = _hoops_HPAPA;
				include->type = _hoops_AGRPR;
				include->_hoops_HIHI = 1;
				include->owner = _hoops_RRA->owner;
				include->key = _hoops_AIRIR (include);
				include->priority = HOOPS_WORLD->_hoops_IPAPA++;
				HI_Copy_Conditional (&_hoops_RRA->condition, &include->condition);

				_hoops_CPAPA (_hoops_RIGC, include, owner);

				include->_hoops_IGRPR = top;
				_hoops_PRRH (top);
				_hoops_SPAPA(_hoops_RIGC, include, top);

				if (_hoops_RRA->_hoops_HHIP == 1) {
					// _hoops_APRI _hoops_RH _hoops_SHSC _hoops_CGRPR, _hoops_HIH _hoops_RAS _hoops_SR _hoops_IRHH _hoops_RH _hoops_GCIS (_hoops_RRP _hoops_IS _hoops_IPS _hoops_RAGPR)
					HI_Disentangle (_hoops_RIGC, (_hoops_HPAH *)_hoops_RRA);
					_hoops_CIGPR (_hoops_RIGC,_hoops_RRA);
					HI_Table_Remove_Geometry (_hoops_RRA);
					_hoops_HPRH (_hoops_RRA);
				}
				else {

					for (int i = 0; i < _hoops_RRA->_hoops_HHIP; i++) {
						if (_hoops_RRA->_hoops_IHIP[i] == (_hoops_SIHIR const *)g) {

							// _hoops_HASIR _hoops_SPR _hoops_CARRA _hoops_HII _hoops_RH _hoops_CRPR
							_hoops_SIHIR const * alter *	_hoops_GHAPA = _hoops_RRA->_hoops_IHIP;

							ALLOC_ARRAY (_hoops_RRA->_hoops_IHIP, _hoops_RRA->_hoops_HHIP-1, _hoops_SIHIR const *);
							if (i > 0)
								_hoops_AIGA (_hoops_GHAPA, i, _hoops_SIHIR const *, _hoops_RRA->_hoops_IHIP);
							if (i < _hoops_RRA->_hoops_HHIP-1)
								_hoops_AIGA (&_hoops_GHAPA[i+1], _hoops_RRA->_hoops_HHIP-1-i, _hoops_SIHIR const *, &_hoops_RRA->_hoops_IHIP[i]);
							FREE_ARRAY (_hoops_GHAPA, _hoops_RRA->_hoops_HHIP, _hoops_SIHIR const *);
							--_hoops_RRA->_hoops_HHIP;
						}
					}
				}
			}

			delete _hoops_APAPA;
		}

		_hoops_GRAPA (_hoops_RIGC, g, top);

		if (g->_hoops_IPPGR != null) {
			Attribute alter **	_hoops_ASRGR = &top->_hoops_IPPGR;
			Attribute alter *	a = g->_hoops_IPPGR;
			Attribute alter *	next;

			do {
				next = a->next;

				if (a->type != HK_USER_OPTIONS && a->type != HK_USER_VALUE) {
					_hoops_CIGPR (_hoops_RIGC,a);
					*_hoops_ASRGR = a;
					a->backlink = _hoops_ASRGR;
					_hoops_ASRGR = &a->next;
				}
			} while ((a = next) != null);

		}


		// _hoops_SCHS _hoops_PPR _hoops_CSHRR _hoops_GHCA _hoops_HGGC _hoops_HS _hoops_SASI _hoops_AIRC _hoops_IS _hoops_RHAPA _hoops_PPR _hoops_HHGP
		if ((g->type == _hoops_SCIP || g->type == _hoops_GSIP) && _hoops_RAAPA (g)) {
			Shell const *		s = (Shell const *)g;

			// _hoops_RGAR _hoops_HPPP _hoops_SCHS _hoops_CCA _hoops_HSP _hoops_CPCI _hoops_HII _hoops_ARI...
			if (g->type == _hoops_GSIP) {
				Key			_hoops_AHAPA;

				PUSHNAME(_hoops_RIGC);
					HC_Open_Segment_By_Key (top->key);
						_hoops_AHAPA = HC_Generate_Shell_From_Geometry (_hoops_AIRIR (g), "");
					HC_Close_Segment();
				POPNAME(_hoops_RIGC);

				s = (Shell const *)_hoops_RCSSR (_hoops_RIGC, _hoops_AHAPA);

				_hoops_CIGPR (_hoops_RIGC,g);
				HI_Table_Remove_Geometry (g);
				_hoops_HPRH (g);

				g = (Geometry *)s;
			}
			else if (s->face_list == null) {
				if (s->tristrips != null)
					HI_Face_List_From_Tristrips (_hoops_RIGC, (Shell *)s);
			}


			_hoops_CRCP alter *			faces;
			_hoops_CRCP alter *			_hoops_GRCPR;
			//_hoops_GSRRR _hoops_RAPC *			_hoops_GIHA;

			//_hoops_GIHA = _hoops_PHAPA (_hoops_HHAPA, _hoops_IRAP, &_hoops_IHAPA, &_hoops_SCIA->_hoops_CHAPA, _hoops_IRAP, _hoops_SCIA, _hoops_IHPR);
			//_hoops_SHAPA(_hoops_HHAPA);
			//	_hoops_GIAPA (_hoops_SPPR->_hoops_SIC);
			//		_hoops_RIAPA ("_hoops_PSP _hoops_RSSI, _hoops_PSP _hoops_SPPR");
			//	_hoops_AIAPA();
			//_hoops_PIAPA(_hoops_HHAPA);
			faces = HI_Create_One_Segment (_hoops_RIGC, (_hoops_HCRPR const *)&_hoops_HAAPA, &top->_hoops_RGRPR, null, top, true);
			PUSHNAME(_hoops_RIGC);
				HC_Open_Segment_By_Key (faces->key);
					HC_Set_Visibility ("no edges, no vertices");
				HC_Close_Segment();
			POPNAME(_hoops_RIGC);
			_hoops_GRCPR = HI_Create_One_Segment (_hoops_RIGC, (_hoops_HCRPR const *)&_hoops_IAAPA, &top->_hoops_RGRPR, null, top, true);
			PUSHNAME(_hoops_RIGC);
				HC_Open_Segment_By_Key (_hoops_GRCPR->key);
					HC_Set_Visibility ("no faces");
					//_hoops_RIAPA ("_hoops_PSP _hoops_RSSI, _hoops_PSP _hoops_GIHA");
				HC_Close_Segment();
			POPNAME(_hoops_RIGC);

			// _hoops_AA _hoops_SR _hoops_RRP _hoops_IS _hoops_HHGP _hoops_SPPR (_hoops_PAR _hoops_GIHA)?
			if (0) {
				// _hoops_IH _hoops_HA, _hoops_PSP, _hoops_PPR _hoops_SHSP _hoops_CAPR _hoops_GIRP
			}
			else {
				// _hoops_RRP _hoops_IRS _hoops_IPS _hoops_IIGR _hoops_RH _hoops_GIGR _hoops_IH _hoops_ASCA _hoops_SAHR _hoops_RH _hoops_SPPR (_hoops_PPR _hoops_GIHA)
				Shell alter *		_hoops_HIAPA = (Shell *)HI_Copy_Geometry (_hoops_RIGC, g);

				_hoops_IRAPA (_hoops_HIAPA);
				//_hoops_IIAPA (_hoops_CIAPA);

				HI_Insert_Geometry (_hoops_RIGC, (_hoops_HPAH *)_hoops_GRCPR, (Geometry *)_hoops_HIAPA, false, 0);
			}

			// _hoops_AA _hoops_SR _hoops_RRP _hoops_IS _hoops_HHGP _hoops_RSSI?
			if (s->face_list != null && _hoops_GAAPA (g)) {
				// _hoops_SIAPA _hoops_RSSI _hoops_CRGR _hoops_GIAH _hoops_SGHC _hoops_IIHA _hoops_GPP _hoops_AIRC

				bool alter *		_hoops_GCAPA;		// _hoops_IH _hoops_CGRSR _hoops_GCRPA
				int const **		_hoops_RCAPA;	// _hoops_HHCI _hoops_ACAPA _hoops_IS _hoops_GIGR _hoops_HIGR _hoops_PCAPA
				Point alter *		points;			// _hoops_AH _hoops_IH _hoops_HCAPA _hoops_ISPAA
				int alter *			face_list;		//	"
				int alter *			_hoops_ICAPA;	// _hoops_GIGR _hoops_IS _hoops_CCAH
				int alter *			face_mapping;	// _hoops_CCAH _hoops_IS _hoops_GIGR
				int					index;
				int const *			_hoops_PSRGA;

				ZALLOC_ARRAY (_hoops_GCAPA, s->face_count, bool);

				ZALLOC_ARRAY (points, s->point_count, Point);
				ZALLOC_ARRAY (face_list, s->face_list_length, int);

				ALLOC_ARRAY (_hoops_ICAPA, s->point_count, int);
				ALLOC_ARRAY (face_mapping, s->face_count, int);

				ZALLOC_ARRAY (_hoops_RCAPA, s->face_count+1, int const *);

				index = 0;
				_hoops_PSRGA = s->face_list;
				while (index < s->face_count) {
					_hoops_RCAPA[index++] = _hoops_PSRGA;
					_hoops_PSRGA += 1 + *_hoops_PSRGA;
					while (_hoops_PSRGA != s->face_list + s->face_list_length && *_hoops_PSRGA < 0)
						_hoops_PSRGA += 1 - *_hoops_PSRGA;
				}
				_hoops_RCAPA[index] = _hoops_PSRGA;	// _hoops_CGH _hoops_SHH _hoops_HPGR _hoops_RSGR

				// _hoops_IHSH _hoops_IH _hoops_IGRI _hoops_GGGRR _hoops_IS _hoops_HHGP _hoops_PSAP _hoops_GAR _hoops_GIAH _hoops_SCHS
				index = 0;
				while (index < s->face_count) {
					while (index < s->face_count && _hoops_GCAPA[index])
						++index;

					if (index < s->face_count) {
						Local_Face_Attributes const *	_hoops_CPRI = &s->local_face_attributes;
						_hoops_GIIPR				flags = *_hoops_CPRI->_hoops_CHHPR (index);
						_hoops_CRCP alter *					part;

						// _hoops_RGGAR _hoops_IH _hoops_SASI _hoops_IGRI _hoops_AARRA
						part = HI_Create_One_Segment (_hoops_RIGC, null, &faces->_hoops_RGRPR, null, faces, true);
						PUSHNAME(_hoops_RIGC);
							HC_Open_Segment_By_Key (part->key);
								if (BIT (flags, _hoops_IAGI))
									HC_Set_Visibility ("faces");
								else if (BIT (flags, _hoops_HSIPR))
									HC_Set_Visibility ("no faces");

								if (BIT (flags, LFA_EXPLICIT_COLOR_BY_VALUE)) {
									HC_Set_Color_By_Value ("faces", "rgb",	_hoops_CPRI->colors[index].red,
																			_hoops_CPRI->colors[index].green,
																			_hoops_CPRI->colors[index].blue);
								}
								else if (BIT (flags, LFA_EXPLICIT_COLOR_BY_FINDEX))
									HC_Set_Color_By_FIndex ("faces", _hoops_CPRI->findices[index]);

								if (BIT (flags, _hoops_HAGI))
									HC_Set_Face_Pattern (face_patterns[_hoops_CPRI->_hoops_AHHIR[index]]);
							HC_Close_Segment();
						POPNAME(_hoops_RIGC);

						// _hoops_PGGC _hoops_PIH _hoops_GPP _hoops_RSSI _hoops_SGS _hoops_SGH _hoops_RGR _hoops_IGRI _hoops_AARRA
						int								test = index;
						int								point_count = 0;
						int								face_count = 0;
						int								face_list_length = 0;

						SET_MEMORY (_hoops_ICAPA, s->point_count*sizeof(int), -1);
						SET_MEMORY (face_mapping, s->face_count*sizeof(int), -1);

						while (test < s->face_count) {
							if (_hoops_AAAPA (_hoops_CPRI, test, index)) {
								_hoops_GCAPA[test] = true;
								face_mapping[face_count++] = test;

								_hoops_PSRGA = _hoops_RCAPA[test];
								while (_hoops_PSRGA < _hoops_RCAPA[test+1]) {
									int			length = Abs (*_hoops_PSRGA);

									face_list[face_list_length++] = *_hoops_PSRGA++;

									while (length-- > 0) {
										int		_hoops_CCAPA = *_hoops_PSRGA++;

										if (_hoops_ICAPA[_hoops_CCAPA] < 0) {
											points[point_count] = s->points[_hoops_CCAPA];
											_hoops_ICAPA[_hoops_CCAPA] = point_count++;
										}
										face_list[face_list_length++] = _hoops_ICAPA[_hoops_CCAPA];
									}
								}
							}
							++test;
						}

						// _hoops_ARPR _hoops_IRS _hoops_CCAH _hoops_RRCPR _hoops_HII _hoops_RSSA & _hoops_SCAPA
						Shell alter *			_hoops_SPHPR;

						ZALLOC (_hoops_SPHPR, Shell);
						_hoops_SPHPR->type = _hoops_SCIP;
						_hoops_SPHPR->_hoops_CPGPR = _hoops_AHSGA;
						_hoops_SPHPR->point_count = point_count;
						_hoops_SPHPR->_hoops_SPHA = -1;
						_hoops_SPHPR->face_count = face_count;

						_hoops_SPHPR->_hoops_GSAPA = true;
						_hoops_SPHPR->face_list_length = face_list_length;

						ALLOC_ARRAY_ALIGNED (_hoops_SPHPR->points, point_count, Point, 16);
						_hoops_AIGA (points, point_count, Point, _hoops_SPHPR->points);

						_hoops_SPHPR->face_list = (int *)HI_Clone_Anything ((void *)face_list,
															face_list_length * (long)sizeof(int));

						_hoops_SPHPR = (Shell *) HI_Insert_Geometry (_hoops_RIGC, (_hoops_HPAH *)part, (Geometry *)_hoops_SPHPR, false, 0);

						// _hoops_ACRAA _hoops_PCHC _hoops_GPHA _hoops_AIRC _hoops_SGS _hoops_PAH _hoops_HAHA _hoops_HSP _hoops_ASCA
						if (s->local_vertex_attributes.normals == null ||
							!BIT (s->polyhedron_flags, PHF_VERTEX_NORMALS_VALID))
							HI_Assemble_3D_Tristrips ((Polyhedron *)s, false, true);

						if (s->local_vertex_attributes.normals != null ||
							s->local_vertex_attributes._hoops_RSAPA > 0) {
							Local_Vertex_Attributes const *		_hoops_SPRI = &s->local_vertex_attributes;

							PUSHNAME(_hoops_RIGC);
								HC_Open_Geometry (_hoops_SPHPR->key);
									for (int i = 0; i < s->point_count; i++) {
										if (_hoops_ICAPA[i] >= 0 &&
											(_hoops_SPRI->normals != null || BIT (*_hoops_SPRI->_hoops_CHHPR (i), _hoops_ASAPA))) {
											HC_Open_Vertex (_hoops_ICAPA[i]);
												if (BIT (*_hoops_SPRI->_hoops_CHHPR (i), _hoops_ASAPA))
													HC_Set_Parameter (_hoops_SPRI->param_width, &_hoops_SPRI->params[i * _hoops_SPRI->param_width]);
												if (_hoops_SPRI->normals != null)
													HC_Set_Normal (_hoops_SPRI->normals[i].x, _hoops_SPRI->normals[i].y, _hoops_SPRI->normals[i].z);
												else {
													_hoops_CGGPA		_hoops_PSAPA;

													HC_Open_Geometry (_hoops_SPHPR->key);
														HC_Open_Vertex (i);
															HC_Show_Net_Normal (&_hoops_PSAPA.x, &_hoops_PSAPA.y, &_hoops_PSAPA.z);
														HC_Close_Vertex ();
													HC_Close_Geometry ();

													HC_Set_Normal (_hoops_PSAPA.x, _hoops_PSAPA.y, _hoops_PSAPA.z);
												}
											HC_Close_Vertex ();
										}
									}
								HC_Close_Geometry ();
							POPNAME(_hoops_RIGC);
						}

						// _hoops_ACRAA _hoops_GII _hoops_HHHA _hoops_HSP _hoops_ASGA
						if (_hoops_CPRI->explicit_normal_count > 0) {
							PUSHNAME(_hoops_RIGC);
								HC_Open_Segment_By_Key (s->key);
									for (int i = 0; i < face_count; i++) {
										int			old = face_mapping[i];

										if (BIT (*_hoops_CPRI->_hoops_CHHPR (old), LFA_EXPLICIT_NORMAL)) {
											HC_Open_Face (i);
												HC_Set_Normal (_hoops_CPRI->normals[old].a, _hoops_CPRI->normals[old].b, _hoops_CPRI->normals[old].c);
											HC_Close_Face ();
										}
									}
								HC_Close_Geometry ();
							POPNAME(_hoops_RIGC);
						}
					}
				}


				FREE_ARRAY (points, s->point_count, Point);
				FREE_ARRAY (face_list, s->face_list_length, int);

				FREE_ARRAY (_hoops_ICAPA, s->point_count, int);
				FREE_ARRAY (face_mapping, s->face_count, int);

				FREE_ARRAY (_hoops_GCAPA, s->face_count, bool);
				FREE_ARRAY (_hoops_RCAPA, s->face_count+1, int const *);
			}
			else {
				// _hoops_RRP _hoops_IRS _hoops_IPS _hoops_IIGR _hoops_RH _hoops_GIGR _hoops_IH _hoops_ASCA _hoops_SAHR _hoops_RH _hoops_RSSI
				Shell alter *		_hoops_HSAPA = (Shell *)HI_Copy_Geometry (_hoops_RIGC, g);

				//_hoops_ISAPA (_hoops_CSAPA);
				//_hoops_IIAPA (_hoops_CSAPA);

				HI_Insert_Geometry (_hoops_RIGC, (_hoops_HPAH *)faces, (Geometry *)_hoops_HSAPA, false, 0);
			}


			// _hoops_PPR _hoops_HA _hoops_PPRI _hoops_RH _hoops_GIGR
			_hoops_CIGPR (_hoops_RIGC,g);
			HI_Table_Remove_Geometry (g);
			_hoops_HPRH (g);
		}

		return top;
	}

	return null;
}

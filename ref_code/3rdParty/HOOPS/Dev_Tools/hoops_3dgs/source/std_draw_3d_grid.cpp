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
 * $Id: obf_tmp.txt 1.139 2010-10-04 23:03:31 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "patterns.h"
#include "driver.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"

#define _hoops_SHHIS			5000.0f


local bool _hoops_GIHIS (
	Net_Rendition const &		nr,
	Grid const *				grid,
	float						x,
	float						y,
	Point alter *				_hoops_SIAIA) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			_hoops_APRA;
	Point						line[2];
	float						_hoops_SSHGA, w, t;
	Point						pt;
	Vector						direction;

	/* _hoops_IIHA _hoops_GASAS _hoops_GPP _hoops_RRGR _hoops_SRS _hoops_CPHR _hoops_IH _hoops_RIHIS */

	_hoops_APRA = _hoops_IHCR->matrix->_hoops_PPRA()->data.elements;

	pt.x = x;
	pt.y = y;
	pt.z = 0.0f;

	line[0].x = _hoops_HPRA (_hoops_APRA, pt);
	line[0].y = _hoops_IPRA (_hoops_APRA, pt);
	line[0].z = _hoops_CPRA (_hoops_APRA, pt);

	w = _hoops_PHCP (_hoops_APRA, pt);

	if (w != 1.0f) {
		if (w == 0.0f) return false;
		w = 1.0f / w;

		line[0].x *= w;
		line[0].y *= w;
		line[0].z *= w;
	}


	pt.z = _hoops_IHCR->_hoops_PCHH / 2;

	line[1].x = _hoops_HPRA (_hoops_APRA, pt);
	line[1].y = _hoops_IPRA (_hoops_APRA, pt);
	line[1].z = _hoops_CPRA (_hoops_APRA, pt);

	w = _hoops_PHCP (_hoops_APRA, pt);

	if (w != 1.0f) {
		if (w == 0.0f) return false;
		w = 1.0f / w;

		line[1].x *= w;
		line[1].y *= w;
		line[1].z *= w;
	}

	direction.x = line[1].x - line[0].x;
	direction.y = line[1].y - line[0].y;
	direction.z = line[1].z - line[0].z;

	if (!HI_Normalize (&direction)) return false;


	_hoops_SSHGA = grid->plane.a * direction.x	 +
			grid->plane.b * direction.y	 +
			grid->plane.c * direction.z;


	if (Abs(_hoops_SSHGA) < 0.0001f) return false;	/* _hoops_PSP _hoops_PPPSR _hoops_RHHR */


	t = grid->plane.d +
		grid->plane.a * line[0].x +
		grid->plane.b * line[0].y +
		grid->plane.c * line[0].z;
	t /= -_hoops_SSHGA;


	_hoops_SIAIA->x = line[0].x + t * direction.x;
	_hoops_SIAIA->y = line[0].y + t * direction.y;
	_hoops_SIAIA->z = line[0].z + t * direction.z;

	if (_hoops_IHCR->_hoops_SPH->projection == _hoops_GHH  &&
		(w = _hoops_PHCP (_hoops_IHCR->matrix->data.elements, *_hoops_SIAIA)) < 0.0f)
		return false;			/* _hoops_GHIPR _hoops_RHC */


	return true;
}




local bool _hoops_AIHIS (
	Net_Rendition const & nr,
	Grid const			*grid,
	float					x,
	float					y,
	float alter				*_hoops_PIHIS,
	float alter				*_hoops_HIHIS) {
	float					_hoops_SSHGA;
	Point				_hoops_SIAIA;
	float					a0, a1, a2, _hoops_SACIC, _hoops_IHHI, _hoops_CHHI;

	if (!_hoops_GIHIS (nr, grid, x, y, &_hoops_SIAIA))
		return false;

	if (Abs(grid->plane.a) > Abs(grid->plane.b) &&
		Abs(grid->plane.a) > Abs(grid->plane.c)) {
		a0 = _hoops_SIAIA.y - grid->origin.y;
		a1 = grid->_hoops_GGHI.y;
		a2 = grid->_hoops_RGHI.y;
		_hoops_SACIC = _hoops_SIAIA.z - grid->origin.z;
		_hoops_IHHI = grid->_hoops_GGHI.z;
		_hoops_CHHI = grid->_hoops_RGHI.z;
	}
	else if (Abs(grid->plane.b) > Abs(grid->plane.c)) {
		a0 = _hoops_SIAIA.x - grid->origin.x;
		a1 = grid->_hoops_GGHI.x;
		a2 = grid->_hoops_RGHI.x;
		_hoops_SACIC = _hoops_SIAIA.z - grid->origin.z;
		_hoops_IHHI = grid->_hoops_GGHI.z;
		_hoops_CHHI = grid->_hoops_RGHI.z;
	}
	else {
		a0 = _hoops_SIAIA.x - grid->origin.x;
		a1 = grid->_hoops_GGHI.x;
		a2 = grid->_hoops_RGHI.x;
		_hoops_SACIC = _hoops_SIAIA.y - grid->origin.y;
		_hoops_IHHI = grid->_hoops_GGHI.y;
		_hoops_CHHI = grid->_hoops_RGHI.y;
	}

	_hoops_SSHGA = a1 * _hoops_CHHI - a2 * _hoops_IHHI;

	*_hoops_PIHIS = (a0 * _hoops_CHHI - a2 * _hoops_SACIC) / _hoops_SSHGA;
	*_hoops_HIHIS = (a1 * _hoops_SACIC - a0 * _hoops_IHHI) / _hoops_SSHGA;

	return true;
}


local void _hoops_IIHIS (
	Net_Rendition const &		inr,
	Grid const *				grid,
	bool						_hoops_CIHIS,
	int							_hoops_PAIIA,
	int							_hoops_HAIIA,
	int							_hoops_IAIIA,
	int							_hoops_CAIIA) {
	Net_Rendition				nr = inr;
	_hoops_ACHR					_hoops_RGP;


	_hoops_RGP = nr->_hoops_RGP;

	if (_hoops_CIHIS && (_hoops_HAIIA - _hoops_PAIIA > 20000 || _hoops_CAIIA - _hoops_IAIIA > 20000)) {
		/* _hoops_SIHIS, _hoops_HIH _hoops_IIS'_hoops_GRI _hoops_AA _hoops_CPHP */
		/* _hoops_HSRS _hoops_IRS _hoops_CCAH _hoops_HAIR _hoops_IIHA _hoops_GPP _hoops_PCPA _hoops_CHH _hoops_SHH _hoops_CHCC _hoops_CGHI */
		if (ANYBIT (_hoops_RGP, T_VERTICES | T_PERIMETER_EDGES|_hoops_CRHGP|T_GENERIC_EDGES)) {
			_hoops_HHA			_hoops_ISHIR;

			_hoops_CIGA alter &		_hoops_CPIHP = nr.Modify()->_hoops_IHA.Modify();

			nr->_hoops_RGP &= ~T_LIGHTS_FOR_FACES;

			if (BIT (_hoops_RGP, T_VERTICES)) {
				_hoops_CPIHP->color = nr->_hoops_SCP->color;
				_hoops_ISHIR = nr->_hoops_SCP->_hoops_CHA;
				_hoops_CPIHP->_hoops_AGP = nr->_hoops_SCP->_hoops_AGP;
				if (BIT(nr->_hoops_RGP, T_LIGHTS_FOR_MARKERS))
					nr->_hoops_RGP |= T_LIGHTS_FOR_FACES;
			}
			else {
				_hoops_CPIHP->color = nr->_hoops_RHP->color;
				_hoops_ISHIR = nr->_hoops_RHP->_hoops_CHA;
				_hoops_CPIHP->_hoops_AGP = nr->_hoops_RHP->_hoops_AGP;
				if (BIT(nr->_hoops_RGP, T_LIGHTS_FOR_EDGES))
					nr->_hoops_RGP |= T_LIGHTS_FOR_FACES;
			}
			_hoops_CPIHP->_hoops_RGIR = _hoops_CPIHP->color;

			_hoops_CPIHP->_hoops_CHA = _hoops_ISHIR;
			_hoops_CPIHP->_hoops_GIA = _hoops_ISHIR;

			_hoops_CPIHP->pattern = FP_SOLID;
		}
		else if (!BIT (_hoops_RGP, T_FACES))
			return;		/* _hoops_RCSC _hoops_AAPR _hoops_SR _hoops_PIGS _hoops_APIC? */

		_hoops_RGP = T_FACES;				/* _hoops_PPR _hoops_SAHR _hoops_PGSA _hoops_SCH _hoops_GAR _hoops_RPP _hoops_SCH _hoops_AAPR _hoops_IRS _hoops_RPHSR _hoops_HSP */
	}


	if (BIT (_hoops_RGP, T_FACES)) {
		Polygon alter *		polygon;
		Point alter *		pl;

		Net_Rendition		_hoops_PPHIS = nr;

		if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE)) {
			_hoops_PPHIS.Modify()->_hoops_RGP &= ~T_ANY_POLYGON_EDGE;
		}

		ZALLOC (polygon, Polygon);

		polygon->_hoops_HIHI = 1;
		polygon->type = _hoops_RCIP;
		polygon->_hoops_RRHH = (grid->_hoops_RRHH & _hoops_RSPCR) |
								_hoops_ARHH|_hoops_IASGP;

		polygon->_hoops_CPGPR = grid->_hoops_CPGPR;
		polygon->_hoops_SPGPR = grid->_hoops_SPGPR;
		polygon->priority = grid->priority;

		polygon->plane.a = grid->plane.a;
		polygon->plane.b = grid->plane.b;
		polygon->plane.c = grid->plane.c;
		polygon->plane.d = grid->plane.d;

		ALLOC_ARRAY (pl, 4, Point);
		polygon->allocated = polygon->count = 4;
		polygon->points = pl;

		pl[0].x = grid->origin.x + _hoops_PAIIA * grid->_hoops_GGHI.x + _hoops_IAIIA * grid->_hoops_RGHI.x;
		pl[0].y = grid->origin.y + _hoops_PAIIA * grid->_hoops_GGHI.y + _hoops_IAIIA * grid->_hoops_RGHI.y;
		pl[0].z = grid->origin.z + _hoops_PAIIA * grid->_hoops_GGHI.z + _hoops_IAIIA * grid->_hoops_RGHI.z;

		pl[1].x = grid->origin.x + _hoops_HAIIA	* grid->_hoops_GGHI.x + _hoops_IAIIA * grid->_hoops_RGHI.x;
		pl[1].y = grid->origin.y + _hoops_HAIIA	* grid->_hoops_GGHI.y + _hoops_IAIIA * grid->_hoops_RGHI.y;
		pl[1].z = grid->origin.z + _hoops_HAIIA	* grid->_hoops_GGHI.z + _hoops_IAIIA * grid->_hoops_RGHI.z;

		pl[2].x = grid->origin.x + _hoops_HAIIA	* grid->_hoops_GGHI.x + _hoops_CAIIA	* grid->_hoops_RGHI.x;
		pl[2].y = grid->origin.y + _hoops_HAIIA	* grid->_hoops_GGHI.y + _hoops_CAIIA	* grid->_hoops_RGHI.y;
		pl[2].z = grid->origin.z + _hoops_HAIIA	* grid->_hoops_GGHI.z + _hoops_CAIIA	* grid->_hoops_RGHI.z;

		pl[3].x = grid->origin.x + _hoops_PAIIA * grid->_hoops_GGHI.x + _hoops_CAIIA	* grid->_hoops_RGHI.x;
		pl[3].y = grid->origin.y + _hoops_PAIIA * grid->_hoops_GGHI.y + _hoops_CAIIA	* grid->_hoops_RGHI.y;
		pl[3].z = grid->origin.z + _hoops_PAIIA * grid->_hoops_GGHI.z + _hoops_CAIIA	* grid->_hoops_RGHI.z;

		_hoops_RCAIP (_hoops_PPHIS, polygon);
		_hoops_HPRH (polygon);

		if (_hoops_GGPGR(nr)) 
			_hoops_RGP = 0;		/* _hoops_ICHRR-_hoops_HCICP _hoops_HHRPA _hoops_ASCA _hoops_RRGR */
	}

	if (ANYBIT (_hoops_RGP, T_PERIMETER_EDGES|_hoops_CRHGP|T_GENERIC_EDGES)) {
		Point				start, end;
		int					count1, count2;
		int					_hoops_GCHIS;
		Point alter			points[2];
		Polyedge *			pe=0;

		start.x = grid->origin.x + _hoops_PAIIA * grid->_hoops_GGHI.x + _hoops_IAIIA * grid->_hoops_RGHI.x;
		start.y = grid->origin.y + _hoops_PAIIA * grid->_hoops_GGHI.y + _hoops_IAIIA * grid->_hoops_RGHI.y;
		start.z = grid->origin.z + _hoops_PAIIA * grid->_hoops_GGHI.z + _hoops_IAIIA * grid->_hoops_RGHI.z;

		count1 = _hoops_HAIIA - _hoops_PAIIA;
		count2 = _hoops_CAIIA - _hoops_IAIIA;

		/*
		 * _hoops_PGSA _hoops_GPP _hoops_HARGR 1
		 */

		end.x	= grid->origin.x + _hoops_PAIIA * grid->_hoops_GGHI.x + _hoops_CAIIA	* grid->_hoops_RGHI.x;
		end.y	= grid->origin.y + _hoops_PAIIA * grid->_hoops_GGHI.y + _hoops_CAIIA	* grid->_hoops_RGHI.y;
		end.z	= grid->origin.z + _hoops_PAIIA * grid->_hoops_GGHI.z + _hoops_CAIIA	* grid->_hoops_RGHI.z;

		if (BIT (_hoops_RGP, T_GENERIC_EDGES))
			_hoops_GCHIS = 1;
		else
			_hoops_GCHIS = _hoops_HAIIA - _hoops_PAIIA;

		do {
			if (!pe || pe->_hoops_HSAI > 1) {
				if (pe) 
					_hoops_ISAI(pe);

				ZALLOC (pe, Polyedge);
				_hoops_ICAI(pe);
				pe->_hoops_GSCP = (Geometry *)grid;

				pe->points = points;
				pe->_hoops_PHHA = 1;
				pe->total = 2;
				pe->point_count = 2;
				pe->_hoops_SPHA = 1;
				pe->_hoops_SRHA = _hoops_SRHH|DL_TEMPORARY_DATA;
					
				pe->lengths_allocated = 1;
				pe->_hoops_IPII = 2;
				pe->_hoops_CPII = 2;
				ALLOC_ARRAY(pe->lengths, pe->lengths_allocated, int);
				ALLOC_ARRAY(pe->_hoops_AIHA, pe->_hoops_IPII, int);
				ALLOC_ARRAY(pe->_hoops_SPII, pe->_hoops_CPII, int);
				pe->_hoops_RAHH |= _hoops_AAHH;
			
				pe->lengths[0] = 2;

				pe->_hoops_AIHA[0] = 0;
				pe->_hoops_AIHA[1] = 1;
				pe->_hoops_SPII[0] = 0;
				pe->_hoops_SPII[1] = 0;
			}

			points[0].x = start.x + count1 * grid->_hoops_GGHI.x;
			points[0].y = start.y + count1 * grid->_hoops_GGHI.y;
			points[0].z = start.z + count1 * grid->_hoops_GGHI.z;

			points[1].x = end.x + count1 * grid->_hoops_GGHI.x;
			points[1].y = end.y + count1 * grid->_hoops_GGHI.y;
			points[1].z = end.z + count1 * grid->_hoops_GGHI.z;

			_hoops_RAIGH (nr, pe);
		} _hoops_RGGA ((count1 -= _hoops_GCHIS) < 0);


		/*
		 * _hoops_PGSA _hoops_GPP _hoops_HARGR 2
		 */

		end.x	= grid->origin.x + _hoops_HAIIA	* grid->_hoops_GGHI.x + _hoops_IAIIA * grid->_hoops_RGHI.x;
		end.y	= grid->origin.y + _hoops_HAIIA	* grid->_hoops_GGHI.y + _hoops_IAIIA * grid->_hoops_RGHI.y;
		end.z	= grid->origin.z + _hoops_HAIIA	* grid->_hoops_GGHI.z + _hoops_IAIIA * grid->_hoops_RGHI.z;

		if (BIT (_hoops_RGP, T_GENERIC_EDGES))
			_hoops_GCHIS = 1;
		else
			_hoops_GCHIS = _hoops_CAIIA - _hoops_IAIIA;

		do {
			if (!pe || pe->_hoops_HSAI > 1) {
				if (pe) 
					_hoops_ISAI(pe);

				ZALLOC (pe, Polyedge);
				_hoops_ICAI(pe);
				pe->_hoops_GSCP = (Geometry *)grid;

				pe->points = points;
				pe->_hoops_PHHA = 1;
				pe->total = 2;
				pe->point_count = 2;
				pe->_hoops_SPHA = 1;
				pe->_hoops_SRHA = _hoops_SRHH|DL_TEMPORARY_DATA;
					
				pe->lengths_allocated = 1;
				pe->_hoops_IPII = 2;
				pe->_hoops_CPII = 2;
				ALLOC_ARRAY(pe->lengths, pe->lengths_allocated, int);
				ALLOC_ARRAY(pe->_hoops_AIHA, pe->_hoops_IPII, int);
				ALLOC_ARRAY(pe->_hoops_SPII, pe->_hoops_CPII, int);
				pe->_hoops_RAHH |= _hoops_AAHH;
			
				pe->lengths[0] = 2;

				pe->_hoops_AIHA[0] = 0;
				pe->_hoops_AIHA[1] = 1;
				pe->_hoops_SPII[0] = 0;
				pe->_hoops_SPII[1] = 0;
			}

			points[0].x = start.x + count2 * grid->_hoops_RGHI.x;
			points[0].y = start.y + count2 * grid->_hoops_RGHI.y;
			points[0].z = start.z + count2 * grid->_hoops_RGHI.z;

			points[1].x = end.x + count2 * grid->_hoops_RGHI.x;
			points[1].y = end.y + count2 * grid->_hoops_RGHI.y;
			points[1].z = end.z + count2 * grid->_hoops_RGHI.z;

			_hoops_RAIGH (nr, pe);
		} _hoops_RGGA ((count2 -= _hoops_GCHIS) < 0);

		if (_hoops_ISAI(pe) == 0)
			HI_Free_Polyedge(pe);
	}

	/*
	 * _hoops_HSPP _hoops_ASCA _hoops_PSSI
	 */

	if (BIT (_hoops_RGP, T_VERTICES)) {
		Point				start;
		int					point_count;
		int					count1, count2;
		Point alter *		points;
		Point alter *		pt;
		int alter *			vlist;
		int alter *			_hoops_RCHIS;
		Polymarker*			pm;

		start.x = grid->origin.x + _hoops_PAIIA * grid->_hoops_GGHI.x + _hoops_IAIIA * grid->_hoops_RGHI.x;
		start.y = grid->origin.y + _hoops_PAIIA * grid->_hoops_GGHI.y + _hoops_IAIIA * grid->_hoops_RGHI.y;
		start.z = grid->origin.z + _hoops_PAIIA * grid->_hoops_GGHI.z + _hoops_IAIIA * grid->_hoops_RGHI.z;

		point_count = _hoops_CAIIA - _hoops_IAIIA + 1;
		
		count1 = _hoops_HAIIA - _hoops_PAIIA;

		do {
			ALLOC_ARRAY_ALIGNED (points, point_count, Point, 16);
			ALLOC_ARRAY (vlist, point_count, int);
			ZALLOC(pm, Polymarker);
			_hoops_ICAI(pm);

			pm->_hoops_GSCP = (Geometry *) grid;
			pm->_hoops_AIHA = vlist;
			pm->_hoops_IPII = point_count;
			pm->_hoops_RAHH |= _hoops_AAHH;
			pm->points = points;
			pm->_hoops_RAHH |= _hoops_AIPI;
			pm->point_count = point_count;
			pm->length = point_count;
			pm->_hoops_SRHA = _hoops_SRHH;

			pt = points;
			_hoops_RCHIS = vlist;
			count2 = point_count - 1;
			do {
				pt->x = start.x + count1 * grid->_hoops_GGHI.x + count2 * grid->_hoops_RGHI.x;
				pt->y = start.y + count1 * grid->_hoops_GGHI.y + count2 * grid->_hoops_RGHI.y;
				pt->z = start.z + count1 * grid->_hoops_GGHI.z + count2 * grid->_hoops_RGHI.z;
				*_hoops_RCHIS++ = pt - points;
				++pt;
			} _hoops_RGGA (count2-- <= 0);

			
			_hoops_HAIGH (nr, pm);

			if (_hoops_ISAI(pm) == 0)
				HI_Free_Polymarker_List(pm);

			if (_hoops_GGPGR(nr)) 
				break;
		} _hoops_RGGA (count1-- <= 0);


	}
}


local void _hoops_ACHIS (
	Net_Rendition const &		nr,
	Grid const *				grid) {
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	float						_hoops_PCHIS[5][2];
	int							_hoops_RCIPS, _hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC;
	float						left, right, bottom, top;
	bool						ll, _hoops_HC, _hoops_HCHIS, _hoops_SIGIP;

	left = (float)_hoops_SGRA->_hoops_PHRA.left;
	right = (float)_hoops_SGRA->_hoops_PHRA.right;
	bottom = (float)_hoops_SGRA->_hoops_PHRA.bottom;
	top = (float)_hoops_SGRA->_hoops_PHRA.top;

	ll = _hoops_AIHIS (nr, grid, left, bottom,
								   &_hoops_PCHIS[0][0], &_hoops_PCHIS[0][1]);
	_hoops_HC = _hoops_AIHIS (nr, grid, right, bottom,
								   &_hoops_PCHIS[1][0], &_hoops_PCHIS[1][1]);
	_hoops_HCHIS = _hoops_AIHIS (nr, grid, left, top,
								   &_hoops_PCHIS[2][0], &_hoops_PCHIS[2][1]);
	_hoops_SIGIP = _hoops_AIHIS (nr, grid, right, top,
								   &_hoops_PCHIS[3][0], &_hoops_PCHIS[3][1]);

	if (ll && _hoops_HC && _hoops_HCHIS && _hoops_SIGIP) {
		/* _hoops_PIHGR, _hoops_SAHR _hoops_PGSA _hoops_PCPA _hoops_SR _hoops_RRP */
		float					_hoops_ICHIS, _hoops_CCHIS, _hoops_SCHIS, _hoops_GSHIS;

		_hoops_ICHIS = _hoops_CCHIS = _hoops_PCHIS[0][0];
		_hoops_SCHIS = _hoops_GSHIS = _hoops_PCHIS[0][1];

		if (_hoops_ICHIS > _hoops_PCHIS[1][0]) _hoops_ICHIS = _hoops_PCHIS[1][0];
		if (_hoops_CCHIS < _hoops_PCHIS[1][0]) _hoops_CCHIS = _hoops_PCHIS[1][0];
		if (_hoops_SCHIS > _hoops_PCHIS[1][1]) _hoops_SCHIS = _hoops_PCHIS[1][1];
		if (_hoops_GSHIS < _hoops_PCHIS[1][1]) _hoops_GSHIS = _hoops_PCHIS[1][1];

		if (_hoops_ICHIS > _hoops_PCHIS[2][0]) _hoops_ICHIS = _hoops_PCHIS[2][0];
		if (_hoops_CCHIS < _hoops_PCHIS[2][0]) _hoops_CCHIS = _hoops_PCHIS[2][0];
		if (_hoops_SCHIS > _hoops_PCHIS[2][1]) _hoops_SCHIS = _hoops_PCHIS[2][1];
		if (_hoops_GSHIS < _hoops_PCHIS[2][1]) _hoops_GSHIS = _hoops_PCHIS[2][1];

		if (_hoops_ICHIS > _hoops_PCHIS[3][0]) _hoops_ICHIS = _hoops_PCHIS[3][0];
		if (_hoops_CCHIS < _hoops_PCHIS[3][0]) _hoops_CCHIS = _hoops_PCHIS[3][0];
		if (_hoops_SCHIS > _hoops_PCHIS[3][1]) _hoops_SCHIS = _hoops_PCHIS[3][1];
		if (_hoops_GSHIS < _hoops_PCHIS[3][1]) _hoops_GSHIS = _hoops_PCHIS[3][1];

		_hoops_RCIPS = (int)_hoops_ICHIS - 1;			_hoops_ACIPS = (int)_hoops_CCHIS + 1;
		_hoops_PCIPS = (int)_hoops_SCHIS - 1;			_hoops_PSIGC = (int)_hoops_GSHIS + 1;

		if (grid->count1 < 0) {
			if (_hoops_ACIPS < grid->count1 ||
				_hoops_RCIPS > -grid->count1) return;	/* _hoops_CPRAH */

			if (_hoops_RCIPS < grid->count1) _hoops_RCIPS = grid->count1;
			if (_hoops_ACIPS > -grid->count1) _hoops_ACIPS = -grid->count1;
		}
		else if (grid->count1 > 0) {
			if (_hoops_ACIPS < 0 ||
				_hoops_RCIPS > grid->count1) return;	/* _hoops_CPRAH */

			if (_hoops_RCIPS < 0) _hoops_RCIPS = 0;
			if (_hoops_ACIPS > grid->count1) _hoops_ACIPS = grid->count1;
		}

		if (grid->count2 < 0) {
			if (_hoops_PSIGC < grid->count2 ||
				_hoops_PCIPS > -grid->count2) return;	/* _hoops_CPRAH */

			if (_hoops_PCIPS < grid->count2) _hoops_PCIPS = grid->count2;
			if (_hoops_PSIGC > -grid->count2) _hoops_PSIGC = -grid->count2;
		}
		else if (grid->count2 > 0) {
			if (_hoops_PSIGC < 0 ||
				_hoops_PCIPS > grid->count2) return;	/* _hoops_CPRAH */

			if (_hoops_PCIPS < 0) _hoops_PCIPS = 0;
			if (_hoops_PSIGC > grid->count2) _hoops_PSIGC = grid->count2;
		}

		_hoops_IIHIS (nr, grid, true, _hoops_RCIPS, _hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC);
	}
	else if (grid->count1 != 0 && grid->count2 != 0) {
		/* _hoops_PPAC, _hoops_HIS _hoops_SR _hoops_PAH _hoops_AA _hoops_SCH _hoops_APIC */

		if (grid->count1 < 0) {
			_hoops_RCIPS = grid->count1;
			_hoops_ACIPS = -grid->count1;
		}
		else {
			_hoops_RCIPS = 0;
			_hoops_ACIPS = grid->count1;
		}

		if (grid->count2 < 0) {
			_hoops_PCIPS = grid->count2;
			_hoops_PSIGC = -grid->count2;
		}
		else {
			_hoops_PCIPS = 0;
			_hoops_PSIGC = grid->count2;
		}

		_hoops_IIHIS (nr, grid, true, _hoops_RCIPS, _hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC);
	}
	else if (ll || _hoops_HC || _hoops_HCHIS || _hoops_SIGIP) {
		/* _hoops_AIHP _hoops_CCA "_hoops_RSHIS" -- _hoops_PHHR _hoops_GAR _hoops_SGIP _hoops_GAR _hoops_SIGR _hoops_GPP _hoops_GII _hoops_AIRSP
		** _hoops_SGS _hoops_SR _hoops_PAH _hoops_CAHA, _hoops_PPR _hoops_IRS _hoops_ICHRR _hoops_ASRAR _hoops_GGGGR */
		float					_hoops_ICHIS, _hoops_CCHIS, _hoops_SCHIS, _hoops_GSHIS;
		int						i;

		if (ll) {
			_hoops_ICHIS = _hoops_CCHIS = _hoops_PCHIS[0][0];
			_hoops_SCHIS = _hoops_GSHIS = _hoops_PCHIS[0][1];

			if (_hoops_HC) {
				if (_hoops_ICHIS > _hoops_PCHIS[1][0]) _hoops_ICHIS = _hoops_PCHIS[1][0];
				if (_hoops_CCHIS < _hoops_PCHIS[1][0]) _hoops_CCHIS = _hoops_PCHIS[1][0];
				if (_hoops_SCHIS > _hoops_PCHIS[1][1]) _hoops_SCHIS = _hoops_PCHIS[1][1];
				if (_hoops_GSHIS < _hoops_PCHIS[1][1]) _hoops_GSHIS = _hoops_PCHIS[1][1];
			}
			if (_hoops_HCHIS) {
				if (_hoops_ICHIS > _hoops_PCHIS[2][0]) _hoops_ICHIS = _hoops_PCHIS[2][0];
				if (_hoops_CCHIS < _hoops_PCHIS[2][0]) _hoops_CCHIS = _hoops_PCHIS[2][0];
				if (_hoops_SCHIS > _hoops_PCHIS[2][1]) _hoops_SCHIS = _hoops_PCHIS[2][1];
				if (_hoops_GSHIS < _hoops_PCHIS[2][1]) _hoops_GSHIS = _hoops_PCHIS[2][1];
			}
			if (_hoops_SIGIP) {
				if (_hoops_ICHIS > _hoops_PCHIS[3][0]) _hoops_ICHIS = _hoops_PCHIS[3][0];
				if (_hoops_CCHIS < _hoops_PCHIS[3][0]) _hoops_CCHIS = _hoops_PCHIS[3][0];
				if (_hoops_SCHIS > _hoops_PCHIS[3][1]) _hoops_SCHIS = _hoops_PCHIS[3][1];
				if (_hoops_GSHIS < _hoops_PCHIS[3][1]) _hoops_GSHIS = _hoops_PCHIS[3][1];
			}
		}
		else if (_hoops_HC) {
			_hoops_ICHIS = _hoops_CCHIS = _hoops_PCHIS[1][0];
			_hoops_SCHIS = _hoops_GSHIS = _hoops_PCHIS[1][1];

			if (_hoops_HCHIS) {
				if (_hoops_ICHIS > _hoops_PCHIS[2][0]) _hoops_ICHIS = _hoops_PCHIS[2][0];
				if (_hoops_CCHIS < _hoops_PCHIS[2][0]) _hoops_CCHIS = _hoops_PCHIS[2][0];
				if (_hoops_SCHIS > _hoops_PCHIS[2][1]) _hoops_SCHIS = _hoops_PCHIS[2][1];
				if (_hoops_GSHIS < _hoops_PCHIS[2][1]) _hoops_GSHIS = _hoops_PCHIS[2][1];
			}
			if (_hoops_SIGIP) {
				if (_hoops_ICHIS > _hoops_PCHIS[3][0]) _hoops_ICHIS = _hoops_PCHIS[3][0];
				if (_hoops_CCHIS < _hoops_PCHIS[3][0]) _hoops_CCHIS = _hoops_PCHIS[3][0];
				if (_hoops_SCHIS > _hoops_PCHIS[3][1]) _hoops_SCHIS = _hoops_PCHIS[3][1];
				if (_hoops_GSHIS < _hoops_PCHIS[3][1]) _hoops_GSHIS = _hoops_PCHIS[3][1];
			}
		}
		else if (_hoops_HCHIS) {
			_hoops_ICHIS = _hoops_CCHIS = _hoops_PCHIS[2][0];
			_hoops_SCHIS = _hoops_GSHIS = _hoops_PCHIS[2][1];

			if (_hoops_SIGIP) {
				if (_hoops_ICHIS > _hoops_PCHIS[3][0]) _hoops_ICHIS = _hoops_PCHIS[3][0];
				if (_hoops_CCHIS < _hoops_PCHIS[3][0]) _hoops_CCHIS = _hoops_PCHIS[3][0];
				if (_hoops_SCHIS > _hoops_PCHIS[3][1]) _hoops_SCHIS = _hoops_PCHIS[3][1];
				if (_hoops_GSHIS < _hoops_PCHIS[3][1]) _hoops_GSHIS = _hoops_PCHIS[3][1];
			}
		}
		else /* _hoops_RPP (_hoops_SGHSP) */ {
			_hoops_ICHIS = _hoops_CCHIS = _hoops_PCHIS[3][0];
			_hoops_SCHIS = _hoops_GSHIS = _hoops_PCHIS[3][1];
		}

#define _hoops_ASHIS	0.05f
		for (i=1; i<20; i++) {
			if (_hoops_AIHIS (nr, grid,
										   left,
										   bottom + i * _hoops_ASHIS * (top - bottom),
										   &_hoops_PCHIS[4][0], &_hoops_PCHIS[4][1])) {
				if (_hoops_ICHIS > _hoops_PCHIS[4][0] && _hoops_ICHIS - _hoops_PCHIS[4][0] < _hoops_SHHIS)
					_hoops_ICHIS = _hoops_PCHIS[4][0];
				if (_hoops_CCHIS < _hoops_PCHIS[4][0] && _hoops_PCHIS[4][0] - _hoops_CCHIS < _hoops_SHHIS)
					_hoops_CCHIS = _hoops_PCHIS[4][0];

				if (_hoops_SCHIS > _hoops_PCHIS[4][1] && _hoops_SCHIS - _hoops_PCHIS[4][1] < _hoops_SHHIS)
					_hoops_SCHIS = _hoops_PCHIS[4][1];
				if (_hoops_GSHIS < _hoops_PCHIS[4][1] && _hoops_PCHIS[4][1] - _hoops_GSHIS < _hoops_SHHIS)
					_hoops_GSHIS = _hoops_PCHIS[4][1];
			}
			if (_hoops_AIHIS (nr, grid,
										   right,
										   bottom + i * _hoops_ASHIS * (top - bottom),
										   &_hoops_PCHIS[4][0], &_hoops_PCHIS[4][1])) {
				if (_hoops_ICHIS > _hoops_PCHIS[4][0] && _hoops_ICHIS - _hoops_PCHIS[4][0] < _hoops_SHHIS)
					_hoops_ICHIS = _hoops_PCHIS[4][0];
				if (_hoops_CCHIS < _hoops_PCHIS[4][0] && _hoops_PCHIS[4][0] - _hoops_CCHIS < _hoops_SHHIS)
					_hoops_CCHIS = _hoops_PCHIS[4][0];

				if (_hoops_SCHIS > _hoops_PCHIS[4][1] && _hoops_SCHIS - _hoops_PCHIS[4][1] < _hoops_SHHIS)
					_hoops_SCHIS = _hoops_PCHIS[4][1];
				if (_hoops_GSHIS < _hoops_PCHIS[4][1] && _hoops_PCHIS[4][1] - _hoops_GSHIS < _hoops_SHHIS)
					_hoops_GSHIS = _hoops_PCHIS[4][1];
			}

			if (_hoops_AIHIS (nr, grid,
										   bottom,
										   left + i * _hoops_ASHIS * (right - left),
										   &_hoops_PCHIS[4][0], &_hoops_PCHIS[4][1])) {
				if (_hoops_ICHIS > _hoops_PCHIS[4][0] && _hoops_ICHIS - _hoops_PCHIS[4][0] < _hoops_SHHIS)
					_hoops_ICHIS = _hoops_PCHIS[4][0];
				if (_hoops_CCHIS < _hoops_PCHIS[4][0] && _hoops_PCHIS[4][0] - _hoops_CCHIS < _hoops_SHHIS)
					_hoops_CCHIS = _hoops_PCHIS[4][0];

				if (_hoops_SCHIS > _hoops_PCHIS[4][1] && _hoops_SCHIS - _hoops_PCHIS[4][1] < _hoops_SHHIS)
					_hoops_SCHIS = _hoops_PCHIS[4][1];
				if (_hoops_GSHIS < _hoops_PCHIS[4][1] && _hoops_PCHIS[4][1] - _hoops_GSHIS < _hoops_SHHIS)
					_hoops_GSHIS = _hoops_PCHIS[4][1];
			}
			if (_hoops_AIHIS (nr, grid,
										   top,
										   left + i * _hoops_ASHIS * (right - left),
										   &_hoops_PCHIS[4][0], &_hoops_PCHIS[4][1])) {
				if (_hoops_ICHIS > _hoops_PCHIS[4][0] && _hoops_ICHIS - _hoops_PCHIS[4][0] < _hoops_SHHIS)
					_hoops_ICHIS = _hoops_PCHIS[4][0];
				if (_hoops_CCHIS < _hoops_PCHIS[4][0] && _hoops_PCHIS[4][0] - _hoops_CCHIS < _hoops_SHHIS)
					_hoops_CCHIS = _hoops_PCHIS[4][0];

				if (_hoops_SCHIS > _hoops_PCHIS[4][1] && _hoops_SCHIS - _hoops_PCHIS[4][1] < _hoops_SHHIS)
					_hoops_SCHIS = _hoops_PCHIS[4][1];
				if (_hoops_GSHIS < _hoops_PCHIS[4][1] && _hoops_PCHIS[4][1] - _hoops_GSHIS < _hoops_SHHIS)
					_hoops_GSHIS = _hoops_PCHIS[4][1];
			}
		}

		_hoops_RCIPS = (int)_hoops_ICHIS - 100;				_hoops_ACIPS = (int)_hoops_CCHIS + 100;
		_hoops_PCIPS = (int)_hoops_SCHIS - 100;				_hoops_PSIGC = (int)_hoops_GSHIS + 100;

		if (grid->count1 < 0) {
			if (_hoops_ACIPS < grid->count1 ||
				_hoops_RCIPS > -grid->count1) return;	/* _hoops_CPRAH */

			if (_hoops_RCIPS < grid->count1) _hoops_RCIPS = grid->count1;
			if (_hoops_ACIPS > -grid->count1) _hoops_ACIPS = -grid->count1;
		}
		else if (grid->count1 > 0) {
			if (_hoops_ACIPS < 0 ||
				_hoops_RCIPS > grid->count1) return;	/* _hoops_CPRAH */

			if (_hoops_RCIPS < 0) _hoops_RCIPS = 0;
			if (_hoops_ACIPS > grid->count1) _hoops_ACIPS = grid->count1;
		}

		if (grid->count2 < 0) {
			if (_hoops_PSIGC < grid->count2 ||
				_hoops_PCIPS > -grid->count2) return;	/* _hoops_CPRAH */

			if (_hoops_PCIPS < grid->count2) _hoops_PCIPS = grid->count2;
			if (_hoops_PSIGC > -grid->count2) _hoops_PSIGC = -grid->count2;
		}
		else if (grid->count2 > 0) {
			if (_hoops_PSIGC < 0 ||
				_hoops_PCIPS > grid->count2) return;	/* _hoops_CPRAH */

			if (_hoops_PCIPS < 0) _hoops_PCIPS = 0;
			if (_hoops_PSIGC > grid->count2) _hoops_PSIGC = grid->count2;
		}

		_hoops_IIHIS (nr, grid, false, _hoops_RCIPS, _hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC);
	}
	else {
		/* _hoops_PIHA _hoops_SHH _hoops_PGI _hoops_PCCP _hoops_PGGS "_hoops_CGGR" _hoops_PGAP _hoops_GHCCP _hoops_RH _hoops_GRPC
		** _hoops_IIGR _hoops_RH _hoops_RAR, _hoops_PAR _hoops_PCCP _hoops_PGGS _hoops_IPPA _hoops_GGAIA _hoops_CCA _hoops_RH _hoops_RAR
		** _hoops_HAGA -- _hoops_CGH _hoops_RASHR _hoops_RGR _hoops_SPHR */


		if (grid->count1 == 0) {
			_hoops_RCIPS = -1000;
			_hoops_ACIPS = 1000;
		}
		else if (grid->count1 < 0) {
			_hoops_RCIPS = grid->count1;
			_hoops_ACIPS = -grid->count1;
		}
		else {
			_hoops_RCIPS = 0;
			_hoops_ACIPS = grid->count1;
		}

		if (grid->count2 == 0) {
			_hoops_PCIPS = -1000;
			_hoops_PSIGC = 1000;
		}
		else if (grid->count2 < 0) {
			_hoops_PCIPS = grid->count2;
			_hoops_PSIGC = -grid->count2;
		}
		else {
			_hoops_PCIPS = 0;
			_hoops_PSIGC = grid->count2;
		}

		_hoops_IIHIS (nr, grid, false, _hoops_RCIPS, _hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC);
	}
}




local bool _hoops_PSHIS (
	Net_Rendition const &		nr,
	Grid const *				grid,
	float						x,
	float						y,
	float alter *				_hoops_PIHIS,
	float alter *				_hoops_HIHIS) {
	Point						_hoops_SIAIA;
	Vector						tmp;
	float						_hoops_RAHCR, _hoops_RGCAS;

	if (!_hoops_GIHIS (nr, grid, x, y, &_hoops_SIAIA))
		return false;

	_hoops_RGCAS = _hoops_SGIHR (grid->_hoops_GGHI.x * grid->_hoops_GGHI.x +
				   grid->_hoops_GGHI.y * grid->_hoops_GGHI.y +
				   grid->_hoops_GGHI.z * grid->_hoops_GGHI.z);

	tmp.x = _hoops_SIAIA.x - grid->origin.x;
	tmp.y = _hoops_SIAIA.y - grid->origin.y;
	tmp.z = _hoops_SIAIA.z - grid->origin.z;

	*_hoops_PIHIS = _hoops_SGIHR (tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z) / _hoops_RGCAS;

	(void)HI_Normalize (&tmp);

	_hoops_RAHCR = _hoops_ISSSR ((grid->_hoops_GGHI.x * tmp.x  +
				   grid->_hoops_GGHI.y * tmp.y  +
				   grid->_hoops_GGHI.z * tmp.z) / _hoops_RGCAS);

	if (grid->_hoops_GGHI.x * tmp.x + grid->_hoops_GGHI.y * tmp.y + grid->_hoops_GGHI.z * tmp.z >= 0.0f)
		*_hoops_HIHIS = _hoops_RAHCR / (360.0f / grid->_hoops_IPIAA);
	else if (grid->count2 <= 0)
		*_hoops_HIHIS = -_hoops_RAHCR / (360.0f / grid->_hoops_IPIAA);
	else
		*_hoops_HIHIS = grid->_hoops_IPIAA - _hoops_RAHCR / (360.0f / grid->_hoops_IPIAA);

	return true;
}


local void _hoops_HSHIS (
	Net_Rendition const &		inr,
	Grid const *				grid,
	int							_hoops_ISHIS,
	int							_hoops_IAIIA,
	int							_hoops_CAIIA) {
	Net_Rendition				nr = inr;
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_ACHR					_hoops_RGP;
	float						start,
								end;
	int							count1,
								count2;
	bool						_hoops_GPIIA = false;
	float						_hoops_RAHCR, increment;
	float						_hoops_GGHCR, _hoops_AGHCR;


	_hoops_RGP = nr->_hoops_RGP;

	if (_hoops_ISHIS > 20000 ||
		_hoops_CAIIA - _hoops_IAIIA > 1000) {		/* _hoops_SIHIS, _hoops_HIH _hoops_IIS'_hoops_GRI _hoops_AA _hoops_CPHP */
		/* _hoops_HSRS _hoops_IRS _hoops_CCAH _hoops_HAIR _hoops_IIHA _hoops_GPP _hoops_PCPA _hoops_CHH _hoops_SHH _hoops_CHCC _hoops_CGHI */
		if (BIT (_hoops_RGP, T_VERTICES | T_PERIMETER_EDGES|_hoops_CRHGP|T_GENERIC_EDGES)) {
			_hoops_CIGA alter &		_hoops_CPIHP = nr.Modify()->_hoops_IHA.Modify();
			_hoops_HHA			_hoops_ISHIR;

			if (BIT (_hoops_RGP, T_VERTICES)) {
				_hoops_CPIHP->color = nr->_hoops_SCP->color;
				_hoops_ISHIR = nr->_hoops_SCP->_hoops_CHA;
			}
			else {
				_hoops_CPIHP->color = nr->_hoops_RHP->color;
				_hoops_ISHIR = nr->_hoops_RHP->_hoops_CHA;
			}
			_hoops_CPIHP->_hoops_RGIR = _hoops_CPIHP->color;

			_hoops_CPIHP->_hoops_CHA = _hoops_ISHIR;
			_hoops_CPIHP->_hoops_GIA = _hoops_ISHIR;

			_hoops_CPIHP->pattern = FP_SOLID;
		}
		else if (!BIT (_hoops_RGP, T_FACES))
			return;		/* _hoops_RCSC _hoops_AAPR _hoops_SR _hoops_PIGS _hoops_APIC? */

		_hoops_RGP = T_FACES;				/* _hoops_PPR _hoops_SAHR _hoops_PGSA _hoops_SCH _hoops_GAR _hoops_RPP _hoops_SCH _hoops_AAPR _hoops_IRS _hoops_RPHSR _hoops_HSP */
	}

	count1 = _hoops_ISHIS;
	count2 = grid->count2;

	if (count2 == 0) {
		start = 0.0f;
		end = 360.0f;
		count2 = grid->_hoops_IPIAA - 1;
	}
	else if (count2 > 0) {
		start = 0.0f;
		if (count2 >= grid->_hoops_IPIAA) {
			end = 360.0f;
			count2 = grid->_hoops_IPIAA - 1;
		}
		else {
			end = count2 * 360.0f / grid->_hoops_IPIAA;
			_hoops_GPIIA = true;
		}
	}
	else {
		count2 *= -2;
		if (count2 >= grid->_hoops_IPIAA) {
			start = 0.0f;
			end = 360.0f;
			count2 = grid->_hoops_IPIAA - 1;
		}
		else {
			end = count2 * 180.0f / grid->_hoops_IPIAA;
			start = -end;
			_hoops_GPIIA = true;
		}
	}

	if (BIT (_hoops_RGP, T_FACES)) {
		Polygon alter *		polygon;
		Point alter *		pl;

		Net_Rendition		_hoops_PPHIS = nr;

		if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE)) {
			_hoops_PPHIS.Modify()->_hoops_RGP &= ~T_ANY_POLYGON_EDGE;
		}

		POOL_ZALLOC (polygon, Polygon, dc->memory_pool);

		polygon->_hoops_HIHI = 1;
		polygon->type = _hoops_RCIP;
		polygon->_hoops_RRHH = (grid->_hoops_RRHH & _hoops_RSPCR) |
								_hoops_ARHH|_hoops_IASGP;
		polygon->_hoops_CPGPR = grid->_hoops_CPGPR;
		polygon->_hoops_SPGPR = grid->_hoops_SPGPR;
		polygon->priority = grid->priority;

		polygon->plane.a = grid->plane.a;
		polygon->plane.b = grid->plane.b;
		polygon->plane.c = grid->plane.c;
		polygon->plane.d = grid->plane.d;

		POOL_ALLOC_ARRAY_CACHED (pl, 76, Point, dc->memory_pool);
		polygon->allocated = 76;
		polygon->count = 0;
		polygon->points = pl;

		if (_hoops_GPIIA) {
			pl->x = grid->origin.x;
			pl->y = grid->origin.y;
			pl->z = grid->origin.z;
			++pl;
		}

		_hoops_RAHCR = start;
		increment = 5.0f;
		do {
			_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);
			pl->x = grid->origin.x +
					 count1 * (_hoops_AGHCR * grid->_hoops_GGHI.x + _hoops_GGHCR * grid->_hoops_RGHI.x);
			pl->y = grid->origin.y +
					 count1 * (_hoops_AGHCR * grid->_hoops_GGHI.y + _hoops_GGHCR * grid->_hoops_RGHI.y);
			pl->z = grid->origin.z +
					 count1 * (_hoops_AGHCR * grid->_hoops_GGHI.z + _hoops_GGHCR * grid->_hoops_RGHI.z);
			++pl;
		} _hoops_RGGA ((_hoops_RAHCR += increment) >= end);

		_hoops_RICH (end, _hoops_GGHCR, _hoops_AGHCR);
		pl->x = grid->origin.x +
					count1 * (_hoops_AGHCR * grid->_hoops_GGHI.x + _hoops_GGHCR * grid->_hoops_RGHI.x);
		pl->y = grid->origin.y +
					count1 * (_hoops_AGHCR * grid->_hoops_GGHI.y + _hoops_GGHCR * grid->_hoops_RGHI.y);
		pl->z = grid->origin.z +
					count1 * (_hoops_AGHCR * grid->_hoops_GGHI.z + _hoops_GGHCR * grid->_hoops_RGHI.z);
		++pl;

		polygon->count = pl - polygon->points;

		_hoops_RCAIP (_hoops_PPHIS, polygon);

		_hoops_HPRH (polygon);

		if (_hoops_GGPGR(nr)) 
			_hoops_RGP = 0;
	}


	if (ANYBIT (_hoops_RGP, T_PERIMETER_EDGES|_hoops_CRHGP|T_GENERIC_EDGES)) {
		Elliptical_Arc alter *	arc = null;
		int						_hoops_GCHIS;

		if ((end - start != 360.0f) || BIT (_hoops_RGP, T_GENERIC_EDGES)) {
			Point alter			points[2];
			int					_hoops_CSHIS = count2;
			Polyedge *			pe = null;

			/*
			 * _hoops_PGSA _hoops_GHARP _hoops_SSHIS
			 */

			_hoops_RAHCR = start;
			if (BIT (_hoops_RGP, T_GENERIC_EDGES)) {
				increment = 360.0f / grid->_hoops_IPIAA;
				_hoops_GCHIS = 1;
			}
			else {
				increment = end - start;
				_hoops_GCHIS = count2;
			}

			points[0].x = grid->origin.x;
			points[0].y = grid->origin.y;
			points[0].z = grid->origin.z;

			do {
				if (!pe || pe->_hoops_HSAI > 1) {
					if (pe) 
						_hoops_ISAI(pe);

					POOL_ZALLOC (pe, Polyedge, dc->memory_pool);
					_hoops_ICAI(pe);
					pe->_hoops_GSCP = (Geometry *)grid;

					pe->points = points;
					pe->_hoops_PHHA = 1;
					pe->total = 2;
					pe->point_count = 2;
					pe->_hoops_SPHA = 1;
					pe->_hoops_SRHA = _hoops_SRHH|DL_TEMPORARY_DATA;
						
					pe->lengths_allocated = 1;
					pe->_hoops_IPII = 2;
					pe->_hoops_CPII = 2;
					POOL_ALLOC_ARRAY_CACHED(pe->lengths, pe->lengths_allocated, int, dc->memory_pool);
					POOL_ALLOC_ARRAY_CACHED(pe->_hoops_AIHA, pe->_hoops_IPII, int, dc->memory_pool);
					POOL_ALLOC_ARRAY_CACHED(pe->_hoops_SPII, pe->_hoops_CPII, int, dc->memory_pool);
					pe->_hoops_RAHH |= _hoops_AAHH;
				
					pe->lengths[0] = 2;

					pe->_hoops_AIHA[0] = 0;
					pe->_hoops_AIHA[1] = 1;
					pe->_hoops_SPII[0] = 0;
					pe->_hoops_SPII[1] = 0;
				}

				_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);

				points[1].x = grid->origin.x +
					count1 * (_hoops_AGHCR * grid->_hoops_GGHI.x + _hoops_GGHCR * grid->_hoops_RGHI.x);
				points[1].y = grid->origin.y +
					count1 * (_hoops_AGHCR * grid->_hoops_GGHI.y + _hoops_GGHCR * grid->_hoops_RGHI.y);
				points[1].z = grid->origin.z +
					count1 * (_hoops_AGHCR * grid->_hoops_GGHI.z + _hoops_GGHCR * grid->_hoops_RGHI.z);

				_hoops_RAIGH (nr, pe);

				_hoops_RAHCR += increment;
			} _hoops_RGGA ((count2 -= _hoops_GCHIS) < 0);

			count2 = _hoops_CSHIS;
			
			if (_hoops_ISAI(pe) == 0)
				HI_Free_Polyedge(pe);
		}

		/*
		 * _hoops_PGSA _hoops_RRRC
		 */

		if (BIT (_hoops_RGP, T_GENERIC_EDGES))
			_hoops_GCHIS = 1;
		else
			_hoops_GCHIS = count1;

		do {
			if (arc == null || arc->_hoops_HIHI != 1) {
				POOL_ALLOC (arc, Elliptical_Arc, dc->memory_pool);

				arc->_hoops_HIHI = 1;
				arc->type = _hoops_GIIP;
				arc->_hoops_RRHH = grid->_hoops_RRHH & _hoops_RSPCR;
				arc->owner = null;
				arc->_hoops_CPGPR = grid->_hoops_CPGPR;
				arc->_hoops_SPGPR = grid->_hoops_SPGPR;
				arc->_hoops_IPPGR = null;

				arc->center.x = grid->origin.x;
				arc->center.y = grid->origin.y;
				arc->center.z = grid->origin.z;
			}

			if (start == 0.0f && end == 360.0f) {
				arc->_hoops_GGHI.x = grid->_hoops_GGHI.x * count1;
				arc->_hoops_GGHI.y = grid->_hoops_GGHI.y * count1;
				arc->_hoops_GGHI.z = grid->_hoops_GGHI.z * count1;
				arc->_hoops_RGHI.x = grid->_hoops_RGHI.x * count1;
				arc->_hoops_RGHI.y = grid->_hoops_RGHI.y * count1;
				arc->_hoops_RGHI.z = grid->_hoops_RGHI.z * count1;
				arc->arc_start = 0.0f;
				arc->_hoops_PHHI = 1.0f;
			}
			else if (grid->count2 > 0) {
				arc->_hoops_GGHI.x = grid->_hoops_GGHI.x * count1;
				arc->_hoops_GGHI.y = grid->_hoops_GGHI.y * count1;
				arc->_hoops_GGHI.z = grid->_hoops_GGHI.z * count1;
				arc->_hoops_RGHI.x = grid->_hoops_RGHI.x * count1;
				arc->_hoops_RGHI.y = grid->_hoops_RGHI.y * count1;
				arc->_hoops_RGHI.z = grid->_hoops_RGHI.z * count1;
				arc->arc_start = 0.0f;
				arc->_hoops_PHHI = end/360.0f;
			}
			else {
				arc->_hoops_GGHI.x = -grid->_hoops_GGHI.x * count1;
				arc->_hoops_GGHI.y = -grid->_hoops_GGHI.y * count1;
				arc->_hoops_GGHI.z = -grid->_hoops_GGHI.z * count1;
				arc->_hoops_RGHI.x = -grid->_hoops_RGHI.x * count1;
				arc->_hoops_RGHI.y = -grid->_hoops_RGHI.y * count1;
				arc->_hoops_RGHI.z = -grid->_hoops_RGHI.z * count1;
				arc->arc_start = (180.0f + start) / 360.0f;
				arc->_hoops_PHHI = (180.0f + end) / 360.0f;
			}

			_hoops_CAICP (nr, arc);

			if (_hoops_GGPGR(nr)) 
				break;

			count1 -= _hoops_GCHIS;
		} _hoops_RGGA (count1 <= 0);

		count1 = _hoops_ISHIS;

		_hoops_HPRH (arc);

		if (_hoops_GGPGR(nr)) 
			_hoops_RGP = 0;
	}


	/*
	 * _hoops_HSPP _hoops_ASCA _hoops_PSSI
	 */

	if (BIT (_hoops_RGP, T_VERTICES)) {
		Point alter *		points;
		Point alter *		pt;
		Point				radius;
		int alter *			vlist;
		int alter *			_hoops_RCHIS;
		Polymarker*			pm;

		POOL_ALLOC_ARRAY (vlist, 1, int, dc->memory_pool);
		POOL_ZALLOC(pm, Polymarker, dc->memory_pool);
		_hoops_ICAI(pm);
		pm->_hoops_GSCP = (Geometry *)grid;

		pm->_hoops_AIHA = vlist;
		pm->_hoops_IPII = 1;
		pm->_hoops_RAHH |= _hoops_AAHH;
		pm->points = (Point alter *)&grid->origin;
		pm->point_count = 1;
		pm->length = 1;
		pm->_hoops_SRHA = _hoops_SRHH;
		vlist[0] = 0;

		_hoops_HAIGH (nr, pm);

		if (_hoops_ISAI(pm) == 0)
			HI_Free_Polymarker_List(pm);

		

		_hoops_RAHCR = start;
		increment = 360.0f / grid->_hoops_IPIAA;
		do {
			POOL_ZALLOC_ARRAY_CACHED (vlist, _hoops_ISHIS, int, dc->memory_pool);
			POOL_ALLOC_ARRAY_ALIGNED_CACHED (points, _hoops_ISHIS, Point, 16, dc->memory_pool);
			POOL_ZALLOC(pm, Polymarker, dc->memory_pool);
			_hoops_ICAI(pm);
			pm->_hoops_GSCP = (Geometry *)grid;

			pm->_hoops_AIHA = vlist;
			pm->_hoops_IPII = _hoops_ISHIS;
			pm->_hoops_RAHH |= _hoops_AAHH;
			pm->points = points;
			pm->point_count = _hoops_ISHIS;
			pm->_hoops_RAHH |= _hoops_AIPI;
			pm->length = _hoops_ISHIS;
			pm->_hoops_SRHA = _hoops_SRHH;
			pt = points;
			_hoops_RCHIS = vlist;
			count1 = _hoops_ISHIS;

			_hoops_RICH (_hoops_RAHCR, _hoops_GGHCR, _hoops_AGHCR);
			_hoops_RAHCR += increment;

			radius.x = _hoops_AGHCR * grid->_hoops_GGHI.x + _hoops_GGHCR * grid->_hoops_RGHI.x;
			radius.y = _hoops_AGHCR * grid->_hoops_GGHI.y + _hoops_GGHCR * grid->_hoops_RGHI.y;
			radius.z = _hoops_AGHCR * grid->_hoops_GGHI.z + _hoops_GGHCR * grid->_hoops_RGHI.z;

			do {
				pt->x = grid->origin.x + count1 * radius.x;
				pt->y = grid->origin.y + count1 * radius.y;
				pt->z = grid->origin.z + count1 * radius.z;
				*_hoops_RCHIS++ = pt - points;
				++pt;
			} _hoops_RGGA (--count1 <= 0);

			_hoops_HAIGH (nr, pm);

			if (_hoops_ISAI(pm) == 0)
				HI_Free_Polymarker_List(pm);

			if (_hoops_GGPGR(nr)) 
				break;
		} _hoops_RGGA (count2-- <= 0);

	}
}


local void _hoops_GGIIS (
	Net_Rendition const &		nr,
	Grid const *				grid) {
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	float						_hoops_PCHIS[5][2];
	int							_hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC;
	float						left, right, bottom, top;
	bool						ll, _hoops_HC, _hoops_HCHIS, _hoops_SIGIP;

	left = (float)_hoops_SGRA->_hoops_PHRA.left;
	right = (float)_hoops_SGRA->_hoops_PHRA.right;
	bottom = (float)_hoops_SGRA->_hoops_PHRA.bottom;
	top = (float)_hoops_SGRA->_hoops_PHRA.top;

	ll = _hoops_PSHIS (nr, grid, left, bottom,
								   &_hoops_PCHIS[0][0], &_hoops_PCHIS[0][1]);
	_hoops_HC = _hoops_PSHIS (nr, grid, right, bottom,
								   &_hoops_PCHIS[1][0], &_hoops_PCHIS[1][1]);
	_hoops_HCHIS = _hoops_PSHIS (nr, grid, left, top,
								   &_hoops_PCHIS[2][0], &_hoops_PCHIS[2][1]);
	_hoops_SIGIP = _hoops_PSHIS (nr, grid, right, top,
								   &_hoops_PCHIS[3][0], &_hoops_PCHIS[3][1]);

	if (ll && _hoops_HC && _hoops_HCHIS && _hoops_SIGIP) {
		/* _hoops_PIHGR, _hoops_SAHR _hoops_PGSA _hoops_PCPA _hoops_SR _hoops_RRP */
		float					_hoops_CCHIS, _hoops_SCHIS, _hoops_GSHIS;

		_hoops_CCHIS = _hoops_PCHIS[0][0];
		_hoops_SCHIS = _hoops_GSHIS = _hoops_PCHIS[0][1];

		if (_hoops_CCHIS < _hoops_PCHIS[1][0]) _hoops_CCHIS = _hoops_PCHIS[1][0];
		if (_hoops_SCHIS > _hoops_PCHIS[1][1]) _hoops_SCHIS = _hoops_PCHIS[1][1];
		if (_hoops_GSHIS < _hoops_PCHIS[1][1]) _hoops_GSHIS = _hoops_PCHIS[1][1];

		if (_hoops_CCHIS < _hoops_PCHIS[2][0]) _hoops_CCHIS = _hoops_PCHIS[2][0];
		if (_hoops_SCHIS > _hoops_PCHIS[2][1]) _hoops_SCHIS = _hoops_PCHIS[2][1];
		if (_hoops_GSHIS < _hoops_PCHIS[2][1]) _hoops_GSHIS = _hoops_PCHIS[2][1];

		if (_hoops_CCHIS < _hoops_PCHIS[3][0]) _hoops_CCHIS = _hoops_PCHIS[3][0];
		if (_hoops_SCHIS > _hoops_PCHIS[3][1]) _hoops_SCHIS = _hoops_PCHIS[3][1];
		if (_hoops_GSHIS < _hoops_PCHIS[3][1]) _hoops_GSHIS = _hoops_PCHIS[3][1];

		_hoops_ACIPS = (int)_hoops_CCHIS + 5;
		_hoops_PCIPS = (int)_hoops_SCHIS - 5;			_hoops_PSIGC = (int)_hoops_GSHIS + 5;

		if (grid->count1 < 0) {
			if (_hoops_ACIPS < grid->count1) return;	/* _hoops_CPRAH */

			if (_hoops_ACIPS > -grid->count1) _hoops_ACIPS = -grid->count1;
		}
		else if (grid->count1 > 0) {
			if (_hoops_ACIPS < 0) return;		/* _hoops_CPRAH */

			if (_hoops_ACIPS > grid->count1) _hoops_ACIPS = grid->count1;
		}

		if (grid->count2 < 0) {
			if (_hoops_PSIGC < grid->count2 ||
				_hoops_PCIPS > -grid->count2) return;	/* _hoops_CPRAH */

			if (_hoops_PCIPS < grid->count2) _hoops_PCIPS = grid->count2;
			if (_hoops_PSIGC > -grid->count2) _hoops_PSIGC = -grid->count2;
		}
		else if (grid->count2 > 0) {
			if (_hoops_PSIGC < 0 ||
				_hoops_PCIPS > grid->count2) return;	/* _hoops_CPRAH */

			if (_hoops_PCIPS < 0) _hoops_PCIPS = 0;
			if (_hoops_PSIGC > grid->count2) _hoops_PSIGC = grid->count2;
		}

		_hoops_HSHIS (nr, grid, _hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC);
	}
	else if (grid->count1 != 0 && grid->count2 != 0) {
		/* _hoops_PPAC, _hoops_HIS _hoops_SR _hoops_PAH _hoops_AA _hoops_SCH _hoops_APIC */

		if (grid->count1 < 0) {
			_hoops_ACIPS = -grid->count1;
		}
		else {
			_hoops_ACIPS = grid->count1;
		}

		if (grid->count2 < 0) {
			_hoops_PCIPS = grid->count2;
			_hoops_PSIGC = -grid->count2;
		}
		else {
			_hoops_PCIPS = 0;
			_hoops_PSIGC = grid->count2;
		}

		_hoops_HSHIS (nr, grid, _hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC);
	}
	else if (ll || _hoops_HC || _hoops_HCHIS || _hoops_SIGIP) {
		/* _hoops_AIHP _hoops_CCA "_hoops_RSHIS" -- _hoops_PHHR _hoops_GAR _hoops_SGIP _hoops_GAR _hoops_SIGR _hoops_GPP _hoops_GII _hoops_AIRSP
		** _hoops_SGS _hoops_SR _hoops_PAH _hoops_CAHA, _hoops_PPR _hoops_IRS _hoops_ICHRR _hoops_ASRAR _hoops_GGGGR */
		float					_hoops_CCHIS, _hoops_SCHIS, _hoops_GSHIS;

		if (ll) {
			_hoops_CCHIS = _hoops_PCHIS[0][0];
			_hoops_SCHIS = _hoops_GSHIS = _hoops_PCHIS[0][1];

			if (_hoops_HC) {
				if (_hoops_CCHIS < _hoops_PCHIS[1][0]) _hoops_CCHIS = _hoops_PCHIS[1][0];
				if (_hoops_SCHIS > _hoops_PCHIS[1][1]) _hoops_SCHIS = _hoops_PCHIS[1][1];
				if (_hoops_GSHIS < _hoops_PCHIS[1][1]) _hoops_GSHIS = _hoops_PCHIS[1][1];
			}
			if (_hoops_HCHIS) {
				if (_hoops_CCHIS < _hoops_PCHIS[2][0]) _hoops_CCHIS = _hoops_PCHIS[2][0];
				if (_hoops_SCHIS > _hoops_PCHIS[2][1]) _hoops_SCHIS = _hoops_PCHIS[2][1];
				if (_hoops_GSHIS < _hoops_PCHIS[2][1]) _hoops_GSHIS = _hoops_PCHIS[2][1];
			}
			if (_hoops_SIGIP) {
				if (_hoops_CCHIS < _hoops_PCHIS[3][0]) _hoops_CCHIS = _hoops_PCHIS[3][0];
				if (_hoops_SCHIS > _hoops_PCHIS[3][1]) _hoops_SCHIS = _hoops_PCHIS[3][1];
				if (_hoops_GSHIS < _hoops_PCHIS[3][1]) _hoops_GSHIS = _hoops_PCHIS[3][1];
			}
		}
		else if (_hoops_HC) {
			_hoops_CCHIS = _hoops_PCHIS[1][0];
			_hoops_SCHIS = _hoops_GSHIS = _hoops_PCHIS[1][1];

			if (_hoops_HCHIS) {
				if (_hoops_CCHIS < _hoops_PCHIS[2][0]) _hoops_CCHIS = _hoops_PCHIS[2][0];
				if (_hoops_SCHIS > _hoops_PCHIS[2][1]) _hoops_SCHIS = _hoops_PCHIS[2][1];
				if (_hoops_GSHIS < _hoops_PCHIS[2][1]) _hoops_GSHIS = _hoops_PCHIS[2][1];
			}
			if (_hoops_SIGIP) {
				if (_hoops_CCHIS < _hoops_PCHIS[3][0]) _hoops_CCHIS = _hoops_PCHIS[3][0];
				if (_hoops_SCHIS > _hoops_PCHIS[3][1]) _hoops_SCHIS = _hoops_PCHIS[3][1];
				if (_hoops_GSHIS < _hoops_PCHIS[3][1]) _hoops_GSHIS = _hoops_PCHIS[3][1];
			}
		}
		else if (_hoops_HCHIS) {
			_hoops_CCHIS = _hoops_PCHIS[2][0];
			_hoops_SCHIS = _hoops_GSHIS = _hoops_PCHIS[2][1];

			if (_hoops_SIGIP) {
				if (_hoops_CCHIS < _hoops_PCHIS[3][0]) _hoops_CCHIS = _hoops_PCHIS[3][0];
				if (_hoops_SCHIS > _hoops_PCHIS[3][1]) _hoops_SCHIS = _hoops_PCHIS[3][1];
				if (_hoops_GSHIS < _hoops_PCHIS[3][1]) _hoops_GSHIS = _hoops_PCHIS[3][1];
			}
		}
		else /* _hoops_RPP (_hoops_SGHSP) */ {
			_hoops_CCHIS = _hoops_PCHIS[3][0];
			_hoops_SCHIS = _hoops_GSHIS = _hoops_PCHIS[3][1];
		}

		if (_hoops_PSHIS (nr, grid,
										 0.5f * (left + right),
										 0.5f * (bottom + top),
										 &_hoops_PCHIS[4][0], &_hoops_PCHIS[4][1])) {
			if (_hoops_CCHIS < _hoops_PCHIS[4][0])
				if (_hoops_PCHIS[4][0] > _hoops_SHHIS)
					_hoops_CCHIS = _hoops_SHHIS;
				else
					_hoops_CCHIS = _hoops_PCHIS[4][0];

			if (_hoops_SCHIS > _hoops_PCHIS[4][1])
				if (_hoops_GSHIS - _hoops_PCHIS[4][1] > _hoops_SHHIS)
					_hoops_SCHIS = _hoops_GSHIS - _hoops_SHHIS;
				else
					_hoops_SCHIS = _hoops_PCHIS[4][1];
			if (_hoops_GSHIS < _hoops_PCHIS[4][1])
				if (_hoops_PCHIS[4][1] - _hoops_SCHIS > _hoops_SHHIS)
					_hoops_GSHIS = _hoops_SCHIS + _hoops_SHHIS;
				else
					_hoops_GSHIS = _hoops_PCHIS[4][1];
		}

		_hoops_ACIPS = (int)_hoops_CCHIS + 100;
		_hoops_PCIPS = (int)_hoops_SCHIS - 100;				_hoops_PSIGC = (int)_hoops_GSHIS + 100;

		if (grid->count1 < 0) {
			if (_hoops_ACIPS < grid->count1) return;	/* _hoops_CPRAH */

			if (_hoops_ACIPS > -grid->count1) _hoops_ACIPS = -grid->count1;
		}
		else if (grid->count1 > 0) {
			if (_hoops_ACIPS < 0) return;		/* _hoops_CPRAH */

			if (_hoops_ACIPS > grid->count1) _hoops_ACIPS = grid->count1;
		}

		if (grid->count2 < 0) {
			if (_hoops_PSIGC < grid->count2 ||
				_hoops_PCIPS > -grid->count2) return;	/* _hoops_CPRAH */

			if (_hoops_PCIPS < grid->count2) _hoops_PCIPS = grid->count2;
			if (_hoops_PSIGC > -grid->count2) _hoops_PSIGC = -grid->count2;
		}
		else if (grid->count2 > 0) {
			if (_hoops_PSIGC < 0 ||
				_hoops_PCIPS > grid->count2) return;	/* _hoops_CPRAH */

			if (_hoops_PCIPS < 0) _hoops_PCIPS = 0;
			if (_hoops_PSIGC > grid->count2) _hoops_PSIGC = grid->count2;
		}

		_hoops_HSHIS (nr, grid, _hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC);
	}
	else {
		/* _hoops_PIHA _hoops_SHH _hoops_PGI _hoops_PCCP _hoops_PGGS "_hoops_CGGR" _hoops_PGAP _hoops_GHCCP _hoops_RH _hoops_GRPC
		** _hoops_IIGR _hoops_RH _hoops_RAR, _hoops_PAR _hoops_PCCP _hoops_PGGS _hoops_IPPA _hoops_GGAIA _hoops_CCA _hoops_RH _hoops_RAR
		** _hoops_HAGA -- _hoops_CGH _hoops_RASHR _hoops_RGR _hoops_SPHR */


		if (grid->count1 == 0)
			_hoops_ACIPS = 100;
		else if (grid->count1 < 0)
			_hoops_ACIPS = -grid->count1;
		else
			_hoops_ACIPS = grid->count1;

		if (grid->count2 == 0) {
			_hoops_PCIPS = -100;
			_hoops_PSIGC = 100;
		}
		else if (grid->count2 < 0) {
			_hoops_PCIPS = grid->count2;
			_hoops_PSIGC = -grid->count2;
		}
		else {
			_hoops_PCIPS = 0;
			_hoops_PSIGC = grid->count2;
		}

		_hoops_HSHIS (nr, grid, _hoops_ACIPS, _hoops_PCIPS, _hoops_PSIGC);
	}
}






GLOBAL_FUNCTION void HD_Std_3D_Grid (
	Net_Rendition const &		inr,
	Grid const *				grid) {
	Net_Rendition				nr = inr;

	/* _hoops_AHHCP _hoops_III _hoops_CCA _hoops_ISHA */
	nr.Modify()->_hoops_AHP = nr->_hoops_RHP;

	if (ANYBIT (nr->_hoops_RGP, T_PERIMETER_EDGES|_hoops_CRHGP|T_GENERIC_EDGES) &&
		!BIT (nr->_hoops_RGP, T_LINES)) {
		nr->_hoops_RGP |= T_LINES;
	}

	switch (grid->_hoops_APIAA) {
		case _hoops_PPIAA: {
			_hoops_ACHIS (nr, grid);
		}	break;

		case _hoops_SPARP: {
			_hoops_GGIIS (nr, grid);
		}	break;
	}
}

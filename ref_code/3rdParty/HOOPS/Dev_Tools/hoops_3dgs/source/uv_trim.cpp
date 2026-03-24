/*
 * Copyright (c) 2001 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: obf_tmp.txt 1.61 2011-01-14 22:31:08 covey Exp $
 */



#include "hoops.h"
#ifndef _hoops_GSPIR

#include "database.h"
#include "hi_proto.h"
#include "phedron.h"
#include "hpserror.h"
#include <limits.h>
#include "adt.h"


#define _hoops_RAAHR 1.0e-5
#define _hoops_IACIR (1e10f)


GLOBAL_FUNCTION void HI_Enumerate_Region_Set_Edges (
		UV_Region_Set const *set,
		int alter *count,
		UV_Edge alter ***_hoops_GRCPR) 
{
	UV_Region *		region;
	UV_Edge **		next;
	int					tmp = 0;

	*count = tmp = 0;
	*_hoops_GRCPR = null;

	if (set == null || set->regions == null)
		return;

	/* _hoops_SRS _hoops_RPR _hoops_RSH _hoops_GSGS _hoops_SR _hoops_GRS _hoops_RRP */
	region = set->regions;
	do {
		UV_Edge *	edge = region->_hoops_GRCPR;

		do {
			++tmp;
		} while ((edge = edge->next) != region->_hoops_GRCPR);
	} while ((region = region->next) != null);

	/* _hoops_HA _hoops_CCPP _hoops_GC */
	ALLOC_ARRAY (next, tmp, UV_Edge alter *);	
	*count = tmp;
	*_hoops_GRCPR = next;

	/* _hoops_PPR _hoops_PRIA _hoops_RH _hoops_SPPR */
	region = set->regions;
	do {
		UV_Edge *	edge = region->_hoops_GRCPR;

		do {
			*next++ = edge;
		} while ((edge = edge->next) != region->_hoops_GRCPR);
	} while ((region = region->next) != null);
}


#if 0
int _hoops_SGIRGR (UV_Region *r) {
	int i = 0;
	UV_Edge *edge;

	edge = r->_hoops_GRCPR;
	do {
		if (i > 100)
			return 0;
		i++;
	} while ((edge = edge->next) != r->_hoops_GRCPR);	
	return 1;
}

int _hoops_GRIRGR (UV_Region_Set alter *set)
{
	int _hoops_HPIS = 1;
	HVHash *_hoops_GCAH;
	UV_Region *region = set->regions;
	UV_Edge *edge;

	_hoops_GCAH = HI_New_VHash(500);
	do {
		edge = region->_hoops_GRCPR;
		do {
			if (HI_VHash_Lookup_Item(_hoops_GCAH, edge, null) == VHASH_STATUS_SUCCESS)
				_hoops_HPIS = 0;
			HI_VHash_Insert_Item (_hoops_GCAH, edge, region);
			if (edge->_hoops_RSSCC) {
				if (edge->_hoops_RSSCC->_hoops_RSSCC != edge)
					_hoops_HPIS = 0;
			}
		} while ((edge = edge->next) != region->_hoops_GRCPR); 
		if (!_hoops_SGIRGR (region))
			_hoops_HPIS = 0;
	} while ((region = region->next) != null);
	HI_Delete_VHash(_hoops_GCAH);
	return _hoops_HPIS;
}


int _hoops_RRIRGR (
		UV_Region_Set alter *set,
		UV_Edge *a,
		UV_Edge *b,
		UV_Edge *c,
		UV_Edge *d,
		UV_Edge *e,
		UV_Edge *f) 
{
	float _hoops_ARGCR;

	_hoops_ARGCR = (0.5f * (set->points[a->index].u + set->points[b->index].u)) - set->points[d->index].u;
	if (!(-_hoops_RAAHR < _hoops_ARGCR && _hoops_ARGCR < _hoops_RAAHR)) 
		return 0;
	_hoops_ARGCR = (0.5f * (set->points[a->index].v + set->points[b->index].v)) - set->points[d->index].v;
	if (!(-_hoops_RAAHR < _hoops_ARGCR && _hoops_ARGCR < _hoops_RAAHR)) 
		return 0;
	_hoops_ARGCR = (0.5f * (set->points[b->index].u + set->points[c->index].u)) - set->points[e->index].u;
	if (!(-_hoops_RAAHR < _hoops_ARGCR && _hoops_ARGCR < _hoops_RAAHR)) 
		return 0;
	_hoops_ARGCR = (0.5f * (set->points[b->index].v + set->points[c->index].v)) - set->points[e->index].v;
	if (!(-_hoops_RAAHR < _hoops_ARGCR && _hoops_ARGCR < _hoops_RAAHR)) 
		return 0;
	_hoops_ARGCR = (0.5f * (set->points[c->index].u + set->points[a->index].u)) - set->points[f->index].u;
	if (!(-_hoops_RAAHR < _hoops_ARGCR && _hoops_ARGCR < _hoops_RAAHR)) 
		return 0;
	_hoops_ARGCR = (0.5f * (set->points[c->index].v + set->points[a->index].v)) - set->points[f->index].v;
	if (!(-_hoops_RAAHR < _hoops_ARGCR && _hoops_ARGCR < _hoops_RAAHR)) 
		return 0;
	return 1;
}


#endif


local void _hoops_ARIRGR (
	UV_Region_Set *	set,
	UV_Region *		region) 
{
	UV_Edge *		test;
	UV_Point *		here;

	test = region->_hoops_GRCPR;
	here = &set->points[test->index];
	region->_hoops_RCHS.min.u =
		region->_hoops_RCHS.max.u = here->u;
	region->_hoops_RCHS.min.v =
		region->_hoops_RCHS.max.v = here->v;
	test = test->next;
	do {
		here = &set->points[test->index];
		if (here->u < region->_hoops_RCHS.min.u)
			region->_hoops_RCHS.min.u = here->u;
		else if (here->u > region->_hoops_RCHS.max.u)
			region->_hoops_RCHS.max.u = here->u;
		if (here->v < region->_hoops_RCHS.min.v)
			region->_hoops_RCHS.min.v = here->v;
		else if (here->v > region->_hoops_RCHS.max.v)
			region->_hoops_RCHS.max.v = here->v;
	} while ((test = test->next) != region->_hoops_GRCPR);
}

local void _hoops_PRIRGR (
	UV_Region_Set alter *	set,
	UV_Edge alter *			edge,
	int							start,
	int							end,
	int							_hoops_HRIRGR) {
	float						length;

	edge->line.a = set->points[start].v - set->points[end].v;
	edge->line.b = set->points[end].u - set->points[start].u;

	length = _hoops_SGIHR (edge->line.a * edge->line.a	+  edge->line.b * edge->line.b);
	if (length > 0.0) {
		length = 1.0f / length;
		edge->line.a *= length;
		edge->line.b *= length;
	}

	edge->line.c = -(edge->line.a * set->points[start].u + edge->line.b * set->points[start].v);
	if (edge->line.a * set->points[_hoops_HRIRGR].u +
		 edge->line.b * set->points[_hoops_HRIRGR].v +
		  edge->line.c < 0.0f) {
		edge->line.a = -edge->line.a;
		edge->line.b = -edge->line.b;
		edge->line.c = -edge->line.c;
	}
}

local void _hoops_IRIRGR (
	UV_Region_Set alter *	set,
	UV_Edge alter *			edge) {
	UV_Region	*_hoops_HIHHA, *_hoops_PIAIA;
	UV_Edge		*a, *b, *c, *d, *e, *f;

	a = edge;
	b = a->next;
	c = b->next;

	if (c->next == a)
		return;			/* _hoops_AIAH _hoops_GGR _hoops_AGSRH _hoops_SRSGR */

	/* _hoops_PPIP _hoops_SRS _hoops_ISPH, _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_SHSGH _hoops_CCA _hoops_ISHA _hoops_IRS */
	_hoops_HIHHA = a->region;
	_hoops_HIHHA->_hoops_GRCPR = a;

	/*
	 * _hoops_GCHGA _hoops_ISHA _hoops_GSGGR (_hoops_PPR _hoops_PCSA _hoops_CGCPH _hoops_GAR _hoops_GHGP) _hoops_CCGR _hoops_SR _hoops_HS:
	 *							 
	 *		_hoops_ARPP	  /^		   
	 *				/  |					 _hoops_HII _hoops_PGAP _hoops_SR _hoops_IRHH _hoops_RGR
	 *			  /_hoops_RCSR   |				/^	 
	 *			...	   |	  _hoops_RAS	  / ||
	 *			...	   |			/_hoops_RCSR _hoops_RCHP||
	 *			 |	  _hoops_IRS|		  ...  / |
	 *			 |_hoops_GHGP	   |		  ... |_hoops_IAS |
	 *			 _hoops_HPPC	   |		   |_hoops_GHGP | _hoops_IRS|
	 *			  \_hoops_GSGGR   |		   | /	 |
	 *				\  |		   |/	 |
	 *				  \|		   _hoops_HPPC	 |
	 *								\_hoops_GSGGR	 |
	 *								  \	 |
	 *									\|
	 * 
	 * _hoops_SR _hoops_PAH _hoops_AACC _hoops_HII _hoops_PGI (_hoops_HSPP _hoops_IIGR _hoops_IRS _hoops_IS _hoops_RSGR _hoops_IIGR _hoops_RCSR) _hoops_PAR (_hoops_RSGR _hoops_IIGR _hoops_IRS _hoops_IS _hoops_HSPP _hoops_IIGR _hoops_GSGGR)
	 */

	/* _hoops_CCAH _hoops_ISPH */
	ALLOC (_hoops_PIAIA, UV_Region);
	_hoops_PIAIA->next = set->regions;
	set->regions = _hoops_PIAIA;
	_hoops_PIAIA->_hoops_IHRRH = _hoops_HIHHA->_hoops_IHRRH;

	do {
		d = c;
		d->region = _hoops_PIAIA; /* _hoops_HCR _hoops_ARPP _hoops_RH _hoops_HACH "_hoops_GSGGR" _hoops_GRS _hoops_SHH _hoops_ISPH 2 */
		c = c->next;
	} _hoops_RGGA (c->next == a);
	_hoops_PIAIA->_hoops_GRCPR = d;

	/* _hoops_CCAH _hoops_ISHA _hoops_PSAI _hoops_IAS & _hoops_RCHP _hoops_SGS _hoops_GIAH _hoops_RH 2 _hoops_PGHH */
	ALLOC (e, UV_Edge);
	e->region = _hoops_HIHHA;
	e->priority = -1.0f;

	ALLOC (f, UV_Edge);
	f->region = _hoops_PIAIA;
	f->priority = -1.0f;

	e->_hoops_RSSCC = f;
	f->_hoops_RSSCC = e;


	e->index = b->index;
	f->index = c->index;
	f->next = b;
	a->next = e;
	e->next = c;
	d->next = f;
	b->region = _hoops_PIAIA;
	_hoops_PRIRGR (set, e, e->index, f->index, a->index);

	f->line.a = -e->line.a;
	f->line.b = -e->line.b;
	f->line.c = -e->line.c;

	_hoops_ARIRGR (set, _hoops_HIHHA);
	_hoops_ARIRGR (set, _hoops_PIAIA);

	_hoops_HIHHA->_hoops_IHRRH = false;
}



GLOBAL_FUNCTION void HI_Split_Region_Set_Edge (
		UV_Region_Set alter *set,
		UV_Edge alter *edge,
		int alter *count,
		UV_Edge alter ***_hoops_GRCPR)
{
	UV_Edge alter *	_hoops_CRIRGR[32];
	int					_hoops_SRIRGR = 0;
	int		_hoops_GAIRGR = set->point_count;
	float	_hoops_RAIRGR = 0.5f * (set->points[edge->index].u + set->points[edge->next->index].u);
	float	_hoops_AAIRGR = 0.5f * (set->points[edge->index].v + set->points[edge->next->index].v);
	UV_Region	*_hoops_HIHHA, *_hoops_PIAIA;
	UV_Edge		*a, *b, *c, *d, *e, *f;

	/* _hoops_PRIA _hoops_CCAH _hoops_PPSR (_hoops_PCCS _hoops_RSSA _hoops_CRPR _hoops_RPP _hoops_SIGR) */
	if (set->point_count == set->_hoops_CAHI) {
		UV_Point *	new_points;

		ALLOC_ARRAY (new_points, set->_hoops_CAHI+16, UV_Point);
		_hoops_AIGA (set->points, set->point_count, UV_Point, new_points);
		FREE_ARRAY (set->points, set->_hoops_CAHI, UV_Point);
		set->points = new_points;
		set->_hoops_CAHI += 16;
	}
	set->points[_hoops_GAIRGR].u = _hoops_RAIRGR;
	set->points[_hoops_GAIRGR].v = _hoops_AAIRGR;
	++set->point_count;

	/* _hoops_IAS-_hoops_RCHP-_hoops_IRS _hoops_CHR _hoops_SPPR _hoops_IIGR _hoops_SCPH _hoops_PAPR _hoops_GAR _hoops_ISPH _hoops_PAIRGR.
	 * _hoops_IAS _hoops_HRGR _hoops_HHGP _hoops_HPGR _hoops_RRSSR, _hoops_RCSR _hoops_HRGR _hoops_IRS _hoops_CCAH _hoops_ISHA _hoops_APRAA _hoops_RH _hoops_IRS-_hoops_PPAP _hoops_GPSPR, _hoops_IAS _hoops_RHCHR _hoops_RH _hoops_RCHP-_hoops_PPAP _hoops_GPSPR
	 *	_hoops_RCHP _hoops_PPAP _hoops_CAHC _hoops_CCA _hoops_CCAH _hoops_ISHA _hoops_GHGP, _hoops_PAIRGR _hoops_HRGR _hoops_PSCR _hoops_GHGP-_hoops_IAS-_hoops_RCHP,
	 *	_hoops_IRS _hoops_PPAP _hoops_CAHC _hoops_CCA _hoops_CCAH _hoops_ISHA _hoops_GSGGR, _hoops_CCAH _hoops_ISPH _hoops_HAIRGR _hoops_HRGR _hoops_PSCR _hoops_IRS-_hoops_RCSR-_hoops_GSGGR
	 *
	 * _hoops_RPP _hoops_RH _hoops_GIGR _hoops_ISHA _hoops_SSCP _hoops_PCCP _hoops_GPPPA _hoops_ISHA, _hoops_RH _hoops_PIRPR _hoops_HRGR _hoops_PSHSC _hoops_GPP _hoops_RGCI _hoops_ISPH (_hoops_GRRSC _hoops_GAR _hoops_IAS' _hoops_AHI)
	 *
	 *				  /|\						  /|\
	 *				/  |  \						/  |  \
	 *			  /_hoops_RCHP   |	\				  /	  _hoops_IAS|_hoops_RCSR'	\
	 *			/	   |	_hoops_IRS'\				/_hoops_RCHP 1   | 2' _hoops_IRS'\
	 *		  /		   |		\		  /		_hoops_GHGP  |  _hoops_GSGGR'	\
	 *		 <	 1	  _hoops_IAS|   1'	 >		 <---------+--------->
	 *		  \		   |_hoops_IAS'		/		  \		_hoops_GSGGR  |  _hoops_GHGP'	/
	 *			\	   |	_hoops_RCHP'/				\_hoops_IRS 2   | 1' _hoops_RCHP'/
	 *			  \_hoops_IRS   |	/				  \	  _hoops_RCSR|_hoops_IAS'	/
	 *				\  |  /						\  |  /
	 *				  \|/						  \|/
	 *
	 */
	/* _hoops_PPIP _hoops_APHR _hoops_SPPR */
	e = edge;
	f = e->next;
	a = f->next;

	if (a->next != e) {
		_hoops_IRIRGR (set, e);
		f = e->next;
		a = f->next;
	}

	/* _hoops_PPIP _hoops_SRS _hoops_ISPH, _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_SHSGH _hoops_CCA _hoops_ISHA _hoops_IAS */
	_hoops_HIHHA = e->region;
	_hoops_HIHHA->_hoops_GRCPR = e;


	/* _hoops_CCAH _hoops_ISPH */
	ALLOC (_hoops_PIAIA, UV_Region);
	_hoops_PIAIA->next = set->regions;
	set->regions = _hoops_PIAIA;
	_hoops_PIAIA->_hoops_IHRRH = false;

	/* _hoops_HHGP _hoops_ISHA _hoops_IAS _hoops_CRGR _hoops_RCSR _hoops_PPR _hoops_IAS */
	ALLOC (b, UV_Edge);
	if ((b->_hoops_RSSCC = e->_hoops_RSSCC) != null)
		b->_hoops_RSSCC->_hoops_RSSCC = b;	/* _hoops_RH _hoops_GPPPA _hoops_ISHA _hoops_GRS _hoops_SHH _hoops_HHGP _hoops_CAPP */
	b->index = e->index;
	b->region = _hoops_PIAIA;
	b->priority = -1.0f;
	b->line.a = edge->line.a;
	b->line.b = edge->line.b;
	b->line.c = edge->line.c;

	e->index = _hoops_GAIRGR;

	/* _hoops_CCAH _hoops_ISHA _hoops_PSAI _hoops_GSGGR & _hoops_GHGP _hoops_SGS _hoops_GIAH _hoops_RH 2 _hoops_PGHH */
	ALLOC (c, UV_Edge);
	c->_hoops_RSSCC = null;
	c->index = _hoops_GAIRGR;
	c->region = _hoops_PIAIA;
	c->priority = -1.0f;
	_hoops_PRIRGR (set, c, _hoops_GAIRGR, a->index, b->index);

	ALLOC (d, UV_Edge);
	d->_hoops_RSSCC = null;
	d->index = a->index;
	d->region = _hoops_HIHHA;
	d->priority = -1.0f;
	d->line.a = -c->line.a;
	d->line.b = -c->line.b;
	d->line.c = -c->line.c;

	c->_hoops_RSSCC = d;
	d->_hoops_RSSCC = c;

	/* _hoops_AGGAR _hoops_ISHA _hoops_RGHS _hoops_GPP _hoops_ARGR _hoops_PGHH */
	a->next = b;
	b->next = c;
	c->next = a;
	_hoops_PIAIA->_hoops_GRCPR = a;
	a->region = _hoops_PIAIA;

	d->next = e;
	f->next = d;

	_hoops_ARIRGR (set, _hoops_HIHHA);
	_hoops_ARIRGR (set, _hoops_PIAIA);

	/* _hoops_PRIA _hoops_SPPR _hoops_RGISH _hoops_HPP _hoops_RH _hoops_HHGP */
	_hoops_CRIRGR[_hoops_SRIRGR++] = a;
	_hoops_CRIRGR[_hoops_SRIRGR++] = b;
	_hoops_CRIRGR[_hoops_SRIRGR++] = c;
	_hoops_CRIRGR[_hoops_SRIRGR++] = d;
	_hoops_CRIRGR[_hoops_SRIRGR++] = e;
	_hoops_CRIRGR[_hoops_SRIRGR++] = f;
	if (a->_hoops_RSSCC != null)
		_hoops_CRIRGR[_hoops_SRIRGR++] = a;
	if (f->_hoops_RSSCC != null)
		_hoops_CRIRGR[_hoops_SRIRGR++] = f;

	if (edge->_hoops_RSSCC != null) {
		/* _hoops_APHS _hoops_RH _hoops_CAIH _hoops_GPP _hoops_RH _hoops_RII _hoops_PPAP, _hoops_CSSHH _hoops_SHPH _hoops_IS _hoops_GPPPA _hoops_AGGAR _hoops_PRCA */

		/* _hoops_PPIP _hoops_APHR _hoops_SPPR */
		e = edge->_hoops_RSSCC;
		f = e->next;
		a = f->next;

		if (a->next != e) {
			_hoops_IRIRGR (set, e);
			f = e->next;
			a = f->next;
		}

		/* _hoops_PPIP _hoops_SRS _hoops_ISPH, _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_SHSGH _hoops_CCA _hoops_ISHA _hoops_IAS */
		_hoops_HIHHA = e->region;
		_hoops_HIHHA->_hoops_GRCPR = e;


		/* _hoops_CCAH _hoops_ISPH */
		ALLOC (_hoops_PIAIA, UV_Region);
		_hoops_PIAIA->next = set->regions;
		set->regions = _hoops_PIAIA;
		_hoops_PIAIA->_hoops_IHRRH = false;

		/* _hoops_HHGP _hoops_ISHA _hoops_IAS _hoops_CRGR _hoops_RCSR _hoops_PPR _hoops_IAS */
		ALLOC (b, UV_Edge);
		b->_hoops_RSSCC = edge;	 /* _hoops_HAGH _hoops_HII _hoops_SRS _hoops_AGIR! */
		b->index = e->index;
		b->region = _hoops_PIAIA;
		b->priority = -1.0f;
		b->line.a = edge->line.a;
		b->line.b = edge->line.b;
		b->line.c = edge->line.c;

		edge->_hoops_RSSCC = b; /* _hoops_GACC _hoops_HAGH */
		e->index = _hoops_GAIRGR;

		/* _hoops_CCAH _hoops_ISHA _hoops_PSAI _hoops_GSGGR & _hoops_GHGP _hoops_SGS _hoops_GIAH _hoops_RH 2 _hoops_PGHH */
		ALLOC (c, UV_Edge);
		c->_hoops_RSSCC = null;
		c->index = _hoops_GAIRGR;
		c->region = _hoops_PIAIA;
		c->priority = -1.0f;
		_hoops_PRIRGR (set, c, _hoops_GAIRGR, a->index, b->index);

		ALLOC (d, UV_Edge);
		d->_hoops_RSSCC = null;
		d->index = a->index;
		d->region = _hoops_HIHHA;
		d->priority = -1.0f;
		d->line.a = -c->line.a;
		d->line.b = -c->line.b;
		d->line.c = -c->line.c;

		c->_hoops_RSSCC = d;
		d->_hoops_RSSCC = c;

		/* _hoops_AGGAR _hoops_ISHA _hoops_RGHS _hoops_GPP _hoops_ARGR _hoops_PGHH */
		a->next = b;
		b->next = c;
		c->next = a;
		_hoops_PIAIA->_hoops_GRCPR = a;
		a->region = _hoops_PIAIA;

		d->next = e;
		f->next = d;

		_hoops_ARIRGR (set, _hoops_HIHHA);
		_hoops_ARIRGR (set, _hoops_PIAIA);

		/* _hoops_PRIA _hoops_SPPR _hoops_RGISH _hoops_HPP _hoops_RH _hoops_HHGP */
		_hoops_CRIRGR[_hoops_SRIRGR++] = a;
		_hoops_CRIRGR[_hoops_SRIRGR++] = b;
		_hoops_CRIRGR[_hoops_SRIRGR++] = c;
		_hoops_CRIRGR[_hoops_SRIRGR++] = d;
		_hoops_CRIRGR[_hoops_SRIRGR++] = e;
		_hoops_CRIRGR[_hoops_SRIRGR++] = f;
		if (a->_hoops_RSSCC != null)
			_hoops_CRIRGR[_hoops_SRIRGR++] = a->_hoops_RSSCC;
		if (f->_hoops_RSSCC != null)
			_hoops_CRIRGR[_hoops_SRIRGR++] = f->_hoops_RSSCC;

	}

	if (count != null)
		*count = _hoops_SRIRGR;
	if (_hoops_GRCPR != null) {
		ALLOC_ARRAY (*_hoops_GRCPR, _hoops_SRIRGR, UV_Edge alter *);	   
		_hoops_AIGA (_hoops_CRIRGR, _hoops_SRIRGR, UV_Edge alter *, *_hoops_GRCPR);
	}
}


local float _hoops_IAIRGR (
		UV_Region_Set alter *set,
		UV_Edge *edge)
{
	float _hoops_SAIAR;

	UNREFERENCED(set);
	
	_hoops_SAIAR = (edge->line.a * edge->next->line.b) - (edge->line.b * edge->next->line.a);
	if (_hoops_SAIAR < 0)
		_hoops_SAIAR = -_hoops_SAIAR;
	return _hoops_SAIAR;
}


/* _hoops_ISPH _hoops_HRGR _hoops_SHHA _hoops_IS _hoops_SHH _hoops_SGCS, _hoops_HIH _hoops_GHCA _hoops_HS _hoops_GARAA _hoops_SPPR */
GLOBAL_FUNCTION void HI_Triangulate_Region (
		UV_Region_Set alter *set,
		UV_Region alter *region) 
{
	UV_Edge *edge, *start;
	float _hoops_SAIAR;

	start = edge = region->_hoops_GRCPR;
	/* _hoops_RSIH _hoops_RIARR _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_IRS _hoops_SCPH */
	if (edge->next->next->next == edge)
		return;
	
	/* _hoops_SHH _hoops_RCRR _hoops_IS _hoops_HHGP _hoops_GARAA _hoops_SPPR */
	do {
		_hoops_SAIAR = _hoops_IAIRGR (set, edge);
		while (_hoops_SAIAR < _hoops_RAAHR) {
			start = edge->next;
			_hoops_IRIRGR (set, edge);
			edge = start;
			_hoops_SAIAR = _hoops_IAIRGR (set, edge);
		}
	} while ((edge = edge->next) != start);
	/* _hoops_HA _hoops_SAHR _hoops_CAIRGR _hoops_HRHH _hoops_PCPA'_hoops_GRI _hoops_RAAP */
	edge = start->next->next->next;
	while (edge != start) {
		_hoops_IRIRGR (set, edge->next);
		edge = edge->next;
	}
}




/*
 *				^--------->						   ^--------->					
 *			 |	|	 _hoops_RCSR							|  |	_hoops_RCSR						
 *			 |	|							  _hoops_SAIRGR|  |_hoops_GHGP							
 *	 _hoops_HPIH |	|					   _hoops_HPIH	|  |							
 *	 _hoops_ISPH	 |	|_hoops_IRS	_hoops_ISPH			   _hoops_ISPH	_hoops_HPPC  ^   _hoops_ISPH				   
 *			 |	|								|  |							
 *			 |	|							  _hoops_GPIRGR|  |_hoops_IRS							
 *			 |	|								|  |							
 *		<----_hoops_HPPC							   <----_hoops_HPPC								
 *																   
 *			 _hoops_ARPP								_hoops_RAS		
 */														 
local UV_Edge *_hoops_RPIRGR (
		UV_Region_Set alter *set,
		UV_Edge alter *a,
		UV_Edge alter *b)
{
	UV_Edge alter *d;
	float u, v;

	ASSERT (a->next == b);
	/* _hoops_PRIA _hoops_CCAH _hoops_RSSA (_hoops_PCCS _hoops_RSSA _hoops_CRPR _hoops_RPP _hoops_SIGR) */
	if (set->point_count+1 > set->_hoops_CAHI) {
		UV_Point *	new_points;

		ALLOC_ARRAY_CACHED (new_points, set->_hoops_CAHI+64, UV_Point);
		_hoops_AIGA (set->points, set->point_count, UV_Point, new_points);
		FREE_ARRAY (set->points, set->_hoops_CAHI, UV_Point);
		set->points = new_points;
		set->_hoops_CAHI += 64;
	}
	u = 0.5f * (set->points[a->index].u + set->points[b->index].u);
	v = 0.5f * (set->points[a->index].v + set->points[b->index].v);
	set->points[set->point_count].u = u;
	set->points[set->point_count].v = v;

	ALLOC (d, UV_Edge);
	d->_hoops_RSSCC = null; /* _hoops_IS _hoops_SHH _hoops_PIISR _hoops_GGR _hoops_SPHR (_hoops_GAAP) */
	d->index =	set->point_count;
	d->region = a->region;
	d->priority = -1.0f;
	d->line.a = a->line.a;
	d->line.b = a->line.b;
	d->line.c = a->line.c;
	d->next = b;
	a->next = d;
	set->point_count++;

	/* _hoops_HHGP _hoops_GII _hoops_GPPPA _hoops_ISHA */
	if (a->_hoops_RSSCC != null) {
		/* _hoops_SR'_hoops_GCPP _hoops_GRPHA _hoops_GPP _hoops_RH _hoops_ISHA _hoops_IPIH _hoops_APIRGR _hoops_GGR _hoops_IRS->_hoops_GPPPA
		 * _hoops_IS _hoops_IRHH _hoops_SCH _hoops_PPIRGR _hoops_GHGP.	 _hoops_GISA _hoops_IRS _hoops_CCAH _hoops_ISHA _hoops_IH _hoops_IRS _hoops_IS _hoops_PPIRGR */
		UV_Edge *		_hoops_HPIRGR = a->_hoops_RSSCC;
		UV_Edge *		_hoops_IPIRGR;

		ALLOC (_hoops_IPIRGR, UV_Edge);
		_hoops_IPIRGR->index = a->next->index;
		_hoops_IPIRGR->region = _hoops_HPIRGR->region;
		_hoops_IPIRGR->priority = -1.0f;
		_hoops_IPIRGR->line.a = _hoops_HPIRGR->line.a;
		_hoops_IPIRGR->line.b = _hoops_HPIRGR->line.b;
		_hoops_IPIRGR->line.c = _hoops_HPIRGR->line.c;
		_hoops_IPIRGR->next = _hoops_HPIRGR->next;
		_hoops_HPIRGR->next = _hoops_IPIRGR;
		_hoops_HPIRGR->_hoops_RSSCC = d;
		d->_hoops_RSSCC = _hoops_HPIRGR;
		_hoops_IPIRGR->_hoops_RSSCC = a;
		a->_hoops_RSSCC = _hoops_IPIRGR;
	}
	return d;
}


local UV_Edge *_hoops_CPIRGR (
		UV_Region_Set alter *set,
		UV_Edge alter *a,
		UV_Edge alter *b)
{
	UV_Edge alter *_hoops_PIHGA, *edge;
	float u, v, _hoops_ISAHH, _hoops_APCGH;
	float dist, _hoops_HARPA = _hoops_IACIR;

	ASSERT (a->next != b);

	/* _hoops_RSIH _hoops_PGPCR _hoops_RPP _hoops_RH _hoops_ISHA _hoops_SSCP _hoops_RPII _hoops_HHGP _hoops_GPCPR _hoops_ARR */
	if (a->next->next == b)
		return a->next;

	u = 0.5f * (set->points[a->index].u + set->points[b->index].u);
	v = 0.5f * (set->points[a->index].v + set->points[b->index].v);
	_hoops_PIHGA = null;
	for (edge = a->next ; edge != b ; edge = edge->next) {
		_hoops_ISAHH = set->points[edge->index].u;
		_hoops_APCGH = set->points[edge->index].v;
		dist = (_hoops_ISAHH-u)*(_hoops_ISAHH-u) + (_hoops_APCGH-v)*(_hoops_APCGH-v);
		if (dist < _hoops_HARPA) {
			_hoops_PIHGA = edge;
			_hoops_HARPA = dist;
		}
	}
	return _hoops_PIHGA;
}


local void _hoops_SPIRGR (
		UV_Region_Set alter *set,
		UV_Edge alter *a,
		UV_Edge alter *b,
		UV_Edge alter *c,
		UV_Edge alter *d,
		UV_Edge alter *e,
		UV_Edge alter *f,
		int alter *_hoops_GHIRGR,
		UV_Edge alter ***_hoops_RHIRGR) 
{
	UV_Region *_hoops_HIHHA, *_hoops_PIAIA, *_hoops_SRPSH;
	UV_Edge alter *g, *h, *i, *_hoops_AHIRGR, *_hoops_RGCPC, *_hoops_ACHPS;
	UV_Edge alter *_hoops_PHIRGR, *_hoops_HHIRGR, *_hoops_HRHHH, *edge;

	/* _hoops_CAHP _hoops_SPPR & _hoops_SRSGR _hoops_RPIA _hoops_HIPH */
	ALLOC (g, UV_Edge);
	g->_hoops_RSSCC = null;
	g->index = d->index;
	g->region = null;
	g->priority = -1.0f;
	_hoops_PRIRGR (set, g, d->index, f->index, a->index);

	ALLOC (h, UV_Edge);
	h->_hoops_RSSCC = null;
	h->index = e->index;
	h->region = null;
	h->priority = -1.0f;
	_hoops_PRIRGR (set, h, e->index, d->index, b->index);

	ALLOC (i, UV_Edge);
	i->_hoops_RSSCC = null;
	i->index = f->index;
	i->region = null;
	i->priority = -1.0f;
	_hoops_PRIRGR (set, i, f->index, e->index, c->index);

	g->next = f;
	h->next = d;
	i->next = e;
	_hoops_PHIRGR = a;
	while (_hoops_PHIRGR->next != d)
		_hoops_PHIRGR = _hoops_PHIRGR->next;
	_hoops_HHIRGR = b;
	while (_hoops_HHIRGR->next != e)
		_hoops_HHIRGR = _hoops_HHIRGR->next;
	_hoops_HRHHH = c;
	while (_hoops_HRHHH->next != f)
		_hoops_HRHHH = _hoops_HRHHH->next;
	_hoops_PHIRGR->next = g;
	_hoops_HHIRGR->next = h;
	_hoops_HRHHH->next = i;
	g->region = a->region;	  /* _hoops_IRS _hoops_IHIRGR _hoops_GIGR _hoops_ISPH */
	a->region->_hoops_GRCPR = a;
	_hoops_ARIRGR (set, a->region);

	ALLOC (_hoops_HIHHA, UV_Region);
	_hoops_HIHHA->next = set->regions;
	set->regions = _hoops_HIHHA;
	_hoops_HIHHA->_hoops_IHRRH = false;
	_hoops_HIHHA->_hoops_GRCPR = b;
	edge = b;
	do {
		edge->region = _hoops_HIHHA;
	} while ((edge = edge->next) != b);
	_hoops_ARIRGR (set, _hoops_HIHHA);

	ALLOC (_hoops_PIAIA, UV_Region);
	_hoops_PIAIA->next = set->regions;
	set->regions = _hoops_PIAIA;
	_hoops_PIAIA->_hoops_IHRRH = false;
	_hoops_PIAIA->_hoops_GRCPR = c;
	edge = c;
	do {
		edge->region = _hoops_PIAIA;
	} while ((edge = edge->next) != c);
	_hoops_ARIRGR (set, _hoops_PIAIA);

	/* _hoops_CAHP _hoops_SPPR & _hoops_SRSGR _hoops_RHCH _hoops_SCPH */
	ALLOC (_hoops_AHIRGR, UV_Edge);
	_hoops_AHIRGR->index = f->index;
	_hoops_AHIRGR->region = null;
	_hoops_AHIRGR->priority = -1.0f;
	_hoops_AHIRGR->line.a = -g->line.a;
	_hoops_AHIRGR->line.b = -g->line.b;
	_hoops_AHIRGR->line.c = -g->line.c;
	_hoops_AHIRGR->_hoops_RSSCC = g;
	g->_hoops_RSSCC = _hoops_AHIRGR;

	ALLOC (_hoops_RGCPC, UV_Edge);
	_hoops_RGCPC->index = d->index;
	_hoops_RGCPC->region = null;
	_hoops_RGCPC->priority = -1.0f;
	_hoops_RGCPC->line.a = -h->line.a;
	_hoops_RGCPC->line.b = -h->line.b;
	_hoops_RGCPC->line.c = -h->line.c;
	_hoops_RGCPC->_hoops_RSSCC = h;
	h->_hoops_RSSCC = _hoops_RGCPC;

	ALLOC (_hoops_ACHPS, UV_Edge);
	_hoops_ACHPS->index = e->index;
	_hoops_ACHPS->region = null;
	_hoops_ACHPS->priority = -1.0f;
	_hoops_ACHPS->line.a = -i->line.a;
	_hoops_ACHPS->line.b = -i->line.b;
	_hoops_ACHPS->line.c = -i->line.c;
	_hoops_ACHPS->_hoops_RSSCC = i;
	i->_hoops_RSSCC = _hoops_ACHPS;

	_hoops_AHIRGR->next = _hoops_RGCPC;
	_hoops_RGCPC->next = _hoops_ACHPS;
	_hoops_ACHPS->next = _hoops_AHIRGR;

	ALLOC (_hoops_SRPSH, UV_Region);
	_hoops_SRPSH->next = set->regions;
	set->regions = _hoops_SRPSH;
	_hoops_SRPSH->_hoops_IHRRH = false;
	_hoops_SRPSH->_hoops_GRCPR = _hoops_AHIRGR;
	_hoops_AHIRGR->region = _hoops_RGCPC->region = _hoops_ACHPS->region = _hoops_SRPSH;
	_hoops_ARIRGR(set, _hoops_SRPSH);

	if (_hoops_GHIRGR != null)
		*_hoops_GHIRGR = 6;
	if (_hoops_RHIRGR != null) {
		UV_Edge **temp;

		ALLOC_ARRAY (temp, 6, UV_Edge *);	
		temp[0] = g;
		temp[1] = h;
		temp[2] = i;
		temp[3] = _hoops_AHIRGR;
		temp[4] = _hoops_RGCPC;
		temp[5] = _hoops_ACHPS;
		*_hoops_RHIRGR = temp;
	}

} /* _hoops_RSGR _hoops_API _hoops_CHIRGR */


/* _hoops_SSS _hoops_RH 3 _hoops_CSPHH _hoops_GAPHS _hoops_IIGR _hoops_IRS _hoops_ISPH.
 * _hoops_GASA: _hoops_SHIRGR, _hoops_SR _hoops_CHR _hoops_CPSA _hoops_IARCC _hoops_IIH _hoops_IS _hoops_SHH _hoops_GPCPR 3 _hoops_GRAA-_hoops_AHHR _hoops_GAPHS _hoops_GGR _hoops_RGR _hoops_ISPH. 
 * _hoops_GHAP _hoops_GIIRGR _hoops_SGS _hoops_SPAAR _hoops_RH 3 _hoops_AAH _hoops_CSAP _hoops_PCIIS _hoops_HSAR _hoops_IPAC _hoops_ACSRR _hoops_CRPHH _hoops_GPSGA, _hoops_PHRI. 
 */
GLOBAL_FUNCTION void HI_Get_UV_Region_Triangle (
		UV_Region_Set *set,
		UV_Region *region,
		UV_Edge alter **a,
		UV_Edge alter **b,
		UV_Edge alter **c)
{
	UV_Edge *edge, *_hoops_RIIRGR[3];
	int i, j, k;
	float _hoops_SAIAR, _hoops_AIIRGR[3];
   
	edge = region->_hoops_GRCPR;
	if (edge->next->next->next == edge) {
		/* _hoops_RSIH _hoops_PGPCR _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_AIAH _hoops_SAHR _hoops_IRS _hoops_SCPH */
		*a = edge;
		*b = edge->next;
		*c = edge->next->next;
	}
	else {
		/* _hoops_AGGPR _hoops_GHIS _hoops_IS _hoops_SSS _hoops_RH 3 _hoops_AAH */
		_hoops_AIIRGR[0] = _hoops_AIIRGR[1] = _hoops_AIIRGR[2] = 0;
		do {
			_hoops_SAIAR = _hoops_IAIRGR (set, edge);
			if (_hoops_SAIAR > _hoops_AIIRGR[2]) {
				for (i = 0 ; i < 3 ; i++) {
					if (_hoops_SAIAR > _hoops_AIIRGR[i]) {
						for (j = 2 ; j > i ; j--)
							_hoops_AIIRGR[j] = _hoops_AIIRGR[j-1];
						_hoops_AIIRGR[i] = _hoops_SAIAR;
						break;
					}	
				}
			}
		} while ((edge = edge->next) != region->_hoops_GRCPR);

		/* _hoops_HA _hoops_PPSI _hoops_RH _hoops_HRSP _hoops_AAH _hoops_CRGR _hoops_IRS,_hoops_RCSR,_hoops_GSGGR _hoops_GGR _hoops_RH _hoops_AGR _hoops_IIGR _hoops_GSCAR */
		edge = region->_hoops_GRCPR;
		k = 0;
		do {
			_hoops_SAIAR = _hoops_IAIRGR (set, edge);
			if (_hoops_SAIAR >= _hoops_AIIRGR[2])
				_hoops_RIIRGR[k++] = edge;
		} while ((edge = edge->next) != region->_hoops_GRCPR);
		ASSERT (k == 3);
		*a = _hoops_RIIRGR[0]->next;
		*b = _hoops_RIIRGR[1]->next;
		*c = _hoops_RIIRGR[2]->next;
	}
}


GLOBAL_FUNCTION void HI_Midpoint_Split_Triangle (
		UV_Region_Set alter *set,
		UV_Region alter *region,
		int alter *_hoops_IRSIH,/* _hoops_GHCA _hoops_SHH _hoops_IRAP */
		UV_Region alter ***_hoops_CRSIH /* _hoops_GHCA _hoops_SHH _hoops_IRAP */) 
{
	UV_Edge			*a, *b, *c, *d, *e, *f, *_hoops_PHIRGR;
	
	HI_Get_UV_Region_Triangle(set, region, &a, &b, &c);

	if (a->next == b)
		d = _hoops_RPIRGR(set, a, b);
	else
		d = _hoops_CPIRGR(set, a, b);
	if (b->next == c)
		e = _hoops_RPIRGR(set, b, c);
	else
		e = _hoops_CPIRGR(set, b, c);
	if (c->next == a)
		f = _hoops_RPIRGR(set, c, a);
	else
		f = _hoops_CPIRGR(set, c, a);
	_hoops_PHIRGR = a;
	while (_hoops_PHIRGR->next != d)
		_hoops_PHIRGR = _hoops_PHIRGR->next;
	_hoops_SPIRGR(set, a, b, c, d, e, f, null, null);
	if (_hoops_IRSIH != null)
		*_hoops_IRSIH = 4;
	_hoops_ARIRGR(set, a->region);
	_hoops_ARIRGR(set, b->region);
	_hoops_ARIRGR(set, c->region);
	_hoops_ARIRGR(set, _hoops_PHIRGR->next->_hoops_RSSCC->region);
	if (_hoops_CRSIH != null) {
		ALLOC_ARRAY(*_hoops_CRSIH, 4, UV_Region *);
		(*_hoops_CRSIH)[0] = a->region;
		(*_hoops_CRSIH)[1] = b->region;
		(*_hoops_CRSIH)[2] = c->region;
		(*_hoops_CRSIH)[3] = _hoops_PHIRGR->next->_hoops_RSSCC->region;
	}
}


GLOBAL_FUNCTION void HI_Midpoint_Split_One_Triangle (
		UV_Region_Set alter *set,
		UV_Edge alter *edge,
		int alter *_hoops_RGGCA,
		UV_Edge alter ***_hoops_PIIRGR)
{
	UV_Edge		*a, *b, *c, *d, *e, *f;
	int				_hoops_GHIRGR;
	UV_Edge alter **_hoops_RHIRGR;

	a = edge;
	b = a->next;
	c = b->next;

	if (c->next != a) {
		_hoops_IRIRGR (set, a);
		b = a->next;
		c = b->next;
	}

	d = _hoops_RPIRGR(set, a, b);
	e = _hoops_RPIRGR(set, b, c);
	f = _hoops_RPIRGR(set, c, a);

	if (a->_hoops_RSSCC != null)
		_hoops_IRIRGR (set, a->next->_hoops_RSSCC);
	if (b->_hoops_RSSCC != null)
		_hoops_IRIRGR (set, b->next->_hoops_RSSCC);
	if (c->_hoops_RSSCC != null)
		_hoops_IRIRGR (set, c->next->_hoops_RSSCC);

	_hoops_SPIRGR(set, a, b, c, d, e, f, &_hoops_GHIRGR, &_hoops_RHIRGR);

	if (_hoops_RGGCA != null)
		*_hoops_RGGCA = _hoops_GHIRGR + 3;
	if (_hoops_PIIRGR != null) {
		UV_Edge alter **_hoops_GRCPR;

		ALLOC_ARRAY(_hoops_GRCPR, _hoops_GHIRGR+3, UV_Edge *);
		_hoops_AIGA(_hoops_RHIRGR, _hoops_GHIRGR, UV_Edge *, _hoops_GRCPR);
		_hoops_GRCPR[_hoops_GHIRGR] = a;
		_hoops_GRCPR[_hoops_GHIRGR+1] = b;
		_hoops_GRCPR[_hoops_GHIRGR+2] = c;
		*_hoops_PIIRGR = _hoops_GRCPR;
	}
	FREE_ARRAY(_hoops_RHIRGR, _hoops_GHIRGR, UV_Edge *);
}


local void _hoops_HIIRGR (UV_Region *region) {
	UV_Edge *		victim = region->_hoops_GRCPR;
	UV_Edge *		next;

	victim = region->_hoops_GRCPR->next;
	region->_hoops_GRCPR->next = null;
	do {
		next = victim->next;
		if (victim->_hoops_RSSCC != null)
			victim->_hoops_RSSCC->_hoops_RSSCC = null;
		FREE (victim, UV_Edge);
	} while ((victim = next) != null);

	FREE (region, UV_Region);
}


GLOBAL_FUNCTION void HI_Free_Region_Set (UV_Region_Set *set) {
	UV_Region *		victim;

	while ((victim = set->regions) != null) {
		set->regions = victim->next;
		_hoops_HIIRGR (victim);
	}

	FREE_ARRAY (set->points, set->_hoops_CAHI, UV_Point);
	FREE (set, UV_Region_Set);
}



GLOBAL_FUNCTION UV_Region_Set * HI_Generate_Convex_Region_Set (
	int					count,
	UV_Point const * points) 
{
	UV_Region_Set *	set = null;
	UV_Region *		region;
	UV_Edge **		_hoops_ASRGR;
	int					_hoops_ASSRR;
	int					i;

	ALLOC (set, UV_Region_Set);
	ALLOC_ARRAY (set->points, count, UV_Point);
	set->point_count = set->_hoops_CAHI = count;
	_hoops_AIGA (points, count, UV_Point, set->points);

	_hoops_ASSRR = ((points[1].u - points[0].u) * (points[2].v - points[1].v) -
			(points[1].v - points[0].v) * (points[2].u - points[1].u)) < 0.0;

	ALLOC (region, UV_Region);
	set->regions = region;
	region->next = null;
	region->_hoops_IHRRH = false;

	region->_hoops_RCHS.min.u = region->_hoops_RCHS.max.u = points[0].u;
	region->_hoops_RCHS.min.v = region->_hoops_RCHS.max.v = points[0].v;

	_hoops_ASRGR = &region->_hoops_GRCPR;
	for (i=0; i<count; ++i) {
		UV_Point const *		here = &points[i];
		UV_Point const *		next = &points[(i+1)%count];
		UV_Edge *			edge;
		float					length;

		if (here->u < region->_hoops_RCHS.min.u)
			region->_hoops_RCHS.min.u = here->u;
		else if (here->u > region->_hoops_RCHS.max.u)
			region->_hoops_RCHS.max.u = here->u;
		if (here->v < region->_hoops_RCHS.min.v)
			region->_hoops_RCHS.min.v = here->v;
		else if (here->v > region->_hoops_RCHS.max.v)
			region->_hoops_RCHS.max.v = here->v;

		ALLOC (edge, UV_Edge);
		*_hoops_ASRGR = edge;
		_hoops_ASRGR = &edge->next;
		edge->_hoops_RSSCC = null;

		edge->index = i;
		edge->region = region;
		edge->priority = -1.0f;
		edge->line.a = here->v - next->v;
		edge->line.b = next->u - here->u;
		if (_hoops_ASSRR) {
			edge->line.a = -edge->line.a;
			edge->line.b = -edge->line.b;
		}
		length = _hoops_SGIHR (edge->line.a * edge->line.a +
					   edge->line.b * edge->line.b);
		if (length > 0.0) {
			length = 1.0f / length;
			edge->line.a *= length;
			edge->line.b *= length;
		}
		edge->line.c = -(edge->line.a * here->u + edge->line.b * here->v);
	}
	*_hoops_ASRGR = region->_hoops_GRCPR;

	return set;
}

GLOBAL_FUNCTION UV_Region_Set * HI_Generate_Rectangular_Regions (
	float				start_u,
	float				end_u,
	float				_hoops_GRSIH,
	float				_hoops_RRSIH,
	int					_hoops_ARSIH,
	int					_hoops_PRSIH) 
{
	UV_Region_Set *	set = null;
	int					_hoops_HIHPR = _hoops_ARSIH + 1;
	int					rows = _hoops_PRSIH + 1;
	int					count = _hoops_HIHPR * rows;
	UV_Region *		_hoops_IIIRGR[256];
	UV_Region **		regions = _hoops_IIIRGR;
	UV_Region *		prev = null;
	int					i, j;

	ALLOC (set, UV_Region_Set);
	ALLOC_ARRAY_CACHED (set->points, count, UV_Point);
	set->point_count = set->_hoops_CAHI = count;

	for (i=0; i<rows; ++i) {
		float			v = _hoops_GRSIH + i * (_hoops_RRSIH - _hoops_GRSIH) / (float)_hoops_PRSIH;

		for (j=0; j<_hoops_HIHPR; ++j) {
			float		u = start_u + j * (end_u - start_u) / (float)_hoops_ARSIH;

			set->points[i*_hoops_HIHPR+j].u = u;
			set->points[i*_hoops_HIHPR+j].v = v;
		}
	}

	if (_hoops_ARSIH * _hoops_PRSIH > 256)
		ALLOC_ARRAY_CACHED (regions, _hoops_ARSIH * _hoops_PRSIH, UV_Region *);

	for (i=0; i<_hoops_PRSIH; ++i) {
		for (j=0; j<_hoops_ARSIH; ++j) {
			UV_Region *		region;
			UV_Edge *		edge;
			UV_Edge **		_hoops_CIIRGR;

			ALLOC (region, UV_Region);
			regions[i*_hoops_ARSIH+j] = region;
			region->_hoops_IHRRH = false;

			region->_hoops_RCHS.min.u = set->points[j].u;
			region->_hoops_RCHS.min.v = set->points[i*_hoops_HIHPR].v;
			region->_hoops_RCHS.max.u = set->points[j+1].u;
			region->_hoops_RCHS.max.v = set->points[(i+1)*_hoops_HIHPR].v;

			/* _hoops_CAHP _hoops_SPPR */
			_hoops_CIIRGR = &region->_hoops_GRCPR;

			ALLOC (edge, UV_Edge);
			*_hoops_CIIRGR = edge;
			_hoops_CIIRGR = &edge->next;
			edge->_hoops_RSSCC = null;
			edge->index = i*_hoops_HIHPR+j;
			edge->region = region;
			edge->priority = -1.0f;
			edge->line.a =	0.0;
			edge->line.b =	1.0;
			edge->line.c = -region->_hoops_RCHS.min.v;

			ALLOC (edge, UV_Edge);
			*_hoops_CIIRGR = edge;
			_hoops_CIIRGR = &edge->next;
			edge->_hoops_RSSCC = null;
			edge->index = i*_hoops_HIHPR+j+1;
			edge->region = region;
			edge->priority = -1.0f;
			edge->line.a = -1.0;
			edge->line.b =	0.0;
			edge->line.c = region->_hoops_RCHS.max.u;

			ALLOC (edge, UV_Edge);
			*_hoops_CIIRGR = edge;
			_hoops_CIIRGR = &edge->next;
			edge->_hoops_RSSCC = null;
			edge->index = (i+1)*_hoops_HIHPR+j+1;
			edge->region = region;
			edge->priority = -1.0f;
			edge->line.a =	0.0;
			edge->line.b = -1.0;
			edge->line.c = region->_hoops_RCHS.max.v;

			ALLOC (edge, UV_Edge);
			*_hoops_CIIRGR = edge;
			_hoops_CIIRGR = &edge->next;
			edge->_hoops_RSSCC = null;
			edge->index = (i+1)*_hoops_HIHPR+j;
			edge->region = region;
			edge->priority = -1.0f;
			edge->line.a =	1.0;
			edge->line.b =	0.0;
			edge->line.c = -region->_hoops_RCHS.min.u;

			*_hoops_CIIRGR = region->_hoops_GRCPR;

			/* _hoops_AGGAR _hoops_ISPH _hoops_GGR _hoops_HIGR */
			region->next = prev;
			prev = region;
		}
	}

	set->regions = prev;

	for (i=0; i<_hoops_PRSIH-1; ++i) {
		for (j=0; j<_hoops_ARSIH; ++j) {
			UV_Region *		_hoops_GPCPA = regions[i*_hoops_ARSIH+j];
			UV_Edge *		_hoops_SIIRGR = _hoops_GPCPA->_hoops_GRCPR->next->next;
			UV_Region *		_hoops_PIGIC = regions[(i+1)*_hoops_ARSIH+j];
			UV_Edge *		_hoops_GCIRGR = _hoops_PIGIC->_hoops_GRCPR;

			_hoops_SIIRGR->_hoops_RSSCC = _hoops_GCIRGR;
			_hoops_GCIRGR->_hoops_RSSCC = _hoops_SIIRGR;
		}
	}

	for (i=0; i<_hoops_PRSIH; ++i) {
		for (j=0; j<_hoops_ARSIH-1; ++j) {
			UV_Region *		left  = regions[i*_hoops_ARSIH+j];
			UV_Edge *		_hoops_RCIRGR = left->_hoops_GRCPR->next;
			UV_Region *		right = regions[i*_hoops_ARSIH+j+1];
			UV_Edge *		_hoops_ACIRGR = right->_hoops_GRCPR->next->next->next;

			_hoops_RCIRGR->_hoops_RSSCC = _hoops_ACIRGR;
			_hoops_ACIRGR->_hoops_RSSCC = _hoops_RCIRGR;
		}
	}

	if (regions != _hoops_IIIRGR)
		FREE_ARRAY (regions, _hoops_ARSIH * _hoops_PRSIH, UV_Region *);

	return set;
}


GLOBAL_FUNCTION UV_Region_Set * HI_Generate_Triangular_Regions (
	float				start_u,
	float				end_u,
	float				_hoops_GRSIH,
	float				_hoops_RRSIH,
	int					_hoops_ARSIH,
	int					_hoops_PRSIH) {
	UV_Region_Set *	set = null;
	UV_Region *region, *tail;
	
	set = HI_Generate_Rectangular_Regions(start_u, end_u, _hoops_GRSIH, _hoops_RRSIH, _hoops_ARSIH, _hoops_PRSIH); 
	tail = region = set->regions;
	while (tail->next != null)
		tail = tail->next;
	while (region != tail) {
		_hoops_IRIRGR(set, region->_hoops_GRCPR);
		region = region->next;
	} 
	_hoops_IRIRGR(set, tail->_hoops_GRCPR);

	return set;
}

local bool _hoops_PCIRGR (
	UV_Region const *	_hoops_IIRHA,
	UV_Point const *	points,
	UV_Region const *	_hoops_HCIRGR) {
	UV_Edge const *		_hoops_ARRGA = _hoops_HCIRGR->_hoops_GRCPR;

	do {
		UV_Edge const *			test = _hoops_IIRHA->_hoops_GRCPR;
		bool					_hoops_ICIRGR = false;

		do {
			UV_Point const *	here = &points[test->index];
			float				_hoops_SSRP = _hoops_ARRGA->line.a * here->u +
									   _hoops_ARRGA->line.b * here->v +
									   _hoops_ARRGA->line.c;

			if (_hoops_SSRP > 0.0f) {
				_hoops_ICIRGR = true;		// _hoops_PAH'_hoops_RA _hoops_PIRRC _hoops_IIHA _hoops_GPP _hoops_RGR _hoops_ISHA
				break;
			}
		} while ((test = test->next) != _hoops_IIRHA->_hoops_GRCPR);

		if (!_hoops_ICIRGR)					// _hoops_ISPH _hoops_CPIIS _hoops_SIPP _hoops_IS _hoops_RGR _hoops_ISHA
			return true;
	} while ((_hoops_ARRGA = _hoops_ARRGA->next) != _hoops_HCIRGR->_hoops_GRCPR);

	return false;
}

#define _hoops_CCIRGR(x)	(-_hoops_RAAHR <= (x) && (x) <= 1.0+_hoops_RAAHR)

GLOBAL_FUNCTION void HI_Subtract_Region_From_Region_Set (
	UV_Region_Set *	set,
	UV_Region_Set *	_hoops_HRSIH) {
	UV_Region *		_hoops_HCIRGR = _hoops_HRSIH->regions;

	if (_hoops_HCIRGR != null) do {
		UV_Region ** _hoops_ASRGR = &set->regions;
		UV_Region *	_hoops_IIRHA;

		while ((_hoops_IIRHA = *_hoops_ASRGR) != null) {
			if (_hoops_IIRHA->_hoops_RCHS.max.u - _hoops_HCIRGR->_hoops_RCHS.min.u > _hoops_RAAHR &&
				_hoops_HCIRGR->_hoops_RCHS.max.u - _hoops_IIRHA->_hoops_RCHS.min.u > _hoops_RAAHR &&
				_hoops_IIRHA->_hoops_RCHS.max.v - _hoops_HCIRGR->_hoops_RCHS.min.v > _hoops_RAAHR &&
				_hoops_HCIRGR->_hoops_RCHS.max.v - _hoops_IIRHA->_hoops_RCHS.min.v > _hoops_RAAHR &&
				!_hoops_PCIRGR (_hoops_IIRHA, set->points, _hoops_HCIRGR)) {
				/* "_hoops_ACAAA" _hoops_RSSAI, _hoops_HA _hoops_RRP _hoops_RRI _hoops_HHHA _hoops_HCGC */
				UV_Edge *			_hoops_ARRGA = _hoops_HCIRGR->_hoops_GRCPR;
				bool				_hoops_IHRRH = false;
				bool				internal = true;

				do {
					UV_Point *		_hoops_IGIGA = &_hoops_HRSIH->points[_hoops_ARRGA->index];
					UV_Point *		_hoops_CGIGA = &_hoops_HRSIH->points[_hoops_ARRGA->next->index];
					UV_Edge *		test = _hoops_IIRHA->_hoops_GRCPR;
					UV_Edge *		start = test;
					UV_Edge *		prev = null;
					UV_Point *		here = &set->points[test->index];
					float				_hoops_GARCA = _hoops_ARRGA->line.a * here->u +
											   _hoops_ARRGA->line.b * here->v +
											   _hoops_ARRGA->line.c;
					int					_hoops_CIARGR = 0;
					int					_hoops_SCIRGR = false;

					do if (test->line.a * _hoops_IGIGA->u +
							test->line.b * _hoops_IGIGA->v +
							 test->line.c > 0.0f &&
						   test->line.a * _hoops_CGIGA->u +
							test->line.b * _hoops_CGIGA->v +
							 test->line.c > 0.0f) {
						_hoops_SCIRGR = true;
						test = start;
						break;
					} while ((test = test->next) != start);

					/* _hoops_HAR _hoops_ICIC _hoops_IS _hoops_HSPP _hoops_HPGR _hoops_IRS _hoops_PPSR _hoops_RRCGC _hoops_RH _hoops_PGAGA */
					while (_hoops_GARCA > -_hoops_RAAHR && _hoops_GARCA < _hoops_RAAHR) {
						prev = test;
						test = start = test->next;
						here = &set->points[test->index];
						_hoops_GARCA = _hoops_ARRGA->line.a * here->u +
							   _hoops_ARRGA->line.b * here->v +
							   _hoops_ARRGA->line.c;
						if (test == _hoops_IIRHA->_hoops_GRCPR) {
							/* _hoops_PAHA'_hoops_RA _hoops_IHPS..._hoops_ARHAR _hoops_ISPH? */
							_hoops_IHRRH = true;			/* _hoops_RGRIR _hoops_PSSAR _hoops_RRGR */
							goto _hoops_GSIRGR;
						}
					}

					if (_hoops_GARCA < -_hoops_RAAHR)
						internal = false;

					do {
						UV_Point *	_hoops_RSIRGR = &set->points[test->next->index];
						float			_hoops_RARCA = _hoops_ARRGA->line.a * _hoops_RSIRGR->u +
											   _hoops_ARRGA->line.b * _hoops_RSIRGR->v +
											   _hoops_ARRGA->line.c;

						if (_hoops_RARCA < -_hoops_RAAHR)
							internal = false;

						if (_hoops_GARCA < -_hoops_RAAHR && _hoops_RARCA > _hoops_RAAHR ||
							_hoops_RARCA < -_hoops_RAAHR && _hoops_GARCA > _hoops_RAAHR) {
							float		_hoops_ASIRGR = _hoops_CGIGA->u - _hoops_IGIGA->u;
							float		_hoops_PSIRGR = _hoops_CGIGA->v - _hoops_IGIGA->v;
							float		_hoops_HSIRGR = _hoops_RSIRGR->u - here->u;
							float		_hoops_ISIRGR = _hoops_RSIRGR->v - here->v;
							float		_hoops_CSIRGR = here->u - _hoops_IGIGA->u;
							float		_hoops_SSIRGR = here->v - _hoops_IGIGA->v;
							float		_hoops_IHIPA = 1.0f/(_hoops_HSIRGR*_hoops_PSIRGR - _hoops_ISIRGR*_hoops_ASIRGR);
							float		s = (_hoops_HSIRGR*_hoops_SSIRGR - _hoops_ISIRGR*_hoops_CSIRGR) * _hoops_IHIPA;
							float		t = (_hoops_ASIRGR*_hoops_SSIRGR - _hoops_PSIRGR*_hoops_CSIRGR) * _hoops_IHIPA;
							bool	_hoops_GGCRGR = false;
							bool	_hoops_RGCRGR = false;

							_hoops_CIARGR = 1;

							if (-_hoops_RAAHR < s && s < _hoops_RAAHR) {
								float			_hoops_AGCRGR;

								_hoops_AGCRGR = test->line.a * _hoops_CGIGA->u +
										 test->line.b * _hoops_CGIGA->v +
										 test->line.c;
								if (_hoops_AGCRGR > 0.0)
									_hoops_GGCRGR = true;
								else
									_hoops_RGCRGR = true;
							}
							if (1.0-_hoops_RAAHR < s && s < 1.0+_hoops_RAAHR) {
								float			_hoops_AGCRGR;

								_hoops_AGCRGR = test->line.a * _hoops_IGIGA->u +
										 test->line.b * _hoops_IGIGA->v +
										 test->line.c;
								if (_hoops_AGCRGR > 0.0)
									_hoops_GGCRGR = true;
								else
									_hoops_RGCRGR = true;
							}

							if ((_hoops_SCIRGR || _hoops_GGCRGR ||
								 _hoops_RAAHR < s && s < 1.0-_hoops_RAAHR) &&
								 !_hoops_RGCRGR) {
								UV_Edge *	other = test->next;

								if (prev != null &&
									(test != prev->next || t < _hoops_RAAHR)) {
									/* _hoops_HPSH _hoops_IRS _hoops_PPSR "_hoops_GPP" _hoops_RH _hoops_PGAGA, _hoops_PAR _hoops_AACC _hoops_HRGR _hoops_HPGR
										_hoops_RSGI _hoops_IIGR "_hoops_RPGP"
									   _hoops_AGRP _hoops_IS _hoops_HGHC _hoops_AACC _hoops_HPGR _hoops_RSGR _hoops_IIGR "_hoops_GCPC" */
									test = prev;
									here = &set->points[test->index];
									_hoops_RSIRGR = &set->points[test->next->index];
									_hoops_HSIRGR = _hoops_RSIRGR->u - here->u;
									_hoops_ISIRGR = _hoops_RSIRGR->v - here->v;
#if 0
									if (t < _hoops_RAAHR) {
										_hoops_GARCA = _hoops_ARRGA->line.a * here->u +
											   _hoops_ARRGA->line.b * here->v +
											   _hoops_ARRGA->line.c;
									}
#endif
									t = 1.0;
								}

								if (_hoops_CCIRGR(t)) {
									/* _hoops_SGSSR _hoops_GIAA _hoops_RH _hoops_SGHC */
									float		_hoops_ACCRR = here->u + t * _hoops_HSIRGR;
									float		_hoops_ISPI = here->v + t * _hoops_ISIRGR;
									int			_hoops_PGCRGR = (_hoops_GARCA < 0);
									int			_hoops_HGCRGR = set->point_count;
									int			_hoops_PSGRA, _hoops_IGCRGR;
									float				_hoops_PCCRR, _hoops_CSPI;
									UV_Edge *		_hoops_CGCRGR;
									UV_Edge *		_hoops_SGCRGR;
									UV_Edge *		_hoops_GRCRGR;
									UV_Edge *		_hoops_RRCRGR;
									UV_Region *		_hoops_ARCRGR;

									_hoops_IHRRH = true;

									if (t < 1.0-_hoops_RAAHR) {
										/* _hoops_HPPA _hoops_RPGP _hoops_ISHA */
										_hoops_PSGRA = _hoops_HGCRGR++;
										ALLOC (_hoops_RRCRGR, UV_Edge);
										_hoops_RRCRGR->index = _hoops_PSGRA;
										_hoops_RRCRGR->region = null;
										_hoops_RRCRGR->priority = -1.0f;
										_hoops_RRCRGR->line.a = test->line.a;
										_hoops_RRCRGR->line.b = test->line.b;
										_hoops_RRCRGR->line.c = test->line.c;
									}
									else {
										/* _hoops_IAGA _hoops_RHIR "_hoops_RSGR" _hoops_IIGR _hoops_RPGP _hoops_ISHA */
										_hoops_PSGRA = test->next->index;
										_hoops_RRCRGR = null;
									}

									ALLOC (_hoops_CGCRGR, UV_Edge);
									_hoops_CGCRGR->index = _hoops_PSGRA;
									_hoops_CGCRGR->region = null;
									_hoops_CGCRGR->priority = -1.0f;
									_hoops_CGCRGR->line.a = _hoops_ARRGA->line.a;
									_hoops_CGCRGR->line.b = _hoops_ARRGA->line.b;
									_hoops_CGCRGR->line.c = _hoops_ARRGA->line.c;

									while (1) {
										UV_Point *	_hoops_AGCSH = &set->points[other->next->index];

										_hoops_RARCA = _hoops_ARRGA->line.a * _hoops_AGCSH->u +
											   _hoops_ARRGA->line.b * _hoops_AGCSH->v +
											   _hoops_ARRGA->line.c;

										if (_hoops_GARCA >	_hoops_RAAHR && _hoops_RARCA > -_hoops_RAAHR ||
											_hoops_GARCA < -_hoops_RAAHR && _hoops_RARCA <  _hoops_RAAHR)
											break;		/* (_hoops_GRS _hoops_SHH) _hoops_ISSC _hoops_GPP _hoops_GIGR _hoops_PPAP */

										other = other->next;
									}

									/*
											 \_hoops_PGAGA
										_hoops_RPGP  \
										-------\--------->
												\
												 \	 _hoops_RII
										<---------\-------
												   \

									_hoops_RHCHR:

										_hoops_RPGP	   _hoops_PRRRH
										------>\  ^--------->
											   _hoops_IRS\  \
												 \	\_hoops_RCSR	_hoops_RII
										<---------_hoops_HPPC	 \<------
												 _hoops_RRRRH
									*/

									here = &set->points[other->index];
									_hoops_RSIRGR = &set->points[other->next->index];
									_hoops_HSIRGR = _hoops_RSIRGR->u - here->u;
									_hoops_ISIRGR = _hoops_RSIRGR->v - here->v;
									_hoops_CSIRGR = here->u - _hoops_IGIGA->u;
									_hoops_SSIRGR = here->v - _hoops_IGIGA->v;
									_hoops_IHIPA = 1.0f/(_hoops_HSIRGR*_hoops_PSIRGR - _hoops_ISIRGR*_hoops_ASIRGR);
									s = (_hoops_HSIRGR*_hoops_SSIRGR - _hoops_ISIRGR*_hoops_CSIRGR) * _hoops_IHIPA;
									t = (_hoops_ASIRGR*_hoops_SSIRGR - _hoops_PSIRGR*_hoops_CSIRGR) * _hoops_IHIPA;
									_hoops_PCCRR = here->u + t * _hoops_HSIRGR;
									_hoops_CSPI = here->v + t * _hoops_ISIRGR;

									if (t < 1.0-_hoops_RAAHR) {
										/* _hoops_HPPA _hoops_RII _hoops_ISHA */
										_hoops_IGCRGR = _hoops_HGCRGR++;
										ALLOC (_hoops_SGCRGR, UV_Edge);
										_hoops_SGCRGR->index = _hoops_IGCRGR;
										_hoops_SGCRGR->region = null;
										_hoops_SGCRGR->priority = -1.0f;
										_hoops_SGCRGR->line.a = other->line.a;
										_hoops_SGCRGR->line.b = other->line.b;
										_hoops_SGCRGR->line.c = other->line.c;
									}
									else {
										/* _hoops_IAGA _hoops_RHIR "_hoops_RSGR" _hoops_IIGR _hoops_RII */
										_hoops_IGCRGR = other->next->index;
										_hoops_SGCRGR = null;
									}

									ALLOC (_hoops_GRCRGR, UV_Edge);
									_hoops_GRCRGR->index = _hoops_IGCRGR;
									_hoops_GRCRGR->region = null;
									_hoops_GRCRGR->priority = -1.0f;
									_hoops_GRCRGR->line.a = _hoops_ARRGA->line.a;
									_hoops_GRCRGR->line.b = _hoops_ARRGA->line.b;
									_hoops_GRCRGR->line.c = _hoops_ARRGA->line.c;

									if (_hoops_SGCRGR != null) {
										_hoops_CGCRGR->next = _hoops_SGCRGR;
										_hoops_SGCRGR->next = other->next;
									}
									else
										_hoops_CGCRGR->next = other->next;

									if (_hoops_RRCRGR != null) {
										_hoops_GRCRGR->next = _hoops_RRCRGR;
										_hoops_RRCRGR->next = test->next;
									}
									else
										_hoops_GRCRGR->next = test->next;

									test->next = _hoops_CGCRGR;
									other->next = _hoops_GRCRGR;
									_hoops_CGCRGR->_hoops_RSSCC = _hoops_GRCRGR;
									_hoops_GRCRGR->_hoops_RSSCC = _hoops_CGCRGR;

									if (_hoops_SGCRGR != null) {
										if (other->_hoops_RSSCC != null) {
											UV_Edge *				_hoops_APIS;

											ALLOC (_hoops_APIS, UV_Edge);
											_hoops_APIS->index = _hoops_IGCRGR;
											_hoops_APIS->region = other->_hoops_RSSCC->region;
											_hoops_APIS->priority = -1.0f;
											_hoops_APIS->line.a = other->_hoops_RSSCC->line.a;
											_hoops_APIS->line.b = other->_hoops_RSSCC->line.b;
											_hoops_APIS->line.c = other->_hoops_RSSCC->line.c;

											_hoops_APIS->next = other->_hoops_RSSCC->next;
											other->_hoops_RSSCC->next = _hoops_APIS;
											_hoops_SGCRGR->_hoops_RSSCC = other->_hoops_RSSCC;
											other->_hoops_RSSCC->_hoops_RSSCC = _hoops_SGCRGR;
											_hoops_APIS->_hoops_RSSCC = other;
											other->_hoops_RSSCC = _hoops_APIS;
										}
										else
											_hoops_SGCRGR->_hoops_RSSCC = null;
									}

									if (_hoops_RRCRGR != null) {
										if (test->_hoops_RSSCC != null) {
											UV_Edge *				_hoops_APIS;

											ALLOC (_hoops_APIS, UV_Edge);
											_hoops_APIS->index = _hoops_PSGRA;
											_hoops_APIS->region = test->_hoops_RSSCC->region;
											_hoops_APIS->priority = -1.0f;
											_hoops_APIS->line.a = test->_hoops_RSSCC->line.a;
											_hoops_APIS->line.b = test->_hoops_RSSCC->line.b;
											_hoops_APIS->line.c = test->_hoops_RSSCC->line.c;

											_hoops_APIS->next = test->_hoops_RSSCC->next;
											test->_hoops_RSSCC->next = _hoops_APIS;
											_hoops_RRCRGR->_hoops_RSSCC = test->_hoops_RSSCC;
											test->_hoops_RSSCC->_hoops_RSSCC = _hoops_RRCRGR;
											_hoops_APIS->_hoops_RSSCC = test;
											test->_hoops_RSSCC = _hoops_APIS;
										}
										else
											_hoops_RRCRGR->_hoops_RSSCC = null;
									}

									if (_hoops_HGCRGR > set->_hoops_CAHI) {
										UV_Point *	new_points;

										ALLOC_ARRAY_CACHED (new_points,
													 set->_hoops_CAHI+16,
													 UV_Point);
										_hoops_AIGA (set->points, set->point_count, UV_Point,
													 new_points);
										FREE_ARRAY (set->points, set->_hoops_CAHI,
													UV_Point);
										set->points = new_points;
										set->_hoops_CAHI += 16;
									}
									if (_hoops_PSGRA >= set->point_count) {
										set->points[set->point_count].u = _hoops_ACCRR;
										set->points[set->point_count++].v = _hoops_ISPI;
									}
									if (_hoops_IGCRGR >= set->point_count) {
										set->points[set->point_count].u = _hoops_PCCRR;
										set->points[set->point_count++].v = _hoops_CSPI;
									}

									ALLOC (_hoops_ARCRGR, UV_Region);
									_hoops_ARCRGR->next = _hoops_IIRHA;
									*_hoops_ASRGR = _hoops_ARCRGR;
									_hoops_ASRGR = &_hoops_ARCRGR->next;

									if (_hoops_PGCRGR) {
										_hoops_CGCRGR->line.a = -_hoops_CGCRGR->line.a;
										_hoops_CGCRGR->line.b = -_hoops_CGCRGR->line.b;
										_hoops_CGCRGR->line.c = -_hoops_CGCRGR->line.c;

										_hoops_ARCRGR->_hoops_GRCPR = test;
										_hoops_IIRHA->_hoops_GRCPR = other;
									}
									else {
										_hoops_GRCRGR->line.a = -_hoops_GRCRGR->line.a;
										_hoops_GRCRGR->line.b = -_hoops_GRCRGR->line.b;
										_hoops_GRCRGR->line.c = -_hoops_GRCRGR->line.c;

										_hoops_ARCRGR->_hoops_GRCPR = other;
										_hoops_IIRHA->_hoops_GRCPR = test;
									}
									_hoops_ARCRGR->_hoops_IHRRH = _hoops_IIRHA->_hoops_IHRRH = true;

									/* _hoops_GGCH _hoops_SHIAR */
									_hoops_ARIRGR (set, _hoops_IIRHA);
									_hoops_ARIRGR (set, _hoops_ARCRGR);

									/* _hoops_CCIH _hoops_PGHH */
									test = _hoops_IIRHA->_hoops_GRCPR;
									do test->region = _hoops_IIRHA;
									while ((test = test->next) != _hoops_IIRHA->_hoops_GRCPR);

									test = _hoops_ARCRGR->_hoops_GRCPR;
									do test->region = _hoops_ARCRGR;
									while ((test = test->next) != _hoops_ARCRGR->_hoops_GRCPR);

									/* _hoops_PSP _hoops_RRI _hoops_SPPR _hoops_RRP _hoops_IS _hoops_SHH _hoops_RAICR _hoops_IH _hoops_RGR _hoops_AACC */
									break;
								}
							}
						}

						here = _hoops_RSIRGR;
						if (_hoops_RARCA > _hoops_RAAHR || _hoops_RARCA < -_hoops_RAAHR) {
							_hoops_GARCA = _hoops_RARCA;
							prev = test;
						}
						else if (prev == null)
							prev = test;
						else if (prev->next == test &&
								 (_hoops_GARCA > _hoops_RAAHR || _hoops_GARCA < -_hoops_RAAHR)) {
							prev = test;
						}
					} while ((test = test->next) != start);

					if (!_hoops_CIARGR && _hoops_GARCA < 0.0) {
						/* _hoops_HCR _hoops_GPP _hoops_PRCRGR _hoops_PPAP _hoops_IIGR _hoops_PCCP _hoops_ISHA, _hoops_GRHP _hoops_RH _hoops_SHSC _hoops_ISPH */
						goto _hoops_HRCRGR;
					}
				} while ((_hoops_ARRGA = _hoops_ARRGA->next) != _hoops_HCIRGR->_hoops_GRCPR);

				/* [_hoops_GII _hoops_HHRPA] _hoops_ISPH _hoops_HRGR _hoops_PAHH _hoops_PCRAI */
			  _hoops_GSIRGR:
				if (_hoops_IHRRH || internal) {
					*_hoops_ASRGR = _hoops_IIRHA->next;
					_hoops_HIIRGR (_hoops_IIRHA);

					continue;	/* _hoops_HSGR _hoops_IHH _hoops_HPSIP _hoops_CIAAI _hoops_HPGR _hoops_RSGR _hoops_IIGR _hoops_HGSI _hoops_HAPR */
				}
			}

		  _hoops_HRCRGR:
			_hoops_ASRGR = &_hoops_IIRHA->next;
		}
	} while ((_hoops_HCIRGR = _hoops_HCIRGR->next) != null);


	/* _hoops_CACH _hoops_RPP _hoops_IIH _hoops_CHR _hoops_GII _hoops_RHRH _hoops_PGHH _hoops_IS _hoops_HASIR */
	if (set->regions != null) {
		UV_Region ** _hoops_ASRGR = &set->regions;
		UV_Region *	_hoops_IIRHA;
		bool		_hoops_CCCIR = true;

		while (_hoops_CCCIR) {
			_hoops_CCCIR = false;

			while ((_hoops_IIRHA = *_hoops_ASRGR) != null) {
				UV_Edge *	test;
				bool		_hoops_IRCRGR = false;

				test = _hoops_IIRHA->_hoops_GRCPR;
				do {
					if (test->_hoops_RSSCC == null) {
						_hoops_IRCRGR = true;
						break;
					}
				} while ((test = test->next) != _hoops_IIRHA->_hoops_GRCPR);


				if (_hoops_IRCRGR) {
					float			area = 0.0f;
					float			_hoops_PARPA, dist, _hoops_IRIAR, _hoops_CRIAR;
					UV_Point *	here;
					UV_Point *	_hoops_RSIRGR;
					UV_Point *	first;

					/* _hoops_GRAS _hoops_CCAC _hoops_PPR _hoops_SPCC _hoops_IIGR _hoops_CPIS _hoops_ISHA */
					test = _hoops_IIRHA->_hoops_GRCPR;
					first = &set->points[test->index];
					if (test->_hoops_RSSCC == null)
						_hoops_IRCRGR = true;

					test = test->next;
					here = &set->points[test->index];
					if (test->_hoops_RSSCC == null)
						_hoops_IRCRGR = true;

					_hoops_IRIAR = first->u - here->u;
					_hoops_CRIAR = first->v - here->v;
					_hoops_PARPA = _hoops_SGIHR (_hoops_IRIAR*_hoops_IRIAR + _hoops_CRIAR*_hoops_CRIAR);

					test = test->next;
					do {
						_hoops_RSIRGR = &set->points[test->index];
						if (test->_hoops_RSSCC == null)
							_hoops_IRCRGR = true;

						_hoops_IRIAR = _hoops_RSIRGR->u - here->u;
						_hoops_CRIAR = _hoops_RSIRGR->v - here->v;
						dist = _hoops_SGIHR (_hoops_IRIAR*_hoops_IRIAR + _hoops_CRIAR*_hoops_CRIAR);

						if (dist > _hoops_PARPA)
							_hoops_PARPA = dist;

						area += ((first->u - here->u)*(first->v - _hoops_RSIRGR->v) -
								 (first->v - here->v)*(first->u - _hoops_RSIRGR->u));

						here = _hoops_RSIRGR;
					} while ((test = test->next) != _hoops_IIRHA->_hoops_GRCPR);
					area *= 0.5f;

					_hoops_IRIAR = first->u - here->u;
					_hoops_CRIAR = first->v - here->v;
					dist = _hoops_SGIHR (_hoops_IRIAR*_hoops_IRIAR + _hoops_CRIAR*_hoops_CRIAR);

					if (dist > _hoops_PARPA)
						_hoops_PARPA = dist;

					if (area < 0.0f)
						area = -area;

					/* _hoops_RPP _hoops_RGRRR & _hoops_SHRII _hoops_GGIC, _hoops_SIAS _hoops_SHH _hoops_IRS _hoops_CRCRGR */
					if (area / _hoops_PARPA < _hoops_RAAHR) {
						/* _hoops_RRP _hoops_IS _hoops_CACH _hoops_RPP _hoops_PCCP _hoops_IGS _hoops_ISHA _hoops_HRGR _hoops_IRS _hoops_RGRRR _hoops_SPR */
						test = _hoops_IIRHA->_hoops_GRCPR;

						do {
							if (test->_hoops_RSSCC == null) {
								here = &set->points[test->index];
								_hoops_RSIRGR = &set->points[test->next->index];

								_hoops_IRIAR = _hoops_RSIRGR->u - here->u;
								_hoops_CRIAR = _hoops_RSIRGR->v - here->v;
								dist = _hoops_SGIHR (_hoops_IRIAR*_hoops_IRIAR + _hoops_CRIAR*_hoops_CRIAR);

								if (dist > 0.25f*_hoops_PARPA) {
									*_hoops_ASRGR = _hoops_IIRHA->next;
									_hoops_HIIRGR (_hoops_IIRHA);
									_hoops_IIRHA = null;
									_hoops_CCCIR = true;
									break;
								}
							}
						} while ((test = test->next) != _hoops_IIRHA->_hoops_GRCPR);
					}
				}

				if (_hoops_IIRHA != null)
					_hoops_ASRGR = &_hoops_IIRHA->next;
			}
		}
	}
}

GLOBAL_FUNCTION void HI_Convert_Regions_To_Facelist (UV_Region_Set const * set,
							 int ** list, int * length, int *_hoops_HCGIR) {
	UV_Region *		region;
	int *				count;
	int *				next;
	bool			_hoops_SRCRGR = false;

	*length = 0;
	*_hoops_HCGIR = 0;

	if (set == null || set->regions == null)
		return;

	/* _hoops_SRS _hoops_RPR _hoops_RSH _hoops_GSGS _hoops_SR _hoops_GRS _hoops_RRP */
	region = set->regions;
	do {
		UV_Edge *	edge = region->_hoops_GRCPR;
		int				_hoops_PGAHA = 0;

		do {
			++_hoops_PGAHA;		/* _hoops_SPR _hoops_IH _hoops_GRR _hoops_GPHA _hoops_GGR _hoops_RGR _hoops_ISPH */
		} while ((edge = edge->next) != region->_hoops_GRCPR);

		if (_hoops_SRCRGR || region->_hoops_IHRRH) {
			_hoops_PGAHA -= 2;			/* 2 _hoops_HIPH _hoops_CRGP _hoops_HSAR _hoops_RSSA */
			*_hoops_HCGIR += _hoops_PGAHA;	/* _hoops_PRIA _hoops_SGS */
			_hoops_PGAHA *= 4;			/* _hoops_PPR 4 _hoops_AGRIR _hoops_RIR _hoops_SCPH */
		}
		else {
			++*_hoops_HCGIR;				/* _hoops_SPR _hoops_RRI _hoops_HSP */
			++_hoops_PGAHA;				/* _hoops_SAHR _hoops_RRP _hoops_IRS _hoops_RSRA _hoops_RPR */
		}

		*length += _hoops_PGAHA;
	} while ((region = region->next) != null);

	/* _hoops_HA _hoops_CCPP _hoops_GC */
	ALLOC_ARRAY (next, *length, int);	 
	*list = next;

	/* _hoops_PPR _hoops_CISA _hoops_SCH _hoops_GGR */
	region = set->regions;
	do {
		UV_Edge *	edge = region->_hoops_GRCPR;

		if (_hoops_SRCRGR || region->_hoops_IHRRH) {
			int			first = edge->index;

			edge = edge->next;
			do {
				*next++ = 3;
				*next++ = first;
				*next++ = edge->index;
				*next++ = edge->next->index;
			} while ((edge = edge->next)->next != region->_hoops_GRCPR);
		}
		else {
			count = next++;
			*count = 0;

			do {
				*next++ = edge->index;
				++*count;
			} while ((edge = edge->next) != region->_hoops_GRCPR);
		}
	} while ((region = region->next) != null);
}


local void _hoops_GACRGR (void *info, Integer32 _hoops_HAPH,
						 Integer32 _hoops_ISPI, Integer32 _hoops_CSPI, Integer32 _hoops_SSPI) 
{
	UV_Region_Set *	set = (UV_Region_Set *)info;
	UV_Point const * points = set->points;
	UV_Region *		region;
	float				_hoops_SAIAR;
	int					_hoops_ASSRR;
	UV_Edge **		_hoops_ASRGR;
	int					i;

	UNREFERENCED(_hoops_HAPH);

	_hoops_SAIAR = (points[_hoops_CSPI].u - points[_hoops_ISPI].u) * (points[_hoops_SSPI].v - points[_hoops_CSPI].v) -
			(points[_hoops_CSPI].v - points[_hoops_ISPI].v) * (points[_hoops_SSPI].u - points[_hoops_CSPI].u);

	//_hoops_RPP (_hoops_SHHP > -_hoops_IPHSH && _hoops_SHHP < _hoops_IPHSH)	/* _hoops_HAH _hoops_GGIC _hoops_IS _hoops_HIISR _hoops_CCA */
	//	_hoops_ASRC;

	_hoops_ASSRR = _hoops_SAIAR < 0.0;

	/* _hoops_PSP _hoops_PSSP _hoops_PAR _hoops_ASSP'_hoops_RA _hoops_SGAGA _hoops_SGCS; _hoops_RRP _hoops_IS _hoops_IRHH _hoops_IRS _hoops_CCAH _hoops_ISPH _hoops_HA */
	ALLOC (region, UV_Region);
	region->next = set->regions;
	set->regions = region;
	region->_hoops_IHRRH = false;

	region->_hoops_RCHS.min.u = region->_hoops_RCHS.max.u = points[_hoops_ISPI].u;
	region->_hoops_RCHS.min.v = region->_hoops_RCHS.max.v = points[_hoops_CSPI].v;

	_hoops_ASRGR = &region->_hoops_GRCPR;
	for (i=0; i<3; ++i) {
		UV_Point const *		here = null;
		UV_Point const *		_hoops_RSIRGR = null;
		UV_Edge *			edge = null;
		float					length = 0;
		int						index = -1;

		switch (i) {
			case 0: {
				index = _hoops_ISPI;
				here = &points[_hoops_ISPI];
				_hoops_RSIRGR = &points[_hoops_CSPI];
			}	break;
			case 1: {
				index = _hoops_CSPI;
				here = &points[_hoops_CSPI];
				_hoops_RSIRGR = &points[_hoops_SSPI];
			}	break;
			case 2: {
				index = _hoops_SSPI;
				here = &points[_hoops_SSPI];
				_hoops_RSIRGR = &points[_hoops_ISPI];
			}	break;
		};

		if (here->u < region->_hoops_RCHS.min.u)
			region->_hoops_RCHS.min.u = here->u;
		else if (here->u > region->_hoops_RCHS.max.u)
			region->_hoops_RCHS.max.u = here->u;
		if (here->v < region->_hoops_RCHS.min.v)
			region->_hoops_RCHS.min.v = here->v;
		else if (here->v > region->_hoops_RCHS.max.v)
			region->_hoops_RCHS.max.v = here->v;

		ALLOC (edge, UV_Edge);
		*_hoops_ASRGR = edge;
		_hoops_ASRGR = &edge->next;
		edge->_hoops_RSSCC = null;

		edge->index = index;
		edge->region = region;
		edge->priority = -1.0f;
		edge->line.a = here->v - _hoops_RSIRGR->v;
		edge->line.b = _hoops_RSIRGR->u - here->u;
		if (_hoops_ASSRR) {
			edge->line.a = -edge->line.a;
			edge->line.b = -edge->line.b;
		}
		length = _hoops_SGIHR (edge->line.a * edge->line.a +
					   edge->line.b * edge->line.b);
		if (length > 0.0) {
			length = 1.0f / length;
			edge->line.a *= length;
			edge->line.b *= length;
		}
		edge->line.c = -(edge->line.a * here->u + edge->line.b * here->v);
	}
	*_hoops_ASRGR = region->_hoops_GRCPR;
}


local void _hoops_CRASH (void *info, Integer32 _hoops_HAPH,
						 Integer32 _hoops_ISPI, Integer32 _hoops_CSPI, Integer32 _hoops_SSPI) {
	UV_Region_Set *	set = (UV_Region_Set *)info;
	UV_Point const * points = set->points;
	UV_Region *		region;
	float				_hoops_SAIAR;
	int					_hoops_ASSRR;

	UNREFERENCED(_hoops_HAPH);

	_hoops_SAIAR = (points[_hoops_CSPI].u - points[_hoops_ISPI].u) * (points[_hoops_SSPI].v - points[_hoops_CSPI].v) -
			(points[_hoops_CSPI].v - points[_hoops_ISPI].v) * (points[_hoops_SSPI].u - points[_hoops_CSPI].u);

	//_hoops_RPP (_hoops_SHHP > -_hoops_IPHSH && _hoops_SHHP < _hoops_IPHSH)	/* _hoops_HAH _hoops_GGIC _hoops_IS _hoops_HIISR _hoops_CCA */
	//	_hoops_ASRC;

	_hoops_ASSRR = _hoops_SAIAR < 0.0;

	/* _hoops_HPPR _hoops_IS _hoops_HASC _hoops_IRS _hoops_SCPH _hoops_CCA _hoops_IRS _hoops_PGHC _hoops_ISPH */
	if ((region = set->regions) != null) do {
		UV_Edge *	prev = region->_hoops_GRCPR;
		UV_Edge *	edge = prev->next;
		UV_Edge *	next = edge->next;

		do {
			int			_hoops_PSHGA = -1;	/* _hoops_HPCAR _hoops_PSP _hoops_PSSP */

			if (edge->index == _hoops_ISPI && next->index == _hoops_SSPI)
				_hoops_PSHGA = _hoops_CSPI;
			else if (edge->index == _hoops_CSPI && next->index == _hoops_ISPI)
				_hoops_PSHGA = _hoops_SSPI;
			else if (edge->index == _hoops_SSPI && next->index == _hoops_CSPI)
				_hoops_PSHGA = _hoops_ISPI;

			if (_hoops_PSHGA != -1) {		/* _hoops_CCRPA _hoops_IAPR _hoops_RGR _hoops_ISHA! */
				UV_Point const *		here = &set->points[edge->index];
				UV_Point const *		_hoops_RSIRGR = &set->points[_hoops_PSHGA];
				float					length;

				/* _hoops_RPP _hoops_PPSR _hoops_ICHIA _hoops_SIPP _hoops_PGI _hoops_GCPC _hoops_PAR _hoops_SPS,
						_hoops_SCH _hoops_CHH _hoops_IRHH _hoops_IRS _hoops_AGHH _hoops_ISPH */
				if (prev->line.a * _hoops_RSIRGR->u +
					  prev->line.b * _hoops_RSIRGR->v +
						prev->line.c  <	 0.0f  ||
					next->line.a * _hoops_RSIRGR->u +
					  next->line.b * _hoops_RSIRGR->v +
						next->line.c  <	 0.0f)
					break;		/* _hoops_RIARR _hoops_ISHA _hoops_HAPR, _hoops_HPPR _hoops_HPIH _hoops_ISPH */

				/* _hoops_HASC _hoops_SCPH _hoops_IAPR _hoops_RGR _hoops_ISHA! */
				/* "_hoops_ISHA" _hoops_RASA _hoops_CCA _hoops_IRS->_hoops_RCSR, _hoops_CCAH "_hoops_SPS" _hoops_IH _hoops_RCSR->_hoops_GSGGR */

				ALLOC (next, UV_Edge);
				next->next = edge->next;
				edge->next = next;
				next->_hoops_RSSCC = null;

				next->index = _hoops_PSHGA;
				next->region = region;
				next->priority = -1.0f;

				/* _hoops_IRCH _hoops_PRCH _hoops_RPP _hoops_SIGR */
				if (_hoops_RSIRGR->u < region->_hoops_RCHS.min.u)
					region->_hoops_RCHS.min.u = _hoops_RSIRGR->u;
				else if (_hoops_RSIRGR->u > region->_hoops_RCHS.max.u)
					region->_hoops_RCHS.max.u = _hoops_RSIRGR->u;
				if (_hoops_RSIRGR->v < region->_hoops_RCHS.min.v)
					region->_hoops_RCHS.min.v = _hoops_RSIRGR->v;
				else if (_hoops_RSIRGR->v > region->_hoops_RCHS.max.v)
					region->_hoops_RCHS.max.v = _hoops_RSIRGR->v;

				/* "_hoops_ISHA" _hoops_IRHS _hoops_IRS _hoops_CCAH _hoops_III _hoops_CGSSR */
				edge->line.a = here->v - _hoops_RSIRGR->v;
				edge->line.b = _hoops_RSIRGR->u - here->u;
				if (_hoops_ASSRR) {
					edge->line.a = -edge->line.a;
					edge->line.b = -edge->line.b;
				}
				length = _hoops_SGIHR (edge->line.a * edge->line.a +
							   edge->line.b * edge->line.b);
				if (length > 0.0) {
					length = 1.0f / length;
					edge->line.a *= length;
					edge->line.b *= length;
				}
				edge->line.c = -(edge->line.a * here->u + edge->line.b * here->v);

				/* "_hoops_SPS" _hoops_IRHS _hoops_IRS _hoops_III _hoops_CGSSR _hoops_IAIAR */
				here = _hoops_RSIRGR;
				_hoops_RSIRGR = &set->points[next->next->index];

				next->line.a = here->v - _hoops_RSIRGR->v;
				next->line.b = _hoops_RSIRGR->u - here->u;
				if (_hoops_ASSRR) {
					next->line.a = -next->line.a;
					next->line.b = -next->line.b;
				}
				length = _hoops_SGIHR (next->line.a * next->line.a +
							   next->line.b * next->line.b);
				if (length > 0.0) {
					length = 1.0f / length;
					next->line.a *= length;
					next->line.b *= length;
				}
				next->line.c = -(next->line.a * here->u + next->line.b * here->v);

				return;
			}

			prev = edge;
			edge = next;
			next = next->next;
		} while (prev != region->_hoops_GRCPR);
	} while ((region = region->next) != null);

	_hoops_GACRGR(info, _hoops_HAPH, _hoops_ISPI, _hoops_CSPI, _hoops_SSPI);
}




GLOBAL_FUNCTION UV_Region_Set * HI_Generate_Complex_Region_Set (
	int							point_count,
	UV_Point const *			points,
	int							face_list_length,
	int const *					face_list,
	bool					_hoops_SGSIH) {
	UV_Region_Set *			set = null;
	Point					_hoops_RACRGR[256];
	Point *					_hoops_AHCP = _hoops_RACRGR;
	int							i;
	int *						new_face_list;
	int							_hoops_PAAHA;
	_hoops_RRCIH		_hoops_AACRGR;

	ALLOC (set, UV_Region_Set);
	ALLOC_ARRAY_CACHED (set->points, point_count + 4, UV_Point);
	set->point_count = point_count;
	set->_hoops_CAHI = point_count + 4;
	_hoops_AIGA (points, point_count, UV_Point, set->points);
	set->regions = null;

	if (point_count+4 > _hoops_GGAPR(_hoops_RACRGR))
		ALLOC_ARRAY_CACHED (_hoops_AHCP, point_count+4, Point);

	/* _hoops_SRS _hoops_RPR _hoops_HHHR _hoops_AGSR _hoops_SR _hoops_HHGC _hoops_IS _hoops_GRHP _hoops_RH _hoops_CHIA _hoops_ISPH,
	 * _hoops_HIS _hoops_SR _hoops_RRP _hoops_IS _hoops_IRHH _hoops_SCH _hoops_IRS _hoops_RCCPR _hoops_GGR _hoops_IRS _hoops_APPR _hoops_PACRGR _hoops_ISPH.
	 */
	if (face_list[0] < 0) {
		UV_Point						min, max;

		min.u = max.u = points[0].u;
		min.v = max.v = points[0].v;
		for (i=0; i<point_count; ++i) {
			if		(points[i].u < min.u) min.u = points[i].u;
			else if (points[i].u > max.u) max.u = points[i].u;
			if		(points[i].v < min.v) min.v = points[i].v;
			else if (points[i].v > max.v) max.v = points[i].v;

			_hoops_AHCP[i].x = points[i].u;
			_hoops_AHCP[i].y = points[i].v;
			_hoops_AHCP[i].z = 0.0;
		}

		/* _hoops_IRHH _hoops_RH _hoops_CRIPR _hoops_ISPH _hoops_APPR _hoops_IS _hoops_HACRGR _hoops_RH _hoops_SHSC _hoops_ISPH */
		min.u -= 2;
		min.v -= 2;
		max.u += 2;
		max.v += 2;

		set->point_count += 4;

		_hoops_AHCP[i].x = set->points[i].u = min.u;
		_hoops_AHCP[i].y = set->points[i].v = min.v;
		_hoops_AHCP[i].z = 0;
		i++;
		_hoops_AHCP[i].x = set->points[i].u = max.u;
		_hoops_AHCP[i].y = set->points[i].v = min.v;
		_hoops_AHCP[i].z = 0;
		i++;
		_hoops_AHCP[i].x = set->points[i].u = max.u;
		_hoops_AHCP[i].y = set->points[i].v = max.v;
		_hoops_AHCP[i].z = 0;
		i++;
		_hoops_AHCP[i].x = set->points[i].u = min.u;
		_hoops_AHCP[i].y = set->points[i].v = max.v;
		_hoops_AHCP[i].z = 0;

		ALLOC_ARRAY_CACHED (new_face_list, face_list_length+5, int);

		new_face_list[0] = 4;
		new_face_list[1] = point_count;
		new_face_list[2] = point_count + 1;
		new_face_list[3] = point_count + 2;
		new_face_list[4] = point_count + 3;

		/* _hoops_PAGA: _hoops_IACRGR _hoops_ASSP'_hoops_RA _hoops_PICP _hoops_AHCA _hoops_HRASR _hoops_IIGR _hoops_IHHA, _hoops_HIS _hoops_SR _hoops_PAH _hoops_SAHR
		 *	_hoops_IPS _hoops_RH _hoops_CRPR _hoops_SIHH _hoops_PCIPR _hoops_AHCA _hoops_CACRGR _hoops_GII _hoops_RAGIR
		 */
		_hoops_AIGA (face_list, face_list_length, int, new_face_list+5);
		_hoops_PAAHA = face_list_length + 5;
	}
	else {
		for (i=0; i<point_count; ++i) {
			_hoops_AHCP[i].x = points[i].u;
			_hoops_AHCP[i].y = points[i].v;
			_hoops_AHCP[i].z = 0.0;
		}

		new_face_list = (int *)face_list;
		_hoops_PAAHA = face_list_length;
	}

	if (_hoops_SGSIH)
		_hoops_AACRGR = _hoops_GACRGR;
	else
		_hoops_AACRGR = _hoops_CRASH;
		
	if (!HI_Triangulate_Face (_hoops_AHCP, &_hoops_IRGA::_hoops_IGHH,
							  new_face_list, new_face_list+_hoops_PAAHA,
							  _hoops_AACRGR, set)) {
		HE_WARNING (HEC_SURFACE, HES_SELF_INTERSECTING_FACE,
				"Encountered a self-intersecting or badly formed surface trim");
	}

	if (_hoops_AHCP != _hoops_RACRGR)
		FREE_ARRAY (_hoops_AHCP, point_count+4, Point);

	if (new_face_list != face_list)
		FREE_ARRAY (new_face_list, _hoops_PAAHA, int);

	return set;
}

GLOBAL_FUNCTION UV_Region_Set * HI_Generate_Polygonal_Region_Set (
	int					count,
	UV_Point const *	points,
	bool				_hoops_SGSIH) {
	UV_Region_Set *		set = null;
	int					_hoops_APIGA[260];
	int *				face_list = _hoops_APIGA;
	bool				_hoops_SACRGR = false;

	if (count < 0) {
		count = -count; 
		_hoops_SACRGR = true;
	}

	if (count+1 > _hoops_GGAPR(_hoops_APIGA))
		ALLOC_ARRAY (face_list, count+1, int);

	UV_Point			min, max;
	min = max = points[0];

	for (int i = 1; i < count; ++i) {
		if (points[i].u < min.u)
			min.u = points[i].u;
		else if (points[i].u > max.u)
			max.u = points[i].u;

		if (points[i].u < min.u)
			min.u = points[i].u;
		else if (points[i].u > max.u)
			max.u = points[i].u;
	}

	float				_hoops_GSAHR = _hoops_IAAA (max.u - min.u, max.v - min.v) * _hoops_RAAHR;

	_hoops_GSAHR *= _hoops_GSAHR;

	int		_hoops_GPCRGR = 0; 
	for (int i = 0; i < count; ++i) {
		if (i < 2)
			face_list[++_hoops_GPCRGR] = i;
		else {
			int		_hoops_ISPI = face_list[_hoops_GPCRGR-1];
			int		_hoops_CSPI = face_list[_hoops_GPCRGR];
			float	_hoops_SAIAR = (points[_hoops_CSPI].u - points[_hoops_ISPI].u) * (points[i].v - points[_hoops_CSPI].v) -
							(points[_hoops_CSPI].v - points[_hoops_ISPI].v) * (points[i].u - points[_hoops_CSPI].u);

			if (_hoops_SAIAR > -_hoops_GSAHR && _hoops_SAIAR < _hoops_GSAHR)
				face_list[_hoops_GPCRGR] = i;	// _hoops_RGCPR _hoops_III, _hoops_GCGRA _hoops_IRGP _hoops_PPSR _hoops_CCA _hoops_CCAH
			else
				face_list[++_hoops_GPCRGR] = i;	// _hoops_GGCR _hoops_CCAH _hoops_IS _hoops_HIGR
		}
	}
	if (points[face_list[_hoops_GPCRGR]].u == points[0].u &&
		points[face_list[_hoops_GPCRGR]].v == points[0].v)	// _hoops_GA'_hoops_RA _hoops_RRP _hoops_HHHA _hoops_GGGR
		--_hoops_GPCRGR;
	else {
		int		_hoops_ISPI = face_list[_hoops_GPCRGR-1];
		int		_hoops_CSPI = face_list[_hoops_GPCRGR];
		float	_hoops_SAIAR = (points[_hoops_CSPI].u - points[_hoops_ISPI].u) * (points[0].v - points[_hoops_CSPI].v) -
						(points[_hoops_CSPI].v - points[_hoops_ISPI].v) * (points[0].u - points[_hoops_CSPI].u);

		if (_hoops_SAIAR > -_hoops_GSAHR && _hoops_SAIAR < _hoops_GSAHR)
			--_hoops_GPCRGR;								// _hoops_RGCPR _hoops_III _hoops_RPCRGR _hoops_GGGR, _hoops_GA'_hoops_RA _hoops_RRP _hoops_IRGP _hoops_PPSR
	}

	if (_hoops_SACRGR)
		face_list[0] = -_hoops_GPCRGR;
	else
		face_list[0] = _hoops_GPCRGR;

	set = HI_Generate_Complex_Region_Set (count, points, _hoops_GPCRGR+1, face_list, _hoops_SGSIH);

	if (face_list != _hoops_APIGA)
		FREE_ARRAY (face_list, count+1, int);

	return set;
}

#endif




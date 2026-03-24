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
 * $Id: obf_tmp.txt 1.99 2010-10-20 02:09:49 covey Exp $
 */

#include "hoops.h"
#include "hi_proto.h"
#include "hpserror.h"

/* #_hoops_PPIP _hoops_HGRRGR */

#define _hoops_GSAHR		1.0e-6f
#define _hoops_IGRRGR	1.0e-10f


typedef struct _hoops_IGGIR {
	Point						point;
	int							index;
	float						u, v;			/* _hoops_SPRSH */
	Intersection const *		_hoops_RSPSA;
} _hoops_CGRRGR;

typedef struct _hoops_SGRRGR {
	struct _hoops_SGRRGR		*next;
	_hoops_CGRRGR						*vertex;
} _hoops_GRRRGR;

typedef struct _hoops_CGGIR {
	struct _hoops_CGGIR		*next, *prev;	/* _hoops_RRRRGR _hoops_CCHHR _hoops_HIGR _hoops_GPHHR */
	_hoops_GRRRGR		*vertices;		/* _hoops_IRS _hoops_RRGC _hoops_IIGR _hoops_GIHA _hoops_HCSPR _hoops_GGSR _hoops_HII _hoops_ISPP _hoops_PPSR */
	_hoops_CGRRGR				*_hoops_RCSHR;		/* _hoops_RSSA _hoops_SAHR _hoops_GRHCP _hoops_RH _hoops_SCIA _hoops_IIGR _hoops_RH _hoops_RRGC */
	_hoops_CGRRGR				*origin;		/* */
	bool				_hoops_ARRRGR;		/* _hoops_ISHA _hoops_HRGR _hoops_RAAP _hoops_PPAP _hoops_IIGR _hoops_IRS _hoops_PSAI */
} _hoops_PRRRGR;


/* _hoops_SRS _hoops_AIAA _hoops_PAPR _hoops_GAR _hoops_SIH _hoops_HRRRGR _hoops_RAAP & _hoops_RPHR _hoops_PAAA */
#define _hoops_HIGRGR			0x00	/* _hoops_RSIPR _hoops_HRGR _hoops_PIGRGR */
#define _hoops_IRRRGR		0x01
#define _hoops_CRRRGR		0x02
#define _hoops_CGHAS			0x03	/* _hoops_GIPR _hoops_CHR _hoops_PIGRGR */
#define _hoops_SRRRGR			0x04
#define _hoops_CSSPS		0x05

local int _hoops_GARRGR[] = {
		_hoops_HIGRGR, _hoops_CRRRGR, _hoops_IRRRGR, _hoops_CGHAS,
		_hoops_SRRRGR, _hoops_CSSPS
	};


/* _hoops_PRCGH _hoops_HRGR _hoops_SPR _hoops_PAR _hoops_RRI _hoops_RSSA _hoops_RARRGR _hoops_IRS _hoops_AARRGR _hoops_CSASI */

typedef struct _hoops_PARRGR {
	struct _hoops_PARRGR		*next;
	_hoops_CGRRGR				*left, *right;			/* _hoops_HSHSH _hoops_IIGR _hoops_RH _hoops_PRCGH (_hoops_AAGAI _hoops_PSHR _hoops_PPSR) */
	_hoops_CGRRGR				*_hoops_HARRGR, *_hoops_IARRGR;/* _hoops_RSSA _hoops_SAHR _hoops_GRHCP _hoops_RH _hoops_HCPA _hoops_IIGR _hoops_RGR _hoops_PRCGH */
	int					type;
	bool				_hoops_CARRGR;
} _hoops_SARRGR, *_hoops_GPRRGR;





/* _hoops_PIH _hoops_SGS _hoops_IRHS _hoops_IS _hoops_SHH _hoops_HHPA _hoops_IS _hoops_SGSS _hoops_PSCH */

typedef struct _hoops_RPRRGR {
	_hoops_ARCIH				action;
	void *						user_data;

	int							_hoops_APRRGR;

	int							axis;
	_hoops_GRRRGR *				_hoops_PPRRGR;
	_hoops_SARRGR *						_hoops_IRCGH;
	bool						_hoops_HHAHR;
} _hoops_HPRRGR;


#define QS_POINT_COMPARE(thing,f1,f2) \
		(thing[f1]->left->v > thing[f2]->left->v || \
		 thing[f1]->left->v == thing[f2]->left->v && \
		 thing[f1]->type >= thing[f2]->type)


#define QS_TYPE				_hoops_GPRRGR *				/* _hoops_RH _hoops_GPRR _hoops_IIGR _hoops_CARA _hoops_PAR _hoops_CRPR _hoops_SGS _hoops_ICGI _hoops_HCR _hoops_HSH */
#define QS_VAL(thing,a)		(thing[a]->left->v)		/* _hoops_HRS _hoops_RH _hoops_PIRA _hoops_IIGR _hoops_PCCP _hoops_IGCI _hoops_CCA _hoops_CIHA _hoops_IRS */
#define QS_COMPLEX_COMPARE(thing, f1,f2) QS_POINT_COMPARE(thing,f1,f2)
#define QS_SWAP(thing,a,b)	Swap (thing[a], thing[b]);

#include "utility/hqsort.h"								/* _hoops_RSSAR _hoops_IRS _hoops_API, "_hoops_CRAHH" _hoops_SGS _hoops_RAIA _hoops_RH _hoops_ARRS _hoops_CIGR */


local void _hoops_IPRRGR (
	_hoops_PRRRGR					*edge,
	_hoops_CGRRGR					*vertex,
	bool					_hoops_CPRRGR) {

	edge->vertices->vertex = vertex;

	if (_hoops_CPRRGR)
		edge->origin = vertex;
}




local void _hoops_RCHHR (
	_hoops_HPRRGR			*info,
	_hoops_CGRRGR					*first,
	_hoops_CGRRGR					*_hoops_IAGRA,
	_hoops_CGRRGR					*_hoops_IGSSA) {

	if (info->_hoops_HHAHR)
		(*info->action) (info->user_data, false,
						 &first->point, &_hoops_IGSSA->point, &_hoops_IAGRA->point,
						 first->index,	_hoops_IGSSA->index,  _hoops_IAGRA->index,
						 first->_hoops_RSPSA,
										_hoops_IGSSA->_hoops_RSPSA,
													   _hoops_IAGRA->_hoops_RSPSA);
	else
		(*info->action) (info->user_data, false,
						 &first->point, &_hoops_IAGRA->point, &_hoops_IGSSA->point,
						 first->index,	_hoops_IAGRA->index,	_hoops_IGSSA->index,
						 first->_hoops_RSPSA,
										_hoops_IAGRA->_hoops_RSPSA,
														_hoops_IGSSA->_hoops_RSPSA);
}


local void _hoops_SPRRGR (
	_hoops_HPRRGR			*info,
	_hoops_PRRRGR					*edge,
	_hoops_CGRRGR					*point,
	bool					_hoops_GHRRGR) {
	_hoops_GRRRGR			*_hoops_HHRAR,
							*_hoops_RHRRGR;

	_hoops_HHRAR = edge->vertices;
	if ((_hoops_RHRRGR = _hoops_HHRAR->next) != null) {
		do {
			/*
			 * _hoops_CGP _hoops_RH _hoops_SCIA _hoops_PGCR _hoops_RSSA _hoops_GPP _hoops_RH _hoops_PPAP (_hoops_HCPC _hoops_PPR _hoops_AHRRGR) _hoops_CHR _hoops_HAR
			 * _hoops_GPP _hoops_RH _hoops_PSHR _hoops_IRGGA, _hoops_PSCR _hoops_ISPR _hoops_RH _hoops_AGICR _hoops_HPASH _hoops_GAPA _hoops_RGR
			 * _hoops_ICRAR _hoops_PPSR _hoops_PPR _hoops_RH _hoops_SCIA _hoops_PPSR _hoops_PPR _hoops_RH _hoops_SCIA _hoops_PPSR _hoops_PPR _hoops_RH _hoops_SPS
			 * _hoops_PPSR.  _hoops_CGP _hoops_RH _hoops_AAPA _hoops_ICSHR _hoops_RHAP _hoops_HAR _hoops_PHRRGR _hoops_RH _hoops_GSSC, _hoops_PSCR _hoops_SR
			 * _hoops_SSSCP _hoops_PSRAR _hoops_GII _hoops_GASAR.
			 *			 @ _hoops_PPSR
			 *			/
			 *		   * _hoops_HCPC
			 *			\
			 *		  ...* _hoops_AHRRGR
			 */
			if (_hoops_HHRAR->vertex->v != _hoops_RHRRGR->vertex->v) {
				if ((point->u - _hoops_HHRAR->vertex->u) * (_hoops_HHRAR->vertex->v - _hoops_RHRRGR->vertex->v) >=
					(_hoops_HHRAR->vertex->u - _hoops_RHRRGR->vertex->u) * (point->v - _hoops_HHRAR->vertex->v)) break;
			}

			/* _hoops_CGP _hoops_RH _hoops_RRGC'_hoops_GRI _hoops_SCIA _hoops_PGCR _hoops_CHR _hoops_GPP _hoops_RH _hoops_PSHR _hoops_IRGGA, _hoops_PSCR _hoops_RPP _hoops_RH _hoops_SCIA _hoops_SPR _hoops_HRGR _hoops_RAAP
			 * _hoops_IIGR _hoops_RH _hoops_SPS, _hoops_PSCR _hoops_IHSA _hoops_PGGA _hoops_SR _hoops_HS _hoops_PCCP _hoops_GGICR _hoops_HHRRGR _hoops_PPR _hoops_SSSCP _hoops_PSRAR
			 * _hoops_GII _hoops_GASAR
			 *			 @ _hoops_PPSR
			 *			/
			 *		_hoops_HCPC *---* _hoops_AHRRGR
			 *		   .../
			 */
			else if (_hoops_RHRRGR->vertex->u > _hoops_HHRAR->vertex->u) break;

			/* _hoops_CGP _hoops_RH _hoops_RRGC'_hoops_GRI _hoops_SCIA _hoops_PGCR _hoops_CHR _hoops_ASPSR, _hoops_PSCR _hoops_GCHGA, _hoops_HIH _hoops_AA _hoops_HAR _hoops_PGSA _hoops_RH
			 * _hoops_SCPH.
			 *			 @ _hoops_PPSR
			 *			/
			 *		_hoops_HCPC * _hoops_AHRRGR
			 *	   .../
			 */
			else if (_hoops_RHRRGR->vertex->u == _hoops_HHRAR->vertex->u) {
				FREE (_hoops_HHRAR, _hoops_GRRRGR);
				_hoops_HHRAR = _hoops_RHRRGR;
				continue;
			}

			/* _hoops_HHPC, _hoops_SR _hoops_PAH _hoops_PGSA _hoops_RH _hoops_SCPH _hoops_PPR _hoops_GCHGA
			 *			 @ _hoops_PPSR
			 *			 |
			 *			 |
			 *			 * _hoops_HCPC
			 *			/
			 *		...* _hoops_AHRRGR
			 */
			_hoops_RCHHR (info, point, _hoops_HHRAR->vertex, _hoops_RHRRGR->vertex);

			FREE (_hoops_HHRAR, _hoops_GRRRGR);
			_hoops_HHRAR = _hoops_RHRRGR;
		} while ((_hoops_RHRRGR = _hoops_RHRRGR->next) != null);

		/* _hoops_RH _hoops_RPHR _hoops_ISHA _hoops_RRGPR _hoops_CAS _hoops_SR _hoops_CSSRH _hoops_IHRRGR */
		edge->vertices = _hoops_HHRAR;
	}

	if (edge->vertices->next == null) {
		/* _hoops_PGHC _hoops_ISHA _hoops_PIHA _hoops_SHH _hoops_CHRRGR */
		_hoops_HHRAR = edge->prev->vertices;
		if (_hoops_GHRRGR && (_hoops_RHRRGR = _hoops_HHRAR->next) != null) {
			_hoops_GRRRGR	*first = _hoops_HHRAR;

			do {
				if (_hoops_HHRAR->vertex->u != _hoops_RHRRGR->vertex->u ||
					_hoops_HHRAR->vertex->v != _hoops_RHRRGR->vertex->v)
					_hoops_RCHHR (info, point, _hoops_RHRRGR->vertex, _hoops_HHRAR->vertex);

				if (_hoops_HHRAR != first) FREE (_hoops_HHRAR, _hoops_GRRRGR);
				_hoops_HHRAR = _hoops_RHRRGR;
			} while ((_hoops_RHRRGR = _hoops_RHRRGR->next) != null);

			FREE (_hoops_HHRAR, _hoops_GRRRGR);
			edge->prev->vertices->next = null;
			_hoops_IPRRGR (edge, first->vertex, false);
		}


		/*
		 *	_hoops_IIH'_hoops_GRI _hoops_PSP _hoops_ISHA		  @ _hoops_PPSR
		 *	   _hoops_RAAP _hoops_RCAPR->	 /
		 *					*	/
		 *				   / \ /
		 *			   ...*	  *	 <- _hoops_ISHA
		 */
		if  (edge->prev->_hoops_RCSHR == null) {
			do {
				/* _hoops_HASIR _hoops_ISHA _hoops_PSAI -- _hoops_SR _hoops_HHGC _hoops_IS _hoops_HASIR _hoops_RGR _hoops_SPR _hoops_PPR _hoops_PGHC,
				 * _hoops_HIH _hoops_IIH _hoops_GHCA _hoops_SHH _hoops_PRCHR, _hoops_HIS _hoops_HASIR _hoops_GCPC _hoops_PPR _hoops_GCPC->_hoops_GCPC,
				 * _hoops_HSACA _hoops_RH _hoops_RRGC _hoops_HII _hoops_GCPC->_hoops_GCPC _hoops_IS _hoops_ARI */
				_hoops_PRRRGR *		victim = edge->prev;

				FREE (edge->vertices, _hoops_GRRRGR);
				FREE (victim->vertices, _hoops_GRRRGR);
				edge->vertices = victim->prev->vertices;
				
				edge->prev = victim->prev->prev;
				edge->prev->next = edge;

				FREE (victim->prev, _hoops_PRRRGR);
				FREE (victim, _hoops_PRRRGR);
			} while (edge->prev->_hoops_RCSHR == null);

			// _hoops_CCA _hoops_SGCRP _hoops_SHRRGR _hoops_GCGSP, _hoops_GHCA _hoops_SHH _hoops_SHSS _hoops_IS _hoops_GASAR _hoops_HPPP _hoops_GRHCP
			_hoops_SPRRGR (info, edge, point, _hoops_GHRRGR);
		}
	}
}


local void _hoops_GIRRGR (
	_hoops_HPRRGR			*info,
	_hoops_PRRRGR					*edge,
	_hoops_CGRRGR					*point,
	bool					_hoops_GHRRGR) {
	_hoops_GRRRGR			*_hoops_HHRAR,
							*_hoops_RHRRGR;

	_hoops_HHRAR = edge->vertices;
	if ((_hoops_RHRRGR = _hoops_HHRAR->next) != null) {
		do {
			/*
			 * _hoops_CGP _hoops_RH _hoops_SCIA _hoops_PGCR _hoops_RSSA _hoops_GPP _hoops_RH _hoops_PPAP (_hoops_HCPC _hoops_PPR _hoops_AHRRGR) _hoops_CHR _hoops_HAR _hoops_GPP _hoops_RH
			 * _hoops_PSHR _hoops_IRGGA, _hoops_PSCR _hoops_ISPR _hoops_RH _hoops_AGICR _hoops_HPASH _hoops_GAPA _hoops_RGR _hoops_ICRAR _hoops_PPSR
			 * _hoops_PPR _hoops_RH _hoops_SCIA _hoops_PPSR _hoops_PPR _hoops_RH _hoops_SCIA _hoops_PPSR _hoops_PPR _hoops_RH _hoops_SPS _hoops_PPSR.	_hoops_CGP _hoops_RH _hoops_AAPA
			 * _hoops_ICSHR _hoops_RHAP _hoops_HAR _hoops_PHRRGR _hoops_RH _hoops_GSSC, _hoops_PSCR _hoops_SR _hoops_SSSCP _hoops_PSRAR _hoops_GII _hoops_GASAR.
			 *			 @ _hoops_PPSR
			 *			  \
			 *			_hoops_HCPC *
			 *			  /
			 *		 _hoops_AHRRGR *...
			 */
			if (_hoops_HHRAR->vertex->v != _hoops_RHRRGR->vertex->v) {
				if ((point->u - _hoops_HHRAR->vertex->u) * (_hoops_HHRAR->vertex->v - _hoops_RHRRGR->vertex->v) <=
					(_hoops_HHRAR->vertex->u - _hoops_RHRRGR->vertex->u) * (point->v - _hoops_HHRAR->vertex->v)) break;
			}

			/* _hoops_CGP _hoops_RH _hoops_RRGC'_hoops_GRI _hoops_SCIA _hoops_PGCR _hoops_CHR _hoops_GPP _hoops_RH _hoops_PSHR _hoops_IRGGA, _hoops_PSCR _hoops_RPP _hoops_RH _hoops_SCIA _hoops_SPR _hoops_HRGR _hoops_RPHR
			 * _hoops_IIGR _hoops_RH _hoops_SPS, _hoops_PSCR _hoops_IHSA _hoops_PGGA _hoops_SR _hoops_HS _hoops_PCCP _hoops_GGICR _hoops_HHRRGR _hoops_PPR _hoops_SSSCP _hoops_PSRAR
			 * _hoops_GII _hoops_GASAR
			 *			 @ _hoops_PPSR
			 *			  \
			 *	   _hoops_AHRRGR *---* _hoops_HCPC
			 *			\...
			 */
			else if (_hoops_RHRRGR->vertex->u < _hoops_HHRAR->vertex->u) break;

			/* _hoops_CGP _hoops_RH _hoops_RRGC'_hoops_GRI _hoops_SCIA _hoops_PGCR _hoops_CHR _hoops_ASPSR, _hoops_PSCR _hoops_GCHGA, _hoops_HIH _hoops_AA _hoops_HAR _hoops_PGSA _hoops_RH
			 * _hoops_SCPH.
			 *			 @ _hoops_PPSR
			 *			  \
			 *			_hoops_HCPC * _hoops_AHRRGR
			 *				\...
			 */
			else if (_hoops_RHRRGR->vertex->u == _hoops_HHRAR->vertex->u) {
				FREE (_hoops_HHRAR, _hoops_GRRRGR);
				_hoops_HHRAR = _hoops_RHRRGR;
				continue;
			}

			/* _hoops_HHPC, _hoops_SR _hoops_PAH _hoops_PGSA _hoops_RH _hoops_SCPH _hoops_PPR _hoops_GCHGA
			 *			 @ _hoops_PPSR
			 *			 |
			 *			 |
			 *		  _hoops_HCPC *
			 *			  \
			 *		   _hoops_AHRRGR *...
			 */
			_hoops_RCHHR (info, point, _hoops_RHRRGR->vertex, _hoops_HHRAR->vertex);

			FREE (_hoops_HHRAR, _hoops_GRRRGR);
			_hoops_HHRAR = _hoops_RHRRGR;
		} while ((_hoops_RHRRGR = _hoops_RHRRGR->next) != null);

		/* _hoops_RH _hoops_RAAP _hoops_ISHA _hoops_RRGPR _hoops_CAS _hoops_SR _hoops_CSSRH _hoops_IHRRGR */
		edge->vertices = _hoops_HHRAR;
	}

	if (edge->vertices->next == null) {
		_hoops_HHRAR = edge->next->vertices;
		if (_hoops_GHRRGR && (_hoops_RHRRGR = _hoops_HHRAR->next) != null) {
			_hoops_GRRRGR	*first = _hoops_HHRAR;

			do {
				if (_hoops_HHRAR->vertex->u != _hoops_RHRRGR->vertex->u ||
					_hoops_HHRAR->vertex->v != _hoops_RHRRGR->vertex->v)
					_hoops_RCHHR (info, point, _hoops_HHRAR->vertex, _hoops_RHRRGR->vertex);

				if (_hoops_HHRAR != first) FREE (_hoops_HHRAR, _hoops_GRRRGR);
				_hoops_HHRAR = _hoops_RHRRGR;
			} while ((_hoops_RHRRGR = _hoops_RHRRGR->next) != null);

			FREE (_hoops_HHRAR, _hoops_GRRRGR);
			edge->next->vertices->next = null;
			_hoops_IPRRGR (edge, first->vertex, false);
		}

		/*
		 *		_hoops_PPSR @			_hoops_IIH'_hoops_GRI _hoops_PSP _hoops_ISHA
		 *			   \	<- _hoops_RPHR _hoops_RCAPR
		 *				\	*
		 *				 \ / \
		 *		   _hoops_ISHA-> *	  *...
		 */
		if (edge->next->_hoops_RCSHR == null) {
			do {
				/* _hoops_HASIR _hoops_ISHA _hoops_PSAI -- _hoops_SR _hoops_HHGC _hoops_IS _hoops_HASIR _hoops_RGR _hoops_SPR _hoops_PPR _hoops_SPS,
				 * _hoops_HIH _hoops_IIH _hoops_GHCA _hoops_SHH _hoops_PRCHR, _hoops_HIS _hoops_HASIR _hoops_SPS _hoops_PPR _hoops_SPS->_hoops_SPS,
				 * _hoops_HSACA _hoops_RH _hoops_RRGC _hoops_HII _hoops_SPS->_hoops_SPS _hoops_IS _hoops_ARI */
				_hoops_PRRRGR *		victim = edge->next;

				FREE (edge->vertices, _hoops_GRRRGR);
				FREE (victim->vertices, _hoops_GRRRGR);
				edge->vertices = victim->next->vertices;
				
				edge->next = victim->next->next;
				edge->next->prev = edge;

				FREE (victim->next, _hoops_PRRRGR);
				FREE (victim, _hoops_PRRRGR);
			} while (edge->next->_hoops_RCSHR == null);

			// _hoops_CCA _hoops_SGCRP _hoops_SHRRGR _hoops_GCGSP, _hoops_GHCA _hoops_SHH _hoops_SHSS _hoops_IS _hoops_GASAR _hoops_HPPP _hoops_GRHCP
			_hoops_GIRRGR (info, edge, point, _hoops_GHRRGR);
		}
	}
}




/*
 * _hoops_PASSC _hoops_IRS _hoops_GPHA "_hoops_PPSR" _hoops_CIAA _hoops_SCIA _hoops_IIGR _hoops_RRGC "_hoops_HIGR"
 */
local void _hoops_RIRRGR (
	_hoops_GRRRGR	**list,
	_hoops_CGRRGR			*vertex) {
	_hoops_GRRRGR	*_hoops_HHRAR;

	ALLOC (_hoops_HHRAR, _hoops_GRRRGR);
	_hoops_HHRAR->vertex = vertex;
	_hoops_HHRAR->next = *list;
	*list = _hoops_HHRAR;
}

local void _hoops_RHPHI (
	_hoops_PRRRGR *			edge,
	_hoops_CGRRGR *		vertex,
	bool			_hoops_CPRRGR) {

	if (edge->vertices == null || vertex != edge->vertices->vertex)
		_hoops_RIRRGR (&edge->vertices, vertex);
	if (_hoops_CPRRGR)
		edge->origin = vertex;
}




typedef struct _hoops_AIRRGR {
	Point		center, scale;
}	_hoops_PIRRGR;


#define X_AXIS 0
#define _hoops_HIRRGR 1
#define _hoops_IIRRGR 2

local _hoops_CGRRGR * _hoops_CIRRGR (
	Point const	*	points,
	int				index,
	int				axis,
	_hoops_PIRRGR const	*_hoops_SIRRGR,
	_hoops_GRRRGR	**list) {
	_hoops_CGRRGR			*pt;
	Point			tmp;

	ALLOC (pt, _hoops_CGRRGR);
	if (index >= 0) {
		pt->point.x = points[index].x;
		pt->point.y = points[index].y;
		pt->point.z = points[index].z;
	}
	else {
		pt->point.x = points->x;
		pt->point.y = points->y;
		pt->point.z = points->z;
	}
	pt->index = index;

	tmp = pt->point;
	if (_hoops_SIRRGR != null) {
		tmp.x = (tmp.x - _hoops_SIRRGR->center.x) * _hoops_SIRRGR->scale.x;
		tmp.y = (tmp.y - _hoops_SIRRGR->center.y) * _hoops_SIRRGR->scale.y;
		tmp.z = (tmp.z - _hoops_SIRRGR->center.z) * _hoops_SIRRGR->scale.z;
	}

	switch (axis) {
		case X_AXIS: {
			pt->u = tmp.y;
			pt->v = tmp.z;
		}	break;

		case _hoops_HIRRGR: {
			pt->u = tmp.z;
			pt->v = tmp.x;
		}	break;

		case _hoops_IIRRGR: {
			pt->u = tmp.x;
			pt->v = tmp.y;
		}	break;
	};
	pt->_hoops_RSPSA = null;

	_hoops_RIRRGR (list, pt);
	return pt;
}


/* _hoops_GCRRGR _hoops_HRGR _hoops_RGAR _hoops_IGI _hoops_IH _hoops_RPGCA _hoops_PRHI _hoops_RSSA (_hoops_ARRSH) */
local _hoops_CGRRGR * _hoops_RCRRGR (
	_hoops_HPRRGR *	info,
	_hoops_CGRRGR *		vertex) {
	_hoops_CGRRGR *		_hoops_SICRA;

	_hoops_SICRA = _hoops_CIRRGR (&vertex->point, --info->_hoops_APRRGR,
								info->axis, null, &info->_hoops_PPRRGR);
	/* _hoops_ACRRGR() _hoops_SAHR _hoops_PCIAR _hoops_HII _hoops_RH _hoops_PPSR, _hoops_SR _hoops_RRP _hoops_RH _hoops_CPPSR _hoops_HSH */
	_hoops_SICRA->u = vertex->u;
	_hoops_SICRA->v = vertex->v;

	return _hoops_SICRA;
}

local _hoops_SARRGR * _hoops_PCRRGR (
	_hoops_HPRRGR *	info,
	_hoops_CGRRGR *		vertex) {
	_hoops_SARRGR *			span;

	ALLOC (span, _hoops_SARRGR);
	span->type = _hoops_CSSPS;
	span->left = span->right = null;
	span->left = span->right = _hoops_RCRRGR (info, vertex);

	return span;
}


local bool _hoops_HCRRGR (
	_hoops_CGRRGR *		test,
	_hoops_CGRRGR *		_hoops_ICRRGR,
	_hoops_PRRRGR *			edge,
	bool			_hoops_CCRRGR) {
	_hoops_CGRRGR *		lower = edge->vertices->vertex;
	_hoops_CGRRGR *		upper = edge->_hoops_RCSHR;

	if (Abs (test->v - lower->v) < _hoops_GSAHR) {
		if (test->u < lower->u)
			return true;
		else if (test->u == lower->u) {
			float		_hoops_ISPI = (_hoops_ICRRGR->u - test->u) * (upper->v - lower->v);
			float		_hoops_CSPI = (upper->u - lower->u) * (_hoops_ICRRGR->v - test->v);

			if (_hoops_ISPI < _hoops_CSPI	 ||	 _hoops_CCRRGR && _hoops_ISPI < _hoops_CSPI+_hoops_GSAHR)
				return true;
		}
	}
	else if (Abs (test->v - upper->v) < _hoops_GSAHR) {
		if (test->u < upper->u)
			return true;
		else if (test->u == upper->u) {
			float		_hoops_ISPI = (_hoops_ICRRGR->u - test->u) * (upper->v - lower->v);
			float		_hoops_CSPI = (upper->u - lower->u) * (_hoops_ICRRGR->v - test->v);

			if (_hoops_ISPI < _hoops_CSPI	 ||	 _hoops_CCRRGR && _hoops_ISPI < _hoops_CSPI+_hoops_GSAHR)
				return true;
		}
	}
	else {
		float		_hoops_ISPI = (test->u - lower->u) / (test->v - lower->v);
		float		_hoops_CSPI = (upper->u - lower->u) / (upper->v - lower->v);

		if (_hoops_ISPI < _hoops_CSPI-_hoops_GSAHR)
			return true;

		if (_hoops_ISPI < _hoops_CSPI+_hoops_GSAHR) {
			_hoops_ISPI = (_hoops_ICRRGR->u - test->u) * (upper->v - lower->v);
			_hoops_CSPI = (upper->u - lower->u) * (_hoops_ICRRGR->v - test->v);

			if (_hoops_ISPI < _hoops_CSPI	 ||	 _hoops_CCRRGR && _hoops_ISPI < _hoops_CSPI+_hoops_GSAHR)
				return true;
		}
	}

	return false;
}



local void _hoops_SCRRGR (
		Intersection *		_hoops_RSPSA,
		int						index,
		_hoops_CGRRGR *				lower,
		_hoops_CGRRGR *				upper,
		float					t) {

	if (lower->index < 0) {
		int			 _hoops_GSRRGR = lower->_hoops_RSPSA->_hoops_PICHR[0]._hoops_HCIGI;

		if (upper->index >= 0 && _hoops_GSRRGR == upper->index ||
			upper->index < 0 &&
			(_hoops_GSRRGR == upper->_hoops_RSPSA->_hoops_PICHR[0]._hoops_HCIGI ||
			 _hoops_GSRRGR == upper->_hoops_RSPSA->_hoops_PICHR[1]._hoops_HCIGI)) {
			_hoops_RSPSA->_hoops_PICHR[index].start =
							lower->_hoops_RSPSA->_hoops_PICHR[0].start;
			_hoops_RSPSA->_hoops_PICHR[index]._hoops_PCIGI =
							lower->_hoops_RSPSA->_hoops_PICHR[0]._hoops_PCIGI;
			t = lower->_hoops_RSPSA->_hoops_PICHR[0]._hoops_RCGCR +
				t * (1.0f - lower->_hoops_RSPSA->_hoops_PICHR[0]._hoops_RCGCR);
		}
		else {
			_hoops_RSPSA->_hoops_PICHR[index].start =
							lower->_hoops_RSPSA->_hoops_PICHR[1].start;
			_hoops_RSPSA->_hoops_PICHR[index]._hoops_PCIGI =
							lower->_hoops_RSPSA->_hoops_PICHR[1]._hoops_PCIGI;
			t = lower->_hoops_RSPSA->_hoops_PICHR[1]._hoops_RCGCR +
				t * (1.0f - lower->_hoops_RSPSA->_hoops_PICHR[1]._hoops_RCGCR);
		}
	}
	else {
		_hoops_RSPSA->_hoops_PICHR[index].start = &lower->point;
		_hoops_RSPSA->_hoops_PICHR[index]._hoops_PCIGI = lower->index;
	}

	if (upper->index < 0) {
		int			 _hoops_RSRRGR = upper->_hoops_RSPSA->_hoops_PICHR[0]._hoops_PCIGI;

		if (lower->index >= 0 && _hoops_RSRRGR == lower->index ||
			lower->index < 0 &&
			(_hoops_RSRRGR == lower->_hoops_RSPSA->_hoops_PICHR[0]._hoops_PCIGI ||
			 _hoops_RSRRGR == lower->_hoops_RSPSA->_hoops_PICHR[1]._hoops_PCIGI)) {
			_hoops_RSPSA->_hoops_PICHR[index].end =
							upper->_hoops_RSPSA->_hoops_PICHR[0].end;
			_hoops_RSPSA->_hoops_PICHR[index]._hoops_HCIGI =
							upper->_hoops_RSPSA->_hoops_PICHR[0]._hoops_HCIGI;
			t *= upper->_hoops_RSPSA->_hoops_PICHR[0]._hoops_RCGCR;
		}
		else {
			_hoops_RSPSA->_hoops_PICHR[index].end =
							upper->_hoops_RSPSA->_hoops_PICHR[1].end;
			_hoops_RSPSA->_hoops_PICHR[index]._hoops_HCIGI =
							upper->_hoops_RSPSA->_hoops_PICHR[1]._hoops_HCIGI;
			t *= upper->_hoops_RSPSA->_hoops_PICHR[1]._hoops_RCGCR;
		}
	}
	else {
		_hoops_RSPSA->_hoops_PICHR[index].end = &upper->point;
		_hoops_RSPSA->_hoops_PICHR[index]._hoops_HCIGI = upper->index;
	}

	_hoops_RSPSA->_hoops_PICHR[index]._hoops_RCGCR = t;
}

local _hoops_CGRRGR * _hoops_ASRRGR (
	_hoops_HPRRGR *	info,
	_hoops_PRRRGR *			edge,
	_hoops_SARRGR *			span) {
	_hoops_CGRRGR *		lower = edge->vertices->vertex;
	_hoops_CGRRGR *		upper = edge->_hoops_RCSHR;
	_hoops_CGRRGR			_hoops_IPPSH;
	float			t;
	_hoops_CGRRGR *		_hoops_SICRA;
	Intersection *_hoops_RSPSA;

	if (lower->v == upper->v) {
		/* _hoops_PAHA'_hoops_RA _hoops_IHPS, _hoops_HIH _hoops_SAHR _hoops_IS _hoops_SRCH _hoops_HHGS... */
		return upper;
	}

	t = (span->left->v - lower->v) / (upper->v - lower->v);

	_hoops_IPPSH.point.x = lower->point.x + t * (upper->point.x - lower->point.x);
	_hoops_IPPSH.point.y = lower->point.y + t * (upper->point.y - lower->point.y);
	_hoops_IPPSH.point.z = lower->point.z + t * (upper->point.z - lower->point.z);
	_hoops_IPPSH.u = lower->u + t * (upper->u - lower->u);
	_hoops_IPPSH.v = span->left->v;

	_hoops_SICRA = _hoops_RCRRGR (info, &_hoops_IPPSH);

	ALLOC (_hoops_RSPSA, Intersection);
	_hoops_SICRA->_hoops_RSPSA = _hoops_RSPSA;
	_hoops_RSPSA->_hoops_PICHR[0].start = &span->left->point;
	_hoops_RSPSA->_hoops_PICHR[0].end	 = &span->right->point;
	_hoops_RSPSA->_hoops_PICHR[0]._hoops_PCIGI = span->left->index;
	_hoops_RSPSA->_hoops_PICHR[0]._hoops_HCIGI   = span->right->index;
	if (span->left->point.x < span->right->point.x)
		_hoops_RSPSA->_hoops_PICHR[0]._hoops_RCGCR = (_hoops_IPPSH.u - span->left->u) /
										  (span->right->u - span->left->u);
	else
		_hoops_RSPSA->_hoops_PICHR[0]._hoops_RCGCR = 0.0f;

	_hoops_SCRRGR (_hoops_RSPSA, 1, lower, upper, t);

	return _hoops_SICRA;
}


local void _hoops_PSRRGR (
	_hoops_HPRRGR *	info,
	_hoops_PRRRGR *			left,
	_hoops_PRRRGR *			right,
	float			_hoops_HSRRGR,
	float			_hoops_ISRRGR) {
	_hoops_CGRRGR *		ll = left->origin;
	_hoops_CGRRGR *		_hoops_CSRRGR = left->_hoops_RCSHR;
	_hoops_CGRRGR *		_hoops_SSRRGR = right->origin;
	_hoops_CGRRGR *		_hoops_GGARGR = right->_hoops_RCSHR;
	float			_hoops_RGARGR, _hoops_AGARGR, _hoops_PGARGR, _hoops_HGARGR;
	float			_hoops_IGARGR, _hoops_CGARGR, _hoops_SGARGR, _hoops_GRARGR;
	float			_hoops_SSHGA, s, t;
	float			v;
	_hoops_CGRRGR			_hoops_IPPSH;
	_hoops_SARRGR *			span;
	_hoops_SARRGR **		_hoops_ASRGR;
	Intersection *_hoops_RSPSA;

	if (_hoops_CSRRGR == null || _hoops_GGARGR == null || ll == _hoops_SSRRGR || _hoops_CSRRGR == _hoops_GGARGR)
		return;

	_hoops_RGARGR = _hoops_CSRRGR->u - ll->u;
	_hoops_AGARGR = _hoops_CSRRGR->v - ll->v;
	_hoops_PGARGR = _hoops_GGARGR->u - ll->u;
	_hoops_HGARGR = _hoops_GGARGR->v - ll->v;

	if (_hoops_RGARGR*_hoops_HGARGR < _hoops_AGARGR*_hoops_PGARGR)		/* _hoops_HRGR _hoops_RPHR _hoops_RCAPR _hoops_ISGR _hoops_RAAP _hoops_ISHA? */
		return;

	_hoops_IGARGR = _hoops_GGARGR->u - _hoops_SSRRGR->u;
	_hoops_CGARGR = _hoops_GGARGR->v - _hoops_SSRRGR->v;
	_hoops_SGARGR = _hoops_SSRRGR->u - ll->u;
	_hoops_GRARGR = _hoops_SSRRGR->v - ll->v;

	_hoops_SSHGA = _hoops_IGARGR*_hoops_AGARGR - _hoops_RGARGR*_hoops_CGARGR;
	if (-_hoops_IGRRGR < _hoops_SSHGA	&& _hoops_SSHGA < _hoops_IGRRGR)		/* _hoops_GGAIA? */
		return;

	_hoops_SSHGA = 1.0f / _hoops_SSHGA;

	s = (_hoops_IGARGR*_hoops_GRARGR - _hoops_SGARGR*_hoops_CGARGR) * _hoops_SSHGA;
	t = (_hoops_RGARGR*_hoops_GRARGR - _hoops_SGARGR*_hoops_AGARGR) * _hoops_SSHGA;

	if (s < _hoops_HSRRGR || t < _hoops_ISRRGR)
		return;

	if (_hoops_CSRRGR->index < 0) {
		if (s > 1.0f)
			return;
	}
	else {
		if (s >= 1.0f-_hoops_GSAHR)
			return;
	}

	if (_hoops_GGARGR->index < 0) {
		if (t > 1.0f)
			return;
	}
	else {
		if (t >= 1.0f-_hoops_GSAHR)
			return;
	}

	v = ll->v + s * (_hoops_CSRRGR->v - ll->v);

	_hoops_ASRGR = &info->_hoops_IRCGH;
	_hoops_PCCAR {
		_hoops_SARRGR *			test = *_hoops_ASRGR;

		if (test == null || v <= test->left->v+_hoops_GSAHR)
			break;

		_hoops_ASRGR = &test->next;
	}
	_hoops_PCCAR {
		_hoops_SARRGR *			test = *_hoops_ASRGR;

		if (test == null || v <= test->left->v+_hoops_GSAHR ||
			test->type != _hoops_CSSPS ||
			test->left->index == left->_hoops_RCSHR->index ||
			test->left->index == right->_hoops_RCSHR->index)
			break;

		if (test->type == _hoops_CSSPS &&
			test->_hoops_HARRGR->index == right->_hoops_RCSHR->index &&
			test->_hoops_IARRGR->index == left->_hoops_RCSHR->index &&
			test->left->v == v)			/* _hoops_AIAH _hoops_HS _hoops_SCH */
			return;

		_hoops_ASRGR = &test->next;
	}

	_hoops_IPPSH.point.x = ll->point.x + s * (_hoops_CSRRGR->point.x - ll->point.x);
	_hoops_IPPSH.point.y = ll->point.y + s * (_hoops_CSRRGR->point.y - ll->point.y);
	_hoops_IPPSH.point.z = ll->point.z + s * (_hoops_CSRRGR->point.z - ll->point.z);
	_hoops_IPPSH.u = ll->u + s * (_hoops_CSRRGR->u - ll->u);
	_hoops_IPPSH.v = v;
	span = _hoops_PCRRGR (info, &_hoops_IPPSH);
	span->next = *_hoops_ASRGR;
	*_hoops_ASRGR = span;
	span->_hoops_HARRGR = right->_hoops_RCSHR;
	span->_hoops_IARRGR = left->_hoops_RCSHR;
	left->_hoops_RCSHR = right->_hoops_RCSHR = span->left;

	ALLOC (_hoops_RSPSA, Intersection);
	span->left->_hoops_RSPSA = _hoops_RSPSA;
	_hoops_SCRRGR (_hoops_RSPSA, 0, ll, _hoops_CSRRGR, s);
	_hoops_SCRRGR (_hoops_RSPSA, 1, _hoops_SSRRGR, _hoops_GGARGR, t);
}




local _hoops_PRRRGR * _hoops_RRARGR (
	_hoops_PRRRGR *			edge) {

	while ((edge = edge->next) != null) {
		if (edge->_hoops_RCSHR != null)
			return edge;
	}

	return null;
}




local int _hoops_ARARGR (
	Vector const		*normal,
	Point const		*points,
	int	const			*face_list) {

	/*
	 * _hoops_CGIC _hoops_RH _hoops_IRSS _hoops_AARGR _hoops_IS _hoops_RH _hoops_PHCR _hoops_IPPA.
	 * _hoops_SCH'_hoops_GRI _hoops_RH _hoops_IRSS _hoops_ICRP _hoops_SGGAR _hoops_RGCGA _hoops_IS _hoops_RH _hoops_HSSP _hoops_GSSR.
	 * _hoops_PIP _hoops_SGS _hoops_SR'_hoops_ASAR _hoops_RGAR _hoops_GPIHR _hoops_GGR _hoops_RH _hoops_GSSR _hoops_HSCHS
	 * _hoops_CRGR _hoops_RH _hoops_SRS _hoops_RCIH - _hoops_SCH'_hoops_GRI _hoops_RCAC _hoops_IS _hoops_RPGP _hoops_IIH.
	 */
	if (normal != null &&
		(normal->x != 0.0f || normal->y != 0.0f || normal->z != 0.0f)) {
		float	ax = Abs (normal->x);
		float	_hoops_RHACA = Abs (normal->y);
		float	_hoops_AHACA = Abs (normal->z);
		if (ax > _hoops_RHACA) {
			if (_hoops_AHACA > ax) return _hoops_IIRRGR;
			else return X_AXIS;
		}
		else {
			if (_hoops_AHACA > _hoops_RHACA) return _hoops_IIRRGR;
			else return _hoops_HIRRGR;
		}
	}
	else {
		/* _hoops_CSH _hoops_GSSR _hoops_RAGA - _hoops_GRAS _hoops_GSSR _hoops_IS _hoops_SRS _hoops_HAPR _hoops_PAPR.
		 */
		Point		const *prev;
		Point		const *point;
		int				const *item = face_list + 1;
		int				const *end = item + *face_list;
		float			a = 0.0f, b = 0.0f, c = 0.0f;

		/* _hoops_PGGC _hoops_SCAHR _hoops_HIAHR */
		prev = points + *item++;
		while (item != end) {
			point = points + *item++;
			a += (point->y + prev->y) * (point->z - prev->z);
			b += (point->z + prev->z) * (point->x - prev->x);
			c += (point->x + prev->x) * (point->y - prev->y);
			prev = point;
		}
		/* _hoops_GA'_hoops_RA _hoops_IPIHR _hoops_PRARGR */
		item = face_list + 1;	/* _hoops_ISSC _hoops_IS _hoops_RH _hoops_HSPP */
		point = points + *item++;
		a += (point->y + prev->y) * (point->z - prev->z);
		b += (point->z + prev->z) * (point->x - prev->x);
		c += (point->x + prev->x) * (point->y - prev->y);

		/* _hoops_IH _hoops_ISCP _hoops_AHAR, _hoops_RGAR _hoops_HIHHR _hoops_HRARGR */
		if (a < 0.0f) a = -a;
		if (b < 0.0f) b = -b;
		if (c < 0.0f) c = -c;

		/* _hoops_PSSSR _hoops_IH _hoops_RAGII _hoops_ARAR _hoops_SGS _hoops_RCPS _hoops_GH _hoops_AHHR (_hoops_IH _hoops_HAGAR, _hoops_RRHP _hoops_IRARGR-_hoops_GGGRA) */
		if (a < _hoops_GSAHR && b < _hoops_GSAHR && c < _hoops_GSAHR) {
			/* _hoops_SAHR _hoops_SGH _hoops_PA, _hoops_HPPR _hoops_IS _hoops_SSS _hoops_IRS _hoops_SHHP _hoops_HPAHR _hoops_IGIAR _hoops_RH _hoops_ISHA */
			Point		const *next;

			while (item != end) {
				next = points + *item++;

				a = (next->y - point->y) * (point->z - prev->z);
				b = (next->z - point->z) * (point->x - prev->x);
				c = (next->x - point->x) * (point->y - prev->y);

				/* _hoops_IH _hoops_ISCP _hoops_AHAR, _hoops_RGAR _hoops_HIHHR _hoops_HRARGR */
				if (a < 0.0f) a = -a;
				if (b < 0.0f) b = -b;
				if (c < 0.0f) c = -c;

				/* _hoops_RHAP _hoops_SCH _hoops_IHSH _hoops_RIRA _hoops_RAPR? */
				if (a > _hoops_IGRRGR || b > _hoops_IGRRGR || c > _hoops_IGRRGR)
					break;

				prev = point;
				point = next;
			}
		}

		/* _hoops_RPGP _hoops_IH _hoops_RH _hoops_AASC _hoops_CCIR */
		if (a > b) {
			if (c > a) return _hoops_IIRRGR;
			else return X_AXIS;
		}
		else {
			if (c > b) return _hoops_IIRRGR;
			else return _hoops_HIRRGR;
		}
	}
}


local void _hoops_CRARGR (
	_hoops_PRRRGR *			edge) {
	_hoops_GRRRGR * _hoops_HHRAR;

	while ((_hoops_HHRAR = edge->vertices) != null) {
		edge->vertices = _hoops_HHRAR->next;
		FREE (_hoops_HHRAR, _hoops_GRRRGR);
	}
}


#ifdef _hoops_SRARGR
#	include <stdio.h>	/* _hoops_IH _hoops_SPCS _hoops_GGSGS _hoops_RGAP _hoops_CAPP */
#	define _hoops_GAARGR(_hoops_RAARGR) do {											 \
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, \
								_hoops_RAARGR);									 \
			_hoops_AAARGR = true; goto _hoops_HPAGR;								 \
		} while (0)
#else
#	define _hoops_GAARGR(_hoops_RAARGR) do { _hoops_AAARGR = true; goto _hoops_HPAGR; } while (0)
#endif


local bool _hoops_PAARGR (
	Point		const *points,
	Vector		const *normal,
	int				const *face_list,
	int				const *_hoops_ICCIH,
	_hoops_ARCIH		triangle_action,
	void					*user_data) {
	_hoops_SARRGR					*span=0;
	int						_hoops_HAARGR = 0;
	_hoops_PRRRGR					*_hoops_GRCPR = null;
	_hoops_PRRRGR					*edge;
	_hoops_PRRRGR					*current;
	_hoops_HPRRGR			info;
	bool				_hoops_AAARGR = false;
	float					_hoops_RPIS;
	_hoops_PIRRGR				_hoops_SIRRGR;

	info.action = triangle_action;
	info.user_data = user_data;
	info._hoops_APRRGR = 0;
	info.axis = _hoops_ARARGR (normal, points, face_list);
	info._hoops_IRCGH = null;
	info._hoops_PPRRGR = null;

	/* _hoops_CGIC _hoops_CSRA _hoops_IH _hoops_SPRSH _hoops_RSSA _hoops_IS _hoops_PSRAR _hoops_CGHCP _hoops_HHGS */
	{
		Point			min, max;
		int			const	*item;
		int			const	*end;
		int			const	*_hoops_CRRHR;
		min.x = max.x = points[face_list[1]].x;
		min.y = max.y = points[face_list[1]].y;
		min.z = max.z = points[face_list[1]].z;

		item = face_list;
		end = _hoops_ICCIH;

		do {
			if (*item++ >= 0) { /* _hoops_GSSR _hoops_RPRHR _hoops_HSP */
				_hoops_CRRHR = item + item[-1];
			}
			else {				/* '_hoops_HHHR' _hoops_HSP == _hoops_IRS _hoops_RCCPR _hoops_GGR _hoops_RH _hoops_CGHI _hoops_HSP */
				_hoops_CRRHR = item - item[-1];
			}

			do {
				Point const *		point = &points[*item++];

				if (point->x < min.x)
					min.x = point->x;
				else if (point->x > max.x)
					max.x = point->x;

				if (point->y < min.y)
					min.y = point->y;
				else if (point->y > max.y)
					max.y = point->y;

				if (point->z < min.z)
					min.z = point->z;
				else if (point->z > max.z)
					max.z = point->z;
			} while (item != _hoops_CRRHR);
		} while (item != end);

		_hoops_SIRRGR.center.x = 0.5f * (min.x + max.x);
		_hoops_SIRRGR.center.y = 0.5f * (min.y + max.y);
		_hoops_SIRRGR.center.z = 0.5f * (min.z + max.z);
		_hoops_SIRRGR.scale.x = max.x - min.x;
		if (_hoops_SIRRGR.scale.x != 0.0f)
			_hoops_SIRRGR.scale.x = 2.0f / _hoops_SIRRGR.scale.x;
		_hoops_SIRRGR.scale.y = max.y - min.y;
		if (_hoops_SIRRGR.scale.y != 0.0f)
			_hoops_SIRRGR.scale.y = 2.0f / _hoops_SIRRGR.scale.y;
		_hoops_SIRRGR.scale.z = max.z - min.z;
		if (_hoops_SIRRGR.scale.z != 0.0f)
			_hoops_SIRRGR.scale.z = 2.0f / _hoops_SIRRGR.scale.z;

		_hoops_RPIS = max.x - min.x;
		if (_hoops_RPIS < max.y - min.y)
			_hoops_RPIS = max.y - min.y;
		if (_hoops_RPIS < max.z - min.z)
			_hoops_RPIS = max.z - min.z;
	}

	{
		int		const *_hoops_GRGPC = face_list;
		float	_hoops_IAARGR = _hoops_GSAHR * _hoops_RPIS;

		while (_hoops_GRGPC != _hoops_ICCIH) {
			_hoops_SARRGR			*_hoops_CAARGR = null;
			_hoops_SARRGR			*_hoops_SAARGR;

			/* _hoops_PIAAR _hoops_CGISH _hoops_GPP _hoops_IRS _hoops_HSP */
			{
				int		length = Abs (*_hoops_GRGPC);
				int		const *_hoops_GPARGR = _hoops_GRGPC + length;
				_hoops_CGRRGR *_hoops_RPARGR;

				/* _hoops_HSGR _hoops_GII _hoops_ARHAR _hoops_RGHS */
				if (length < 3) {
					_hoops_GRGPC = _hoops_GPARGR+1;
					continue;
				}

				/* _hoops_PPSR _hoops_IS _hoops_RH _hoops_SRS _hoops_GPHA _hoops_GPP _hoops_RH _hoops_SCGR _hoops_HSP */
				++_hoops_GRGPC;
				_hoops_RPARGR = _hoops_CIRRGR (points, *_hoops_GRGPC, info.axis, &_hoops_SIRRGR, &info._hoops_PPRRGR);

				_hoops_PCCAR {
					/* _hoops_RPGH _hoops_IRS _hoops_CCAH _hoops_PRCGH */
					ALLOC (span, _hoops_SARRGR);
					span->next = info._hoops_IRCGH;
					info._hoops_IRCGH = span;
					++_hoops_HAARGR;

					if (_hoops_CAARGR == null) _hoops_CAARGR = span;

					/* _hoops_ARP _hoops_RAAP _hoops_RSGR _hoops_IIGR _hoops_RH _hoops_PRCGH _hoops_IS _hoops_SCGR _hoops_GPHA */
					span->left = span->right = _hoops_RPARGR;

					/* _hoops_SPIC _hoops_RSSA _hoops_GAR _hoops_RGRRR _hoops_GAR _hoops_PSHR _hoops_IRGGA _hoops_PPR _hoops_ARP _hoops_RPHR */
					_hoops_PCCAR {
						if (++_hoops_GRGPC > _hoops_GPARGR) break;
						_hoops_RPARGR = _hoops_CIRRGR (points, *_hoops_GRGPC, info.axis, &_hoops_SIRRGR, &info._hoops_PPRRGR);

						if (Abs (_hoops_RPARGR->v - span->left->v) <= _hoops_GSAHR) {	/* _hoops_SCGA _hoops_GC! */
							span->right = _hoops_RPARGR;
							_hoops_RPARGR->v = span->left->v;	/* _hoops_IRHH _hoops_SCH _hoops_CPSA _hoops_GPIC _hoops_RPP _hoops_GGGR */
						}
						else {
							int			_hoops_AAGHR = _hoops_GPARGR - _hoops_GRGPC + 1;
							int	const	*_hoops_APARGR = _hoops_GRGPC + 1;

							while (_hoops_AAGHR > 1 &&
								   Abs (points[*_hoops_APARGR].x - _hoops_RPARGR->point.x) <= _hoops_IAARGR &&
								   Abs (points[*_hoops_APARGR].y - _hoops_RPARGR->point.y) <= _hoops_IAARGR &&
								   Abs (points[*_hoops_APARGR].z - _hoops_RPARGR->point.z) <= _hoops_IAARGR) {
								_hoops_APARGR++;
								_hoops_AAGHR--;
							}
							if (_hoops_APARGR <= _hoops_GPARGR &&
								Abs (points[*_hoops_APARGR].x - span->right->point.x) <= _hoops_IAARGR &&
								Abs (points[*_hoops_APARGR].y - span->right->point.y) <= _hoops_IAARGR &&
								Abs (points[*_hoops_APARGR].z - span->right->point.z) <= _hoops_IAARGR) {
								_hoops_GRGPC = _hoops_APARGR;
							}
							else
								break;
						}
					}

					if (Abs (span->left->u - span->right->u) < _hoops_GSAHR)
						span->right = span->left;

					if (_hoops_GRGPC > _hoops_GPARGR) break;
				}
			}

			/* _hoops_PSSSR _hoops_IH _hoops_RH _hoops_AGIR _hoops_CAS _hoops_HCR _hoops_RH _hoops_RSSA _hoops_CHR _hoops_GPP _hoops_IRS _hoops_RSRA _hoops_PRCGH */
			if (span == _hoops_CAARGR) {
				/* _hoops_SR _hoops_PAH _hoops_SAHR _hoops_SSPC _hoops_RGR _hoops_PRCGH, _hoops_SCH _hoops_IGRIR _hoops_ISAP _hoops_IS _hoops_RH _hoops_RIRPA */
				info._hoops_IRCGH = info._hoops_IRCGH->next;
				FREE (span, _hoops_SARRGR);
				span = null;
				--_hoops_HAARGR;
				continue;
			}

			/*
			 * _hoops_PCPC _hoops_SRS _hoops_PPR _hoops_CGHI _hoops_CGISH _hoops_GPP _hoops_RGR _hoops_HSP _hoops_RPP
			 * _hoops_SSIA _hoops_CHR _hoops_GPP _hoops_RH _hoops_PSHR _hoops_IRGGA, _hoops_HIS _hoops_SGS
			 *
			 *		   _hoops_PRCGH		 _hoops_PPARGR
			 *	  *------------**---------------*
			 *	  _hoops_GSSAA			   _hoops_HPARGR				_hoops_AHGPH
			 *	  _hoops_IPARGR
			 *
			 *	_hoops_RHCHR
			 *
			 *			 _hoops_PPARGR
			 *	  *--------------------------*
			 *	  _hoops_ISAII							 _hoops_AHGPH
			 *	  _hoops_CPARGR
			 */
			if (Abs (span->right->v - _hoops_CAARGR->left->v) < _hoops_GSAHR) {
				_hoops_CAARGR->left = span->left;
				info._hoops_IRCGH = info._hoops_IRCGH->next;
				FREE (span, _hoops_SARRGR);
				span = info._hoops_IRCGH;
				--_hoops_HAARGR;
			}

			_hoops_SAARGR = _hoops_CAARGR->next;

			/* _hoops_PPSR _hoops_RH _hoops_SPARGR _hoops_PPR _hoops_GHARGR _hoops_CICRR _hoops_CIAH */
			span = info._hoops_IRCGH;
			do {
				_hoops_SARRGR	*_hoops_RHARGR;

				if ((_hoops_RHARGR = span->next) == _hoops_SAARGR)
					_hoops_RHARGR = info._hoops_IRCGH;

				span->_hoops_HARRGR = _hoops_RHARGR->right;
				_hoops_RHARGR->_hoops_IARRGR = span->left;
			} while ((span = span->next) != _hoops_SAARGR);

			/* _hoops_AHARGR _hoops_CGISH */
			span = info._hoops_IRCGH;
			do {
				span->type = 0;
				if (span->_hoops_HARRGR->v	> span->left->v)
					span->type |= _hoops_IRRRGR;
				if (span->_hoops_IARRGR->v > span->right->v)
					span->type |= _hoops_CRRRGR;
			} while ((span = span->next) != _hoops_SAARGR);

			/*
			 * _hoops_IHAA _hoops_RH _hoops_CGISH _hoops_AARI _hoops_HIS _hoops_SGS _hoops_RH _hoops_RAAP _hoops_HRGR _hoops_CPSA _hoops_RAAP
			 * _hoops_PPR _hoops_RH _hoops_RPHR _hoops_HRGR _hoops_CPSA _hoops_RPHR, _hoops_RPP _hoops_SCH _hoops_GPGH'_hoops_RA _hoops_SGS _hoops_PPRRR _hoops_AIAH.
			 */
			span = info._hoops_IRCGH;
			do {
				span->_hoops_CARRGR = true;	/* _hoops_HPCAR */

				if (Abs (span->left->u - span->right->u)  < _hoops_GSAHR) {
					switch (span->type) {
					  case _hoops_CGHAS:
						if ((span->_hoops_HARRGR->u - span->left->u) * (span->_hoops_IARRGR->v - span->right->v) >
							(span->_hoops_IARRGR->u - span->right->u) * (span->_hoops_HARRGR->v - span->left->v))
							span->_hoops_CARRGR = false;
						break;
					  case _hoops_HIGRGR:
						if ((span->_hoops_HARRGR->u - span->left->u) * (span->_hoops_IARRGR->v - span->right->v) <
							(span->_hoops_IARRGR->u - span->right->u) * (span->_hoops_HARRGR->v - span->left->v))
							span->_hoops_CARRGR = false;
						break;
					  case _hoops_IRRRGR:
					  case _hoops_CRRRGR:
						span->type = _hoops_SRRRGR;

						if (span->_hoops_HARRGR->v > span->_hoops_IARRGR->v)
							span->_hoops_CARRGR = false;
						break;
					}
				}
				else if (span->left->u > span->right->u)
					span->_hoops_CARRGR = false;

				if (!span->_hoops_CARRGR) {
					/* _hoops_GGSHR _hoops_PHARGR _hoops_PPR _hoops_CHAII */
					Swap (span->right, span->left);
					Swap (span->_hoops_IARRGR, span->_hoops_HARRGR);

					/* _hoops_GPRR _hoops_GHCA _hoops_AGRP (_hoops_HHARGR _hoops_CIGCR) */
					span->type = _hoops_GARRGR[span->type];
				}
			} while ((span = span->next) != _hoops_SAARGR);
		}
	}

	if (_hoops_HAARGR == 0) {
		/* _hoops_RSIR _hoops_CAHA _hoops_PIHA _hoops_SHH _hoops_SPR _hoops_PAR _hoops_RRI _hoops_IRGGA _hoops_APGR */
		goto _hoops_HPAGR;
	}


	/*
	 * _hoops_ARP _hoops_GH _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_CRS _hoops_IS _hoops_CGISH, _hoops_HIS _hoops_SR _hoops_PAH _hoops_GHIS _hoops_AGAP, _hoops_HRII
	 * _hoops_HSAR _hoops_RH _hoops_HCCGR
	 */
	{
		_hoops_GPRRGR				*_hoops_IHARGR = null;
		_hoops_GPRRGR				*_hoops_CHARGR;
		int						i;

		ALLOC_ARRAY_CACHED (_hoops_IHARGR, _hoops_HAARGR, _hoops_GPRRGR);
		_hoops_CHARGR = _hoops_IHARGR;
		span = info._hoops_IRCGH;
		do *_hoops_CHARGR++ = span;
		while ((span = span->next) != null);

		/* _hoops_SGH _hoops_PHRSA _hoops_SHARGR _hoops_IS _hoops_AGR _hoops_CGISH _hoops_HPP _hoops_AHGP _hoops_HPPC */
		quick_sort (_hoops_IHARGR, 0, _hoops_HAARGR - 1);

		for (i=0; i<_hoops_HAARGR-1; i++) {
			_hoops_IHARGR[i]->next = _hoops_IHARGR[i+1];
		}
		_hoops_IHARGR[_hoops_HAARGR-1]->next = null;
		info._hoops_IRCGH = _hoops_IHARGR[0];

		/* _hoops_CIH _hoops_RH _hoops_CRPR _hoops_IIGR _hoops_PRCGH _hoops_CICRR */
		FREE_ARRAY (_hoops_IHARGR, _hoops_HAARGR, _hoops_GPRRGR);
	}

	/* _hoops_GIARGR _hoops_PCCP _hoops_HSCHR _hoops_IIHA _hoops_GPP _hoops_RH _hoops_SRS _hoops_PRCGH _hoops_SR _hoops_GRS _hoops_CHCIS */
	info._hoops_HHAHR = info._hoops_IRCGH->_hoops_CARRGR;


	/* _hoops_RH _hoops_HGSI _hoops_HAPR */
	while ((span = info._hoops_IRCGH) != null) {
		info._hoops_IRCGH = span->next;

		switch (span->type) {
			case _hoops_CGHAS: {
				ALLOC (edge, _hoops_PRRRGR);
				ALLOC (edge->next, _hoops_PRRRGR);
				edge->next->prev = edge;
				edge->prev = edge->next->next = null;
				edge->vertices = edge->next->vertices = null;

				_hoops_RHPHI (edge, span->left, true);
				/* _hoops_ISHA->_hoops_SPS _hoops_SAGGR _hoops_RGCI _hoops_GPHA _hoops_CGPR _hoops_AGCA _hoops_GGR _hoops_HIGR */
				edge->_hoops_RCSHR = span->_hoops_HARRGR;
				edge->next->_hoops_RCSHR = span->_hoops_IARRGR;
				edge->_hoops_ARRRGR = true;
				edge->next->_hoops_ARRRGR = false;

				if (_hoops_GRCPR == null) {
					_hoops_GRCPR = edge;
					_hoops_RHPHI (edge->next, span->left, true);
					if (span->left->u != span->right->u) {
						_hoops_RHPHI (edge->next, span->right, true);
						_hoops_PSRRGR (&info, edge, edge->next, _hoops_GSAHR, _hoops_GSAHR);
					}
					break;
				}

				current = _hoops_GRCPR;
				_hoops_PCCAR {
					if (current->_hoops_RCSHR != null &&
						_hoops_HCRRGR (span->left, span->_hoops_HARRGR,
									  current, false)) {
						_hoops_CGRRGR *		start;
						_hoops_CGRRGR *		tmp;

						if (current->prev != null)
							_hoops_PSRRGR (&info, current->prev, edge, _hoops_GSAHR, _hoops_GSAHR);

						if (current->_hoops_ARRRGR) {
							if ((edge->prev = current->prev) != null)
								edge->prev->next = edge;
							edge->next->next = current;
							current->prev = edge->next;

							if (_hoops_GRCPR == current)
								_hoops_GRCPR = edge;

							current = edge->next;
						}
						else {
							_hoops_PRRRGR * right = current;
							_hoops_PRRRGR * left = current->prev;

							Swap (edge->_hoops_ARRRGR, edge->next->_hoops_ARRRGR);

							if (left->_hoops_RCSHR == null) {
								_hoops_SPRRGR (&info, left->prev, span->left, true);
								_hoops_RHPHI (left->prev, span->left, true);
								left->prev->_hoops_RCSHR = span->_hoops_HARRGR;

								_hoops_GIRRGR (&info, left, span->left, true);
								left->_hoops_RCSHR = span->_hoops_IARRGR;

								current = left;
								_hoops_PSRRGR (&info, current->prev->prev, current->prev, _hoops_GSAHR, _hoops_GSAHR);

								_hoops_CRARGR (edge->next);
								FREE (edge->next, _hoops_PRRRGR);
								_hoops_CRARGR (edge);
								FREE (edge, _hoops_PRRRGR);
							}
							else {
								_hoops_CGRRGR *		_hoops_RIARGR = left->vertices->vertex;
								_hoops_CGRRGR *		_hoops_AIARGR = right->vertices->vertex;

								_hoops_GIRRGR (&info, left, span->left, false);
								_hoops_SPRRGR (&info, right, span->left, false);

								if (left->vertices->next != null) {
									edge->next->vertices = left->vertices;
									left->vertices = null;
									_hoops_RHPHI (left, _hoops_RIARGR, true);
								}
								else {
									_hoops_IPRRGR (left, _hoops_RIARGR, true);
									_hoops_RHPHI (edge->next, _hoops_AIARGR, true);
								}

								if (right->vertices->next != null)
									Swap (edge->vertices, right->vertices);
								else
									_hoops_IPRRGR (edge, _hoops_RIARGR, true);
								_hoops_IPRRGR (right, _hoops_AIARGR, true);

								edge->prev = current->prev;
								edge->next->next = current;
								edge->prev->next = edge;
								current->prev = edge->next;

								_hoops_RHPHI (edge, span->left, true);

								current = edge->next;
							}
						}

						start = span->left;

						_hoops_PCCAR {
							if (current->next->_hoops_RCSHR != null) {
								if (_hoops_HCRRGR (span->right, span->_hoops_IARRGR, current->next, true)) {
									if (current->_hoops_ARRRGR && span->left->u != span->right->u) {
										_hoops_RCHHR (&info, current->vertices->vertex, start, span->right);
										_hoops_GIRRGR (&info, current, span->right, true);
									}
									else
										_hoops_RHPHI (current, start, true);

									_hoops_RHPHI (current, span->right, true);
									current->_hoops_RCSHR = span->_hoops_IARRGR;

									if (current->prev != null)
										_hoops_PSRRGR (&info, current->prev, current, _hoops_GSAHR, _hoops_GSAHR);
									if (current->next != null)
										_hoops_PSRRGR (&info, current, current->next, _hoops_GSAHR, _hoops_GSAHR);
									break;
								}

								tmp = _hoops_ASRRGR (&info, current->next, span);

								if (current->_hoops_ARRRGR) {
									_hoops_RCHHR (&info, current->vertices->vertex, start, tmp);
									_hoops_GIRRGR (&info, current, tmp, true);

									_hoops_SPRRGR (&info, current->next, tmp, true);

									_hoops_IPRRGR (current, tmp, false);
									_hoops_IPRRGR (current->next, tmp, false);
								}
								else {
									_hoops_RHPHI (current, start, true);
									_hoops_RHPHI (current, tmp, false);
								}

								start = tmp;
								current->_hoops_RCSHR = current->next->_hoops_RCSHR;
								current->origin = current->next->origin;
								current->next->_hoops_RCSHR = span->_hoops_IARRGR;

								if (current->prev != null)
									_hoops_PSRRGR (&info, current->prev, current, _hoops_GSAHR, _hoops_GSAHR);
							}

							if ((current = current->next) == null)
								_hoops_GAARGR("valley: stop before nonexistent edge?");

							if (current->next == null) {
								_hoops_RHPHI (current, start, false);
								_hoops_RHPHI (current, span->right, true);
								current->_hoops_RCSHR = span->_hoops_IARRGR;
								_hoops_PSRRGR (&info, current->prev, current, _hoops_GSAHR, _hoops_GSAHR);
								break;
							}

							if (current->_hoops_ARRRGR)
								_hoops_GIRRGR (&info, current, start, true);
							else
								_hoops_SPRRGR (&info, current, start, true);
						}

						break;
					}
					else if (current->next == null) {
						current->next = edge;
						edge->prev = current;

						_hoops_PSRRGR (&info, current, edge, _hoops_GSAHR, _hoops_GSAHR);

						_hoops_RHPHI (edge->next, edge->vertices->vertex, true);
						if (span->left->u != span->right->u) {
							_hoops_RHPHI (edge->next, span->right, true);
							_hoops_PSRRGR (&info, edge, edge->next, _hoops_GSAHR, _hoops_GSAHR);
						}
						break;
					}
					else
						current = current->next;
				}
			}	break;

			case _hoops_HIGRGR: {
				_hoops_CGRRGR *		tmp;
				_hoops_CGRRGR *		start = null;
				_hoops_CGRRGR *		_hoops_GGSSR;

				if ((current = _hoops_GRCPR) == null)
					_hoops_GAARGR("peak: empty edge list");

				_hoops_PCCAR {
					if (current->_hoops_RCSHR == span->left) {
						_hoops_CGRRGR *		_hoops_ARSIP;
						_hoops_CGRRGR *		_hoops_PIARGR;

						if (current->next == null)
							_hoops_GAARGR("peak: bad connection at end of edge list");

						if (_hoops_RRARGR(current)->_hoops_RCSHR == span->right) {
							if (current->_hoops_ARRRGR) {
								_hoops_PRRRGR *		_hoops_HIARGR = current->prev;

								_hoops_GIRRGR (&info, current, span->left, true);

								if (span->left->u != span->right->u)
									_hoops_RCHHR (&info, current->vertices->vertex, span->left, span->right);

								_hoops_SPRRGR (&info, current->next, span->right, true);

								if (current->prev != null)
									current->prev->next = current->next->next;
								if (current->next->next != null)
									current->next->next->prev = current->prev;
								if (_hoops_GRCPR == current)
									_hoops_GRCPR = current->next->next;

								_hoops_CRARGR (current->next);
								FREE (current->next, _hoops_PRRRGR);
								_hoops_CRARGR (current);
								FREE (current, _hoops_PRRRGR);

								if (_hoops_HIARGR != null && _hoops_HIARGR->next != null)
									_hoops_PSRRGR (&info, _hoops_HIARGR, _hoops_HIARGR->next, _hoops_GSAHR, _hoops_GSAHR);
								break;
							}
							else {
								_hoops_SPRRGR (&info, current, span->left, true);
								_hoops_RHPHI (current, span->left, true);

								if (span->left->u != span->right->u)
									_hoops_RHPHI (current, span->right, true);
								current->_hoops_RCSHR = null;

								current = current->next;

								_hoops_GIRRGR (&info, current, span->right, true);
								_hoops_RHPHI (current, span->right, true);
								current->_hoops_RCSHR = null;

								_hoops_PSRRGR (&info, current->prev->prev, current->next, _hoops_GSAHR, _hoops_GSAHR);
								break;
							}
						}

						/* _hoops_ARARH */

						if (_hoops_HCRRGR (span->right, span->_hoops_IARRGR, _hoops_RRARGR(current), false)) {
							/* _hoops_GAAP _hoops_IRS _hoops_ARHAR _hoops_IIARGR, _hoops_IIS'_hoops_GRI _hoops_CACH _hoops_RPP _hoops_SR
							 * _hoops_PAH _hoops_HGIHR _hoops_SCH _hoops_PPR _hoops_HPPR _hoops_SCH _hoops_GICS
							 */
							if (current->vertices->vertex == current->next->vertices->vertex) {
								Swap (current->_hoops_RCSHR, current->next->_hoops_RCSHR);
								continue;
							}
							if (current->next->next != null &&
								span->right == current->next->next->_hoops_RCSHR) {
								Swap (current->next->_hoops_RCSHR, current->next->next->_hoops_RCSHR);
								continue;
							}

							_hoops_GAARGR("peak: bad connection");
						}

						if (current->_hoops_ARRRGR) {
							_hoops_GIRRGR (&info, current, span->left, true);

							_hoops_GGSSR = _hoops_ASRRGR (&info, current->next, span);

							_hoops_RCHHR (&info, current->vertices->vertex, span->left, _hoops_GGSSR);
						}
						else {
							_hoops_SPRRGR (&info, current, span->left, true);
							_hoops_RHPHI (current, span->left, true);

							current = current->next;

							_hoops_GGSSR = _hoops_ASRRGR (&info, current, span);

							_hoops_RHPHI (current->prev, _hoops_GGSSR, false);
							current->prev->_hoops_RCSHR = current->_hoops_RCSHR;
							current->prev->origin = current->origin;

							if (current->next->_hoops_RCSHR == span->right)
								start = span->right;
							else {
								_hoops_PRRRGR * _hoops_CIARGR = current->next;

								while (_hoops_CIARGR->_hoops_RCSHR == null)
									_hoops_CIARGR = _hoops_CIARGR->next->next;

								start = _hoops_ASRRGR (&info, _hoops_CIARGR, span);
							}

							_hoops_GIRRGR (&info, current, _hoops_GGSSR, true);
							_hoops_RCHHR (&info, current->vertices->vertex, _hoops_GGSSR, start);

							_hoops_GGSSR = start;
							start = null;
						}

						edge = current;
						current = current->next;
						_hoops_SPRRGR (&info, current, _hoops_GGSSR, true);

						_hoops_ARSIP = current->_hoops_RCSHR;
						_hoops_PIARGR = current->origin;
						current = current->next;

						if (edge->prev != null)
							edge->prev->next = current;
						if (current != null)
							current->prev = edge->prev;
						if (_hoops_GRCPR == edge)
							_hoops_GRCPR = current;

						_hoops_CRARGR (edge->next);
						FREE (edge->next, _hoops_PRRRGR);
						_hoops_CRARGR (edge);
						FREE (edge, _hoops_PRRRGR);

						if (_hoops_GGSSR == span->right)
							break;

						if (current == null)
							_hoops_GAARGR("peak: bad connection after close");

						_hoops_PCCAR {
							if (current->_hoops_RCSHR != null) {
								if (current->_hoops_RCSHR == span->right) {
									if (current->_hoops_ARRRGR) {
										_hoops_GIRRGR (&info, current, span->right, true);
										_hoops_RHPHI (current, span->right, true);
										_hoops_RHPHI (current, _hoops_GGSSR, false);
										current->_hoops_RCSHR = _hoops_ARSIP;
										current->origin = _hoops_PIARGR;
									}
									else {
										_hoops_SPRRGR (&info, current, span->right, true);
										_hoops_RCHHR (&info, current->vertices->vertex, _hoops_GGSSR, span->right);
										if (current->vertices->vertex == current->prev->vertices->vertex)
											_hoops_IPRRGR (current, _hoops_GGSSR, false);
										else
											_hoops_RHPHI (current, _hoops_GGSSR, false);
										current->_hoops_RCSHR = _hoops_ARSIP;
										current->origin = _hoops_PIARGR;
										if (start != null) {
											_hoops_IPRRGR (current->prev, _hoops_GGSSR, false);
											_hoops_RHPHI (current->prev, start, false);
										}
									}
									break;
								}

								tmp = _hoops_ASRRGR (&info, current, span);

								if (current->_hoops_ARRRGR)
									_hoops_GIRRGR (&info, current, tmp, true);
								else {
									_hoops_SPRRGR (&info, current, span->right, true);
									_hoops_RCHHR (&info, current->vertices->vertex, _hoops_GGSSR, tmp);
									_hoops_IPRRGR (current, _hoops_GGSSR, false);
									if (start != null) {
										_hoops_IPRRGR (current->prev, _hoops_GGSSR, false);
										_hoops_RHPHI (current->prev, start, false);
									}
								}

								Swap (current->_hoops_RCSHR, _hoops_ARSIP);
								Swap (current->origin, _hoops_PIARGR);

								start = _hoops_GGSSR;
								_hoops_GGSSR = tmp;
							}

							if ((current = current->next) == null)
								_hoops_GAARGR("peak: end of edge list after close");
						}

						break;
					}
					else if (current->_hoops_RCSHR == span->right) {
						/* _hoops_PAHA'_hoops_RA _hoops_PSSP _hoops_RPHR _hoops_ARPP _hoops_RAAP _hoops_HCCPR _hoops_SR _hoops_GGHP
						 * _hoops_CPHP _hoops_HPIPR, _hoops_PAHH _hoops_SAPGP _hoops_IS _hoops_ARHAR
						 * _hoops_CIIA.  _hoops_HCR _hoops_SR _hoops_PAH _hoops_AA _hoops_HRGR _hoops_GGSHR & _hoops_RCRPA
						 */
						Swap (span->right, span->left);
						Swap (span->_hoops_IARRGR, span->_hoops_HARRGR);
					}
					else if ((current = current->next) == null)
						_hoops_GAARGR("peak: no match found");
				}
			}	break;

			case _hoops_SRRRGR: {
				if ((current = _hoops_GRCPR) == null)
					_hoops_GAARGR("bend: empty edge list");

				_hoops_PCCAR {
					if (current->_hoops_RCSHR == span->left) {
						if (current->_hoops_ARRRGR)
							_hoops_GIRRGR (&info, current, span->left, true);
						else
							_hoops_SPRRGR (&info, current, span->left, true);

						_hoops_RHPHI (current, span->right, true);
						current->_hoops_RCSHR = span->_hoops_IARRGR;

						while (current->prev != null &&
							   current->prev->vertices->vertex == current->vertices->vertex) {
							_hoops_CGRRGR *	_hoops_HAPCR = current->vertices->vertex;
							_hoops_CGRRGR *	_hoops_PPRGH = current->_hoops_RCSHR;
							_hoops_CGRRGR *	pl = current->prev->vertices->vertex;
							_hoops_CGRRGR *	_hoops_SIARGR = current->prev->_hoops_RCSHR;
							float		_hoops_ISPI = (_hoops_PPRGH->u - _hoops_HAPCR->u) * (_hoops_SIARGR->v - pl->v);
							float		_hoops_CSPI = (_hoops_SIARGR->u - pl->u) * (_hoops_PPRGH->v - _hoops_HAPCR->v);

							if (_hoops_ISPI >= _hoops_CSPI)
								break;

							Swap (current->_hoops_RCSHR, current->prev->_hoops_RCSHR);
							Swap (current->origin, current->prev->origin);
							if (current->next != null)
								_hoops_PSRRGR (&info, current, current->next, 0.0, _hoops_GSAHR);
						}
						while (current->next != null &&
							   current->next->vertices->vertex == current->vertices->vertex) {
							_hoops_CGRRGR *	_hoops_HAPCR = current->vertices->vertex;
							_hoops_CGRRGR *	_hoops_PPRGH = current->_hoops_RCSHR;
							_hoops_CGRRGR *	nl = current->next->vertices->vertex;
							_hoops_CGRRGR *	_hoops_GCARGR = current->next->_hoops_RCSHR;
							float		_hoops_ISPI = (_hoops_PPRGH->u - _hoops_HAPCR->u) * (_hoops_GCARGR->v - nl->v);
							float		_hoops_CSPI = (_hoops_GCARGR->u - nl->u) * (_hoops_PPRGH->v - _hoops_HAPCR->v);

							if (_hoops_ISPI <= _hoops_CSPI)
								break;

							Swap (current->_hoops_RCSHR, current->next->_hoops_RCSHR);
							Swap (current->origin, current->next->origin);
							if (current->prev != null)
								_hoops_PSRRGR (&info, current->prev, current, 0.0, _hoops_GSAHR);
						}

						if (current->prev != null) {
							float		_hoops_RCARGR = _hoops_GSAHR;
							float		_hoops_ACARGR = 0.0f;
							if (current->vertices->vertex->u == current->prev->vertices->vertex->u)
								_hoops_RCARGR = _hoops_ACARGR = -_hoops_GSAHR;
							_hoops_PSRRGR (&info, current->prev, current, _hoops_RCARGR, _hoops_ACARGR);
						}
						if (current->next != null) {
							float		_hoops_RCARGR = 0.0f;
							float		_hoops_ACARGR = _hoops_GSAHR;
							if (current->vertices->vertex->u == current->next->vertices->vertex->u)
								_hoops_RCARGR = _hoops_ACARGR = -_hoops_GSAHR;
							_hoops_PSRRGR (&info, current, current->next, _hoops_RCARGR, _hoops_ACARGR);
						}
						break;
					}

					if ((current = current->next) == null)
						_hoops_GAARGR("bend: no match found");
				}
			}	break;

			case _hoops_IRRRGR: {
				_hoops_CGRRGR *		tmp;

				if ((current = _hoops_GRCPR) == null)
					_hoops_GAARGR("left: empty edge list");

				_hoops_PCCAR {
					if (current->_hoops_RCSHR == span->right) {
						_hoops_CGRRGR *		start = span->right;

						_hoops_PCCAR {
							if (current->prev == null) {
								_hoops_GIRRGR (&info, current, start, true);
								_hoops_RHPHI (current, start, false);
								_hoops_RHPHI (current, span->left, true);
								current->_hoops_RCSHR = span->_hoops_HARRGR;
								_hoops_PSRRGR (&info, current, current->next, _hoops_GSAHR, _hoops_GSAHR);
								break;
							}

							if (!current->_hoops_ARRRGR)
								_hoops_SPRRGR (&info, current, start, true);
							else
								_hoops_GIRRGR (&info, current, start, true);
							_hoops_RHPHI (current, start, true);

							if (current->prev->_hoops_RCSHR != null) {
								if (!_hoops_HCRRGR (span->left, span->_hoops_HARRGR, current->prev, true)) {
									if (!current->_hoops_ARRRGR) {
										if (current->vertices->vertex != start)
											_hoops_RCHHR (&info, current->vertices->vertex, span->left, start);
										_hoops_SPRRGR (&info, current, span->left, true);
									}

									_hoops_RHPHI (current, span->left, true);
									current->_hoops_RCSHR = span->_hoops_HARRGR;

									if (current->prev != null)
										_hoops_PSRRGR (&info, current->prev, current, _hoops_GSAHR, 0.0);

									if (current->next != null)
										_hoops_PSRRGR (&info, current, current->next, 0.0, _hoops_GSAHR);

									break;
								}

								tmp = _hoops_ASRRGR (&info, current->prev, span);

								if (!current->_hoops_ARRRGR) {
									_hoops_RCHHR (&info, current->vertices->vertex, tmp, start);
									_hoops_SPRRGR (&info, current, tmp, true);
									_hoops_GIRRGR (&info, current->prev, tmp, true);
									_hoops_IPRRGR (current, tmp, false);
									_hoops_IPRRGR (current->prev, tmp, false);
								}
								else {
									_hoops_RHPHI (current, start, false);
									_hoops_RHPHI (current, tmp, false);
								}

								start = tmp;
								current->_hoops_RCSHR = current->prev->_hoops_RCSHR;
								current->origin = current->prev->origin;
								current->prev->_hoops_RCSHR = span->_hoops_HARRGR;

								if (current->next != null)
									_hoops_PSRRGR (&info, current, current->next, _hoops_GSAHR, _hoops_GSAHR);
							}

							if ((current = current->prev) == null)
								_hoops_GAARGR("left: past start of edge list");
						}
						break;
					}
					else if ((current = current->next) == null)
						_hoops_GAARGR("left: no match found");
				}
			}	break;

			case _hoops_CRRRGR: {
				_hoops_CGRRGR *		tmp;

				if ((current = _hoops_GRCPR) == null)
					_hoops_GAARGR("right: empty edge list");

				_hoops_PCCAR {
					if (current->_hoops_RCSHR == span->left) {
						_hoops_CGRRGR *		start = span->left;

						_hoops_PCCAR {
							if (current->next == null) {
								_hoops_SPRRGR (&info, current, start, true);
								_hoops_RHPHI (current, start, false);
								_hoops_RHPHI (current, span->right, true);
								current->_hoops_RCSHR = span->_hoops_IARRGR;
								_hoops_PSRRGR (&info, current->prev, current, _hoops_GSAHR, _hoops_GSAHR);
								break;
							}

							if (current->_hoops_ARRRGR)
								_hoops_GIRRGR (&info, current, start, true);
							else
								_hoops_SPRRGR (&info, current, start, true);
							_hoops_RHPHI (current, start, true);

							if (current->next->_hoops_RCSHR != null) {
								if (_hoops_HCRRGR (span->right, span->_hoops_IARRGR, current->next, true)) {
									if (current->_hoops_ARRRGR) {
										if (current->vertices->vertex != start)
											_hoops_RCHHR (&info, current->vertices->vertex, start, span->right);
										_hoops_GIRRGR (&info, current, span->right, true);
									}

									_hoops_RHPHI (current, span->right, true);
									current->_hoops_RCSHR = span->_hoops_IARRGR;

									if (current->prev != null)
										_hoops_PSRRGR (&info, current->prev, current, _hoops_GSAHR, 0.0);

									if (current->next != null)
										_hoops_PSRRGR (&info, current, current->next, 0.0, _hoops_GSAHR);

									break;
								}

								tmp = _hoops_ASRRGR (&info, current->next, span);

								if (current->_hoops_ARRRGR) {
									_hoops_RCHHR (&info, current->vertices->vertex, start, tmp);
									_hoops_GIRRGR (&info, current, tmp, true);
									_hoops_SPRRGR (&info, current->next, tmp, true);
									_hoops_IPRRGR (current, tmp, false);
									_hoops_IPRRGR (current->next, tmp, false);
								}
								else {
									_hoops_RHPHI (current, start, false);
									_hoops_RHPHI (current, tmp, false);
								}

								start = tmp;
								current->_hoops_RCSHR = current->next->_hoops_RCSHR;
								current->origin = current->next->origin;
								current->next->_hoops_RCSHR = span->_hoops_IARRGR;

								if (current->prev != null)
									_hoops_PSRRGR (&info, current->prev, current, _hoops_GSAHR, _hoops_GSAHR);
							}

							if ((current = current->next) == null)
								_hoops_GAARGR("right: past end of edge list");
						}
						break;
					}
					else if ((current = current->next) == null)
						_hoops_GAARGR("right: no match found");
				}
			}	break;

			case _hoops_CSSPS: {
				if ((current = _hoops_GRCPR) == null)
					_hoops_GAARGR("crossing: empty edge list");

				_hoops_PCCAR {
					if (current->_hoops_RCSHR == span->left) {
						if (current->_hoops_ARRRGR) {
							if (current->next == null)
								_hoops_GAARGR("intersection attached ro unpaired edge");

							_hoops_GIRRGR (&info, current, span->left, true);
							_hoops_SPRRGR (&info, current->next, span->right, true);

							_hoops_IPRRGR (current, span->left, false);
							current->_hoops_RCSHR = span->_hoops_HARRGR;

							_hoops_IPRRGR (current->next, span->right, false);
							current->next->_hoops_RCSHR = span->_hoops_IARRGR;
						}
						else {
							if (current->next == null)
								_hoops_GAARGR("intersection at end of edge list");

							_hoops_SPRRGR (&info, current, span->left, true);
							_hoops_RHPHI (current, span->left, false);
							current->_hoops_RCSHR = span->_hoops_HARRGR;

							_hoops_GIRRGR (&info, current->next, span->right, true);
							_hoops_RHPHI (current->next, span->right, false);
							current->next->_hoops_RCSHR = span->_hoops_IARRGR;
						}

						Swap (current->origin, current->next->origin);

						if (current->prev != null)
							_hoops_PSRRGR (&info, current->prev, current, _hoops_GSAHR, _hoops_GSAHR);
						if (current->next->next != null)
							_hoops_PSRRGR (&info, current->next, current->next->next, _hoops_GSAHR, _hoops_GSAHR);

						break;
					}

					if ((current = current->next) == null)
						_hoops_GAARGR("crossing: no match found");
				}
			}	break;

			default: {
				_hoops_GAARGR("unknown");
			}	_hoops_HHHI;
		}

		FREE (span, _hoops_SARRGR);
	}

	/* _hoops_GGR _hoops_AGIR _hoops_SR _hoops_RAAP _hoops_SAPGP _hoops_IS _hoops_PCARGR-_hoops_SAIP, _hoops_CASI _hoops_GH */
  _hoops_HPAGR:

#ifdef _hoops_SRARGR
	/* _hoops_ARPP _hoops_HCARGR _hoops_GGAS _hoops_HIS _hoops_SR _hoops_HS _hoops_IRS _hoops_CGGC _hoops_IS _hoops_IHSH _hoops_HPGR _hoops_SCGR _hoops_PIAP */
	if (_hoops_AAARGR) {
		int		_hoops_ICARGR = 0;

		if (_hoops_ICARGR) {
			int point_count = 0;
			int *_hoops_PSRGA = face_list;
			FILE *fp;
			int ii;

			while (_hoops_PSRGA != _hoops_ICCIH) {
				int length = *_hoops_PSRGA++;
				if (length < 0)
					length = -length;
				for (ii=0; ii<length; ii++) {
					if (*_hoops_PSRGA > point_count)
						point_count = *_hoops_PSRGA;
					++_hoops_PSRGA;
				}
			}
			++point_count;	/* _hoops_AGRP _hoops_HII _hoops_CIHA _hoops_IS _hoops_RPR */

			fp = fopen ("D:\\bad_new.hmf", "w");

			fprintf (fp, ";; HMF V1.24 TEXT\n\n");
			fprintf (fp, "(Visibility \"geometry\")\n");
			fprintf (fp, "(Marker_Symbol \"x\")\n");
			fprintf (fp, "(marker_Size 0.05)\n");
			fprintf (fp, "(Color \"marker = red\")\n");

			fprintf (fp, "(Shell\n");
			fprintf (fp, "	(\n");
			for (ii=0; ii<point_count; ii++)
				fprintf (fp, "	  (%f %f %f)\n",
						 points[ii].x, points[ii].y, points[ii].z);
			fprintf (fp, "	)\n");
			fprintf (fp, "	(\n");
			_hoops_PSRGA = face_list;
			fprintf (fp, "	  ");
			while (_hoops_PSRGA != _hoops_ICCIH) {
				fprintf (fp, "%d ", *_hoops_PSRGA++);
				if (_hoops_PSRGA != _hoops_ICCIH && (_hoops_PSRGA-face_list)%10 == 0)
					fprintf (fp, "\n	");
			}
			fprintf (fp, "	)\n");
			fprintf (fp, ")\n");

			fclose (fp);
			_hoops_ICARGR = 0;
		}
	}
#endif

	if (span != null)
		FREE (span, _hoops_SARRGR);	/* _hoops_PIHA _hoops_HS _hoops_PRGS _hoops_GGSR _hoops_HII _hoops_HGSI _hoops_HAPR */

	while ((span = info._hoops_IRCGH) != null) {
		info._hoops_IRCGH = span->next;
		FREE (span, _hoops_SARRGR);
	}
	while ((edge = _hoops_GRCPR) != null) {
		_hoops_GRCPR = edge->next;
		_hoops_CRARGR (edge);
		FREE (edge, _hoops_PRRRGR);
	}


	/* _hoops_CIH _hoops_RH _hoops_PHCR _hoops_RSSA */
	while (info._hoops_PPRRGR != null) {
		_hoops_GRRRGR *victim = info._hoops_PPRRGR;
		info._hoops_PPRRGR = victim->next;
		if (victim->vertex->_hoops_RSPSA != null)
			FREE (victim->vertex->_hoops_RSPSA, Intersection);
		FREE (victim->vertex, _hoops_CGRRGR);
		FREE (victim, _hoops_GRRRGR);
	}

	return !_hoops_AAARGR;
}



local void _hoops_CCARGR (
	Point const			*points,
	int const			*face_list,
	_hoops_ARCIH		triangle_action,
	void				*user_data) {
	Integer32			_hoops_GAPPA, _hoops_RAPPA, _hoops_CAPPA;
	int					_hoops_SCARGR,
						count = *face_list++;

	_hoops_GAPPA = *face_list++;
	_hoops_RAPPA = *face_list;
	_hoops_SCARGR = count - 2;

	_hoops_RGGA (_hoops_SCARGR < 2) {
		/* _hoops_HSRS _hoops_HII _hoops_CSGR _hoops_HHAA-_hoops_GSARGR */
		_hoops_CAPPA = face_list[_hoops_SCARGR];
		(*triangle_action) (user_data, true,
							&points[_hoops_GAPPA], &points[_hoops_RAPPA], &points[_hoops_CAPPA],
							_hoops_GAPPA, _hoops_RAPPA, _hoops_CAPPA,	null, null, null);
		/* _hoops_PARRH */
		_hoops_GAPPA = _hoops_RAPPA;
		_hoops_RAPPA = _hoops_CAPPA;

		/* _hoops_GCHGA */
		++face_list;
		_hoops_SCARGR -= 2;

		/* _hoops_HSRS _hoops_HII _hoops_SPIGS _hoops_HHAA-_hoops_GSARGR (_hoops_PAGA _hoops_PPSR _hoops_AGR!) */
		_hoops_CAPPA = *face_list;
		(*triangle_action) (user_data, true,
							&points[_hoops_GAPPA], &points[_hoops_CAPPA], &points[_hoops_RAPPA],
							_hoops_GAPPA, _hoops_CAPPA, _hoops_RAPPA,	null, null, null);
		/* _hoops_PARRH */
		_hoops_GAPPA = _hoops_RAPPA;
		_hoops_RAPPA = _hoops_CAPPA;
	}

	if (_hoops_SCARGR != 0) {
		_hoops_CAPPA = *++face_list;
		(*triangle_action) (user_data, true,
							&points[_hoops_GAPPA], &points[_hoops_RAPPA], &points[_hoops_CAPPA],
							_hoops_GAPPA, _hoops_RAPPA, _hoops_CAPPA,	null, null, null);
	}
}



GLOBAL_FUNCTION bool HI_Triangulate_Face_X (
	Point const			*points,
	Vector const			*normal,
	int	const				*face_list,
	int	const				*_hoops_ICCIH,
	_hoops_ARCIH		triangle_action,
	void 					*user_data) {

	if (*face_list < 3) return false; /* _hoops_IRISI _hoops_PCPA? */

	if (face_list + *face_list + 1 == _hoops_ICCIH) {
		/* _hoops_SPCA _hoops_CHR _hoops_PSP _hoops_PCCPR _hoops_GGR _hoops_RGR _hoops_HSP. _hoops_SGCH _hoops_IH _hoops_PCCP _hoops_PIHGR _hoops_PPRRR. */
		if (*face_list == 3) {
			(*triangle_action) (user_data, false,
								&points[face_list[1]],
								&points[face_list[2]],
								&points[face_list[3]],
								face_list[1], face_list[2], face_list[3],
								null, null, null);
			return true;
		}
		else if (!BIT (HI_Rank_Polygon (points, face_list, _hoops_ICCIH),
					   _hoops_ARPGI)) {
			_hoops_CCARGR (points, face_list,
								triangle_action, user_data);
			return true;
		}
	}

	return _hoops_PAARGR (points, normal,
								face_list, _hoops_ICCIH,
								triangle_action, user_data);
}

/*---------------------------------------------------------------------------*/

struct _hoops_RSARGR {
	_hoops_RRCIH		action;
	void *						info;
};

local int _hoops_ASARGR (
	Point const *		p,
	Intersection const * i) {
	Point const *		test;
	int						_hoops_ACCAA;
	float					dist, _hoops_HIPAS;
	float					dx, _hoops_CRRAR, _hoops_AAAC;

	test = i->_hoops_PICHR[0].start;
	dx = p->x - test->x;
	_hoops_CRRAR = p->y - test->y;
	_hoops_AAAC = p->z - test->z;
	dist = dx*dx + _hoops_CRRAR*_hoops_CRRAR + _hoops_AAAC*_hoops_AAAC;
	_hoops_ACCAA = i->_hoops_PICHR[0]._hoops_PCIGI;
	_hoops_HIPAS = dist;

	test = i->_hoops_PICHR[1].start;
	dx = p->x - test->x;
	_hoops_CRRAR = p->y - test->y;
	_hoops_AAAC = p->z - test->z;
	dist = dx*dx + _hoops_CRRAR*_hoops_CRRAR + _hoops_AAAC*_hoops_AAAC;
	if (dist < _hoops_HIPAS) {
		_hoops_ACCAA = i->_hoops_PICHR[1]._hoops_PCIGI;
		_hoops_HIPAS = dist;
	}

	/* _hoops_HSPP _hoops_PSPI _hoops_CGH _hoops_SHR _hoops_SHH _hoops_HPHR, _hoops_HIH _hoops_RSGR _hoops_PSPI
	 * _hoops_SIAS _hoops_SHH _hoops_PRCHR _hoops_IS _hoops_RII _hoops_IAHI */
	if (i->_hoops_PICHR[0]._hoops_HCIGI >= 0) {
		test = i->_hoops_PICHR[0].end;
		dx = p->x - test->x;
		_hoops_CRRAR = p->y - test->y;
		_hoops_AAAC = p->z - test->z;
		dist = dx*dx + _hoops_CRRAR*_hoops_CRRAR + _hoops_AAAC*_hoops_AAAC;
		if (dist < _hoops_HIPAS) {
			_hoops_ACCAA = i->_hoops_PICHR[0]._hoops_HCIGI;
			_hoops_HIPAS = dist;
		}
	}

	if (i->_hoops_PICHR[1]._hoops_HCIGI >= 0) {
		test = i->_hoops_PICHR[1].end;
		dx = p->x - test->x;
		_hoops_CRRAR = p->y - test->y;
		_hoops_AAAC = p->z - test->z;
		dist = dx*dx + _hoops_CRRAR*_hoops_CRRAR + _hoops_AAAC*_hoops_AAAC;
		if (dist < _hoops_HIPAS) {
			_hoops_ACCAA = i->_hoops_PICHR[1]._hoops_HCIGI;
			_hoops_HIPAS = dist;
		}
	}

	return _hoops_ACCAA;
}

local void _hoops_PSARGR (
	void *					info,
	int						_hoops_HSARGR,
	Point const *		p1,
	Point const *		p2,
	Point const *		_hoops_IAPH,
	int						s1,
	int						s2,
	int						_hoops_CAPH,
	Intersection const * i1,
	Intersection const * i2,
	Intersection const * _hoops_SAPH) {
	struct _hoops_RSARGR *		_hoops_HHHRR = (struct _hoops_RSARGR *)info;

#if 0
	/* _hoops_RHGS _hoops_SRSGR, _hoops_ISARGR _hoops_GII _hoops_HIPH _hoops_IICHR _hoops_IS _hoops_SGSSR _hoops_RSSA */
	if (s1 < 0 || s2 < 0 || _hoops_CAPH < 0)
		return;
#endif

	/* _hoops_CCAH _hoops_SRSGR, _hoops_GCGRA _hoops_SGSSR _hoops_CCA _hoops_PHRHA _hoops_GIGR _hoops_PPSR _hoops_PGCRA
	 * _hoops_GGR _hoops_RH _hoops_RGAP _hoops_IIGR _hoops_RH _hoops_SGSSR
	 */
	if (s1 < 0)
		s1 = _hoops_ASARGR (p1, i1);
	if (s2 < 0)
		s2 = _hoops_ASARGR (p2, i2);
	if (_hoops_CAPH < 0)
		_hoops_CAPH = _hoops_ASARGR (_hoops_IAPH, _hoops_SAPH);

	(*_hoops_HHHRR->action) (_hoops_HHHRR->info, _hoops_HSARGR, s1, s2, _hoops_CAPH);
}

GLOBAL_FUNCTION bool HI_Triangulate_Face (
	Point const			*points,
	Vector const			*normal,
	int	const				*face_list,
	int	const				*_hoops_ICCIH,
	_hoops_RRCIH	triangle_action,
	void					*user_data) {
	struct _hoops_RSARGR			_hoops_HHHRR;

	if (_hoops_ICCIH - face_list < 4) return false; /* _hoops_IRISI _hoops_PCPA? */

	_hoops_HHHRR.action = triangle_action;
	_hoops_HHHRR.info = user_data;

	return HI_Triangulate_Face_X (points, normal, face_list, _hoops_ICCIH,
								  _hoops_PSARGR, &_hoops_HHHRR);
}



struct _hoops_CSARGR {
	Point	delta;
	struct {
		int		x, y, z;
	} _hoops_SSARGR;
	Point	_hoops_SAIAR;
};


/*
 * _hoops_HSRR _hoops_CIIA, _hoops_SR _hoops_HGCR _hoops_PCCP _hoops_CRPR _hoops_IIGR _hoops_RSSA _hoops_PPR _hoops_IRS _hoops_HSP _hoops_HIGR.  _hoops_IPCP
 * _hoops_HSP _hoops_HIGR _hoops_RRGPR _hoops_CCA _hoops_RH _hoops_PHI _hoops_IIGR _hoops_RSSA _hoops_GGR _hoops_RH _hoops_HSSP,
 * _hoops_PGAP _hoops_GHCA _hoops_SCIR _hoops_IRS _hoops_SSRS _hoops_HSPP/_hoops_RSGR _hoops_PPSR.  _hoops_IPCP _hoops_HIGR
 * _hoops_GGPRGR _hoops_ICGI _hoops_PSPI _hoops_CRGR _hoops_RH _hoops_RSSA _hoops_CRPR.
 *
 * _hoops_PS _hoops_ASRC _hoops_SIH _hoops_SGS _hoops_GAHPC _hoops_RH _hoops_HSSP.  _hoops_RAIGR _hoops_AHHR (_hoops_PSP _hoops_SIH _hoops_ARP)
 * _hoops_SIGH _hoops_RH _hoops_HSSP _hoops_CSAP _hoops_IHGP.  _hoops_CRRAI _hoops_GHCA _hoops_SHH _hoops_RRAI _hoops_RPP
 * _hoops_RH _hoops_HSSP _hoops_HRGR _hoops_HAHI-_hoops_IAGPR _hoops_PAR _hoops_AGHH.
 *
 * _hoops_RGPRGR _hoops_CHR _hoops_CPSIA _hoops_HPP _hoops_RSRHA _hoops_PGCHR _hoops_HAGA (_hoops_HHHR
 * _hoops_PSCHR _hoops_HPAHR) _hoops_IIGR _hoops_PGCR _hoops_SCCPR _hoops_GPHA _hoops_SHHP _hoops_RSSSR.	_hoops_ASC
 * _hoops_SHHP _hoops_RSSSR _hoops_CHR _hoops_GGSRA _hoops_HII _hoops_RH _hoops_SPPR, _hoops_AIHCR _hoops_GAR _hoops_PSPAR
 * _hoops_SGS _hoops_HSSRR _hoops_IRS _hoops_GPHA.
 *
 * _hoops_AGPRGR-_hoops_SGSSR _hoops_SIAS _hoops_SHH _hoops_CPSIA _hoops_HPP _hoops_RPCPR _hoops_RH _hoops_PHI _hoops_IIGR
 * _hoops_HRASR _hoops_SHPH _hoops_RH _hoops_IACA _hoops_CRHPR _hoops_GGR _hoops_GRR _hoops_ISRR.  _hoops_HHAIA
 * _hoops_GCA _hoops_SGS _hoops_HPGR _hoops_CHGC _hoops_SPR _hoops_ISRR _hoops_AAHSI _hoops_RRI _hoops_HSAR _hoops_RRPC.
 * _hoops_PAGA _hoops_SGS _hoops_RGR _hoops_HRGR _hoops_RGHP _hoops_HIH _hoops_HAR _hoops_CHIS, _hoops_GAR _hoops_IRS _hoops_CAHA _hoops_PGPRGR
 * _hoops_RH _hoops_SIPP _hoops_IIGR _hoops_IRS _hoops_HGPRGR _hoops_PAR _hoops_GRII _hoops_HARRA _hoops_GRS _hoops_HS _hoops_AHPH _hoops_PSSHR.
 *
 * _hoops_HASRR _hoops_IPI _hoops_RGAR _hoops_CPSA _hoops_GCA _hoops_IGPRGR _hoops_IHGP _hoops_HII _hoops_RII,
 * _hoops_HIS _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_RPSHR _hoops_RPP _hoops_SR _hoops_CPSA _hoops_ACPA...
 */

GLOBAL_FUNCTION _hoops_ARASA HI_Rank_Polygon (
	Point const			*points,
	int const				*face_list,
	int const				*_hoops_ICCIH) {
	_hoops_CSARGR		_hoops_AGCII;
	_hoops_CSARGR		_hoops_AIGCR;
	_hoops_CSARGR		*prev = &_hoops_AGCII;
	_hoops_CSARGR		*_hoops_RSGHR = &_hoops_AIGCR;
	Point const			*_hoops_CGPRGR;
	Point const			*_hoops_GAPPA;
	int						_hoops_SGPRGR[3];

	if (*face_list != _hoops_ICCIH-face_list-1)
		return _hoops_ARPGI;			/* _hoops_PIHA _hoops_SCIR _hoops_PCCPR */

	if (*face_list++ == 3) return _hoops_HRIHR;

	_hoops_CGPRGR = points + _hoops_ICCIH[-2];
	_hoops_GAPPA = points + _hoops_ICCIH[-1];

	prev->delta.x = _hoops_GAPPA->x - _hoops_CGPRGR->x;
	prev->delta.y = _hoops_GAPPA->y - _hoops_CGPRGR->y;
	prev->delta.z = _hoops_GAPPA->z - _hoops_CGPRGR->z;

	_hoops_RGGA (prev->delta.x != 0.0f ||
		   prev->delta.y != 0.0f ||
		   prev->delta.z != 0.0f) {
		_hoops_CGPRGR = _hoops_GAPPA;
		_hoops_GAPPA = points + *face_list;

		if (++face_list == _hoops_ICCIH)
			return _hoops_HRIHR;

		prev->delta.x = _hoops_GAPPA->x - _hoops_CGPRGR->x;
		prev->delta.y = _hoops_GAPPA->y - _hoops_CGPRGR->y;
		prev->delta.z = _hoops_GAPPA->z - _hoops_CGPRGR->z;
	}

	_hoops_SGPRGR[0] = _hoops_SGPRGR[1] = _hoops_SGPRGR[2] = 0;

	prev->_hoops_SSARGR.x = Sign (prev->delta.x);
	prev->_hoops_SSARGR.y = Sign (prev->delta.y);
	prev->_hoops_SSARGR.z = Sign (prev->delta.z);

	prev->_hoops_SAIAR.x = prev->_hoops_SAIAR.y = prev->_hoops_SAIAR.z = 0.0f;

	do {
		_hoops_CGPRGR = _hoops_GAPPA;
		_hoops_GAPPA = points + *face_list;

		/*
		 * _hoops_IPCP _hoops_HSPR _hoops_GRPRGR _hoops_IRAA _hoops_PICP _hoops_IIGR _hoops_SGS
		 * _hoops_RRPRGR _hoops_IPGCA _hoops_AHHR.	_hoops_HAIC'_hoops_RA _hoops_IRHH _hoops_ICCSS _hoops_GHCRH
		 * _hoops_CAHRI _hoops_IIGR _hoops_SGS _hoops_RPP _hoops_RHAC'_hoops_RISP _hoops_GGHP _hoops_SAHR _hoops_SPR _hoops_PPGS _hoops_SIHGA,
		 * _hoops_PPR _hoops_RHAC'_hoops_ASAR _hoops_IRCC _hoops_IS _hoops_CSSP _hoops_IRS _hoops_HRASR _hoops_AGRP.
		 */
		_hoops_RSGHR->delta.x = _hoops_GAPPA->x - _hoops_CGPRGR->x;
		if ((_hoops_RSGHR->_hoops_SSARGR.x = Sign (_hoops_RSGHR->delta.x)) == 0)
			_hoops_RSGHR->_hoops_SSARGR.x = prev->_hoops_SSARGR.x;

		_hoops_RSGHR->delta.y = _hoops_GAPPA->y - _hoops_CGPRGR->y;
		if ((_hoops_RSGHR->_hoops_SSARGR.y = Sign (_hoops_RSGHR->delta.y)) == 0)
			_hoops_RSGHR->_hoops_SSARGR.y = prev->_hoops_SSARGR.y;

		_hoops_RSGHR->delta.z = _hoops_GAPPA->z - _hoops_CGPRGR->z;
		if ((_hoops_RSGHR->_hoops_SSARGR.z = Sign (_hoops_RSGHR->delta.z)) == 0)
			_hoops_RSGHR->_hoops_SSARGR.z = prev->_hoops_SSARGR.z;

		if (_hoops_RSGHR->delta.x == 0.0f &&
			_hoops_RSGHR->delta.y == 0.0f &&
			_hoops_RSGHR->delta.z == 0.0f) {
			/* _hoops_PSHR _hoops_PPSR -- _hoops_HSGR _hoops_SCH */
		}
		else {
			if (_hoops_RSGHR->_hoops_SSARGR.x != prev->_hoops_SSARGR.x) ++_hoops_SGPRGR[0];
			if (_hoops_RSGHR->_hoops_SSARGR.y != prev->_hoops_SSARGR.y) ++_hoops_SGPRGR[1];
			if (_hoops_RSGHR->_hoops_SSARGR.z != prev->_hoops_SSARGR.z) ++_hoops_SGPRGR[2];


			_hoops_RSGHR->_hoops_SAIAR.x = (prev->delta.y*_hoops_RSGHR->delta.z -
							 prev->delta.z*_hoops_RSGHR->delta.y);
			_hoops_RSGHR->_hoops_SAIAR.y = (prev->delta.z*_hoops_RSGHR->delta.x -
							 prev->delta.x*_hoops_RSGHR->delta.z);
			_hoops_RSGHR->_hoops_SAIAR.z = (prev->delta.x*_hoops_RSGHR->delta.y -
							 prev->delta.y*_hoops_RSGHR->delta.x);

			if (_hoops_RSGHR->_hoops_SAIAR.x == 0.0f &&
				_hoops_RSGHR->_hoops_SAIAR.y == 0.0f &&
				_hoops_RSGHR->_hoops_SAIAR.z == 0.0f) {
				/* _hoops_PSHR _hoops_AAGA -- _hoops_HSGR _hoops_SCH (_hoops_GA'_hoops_RA _hoops_CRCH _hoops_PGHC _hoops_ISGSP & _hoops_SHHP) */
			}
			else {
				if (prev->_hoops_SAIAR.x * _hoops_RSGHR->_hoops_SAIAR.x +
					prev->_hoops_SAIAR.y * _hoops_RSGHR->_hoops_SAIAR.y +
					prev->_hoops_SAIAR.z * _hoops_RSGHR->_hoops_SAIAR.z < 0.0f)
					return _hoops_ARPGI;

				{
					_hoops_CSARGR		*temp;
					temp = prev; prev = _hoops_RSGHR; _hoops_RSGHR = temp;
				}
			}
		}
	} _hoops_RGGA (++face_list == _hoops_ICCIH);

	if (_hoops_SGPRGR[0] > 2 || _hoops_SGPRGR[1] > 2 || _hoops_SGPRGR[2] > 2)
		return _hoops_ARPGI; /* _hoops_HPGR _hoops_CHGC, _hoops_GAAP _hoops_HAHI-_hoops_IAGPR */

	return _hoops_HRIHR;
}

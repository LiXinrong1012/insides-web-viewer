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
 * $Id: obf_tmp.txt 1.16 2010-12-06 22:05:41 jason Exp $
 */

#include "hoops.h"
#include "hi_proto.h"
#include "hd_proto.h"
#include "phedron.h"
#include "adt.h"



#define _hoops_PCAHP(i) ((i-1)/2)
#define _hoops_HCAHP(i) (2*i+1)
#define _hoops_ICAHP(i) (2*i+2)
#define _hoops_CCAHP(heap,_hoops_SHHCR) {\
	ASSERT ((heap)->_hoops_SCAHP[(_hoops_SHHCR)]->dl->type == _hoops_HCIIR); \
	(heap)->_hoops_SCAHP[(_hoops_SHHCR)]->dl->_hoops_GGCI = (_hoops_SHHCR); \
}


local void _hoops_GSAHP (_hoops_RSAHP alter *heap, int i) {
	int p = _hoops_PCAHP(i);
	_hoops_GICGP *temp;

	while (i > 0) {
		if (heap->_hoops_SCAHP[i]->priority > heap->_hoops_SCAHP[p]->priority) {
			temp = heap->_hoops_SCAHP[i];
			heap->_hoops_SCAHP[i] = heap->_hoops_SCAHP[p];
			_hoops_CCAHP (heap, i);
			heap->_hoops_SCAHP[p] = temp;
			_hoops_CCAHP (heap, p);
			i = p;
			p = _hoops_PCAHP(p);
		}
		else
			break;
	}
}


local void _hoops_ASAHP(_hoops_RSAHP alter *heap, int i)
{
	_hoops_GICGP *temp;
	int l = _hoops_HCAHP(i);
	int r = _hoops_ICAHP(i);
	int _hoops_PSAHP = i;
	int _hoops_HSAHP = i;

	while (l < heap->used) {
		if (heap->_hoops_SCAHP[l]->priority > heap->_hoops_SCAHP[_hoops_HSAHP]->priority)
			_hoops_PSAHP = l;
		if (r < heap->used)
			if (heap->_hoops_SCAHP[r]->priority > heap->_hoops_SCAHP[_hoops_PSAHP]->priority)
				_hoops_PSAHP = r;
		if (_hoops_PSAHP != _hoops_HSAHP) {
			temp = heap->_hoops_SCAHP[_hoops_HSAHP];
			heap->_hoops_SCAHP[_hoops_HSAHP] = heap->_hoops_SCAHP[_hoops_PSAHP];
			_hoops_CCAHP (heap, _hoops_HSAHP);
			heap->_hoops_SCAHP[_hoops_PSAHP] = temp;
			_hoops_CCAHP (heap, _hoops_PSAHP);
			l = _hoops_HCAHP (_hoops_PSAHP);
			r = _hoops_ICAHP (_hoops_PSAHP);
			_hoops_HSAHP = _hoops_PSAHP;
		}
		else
			break;
	}
}

local void _hoops_ISAHP (_hoops_RSAHP alter *heap, _hoops_GICGP alter *_hoops_CSAHP)
{
	ASSERT (_hoops_CSAHP != null);
	if (heap->used == heap->allocated)
	{
		_hoops_GICGP alter **_hoops_PCAHA;

		if (heap->allocated) {
			heap->allocated *= 2;
			ALLOC_ARRAY(_hoops_PCAHA, heap->allocated, _hoops_GICGP *);
			_hoops_AIGA(heap->_hoops_SCAHP, heap->used, _hoops_GICGP *, _hoops_PCAHA);
			FREE_ARRAY(heap->_hoops_SCAHP, heap->used, _hoops_GICGP *);
			heap->_hoops_SCAHP = _hoops_PCAHA;
		}
		else {
			heap->allocated = 10;
			ALLOC_ARRAY(heap->_hoops_SCAHP, heap->allocated, _hoops_GICGP *);
		}
	}
	heap->_hoops_SCAHP[heap->used] = _hoops_CSAHP;
	_hoops_CCAHP (heap, heap->used);
	heap->used++;
	_hoops_GSAHP(heap, heap->used-1);
}


local _hoops_GICGP *_hoops_SSAHP (_hoops_RSAHP alter *heap)
{
	_hoops_GICGP *_hoops_CSAHP;

	if (heap->used == 0)
		return null;
	_hoops_CSAHP = heap->_hoops_SCAHP[0];
	heap->_hoops_SCAHP[0] = heap->_hoops_SCAHP[heap->used-1];
	_hoops_CCAHP (heap, 0);
	_hoops_CSAHP->dl->_hoops_GGCI = -1; //_hoops_PSP _hoops_RPIP _hoops_GGR _hoops_SIHPA
	heap->_hoops_SCAHP[heap->used-1] = null;
	heap->used--;
	if (heap->used)
		_hoops_ASAHP(heap, 0);
	else {
		FREE_ARRAY(heap->_hoops_SCAHP, heap->allocated, _hoops_GICGP *);
		heap->allocated = 0;
	}
	return _hoops_CSAHP;
}


/* 
 * _hoops_GHCP _hoops_ARI _hoops_HRGR _hoops_AIPP/_hoops_PHGC -- _hoops_SR'_hoops_ASAR _hoops_CGRSR _hoops_RH _hoops_CHGC _hoops_PSIGA _hoops_IPIH 
 * _hoops_CISI _hoops_AIRI _hoops_HIGR
 */
GLOBAL_FUNCTION bool HI_Push_Display_List (
		_hoops_AIGPR *	_hoops_RIGC, 
		_hoops_GACR alter *	dl,
		float					priority,
		int						_hoops_GPGC)
{
	_hoops_RSAHP *heap = &HOOPS_WORLD->_hoops_GGPHP;
	_hoops_GICGP *_hoops_CSAHP;
	size_t limit = HOOPS_WORLD->_hoops_PHARR;
	size_t _hoops_GCI = HOOPS_WORLD->display_list_vram_usage + HOOPS_WORLD->_hoops_SARH;
	bool status = true;

	_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);
	ASSERT (dl->_hoops_GGCI < 0);
	ASSERT (priority < MAX_FLOAT);
	while (_hoops_GCI + _hoops_GPGC > limit) {
		if (heap->used == 0) {
			status = false; 
			goto _hoops_HPAGR;
		}
		else if (priority > heap->_hoops_SCAHP[0]->priority) {
			status = false; 
			goto _hoops_HPAGR;
		}

		_hoops_GICGP *victim = _hoops_SSAHP (heap);
		_hoops_GCI -= victim->_hoops_GPGC;
		HI_Clean_Display_List (&victim->dl, true, false);
		FREE (victim, _hoops_GICGP);
	}

	ZALLOC (_hoops_CSAHP, _hoops_GICGP);
	_hoops_CSAHP->dl = dl;  //_hoops_GA'_hoops_RA _hoops_PCPCA _hoops_ARI
	_hoops_CSAHP->priority = priority;
	_hoops_CSAHP->_hoops_GPGC = _hoops_GPGC;
	_hoops_ISAHP (heap, _hoops_CSAHP);
  _hoops_HPAGR:
	_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);
	UNREFERENCED (_hoops_RIGC);
	return status;
}


GLOBAL_FUNCTION void HI_Extract_Display_List (
		_hoops_AIGPR *	_hoops_RIGC,
		int						index, 
		_hoops_GACR const *	dl)
{
	_hoops_RSAHP *heap = &HOOPS_WORLD->_hoops_GGPHP;
	_hoops_GICGP *_hoops_CSAHP;
	float _hoops_RGPHP;

	_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);
	ASSERT (heap->used > index);
	_hoops_CSAHP = heap->_hoops_SCAHP[index];
	_hoops_RGPHP = _hoops_CSAHP->priority;
	_hoops_CSAHP->priority = MAX_FLOAT;
	_hoops_GSAHP (heap, index);
	_hoops_CSAHP = _hoops_SSAHP (heap);
	ASSERT (_hoops_CSAHP->dl == dl);
	_hoops_CSAHP->priority = _hoops_RGPHP;
	//_hoops_PHGSR _hoops_IHPR _hoops_IH _hoops_AGPHP _hoops_IS _hoops_PGPHP _hoops_ARI _hoops_HGPHP 
	//11788_hoops_IGPHP, _hoops_HIH _hoops_RGAR _hoops_GPP _hoops_AHHS
	HI_Clean_Display_List (&_hoops_CSAHP->dl, false, false);
	FREE (_hoops_CSAHP, _hoops_GICGP);
	_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);
	UNREFERENCED (_hoops_RIGC);

	//_hoops_GRHP _hoops_RH _hoops_HICA _hoops_RSPPP _hoops_GGR _hoops_RCSH _hoops_CCH _hoops_GSHRA _hoops_CAS _hoops_RH _hoops_AGHR _hoops_HRGR _hoops_CPIAR _hoops_GGSR
	UNREFERENCED (dl); 
}


GLOBAL_FUNCTION void HD_Queue_Destroy_List (
	_hoops_AGCI alter *	_hoops_AGAGR,
	bool								_hoops_CGPHP) {
	_hoops_GGAGR alter *						_hoops_GHRI = (_hoops_GGAGR alter *)_hoops_AGAGR->_hoops_GHRI;

	ASSERT(_hoops_GHRI);

	if (_hoops_CGPHP)
		_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);

	/* _hoops_SGPHP _hoops_HII _hoops_RH _hoops_AAPA _hoops_PAPA _hoops_GRPHP */
	if (_hoops_AGAGR->_hoops_PPAH) {
		_hoops_GACR *_hoops_PPAH = _hoops_AGAGR->_hoops_PPAH;
		/* _hoops_SGPHP _hoops_SPCGP _hoops_HII _hoops_HCGI (_hoops_PAR _hoops_GPHP _hoops_RPHP) */
		if (_hoops_PPAH->_hoops_GASI)
			_hoops_PPAH->_hoops_GASI->_hoops_GASI = null;
		_hoops_PPAH->list = null;
		_hoops_AGAGR->_hoops_PPAH = null;
	}

	/* _hoops_SGPHP _hoops_HII _hoops_GSSC _hoops_PAPA */
	if (_hoops_AGAGR->next)
		_hoops_AGAGR->next->prev = _hoops_AGAGR->prev;
	if (_hoops_AGAGR->prev)
		*_hoops_AGAGR->prev = _hoops_AGAGR->next;

	_hoops_AGAGR->next = _hoops_GHRI->_hoops_RGAGR;
	_hoops_AGAGR->prev = null;
	_hoops_GHRI->_hoops_RGAGR = _hoops_AGAGR;

	if (_hoops_AGAGR->_hoops_ISCS) {
		// _hoops_CSH _hoops_RPIP _hoops_APIP
		_hoops_AGAGR->_hoops_ISCS->valid = false;
		_hoops_AGAGR->_hoops_ISCS->_hoops_APGGR = false;
		_hoops_AGAGR->_hoops_ISCS->master_rendition = null;
	}

	if (_hoops_CGPHP)
		_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);
}


GLOBAL_FUNCTION void HD_Purge_Display_Lists (
	_hoops_GGAGR const *						_hoops_GHRI,
	_hoops_RRPHP	_hoops_ARPHP,
	void *								_hoops_HHCAP) {

	if (_hoops_GHRI != null) {
		_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);

		_hoops_AGCI alter *	_hoops_AGAGR = HOOPS_WORLD->_hoops_GPAI;

		while (_hoops_AGAGR != null) {
			_hoops_AGCI alter *	_hoops_RRAGR = _hoops_AGAGR->next;

			if (_hoops_AGAGR->_hoops_GHRI == _hoops_GHRI) {
				if (_hoops_ARPHP == null || _hoops_ARPHP(_hoops_AGAGR, _hoops_HHCAP))
					HD_Queue_Destroy_List (_hoops_AGAGR, false);
			}

			_hoops_AGAGR = _hoops_RRAGR;
		}

		_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);
	}
}

GLOBAL_FUNCTION void HI_Clean_Display_List (
		_hoops_GACR **		_hoops_PRPHP,
		bool				_hoops_HRPHP,
		bool				_hoops_CGPHP) 
{
	_hoops_GACR **		_hoops_PICI = _hoops_PRPHP;
	_hoops_GACR *		dl;

	while ((dl = *_hoops_PICI) != null) {
		if (dl->list != null) {
			HD_Queue_Destroy_List (dl->list, _hoops_CGPHP);

			if (_hoops_HRPHP) {
				*_hoops_PICI = dl->next;
				dl->list = null;
				dl->_hoops_RRHH |= _hoops_HGAGR;
				_hoops_HPRH (dl);
			}
			else
				return;
		}
		else
			_hoops_PICI = &dl->next;
	}
}



GLOBAL_FUNCTION void HI_Clean_Geometry_Display_Lists (
		Geometry *		geometry,
		bool			_hoops_IRPHP,
		bool			_hoops_CGPHP) 
{

	if (_hoops_CGPHP)
		_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);

	do switch (geometry->type) {
		case _hoops_HGCP: {
			Image *				image = (Image*) geometry;

			while (image) {
				if (image->_hoops_GAHA)
					HI_Clean_Display_List (&image->_hoops_GAHA, true, false);
				image = image->next;
			}
		}  break;

		case _hoops_SCIP:
		case _hoops_GSIP: {
			Polyhedron *		_hoops_IPRI = (Polyhedron *)geometry;
			Tristrip *			ts;
			Polyedge *			pe;
			Polymarker *		pm;

			if ((ts = _hoops_IPRI->tristrips) != null) do {
				if (ts->_hoops_GAHA)
					HI_Clean_Display_List (&ts->_hoops_GAHA, true, false);
			} while ((ts = ts->next) != null);

			if ((pe = _hoops_IPRI->_hoops_SHGPR) != null) do {
				if (pe->_hoops_GAHA)
					HI_Clean_Display_List (&pe->_hoops_GAHA, true, false);
			} while ((pe = pe->next) != null);

			if ((pm = _hoops_IPRI->_hoops_GIGPR) != null) do {
				if (pm->_hoops_GAHA)
					HI_Clean_Display_List (&pm->_hoops_GAHA, true, false);
			} while ((pm = pm->next) != null);

			if ((pe = _hoops_IPRI->_hoops_CHGPR) != null) do {
				if (pe->_hoops_GAHA)
					HI_Clean_Display_List (&pe->_hoops_GAHA, true, false);
			} while ((pe = pe->next) != null);


			if (_hoops_IPRI->_hoops_HGAIR != null) {
				for (int i = 0; i < _hoops_IGAIR; i++) {
					if (_hoops_IPRI->_hoops_HGAIR->data[i] != null)
						HI_Clean_Geometry_Display_Lists  (_hoops_IPRI->_hoops_HGAIR->data[i], true, false);
				}
			}
		}	break;
	} while (_hoops_IRPHP && (geometry = geometry->next) != null);

	if (_hoops_CGPHP)
		_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);
}


GLOBAL_FUNCTION void HI_Clean_Segment_Display_Lists (
	_hoops_CRCP const *		segment,
	bool				_hoops_CGPHP) {

	if (_hoops_CGPHP)
		_hoops_CAAI (HOOPS_WORLD->_hoops_SAAI);

	if (segment->_hoops_CSC != null) {
		_hoops_GPAGR		_hoops_RPAGR = segment->_hoops_CSC->_hoops_PHAGR();

		if (_hoops_RPAGR != null && _hoops_RPAGR->_hoops_IHAGR)
			HI_Clean_Display_List (&_hoops_RPAGR->_hoops_IHAGR, true, false);
	}

	_hoops_PGAIR *		_hoops_HGAIR = segment->_hoops_SSRIR();

	if (_hoops_HGAIR != null) {
		for (int i = 0; i < _hoops_IGAIR; i++) {
			if (_hoops_HGAIR->data[i] != null)
				HI_Clean_Geometry_Display_Lists  (_hoops_HGAIR->data[i], true, false);
		}
	}

	if (segment->geometry != null)
		HI_Clean_Geometry_Display_Lists (segment->geometry, true, false);

	Subsegment *		_hoops_GIPIA = segment->_hoops_RGRPR;

	if (_hoops_GIPIA != null) do {
		if (_hoops_GIPIA->type == _hoops_AGRPR) {
			_hoops_PGRPR *		include = (_hoops_PGRPR *)_hoops_GIPIA;

			HI_Clean_Segment_Display_Lists ((_hoops_CRCP *)include->_hoops_IGRPR, false);
		}
		else
			HI_Clean_Segment_Display_Lists ((_hoops_CRCP *)_hoops_GIPIA, false);
	} while ((_hoops_GIPIA = _hoops_GIPIA->next) != null);

	if (_hoops_CGPHP)
		_hoops_APAI (HOOPS_WORLD->_hoops_SAAI);
}



GLOBAL_FUNCTION void HI_Invalidate_Display_Lists (_hoops_AIGPR * _hoops_RIGC, Geometry alter *g)
{
	if (g->owner)
		HI_Invalidate_Segment_Display_Lists (_hoops_RIGC, g->owner, -2, g, 0);

	if (g->type == _hoops_GSIP || g->type == _hoops_SCIP) {
		Polyhedron alter * phon = (Polyhedron *)g;

		/* _hoops_HHSA _hoops_GII _hoops_CRHH _hoops_AIRI _hoops_HIGR _hoops_HRSPR */
		{
			Tristrip *			ts;

			if ((ts = phon->tristrips) != null) do {
				_hoops_GACR *		dl;

				if ((dl = ts->_hoops_GAHA) != null) do {
					dl->_hoops_GSAI = (_hoops_GHGI)DL_FLAG_INVALID;
				} while ((dl = dl->next) != null);
			} while ((ts = ts->next) != null);
		}
		/* _hoops_HHSA _hoops_GII _hoops_ACRI _hoops_AIRI _hoops_CPCI _hoops_IS _hoops_HRSPR */
		{
			Polyedge *			pe;

			if ((pe = phon->_hoops_SHGPR) != null) do {
				_hoops_GACR *		dl;

				if ((dl = pe->_hoops_GAHA) != null) do {
					dl->_hoops_GSAI = (_hoops_GHGI)DL_FLAG_INVALID;
				} while ((dl = dl->next) != null);
			} while ((pe = pe->next) != null);
		}
		/* _hoops_HHSA _hoops_GII _hoops_PAAI _hoops_AIRI _hoops_HIGR _hoops_HRSPR */
		{
			Polymarker *			pm;

			if ((pm = phon->_hoops_GIGPR) != null) do {
				_hoops_GACR *		dl;

				if ((dl = pm->_hoops_GAHA) != null) do {
					dl->_hoops_GSAI = (_hoops_GHGI)DL_FLAG_INVALID;
				} while ((dl = dl->next) != null);
			} while ((pm = pm->next) != null);
		}
		/* _hoops_HHSA _hoops_GII _hoops_ACGC _hoops_AIRI _hoops_CPCI _hoops_IS _hoops_HRSPR */
		{
			Polyedge *			pe;

			if ((pe = phon->_hoops_CHGPR) != null) do {
				_hoops_GACR *		dl;

				if ((dl = pe->_hoops_GAHA) != null) do {
					dl->_hoops_GSAI = (_hoops_GHGI)DL_FLAG_INVALID;
				} while ((dl = dl->next) != null);
			} while ((pe = pe->next) != null);
		}
	}
	else if (g->type == _hoops_CSIP) {
		PolyCylinder alter *	_hoops_HSPIR = (PolyCylinder *)g;
		_hoops_GACR alter *	dl;

		if ((dl = _hoops_HSPIR->_hoops_SGHIR) != null) do {
			dl->_hoops_GSAI = (_hoops_GHGI)DL_FLAG_INVALID;
		} while ((dl = dl->next) != null);

		if ((dl = _hoops_HSPIR->_hoops_GRHIR) != null) do {
			dl->_hoops_GSAI = (_hoops_GHGI)DL_FLAG_INVALID;
		} while ((dl = dl->next) != null);
	}
	else {
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, Sprintf_D (null,
								"Unexpected geometry type (#%d)", g->type));
	}
}

GLOBAL_FUNCTION void HI_Invalidate_Segment_Display_Lists (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_CRCP const *			_hoops_SRCP,
	int						type,
	Geometry const *		geo,
	unsigned int			_hoops_GCRC) 
{
	_hoops_RSIIR(_hoops_RIGC);

	_hoops_GACR *			dl;

	// _hoops_AAHS _hoops_RGR _hoops_ARPP _hoops_RH _hoops_CRPHP _hoops_IS _hoops_SRCH _hoops_SRPHP
	_hoops_CAAI (HOOPS_WORLD->_hoops_GAPHP);

	{
		_hoops_SPAGR		_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, _hoops_RIGC->thread_id);

		if (HOOPS_WORLD->_hoops_RAPHP == null) {
			HOOPS_WORLD->_hoops_RAPHP = 
				POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_AAPHP)(HOOPS_WORLD->memory_pool, _hoops_PAPHP);
			HOOPS_WORLD->_hoops_HAPHP = HOOPS_WORLD->_hoops_GPPI;
		}

		if (HOOPS_WORLD->_hoops_GPPI != HOOPS_WORLD->_hoops_HAPHP) {
			HOOPS_WORLD->_hoops_RAPHP->Flush();
			HOOPS_WORLD->_hoops_HAPHP = HOOPS_WORLD->_hoops_GPPI;
		}

		int _hoops_IAPHP = 0;
		int _hoops_CAPHP = 0;

		if (type == -1)
			_hoops_IAPHP = ~0; // _hoops_HCR _hoops_CSSC
		else if (type == -2)
			; // _hoops_SAHR _hoops_SCAC _hoops_RH _hoops_CAGH _hoops_PAPA _hoops_CIPH
		else
			_hoops_IAPHP = _hoops_AGPGR(type);

		if (HOOPS_WORLD->_hoops_RAPHP->LookupItem(_hoops_SRCP, &_hoops_CAPHP) == VHASH_STATUS_SUCCESS) {

			if ((_hoops_IAPHP&~_hoops_CAPHP) == 0) {
				_hoops_APAI (HOOPS_WORLD->_hoops_GAPHP);
				return;
			}

			HOOPS_WORLD->_hoops_RAPHP->ReplaceItem(_hoops_SRCP, _hoops_IAPHP|_hoops_CAPHP);
		}
		else
			HOOPS_WORLD->_hoops_RAPHP->InsertItem(_hoops_SRCP, _hoops_IAPHP);

		_hoops_APAI (HOOPS_WORLD->_hoops_GAPHP);


		_hoops_AHAGR *		_hoops_CSC;

		if ((_hoops_CSC = _hoops_SRCP->_hoops_CSC) != null) do {
			_hoops_GPAGR	_hoops_RPAGR = _hoops_CSC->_hoops_PHAGR();

			if (_hoops_RPAGR != null) {
				if ((dl = _hoops_RPAGR->_hoops_GAHA) != null) do {
					if (!_hoops_GCRC || ANYBIT (dl->_hoops_PRRI, _hoops_GCRC)) {
						HI_Clean_Display_List (&_hoops_RPAGR->_hoops_GAHA, true, false);
						break;
					}
				} while ((dl = dl->next) != null);
				if ((dl = _hoops_RPAGR->_hoops_HHICA) != null) do {
					if (!_hoops_GCRC || ANYBIT (dl->_hoops_PRRI, _hoops_GCRC)) {
						HI_Clean_Display_List (&_hoops_RPAGR->_hoops_HHICA, true, false);
						break;
					}
				} while ((dl = dl->next) != null);
			}
		} while ((_hoops_CSC = _hoops_CSC->next) != null);
	}

	
	_hoops_RPAPA * _hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(_hoops_SRCP);

	if (_hoops_APAPA != null) {
		_hoops_RPAPA::UniqueCursor *	uc = _hoops_APAPA->GetUniqueCursor();
		void *	_hoops_SAPHP = null;
		_hoops_PHIP *	_hoops_RRA;
		while((_hoops_RRA = uc->Peek()) != null) {
			if (_hoops_RRA->owner != _hoops_SAPHP) {
				HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, _hoops_RRA->owner, _hoops_AHIP, _hoops_RRA, 0);
				_hoops_SAPHP = _hoops_RRA->owner;
			}
			uc->Advance();
		}
		delete uc;
	}

	if (geo != null) {

		_hoops_APAPA = HOOPS_WORLD->_hoops_PPAPA->Lookup(geo);

		if (_hoops_APAPA != null) {
			_hoops_RPAPA::UniqueCursor *	uc = _hoops_APAPA->GetUniqueCursor();
			void *	_hoops_SAPHP = null;
			_hoops_PHIP *	_hoops_RRA;
			while((_hoops_RRA = uc->Peek()) != null) {
				if (_hoops_RRA->owner != _hoops_SAPHP) {
					HI_Invalidate_Segment_Display_Lists(_hoops_RIGC, _hoops_RRA->owner, _hoops_AHIP, _hoops_RRA, 0);
					_hoops_SAPHP = _hoops_RRA->owner;
				}
				uc->Advance();
			}
			delete uc;
		}
	}

	switch (type) {
		case -2: {
			/* _hoops_SAHR _hoops_SCAC _hoops_RH _hoops_CAGH _hoops_PAPA _hoops_CIPH */
		} break;

		case -1: { /* _hoops_GRH _hoops_AGIR _hoops_IS _hoops_HRCI _hoops_HCR _hoops_CSSC */
			/* _hoops_HPGGR _hoops_RH _hoops_CAGH'_hoops_GRI _hoops_ISII _hoops_AIRI _hoops_CPCI _hoops_GAR _hoops_AIPH */
			if (_hoops_SRCP->_hoops_CSC != null) {
				_hoops_GPAGR	_hoops_RPAGR = _hoops_SRCP->_hoops_CSC->_hoops_PHAGR();

				if (_hoops_RPAGR != null && (dl = _hoops_RPAGR->_hoops_IHAGR) != null) do {
					dl->_hoops_GSAI = (_hoops_GHGI)DL_FLAG_INVALID;
				} while ((dl = dl->next) != null);
			}
		} break;


		case _hoops_CHIP:
		case _hoops_RIIP:
		case _hoops_GIIP:
		case _hoops_PIIP:
		case _hoops_HIIP:
		case _hoops_IIIP: {
			/* _hoops_HPGGR _hoops_RH _hoops_CAGH'_hoops_GRI _hoops_ISII _hoops_AIRI _hoops_CPCI _hoops_GAR _hoops_AIPH */
			if (_hoops_SRCP->_hoops_CSC != null) {
				_hoops_GPAGR	_hoops_RPAGR = _hoops_SRCP->_hoops_CSC->_hoops_PHAGR();

				if (_hoops_RPAGR != null && (dl = _hoops_RPAGR->_hoops_IHAGR) != null) do {
					dl->_hoops_GSAI = (_hoops_GHGI)DL_FLAG_INVALID;
				} while ((dl = dl->next) != null);
			}
		}	break;

		case _hoops_GRCP:
		case _hoops_RRCP:
		case _hoops_SGCP:
		case _hoops_CGCP:
		case _hoops_RCIP: {
		}	break;

		case _hoops_GGCP:
		case _hoops_GSIP:
		case _hoops_PRCP:
		case _hoops_ASIP:
		case _hoops_CSIP:
		case _hoops_HSIP:
		case _hoops_SCIP: {
		}	break;

		case _hoops_SIIP:
		case _hoops_PCIP:
		case _hoops_PIRS: {
		}	break;
		case _hoops_HGCP: {
		}	break;
		case _hoops_AGCP: {
		}	break;

		case _hoops_HGPGR:
		case _hoops_ICIP:
		case HK_STRING_CURSOR: {
		}	break;

		case _hoops_AHIP: {
		}	break;

		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, Sprintf_D (null,
									"Unexpected segment geometry type (#%d)", type));
		}
	}
}

GLOBAL_FUNCTION bool HI_Get_Display_List(
	_hoops_GGAGR const *			_hoops_GHRI,
	_hoops_GACR alter **	_hoops_ASRGR,
	_hoops_GACR alter **	_hoops_PAGR) {

	_hoops_GACR *			dl;

	if ((dl = *_hoops_ASRGR) != null) do {
		if (dl->_hoops_GHRI == _hoops_GHRI) {
			*_hoops_PAGR = dl;
			return false;
		}
		if (_hoops_GHRI->_hoops_CAIAP != _hoops_GRIAP &&
			_hoops_GHRI->_hoops_CAIAP == dl->_hoops_GHRI->_hoops_CAIAP) {
			*_hoops_PAGR = dl;
			return false;
		}
	} while ((dl = dl->next) != null);

	ZALLOC(dl, _hoops_GACR);
	dl->type = _hoops_HCIIR;
	dl->_hoops_HIHI = 1;
	dl->_hoops_GHRI = _hoops_GHRI;
	dl->_hoops_GGCI = -1;

	if ((dl->next = *_hoops_ASRGR) != null)
		dl->next->backlink = &dl->next;
	dl->backlink = _hoops_ASRGR;

	*_hoops_ASRGR = dl;
	*_hoops_PAGR = dl;

	return true;
}





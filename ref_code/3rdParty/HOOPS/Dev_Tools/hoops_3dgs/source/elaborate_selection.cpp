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
 * $Id: obf_tmp.txt 1.93 2010-06-04 21:37:17 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "please.h"
#include "select.h"
#include "hd_proto.h"
#include "hi_proto.h"

GLOBAL_FUNCTION void HI_Free_Include_Chain (
	_hoops_RISAP *			_hoops_HACAH) {
	_hoops_RISAP *			prev;

	do {
		prev = _hoops_HACAH->prev;
		if (BIT(_hoops_HACAH->include->_hoops_RRHH, _hoops_HGAGR))
			((_hoops_PGRPR *)_hoops_HACAH->include)->owner = null;
		_hoops_HPRH (_hoops_HACAH->include);
		FREE (_hoops_HACAH, _hoops_RISAP);
	} while ((_hoops_HACAH = prev) != null);
}

#ifndef DISABLE_SELECTION

local _hoops_RISAP alter * _hoops_IACAH (
	_hoops_RISAP alter	*	_hoops_CACAH) {
	_hoops_RISAP alter	*	_hoops_SACAH;
	_hoops_RISAP alter	*	_hoops_GPCAH;
	_hoops_RISAP alter	*	head;

	if (_hoops_CACAH == null) return null;

	ALLOC (head, _hoops_RISAP);
	head->include = _hoops_CACAH->include; _hoops_PRRH (_hoops_CACAH->include);
	_hoops_GPCAH = head;
	while ((_hoops_CACAH = _hoops_CACAH->prev) != null) {
		ALLOC (_hoops_SACAH, _hoops_RISAP);
		_hoops_SACAH->include = _hoops_CACAH->include; _hoops_PRRH (_hoops_CACAH->include);
		_hoops_GPCAH->prev = _hoops_SACAH;
		_hoops_GPCAH = _hoops_SACAH;
	}
	_hoops_GPCAH->prev = null;
	return head;
}


local void _hoops_RPCAH (
	_hoops_AISAP *	_hoops_ACSAP) {

	while (_hoops_ACSAP != null) {
		_hoops_AISAP *	victim = _hoops_ACSAP;
		_hoops_ACSAP = victim->next;
		FREE (victim, _hoops_AISAP);
	}
}


local bool _hoops_APCAH (_hoops_RPIIR * _hoops_PPCAH, _hoops_RPIIR * _hoops_HPCAH)
{
	if (_hoops_PPCAH->_hoops_PCSAP > _hoops_HPCAH->_hoops_PCSAP)
		return true;
	else
		return false;
}


/* _hoops_GHIS _hoops_SRS _hoops_HPP _hoops_IPCAH, _hoops_PSCR _hoops_HPP _hoops_SSH */
local bool _hoops_CPCAH (_hoops_RPIIR * _hoops_PPCAH, _hoops_RPIIR * _hoops_HPCAH)
{
	if ((_hoops_PPCAH->_hoops_HCSAP > _hoops_HPCAH->_hoops_HCSAP) ||
		((_hoops_PPCAH->_hoops_HCSAP == _hoops_HPCAH->_hoops_HCSAP) && (_hoops_PPCAH->_hoops_PCSAP > _hoops_HPCAH->_hoops_PCSAP)))
		return true;
	else 
		return false;
}


#define _hoops_PCAHP(i) ((i-1)/2)
#define _hoops_HCAHP(i) (2*i+1)
#define _hoops_ICAHP(i) (2*i+2)

local void _hoops_GSAHP (_hoops_IPIIR alter *heap, int i) {
	int p = _hoops_PCAHP(i);
	_hoops_RPIIR *temp;

	while (i > 0) {
		if (heap->compare (heap->_hoops_SPIIR[i], heap->_hoops_SPIIR[p])) {
			temp = heap->_hoops_SPIIR[i];
			heap->_hoops_SPIIR[i] = heap->_hoops_SPIIR[p];
			heap->_hoops_SPIIR[p] = temp;
			i = p;
			p = _hoops_PCAHP(p);
		}
		else
			break;
	}
}


local void _hoops_ASAHP(_hoops_IPIIR alter *heap, int i) 
{
	_hoops_RPIIR *temp;
	int l = _hoops_HCAHP(i);
	int r = _hoops_ICAHP(i);
	int _hoops_PSAHP = i;
	int _hoops_HSAHP = i;

	while (l < heap->used) {
		if (heap->compare (heap->_hoops_SPIIR[l], heap->_hoops_SPIIR[_hoops_HSAHP]))
			_hoops_PSAHP = l;
		if (r < heap->used)
			if (heap->compare (heap->_hoops_SPIIR[r], heap->_hoops_SPIIR[_hoops_PSAHP]))
				_hoops_PSAHP = r;
		if (_hoops_PSAHP != _hoops_HSAHP) {
			temp = heap->_hoops_SPIIR[_hoops_HSAHP];
			heap->_hoops_SPIIR[_hoops_HSAHP] = heap->_hoops_SPIIR[_hoops_PSAHP];
			heap->_hoops_SPIIR[_hoops_PSAHP] = temp;
			l = _hoops_HCAHP (_hoops_PSAHP);
			r = _hoops_ICAHP (_hoops_PSAHP);
			_hoops_HSAHP = _hoops_PSAHP;
		}
		else
			break;
	}
}


local void _hoops_SPCAH (
	_hoops_IPIIR alter *heap,
	_hoops_RPIIR alter *si) {
	if (heap->used == heap->allocated) {
		_hoops_RPIIR alter **_hoops_PCAHA;

		heap->allocated *= 2;
		ALLOC_ARRAY(_hoops_PCAHA, heap->allocated, _hoops_RPIIR *);
		_hoops_AIGA(heap->_hoops_SPIIR, heap->used, _hoops_RPIIR *, _hoops_PCAHA);
		FREE_ARRAY(heap->_hoops_SPIIR, heap->used, _hoops_RPIIR *);
		heap->_hoops_SPIIR = _hoops_PCAHA;
	}
	heap->_hoops_SPIIR[heap->used++] = si;
	_hoops_GSAHP(heap, heap->used-1);
}


GLOBAL_FUNCTION _hoops_RPIIR * HI_Selection_Item_Heap_Pop (
	_hoops_IPIIR alter *heap) {
	_hoops_RPIIR *si;

	if (heap->used == 0)
		return null;
	si = heap->_hoops_SPIIR[0];
	heap->_hoops_SPIIR[0] = heap->_hoops_SPIIR[heap->used-1];
	heap->_hoops_SPIIR[heap->used-1] = si;
	heap->used--;
	if (heap->used)
		_hoops_ASAHP(heap, 0);
	return si;
}


GLOBAL_FUNCTION void HI_Free_Selection_Item (_hoops_RPIIR *victim)
{
	victim->_hoops_APHGA.release();
	if (victim->_hoops_SISAP)
		HI_Free_Include_Chain (victim->_hoops_SISAP);
	_hoops_RPCAH (victim->_hoops_ACSAP);
	_hoops_HPRH (victim->item);
	FREE (victim, _hoops_RPIIR);
}


local _hoops_RPIIR * _hoops_GHCAH (
	Net_Rendition const &		nr,
	_hoops_ACCCP alter *	sc,
	Selection_Event alter *		_hoops_GPIIR,
	float						_hoops_RCSAP,
	float						_hoops_HCSAP) {
	_hoops_IPIIR *		_hoops_CPIIR = _hoops_GPIIR->_hoops_HPIIR;
	_hoops_RPIIR alter		*si, *victim;

	if (_hoops_CPIIR == null) {
		ALLOC (_hoops_CPIIR, _hoops_IPIIR);
		_hoops_CPIIR->flags = 0;
		_hoops_CPIIR->used = 0;
		_hoops_CPIIR->allocated = 2;
		_hoops_CPIIR->_hoops_SCSAP = null;
		_hoops_CPIIR->_hoops_GSSAP = 0;
		if (BIT (sc->options, _hoops_RHCAH)) {
			_hoops_CPIIR->compare = _hoops_APCAH;
			if (sc->_hoops_GCCIA == _hoops_IICIA)
				_hoops_CPIIR->flags |= _hoops_CCSAP;
		}
		else
			_hoops_CPIIR->compare = _hoops_CPCAH;
		ALLOC_ARRAY(_hoops_CPIIR->_hoops_SPIIR, _hoops_CPIIR->allocated, _hoops_RPIIR *);
		_hoops_GPIIR->_hoops_HPIIR = _hoops_CPIIR;
	} 

	/* _hoops_RSIH _hoops_RIARR _hoops_RPP _hoops_SR'_hoops_RISP _hoops_RHHR _hoops_RH _hoops_SAIPR _hoops_PPR _hoops_ISCP _hoops_SCGR _hoops_AHCAH _hoops_HRGR _hoops_PHCAH _hoops_HSAR _hoops_RH _hoops_HRGI _hoops_SR
	 * _hoops_HS _hoops_GCPRA _hoops_AARI _hoops_HIS _hoops_SGIP */
	if (_hoops_CPIIR->used > sc->_hoops_GCCIA) {
		_hoops_RPIIR *_hoops_HHCAH = _hoops_CPIIR->_hoops_SPIIR[0];
		if (BIT (sc->options, _hoops_RHCAH)) {
			if (_hoops_RCSAP > _hoops_HHCAH->_hoops_PCSAP)
				return null;
		}
		else {
			if (_hoops_HCSAP > _hoops_HHCAH->_hoops_HCSAP) 
				return null;
			if (_hoops_HCSAP == _hoops_HHCAH->_hoops_HCSAP &&
				_hoops_RCSAP > _hoops_HHCAH->_hoops_PCSAP)
				return null;
		}
	}

	ALLOC (si, _hoops_RPIIR);
	ZERO_STRUCT (si, _hoops_RPIIR);
	si->_hoops_PCSAP = _hoops_RCSAP;
	si->_hoops_HCSAP = _hoops_HCSAP;
	if (BIT(_hoops_CPIIR->flags, _hoops_CCSAP)) {
		si->next = _hoops_CPIIR->_hoops_SCSAP;
		_hoops_CPIIR->_hoops_SCSAP = si;
		_hoops_CPIIR->_hoops_GSSAP++;
	}
	else {
		si->next = null;
		_hoops_SPCAH (_hoops_CPIIR, si);
	}

	/* _hoops_GRHP _hoops_IHCAH (_hoops_PPR _hoops_HCPCA _hoops_RH _hoops_HRGI _hoops_IGCI _hoops_PSAP _hoops_RH _hoops_SIHPA _hoops_CCGR _hoops_SR _hoops_CHCAH _hoops_CCA _hoops_RH _hoops_IPPAR _hoops_GHSHA _hoops_SAIPR */
	while (_hoops_CPIIR->used-1 > sc->_hoops_GCCIA) {
		victim = HI_Selection_Item_Heap_Pop (_hoops_CPIIR);
		HI_Free_Selection_Item (victim);
	}

	/* _hoops_RPP _hoops_SHCAH _hoops_HPP _hoops_IPCAH _hoops_PPR _hoops_SR _hoops_RHHR _hoops_RH _hoops_IPPAR _hoops_GHSHA _hoops_SAIPR, _hoops_SR _hoops_PAH _hoops_PSRAR _hoops_RH _hoops_GHSHA 
	 * _hoops_RPPS _hoops_GAR _hoops_SR _hoops_PHHR _hoops_IS _hoops_ASAC _hoops_CAIR _hoops_HHH _hoops_IPHR _hoops_SPHR _hoops_GPP */
	if (_hoops_CPIIR->used > sc->_hoops_GCCIA &&
		!BIT (sc->options, _hoops_RHCAH)) {
		_hoops_RPIIR *_hoops_HHCAH = _hoops_CPIIR->_hoops_SPIIR[0];

		if (_hoops_HHCAH->_hoops_HCSAP == 0.0f) {
			sc->_hoops_GICAH = 0.0f;
			sc->_hoops_RICAH.x = sc->_hoops_RICAH.y = 0.0f;
			sc->bounding.left = sc->bounding.right = sc->_hoops_AICAH.x;
			sc->bounding.bottom = sc->bounding.top = sc->_hoops_AICAH.y;
		}
		else {
			float						_hoops_PICAH;
			_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;

			_hoops_PICAH = _hoops_SGIHR (_hoops_HHCAH->_hoops_HCSAP);

			sc->_hoops_RICAH.x = 0.999f*_hoops_PICAH*sc->_hoops_HICAH.x;
			sc->_hoops_RICAH.y = 0.999f*_hoops_PICAH*sc->_hoops_HICAH.y;
			sc->bounding.left	= sc->_hoops_AICAH.x - sc->_hoops_RICAH.x;
			sc->bounding.right	= sc->_hoops_AICAH.x + sc->_hoops_RICAH.x;
			sc->bounding.bottom = sc->_hoops_AICAH.y - sc->_hoops_RICAH.y;
			sc->bounding.top	= sc->_hoops_AICAH.y + sc->_hoops_RICAH.y;

			if (!BIT (sc->options, _hoops_IICAH)) {
				if (sc->bounding.left < (float)_hoops_SGRA->_hoops_PHRA.left)
					sc->bounding.left = (float)_hoops_SGRA->_hoops_PHRA.left;
				else if (sc->bounding.left > (float)_hoops_SGRA->_hoops_PHRA.right)
					sc->bounding.left = (float)_hoops_SGRA->_hoops_PHRA.right;

				if (sc->bounding.right < (float)_hoops_SGRA->_hoops_PHRA.left)
					sc->bounding.right = (float)_hoops_SGRA->_hoops_PHRA.left;
				else if (sc->bounding.right > (float)_hoops_SGRA->_hoops_PHRA.right)
					sc->bounding.right = (float)_hoops_SGRA->_hoops_PHRA.right;

				if (sc->bounding.bottom < (float)_hoops_SGRA->_hoops_PHRA.bottom)
					sc->bounding.bottom = (float)_hoops_SGRA->_hoops_PHRA.bottom;
				else if (sc->bounding.bottom > (float)_hoops_SGRA->_hoops_PHRA.top)
					sc->bounding.bottom = (float)_hoops_SGRA->_hoops_PHRA.top;

				if (sc->bounding.top < (float)_hoops_SGRA->_hoops_PHRA.bottom)
					sc->bounding.top = (float)_hoops_SGRA->_hoops_PHRA.bottom;
				else if (sc->bounding.top > (float)_hoops_SGRA->_hoops_PHRA.top)
					sc->bounding.top = (float)_hoops_SGRA->_hoops_PHRA.top;
			}
		}
	}
	return si;
} /* _hoops_RSGR _hoops_API _hoops_CICAH */


local _hoops_RPIIR * _hoops_SICAH (
	Net_Rendition const &		nr,
	_hoops_ACCCP alter *	sc,
	Selection_Event alter *		_hoops_GPIIR,
	float						_hoops_RCSAP,
	float						_hoops_HCSAP) {
	_hoops_RPIIR alter *		si;

	UNREFERENCED(nr);

	ALLOC (si, _hoops_RPIIR);
	ZERO_STRUCT (si, _hoops_RPIIR);
	si->_hoops_PCSAP = _hoops_RCSAP;
	si->_hoops_HCSAP = _hoops_HCSAP;
	si->next = _hoops_GPIIR->_hoops_APIIR;
	_hoops_GPIIR->_hoops_APIIR = si;
	sc->_hoops_GCCAH++;

	return si;
}
#endif



#define _hoops_RCCAH(_hoops_AIPPA,_hoops_PIPPA) \
			((_hoops_AIPPA->_hoops_HISAP > _hoops_PIPPA->_hoops_HISAP) ||  \
			 (_hoops_AIPPA->_hoops_HISAP == _hoops_PIPPA->_hoops_HISAP && _hoops_AIPPA->_hoops_IISAP > _hoops_PIPPA->_hoops_IISAP))
#define _hoops_ACCAH(_hoops_AIPPA,_hoops_PIPPA) (_hoops_AIPPA->_hoops_HISAP == _hoops_PIPPA->_hoops_HISAP && _hoops_AIPPA->_hoops_IISAP == _hoops_PIPPA->_hoops_IISAP)

#define QS_TYPE					_hoops_AISAP **
#define QS_COMPARETYPE			_hoops_AISAP *
#define QS_VAL(thing,a)			(thing[a]->_hoops_HISAP)
#define QS_PIVOT_VAL(thing,a)	(thing[a])
#define QS_COMPLEX_COMPARE(thing,a,b) _hoops_RCCAH(thing[a],thing[b])
#define QS_SWAP(thing,a,b)		{_hoops_AISAP * tmp = thing[a]; thing[a] = thing[b]; thing[b] = tmp;}
#define QS_EQUAL(thing,a,b)		_hoops_ACCAH(thing[a],thing[b])
#include "utility/hqsort.h"


GLOBAL_FUNCTION void HD_Elaborate_Selection (
	Net_Rendition const &		nr,
	Geometry const *			item,
	Key							_hoops_HSICA,
	Key							_hoops_CISAP,
	int							offset1,
	int							offset2,
	int							offset3,
	float						_hoops_RCSAP,
	float						_hoops_HCSAP,
	_hoops_ACHR					_hoops_PCCAH,
	_hoops_AISAP *			_hoops_ACSAP) {
#ifndef DISABLE_SELECTION
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_ACCCP alter	*	sc = dc->_hoops_APHHP;
	Selection_Event alter *		_hoops_GPIIR = sc->event;
	_hoops_RPIIR alter *		si;

	if (sc->_hoops_HCCAH != null && nr->_hoops_IRR->_hoops_GRCRP != _hoops_PGCRP) {
		/* _hoops_ASSA _hoops_CAGH _hoops_PAR _hoops_CAGH _hoops_HHIS _hoops_GHSHA, _hoops_SAHR _hoops_PRIA _hoops_RCAHR */
		_hoops_ICCAH	*_hoops_CCCAH = sc->_hoops_HCCAH;

		if (!_hoops_CCCAH->valid) {
			_hoops_CCCAH->_hoops_HCSAP = _hoops_HCSAP;
			_hoops_CCCAH->_hoops_RCSAP = _hoops_RCSAP;
			_hoops_CCCAH->valid = true;
		}
		else if (BIT (sc->options, _hoops_RHCAH)) {
			if (_hoops_RCSAP < _hoops_CCCAH->_hoops_RCSAP)
				_hoops_CCCAH->_hoops_RCSAP = _hoops_RCSAP;
		}
		else {
			if (_hoops_HCSAP < _hoops_CCCAH->_hoops_HCSAP) {
				_hoops_CCCAH->_hoops_HCSAP = _hoops_HCSAP;
				_hoops_CCCAH->_hoops_RCSAP = _hoops_RCSAP;
			}
			else if (_hoops_HCSAP == _hoops_CCCAH->_hoops_HCSAP) {
				if (_hoops_RCSAP < _hoops_CCCAH->_hoops_RCSAP)
					_hoops_CCCAH->_hoops_RCSAP = _hoops_RCSAP;
			}
		}
		_hoops_CCCAH->_hoops_SCCAH |= _hoops_PCCAH;

		_hoops_RPCAH (_hoops_ACSAP);
		return;
	}


	if ((BIT (item->_hoops_RRHH, _hoops_PASIR) || sc->_hoops_GSCAH) &&
		!BIT (nr->transform_rendition->heuristics, _hoops_IRI) ||
		!BIT (nr->transform_rendition->heuristics, _hoops_GAIRP) ||
		(BIT (sc->options, _hoops_RSCAH) && !BIT (sc->options, _hoops_RHCAH)))
		si = _hoops_SICAH (nr, sc, _hoops_GPIIR, _hoops_RCSAP, _hoops_HCSAP);
	else 
		si = _hoops_GHCAH (nr, sc, _hoops_GPIIR, _hoops_RCSAP, _hoops_HCSAP);

	if (si == null) {
		_hoops_RPCAH (_hoops_ACSAP);
		return;
	}

	if (BIT (nr->_hoops_IRR->restricted_selectability, _hoops_PCCAH))
		si->_hoops_GCSAP = _hoops_RIII (_hoops_GPIIR->_hoops_CHSHA);
	else if (_hoops_GPIIR->_hoops_CHSHA == _hoops_HPSHA)
		si->_hoops_GCSAP = _hoops_IPSHA;
	else
		si->_hoops_GCSAP = _hoops_SPSHA;

	si->_hoops_SISAP = _hoops_IACAH (sc->_hoops_ASCAH);
	si->item = (_hoops_HPAH const *)item;
	_hoops_PRRH (item);
	si->_hoops_HSICA = _hoops_HSICA;
	si->_hoops_CISAP = _hoops_CISAP;
	si->offset1 = offset1;
	si->offset2 = offset2;
	si->offset3 = offset3;
	si->xw = sc->xw;
	si->yw = sc->yw;
	si->_hoops_PCSAP = _hoops_RCSAP;
	si->_hoops_APHGA = nr;

	if (_hoops_ACSAP != null && BIT (nr->transform_rendition->heuristics, _hoops_GAIRP)) {
		_hoops_AISAP **_hoops_AICHR;
		_hoops_AISAP *ptr;
		int i, count;

		ptr = _hoops_ACSAP;
		count = 0;
		do {
			++count;
		} while ((ptr = ptr->next) != null);

		ALLOC_ARRAY (_hoops_AICHR, count, _hoops_AISAP *);
		ptr = _hoops_ACSAP;
		for (i = 0; i < count; i++) {
			_hoops_AICHR[i] = ptr;
			if (BIT (sc->options, _hoops_RHCAH)) {
				ptr->_hoops_HISAP = ptr->_hoops_IISAP;
				ptr->_hoops_IISAP = i;
			}
			ptr = ptr->next;
		}
 
		quick_sort (_hoops_AICHR, 0, count-1);

		for (i = 0; i < count-1; i++)
			_hoops_AICHR[i]->next = _hoops_AICHR[i+1];
		_hoops_AICHR[count-1]->next = null;

		_hoops_ACSAP = _hoops_AICHR[0];
		FREE_ARRAY (_hoops_AICHR, count, _hoops_AISAP *);

		if ((item->type == _hoops_SCIP || item->type == _hoops_GSIP) &&
			nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR < count) {
			_hoops_AISAP * _hoops_PSCAH = _hoops_ACSAP;
			int _hoops_HSCAH = 0;
			while (_hoops_PSCAH->next != null && _hoops_HSCAH < nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR-1) {
				_hoops_HSCAH++;
				_hoops_PSCAH = _hoops_PSCAH->next;
			}
			_hoops_RPCAH (_hoops_PSCAH->next);
			_hoops_PSCAH->next = null;
		}
	}
	si->_hoops_ACSAP = _hoops_ACSAP;

	/* (_hoops_PSCPR _hoops_RH _hoops_SARA _hoops_PCRR _hoops_SHRRR _hoops_CCGR _hoops_SPHR) */
#endif
}

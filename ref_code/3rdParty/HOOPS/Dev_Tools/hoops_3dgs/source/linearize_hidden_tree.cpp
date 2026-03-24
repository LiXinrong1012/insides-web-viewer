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
 * $Id: obf_tmp.txt 1.70 2010-09-16 17:21:22 warren Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "hidden.h"
#include "hd_proto.h"

struct _hoops_AHCIA {
	float *_hoops_PAGCP;
	_hoops_CASS **_hoops_AICHR;
};


#define QS_TYPE				struct _hoops_AHCIA *					
#define QS_VAL(thing,a)		(thing->_hoops_PAGCP[a])	
#define QS_COMPARE(f1,f2)	(f1<f2)					
#define QS_SWAP(thing,a,b) {		\
	Swap (thing->_hoops_PAGCP[a], thing->_hoops_PAGCP[b]); \
	Swap (thing->_hoops_AICHR[a], thing->_hoops_AICHR[b]); \
}

#include "utility/hqsort.h"


local _hoops_CASS *_hoops_IACPI(
	Display_Context const *	dc,
	_hoops_CASS alter *			head,
	int						count,
	int						_hoops_ICHIH) 
{
	float *_hoops_PAGCP;
	float displacement;
	_hoops_CASS **_hoops_AICHR;
	_hoops_CASS *ptr;
	int i;
	struct _hoops_AHCIA _hoops_RCCIA;

	POOL_ALLOC_ARRAY_CACHED(_hoops_AICHR, count, _hoops_CASS *, dc->memory_pool);
	POOL_ALLOC_ARRAY_CACHED(_hoops_PAGCP, count, float, dc->memory_pool);
	_hoops_RCCIA._hoops_AICHR = _hoops_AICHR;
	_hoops_RCCIA._hoops_PAGCP = _hoops_PAGCP;
	ptr = head;
	if (BIT(_hoops_ICHIH,_hoops_GAI)) {
		for (i = 0; i < count; i++) {
			_hoops_AICHR[i] = ptr;
			_hoops_PAGCP[i] = (float)-ptr->values;
			ptr = ptr->next;
		}
	}
	else if (BIT(_hoops_ICHIH, _hoops_HSSS)) {
		for (i = 0; i < count; i++) {
			_hoops_AICHR[i] = ptr;
			if (ptr->_hoops_ASHSA->type == _hoops_RIGCP || ptr->_hoops_ASHSA->type == _hoops_HIGCP) {
				if (ptr->_hoops_ASHSA->_hoops_APHGA->_hoops_CPP->_hoops_PRH._hoops_RGGIP) {
					if (BIT (ptr->flags, HF_ZSORT_BACKFACE))
						_hoops_PAGCP[i] = ptr->_hoops_ASHSA->_hoops_AICR;  //_hoops_CHAA _hoops_ISSC _hoops_RSSI _hoops_IS _hoops_HGCR _hoops_CHCC _hoops_IARRA (_hoops_HAS._hoops_IAS. _hoops_GHIPR)
					else if (BIT (ptr->flags, HF_ZSORT_FRONTFACE))
						_hoops_PAGCP[i] = ptr->_hoops_ASHSA->_hoops_RICR;  //_hoops_CHAA _hoops_RIPS _hoops_RSSI _hoops_IS _hoops_HGCR _hoops_CHCC _hoops_SPHR (_hoops_HAS._hoops_IAS. _hoops_GGR _hoops_RIPS)
					else
						_hoops_PAGCP[i] = (ptr->_hoops_ASHSA->_hoops_AICR + ptr->_hoops_ASHSA->_hoops_RICR) * 0.5f;
				}
				else
					_hoops_PAGCP[i] = ptr->_hoops_ASHSA->_hoops_AICR; //_hoops_AGIRA _hoops_CACPI _hoops_SACPI _hoops_RSIH _hoops_HIS _hoops_SCH _hoops_PAH _hoops_HSPP _hoops_GPCPI _hoops_GGR _hoops_GHIR
			}
			else {
				_hoops_PAGCP[i] = (ptr->_hoops_ASHSA->_hoops_AICR + ptr->_hoops_ASHSA->_hoops_RICR) * 0.5f;  //_hoops_GHIS _hoops_SHISR _hoops_PAIRR (_hoops_GRAA-_hoops_GARI & _hoops_GRAA-_hoops_IRAS) _hoops_HPP _hoops_RPCPI
			}
			/* _hoops_RIIA _hoops_IIGR _hoops_RCPH _hoops_APCPI _hoops_ARPP _hoops_PPR _hoops_RAS _hoops_RH _hoops_GHIS, _hoops_SR _hoops_CHAA _hoops_RPHR _hoops_GAR _hoops_SR 
			   _hoops_CHR _hoops_CCCH _hoops_CRGR _hoops_RH _hoops_CRPR _hoops_IIGR _hoops_HSH _hoops_IS _hoops_PGSA */
			displacement = ptr->_hoops_ASHSA->_hoops_APHGA->transform_rendition->_hoops_SHIH;
			if (_hoops_HRCSA (ptr->_hoops_ASHSA->type))
				displacement += ptr->_hoops_ASHSA->_hoops_APHGA->transform_rendition->_hoops_CHIH;
			displacement *= _hoops_ISSIR(ptr->_hoops_ASHSA->_hoops_APHGA->transform_rendition);
			_hoops_PAGCP[i] += displacement;

			ptr = ptr->next;
		}
	}
	else {
		for (i = 0; i < count; i++) {
			_hoops_AICHR[i] = ptr;
			_hoops_PAGCP[i] = ptr->_hoops_ASHSA->_hoops_AICR;
			ptr = ptr->next;
		}

	}
 
	quick_sort (&_hoops_RCCIA, 0, count-1);

	for (i = 0; i < count-1; i++) {
		_hoops_AICHR[i]->next = _hoops_AICHR[i+1];
	}
	_hoops_AICHR[count-1]->next = null;
	head = _hoops_AICHR[0];
	FREE_ARRAY(_hoops_AICHR, count, _hoops_CASS *);
	FREE_ARRAY(_hoops_PAGCP, count, float);
	return head;
}


GLOBAL_FUNCTION void HD_Linearize_Hidden_Tree (
	Display_Context const *		dc,
	_hoops_CASS alter *				x,
	int							count,
	int							_hoops_ICHIH,
	_hoops_CASS alter **				_hoops_CCHIH,
	_hoops_CASS alter **				_hoops_SCHIH) {

#ifndef DISABLE_SORTING_HSR
	_hoops_CASS *					head;
	_hoops_CASS *					tail=0;
	_hoops_CASS *					ptr;
	_hoops_CASS **					_hoops_ASRGR;

	if (_hoops_ICHIH == _hoops_CGAAP) {
		*_hoops_CCHIH = x;
		return;
	}

	head = _hoops_IACPI (dc, x, count, _hoops_ICHIH);
	ptr = head;
	_hoops_ASRGR = &head;

	if (BIT(_hoops_ICHIH, _hoops_GAI) && ptr) do {
		if (ptr->_hoops_ASHSA->type == _hoops_SSGSH) {
			_hoops_CASS *				victim = ptr;
			_hoops_PSGSH	alter *	info = (_hoops_PSGSH alter *)victim->_hoops_ASHSA->_hoops_GPHSA;

			ptr = victim->next;

			if (info->root) {
				HD_Linearize_Hidden_Tree (dc, info->root, info->count, _hoops_ICHIH, _hoops_ASRGR, &tail); 
				tail->next = ptr;
				_hoops_ASRGR = &tail->next;
			}
			else	// _hoops_PPCPI _hoops_PISRA _hoops_GH _hoops_RHPA
				*_hoops_ASRGR = ptr;


			victim->_hoops_ASHSA->_hoops_APHGA.release();

			FREE (victim->_hoops_ASHSA, _hoops_SRHSA);
			FREE (victim, _hoops_CASS);
			FREE (info, _hoops_PSGSH);
		}
		else {
			tail = ptr;
			_hoops_ASRGR = &ptr->next;
			ptr = ptr->next;
		}
	} while (ptr != null);

	*_hoops_CCHIH = head;
	if (_hoops_SCHIH)
		*_hoops_SCHIH = tail;
#endif
}




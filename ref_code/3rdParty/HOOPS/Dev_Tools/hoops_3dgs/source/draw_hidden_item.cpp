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
 * $Id: obf_tmp.txt 1.185 2011-01-12 00:57:46 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hidden.h"
#include "patterns.h"
#include "phedron.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "database.h" /* _hoops_RGAR _hoops_IH _hoops_HCGR->_hoops_SGSS */
#include "hpserror.h"
#include "hpspsf.h"
#include "phdraw.h"

local void _hoops_IPSIP (
	Display_Context alter *		dc) {
	_hoops_CPSIP alter *		_hoops_CSC = dc->_hoops_SPSIP;

	POOL_ZALLOC(_hoops_CSC, _hoops_CPSIP, dc->memory_pool);
	POOL_ALLOC_ARRAY_CACHED (_hoops_CSC->points, _hoops_GHSIP, DC_Point, dc->memory_pool);
	POOL_ALLOC_ARRAY_CACHED (_hoops_CSC->_hoops_HPHSA, _hoops_GHSIP, RGBAS32, dc->memory_pool);
	POOL_ZALLOC_ARRAY_CACHED (_hoops_CSC->planes, _hoops_GHSIP, _hoops_ARPA, dc->memory_pool);
	POOL_ALLOC_ARRAY_CACHED (_hoops_CSC->rgba_colors, _hoops_GHSIP, RGBA, dc->memory_pool);
	_hoops_CSC->_hoops_HPHSA[0] = _hoops_CAHSR::_hoops_SAHSR;
	_hoops_CSC->_hoops_RHSIP = 2;
	POOL_ALLOC_ARRAY_CACHED (_hoops_CSC->params, 
				 _hoops_CSC->_hoops_RHSIP*_hoops_GHSIP, 
				 _hoops_RSSH, dc->memory_pool);
	dc->_hoops_SPSIP = _hoops_CSC;
}


local void _hoops_AHSIP (
	_hoops_CASS alter *				hidden) {
	_hoops_SRHSA alter *		_hoops_ASHSA = hidden->_hoops_ASHSA;
	Net_Rendition const & 		nr = _hoops_ASHSA->_hoops_APHGA;
	_hoops_CAHSA const *	info = (_hoops_CAHSA const *)_hoops_ASHSA->_hoops_GPHSA;
	Display_Context alter *		dc = (Display_Context alter *) nr->_hoops_SRA;
	_hoops_CPSIP alter *		_hoops_CSC = dc->_hoops_SPSIP;
	int							used;

	if (_hoops_CSC->used == 0) {
		if (info) {
			if (info->param_width > _hoops_CSC->_hoops_RHSIP) {
				FREE_ARRAY (_hoops_CSC->params, 
							_hoops_CSC->_hoops_RHSIP*_hoops_GHSIP, 
							_hoops_RSSH);
				_hoops_CSC->_hoops_RHSIP = info->param_width;
				POOL_ALLOC_ARRAY (_hoops_CSC->params, 
							 _hoops_CSC->_hoops_RHSIP*_hoops_GHSIP, 
							 _hoops_RSSH, dc->memory_pool);
			}
			_hoops_CSC->param_flags = info->param_flags;
			_hoops_CSC->param_width = info->param_width;
			_hoops_CSC->_hoops_PHSIP = info->_hoops_RAGR;
			if (info->_hoops_RAGR == _hoops_PPHSA)
				_hoops_CSC->_hoops_HPHSA[0] = *info->_hoops_HPHSA;
		}
		else {
			_hoops_CSC->_hoops_PHSIP = 0;
		}
		_hoops_CSC->nr = nr;
	}
	else {
		if (info) {
			if (nr->_hoops_CPA != _hoops_CSC->nr->_hoops_CPA ||
				info->_hoops_RAGR != _hoops_CSC->_hoops_PHSIP ||
				info->param_width != _hoops_CSC->param_width) {

				HD_Flush_Hidden_Item_Cache(dc);
				
				if (info->param_width > _hoops_CSC->_hoops_RHSIP) {
					FREE_ARRAY (_hoops_CSC->params, 
								_hoops_CSC->_hoops_RHSIP*_hoops_GHSIP, 
								_hoops_RSSH);
					_hoops_CSC->_hoops_RHSIP = info->param_width;
					POOL_ALLOC_ARRAY (_hoops_CSC->params, 
								 _hoops_CSC->_hoops_RHSIP*_hoops_GHSIP, 
								 _hoops_RSSH, dc->memory_pool);
				}
				_hoops_CSC->param_flags = info->param_flags;
				_hoops_CSC->param_width = info->param_width;
				_hoops_CSC->_hoops_PHSIP = info->_hoops_RAGR;
				_hoops_CSC->nr = nr;
			}
		}
		else {
			if (nr->_hoops_CPA != _hoops_CSC->nr->_hoops_CPA ||
				_hoops_CSC->_hoops_PHSIP != 0) {
				HD_Flush_Hidden_Item_Cache(dc);
				_hoops_CSC->_hoops_PHSIP = 0;
				_hoops_CSC->nr = nr;
			}		
		}
		if (_hoops_CSC->used > _hoops_GHSIP - 3) {
			HD_Flush_Hidden_Item_Cache(dc);
			_hoops_CSC->nr = nr;
		}
	}
	used = _hoops_CSC->used;
	if (info && info->_hoops_RAGR) {
		switch (info->_hoops_RAGR) {
			case _hoops_PPHSA:
				if (_hoops_CSC->_hoops_HPHSA[0] != *info->_hoops_HPHSA)
					_hoops_CSC->flags |= _hoops_HHSIP;
				_hoops_AIGA(_hoops_ASHSA->points, 3, DC_Point, &_hoops_CSC->points[used]);
				_hoops_CSC->_hoops_HPHSA[used/3] = *info->_hoops_HPHSA;
				break;

			case _hoops_CPHSA:
				_hoops_AIGA(_hoops_ASHSA->points, 3, DC_Point, &_hoops_CSC->points[used]);
				_hoops_AIGA(info->_hoops_HPHSA, 3, RGBAS32, &_hoops_CSC->_hoops_HPHSA[used]);
				break;

			default:
				if (ANYBIT (info->_hoops_RAGR, ~(_hoops_GHHSA|_hoops_SPHSA|_hoops_RHHSA))) {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									 "Hidden triangle has undecipherable attributes");
					break;
				}
#ifndef _hoops_IHSIP
				_hoops_AIGA(_hoops_ASHSA->points, 3, DC_Point, &_hoops_CSC->points[used]);
				if (info->rgba_colors)
					_hoops_AIGA(info->rgba_colors, 3, RGBA, &_hoops_CSC->rgba_colors[used]);			
				if (info->planes)
					_hoops_AIGA(info->planes, 3, _hoops_ARPA, &_hoops_CSC->planes[used]);			
				if (info->params)
					_hoops_AIGA(info->params,  info->param_width * 3, _hoops_RSSH, 
								&_hoops_CSC->params[info->param_width * used]);			
#endif
				break;
		}
	}
	else {
		_hoops_AIGA(_hoops_ASHSA->points, 3, DC_Point, &_hoops_CSC->points[used]);
	}
	_hoops_CSC->used += 3;
}



GLOBAL_FUNCTION void HD_Free_Hidden_Item_Cache (
	Display_Context alter *		dc) {
	_hoops_CPSIP alter *		_hoops_CSC = dc->_hoops_SPSIP;

	if (_hoops_CSC) {
		FREE_ARRAY (_hoops_CSC->points, _hoops_GHSIP, DC_Point);
		FREE_ARRAY (_hoops_CSC->_hoops_HPHSA, _hoops_GHSIP, RGBAS32);
		FREE_ARRAY (_hoops_CSC->rgba_colors, _hoops_GHSIP, RGBA);
		FREE_ARRAY (_hoops_CSC->planes, _hoops_GHSIP, _hoops_ARPA);
		FREE_ARRAY (_hoops_CSC->params, 
					_hoops_CSC->_hoops_RHSIP*_hoops_GHSIP, 
					_hoops_RSSH);
		FREE(_hoops_CSC, _hoops_CPSIP);
		dc->_hoops_SPSIP = null;
	}
}




GLOBAL_FUNCTION void HD_Flush_Hidden_Item_Cache (
	Display_Context alter *		dc) {
	_hoops_CPSIP alter *		_hoops_CSC = dc->_hoops_SPSIP;
	Net_Rendition				nr = _hoops_CSC->nr;

	if (_hoops_CSC->used == 0)
		return;

	if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
		bool _hoops_IGCIP = !BIT (nr->_hoops_CPP->_hoops_PRH.options, _hoops_GPAAP);
		if (BIT(nr->transform_rendition->flags, _hoops_ISH) != _hoops_IGCIP) {
			if (_hoops_IGCIP)
				nr.Modify()->transform_rendition.Modify(_hoops_HRCIP)->flags |= _hoops_ISH;
			else 
				nr.Modify()->transform_rendition.Modify(_hoops_HRCIP)->flags &= ~_hoops_ISH;
		}
	}

	if (BIT (nr->transform_rendition->flags, _hoops_CSP)) {
		RGBAS32 const *		_hoops_CHSIP = null;
		RGBA const *		_hoops_HPHSA = null;
		_hoops_ARPA const *		planes = null;
		_hoops_RSSH const *	params = null;
		_hoops_GPGGA		flags = _hoops_GPHC;

		if (BIT (_hoops_CSC->_hoops_PHSIP, _hoops_PPHSA)) {
			if (BIT(_hoops_CSC->flags, _hoops_HHSIP))
				flags |= _hoops_PAIC;
			else
				flags |= _hoops_RAIC;
		}

		if (BIT (_hoops_CSC->_hoops_PHSIP, _hoops_GHHSA)) {
			planes = _hoops_CSC->planes;
			if (ANYBIT (_hoops_CSC->_hoops_PHSIP, _hoops_PPHSA|_hoops_CPHSA)) {
				_hoops_CSC->rgba_colors[0] = _hoops_CSC->_hoops_HPHSA[0];
				for (int i = 1; i < _hoops_CSC->used; i++) {
					if (_hoops_CSC->_hoops_HPHSA[i] == _hoops_CSC->_hoops_HPHSA[i-1])
						_hoops_CSC->rgba_colors[i] = _hoops_CSC->rgba_colors[i-1];
					else
						_hoops_CSC->rgba_colors[i] = _hoops_CSC->_hoops_HPHSA[i];
				}
				_hoops_HPHSA = _hoops_CSC->rgba_colors;
			}
			else if (BIT (_hoops_CSC->_hoops_PHSIP, _hoops_SPHSA))
				_hoops_HPHSA = _hoops_CSC->rgba_colors;
		}
		else {
			if (BIT (_hoops_CSC->_hoops_PHSIP, _hoops_CPHSA)) {
				_hoops_CHSIP = _hoops_CSC->_hoops_HPHSA;
				flags |= _hoops_AAIC;
			}
			else if (BIT (_hoops_CSC->_hoops_PHSIP, _hoops_PPHSA))
				_hoops_CHSIP = _hoops_CSC->_hoops_HPHSA;	// _hoops_SHSIP _hoops_PAR _hoops_GISIP _hoops_AIAH _hoops_RISIP _hoops_ARRS
			else if (BIT (_hoops_CSC->_hoops_PHSIP, _hoops_SPHSA))
				_hoops_HPHSA = _hoops_CSC->rgba_colors;
		}
		if (BIT (_hoops_CSC->_hoops_PHSIP, _hoops_RHHSA))
			params = _hoops_CSC->params;

		HD_Clip_DC_Polytriangle (nr, -_hoops_CSC->used, _hoops_CSC->points, _hoops_CHSIP, _hoops_HPHSA, planes,
								 params, _hoops_CSC->param_width, _hoops_CSC->param_flags, flags);
	}
	else
	switch (_hoops_CSC->_hoops_PHSIP) {
		case 0:
			/* _hoops_AISIP: _hoops_HCR _hoops_IIGR _hoops_RH _hoops_PISIP _hoops_SICAR _hoops_IRAA _hoops_IRS _hoops_HHHR _hoops_RPR, _hoops_PGAP _hoops_AGSR _hoops_SGS
			   _hoops_HIPH _hoops_CHR _hoops_HIAGR (_hoops_GAR _hoops_HISIP _hoops_IS _hoops_RIHA _hoops_CRGR _hoops_IRS _hoops_CRHH */
			_hoops_GSRGA (nr, -_hoops_CSC->used, _hoops_CSC->points);
			break;

		case _hoops_PPHSA: {
			bool		single = !BIT(_hoops_CSC->flags, _hoops_HHSIP);

			_hoops_SCRGA (nr, -_hoops_CSC->used, _hoops_CSC->points, _hoops_CSC->_hoops_HPHSA, single);
		}	break;

		case _hoops_CPHSA:
			_hoops_CCRGA (nr, -_hoops_CSC->used, _hoops_CSC->points, _hoops_CSC->_hoops_HPHSA);
			break;

#ifndef _hoops_IHSIP
		case _hoops_GHHSA:
			_hoops_ICRGA (nr, -_hoops_CSC->used, _hoops_CSC->points, null, _hoops_CSC->planes);
			break;

		case _hoops_GHHSA|_hoops_SPHSA:
			_hoops_ICRGA (nr, -_hoops_CSC->used, _hoops_CSC->points, _hoops_CSC->rgba_colors, _hoops_CSC->planes);
			break;

		case _hoops_RHHSA:
			_hoops_HCRGA (nr, -_hoops_CSC->used, _hoops_CSC->points, null, null,
												_hoops_CSC->params, _hoops_CSC->param_width, _hoops_CSC->param_flags);
			break;

		case _hoops_RHHSA|_hoops_GHHSA:
			_hoops_HCRGA (nr, -_hoops_CSC->used, _hoops_CSC->points, null, _hoops_CSC->planes,
												_hoops_CSC->params, _hoops_CSC->param_width, _hoops_CSC->param_flags);
			break;

		case _hoops_RHHSA|_hoops_SPHSA:
			_hoops_HCRGA (nr, -_hoops_CSC->used, _hoops_CSC->points, _hoops_CSC->rgba_colors, null,
												_hoops_CSC->params, _hoops_CSC->param_width, _hoops_CSC->param_flags);
			break;

		case _hoops_RHHSA|_hoops_GHHSA|_hoops_SPHSA:
			_hoops_HCRGA (nr, -_hoops_CSC->used, _hoops_CSC->points, _hoops_CSC->rgba_colors, _hoops_CSC->planes,
												_hoops_CSC->params, _hoops_CSC->param_width, _hoops_CSC->param_flags);
			break;

		case _hoops_CPHSA|_hoops_GHHSA:
		case _hoops_PPHSA|_hoops_GHHSA:
			/* _hoops_RHI _hoops_SIA */
			   /* _hoops_SICR _hoops_PSHA _hoops_HII 8-_hoops_IGRH/_hoops_RCAP _hoops_IS _hoops_AIIC _hoops_SRSGR */
			_hoops_CSC->rgba_colors[0] = _hoops_CSC->_hoops_HPHSA[0];
			for (int i = 1; i < _hoops_CSC->used; i++) {
				if (_hoops_CSC->_hoops_HPHSA[i] == _hoops_CSC->_hoops_HPHSA[i-1])
					_hoops_CSC->rgba_colors[i] = _hoops_CSC->rgba_colors[i-1];
				else
					_hoops_CSC->rgba_colors[i] = _hoops_CSC->_hoops_HPHSA[i];
			}
			_hoops_HCRGA (nr, -_hoops_CSC->used, _hoops_CSC->points, _hoops_CSC->rgba_colors, _hoops_CSC->planes, 
												null, 0, _hoops_CSC->param_flags);
			break;

#endif
		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						 "unknown attribute in hidden item cache");
	}
	_hoops_CSC->nr = null;
	_hoops_CSC->used = 0;
	_hoops_CSC->flags = 0;
	_hoops_CSC->_hoops_IISIP = 0;
}


#define _hoops_PCAHP(i) ((i-1)/2)
#define _hoops_HCAHP(i) (2*i+1)
#define _hoops_ICAHP(i) (2*i+2)

local void _hoops_CISIP (
	_hoops_SISIP alter *	heap,
	int								_hoops_HSAHP) {
	int								p = _hoops_PCAHP(_hoops_HSAHP);
	Hidden_Tristrip *				temp;

	while (_hoops_HSAHP > 0) {
		if (heap->data[_hoops_HSAHP]->_hoops_GCSIP > heap->data[p]->_hoops_GCSIP) {
			temp = heap->data[_hoops_HSAHP];
			heap->data[_hoops_HSAHP] = heap->data[p];
			heap->data[p] = temp;
			_hoops_HSAHP = p;
			p = _hoops_PCAHP(p);
		}
		else
			break;
	}
}


local void downheap_hth (
	_hoops_SISIP alter *	heap,
	int								_hoops_HSAHP) {
	Hidden_Tristrip *				temp;
	int								l = _hoops_HCAHP(_hoops_HSAHP);
	int								r = _hoops_ICAHP(_hoops_HSAHP);
	int								_hoops_PSAHP = _hoops_HSAHP;

	while (l < heap->used) {
		if (heap->data[l]->_hoops_GCSIP > heap->data[_hoops_HSAHP]->_hoops_GCSIP)
			_hoops_PSAHP = l;
		if (r < heap->used)
			if (heap->data[r]->_hoops_GCSIP > heap->data[_hoops_PSAHP]->_hoops_GCSIP)
				_hoops_PSAHP = r;
		if (_hoops_PSAHP != _hoops_HSAHP) {
			temp = heap->data[_hoops_HSAHP];
			heap->data[_hoops_HSAHP] = heap->data[_hoops_PSAHP];
			heap->data[_hoops_PSAHP] = temp;
			l = _hoops_HCAHP (_hoops_PSAHP);
			r = _hoops_ICAHP (_hoops_PSAHP);
			_hoops_HSAHP = _hoops_PSAHP;
		}
		else
			break;
	}
}


local void _hoops_RCSIP (
	Display_Context const *			dc,
	_hoops_SISIP alter *	heap,
	Hidden_Tristrip alter *			_hoops_ACSIP) {

	if (heap->used == heap->allocated) {
		Hidden_Tristrip alter **	_hoops_PCAHA;

		if (heap->allocated) {
			heap->allocated *= 2;
			POOL_ALLOC_ARRAY (_hoops_PCAHA, heap->allocated, Hidden_Tristrip *, dc->memory_pool);
			_hoops_AIGA(heap->data, heap->used, Hidden_Tristrip *, _hoops_PCAHA);
			FREE_ARRAY (heap->data, heap->used, Hidden_Tristrip *);
			heap->data = _hoops_PCAHA;
		}
		else {
			heap->allocated = 32;
			POOL_ALLOC_ARRAY (heap->data, heap->allocated, Hidden_Tristrip *, dc->memory_pool);
		}
	}
	heap->data[heap->used++] = _hoops_ACSIP;
	_hoops_CISIP (heap, heap->used-1);
}


local void _hoops_PCSIP (
	_hoops_SISIP alter *	heap,
	int								which) {

	if (which < heap->used-1) {
		heap->data[which] = heap->data[heap->used-1];
		downheap_hth (heap, which);
	}
	heap->used--;
}


local void _hoops_HCSIP (
	Display_Context const *			dc,
	_hoops_SISIP alter *	_hoops_ICSIP,
	float							_hoops_CCSIP) {
	float							_hoops_SCSIP, _hoops_GCSIP;
	Hidden_Tristrip alter *			_hoops_ACSIP;

	UNREFERENCED(dc);

	if (_hoops_ICSIP->used == 0)
		return;

	_hoops_ACSIP = _hoops_ICSIP->data[0];
	while (_hoops_ACSIP->_hoops_GCSIP > _hoops_CCSIP) {
		if (_hoops_ICSIP->used >= 3) {
			_hoops_SCSIP = _hoops_IAAA (_hoops_ICSIP->data[1]->_hoops_GCSIP, _hoops_ICSIP->data[2]->_hoops_GCSIP);
			_hoops_GCSIP = _hoops_IAAA (_hoops_SCSIP, _hoops_CCSIP);
		}
		else if (_hoops_ICSIP->used == 2) 
			_hoops_GCSIP = _hoops_IAAA (_hoops_ICSIP->data[1]->_hoops_GCSIP, _hoops_CCSIP);
		else
			_hoops_GCSIP = _hoops_CCSIP; 	
		HD_Cache_From_Hidden_Tristrip (_hoops_ACSIP, _hoops_GCSIP);
		if (_hoops_ACSIP->_hoops_GSSIP == _hoops_ACSIP->_hoops_APPH) {
			_hoops_PCSIP (_hoops_ICSIP, 0);
			HD_Free_Hidden_Tristrip (_hoops_ACSIP);
			if (_hoops_ICSIP->used == 0)
				break;
		}
		else {
			downheap_hth (_hoops_ICSIP, 0);
		}
		_hoops_ACSIP = _hoops_ICSIP->data[0];
	}
}


local int _hoops_RSSIP (
	Tristrip const *		ts) {

 	if (ts->_hoops_GSSH && ts->_hoops_GSSH->_hoops_GSHA) {
		if (ts->_hoops_ICHA) {
			/*_hoops_ASSIP*/
			return _hoops_PSSIP;
		}
		else if (ts->_hoops_PRHH) {
			/*_hoops_HSSIP*/
			return _hoops_ISSIP;
		}
		else {
			/*_hoops_CSSIP*/
			return _hoops_SSSIP;
		}
	}
	else {
		if (ts->_hoops_PCHA) {
			if (ts->_hoops_ICHA) {
				/*_hoops_GGGCP*/
				return _hoops_RGGCP; 
			}
			else if (ts->_hoops_PRHH) {
				/*_hoops_AGGCP*/
				return _hoops_PGGCP;
			}
			else {
				/*_hoops_HGGCP*/
				return _hoops_IGGCP;
			}
		}
		else {
			if (ts->_hoops_PAGI) {
				if (ts->_hoops_ICHA) {
					/*_hoops_CGGCP*/
					return _hoops_SGGCP;
				}
				else if (ts->_hoops_PRHH) {
					/*_hoops_GRGCP*/		
					return _hoops_RRGCP;
				}
				else {
					/*_hoops_ARGCP*/
					return _hoops_PRGCP;
				}
			}
			else {
				if (ts->_hoops_ICHA) {
					/*_hoops_HRGCP*/	
					return _hoops_IRGCP;
				}
				else if (ts->_hoops_PRHH) {
					/*_hoops_CRGCP*/
					return _hoops_SRGCP;
				}
				else {
					/*_hoops_GAGCP*/
					return _hoops_RAGCP;
				}
			}
		}
	}
}


struct _hoops_AAGCP {
	float *	_hoops_PAGCP;
	int *	indices;
};

#define QS_TYPE				struct _hoops_AAGCP *					
#define QS_VAL(thing,a)		(thing->_hoops_PAGCP[a])	
#define QS_COMPARE(f1,f2)	(f1<f2)					
#define QS_SWAP(thing,a,b) {		\
	Swap (thing->_hoops_PAGCP[a], thing->_hoops_PAGCP[b]); \
	Swap (thing->indices[a], thing->indices[b]); \
}
#include "utility/hqsort.h"


/* _hoops_RGR _hoops_API _hoops_HAGCP _hoops_PPR _hoops_HAHI-_hoops_HSPRA _hoops_RH _hoops_HIPH _hoops_GIAA _hoops_IRS _hoops_AASGR _hoops_HRPR
	(_hoops_PSHS _hoops_GGR _hoops_IAGCP).  _hoops_IPCP _hoops_HGSI _hoops_HIGR _hoops_IIGR _hoops_CCSHP _hoops_APSAR _hoops_HRGR _hoops_GSHHR _hoops_GGR
	_hoops_CAGCP */
local bool _hoops_SAGCP (
	_hoops_CASS alter *					hidden) {
	Hidden_Tristrip alter *			_hoops_ACSIP = (Hidden_Tristrip alter *)hidden->_hoops_ASHSA->_hoops_GPHSA;	
	Net_Rendition const & 			nr = _hoops_ACSIP->_hoops_APHGA;
	Display_Context alter *			dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_GPGCP *		_hoops_RPGCP;
	Tristrip const *				ts = _hoops_ACSIP->tristrips;
	int								_hoops_SSPAR, _hoops_APGCP, _hoops_APPH, i, j, _hoops_PPGCP, _hoops_SAHAR, length;
	float							_hoops_HGSIR, _hoops_IGSIR, _hoops_RICR, _hoops_AICR, displacement;
	struct _hoops_AAGCP			_hoops_RCCIA;
	bool							_hoops_APH;
	DC_Point const *				_hoops_CGCAR = hidden->_hoops_ASHSA->points;

	hidden->_hoops_ASHSA->_hoops_APHGA.release();
	FREE (hidden->_hoops_ASHSA, _hoops_SRHSA);
	FREE (hidden, _hoops_CASS);

	/* _hoops_HSPR _hoops_III _hoops_HRGR _hoops_PCCP _hoops_AAPA _hoops_ASCR (_hoops_ASSP'_hoops_RA _hoops_HIHA _hoops_IH _hoops_HPIPR _hoops_RSSI) */
	_hoops_APPH = ts->total - 2*ts->_hoops_PHHA;
	_hoops_ACSIP->_hoops_AGH = _hoops_IAAA(ts->face_count, ts->point_count);

	displacement = nr->transform_rendition->_hoops_CHIH+
					nr->transform_rendition->_hoops_SHIH;
	displacement *= _hoops_ISSIR(nr->transform_rendition);

	_hoops_APH = BIT (nr->transform_rendition->flags, _hoops_IGSP) &&
			  ANYBIT (nr->transform_rendition->heuristics,
					_hoops_SASA | _hoops_GPSA);

	POOL_ALLOC_ARRAY_CACHED (_hoops_RPGCP, _hoops_APPH, _hoops_GPGCP, dc->memory_pool);
	POOL_ALLOC_ARRAY_CACHED (_hoops_RCCIA.indices, _hoops_APPH, int, dc->memory_pool);
	POOL_ALLOC_ARRAY_CACHED (_hoops_RCCIA._hoops_PAGCP, _hoops_APPH, float, dc->memory_pool);

	j = 0;
	_hoops_APGCP = 0;
	_hoops_SSPAR = -1;
	for (i = 0; i < ts->_hoops_PHHA; i++) {
		length = ts->lengths[i]; 
		_hoops_PPGCP = j;
		_hoops_SAHAR = j + length;
		j += 2;
		while (j < _hoops_SAHAR) {
			if (ts->face_indices)
				_hoops_SSPAR = ts->face_indices[j];
			else
				_hoops_SSPAR++;			
			if (!_hoops_APH || (_hoops_ACSIP->_hoops_AGHAR && _hoops_ACSIP->_hoops_AGHAR[_hoops_SSPAR])) {
				_hoops_RPGCP[_hoops_APGCP]._hoops_HPGCP = i;
				_hoops_RPGCP[_hoops_APGCP]._hoops_IPGCP = j - _hoops_PPGCP - 2;
				_hoops_RPGCP[_hoops_APGCP]._hoops_PPGCP = _hoops_PPGCP;
				if (ts->lengths[i] > 0)
					_hoops_RICR = _hoops_AICR = _hoops_CGCAR[ts->_hoops_AIHA[j-2]].z;
				else
					_hoops_RICR = _hoops_AICR = _hoops_CGCAR[ts->_hoops_AIHA[_hoops_PPGCP]].z;
				_hoops_HGSIR = _hoops_CGCAR[ts->_hoops_AIHA[j-1]].z;
				_hoops_IGSIR = _hoops_CGCAR[ts->_hoops_AIHA[j]].z;
				if (_hoops_IGSIR > _hoops_HGSIR) {
					if (_hoops_IGSIR > _hoops_AICR)
						_hoops_AICR = _hoops_IGSIR;
					if (_hoops_HGSIR < _hoops_RICR)
						_hoops_RICR = _hoops_HGSIR;
				}
				else {
					if (_hoops_HGSIR > _hoops_AICR)
						_hoops_AICR = _hoops_HGSIR;
					if (_hoops_IGSIR < _hoops_RICR)
						_hoops_RICR = _hoops_IGSIR;
				}
				_hoops_RCCIA._hoops_PAGCP[_hoops_APGCP] = displacement + (_hoops_AICR + _hoops_RICR)/2;
				_hoops_RCCIA.indices[_hoops_APGCP] = _hoops_APGCP;
				_hoops_APGCP++;
			}
			j++;
		}
	}
	_hoops_ACSIP->_hoops_APPH = _hoops_APGCP;

	if (_hoops_ACSIP->_hoops_APPH != 0) {
#if 1
		HI_Sort_Array (_hoops_ACSIP->_hoops_APPH, _hoops_RCCIA._hoops_PAGCP, (void**)_hoops_RCCIA.indices, sizeof(int), false);
#else
		quick_sort (&_hoops_RCCIA, 0, _hoops_ACSIP->_hoops_APPH-1);
#endif
		POOL_ALLOC_ARRAY_CACHED (_hoops_ACSIP->_hoops_CPGCP, _hoops_ACSIP->_hoops_APPH, _hoops_GPGCP, dc->memory_pool);
		for (i = 0; i < _hoops_ACSIP->_hoops_APPH; i++) {
			_hoops_RSAI (&_hoops_RPGCP[_hoops_RCCIA.indices[i]], 
						 _hoops_GPGCP, 
						 &_hoops_ACSIP->_hoops_CPGCP[i]);
		}
		FREE_ARRAY (_hoops_RPGCP, _hoops_APPH, _hoops_GPGCP);
		FREE_ARRAY (_hoops_RCCIA.indices, _hoops_APPH, int);
		if (_hoops_ACSIP->_hoops_APPH < _hoops_APPH) {
			POOL_ALLOC_ARRAY_CACHED (_hoops_ACSIP->_hoops_SPGCP, _hoops_ACSIP->_hoops_APPH, float, dc->memory_pool);
			_hoops_AIGA (_hoops_RCCIA._hoops_PAGCP, _hoops_ACSIP->_hoops_APPH, float, _hoops_ACSIP->_hoops_SPGCP);
			FREE_ARRAY (_hoops_RCCIA._hoops_PAGCP, _hoops_APPH, float);
		}
		else
			_hoops_ACSIP->_hoops_SPGCP = _hoops_RCCIA._hoops_PAGCP;

		_hoops_ACSIP->_hoops_IISIP = _hoops_RSSIP(ts);

		POOL_ZALLOC_ARRAY_CACHED (_hoops_ACSIP->_hoops_GHGCP, 2*_hoops_ACSIP->_hoops_AGH, RGBAS32, dc->memory_pool);
		_hoops_ACSIP->_hoops_GCSIP = _hoops_ACSIP->_hoops_SPGCP[0];
	}
	else {
		/* _hoops_CPS _hoops_CSAP _hoops_RHGCP _hoops_SGGR */
		FREE_ARRAY (_hoops_RPGCP, _hoops_APPH, _hoops_GPGCP);
		FREE_ARRAY (_hoops_RCCIA.indices, _hoops_APPH, int);
		FREE_ARRAY (_hoops_RCCIA._hoops_PAGCP, _hoops_APPH, float);
		HD_Free_Hidden_Tristrip (_hoops_ACSIP);
		return false;
	}

	if (!dc->_hoops_AHGCP)
		POOL_ZALLOC (dc->_hoops_AHGCP, _hoops_SISIP, dc->memory_pool);

	_hoops_RCSIP (dc, dc->_hoops_AHGCP, _hoops_ACSIP);
	return true;
}


/* _hoops_HCPH _hoops_IS _hoops_RGR _hoops_API _hoops_GHCA _hoops_RRP _hoops_IS _hoops_SHH _hoops_SCRH _hoops_HPP _hoops_IRS _hoops_AASA _hoops_IS 
	_hoops_PHGCP _hoops_ACIPA _hoops_CSSHP _hoops_HHGCP _hoops_IHGCP (_hoops_PAPR _hoops_ARRS) */
GLOBAL_FUNCTION _hoops_CASS alter * HD_Draw_Hidden_Item (
	_hoops_CASS alter *				hidden,
	bool						_hoops_CHGCP) {
#ifndef DISABLE_SORTING_HSR
	Net_Rendition				nr;
	Display_Context alter *		dc = (Display_Context alter *)hidden->_hoops_ASHSA->_hoops_APHGA->_hoops_SRA;
	bool						_hoops_SHGCP = !_hoops_CHGCP; /* _hoops_SHS _hoops_SSH-_hoops_GHIS _hoops_PAR _hoops_GHCP */
	_hoops_CASS *					next;
	float						z = 0;
	_hoops_SRHSA *			_hoops_ASHSA;

	if (_hoops_SHGCP) 
		HD_Painters_Bias_Z (hidden, false); 

	if (!dc->_hoops_SPSIP)
		_hoops_IPSIP (dc);

_hoops_GIGCP:

	_hoops_ASHSA = hidden->_hoops_ASHSA;

	if (_hoops_CHGCP && dc->_hoops_AHGCP && _hoops_ASHSA->type != _hoops_RIGCP) {
		z = (_hoops_ASHSA->_hoops_RICR + _hoops_ASHSA->_hoops_AICR) / 2;
		_hoops_HCSIP (dc, dc->_hoops_AHGCP, z);
	}

	next = hidden->next;

	/* _hoops_SR _hoops_ACPA _hoops_SGS _hoops_SR _hoops_CHR _hoops_CPIC _hoops_IS _hoops_RRP _hoops_RH _hoops_SPS _hoops_IGCI _hoops_GGR _hoops_RH _hoops_HIGR _hoops_RAS _hoops_SR _hoops_HPIRA _hoops_RGR
	   _hoops_SPR, _hoops_HIS _hoops_HGCR _hoops_RH _hoops_IHAH _hoops_AIGCP _hoops_GH _hoops_HA _hoops_PPR _hoops_IPPR _hoops_RH _hoops_PIGCP */
	if (_hoops_CHGCP)
		_hoops_SSAGR(next);

	if (_hoops_ASHSA->type == _hoops_IPHSA) {
		_hoops_AHSIP(hidden);
	}
	else if (_hoops_ASHSA->type != _hoops_RIGCP && _hoops_ASHSA->type != _hoops_HIGCP) {
		nr = _hoops_ASHSA->_hoops_APHGA;

		if (dc->_hoops_SPSIP && dc->_hoops_SPSIP->used > 0)
			HD_Flush_Hidden_Item_Cache (dc);

		if (nr->_hoops_CPP->_hoops_PRH._hoops_HRH) {
			bool	_hoops_IGCIP = false;

			switch (_hoops_ASHSA->type) {
				case _hoops_RCHSA:
				case _hoops_AHHSA: {
					if (nr->_hoops_AHP->_hoops_CHA->_hoops_IRIR < 0.9f)
						_hoops_IGCIP = true;	
				} break;

				case _hoops_IAHSA:
				case _hoops_HCHSA:
				case _hoops_ACHSA: {
					if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < 0.9f)
						_hoops_IGCIP = true;	
				} break;

				case _hoops_HIGCP:
				case _hoops_PCHSA: {
					if (nr->_hoops_GSP->_hoops_CHA->_hoops_IRIR < 0.9f)
						_hoops_IGCIP = true;	
				} break;

				case _hoops_SHHSA:
				case _hoops_PIHSA: {
					if (nr->_hoops_SISI->_hoops_CHA->_hoops_IRIR < 0.9f)
						_hoops_IGCIP = true;	
				} break;

				case _hoops_PHHSA: {
					/* _hoops_HPGR _hoops_SPR _hoops_PPSR _hoops_SR _hoops_AAPR _hoops_IIGCP _hoops_SSH _hoops_CIGCP (_hoops_GAR _hoops_GGR _hoops_RH _hoops_GRGR _hoops_RRGR _hoops_RIS _hoops_CAPP) 
						_hoops_RPP _hoops_IIH _hoops_CSAP _hoops_GII _hoops_IHSP _hoops_GGR _hoops_RH _hoops_CSCR, _hoops_HIH _hoops_CIIHP _hoops_SGS _hoops_SGS _hoops_RRRH _hoops_PAH 
						_hoops_HS _hoops_IRS _hoops_ASRS _hoops_IIGR _hoops_CIGC _hoops_PPR _hoops_RRH _hoops_ASPA, _hoops_HIS _hoops_SCH _hoops_HRGR _hoops_GIH _hoops_IS _hoops_SHSP _hoops_SSH _hoops_CIGCP _hoops_GPP */
					/*
					_hoops_SIGCP _hoops_RAPC		*_hoops_ICRHA = &_hoops_CCSHP->_hoops_GCGCP->_hoops_RCGCP;

					_hoops_RPP (_hoops_IRRC(_hoops_ICRHA->_hoops_ACGCP->_hoops_SGI, _hoops_PCGCP))
						_hoops_HCGCP=_hoops_IHPR;
					*/
				} break;

				default: {
				  _hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
									 "Can't draw hidden item");
				}	break;
			}

			if (_hoops_IGCIP)
				nr.Modify()->transform_rendition.Modify(_hoops_HRCIP)->flags |= _hoops_ISH;
		}

		switch (_hoops_ASHSA->type) {
			case _hoops_RCHSA: {
				_hoops_AIGGA (nr, 1, _hoops_ASHSA->points);
			}	break;

			case _hoops_AHHSA: {
				_hoops_CAHSA alter *	info = (_hoops_CAHSA alter *)_hoops_ASHSA->_hoops_GPHSA;

				if (info == null)
					_hoops_ICGCP (nr, _hoops_ASHSA->points);
				else switch (info->_hoops_RAGR) {
					case 0:
						 _hoops_ICGCP (nr, _hoops_ASHSA->points);
						break;

					case _hoops_PPHSA:
						_hoops_CCGCP (nr, _hoops_ASHSA->points, info->_hoops_HPHSA);
						break;

					case _hoops_CPHSA:
						_hoops_SCGCP (nr, _hoops_ASHSA->points, info->_hoops_HPHSA);
						break;

					default:
						if (ANYBIT (info->_hoops_RAGR, ~(_hoops_GHHSA|_hoops_SPHSA|_hoops_RHHSA))) {
							_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
											 "Hidden edge has undecipherable attributes");
							break;
						}
#ifndef _hoops_IHSIP
						_hoops_GSGCP (nr, _hoops_ASHSA->points, info->rgba_colors, info->planes, 
												   info->params, info->param_width, info->param_flags);
#endif
					break;
				}
			}	break;


			case _hoops_IAHSA:
			case _hoops_HCHSA:
			case _hoops_ACHSA: {
				switch (_hoops_ASHSA->type) {
					case _hoops_IAHSA: {
						_hoops_CAHSA alter	*	info = (_hoops_CAHSA alter *)_hoops_ASHSA->_hoops_GPHSA;

						if (info == null || !BIT (info->_hoops_RAGR, _hoops_PPHSA))
							_hoops_RSGCP (nr, _hoops_ASHSA->count, _hoops_ASHSA->points);
						else
							_hoops_ASGCP (nr, _hoops_ASHSA->count, _hoops_ASHSA->points, &info->_hoops_HPHSA[0]);
					}	break;

					case _hoops_ACHSA: {
						_hoops_PSGCP (nr, _hoops_ASHSA->count, _hoops_ASHSA->points);
					}	break;

					case _hoops_HCHSA: {
						DC_Point		buf[256];
						DC_Point *		pts = buf;
						int				current;
						int				start;
						bool *			_hoops_CCHSA;
  					  
						_hoops_CCHSA = _hoops_ASHSA->_hoops_GPHSA->_hoops_HSGCP._hoops_CCHSA;

						_hoops_RSGCP (nr, _hoops_ASHSA->count, _hoops_ASHSA->points);

						if (_hoops_ASHSA->count+1 > _hoops_GGAPR (buf))
							POOL_ALLOC_ARRAY (pts, _hoops_ASHSA->count, DC_Point, dc->memory_pool);
						_hoops_AIGA (_hoops_ASHSA->points, _hoops_ASHSA->count, DC_Point, pts);
						_hoops_RSAI (&_hoops_ASHSA->points[0], DC_Point, &pts[_hoops_ASHSA->count]);

						current = 0;

						_hoops_PCCAR {
							/* _hoops_IHSH _hoops_IH _hoops_IRS _hoops_APHR _hoops_III _hoops_CAGH */
							do {
								if (++current == _hoops_ASHSA->count) {
									/* _hoops_HHPPA, _hoops_SARS'_hoops_RA _hoops_SSS _hoops_SPR - _hoops_ARGAR _hoops_ISSC _hoops_AARI */
									if (_hoops_CCHSA[0]) {
										/* _hoops_PGSA _hoops_RH _hoops_CSGR _hoops_ISHA _hoops_GRGA */
										_hoops_SCGGA (nr, 2, &pts[_hoops_ASHSA->count - 1]);
									}
									goto _hoops_PCPPR;
								}

							} while (!_hoops_CCHSA[current]);

							/* _hoops_IHSH _hoops_RSH _hoops_SGIP _hoops_SCH _hoops_PHRPA */
							start = current - 1;
							do {
								if (++current == _hoops_ASHSA->count) {
									/* _hoops_HHPPA, _hoops_IHCS _hoops_PSAP - _hoops_ARGAR _hoops_ISSC _hoops_AARI */
									if (_hoops_CCHSA[0]) {
										/* _hoops_SR _hoops_HHGC _hoops_SPR *_hoops_ISGR* _hoops_RH _hoops_CGHI _hoops_APIP _hoops_ISHA-_hoops_IS-_hoops_PPSR. */
										++current;
									}

									_hoops_SCGGA (nr, current - start, &pts[start]);
									goto _hoops_PCPPR;
								}
							} while (_hoops_CCHSA[current]);

							/* _hoops_PGSA _hoops_SCH */
							_hoops_SCGGA (nr, current - start, &pts[start]);
						}
						_hoops_PCPPR:;

						if (pts != buf)
							FREE_ARRAY (pts, _hoops_ASHSA->count+1, DC_Point);
					}	break;
				}
			}	break;


			case _hoops_PCHSA: {
				DC_Point			where;

				where.x = (_hoops_ASHSA->xmin + _hoops_ASHSA->xmax) * 0.5f;
				where.y = (_hoops_ASHSA->ymin + _hoops_ASHSA->ymax) * 0.5f;
				where.z = _hoops_ASHSA->_hoops_RICR;

				_hoops_ISGCP (nr, &where);
			}	break;


			case _hoops_PIHSA: {
				_hoops_HIHSA alter *	_hoops_CSGCP;

				_hoops_CSGCP = (_hoops_HIHSA alter *)_hoops_ASHSA->_hoops_GPHSA;
				((Font_Instance *)nr->_hoops_SISI->font)->_hoops_RACSR = _hoops_CSGCP->_hoops_RACSR;
				((Font_Instance *)nr->_hoops_SISI->font)->_hoops_GCHSA = _hoops_CSGCP->_hoops_GCHSA;

				HD_Standard_Draw_Plain_Text (nr, _hoops_CSGCP->text, (Point const *)_hoops_ASHSA->points,
											 _hoops_CSGCP->_hoops_SIHSA.length, _hoops_CSGCP->_hoops_SIHSA._hoops_IPPPP, null);
			}	break;


			case _hoops_PHHSA: {
				_hoops_HHHSA alter *			ii = &_hoops_ASHSA->_hoops_GPHSA->_hoops_CHHSA;
				DC_Point					start, end;
				int							hoffset, voffset;
				Int_Rectangle const &		_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

				start = Point (_hoops_ASHSA->xmin, _hoops_ASHSA->ymax, _hoops_ASHSA->_hoops_RICR);	// _hoops_PAGA: _hoops_GHCR _hoops_HSH _hoops_GGICR _hoops_GPP _hoops_AGCR _hoops_PGCR
				end   = Point (_hoops_ASHSA->xmax, _hoops_ASHSA->ymin, _hoops_ASHSA->_hoops_AICR);

				hoffset = ii->hoffset;
				voffset = 0;

				if (start.x < _hoops_GPHH.left) {
					hoffset += _hoops_GPHH.left - (int)start.x;
					start.x = (float)_hoops_GPHH.left;
				}
				if (start.y > _hoops_GPHH.top) {
					voffset = (int)start.y - _hoops_GPHH.top;
					start.y = (float)_hoops_GPHH.top;
				}

				if (end.x > _hoops_GPHH.right)
					end.x = (float)_hoops_GPHH.right;
				if (end.y < _hoops_GPHH.bottom)
					end.y = (float)_hoops_GPHH.bottom;

				if (start.x > end.x || start.y < end.y) break;

				_hoops_SSGCP (nr, &start, &end, hoffset, ii->format, ii->row_bytes, ii->rasters + voffset,
								   ii->pattern, ii->contrast_color, ii->db_image);
			}	break;


			case _hoops_SHHSA: {
				_hoops_GIHSA alter *	si = &_hoops_ASHSA->_hoops_GPHSA->_hoops_AIHSA;
				DC_Point				points[4];

				points[0].x = points[1].x = _hoops_ASHSA->xmin;
				points[2].x = points[3].x = _hoops_ASHSA->xmax;
				points[0].y = points[2].y = _hoops_ASHSA->ymin;
				points[1].y = points[3].y = _hoops_ASHSA->ymax;
				points[0].z = points[1].z = points[2].z = points[3].z = _hoops_ASHSA->_hoops_RICR;
  			  

				_hoops_GGRCP (nr, points, si->stencil);
			}	break;


			default: {
				_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
								   "Can't draw hidden item");
			}	break;
		}
	}


	//_hoops_PPISA = _hoops_CCSHP->_hoops_PPISA;
	if (_hoops_CHGCP) {
		hidden->next = null;	// _hoops_SGPHP, _hoops_HIH _hoops_PIP _hoops_SGS _hoops_RGRCP _hoops_GRS _hoops_ACRAA _hoops_SAII _hoops_RPP "_hoops_PISS"

		if (_hoops_ASHSA->type == _hoops_RIGCP) {
			if (_hoops_ASHSA->_hoops_APHGA->_hoops_CPP->_hoops_PRH._hoops_RGGIP) {
				Hidden_Tristrip alter *			_hoops_ACSIP = (Hidden_Tristrip alter *)hidden->_hoops_ASHSA->_hoops_GPHSA;	
				Net_Rendition const & 			nr = _hoops_ACSIP->_hoops_APHGA;
				Tristrip alter *				ts = (Tristrip alter *)_hoops_ACSIP->tristrips;

				ts->_hoops_SRHA |= DL_3D_TRANSPARENCY;
				if (ANYBIT (hidden->flags, HF_ZSORT_BACKFACE|HF_ZSORT_FRONTFACE)) {
					Net_Rendition _hoops_CRAI = nr.Copy();
					_hoops_HHCR _hoops_GGCC = _hoops_CRAI.Modify()->transform_rendition.Modify();

					if (!ANYBIT (_hoops_GGCC->heuristics, _hoops_RSA))
						_hoops_GGCC->heuristics |= _hoops_GPSA; //_hoops_SAHR _hoops_IRHH _hoops_IRS _hoops_AHGC
					_hoops_GGCC->flags |= _hoops_IGSP;
					if (BIT (hidden->flags, HF_ZSORT_BACKFACE))
						_hoops_GGCC->flags |= _hoops_SPP;
					_hoops_CRAI->transform_rendition = _hoops_GGCC;
					_hoops_RACIP (_hoops_CRAI,ts);
				}
				else
					_hoops_RACIP (nr,ts);
				HD_Free_Hidden_List (dc, hidden);
			}
			else
				_hoops_SAGCP (hidden);
		}
		else if (_hoops_ASHSA->type == _hoops_HIGCP) {
			/* _hoops_RPP (_hoops_PPISA->_hoops_CRSIP->_hoops_SICC->_hoops_IHSP._hoops_AGRCP) */ {
				_hoops_PGRCP alter *		_hoops_HGRCP = (_hoops_PGRCP alter *)hidden->_hoops_ASHSA->_hoops_GPHSA;	
				Net_Rendition const & 			nr = _hoops_HGRCP->_hoops_APHGA;
				Polymarker alter *				pm = (Polymarker alter *)_hoops_HGRCP->_hoops_GIGPR;

				pm->_hoops_SRHA |= DL_3D_TRANSPARENCY;
				_hoops_SACIP (nr, pm);
				HD_Free_Hidden_List (dc, hidden);
			}
			//_hoops_SHS {
				// _hoops_PSP _hoops_IGRCP _hoops_GAPR _hoops_IH _hoops_PSSI
			//}
		}	
		else
			HD_Free_Hidden_List (dc, hidden);


		hidden = next;
		if (hidden != null) {
			if (_hoops_GGPGR(hidden->_hoops_ASHSA->_hoops_APHGA)) {
				if (dc->_hoops_AHGCP != 0) {
					_hoops_HCSIP (dc, dc->_hoops_AHGCP, -MAX_FLOAT);
					FREE_ARRAY (dc->_hoops_AHGCP->data, 
								dc->_hoops_AHGCP->allocated, Hidden_Tristrip *);
					FREE (dc->_hoops_AHGCP, _hoops_SISIP);
					dc->_hoops_AHGCP = null;
				}

				if (dc->_hoops_SPSIP && dc->_hoops_SPSIP->used != 0)
					HD_Flush_Hidden_Item_Cache (dc);

				return hidden;
			}
			goto _hoops_GIGCP;
		}
		else {
			if (dc->_hoops_AHGCP != 0) {
				_hoops_HCSIP (dc, dc->_hoops_AHGCP, -MAX_FLOAT);
				FREE_ARRAY (dc->_hoops_AHGCP->data, 
						dc->_hoops_AHGCP->allocated, Hidden_Tristrip *);
				FREE (dc->_hoops_AHGCP, _hoops_SISIP);
				dc->_hoops_AHGCP = null;
			}

			if (dc->_hoops_SPSIP && dc->_hoops_SPSIP->used != 0)
				HD_Flush_Hidden_Item_Cache (dc);
		}
	}
	else {
		/* _hoops_GGCH _hoops_RHAR _hoops_PPR _hoops_HSP _hoops_ISP */
		HD_Painters_Bias_Z (hidden, true);
	}

	return null;
#endif
}


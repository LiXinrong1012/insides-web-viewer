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
 * $Id: obf_tmp.txt 1.49 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "phdraw.h"
#include "span.h"
#include "patterns.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HD_Buffer_DC_Rectangle_C08 (
	Net_Rendition const & nr,
	int								left,
	int								right,
	int								bottom,
	int								top) {
#ifndef DISABLE_RASTERIZER
	_hoops_HCSIR const		*_hoops_ICSIR;
	int								_hoops_ASGCR;
	unsigned char alter * const		*_hoops_RPPA;
	unsigned char alter * const		*_hoops_GSGCR;
	unsigned char					color;

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Rectangle (nr, left, right, bottom, top);
		return;
	}

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Rectangle (nr, left, right, bottom, top);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_PSGCR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	if (_hoops_ICSIR == null || _hoops_ICSIR->_hoops_HIAI == null) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Trying to clear a non-existent frame buffer");
		return;
	}

	Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (left < _hoops_GPHH.left)   
		left = _hoops_GPHH.left;
	if (right > _hoops_GPHH.right)  
		right = _hoops_GPHH.right;

	if ((_hoops_ASGCR = right - left + 1) <= 0)
		return;

	if (bottom < _hoops_GPHH.bottom) 
		bottom = _hoops_GPHH.bottom;
	if (top > _hoops_GPHH.top)
		top = _hoops_GPHH.top;

	color = (unsigned char)nr->_hoops_IHA->color._hoops_PGGCR;
	left -= _hoops_ICSIR->offset.x;

	_hoops_RPPA = &((unsigned char alter * const *)
		   _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[bottom - _hoops_ICSIR->offset.y];
	_hoops_GSGCR = &((unsigned char alter * const *)
		   _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[top - _hoops_ICSIR->offset.y];

	do SET_MEMORY (&_hoops_RPPA[0][left], _hoops_ASGCR, color);
	_hoops_RGGA (_hoops_RPPA++ == _hoops_GSGCR);
#endif
}



GLOBAL_FUNCTION void HD_Buffer_DC_Rectangle_C24 (
	Net_Rendition const & nr,
	int								left,
	int								right,
	int								bottom,
	int								top) {
#ifndef DISABLE_RASTERIZER
	_hoops_HCSIR const		*_hoops_ICSIR;
	RGBAS32 alter * const		*_hoops_SCGCR;
	RGBAS32 alter * const		*_hoops_HSGCR;
	RGBAS32 alter				*_hoops_RPPA;
	RGBAS32 alter				*_hoops_GSGCR;
	RGBAS32						color;
	int								_hoops_ASGCR;

	if (nr->transform_rendition->_hoops_HCHH != null) {
		HD_Std_DC_Rectangle (nr, left, right, bottom, top);
		return;
	}

	if (nr->_hoops_IHA->pattern != FP_SOLID) {
		HD_Span_DC_Rectangle (nr, left, right, bottom, top);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_PSGCR)) return;
#endif

	_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();
	color = nr->_hoops_IHA->color;

	Int_Rectangle const & _hoops_GPHH = nr->transform_rendition->_hoops_AGAA;

	if (left < _hoops_GPHH.left)   
		left = _hoops_GPHH.left;
	if (right > _hoops_GPHH.right)  
		right = _hoops_GPHH.right;

	if ((_hoops_ASGCR = (right - left + 1)*sizeof(RGBAS32)) <= 0)
		return;

	if (bottom < _hoops_GPHH.bottom) 
		bottom = _hoops_GPHH.bottom;
	if (top > _hoops_GPHH.top)	   
		top = _hoops_GPHH.top;


	left  -= _hoops_ICSIR->offset.x;
	right -= _hoops_ICSIR->offset.x;

	_hoops_SCGCR = &((RGBAS32 alter * const *)
		   _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[bottom - _hoops_ICSIR->offset.y];
	_hoops_HSGCR = &((RGBAS32 alter * const *)
		   _hoops_ICSIR->_hoops_HIAI->_hoops_RCPIR)[top - _hoops_ICSIR->offset.y];

	/*_hoops_IRHH _hoops_SPR _hoops_PSCR _hoops_IPS*/
	_hoops_RPPA = &_hoops_SCGCR[0][left];
	_hoops_GSGCR = &_hoops_SCGCR[0][right];
	_hoops_RGGA (_hoops_RPPA > _hoops_GSGCR)
		*_hoops_RPPA++ = color;

	_hoops_RPPA = &_hoops_SCGCR[0][left];

	while (++_hoops_SCGCR <= _hoops_HSGCR) {
		COPY_MEMORY(_hoops_RPPA, _hoops_ASGCR, &_hoops_SCGCR[0][left]);
	} 

#endif
}




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
 * $Id: obf_tmp.txt 1.43 2010-06-04 21:37:19 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "phdraw.h"
#include "span.h"


GLOBAL_FUNCTION void HD_Span_DC_Rectangle (
	Net_Rendition const &	nr,
	int						left,
	int						right,
	int						bottom,
	int						top) {
#ifndef DISABLE_RASTERIZER
	_hoops_GHISP			_hoops_RHISP;
	_hoops_AHISP					_hoops_CGIHS[_hoops_GGIHS];
	_hoops_AHISP alter *			_hoops_SGIHS = _hoops_CGIHS+_hoops_GGAPR(_hoops_CGIHS);
	_hoops_AHISP alter *			span;

	_hoops_HHCR const & _hoops_IHCR = nr->transform_rendition;

	if (_hoops_IHCR->_hoops_HCHH != null) {
		HD_Std_DC_Rectangle (nr, left, right, bottom, top);
		return;
	}

#ifdef _hoops_CGSPR
	if (BIT (nr->_hoops_IRR->_hoops_GSSIR, _hoops_PSGCR)) return;
#endif

	_hoops_RHISP.z = _hoops_HSCHA;
	_hoops_RHISP._hoops_PIHSR = nr->_hoops_SRA->_hoops_PGCC._hoops_PIHSR;
	_hoops_RHISP.color = nr->_hoops_IHA->color;
	_hoops_RHISP.contrast_color = nr->_hoops_IHA->contrast_color;
	_hoops_RHISP.pattern = nr->_hoops_IHA->pattern;

	if (left < _hoops_IHCR->_hoops_AGAA.left)   
		left = _hoops_IHCR->_hoops_AGAA.left;
	if (right > _hoops_IHCR->_hoops_AGAA.right)  
		right = _hoops_IHCR->_hoops_AGAA.right;
	if (bottom < _hoops_IHCR->_hoops_AGAA.bottom) 
		bottom = _hoops_IHCR->_hoops_AGAA.bottom;
	if (top > _hoops_IHCR->_hoops_AGAA.top)	   
		top = _hoops_IHCR->_hoops_AGAA.top;

	/*
	 * _hoops_IISS _hoops_RRP _hoops_IS _hoops_HSPH _hoops_GASAR _hoops_RPP _hoops_ICCGR _hoops_SSH _hoops_RHGPR
	 * _hoops_CCA _hoops_IRS _hoops_IGIR _hoops_SAIPR.  _hoops_PSCSR (_hoops_RH _hoops_HRIHS _hoops_IIGR _hoops_CIPSI)
	 * _hoops_CHR _hoops_GAHPR _hoops_IRIHS _hoops_IS _hoops_CIHH _hoops_IIGR _hoops_RH _hoops_GSSR _hoops_GHIS.
	 */
	{
		_hoops_HCSIR const	*_hoops_ICSIR = null;

		if (nr->_hoops_SAIR->_hoops_ASSIR != null)
			_hoops_ICSIR = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR();

		if (_hoops_ICSIR != null && _hoops_ICSIR->_hoops_HIAI != null) {
			if (top > _hoops_ICSIR->offset.y + _hoops_ICSIR->_hoops_HIAI->height - 1)
				top = _hoops_ICSIR->offset.y + _hoops_ICSIR->_hoops_HIAI->height - 1;
			if (bottom < _hoops_ICSIR->offset.y)
				bottom = _hoops_ICSIR->offset.y;
		}
	}

	span = _hoops_CGIHS;

	_hoops_RGGA (bottom > top) {
		span->left.bx._hoops_HAGR._hoops_SAGCR  = left;		/* _hoops_RHRSP */
		span->right.bx._hoops_HAGR._hoops_SAGCR = right + 1;	/* _hoops_HGIA */
		span->left.bz._hoops_HAGR._hoops_SAGCR = _hoops_HSCHA;
		span->right.bz._hoops_HAGR._hoops_SAGCR = _hoops_HSCHA;

		span = &span[1];
		++bottom;
		if (span == _hoops_SGIHS) {
			_hoops_HRCGH (nr, _hoops_RHISP, _hoops_CGIHS,
							   _hoops_GGIHS, bottom - _hoops_GGIHS);
			span = _hoops_CGIHS;
		}
	}

	if (span != _hoops_CGIHS)
		_hoops_HRCGH (nr, _hoops_RHISP, _hoops_CGIHS,
						   span - _hoops_CGIHS, bottom - (span - _hoops_CGIHS));
#endif
}

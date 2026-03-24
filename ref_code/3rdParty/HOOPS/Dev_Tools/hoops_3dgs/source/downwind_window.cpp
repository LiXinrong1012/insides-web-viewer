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
 * $Id: obf_tmp.txt 1.86 2010-10-27 00:51:29 covey Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "tandt.h"

// _hoops_PAGA: _hoops_RGAIP _hoops_HRGR *_hoops_HAR* _hoops_IRS _hoops_PAGGR _hoops_IS _hoops_SCII->_hoops_AGAIP, _hoops_GAR _hoops_SGS _hoops_GRS _hoops_PGAIP _hoops_AGRP
// _hoops_PPR _hoops_SR _hoops_RRP _hoops_IS _hoops_HGCR _hoops_IS _hoops_RH _hoops_HPHR _hoops_HRPR _hoops_SGS _hoops_CSAP _hoops_IIH _hoops_ARPP
GLOBAL_FUNCTION void HD_Downwind_Window (
	Net_Rendition alter &		nr,
	Attribute const *			_hoops_ASGPR) {
	Window const *				window = (Window const *)_hoops_ASGPR;
	_hoops_CGRA			_hoops_HGAIP = nr->_hoops_SAIR;
	_hoops_HHCR alter &	_hoops_IHCR = nr.Modify()->transform_rendition.Modify();
	_hoops_CGRA alter &	_hoops_SGRA = nr->_hoops_SAIR.Modify();
	_hoops_ISHHP const	&	_hoops_CSHHP = nr->_hoops_ASIR;
	Display_Context const *		dc = nr->_hoops_SRA;
	float						_hoops_RISHP, _hoops_AISHP,
								_hoops_PISHP, _hoops_HISHP;
	_hoops_HRPA					_hoops_RHSPR;
	float						_hoops_HPPHP;
	_hoops_PACIR			_hoops_IGAIP;

	if (_hoops_SGRA->_hoops_SICSR != null)
		_hoops_HPRH (_hoops_SGRA->_hoops_SICSR);
	_hoops_SGRA->_hoops_SICSR = null;
	if (dc->_hoops_APHHP == null) {
		if ((_hoops_SGRA->_hoops_SICSR = _hoops_CSHHP->window.texture) != null)
			_hoops_PRRH (_hoops_SGRA->_hoops_SICSR);
	}

	_hoops_SGRA->_hoops_CGAIP = _hoops_CSHHP->window.pattern;
	_hoops_SGRA->_hoops_SGAIP = _hoops_CSHHP->window._hoops_RARIP;
	_hoops_SGRA->_hoops_GPIR = _hoops_CSHHP->window.color;
	_hoops_SGRA->_hoops_GRAIP.red	 = _hoops_CSHHP->window._hoops_PGC.red;
	_hoops_SGRA->_hoops_GRAIP.green = _hoops_CSHHP->window._hoops_PGC.green;
	_hoops_SGRA->_hoops_GRAIP.blue	 = _hoops_CSHHP->window._hoops_PGC.blue;
	_hoops_SGRA->contrast_color = _hoops_CSHHP->window._hoops_HGIHP;
	_hoops_SGRA->_hoops_CGIHP.red   = _hoops_CSHHP->window._hoops_CGIHP.red;
	_hoops_SGRA->_hoops_CGIHP.green = _hoops_CSHHP->window._hoops_CGIHP.green;
	_hoops_SGRA->_hoops_CGIHP.blue  = _hoops_CSHHP->window._hoops_CGIHP.blue;

	_hoops_SGRA->_hoops_ASIHP = nr->_hoops_ASIR->window._hoops_ASIHP;

	if (BIT (_hoops_HGAIP->_hoops_ASIHP, _hoops_GCARP))
		_hoops_SGRA->_hoops_ASIHP |= _hoops_RCARP;


	HD_Undo_Screen (nr, &_hoops_RHSPR);

	_hoops_IGAIP = _hoops_HGAIP->extent;

	if (!BIT(dc->flags, _hoops_CPPHP) && BIT (_hoops_SGRA->_hoops_ASIHP, _hoops_HIARP))
		_hoops_IGAIP._hoops_AGPGP(_hoops_HGAIP->_hoops_RRAIP);

	_hoops_PISHP = (_hoops_IGAIP.right - _hoops_IGAIP.left) * 0.5f;
	_hoops_HISHP = (_hoops_IGAIP.top -	_hoops_IGAIP.bottom) * 0.5f;
	_hoops_RISHP = (_hoops_IGAIP.left +	_hoops_IGAIP.right) * 0.5f;
	_hoops_AISHP = (_hoops_IGAIP.top +	_hoops_IGAIP.bottom) * 0.5f;

	_hoops_SGRA->extent.left =	_hoops_RISHP + window->_hoops_RCHS.left   * _hoops_PISHP;
	_hoops_SGRA->extent.right =	_hoops_RISHP + window->_hoops_RCHS.right  * _hoops_PISHP;
	_hoops_SGRA->extent.bottom = _hoops_AISHP + window->_hoops_RCHS.bottom * _hoops_HISHP;
	_hoops_SGRA->extent.top =	_hoops_AISHP + window->_hoops_RCHS.top    * _hoops_HISHP;

	if (BIT(dc->flags, _hoops_CPPHP))
		return;		/* _hoops_SGS'_hoops_GRI _hoops_SCH, _hoops_PSP _hoops_HHIPR _hoops_CIPH _hoops_IH _hoops_HA */

	_hoops_SGRA->_hoops_PHRA.left =	FLOOR (_hoops_SGRA->extent.left + 0.499f);
	_hoops_SGRA->_hoops_PHRA.bottom = FLOOR (_hoops_SGRA->extent.bottom + 0.499f);
	_hoops_SGRA->_hoops_PHRA.right =	FLOOR (_hoops_SGRA->extent.right - 0.5f);/*_hoops_CRRPR "- 1"*/
	_hoops_SGRA->_hoops_PHRA.top =	FLOOR (_hoops_SGRA->extent.top - 0.5f);  /*_hoops_CRRPR "- 1"*/

	if (_hoops_SGRA->_hoops_PHRA.right < _hoops_SGRA->_hoops_PHRA.left)
		_hoops_SGRA->_hoops_PHRA.right = _hoops_SGRA->_hoops_PHRA.left;

	if (_hoops_SGRA->_hoops_PHRA.top < _hoops_SGRA->_hoops_PHRA.bottom)
		_hoops_SGRA->_hoops_PHRA.top = _hoops_SGRA->_hoops_PHRA.bottom;

	_hoops_SGRA->_hoops_CIIH = _hoops_SGRA->_hoops_PHRA;

	if (BIT (_hoops_SGRA->_hoops_ASIHP, _hoops_IIARP)) {
		if (_hoops_SGRA->_hoops_CIIH.left < _hoops_HGAIP->_hoops_PHRA.left)
			_hoops_SGRA->_hoops_CIIH.left += _hoops_HGAIP->_hoops_RRAIP.left;
		if (_hoops_SGRA->_hoops_CIIH.right > _hoops_HGAIP->_hoops_PHRA.right)
			_hoops_SGRA->_hoops_CIIH.right -= _hoops_HGAIP->_hoops_RRAIP.right;
		if (_hoops_SGRA->_hoops_CIIH.bottom < _hoops_HGAIP->_hoops_PHRA.bottom)
			_hoops_SGRA->_hoops_CIIH.bottom	+= _hoops_HGAIP->_hoops_RRAIP.bottom;
		if (_hoops_SGRA->_hoops_CIIH.top > _hoops_HGAIP->_hoops_PHRA.top)
			_hoops_SGRA->_hoops_CIIH.top -= _hoops_HGAIP->_hoops_RRAIP.top;

		_hoops_SGRA->_hoops_PHRA = _hoops_SGRA->_hoops_PHRA._hoops_PGPGP(_hoops_HGAIP->_hoops_PHRA);
	}

	_hoops_SGRA->_hoops_SCIH = _hoops_SGRA->_hoops_PHRA;

	if (BIT (_hoops_SGRA->_hoops_ASIHP, _hoops_HIARP))
		_hoops_SGRA->_hoops_SCIH = _hoops_SGRA->_hoops_SCIH._hoops_PGPGP(_hoops_HGAIP->_hoops_PHRA);

	_hoops_SGRA->_hoops_SCIH._hoops_PGPGP(_hoops_HGAIP->_hoops_SCIH);

	_hoops_SGRA->_hoops_HHCAR = _hoops_SGRA->_hoops_SCIH;
	_hoops_SGRA->_hoops_HHCAR._hoops_IACHA(dc->_hoops_ARAIP);

	_hoops_SGRA->_hoops_RRAIP.left = _hoops_SGRA->_hoops_RRAIP.right = 0;
	_hoops_SGRA->_hoops_RRAIP.bottom = _hoops_SGRA->_hoops_RRAIP.top = 0;

	/* _hoops_HSIH _hoops_AHHSR _hoops_SHRRR */
	if (_hoops_SGRA->_hoops_CIIH.right > _hoops_SGRA->_hoops_CIIH.left)
		_hoops_SGRA->_hoops_CSIH = (float)(_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom) /
					 (float)(_hoops_SGRA->_hoops_CIIH.right - _hoops_SGRA->_hoops_CIIH.left) *
					 dc->current._hoops_AGRS;


	if (_hoops_IHCR->_hoops_SPH != null)
		_hoops_IHCR->flags |= _hoops_PRAIP;
	HD_Redo_Screen (nr, &_hoops_RHSPR);


	_hoops_SGRA->_hoops_ASSIR = null;

	if (BIT(nr->flags, _hoops_GHSHP))
		nr.Modify()->flags |= _hoops_SPSHP;

	if (_hoops_IHCR->_hoops_SPH) {
		_hoops_HPPHP = *_hoops_IHCR->_hoops_SPH->_hoops_SIPCR;

		if (_hoops_HPPHP > 0.0f)
			_hoops_IHCR->_hoops_CHCR = _hoops_HPPHP;
		else if (_hoops_HPPHP < 0.0f)
			_hoops_IHCR->_hoops_CHCR = -_hoops_HPPHP;
		else
			_hoops_IHCR->_hoops_CHCR = Abs(_hoops_GIPHP);

		_hoops_IHCR->_hoops_RIPHP = 1.0f;

		float	width = nr->_hoops_SAIR->_hoops_PHRA.right - nr->_hoops_SAIR->_hoops_PHRA.left;
		_hoops_IHCR->_hoops_HIPHP = width / _hoops_IHCR->_hoops_SPH->_hoops_ISPA;
		if (width > 0.0f)
			_hoops_IHCR->_hoops_IIPHP = _hoops_IHCR->_hoops_SPH->_hoops_ISPA / width;
		else
			_hoops_IHCR->_hoops_IIPHP = 1.0e9f;
	}
}

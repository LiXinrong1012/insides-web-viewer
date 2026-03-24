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
 * $Id: obf_tmp.txt 1.56 2010-02-16 20:06:55 heppe Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "patterns.h"
#include "hd_proto.h"
#include "hi_proto.h"


GLOBAL_FUNCTION void HD_Standard_Draw_Window_Frame (
	Net_Rendition const &		inr,
	Int_Rectangle const *		extent,
	Int_Rectangle alter *		frame,
	bool						calculate_only) {
	Net_Rendition				nr = inr;
	Line_Rendition				_hoops_ASGIP;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Display_Context const *		dc = nr->_hoops_SRA;
	int							left = extent->left,
								right = extent->right,
								bottom = extent->bottom,
								top = extent->top;
	int							line_weight = dc->_hoops_PGCC._hoops_IHHSR;
	int							_hoops_IHISS = 2;
	bool						_hoops_CHISS = true;
	bool						_hoops_SHISS = true;
	DC_Point					pt[5];

	if (BIT(_hoops_SGRA->_hoops_ASIHP, _hoops_PIARP)) {
		_hoops_IHISS = 1;
		_hoops_SHISS = false;
	}

	frame->left = frame->right = frame->bottom = frame->top = _hoops_IHISS * line_weight;

	if (calculate_only) 
		return;

	if (_hoops_SGRA->_hoops_CGAIP == FP_WINDOW_TRANSPARENT ||
		_hoops_SGRA->_hoops_CGAIP == FP_WINDOW_TRANS_NO_ZCLEAR)
		_hoops_SHISS = false;

	/* _hoops_AHHCP _hoops_III _hoops_CCA _hoops_RSPH _hoops_SPR _hoops_IH _hoops_HCHSR */
	_hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();

	HD_Replace_Line_Style(_hoops_ASGIP, nr->_hoops_GCSHP->_hoops_IHRIP);

	_hoops_ASGIP->weight = dc->_hoops_PGCC._hoops_IHHSR;

	if (BIT(nr->_hoops_IRR->_hoops_CHP, _hoops_SHP))
		nr.Modify()->_hoops_IRR.Modify()->_hoops_CHP &= ~_hoops_SHP;
	if ( BIT(nr->_hoops_IRR->_hoops_PPH, _hoops_CRI) )
		nr.Modify()->_hoops_IRR.Modify()->_hoops_PPH &= ~_hoops_CRI;
	if (BIT (nr->transform_rendition->heuristics, _hoops_IRI))
		nr.Modify()->transform_rendition.Modify()->heuristics &= ~_hoops_IRI;

	if (_hoops_CHISS) {
		_hoops_ASGIP->color = _hoops_SGRA->contrast_color;

		if (BIT(_hoops_SGRA->_hoops_ASIHP, _hoops_PIARP)) {
			/* _hoops_ARP _hoops_GH _hoops_CGRHH _hoops_III */
			pt[0].x = (float)left;
			pt[0].y = (float)bottom;
			pt[0].z = 0.0f;
			pt[1].x = (float)left;
			pt[1].y = (float)top;
			pt[1].z = 0.0f;
			pt[2].x = (float)right;
			pt[2].y = (float)top;
			pt[2].z = 0.0f;
			pt[3].x = (float)right;
			pt[3].y = (float)bottom;
			pt[3].z = 0.0f;
			pt[4].x = (float)left;
			pt[4].y = (float)bottom;
			pt[4].z = 0.0f;

			_hoops_SCGGA (nr, 5, pt);
		}
		else {
			/* _hoops_ARP _hoops_GH _hoops_ASSA _hoops_HCHSR _hoops_III */
			pt[0].x = (float)(left + line_weight);
			pt[0].y = (float)(bottom + line_weight);
			pt[0].z = 0.0f;
			pt[1].x = (float)(left + line_weight);
			pt[1].y = (float)(top - line_weight);
			pt[1].z = 0.0f;
			pt[2].x = (float)(right - line_weight);
			pt[2].y = (float)(top - line_weight);
			pt[2].z = 0.0f;
			pt[3].x = (float)(right - line_weight);
			pt[3].y = (float)(bottom + line_weight);
			pt[3].z = 0.0f;
			pt[4].x = (float)(left + line_weight);
			pt[4].y = (float)(bottom + line_weight);
			pt[4].z = 0.0f;

			_hoops_SCGGA (nr, 5, pt);
		}
	}

	if (_hoops_SHISS) {
		/* _hoops_PPR _hoops_HA _hoops_RH _hoops_GSSR _hoops_HCHSR _hoops_III */
		if (!nr->shared()) {
			/* _hoops_GIGHR: _hoops_RGR _hoops_RRGR _hoops_RPGAR _hoops_IS _hoops_RPRS _hoops_RH _hoops_HGIIP _hoops_SAHR _hoops_IGI
			** _hoops_IH _hoops_RH _hoops_PGHC _hoops_III _hoops_IS _hoops_ASAC _hoops_GPP _hoops_IPS/_hoops_CIH _hoops_HCPH.  _hoops_CGP _hoops_IRS
			** _hoops_IPP _hoops_PAH _hoops_SHH _hoops_CGAPA, _hoops_SR _hoops_HS _hoops_IS _hoops_CIPAA _hoops_RGCI _hoops_HSHR
			** _hoops_CR _hoops_SR _hoops_CHR _hoops_HHACR _hoops_SCH */

			nr.Renew();
			_hoops_ASGIP.Renew();

			_hoops_ASGIP->_hoops_SSHHP = null;

			/* _hoops_AGCR _hoops_PGCR _hoops_ARAR _hoops_GHCA _hoops_SHH _hoops_SIGR _hoops_RPP _hoops_SR _hoops_PGSA _hoops_GGHAS _hoops_RAGAH */
			_hoops_ASGIP->_hoops_IHA = null;
			_hoops_ASGIP->contrast_rendition = null;
		}
		else
			_hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();

		_hoops_ASGIP->color = _hoops_SGRA->_hoops_GPIR;

		/* _hoops_ARP _hoops_GH _hoops_CGRHH _hoops_III */
		pt[0].x = (float)left;
		pt[0].y = (float)bottom;
		pt[0].z = 0.0f;
		pt[1].x = (float)left;
		pt[1].y = (float)top;
		pt[1].z = 0.0f;
		pt[2].x = (float)right;
		pt[2].y = (float)top;
		pt[2].z = 0.0f;
		pt[3].x = (float)right;
		pt[3].y = (float)bottom;
		pt[3].z = 0.0f;
		pt[4].x = (float)left;
		pt[4].y = (float)bottom;
		pt[4].z = 0.0f;

		_hoops_SCGGA (nr, 5, pt);
	}
}

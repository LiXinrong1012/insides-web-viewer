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
 * $Id: obf_tmp.txt 1.50 2011-01-18 22:42:13 covey Exp $
 */


#include "hoops.h"
#include "driver.h"
#include "hd_proto.h"
#include "database.h"
#include "patterns.h"


GLOBAL_FUNCTION void HD_Std_DC_Colorized_Polymarker (
	Net_Rendition const &		inr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						_hoops_AIPSP,
	float const *				rotations,
	float const *				size_fixups) {
	Net_Rendition				nr = inr.Copy();
	_hoops_ICP const &	_hoops_CCP = nr->_hoops_GSP;
	Line_Rendition				_hoops_HC;
   
	if (_hoops_CCP->_hoops_SSHHP == null) {
		((_hoops_ICP alter &)_hoops_CCP)->_hoops_SSHHP = nr->_hoops_AHP;
		Line_Rendition alter &	_hoops_ASGIP = ((_hoops_ICP alter &)_hoops_CCP)->_hoops_SSHHP.Modify();

		HD_Replace_Line_Style(_hoops_ASGIP, nr->_hoops_GCSHP->_hoops_IHRIP);

		float weight = 1.0f;

		if (BIT(_hoops_CCP->flags, _hoops_SGPSP)) {

			weight = _hoops_CCP->_hoops_GRPSP.value;

			// _hoops_IPIH _hoops_RGAR _hoops_ICPAA _hoops_GGR _hoops_HII _hoops_III _hoops_PCIAA _hoops_GGRGR-_hoops_CIICS
			ASSERT(_hoops_CCP->_hoops_GRPSP._hoops_HHP == GSU_PIXELS);
		}

		_hoops_ASGIP->weight = weight * nr->_hoops_SRA->_hoops_PGCC._hoops_IHHSR;

		_hoops_ASGIP->color = _hoops_CCP->color;
		_hoops_ASGIP->contrast_color = _hoops_CCP->contrast_color;

		_hoops_ASGIP->_hoops_CHA = _hoops_CCP->_hoops_CHA;
	}
	_hoops_HC = nr->_hoops_AHP = _hoops_CCP->_hoops_SSHHP;

	if (_hoops_HC->_hoops_IHA == null) {
		_hoops_HC->_hoops_IHA = nr->_hoops_IHA;
		_hoops_CIGA alter &		_hoops_SIGA = _hoops_HC->_hoops_IHA.Modify();

		_hoops_SIGA->color = _hoops_HC->color;
		_hoops_SIGA->contrast_color = _hoops_HC->contrast_color;
		_hoops_SIGA->pattern = FP_SOLID;

		_hoops_SIGA->_hoops_CHA = _hoops_HC->_hoops_CHA;
	} 
	nr->_hoops_IHA = _hoops_HC->_hoops_IHA;

	if (nr->transform_rendition->_hoops_CHIH != 0 ||
		!BIT (nr->transform_rendition->heuristics, _hoops_CGCS)) {
		_hoops_HHCR alter &		_hoops_GGCC = nr->transform_rendition.Modify(1000000);

		_hoops_GGCC->_hoops_CHIH = 0;
		_hoops_GGCC->heuristics |= _hoops_CGCS;
	}

	if (BIT (nr->transform_rendition->flags, _hoops_AIHS) &&
		(size_fixups != null || _hoops_CCP->_hoops_RGRS > 0.5f || _hoops_CCP->ysize > 0.5f))
		nr->transform_rendition.Modify()->flags &= ~_hoops_AIHS;

	HD_Draw_Glyphs (nr, 0, count, points, colors, _hoops_AIPSP, rotations, size_fixups);
}

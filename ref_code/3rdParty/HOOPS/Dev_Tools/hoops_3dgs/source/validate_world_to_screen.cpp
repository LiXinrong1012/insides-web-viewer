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
 * $Id: obf_tmp.txt 1.30 2010-01-13 00:37:08 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"


GLOBAL_FUNCTION void HD_Validate_World_To_Screen (
	Net_Rendition const &		nr) {
	Net_Rendition				_hoops_APS = nr;
	_hoops_HHCR alter &	_hoops_IHCR = _hoops_APS->transform_rendition;
	Point						scale,
								translate;
	float						_hoops_CHHCR = 0.0f;

	switch (nr->transform_rendition->_hoops_RHPHP) {
		case _hoops_AHPHP:
				_hoops_CHHCR = 0.0f;
				break;
		case _hoops_PHPHP:
				_hoops_CHHCR = -nr->transform_rendition->_hoops_ACSRP;
				break;
		case _hoops_HHPHP:
				_hoops_CHHCR =  nr->transform_rendition->_hoops_ACSRP;
				break;
	}

	if (!HI_Camera_To_Transform ((_hoops_HHRA alter *)_hoops_IHCR->_hoops_SPH, _hoops_CHHCR))
		return;

	HD_Compute_Screen_Transform (nr, &scale, &translate);

	_hoops_IHCR->_hoops_CGCC.Modify();

	HI_Scale_And_Translate_Matrix (&_hoops_IHCR->_hoops_SPH->_hoops_GRCC,
								   scale.x, scale.y, scale.z,
								   translate.x, translate.y, translate.z,
								   &_hoops_IHCR->_hoops_CGCC->data);

	_hoops_IHCR->flags |= _hoops_IGCC;
}



GLOBAL_FUNCTION void HD_Validate_Object_To_Proj (
	Net_Rendition const &		nr) {
	Net_Rendition				_hoops_APS = nr;
	_hoops_HHCR alter &	_hoops_IHCR = _hoops_APS->transform_rendition;
	float						_hoops_CHHCR;

	switch (nr->transform_rendition->_hoops_RHPHP) {
		case _hoops_PHPHP:
				_hoops_CHHCR = -nr->transform_rendition->_hoops_ACSRP;
				break;
		case _hoops_HHPHP:
				_hoops_CHHCR =  nr->transform_rendition->_hoops_ACSRP;
				break;
		case _hoops_AHPHP:
		default:
				_hoops_CHHCR = 0.0f;
				break;
	}

	if (!HI_Camera_To_Transform ((_hoops_HHRA alter *)_hoops_IHCR->_hoops_SPH, _hoops_CHHCR))
		return;

	_hoops_IHCR->object_to_projection_matrix.Modify();

	HI_Multiply_Matrices (&_hoops_IHCR->_hoops_IPH->data,
						  &_hoops_IHCR->_hoops_SPH->_hoops_GRCC,
						  &_hoops_IHCR->object_to_projection_matrix->data);

	_hoops_IHCR->flags |= _hoops_HCPHP;
}


GLOBAL_FUNCTION void HD_Validate_Object_To_View (
	Net_Rendition const &		nr) {
	Net_Rendition				_hoops_APS = nr;
	_hoops_HHCR alter &	_hoops_IHCR = _hoops_APS->transform_rendition;

	if (_hoops_IHCR->_hoops_GGPSP == null || _hoops_IHCR->_hoops_GGPSP->shared())
		_hoops_IHCR->_hoops_GGPSP = _hoops_SGCC::Create (nr->_hoops_SRA);

	HI_Multiply_Matrices (&_hoops_IHCR->_hoops_IPH->data,
						  &_hoops_IHCR->_hoops_SPH->_hoops_PRPA,
						  &_hoops_IHCR->_hoops_GGPSP->data);

	_hoops_IHCR->flags |= _hoops_ICPHP;
}



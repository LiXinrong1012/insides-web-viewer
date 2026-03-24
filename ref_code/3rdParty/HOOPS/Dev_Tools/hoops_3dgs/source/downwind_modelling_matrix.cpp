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
 * $Id: obf_tmp.txt 1.69 2010-09-22 02:29:38 trask Exp $
 */


#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hd_proto.h"
#include "hi_proto.h"

#define _hoops_CACIR (1e-5)



GLOBAL_FUNCTION void HD_Append_Modelling_Matrix (
	Net_Rendition alter &			nr,
	_hoops_HRPA const *				_hoops_SCIHP) {
	Display_Context alter *			dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_HHCR				_hoops_IHCR;
	_hoops_HRPA alter *				mat;

	if (!ANYBIT (_hoops_SCIHP->_hoops_RAGR, _hoops_CICH))
		return;

	_hoops_IHCR = nr.Modify()->transform_rendition.Modify();

	/*
	 * _hoops_SIIR "_hoops_IHIR" _hoops_RSGA
	 */
	if (_hoops_IHCR->matrix->shared()) {
		_hoops_SGCC			temp = _hoops_SGCC::Create (dc);

		HI_Multiply_Matrices (_hoops_SCIHP,
							  &_hoops_IHCR->matrix->data,
							  &temp->data);
		_hoops_IHCR->matrix = temp;
	}
	else {
		_hoops_HRPA					_hoops_RHSPR;

		mat = &_hoops_IHCR->matrix->data;

		HI_Copy_Matrix (mat, &_hoops_RHSPR);
		HI_Multiply_Matrices (_hoops_SCIHP, &_hoops_RHSPR, mat);
	}


	/*
	 * _hoops_SIIR _hoops_GCHRR _hoops_PRGIA _hoops_RSGA
	 */
	if (_hoops_IHCR->_hoops_IPH->shared()) {
		_hoops_SGCC			temp = _hoops_SGCC::Create (dc);

		HI_Multiply_Matrices (_hoops_SCIHP,
							  &_hoops_IHCR->_hoops_IPH->data,
							  &temp->data);
		_hoops_IHCR->_hoops_IPH = temp;
	}
	else {
		_hoops_HRPA					_hoops_RHSPR;

		mat = &_hoops_IHCR->_hoops_IPH->data;

		HI_Copy_Matrix (mat, &_hoops_RHSPR);
		HI_Multiply_Matrices (_hoops_SCIHP, &_hoops_RHSPR, mat);
	}

	if (BIT (_hoops_SCIHP->_hoops_RAGR, _hoops_RRICR))
		_hoops_IHCR->flags |= _hoops_GSIHP;
	_hoops_IHCR->flags |= _hoops_AIPHP;
	_hoops_IHCR->flags &= ~(_hoops_IGCC |
				   _hoops_HCPHP |
				   _hoops_ICPHP);
}

GLOBAL_FUNCTION void HD_Downwind_Modelling_Matrix (
	Net_Rendition alter &		nr,
	Attribute const *			_hoops_ASGPR) {

	HD_Append_Modelling_Matrix (nr, &((_hoops_ISGI const *)_hoops_ASGPR)->matrix);
}


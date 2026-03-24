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
 * $Id: obf_tmp.txt 1.51 2010-11-30 23:40:33 jason Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"


GLOBAL_FUNCTION void HD_Redo_Screen (
	Net_Rendition const &		nr,
	_hoops_HRPA alter *			matrix) {
	_hoops_HHCR alter &	_hoops_IHCR = _hoops_PGRCA(nr)->transform_rendition;
	Point						scale;
	Point						translate;

	if (_hoops_IHCR->matrix->shared())
		_hoops_IHCR->matrix.Modify();

	_hoops_IHCR->flags &= ~_hoops_PSASP;

	if (!BIT (_hoops_IHCR->flags, _hoops_PRAIP)) {
		HI_Copy_Matrix (matrix, &_hoops_IHCR->matrix->data);
	}
	else {
		HD_Compute_Screen_Transform (nr, &scale, &translate);

		HI_Scale_And_Translate_Matrix (matrix,
									   scale.x, scale.y, scale.z,
									   translate.x, translate.y, translate.z,
									   &_hoops_IHCR->matrix->data);

		_hoops_IHCR->matrix->data.flags &= ~_hoops_HASA;
		_hoops_IHCR->flags &= ~_hoops_IGCC;

		if (!nr->_hoops_SAIR->_hoops_SCIH._hoops_HPCIR(nr->_hoops_SAIR->_hoops_CIIH))
			_hoops_IHCR->flags |= _hoops_PSASP;
	}
}


GLOBAL_FUNCTION void HD_Undo_Screen (
	Net_Rendition const &		nr,
	_hoops_HRPA alter *			matrix) {
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	Point						scale;
	Point						translate;

	if (!BIT (_hoops_IHCR->flags, _hoops_PRAIP)) {
		HI_Copy_Matrix (&_hoops_IHCR->matrix->data, matrix);
	}
	else {
		HD_Compute_Screen_Transform (nr, &scale, &translate);

		if (scale.x == 0)
			scale.x = 1.0f;
		if (scale.y == 0)
			scale.y = 1.0f;
		if (scale.z == 0)
			scale.z = 1.0f;

		HI_Scale_And_Translate_Matrix (&_hoops_IHCR->matrix->data,
									   1.0f / scale.x,
									   1.0f / scale.y,
									   1.0f / scale.z,
									   -translate.x / scale.x,
									   -translate.y / scale.y,
									   -translate.z / scale.z,
									   matrix);
	}
}


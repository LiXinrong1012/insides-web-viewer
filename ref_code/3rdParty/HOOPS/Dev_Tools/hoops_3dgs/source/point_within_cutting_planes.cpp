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
 * $Id: obf_tmp.txt 1.30 2009-10-23 23:20:44 trask Exp $
 */
#include "hoops.h"
#include "driver.h"
#include "hd_proto.h"

GLOBAL_FUNCTION bool HD_Point_Within_Cutting_Set (
	_hoops_IAPA const *		_hoops_HRCAR,
	float							x,
	float							y,
	float							z) {
	_hoops_GPPA const *	_hoops_IRCAR;

	_hoops_IRCAR = _hoops_HRCAR->_hoops_APPA;

	do if (x * _hoops_IRCAR->_hoops_SPPA.a +
		   y * _hoops_IRCAR->_hoops_SPPA.b +
		   z * _hoops_IRCAR->_hoops_SPPA.c + _hoops_IRCAR->_hoops_SPPA.d > 0.0f)
		return false;
	while ((_hoops_IRCAR = _hoops_IRCAR->next) != null);

	return true;
}

GLOBAL_FUNCTION bool HD_Point_Within_Cutting_Planes (
	_hoops_HHCR const &		_hoops_IHCR,
	float							x,
	float							y,
	float							z) {
	_hoops_IAPA const *		_hoops_HRCAR;

	_hoops_HRCAR = _hoops_IHCR->_hoops_RGH->_hoops_PHCA;

	do if (HD_Point_Within_Cutting_Set (_hoops_HRCAR, x, y, z))
		return true;
	while ((_hoops_HRCAR = _hoops_HRCAR->next) != null);

	return false;
}


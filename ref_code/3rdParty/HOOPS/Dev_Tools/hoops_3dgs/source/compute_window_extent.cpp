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
 * $Id: obf_tmp.txt 1.46 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "database.h"
#include "please.h"
#include "hd_proto.h"
#include "hi_proto.h"


GLOBAL_FUNCTION bool HI_Compute_Window_Extent (
	_hoops_AIGPR *		_hoops_RIGC,
	char const *				segname,
	float *						_hoops_AGACA,
	float *						_hoops_PGACA,
	int *						_hoops_HGACA,
	int *						_hoops_IGACA,
	int *						left,
	int *						right,
	int *						bottom,
	int *						top) {
	_hoops_GGAGR *						_hoops_GHRI;
	_hoops_RIACA		_hoops_AIACA;

	if ((_hoops_GHRI = HI_Force_Find_Owner_Actor (_hoops_RIGC, segname, &_hoops_AIACA.context)) == null)
		return false;

	if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_PIACA, &_hoops_AIACA))
		return false;

	*_hoops_AGACA = _hoops_AIACA._hoops_HAP.x;
	*_hoops_PGACA = _hoops_AIACA._hoops_HAP.y;
	*_hoops_HGACA = _hoops_AIACA._hoops_HIACA.x;
	*_hoops_IGACA = _hoops_AIACA._hoops_HIACA.y;
	*left	= _hoops_AIACA._hoops_IIACA.left;
	*right	= _hoops_AIACA._hoops_IIACA.right;
	*bottom = _hoops_AIACA._hoops_IIACA.bottom;
	*top	= _hoops_AIACA._hoops_IIACA.top;
	return true;
}


GLOBAL_FUNCTION bool HI_Compute_Window_Extent_By_Pth (
	_hoops_AIGPR *		_hoops_RIGC,
	int							count,
	_hoops_CRCP const **			_hoops_SISAA,
	float *						_hoops_AGACA,
	float *						_hoops_PGACA,
	int *						_hoops_HGACA,
	int *						_hoops_IGACA,
	int *						left,
	int *						right,
	int *						bottom,
	int *						top) {
	_hoops_GGAGR *						_hoops_GHRI;
	_hoops_RIACA		_hoops_AIACA;

	if ((_hoops_GHRI = HI_Force_Find_Path_Actor (_hoops_RIGC, count, _hoops_SISAA, &_hoops_AIACA.context)) == null)
		return false;

	_hoops_AIACA.context = null;
	_hoops_AIACA._hoops_CISAA = count;
	_hoops_AIACA.path = _hoops_SISAA;

	if (!_hoops_HISAA (_hoops_RIGC, _hoops_GHRI, _hoops_PIACA, &_hoops_AIACA))
		return false;

	*_hoops_AGACA = _hoops_AIACA._hoops_HAP.x;
	*_hoops_PGACA = _hoops_AIACA._hoops_HAP.y;
	*_hoops_HGACA = _hoops_AIACA._hoops_HIACA.x;
	*_hoops_IGACA = _hoops_AIACA._hoops_HIACA.y;
	*left	= _hoops_AIACA._hoops_IIACA.left;
	*right	= _hoops_AIACA._hoops_IIACA.right;
	*bottom = _hoops_AIACA._hoops_IIACA.bottom;
	*top	= _hoops_AIACA._hoops_IIACA.top;
	return true;
}

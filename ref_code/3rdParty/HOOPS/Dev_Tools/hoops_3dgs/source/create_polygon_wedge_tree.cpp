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
 * $Id: obf_tmp.txt 1.30 2010-09-22 02:29:38 trask Exp $
 */

#include "hoops.h"
#include "topology.h"
#include "hi_proto.h"



GLOBAL_FUNCTION void HI_Free_Wedge_Tree (
	_hoops_RGASA	*tree) {

	if (tree != null) {
		HI_Free_Wedge_Tree (tree->left);
		HI_Free_Wedge_Tree (tree->right);
		FREE (tree, _hoops_RGASA);
	}
}



local _hoops_RGASA *_hoops_AGASA (
	Point		   *pivot,
	Point		   *vertices,
	int			   _hoops_PGASA,
	int				_hoops_HGASA,
	int			   _hoops_IGASA,
	bool		_hoops_CGASA) {

	if (_hoops_IGASA - _hoops_PGASA <= 1) return null;
	else {
		_hoops_RGASA	*_hoops_SGASA;
		int				_hoops_SPGIR;

		ALLOC (_hoops_SGASA, _hoops_RGASA);

		_hoops_SGASA->_hoops_HGASA = _hoops_HGASA;
		_hoops_SGASA->_hoops_GRASA.x = vertices[_hoops_HGASA].x - pivot->x;
		_hoops_SGASA->_hoops_GRASA.y = vertices[_hoops_HGASA].y - pivot->y;
		_hoops_SGASA->_hoops_GRASA.z = 0.0f;

		if (_hoops_CGASA) {
			_hoops_SPGIR = (_hoops_PGASA + _hoops_HGASA) / 2;
			_hoops_SGASA->left	 = _hoops_AGASA (pivot, vertices,
										   _hoops_PGASA, _hoops_SPGIR, _hoops_HGASA, _hoops_CGASA);

			_hoops_SPGIR = (_hoops_IGASA + _hoops_HGASA) / 2;
			_hoops_SGASA->right = _hoops_AGASA (pivot, vertices,
										   _hoops_HGASA, _hoops_SPGIR, _hoops_IGASA, _hoops_CGASA);
		}
		else {
			_hoops_SPGIR = (_hoops_PGASA + _hoops_HGASA) / 2;
			_hoops_SGASA->right = _hoops_AGASA (pivot, vertices,
										   _hoops_PGASA, _hoops_SPGIR, _hoops_HGASA, _hoops_CGASA);

			_hoops_SPGIR = (_hoops_IGASA + _hoops_HGASA) / 2;
			_hoops_SGASA->left	 = _hoops_AGASA (pivot, vertices,
										   _hoops_HGASA, _hoops_SPGIR, _hoops_IGASA, _hoops_CGASA);
		}

		return _hoops_SGASA;
	}
}


#define _hoops_SAIGA 15

GLOBAL_FUNCTION _hoops_RGASA * HI_Create_Polygon_Wedge_Tree (
	int				count,
	Point		*points,
	Point		*pivot,
	bool		_hoops_CGASA) {
	Vector		_hoops_RRASA, _hoops_HIHHA;
	int				_hoops_SPGIR = 1;
	int				_hoops_APIGA[_hoops_SAIGA + 1];
	int alter		*face_list;
	int				index;
	_hoops_ARASA _hoops_PRASA;

	if (count < 3) return null;

	if (count > _hoops_SAIGA)
		ALLOC_ARRAY (face_list, count + 1, int);
	else
		face_list = _hoops_APIGA;

	face_list[0] = count;
	for (index = 0; index < count; ++index)
		face_list[index+1] = index;

	_hoops_PRASA = HI_Rank_Polygon (points, face_list, face_list + count + 1);

	if (count > _hoops_SAIGA)
		FREE_ARRAY (face_list, count + 1, int);

	if (_hoops_PRASA != _hoops_HRIHR) return null;	/* _hoops_PAH'_hoops_RA _hoops_IRHH _hoops_RRII */


	_hoops_RRASA.x = points[0].x - pivot->x;
	_hoops_RRASA.y = points[0].y - pivot->y;

	_hoops_HIHHA.x = points[1].x - pivot->x;
	_hoops_HIHHA.y = points[1].y - pivot->y;

	if (_hoops_CGASA) {
		do {
			++_hoops_SPGIR;
			_hoops_HIHHA.x = points[_hoops_SPGIR].x - pivot->x;
			_hoops_HIHHA.y = points[_hoops_SPGIR].y - pivot->y;
		} _hoops_RGGA (_hoops_RRASA.x * _hoops_HIHHA.y <= _hoops_HIHHA.x * _hoops_RRASA.y);
	}
	else {
		do {
			++_hoops_SPGIR;
			_hoops_HIHHA.x = points[_hoops_SPGIR].x - pivot->x;
			_hoops_HIHHA.y = points[_hoops_SPGIR].y - pivot->y;
		} _hoops_RGGA (_hoops_RRASA.x * _hoops_HIHHA.y >= _hoops_HIHHA.x * _hoops_RRASA.y);
	}

	return _hoops_AGASA (pivot, points, 0, _hoops_SPGIR, count, _hoops_CGASA);
}

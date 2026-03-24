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
 * $Id: obf_tmp.txt 1.42 2009-10-23 23:28:56 trask Exp $
 */

#include "hoops.h"
#include "driver.h"
#include "phdraw.h"
#include "hd_proto.h"
#include "hi_proto.h"

#ifndef DISABLE_DRAW_3D

struct _hoops_GRCCS {
	Net_Rendition		_hoops_APHGA;
	DC_Point const *	_hoops_PIICS;
	float				scale;
};



local void triangle_action (
	void alter *				_hoops_CAIGA,
	int							_hoops_HAPH,
	Point const *				p1,
	Point const *				p2,
	Point const *				_hoops_IAPH,
	Integer32					s1,
	Integer32					s2,
	Integer32					_hoops_CAPH,
	Intersection const *		i1,
	Intersection const *		i2,
	Intersection const *		_hoops_SAPH) {
	_hoops_GRCCS const *		_hoops_CRHCP = (_hoops_GRCCS const *)_hoops_CAIGA;
	DC_Point					points[3];

	UNREFERENCED (_hoops_HAPH);
	UNREFERENCED (s1);
	UNREFERENCED (s2);
	UNREFERENCED (_hoops_CAPH);
	UNREFERENCED (i1);
	UNREFERENCED (i2);
	UNREFERENCED (_hoops_SAPH);

	points[0].x = p1->x;
	points[0].y = p1->y;
	points[0].z = p1->z * _hoops_CRHCP->scale;

	points[1].x = p2->x;
	points[1].y = p2->y;
	points[1].z = p2->z * _hoops_CRHCP->scale;

	points[2].x = _hoops_IAPH->x;
	points[2].y = _hoops_IAPH->y;
	points[2].z = _hoops_IAPH->z * _hoops_CRHCP->scale;

	_hoops_RAPCP (_hoops_CRHCP->_hoops_APHGA, 3, points);
}

#endif


#define _hoops_SAIGA 15

GLOBAL_FUNCTION void HD_Std_DC_Face (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
#ifndef DISABLE_DRAW_3D
	int							_hoops_APIGA[_hoops_SAIGA + 1];
	int alter *					face_list;
	Point						_hoops_HIICS[_hoops_SAIGA];
	Point alter *				nice;
	int							index;
	_hoops_GRCCS				_hoops_CRHCP;
	float						scale;

	if (count < 3) return;

	if (count > _hoops_SAIGA) {
		ALLOC_ARRAY (face_list, count + 1, int);
		ALLOC_ARRAY (nice, count, Point);
	}
	else {
		face_list = _hoops_APIGA;
		nice = _hoops_HIICS;
	}

	scale = nr->_hoops_SRA->_hoops_PGCC._hoops_PRPSR.y /
			nr->transform_rendition->_hoops_PCHH;

	for (index = 0; index < count; ++index) {
		nice[index].x = points[index].x;
		nice[index].y = points[index].y;
		nice[index].z = points[index].z * scale;
	}

	face_list[0] = count;
	for (index = 0; index < count; ++index)
		face_list[index+1] = index;

	_hoops_CRHCP._hoops_PIICS = points;
	_hoops_CRHCP._hoops_APHGA = nr;
	_hoops_CRHCP.scale = 1.0f / scale;

	HI_Triangulate_Face_X (nice, null, face_list, face_list + count + 1,
						   triangle_action, (void alter *)&_hoops_CRHCP);

	if (count > _hoops_SAIGA) {
		FREE_ARRAY (face_list, count + 1, int);
		FREE_ARRAY (nice, count, Point);
	}
#endif
}

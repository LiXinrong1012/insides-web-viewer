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
 * $Id: obf_tmp.txt 1.184 2011-01-24 20:04:55 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "phedron.h"
#include "driver.h"
#include "phdraw.h"
#include "tandt.h"
#include "patterns.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"

#ifndef DISABLE_PARTIAL_ERASE

local RGBAS32 _hoops_RSHCP (
	Net_Rendition const &		nr,
	DC_Point const *			where) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	Int_Rectangle const *		extent = &_hoops_SGRA->_hoops_GAHIP;
	float						delta;
	RGBAS32						result;

	switch (_hoops_SGRA->_hoops_CGAIP) {
		case FP_WINDOW_GRADIENT_N:
			delta = (where->y - (float)extent->bottom) / (float)(extent->top - extent->bottom);
			break;
		case FP_WINDOW_GRADIENT_S:
			delta = ((float)extent->top - where->y) / (float)(extent->top - extent->bottom);
			break;
		case FP_WINDOW_GRADIENT_E:
			delta = (where->x - (float)extent->left) / (float)(extent->right - extent->left);
			break;
		case FP_WINDOW_GRADIENT_W:
			delta = ((float)extent->right - where->x) / (float)(extent->right - extent->left);
			break;

		case FP_WINDOW_GRADIENT_NE:
			delta = (where->y - (float)extent->bottom + where->x - (float)extent->left) /
					(float)(extent->top - extent->bottom + extent->right - extent->left);
			break;
		case FP_WINDOW_GRADIENT_NW:
			delta = (where->y - (float)extent->bottom + (float)extent->right - where->x) /
					(float)(extent->top - extent->bottom + extent->right - extent->left);
			break;
		case FP_WINDOW_GRADIENT_SE:
			delta = ((float)extent->top - where->y + where->x - (float)extent->left) /
					(float)(extent->top - extent->bottom + extent->right - extent->left);
			break;
		case FP_WINDOW_GRADIENT_SW:
			delta = ((float)extent->top - where->y + (float)extent->right - where->x) /
					(float)(extent->top - extent->bottom + extent->right - extent->left);
			break;

		default:
			delta = 0;	/* _hoops_CPS _hoops_SHS _hoops_SAHR _hoops_RAIA _hoops_RPPS _hoops_HAIR */
			break;
	}

	if (delta < 0.0f)
		delta = 0.0f;
	else if (delta > 1.0f)
		delta = 1.0f;

	result.r = dc->_hoops_ASHCP.color.r + (int)(delta * dc->_hoops_ASHCP._hoops_PSHCP.r);
	result.g = dc->_hoops_ASHCP.color.g + (int)(delta * dc->_hoops_ASHCP._hoops_PSHCP.g);
	result.b = dc->_hoops_ASHCP.color.b + (int)(delta * dc->_hoops_ASHCP._hoops_PSHCP.b);
	result.a = _hoops_GPGCR;

	return result;
}

local Driver_Color _hoops_HSHCP (
	Net_Rendition const &		nr,
	RGBAS32						_hoops_ISHCP) {
	Display_Context const *		dc = nr->_hoops_SRA;
	Driver_Color				color = _hoops_CAHSR::_hoops_SAHSR;

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
		color = _hoops_ISHCP;
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		_hoops_GARSR		colors[4+1];
		int				_hoops_AHHIR[3+1];

		/* _hoops_SGH "_hoops_AAH" _hoops_HAIR */
		(void)HD_Find_Dither_Pattern (nr, &_hoops_ISHCP, colors, _hoops_AHHIR);
		color._hoops_PGGCR = colors[0];
	}
	else /* _hoops_AIHHP */ {
		RGB				rgb = _hoops_ISHCP;

		color._hoops_PIHHP = (_hoops_HIHHP)(rgb._hoops_CPIR() * ((float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f));
	}

	return color;
}



local void interpolate_dc_polymarker (
	Net_Rendition const &		inr,
	int							count,
	DC_Point const *			points,
	float const *				rotations,
	float const *				size_fixups) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)inr->_hoops_SRA;
	_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_GSP.Modify();

	_hoops_IGRS (dc);
	while (count--) {
		/* _hoops_CSHCP _hoops_IPP _hoops_CGH _hoops_SHH _hoops_ICIC _hoops_HII _hoops_IASI _hoops_AHPIP, _hoops_HIH _hoops_CASI _hoops_PIAH _hoops_III _hoops_IPP */
		_hoops_CCP->color = _hoops_HSHCP (nr, _hoops_RSHCP (nr, points));
		_hoops_CCP->_hoops_SSHHP = null;
		_hoops_SSHCP (nr, 1, points, rotations, size_fixups);

		points++;
		if (rotations)
			rotations++;
	}
	_hoops_SGRS (dc);
}

local void _hoops_GGICP (
	Net_Rendition const &		inr,
	int							count,
	DC_Point const *			points) {
	Net_Rendition				nr = inr;
	Display_Context alter		*dc = (Display_Context alter *)inr->_hoops_SRA;
	Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_AHP.Modify();

	_hoops_IGRS (dc);
	while (count--) {
		/* _hoops_CSHCP _hoops_IPP _hoops_CGH _hoops_SHH _hoops_ICIC _hoops_HII _hoops_IASI _hoops_AHPIP, _hoops_HIH _hoops_CASI _hoops_PIAH _hoops_III _hoops_IPP */
		_hoops_HC->color = _hoops_HSHCP (nr, _hoops_RSHCP (nr, points));
		_hoops_AIGGA (nr, 1, points);

		points++;
	}
	_hoops_SGRS (dc);
}

local void _hoops_RGICP (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				_hoops_IASGR,
	bool						single) {

	UNREFERENCED (_hoops_IASGR);
	UNREFERENCED (single);

	_hoops_GGICP (nr, count, points);
}

local void _hoops_AGICP (
	Net_Rendition const & 		inr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				_hoops_PGICP) {
	Display_Context alter *		dc = (Display_Context alter *)inr->_hoops_SRA;
	Net_Rendition				nr = inr;
	Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_AHP.Modify();
	RGBAS32						colors[2];
	int							_hoops_RRC;

	UNREFERENCED (_hoops_PGICP);

	HD_Replace_Line_Style(_hoops_HC, nr->_hoops_GCSHP->_hoops_IHRIP);
	//_hoops_HGICP->_hoops_GGCS = _hoops_IRAP;

	_hoops_IGRS (dc);
	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		colors[0] = _hoops_RSHCP (nr, &points[0]);
		colors[1] = _hoops_RSHCP (nr, &points[1]);

		_hoops_ICGGA (nr, 2, points, colors);

		points += _hoops_RRC;
	}
	_hoops_SGRS (dc);
}


local void _hoops_IGICP (
	Net_Rendition const & 		inr,
	int							_hoops_ICGPA,
	DC_Point const *			_hoops_CGICP,
	RGBAS32 const *				_hoops_PGICP,
	bool						single) {
	Display_Context alter *		dc = (Display_Context alter *)inr->_hoops_SRA;
	Net_Rendition				nr = inr;
	int							_hoops_RRC;

	UNREFERENCED (_hoops_PGICP);	UNREFERENCED (single);

	if (!BIT(dc->_hoops_PGCC.flags, _hoops_SGICP)) {
		Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_AHP.Modify();
		int							count = _hoops_ICGPA;
		DC_Point const *			points = _hoops_CGICP;

		HD_Replace_Line_Style(_hoops_HC, nr->_hoops_GCSHP->_hoops_IHRIP);

		//_hoops_HGICP->_hoops_GGCS = _hoops_IRAP;

		_hoops_IGRS (dc);
		_hoops_ICHC (count, _hoops_RRC, 2);
		while (count-- > 0) {
			DC_Point			_hoops_SPGIR;

			_hoops_SPGIR.x = 0.5f * (points[0].x + points[1].x);
			_hoops_SPGIR.y = 0.5f * (points[0].y + points[1].y);
			_hoops_SPGIR.z = 0.5f * (points[0].z + points[1].z);

			/* _hoops_ICIC _hoops_IS _hoops_RPRS _hoops_IPP _hoops_CR _hoops_IASI _hoops_AHPIP _hoops_RGAR _hoops_RHAP _hoops_HGAI _hoops_ASCA. */
			_hoops_HC->color = _hoops_HSHCP (nr, _hoops_RSHCP (nr, &_hoops_SPGIR));
			_hoops_HC.Renew();

			_hoops_SCGGA (nr, 2, points);

			points += _hoops_RRC;
		}
		_hoops_SGRS (dc);
	}

	_hoops_AGICP (inr, _hoops_ICGPA, _hoops_CGICP, null);
}

local void _hoops_GRICP (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {

	_hoops_IGICP (nr, count, points, null, false);
}




local void _hoops_RRICP (
	Net_Rendition const &		nr,
	Polyedge const *			pe) {
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	int							point_count = pe->point_count;
	Polyedge					polyedge;
	int							index;
	int							_hoops_CRCAR;
	DC_Point alter *			_hoops_CGCAR;
	float alter *				ws;
	unsigned char alter *		_hoops_RRCAR;

	if (point_count == 0) {
		int const *				_hoops_AIHA = pe->_hoops_AIHA;
		int						length = pe->total;

		while (length-- > 0) {
			if ((index = *_hoops_AIHA++) > point_count)
				point_count = index;
		}

		/* _hoops_AGRP _hoops_CCAH _hoops_HSH _hoops_HII "_hoops_CIAS _hoops_CIHA" _hoops_IS "_hoops_PHI _hoops_IIGR _hoops_PSPI" */
		((Polyedge alter *)pe)->point_count = ++point_count;
	}



	ALLOC_ARRAY_ALIGNED (_hoops_CGCAR, point_count, DC_Point, 16);
	ALLOC_ARRAY_ALIGNED (ws, point_count, float, 16);
	ALLOC_ARRAY (_hoops_RRCAR, point_count, _hoops_GRCAR);
	_hoops_CRCAR = HD_Acquire_Clip_Points (nr, pe->bounding,
											pe->point_count, pe->points,
											_hoops_CGCAR, ws, _hoops_RRCAR);
	if (_hoops_CRCAR == 0) {
		FREE_ARRAY_ALIGNED (_hoops_CGCAR, point_count, DC_Point, 16);
		FREE_ARRAY_ALIGNED (ws, point_count, float, 16);
		FREE_ARRAY (_hoops_RRCAR, point_count, _hoops_GRCAR);
		return;
	}

	ZERO_STRUCT (&polyedge, Polyedge);
	polyedge._hoops_SRHA = _hoops_SRHH;
	polyedge.points = pe->points;
	polyedge.point_count = pe->point_count;
	polyedge._hoops_SPHA = pe->_hoops_SPHA;
	polyedge._hoops_PHHA = pe->_hoops_PHHA;
	polyedge.total = pe->total;
	polyedge.lengths = pe->lengths;
	polyedge._hoops_AIHA = pe->_hoops_AIHA;
	polyedge._hoops_SPII = pe->_hoops_SPII;
	polyedge._hoops_RPRCP = true;

	ALLOC_ARRAY (polyedge._hoops_PCHA, point_count, RGB);

	for (index=0; index<point_count; index++) {
		if (BIT (_hoops_RRCAR[index], _hoops_IPCAR))
			break;

		polyedge._hoops_PCHA[index] = _hoops_RSHCP (nr, &_hoops_CGCAR[index]);
	}


	if (index == point_count) { /* _hoops_HAPR _hoops_ASAS */
		_hoops_IGRS (dc);
		_hoops_IACIP (nr, &polyedge);
		_hoops_SGRS (dc);
	}
	else
		HD_Std_3D_Polyedge (nr, pe);


	FREE_ARRAY (polyedge._hoops_PCHA, point_count, RGB);
	FREE_ARRAY_ALIGNED (_hoops_CGCAR, point_count, DC_Point, 16);
	FREE_ARRAY_ALIGNED (ws, point_count, float, 16);
	FREE_ARRAY (_hoops_RRCAR, point_count, _hoops_GRCAR);
}

local void _hoops_ARICP (
	Net_Rendition const &		inr,
	Polyline const *			polyline) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	int							point_count = polyline->count;
	Polyedge					polyedge;
	DC_Point *					_hoops_CGCAR;
	float *						ws;
	_hoops_GRCAR *					_hoops_ARCAR;
	int							index;

	if (BIT(dc->_hoops_PGCC.flags, _hoops_SGICP) &&
		nr->_hoops_SAIR->_hoops_CGAIP >= FP_WINDOW_FIRST_GRADIENT &&
		nr->_hoops_SAIR->_hoops_CGAIP <= FP_WINDOW_LAST_GRADIENT) {
		if (nr->_hoops_RHP != nr->_hoops_AHP)
			nr.Modify()->_hoops_RHP = nr->_hoops_AHP;

		ALLOC_ARRAY_ALIGNED (_hoops_CGCAR, point_count, DC_Point, 16);
		ALLOC_ARRAY_ALIGNED (ws, point_count, float, 16);
		ALLOC_ARRAY (_hoops_ARCAR, point_count, _hoops_GRCAR);
		index = HD_Acquire_Clip_Points (nr, null,
										polyline->count,
										polyline->points,
										_hoops_CGCAR, ws, _hoops_ARCAR);

		ZERO_STRUCT (&polyedge, Polyedge);
		polyedge._hoops_SRHA = _hoops_SRHH;
		polyedge._hoops_CARI = _hoops_IPHS;
		if (polyline->type == _hoops_PIIP) {
			Line const *		line = (Line const *)polyline;

			polyedge.points = (Point *)line->points;
			polyedge.point_count = 2;
		}
		else {
			polyedge.points = polyline->points;
			polyedge.point_count = polyline->count;
		}
		polyedge._hoops_SPHA = polyedge.point_count-1;
		polyedge._hoops_PHHA = 1;
		polyedge.total = polyedge.point_count;
		polyedge.lengths = &polyedge.point_count;
		polyedge._hoops_RPRCP = true;

		ALLOC_ARRAY (polyedge._hoops_PCHA, point_count, RGB);
		ALLOC_ARRAY (polyedge._hoops_AIHA, point_count, int);

		for (index=0; index<point_count; index++) {
			if (BIT (_hoops_ARCAR[index], _hoops_IPCAR)) /* _hoops_HRGHP */
				break;

			polyedge._hoops_PCHA[index] = _hoops_RSHCP (nr, &_hoops_CGCAR[index]);
			polyedge._hoops_AIHA[index] = index;
		}


		if (index == point_count) { /* _hoops_HAPR _hoops_ASAS */
			_hoops_IGRS (dc);
			_hoops_IACIP (nr, &polyedge);
			_hoops_SGRS (dc);
		}
		else
			HD_Std_3D_Polyline (nr, polyline);


		FREE_ARRAY (polyedge._hoops_PCHA, point_count, RGB);
		FREE_ARRAY (polyedge._hoops_AIHA, point_count, int);

		FREE_ARRAY_ALIGNED (_hoops_CGCAR, point_count, DC_Point, 16);
		FREE_ARRAY_ALIGNED (ws, point_count, float, 16);
		FREE_ARRAY (_hoops_ARCAR, point_count, _hoops_GRCAR);
	}
	else {
		Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_AHP.Modify();

		_hoops_HC->color = nr->_hoops_SAIR->_hoops_GPIR;

		_hoops_IGRS (dc);
		HD_Std_3D_Polyline (nr, polyline);
		_hoops_SGRS (dc);
	}
}


local void _hoops_PRICP (
	Net_Rendition const & 		inr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				_hoops_PGICP) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	RGBAS32						colors[3];
	int							_hoops_RRC;

	UNREFERENCED (_hoops_PGICP);

	nr.Modify()->_hoops_IHA.Modify()->pattern = FP_SOLID;

	_hoops_IGRS (dc);
	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		colors[0] = _hoops_RSHCP (nr, &points[0]);
		colors[1] = _hoops_RSHCP (nr, &points[1]);
		colors[2] = _hoops_RSHCP (nr, &points[2]);
		_hoops_CCRGA (nr, 3, points, colors);

		points += _hoops_RRC;
	}
	_hoops_SGRS (dc);
}


local void _hoops_HRICP (
	Net_Rendition const & 		inr,
	int							_hoops_ICGPA,
	DC_Point const *			_hoops_CGICP,
	RGBAS32 const *				_hoops_PGICP,
	bool						single) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	int							_hoops_RRC;

	UNREFERENCED (_hoops_PGICP);	UNREFERENCED (single);

	if (!BIT(dc->_hoops_PGCC.flags, _hoops_SGICP)) {
		int							count = _hoops_ICGPA;
		DC_Point const *			points = _hoops_CGICP;

		_hoops_CIGA alter &		_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

		_hoops_SIGA->pattern = FP_SOLID;

		_hoops_IGRS (dc);
		_hoops_ICHC (count, _hoops_RRC, 3);
		while (count-- > 0) {
			DC_Point			_hoops_SPGIR;

			_hoops_SPGIR.x = 1.0f / 3.0f * (points[0].x + points[1].x + points[2].x);
			_hoops_SPGIR.y = 1.0f / 3.0f * (points[0].y + points[1].y + points[2].y);
			_hoops_SPGIR.z = 1.0f / 3.0f * (points[0].z + points[1].z + points[2].z);

			/* _hoops_ICIC _hoops_IS _hoops_RPRS _hoops_IPP _hoops_CR _hoops_IASI _hoops_AHPIP _hoops_RGAR _hoops_RHAP _hoops_HGAI _hoops_ASCA. */
			_hoops_SIGA->color = _hoops_HSHCP (nr, _hoops_RSHCP (nr, &_hoops_SPGIR));
			_hoops_SIGA.Renew();	/* _hoops_HIH _hoops_HPGGR _hoops_SCH _hoops_PII _hoops_CCAH */

			_hoops_GSRGA (nr, 3, points);

			points += _hoops_RRC;
		}
		_hoops_SGRS (dc);
	}

	_hoops_PRICP (inr, _hoops_ICGPA, _hoops_CGICP, null);
}

local void _hoops_IRICP (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {

	_hoops_HRICP (nr, count, points, null, false);
}



struct _hoops_CRICP {
	Net_Rendition		_hoops_APHGA;
	Tristrip			tristrip;
	int					lengths[1];
	int					_hoops_AIHA[3];
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
	_hoops_CRICP alter *		_hoops_CRHCP = (_hoops_CRICP alter *)_hoops_CAIGA;
	Point						points[3];

	UNREFERENCED (_hoops_HAPH);
	UNREFERENCED (s1);
	UNREFERENCED (s2);
	UNREFERENCED (_hoops_CAPH);
	UNREFERENCED (i1);
	UNREFERENCED (i2);
	UNREFERENCED (_hoops_SAPH);

	points[0].x = p1->x;
	points[0].y = p1->y;
	points[0].z = p1->z;

	points[1].x = p2->x;
	points[1].y = p2->y;
	points[1].z = p2->z;

	points[2].x = _hoops_IAPH->x;
	points[2].y = _hoops_IAPH->y;
	points[2].z = _hoops_IAPH->z;

	_hoops_CRHCP->tristrip.points = points;
	_hoops_RACIP (_hoops_CRHCP->_hoops_APHGA, &_hoops_CRHCP->tristrip);
}


#define _hoops_SAIGA 15

local void _hoops_SRICP (
	Net_Rendition const &		inr,
	Polygon const *				polygon) {
	Net_Rendition				nr = inr;
	int							_hoops_APIGA[_hoops_SAIGA + 1];
	int alter *					face_list = _hoops_APIGA;
	int							count = polygon->count;
	int							index;
	_hoops_CRICP				_hoops_CRHCP;
	Polyline					polyline;

	if (count < 3) return;

	if (count > _hoops_SAIGA)
		ALLOC_ARRAY (face_list, count + 1, int);

	face_list[0] = count;
	for (index = 0; index < count; ++index)
		face_list[index+1] = index;

	_hoops_CRHCP._hoops_APHGA = nr;

	ZERO_STRUCT (&_hoops_CRHCP.tristrip, Tristrip);
	_hoops_ICAI (&_hoops_CRHCP.tristrip);
	_hoops_CRHCP.tristrip._hoops_SRHA = _hoops_SRHH;
	_hoops_CRHCP.tristrip.point_count = 3;
	_hoops_CRHCP.tristrip.face_count = 1;
	_hoops_CRHCP.tristrip._hoops_PHHA = 1;
	_hoops_CRHCP.tristrip.total = 3;
	_hoops_CRHCP.tristrip.lengths = _hoops_CRHCP.lengths;
	_hoops_CRHCP.tristrip._hoops_AIHA = _hoops_CRHCP._hoops_AIHA;
	_hoops_CRHCP.tristrip.face_indices = null;
	_hoops_CRHCP.tristrip._hoops_RPRCP = true;

	_hoops_CRHCP.lengths[0] = 3;
	_hoops_CRHCP._hoops_AIHA[0] = 0;
	_hoops_CRHCP._hoops_AIHA[1] = 1;
	_hoops_CRHCP._hoops_AIHA[2] = 2;

	HI_Triangulate_Face_X (polygon->points, null, face_list, face_list + count + 1,
						   triangle_action, (void alter *)&_hoops_CRHCP);

	if (count > _hoops_SAIGA) {
		FREE_ARRAY (face_list, count + 1, int);
	}

	if (ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE)) {
		if (nr->_hoops_AHP != nr->_hoops_RHP)
			nr.Modify()->_hoops_AHP = nr->_hoops_RHP;
		ZERO_STRUCT(&polyline, Polyline);
		polyline.type = _hoops_IIIP;
		polyline.count = polygon->count + 1;
		ALLOC_ARRAY (polyline.points, polyline.count, Point);
		_hoops_AIGA (polygon->points, polygon->count, Point, polyline.points);
		_hoops_RSAI (polygon->points, Point, &polyline.points[polygon->count]);
		_hoops_ARICP (nr, &polyline);
		FREE_ARRAY (polyline.points, polyline.count, Point);
	}

	if (_hoops_CRHCP.tristrip._hoops_HSAI > 1)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR,
						   "Detected deferral of partial erase tristrip");
}


local void _hoops_GAICP (
	Net_Rendition const & 		inr,
	DC_Point const *			position,
	int							count,
	Karacter const *			kstring) {
	_hoops_IGCSR const &		_hoops_HRCIR = inr->_hoops_SISI;
	Display_Context alter *		dc = (Display_Context alter *)inr->_hoops_SRA;
	Font_Instance const *		font = inr->_hoops_SISI->font;
	DC_Point					point;
	float						width;

	point.x = position->x;
	point.y = position->y;
	point.z = position->z;

	_hoops_IGRS (dc);
	while (count-- > 0) {
		Net_Rendition			nr = inr;
		_hoops_IGCSR alter &	_hoops_IRRIP = nr.Modify()->_hoops_SISI.Modify();

		HD_Measure_Characters (inr, 1, kstring, font->encoding, &width);
		width *= inr->_hoops_SISI->width_scale;

		_hoops_IRRIP->color = _hoops_HSHCP (nr, _hoops_RSHCP (nr, &point));
		_hoops_IRRIP->_hoops_RGIHP = null;

		_hoops_RAICP (nr, &point, 1, kstring);

		point.x += _hoops_HRCIR->path.x * width;
		point.y += _hoops_HRCIR->path.y * width;
		point.z += _hoops_HRCIR->path.z * width;

		++kstring;
	}
	_hoops_SGRS (dc);
}


local void _hoops_AAICP (
	Net_Rendition const &		inr,
	Geometry const *			geometry,
	Driver_Color				background) {
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_GRGH const &		_hoops_PAICP = nr->_hoops_IRR;
	_hoops_ACHR					_hoops_RGP = inr->_hoops_RGP;

	do if (!BIT (geometry->_hoops_CPGPR, _hoops_CASIR)) {
		/* _hoops_HGCR _hoops_IASH _hoops_IIGR _hoops_GRR _hoops_CPAP _hoops_GPRR - _hoops_RIRRR _hoops_HII _hoops_PCSS */
		dc->_hoops_RAI = geometry;

		switch (geometry->type) {
			case _hoops_GHPGR: {
			}	break;

			case _hoops_ICIP: {
				/* _hoops_GGCH _hoops_SS -- _hoops_CCAC _hoops_SS _hoops_HPGR _hoops_CHGC _hoops_GRS _hoops_SHH _hoops_HAICP */
			}	break;

			case _hoops_SGCP:
			case _hoops_CGCP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
					if (nr->_hoops_IHA->color != background ||
						nr->_hoops_IHA->contrast_color != background) {
						_hoops_CIGA alter &		_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

						_hoops_SIGA->color = background;
						_hoops_SIGA->contrast_color = background;
					}
					if (nr->_hoops_RHP->color != background) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_RHP.Modify();

						_hoops_HC->color = background;
						//_hoops_HGICP->_hoops_GGCS = _hoops_IRAP;
					}

					_hoops_IAICP (nr, (Ellipse const *)geometry);
				}
			}	break;

			case _hoops_RIIP:
			case _hoops_GIIP: {
				if (BIT (_hoops_RGP, T_LINES)) {
					if (nr->_hoops_AHP->color != background) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_AHP.Modify();

						_hoops_HC->color = background;
						//_hoops_HGICP->_hoops_GGCS = _hoops_IRAP;
					}

					_hoops_CAICP (nr,
												(Elliptical_Arc const *)geometry);
				}
			}	break;

			case _hoops_GRCP:
			case _hoops_RRCP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
					if (nr->_hoops_IHA->color != background ||
						nr->_hoops_IHA->contrast_color != background) {
						_hoops_CIGA alter &		_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

						_hoops_SIGA->color = background;
						_hoops_SIGA->contrast_color = background;
					}
					if (nr->_hoops_RHP->color != background) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_RHP.Modify();

						_hoops_HC->color = background;
						//_hoops_HGICP->_hoops_GGCS = _hoops_IRAP;
					}

					_hoops_CAICP (nr,
												(Elliptical_Arc const *)geometry);
				}
			}	break;

			case _hoops_PIIP:
			case _hoops_HIIP:
			case _hoops_IIIP: {
				if (BIT (_hoops_RGP, T_LINES)) {
					if (nr->_hoops_AHP->color != background) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_AHP.Modify();

						_hoops_HC->color = background;
						//_hoops_HGICP->_hoops_GGCS = _hoops_IRAP;
					}

					_hoops_CCAIP (nr, (Polyline const *)geometry);
				}
			}	break;

			case _hoops_CHIP: {
				if (BIT (_hoops_RGP, T_LINES)) {
					if (nr->_hoops_AHP->color != background) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_AHP.Modify();

						_hoops_HC->color = background;
						//_hoops_HGICP->_hoops_GGCS = _hoops_IRAP;
					}

					_hoops_SAICP (nr, (_hoops_PIRGR alter *)geometry);
				}
			}	break;

			case _hoops_RCIP: {
				if (ANYBIT (_hoops_RGP, T_FACES|T_ANY_POLYGON_EDGE)) {
					if (nr->_hoops_IHA->color != background ||
						nr->_hoops_IHA->contrast_color != background) {
						_hoops_CIGA alter &		_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

						_hoops_SIGA->color = background;
						_hoops_SIGA->contrast_color = background;
					}
					if (nr->_hoops_RHP->color != background) {
						Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_RHP.Modify();

						_hoops_HC->color = background;
						//_hoops_HGICP->_hoops_GGCS = _hoops_IRAP;
					}

					_hoops_RCAIP (nr, (Polygon const *)geometry);
				}
			}	break;

			case _hoops_PCIP: {
				if (BIT (_hoops_RGP, T_MARKERS)) {
					if (nr->_hoops_GSP->color != background) {
						_hoops_ICP alter &		_hoops_CCP = nr.Modify()->_hoops_GSP.Modify();

						_hoops_CCP->color = background;
					}

					_hoops_GPICP (nr, (Marker const *)geometry);
				}
			}	break;

			case _hoops_PIRS: {
				if (BIT (_hoops_RGP, T_MARKERS)) {
					if (nr->_hoops_GSP->color != background) {
						_hoops_ICP alter &		_hoops_CCP = nr.Modify()->_hoops_GSP.Modify();

						_hoops_CCP->color = background;
					}

					_hoops_RPICP (nr, (_hoops_GRPGR const *)geometry);
				}
			}	break;

			case _hoops_AGCP: {
				if (BIT (_hoops_RGP, T_TEXT)) {
					_hoops_HACC const *		text = (_hoops_HACC const *)geometry;

					if (text->count != 0 ||
						text->_hoops_AAPGR != null) {
						if (nr->_hoops_SISI->color != background) {
							_hoops_IGCSR alter &		_hoops_HRCIR = nr.Modify()->_hoops_SISI.Modify();

							_hoops_HRCIR->color = background;
							_hoops_HRCIR->_hoops_RGIHP = null;
						}

						_hoops_APICP (nr, text);
					}
				}
			}	break;

			case _hoops_GGCP:
			case _hoops_GSIP:
			case _hoops_SCIP:
			case _hoops_PRCP:
			case _hoops_ASIP:
			case _hoops_CSIP:
			case _hoops_HSIP: {
				if (nr->_hoops_IHA->color != background ||
					nr->_hoops_IHA->contrast_color != background) {
					_hoops_CIGA alter &		_hoops_SIGA = nr.Modify()->_hoops_IHA.Modify();

					_hoops_SIGA->color = background;
					_hoops_SIGA->contrast_color = background;
				}
				if (nr->_hoops_RHP->color != background) {
					Line_Rendition alter &		_hoops_HC = nr.Modify()->_hoops_RHP.Modify();

					_hoops_HC->color = background;
					//_hoops_HGICP->_hoops_GGCS = _hoops_IRAP;
				}
				if (nr->_hoops_SCP->color != background) {
					_hoops_ICP alter &	_hoops_CCP = nr.Modify()->_hoops_SCP.Modify();

					_hoops_CCP->color = background;
				}

				if (nr->_hoops_IRR == _hoops_PAICP) {
					/* "_hoops_AAHS" _hoops_GGSR _hoops_IRGH _hoops_HSHRR/_hoops_RRCPR _hoops_PSHA */
					_hoops_GRGH alter &	_hoops_RRGH = nr.Modify()->_hoops_IRR.Modify();

					_hoops_RRGH->locks._hoops_IPPGR |= _hoops_GGCAA(HK_COLOR);
					_hoops_RRGH->locks.color = Color_EVERYTHING;
				}

				switch (geometry->type) {
					case _hoops_GGCP:
						_hoops_PPICP (nr, (Grid const *)geometry);
						break;
					case _hoops_GSIP:
					case _hoops_SCIP: {
						_hoops_CRCP *	_hoops_ARPGR;
						if ((_hoops_ARPGR = dc->_hoops_RAI->owner) != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(dc->_hoops_RIGC->thread_id);
						_hoops_HPICP (nr, (Polyhedron const *)geometry);
						if (_hoops_ARPGR != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
					} break;
					case _hoops_PRCP:
						_hoops_CRCP *	_hoops_ARPGR;
						if ((_hoops_ARPGR = dc->_hoops_RAI->owner) != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_PRPGR(dc->_hoops_RIGC->thread_id);
						_hoops_IPICP (nr, (_hoops_APPGR alter *)geometry);
						if (_hoops_ARPGR != null)
							_hoops_ARPGR->_hoops_RHAGR._hoops_IRPGR();
						break;
					case _hoops_ASIP:
						_hoops_CPICP (nr, (Cylinder const *)geometry);
						break;
					case _hoops_CSIP:
						_hoops_SPICP (nr, (PolyCylinder const *)geometry);
						break;
					case _hoops_HSIP:
						_hoops_GHICP (nr, (Sphere const *)geometry);
						break;
				}
			}	break;

			case _hoops_HGCP: {
				Image const *		image = (Image const *)geometry;
				float				_hoops_IACC, _hoops_CACC, _hoops_SACC;
				int					width, height;

				if (HD_Calc_Image_Position_And_Size (nr, image, &width, &height, &_hoops_IACC, &_hoops_CACC, &_hoops_SACC)) {
					Int_Rectangle const &	_hoops_GPHH = nr->transform_rendition->_hoops_AGAA;
					int							left, right, bottom, top;

					left = (int)(_hoops_IACC + 0.5f - image->width	 * 0.5f);
					top	 = (int)(_hoops_CACC + 0.5f + image->height * 0.5f);
					right = left + width - 1;
					bottom = top - height;

					if (left < _hoops_GPHH.left)
						left = _hoops_GPHH.left;
					if (right > _hoops_GPHH.right)
						right = _hoops_GPHH.right;
					if (bottom < _hoops_GPHH.bottom)
						bottom = _hoops_GPHH.bottom;
					if (top > _hoops_GPHH.top)
						top = _hoops_GPHH.top;

					if (left <= right && bottom <= top) {
						Net_Rendition				_hoops_RHICP = nr;
						_hoops_HHCR			_hoops_AHICP;
						DC_Point					box[4];

						_hoops_AHICP = _hoops_RHICP.Modify()->transform_rendition.Modify();

						_hoops_AHICP->_hoops_AGAA.left	= left;
						_hoops_AHICP->_hoops_AGAA.right	= right;
						_hoops_AHICP->_hoops_AGAA.bottom = bottom;
						_hoops_AHICP->_hoops_AGAA.top	= top;

						left -= 2;
						right += 2;
						bottom -= 2;
						top += 2;
						box[0].x = (float)left;
						box[0].y = (float)bottom;
						box[0].z = 0.0f;
						box[1].x = (float)right;
						box[1].y = (float)bottom;
						box[1].z = 0.0f;
						box[2].x = (float)left;
						box[2].y = (float)top;
						box[2].z = 0.0f;
						box[3].x = (float)right;
						box[3].y = (float)top;
						box[3].z = 0.0f;

						_hoops_IRICP (_hoops_RHICP, 3, &box[0]);
						_hoops_IRICP (_hoops_RHICP, 3, &box[1]);
					}
				}
			}	break;

			default: {
				_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, Sprintf_D (null,
									"'Partial erase' - unknown type '%d'",
									geometry->type));

				return;
			}	_hoops_HHHI;
		}
	} _hoops_RGGA ((geometry = geometry->next) == null);
	dc->_hoops_RAI = null;
}
#endif


local void _hoops_PHICP (
	Net_Rendition const &		inr,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_HICS const &		path,
	bool						_hoops_HGRHP) {
#ifndef DISABLE_PARTIAL_ERASE
	Display_Context alter *		dc = (Display_Context alter *)inr->_hoops_SRA;
	Net_Rendition				_hoops_ACRIP;

	{
		_hoops_SPAGR					_hoops_GHAGR (_hoops_SRCP->_hoops_RHAGR, dc->_hoops_RIGC->thread_id);
		_hoops_AHAGR *			_hoops_CSC = HI_Find_Segment_Cache (_hoops_SRCP, path);

		if (_hoops_CSC != null)
			_hoops_ACRIP = _hoops_CSC->_hoops_APHGA;
	}


#ifndef DISABLE_CALLBACKS
	if (true || BIT (HOOPS_WORLD->_hoops_HPSPP, _hoops_GHCPP)) {
		if (BIT(dc->flags, _hoops_HHICP)) {
			dc->flags &= ~_hoops_HHICP;
		}
		else if (_hoops_ACRIP != null) {
			_hoops_PSIHP	_hoops_HSIHP = _hoops_ACRIP->_hoops_RSGC;

			if (_hoops_HSIHP->action.draw_segment_tree != nullroutine ||
				_hoops_HSIHP->action.draw_segment != nullroutine) {
				Segment_Info alter	*si;

				ZALLOC (si, Segment_Info);
				si->segment = _hoops_SRCP;
				si->path = path;
				si->_hoops_IHICP = _hoops_HGRHP;

				si->next = (Segment_Info alter *)dc->_hoops_CHICP; /* _hoops_ICIC _hoops_HIIC */
				dc->_hoops_CHICP = si;

				dc->flags |= _hoops_HHICP;

				if (_hoops_HSIHP->action.draw_segment_tree != nullroutine) {
					_hoops_SCCHP		action = _hoops_HSIHP->action.draw_segment_tree;

					_hoops_HSIHP->action.draw_segment_tree = nullroutine; /* _hoops_ASSP'_hoops_RA _hoops_CAPGP */
					(*action) (&_hoops_ACRIP, si);
				}
				else
					_hoops_SHICP (_hoops_ACRIP, draw_segment) (&_hoops_ACRIP, si);

				if (dc->_hoops_CHICP != si) {
					do {
						Segment_Info const *	victim;

						if ((victim = dc->_hoops_CHICP) == null) {
							HE_ERROR (HEC_SEGMENT, HES_RENDITION_FREED, "Too many Renditions freed during a segment callback.");
							return;
						}
						dc->_hoops_CHICP = victim->next;
						victim->path.release();
						FREE (victim, Segment_Info);
					} _hoops_RGGA (dc->_hoops_CHICP == si);
					HE_ERROR (HEC_SEGMENT, HES_RENDITION_NOT_FREED, "New Renditions during a segment callback were not freed.");
				}

				dc->_hoops_CHICP = si->next;
				si->path.release();
				FREE (si, Segment_Info);
				dc->flags &= ~_hoops_HHICP;
				return;
			}
		}
	}
#endif

	/* _hoops_SPIC _hoops_ISHP _hoops_GGR _hoops_ARI _hoops_HCHAR _hoops_IH _hoops_CGSI _hoops_SGS _hoops_HS _hoops_RPII _hoops_PGHPR,
	 * _hoops_PPR _hoops_AIIAP _hoops_CAPR. */

	if (_hoops_ACRIP != null &&
		(_hoops_HGRHP && _hoops_SRCP->geometry != null || _hoops_SRCP->_hoops_SCGPR() != null)) {
		Driver_Color					background = _hoops_ACRIP->_hoops_SAIR->_hoops_GPIR;
		Net_Rendition					nr = _hoops_ACRIP;
		_hoops_CGRA alter &		_hoops_SGRA = nr->_hoops_SAIR;
		_hoops_HHCR alter &		_hoops_IHCR = nr.Modify()->transform_rendition.Modify();

		if (nr->_hoops_IHA->_hoops_AGP != null)
			nr->_hoops_IHA.Modify()->_hoops_AGP = null;
		if (nr->_hoops_RHP->_hoops_AGP != null)
			nr->_hoops_RHP.Modify()->_hoops_AGP = null;
		if (nr->_hoops_SCP->_hoops_AGP != null)
			nr->_hoops_SCP.Modify()->_hoops_AGP = null;
		_hoops_IHCR->flags &= ~_hoops_GRHH;

		_hoops_IHCR->_hoops_AGAA = _hoops_SGRA->_hoops_SCIH;
		_hoops_IHCR->_hoops_AGAA._hoops_IACHA(_hoops_SGRA->_hoops_RRAIP);

		/* _hoops_HHCI _hoops_RIPPR _hoops_AGSAR _hoops_CHR _hoops_SGSIP _hoops_GGGGR... */
		if (!BIT(_hoops_IHCR->heuristics, _hoops_HRIRP)) {
			if (_hoops_HGRHP && _hoops_SRCP->geometry != null)
				_hoops_AAICP (nr, _hoops_SRCP->geometry, background);

			if (_hoops_SRCP->_hoops_SCGPR() != null)
				_hoops_AAICP (nr, _hoops_SRCP->_hoops_SCGPR(), background);

			Subsegment const *		_hoops_SSGPR = _hoops_SRCP->_hoops_PRRPR();

			if (_hoops_SSGPR != null) do {
				_hoops_HICS		_hoops_HHPIP = path;
				_hoops_CRCP const *		_hoops_SIIS;

				if (_hoops_SSGPR->type == _hoops_AGRPR) {
					_hoops_PGRPR const *		include = (_hoops_PGRPR *)_hoops_SSGPR;

					_hoops_SIIS = (_hoops_CRCP const *)include->_hoops_IGRPR;
					_hoops_HHPIP._hoops_IACHA (include, dc);
				}
				else
					_hoops_SIIS = (_hoops_CRCP const *)_hoops_SSGPR;

				_hoops_PHICP (inr, _hoops_SIIS, _hoops_HHPIP, true);
			} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);
		}
	}


	if (_hoops_SRCP->_hoops_RGRPR != null) {
		Subsegment const *		_hoops_SSGPR = _hoops_SRCP->_hoops_RGRPR;

		do if (_hoops_HGRHP || BIT (_hoops_SSGPR->_hoops_CPGPR, _hoops_CPPGP)) {
			_hoops_HICS		_hoops_HHPIP = path;

			if (_hoops_SSGPR->type == _hoops_AGRPR) {
				_hoops_PGRPR const *		include = (_hoops_PGRPR *)_hoops_SSGPR;

				_hoops_SRCP = (_hoops_CRCP const *)include->_hoops_IGRPR;
				_hoops_HHPIP._hoops_IACHA (include, dc);
			}
			else
				_hoops_SRCP = (_hoops_CRCP const *)_hoops_SSGPR;


			/** ? _hoops_ISPR _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_SHH _hoops_IGSIP _hoops_HCR _hoops_IIGR _hoops_RGR _hoops_GIICP **/
			if (!BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CASIR) &&
				(!BIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR) ||
				 BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_CPPGP))) {
				/* _hoops_SPIC _hoops_CRGR _hoops_SCH */
				/** _hoops_ASRHR: _hoops_HAR _hoops_PSAS!! **/

				_hoops_PHICP (inr, _hoops_SRCP, _hoops_HHPIP,
										 _hoops_HGRHP || BIT (_hoops_SRCP->_hoops_CPGPR, _hoops_ICHPA));
			}
		} while ((_hoops_SSGPR = _hoops_SSGPR->next) != null);
	}
#endif
}


GLOBAL_FUNCTION void HD_Draw_Partial_Erase_Tree (
	Net_Rendition const &		inr,
	_hoops_CRCP const *				segment,
	_hoops_HICS const &		path,
	bool						_hoops_HGRHP) {
#ifndef DISABLE_PARTIAL_ERASE
	Net_Rendition				nr = inr;
	Display_Context alter *		dc = (Display_Context alter *)inr->_hoops_SRA;
	_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
	RGBAS32						_hoops_AIGCR, _hoops_PIGCR;
	_hoops_APARR				_hoops_RRCI;

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
		_hoops_AIGCR = _hoops_SGRA->_hoops_GPIR;
		_hoops_PIGCR = _hoops_SGRA->contrast_color;
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		RGB const	 *_hoops_SPRAR;

		_hoops_SPRAR = nr->_hoops_SRA->_hoops_CHHIP;

		_hoops_AIGCR = _hoops_SPRAR[_hoops_SGRA->_hoops_GPIR._hoops_PGGCR];
		_hoops_PIGCR = _hoops_SPRAR[_hoops_SGRA->contrast_color._hoops_PGGCR];
	}
	else /* _hoops_AIHHP */ {
		_hoops_AIGCR.r =
		 _hoops_AIGCR.g =
		  _hoops_AIGCR.b = (int)(255.99f *
						(_hoops_SGRA->_hoops_GPIR._hoops_PIHHP /
						 (float)(dc->_hoops_PGCC._hoops_PCHSR-1)));
		_hoops_PIGCR.r =
		 _hoops_PIGCR.g =
		  _hoops_PIGCR.b = (int)(255.99f *
						(_hoops_SGRA->contrast_color._hoops_PIHHP /
						 (float)(dc->_hoops_PGCC._hoops_PCHSR-1)));

		_hoops_AIGCR.a =
		 _hoops_PIGCR.a = _hoops_GPGCR;
	}
	dc->_hoops_ASHCP.color.r = (int)_hoops_AIGCR.r;
	dc->_hoops_ASHCP.color.g = (int)_hoops_AIGCR.g;
	dc->_hoops_ASHCP.color.b = (int)_hoops_AIGCR.b;
	dc->_hoops_ASHCP._hoops_PSHCP.r = (int)_hoops_PIGCR.r - dc->_hoops_ASHCP.color.r;
	dc->_hoops_ASHCP._hoops_PSHCP.g = (int)_hoops_PIGCR.g - dc->_hoops_ASHCP.color.g;
	dc->_hoops_ASHCP._hoops_PSHCP.b = (int)_hoops_PIGCR.b - dc->_hoops_ASHCP.color.b;


	_hoops_RRCI = _hoops_HGCGA (dc, "partial erase", nr);

	_hoops_RRCI->draw_dc_polymarker				= interpolate_dc_polymarker;

	_hoops_RRCI->draw_dc_polydot					= _hoops_GGICP;
	_hoops_RRCI->draw_dc_colorized_polydot		= _hoops_RGICP;

	_hoops_RRCI->draw_dc_polyline				= _hoops_GRICP;
	_hoops_RRCI->draw_dc_colorized_polyline		= _hoops_IGICP;
	_hoops_RRCI->draw_dc_gouraud_polyline		= _hoops_AGICP;

	_hoops_RRCI->draw_dc_polytriangle			= _hoops_IRICP;
	_hoops_RRCI->draw_dc_colorized_polytriangle	= _hoops_HRICP;
	_hoops_RRCI->draw_dc_gouraud_polytriangle	= _hoops_PRICP;

	_hoops_RRCI->draw_dc_text 					= _hoops_GAICP;
	_hoops_RRCI->draw_dc_face 					= HD_Std_DC_Face;
	_hoops_RRCI->_hoops_RPCGA					= HD_Std_DC_Polygon;

	_hoops_RRCI->draw_3d_marker					= HD_Std_3D_Marker;
	_hoops_RRCI->_hoops_RIICP				= HD_Std_3D_Multimarker;
	_hoops_RRCI->draw_3d_polymarker				= HD_Std_3D_Polymarker;

	_hoops_RRCI->draw_3d_polyline				= HD_Std_3D_Polyline;
	_hoops_RRCI->draw_3d_polyedge				= HD_Std_3D_Polyedge;
	_hoops_RRCI->draw_3d_polyedge_from_tristrip	= nullroutine;

	_hoops_RRCI->draw_3d_polygon					= HD_Std_3D_Polygon;
	_hoops_RRCI->draw_3d_tristrip				= HD_Std_3D_Tristrip;

	_hoops_RRCI->draw_3d_text					= HD_Std_3D_Text;

	_hoops_RRCI->draw_3d_cylinder				= HD_Std_3D_Cylinder;
	_hoops_RRCI->draw_3d_polycylinder			= HD_Std_3D_PolyCylinder;
	_hoops_RRCI->draw_3d_sphere					= HD_Std_3D_Sphere;


	_hoops_RRCI = _hoops_HGCGA (dc, "partial erase special 3d", nr);

	_hoops_RRCI->draw_3d_polyline		= _hoops_ARICP;
	_hoops_RRCI->draw_3d_polyedge		= _hoops_RRICP;

	_hoops_RRCI->draw_3d_polygon			= _hoops_SRICP;


	if (BIT(nr->transform_rendition->flags, _hoops_PASP)) {
		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

		_hoops_GGCC->flags &= ~_hoops_PASP;
		_hoops_GGCC->_hoops_GSCH[0] = _hoops_GGCC->_hoops_GSCH[1] = 0.0f;
	}


	dc->_hoops_CPIGA = true;
	_hoops_PHICP (nr, segment, path, _hoops_HGRHP);
	dc->_hoops_CPIGA = false;

	_hoops_HGSGA (dc, "partial erase special 3d");
	_hoops_HGSGA (dc, "partial erase");
#endif
}

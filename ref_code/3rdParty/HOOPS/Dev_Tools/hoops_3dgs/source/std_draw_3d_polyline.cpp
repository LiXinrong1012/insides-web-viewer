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
 * $Id: obf_tmp.txt 1.148 2010-10-29 00:49:05 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "tandt.h"
#include "hpserror.h"
#include "hd_proto.h"
#include "hc_proto.h"
#include "hi_proto.h"
#include "phedron.h"
#define _hoops_HGIRA 0.000001

#ifndef DISABLE_DRAW_3D
local void _hoops_HCRCS (
	Net_Rendition const & 		nr,
	int							count,
	DC_Point const *			points,
	bool						_hoops_ICRCS) {
	RGBAS32 alter *				colors;
	RGBA						_hoops_SGIIS;
	Point						_hoops_SSGGA;
	_hoops_RPRA const *			_hoops_APRA;
	int							i;
	float						_hoops_APCP;

	ALLOC_ARRAY (colors, Abs(count), RGBAS32);

	if (!BIT (nr->transform_rendition->flags, _hoops_IGCC))
		HD_Validate_World_To_Screen (nr);
	_hoops_APRA = nr->transform_rendition->_hoops_CGCC->_hoops_PPRA()->data.elements;

	i = 0;
	if (_hoops_ICRCS) {
		colors[i] = nr->_hoops_SAIR->_hoops_GRAIP;
		i++;
	}
	for (; i<Abs(count); i++) {
		_hoops_APCP = 1.0f / _hoops_PHCP (_hoops_APRA, points[i]);
		_hoops_SSGGA.x = _hoops_HPRA (_hoops_APRA, points[i]) * _hoops_APCP;
		_hoops_SSGGA.y = _hoops_IPRA (_hoops_APRA, points[i]) * _hoops_APCP;
		_hoops_SSGGA.z = _hoops_CPRA (_hoops_APRA, points[i]) * _hoops_APCP;

		_hoops_PC		_hoops_RRIIS;
		_hoops_ISACP (nr, _hoops_RRIIS,
							 nr->_hoops_AHP->_hoops_CHA,
							 &_hoops_SSGGA, null, null, null, null, 0, 0, &_hoops_SGIIS, null);

		colors[i] = _hoops_SGIIS;
	}

	_hoops_SSHGH (nr, count, points, colors);

	FREE_ARRAY(colors, Abs(count), RGBAS32);
}
#endif

GLOBAL_FUNCTION void HI_Glyph_Fixup_Polyline (
	Net_Rendition const &		nr,
	int							incount,
	DC_Point const *			_hoops_IRRAA) {
	Polyline *					pl;

	ZALLOC(pl, Polyline);
	pl->type = _hoops_IIIP;
	pl->_hoops_HIHI = 1;
	pl->count = incount;
	pl->allocated = Abs(incount);
	ALLOC_ARRAY_CACHED(pl->points,Abs(incount),Point);

	HI_Compute_Transformed_Points (Abs(incount), (Point *)_hoops_IRRAA,
									&nr->_hoops_SRA->_hoops_SAHGH->_hoops_APRA->data.elements[0][0],
									pl->points);

	_hoops_IGRS(nr->_hoops_SRA);

	_hoops_CPAGR(nr, pl);

	_hoops_SGRS(nr->_hoops_SRA);
	_hoops_HPRH(pl);
}

GLOBAL_FUNCTION void HI_Glyph_Fixup_Polygon (
	Net_Rendition const &		inr,
	int							incount,
	DC_Point const *			_hoops_IRRAA) {
	Polygon *					_hoops_RPIGA;
	Net_Rendition				nr = inr;

	ZALLOC(_hoops_RPIGA, Polygon);
	_hoops_RPIGA->type = _hoops_RCIP;
	_hoops_RPIGA->_hoops_HIHI = 1;
	_hoops_RPIGA->count = incount;
	_hoops_RPIGA->allocated = Abs(incount);
	ALLOC_ARRAY_CACHED(_hoops_RPIGA->points,Abs(incount),Point);

	HI_Compute_Transformed_Points (Abs(incount), (Point *)_hoops_IRRAA,
									&nr->_hoops_SRA->_hoops_SAHGH->_hoops_APRA->data.elements[0][0],
									_hoops_RPIGA->points);

	if (ANYBIT(nr->transform_rendition->flags,_hoops_GRHH | _hoops_PRIR))
		nr.Modify()->transform_rendition.Modify()->flags &= ~(_hoops_GRHH | _hoops_PRIR);

	_hoops_IGRS(nr->_hoops_SRA);

	_hoops_SGPGR(nr, _hoops_RPIGA);

	_hoops_SGRS(nr->_hoops_SRA);
	_hoops_HPRH(_hoops_RPIGA);
}

GLOBAL_FUNCTION void HI_Glyph_Fixup_Polydot (
	Net_Rendition const &		nr,
	int							incount,
	DC_Point const *			_hoops_IRRAA) {
	Polyline *					_hoops_RGHGS;
	Point *						_hoops_HAPAR;

	ZALLOC(_hoops_RGHGS, Polyline);
	_hoops_RGHGS->type = _hoops_IIIP;
	_hoops_RGHGS->_hoops_HIHI = 1;
	incount = Abs(incount);
	_hoops_RGHGS->count = -incount*2;
	_hoops_RGHGS->allocated = incount*2;
	ZALLOC_ARRAY_CACHED(_hoops_RGHGS->points,incount*2,Point);
	ALLOC_ARRAY_CACHED(_hoops_HAPAR,incount,Point);

	HI_Compute_Transformed_Points (incount, (Point *)_hoops_IRRAA,
									&nr->_hoops_SRA->_hoops_SAHGH->_hoops_APRA->data.elements[0][0],
									_hoops_HAPAR);

	int i;
	for (i=0; i<incount; i++) {
		int t = i*2;
		_hoops_RGHGS->points[t].x = _hoops_RGHGS->points[t+1].x = _hoops_HAPAR[i].x;
		_hoops_RGHGS->points[t].y = _hoops_RGHGS->points[t+1].y = _hoops_HAPAR[i].y;
		_hoops_RGHGS->points[t].z = _hoops_RGHGS->points[t+1].z = _hoops_HAPAR[i].z;
	}

	FREE_ARRAY(_hoops_HAPAR,incount,Point);

	_hoops_IGRS(nr->_hoops_SRA);

	_hoops_CPAGR(nr, _hoops_RGHGS);

	_hoops_SGRS(nr->_hoops_SRA);
	_hoops_HPRH(_hoops_RGHGS);
}

GLOBAL_FUNCTION void HI_Glyph_Fixup_Ellipse (
	Net_Rendition const &		inr,
	DC_Point const *			center,
	DC_Point const *			_hoops_HISIH) {
	Ellipse *					_hoops_IHHIR;
	Point						_hoops_CCRCS[2];
	Net_Rendition				nr = inr;

	ZALLOC(_hoops_IHHIR, Ellipse);
	_hoops_IHHIR->type = _hoops_CGCP;
	_hoops_IHHIR->_hoops_HIHI = 1;
	_hoops_IHHIR->_hoops_CPGPR = _hoops_PHSSR;

	_hoops_CCRCS[0].x = center->x + _hoops_HISIH->x;
	_hoops_CCRCS[0].y = center->y;
	_hoops_CCRCS[0].z = center->z;

	_hoops_CCRCS[1].x = center->x;
	_hoops_CCRCS[1].y = center->y + _hoops_HISIH->y;
	_hoops_CCRCS[1].z = center->z;

	HI_Compute_Transformed_Points (1, (Point *)center,
									&nr->_hoops_SRA->_hoops_SAHGH->_hoops_APRA->data.elements[0][0],
									&_hoops_IHHIR->center);
	HI_Compute_Transformed_Points (2, _hoops_CCRCS,
									&nr->_hoops_SRA->_hoops_SAHGH->_hoops_APRA->data.elements[0][0],
									_hoops_CCRCS);

	/* _hoops_HARGR 1 & 2 */
	_hoops_IHHIR->_hoops_GGHI.x = _hoops_CCRCS[0].x - _hoops_IHHIR->center.x;
	_hoops_IHHIR->_hoops_GGHI.y = _hoops_CCRCS[0].y - _hoops_IHHIR->center.y;
	_hoops_IHHIR->_hoops_GGHI.z = _hoops_CCRCS[0].z - _hoops_IHHIR->center.z;
	_hoops_IHHIR->_hoops_RGHI.x = _hoops_CCRCS[1].x - _hoops_IHHIR->center.x;
	_hoops_IHHIR->_hoops_RGHI.y = _hoops_CCRCS[1].y - _hoops_IHHIR->center.y;
	_hoops_IHHIR->_hoops_RGHI.z = _hoops_CCRCS[1].z - _hoops_IHHIR->center.z;

	/* _hoops_ARSSA & _hoops_CSSHH */
	_hoops_IHHIR->major.x = _hoops_CCRCS[0].x;
	_hoops_IHHIR->major.y = _hoops_CCRCS[0].y;
	_hoops_IHHIR->major.z = _hoops_CCRCS[0].z;
	_hoops_IHHIR->minor.x = _hoops_CCRCS[1].x;
	_hoops_IHHIR->minor.y = _hoops_CCRCS[1].y;
	_hoops_IHHIR->minor.z = _hoops_CCRCS[1].z;

	if (ANYBIT(nr->transform_rendition->flags,_hoops_GRHH | _hoops_PRIR))
		nr.Modify()->transform_rendition.Modify()->flags &= ~(_hoops_GRHH | _hoops_PRIR);

	_hoops_IGRS(nr->_hoops_SRA);

	_hoops_PCAIP(nr, _hoops_IHHIR);

	_hoops_SGRS(nr->_hoops_SRA);
	_hoops_HPRH(_hoops_IHHIR);
}

GLOBAL_FUNCTION void HI_Glyph_Fixup_Outline_Ellipse (
	Net_Rendition const &		nr,
	DC_Point const *			center,
	DC_Point const *			_hoops_HISIH) {
	Elliptical_Arc *			_hoops_ACAIP;
	Point						_hoops_CCRCS[2];

	ZALLOC(_hoops_ACAIP, Elliptical_Arc);
	_hoops_ACAIP->type = _hoops_GIIP;
	_hoops_ACAIP->_hoops_HIHI = 1;
	_hoops_ACAIP->_hoops_CPGPR = _hoops_PHSSR;

	_hoops_CCRCS[0].x = center->x + _hoops_HISIH->x;
	_hoops_CCRCS[0].y = center->y;
	_hoops_CCRCS[0].z = center->z;

	_hoops_CCRCS[1].x = center->x;
	_hoops_CCRCS[1].y = center->y + _hoops_HISIH->y;
	_hoops_CCRCS[1].z = center->z;

	HI_Compute_Transformed_Points (1, (Point *)center,
									&nr->_hoops_SRA->_hoops_SAHGH->_hoops_APRA->data.elements[0][0],
									&_hoops_ACAIP->center);
	HI_Compute_Transformed_Points (2, _hoops_CCRCS,
									&nr->_hoops_SRA->_hoops_SAHGH->_hoops_APRA->data.elements[0][0],
									_hoops_CCRCS);

	/* _hoops_HARGR 1 & 2 */
	_hoops_ACAIP->_hoops_GGHI.x = _hoops_CCRCS[0].x - _hoops_ACAIP->center.x;
	_hoops_ACAIP->_hoops_GGHI.y = _hoops_CCRCS[0].y - _hoops_ACAIP->center.y;
	_hoops_ACAIP->_hoops_GGHI.z = _hoops_CCRCS[0].z - _hoops_ACAIP->center.z;
	_hoops_ACAIP->_hoops_RGHI.x = _hoops_CCRCS[1].x - _hoops_ACAIP->center.x;
	_hoops_ACAIP->_hoops_RGHI.y = _hoops_CCRCS[1].y - _hoops_ACAIP->center.y;
	_hoops_ACAIP->_hoops_RGHI.z = _hoops_CCRCS[1].z - _hoops_ACAIP->center.z;

	/* _hoops_ARSSA & _hoops_CSSHH */
	_hoops_ACAIP->major.x = _hoops_CCRCS[0].x;
	_hoops_ACAIP->major.y = _hoops_CCRCS[0].y;
	_hoops_ACAIP->major.z = _hoops_CCRCS[0].z;
	_hoops_ACAIP->minor.x = _hoops_CCRCS[1].x;
	_hoops_ACAIP->minor.y = _hoops_CCRCS[1].y;
	_hoops_ACAIP->minor.z = _hoops_CCRCS[1].z;

	_hoops_ACAIP->arc_start	= 0.0f;
	_hoops_ACAIP->_hoops_PHHI		= 1.0f;

	_hoops_IGRS(nr->_hoops_SRA);

	_hoops_PPAGR(nr, _hoops_ACAIP);

	_hoops_SGRS(nr->_hoops_SRA);
	_hoops_HPRH(_hoops_ACAIP);
}

GLOBAL_FUNCTION void HI_Glyph_Fixup_Polytriangle (
	Net_Rendition const &		inr,
	int							incount,
	DC_Point const *			_hoops_IRRAA) {
	Net_Rendition				nr = inr;
	Tristrip *					ts;
	int							i;

	ZALLOC(ts, Tristrip);
	_hoops_ICAI (ts);
	ts->point_count = Abs(incount);
	ALLOC_ARRAY_ALIGNED_CACHED(ts->points,Abs(incount),Point,16);

	if (incount < 0) {
		ts->_hoops_PHHA = ts->lengths_allocated = -incount/3;
		ALLOC_ARRAY_CACHED(ts->lengths, ts->lengths_allocated, int);
		for (i=0; i<ts->lengths_allocated; i++)
			ts->lengths[i] = 3;
	}
	else {
		ts->_hoops_PHHA = ts->lengths_allocated = 1;
		ALLOC_ARRAY_CACHED(ts->lengths, ts->lengths_allocated, int);
		ts->lengths[0] = incount;
	}
	ts->total = ts->_hoops_IPII = ts->point_count;
	ALLOC_ARRAY_CACHED(ts->_hoops_AIHA, ts->_hoops_IPII, int);
	for (i=0; i<ts->point_count; i++)
		ts->_hoops_AIHA[i] = i;

	ts->_hoops_RAHH |= _hoops_AAHH | _hoops_AIPI;

	ts->_hoops_SRHA |= _hoops_GAHH | DL_TEMPORARY_DATA | _hoops_SRHH;

	HI_Compute_Transformed_Points (Abs(incount), (Point *)_hoops_IRRAA,
									&nr->_hoops_SRA->_hoops_SAHGH->_hoops_APRA->data.elements[0][0],
									ts->points);

	nr.Modify()->transform_rendition.Modify()->flags &= ~(_hoops_GRHH | _hoops_PRIR);

	_hoops_CIGA alter &	_hoops_CPIHP = nr->_hoops_IHA.Modify();
	_hoops_CPIHP->_hoops_CHA = _hoops_CPIHP->_hoops_GIA = nr->_hoops_AHP->_hoops_CHA;
	_hoops_CPIHP->_hoops_AGP = null;

	_hoops_IGRS(nr->_hoops_SRA);

	_hoops_RACIP(nr, ts);

	_hoops_SGRS(nr->_hoops_SRA);
	if (_hoops_ISAI (ts) == 0)
		HI_Free_Tristrip (ts);
}

GLOBAL_FUNCTION void HD_Setup_Line_Marker_Xform (
	Net_Rendition const &		inr,
	Polyline const *			pl,
	DC_Point alter *			_hoops_GHPCP,
	Marker const *				_hoops_GPIIH,
	_hoops_HRPA alter *			matrix) {
	Net_Rendition				nr = inr;
	Display_Context const *		dc = nr->_hoops_SRA;
	float scale = HD_Compute_Generic_Size (nr, 1.0, GSU_ORU, 1.0f, false, 0, true);
	HI_Ident_Matrix(matrix);

	if (pl && pl->type == _hoops_IIIP && pl->orientation) {
		if (BIT(pl->_hoops_RRHH, _hoops_HCPIR)) {
			Vector _hoops_SAIAR;
			HI_Cross_Product(&pl->orientation[1], &pl->orientation[0], &_hoops_SAIAR);
			matrix->elements[0][0] = _hoops_SAIAR.x;
			matrix->elements[1][0] = _hoops_SAIAR.y;
			matrix->elements[2][0] = _hoops_SAIAR.z;
			matrix->elements[0][1] = pl->orientation[1].x;
			matrix->elements[1][1] = pl->orientation[1].y;
			matrix->elements[2][1] = pl->orientation[1].z;
			matrix->elements[0][2] = pl->orientation[0].x;
			matrix->elements[1][2] = pl->orientation[0].y;
			matrix->elements[2][2] = pl->orientation[0].z;
		}
		else {
			float		_hoops_RPSSI, _hoops_RAHCR;
			Vector		axis, _hoops_GPSSI;

			axis.x = 0.0f;
			axis.y = 0.0f;
			axis.z = 1.0f;
			HI_Cross_Product (&axis, &pl->orientation[0], &_hoops_GPSSI);

			_hoops_RPSSI = (float)HI_Compute_Vector_Length (&_hoops_GPSSI);
			_hoops_RPSSI = _hoops_RPSSI*_hoops_RPSSI;
			if (_hoops_RPSSI < 1.0f)
				_hoops_RAHCR = _hoops_ISSSR (_hoops_SGIHR (1.0f - _hoops_RPSSI));
			else
				_hoops_RAHCR = 90.0f;
			if (_hoops_RAHCR != 0.0f) {
				HI_Compute_Offaxis_Rotation (_hoops_GPSSI.x, _hoops_GPSSI.y, _hoops_GPSSI.z, _hoops_RAHCR, (float *)matrix->elements);
			}

		}
		matrix->_hoops_RAGR |= _hoops_GRICR;
	}
	else if (_hoops_GPIIH && _hoops_GPIIH->orientation) {
		if (BIT(_hoops_GPIIH->_hoops_RRHH, _hoops_IHPIR)) {
			Vector _hoops_SAIAR;
			HI_Cross_Product(&_hoops_GPIIH->orientation[1], &_hoops_GPIIH->orientation[0], &_hoops_SAIAR);
			matrix->elements[0][0] = _hoops_SAIAR.x;
			matrix->elements[1][0] = _hoops_SAIAR.y;
			matrix->elements[2][0] = _hoops_SAIAR.z;
			matrix->elements[0][1] = _hoops_GPIIH->orientation[1].x;
			matrix->elements[1][1] = _hoops_GPIIH->orientation[1].y;
			matrix->elements[2][1] = _hoops_GPIIH->orientation[1].z;
			matrix->elements[0][2] = _hoops_GPIIH->orientation[0].x;
			matrix->elements[1][2] = _hoops_GPIIH->orientation[0].y;
			matrix->elements[2][2] = _hoops_GPIIH->orientation[0].z;
		}
		else {
			float		_hoops_RPSSI, _hoops_RAHCR;
			Vector		axis, _hoops_GPSSI;

			axis.x = 0.0f;
			axis.y = 0.0f;
			axis.z = 1.0f;
			HI_Cross_Product (&axis, &_hoops_GPIIH->orientation[0], &_hoops_GPSSI);

			_hoops_RPSSI = (float)HI_Compute_Vector_Length (&_hoops_GPSSI);
			_hoops_RPSSI = _hoops_RPSSI*_hoops_RPSSI;
			if (_hoops_RPSSI < 1.0f)
				_hoops_RAHCR = _hoops_ISSSR (_hoops_SGIHR (1.0f - _hoops_RPSSI));
			else
				_hoops_RAHCR = 90.0f;
			if (_hoops_RAHCR != 0.0f) {
				HI_Compute_Offaxis_Rotation (_hoops_GPSSI.x, _hoops_GPSSI.y, _hoops_GPSSI.z, _hoops_RAHCR, (float *)matrix->elements);
			}
		}
		matrix->_hoops_RAGR |= _hoops_GRICR;

	}
	matrix->elements[0][0] *= scale;
	matrix->elements[0][1] *= scale;
	matrix->elements[0][2] *= scale;
	matrix->elements[1][0] *= scale;
	matrix->elements[1][1] *= scale;
	matrix->elements[1][2] *= scale;
	matrix->elements[2][0] *= scale;
	matrix->elements[2][1] *= scale;
	matrix->elements[2][2] *= scale;
	matrix->_hoops_RAGR |= _hoops_CHCP;

	HI_Validate_Matrix_Adjoint(matrix);
	((Display_Context *)dc)->_hoops_SAHGH = matrix;

	if (pl) {
		if (pl->type == _hoops_PIIP) {
			Line const *		line = (Line const *)pl;
			HI_Compute_Transformed_Points(2, line->points, &matrix->elements[0][0], (Point *)_hoops_GHPCP);
		}
		else
			HI_Compute_Transformed_Points (Abs(pl->count), pl->points, &matrix->elements[0][0], (Point *)_hoops_GHPCP);
	}
	else if (_hoops_GPIIH)
		HI_Compute_Transformed_Points (1, &_hoops_GPIIH->_hoops_CSAI, &matrix->elements[0][0], (Point *)_hoops_GHPCP);

	_hoops_HGCGA(nr->_hoops_SRA, "transformable line patterns", nr);
	_hoops_APARR alter & _hoops_RRCI = (_hoops_APARR alter &)nr->_hoops_SRA->_hoops_IPCI;
	_hoops_RRCI->draw_dc_polyline = HI_Glyph_Fixup_Polyline;
	_hoops_RRCI->draw_dc_ellipse = HI_Glyph_Fixup_Ellipse;
	_hoops_RRCI->_hoops_SCISR = HI_Glyph_Fixup_Outline_Ellipse;
	_hoops_RRCI->draw_dc_face = HI_Glyph_Fixup_Polygon;
	_hoops_RRCI->draw_dc_polydot = HI_Glyph_Fixup_Polydot;
	_hoops_RRCI->draw_dc_polytriangle = HI_Glyph_Fixup_Polytriangle;
}

GLOBAL_FUNCTION void HD_Takedown_Line_Marker_Xform (Net_Rendition const & inr) {
	Display_Context const *		dc = inr->_hoops_SRA;
	_hoops_HGSGA(dc, "transformable line patterns");
	((Display_Context *)dc)->_hoops_SAHGH = null;
}

GLOBAL_FUNCTION void HD_Std_3D_Polyline (
	Net_Rendition const &		inr,
	Polyline const *			pl) {
#ifndef DISABLE_DRAW_3D
	Net_Rendition				nr = inr;
	Point const *				in;
	Point const *				end;
	DC_Point const *			_hoops_SCRCS;
	DC_Point const *			_hoops_GSRCS;
	DC_Point alter *			_hoops_GHPCP;
	float const *				_hoops_RSRCS;
	float alter*				ws;
	_hoops_GRCAR const *			_hoops_ASRCS;
	_hoops_GRCAR alter *			_hoops_ARCAR;
	DC_Point alter *			out_base;
	DC_Point alter *			_hoops_PAGR;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	float						_hoops_SRSAS = _hoops_IHCR->_hoops_GSCH[0] * nr->_hoops_SRA->_hoops_PGCC._hoops_PASHP;
	int							count, _hoops_CRCAR, _hoops_PIHS;
	bool						_hoops_PSRCS;
	int							_hoops_HSRCS;
	bool						_hoops_ISRCS;

	if (BIT(nr->_hoops_AHP->line_style->flags, _hoops_CRCAP) &&
		nr->_hoops_RSGC->action.draw_dc_polyline == nullroutine)
		return;

	if (pl->type == _hoops_HIIP && nr->_hoops_RSGC->action.draw_dc_polyline != nullroutine) {
		Display_Context alter *	dc = (Display_Context alter *)nr->_hoops_SRA;
		_hoops_SHRIR alter *		_hoops_GIRIR = (_hoops_SHRIR alter *)pl;
		Point const *			points = _hoops_GIRIR->points;
		int const *				mapping = _hoops_GIRIR->mapping;
		int						count = -_hoops_GIRIR->count / 2;

		while (count-- > 0) {
			Key				_hoops_CPCAS = HOOPS_WORLD->_hoops_GCHCA.table[*mapping++ & ~_hoops_RIRIR].key;
			Line *			line;

			ZALLOC (line, Line);
			line->type = _hoops_PIIP;
			line->_hoops_HIHI = 1;
			line->owner = pl->owner;
			line->key = _hoops_CPCAS;
			line->points[0] = *points++;
			line->points[1] = *points++;

			dc->_hoops_RAI = (Geometry *)line;
			HD_Std_3D_Polyline (nr, (Polyline *)line);

			_hoops_HPRH (line);
		}

		dc->_hoops_RAI = (Geometry *)pl;
		return;
	}


	if (pl->type == _hoops_PIIP) {
		Line const *	line = (Line const *)pl;

		_hoops_HSRCS = 2;
		in = line->points;
	}
	else {
		if ((_hoops_HSRCS = Abs(pl->count)) < 2)
			return;

		in = pl->points;
	}
	end = in + _hoops_HSRCS;


	if (nr->_hoops_AHP->weight < 0) {
		Line_Rendition alter &	_hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();

		_hoops_ASGIP->weight = HD_Compute_Generic_Size (nr, _hoops_ASGIP->_hoops_PHP, _hoops_ASGIP->_hoops_HHP, 1.0f, false, 0, true) + 0.5f;

		if (_hoops_ASGIP->_hoops_HHP != GSU_PIXELS && _hoops_ASGIP->_hoops_HHP != GSU_PERCENT && _hoops_ASGIP->_hoops_HHP != GSU_SCALE)
			_hoops_ASGIP->flags |= _hoops_SSGIP;
	}

	_hoops_PSRCS = BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH);


	POOL_ALLOC_ARRAY_CACHED (_hoops_PAGR, _hoops_HSRCS, DC_Point, nr->_hoops_SRA->memory_pool);
	POOL_ALLOC_ARRAY_ALIGNED_CACHED (_hoops_GHPCP, _hoops_HSRCS, DC_Point, 16, nr->_hoops_SRA->memory_pool);
	POOL_ALLOC_ARRAY_ALIGNED_CACHED (ws, _hoops_HSRCS, float, 16, nr->_hoops_SRA->memory_pool);
	POOL_ALLOC_ARRAY_CACHED (_hoops_ARCAR, _hoops_HSRCS, _hoops_GRCAR, nr->_hoops_SRA->memory_pool);
	out_base = _hoops_PAGR;
	_hoops_GSRCS = _hoops_GHPCP;
	_hoops_RSRCS  = ws;
	_hoops_ASRCS  = _hoops_ARCAR;

	if (BIT(nr->_hoops_AHP->line_style->flags, _hoops_PRCAP)) {
		_hoops_HRPA		matrix;
		HD_Setup_Line_Marker_Xform(nr, pl, _hoops_GHPCP, 0, &matrix);
		HD_Std_DC_Polyline(nr, _hoops_HSRCS, _hoops_GHPCP);
		HD_Takedown_Line_Marker_Xform(nr);
		goto _hoops_HPAGR;
	}

	_hoops_CRCAR = HD_Acquire_Clip_Points (nr, null, _hoops_HSRCS, in, _hoops_GHPCP, ws, _hoops_ARCAR);

	if (!ANYBIT (nr->_hoops_AHP->line_style->flags,
		_hoops_PRCAP|LSF_OFFSET|LSF_WEIGHT|_hoops_RHISA|LSF_GLYPHS) &&
		_hoops_CRCAR == 0)
		goto _hoops_HPAGR;

#define _hoops_HRIIS(_hoops_CSRCS, _hoops_PAGR)	\
	do {						\
		(_hoops_PAGR)->x = (_hoops_CSRCS)->x;	\
		(_hoops_PAGR)->y = (_hoops_CSRCS)->y;	\
		(_hoops_PAGR)->z = (_hoops_CSRCS)->z;	\
	} while (0)


	_hoops_SCRCS = 0;

	count = _hoops_HSRCS;

	_hoops_ISRCS = false;

	while (count--) {
		if (BIT (*_hoops_ARCAR, _hoops_IPCAR)) {
			if (_hoops_ISRCS) {
				float			_hoops_PRSAS, _hoops_HRSAS;
				float			trim;
				float			_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

				_hoops_HRIIS (_hoops_GHPCP, _hoops_PAGR);

				_hoops_PRSAS = ws[-1];
				_hoops_HRSAS = ws[0];

				trim = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_HRSAS - _hoops_PRSAS);

				_hoops_PAGR[0].x = (_hoops_PRSAS*_hoops_PAGR[-1].x + (_hoops_PAGR[0].x - _hoops_PRSAS*_hoops_PAGR[-1].x) * trim) * _hoops_PASAS;
				_hoops_PAGR[0].y = (_hoops_PRSAS*_hoops_PAGR[-1].y + (_hoops_PAGR[0].y - _hoops_PRSAS*_hoops_PAGR[-1].y) * trim) * _hoops_PASAS;
				_hoops_PAGR[0].z = _hoops_SRSAS;
				_hoops_PAGR++;

				/* _hoops_ASIGA _hoops_ASSI _hoops_RSGR _hoops_RPHH */

				if (_hoops_HSRCS > 0) {

					_hoops_PIHS = _hoops_PAGR-out_base;

					if (_hoops_PSRCS)
						_hoops_HCRCS (nr, _hoops_PIHS, out_base, false);
					else
						_hoops_SRPIP (nr, _hoops_PIHS, out_base);

					_hoops_PAGR = out_base;
					_hoops_ISRCS = false;
				}
			}

			_hoops_SCRCS = _hoops_GHPCP;
		}
		else if (_hoops_SCRCS) {
			float			_hoops_PRSAS, _hoops_HRSAS;
			float			trim;
			float			_hoops_PASAS = 1.0f / _hoops_IHCR->_hoops_CHCR;

			_hoops_HRIIS (_hoops_SCRCS, _hoops_PAGR);
			_hoops_PAGR++;

			_hoops_HRIIS (_hoops_GHPCP, _hoops_PAGR);

			_hoops_PRSAS = *ws;
			_hoops_HRSAS = _hoops_RSRCS[_hoops_SCRCS - _hoops_GSRCS];

			trim = (_hoops_IHCR->_hoops_CHCR - _hoops_PRSAS) / (_hoops_HRSAS - _hoops_PRSAS);

			_hoops_PAGR[-1].x = (_hoops_PRSAS*_hoops_PAGR[0].x + (_hoops_PAGR[-1].x - _hoops_PRSAS*_hoops_PAGR[0].x) * trim) * _hoops_PASAS;
			_hoops_PAGR[-1].y = (_hoops_PRSAS*_hoops_PAGR[0].y + (_hoops_PAGR[-1].y - _hoops_PRSAS*_hoops_PAGR[0].y) * trim) * _hoops_PASAS;
			_hoops_PAGR[-1].z = _hoops_SRSAS;
			_hoops_PAGR++;

			/* _hoops_ASIGA _hoops_ASSI _hoops_HSPP _hoops_RPHH */
			_hoops_SCRCS = 0;
			_hoops_ISRCS = true;
		}
		else {
			_hoops_HRIIS (_hoops_GHPCP, _hoops_PAGR);
			_hoops_PAGR++;
			_hoops_ISRCS = true;
		}

		_hoops_GHPCP++;
		ws++;
		_hoops_ARCAR++;

		if (pl->type != _hoops_PIIP && pl->count < 0 && !(count & 0x1)) {
			_hoops_SCRCS = 0;
			_hoops_ISRCS = false;
		}
	}

	_hoops_PIHS = _hoops_PAGR - out_base;

	if (pl->type != _hoops_PIIP && pl->count < 0)
		_hoops_PIHS = -_hoops_PIHS;

	if (_hoops_PAGR != out_base) {
		if (_hoops_PSRCS)
			_hoops_HCRCS (nr, _hoops_PIHS, out_base, false);
		else
			_hoops_SRPIP (nr, _hoops_PIHS, out_base);
	}


  _hoops_HPAGR:
	FREE_ARRAY (out_base, _hoops_HSRCS, DC_Point);
	FREE_ARRAY_ALIGNED (_hoops_GSRCS, _hoops_HSRCS, DC_Point, 16);
	FREE_ARRAY_ALIGNED (_hoops_RSRCS, _hoops_HSRCS, float, 16);
	FREE_ARRAY (_hoops_ASRCS, _hoops_HSRCS, _hoops_GRCAR);
#endif
}

enum { _hoops_HRASA, _hoops_IRASA, _hoops_SSRCS, _hoops_GGACS, _hoops_RGACS};

GLOBAL_FUNCTION void HD_Std_3D_Infinite_Line (
	Net_Rendition const & 		inr,
	Polyline const *			pl) {
#ifndef DISABLE_DRAW_3D
	Net_Rendition		 		nr = inr;
	_hoops_HHCR alter &	_hoops_IHCR = nr.Modify()->transform_rendition.Modify();
	_hoops_HHRA const *				_hoops_SPH = _hoops_IHCR->_hoops_SPH;
	int							_hoops_AGACS, _hoops_PGACS, _hoops_HGACS, _hoops_IGACS,
								_hoops_CGACS, _hoops_SGACS;
	bool						_hoops_PSRCS;
	Point						_hoops_IIPCR, _hoops_GRACS, _hoops_RRACS,
								_hoops_ARACS, _hoops_PRACS, _hoops_HRACS,
								*_hoops_RIRSH, _hoops_IRACS, _hoops_CRACS;
	float						_hoops_SRACS = 0.0f, _hoops_GAACS = 0.0f;
	int							ortho, _hoops_RAACS = 0, _hoops_AAACS = 0, _hoops_PAACS = 0, _hoops_HAACS = 0, _hoops_IAACS = 0;
	Point						_hoops_CAACS[3], _hoops_SAACS[3], _hoops_GPACS[3], _hoops_RPACS[3], _hoops_APACS[3], _hoops_PPACS[3];
	float						_hoops_SSHGA, _hoops_HPACS, _hoops_IPACS, H, T, _hoops_CPGAP, _hoops_CPACS, _hoops_SPACS;
	_hoops_ARPA						_hoops_GHACS, _hoops_RHACS, _hoops_AHACS, _hoops_PHACS, _hoops_HHACS, _hoops_IHACS;
	int							_hoops_CHACS[5];
	int							_hoops_SHACS = 0;


	ZERO_ARRAY(_hoops_CHACS, 5, int);

	if (pl->count < 2) return;

	if (nr->transform_rendition->_hoops_SPH->projection == _hoops_CPPCR)
		ortho = true;
	else
		ortho = false;

	/* _hoops_HIHP _hoops_RH _hoops_RSSA _hoops_RHIR _hoops_RH _hoops_SICH, _hoops_PSCR _hoops_HIAP _hoops_RH _hoops_SICH _hoops_IS _hoops_SRGH
	   _hoops_HIS _hoops_SGS _hoops_RH _hoops_RSSA _hoops_GA'_hoops_RA _hoops_HGCR _hoops_GIACS _hoops_SGGR _hoops_HII _hoops_RH _hoops_SPPR _hoops_IIGR _hoops_RH _hoops_RAR _hoops_CHRA */
	HI_Transform_Points_43(1, &pl->points[0], (const float*)_hoops_IHCR->_hoops_IPH->data.elements, &_hoops_IRACS);
	HI_Transform_Points_43(1, &pl->points[1], (const float*)_hoops_IHCR->_hoops_IPH->data.elements, &_hoops_CRACS);

	/*	_hoops_SR _hoops_RRP _hoops_IS _hoops_ARP _hoops_GH _hoops_IRS _hoops_CCAH _hoops_IPP _hoops_PGGA _hoops_SR _hoops_CHR _hoops_RRPRA _hoops_RH _hoops_GCHRR _hoops_PRGIA _hoops_RSGA _hoops_ARI _hoops_RIIA _hoops_IIGR _hoops_GGR _hoops_RH
		3D/_hoops_SHCA _hoops_III _hoops_ASCA _hoops_RRGR _hoops_SPHR _hoops_GPP */

	_hoops_IHCR->_hoops_IPH = _hoops_SGCC::Create (nr->_hoops_SRA);


	/* _hoops_RGR _hoops_ASAR-_hoops_RIACS _hoops_RH _hoops_CPSP->_hoops_RSGA */
	HD_Downwind_Camera (nr, (Attribute *)_hoops_IHCR->_hoops_SPH);


	if (nr->_hoops_AHP->weight < 0) {
		Line_Rendition alter &		_hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();

		_hoops_ASGIP->weight = HD_Compute_Generic_Size (nr, _hoops_ASGIP->_hoops_PHP, _hoops_ASGIP->_hoops_HHP, 1.0f, false, 0, true) + 0.5f;
	}

	_hoops_PSRCS = BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH);

	ALLOC_ARRAY_ALIGNED (_hoops_RIRSH, 4, Point, 16);


	_hoops_IIPCR.x = -1.0f*(_hoops_SPH->target.x - _hoops_SPH->position.x);
	_hoops_IIPCR.y = -1.0f*(_hoops_SPH->target.y - _hoops_SPH->position.y);
	_hoops_IIPCR.z = -1.0f*(_hoops_SPH->target.z - _hoops_SPH->position.z);

	_hoops_CPACS = _hoops_SPACS = 1.0f;
	if (_hoops_SPH->projection != _hoops_SSIH) {
		_hoops_CGRA const &		_hoops_SGRA = nr->_hoops_SAIR;

		if (_hoops_SPH->_hoops_CSIH > _hoops_SGRA->_hoops_CSIH)
			_hoops_CPACS = _hoops_SPH->_hoops_CSIH / _hoops_SGRA->_hoops_CSIH;
		else
			_hoops_SPACS = _hoops_SGRA->_hoops_CSIH / _hoops_SPH->_hoops_CSIH;
	}

	_hoops_CPACS *= 0.5f * _hoops_SPH->_hoops_ISPA;
	_hoops_SPACS *= 0.5f * _hoops_SPH->_hoops_SSPA;

	/* _hoops_PRPC _hoops_RAAP _hoops_RPIA */
	_hoops_RIRSH[0].x = _hoops_SPH->target.x + _hoops_CPACS*_hoops_SPH->_hoops_CRSS.x - _hoops_SPACS*_hoops_SPH->up_vector.x;
	_hoops_RIRSH[0].y = _hoops_SPH->target.y + _hoops_CPACS*_hoops_SPH->_hoops_CRSS.y - _hoops_SPACS*_hoops_SPH->up_vector.y;
	_hoops_RIRSH[0].z = _hoops_SPH->target.z + _hoops_CPACS*_hoops_SPH->_hoops_CRSS.z - _hoops_SPACS*_hoops_SPH->up_vector.z;

	/* _hoops_SCIA _hoops_RAAP _hoops_RPIA */
	_hoops_RIRSH[1].x = _hoops_SPH->target.x + _hoops_CPACS*_hoops_SPH->_hoops_CRSS.x + _hoops_SPACS*_hoops_SPH->up_vector.x;
	_hoops_RIRSH[1].y = _hoops_SPH->target.y + _hoops_CPACS*_hoops_SPH->_hoops_CRSS.y + _hoops_SPACS*_hoops_SPH->up_vector.y;
	_hoops_RIRSH[1].z = _hoops_SPH->target.z + _hoops_CPACS*_hoops_SPH->_hoops_CRSS.z + _hoops_SPACS*_hoops_SPH->up_vector.z;

	/* _hoops_SCIA _hoops_RPHR _hoops_RPIA */
	_hoops_RIRSH[2].x = _hoops_SPH->target.x - _hoops_CPACS*_hoops_SPH->_hoops_CRSS.x + _hoops_SPACS*_hoops_SPH->up_vector.x;
	_hoops_RIRSH[2].y = _hoops_SPH->target.y - _hoops_CPACS*_hoops_SPH->_hoops_CRSS.y + _hoops_SPACS*_hoops_SPH->up_vector.y;
	_hoops_RIRSH[2].z = _hoops_SPH->target.z - _hoops_CPACS*_hoops_SPH->_hoops_CRSS.z + _hoops_SPACS*_hoops_SPH->up_vector.z;

	/* _hoops_PRPC _hoops_RPHR _hoops_RPIA */
	_hoops_RIRSH[3].x = _hoops_SPH->target.x - _hoops_CPACS*_hoops_SPH->_hoops_CRSS.x - _hoops_SPACS*_hoops_SPH->up_vector.x;
	_hoops_RIRSH[3].y = _hoops_SPH->target.y - _hoops_CPACS*_hoops_SPH->_hoops_CRSS.y - _hoops_SPACS*_hoops_SPH->up_vector.y;
	_hoops_RIRSH[3].z = _hoops_SPH->target.z - _hoops_CPACS*_hoops_SPH->_hoops_CRSS.z - _hoops_SPACS*_hoops_SPH->up_vector.z;


#ifdef HOOPS_DEBUG_BUILD
	/* _hoops_PGSA _hoops_SHPR _hoops_PHGSP */
	if (0) {
		Polyline *		_hoops_AIACS;
		ZALLOC(_hoops_AIACS, Polyline);
		_hoops_AIACS->type = _hoops_IIIP;
		_hoops_AIACS->_hoops_HIHI = 1;
		_hoops_AIACS->allocated = 4;
		_hoops_AIACS->count = 4;
		ALLOC_ARRAY(_hoops_AIACS->points, 4, Point);
		_hoops_AIGA(_hoops_RIRSH, 4, Point, _hoops_AIACS->points);
		_hoops_CCAIP(nr, _hoops_AIACS);
		_hoops_HPRH(_hoops_AIACS);
	}
#endif

	/* _hoops_ARP _hoops_GH _hoops_RH _hoops_RAAP _hoops_CHRA _hoops_IPPA */
	_hoops_CAACS[0].x = _hoops_SPH->position.x;
	_hoops_CAACS[0].y = _hoops_SPH->position.y;
	_hoops_CAACS[0].z = _hoops_SPH->position.z;

	_hoops_CAACS[1].x = _hoops_RIRSH[0].x; /* _hoops_PRPC _hoops_RAAP */
	_hoops_CAACS[1].y = _hoops_RIRSH[0].y;
	_hoops_CAACS[1].z = _hoops_RIRSH[0].z;

	_hoops_CAACS[2].x = _hoops_RIRSH[1].x; /* _hoops_SCIA _hoops_RAAP */
	_hoops_CAACS[2].y = _hoops_RIRSH[1].y;
	_hoops_CAACS[2].z = _hoops_RIRSH[1].z;

	if (ortho) {
		_hoops_CAACS[0].x =  _hoops_CAACS[1].x + _hoops_SPH->_hoops_IIPCR.x;
		_hoops_CAACS[0].y =  _hoops_CAACS[1].y + _hoops_SPH->_hoops_IIPCR.y;
		_hoops_CAACS[0].z =  _hoops_CAACS[1].z + _hoops_SPH->_hoops_IIPCR.z;
	}

	/* _hoops_ARP _hoops_GH _hoops_RH _hoops_RPHR _hoops_CHRA _hoops_IPPA */
	_hoops_SAACS[0].x = _hoops_SPH->position.x;
	_hoops_SAACS[0].y = _hoops_SPH->position.y;
	_hoops_SAACS[0].z = _hoops_SPH->position.z;

	_hoops_SAACS[1].x = _hoops_RIRSH[2].x; /* _hoops_SCIA _hoops_RPHR */
	_hoops_SAACS[1].y = _hoops_RIRSH[2].y;
	_hoops_SAACS[1].z = _hoops_RIRSH[2].z;

	_hoops_SAACS[2].x = _hoops_RIRSH[3].x; /* _hoops_PRPC _hoops_RPHR */
	_hoops_SAACS[2].y = _hoops_RIRSH[3].y;
	_hoops_SAACS[2].z = _hoops_RIRSH[3].z;

	if (ortho) {
		_hoops_SAACS[0].x =  _hoops_SAACS[1].x + _hoops_SPH->_hoops_IIPCR.x;
		_hoops_SAACS[0].y =  _hoops_SAACS[1].y + _hoops_SPH->_hoops_IIPCR.y;
		_hoops_SAACS[0].z =  _hoops_SAACS[1].z + _hoops_SPH->_hoops_IIPCR.z;
	}

	/* _hoops_ARP _hoops_GH _hoops_RH _hoops_SCIA _hoops_CHRA _hoops_IPPA */
	_hoops_GPACS[0].x = _hoops_SPH->position.x;
	_hoops_GPACS[0].y = _hoops_SPH->position.y;
	_hoops_GPACS[0].z = _hoops_SPH->position.z;

	_hoops_GPACS[1].x = _hoops_RIRSH[1].x; /* _hoops_SCIA _hoops_RAAP */
	_hoops_GPACS[1].y = _hoops_RIRSH[1].y;
	_hoops_GPACS[1].z = _hoops_RIRSH[1].z;

	_hoops_GPACS[2].x = _hoops_RIRSH[2].x; /* _hoops_SCIA _hoops_RPHR */
	_hoops_GPACS[2].y = _hoops_RIRSH[2].y;
	_hoops_GPACS[2].z = _hoops_RIRSH[2].z;

	if (ortho) {
		_hoops_GPACS[0].x =  _hoops_GPACS[1].x + _hoops_SPH->_hoops_IIPCR.x;
		_hoops_GPACS[0].y =  _hoops_GPACS[1].y + _hoops_SPH->_hoops_IIPCR.y;
		_hoops_GPACS[0].z =  _hoops_GPACS[1].z + _hoops_SPH->_hoops_IIPCR.z;
	}

	/* _hoops_ARP _hoops_GH _hoops_RH _hoops_PRPC _hoops_CHRA _hoops_IPPA */
	_hoops_RPACS[0].x = _hoops_SPH->position.x;
	_hoops_RPACS[0].y = _hoops_SPH->position.y;
	_hoops_RPACS[0].z = _hoops_SPH->position.z;

	_hoops_RPACS[1].x = _hoops_RIRSH[0].x; /* _hoops_PRPC _hoops_RAAP */
	_hoops_RPACS[1].y = _hoops_RIRSH[0].y;
	_hoops_RPACS[1].z = _hoops_RIRSH[0].z;

	_hoops_RPACS[2].x = _hoops_RIRSH[3].x; /* _hoops_PRPC _hoops_RPHR */
	_hoops_RPACS[2].y = _hoops_RIRSH[3].y;
	_hoops_RPACS[2].z = _hoops_RIRSH[3].z;

	if (ortho) {
		_hoops_RPACS[0].x =  _hoops_RPACS[1].x + _hoops_SPH->_hoops_IIPCR.x;
		_hoops_RPACS[0].y =  _hoops_RPACS[1].y + _hoops_SPH->_hoops_IIPCR.y;
		_hoops_RPACS[0].z =  _hoops_RPACS[1].z + _hoops_SPH->_hoops_IIPCR.z;
	}

	/* _hoops_ARP _hoops_GH _hoops_RH _hoops_APAP _hoops_CHRA _hoops_IPPA */
	if (0) {
		_hoops_APACS[0].x = _hoops_RIRSH[0].x; /* _hoops_PRPC _hoops_RAAP */
		_hoops_APACS[0].y = _hoops_RIRSH[0].y;
		_hoops_APACS[0].z = _hoops_RIRSH[0].z;

		_hoops_APACS[1].x = _hoops_RIRSH[1].x; /* _hoops_SCIA _hoops_RAAP */
		_hoops_APACS[1].y = _hoops_RIRSH[1].y;
		_hoops_APACS[1].z = _hoops_RIRSH[1].z;

		_hoops_APACS[2].x = _hoops_RIRSH[2].x; /* _hoops_SCIA _hoops_RPHR */
		_hoops_APACS[2].y = _hoops_RIRSH[2].y;
		_hoops_APACS[2].z = _hoops_RIRSH[2].z;
	}
	else {
		_hoops_APACS[0].x = _hoops_SPH->position.x + _hoops_IHCR->_hoops_CHCR*(_hoops_RIRSH[0].x - _hoops_SPH->position.x);
		_hoops_APACS[0].y = _hoops_SPH->position.y + _hoops_IHCR->_hoops_CHCR*(_hoops_RIRSH[0].y - _hoops_SPH->position.y);
		_hoops_APACS[0].z = _hoops_SPH->position.z + _hoops_IHCR->_hoops_CHCR*(_hoops_RIRSH[0].z - _hoops_SPH->position.z);

		_hoops_APACS[1].x = _hoops_SPH->position.x + _hoops_SPH->_hoops_CRSS.x + _hoops_IHCR->_hoops_CHCR*(_hoops_RIRSH[1].x - (_hoops_SPH->position.x + _hoops_SPH->_hoops_CRSS.x));
		_hoops_APACS[1].y = _hoops_SPH->position.y + _hoops_SPH->_hoops_CRSS.y + _hoops_IHCR->_hoops_CHCR*(_hoops_RIRSH[1].y - (_hoops_SPH->position.y + _hoops_SPH->_hoops_CRSS.y));
		_hoops_APACS[1].z = _hoops_SPH->position.z + _hoops_SPH->_hoops_CRSS.z + _hoops_IHCR->_hoops_CHCR*(_hoops_RIRSH[1].z - (_hoops_SPH->position.z + _hoops_SPH->_hoops_CRSS.z));

		_hoops_APACS[2].x = _hoops_SPH->position.x + _hoops_SPH->up_vector.x + _hoops_IHCR->_hoops_CHCR*(_hoops_RIRSH[2].x - (_hoops_SPH->position.x + _hoops_SPH->up_vector.x));
		_hoops_APACS[2].y = _hoops_SPH->position.y + _hoops_SPH->up_vector.y + _hoops_IHCR->_hoops_CHCR*(_hoops_RIRSH[2].y - (_hoops_SPH->position.y + _hoops_SPH->up_vector.y));
		_hoops_APACS[2].z = _hoops_SPH->position.z + _hoops_SPH->up_vector.z + _hoops_IHCR->_hoops_CHCR*(_hoops_RIRSH[2].z - (_hoops_SPH->position.z + _hoops_SPH->up_vector.z));
	}

	_hoops_PPACS[0].x = _hoops_SPH->position.x;
	_hoops_PPACS[0].y = _hoops_SPH->position.y;
	_hoops_PPACS[0].z = _hoops_SPH->position.z;

	_hoops_PPACS[1].x = _hoops_SPH->position.x + _hoops_SPH->_hoops_CRSS.x;
	_hoops_PPACS[1].y = _hoops_SPH->position.y + _hoops_SPH->_hoops_CRSS.y;
	_hoops_PPACS[1].z = _hoops_SPH->position.z + _hoops_SPH->_hoops_CRSS.z;

	_hoops_PPACS[2].x = _hoops_SPH->position.x + _hoops_SPH->up_vector.x;
	_hoops_PPACS[2].y = _hoops_SPH->position.y + _hoops_SPH->up_vector.y;
	_hoops_PPACS[2].z = _hoops_SPH->position.z + _hoops_SPH->up_vector.z;


	HI_Figure_Plane_From_Points(3, _hoops_CAACS, &_hoops_GHACS);
	HI_Figure_Plane_From_Points(3, _hoops_SAACS, &_hoops_RHACS);
	HI_Figure_Plane_From_Points(3, _hoops_GPACS, &_hoops_AHACS);
	HI_Figure_Plane_From_Points(3, _hoops_RPACS, &_hoops_PHACS);
	HI_Figure_Plane_From_Points(3, _hoops_APACS, &_hoops_HHACS);
	HI_Figure_Plane_From_Points(3, _hoops_PPACS, &_hoops_IHACS);


	_hoops_HPACS = _hoops_CRACS.x - _hoops_IRACS.x;
	_hoops_IPACS = _hoops_CRACS.y - _hoops_IRACS.y;
	H = _hoops_CRACS.z - _hoops_IRACS.z;

	_hoops_AGACS = 0;
	_hoops_PGACS = 0;
	_hoops_HGACS = 0;
	_hoops_IGACS = 0;
	_hoops_CGACS = -1;
	_hoops_SGACS = -1;

	/* _hoops_HSPC _hoops_HCR _hoops_RH _hoops_SGSSR _hoops_HSH _hoops_ARPP _hoops_SHRAA _hoops_CAPR _hoops_GGR */
	_hoops_GRACS.x = 0; _hoops_GRACS.y = 0; _hoops_GRACS.z = 0;
	_hoops_RRACS.x = 0; _hoops_RRACS.y = 0; _hoops_RRACS.z = 0;
	_hoops_ARACS.x = 0; _hoops_ARACS.y = 0; _hoops_ARACS.z = 0;
	_hoops_PRACS.x = 0; _hoops_PRACS.y = 0; _hoops_PRACS.z = 0;
	_hoops_HRACS.x = 0; _hoops_HRACS.y = 0; _hoops_HRACS.z = 0;

	/* _hoops_RAAP _hoops_SGSSR */
	_hoops_SSHGA = _hoops_GHACS.a * _hoops_HPACS + _hoops_GHACS.b * _hoops_IPACS + _hoops_GHACS.c * H;
	if (Abs(_hoops_SSHGA) < _hoops_HGIRA) {
		/* _hoops_GGAIA */
		_hoops_RAACS = 1;
	}
	else {
		T = -(_hoops_GHACS.a * _hoops_IRACS.x + _hoops_GHACS.b * _hoops_IRACS.y + _hoops_GHACS.c * _hoops_IRACS.z + _hoops_GHACS.d)/_hoops_SSHGA;
		_hoops_GRACS.x = _hoops_IRACS.x + _hoops_HPACS * T;
		_hoops_GRACS.y = _hoops_IRACS.y + _hoops_IPACS * T;
		_hoops_GRACS.z = _hoops_IRACS.z + H * T;

		if ( T > 0 ) {
			_hoops_CHACS[_hoops_HRASA] = 1;
			_hoops_SHACS++;
		}

		_hoops_SSHGA = _hoops_IHACS.a * _hoops_IHACS.a + _hoops_IHACS.b * _hoops_IHACS.b + _hoops_IHACS.c * _hoops_IHACS.c;
		if (_hoops_SSHGA < _hoops_HGIRA) {
			/* _hoops_AHCI _hoops_IPPA _hoops_PIACS */
		}
		else {
			_hoops_CPGAP = _hoops_IHACS.a * _hoops_GRACS.x + _hoops_IHACS.b * _hoops_GRACS.y + _hoops_IHACS.c * _hoops_GRACS.z + _hoops_IHACS.d;
			if (_hoops_CPGAP < _hoops_HGIRA)
				_hoops_AGACS++;
			else {
				_hoops_HGACS++;
				_hoops_CGACS = 1;
			}
		}

	}

	/* _hoops_RPHR _hoops_SGSSR */
	_hoops_SSHGA = _hoops_RHACS.a * _hoops_HPACS + _hoops_RHACS.b * _hoops_IPACS + _hoops_RHACS.c * H;
	if (Abs(_hoops_SSHGA) < _hoops_HGIRA) {
		/* _hoops_GGAIA */
		_hoops_AAACS = 1;
	}
	else {
		T = -(_hoops_RHACS.a * _hoops_IRACS.x + _hoops_RHACS.b * _hoops_IRACS.y + _hoops_RHACS.c * _hoops_IRACS.z + _hoops_RHACS.d)/_hoops_SSHGA;
		_hoops_RRACS.x = _hoops_IRACS.x + _hoops_HPACS * T;
		_hoops_RRACS.y = _hoops_IRACS.y + _hoops_IPACS * T;
		_hoops_RRACS.z = _hoops_IRACS.z + H * T;

		if ( T > 0 ) {
			_hoops_CHACS[_hoops_IRASA] = 1;
			_hoops_SHACS++;
		}

		_hoops_SSHGA = _hoops_IHACS.a * _hoops_IHACS.a + _hoops_IHACS.b * _hoops_IHACS.b + _hoops_IHACS.c * _hoops_IHACS.c;
		if (_hoops_SSHGA < _hoops_HGIRA) {
			/* _hoops_AHCI _hoops_IPPA _hoops_PIACS */
		}
		else {
			_hoops_CPGAP = _hoops_IHACS.a * _hoops_RRACS.x + _hoops_IHACS.b * _hoops_RRACS.y + _hoops_IHACS.c * _hoops_RRACS.z + _hoops_IHACS.d;
			if (_hoops_CPGAP < _hoops_HGIRA)
				_hoops_AGACS++;
			else {
				_hoops_HGACS++;
				_hoops_CGACS = 0;
			}
		}
	}

	/* _hoops_SCIA _hoops_SGSSR */
	_hoops_SSHGA = _hoops_AHACS.a * _hoops_HPACS + _hoops_AHACS.b * _hoops_IPACS + _hoops_AHACS.c * H;
	if (Abs(_hoops_SSHGA) < _hoops_HGIRA) {
		/* _hoops_GGAIA */
		_hoops_PAACS = 1;
	}
	else {
		T = -(_hoops_AHACS.a * _hoops_IRACS.x + _hoops_AHACS.b * _hoops_IRACS.y + _hoops_AHACS.c * _hoops_IRACS.z + _hoops_AHACS.d)/_hoops_SSHGA;
		_hoops_ARACS.x = _hoops_IRACS.x + _hoops_HPACS * T;
		_hoops_ARACS.y = _hoops_IRACS.y + _hoops_IPACS * T;
		_hoops_ARACS.z = _hoops_IRACS.z + H * T;

		if ( T > 0 ) {
			_hoops_CHACS[_hoops_SSRCS] = 1;
			_hoops_SHACS++;
		}

		_hoops_SSHGA = _hoops_IHACS.a * _hoops_IHACS.a + _hoops_IHACS.b * _hoops_IHACS.b + _hoops_IHACS.c * _hoops_IHACS.c;
		if (_hoops_SSHGA < _hoops_HGIRA) {
			/* _hoops_AHCI _hoops_IPPA _hoops_PIACS */
		}
		else {
			_hoops_CPGAP = _hoops_IHACS.a * _hoops_ARACS.x + _hoops_IHACS.b * _hoops_ARACS.y + _hoops_IHACS.c * _hoops_ARACS.z + _hoops_IHACS.d;
			if (_hoops_CPGAP < _hoops_HGIRA)
				_hoops_PGACS++;
			else {
				_hoops_IGACS++;
				_hoops_SGACS = 1;
			}
		}
	}

	/* _hoops_HIACS _hoops_SGSSR */
	_hoops_SSHGA = _hoops_PHACS.a * _hoops_HPACS + _hoops_PHACS.b * _hoops_IPACS + _hoops_PHACS.c * H;
	if (Abs(_hoops_SSHGA) < _hoops_HGIRA) {
		/* _hoops_GGAIA */
		_hoops_HAACS = 1;
	}
	else {
		T = -(_hoops_PHACS.a * _hoops_IRACS.x + _hoops_PHACS.b * _hoops_IRACS.y + _hoops_PHACS.c * _hoops_IRACS.z + _hoops_PHACS.d)/_hoops_SSHGA;
		_hoops_PRACS.x = _hoops_IRACS.x + _hoops_HPACS * T;
		_hoops_PRACS.y = _hoops_IRACS.y + _hoops_IPACS * T;
		_hoops_PRACS.z = _hoops_IRACS.z + H * T;

		if ( T > 0 ) {
			_hoops_CHACS[_hoops_GGACS] = 1;
			_hoops_SHACS++;
		}

		_hoops_SSHGA = _hoops_IHACS.a * _hoops_IHACS.a + _hoops_IHACS.b * _hoops_IHACS.b + _hoops_IHACS.c * _hoops_IHACS.c;
		if (_hoops_SSHGA < _hoops_HGIRA) {
			/* _hoops_AHCI _hoops_IPPA _hoops_PIACS */
		}
		else {
			_hoops_CPGAP = _hoops_IHACS.a * _hoops_PRACS.x + _hoops_IHACS.b * _hoops_PRACS.y + _hoops_IHACS.c * _hoops_PRACS.z + _hoops_IHACS.d;
			if (_hoops_CPGAP < _hoops_HGIRA)
				_hoops_PGACS++;
			else {
				_hoops_IGACS++;
				_hoops_SGACS = 0;
			}
		}
	}

	/* _hoops_APAP _hoops_SGSSR */
	_hoops_SSHGA = _hoops_HHACS.a * _hoops_HPACS + _hoops_HHACS.b * _hoops_IPACS + _hoops_HHACS.c * H;
	if (Abs(_hoops_SSHGA) < _hoops_HGIRA) {
		/* _hoops_GGAIA */
		_hoops_IAACS = 1;
	}
	else {
		T = -(_hoops_HHACS.a * _hoops_IRACS.x + _hoops_HHACS.b * _hoops_IRACS.y + _hoops_HHACS.c * _hoops_IRACS.z + _hoops_HHACS.d)/_hoops_SSHGA;
		_hoops_HRACS.x = _hoops_IRACS.x + _hoops_HPACS * T;
		_hoops_HRACS.y = _hoops_IRACS.y + _hoops_IPACS * T;
		_hoops_HRACS.z = _hoops_IRACS.z + H * T;

		if ( T > 0 ) {
			_hoops_CHACS[_hoops_RGACS] = 1;
			_hoops_SHACS++;
		}
	}

	_hoops_SRACS = _hoops_SGIHR((_hoops_ARACS.x - _hoops_PRACS.x) * (_hoops_ARACS.x - _hoops_PRACS.x) +
					(_hoops_ARACS.y - _hoops_PRACS.y) * (_hoops_ARACS.y - _hoops_PRACS.y) +
					(_hoops_ARACS.z - _hoops_PRACS.z) * (_hoops_ARACS.z - _hoops_PRACS.z));

	_hoops_GAACS = _hoops_SGIHR((_hoops_RRACS.x - _hoops_GRACS.x) * (_hoops_RRACS.x - _hoops_GRACS.x) +
					(_hoops_RRACS.y - _hoops_GRACS.y) * (_hoops_RRACS.y - _hoops_GRACS.y) +
					(_hoops_RRACS.z - _hoops_GRACS.z) * (_hoops_RRACS.z - _hoops_GRACS.z));

	if (_hoops_IGACS == 2 && _hoops_HGACS == 2 || _hoops_PGACS == 2 && _hoops_AGACS == 2 || ortho) {
		if (_hoops_AAACS && _hoops_RAACS ||
			_hoops_SRACS < _hoops_GAACS && _hoops_SRACS != 0.0 ||
			Abs(_hoops_GAACS) <= _hoops_HGIRA) {
			/*_hoops_RPP (_hoops_IIACS < _hoops_CIACS) {*/
			Polyline *		_hoops_AIACS;

			ZALLOC(_hoops_AIACS, Polyline);
			_hoops_AIACS->_hoops_HIHI = 1;
			_hoops_AIACS->type = _hoops_IIIP;
			_hoops_AIACS->allocated = 2;
			_hoops_AIACS->count = 2;
			ZALLOC_ARRAY(_hoops_AIACS->points, 2, Point);
			if (BIT(pl->_hoops_RRHH, _hoops_IHHCA)) {
				if (_hoops_CHACS[_hoops_SSRCS] && _hoops_CHACS[_hoops_GGACS]) {
					_hoops_AIGA(&_hoops_ARACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_PRACS, 3, float, _hoops_AIACS->points+1);
				}
				else if (_hoops_CHACS[_hoops_SSRCS]) {
					_hoops_AIGA(&_hoops_ARACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
				}
				else if (_hoops_CHACS[_hoops_GGACS]) {
					_hoops_AIGA(&_hoops_PRACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
				}
				else if (_hoops_CHACS[_hoops_HRASA] && _hoops_CHACS[_hoops_IRASA]) {
					_hoops_AIGA(&_hoops_GRACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_RRACS, 3, float, _hoops_AIACS->points+1);
				}
				else if (_hoops_CHACS[_hoops_HRASA]) {
					_hoops_AIGA(&_hoops_GRACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
				}
				else if (_hoops_CHACS[_hoops_IRASA]) {
					_hoops_AIGA(&_hoops_RRACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
				}
			}
			else{
				_hoops_AIGA(&_hoops_ARACS, 3, float, _hoops_AIACS->points);
				_hoops_AIGA(&_hoops_PRACS, 3, float, _hoops_AIACS->points+1);
			}
			_hoops_CCAIP(nr, _hoops_AIACS);
			_hoops_HPRH(_hoops_AIACS);
		}
		else {
			Polyline *		_hoops_AIACS;

			ZALLOC(_hoops_AIACS, Polyline);
			_hoops_AIACS->_hoops_HIHI = 1;
			_hoops_AIACS->type = _hoops_IIIP;
			_hoops_AIACS->allocated = 2;
			_hoops_AIACS->count = 2;
			ZALLOC_ARRAY(_hoops_AIACS->points, 2, Point);
			if (BIT(pl->_hoops_RRHH, _hoops_IHHCA)) {
				if (_hoops_CHACS[_hoops_HRASA] && _hoops_CHACS[_hoops_IRASA]) {
					_hoops_AIGA(&_hoops_GRACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_RRACS, 3, float, _hoops_AIACS->points+1);
				}
				else if (_hoops_CHACS[_hoops_HRASA]) {
					_hoops_AIGA(&_hoops_GRACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
				}
				else if (_hoops_CHACS[_hoops_IRASA]) {
					_hoops_AIGA(&_hoops_RRACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
				}
				else if (_hoops_CHACS[_hoops_SSRCS] && _hoops_CHACS[_hoops_GGACS]) {
					_hoops_AIGA(&_hoops_ARACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_PRACS, 3, float, _hoops_AIACS->points+1);
				}
				else if (_hoops_CHACS[_hoops_SSRCS]) {
					_hoops_AIGA(&_hoops_ARACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
				}
				else if (_hoops_CHACS[_hoops_GGACS]) {
					_hoops_AIGA(&_hoops_PRACS, 3, float, _hoops_AIACS->points);
					_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
				}
			}
			else{
				_hoops_AIGA(&_hoops_GRACS, 3, float, _hoops_AIACS->points);
				_hoops_AIGA(&_hoops_RRACS, 3, float, _hoops_AIACS->points+1);
			}
			_hoops_CCAIP(nr, _hoops_AIACS);
			_hoops_HPRH(_hoops_AIACS);
		}
	}
	else if (_hoops_IGACS == 2 /* || _hoops_SIACS == 2*/ ) {
		Polyline *		_hoops_AIACS;

		ZALLOC(_hoops_AIACS, Polyline);
		_hoops_AIACS->_hoops_HIHI = 1;
		_hoops_AIACS->type = _hoops_IIIP;
		_hoops_AIACS->allocated = 2;
		_hoops_AIACS->count = 2;
		ZALLOC_ARRAY(_hoops_AIACS->points, 2, Point);
		if (BIT(pl->_hoops_RRHH, _hoops_IHHCA)) {
			if (_hoops_CHACS[_hoops_SSRCS] && _hoops_CHACS[_hoops_GGACS]) {
				_hoops_AIGA(&_hoops_ARACS, 3, float, _hoops_AIACS->points);
				_hoops_AIGA(&_hoops_PRACS, 3, float, _hoops_AIACS->points+1);
			}
			else if (_hoops_CHACS[_hoops_SSRCS]) {
				_hoops_AIGA(&_hoops_ARACS, 3, float, _hoops_AIACS->points);
				_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
			}
			else if (_hoops_CHACS[_hoops_GGACS]) {
				_hoops_AIGA(&_hoops_PRACS, 3, float, _hoops_AIACS->points);
				_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
			}
		}
		else{
			_hoops_AIGA(&_hoops_ARACS, 3, float, _hoops_AIACS->points);
			_hoops_AIGA(&_hoops_PRACS, 3, float, _hoops_AIACS->points+1);
		}
		_hoops_CCAIP(nr, _hoops_AIACS);
		_hoops_HPRH(_hoops_AIACS);
	}
	else if (_hoops_HGACS == 2 /* || _hoops_GCACS == 2 */) {
		Polyline *		_hoops_AIACS;

		ZALLOC(_hoops_AIACS, Polyline);
		_hoops_AIACS->_hoops_HIHI = 1;
		_hoops_AIACS->type = _hoops_IIIP;
		_hoops_AIACS->allocated = 2;
		_hoops_AIACS->count = 2;
		ZALLOC_ARRAY(_hoops_AIACS->points, 2, Point);
		if (BIT(pl->_hoops_RRHH, _hoops_IHHCA)) {
			if (_hoops_CHACS[_hoops_HRASA] && _hoops_CHACS[_hoops_IRASA]) {
				_hoops_AIGA(&_hoops_GRACS, 3, float, _hoops_AIACS->points);
				_hoops_AIGA(&_hoops_RRACS, 3, float, _hoops_AIACS->points+1);
			}
			else if (_hoops_CHACS[_hoops_HRASA]) {
				_hoops_AIGA(&_hoops_GRACS, 3, float, _hoops_AIACS->points);
				_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
			}
			else if (_hoops_CHACS[_hoops_IRASA]) {
				_hoops_AIGA(&_hoops_RRACS, 3, float, _hoops_AIACS->points);
				_hoops_AIGA(&_hoops_IRACS, 3, float, _hoops_AIACS->points+1);
			}
		}
		else{
			_hoops_AIGA(&_hoops_GRACS, 3, float, _hoops_AIACS->points);
			_hoops_AIGA(&_hoops_RRACS, 3, float, _hoops_AIACS->points+1);
		}
		_hoops_CCAIP(nr, _hoops_AIACS);
		_hoops_HPRH(_hoops_AIACS);
	}
	else {
		/* _hoops_RCACS _hoops_PPSR _hoops_GPP _hoops_SHPR, _hoops_PIHA _hoops_PGSA _hoops_SHCA _hoops_APGR */
		_hoops_RPRA const *		m = (_hoops_RPRA const *)_hoops_IHCR->matrix->data.elements;
		float					x, y, z, w;
		DC_Point				_hoops_ACACS[2];

		if (BIT(pl->_hoops_RRHH, _hoops_IHHCA) && !_hoops_CHACS[_hoops_RGACS]) {
			x = _hoops_HPACS*m[0][0] + _hoops_IPACS*m[1][0] + H*m[2][0] + 0*m[3][0];
			y = _hoops_HPACS*m[0][1] + _hoops_IPACS*m[1][1] + H*m[2][1] + 0*m[3][1];
			z = _hoops_HPACS*m[0][2] + _hoops_IPACS*m[1][2] + H*m[2][2] + 0*m[3][2];
			w = _hoops_HPACS*m[0][3] + _hoops_IPACS*m[1][3] + H*m[2][3] + 0*m[3][3];

			if (w != 1.0f) {
				if (w != 0.0f) {
					w = 1.0f / w;
					x *= w;
					y *= w;
					z *= w;
				}
				else {
					/* _hoops_HIIPA ? */
				}
			}
			_hoops_ACACS[0].x = x; _hoops_ACACS[0].y = y; _hoops_ACACS[0].z = z;

			x = _hoops_IRACS.x*m[0][0] + _hoops_IRACS.y*m[1][0] + _hoops_IRACS.z*m[2][0] + m[3][0];
			y = _hoops_IRACS.x*m[0][1] + _hoops_IRACS.y*m[1][1] + _hoops_IRACS.z*m[2][1] + m[3][1];
			z = _hoops_IRACS.x*m[0][2] + _hoops_IRACS.y*m[1][2] + _hoops_IRACS.z*m[2][2] + m[3][2];
			w = _hoops_IRACS.x*m[0][3] + _hoops_IRACS.y*m[1][3] + _hoops_IRACS.z*m[2][3] + m[3][3];

			if (w != 1.0f) {
				if (w != 0.0f) {
					w = 1.0f / w;
					x *= w;
					y *= w;
					z *= w;
				}
				else {
					/* _hoops_HIIPA ? */
				}
			}
			_hoops_ACACS[1].x = x; _hoops_ACACS[1].y = y; _hoops_ACACS[1].z = z;
		}
		else if (BIT(pl->_hoops_RRHH, _hoops_IHHCA) && _hoops_CHACS[_hoops_RGACS]) {
			x = _hoops_HRACS.x*m[0][0] + _hoops_HRACS.y*m[1][0] + _hoops_HRACS.z*m[2][0] + m[3][0];
			y = _hoops_HRACS.x*m[0][1] + _hoops_HRACS.y*m[1][1] + _hoops_HRACS.z*m[2][1] + m[3][1];
			z = _hoops_HRACS.x*m[0][2] + _hoops_HRACS.y*m[1][2] + _hoops_HRACS.z*m[2][2] + m[3][2];
			w = _hoops_HRACS.x*m[0][3] + _hoops_HRACS.y*m[1][3] + _hoops_HRACS.z*m[2][3] + m[3][3];

			if (w != 1.0f) {
				if (w != 0.0f) {
					w = 1.0f / w;
					x *= w;
					y *= w;
					z *= w;
				}
				else {
					/* _hoops_HIIPA ? */
				}
			}
			_hoops_ACACS[0].x = x; _hoops_ACACS[0].y = y; _hoops_ACACS[0].z = z;

			x = _hoops_IRACS.x*m[0][0] + _hoops_IRACS.y*m[1][0] + _hoops_IRACS.z*m[2][0] + m[3][0];
			y = _hoops_IRACS.x*m[0][1] + _hoops_IRACS.y*m[1][1] + _hoops_IRACS.z*m[2][1] + m[3][1];
			z = _hoops_IRACS.x*m[0][2] + _hoops_IRACS.y*m[1][2] + _hoops_IRACS.z*m[2][2] + m[3][2];
			w = _hoops_IRACS.x*m[0][3] + _hoops_IRACS.y*m[1][3] + _hoops_IRACS.z*m[2][3] + m[3][3];

			if (w != 1.0f) {
				if (w != 0.0f) {
					w = 1.0f / w;
					x *= w;
					y *= w;
					z *= w;
				}
				else {
					/* _hoops_HIIPA ? */
				}
			}
			_hoops_ACACS[1].x = x; _hoops_ACACS[1].y = y; _hoops_ACACS[1].z = z;
		}
		else{
			x = _hoops_HPACS*m[0][0] + _hoops_IPACS*m[1][0] + H*m[2][0] + 0*m[3][0];
			y = _hoops_HPACS*m[0][1] + _hoops_IPACS*m[1][1] + H*m[2][1] + 0*m[3][1];
			z = _hoops_HPACS*m[0][2] + _hoops_IPACS*m[1][2] + H*m[2][2] + 0*m[3][2];
			w = _hoops_HPACS*m[0][3] + _hoops_IPACS*m[1][3] + H*m[2][3] + 0*m[3][3];

			if (w != 1.0f) {
				if (w != 0.0f) {
					w = 1.0f / w;
					x *= w;
					y *= w;
					z *= w;
				}
				else {
					/* _hoops_HIIPA ? */
				}
			}
			_hoops_ACACS[0].x = x; _hoops_ACACS[0].y = y; _hoops_ACACS[0].z = z;

			x = _hoops_HRACS.x*m[0][0] + _hoops_HRACS.y*m[1][0] + _hoops_HRACS.z*m[2][0] + m[3][0];
			y = _hoops_HRACS.x*m[0][1] + _hoops_HRACS.y*m[1][1] + _hoops_HRACS.z*m[2][1] + m[3][1];
			z = _hoops_HRACS.x*m[0][2] + _hoops_HRACS.y*m[1][2] + _hoops_HRACS.z*m[2][2] + m[3][2];
			w = _hoops_HRACS.x*m[0][3] + _hoops_HRACS.y*m[1][3] + _hoops_HRACS.z*m[2][3] + m[3][3];

			if (w != 1.0f) {
				if (w != 0.0f) {
					w = 1.0f / w;
					x *= w;
					y *= w;
					z *= w;
				}
				else {
					/* _hoops_HIIPA ? */
				}
			}
			_hoops_ACACS[1].x = x; _hoops_ACACS[1].y = y; _hoops_ACACS[1].z = z;
		}

		if (_hoops_PSRCS)
			_hoops_HCRCS (nr, 2, _hoops_ACACS, true);
		else
			_hoops_SRPIP (nr, 2, _hoops_ACACS);
	}

	FREE_ARRAY_ALIGNED(_hoops_RIRSH, 4, Point, 16);
#endif
}

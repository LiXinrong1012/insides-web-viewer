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
 * $Id: obf_tmp.txt 1.45 2010-08-09 23:24:37 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "driver.h"
#include "hi_proto.h"
#include "hd_proto.h"


/*********************************************************************\
 *	_hoops_HGAIS
\*********************************************************************/
GLOBAL_FUNCTION void HD_Std_3D_NURBS_Curve (
	Net_Rendition const &		in_nr,
	_hoops_PIRGR const *			curve) {
#ifndef _hoops_CCPIR
	Polyline *					polyline;
	Net_Rendition				nr = in_nr;

	if (curve->control_point_count == 0)
		return;

	if (!BIT (curve->_hoops_RRHH, _hoops_CHIAA) &&
		!BIT (nr->transform_rendition->flags, _hoops_AIHS)) {

		float	_hoops_IGAIS = nr->_hoops_AHP->weight;

		if (_hoops_IGAIS < 0)
			_hoops_IGAIS = HD_Compute_Generic_Size (nr, nr->_hoops_AHP->_hoops_PHP, nr->_hoops_AHP->_hoops_HHP, 1.0f, false, 0, true);
		
		_hoops_CAIS sphere(curve->control_point_count, curve->control_points);

		Test _hoops_ASIS = Test_DISJOINT;

		float _hoops_RRIIH = _hoops_IAAA(nr->_hoops_SAIR->_hoops_SCIH.left - nr->_hoops_SAIR->_hoops_HHCAR.left, _hoops_IGAIS);

		HD_Transform_And_Test_Simple_Sphere (nr, 1, &sphere, null, _hoops_RRIIH, 0.0f, &_hoops_ASIS, null, null);

		if (_hoops_ASIS == Test_DISJOINT)
			return;
	}

	if (!BIT(nr->_hoops_AHP->flags, _hoops_HGRIP) &&
		BIT(nr->_hoops_AHP->line_style->flags, LSF_MIDDLE_GLYPH|LSF_JOIN)) {
		nr.Modify()->_hoops_AHP.Modify()->flags |= _hoops_HGRIP;
	}
 
	ZALLOC(polyline, Polyline);

	if (nr->_hoops_ARA->_hoops_APPI._hoops_SAR ||  
		curve->polyline.points == null) {
		
		HI_Generate_NURBS_Polyline (curve,
			&nr->_hoops_ARA->_hoops_APPI, 
			&nr->transform_rendition->matrix->data,
			polyline, 0);

		/* _hoops_SRAI _hoops_SCH _hoops_IH _hoops_SPS _hoops_GHIR */
		if (!nr->_hoops_ARA->_hoops_APPI._hoops_SAR) {
			/* _hoops_IIGGR _hoops_SAII _hoops_IIGR _hoops_RH _hoops_PIH, _hoops_PPR _hoops_GRHP _hoops_SCH _hoops_AARI */
			_hoops_PIRGR alter *_hoops_IPPSI = (_hoops_PIRGR alter *)curve;
			_hoops_IPPSI->polyline.points = polyline->points;
			_hoops_IPPSI->polyline.allocated = polyline->allocated;
			_hoops_IPPSI->polyline.count = polyline->count;
			polyline->_hoops_RRHH = _hoops_PCPIR;
		}	
	}
	else {
		polyline->_hoops_HIHI = 1;
		polyline->type = _hoops_IIIP;
		polyline->_hoops_CPGPR = curve->_hoops_CPGPR;
		polyline->_hoops_RRHH = _hoops_PCPIR;
		polyline->count = curve->polyline.count;
		polyline->points = curve->polyline.points;
		polyline->allocated = curve->polyline.allocated;
	}

	_hoops_GPRH(_hoops_HHRGH)++;
	_hoops_CCAIP (nr, polyline);

	_hoops_HPRH(polyline);
#endif
} /* _hoops_RSGR _hoops_API _hoops_CGAIS */


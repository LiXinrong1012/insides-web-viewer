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
 * $Id: obf_tmp.txt 1.83 2010-07-01 04:34:36 covey Exp $
 */

#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "driver.h"
#include "phdraw.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"


GLOBAL_FUNCTION void HD_Std_3D_Marker (
	Net_Rendition const &		inr,
	Marker const *				marker) {
	Net_Rendition				nr = inr;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
	Display_Context const *		dc = nr->_hoops_SRA;
	float						x, y, z, w;
	DC_Point					point;

	switch (_hoops_IHCR->_hoops_HGSC) {
		case _hoops_SIPHP: {
			x = marker->_hoops_CSAI.x;
			y = marker->_hoops_CSAI.y;
			z = 0.0f;
		}	break;

		case _hoops_CIPHP: {
			x = _hoops_PRPPI (elements, marker->_hoops_CSAI);
			y = _hoops_HRPPI (elements, marker->_hoops_CSAI);
			z = 0.0f;
		}	break;

		case _hoops_PCPHP: {
			x = _hoops_HPRA (elements, marker->_hoops_CSAI);
			y = _hoops_IPRA (elements, marker->_hoops_CSAI);
			z = 0.0f;
		}	break;

		case _hoops_RCPHP: {
			w = _hoops_PHCP (elements, marker->_hoops_CSAI);
			if (w <= _hoops_IHCR->_hoops_CHCR)
				return;

			x = _hoops_HPRA (elements, marker->_hoops_CSAI) / w;
			y = _hoops_IPRA (elements, marker->_hoops_CSAI) / w;
			z = 0.0f;
		}	break;

		case _hoops_ACPHP: {
			x = _hoops_HPRA (elements, marker->_hoops_CSAI);
			y = _hoops_IPRA (elements, marker->_hoops_CSAI);
			z = _hoops_CPRA (elements, marker->_hoops_CSAI);
		}	break;

		case _hoops_GCPHP: {
			w = _hoops_PHCP (elements, marker->_hoops_CSAI);
			if (w <= _hoops_IHCR->_hoops_CHCR)
				return;

			x = _hoops_HPRA (elements, marker->_hoops_CSAI) / w;
			y = _hoops_IPRA (elements, marker->_hoops_CSAI) / w;
			z = _hoops_CPRA (elements, marker->_hoops_CSAI) / w;
		}	break;

		default: {
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "unexpected transform type");
			x = y = z = 0.0f;
		}
	}

	point.x = x;
	point.y = y;

	if (_hoops_PGSC (_hoops_IHCR->_hoops_HGSC))
		point.z = _hoops_IGSC (z, _hoops_IHCR);
	else
		point.z = z;

	if (BIT (_hoops_IHCR->flags, _hoops_CSP))
		if (!HD_Point_Within_Cutting_Planes (_hoops_IHCR, x, y, z)) return;

	if (nr->_hoops_GSP->ysize < 0) {
		_hoops_ICP alter &	_hoops_CCP = nr->_hoops_GSP.Modify();
		float						size;

		size = HD_Compute_Generic_Size (nr, _hoops_CCP->_hoops_PHP, _hoops_CCP->_hoops_HHP, 1.0f, false, 0, true);
		_hoops_CCP->ysize = size*0.5f;
		_hoops_CCP->_hoops_RGRS = size*0.5f*dc->current._hoops_AGRS;

		if (nr->_hoops_GSP->_hoops_HHP == _hoops_SPSC &&	nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH) {
			Point	temp;
			float	_hoops_SACPA;

			temp.x = _hoops_HPRA (_hoops_IHCR->_hoops_IPH->data.elements, marker->_hoops_CSAI);
			temp.y = _hoops_IPRA (_hoops_IHCR->_hoops_IPH->data.elements, marker->_hoops_CSAI);
			temp.z = _hoops_CPRA (_hoops_IHCR->_hoops_IPH->data.elements, marker->_hoops_CSAI);
			z = _hoops_CPRA (_hoops_IHCR->_hoops_SPH->_hoops_PRPA.elements, temp);
			w = _hoops_PHCP (_hoops_IHCR->_hoops_SPH->_hoops_PRPA.elements, temp);
			z /= w;
			z /= _hoops_IHCR->_hoops_SPH->_hoops_SRIR;
			_hoops_SACPA = 1 / (z + 1);
			_hoops_CCP->ysize *= _hoops_SACPA;
			_hoops_CCP->_hoops_RGRS *= _hoops_SACPA;
		}
	}

	if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HPH)) {
		RGBAS32						color;
		RGBA						_hoops_SGIIS;
		Point						_hoops_GRIIS;
		_hoops_SGCC const &	_hoops_HSGA = nr->transform_rendition->_hoops_IPH;
		_hoops_PC				_hoops_RRIIS;

		if (!ANYBIT (_hoops_HSGA->data._hoops_RAGR, _hoops_CICH)) {
			_hoops_ISACP (nr, _hoops_RRIIS,
								 nr->_hoops_GSP->_hoops_CHA,
								 &marker->_hoops_CSAI, null, null, null, null, 0, 0, &_hoops_SGIIS, null);
		}
		else {
			_hoops_GRIIS.x = _hoops_HPRA (_hoops_HSGA->data.elements, marker->_hoops_CSAI);
			_hoops_GRIIS.y = _hoops_IPRA (_hoops_HSGA->data.elements, marker->_hoops_CSAI);
			_hoops_GRIIS.z = _hoops_CPRA (_hoops_HSGA->data.elements, marker->_hoops_CSAI);
			_hoops_ISACP (nr, _hoops_RRIIS,
								 nr->_hoops_GSP->_hoops_CHA,
								 &_hoops_GRIIS, null, null, null, null, 0, 0, &_hoops_SGIIS, null);
		}

		color = _hoops_SGIIS;
		_hoops_SIPCP (dc, color);
		if (marker->orientation) {
			_hoops_ICP alter &	_hoops_CCP = nr->_hoops_GSP.Modify();
			_hoops_HRPA					matrix;

			_hoops_CCP->flags |= _hoops_CGPSP;
			HD_Setup_Line_Marker_Xform(nr, 0, &point, marker, &matrix);
			_hoops_PGIGH (nr, 1, &point, &color, true, null, null);
			HD_Takedown_Line_Marker_Xform(nr);
		}
		else
			_hoops_PGIGH (nr, 1, &point, &color, true, null, null);
	}
	else
		if (marker->orientation) {
			_hoops_ICP alter &	_hoops_CCP = nr->_hoops_GSP.Modify();
			_hoops_HRPA					matrix;

			_hoops_CCP->flags |= _hoops_CGPSP;
			HD_Setup_Line_Marker_Xform(nr, 0, &point, marker, &matrix);
			_hoops_AGIGH (nr, 1, &point, null, null);
			HD_Takedown_Line_Marker_Xform(nr);
		}
		else
			_hoops_AGIGH (nr, 1, &point, null, null);
}


GLOBAL_FUNCTION void HD_Std_3D_Multimarker (
	Net_Rendition const &		nr,
	_hoops_GRPGR const *			_hoops_CHPIR) {

	HD_Markers_To_Polymarker (nr, _hoops_CHPIR->count, _hoops_CHPIR->points);
}

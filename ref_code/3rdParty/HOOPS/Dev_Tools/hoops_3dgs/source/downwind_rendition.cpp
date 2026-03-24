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
 * $Id: obf_tmp.txt 1.532 2010-11-22 21:30:56 jason Exp $
 */


#include "hoops.h"
#include "database.h"
#include "patterns.h"
#include "select.h"
#include "driver.h"
#include "hidden.h"
#include "hl.h"
#include "please.h"
#include "hc_proto.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "adt.h"



local bool _hoops_RSIHP (
	_hoops_CRCP const *				_hoops_SRCP) {
	Subsegment const *			_hoops_SIIS;

	if (ANYBIT (_hoops_SRCP->_hoops_PHSI, _hoops_SHSIR|_hoops_GISIR))
		return false;

	if (_hoops_SRCP->geometry != null)
		return true;

	if ((_hoops_SIIS = _hoops_SRCP->_hoops_RGRPR) != null) do {
		_hoops_CRCP const *			s = _hoops_SSIGP (_hoops_SIIS);

		if (_hoops_RSIHP (s))
			return true;
	} while ((_hoops_SIIS = _hoops_SIIS->next) != null);

	return false;
}


GLOBAL_FUNCTION void HD_Downwind_Window_Frame (
	Net_Rendition alter &		nr,
	Attribute const *			_hoops_ASGPR) {
	_hoops_GSAIR const *		frame = (_hoops_GSAIR const *)_hoops_ASGPR;
	_hoops_ISHHP const	&	_hoops_CSHHP = nr->_hoops_ASIR;

	if (frame->flags != (_hoops_CSHHP->window._hoops_ASIHP & _hoops_SIARP))
		nr.Modify()->_hoops_ASIR.Modify()->window._hoops_ASIHP = frame->flags;
}


local void HD_Downwind_Callback (
	Net_Rendition alter &		nr,
	_hoops_GCHIR const *			callback) {
#ifndef DISABLE_CALLBACKS
	_hoops_IHACR const *		_hoops_RCACR = callback->_hoops_ACHIR;
	_hoops_PSIHP			_hoops_HSIHP = nr->_hoops_RSGC;
	bool						_hoops_ISIHP = false;
	_hoops_CRCP const *				owner = callback->owner;

#define		_hoops_CSIHP(index, _hoops_RCACR, element, type, _hoops_SSIHP) do {	\
		if (_hoops_HSIHP->action.element != (type)_hoops_RCACR->name->address || \
			_hoops_HSIHP->_hoops_AIACR[index] != _hoops_RCACR->_hoops_AIACR) { \
			if (!_hoops_ISIHP) {										\
				_hoops_HSIHP = nr.Modify()->_hoops_RSGC.Modify();	\
				_hoops_ISIHP = true;									\
			}													\
			if (_hoops_SSIHP && _hoops_HSIHP->action.element != nullroutine) --_hoops_HSIHP->_hoops_GGCHP;	\
			_hoops_HSIHP->action.element = (type)_hoops_RCACR->name->address;				\
			if (_hoops_SSIHP && _hoops_HSIHP->action.element != nullroutine) ++_hoops_HSIHP->_hoops_GGCHP;	\
			_hoops_HSIHP->_hoops_RGCHP[index] = owner;				\
			_hoops_HSIHP->_hoops_AIACR[index] = _hoops_RCACR->_hoops_AIACR;	\
		}														\
	} while (0)

	if (_hoops_RCACR != null) do switch (_hoops_RCACR->type) {
		case _hoops_ARRCR: {
			_hoops_CSIHP (_hoops_ARRCR, _hoops_RCACR, draw_dc_marker, _hoops_AGCHP, true);
			if (_hoops_HSIHP->action.draw_dc_marker != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HGCHP;
		}	break;


		case _hoops_HRRCR: {
			_hoops_CSIHP (_hoops_HRRCR, _hoops_RCACR, draw_dc_polyline, _hoops_IGCHP, true);
			if (_hoops_HSIHP->action.draw_dc_polyline != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_CGCHP;
		}	break;

		case _hoops_IRRCR: {
			_hoops_CSIHP (_hoops_IRRCR, _hoops_RCACR, draw_dc_edge, _hoops_SGCHP, true);
			if (_hoops_HSIHP->action.draw_dc_edge != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_CGCHP;
		}	break;

		case _hoops_CRRCR: {
			_hoops_CSIHP (_hoops_CRRCR, _hoops_RCACR, draw_dc_face, _hoops_GRCHP, true);
			if (_hoops_HSIHP->action.draw_dc_face != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;


		case _hoops_GARCR: {
			_hoops_CSIHP (_hoops_GARCR, _hoops_RCACR, draw_dc_colorized_marker, _hoops_ARCHP, true);
			if (_hoops_HSIHP->action.draw_dc_colorized_marker != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HGCHP;
		}	break;

		case _hoops_SRRCR: {
			_hoops_CSIHP (_hoops_SRRCR, _hoops_RCACR, draw_dc_colorized_face, _hoops_PRCHP, true);
			if (_hoops_HSIHP->action.draw_dc_colorized_face != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;


		case _hoops_RARCR	: {
			_hoops_CSIHP (_hoops_RARCR, _hoops_RCACR, draw_dc_line, _hoops_HRCHP, true);
			if (_hoops_HSIHP->action.draw_dc_line != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_CGCHP;
		}	break;

		case _hoops_AARCR: {
			_hoops_CSIHP (_hoops_AARCR, _hoops_RCACR, draw_dc_colorized_line, _hoops_IRCHP, true);
			if (_hoops_HSIHP->action.draw_dc_colorized_line != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_CGCHP;
		}	break;

		case _hoops_CPRCR: {
			_hoops_CSIHP (_hoops_CPRCR, _hoops_RCACR, draw_dc_colorized_polyline, _hoops_CRCHP, true);
			if (_hoops_HSIHP->action.draw_dc_colorized_polyline != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_CGCHP;
		}	break;

		case _hoops_PARCR: {
			_hoops_CSIHP (_hoops_PARCR, _hoops_RCACR, draw_dc_gouraud_line, _hoops_SRCHP, true);
			if (_hoops_HSIHP->action.draw_dc_gouraud_line != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_CGCHP;
		}	break;

		case _hoops_SPRCR: {
			_hoops_CSIHP (_hoops_SPRCR, _hoops_RCACR, draw_dc_gouraud_polyline, _hoops_GACHP, true);
			if (_hoops_HSIHP->action.draw_dc_gouraud_polyline != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_CGCHP;
		}	break;

		case _hoops_GHRCR: {
			_hoops_CSIHP (_hoops_GHRCR, _hoops_RCACR, draw_dc_phong_polyline, _hoops_RACHP, true);
			if (_hoops_HSIHP->action.draw_dc_phong_polyline != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_CGCHP;
		 }	break;

		case _hoops_RHRCR: {
			_hoops_CSIHP (_hoops_RHRCR, _hoops_RCACR, draw_dc_textured_polyline, _hoops_AACHP, true);
			if (_hoops_HSIHP->action.draw_dc_textured_polyline != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_CGCHP;
		}	break;

		case _hoops_HARCR: {
			_hoops_CSIHP (_hoops_HARCR, _hoops_RCACR,
						   draw_dc_reshaded_line, _hoops_PACHP, true);
			if (_hoops_HSIHP->action.draw_dc_reshaded_line != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_CGCHP;
		}	break;

		case _hoops_IARCR: {
			_hoops_CSIHP (_hoops_IARCR, _hoops_RCACR, draw_dc_triangle, _hoops_HACHP, true);
			if (_hoops_HSIHP->action.draw_dc_triangle != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;

		case _hoops_RPRCR: {
			_hoops_CSIHP (_hoops_RPRCR, _hoops_RCACR, draw_dc_polytriangle, _hoops_IACHP, true);
			if (_hoops_HSIHP->action.draw_dc_polytriangle != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;

		case _hoops_CARCR: {
			_hoops_CSIHP (_hoops_CARCR, _hoops_RCACR, draw_dc_colorized_triangle, _hoops_CACHP, true);
			if (_hoops_HSIHP->action.draw_dc_colorized_triangle != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;

		case _hoops_APRCR: {
			_hoops_CSIHP (_hoops_APRCR, _hoops_RCACR, draw_dc_colorized_polytriangle, _hoops_SACHP, true);
			if (_hoops_HSIHP->action.draw_dc_colorized_polytriangle != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;

		case _hoops_SARCR: {
			_hoops_CSIHP (_hoops_SARCR, _hoops_RCACR, draw_dc_gouraud_triangle, _hoops_GPCHP, true);
			if (_hoops_HSIHP->action.draw_dc_gouraud_triangle != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;

		case _hoops_PPRCR: {
			_hoops_CSIHP (_hoops_PPRCR, _hoops_RCACR, draw_dc_gouraud_polytriangle, _hoops_RPCHP, true);
			if (_hoops_HSIHP->action.draw_dc_gouraud_polytriangle != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;

		case _hoops_HPRCR: {
			_hoops_CSIHP (_hoops_HPRCR, _hoops_RCACR, draw_dc_phong_polytriangle, _hoops_APCHP, true);
			if (_hoops_HSIHP->action.draw_dc_phong_polytriangle != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;

		case _hoops_IPRCR: {
			_hoops_CSIHP (_hoops_IPRCR, _hoops_RCACR, draw_dc_textured_polytriangle, _hoops_PPCHP, true);
			if (_hoops_HSIHP->action.draw_dc_textured_polytriangle != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;

		case _hoops_GPRCR: {
			_hoops_CSIHP (_hoops_GPRCR, _hoops_RCACR, draw_dc_reshaded_triangle, _hoops_HPCHP, true);
			if (_hoops_HSIHP->action.draw_dc_reshaded_triangle != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;

		case _hoops_AHRCR: {
			_hoops_CSIHP (_hoops_AHRCR, _hoops_RCACR, draw_dc_polymarker, _hoops_IPCHP, true);
			if (_hoops_HSIHP->action.draw_dc_polymarker != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HGCHP;
				_hoops_HSIHP->action_mask |= _hoops_RGPI;
			}
		}	break;

		case _hoops_PHRCR: {
			_hoops_CSIHP (_hoops_PHRCR, _hoops_RCACR, draw_dc_colorized_polymarker, _hoops_CPCHP, true);
			if (_hoops_HSIHP->action.draw_dc_colorized_polymarker != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HGCHP;
				_hoops_HSIHP->action_mask |= _hoops_RGPI;
			}
		}	break;

		case _hoops_HHRCR: {
			_hoops_CSIHP (_hoops_HHRCR, _hoops_RCACR, _hoops_SPCHP, _hoops_GHCHP, true);
			if (_hoops_HSIHP->action._hoops_SPCHP != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_CGCHP;
		}	break;

		case _hoops_IHRCR: {
			_hoops_CSIHP (_hoops_IHRCR, _hoops_RCACR, _hoops_RHCHP, _hoops_AHCHP, true);
			if (_hoops_HSIHP->action._hoops_RHCHP != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_RRCHP;
		}	break;

		case _hoops_GIRCR: {
			_hoops_CSIHP (_hoops_GIRCR, _hoops_RCACR, draw_text, _hoops_PHCHP, true);
			if (_hoops_HSIHP->action.draw_text != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_PGCP;
			}
		}	break;

		case _hoops_RIRCR: {
			_hoops_CSIHP (_hoops_RIRCR, _hoops_RCACR, draw_3d_marker, _hoops_IHCHP, true);
			if (_hoops_HSIHP->action.draw_3d_marker != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_RGPI;
			}
		}	break;

		case _hoops_AIRCR: {
			_hoops_CSIHP (_hoops_AIRCR, _hoops_RCACR, draw_3d_polyline, _hoops_CHCHP, true);
			if (_hoops_HSIHP->action.draw_3d_polyline != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_IRPI;
			}
		}	break;

		case _hoops_PIRCR: {
			_hoops_CSIHP (_hoops_PIRCR, _hoops_RCACR, draw_3d_infinite_line, _hoops_CHCHP, true);
			if (_hoops_HSIHP->action.draw_3d_infinite_line != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
		}	break;

		case _hoops_HIRCR: {
			_hoops_CSIHP (_hoops_HIRCR, _hoops_RCACR, draw_3d_polygon, _hoops_HCIGA, true);
			if (_hoops_HSIHP->action.draw_3d_polygon != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_ACIP;
			}
		}	break;

		case _hoops_RPACR: {
			_hoops_CSIHP (_hoops_RPACR, _hoops_RCACR, _hoops_SHCHP, _hoops_GICHP, true);
			if (_hoops_HSIHP->action._hoops_SHCHP != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
		}	break;

		case _hoops_PCRCR: {
			_hoops_CSIHP (_hoops_PCRCR, _hoops_RCACR, draw_3d_polyedge, _hoops_RICHP, true);
			if (_hoops_HSIHP->action.draw_3d_polyedge != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_IGAI;
			}
		}	break;

		case _hoops_HCRCR: {
			_hoops_CSIHP (_hoops_HCRCR, _hoops_RCACR, draw_3d_polymarker, _hoops_AICHP, true);
			if (_hoops_HSIHP->action.draw_3d_polymarker != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_RGPI;
			}
		}	break;

		case _hoops_ICRCR: {
			_hoops_CSIHP (_hoops_ICRCR, _hoops_RCACR, draw_3d_tristrip, _hoops_PICHP, true);
			/* _hoops_ASIGA _hoops_AA _hoops_SR _hoops_RRP _hoops_SAIA _hoops_PPR _hoops_APGR _hoops_ARI? */
			if (_hoops_HSIHP->action.draw_3d_tristrip != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_PGRI;
			}
		}	break;

		case _hoops_GCRCR: {
			_hoops_CSIHP (_hoops_GCRCR, _hoops_RCACR, draw_3d_polyhedron, _hoops_CHIGA, true);
			if (_hoops_HSIHP->action.draw_3d_polyhedron != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_PCSI;
			}
		}	break;

		case _hoops_IIRCR: {
			_hoops_CSIHP (_hoops_IIRCR, _hoops_RCACR, draw_3d_text, _hoops_HICHP, true);
			if (_hoops_HSIHP->action.draw_3d_text != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_PGCP;
			}
		}	break;

		case _hoops_CIRCR: {
			_hoops_CSIHP (_hoops_CIRCR, _hoops_RCACR, draw_3d_image, _hoops_IICHP, true);
			if (_hoops_HSIHP->action.draw_3d_image != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
		}	break;

		case _hoops_SIRCR: {
			_hoops_CSIHP (_hoops_SIRCR, _hoops_RCACR, draw_3d_grid, _hoops_CCIGA, true);
			if (_hoops_HSIHP->action.draw_3d_grid != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
		}	break;

		case _hoops_RCRCR: {
			_hoops_CSIHP (_hoops_RCRCR, _hoops_RCACR, draw_3d_ellipse, _hoops_GCIGA, true);
			if (_hoops_HSIHP->action.draw_3d_ellipse != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_ACIP;
			}
		}	break;

		case _hoops_ACRCR: {
			_hoops_CSIHP (_hoops_ACRCR, _hoops_RCACR, draw_3d_elliptical_arc, _hoops_ACIGA, true);
			if (_hoops_HSIHP->action.draw_3d_elliptical_arc != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_IRPI;
			}
		}	break;

		case _hoops_PSRCR: {
			_hoops_CSIHP (_hoops_PSRCR, _hoops_RCACR, draw_3d_geometry, _hoops_CICHP, true);
			if (_hoops_HSIHP->action.draw_3d_geometry != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_SICHP;
			}
		}	break;


		case _hoops_HSRCR: {
			_hoops_CSIHP (_hoops_HSRCR, _hoops_RCACR, _hoops_GCCHP, _hoops_RCCHP, true);
			if (_hoops_HSIHP->action._hoops_GCCHP != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
		}	break;

		case _hoops_ISRCR: {
			_hoops_CSIHP (_hoops_ISRCR, _hoops_RCACR, _hoops_ACCHP, _hoops_PCCHP, true);
			if (_hoops_HSIHP->action._hoops_ACCHP != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
		}	break;


		case _hoops_CHRCR: {
			_hoops_CSIHP (_hoops_CHRCR, _hoops_RCACR, draw_window, _hoops_HCCHP, true);
		}	break;

		case _hoops_SHRCR: {
			_hoops_CSIHP (_hoops_SHRCR, _hoops_RCACR, draw_window_frame, _hoops_ICCHP, true);
		}	break;


		case _hoops_CSRCR: {
			_hoops_CSIHP (_hoops_CSRCR, _hoops_RCACR, draw_segment, _hoops_CCCHP, true);
		}	break;

		case _hoops_SSRCR: {
			_hoops_CSIHP (_hoops_SSRCR, _hoops_RCACR, draw_segment_tree, _hoops_SCCHP, true);
		}	break;

		case _hoops_RRACR: {
			_hoops_CSIHP (_hoops_RRACR, _hoops_RCACR, _hoops_GSCHP, _hoops_RSCHP, false);
		}	break;

		case _hoops_ARACR: {
			_hoops_CSIHP (_hoops_ARACR, _hoops_RCACR, _hoops_ASCHP, _hoops_PSCHP, false);
		}	break;

		case _hoops_PRACR: {
			_hoops_CSIHP (_hoops_PRACR, _hoops_RCACR, _hoops_HSCHP, _hoops_IGCHP, true);
		}	break;

		case _hoops_HRACR: {
			_hoops_CSIHP (_hoops_HRACR, _hoops_RCACR, draw_3d_isoline, _hoops_RICHP, true);
		}	break;

		case _hoops_IRACR: {
			_hoops_CSIHP (_hoops_IRACR, _hoops_RCACR, _hoops_ISCHP, _hoops_IGCHP, true);
		}	break;

		case _hoops_CRACR: {
			_hoops_CSIHP (_hoops_CRACR, _hoops_RCACR, _hoops_CSCHP, _hoops_AGCHP, true);
		}	break;

		case _hoops_SRACR: {
			_hoops_CSIHP (_hoops_SRACR, _hoops_RCACR, _hoops_SSCHP, _hoops_IGCHP, true);
		}	break;

		case _hoops_GAACR: {
			_hoops_CSIHP (_hoops_GAACR, _hoops_RCACR,_hoops_GGSHP, _hoops_AGCHP, true);
		}	break;

		case _hoops_PAACR: {
			_hoops_CSIHP (_hoops_PAACR, _hoops_RCACR, finish_picture, _hoops_RGSHP, false);
		}	break;

		case _hoops_HAACR: {
			_hoops_CSIHP (_hoops_HAACR, _hoops_RCACR, create_region, _hoops_AGSHP, false);
		}	break;

		case _hoops_IAACR: {
			_hoops_CSIHP (_hoops_IAACR, _hoops_RCACR, _hoops_HIPGR, _hoops_PGSHP, false);
		}	break;

		case _hoops_CAACR: {
			_hoops_CSIHP (_hoops_CAACR, _hoops_RCACR, _hoops_PIPGR, _hoops_HGSHP, false);
		}	break;

		case _hoops_SAACR: {
			_hoops_CSIHP (_hoops_SAACR, _hoops_RCACR, _hoops_ISPGR, _hoops_IGSHP, false);
		}	break;

		case _hoops_CCRCR: {
			_hoops_CSIHP (_hoops_CCRCR, _hoops_RCACR, draw_3d_sphere, _hoops_CIIGA, true);
			if (_hoops_HSIHP->action.draw_3d_sphere != nullroutine)
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
		}	break;

		case _hoops_SCRCR: {
			_hoops_CSIHP (_hoops_SCRCR, _hoops_RCACR, draw_3d_cylinder, _hoops_AIIGA, true);
			if (_hoops_HSIHP->action.draw_3d_cylinder != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_PCSI;
			}
		}	break;

		case _hoops_GSRCR: {
			_hoops_CSIHP (_hoops_GSRCR, _hoops_RCACR, draw_3d_polycylinder, _hoops_HIIGA, true);
			if (_hoops_HSIHP->action.draw_3d_polycylinder != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_PCSI;
			}
		}	break;

		case _hoops_RSRCR: {
			_hoops_CSIHP (_hoops_RSRCR, _hoops_RCACR, draw_3d_nurbs_curve, _hoops_CGSHP, true);
			if (_hoops_HSIHP->action.draw_3d_nurbs_curve != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_IRPI;
			}
		}	break;

		case _hoops_ASRCR: {
			_hoops_CSIHP (_hoops_ASRCR, _hoops_RCACR, draw_3d_nurbs_surface, _hoops_GIIGA, true);
			if (_hoops_HSIHP->action.draw_3d_nurbs_surface != nullroutine) {
				_hoops_HSIHP->_hoops_PGCHP |= _hoops_HHCHP;
				_hoops_HSIHP->action_mask |= _hoops_PCSI;
			}
		}	break;

		case _hoops_APACR: {
			_hoops_CSIHP (_hoops_APACR, _hoops_RCACR, _hoops_SGSHP, _hoops_GRSHP, true);
		}	break;

		case _hoops_PPACR: {
			_hoops_CSIHP (_hoops_PPACR, _hoops_RCACR, set_shader, _hoops_RRSHP, true);
		}	break;

		case _hoops_HPACR: {
			_hoops_CSIHP (_hoops_HPACR, _hoops_RCACR, _hoops_ARSHP, _hoops_PRSHP, true);
		}	break;

	} while ((_hoops_RCACR = _hoops_RCACR->next) != null);

	nr->_hoops_RCSHR |= _hoops_HSIHP->_hoops_PGCHP;

	if (nr->_hoops_RSGC->_hoops_GGCHP > 0)
		nr->flags |= _hoops_HRSHP;
	else
		nr->flags &= ~_hoops_HRSHP;

	if (BIT(_hoops_HSIHP->_hoops_PGCHP, _hoops_CGCHP))
		_hoops_HSIHP->action_mask |= _hoops_IRPI;
	if (BIT(_hoops_HSIHP->_hoops_PGCHP, _hoops_RRCHP))
		_hoops_HSIHP->action_mask |= (_hoops_PGRI | _hoops_ACIP);
	if (BIT(_hoops_HSIHP->_hoops_PGCHP, _hoops_HGCHP))
		_hoops_HSIHP->action_mask |= _hoops_RGPI;
#endif
}

local int HD_Downwind_Rendering_Options (
	Net_Rendition alter &		nr,
	_hoops_RHAIR const	*	_hoops_AHAIR,
	_hoops_PIGRA const *		_hoops_PCGS) 
{
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_GHGI					_hoops_CCCIR;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_GHGI					_hoops_IRSHP = _hoops_RRGH->_hoops_PPH;
	bool						_hoops_CRSHP = false;
	bool						_hoops_SRSHP = false;
	int							_hoops_HCHHP = _hoops_ICHHP;

	UNREFERENCED(_hoops_PCGS);

	/* _hoops_GIGHR: _hoops_IGRI _hoops_AAHS _hoops_GIR _hoops_GAR _hoops_GRH _hoops_AGIR _hoops_ARPP _hoops_HGSI _hoops_HAPR */

	if ((_hoops_CCCIR = _hoops_AHAIR->_hoops_SCIAA &
				   (_hoops_RRGH->_hoops_GASHP ^ _hoops_AHAIR->_hoops_RSIAA)) != 0)
		nr.Modify()->_hoops_IRR.Modify()->_hoops_GASHP ^= _hoops_CCCIR;

	if ((_hoops_CCCIR = _hoops_AHAIR->_hoops_PSHCA &
				   (_hoops_RRGH->_hoops_PPH ^ _hoops_AHAIR->_hoops_RRRAP)) != 0)
		nr.Modify()->_hoops_IRR.Modify()->_hoops_PPH ^= _hoops_CCCIR;

	if ((_hoops_CCCIR = _hoops_AHAIR->_hoops_ISHCA &
		(_hoops_RRGH->_hoops_CSA ^ _hoops_AHAIR->_hoops_GHRAP)) != 0) {
		nr.Modify()->_hoops_IRR.Modify()->_hoops_CSA ^= _hoops_CCCIR;

		if (BIT (_hoops_CCCIR, _hoops_HIRC) &&
			nr->_hoops_ARA->_hoops_CICP._hoops_CCCRP == _hoops_HCCRP) {
			_hoops_CAHHP const &		_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
			_hoops_GRA alter &		_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

			if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_HIRC)) {
				_hoops_GCIHP->_hoops_CICP.scale = _hoops_SAHHP->_hoops_CSIR->length - 1;
				_hoops_GCIHP->_hoops_CICP.translate = 0.0f;
			}
			else {
				_hoops_GCIHP->_hoops_CICP.scale = _hoops_SAHHP->_hoops_CSIR->length;
				_hoops_GCIHP->_hoops_CICP.translate = -0.5f;
			}
		}
	}


	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_CRRAP) &&
		_hoops_AHAIR->_hoops_CHIH != nr->transform_rendition->_hoops_CHIH) {
		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

		_hoops_GGCC->_hoops_CHIH = _hoops_GGCC->_hoops_RASHP = (float)_hoops_AHAIR->_hoops_CHIH;
		if (!BIT(dc->flags, _hoops_AASHP))
			_hoops_GGCC->_hoops_CHIH *= dc->_hoops_PGCC._hoops_PASHP /
								(float)(1L << dc->_hoops_PGCC._hoops_HASHP);

		nr->flags &= ~_hoops_IASHP;
	}
	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_IPRAP) &&
		_hoops_AHAIR->_hoops_IGAAP != nr->transform_rendition->_hoops_IGAAP) {
		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

		_hoops_GGCC->_hoops_IGAAP = _hoops_GGCC->_hoops_CASHP = (float)_hoops_AHAIR->_hoops_IGAAP;
		if (!BIT(dc->flags, _hoops_AASHP))
			_hoops_GGCC->_hoops_IGAAP *= dc->_hoops_PGCC._hoops_PASHP /
								(float)(1L << dc->_hoops_PGCC._hoops_HASHP);
	}
	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_SARAP) &&
		_hoops_AHAIR->_hoops_SHIH != nr->transform_rendition->_hoops_SHIH) {
		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

			_hoops_GGCC->_hoops_SHIH = _hoops_GGCC->_hoops_SASHP = (float)_hoops_AHAIR->_hoops_SHIH;
			if (!BIT(dc->flags, _hoops_AASHP))
				_hoops_GGCC->_hoops_SHIH *= dc->_hoops_PGCC._hoops_PASHP /
				(float)(1L << dc->_hoops_PGCC._hoops_HASHP);
	}

	if (BIT(_hoops_AHAIR->_hoops_PSHCA, _hoops_SPRAP)) {
		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

		if (BIT (_hoops_AHAIR->_hoops_RRRAP, _hoops_SPRAP))
			_hoops_GGCC->flags |= _hoops_GPSHP;
		else
			_hoops_GGCC->flags &= ~_hoops_GPSHP;
	}


	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_GPRAP)) {
		if (_hoops_AHAIR->_hoops_GSAAP != nr->_hoops_AHP->_hoops_HCAA)
			nr.Modify()->_hoops_AHP.Modify()->_hoops_HCAA = (float)_hoops_AHAIR->_hoops_GSAAP;

		if (_hoops_AHAIR->_hoops_RSAAP != nr->_hoops_RHP->_hoops_HCAA)
			nr.Modify()->_hoops_RHP.Modify()->_hoops_HCAA = (float)_hoops_AHAIR->_hoops_RSAAP;
	}
	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_IRRAP)) {
		int				dl = _hoops_AHAIR->_hoops_PSAAP;

		if (nr->_hoops_IRR->_hoops_GAHA != dl ||
			dl == _hoops_ASAAP) {
			_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

			_hoops_APIHP->_hoops_GAHA = dl;
			if (dl == _hoops_ASAAP)
				_hoops_APIHP->_hoops_RPSHP = true;
		}
	}

	if (_hoops_AHAIR->geometry != null) {

#ifndef _hoops_CCPIR
		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_IRICA)) {
			_hoops_GRA alter &		_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

			if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_HHGAP))
				_hoops_GCIHP->_hoops_APPI._hoops_SAR =
					BIT (_hoops_AHAIR->geometry->_hoops_APPI.value, _hoops_HHGAP);
			if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_CHGAP))
				_hoops_GCIHP->_hoops_APPI._hoops_PPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_PPPI;
			if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_SHGAP))
				_hoops_GCIHP->_hoops_APPI._hoops_HPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_HPPI;
			if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_GIGAP))
				_hoops_GCIHP->_hoops_APPI._hoops_IPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_IPPI;
			if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_RIGAP))
				_hoops_GCIHP->_hoops_APPI._hoops_CPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_CPPI;
			if (BIT (_hoops_AHAIR->geometry->_hoops_APPI.mask, _hoops_AIGAP))
				_hoops_GCIHP->_hoops_APPI._hoops_SPPI = _hoops_AHAIR->geometry->_hoops_APPI._hoops_SPPI;
		}
#endif

#ifndef _hoops_GSPIR
		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_CRICA)) {
			_hoops_GRA alter &		_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

			if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_PIGAP))
				_hoops_GCIHP->_hoops_APSHP._hoops_GGIRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_GGIRP;
			if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_IIGAP))
				_hoops_GCIHP->_hoops_APSHP._hoops_CSHRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_CSHRP;
			if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_CIGAP))
				_hoops_GCIHP->_hoops_APSHP._hoops_RGIRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_RGIRP;
			if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_SIGAP))
				_hoops_GCIHP->_hoops_APSHP._hoops_AGIRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_AGIRP;
			if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_GCGAP))
				_hoops_GCIHP->_hoops_APSHP._hoops_PGIRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_PGIRP;
			if (BIT (_hoops_AHAIR->geometry->_hoops_PSRIR.mask, _hoops_RCGAP))
				_hoops_GCIHP->_hoops_APSHP._hoops_SSHRP = _hoops_AHAIR->geometry->_hoops_PSRIR.configs._hoops_SSHRP;
			_hoops_ISHRP(_hoops_GCIHP->_hoops_APSHP);
		}
#endif

		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_SRICA)) {
			_hoops_GRA const &			_hoops_RRA = nr->_hoops_ARA;
			bool								_hoops_PPSHP = false;

			if (BIT (_hoops_AHAIR->geometry->_hoops_GAICA.mask, _hoops_ACGAP)) {
				for (int ii=0; ii<_hoops_IGAIR; ++ii) {
					if (_hoops_AHAIR->geometry->_hoops_GAICA.cylinder[ii] != _hoops_RRA->_hoops_GAICA.cylinder[ii]) {
						_hoops_PPSHP = true;
						break;
					}
				}
			}
			if (!_hoops_PPSHP && BIT (_hoops_AHAIR->geometry->_hoops_GAICA.mask, _hoops_PCGAP)) {
				for (int ii=0; ii<_hoops_IGAIR; ++ii) {
					if (_hoops_AHAIR->geometry->_hoops_GAICA.sphere[ii] != _hoops_RRA->_hoops_GAICA.sphere[ii]) {
						_hoops_PPSHP = true;
						break;
					}
				}
			}

			if (_hoops_PPSHP) {
				_hoops_GRA alter &		_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

				if (BIT (_hoops_AHAIR->geometry->_hoops_GAICA.mask, _hoops_ACGAP)) {
					for (int ii=0; ii<_hoops_IGAIR; ++ii) {
						_hoops_GCIHP->_hoops_GAICA.cylinder[ii] = _hoops_AHAIR->geometry->_hoops_GAICA.cylinder[ii];
					}
				}
				if (BIT (_hoops_AHAIR->geometry->_hoops_GAICA.mask, _hoops_PCGAP)) {
					for (int ii=0; ii<_hoops_IGAIR; ++ii) {
						_hoops_GCIHP->_hoops_GAICA.sphere[ii] = _hoops_AHAIR->geometry->_hoops_GAICA.sphere[ii];
					}
				}
			}
		}

		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_HRICA)) {
			_hoops_GRA const &			_hoops_RRA = nr->_hoops_ARA;
			int									_hoops_HPSHP;

			if ((_hoops_HPSHP = (_hoops_AHAIR->geometry->mask &
								 (_hoops_RRA->geometry_options ^ _hoops_AHAIR->geometry->value))) != 0 ||
				BIT (_hoops_AHAIR->geometry->mask, _hoops_GHGAP) &&
				_hoops_RRA->_hoops_GCIPR != _hoops_AHAIR->geometry->_hoops_GCIPR) {
				_hoops_GRA alter &		_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

				_hoops_GCIHP->geometry_options ^= _hoops_HPSHP;
				_hoops_GCIHP->_hoops_GCIPR = _hoops_AHAIR->geometry->_hoops_GCIPR;
			}
		}

	}


	if (_hoops_AHAIR->_hoops_HHAIR != null) {

		if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_PPRAP)) {
			_hoops_GRGH alter &_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();
			if (BIT (_hoops_AHAIR->_hoops_RRRAP, _hoops_PPRAP))
				_hoops_APIHP->_hoops_HRGA = _hoops_AHAIR->_hoops_HHAIR->_hoops_HRGA;
			else
				_hoops_APIHP->_hoops_HRGA = _hoops_IRGA::_hoops_CRGA;
		}

#ifndef DISABLE_CUT_GEOMETRY
		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_ARICA)) {
			_hoops_GCIR	 alter &	_hoops_SCPHP = nr.Modify()->_hoops_CPP.Modify();

			if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_RSSRP)) {
				_hoops_SCPHP->_hoops_PRIGA.level = _hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.level;

				nr->flags &= ~(_hoops_IPSHP|_hoops_CPSHP);

				if (_hoops_SCPHP->_hoops_PRIGA.level == _hoops_GGGAP)
					nr->flags |= _hoops_CPSHP;
				else
					nr->flags &= ~_hoops_CPSHP;

				ASSERT(_hoops_SCPHP->_hoops_PRIGA.level != _hoops_CSSRP);
			}

			if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_HSSRP)) {
				if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.value, _hoops_HSSRP))
					_hoops_SCPHP->_hoops_PRIGA._hoops_SRIGA = _hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA._hoops_SRIGA;
				else
					_hoops_SCPHP->_hoops_PRIGA._hoops_SRIGA = _hoops_RGGAP;
			}

			if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.mask, _hoops_PSSRP)) {
				_hoops_SCPHP->_hoops_PRIGA._hoops_CCPHP =
									BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.value, _hoops_ISSRP);
				_hoops_SCPHP->_hoops_PRIGA.tolerance = _hoops_AHAIR->_hoops_HHAIR->_hoops_PRIGA.tolerance;
				_hoops_SCPHP->_hoops_PRIGA._hoops_GSPHP = _hoops_SCPHP->_hoops_PRIGA.tolerance;

				if (_hoops_SCPHP->_hoops_PRIGA._hoops_CCPHP) {
					_hoops_HHRA const *		_hoops_SPH;

					_hoops_SCPHP->_hoops_PRIGA._hoops_GSPHP *= 0.01f;
					if ((_hoops_SPH = nr->transform_rendition->_hoops_SPH) != null) {
						_hoops_SCPHP->_hoops_PRIGA.tolerance =
								_hoops_SCPHP->_hoops_PRIGA._hoops_GSPHP *
								_hoops_IAAA (_hoops_SPH->_hoops_ISPA, _hoops_SPH->_hoops_SSPA);
					}
				}
			}
		}
#endif

#ifndef DISABLE_SIMPLE_SHADOW
		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_RRICA)) {
			_hoops_GCIR	 alter &	_hoops_SCPHP = nr.Modify()->_hoops_CPP.Modify();

			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_PGGAP)) {
				if (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS._hoops_RGP != _hoops_HRGAP)
					nr->flags |= _hoops_SPSHP;
				else
					nr->flags &= ~_hoops_SPSHP;

				switch (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS._hoops_RGP) {
					case _hoops_HRGAP: {
						nr->flags &= ~_hoops_GHSHP;
					}	break;

					case _hoops_IRGAP: {
						nr->flags |= _hoops_GHSHP;
					}	break;

					case _hoops_CRGAP: {
					}	break;
				}
			}

			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_IGGAP))
				_hoops_SCPHP->_hoops_GHSS.plane = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.plane;
			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_CGGAP))
				_hoops_SCPHP->_hoops_GHSS.light = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.light;

			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_PRGAP))
				_hoops_SCPHP->_hoops_GHSS._hoops_RPHHP = BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.value, _hoops_PRGAP);

			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_SGGAP)) {
				RGB			color;

				if (_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.color.rgb.green < 0.0f) { /* _hoops_CIHA */
	#ifndef DISABLE_COLOR_MAPS
					_hoops_CAHHP const &		_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;
					int								index = (int)(_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.color.rgb.red + 0.5f);

					if (index < (int)_hoops_SAHHP->length) {
						Named_Material const *		_hoops_ISHIR = _hoops_SAHHP->_hoops_CSIR->_hoops_HAA;

						color = _hoops_ISHIR[index]._hoops_CSHR;
					}
					else
						color.red = color.green = color.blue = 0.0f;
	#else
					color.red = color.green = color.blue = 0.0f;
	#endif
					_hoops_SCPHP->_hoops_GHSS.color = color;
				}
				else {
					_hoops_SCPHP->_hoops_GHSS.color = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.color.rgb;
				}
			}
			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_GRGAP))
				_hoops_SCPHP->_hoops_GHSS._hoops_IRIR = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS._hoops_IRIR;

			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_RRGAP))
				_hoops_SCPHP->_hoops_GHSS._hoops_HAP = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS._hoops_HAP;
			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS.mask, _hoops_ARGAP))
				_hoops_SCPHP->_hoops_GHSS._hoops_IGGGR = _hoops_AHAIR->_hoops_HHAIR->_hoops_GHSS._hoops_IGGGR;

			if (_hoops_SCPHP->_hoops_GHSS.light._hoops_SSRP (_hoops_SCPHP->_hoops_GHSS.plane) < 0.0f) {
				/* _hoops_RHSHP _hoops_IPPA _hoops_CCA _hoops_RRR _hoops_IH _hoops_PGISR */
				_hoops_SCPHP->_hoops_GHSS.plane = -_hoops_SCPHP->_hoops_GHSS.plane;
			}
		}
#endif

		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_CSGAP)) {
			_hoops_GCIR	 alter &	_hoops_SCPHP = nr.Modify()->_hoops_CPP.Modify();

			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.mask, _hoops_GAGAP)) {
				if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.value, _hoops_GAGAP))
					nr->flags |= _hoops_AHSHP;
				else
					nr->flags &= ~_hoops_AHSHP;
			}
			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.mask, _hoops_AAGAP))
				if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.value, _hoops_AAGAP))
					_hoops_SCPHP->_hoops_HRR._hoops_HI = true;
				else
					_hoops_SCPHP->_hoops_HRR._hoops_HI = false;

			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.mask, _hoops_IAGAP))
				if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.value, _hoops_IAGAP))
					_hoops_SCPHP->_hoops_HRR._hoops_SAR = true;
				else
					_hoops_SCPHP->_hoops_HRR._hoops_SAR = false;

			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.mask, _hoops_PAGAP))
				_hoops_SCPHP->_hoops_HRR._hoops_HAP = _hoops_AHAIR->_hoops_HHAIR->_hoops_HRR._hoops_HAP;
			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_HRR.mask, _hoops_HAGAP))
				_hoops_SCPHP->_hoops_HRR._hoops_CAP = _hoops_AHAIR->_hoops_HHAIR->_hoops_HRR._hoops_CAP;
		}

		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_SSGAP)) {
			_hoops_GCIR	 alter &	_hoops_SCPHP = nr.Modify()->_hoops_CPP.Modify();

			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_CAGAP)) {
				if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_CAGAP))
					nr->flags |= _hoops_PHSHP|_hoops_HHSHP;
				else
					nr->flags &= ~(_hoops_PHSHP|_hoops_HHSHP);
			}

			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_GPGAP))
				_hoops_SCPHP->_hoops_RHGGR.plane = _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.plane;
			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_RPGAP))
				_hoops_SCPHP->_hoops_RHGGR._hoops_IRIR = _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR._hoops_IRIR;
			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_APGAP))
				_hoops_SCPHP->_hoops_RHGGR._hoops_IHSHP = BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.value, _hoops_APGAP);
			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_HPGAP))
				_hoops_SCPHP->_hoops_RHGGR._hoops_IGGGR = _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR._hoops_IGGGR;
			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_PPGAP)) {
				_hoops_SCPHP->_hoops_RHGGR.hither = _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.hither;
				_hoops_SCPHP->_hoops_RHGGR.yon = _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.yon;
				_hoops_SCPHP->_hoops_RHGGR._hoops_SIRH = (_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.yon != 0);
			}
			if (BIT(_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR.mask, _hoops_IPGAP)) {
				_hoops_SCPHP->_hoops_RHGGR._hoops_RGP &= ~_hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask;
				_hoops_SCPHP->_hoops_RHGGR._hoops_RGP |= _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.mask &
													 _hoops_AHAIR->_hoops_HHAIR->_hoops_RHGGR._hoops_RGP.value;

				if (BIT(dc->flags, _hoops_CHSHP) &&
					ANYBIT (nr->_hoops_RGP, ~_hoops_SCPHP->_hoops_RHGGR._hoops_RGP)) {
					nr->_hoops_RGP &= _hoops_SCPHP->_hoops_RHGGR._hoops_RGP;
				}
			}
		}


		if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_HPH) &&
			(_hoops_AHAIR->_hoops_HHAIR->_hoops_CRIR.hither != nr->_hoops_CPP->_hoops_CRIR.hither ||
			_hoops_AHAIR->_hoops_HHAIR->_hoops_CRIR.yon	   != nr->_hoops_CPP->_hoops_CRIR.yon)) {
				_hoops_GCIR	 alter &	_hoops_SCPHP = nr.Modify()->_hoops_CPP.Modify();

				_hoops_SCPHP->_hoops_CRIR.hither = _hoops_AHAIR->_hoops_HHAIR->_hoops_CRIR.hither;
				_hoops_SCPHP->_hoops_CRIR.yon = _hoops_AHAIR->_hoops_HHAIR->_hoops_CRIR.yon;
		}

		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GGRAP)) {
			_hoops_GCIR	alter &		_hoops_SCPHP = nr.Modify()->_hoops_CPP.Modify();

			if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.mask, _hoops_ICSRP)) {
				if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.value, _hoops_ICSRP)) {
					_hoops_SCPHP->_hoops_GIC._hoops_HCIR[0] = _hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[0];
					_hoops_SCPHP->_hoops_GIC._hoops_HCIR[1] = _hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_HCIR[1];
				}
				else {
					_hoops_SCPHP->_hoops_GIC._hoops_HCIR[0] = _hoops_SCPHP->_hoops_GIC._hoops_HCIR[1] = 0;
				}

			}
			if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.mask, _hoops_SCSRP)) {
				_hoops_SCPHP->_hoops_GIC._hoops_GRCR = _hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR._hoops_GRCR;
			}
			if (BIT (_hoops_AHAIR->_hoops_HHAIR->_hoops_IHAIR.value, _hoops_GSSRP)) {
				HD_Downwind_Color_Map(nr, (Attribute *)_hoops_AHAIR);
			}
		}

		if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_IARAP) &&
			_hoops_AHAIR->_hoops_HHAIR->_hoops_ACSRP !=
			nr->transform_rendition->_hoops_ACSRP) {
				nr.Modify()->transform_rendition.Modify()->_hoops_ACSRP = _hoops_AHAIR->_hoops_HHAIR->_hoops_ACSRP;
				_hoops_SRSHP = true;
		}

		if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_RPRAP) &&
			_hoops_AHAIR->_hoops_HHAIR->_hoops_PCSRP !=
			nr->transform_rendition->_hoops_PCSRP) {
				nr.Modify()->transform_rendition.Modify()->_hoops_PCSRP = _hoops_AHAIR->_hoops_HHAIR->_hoops_PCSRP;
				_hoops_SRSHP = true;
		}

	}

	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_HRRAP) &&
		(_hoops_AHAIR->_hoops_HHAAP[0] != nr->transform_rendition->_hoops_GSCH[0] ||
		 _hoops_AHAIR->_hoops_HHAAP[1] != nr->transform_rendition->_hoops_GSCH[1])) {
		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();
		_hoops_HRPA						_hoops_RHSPR;

		HD_Undo_Screen (nr, &_hoops_RHSPR);
		_hoops_GGCC->_hoops_GSCH[0] = _hoops_AHAIR->_hoops_HHAAP[0];
		_hoops_GGCC->_hoops_GSCH[1] = _hoops_AHAIR->_hoops_HHAAP[1];
		if (_hoops_GGCC->_hoops_GSCH[0] == _hoops_GGCC->_hoops_GSCH[1]) {
			if (_hoops_GGCC->_hoops_GSCH[1] == 1.0f)
				_hoops_GGCC->_hoops_GSCH[0] -= 0.0001f;
			else
				_hoops_GGCC->_hoops_GSCH[1] += 0.0001f;
		}
		HD_Redo_Screen (nr, &_hoops_RHSPR);

		if (BIT (_hoops_GGCC->flags, _hoops_HHGGA))
			HD_Set_DC_Cutting_Planes (nr);

		if (dc->_hoops_SHSHP != null)
			dc->_hoops_SHSHP->_hoops_GISHP = true;
	}

	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_APRAP) &&
		(_hoops_AHAIR->_hoops_HCIH.left != nr->transform_rendition->_hoops_HCIH.left ||
		 _hoops_AHAIR->_hoops_HCIH.right != nr->transform_rendition->_hoops_HCIH.right ||
		 _hoops_AHAIR->_hoops_HCIH.bottom != nr->transform_rendition->_hoops_HCIH.bottom ||
		 _hoops_AHAIR->_hoops_HCIH.top != nr->transform_rendition->_hoops_HCIH.top)) {
		_hoops_CGRA const &	_hoops_SGRA = nr->_hoops_SAIR;
		_hoops_HRPA					_hoops_RHSPR;
		Int_Rectangle				_hoops_GPHH;
		float						_hoops_RISHP, _hoops_AISHP,
									_hoops_PISHP, _hoops_HISHP;

		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

		HD_Undo_Screen (nr, &_hoops_RHSPR);
		_hoops_GGCC->_hoops_HCIH = _hoops_AHAIR->_hoops_HCIH;
		HD_Redo_Screen (nr, &_hoops_RHSPR);

		_hoops_PISHP = (_hoops_SGRA->_hoops_CIIH.right - _hoops_SGRA->_hoops_CIIH.left) * 0.5f;
		_hoops_HISHP = (_hoops_SGRA->_hoops_CIIH.top - _hoops_SGRA->_hoops_CIIH.bottom) * 0.5f;
		_hoops_RISHP = (_hoops_SGRA->_hoops_CIIH.left +	_hoops_SGRA->_hoops_CIIH.right) * 0.5f;
		_hoops_AISHP = (_hoops_SGRA->_hoops_CIIH.top + _hoops_SGRA->_hoops_CIIH.bottom) * 0.5f;

		_hoops_GPHH.left   = int (_hoops_RISHP + _hoops_AHAIR->_hoops_HCIH.left   * _hoops_PISHP);
		_hoops_GPHH.right  = int (_hoops_RISHP + _hoops_AHAIR->_hoops_HCIH.right  * _hoops_PISHP);
		_hoops_GPHH.bottom = int (_hoops_AISHP + _hoops_AHAIR->_hoops_HCIH.bottom * _hoops_HISHP);
		_hoops_GPHH.top    = int (_hoops_AISHP + _hoops_AHAIR->_hoops_HCIH.top    * _hoops_HISHP);

		_hoops_GGCC->_hoops_AGAA._hoops_PGPGP(_hoops_GPHH);
	}

	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_GARAP) &&
		(_hoops_AHAIR->_hoops_IHAAP[0] != nr->_hoops_ARA->image.width_scale ||
		 _hoops_AHAIR->_hoops_IHAAP[1] != nr->_hoops_ARA->image._hoops_IISHP)) {
		_hoops_GRA alter &			_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

		_hoops_GCIHP->image.width_scale = _hoops_AHAIR->_hoops_IHAAP[0];
		_hoops_GCIHP->image._hoops_IISHP = _hoops_AHAIR->_hoops_IHAAP[1];
	}

	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_RARAP) &&
		_hoops_AHAIR->_hoops_CHAAP != nr->_hoops_ARA->image._hoops_RSCC) {
		_hoops_GRA alter &			_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

		_hoops_GCIHP->image._hoops_RSCC = _hoops_AHAIR->_hoops_CHAAP;
	}

	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_CPRAP) &&
		_hoops_AHAIR->_hoops_HRA != nr->_hoops_ARA->image._hoops_HRA) {
		_hoops_GRA alter &			_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

		_hoops_GCIHP->image._hoops_HRA = _hoops_AHAIR->_hoops_HRA;
	}

	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_PRRAP) &&
		_hoops_AHAIR->_hoops_IRARR != _hoops_RRGH->_hoops_GSSIR)
		nr.Modify()->_hoops_IRR.Modify()->_hoops_GSSIR = _hoops_AHAIR->_hoops_IRARR;

	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_PARAP) &&
		_hoops_AHAIR->_hoops_SIRAP != _hoops_RRGH->_hoops_SIRAP)
		nr.Modify()->_hoops_IRR.Modify()->_hoops_SIRAP = _hoops_AHAIR->_hoops_SIRAP;

	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_CARAP) &&
		_hoops_AHAIR->_hoops_RCRAP != _hoops_RRGH->_hoops_RCRAP) {
		_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

		_hoops_APIHP->_hoops_RCRAP = _hoops_AHAIR->_hoops_RCRAP;

		if (BIT (_hoops_APIHP->_hoops_RCRAP, _hoops_ICRAP))
			nr.Modify()->_hoops_RCSHR |= _hoops_CISHP;
		else
			nr.Modify()->_hoops_RCSHR &= ~_hoops_CISHP;
	}

	if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GGICA) &&
		(_hoops_AHAIR->_hoops_RGICA.value != nr->_hoops_ASIR->buffer.options ||
		 _hoops_AHAIR->_hoops_RGICA._hoops_SPAAP != nr->_hoops_ASIR->buffer._hoops_SPAAP ||
		 _hoops_AHAIR->_hoops_RGICA._hoops_GHAAP != nr->_hoops_ASIR->buffer._hoops_GHAAP)) {
		_hoops_ISHHP alter &		_hoops_RHIHP = nr.Modify()->_hoops_ASIR.Modify();

		_hoops_RHIHP->buffer.options &= ~_hoops_AHAIR->_hoops_RGICA.mask;
		_hoops_RHIHP->buffer.options |= _hoops_AHAIR->_hoops_RGICA.value;

		if (BIT (_hoops_AHAIR->_hoops_RGICA.value, _hoops_HPAAP))
			_hoops_RHIHP->buffer._hoops_SPAAP = _hoops_AHAIR->_hoops_RGICA._hoops_SPAAP;
		else
			if (BIT (_hoops_AHAIR->_hoops_RGICA.mask, _hoops_HPAAP))
				_hoops_RHIHP->buffer._hoops_SPAAP = 0;

		if (_hoops_RHIHP->buffer._hoops_SPAAP != 0)
			nr->flags |= _hoops_SISHP;
		else
			nr->flags &= ~_hoops_SISHP;

		if (BIT (_hoops_AHAIR->_hoops_RGICA.value, _hoops_CPAAP))
			_hoops_RHIHP->buffer._hoops_GHAAP = _hoops_AHAIR->_hoops_RGICA._hoops_GHAAP;
	}

	if (_hoops_AHAIR->_hoops_AIAIR != null) {

		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_IGICA)) {
			_hoops_ISHHP const	&		_hoops_CSHHP = nr->_hoops_ASIR;
			Line_Style						line_style;

			if (BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_RPCRP)) {
				for (int i=0; i<nr->_hoops_GCSHP->count; i++) {
					if (nr->_hoops_GCSHP->keys[i] == _hoops_AHAIR->_hoops_AIAIR->_hoops_HHCRP &&
						_hoops_RAHSR(_hoops_AHAIR->_hoops_AIAIR->_hoops_PIAIR, nr->_hoops_GCSHP->_hoops_HPAIR[i]->name)) {
						line_style = nr->_hoops_GCSHP->_hoops_HPAIR[i];
						break;
					}
				}

				if (!line_style) {
					HE_WARNING (HEC_LINE_STYLE, HES_NOT_AVAILABLE,
								Sprintf_N (null, "Requested hidden line pattern '%n' not found",
										   &_hoops_AHAIR->_hoops_AIAIR->_hoops_PIAIR));
				}
			}

			if (_hoops_AHAIR->_hoops_AIAIR->value != _hoops_CSHHP->_hoops_GCCI.options ||
				BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_RPCRP) &&
				line_style != _hoops_CSHHP->_hoops_GCCI.line_style ||
				 BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_GHCRP) &&
				 (_hoops_AHAIR->_hoops_AIAIR->weight.value != _hoops_CSHHP->_hoops_GCCI.weight.value ||
				  _hoops_AHAIR->_hoops_AIAIR->weight._hoops_HHP != _hoops_CSHHP->_hoops_GCCI.weight._hoops_HHP) ||
				 BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_SPCRP) &&
				 (_hoops_AHAIR->_hoops_AIAIR->color.red != _hoops_CSHHP->_hoops_GCCI.color.red ||
				  _hoops_AHAIR->_hoops_AIAIR->color.green != _hoops_CSHHP->_hoops_GCCI.color.green ||
				  _hoops_AHAIR->_hoops_AIAIR->color.blue != _hoops_CSHHP->_hoops_GCCI.color.blue) ||
				 BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_APCRP) &&
				 _hoops_AHAIR->_hoops_AIAIR->_hoops_IHCRP != _hoops_CSHHP->_hoops_GCCI._hoops_IHCRP ||
				 BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_PPCRP) &&
				 _hoops_AHAIR->_hoops_AIAIR->_hoops_CHIH != _hoops_CSHHP->_hoops_GCCI._hoops_CHIH ||
				 BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_PHCRP) &&
				 _hoops_AHAIR->_hoops_AIAIR->_hoops_CHCRP != _hoops_CSHHP->_hoops_GCCI._hoops_CHCRP ||
				 BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_AHCRP) &&
				 _hoops_AHAIR->_hoops_AIAIR->_hoops_SRI != _hoops_CSHHP->_hoops_GCCI._hoops_SRI) {
				_hoops_ISHHP alter	&		_hoops_RHIHP = nr.Modify()->_hoops_ASIR.Modify();
				_hoops_GPCRP				_hoops_CCCIR = (_hoops_RHIHP->_hoops_GCCI.options ^ _hoops_AHAIR->_hoops_AIAIR->value) & _hoops_AHAIR->_hoops_AIAIR->mask;
				int								_hoops_RCSHP = _hoops_ICHHP;

				_hoops_RHIHP->_hoops_GCCI.options ^= _hoops_CCCIR;

				if (BIT (_hoops_CCCIR, _hoops_RCCI|_hoops_RHCRP|
								  _hoops_HPCRP|_hoops_IPCRP))
					_hoops_RCSHP |= _hoops_IPIHP;

				if (line_style && BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_RPCRP)) {
					_hoops_RHIHP->_hoops_GCCI.line_style = line_style;
					_hoops_RCSHP |= _hoops_ACSHP;
				}
				if (BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_GHCRP)) {
					_hoops_RHIHP->_hoops_GCCI.weight.value = _hoops_AHAIR->_hoops_AIAIR->weight.value;
					_hoops_RHIHP->_hoops_GCCI.weight._hoops_HHP = _hoops_AHAIR->_hoops_AIAIR->weight._hoops_HHP;
					_hoops_RCSHP |= _hoops_ACSHP;
				}
				if (BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_SPCRP)) {
					_hoops_RHIHP->_hoops_GCCI.color.red = _hoops_AHAIR->_hoops_AIAIR->color.red;
					_hoops_RHIHP->_hoops_GCCI.color.green = _hoops_AHAIR->_hoops_AIAIR->color.green;
					_hoops_RHIHP->_hoops_GCCI.color.blue = _hoops_AHAIR->_hoops_AIAIR->color.blue;
					_hoops_RCSHP |= _hoops_PHIHP;
				}
				if (BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_APCRP)) {
					_hoops_RHIHP->_hoops_GCCI._hoops_IHCRP = _hoops_AHAIR->_hoops_AIAIR->_hoops_IHCRP;
					_hoops_RCSHP |= _hoops_PHIHP;
				}
				if (BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_PPCRP)) {
					_hoops_RHIHP->_hoops_GCCI._hoops_CHIH = _hoops_AHAIR->_hoops_AIAIR->_hoops_CHIH;
					if (!BIT(dc->flags, _hoops_AASHP))
						_hoops_RHIHP->_hoops_GCCI._hoops_CHIH *= dc->_hoops_PGCC._hoops_PASHP /
											(float)(1L << dc->_hoops_PGCC._hoops_HASHP);
				}
				if (BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_PHCRP)) {
					_hoops_RHIHP->_hoops_GCCI._hoops_CHCRP = _hoops_AHAIR->_hoops_AIAIR->_hoops_CHCRP;
					_hoops_RCSHP |= _hoops_IPIHP;
				}

				if (BIT (_hoops_AHAIR->_hoops_AIAIR->value, _hoops_AHCRP))
					_hoops_RHIHP->_hoops_GCCI._hoops_SRI = _hoops_AHAIR->_hoops_AIAIR->_hoops_SRI;

				if (_hoops_RCSHP != _hoops_ICHHP &&
					(ANYBIT (nr->_hoops_IRR->_hoops_SRI, _hoops_SICI|_hoops_PRAAP) ||
					 BIT(dc->flags, _hoops_GPHHP))) {

					_hoops_HCHHP |= _hoops_RCSHP;
					if (ANYBIT(nr->flags, _hoops_RCSHP))
						nr.Modify()->flags &= ~_hoops_RCSHP;
				}
			}
		}
	}

	if (_hoops_AHAIR->_hoops_IIAIR != null) {

		if (ANYBIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_AGRAP | _hoops_PRICA)) {
			_hoops_GRA alter &		_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

			if (ANYBIT (_hoops_AHAIR->_hoops_IIAIR->value, _hoops_RICRP|_hoops_HICRP)) {
				_hoops_GCIHP->_hoops_CICP._hoops_RGP &= ~_hoops_AHAIR->_hoops_IIAIR->_hoops_RGP.mask;
				_hoops_GCIHP->_hoops_CICP._hoops_RGP |= _hoops_AHAIR->_hoops_IIAIR->_hoops_RGP.value;
			}

			if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_AICRP)) {
				if (BIT (_hoops_AHAIR->_hoops_IIAIR->value, _hoops_AICRP)) {
					_hoops_GCIHP->_hoops_CICP._hoops_CCCRP = _hoops_AHAIR->_hoops_IIAIR->_hoops_CCCRP;

					if (_hoops_GCIHP->_hoops_CICP._hoops_CCCRP == _hoops_HCCRP) {
						_hoops_CAHHP const &		_hoops_SAHHP = nr->_hoops_ASIR->_hoops_PSIR;

						if (BIT (nr->_hoops_IRR->_hoops_CSA, _hoops_HIRC)) {
							_hoops_GCIHP->_hoops_CICP.scale = _hoops_SAHHP->_hoops_CSIR->length - 1;
							_hoops_GCIHP->_hoops_CICP.translate = 0.0f;
						}
						else {
							_hoops_GCIHP->_hoops_CICP.scale = _hoops_SAHHP->_hoops_CSIR->length;
							_hoops_GCIHP->_hoops_CICP.translate = -0.5f;
						}
					}
					else {
						_hoops_GCIHP->_hoops_CICP.scale = _hoops_AHAIR->_hoops_IIAIR->scale;
						_hoops_GCIHP->_hoops_CICP.translate = _hoops_AHAIR->_hoops_IIAIR->translate;
					}
				}
				else {
					_hoops_GCIHP->_hoops_CICP._hoops_CCCRP = _hoops_PCCRP;
					_hoops_GCIHP->_hoops_CICP.scale = 1.0f;
					_hoops_GCIHP->_hoops_CICP.translate = 0.0f;
				}
			}

			if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_IICRP)) {
				if (_hoops_GCIHP->_hoops_ACP._hoops_CIAIR != 0)
					FREE_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_SIAIR, _hoops_GCIHP->_hoops_ACP._hoops_CIAIR, float);
				_hoops_GCIHP->_hoops_ACP._hoops_SIAIR = null;

				_hoops_GCIHP->_hoops_ACP._hoops_RSCRP = _hoops_AHAIR->_hoops_IIAIR->_hoops_RSCRP;
				if ((_hoops_GCIHP->_hoops_ACP._hoops_CIAIR = _hoops_AHAIR->_hoops_IIAIR->_hoops_CIAIR) != 0) {
					POOL_ALLOC_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_SIAIR, _hoops_GCIHP->_hoops_ACP._hoops_CIAIR, float, dc->memory_pool);
					_hoops_AIGA (_hoops_AHAIR->_hoops_IIAIR->_hoops_SIAIR, _hoops_GCIHP->_hoops_ACP._hoops_CIAIR, float, _hoops_GCIHP->_hoops_ACP._hoops_SIAIR);
				}
			}
			if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_CICRP)) {
				if (_hoops_GCIHP->_hoops_ACP._hoops_GCAIR != 0)
					FREE_ARRAY (_hoops_GCIHP->_hoops_ACP.colors, _hoops_GCIHP->_hoops_ACP._hoops_GCAIR, RGB);
				_hoops_GCIHP->_hoops_ACP.colors = null;

				if ((_hoops_GCIHP->_hoops_ACP._hoops_GCAIR = _hoops_AHAIR->_hoops_IIAIR->_hoops_GCAIR) != 0) {
					POOL_ALLOC_ARRAY (_hoops_GCIHP->_hoops_ACP.colors, _hoops_GCIHP->_hoops_ACP._hoops_GCAIR, RGB, dc->memory_pool);
					_hoops_AIGA (_hoops_AHAIR->_hoops_IIAIR->colors, _hoops_GCIHP->_hoops_ACP._hoops_GCAIR, RGB, _hoops_GCIHP->_hoops_ACP.colors);
				}
			}
			if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_SICRP)) {
				if (_hoops_GCIHP->_hoops_ACP._hoops_RCAIR != 0) {
					for (int i=0; i<_hoops_GCIHP->_hoops_ACP._hoops_RCAIR; i++)
						_hoops_RGAIR (_hoops_GCIHP->_hoops_ACP._hoops_ACAIR[i]);
					FREE_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_ACAIR, _hoops_GCIHP->_hoops_ACP._hoops_RCAIR, _hoops_HCRPR);

					FREE_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_PCAIR, _hoops_GCIHP->_hoops_ACP._hoops_RCAIR, Integer32);
				}
				_hoops_GCIHP->_hoops_ACP._hoops_ACAIR = null;
				_hoops_GCIHP->_hoops_ACP._hoops_PCAIR = null;

				if ((_hoops_GCIHP->_hoops_ACP._hoops_RCAIR = _hoops_AHAIR->_hoops_IIAIR->_hoops_RCAIR) != 0) {
					POOL_ALLOC_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_ACAIR, _hoops_GCIHP->_hoops_ACP._hoops_RCAIR, _hoops_HCRPR, dc->memory_pool);
					for (int i=0; i<_hoops_GCIHP->_hoops_ACP._hoops_RCAIR; i++)
						HI_Copy_Name (&_hoops_AHAIR->_hoops_IIAIR->_hoops_ACAIR[i], &_hoops_GCIHP->_hoops_ACP._hoops_ACAIR[i]);
					POOL_ALLOC_ARRAY (_hoops_GCIHP->_hoops_ACP._hoops_PCAIR, _hoops_GCIHP->_hoops_ACP._hoops_RCAIR, Integer32, dc->memory_pool);
					_hoops_AIGA (_hoops_AHAIR->_hoops_IIAIR->_hoops_PCAIR, _hoops_GCIHP->_hoops_ACP._hoops_RCAIR, Integer32, _hoops_GCIHP->_hoops_ACP._hoops_PCAIR);
				}
			}
			if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_GCCRP)) {
				if (_hoops_GCIHP->_hoops_ACP.weight_count != 0)
					FREE_ARRAY (_hoops_GCIHP->_hoops_ACP.weights, _hoops_GCIHP->_hoops_ACP.weight_count, _hoops_HCAIR);
				_hoops_GCIHP->_hoops_ACP.weights = null;

				if ((_hoops_GCIHP->_hoops_ACP.weight_count = _hoops_AHAIR->_hoops_IIAIR->weight_count) != 0) {
					POOL_ALLOC_ARRAY (_hoops_GCIHP->_hoops_ACP.weights, _hoops_GCIHP->_hoops_ACP.weight_count, _hoops_HCAIR, dc->memory_pool);
					_hoops_AIGA (_hoops_AHAIR->_hoops_IIAIR->weights, _hoops_GCIHP->_hoops_ACP.weight_count, _hoops_HCAIR, _hoops_GCIHP->_hoops_ACP.weights);
				}
			}
			if (BIT (_hoops_AHAIR->_hoops_IIAIR->mask, _hoops_RCCRP)) {
				_hoops_GCIHP->_hoops_ACP._hoops_PCP = BIT (_hoops_AHAIR->_hoops_IIAIR->value, _hoops_RCCRP);
			}
		}
	}


	if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_PGRAP)) {
		_hoops_GRA alter &		_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

		_hoops_GCIHP->_hoops_IHRH.options ^= (_hoops_GCIHP->_hoops_IHRH.options ^ _hoops_AHAIR->_hoops_GIAAP) & _hoops_AHAIR->_hoops_SHAAP;

		if (BIT (_hoops_AHAIR->_hoops_SHAAP, _hoops_HIGRP))
			_hoops_GCIHP->_hoops_IHRH._hoops_ACGRP = _hoops_AHAIR->_hoops_IHRH._hoops_ACGRP;
		if (BIT (_hoops_AHAIR->_hoops_SHAAP, _hoops_AIGRP)) {
			_hoops_GCIHP->_hoops_IHRH.scale = _hoops_AHAIR->_hoops_IHRH.scale;
			_hoops_GCIHP->_hoops_IHRH.translate = _hoops_AHAIR->_hoops_IHRH.translate;
			if (_hoops_AHAIR->_hoops_IHRH.scale == 1.0f &&
				_hoops_AHAIR->_hoops_IHRH.translate == 0.0f)
				_hoops_GCIHP->_hoops_IHRH.options &= ~_hoops_AIGRP;
		}
		if (BIT (_hoops_AHAIR->_hoops_SHAAP, _hoops_PIGRP))
			_hoops_GCIHP->_hoops_IHRH.color = _hoops_AHAIR->_hoops_IHRH.color;
	}


	if (_hoops_AHAIR->_hoops_PRSI != null) {

		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_SGICA)) {
			for (int i = 0; i < _hoops_IGAIR; i++) {
				if (_hoops_AHAIR->_hoops_PRSI->_hoops_AISRP[i] != nr->_hoops_ARA->_hoops_PRSI._hoops_AISRP[i] ||
					_hoops_AHAIR->_hoops_PRSI->_hoops_PRPHA[i] != nr->_hoops_ARA->_hoops_PRSI._hoops_PRPHA[i] ||
					_hoops_AHAIR->_hoops_PRSI->_hoops_GHRGR[i] != nr->_hoops_ARA->_hoops_PRSI._hoops_GHRGR[i]) {
					_hoops_CRSHP = true;
					break;
				}
			}
			if (_hoops_AHAIR->_hoops_PRSI->bounding == null) {
				if (nr->_hoops_ARA->_hoops_PRSI.bounding != null)
					_hoops_CRSHP = true;
			}
			else if (HI_Compare_Bounding (
					_hoops_AHAIR->_hoops_PRSI->bounding,
					nr->_hoops_ARA->_hoops_PRSI.bounding))
				_hoops_CRSHP = true;
		}
		if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_SGICA)  &&
			(_hoops_CRSHP ||
			 _hoops_AHAIR->_hoops_PRSI->value != nr->_hoops_ARA->_hoops_PRSI.options ||
			 _hoops_AHAIR->_hoops_PRSI->_hoops_HISRP != nr->_hoops_ARA->_hoops_PRSI._hoops_HISRP ||
			 _hoops_AHAIR->_hoops_PRSI->_hoops_IISRP != nr->_hoops_ARA->_hoops_PRSI._hoops_IISRP ||
			 _hoops_AHAIR->_hoops_PRSI->_hoops_IRSH != nr->_hoops_ARA->_hoops_PRSI._hoops_IRSH ||
			 _hoops_AHAIR->_hoops_PRSI->_hoops_ARPHA != nr->_hoops_ARA->_hoops_PRSI._hoops_ARPHA ||
			 _hoops_AHAIR->_hoops_PRSI->_hoops_RHPHA != nr->_hoops_ARA->_hoops_PRSI._hoops_RHPHA ||
			 _hoops_AHAIR->_hoops_PRSI->tolerance != nr->_hoops_ARA->_hoops_PRSI.tolerance ||
			 _hoops_AHAIR->_hoops_PRSI->_hoops_SRHHR != nr->_hoops_ARA->_hoops_PRSI._hoops_SRHHR||
			 _hoops_AHAIR->_hoops_PRSI->_hoops_RCSRP != nr->_hoops_ARA->_hoops_PRSI._hoops_RCSRP)) {
			_hoops_GRA alter &		_hoops_GCIHP = nr.Modify()->_hoops_ARA.Modify();

			_hoops_GCIHP->_hoops_PRSI.options &= ~_hoops_AHAIR->_hoops_PRSI->mask;
			_hoops_GCIHP->_hoops_PRSI.options |= _hoops_AHAIR->_hoops_PRSI->value;

			if (ANYBIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_HRSRP)) {
				if (_hoops_GCIHP->_hoops_PRSI.options & _hoops_ARSRP) {
					_hoops_CRCP const *		_hoops_SRCP = _hoops_AHAIR->owner;
					Bounding const		_hoops_PCSHP = _hoops_SRCP->bounding;

					if (_hoops_PCSHP == null) {
						if (!BIT(dc->flags, _hoops_CPPHP))
							HE_ERROR (HEC_LOD, HES_BOUNDING_BOX,
								"LOD bounding volumes must be explicit if segment bounding volumes disabled");
					}
					else
						_hoops_GCIHP->_hoops_PRSI.bounding = _hoops_PCSHP._hoops_SCIS (&nr->transform_rendition->_hoops_IPH->data.elements[0][0]);
				}
				else if (_hoops_GCIHP->_hoops_PRSI.options & _hoops_PRSRP)
					_hoops_GCIHP->_hoops_PRSI.bounding = _hoops_AHAIR->_hoops_PRSI->bounding._hoops_SCIS (&nr->transform_rendition->_hoops_IPH->data.elements[0][0]);
			}
			if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_SSCRP))
				_hoops_GCIHP->_hoops_PRSI._hoops_IRSH = _hoops_AHAIR->_hoops_PRSI->_hoops_IRSH;
			if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_IGSRP))
				_hoops_GCIHP->_hoops_PRSI._hoops_ARPHA = _hoops_AHAIR->_hoops_PRSI->_hoops_ARPHA;
			if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_IASRP)) {
				for (int i = 0; i < _hoops_IGAIR; i++)
					_hoops_GCIHP->_hoops_PRSI._hoops_AISRP[i] = _hoops_AHAIR->_hoops_PRSI->_hoops_AISRP[i];
			}
			if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_ISCRP)) {
				for (int i = 0; i < _hoops_IGAIR; i++)
					_hoops_GCIHP->_hoops_PRSI._hoops_PRPHA[i] = _hoops_AHAIR->_hoops_PRSI->_hoops_PRPHA[i];
			}
			if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_IRSRP)) {
				for (int i = 0; i < _hoops_IGAIR; i++)
					_hoops_GCIHP->_hoops_PRSI._hoops_GHRGR[i] = _hoops_AHAIR->_hoops_PRSI->_hoops_GHRGR[i];
			}

			if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_CSCRP))
				_hoops_GCIHP->_hoops_PRSI._hoops_HISRP = _hoops_AHAIR->_hoops_PRSI->_hoops_HISRP;
			/* _hoops_PISH _hoops_RIIA _hoops_IIGR _hoops_PIRA _hoops_HIS _hoops_SR _hoops_IPS _hoops_RH _hoops_CISRP _hoops_PRGI _hoops_RPP _hoops_SCH'_hoops_GRI _hoops_HAR _hoops_CISI */
			if (BIT (_hoops_AHAIR->_hoops_PRSI->mask, _hoops_HASRP))
				_hoops_GCIHP->_hoops_PRSI._hoops_IISRP = _hoops_AHAIR->_hoops_PRSI->_hoops_IISRP;
			if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_GGSRP))
				_hoops_GCIHP->_hoops_PRSI._hoops_RHPHA = _hoops_AHAIR->_hoops_PRSI->_hoops_RHPHA;
			if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_AGSRP))
				_hoops_GCIHP->_hoops_PRSI.tolerance = _hoops_AHAIR->_hoops_PRSI->tolerance;
			if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_AGSRP))
				_hoops_GCIHP->_hoops_PRSI.tolerance = _hoops_AHAIR->_hoops_PRSI->tolerance;
			if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_GRSRP))
				_hoops_GCIHP->_hoops_PRSI._hoops_SRHHR = _hoops_AHAIR->_hoops_PRSI->_hoops_SRHHR;
			if (BIT (_hoops_AHAIR->_hoops_PRSI->value, _hoops_PASRP))
				_hoops_GCIHP->_hoops_PRSI._hoops_RCSRP = _hoops_AHAIR->_hoops_PRSI->_hoops_RCSRP;
		}
	}

	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_HPRAP)) {
		_hoops_ICP alter &	_hoops_HCSHP = nr.Modify()->_hoops_SCP.Modify();

		_hoops_HCSHP->_hoops_CSRS = _hoops_AHAIR->_hoops_CSRS;
	}

	if (BIT (_hoops_AHAIR->_hoops_PSHCA, _hoops_SRRAP) &&
		_hoops_AHAIR->_hoops_SRI != _hoops_RRGH->_hoops_SRI) {
		_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();
		_hoops_SHCRP				_hoops_ICSHP = _hoops_APIHP->_hoops_SRI ^ _hoops_AHAIR->_hoops_SRI;

		if (_hoops_AHAIR->owner != null && _hoops_RSIHP (_hoops_AHAIR->owner)) {
			_hoops_PHPGR (HEC_RENDERING, HES_NONWINDOWED_HSR,
						 "Use of \"hsr algorithm\" on segments containing geometry but without windows is not recommended",
						 Sprintf_P (null, "Segment is: '%p'", _hoops_AHAIR->owner));
		}

		_hoops_APIHP->_hoops_SRI = _hoops_AHAIR->_hoops_SRI;

		/*
		 * _hoops_PS _hoops_PAH _hoops_RGAR _hoops_ARP _hoops_RH _hoops_RIIRA _hoops_RPP _hoops_SR'_hoops_ASAR _hoops_CPIC _hoops_IS _hoops_SHH
		 * _hoops_GHGA _hoops_CCSHP _hoops_AARAR _hoops_GGR _hoops_RH _hoops_SRS _hoops_HGHC.  _hoops_IPCP _hoops_SCSHP
		 * _hoops_RRGR _hoops_CAPP _hoops_GRS _hoops_IRAA _hoops_PICP _hoops_IIGR _hoops_SGS _hoops_IGRH, _hoops_PPR _hoops_IGAPA _hoops_RH
		 * _hoops_RGSR _hoops_IIGR _hoops_RH _hoops_RIIRA _hoops_GAHPR.
		 */
		if (BIT (nr->_hoops_RCSHR, _hoops_CSGGR)) {
			if (BIT (_hoops_ICSHP, _hoops_SGAAP)) {
				if (BIT (_hoops_APIHP->_hoops_SRI, _hoops_SGAAP))
					nr.Modify()->_hoops_RCSHR |= _hoops_GSSHP;
				else
					nr.Modify()->_hoops_RCSHR &= ~_hoops_GSSHP;
			}

			if (BIT (_hoops_ICSHP, _hoops_RRAAP)) {
				if (BIT (_hoops_APIHP->_hoops_SRI, _hoops_RRAAP))
					nr.Modify()->_hoops_RCSHR |= _hoops_RSSHP;
				else
					nr.Modify()->_hoops_RCSHR &= ~_hoops_RSSHP;
			}

			if (BIT (_hoops_ICSHP, _hoops_SICI)) {
				if (ALLBITS(dc->_hoops_PGCC.flags, _hoops_ASSHP|_hoops_PSSHP)) {
					if (BIT (_hoops_APIHP->_hoops_SRI, _hoops_SICI))
						nr.Modify()->_hoops_RCSHR |= _hoops_GSSHP|_hoops_HSSHP;
					else
						nr.Modify()->_hoops_RCSHR &= ~(_hoops_GSSHP|_hoops_HSSHP);
				}
				else {
					if (BIT (_hoops_APIHP->_hoops_SRI, _hoops_SICI))
						_hoops_APIHP->_hoops_SRI = _hoops_PRAAP;

					nr.Modify()->_hoops_RCSHR &= ~(_hoops_GSSHP|_hoops_RSSHP);
				}
			}

			if (BIT (_hoops_ICSHP, _hoops_GAI)) {
				if (BIT (dc->_hoops_PGCC.flags, _hoops_ISSHP)) {
					if (BIT (_hoops_APIHP->_hoops_SRI, _hoops_GAI))
						nr.Modify()->_hoops_RCSHR |= _hoops_GSSHP;
					else
						nr.Modify()->_hoops_RCSHR &= ~_hoops_GSSHP;
				}
			}

			if (_hoops_APIHP->_hoops_SRI == _hoops_PRAAP)
				nr.Modify()->current &= ~_hoops_CSGGR;
		}

		/* _hoops_CSSHP _hoops_RGAIA _hoops_SHPH _hoops_RSH _hoops_SR _hoops_RGHH _hoops_AAPI */
	}

	if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_ISGAP) &&
		dc->_hoops_APHHP == null) {
		short		_hoops_SSSHP;

		if ((_hoops_SSSHP = (_hoops_AHAIR->_hoops_CHP.mask &
							 (nr->_hoops_IRR->_hoops_CHP ^
							  _hoops_AHAIR->_hoops_CHP.value))) != 0) {
			_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

			_hoops_APIHP->_hoops_CHP ^= _hoops_SSSHP;

			if (BIT(_hoops_APIHP->_hoops_CHP, _hoops_SHP) &&
				!BIT (nr->_hoops_RCSHR, _hoops_HSGGR))
				nr.Modify()->_hoops_RCSHR |= _hoops_HSGGR;

			if (BIT(_hoops_APIHP->_hoops_CHP, _hoops_CRAAP) &&
				!BIT (nr->_hoops_RCSHR, _hoops_ISGGR))
				nr.Modify()->_hoops_RCSHR |= _hoops_ISGGR;
		}
	}


	if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_CSHCA)) {
		int			_hoops_GGGIP;

		if ((_hoops_GGGIP = (_hoops_AHAIR->_hoops_SSHCA.mask &
							 (nr->_hoops_CPP->_hoops_PRH.options ^
							  _hoops_AHAIR->_hoops_SSHCA.value))) != 0) {
			nr.Modify()->_hoops_CPP.Modify()->_hoops_PRH.options ^= _hoops_GGGIP;
		}

		if (BIT (_hoops_AHAIR->_hoops_SSHCA.mask, _hoops_AAAAP) &&
			(_hoops_AHAIR->_hoops_SSHCA._hoops_SRI !=
			 nr->_hoops_CPP->_hoops_PRH._hoops_SRI)) {
			nr.Modify()->_hoops_CPP.Modify()->_hoops_PRH._hoops_SRI = _hoops_AHAIR->_hoops_SSHCA._hoops_SRI;
		}

		if (BIT (_hoops_AHAIR->_hoops_SSHCA.mask, _hoops_HAAAP) &&
			(_hoops_AHAIR->_hoops_SSHCA._hoops_RPAAP !=
			 nr->_hoops_CPP->_hoops_PRH._hoops_RPAAP)) {
			nr.Modify()->_hoops_CPP.Modify()->_hoops_PRH._hoops_RPAAP = _hoops_AHAIR->_hoops_SSHCA._hoops_RPAAP;
		}

		if (BIT (_hoops_AHAIR->_hoops_SSHCA.mask, _hoops_IAAAP) &&
			(_hoops_AHAIR->_hoops_SSHCA._hoops_APAAP !=
			 nr->_hoops_CPP->_hoops_PRH._hoops_APAAP)) {
			nr.Modify()->_hoops_CPP.Modify()->_hoops_PRH._hoops_APAAP = _hoops_AHAIR->_hoops_SSHCA._hoops_APAAP;
		}

		if (BIT (_hoops_AHAIR->_hoops_SSHCA.mask, _hoops_SAAAP) &&
			(BIT (_hoops_AHAIR->_hoops_SSHCA.value, _hoops_SAAAP) !=
			 nr->_hoops_CPP->_hoops_PRH._hoops_RGGIP)) {
			nr.Modify()->_hoops_CPP.Modify()->_hoops_PRH._hoops_RGGIP =
				BIT (_hoops_AHAIR->_hoops_SSHCA.value, _hoops_SAAAP);
		}

		if (BIT (_hoops_AHAIR->_hoops_SSHCA.mask, _hoops_RAAAP) &&
			(_hoops_AHAIR->_hoops_SSHCA.style !=
			 nr->_hoops_CPP->_hoops_PRH.style)) {
			_hoops_GCIR			_hoops_SCPHP;
			int								style;

			style = _hoops_AHAIR->_hoops_SSHCA.style;

			_hoops_SCPHP = nr.Modify()->_hoops_CPP.Modify();
			_hoops_SCPHP->_hoops_PRH.style = style;

			if (BIT (nr->_hoops_RCSHR, _hoops_AHIHP)) {
				switch (style) {
					case _hoops_AIII: {
						nr->_hoops_RCSHR &= ~_hoops_AHIHP;
						nr->current &= ~_hoops_AHIHP;
					}	break;

					case Transparency_STYLE_BLENDING: {
					}	break;

					case _hoops_GCPI: {
						nr->current |= _hoops_AHIHP;
						if (nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR < 1.0f) {
							nr->_hoops_IHA.Modify()->_hoops_CHA.Modify();
							HD_Setup_Screen_Door (nr);
						}
					}	break;
				}
			}
		}
	}




	if (BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HARAP)) {
		if (ANYBIT (nr->current | nr->_hoops_RCSHR,
					_hoops_CISHP | _hoops_RSSHP))
			nr.Modify()->_hoops_IRR.Modify()->_hoops_PPH &= ~_hoops_HARAP;
	}
	if ((BIT (_hoops_IRSHP ^ nr->_hoops_IRR->_hoops_PPH, _hoops_HARAP) ||
		 BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HARAP) && _hoops_SRSHP) &&
		(BIT(dc->_hoops_PGCC.flags, _hoops_IPPHP) || BIT(dc->flags, _hoops_CPPHP))) {
		_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

		if (!BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HARAP))
			_hoops_GGCC->_hoops_RHPHP = _hoops_AHPHP;
		else {
			((Display_Context alter *)dc)->_hoops_AGGIP = true;
			if (_hoops_GGCC->_hoops_PGGIP != _hoops_HHPHP)
				_hoops_GGCC->_hoops_RHPHP = _hoops_PHPHP;
			else
				_hoops_GGCC->_hoops_RHPHP = _hoops_HHPHP;
		}

		if (_hoops_GGCC->_hoops_SPH != null)
			HD_Downwind_Camera (nr, (Attribute *)_hoops_GGCC->_hoops_SPH);
	}

	if (dc->options._hoops_SIAH &&
		!BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HAI)) {
		_hoops_AHAH alter &		_hoops_PHAH = nr.Modify()->_hoops_ARA.Modify()->_hoops_IHRH;

		_hoops_PHAH.options = _hoops_CHRH | _hoops_HIGRP | _hoops_PIGRP;
		_hoops_PHAH._hoops_ACGRP = _hoops_CIGRP;
		_hoops_PHAH.color = _hoops_GPSR::_hoops_IAHHP;

		// _hoops_RHGS _hoops_SRSGR _hoops_CGH _hoops_PGPS _hoops_PHHR _hoops_SGGR...
		nr->_hoops_IRR.Modify()->_hoops_PPH |= (_hoops_HAI & ~_hoops_AHGI);
	}

	/* _hoops_RPP _hoops_SR _hoops_SIAS _hoops_SHH _hoops_IAHAR _hoops_GPP _hoops_PAR _hoops_PSAP _hoops_HGGIP _hoops_PHSPR,
	_hoops_SGS _hoops_CGH _hoops_CHASA _hoops_HISI _hoops_PSHA _hoops_CHR _hoops_ARP _hoops_GGR _hoops_RGR _hoops_CAGH */
	if (BIT (_hoops_AHAIR->_hoops_SHAAP, _hoops_CHRH))
		_hoops_HCHHP |= _hoops_HHIHP;

	return _hoops_HCHHP;
}


local void HD_Downwind_Heuristics(Net_Rendition alter & nr, _hoops_GHAIR const *_hoops_GIGC)
{
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_CGSP			_hoops_CCCIR = 0;
	short						_hoops_IGGIP = 0;

	if (BIT(dc->flags, _hoops_CPPHP)) {
		if (BIT (_hoops_GIGC->mask, _hoops_SICIA))
			if (nr->_hoops_IRR->_hoops_GCCIA !=
					_hoops_GIGC->_hoops_GCCIA)
				nr.Modify()->_hoops_IRR.Modify()->_hoops_GCCIA =
					_hoops_GIGC->_hoops_GCCIA;

		if (BIT (_hoops_GIGC->mask, _hoops_SRIRP)) {
			if (BIT (_hoops_GIGC->_hoops_CCIRP.mask, _hoops_HCIRP) &&
				nr->_hoops_IRR->_hoops_CCIRP._hoops_SPHPR !=
					_hoops_GIGC->_hoops_CCIRP._hoops_SPHPR ||
				BIT (_hoops_GIGC->_hoops_CCIRP.mask, _hoops_ICIRP) &&
				nr->_hoops_IRR->_hoops_CCIRP.polyline !=
					_hoops_GIGC->_hoops_CCIRP.polyline) {
				_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

				if (BIT (_hoops_GIGC->_hoops_CCIRP.mask, _hoops_HCIRP))
					_hoops_APIHP->_hoops_CCIRP._hoops_SPHPR =
						_hoops_GIGC->_hoops_CCIRP._hoops_SPHPR;
				if (BIT (_hoops_GIGC->_hoops_CCIRP.mask, _hoops_ICIRP))
					_hoops_APIHP->_hoops_CCIRP.polyline =
						_hoops_GIGC->_hoops_CCIRP.polyline;
			}
		}
		if (BIT (_hoops_GIGC->mask, _hoops_RPIRP))
			if (nr->_hoops_IRR->_hoops_GRCRP != _hoops_GIGC->_hoops_GRCRP)
				nr.Modify()->_hoops_IRR.Modify()->_hoops_GRCRP = _hoops_GIGC->_hoops_GRCRP;
	}

	if (!BIT (nr->transform_rendition->_hoops_SSPPP, _hoops_CGGIP) &&
		ANYBIT (_hoops_GIGC->mask & _hoops_GIGC->value, _hoops_HAIRP)) {
		nr.Modify()->_hoops_RCSHR |= _hoops_CSPPP;
		nr->transform_rendition.Modify()->_hoops_SSPPP = _hoops_SGGIP;
	}
	if (BIT (nr->transform_rendition->_hoops_SSPPP, _hoops_SGGIP) &&
		BIT (_hoops_GIGC->mask & _hoops_GIGC->value, _hoops_IAIRP))
		nr.Modify()->transform_rendition.Modify()->_hoops_SSPPP = _hoops_GRGIP;

	if (BIT (_hoops_GIGC->mask & _hoops_GIGC->value, _hoops_CAIRP)) {

		_hoops_GCIR alter &		_hoops_SCPHP = nr.Modify()->_hoops_CPP.Modify();

		for (int i=0; i<_hoops_ISIRP; i++) {
			if (BIT (_hoops_GIGC->_hoops_CSIRP, 1<<i))
				_hoops_SCPHP->_hoops_SSIRP[i] = _hoops_GIGC->_hoops_SSIRP[i];
		}

		_hoops_SCPHP->_hoops_GGCRP = _hoops_GIGC->_hoops_GGCRP;
		_hoops_SCPHP->_hoops_RGCRP = _hoops_GIGC->_hoops_RGCRP;
		_hoops_SCPHP->_hoops_AGCRP = _hoops_GIGC->_hoops_AGCRP;
	}

	_hoops_CCCIR = (nr->transform_rendition->heuristics ^ _hoops_GIGC->value) &
			  _hoops_GIGC->mask;

	if (BIT (_hoops_GIGC->mask, _hoops_APIRP)) {

		if (nr->_hoops_IRR->_hoops_RRCRP != _hoops_GIGC->_hoops_RRCRP ||
			nr->_hoops_IRR->_hoops_ARCRP != 0.0f) {

			_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();
			_hoops_APIHP->_hoops_RRCRP = _hoops_GIGC->_hoops_RRCRP;

			if (_hoops_APIHP->_hoops_RRCRP != 0)
				nr->flags |= _hoops_RRGIP;
			else
				nr->flags &= ~_hoops_RRGIP;

			// _hoops_IRAA _hoops_RH _hoops_AHPA _hoops_SR _hoops_HS _hoops_GCRHA
			if (_hoops_GIGC->_hoops_ARCRP > _hoops_APIHP->_hoops_ARCRP)
				_hoops_APIHP->_hoops_ARCRP = _hoops_GIGC->_hoops_ARCRP;
		}
	}

	if (BIT (_hoops_GIGC->mask, _hoops_PPIRP))
		if (nr->_hoops_IRR->_hoops_IRCRP != _hoops_GIGC->_hoops_IRCRP)
				nr.Modify()->_hoops_IRR.Modify()->_hoops_IRCRP = _hoops_GIGC->_hoops_IRCRP;

	if (BIT (_hoops_GIGC->mask, _hoops_RAIRP)) {
		if (BIT (_hoops_GIGC->_hoops_APH.mask & _hoops_GIGC->_hoops_APH.value, _hoops_SPIRP) &&
			(nr->_hoops_IRR->_hoops_ACIRP != _hoops_GIGC->_hoops_APH._hoops_ACIRP ||
			 nr->_hoops_IRR->_hoops_PCIRP != _hoops_GIGC->_hoops_APH._hoops_PCIRP)) {
			_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

			_hoops_APIHP->_hoops_ACIRP = _hoops_GIGC->_hoops_APH._hoops_ACIRP;
			_hoops_APIHP->_hoops_PCIRP = _hoops_GIGC->_hoops_APH._hoops_PCIRP;
		}

		if (BIT (_hoops_GIGC->_hoops_APH.mask & _hoops_GIGC->_hoops_APH.value, Heur_Culling_EXTENT) &&
			nr->_hoops_IRR->_hoops_GRGC != _hoops_GIGC->_hoops_APH._hoops_GRGC)
			nr.Modify()->_hoops_IRR.Modify()->_hoops_GRGC = _hoops_GIGC->_hoops_APH._hoops_GRGC;

		if (BIT (_hoops_GIGC->_hoops_APH.mask & _hoops_GIGC->_hoops_APH.value, _hoops_RIHS) &&
			nr->_hoops_IRR->_hoops_GCHS != _hoops_GIGC->_hoops_APH._hoops_GCHS)
			nr.Modify()->_hoops_IRR.Modify()->_hoops_GCHS = _hoops_GIGC->_hoops_APH._hoops_GCHS;

		if (BIT (_hoops_GIGC->_hoops_APH.mask & _hoops_GIGC->_hoops_APH.value, _hoops_RHIRP) &&
			nr->_hoops_IRR->_hoops_PCHS != _hoops_GIGC->_hoops_APH._hoops_PCHS)
			nr.Modify()->_hoops_IRR.Modify()->_hoops_PCHS = _hoops_GIGC->_hoops_APH._hoops_PCHS;

		if (BIT (_hoops_GIGC->_hoops_APH.mask & _hoops_GIGC->_hoops_APH.value, _hoops_HHIRP) &&
			nr->_hoops_IRR->_hoops_SHHS != _hoops_GIGC->_hoops_APH._hoops_SHHS)
			nr.Modify()->_hoops_IRR.Modify()->_hoops_SHHS = _hoops_GIGC->_hoops_APH._hoops_SHHS;

		if (BIT (_hoops_GIGC->_hoops_APH.mask & _hoops_GIGC->_hoops_APH.value, _hoops_AHIRP) &&
			nr->_hoops_IRR->_hoops_CIIRP != _hoops_GIGC->_hoops_APH._hoops_CIIRP)
			nr.Modify()->_hoops_IRR.Modify()->_hoops_CIIRP = _hoops_GIGC->_hoops_APH._hoops_CIIRP;

		_hoops_IGGIP = (nr->transform_rendition->_hoops_APH ^ _hoops_GIGC->_hoops_APH.value) &
						  _hoops_GIGC->_hoops_APH.mask;
	}
	if (BIT (_hoops_GIGC->_hoops_APH.mask & _hoops_GIGC->_hoops_APH.value, _hoops_GHIRP) &&
		(nr->_hoops_IRR->vector.x != _hoops_GIGC->_hoops_APH.vector.x ||
		 nr->_hoops_IRR->vector.y != _hoops_GIGC->_hoops_APH.vector.y ||
		 nr->_hoops_IRR->vector.z != _hoops_GIGC->_hoops_APH.vector.z)) {
		_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

		_hoops_APIHP->vector.x = _hoops_GIGC->_hoops_APH.vector.x;
		_hoops_APIHP->vector.y = _hoops_GIGC->_hoops_APH.vector.y;
		_hoops_APIHP->vector.z = _hoops_GIGC->_hoops_APH.vector.z;
	}
	if (BIT (_hoops_GIGC->_hoops_APH.mask & _hoops_GIGC->_hoops_APH.value, _hoops_PHIRP) &&
		nr->_hoops_IRR->_hoops_IIIRP != _hoops_GIGC->_hoops_APH._hoops_IIIRP)
		nr.Modify()->_hoops_IRR.Modify()->_hoops_IIIRP = _hoops_GIGC->_hoops_APH._hoops_IIIRP;

	if (!BIT(dc->flags, _hoops_CPPHP) &&
		BIT (_hoops_CCCIR, _hoops_RRIRP) &&
		!BIT (_hoops_GIGC->owner->_hoops_PHSI, _hoops_GISIR)) {
		char				options[4096];
		HI_Show_Heuristics (_hoops_GIGC, options, -1);
		_hoops_ARGIP (HEC_DRIVER, HES_IGNORED,
					 "Ignoring 'incremental updates' heuristic set below an active driver segment,",
					 Sprintf_P (null, "Segment is '%p', options are:", _hoops_GIGC->owner),
					 options);
		_hoops_CCCIR &= ~_hoops_RRIRP;
	}
	if (_hoops_CCCIR == 0 && _hoops_IGGIP == 0)
		return;

	_hoops_HHCR alter &		_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

	_hoops_GGCC->heuristics ^= _hoops_CCCIR;
	_hoops_GGCC->_hoops_APH ^= _hoops_IGGIP;

	if (BIT (_hoops_GGCC->heuristics, _hoops_SGIRP) &&
		ANYBIT (_hoops_GGCC->heuristics, _hoops_GPSA|
								 _hoops_SASA))
		_hoops_GGCC->flags |= _hoops_IGSP;
	else
		_hoops_GGCC->flags &= ~_hoops_IGSP;

	if (BIT (_hoops_CCCIR, _hoops_IRI)) {
		if (BIT (_hoops_GGCC->heuristics, _hoops_IRI)) {
			_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;

			nr->_hoops_RCSHR |= _hoops_CSGGR;

			if (BIT (_hoops_RRGH->_hoops_SRI, _hoops_SGAAP))
				nr->_hoops_RCSHR |= _hoops_GSSHP;
			if (BIT (_hoops_RRGH->_hoops_SRI, _hoops_RRAAP))
				nr->_hoops_RCSHR |= _hoops_RSSHP;

			if (BIT (_hoops_RRGH->_hoops_SRI, _hoops_SICI)) {
				if (ALLBITS(dc->_hoops_PGCC.flags, _hoops_ASSHP|_hoops_PSSHP)) {
					nr->_hoops_RCSHR |= _hoops_GSSHP|_hoops_HSSHP;
				}
				else {
					nr->_hoops_IRR.Modify()->_hoops_SRI = _hoops_PRAAP;
					nr->_hoops_RCSHR &= ~_hoops_GSSHP;
				}
			}
			if (BIT (_hoops_RRGH->_hoops_SRI, _hoops_GAI)) {
				if (BIT (dc->_hoops_PGCC.flags, _hoops_ISSHP)) {
					nr->_hoops_RCSHR |= _hoops_GSSHP;
				}
			}
		}
		else
			if (dc->_hoops_APHHP == null) {
				_hoops_PRGIP	_hoops_HRGIP = nr->_hoops_RCSHR & nr->current & _hoops_RSSHP;

				nr->_hoops_RCSHR &= ~_hoops_IRGIP;
				nr->_hoops_RCSHR |= _hoops_HRGIP;
			}

		/* _hoops_CSSHP _hoops_RGAIA _hoops_SHPH _hoops_RSH _hoops_SR _hoops_RGHH _hoops_AAPI */
	}

	if (dc->_hoops_APHHP == null) {
		if (BIT (_hoops_GGCC->_hoops_APH, _hoops_SPIRP) &&
			dc->_hoops_ACPGR->_hoops_CRGIP != nullroutine) {
			nr->_hoops_RCSHR |= _hoops_SRGIP;
		}
	}

	/*
	 * _hoops_GAGIP _hoops_RH "_hoops_PPR" _hoops_IIGR _hoops_RH _hoops_RHPP _hoops_CPHSR _hoops_IGRH _hoops_HIS _hoops_SR _hoops_GA'_hoops_RA
	 * _hoops_HPPR _hoops_IS _hoops_AA "_hoops_HHCI _hoops_IHCI" _hoops_CCA _hoops_SPSIR _hoops_SGS _hoops_RAGIP _hoops_GIPR
	 * _hoops_PIHHR _hoops_ASCA _hoops_PPR _hoops_APHSR _hoops_GHC. _hoops_GARP, _hoops_RGR _hoops_RPSAR
	 * _hoops_RGAR _hoops_IS _hoops_HIHH _hoops_GPP _hoops_RH _hoops_AAGIP.
	 */
	if (ANYBIT (_hoops_CCCIR, _hoops_HPIRP) &&
		BIT (nr->transform_rendition->heuristics, _hoops_RRIRP) &&
		!BIT(dc->_hoops_PGCC.flags, _hoops_GIHSR) &&
		!BIT(dc->flags, _hoops_GPHHP)) {

		if (ANYBIT (_hoops_GGCC->heuristics, _hoops_HPIRP)) {
			nr->_hoops_RCSHR |= _hoops_CRSI;
			if (dc->_hoops_SHPGR == QMoves_Spriting ||
				((_hoops_GGCC->heuristics & _hoops_HPIRP) == _hoops_IRIRP))
				nr->_hoops_RCSHR |= _hoops_SRSI;
			else
				nr->_hoops_RCSHR &= ~_hoops_SRSI;

			if (!BIT(dc->_hoops_PGCC.flags, _hoops_PAGIP)) {
				nr->_hoops_RCSHR &= ~_hoops_SRSI;
				//_hoops_RPP _hoops_RHAC _hoops_HAGIP _hoops_IH _hoops_IAGIP _hoops_PPR _hoops_GA'_hoops_RA _hoops_HGCR _hoops_SCH, _hoops_AA _hoops_IHIR _hoops_HGISR
				if ((_hoops_GGCC->heuristics & _hoops_HPIRP) == _hoops_IRIRP)
					nr->_hoops_RCSHR &= ~_hoops_CRSI;
			}
			if (BIT(dc->_hoops_PGCC.flags, _hoops_GIHSR))
				nr->_hoops_RCSHR &= ~(_hoops_CRSI|_hoops_SRSI);
		}
		else
			nr->_hoops_RCSHR &= ~(_hoops_CRSI|_hoops_SRSI);
	}
}

GLOBAL_FUNCTION void HD_Downwind_Rendition (
	Net_Rendition alter &	nr,
	Attribute const *		_hoops_HPPGR,
	_hoops_ACHR				_hoops_RCGC,
	bool					_hoops_CAGIP) {
	_hoops_SSAGR(_hoops_HPPGR);
	Display_Context alter *	dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_PIGRA			_hoops_SAGIP;
	_hoops_PIGRA			_hoops_GPGIP;
	_hoops_PIGRA *		_hoops_PCGS = null;
	_hoops_PIGRA *		_hoops_CIIAA = null;
	bool					_hoops_RPGIP = false;
	int						_hoops_HCHHP = _hoops_ICHHP;

	// _hoops_AHGHR _hoops_IRS _hoops_HIGR _hoops_IIGR _hoops_AIRC, _hoops_CAHP _hoops_IRS _hoops_CCAH _hoops_GCHRR _hoops_IPP

	// _hoops_GAAP _hoops_PGHGR _hoops_APGIP _hoops_CAPP, _hoops_PAR _hoops_CISI _hoops_ARIPR _hoops_HII _hoops_ARRS, _hoops_HIS _hoops_HHSA _hoops_HGAGA _hoops_IIGR _hoops_HCR _hoops_AIRC
	// _hoops_HRII _hoops_HSAR _hoops_SAHR _hoops_AGAP _hoops_IRPR _hoops_IS _hoops_RH _hoops_SSSHR _hoops_CPAP _hoops_CSSC
	// _hoops_IPSH _hoops_SHR _hoops_AA _hoops_HPGP _hoops_GHPHP _hoops_HIS _hoops_RHPP-_hoops_PAPA _hoops_IPP _hoops_HRGR _hoops_APRAR
	bool _hoops_PPGIP = (BIT(_hoops_RCGC, _hoops_AHHGP) || BIT(nr->flags, _hoops_HRSHP) || BIT(dc->flags, _hoops_CPPHP));

	if (_hoops_PPGIP)
		_hoops_RCGC |= _hoops_CAHGP&_hoops_IRHGP;

	/* _hoops_HSPP _hoops_CCA _hoops_SGHS _hoops_GCIAA _hoops_HII _hoops_ARRS */
	_hoops_PCGS = &nr->_hoops_IRR->locks;

	/* _hoops_RRP _hoops_IS _hoops_ISPR _hoops_IH _hoops_RCIAA _hoops_ACIAA _hoops_RSIH, _hoops_IS _hoops_CGIC
	** _hoops_IGH _hoops_PAR _hoops_HAR _hoops_PA _hoops_ARPP _hoops_SCH (_hoops_SHCAR, _hoops_PCIAA) _hoops_GHCA _hoops_SHH _hoops_IGI _hoops_HCIAA */
	/* _hoops_GACC _hoops_RGHH _hoops_AGIR _hoops_IIGR _hoops_IRGH _hoops_HAIR _hoops_ARCR _hoops_ARI _hoops_HIS _hoops_SGS _hoops_IRS _hoops_HAIR-_hoops_HPP-_hoops_CIHA _hoops_GGR
	** _hoops_IRS _hoops_IAHA _hoops_PSAP _hoops_ARI _hoops_GRS _hoops_SHH _hoops_ARP _hoops_CIAH */
	Attribute const	*		_hoops_HPGIP = _hoops_HPPGR;

	do {
		_hoops_SSAGR(_hoops_HPPGR->next);

		if (_hoops_HPPGR->type > _hoops_IAAA (_hoops_CPPIR, HK_RENDERING_OPTIONS, HK_COLOR_MAP, _hoops_HAAIR))
			break;

		switch (_hoops_HPPGR->type) {
			case _hoops_CPPIR: {
				_hoops_SPPIR const *	_hoops_GHPIR = (_hoops_SPPIR const *)_hoops_HPPGR;
				
				if (HOOPS_WORLD->_hoops_PCIIR != 0 &&
					BIT(_hoops_RCGC, _hoops_CPHGP)) {

					if (_hoops_GHPIR->count > 0) {
						_hoops_ISHHP alter &	_hoops_RHIHP = nr.Modify()->_hoops_ASIR.Modify();

						int	count = HOOPS_WORLD->_hoops_AGCAA / 32;

						if (_hoops_RHIHP->conditions._hoops_RCHA == null) {
							POOL_ZALLOC_ARRAY (_hoops_RHIHP->conditions._hoops_RCHA, count, unsigned int, dc->memory_pool);
							_hoops_RHIHP->conditions.count = count;
						}
						else if (_hoops_RHIHP->conditions.count < count) {
							unsigned int *	_hoops_IPGIP = _hoops_RHIHP->conditions._hoops_RCHA;
							int				_hoops_IRCSA = _hoops_RHIHP->conditions.count;

							POOL_ZALLOC_ARRAY (_hoops_RHIHP->conditions._hoops_RCHA, count, unsigned int, dc->memory_pool);
							_hoops_AIGA (_hoops_IPGIP, _hoops_IRCSA, unsigned int, _hoops_RHIHP->conditions._hoops_RCHA);
							FREE_ARRAY (_hoops_IPGIP, _hoops_IRCSA, unsigned int);
							_hoops_RHIHP->conditions.count = count;
						}

						_hoops_HSIAA (_hoops_RHIHP->conditions._hoops_RCHA, _hoops_GHPIR->_hoops_SGCAA, _hoops_GHPIR->count*sizeof(unsigned int));
						_hoops_ISIAA (_hoops_RHIHP->conditions._hoops_RCHA, _hoops_GHPIR->values, _hoops_GHPIR->count*sizeof(unsigned int));

						if (!_hoops_RHIHP->conditions._hoops_CPGIP)
							_hoops_RHIHP->conditions._hoops_CPGIP = POOL_NEW(dc->memory_pool, _hoops_SPGIP)(dc->memory_pool);

						_hoops_PRRH(_hoops_GHPIR);
						_hoops_RHIHP->conditions._hoops_CPGIP->AddFirst(_hoops_GHPIR);
#if 0
						for (int i=0; i<_hoops_GHPIR->count; i++) {
							unsigned int	mask = _hoops_GHPIR->_hoops_SGCAA[i];
							unsigned int	value = _hoops_GHPIR->values[i];
							unsigned int	_hoops_IPGIP = _hoops_RHIHP->conditions._hoops_RCHA[i];
							int				index = i * 32;

							while (mask != 0) {

								if ((mask & 1) != 0 && ((value^_hoops_IPGIP) & 1) != 0) {

									if ((value & 1) != 0)
										_hoops_PRRH (HOOPS_WORLD->_hoops_PCIIR[index]);
									else 
										_hoops_HPRH (HOOPS_WORLD->_hoops_PCIIR[index]);
								}

								mask >>= 1;
								value >>= 1;
								_hoops_IPGIP >>= 1;
								++index;
							}
						}
#endif
					}

					if (_hoops_GHPIR->_hoops_ACPGR != null) {

						_hoops_ISHHP alter &	_hoops_RHIHP = nr.Modify()->_hoops_ASIR.Modify();

						_hoops_PCACA *	_hoops_HCACA = _hoops_RHIHP->conditions._hoops_ACPGR;
						_hoops_PCACA *	_hoops_GHGIP = _hoops_HCACA;

						_hoops_RHIHP->conditions._hoops_ACPGR = HI_Copy_Conditional_Actions(_hoops_GHPIR->_hoops_ACPGR);
		
						while (_hoops_HCACA != null) {

							_hoops_PCACA *	_hoops_GSACA = _hoops_RHIHP->conditions._hoops_ACPGR;
							bool					_hoops_RHGIP = true;

							while (_hoops_GSACA != null) {
								if (_hoops_GSACA->flags == _hoops_HCACA->flags && 
									_hoops_GSACA->type == _hoops_HCACA->type && 
									_hoops_GSACA->condition.count == _hoops_HCACA->condition.count &&
									EQUAL_MEMORY (_hoops_GSACA->condition._hoops_ASACA, _hoops_GSACA->condition.count*sizeof(int), _hoops_HCACA->condition._hoops_ASACA)) {
										_hoops_RHGIP = false;
										break;
								}
								_hoops_GSACA = _hoops_GSACA->next;
							}

							if (_hoops_RHGIP) {
								ZALLOC(_hoops_GSACA, _hoops_PCACA);
								HI_Copy_Conditional (&_hoops_HCACA->condition, &_hoops_GSACA->condition);
								_hoops_GSACA->flags = _hoops_HCACA->flags;
								_hoops_GSACA->type = _hoops_HCACA->type;

								_hoops_GSACA->next = _hoops_RHIHP->conditions._hoops_ACPGR;
								_hoops_RHIHP->conditions._hoops_ACPGR = _hoops_GSACA;
							}

							_hoops_HCACA = _hoops_HCACA->next;
						}

						if (_hoops_GHGIP != null)
							HI_Free_Conditional_Actions(_hoops_GHGIP);

						nr->flags |= _hoops_AHGIP;
					}
					else if (_hoops_GHPIR->_hoops_SGCAA && nr->_hoops_ASIR->conditions._hoops_ACPGR != null)
						nr.Modify()->flags |= _hoops_AHGIP;
	
				}
			}	break;

			case HK_RENDERING_OPTIONS: {
				_hoops_RHAIR const	*	_hoops_AHAIR = (_hoops_RHAIR const *)_hoops_HPPGR;

				if (_hoops_AHAIR->locks != null) {

					if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_GSIAA)) {
						_hoops_GRGH const &	_hoops_RRGH = nr->_hoops_IRR;
						_hoops_PIGRA			_hoops_PHGIP;

						_hoops_CIIAA = &_hoops_GPGIP;
						/* _hoops_PA _hoops_HSGRA _hoops_HRGR _hoops_HCAGR _hoops_ASIAA _hoops_HCIAA */
						_hoops_RSAI (&_hoops_AHAIR->locks->normal.mask, _hoops_PIGRA, _hoops_CIIAA);
						// _hoops_HIH _hoops_HAR _hoops_PA _hoops_GRGA _hoops_ARP _hoops_IS _hoops_SSPC
						_hoops_HSIAA (_hoops_CIIAA, &_hoops_RRGH->_hoops_HHGIP, sizeof (_hoops_PIGRA));


						_hoops_PCGS = &_hoops_SAGIP;
						_hoops_RSAI (&nr->_hoops_IRR->locks, _hoops_PIGRA, _hoops_PCGS);

						/* _hoops_HASC _hoops_CCAH _hoops_AAHS _hoops_HRP */
						_hoops_HSIAA (_hoops_PCGS, _hoops_CIIAA, sizeof (_hoops_PIGRA));
						/* _hoops_PIASR _hoops_HRGR _hoops_PA _hoops_SR _hoops_HHGC _hoops_IS _hoops_AAHS, _hoops_ACCHA _hoops_GII _hoops_SR _hoops_SPGA'_hoops_RA _hoops_PHRH _hoops_IS _hoops_AGRP */
						_hoops_RSAI (&_hoops_AHAIR->locks->normal.value, _hoops_PIGRA, &_hoops_PHGIP);
						_hoops_HSIAA (&_hoops_PHGIP, &_hoops_RRGH->_hoops_HHGIP, sizeof (_hoops_PIGRA));

						_hoops_ISIAA (_hoops_PCGS, &_hoops_PHGIP, sizeof (_hoops_PIGRA));

						/* _hoops_PPR _hoops_ARP _hoops_GPP _hoops_IPP */
						if (!EQUAL_MEMORY (_hoops_PCGS, sizeof (_hoops_PIGRA), &_hoops_RRGH->locks)) {
							_hoops_GRGH alter &	_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

							_hoops_RSAI (_hoops_PCGS, _hoops_PIGRA, &_hoops_APIHP->locks);
						}

						/* _hoops_IH _hoops_IRGH _hoops_HCGC _hoops_ARP _hoops_RGR _hoops_IS _hoops_SRCH _hoops_CSIAA '_hoops_PCPAR _hoops_HIH _hoops_HCIAA _hoops_ASIAA' */
						_hoops_HSIAA (_hoops_PCGS, _hoops_CIIAA, sizeof (_hoops_PIGRA));
					}
					if (BIT (_hoops_AHAIR->_hoops_SCIAA, _hoops_RGRAP)) {
						_hoops_GRGH alter &	_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

						// _hoops_AGCR _hoops_SAHR _hoops_RARHR -- _hoops_RPSI _hoops_PAH _hoops_HAR _hoops_HHSP
						_hoops_ISIAA (&_hoops_APIHP->_hoops_HHGIP, &_hoops_AHAIR->locks->_hoops_SACRP.value, sizeof (_hoops_PIGRA));
					}
				}

				/* _hoops_GCAC _hoops_AAP _hoops_CGH _hoops_SHH _hoops_SRS, _hoops_HIH _hoops_AA _hoops_RGR _hoops_ARI _hoops_GGR _hoops_AGIR _hoops_SCH _hoops_SHPH */
				if (!BIT (_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_RENDERING_OPTIONS)) &&
					BIT (_hoops_AHAIR->_hoops_SCIAA & _hoops_AHAIR->_hoops_RSIAA, _hoops_AGICA) &&
					_hoops_AHAIR->_hoops_PGICA != _hoops_GCAAP) {
					_hoops_ISGI		temp;

					temp._hoops_RRHH = _hoops_RSPCR;

					if (ANYBIT (_hoops_AHAIR->_hoops_PGICA, _hoops_ACAAP)) {
						_hoops_SGCC const &		_hoops_HSGA = nr->transform_rendition->_hoops_IPH;

						if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_CIAAP)) {
							HI_Copy_Matrix (&_hoops_HSGA->data, &temp.matrix);
							if (!BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_IIAAP)) {
								HI_Normalize ((Vector *)&temp.matrix.elements[0][0]);
								HI_Normalize ((Vector *)&temp.matrix.elements[1][0]);
								HI_Normalize ((Vector *)&temp.matrix.elements[2][0]);
							}
							temp.matrix.elements[3][0] =
								temp.matrix.elements[3][1] =
									temp.matrix.elements[3][2] = 0.0f;
							HI_Validate_Matrix_Adjoint (&temp.matrix);
							_hoops_AIGA (&temp.matrix._hoops_APRA->data.elements[0][0], 16, float,
										 &temp.matrix.elements[0][0]);
							/* _hoops_RSGA _hoops_IHGIP _hoops_CHGIP, _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_ASSP'_hoops_RA _hoops_IHSH _hoops_PRAR _hoops_GIR */
							temp.matrix.flags &= ~_hoops_HASA;
							temp.matrix._hoops_CPH = 0.0f;

							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
						else if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_IIAAP)) {
							float			_hoops_PIIH, _hoops_HIIH, _hoops_SHGIP;

							_hoops_PIIH = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->data.elements[0][0]);
							_hoops_HIIH = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->data.elements[1][0]);
							_hoops_SHGIP = (float)HI_Compute_Vector_Length ((Vector const *)&_hoops_HSGA->data.elements[2][0]);

							if (_hoops_PIIH == 0.0f)
								_hoops_PIIH = 1.0f;
							if (_hoops_HIIH == 0.0f)
								_hoops_HIIH = 1.0f;
							if (_hoops_SHGIP == 0.0f)
								_hoops_SHGIP = 1.0f;

							HI_Figure_Scale_Matrix (1.0f / _hoops_PIIH, 1.0f / _hoops_HIIH, 1.0f / _hoops_SHGIP, &temp.matrix);
							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
						if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_SIAAP)) {
							HI_Ident_Matrix (&temp.matrix);
							temp.matrix.elements[3][0] = -_hoops_HSGA->data.elements[3][0];
							temp.matrix.elements[3][1] = -_hoops_HSGA->data.elements[3][1];
							temp.matrix.elements[3][2] = -_hoops_HSGA->data.elements[3][2];
							temp.matrix._hoops_RAGR = _hoops_PRICR;
							if (temp.matrix.elements[3][2] != 0.0f)
								temp.matrix._hoops_RAGR |= _hoops_RRICR;
							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
					}

					if (ANYBIT (_hoops_AHAIR->_hoops_PGICA, _hoops_RCAAP)) {
						_hoops_HHRA const *		_hoops_SPH;

						_hoops_SPH = nr->transform_rendition->_hoops_SPH;

						if (BIT (_hoops_AHAIR->_hoops_PGICA,
								 _hoops_HIAAP)) {
							/* _hoops_RRP _hoops_IS _hoops_RGHH _hoops_RGR _hoops_SPHR _hoops_PGGA _hoops_SR _hoops_HHGC _hoops_SCH _hoops_IS *_hoops_GCIS* _hoops_GII _hoops_IRGH _hoops_PRGIA */
							_hoops_RPGIP = true;
						}
						if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_PIAAP)) {
							HI_Ident_Matrix (&temp.matrix);
							temp.matrix.elements[3][0] = _hoops_SPH->target.x;
							temp.matrix.elements[3][1] = _hoops_SPH->target.y;
							temp.matrix.elements[3][2] = _hoops_SPH->target.z;
							temp.matrix._hoops_RAGR = _hoops_PRICR;
							if (temp.matrix.elements[3][2] != 0.0f)
								temp.matrix._hoops_RAGR |= _hoops_RRICR;
							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
						if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_AIAAP)) {
							HI_Ident_Matrix (&temp.matrix);
							temp.matrix.elements[0][0] = _hoops_SPH->_hoops_CRSS.x;
							temp.matrix.elements[0][1] = _hoops_SPH->_hoops_CRSS.y;
							temp.matrix.elements[0][2] = _hoops_SPH->_hoops_CRSS.z;
							temp.matrix.elements[1][0] = _hoops_SPH->up_vector.x;
							temp.matrix.elements[1][1] = _hoops_SPH->up_vector.y;
							temp.matrix.elements[1][2] = _hoops_SPH->up_vector.z;
							temp.matrix.elements[2][0] = _hoops_SPH->_hoops_IIPCR.x;
							temp.matrix.elements[2][1] = _hoops_SPH->_hoops_IIPCR.y;
							temp.matrix.elements[2][2] = _hoops_SPH->_hoops_IIPCR.z;
							temp.matrix._hoops_CPH = 1.0f;
							temp.matrix._hoops_RAGR = _hoops_GRICR |
											_hoops_RRICR;

							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
						if (BIT (_hoops_AHAIR->_hoops_PGICA, _hoops_RIAAP)) {
							float			scale;

							scale = _hoops_SPH->_hoops_SSPA;
							if (_hoops_SPH->_hoops_CSIH != 1.0f && _hoops_SPH->_hoops_CSIH < nr->_hoops_SAIR->_hoops_CSIH && _hoops_SPH->projection != _hoops_SSIH)
								scale*= (nr->_hoops_SAIR->_hoops_CSIH / _hoops_SPH->_hoops_CSIH);

							scale = scale / 2.0f;

							HI_Figure_Scale_Matrix (scale, scale, scale, &temp.matrix);
							HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
						}
					}
				}

			}	break;

			case HK_COLOR_MAP: {
				if (!BIT(dc->flags, _hoops_IRSI) &&
					!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_COLOR_MAP)))
					HD_Downwind_Color_Map (nr, _hoops_HPPGR);
			}	break;

			case _hoops_HAAIR: {
				_hoops_IAAIR const *			_hoops_CAAIR = (_hoops_IAAIR const *)_hoops_HPPGR;

				if (_hoops_CAAIR->count > 0) {
					_hoops_GPAIR *					_hoops_GIGIP;
					int *							new_keys;
					int								_hoops_RGCCA;

					_hoops_RIGIP alter &	_hoops_AIGIP = nr.Modify()->_hoops_PIGIP.Modify();

					_hoops_RGCCA = _hoops_AIGIP->count + _hoops_CAAIR->count;

					POOL_ZALLOC_ARRAY_CACHED (_hoops_GIGIP, _hoops_RGCCA, _hoops_GPAIR, dc->memory_pool);
					POOL_ALLOC_ARRAY_CACHED (new_keys, _hoops_RGCCA, Integer32, dc->memory_pool);

					for (int i=0; i<_hoops_CAAIR->count; ++i)
						_hoops_GIGIP[i] = _hoops_CAAIR->_hoops_SAAIR[i];
					_hoops_AIGA (_hoops_CAAIR->keys, _hoops_CAAIR->count, Integer32, new_keys);

					if (_hoops_AIGIP->count) {
						// _hoops_PIP, _hoops_HIGIP _hoops_AGCR
						_hoops_AIGA (_hoops_AIGIP->_hoops_SAAIR, _hoops_AIGIP->count, _hoops_GPAIR, &_hoops_GIGIP[_hoops_CAAIR->count]);
						FREE_ARRAY (_hoops_AIGIP->_hoops_SAAIR, _hoops_AIGIP->count, _hoops_GPAIR);

						_hoops_AIGA (_hoops_AIGIP->keys, _hoops_AIGIP->count, Integer32, &new_keys[_hoops_CAAIR->count]);
						FREE_ARRAY (_hoops_AIGIP->keys, _hoops_AIGIP->count, Integer32);
					}

					_hoops_AIGIP->_hoops_SAAIR = _hoops_GIGIP;
					_hoops_AIGIP->keys = new_keys;
					_hoops_AIGIP->count = _hoops_RGCCA;
				}
			}	break;

		}
	} while ((_hoops_HPPGR = _hoops_HPPGR->next) != null && _hoops_CAGIP);

	_hoops_HPPGR = _hoops_HPGIP;
	_hoops_SSAGR(_hoops_HPPGR);

	do {
		_hoops_SSAGR(_hoops_HPPGR->next);

		switch (_hoops_HPPGR->type) {

		/* (_hoops_SRCH _hoops_RIHH _hoops_RPGP _hoops_HPGR _hoops_PRPC) */
		case _hoops_GRAIR:
		case HK_USER_VALUE: {
		}	break;

		case HK_USER_OPTIONS: {
			if (!BIT(dc->flags, _hoops_IRSI) &&
				_hoops_PPGIP &&
				!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_USER_OPTIONS))) {
				_hoops_HPPIR const *	_hoops_IPPIR = (_hoops_HPPIR const *)_hoops_HPPGR;

				int _hoops_RHSAA = 0;
				int _hoops_IIGIP = 0;

				if (_hoops_IPPIR->_hoops_AGGSA)
					_hoops_RHSAA = _hoops_IPPIR->_hoops_AGGSA->Count();

				if (_hoops_IPPIR->_hoops_IGGSA)
					_hoops_IIGIP = _hoops_IPPIR->_hoops_IGGSA->Count();

				if (_hoops_RHSAA > 0 || _hoops_IIGIP > 0){
					_hoops_CIGIP _hoops_SIGIP = nr.Modify()->_hoops_GCGIP.Modify();

					if (!_hoops_SIGIP->_hoops_IGGSA)
						_hoops_SIGIP->_hoops_IGGSA = POOL_NEW(dc->memory_pool, _hoops_CGGSA)(dc->memory_pool);

					if (_hoops_IIGIP > 0) {
						_hoops_HPPIR const *	_hoops_RCGIP;

						_hoops_CGGSA::UniqueCursor *	uc = _hoops_IPPIR->_hoops_IGGSA->GetUniqueCursor();

						while((_hoops_RCGIP = uc->Peek()) != null) {
							ASSERT(_hoops_RCGIP->_hoops_IGGSA == null);
							_hoops_PRRH(_hoops_RCGIP);
							_hoops_SIGIP->_hoops_IGGSA->AddFirst(_hoops_RCGIP);
							uc->Advance();
						}

						delete uc;
					}

					if (_hoops_RHSAA > 0) {
						_hoops_PRRH(_hoops_IPPIR);
						_hoops_SIGIP->_hoops_IGGSA->AddFirst(_hoops_IPPIR);
					}
				}
			}
		}	break;

		case HK_STYLE:	if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_STYLE))) {
#ifndef DISABLE_STYLE_SEGMENT
			Style const *		style = (Style const *)_hoops_HPPGR;
			_hoops_CRCP const *		_hoops_ACSR = style->_hoops_IGRPR;

			if (_hoops_ACSR == null) {
				// _hoops_ACGIP _hoops_IAHA
				_hoops_GPAIR _hoops_PCGIP;

				for (int i=0; i<nr->_hoops_PIGIP->count; i++) {
					if (nr->_hoops_PIGIP->keys[i] == style->_hoops_PCSCA) {
						if (!_hoops_RAHSR(style->_hoops_SGAIR,  nr->_hoops_PIGIP->_hoops_SAAIR[i]->name))
							continue;
						_hoops_PCGIP = nr->_hoops_PIGIP->_hoops_SAAIR[i];
						break;
					}
				}
				if (!_hoops_PCGIP) {
					HE_WARNING (HEC_STYLE, HES_NOT_AVAILABLE,
						Sprintf_N (null, "Requested named style '%n' not found", &style->_hoops_SGAIR));
				}
				else 
					_hoops_ACSR = _hoops_PCGIP->segment;
			}

			if (_hoops_ACSR && _hoops_ACSR->_hoops_IPPGR &&
				(style->condition.count == 0 ||
				 HI_Condition_Passed (nr->_hoops_ASIR->conditions.count,
									 nr->_hoops_ASIR->conditions._hoops_RCHA,
									 &style->condition))) {

				if (!BIT (_hoops_ACSR->_hoops_RCGC, _hoops_RHHGP))	// _hoops_IHGP!
					HD_Downwind_Rendition (nr, _hoops_ACSR->_hoops_IPPGR, _hoops_RCGC, true);
				else {
					_hoops_PIGRA			_hoops_HCGIP;

					_hoops_RSAI (&nr->_hoops_IRR->locks, _hoops_PIGRA, &_hoops_HCGIP);

					HD_Downwind_Rendition (nr, _hoops_ACSR->_hoops_IPPGR, _hoops_RCGC, true);

					// _hoops_IRHH _hoops_RCRR _hoops_SGHS _hoops_CHR _hoops_GH-_hoops_IS-_hoops_ICGIP
					_hoops_GRGH alter &	_hoops_RRGH = nr->_hoops_IRR;

					// _hoops_SRS, _hoops_IRHH _hoops_RCRR _hoops_SR _hoops_HS _hoops_IRGH _hoops_PIH _hoops_IS _hoops_HPSI _hoops_CCA
					_hoops_PCGS = &_hoops_SAGIP;
					_hoops_RSAI (&_hoops_RRGH->locks, _hoops_PIGRA, _hoops_PCGS);

					if (_hoops_CIIAA != null) {
						// _hoops_SPS, _hoops_PA _hoops_HCIAA _hoops_ASIAA _hoops_IGICR _hoops_ASIAA
						_hoops_HSIAA (_hoops_PCGS, _hoops_CIIAA, sizeof (_hoops_PIGRA));

						// _hoops_CASI _hoops_IH _hoops_RH _hoops_HGCAA _hoops_CAPP
						_hoops_IGCAA (&_hoops_HCGIP, _hoops_CIIAA, sizeof (_hoops_PIGRA));
					}
					// _hoops_HGCAA _hoops_PA _hoops_SR _hoops_PCPAR _hoops_SGS _hoops_RH _hoops_IAHA _hoops_GHCA _hoops_HS _hoops_ASIAA */
					_hoops_ISIAA (&_hoops_HCGIP, _hoops_PCGS, sizeof (_hoops_PIGRA));

					// _hoops_PPR _hoops_PRIA _hoops_IS _hoops_CCGIP _hoops_RPP _hoops_HAGH
					if (!EQUAL_MEMORY (&_hoops_HCGIP, sizeof (_hoops_PIGRA), &_hoops_RRGH->locks)) {
						_hoops_GRGH alter &	_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

						_hoops_RSAI (&_hoops_HCGIP, _hoops_PIGRA, &_hoops_APIHP->locks);
					}
				}
			}
#endif
		}	break;

		case HK_CALLBACK:	if (!BIT(dc->flags, _hoops_IRSI) &&
								!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_CALLBACK))) {
			//_hoops_AGHR(_hoops_SCGIP == _hoops_IHPR); _hoops_IRAP _hoops_ASGC _hoops_AA _hoops_HAR _hoops_ARP _hoops_RIP
#ifndef DISABLE_CALLBACKS
			HD_Downwind_Callback (nr, (_hoops_GCHIR const *)_hoops_HPPGR);
#endif
		}	break;

		case HK_CLIP_REGION:	if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_CLIP_REGION))) {
			_hoops_IRAIR const *			_hoops_CRAIR = (_hoops_IRAIR const *)_hoops_HPPGR;
			_hoops_HHCR alter &	_hoops_GGCC = nr.Modify()->transform_rendition.Modify();

			if (_hoops_CRAIR->count > 0) {
				DC_Point				buffer[32];
				DC_Point				*points = buffer;
				int						count = _hoops_CRAIR->count;
				float const				*mat;
				float					_hoops_IHPIA[4][4];
				_hoops_ASHH alter *_hoops_PPGGA;

				if (count > _hoops_GGAPR(buffer))
					POOL_ALLOC_ARRAY_CACHED (points, count, DC_Point, dc->memory_pool);

				if (BIT (_hoops_CRAIR->flags, _hoops_SPAGA)) {
					if (!BIT (_hoops_GGCC->flags, _hoops_IGCC))
						HD_Validate_World_To_Screen (nr);
					mat = &_hoops_GGCC->_hoops_CGCC->data.elements[0][0];
				}
				else {
					_hoops_CGRA const &		_hoops_SGRA = nr->_hoops_SAIR;

					HI_Compute_Identity_Matrix (&_hoops_IHPIA[0][0]);

					_hoops_IHPIA[0][0] = 0.5f * (_hoops_SGRA->_hoops_PHRA.right - _hoops_SGRA->_hoops_PHRA.left);
					_hoops_IHPIA[1][1] = 0.5f * (_hoops_SGRA->_hoops_PHRA.top  - _hoops_SGRA->_hoops_PHRA.bottom);
					_hoops_IHPIA[3][0] = 0.5f * (_hoops_SGRA->_hoops_PHRA.left + _hoops_SGRA->_hoops_PHRA.right);
					_hoops_IHPIA[3][1] = 0.5f * (_hoops_SGRA->_hoops_PHRA.bottom + _hoops_SGRA->_hoops_PHRA.top);
					mat = &_hoops_IHPIA[0][0];
				}

				HI_Compute_Transformed_Points (count, _hoops_CRAIR->points,
												mat, (Point *)points);

				_hoops_PPGGA = HD_New_Convex_Clip_Region (nr, count, points);
				_hoops_PPGGA->flags =_hoops_CRAIR->flags;


				if (_hoops_GGCC->_hoops_HCHH != null)
					_hoops_GGCC->_hoops_HCHH.Modify();
				else
					_hoops_GGCC->_hoops_HCHH = _hoops_HSRGA::Create (dc);

				_hoops_ASHH **	_hoops_ASRGR = (_hoops_ASHH **)&_hoops_GGCC->_hoops_HCHH->_hoops_PSHH;

				if (BIT (_hoops_PPGGA->flags, _hoops_RHIH)) {
					_hoops_GGCC->_hoops_HCHH->_hoops_ISRGA = true;

					while (*_hoops_ASRGR && !BIT ((*_hoops_ASRGR)->flags, _hoops_RHIH))
						_hoops_ASRGR = &(*_hoops_ASRGR)->next;
				}

				_hoops_PPGGA->next = *_hoops_ASRGR;
				*_hoops_ASRGR = _hoops_PPGGA;

				if (count > _hoops_GGAPR(buffer))
					FREE_ARRAY (points, count, DC_Point);
			}
		}	break;

		case HK_COLOR:	if (!BIT(dc->flags, _hoops_IRSI) &&
							!ALLBITS(_hoops_PCGS->_hoops_IPPGR, Color_EVERYTHING)) {
			_hoops_HCHHP |= HD_Downwind_Color (nr, (_hoops_SSGI const *)_hoops_HPPGR, _hoops_RCGC, _hoops_PCGS);

			if (dc->_hoops_APHHP != null) {
				_hoops_HCHHP |= _hoops_GSGIP;
				if (ANYBIT(nr->flags, _hoops_GSGIP))
					nr.Modify()->flags &= ~_hoops_GSGIP;
			}
		}	break;

		case HK_CAMERA: if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_CAMERA))) {
			HD_Downwind_Camera (nr, _hoops_HPPGR);

			_hoops_IGCSR const &	_hoops_HRCIR = nr->_hoops_SISI;

			if (_hoops_HRCIR->_hoops_GHGRP == GSU_ORU ||
				_hoops_HRCIR->_hoops_GHGRP == _hoops_SPSC ||
				_hoops_HRCIR->_hoops_SSPAP == GSU_ORU ||
				_hoops_HRCIR->_hoops_SSPAP == _hoops_SPSC)
				nr.Modify()->_hoops_SISI.Modify();

			if (nr->_hoops_AHP->_hoops_HHP == GSU_ORU || nr->_hoops_AHP->_hoops_HHP == _hoops_SPSC)
				nr.Modify()->_hoops_AHP.Modify()->weight = -1;

			if (nr->_hoops_RHP->_hoops_HHP == GSU_ORU || nr->_hoops_RHP->_hoops_HHP == _hoops_SPSC) {
				bool				_hoops_GRHPR;

				_hoops_GRHPR = (nr->_hoops_RHP == nr->_hoops_CAIHP);
				nr.Modify()->_hoops_RHP.Modify()->weight = -1;

				if (_hoops_GRHPR)
					nr->_hoops_CAIHP = nr->_hoops_RHP;
				else
					nr.Modify()->_hoops_CAIHP.Modify()->weight = -1;
			}

			if (nr->_hoops_GSP->_hoops_HHP == GSU_ORU || nr->_hoops_GSP->_hoops_HHP == _hoops_SPSC) {
				_hoops_ICP alter &	_hoops_HCSHP = nr.Modify()->_hoops_GSP.Modify();
				_hoops_HCSHP->ysize = _hoops_HCSHP->_hoops_RGRS = -1;
			}
		}	break;

		case HK_COLOR_MAP: {
			if (!BIT(dc->flags, _hoops_IRSI) &&
				!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_COLOR_MAP))) {

				if (nr->_hoops_ASIR->_hoops_PSIR->_hoops_CSIR == (_hoops_RHAH const *)_hoops_HPPGR) {
					/* _hoops_RGR _hoops_SPR _hoops_CSAP _hoops_GIR _hoops_ARRS _hoops_PPR _hoops_HAR _hoops_RASA _hoops_HPP _hoops_SPR
					** _hoops_GGR _hoops_IRS _hoops_IAHA, _hoops_HIS _hoops_SR _hoops_SAHR _hoops_PHHR _hoops_CCA _hoops_SCH */
				}
				else
					HD_Downwind_Color_Map (nr, _hoops_HPPGR);
			}
		}	break;

		case _hoops_CPPIR: {
			// _hoops_RSGIP _hoops_RSIH
		}	break;

		case HK_EDGE_PATTERN:	if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_EDGE_PATTERN)) && BIT (_hoops_RCGC, T_EDGES)) {
			_hoops_ISAIR const *		_hoops_CSAIR = (_hoops_ISAIR const *)_hoops_HPPGR;
			Line_Style						line_style;

			if (_hoops_CSAIR->mask == 0 ||
				(BIT(_hoops_CSAIR->mask, _hoops_AICAP) && _hoops_CSAIR->line_style.length != 0)) {
				for (int i=0; i<nr->_hoops_GCSHP->count; i++) {
					if (nr->_hoops_GCSHP->keys[i] == _hoops_CSAIR->_hoops_SCCAP) {
						if (!_hoops_RAHSR(_hoops_CSAIR->line_style,
							nr->_hoops_GCSHP->_hoops_HPAIR[i]->name)) continue;
						line_style = nr->_hoops_GCSHP->_hoops_HPAIR[i];
						break;
					}
				}
				if (!line_style) {
					HE_WARNING (HEC_LINE_STYLE, HES_NOT_AVAILABLE,
						Sprintf_N (null, "Requested line style '%n' not found", &_hoops_CSAIR->line_style));
				}
			}

			if (_hoops_CSAIR->mask == 0) {
				if (line_style &&
					(nr->_hoops_RHP->line_style != line_style ||
						 nr->_hoops_RHP->style != _hoops_CSAIR->value)) {
					Line_Rendition			_hoops_ASGIP = nr.Modify()->_hoops_RHP.Modify();
					bool					_hoops_GRHPR = (nr->_hoops_RHP == nr->_hoops_CAIHP);

					_hoops_ASGIP->style = _hoops_CSAIR->value;
					_hoops_ASGIP->line_style = line_style;

					if (_hoops_GRHPR)
						nr->_hoops_CAIHP = nr->_hoops_RHP;
					else {
						_hoops_ASGIP = nr->_hoops_CAIHP.Modify();

						_hoops_ASGIP->style = _hoops_CSAIR->value;
						_hoops_ASGIP->line_style = line_style;
					}
				}
			}
			else {
				Line_Rendition alter &		_hoops_ASGIP = nr.Modify()->_hoops_RHP.Modify();

				if (BIT(_hoops_CSAIR->mask, _hoops_CICAP)) {
					_hoops_ASGIP->style &= ~LJOIN_MASK;
					_hoops_ASGIP->style |= _hoops_CSAIR->value & LJOIN_MASK;
				}
				if (BIT(_hoops_CSAIR->mask, _hoops_IICAP)) {
					_hoops_ASGIP->style &= ~LPAT_MASK;
					_hoops_ASGIP->style |= _hoops_CSAIR->value & LPAT_MASK;
				}

				/* _hoops_ARP _hoops_IS _hoops_SHIR _hoops_RPP _hoops_SR'_hoops_RISP _hoops_CHIA "_hoops_PSP _hoops_III _hoops_IAHA" */
				if (BIT(_hoops_CSAIR->mask, _hoops_AICAP) && _hoops_CSAIR->line_style.length == 0) {
					_hoops_ASGIP->line_style = null;
					line_style = HD_Find_Line_Style(nr, "-");
				}

				if (BIT(_hoops_CSAIR->mask, _hoops_AICAP) && line_style)
					_hoops_ASGIP->line_style = line_style;
			}
			_hoops_HCHHP |= _hoops_ACSHP;
			if (BIT(nr->flags, _hoops_ACSHP))
				nr.Modify()->flags &= ~_hoops_ACSHP;
		}	break;

		case HK_EDGE_WEIGHT:	if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_EDGE_WEIGHT)) && BIT (_hoops_RCGC, T_EDGES)) {
			_hoops_RHCAP const *				_hoops_PSGIP = (_hoops_RHCAP const *)_hoops_HPPGR;

			if (nr->_hoops_RHP->_hoops_PHP != _hoops_PSGIP->data.value || nr->_hoops_RHP->_hoops_HHP != _hoops_PSGIP->data._hoops_HHP) {
				Line_Rendition alter &		_hoops_ASGIP = nr.Modify()->_hoops_RHP.Modify();
				bool						_hoops_GRHPR = (nr->_hoops_RHP == nr->_hoops_CAIHP);

				// _hoops_GACC _hoops_GGR _hoops_HSGIP _hoops_PPR _hoops_ISGIP

				_hoops_ASGIP->_hoops_PHP = _hoops_PSGIP->data.value;
				_hoops_ASGIP->_hoops_HHP = _hoops_PSGIP->data._hoops_HHP;

				if (_hoops_ASGIP->_hoops_HHP == _hoops_SHGRP)
					_hoops_ASGIP->weight = _hoops_ASGIP->_hoops_PHP * dc->_hoops_PGCC._hoops_IHHSR;
				else if (_hoops_ASGIP->_hoops_HHP == GSU_PIXELS)
					_hoops_ASGIP->weight = (int)(_hoops_ASGIP->_hoops_PHP + 0.5f);
				else
					_hoops_ASGIP->weight = -1;

				if (_hoops_ASGIP->weight != -1 && 
					(_hoops_ASGIP->weight < 0 || _hoops_ASGIP->weight > _hoops_CSGIP)) {
					_hoops_ASGIP->weight = (float)_hoops_CSGIP;
				}

				/* _hoops_ASC _hoops_AIAH _hoops_IRAA _hoops_SISS _hoops_RAAA _hoops_CRGR _hoops_HIHA... */
				if (_hoops_ASGIP->_hoops_HHP == GSU_ORU ||
					_hoops_ASGIP->_hoops_HHP == _hoops_SPSC ||
					_hoops_ASGIP->_hoops_HHP == GSU_POINTS ||
					_hoops_ASGIP->_hoops_HHP == GSU_SRU ||
					_hoops_ASGIP->_hoops_HHP == GSU_WRU)
					_hoops_ASGIP->flags |= _hoops_SSGIP;

				if (_hoops_GRHPR)
					nr->_hoops_CAIHP = nr->_hoops_RHP;
				else
					nr->_hoops_CAIHP.Modify()->weight = nr->_hoops_RHP->weight;
			}
		}	break;

		case HK_FACE_PATTERN:	if (!BIT(dc->flags, _hoops_IRSI) &&
							!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_FACE_PATTERN)) && BIT (_hoops_RCGC, T_FACES)) {
			_hoops_IHCAP const *			fp = (_hoops_IHCAP const *)_hoops_HPPGR;

			if (nr->_hoops_IHA->pattern != fp->value) {
				if (nr->_hoops_IHA->_hoops_PGPH == null ||
					nr->_hoops_IHA->_hoops_PGPH->stipple == 0)/* _hoops_CRHR _hoops_IPSP-_hoops_CHIA _hoops_HSP _hoops_PAIA _hoops_HII _hoops_GGRIP _hoops_ISCP _hoops_SHPR _hoops_CIHHP */
					nr.Modify()->_hoops_IHA.Modify()->pattern = fp->value;
			}
		}	break;

		case HK_LINE_PATTERN:	if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_LINE_PATTERN)) && BIT (_hoops_RCGC, T_LINES)) {
			_hoops_PSAIR const *		_hoops_HSAIR = (_hoops_PSAIR const *)_hoops_HPPGR;
			Line_Style						line_style;

			if (_hoops_HSAIR->mask == 0 || (BIT(_hoops_HSAIR->mask, _hoops_AICAP) && _hoops_HSAIR->line_style.length != 0)) {
				for (int i=0; i<nr->_hoops_GCSHP->count; i++) {
					if (nr->_hoops_GCSHP->keys[i] == _hoops_HSAIR->_hoops_SCCAP) {
						if (!_hoops_RAHSR(_hoops_HSAIR->line_style,  nr->_hoops_GCSHP->_hoops_HPAIR[i]->name))
							continue;
						line_style = nr->_hoops_GCSHP->_hoops_HPAIR[i];
						break;
					}
				}
				if (!line_style) {
					HE_WARNING (HEC_LINE_STYLE, HES_NOT_AVAILABLE,
						Sprintf_N (null, "Requested line style '%n' not found", &_hoops_HSAIR->line_style));
				}
			}

			if (_hoops_HSAIR->mask == 0) {
				if (line_style &&
					(nr->_hoops_AHP->line_style != line_style ||
						 nr->_hoops_AHP->style != _hoops_HSAIR->value)) {
					Line_Rendition alter &	_hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();

					_hoops_ASGIP->start_glyph = null;
					_hoops_ASGIP->middle_glyph = null;
					_hoops_ASGIP->end_glyph = null;

					_hoops_ASGIP->flags &= ~(_hoops_RGRIP|_hoops_SRPI|_hoops_AGRIP);

					_hoops_ASGIP->style = _hoops_HSAIR->value;
					_hoops_ASGIP->line_style = line_style;
				}
			}
			else {
				int		glyph_count = 0;

				if (_hoops_HSAIR->start_glyph.length != 0)
					glyph_count++;
				if (_hoops_HSAIR->middle_glyph.length != 0)
					glyph_count++;
				if (_hoops_HSAIR->end_glyph.length != 0)
					glyph_count++;

				Line_Rendition alter &		_hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();

				/* _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_SR _hoops_HS _hoops_HHPA _hoops_HCR _hoops_RH _hoops_GPPC _hoops_ACGIP _hoops_GGR _hoops_RH _hoops_PGRIP */
				if (glyph_count > 0) {
					for (int i=0; i<nr->glyph_rendition->count; i++) {
						if (_hoops_HSAIR->start_glyph.length != 0 &&
							nr->glyph_rendition->glyphs[i]->key == _hoops_HSAIR->_hoops_GSCAP &&
							_hoops_RAHSR(_hoops_HSAIR->start_glyph, nr->glyph_rendition->glyphs[i]->name)) {
							_hoops_ASGIP->start_glyph = nr->glyph_rendition->glyphs[i];
							glyph_count--;
							_hoops_ASGIP->flags &= ~_hoops_HHISA;
						}
						if (_hoops_HSAIR->middle_glyph.length != 0 &&
							nr->glyph_rendition->glyphs[i]->key == _hoops_HSAIR->_hoops_RSCAP &&
							_hoops_RAHSR(_hoops_HSAIR->middle_glyph, nr->glyph_rendition->glyphs[i]->name)) {
							_hoops_ASGIP->middle_glyph = nr->glyph_rendition->glyphs[i];
							glyph_count--;
							_hoops_ASGIP->flags &= ~_hoops_HGRIP;
						}
						if (_hoops_HSAIR->end_glyph.length != 0 &&
							nr->glyph_rendition->glyphs[i]->key == _hoops_HSAIR->_hoops_ASCAP &&
							_hoops_RAHSR(_hoops_HSAIR->end_glyph, nr->glyph_rendition->glyphs[i]->name)) {
							_hoops_ASGIP->end_glyph = nr->glyph_rendition->glyphs[i];
							if (BIT(_hoops_HSAIR->mask, _hoops_PCCAP))
								_hoops_ASGIP->flags |= _hoops_RGRIP;
							else
								_hoops_ASGIP->flags &= ~_hoops_RGRIP;
							glyph_count--;
							_hoops_ASGIP->flags &= ~_hoops_PHISA;
						}

						if (glyph_count == 0)
							break;
					}

					if (glyph_count > 0) {
						/* _hoops_AHGSR _hoops_IH _hoops_IGRIP _hoops_RPHH _hoops_PAIGR */
						if (_hoops_HSAIR->start_glyph.length != 0 && !_hoops_ASGIP->start_glyph) {
							HE_WARNING (HEC_MARKER, HES_NOT_AVAILABLE,
								Sprintf_N (null, "Requested glyph '%n' not found", &_hoops_HSAIR->start_glyph));
						}
						if (_hoops_HSAIR->middle_glyph.length != 0 && !_hoops_ASGIP->middle_glyph) {
							HE_WARNING (HEC_MARKER, HES_NOT_AVAILABLE,
								Sprintf_N (null, "Requested glyph '%n' not found", &_hoops_HSAIR->middle_glyph));
						}
						if (_hoops_HSAIR->end_glyph.length != 0 && !_hoops_ASGIP->end_glyph) {
							HE_WARNING (HEC_MARKER, HES_NOT_AVAILABLE,
								Sprintf_N (null, "Requested glyph '%n' not found", &_hoops_HSAIR->end_glyph));
						}
					}
				}

				/* _hoops_RPP _hoops_IIH _hoops_SSCP _hoops_RPII _hoops_IRS _hoops_IAGC _hoops_IS _hoops_IPPRA _hoops_GPPC, _hoops_AA _hoops_SGS _hoops_SRS */
				if (BIT(_hoops_HSAIR->mask, _hoops_ICCAP)) {
					_hoops_ASGIP->flags &= ~(_hoops_AGRIP|_hoops_SRPI|_hoops_RGRIP);
					_hoops_ASGIP->start_glyph = null;
					_hoops_ASGIP->middle_glyph = null;
					_hoops_ASGIP->end_glyph = null;
				}

				if (BIT(_hoops_HSAIR->mask, _hoops_SICAP) &&
					_hoops_HSAIR->start_glyph.length == 0) {
					_hoops_ASGIP->start_glyph = null;
					_hoops_ASGIP->flags |= _hoops_HHISA;
				}
				if (BIT(_hoops_HSAIR->mask, _hoops_RCCAP) &&
					_hoops_HSAIR->middle_glyph.length == 0) {
					_hoops_ASGIP->middle_glyph = null;
					_hoops_ASGIP->flags |= _hoops_HGRIP;
				}
				if (ANYBIT(_hoops_HSAIR->mask, (_hoops_GCCAP|_hoops_PCCAP)) &&
					_hoops_HSAIR->end_glyph.length == 0) {
					_hoops_ASGIP->end_glyph = null;
					_hoops_ASGIP->flags &= ~_hoops_RGRIP;
					_hoops_ASGIP->flags |= _hoops_PHISA;
				}

				if (_hoops_ASGIP->start_glyph || _hoops_ASGIP->middle_glyph || _hoops_ASGIP->end_glyph)
					_hoops_ASGIP->flags |= _hoops_SRPI;
				else
					_hoops_ASGIP->flags &= ~_hoops_SRPI;

				if (BIT(_hoops_HSAIR->mask, _hoops_PICAP)) {
					_hoops_ASGIP->style &= ~LCAP_START_MASK;
					_hoops_ASGIP->style |= _hoops_HSAIR->value & LCAP_START_MASK;
				}
				if (BIT(_hoops_HSAIR->mask, _hoops_HICAP)) {
					_hoops_ASGIP->style &= ~LCAP_END_MASK;
					_hoops_ASGIP->style |= _hoops_HSAIR->value & LCAP_END_MASK;
				}
				if (BIT(_hoops_HSAIR->mask, _hoops_CICAP)) {
					_hoops_ASGIP->style &= ~LJOIN_MASK;
					_hoops_ASGIP->style |= _hoops_HSAIR->value & LJOIN_MASK;
				}
				if (BIT(_hoops_HSAIR->mask, _hoops_IICAP)) {
					_hoops_ASGIP->style &= ~LPAT_MASK;
					_hoops_ASGIP->style |= _hoops_HSAIR->value & LPAT_MASK;
				}

				/* _hoops_ARP _hoops_IS _hoops_SHIR _hoops_RPP _hoops_SR'_hoops_RISP _hoops_CHIA "_hoops_PSP _hoops_III _hoops_IAHA" */
				if (BIT(_hoops_HSAIR->mask, _hoops_AICAP) && _hoops_HSAIR->line_style.length == 0) {
					_hoops_ASGIP->line_style = null;
					line_style = HD_Find_Line_Style(nr, "-");
				}

				if (BIT(_hoops_HSAIR->mask, _hoops_AICAP) && line_style)
					_hoops_ASGIP->line_style = line_style;
			}

			_hoops_HCHHP |= _hoops_ACSHP;
			if (BIT(nr->flags, _hoops_ACSHP))
				nr.Modify()->flags &= ~_hoops_ACSHP;
		}	break;

		case HK_LINE_WEIGHT:	if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_LINE_WEIGHT)) && BIT (_hoops_RCGC, T_LINES)) {
			_hoops_GHCAP const *				_hoops_CGRIP = (_hoops_GHCAP const *)_hoops_HPPGR;

			if (nr->_hoops_AHP->_hoops_PHP != _hoops_CGRIP->data.value ||
				nr->_hoops_AHP->_hoops_HHP != _hoops_CGRIP->data._hoops_HHP) {
				Line_Rendition alter &		_hoops_ASGIP = nr.Modify()->_hoops_AHP.Modify();

				// _hoops_GACC _hoops_GGR _hoops_SGRIP _hoops_PPR _hoops_ISGIP

				_hoops_ASGIP->_hoops_PHP = _hoops_CGRIP->data.value;
				_hoops_ASGIP->_hoops_HHP = _hoops_CGRIP->data._hoops_HHP;

				if (_hoops_ASGIP->_hoops_HHP == _hoops_SHGRP)
					_hoops_ASGIP->weight = _hoops_ASGIP->_hoops_PHP * dc->_hoops_PGCC._hoops_IHHSR;
				else if (_hoops_ASGIP->_hoops_HHP == GSU_PIXELS)
					_hoops_ASGIP->weight = (int)(_hoops_ASGIP->_hoops_PHP + 0.5f);
				else
					_hoops_ASGIP->weight = -1;

				if (_hoops_ASGIP->weight != -1 && 
					(_hoops_ASGIP->weight < 0 || _hoops_ASGIP->weight > _hoops_CSGIP)) {
					_hoops_ASGIP->weight = (float)_hoops_CSGIP;
				}

				/* _hoops_ASC _hoops_AIAH _hoops_IRAA _hoops_SISS _hoops_RAAA _hoops_CRGR _hoops_HIHA... */
				if (_hoops_ASGIP->_hoops_HHP == GSU_ORU ||
					_hoops_ASGIP->_hoops_HHP == _hoops_SPSC ||
					_hoops_ASGIP->_hoops_HHP == GSU_POINTS ||
					_hoops_ASGIP->_hoops_HHP == GSU_SRU ||
					_hoops_ASGIP->_hoops_HHP == GSU_WRU)
					_hoops_ASGIP->flags |= _hoops_SSGIP;
			}
		}	break;

		case HK_MARKER_SYMBOL:	if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_MARKER_SYMBOL)) && 
									ANYBIT (_hoops_RCGC, T_LINES|T_MARKERS|T_VERTICES)) {
			_hoops_GICAP const *			_hoops_IRPP = (_hoops_GICAP const *)_hoops_HPPGR;
			_hoops_GASC							glyph;

			for (int i=0; i<nr->glyph_rendition->count; i++) {
				if (nr->glyph_rendition->keys[i] == _hoops_IRPP->key &&
					_hoops_RAHSR(_hoops_IRPP->name,  nr->glyph_rendition->glyphs[i]->name)) {
					glyph = nr->glyph_rendition->glyphs[i];
					break;
				}
			}

			if (!glyph) {
				HE_WARNING (HEC_MARKER, HES_NOT_AVAILABLE,
					Sprintf_N (null, "Requested marker '%n' not found", &_hoops_IRPP->name));
			}
			else if (nr->_hoops_GSP->glyph != glyph) {
				bool						shared = (nr->_hoops_GSP == nr->_hoops_SCP);
				_hoops_ICP alter &	_hoops_HCSHP = nr.Modify()->_hoops_GSP.Modify();

				_hoops_HCSHP->glyph = glyph;

				if (shared)
					nr->_hoops_SCP = _hoops_HCSHP;
				else {
					_hoops_ICP alter &	_hoops_SCPHP = nr->_hoops_SCP.Modify();

					_hoops_SCPHP->glyph = glyph;
				}
			}
		}	break;

		case HK_MARKER_SIZE:	if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_MARKER_SIZE)) && 
									ANYBIT (_hoops_RCGC, T_LINES|T_MARKERS|T_VERTICES)) {
			_hoops_AHCAP const *				_hoops_IRPP = (_hoops_AHCAP const *)_hoops_HPPGR;

			if (nr->_hoops_GSP->_hoops_PHP != _hoops_IRPP->data.value || nr->_hoops_GSP->_hoops_HHP != _hoops_IRPP->data._hoops_HHP) {
				bool						shared = (nr->_hoops_GSP == nr->_hoops_SCP);
				_hoops_ICP alter &	_hoops_HCSHP = nr.Modify()->_hoops_GSP.Modify();

				// _hoops_GACC _hoops_GGR _hoops_GRRIP

				_hoops_HCSHP->_hoops_PHP = _hoops_IRPP->data.value;
				_hoops_HCSHP->_hoops_HHP = _hoops_IRPP->data._hoops_HHP;

				if (_hoops_HCSHP->_hoops_HHP == _hoops_SHGRP) {
					float					size;

					size = _hoops_HCSHP->_hoops_PHP * _hoops_RRRIP * dc->current._hoops_PRPSR.y;
					_hoops_HCSHP->ysize = size;
					_hoops_HCSHP->_hoops_RGRS = size*dc->current._hoops_AGRS;
				}
				else if (_hoops_HCSHP->_hoops_HHP == GSU_PIXELS) {
					_hoops_HCSHP->ysize = _hoops_HCSHP->_hoops_PHP*0.5f;
					_hoops_HCSHP->_hoops_RGRS = _hoops_HCSHP->_hoops_PHP*0.5f*dc->current._hoops_AGRS;
				}
				else
					_hoops_HCSHP->ysize = _hoops_HCSHP->_hoops_RGRS = -1.0f;

				if (shared)
					nr->_hoops_SCP = _hoops_HCSHP;
				else {
					_hoops_ICP alter &	_hoops_SCPHP = nr->_hoops_SCP.Modify();

					_hoops_SCPHP->_hoops_RGRS = nr->_hoops_GSP->_hoops_RGRS;
					_hoops_SCPHP->ysize = nr->_hoops_GSP->ysize;
					_hoops_SCPHP->_hoops_PHP = _hoops_IRPP->data.value;
					_hoops_SCPHP->_hoops_HHP = _hoops_IRPP->data._hoops_HHP;
				}
			}
		}	break;

		case HK_TEXT_FONT:		if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_TEXT_FONT)) && BIT (_hoops_RCGC, T_TEXT)) {
			_hoops_HCHHP |= HD_Downwind_Text_Font (nr, (_hoops_AGPIR const *)_hoops_HPPGR);
		}	break;

		case HK_TEXT_SPACING:	if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_TEXT_SPACING)) && BIT (_hoops_RCGC, T_TEXT)) {
			_hoops_PHCAP const *		ts = (_hoops_PHCAP const *)_hoops_HPPGR;

			if (nr->_hoops_SISI->spacing != ts->data.value) {
				nr.Modify()->_hoops_SISI.Modify()->spacing= ts->data.value;
			}
		}	break;

		case HK_TEXT_ALIGNMENT: if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_TEXT_ALIGNMENT)) && BIT (_hoops_RCGC, T_TEXT)) {
			_hoops_SHCAP const *		_hoops_ARRIP = (_hoops_SHCAP const *)_hoops_HPPGR;

			if (nr->_hoops_SISI->_hoops_PRRIP != _hoops_ARRIP->value ||
				nr->_hoops_SISI->_hoops_HRRIP != _hoops_ARRIP->_hoops_HHCAP) {
				_hoops_IGCSR alter &		_hoops_IRRIP = nr.Modify()->_hoops_SISI.Modify();

				_hoops_IRRIP->_hoops_PRRIP = _hoops_ARRIP->value;
				_hoops_IRRIP->_hoops_HRRIP = _hoops_ARRIP->_hoops_HHCAP;
			}
		}	break;

		case HK_TEXT_PATH:		if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_TEXT_PATH)) && BIT (_hoops_RCGC, T_TEXT)) {
			_hoops_RGPIR const *				_hoops_HAPAR = (_hoops_RGPIR const *)_hoops_HPPGR;

			if (nr->_hoops_SISI->path != _hoops_HAPAR->value) {
				_hoops_IGCSR alter &		_hoops_IRRIP = nr.Modify()->_hoops_SISI.Modify();

				_hoops_IRRIP->path = _hoops_HAPAR->value;

				if (_hoops_IRRIP->_hoops_CRRIP) {
					if (_hoops_IRRIP->path.x != 0.0f || _hoops_IRRIP->path.y != 0.0f)
						_hoops_IRRIP->rotation = _hoops_AGGGA (_hoops_IRRIP->path.y, _hoops_IRRIP->path.x);

					_hoops_IRRIP->_hoops_SRRIP();
				}
			}
		}	break;

		case HK_WINDOW_PATTERN: if (!BIT(dc->flags, _hoops_IRSI) &&
							!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_WINDOW_PATTERN))) {
			_hoops_CHCAP const *		_hoops_GARIP = (_hoops_CHCAP const *)_hoops_HPPGR;

			if (nr->_hoops_ASIR->window.pattern != _hoops_GARIP->value) {
				_hoops_ISHHP alter &		_hoops_RHIHP = nr.Modify()->_hoops_ASIR.Modify();

				if (_hoops_GARIP->value == FP_BLEND)
					_hoops_RHIHP->window._hoops_RARIP = true;
				else {
					_hoops_RHIHP->window.pattern = _hoops_GARIP->value;
					_hoops_RHIHP->window._hoops_RARIP = false;
				}
			}
		}	break;

		case HK_VISIBILITY:		/* _hoops_AAHS _hoops_GIR _hoops_SSPP _hoops_GGR _hoops_IGRH _hoops_HGRH */ {
			_hoops_RSAIR const *		vis = (_hoops_RSAIR const *)_hoops_HPPGR;
			_hoops_ACHR				_hoops_CCCIR = (nr->_hoops_IRR->_hoops_AARIP ^ vis->value) &
											  (vis->mask & ~_hoops_PCGS->_hoops_RGP);

			if (_hoops_CCCIR != 0) {
				nr.Modify();

				_hoops_CIGA alter &		_hoops_CPIHP = nr->_hoops_IHA.Modify();
				_hoops_GRGH alter &		_hoops_APIHP = nr->_hoops_IRR.Modify();
				_hoops_ACHR					_hoops_PARIP = nr->_hoops_CPP->_hoops_RHGGR._hoops_RGP;
				int							_hoops_RCSHP;

				_hoops_RCSHP = _hoops_IPIHP;
				if (BIT(dc->flags, _hoops_CHSHP))
					_hoops_RCSHP |= _hoops_HARIP;
				else if (dc->_hoops_APHHP != null)
					_hoops_RCSHP |= _hoops_GSGIP;

				_hoops_APIHP->_hoops_AARIP ^= _hoops_CCCIR;
				nr->_hoops_RGP = _hoops_APIHP->_hoops_AARIP;

				_hoops_HCHHP |= _hoops_RCSHP;
				if (ANYBIT(nr->flags, _hoops_RCSHP))
					nr->flags &= ~_hoops_RCSHP;

				if (BIT(dc->flags, _hoops_CHSHP) && ANYBIT (nr->_hoops_RGP, ~_hoops_PARIP))
					nr->_hoops_RGP &= _hoops_PARIP;

				if (ANYBIT (_hoops_CCCIR, T_FACES|T_ANY_EDGE)) {
					if (dc->options._hoops_RAHHP &&
						ANYBIT (_hoops_CCCIR, T_ANY_EDGE)) {
						if (ANYBIT (nr->_hoops_RGP, T_ANY_EDGE)) {
							_hoops_CPIHP->color = dc->_hoops_GHHHP;
							_hoops_CPIHP->contrast_color = dc->_hoops_SPHHP;
						}
						else {
							_hoops_CPIHP->color = dc->_hoops_SPHHP;
							_hoops_CPIHP->contrast_color = dc->_hoops_GHHHP;
						}
					}
				}


				/* (_hoops_SPS _hoops_RPGP _hoops_SPASR _hoops_IARIP _hoops_GGR _hoops_CARIP) */
				if (nr->_hoops_IHA->_hoops_AGP != null &&
					BIT (nr->_hoops_RGP, T_LIGHTS_FOR_FACES) ||
					nr->_hoops_RHP->_hoops_AGP != null &&
					BIT (nr->_hoops_RGP, T_LIGHTS_FOR_EDGES) ||
					nr->_hoops_SCP->_hoops_AGP != null &&
					BIT (nr->_hoops_RGP, T_LIGHTS_FOR_MARKERS))
					nr->_hoops_RCSHR |= _hoops_SARIP;
				else
					nr->_hoops_RCSHR &= ~_hoops_SARIP;

				if (nr->transform_rendition->_hoops_RGH != null &&
					BIT (nr->_hoops_RGP, T_CUTTING_PLANES))
					nr->_hoops_RCSHR |= _hoops_GPRIP;
				else
					nr->_hoops_RCSHR &= ~_hoops_GPRIP;

				if (dc->_hoops_APHHP != null) {
					_hoops_HCHHP |= _hoops_GSGIP;
					if (ANYBIT(nr->flags, _hoops_GSGIP))
						nr.Modify()->flags &= ~_hoops_GSGIP;
				}
			}

			if (BIT(vis->mask, T_CUT_GEOMETRY) && !BIT(_hoops_PCGS->_hoops_RGP, T_CUT_GEOMETRY)) {
				if (BIT(vis->value, T_CUT_GEOMETRY)) {
					// _hoops_AGRP _hoops_GII _hoops_SASI _hoops_RPRIP _hoops_HRP
					_hoops_CCCIR = vis->_hoops_PRIGA.mask &
							   (nr->_hoops_IRR->_hoops_GHIHP ^
								vis->_hoops_PRIGA.value);
				}
				else	// _hoops_HCR _hoops_PSAP, _hoops_HIS "_hoops_AGRP" _hoops_PA _hoops_SGS _hoops_CSAP _hoops_GPP
					_hoops_CCCIR = nr->_hoops_IRR->_hoops_GHIHP;

				if (_hoops_CCCIR != 0) {
					nr.Modify()->_hoops_IRR.Modify()->_hoops_GHIHP ^= _hoops_CCCIR;
					int							_hoops_RCSHP;

					_hoops_RCSHP = _hoops_IPIHP;
					if (BIT(dc->flags, _hoops_CHSHP))
						_hoops_RCSHP |= _hoops_HARIP;
					else if (dc->_hoops_APHHP != null)
						_hoops_RCSHP |= _hoops_GSGIP;
				}
			}

			if (BIT(vis->mask, T_ANY_SHADOW) && !BIT(_hoops_PCGS->_hoops_RGP, T_ANY_SHADOW)) {
				if (BIT(vis->value, T_ANY_SHADOW)) {
					/* _hoops_AGRP _hoops_GII _hoops_SASI _hoops_RCAR _hoops_HRP */
					_hoops_CCCIR = vis->_hoops_SPSS.mask &
							   (nr->_hoops_IRR->_hoops_CRR ^
								vis->_hoops_SPSS.value);
				}
				else {
					/* _hoops_HCR _hoops_PSAP, _hoops_HIS "_hoops_AGRP" _hoops_PA _hoops_SGS _hoops_CSAP _hoops_GPP */
					_hoops_CCCIR = nr->_hoops_IRR->_hoops_CRR;
				}

				if (_hoops_CCCIR != 0) {
					nr.Modify()->_hoops_IRR.Modify()->_hoops_CRR ^= _hoops_CCCIR;
					int							_hoops_RCSHP;

					_hoops_RCSHP = _hoops_IPIHP;
					if (BIT(dc->flags, _hoops_CHSHP))
						_hoops_RCSHP |= _hoops_HARIP;
					else if (dc->_hoops_APHHP != null)
						_hoops_RCSHP |= _hoops_GSGIP;
				}
			}
		}	break;

		case HK_RENDERING_OPTIONS:		if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_RENDERING_OPTIONS))) {
			_hoops_HCHHP |= HD_Downwind_Rendering_Options(nr, (_hoops_RHAIR const *)_hoops_HPPGR, _hoops_PCGS);
		}	break;

		case HK_HEURISTICS:		if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_HEURISTICS))) {
			HD_Downwind_Heuristics(nr,(_hoops_GHAIR const *)_hoops_HPPGR);
		}	break;

		case HK_MODELLING_MATRIX:		if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_MODELLING_MATRIX))) {
			HD_Downwind_Modelling_Matrix (nr, _hoops_HPPGR);
		}	break;

		case HK_TEXTURE_MATRIX: if (!BIT(dc->flags, _hoops_IRSI) &&
							!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_TEXTURE_MATRIX))) {
			nr.Modify()->_hoops_IRR.Modify()->_hoops_APGH = (_hoops_GAAIR const *)_hoops_HPPGR;
		}	break;


		case _hoops_IPAIR: if (!BIT(dc->flags, _hoops_IRSI)) {
			_hoops_CPAIR const *			_hoops_SPAIR = (_hoops_CPAIR const *)_hoops_HPPGR;

			if (_hoops_SPAIR->count > 0) {
				/* _hoops_HGCR _hoops_HH _hoops_APRIP _hoops_GIRP _hoops_RSIH _hoops_HIS */
				/* _hoops_SGS _hoops_HAIR _hoops_PAH _hoops_SHH _hoops_PPRIP _hoops_GH _hoops_CAPP */
				_hoops_RCR **					_hoops_HPRIP;
				int *						new_keys;
				int							_hoops_RGCCA;

				_hoops_IPRIP alter &	_hoops_CPRIP = nr.Modify()->_hoops_GCCSR.Modify();

				_hoops_RGCCA = _hoops_CPRIP->count + _hoops_SPAIR->count;

				POOL_ALLOC_ARRAY_CACHED (_hoops_HPRIP, _hoops_RGCCA, _hoops_RCR *, dc->memory_pool);
				POOL_ALLOC_ARRAY_CACHED (new_keys, _hoops_RGCCA, Integer32, dc->memory_pool);

				_hoops_AIGA (_hoops_SPAIR->textures,
							_hoops_SPAIR->count, _hoops_RCR *, _hoops_HPRIP);

				_hoops_AIGA (_hoops_SPAIR->keys,
							_hoops_SPAIR->count, Integer32, new_keys);

				if (_hoops_CPRIP->count) {
					_hoops_AIGA (_hoops_CPRIP->textures, _hoops_CPRIP->count, _hoops_RCR *,
								&_hoops_HPRIP[_hoops_SPAIR->count]);

					_hoops_AIGA (_hoops_CPRIP->keys, _hoops_CPRIP->count, Integer32,
								&new_keys[_hoops_SPAIR->count]);

					FREE_ARRAY (_hoops_CPRIP->textures, _hoops_CPRIP->count, _hoops_RCR *);
					FREE_ARRAY (_hoops_CPRIP->keys, _hoops_CPRIP->count, Integer32);
				}

				_hoops_CPRIP->textures = _hoops_HPRIP;
				_hoops_CPRIP->keys = new_keys;
				_hoops_CPRIP->count = _hoops_RGCCA;
			}
		}	break;

		case _hoops_RAAIR: if (ANYBIT (_hoops_RCGC, T_MARKERS|T_VERTICES | T_LINES|T_EDGES)) {
			_hoops_AAAIR const *				_hoops_PAAIR = (_hoops_AAAIR const *)_hoops_HPPGR;

			if (_hoops_PAAIR->count > 0) {
				_hoops_GASC *						_hoops_SPRIP;
				int *						new_keys;
				int							_hoops_RGCCA;

				_hoops_GHRIP alter &		_hoops_RHRIP = nr.Modify()->glyph_rendition.Modify();

				_hoops_RGCCA = _hoops_RHRIP->count + _hoops_PAAIR->count;

				POOL_ZALLOC_ARRAY_CACHED (_hoops_SPRIP, _hoops_RGCCA, _hoops_GASC, dc->memory_pool);
				POOL_ALLOC_ARRAY_CACHED (new_keys, _hoops_RGCCA, Integer32, dc->memory_pool);

				for (int i=0; i<_hoops_PAAIR->count; ++i)
					_hoops_SPRIP[i] = _hoops_PAAIR->glyphs[i];
				_hoops_AIGA (_hoops_PAAIR->keys, _hoops_PAAIR->count, Integer32, new_keys);

				if (_hoops_RHRIP->count) {
					// _hoops_PIP, _hoops_HIGIP _hoops_AGCR
					_hoops_AIGA (_hoops_RHRIP->glyphs, _hoops_RHRIP->count, _hoops_GASC, &_hoops_SPRIP[_hoops_PAAIR->count]);
					FREE_ARRAY (_hoops_RHRIP->glyphs, _hoops_RHRIP->count, _hoops_GASC);

					_hoops_AIGA (_hoops_RHRIP->keys, _hoops_RHRIP->count, Integer32, &new_keys[_hoops_PAAIR->count]);
					FREE_ARRAY (_hoops_RHRIP->keys, _hoops_RHRIP->count, Integer32);
				}

				_hoops_RHRIP->glyphs = _hoops_SPRIP;
				_hoops_RHRIP->keys = new_keys;
				_hoops_RHRIP->count = _hoops_RGCCA;
			}
		}	break;

		case _hoops_RPAIR: if (ANYBIT (_hoops_RCGC, T_LINES|T_EDGES)) {
			_hoops_APAIR const *				_hoops_PPAIR = (_hoops_APAIR const *)_hoops_HPPGR;

			if (_hoops_PPAIR->count > 0) {
				Line_Style *					_hoops_AHRIP;
				int *							new_keys;
				int								_hoops_RGCCA;

				_hoops_PHRIP alter &	_hoops_HHRIP = nr.Modify()->_hoops_GCSHP.Modify();

				_hoops_RGCCA = _hoops_HHRIP->count + _hoops_PPAIR->count;

				POOL_ZALLOC_ARRAY_CACHED (_hoops_AHRIP, _hoops_RGCCA, Line_Style, dc->memory_pool);
				POOL_ALLOC_ARRAY_CACHED (new_keys, _hoops_RGCCA, Integer32, dc->memory_pool);

				for (int i=0; i<_hoops_PPAIR->count; ++i)
					_hoops_AHRIP[i] = _hoops_PPAIR->_hoops_HPAIR[i];
				_hoops_AIGA (_hoops_PPAIR->keys, _hoops_PPAIR->count, Integer32, new_keys);

				if (_hoops_HHRIP->count) {
					// _hoops_PIP, _hoops_HIGIP _hoops_AGCR
					_hoops_AIGA (_hoops_HHRIP->_hoops_HPAIR, _hoops_HHRIP->count, Line_Style, &_hoops_AHRIP[_hoops_PPAIR->count]);
					FREE_ARRAY (_hoops_HHRIP->_hoops_HPAIR, _hoops_HHRIP->count, Line_Style);

					_hoops_AIGA (_hoops_HHRIP->keys, _hoops_HHRIP->count, Integer32, &new_keys[_hoops_PPAIR->count]);
					FREE_ARRAY (_hoops_HHRIP->keys, _hoops_HHRIP->count, Integer32);
				}

				_hoops_HHRIP->_hoops_HPAIR = _hoops_AHRIP;
				_hoops_HHRIP->keys = new_keys;
				_hoops_HHRIP->count = _hoops_RGCCA;

				if (!_hoops_HHRIP->_hoops_IHRIP)		// _hoops_RGAR _hoops_GPP _hoops_RH _hoops_SRRPR _hoops_CAGH
					_hoops_HHRIP->_hoops_IHRIP = HD_Find_Line_Style(nr, "-");
			}
		}	break;

		case _hoops_HAAIR: {
			// _hoops_RSGIP _hoops_RSIH
		}	break;

		case HK_DRIVER: {
			Window					window;

			ZERO_STRUCT (&window, Window);
			window._hoops_RCHS.left = -1;
			window._hoops_RCHS.right =  1;
			window._hoops_RCHS.bottom = -1;
			window._hoops_RCHS.top =  1;
			HD_Downwind_Window (nr, (Attribute *) &window);

			nr.Modify()->_hoops_RCSHR |= _hoops_CRHPP;

		}	break;

		case HK_WINDOW: {
			HD_Downwind_Window (nr, _hoops_HPPGR);
#if 0
/* _hoops_RGR _hoops_HRGR _hoops_CHRIP _hoops_HPP _hoops_RH _hoops_GRP "_hoops_PSIPR" _hoops_RPPS _hoops_HSGP _hoops_GGR 16.0 */
#ifdef _hoops_SHRIP
			if (_hoops_HPPGR->owner &&
				BIT (_hoops_HPPGR->owner->_hoops_PHSI, _hoops_RCHGP))
				nr.Modify()->_hoops_SAIR.Modify()->flags |= _hoops_ACARP;
#endif
#endif

			nr.Modify()->_hoops_RCSHR |= _hoops_CRHPP;

			_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;

			if (_hoops_HRCIR->_hoops_GHGRP == GSU_ORU ||
				_hoops_HRCIR->_hoops_SSPAP == GSU_ORU ||
				_hoops_HRCIR->_hoops_GHGRP == GSU_WRU ||
				_hoops_HRCIR->_hoops_SSPAP == GSU_WRU ||
				_hoops_HRCIR->_hoops_GHGRP == _hoops_SPSC ||
				_hoops_HRCIR->_hoops_SSPAP == _hoops_SPSC)
				nr.Modify()->_hoops_SISI.Modify();
		}	break;

		case HK_HANDEDNESS:		if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_HANDEDNESS))) {
			HD_Downwind_Handedness (nr, _hoops_HPPGR);
		}	break;

		case HK_DRIVER_OPTIONS: if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_DRIVER_OPTIONS))) {
			if (BIT(dc->flags, _hoops_CPPHP)) {
				HD_Record_Driver_Options ((Display_Context alter *)dc, _hoops_HPPGR);
			}
			else if (!ANYBIT (_hoops_HPPGR->owner->_hoops_PHSI, _hoops_GISIR|_hoops_HIHGP) &&
					 BIT(dc->flags, _hoops_GIRIP)) {
				char				options[4096];

				HI_Show_Driver_Options ((_hoops_GAPIR *)_hoops_HPPGR, options, -1);

				_hoops_ARGIP (HEC_DRIVER, HES_IGNORED,
							 "Ignoring Driver_Options set below an active driver segment,",
							 Sprintf_P (null, "Segment is %p, options are:", _hoops_HPPGR->owner),
							 options);
			}
		}	break;

		case HK_SELECTABILITY:	if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_SELECTABILITY))) {
			if (dc->_hoops_APHHP != null) {
				_hoops_ASAIR const *	_hoops_RIRIP = (_hoops_ASAIR const *)_hoops_HPPGR;
				_hoops_GRGH const &	_hoops_RRGH = nr->_hoops_IRR;
				_hoops_ACHR				_hoops_CCCIR,
										_hoops_AIRIP,
										_hoops_PIRIP;

				switch (dc->_hoops_APHHP->event->_hoops_CHSHA) {
					case _hoops_HPSHA: {
						_hoops_CCCIR = ((_hoops_RIRIP->down | _hoops_RIRIP->_hoops_AHARP) ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
						_hoops_AIRIP = (_hoops_RIRIP->down ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
					}	break;

					case _hoops_IPSHA: {
						_hoops_CCCIR = (_hoops_RIRIP->_hoops_AHARP ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
						_hoops_AIRIP = _hoops_CCCIR;
					}	break;

					case _hoops_CPSHA: {
						_hoops_CCCIR = ((_hoops_RIRIP->up | _hoops_RIRIP->_hoops_RHARP) ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
						_hoops_AIRIP = (_hoops_RIRIP->up ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
					}	break;

					default: /* _hoops_AGIR _hoops_HIRIP: */ {
						_hoops_CCCIR = (_hoops_RIRIP->_hoops_RHARP ^ _hoops_RRGH->_hoops_AAICA) & _hoops_RIRIP->mask;
						_hoops_AIRIP = _hoops_CCCIR;
					}	break;
				}

				_hoops_PIRIP = (_hoops_RIRIP->_hoops_PHARP ^ _hoops_RRGH->_hoops_PHARP) & _hoops_RIRIP->mask;

				if (_hoops_CCCIR || _hoops_AIRIP || _hoops_PIRIP) {
					_hoops_GRGH alter &		_hoops_APIHP = nr.Modify()->_hoops_IRR.Modify();

					_hoops_APIHP->_hoops_AAICA ^= _hoops_CCCIR;
					_hoops_APIHP->restricted_selectability ^= _hoops_AIRIP;
					_hoops_APIHP->_hoops_PHARP ^= _hoops_PIRIP;

					if (dc->_hoops_APHHP != null)
						_hoops_HCHHP |= _hoops_GSGIP;
				}
			}
		}	break;

		case HK_WINDOW_FRAME:	if (!BIT(_hoops_PCGS->_hoops_IPPGR, _hoops_GGCAA(HK_WINDOW_FRAME))) {
			HD_Downwind_Window_Frame (nr, _hoops_HPPGR);
		}	break;

		NODEFAULT;
#if 0
		default: {
			_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, Sprintf_D (null,
						"Unknown type '%d' in 'downwind'", _hoops_HPPGR->type));
			return;
		}	_hoops_HHHI;
#endif
		} // _hoops_CICA

	} while ((_hoops_HPPGR = _hoops_HPPGR->next) != null && _hoops_CAGIP);



	if (!BIT(dc->flags, _hoops_IRSI) &&
		dc->options._hoops_SIAH &&
		!BIT (nr->_hoops_IRR->_hoops_PPH, _hoops_HAI)) {
		_hoops_AHAH alter &		_hoops_PHAH = nr.Modify()->_hoops_ARA.Modify()->_hoops_IHRH;

		_hoops_PHAH.options = _hoops_CHRH | _hoops_HIGRP | _hoops_PIGRP;
		_hoops_PHAH._hoops_ACGRP = _hoops_CIGRP;
		_hoops_PHAH.color = _hoops_GPSR::_hoops_IAHHP;

		_hoops_HCHHP |= _hoops_HHIHP;

		// _hoops_RHGS _hoops_SRSGR _hoops_CGH _hoops_PGPS _hoops_PHHR _hoops_SGGR...
		nr.Modify()->_hoops_IRR.Modify()->_hoops_PPH |= (_hoops_HAI & ~_hoops_AHGI);
	}

	if (_hoops_RPGIP &&
		nr->transform_rendition->_hoops_SPH->projection == _hoops_GHH) {
		/* _hoops_SR _hoops_HHGC _hoops_RH _hoops_ARGR _hoops_GSSP _hoops_AHC _hoops_IIGR _hoops_RH _hoops_CARA _hoops_CGRS (_hoops_PGAP _hoops_SRIPR _hoops_IS _hoops_SHH _hoops_RH
		 * _hoops_HCHIA _hoops_ARIP _hoops_IIGR _hoops_RH _hoops_GCHRR _hoops_PRGIA _hoops_RSGA), _hoops_PPR _hoops_CACH _hoops_RSH _hoops_SGS _hoops_IIRIP _hoops_GPP _hoops_RH _hoops_RAR
		 * _hoops_AAGA.	_hoops_RH _hoops_AHHSR _hoops_IIGR _hoops_SGS _hoops_CCA _hoops_RH _hoops_SAAP _hoops_GIRA _hoops_CGH _hoops_PPGR _hoops_IH
		 * _hoops_RH _hoops_IGIR _hoops_AGRP _hoops_SAPGP _hoops_IS _hoops_AIHP
		 */
		_hoops_HHRA const *				_hoops_SPH = nr->transform_rendition->_hoops_SPH;
		_hoops_SGCC const &	_hoops_HSGA = nr->transform_rendition->_hoops_IPH;
		Point const *				origin = (Point const *)&_hoops_HSGA->data.elements[3][0];
		float						scale;
		_hoops_ISGI			temp;

		temp._hoops_RRHH = _hoops_RSPCR;

		/* '_hoops_GHGP' _hoops_IIGR _hoops_IPPA _hoops_PHGSR _hoops_RHIR _hoops_SARA _hoops_AHC */
		scale = -(_hoops_SPH->position.x * _hoops_SPH->_hoops_IIPCR.x +
				  _hoops_SPH->position.y * _hoops_SPH->_hoops_IIPCR.y +
				  _hoops_SPH->position.z * _hoops_SPH->_hoops_IIPCR.z);
		/* _hoops_PRRGR _hoops_CGRS _hoops_CIAA _hoops_SARA _hoops_AAGA _hoops_CSCHR _hoops_IS _hoops_SARA _hoops_AHC */
		scale += origin->x * _hoops_SPH->_hoops_IIPCR.x + origin->y * _hoops_SPH->_hoops_IIPCR.y + origin->z * _hoops_SPH->_hoops_IIPCR.z;
		/* _hoops_CSRA _hoops_RRPS _hoops_IS _hoops_SARA _hoops_GIRA */
		scale /= _hoops_SPH->_hoops_SRIR;

		/* _hoops_PSSSR _hoops_IH _hoops_AHCI _hoops_ARAR */
		if (scale < nr->transform_rendition->_hoops_CHCR)
			scale = nr->transform_rendition->_hoops_CHCR;

		HI_Figure_Scale_Matrix (scale, scale, scale, &temp.matrix);
		HD_Downwind_Modelling_Matrix (nr, (Attribute const *)&temp);
	}

	if (_hoops_HCHHP != _hoops_ICHHP && !BIT(dc->flags, _hoops_IRSI))
		HD_Fixup_Attributes (nr, _hoops_PCGS, _hoops_HCHHP);
}

local _hoops_HHRA const * _hoops_CIRIP (
	Attribute const *			_hoops_IPPGR) {
	_hoops_HHRA const *				_hoops_SPH = null;

	do {
		if (_hoops_IPPGR->type > _hoops_IAAA (HK_STYLE, HK_CAMERA))
			break;

		if (_hoops_IPPGR->type == HK_STYLE) {
			Style const *		style = (Style const *)_hoops_IPPGR;

			if (style->_hoops_IGRPR != null && style->_hoops_IGRPR->_hoops_IPPGR != null) {
				_hoops_HHRA const *	_hoops_SIRIP = _hoops_CIRIP (style->_hoops_IGRPR->_hoops_IPPGR);

				if (_hoops_SIRIP != null)
					_hoops_SPH = _hoops_SIRIP;
			}
		}
		else if (_hoops_IPPGR->type == HK_CAMERA) {
			_hoops_SPH = (_hoops_HHRA const *)_hoops_IPPGR;
			break;
		}
	} while ((_hoops_IPPGR = _hoops_IPPGR->next) != null);

	return _hoops_SPH;
}

#define	_hoops_GCRIP (_hoops_GRHH|_hoops_PRIR|_hoops_CSP|_hoops_RCRIP)

GLOBAL_FUNCTION void HD_Patch_Rendition (
	Net_Rendition alter &		nr,
	Net_Rendition const &		_hoops_ACRIP,
	_hoops_CRCP const *				_hoops_SRCP,
	_hoops_PSPGP alter &		_hoops_PCGPR) {
	Net_Rendition				upper = nr;
	Attribute const *			_hoops_IPPGR = _hoops_SRCP->_hoops_IPPGR;

	nr = _hoops_ACRIP.Copy();

	nr->current = upper->current;
	nr->_hoops_RCSHR = upper->_hoops_RCSHR;

	nr->_hoops_IHA.Modify()->_hoops_AGP = upper->_hoops_IHA->_hoops_AGP;
	nr->_hoops_RHP.Modify()->_hoops_AGP = upper->_hoops_RHP->_hoops_AGP;
	nr->_hoops_SCP.Modify()->_hoops_AGP = upper->_hoops_SCP->_hoops_AGP;

	nr->transform_rendition.Modify()->_hoops_RGH = upper->transform_rendition->_hoops_RGH;

	nr->transform_rendition->flags &= ~_hoops_GCRIP;
	nr->transform_rendition->flags |= upper->transform_rendition->flags & _hoops_GCRIP;

	if (BIT (_hoops_PCGPR, _hoops_ISPGP)) {
		_hoops_HHRA const *		_hoops_SPH = _hoops_CIRIP (_hoops_IPPGR);

		if (_hoops_SPH != null) {
			if (BIT (_hoops_SRCP->_hoops_PCGPR, _hoops_ISPGP))
				HD_Downwind_Camera (nr, _hoops_SPH);
			else
				_hoops_PCGPR &= ~_hoops_ISPGP;
		}
		else
			HD_Downwind_Camera (nr, upper->transform_rendition->_hoops_SPH);
	}
}

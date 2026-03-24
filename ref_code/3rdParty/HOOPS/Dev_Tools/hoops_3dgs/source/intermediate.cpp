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
 * $Id: obf_tmp.txt 1.416 2011-01-13 22:30:14 boni Exp $
 */

#include "hoops.h"
#include "hversion.h"
#include "database.h"
#include "driver.h"
#include "patterns.h"
#include "tandt.h"
#include "hd_proto.h"
#include "hi_proto.h"
#include "hpserror.h"
#include "phedron.h"
#include "select.h"
#include "adt.h"

#define BUILDING_HOOPS_INTERNALS
#include "hic.h"

#include "hic_calls.h"


#define _hoops_SCAPI			0,0,0,0
#define _hoops_GSAPI		0,0,0,0
#define IM_NO_VALUES		_hoops_SCAPI, _hoops_GSAPI
#define _hoops_RSAPI(_hoops_ASAPI)		(_hoops_ASAPI),0,0,0, _hoops_GSAPI
#define _hoops_PSAPI(_hoops_HSAPI)	_hoops_SCAPI,(_hoops_HSAPI),0,0,0
#define _hoops_ISAPI		0, IM_NO_VALUES

#ifndef DISABLE_CALLBACKS

local void _hoops_CSAPI (
	Geometry alter *	geo,
	Type				type) {

	geo->type = type;
	geo->_hoops_CPGPR = _hoops_PHSSR;
	geo->_hoops_RRHH = _hoops_HRPGI;
	geo->_hoops_SPGPR = false;
	geo->_hoops_HIHI = 1;
	geo->owner = null;
	geo->next = null;
	geo->backlink = null;
	geo->_hoops_IPPGR = null;
	geo->key = _hoops_AIRIR (geo);
} /* _hoops_RSGR _hoops_API _hoops_SSAPI  */


local void _hoops_GGPPI (
	Net_Rendition const & 	nr,
	void const *				_hoops_PHGH,
	int 						width,
	int 						height,
	Image_Format 			format,
	int 						row_bytes,
	float 						x,
	float 						y,
	float 						z) {
	DC_Point					start,
								end;
	void const *				_hoops_RGPPI[1024];
	void const * alter *		rasters = _hoops_RGPPI;
	void const * alter *		_hoops_SCGCR;
	int							count;
	int							bpp = -1;
	void const *				_hoops_RPPA = _hoops_PHGH;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	start.x = x;
	start.y = y;
	start.z = z;
	end.x = start.x + width - 1;
	end.y = start.y - height + 1;
	end.z = start.z;

	if (end.x < _hoops_IHCR->_hoops_AGAA.left || start.x > _hoops_IHCR->_hoops_AGAA.right ||
		end.y > _hoops_IHCR->_hoops_AGAA.top || start.y < _hoops_IHCR->_hoops_AGAA.bottom)
		return;			/* _hoops_SACH _hoops_SGGR */

	switch (format) {
		case _hoops_GGRH:
		case _hoops_RGRH:
		case _hoops_AGRH:
		case _hoops_IRRH:
		case _hoops_CRRH:
		case _hoops_SRRH:
		case _hoops_AHGH:
			ASSERT(0);  //_hoops_AGPPI _hoops_AGHS _hoops_GRS _hoops_HS _hoops_IS _hoops_SHH _hoops_GIR _hoops_RRAR
			break;

		case Image_MAPPED_8:	bpp = 1;		break;
		case Image_MAPPED_16:	bpp = 2;		break;
		case _hoops_HHGH:		bpp = 3;		break;
		case Image_RGBA32:
		case _hoops_HRSRH:
		case _hoops_CSGSP:		bpp = 4;		break;
		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "unexpected image format");
			bpp = 3;
			break;
	}

	if ((count = height) > _hoops_GGAPR (_hoops_RGPPI))
		ALLOC_ARRAY (rasters, height, void const *);

	if (row_bytes  == 0)
		row_bytes = bpp * width;

	_hoops_SCGCR = rasters;
	_hoops_RGGA (count-- <= 0) {
		*_hoops_SCGCR++ = _hoops_RPPA;
		_hoops_RPPA = (void const *)((char const *)_hoops_RPPA + row_bytes);
	}

	count = 0;			/* _hoops_PGPPI */
	_hoops_SCGCR = rasters;

	if (start.y > _hoops_IHCR->_hoops_AGAA.top) {
		_hoops_SCGCR += (int)start.y - _hoops_IHCR->_hoops_AGAA.top;
		start.y = (float)_hoops_IHCR->_hoops_AGAA.top;
	}
	if (end.y < _hoops_IHCR->_hoops_AGAA.bottom) {
		end.y = (float)_hoops_IHCR->_hoops_AGAA.bottom;
	}

	if (start.x < _hoops_IHCR->_hoops_AGAA.left) {
		count = _hoops_IHCR->_hoops_AGAA.left - (int)start.x;
		start.x = (float)_hoops_IHCR->_hoops_AGAA.left;
	}
	if (end.x > _hoops_IHCR->_hoops_AGAA.right) {
		end.x = (float)_hoops_IHCR->_hoops_AGAA.right;
	}


	_hoops_GACIP (nr, _hoops_HPCGA)(nr,
		&start, &end, count, format,
		row_bytes, _hoops_SCGCR, FP_SOLID, null, null);


	if (rasters != _hoops_RGPPI)
		FREE_ARRAY (rasters, height, void const *);
}

local void draw_3d_geometry (
	Net_Rendition const & 		_hoops_SGIIH,
	long						request,
	void const *				pointer,
	long						v) {
	Net_Rendition				nr = _hoops_SGIIH;
	_hoops_PSIHP alter &	_hoops_HSIHP = nr.Modify()->_hoops_RSGC.Modify();
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;
	_hoops_AAGSP *			_hoops_PAGSP = dc->_hoops_SPA;
	Geometry const *			g = (Geometry const *)pointer;
	Geometry const *			_hoops_HGPPI = dc->_hoops_RAI;;

	UNREFERENCED (request);
	UNREFERENCED (v);

	_hoops_HSIHP->action.draw_3d_marker = null;
	_hoops_HSIHP->action.draw_3d_polyline = null;
	_hoops_HSIHP->action.draw_3d_polygon = null;
	_hoops_HSIHP->action.draw_3d_text = null;
	_hoops_HSIHP->action.draw_3d_geometry = null;

	dc->_hoops_SPA = dc->_hoops_ISAGR;
	_hoops_GACIP (nr, _hoops_CHCI)(nr, g, _hoops_RAPI, true);
	dc->_hoops_SPA = _hoops_PAGSP;

	dc->_hoops_RAI = _hoops_HGPPI;
}

local void select_geometry (
	Net_Rendition const &		_hoops_SGIIH,
	long						request,
	void const *				pointer,
	long						v) {
	Net_Rendition				nr = _hoops_SGIIH;
	_hoops_PSIHP			_hoops_HSIHP = nr.Modify()->_hoops_RSGC.Modify();
	Geometry const *			g = (Geometry const *)pointer;

	UNREFERENCED (request);
	UNREFERENCED (v);

	_hoops_HSIHP->action.draw_3d_marker = null;
	_hoops_HSIHP->action.draw_3d_polyline = null;
	_hoops_HSIHP->action.draw_3d_polygon = null;
	_hoops_HSIHP->action.draw_3d_text = null;
	_hoops_HSIHP->action.draw_3d_geometry = null;

	HD_Selection_Render (nr, g, true);
}

local void _hoops_IGPPI (
	Net_Rendition const & 		nr,
	int							offset1,
	int							offset2,
	int							offset3,
	float						_hoops_CGPPI,
	float						_hoops_HCSAP) {
	Display_Context const *		dc = nr->_hoops_SRA;
	_hoops_GRGH const &		_hoops_RRGH = nr->_hoops_IRR;
	_hoops_ACHR					_hoops_SGPPI;
	_hoops_ACHR					_hoops_PCCAH;
	Geometry const *			geo;

	if ((geo = dc->_hoops_RAI) == null) {
		/* _hoops_PIHA _hoops_SHH _hoops_HII _hoops_IRS _hoops_CAGH-_hoops_PAPA _hoops_GHSHA _hoops_CAPGR */
		Segment_Info const *	si;

		if ((si = dc->_hoops_CHICP) == null) return;		/* _hoops_GRPPI? */

		geo = (Geometry const *)si->segment;
	}

	_hoops_SGPPI = _hoops_RRGH->_hoops_AAICA & (nr->_hoops_RGP | _hoops_RRGH->_hoops_PHARP);

	switch (geo->type) {
		case _hoops_PIIP:
		case _hoops_IIIP:
		case _hoops_RIIP:
		case _hoops_GIIP:
			_hoops_PCCAH = T_LINES;
			break;

		case _hoops_RCIP:
		case _hoops_SGCP:
		case _hoops_CGCP:
		case _hoops_GRCP:
		case _hoops_RRCP:
			_hoops_PCCAH = _hoops_SGPPI & (T_FACES | T_ANY_POLYGON_EDGE);
			break;

		case _hoops_PCIP:
			_hoops_PCCAH = T_MARKERS;
			break;

		case _hoops_AGCP:
			_hoops_PCCAH = T_TEXT;
			break;

		case _hoops_HGCP:
			_hoops_PCCAH = T_IMAGES;
			break;

		case _hoops_ICIP:
			_hoops_PCCAH = T_ANY_LIGHTS;
			break;

		case _hoops_GGCP:
			_hoops_PCCAH = _hoops_SGPPI & (T_VERTICES | T_FACES | T_ANY_GRID_EDGE);
			break;

		case _hoops_GSIP:
		case _hoops_SCIP:
			_hoops_PCCAH = _hoops_SGPPI & (T_VERTICES | T_FACES | T_ANY_EDGE);
			break;

		case _hoops_IRCP:
			_hoops_PCCAH = T_WINDOWS;
			break;

		default:
			_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "unexpected geometry");
			_hoops_PCCAH = (_hoops_ACHR)0L;
			_hoops_HHHI;
	}

	HD_Elaborate_Selection (nr, geo, geo->key, _hoops_AIRIR(geo),
							offset1, offset2, offset3,
							_hoops_CGPPI, _hoops_HCSAP,
							_hoops_PCCAH, null);
}


GLOBAL_FUNCTION void HD_Merge_User_Indices(_hoops_CIGIP const &_hoops_SIGIP)
{

	if (_hoops_SIGIP->_hoops_IGGSA == null)
		return;

	if (_hoops_SIGIP->_hoops_IGGSA->Count() > 1) {

		_hoops_HPPIR alter *	_hoops_RASGH = null;
		_hoops_HPPIR const *	_hoops_GASGH;

		_hoops_SIGIP->_hoops_IGGSA->Reverse();

		while ((_hoops_GASGH = _hoops_SIGIP->_hoops_IGGSA->RemoveFirst()) != null) {

			ASSERT(_hoops_GASGH->_hoops_AGGSA);
			ASSERT(_hoops_GASGH->_hoops_AGGSA->Count() > 0);

			if (!_hoops_RASGH) {

				if (_hoops_GASGH->_hoops_HIHI == 1) {
					// _hoops_RPRS
					_hoops_RASGH = (_hoops_HPPIR alter *)_hoops_GASGH;
					continue;
				} else {
					ZALLOC (_hoops_RASGH, _hoops_HPPIR);
					_hoops_RASGH->type = HK_USER_OPTIONS;
					_hoops_RASGH->_hoops_AGGSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_PGGSA)(_hoops_GASGH->_hoops_AGGSA);
					_hoops_PRRH(_hoops_RASGH);
				}
			}
			else
				_hoops_RASGH->_hoops_AGGSA->Merge(_hoops_GASGH->_hoops_AGGSA, VHASH_MERGE_REPLACE_DUPLICATES);

			_hoops_HPRH(_hoops_GASGH);
		}

		_hoops_SIGIP->_hoops_IGGSA->AddFirst(_hoops_RASGH);
	}

}

GLOBAL_FUNCTION void *HD_Show_User_Index(Net_Rendition const &nr, int index)
{
	
	_hoops_CIGIP _hoops_SIGIP = nr->_hoops_GCGIP;

	if (_hoops_SIGIP->_hoops_IGGSA == null || 
		_hoops_SIGIP->_hoops_IGGSA->Count() == 0)
		return null;

	if (_hoops_SIGIP->_hoops_IGGSA->Count() > 2)
		HD_Merge_User_Indices(_hoops_SIGIP);

	ASSERT(_hoops_SIGIP->_hoops_IGGSA->Count() <= 2);

	_hoops_HPPIR const * _hoops_IPPIR;
	_hoops_PGGSA::status status;
	void * value;

	_hoops_SIGIP->_hoops_IGGSA->ResetCursor();
	_hoops_IPPIR = _hoops_SIGIP->_hoops_IGGSA->PeekCursor();
	ASSERT(_hoops_IPPIR->_hoops_IGGSA == null);
	status = _hoops_IPPIR->_hoops_AGGSA->LookupItem(index, &value);
	if (status == VHASH_STATUS_SUCCESS) 
		return value;

	_hoops_SIGIP->_hoops_IGGSA->AdvanceCursor();
	_hoops_IPPIR = _hoops_SIGIP->_hoops_IGGSA->PeekCursor();
	if (_hoops_IPPIR) {
		ASSERT(_hoops_IPPIR->_hoops_IGGSA == null);
		status = _hoops_IPPIR->_hoops_AGGSA->LookupItem(index, &value);
		if (status == VHASH_STATUS_SUCCESS) 
			return value;
	}

	return null;
}


GLOBAL_FUNCTION void HD_Unwrap_Polytriangle (
	Net_Rendition const & 		nr,
	int							count,
	DC_Point const *			points) {
	int							_hoops_RRC;

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_SHICP (nr, draw_dc_triangle) (&nr, points);
		points += _hoops_RRC;
	}
}

GLOBAL_FUNCTION void HD_Unwrap_Colorized_Polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						single) {
	int							_hoops_RRC;

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_SHICP (nr, draw_dc_colorized_triangle) (&nr, points, colors);
		points += _hoops_RRC;
		if (!single)
			colors++;
	}
}

GLOBAL_FUNCTION void HD_Unwrap_Gouraud_Polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors) {
	int							_hoops_RRC;

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_SHICP (nr, draw_dc_gouraud_triangle) (&nr, points, colors);
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
}

GLOBAL_FUNCTION void HD_Unwrap_Reshaded_Polytriangle (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	_hoops_SSIC				param_flags) {
	int							_hoops_RRC;

	_hoops_ICHC (count, _hoops_RRC, 3);
	while (count-- > 0) {
		_hoops_SHICP (nr, draw_dc_reshaded_triangle) (&nr, points, colors, planes, params, param_width, param_flags);
		points += _hoops_RRC;
		if (colors)
			colors += _hoops_RRC;
		if (planes)
			planes += _hoops_RRC;
		if (params)
			params += _hoops_RRC * param_width;
	}
}


GLOBAL_FUNCTION void HD_Unwrap_Polyline (
	Net_Rendition const & 		nr,
	int							count,
	DC_Point const *			points) {
	int							_hoops_RRC;

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		_hoops_SHICP (nr, draw_dc_line) (&nr, points);
		points += _hoops_RRC;
	}
}

GLOBAL_FUNCTION void HD_Unwrap_Colorized_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						single) {
	int							_hoops_RRC;

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		_hoops_SHICP (nr, draw_dc_colorized_line) (&nr, points, colors);
		points += _hoops_RRC;
		if (!single)
			colors++;
	}
}

GLOBAL_FUNCTION void HD_Unwrap_Gouraud_Polyline (
	Net_Rendition const & 		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors) {
	int							_hoops_RRC;

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		_hoops_SHICP (nr, draw_dc_gouraud_line) (&nr, points, colors);
		points += _hoops_RRC;
		colors += _hoops_RRC;
	}
}

GLOBAL_FUNCTION void HD_Unwrap_Reshaded_Polyline (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBA const *				colors,
	_hoops_ARPA const *				planes,
	_hoops_RSSH const *			params,
	Integer32					param_width,
	_hoops_SSIC				param_flags) {
	int							_hoops_RRC;

	_hoops_ICHC (count, _hoops_RRC, 2);
	while (count-- > 0) {
		_hoops_SHICP (nr, draw_dc_reshaded_line) (&nr, points, colors, planes, params, param_width, param_flags);
		points += _hoops_RRC;
		if (colors)
			colors += _hoops_RRC;
		if (planes)
			planes += _hoops_RRC;
		if (params)
			params += _hoops_RRC * param_width;
	}
}


GLOBAL_FUNCTION void HD_Unwrap_Polymarker (
	Net_Rendition const & 		nr,
	int							count,
	DC_Point const *			points,
	float const *				rotations,
	float const *				size_fixups) {

	UNREFERENCED(rotations);
	UNREFERENCED(size_fixups);

	while (count-- > 0) {
		_hoops_SHICP (nr, draw_dc_marker) (&nr, points);
		points++;
	}
}

GLOBAL_FUNCTION void HD_Unwrap_Colorized_Polymarker (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points,
	RGBAS32 const *				colors,
	bool						single,
	float const *				rotations,
	float const *				size_fixups) {

	UNREFERENCED(rotations);
	UNREFERENCED(size_fixups);

	while (count-- > 0) {
		_hoops_SHICP (nr, draw_dc_colorized_marker) (&nr, points, colors);
		points++;
		if (!single)
			colors++;
	}
}


GLOBAL_FUNCTION Point const * HD_Compute_Transformed_Text_Position(
	Net_Rendition const & 		nr,
	Text_Info alter *			ti,
	Point const *				p) {
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	Point const *				start = p;
	Point const *				_hoops_RRPPI = &ti->_hoops_IPPSP;
	Point const *				ref = &ti->_hoops_CSAGR;
	Point const *				_hoops_CRIPA = &ti->_hoops_HPPSP;
	Vector const *				scale = &ti->scale;
	Point						_hoops_CSAI;

	/* _hoops_PHPHA _hoops_HII _hoops_ARPPI */

	switch (_hoops_HRCIR->transform) {
		case FT_NONE:	break;			/* _hoops_RHRH */

		case FT_POSITION_ONLY:
		case FT_POSITION_ADJUSTED:
		case FT_FULL: {
			_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
			_hoops_RPRA const *			elements = _hoops_IHCR->matrix->data.elements;
			Point						point = _hoops_HPCH::_hoops_IPCH;

			_hoops_CSAI = *_hoops_RRPPI;

			if (_hoops_HRCIR->transform == FT_FULL) {
				_hoops_CSAI.x += (start->x - ref->x) * scale->x;
				_hoops_CSAI.y += (start->y - ref->y) * scale->y;
				_hoops_CSAI.z += (start->z - ref->z) * scale->z;
			}
			else {
				_hoops_CSAI.x += (start->x - ref->x - _hoops_CRIPA->x) * scale->x;
				_hoops_CSAI.y += (start->y - ref->y - _hoops_CRIPA->y) * scale->y;
				_hoops_CSAI.z += (start->z - ref->z - _hoops_CRIPA->z) * scale->z;
			}

			switch (_hoops_IHCR->_hoops_HGSC) {
				case _hoops_SIPHP: {
					point.x = _hoops_CSAI.x;
					point.y = _hoops_CSAI.y;
					point.z = 0.0f;
				}	break;

				case _hoops_CIPHP: {
					point.x = _hoops_PRPPI (elements, _hoops_CSAI);
					point.y = _hoops_HRPPI (elements, _hoops_CSAI);
					point.z = 0.0f;
				}	break;

				case _hoops_PCPHP: {
					point.x = _hoops_HPRA (elements, _hoops_CSAI);
					point.y = _hoops_IPRA (elements, _hoops_CSAI);
					point.z = 0.0f;
				}	break;

				case _hoops_RCPHP: {
					float			w;

					w = _hoops_PHCP (elements, _hoops_CSAI);
					if (w <= _hoops_IHCR->_hoops_CHCR)
						return null;

					point.x = _hoops_HPRA (elements, _hoops_CSAI) / w;
					point.y = _hoops_IPRA (elements, _hoops_CSAI) / w;
					point.z = 0.0f;
				}	break;

				case _hoops_ACPHP: {
					point.x = _hoops_HPRA (elements, _hoops_CSAI);
					point.y = _hoops_IPRA (elements, _hoops_CSAI);
					point.z = _hoops_CPRA (elements, _hoops_CSAI);
					point.z = _hoops_IGSC (point.z, _hoops_IHCR);
				}	break;

				case _hoops_GCPHP: {
					float			w;

					w = _hoops_PHCP (elements, _hoops_CSAI);
					if (w <= _hoops_IHCR->_hoops_CHCR)
						return null;

					point.x = _hoops_HPRA (elements, _hoops_CSAI) / w;
					point.y = _hoops_IPRA (elements, _hoops_CSAI) / w;
					point.z = _hoops_CPRA (elements, _hoops_CSAI) / w;
					point.z = _hoops_IGSC (point.z, _hoops_IHCR);
				}	break;
			}

			if (_hoops_HRCIR->transform == FT_FULL) {
				ti->_hoops_AGRI.x = point.x;
				ti->_hoops_AGRI.y = point.y;
				ti->_hoops_AGRI.z = point.z;
			}
			else {
				ti->_hoops_AGRI.x = point.x + _hoops_CRIPA->x;
				ti->_hoops_AGRI.y = point.y + _hoops_CRIPA->y;
				ti->_hoops_AGRI.z = point.z + _hoops_CRIPA->z;
			}
		}	break;
	}

	return (Point const *)&ti->_hoops_AGRI;
}


/* _hoops_IIHHP _hoops_HII _hoops_SAPS _hoops_PPSR [0..1] _hoops_AIHSR _hoops_HCPC _hoops_IS _hoops_HISI _hoops_HAIR _hoops_GHARR _hoops_HRGR _hoops_CISI _hoops_GPP _hoops_RH _hoops_RHPP */

GLOBAL_FUNCTION void HD_Figure_Driver_Color (
	Net_Rendition const & 		nr,
	RGB const *					rgb,
	Driver_Color alter *		_hoops_CPHHP) {
	Display_Context const *		dc = nr->_hoops_SRA;

	*_hoops_CPHHP = _hoops_CAHSR::_hoops_SAHSR;

	if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR) {
		_hoops_CPHHP->_hoops_HRIR.r = (unsigned char)(255.99f * rgb->red);
		_hoops_CPHHP->_hoops_HRIR.g = (unsigned char)(255.99f * rgb->green);
		_hoops_CPHHP->_hoops_HRIR.b = (unsigned char)(255.99f * rgb->blue);
		_hoops_CPHHP->_hoops_HRIR.a = 255;
	}
	else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
		RGB const *		_hoops_IHPCR;
		RGB const *		lowest;

		/* _hoops_SRS _hoops_IHSH _hoops_IH _hoops_RIRA _hoops_PSSP _hoops_HPP _hoops_SGGHA _hoops_RHIR _hoops_RH _hoops_ARCR */
		lowest = dc->_hoops_CHHIP + dc->_hoops_PGCC._hoops_APASR;
		_hoops_IHPCR = lowest + dc->_hoops_PGCC._hoops_AAPSR;

		_hoops_RGGA (--_hoops_IHPCR < lowest) {
			if (Abs (rgb->red - _hoops_IHPCR->red) < 0.015f &&
				Abs (rgb->green - _hoops_IHPCR->green) < 0.015f &&
				Abs (rgb->blue - _hoops_IHPCR->blue) < 0.015f) {
				_hoops_CPHHP->_hoops_PGGCR = _hoops_IHPCR - dc->_hoops_CHHIP;
				return;
			}
		}

		/* _hoops_SCRRI _hoops_IH _hoops_IRS _hoops_IRPPI _hoops_PSSP */
		_hoops_IHPCR = lowest + dc->_hoops_PGCC._hoops_AAPSR;

		_hoops_RGGA (--_hoops_IHPCR < lowest) {
			if (Abs (rgb->red - _hoops_IHPCR->red) < 0.1f &&
				Abs (rgb->green - _hoops_IHPCR->green) < 0.1f &&
				Abs (rgb->blue - _hoops_IHPCR->blue) < 0.1f) {
				_hoops_CPHHP->_hoops_PGGCR = _hoops_IHPCR - dc->_hoops_CHHIP;
				return;
			}
		}

		/* _hoops_PAR _hoops_PRGI _hoops_IRS _hoops_CPSA _hoops_AHCI _hoops_SPR */
		_hoops_IHPCR = lowest + dc->_hoops_PGCC._hoops_AAPSR;

		_hoops_RGGA (--_hoops_IHPCR < lowest) {
			if (Abs (rgb->red - _hoops_IHPCR->red) < 0.3f &&
				Abs (rgb->green - _hoops_IHPCR->green) < 0.3f &&
				Abs (rgb->blue - _hoops_IHPCR->blue) < 0.3f) {
				_hoops_CPHHP->_hoops_PGGCR = _hoops_IHPCR - dc->_hoops_CHHIP;
				return;
			}
		}

		/* _hoops_RPP _hoops_SR _hoops_HGCR _hoops_ARI, _hoops_RCRP _hoops_GH */
	}
	else {
		float	_hoops_CRPPI;

		_hoops_CRPPI = (float)dc->_hoops_PGCC._hoops_PCHSR - 0.01f;
		_hoops_CPHHP->_hoops_PIHHP = (_hoops_HIHHP)(_hoops_CRPPI * rgb->_hoops_CPIR());
	}

}

local void _hoops_SRPPI (
	Net_Rendition alter & 				nr) {
	_hoops_HHCR alter &			_hoops_IHCR = nr->transform_rendition;
	_hoops_SGCC const &			mat = _hoops_IHCR->_hoops_CGCC;
	_hoops_GPPA alter *		_hoops_IRCAR;
	_hoops_GPPA alter **		_hoops_SAGGA;
	_hoops_IAPA alter *			_hoops_HRCAR;
	int									i;

	if (!ANYBIT (nr->current,
				 _hoops_RSSHP|_hoops_CISHP))
		return;

	_hoops_IHCR->flags |= _hoops_CSP;

	if (_hoops_IHCR->_hoops_RGH == null) {
		_hoops_IHCR->_hoops_RGH = _hoops_SSP::Create(nr->_hoops_SRA);
		_hoops_IHCR->flags |= _hoops_CSP | _hoops_HHGGA;
	}

	_hoops_SSP alter &		_hoops_GGH = _hoops_IHCR->_hoops_RGH.Modify();


	if (!BIT (_hoops_IHCR->flags, _hoops_IGCC))
		HD_Validate_World_To_Screen (nr);

	if ((_hoops_HRCAR = (_hoops_IAPA *)_hoops_GGH->_hoops_ISIGA) == null) {
		ZALLOC (_hoops_HRCAR, _hoops_IAPA);
		_hoops_GGH->_hoops_ISIGA = _hoops_HRCAR;
	}
	_hoops_SAGGA = (_hoops_GPPA alter **)&_hoops_HRCAR->_hoops_APPA;
	if (*_hoops_SAGGA != null) {
		do {}
		_hoops_RGGA (*(_hoops_SAGGA = &(*_hoops_SAGGA)->next) == null);
	}

	for (i=0; i<4; i++) {
		ZALLOC (_hoops_IRCAR, _hoops_GPPA);
		*_hoops_SAGGA = _hoops_IRCAR;
		_hoops_SAGGA = &_hoops_IRCAR->next;
		_hoops_IRCAR->next = null;
		_hoops_IRCAR->internal = true;
		_hoops_IRCAR->id = _hoops_GGH->_hoops_AHASP++;

		if (++_hoops_HRCAR->_hoops_IPASP > _hoops_GGH->_hoops_PGH)
			_hoops_GGH->_hoops_PGH = _hoops_HRCAR->_hoops_IPASP;

		switch (i) {
			case 0: {
				_hoops_IRCAR->_hoops_SPPA.a = -1.0f;
				_hoops_IRCAR->_hoops_SPPA.b = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.c = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.d = (float)_hoops_IHCR->_hoops_AGAA.left;
			}	break;
			case 1: {
				_hoops_IRCAR->_hoops_SPPA.a = 1.0f;
				_hoops_IRCAR->_hoops_SPPA.b = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.c = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.d = -(float)_hoops_IHCR->_hoops_AGAA.right;
			}	break;
			case 2: {
				_hoops_IRCAR->_hoops_SPPA.a = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.b = -1.0f;
				_hoops_IRCAR->_hoops_SPPA.c = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.d = (float)_hoops_IHCR->_hoops_AGAA.bottom;
			}	break;
			case 3: {
				_hoops_IRCAR->_hoops_SPPA.a = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.b = 1.0f;
				_hoops_IRCAR->_hoops_SPPA.c = 0.0f;
				_hoops_IRCAR->_hoops_SPPA.d = -(float)_hoops_IHCR->_hoops_AGAA.top;
			}	break;
		}

		_hoops_IRCAR->_hoops_SHPA.a =
				   mat->data.elements[0][0] * _hoops_IRCAR->_hoops_SPPA.a +
				   mat->data.elements[0][1] * _hoops_IRCAR->_hoops_SPPA.b +
				   mat->data.elements[0][2] * _hoops_IRCAR->_hoops_SPPA.c +
				   mat->data.elements[0][3] * _hoops_IRCAR->_hoops_SPPA.d;

		_hoops_IRCAR->_hoops_SHPA.b =
				   mat->data.elements[1][0] * _hoops_IRCAR->_hoops_SPPA.a +
				   mat->data.elements[1][1] * _hoops_IRCAR->_hoops_SPPA.b +
				   mat->data.elements[1][2] * _hoops_IRCAR->_hoops_SPPA.c +
				   mat->data.elements[1][3] * _hoops_IRCAR->_hoops_SPPA.d;

		_hoops_IRCAR->_hoops_SHPA.c =
				   mat->data.elements[2][0] * _hoops_IRCAR->_hoops_SPPA.a +
				   mat->data.elements[2][1] * _hoops_IRCAR->_hoops_SPPA.b +
				   mat->data.elements[2][2] * _hoops_IRCAR->_hoops_SPPA.c +
				   mat->data.elements[2][3] * _hoops_IRCAR->_hoops_SPPA.d;

		_hoops_IRCAR->_hoops_SHPA.d =
				   mat->data.elements[3][0] * _hoops_IRCAR->_hoops_SPPA.a +
				   mat->data.elements[3][1] * _hoops_IRCAR->_hoops_SPPA.b +
				   mat->data.elements[3][2] * _hoops_IRCAR->_hoops_SPPA.c +
				   mat->data.elements[3][3] * _hoops_IRCAR->_hoops_SPPA.d;

		if (!HI_Normalize_Plane (&_hoops_IRCAR->_hoops_SHPA))
			HE_WARNING (HEC_CUTTING_PLANE, HES_SINGULAR_PLANE,
					"A cutting plane became singular after transforming");
	}

	HD_Validate_Cutting_Plane_Sets (_hoops_GGH);
}

GLOBAL_FUNCTION void HD_Remove_Cutting_Planes(Net_Rendition alter & nr)
{
	_hoops_HHCR alter &		_hoops_IHCR = nr->transform_rendition;

	_hoops_IHCR->_hoops_RGH = null;
	_hoops_IHCR->flags &= ~(_hoops_CSP | _hoops_HHGGA);
}

GLOBAL_FUNCTION void HD_Add_Cutting_Plane (
	Net_Rendition alter &			nr,
	_hoops_ARPA const *					plane) {
	_hoops_HHCR alter &		_hoops_IHCR = nr->transform_rendition;
	_hoops_SGCC const &		mat = _hoops_IHCR->_hoops_CGCC;
	_hoops_GPPA alter *	_hoops_IRCAR;
	_hoops_GPPA alter **	_hoops_SAGGA;
	_hoops_IAPA alter *		_hoops_HRCAR;

	if (plane->a == 0.0f && plane->b == 0.0f && plane->c == 0.0f) {
		HE_WARNING (HEC_CUTTING_PLANE, HES_SINGULAR_PLANE,
				"An invalid cutting plane was specified");
		return;
	}

	if (_hoops_IHCR->_hoops_RGH == null) {
		_hoops_IHCR->_hoops_RGH = _hoops_SSP::Create(nr->_hoops_SRA);
		_hoops_IHCR->flags |= _hoops_CSP | _hoops_HHGGA;
	}

	_hoops_SSP alter &		_hoops_GGH = _hoops_IHCR->_hoops_RGH.Modify();


	if (!BIT (_hoops_IHCR->flags, _hoops_IGCC))
		HD_Validate_World_To_Screen (nr);

	_hoops_RPRA const * _hoops_APRA = mat->_hoops_PPRA()->data.elements;

	if ((_hoops_HRCAR = (_hoops_IAPA *)_hoops_GGH->_hoops_ISIGA) == null) {
		ZALLOC (_hoops_HRCAR, _hoops_IAPA);
		_hoops_GGH->_hoops_ISIGA = _hoops_HRCAR;
	}
	_hoops_SAGGA = (_hoops_GPPA alter **)&_hoops_HRCAR->_hoops_APPA;
	if (*_hoops_SAGGA != null) {
		do {}
		_hoops_RGGA (*(_hoops_SAGGA = &(*_hoops_SAGGA)->next) == null);
	}

	ZALLOC (_hoops_IRCAR, _hoops_GPPA);
	*_hoops_SAGGA = _hoops_IRCAR;
	_hoops_IRCAR->next = null;
	if (++_hoops_HRCAR->_hoops_IPASP > _hoops_GGH->_hoops_PGH)
		_hoops_GGH->_hoops_PGH = _hoops_HRCAR->_hoops_IPASP;
	_hoops_IRCAR->internal = false;
	_hoops_IRCAR->id = _hoops_GGH->_hoops_AHASP++;

	_hoops_IRCAR->_hoops_SHPA.a = plane->a;
	_hoops_IRCAR->_hoops_SHPA.b = plane->b;
	_hoops_IRCAR->_hoops_SHPA.c = plane->c;
	_hoops_IRCAR->_hoops_SHPA.d = plane->d;

	HI_Normalize_Plane (&_hoops_IRCAR->_hoops_SHPA);

	_hoops_IRCAR->_hoops_SPPA.a =
			   _hoops_APRA[0][0] * _hoops_IRCAR->_hoops_SHPA.a +
			   _hoops_APRA[0][1] * _hoops_IRCAR->_hoops_SHPA.b +
			   _hoops_APRA[0][2] * _hoops_IRCAR->_hoops_SHPA.c +
			   _hoops_APRA[0][3] * _hoops_IRCAR->_hoops_SHPA.d;

	_hoops_IRCAR->_hoops_SPPA.b =
			   _hoops_APRA[1][0] * _hoops_IRCAR->_hoops_SHPA.a +
			   _hoops_APRA[1][1] * _hoops_IRCAR->_hoops_SHPA.b +
			   _hoops_APRA[1][2] * _hoops_IRCAR->_hoops_SHPA.c +
			   _hoops_APRA[1][3] * _hoops_IRCAR->_hoops_SHPA.d;

	_hoops_IRCAR->_hoops_SPPA.c =
			   _hoops_APRA[2][0] * _hoops_IRCAR->_hoops_SHPA.a +
			   _hoops_APRA[2][1] * _hoops_IRCAR->_hoops_SHPA.b +
			   _hoops_APRA[2][2] * _hoops_IRCAR->_hoops_SHPA.c +
			   _hoops_APRA[2][3] * _hoops_IRCAR->_hoops_SHPA.d;

	_hoops_IRCAR->_hoops_SPPA.d =
			   _hoops_APRA[3][0] * _hoops_IRCAR->_hoops_SHPA.a +
			   _hoops_APRA[3][1] * _hoops_IRCAR->_hoops_SHPA.b +
			   _hoops_APRA[3][2] * _hoops_IRCAR->_hoops_SHPA.c +
			   _hoops_APRA[3][3] * _hoops_IRCAR->_hoops_SHPA.d;

	HI_Normalize_Plane (&_hoops_IRCAR->_hoops_SPPA);

	HD_Validate_Cutting_Plane_Sets (_hoops_GGH);
}

GLOBAL_FUNCTION void HD_Draw_Window (Net_Rendition const & nr, Int_Rectangle const * extent)
{
	_hoops_HCSIR alter		*_hoops_GAPPI = null;

	if (nr->_hoops_SAIR->_hoops_ASSIR != null &&
		(_hoops_GAPPI = nr->_hoops_SAIR->_hoops_ASSIR->_hoops_PSSIR()) != null)
			_hoops_GAPPI->_hoops_GRGSP = true;

	_hoops_GACIP (nr, draw_window)(nr, extent);

	if (_hoops_GAPPI != null)
		_hoops_GAPPI->_hoops_GRGSP = false;
}

GLOBAL_FUNCTION void HD_Free_User_Face_Pattern(_hoops_SIHHP const *u)
{
	_hoops_SIHHP alter *up = (_hoops_SIHHP alter *)u;

	if (up != null) {
		if (_hoops_ISAI (up) == 0) {
			if (up->pattern != null)
				FREE_ARRAY (up->pattern, up->width * up->height, unsigned char);

			FREE (up, _hoops_SIHHP);
		}
	}
}


GLOBAL_FUNCTION _hoops_ASHH * HD_New_Convex_Clip_Region (
	Net_Rendition const &		nr,
	int							count,
	DC_Point const *			points) {
	_hoops_ASHH *		_hoops_CRAIR;
	DC_Point const *			prev;
	int							i, j;

	UNREFERENCED (nr);

	ZALLOC (_hoops_CRAIR, _hoops_ASHH);
	_hoops_ICAI (_hoops_CRAIR);
	_hoops_CRAIR->count = count;

	/* _hoops_RPR _hoops_GRAA-_hoops_SSRS _hoops_RSSA */
	prev = points;
	for (i=1; i<count; i++) {
		if (points[i].x == prev->x && points[i].y == prev->y) {
			--_hoops_CRAIR->count;
		}
		else
			prev = &points[i];
	}
	if (points[0].x == prev->x && points[0].y == prev->y)
		--_hoops_CRAIR->count;

	if (_hoops_CRAIR->count == 0) /* _hoops_PSSSR _hoops_IH _hoops_CCGC _hoops_ARHAR _hoops_ARAR */
		_hoops_CRAIR->count = 1;

	ALLOC_ARRAY (_hoops_CRAIR->points, _hoops_CRAIR->count, DC_Point);

	/* _hoops_IPS _hoops_HSGS _hoops_RSSA & _hoops_GRAS _hoops_IASC */
	j = 0;
	_hoops_CRAIR->points[j].x = points->x;
	_hoops_CRAIR->points[j].y = points->y;
	_hoops_CRAIR->points[j].z = 0.0f;

	_hoops_CRAIR->_hoops_RCHS.left = _hoops_CRAIR->_hoops_RCHS.right = points->x;
	_hoops_CRAIR->_hoops_RCHS.bottom = _hoops_CRAIR->_hoops_RCHS.top = points->y;

	prev = points++;
	j++;
	for (i=1; i<count; i++) {
		if (points->x != prev->x || points->y != prev->y) {
			_hoops_CRAIR->points[j].x = points->x;
			_hoops_CRAIR->points[j].y = points->y;
			_hoops_CRAIR->points[j].z = 0.0f;

			if (points->x < _hoops_CRAIR->_hoops_RCHS.left)
				_hoops_CRAIR->_hoops_RCHS.left = points->x;
			else if (points->x > _hoops_CRAIR->_hoops_RCHS.right)
				_hoops_CRAIR->_hoops_RCHS.right = points->x;
			if (points->y < _hoops_CRAIR->_hoops_RCHS.bottom)
				_hoops_CRAIR->_hoops_RCHS.bottom = points->y;
			else if (points->y > _hoops_CRAIR->_hoops_RCHS.top)
				_hoops_CRAIR->_hoops_RCHS.top = points->y;

			if (++j == _hoops_CRAIR->count)
				break;	/* _hoops_GII _hoops_RSSA _hoops_HHRPA _hoops_PIHA _hoops_SHH _hoops_HSSPR _hoops_IGAPA */
		}
		prev = points++;
	}

	return _hoops_CRAIR;
}


GLOBAL_FUNCTION void HD_Free_Convex_Clip_Region (_hoops_ASHH const *v)
{
	_hoops_ASHH alter * victim = (_hoops_ASHH alter *)v;

	if (!victim)
		return;

	if (_hoops_ISAI (victim) == 0) {
		if (victim->next)
			HD_Free_Convex_Clip_Region (victim->next);
		FREE_ARRAY (victim->points, victim->count, DC_Point);
		if (victim->_hoops_GRCPR != null)
			FREE_ARRAY (victim->_hoops_GRCPR, victim->count, _hoops_GPPA);
		FREE (victim, _hoops_ASHH);
	}
}

GLOBAL_FUNCTION float HD_Compute_Character_Width(Net_Rendition const & nr, Text_Info alter	*ti, int index)
{
	_hoops_IGCSR const &	_hoops_HRCIR = nr->_hoops_SISI;
	Karacter const *		_hoops_IHSCP = ti->_hoops_SIHSA._hoops_IPPPP;
	float					width;

	HD_Measure_Characters (nr, 1, _hoops_IHSCP + index, ti->text->encoding, &width);
	width *= _hoops_HRCIR->width_scale;

	return width;
}

GLOBAL_FUNCTION Point const * HD_Compute_Character_Position(Net_Rendition const & nr, Text_Info alter *ti, int index)
{
	_hoops_IGCSR const &	_hoops_HRCIR = nr->_hoops_SISI;
	Karacter const *		_hoops_IHSCP = ti->_hoops_SIHSA._hoops_IPPPP;
	_hoops_HACC const *			text = ti->text;
	float					_hoops_RAPPI, _hoops_AAPPI;
	float					_hoops_CGSIR;
	float					_hoops_CCCRP;

	ti->_hoops_AGRI.x = ti->position.x;
	ti->_hoops_AGRI.y = ti->position.y;
	ti->_hoops_AGRI.z = ti->position.z;

	/* _hoops_GSPPA _hoops_SRSGR _hoops_HPRGR _hoops_ASCA _hoops_RRGR */
	HD_Measure_Characters (nr, 1, _hoops_IHSCP, text->encoding, &_hoops_RAPPI);
	_hoops_RAPPI *= _hoops_HRCIR->width_scale;
	if (index > 0) _hoops_PCCAR {
		HD_Measure_Characters (nr, 1, ++_hoops_IHSCP, text->encoding, &_hoops_AAPPI);
		_hoops_AAPPI *= _hoops_HRCIR->width_scale;

		if (_hoops_HRCIR->_hoops_HCRIP)
			_hoops_CGSIR = ti->_hoops_SHPSP / (float)(text->count - 1);
		else
			_hoops_CGSIR = ti->_hoops_AHPSP.x * 0.5f * (_hoops_RAPPI + _hoops_AAPPI) +
						ti->_hoops_AHPSP.y + ti->_hoops_AHPSP.z + ti->_hoops_PCPAP;

		_hoops_CCCRP = 0.5f * (_hoops_RAPPI - _hoops_AAPPI);

		ti->_hoops_AGRI.x += ti->path.x * _hoops_CGSIR	+  ti->_hoops_GHPSP.x * _hoops_CCCRP;
		ti->_hoops_AGRI.y += ti->path.y * _hoops_CGSIR	+  ti->_hoops_GHPSP.y * _hoops_CCCRP;
		ti->_hoops_AGRI.z += ti->path.z * _hoops_CGSIR; /* _hoops_PAPPI->_hoops_HAPPI._hoops_SSH _hoops_HRGR _hoops_SHR 0 */

		if (--index == 0)
			break;

		_hoops_RAPPI = _hoops_AAPPI;
	}

	return (Point const *)&ti->_hoops_AGRI;
}


local void * HIC_Intermediate_Utility (
	HIC_Rendition const *	inr,
	long					request,
	void alter *			pointer,
	HC_POINTER_SIZED_INT	_hoops_ISPI,
	HC_POINTER_SIZED_INT	_hoops_CSPI,
	HC_POINTER_SIZED_INT	_hoops_SSPI,
	HC_POINTER_SIZED_INT	_hoops_SGHI,
	float 					f1,
	float 					f2,
	float 					_hoops_CGHGR,
	float 					_hoops_SGHGR) {

	UNREFERENCED(_hoops_SGHGR);

#ifndef DISABLE_CALLBACKS
	Net_Rendition alter &	nr = *(Net_Rendition alter *)inr;

	switch (request) {

		case _hoops_ARGCH: {
			Display_Context const *		dc = nr->_hoops_SRA;

			/* _hoops_SPASR _hoops_IAPPI _hoops_IH _hoops_CAPPI */
			if (!BIT(dc->_hoops_PGCC.flags, _hoops_CAPGH) ||
				!_hoops_AGGR (dc->_hoops_PGCC._hoops_ICHSR,
								   "frame buffer"))
				return null;
			else {
				if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_HIHSR)
					return (void alter *)24;
				else if (dc->_hoops_PGCC._hoops_PIHSR == _hoops_SIHSR) {
					int		planes = 1;

					_hoops_RGGA ((1<<planes) >= dc->_hoops_PGCC._hoops_AAPSR)
						++planes;
					return (void alter *)(POINTER_SIZED_INT)planes;
				}
				else /* _hoops_AIHHP */
					return (void alter *)1;
			}
		}	_hoops_HHHI;

		case _hoops_APCCH: {
			nr->transform_rendition.Modify()->flags |= _hoops_CASP;
		} break;

		case _hoops_PPCCH: {
			nr->transform_rendition.Modify()->flags &= ~_hoops_CASP;
		} break;

		case _hoops_PRGCH: {
			return (void alter *)&nr->transform_rendition.Modify();
		}	_hoops_HHHI;

		case _hoops_PAGCH: {
			nr->_hoops_SAIR.Modify();

			return (void alter *)&nr->_hoops_SAIR;
		}	_hoops_HHHI;

		case _hoops_HRGCH: {
			nr->_hoops_AHP.Modify()->_hoops_CHA.Modify();

			return (void alter *)&nr->_hoops_AHP;
		}	_hoops_HHHI;

		case _hoops_IRGCH: {
			nr->_hoops_RHP.Modify()->_hoops_CHA.Modify();

			return (void alter *)&nr->_hoops_RHP;
		}	_hoops_HHHI;

		case _hoops_CGRCH: {
			nr->_hoops_CAIHP.Modify()->_hoops_CHA.Modify();

			return (void alter *)&nr->_hoops_CAIHP;
		}	_hoops_HHHI;

		case _hoops_CRGCH: {
			_hoops_CIGA alter &		_hoops_CPIHP = nr->_hoops_IHA;


			if (_hoops_ISPI)		/* _hoops_ISSC */
				_hoops_CPIHP->_hoops_GIA.Modify();
			else {
				if (_hoops_CPIHP->_hoops_GIA == _hoops_CPIHP->_hoops_CHA) {
					_hoops_CPIHP->_hoops_CHA.Modify();
					_hoops_CPIHP->_hoops_GIA = _hoops_CPIHP->_hoops_CHA;
				}
				else
					_hoops_CPIHP->_hoops_CHA.Modify();
			}

			return (void alter *)&nr->_hoops_IHA;
		}	_hoops_HHHI;

		case _hoops_IGRCH: {
			_hoops_CIGA alter &		_hoops_CPIHP = nr->_hoops_HAIHP;

			if (_hoops_ISPI)		/* _hoops_ISSC */
				_hoops_CPIHP->_hoops_GIA.Modify();
			else {
				if (_hoops_CPIHP->_hoops_GIA == _hoops_CPIHP->_hoops_CHA) {
					_hoops_CPIHP->_hoops_CHA.Modify();
					_hoops_CPIHP->_hoops_GIA = _hoops_CPIHP->_hoops_CHA;
				}
				else
					_hoops_CPIHP->_hoops_CHA.Modify();
			}

			return (void alter *)&nr->_hoops_HAIHP;
		}	_hoops_HHHI;

		case _hoops_HGRCH: {
			_hoops_CIGA alter &		_hoops_CPIHP = nr->_hoops_AAIHP;

			if (_hoops_ISPI)		/* _hoops_ISSC */
				_hoops_CPIHP->_hoops_GIA.Modify();
			else {
				if (_hoops_CPIHP->_hoops_GIA == _hoops_CPIHP->_hoops_CHA) {
					_hoops_CPIHP->_hoops_CHA.Modify();
					_hoops_CPIHP->_hoops_GIA = _hoops_CPIHP->_hoops_CHA;
				}
				else
					_hoops_CPIHP->_hoops_CHA.Modify();
			}

			return (void alter *)&nr->_hoops_AAIHP;
		}	_hoops_HHHI;

		case _hoops_SRGCH: {
			nr->_hoops_GSP.Modify();

			return (void alter *)&nr->_hoops_GSP;
		}	_hoops_HHHI;

		case _hoops_PCGCH: {
			nr->_hoops_SCP.Modify();

			return (void alter *)&nr->_hoops_SCP;
		}	_hoops_HHHI;

		case _hoops_GAGCH: {
			nr->_hoops_IRR.Modify();

			return (void alter *)&nr->_hoops_IRR;
		}	_hoops_HHHI;

		case _hoops_ARRCH: {
			nr->_hoops_CPP.Modify();

			return (void alter *)&nr->_hoops_CPP;
		}	_hoops_HHHI;

		case _hoops_SGRCH: {
			nr->_hoops_ARA.Modify();

			return (void alter *)&nr->_hoops_ARA;
		}	_hoops_HHHI;

		case _hoops_RAGCH: {
			nr->_hoops_ASIR.Modify()->_hoops_PSIR.Modify();

			return (void alter *)&nr->_hoops_ASIR->_hoops_PSIR;
		}	_hoops_HHHI;

		case _hoops_AAGCH: {
			_hoops_IGCSR alter &	_hoops_IRRIP = nr->_hoops_SISI.Modify();

			_hoops_IRRIP->_hoops_CHA.Modify();
			_hoops_IRRIP->_hoops_RGIHP = null;

			return (void alter *)&nr->_hoops_SISI;
		}	_hoops_HHHI;

		case _hoops_HAGCH: {
			int	index = _hoops_ISPI;
			Text_Info alter *		ti = (Text_Info alter *)pointer;

			if (index < 0)
				index = 0;
			else
				if (index >= ti->_hoops_SIHSA.length)
					index = ti->_hoops_SIHSA.length - 1;

			return (void alter *)HD_Compute_Character_Position(nr, ti, index);

		} _hoops_HHHI;

		case _hoops_CAGCH: {
			int	index = _hoops_ISPI;
			Text_Info alter *		ti = (Text_Info alter *)pointer;

			if (index < 0)
				index = 0;
			else
				if (index >= ti->_hoops_SIHSA.length)
					index = ti->_hoops_SIHSA.length - 1;

			ti->_hoops_AGRI.x = HD_Compute_Character_Width(nr, ti, index);

			return (void alter *)&ti->_hoops_AGRI.x;

		}	_hoops_HHHI;

		case _hoops_IAGCH: {
			Text_Info alter *		ti = (Text_Info alter *)pointer;
			Point p;
			p.x = f1; p.y = f2; p.z = _hoops_CGHGR;
			return (void alter *)HD_Compute_Transformed_Text_Position (nr, ti, &p);
		}	_hoops_HHHI;

		case _hoops_GPGCH: {
			draw_3d_geometry (nr, request, pointer, _hoops_ISPI);
		}	break;

		case _hoops_RPGCH: {
			Segment_Info const *		si = (Segment_Info const *)pointer;
			Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

			HD_Selection_Walk_Tree (nr, si->segment, si->path);

			dc->flags |= _hoops_HHICP;
		}	break;

		case _hoops_APGCH: {
			select_geometry (nr, request, pointer, _hoops_ISPI);
		}	break;

		case _hoops_PPGCH: {
			Point alter				scale,
										translate;
			/* _hoops_CAHA _hoops_CAS _hoops_RH _hoops_AHCR=0 _hoops_IPPA _hoops_HRGR _hoops_GGR _hoops_SHPR _hoops_CPHH - "_hoops_PHCH._hoops_SSH" */

			HD_Compute_Screen_Transform (nr, &scale, &translate);

			HD_Elaborate_Selection (nr, (Geometry alter *)pointer,
									((Geometry alter *)pointer)->key, _hoops_AIRIR(pointer),
									-1, -1, -1,
									translate.z, MAX_FLOAT, T_WINDOWS, null);
		}	break;


		case _hoops_HPGCH: {
			_hoops_IGPPI (nr, _hoops_ISPI, _hoops_CSPI, _hoops_SSPI, f1, f2);
		}	break;

		case _hoops_IPGCH: {
			Marker alter *			marker;
			Point const *			where = (Point const *)pointer;

			ZALLOC (marker, Marker);
			_hoops_CSAPI (marker, _hoops_PCIP);

			marker->_hoops_CSAI.x = where->x;
			marker->_hoops_CSAI.y = where->y;
			marker->_hoops_CSAI.z = where->z;

			return (void alter *)marker;
		}	_hoops_HHHI;

		case _hoops_CPGCH: {
			Polyline alter *			polyline;

			ZALLOC (polyline, Polyline);
			_hoops_CSAPI (polyline, _hoops_IIIP);

			polyline->count = polyline->allocated = _hoops_ISPI;
			polyline->points = (Point alter *)HI_Clone_Anything (pointer,
												  _hoops_ISPI * (long)sizeof (Point));

			return (void alter *)polyline;
		}	_hoops_HHHI;

		case _hoops_SPGCH: {
			Polygon alter *		polygon;

			ZALLOC (polygon, Polygon);
			_hoops_CSAPI (polygon, _hoops_RCIP);

			polygon->count = polygon->allocated = _hoops_ISPI;
			polygon->points = (Point alter *)HI_Clone_Anything (pointer,
												 _hoops_ISPI * (long)sizeof (Point));

			return (void alter *)polygon;
		}	_hoops_HHHI;

		case _hoops_RHGCH: {
			Geometry alter *		geo = (Geometry alter *)pointer;

			if (geo == null)
				return null;

			if (geo->type < _hoops_AHRIR ||
				geo->type > _hoops_PHRIR ||
				BIT (geo->_hoops_RRHH, _hoops_HGAGR)) {
				HE_WARNING (HEC_GEOMETRY, HES_INVALID_ADDRESS_POINTER,
						"Pointer does not seem to refer to geometry");
			}
			else if (geo->owner != null ||
					 geo->backlink != null ||
					 geo->next != null) {
				/* _hoops_SRSH _hoops_ARRPA _hoops_ISPR */
				HE_ERROR (HEC_GEOMETRY, HES_GEOMETRY_NOT_CREATED_BY_IM,
						"Specified geometry does not seem to be created by I.M.");
			}
			else
				_hoops_HPRH (geo);

			return null;
		}	_hoops_HHHI;


		case _hoops_AHGCH: {
			Tristrip alter *		tristrip;
			Tristrip alter *		_hoops_SAPPI;

			ZALLOC (tristrip, Tristrip);
			_hoops_ICAI (tristrip);
			tristrip->_hoops_SRHA |= (DL_TEMPORARY_DATA | _hoops_SRHH);

			if ((_hoops_SAPPI = (Tristrip alter *)pointer) != null) {
				tristrip->points = _hoops_SAPPI->points;
				tristrip->_hoops_PHHA = _hoops_SAPPI->_hoops_PHHA;
				tristrip->total = _hoops_SAPPI->total;

				_hoops_APRGA(_hoops_SAPPI->lengths, _hoops_SAPPI->_hoops_PHHA, int, tristrip->lengths);
				tristrip->lengths_allocated = _hoops_SAPPI->_hoops_PHHA;

				_hoops_APRGA(_hoops_SAPPI->_hoops_AIHA, _hoops_SAPPI->total, int, tristrip->_hoops_AIHA);
				tristrip->_hoops_IPII = _hoops_SAPPI->total;

				if (_hoops_SAPPI->face_indices != null) {
					_hoops_APRGA(_hoops_SAPPI->face_indices, _hoops_SAPPI->total, int, tristrip->face_indices);
					tristrip->_hoops_SGAHR = _hoops_SAPPI->total;
				}
				else {
					tristrip->face_indices = null;
					tristrip->_hoops_SGAHR = 0;
				}

				tristrip->_hoops_RAHH |= _hoops_AAHH;

				tristrip->point_count = _hoops_SAPPI->point_count;
				tristrip->face_count = _hoops_SAPPI->face_count;

				tristrip->_hoops_PAGI = _hoops_SAPPI->_hoops_PAGI;
				tristrip->_hoops_PRHH = _hoops_SAPPI->_hoops_PRHH;

				tristrip->_hoops_PCHA = _hoops_SAPPI->_hoops_PCHA;
				tristrip->_hoops_HCHA = _hoops_SAPPI->_hoops_HCHA;
				tristrip->_hoops_ICHA = _hoops_SAPPI->_hoops_ICHA;

				if ((tristrip->_hoops_GSSH = _hoops_SAPPI->_hoops_GSSH) != null)
					_hoops_CAHS (tristrip->_hoops_GSSH);

				tristrip->_hoops_RPRCP = _hoops_SAPPI->_hoops_RPRCP;
				tristrip->_hoops_GPPPI = _hoops_SAPPI->_hoops_GPPPI;
				tristrip->_hoops_SRHA |= _hoops_SRHH;
				tristrip->_hoops_GSCP = _hoops_SAPPI->_hoops_GSCP;
			}

			return (void alter *)tristrip;
		}	_hoops_HHHI;


		case _hoops_PHGCH: {
			Tristrip *			ts = (Tristrip *)pointer;

			if (_hoops_ISAI (ts) == 0)
				HI_Free_Tristrip (ts);
		}	break;


		case _hoops_HHGCH: {
			Polyedge alter *		polyedge;
			Polyedge alter *		_hoops_SAPPI;


			ZALLOC (polyedge, Polyedge);
			_hoops_ICAI (polyedge);

			if ((_hoops_SAPPI = (Polyedge alter *)pointer) != null) {
				polyedge->points = _hoops_SAPPI->points;
				polyedge->_hoops_PHHA = _hoops_SAPPI->_hoops_PHHA;
				polyedge->total = _hoops_SAPPI->total;

				_hoops_APRGA(_hoops_SAPPI->lengths, _hoops_SAPPI->_hoops_PHHA, int, polyedge->lengths);
				polyedge->lengths_allocated = _hoops_SAPPI->_hoops_PHHA;

				_hoops_APRGA(_hoops_SAPPI->_hoops_AIHA, _hoops_SAPPI->total, int, polyedge->_hoops_AIHA);
				polyedge->_hoops_IPII = _hoops_SAPPI->total;

				if (_hoops_SAPPI->_hoops_SPII != null) {
					_hoops_APRGA(_hoops_SAPPI->_hoops_SPII, _hoops_SAPPI->total, int, polyedge->_hoops_SPII);
					polyedge->_hoops_CPII = _hoops_SAPPI->total;
				}

				polyedge->_hoops_RAHH |= _hoops_AAHH;

				polyedge->point_count = _hoops_SAPPI->point_count;
				polyedge->_hoops_SPHA = _hoops_SAPPI->_hoops_SPHA;

				polyedge->_hoops_ASHA = _hoops_SAPPI->_hoops_ASHA;
				polyedge->_hoops_RSHA = _hoops_SAPPI->_hoops_RSHA;

				polyedge->_hoops_PCHA = _hoops_SAPPI->_hoops_PCHA;
				polyedge->_hoops_HCHA = _hoops_SAPPI->_hoops_HCHA;
				polyedge->_hoops_ICHA = _hoops_SAPPI->_hoops_ICHA;
				polyedge->_hoops_CCHA = _hoops_SAPPI->_hoops_CCHA;
				polyedge->_hoops_GSHA = _hoops_SAPPI->_hoops_GSHA;
				polyedge->_hoops_SCAI = _hoops_SAPPI->_hoops_SCAI;

				polyedge->_hoops_RPRCP = _hoops_SAPPI->_hoops_RPRCP;
				polyedge->_hoops_GPPPI = _hoops_SAPPI->_hoops_GPPPI;
				polyedge->bounding = _hoops_SAPPI->bounding;
			}
			return (void alter *)polyedge;
		}	_hoops_HHHI;

		case _hoops_IHGCH: {
			Polyedge alter *		polyedge = (Polyedge *)pointer;

			if (_hoops_ISAI (polyedge) == 0)
				HI_Free_Polyedge (polyedge);
		}	break;


		case _hoops_CHGCH: {
			Polymarker alter *	_hoops_RGRHR;
			Polymarker alter *	_hoops_SAPPI;

			ZALLOC (_hoops_RGRHR, Polymarker);

			if ((_hoops_SAPPI = (Polymarker alter *)pointer) != null) {
				_hoops_RGRHR->points = _hoops_SAPPI->points;
				_hoops_RGRHR->length = _hoops_SAPPI->length;

				if (_hoops_SAPPI->_hoops_AIHA != null) {
					_hoops_APRGA(_hoops_SAPPI->_hoops_AIHA, _hoops_SAPPI->length, int, _hoops_RGRHR->_hoops_AIHA);
					_hoops_RGRHR->_hoops_IPII = _hoops_SAPPI->length;
					_hoops_RGRHR->_hoops_RAHH |= _hoops_AAHH;
				}

				_hoops_RGRHR->point_count = _hoops_SAPPI->point_count;

				_hoops_RGRHR->_hoops_PCHA = _hoops_SAPPI->_hoops_PCHA;
				_hoops_RGRHR->_hoops_HCHA = _hoops_SAPPI->_hoops_HCHA;
				_hoops_RGRHR->_hoops_ICHA = _hoops_SAPPI->_hoops_ICHA;
				_hoops_RGRHR->_hoops_CCHA = _hoops_SAPPI->_hoops_CCHA;
				_hoops_RGRHR->_hoops_GSHA = _hoops_SAPPI->_hoops_GSHA;

				_hoops_RGRHR->_hoops_RPRCP = _hoops_SAPPI->_hoops_RPRCP;
				_hoops_RGRHR->_hoops_GPPPI = _hoops_SAPPI->_hoops_GPPPI;
			}

			return (void alter *)_hoops_RGRHR;
		}	_hoops_HHHI;

		case _hoops_SHGCH: {
			Polymarker alter *	_hoops_RGRHR = (Polymarker *)pointer;

			HI_Free_Polymarker(_hoops_RGRHR);
		}	break;


		case _hoops_GIGCH: {
			_hoops_PCCCA	data;

			ZERO_STRUCT(&data, _hoops_PCCCA);
			data.database.set = _hoops_GGCCA;
			data.area.left	 = -1.0f;	data.area.right = 1.0f;
			data.area.bottom = -1.0f;	data.area.top	= 1.0f;

			_hoops_AIGPR *	_hoops_RIGC = nr->_hoops_SRA->_hoops_RIGC;
			HI_Set_And_Clear_Flags (_hoops_RIGC, (_hoops_CRCP alter *)pointer, (void *)&data);

		}	break;

		case _hoops_RIGCH: {
			_hoops_PCCCA	data;

			ZERO_STRUCT(&data, _hoops_PCCCA);
			data.database.clear = _hoops_GGCCA;
			data.area.left	 = -1.0f;	data.area.right = 1.0f;
			data.area.bottom = -1.0f;	data.area.top	= 1.0f;

			_hoops_AIGPR *	_hoops_RIGC = nr->_hoops_SRA->_hoops_RIGC;
			HI_Set_And_Clear_Flags (_hoops_RIGC, (_hoops_CRCP alter *)pointer, (void *)&data);

		}	break;

		case _hoops_SAGCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = nr->_hoops_SISI;

			if (_hoops_HRCIR->_hoops_CRRIP) {
				if (_hoops_HRCIR->path.x != 0.0f || _hoops_HRCIR->path.y != 0.0f)
					_hoops_HRCIR->rotation = _hoops_AGGGA (_hoops_HRCIR->path.y, _hoops_HRCIR->path.x);
			}

		}	break;

		case _hoops_AIGCH: {
			_hoops_GGPPI (nr, pointer, _hoops_ISPI, _hoops_CSPI, (Image_Format)_hoops_SSPI, _hoops_SGHI, f1, f2, _hoops_CGHGR);
		}	break;

		case _hoops_PIGCH: {
			_hoops_GPRH(_hoops_RSRGH)++;
			HD_Interrupt_Update(nr->_hoops_SRA, true, false);
			_hoops_APSRR(nr->_hoops_SRA, "IM_Abort_Update","", 0);
		}	break;

		case _hoops_HIGCH: {
			_hoops_SIHHP alter *	up;
			int								height = _hoops_ISPI,
											width = _hoops_CSPI;

			if (width <= 0 || height == 0) {
				HE_ERROR (HEC_FACE, HES_INVALID_FILL_PATTERN_SIZE,
						  "User-defined fill pattern size is unreasonable");
				return null;
			}

			ZALLOC (up, _hoops_SIHHP);
			_hoops_ICAI (up);
			up->_hoops_CPA = nr->_hoops_SRA->_hoops_GCHHP();
			up->width = width;
			up->height = height;
			up->_hoops_RCHHP = true;
			up->_hoops_ACHHP = _hoops_SSPI;
			if (up->height < 0) {
				up->height = -up->height;
				up->_hoops_RCHHP = false;
			}
			up->pattern = (unsigned char const *)
								HI_Clone_Anything (pointer,
												   up->width * up->height);
			up->stipple = false;
			return (void alter *)up;
		}	_hoops_HHHI;

		case _hoops_IIGCH: {
			if (pointer != null)
				HD_Free_User_Face_Pattern((_hoops_SIHHP const *)pointer);
		}	break;

		case _hoops_CIGCH: {
			_hoops_SRPPI (nr);
		}	break;


		case _hoops_SIGCH: {
			Line_Style *	_hoops_ACCI;
			ZALLOC (_hoops_ACCI, Line_Style);
			*_hoops_ACCI = HD_Define_Line_Style_Legacy(nr, pointer, _hoops_ISPI, _hoops_CSPI, false);
			return (void alter *)_hoops_ACCI;
		}	_hoops_HHHI;

		case _hoops_CCGCH: {
			Line_Style *	_hoops_ACCI;
			ZALLOC (_hoops_ACCI, Line_Style);
			*_hoops_ACCI = HD_Define_Line_Style_Legacy(nr, pointer, _hoops_ISPI, _hoops_CSPI, true);
			return (void alter *)_hoops_ACCI;
		}	_hoops_HHHI;

		case _hoops_GCGCH: {
			Line_Style *	_hoops_ACCI;
			if ((_hoops_ACCI = (Line_Style *)pointer) != null) {
				*_hoops_ACCI = null;
				FREE (_hoops_ACCI, Line_Style);
			}
		}	break;


		case _hoops_RCGCH: {
			return (void alter *) HD_New_Convex_Clip_Region(nr, (int)_hoops_ISPI, (DC_Point const *)pointer);
		}	_hoops_HHHI;

		case _hoops_ACGCH: {
			_hoops_ASHH *			victim = (_hoops_ASHH *)pointer;
			if (victim != null)
				HD_Free_Convex_Clip_Region(victim);
		}	break;

		case _hoops_SCGCH: {
			nr->transform_rendition.Modify();
			_hoops_HHCR alter &		_hoops_IHCR = nr->transform_rendition;
			_hoops_HRPA						_hoops_RHSPR;

			/* _hoops_PAISR/_hoops_PRHSA _hoops_HGRH _hoops_RCAGR _hoops_HII _hoops_RPPPI
			 * _hoops_HPIAA _hoops_APPPI _hoops_CGH _hoops_SHH _hoops_IHPR
			 */

			/* _hoops_IPCP _hoops_SSH-_hoops_SRHR _hoops_PIH _hoops_GSH _hoops_RH _hoops_PPPPI _hoops_SHPR _hoops_HIHP, _hoops_HIS _hoops_AHCR
			 * _hoops_SHPH _hoops_HGAP _hoops_PCCP _hoops_PAISR-_hoops_PRHSA _hoops_IIGR _hoops_PCCP _hoops_AIAH-_hoops_SGGA _hoops_SHPR _hoops_HPPPI.
			 */

			HD_Undo_Screen (nr, &_hoops_RHSPR);

			_hoops_IHCR->_hoops_GSCH[0] = f1;
			_hoops_IHCR->_hoops_GSCH[1] = f2;

			/* _hoops_CISRP _hoops_HCPC _hoops_IS _hoops_GHAR _hoops_CCIR */
			if (_hoops_IHCR->_hoops_GSCH[0] < 0.0f)
				_hoops_IHCR->_hoops_GSCH[0] = 0.0f;
			else if (_hoops_IHCR->_hoops_GSCH[0] > 1.0f)
				_hoops_IHCR->_hoops_GSCH[0] = 1.0f;

			if (_hoops_IHCR->_hoops_GSCH[1] < 0.0f)
				_hoops_IHCR->_hoops_GSCH[1] = 0.0f;
			else if (_hoops_IHCR->_hoops_GSCH[1] > 1.0f)
				_hoops_IHCR->_hoops_GSCH[1] = 1.0f;

			HD_Redo_Screen (nr, &_hoops_RHSPR);

			if (BIT (_hoops_IHCR->flags, _hoops_HHGGA))
				HD_Set_DC_Cutting_Planes (nr);

			return null;
		}	_hoops_HHHI;

		case _hoops_GSGCH:
		case _hoops_RSGCH: {
			_hoops_GASC	glyph;

			if (request == _hoops_GSGCH)
				glyph = HD_Find_Glyph_Legacy(nr, (char)_hoops_ISPI);
			else
				glyph = HD_Find_Glyph(nr->glyph_rendition, (const char *)pointer, 0, 0, false);

			if (glyph)
				nr->_hoops_GSP.Modify()->glyph = glyph;

			return null;
		} _hoops_HHHI;

		case _hoops_ASGCH:
		case _hoops_PSGCH: {
			_hoops_GASC	glyph;

			if (request == _hoops_ASGCH)
				glyph = HD_Find_Glyph_Legacy(nr, (char)_hoops_ISPI);
			else
				glyph = HD_Find_Glyph(nr->glyph_rendition, (const char *)pointer, 0, 0, false);

			if (glyph)
				nr->_hoops_SCP.Modify()->glyph = glyph;

			return null;
		} _hoops_HHHI;


		case _hoops_HSGCH:
		case _hoops_ISGCH: {
			Line_Style						_hoops_ACCI;
			Integer32						_hoops_ACSAP = LCAP_BUTT | LJOIN_MITER | LPAT_BUTT;

			if (request == _hoops_HSGCH)
				_hoops_ACCI = HD_Find_Line_Style_Legacy(nr, (char)_hoops_ISPI);
			else {
				_hoops_ACCI = HD_Find_Line_Style(nr, (const char *)pointer);
				HI_Canonize_Line_Pattern((const char *)pointer, 0, &_hoops_ACSAP);
			}

			if (_hoops_ACCI) {
				Line_Rendition alter &	_hoops_HC = nr->_hoops_AHP.Modify();
				_hoops_HC->style = _hoops_ACSAP;
				_hoops_HC->line_style = _hoops_ACCI;
			}

			return null;
		} _hoops_HHHI;

		case _hoops_AGRCH:
		case _hoops_PGRCH: {
			Line_Style						_hoops_ACCI;
			Integer32						_hoops_ACSAP = LCAP_BUTT | LJOIN_MITER | LPAT_BUTT;

			if (request == _hoops_AGRCH)
				_hoops_ACCI = HD_Find_Line_Style_Legacy(nr, (char)_hoops_ISPI);
			else {
				_hoops_ACCI = HD_Find_Line_Style(nr, (const char *)pointer);
				HI_Canonize_Line_Pattern((const char *)pointer, 0, &_hoops_ACSAP);
			}

			if (_hoops_ACCI) {
				Line_Rendition alter &	_hoops_HC = nr->_hoops_RHP.Modify();
				_hoops_HC->style = _hoops_ACSAP;
				_hoops_HC->line_style = _hoops_ACCI;
			}

			return null;
		} _hoops_HHHI;

		case _hoops_CSGCH: {
			_hoops_CRCP const *			node = nr->_hoops_SRA->_hoops_RRCIP;
			_hoops_HICS const &	path = nr->_hoops_SRA->path;
			int						_hoops_IPPPI = 0;
			_hoops_PGRPR const *			include = null;
			_hoops_PGRPR const **		_hoops_PGCGP = null;
			HIC_Segment_Path *		sp;
			Key *					keys;
			int						allocated = 16;
			int						count = 0;

			if (path != null) {
				_hoops_PGCGP = path->_hoops_PGCGP;
				include = *_hoops_PGCGP++;
				_hoops_IPPPI = path->count - 1;
			}

			ALLOC_ARRAY (keys, allocated, Key);

			while (node != null && node->type != _hoops_PRAIR) {
				if (count == allocated) {
					Key *		old_keys = keys;

					allocated *= 2;
					ALLOC_ARRAY (keys, allocated, Key);
					_hoops_AIGA (old_keys, count, Key, keys);
					FREE_ARRAY (old_keys, count, Key);
				}

				// _hoops_PAGA: _hoops_RGR _hoops_GRS _hoops_HGCR _hoops_RH _hoops_SIC _hoops_IH _hoops_PCCP _hoops_GCIS _hoops_GAR _hoops_SCH _hoops_RGAR _hoops_SPCP _hoops_CPPPI
				// _hoops_HIH _hoops_PSSSR _hoops_IH _hoops_GRH "_hoops_GCIS" _hoops_PGAP _hoops_SPPPI _hoops_IRS _hoops_RSPHR _hoops_HHIS
				if (node->type != _hoops_PIRIR)
					keys[count++] = node->key;

				if (include != null && node == include->_hoops_IGRPR) {
					node = (_hoops_CRCP *)include;
					if (_hoops_IPPPI > 0) {
						include = *_hoops_PGCGP++;
						--_hoops_IPPPI;
					}
					else
						include = null;
				}
				else
					node = node->owner;
			}

			if (count != allocated) {
				Key *		old_keys = keys;

				ALLOC_ARRAY (keys, count, Key);
				_hoops_AIGA (old_keys, count, Key, keys);
				FREE_ARRAY (old_keys, allocated, Key);
			}

			ZALLOC (sp, HIC_Segment_Path);
			sp->keys = keys;
			sp->count = count;

			return sp;
		} _hoops_HHHI;

		case _hoops_SSGCH: {
			HIC_Segment_Path *		sp = (HIC_Segment_Path *)pointer;
			FREE_ARRAY (sp->keys, sp->count, Key);
			FREE (sp, HIC_Segment_Path);
			return null;
		} _hoops_HHHI;


		case _hoops_GGRCH: {
			Text_Info const *	ti = (Text_Info *)pointer;
			return HI_Clone_Text_Info(ti);
		} _hoops_HHHI;


		case _hoops_RGRCH: {
			Text_Info alter *	ti = (Text_Info *)pointer;
			HI_Free_Text_Info(ti);
			return null;
		} _hoops_HHHI;

		case _hoops_GRRCH: {
			_hoops_RAARP		stencil;

			ZERO_STRUCT (&stencil, _hoops_RAARP);
			stencil.width = _hoops_ISPI;
			stencil.height = _hoops_CSPI;
			stencil._hoops_APARP = _hoops_SSPI;
			stencil._hoops_PPARP = _hoops_SGHI;
			stencil.bitmap = (unsigned char *)pointer;

			return HI_Clone_Stencil (&stencil);
		} _hoops_HHHI;

		case _hoops_RRRCH: {
			HI_Cleanup_Stencil((_hoops_RAARP *)pointer, true);
			return null;
		} _hoops_HHHI;

		case _hoops_PRRCH: {
			return (void *)(POINTER_SIZED_INT)HD_Exit_Update (nr->_hoops_SRA);
		} _hoops_HHHI;

		case _hoops_HRRCH: {
			HD_Draw_Window(nr, (Int_Rectangle const *)pointer);
		} break;

		case _hoops_IRRCH: {
			_hoops_ICHIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_CRRCH: {
			_hoops_RPIIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_SRRCH: {
			_hoops_CCHIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_GARCH: {
			_hoops_APIIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_RARCH: {
			_hoops_RGIIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_AARCH: {
			_hoops_SCHIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_PARCH: {
			_hoops_HHCGH(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_HARCH: {
			_hoops_GRIIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_IARCH: {
			_hoops_RRIIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_CARCH: {
			_hoops_CGIIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_SARCH: {
			_hoops_IGIIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_GPRCH: {
			_hoops_GSHIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_RPRCH: {
			_hoops_PPIIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_APRCH: {
			_hoops_ARIIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_PPRCH: {
			_hoops_HPIIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_HPRCH: {
			_hoops_RSHIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_IPRCH: {
			_hoops_IPIIP(nr, (RGB const *)pointer, true);
		} break;

		case _hoops_CPRCH: {
			if (nr->_hoops_SRA->_hoops_APHHP != null) {
				Net_Rendition		_hoops_CRAI = nr;
				_hoops_CRAI->_hoops_SRA->_hoops_APHHP->_hoops_GHPPI = true;
			}
		} break;

		case _hoops_SPRCH: {
			_hoops_GACIP (nr, _hoops_CAAGR)(nr,
				nr->transform_rendition->_hoops_AGAA.left,
				nr->transform_rendition->_hoops_AGAA.right,
				nr->transform_rendition->_hoops_AGAA.bottom,
				nr->transform_rendition->_hoops_AGAA.top);
		} break;

		case _hoops_GHRCH: {
			return (void *)((nr->_hoops_SRA->_hoops_ACPGR->_hoops_GRSSP) ? true : false);
		} break;

		case _hoops_RHRCH: {
			return (void *)(nr->_hoops_SRA->_hoops_AAHSR->key);
		} break;

		case _hoops_AHRCH: {
			return (void *)(_hoops_AIRIR (nr->_hoops_SRA->_hoops_AAHSR));
		} break;

		case _hoops_PHRCH: {
			return (void *)(nr->_hoops_SRA->_hoops_PGCC._hoops_ICHSR);
		} break;

		case _hoops_HHRCH: {
			return (void *)(nr->_hoops_SRA->_hoops_PGCC.driver_type);
		} break;

		case _hoops_IHRCH: {
			return (void *)(BIT(nr->_hoops_SRA->_hoops_PGCC.flags, _hoops_HSHSR));
		} break;

		case _hoops_CHRCH: {
			return (void *)(BIT(nr->_hoops_SRA->_hoops_PGCC.flags, _hoops_RSHSR));
		} break;

		case _hoops_SHRCH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SRA->_hoops_PGCC._hoops_ASHSR);
		} break;

		case _hoops_GIRCH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SRA->_hoops_PGCC._hoops_RCPGH);
		} break;

		case _hoops_RIRCH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SRA->_hoops_PGCC._hoops_AAPSR);
		} break;

		case _hoops_AIRCH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SRA->_hoops_PGCC._hoops_HHPGH);
		} break;

		case _hoops_PIRCH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SRA->current._hoops_PRPSR.x);
		} break;

		case _hoops_HIRCH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SRA->current._hoops_PRPSR.y);
		} break;

		case _hoops_IIRCH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SRA->_hoops_PGCC._hoops_PRPSR.x);
		} break;

		case _hoops_CIRCH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SRA->_hoops_PGCC._hoops_PRPSR.y);
		} break;

		case _hoops_SIRCH: {
			return (void *)nr->_hoops_SRA->current._hoops_RAPGH;
		} break;

		case _hoops_GCRCH: {
			return (void *)nr->_hoops_SRA->current._hoops_PAPGH;
		} break;

		case _hoops_RCRCH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_SRA->current._hoops_HAPGH;
		} break;

		case _hoops_ACRCH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_SRA->_hoops_PGCC._hoops_HASHP;
		} break;

		case _hoops_PCRCH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_SRA->_hoops_PGCC._hoops_HGCC;
		} break;

		case _hoops_HCRCH: {
			return (void *)(BIT(nr->_hoops_SRA->_hoops_PGCC.flags, _hoops_SGICP));
		} break;

		case _hoops_ICRCH: {
			return (void *)(BIT(nr->_hoops_SRA->_hoops_PGCC.flags, _hoops_RPPGH));
		} break;

		case _hoops_CCRCH: {
			return (void *)(POINTER_SIZED_INT)HD_Find_Line_Style_Legacy_P(nr->_hoops_AHP->line_style);
		} break;

		case _hoops_SCRCH: {
			return (void *)nr->_hoops_AHP->line_style->name.text;
		} break;

		case _hoops_GSRCH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_AHP->weight);
		} break;

		case _hoops_RSRCH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_AHP->color;
		} break;

		case _hoops_ASRCH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_AHP->contrast_color;
		} break;

		case _hoops_PSRCH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_RHP->color;
		} break;

		case _hoops_HSRCH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_RHP->contrast_color;
		} break;

		case _hoops_ISRCH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_IHA->color;
		} break;

		case _hoops_CSRCH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_IHA->contrast_color;
		} break;

		case _hoops_SSRCH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_IHA->_hoops_RGIR;
		} break;

		case _hoops_GGACH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_GSP->color;
		} break;

		case _hoops_RGACH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_GSP->contrast_color;
		} break;

		case _hoops_AGACH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_SCP->color;
		} break;

		case _hoops_PGACH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_SCP->contrast_color;
		} break;

		case _hoops_HGACH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_SISI->color;
		} break;

		case _hoops_IGACH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_SAIR->_hoops_GPIR;
		} break;

		case _hoops_CGACH: {
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&nr->_hoops_SAIR->contrast_color;
		} break;

		case _hoops_SGACH: {
			int include = 0;
			if (!BIT (nr->_hoops_RGP, T_FACES))
				include = 2;//_hoops_RHPPI
			else if (!ANYBIT (nr->_hoops_RGP, T_ANY_POLYGON_EDGE))
				include = 1;//_hoops_AHPPI
			else
				include = 3;//_hoops_PHPPI
			return (void *)(POINTER_SIZED_INT)include;
		} break;
		case _hoops_GRACH: {
			return (void *)(POINTER_SIZED_INT)HD_Find_Line_Style_Legacy_P(nr->_hoops_RHP->line_style);
		} break;
		case _hoops_RRACH: {
			return (void *)nr->_hoops_RHP->line_style->name.text;
		} break;
		case _hoops_ARACH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_RHP->weight);
		} break;
		case _hoops_PRACH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_IHA->pattern);
		} break;

		case _hoops_AGCCH: {
			return (void *)&nr->_hoops_IHA->_hoops_CHA->_hoops_CSHR;
		} break;

		case _hoops_HACCH: {
			RGBAS32	c;
			c.r = (unsigned char)_hoops_ISPI;
			c.g = (unsigned char)_hoops_CSPI;
			c.b = (unsigned char)_hoops_SSPI;
			c.a = (unsigned char)_hoops_SGHI;
			return (void *)(POINTER_SIZED_INT)*(Integer32 const *)&c;
		} break;

		case _hoops_HRACH: {
			return (void *)(POINTER_SIZED_INT)HD_Find_Glyph_Legacy_Symbol(nr->_hoops_GSP->glyph);
		} break;
		case _hoops_IRACH: {
			return (void *)nr->_hoops_GSP->glyph->name.text;
		} break;


		case _hoops_CRACH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SISI->_hoops_PRRIP);
		} break;
		case _hoops_SRACH: {
			return (void *)(&nr->_hoops_SISI->path);
		} break;
		case _hoops_GAACH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_SISI->_hoops_GHGRP;
		} break;
		case _hoops_RAACH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_SISI->_hoops_SSPAP;
		} break;
		case _hoops_AAACH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_SISI->_hoops_GGHAP;
		} break;

		case _hoops_PAACH: {
			if (nr->_hoops_SISI->font == null ||
				!nr->_hoops_SISI->font->_hoops_CGCSR)
				return 0;

			return nr->_hoops_SISI->font->_hoops_GAASR;
		} break;

		case _hoops_HAACH: {
			if (nr->_hoops_SISI->font == null)
				return 0;
			if (nr->_hoops_SISI->font->name.length != 0)
				return (void *)nr->_hoops_SISI->font->name.text;
			return nr->_hoops_SISI->font->family->name.text;
		} break;

		case _hoops_IAACH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SISI->transform);
		} break;

		case _hoops_CAACH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SISI->_hoops_GRCSR);
		} break;

		case _hoops_SAACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(POINTER_SIZED_INT)(ti->_hoops_PPPSP);
		} break;

		case _hoops_GPACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(POINTER_SIZED_INT)(ti->_hoops_HGCSR);
		} break;

		case _hoops_RPACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(&ti->_hoops_HGCSR[_hoops_ISPI]);
		} break;

		case _hoops_APACH: {
			_hoops_PGCSR const * ki = (_hoops_PGCSR const *)pointer;
			return (void *)(&ki->position);
		} break;

		case _hoops_PPACH: {
			_hoops_PGCSR const * ki = (_hoops_PGCSR const *)pointer;
			return (void *)(&ki->point);
		} break;

		case _hoops_HPACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(ti->_hoops_SIHSA._hoops_IPPPP);
		} break;

		case _hoops_IPACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(POINTER_SIZED_INT)(ti->_hoops_SIHSA.length);
		} break;
		case _hoops_CPACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(POINTER_SIZED_INT)(ti->text->encoding);
		} break;
		case _hoops_SPACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(POINTER_SIZED_INT)(ti->text->_hoops_PICHR);
		} break;
		case _hoops_GHACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(POINTER_SIZED_INT)(ti->line_index);
		} break;
		case _hoops_RHACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(ti->text->_hoops_ICI);
		} break;
		case _hoops_AHACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(&ti->position);
		} break;
		case _hoops_PHACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(&ti->_hoops_CSAGR);
		} break;
		case _hoops_HHACH: {
			_hoops_HACC const * t = (_hoops_HACC const *)pointer;
			return (void *)(&t->_hoops_CSAI);
		} break;
		case _hoops_IHACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(&ti->_hoops_HHPSP);
		} break;
		case _hoops_CHACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(&ti->_hoops_IHPSP);
		} break;
		case _hoops_SHACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(&ti->_hoops_GHPSP);
		} break;
		case _hoops_GIACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(&ti->_hoops_CHPSP);
		} break;
		case _hoops_RIACH: {
			Text_Info const * ti = (Text_Info const *)pointer;
			return (void *)(&ti->_hoops_PHPSP);
		} break;

		case _hoops_AIACH: {
			return (void *)(&nr->transform_rendition->_hoops_SPH->position);
		} break;
		case _hoops_PIACH: {
			return (void *)(&nr->transform_rendition->_hoops_SPH->target);
		} break;
		case _hoops_HIACH: {
			return (void *)(&nr->transform_rendition->_hoops_SPH->up_vector);
		} break;
		case _hoops_IIACH: {
			return (void *)(POINTER_SIZED_INT)(nr->transform_rendition->_hoops_SPH->projection);
		} break;


		case _hoops_CIACH: {
			return (void *)(POINTER_SIZED_INT)(BIT(nr->transform_rendition->flags, _hoops_PASP));
		} break;
		case _hoops_SIACH: {
			return (void *)(&nr->_hoops_SAIR->_hoops_PHRA);
		} break;
		case _hoops_GCACH: {
			return (void *)(&nr->transform_rendition->_hoops_AGAA.left);	/* _hoops_RHRIR, _hoops_CPSA _hoops_IRS _hoops_HHPPI _hoops_CCA _hoops_IRS '_hoops_SPS' _hoops_PAIP */
		} break;
		case _hoops_SGCCH: {
			return (void *)(&nr->_hoops_SAIR->_hoops_SCIH);
		} break;
		case _hoops_RCACH: {
			return (void *)(POINTER_SIZED_INT)(BIT (nr->transform_rendition->heuristics, _hoops_IRI)?true:false);
		} break;
		case _hoops_ACACH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_RGP;
		} break;


		case _hoops_PCACH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SAIR->_hoops_CGAIP);
		} break;


		case _hoops_GSACH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SRA->_hoops_CPIGA);
		} break;


		case _hoops_RSACH: {
			return (void *)nr->_hoops_SRA->_hoops_AIACR;
		} break;

		case _hoops_ASACH: {
			Line_Rendition alter &	_hoops_HC = *(Line_Rendition alter *)
					HIC_Intermediate_Utility (inr, _hoops_HRGCH, _hoops_ISAPI);

			_hoops_HC->weight = _hoops_ISPI;
		} break;

		case _hoops_PSACH: {
			Line_Rendition alter &	_hoops_HC = *(Line_Rendition alter *)
					HIC_Intermediate_Utility (inr, _hoops_HRGCH, _hoops_ISAPI);

			_hoops_HC->_hoops_HHP = _hoops_ISPI;
			_hoops_HC->_hoops_PHP = f1;

			if (_hoops_HC->_hoops_HHP == _hoops_SHGRP) {
				Display_Context alter *	dc = (Display_Context alter *)nr->_hoops_SRA;
				_hoops_HC->weight = (int)(_hoops_HC->_hoops_PHP * dc->_hoops_PGCC._hoops_IHHSR);
			}
			else if (_hoops_HC->_hoops_HHP == GSU_PIXELS)
				_hoops_HC->weight = (int)(_hoops_HC->_hoops_PHP + 0.5f);
			else
				_hoops_HC->weight = -1;

			if (_hoops_HC->weight != -1 && 
				(_hoops_HC->weight < 0 || _hoops_HC->weight > _hoops_CSGIP)) {
				_hoops_HC->weight = (float)_hoops_CSGIP;
			}

			/* _hoops_ASC _hoops_AIAH _hoops_IRAA _hoops_SISS _hoops_RAAA _hoops_CRGR _hoops_HIHA... */
			if (_hoops_HC->_hoops_HHP == GSU_ORU ||
				_hoops_HC->_hoops_HHP == _hoops_SPSC ||
				_hoops_HC->_hoops_HHP == GSU_POINTS ||
				_hoops_HC->_hoops_HHP == GSU_SRU ||
				_hoops_HC->_hoops_HHP == GSU_WRU)
				_hoops_HC->flags |= _hoops_SSGIP;

		} break;

		case _hoops_HSACH: {
			Line_Rendition alter &	_hoops_HC = *(Line_Rendition alter *)
					HIC_Intermediate_Utility (inr, _hoops_HRGCH, _hoops_ISAPI);

			if ((_hoops_HC->line_style = *(Line_Style *)pointer) == null)
				_hoops_HC->line_style = HD_Find_Line_Style(nr, "-");
		} break;

		case _hoops_ISACH: {
			Line_Rendition alter &	_hoops_HC = *(Line_Rendition alter *)
					HIC_Intermediate_Utility (inr, _hoops_HRGCH, _hoops_ISAPI);

			_hoops_HC->color = (RGBAS32 const &)_hoops_ISPI;
		} break;

		case _hoops_CSACH: {
			Line_Rendition alter &	_hoops_HC = *(Line_Rendition alter *)
					HIC_Intermediate_Utility (inr, _hoops_IRGCH, _hoops_ISAPI);

			_hoops_HC->weight = _hoops_ISPI;
		} break;

		case _hoops_SSACH: {
			Line_Rendition alter &	_hoops_HC = *(Line_Rendition alter *)
					HIC_Intermediate_Utility (inr, _hoops_IRGCH, _hoops_ISAPI);

			_hoops_HC->_hoops_HHP = _hoops_ISPI;
			_hoops_HC->_hoops_PHP = f1;

			if (_hoops_HC->_hoops_HHP == _hoops_SHGRP) {
				Display_Context alter *	dc = (Display_Context alter *)nr->_hoops_SRA;
				_hoops_HC->weight = (int)(_hoops_HC->_hoops_PHP * dc->_hoops_PGCC._hoops_IHHSR);
			}
			else if (_hoops_HC->_hoops_HHP == GSU_PIXELS)
				_hoops_HC->weight = (int)(_hoops_HC->_hoops_PHP + 0.5f);
			else
				_hoops_HC->weight = -1;

			if (_hoops_HC->weight != -1 && 
				(_hoops_HC->weight < 0 || _hoops_HC->weight > _hoops_CSGIP)) {
				_hoops_HC->weight = (float)_hoops_CSGIP;
			}


			/* _hoops_ASC _hoops_AIAH _hoops_IRAA _hoops_SISS _hoops_RAAA _hoops_CRGR _hoops_HIHA... */
			if (_hoops_HC->_hoops_HHP == GSU_ORU ||
				_hoops_HC->_hoops_HHP == _hoops_SPSC ||
				_hoops_HC->_hoops_HHP == GSU_POINTS ||
				_hoops_HC->_hoops_HHP == GSU_SRU ||
				_hoops_HC->_hoops_HHP == GSU_WRU)
				_hoops_HC->flags |= _hoops_SSGIP;

		} break;

		case _hoops_GGPCH: {
			Line_Rendition alter &	_hoops_HC = *(Line_Rendition alter *)
					HIC_Intermediate_Utility (inr, _hoops_IRGCH, _hoops_ISAPI);

			if ((_hoops_HC->line_style = *(Line_Style *)pointer) == null)
				_hoops_HC->line_style = HD_Find_Line_Style(nr, "-");
		} break;

		case _hoops_RGPCH: {
			Line_Rendition alter &	_hoops_HC = *(Line_Rendition alter *)
					HIC_Intermediate_Utility (inr, _hoops_IRGCH, _hoops_ISAPI);

			_hoops_HC->color = (RGBAS32 const &)_hoops_ISPI;
		} break;

		case _hoops_AGPCH: {
			_hoops_CIGA alter &	_hoops_SIGA = *(_hoops_CIGA alter *)
					HIC_Intermediate_Utility (inr, _hoops_CRGCH, _hoops_ISAPI);

			_hoops_SIGA->pattern = _hoops_ISPI;
		} break;

		case _hoops_PGPCH: {
			_hoops_CGRA alter &	_hoops_SGRA = *(_hoops_CGRA alter *)
					HIC_Intermediate_Utility (inr, _hoops_PAGCH, _hoops_ISAPI);

			_hoops_SGRA->_hoops_CGAIP = _hoops_ISPI;
		} break;

		case _hoops_HGPCH: {
			_hoops_CIGA alter &	_hoops_SIGA = *(_hoops_CIGA alter *)
					HIC_Intermediate_Utility (inr, _hoops_CRGCH, _hoops_ISAPI);

			HIC_Free_User_Face_Pattern ((HIC_User_Face_Pattern const *)_hoops_SIGA->_hoops_PGPH);
			if ((_hoops_SIGA->_hoops_PGPH = (_hoops_SIHHP const *)pointer) != null) {
				_hoops_CAHS (_hoops_SIGA->_hoops_PGPH);
				_hoops_SIGA->pattern = FP_USER_DEFINED;
			}
			else
				_hoops_SIGA->pattern = FP_SOLID;
		} break;

		case _hoops_IGPCH: {
			_hoops_CGRA alter &	_hoops_SGRA = *(_hoops_CGRA alter *)
					HIC_Intermediate_Utility (inr, _hoops_PAGCH, _hoops_ISAPI);

			HIC_Free_User_Face_Pattern ((HIC_User_Face_Pattern const *)_hoops_SGRA->_hoops_PGPH);
			if ((_hoops_SGRA->_hoops_PGPH = (_hoops_SIHHP const *)pointer) != null) {
				_hoops_CAHS (_hoops_SGRA->_hoops_PGPH);
				_hoops_SGRA->_hoops_CGAIP = FP_USER_DEFINED;
			}
			else
				_hoops_SGRA->_hoops_CGAIP = FP_SOLID;
		} break;

		case _hoops_CGPCH: {
			_hoops_CIGA alter &	_hoops_SIGA = *(_hoops_CIGA alter *)
					HIC_Intermediate_Utility (inr, _hoops_CRGCH, _hoops_ISAPI);

			_hoops_SIGA->color = (RGBAS32 const &)_hoops_ISPI;
		} break;

		case _hoops_SGPCH: {
			_hoops_CIGA alter &	_hoops_SIGA = *(_hoops_CIGA alter *)
					HIC_Intermediate_Utility (inr, _hoops_CRGCH, null, _hoops_RSAPI(1));

			_hoops_SIGA->_hoops_RGIR = (RGBAS32 const &)_hoops_ISPI;
		} break;

		case _hoops_GRPCH: {
			_hoops_CIGA alter &	_hoops_SIGA = *(_hoops_CIGA alter *)
					HIC_Intermediate_Utility (inr, _hoops_CRGCH, _hoops_ISAPI);

			_hoops_SIGA->contrast_color = (RGBAS32 const &)_hoops_ISPI;
		} break;

		case _hoops_RRPCH: {
			_hoops_CIGA alter &	_hoops_SIGA = *(_hoops_CIGA alter *)
					HIC_Intermediate_Utility (inr, _hoops_CRGCH, _hoops_ISAPI);

			_hoops_HHA alter &	mat = _hoops_SIGA->_hoops_CHA;
			RGB *						in = (RGB *)pointer;
			mat->_hoops_IRIR = 1.0f - 0.333f * (in->red + in->green + in->blue);
			mat->color[_hoops_PCA].red = in->red;
			mat->color[_hoops_PCA].green = in->green;
			mat->color[_hoops_PCA].blue = in->blue;
		} break;

		case _hoops_ARPCH: {
			_hoops_ICP alter &	_hoops_CCP = *(_hoops_ICP alter *)
					HIC_Intermediate_Utility (inr, _hoops_SRGCH, _hoops_ISAPI);

			_hoops_CCP->ysize = f1;
			_hoops_CCP->_hoops_RGRS = f1*nr->_hoops_SRA->current._hoops_AGRS;
		} break;

		case _hoops_PRPCH: {
			_hoops_ICP alter &	_hoops_CCP = *(_hoops_ICP alter *)
					HIC_Intermediate_Utility (inr, _hoops_SRGCH, _hoops_ISAPI);

			_hoops_CCP->_hoops_PHP = f1;
			_hoops_CCP->_hoops_HHP = _hoops_ISPI;

			Display_Context alter *	dc = (Display_Context alter *)nr->_hoops_SRA;

			if (_hoops_CCP->_hoops_HHP == _hoops_SHGRP) {
				float					size;

				size = _hoops_CCP->_hoops_PHP * _hoops_RRRIP * dc->current._hoops_PRPSR.y;
				_hoops_CCP->ysize = size;
				_hoops_CCP->_hoops_RGRS = size*dc->current._hoops_AGRS;
			}
			else if (_hoops_CCP->_hoops_HHP == GSU_PIXELS) {
				_hoops_CCP->ysize = _hoops_CCP->_hoops_PHP*0.5f;
				_hoops_CCP->_hoops_RGRS = _hoops_CCP->_hoops_PHP*0.5f*dc->current._hoops_AGRS;
			}
			else
				_hoops_CCP->ysize = _hoops_CCP->_hoops_RGRS = -1.0f;


		} break;


		case _hoops_HRPCH: {
			_hoops_ICP alter &	_hoops_CCP = *(_hoops_ICP alter *)
					HIC_Intermediate_Utility (inr, _hoops_PCGCH, _hoops_ISAPI);

			_hoops_CCP->ysize = f1;
			_hoops_CCP->_hoops_RGRS = f1*nr->_hoops_SRA->current._hoops_AGRS;
		} break;

		case _hoops_IRPCH: {
			_hoops_ICP alter &	_hoops_CCP = *(_hoops_ICP alter *)
					HIC_Intermediate_Utility (inr, _hoops_PCGCH, _hoops_ISAPI);

			_hoops_CCP->_hoops_PHP = f1;
			_hoops_CCP->_hoops_HHP = _hoops_ISPI;

			Display_Context alter *	dc = (Display_Context alter *)nr->_hoops_SRA;

			if (_hoops_CCP->_hoops_HHP == _hoops_SHGRP) {
				float					size;

				size = _hoops_CCP->_hoops_PHP * _hoops_RRRIP * dc->current._hoops_PRPSR.y;
				_hoops_CCP->ysize = size;
				_hoops_CCP->_hoops_RGRS = size*dc->current._hoops_AGRS;
			}
			else if (_hoops_CCP->_hoops_HHP == GSU_PIXELS) {
				_hoops_CCP->ysize = _hoops_CCP->_hoops_PHP*0.5f;
				_hoops_CCP->_hoops_RGRS = _hoops_CCP->_hoops_PHP*0.5f*dc->current._hoops_AGRS;
			}
			else
				_hoops_CCP->ysize = _hoops_CCP->_hoops_RGRS = -1.0f;


		} break;


		case _hoops_CRPCH: {
			_hoops_ICP alter &	_hoops_CCP = *(_hoops_ICP alter *)
					HIC_Intermediate_Utility (inr, _hoops_SRGCH, _hoops_ISAPI);

			_hoops_CCP->color = (RGBAS32 const &)_hoops_ISPI;
		} break;

		case _hoops_SRPCH: {
			_hoops_ICP alter &	_hoops_CCP = *(_hoops_ICP alter *)
					HIC_Intermediate_Utility (inr, _hoops_PCGCH, _hoops_ISAPI);

			_hoops_CCP->color = (RGBAS32 const &)_hoops_ISPI;
		} break;

		case _hoops_GAPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->transform = _hoops_ISPI;
			_hoops_HRCIR->_hoops_SRRIP();
		} break;

		case _hoops_RAPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->_hoops_PHP = f1;
			_hoops_HRCIR->_hoops_SRRIP();
		} break;

		case _hoops_AAPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->_hoops_GHGRP = _hoops_ISPI;
			_hoops_HRCIR->_hoops_SRRIP();
		} break;

		case _hoops_PAPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->_hoops_ACPAP = f1;
			_hoops_HRCIR->_hoops_SRRIP();
		} break;

		case _hoops_HAPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->_hoops_SSPAP = (_hoops_GIGRP)_hoops_ISPI;
			_hoops_HRCIR->_hoops_SRRIP();
		} break;

		case _hoops_IAPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->_hoops_PCPAP = f1;
		} break;


		case _hoops_CAPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->_hoops_GGHAP = (_hoops_GIGRP)_hoops_ISPI;
		} break;

		case _hoops_SAPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->_hoops_PRRIP = _hoops_ISPI;
		} break;

		case _hoops_GPPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->spacing = f1;
		} break;

		case _hoops_RPPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->path.x = f1;
			_hoops_HRCIR->path.y = f2;
			_hoops_HRCIR->path.z = _hoops_CGHGR;
		} break;

		case _hoops_APPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->_hoops_CRRIP = false;
			_hoops_HRCIR->rotation = f1;
			_hoops_HRCIR->_hoops_SRRIP();
		} break;

		case _hoops_PPPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
				HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->_hoops_CRRIP = true;
			_hoops_HRCIR->_hoops_SRRIP();
			HIC_Intermediate_Utility (inr, _hoops_SAGCH, _hoops_ISAPI);
		} break;

		case _hoops_HPPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
				HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->width_scale = f1;
			_hoops_HRCIR->_hoops_SRRIP();
		} break;

		case _hoops_IPPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
				HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->_hoops_IPGRP = f1;
			_hoops_HRCIR->_hoops_SRRIP();
		} break;

		case _hoops_CPPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
					HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->color = (RGBAS32 const &)_hoops_ISPI;
		} break;

		case _hoops_SPPCH: {
			Text_Info alter *		ti = (Text_Info alter *)pointer;
			Point					_hoops_IHPPI (f1, f2, _hoops_CGHGR);

			ti->_hoops_CPPSP += _hoops_IHPPI - ti->position;
			ti->position = _hoops_IHPPI;
		} break;

		case _hoops_GHPCH: {
			Text_Info alter *		ti = (Text_Info alter *)pointer;

			ti->_hoops_CSAGR = Point (f1, f2, _hoops_CGHGR);
		} break;

		case _hoops_RHPCH: {
			_hoops_HACC alter *		t = (_hoops_HACC alter *)pointer;

			t->_hoops_CSAI = Point (f1, f2, _hoops_CGHGR);
		} break;

		case _hoops_AHPCH: {
			_hoops_IGCSR alter &	_hoops_HRCIR = *(_hoops_IGCSR alter *)
				HIC_Intermediate_Utility (inr, _hoops_AAGCH, _hoops_ISAPI);

			_hoops_HRCIR->_hoops_GRCSR = _hoops_ISPI;
		} break;

		case _hoops_PHPCH: {
			Text_Info alter *	iti = (Text_Info alter *)pointer;

			iti->_hoops_PPPSP = (int *)_hoops_ISPI;
		} break;

		case _hoops_HHPCH: {
			Text_Info alter *	iti = (Text_Info alter *)pointer;

			iti->_hoops_HGCSR = (_hoops_PGCSR *)_hoops_ISPI;
		} break;

		case _hoops_IHPCH: {
			Text_Info alter *	iti = (Text_Info alter *)pointer;
			iti->line_index = _hoops_ISPI;
		} break;

		case _hoops_CHPCH: {
			_hoops_PGCSR alter *	ki = (_hoops_PGCSR alter *)pointer;

			ki->position = Point (f1, f2, _hoops_CGHGR);
		} break;

		case _hoops_SHPCH: {
			_hoops_PGCSR alter *	ki = (_hoops_PGCSR alter *)pointer;

			ki->point = Point (f1, f2, _hoops_CGHGR);
		} break;

		case _hoops_GIPCH: {
			_hoops_PGCSR alter *	ki = (_hoops_PGCSR alter *)pointer;

			ki->string.width = f1;
		} break;

		case _hoops_RIPCH: {
			_hoops_PGCSR alter *	ki = (_hoops_PGCSR alter *)pointer;

			ki->string.height = f1;
		} break;

		case _hoops_AIPCH: {
			_hoops_PGCSR alter *	ki = (_hoops_PGCSR alter *)pointer;

			ki->string.x = f1;
		} break;

		case _hoops_PIPCH: {
			_hoops_PGCSR alter *	ki = (_hoops_PGCSR alter *)pointer;

			ki->string.y = f1;
		} break;

		case _hoops_HIPCH: {
			_hoops_PGCSR alter *	ki = (_hoops_PGCSR alter *)pointer;

			ki->screen.width = f1;
		} break;

		case _hoops_IIPCH: {
			_hoops_PGCSR alter *	ki = (_hoops_PGCSR alter *)pointer;

			ki->screen.height = f1;
		} break;

		case _hoops_CIPCH: {
			_hoops_PGCSR alter *	ki = (_hoops_PGCSR alter *)pointer;

			ki->screen.x = f1;
		} break;

		case _hoops_SIPCH: {
			_hoops_PGCSR alter *	ki = (_hoops_PGCSR alter *)pointer;

			ki->screen.y = f1;
		} break;

		case _hoops_GCPCH: {
			_hoops_PGCSR alter *	ki = (_hoops_PGCSR alter *)pointer;

			ki->flags = _hoops_ISPI;
		} break;


		case _hoops_RCPCH: {
			_hoops_CGRA alter &	_hoops_SGRA = *(_hoops_CGRA alter *)
				HIC_Intermediate_Utility (inr, _hoops_PAGCH, _hoops_ISAPI);

			HD_Figure_Driver_Color (nr, (RGB const *)pointer, (Driver_Color alter *)&_hoops_SGRA->_hoops_GPIR);
		} break;

		case _hoops_ACPCH: {
			_hoops_CGRA alter &	_hoops_SGRA = *(_hoops_CGRA alter *)
				HIC_Intermediate_Utility (inr, _hoops_PAGCH, _hoops_ISAPI);

			_hoops_SGRA->_hoops_GPIR = (RGBAS32 const &)_hoops_ISPI;
		} break;

		case _hoops_PCPCH: {
			_hoops_CGRA alter &	_hoops_SGRA = *(_hoops_CGRA alter *)
				HIC_Intermediate_Utility (inr, _hoops_PAGCH, _hoops_ISAPI);

			HD_Figure_Driver_Color (nr, (RGB const *)pointer, (Driver_Color alter *)&_hoops_SGRA->contrast_color);
		} break;

		case _hoops_HCPCH: {
			_hoops_CGRA alter &	_hoops_SGRA = *(_hoops_CGRA alter *)
				HIC_Intermediate_Utility (inr, _hoops_PAGCH, _hoops_ISAPI);

			_hoops_SGRA->contrast_color = (RGBAS32 const &)_hoops_ISPI;
		} break;

		case _hoops_ICPCH: {
			_hoops_CAHHP alter &	_hoops_CRAIR = *(_hoops_CAHHP alter *)
				HIC_Intermediate_Utility (inr, _hoops_RAGCH, _hoops_ISAPI);

			_hoops_CRAIR->_hoops_RHHHP = (_hoops_GARSR)_hoops_ISPI;
		} break;

		case _hoops_CCPCH: {
			_hoops_HHCR alter &	_hoops_IHCR = *(_hoops_HHCR alter *)
				HIC_Intermediate_Utility (inr, _hoops_PRGCH, _hoops_ISAPI);

			_hoops_IHCR->_hoops_CHIH = f1;
		} break;

		case _hoops_SCPCH:{
			_hoops_HHCR alter &	_hoops_IHCR = *(_hoops_HHCR alter *)
				HIC_Intermediate_Utility (inr, _hoops_PRGCH, _hoops_ISAPI);

			_hoops_IHCR->_hoops_SHIH = f1;
		} break;

		case _hoops_GSPCH: {
			_hoops_HHCR alter &	_hoops_IHCR = *(_hoops_HHCR alter *)
				HIC_Intermediate_Utility (inr, _hoops_PRGCH, _hoops_ISAPI);

			_hoops_IHCR->flags &= ~_hoops_AIHS;
			_hoops_IHCR->_hoops_AGAA.left = _hoops_ISPI;
			_hoops_IHCR->_hoops_AGAA.right = _hoops_CSPI;
			_hoops_IHCR->_hoops_AGAA.bottom = _hoops_SSPI;
			_hoops_IHCR->_hoops_AGAA.top = _hoops_SGHI;

			_hoops_AHAGR const * _hoops_CSC = nr->_hoops_SAIR->_hoops_ASSIR;
			if (_hoops_CSC != null &&
				_hoops_CSC->_hoops_PSSIR() != null &&
				_hoops_CSC->_hoops_PSSIR()->_hoops_HIAI != null)
				HIC_Intermediate_Utility (inr, _hoops_CIGCH, _hoops_ISAPI);
		} break;

		case _hoops_RSPCH: {
			_hoops_HHCR alter &	_hoops_IHCR = *(_hoops_HHCR alter *)
				HIC_Intermediate_Utility (inr, _hoops_PRGCH, _hoops_ISAPI);

			_hoops_IHCR->flags &= ~_hoops_AIHS;
			if (_hoops_ISPI > _hoops_IHCR->_hoops_AGAA.left)
				_hoops_IHCR->_hoops_AGAA.left = _hoops_ISPI;
			if (_hoops_CSPI < _hoops_IHCR->_hoops_AGAA.right)
				_hoops_IHCR->_hoops_AGAA.right = _hoops_CSPI;
			if (_hoops_SSPI > _hoops_IHCR->_hoops_AGAA.bottom)
				_hoops_IHCR->_hoops_AGAA.bottom = _hoops_SSPI;
			if (_hoops_SGHI < _hoops_IHCR->_hoops_AGAA.top)
				_hoops_IHCR->_hoops_AGAA.top = _hoops_SGHI;

			_hoops_AHAGR const * _hoops_CSC = nr->_hoops_SAIR->_hoops_ASSIR;
			if (_hoops_CSC != null &&
				_hoops_CSC->_hoops_PSSIR() != null &&
				_hoops_CSC->_hoops_PSSIR()->_hoops_HIAI != null)
				HIC_Intermediate_Utility (inr, _hoops_CIGCH, _hoops_ISAPI);
		} break;

		case _hoops_ASPCH: {
			_hoops_HHCR alter &	_hoops_IHCR = *(_hoops_HHCR alter *)
				HIC_Intermediate_Utility (inr, _hoops_PRGCH, _hoops_ISAPI);

			_hoops_IHCR->_hoops_HCHH = _hoops_HSRGA::Create(nr->_hoops_SRA);
			if ((_hoops_IHCR->_hoops_HCHH->_hoops_PSHH = (_hoops_ASHH const *)pointer) != null)
				_hoops_CAHS (_hoops_IHCR->_hoops_HCHH->_hoops_PSHH);
		} break;

		case _hoops_HCGCH: {
			HIC_Intermediate_Utility (inr, _hoops_PRGCH, _hoops_ISAPI);

			HD_Add_Cutting_Plane (nr, (_hoops_ARPA alter *)pointer);
		} break;

		case _hoops_ICGCH: {
			HIC_Intermediate_Utility (inr, _hoops_PRGCH, _hoops_ISAPI);
			HD_Remove_Cutting_Planes(nr);
		} break;


		case _hoops_PSPCH: {
			nr->_hoops_RGP = (_hoops_ACHR)_hoops_ISPI;
		} break;

		case _hoops_HSPCH: {
			Marker const *	marker = (Marker const *)pointer;
			return (void *)(&marker->_hoops_CSAI);
		} break;

		case _hoops_ISPCH: {
			Geometry const *		geometry = (Geometry const *)pointer;

			if (geometry->type == _hoops_PIIP) {
				return (void *)(POINTER_SIZED_INT)2;
			}
			else {
				Polyline const *	polyline = (Polyline const *)geometry;
				return (void *)(POINTER_SIZED_INT)polyline->count;
			}
		} break;

		case _hoops_CSPCH: {
			Geometry const *		geometry = (Geometry const *)pointer;

			if (geometry->type == _hoops_PIIP) {
				Line const *		line = (Line const *)geometry;
				return (void *)line->points;
			}
			else {
				Polyline const *	polyline = (Polyline const *)geometry;
				return (void *)polyline->points;
			}
		} break;

		case _hoops_SSPCH: {
			Polygon const *	polygon = (Polygon const *)pointer;
			return (void *)(POINTER_SIZED_INT)polygon->count;
		} break;

		case _hoops_GGHCH: {
			Polygon const *	polygon = (Polygon const *)pointer;
			return (void *)polygon->points;
		} break;

		case _hoops_RGHCH: {
			_hoops_GRA			_hoops_RRA = *(_hoops_GRA alter *)
				HIC_Intermediate_Utility (inr, _hoops_SGRCH, _hoops_ISAPI);

			_hoops_RRA->_hoops_PRSI._hoops_IISRP = (int)_hoops_ISPI;
		} break;

		case _hoops_AGHCH: {
			return (void *)&nr->_hoops_SRA->_hoops_APHHP->_hoops_AICAH;
		} break;

		case _hoops_PGHCH: {
			return (void *)&nr->_hoops_SRA->_hoops_APHHP->bounding;
		} break;

		case _hoops_HGHCH: {
			if (nr->_hoops_SRA->_hoops_APHHP == null)
				return 0;
			return (void *)(POINTER_SIZED_INT)nr->_hoops_SRA->_hoops_APHHP->event->status;
		} break;

		case _hoops_IGHCH: {
			if (nr->_hoops_SRA->_hoops_APHHP == null)
				return 0;
			return (void *)(POINTER_SIZED_INT)nr->_hoops_SRA->_hoops_APHHP->event->_hoops_CHSHA;
		} break;

		case _hoops_CGHCH:{
			Segment_Info const *	si = (Segment_Info const *)pointer;
			if (!BIT (si->segment->_hoops_RRHH, _hoops_GGCCA))
				(void)HIC_Intermediate_Utility (inr, _hoops_GIGCH, (void *)si->segment, IM_NO_VALUES);
		} break;

		case _hoops_SGHCH: {
			Segment_Info const *	si = (Segment_Info const *)pointer;
			if (BIT (si->segment->_hoops_RRHH, _hoops_GGCCA))
				(void)HIC_Intermediate_Utility (inr, _hoops_RIGCH, (void *)si->segment, IM_NO_VALUES);
		} break;

		case _hoops_GRHCH: {
			Segment_Info const *	si = (Segment_Info const *)pointer;
			if (BIT(si->segment->_hoops_RRHH, _hoops_GGCCA))
				return (void *)(POINTER_SIZED_INT)true;
			return (void *)(POINTER_SIZED_INT)false;
		} break;

		case _hoops_RRHCH: {
			Geometry const *		geo = (Geometry const *)pointer;
			if (!BIT (geo->_hoops_RRHH, _hoops_GGCCA))
				(void)HIC_Intermediate_Utility (inr, _hoops_GIGCH, (void *)geo, IM_NO_VALUES);
		} break;

		case _hoops_ARHCH: {
			Geometry const *		geo = (Geometry const *)pointer;
			if (BIT (geo->_hoops_RRHH, _hoops_GGCCA))
				(void)HIC_Intermediate_Utility (inr, _hoops_RIGCH, (void *)geo, IM_NO_VALUES);
		} break;

		case _hoops_PRHCH: {
			Geometry const *		geo = (Geometry const *)pointer;
			if (BIT(geo->_hoops_RRHH, _hoops_GGCCA))
				return (void *)(POINTER_SIZED_INT)true;
			return (void *)(POINTER_SIZED_INT)false;
		} break;

		case _hoops_HRHCH: {
			if (nr->_hoops_SRA->_hoops_RAI &&
				!BIT (nr->_hoops_SRA->_hoops_RAI->_hoops_RRHH, _hoops_GGCCA))
				(void)HIC_Intermediate_Utility (inr, _hoops_GIGCH,
					(void *)nr->_hoops_SRA->_hoops_RAI, IM_NO_VALUES);
		} break;

		case _hoops_IRHCH: {
			if (nr->_hoops_SRA->_hoops_RAI &&
				BIT (nr->_hoops_SRA->_hoops_RAI->_hoops_RRHH, _hoops_GGCCA))
				(void)HIC_Intermediate_Utility (inr, _hoops_RIGCH,
					(void *)nr->_hoops_SRA->_hoops_RAI, IM_NO_VALUES);
		} break;

		case _hoops_CRHCH: {
			if (nr->_hoops_SRA->_hoops_RAI == null)
				return 0;

			if (BIT(nr->_hoops_SRA->_hoops_RAI->_hoops_RRHH, _hoops_GGCCA))
				return (void *)(POINTER_SIZED_INT)true;
			return (void *)(POINTER_SIZED_INT)false;
		} break;

		case _hoops_SRHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)ts->points;
		} break;

		case _hoops_GAHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			ts->points = (Point *)_hoops_ISPI;
		} break;

		case _hoops_RAHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)(POINTER_SIZED_INT)ts->point_count;
		} break;

		case _hoops_AAHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)(POINTER_SIZED_INT)ts->face_count;
		} break;

		case _hoops_PAHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)(POINTER_SIZED_INT)ts->_hoops_PHHA;
		} break;

		case _hoops_HAHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			ts->_hoops_PHHA = _hoops_ISPI;
			if (ts->total == 0)
				ts->total = 3*ts->_hoops_PHHA; //_hoops_GRS _hoops_PAHH _hoops_HGCR _hoops_CPAHA _hoops_HPP _hoops_CHPPI _hoops_SPHR
			if (ts->point_count == 0)
				ts->point_count = 3*ts->_hoops_PHHA; //_hoops_GRS _hoops_PAHH _hoops_HGCR _hoops_CPAHA _hoops_HPP _hoops_SHPPI _hoops_SPHR
		} break;

		case _hoops_IAHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)ts->lengths;
		} break;

		case _hoops_CAHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			int *				lns = (int*)_hoops_ISPI;

			if (BIT (ts->_hoops_RAHH, _hoops_AAHH)) {
				if (ts->lengths != null)
					FREE_ARRAY (ts->lengths, ts->lengths_allocated, int);
			}
			else {
				/* _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_HPGGR _hoops_GIPPI, _hoops_HIS _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_RII _hoops_CIHA
				 * _hoops_CICRR _hoops_SGS _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HAII, _hoops_SR _hoops_RRP _hoops_IS _hoops_CCPP _hoops_PPR _hoops_IRAA
				 * _hoops_SAII */
				if (ts->_hoops_AIHA) {
					int *vi;
					int count = (ts->_hoops_IPII > 0 ? ts->_hoops_IPII : ts->total);
					ALLOC_ARRAY (vi, count, int);
					_hoops_AIGA (ts->_hoops_AIHA, ts->total, int, vi);
					ts->_hoops_AIHA = vi;
				}
				if (ts->face_indices) {
					int *fi;
					int count = (ts->_hoops_SGAHR > 0 ? ts->_hoops_SGAHR : ts->total);
					ASSERT (count >= ts->total);
					ALLOC_ARRAY (fi, count, int);
					_hoops_AIGA (ts->face_indices, ts->total, int, fi);
					ts->face_indices = fi;
				}
			}
			_hoops_APRGA(lns, ts->_hoops_PHHA, int, ts->lengths);
			ts->lengths_allocated = ts->_hoops_PHHA;
			ts->total = 0;
			int ii;
			for (ii=0; ii<ts->_hoops_PHHA; ii++) {
				if (lns[ii] > 0)
					(ts)->total += lns[ii];
				else
					(ts)->total -= lns[ii];
			}
			ts->_hoops_RAHH |= _hoops_AAHH;
		} break;

		case _hoops_SAHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)ts->_hoops_AIHA;
		} break;

		case _hoops_GPHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			int *vi = (int*)_hoops_ISPI;
			int i, _hoops_RIPPI;

			if (BIT (ts->_hoops_RAHH, _hoops_AAHH)) {
				if (ts->_hoops_AIHA != null)
					FREE_ARRAY (ts->_hoops_AIHA, ts->_hoops_IPII, int);
			}
			else {
				/* _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_HPGGR _hoops_GIPPI, _hoops_HIS _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_RII _hoops_CIHA
				 * _hoops_CICRR _hoops_SGS _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HAII, _hoops_SR _hoops_RRP _hoops_IS _hoops_CCPP _hoops_PPR _hoops_IRAA
				 * _hoops_SAII */
				if (ts->face_indices) {
					int *fi;
					int count = (ts->_hoops_SGAHR > 0 ? ts->_hoops_SGAHR : ts->total);
					ASSERT (count >= ts->total);
					ALLOC_ARRAY (fi, count, int);
					_hoops_AIGA (ts->face_indices, ts->total, int, fi);
					ts->face_indices = fi;
				}
				if (ts->lengths) {
					int *lengths;
					int count = (ts->lengths_allocated > 0 ? ts->lengths_allocated : ts->_hoops_PHHA);
					ALLOC_ARRAY (lengths, count, int);
					_hoops_AIGA (ts->lengths, ts->total, int, lengths);
					ts->lengths = lengths;
				}
			}
			_hoops_APRGA(vi, ts->total, int, ts->_hoops_AIHA);
			ts->_hoops_IPII = ts->total;
			_hoops_RIPPI = 0;
			for (i = 0 ; i < ts->total ; i++) {
				if (ts->_hoops_AIHA[i] > _hoops_RIPPI)
					_hoops_RIPPI = ts->_hoops_AIHA[i];
				ts->point_count = _hoops_RIPPI+1;
			}
			ts->_hoops_RAHH |= _hoops_AAHH;
		} break;

		case _hoops_RPHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)ts->face_indices;
		} break;

		case _hoops_APHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			int *				fi = (int*)_hoops_ISPI;

			if (BIT (ts->_hoops_RAHH, _hoops_AAHH)) {
				if (ts->face_indices != null)
					FREE_ARRAY (ts->face_indices, ts->_hoops_SGAHR, int);
			}
			else {
				/* _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_HPGGR _hoops_GIPPI, _hoops_HIS _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_RII _hoops_CIHA
				 * _hoops_CICRR _hoops_SGS _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HAII, _hoops_SR _hoops_RRP _hoops_IS _hoops_CCPP _hoops_PPR _hoops_IRAA
				 * _hoops_SAII */
				if (ts->_hoops_AIHA) {
					int *vi;
					int count = (ts->_hoops_IPII > 0 ? ts->_hoops_IPII : ts->total);
					ALLOC_ARRAY (vi, count, int);
					_hoops_AIGA (ts->_hoops_AIHA, ts->total, int, vi);
					ts->_hoops_AIHA = vi;
				}
				if (ts->lengths) {
					int *lengths;
					int count = (ts->lengths_allocated > 0 ? ts->lengths_allocated : ts->_hoops_PHHA);
					ALLOC_ARRAY (lengths, count, int);
					_hoops_AIGA (ts->lengths, ts->total, int, lengths);
					ts->lengths = lengths;
				}
			}
			_hoops_APRGA(fi, ts->total, int, ts->face_indices);
			ts->_hoops_SGAHR = ts->total;
			ts->face_count = 0;
			ts->_hoops_RAHH |= _hoops_AAHH;
		} break;

		case _hoops_PPHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)ts->_hoops_PAGI;
		} break;

		case _hoops_HPHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			RGB *			fcolors = (RGB*)_hoops_ISPI;
			ts->_hoops_PAGI = fcolors;
		} break;

		case _hoops_IPHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)ts->_hoops_PRHH;
		} break;

		case _hoops_CPHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			_hoops_ARPA *			fnormals = (_hoops_ARPA*)_hoops_ISPI;
			ts->_hoops_PRHH = fnormals;
		} break;

		case _hoops_SPHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)ts->_hoops_PCHA;
		} break;

		case _hoops_GHHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			RGB *			vcolors = (RGB*)_hoops_ISPI;
			ts->_hoops_PCHA = vcolors;
		} break;

		case _hoops_RHHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)ts->_hoops_HCHA;
		} break;

		case _hoops_AHHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			float *				vfindices = (float*)_hoops_ISPI;
			ts->_hoops_HCHA = vfindices;
		} break;

		case _hoops_PHHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)ts->_hoops_ICHA;
		} break;

		case _hoops_HHHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			Vector *			vnormals = (Vector*)_hoops_ISPI;
			ts->_hoops_ICHA = vnormals;
		} break;

		case _hoops_IHHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)ts->_hoops_GSSH->_hoops_CCHA;
		} break;

		case _hoops_CHHCH: {
			Tristrip alter *			ts = (Tristrip alter *)pointer;
			_hoops_RRCC alter *	_hoops_HAPAR  = ts->_hoops_GSSH;
			_hoops_RSSH *					vparameters = (_hoops_RSSH*)_hoops_ISPI;
			if (BIT (_hoops_HAPAR->_hoops_SCAI, _hoops_ARCC)) {
				FREE_ARRAY (_hoops_HAPAR->_hoops_CCHA, _hoops_HAPAR->_hoops_CGAHR * _hoops_HAPAR->_hoops_GSHA, _hoops_RSSH);
				_hoops_HAPAR->_hoops_SCAI &= ~_hoops_ARCC;
			}
			_hoops_HAPAR->_hoops_CCHA = vparameters;
		} break;

		case _hoops_SHHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)(POINTER_SIZED_INT)ts->_hoops_GSSH->_hoops_GSHA;
		} break;

		case _hoops_GIHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			ts->_hoops_GSSH->_hoops_GSHA = (Integer32)_hoops_ISPI;
		} break;

		case _hoops_RIHCH: {
			Tristrip const *	ts = (Tristrip const *)pointer;
			return (void *)(POINTER_SIZED_INT)ts->_hoops_RPRCP;
		} break;

		case _hoops_AIHCH: {
			Tristrip alter *	ts = (Tristrip alter *)pointer;
			ts->_hoops_RPRCP = (_hoops_ISPI != 0);
		} break;

		case _hoops_PIHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)pe->points;
		} break;

		case _hoops_HIHCH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			pe->points = (Point *)_hoops_ISPI;
		} break;

		case _hoops_IIHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)(POINTER_SIZED_INT)pe->point_count;
		} break;

		case _hoops_CIHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)(POINTER_SIZED_INT)pe->_hoops_SPHA;
		} break;

		case _hoops_SIHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)(POINTER_SIZED_INT)pe->_hoops_PHHA;
		} break;

		case _hoops_GCHCH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			pe->_hoops_PHHA = (int)_hoops_ISPI;
		} break;

		case _hoops_RCHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)pe->lengths;
		} break;

		case _hoops_ACHCH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			int *				lns = (int*)_hoops_ISPI;

			if (BIT (pe->_hoops_RAHH, _hoops_AAHH)) {
				if (pe->lengths)
					FREE_ARRAY (pe->lengths, pe->lengths_allocated, int);
			}
			else {
				/* _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_HPGGR _hoops_GIPPI, _hoops_HIS _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_PCCP _hoops_AIPPI
				 * _hoops_CRS _hoops_SGS _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HAII, _hoops_SR _hoops_RRP _hoops_IS _hoops_CCPP _hoops_PPR _hoops_IRAA
				 * _hoops_SAII */
				if (pe->_hoops_AIHA) {
					int *vi;
					int count = (pe->_hoops_IPII>0 ? pe->_hoops_IPII : pe->total);
					ASSERT (count >= pe->total);
					ALLOC_ARRAY (vi, count, int);
					_hoops_AIGA (pe->_hoops_AIHA, pe->total, int, vi);
					pe->_hoops_AIHA = vi;
				}
				if (pe->_hoops_SPII) {
					int *ei;
					int count = (pe->_hoops_CPII>0 ? pe->_hoops_CPII : pe->total);
					ASSERT (count >= pe->total);
					ALLOC_ARRAY (ei, count, int);
					_hoops_AIGA (pe->_hoops_SPII, pe->total, int, ei);
					pe->_hoops_SPII = ei;
				}
			}
			_hoops_APRGA(lns, pe->_hoops_PHHA, int, pe->lengths);
			pe->lengths_allocated = pe->_hoops_PHHA;
			pe->total = 0;
			int ii;
			for (ii=0; ii<pe->_hoops_PHHA; ii++) {
				if (lns[ii] > 0)
					pe->total += lns[ii];
				else
					pe->total -= lns[ii];
			}
			pe->_hoops_RAHH |= _hoops_AAHH;
		} break;

		case _hoops_PCHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)pe->_hoops_AIHA;
		} break;

		case _hoops_HCHCH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			int *				vi = (int*)_hoops_ISPI;

			if (BIT (pe->_hoops_RAHH, _hoops_AAHH)) {
				if (pe->_hoops_AIHA)
					FREE_ARRAY (pe->_hoops_AIHA, pe->_hoops_IPII, int);
			}
			else {
				/* _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_HPGGR _hoops_GIPPI, _hoops_HIS _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_PCCP _hoops_AIPPI
				 * _hoops_CRS _hoops_SGS _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HAII, _hoops_SR _hoops_RRP _hoops_IS _hoops_CCPP _hoops_PPR _hoops_IRAA
				 * _hoops_SAII */
				if (pe->_hoops_SPII) {
					int *ei;
					int count = (pe->_hoops_CPII>0 ? pe->_hoops_CPII : pe->total);
					ASSERT (count >= pe->total);
					ALLOC_ARRAY (ei, count, int);
					_hoops_AIGA (pe->_hoops_SPII, pe->total, int, ei);
					pe->_hoops_SPII = ei;
				}
				if (pe->lengths) {
					int *lengths;
					int count = (pe->lengths_allocated>0 ? pe->lengths_allocated : pe->_hoops_PHHA);
					ASSERT (count >= pe->_hoops_PHHA);
					ALLOC_ARRAY (lengths, count, int);
					_hoops_AIGA (pe->_hoops_SPII, pe->_hoops_PHHA, int, lengths);
					pe->_hoops_SPII = lengths;
				}
			}
			_hoops_APRGA(vi, pe->total, int, pe->_hoops_AIHA);
			pe->_hoops_IPII = pe->total;
			pe->_hoops_RAHH |= _hoops_AAHH;
		} break;

		case _hoops_ICHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)pe->_hoops_SPII;
		} break;

		case _hoops_CCHCH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			int *				ei = (int*)_hoops_ISPI;

			if (BIT (pe->_hoops_RAHH, _hoops_AAHH)) {
				if (pe->_hoops_SPII)
					FREE_ARRAY (pe->_hoops_SPII, pe->_hoops_CPII, int);
			}
			else {
				/* _hoops_SR'_hoops_ASAR _hoops_AHCA _hoops_IS _hoops_HPGGR _hoops_GIPPI, _hoops_HIS _hoops_RPP _hoops_IIH'_hoops_GRI _hoops_IRS _hoops_ACHAR
				 * _hoops_CRS _hoops_SGS _hoops_SR _hoops_GA'_hoops_RA _hoops_AIAH _hoops_HAII, _hoops_SR _hoops_RRP _hoops_IS _hoops_CCPP _hoops_PPR _hoops_IRAA
				 * _hoops_SAII */
				if (pe->_hoops_AIHA) {
					int *vi;
					int count = (pe->_hoops_IPII>0 ? pe->_hoops_IPII : pe->total);
					ASSERT (count >= pe->total);
					ALLOC_ARRAY (vi, count, int);
					_hoops_AIGA (pe->_hoops_AIHA, pe->total, int, vi);
					pe->_hoops_AIHA = vi;
				}
				if (pe->lengths) {
					int *lengths;
					int count = (pe->lengths_allocated>0 ? pe->lengths_allocated : pe->_hoops_PHHA);
					ASSERT (count >= pe->_hoops_PHHA);
					ALLOC_ARRAY (lengths, count, int);
					_hoops_AIGA (pe->_hoops_SPII, pe->_hoops_PHHA, int, lengths);
					pe->_hoops_SPII = lengths;
				}
			}
			_hoops_APRGA(ei, pe->total, int, pe->_hoops_SPII);
			pe->_hoops_CPII = pe->total;

			pe->_hoops_SPHA = 0;
			for (int i = 0 ; i < pe->total ; i++) {
				if (pe->_hoops_SPII[i] >= pe->_hoops_SPHA)
					pe->_hoops_SPHA = pe->_hoops_SPII[i] + 1;
			}

			pe->_hoops_RAHH |= _hoops_AAHH;
		} break;

		case _hoops_SCHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)pe->_hoops_ASHA;
		} break;

		case _hoops_GSHCH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			RGB *			ecolors = (RGB*)_hoops_ISPI;
			pe->_hoops_ASHA = ecolors;
		} break;

		case _hoops_RSHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)pe->_hoops_RSHA;
		} break;

		case _hoops_ASHCH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			Vector *			enormals = (Vector*)_hoops_ISPI;
			pe->_hoops_RSHA = enormals;
		} break;

		case _hoops_PSHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)pe->_hoops_PCHA;
		} break;

		case _hoops_HSHCH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			RGB *			vcolors = (RGB*)_hoops_ISPI;
			pe->_hoops_PCHA = vcolors;
		} break;

		case _hoops_ISHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)pe->_hoops_HCHA;
		} break;

		case _hoops_CSHCH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			float *				vfindices = (float*)_hoops_ISPI;
			pe->_hoops_HCHA = vfindices;
		} break;

		case _hoops_SSHCH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)pe->_hoops_ICHA;
		} break;

		case _hoops_GGICH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			Vector *			vnormals = (Vector*)_hoops_ISPI;
			pe->_hoops_ICHA = vnormals;
		} break;

		case _hoops_RGICH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)pe->_hoops_CCHA;
		} break;

		case _hoops_AGICH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			_hoops_RSSH *		vparameters = (_hoops_RSSH*)_hoops_ISPI;
			pe->_hoops_CCHA = vparameters;
		} break;

		case _hoops_PGICH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)(POINTER_SIZED_INT)pe->_hoops_GSHA;
		} break;

		case _hoops_HGICH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			pe->_hoops_GSHA = _hoops_ISPI;
		} break;

		case _hoops_IGICH: {
			Polyedge const *	pe = (Polyedge const *)pointer;
			return (void *)(POINTER_SIZED_INT)pe->_hoops_RPRCP;
		} break;

		case _hoops_CGICH: {
			Polyedge alter *	pe = (Polyedge alter *)pointer;
			pe->_hoops_RPRCP = (_hoops_ISPI != 0);
		} break;

		case _hoops_SGICH: {
			Polymarker const *	pm = (Polymarker const *)pointer;
			return (void *)pm->points;
		} break;

		case _hoops_GRICH: {
			Polymarker alter *	pm = (Polymarker alter *)pointer;
			Point *				pts = (Point*)_hoops_ISPI;
			pm->points = pts;
		} break;

		case _hoops_RRICH: {
			Polymarker const *	pm = (Polymarker const *)pointer;
			return (void *)(POINTER_SIZED_INT)pm->point_count;
		} break;

		case _hoops_ARICH: {
			Polymarker const *	pm = (Polymarker const *)pointer;
			return (void *)(POINTER_SIZED_INT)pm->length;
		} break;

		case _hoops_PRICH: {
			Polymarker alter *	pm = (Polymarker alter *)pointer;
			int						len = (int)_hoops_ISPI;
			pm->length = len;
		} break;

		case _hoops_HRICH: {
			Polymarker const *	pm = (Polymarker const *)pointer;
			return (void *)pm->_hoops_AIHA;
		} break;

		case _hoops_IRICH: {
			Polymarker alter *	pm = (Polymarker alter *)pointer;
			int *					vi = (int *)_hoops_ISPI;

			if (pm->_hoops_AIHA != null && BIT (pm->_hoops_RAHH, _hoops_AAHH))
				FREE_ARRAY (pm->_hoops_AIHA, pm->_hoops_IPII, int);
			_hoops_APRGA(vi, pm->length, int, pm->_hoops_AIHA);
			pm->_hoops_RAHH |= _hoops_AAHH;
			pm->_hoops_IPII = pm->length;
		} break;

		case _hoops_CRICH: {
			Polymarker const *	pm = (Polymarker const *)pointer;
			return (void *)pm->_hoops_PCHA;
		} break;

		case _hoops_SRICH: {
			Polymarker alter *	pm = (Polymarker alter *)pointer;
			RGB *				vcolors = (RGB *)_hoops_ISPI;
			pm->_hoops_PCHA = vcolors;
		} break;

		case _hoops_GAICH: {
			Polymarker const *	pm = (Polymarker const *)pointer;
			return (void *)pm->_hoops_HCHA;
		} break;

		case _hoops_RAICH: {
			Polymarker alter *	pm = (Polymarker alter *)pointer;
			float *					vfindices = (float *)_hoops_ISPI;
			pm->_hoops_HCHA = vfindices;
		} break;

		case _hoops_AAICH: {
			Polymarker const *	pm = (Polymarker const *)pointer;
			return (void *)pm->_hoops_ICHA;
		} break;

		case _hoops_PAICH: {
			Polymarker alter *	pm = (Polymarker alter *)pointer;
			Vector *				vnormals = (Vector *)_hoops_ISPI;
			pm->_hoops_ICHA = vnormals;
		} break;

		case _hoops_HAICH: {
			Polymarker const *	pm = (Polymarker const *)pointer;
			return (void *)pm->_hoops_CCHA;
		} break;

		case _hoops_IAICH: {
			Polymarker alter *	pm = (Polymarker alter *)pointer;
			_hoops_RSSH *			vparameters = (_hoops_RSSH *)_hoops_ISPI;
			pm->_hoops_CCHA = vparameters;
		} break;

		case _hoops_CAICH: {
			Polymarker const *	pm = (Polymarker const *)pointer;
			return (void *)(POINTER_SIZED_INT)pm->_hoops_GSHA;
		} break;

		case _hoops_SAICH: {
			Polymarker alter *	pm = (Polymarker alter *)pointer;
			pm->_hoops_GSHA = _hoops_ISPI;
		} break;

		case _hoops_GPICH: {
			Polymarker const *	pm = (Polymarker const *)pointer;
			return (void *)(POINTER_SIZED_INT)pm->_hoops_RPRCP;
		} break;

		case _hoops_RPICH: {
			Polymarker alter *	pm = (Polymarker alter *)pointer;
			pm->_hoops_RPRCP = (_hoops_ISPI != 0);
		} break;

		case _hoops_APICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAA];
		} break;

		case _hoops_PPICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_RSHHP];
		} break;

		case _hoops_HPICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_SGIHP];
		} break;

		case _hoops_IPICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_SAA];
		} break;

		case _hoops_CPICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_HRIHP];
		} break;

		case _hoops_SPICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_RPA];
		} break;

		case _hoops_GHICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_IRIHP];
		} break;

		case _hoops_RHICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_APA];
		} break;

		case _hoops_AHICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_CRIHP];
		} break;

		case _hoops_PHICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_PPA];
		} break;

		case _hoops_HHICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_SRIHP];
		} break;

		case _hoops_IHICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_GGIHP];
		} break;

		case _hoops_CHICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_GAIHP];
		} break;

		case _hoops_SHICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_HSHHP];
		} break;

		case _hoops_GIICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_PGIHP];
		} break;

		case _hoops_RIICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_PAIHP];
		} break;

		case _hoops_AIICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_HAA[_hoops_IAIHP];
		} break;

		case _hoops_PIICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks.color;
		} break;

		case _hoops_HIICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_RGP;
		} break;

		case _hoops_IIICH: {
			return (void *)(POINTER_SIZED_INT)nr->_hoops_IRR->locks._hoops_IPPGR;
		} break;



#define _hoops_PIPPI(nr, _hoops_HIPPI, _hoops_IIPPI) \
	_hoops_GHIA (\
		_hoops_GRGH alter &	_hoops_RRGH = *(_hoops_GRGH alter *) \
				HIC_Intermediate_Utility (inr, _hoops_GAGCH, _hoops_ISAPI); \
		if ((_hoops_RRGH->locks._hoops_HAA[_hoops_HIPPI] = (_hoops_IIPPI)) != 0) \
			_hoops_RRGH->locks.color |= (1<<_hoops_HIPPI); \
		else \
			_hoops_RRGH->locks.color &= ~(1<<_hoops_HIPPI);)


		case _hoops_CIICH: {
			_hoops_PIPPI(nr, _hoops_IAA, _hoops_ISPI);
		} break;

		case _hoops_SIICH: {
			_hoops_PIPPI(nr, _hoops_RSHHP, _hoops_ISPI);
		} break;

		case _hoops_GCICH: {
			_hoops_PIPPI(nr, _hoops_SGIHP, _hoops_ISPI);
		} break;

		case _hoops_RCICH: {
			_hoops_PIPPI(nr, _hoops_SAA, _hoops_ISPI);
		} break;

		case _hoops_ACICH: {
			_hoops_PIPPI(nr, _hoops_HRIHP, _hoops_ISPI);
		} break;

		case _hoops_PCICH: {
			_hoops_PIPPI(nr, _hoops_RPA, _hoops_ISPI);
		} break;

		case _hoops_HCICH: {
			_hoops_PIPPI(nr, _hoops_IRIHP, _hoops_ISPI);
		} break;

		case _hoops_ICICH: {
			_hoops_PIPPI(nr, _hoops_APA, _hoops_ISPI);
		} break;

		case _hoops_CCICH: {
			_hoops_PIPPI(nr, _hoops_CRIHP, _hoops_ISPI);
		} break;

		case _hoops_SCICH: {
			_hoops_PIPPI(nr, _hoops_PPA, _hoops_ISPI);
		} break;

		case _hoops_GSICH: {
			_hoops_PIPPI(nr, _hoops_SRIHP, _hoops_ISPI);
		} break;

		case _hoops_RSICH: {
			_hoops_PIPPI(nr, _hoops_GGIHP, _hoops_ISPI);
		} break;

		case _hoops_ASICH: {
			_hoops_PIPPI(nr, _hoops_GAIHP, _hoops_ISPI);
		} break;

		case _hoops_PSICH: {
			_hoops_PIPPI(nr, _hoops_HSHHP, _hoops_ISPI);
		} break;

		case _hoops_HSICH: {
			_hoops_PIPPI(nr, _hoops_PGIHP, _hoops_ISPI);
		} break;

		case _hoops_ISICH: {
			_hoops_PIPPI(nr, _hoops_PAIHP, _hoops_ISPI);
		} break;

		case _hoops_CSICH: {
			_hoops_PIPPI(nr, _hoops_IAIHP, _hoops_ISPI);
		} break;

		case _hoops_SSICH: {
			_hoops_GRGH alter &	_hoops_RRGH = *(_hoops_GRGH alter *)
					HIC_Intermediate_Utility (inr, _hoops_GAGCH, _hoops_ISAPI);

			if ((_hoops_RRGH->locks.color = _hoops_ISPI) != 0) {
				_hoops_RRGH->locks._hoops_IPPGR |= _hoops_GGCAA(HK_COLOR);
				for (int i=0; i<_hoops_IIGRA; i++)
					if (BIT ((int)_hoops_ISPI, 1<<i))
						_hoops_RRGH->locks._hoops_HAA[i] = ~0;
					else
						_hoops_RRGH->locks._hoops_HAA[i] = 0;
			}
			else {
				_hoops_RRGH->locks._hoops_IPPGR &= ~_hoops_GGCAA(HK_COLOR);
				for (int i=0; i<_hoops_IIGRA; i++)
					_hoops_RRGH->locks._hoops_HAA[i] = 0;
			}

		} break;

		case _hoops_GGCCH: {
			_hoops_GRGH alter &	_hoops_RRGH = *(_hoops_GRGH alter *)
					HIC_Intermediate_Utility (inr, _hoops_GAGCH, _hoops_ISAPI);

			if ((_hoops_RRGH->locks._hoops_RGP = _hoops_ISPI) != 0)
				_hoops_RRGH->locks._hoops_IPPGR |= _hoops_GGCAA(HK_VISIBILITY);
			else
				_hoops_RRGH->locks._hoops_IPPGR &= ~_hoops_GGCAA(HK_VISIBILITY);
		} break;

		case _hoops_RGCCH: {
			_hoops_GRGH alter &	_hoops_RRGH = *(_hoops_GRGH alter *)
					HIC_Intermediate_Utility (inr, _hoops_GAGCH, _hoops_ISAPI);

			_hoops_RRGH->locks._hoops_IPPGR = _hoops_ISPI;
		} break;



		case _hoops_PGCCH: {
			Segment_Info alter *		_hoops_CIPPI = (Segment_Info alter *)HI_Clone_Anything(pointer, sizeof(Segment_Info));
			_hoops_CIPPI->next = null;
			_hoops_CIPPI->path.retain();
			return (void *)_hoops_CIPPI;
		} _hoops_HHHI;

		case _hoops_HGCCH: {
			Segment_Info alter *		si = (Segment_Info alter *)pointer;
			si->path.release();
			FREE(si, Segment_Info);
		} break;


		case _hoops_IGCCH: {
			switch (nr->_hoops_IRR->_hoops_SRI) {
				case _hoops_GRAAP:
				case _hoops_ARAAP:
				case _hoops_HSSS:
				case _hoops_PRAAP:
					return (void *)(POINTER_SIZED_INT)true;
			}
			return (void *)(POINTER_SIZED_INT)false;
		} _hoops_HHHI;

		case _hoops_ARCCH: {

			//_hoops_ASIGA _hoops_IPRPI
		} break;

		case _hoops_PRCCH:{
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SRA->options._hoops_SRRRR &&
						nr->_hoops_SRA->_hoops_PGCC._hoops_CHHSR == _hoops_RCPGA);
		} _hoops_HHHI;

		case _hoops_CGCCH: {
			return (void *)(POINTER_SIZED_INT)(nr->_hoops_SRA->_hoops_ACPGR->snapshot ? true : false);
		} _hoops_HHHI;

		case _hoops_GRCCH: {
			Tristrip const *		ts = (Tristrip const *)pointer;
			return (void *)(POINTER_SIZED_INT)((ts->_hoops_GAHA != null) ? true : false);
		} _hoops_HHHI;

		case _hoops_RRCCH: {
			Tristrip alter *		ts = (Tristrip alter *)pointer;
			ts->_hoops_SRHA |= DL_TEXTURE_PREBOUND;
		} break;

		case _hoops_IACCH: {
			return (void *)(BIT(nr->_hoops_SRA->_hoops_PGCC.flags, _hoops_PAGIP));
		} _hoops_HHHI;

		case _hoops_CACCH: {

			_hoops_AIGPR *	_hoops_RIGC;
			_hoops_IIRIR (_hoops_RIGC);

			return (void *)_hoops_RCSSR (_hoops_RIGC, _hoops_ISPI);
		} _hoops_HHHI;

		case _hoops_SACCH: {
			Image const *		image = (Image const *)pointer;
			return (void *)image->_hoops_PHGH;
		} _hoops_HHHI;

		case _hoops_HRCCH: {
			Polyhedron const *phon = (Polyhedron const *)pointer;
			return (void *)(POINTER_SIZED_INT)phon->points;
		} _hoops_HHHI;

		case _hoops_IRCCH: {
			Polyhedron const *phon = (Polyhedron const *)pointer;
			return (void *)(POINTER_SIZED_INT)phon->point_count;
		} _hoops_HHHI;

		case _hoops_CRCCH: {
			Shell const *_hoops_SPHPR = (Shell const *)pointer;
			return (void *)_hoops_SPHPR->face_list;
		} _hoops_HHHI;

		case _hoops_SRCCH: {
			Shell const *_hoops_SPHPR = (Shell const *)pointer;
			return (void *)(POINTER_SIZED_INT)_hoops_SPHPR->face_list_length;
		} _hoops_HHHI;

		case _hoops_RACCH: {
			Shell alter *_hoops_SPHPR = (Shell alter *)pointer;
			HI_Face_List_From_Tristrips(nr->_hoops_SRA->_hoops_RIGC, _hoops_SPHPR);
		} break;

		case _hoops_AACCH: {
			Polyhedron alter *phon = (Polyhedron alter *)pointer;
			HI_Assemble_Face_Normals (phon);
		} break;

		case _hoops_GACCH: {
			Polyhedron const *phon = (Polyhedron const *)pointer;
			return (void *)(POINTER_SIZED_INT)(phon->polyhedron_flags & PHF_FACE_NORMALS_VALID);
		} _hoops_HHHI;

		case _hoops_PACCH: {
			Polyhedron const *phon = (Polyhedron const *)pointer;
			return (void *)(POINTER_SIZED_INT)phon->face_count;
		} _hoops_HHHI;

		case _hoops_GPCCH: {
			Shell alter *		_hoops_SPHPR;

			ZALLOC (_hoops_SPHPR, Shell);
			_hoops_CSAPI (_hoops_SPHPR, _hoops_SCIP);

			_hoops_SPHPR->polyhedron_flags |= PHF_POINTS_BY_REFERENCE;
			_hoops_SPHPR->point_count = _hoops_ISPI;
			_hoops_SPHPR->points = (Point *)pointer;

			_hoops_SPHPR->polyhedron_flags |= PHF_SHELL_FACE_LIST_BY_REFERENCE;
			_hoops_SPHPR->face_list_length = _hoops_SSPI;
			_hoops_SPHPR->face_list = (int *)_hoops_SGHI;
			_hoops_SPHPR->face_count = 0;
			int const *		ptr = _hoops_SPHPR->face_list;
			while (ptr < _hoops_SPHPR->face_list + _hoops_SPHPR->face_list_length) {
				if (*ptr > 0) {
					ptr += 1 + *ptr;
					++_hoops_SPHPR->face_count;
				}
				else
					ptr += 1 - *ptr;
			}

			_hoops_SPHPR->_hoops_SPHA = -1;				/* _hoops_HAR _hoops_AISP _hoops_GAPR */

			if (_hoops_CSPI != 0) {
				_hoops_SPHPR->polyhedron_flags |= PHF_VERTEX_NORMALS_BY_REFERENCE;
				_hoops_SPHPR->polyhedron_flags |= PHF_VERTEX_NORMALS_VALID;
				_hoops_SPHPR->local_vertex_attributes.normals = (Vector *) _hoops_CSPI;
			}

			HI_Initialize_Vertex_Attributes ((Polyhedron *)_hoops_SPHPR, 0, 0);

			_hoops_SPHPR->bounding = Bounding::Create(_hoops_SPHPR->point_count, _hoops_SPHPR->points);

			return _hoops_SPHPR;
		} break;

		case _hoops_RPCCH: {
			Polyhedron alter *	_hoops_SPHPR = (Polyhedron alter *)pointer;

			_hoops_HPRH (_hoops_SPHPR);
		} break;

		default: {
			/* _hoops_SPSIR _hoops_HGCR _hoops_IRS _hoops_SIPPI _hoops_HPGR _hoops_RHGC _hoops_GCPPI */
			return nr->_hoops_SRA->_hoops_ACPGR->_hoops_IGHGR (nr, request, pointer,
															_hoops_ISPI, _hoops_CSPI, _hoops_SSPI, _hoops_SGHI, f1, f2, _hoops_CGHGR, _hoops_SGHGR);
		}	break;
	}

#endif
	return null;
}



HC_EXTERNAL HIC_API void HIC_Finish_Picture (HIC_Rendition const *inr, bool swap_buffers)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, finish_picture)(nr, swap_buffers);
}


HC_EXTERNAL HIC_API void HIC_Draw_Window_Frame (HIC_Rendition const *inr,
	HIC_Int_Rectangle const *extent, HIC_Int_Rectangle *frame, bool calculate_only)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_window_frame)(nr,
		(Int_Rectangle const *)extent,
		(Int_Rectangle *)frame,
		calculate_only);
}


HC_EXTERNAL HIC_API void HIC_Draw_Text (HIC_Rendition const *inr, HIC_Text_Info const *ti)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, _hoops_CSCGA)(nr, (Text_Info const *)ti);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Text (HIC_Rendition const *inr, HIC_DC_Point const *where, int count, HIC_Karacter const *kstring)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_IGCSR const &		_hoops_HRCIR = nr->_hoops_SISI;
	Font_Instance const *		font = _hoops_HRCIR->font;

	if (font == null) do {
		HD_Choose_Font (nr, _hoops_HRCIR->_hoops_HSRIP->_hoops_HGPIR, _hoops_SSAIP, true);

		if ((font = _hoops_HRCIR->font) == null)
			break;
	} while (!HD_Load_Font (nr->_hoops_SRA, font));

	if (font != null)
		_hoops_GACIP (nr, draw_dc_text)(nr, (DC_Point const *)where, count, (Karacter const *)kstring);
}

HC_EXTERNAL HIC_API void HIC_Draw_Simple_Text(HIC_Rendition const *inr, HIC_DC_Point const *where, const char *text)
{
	Net_Rendition	nr = (*(Net_Rendition const *)inr).Copy();
	_hoops_IGCSR	&_hoops_HRCIR = nr->_hoops_SISI.Modify();
	KName			_hoops_SIHSA;
	_hoops_IGPIR		_hoops_RCPPI;

	_hoops_RCPPI.specified.length = 0;
	_hoops_RCPPI.specified.text = 0;
	_hoops_RCPPI.next = null;
	_hoops_RCPPI._hoops_SSSGP = GFN_STROKED;

	_hoops_CAAI (HOOPS_WORLD->_hoops_HPHGI);

	do
	{
		HD_Choose_Font (nr, &_hoops_RCPPI, _hoops_SSAIP, true);

		if (_hoops_HRCIR->font == null)
			break;

	} _hoops_RGGA (HD_Load_Font (nr->_hoops_SRA, _hoops_HRCIR->font));

	if (_hoops_HRCIR->font)
	{
		HI_Convert_Char_To_KName(text, &_hoops_SIHSA, _hoops_SSAIP);
		_hoops_GACIP (nr, _hoops_AGCSR)(nr, null, (DC_Point const*)where, _hoops_SIHSA.length, _hoops_SIHSA._hoops_IPPPP, null);
		_hoops_PRPIR(_hoops_SIHSA);
	}

	_hoops_APAI (HOOPS_WORLD->_hoops_HPHGI);		
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Marker (HIC_Rendition const *inr, HIC_Marker const *marker)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_marker)(nr, (Marker const *)marker);
}



HC_EXTERNAL HIC_API void HIC_Draw_3D_Polyline (HIC_Rendition const *inr, HIC_Polyline const *polyline)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_polyline)(nr, (Polyline const *)polyline);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Infinite_Line (HIC_Rendition const *inr, HIC_Polyline const *polyline)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_infinite_line)(nr, (Polyline const *)polyline);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Polygon (HIC_Rendition const *inr, HIC_Polygon const *polygon)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_polygon)(nr, (Polygon const *)polygon);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Text (HIC_Rendition const *inr, HIC_Text const *text)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_text)(nr, (_hoops_HACC const *)text);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Stenciled_Quad (HIC_Rendition const *inr, HIC_Point const*points, HIC_Stencil_Bitmap const *stencil)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, _hoops_CRCGA)(nr, (Point const*)points, (_hoops_RAARP const *)stencil);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Tristrip (HIC_Rendition const *inr, HIC_Tristrip const *tristrip)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	Tristrip const		*ts = (Tristrip const *)tristrip;

	if (ts->_hoops_HCHA != null)
		_hoops_GACIP (nr, _hoops_ARCI)(nr, ts);
	else
		_hoops_GACIP (nr, draw_3d_tristrip)(nr, ts);

}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Polyhedron (HIC_Rendition const *inr, HIC_Polyhedron const *phon)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_polyhedron)(nr, (Polyhedron const *)phon);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Shell (HIC_Rendition const *inr, HIC_Polyhedron const *phon)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_polyhedron)(nr, (Polyhedron const *)phon);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Mesh (HIC_Rendition const *inr, HIC_Polyhedron const *phon)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_polyhedron)(nr, (Polyhedron const *)phon);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Polyedge (HIC_Rendition const *inr, HIC_Polyedge const *_hoops_RASGR)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	Polyedge const *pe = (Polyedge const *)_hoops_RASGR;

	if ((pe)->_hoops_HCHA != null)
		_hoops_GACIP (nr, _hoops_PPAS)(nr, pe);
	else
		_hoops_GACIP (nr, draw_3d_polyedge)(nr, pe);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Polymarker (HIC_Rendition const *inr, HIC_Polymarker const *pm)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_polymarker)(nr, (Polymarker const *)pm);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Polyedge_From_Tristrip (HIC_Rendition const *inr, HIC_Polyedge const *_hoops_RASGR, HIC_Tristrip const *its)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	Polyedge const *pe = (Polyedge const *)_hoops_RASGR;
	Tristrip const *ts = (Tristrip const *)its;

	_hoops_GACIP (nr, draw_3d_polyedge_from_tristrip)(nr, pe, ts);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Ellipse (HIC_Rendition const *inr, HIC_Ellipse const *ellipse)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_ellipse)(nr, (Ellipse const *)ellipse);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Elliptical_Arc (HIC_Rendition const *inr, HIC_Elliptical_Arc const *arc)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_elliptical_arc)(nr, (Elliptical_Arc const *)arc);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_NURBS_Curve (HIC_Rendition const *inr, HIC_NURBS_Curve const *curve)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_nurbs_curve)(nr, (_hoops_PIRGR const *)curve);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_NURBS_Surface (HIC_Rendition const *inr, HIC_NURBS_Surface const *surface)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_nurbs_surface)(nr, (_hoops_APPGR const *)surface);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Cylinder (HIC_Rendition const *inr, HIC_Cylinder const *cylinder)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_cylinder)(nr, (Cylinder const *)cylinder);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_PolyCylinder (HIC_Rendition const *inr, HIC_Polycylinder const *polycylinder)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_polycylinder)(nr, (PolyCylinder const *)polycylinder);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Sphere (HIC_Rendition const *inr, HIC_Sphere const *sphere)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_sphere)(nr, (Sphere const *)sphere);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Grid (HIC_Rendition const *inr, HIC_Grid const *grid)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_grid)(nr, (Grid const *)grid);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Image (HIC_Rendition const *inr, HIC_Image const *image)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_3d_image)(nr, (Image const *)image);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Triangle (HIC_Rendition const *inr, HIC_DC_Point const *points)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_polytriangle)(nr, 3, (DC_Point const *)points);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Colorized_Triangle (HIC_Rendition const *inr, HIC_DC_Point const *points, HIC_RGBAS32 const *color)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_colorized_polytriangle)(nr, 3, (DC_Point const *)points, (RGBAS32 const *)color, true);
}

HC_EXTERNAL HIC_API void HIC_Draw_DC_Gouraud_Triangle (HIC_Rendition const *inr, HIC_DC_Point const *points, HIC_RGBAS32 const *colors)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_gouraud_polytriangle)(nr, 3, (DC_Point const *)points, (RGBAS32 const *)colors);
}

HC_EXTERNAL HIC_API void HIC_Draw_DC_Reshaded_Triangle (HIC_Rendition const *inr,
	HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes,
	float const *params, int param_width, HIC_Integer32 param_flags)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_textured_polytriangle)(nr, 3,
		(DC_Point const *)points, (RGBA const *)colors, (_hoops_ARPA const *)planes,
		params, param_width, param_flags);
}

HC_EXTERNAL HIC_API void HIC_Draw_DC_Polytriangle (HIC_Rendition const *inr, int count, HIC_DC_Point const *points)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_polytriangle)(nr, count, (DC_Point const *)points);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Colorized_Polytriangle (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, HIC_RGBAS32 const *color, bool single)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_colorized_polytriangle)(nr,
		count, (DC_Point const *)points, (RGBAS32 const *)color, single);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Gouraud_Polytriangle (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, HIC_RGBAS32 const *colors)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_gouraud_polytriangle)(nr,
		count, (DC_Point const *)points, (RGBAS32 const *)colors);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Phong_Polytriangle (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_phong_polytriangle)(nr,
		count, (DC_Point const *)points, (RGBA const *)colors, (_hoops_ARPA const *)planes);
}


/* _hoops_ASIGA _hoops_RRP _hoops_IS _hoops_ACPPI _hoops_CGCI */
HC_EXTERNAL HIC_API void HIC_Draw_DC_Textured_Polytriangle (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes,
	float const *params, int param_width, HIC_Integer32 param_flags)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_textured_polytriangle)(nr, count,
		(DC_Point const *)points, (RGBA const *)colors, (_hoops_ARPA const *)planes,
		params, param_width, param_flags);
}



HC_EXTERNAL HIC_API void HIC_Draw_DC_Line (HIC_Rendition const *inr, HIC_DC_Point const *points)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_polyline)(nr, 2, (DC_Point const *)points);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Colorized_Line (HIC_Rendition const *inr, HIC_DC_Point const *points, HIC_RGBAS32 const *color)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_colorized_polyline)(nr, 2, (DC_Point const *)points, (RGBAS32 const *)color, true);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Gouraud_Line (HIC_Rendition const *inr, HIC_DC_Point const *points, HIC_RGBAS32 const *colors)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_gouraud_polyline)(nr, 2, (DC_Point const *)points, (RGBAS32 const *)colors);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Reshaded_Line (HIC_Rendition const *inr,
	HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes,
	float const *params, int param_width, HIC_Integer32 param_flags)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_textured_polyline)(nr, 2,
		(DC_Point const *)points, (RGBA const *)colors, (_hoops_ARPA const *)planes,
		params, param_width, param_flags);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Polyline (HIC_Rendition const *inr, int count, HIC_DC_Point const *points)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_polyline)(nr, count, (DC_Point const *)points);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Colorized_Polyline (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, HIC_RGBAS32 const *color, bool single)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_colorized_polyline)(nr, count, (DC_Point const *)points, (RGBAS32 const *)color, single);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Gouraud_Polyline (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, HIC_RGBAS32 const *colors)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_gouraud_polyline)(nr, count, (DC_Point const *)points, (RGBAS32 const *)colors);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Phong_Polyline (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_phong_polyline)(nr, count,
		(DC_Point const *)points, (RGBA const *)colors, (_hoops_ARPA const *)planes);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Textured_Polyline (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, HIC_RGBA const *colors, HIC_Plane const *planes,
	float const *params, int param_width, HIC_Integer32 param_flags)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_textured_polyline)(nr, count,
		(DC_Point const *)points, (RGBA const *)colors, (_hoops_ARPA const *)planes,
		params, param_width, param_flags);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Marker (HIC_Rendition const *inr, HIC_DC_Point const *point)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_polymarker)(nr, 1, (DC_Point const *)point, null, null);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Colorized_Marker (HIC_Rendition const *inr, HIC_DC_Point const *point, HIC_RGBAS32 const *color)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_colorized_polymarker)(nr, 1,
		(DC_Point const *)point, (RGBAS32 const *)color,
		true, null, null);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Polymarker (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, float const *rotations, float const *size_fixups)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_polymarker)(nr, count, (DC_Point const *)points, rotations, size_fixups);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Colorized_Polymarker (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, HIC_RGBAS32 const *colors, bool single,
	float const *rotations, float const *size_fixups)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_colorized_polymarker)(nr, count,
		(DC_Point const *)points, (RGBAS32 const *)colors,
		single, rotations, size_fixups);
}



HC_EXTERNAL HIC_API void HIC_Draw_DC_Dot (HIC_Rendition const *inr, HIC_DC_Point const *point)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_polydot)(nr, 1, (DC_Point const *)point);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Polydot (HIC_Rendition const *inr, int count, HIC_DC_Point const *points)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_polydot)(nr, count, (DC_Point const *)points);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Colorized_Polydot (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, HIC_RGBAS32 const *colors, bool single)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_colorized_polydot)(nr, count,
		(DC_Point const *)points, (RGBAS32 const *)colors,
		single);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Polygon (HIC_Rendition const *inr, int count, HIC_DC_Point const *points)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, _hoops_RPCGA)(nr, count, (DC_Point const *)points);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Face (HIC_Rendition const *inr, int count, HIC_DC_Point const *points)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_face)(nr, count, (DC_Point const *)points);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Ellipse (HIC_Rendition const *inr, HIC_DC_Point const *where, HIC_DC_Point const *radius)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_ellipse)(nr, (DC_Point const *)where, (DC_Point const *)radius);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Elliptical_Arc (HIC_Rendition const *inr,
	HIC_DC_Point const *where, HIC_DC_Point const *radius, float start, float end)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, _hoops_CCISR)(nr, (DC_Point const *)where, (DC_Point const *)radius, start, end);
}



HC_EXTERNAL HIC_API void HIC_Draw_DC_Outline_Ellipse (HIC_Rendition const *inr, HIC_DC_Point const *where, HIC_DC_Point const *radius)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, _hoops_SCISR)(nr, (DC_Point const *)where, (DC_Point const *)radius);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Colorized_Face (HIC_Rendition const *inr,
	int count, HIC_DC_Point const *points, HIC_RGBAS32 const *color)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_colorized_face)(nr, count, (DC_Point const *)points, (RGBAS32 const *)color);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Rectangle (HIC_Rendition const *inr, int left, int right, int bottom, int top)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_rectangle)(nr, left, right, bottom, top);
}



/* _hoops_CSPH _hoops_CSCR */

HC_EXTERNAL HIC_API void HIC_Draw_DC_Image (HIC_Rendition const *inr,
	HIC_DC_Point const *start, HIC_DC_Point const *end, int hoffset, HIC_Image_Format format,
	int row_bytes, void const *const *rasters, int pattern,
	HIC_Driver_Color const *contrast_color, HIC_Image const *db_image)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, _hoops_HPCGA)(nr,
		(DC_Point const *)start,
		(DC_Point const *)end, hoffset,
		(Image_Format)format,
		row_bytes, rasters, pattern,
		(Driver_Color const*)contrast_color,
		(Image const*)db_image);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Stenciled_Quad (HIC_Rendition const *inr,
	HIC_DC_Point const *points, HIC_Stencil_Bitmap const *stencil)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, _hoops_SPCGA)(nr, (DC_Point const *)points, (_hoops_RAARP const *)stencil);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Bit_Rasters (HIC_Rendition const *inr,
	HIC_DC_Point const *start, HIC_DC_Point const *end, int rowbytes, unsigned char const *rasters)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, _hoops_CCCGA)(nr, (DC_Point const *)start, (DC_Point const *)end, rowbytes, rasters);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Gray8_Rasters (HIC_Rendition const *inr,
	HIC_DC_Point const *start, HIC_DC_Point const *end, int rowbytes, unsigned char const *rasters)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, _hoops_GSCGA)(nr, (DC_Point const *)start, (DC_Point const *)end, rowbytes, rasters);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Mapped8_Rasters (HIC_Rendition const *inr,
	HIC_DC_Point const *start, HIC_DC_Point const *end, int rowbytes, unsigned char const *rasters)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
		_hoops_GACIP (nr, _hoops_CCCSR)(nr, (DC_Point const *)start, (DC_Point const *)end, rowbytes, rasters);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_Mapped16_Rasters (HIC_Rendition const *inr,
	HIC_DC_Point const *start, HIC_DC_Point const *end, int rowbytes, unsigned short const *rasters)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, _hoops_PSCGA)(nr, (DC_Point const *)start, (DC_Point const *)end, rowbytes, rasters);
}


HC_EXTERNAL HIC_API void HIC_Draw_DC_RGB32_Rasters (HIC_Rendition const *inr,
	HIC_DC_Point const *start, HIC_DC_Point const *end, int rowbytes, HIC_RGBAS32 const *rasters)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_GACIP (nr, draw_dc_rgb32_rasters)(nr, (DC_Point const *)start, (DC_Point const *)end, rowbytes, (RGBAS32 const *)rasters);
}


HC_EXTERNAL HIC_API void * HIC_Begin_Occlusion_Query (HIC_Rendition const *inr, bool disable_write)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	if (nr->_hoops_SRA->_hoops_ACPGR->_hoops_GRSSP)
		return _hoops_GACIP (nr, _hoops_GRSSP)(nr, disable_write);

	return 0;
}

HC_EXTERNAL HIC_API void HIC_End_Occlusion_Query (HIC_Rendition const *inr, void * id)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	if (nr->_hoops_SRA->_hoops_ACPGR->_hoops_RRSSP)
		_hoops_GACIP (nr, _hoops_RRSSP)(nr, id);

}

HC_EXTERNAL HIC_API int HIC_Get_Occlusion_Query (HIC_Rendition const *inr, void * id)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	if (nr->_hoops_SRA->_hoops_ACPGR->_hoops_CRGIP)
		return _hoops_GACIP (nr, _hoops_CRGIP)(nr, id);

	return 0;
}

HC_EXTERNAL HIC_API void HIC_Delete_Occlusion_Query (HIC_Rendition const *inr, void * id)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	if (nr->_hoops_SRA->_hoops_ACPGR->_hoops_ARSSP)
		_hoops_GACIP (nr, _hoops_ARSSP)(nr, id);
}

HC_EXTERNAL HIC_API void HIC_Create_Region(HIC_Rendition const *inr, HIC_Int_Rectangle const *area, void **image_buffer, void **z_buffer){
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	if (nr->_hoops_SRA->_hoops_ACPGR->create_region)
		_hoops_GACIP (nr, create_region)(nr, (Int_Rectangle const *)area, image_buffer, z_buffer);
}
HC_EXTERNAL HIC_API void HIC_Save_Region(HIC_Rendition const *inr, HIC_Int_Rectangle const *area, void *image_buffer, void *z_buffer){
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	if (nr->_hoops_SRA->_hoops_ACPGR->_hoops_HIPGR)
		_hoops_GACIP (nr, _hoops_HIPGR)(nr, (Int_Rectangle const *)area, image_buffer, z_buffer);
}
HC_EXTERNAL HIC_API void HIC_Restore_Region(HIC_Rendition const *inr, HIC_Int_Rectangle const *area, void *image_buffer, void *z_buffer){
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	if (nr->_hoops_SRA->_hoops_ACPGR->_hoops_PIPGR)
		_hoops_GACIP (nr, _hoops_PIPGR)(nr, (Int_Rectangle const *)area, image_buffer, z_buffer);
}
HC_EXTERNAL HIC_API void HIC_Destroy_Region(HIC_Rendition const *inr, void *image_buffer, void *z_buffer){
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	if (nr->_hoops_SRA->_hoops_ACPGR->_hoops_ISPGR)
		_hoops_GACIP (nr, _hoops_ISPGR)(nr, image_buffer, z_buffer);
}

HC_EXTERNAL HIC_API bool HIC_Snapshot(HIC_Rendition const *inr, int width, int height, unsigned char *data){
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	if (nr->_hoops_SRA->_hoops_ACPGR->snapshot)
		return _hoops_GACIP (nr, snapshot)(nr, width, height, data);
	return false;
}





HC_EXTERNAL HIC_API float HIC_Show_Device_Size_X (HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SRA->current.size.x;
}
HC_EXTERNAL HIC_API float HIC_Show_Device_Size_Y (HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SRA->current.size.y;
}
HC_EXTERNAL HIC_API float HIC_Show_Device_Max_Size_X (HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SRA->_hoops_PGCC.size.x;
}
HC_EXTERNAL HIC_API float HIC_Show_Device_Max_Size_Y (HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SRA->_hoops_PGCC.size.y;
}

HC_EXTERNAL HIC_API float HIC_Show_Device_Resolution_X(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SRA->current._hoops_HAP.x;
}

HC_EXTERNAL HIC_API float HIC_Show_Device_Resolution_Y(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SRA->current._hoops_HAP.y;
}

HC_EXTERNAL HIC_API float HIC_Show_Device_Pixel_Aspect_Ratio (HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SRA->current._hoops_AGRS;
}

HC_EXTERNAL HIC_API float HIC_Show_Device_Window_Aspect_Ratio (HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return (nr->_hoops_SRA->current.size.y / nr->_hoops_SRA->current.size.x);
}

HC_EXTERNAL HIC_API float HIC_Show_Marker_Size(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_GSP->ysize;
}


/* _hoops_HCGR */
HC_EXTERNAL HIC_API float HIC_Show_Text_Spacing(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SISI->spacing;
}
HC_EXTERNAL HIC_API float HIC_Show_Text_Font_Size(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SISI->_hoops_PHP;
}
HC_EXTERNAL HIC_API float HIC_Show_Text_Font_Size_Tolerance(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SISI->_hoops_ACPAP;
}
HC_EXTERNAL HIC_API float HIC_Show_Text_Final_Font_Size(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SISI->font->_hoops_ISISR;
}
HC_EXTERNAL HIC_API float HIC_Show_Text_Font_Extra_Space(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SISI->_hoops_PCPAP;
}
HC_EXTERNAL HIC_API float HIC_Show_Text_Font_Rotation(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SISI->rotation;
}
HC_EXTERNAL HIC_API float HIC_Show_Text_Font_Slant(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SISI->_hoops_IPGRP;
}
HC_EXTERNAL HIC_API bool HIC_Show_Text_Is_Outlined(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_SISI->outline;
}
HC_EXTERNAL HIC_API double HIC_Show_Text_Width_Scale(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_SISI->width_scale;
}
HC_EXTERNAL HIC_API const char * HIC_Show_Text_Specified_Text(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_SISI->_hoops_HSRIP->_hoops_HGPIR->specified.text;
}



/* _hoops_RHPP _hoops_PSHA */

HC_EXTERNAL HIC_API float HIC_Show_Window_Contrast_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SAIR->contrast_color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Window_Contrast_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SAIR->contrast_color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Window_Contrast_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SAIR->contrast_color, b, blue);
}

HC_EXTERNAL HIC_API float HIC_Show_Line_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_AHP->color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Line_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_AHP->color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Line_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_AHP->color, b, blue);
}

HC_EXTERNAL HIC_API float HIC_Show_Edge_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_RHP->color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Edge_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_RHP->color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Edge_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_RHP->color, b, blue);
}

HC_EXTERNAL HIC_API float HIC_Show_Line_Contrast_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_AHP->contrast_color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Line_Contrast_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_AHP->contrast_color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Line_Contrast_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_AHP->contrast_color, b, blue);
}
HC_EXTERNAL HIC_API float HIC_Show_Edge_Contrast_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_RHP->contrast_color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Edge_Contrast_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_RHP->contrast_color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Edge_Contrast_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_RHP->contrast_color, b, blue);
}

HC_EXTERNAL HIC_API float HIC_Show_Face_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_IHA->color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_IHA->color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_IHA->color, b, blue);
}

HC_EXTERNAL HIC_API float HIC_Show_Face_Back_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_IHA->_hoops_RGIR, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Back_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_IHA->_hoops_RGIR, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Back_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_IHA->_hoops_RGIR, b, blue);
}

HC_EXTERNAL HIC_API float HIC_Show_Face_Contrast_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_IHA->contrast_color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Contrast_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_IHA->contrast_color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Contrast_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_IHA->contrast_color, b, blue);
}


HC_EXTERNAL HIC_API float HIC_Show_Marker_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_GSP->color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Marker_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_GSP->color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Marker_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_GSP->color, b, blue);
}
HC_EXTERNAL HIC_API float HIC_Show_Marker_Contrast_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_GSP->contrast_color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Marker_Contrast_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_GSP->contrast_color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Marker_Contrast_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_GSP->contrast_color, b, blue);
}

HC_EXTERNAL HIC_API float HIC_Show_Vertex_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SCP->color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Vertex_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SCP->color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Vertex_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SCP->color, b, blue);
}
HC_EXTERNAL HIC_API float HIC_Show_Vertex_Contrast_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SCP->contrast_color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Vertex_Contrast_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SCP->contrast_color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Vertex_Contrast_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SCP->contrast_color, b, blue);
}
HC_EXTERNAL HIC_API float HIC_Show_Text_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SISI->color, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Text_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SISI->color, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Text_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SISI->color, b, blue);
}

HC_EXTERNAL HIC_API float HIC_Show_Window_Color_Red (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SAIR->_hoops_GPIR, r, red);
}
HC_EXTERNAL HIC_API float HIC_Show_Window_Color_Green (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SAIR->_hoops_GPIR, g, green);
}
HC_EXTERNAL HIC_API float HIC_Show_Window_Color_Blue (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return _hoops_HCHIP (nr, _hoops_SAIR->_hoops_GPIR, b, blue);
}


HC_EXTERNAL HIC_API float HIC_Show_Camera_Field_Width (HIC_Rendition const *inr) {
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->transform_rendition->_hoops_SPH->_hoops_ISPA;
}
HC_EXTERNAL HIC_API float HIC_Show_Camera_Field_Height (HIC_Rendition const *inr){
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->transform_rendition->_hoops_SPH->_hoops_SSPA;
}
HC_EXTERNAL HIC_API float HIC_Show_Camera_Oblique_X (HIC_Rendition const *inr){
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->transform_rendition->_hoops_SPH->_hoops_HHCH;
}
HC_EXTERNAL HIC_API float HIC_Show_Camera_Oblique_Y (HIC_Rendition const *inr){
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->transform_rendition->_hoops_SPH->_hoops_IHCH;
}

HC_EXTERNAL HIC_API float HIC_Show_Camera_Eye_Distance (HIC_Rendition const *inr){
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->transform_rendition->_hoops_SPH->_hoops_SRIR;
}


HC_EXTERNAL HIC_API float HIC_Show_Current_Z_Max (HIC_Rendition const *inr){
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->transform_rendition->_hoops_PCHH;
}

HC_EXTERNAL HIC_API float HIC_Show_Face_Displacement(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->transform_rendition->_hoops_CHIH;
}

HC_EXTERNAL HIC_API float HIC_Show_General_Displacement(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->transform_rendition->_hoops_SHIH;
}


HC_EXTERNAL HIC_API float HIC_Show_Selection_Proximity_Sq(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SRA->_hoops_APHHP->_hoops_GICAH;
}


HC_EXTERNAL HIC_API unsigned char HIC_Show_Face_DirectRGB_Red(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_IHA->color._hoops_HRIR.r;
}
HC_EXTERNAL HIC_API unsigned char HIC_Show_Face_DirectRGB_Green(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_IHA->color._hoops_HRIR.g;
}
HC_EXTERNAL HIC_API unsigned char HIC_Show_Face_DirectRGB_Blue(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_IHA->color._hoops_HRIR.b;
}
HC_EXTERNAL HIC_API unsigned char HIC_Show_Face_DirectRGB_Alpha(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_IHA->color._hoops_HRIR.a;
}

HC_EXTERNAL HIC_API bool HIC_Has_Face_Material(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_IHA->_hoops_CHA != null;
}
HC_EXTERNAL HIC_API bool HIC_Face_Mat_Has_Enviro_Txr(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_IHA->_hoops_CHA->texture[_hoops_RIA] != null;
}

HC_EXTERNAL HIC_API float HIC_Show_Face_Mat_Mirror_Txr_R(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_IHA->_hoops_CHA->color[_hoops_ACA].red;
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Mat_Mirror_Txr_G(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_IHA->_hoops_CHA->color[_hoops_ACA].green;
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Mat_Mirror_Txr_B(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_IHA->_hoops_CHA->color[_hoops_ACA].blue;
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Mat_Opacity(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_IHA->_hoops_CHA->_hoops_IRIR;
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Mat_Trans_R(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_IHA->_hoops_CHA->color[_hoops_PCA].red;
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Mat_Trans_G(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_IHA->_hoops_CHA->color[_hoops_PCA].green;
}
HC_EXTERNAL HIC_API float HIC_Show_Face_Mat_Trans_B(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_IHA->_hoops_CHA->color[_hoops_PCA].blue;
}


HC_EXTERNAL HIC_API float HIC_Show_Current_Arc_Start(HIC_Rendition const *nr)
{
	float					_hoops_HAGR;
	Net_Rendition const &	_hoops_PCPPI = *(Net_Rendition const *)nr;
	switch (_hoops_PCPPI->_hoops_SRA->_hoops_RAI->type) {
		case _hoops_RIIP: {
			Circular_Arc const *_hoops_PRIAA = (Circular_Arc const *)_hoops_PCPPI->_hoops_SRA->_hoops_RAI;
			_hoops_HAGR = _hoops_PRIAA->arc_start;
			break;
		}
		case _hoops_GIIP:	{
			Elliptical_Arc const *_hoops_ACAIP = (Elliptical_Arc const *)_hoops_PCPPI->_hoops_SRA->_hoops_RAI;
			_hoops_HAGR = _hoops_ACAIP->arc_start;
			break;
		}
		default:
			_hoops_HAGR = 0;
	}
	return _hoops_HAGR;
}
HC_EXTERNAL HIC_API float HIC_Show_Current_Arc_End(HIC_Rendition const *nr)
{
	float					_hoops_HAGR;
	Net_Rendition const &	_hoops_PCPPI = *(Net_Rendition const *)nr;
	switch (_hoops_PCPPI->_hoops_SRA->_hoops_RAI->type) {
		case _hoops_RIIP: {
			Circular_Arc const *	_hoops_PRIAA = (Circular_Arc const *)_hoops_PCPPI->_hoops_SRA->_hoops_RAI;
			_hoops_HAGR = _hoops_PRIAA->_hoops_PHHI;
			break;
		}
		case _hoops_GIIP:	{
			Elliptical_Arc const *	_hoops_ACAIP = (Elliptical_Arc const *)_hoops_PCPPI->_hoops_SRA->_hoops_RAI;
			_hoops_HAGR = _hoops_ACAIP->_hoops_PHHI;
			break;
		}
		default:
			_hoops_HAGR = 0;
	}
	return _hoops_HAGR;
}

HC_EXTERNAL HIC_API int HIC_Show_Diffuse_Textures_Name_Length(HIC_Rendition const *inr, const int layer)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_HIR const * _hoops_HCPPI = nr->_hoops_IHA->_hoops_CHA->_hoops_SCA;
	while (_hoops_HCPPI != null) {
		if (_hoops_HCPPI->_hoops_HGA == layer)
			return _hoops_HCPPI->name.length;
		_hoops_HCPPI = _hoops_HCPPI->next;
	}
	return 0;
}
HC_EXTERNAL HIC_API const char * HIC_Show_Diffuse_Textures_Name_Text(HIC_Rendition const *inr, const int layer)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_HIR const * _hoops_HCPPI = nr->_hoops_IHA->_hoops_CHA->_hoops_SCA;
	while (_hoops_HCPPI != null) {
		if (_hoops_HCPPI->_hoops_HGA == layer)
			return _hoops_HCPPI->name.text;
		_hoops_HCPPI = _hoops_HCPPI->next;
	}
	return 0;
}
HC_EXTERNAL HIC_API int HIC_Show_Diffuse_Texture_Source_Name_Length(HIC_Rendition const *inr, const int layer)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_HIR const * _hoops_HCPPI = nr->_hoops_IHA->_hoops_CHA->_hoops_SCA;
	while (_hoops_HCPPI != null) {
		if (_hoops_HCPPI->_hoops_HGA == layer)
			return _hoops_HCPPI->texture->name.length;
		_hoops_HCPPI = _hoops_HCPPI->next;
	}
	return 0;
}
HC_EXTERNAL HIC_API const char * HIC_Show_Diffuse_Texture_Source_Name_Text(HIC_Rendition const *inr, const int layer)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_HIR const * _hoops_HCPPI = nr->_hoops_IHA->_hoops_CHA->_hoops_SCA;
	while (_hoops_HCPPI != null) {
		if (_hoops_HCPPI->_hoops_HGA == layer)
			return _hoops_HCPPI->texture->name.text;
		_hoops_HCPPI = _hoops_HCPPI->next;
	}
	return 0;
}


HC_EXTERNAL HIC_API bool HIC_Face_Mat_Has_Diffuse_Txr(HIC_Rendition const *inr, const int layer)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	_hoops_HIR const * _hoops_HCPPI = nr->_hoops_IHA->_hoops_CHA->_hoops_SCA;
	while (_hoops_HCPPI != null) {
		if (_hoops_HCPPI->_hoops_HGA == layer)
			return 1;
		_hoops_HCPPI = _hoops_HCPPI->next;
	}
	return 0;
}


HC_EXTERNAL HIC_API void HIC_Face_Mat_Set_Diffuse_Txr_Tint(HIC_Rendition const *inr, HIC_RGB const *rgb)
{
	_hoops_CIGA alter &	_hoops_SIGA = *(_hoops_CIGA alter *)
		HIC_Intermediate_Utility (inr, _hoops_CRGCH, _hoops_ISAPI);

	_hoops_SIGA->_hoops_CHA->_hoops_SCA->flags |= _hoops_PRA|_hoops_PPIR;
	_hoops_SIGA->_hoops_CHA->_hoops_CSHR.red = rgb->red;
	_hoops_SIGA->_hoops_CHA->_hoops_CSHR.green = rgb->green;
	_hoops_SIGA->_hoops_CHA->_hoops_CSHR.blue = rgb->blue;
}



HC_EXTERNAL HIC_API float HIC_Show_Face_Opacity(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_IHA->_hoops_CHA->_hoops_IRIR;
}

HC_EXTERNAL HIC_API bool HIC_Show_Mirroring(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return BIT(nr->_hoops_SRA->flags, _hoops_CHSHP);
}

HC_EXTERNAL HIC_API unsigned char HIC_Unpack_RGBAS32_Red(HIC_RGBAS32 _hoops_ICPPI)
{
	RGBAS32 const *rgbas32 = (RGBAS32 const *)&_hoops_ICPPI;
	return rgbas32->r;
}
HC_EXTERNAL HIC_API unsigned char HIC_Unpack_RGBAS32_Green(HIC_RGBAS32 _hoops_ICPPI)
{
	RGBAS32 const *rgbas32 = (RGBAS32 const *)&_hoops_ICPPI;
	return rgbas32->g;
}
HC_EXTERNAL HIC_API unsigned char HIC_Unpack_RGBAS32_Blue(HIC_RGBAS32 _hoops_ICPPI)
{
	RGBAS32 const *rgbas32 = (RGBAS32 const *)&_hoops_ICPPI;
	return rgbas32->b;
}
HC_EXTERNAL HIC_API unsigned char HIC_Unpack_RGBAS32_Alpha(HIC_RGBAS32 _hoops_ICPPI)
{
	RGBAS32 const *rgbas32 = (RGBAS32 const *)&_hoops_ICPPI;
	return rgbas32->a;
}

HC_EXTERNAL HIC_API void HIC_Set_Cylinder_Radius(HIC_Geometry const *_hoops_HASGR, float radius)
{
	Cylinder alter * cylinder = (Cylinder alter *)_hoops_HASGR;
	cylinder->radius = radius;
}

HC_EXTERNAL HIC_API void HIC_Set_Cylinder_Basis_Axis0(HIC_Geometry const *geo, HIC_Vector const *v)
{
	Cylinder alter * cylinder = (Cylinder alter *)geo;
	cylinder->_hoops_CSPIR.axis[0] = Vector(v->x, v->y, v->z);
}

HC_EXTERNAL HIC_API void HIC_Set_Cylinder_Basis_Axis1(HIC_Geometry const *geo, HIC_Vector const *v)
{
	Cylinder alter * cylinder = (Cylinder alter *)geo;
	cylinder->_hoops_CSPIR.axis[1] = Vector(v->x, v->y, v->z);
}

HC_EXTERNAL HIC_API void HIC_Set_Cylinder_Axis0(HIC_Geometry const *geo, HIC_Point const *p)
{
	Cylinder alter * cylinder = (Cylinder alter *)geo;
	cylinder->axis[0] = Point(p->x, p->y, p->z);
}

HC_EXTERNAL HIC_API void HIC_Set_Cylinder_Axis1(HIC_Geometry const *geo, HIC_Point const *p)
{
	Cylinder alter * cylinder = (Cylinder alter *)geo;
	cylinder->axis[1] = Point(p->x, p->y, p->z);
}

HC_EXTERNAL HIC_API float HIC_Show_Cylinder_Radius(HIC_Geometry const *_hoops_HASGR)
{
	Cylinder const * cylinder = (Cylinder const *)_hoops_HASGR;
	return cylinder->radius;
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Cylinder_Basis_Axis0(HIC_Geometry const *geo)
{
	Cylinder alter * cylinder = (Cylinder alter *)geo;
	return (HIC_Vector const *)&cylinder->_hoops_CSPIR.axis[0];
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Cylinder_Basis_Axis1(HIC_Geometry const *geo)
{
	Cylinder alter * cylinder = (Cylinder alter *)geo;
	return (HIC_Vector const *)&cylinder->_hoops_CSPIR.axis[1];
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Cylinder_Axis0(HIC_Geometry const *geo)
{
	Cylinder alter * cylinder = (Cylinder alter *)geo;
	return (HIC_Point const *)&cylinder->axis[0];
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Cylinder_Axis1(HIC_Geometry const *geo)
{
	Cylinder alter * cylinder = (Cylinder alter *)geo;
	return (HIC_Point const *)&cylinder->axis[1];
}

HC_EXTERNAL HIC_API void HIC_Set_PolyCylinder_Basis_Axis0(HIC_Geometry const *geo, int basis_index, HIC_Vector const *v)
{
	PolyCylinder alter * polycylinder = (PolyCylinder alter *)geo;
	polycylinder->_hoops_CSPIR[basis_index].axis[0] = Vector(v->x, v->y, v->z);
	if (polycylinder->_hoops_SGHIR != null)
		polycylinder->_hoops_SGHIR->_hoops_GSAI = DL_FLAG_INVALID;
	if (polycylinder->_hoops_GRHIR != null)
		polycylinder->_hoops_GRHIR->_hoops_GSAI = DL_FLAG_INVALID;
}

HC_EXTERNAL HIC_API void HIC_Set_PolyCylinder_Basis_Axis1(HIC_Geometry const *geo, int basis_index, HIC_Vector const *v)
{
	PolyCylinder alter * polycylinder = (PolyCylinder alter *)geo;
	polycylinder->_hoops_CSPIR[basis_index].axis[1] = Vector(v->x, v->y, v->z);
	if (polycylinder->_hoops_SGHIR != null)
		polycylinder->_hoops_SGHIR->_hoops_GSAI = DL_FLAG_INVALID;
	if (polycylinder->_hoops_GRHIR != null)
		polycylinder->_hoops_GRHIR->_hoops_GSAI = DL_FLAG_INVALID;
}

HC_EXTERNAL HIC_API void HIC_Set_PolyCyliner_Points(HIC_Geometry const *geo, int index, HIC_Point const *p)
{
	PolyCylinder alter * polycylinder = (PolyCylinder alter *)geo;
	polycylinder->points[index] = Point(p->x, p->y, p->z);
	if (polycylinder->_hoops_SGHIR != null)
		polycylinder->_hoops_SGHIR->_hoops_GSAI = DL_FLAG_INVALID;
	if (polycylinder->_hoops_GRHIR != null)
		polycylinder->_hoops_GRHIR->_hoops_GSAI = DL_FLAG_INVALID;
}

HC_EXTERNAL HIC_API void HIC_Set_PolyCylinder_Radii(HIC_Geometry const *geo, int index, float r)
{
	PolyCylinder alter * polycylinder = (PolyCylinder alter *)geo;
	polycylinder->radii[index] = r;
	if (polycylinder->_hoops_SGHIR != null)
		polycylinder->_hoops_SGHIR->_hoops_GSAI = DL_FLAG_INVALID;
	if (polycylinder->_hoops_GRHIR != null)
		polycylinder->_hoops_GRHIR->_hoops_GSAI = DL_FLAG_INVALID;
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_PolyCylinder_Basis_Axis0(HIC_Geometry const *geo, int basis_index)
{
	PolyCylinder alter * polycylinder = (PolyCylinder alter *)geo;
	return (HIC_Vector const *)&polycylinder->_hoops_CSPIR[basis_index].axis[0];
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_PolyCylinder_Basis_Axis1(HIC_Geometry const *geo, int basis_index)
{
	PolyCylinder alter * polycylinder = (PolyCylinder alter *)geo;
	return (HIC_Vector const *)&polycylinder->_hoops_CSPIR[basis_index].axis[1];
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_PolyCylinder_Points(HIC_Geometry const *geo, int index)
{
	PolyCylinder alter * polycylinder = (PolyCylinder alter *)geo;
	return (HIC_Point const *)&polycylinder->points[index];
}

HC_EXTERNAL HIC_API float HIC_Show_PolyCylinder_Radii(HIC_Geometry const *geo, int index)
{
	PolyCylinder alter * polycylinder = (PolyCylinder alter *)geo;
	return polycylinder->radii[index];
}

HC_EXTERNAL HIC_API int HIC_Show_PolyCylinder_Point_Count(HIC_Geometry const *geo)
{
	PolyCylinder alter * polycylinder = (PolyCylinder alter *)geo;
	return polycylinder->point_count;
}

HC_EXTERNAL HIC_API void HIC_Set_Sphere_Radius(HIC_Geometry const *geo, float radius)
{
	Sphere alter * sphere = (Sphere alter *)geo;
	sphere->data.radius = radius;
}

HC_EXTERNAL HIC_API float HIC_Show_Sphere_Radius(HIC_Geometry const *geo)
{
	Sphere alter * sphere = (Sphere alter *)geo;
	return sphere->data.radius;
}

HC_EXTERNAL HIC_API bool HIC_Using_Analytic_HSRA(HIC_Rendition const *nr)
{
	return(HIC_Intermediate_Utility (nr, _hoops_IGCCH, _hoops_ISAPI)?true:false);
}

HC_EXTERNAL HIC_API bool HIC_Tristrip_Has_DL(HIC_Tristrip const *ts)
{
	return(HIC_Intermediate_Utility (0, _hoops_GRCCH, (void *)ts, IM_NO_VALUES)?true:false);
}

HC_EXTERNAL HIC_API void HIC_Tristrip_Mark_Texture_Prebound(HIC_Tristrip const *ts)
{
	(void)HIC_Intermediate_Utility (0, _hoops_RRCCH, (void *)ts, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Get_Bounding_Cuboid(HIC_Segment_Info const *si, HIC_Bounding_Cuboid *bounding)
{
	(void)HIC_Intermediate_Utility (0, _hoops_ARCCH, (void *)si, _hoops_RSAPI((HC_POINTER_SIZED_INT)bounding));
}

HC_EXTERNAL HIC_API bool HIC_Using_Double_Buffer_Swap(HIC_Rendition const *nr)
{
	return(HIC_Intermediate_Utility (nr, _hoops_PRCCH, _hoops_ISAPI)?true:false);
}


HC_EXTERNAL HIC_API int HIC_Get_Polyhedron_Point_Count(HIC_Polyhedron const *phon)
{
	return(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_IRCCH, (void *)phon, IM_NO_VALUES);
}



HC_EXTERNAL HIC_API HIC_Point const * HIC_Get_Polyhedron_Points(HIC_Polyhedron const *phon)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_HRCCH, (void *)phon, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API int * HIC_Get_Polyhedron_Shell_Face_List(HIC_Polyhedron const *phon)
{
	return (int *)HIC_Intermediate_Utility (0, _hoops_CRCCH, (void *)phon, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Get_Polyhedron_Shell_Face_List_Length(HIC_Polyhedron const *phon)
{
	return(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_SRCCH, (void *)phon, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API void HIC_Polyhedron_Generate_Face_List(HIC_Polyhedron const *phon)
{
	(void)HIC_Intermediate_Utility (0, _hoops_RACCH, (void *)phon, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API bool HIC_Polyhedron_Face_Normals_Valid(HIC_Polyhedron const *phon)
{
	return(HIC_Intermediate_Utility (0, _hoops_GACCH, (void *)phon, IM_NO_VALUES)?true:false);
}


HC_EXTERNAL HIC_API void HIC_Polyhedron_Assemble_Face_Normals(HIC_Polyhedron const *phon)
{
	(void)HIC_Intermediate_Utility (0, _hoops_AACCH, (void *)phon, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API int HIC_Get_Polyhedron_Face_Count(HIC_Polyhedron const *phon)
{
	return(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_PACCH, (void *)phon, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API void* HIC_Get_Image_Block(HIC_Image const *image)
{
	return HIC_Intermediate_Utility (0, _hoops_SACCH, (void *)image, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API HIC_Geometry const * HIC_Key_To_Geometry_Pointer(HIC_Rendition const *nr, HC_KEY key)
{
	return	(HIC_Geometry const *)HIC_Intermediate_Utility (nr, _hoops_CACCH, 0, _hoops_RSAPI(key));
}


HC_EXTERNAL HIC_API HIC_Segment_Info const * HIC_Copy_Segment_Info(HIC_Segment_Info const *si)
{
	return (HIC_Segment_Info const *)HIC_Intermediate_Utility (0, _hoops_PGCCH, (void *)si, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API void HIC_Free_Segment_Info(HIC_Segment_Info const *si)
{
	(void)HIC_Intermediate_Utility (0, _hoops_HGCCH, (void *)si, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API HIC_RGBAS32 HIC_Pack_RGBAS32(int r, int g, int b, int a)
{
	return (HIC_RGBAS32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_HACCH, 0, (r), (g), (b), (a), _hoops_GSAPI);
}


HC_EXTERNAL HIC_API HIC_Text_Info const * HIC_New_Text_Info(HIC_Text_Info const *text_info)
{
	return (HIC_Text_Info const *)HIC_Intermediate_Utility (0, _hoops_GGRCH, (void *)text_info, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API void HIC_Free_Text_Info(HIC_Text_Info const *text_info)
{
	(void)HIC_Intermediate_Utility (0, _hoops_RGRCH, (void *)text_info, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API void HIC_Draw_3D_Geometry(HIC_Rendition const *nr, HIC_Geometry const  *geo)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GPGCH, (void *)geo, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API void HIC_Exit_Update(HIC_Rendition const *nr)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PRRCH, _hoops_ISAPI);
}


HC_EXTERNAL HIC_API void HIC_Abort_Update(HIC_Rendition const *nr)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PIGCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API void HIC_Abort_Selection(HIC_Rendition const *nr)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CPRCH, _hoops_ISAPI);
}


HC_EXTERNAL HIC_API void HIC_Draw_Window(HIC_Rendition const *nr, HIC_Int_Rectangle const *extent)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HRRCH, (void *)extent, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API void HIC_Clear_Z_Buffer(HIC_Rendition const *nr)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SPRCH, _hoops_ISAPI);
}

/*  _hoops_CCPPI
_hoops_SCPPI _hoops_GSPPI _hoops_SRPC _hoops_RSPPI(_hoops_ASPPI _hoops_RCIC *_hoops_SCII, _hoops_PSPPI &_hoops_HSPPI, _hoops_SCSH _hoops_ISPPI, _hoops_SCSH  _hoops_CSPPI, _hoops_SSPPI _hoops_GGHPI, _hoops_SCSH _hoops_RGHPI, _hoops_RCIC _hoops_SRPC *_hoops_AGHPI)
{
	(_hoops_SRPC) _hoops_PGHPI (_hoops_SCII, _hoops_HGHPI, (_hoops_SRPC *)_hoops_AGHPI, _hoops_ISPPI, _hoops_CSPPI, _hoops_GGHPI, _hoops_RGHPI, (_hoops_HSPPI)->_hoops_SISR, (_hoops_HSPPI)->_hoops_HAPC, (_hoops_HSPPI)->_hoops_SSH, 0);
}

*/



HC_EXTERNAL HIC_API bool HIC_Occlusion_Query_Available(HIC_Rendition const *nr)
{
	return (HIC_Intermediate_Utility (nr, _hoops_GHRCH, _hoops_ISAPI)?true:false);
}

HC_EXTERNAL HIC_API bool HIC_Can_Save_And_Restore_Regions(HIC_Rendition const *nr)
{
	return (HIC_Intermediate_Utility (nr, _hoops_IACCH, _hoops_ISAPI)?true:false);
}


HC_EXTERNAL HIC_API bool HIC_Can_Snapshot(HIC_Rendition const *nr)
{
	return (HIC_Intermediate_Utility (nr, _hoops_CGCCH, _hoops_ISAPI)?true:false);
}


HC_EXTERNAL HIC_API HIC_Stencil_Bitmap const * HIC_New_Stencil_Bitmap(HIC_Rendition const *nr, int nw, int nh, int  bpr, int bpp, unsigned char *bm)
{
	return(HIC_Stencil_Bitmap const *)HIC_Intermediate_Utility (nr, _hoops_GRRCH, (void *)bm, nw, nh, bpr, bpp, _hoops_GSAPI);
}


HC_EXTERNAL HIC_API void HIC_Free_Stencil_Bitmap(HIC_Rendition const *nr, HIC_Stencil_Bitmap const *stencil)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RRRCH, (void *)stencil, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API void HIC_Draw_Segment(HIC_Rendition const *in_nr, HIC_Segment_Info const *_hoops_IGHPI)
{
	Net_Rendition const &		nr = *(Net_Rendition const *)in_nr;
	Segment_Info const *		si = (Segment_Info const *)_hoops_IGHPI;
	Display_Context alter *		dc = (Display_Context alter *)nr->_hoops_SRA;

#ifndef DISABLE_PARTIAL_ERASE
	if (dc->_hoops_CPIGA)
		HD_Draw_Partial_Erase_Tree (nr, si->segment, si->path, si->_hoops_IHICP);
	else
#endif
	if (dc->_hoops_APHHP != null)
		HD_Selection_Walk_Tree (nr, si->segment, si->path);
	else
		HD_Standard_Draw_Tree (nr, si->segment, si->path);

	dc->flags |= _hoops_HHICP;
}

HC_EXTERNAL HIC_API HC_KEY HIC_Show_Segment_Key(HIC_Segment_Info const *_hoops_IGHPI)
{
	Segment_Info const *	si = (Segment_Info const *)_hoops_IGHPI;
	return (HC_KEY)(si->segment->key);
}


HC_EXTERNAL HIC_API HC_KEY HIC_Show_Original_Segment_Key(HIC_Segment_Info const *_hoops_IGHPI)
{
	Segment_Info const *	si = (Segment_Info const *)_hoops_IGHPI;
	return (HC_KEY)_hoops_AIRIR (si->segment);
}

HC_EXTERNAL HIC_API HC_KEY HIC_Show_Driver_Segment_Key(HIC_Rendition const *nr)
{
	return (HC_KEY) HIC_Intermediate_Utility (nr, _hoops_RHRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HC_KEY HIC_Show_Original_Driver_Segment_Key(HIC_Rendition const *nr)
{
	return (HC_KEY) HIC_Intermediate_Utility (nr, _hoops_AHRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API char const * HIC_Show_Device_Type(HIC_Rendition const *nr)
{
	return (char const *) HIC_Intermediate_Utility (nr, _hoops_PHRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API char const * HIC_Show_Actor_Name(HIC_Rendition const *inr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)inr;
	return nr->_hoops_SRA->_hoops_PCRSR;
}


HC_EXTERNAL HIC_API char const * HIC_Show_Device_Driver(HIC_Rendition const *nr)
{
	return(char const *) HIC_Intermediate_Utility (nr, _hoops_HHRCH, _hoops_ISAPI);
}


HC_EXTERNAL HIC_API bool HIC_Show_Device_Windowing_System(HIC_Rendition const *nr)
{
	return	(HIC_Intermediate_Utility (nr, _hoops_IHRCH, _hoops_ISAPI)?true:false);
}

HC_EXTERNAL HIC_API bool HIC_Show_Device_Locater(HIC_Rendition const *nr)
{
	return(HIC_Intermediate_Utility (nr, _hoops_CHRCH, _hoops_ISAPI)?true:false);
}


HC_EXTERNAL HIC_API int HIC_Show_Device_Locater_Button_Count(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT) HIC_Intermediate_Utility (nr, _hoops_SHRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API char const * HIC_Show_Device_Locater_Type(HIC_Rendition const *nr)
{
	return (char const *)HIC_Intermediate_Utility (nr, _hoops_GIRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int HIC_Show_Device_Plane_Count(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_ARGCH, _hoops_ISAPI);
}


HC_EXTERNAL HIC_API int HIC_Show_Device_Colors(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT) HIC_Intermediate_Utility (nr, _hoops_RIRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32  HIC_Show_Device_Max_Colors(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT) HIC_Intermediate_Utility (nr, _hoops_AIRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int  HIC_Show_Device_Pixels_X(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_PIRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int  HIC_Show_Device_Pixels_Y(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_HIRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int  HIC_Show_Device_Max_Pixels_X(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_IIRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int  HIC_Show_Device_Max_Pixels_Y(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_CIRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HC_POINTER_SIZED_INT HIC_Show_Device_Window_ID(HIC_Rendition const *nr)
{
	return (HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_SIRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HC_POINTER_SIZED_INT HIC_Show_Device_Window_ID2(HIC_Rendition const *nr)
{
	return (HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_GCRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API long HIC_Show_Device_Colormap_ID(HIC_Rendition const *nr)
{
	return (long)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_RCRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int HIC_Show_Device_Z_Buffer_Depth(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_ACRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API bool HIC_Show_Device_Hardware_Lights(HIC_Rendition const *nr)
{
	return (HIC_Intermediate_Utility (nr, _hoops_PCRCH, _hoops_ISAPI)?true:false);
}


HC_EXTERNAL HIC_API bool HIC_Show_Device_Gouraud_Shading(HIC_Rendition const *nr)
{
	return (HIC_Intermediate_Utility (nr, _hoops_HCRCH, _hoops_ISAPI)?true:false);
}

HC_EXTERNAL HIC_API bool HIC_Show_Device_Phong_Shading(HIC_Rendition const *nr)
{
	return (HIC_Intermediate_Utility (nr, _hoops_ICRCH, _hoops_ISAPI)?true:false);
}

HC_EXTERNAL HIC_API char HIC_Show_Line_Pattern(HIC_Rendition const *nr)
{
	return (char)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_CCRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API const char * HIC_Show_Line_Style(HIC_Rendition const *nr)
{
	return (const char *)HIC_Intermediate_Utility (nr, _hoops_SCRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int HIC_Show_Line_Weight(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_GSRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Line_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_RSRCH, _hoops_ISAPI);
}
HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Line_Contrast_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_ASRCH, _hoops_ISAPI);
}
HC_EXTERNAL HIC_API int HIC_Show_Polygon_Visibility(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_SGACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  char HIC_Show_Edge_Pattern(HIC_Rendition const *nr)
{
	return (char)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_GRACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API const char * HIC_Show_Edge_Style(HIC_Rendition const *nr)
{
	return (const char *)HIC_Intermediate_Utility (nr, _hoops_RRACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int HIC_Show_Edge_Weight(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_ARACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Edge_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_PSRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Edge_Contrast_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_HSRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API char  HIC_Show_Face_Pattern(HIC_Rendition const *nr)
{
	return (char)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_PRACH, _hoops_ISAPI);
}
HC_EXTERNAL HIC_API HIC_RGB const * HIC_Show_Face_Material_Diffuse_Color(HIC_Rendition const *nr)
{
	return (HIC_RGB const *)HIC_Intermediate_Utility (nr, _hoops_AGCCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Face_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_ISRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Face_Back_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_SSRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Face_Contrast_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_CSRCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API char HIC_Show_Marker_Symbol(HIC_Rendition const *nr)
{
	return (char)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_HRACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API const char * HIC_Show_Marker_Name(HIC_Rendition const *nr)
{
	return (const char *)HIC_Intermediate_Utility (nr, _hoops_IRACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32  HIC_Show_Internal_Marker_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_GGACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Marker_Contrast_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_RGACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Vertex_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_AGACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Vertex_Contrast_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_PGACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int HIC_Show_Text_Alignment(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_CRACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Text_Path(HIC_Rendition const *nr)
{
	return (HIC_Vector const *)HIC_Intermediate_Utility (nr, _hoops_SRACH, _hoops_ISAPI);
}
HC_EXTERNAL HIC_API HIC_Size_Units HIC_Show_Text_Font_Size_Units(HIC_Rendition const *nr)
{
	return(HIC_Size_Units)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_GAACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Size_Units HIC_Show_Text_Font_Size_Tol_Units(HIC_Rendition const *nr)
{
	return (HIC_Size_Units)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_RAACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Size_Units HIC_Show_Text_Font_Extra_Space_Units(HIC_Rendition const *nr)
{
	return (HIC_Size_Units)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_AAACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API void * HIC_Show_Text_Font_ID(HIC_Rendition const *nr)
{
	return (void *)HIC_Intermediate_Utility (nr, _hoops_PAACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API const char * HIC_Show_Text_Font_Name(HIC_Rendition const *nr)
{
	return (const char *)HIC_Intermediate_Utility (nr, _hoops_HAACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int HIC_Show_Text_Font_Transform(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_IAACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int HIC_Show_Text_Font_Index(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_IAACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Text_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_HGACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Karacter const * HIC_Show_Text_String(HIC_Text_Info const *ti)
{
	return (HIC_Karacter const *)HIC_Intermediate_Utility (0, _hoops_HPACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Show_Text_Length(HIC_Text_Info const *ti)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_IPACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Show_Text_Char_Encoding(HIC_Text_Info const *ti)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_CPACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Show_Text_Line_Count(HIC_Text_Info const *ti)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_SPACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Show_Text_Line_Index(HIC_Text_Info const *ti)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_GHACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int const * HIC_Show_Text_Counts(HIC_Text_Info const *ti)
{
	return (int const *)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_RHACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Text_Position(HIC_Text_Info const *ti)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_AHACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Text_Reference(HIC_Text_Info const *ti)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_PHACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_3D_Text_Position(HIC_Text const *t)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_HHACH, (void *)t, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Text_Baseline(HIC_Text_Info const *ti)
{
	return (HIC_Vector const *)HIC_Intermediate_Utility (0, _hoops_IHACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Text_Longest_Baseline(HIC_Text_Info const *ti)
{
	return (HIC_Vector const *)HIC_Intermediate_Utility (0, _hoops_CHACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Text_Char_Horizontal(HIC_Text_Info const *ti)
{
	return (HIC_Vector const *)HIC_Intermediate_Utility (0, _hoops_SHACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Text_Char_Vertical(HIC_Text_Info const *ti)
{
	return (HIC_Vector const *)HIC_Intermediate_Utility (0, _hoops_GIACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Text_Next_Line(HIC_Text_Info const *ti)
{
	return (HIC_Vector const *)HIC_Intermediate_Utility (0, _hoops_RIACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Text_Char_Position(HIC_Rendition const *nr, HIC_Text_Info const *ti, int index)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (nr, _hoops_HAGCH, (void *)ti,  _hoops_RSAPI(index));
}

HC_EXTERNAL HIC_API float HIC_Show_Text_Char_Width(HIC_Rendition const *nr, HIC_Text_Info const *ti, int index)
{
	return *((float const *)HIC_Intermediate_Utility (nr, _hoops_CAGCH, (void *)ti,  _hoops_RSAPI(index)));
}

HC_EXTERNAL HIC_API int const * HIC_Show_Text_KIndex(HIC_Rendition const *nr, HIC_Text_Info const *ti)
{
	return (int const *)HIC_Intermediate_Utility (nr, _hoops_SAACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Text_Karacter_Info const * HIC_Show_Text_KInfo(HIC_Rendition const *nr, HIC_Text_Info const *ti)
{
	return (HIC_Text_Karacter_Info const *)HIC_Intermediate_Utility (nr, _hoops_GPACH, (void *)ti, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Text_Karacter_Info const * HIC_Show_Text_KInfo_At_Index(HIC_Rendition const *nr, HIC_Text_Info const *ti, int index)
{
	return (HIC_Text_Karacter_Info const *)HIC_Intermediate_Utility (nr, _hoops_RPACH, (void *)ti, _hoops_RSAPI(index));
}

HC_EXTERNAL HIC_API HIC_Rendition const * HIC_Show_KInfo_Net_Rendition(HIC_Text_Karacter_Info const *iki)
{
	_hoops_PGCSR const * ki = (_hoops_PGCSR const *)iki;
	return (HIC_Rendition const*)&ki->nr;
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_KInfo_Position(HIC_Text_Karacter_Info const *ki)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_APACH, (void *)ki, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_KInfo_Point(HIC_Text_Karacter_Info const *ki)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_PPACH, (void *)ki, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API float HIC_Show_KInfo_Width(HIC_Text_Karacter_Info const *iki)
{
	_hoops_PGCSR const * ki = (_hoops_PGCSR const *)iki;
	return ki->width;
}

HC_EXTERNAL HIC_API float HIC_Show_KInfo_Height(HIC_Text_Karacter_Info const *iki)
{
	_hoops_PGCSR const * ki = (_hoops_PGCSR const *)iki;
	return ki->height;
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Compute_Transformed_Text_Position(HIC_Rendition const *nr, HIC_Text_Info const *ti, HIC_DC_Point *pt)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (nr, _hoops_IAGCH, (void *)ti, _hoops_SCAPI, (pt)->x, (pt)->y, (pt)->z, 0);
}

HC_EXTERNAL HIC_API void * HIC_Show_User_Index(HIC_Rendition const *in_nr, int index)
{
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;
	return HD_Show_User_Index(nr, index);
}

HC_EXTERNAL HIC_API void * HIC_Set_User_Index(HIC_Rendition const *in_nr, int index, const void *value)
{
	Net_Rendition & nr = *(Net_Rendition *)in_nr;

	Display_Context const *	dc = nr->_hoops_SRA;

	_hoops_HPPIR *	_hoops_RASGH;
	ZALLOC (_hoops_RASGH, _hoops_HPPIR);
	_hoops_RASGH->type = HK_USER_OPTIONS;
	_hoops_RASGH->_hoops_AGGSA = POOL_NEW(HOOPS_WORLD->memory_pool, _hoops_PGGSA)(HOOPS_WORLD->memory_pool, 2);
	_hoops_RASGH->_hoops_AGGSA->InsertItem(index, (void *)value);

	_hoops_CIGIP alter &	_hoops_SIGIP = nr->_hoops_GCGIP.Modify();

	if(!_hoops_SIGIP->_hoops_IGGSA)
		_hoops_SIGIP->_hoops_IGGSA = POOL_NEW(dc->memory_pool, _hoops_CGGSA)(dc->memory_pool);

	_hoops_PRRH(_hoops_RASGH);
	_hoops_SIGIP->_hoops_IGGSA->AddFirst(_hoops_RASGH);

	return null;
}

HC_EXTERNAL HIC_API void * HIC_Show_User_Option_By_Index(HIC_Rendition const *nr, int index)
{
	return (void *)HIC_Show_User_Index (nr, index);
}

HC_EXTERNAL HIC_API void * HIC_Set_User_Option_By_Index(HIC_Rendition const *nr, int index, const char *value)
{
	return (void *)HIC_Set_User_Index (nr, index, value);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Camera_Position(HIC_Rendition const *nr)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (nr, _hoops_AIACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Camera_Target(HIC_Rendition const *nr)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (nr, _hoops_PIACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Camera_Up_Vector(HIC_Rendition const *nr)
{
	return (HIC_Vector const *)HIC_Intermediate_Utility (nr, _hoops_HIACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int HIC_Show_Camera_Projection(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_IIACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API bool HIC_Show_Z_Buffering(HIC_Rendition const *nr)
{
	return (HIC_Intermediate_Utility (nr, _hoops_CIACH, _hoops_ISAPI)?true:false);
}

HC_EXTERNAL HIC_API HIC_Int_Rectangle const * HIC_Show_Window_Extent(HIC_Rendition const *nr)
{
	return (HIC_Int_Rectangle const *)HIC_Intermediate_Utility (nr, _hoops_SIACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Int_Rectangle const * HIC_Show_Clipping(HIC_Rendition const *nr)
{
	return (HIC_Int_Rectangle const *)HIC_Intermediate_Utility (nr, _hoops_GCACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Int_Rectangle const * HIC_Show_Full_Hard_Clip(HIC_Rendition const *nr)
{
	return (HIC_Int_Rectangle const *)HIC_Intermediate_Utility (nr, _hoops_SGCCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API bool HIC_Show_Hidden_Surfaces(HIC_Rendition const *nr)
{
	return (HIC_Intermediate_Utility (nr, _hoops_RCACH, _hoops_ISAPI)?true:false);
}

HC_EXTERNAL HIC_API int HIC_Show_Visibility(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_ACACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Window_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_IGACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HC_KEY HIC_Show_Geometry_Key(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	if (!_hoops_PCPPI->_hoops_SRA->_hoops_RAI)
		return _hoops_SHSSR;
	return _hoops_PCPPI->_hoops_SRA->_hoops_RAI->key;
}

HC_EXTERNAL HIC_API HC_KEY HIC_Show_Original_Geometry_Key(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	if (!_hoops_PCPPI->_hoops_SRA->_hoops_RAI)
		return _hoops_SHSSR;
	return _hoops_AIRIR (_hoops_PCPPI->_hoops_SRA->_hoops_RAI);
}

HC_EXTERNAL HIC_API HIC_Geometry_Type HIC_Show_Geometry_Type(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	if (!_hoops_PCPPI->_hoops_SRA->_hoops_RAI)
		return (HIC_Geometry_Type)(POINTER_SIZED_INT)HIC_Geometry_Type_BAD_TYPE;
	return (HIC_Geometry_Type)(POINTER_SIZED_INT)_hoops_PCPPI->_hoops_SRA->_hoops_RAI->type;
}

HC_EXTERNAL HIC_API bool HIC_Partial_Erasing(HIC_Rendition const *nr)
{
	return (HIC_Intermediate_Utility (nr, _hoops_GSACH, _hoops_ISAPI)?true:false);
}

HC_EXTERNAL HIC_API HC_KEY HIC_Show_Geometry_Owner(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;

	if (!_hoops_PCPPI->_hoops_SRA->_hoops_RAI)
		return (HC_KEY)_hoops_SHSSR;

	_hoops_AIGPR *	_hoops_RIGC;
	_hoops_IIRIR (_hoops_RIGC);

	return (HC_KEY) HI_Show_Owner_Key_By_Key(_hoops_RIGC, _hoops_PCPPI->_hoops_SRA->_hoops_RAI->key, true, false);
}

HC_EXTERNAL HIC_API HIC_Segment const * HIC_Get_Geometry_Owner(HIC_Geometry const *geo)
{
	Geometry const *			_hoops_CGHPI= (Geometry const *)geo;
	return (HIC_Segment const *)_hoops_CGHPI->owner;
}

HC_EXTERNAL HIC_API HC_KEY HIC_Get_Geometry_Key(HIC_Geometry const *geo)
{
	Geometry const *	_hoops_CGHPI = (Geometry const *)geo;
	return (HC_KEY)_hoops_CGHPI->key;
}

HC_EXTERNAL HIC_API void const * HIC_Show_Callback_Data(HIC_Rendition const *nr)
{
	return (void const *)HIC_Intermediate_Utility (nr, _hoops_RSACH, _hoops_ISAPI);
}
HC_EXTERNAL HIC_API HIC_Segment_Path const *  HIC_Show_Segment_Path(HIC_Rendition const *nr)
{
	return (HIC_Segment_Path const *)HIC_Intermediate_Utility (nr, _hoops_CSGCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API void HIC_Free_Segment_Path(HIC_Segment_Path const *sp)
{
	(void)HIC_Intermediate_Utility (0, _hoops_SSGCH, (void *)sp, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Rendition const * HIC_New_Rendition(HIC_Rendition const *in_nr)
{
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;
	Net_Rendition *			_hoops_RHICP = new Net_Rendition (nr);
	(*_hoops_RHICP).Modify();
	return (HIC_Rendition const *) _hoops_RHICP;
}

HC_EXTERNAL HIC_API void HIC_Free_Rendition(HIC_Rendition const *in_nr)
{
	Net_Rendition const * _hoops_SGHPI = (Net_Rendition const *)in_nr;
	delete _hoops_SGHPI;
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Internal_Window_Contrast_Color(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_CGACH, _hoops_ISAPI);
}

HC_EXTERNAL char HIC_API HIC_Show_Window_Pattern(HIC_Rendition const *nr)
{
	return (char)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_PCACH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Geometry const * HIC_Show_Geometry(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return (HIC_Geometry const *)_hoops_PCPPI->_hoops_SRA->_hoops_RAI;
}

HC_EXTERNAL HIC_API void HIC_Set_Line_Equal_Edge_Rendition(HIC_Rendition const *nr)
{
	Net_Rendition &_hoops_PCPPI = *(Net_Rendition *)nr;
	_hoops_PCPPI.Modify()->_hoops_AHP = _hoops_PCPPI->_hoops_RHP;
}
HC_EXTERNAL HIC_API void HIC_Set_Line_Weight(HIC_Rendition const *nr, int nweight)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ASACH, 0, _hoops_RSAPI(nweight));
}
HC_EXTERNAL HIC_API void HIC_Set_Variable_Line_Weight(HIC_Rendition const *nr, HIC_Size_Units nunit, float nweight)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PSACH, 0, nunit, 0, 0, 0, nweight, 0, 0, 0);
}
HC_EXTERNAL HIC_API void HIC_Set_Line_Pattern(HIC_Rendition const *nr, int npattern)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HSGCH, 0, _hoops_RSAPI(npattern));
}

HC_EXTERNAL HIC_API void HIC_Set_Line_Style(HIC_Rendition const *nr, const char *nname)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ISGCH, (void *)nname, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Line_Style *  HIC_New_User_Line_Pattern(HIC_Rendition const *nr, long nlen, void *npat)
{
	return (HIC_Line_Style *) HIC_Intermediate_Utility (nr, _hoops_SIGCH, (void *)npat,  _hoops_RSAPI(nlen));
}

HC_EXTERNAL HIC_API HIC_Line_Style * HIC_New_User_Line_Pattern2(HIC_Rendition const *nr, long nlen, void *npat, long abs)
{
	return (HIC_Line_Style *) HIC_Intermediate_Utility (nr, _hoops_CCGCH, (void *)npat, nlen, abs, 0, 0, _hoops_GSAPI);
}

HC_EXTERNAL HIC_API void HIC_Set_Line_Color(HIC_Rendition const *nr, HIC_RGB const  *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_IRRCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Line_Contrast_Color(HIC_Rendition const *nr, HIC_RGB const  *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CRRCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Free_User_Line_Pattern(HIC_Line_Style const *upat)
{
	(void)HIC_Intermediate_Utility (0, _hoops_GCGCH, (void *)upat, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API void HIC_Set_User_Line_Pattern(HIC_Rendition const *nr, HIC_Line_Style const *upat)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HSACH, (void *)upat, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void  HIC_Set_Internal_Line_Color(HIC_Rendition const *nr, HIC_RGBAS32 internal)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ISACH, 0,  _hoops_RSAPI(internal));
}

HC_EXTERNAL HIC_API void  HIC_Set_Edge_Weight(HIC_Rendition const *nr, int nweight)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CSACH, 0, _hoops_RSAPI(nweight));
}

HC_EXTERNAL HIC_API void  HIC_Set_Variable_Edge_Weight(HIC_Rendition const *nr, HIC_Size_Units nunits, float nweight)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SSACH, 0, nunits, 0, 0, 0, nweight, 0, 0, 0);
}

HC_EXTERNAL HIC_API void  HIC_Set_Edge_Pattern(HIC_Rendition const *nr, char npattern)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_AGRCH, 0, _hoops_RSAPI(npattern));
}

HC_EXTERNAL HIC_API void HIC_Set_Edge_Style(HIC_Rendition const *nr, char const *nname)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PGRCH, (void *)nname, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_User_Edge_Pattern(HIC_Rendition const *nr, HIC_User_Line_Pattern const *upat)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GGPCH, (void *)upat, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Edge_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SRRCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Edge_Contrast_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GARCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Cut_Edge_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RARCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Internal_Edge_Color(HIC_Rendition const *nr, HIC_RGBAS32 internal)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RGPCH, 0, _hoops_RSAPI(internal));
}

HC_EXTERNAL HIC_API void HIC_Set_Face_Pattern(HIC_Rendition const *nr, int npattern)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_AGPCH, 0, _hoops_RSAPI(npattern));
}

HC_EXTERNAL HIC_API void HIC_Set_Window_Pattern(HIC_Rendition const *nr, int npattern)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PGPCH, 0, _hoops_RSAPI(npattern));
}
HC_EXTERNAL HIC_API HIC_User_Face_Pattern const * HIC_New_User_Face_Pattern(HIC_Rendition const *nr, int nrows, int ncols, unsigned char *npat, int const nsee)
{
	return (HIC_User_Face_Pattern const *)HIC_Intermediate_Utility (nr, _hoops_HIGCH, (void *)npat, nrows, ncols, nsee, 0, _hoops_GSAPI);
}

HC_EXTERNAL HIC_API void HIC_Free_User_Face_Pattern(HIC_User_Face_Pattern const *upat)
{
	(void)HIC_Intermediate_Utility (0, _hoops_IIGCH, (void *)upat, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_User_Face_Pattern(HIC_Rendition const *nr, HIC_User_Face_Pattern const *upat)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HGPCH, (void *)upat, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_User_Window_Pattern(HIC_Rendition const *nr, HIC_User_Face_Pattern const *upat)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_IGPCH, (void *)upat, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Face_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_AARCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Face_Mirror_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PARCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Simple_Reflection_Face_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HARCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Cut_Face_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_IARCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Internal_Face_Color(HIC_Rendition const *nr, HIC_RGBAS32 internal)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CGPCH, 0, _hoops_RSAPI(internal));
}

HC_EXTERNAL HIC_API void HIC_Set_Face_Back_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CARCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Internal_Face_Back_Color(HIC_Rendition const *nr, HIC_RGBAS32 internal)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SGPCH, 0,  _hoops_RSAPI(internal));
}

HC_EXTERNAL HIC_API void HIC_Set_Face_Contrast_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SARCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Internal_Face_Contrast_Color(HIC_Rendition const *nr, HIC_RGBAS32 internal)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GRPCH, 0, _hoops_RSAPI(internal));
}

HC_EXTERNAL HIC_API void HIC_Set_Face_Transmission_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RRPCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Marker_Symbol(HIC_Rendition const *nr, HIC_RGBAS32 nsymbol)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GSGCH, 0, _hoops_RSAPI(nsymbol));
}

HC_EXTERNAL HIC_API void HIC_Set_Marker_Name(HIC_Rendition const *nr, const char *nname)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RSGCH, (void *)nname, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Vertex_Symbol(HIC_Rendition const *nr, HIC_RGBAS32 nsymbol)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ASGCH, 0, _hoops_RSAPI(nsymbol));
}

HC_EXTERNAL HIC_API void HIC_Set_Vertex_Name(HIC_Rendition const *nr, const char *nname)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PSGCH, (void *)nname, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API void HIC_Set_Marker_Size(HIC_Rendition const *nr, float nsize)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ARPCH, 0, _hoops_PSAPI(nsize));
}

HC_EXTERNAL HIC_API void HIC_Set_Variable_Marker_Size(HIC_Rendition const *nr, HIC_Size_Units nunits, float nsize)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PRPCH, 0, nunits, 0, 0, 0, nsize, 0, 0, 0);
}


HC_EXTERNAL HIC_API void HIC_Set_Vertex_Size(HIC_Rendition const *nr, float nsize)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HRPCH, 0, _hoops_PSAPI(nsize));
}

HC_EXTERNAL HIC_API void HIC_Set_Variable_Vertex_Size(HIC_Rendition const *nr, HIC_Size_Units nunits, float nsize)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_IRPCH, 0, nunits, 0, 0, 0, nsize, 0, 0, 0);
}


HC_EXTERNAL HIC_API void HIC_Set_Marker_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GPRCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Marker_Contrast_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RPRCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Internal_Marker_Color(HIC_Rendition const *nr, HIC_RGBAS32 internal)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CRPCH, 0, _hoops_RSAPI(internal));
}

HC_EXTERNAL HIC_API void HIC_Set_Vertex_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_APRCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Vertex_Contrast_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PPRCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Internal_Vertex_Color(HIC_Rendition const *nr, HIC_RGBAS32 internal)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SRPCH, 0, _hoops_RSAPI(internal));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Transform(HIC_Rendition const *nr, HIC_Integer32 xfrm)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GAPCH, 0,  _hoops_RSAPI(xfrm));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Size(HIC_Rendition const *nr, HIC_Parameter sz)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RAPCH, 0, _hoops_PSAPI(sz));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Size_Units(HIC_Rendition const *nr, HIC_Integer32 unts)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_AAPCH, 0,  _hoops_RSAPI(unts));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Size_Tolerance(HIC_Rendition const *nr, HIC_Parameter sz)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PAPCH, 0, _hoops_PSAPI(sz));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Size_Tolerance_Units(HIC_Rendition const *nr, HIC_Integer32 unts)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HAPCH, 0,  _hoops_RSAPI(unts));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Extra_Space(HIC_Rendition const *nr, HIC_Parameter  spc)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_IAPCH, 0, _hoops_PSAPI(spc));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Extra_Space_Units(HIC_Rendition const *nr, HIC_Integer32 unts)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CAPCH, 0, _hoops_RSAPI(unts));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Alignment(HIC_Rendition const *nr, HIC_Integer32 ali)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SAPCH, 0, _hoops_RSAPI(ali));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Spacing(HIC_Rendition const *nr, HIC_Parameter spc)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GPPCH, 0, _hoops_PSAPI(spc));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Path(HIC_Rendition const *nr, float px, float py, float pz)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RPPCH, 0, _hoops_SCAPI, px, py, pz, 0);
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Rotation(HIC_Rendition const *nr, HIC_Parameter rot)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_APPCH, 0, _hoops_PSAPI(rot));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Rotation_Follow_Path(HIC_Rendition const *nr)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PPPCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Width_Scale(HIC_Rendition const *nr, HIC_Parameter ws)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HPPCH, 0, _hoops_PSAPI(ws));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Slant(HIC_Rendition const *nr, HIC_Parameter sl)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_IPPCH, 0, _hoops_PSAPI(sl));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HPRCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Contrast_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_IPRCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Internal_Text_Color(HIC_Rendition const *nr, long internal)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CPPCH, 0, _hoops_RSAPI(internal));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Position(HIC_Text_Info const *iti, HIC_Point const *p)
{
	(void)HIC_Intermediate_Utility (0, _hoops_SPPCH, (void *)iti, _hoops_SCAPI, (p)->x, (p)->y, (p)->z, 0);
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Reference(HIC_Text_Info const *iti, HIC_Point const *p)
{
	(void)HIC_Intermediate_Utility (0, _hoops_GHPCH, (void *)iti, _hoops_SCAPI, (p)->x, (p)->y, (p)->z, 0);
}

HC_EXTERNAL HIC_API void HIC_Set_3D_Text_Position(HIC_Text const *t, HIC_Point const *p)
{
	(void)HIC_Intermediate_Utility (0, _hoops_RHPCH, (void *)t, _hoops_SCAPI, (p)->x, (p)->y, (p)->z, 0);
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Font_Index(HIC_Rendition const *nr, int index)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_AHPCH, 0,  _hoops_RSAPI(index));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_KIndex(HIC_Rendition const *nr, HIC_Text_Info const *iti, int const *index)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PHPCH, (void *)iti, _hoops_RSAPI((POINTER_SIZED_INT)index));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_KInfo(HIC_Rendition const *nr, HIC_Text_Info const *iti, HIC_Text_Karacter_Info const *info)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HHPCH, (void *)iti, _hoops_RSAPI((POINTER_SIZED_INT)info));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Line_Index(HIC_Text_Info const *iti, int index)
{
	(void)HIC_Intermediate_Utility (0, _hoops_IHPCH, (void *)iti, _hoops_RSAPI(index));
}

HC_EXTERNAL HIC_API void HIC_Set_Text_String(HIC_Text_Info const *iti, HIC_Karacter const *txt)
{
	Text_Info *ti = (Text_Info *)iti;
	ti->_hoops_SIHSA._hoops_IPPPP = (Karacter *)txt;
}

HC_EXTERNAL HIC_API void HIC_Set_Text_Length(HIC_Text_Info const *iti, int len)
{
	Text_Info *ti = (Text_Info *)iti;
	ti->_hoops_SIHSA.length = (_hoops_GPAGI)len;
}

HC_EXTERNAL HIC_API void HIC_Set_KInfo_Position(HIC_Text_Karacter_Info const *info, HIC_Point const *p)
{
	(void)HIC_Intermediate_Utility (0, _hoops_CHPCH, (void *)info, _hoops_SCAPI, (p)->x, (p)->y, (p)->z, 0);
}

HC_EXTERNAL HIC_API void HIC_Set_KInfo_Point(HIC_Text_Karacter_Info const *info, HIC_Point const *p)
{
	(void)HIC_Intermediate_Utility (0, _hoops_SHPCH, (void *)info, _hoops_SCAPI, (p)->x, (p)->y, (p)->z, 0);
}

HC_EXTERNAL HIC_API void HIC_Set_KInfo_String_Width(HIC_Text_Karacter_Info const *info, float width)
{
	(void)HIC_Intermediate_Utility (0, _hoops_GIPCH, (void *)info, _hoops_PSAPI(width));
}

HC_EXTERNAL HIC_API void HIC_Set_KInfo_String_Height(HIC_Text_Karacter_Info const *info, float height)
{
	(void)HIC_Intermediate_Utility (0, _hoops_RIPCH, (void *)info, _hoops_PSAPI(height));
}

HC_EXTERNAL HIC_API void HIC_Set_KInfo_String_X(HIC_Text_Karacter_Info const *info, float x)
{
	(void)HIC_Intermediate_Utility (0, _hoops_AIPCH, (void *)info, _hoops_PSAPI(x));
}

HC_EXTERNAL HIC_API void HIC_Set_KInfo_String_Y(HIC_Text_Karacter_Info const *info, float y)
{
	(void)HIC_Intermediate_Utility (0, _hoops_PIPCH, (void *)info, _hoops_PSAPI(y));
}

HC_EXTERNAL HIC_API void HIC_Set_KInfo_Screen_Width(HIC_Text_Karacter_Info const *info, float width)
{
	(void)HIC_Intermediate_Utility (0, _hoops_HIPCH, (void *)info, _hoops_PSAPI(width));
}

HC_EXTERNAL HIC_API void HIC_Set_KInfo_Screen_Height(HIC_Text_Karacter_Info const *info, float height)
{
	(void)HIC_Intermediate_Utility (0, _hoops_IIPCH, (void *)info, _hoops_PSAPI(height));
}

HC_EXTERNAL HIC_API void HIC_Set_KInfo_Screen_X(HIC_Text_Karacter_Info const *info, float x)
{
	(void)HIC_Intermediate_Utility (0, _hoops_CIPCH, (void *)info, _hoops_PSAPI(x));
}

HC_EXTERNAL HIC_API void HIC_Set_KInfo_Screen_Y(HIC_Text_Karacter_Info const *info, float y)
{
	(void)HIC_Intermediate_Utility (0, _hoops_SIPCH, (void *)info, _hoops_PSAPI(y));
}

HC_EXTERNAL HIC_API void HIC_Set_KInfo_Flags(HIC_Text_Karacter_Info const *info, HIC_KInfo_Flags flags)
{
	(void)HIC_Intermediate_Utility (0, _hoops_GCPCH, (void *)info, _hoops_RSAPI(flags));
}

HC_EXTERNAL HIC_API void HIC_Set_Window_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RCPCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Internal_Window_Color(HIC_Rendition const *nr, long internal)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ACPCH, 0, _hoops_RSAPI(internal));
}

HC_EXTERNAL HIC_API void HIC_Set_Window_Contrast_Color(HIC_Rendition const *nr, HIC_RGB const *rgb)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PCPCH, (void *)rgb, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Internal_Window_Contrast_Color(HIC_Rendition const *nr, long internal)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HCPCH, 0,  _hoops_RSAPI(internal));
}

HC_EXTERNAL HIC_API void HIC_Set_Color_Map_Start(HIC_Rendition const *nr, long strt)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ICPCH, 0, _hoops_RSAPI(strt));
}

HC_EXTERNAL HIC_API void HIC_Set_Z_Range(HIC_Rendition const *nr, float _near_, float _far_)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SCGCH, 0, _hoops_SCAPI, _near_, _far_, 0, 0);
}

HC_EXTERNAL HIC_API void HIC_Set_Face_Displacement(HIC_Rendition const *nr, float displacement)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CCPCH, 0, _hoops_PSAPI(displacement));
}

HC_EXTERNAL HIC_API void HIC_Set_General_Displacement(HIC_Rendition const *nr, float displacement)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SCPCH, 0, _hoops_PSAPI(displacement));
}

HC_EXTERNAL HIC_API void  HIC_Set_Clipping(HIC_Rendition const *nr, long nleft, long nright, long nbottom, long ntop)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GSPCH, 0, nleft, nright, nbottom, ntop, _hoops_GSAPI);
}

HC_EXTERNAL HIC_API void  HIC_Restrict_Clipping(HIC_Rendition const *nr, long nleft, long nright, long nbottom, long ntop)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RSPCH, 0, nleft, nright, nbottom, ntop, _hoops_GSAPI);
}

HC_EXTERNAL HIC_API void  HIC_UnSet_Clipping_Not_Needed(HIC_Rendition const *nr)
{
	_hoops_HHCR alter &	_hoops_IHCR = *(_hoops_HHCR alter *)
				HIC_Intermediate_Utility (nr, _hoops_PRGCH, _hoops_ISAPI);
	_hoops_IHCR->flags &= ~_hoops_AIHS;
}

HC_EXTERNAL HIC_API HIC_Convex_Clip_Region const * HIC_New_Convex_Clip_Region(HIC_Rendition const *nr, long ncnt, HIC_DC_Point const *npts)
{
	return (HIC_Convex_Clip_Region const *) HIC_Intermediate_Utility (nr, _hoops_RCGCH, (void *)npts, _hoops_RSAPI(ncnt));
}

HC_EXTERNAL HIC_API void  HIC_Free_Convex_Clip_Region(HIC_Convex_Clip_Region const *ccr)
{
	(void) HIC_Intermediate_Utility (0, _hoops_ACGCH, (void *)ccr, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void  HIC_Set_Convex_Clip_Region(HIC_Rendition const *nr, HIC_Convex_Clip_Region const *ccr)
{
	(void) HIC_Intermediate_Utility (nr, _hoops_ASPCH, (void *)ccr, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void  HIC_Add_Cutting_Plane(HIC_Rendition const *nr, HIC_Plane const *pln)
{
	(void) HIC_Intermediate_Utility (nr, _hoops_HCGCH, (void *)pln, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void  HIC_Remove_Cutting_Planes(HIC_Rendition const *nr)
{
	(void) HIC_Intermediate_Utility (nr, _hoops_ICGCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API void  HIC_Clear_Cutting_Planes(HIC_Rendition const *nr)
{
	(void) HIC_Intermediate_Utility (nr, _hoops_ICGCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API void  HIC_Set_Modelling_Matrix(HIC_Rendition const *in_nr, float const *fp)
{
	Net_Rendition alter &		nr = *(Net_Rendition alter *)in_nr;
	_hoops_HHCR alter &	_hoops_IHCR = nr->transform_rendition.Modify();
	_hoops_HRPA					_hoops_GRHPI;
	_hoops_HRPA					_hoops_RHSPR;

	if (!HI_Figure_General_Modelling_Mtx (fp, &_hoops_GRHPI))
		return;

	_hoops_IHCR->matrix.Modify();
	HI_Multiply_Matrices (&_hoops_GRHPI, &_hoops_IHCR->_hoops_SPH->_hoops_GRCC, &_hoops_RHSPR);
	HD_Redo_Screen (nr, &_hoops_RHSPR);

	HI_Copy_Matrix (&_hoops_GRHPI, &_hoops_IHCR->_hoops_IPH.Modify()->data);
}

HC_EXTERNAL HIC_API void  HIC_Set_Visibility(HIC_Rendition const *nr, long vis)
{
	(void) HIC_Intermediate_Utility (nr, _hoops_PSPCH, 0,  _hoops_RSAPI(vis));
}

HC_EXTERNAL HIC_API void  HIC_Disable_Shadows(HIC_Rendition const *nr)
{
	(void) HIC_Intermediate_Utility (nr, _hoops_PSPCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API void  HIC_Enable_Shadows(HIC_Rendition const *nr)
{
	(void) HIC_Intermediate_Utility (nr, _hoops_PSPCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Marker const * HIC_New_Marker(HIC_Point const *point)
{
	return (HIC_Marker const *) HIC_Intermediate_Utility (0, _hoops_IPGCH, (void *)point, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Marker_Position(HIC_Marker const *marker)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_HSPCH, (void *)marker, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Show_Marker_X_Size(HIC_Rendition const *in_nr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)in_nr;
	return nr->_hoops_GSP->_hoops_RGRS;
}

HC_EXTERNAL HIC_API int HIC_Show_Marker_Y_Size(HIC_Rendition const *in_nr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)in_nr;
	return nr->_hoops_GSP->ysize;
}

HC_EXTERNAL HIC_API HIC_Polyline const * HIC_New_Polyline(int count, HIC_Point *points)
{
	return (HIC_Polyline const *) HIC_Intermediate_Utility (0, _hoops_CPGCH, points,  _hoops_RSAPI(count));
}

HC_EXTERNAL HIC_API int HIC_Show_Polyline_Count(HIC_Polyline const *polyline)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_ISPCH, (void *)polyline, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Polyline_Points(HIC_Polyline const *polyline)
{
	return ((HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_CSPCH, (void *)polyline, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API HIC_Polygon const * HIC_New_Polygon(int count, HIC_Point *points)
{
	return (HIC_Polygon const *) HIC_Intermediate_Utility (0, _hoops_SPGCH, points,  _hoops_RSAPI(count));
}

HC_EXTERNAL HIC_API int HIC_Show_Polygon_Count(HIC_Polygon const *polygon)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_SSPCH, (void *)polygon, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Polygon_Points(HIC_Polygon const *polygon)
{
	return ((HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_GGHCH, (void *)polygon, IM_NO_VALUES));
}
#if 0

HC_EXTERNAL HIC_API void HIC_Free_Geometry(void *pointer)
{
	(void) HIC_Intermediate_Utility (0, _hoops_RHGCH, (void *)pointer, IM_NO_VALUES);
}
#endif

HC_EXTERNAL HIC_API HIC_Tristrip const * HIC_New_Tristrip(HIC_Tristrip const *ts)
{
	return (HIC_Tristrip const *) HIC_Intermediate_Utility (0, _hoops_AHGCH, (void *)ts, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Free_Tristrip(HIC_Tristrip const *ts)
{
	(void) HIC_Intermediate_Utility (0, _hoops_PHGCH, (void *)ts, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Polyedge const * HIC_New_Polyedge(HIC_Polyedge const *pe)
{
	return (HIC_Polyedge const *) HIC_Intermediate_Utility (0, _hoops_HHGCH, (void *)pe, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Free_Polyedge(HIC_Polyedge const *pe)
{
	(void) HIC_Intermediate_Utility (0, _hoops_IHGCH, (void *)pe, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HIC_Polymarker const * HIC_New_Polymarker(HIC_Polymarker const *pm)
{
	return (HIC_Polymarker const *) HIC_Intermediate_Utility (0, _hoops_CHGCH, (void *)pm, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Free_Polymarker(HIC_Polymarker const *pm)
{
	(void) HIC_Intermediate_Utility (0, _hoops_SHGCH, (void *)pm, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_LOD_Clamp(HIC_Rendition const *nr, int clampval)
{
	(void) HIC_Intermediate_Utility (nr, _hoops_RGHCH, 0,  _hoops_RSAPI(clampval));
}

HC_EXTERNAL HIC_API int HIC_Show_LOD_Clamp(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_ARA->_hoops_PRSI._hoops_IISRP;
}

HC_EXTERNAL HIC_API void HIC_LOD_Enable(HIC_Rendition const *nr)
{
	_hoops_GRA			_hoops_RRA = *(_hoops_GRA alter *)
		HIC_Intermediate_Utility (nr, _hoops_SGRCH, _hoops_ISAPI);

	_hoops_RRA->_hoops_PRSI.options |= _hoops_HRSI;
}

HC_EXTERNAL HIC_API void HIC_LOD_Disable(HIC_Rendition const *nr)
{
	_hoops_GRA			_hoops_RRA = *(_hoops_GRA alter *)
		HIC_Intermediate_Utility (nr, _hoops_SGRCH, _hoops_ISAPI);

	_hoops_RRA->_hoops_PRSI.options &= ~_hoops_HRSI;
}

HC_EXTERNAL HIC_API void HIC_Select_Segment(HIC_Rendition const *nr, HIC_Segment_Info const *si)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RPGCH, (void *)si, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Select_Window(HIC_Rendition const *nr, HIC_Geometry *wi)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PPGCH, (void *)wi, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Record_Selection(HIC_Rendition const *nr, float xyoff, float bz, int off1, int off2, int off3)
{
	(void) HIC_Intermediate_Utility (nr, _hoops_HPGCH, 0, off1, off2, off3, 0, bz, xyoff, 0, 0);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Selection_Point(HIC_Rendition const *nr)
{
	return (HIC_Point const *)HIC_Intermediate_Utility (nr, _hoops_AGHCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Volume const * HIC_Show_Selection_Volume(HIC_Rendition const *nr)
{
	return (HIC_Volume const *)HIC_Intermediate_Utility (nr, _hoops_PGHCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API float HIC_Show_Selection_Proximity_Sq(HIC_Rendition const *nr);


HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Selection_Status(HIC_Rendition const *nr)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_HGHCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int HIC_Show_Selection_Action(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_IGHCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API void HIC_Select_Geometry(HIC_Rendition const *nr, HIC_Geometry const *geo)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_APGCH, (void *)geo, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Segment_Interesting(HIC_Rendition const *nr, HIC_Segment_Info const *si)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CGHCH, (void *)si, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_UnSet_Segment_Interesting(HIC_Rendition const *nr, HIC_Segment_Info const *si)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SGHCH, (void *)si, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API bool HIC_Check_Segment_Interesting(HIC_Rendition const *nr, HIC_Segment_Info const *si)
{
	return (HIC_Intermediate_Utility (nr, _hoops_GRHCH, (void *)si, IM_NO_VALUES)?true:false);
}

HC_EXTERNAL HIC_API void HIC_Set_Geometry_Interesting(HIC_Rendition const *nr, HIC_Marker const *geo)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RRHCH, (void *)geo, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_UnSet_Geometry_Interesting(HIC_Rendition const *nr, HIC_Marker const *geo)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ARHCH, (void *)geo, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API bool HIC_Check_Geometry_Interesting(HIC_Rendition const *nr, HIC_Marker const *geo)
{
	return (HIC_Intermediate_Utility (nr, _hoops_PRHCH, (void *)geo, IM_NO_VALUES)?true:false);
}

HC_EXTERNAL HIC_API void HIC_Set_Current_Geometry_Interesting(HIC_Rendition const *nr)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HRHCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API void HIC_UnSet_Current_Geometry_Interesting(HIC_Rendition const *nr)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_IRHCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API bool HIC_Check_Current_Geometry_Interesting(HIC_Rendition const *nr)
{
	return (HIC_Intermediate_Utility (nr, _hoops_CRHCH, _hoops_ISAPI)?true:false);
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Tristrip_Points(HIC_Tristrip const *ts)
{
	return ((HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_SRHCH, (void *)ts, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Points(HIC_Tristrip const *ts, HIC_Point const *pts)
{
	(void)HIC_Intermediate_Utility (0, _hoops_GAHCH, (void *)ts, _hoops_RSAPI((HC_POINTER_SIZED_INT)pts));
}

HC_EXTERNAL HIC_API int HIC_Show_Tristrip_Point_Count(HIC_Tristrip const *ts)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_RAHCH, (void *)ts, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Show_Tristrip_Face_Count(HIC_Tristrip const *ts)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_AAHCH, (void *)ts, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Show_Tristrip_Strips(HIC_Tristrip const *ts)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_PAHCH, (void *)ts, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Strips(HIC_Tristrip const *ts, int str)
{
	(void)HIC_Intermediate_Utility (0, _hoops_HAHCH, (void *)ts, _hoops_RSAPI(str));
}

HC_EXTERNAL HIC_API int const * HIC_Show_Tristrip_Lengths(HIC_Tristrip const *ts)
{
	return ((int const *)HIC_Intermediate_Utility (0, _hoops_IAHCH, (void *)ts, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Lengths(HIC_Tristrip const *ts, int const *lns)
{
	(void)HIC_Intermediate_Utility (0, _hoops_CAHCH, (void *)ts, _hoops_RSAPI((HC_POINTER_SIZED_INT)lns));
}

HC_EXTERNAL HIC_API int const * HIC_Show_Tristrip_Vertex_Indices(HIC_Tristrip const *ts)
{
	return ((int const *)HIC_Intermediate_Utility (0, _hoops_SAHCH, (void *)ts, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Vertex_Indices(HIC_Tristrip const *ts, int const *vi)
{
	(void)HIC_Intermediate_Utility (0, _hoops_GPHCH, (void *)ts, _hoops_RSAPI((HC_POINTER_SIZED_INT)vi));
}

HC_EXTERNAL HIC_API int const * HIC_Show_Tristrip_Face_Indices(HIC_Tristrip const *ts)
{
	return ((int const *)HIC_Intermediate_Utility (0, _hoops_RPHCH, (void *)ts, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Face_Indices(HIC_Tristrip const *ts, int const *fi)
{
	(void)HIC_Intermediate_Utility (0, _hoops_APHCH, (void *)ts, _hoops_RSAPI((HC_POINTER_SIZED_INT)fi));
}

HC_EXTERNAL HIC_API HIC_RGB const * HIC_Show_Tristrip_Face_Colors(HIC_Tristrip const *ts)
{
	return (HIC_RGB const *)HIC_Intermediate_Utility (0, _hoops_PPHCH, (void *)ts, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Face_Colors(HIC_Tristrip const *ts, HIC_RGB const *fcolors)
{
	(void)HIC_Intermediate_Utility (0, _hoops_HPHCH, (void *)ts, _hoops_RSAPI((HC_POINTER_SIZED_INT)fcolors));
}

HC_EXTERNAL HIC_API HIC_Plane const * HIC_Show_Tristrip_Face_Normals(HIC_Tristrip const *ts)
{
	return (HIC_Plane const *)HIC_Intermediate_Utility (0, _hoops_IPHCH, (void *)ts, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Face_Normals(HIC_Tristrip const *ts, HIC_Plane const *fnormals)
{
	(void)HIC_Intermediate_Utility (0, _hoops_CPHCH, (void *)ts, _hoops_RSAPI((HC_POINTER_SIZED_INT)fnormals));
}

HC_EXTERNAL HIC_API HIC_RGB const * HIC_Show_Tristrip_Vertex_Colors(HIC_Tristrip const *ts)
{
	return ((HIC_RGB const *)HIC_Intermediate_Utility (0, _hoops_SPHCH, (void *)ts, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Vertex_Colors(HIC_Tristrip const *ts, HIC_RGB const *vcolors)
{
	(void)HIC_Intermediate_Utility (0, _hoops_GHHCH, (void *)ts, _hoops_RSAPI((HC_POINTER_SIZED_INT)vcolors));
}

HC_EXTERNAL HIC_API float const * HIC_Show_Tristrip_Vertex_Findices(HIC_Tristrip const *ts)
{
	return ((float const *)HIC_Intermediate_Utility (0, _hoops_RHHCH, (void *)ts, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Vertex_Findices(HIC_Tristrip const *ts, float const *vfindices)
{
	(void)HIC_Intermediate_Utility (0, _hoops_AHHCH, (void *)ts, _hoops_RSAPI((HC_POINTER_SIZED_INT)vfindices));
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Tristrip_Vertex_Normals(HIC_Tristrip const *ts)
{
	return ((HIC_Vector const *)HIC_Intermediate_Utility (0, _hoops_PHHCH, (void *)ts, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Vertex_Normals(HIC_Tristrip const *ts, HIC_Vector const *vnormals)
{
	(void)HIC_Intermediate_Utility (0, _hoops_HHHCH, (void *)ts, _hoops_RSAPI((HC_POINTER_SIZED_INT)vnormals));
}

HC_EXTERNAL HIC_API HIC_Parameter const * HIC_Show_Tristrip_Vertex_Parameters(HIC_Tristrip const *ts)
{
	return ((HIC_Parameter const *)HIC_Intermediate_Utility (0, _hoops_IHHCH, (void *)ts, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Vertex_Parameters(HIC_Tristrip const *ts, HIC_Parameter const *vparameters)
{
	(void)HIC_Intermediate_Utility (0, _hoops_CHHCH, (void *)ts, _hoops_RSAPI((HC_POINTER_SIZED_INT)vparameters));
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Tristrip_Vertex_Parameter_Width(HIC_Tristrip const *ts)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_SHHCH, (void *)ts, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Vertex_Parameter_Width(HIC_Tristrip const *ts, int width)
{
	(void)HIC_Intermediate_Utility (0, _hoops_GIHCH, (void *)ts,  _hoops_RSAPI(width));
}

HC_EXTERNAL HIC_API bool HIC_Show_Tristrip_Findex_Color_Interpolation(HIC_Tristrip const *ts)
{
	return (HIC_Intermediate_Utility (0, _hoops_RIHCH, (void *)ts, IM_NO_VALUES)?true:false);
}

HC_EXTERNAL HIC_API void HIC_Set_Tristrip_Findex_Color_Interpolation(HIC_Tristrip const *ts, bool flag)
{
	(void)HIC_Intermediate_Utility (0, _hoops_AIHCH, (void *)ts, _hoops_RSAPI((HC_POINTER_SIZED_INT)flag));
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Polyedge_Points(HIC_Polyedge const *pe)
{
	return((HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_PIHCH, (void *)pe, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Points(HIC_Polyedge const *pe, HIC_Point const *pts)
{
	(void)HIC_Intermediate_Utility (0, _hoops_HIHCH, (void *)pe, _hoops_RSAPI((HC_POINTER_SIZED_INT)pts));
}

HC_EXTERNAL HIC_API int HIC_Show_Polyedge_Point_Count(HIC_Polyedge const *pe)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_IIHCH, (void *)pe, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Show_Polyedge_Edge_Count(HIC_Polyedge const *pe)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_CIHCH, (void *)pe, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Show_Polyedge_Strips(HIC_Polyedge const *pe)
{
	return(int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_SIHCH, (void *)pe, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Strips(HIC_Polyedge const *pe, int str)
{
	(void)HIC_Intermediate_Utility (0, _hoops_GCHCH, (void *)pe, _hoops_RSAPI(str));
}

HC_EXTERNAL HIC_API int const * HIC_Show_Polyedge_Lengths(HIC_Polyedge const *pe)
{
	return((int const *)HIC_Intermediate_Utility (0, _hoops_RCHCH, (void *)pe, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Lengths(HIC_Polyedge const *pe, int const *lns)
{
	(void)HIC_Intermediate_Utility (0, _hoops_ACHCH, (void *)pe,  _hoops_RSAPI((HC_POINTER_SIZED_INT)lns));
}

HC_EXTERNAL HIC_API int const * HIC_Show_Polyedge_Vertex_Indices(HIC_Polyedge const *pe)
{
	return((int const *)HIC_Intermediate_Utility (0, _hoops_PCHCH, (void *)pe, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Vertex_Indices(HIC_Polyedge const *pe, int const *vi)
{
	(void)HIC_Intermediate_Utility (0, _hoops_HCHCH, (void *)pe,  _hoops_RSAPI((HC_POINTER_SIZED_INT)vi));
}

HC_EXTERNAL HIC_API int const * HIC_Show_Polyedge_Edge_Indices(HIC_Polyedge const *pe)
{
	return((int const *)HIC_Intermediate_Utility (0, _hoops_ICHCH, (void *)pe, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Edge_Indices(HIC_Polyedge const *pe, int const *ei)
{
	(void)HIC_Intermediate_Utility (0, _hoops_CCHCH, (void *)pe,  _hoops_RSAPI((HC_POINTER_SIZED_INT)ei));
}

HC_EXTERNAL HIC_API HIC_RGB const * HIC_Show_Polyedge_Edge_Colors(HIC_Polyedge const *pe)
{
	return((HIC_RGB const *)HIC_Intermediate_Utility (0, _hoops_SCHCH, (void *)pe, IM_NO_VALUES));
}

/*

_hoops_SCPPI _hoops_GSPPI _hoops_SRPC _hoops_RRHPI(_hoops_ARHPI _hoops_RCIC *_hoops_SAHA, _hoops_PRHPI _hoops_RCIC *_hoops_HRHPI)
{
	(_hoops_SRPC)_hoops_PGHPI (0, _hoops_IRHPI, (_hoops_SRPC *)_hoops_SAHA,  _hoops_CRHPI((_hoops_SRHPI)_hoops_HRHPI));
}

*/

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Polyedge_Edge_Normals(HIC_Polyedge const *pe)
{
	return((HIC_Vector const *)HIC_Intermediate_Utility (0, _hoops_RSHCH, (void *)pe, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Edge_Normals(HIC_Polyedge const *pe, HIC_Vector const *enormals)
{
	(void)HIC_Intermediate_Utility (0, _hoops_ASHCH, (void *)pe,  _hoops_RSAPI((HC_POINTER_SIZED_INT)enormals));

}

HC_EXTERNAL HIC_API HIC_RGB const *HIC_Show_Polyedge_Vertex_Colors(HIC_Polyedge const *pe)
{
	return((HIC_RGB const *)HIC_Intermediate_Utility (0, _hoops_PSHCH, (void *)pe, IM_NO_VALUES));
}

/*
_hoops_SCPPI _hoops_GSPPI _hoops_SRPC _hoops_GAHPI(_hoops_ARHPI _hoops_RCIC *_hoops_SAHA, _hoops_PRHPI _hoops_RCIC *_hoops_RAHPI)
{
	(_hoops_SRPC)_hoops_PGHPI (0, _hoops_AAHPI, (_hoops_SRPC *)_hoops_SAHA,  _hoops_CRHPI((_hoops_SRHPI)_hoops_RAHPI));
}
*/

HC_EXTERNAL HIC_API float const * HIC_Show_Polyedge_Vertex_Findices(HIC_Polyedge const *pe)
{
	return ((float const *)HIC_Intermediate_Utility (0, _hoops_ISHCH, (void *)pe, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Vertex_Findices(HIC_Polyedge const *pe, float const *vfindices)
{
	(void)HIC_Intermediate_Utility (0, _hoops_CSHCH, (void *)pe,  _hoops_RSAPI((HC_POINTER_SIZED_INT)vfindices));
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Polyedge_Vertex_Normals(HIC_Polyedge const *pe)
{
	return ((HIC_Vector const *)HIC_Intermediate_Utility (0, _hoops_SSHCH, (void *)pe, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Vertex_Normals(HIC_Polyedge const *pe, HIC_Vector const *vnormals)
{
	(void)HIC_Intermediate_Utility (0, _hoops_GGICH, (void *)pe,  _hoops_RSAPI((HC_POINTER_SIZED_INT)vnormals));
}

HC_EXTERNAL HIC_API HIC_Parameter const * HIC_Show_Polyedge_Vertex_Parameters(HIC_Polyedge const *pe)
{
	return ((HIC_Parameter const *)HIC_Intermediate_Utility (0, _hoops_RGICH, (void *)pe, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Vertex_Parameters(HIC_Polyedge const *pe, HIC_Parameter const *vparameters)
{
	(void)HIC_Intermediate_Utility (0, _hoops_AGICH, (void *)pe,  _hoops_RSAPI((HC_POINTER_SIZED_INT)vparameters));
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Polyedge_Vertex_Parameter_Width(HIC_Polyedge const *pe)
{
	return (HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_PGICH, (void *)pe, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Vertex_Parameter_Width(HIC_Polyedge const *pe, HIC_Integer32 width)
{
	(void)HIC_Intermediate_Utility (0, _hoops_HGICH, (void *)pe,  _hoops_RSAPI(width));
}

HC_EXTERNAL HIC_API bool HIC_Show_Polyedge_Findex_Color_Interpolation(HIC_Polyedge const *pe)
{
	return(HIC_Intermediate_Utility (0, _hoops_IGICH, (void *)pe, IM_NO_VALUES)?true:false);
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Findex_Color_Interpolation(HIC_Polyedge const *pe, bool flag)
{
	(void)HIC_Intermediate_Utility (0, _hoops_CGICH, (void *)pe, _hoops_RSAPI((HC_POINTER_SIZED_INT)flag));
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Polymarker_Points(HIC_Polymarker const *pm)
{
	return ((HIC_Point const *)HIC_Intermediate_Utility (0, _hoops_SGICH, (void *)pm, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polymarker_Points(HIC_Polymarker const *pm, HIC_Point const *pts)
{
	(void)HIC_Intermediate_Utility (0, _hoops_GRICH, (void *)pm,  _hoops_RSAPI((HC_POINTER_SIZED_INT)pts));
}

HC_EXTERNAL HIC_API int HIC_Show_Polymarker_Point_Count(HIC_Polymarker const *pm)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_RRICH, (void *)pm, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Show_Polymarker_Length(HIC_Polymarker const *pm)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_ARICH, (void *)pm, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Polymarker_Length(HIC_Polymarker const *pm, int len)
{
	(void)HIC_Intermediate_Utility (0, _hoops_PRICH, (void *)pm, _hoops_RSAPI((HC_POINTER_SIZED_INT)len));
}

HC_EXTERNAL HIC_API int const * HIC_Show_Polymarker_Vertex_Indices(HIC_Polymarker const *pm)
{
	return ((int const *)HIC_Intermediate_Utility (0, _hoops_HRICH, (void *)pm, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polymarker_Vertex_Indices(HIC_Polymarker const *pm, int const *vi)
{
	(void)HIC_Intermediate_Utility (0, _hoops_IRICH, (void *)pm,  _hoops_RSAPI((HC_POINTER_SIZED_INT)vi));
}

HC_EXTERNAL HIC_API HIC_RGB const * HIC_Show_Polymarker_Vertex_Colors(HIC_Polymarker const *pm)
{
	return((HIC_RGB const *)HIC_Intermediate_Utility (0, _hoops_CRICH, (void *)pm, IM_NO_VALUES));
}

/*

_hoops_SCPPI _hoops_GSPPI _hoops_SRPC _hoops_PAHPI(_hoops_HAHPI _hoops_RCIC *_hoops_IRAS, _hoops_PRHPI _hoops_RCIC *_hoops_RAHPI)
{
	(_hoops_SRPC)_hoops_PGHPI (0, _hoops_IAHPI, (_hoops_SRPC *)_hoops_IRAS, _hoops_CRHPI((_hoops_SRHPI)_hoops_RAHPI));
}
*/

HC_EXTERNAL HIC_API float const * HIC_Show_Polymarker_Vertex_Findices(HIC_Polymarker const *pm)
{
	return((float const *)HIC_Intermediate_Utility (0, _hoops_GAICH, (void *)pm, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polymarker_Vertex_Findices(HIC_Polymarker const *pm, float const *vfindices)
{
	(void)HIC_Intermediate_Utility (0, _hoops_RAICH, (void *)pm, _hoops_RSAPI((HC_POINTER_SIZED_INT)vfindices));
}

HC_EXTERNAL HIC_API HIC_Vector const * HIC_Show_Polymarker_Vertex_Normals(HIC_Polymarker const *pm)
{
	return((HIC_Vector const *)HIC_Intermediate_Utility (0, _hoops_AAICH, (void *)pm, IM_NO_VALUES));
}

HC_EXTERNAL HIC_API void HIC_Set_Polymarker_Vertex_Normals(HIC_Polymarker const *pm, HIC_Vector const *vnormals)
{
	(void)HIC_Intermediate_Utility (0, _hoops_RAICH, (void *)pm, _hoops_RSAPI((HC_POINTER_SIZED_INT)vnormals));
}

HC_EXTERNAL HIC_API HIC_Parameter const * HIC_Show_Polymarker_Vertex_Parameters(HIC_Polymarker const *pm)
{
	return((HIC_Parameter const *)HIC_Intermediate_Utility (0, _hoops_HAICH, (void *)pm, IM_NO_VALUES));

}
HC_EXTERNAL HIC_API void HIC_Set_Polymarker_Vertex_Parameters(HIC_Polymarker const *pm, HIC_Parameter const *vparameters)
{
	(void)HIC_Intermediate_Utility (0, _hoops_IAICH, (void *)pm, _hoops_RSAPI((HC_POINTER_SIZED_INT)vparameters));
}

HC_EXTERNAL HIC_API HIC_Integer32 HIC_Show_Polymarker_Vertex_Parameter_Width(HIC_Polymarker const *pm)
{
	return(HIC_Integer32)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (0, _hoops_CAICH, (void *)pm, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API void HIC_Set_Polymarker_Vertex_Parameter_Width(HIC_Polymarker const *pm, HIC_Integer32 width)
{
	(void)HIC_Intermediate_Utility (0, _hoops_SAICH, (void *)pm, _hoops_RSAPI(width));
}

HC_EXTERNAL HIC_API bool HIC_Show_Polymarker_Findex_Color_Interpolation(HIC_Polymarker const *pm)
{
	return (HIC_Intermediate_Utility (0, _hoops_GPICH, (void *)pm, IM_NO_VALUES)?true:false);
}

HC_EXTERNAL HIC_API void HIC_Set_Polymarker_Findex_Color_Interpolation(HIC_Polymarker const *pm, bool flag)
{
	(void)HIC_Intermediate_Utility (0, _hoops_RPICH, (void *)pm,  _hoops_RSAPI((HC_POINTER_SIZED_INT)flag));
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Front_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_APICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Back_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_PPICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Face_Contrast_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_HPICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Edge_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_IPICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Edge_Contrast_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_CPICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Line_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_SPICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Line_Contrast_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_GHICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Marker_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_RHICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Marker_Contrast_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_AHICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Vertex_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_PHICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Vertex_Contrast_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_HHICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Text_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_IHICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Text_Contrast_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_CHICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Window_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_SHICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Window_Contrast_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_GIICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Cut_Face_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_RIICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API  HIC_Material_Color_Locks  HIC_Show_Color_Cut_Edge_Locks(HIC_Rendition const *nr)
{
	return (HIC_Material_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_AIICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Color_Locks HIC_Show_Color_Locks(HIC_Rendition const *nr)
{
	return (HIC_Color_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_PIICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Visibility_Locks HIC_Show_Visibility_Locks(HIC_Rendition const *nr)
{
	return(HIC_Visibility_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_HIICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API HIC_Attribute_Locks HIC_Show_Attribute_Locks(HIC_Rendition const *nr)
{
	return(HIC_Attribute_Locks)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_IIICH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Front_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CIICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Back_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SIICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Face_Contrast_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GCICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Edge_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RCICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Edge_Contrast_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ACICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Line_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PCICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Line_Contrast_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HCICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Marker_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ICICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Marker_Contrast_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CCICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Vertex_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SCICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Vertex_Contrast_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GSICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Text_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RSICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Text_Contrast_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ASICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Window_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PSICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Window_Contrast_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HSICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Cut_Face_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_ISICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void  HIC_Set_Color_Cut_Edge_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects material_color_locks)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CSICH, 0, _hoops_RSAPI(material_color_locks));
}

HC_EXTERNAL HIC_API void HIC_Set_Color_Locks(HIC_Rendition const *nr, HIC_Color_Lock_Objects color_locks)
{
		(void)HIC_Intermediate_Utility (nr, _hoops_SSICH, 0, _hoops_RSAPI(color_locks));
}

HC_EXTERNAL HIC_API void HIC_Set_Visibility_Locks(HIC_Rendition const *nr, HIC_Visibility_e visibility_locks)
{
		(void)HIC_Intermediate_Utility (nr, _hoops_GGCCH, 0, _hoops_RSAPI(visibility_locks));
}

HC_EXTERNAL HIC_API void HIC_Set_Attribute_Locks(HIC_Rendition const *nr, HIC_Attributes attribute_locks)
{
		(void)HIC_Intermediate_Utility (nr, _hoops_RGCCH, 0, _hoops_RSAPI(attribute_locks));
}

HC_EXTERNAL HIC_API HIC_Polyhedron const * HIC_New_User_Shell(int point_count, HIC_Point const *points, HIC_Vector const*normals, int face_list_length, int *face_list)
{
	return	(HIC_Polyhedron const *)HIC_Intermediate_Utility (0, _hoops_GPCCH, (void *)points, point_count,
			(HC_POINTER_SIZED_INT)normals, face_list_length, (HC_POINTER_SIZED_INT)face_list, _hoops_GSAPI);

}

HC_EXTERNAL HIC_API void HIC_Free_User_Shell(HIC_Polyhedron const *user_shell)
{
	(void)HIC_Intermediate_Utility (0, _hoops_RPCCH, (void *)user_shell, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API int HIC_Driver_Get_Window_Width(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_GRHGR, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API int HIC_Driver_Get_Window_Height(HIC_Rendition const *nr)
{
	return (int)(HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_RRHGR, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API bool HIC_Driver_Is_Double_Buffering(HIC_Rendition const *nr)
{
	return (HIC_Intermediate_Utility (nr, _hoops_HPCCH, _hoops_ISAPI)?true:false);
}


HC_EXTERNAL HIC_API bool HIC_Driver_Tristrip_Has_Valid_DL(HIC_Rendition const *nr, HIC_Tristrip const *ts)
{
	return (HIC_Intermediate_Utility (nr, _hoops_CPCCH, (void *)ts, IM_NO_VALUES)?true:false);
}

HC_EXTERNAL HIC_API void HIC_Driver_glActiveTextureARB(HIC_Rendition const *nr, int number)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_SPCCH, 0, _hoops_RSAPI(number));
}

HC_EXTERNAL HIC_API void  HIC_Driver_ENSURE_ALPHA_TEST_ON(HIC_Rendition const *nr, int number)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_APCCH, 0, _hoops_RSAPI(number));
}

HC_EXTERNAL HIC_API void  HIC_Driver_ENSURE_ALPHA_TEST_OFF(HIC_Rendition const *nr, int number)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PPCCH, 0, _hoops_RSAPI(number));
}

HC_EXTERNAL HIC_API void  HIC_Driver_ENSURE_TEXTURES_ON(HIC_Rendition const *nr, int number)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GHCCH, 0, _hoops_RSAPI(number));
}

HC_EXTERNAL HIC_API void HIC_Driver_ENSURE_TEXTURES_OFF(HIC_Rendition const *nr, int number)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_RHCCH, 0, _hoops_RSAPI(number));
}


HC_EXTERNAL HIC_API void HIC_Driver_FORCE_TEXTURE_GEN_OFF(HIC_Rendition const *nr, int number)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_AHCCH, 0, _hoops_RSAPI(number));
}

HC_EXTERNAL HIC_API void HIC_Driver_Bind_Image_As_Texture(HIC_Rendition const *nr, HIC_Image const *image)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PHCCH, (void *)image, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API HC_POINTER_SIZED_INT HIC_Driver_Compile_Shader(HIC_Rendition const *nr, HIC_Shader_Type type, char const *shader_source)
{
	return (HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_ARHGR, (void *)shader_source, _hoops_RSAPI(type));
}
HC_EXTERNAL HIC_API void HIC_Driver_Release_Shader(HIC_Rendition const *nr, HC_POINTER_SIZED_INT shader_handle)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HRHGR, (void *)shader_handle, IM_NO_VALUES);
}
HC_EXTERNAL HIC_API bool HIC_Driver_Set_Shader(HIC_Rendition const *nr, HIC_Shader_Type type, HC_POINTER_SIZED_INT shader_handle)
{
	return (HIC_Intermediate_Utility (nr, _hoops_CRHGR, (void *)shader_handle, _hoops_RSAPI(type))?true:false);
}
HC_EXTERNAL HIC_API void HIC_Driver_Set_Shader_Integer(HIC_Rendition const *nr, HIC_Shader_Type type, char const *name, int count, int const *data)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GAHGR, (void *)name, type, count, (HC_POINTER_SIZED_INT)data, 0, _hoops_GSAPI);
}
HC_EXTERNAL HIC_API void HIC_Driver_Set_Shader_Float(HIC_Rendition const *nr, HIC_Shader_Type type, char const *name, int count, float const *data)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_AAHGR, (void *)name, type, count, (HC_POINTER_SIZED_INT)data, 0, _hoops_GSAPI);
}
HC_EXTERNAL HIC_API void HIC_Driver_Set_Shader_Vector(HIC_Rendition const *nr, HIC_Shader_Type type, char const *name, int width, int count, float const *data)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_HAHGR, (void *)name, type, width, count, (HC_POINTER_SIZED_INT)data, _hoops_GSAPI);
}
HC_EXTERNAL HIC_API void HIC_Driver_Set_Shader_Matrix(HIC_Rendition const *nr, HIC_Shader_Type type, char const *name, int count, float const *data)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CAHGR, (void *)name, type, count, (HC_POINTER_SIZED_INT)data, 0, _hoops_GSAPI);
}
HC_EXTERNAL HIC_API void HIC_Driver_Show_Shader_Modelview_Matrix(HIC_Rendition const *nr, float *matrix)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_GPHGR, (void *)matrix, IM_NO_VALUES);
}
HC_EXTERNAL HIC_API void HIC_Driver_Show_Shader_Projection_Matrix(HIC_Rendition const *nr, float *matrix)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_PPHGR, (void *)matrix, IM_NO_VALUES);
}
HC_EXTERNAL HIC_API HC_POINTER_SIZED_INT HIC_Driver_Snapshot_Texture(HIC_Rendition const *nr, HC_POINTER_SIZED_INT id)
{
	return (HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_HHCCH, (void *)id, IM_NO_VALUES);
}
HC_EXTERNAL HIC_API HC_POINTER_SIZED_INT HIC_Driver_Snapshot_Depth_Texture(HIC_Rendition const *nr, HC_POINTER_SIZED_INT id)
{
	return (HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_IHCCH, (void *)id, IM_NO_VALUES);
}
HC_EXTERNAL HIC_API void HIC_Driver_Show_Projection_Matrix(HIC_Rendition const *nr, float *matrix)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_APHGR, (void *)matrix, IM_NO_VALUES);
}
HC_EXTERNAL HIC_API void HIC_Driver_Draw_Clear_Window(HIC_Rendition const *nr, HIC_Int_Rectangle const *extent)
{
	(void)HIC_Intermediate_Utility (nr, _hoops_CHCCH, (void *)extent, IM_NO_VALUES);
}


HC_EXTERNAL HIC_API void HIC_Set_Polymarker_Vertex_Colors(HIC_Polymarker const *pm, HIC_RGB const *vcolors)
{
	(void)HIC_Intermediate_Utility (0, _hoops_SRICH, (void *)pm, _hoops_RSAPI((HC_POINTER_SIZED_INT)vcolors));
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Edge_Colors(HIC_Polyedge const *pe, HIC_RGB const *ecolors)
{
	HIC_Intermediate_Utility (0, _hoops_GSHCH, (void *)pe,  _hoops_RSAPI((HC_POINTER_SIZED_INT)ecolors));
}

HC_EXTERNAL HIC_API void HIC_Set_Polyedge_Vertex_Colors(HIC_Polyedge const *pe, HIC_RGB const *vcolors)
{
	(void)HIC_Intermediate_Utility (0, _hoops_HSHCH, (void *)pe,  _hoops_RSAPI((HC_POINTER_SIZED_INT)vcolors));
}


HC_EXTERNAL HIC_API void HIC_Free_Geometry(HIC_Geometry const *pointer)
{
	 HIC_Intermediate_Utility (0, _hoops_RHGCH, (void *)pointer, IM_NO_VALUES);
}

HC_EXTERNAL HIC_API float const * HIC_Show_Camera_Positioning_Matrix(HIC_Rendition const *in_nr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)in_nr;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_HHRA const *				_hoops_SPH = _hoops_IHCR->_hoops_SPH;

	if (!HI_Camera_To_Transform ((_hoops_HHRA alter *)_hoops_SPH, 0.0)) /* _hoops_ICIC */
		return null;
	else
		return (float const *)&_hoops_SPH->_hoops_PRPA.elements[0][0];
}

HC_EXTERNAL HIC_API float const * HIC_Show_Camera_Projection_Matrix(HIC_Rendition const *in_nr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)in_nr;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;
	_hoops_HHRA const *				_hoops_SPH = _hoops_IHCR->_hoops_SPH;

	if (!HI_Camera_To_Transform ((_hoops_HHRA alter *)_hoops_SPH, 0.0)) /* _hoops_ICIC */
		return null;
	else
		return (float const *)&_hoops_SPH->_hoops_AIIH.elements[0][0];
}

HC_EXTERNAL HIC_API float HIC_Show_Camera_Aspect(HIC_Rendition const *in_nr)
{
	Net_Rendition const & nr = *(Net_Rendition const *)in_nr;
	return nr->transform_rendition->_hoops_SPH->_hoops_CSIH;
}

HC_EXTERNAL HIC_API float const * HIC_Show_Modelling_Matrix(HIC_Rendition const *in_nr)
{
	Net_Rendition const &		nr = *(Net_Rendition const *)in_nr;
	return (float const *)&nr->transform_rendition->_hoops_IPH->data.elements[0][0];
}

HC_EXTERNAL HIC_API float const * HIC_Show_Modelling_Matrix_Adjoint(HIC_Rendition const *in_nr)
{
	Net_Rendition const &		nr = *(Net_Rendition const *)in_nr;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	return (float const *)&_hoops_IHCR->_hoops_IPH->_hoops_PPRA()->data.elements[0][0];
}

HC_EXTERNAL HIC_API float const * HIC_Show_World_To_Screen_Matrix(HIC_Rendition const *in_nr)
{
	Net_Rendition const &		nr = *(Net_Rendition const *)in_nr;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	if (!BIT (_hoops_IHCR->flags, _hoops_IGCC))
		HD_Validate_World_To_Screen (nr);

	return (float const *)&_hoops_IHCR->_hoops_CGCC->data.elements[0][0];
}

HC_EXTERNAL HIC_API float const * HIC_Show_World_To_Screen_Adjoint(HIC_Rendition const *in_nr)
{
	Net_Rendition const &		nr = *(Net_Rendition const *)in_nr;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	if (!BIT (_hoops_IHCR->flags, _hoops_IGCC))
		HD_Validate_World_To_Screen (nr);

	return (float const *)&_hoops_IHCR->_hoops_CGCC->_hoops_PPRA()->data.elements[0][0];
}

HC_EXTERNAL HIC_API float const * HIC_Show_Object_To_Screen_Matrix(HIC_Rendition const *in_nr)
{
	Net_Rendition const &		nr = *(Net_Rendition const *)in_nr;
	return (float const *)&nr->transform_rendition->matrix->data.elements[0][0];
}

HC_EXTERNAL HIC_API float const * HIC_Show_Object_To_Screen_Adjoint(HIC_Rendition const *in_nr)
{
	Net_Rendition const &		nr = *(Net_Rendition const *)in_nr;
	_hoops_HHCR const &	_hoops_IHCR = nr->transform_rendition;

	return (float const *)&_hoops_IHCR->matrix->_hoops_PPRA()->data.elements[0][0];
}


HC_EXTERNAL HIC_API float const * HIC_Show_Transform_Matrix(HIC_Rendition const *in_nr)
{
	Net_Rendition const &		nr = *(Net_Rendition const *)in_nr;
	return (float const *)&nr->transform_rendition->matrix->data.elements[0][0];
}

HC_EXTERNAL HIC_API void *HIC_Driver_Get_HDC(HIC_Rendition const *nr)
{
		return HIC_Intermediate_Utility (nr, _hoops_IPCCH, _hoops_ISAPI);
}

HC_EXTERNAL HIC_API void HIC_Draw_DC_Image_Block(HIC_Rendition const *nr, HIC_DC_Point *strt, int wdth, int hite, HIC_Image_Format frmt, int rowbytes, void const *blk)
{
	(void) HIC_Intermediate_Utility (nr, _hoops_AIGCH, (void *)blk, wdth, hite, frmt, rowbytes, (strt)->x, (strt)->y, (strt)->z, 0);
}


HC_EXTERNAL HIC_API void HIC_Get_Update_Stat(HIC_Rendition const *in_nr, const char *stat_name, double *stat_value)
{
	Net_Rendition const & nr = *(Net_Rendition const *)in_nr;

	if (!stat_name || !stat_value)
		return;

	*stat_value = 0.0;

	if (_hoops_AGGR (stat_name, "segments"))
		*stat_value = (double)_hoops_GPRH(_hoops_SISAA);
}

HC_EXTERNAL HIC_API bool HIC_Using_Hidden_Line_HSRA(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_IRR->_hoops_SRI == _hoops_SICI;
}

HC_EXTERNAL HIC_API bool HIC_Has_Text_Names_Ref(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_SISI->_hoops_HSRIP != null;
}
HC_EXTERNAL HIC_API bool HIC_Has_Text_Names_Ref_Names(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_SISI->_hoops_HSRIP->_hoops_HGPIR != null;
}
HC_EXTERNAL HIC_API bool HIC_Is_Text_GFN_Specified(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_SISI->_hoops_HSRIP->_hoops_HGPIR->_hoops_SSSGP == GFN_SPECIFIED;
}

HC_EXTERNAL HIC_API HIC_Point const * HIC_Show_Image_Position(HIC_Image const *image)
{
	Image const * img = (Image const *)image;
	return (HIC_Point const *)&img->_hoops_CSAI;
}


HC_EXTERNAL HIC_API void HIC_Show_Time(double *current_time)
{
	*current_time = HI_What_Time() * (1.0 / _hoops_HSPGR);
}




HC_EXTERNAL HIC_API void HIC_Compute_Transformed_Points (
	HIC_Rendition const *nr,
	int					count,
	HIC_Point const *	points,
	float const *		matp,
	HIC_Point *			result)
{
	UNREFERENCED(nr);
	HI_Compute_Transformed_Points (count, (Point const *)points, matp, (Point *)result);
}

HC_EXTERNAL HIC_API HC_KEY HIC_Find_Relative_Segment(HIC_Rendition const *nr, HC_KEY _hoops_CAHPI, const char *path)
{
	Net_Rendition const &	_hoops_PCPPI = *(Net_Rendition const *)nr;
	_hoops_AIGPR *	_hoops_RIGC = _hoops_PCPPI->_hoops_SRA->_hoops_RIGC;

	_hoops_CRCP * start = (_hoops_CRCP *)_hoops_RCSSR (_hoops_RIGC, _hoops_CAHPI);

	if (!start || start->type != _hoops_IRCP)
		return _hoops_SHSSR;

	HI_Open_Segment(_hoops_RIGC, start);

	_hoops_CRCP * _hoops_SRCP = HI_One_Segment_Search (_hoops_RIGC, path, false);

	HI_Close_Segment (_hoops_RIGC);

	if (!_hoops_SRCP || _hoops_SRCP->type != _hoops_IRCP)
		return _hoops_SHSSR;

	return _hoops_AIRIR(_hoops_SRCP);
}

HC_EXTERNAL HIC_API HC_KEY HIC_Show_Owner_Key_By_Key(HIC_Rendition const *nr, HC_KEY key)
{
	Net_Rendition const &	_hoops_PCPPI = *(Net_Rendition const *)nr;
	_hoops_AIGPR *	_hoops_RIGC = _hoops_PCPPI->_hoops_SRA->_hoops_RIGC;
	return (HC_KEY) HI_Show_Owner_Key_By_Key(_hoops_RIGC, key, true, false);
}

HC_EXTERNAL HIC_API HC_KEY HIC_Show_Owner_Original_Key_By_Key(HIC_Rendition const *nr, HC_KEY key)
{
	Net_Rendition const &	_hoops_PCPPI = *(Net_Rendition const *)nr;
	_hoops_AIGPR *	_hoops_RIGC = _hoops_PCPPI->_hoops_SRA->_hoops_RIGC;
	return (HC_KEY) HI_Show_Owner_Key_By_Key(_hoops_RIGC, key, true, true);
}



HC_EXTERNAL HIC_API bool HIC_Compute_Transform_By_Path(
	HIC_Rendition const *	in_nr,
	int						count,
	HC_KEY const *			keys,
	char const *			in_system,
	char const *			out_system,
	float *					matrix)
{
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;
	return HI_Compute_Transform_By_Path (nr->_hoops_SRA->_hoops_RIGC, count, keys, in_system, out_system, matrix);
}


HC_EXTERNAL HIC_API void HIC_Show_Shell_Size(
	HIC_Rendition const *	in_nr,
	HC_KEY key,
	int * point_countp,
	int * face_list_lengthp)
{
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;

	HI_Show_Shell_Size (nr->_hoops_SRA->_hoops_RIGC, key, point_countp, face_list_lengthp);
}


HC_EXTERNAL HIC_API void HIC_Show_Shell (
	HIC_Rendition const *in_nr,
	HC_KEY key,
	int *point_countp,
	HIC_Point *points,
	int *face_list_lengthp,
	int *face_list)
{
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;

	HI_Show_Shell (nr->_hoops_SRA->_hoops_RIGC, key, point_countp, (Point *)points, face_list_lengthp, face_list);
}


HC_EXTERNAL HIC_API void HIC_Compute_Identity_Matrix (
	HIC_Rendition const *nr,
	float *matp)
{
	UNREFERENCED(nr);
	HI_Compute_Identity_Matrix (matp);
}

HC_EXTERNAL HIC_API void HIC_Compute_Scale_Matrix (
	HIC_Rendition const *nr,
	double x,
	double y,
	double z,
	float *matp)
{
	UNREFERENCED(nr);
	HI_Compute_Scale_Matrix (x, y, z, matp);
}


HC_EXTERNAL HIC_API void HIC_Compute_Matrix_Product (
	HIC_Rendition const *nr,
	float const *leftp,
	float const *rightp,
	float *resultp)
{
	UNREFERENCED(nr);
	HI_Compute_Matrix_Product (leftp, rightp, resultp);
}



HC_EXTERNAL HIC_API bool HIC_Compute_Matrix_Inverse (
	HIC_Rendition const *nr,
	float const * matp,
	float * invp)
{
	UNREFERENCED(nr);
	return HI_Compute_Matrix_Inverse (matp, invp);
}




HC_EXTERNAL HIC_API void HIC_Unsafe_Threading (
	HIC_Rendition const *in_nr,
	bool allow)
{

	_hoops_AIGPR *	_hoops_RIGC;
	if (in_nr) {
		Net_Rendition const &		nr = *(Net_Rendition const *)in_nr;
		Display_Context const *		dc = nr->_hoops_SRA;
		_hoops_RIGC = dc->_hoops_RIGC;
	}
	else {
		_hoops_IIRIR (_hoops_RIGC);
	}

	_hoops_RIGC->_hoops_GSHGH = allow;
}


HC_EXTERNAL HIC_API HC_POINTER_SIZED_INT HIC_Show_Effective_Thread_ID()
{
	_hoops_AIGPR *_hoops_RIGC;
	_hoops_IIRIR (_hoops_RIGC);

	return (HC_POINTER_SIZED_INT)_hoops_RIGC->thread_id;
}

HC_EXTERNAL HIC_API bool HIC_Show_Bounding_Sphere_By_Key(HIC_Rendition const *in_nr, HC_KEY key, HIC_Point *center, float *radius)
{
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;
	_hoops_AIGPR *	_hoops_RIGC = nr->_hoops_SRA->_hoops_RIGC;

	Bounding	_hoops_RCHS;

	_hoops_HPAH *	item = (_hoops_HPAH *)_hoops_RCSSR (_hoops_RIGC, key);
	HI_Find_Bounding (_hoops_RIGC, item, _hoops_RCHS);
	
	if (!_hoops_RCHS._hoops_HICAR()) {

		center->x = _hoops_RCHS->sphere.center.x;
		center->y = _hoops_RCHS->sphere.center.y;
		center->z = _hoops_RCHS->sphere.center.z;

		*radius = _hoops_RCHS->sphere.radius;

		return true;
	}

	return false;
}

HC_EXTERNAL HIC_API bool HIC_Show_Bounding_Cuboid_By_Key (HIC_Rendition const *in_nr, HC_KEY key, HIC_Point * min, HIC_Point * max) {
	
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;
	_hoops_AIGPR *	_hoops_RIGC = nr->_hoops_SRA->_hoops_RIGC;

	Bounding	_hoops_RCHS;

	_hoops_HPAH *	item = (_hoops_HPAH *)_hoops_RCSSR (_hoops_RIGC, key);
	HI_Find_Bounding (_hoops_RIGC, item, _hoops_RCHS);

	if (!_hoops_RCHS._hoops_HICAR()) {

		min->x = _hoops_RCHS->cuboid.min.x;
		min->y = _hoops_RCHS->cuboid.min.y;
		min->z = _hoops_RCHS->cuboid.min.z;

		max->x = _hoops_RCHS->cuboid.max.x;
		max->y = _hoops_RCHS->cuboid.max.y;
		max->z = _hoops_RCHS->cuboid.max.z;

		return true;
	}

	return false;
}

HC_EXTERNAL HIC_API bool HIC_Show_Camera_By_Key(HIC_Rendition const *in_nr, HC_KEY key, HIC_Point *position, HIC_Point *target, HIC_Vector *up_vector, float *width, float *height, int *projection)
{
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;
	_hoops_AIGPR *	_hoops_RIGC = nr->_hoops_SRA->_hoops_RIGC;

	_hoops_HPAH const * thing = (_hoops_HPAH const *)_hoops_RCSSR (_hoops_RIGC, key);
	_hoops_CRCP const * _hoops_SRCP = (_hoops_CRCP const*)thing;

	Attribute const *           _hoops_HPHCR;

	if ((_hoops_HPHCR = _hoops_SRCP->_hoops_IPPGR) != null) do {

		if (_hoops_HPHCR->type > HK_CAMERA)
			break;

		if (_hoops_HPHCR->type == HK_CAMERA)
		{
			_hoops_HHRA const * _hoops_SPH = (_hoops_HHRA const*)_hoops_HPHCR;

			if (position) {
				position->x = _hoops_SPH->position.x;
				position->y = _hoops_SPH->position.y;
				position->z = _hoops_SPH->position.z;
			}
			if (target) {
				target->x = _hoops_SPH->target.x;
				target->y = _hoops_SPH->target.y;
				target->z = _hoops_SPH->target.z;
			}
			if (up_vector) {
				up_vector->x = _hoops_SPH->up_vector.x;
				up_vector->y = _hoops_SPH->up_vector.y;
				up_vector->z = _hoops_SPH->up_vector.z;
			}
			if (width)
				*width = _hoops_SPH->_hoops_ISPA;
			if (height)
				*height = _hoops_SPH->_hoops_SSPA;

			if (projection)
				*projection = _hoops_SPH->projection;

			return true;
		}

	} while ((_hoops_HPHCR = _hoops_HPHCR->next) != null);

	return false; 

}

HC_EXTERNAL HIC_API bool HIC_Is_Selection(HIC_Rendition const *nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)nr;
	return _hoops_PCPPI->_hoops_SRA->_hoops_APHHP != null;
}


HC_EXTERNAL HIC_API bool HIC_PShow_One_Net_User_Option(HIC_Rendition const *in_nr, int count, Key const * keys, char const * uoname, char * options)
{
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;
	_hoops_AIGPR *	_hoops_RIGC = nr->_hoops_SRA->_hoops_RIGC;
	return HI_PShow_One_Net_User_Option(_hoops_RIGC, count, keys, uoname, options);
}

HC_EXTERNAL HIC_API bool HIC_Show_One_User_Option_By_Key(HIC_Rendition const *in_nr, Key key, char const * uoname, char * options)
{
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;
	_hoops_AIGPR *	_hoops_RIGC = nr->_hoops_SRA->_hoops_RIGC;
	return HI_Show_One_User_Option_By_Key(_hoops_RIGC, key, uoname, options);
}

HC_EXTERNAL HIC_API void HIC_PShow_One_Net_User_Data(HIC_Rendition const *in_nr, int count, HC_KEY const * keys, 
	HC_POINTER_SIZED_INT index, void * data, long data_length, long * data_length_out)
{
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;
	_hoops_AIGPR *	_hoops_RIGC = nr->_hoops_SRA->_hoops_RIGC;
	HI_PShow_One_Net_User_Data(_hoops_RIGC, count, keys, index, data, data_length, data_length_out);
}

HC_EXTERNAL HIC_API void HIC_Show_One_User_Data_By_Key(HIC_Rendition const *in_nr, HC_KEY key, 
	HC_POINTER_SIZED_INT index, void * data, long data_length, long * data_length_out)
{
	Net_Rendition const &	nr = *(Net_Rendition const *)in_nr;
	_hoops_AIGPR *	_hoops_RIGC = nr->_hoops_SRA->_hoops_RIGC;
	HI_Show_One_User_Data_By_Key(_hoops_RIGC, key, index, data, data_length, data_length_out);
}


HC_EXTERNAL HIC_API float HIC_Get_Current_Segment_Extent(HIC_Rendition const *in_nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)in_nr;
	return _hoops_PCPPI->_hoops_SRA->_hoops_AHSI->_hoops_CIHS;
}

HC_EXTERNAL HIC_API void HIC_Prune_Segment(HIC_Rendition const *in_nr)
{
	Net_Rendition const & _hoops_PCPPI = *(Net_Rendition const *)in_nr;
	_hoops_PCPPI->_hoops_SRA->_hoops_AHSI->stage = _hoops_ACHCP;
}

HC_EXTERNAL HIC_API HC_POINTER_SIZED_INT HIC_Driver_Get_Surface(HIC_Rendition const *nr)
{
	return (HC_POINTER_SIZED_INT)HIC_Intermediate_Utility (nr, _hoops_IPHGR, 0, IM_NO_VALUES);
}


#endif //_hoops_SAHPI




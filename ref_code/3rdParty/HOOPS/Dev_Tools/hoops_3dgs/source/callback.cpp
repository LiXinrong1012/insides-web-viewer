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
 * $Id: obf_tmp.txt 1.140 2010-11-18 00:59:02 jason Exp $
 */

#include "hoops.h"
#include "database.h"
#include "hi_proto.h"
#include "hc_proto.h"
#include "searchh.h"
#include "hpserror.h"

#ifndef DISABLE_CALLBACKS

local const _hoops_IGRCR _hoops_CGRCR[] = {
	{_hoops_SGRCR,			_hoops_GRRCR ("redraw"),			_hoops_RRRCR, 0, true},
	{_hoops_SGRCR,			_hoops_GRRCR ("redraws"),			_hoops_RRRCR, 0, true},

	{_hoops_ARRCR,	_hoops_GRRCR ("draw dc marker"),	_hoops_PRRCR, 1, false},
	{_hoops_ARRCR,	_hoops_GRRCR ("draw dc markers"),	_hoops_PRRCR, 1, false},
	{_hoops_HRRCR,	_hoops_GRRCR ("draw dc polyline"),	_hoops_PRRCR, 1, false},
	{_hoops_HRRCR,	_hoops_GRRCR ("draw dc polylines"), _hoops_PRRCR, 1, false},
	{_hoops_IRRCR,		_hoops_GRRCR ("draw dc edge"),		_hoops_PRRCR, 1, false},
	{_hoops_IRRCR,		_hoops_GRRCR ("draw dc edges"),		_hoops_PRRCR, 1, false},
	{_hoops_CRRCR,		_hoops_GRRCR ("draw dc face"),		_hoops_PRRCR, 1, false},
	{_hoops_CRRCR,		_hoops_GRRCR ("draw dc faces"),		_hoops_PRRCR, 1, false},


	{_hoops_SRRCR,		_hoops_GRRCR ("draw dc colorized face"),_hoops_PRRCR, 1, false},
	{_hoops_SRRCR,		_hoops_GRRCR ("draw dc colorized faces"),_hoops_PRRCR, 1, false},
	{_hoops_GARCR,		_hoops_GRRCR ("draw dc colorized marker"),_hoops_PRRCR, 1, false},
	{_hoops_GARCR,		_hoops_GRRCR ("draw dc colorized markers"),_hoops_PRRCR, 1, false},

	{_hoops_RARCR,					_hoops_GRRCR ("draw dc line"),_hoops_PRRCR, 1, false},
	{_hoops_RARCR,					_hoops_GRRCR ("draw dc lines"),_hoops_PRRCR, 1, false},
	{_hoops_AARCR,		_hoops_GRRCR ("draw dc colorized line"),_hoops_PRRCR, 1, false},
	{_hoops_AARCR,		_hoops_GRRCR ("draw dc colorized lines"),_hoops_PRRCR, 1, false},
	{_hoops_PARCR,			_hoops_GRRCR ("draw dc gouraud line"),_hoops_PRRCR, 1, false},
	{_hoops_PARCR,			_hoops_GRRCR ("draw dc gouraud lines"),_hoops_PRRCR, 1, false},
	{_hoops_HARCR,			_hoops_GRRCR ("draw dc reshaded line"),_hoops_PRRCR, 1, false},
	{_hoops_HARCR,			_hoops_GRRCR ("draw dc reshaded lines"),_hoops_PRRCR, 1, false},
	{_hoops_IARCR,				_hoops_GRRCR ("draw dc triangle"),_hoops_PRRCR, 1, false},
	{_hoops_IARCR,				_hoops_GRRCR ("draw dc triangles"),_hoops_PRRCR, 1, false},
	{_hoops_CARCR,	_hoops_GRRCR ("draw dc colorized triangle"),_hoops_PRRCR, 1, false},
	{_hoops_CARCR,	_hoops_GRRCR ("draw dc colorized triangles"),_hoops_PRRCR, 1, false},
	{_hoops_SARCR,		_hoops_GRRCR ("draw dc gouraud triangle"),_hoops_PRRCR, 1, false},
	{_hoops_SARCR,		_hoops_GRRCR ("draw dc gouraud triangles"),_hoops_PRRCR, 1, false},
	{_hoops_GPRCR,		_hoops_GRRCR ("draw dc reshaded triangle"),_hoops_PRRCR, 1, false},
	{_hoops_GPRCR,		_hoops_GRRCR ("draw dc reshaded triangles"),_hoops_PRRCR, 1, false},


	{_hoops_RPRCR,			_hoops_GRRCR ("draw dc polytriangle"),_hoops_PRRCR, 1, false},
	{_hoops_RPRCR,			_hoops_GRRCR ("draw dc polytriangles"),_hoops_PRRCR, 1, false},
	{_hoops_APRCR,_hoops_GRRCR ("draw dc colorized polytriangle"),_hoops_PRRCR, 1, false},
	{_hoops_APRCR,_hoops_GRRCR ("draw dc colorized polytriangles"),_hoops_PRRCR, 1, false},
	{_hoops_PPRCR,	_hoops_GRRCR ("draw dc gouraud polytriangle"),_hoops_PRRCR, 1, false},
	{_hoops_PPRCR,	_hoops_GRRCR ("draw dc gouraud polytriangles"),_hoops_PRRCR, 1, false},
	{_hoops_HPRCR,	_hoops_GRRCR ("draw dc phong polytriangle"),_hoops_PRRCR, 1, false},
	{_hoops_HPRCR,	_hoops_GRRCR ("draw dc phong polytriangles"),_hoops_PRRCR, 1, false},
	{_hoops_IPRCR, _hoops_GRRCR ("draw dc textured polytriangle"),_hoops_PRRCR, 1, false},
	{_hoops_IPRCR, _hoops_GRRCR ("draw dc textured polytriangles"),_hoops_PRRCR, 1, false},
	{_hoops_HRRCR,				_hoops_GRRCR ("draw dc polyline"),_hoops_PRRCR, 1, false},
	{_hoops_HRRCR,				_hoops_GRRCR ("draw dc polylines"),_hoops_PRRCR, 1, false},
	{_hoops_CPRCR,	_hoops_GRRCR ("draw dc colorized polyline"),_hoops_PRRCR, 1, false},
	{_hoops_CPRCR,	_hoops_GRRCR ("draw dc colorized polylines"),_hoops_PRRCR, 1, false},
	{_hoops_SPRCR,		_hoops_GRRCR ("draw dc gouraud polyline"),_hoops_PRRCR, 1, false},
	{_hoops_SPRCR,		_hoops_GRRCR ("draw dc gouraud polylines"),_hoops_PRRCR, 1, false},
	{_hoops_GHRCR,		_hoops_GRRCR ("draw dc phong polyline"),_hoops_PRRCR, 1, false},
	{_hoops_GHRCR,		_hoops_GRRCR ("draw dc phong polylines"),_hoops_PRRCR, 1, false},
	{_hoops_RHRCR,		_hoops_GRRCR ("draw dc textured polyline"),_hoops_PRRCR, 1, false},
	{_hoops_RHRCR,		_hoops_GRRCR ("draw dc textured polylines"),_hoops_PRRCR, 1, false},
	{_hoops_AHRCR,			_hoops_GRRCR ("draw dc polymarker"),_hoops_PRRCR, 1, false},
	{_hoops_AHRCR,			_hoops_GRRCR ("draw dc polymarkers"),_hoops_PRRCR, 1, false},
	{_hoops_PHRCR,	_hoops_GRRCR ("draw dc colorized polymarker"),_hoops_PRRCR, 1, false},
	{_hoops_PHRCR,	_hoops_GRRCR ("draw dc colorized polymarkers"),_hoops_PRRCR, 1, false},



	{_hoops_HHRCR,_hoops_GRRCR ("draw dc text stroke"), _hoops_PRRCR, 1, false},
	{_hoops_HHRCR,_hoops_GRRCR ("draw dc text strokes"),_hoops_PRRCR, 1, false},
	{_hoops_IHRCR,_hoops_GRRCR ("draw dc text area"), _hoops_PRRCR, 1, false},
	{_hoops_IHRCR,_hoops_GRRCR ("draw dc text areas"),_hoops_PRRCR, 1, false},

	{_hoops_CHRCR,		_hoops_GRRCR ("draw window"),		_hoops_PRRCR, 1, false},
	{_hoops_CHRCR,		_hoops_GRRCR ("draw windows"),		_hoops_PRRCR, 1, false},
	{_hoops_SHRCR, _hoops_GRRCR ("draw window frame"), _hoops_PRRCR, 1, false},
	{_hoops_SHRCR, _hoops_GRRCR ("draw window frames"),_hoops_PRRCR, 1, false},

	{_hoops_GIRCR,			_hoops_GRRCR ("draw text"),			_hoops_PRRCR, 1, false},

	{_hoops_RIRCR,	_hoops_GRRCR ("draw 3d marker"),	_hoops_PRRCR, 1, false},
	{_hoops_RIRCR,	_hoops_GRRCR ("draw 3d markers"),	_hoops_PRRCR, 1, false},
	{_hoops_AIRCR,	_hoops_GRRCR ("draw 3d polyline"),	_hoops_PRRCR, 1, false},
	{_hoops_AIRCR,	_hoops_GRRCR ("draw 3d polylines"), _hoops_PRRCR, 1, false},
	{_hoops_PIRCR,	_hoops_GRRCR ("draw 3d infinite line"), _hoops_PRRCR, 1, false},
	{_hoops_PIRCR,	_hoops_GRRCR ("draw 3d infinite lines"), _hoops_PRRCR, 1, false},
	{_hoops_HIRCR,	_hoops_GRRCR ("draw 3d polygon"),	_hoops_PRRCR, 1, false},
	{_hoops_HIRCR,	_hoops_GRRCR ("draw 3d polygons"),	_hoops_PRRCR, 1, false},
	{_hoops_IIRCR,		_hoops_GRRCR ("draw 3d text"),		_hoops_PRRCR, 1, false},
	{_hoops_CIRCR,		_hoops_GRRCR ("draw 3d image"),		_hoops_PRRCR, 1, false},
	{_hoops_CIRCR,		_hoops_GRRCR ("draw 3d images"),	_hoops_PRRCR, 1, false},
	{_hoops_SIRCR,		_hoops_GRRCR ("draw 3d grid"),		_hoops_PRRCR, 1, false},
	{_hoops_SIRCR,		_hoops_GRRCR ("draw 3d grids"),		_hoops_PRRCR, 1, false},
	{_hoops_GCRCR,	_hoops_GRRCR ("draw 3d polyhedron"),	_hoops_PRRCR, 1, false},
	{_hoops_GCRCR,	_hoops_GRRCR ("draw 3d mesh"),		_hoops_PRRCR, 1, false},
	{_hoops_GCRCR,	_hoops_GRRCR ("draw 3d meshes"),	_hoops_PRRCR, 1, false},
	{_hoops_GCRCR,	_hoops_GRRCR ("draw 3d shell"),		_hoops_PRRCR, 1, false},
	{_hoops_GCRCR,	_hoops_GRRCR ("draw 3d shells"),	_hoops_PRRCR, 1, false},
	{_hoops_RCRCR,	_hoops_GRRCR ("draw 3d ellipse"),	_hoops_PRRCR, 1, false},
	{_hoops_RCRCR,	_hoops_GRRCR ("draw 3d ellipses"),	_hoops_PRRCR, 1, false},
	{_hoops_ACRCR,	_hoops_GRRCR ("draw 3d elliptical arc"),	_hoops_PRRCR, 1, false},
	{_hoops_ACRCR,	_hoops_GRRCR ("draw 3d elliptical arcs"),	_hoops_PRRCR, 1, false},
	{_hoops_PCRCR,	_hoops_GRRCR ("draw 3d polyedge"),	_hoops_PRRCR, 1, false},
	{_hoops_PCRCR,	_hoops_GRRCR ("draw 3d polyedges"), _hoops_PRRCR, 1, false},
	{_hoops_HCRCR,_hoops_GRRCR ("draw 3d polymarker"), _hoops_PRRCR, 1, false},
	{_hoops_HCRCR,_hoops_GRRCR ("draw 3d polymarkers"), _hoops_PRRCR, 1, false},
	{_hoops_ICRCR,	_hoops_GRRCR ("draw 3d tristrip"),	_hoops_PRRCR, 1, false},
	{_hoops_ICRCR,	_hoops_GRRCR ("draw 3d tristrips"), _hoops_PRRCR, 1, false},
	{_hoops_CCRCR,	_hoops_GRRCR ("draw 3d sphere"),	_hoops_PRRCR, 1, false},
	{_hoops_CCRCR,	_hoops_GRRCR ("draw 3d spheres"),	_hoops_PRRCR, 1, false},
	{_hoops_SCRCR,	_hoops_GRRCR ("draw 3d cylinder"),	_hoops_PRRCR, 1, false},
	{_hoops_SCRCR,	_hoops_GRRCR ("draw 3d cylinders"), _hoops_PRRCR, 1, false},
	{_hoops_GSRCR,	_hoops_GRRCR ("draw 3d polycylinder"),	_hoops_PRRCR, 1, false},
	{_hoops_GSRCR,	_hoops_GRRCR ("draw 3d polycylinders"), _hoops_PRRCR, 1, false},
	{_hoops_RSRCR,		_hoops_GRRCR ("draw 3d nurbs curve"),		_hoops_PRRCR, 1, false},
	{_hoops_RSRCR,		_hoops_GRRCR ("draw 3d nurbs curves"),		_hoops_PRRCR, 1, false},
	{_hoops_ASRCR,	_hoops_GRRCR ("draw 3d nurbs surface"),		_hoops_PRRCR, 1, false},
	{_hoops_ASRCR,	_hoops_GRRCR ("draw 3d nurbs surfaces"),	_hoops_PRRCR, 1, false},
	{_hoops_RSRCR,		_hoops_GRRCR ("draw 3d curve"),		_hoops_PRRCR, 1, false},
	{_hoops_RSRCR,		_hoops_GRRCR ("draw 3d curves"),	_hoops_PRRCR, 1, false},
	{_hoops_ASRCR,	_hoops_GRRCR ("draw 3d surface"),	_hoops_PRRCR, 1, false},
	{_hoops_ASRCR,	_hoops_GRRCR ("draw 3d surfaces"),	_hoops_PRRCR, 1, false},
	{_hoops_PSRCR,	_hoops_GRRCR ("draw 3d geometry"),	_hoops_PRRCR, 1, false},

	{_hoops_HSRCR,_hoops_GRRCR ("draw 3d text stroke"), _hoops_PRRCR, 1, false},
	{_hoops_HSRCR,_hoops_GRRCR ("draw 3d text strokes"),_hoops_PRRCR, 1, false},
	{_hoops_ISRCR,_hoops_GRRCR ("draw 3d text area"), _hoops_PRRCR, 1, false},
	{_hoops_ISRCR,_hoops_GRRCR ("draw 3d text areas"),_hoops_PRRCR, 1, false},

	{_hoops_CSRCR,		_hoops_GRRCR ("draw segment"),		_hoops_PRRCR, 1, false},
	{_hoops_CSRCR,		_hoops_GRRCR ("draw segments"),		_hoops_PRRCR, 1, false},
	{_hoops_SSRCR, _hoops_GRRCR ("draw segment tree"), _hoops_PRRCR, 1, false},

	{_hoops_GGACR,	_hoops_GRRCR ("select 3d marker"),	_hoops_PRRCR, 1, false},
	{_hoops_GGACR,	_hoops_GRRCR ("select 3d markers"), _hoops_PRRCR, 1, false},
	{_hoops_RGACR,_hoops_GRRCR ("select 3d polyline"),_hoops_PRRCR, 1, false},
	{_hoops_RGACR,_hoops_GRRCR ("select 3d polylines"),_hoops_PRRCR, 1, false},
	{_hoops_AGACR, _hoops_GRRCR ("select 3d polygon"), _hoops_PRRCR, 1, false},
	{_hoops_AGACR, _hoops_GRRCR ("select 3d polygons"),_hoops_PRRCR, 1, false},
	{_hoops_PGACR,	_hoops_GRRCR ("select 3d text"),	_hoops_PRRCR, 1, false},
	{_hoops_HGACR,_hoops_GRRCR ("select 3d geometry"),_hoops_PRRCR, 1, false},

	{_hoops_IGACR,		_hoops_GRRCR ("select text"),		_hoops_PRRCR, 1, false},

	{_hoops_CGACR,		_hoops_GRRCR ("select window"),		_hoops_PRRCR, 1, false},
	{_hoops_CGACR,		_hoops_GRRCR ("select windows"),	_hoops_PRRCR, 1, false},

	{_hoops_SGACR,	_hoops_GRRCR ("select segment"),	_hoops_PRRCR, 1, false},
	{_hoops_SGACR,	_hoops_GRRCR ("select segments"),	_hoops_PRRCR, 1, false},
	{_hoops_GRACR,_hoops_GRRCR ("select segment tree"),_hoops_PRRCR, 1, false},

	{_hoops_RRACR,	_hoops_GRRCR ("driver startup"),	_hoops_PRRCR, 1, false},
	{_hoops_ARACR,	_hoops_GRRCR ("driver shutdown"),	_hoops_PRRCR, 1, false},

	{_hoops_PRACR,	_hoops_GRRCR ("draw dc cut line"),	_hoops_PRRCR, 1, false},
	{_hoops_PRACR,	_hoops_GRRCR ("draw dc cut lines"), _hoops_PRRCR, 1, false},
	{_hoops_HRACR,	_hoops_GRRCR ("draw 3d isoline"),	_hoops_PRRCR, 1, false},
	{_hoops_HRACR,	_hoops_GRRCR ("draw 3d isolines"), _hoops_PRRCR, 1, false},

	{_hoops_IRACR,		_hoops_GRRCR ("hlr polyline"),	_hoops_PRRCR, 1, false},
	{_hoops_IRACR,		_hoops_GRRCR ("hlr polylines"), _hoops_PRRCR, 1, false},
	{_hoops_CRACR,		_hoops_GRRCR ("hlr marker"),  _hoops_PRRCR, 1, false},
	{_hoops_CRACR,		_hoops_GRRCR ("hlr markers"), _hoops_PRRCR, 1, false},

	{_hoops_SRACR,_hoops_GRRCR ("hlr hidden polyline"),	_hoops_PRRCR, 1, false},
	{_hoops_SRACR,_hoops_GRRCR ("hlr hidden polylines"), _hoops_PRRCR, 1, false},
	{_hoops_GAACR,	 _hoops_GRRCR ("hlr hidden marker"),  _hoops_PRRCR, 1, false},
	{_hoops_GAACR,	 _hoops_GRRCR ("hlr hidden markers"), _hoops_PRRCR, 1, false},

	/* _hoops_RAACR _hoops_IH _hoops_SPCHR _hoops_AAACR (_hoops_CAS _hoops_HAR _hoops_HGAS, _hoops_PII "_hoops_HAIHR _hoops_HCGR") */
	{_hoops_GGACR,	   _hoops_GRRCR ("select marker"),	_hoops_PRRCR, 1, false},
	{_hoops_GGACR,	   _hoops_GRRCR ("select markers"), _hoops_PRRCR, 1, false},
	{_hoops_RGACR,   _hoops_GRRCR ("select polyline"),_hoops_PRRCR, 1, false},
	{_hoops_RGACR,   _hoops_GRRCR ("select polylines"),_hoops_PRRCR, 1, false},
	{_hoops_AGACR,	   _hoops_GRRCR ("select polygon"), _hoops_PRRCR, 1, false},
	{_hoops_AGACR,	   _hoops_GRRCR ("select polygons"),		_hoops_PRRCR, 1, false},
	{_hoops_HGACR,   _hoops_GRRCR ("select geometry"),		_hoops_PRRCR, 1, false},

	{_hoops_PAACR,	_hoops_GRRCR ("finish picture"),	_hoops_PRRCR, 1, false},

	{_hoops_HAACR,		_hoops_GRRCR ("create region"),		_hoops_PRRCR, 1, false},
	{_hoops_IAACR,		_hoops_GRRCR ("save region"),		_hoops_PRRCR, 1, false},
	{_hoops_CAACR,	_hoops_GRRCR ("restore region"),	_hoops_PRRCR, 1, false},
	{_hoops_SAACR,	_hoops_GRRCR ("destroy region"),	_hoops_PRRCR, 1, false},


	{_hoops_GPACR,	_hoops_GRRCR ("segment activity change"),	_hoops_PRRCR, 1, false},
	{_hoops_RPACR,	_hoops_GRRCR ("draw 3d contour"),	_hoops_PRRCR, 1, false},

	{_hoops_APACR,	_hoops_GRRCR ("populate segment"),	_hoops_PRRCR, 1, false},
	{_hoops_PPACR,		_hoops_GRRCR ("set shader"),		_hoops_PRRCR, 1, false},

	{_hoops_HPACR,	_hoops_GRRCR ("process segment"),	_hoops_PRRCR, 1, false},
};


local Attribute * _hoops_IPACR (
	_hoops_AIGPR *		_hoops_RIGC,
	_hoops_HPAH alter *			item,
	Attribute const *			_hoops_CPACR,
	Attribute alter *			_hoops_SPACR)
{
	_hoops_GCHIR const *			_hoops_GHACR = (_hoops_GCHIR const *)_hoops_CPACR;
	_hoops_GCHIR alter *			_hoops_RHACR = (_hoops_GCHIR alter *)_hoops_SPACR;

	UNREFERENCED (_hoops_RIGC);
	UNREFERENCED (item);

	if (_hoops_GHACR == null || _hoops_GHACR->_hoops_ACHIR == null) {
		// _hoops_ISAP _hoops_IS _hoops_AA 
	}
	else if (_hoops_RHACR->_hoops_ACHIR == null) {
		/* _hoops_AHACR _hoops_HICP; _hoops_PHACR _hoops_HRGR _hoops_RHPA; _hoops_HAR _hoops_HHACR _hoops_PA */
		return null;
	}
	else { /* _hoops_PIHA _hoops_HASC */

		/* _hoops_ISPR _hoops_IS _hoops_CACH _hoops_RPP _hoops_RH _hoops_CCAH _hoops_HIGR _hoops_ICGI _hoops_GII _hoops_IAHP _hoops_HII _hoops_RH _hoops_RHGS */

		_hoops_IHACR *	_hoops_CHACR = _hoops_RHACR->_hoops_ACHIR;
		_hoops_IHACR *	_hoops_SHACR = _hoops_GHACR->_hoops_ACHIR;

		_hoops_PCCAR {
			while (_hoops_SHACR->type < _hoops_CHACR->type)
				if ((_hoops_SHACR = _hoops_SHACR->next) == null) 
					goto _hoops_PCPPR;

			if (_hoops_SHACR->type != _hoops_CHACR->type || _hoops_SHACR->name != _hoops_CHACR->name)
				break;

			if ((_hoops_CHACR = _hoops_CHACR->next) == null) {
				/* _hoops_RPAPR. */
				return null;
			}
		}
		_hoops_PCPPR:;

		/* _hoops_HA _hoops_IPS _hoops_PPR _hoops_HASC _hoops_IH _hoops_HPHR */

		_hoops_IHACR *	_hoops_GIACR = HI_Merge_Callback_Lists (_hoops_GHACR->_hoops_ACHIR, _hoops_RHACR->_hoops_ACHIR);

		HI_Free_Callback_List (_hoops_RHACR->_hoops_ACHIR);

		_hoops_RHACR->_hoops_ACHIR = _hoops_GIACR;
	}

	return _hoops_RHACR;
}


local bool _hoops_RIACR (
	_hoops_AIGPR *		_hoops_RIGC,
	char const *				list,
	_hoops_IHACR * &			_hoops_ACHIR,
	void const *				_hoops_AIACR) 
{
	Option_Value *				option_list;
	Option_Value *				option;
	bool						_hoops_PIACR = false;

	_hoops_ACHIR = null;

	_hoops_HIACR (_hoops_IIACR, _hoops_CGRCR);

	if (!HI_Parse_Options (_hoops_RIGC, list, _hoops_CIACR (_hoops_IIACR), &option_list, _hoops_SIACR))
		return false;

	if ((option = option_list) != null) do {
		if (option->type->id == _hoops_SGRCR) {
			_hoops_PIACR = option->_hoops_GCACR;
			break;
		}
	} while ((option = option->next) != null);

	if ((option = option_list) != null) do if (option->type->id != _hoops_SGRCR) {
		_hoops_IHACR **	_hoops_ASRGR;
		_hoops_IHACR *		_hoops_RCACR=0;

		_hoops_ASRGR = &_hoops_ACHIR;
		_hoops_PCCAR {
			if ((_hoops_RCACR = *_hoops_ASRGR) == null) {
				ALLOC (_hoops_RCACR, _hoops_IHACR);
				_hoops_RCACR->next = null;
				*_hoops_ASRGR = _hoops_RCACR;
				break;
			}
			else if (_hoops_RCACR->type >= option->type->id) {
				if (_hoops_RCACR->type == option->type->id) {
					_hoops_HPRH (_hoops_RCACR->name);
				}
				else {
					ALLOC (_hoops_RCACR, _hoops_IHACR);
					_hoops_RCACR->next = *_hoops_ASRGR;
					*_hoops_ASRGR = _hoops_RCACR;
				}
				break;
			}

			_hoops_ASRGR = &_hoops_RCACR->next;
		}

		_hoops_RCACR->type = (int)option->type->id;
		_hoops_RCACR->_hoops_AIACR = _hoops_AIACR;
		_hoops_RCACR->_hoops_PIACR = _hoops_PIACR;

		if ((_hoops_RCACR->name = *HI_Look_Up_Callback_Name (_hoops_RIGC,
									 option->value._name[0].text,
									 option->value._name[0].length)) == null) {

			HE_ERROR2 (HEC_CALLBACK, HES_INVALID_INPUT,
					   Sprintf_N (null, "'%n' is not a recognized routine name -", &option->value._name[0]),
					   "Define_Callback_Name needs to be called first");

			/* _hoops_ACACR _hoops_PCACR... */

			/* _hoops_HCACR _hoops_RH _hoops_SCGR _hoops_SPR _hoops_ICACR, _hoops_CR _hoops_RGCI _hoops_RSIRR
			 * _hoops_CCACR'_hoops_RA _hoops_RPII _hoops_PAPR _hoops_GAPR.
			 */
			*_hoops_ASRGR = _hoops_RCACR->next;
			FREE (_hoops_RCACR, _hoops_IHACR);

			/* _hoops_SCACR */
			HI_Free_Callback_List (_hoops_ACHIR);
			HI_Free_Option_List (_hoops_RIGC, option_list);
			return false;
		}
		else
			_hoops_PRRH (_hoops_RCACR->name);
	} while ((option = option->next) != null);

	HI_Free_Option_List (_hoops_RIGC, option_list);

	return true;
}	
#endif


GLOBAL_FUNCTION bool HI_Set_Callback(
	_hoops_AIGPR *	_hoops_RIGC, 
	_hoops_HPAH *				item, 
	_hoops_GCHIR *				callback)
{
	return HI_Set_Attribute (_hoops_RIGC, item, HK_CALLBACK, _hoops_IPACR, callback);
}


HC_INTERFACE void HC_CDECL HC_Set_Callback (
	char const *			list)
{
	_hoops_PAPPR context("Set_Callback");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Callback (%S);\n", list));
	);

	bool		used = false;
	_hoops_GCHIR *	callback;
	ZALLOC (callback, _hoops_GCHIR);

	if (_hoops_RIACR (context,  list, callback->_hoops_ACHIR, null)) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_GSACR)) != null) {
			used = HI_Set_Callback(context, target, callback);
			_hoops_IRRPR();
		}
	}
	
	if (!used) {
		if (callback->_hoops_ACHIR != null)
			HI_Free_Callback_List (callback->_hoops_ACHIR);
		FREE(callback, _hoops_GCHIR);
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_Set_Callback_With_Data (
	char const *			list,
	void const *			data)
{
	_hoops_PAPPR context("Set_Callback_With_Data");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_Set_Callback_With_Data (%S,", list));
		HI_Dump_Code (Sprintf_LD (null, "0x%X);\n", data));
	);

	bool		used = false;
	_hoops_GCHIR *	callback;
	ZALLOC (callback, _hoops_GCHIR);

	if (_hoops_RIACR (context,  list, callback->_hoops_ACHIR, data)) {

		_hoops_HPAH * target;
		if ((target = HI_Find_Target_And_Lock(context, _hoops_GSACR)) != null) {
			used = HI_Set_Callback(context, target, callback);
			_hoops_IRRPR();
		}
	}

	if (!used) {
		if (callback->_hoops_ACHIR != null)
			HI_Free_Callback_List (callback->_hoops_ACHIR);
		FREE(callback, _hoops_GCHIR);
	}
#endif
}


HC_INTERFACE void HC_CDECL HC_UnSet_Callback (void) 
{
	_hoops_PAPPR context("UnSet_Callback");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
	CODE_GENERATION (
		HI_Dump_Code ("HC_UnSet_Callback ();\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_GSACR|_hoops_GSIIR)) != null) {
		HI_UnSet_Attribute(context, target, HK_CALLBACK);
		_hoops_IRRPR();
	}
#endif
}




GLOBAL_FUNCTION _hoops_IHACR * HI_Copy_Callback_List (
	_hoops_IHACR const *	in) {
#ifndef DISABLE_CALLBACKS
	_hoops_IHACR			_hoops_GGHPR;
	_hoops_IHACR *			_hoops_PAGR = &_hoops_GGHPR;

	if (in != null) do {
		ALLOC (_hoops_PAGR->next, _hoops_IHACR);
		_hoops_PAGR = _hoops_PAGR->next;
		_hoops_PAGR->type = in->type;
		_hoops_PAGR->name = in->name;
		_hoops_PRRH (_hoops_PAGR->name);
		_hoops_PAGR->_hoops_PIACR = in->_hoops_PIACR;
		_hoops_PAGR->_hoops_AIACR = in->_hoops_AIACR;
	} while ((in = in->next) != null);

	_hoops_PAGR->next = null;
	return _hoops_GGHPR.next;
#else
	return null;
#endif
}

GLOBAL_FUNCTION void HI_Free_Callback_List (
	_hoops_IHACR *			item) {
#ifndef DISABLE_CALLBACKS
	_hoops_IHACR *			next;

	if (item != null) do {
		_hoops_HPRH (item->name);
		next = item->next;
		FREE (item, _hoops_IHACR);
	} while ((item = next) != null);
#endif
}

GLOBAL_FUNCTION _hoops_IHACR * HI_Merge_Callback_Lists (
	_hoops_IHACR const *	_hoops_RSACR,
	_hoops_IHACR const *	_hoops_ASACR) {
#ifndef DISABLE_CALLBACKS
	_hoops_IHACR			_hoops_GGHPR;
	_hoops_IHACR *			_hoops_PSACR = &_hoops_GGHPR;

	_hoops_PCCAR {
		while (_hoops_ASACR->type < _hoops_RSACR->type) {
			/* _hoops_IRAA _hoops_HII _hoops_CPAC */
			ALLOC (_hoops_PSACR->next, _hoops_IHACR);
			_hoops_PSACR = _hoops_PSACR->next;
			_hoops_PSACR->type = _hoops_ASACR->type;
			_hoops_PSACR->name = _hoops_ASACR->name;
			_hoops_PRRH (_hoops_PSACR->name);
			_hoops_PSACR->_hoops_PIACR = _hoops_ASACR->_hoops_PIACR;
			_hoops_PSACR->_hoops_AIACR = _hoops_ASACR->_hoops_AIACR;
			if ((_hoops_ASACR = _hoops_ASACR->next) == null) {
				_hoops_PSACR->next = HI_Copy_Callback_List (_hoops_RSACR);
				return _hoops_GGHPR.next;
			}
		}
		while (_hoops_ASACR->type > _hoops_RSACR->type) {
			/* _hoops_IRAA _hoops_HII _hoops_RPAC */
			ALLOC (_hoops_PSACR->next, _hoops_IHACR);
			_hoops_PSACR = _hoops_PSACR->next;
			_hoops_PSACR->type = _hoops_RSACR->type;
			_hoops_PSACR->name = _hoops_RSACR->name;
			_hoops_PRRH (_hoops_PSACR->name);
			_hoops_PSACR->_hoops_PIACR = _hoops_RSACR->_hoops_PIACR;
			_hoops_PSACR->_hoops_AIACR = _hoops_RSACR->_hoops_AIACR;
			if ((_hoops_RSACR = _hoops_RSACR->next) == null) {
				_hoops_PSACR->next = HI_Copy_Callback_List (_hoops_ASACR);
				return _hoops_GGHPR.next;
			}
		}
		while (_hoops_ASACR->type == _hoops_RSACR->type) {
			/* _hoops_IRAA _hoops_HII _hoops_CPAC, _hoops_PH _hoops_GIPR */
			ALLOC (_hoops_PSACR->next, _hoops_IHACR);
			_hoops_PSACR = _hoops_PSACR->next;
			_hoops_PSACR->type = _hoops_ASACR->type;
			_hoops_PSACR->name = _hoops_ASACR->name;
			_hoops_PRRH (_hoops_PSACR->name);
			_hoops_PSACR->_hoops_PIACR = _hoops_ASACR->_hoops_PIACR;
			_hoops_PSACR->_hoops_AIACR = _hoops_ASACR->_hoops_AIACR;
			if ((_hoops_ASACR = _hoops_ASACR->next) == null) {
				_hoops_PSACR->next = HI_Copy_Callback_List (_hoops_RSACR->next);
				return _hoops_GGHPR.next;
			}
			if ((_hoops_RSACR = _hoops_RSACR->next) == null) {
				_hoops_PSACR->next = HI_Copy_Callback_List (_hoops_ASACR);
				return _hoops_GGHPR.next;
			}
		}
	}
#else
	return null;
#endif
}




/* _hoops_IRGGR _hoops_GPP _hoops_HSACR. */

#ifdef DISABLE_SHOW
#	ifdef DISABLE_METAFILE
#		ifdef DISABLE_CALLBACKS
#			define		_hoops_ISACR
#		endif
#	endif
#endif


GLOBAL_FUNCTION void HI_Show_Callback (
	_hoops_GCHIR *			callback,
	char *				spec,
	int					_hoops_CSACR,
	void **				_hoops_AIACR) {
#ifndef _hoops_ISACR
	_hoops_IHACR *		_hoops_RCACR;
	local char const	_hoops_SSACR[] = "Return string won't fit in provided space";
	bool				_hoops_GGPCR = false;

	if (_hoops_AIACR)
		*_hoops_AIACR=0;

	if ((_hoops_RCACR = callback->_hoops_ACHIR) == null)
		HI_Return_Chars (spec, _hoops_CSACR, "", 0);
	else {
		char			*_hoops_ASAPR = spec;
		char			*_hoops_PSAPR;

		if (_hoops_CSACR == -1)
			_hoops_PSAPR = _hoops_ASAPR + HOOPS_WORLD->_hoops_RAPPR;	/* _hoops_IHRPR _hoops_IAHA */
		else
			_hoops_PSAPR = _hoops_ASAPR + _hoops_CSACR;			/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */

		_hoops_PCCAR {
 			if (_hoops_AIACR)
				*_hoops_AIACR = (void *)_hoops_RCACR->_hoops_AIACR;

			switch (_hoops_RCACR->type) {
				case _hoops_ARRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc marker", null);
				}	break;

				case _hoops_IRRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc edge", null);
				}	break;

				case _hoops_CRRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc face", null);
				}	break;

				case _hoops_SRRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc colorized face", null);
				}	break;

				case _hoops_GARCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc colorized marker", null);
				}	break;

				case _hoops_RARCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc line", null);
				}	break;
				case _hoops_AARCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc colorized line", null);
				}	break;
				case _hoops_PARCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc gouraud line", null);
				}	break;
				case _hoops_HARCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc reshaded line", null);
				}	break;

				case _hoops_IARCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc triangle", null);
				}	break;
				case _hoops_CARCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc colorized triangle", null);
				}	break;
				case _hoops_SARCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc gouraud triangle", null);
				}	break;
				case _hoops_GPRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc reshaded triangle", null);
				}	break;

				case _hoops_RPRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc polytriangle", null);
				}	break;
				case _hoops_APRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc colorized polytriangle", null);
				}	break;
				case _hoops_PPRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc gouraud polytriangle", null);
				}	break;
				case _hoops_HPRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc phong polytriangle", null);
				}	break;
				case _hoops_IPRCR:
					{	_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc textured polytriangle", null);
				}	break;

				case _hoops_HRRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc polyline", null);
				}	break;
				case _hoops_CPRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc colorized polyline", null);
				}	break;
				case _hoops_SPRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc gouraud polyline", null);
				}	break;
				case _hoops_GHRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc phong polyline", null);
				}	break;
				case _hoops_RHRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc textured polyline", null);
				}	break;

				case _hoops_AHRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc polymarker", null);
				}	break;
				case _hoops_PHRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc colorized polymarker", null);
				}	break;

				case _hoops_HHRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc text stroke", null);
				}	break;
				case _hoops_IHRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc text area", null);
				}	break;

				case _hoops_CHRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw window", null);
				}	break;
				case _hoops_SHRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw window frame", null);
				}	break;

				case _hoops_GIRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw text", null);
				}	break;

				case _hoops_RIRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d marker", null);
				}	break;

				case _hoops_AIRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d polyline", null);
				}	break;

				case _hoops_PIRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d infinite line", null);
				}	break;

				case _hoops_HIRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d polygon", null);
				}	break;

				case _hoops_PCRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d polyedge", null);
				}	break;

				case _hoops_HCRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d polymarker", null);
				}	break;

				case _hoops_ICRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d tristrip", null);
				}	break;

				case _hoops_GCRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d polyhedron", null);
				}	break;

				case _hoops_IIRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d text", null);
				}	break;

				case _hoops_CIRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d image", null);
				}	break;

				case _hoops_SIRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d grid", null);
				}	break;

				case _hoops_RCRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d ellipse", null);
				}	break;

				case _hoops_ACRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d elliptical arc", null);
				}	break;

				case _hoops_PSRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d geometry", null);
				}	break;

				case _hoops_HSRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d text stroke", null);
				}	break;

				case _hoops_ISRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d text area", null);
				}	break;

				case _hoops_CSRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw segment", null);
				}	break;

				case _hoops_SSRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw segment tree", null);
				}	break;

				case _hoops_GGACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "select 3d marker", null);
				}	break;

				case _hoops_RGACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "select 3d polyline", null);
				}	break;

				case _hoops_AGACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "select 3d polygon", null);
				}	break;

				case _hoops_PGACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "select 3d text", null);
				}	break;

				case _hoops_HGACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "select 3d geometry", null);
				}	break;

				case _hoops_IGACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "select text", null);
				}	break;

				case _hoops_CGACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "select window", null);
				}	break;

				case _hoops_SGACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "select segment", null);
				}	break;

				case _hoops_GRACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "select segment tree", null);
				}	break;

				case _hoops_RRACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "driver startup", null);
				}	break;

				case _hoops_ARACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "driver shutdown", null);
				}	break;

				case _hoops_PRACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw dc cut line", null);
				}	break;

				case _hoops_HRACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d isoline", null);
				}	break;

				case _hoops_IRACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "hlr polyline", null);
				}	break;

				case _hoops_CRACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "hlr marker", null);
				}	break;

				case _hoops_SRACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "hlr hidden polyline", null);
				}	break;

				case _hoops_GAACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "hlr hidden marker", null);
				}	break;

				case _hoops_PAACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "finish picture", null);
				}	break;

				case _hoops_HAACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "create region", null);
				}	break;

				case _hoops_IAACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "save region", null);
				}	break;

				case _hoops_CAACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "restore region", null);
				}	break;

				case _hoops_SAACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "destroy region", null);
				}	break;

				case _hoops_CCRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d sphere", null);
				}	break;

				case _hoops_SCRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d cylinder", null);
				}	break;

				case _hoops_GSRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d polycylinder", null);
				}	break;

				case _hoops_RSRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d nurbs curve", null);
				}	break;

				case _hoops_ASRCR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d nurbs surface", null);
				}	break;

				case _hoops_GPACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "segment activity change", null);
				}	break;

				case _hoops_RPACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "draw 3d contour", null);
				}	break;

				case _hoops_APACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "populate segment", null);
				}	break;

				case _hoops_PPACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "set shader", null);
				}	break;

				case _hoops_HPACR: {
					_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "process segment", null);
				}	break;

				default: {
					_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unrecognized callback type");
				}	break;
			}

			_hoops_ASAPR = HI_Sprintf1 (_hoops_ASAPR, _hoops_PSAPR, "=%n", (void *)&_hoops_RCACR->name->name);

			if ((_hoops_RCACR = _hoops_RCACR->next) == null) break;

			if (_hoops_AIACR && ! _hoops_GGPCR) {
				_hoops_GGPCR=true;
				HE_WARNING (HEC_CALLBACK, HES_DATA_LENGTH_MISMATCH,
					"Callback data not useful... Use Show One With Data");
			}

			if (_hoops_ASAPR == _hoops_PSAPR) _hoops_ASAPR = null; /* _hoops_PGPCR _hoops_RPP _hoops_PSP _hoops_RSIAR _hoops_IH ',' */
			if (_hoops_ASAPR == null) break;	  /* _hoops_PAR _hoops_RPP _hoops_AIAH _hoops_GGSR _hoops_IIGR _hoops_RSIAR */
			*_hoops_ASAPR++ = ',';		/* _hoops_GGCR ',' _hoops_GAPA _hoops_APSAR */
		}

		if (_hoops_ASAPR == null) {
			HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR);
			return;
		}

		/* _hoops_GHHR _hoops_PRRP */
		if (_hoops_CSACR == -1) {
			if (_hoops_ASAPR == _hoops_PSAPR) {
				HE_ERROR (HEC_MEMORY, HES_BUFFER_OVERFLOW, _hoops_SSACR);
				return;
			}
			*_hoops_ASAPR = '\0';							/* _hoops_IHRPR _hoops_IAHA */
		}
		else {
			_hoops_RGGA (_hoops_ASAPR == _hoops_PSAPR) *_hoops_ASAPR++ = ' ';		/* _hoops_RGPCR/_hoops_AGPCR _hoops_IAHA */
		}
	}
#endif
}


#ifndef DISABLE_SHOW
#ifndef DISABLE_CALLBACKS

local void _hoops_HGPCR (
	_hoops_AIGPR *	_hoops_RIGC,
	_hoops_GCHIR *				callback,
	bool					_hoops_PSACR,
	char const *			_hoops_IGPCR,
	char *					list,
	int						_hoops_GGCIR,
	void **					_hoops_AIACR)
{
	Option_Value *		option;
	int					id;
	_hoops_IHACR *		_hoops_RCACR;

	if (!HI_Parse_Options (_hoops_RIGC, _hoops_IGPCR, _hoops_CIACR (_hoops_IIACR),
						   &option, _hoops_CGPCR))
		return;

	if (option == null) {
		HE_ERROR (HEC_ATTRIBUTE, HES_INVALID_OPTION,
				  Sprintf_S (null,
							 "'%s' is not a recognized option name",
							 _hoops_IGPCR));
		return;
	}
	id = option->type->id;
	HI_Free_Option_List (_hoops_RIGC, option);

	if (_hoops_SGPCR <= 0 && 0 <= _hoops_GRPCR)
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Bad assumption");

	if (id < _hoops_SGPCR || id > _hoops_GRPCR) {
		_hoops_IPR (HEC_INTERNAL_ERROR, HES_PROCEDURAL_ERROR, "Unexpected callback");
		return;
	}

	if (_hoops_AIACR)
		*_hoops_AIACR=0;

	if ((_hoops_RCACR = callback->_hoops_ACHIR) != null) {
		do if (_hoops_RCACR->type == id) {
			if (_hoops_AIACR)
				*_hoops_AIACR = (void*)_hoops_RCACR->_hoops_AIACR;

			HI_Return_Chars (list, _hoops_GGCIR,
							 _hoops_RCACR->name->name.text,
							 _hoops_RCACR->name->name.length);
			return;
		} while ((_hoops_RCACR = _hoops_RCACR->next) != null);
	}

	if (!_hoops_PSACR) {
		HE_ERROR (HEC_CALLBACK, HES_NO_LOCAL_SETTING,
				  Sprintf_SP (null, "'%s' has no local setting in '%p'",
							  _hoops_IGPCR, callback->owner));
		return;
	}

	HI_Return_Chars (list, _hoops_GGCIR, "", 0);
}

#endif
#endif



HC_INTERFACE void HC_CDECL HC_Show_Callback (
	char *				spec)
{
	_hoops_PAPPR context("Show_Callback");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Callback () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RRPCR)) != null) {
		_hoops_GCHIR *	callback;
		if ((callback = (_hoops_GCHIR *)HI_Find_Attribute (context, target, HK_CALLBACK)) != null) {
			HI_Show_Callback (callback, spec, -1, 0);
			_hoops_HPRH (callback);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}


#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_Net_Callback (
	int					count,
	Key const *			keys,
	char *				spec)
{
	_hoops_PAPPR context("PShow_Net_Callback");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_Net_Callback () */\n");
	);

	_hoops_GCHIR *	callback;
	if ((callback = (_hoops_GCHIR *) HI_Find_Attribute_And_Lock(context, _hoops_RRPCR, _hoops_HRPCR, count, keys)) != null) {
		HI_Show_Callback (callback, spec, -1, 0);
		_hoops_HPRH (callback);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(spec, -1, "", 0);

#endif
#endif
}
#endif


HC_INTERFACE void HC_CDECL HC_Show_One_Callback (
	char const *		_hoops_IGPCR,
	char *				spec)
{
	_hoops_PAPPR context("Show_One_Callback");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Callback () */\n");
	);


	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RRPCR)) != null) {
		_hoops_GCHIR *	callback;
		if ((callback = (_hoops_GCHIR *)HI_Find_Attribute (context, target, HK_CALLBACK)) != null) {
			_hoops_HGPCR (context, callback, false, _hoops_IGPCR, spec, -1, 0);
			_hoops_HPRH (callback);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}





HC_INTERFACE void HC_CDECL HC_Show_One_Callback_With_Data (
	char const *		_hoops_IGPCR,
	char *				spec,
	void **				data)
{
	_hoops_PAPPR context("Show_One_Callback_With_Data");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
#ifdef DISABLE_SHOW
	_hoops_IRPPR ("Show");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_One_Callback_With_Data () */\n");
	);

	_hoops_HPAH * target;
	if ((target = HI_Find_Target_And_Lock(context, _hoops_RRPCR)) != null) {

		_hoops_GCHIR *	callback;
		if ((callback = (_hoops_GCHIR *)HI_Find_Attribute (context, target, HK_CALLBACK)) != null) {
			_hoops_HGPCR (context, callback, false, _hoops_IGPCR, spec, -1, data);
			_hoops_HPRH (callback);
		}
		_hoops_IRRPR();
	}
#endif
#endif
}




#ifndef _hoops_ARPCR
HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Callback (
	int					count,
	Key const *			keys,
	char const *		_hoops_IGPCR,
	char *				spec)
{
	_hoops_PAPPR context("PShow_One_Net_Callback");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Callback () */\n");
	);

	_hoops_GCHIR *	callback;
	if ((callback = (_hoops_GCHIR *) HI_Find_Attribute_And_Lock(context, _hoops_RRPCR, _hoops_HRPCR, count, keys)) != null) {
		_hoops_HGPCR (context, callback, true, _hoops_IGPCR, spec, -1, 0);
		_hoops_HPRH (callback);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(spec, -1, "", 0);
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_PShow_One_Net_Callback_WD (
	int					count,
	Key const *			keys,
	char const *		_hoops_IGPCR,
	char *				spec,
	void **				data)
{
	_hoops_PAPPR context("PShow_One_Net_Callback_WD");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
#ifdef _hoops_PRPCR
	_hoops_IRPPR ("PShow");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_PShow_One_Net_Callback_WD () */\n");
	);

	_hoops_GCHIR *	callback;
	if ((callback = (_hoops_GCHIR *) HI_Find_Attribute_And_Lock(context, _hoops_RRPCR, _hoops_HRPCR, count, keys)) != null) {
		_hoops_HGPCR (context, callback, true, _hoops_IGPCR, spec, -1, data);
		_hoops_HPRH (callback);
		_hoops_IRRPR();
	}
	else
		HI_Return_Chars(spec, -1, "", 0);
#endif
#endif
}

#endif



HC_INTERFACE void HC_CDECL HC_Show_Callback_Name (
	char const *		name,
	_hoops_IRPCR *		address)
{
	_hoops_PAPPR context("Show_Callback_Name");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Callback_Name () */\n");
	);

	_hoops_HCRPR	_hoops_CRPCR;
	HI_Canonize_Chars (name, &_hoops_CRPCR);

	_hoops_CSPPR();
	_hoops_HCHIR * _hoops_SRPCR = *HI_Look_Up_Callback_Name (context, _hoops_CRPCR.text, _hoops_CRPCR.length);
	_hoops_RGAIR (_hoops_CRPCR);

	if (_hoops_SRPCR == null) {
		HE_ERROR (HEC_CALLBACK, HES_DEFINITION_NOT_FOUND, "Callback_Name not defined");
	}
	else {
		*address = _hoops_SRPCR->address;
	}
	_hoops_IRRPR();

#endif
}



HC_INTERFACE void HC_CDECL HC_Begin_Callback_Name_Search (void)
{
	_hoops_PAPPR context("Begin_Callback_Name_Search");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Begin_Callback_Name_Search () */\n");
		++HOOPS_WORLD->_hoops_ISPPR;
	);

	_hoops_HCHIR		**_hoops_GAPCR, *callback_name;
	_hoops_AGHPR *		node;
	int					count;

	_hoops_GAPCR = _hoops_RSPPR(context, _hoops_RAPCR);
	if (_hoops_GAPCR == null) {
		_hoops_SPCI (HEC_INTERNAL_ERROR, HES_DATA_ERROR, "Callback_Name hash table missing");
		return;
	}

	_hoops_SSPPR *		_hoops_GGHPR;
	ZALLOC (_hoops_GGHPR, _hoops_SSPPR);
	_hoops_GGHPR->prev = context->_hoops_AAPCR;
	context->_hoops_AAPCR = _hoops_GGHPR;

	_hoops_CSPPR();

	count = _hoops_PAPCR;
	do {
		if ((callback_name = *_hoops_GAPCR) != null) do {
			ALLOC (node, _hoops_AGHPR);
			node->next = _hoops_GGHPR->list;
			_hoops_GGHPR->list = node;
			node->item = (_hoops_HPAH *)callback_name;
			node->_hoops_AGRI = false;
			_hoops_PRRH (callback_name);
			++_hoops_GGHPR->count;
		} while ((callback_name = callback_name->next) != null);
		++_hoops_GAPCR;
	} while (--count > 0);

	_hoops_IRRPR();
#endif
#endif
}


HC_INTERFACE bool HC_CDECL HC_Find_Callback_Name (
	char *			callback_name)
{
	_hoops_PAPPR context("Find_Callback_Name");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Find_Callback_Name () */\n");
	);

	_hoops_AGHPR	*		list;

	if (context->_hoops_AAPCR == null) {
		HE_ERROR (HEC_CALLBACK, HES_INACTIVE_SEARCH, "No callback_name search is active");
		return false;
	}

	while ((list = context->_hoops_AAPCR->list) != null) {
		_hoops_HCHIR		*item = (_hoops_HCHIR *)list->item;

		context->_hoops_AAPCR->list = list->next;
		FREE (list, _hoops_AGHPR);

		/* _hoops_IRHH _hoops_RCRR _hoops_SCH _hoops_RSAS'_hoops_RA _hoops_PGHPR */
		if (!BIT (item->_hoops_RRHH, _hoops_HGAGR)) {
			HI_Return_Sprintf1 (callback_name, -1, "%n", (void *)&item->name);
			_hoops_HPRH (item);
			return true;
		}
		else
			_hoops_HPRH (item);
	}

#endif
#endif
	return false;
}


HC_INTERFACE void HC_CDECL HC_Show_Callback_Name_Count (
	int *					count)
{
	_hoops_PAPPR context("Show_Callback_Name_Count");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		HI_Dump_Code ("/* HC_Show_Callback_Name_Count () */\n");
	);

	_hoops_SSPPR *	_hoops_GGHPR = context->_hoops_AAPCR;

	if (_hoops_GGHPR == null) {
		*count = 0;
		HE_ERROR (HEC_CALLBACK, HES_INACTIVE_SEARCH, "No callback_name search is active");
	}
	else
		*count = _hoops_GGHPR->count;
#endif
#endif
}


HC_INTERFACE void HC_CDECL HC_End_Callback_Name_Search (void)
{
	_hoops_PAPPR context("End_Callback_Name_Search");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
#ifdef DISABLE_SEARCH
	_hoops_IRPPR ("Search");
#else
	CODE_GENERATION (
		--HOOPS_WORLD->_hoops_ISPPR;
		HI_Dump_Code ("/* HC_End_Callback_Name_Search () */\n");
	);

	_hoops_SSPPR *		_hoops_GGHPR = context->_hoops_AAPCR;
	if (_hoops_GGHPR == null) {
		HE_ERROR (HEC_CALLBACK, HES_END_WITHOUT_BEGIN_SEARCH, "End without Begin");
		return;
	}

	HI_Free_Search_List (context, _hoops_GGHPR->list);

	context->_hoops_AAPCR = _hoops_GGHPR->prev;
	FREE (_hoops_GGHPR, _hoops_SSPPR);
#endif
#endif
}



GLOBAL_FUNCTION _hoops_HCHIR ** HI_Look_Up_Callback_Name (
	_hoops_AIGPR *	_hoops_RIGC,
	char const *			name,
	int						length) {
#ifndef DISABLE_CALLBACKS
	int						_hoops_SCPPR;
	char const *			_hoops_RPPA;
	char const *			_hoops_GSPPR;
	_hoops_HCHIR **		_hoops_GAPCR, *_hoops_HAPCR;
	int						_hoops_GCAH = 0;
	int						id;

	id = _hoops_RIGC->_hoops_IAPCR;

	if ((_hoops_GAPCR = _hoops_RSPPR(_hoops_RIGC, _hoops_RAPCR)) == null) {
		ZALLOC_ARRAY (_hoops_GAPCR, _hoops_PAPCR, _hoops_HCHIR *);
		_hoops_RSPPR(_hoops_RIGC, _hoops_RAPCR) = _hoops_GAPCR;
	}

	_hoops_RPPA = name;
	_hoops_SCPPR = length;
	do _hoops_GCAH += (int)*_hoops_RPPA++;
	_hoops_RGGA (--_hoops_SCPPR == 0);

	/*** _hoops_PGCR'_hoops_GRI _hoops_HSPPR _hoops_RGAR! ***/
	_hoops_GAPCR += _hoops_GCAH & (_hoops_PAPCR - 1);

	while ((_hoops_HAPCR = *_hoops_GAPCR) != null) {
		if (_hoops_HAPCR->name.length == length) {
			_hoops_SCPPR = length;
			_hoops_RPPA = name;
			_hoops_GSPPR = _hoops_HAPCR->name.text;
			while (*_hoops_RPPA++ == *_hoops_GSPPR++) if (--_hoops_SCPPR == 0)
				return _hoops_GAPCR;
		}

		_hoops_GAPCR = &_hoops_HAPCR->next;
	}

	return _hoops_GAPCR;
#else
	return null;
#endif
}


HC_INTERFACE void HC_CDECL HC_UnDefine_Callback_Name (
	char const *		iname)
{
	_hoops_PAPPR context("UnDefine_Calback_Name");

#ifdef DISABLE_CALLBACKS
	_hoops_IRPPR ("Callbacks");
#else
	CODE_GENERATION (
		HI_Dump_Code (Sprintf_S (null, "HC_UnDefine_Callback_Name (%S);\n", iname));
	);

	_hoops_HCRPR				_hoops_CRPCR;
	HI_Canonize_Chars (iname, &_hoops_CRPCR);

	_hoops_RPPPR();

	_hoops_HCHIR *	_hoops_RCHIR = *HI_Look_Up_Callback_Name (context, _hoops_CRPCR.text, _hoops_CRPCR.length);

	if (_hoops_RCHIR == null) {
		HE_WARNING (HEC_CALLBACK, HES_UNDEFINE_FAILED,
			Sprintf_N (null, "Callback_Name '%n' not currently defined - can't UnDefine",&_hoops_CRPCR));
	}
	else
		HI_Generic_Delete (context, (_hoops_HPAH *)_hoops_RCHIR);

	_hoops_RGAIR (_hoops_CRPCR);

	_hoops_IRRPR();
#endif
}

